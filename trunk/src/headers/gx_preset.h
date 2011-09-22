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
    static void           gx_recall_main_setting(GtkMenuItem*, gpointer);
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
    void                  gx_recall_settings_file(const string *filename = 0);
    void                  gx_cleanup_preset_name(string& presname);
    void                  gx_refresh_preset_menus();
    void                  gx_load_factory_file(int i);
    void                  init();
    
    string                gx_current_preset;
    string                gx_factory_preset;
    string                old_preset_name;

    bool                  gx_nth_preset(unsigned char pgm);
    bool                  setting_is_preset;
    bool                  setting_is_factory;

    GtkMenuItem* const    gx_get_preset_item_from_name(int, const string&);
    GtkWidget*            ffpresmenu[GX_NUM_OF_FACTORY_PRESET];
    GtkWidget*            fpresmenu;
    GtkWidget*            presmenu[GX_NUM_OF_PRESET_LISTS];
    GtkWidget*            presMenu[GX_NUM_OF_PRESET_LISTS];

    vector<string>        fplist[GX_NUM_OF_FACTORY_PRESET];
    vector<GtkMenuItem*>  fpm_list[GX_NUM_OF_FACTORY_PRESET];
    vector<string>        plist;
    vector<GtkMenuItem*>  pm_list[GX_NUM_OF_PRESET_LISTS];
};
extern GxPreset gxpreset;

extern gx_gui::FileParameter gx_preset_file;
extern gx_gui::FileParameter gx_factory_preset_file;

/* --------------------------------------------------------------------- */
} /* end of gx_preset namespace */
#endif  // SRC_HEADERS_GX_PRESET_H_

