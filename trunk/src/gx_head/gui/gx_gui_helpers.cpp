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

#include <unistd.h>        //  NOLINT

#include <cstring>         //  NOLINT
#include <algorithm>       //  NOLINT
#include <string>          //  NOLINT
#include <iostream>        // NOLINT
//#include <gdk/gdkkeysyms.h>            // NOLINT
//#include <gtkmm/filechooserdialog.h>   // NOLINT
#include <gxw/GxControlParameter.h>      // NOLINT


/* --------------------------- gx_gui namespace ------------------------ */
namespace gx_gui {


void show_error_msg(const string& msg) {
    Gtk::MessageDialog dialog(
	msg, false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_CLOSE, true);
    dialog.set_title("gx_head");
    dialog.run();
}

// ----menu function patch info widget
void gx_patch() {
    gtk_widget_show_all(gw.patch_info);
}

// ----menu funktion help
void gx_show_help() {
    GError *error = NULL;
    gtk_show_uri(gdk_screen_get_default(), "http://sourceforge.net/apps/mediawiki/guitarix/index.php?title=Main_Page",
    gtk_get_current_event_time(), &error);
    if (error)
    {
        gx_system::gx_print_error("guitarix help",
				  _("failed to load online help   "));
        g_error_free(error);
    } 

}

// ----menu funktion about
void gx_show_about() {
    static string about;
    if (about.empty()) {
        about +=
            _("\n\n  This Aplication is to a large extent provided"
            "\n  with the marvelous faust compiler.Yann Orlary"
            "\n  http://faust.grame.fr/"
            "\n  A large part is based on the work of Julius Orion Smith"
            "\n  http://ccrma.stanford.edu/realsimple/faust/"
            "\n  and Albert Graef\n  http://q-lang.sourceforge.net/examples.html#Faust"
            "\n\n\n  gx_head ");

        about += GX_VERSION;

        about +=
            _("\n  for impulse response it use zita-convolver "
            "\n  byFons Adriaensen "
            "\n  http://www.kokkinizita.net/linuxaudio/index.html "
            "\n\n  authors: Hermann Meyer <brummer-@web.de>"
            "\n  authors: James Warden <warjamy@yahoo.com>"
            "\n  authors: Andreas Degert <andreas.degert@googlemail.com>    "
            "\n  authors: Pete Shorthose <pshorthose@gmail.com>    "
            "\n  home: http://guitarix.sourceforge.net/\n");
    }

    gx_message_popup(about.c_str());
}


// reset all parameters to default settings
void gx_reset_units(gx_engine::ParamMap& pmap, Glib::ustring group_id) {
    group_id += ".";
    string on_off = group_id + "on_off";
    for (gx_engine::ParamMap::iterator i = pmap.begin(); i != pmap.end(); ++i) {
        if (i->first.compare(0, group_id.size(), group_id) == 0) {
            if (i->second->isControllable()) {
                string id = i->first;
                if (i->first != on_off) {
                    i->second->set_std_value();
                }
            }
        }
    }
}

/* ----- delete event ---- */
gboolean gx_delete_event(GtkWidget *widget, gpointer   data ) {
    gtk_range_set_value(GTK_RANGE(widget), 0);
    return TRUE;
}

/****************************************************************
 ** auto resize handling 
 */

gboolean gx_set_resizeable(gpointer data) {
    if (!gtk_window_get_resizable(GTK_WINDOW(data)) &&
      GDK_IS_WINDOW (GTK_WIDGET(data)->window)) {
        gtk_window_set_resizable(GTK_WINDOW(data), TRUE);
        return false;
    } else {
        return true;
    }
}

gboolean gx_set_sresizeable(gpointer data) {
    if (!gtk_window_get_resizable(GTK_WINDOW(data)) &&
      GDK_IS_WINDOW (GTK_WIDGET(data)->window))
        gtk_window_set_resizable(GTK_WINDOW(data), FALSE);
    return false;
}

gboolean gx_set_default(gpointer data) {
    if(GDK_IS_WINDOW (GTK_WIDGET(data)->window)) {
        gtk_widget_set_size_request(GTK_WIDGET(data), -1, -1);
        return false;
    } else {
        return true;
    }
}

gboolean gx_set_default_size(gpointer data) {
    gtk_widget_set_size_request(GTK_WIDGET(data), -1, 440);
    return false;
}

gboolean gx_set_default_ssize(gpointer data) {
    gtk_widget_set_size_request(GTK_WIDGET(data), -1, 460);
    return false;
}

/****************************************************************
 ** effect box handling
 */

// ----- show / hide effect boxes
void gx_show_extended_settings(GtkWidget *widget, gpointer data) {
    gx_gui::GxMainInterface& gui = gx_gui::GxMainInterface::get_instance();
    GtkAllocation alloc;
    gtk_widget_get_allocation (GTK_WIDGET(gui.RBox), &alloc);
    if (gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(widget)) == TRUE) {

        GtkWidget *plug = gtk_widget_get_parent(GTK_WIDGET(data));
        gtk_widget_show(GTK_WIDGET(plug));
        GtkWidget *vbox = gtk_widget_get_parent(GTK_WIDGET(plug));
        GtkWidget *box1 = gtk_widget_get_parent(GTK_WIDGET(vbox));
        vbox = gtk_widget_get_parent(GTK_WIDGET(box1));
        box1 = gtk_widget_get_parent(GTK_WIDGET(vbox));
        vbox = gtk_widget_get_parent(GTK_WIDGET(box1));
        box1 = gtk_widget_get_parent(GTK_WIDGET(vbox));

        // if order is horizontal, force resize the rack widget width
        if (strcmp(gtk_widget_get_name(GTK_WIDGET(box1)), "GtkViewport") == 0) {
            gtk_widget_hide(GTK_WIDGET(vbox));
            if (gui.fWindow.get_resizable())
                gui.fWindow.set_resizable(false);
            gtk_widget_show(GTK_WIDGET(vbox));
            if (GDK_IS_WINDOW (gui.RBox->window)) {
                gtk_widget_set_size_request(GTK_WIDGET(gui.RBox), -1, alloc.height);
            } else {
                gtk_widget_set_size_request(GTK_WIDGET(gui.RBox), -1, 460);
            }
            if (guivar.g_threads[7] == 0 || g_main_context_find_source_by_id
                                    (NULL, guivar.g_threads[7]) == NULL)
                guivar.g_threads[7] = g_timeout_add_full(
                    G_PRIORITY_HIGH_IDLE + 10, 40, gx_gui::gx_set_resizeable,
                    gpointer(gui.fWindow.gobj()), NULL);
            if (guivar.g_threads[6] == 0 || g_main_context_find_source_by_id
                                    (NULL, guivar.g_threads[6]) == NULL)
                guivar.g_threads[6] = g_timeout_add_full(G_PRIORITY_HIGH_IDLE + 10, 50,
                               gx_gui::gx_set_default, gpointer(gui.RBox), NULL);
        }
    } else {
        GtkWidget *plug = gtk_widget_get_parent(GTK_WIDGET(data));
        gtk_widget_hide(GTK_WIDGET(plug));
        GtkWidget *vbox = gtk_widget_get_parent(GTK_WIDGET(plug));
        GtkWidget *box1 = gtk_widget_get_parent(GTK_WIDGET(vbox));
        vbox = gtk_widget_get_parent(GTK_WIDGET(box1));
        box1 = gtk_widget_get_parent(GTK_WIDGET(vbox));
        vbox = gtk_widget_get_parent(GTK_WIDGET(box1));
        box1 = gtk_widget_get_parent(GTK_WIDGET(vbox));

        // if order is horizontal, force resize the rack widget width
        if (strcmp(gtk_widget_get_name(GTK_WIDGET(box1)), "GtkViewport") == 0) {
            gtk_widget_hide(GTK_WIDGET(vbox));
            if (gui.fWindow.get_resizable())
                gui.fWindow.set_resizable(false);
            gtk_widget_show(GTK_WIDGET(vbox));

            if (GDK_IS_WINDOW (gui.RBox->window)) {
                gtk_widget_set_size_request(GTK_WIDGET(gui.RBox), -1, alloc.height);
            } else {
                gtk_widget_set_size_request(GTK_WIDGET(gui.RBox), -1, 460);
            }    
            if (guivar.g_threads[7] == 0 || g_main_context_find_source_by_id
                                        (NULL, guivar.g_threads[7]) == NULL)
            guivar.g_threads[7] = g_timeout_add_full(
                G_PRIORITY_HIGH_IDLE + 10, 40, gx_gui::gx_set_resizeable,
                gpointer(gui.fWindow.gobj()), NULL);
            if (guivar.g_threads[6] == 0 || g_main_context_find_source_by_id
                                    (NULL, guivar.g_threads[6]) == NULL)
                guivar.g_threads[6] = g_timeout_add_full(G_PRIORITY_HIGH_IDLE + 10, 50,
                               gx_gui::gx_set_default, gpointer(gui.RBox), NULL);
        }
    }
}

// ----- show / hide effect boxes
void gx_show_menu_settings(GtkWidget *widget, gpointer data) {
    // done by the button allready
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
    const gint default_response) {
    GxMainInterface& gui = GxMainInterface::get_instance();
    GtkWidget* dialog   = gtk_dialog_new();
    GtkWidget* text_label = gtk_label_new(msg);
    GtkWidget* image   = gtk_image_new_from_pixbuf(gui.gw_ib->gobj());

    gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox), text_label);

    GdkColor colorGreen;
    gdk_color_parse("#e1e1ed", &colorGreen);
    gtk_widget_modify_fg(text_label, GTK_STATE_NORMAL, &colorGreen);

    GdkColor colorBlack;
    gdk_color_parse("#10101e", &colorBlack);
    gtk_widget_modify_bg(dialog, GTK_STATE_NORMAL, &colorBlack);
    g_signal_connect(GTK_DIALOG(dialog)->vbox, "expose-event",
                     G_CALLBACK(gx_cairo::start_box_expose), NULL);
    gtk_widget_set_redraw_on_allocate(GTK_WIDGET(GTK_DIALOG(dialog)->vbox),true);
    GtkStyle* text_style = gtk_widget_get_style(text_label);
    pango_font_description_set_size(text_style->font_desc, 10*PANGO_SCALE);
    pango_font_description_set_weight(text_style->font_desc, PANGO_WEIGHT_BOLD);

    gtk_widget_modify_font(text_label, text_style->font_desc);
    gtk_container_add(GTK_CONTAINER(gtk_dialog_get_action_area(GTK_DIALOG(dialog))), image);
    for (guint i = 0; i < nchoice; i++) {
        GtkWidget* button =
            gtk_dialog_add_button(GTK_DIALOG(dialog), label[i], resp[i]);

        gdk_color_parse("#555555", &colorBlack);
        gtk_widget_modify_bg(button, GTK_STATE_NORMAL, &colorBlack);

        g_signal_connect_swapped(button, "clicked",  G_CALLBACK(gtk_widget_destroy), dialog);
    }

    // set default
    gtk_dialog_set_has_separator(GTK_DIALOG(dialog), FALSE);
    gtk_dialog_set_default_response(GTK_DIALOG(dialog), default_response);
    gtk_window_set_title(GTK_WINDOW(dialog), window_title);

    gtk_widget_show(text_label);
    gtk_widget_show(image);
    // --- run dialog and check response
    gint response = gtk_dialog_run(GTK_DIALOG(dialog));
    return response;
}

// ---- choice dialog without text entry
gint gx_choice_dialog_without_entry(
    const char* window_title,
    const char* msg,
    const char* label1,
    const char* label2,
    const gint resp1,
    const gint resp2,
    const gint default_response) {

    const guint nchoice     = 2;
    const char* labels[]    = {label1, label2};
    const gint  responses[] = {resp1, resp2};

    return gx_nchoice_dialog_without_entry(
        window_title,
        msg,
        nchoice,
        labels,
        responses,
        default_response);
}

// ---- get text entry from dialog
void gx_get_text_entry(GtkEntry* entry, Glib::ustring& output) {
    if (gtk_entry_get_text(entry)[0])
        output = gtk_entry_get_text(entry);
}

// ---- choice dialog with text entry
gint gx_choice_dialog_with_text_entry(
    const char* window_title,
    const char* msg,
    const char* label1,
    const char* label2,
    const gint resp1,
    const gint resp2,
    const gint default_response,
    GCallback func) {

    GtkWidget *dialog, *button1, *button2;
    dialog  = gtk_dialog_new();
    button1 = gtk_dialog_add_button(GTK_DIALOG(dialog), label1, resp1);
    button2 = gtk_dialog_add_button(GTK_DIALOG(dialog), label2, resp2);

    GtkWidget* text_label = gtk_label_new(msg);
    gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox), text_label);


    GtkWidget* gtk_entry = gtk_entry_new_with_max_length(32);
    gtk_entry_set_text(GTK_ENTRY(gtk_entry), "");
    gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox), gtk_entry);

    g_signal_connect_swapped(button1, "clicked",  G_CALLBACK(func), gtk_entry);
    g_signal_connect(GTK_DIALOG(dialog)->vbox, "expose-event",
                     G_CALLBACK(gx_cairo::rectangle_skin_color_expose), NULL);

    gtk_dialog_set_has_separator(GTK_DIALOG(dialog), TRUE);
    gtk_dialog_set_default_response(GTK_DIALOG(dialog), default_response);
    gtk_entry_set_activates_default(GTK_ENTRY(gtk_entry), TRUE);
    GTK_BOX(GTK_DIALOG(dialog)->action_area)->spacing = 4;

    // some display style
    GdkColor colorGreen;
    gdk_color_parse("#969292", &colorGreen);
    gtk_widget_modify_fg(text_label, GTK_STATE_NORMAL, &colorGreen);

    GdkColor colorBlack;
    gdk_color_parse("#000000", &colorBlack);
    gtk_widget_modify_bg(dialog, GTK_STATE_NORMAL, &colorBlack);

    GtkStyle* text_style = gtk_widget_get_style(text_label);
    pango_font_description_set_size(text_style->font_desc, 10*PANGO_SCALE);
    pango_font_description_set_weight(text_style->font_desc, PANGO_WEIGHT_BOLD);

    gtk_widget_modify_font(text_label, text_style->font_desc);

    gdk_color_parse("#555555", &colorBlack);
    gtk_widget_modify_bg(button1, GTK_STATE_NORMAL, &colorBlack);

    gdk_color_parse("#555555", &colorBlack);
    gtk_widget_modify_bg(button2, GTK_STATE_NORMAL, &colorBlack);

    // display extra stuff
    gtk_widget_show(text_label);
    gtk_widget_show(gtk_entry);
    gtk_window_set_title(GTK_WINDOW(dialog), window_title);

    // run the dialog and wait for response
    gint response = gtk_dialog_run(GTK_DIALOG(dialog));

    if (dialog) gtk_widget_destroy(dialog);

    return response;
}

// ---- popup warning
int gx_message_popup(const char* msg) {
    // check msg validity
    if (!msg) {
        gx_system::gx_print_warning("Message Popup",
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

    g_signal_connect(GTK_DIALOG(about)->vbox, "expose-event", G_CALLBACK(gx_cairo::start_box_expose), NULL);
    gtk_widget_set_redraw_on_allocate(GTK_WIDGET(GTK_DIALOG(about)->vbox),true);
    gtk_widget_show(ok_button);
    gtk_widget_show(label);
    return gtk_dialog_run (GTK_DIALOG(about));
}

/****************************************************************
 ** skin handling
 */

// ---- retrive skin array index from skin name
void gx_actualize_skin_index(gx_system::SkinHandling& skin, const string& skin_name) {
    for (guint s = 0; s < skin.skin_list.size(); s++) {
        if (skin_name == skin.skin_list[s]) {
            gx_engine::audio.fskin = s;
            return;
        }
    }
}

// ----- skin change
void  gx_change_skin(Gtk::RadioMenuItem& item, int idx) {
    // no action needed on false
    if (!item.get_active()) {
        return;
    }
    // update the skin to the one picked by user
    (void)gx_update_skin(idx, "gx_change_skin");
}

// ----- cycling through skin
void  gx_cycle_through_skin(GtkWidget *widget, gpointer arg) {
    GxMainInterface& gui = GxMainInterface::get_instance();
    gint idx = gx_engine::audio.fskin + 1;
    idx %= gui.options.skin.skin_list.size();

    // did it work ? if yes, update current skin
    if (gx_update_skin(idx, "gx_cycle_through_skin"))
        gx_engine::audio.fskin = idx;

    // update menu item state
    gx_update_skin_menu_item(gx_engine::audio.fskin);
}

// ----- cycling through skin
void  gx_update_skin_menu_item(const int index) {
    // update menu item state
    GxMainInterface& gui = GxMainInterface::get_instance();
    GList*     list = gtk_container_get_children(GTK_CONTAINER(gui.mainmenu.skin_menu.gobj()));
    GtkWidget* item = reinterpret_cast<GtkWidget*>(g_list_nth_data(list, index));
    g_list_free(list);
    if (item) gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(item), TRUE);
}

// ---- skin changer, used internally frm callbacks
bool gx_update_skin(const gint idx, const char* calling_func) {
    GxMainInterface& gui = GxMainInterface::get_instance();
    // check skin validity
    if (idx < 0 || idx >= (gint)gui.options.skin.skin_list.size()) {
        gx_system::gx_print_warning(calling_func,
                _("skin index out of range, keeping actual skin"));
        return false;
    }

    string rcfile = gui.options.get_style_filepath(
	"gx_head_" + gui.options.skin.skin_list[idx] + ".rc");
    gtk_rc_parse(rcfile.c_str());
    gtk_rc_reset_styles(gtk_settings_get_default());

    gx_engine::audio.fskin = idx;

    return true;
}
} // end namespace gx_gui


