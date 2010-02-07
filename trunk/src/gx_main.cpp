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
 *    name         : "guitarix"
 *    version      : "0.04.7"
 *    authors      : "hermann meyer" & "james warden"
 *    contributors : "Julius O. Smith (jos at ccrma.stanford.edu)"
 *    license      : "GPL"
 *    copyright    : "(c)brummer 2008"
 *    reference    : "http://ccrma.stanford.edu/realsimple/faust_strings/"
 *
 *    Code prototype generated with Faust 0.9.9.4f (http://faust.grame.fr)
 * ----------------------------------------------------------------------------
 *
 *    This is guitarix main.
 *
 * ----------------------------------------------------------------------------
 */

/* link with  */
#include <sys/ioctl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <cmath>
#include <assert.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <unistd.h>
#include <sysexits.h>
#include <errno.h>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <dlfcn.h>
#include <pthread.h>
#include <limits.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <set>
#include <map>
#include <list>
#include <vector>

#include <sndfile.hh>
//#include <fftw3.h>
#include <libgen.h>
#include <jack/jack.h>
#include <jack/midiport.h>

#ifdef USE_RINGBUFFER
#include <jack/ringbuffer.h>
#endif

using namespace std;

/* guitarix own defines */
#include "guitarix.h"

using namespace gx_system;


/* --------- Guitarix main ---------- */
int main(int argc, char *argv[])
{
  // ----------------------- init GLIB threads ----------------------
  g_thread_init(NULL);

  //----- connect the signal handler for propper shutdown when a error appears
  signal(SIGQUIT, gx_signal_handler);
  signal(SIGTERM, gx_signal_handler);
  signal(SIGHUP,  gx_signal_handler);
  signal(SIGINT,  gx_signal_handler);
  //signal(SIGSEGV, gx_signal_handler); // quits application silently

  /* ----- block signal USR1 ---------
  ** inherited by all threads which are created later
  ** USR1 is processed synchronously by gx_signal_helper_thread
   */
  sigset_t waitset;
  sigemptyset(&waitset);
  sigaddset(&waitset, SIGUSR1);
  sigprocmask(SIG_BLOCK, &waitset, NULL);

  // ---------------------- user options handling ------------------
  string optvar[NUM_SHELL_VAR];
  gx_process_cmdline_options(argc, argv, optvar);

  // ---------------- Check for working user directory  -------------
  gx_system::gx_version_check();

  // ----------------------- init GTK interface----------------------
  gx_gui::GxMainInterface* gui = gx_gui::GxMainInterface::instance("guitarix", &argc, &argv);
  gui->setup();

  // ---------------------- initialize jack client ------------------
  if (gx_jack::gx_jack_init())
    {
      // -------- initialize guitarix engine --------------------------
      gx_engine::gx_engine_init();

      // -------- set jack callbacks and activation -------------------
      gx_jack::gx_jack_callbacks_and_activate();

      // -------- init port connections
      gx_jack::gx_jack_init_port_connection(optvar);
    }

  // ----------------------- run GTK main loop ----------------------
  gx_threads::gx_update_all_gui(NULL);
  gui->show();
  gui->run();

  // ------------- shut things down
  gx_system::gx_clean_exit(NULL, NULL);

  return 0;
}



