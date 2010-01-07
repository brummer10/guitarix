/*
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

/* ------- This is the GUI namespace ------- */

#pragma once

namespace gx_gui
{
  /* --------------  function declarations ---------------- */
  /* slow GTK threads, see GxMainInterface::run() */
  gboolean gx_refresh_meter_level    (gpointer arg);
  gboolean gx_refresh_oscilloscope   (gpointer args);
  gboolean gx_survive_jack_shutdown  (gpointer arg);
  gboolean gx_monitor_jack_clients   (gpointer args);
  gboolean gx_monitor_jack_ports     (gpointer args);
  gboolean gx_update_all_gui         (gpointer args);
  gboolean gx_check_startup          (gpointer args);
  gboolean gx_hide_eq( GtkWidget *widget, gpointer   data );

  gboolean box12_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data);
  gboolean box11_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data);
  gboolean box10_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data);
  gboolean box9_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data);
  gboolean box8_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data);
  gboolean box7_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data);
  gboolean box6_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data);
  gboolean box5_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data);
  gboolean box4_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data);
  gboolean box3_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data);
  gboolean box2_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data);
  gboolean box1_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data);
  gboolean box_expose (GtkWidget *wi, GdkEventExpose *ev, gpointer user_data);
  gboolean label_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data);

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
  void gx_show_portmap_window (GtkWidget* widget, gpointer arg);
  void gx_hide_portmap_window (GtkWidget* widget, gpointer arg);

  void gx_refresh_portconn_status(GtkWidget* button, gpointer data);
  void gx_cycle_through_client_tabs(GtkWidget* item, gpointer data);

  void gx_queue_client_port(const string, const string, const int);
  void gx_queue_client(const string);

  void gx_dequeue_client_port(const string, const string, const int);
  void gx_dequeue_client(const string);

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
  void gx_show_oscilloscope      (GtkCheckMenuItem*, gpointer);
  void gx_tuner                  (GtkCheckMenuItem*, gpointer);
  void gx_midi_out               (GtkCheckMenuItem*, gpointer);
  void gx_log_window             (GtkWidget*, gpointer);

  void gx_init_pixmaps();
  void gx_systray_menu            (GtkWidget*, gpointer);
  void gx_reset_units             (GtkWidget*, gpointer);
  void gx_reset_effects           (GtkWidget*, gpointer);
  void gx_show_about              (GtkWidget*, gpointer);

  void gx_show_extended_settings    (GtkWidget*, gpointer);
  void gx_hide_extended_settings    (GtkWidget*, gpointer);
  void gx_user_disable_latency_warn (GtkWidget*, gpointer);
  gint gx_wait_latency_warn         ();
  int  gx_message_popup             (const char*);

  gboolean gx_delete_event       (GtkWidget*, gpointer);

  void gx_meter_button_release(GdkEventButton* ev, gpointer arg);

  /* -------------------------------------------------------------------------- */
} /* end of gx_gui namespace */

