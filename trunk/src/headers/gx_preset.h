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

#include <string>
#include <sstream>

// number of preset action lists
#define GX_NUM_OF_PRESET_LISTS (3)

// preset action index
#define LOAD_PRESET_LIST   (0)
#define SAVE_PRESET_LIST   (1)
#define RENAME_PRESET_LIST (2)
// #define DELETE_PRESET_LIST (3)

// number of factory preset lists
#define GX_NUM_OF_FACTORY_PRESET (5)

namespace gx_preset {

/****************************************************************
 ** class BasicIO, class PresetIO, class StateIO, class GxSettings
 */

class PresetIO: public gx_system::AbstractPresetIO {
private:
    gx_gui::MidiControllerList& mctrl;
    gx_engine::ConvolverAdapter& convolver;
    gx_gui::paramlist plist;
    gx_gui::MidiControllerList::controller_array *m;
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
    PresetIO(gx_gui::MidiControllerList& mctrl, gx_engine::ConvolverAdapter& cvr);
    ~PresetIO();
    void read_preset(gx_system::JsonParser &jp, const gx_system::SettingsFileHeader&);
    void commit_preset();
    void write_preset(gx_system::JsonWriter& jw);
    void copy_preset(gx_system::JsonParser &jp, const gx_system::SettingsFileHeader&, gx_system::JsonWriter &jw);
};

class StateIO: public gx_system::AbstractStateIO, private PresetIO {
private:
    gx_gui::MidiStandardControllers& midi_std_control;
    gx_jack::GxJack& jack;
public:
    StateIO(gx_gui::MidiControllerList& mctrl, gx_engine::ConvolverAdapter& cvr,
	    gx_gui::MidiStandardControllers& mstdctr, gx_jack::GxJack& jack);
    ~StateIO();
    void read_state(gx_system::JsonParser &jp, const gx_system::SettingsFileHeader&);
    void commit_state();
    void write_state(gx_system::JsonWriter &jw);
};

class GxSettings: public gx_system::GxSettingsBase {
private:
    gx_preset::PresetIO   preset_io;
    gx_preset::StateIO    state_io;
    gx_gui::FileParameter presetfile_parameter;
    bool                  state_loaded;
    gx_jack::GxJack&      jack;
    gx_system::CmdlineOptions& options;
    static GxSettings *instance;//FIXME
    void presetfile_changed();
    void exit_handler(bool otherthread);
    void jack_client_changed();
    string make_state_filename();
    string make_std_preset_filename();
    void check_convert_presetfile();
    static string get_default_presetfile(gx_system::CmdlineOptions& opt);
public:
    GxSettings(gx_system::CmdlineOptions& opt, gx_jack::GxJack& jack, gx_engine::ConvolverAdapter& cvr,
	       gx_gui::MidiStandardControllers& mstdctr, gx_gui::MidiControllerList& mctrl,
	       gx_engine::ModuleSequencer& seq);
    ~GxSettings();
    static void check_settings_dir(gx_system::CmdlineOptions& opt);
    void load(Source src, const string& name = "", const string& factory = "");
    bool rename_preset(const string& name, const string& newname);
    static GxSettings& get_instance() { return *instance; }
    void set_std_presetfile() { presetfile_parameter.set_std_value(); }
    string get_preset_filename() { return presetfile_parameter.get_path(); }
    string get_preset_dirname() { return presetfile_parameter.get_directory_path(); }
    void copy_preset_file(const string& destination) { presetfile_parameter.copy(destination); }
    sigc::signal<void>& signal_presetfile_changed() { return presetfile_parameter.signal_changed(); }
};

/****************************************************************
 ** class GxPreset
 */

class GxPreset {
 private:
    string                gx_get_accel_path(int lindex);
    void                  gx_add_preset_to_menus(const string&);
    void                  gx_save_preset(const gchar*, bool);
    void                  gx_add_single_preset_menu_item(const string&,
                                                         const gint,
                                                         GCallback);
 public:
    static void           gx_save_newpreset_dialog(GtkMenuItem*, gpointer);
    static void           gx_save_oldpreset(GtkMenuItem*, gpointer);
    static void           gx_save_newpreset(GtkEntry* entry);
    static void           gx_load_preset_file(const gchar*, bool);
    static void           gx_save_preset_file(const gchar*, bool);
    static void           gx_load_preset(GtkMenuItem*, gpointer);
    static void           gx_save_main_setting(GtkMenuItem*, gpointer);
    static void           gx_rename_preset(GtkEntry* entry);
    static void           gx_rename_preset_dialog(GtkMenuItem*, gpointer);
    static void           gx_rename_active_preset_dialog(GtkWidget*, gpointer);
    static void           gx_delete_preset(GtkMenuItem*, gpointer);
    static void           gx_delete_preset_dialog(GtkMenuItem*, gpointer);
    static void           gx_delete_active_preset_dialog(GtkWidget*, gpointer);
    static void           gx_delete_all_presets_dialog(GtkMenuItem*, gpointer);
    static void           gx_next_preset(GtkWidget*, gpointer);
    static void           gx_previous_preset(GtkWidget*, gpointer);

    void                  gx_delete_all_presets();
    void                  gx_recall_settings_file();
    void                  gx_cleanup_preset_name(Glib::ustring& presname);
    void                  gx_refresh_preset_menus();
    void                  gx_load_factory_file(int i);
    bool                  gx_nth_preset(unsigned char pgm);

    GtkMenuItem* const    gx_get_preset_item_from_name(int, const string&);
    GtkWidget*            ffpresmenu[GX_NUM_OF_FACTORY_PRESET];
    GtkWidget*            fpresmenu;
    GtkWidget*            presmenu[GX_NUM_OF_PRESET_LISTS];
    GtkWidget*            presMenu[GX_NUM_OF_PRESET_LISTS];

 private:
    string                old_preset_name;
    static bool gx_build_preset_list();
    static int gx_get_single_preset_menu_pos(const string& presname, const gint lindex);
    static void gx_load_factory_preset(GtkMenuItem *menuitem, gpointer load_preset);
    vector<string>        fplist[GX_NUM_OF_FACTORY_PRESET];
    vector<GtkMenuItem*>  fpm_list[GX_NUM_OF_FACTORY_PRESET];
    vector<string>        plist;
    vector<GtkMenuItem*>  pm_list[GX_NUM_OF_PRESET_LISTS];
};

extern GxPreset gxpreset;

/* --------------------------------------------------------------------- */
} /* end of gx_preset namespace */
#endif  // SRC_HEADERS_GX_PRESET_H_
