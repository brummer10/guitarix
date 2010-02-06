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
 * ---------------------------------------------------------------------------
 *
 *    This are the guitarix multithreads related functionality
 *
 * ----------------------------------------------------------------------------
 */

#include <errno.h>

#include <assert.h>
#include <cstring>
#include <list>
#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <cstdio>

using namespace std;

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <jack/jack.h>
#include <sndfile.h>
//#include <fftw3.h>

#include "guitarix.h"

using namespace gx_system;
using namespace gx_child_process;
using namespace gx_gui;



namespace gx_threads
  {
    static const float falloff = meter_falloff * meter_display_timeout * 0.001;

    /* ----------------- refresh GX level display function ---------------- */
    gboolean gx_refresh_meter_level(gpointer args)
    {
      if (gx_jack::client && gx_engine::buffers_ready)
        {

          gx_gui::GxMainInterface* gui = gx_gui::GxMainInterface::instance();

          // data holders for meters
          // Note: removed RMS calculation, we will only focus on max peaks
          float max_level  [2];
          (void)memset(max_level,   0, sizeof(max_level));
          float max_jclevel[2];
          (void)memset(max_jclevel, 0, sizeof(max_jclevel));

          static float old_peak_db  [2] = {-INFINITY, -INFINITY};
          static float old_jcpeak_db[2] = {-INFINITY, -INFINITY};

          jack_nframes_t nframes = gx_jack::jack_bs;

          // retrieve meter widgets
          GtkWidget* const* meters   = gui->getLevelMeters();
          GtkWidget* const* jcmeters = gui->getJCLevelMeters();

          // fill up from engine buffers
          for (int c = 0; c < 2; c++)
            {
              // guitarix output levels
              float data[nframes];

              // jconv output levels
              float jcdata[nframes];

              // need to differentiate between channels due to stereo
              switch (c)
                {
                default:
                case 0:
                  (void)memcpy(data, gx_engine::get_frame,  sizeof(data));
                  break;

                case 1:
                  (void)memcpy(data, gx_engine::get_frame1, sizeof(data));
                  break;
                }

              // turn channels for box_pack_end
              int b;
              if (c)b=1;
              else b=2;
              // jconv: note that jconv monitor channels are input[1] and [2]
              if (gx_jconv::jconv_is_running && gx_engine::is_setup)
                (void)memcpy(jcdata, gx_engine::gInChannel[b], sizeof(jcdata));

              // calculate  max peak
              for (guint f = 0; f < nframes; f++)
                {
                  max_level[c] = max(max_level[c], abs(data[f]));

                  if (gx_jconv::jconv_is_running && gx_engine::is_setup)
                    max_jclevel[c] = max(max_jclevel[c], abs(jcdata[f]));
                }


              // update meters (consider falloff as well)
              if (meters[c])
                {
                  // calculate peak dB and translate into meter
                  float peak_db = -INFINITY;
                  if (max_level[c] > 0.) peak_db = power2db(max_level[c]);

                  // retrieve old meter value and consider falloff
                  if (peak_db < old_peak_db[c])
                    peak_db = old_peak_db[c] - falloff;

                  gtk_fast_meter_set(GTK_FAST_METER(meters[c]), log_meter(peak_db));
                  old_peak_db[c] = max(peak_db, -INFINITY);
                }


              if (gx_jconv::jconv_is_running && jcmeters[c] && gx_engine::is_setup)
                {
                  // calculate peak dB and translate into meter
                  float peak_db = -INFINITY;
                  if (max_jclevel[c] > 0.) peak_db = power2db(max_jclevel[c]);

                  // retrieve old meter value and consider falloff
                  if (peak_db < old_jcpeak_db[c])
                    peak_db = old_jcpeak_db[c] - falloff;

                  gtk_fast_meter_set(GTK_FAST_METER(jcmeters[c]), log_meter(peak_db));
                  old_jcpeak_db[c] = max(peak_db, -INFINITY);
                }
            }
        }
      // run thread again
      return TRUE;
    }

    /* -------------- refresh oscilloscope function -------------- */
    gboolean gx_refresh_oscilloscope(gpointer args)
    {
      // repaint the oscilloscope without involve updateAllGui().
      if ((showwave == 1) && ((gx_engine::GxEngineState)gx_engine::checky) &&(!gx_jack::NO_CONNECTION ))
        gdk_window_invalidate_rect(GDK_WINDOW(livewa->window),NULL,TRUE);
      //gx_engine::GxEngine::instance()->viv *= -1;
      // run thread again when needed
      if(showwave) return TRUE;
      else return FALSE;
    }

    /* -------------- refresh tuner function -------------- */
    gboolean gx_refresh_tuner(gpointer args)
    {
      // set the value to the tuner and let updateAllGui() do the repaint
      gx_engine::GxEngine* engine = gx_engine::GxEngine::instance();
      if (shownote )
        {
        engine->fConsta1t = engine->fConsta1;
        // run thread again
        return TRUE;
        }
      // dont run again
      return FALSE;
    }
    gboolean gx_xrun_report(gpointer arg)
    {

        ostringstream s;
        s << " delay of at least " << gx_jack::xdel << " microsecs";
        gx_print_warning("Jack XRun", s.str());

        return FALSE;
    }

    /* -------------- timeout for jconv startup when guitarix init -------------- */
    gboolean gx_check_startup(gpointer args)
    {
      // check if jack is alive
     // gx_survive_jack_shutdown(NULL);
      // get avaluable ports
     // gx_monitor_jack_ports(NULL);
      // set global variable the all whent well
      gx_engine::is_setup = 1;
      // case jconvolver is on at startup
      if (gx_jconv::GxJConvSettings::checkbutton7 == 1)
        gx_start_stop_jconv(NULL,NULL);
      // run only one time
      return FALSE;
    }

    /* --------- load preset triggered by midi program change --------- */
    gboolean gx_do_program_change(gpointer arg)
    {
      int pgm = (int)arg;
      gx_engine::GxEngineState estate =
        (gx_engine::GxEngineState)gx_engine::checky;
      if (gx_preset::gx_nth_preset(pgm))
        {
          if (estate == gx_engine::kEngineBypass)
            // engine bypass but preset found -> engine on
            gx_engine_switch ((GtkWidget*)0, (gpointer)1);
        }
      else
        {
          if (estate == gx_engine::kEngineOn)
            // engine on but preset not found -> engine bypass
            gx_engine_switch ((GtkWidget*)0, (gpointer)1);
        }
      // mainloop idle callback: do not call again
      return FALSE;
    }

    /* -------------- for thread that checks jackd liveliness -------------- */
    gboolean gx_survive_jack_shutdown(gpointer arg)
    {
      GtkWidget* wd = gx_gui::GxMainInterface::instance()->getJackConnectItem();

      // return if jack is not down
      if (gx_system_call("pgrep", "jackd", true) == SYSTEM_OK)
        {
          if (gx_jack::jack_is_down)
            {
              // let's make sure we get out of here
              if (!gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(wd)))
                gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(wd), TRUE);

              // revive existing client menus
              gx_gui::GxMainInterface::instance()->initClientPortMaps();
              // run only one time whem jackd is running
              return false;
            }
        }
      else
        {
          // set jack client to NULL
          gx_jack::client = 0;

          // refresh some stuff. Note that it can be executed
          // more than once, no harm here
          gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(wd), FALSE);
          gx_gui::GxMainInterface::instance()->deleteAllClientPortMaps();

          gx_jconv::GxJConvSettings::checkbutton7 = 0;
          gx_jconv::jconv_is_running = false;
          gx_jack::jack_is_down = true;
        }
      // run as long jackd is down
      return true;
    }

    /* ---------------------- monitor jack ports  items ------------------ */
    // we also refresh the connection status of these buttons
    gboolean gx_monitor_jack_ports(gpointer args)
    {
      // get gui instance
      gx_gui::GxMainInterface* gui = gx_gui::GxMainInterface::instance();

      // don't bother if we are not a valid client or if we are in the middle
      // of deleting stuff
      // if we are off jack or jack is down, delete everything
      if (!gx_jack::client || gx_jack::jack_is_down)
        {
          gui->deleteAllClientPortMaps();
          gx_client_port_dequeue.clear();
          gx_client_port_queue.clear();
          return TRUE;
        }

      // if the external client left without "unregistering" its ports
      // (yes, it happens, shame on the devs ...), we catch it here
      if (!gx_jack::client_out_graph.empty())
        {
          gx_client_port_dequeue.clear();
          gui->deleteClientPortMap(gx_jack::client_out_graph);
          gx_jack::client_out_graph = "";
          return TRUE;
        }

      // browse queue of added ports and update if needed
      gui->addClientPorts();

      // browse queue of removed ports and update if needed
      gui->deleteClientPorts();

      // loop over all existing clients
      set<GtkWidget*>::iterator cit = gui->fClientPortMap.begin();
      while (cit != gui->fClientPortMap.end())
        {
          // fetch client port map
          GtkWidget* portmap = *cit;
          GList* list = gtk_container_get_children(GTK_CONTAINER(portmap));

          guint len = g_list_length(list);
          if (len == NUM_PORT_LISTS) // something weird ...
            for (guint i = 0; i < len; i++)
              {
                // fetch client table
                GtkWidget* table = (GtkWidget*)g_list_nth_data(list, i);

                // check port connection status for each port
                gtk_container_foreach(GTK_CONTAINER(table),
                                      gx_refresh_portconn_status,
                                      GINT_TO_POINTER(i));
              }
          g_list_free(list);
          // next client
          cit++;
        }
      // run thraed again
      return TRUE;
    }

    /* Update all user items reflecting zone z */
    gboolean gx_update_all_gui(gpointer)
    {
      // the general Gui update handler
      gx_ui::GxUI::updateAllGuis();
      return TRUE;
    }

    /** ----------- Glibc THREADS RUNNING BY GUITARIX -----------------  **/
    /** ----------- -------------------------------- ------------------  **/


    //--- wait for USR1 signal to arrive and invoke ladi handler via mainloop
    gpointer gx_signal_helper_thread(gpointer data)
    {
      int sig;
      int ret;
      sigset_t waitset;
      guint source_id = 0;
      sigemptyset(&waitset);
      sigaddset(&waitset, SIGUSR1);
      sigprocmask(SIG_BLOCK, &waitset, NULL);
      while (true)
        {
          ret = sigwait(&waitset, &sig);
          if (ret == 0)
            {
              // do not add a new call if another one is already pending
              if (source_id == 0 || g_main_context_find_source_by_id(NULL, source_id) == NULL)
                source_id = g_idle_add(gx_ladi_handler, NULL);
            }
          else
            assert(errno == EINTR);
        }
      //notreached
      return NULL;
    }

    //---- feed a midi program change from realtime thread to ui thread
    gpointer gx_program_change_helper_thread(gpointer data)
    {
      gint pgm;
      while (TRUE)
        {
          // wait for a semaphore post from jack realtime thread
          sem_wait(&program_change_sem);
          // atomic read and reset the variable
          do
            {
              pgm = g_atomic_int_get(&program_change);
            }
          while (!g_atomic_int_compare_and_exchange(&program_change, pgm, -1));
          assert(pgm != -1);
          // get the work done by ui thread
          g_idle_add(gx_do_program_change, (gpointer)pgm);
        }
      //notreached
      return NULL;
    }

    /** ------------------- Glibc THREADS END -------------------------  **/
    /** ----------- -------------------------------- ------------------  **/

  }
