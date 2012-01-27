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
 *
 *    This is the gx_head GUI related functionality of preset handling
 *
 * ----------------------------------------------------------------------------
 */

#pragma once

#ifndef SRC_HEADERS_GX_PRESTE_OPTIONS_H_
#define SRC_HEADERS_GX_PRESTE_OPTIONS_H_

// number of preset action lists
#define GX_NUM_OF_PRESET_LISTS (3)

// preset action index
#define LOAD_PRESET_LIST   (0)
#define SAVE_PRESET_LIST   (1)
#define RENAME_PRESET_LIST (2)


namespace gx_preset {

/****************************************************************
 ** class GxPreset
 */

class GxPreset {
 private:
    typedef void (*callback_with_menuitem)(Gtk::MenuItem*);
    string                gx_get_accel_path(int lindex);
    void                  gx_add_preset_to_menus(const string&);
    void                  gx_save_preset(const gchar*, bool);
    void                  gx_add_single_preset_menu_item(const string&,
                                                         const gint,
                                                         callback_with_menuitem);
 public:
    static void           gx_save_newpreset_dialog();
    static void           gx_save_oldpreset(Gtk::MenuItem*);
    static void           gx_save_active_preset();
    static void           gx_save_newpreset(GtkEntry* entry);
    static void           gx_load_preset_file();
    static void           gx_save_preset_file();
    static void           gx_load_preset(Gtk::MenuItem*);
    static void           gx_save_main_setting();
    static void           gx_rename_preset(GtkEntry* entry);
    static void           gx_rename_preset_dialog(Gtk::MenuItem*);
    static void           gx_rename_active_preset_dialog();
    static void           gx_delete_preset(Gtk::MenuItem*);
    static void           gx_delete_preset_dialog(Gtk::MenuItem*);
    static void           gx_delete_active_preset_dialog();
    static void           gx_delete_all_presets_dialog();
    static void           gx_next_preset();
    static void           gx_previous_preset();

    void                  gx_delete_all_presets();
    void                  gx_recall_settings_file();
    void                  gx_cleanup_preset_name(Glib::ustring& presname);
    void                  gx_refresh_preset_menus();
    void                  gx_append_factory_file(const string& name, Gtk::Menu& menu);
    bool                  gx_nth_preset(unsigned char pgm);

    Gtk::MenuItem* const  gx_get_preset_item_from_name(int, const string&);
    GtkWidget*            fpresmenu;
    GtkWidget*            presMenu[GX_NUM_OF_PRESET_LISTS];

 private:
    string                old_preset_name;
    static bool gx_build_preset_list();
    static int gx_get_single_preset_menu_pos(const string& presname, const gint lindex);
    static void gx_load_factory_preset(
	const string& factory_name, const string& preset_name);
    vector<string>        plist;  // name list of loadable presets
    vector<Gtk::MenuItem*> pm_list[GX_NUM_OF_PRESET_LISTS];
};

extern GxPreset gxpreset;

} // !namespace gx_preset

#endif  // SRC_HEADERS_GX_PRESTE_OPTIONS_H_

