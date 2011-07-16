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
 * ----------------------------------------------------------------------------
 *
 *    This is gx_head main.
 *
 * ----------------------------------------------------------------------------
 */

#include "guitarix.h"       // NOLINT

#include <giomm/init.h>     // NOLINT
#include <gtkmm/main.h>     // NOLINT
#include <gxwmm/init.h>     // NOLINT
#include <string>           // NOLINT


// using namespace gx_system;

void init_unix_signal_handlers() {
    /* ----- block signal USR1 ---------
    ** inherited by all threads which are created later
    ** USR1 is processed synchronously by gx_signal_helper_thread
    */
    sigset_t waitset;
    sigemptyset(&waitset);
    sigaddset(&waitset, SIGUSR1);
    sigaddset(&waitset, SIGCHLD);
    sigprocmask(SIG_BLOCK, &waitset, NULL);

    // ----- set unix signal handlers for proper shutdown
    signal(SIGQUIT, gx_system::gx_signal_handler);
    signal(SIGTERM, gx_system::gx_signal_handler);
    signal(SIGHUP,  gx_system::gx_signal_handler);
    signal(SIGINT,  gx_system::gx_signal_handler);
    // signal(SIGSEGV, gx_signal_handler); // no good, quits application silently
}

/* --------- Guitarix main ---------- */
int main(int argc, char *argv[]) {
#ifdef DISABLE_NLS
// break
#elseif IS_MACOSX
// break
#elseif ENABLE_NLS

    bindtextdomain(GETTEXT_PACKAGE, LOCALEDIR);
    bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
    textdomain(GETTEXT_PACKAGE);
#endif

    init_unix_signal_handlers();

    // ----------------------- init basic subsystems ----------------------
    Glib::thread_init();
    Glib::init();
    Gxw::init();

    // ------ initialize parameter list ------
    gx_engine::audio.register_parameter();
    gx_engine::midi.register_parameter();
    gx_engine::register_faust_parameters();
    gx_gui::GuiVariables guivar;
    guivar.register_gui_parameter();
    gx_preset::init();
    gx_gui::parameter_map.set_init_values();

    // ---------------------- user options handling ------------------
    string optvar[NUM_SHELL_VAR];
    gx_system::gx_process_cmdline_options(argc, argv, optvar);
    Gtk::Main main(argc, argv);

    // ---------------- Check for working user directory  -------------
    gx_system::gx_version_check();

    // ------ time measurement (debug) ------
#ifndef NDEBUG
    gx_system::add_time_measurement();
#endif

    // ----------------------- init GTK interface----------------------
    g_type_class_unref(g_type_class_ref(GTK_TYPE_IMAGE_MENU_ITEM));
    g_object_set(gtk_settings_get_default(), "gtk-menu-images", FALSE, NULL);
    gx_gui::GxMainInterface* gui = gx_gui::GxMainInterface::instance("gx_head");
    gui->setup();


    // ---------------------- initialize jack gxjack.client ------------------
    if (gx_jack::gxjack.gx_jack_init(optvar)) {
        // -------- initialize gx_head engine --------------------------
        gx_engine::gx_engine_init(optvar);

        // -------- set jack callbacks and activation -------------------
        gx_jack::gxjack.gx_jack_callbacks_and_activate();

        // -------- init port connections
        gx_jack::gx_jack_init_port_connection(optvar);
    }

    // ----------------------- run GTK main loop ----------------------
    gx_system::gx_set_override_options(optvar);
    gx_ui::GxUI::updateAllGuis();
    g_type_class_unref(g_type_class_ref(GTK_TYPE_IMAGE_MENU_ITEM));
    g_object_set(gtk_settings_get_default(), "gtk-menu-images", TRUE, NULL);
    gui->show();

    if (gx_jack::gxjack.client) {
        // -------- pitch tracker (needs jack thread running) -------------
        gx_engine::pitch_tracker.init();
    }

    // Gxw::Knob::set_jump_to_mouse(false);
    gui->run();

    // ------------- shut things down
    gx_system::gx_clean_exit(NULL, NULL);

    return 0;
}
