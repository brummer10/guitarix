/*
 * Copyright (C) 2013 Andreas Degert
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "guitarix.h"
#include <sys/mman.h>
#ifndef GUITARIX_AS_PLUGIN
#include "jsonrpc_methods.h"
#else
#include "jsonrpc_methods-generated.h"
#endif
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <giomm/resolver.h>
#include <giomm/inetsocketaddress.h>
#ifdef HAVE_BLUEZ
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#endif


#if !defined(__APPLE__) && !defined(__FreeBSD__) && !defined(_WINDOWS)
#include <malloc.h>

void set_memory_allocation() {
    if (mlockall(MCL_CURRENT | MCL_FUTURE))
        gx_print_error("system init", "mlockall failed:");
#if defined(M_TRIM_THRESHOLD) && defined(M_MMAP_MAX)
    mallopt(M_TRIM_THRESHOLD, -1);
    mallopt(M_MMAP_MAX, 0);
#endif
}

#else

void set_memory_allocation() {}

#endif

void lock_rt_memory() {
#ifndef GUITARIX_AS_PLUGIN
#ifndef __APPLE__
    extern char __start_rt_text[], __stop_rt_text[];
    extern char __start_rt_data[], __stop_rt_data[];
    struct {
	char *start;
	long len;
    } regions[] = {
	{ __start_rt_text, __stop_rt_text - __start_rt_text },
	{ __start_rt_data, __stop_rt_data - __start_rt_data },
    };
#ifndef NDEBUG
    long int total_size = 0;
#endif
    set_memory_allocation();
    for (unsigned int i = 0; i < sizeof(regions)/sizeof(regions[0]); i++) {
#ifndef NDEBUG
        total_size +=regions[i].len;
#endif
        if (mlock(regions[i].start, regions[i].len) != 0) {
            gx_print_error(
            "system init",
            boost::format(_("failed to lock memory: %1%")) % strerror(errno));
        }
    }
#ifndef NDEBUG
    fprintf(stderr,"mlock %ld bytes\n",total_size);
#endif
#endif
#endif
}

void unlock_rt_memory() {
#ifndef GUITARIX_AS_PLUGIN
#ifndef __APPLE__    
    extern char __start_rt_text[], __stop_rt_text[];
    extern char __start_rt_data[], __stop_rt_data[];
    struct {
    char *start;
    long len;
    } regions[] = {
    { __start_rt_text, __stop_rt_text - __start_rt_text },
    { __start_rt_data, __stop_rt_data - __start_rt_data },
    };
#ifndef NDEBUG
    long int total_size = 0;
#endif
    for (unsigned int i = 0; i < sizeof(regions)/sizeof(regions[0]); i++) {
#ifndef NDEBUG
        total_size +=regions[i].len;
#endif
        if (munlock(regions[i].start, regions[i].len) != 0) {
            gx_print_error(
            "system init",
            boost::format(_("failed to unlock memory: %1%")) % strerror(errno));      
        }
    }
#ifndef NDEBUG
    fprintf(stderr,"munlock %ld bytes\n",total_size);
#endif  
#endif
#endif
}

namespace gx_engine {

GxMachineBase::GxMachineBase()
    : impresp_list() {
}

GxMachineBase::~GxMachineBase() {
}

void GxMachineBase::set_update_parameter(void *control, const string& id, bool on) {
    if (on) {
	update_map[id].insert(control);
	if (!update_timeout.connected()) {
	    update_timeout = Glib::signal_timeout().connect(
		sigc::mem_fun(*this, &GxMachineBase::update_parameter), 60);
	}
    } else {
	output_listen_map::iterator i = update_map.find(id);
	if (i != update_map.end()) {
	    i->second.erase(control);
	    if (i->second.empty()) {
		update_map.erase(id);
	    }
	}
	if (update_map.empty()) {
	    update_timeout.disconnect();
	}
    }
}


/****************************************************************
 ** GxMachine
 */

void set_engine_mute(GxEngineState s, BoolParameter& p) {
    p.set(s == kEngineOff);
}

void on_engine_mute_changed(bool s, GxEngine& engine) {
    if (s) {
	engine.set_state(kEngineOff);
    } else {
	if (engine.get_state() == kEngineOff) {
	    engine.set_state(kEngineOn);
	}
    }
}

void on_engine_bypass_changed(bool s, GxEngine& engine) {
    if (s) {
	engine.set_state(kEngineBypass);
    } else {
	if (engine.get_state() == kEngineBypass) {
	    engine.set_state(kEngineOn);
	}
    }
}

void GxMachine::process_cmdline_bank_preset() {
#ifndef GUITARIX_AS_PLUGIN
    Glib::ustring sbank = options.get_setbank();
    if (sbank.empty()) {
        return;
    }
    sbank = sbank.lowercase();
    if (sbank.size() < 2) {
        return;
    }
    Glib::ustring bank = settings.banks.get_name(
        KeySwitcher::key_offset_to_bank_idx(sbank[0]-'a', bank_size()));
    int i = (sbank[1] == ':' ? 2 : 1);
    Glib::ustring preset = get_bank_file(bank)->get_name(
        KeySwitcher::key_offset_to_idx(std::stoi(sbank.substr(i))));
    options.set_bank_preset(bank, preset);
#endif
}

GxMachine::GxMachine(gx_system::CmdlineOptions& options_):
    GxMachineBase(),
    options(options_),
    engine(options.get_plugin_dir(), gx_engine::get_group_table(), options),
    jack(engine),
    settings(options, jack, engine.stereo_convolver, gx_engine::midi_std_ctr,
	     engine.controller_map, engine),
    tuner_switcher(settings, engine),
    sock(0),
#ifdef HAVE_AVAHI
    avahi_service(0),
#endif
    pmap(engine.get_param()),
    switch_bank() {
    engine.oscilloscope.set_jack(jack);
    process_cmdline_bank_preset();

    /*
    ** setup parameters
    */

    static value_pair starter[] = {
	{ "other", "other" },
	{ "qjackctl", "qjackctl" },
	{ "autostart", "autostart" },
	{0}
    };
    pmap.reg_non_midi_enum_par(
	"ui.jack_starter_idx", "", starter, static_cast<int*>(0), false, 1);
    pmap.reg_non_midi_par("ui.ask_for_jack_starter", (bool*)0, false, true);
    pmap.reg_string("ui.jack_starter", "", 0, "");

    // rack tuner
    gx_engine::get_group_table().insert("racktuner", N_("Rack Tuner"));
    static const value_pair streaming_labels[] = {{"scale"}, {"stream"}, {0}};
    pmap.reg_non_midi_enum_par("racktuner.streaming", "Streaming Mode", streaming_labels, (int*)0, false, 1);
    static const value_pair tuning_labels[] = {{"(Chromatic)"},{"Standard"}, {"Standard/Es"}, {"Open E"}, 
        {"Drop D"},{"Half Step Down"},{"Full Step Down"},{"1 and 1/2 Steps Down"},{"Double Drop D"},{"Drop C"},
        {"Drop C#"},{"Drop B"},{"Drop A#"},{"Drop A"},{"Open D"},{"Open D Minor"}, {"Open G"},{"Open G Minor"},
        {"Open C"},{"Open C#"},{"Open C Minor"},{"Open E7"},{"Open E Minor7"},{"Open G Major7"},{"Open A Minor"},
        {"Open A Minor7"},{"Open A"},{"C Tuning"},{"C# Tuning"},{"Bb Tuning"},{"A to A (Baritone)"},{"Open Dsus2"},
        {"Open Gsus2"},{"G6"},{"Modal G"},{"Overtone"},{"Pentatonic"},{"Minor Third"},{"Major Third"},{"All Fourths"},
        {"Augmented Fourths"},{"Slow Motion"},{"Admiral"},{"Buzzard"},{"Face"},{"Four and Twenty"},{"Ostrich"},{"Capo 200"},
        {"Balalaika"},{"Cittern One"},{"Cittern Two"},{"Dobro"},{"Lefty"},{"Mandoguitar"},{"Rusty Cage"},{"Hardcore"}, {0}};
    pmap.reg_non_midi_enum_par("racktuner.tuning", "Tuning", tuning_labels, (int*)0, false, 0);
    static const value_pair tuning_temperament[] = {{"12-ET"},{"19-ET"},{"24-ET"},{"31-ET"},{"41-ET"},{"53-ET"}, {0}};
    pmap.reg_non_midi_enum_par("racktuner.temperament", "Temperament", tuning_temperament, (int*)0, false, 0);
    pmap.reg_par_non_preset("racktuner.scale_lim", "Limit", 0, 3.0, 1.0, 10.0, 1.0);
    pmap.reg_par_non_preset("ui.tuner_reference_pitch", "?Tuner Reference Pitch", 0, 440, 225, 453, 0.1);
    //pmap.reg_par("racktuner.scale_lim", "Limit", &scale_lim, 3.0, 1.0, 10.0, 1.0); FIXME add in detail view?

    static const value_pair midi_channels[] = {{"--"},{"1"},{"2"},{"3"},{"4"},{"5"},{"6"},{"7"},{"8"},{"9"},{"10"},
        {"11"},{"12"},{"13"},{"14"},{"15"},{"16"}, {0}};
    EnumParameter* ep = pmap.reg_non_midi_enum_par("system.midi_channel", "Midichannel", midi_channels, (int*)0, false, 0);
    ep->signal_changed_int().connect(sigc::mem_fun(this, &GxMachineBase::set_midi_channel));

    pmap.reg_par("ui.live_play_switcher", "Liveplay preset mode" , (bool*)0, false, false)->setSavable(false);
    BoolParameter& up = pmap.reg_par("ui.racktuner", N_("Tuner on/off"), (bool*)0, false, false)->getBool();
    up.signal_changed().connect(
        sigc::mem_fun(this, &GxMachineBase::tuner_switch));
    pmap.reg_non_midi_par("system.show_tuner", (bool*)0, false);
    pmap.reg_non_midi_par("system.stick_tuner", (bool*)0, false);
    BoolParameter& mp = pmap.reg_par("system.midiout_tuner", "Tuner midi output",(bool*)0, false, false)->getBool();
    mp.signal_changed().connect(
        sigc::mem_fun(this, &GxMachineBase::tuner_used_by_midi));
    
    pmap.reg_non_midi_par("system.midi_in_preset", (bool*)0, false, false);
    pmap.reg_par_non_preset("ui.liveplay_brightness", "?liveplay_brightness", 0, 1.0, 0.5, 1.0, 0.01);
    pmap.reg_par_non_preset("ui.liveplay_background", "?liveplay_background", 0, 0.8, 0.0, 1.0, 0.01);
    pmap.reg_par("engine.next_preset", "Switch to next preset" , (bool*)0, false, false)->setSavable(false);
    pmap.reg_par("engine.previus_preset", "Switch to previous preset" , (bool*)0, false, false)->setSavable(false);
    BoolParameter& p = pmap.reg_par(
	"engine.mute", "Mute", 0, engine.get_state() == gx_engine::kEngineOff
	)->getBool();
    p.setSavable(false);
    engine.signal_state_change().connect(
	sigc::bind(sigc::ptr_fun(set_engine_mute), sigc::ref(p)));
    p.signal_changed().connect(
	sigc::bind(sigc::ptr_fun(on_engine_mute_changed), sigc::ref(engine)));
    BoolParameter& pb = pmap.reg_par(
	"engine.bypass", "Bypass", 0, engine.get_state() == gx_engine::kEngineBypass
	)->getBool();
    pb.setSavable(false);
    pb.signal_changed().connect(
	sigc::bind(sigc::ptr_fun(on_engine_bypass_changed), sigc::ref(engine)));
    pmap.reg_non_midi_par("ui.mp_s_h", (bool*)0, false);
    pmap.reg_non_midi_par("ui.all_s_h", (bool*)0, false);
    BoolParameter& ip = pmap.reg_par(
      "engine.insert", N_("switch insert ports on/off"), (bool*)0, false, false)->getBool();
    ip.signal_changed().connect(
	sigc::mem_fun(this, &GxMachineBase::set_jack_insert));
#ifndef GUITARIX_AS_PLUGIN
    pmap.reg_par("engine.set_stereo", N_("Stereo on/off"), (bool*)0, false, true);
#endif
    gx_preset::UnitPresetList presetnames;
#ifndef GUITARIX_AS_PLUGIN
    plugin_preset_list_load(pluginlist_lookup_plugin("seq")->get_pdef(), presetnames);
#endif
    for (gx_preset::UnitPresetList::iterator i = presetnames.begin(); i != presetnames.end(); ++i) {
        if (!i->name.empty()) {
            Glib::ustring id = "seq." + i->name;
            Glib::ustring tb = "switch to preset " + i->name;
            BoolParameter& sp = pmap.reg_par(
              id, tb, (bool*)0, false, false)->getBool();
            sp.setSavable(false);
            sp.signal_changed().connect(sigc::hide(
               sigc::bind(sigc::bind(sigc::bind(sigc::mem_fun(this, &GxMachine::plugin_preset_list_set_on_idle), i->name), false),pluginlist_lookup_plugin("seq")->get_pdef())));
        }
    }

#ifndef NDEBUG
    // ------ time measurement (debug) ------
    gx_system::add_time_measurement();
#endif
    lock_rt_memory();

    engine.controller_map.signal_new_program().connect(
	sigc::mem_fun(this, &GxMachine::do_program_change));
    engine.controller_map.signal_new_mute_state().connect(
	sigc::mem_fun(this, &GxMachine::set_mute_state));
    engine.controller_map.signal_new_bank().connect(
	sigc::mem_fun(this, &GxMachine::do_bank_change));
    pmap["ui.live_play_switcher"].signal_changed_bool().connect(
	sigc::mem_fun(this, &GxMachine::edge_toggle_tuner));
    switch_bank = settings.get_current_bank();
    pmap["engine.next_preset"].signal_changed_bool().connect(
	sigc::mem_fun(this, &GxMachine::process_next_preset_switch));
    pmap["engine.previus_preset"].signal_changed_bool().connect(
	sigc::mem_fun(this, &GxMachine::process_previus_preset_switch));
    engine.controller_map.signal_trigger_midi_feedback().connect(
        sigc::mem_fun(this, &GxMachine::midi_feedback));
    engine.tuner.signal_freq_changed().connect(
        sigc::mem_fun(this, &GxMachine::on_tuner_freq_changed));
}

GxMachine::~GxMachine() {
    stop_socket();
    unlock_rt_memory();
#ifndef NDEBUG
    if (options.dump_parameter) {
	pmap.dump("json");
    }
#endif
}

void GxMachine::insert_param(Glib::ustring group, Glib::ustring name) {
    
    Glib::ustring tb = "switch to preset " + name;
    Glib::ustring id = group + "." + name;
    BoolParameter& sp = pmap.reg_par(
      id, tb, (bool*)0, false, false)->getBool();
    sp.setSavable(false);
    sp.signal_changed().connect(sigc::hide(
      sigc::bind(sigc::bind(sigc::bind(sigc::mem_fun(this, &GxMachine::plugin_preset_list_set_on_idle), name), false),pluginlist_lookup_plugin("seq")->get_pdef())));
}

void GxMachine::edge_toggle_tuner(bool v) {
    if (v) {
	tuner_switcher.toggle(engine.tuner.used_for_display());
    }
}

void GxMachine::next_preset_switch() {
    gx_system::PresetFileGui *f= get_current_bank_file();
    int idx = f->get_index(get_current_name());
    if (idx+1 < f->size()) load_preset(f, f->get_name(idx+1));
    else load_preset(f, f->get_name(0));
}

void GxMachine::previus_preset_switch() {
    gx_system::PresetFileGui *f= get_current_bank_file();
    int idx = f->get_index(get_current_name());
    if (idx-1 > -1) load_preset(f, f->get_name(idx-1));
    else load_preset(f, f->get_name(f->size()-1));
}

void GxMachine::process_next_preset_switch(bool s) {
    if(s) {
        Glib::signal_idle().connect_once(
          sigc::mem_fun(this, &GxMachine::next_preset_switch));
        set_parameter_value("engine.next_preset",false);
    }
}

void GxMachine::process_previus_preset_switch(bool s) {
    if(s) {
        Glib::signal_idle().connect_once(
          sigc::mem_fun(this, &GxMachine::previus_preset_switch));
        set_parameter_value("engine.previus_preset",false);
    }
}

void GxMachine::do_program_change(int pgm) {
    Glib::ustring bank = settings.get_current_bank();
    if ((bank != switch_bank) && !switch_bank.empty()) {
        bank = switch_bank;
	}
    bool in_preset = !bank.empty();
    gx_system::PresetFile *f;
    if (in_preset) {
        f = settings.banks.get_file(bank);
        in_preset = pgm < f->size();
    }
    if (in_preset) {
        settings.load_preset(f, f->get_name(pgm));
        set_parameter_value("system.current_bank",bank);
	if (engine.get_state() == gx_engine::kEngineBypass) {
	    engine.set_state(gx_engine::kEngineOn);
	}
    } // do nothing when bank/preset is out of range
    // else if (engine.get_state() == gx_engine::kEngineOn) {
	// engine.set_state(gx_engine::kEngineBypass);
    //}
}

void GxMachine::reset_switch_bank() {
	switch_bank = settings.get_current_bank();
}

void GxMachine::do_bank_change(int pgm) {
	if (!get_bank_name(pgm).empty()) {
		switch_bank = get_bank_name(pgm);
		Glib::signal_timeout().connect_once(
		    sigc::mem_fun(this,&GxMachine::reset_switch_bank), 50);
	} else {
		switch_bank = settings.get_current_bank();
	}
}

void GxMachine::set_mute_state(int mute) {
	if (mute == 0) {
		engine.set_state(gx_engine::kEngineOn);
	} else  {
		engine.set_state(gx_engine::kEngineOff);
	}
}

void GxMachine::set_state(GxEngineState state) {
    engine.set_state(state);
}

GxEngineState GxMachine::get_state() {
    return engine.get_state();
}

void GxMachine::load_ladspalist(std::vector<std::string>& old_not_found, ladspa::LadspaPluginList& pluginlist) {
    pluginlist.load(options, old_not_found);
}

void GxMachine::save_ladspalist(ladspa::LadspaPluginList& pluginlist) {
    pluginlist.save(options);
}

void GxMachine::commit_ladspa_changes() {
    if (sock) {
	sock->ladspaloader_update_plugins(0, 0);
    } else {
	engine.ladspaloader_update_plugins();
    }
}

#ifdef GUITARIX_AS_PLUGIN
void GxMachine::timerUpdate() 
{
	if (engine.get_rack_changed())
		if (!engine.check_module_lists())
			engine.clear_rack_changed();
	engine.signal_timeout().emit();
}
#endif
sigc::signal<void,Plugin*,PluginChange::pc>& GxMachine::signal_plugin_changed() {
    return engine.signal_plugin_changed();
}

Plugin *GxMachine::pluginlist_lookup_plugin(const std::string& id) const {
    return engine.pluginlist.lookup_plugin(id);
}

bool GxMachine::load_unit(gx_gui::UiBuilderImpl& builder, PluginDef* pdef) {
#ifndef GUITARIX_AS_PLUGIN
    return builder.load_unit(pdef);
#else
    return false;
#endif
}

void GxMachine::pluginlist_append_rack(UiBuilderBase& ui) {
    engine.pluginlist.append_rack(ui);
}

float GxMachine::get_tuner_freq() {
    return engine.tuner.get_freq();
}

float GxMachine::get_tuner_note() {
    return engine.tuner.get_note();
}

void GxMachine::set_oscilloscope_mul_buffer(int a) {
    engine.oscilloscope.set_mul_buffer(a, jack.get_jack_bs());
}

int GxMachine::get_oscilloscope_mul_buffer() {
    return engine.oscilloscope.get_mul_buffer();
}

gx_system::CmdlineOptions& GxMachine::get_options() const {
    return options;
}

void GxMachine::exit_handler(bool otherthread) {
    if (!otherthread) {
	delete sock;
	sock = 0;
    }
}

void GxMachine::stop_socket() {
#ifdef HAVE_AVAHI
    delete avahi_service;
    avahi_service = 0;
#endif
    delete sock;
    sock = 0;
}

void GxMachine::start_socket(sigc::slot<void> quit_mainloop, const Glib::ustring& host, int port) {
    if (sock) {
	return;
    }
    sock = new GxService(settings, jack, tuner_switcher, quit_mainloop, host, &port);
    sock->start();
    GxExit::get_instance().signal_exit().connect(
	sigc::mem_fun(*this, &GxMachine::exit_handler));
#ifdef HAVE_AVAHI
    if (port > 0) {
	std::string name = "Guitarix";
	if (jack.get_default_instancename() != jack.get_instancename()) {
	    name += ": " + jack.get_instancename();
	}
	avahi_service = new AvahiService;
	avahi_service->register_service(name, port);
    }
#endif
}

sigc::signal<void,const Glib::ustring&,const Glib::ustring&>& GxMachine::tuner_switcher_signal_display() {
    return tuner_switcher.signal_display();
}

sigc::signal<void,TunerSwitcher::SwitcherState>& GxMachine::tuner_switcher_signal_set_state() {
    return tuner_switcher.signal_set_state();
}

sigc::signal<void, bool>& GxMachine::tuner_switcher_signal_selection_done() {
    return tuner_switcher.signal_selection_done();
}

sigc::signal<void,GxEngineState>& GxMachine::signal_state_change() {
    return engine.signal_state_change();
}

void GxMachine::tuner_used_for_display(bool on) {
    engine.tuner.used_for_display(on);
}

void GxMachine::tuner_used_by_midi(bool on) {
    if ((on && get_parameter("ui.racktuner").getBool().get_value()) || !on) {
        engine.tuner.used_by_midi(on);
    }
}

void GxMachine::tuner_switch(bool on) {
    if (!on && get_parameter("system.midiout_tuner").getBool().get_value()) {
        engine.tuner.used_by_midi(false);
    } else if (on && get_parameter("system.midiout_tuner").getBool().get_value()) {
        engine.tuner.used_by_midi(true);
    }
}

const std::vector<std::string>& GxMachine::get_rack_unit_order(PluginType type) {
    return settings.get_rack_unit_order(type == PLUGIN_TYPE_STEREO);
}

sigc::signal<void,bool>& GxMachine::signal_rack_unit_order_changed() {
    return settings.signal_rack_unit_order_changed();
}

void GxMachine::remove_rack_unit(const std::string& unit, PluginType type) {
    if (!settings.remove_rack_unit(unit, type == PLUGIN_TYPE_STEREO)) {
	return;
    }
    settings.signal_rack_unit_order_changed()(type == PLUGIN_TYPE_STEREO);
}

void GxMachine::insert_rack_unit(const std::string& unit, const std::string& before, PluginType type) {
    settings.insert_rack_unit(unit, before, type == PLUGIN_TYPE_STEREO);
    settings.signal_rack_unit_order_changed()(type == PLUGIN_TYPE_STEREO);
}

// tuner_switcher
bool GxMachine::get_tuner_switcher_active() {
    return tuner_switcher.get_active();
}

void GxMachine::tuner_switcher_activate(bool v) {
    tuner_switcher.activate(v);
}

void GxMachine::tuner_switcher_deactivate() {
    tuner_switcher.deactivate();
}

void GxMachine::tuner_switcher_toggle(bool v) {
    tuner_switcher.toggle(v);
}


void GxMachine::on_tuner_freq_changed() {
#ifdef USE_MIDI_CC_OUT
    if (get_parameter("system.midiout_tuner").getBool().get_value()) {
        float fnote = engine.tuner.get_note();
        if (fnote < 999.0) {
            //float tet = get_parameter("racktuner.temperament").getFloat().get_value();
            int note = static_cast<int>(round(fnote));
            uint8_t midi_note = static_cast<uint8_t>(note+69);
            uint8_t vel = static_cast<uint8_t>(((fnote - note) * 127) +63);

            msend_midi_cc(0x90, midi_note,vel, 3);
        } else {
            msend_midi_cc(0xB0, 123, 0, 3);
        }
    }
#endif
}


// preset
bool GxMachine::setting_is_preset() {
    return settings.setting_is_preset();
}


const Glib::ustring& GxMachine::get_current_bank() {
    return settings.get_current_bank();
}

gx_system::PresetFileGui *GxMachine::get_current_bank_file() {
    return settings.get_current_bank_file()->get_guiwrapper();
}

const Glib::ustring& GxMachine::get_current_name() {
    return settings.get_current_name();
}

gx_system::PresetFileGui* GxMachine::get_bank_file(const Glib::ustring& bank) const {
    return settings.banks.get_file(bank)->get_guiwrapper();
}

Glib::ustring GxMachine::get_bank_name(int n) {
    return settings.banks.get_name(n);
}

bool GxMachine::msend_midi_cc(int cc, int pgn, int bgn, int num) {
#ifndef GUITARIX_AS_PLUGIN
	return jack.send_midi_cc(cc, pgn, bgn, num);
#else
    return false;
#endif
}

void GxMachine::load_preset(gx_system::PresetFileGui *pf, const Glib::ustring& name) {
    settings.load_preset(pf, name);
#ifdef USE_MIDI_CC_OUT
    int n = get_bank_index(get_current_bank());
    bool cc_ok = true;
    if (get_bank_index(pf->get_name()) != n) {
        cc_ok = msend_midi_cc(0xB0, 32, get_bank_index(pf->get_name()),3);
    }
    if (cc_ok) { // don't send program change if bank switch failed
        msend_midi_cc(0xC0, pf->get_index(name),0,2);
    }
#endif
}

void GxMachine::loadstate() {
    settings.loadstate();
}

int GxMachine::bank_size() {
    return settings.banks.size();
}

int GxMachine::get_bank_index(const Glib::ustring& bank) {
    return settings.banks.get_index(bank);
}

void GxMachine::create_default_scratch_preset() {
    settings.create_default_scratch_preset();
}

void GxMachine::set_statefilename(const std::string& fn) {
    settings.set_statefilename(fn);
}

void GxMachine::save_to_state(bool preserve_preset) {
    settings.save_to_state(preserve_preset);
}

void GxMachine::plugin_preset_list_load(const PluginDef *pdef, gx_preset::UnitPresetList &presetnames) {
    settings.plugin_preset_list_load(pdef, presetnames);
}

void GxMachine::plugin_preset_list_set(const PluginDef *pdef, bool factory, const Glib::ustring& name) {
    settings.plugin_preset_list_set(pdef, factory, name);
}

void GxMachine::plugin_preset_list_sync_set(const PluginDef *pdef, bool factory, const Glib::ustring& name) {
    settings.plugin_preset_list_sync_set(pdef, factory, name);
}

void GxMachine::plugin_preset_list_set_on_idle(const PluginDef *pdef, bool factory, const Glib::ustring& name) {
    Glib::signal_idle().connect_once(
      sigc::bind(sigc::bind(sigc::bind(sigc::mem_fun(this, &GxMachine::plugin_preset_list_sync_set),name),factory),pdef));

}

void GxMachine::plugin_preset_list_save(const PluginDef *pdef, const Glib::ustring& name) {
    settings.plugin_preset_list_save(pdef, name);
}

void GxMachine::plugin_preset_list_remove(const PluginDef *pdef, const Glib::ustring& name) {
    settings.plugin_preset_list_remove(pdef, name);
}

void GxMachine::disable_autosave(bool v) {
    settings.disable_autosave(v);
}

void GxMachine::disable_save_on_exit(bool v) {
    settings.disable_save_on_exit(v);
}

sigc::signal<void>& GxMachine::signal_selection_changed() {
    return settings.signal_selection_changed();
}

sigc::signal<void>& GxMachine::signal_presetlist_changed() {
    return settings.signal_presetlist_changed();
}

gx_system::PresetFileGui* GxMachine::bank_insert_uri(const Glib::ustring& uri, bool move, int position) {
    gx_system::PresetFile *f = settings.bank_insert_uri(uri, move, position);
    if (f) {
	return f->get_guiwrapper();
    } else {
	return 0;
    }
}

gx_system::PresetFileGui *GxMachine::bank_insert_new(const Glib::ustring& name) {
    gx_system::PresetFile *f = settings.bank_insert_new(name);
    if (f) {
	return f->get_guiwrapper();
    } else {
	return 0;
    }
}

bool GxMachine::rename_bank(const Glib::ustring& oldname, Glib::ustring& newname) {
    return settings.rename_bank(oldname, newname);
}

bool GxMachine::rename_preset(gx_system::PresetFileGui& pf, const Glib::ustring& oldname, const Glib::ustring& newname) {
    return settings.rename_preset(pf, oldname, newname);
}

void GxMachine::bank_reorder(const std::vector<Glib::ustring>& neworder) {
    settings.banks.reorder(neworder);
}

void GxMachine::reorder_preset(gx_system::PresetFileGui& pf, const std::vector<Glib::ustring>& neworder) {
    settings.reorder_preset(pf, neworder);
}

bool GxMachine::bank_check_reparse() {
    return settings.banks.check_reparse();
}

void GxMachine::erase_preset(gx_system::PresetFileGui& pf, const Glib::ustring& name) {
    settings.erase_preset(pf, name);
}

void GxMachine::bank_set_flag(gx_system::PresetFileGui *pf, int flag, bool v) {
    static_cast<gx_system::PresetFile*>(pf)->set_flag(flag, v);
    settings.banks.save();
    signal_presetlist_changed()();
}

std::string GxMachine::bank_get_filename(const Glib::ustring& bank) {
    return settings.banks.get_file(bank)->get_filename();
}

void GxMachine::bank_drag_begin() {
}

gx_system::PresetFileGui *GxMachine::bank_get_file(const Glib::ustring& bank) const {
    return settings.banks.get_file(bank)->get_guiwrapper();
}

bank_iterator GxMachine::bank_begin() {
    return bank_iterator(settings.banks.begin());
}

bank_iterator GxMachine::bank_end() {
    return bank_iterator(settings.banks.end());
}

void GxMachine::pf_append(gx_system::PresetFileGui& pf, const Glib::ustring& src, gx_system::PresetFileGui& pftgt, const Glib::ustring& name) {
    settings.append(pf, src, pftgt, name);
}

void GxMachine::pf_insert_before(gx_system::PresetFileGui& pf, const Glib::ustring& src, gx_system::PresetFileGui& pftgt, const Glib::ustring& pos, const Glib::ustring& name) {
    settings.insert_before(pf, src, pftgt, pos, name);
}

void GxMachine::pf_insert_after(gx_system::PresetFileGui& pf, const Glib::ustring& src, gx_system::PresetFileGui& pftgt, const Glib::ustring& pos, const Glib::ustring& name) {
    settings.insert_after(pf, src, pftgt, pos, name);
}

bool GxMachine::convert_preset(gx_system::PresetFileGui& pf) {
    return settings.convert_preset(pf);
}

bool GxMachine::bank_remove(const Glib::ustring& bank) {
    return settings.remove_bank(bank);
}

void GxMachine::bank_save() {
    settings.banks.save();
}

void GxMachine::pf_save(gx_system::PresetFileGui& pf, const Glib::ustring& name) {
    settings.save(pf, name);
}


// jack
gx_jack::GxJack *GxMachine::get_jack() {
    return &jack;
}

void GxMachine::set_jack_insert(bool v) {
    return jack.set_jack_insert(v);
}

// pmap
Parameter& GxMachine::get_parameter(const char *p) {
    return pmap[p];
}

Parameter& GxMachine::get_parameter(const std::string& id) {
    return pmap[id];
}

void GxMachine::set_init_values() {
    pmap.set_init_values();
}

bool GxMachine::update_parameter() {
    for (output_listen_map::const_iterator i = update_map.cbegin(); i != update_map.cend(); ++i) {
	Parameter& p = pmap[i->first];
	if (p.isMaxlevel()) {
	    float*f = p.getFloat().value;
	    if (sock) {
		*f = sock->update_maxlevel(i->first, true);
		}
	    p.trigger_changed();
	    *f = 0.0;
	} else {
	    p.trigger_changed();
	}
    }
    return true;
}

bool GxMachine::parameter_hasId(const char *p) {
    return pmap.hasId(p);
}

bool GxMachine::parameter_hasId(const std::string& id) {
    return pmap.hasId(id);
}

void GxMachine::reset_unit(const PluginDef *pdef) const {
    pmap.reset_unit(pdef);
}

bool GxMachine::parameter_unit_has_std_values(const PluginDef *pdef) const {
    return pmap.unit_has_std_values(pdef);
}

void GxMachine::set_parameter_value(const std::string& id, int value) {
#ifdef USE_MIDI_CC_OUT
    if (options.system_midiout) {
        const gx_engine::MidiController *pctrl;
        IntParameter& p = get_parameter(id).getInt();
        if (p.get_value() != value) {
            int nctl = midi_param2controller(p, &pctrl);
            if (nctl > -1 && nctl < 128) {
                int state = int(((float(value) - p.getLowerAsFloat()) /
                    (p.getUpperAsFloat() - p.getLowerAsFloat())) * 127.0);
                msend_midi_cc(0xB0, nctl, state, 3);
                if (pctrl->toggle_behaviour() != Parameter::toggle_type::OnOff) {
                    engine.controller_map.set_last_midi_control_value(nctl, state);
                } else {
                    engine.controller_map.set_last_midi_control_value(nctl, p.get_value()*127);
                }
            }
        }
    }
#endif
    pmap[id].getInt().set(value);
}

void GxMachine::set_parameter_value(const std::string& id, bool value) {
#ifdef USE_MIDI_CC_OUT
    if (options.system_midiout) {
        const gx_engine::MidiController *pctrl;
        BoolParameter& p = get_parameter(id).getBool();
        if (p.get_value() != value) {
            int nctl = midi_param2controller(p, &pctrl);
            if (nctl > -1 && nctl < 128) {
                int state = int(value * 127);
                msend_midi_cc(0xB0, nctl,state, 3);
                if (pctrl->toggle_behaviour() != Parameter::toggle_type::OnOff) {
                    engine.controller_map.set_last_midi_control_value(nctl, state);
                } else {
                    engine.controller_map.set_last_midi_control_value(nctl, p.get_value()*127);
                }
            }
        }
    }
#endif
    pmap[id].getBool().set(value);
}

void GxMachine::set_parameter_value(const std::string& id, float value) {
#ifdef USE_MIDI_CC_OUT
    if (options.system_midiout) {
        const gx_engine::MidiController *pctrl;
        FloatParameter& p = get_parameter(id).getFloat();
        if ( std::fabs(p.get_value() - value) > 0.00001) {
            int nctl = midi_param2controller(p, &pctrl);
            if (nctl > -1 && nctl < 128) {
                int state = int(((float(value) - p.getLowerAsFloat()) /
                    (p.getUpperAsFloat() - p.getLowerAsFloat())) * 127.0);
                msend_midi_cc(0xB0, nctl, state, 3);
               // if (pctrl->toggle_behaviour() != Parameter::toggle_type::OnOff) {
               //     engine.controller_map.set_last_midi_control_value(nctl, state);
               // } else {
               //      engine.controller_map.set_last_midi_control_value(nctl, p.get_value()*127);
               // }
            }
        }
    }
#endif
    pmap[id].getFloat().set(value);
}

void GxMachine::set_parameter_value(const std::string& id, const std::string& value) {
    pmap[id].getString().set(value);
}

int GxMachine::_get_parameter_value_int(const std::string& id) {
    return pmap[id].getInt().get_value();
}

int GxMachine::_get_parameter_value_bool(const std::string& id) {
    return pmap[id].getBool().get_value();
}

float GxMachine::_get_parameter_value_float(const std::string& id) {
    return pmap[id].getFloat().get_value();
}

std::string GxMachine::_get_parameter_value_string(const std::string& id) {
    return pmap[id].getString().get_value();
}

sigc::signal<void, int>& GxMachine::_signal_parameter_value_int(const std::string& id) {
    return pmap[id].signal_changed_int();
}

sigc::signal<void, bool>& GxMachine::_signal_parameter_value_bool(const std::string& id) {
    return pmap[id].signal_changed_bool();
}

sigc::signal<void, float>& GxMachine::_signal_parameter_value_float(const std::string& id) {
    return pmap[id].signal_changed_float();
}

// MidiControllerList
bool GxMachine::midi_get_config_mode(int *ctl) {
    if (engine.controller_map.get_config_mode()) {
	*ctl = engine.controller_map.get_current_control();
	return true;
    }
    return false;
}

void GxMachine::midi_set_config_mode(bool v, int ctl) {
    engine.controller_map.set_config_mode(v, ctl);
}

sigc::signal<void>& GxMachine::signal_midi_changed() {
    return engine.controller_map.signal_changed();
}

sigc::signal<void, int, int>& GxMachine::signal_midi_value_changed() {
    return engine.controller_map.signal_midi_value_changed();
}

void GxMachine::request_midi_value_update() {
    engine.controller_map.request_midi_value_update();
}

int GxMachine::midi_size() {
    return engine.controller_map.size();
}

midi_controller_list& GxMachine::midi_get(int n) {
    return engine.controller_map[n];
}

void GxMachine::midi_deleteParameter(Parameter& param) {
    engine.controller_map.deleteParameter(param);
}

void GxMachine::midi_set_current_control(int v) {
    engine.controller_map.set_current_control(v);
}

void GxMachine::midi_modifyCurrent(Parameter& param, float lower, float upper,
                                   bool toggle, int toggle_behaviour) {
    engine.controller_map.modifyCurrent(param, lower, upper, toggle, toggle_behaviour);
}

int GxMachine::midi_param2controller(Parameter& param, const MidiController** p) {
    return engine.controller_map.param2controller(param, p);
}

void GxMachine::set_midi_channel(int s) {
    return engine.controller_map.set_midi_channel(s);
}

void GxMachine::midi_feedback(int c, int v) {
#ifdef USE_MIDI_CC_OUT
    if (options.system_midiout) {
        // Don't send midi feedback for bpm / jack_transport and not on/off events
        if ( c !=22 && c != 24 && c < 128) {
            msend_midi_cc(0xB0, c,v, 3);
        }
    }
#endif
}

bool GxMachine::get_midi_feedback() {
    return options.system_midiout;
}

void GxMachine::set_midi_feedback(int v) {
    options.system_midiout = v;
}

// Convolver

void GxMachine::on_impresp(const std::string& path) {
    gx_system::IRFileListing l(path);
    impresp_list(path, l.get_listing());
}

void GxMachine::reload_impresp_list(const std::string& path) {
    Glib::signal_idle().connect_once(
	sigc::bind(
	    sigc::mem_fun(this, &GxMachine::on_impresp), path));
}

void GxMachine::load_impresp_dirs(std::vector<gx_system::FileName>& dirs) {
    assert(false);
}

bool GxMachine::read_audio(const std::string& filename, unsigned int *audio_size, int *audio_chan,
			   int *audio_type, int *audio_form, int *audio_rate, float **buffer) {
    return gx_engine::read_audio(filename, audio_size, audio_chan, audio_type, audio_form, audio_rate, buffer);
}


/****************************************************************
 ** GxMachineRemote
 */

#ifdef NDEBUG
#define START_NOTIFY(m)  { start_call(RPNM_##m)
#else
#define START_NOTIFY(m)  { const jsonrpc_method_def& _md = start_call(RPNM_##m)
#endif

#define SEND()           assert(!_md.has_result); send(); }

#define START_CALL(m)    { const jsonrpc_method_def& _md = start_call(RPCM_##m)

#define START_RECEIVE(s) assert(_md.has_result); send(); { \
                           gx_system::JsonStringParser *jp = receive();\
                           if (!jp) { return s; }\
			   try {

#define END_RECEIVE(s)     } catch (const gx_system::JsonException& e) { report_rpc_error(jp, e, _md.name); } \
			 delete jp; s; }}


GxMachineRemote::GxMachineRemote(gx_system::CmdlineOptions& options_)
    : GxMachineBase(),
      options(options_),
      pmap(),
      pluginlist(),
      banks(),
      engine_state_change(),
      selection_changed(),
      presetlist_changed(),
      socket(),
      writebuf(),
      os(),
      jw(0),
      notify_list(),
      idle_conn(),
      rack_units(),
      midi_changed(),
      midi_value_changed(),
      current_bank(),
      current_preset(),
      bank_drag_get_counter(),
      bank_drag_get_path(),
      tuner_switcher_display(),
      tuner_switcher_set_state(),
      tuner_switcher_selection_done() {
    if (options.get_rpcaddress().compare(0, 3, "BT:") == 0) {
	create_bluetooth_socket(options.get_rpcaddress().substr(3));
    } else {
	create_tcp_socket();
    }
    socket->set_blocking(true);
#ifdef GUITARIX_AS_PLUGIN
    writebuf = new __gnu_cxx::stdio_filebuf<char>(socket->get_fd(), std::ios::out);
    os = new ostream(writebuf);
#else
    writebuf = new  boost::iostreams::file_descriptor_sink;
    writebuf->open(socket->get_fd(),boost::iostreams::never_close_handle);
    os = new boost::iostreams::stream<boost::iostreams::file_descriptor_sink>(*writebuf);
#endif
    jw = new gx_system::JsonWriter(os, false);

    START_CALL(parameterlist);
    START_RECEIVE();
    pmap.readJSON(*jp);
    END_RECEIVE();
    current_bank = pmap["system.current_bank"].getString().get_value();
    current_preset = pmap["system.current_preset"].getString().get_value();
    START_CALL(pluginlist);
    START_RECEIVE();
    pluginlist.readJSON(*jp, pmap);
    END_RECEIVE();
    START_CALL(banks);
    START_RECEIVE();
    banks.readJSON_remote(*jp);
    END_RECEIVE();
    START_CALL(get_midi_controller_map);
    START_RECEIVE();
    midi_controller_map.readJSON(*jp, pmap);
    END_RECEIVE();
    START_NOTIFY(listen);
    jw->write("preset");
    jw->write("state");
    //we don't need "freq"
    jw->write("display");
    jw->write("tuner");
    jw->write("presetlist_changed");
    jw->write("logger");
    jw->write("midi");
    jw->write("param");
    jw->write("plugins_changed");
    jw->write("misc");
    jw->write("units_changed");
    SEND();
}

GxMachineRemote::~GxMachineRemote() {
    jw->close();
    delete jw;
    writebuf->close();
    delete os;
    delete writebuf;
}

#ifdef NDEBUG
inline void debug_trace_param(Parameter *p) {}
#else
inline void debug_trace_param(Parameter *p) {
    const char *q = getenv("GUITARIX_TRACE");
    if (!q) {
	return;
    }
    if (*q && q != p->id()) {
	return;
    }
    cerr << "set " << p->id() << " = ";
    if (p->isInt()) {
	cerr << p->getInt().get_value();
    } else if (p->isBool()) {
	cerr << p->getBool().get_value();
    } else if (p->isFloat()) {
	cerr << p->getFloat().get_value();
    } else if (p->isString()) {
	cerr << p->getString().get_value();
    } else if (dynamic_cast<JConvParameter*>(p) != 0) {
	cerr << dynamic_cast<JConvParameter*>(p)->get_value().getFullIRPath();
    } else if (dynamic_cast<SeqParameter*>(p) != 0) {
	cerr << "SeqParameter";
    } else {
	assert(false);
    }
    if (p->get_blocked()) {
	cerr << " (blocked)";
    }
    cerr << endl;
}
#endif

#if HAVE_BLUEZ
void GxMachineRemote::create_bluetooth_socket(const Glib::ustring& bdaddr) {
    struct sockaddr_rc addr = { 0 };
    addr.rc_family = AF_BLUETOOTH;
    str2ba(bdaddr.c_str(), &addr.rc_bdaddr);
    int error = EBUSY;
    for (int channel = 1; channel <= 9; channel++) {
	addr.rc_channel = (uint8_t)channel;
	int s = ::socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
	if (connect(s, (const struct sockaddr *)&addr, sizeof(addr)) < 0) {
	    error = errno;
	    close(s);
	    if (error != EBUSY) {
		break;
	    }
	} else {
	    socket = Gio::Socket::create_from_fd(s);
	    return;
	}
    }
    char buf[100];
    throw GxFatalError(
	Glib::ustring::compose(
	    _("Remote Connection: cannot connect to bluetooth %1: %2"),
	    bdaddr, strerror_r(error, buf, sizeof(buf))));
}
#else // !HAVE_BLUEZ
void GxMachineRemote::create_bluetooth_socket(const Glib::ustring& bdaddr) {
    gx_print_fatal(
	_("frontend"),
	_("Bluetooth not available; rebuild Guitarix with Bluetooth support"));
}
#endif // HAVE_BLUEZ

void GxMachineRemote::create_tcp_socket() {
    socket = Gio::Socket::create(Gio::SOCKET_FAMILY_IPV4, Gio::SOCKET_TYPE_STREAM, Gio::SOCKET_PROTOCOL_TCP);
    int flag = 1;
    if (setsockopt(socket->get_fd(), IPPROTO_TCP, TCP_NODELAY, &flag, sizeof(int)))
        gx_print_error("GxMachineRemote","setsockopt(IPPROTO_TCP, TCP_NODELAY) failed");
    typedef std::vector< Glib::RefPtr<Gio::InetAddress> > adr_list;
    adr_list al;
    try {
	al = Gio::Resolver::get_default()->lookup_by_name(options.get_rpcaddress());
    } catch (Glib::Error& e) {
	gx_print_fatal(_("Remote Connection"), e.what());
    }
    Glib::ustring msg;
    bool error = true;
    for (adr_list::iterator i = al.begin(); i != al.end(); ++i) {
	try {
	    socket->connect(Gio::InetSocketAddress::create(*i, options.get_rpcport()));
	    error = false;
	} catch (Gio::Error& e) {
	    msg = e.what();
	    error = true;
	}
    }
    if (error) {
	gx_print_fatal(_("Remote Connection"), msg);
    }
}

void GxMachineRemote::param_signal(Parameter *p) {
    debug_trace_param(p);
    if (p->get_blocked()) {
	return;
    }
    START_NOTIFY(set);
    jw->write(p->id());
    if (p->isInt()) {
	jw->write(p->getInt().get_value());
    } else if (p->isBool()) {
	jw->write(p->getBool().get_value());
    } else if (p->isFloat()) {
	jw->write(p->getFloat().get_value());
    } else if (p->isString()) {
	jw->write(p->getString().get_value());
    } else if (dynamic_cast<JConvParameter*>(p) != 0) {
	dynamic_cast<JConvParameter*>(p)->get_value().writeJSON(*jw);
    } else if (dynamic_cast<SeqParameter*>(p) != 0) {
	dynamic_cast<SeqParameter*>(p)->get_value().writeJSON(*jw);
    } else {
	assert(false);
    }
    SEND();
}

void GxMachineRemote::parameter_changed(gx_system::JsonStringParser *jp) {
    Parameter& p = pmap[jp->current_value()];
    p.set_blocked(true);
    if (p.isFloat()) {
	float v;
	switch (jp->next()) {
	case gx_system::JsonParser::value_string:
	    v = dynamic_cast<FloatEnumParameter*>(&p)->idx_from_id(jp->current_value());
	    break;
	case gx_system::JsonParser::value_number:
	    v = jp->current_value_float();
	    break;
	default:
	    assert(false);
	    v = 0;
	}
	p.getFloat().set(v);
    } else if (p.isInt()) {
	int v;
	switch (jp->next()) {
	case gx_system::JsonParser::value_string:
	    v = p.getEnum().idx_from_id(jp->current_value());
	    break;
	case gx_system::JsonParser::value_number:
	    v = jp->current_value_int();
	    break;
	default:
	    assert(false);
	    v = 0;
	}
	p.getInt().set(v);
    } else if (p.isBool()) {
	jp->next(gx_system::JsonParser::value_number);
	p.getBool().set(jp->current_value_int());
    } else if (p.isString()) {
	jp->next(gx_system::JsonParser::value_string);
	p.getString().set(jp->current_value());
    } else if (p.isFile()) {
	cerr << "change file parameter " << p.id() << endl;
    } else if (dynamic_cast<JConvParameter*>(&p) != 0) {
	JConvParameter* pj = dynamic_cast<JConvParameter*>(&p);
	pj->readJSON_value(*jp);
	pj->setJSON_value();
    } else if (dynamic_cast<SeqParameter*>(&p) != 0) {
	SeqParameter* pj = dynamic_cast<SeqParameter*>(&p);
	pj->readJSON_value(*jp);
	pj->setJSON_value();
    } else if (dynamic_cast<OscParameter*>(&p) != 0) {
	OscParameter* po = dynamic_cast<OscParameter*>(&p);
	po->readJSON_value(*jp);
	po->setJSON_value();
    } else {
	cerr << "change special type parameter " << p.id() << endl;
    }
    p.set_blocked(false);
}

void GxMachineRemote::handle_notify(gx_system::JsonStringParser *jp) {
    jp->next(gx_system::JsonParser::value_string);
    std::string method = jp->current_value();
    jp->next(gx_system::JsonParser::value_key); // "params"
    jp->next(gx_system::JsonParser::begin_array);
    if (method == "state_changed") {
	jp->next(gx_system::JsonParser::value_string);
	engine_state_change(string_to_engine_state(jp->current_value()));
    } else if (method == "message") {
	jp->next(gx_system::JsonParser::value_string);
	GxLogger::MsgType msgtype = GxLogger::kError;
	if (jp->current_value() == "info") {
	    msgtype = GxLogger::kInfo;
	} else if (jp->current_value() == "warning") {
	    msgtype = GxLogger::kWarning;
	}
	jp->next(gx_system::JsonParser::value_string);
	GxLogger::get_logger().print(jp->current_value(), msgtype);
    } else if (method == "preset_changed") {
	jp->next();
	Glib::ustring new_bank = jp->current_value();
	jp->next(gx_system::JsonParser::value_string);
	Glib::ustring new_preset = jp->current_value();
	jp->next(gx_system::JsonParser::end_array);
	current_bank = new_bank;
	current_preset = new_preset;
	selection_changed();
    } else if (method == "presetlist_changed") {
	START_CALL(banks);
	START_RECEIVE();
	banks.readJSON_remote(*jp);
	END_RECEIVE();
	presetlist_changed();
    } else if (method == "set") {
	while (jp->peek() != gx_system::JsonParser::end_array) {
	    jp->next(gx_system::JsonParser::value_string);
	    parameter_changed(jp);
	}
    } else if (method == "rack_units_changed") {
	jp->next(gx_system::JsonParser::begin_array);
	jp->next(gx_system::JsonParser::value_number);
	bool stereo = jp->current_value_int();
	std::vector<std::string>& l = (stereo ? rack_units.stereo : rack_units.mono);
	l.clear();
	while (jp->peek() != gx_system::JsonParser::end_array) {
	    jp->next(gx_system::JsonParser::value_string);
	    l.push_back(jp->current_value());
	}
	jp->next(gx_system::JsonParser::end_array);
	rack_units.rack_unit_order_changed(stereo);
    } else if (method == "midi_changed") {
	midi_controller_map.readJSON(*jp, pmap);
	midi_changed();
    } else if (method == "midi_value_changed") {
	jp->next(gx_system::JsonParser::begin_array);
	jp->next(gx_system::JsonParser::value_number);
	int ctl = jp->current_value_int();
	jp->next(gx_system::JsonParser::value_number);
	int value = jp->current_value_int();
	jp->next(gx_system::JsonParser::end_array);
	midi_value_changed(ctl, value);
    } else if (method == "show_tuner") {
	jp->next(gx_system::JsonParser::value_number);
	tuner_switcher_selection_done(jp->current_value_int());
    } else if (method == "set_display_state") {
	jp->next(gx_system::JsonParser::value_string);
	TunerSwitcher::SwitcherState state = TunerSwitcher::normal_mode;
	if (jp->current_value() == "normal_mode") {
	    state = TunerSwitcher::normal_mode;
	} else if (jp->current_value() == "wait_start") {
	    state = TunerSwitcher::wait_start;
	} else if (jp->current_value() == "listening") {
	    state = TunerSwitcher::listening;
	} else if (jp->current_value() == "wait_stop") {
	    state = TunerSwitcher::wait_stop;
	} else {
	    assert(false);
	}
	tuner_switcher_set_state(state);
    } else if (method == "display_bank_preset") {
	jp->next(gx_system::JsonParser::value_string);
	Glib::ustring bank = jp->current_value();
	jp->next(gx_system::JsonParser::value_string);
	tuner_switcher_display(bank, jp->current_value());
    } else if (method == "impresp_list") {
	std::vector<gx_system::FileName> l;
	jp->next(gx_system::JsonParser::value_string);
	std::string path = jp->current_value();
	while (jp->peek() == gx_system::JsonParser::begin_array) {
	    jp->next(gx_system::JsonParser::begin_array);
	    jp->next(gx_system::JsonParser::value_string);
	    std::string filename = jp->current_value();
	    jp->next(gx_system::JsonParser::value_string);
	    l.push_back(gx_system::FileName(filename, jp->current_value()));
	    jp->next(gx_system::JsonParser::end_array);
	}
	impresp_list(path, l);
    } else if (method == "plugins_changed") {
	update_plugins(jp);
    } else if (method == "server_shutdown") {
#ifndef GUITARIX_AS_PLUGIN
	Gtk::Main::quit();
#endif
    } else {
	cerr << "> " << jp->get_string() << endl;
    }
}

static int socket_get_available_bytes(const Glib::RefPtr<Gio::Socket>& socket) {
    // return socket->get_available_bytes();  // Glib 2.32
    int avail;
    ioctl(socket->get_fd(), FIONREAD, &avail);
    int ret = ioctl(socket->get_fd(), FIONREAD, &avail);
    if (ret != 0) {
	return -1;
    }
    return avail;
}

bool GxMachineRemote::socket_input_handler(Glib::IOCondition cond) {
    if (cond & (Glib::IO_HUP|Glib::IO_ERR|Glib::IO_NVAL)) {
	socket_error(0);
	return false;
    }
    int n = socket_get_available_bytes(socket);
    if (n == 0) {
	return true;
    } else if (n < 0) {
	socket_error(1);
    }
    char buf[10000];
    gx_system::JsonStringParser *jp = new gx_system::JsonStringParser;
    while (true) {
	try {
	    n = socket->receive(buf, sizeof(buf));
	} catch(Glib::Error& e) {
	    delete jp;
	    socket_error(2);
	    return false;
	}
	if (n <= 0) {
	    delete jp;
	    socket_error(3);
	    return false;
	}
	char *p = buf;
	while (n-- > 0) {
	    jp->put(*p);
	    if (*p == '\n') {
		jp->start_parser();
		try {
		    jp->next(gx_system::JsonParser::begin_object);
		    jp->next(gx_system::JsonParser::value_key); // "jsonrpc"
		    jp->next(gx_system::JsonParser::value_string); // "2.0"
		    jp->next(gx_system::JsonParser::value_key); // "method"
		    handle_notify(jp);
		} catch (gx_system::JsonException& e) {
		    cerr << "JsonException: " << e.what() << ": '" << jp->get_string() << "'" << endl;
		    assert(false);
		}
		if (n == 0) {
		    int avail = socket_get_available_bytes(socket);
		    if (avail == 0) {
			delete jp;
			return true;
		    } else if (avail < 0) {
			socket_error(4);
		    }
		}
		delete jp;
		jp = new gx_system::JsonStringParser;
	    }
	    p++;
	}
    }
}

const jsonrpc_method_def& GxMachineRemote::start_call(jsonrpc_method m) {
    const jsonrpc_method_def& md = jsonrpc_method_list[m];
    jw->begin_object();
    jw->write_kv("jsonrpc", "2.0");
    if (md.has_result) {
	jw->write_kv("id", "1");
    }
    jw->write_kv("method", md.name);
    jw->write_key("params");
    jw->begin_array();
    return md;
}

void GxMachineRemote::send() {
    jw->end_array();
    jw->end_object();
    *os << endl;
    if (os->fail()) {
	socket_error(5);
    }
    jw->reset();
}

void GxMachineRemote::report_rpc_error(gx_system::JsonStringParser *jp, const gx_system::JsonException& e, const char *method) {
    if (method) {
	cerr << "RPC Error in " << method << "(): ";
    } else {
	cerr << "RPC Error: ";
    }
    cerr << e.what() << ": '" << jp->get_string() << "'" << endl;
    assert(false);
}

bool GxMachineRemote::idle_notify_handler() {
    for (unsigned int i = 0; i < notify_list.size(); ++i) {
	gx_system::JsonStringParser *jp = notify_list[i];
	handle_notify(jp);
	delete jp;
    }
    notify_list.clear();
    return false;
}

void GxMachineRemote::add_idle_handler() {
    if (!idle_conn.connected()) {
	idle_conn = Glib::signal_idle().connect(
	    sigc::mem_fun(this, &GxMachineRemote::idle_notify_handler));
    }
}

void GxMachineRemote::throw_error(gx_system::JsonStringParser *jp) {
    jp->next(gx_system::JsonParser::begin_object);
    int code = 0;
    Glib::ustring message;
    while (jp->peek() != gx_system::JsonParser::end_object) {
	jp->next(gx_system::JsonParser::value_key);
	if (jp->current_value() == "code") {
	    jp->next(gx_system::JsonParser::value_number);
	    code = jp->current_value_int();
	} else if (jp->current_value() == "message") {
	    jp->next(gx_system::JsonParser::value_string);
	    message = jp->current_value();
	}
    }
    jp->next(gx_system::JsonParser::end_object);
    cerr << jp->get_string() << std::flush;
    throw gx_system::JsonException(
	Glib::ustring::compose("RPC error %1 : %2", code, message));
}

void GxMachineRemote::socket_error(int loc) {
    if (!socket->is_closed()) {
	socket->close();
    }
    gx_print_fatal("Network", Glib::ustring::compose("Server has closed connection (%1)", loc));
}

gx_system::JsonStringParser *GxMachineRemote::receive() {
    char buf[10000];
    bool error = false;
    gx_system::JsonStringParser *jp_ret = 0;
    gx_system::JsonStringParser *jp = new gx_system::JsonStringParser;
    try {
	while (true) {
	    int n;
	    try {
		n = socket->receive(buf, sizeof(buf));
	    } catch(Glib::Error& e) {
		cerr << "Glib receive error: " << e.what() << endl;
		return 0;
	    }
	    if (n <= 0) {
		socket_error(6);
		return 0;
	    }
	    char *p = buf;
	    while (n-- > 0) {
		jp->put(*p);
		if (*p == '\n') {
		    jp->start_parser();
		    jp->next(gx_system::JsonParser::begin_object);
		    jp->next(gx_system::JsonParser::value_key); // "jsonrpc"
		    jp->next(gx_system::JsonParser::value_string); // "2.0"
		    jp->next(gx_system::JsonParser::value_key);
		    if (jp->current_value() == "id") {
			jp->next(); // id or null
			jp->next(gx_system::JsonParser::value_key);
			if (jp->current_value() == "error") {
			    error = true;
			}
			assert(jp_ret == 0);
			jp_ret = jp;
		    } else {
			assert(jp->current_value() == "method");
			notify_list.push_back(jp);
			add_idle_handler();
		    }
		    if (n == 0 && jp_ret) {
			if (error) {
			    throw_error(jp_ret);
			}
			return jp_ret;
		    }
		    jp = new gx_system::JsonStringParser;
		}
		p++;
	    }
	}
    } catch (const gx_system::JsonException& e) {
	report_rpc_error(jp, e);
	delete jp;
	return 0;
    }
}

bool GxMachineRemote::get_bool(gx_system::JsonStringParser *jp) {
    jp->next(gx_system::JsonParser::value_number);
    return bool(jp->current_value_int());
}

void GxMachineRemote::set_state(GxEngineState state) {
    START_NOTIFY(setstate);
    jw->write(engine_state_to_string(state));
    SEND();
}

GxEngineState GxMachineRemote::get_state() {
    START_CALL(getstate);
    START_RECEIVE(gx_engine::kEngineOff);
    jp->next(gx_system::JsonParser::value_string);
    return string_to_engine_state(jp->current_value());
    END_RECEIVE(return gx_engine::kEngineOff);
}


/*
** LadspaLoader
*/

void GxMachineRemote::load_ladspalist(std::vector<std::string>& old_not_found, ladspa::LadspaPluginList& pluginlist) {
    START_CALL(load_ladspalist);
    START_RECEIVE();
    jp->next(gx_system::JsonParser::begin_array);
    while (jp->peek() != gx_system::JsonParser::end_array) {
	jp->next(gx_system::JsonParser::value_number);
	old_not_found.push_back(jp->current_value());
    }
    jp->next(gx_system::JsonParser::end_array);
    pluginlist.readJSON(*jp);
    END_RECEIVE();
}

void GxMachineRemote::save_ladspalist(ladspa::LadspaPluginList& pluginlist) {
    START_NOTIFY(save_ladspalist);
    pluginlist.writeJSON(*jw);
    SEND();
}

void GxMachineRemote::update_plugins(gx_system::JsonParser *jp) {
    // deleted parameters
    jp->next(gx_system::JsonParser::begin_array);
    while (jp->peek() != gx_system::JsonParser::end_array) {
	jp->next(gx_system::JsonParser::value_string);
	pmap.unregister(jp->current_value());
    }
    jp->next(gx_system::JsonParser::end_array);
    // inserted parameters
    jp->next(gx_system::JsonParser::begin_array);
    pmap.set_replace_mode(true);
    while (jp->peek() != gx_system::JsonParser::end_array) {
	pmap.readJSON_one(*jp);
    }
    pmap.set_replace_mode(false);
    jp->next(gx_system::JsonParser::end_array);
    // updated plugins
    jp->next(gx_system::JsonParser::begin_array);
    while (jp->peek() != gx_system::JsonParser::end_array) {
	jp->next(gx_system::JsonParser::begin_array);
	jp->next(gx_system::JsonParser::value_number);
	PluginChange::pc c = static_cast<PluginChange::pc>(jp->current_value_int());
	if (c == PluginChange::remove) {
	    jp->next(gx_system::JsonParser::value_string);
	    Plugin *p = pluginlist.lookup_plugin(jp->current_value());
	    plugin_changed(p, c);
	    pluginlist.delete_module(p);
	} else {
	    Plugin *p = new Plugin(*jp, pmap);
	    if (c == PluginChange::add) {
		pluginlist.insert_plugin(p);
	    } else {
		pluginlist.update_plugin(p);
	    }
	    plugin_changed(p, c);
	}
	jp->next(gx_system::JsonParser::end_array);
    }
    jp->next(gx_system::JsonParser::end_array);
    plugin_changed(0, PluginChange::update);
}

void GxMachineRemote::commit_ladspa_changes() {
    START_CALL(ladspaloader_update_plugins);
    START_RECEIVE();
    jp->next(gx_system::JsonParser::begin_array);
    update_plugins(jp);
    jp->next(gx_system::JsonParser::end_array);
    END_RECEIVE();
}

sigc::signal<void,Plugin*,PluginChange::pc>& GxMachineRemote::signal_plugin_changed() {
    return plugin_changed;
}


/*
** PluginList
*/

Plugin *GxMachineRemote::pluginlist_lookup_plugin(const std::string& id) const {
    return pluginlist.lookup_plugin(id);
}

void GxMachineRemote::pluginlist_append_rack(UiBuilderBase& ui) {
    pluginlist.append_rack(ui);
}

/*
// unused now, 
static const char *next_char_pointer(gx_system::JsonParser *jp) {
    switch (jp->next()) {
    case gx_system::JsonParser::value_string: return jp->current_value().c_str();
    case gx_system::JsonParser::value_null: return 0;
    default: jp->throw_unexpected(gx_system::JsonParser::value_string); return 0;
    }
}
*/

static const std::string next_string(gx_system::JsonParser *jp) {
    if (jp->next() != gx_system::JsonParser::value_string) {
	jp->throw_unexpected(gx_system::JsonParser::value_string);
    }
    return jp->current_value();
}

int GxMachineRemote::load_remote_ui(const UiBuilder& builder, int form) {
    START_CALL(plugin_load_ui);
    jw->write(builder.plugin->id);
    jw->write(form);
    START_RECEIVE(-1);
    jp->next(gx_system::JsonParser::begin_array);
    while (jp->peek() != gx_system::JsonParser::end_array) {
	jp->next(gx_system::JsonParser::begin_array);
	jp->next(gx_system::JsonParser::value_string);
	if (jp->current_value() == "openTabBox") {
	    builder.openTabBox(next_string(jp).c_str());
	} else if (jp->current_value() == "openVerticalBox") {
	    builder.openVerticalBox(next_string(jp).c_str());
	} else if (jp->current_value() == "openVerticalBox1") {
	    builder.openVerticalBox1(next_string(jp).c_str());
	} else if (jp->current_value() == "openVerticalBox2") {
	    builder.openVerticalBox2(next_string(jp).c_str());
	} else if (jp->current_value() == "openHorizontalhideBox") {
	    builder.openHorizontalhideBox(next_string(jp).c_str());
	} else if (jp->current_value() == "openHorizontalTableBox") {
	    builder.openHorizontalTableBox(next_string(jp).c_str());
	} else if (jp->current_value() == "openFrameBox") {
	    builder.openFrameBox(next_string(jp).c_str());
	} else if (jp->current_value() == "openFlipLabelBox") {
	    builder.openFlipLabelBox(next_string(jp).c_str());
	} else if (jp->current_value() == "openpaintampBox") {
	    builder.openpaintampBox(next_string(jp).c_str());
	} else if (jp->current_value() == "openHorizontalBox") {
	    builder.openHorizontalBox(next_string(jp).c_str());
	} else if (jp->current_value() == "insertSpacer") {
	    builder.insertSpacer();
	} else if (jp->current_value() == "set_next_flags") {
	    jp->next(gx_system::JsonParser::value_number);
	    builder.set_next_flags(jp->current_value_int());
	} else if (jp->current_value() == "create_mid_rackknob") {
	    std::string id = next_string(jp);
	    std::string lab = next_string(jp);
	    builder.create_mid_rackknob(id.c_str(), lab.c_str());
	} else if (jp->current_value() == "create_small_rackknob") {
	    std::string id = next_string(jp);
	    std::string lab = next_string(jp);
	    builder.create_small_rackknob(id.c_str(), lab.c_str());
	} else if (jp->current_value() == "create_small_rackknobr") {
	    std::string id = next_string(jp);
	    std::string lab = next_string(jp);
	    builder.create_small_rackknobr(id.c_str(), lab.c_str());
	} else if (jp->current_value() == "create_big_rackknob") {
	    std::string id = next_string(jp);
	    std::string lab = next_string(jp);
	    builder.create_big_rackknob(id.c_str(), lab.c_str());
	} else if (jp->current_value() == "create_master_slider") {
	    std::string id = next_string(jp);
	    std::string lab = next_string(jp);
	    builder.create_master_slider(id.c_str(), lab.c_str());
	} else if (jp->current_value() == "create_feedback_slider") {
	    std::string id = next_string(jp);
	    std::string lab = next_string(jp);
	    builder.create_feedback_slider(id.c_str(), lab.c_str());
	} else if (jp->current_value() == "create_selector_no_caption") {
	    std::string id = next_string(jp);
	    builder.create_selector_no_caption(id.c_str());
	} else if (jp->current_value() == "create_selector") {
	    std::string id = next_string(jp);
	    std::string lab = next_string(jp);
	    builder.create_selector(id.c_str(), lab.c_str());
	} else if (jp->current_value() == "create_simple_meter") {
		std::string id = next_string(jp);
        builder.create_simple_meter(id.c_str());
	} else if (jp->current_value() == "create_simple_c_meter") {
        std::string id = next_string(jp);
	    std::string idl = next_string(jp);
	    std::string lab = next_string(jp);
	    builder.create_simple_c_meter(id.c_str(),idl.c_str(), lab.c_str());
	} else if (jp->current_value() == "create_spin_value") {
	    std::string id = next_string(jp);
	    std::string lab = next_string(jp);
	    builder.create_spin_value(id.c_str(), lab.c_str());
	} else if (jp->current_value() == "create_switch_no_caption") {
	    std::string sw_type = next_string(jp);
	    std::string id = next_string(jp);
	    builder.create_switch_no_caption(sw_type.c_str(), id.c_str());
	} else if (jp->current_value() == "create_feedback_switch") {
	    std::string sw_type = next_string(jp);
	    std::string id = next_string(jp);
	    builder.create_feedback_switch(sw_type.c_str(), id.c_str());
	} else if (jp->current_value() == "create_fload_switch") {
	    std::string sw_type = next_string(jp);
	    std::string id = next_string(jp);
	    std::string idf = next_string(jp);
	    builder.create_fload_switch(sw_type.c_str(), id.c_str(), idf.c_str());
	} else if (jp->current_value() == "create_switch") {
	    std::string sw_type = next_string(jp);
	    std::string id = next_string(jp);
	    std::string lab = next_string(jp);
	    builder.create_switch(sw_type.c_str(), id.c_str(), lab.c_str());
	} else if (jp->current_value() == "create_wheel") {
	    std::string id = next_string(jp);
	    std::string lab = next_string(jp);
	    builder.create_wheel(id.c_str(), lab.c_str());
	} else if (jp->current_value() == "create_port_display") {
	    std::string id = next_string(jp);
	    std::string lab = next_string(jp);
	    builder.create_port_display(id.c_str(), lab.c_str());
	} else if (jp->current_value() == "create_p_display") {
        std::string id = next_string(jp);
	    std::string idl = next_string(jp);
	    std::string idh = next_string(jp);
	    builder.create_p_display(id.c_str(),idl.c_str(),idh.c_str());
	} else if (jp->current_value() == "create_simple_spin_value") {
		std::string id = next_string(jp);
	    builder.create_simple_spin_value(id.c_str());
	} else if (jp->current_value() == "create_eq_rackslider_no_caption") {
		std::string id = next_string(jp);
	    builder.create_eq_rackslider_no_caption(id.c_str());
	} else if (jp->current_value() == "closeBox") {
	    builder.closeBox();
	} else if (jp->current_value() == "load_glade") {
	    jp->next(gx_system::JsonParser::value_string);
	    builder.load_glade(jp->current_value().c_str());
	} else {
	    cerr << "unknown uiBuilder function " << jp->current_value() << endl;
	    jp->skip_object();
	}
	jp->next(gx_system::JsonParser::end_array);
    }
    jp->next(gx_system::JsonParser::end_array);
    return 0;
    END_RECEIVE(return -1);
}

bool GxMachineRemote::load_unit(gx_gui::UiBuilderImpl& builder, PluginDef* pdef) {
#ifndef GUITARIX_AS_PLUGIN
    pdef->load_ui = [](const UiBuilder& builder, int form) {
                        GxMachineRemote *m = dynamic_cast<GxMachineRemote*>(
                            &static_cast<const gx_gui::UiBuilderImpl*>(
                                &builder)->plugin_dict.get_machine());
                        return m->load_remote_ui(builder, form);
                    };
    return builder.load_unit(pdef);
#else
    return false;
#endif
}


/*
** Oscilloscope
*/

void GxMachineRemote::set_oscilloscope_mul_buffer(int a) {
    START_NOTIFY(set_oscilloscope_mul_buffer);
    jw->write(a);
    SEND();
}

int GxMachineRemote::get_oscilloscope_mul_buffer() {
    START_CALL(get_oscilloscope_mul_buffer);
    START_RECEIVE(1);
    return get_bool(jp);
    END_RECEIVE(return 1);
}

float GxMachineRemote::get_tuner_freq() {
    START_CALL(get_tuner_freq);
    START_RECEIVE(0);
    jp->next(gx_system::JsonParser::value_number);
    return jp->current_value_float();
    END_RECEIVE(return 0);
}

float GxMachineRemote::get_tuner_note() {
    START_CALL(get_tuner_note);
    START_RECEIVE(0);
    jp->next(gx_system::JsonParser::value_number);
    return jp->current_value_float();
    END_RECEIVE(return 0);
}

gx_system::CmdlineOptions& GxMachineRemote::get_options() const {
    return options;
}

void GxMachineRemote::start_socket(sigc::slot<void> quit_mainloop, const Glib::ustring& host, int port) {
    assert(false);
}

void GxMachineRemote::stop_socket() {
}

sigc::signal<void,const Glib::ustring&,const Glib::ustring&>& GxMachineRemote::tuner_switcher_signal_display() {
    return tuner_switcher_display;
}

sigc::signal<void,TunerSwitcher::SwitcherState>& GxMachineRemote::tuner_switcher_signal_set_state() {
    return tuner_switcher_set_state;
}

sigc::signal<void, bool>& GxMachineRemote::tuner_switcher_signal_selection_done() {
    return tuner_switcher_selection_done;
}

sigc::signal<void,GxEngineState>& GxMachineRemote::signal_state_change() {
    return engine_state_change;
}

void GxMachineRemote::tuner_used_for_display(bool on) {
    START_NOTIFY(tuner_used_for_display);
    jw->write(on);
    SEND();
}

void GxMachineRemote::tuner_used_by_midi(bool on) {
    if ((on && get_parameter("ui.racktuner").getBool().get_value()) || !on) {
        START_NOTIFY(tuner_used_by_midi);
        jw->write(on);
        SEND();
    }
}

void GxMachineRemote::tuner_switch(bool on) {
    if (!on && get_parameter("system.midiout_tuner").getBool().get_value()) {
        tuner_used_by_midi(false);
    } else if (on && get_parameter("system.midiout_tuner").getBool().get_value()) {
        tuner_used_by_midi(true);
    }
}

const std::vector<std::string>& GxMachineRemote::get_rack_unit_order(PluginType type) {
    bool stereo = (type == PLUGIN_TYPE_STEREO);
    std::vector<std::string>& l = (stereo ? rack_units.stereo : rack_units.mono);
    l.clear();
    START_CALL(get_rack_unit_order);
    jw->write(stereo);
    START_RECEIVE(l);
    try {
	jp->next(gx_system::JsonParser::begin_array);
	while (jp->peek() != gx_system::JsonParser::end_array) {
	    jp->next(gx_system::JsonParser::value_string);
	    l.push_back(jp->current_value());
	}
	jp->next(gx_system::JsonParser::end_array);
    } catch (gx_system::JsonException& e) {
	cerr << "JsonException: " << e.what() << ": '" << jp->get_string() << "'" << endl;
	assert(false);
    }
    return l;
    END_RECEIVE(return l);
}

sigc::signal<void,bool>& GxMachineRemote::signal_rack_unit_order_changed() {
    return rack_units.rack_unit_order_changed;
}

void GxMachineRemote::remove_rack_unit(const std::string& unit, PluginType type) {
    START_NOTIFY(remove_rack_unit);
    jw->write(unit);
    jw->write(type == PLUGIN_TYPE_STEREO);
    SEND();
    rack_units.rack_unit_order_changed(type == PLUGIN_TYPE_STEREO);
}

void GxMachineRemote::insert_rack_unit(const std::string& unit, const std::string& before, PluginType type) {
    START_NOTIFY(insert_rack_unit);
    jw->write(unit);
    jw->write(before);
    jw->write(type == PLUGIN_TYPE_STEREO);
    SEND();
    rack_units.rack_unit_order_changed(type == PLUGIN_TYPE_STEREO);
}

// tuner_switcher
bool GxMachineRemote::get_tuner_switcher_active() {
    START_CALL(get_tuner_switcher_active);
    START_RECEIVE(false);
    return get_bool(jp);
    END_RECEIVE(return false);
}

void GxMachineRemote::tuner_switcher_activate(bool v) {
    START_NOTIFY(tuner_switcher_activate);
    jw->write(v);
    SEND();
}

void GxMachineRemote::tuner_switcher_deactivate() {
    START_NOTIFY(tuner_switcher_deactivate);
    SEND();
}

void GxMachineRemote::tuner_switcher_toggle(bool v) {
    START_NOTIFY(tuner_switcher_toggle);
    jw->write(v);
    SEND();
}

void GxMachineRemote::on_tuner_freq_changed() {
#ifdef USE_MIDI_CC_OUT
    if (get_parameter("system.midiout_tuner").getBool().get_value()) {
        float fnote = get_tuner_note();
        if (fnote < 999.0) {
            int note = static_cast<int>(round(fnote));
            uint8_t midi_note = static_cast<uint8_t>(note+69);
            uint8_t vel = static_cast<uint8_t>(((fnote - note) * 127) +63);

            msend_midi_cc(0x90, midi_note,vel, 3);
        } else {
            msend_midi_cc(0xB0, 123, 0, 3);
        }
    }
#endif
}

// preset

void GxMachineRemote::next_preset_switch() {
    gx_system::PresetFileGui *f= get_current_bank_file();
    int idx = f->get_index(get_current_name());
    if (idx+1 < f->size()) load_preset(f, f->get_name(idx+1));
    else load_preset(f, f->get_name(0));
}

void GxMachineRemote::previus_preset_switch() {
    gx_system::PresetFileGui *f= get_current_bank_file();
    int idx = f->get_index(get_current_name());
    if (idx-1 > -1) load_preset(f, f->get_name(idx-1));
    else load_preset(f, f->get_name(f->size()-1));
}

void GxMachineRemote::process_next_preset_switch(bool s) {
    if(s) {
        Glib::signal_idle().connect_once(
          sigc::mem_fun(this, &GxMachineRemote::next_preset_switch));
        set_parameter_value("engine.next_preset",false);
    }
}

void GxMachineRemote::process_previus_preset_switch(bool s) {
    if(s) {
        Glib::signal_idle().connect_once(
          sigc::mem_fun(this, &GxMachineRemote::previus_preset_switch));
        set_parameter_value("engine.previus_preset",false);
    }
}


bool GxMachineRemote::setting_is_preset() {
    return (!get_current_bank().empty());
}

static const Glib::ustring empty_string;

const Glib::ustring& GxMachineRemote::get_current_bank() {
    return current_bank;
}

gx_system::PresetFileGui *GxMachineRemote::get_current_bank_file() {
    return get_bank_file(get_current_bank());
}

const Glib::ustring& GxMachineRemote::get_current_name() {
    return current_preset;
}

gx_system::PresetFileGui* GxMachineRemote::get_bank_file(const Glib::ustring& bank) const { //FIXME
    return banks.get_file(bank)->get_guiwrapper();
}

Glib::ustring GxMachineRemote::get_bank_name(int n) {
    return banks.get_name(n);
}

bool GxMachineRemote::msend_midi_cc(int cc, int pgn, int bgn, int num) {
	START_NOTIFY(sendcc);
    jw->write(cc);
    jw->write(pgn);
    jw->write(bgn);
    jw->write(num);
    SEND();
    return true;
}

void GxMachineRemote::load_preset(gx_system::PresetFileGui *pf, const Glib::ustring& name) {
    int n = get_bank_index(get_current_bank());
    START_NOTIFY(setpreset);
    jw->write(pf->get_name());
    jw->write(name);
    SEND();
#ifdef USE_MIDI_CC_OUT
    if (get_bank_index(pf->get_name()) != n) {
        msend_midi_cc(0xB0, 32, get_bank_index(pf->get_name()),3);
    }
    msend_midi_cc(0xC0, pf->get_index(name),0,2);
#endif
}

void GxMachineRemote::loadstate() {
    /* noop */
}

int GxMachineRemote::bank_size() {
    return banks.size();
}

int GxMachineRemote::get_bank_index(const Glib::ustring& bank) {
    return banks.get_index(bank);
}

void GxMachineRemote::create_default_scratch_preset() {
    START_NOTIFY(create_default_scratch_preset);
    SEND();
}

void GxMachineRemote::set_statefilename(const std::string& fn) {
    //FIXME move jack session handling inside machine
    /* noop */
}

void GxMachineRemote::save_to_state(bool preserve_preset) {
    //FIXME move jack session handling inside machine
    /* noop */
}

void GxMachineRemote::plugin_preset_list_load(const PluginDef *pdef, gx_preset::UnitPresetList &presetnames) {
    START_CALL(plugin_preset_list_load);
    jw->write(pdef->id);
    START_RECEIVE();
    jp->next(gx_system::JsonParser::begin_array);
    while (jp->peek() != gx_system::JsonParser::end_array) {
	jp->next(gx_system::JsonParser::begin_array);
	jp->next(gx_system::JsonParser::value_string);
	Glib::ustring name = jp->current_value();
	jp->next(gx_system::JsonParser::value_number);
	presetnames.push_back(gx_preset::PluginPresetEntry(name, jp->current_value_int()));
	jp->next(gx_system::JsonParser::end_array);
    }
    jp->next(gx_system::JsonParser::end_array);
    END_RECEIVE();
}

void GxMachineRemote::plugin_preset_list_set(const PluginDef *pdef, bool factory, const Glib::ustring& name) {
    START_NOTIFY(plugin_preset_list_set);
    jw->write(pdef->id);
    jw->write(factory);
    jw->write(name);
    SEND();
}

void GxMachineRemote::plugin_preset_list_sync_set(const PluginDef *pdef, bool factory, const Glib::ustring& name) {
    START_NOTIFY(plugin_preset_list_sync_set);
    jw->write(pdef->id);
    jw->write(factory);
    jw->write(name);
    SEND();
}

void GxMachineRemote::plugin_preset_list_set_on_idle(const PluginDef *pdef, bool factory, const Glib::ustring& name) {
    Glib::signal_idle().connect_once(
      sigc::bind(sigc::bind(sigc::bind(sigc::mem_fun(this, &GxMachineRemote::plugin_preset_list_sync_set),name),factory),pdef));
}

void GxMachineRemote::plugin_preset_list_save(const PluginDef *pdef, const Glib::ustring& name) {
    START_NOTIFY(plugin_preset_list_save);
    jw->write(pdef->id);
    jw->write(name);
    SEND();
}

void GxMachineRemote::plugin_preset_list_remove(const PluginDef *pdef, const Glib::ustring& name) {
    START_NOTIFY(plugin_preset_list_remove);
    jw->write(pdef->id);
    jw->write(name);
    SEND();
}

void GxMachineRemote::disable_autosave(bool v) {
    //FIXME: move inside machine
    /* noop */
}

void GxMachineRemote::disable_save_on_exit(bool v) {
    //FIXME: move inside machine
    /* noop */
}

sigc::signal<void>& GxMachineRemote::signal_selection_changed() {
    return selection_changed;
}

sigc::signal<void>& GxMachineRemote::signal_presetlist_changed() {
    return presetlist_changed;
}

gx_system::PresetFileGui *GxMachineRemote::bank_insert_uri(const Glib::ustring& uri, bool move, int position) {
    START_CALL(bank_insert_content);
    jw->write(uri);
    Glib::RefPtr<Gio::File> rem = Gio::File::create_for_uri(uri);
    fstream f(rem->get_path().c_str());
    stringstream s;
    s << f.rdbuf();
    jw->write(s.str());
    jw->write(position);
    START_RECEIVE(0);
    if (jp->peek() != gx_system::JsonParser::begin_object) {
	return 0;
    }
    gx_system::PresetFile *pf = new gx_system::PresetFile();
    pf->readJSON_remote(*jp);
    banks.insert(pf, position);
    return pf->get_guiwrapper();
    END_RECEIVE(return 0);
}

gx_system::PresetFileGui *GxMachineRemote::bank_insert_new(const Glib::ustring& newname) {
    START_CALL(bank_insert_new);
    jw->write(newname);
    START_RECEIVE(0);
    gx_system::PresetFile *pf = new gx_system::PresetFile();
    pf->readJSON_remote(*jp);
    banks.insert(pf);
    return pf->get_guiwrapper();
    END_RECEIVE(return 0);
}

bool GxMachineRemote::rename_bank(const Glib::ustring& oldname, Glib::ustring& newname) {
    START_CALL(rename_bank);
    jw->write(oldname);
    jw->write(newname);
    START_RECEIVE(false);
    jp->next(gx_system::JsonParser::begin_array);
    jp->next(gx_system::JsonParser::value_number);
    bool ret = jp->current_value_int();
    jp->next(gx_system::JsonParser::value_string);
    newname = jp->current_value();
    jp->next(gx_system::JsonParser::end_array);
    if (ret) {
	banks.get_file(oldname)->name = newname;
    }
    return ret;
    END_RECEIVE(return false);
}

bool GxMachineRemote::rename_preset(gx_system::PresetFileGui& pf, const Glib::ustring& oldname, const Glib::ustring& newname) {
    START_CALL(rename_preset);
    jw->write(pf.get_name());
    jw->write(oldname);
    jw->write(newname);
    START_RECEIVE(false);
    bool ret = get_bool(jp);
    if (ret) {
	int idx = pf.get_index(oldname);
	assert(idx >= 0);
	pf.entries[idx].name = newname;
    }
    return ret;
    END_RECEIVE(return false);
}

void GxMachineRemote::bank_reorder(const std::vector<Glib::ustring>& neworder) {
    START_NOTIFY(bank_reorder);
    for (std::vector<Glib::ustring>::const_iterator i = neworder.begin(); i != neworder.end(); ++i) {
	jw->write(*i);
    }
    SEND();
    banks.reorder(neworder);
}

void GxMachineRemote::reorder_preset(gx_system::PresetFileGui& pf, const std::vector<Glib::ustring>& neworder) {
    START_NOTIFY(reorder_preset);
    jw->write(pf.get_name());
    for (std::vector<Glib::ustring>::const_iterator i = neworder.begin(); i != neworder.end(); ++i) {
	jw->write(*i);
    }
    SEND();
    int n = 0;
    for (std::vector<Glib::ustring>::const_iterator i = neworder.begin(); i != neworder.end(); ++i) {
	pf.entries[n++].name = *i;
    }
    presetlist_changed();
}

bool GxMachineRemote::bank_check_reparse() {
    START_CALL(bank_check_reparse);
    START_RECEIVE(false);
    return get_bool(jp);
    END_RECEIVE(return false);
}

void GxMachineRemote::erase_preset(gx_system::PresetFileGui& pf, const Glib::ustring& name) {
    START_NOTIFY(erase_preset);
    jw->write(pf.get_name());
    jw->write(name);
    SEND();
    for (gx_system::PresetFile::iterator i = pf.begin(); i != pf.end(); ++i) {
	if (i->name == name) {
	    pf.entries.erase(i);
	    break;
	}
    }
}

void GxMachineRemote::bank_set_flag(gx_system::PresetFileGui *pf, int flag, bool v) {
    START_NOTIFY(bank_set_flag);
    jw->write(pf->get_name());
    jw->write(flag);
    jw->write(v);
    SEND();
    pf->set_flag(flag, v);
}

std::string GxMachineRemote::bank_get_filename(const Glib::ustring& bank) {
    // FIXME Gtk3: bank_get_filename is used in DnD bank operation, and the
    // first request is due to an internal window of the DnD mechanism but
    // there seems to be no way to detect this. Skip this first request so
    // that no contents is send for a DnD reorder operation. Recheck for Gtk3
    switch (bank_drag_get_counter) {
    case 0:
	bank_drag_get_counter++;
	return "";
    case 1:
	bank_drag_get_counter++;
	START_CALL(bank_get_contents);
	jw->write(bank);
	START_RECEIVE(empty_string);
	jp->next(gx_system::JsonParser::begin_array);
	jp->next(gx_system::JsonParser::value_string);
	Glib::RefPtr<Gio::File> target = Gio::File::create_for_path(
	    options.get_temp_filepath(
		Gio::File::create_for_path(jp->current_value())->get_basename()));
	jp->next(gx_system::JsonParser::value_string);
	Glib::RefPtr<Gio::FileOutputStream> s = target->replace(
	    "", false, Gio::FILE_CREATE_REPLACE_DESTINATION);
	s->write(jp->current_value());
	s->close();
	jp->next(gx_system::JsonParser::end_array);
	bank_drag_get_path = target->get_path();
	END_RECEIVE(return empty_string);
    }
    return bank_drag_get_path;
}

void GxMachineRemote::bank_drag_begin() {
    bank_drag_get_counter = 0;
    bank_drag_get_path.clear();
}

gx_system::PresetFileGui *GxMachineRemote::bank_get_file(const Glib::ustring& bank) const {
    return banks.get_file(bank)->get_guiwrapper();
}

bank_iterator GxMachineRemote::bank_begin() {
    return banks.begin();
}

bank_iterator GxMachineRemote::bank_end() {
    return banks.end();
}

void GxMachineRemote::pf_append(gx_system::PresetFileGui& pf, const Glib::ustring& src, gx_system::PresetFileGui& pftgt, const Glib::ustring& name) {
    START_NOTIFY(pf_append);
    jw->write(pf.get_name());
    jw->write(src);
    jw->write(pftgt.get_name());
    jw->write(name);
    SEND();
    pftgt.entries.push_back(gx_system::PresetFile::Position(name,0));
}

void GxMachineRemote::pf_insert_before(gx_system::PresetFileGui& pf, const Glib::ustring& src, gx_system::PresetFileGui& pftgt, const Glib::ustring& pos, const Glib::ustring& name) {
    START_NOTIFY(pf_insert_before);
    jw->write(pf.get_name());
    jw->write(src);
    jw->write(pftgt.get_name());
    jw->write(pos);
    jw->write(name);
    SEND();
    for (gx_system::PresetFile::iterator i = pftgt.begin(); i != pftgt.end(); ++i) {
	if (i->name == pos) {
	    pftgt.entries.insert(i, gx_system::PresetFile::Position(name, 0));
	    break;
	}
    }
}

void GxMachineRemote::pf_insert_after(gx_system::PresetFileGui& pf, const Glib::ustring& src, gx_system::PresetFileGui& pftgt, const Glib::ustring& pos, const Glib::ustring& name) {
    START_NOTIFY(pf_insert_after);
    jw->write(pf.get_name());
    jw->write(src);
    jw->write(pftgt.get_name());
    jw->write(pos);
    jw->write(name);
    SEND();
    for (gx_system::PresetFile::iterator i = pftgt.begin(); i != pftgt.end(); ++i) {
	if (i->name == pos) {
	    pftgt.entries.insert(++i, gx_system::PresetFile::Position(name, 0));
	    break;
	}
    }
}

bool GxMachineRemote::convert_preset(gx_system::PresetFileGui& pf) {
    START_CALL(convert_preset);
    jw->write(pf.get_name());
    START_RECEIVE(false);
    bool ret = get_bool(jp);
    if (ret) {
	pf.set_flag(gx_system::PRESET_FLAG_VERSIONDIFF, false);
    }
    return ret;
    END_RECEIVE(return false);
}

bool GxMachineRemote::bank_remove(const Glib::ustring& bank) {
    gx_system::PresetFile *f = banks.get_file(bank);
    START_CALL(bank_remove);
    jw->write(bank);
    START_RECEIVE(false);
    bool ret = get_bool(jp);
    if (ret) {
	banks.banklist.remove(f);
	delete f;
    }
    return ret;
    END_RECEIVE(return false);
}

void GxMachineRemote::bank_save() {
    START_NOTIFY(bank_save);
    SEND();
}

void GxMachineRemote::pf_save(gx_system::PresetFileGui& pf, const Glib::ustring& name) {
    START_NOTIFY(pf_save);
    jw->write(pf.get_name());
    jw->write(name);
    SEND();
}


// jack
gx_jack::GxJack *GxMachineRemote::get_jack() {
    return 0;
}

void GxMachineRemote::set_jack_insert(bool v) {
    START_NOTIFY(set_jack_insert);
    jw->write(v);
    SEND();
}

// pmap
Parameter& GxMachineRemote::get_parameter(const char *p) {
    return pmap[p];
}

Parameter& GxMachineRemote::get_parameter(const std::string& id) {
    return pmap[id];
}

// special case for DrumSequencer: register parameter for midi cc connection
void GxMachineRemote::insert_param(Glib::ustring group, Glib::ustring name) {
    Glib::ustring id = group + "." + name;
    Glib::ustring tb = "switch to preset " + name;
    START_NOTIFY(insert_param);
    jw->write(id);
    jw->write(tb);
    SEND();
    if (!pmap.hasId(id)) {
        if (!gx_engine::get_group_table().group_exist(group))
            gx_engine::get_group_table().insert(group,"Drumsequencer");
        BoolParameter& sp = pmap.reg_par(
          id, tb, (bool*)0, false, false)->getBool();
        sp.setSavable(false);
    }
    if (pmap.hasId(id))
        pmap[id].signal_changed_bool().connect(sigc::hide(
          sigc::bind(sigc::bind(sigc::bind(sigc::mem_fun(this, &GxMachineRemote::plugin_preset_list_set_on_idle), name), false),pluginlist_lookup_plugin("seq")->get_pdef())));
}

void GxMachineRemote::set_init_values() {
    for (ParamMap::iterator i = pmap.begin(); i != pmap.end(); ++i) {
	Parameter *p = i->second;
	if (p->isFloat()) {
	    FloatParameter& pf = p->getFloat();
	    pf.signal_changed()(pf.get_value());
	} else if (p->isInt()) {
	    IntParameter& pi = p->getInt();
	    pi.signal_changed()(pi.get_value());
	} else if (p->isBool()) {
	    BoolParameter& pb = p->getBool();
	    pb.signal_changed()(pb.get_value());
	} else if (p->isString()) {
	    StringParameter& ps = p->getString();
	    ps.signal_changed()(ps.get_value());
	} else if (p->isFile()) {
	    FileParameter& fp = p->getFile();
	    fp.signal_changed()();
	} else if (dynamic_cast<JConvParameter*>(i->second) != 0) {
	    JConvParameter* pj = dynamic_cast<JConvParameter*>(i->second);
	    pj->signal_changed()(&pj->get_value());
	} else if (dynamic_cast<SeqParameter*>(i->second) != 0) {
	    SeqParameter* pj = dynamic_cast<SeqParameter*>(i->second);
	    pj->signal_changed()(&pj->get_value());
	}
    }
    selection_changed(); // give preset window a chance to catch up on current preset
    Glib::signal_io().connect(
	sigc::mem_fun(this, &GxMachineRemote::socket_input_handler),
	socket->get_fd(), Glib::IO_IN);
    for (ParamMap::iterator i = pmap.begin(); i != pmap.end(); ++i) {
	if (i->second->isInt()) {
	    i->second->getInt().signal_changed().connect(
		sigc::hide(
		    sigc::bind(
			sigc::mem_fun(this, &GxMachineRemote::param_signal), i->second)));
	} else if (i->second->isBool()) {
	    i->second->getBool().signal_changed().connect(
		sigc::hide(
		    sigc::bind(
			sigc::mem_fun(this, &GxMachineRemote::param_signal), i->second)));
	} else if (i->second->isFloat()) {
	    i->second->getFloat().signal_changed().connect(
		sigc::hide(
		    sigc::bind(
			sigc::mem_fun(this, &GxMachineRemote::param_signal), i->second)));
	} else if (i->second->isString()) {
	    i->second->getString().signal_changed().connect(
		sigc::hide(
		    sigc::bind(
			sigc::mem_fun(this, &GxMachineRemote::param_signal), i->second)));
	} else if (dynamic_cast<JConvParameter*>(i->second) != 0) {
	    dynamic_cast<JConvParameter*>(i->second)->signal_changed().connect(
		sigc::hide(
		    sigc::bind(
			sigc::mem_fun(this, &GxMachineRemote::param_signal), i->second)));
	} else if (dynamic_cast<SeqParameter*>(i->second) != 0) {
	    dynamic_cast<SeqParameter*>(i->second)->signal_changed().connect(
		sigc::hide(
		    sigc::bind(
			sigc::mem_fun(this, &GxMachineRemote::param_signal), i->second)));
	}
    }
}

bool GxMachineRemote::update_parameter() {
    START_NOTIFY(get_updates);
    for (output_listen_map::const_iterator i = update_map.cbegin(); i != update_map.cend(); ++i) {
	jw->write(i->first);
    }
    SEND();
    return true;
}

bool GxMachineRemote::parameter_hasId(const char *p) {
    return pmap.hasId(p);
}

bool GxMachineRemote::parameter_hasId(const std::string& id) {
    return pmap.hasId(id);
}

void GxMachineRemote::reset_unit(const PluginDef *pdef) const {
    pmap.reset_unit(pdef);
}

bool GxMachineRemote::parameter_unit_has_std_values(const PluginDef *pdef) const {
    return pmap.unit_has_std_values(pdef);
}

void GxMachineRemote::set_parameter_value(const std::string& id, int value) {
#ifdef USE_MIDI_CC_OUT
    if (options.system_midiout) {
        const gx_engine::MidiController *pctrl;
        IntParameter& p = get_parameter(id).getInt();
        if (p.get_value() != value) {
            int nctl = midi_param2controller(p, &pctrl);
            if (nctl > -1 && nctl < 128) {
                int state = int(((float(value) - p.getLowerAsFloat()) /
                    (p.getUpperAsFloat() - p.getLowerAsFloat())) * 127.0);
                msend_midi_cc(0xB0, nctl, state, 3);
                if (pctrl->toggle_behaviour() != Parameter::toggle_type::OnOff) {
                    midi_set_last_controller_value(nctl, state);
                } else {
                     midi_set_last_controller_value(nctl, p.get_value()*127);
                }
            }
        }
    }
#endif
    pmap[id].getInt().set(value);
}

void GxMachineRemote::set_parameter_value(const std::string& id, bool value) {
#ifdef USE_MIDI_CC_OUT
    if (options.system_midiout) {
        const gx_engine::MidiController *pctrl;
        BoolParameter& p = get_parameter(id).getBool();
        if (p.get_value() != value) {
            int nctl = midi_param2controller(p, &pctrl);
            if (nctl > -1 && nctl < 128) {
                int state = int(value * 127);
                msend_midi_cc(0xB0, nctl,state, 3);
                if (pctrl->toggle_behaviour() != Parameter::toggle_type::OnOff) {
                    midi_set_last_controller_value(nctl, state);
                } else {
                     midi_set_last_controller_value(nctl, p.get_value()*127);
                }
            }
        }
    }
#endif
    pmap[id].getBool().set(value);
}

void GxMachineRemote::set_parameter_value(const std::string& id, float value) {
#ifdef USE_MIDI_CC_OUT
    if (options.system_midiout) {
        const gx_engine::MidiController *pctrl;
        FloatParameter& p = get_parameter(id).getFloat();
        if ( std::fabs(p.get_value() - value) > 0.00001) {
            int nctl = midi_param2controller(p, &pctrl);
            if (nctl > -1 && nctl < 128) {
                int state = int(((float(value) - p.getLowerAsFloat()) /
                    (p.getUpperAsFloat() - p.getLowerAsFloat())) * 127.0);
                msend_midi_cc(0xB0, nctl, state, 3);
               // if (pctrl->toggle_behaviour() != Parameter::toggle_type::OnOff) {
               //     midi_set_last_controller_value(nctl, state);
               // } else {
               //      midi_set_last_controller_value(nctl, p.get_value()*127);
               // }
            }
        }
    }
#endif
    pmap[id].getFloat().set(value);
}

void GxMachineRemote::set_parameter_value(const std::string& id, const std::string& value) {
    if (!pmap[id].getString().set(value)) {
	return;
    }
    START_NOTIFY(set);
    jw->write(id);
    jw->write(value);
    SEND();
}

int GxMachineRemote::_get_parameter_value_int(const std::string& id) {
    START_CALL(get);
    jw->write(id);
    START_RECEIVE(0);
    jp->next(gx_system::JsonParser::begin_object);
    jp->next(gx_system::JsonParser::value_key);
    int v;
    switch (jp->next()) {
    case gx_system::JsonParser::value_string:
	v = pmap[id].getEnum().idx_from_id(jp->current_value());
	break;
    case gx_system::JsonParser::value_number:
	v = jp->current_value_int();
	break;
    default:
	assert(false);
	return 0;
    }
    return v;
    END_RECEIVE(return 0);
}

int GxMachineRemote::_get_parameter_value_bool(const std::string& id) {
    START_CALL(get);
    jw->write(id);
    START_RECEIVE(false);
    jp->next(gx_system::JsonParser::begin_object);
    jp->next(gx_system::JsonParser::value_key);
    jp->next(gx_system::JsonParser::value_number);
    return jp->current_value_int();
    END_RECEIVE(return false);
}

float GxMachineRemote::_get_parameter_value_float(const std::string& id) {
    START_CALL(get);
    jw->write(id);
    START_RECEIVE(0);
    jp->next(gx_system::JsonParser::begin_object);
    jp->next(gx_system::JsonParser::value_key);
    float v;
    switch (jp->next()) {
    case gx_system::JsonParser::value_string:
	v = dynamic_cast<FloatEnumParameter*>(&pmap[id])->idx_from_id(jp->current_value());
	break;
    case gx_system::JsonParser::value_number:
	v = jp->current_value_float();
	break;
    default:
	assert(false);
	return 0;
    }
    return v;
    END_RECEIVE(return 0);
}

std::string GxMachineRemote::_get_parameter_value_string(const std::string& id) {
    START_CALL(get);
    jw->write(id);
    START_RECEIVE(empty_string);
    jp->next(gx_system::JsonParser::begin_object);
    jp->next(gx_system::JsonParser::value_key);
    jp->next(gx_system::JsonParser::value_string);
    return jp->current_value();
    END_RECEIVE(return empty_string);
}

sigc::signal<void, int>& GxMachineRemote::_signal_parameter_value_int(const std::string& id) {
    return pmap[id].signal_changed_int();
}

sigc::signal<void, bool>& GxMachineRemote::_signal_parameter_value_bool(const std::string& id) {
    return pmap[id].signal_changed_bool();
}

sigc::signal<void, float>& GxMachineRemote::_signal_parameter_value_float(const std::string& id) {
    return pmap[id].signal_changed_float();
}

// MidiControllerList
bool GxMachineRemote::midi_get_config_mode(int *ctl) {
    START_CALL(midi_get_config_mode);
    START_RECEIVE(false);
    jp->next(gx_system::JsonParser::begin_array);
    bool ret = get_bool(jp);
    jp->next(gx_system::JsonParser::value_number);
    if (ret && ctl) {
	*ctl = jp->current_value_int();
    }
    jp->next(gx_system::JsonParser::end_array);
    return ret;
    END_RECEIVE(return false);
}

void GxMachineRemote::midi_set_config_mode(bool v, int ctl) {
    START_NOTIFY(midi_set_config_mode);
    jw->write(v);
    jw->write(ctl);
    SEND();
}

sigc::signal<void>& GxMachineRemote::signal_midi_changed() {
    return midi_changed;
}

sigc::signal<void, int, int>& GxMachineRemote::signal_midi_value_changed() {
    return midi_value_changed;
}

void GxMachineRemote::request_midi_value_update() {
    START_NOTIFY(request_midi_value_update);
    SEND();
}

int GxMachineRemote::midi_size() {
    return midi_controller_map.size();
}

midi_controller_list& GxMachineRemote::midi_get(int n) {
    return midi_controller_map[n];
}

void GxMachineRemote::midi_deleteParameter(Parameter& param) {
    START_NOTIFY(midi_deleteParameter);
    jw->write(param.id());
    SEND();
}

void GxMachineRemote::midi_set_current_control(int v) {
    START_NOTIFY(midi_set_current_control);
    jw->write(v);
    SEND();
}

void GxMachineRemote::midi_modifyCurrent(Parameter& param, float lower, float upper, bool toggle, int toggle_behaviour) {
    START_NOTIFY(midi_modifyCurrent);
    jw->write(param.id());
    jw->write(lower);
    jw->write(upper);
    jw->write(toggle);
    jw->write(toggle_behaviour);
    SEND();
}

int GxMachineRemote::midi_param2controller(Parameter& param, const MidiController** p) {
    return midi_controller_map.param2controller(param, p);
}

void GxMachineRemote::set_midi_channel(int s) {
    START_NOTIFY(set_midi_channel);
    jw->write(s);
    SEND();
}

int GxMachineRemote::midi_get_last_controller_value(int ctl) {
    START_CALL(get_last_midi_control_value);
    jw->write(ctl);
    START_RECEIVE(false);
    jp->next(gx_system::JsonParser::begin_object);
    jp->next(gx_system::JsonParser::value_number);
    return jp->current_value_int();
    END_RECEIVE(return false);
    
}

void GxMachineRemote::midi_set_last_controller_value(int ctl, int v) {
    START_NOTIFY(set_last_midi_control_value);
    jw->write(ctl);
    jw->write(v);
    SEND();
    
}

void GxMachineRemote::midi_feedback(int c, int v) {
#ifdef USE_MIDI_CC_OUT
    if (options.system_midiout) {
        // Don't send midi feedback for bpm / jack_transport and not on/off events
        if ( c !=22 && c != 24 && c < 128) {
            msend_midi_cc(0xB0, c,v, 3);
        }
    }
#endif
}

bool GxMachineRemote::get_midi_feedback() {
    START_CALL(get_midi_feedback);
    START_RECEIVE(false);
    jp->next(gx_system::JsonParser::begin_object);
    jp->next(gx_system::JsonParser::value_number);
    return jp->current_value_int();
    END_RECEIVE(return false);
    
}

void GxMachineRemote::set_midi_feedback(int v) {
    START_NOTIFY(set_midi_feedback);
    jw->write(v);
    SEND();
}

// Convolver

void GxMachineRemote::reload_impresp_list(const std::string& path) {
    START_NOTIFY(reload_impresp_list);
    jw->write(path);
    SEND();
}

void GxMachineRemote::load_impresp_dirs(std::vector<gx_system::FileName>& dirs) {
    START_CALL(load_impresp_dirs);
    START_RECEIVE();
    jp->next(gx_system::JsonParser::begin_array);
    while (jp->peek() != gx_system::JsonParser::end_array) {
	jp->next(gx_system::JsonParser::begin_array);
	jp->next(gx_system::JsonParser::value_string);
	std::string filename = jp->current_value();
	jp->next(gx_system::JsonParser::value_string);
	dirs.push_back(gx_system::FileName(filename, jp->current_value()));
	jp->next(gx_system::JsonParser::end_array);
    }
    jp->next(gx_system::JsonParser::end_array);
    END_RECEIVE();
}

bool GxMachineRemote::read_audio(const std::string& filename, unsigned int *audio_size, int *audio_chan,
				 int *audio_type, int *audio_form, int *audio_rate, float **buffer) {
    START_CALL(read_audio);
    jw->write(filename);
    START_RECEIVE(false);
    if (jp->peek() != gx_system::JsonParser::begin_array) {
	*audio_size = 0;
	*audio_chan = *audio_type = *audio_form = *audio_rate = 0;
	*buffer = 0;
        return false;
    }
    jp->next(gx_system::JsonParser::begin_array);
    jp->next(gx_system::JsonParser::value_number);
    *audio_size = jp->current_value_int();
    jp->next(gx_system::JsonParser::value_number);
    *audio_chan = jp->current_value_int();
    jp->next(gx_system::JsonParser::value_number);
    *audio_type = jp->current_value_int();
    jp->next(gx_system::JsonParser::value_number);
    *audio_form = jp->current_value_int();
    jp->next(gx_system::JsonParser::value_number);
    *audio_rate = jp->current_value_int();
    jp->next(gx_system::JsonParser::begin_array);
    *buffer = new float[*audio_size * *audio_chan];
    float *p = *buffer;
    while (jp->peek() != gx_system::JsonParser::end_array) {
	jp->next(gx_system::JsonParser::value_number);
	*p++ = jp->current_value_float();
    }
    jp->next(gx_system::JsonParser::end_array);
    jp->next(gx_system::JsonParser::end_array);
    return true;
    END_RECEIVE(return false);
}

} // namespace gx_engine
