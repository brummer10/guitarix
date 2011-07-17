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

#include <errno.h>          // NOLINT
#include <cstring>          // NOLINT
#include <algorithm>        // NOLINT


namespace gx_threads {
static const float falloff = gx_gui::meter_falloff * gx_gui::meter_display_timeout * 0.001;

/* ----------------- refresh GX level display function ---------------- */
gboolean gx_refresh_meter_level(gpointer args) {
    if (gx_jack::gxjack.client && gx_engine::buffers_ready) {
        gx_gui::GxMainInterface* gui = gx_gui::GxMainInterface::instance();

        // data holders for meters
        // Note: removed RMS calculation, we will only focus on max peaks
        float max_level[2];
        (void)memset(max_level,   0, sizeof(max_level));

        static float old_peak_db[2] = {-INFINITY, -INFINITY};

        jack_nframes_t nframes = gx_jack::gxjack.jack_bs;

        // fill up from engine buffers
        for (int c = 0; c < 2; c++) {
            // guitarix output levels
            float data[nframes];

            // need to differentiate between channels due to stereo
            switch (c) {
            default:
            case 0:
                (void)memcpy(data, gx_engine::get_frame,  sizeof(data));
                break;

            case 1:
                (void)memcpy(data, gx_engine::get_frame1, sizeof(data));
                break;
            }

            // calculate  max peak
            for (guint f = 0; f < nframes; f++) {
                max_level[c] = max(max_level[c], abs(data[f]));
            }

            // update meters (consider falloff as well)
            // calculate peak dB and translate into meter
            float peak_db = -INFINITY;
            if (max_level[c] > 0.) {
                peak_db = power2db(max_level[c]);
            }

            // retrieve old meter value and consider falloff
            if (peak_db < old_peak_db[c]) {
                peak_db = old_peak_db[c] - falloff;
            }
            gui->getLevelMeter(c).set(log_meter(peak_db));
            old_peak_db[c] = max(peak_db, -INFINITY);
        }
    }
    // run thread again
    return TRUE;
}

/* -------------- refresh oscilloscope function -------------- */
gboolean gx_xrun_report(gpointer arg) {
    usleep(40);
    ostringstream s;
    s << " delay of at least " << gx_jack::gxjack.xdel << " microsecs";
    gx_system::gx_print_warning("Jack XRun", s.str());

    return FALSE;
}

/* --------- load preset triggered by midi program change --------- */
gboolean gx_do_program_change(gpointer arg) {
    int pgm = GPOINTER_TO_INT(arg);
    gx_engine::GxEngineState estate = gx_engine::checky;
    if (gx_preset::gxpreset.gx_nth_preset(pgm)) {
        if (estate == gx_engine::kEngineBypass)
            // engine bypass but preset found -> engine on
            gx_gui::gx_engine_switch(reinterpret_cast<GtkWidget*>(0), (gpointer)1);
    } else {
        if (estate == gx_engine::kEngineOn)
            // engine on but preset not found -> engine bypass
            gx_gui::gx_engine_switch(reinterpret_cast<GtkWidget*>(0), (gpointer)1);
    }
    // mainloop idle callback: do not call again
    return FALSE;
}

/* -------------- for thread that checks jackd liveliness -------------- */
gboolean gx_survive_jack_shutdown(gpointer arg) {
    GtkWidget* wd = gx_gui::GxMainInterface::instance()->getJackConnectItem();

    // return if jack is not down
    if (gx_system::gx_system_call("pgrep", "jackd", true) == gx_system::SYSTEM_OK) {
        if (gx_jack::gxjack.jack_is_down) {
            // let's make sure we get out of here
            if (!gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(wd)))
                gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(wd), TRUE);

            // run only one time whem jackd is running
            return false;
        }
    } else {
        // set jack gxjack.client to NULL
        gx_jack::gxjack.client = 0;

        // refresh some stuff. Note that it can be executed
        // more than once, no harm here
        gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(wd), FALSE);
        gx_jconv::GxJConvSettings::checkbutton7 = 0;
        gx_jack::gxjack.jack_is_down = true;
    }
    // run as long jackd is down
    return true;
}

/* Update all user items reflecting zone z */
gboolean gx_update_all_gui(gpointer) {
    // the general Gui update handler
    gx_ui::GxUI::updateAllGuis();
    // watch for tonestack and amp switch
    gx_engine::gx_check_engine_state(NULL);
    // watch for rack order
    gx_engine::gx_reorder_rack(NULL);
    return TRUE;
}

gboolean gx_check_cab_state(gpointer) {
    if (gx_engine::audio.fcab) {
        if (gx_engine::audio.cab_switched != gx_engine::audio.cabinet
                || fabs(gx_engine::audio.cab_sum - (gx_engine::audio.cab_level
                + gx_engine::audio.cab_bass + gx_engine::audio.cab_treble)) < -0.01
                || fabs(gx_engine::audio.cab_sum - (gx_engine::audio.cab_level
                + gx_engine::audio.cab_bass + gx_engine::audio.cab_treble)) > 0.01) {

            gx_engine::cab_conv.stop();
            gx_gui::cab_conv_restart();
        }
    }
    return TRUE;
}

/** ----------- Glibc THREADS RUNNING BY GUITARIX -----------------  **/
/** ----------- -------------------------------- ------------------  **/


// --- wait for USR1 signal to arrive and invoke ladi handler via mainloop
gpointer gx_signal_helper_thread(gpointer data) {
    int sig;
    int ret;
    sigset_t waitset;
    guint source_id = 0;
    sigemptyset(&waitset);
    sigaddset(&waitset, SIGUSR1);
    sigaddset(&waitset, SIGCHLD);
    sigprocmask(SIG_BLOCK, &waitset, NULL);
    while (true) {
        ret = sigwait(&waitset, &sig);
        if (ret == 0) {
            if (sig == SIGUSR1) {
                // do not add a new call if another one is already pending
                if (source_id == 0 || g_main_context_find_source_by_id(NULL, source_id) == NULL)
                    source_id = g_idle_add(gx_system::gx_ladi_handler, NULL);
            } else {
                assert(sig == SIGCHLD);
                source_id = g_idle_add(gx_child_process::gx_sigchld_handler, NULL);
            }
        } else {
            assert(errno == EINTR);
        }
    }
    // notreached
    return NULL;
}

// ---- feed a midi program change from realtime thread to ui thread
gpointer gx_program_change_helper_thread(gpointer data) {
    gint pgm;
    while (TRUE) {
        // wait for a semaphore post from jack realtime thread
        sem_wait(&gx_gui::program_change_sem);
        // atomic read and reset the variable
        do {
            pgm = g_atomic_int_get(&gx_gui::program_change);
        } while (!g_atomic_int_compare_and_exchange(&gx_gui::program_change, pgm, -1));
        assert(pgm != -1);
        // get the work done by ui thread
        g_idle_add(gx_do_program_change, (gpointer)pgm);
    }
    // notreached
    return NULL;
}

/** ------------------- Glibc THREADS END -------------------------  **/
/** ----------- -------------------------------- ------------------  **/
}
