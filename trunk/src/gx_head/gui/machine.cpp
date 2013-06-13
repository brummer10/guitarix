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

void lock_rt_memory() {
    extern char __rt_text__start[], __rt_text__end[];
    extern char __rt_data__start[], __rt_data__end[];
    struct {
	char *start;
	int len;
    } regions[] = {
	{ __rt_text__start, __rt_text__end - __rt_text__start },
	{ __rt_data__start, __rt_data__end - __rt_data__start },
    };
    for (unsigned int i = 0; i < sizeof(regions)/sizeof(regions[0]); i++) {
	if (mlock(regions[i].start, regions[i].len) != 0) {
	    throw gx_system::GxFatalError(
		boost::format(_("failed to lock memory: %1%")) % strerror(errno));
	}
    }
}


namespace gx_engine {

GxMachineBase::~GxMachineBase() {
}


/****************************************************************
 ** GxMachine
 */

GxMachine::GxMachine(gx_system::CmdlineOptions& options_):
    GxMachineBase(),
    options(options_),
    pmap(),
    engine(options.get_plugin_dir(), pmap, gx_engine::get_group_table(), options),
    jack(engine),
    settings(options, jack, engine.stereo_convolver, gx_engine::midi_std_ctr,
	     engine.controller_map, engine, pmap),
    tuner_switcher(settings, engine),
    sock(0),
    signals() {
    engine.set_jack(&jack);
    // ------ initialize parameter list ------
    gx_gui::guivar.register_gui_parameter(pmap);

    /*
    ** setup parameters
    */

    // rack tuner
    gx_engine::get_group_table().insert("racktuner", N_("Rack Tuner"));
    static const value_pair streaming_labels[] = {{"scale"}, {"stream"}, {0}};
    pmap.reg_non_midi_enum_par("racktuner.streaming", "Streaming Mode", streaming_labels, (int*)0, false, 1);
    static const value_pair tuning_labels[] = {{"(Chromatic)"},{"Standard"}, {"Standard/Es"}, {"Open E"}, {0}};
    pmap.reg_non_midi_enum_par("racktuner.tuning", "Tuning", tuning_labels, (int*)0, false, 0);
    pmap.reg_par_non_preset("racktuner.scale_lim", "Limit", 0, 3.0, 1.0, 10.0, 1.0);
    pmap.reg_par_non_preset("ui.tuner_reference_pitch", "?Tuner Reference Pitch", 0, 440, 427, 453, 0.1);
    //pmap.reg_par("racktuner.scale_lim", "Limit", &scale_lim, 3.0, 1.0, 10.0, 1.0); FIXME add in detail view?

    pmap.reg_par("ui.live_play_switcher", "Liveplay preset mode" , (bool*)0, false, false)->setSavable(false);
    pmap.reg_par("ui.racktuner", N_("Tuner on/off"), (bool*)0, true, false);
    pmap.reg_non_midi_par("system.show_tuner", (bool*)0, false);
    pmap.reg_non_midi_par("system.order_rack_h", (bool*)0, false, false);
    pmap.reg_non_midi_par("system.show_value", (bool*)0, false, false);
    pmap.reg_non_midi_par("system.show_tooltips", (bool*)0, false, true);
    pmap.reg_non_midi_par("system.midi_in_preset", (bool*)0, false, false);
    pmap.reg_non_midi_par("system.animations", (bool*)0, false, true);
    pmap.reg_par_non_preset("ui.liveplay_brightness", "?liveplay_brightness", 0, 1.0, 0.5, 1.0, 0.01);
    pmap.reg_par_non_preset("ui.liveplay_background", "?liveplay_background", 0, 0.8, 0.0, 1.0, 0.01);
    pmap.reg_par("engine.mute", "Mute", 0, false);
    pmap.reg_non_midi_par("ui.mp_s_h", (bool*)0, false);
    pmap.reg_non_midi_par("system.show_presets", (bool*)0, false, false);
    pmap.reg_non_midi_par("system.show_toolbar", (bool*)0, false, false);
    pmap.reg_non_midi_par("system.show_rack", (bool*)0, false, false);

#ifndef NDEBUG
    // ------ time measurement (debug) ------
    gx_system::add_time_measurement();
#endif
    lock_rt_memory();
}

GxMachine::~GxMachine() {
    delete sock;
#ifndef NDEBUG
    if (options.dump_parameter) {
	pmap.dump("json");
    }
#endif
}

void GxMachine::set_state(GxEngineState state) {
    engine.set_state(state);
}

GxEngineState GxMachine::get_state() {
    return engine.get_state();
}

unsigned int GxMachine::get_samplerate() {
    return engine.get_samplerate();
}

bool GxMachine::ladspaloader_load(const gx_system::CmdlineOptions& options, LadspaLoader::pluginarray& p) {
    return engine.ladspaloader.load(options, p);
}

LadspaLoader::pluginarray::iterator GxMachine::ladspaloader_begin() {
    return engine.ladspaloader.begin();
}

LadspaLoader::pluginarray::iterator GxMachine::ladspaloader_end() {
    return engine.ladspaloader.end();
}

void GxMachine::ladspaloader_update_instance(PluginDef *pdef, plugdesc *pdesc) {
    engine.ladspaloader.update_instance(pdef, pdesc);
    if (pdef->register_params) {
	pmap.set_replace_mode(true);
	gx_engine::ParamRegImpl preg(&pmap);
	preg.plugin = pdef;
	pdef->register_params(preg);
	pmap.set_replace_mode(false);
    }
}

bool GxMachine::update_module_lists() {
    return engine.update_module_lists();
}

void GxMachine::check_module_lists() {
    engine.check_module_lists();
}

void GxMachine::mono_chain_release() {
    engine.mono_chain.release();
}

void GxMachine::stereo_chain_release() {
    engine.stereo_chain.release();
}

int GxMachine::pluginlist_add(Plugin *pl, PluginPos pos, int flags) {
    return engine.pluginlist.add(pl, pos, flags);
}

int GxMachine::pluginlist_add(PluginDef *p, PluginPos pos, int flags) {
    return engine.pluginlist.add(p, pos, flags);
}

int GxMachine::pluginlist_add(PluginDef **p, PluginPos pos, int flags) {
    return engine.pluginlist.add(p, pos, flags);
}

int GxMachine::pluginlist_add(plugindef_creator *p, PluginPos pos, int flags) {
    return engine.pluginlist.add(p, pos, flags);
}

void GxMachine::pluginlist_delete_module(Plugin *pl) {
    engine.pluginlist.delete_module(pl, pmap, gx_engine::get_group_table());
}

Plugin *GxMachine::pluginlist_lookup_plugin(const char *id) const {
    return engine.pluginlist.lookup_plugin(id);
}

bool GxMachine::load_unit(gx_gui::UiBuilderImpl& builder, PluginDef* pdef) {
    return builder.load_unit(pdef);
}

PluginDef *GxMachine::ladspaloader_create(unsigned int idx) {
    return engine.ladspaloader.create(idx);
}

PluginDef *GxMachine::ladspaloader_create(plugdesc *p) {
    return engine.ladspaloader.create(p);
}

LadspaLoader::pluginarray::iterator GxMachine::ladspaloader_find(unsigned long uniqueid) {
    return engine.ladspaloader.find(uniqueid);
}

void GxMachine::ladspaloader_set_plugins(LadspaLoader::pluginarray& new_plugins) {
    engine.ladspaloader.set_plugins(new_plugins);
}

void GxMachine::pluginlist_append_rack(UiBuilderBase& ui) {
    engine.pluginlist.append_rack(ui);
}

void GxMachine::pluginlist_registerPlugin(Plugin *pl) {
    engine.pluginlist.registerPlugin(pl, pmap, gx_engine::get_group_table());
}

const std::string& GxMachine::conv_getIRFile(const char *id) {
    if (strcmp(id, "jconv") == 0) {
	return engine.stereo_convolver.getIRFile();
    } else {
	return engine.mono_convolver.getIRFile();
    }
}

float GxMachine::get_tuner_freq() {
    return engine.tuner.get_freq();
}

void GxMachine::set_oscilloscope_mul_buffer(int a, unsigned int b) {
    engine.oscilloscope.set_mul_buffer(a, b);
}

int GxMachine::get_oscilloscope_mul_buffer() {
    return engine.oscilloscope.get_mul_buffer();
}

float *GxMachine::get_oscilloscope_buffer() {
    return engine.oscilloscope.get_buffer();
}

void GxMachine::clear_oscilloscope_buffer() {
    engine.oscilloscope.clear_buffer();
}

bool GxMachine::oscilloscope_plugin_box_visible() {
    return engine.oscilloscope.plugin.box_visible;
}

sigc::signal<void, int>& GxMachine::signal_oscilloscope_post_pre() {
    return engine.oscilloscope.post_pre_signal.changed;
}

sigc::signal<void, bool>& GxMachine::signal_oscilloscope_visible() {
    return engine.oscilloscope.visible.changed;
}

sigc::signal<int, bool>& GxMachine::signal_oscilloscope_activation() {
    return engine.oscilloscope.activation;
}

sigc::signal<void, unsigned int>& GxMachine::signal_oscilloscope_size_change() {
    return engine.oscilloscope.size_change;
}

float GxMachine::maxlevel_get(int channel) {
    return engine.maxlevel.get(channel);
}

void GxMachine::maxlevel_reset() {
    engine.maxlevel.reset();
}

bool GxMachine::midiaudiobuffer_get_midistat() {
    return engine.midiaudiobuffer.get_midistat();
}

MidiAudioBuffer::Load GxMachine::midiaudiobuffer_jack_load_status() {
    return engine.midiaudiobuffer.jack_load_status();
}

gx_system::CmdlineOptions& GxMachine::get_options() const {
    return options;
}

void GxMachine::start_socket(sigc::slot<void> quit_mainloop, int port) {
    if (sock) {
	return;
    }
    sock = new MyService(settings, jack, quit_mainloop, port);
    sock->start();
}

sigc::signal<void>& GxMachine::signal_conv_settings_changed(const char *id) {
    if (strcmp(id, "jconv") == 0) {
	return engine.stereo_convolver.signal_settings_changed();
    } else {
	return engine.mono_convolver.signal_settings_changed();
    }
}

sigc::signal<void,const Glib::ustring&,const Glib::ustring&>& GxMachine::tuner_switcher_signal_display() {
    return tuner_switcher.signal_display();
}

sigc::signal<void,TunerSwitcher::SwitcherState>& GxMachine::tuner_switcher_signal_set_state() {
    return tuner_switcher.signal_set_state();
}

sigc::signal<void>& GxMachine::tuner_switcher_signal_selection_done() {
    return tuner_switcher.signal_selection_done();
}

sigc::signal<void,GxEngineState>& GxMachine::signal_state_change() {
    return engine.signal_state_change();
}

Glib::Dispatcher& GxMachine::signal_jack_load_change() {
    return engine.midiaudiobuffer.signal_jack_load_change();
}

void GxMachine::tuner_used_for_display(bool on) {
    engine.tuner.used_for_display(on);
}

void GxMachine::tuner_used_for_livedisplay(bool on) {
    engine.tuner.used_for_livedisplay(on);
}

void GxMachine::start_ramp_down() {
    engine.start_ramp_down();
}

void GxMachine::wait_ramp_down_finished() {
    engine.wait_ramp_down_finished();
}

void GxMachine::set_stateflag(ModuleSequencer::StateFlag flag) {
    engine.set_stateflag(flag);
}

// tuner_switcher
bool GxMachine::get_tuner_switcher_active() {
    return tuner_switcher.get_active();
}

void GxMachine::tuner_switcher_activate(bool v) {
    tuner_switcher.activate(v);
}

bool GxMachine::tuner_switcher_deactivate() {
    return tuner_switcher.deactivate();
}

// preset
bool GxMachine::setting_is_preset() {
    return settings.setting_is_preset();
}


const Glib::ustring& GxMachine::get_current_bank() {
    return settings.get_current_bank();
}

gx_system::PresetFile *GxMachine::get_current_bank_file() {
    return settings.get_current_bank_file();
}

const Glib::ustring& GxMachine::get_current_name() {
    return settings.get_current_name();
}

gx_system::PresetFile* GxMachine::get_bank_file(const Glib::ustring& bank) const {
    return settings.banks.get_file(bank);
}

Glib::ustring GxMachine::get_bank_name(int n) {
    return settings.banks.get_name(n);
}

void GxMachine::load_preset(gx_system::PresetFile *pf, const Glib::ustring& name) {
    settings.load_preset(pf, name);
}

void GxMachine::loadstate() {
    settings.loadstate();
}

int GxMachine::bank_size() {
    return settings.banks.size();
}

bool GxMachine::settings_is_loading() {
    return settings.is_loading();
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

Glib::RefPtr<gx_preset::PluginPresetList> GxMachine::load_plugin_preset_list(const Glib::ustring& id, bool factory) const {
    return settings.load_plugin_preset_list(id, factory);
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

bool GxMachine::bank_strip_preset_postfix(std::string& name) {
    return settings.banks.strip_preset_postfix(name);
}

std::string GxMachine::bank_decode_filename(const std::string& s) {
    return settings.banks.decode_filename(s);
}

void GxMachine::bank_make_valid_utf8(Glib::ustring& s) {
    settings.banks.make_valid_utf8(s);
}

void GxMachine::bank_make_bank_unique(Glib::ustring& name, std::string *file) {
    settings.banks.make_bank_unique(name, file);
}

void GxMachine::bank_insert(gx_system::PresetFile* f) {
    settings.banks.insert(f);
}

bool GxMachine::rename_bank(const Glib::ustring& oldname, const Glib::ustring& newname, const std::string& newfile) {
    return settings.rename_bank(oldname, newname, newfile);
}

bool GxMachine::rename_preset(gx_system::PresetFile& pf, const Glib::ustring& oldname, const Glib::ustring& newname) {
    return settings.rename_preset(pf, oldname, newname);
}

void GxMachine::bank_reorder(const std::vector<Glib::ustring>& neworder) {
    settings.banks.reorder(neworder);
}

void GxMachine::reorder_preset(gx_system::PresetFile& pf, const std::vector<Glib::ustring>& neworder) {
    settings.reorder_preset(pf, neworder);
}

bool GxMachine::bank_check_reparse() {
    return settings.banks.check_reparse();
}

void GxMachine::erase_preset(gx_system::PresetFile& pf, const Glib::ustring& name) {
    settings.erase_preset(pf, name);
}

gx_system::PresetFile *GxMachine::bank_get_file(const Glib::ustring& bank) const {
    return settings.banks.get_file(bank);
}

gx_system::PresetBanks::iterator GxMachine::bank_begin() {
    return settings.banks.begin();
}

gx_system::PresetBanks::iterator GxMachine::bank_end() {
    return settings.banks.end();
}

void GxMachine::pf_append(gx_system::PresetFile& pf, const Glib::ustring& src, gx_system::PresetFile& pftgt, const Glib::ustring& name) {
    settings.append(pf, src, pftgt, name);
}

void GxMachine::pf_insert_before(gx_system::PresetFile& pf, const Glib::ustring& src, gx_system::PresetFile& pftgt, const Glib::ustring& pos, const Glib::ustring& name) {
    settings.insert_before(pf, src, pftgt, pos, name);
}

void GxMachine::pf_insert_after(gx_system::PresetFile& pf, const Glib::ustring& src, gx_system::PresetFile& pftgt, const Glib::ustring& pos, const Glib::ustring& name) {
    settings.insert_after(pf, src, pftgt, pos, name);
}

bool GxMachine::convert_preset(gx_system::PresetFile& pf) {
    return settings.convert_preset(pf);
}

bool GxMachine::bank_remove(const Glib::ustring& bank) {
    return settings.banks.remove(bank);
}

void GxMachine::bank_save() {
    settings.banks.save();
}

void GxMachine::set_source_to_state() {
    settings.set_source_to_state();
}

void GxMachine::make_bank_unique(Glib::ustring& name, std::string *file) {
    settings.banks.make_bank_unique(name, file);
}

void GxMachine::pf_save(gx_system::PresetFile& pf, const Glib::ustring& name) {
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

void GxMachine::reset_unit(Glib::ustring group_id) const {
    pmap.reset_unit(group_id, engine.pluginlist.lookup_plugin(group_id.c_str())->pdef->groups);
}

bool GxMachine::parameter_unit_has_std_values(Glib::ustring group_id) const {
    return pmap.unit_has_std_values(group_id, engine.pluginlist.lookup_plugin(group_id.c_str())->pdef->groups);
}

void GxMachine::set_parameter_value(const std::string& id, int value) {
    //cerr << "SVI " << id << ": " << value << endl;
    pmap[id].getInt().set(value);
}

void GxMachine::set_parameter_value(const std::string& id, bool value) {
    //cerr << "SVB " << id << ": " << value << endl;
    pmap[id].getBool().set(value);
}

void GxMachine::set_parameter_value(const std::string& id, float value) {
    //cerr << "SVF " << id << ": " << value << endl;
    pmap[id].getFloat().set(value);
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

sigc::signal<void, int>& GxMachine::_signal_parameter_value_int(const std::string& id) {
    std::map<string,gx_ui::GxUiItem*>::iterator i = signals.find(id);
    gx_ui::UiSignal<int> *u;
    if (i != signals.end()) {
	u = dynamic_cast<gx_ui::UiSignal<int>*>(i->second);
    } else {
	u = gx_ui::UiSignal<int>::create(&engine.get_ui(), pmap, id);
	signals[id] = u;
    }
    return u->changed;
}

sigc::signal<void, bool>& GxMachine::_signal_parameter_value_bool(const std::string& id) {
    std::map<string,gx_ui::GxUiItem*>::iterator i = signals.find(id);
    gx_ui::UiSignal<bool> *u;
    if (i != signals.end()) {
	u = dynamic_cast<gx_ui::UiSignal<bool>*>(i->second);
    } else {
	u = gx_ui::UiSignal<bool>::create(&engine.get_ui(), pmap, id);
	signals[id] = u;
    }
    return u->changed;
}

sigc::signal<void, float>& GxMachine::_signal_parameter_value_float(const std::string& id) {
    std::map<string,gx_ui::GxUiItem*>::iterator i = signals.find(id);
    gx_ui::UiSignal<float> *u;
    if (i != signals.end()) {
	u = dynamic_cast<gx_ui::UiSignal<float>*>(i->second);
    } else {
	u = gx_ui::UiSignal<float>::create(&engine.get_ui(), pmap, id);
	signals[id] = u;
    }
    return u->changed;
}

// MidiControllerList
bool GxMachine::midi_get_config_mode() {
    return engine.controller_map.get_config_mode();
}

void GxMachine::midi_set_config_mode(bool v, int ctl) {
    engine.controller_map.set_config_mode(v, ctl);
}

sigc::signal<void,int>& GxMachine::signal_midi_new_program() {
    return engine.controller_map.signal_new_program();
}

sigc::signal<void>& GxMachine::signal_midi_changed() {
    return engine.controller_map.signal_changed();
}

int GxMachine::midi_size() {
    return engine.controller_map.size();
}

midi_controller_list& GxMachine::midi_get(int n) {
    return engine.controller_map[n];
}

void GxMachine::midi_deleteParameter(Parameter& param, bool quiet) {
    engine.controller_map.deleteParameter(param, quiet);
}

int GxMachine::midi_get_current_control() {
    return engine.controller_map.get_current_control();
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

// cheat
ConvolverMonoAdapter& GxMachine::get_mono_convolver() {
    return engine.mono_convolver;
}

ConvolverStereoAdapter& GxMachine::get_stereo_convolver() {
    return engine.stereo_convolver;
}


/****************************************************************
 ** GxMachineRemote
 */

GxMachineRemote::GxMachineRemote(gx_system::CmdlineOptions& options_)
    : GxMachineBase(),
      options(options_),
      pmap(),
      pluginlist(),
      socket(),
      writebuf(),
      os(),
      jw(),
      is(0),
      jp() {
    socket = Gio::Socket::create(Gio::SOCKET_FAMILY_IPV4, Gio::SOCKET_TYPE_STREAM, Gio::SOCKET_PROTOCOL_TCP);
    Glib::RefPtr<Gio::InetAddress> a = Gio::InetAddress::create("127.0.0.1");
    try {
	socket->connect(Gio::InetSocketAddress::create(a, 7000));
    } catch (Gio::Error e) {
	throw e;
    }
    socket->set_blocking(false);
    writebuf = new __gnu_cxx::stdio_filebuf<char>(socket->get_fd(), std::ios::out);
    os = new ostream(writebuf);
    jw = new gx_system::JsonWriter(os, false);

    start_call("parameterlist");
    send();
    receive();
    pmap.readJSON(jp);
    start_call("pluginlist");
    send();
    receive();
    pluginlist.readJSON(jp);
    Glib::signal_io().connect(
	sigc::mem_fun(this, &GxMachineRemote::socket_input_handler),
	socket->get_fd(), Glib::IO_IN|Glib::IO_HUP);
    start_notify("listen");
    jw->write("all");
    send();
}

GxMachineRemote::~GxMachineRemote() {
    jw->close();
    delete jw;
    writebuf->close();
    delete os;
    delete writebuf;
}

bool GxMachineRemote::socket_input_handler(Glib::IOCondition cond) {
    if (cond == Glib::IO_HUP) {
	return false;
    }
    char buf[10000];
    int n = socket->receive(buf, sizeof(buf));
    delete is;
    is = new stringstream(std::string(buf, n));
    jp.set_stream(is);
    jp.reset();
    try {
	jp.next(gx_system::JsonParser::begin_object);
	jp.next(gx_system::JsonParser::value_key);
	jp.next(gx_system::JsonParser::value_string);
	jp.next(gx_system::JsonParser::value_key);
	jp.next(gx_system::JsonParser::value_string);
	std::string method = jp.current_value();
	jp.next(gx_system::JsonParser::value_key);
	if (method == "state_changed") {
	    jp.next(gx_system::JsonParser::begin_array);
	    jp.next(gx_system::JsonParser::value_string);
	    engine_state_change(string_to_engine_state(jp.current_value()));
	} else if (method == "set") {
	    jp.next(gx_system::JsonParser::begin_array);
	    while (jp.peek() != gx_system::JsonParser::end_array) {
		jp.next(gx_system::JsonParser::value_string);
		Parameter& p = pmap[jp.current_value()];
		if (p.isFloat()) {
		    jp.next(gx_system::JsonParser::value_number);
		    std::map<std::string,sigc::signal<void,float>* >::iterator i = signals_float.find(p.id());
		    if (i != signals_float.end()) {
			(*i->second)(jp.current_value_float());
		    }
		} else if (p.isInt()) {
		    jp.next(gx_system::JsonParser::value_number);
		    std::map<std::string,sigc::signal<void,int>* >::iterator i = signals_int.find(p.id());
		    if (i != signals_int.end()) {
			(*i->second)(jp.current_value_int());
		    }
		} else if (p.isBool()) {
		    jp.next(gx_system::JsonParser::value_number);
		    std::map<std::string,sigc::signal<void,bool>* >::iterator i = signals_bool.find(p.id());
		    if (i != signals_bool.end()) {
			(*i->second)(jp.current_value_int());
		    }
		} else if (p.isFile() || p.isString()) {
		} else {
		}
	    }
	    jp.next(gx_system::JsonParser::end_array);
	} else {
	    printf("> %.*s", n, buf); fflush(stdout);
	}
    } catch (gx_system::JsonException e) {
	cerr << "JsonException: " << e.what() << endl;
	assert(false);
    }
    return true;
}

void GxMachineRemote::start_notify(const char *method) {
    jw->begin_object();
    jw->write_key("jsonrpc");
    jw->write("2.0");
    jw->write_key("method");
    jw->write(method);
    jw->write_key("params");
    jw->begin_array();
}

void GxMachineRemote::start_call(const char *method) {
    jw->begin_object();
    jw->write_key("jsonrpc");
    jw->write("2.0");
    jw->write_key("id");
    jw->write("1");
    jw->write_key("method");
    jw->write(method);
    jw->write_key("params");
    jw->begin_array();
}

void GxMachineRemote::send() {
    jw->end_array();
    jw->end_object();
    *os << endl;
    jw->reset();
}

bool GxMachineRemote::receive(gx_system::JsonParser *jpl, bool verbose) {
    char buf[10000];
    socket->set_blocking(true);
    iostream *isl;
    if (jpl) {
	isl = static_cast<iostream*>(jpl->get_stream()); //FIXME
    } else {
	delete is;
	is = new stringstream();
	jp.set_stream(is);
	jp.reset();
	isl = is;
	jpl = &jp;
    }
    while (true) {
	int n;
	try {
	    n = socket->receive(buf, sizeof(buf));
	    if (verbose && n > 0) {
		printf("%.*s", n, buf);
		fflush(stdout);
	    }
	} catch(Glib::Error e) {
	    return false;
	}
	if (n <= 0) {
	    return false;
	}
	char *p = buf;
	while (n-- > 0) {
	    isl->put(*p);
	    if (*p == '\n') {
		isl->seekg(0);
		jpl->next(gx_system::JsonParser::begin_object);
		jpl->next(gx_system::JsonParser::value_key); // "jsonrpc"
		jpl->next(gx_system::JsonParser::value_string); // "2.0"
		jpl->next(gx_system::JsonParser::value_key);
		if (jpl->current_value() == "id") {
		    jpl->next(gx_system::JsonParser::value_string); // id
		    jpl->next(gx_system::JsonParser::value_key); // "result"
		    return true;
		} else {
		    assert(jpl->current_value() == "method");
		    isl->seekp(0);
		    jp.reset();
		}
	    }
	    p++;
	}
    }
}

void GxMachineRemote::set_state(GxEngineState state) {
    start_notify("setstate");
    jw->write(engine_state_to_string(state));
    send();
}

GxEngineState GxMachineRemote::get_state() {
    start_call("getstate");
    send();
    receive();
    jp.next(gx_system::JsonParser::value_string);
    return string_to_engine_state(jp.current_value());
}

unsigned int GxMachineRemote::get_samplerate() {
    return 44100;
}


/*
** LadspaLoader
*/

bool GxMachineRemote::ladspaloader_load(const gx_system::CmdlineOptions& options, LadspaLoader::pluginarray& p) {
    return false;
}

LadspaLoader::pluginarray::iterator GxMachineRemote::ladspaloader_begin() {
    LadspaLoader::pluginarray p;
    return p.begin();
}

LadspaLoader::pluginarray::iterator GxMachineRemote::ladspaloader_end() {
    LadspaLoader::pluginarray p;
    return p.end();
}

void GxMachineRemote::ladspaloader_update_instance(PluginDef *pdef, plugdesc *pdesc) {
}

PluginDef *GxMachineRemote::ladspaloader_create(unsigned int idx) {
    return 0;
}

PluginDef *GxMachineRemote::ladspaloader_create(plugdesc *p) {
    return 0;
}

LadspaLoader::pluginarray::iterator GxMachineRemote::ladspaloader_find(unsigned long uniqueid) {
    LadspaLoader::pluginarray p;
    return p.begin();
}

void GxMachineRemote::ladspaloader_set_plugins(LadspaLoader::pluginarray& new_plugins) {
}

bool GxMachineRemote::update_module_lists() {
    return false;
}

void GxMachineRemote::check_module_lists() {
}

void GxMachineRemote::mono_chain_release() {
}

void GxMachineRemote::stereo_chain_release() {
}


/*
** PluginList
*/

int GxMachineRemote::pluginlist_add(Plugin *pl, PluginPos pos, int flags) {
    return 0;
}

int GxMachineRemote::pluginlist_add(PluginDef *p, PluginPos pos, int flags) {
    return 0;
}

int GxMachineRemote::pluginlist_add(PluginDef **p, PluginPos pos, int flags) {
    return 0;
}

int GxMachineRemote::pluginlist_add(plugindef_creator *p, PluginPos pos, int flags) {
    return 0;
}

void GxMachineRemote::pluginlist_delete_module(Plugin *pl) {
}

Plugin *GxMachineRemote::pluginlist_lookup_plugin(const char *id) const {
    return pluginlist.lookup_plugin(id);
}

void GxMachineRemote::pluginlist_append_rack(UiBuilderBase& ui) {
    pluginlist.append_rack(ui);
}

void GxMachineRemote::pluginlist_registerPlugin(Plugin *pl) {
    assert(false);
}

static const char *next_char_pointer(gx_system::JsonParser& jp) {
    switch (jp.next()) {
    case gx_system::JsonParser::value_string: return jp.current_value().c_str();
    case gx_system::JsonParser::value_null: return 0;
    default: jp.throw_unexpected(gx_system::JsonParser::value_string); return 0;
    }
}

static const std::string next_string(gx_system::JsonParser& jp) {
    if (jp.next() != gx_system::JsonParser::value_string) {
	jp.throw_unexpected(gx_system::JsonParser::value_string);
    }
    return jp.current_value();
}

int GxMachineRemote::load_remote_ui(const UiBuilder& builder) {
    GxMachineRemote *m = dynamic_cast<GxMachineRemote*>(&static_cast<const gx_gui::UiBuilderImpl*>(&builder)->main.get_machine());
    m->start_call("plugin_load_ui");
    m->jw->write(builder.plugin->id);
    m->send();
    try {
	stringstream is;
	gx_system::JsonParser jp(&is);
	m->receive(&jp);
	jp.next(gx_system::JsonParser::begin_array);
	while (jp.peek() != gx_system::JsonParser::end_array) {
	    jp.next(gx_system::JsonParser::begin_array);
	    jp.next(gx_system::JsonParser::value_string);
	    if (jp.current_value() == "openTabBox") {
		builder.openTabBox(next_char_pointer(jp));
	    } else if (jp.current_value() == "openVerticalBox") {
		builder.openVerticalBox(next_char_pointer(jp));
	    } else if (jp.current_value() == "openVerticalBox1") {
		builder.openVerticalBox1(next_char_pointer(jp));
	    } else if (jp.current_value() == "openVerticalBox2") {
		builder.openVerticalBox2(next_char_pointer(jp));
	    } else if (jp.current_value() == "openHorizontalhideBox") {
		builder.openHorizontalhideBox(next_char_pointer(jp));
	    } else if (jp.current_value() == "openHorizontalBox") {
		builder.openHorizontalBox(next_char_pointer(jp));
	    } else if (jp.current_value() == "openHorizontalBox") {
		builder.openHorizontalBox(next_char_pointer(jp));
	    } else if (jp.current_value() == "insertSpacer") {
		builder.insertSpacer();
	    } else if (jp.current_value() == "set_next_flags") {
		jp.next(gx_system::JsonParser::value_number);
		builder.set_next_flags(jp.current_value_int());
	    } else if (jp.current_value() == "create_small_rackknob") {
		std::string id = next_string(jp);
		builder.create_small_rackknob(id.c_str(), next_char_pointer(jp));
	    } else if (jp.current_value() == "create_small_rackknobr") {
		std::string id = next_string(jp);
		builder.create_small_rackknobr(id.c_str(), next_char_pointer(jp));
	    } else if (jp.current_value() == "create_master_slider") {
		std::string id = next_string(jp);
		builder.create_master_slider(id.c_str(), next_char_pointer(jp));
	    } else if (jp.current_value() == "create_selector_no_caption") {
		builder.create_selector_no_caption(next_char_pointer(jp));
	    } else if (jp.current_value() == "create_selector") {
		std::string id = next_string(jp);
		builder.create_selector(id.c_str(), next_char_pointer(jp));
	    } else if (jp.current_value() == "create_spin_value") {
		std::string id = next_char_pointer(jp);
		builder.create_spin_value(id.c_str(), next_char_pointer(jp));
	    } else if (jp.current_value() == "create_switch_no_caption") {
		std::string sw_type = next_char_pointer(jp);
		builder.create_switch_no_caption(sw_type.c_str(), next_char_pointer(jp));
	    } else if (jp.current_value() == "create_switch") {
		std::string sw_type = next_char_pointer(jp);
		std::string id = next_char_pointer(jp);
		builder.create_switch(sw_type.c_str(), id.c_str(), next_char_pointer(jp));
	    } else if (jp.current_value() == "create_port_display") {
		std::string id = next_char_pointer(jp);
		builder.create_port_display(id.c_str(), next_char_pointer(jp));
	    } else if (jp.current_value() == "closeBox") {
		builder.closeBox();
	    } else if (jp.current_value() == "load_glade") {
		jp.next(gx_system::JsonParser::value_string);
		builder.load_glade(jp.current_value().c_str());
	    } else {
		cerr << "unknown uiBuilder function " << jp.current_value() << endl;
		jp.skip_object();
	    }
	    jp.next(gx_system::JsonParser::end_array);
	}
	jp.next(gx_system::JsonParser::end_array);
    } catch (gx_system::JsonException e) {
	cerr << "JsonException: " << e.what() << endl;
	assert(false);
    }
    return 0;
}

bool GxMachineRemote::load_unit(gx_gui::UiBuilderImpl& builder, PluginDef* pdef) {
    pdef->load_ui = load_remote_ui;
    return builder.load_unit(pdef);
}


/*
** Oscilloscope
*/

void GxMachineRemote::set_oscilloscope_mul_buffer(int a, unsigned int b) {
}

int GxMachineRemote::get_oscilloscope_mul_buffer() {
    return 1;
}

float *GxMachineRemote::get_oscilloscope_buffer() {
    return 0;
}

void GxMachineRemote::clear_oscilloscope_buffer() {
}

bool GxMachineRemote::oscilloscope_plugin_box_visible() {
    return false;
}

sigc::signal<void, int>& GxMachineRemote::signal_oscilloscope_post_pre() {
    static sigc::signal<void, int> x;
    return x;
}

sigc::signal<void, bool>& GxMachineRemote::signal_oscilloscope_visible() {
    static sigc::signal<void, bool> x;
    return x;
}

sigc::signal<int, bool>& GxMachineRemote::signal_oscilloscope_activation() {
    static sigc::signal<int, bool> x;
    return x;
}

sigc::signal<void, unsigned int>& GxMachineRemote::signal_oscilloscope_size_change() {
    static sigc::signal<void, unsigned int> x;
    return x;
}

const std::string& GxMachineRemote::conv_getIRFile(const char *id) {
    static std::string s = "";
    return s;
}

float GxMachineRemote::get_tuner_freq() {
    return 0;
}

float GxMachineRemote::maxlevel_get(int channel) {
    return 0;
}

void GxMachineRemote::maxlevel_reset() {
}

bool GxMachineRemote::midiaudiobuffer_get_midistat() {
    return false;
}

MidiAudioBuffer::Load GxMachineRemote::midiaudiobuffer_jack_load_status() {
    return MidiAudioBuffer::load_normal;
}

gx_system::CmdlineOptions& GxMachineRemote::get_options() const {
    return options;
}

void GxMachineRemote::start_socket(sigc::slot<void> quit_mainloop, int port) {
    assert(false);
}

sigc::signal<void>& GxMachineRemote::signal_conv_settings_changed(const char *id) {
    static sigc::signal<void> x;
    return x;
}

sigc::signal<void,const Glib::ustring&,const Glib::ustring&>& GxMachineRemote::tuner_switcher_signal_display() {
    static sigc::signal<void,const Glib::ustring&,const Glib::ustring&> x;
    return x;
}

sigc::signal<void,TunerSwitcher::SwitcherState>& GxMachineRemote::tuner_switcher_signal_set_state() {
    static sigc::signal<void,TunerSwitcher::SwitcherState> x;
    return x;
}

sigc::signal<void>& GxMachineRemote::tuner_switcher_signal_selection_done() {
    static sigc::signal<void> x;
    return x;
}

sigc::signal<void,GxEngineState>& GxMachineRemote::signal_state_change() {
    return engine_state_change;
}

Glib::Dispatcher& GxMachineRemote::signal_jack_load_change() {
    static Glib::Dispatcher x;
    return x;
}

void GxMachineRemote::tuner_used_for_display(bool on) {
}

void GxMachineRemote::tuner_used_for_livedisplay(bool on) {
}

void GxMachineRemote::start_ramp_down() {
}

void GxMachineRemote::wait_ramp_down_finished() {
}

void GxMachineRemote::set_stateflag(ModuleSequencer::StateFlag flag) {
}

// tuner_switcher
bool GxMachineRemote::get_tuner_switcher_active() {
    return false;
}

void GxMachineRemote::tuner_switcher_activate(bool v) {
}

bool GxMachineRemote::tuner_switcher_deactivate() {
    return false;
}

// preset
bool GxMachineRemote::setting_is_preset() {
    return true;
}


const Glib::ustring& GxMachineRemote::get_current_bank() {
    static Glib::ustring s = "testbank";
    return s;
}

gx_system::PresetFile *GxMachineRemote::get_current_bank_file() {
    return 0;
}

const Glib::ustring& GxMachineRemote::get_current_name() {
    static Glib::ustring s = "testpreset";
    return s;
}

gx_system::PresetFile* GxMachineRemote::get_bank_file(const Glib::ustring& bank) const {
    return 0;
}

Glib::ustring GxMachineRemote::get_bank_name(int n) {
    return "testbank";
}

void GxMachineRemote::load_preset(gx_system::PresetFile *pf, const Glib::ustring& name) {
}

void GxMachineRemote::loadstate() {
}

int GxMachineRemote::bank_size() {
    return 0;
}

bool GxMachineRemote::settings_is_loading() {
    return false;
}

void GxMachineRemote::create_default_scratch_preset() {
}

void GxMachineRemote::set_statefilename(const std::string& fn) {
}

void GxMachineRemote::save_to_state(bool preserve_preset) {
}

Glib::RefPtr<gx_preset::PluginPresetList> GxMachineRemote::load_plugin_preset_list(const Glib::ustring& id, bool factory) const {
    static gx_engine::MidiControllerList m;
    static std::string fname = "";
    static Glib::RefPtr<gx_preset::PluginPresetList> p = gx_preset::PluginPresetList::create(fname, const_cast<ParamMap&>(pmap), m);
    return p;
}

void GxMachineRemote::disable_autosave(bool v) {
}

sigc::signal<void>& GxMachineRemote::signal_selection_changed() {
    static sigc::signal<void> x;
    return x;
}

sigc::signal<void>& GxMachineRemote::signal_presetlist_changed() {
    static sigc::signal<void> x;
    return x;
}

bool GxMachineRemote::bank_strip_preset_postfix(std::string& name) {
    return false;
}

std::string GxMachineRemote::bank_decode_filename(const std::string& s) {
    return s;
}

void GxMachineRemote::bank_make_valid_utf8(Glib::ustring& s) {
}

void GxMachineRemote::bank_make_bank_unique(Glib::ustring& name, std::string *file) {
}

void GxMachineRemote::bank_insert(gx_system::PresetFile* f) {
}

bool GxMachineRemote::rename_bank(const Glib::ustring& oldname, const Glib::ustring& newname, const std::string& newfile) {
    return false;
}

bool GxMachineRemote::rename_preset(gx_system::PresetFile& pf, const Glib::ustring& oldname, const Glib::ustring& newname) {
    return false;
}

void GxMachineRemote::bank_reorder(const std::vector<Glib::ustring>& neworder) {
}

void GxMachineRemote::reorder_preset(gx_system::PresetFile& pf, const std::vector<Glib::ustring>& neworder) {
}

bool GxMachineRemote::bank_check_reparse() {
    return false;
}

void GxMachineRemote::erase_preset(gx_system::PresetFile& pf, const Glib::ustring& name) {
}

gx_system::PresetFile *GxMachineRemote::bank_get_file(const Glib::ustring& bank) const {
    return 0;
}

gx_system::PresetBanks::iterator GxMachineRemote::bank_begin() {
    static gx_system::PresetBanks x;
    return x.begin();
}

gx_system::PresetBanks::iterator GxMachineRemote::bank_end() {
    static gx_system::PresetBanks x;
    return x.end();
}

void GxMachineRemote::pf_append(gx_system::PresetFile& pf, const Glib::ustring& src, gx_system::PresetFile& pftgt, const Glib::ustring& name) {
}

void GxMachineRemote::pf_insert_before(gx_system::PresetFile& pf, const Glib::ustring& src, gx_system::PresetFile& pftgt, const Glib::ustring& pos, const Glib::ustring& name) {
}

void GxMachineRemote::pf_insert_after(gx_system::PresetFile& pf, const Glib::ustring& src, gx_system::PresetFile& pftgt, const Glib::ustring& pos, const Glib::ustring& name) {
}

bool GxMachineRemote::convert_preset(gx_system::PresetFile& pf) {
    return true;
}

bool GxMachineRemote::bank_remove(const Glib::ustring& bank) {
    return true;
}

void GxMachineRemote::bank_save() {
}

void GxMachineRemote::set_source_to_state() {
}

void GxMachineRemote::make_bank_unique(Glib::ustring& name, std::string *file) {
}

void GxMachineRemote::pf_save(gx_system::PresetFile& pf, const Glib::ustring& name) {
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
}

bool GxMachineRemote::parameter_hasId(const char *p) {
    return pmap.hasId(p);
}

bool GxMachineRemote::parameter_hasId(const std::string& id) {
    return pmap.hasId(id);
}

void GxMachineRemote::reset_unit(Glib::ustring group_id) const {
    pmap.reset_unit(group_id, 0);
}

bool GxMachineRemote::parameter_unit_has_std_values(Glib::ustring group_id) const {
    return pmap.unit_has_std_values(group_id, 0);
}

void GxMachineRemote::set_parameter_value(const std::string& id, int value) {
    //cerr << "SVI " << id << ": " << value << endl;
    start_notify("set");
    jw->write(id);
    jw->write(value);
    send();
    std::map<string,sigc::signal<void,int>*>::iterator i = signals_int.find(id);
    if (i != signals_int.end()) {
	(*i->second)(value);
    }
}

void GxMachineRemote::set_parameter_value(const std::string& id, bool value) {
    //cerr << "SVB " << id << ": " << value << endl;
    start_notify("set");
    jw->write(id);
    jw->write(value);
    send();
    std::map<string,sigc::signal<void,bool>*>::iterator i = signals_bool.find(id);
    if (i != signals_bool.end()) {
	(*i->second)(value);
    }
}

void GxMachineRemote::set_parameter_value(const std::string& id, float value) {
    //cerr << "SVF " << id << ": " << value << endl;
    start_notify("set");
    jw->write(id);
    jw->write(value);
    send();
    std::map<string,sigc::signal<void,float>*>::iterator i = signals_float.find(id);
    if (i != signals_float.end()) {
	(*i->second)(value);
    }
}

void GxMachineRemote::_request_parameter_value(const std::string& id) {
    start_call("get");
    jw->write(id);
    send();
    receive();
    jp.next(gx_system::JsonParser::begin_object);
    jp.next(gx_system::JsonParser::value_key);
}

int GxMachineRemote::_get_parameter_value_int(const std::string& id) {
    _request_parameter_value(id);
    int v;
    switch (jp.next()) {
    case gx_system::JsonParser::value_string:
	v = pmap[id].getEnum().idx_from_id(jp.current_value());
	break;
    case gx_system::JsonParser::value_number:
	v = jp.current_value_int();
	break;
    default:
	assert(false);
	return 0;
    }
    //cerr << "GVI " << id << ": " << v << endl;
    return v;
}

int GxMachineRemote::_get_parameter_value_bool(const std::string& id) {
    _request_parameter_value(id);
    jp.next(gx_system::JsonParser::value_number);
    //cerr << "GVB " << id << ": " << jp.current_value_int() << endl;
    return jp.current_value_int();
}

float GxMachineRemote::_get_parameter_value_float(const std::string& id) {
    _request_parameter_value(id);
    float v;
    switch (jp.next()) {
    case gx_system::JsonParser::value_string:
	v = dynamic_cast<FloatEnumParameter*>(&pmap[id])->idx_from_id(jp.current_value());
	break;
    case gx_system::JsonParser::value_number:
	v = jp.current_value_float();
	break;
    default:
	assert(false);
	return 0;
    }
    //cerr << "GVF " << id << ": " << jp.current_value_float() << endl;
    return v;
}

sigc::signal<void, int>& GxMachineRemote::_signal_parameter_value_int(const std::string& id) {
    std::map<std::string,sigc::signal<void,int>* >::iterator i = signals_int.find(id);
    if (i != signals_int.end()) {
	return *i->second;
    } else {
	sigc::signal<void,int> *u = new sigc::signal<void,int>;
	signals_int[id] = u;
	return *u;
    }
}

sigc::signal<void, bool>& GxMachineRemote::_signal_parameter_value_bool(const std::string& id) {
    std::map<string,sigc::signal<void,bool>*>::iterator i = signals_bool.find(id);
    if (i != signals_bool.end()) {
	return *i->second;
    } else {
	sigc::signal<void,bool> *u = new sigc::signal<void,bool>;
	signals_bool[id] = u;
	return *u;
    }
}

sigc::signal<void, float>& GxMachineRemote::_signal_parameter_value_float(const std::string& id) {
    std::map<string,sigc::signal<void,float>*>::iterator i = signals_float.find(id);
    if (i != signals_float.end()) {
	return *i->second;
    } else {
	sigc::signal<void,float> *u = new sigc::signal<void,float>;
	signals_float[id] = u;
	return *u;
    }
}

// MidiControllerList
bool GxMachineRemote::midi_get_config_mode() {
    return false;
}

void GxMachineRemote::midi_set_config_mode(bool v, int ctl) {
}

sigc::signal<void,int>& GxMachineRemote::signal_midi_new_program() {
    static sigc::signal<void,int> x;
    return x;
}

sigc::signal<void>& GxMachineRemote::signal_midi_changed() {
    static sigc::signal<void> x;
    return x;
}

int GxMachineRemote::midi_size() {
    return 0;
}

midi_controller_list& GxMachineRemote::midi_get(int n) {
    static midi_controller_list s;
    return s;
}

void GxMachineRemote::midi_deleteParameter(Parameter& param, bool quiet) {
}

int GxMachineRemote::midi_get_current_control() {
    return -1;
}

void GxMachineRemote::midi_set_current_control(int v) {
}

void GxMachineRemote::midi_modifyCurrent(Parameter& param, float lower, float upper, bool toggle) {
}

int GxMachineRemote::midi_param2controller(Parameter& param, const MidiController** p) {
    return -1;
}

// cheat
ConvolverMonoAdapter& GxMachineRemote::get_mono_convolver() {
    return *(ConvolverMonoAdapter*)0;
}

ConvolverStereoAdapter& GxMachineRemote::get_stereo_convolver() {
    return *(ConvolverStereoAdapter*)0;
}


} // namespace gx_engine
