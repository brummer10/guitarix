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

/* ------- This is the GUI namespace ------- */

#pragma once

#ifndef SRC_HEADERS_GX_GUI_HELPERS_H_
#define SRC_HEADERS_GX_GUI_HELPERS_H_

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
    void                  gx_load_factory_file(int i);
    bool                  gx_nth_preset(unsigned char pgm);

    Gtk::MenuItem* const  gx_get_preset_item_from_name(int, const string&);
    //GtkWidget*            ffpresmenu[GX_NUM_OF_FACTORY_PRESET];
    GtkWidget*            fpresmenu;
    //GtkWidget*            presmenu[GX_NUM_OF_PRESET_LISTS];
    GtkWidget*            presMenu[GX_NUM_OF_PRESET_LISTS];

 private:
    string                old_preset_name;
    static bool gx_build_preset_list();
    static int gx_get_single_preset_menu_pos(const string& presname, const gint lindex);
    static void gx_load_factory_preset(Gtk::MenuItem *menuitem, int load_preset);
    vector<string>        fplist[GX_NUM_OF_FACTORY_PRESET];
    vector<Gtk::MenuItem*>  fpm_list[GX_NUM_OF_FACTORY_PRESET];
    vector<string>        plist;
    vector<Gtk::MenuItem*>  pm_list[GX_NUM_OF_PRESET_LISTS];
};

extern GxPreset gxpreset;

} // !namespace gx_preset

namespace gx_gui {

/* --------------  function declarations ---------------- */
GtkWidget *load_toplevel(GtkBuilder *builder, const char* filename, const char* windowname);
gboolean gx_hide_eq(GtkWidget *widget, gpointer   data );

/* guitarix skin related functions */
void gx_change_skin(Gtk::RadioMenuItem& item, int idx);
void gx_cycle_through_skin(GtkWidget *widget, gpointer arg);
bool gx_update_skin(const gint idx, const char* calling_func);
void gx_update_skin_menu_item(const int);
void gx_actualize_skin_index(gx_system::SkinHandling& skin, const string& skin_name);

/* jack client and port mapping functions */
bool gx_start_jack_dialog();

/* choice dialog windows */
void gx_get_text_entry(GtkEntry*, Glib::ustring&);

gint gx_choice_dialog_with_text_entry(
    const char* window_title,
    const char* msg,
    const char* label1,
    const char* label2,
    const gint  resp1,
    const gint  resp2,
    const gint  default_response,
    GCallback   func
    );

gint gx_choice_dialog_without_entry(
    const char* window_title,
    const char* msg,
    const char* label1,
    const char* label2,
    const gint  resp1,
    const gint  resp2,
    const gint  default_response
    );

gint gx_nchoice_dialog_without_entry(
    const char* window_title,
    const char* msg,
    const guint nchoice,
    const char* label[],
    const gint  resp[],
    const gint  default_response
    );

/* extra GUI helpers */
void gx_midi_out(Gtk::CheckMenuItem& menuitem);
void gx_patch();

void gx_show_extended_settings(GtkWidget*, gpointer);
void gx_reset_units(Glib::ustring group_id);
void gx_reset_effects(GtkWidget*, gpointer);
void gx_show_about();

void gx_show_menu_settings(GtkWidget*, gpointer);
void gx_user_disable_latency_warn(GtkWidget*, gpointer);
gint gx_wait_latency_warn();
int  gx_message_popup(const char*);
void show_error_msg(const string& msg);

gboolean gx_delete_event(GtkWidget*, gpointer);
gboolean gx_set_default_size(gpointer data);
gboolean gx_set_default_ssize(gpointer data);
gboolean gx_set_sresizeable(gpointer data);
gboolean gx_set_default(gpointer data);
gboolean gx_set_resizeable(gpointer data);

/* -------------------------------------------------------------------------- */
} /* end of gx_gui namespace */
#endif  // SRC_HEADERS_GX_GUI_HELPERS_H_
