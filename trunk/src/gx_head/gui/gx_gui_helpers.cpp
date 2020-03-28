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
 *    This is the gx_head GUI related functionality
 *
 * ----------------------------------------------------------------------------
 */

#include "guitarix.h"      //  NOLINT

/* --------------------------- gx_gui namespace ------------------------ */
namespace gx_gui {


void show_error_msg(const string& msg) {
    Gtk::MessageDialog dialog(
	msg, false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_CLOSE, true);
    dialog.set_title("gx_head");
    dialog.set_keep_above();
    dialog.run();
}

void child_set_property(Gtk::Container& container, Gtk::Widget& child, const char *property_name, bool value) {
    GValue v = {0};
    g_value_init(&v, G_TYPE_BOOLEAN);
    g_value_set_boolean(&v, value);
    gtk_container_child_set_property(container.gobj(), child.gobj(), property_name, &v);
}

Glib::ustring logarithmic_format_value(double v, int prec) {
    if (v < -4) {
	return Glib::ustring::format(std::setprecision(prec+1), pow(10.0,v));
    } else {
	return Glib::ustring::format(std::fixed, std::setprecision(prec-floor(v)), pow(10.0,v));
    }
}

int logarithmic_input_value(gpointer obj, gpointer nv)
{
    GtkEntry *entry = GTK_ENTRY(obj);
    double *new_val = static_cast<double*>(nv);
    gchar *err = NULL;
    *new_val = g_strtod(gtk_entry_get_text(entry), &err);
    if (*err)
	return GTK_INPUT_ERROR;
    else {
	*new_val = log10(*new_val);
	return TRUE;
    }
}

/****************************************************************
 ** WaitCursor
 */

WaitCursor::WaitCursor(Gtk::Window *window) {
    gdk_window = window->get_window();
    if (!gdk_window) {
	return;
    }
    Glib::RefPtr<Gdk::Cursor> cursor(
	Gdk::Cursor::create(window->get_display(), Gdk::WATCH));
    gdk_window->set_cursor(cursor);
    while(Gtk::Main::events_pending()) {
        Gtk::Main::iteration(false);
    }
}

WaitCursor::~WaitCursor() {
    if (gdk_window) {
	gdk_window->set_cursor();
    }
}

/****************************************************************
 ** message boxes
 */

// ---- choice dialog without text entry
gint gx_nchoice_dialog_without_entry(
    const char* window_title,
    const char* msg,
    const guint nchoice,
    const char* label[],
    const gint  resp[],
    const gint default_response,
    Glib::RefPtr<Gdk::Pixbuf> gw_ib) {
    auto dialog = Gtk::Dialog(window_title);
    auto text_label = Gtk::Label();
    auto image = Gtk::Image(gw_ib->scale_simple(64, 64, Gdk::INTERP_BILINEAR));
    
    text_label.set_markup(msg);
    text_label.set_margin_start(10);
    text_label.set_margin_end(10);
    text_label.set_margin_top(10);
    text_label.set_margin_bottom(10);
    dialog.get_content_area()->add(text_label);

    image.set_halign(Gtk::ALIGN_FILL);
    dialog.get_action_area()->add(image);
    for (guint i = 0; i < nchoice; i++) {
        dialog.add_button(label[i], resp[i]);
    }
    dialog.set_default_response(default_response);
    //dialog.set_keep_above(true);

    text_label.show();
    image.show();

    // since gx_nchoice_dialog_without_entry is only used for the
    // jack starter dialog (FIXME: cleanup...):
    // little hack to set the window non-modal
    // after gtk_dialog_run() forced it to modal
    // needed in case an error window is already open
    // or gets opened by an background handler
    dialog.signal_map().connect([&](){ dialog.set_modal(false); });

    // --- run dialog and check response
    return dialog.run();
}

// ---- popup warning
int gx_message_popup(const char* msg) {
    // check msg validity
    if (!msg) {
        gx_print_warning("Message Popup",
                         string(_("warning message does not exist")));
        return -1;
    }

    // build popup window
    auto about = Gtk::Dialog();
    about.set_name("MessagePopup");
    auto label = Gtk::Label();
    label.set_markup(msg);
    label.set_selectable(true);
    label.set_margin_start(10);
    label.set_margin_end(10);
    label.set_margin_top(10);
    label.set_margin_bottom(10);
    about.get_content_area()->add(label);
    about.add_button(_("_OK"), Gtk::RESPONSE_ACCEPT);
    label.show();
    return about.run();
}

} // end namespace gx_gui
