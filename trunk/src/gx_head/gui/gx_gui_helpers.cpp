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
 ** message boxes
 */

static void on_gx_nchoice_map(GtkWidget *w, gpointer data) {
    // since gx_nchoice_dialog_without_entry is only used for the
    // jack starter dialog (FIXME: cleanup...):
    // little hack to set the window non-modal
    // after gtk_dialog_run() forced it to modal
    // needed in case an error window is already open
    // or gets opened by an background handler
    gtk_window_set_modal(GTK_WINDOW(w), FALSE);
}

// ---- choice dialog without text entry
gint gx_nchoice_dialog_without_entry(
    const char* window_title,
    const char* msg,
    const guint nchoice,
    const char* label[],
    const gint  resp[],
    const gint default_response,
    Glib::RefPtr<Gdk::Pixbuf> gw_ib) {
    GtkWidget* dialog     = gtk_dialog_new();
    GtkWidget* text_label = gtk_label_new("");
    GdkPixbuf *pb         = gdk_pixbuf_scale_simple(gw_ib->gobj(), 64, 64, GDK_INTERP_BILINEAR);
    GtkWidget* image      = gtk_image_new_from_pixbuf(pb);
    
    gtk_label_set_markup(GTK_LABEL(text_label), msg);
    
    gtk_container_add_with_properties(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox), text_label, "padding", 10, "expand", TRUE, "fill", TRUE, NULL);
    gtk_container_add(GTK_CONTAINER(gtk_dialog_get_action_area(GTK_DIALOG(dialog))), image);
    for (guint i = 0; i < nchoice; i++)
        gtk_dialog_add_button(GTK_DIALOG(dialog), label[i], resp[i]);

    // set default
    gtk_dialog_set_has_separator(GTK_DIALOG(dialog), FALSE);
    gtk_dialog_set_default_response(GTK_DIALOG(dialog), default_response);
    gtk_window_set_title(GTK_WINDOW(dialog), window_title);
    gtk_window_set_keep_above(GTK_WINDOW(dialog), TRUE);

    gtk_widget_show(text_label);
    gtk_widget_show(image);

    g_signal_connect(dialog, "map", G_CALLBACK(on_gx_nchoice_map), NULL);

    // --- run dialog and check response
    gint response = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    return response;
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
    GtkWidget *about;
    GtkWidget *label;
    GtkWidget *ok_button;

    about = gtk_dialog_new();
    ok_button  = gtk_button_new_from_stock(GTK_STOCK_OK);

    label = gtk_label_new(msg);

    GtkStyle *style = gtk_widget_get_style(label);

    pango_font_description_set_size(style->font_desc, 10*PANGO_SCALE);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);

    gtk_widget_modify_font(label, style->font_desc);

    gtk_label_set_selectable(GTK_LABEL(label), TRUE);

    gtk_container_add(GTK_CONTAINER(GTK_DIALOG(about)->vbox), label);

    GTK_BOX(GTK_DIALOG(about)->action_area)->spacing = 3;
    gtk_container_add(GTK_CONTAINER(GTK_DIALOG(about)->action_area), ok_button);

    g_signal_connect_swapped(ok_button, "clicked",
                              G_CALLBACK(gtk_widget_destroy), about);

    gtk_widget_set_redraw_on_allocate(GTK_WIDGET(GTK_DIALOG(about)->vbox),true);
    gtk_widget_show(ok_button);
    gtk_widget_show(label);
    return gtk_dialog_run (GTK_DIALOG(about));
}

} // end namespace gx_gui
