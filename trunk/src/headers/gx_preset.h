/*
 * Copyright (C) 2009, 2010 Hermann Meyer, James Warden, Andreas Degert
 * Copyright (C) 2011 Pete Shorthose
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
 * --------------------------------------------------------------------------
 */

/* ------- This is the preset namespace ------- */

#pragma once

#ifndef SRC_HEADERS_GX_PRESET_H_
#define SRC_HEADERS_GX_PRESET_H_

class PosixSignals;

namespace gx_preset {

/****************************************************************
 ** class BasicIO, class PresetIO, class StateIO, class GxSettings
 */

class PresetIO: public gx_system::AbstractPresetIO {
private:
    gx_engine::MidiControllerList& mctrl;
    gx_engine::ConvolverAdapter& convolver;
    gx_engine::ParamMap& param;
    gx_system::CmdlineOptions& opt;
    gx_engine::paramlist plist;
    gx_engine::MidiControllerList::controller_array *m;
    gx_engine::GxJConvSettings *jcset;
    void read_parameters(gx_system::JsonParser &jp, bool preset);
    void write_parameters(gx_system::JsonWriter &w, bool preset);
    void clear();
    bool midi_in_preset();
    void read_intern(gx_system::JsonParser &jp, bool *has_midi, const gx_system::SettingsFileHeader& head);
    void fixup_parameters(const gx_system::SettingsFileHeader& head);
    void write_intern(gx_system::JsonWriter &w, bool write_midi);
    bool convert_old(gx_system::JsonParser &jp);
    friend class StateIO;
public:
    PresetIO(gx_engine::MidiControllerList& mctrl, gx_engine::ConvolverAdapter& cvr,
	     gx_engine::ParamMap& param, gx_system::CmdlineOptions& opt);
    ~PresetIO();
    void read_preset(gx_system::JsonParser &jp, const gx_system::SettingsFileHeader&);
    void commit_preset();
    void write_preset(gx_system::JsonWriter& jw);
    void copy_preset(gx_system::JsonParser &jp, const gx_system::SettingsFileHeader&, gx_system::JsonWriter &jw);
};

class StateIO: public gx_system::AbstractStateIO, private PresetIO {
private:
    gx_engine::MidiStandardControllers& midi_std_control;
    gx_jack::GxJack& jack;
public:
    StateIO(gx_engine::MidiControllerList& mctrl, gx_engine::ConvolverAdapter& cvr,
	    gx_engine::ParamMap& param, gx_engine::MidiStandardControllers& mstdctr,
	    gx_jack::GxJack& jack, gx_system::CmdlineOptions& opt);
    ~StateIO();
    void read_state(gx_system::JsonParser &jp, const gx_system::SettingsFileHeader&);
    void commit_state();
    void write_state(gx_system::JsonWriter &jw, bool preserve_preset);
};

class PluginPresetList: public Glib::Object {
private:
    std::string filename;
    gx_engine::ParamMap& pmap;
    gx_engine::MidiControllerList& mctrl;
    ifstream is;
    gx_system::JsonParser jp;
    PluginPresetList(const std::string& fname, gx_engine::ParamMap& pmap, gx_engine::MidiControllerList& mctrl_);
public:
    static Glib::RefPtr<PluginPresetList> create(const std::string& fname, gx_engine::ParamMap& pmap, gx_engine::MidiControllerList& mctrl);
    bool start();
    bool next(Glib::ustring& name, bool *is_set = 0);
    void set(const Glib::ustring& name);
    void write_values(gx_system::JsonWriter& jw, std::string id);
    void save(const Glib::ustring& name, const std::string& id);
    void remove(const Glib::ustring& name);
};

class GxSettings: public sigc::trackable, public gx_system::GxSettingsBase {
private:
    gx_engine::ParamMap&  param;
    gx_preset::PresetIO   preset_io;
    gx_preset::StateIO    state_io;
    bool                  state_loaded;
    bool                  no_autosave;
    gx_jack::GxJack&      jack;
    gx_engine::MidiControllerList& mctrl;
    gx_system::CmdlineOptions& options;
    gx_engine::StringParameter& preset_parameter;
    gx_engine::StringParameter& bank_parameter;
    void exit_handler(bool otherthread);
    void jack_client_changed();
    string make_state_filename();
    string make_default_state_filename();
    static bool check_create_config_dir(const Glib::ustring& dir);
    static GxSettings *instance;
    friend class ::PosixSignals;
public:
    using GxSettingsBase::banks;
    GxSettings(gx_system::CmdlineOptions& opt, gx_jack::GxJack& jack, gx_engine::ConvolverAdapter& cvr,
	       gx_engine::MidiStandardControllers& mstdctr, gx_engine::MidiControllerList& mctrl,
	       gx_engine::ModuleSequencer& seq, gx_engine::ParamMap& param);
    ~GxSettings();
    inline gx_engine::ParamMap&  get_param() const { return param; }
    inline gx_system::CmdlineOptions& get_options() const { return options; }
    static bool check_settings_dir(gx_system::CmdlineOptions& opt, bool *need_new_preset);
    void loadstate();
    bool get_auto_save_state() { return no_autosave;}
    void disable_autosave(bool v) { no_autosave = v; }
    void auto_save_state();
    Glib::RefPtr<PluginPresetList> load_plugin_preset_list(const Glib::ustring& id, bool factory) const;
    void create_default_scratch_preset();
};

/* --------------------------------------------------------------------- */
} /* end of gx_preset namespace */
#endif  // SRC_HEADERS_GX_PRESET_H_
