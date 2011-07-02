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
#define GX_NUM_OF_FACTORY_PRESET (3)

namespace gx_preset {
extern gx_gui::FileParameter gx_preset_file;
extern gx_gui::FileParameter gx_factory_preset_file;

/* function declarations */
string gx_get_accel_path(int lindex);

void  gx_save_newpreset_dialog(GtkMenuItem*, gpointer);
void  gx_save_newpreset(GtkEntry* entry);
void  gx_save_preset(const gchar*, bool);
void  gx_save_oldpreset(GtkMenuItem*, gpointer);

void  gx_save_preset_file(const gchar*, bool);
void  gx_load_preset_file(const gchar*, bool);

void  gx_load_preset(GtkMenuItem*, gpointer);
void  gx_recall_settings_file(const string *filename = 0);
void  gx_recall_main_setting(GtkMenuItem*, gpointer);
void  gx_save_main_setting(GtkMenuItem*, gpointer);

void  gx_load_factory_file(int i);

void  gx_rename_preset(GtkEntry* entry);
void  gx_rename_preset_dialog(GtkMenuItem*, gpointer);
void  gx_rename_active_preset_dialog(GtkWidget*, gpointer);

void  gx_delete_preset(GtkMenuItem*, gpointer);
void  gx_delete_preset_dialog(GtkMenuItem*, gpointer);
void  gx_delete_active_preset_dialog(GtkWidget*, gpointer);

void  gx_delete_all_presets_dialog(GtkMenuItem*, gpointer);
void  gx_delete_all_presets();

void  gx_add_preset_to_menus(const string&);
void  gx_add_single_preset_menu_item(const string&,
                                     const gint,
                                     GCallback);

void  gx_refresh_preset_menus();
void  gx_cleanup_preset_name(string& presname);

bool gx_nth_preset(unsigned char pgm);
void  gx_next_preset(GtkWidget*, gpointer);
void  gx_previous_preset(GtkWidget*, gpointer);

GtkMenuItem* const gx_get_preset_item_from_name(int, const string&);

void init();

/* --------------------------------------------------------------------- */
} /* end of gx_preset namespace */
#endif  // SRC_HEADERS_GX_PRESET_H_
