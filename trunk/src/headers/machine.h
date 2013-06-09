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

#pragma once

#ifndef SRC_HEADERS_MACHINE_H_
#define SRC_HEADERS_MACHINE_H_

#include <ext/stdio_filebuf.h>

namespace gx_engine {

class GxMachineBase {
private:
    virtual int _get_parameter_value_int(const std::string& id) = 0;
    virtual int _get_parameter_value_bool(const std::string& id) = 0;
    virtual float _get_parameter_value_float(const std::string& id) = 0;
    virtual sigc::signal<void, int>& _signal_parameter_value_int(const std::string& id) = 0;
    virtual sigc::signal<void, bool>& _signal_parameter_value_bool(const std::string& id) = 0;
    virtual sigc::signal<void, float>& _signal_parameter_value_float(const std::string& id) = 0;
protected:
    GxMachineBase() {}
public:
    virtual ~GxMachineBase();
    // engine
    virtual void set_state(GxEngineState state) = 0;
    virtual GxEngineState get_state() = 0;
    virtual unsigned int get_samplerate() = 0;
    virtual bool ladspaloader_load(const gx_system::CmdlineOptions& options, LadspaLoader::pluginarray& p) = 0;
    virtual LadspaLoader::pluginarray::iterator ladspaloader_begin() = 0;
    virtual LadspaLoader::pluginarray::iterator ladspaloader_end() = 0;
    virtual void ladspaloader_update_instance(PluginDef *pdef, plugdesc *pdesc) = 0;
    virtual bool update_module_lists() = 0;
    virtual void check_module_lists() = 0;
    virtual void mono_chain_release() = 0;
    virtual void stereo_chain_release() = 0;
    virtual int pluginlist_add(Plugin *pl, PluginPos pos, int flags) = 0;
    virtual int pluginlist_add(PluginDef *p, PluginPos pos = PLUGIN_POS_RACK, int flags=0) = 0;
    virtual int pluginlist_add(PluginDef **p, PluginPos pos = PLUGIN_POS_RACK, int flags=0) = 0;
    virtual int pluginlist_add(plugindef_creator *p, PluginPos pos = PLUGIN_POS_RACK, int flags=0) = 0;
    virtual void pluginlist_delete_module(Plugin *pl) = 0;
    virtual Plugin *pluginlist_lookup_plugin(const char *id) const = 0;
    virtual PluginDef *ladspaloader_create(unsigned int idx) = 0;
    virtual PluginDef *ladspaloader_create(plugdesc *p) = 0;
    virtual LadspaLoader::pluginarray::iterator ladspaloader_find(unsigned long uniqueid) = 0;
    virtual void ladspaloader_set_plugins(LadspaLoader::pluginarray& new_plugins) = 0;
    virtual void pluginlist_append_rack(UiBuilderBase& ui) = 0;
    virtual void pluginlist_registerPlugin(Plugin *pl) = 0;
    virtual const std::string& conv_getIRFile(const char *id) = 0;
    virtual float get_tuner_freq() = 0;
    virtual void set_oscilloscope_mul_buffer(int a, unsigned int b) = 0;
    virtual int get_oscilloscope_mul_buffer() = 0;
    virtual float *get_oscilloscope_buffer() = 0;
    virtual void clear_oscilloscope_buffer() = 0;
    virtual bool oscilloscope_plugin_box_visible() = 0;
    virtual sigc::signal<void, int>& signal_oscilloscope_post_pre() = 0;
    virtual sigc::signal<void, bool>& signal_oscilloscope_visible() = 0;
    virtual sigc::signal<int, bool>& signal_oscilloscope_activation() = 0;
    virtual sigc::signal<void, unsigned int>& signal_oscilloscope_size_change() = 0;
    virtual float maxlevel_get(int channel) = 0;
    virtual void maxlevel_reset() = 0;
    virtual bool midiaudiobuffer_get_midistat() = 0;
    virtual MidiAudioBuffer::Load midiaudiobuffer_jack_load_status() = 0;
    virtual gx_system::CmdlineOptions& get_options() const = 0;
    virtual void start_socket(sigc::slot<void> quit_mainloop, int port) = 0;
    virtual sigc::signal<void>& signal_conv_settings_changed(const char *id) = 0;
    virtual sigc::signal<void,const Glib::ustring&,const Glib::ustring&>& tuner_switcher_signal_display() = 0;
    virtual sigc::signal<void,TunerSwitcher::SwitcherState>& tuner_switcher_signal_set_state() = 0;
    virtual sigc::signal<void>& tuner_switcher_signal_selection_done() = 0;
    virtual sigc::signal<void,GxEngineState>& signal_state_change() = 0;
    virtual Glib::Dispatcher& signal_jack_load_change() = 0;
    virtual void tuner_used_for_display(bool on) = 0;
    virtual void tuner_used_for_livedisplay(bool on) = 0;
    virtual void start_ramp_down() = 0;
    virtual void wait_ramp_down_finished() = 0;
    virtual void set_stateflag(ModuleSequencer::StateFlag flag) = 0; // RT
    // tuner_switcher
    virtual bool get_tuner_switcher_active() = 0;
    virtual void tuner_switcher_activate(bool v) = 0;
    virtual bool tuner_switcher_deactivate() = 0;
    // preset
    virtual bool setting_is_preset() = 0;
    virtual const Glib::ustring& get_current_bank() = 0;
    virtual gx_system::PresetFile *get_current_bank_file() = 0;
    virtual const Glib::ustring& get_current_name() = 0;
    virtual gx_system::PresetFile* get_bank_file(const Glib::ustring& bank) const = 0;
    virtual Glib::ustring get_bank_name(int n) = 0;
    virtual void load_preset(gx_system::PresetFile *pf, const Glib::ustring& name) = 0;
    virtual void loadstate() = 0;
    virtual int bank_size() = 0;
    virtual bool settings_is_loading() = 0;
    virtual void create_default_scratch_preset() = 0;
    virtual void set_statefilename(const std::string& fn) = 0;
    virtual void save_to_state(bool preserve_preset=false) = 0;
    virtual Glib::RefPtr<gx_preset::PluginPresetList> load_plugin_preset_list(const Glib::ustring& id, bool factory) const = 0;
    virtual void disable_autosave(bool v) = 0;
    virtual sigc::signal<void>& signal_selection_changed() = 0;
    virtual sigc::signal<void>& signal_presetlist_changed() = 0;
    virtual bool bank_strip_preset_postfix(std::string& name) = 0;
    virtual std::string bank_decode_filename(const std::string& s) = 0;
    virtual void bank_make_valid_utf8(Glib::ustring& s) = 0;
    virtual void bank_make_bank_unique(Glib::ustring& name, std::string *file = 0) = 0;
    virtual void bank_insert(gx_system::PresetFile* f) = 0;
    virtual bool rename_bank(const Glib::ustring& oldname, const Glib::ustring& newname, const std::string& newfile) = 0;
    virtual bool rename_preset(gx_system::PresetFile& pf, const Glib::ustring& oldname, const Glib::ustring& newname) = 0;
    virtual void bank_reorder(const std::vector<Glib::ustring>& neworder) = 0;
    virtual void reorder_preset(gx_system::PresetFile& pf, const std::vector<Glib::ustring>& neworder) = 0;
    virtual bool bank_check_reparse() = 0;
    virtual void erase_preset(gx_system::PresetFile& pf, const Glib::ustring& name) = 0;
    virtual gx_system::PresetFile *bank_get_file(const Glib::ustring& bank) const = 0;
    virtual gx_system::PresetBanks::iterator bank_begin() = 0;
    virtual gx_system::PresetBanks::iterator bank_end() = 0;
    virtual void pf_append(gx_system::PresetFile& pf, const Glib::ustring& src, gx_system::PresetFile& pftgt, const Glib::ustring& name) = 0;
    virtual void pf_insert_before(gx_system::PresetFile& pf, const Glib::ustring& src, gx_system::PresetFile& pftgt, const Glib::ustring& pos, const Glib::ustring& name) = 0;
    virtual void pf_insert_after(gx_system::PresetFile& pf, const Glib::ustring& src, gx_system::PresetFile& pftgt, const Glib::ustring& pos, const Glib::ustring& name) = 0;
    virtual bool convert_preset(gx_system::PresetFile& pf) = 0;
    virtual bool bank_remove(const Glib::ustring& bank) = 0;
    virtual void bank_save() = 0;
    virtual void set_source_to_state() = 0;
    virtual void make_bank_unique(Glib::ustring& name, std::string *file = 0) = 0;
    virtual void pf_save(gx_system::PresetFile& pf, const Glib::ustring& name) = 0;

    // jack
    virtual gx_jack::GxJack *get_jack() = 0;
    // pmap
    virtual Parameter& get_parameter(const std::string& id) = 0;
    virtual void set_init_values() = 0;
    virtual bool parameter_hasId(const char *p) = 0;
    virtual bool parameter_hasId(const std::string& id) = 0;
    virtual void reset_unit(Glib::ustring group_id) const = 0;
    virtual bool parameter_unit_has_std_values(Glib::ustring group_id) const = 0;
    virtual void set_parameter_value(const std::string& id, int value) = 0;
    virtual void set_parameter_value(const std::string& id, float value) = 0;
    virtual void set_parameter_value(const std::string& id, bool value) = 0;
    void set_parameter_value(const std::string& id, double value) { set_parameter_value(id, (float)value); }
    template <class T> T get_parameter_value (const std::string& id);
    template <class T> sigc::signal<void, T>& signal_parameter_value(const std::string& id);
    // MidiControllerList
    virtual bool midi_get_config_mode() = 0;
    virtual void midi_set_config_mode(bool v, int ctl=-1) = 0;
    virtual sigc::signal<void,int>& signal_midi_new_program() = 0;
    virtual sigc::signal<void>& signal_midi_changed() = 0;
    virtual int midi_size() = 0;
    virtual midi_controller_list& midi_get(int n) = 0;
    virtual void midi_deleteParameter(Parameter& param, bool quiet = false) = 0;
    virtual int midi_get_current_control() = 0;
    virtual void midi_set_current_control(int v) = 0;
    virtual void midi_modifyCurrent(Parameter& param, float lower, float upper, bool toggle) = 0;
    virtual int midi_param2controller(Parameter& param, const MidiController** p) = 0;
    // cheat
    virtual ConvolverMonoAdapter& get_mono_convolver() = 0;
    virtual ConvolverStereoAdapter& get_stereo_convolver() = 0;
};

template <> inline float GxMachineBase::get_parameter_value(const std::string& id) {
    return _get_parameter_value_float(id);
}

template <> inline int GxMachineBase::get_parameter_value(const std::string& id) {
    return _get_parameter_value_int(id);
}

template <> inline bool GxMachineBase::get_parameter_value(const std::string& id) {
    return _get_parameter_value_bool(id);
}

template <> inline sigc::signal<void, float>& GxMachineBase::signal_parameter_value(const std::string& id) {
    return _signal_parameter_value_float(id);
}

template <> inline sigc::signal<void, int>& GxMachineBase::signal_parameter_value(const std::string& id) {
    return _signal_parameter_value_int(id);
}

template <> inline sigc::signal<void, bool>& GxMachineBase::signal_parameter_value(const std::string& id) {
    return _signal_parameter_value_bool(id);
}

class GxMachine: public GxMachineBase {
private:
    gx_system::CmdlineOptions& options;
    ParamMap  pmap;
    GxEngine  engine;
    gx_jack::GxJack       jack;
    gx_preset::GxSettings settings;
    TunerSwitcher tuner_switcher;
    MyService *sock;
    std::map<string,gx_ui::GxUiItem*> signals;
private:
    virtual int _get_parameter_value_int(const std::string& id);
    virtual int _get_parameter_value_bool(const std::string& id);
    virtual float _get_parameter_value_float(const std::string& id);
    virtual sigc::signal<void, int>& _signal_parameter_value_int(const std::string& id);
    virtual sigc::signal<void, bool>& _signal_parameter_value_bool(const std::string& id);
    virtual sigc::signal<void, float>& _signal_parameter_value_float(const std::string& id);
public:
    GxMachine(gx_system::CmdlineOptions& options);
    virtual ~GxMachine();
    virtual void set_state(GxEngineState state);
    virtual GxEngineState get_state();
    virtual unsigned int get_samplerate();
    virtual bool ladspaloader_load(const gx_system::CmdlineOptions& options, LadspaLoader::pluginarray& p);
    virtual LadspaLoader::pluginarray::iterator ladspaloader_begin();
    virtual LadspaLoader::pluginarray::iterator ladspaloader_end();
    virtual void ladspaloader_update_instance(PluginDef *pdef, plugdesc *pdesc);
    virtual bool update_module_lists();
    virtual void check_module_lists();
    virtual void mono_chain_release();
    virtual void stereo_chain_release();
    virtual int pluginlist_add(Plugin *pl, PluginPos pos, int flags);
    virtual int pluginlist_add(PluginDef *p, PluginPos pos = PLUGIN_POS_RACK, int flags=0);
    virtual int pluginlist_add(PluginDef **p, PluginPos pos = PLUGIN_POS_RACK, int flags=0);
    virtual int pluginlist_add(plugindef_creator *p, PluginPos pos = PLUGIN_POS_RACK, int flags=0);
    virtual void pluginlist_delete_module(Plugin *pl);
    virtual Plugin *pluginlist_lookup_plugin(const char *id) const;
    virtual PluginDef *ladspaloader_create(unsigned int idx);
    virtual PluginDef *ladspaloader_create(plugdesc *p);
    virtual LadspaLoader::pluginarray::iterator ladspaloader_find(unsigned long uniqueid);
    virtual void ladspaloader_set_plugins(LadspaLoader::pluginarray& new_plugins);
    virtual void pluginlist_append_rack(UiBuilderBase& ui);
    virtual void pluginlist_registerPlugin(Plugin *pl);
    virtual const std::string& conv_getIRFile(const char *id);
    virtual float get_tuner_freq();
    virtual void set_oscilloscope_mul_buffer(int a, unsigned int b);
    virtual int get_oscilloscope_mul_buffer();
    virtual float *get_oscilloscope_buffer();
    virtual void clear_oscilloscope_buffer();
    virtual bool oscilloscope_plugin_box_visible();
    virtual sigc::signal<void, int>& signal_oscilloscope_post_pre();
    virtual sigc::signal<void, bool>& signal_oscilloscope_visible();
    virtual sigc::signal<int, bool>& signal_oscilloscope_activation();
    virtual sigc::signal<void, unsigned int>& signal_oscilloscope_size_change();
    virtual float maxlevel_get(int channel);
    virtual void maxlevel_reset();
    virtual bool midiaudiobuffer_get_midistat();
    virtual MidiAudioBuffer::Load midiaudiobuffer_jack_load_status();
    virtual gx_system::CmdlineOptions& get_options() const;
    virtual void start_socket(sigc::slot<void> quit_mainloop, int port);
    virtual sigc::signal<void>& signal_conv_settings_changed(const char *id);
    virtual sigc::signal<void,const Glib::ustring&,const Glib::ustring&>& tuner_switcher_signal_display();
    virtual sigc::signal<void,TunerSwitcher::SwitcherState>& tuner_switcher_signal_set_state();
    virtual sigc::signal<void>& tuner_switcher_signal_selection_done();
    virtual sigc::signal<void,GxEngineState>& signal_state_change();
    virtual Glib::Dispatcher& signal_jack_load_change();
    virtual void tuner_used_for_display(bool on);
    virtual void tuner_used_for_livedisplay(bool on);
    virtual void start_ramp_down();
    virtual void wait_ramp_down_finished();
    virtual void set_stateflag(ModuleSequencer::StateFlag flag); // RT
    // tuner_switcher
    virtual bool get_tuner_switcher_active();
    virtual void tuner_switcher_activate(bool v);
    virtual bool tuner_switcher_deactivate();
    // preset
    virtual bool setting_is_preset();
    virtual const Glib::ustring& get_current_bank();
    virtual gx_system::PresetFile *get_current_bank_file();
    virtual const Glib::ustring& get_current_name();
    virtual gx_system::PresetFile* get_bank_file(const Glib::ustring& bank) const;
    virtual Glib::ustring get_bank_name(int n);
    virtual void load_preset(gx_system::PresetFile *pf, const Glib::ustring& name);
    virtual void loadstate();
    virtual int bank_size();
    virtual bool settings_is_loading();
    virtual void create_default_scratch_preset();
    virtual void set_statefilename(const std::string& fn);
    virtual void save_to_state(bool preserve_preset=false);
    virtual Glib::RefPtr<gx_preset::PluginPresetList> load_plugin_preset_list(const Glib::ustring& id, bool factory) const;
    virtual void disable_autosave(bool v);
    virtual sigc::signal<void>& signal_selection_changed();
    virtual sigc::signal<void>& signal_presetlist_changed();
    virtual bool bank_strip_preset_postfix(std::string& name);
    virtual std::string bank_decode_filename(const std::string& s);
    virtual void bank_make_valid_utf8(Glib::ustring& s);
    virtual void bank_make_bank_unique(Glib::ustring& name, std::string *file = 0);
    virtual void bank_insert(gx_system::PresetFile* f);
    virtual bool rename_bank(const Glib::ustring& oldname, const Glib::ustring& newname, const std::string& newfile);
    virtual bool rename_preset(gx_system::PresetFile& pf, const Glib::ustring& oldname, const Glib::ustring& newname);
    virtual void bank_reorder(const std::vector<Glib::ustring>& neworder);
    virtual void reorder_preset(gx_system::PresetFile& pf, const std::vector<Glib::ustring>& neworder);
    virtual bool bank_check_reparse();
    virtual void erase_preset(gx_system::PresetFile& pf, const Glib::ustring& name);
    virtual gx_system::PresetFile *bank_get_file(const Glib::ustring& bank) const;
    virtual gx_system::PresetBanks::iterator bank_begin();
    virtual gx_system::PresetBanks::iterator bank_end();
    virtual void pf_append(gx_system::PresetFile& pf, const Glib::ustring& src, gx_system::PresetFile& pftgt, const Glib::ustring& name);
    virtual void pf_insert_before(gx_system::PresetFile& pf, const Glib::ustring& src, gx_system::PresetFile& pftgt, const Glib::ustring& pos, const Glib::ustring& name);
    virtual void pf_insert_after(gx_system::PresetFile& pf, const Glib::ustring& src, gx_system::PresetFile& pftgt, const Glib::ustring& pos, const Glib::ustring& name);
    virtual bool convert_preset(gx_system::PresetFile& pf);
    virtual bool bank_remove(const Glib::ustring& bank);
    virtual void bank_save();
    virtual void set_source_to_state();
    virtual void make_bank_unique(Glib::ustring& name, std::string *file = 0);
    virtual void pf_save(gx_system::PresetFile& pf, const Glib::ustring& name);

    // jack
    virtual gx_jack::GxJack *get_jack();
    // pmap
    virtual Parameter& get_parameter(const char *p);
    virtual Parameter& get_parameter(const std::string& id);
    virtual void set_init_values();
    virtual bool parameter_hasId(const char *p);
    virtual bool parameter_hasId(const std::string& id);
    virtual void reset_unit(Glib::ustring group_id) const;
    virtual bool parameter_unit_has_std_values(Glib::ustring group_id) const;
    virtual void set_parameter_value(const std::string& id, int value);
    virtual void set_parameter_value(const std::string& id, bool value);
    virtual void set_parameter_value(const std::string& id, float value);
    // MidiControllerList
    virtual bool midi_get_config_mode();
    virtual void midi_set_config_mode(bool v, int ctl=-1);
    virtual sigc::signal<void,int>& signal_midi_new_program();
    virtual sigc::signal<void>& signal_midi_changed();
    virtual int midi_size();
    virtual midi_controller_list& midi_get(int n);
    virtual void midi_deleteParameter(Parameter& param, bool quiet = false);
    virtual int midi_get_current_control();
    virtual void midi_set_current_control(int v);
    virtual void midi_modifyCurrent(Parameter& param, float lower, float upper, bool toggle);
    virtual int midi_param2controller(Parameter& param, const MidiController** p);
    // cheat
    virtual ConvolverMonoAdapter& get_mono_convolver();
    virtual ConvolverStereoAdapter& get_stereo_convolver();
};

class GxMachineRemote: public GxMachineBase {
private:
    gx_system::CmdlineOptions& options;
    ParamMap  pmap;
    Glib::RefPtr<Gio::Socket> socket;
    __gnu_cxx::stdio_filebuf<char> *writebuf;
    ostream *os;
    gx_system::JsonWriter *jw;
    gx_system::JsonParser jp;
    std::stringbuf inbuf;
    std::map<string,sigc::signal<void,int>*> signals_int;
    std::map<string,sigc::signal<void,bool>*> signals_bool;
    std::map<string,sigc::signal<void,float>*> signals_float;
private:
    void start_notify(const char *method);
    void start_call(const char *method);
    void send();
    bool receive(istringstream& is);
    void load_parameter();
    virtual int _get_parameter_value_int(const std::string& id);
    virtual int _get_parameter_value_bool(const std::string& id);
    virtual float _get_parameter_value_float(const std::string& id);
    virtual sigc::signal<void, int>& _signal_parameter_value_int(const std::string& id);
    virtual sigc::signal<void, bool>& _signal_parameter_value_bool(const std::string& id);
    virtual sigc::signal<void, float>& _signal_parameter_value_float(const std::string& id);
public:
    GxMachineRemote(gx_system::CmdlineOptions& options);
    virtual ~GxMachineRemote();
    virtual void set_state(GxEngineState state);
    virtual GxEngineState get_state();
    virtual unsigned int get_samplerate();
    virtual bool ladspaloader_load(const gx_system::CmdlineOptions& options, LadspaLoader::pluginarray& p);
    virtual LadspaLoader::pluginarray::iterator ladspaloader_begin();
    virtual LadspaLoader::pluginarray::iterator ladspaloader_end();
    virtual void ladspaloader_update_instance(PluginDef *pdef, plugdesc *pdesc);
    virtual bool update_module_lists();
    virtual void check_module_lists();
    virtual void mono_chain_release();
    virtual void stereo_chain_release();
    virtual int pluginlist_add(Plugin *pl, PluginPos pos, int flags);
    virtual int pluginlist_add(PluginDef *p, PluginPos pos = PLUGIN_POS_RACK, int flags=0);
    virtual int pluginlist_add(PluginDef **p, PluginPos pos = PLUGIN_POS_RACK, int flags=0);
    virtual int pluginlist_add(plugindef_creator *p, PluginPos pos = PLUGIN_POS_RACK, int flags=0);
    virtual void pluginlist_delete_module(Plugin *pl);
    virtual Plugin *pluginlist_lookup_plugin(const char *id) const;
    virtual PluginDef *ladspaloader_create(unsigned int idx);
    virtual PluginDef *ladspaloader_create(plugdesc *p);
    virtual LadspaLoader::pluginarray::iterator ladspaloader_find(unsigned long uniqueid);
    virtual void ladspaloader_set_plugins(LadspaLoader::pluginarray& new_plugins);
    virtual void pluginlist_append_rack(UiBuilderBase& ui);
    virtual void pluginlist_registerPlugin(Plugin *pl);
    virtual const std::string& conv_getIRFile(const char *id);
    virtual float get_tuner_freq();
    virtual void set_oscilloscope_mul_buffer(int a, unsigned int b);
    virtual int get_oscilloscope_mul_buffer();
    virtual float *get_oscilloscope_buffer();
    virtual void clear_oscilloscope_buffer();
    virtual bool oscilloscope_plugin_box_visible();
    virtual sigc::signal<void, int>& signal_oscilloscope_post_pre();
    virtual sigc::signal<void, bool>& signal_oscilloscope_visible();
    virtual sigc::signal<int, bool>& signal_oscilloscope_activation();
    virtual sigc::signal<void, unsigned int>& signal_oscilloscope_size_change();
    virtual float maxlevel_get(int channel);
    virtual void maxlevel_reset();
    virtual bool midiaudiobuffer_get_midistat();
    virtual MidiAudioBuffer::Load midiaudiobuffer_jack_load_status();
    virtual gx_system::CmdlineOptions& get_options() const;
    virtual void start_socket(sigc::slot<void> quit_mainloop, int port);
    virtual sigc::signal<void>& signal_conv_settings_changed(const char *id);
    virtual sigc::signal<void,const Glib::ustring&,const Glib::ustring&>& tuner_switcher_signal_display();
    virtual sigc::signal<void,TunerSwitcher::SwitcherState>& tuner_switcher_signal_set_state();
    virtual sigc::signal<void>& tuner_switcher_signal_selection_done();
    virtual sigc::signal<void,GxEngineState>& signal_state_change();
    virtual Glib::Dispatcher& signal_jack_load_change();
    virtual void tuner_used_for_display(bool on);
    virtual void tuner_used_for_livedisplay(bool on);
    virtual void start_ramp_down();
    virtual void wait_ramp_down_finished();
    virtual void set_stateflag(ModuleSequencer::StateFlag flag); // RT
    // tuner_switcher
    virtual bool get_tuner_switcher_active();
    virtual void tuner_switcher_activate(bool v);
    virtual bool tuner_switcher_deactivate();
    // preset
    virtual bool setting_is_preset();
    virtual const Glib::ustring& get_current_bank();
    virtual gx_system::PresetFile *get_current_bank_file();
    virtual const Glib::ustring& get_current_name();
    virtual gx_system::PresetFile* get_bank_file(const Glib::ustring& bank) const;
    virtual Glib::ustring get_bank_name(int n);
    virtual void load_preset(gx_system::PresetFile *pf, const Glib::ustring& name);
    virtual void loadstate();
    virtual int bank_size();
    virtual bool settings_is_loading();
    virtual void create_default_scratch_preset();
    virtual void set_statefilename(const std::string& fn);
    virtual void save_to_state(bool preserve_preset=false);
    virtual Glib::RefPtr<gx_preset::PluginPresetList> load_plugin_preset_list(const Glib::ustring& id, bool factory) const;
    virtual void disable_autosave(bool v);
    virtual sigc::signal<void>& signal_selection_changed();
    virtual sigc::signal<void>& signal_presetlist_changed();
    virtual bool bank_strip_preset_postfix(std::string& name);
    virtual std::string bank_decode_filename(const std::string& s);
    virtual void bank_make_valid_utf8(Glib::ustring& s);
    virtual void bank_make_bank_unique(Glib::ustring& name, std::string *file = 0);
    virtual void bank_insert(gx_system::PresetFile* f);
    virtual bool rename_bank(const Glib::ustring& oldname, const Glib::ustring& newname, const std::string& newfile);
    virtual bool rename_preset(gx_system::PresetFile& pf, const Glib::ustring& oldname, const Glib::ustring& newname);
    virtual void bank_reorder(const std::vector<Glib::ustring>& neworder);
    virtual void reorder_preset(gx_system::PresetFile& pf, const std::vector<Glib::ustring>& neworder);
    virtual bool bank_check_reparse();
    virtual void erase_preset(gx_system::PresetFile& pf, const Glib::ustring& name);
    virtual gx_system::PresetFile *bank_get_file(const Glib::ustring& bank) const;
    virtual gx_system::PresetBanks::iterator bank_begin();
    virtual gx_system::PresetBanks::iterator bank_end();
    virtual void pf_append(gx_system::PresetFile& pf, const Glib::ustring& src, gx_system::PresetFile& pftgt, const Glib::ustring& name);
    virtual void pf_insert_before(gx_system::PresetFile& pf, const Glib::ustring& src, gx_system::PresetFile& pftgt, const Glib::ustring& pos, const Glib::ustring& name);
    virtual void pf_insert_after(gx_system::PresetFile& pf, const Glib::ustring& src, gx_system::PresetFile& pftgt, const Glib::ustring& pos, const Glib::ustring& name);
    virtual bool convert_preset(gx_system::PresetFile& pf);
    virtual bool bank_remove(const Glib::ustring& bank);
    virtual void bank_save();
    virtual void set_source_to_state();
    virtual void make_bank_unique(Glib::ustring& name, std::string *file = 0);
    virtual void pf_save(gx_system::PresetFile& pf, const Glib::ustring& name);

    // jack
    virtual gx_jack::GxJack *get_jack();
    // pmap
    virtual Parameter& get_parameter(const char *p);
    virtual Parameter& get_parameter(const std::string& id);
    virtual void set_init_values();
    virtual bool parameter_hasId(const char *p);
    virtual bool parameter_hasId(const std::string& id);
    virtual void reset_unit(Glib::ustring group_id) const;
    virtual bool parameter_unit_has_std_values(Glib::ustring group_id) const;
    virtual void set_parameter_value(const std::string& id, int value);
    virtual void set_parameter_value(const std::string& id, bool value);
    virtual void set_parameter_value(const std::string& id, float value);
    // MidiControllerList
    virtual bool midi_get_config_mode();
    virtual void midi_set_config_mode(bool v, int ctl=-1);
    virtual sigc::signal<void,int>& signal_midi_new_program();
    virtual sigc::signal<void>& signal_midi_changed();
    virtual int midi_size();
    virtual midi_controller_list& midi_get(int n);
    virtual void midi_deleteParameter(Parameter& param, bool quiet = false);
    virtual int midi_get_current_control();
    virtual void midi_set_current_control(int v);
    virtual void midi_modifyCurrent(Parameter& param, float lower, float upper, bool toggle);
    virtual int midi_param2controller(Parameter& param, const MidiController** p);
    // cheat
    virtual ConvolverMonoAdapter& get_mono_convolver();
    virtual ConvolverStereoAdapter& get_stereo_convolver();
};

} // namespace gx_engine

#endif  // SRC_HEADERS_MACHINE_H_
