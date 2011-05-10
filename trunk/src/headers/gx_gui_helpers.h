/*
 * Copyright (C) 2009, 2010 Hermann Meyer, James Warden, Andreas Degert
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

/* ------- This is the GUI namespace ------- */

#pragma once

#include <gtkmm/checkmenuitem.h>
#include <gtkmm/radiomenuitem.h>
namespace gx_gui
{

/* ---- linking menu items and parameter ---- */
class MenuCheckItem: public Gtk::CheckMenuItem
{
private:
	SwitchParameter* param;
	void on_my_activate();
public:
	//FIXME not gtk-2.12: MenuCheckItem() { set_use_underline(); }
	MenuCheckItem(): Gtk::CheckMenuItem("", true) {}
	void set_parameter(SwitchParameter *p);
	void add_parameter(SwitchParameter *p);
	SwitchParameter * get_parameter();
};

/* ---- linking menu items and parameter ---- */
class RadioCheckItem: public Gtk::RadioMenuItem
{
private:
	
	SwitchParameter* param;
	void on_my_toggled();
public:
	Gtk::RadioMenuItem::Group Group;
	//FIXME not gtk-2.12: MenuCheckItem() { set_use_underline(); }
	RadioCheckItem(): Gtk::RadioMenuItem(Group,"", true) {}
	void set_parameter(SwitchParameter *p);
	SwitchParameter * get_parameter();
};
/* --------------  function declarations ---------------- */
GtkWidget *load_toplevel(GtkBuilder *builder, const char* filename, const char* windowname);
gboolean gx_hide_eq( GtkWidget *widget, gpointer   data );

/* guitarix skin related functions */
unsigned int gx_fetch_available_skins();

void gx_change_skin(GtkCheckMenuItem *menuitem, gpointer arg);
void gx_cycle_through_skin(GtkWidget *widget, gpointer arg);
bool gx_update_skin(const gint idx, const char* calling_func);
void gx_update_skin_menu_item(const int);
void gx_actualize_skin_index(const string& skin_name);
bool gx_set_skin(GtkWidget *widget, gpointer data);
void gx_get_skin_change(float* fskin);
void gx_set_skin_change(float fskin);

/* engine status and switch */
void gx_refresh_engine_status_display();
void gx_engine_switch (GtkWidget* widget, gpointer arg);

/* jack client and port mapping functions */
void gx_jack_is_down();
void gx_jack_report_xrun();

/* choice dialog windows */
void gx_get_text_entry(GtkEntry*, string&);

gint gx_choice_dialog_with_text_entry (
	const char* window_title,
	const char* msg,
	const char* label1,
	const char* label2,
	const gint  resp1,
	const gint  resp2,
	const gint  default_response,
	GCallback   func
	);

gint gx_choice_dialog_without_entry (
	const char* window_title,
	const char* msg,
	const char* label1,
	const char* label2,
	const gint  resp1,
	const gint  resp2,
	const gint  default_response
	);

gint gx_nchoice_dialog_without_entry (
	const char* window_title,
	const char* msg,
	const guint nchoice,
	const char* label[],
	const gint  resp[],
	const gint  default_response
	);

/* extra GUI helpers */
void gx_midi_out               (GtkCheckMenuItem*, gpointer);
void gx_log_window             (GtkWidget*, gpointer);
void gx_patch                  (GtkCheckMenuItem*, gpointer );

void gx_systray_menu            (GtkWidget*, gpointer);
void gx_reset_units             (Glib::ustring group_id);
void gx_reset_effects           (GtkWidget*, gpointer);
void gx_show_about              (GtkWidget*, gpointer);

void cab_conv_restart();
void contrast_conv_restart();

void gx_show_extended_settings    (GtkWidget*, gpointer);
void gx_hide_extended_settings    (GtkWidget*, gpointer);
void gx_show_menu_settings        (GtkWidget*, gpointer);
void gx_user_disable_latency_warn (GtkWidget*, gpointer);
gint gx_wait_latency_warn         ();
int  gx_message_popup             (const char*);

gboolean gx_delete_event       (GtkWidget*, gpointer);

/* -------------------------------------------------------------------------- */
} /* end of gx_gui namespace */

