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
#include "jsonrpc_methods.h"
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/ioctl.h>
#ifdef HAVE_BLUEZ
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#endif

void lock_rt_memory() {
    extern char __rt_text__start[], __rt_text__end[];
    extern char __rt_data__start[], __rt_data__end[];
    struct {
	char *start;
	long len;
    } regions[] = {
	{ __rt_text__start, __rt_text__end - __rt_text__start },
	{ __rt_data__start, __rt_data__end - __rt_data__start },
    };
    for (unsigned int i = 0; i < sizeof(regions)/sizeof(regions[0]); i++) {
	if (mlock(regions[i].start, regions[i].len) != 0) {
	    gx_print_error(
		"system init",
		boost::format(_("failed to lock memory: %1%")) % strerror(errno));
	}
    }
}


namespace gx_engine {

GxMachineBase::GxMachineBase()
    : impresp_list() {
}

GxMachineBase::~GxMachineBase() {
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
    pmap(engine.get_param()) {
    engine.set_jack(&jack);

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
    static const value_pair tuning_temperament[] = {{"12-ET"},{"19-ET"},{"24-ET"},{"31-ET"}, {0}};
    pmap.reg_non_midi_enum_par("racktuner.temperament", "Temperament", tuning_temperament, (int*)0, false, 0);
    pmap.reg_par_non_preset("racktuner.scale_lim", "Limit", 0, 3.0, 1.0, 10.0, 1.0);
    pmap.reg_par_non_preset("ui.tuner_reference_pitch", "?Tuner Reference Pitch", 0, 440, 427, 453, 0.1);
    //pmap.reg_par("racktuner.scale_lim", "Limit", &scale_lim, 3.0, 1.0, 10.0, 1.0); FIXME add in detail view?

    pmap.reg_par("ui.live_play_switcher", "Liveplay preset mode" , (bool*)0, false, false)->setSavable(false);
    pmap.reg_par("ui.racktuner", N_("Tuner on/off"), (bool*)0, false, false);
    pmap.reg_non_midi_par("system.show_tuner", (bool*)0, false);
    pmap.reg_non_midi_par("system.midi_in_preset", (bool*)0, false, false);
    pmap.reg_par_non_preset("ui.liveplay_brightness", "?liveplay_brightness", 0, 1.0, 0.5, 1.0, 0.01);
    pmap.reg_par_non_preset("ui.liveplay_background", "?liveplay_background", 0, 0.8, 0.0, 1.0, 0.01);
    BoolParameter& p = pmap.reg_par(
	"engine.mute", "Mute", 0, engine.get_state() == gx_engine::kEngineOff
	)->getBool();
    p.setSavable(false);
    engine.signal_state_change().connect(
	sigc::bind(sigc::ptr_fun(set_engine_mute), sigc::ref(p)));
    p.signal_changed().connect(
	sigc::bind(sigc::ptr_fun(on_engine_mute_changed), sigc::ref(engine)));
    pmap.reg_non_midi_par("ui.mp_s_h", (bool*)0, false);

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
    engine.midiaudiobuffer.signal_jack_load_change().connect(
	sigc::mem_fun(this, &GxMachine::on_jack_load_change));
    switch_bank = settings.get_current_bank();

}

GxMachine::~GxMachine() {
    stop_socket();
#ifndef NDEBUG
    if (options.dump_parameter) {
	pmap.dump("json");
    }
#endif
}

void GxMachine::on_jack_load_change() {
    gx_engine::MidiAudioBuffer::Load l = engine.midiaudiobuffer.jack_load_status();
    if (l == gx_engine::MidiAudioBuffer::load_low && !engine.midiaudiobuffer.get_midistat()) {
	l = gx_engine::MidiAudioBuffer::load_high;
    }
    jack_load_change(l);
}

void GxMachine::edge_toggle_tuner(bool v) {
    if (v) {
	tuner_switcher.toggle(engine.tuner.used_for_display());
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

sigc::signal<void,Plugin*,PluginChange::pc>& GxMachine::signal_plugin_changed() {
    return engine.signal_plugin_changed();
}

Plugin *GxMachine::pluginlist_lookup_plugin(const std::string& id) const {
    return engine.pluginlist.lookup_plugin(id);
}

bool GxMachine::load_unit(gx_gui::UiBuilderImpl& builder, PluginDef* pdef) {
    return builder.load_unit(pdef);
}

void GxMachine::pluginlist_append_rack(UiBuilderBase& ui) {
    engine.pluginlist.append_rack(ui);
}

float GxMachine::get_tuner_freq() {
    return engine.tuner.get_freq();
}

void GxMachine::set_oscilloscope_mul_buffer(int a) {
    engine.oscilloscope.set_mul_buffer(a, jack.get_jack_bs());
}

int GxMachine::get_oscilloscope_mul_buffer() {
    return engine.oscilloscope.get_mul_buffer();
}

const float *GxMachine::get_oscilloscope_buffer() {
    return engine.oscilloscope.get_buffer();
}

void GxMachine::clear_oscilloscope_buffer() {
    engine.oscilloscope.clear_buffer();
}

bool GxMachine::oscilloscope_plugin_box_visible() {
    return engine.oscilloscope.plugin.get_box_visible();
}

sigc::signal<void, int>& GxMachine::signal_oscilloscope_post_pre() {
    return pmap[engine.oscilloscope.plugin.id_effect_post_pre()].signal_changed_int();
}

sigc::signal<void, bool>& GxMachine::signal_oscilloscope_visible() {
    return pmap[engine.oscilloscope.plugin.id_box_visible()].signal_changed_bool();
}

sigc::signal<int, bool>& GxMachine::signal_oscilloscope_activation() {
    return engine.oscilloscope.activation;
}

sigc::signal<void, unsigned int>& GxMachine::signal_oscilloscope_size_change() {
    return engine.oscilloscope.size_change;
}

void GxMachine::maxlevel_get(int channels, float *values) {
    if (sock) {
	sock->update_maxlevel();
	for (int i = 0; i < channels; i++) {
	    values[i] = sock->get_maxlevel(i);
	}
    } else {
	for (int i = 0; i < channels; i++) {
	    values[i] = engine.maxlevel.get(i);
	}
    }
}

void GxMachine::get_oscilloscope_info(int& load, int& frames, bool& is_rt, jack_nframes_t& bsize) {
    load = static_cast<int>(round(jack.get_jcpu_load()));
    frames = jack.get_time_is()/100000;
    is_rt = jack.get_is_rt();
    bsize = jack.get_jack_bs();
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
    if (sock) {
	sock->send_rack_changed(type == PLUGIN_TYPE_STEREO, 0);
    }
}

void GxMachine::insert_rack_unit(const std::string& unit, const std::string& before, PluginType type) {
    settings.insert_rack_unit(unit, before, type == PLUGIN_TYPE_STEREO);
    if (sock) {
	sock->send_rack_changed(type == PLUGIN_TYPE_STEREO, 0);
    }
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

int GxMachine::get_bank_num(Glib::ustring num) {
    Glib::ustring array = "abcdefghijklmnopqrstuvwxyz" ;
    int i = 0;
	for(i=0;i<26;i++) {
		if(num.compare(array.substr(i,1))==0) break;
	}
	return bank_size() -i -1;
}

void GxMachine::msend_midi_cc(int cc, int pgn, int bgn, int num) {
	jack.send_midi_cc(cc, pgn, bgn, num);
}

void GxMachine::load_preset(gx_system::PresetFileGui *pf, const Glib::ustring& name) {
    int n = get_bank_index(get_current_bank());
    settings.load_preset(pf, name);
#ifdef USE_MIDI_CC_OUT
    if (get_bank_index(pf->get_name()) != n) {
        msend_midi_cc(0xB0, 32, get_bank_index(pf->get_name()),3);
    }
    msend_midi_cc(0xC0, pf->get_index(name),0,2);
#endif
}

void GxMachine::loadstate() {
    settings.loadstate();
	if (!options.get_setbank().empty()) {
		Glib::ustring sbank = options.get_setbank();
		int bl = get_bank_num(sbank.substr(0,1).lowercase());
		int pgm = max(0,atoi(sbank.substr(2,Glib::ustring::npos).raw().c_str())-1);
		switch_bank = settings.banks.get_name(bl);
		do_program_change(pgm);
    }
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

void GxMachine::plugin_preset_list_save(const PluginDef *pdef, const Glib::ustring& name) {
    settings.plugin_preset_list_save(pdef, name);
}

void GxMachine::plugin_preset_list_remove(const PluginDef *pdef, const Glib::ustring& name) {
    settings.plugin_preset_list_remove(pdef, name);
}

void GxMachine::disable_autosave(bool v) {
    settings.disable_autosave(v);
}

sigc::signal<void>& GxMachine::signal_selection_changed() {
    return settings.signal_selection_changed();
}

sigc::signal<void>& GxMachine::signal_presetlist_changed() {
    return settings.signal_presetlist_changed();
}

gx_system::PresetFileGui* GxMachine::bank_insert_uri(const Glib::ustring& uri, bool move) {
    gx_system::PresetFile *f = settings.bank_insert_uri(uri, move);
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
    pmap[id].getInt().set(value);
}

void GxMachine::set_parameter_value(const std::string& id, bool value) {
    pmap[id].getBool().set(value);
}

 //bool GxMachine::ui_f_update(const std::string& id, float value) {
 //    pmap[id].getFloat().set(value);
 //    return false;
 //}

void GxMachine::set_parameter_value(const std::string& id, float value) {
    // Glib::signal_timeout().connect(
    //     sigc::bind<const std::string&>(sigc::bind<float>(
     //    sigc::mem_fun (*this, &GxMachine::ui_f_update),value),id), 20);
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

void GxMachine::midi_modifyCurrent(Parameter& param, float lower, float upper, bool toggle) {
    engine.controller_map.modifyCurrent(param, lower, upper, toggle);
}

int GxMachine::midi_param2controller(Parameter& param, const MidiController** p) {
    return engine.controller_map.param2controller(param, p);
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
      oscilloscope_activation(),
      oscilloscope_size_change(),
      oscilloscope_buffer(0),
      oscilloscope_buffer_size(0),
      tuner_switcher_display(),
      tuner_switcher_set_state(),
      tuner_switcher_selection_done() {
    if (options.get_rpcaddress().compare(0, 3, "BT:") == 0) {
	create_bluetooth_socket(options.get_rpcaddress().substr(3));
    } else {
	create_tcp_socket();
    }
    socket->set_blocking(true);
    writebuf = new __gnu_cxx::stdio_filebuf<char>(socket->get_fd(), std::ios::out);
    os = new ostream(writebuf);
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
    jw->write("oscilloscope");
    jw->write("jack_load");
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
    setsockopt(socket->get_fd(), IPPROTO_TCP, TCP_NODELAY, &flag, sizeof(int));
    typedef std::vector< Glib::RefPtr<Gio::InetAddress> > adr_list;
    adr_list al;
    try {
	al = Gio::Resolver::get_default()->lookup_by_name(options.get_rpcaddress());
    } catch (Glib::Error e) {
	gx_print_fatal(_("Remote Connection"), e.what());
    }
    Glib::ustring msg;
    bool error = true;
    for (adr_list::iterator i = al.begin(); i != al.end(); ++i) {
	try {
	    socket->connect(Gio::InetSocketAddress::create(*i, options.get_rpcport()));
	    error = false;
	} catch (Gio::Error e) {
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
    } else if (method == "osc_activation") {
	jp->next(gx_system::JsonParser::value_number);
	oscilloscope_activation(jp->current_value_int());
    } else if (method == "osc_size_changed") {
	jp->next(gx_system::JsonParser::value_number);
	unsigned int sz = jp->current_value_int();
	if (oscilloscope_buffer_size != sz) {
	    delete oscilloscope_buffer;
	    oscilloscope_buffer = new float[sz];
	    oscilloscope_buffer_size = sz;
	}
	oscilloscope_size_change(sz);
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
    } else if (method == "jack_load_changed") {
	jp->next(gx_system::JsonParser::value_number);
	jack_load_change(static_cast<gx_engine::MidiAudioBuffer::Load>(jp->current_value_int()));
    } else if (method == "server_shutdown") {
	Gtk::Main::quit();
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
	} catch(Glib::Error e) {
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
		} catch (gx_system::JsonException e) {
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
	    } catch(Glib::Error e) {
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

static const char *next_char_pointer(gx_system::JsonParser *jp) {
    switch (jp->next()) {
    case gx_system::JsonParser::value_string: return jp->current_value().c_str();
    case gx_system::JsonParser::value_null: return 0;
    default: jp->throw_unexpected(gx_system::JsonParser::value_string); return 0;
    }
}

static const std::string next_string(gx_system::JsonParser *jp) {
    if (jp->next() != gx_system::JsonParser::value_string) {
	jp->throw_unexpected(gx_system::JsonParser::value_string);
    }
    return jp->current_value();
}

int GxMachineRemote::load_remote_ui_static (const UiBuilder& builder, int form) {
    GxMachineRemote *m = dynamic_cast<GxMachineRemote*>(&static_cast<const gx_gui::UiBuilderImpl*>(&builder)->main.get_machine());
    return m->load_remote_ui(builder, form);
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
	    builder.openTabBox(next_char_pointer(jp));
	} else if (jp->current_value() == "openVerticalBox") {
	    builder.openVerticalBox(next_char_pointer(jp));
	} else if (jp->current_value() == "openVerticalBox1") {
	    builder.openVerticalBox1(next_char_pointer(jp));
	} else if (jp->current_value() == "openVerticalBox2") {
	    builder.openVerticalBox2(next_char_pointer(jp));
	} else if (jp->current_value() == "openHorizontalhideBox") {
	    builder.openHorizontalhideBox(next_char_pointer(jp));
	} else if (jp->current_value() == "openHorizontalTableBox") {
	    builder.openHorizontalTableBox(next_char_pointer(jp));
	} else if (jp->current_value() == "openFrameBox") {
	    builder.openFrameBox(next_char_pointer(jp));
	} else if (jp->current_value() == "openFlipLabelBox") {
	    builder.openFlipLabelBox(next_char_pointer(jp));
	} else if (jp->current_value() == "openpaintampBox") {
	    builder.openpaintampBox(next_char_pointer(jp));
	} else if (jp->current_value() == "openHorizontalBox") {
	    builder.openHorizontalBox(next_char_pointer(jp));
	} else if (jp->current_value() == "insertSpacer") {
	    builder.insertSpacer();
	} else if (jp->current_value() == "set_next_flags") {
	    jp->next(gx_system::JsonParser::value_number);
	    builder.set_next_flags(jp->current_value_int());
	} else if (jp->current_value() == "create_small_rackknob") {
	    std::string id = next_string(jp);
	    builder.create_small_rackknob(id.c_str(), next_char_pointer(jp));
	} else if (jp->current_value() == "create_small_rackknobr") {
	    std::string id = next_string(jp);
	    builder.create_small_rackknobr(id.c_str(), next_char_pointer(jp));
	} else if (jp->current_value() == "create_master_slider") {
	    std::string id = next_string(jp);
	    builder.create_master_slider(id.c_str(), next_char_pointer(jp));
	} else if (jp->current_value() == "create_feedback_slider") {
	    std::string id = next_string(jp);
	    builder.create_feedback_slider(id.c_str(), next_char_pointer(jp));
	} else if (jp->current_value() == "create_selector_no_caption") {
	    builder.create_selector_no_caption(next_char_pointer(jp));
	} else if (jp->current_value() == "create_selector") {
	    std::string id = next_string(jp);
	    builder.create_selector(id.c_str(), next_char_pointer(jp));
	} else if (jp->current_value() == "create_simple_meter") {
        builder.create_simple_meter(next_char_pointer(jp));
	} else if (jp->current_value() == "create_simple_c_meter") {
        std::string id = next_char_pointer(jp);
	    std::string idl = next_char_pointer(jp);
	    builder.create_simple_c_meter(id.c_str(),idl.c_str(), next_char_pointer(jp));
	} else if (jp->current_value() == "create_spin_value") {
	    std::string id = next_char_pointer(jp);
	    builder.create_spin_value(id.c_str(), next_char_pointer(jp));
	} else if (jp->current_value() == "create_switch_no_caption") {
	    std::string sw_type = next_char_pointer(jp);
	    builder.create_switch_no_caption(sw_type.c_str(), next_char_pointer(jp));
	} else if (jp->current_value() == "create_feedback_switch") {
	    std::string sw_type = next_char_pointer(jp);
	    builder.create_feedback_switch(sw_type.c_str(), next_char_pointer(jp));
	} else if (jp->current_value() == "create_fload_switch") {
	    std::string sw_type = next_char_pointer(jp);
	    std::string id = next_char_pointer(jp);
	    std::string idf = next_char_pointer(jp);
	    builder.create_fload_switch(sw_type.c_str(), id.c_str(), idf.c_str());
	} else if (jp->current_value() == "create_switch") {
	    std::string sw_type = next_char_pointer(jp);
	    std::string id = next_char_pointer(jp);
	    builder.create_switch(sw_type.c_str(), id.c_str(), next_char_pointer(jp));
	} else if (jp->current_value() == "create_wheel") {
	    std::string id = next_char_pointer(jp);
	    builder.create_wheel(id.c_str(), next_char_pointer(jp));
	} else if (jp->current_value() == "create_port_display") {
	    std::string id = next_char_pointer(jp);
	    builder.create_port_display(id.c_str(), next_char_pointer(jp));
	} else if (jp->current_value() == "create_p_display") {
        std::string id = next_char_pointer(jp);
	    std::string idl = next_char_pointer(jp);
	    std::string idh = next_char_pointer(jp);
	    builder.create_p_display(id.c_str(),idl.c_str(),idh.c_str());
	} else if (jp->current_value() == "create_simple_spin_value") {
	    builder.create_simple_spin_value(next_char_pointer(jp));
	} else if (jp->current_value() == "create_eq_rackslider_no_caption") {
	    builder.create_eq_rackslider_no_caption(next_char_pointer(jp));
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
    pdef->load_ui = load_remote_ui_static;
    return builder.load_unit(pdef);
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

const float *GxMachineRemote::get_oscilloscope_buffer() {
    return oscilloscope_buffer;
}

void GxMachineRemote::clear_oscilloscope_buffer() {
    START_NOTIFY(clear_oscilloscope_buffer);
    SEND();
}

bool GxMachineRemote::oscilloscope_plugin_box_visible() {
    return pluginlist.lookup_plugin("oscilloscope")->get_box_visible();
}

sigc::signal<void, int>& GxMachineRemote::signal_oscilloscope_post_pre() {
    return pmap["oscilloscope.pp"].signal_changed_int();
}

sigc::signal<void, bool>& GxMachineRemote::signal_oscilloscope_visible() {
    return pmap["ui.oscilloscope"].signal_changed_bool();
}

sigc::signal<int, bool>& GxMachineRemote::signal_oscilloscope_activation() {
    return oscilloscope_activation;
}

sigc::signal<void, unsigned int>& GxMachineRemote::signal_oscilloscope_size_change() {
    return oscilloscope_size_change;
}

float GxMachineRemote::get_tuner_freq() {
    START_CALL(get_tuner_freq);
    START_RECEIVE(0);
    jp->next(gx_system::JsonParser::value_number);
    return jp->current_value_float();
    END_RECEIVE(return 0);
}

void GxMachineRemote::maxlevel_get(int channels, float *values) {
    START_CALL(get_max_output_level);
    jw->write(channels);
    START_RECEIVE();
    jp->next(gx_system::JsonParser::begin_array);
    for (int i = 0; i < channels; i++) {
	if (jp->peek() != gx_system::JsonParser::end_array) {
	    jp->next(gx_system::JsonParser::value_number);
	    values[i] = jp->current_value_float();
	} else {
	    values[i] = 0.0;
	}
    }
    END_RECEIVE();
}

void GxMachineRemote::get_oscilloscope_info(int& load, int& frames, bool& is_rt, jack_nframes_t& bsize) {
    START_CALL(get_oscilloscope_info);
    START_RECEIVE();
    jp->next(gx_system::JsonParser::begin_array);
    jp->next(gx_system::JsonParser::value_number);
    load = jp->current_value_int();
    jp->next(gx_system::JsonParser::value_number);
    frames = jp->current_value_int();
    jp->next(gx_system::JsonParser::value_number);
    is_rt = jp->current_value_int();
    jp->next(gx_system::JsonParser::value_number);
    bsize = jp->current_value_int();
    jp->next(gx_system::JsonParser::value_number);
    unsigned int sz = jp->current_value_int();
    if (oscilloscope_buffer_size != sz) {
	delete oscilloscope_buffer;
	oscilloscope_buffer = new float[sz];
	oscilloscope_buffer_size = sz;
	oscilloscope_size_change(sz);
    }
    jp->next(gx_system::JsonParser::begin_array);
    float *p = oscilloscope_buffer;
    while (jp->peek() != gx_system::JsonParser::end_array) {
	jp->next(gx_system::JsonParser::value_number);
	*p++ = jp->current_value_float();
    }
    jp->next(gx_system::JsonParser::end_array);
    jp->next(gx_system::JsonParser::end_array);
    END_RECEIVE();
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
    } catch (gx_system::JsonException e) {
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
}

void GxMachineRemote::insert_rack_unit(const std::string& unit, const std::string& before, PluginType type) {
    START_NOTIFY(insert_rack_unit);
    jw->write(unit);
    jw->write(before);
    jw->write(type == PLUGIN_TYPE_STEREO);
    SEND();
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

// preset
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

void GxMachineRemote::msend_midi_cc(int cc, int pgn, int bgn, int num) {
	START_NOTIFY(sendcc);
    jw->write(cc);
    jw->write(pgn);
    jw->write(bgn);
    jw->write(num);
    SEND();
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
    /* noop */
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

sigc::signal<void>& GxMachineRemote::signal_selection_changed() {
    return selection_changed;
}

sigc::signal<void>& GxMachineRemote::signal_presetlist_changed() {
    return presetlist_changed;
}

gx_system::PresetFileGui *GxMachineRemote::bank_insert_uri(const Glib::ustring& uri, bool move) {
    START_CALL(bank_insert_content);
    jw->write(uri);
    Glib::RefPtr<Gio::File> rem = Gio::File::create_for_uri(uri);
    fstream f(rem->get_path().c_str());
    stringstream s;
    s << f.rdbuf();
    jw->write(s.str());
    START_RECEIVE(0);
    if (jp->peek() != gx_system::JsonParser::begin_object) {
	return 0;
    }
    gx_system::PresetFile *pf = new gx_system::PresetFile();
    pf->readJSON_remote(*jp);
    banks.insert(pf);
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

// pmap
Parameter& GxMachineRemote::get_parameter(const char *p) {
    return pmap[p];
}

Parameter& GxMachineRemote::get_parameter(const std::string& id) {
    return pmap[id];
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
	}
    }
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
    pmap[id].getInt().set(value);
}

void GxMachineRemote::set_parameter_value(const std::string& id, bool value) {
    pmap[id].getBool().set(value);
}

void GxMachineRemote::set_parameter_value(const std::string& id, float value) {
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

void GxMachineRemote::midi_modifyCurrent(Parameter& param, float lower, float upper, bool toggle) {
    START_NOTIFY(midi_modifyCurrent);
    jw->write(param.id());
    jw->write(lower);
    jw->write(upper);
    jw->write(toggle);
    SEND();
}

int GxMachineRemote::midi_param2controller(Parameter& param, const MidiController** p) {
    return midi_controller_map.param2controller(param, p);
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
