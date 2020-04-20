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

class WaitCursor {
private:
    Glib::RefPtr<Gdk::Window> gdk_window;
public:
    WaitCursor(Gtk::Window *window);
    ~WaitCursor();
};

gint gx_nchoice_dialog_without_entry(
    const char* window_title,
    const char* msg,
    const guint nchoice,
    const char* label[],
    const gint  resp[],
    const gint  default_response,
    Glib::RefPtr<Gdk::Pixbuf> gw_ib
    );

/* extra GUI helpers */
int  gx_message_popup(const char*);
void show_error_msg(const string& msg);
void child_set_property(Gtk::Container& container, Gtk::Widget& child, const char *property_name, bool value);
Glib::ustring logarithmic_format_value(double v, int prec);
int logarithmic_input_value(gpointer obj, gpointer nv);

/* -------------------------------------------------------------------------- */
} /* end of gx_gui namespace */
#endif  // SRC_HEADERS_GX_GUI_HELPERS_H_

