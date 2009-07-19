/* -*- mode: C++ -*-
 * Copyright (C) 2009 Hermann Meyer and James Warden
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
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 * --------------------------------------------------------------------------
 */

/* ------- This is the preset namespace ------- */

#pragma once

// number of preset action lists, can expand to 4 if required
#define GX_NUM_OF_PRESET_LISTS (2) 

// preset action index
#define LOAD_PRESET_LIST   (0)
#define SAVE_PRESET_LIST   (1)
#define RENAME_PRESET_LIST (2)
#define DELETE_PRESET_LIST (3)
    
namespace gx_preset
{
  /* function declarations */
  void  gx_build_preset_list();
    
  void  gx_save_newpreset_dialog (GtkMenuItem*, gpointer);
  void  gx_save_newpreset (GtkEntry*);
  void  gx_save_preset (const gchar*, bool);
  void  gx_save_oldpreset (GtkMenuItem*, gpointer);
    
  void  gx_load_preset (GtkMenuItem*, gpointer);
  void  gx_recall_main_setting(GtkMenuItem*, gpointer);
  void  gx_save_main_setting(GtkMenuItem*, gpointer);
    
  void  gx_rename_preset (GtkEntry*);
  void  gx_rename_preset_dialog (GtkMenuItem*, gpointer);
  void  gx_rename_active_preset_dialog(GtkWidget*, gpointer);
    
  void  gx_delete_preset(GtkMenuItem*, gpointer);
  void  gx_delete_preset_dialog (GtkMenuItem*, gpointer);
  void  gx_delete_active_preset_dialog(GtkWidget*, gpointer);
    
  void  gx_delete_all_presets_dialog(GtkMenuItem*, gpointer);
  void  gx_delete_all_presets();
    
  void  gx_add_preset_to_menus(const string&);
  void  gx_add_single_preset_menu_item(const string&,
				       const gint,
				       GCallback);
    
  void  gx_del_single_preset_menu_item(const string&,
				       const gint);
  void  gx_del_preset_from_menus(const string&);
  void  gx_refresh_preset_menus();
  void  gx_cleanup_preset_name(string& presname);
    
  void  gx_next_preset(GtkWidget*, gpointer);
  void  gx_previous_preset(GtkWidget*, gpointer);
    
  GtkMenuItem* const gx_get_preset_item_from_name(int, const string&);
  
  /* --------------------------------------------------------------------- */
} /* end of gx_preset namespace */
