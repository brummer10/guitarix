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

#include <dirent.h>        //  NOLINT
#include <unistd.h>        //  NOLINT
#include <glibmm/i18n.h>   //  NOLINT

#include <cstring>         //  NOLINT
#include <algorithm>       //  NOLINT
#include <string>          //  NOLINT
#include <iostream>        // NOLINT


/* --------------------------- gx_gui namespace ------------------------ */
namespace gx_gui {

/* ----- Menu check item signaled from parameter ------ */

void MenuCheckItem::on_my_activate() {
    param->set(get_active());
}

SwitchParameter* MenuCheckItem::get_parameter() {
    return param;
}

void MenuCheckItem::set_parameter(SwitchParameter *p) {
    param = p;
    parameter_map.insert(p);
    p->changed.connect(sigc::mem_fun(*this, &MenuCheckItem::set_active));
    signal_activate().connect(
        sigc::mem_fun(*this, &MenuCheckItem::on_my_activate));
}

void MenuCheckItem::add_parameter(SwitchParameter *p) {
    param = p;
    p->changed.connect(sigc::mem_fun(*this, &MenuCheckItem::set_active));
    signal_activate().connect(
        sigc::mem_fun(*this, &MenuCheckItem::on_my_activate));
}

void RadioCheckItem::on_my_toggled() {
    param->set(get_active());
}

SwitchParameter* RadioCheckItem::get_parameter() {
    return param;
}

void RadioCheckItem::set_parameter(SwitchParameter *p) {
    param = p;
    parameter_map.insert(p);
    p->changed.connect(sigc::mem_fun(*this, &RadioCheckItem::set_active));
    signal_activate().connect(
        sigc::mem_fun(*this, &RadioCheckItem::on_my_toggled));
}

/* ----- load a top level window from gtk builder file ------ */

GtkWidget *load_toplevel(GtkBuilder *builder, const char* filename, const char* windowname) {
    string fname = gx_system::sysvar.gx_builder_dir+filename;
    GError *err = NULL;
    if (!gtk_builder_add_from_file(builder, fname.c_str(), &err)) {
        g_object_unref(G_OBJECT(builder));
        gx_system::gx_print_fatal(_("gtk builder"), err->message);
        g_error_free(err);
        return NULL;
    }
    GtkWidget *w = GTK_WIDGET(gtk_builder_get_object(builder, windowname));
    if (!w) {
        g_object_unref(G_OBJECT(builder));
        gx_system::gx_print_fatal(_("gtk builder"), string(windowname)+_(" not found in ")+fname);
        return NULL;
    }
    gtk_builder_connect_signals(builder, 0);
    return w;
}

/* --------- menu function triggering engine on/off/bypass --------- */
void gx_engine_switch(GtkWidget* widget, gpointer arg) {
    gx_engine::GxEngineState estate = GxMainInterface::get_instance().engine.get_state();

    switch (estate) {
    case gx_engine::kEngineOn:
        estate = gx_engine::kEngineOff;
        if (arg) {
            // need to activate item
            gtk_check_menu_item_set_active(
                GTK_CHECK_MENU_ITEM(gw.gx_engine_item), TRUE
                );
            estate = gx_engine::kEngineBypass;
        }

        break;

    case gx_engine::kEngineOff:
        if (!arg)
            estate = gx_engine::kEngineOn;
        break;

    default:
        estate = gx_engine::kEngineOn;
        gtk_check_menu_item_set_active(
            GTK_CHECK_MENU_ITEM(gw.gx_engine_item), TRUE
            );
    }

    GxMainInterface::get_instance().engine.set_state(estate);
    gx_refresh_engine_status_display();
}

/* -------------- refresh engine status display ---------------- */
void gx_refresh_engine_status_display() {
    gx_engine::GxEngineState estate = GxMainInterface::get_instance().engine.get_state();

    string state;

    switch (estate) {

    case gx_engine::kEngineOff:
        gtk_widget_show(gw.gx_engine_off_image);
        gtk_widget_hide(gw.gx_engine_on_image);
        gtk_widget_hide(gw.gx_engine_bypass_image);

        gtk_check_menu_item_set_active(
            GTK_CHECK_MENU_ITEM(gw.gx_engine_item), FALSE
            );
        state = "OFF";
        break;

    case gx_engine::kEngineBypass:
        gtk_widget_show(gw.gx_engine_bypass_image);
        gtk_widget_hide(gw.gx_engine_off_image);
        gtk_widget_hide(gw.gx_engine_on_image);

        gtk_check_menu_item_set_active(
            GTK_CHECK_MENU_ITEM(gx_gui::gw.gx_engine_item), TRUE
            );
        state = "BYPASSED";
        break;

    case gx_engine::kEngineOn:
    default: // ON
        gtk_widget_show(gw.gx_engine_on_image);
        gtk_widget_hide(gw.gx_engine_off_image);
        gtk_widget_hide(gw.gx_engine_bypass_image);

        gtk_check_menu_item_set_active(
            GTK_CHECK_MENU_ITEM(gx_gui::gw.gx_engine_item), TRUE
            );
        state = "ON";
    }

    gx_system::gx_print_info(_("Engine State: "), state);
}


// get the last used skin as default
void gx_set_skin_change(float fskin) {
       skin.last_skin = static_cast<int>(fskin);
}

// save the current used skin as default
void gx_get_skin_change(float *fskin) {
    *fskin  = static_cast<float>(skin.gx_current_skin);
}

void gx_jack_is_down() {
    /* FIXME send to ui thread
    gx_print_warning("Jack Shutdown",
                     "jack has bumped us out!!");
    */
    std::cout << _("jack has bumped us out!!") << endl;
    GxMainInterface::get_instance().jack.set_jack_exit(true);
    GxMainInterface::get_instance().engine.set_stateflag(gx_engine::GxEngine::SF_JACK_RECONFIG);
    g_timeout_add_full(G_PRIORITY_LOW, 200, gx_threads::gx_survive_jack_shutdown, 0, NULL);
}

void gx_jack_report_xrun() {
    guivar.g_threads[2] = 0;
    if (guivar.g_threads[2] == 0 ||g_main_context_find_source_by_id(NULL, guivar.g_threads[2]) == NULL)
        guivar.g_threads[2] =g_idle_add(gx_threads::gx_xrun_report, gpointer(NULL));
}

// ----menu function gx_show_oscilloscope
void GxMainInterface::on_show_oscilloscope() {
    if (fShowWaveView.get_active()) {
        guivar.showwave = 1; // FIXME just use is_visible
        Glib::signal_timeout().connect(sigc::mem_fun(*this,
             &GxMainInterface::on_refresh_oscilloscope), 60); // FIXME G_PRIORITY_DEFAULT_IDLE??
        fWaveView.get_parent()->show(); // FIXME why??
    } else {
        guivar.showwave = 0;
        fWaveView.get_parent()->hide();
    }
}

// show loggingbox
void GxMainInterface::on_log_activate() {
    if (gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(fShowLogger.gobj())) == TRUE) {
        gint rxorg, ryorg;
        gtk_window_get_position(GTK_WINDOW(gw.fWindow), &rxorg, &ryorg);
        gtk_window_move(GTK_WINDOW(logger), rxorg+5, ryorg+272);
        gtk_widget_show_all(GTK_WIDGET(logger));
    } else {
        gtk_widget_hide(GTK_WIDGET(logger));
    }
}

// ----menu function oatch info widget
void gx_patch(GtkCheckMenuItem *menuitem, gpointer checkplay) {
    gtk_widget_show_all(gw.patch_info);
}

// ---- menu function logging widget
void gx_log_window(GtkWidget* menuitem, gpointer arg) {
    GtkExpander* const exbox = GxMainInterface::get_instance().getLoggingBox();

    // we could be called before UI is built up
    if (!exbox) return;

    bool expanded = gtk_expander_get_expanded(exbox);
    bool checked = gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(menuitem));
    if (!(expanded ^ checked)) {
        return;
    }
    gtk_signal_emit_by_name(GTK_OBJECT(exbox), "activate");
}

// ----menu funktion about
void gx_show_about(GtkWidget *widget, gpointer data ) {
    static string about;
    if (about.empty()) {
        about +=
            _("\n  This Aplication is to a large extent provided"
            "\n  with the marvelous faust compiler.Yann Orlary"
            "\n  <http://faust.grame.fr/>"
            "\n  A large part is based on the work of Julius Orion Smith"
            "\n <http://ccrma.stanford.edu/realsimple/faust/>"
            "\n  and Albert Graef\n  <http://www.musikwissenschaft.uni-mainz.de/~ag/ag.html>  "
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


// ----- change the jack buffersize on the fly is still experimental, give a warning
gint gx_wait_latency_warn() {
    GtkWidget* warn_dialog = gtk_dialog_new();
    gtk_window_set_destroy_with_parent(GTK_WINDOW(warn_dialog), TRUE);

    GtkWidget* box     = gtk_vbox_new(0, 4);
    GtkWidget* labelt  = gtk_label_new(_("\nWARNING\n"));
    GtkWidget* labelt1 = gtk_label_new(_("CHANGING THE JACK_BUFFER_SIZE ON THE FLY \n"
                                       "MAY CAUSE UNPREDICTABLE EFFECTS \n"
                                       "TO OTHER RUNNING JACK APPLICATIONS. \n"
                                       "DO YOU WANT TO PROCEED ?"));
    GdkColor colorGreen;
    gdk_color_parse("#969292", &colorGreen);
    gtk_widget_modify_fg(labelt1, GTK_STATE_NORMAL, &colorGreen);

    GtkStyle *style1 = gtk_widget_get_style(labelt1);
    pango_font_description_set_size(style1->font_desc, 10*PANGO_SCALE);
    pango_font_description_set_weight(style1->font_desc, PANGO_WEIGHT_BOLD);
    gtk_widget_modify_font(labelt1, style1->font_desc);

    gdk_color_parse("#ffffff", &colorGreen);
    gtk_widget_modify_fg(labelt, GTK_STATE_NORMAL, &colorGreen);
    style1 = gtk_widget_get_style(labelt);
    pango_font_description_set_size(style1->font_desc, 14*PANGO_SCALE);
    pango_font_description_set_weight(style1->font_desc, PANGO_WEIGHT_BOLD);
    gtk_widget_modify_font(labelt, style1->font_desc);

    GtkWidget* button1 =
        gtk_dialog_add_button(GTK_DIALOG(warn_dialog),
                              _("Yes"), GxMainInterface::get_instance().jack.kChangeLatency);

    GtkWidget* button2 =
        gtk_dialog_add_button(GTK_DIALOG(warn_dialog),
                              _("No"),  GxMainInterface::get_instance().jack.kKeepLatency);


    GtkWidget* box1    = gtk_hbox_new(0, 4);
    GtkWidget* box2    = gtk_hbox_new(0, 4);

    GtkWidget* disable_warn = gtk_check_button_new();
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(disable_warn), FALSE);
    g_signal_connect(disable_warn, "clicked",
                     G_CALLBACK(gx_user_disable_latency_warn), NULL);

    GtkWidget * labelt2 =
        gtk_label_new(_("Don't bother me again with such a question, "
                       "I know what I am doing"));

    gtk_container_add(GTK_CONTAINER(box),  labelt);
    gtk_container_add(GTK_CONTAINER(box),  labelt1);
    gtk_container_add(GTK_CONTAINER(box),  box2);
    gtk_container_add(GTK_CONTAINER(box),  box1);
    gtk_container_add(GTK_CONTAINER(box1), disable_warn);
    gtk_container_add(GTK_CONTAINER(box1), labelt2);
    gtk_container_add(GTK_CONTAINER(GTK_DIALOG(warn_dialog)->vbox), box);

    gtk_widget_modify_fg(labelt2, GTK_STATE_NORMAL, &colorGreen);

    GtkStyle *style = gtk_widget_get_style(labelt2);
    pango_font_description_set_size(style->font_desc, 8*PANGO_SCALE);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_NORMAL);
    gtk_widget_modify_font(labelt2, style->font_desc);

    g_signal_connect_swapped(button1, "clicked",
                             G_CALLBACK(gtk_widget_destroy), warn_dialog);
    g_signal_connect_swapped(button2, "clicked",
                             G_CALLBACK(gtk_widget_destroy), warn_dialog);

    gtk_widget_show_all(box);

    return gtk_dialog_run(GTK_DIALOG(warn_dialog));
}

// check user's decision to turn off latency change warning
void gx_user_disable_latency_warn(GtkWidget* wd, gpointer arg) {
    GtkToggleButton* button = GTK_TOGGLE_BUTTON(wd);
    gx_engine::audio.fwarn = static_cast<int>(gtk_toggle_button_get_active(button));
}

void gx_reset_effects(GtkWidget *widget, gpointer data ) {
    string pos(".position");
    for (ParamMap::iterator i = parameter_map.begin(); i != parameter_map.end(); i++) {
        string id = i->first;
        if (id.size() > pos.size() &&
            id.compare(id.size()-pos.size(), pos.size(), pos) == 0) {
            i->second->set_std_value();
        }
    }
}

// reset the extended sliders to default settings
void gx_reset_units(Glib::ustring group_id) {
    group_id += ".";
    string on_off = group_id + "on_off";
    for (ParamMap::iterator i = parameter_map.begin(); i != parameter_map.end(); i++) {
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

gboolean gx_set_resizeable(gpointer data) {
    if (!gtk_window_get_resizable(GTK_WINDOW(data)))
        gtk_window_set_resizable(GTK_WINDOW(data), TRUE);
    return false;
}

gboolean gx_set_sresizeable(gpointer data) {
    if (!gtk_window_get_resizable(GTK_WINDOW(data)))
        gtk_window_set_resizable(GTK_WINDOW(data), FALSE);
    return false;
}

gboolean gx_set_default(gpointer data) {
    gtk_widget_set_size_request(GTK_WIDGET(data), -1, -1);
    return false;
}

gboolean gx_set_default_size(gpointer data) {
    gtk_widget_set_size_request(GTK_WIDGET(data), -1, 440);
    return false;
}

gboolean gx_set_default_ssize(gpointer data) {
    gtk_widget_set_size_request(GTK_WIDGET(data), -1, 460);
    return false;
}

// ----- show extendend settings slider
void gx_show_extended_settings(GtkWidget *widget, gpointer data) {
    gx_gui::GxMainInterface& gui = gx_gui::GxMainInterface::get_instance();
    if (gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(widget)) == TRUE) {

        GtkWidget *plug = gtk_widget_get_parent(GTK_WIDGET(data));
        gtk_widget_show_all(GTK_WIDGET(plug));
        GtkWidget *vbox = gtk_widget_get_parent(GTK_WIDGET(plug));
        GtkWidget *box1 = gtk_widget_get_parent(GTK_WIDGET(vbox));
        vbox = gtk_widget_get_parent(GTK_WIDGET(box1));
        box1 = gtk_widget_get_parent(GTK_WIDGET(vbox));
        vbox = gtk_widget_get_parent(GTK_WIDGET(box1));
        box1 = gtk_widget_get_parent(GTK_WIDGET(vbox));

        // if order is horizontal, force resize the rack widget width
        if (strcmp(gtk_widget_get_name(GTK_WIDGET(box1)), "GtkViewport") == 0) {
            gtk_widget_hide(GTK_WIDGET(vbox));
            if (gtk_window_get_resizable(GTK_WINDOW(gw.fWindow)))
                gtk_window_set_resizable(GTK_WINDOW(gw.fWindow), FALSE);
            gtk_widget_show(GTK_WIDGET(vbox));

            gtk_widget_set_size_request(GTK_WIDGET(gui.RBox), -1, 460);
                if (guivar.g_threads[7] == 0 || g_main_context_find_source_by_id
                                        (NULL, guivar.g_threads[7]) == NULL)
                    guivar.g_threads[7] = g_timeout_add_full(G_PRIORITY_HIGH_IDLE + 10, 40,
                                   gx_gui::gx_set_resizeable, gpointer(gw.fWindow), NULL);
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
            if (gtk_window_get_resizable(GTK_WINDOW(gw.fWindow)))
                gtk_window_set_resizable(GTK_WINDOW(gw.fWindow) , FALSE);
            gtk_widget_show(GTK_WIDGET(vbox));

            gtk_widget_set_size_request(GTK_WIDGET(gui.RBox), -1, 460);
                if (guivar.g_threads[7] == 0 || g_main_context_find_source_by_id
                                        (NULL, guivar.g_threads[7]) == NULL)
                    guivar.g_threads[7] = g_timeout_add_full(G_PRIORITY_HIGH_IDLE + 10, 40,
                                   gx_gui::gx_set_resizeable, gpointer(gw.fWindow), NULL);
                if (guivar.g_threads[6] == 0 || g_main_context_find_source_by_id
                                        (NULL, guivar.g_threads[6]) == NULL)
                    guivar.g_threads[6] = g_timeout_add_full(G_PRIORITY_HIGH_IDLE + 10, 50,
                                   gx_gui::gx_set_default, gpointer(gui.RBox), NULL);
        }
    }
}

// ----- show extendend settings slider
void gx_show_menu_settings(GtkWidget *widget, gpointer data) {
    // done by the button allready
}


// ----menu function gx_mono_rack
void GxMainInterface::on_rack_activate() {
    if (fShowRack.get_active()) {
        gtk_widget_show(gw.rack_widget);
        if (!fShowRRack.get_active()) {
            fShowRRack.set_active(true);
        }
    } else {
        gtk_widget_hide(gw.rack_widget);
    }
}

// ----menu function gx_rack
void GxMainInterface::on_rrack_activate() {

    if (fShowRRack.get_active()) {
        gtk_widget_set_size_request(GTK_WIDGET(RBox), -1, 460);
        gtk_widget_show(RBox);
        // fShowRack.set_active(true);
        // fShowSRack.set_active(true);
    } else {
        if (gtk_window_get_resizable(GTK_WINDOW(gw.fWindow)))
            gtk_window_set_resizable(GTK_WINDOW(gw.fWindow) , FALSE);
        gtk_widget_hide(RBox);
        // fShowRack.set_active(false);
        // fShowSRack.set_active(false);
    }
    if (guivar.g_threads[7] == 0 || g_main_context_find_source_by_id(NULL, guivar.g_threads[7]) == NULL)
            guivar.g_threads[7] = g_timeout_add_full(G_PRIORITY_HIGH_IDLE + 10, 40,
                           gx_set_resizeable, gpointer(gw.fWindow), NULL);
    if (guivar.g_threads[6] == 0 || g_main_context_find_source_by_id(NULL, guivar.g_threads[6]) == NULL)
            guivar.g_threads[6] = g_timeout_add_full(G_PRIORITY_HIGH_IDLE + 10, 50,
                           gx_set_default, gpointer(RBox), NULL);
}

// ----menu function gx_rack
void GxMainInterface::on_srack_activate() {
    if (gtk_window_get_resizable(GTK_WINDOW(gw.fWindow)))
        gtk_window_set_resizable(GTK_WINDOW(gw.fWindow) , FALSE);
    if (fShowSRack.get_active()) {
        gtk_widget_show(gw.srack_widget);

        GtkWidget *parent = gtk_widget_get_parent(GTK_WIDGET(gw.srack_widget));
        GtkWidget *vbox = gtk_widget_get_parent(GTK_WIDGET(parent));
        vbox = gtk_widget_get_parent(GTK_WIDGET(vbox));
        // vbox = gtk_widget_get_parent(GTK_WIDGET(vbox));
        // if order is horizontal, force resize the rack widget width
        if (strcmp(gtk_widget_get_name(GTK_WIDGET(vbox)), "GtkViewport") == 0) {
            gtk_widget_hide(GTK_WIDGET(vbox));
            parent = gtk_widget_get_parent(GTK_WIDGET(vbox));
            if (strcmp(gtk_widget_get_name(GTK_WIDGET(parent)), "HorizontalStereoBox") == 0) {
                if (!gtk_widget_is_drawable(GTK_WIDGET(parent)))
                    gtk_widget_show(GTK_WIDGET(parent));
            }
            gtk_widget_show(GTK_WIDGET(vbox));
        }
        if (!fShowRRack.get_active()) {
            fShowRRack.set_active(true);
        }
    } else {
        gtk_widget_hide(gw.srack_widget);

        GtkWidget *parent = gtk_widget_get_parent(GTK_WIDGET(gw.srack_widget));
        GtkWidget *vbox = gtk_widget_get_parent(GTK_WIDGET(parent));
        vbox = gtk_widget_get_parent(GTK_WIDGET(vbox));
        // vbox = gtk_widget_get_parent(GTK_WIDGET(vbox));
        // if order is horizontal, force resize the rack widget size
        if (strcmp(gtk_widget_get_name(GTK_WIDGET(vbox)), "GtkViewport") == 0) {
            gtk_widget_hide(GTK_WIDGET(vbox));
            parent = gtk_widget_get_parent(GTK_WIDGET(vbox));
            if (strcmp(gtk_widget_get_name(GTK_WIDGET(parent)), "HorizontalStereoBox") == 0) {
                if (gtk_widget_is_drawable(GTK_WIDGET(parent)))
                    gtk_widget_hide(GTK_WIDGET(parent));
            }
            gtk_widget_show(GTK_WIDGET(vbox));
        }
    }

    gtk_widget_set_size_request(GTK_WIDGET(RBox), -1, 460 );
    if (guivar.g_threads[7] == 0 || g_main_context_find_source_by_id(NULL, guivar.g_threads[7]) == NULL)
            guivar.g_threads[7] = g_timeout_add_full(G_PRIORITY_HIGH_IDLE + 10, 40,
                           gx_set_resizeable, gpointer(gw.fWindow), NULL);
    if (guivar.g_threads[6] == 0 || g_main_context_find_source_by_id(NULL, guivar.g_threads[6]) == NULL)
            guivar.g_threads[6] = g_timeout_add_full(G_PRIORITY_HIGH_IDLE + 10, 50,
                           gx_set_default, gpointer(RBox), NULL);
}

// ----menu function gx_toolbar
void GxMainInterface::on_toolbar_activate() {

    if (fShowToolBar.get_active()) {
        gtk_widget_show_all(gw.rack_tool_bar);
    } else {
        GtkAllocation my_size;
        gtk_widget_get_allocation(GTK_WIDGET(RBox), &my_size);
        gtk_widget_set_size_request(GTK_WIDGET(RBox), -1, my_size.height);
        if (gtk_window_get_resizable(GTK_WINDOW(gw.fWindow)))
            gtk_window_set_resizable(GTK_WINDOW(gw.fWindow) , FALSE);
        gtk_widget_hide(gw.rack_tool_bar);
    }
    if (guivar.g_threads[7] == 0 || g_main_context_find_source_by_id(NULL, guivar.g_threads[7]) == NULL)
            guivar.g_threads[7] = g_timeout_add_full(G_PRIORITY_HIGH_IDLE + 10, 40,
                           gx_set_resizeable, gpointer(gw.fWindow), NULL);
    if (guivar.g_threads[6] == 0 || g_main_context_find_source_by_id(NULL, guivar.g_threads[6]) == NULL)
            guivar.g_threads[6] = g_timeout_add_full(G_PRIORITY_HIGH_IDLE + 10, 50,
                           gx_set_default, gpointer(RBox), NULL);
}

// ----menu function gx_tuner
void GxMainInterface::on_tuner_activate() {
    bool tuner_on = fShowTuner.get_active();
    engine.tuner.used_for_display(tuner_on);
    engine.set_rack_changed();
    if (tuner_on) {
        gtk_widget_show_all(gw.tuner_widget);
        fTuner.show();
    } else {
        GtkAllocation my_size;
        gtk_widget_get_allocation(GTK_WIDGET(RBox), &my_size);
        gtk_widget_set_size_request(GTK_WIDGET(RBox), -1, my_size.height);
        if (gtk_window_get_resizable(GTK_WINDOW(gw.fWindow)))
            gtk_window_set_resizable(GTK_WINDOW(gw.fWindow) , FALSE);
        fTuner.hide();
        gtk_widget_hide(gw.tuner_widget);
    }
    if (guivar.g_threads[7] == 0 || g_main_context_find_source_by_id(NULL, guivar.g_threads[7]) == NULL)
            guivar.g_threads[7] = g_timeout_add_full(G_PRIORITY_HIGH_IDLE + 10, 40,
                           gx_set_resizeable, gpointer(gw.fWindow), NULL);
    if (guivar.g_threads[6] == 0 || g_main_context_find_source_by_id(NULL, guivar.g_threads[6]) == NULL)
            guivar.g_threads[6] = g_timeout_add_full(G_PRIORITY_HIGH_IDLE + 10, 50,
                           gx_set_default, gpointer(RBox), NULL);
}

// ---- menu function gx_midi_out
void gx_midi_out(GtkCheckMenuItem *menuitem, gpointer checkplay) {
    GList*   child_list =  gtk_container_get_children(GTK_CONTAINER(gw.midibox));
    GtkWidget *child = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 0));
    g_list_free(child_list);
    gx_show_extended_settings(GTK_WIDGET(menuitem), (gpointer) child);
    static bool first = true;
    if (gtk_check_menu_item_get_active(menuitem) == TRUE) {
        if (first) {
	    guivar.refresh_size = 0;
	}
        //gx_engine::turnOnMidi();//FIXME
    } else {
        //gx_engine::turnOffMidi();//FIXME
        string group = "midi_out.on_off";
        parameter_map[group].set_std_value();
    }
    first =false;
    GxMainInterface::get_instance().engine.set_rack_changed();
}

// ----- hide the extendend settings slider
void gx_hide_extended_settings(GtkWidget *widget, gpointer data) {

    if (gdk_window_get_state(gw.fWindow->window)
        & (GDK_WINDOW_STATE_ICONIFIED|GDK_WINDOW_STATE_WITHDRAWN)) {
        gint mainxorg = gx_set_mx_oriantation();
        gint mainyorg = gx_set_my_oriantation();
        gtk_window_move(GTK_WINDOW(gw.fWindow), mainxorg, mainyorg);
        gtk_window_present(GTK_WINDOW(gw.fWindow));
    } else {
        gtk_widget_hide(gw.fWindow);
        // gtk_window_iconify(GTK_WINDOW(gw.fWindow));
    }
}

// ----- systray menu
void gx_systray_menu(GtkWidget *widget, gpointer data) {
    guint32 tim = gtk_get_current_event_time();
    gtk_menu_popup(GTK_MENU(gw.menuh), NULL, NULL, NULL, (gpointer) gw.menuh, 2, tim);
}

// ---- choice dialog without text entry
gint gx_nchoice_dialog_without_entry(
    const char* window_title,
    const char* msg,
    const guint nchoice,
    const char* label[],
    const gint  resp[],
    const gint default_response) {

    GtkWidget* dialog   = gtk_dialog_new();
    GtkWidget* text_label = gtk_label_new(msg);
    gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox), text_label);

    GdkColor colorGreen;
    gdk_color_parse("#969292", &colorGreen);
    gtk_widget_modify_fg(text_label, GTK_STATE_NORMAL, &colorGreen);

    GdkColor colorBlack;
    gdk_color_parse("#000000", &colorBlack);
    gtk_widget_modify_bg(dialog, GTK_STATE_NORMAL, &colorBlack);
    g_signal_connect(GTK_DIALOG(dialog)->vbox, "expose-event",
                     G_CALLBACK(gx_cairo::rectangle_skin_color_expose), NULL);
    GtkStyle* text_style = gtk_widget_get_style(text_label);
    pango_font_description_set_size(text_style->font_desc, 10*PANGO_SCALE);
    pango_font_description_set_weight(text_style->font_desc, PANGO_WEIGHT_BOLD);

    gtk_widget_modify_font(text_label, text_style->font_desc);

    for (guint i = 0; i < nchoice; i++) {
        GtkWidget* button =
            gtk_dialog_add_button(GTK_DIALOG(dialog), label[i], resp[i]);

        gdk_color_parse("#555555", &colorBlack);
        gtk_widget_modify_bg(button, GTK_STATE_NORMAL, &colorBlack);

        g_signal_connect_swapped(button, "clicked",  G_CALLBACK(gtk_widget_destroy), dialog);
    }

    // set default
    gtk_dialog_set_has_separator(GTK_DIALOG(dialog), TRUE);
    gtk_dialog_set_default_response(GTK_DIALOG(dialog), default_response);
    gtk_window_set_title(GTK_WINDOW(dialog), window_title);

    gtk_widget_show(text_label);

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
void gx_get_text_entry(GtkEntry* entry, string& output) {
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

// ---- retrive skin array index from skin name
void gx_actualize_skin_index(const string& skin_name) {
    for (guint s = 0; s < skin.skin_list.size(); s++) {
        if (skin_name == skin.skin_list[s]) {
            skin.gx_current_skin = s;
            return;
        }
    }
}

// ------- count the number of available skins
unsigned int gx_fetch_available_skins() {
    DIR *d;
    d = opendir(gx_system::sysvar.gx_style_dir.c_str());
    if (!d) {
        return 0;
    }
    // look for gx_head_*.rc and extract *-part
    struct dirent *de;
    while ((de = readdir(d)) != 0) {
        char *p = de->d_name;
        if (strncmp(p, "gx_head_", 8) != 0) {
            continue;
        }
        p += 8;
        int n = strlen(p) - 3;
        if (strcmp(p+n, ".rc") != 0) {
            continue;
        }
        skin.skin_list.push_back(string(p, n));
        sort(skin.skin_list.begin(), skin.skin_list.end());
    }
    closedir(d);
    return skin.skin_list.size();
}

// ----- skin change
void  gx_change_skin(GtkCheckMenuItem *menuitem, gpointer arg) {
    // no action needed on false
    if (gtk_check_menu_item_get_active(menuitem) == FALSE)
        return;

    // update the skin to the one picked by user
    const int idx = static_cast<int>(GPOINTER_TO_INT(arg));

    (void)gx_update_skin(idx, "gx_change_skin");
}

// ----- cycling through skin
void  gx_cycle_through_skin(GtkWidget *widget, gpointer arg) {

    gint idx = skin.gx_current_skin + 1;
    idx %= skin.skin_list.size();

    // did it work ? if yes, update current skin
    if (gx_update_skin(idx, "gx_cycle_through_skin"))
        skin.gx_current_skin = idx;

    // update menu item state
    gx_update_skin_menu_item(skin.gx_current_skin);
}

// ----- cycling through skin
void  gx_update_skin_menu_item(const int index) {
    // update menu item state
    GxMainInterface& gui = GxMainInterface::get_instance();
    GtkWidget* skinmenu = gui.getMenu("Skin");

    GList*     list = gtk_container_get_children(GTK_CONTAINER(skinmenu));
    GtkWidget* item = reinterpret_cast<GtkWidget*>(g_list_nth_data(list, index));
    g_list_free(list);
    if (item) gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(item), TRUE);
}

// ---- skin changer, used internally frm callbacks
bool gx_update_skin(const gint idx, const char* calling_func) {
    // check skin validity
    if (idx < 0 || idx >= (gint)skin.skin_list.size()) {
        gx_system::gx_print_warning(calling_func,
                _("skin index out of range, keeping actual skin"));
        return false;
    }

    string rcfile = gx_system::sysvar.gx_style_dir + "gx_head_";
    rcfile += skin.skin_list[idx];
    rcfile += ".rc";

    gtk_rc_parse(rcfile.c_str());
    gtk_rc_reset_styles(gtk_settings_get_default());

    skin.gx_current_skin = idx;

    // refresh latency check menu
    GxMainInterface& gui = GxMainInterface::get_instance();
    GtkWidget* wd = gui.getJackLatencyItem(GxMainInterface::get_instance().jack.jack_bs);
    if (wd) gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(wd), TRUE);

    return true;
}

// ---- set last used skin as default
bool gx_set_skin(GtkWidget *widget, gpointer data) {
    return gx_update_skin(skin.last_skin, "Set Skin");
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

    g_signal_connect(label, "expose-event", G_CALLBACK(gx_cairo::conv_widget_expose), NULL);
    gtk_widget_show(ok_button);
    gtk_widget_show(label);
    return gtk_dialog_run (GTK_DIALOG(about));
}

/* meter button release   */
bool GxMainInterface::on_meter_button_release(GdkEventButton* ev) {
    if (ev->button == 1) {
        for (unsigned int i = 0; i < sizeof(fLevelMeters)/sizeof(fLevelMeters[0]); i++) {
            fLevelMeters[i].clear();
        }
        return true;
    }
    return false;
}



/* ----- delete event ---- */
gboolean gx_delete_event(GtkWidget *widget, gpointer   data ) {
    gtk_range_set_value(GTK_RANGE(widget), 0);
    return TRUE;
}
} /* end of gx_gui namespace */

