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

namespace gx_preset {

/****************************************************************
 ** class BasicIO, class PresetIO, class StateIO, class GxSettings
 */

class PresetIO: public gx_system::AbstractPresetIO {
private:
    gx_engine::MidiControllerList& mctrl;
    gx_engine::ConvolverAdapter& convolver;
    gx_engine::ParamMap& param;
    const gx_system::CmdlineOptions& opt;
    gx_engine::paramlist plist;
    gx_engine::MidiControllerList::controller_array *m;
    gx_engine::GxJConvSettings jcset;
    void read_parameters(gx_system::JsonParser &jp, bool preset);
    void write_parameters(gx_system::JsonWriter &w, bool preset);
    void clear();
    bool midi_in_preset();
    void read_intern(gx_system::JsonParser &jp, bool *has_midi, const gx_system::SettingsFileHeader& head);
    void fixup_parameters(const gx_system::SettingsFileHeader& head);
    void write_intern(gx_system::JsonWriter &w, bool write_midi);
    friend class StateIO;
public:
    PresetIO(gx_engine::MidiControllerList& mctrl, gx_engine::ConvolverAdapter& cvr,
	     gx_engine::ParamMap& param, const gx_system::CmdlineOptions& opt);
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
	    gx_jack::GxJack& jack, const gx_system::CmdlineOptions& opt);
    ~StateIO();
    void read_state(gx_system::JsonParser &jp, const gx_system::SettingsFileHeader&);
    void commit_state();
    void write_state(gx_system::JsonWriter &jw, bool preserve_preset);
};

class GxSettings: public sigc::trackable, public gx_system::GxSettingsBase {
private:
    gx_preset::PresetIO   preset_io;
    gx_preset::StateIO    state_io;
    gx_engine::FileParameter& presetfile_parameter;
    bool                  state_loaded;
    bool                  no_autosave;
    gx_jack::GxJack&      jack;
    gx_system::CmdlineOptions& options;
    gx_engine::StringParameter& preset_parameter;
    gx_engine::StringParameter& factory_parameter;
    static GxSettings *instance;//FIXME
    void presetfile_changed();
    void exit_handler(bool otherthread);
    void jack_client_changed();
    string make_state_filename();
    string make_default_state_filename();
    string make_std_preset_filename();
    void check_convert_presetfile();
    void parse_factory_list();
    static bool check_create_config_dir(const Glib::ustring& dir);
    static string get_default_presetfile(gx_system::CmdlineOptions& opt);
public:
    using GxSettingsBase::banks;
    GxSettings(gx_system::CmdlineOptions& opt, gx_jack::GxJack& jack, gx_engine::ConvolverAdapter& cvr,
	       gx_engine::MidiStandardControllers& mstdctr, gx_engine::MidiControllerList& mctrl,
	       gx_engine::ModuleSequencer& seq, gx_engine::ParamMap& param);
    ~GxSettings();
    string get_displayname();
    static bool check_settings_dir(gx_system::CmdlineOptions& opt);
    void load(Source src, const string& name = "", const string& factory = "");
    void loadstate();
    void disable_autosave(bool v) { no_autosave = v; }
    void auto_save_state();
    static GxSettings& get_instance() { assert(instance); return *instance; }
    void set_std_presetfile() { presetfile_parameter.set_std_value(); }
    string get_preset_filename() { return presetfile_parameter.get_path(); }
    bool set_preset_file(const string& newfile);
    string get_preset_dirname() { return presetfile_parameter.get_directory_path(); }
    void copy_preset_file(const string& destination) { presetfile_parameter.copy(destination); }
    sigc::signal<void>& signal_presetfile_changed() { return presetfile_parameter.signal_changed(); }
};

/* --------------------------------------------------------------------- */
} /* end of gx_preset namespace */
#endif  // SRC_HEADERS_GX_PRESET_H_
