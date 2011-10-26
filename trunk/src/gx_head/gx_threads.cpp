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
 *    This are the guitarix multithreads related functionality
 *
 * ----------------------------------------------------------------------------
 */

#include "guitarix.h"       // NOLINT

#include <glibmm/i18n.h>    // NOLINT
#include <errno.h>          // NOLINT
#include <cstring>          // NOLINT
#include <algorithm>        // NOLINT
#include <gtkmm/main.h>

namespace gx_threads {

/* ----------------- refresh GX level display function ---------------- */
gboolean gx_refresh_meter_level(gpointer args) {
    if (gx_gui::GxMainInterface::get_instance().jack.client) {
        gx_gui::GxMainInterface& gui = gx_gui::GxMainInterface::get_instance();
        static const float falloff = gx_gui::guivar.meter_falloff *
                                     gx_gui::guivar.meter_display_timeout * 0.001;

        // Note: removed RMS calculation, we will only focus on max peaks
        static float old_peak_db[2] = {-INFINITY, -INFINITY};

        // fill up from engine buffers
	gx_engine::MaxLevel& m = gx_gui::GxMainInterface::get_instance().engine.maxlevel;
        for (int c = 0; c < 2; c++) {
            // update meters (consider falloff as well)
            // calculate peak dB and translate into meter
            float peak_db = -INFINITY;
            if (m.get(c) > 0) {
                peak_db = power2db(m.get(c));
            }
            // retrieve old meter value and consider falloff
            if (peak_db < old_peak_db[c]) {
	        peak_db = max(peak_db, old_peak_db[c] - falloff);
            }
            gui.getLevelMeter(c).set(log_meter(peak_db));
            old_peak_db[c] = peak_db;
        }
	m.reset();
    }
    // run thread again
    return TRUE;
}

/* -------------- for thread that checks jackd liveliness -------------- */
gboolean gx_survive_jack_shutdown(gpointer arg) {
    GtkWidget* wd = gx_gui::GxMainInterface::get_instance().getJackConnectItem();

    // return if jack is not down
    if (gx_system::gx_system_call("pgrep", "jackd", true) == SYSTEM_OK) {
        if (gx_gui::GxMainInterface::get_instance().jack.is_jack_down()) {
            // let's make sure we get out of here
            if (!gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(wd)))
                gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(wd), TRUE);

            // run only one time whem jackd is running
            return false;
        }
    } else {
        // set jack gxjack.client to NULL
        gx_gui::GxMainInterface::get_instance().jack.client = 0;

        // refresh some stuff. Note that it can be executed
        // more than once, no harm here
        gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(wd), FALSE);
        *gx_engine::GxJConvSettings::checkbutton7 = 0;
        gx_gui::GxMainInterface::get_instance().jack.set_jack_down(true);
    }
    // run as long jackd is down
    return true;
}

/* Update all user items reflecting zone z */
gboolean gx_update_all_gui(gpointer) {
    // the general Gui update handler
    gx_ui::GxUI::updateAllGuis();
    gx_gui::GxMainInterface::get_instance().engine.check_module_lists();
    return TRUE;
}

static gboolean conv_restart(gpointer data) {
    gx_gui::GxMainInterface::get_instance().engine.cabinet.start();
    return false;
}

void cab_conv_restart() {
    if (gx_gui::guivar.g_threads[5] == 0 || g_main_context_find_source_by_id(NULL, gx_gui::guivar.g_threads[5]) == NULL) {
        gx_gui::guivar.g_threads[5] = g_timeout_add_full(G_PRIORITY_HIGH_IDLE + 10, 0,
						 conv_restart,NULL,NULL);
    } else {
        gx_system::gx_print_warning(_("Cabinet Loading"), string(_(" cab thread is bussy")));
    }
}

static gboolean contrast_restart(gpointer data) {
    gx_gui::GxMainInterface::get_instance().engine.contrast.start();
    return false;
}

void contrast_conv_restart() {
    if (gx_gui::guivar.g_threads[9] == 0 || g_main_context_find_source_by_id(NULL, gx_gui::guivar.g_threads[9]) == NULL) {
        gx_gui::guivar.g_threads[9] = g_timeout_add_full(G_PRIORITY_HIGH_IDLE + 10, 0, contrast_restart,NULL,NULL);
    } else {
        gx_system::gx_print_warning(_("Presence Loading"), string(_(" presence thread is bussy")));
     }
}

gboolean gx_check_cab_state(gpointer) {
    if (gx_gui::GxMainInterface::get_instance().engine.cabinet.plugin.on_off) {
	if (gx_gui::GxMainInterface::get_instance().engine.cabinet.cabinet_changed()) {
            gx_gui::GxMainInterface::get_instance().engine.cabinet.conv_stop();
            cab_conv_restart();
	} else if (gx_gui::GxMainInterface::get_instance().engine.cabinet.sum_changed()) {
	    gx_gui::GxMainInterface::get_instance().engine.cabinet.conv_update();
        }
    }
    if (gx_gui::GxMainInterface::get_instance().engine.contrast.plugin.on_off) {
        if (gx_gui::GxMainInterface::get_instance().engine.contrast.sum_changed()) {
            gx_gui::GxMainInterface::get_instance().engine.contrast.conv_stop();
            contrast_conv_restart();
        }
    }
    return TRUE;
}

/** ----------- -------------------------------- ------------------  **/
}
