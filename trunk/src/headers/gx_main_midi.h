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
 * ---------------------------------------------------------------------------
 *
 *    This file is part of the guitarix GUI main class
 *    Note: this header file depends on gx_parameter.h 
 *    and make use of the gx_engine namespace
 * 
 * ----------------------------------------------------------------------------
 */

#pragma once

#ifndef SRC_HEADERS_GX_MAIN_MIDI_H_
#define SRC_HEADERS_GX_MAIN_MIDI_H_

#ifndef SRC_HEADERS_GX_PARAMETER_H_
#include "./gx_parameter.h"
#endif

#include <glibmm.h>
#include <gtk/gtk.h>

#include <iomanip>
#include <cstring>
#include <string>

namespace gx_main_midi {
/****************************************************************
 ** MidiControllerTable
 */

class MidiControllerTable: public sigc::trackable {
 private:
    enum {RESPONSE_DELETE_SELECTED};
    static GtkWidget *window; // there can only be 1 window
    GtkToggleButton *togglebutton;
    GtkTreeSelection *selection;
    GtkListStore *store;
    Glib::RefPtr<Gtk::ToggleAction> menuaction;
    gx_engine::GxMachineBase& machine;
    sigc::connection midi_conn;
    static void response_cb(GtkWidget *widget, gint response_id, gpointer data);
    static void edited_cb(GtkCellRendererText *renderer, gchar *path,
                          gchar *new_text, gpointer data);
    static void destroy_cb(GtkWidget*, gpointer data);
    static void toggleButtonSetSwitch(GtkWidget *w, gpointer data);
    void set(bool v);
    void load();
    explicit MidiControllerTable(gx_engine::GxMachineBase& machine, Glib::RefPtr<Gtk::ToggleAction> item);
    ~MidiControllerTable();
 public:
    static void toggle(gx_engine::GxMachineBase& machine, Glib::RefPtr<Gtk::ToggleAction> item);
};

/*****************************************************************
 ** Midi Control
 */

class MidiConnect {
 private:
    enum { RESPONSE_DELETE = 1 };
    std::map<gx_engine::Parameter::toggle_type, const char*> toggle_behaviour_descriptions {
        { gx_engine::Parameter::toggle_type::OnOff, "off /on states transition toggle" },
        { gx_engine::Parameter::toggle_type::Constant, "constant state toggle" },
        { gx_engine::Parameter::toggle_type::Toggle, "toggle state" }
    };
    GtkTreeSelection* selection;
    GtkListStore* store;
    gx_engine::Parameter &param;
    gx_engine::GxMachineBase& machine;
    int current_control;
    GtkAdjustment* adj_lower;
    GtkAdjustment* adj_upper;
    GtkToggleButton *use_toggle;
    //
    GtkWidget* dialog;
    GtkWidget* entry_new;
    GtkWidget* label_desc;
    GtkWidget* toggle_behaviours;
    static string ctr_desc(int ctr);
    static const char *ctl_to_str(int n);
 public:
    MidiConnect(GdkEventButton *event, gx_engine::Parameter& param, gx_engine::GxMachineBase& machine);
    static void midi_response_cb(GtkWidget *widget, gint response_id, gpointer data);
    static void midi_destroy_cb(GtkWidget *widget, gpointer data);
    static void toggle_behaviours_visibility(GtkWidget *widget, gpointer data);
    static gboolean check_midi_cb(gpointer);
    static void changed_text_handler(GtkEditable *entry, gpointer data);
};

} // end namespace
#endif  // SRC_HEADERS_GX_MAIN_MIDI_H_

