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

namespace gx_gui {

/* --------------  function declarations ---------------- */
gboolean gx_hide_eq(GtkWidget *widget, gpointer   data );

/* guitarix skin related functions */
void gx_change_skin(Gtk::RadioMenuItem& item, int idx);
void gx_cycle_through_skin(GtkWidget *widget, gpointer arg);
bool gx_update_skin(const gint idx, const char* calling_func);
void gx_update_skin_menu_item(const int);
void gx_actualize_skin_index(gx_system::SkinHandling& skin, const string& skin_name);

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
void gx_patch();

void gx_show_extended_settings(GtkWidget*, gpointer);
void gx_reset_units(gx_engine::ParamMap& pmap, Glib::ustring group_id);
void gx_show_about();
void gx_show_help();

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

