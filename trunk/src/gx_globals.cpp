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
 * --------------------------------------------------------------------------
 *
 *  This is the guitarix global variable definitions for all namespaces
 *
 * --------------------------------------------------------------------------
 */

#include <cstring>
#include <list>
#include <map>
#include <vector>
#include <set>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <cstdio>

using namespace std;

//#include <fftw3.h>
#include <sndfile.h>
#include <jack/jack.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include "guitarix.h"

/* ------------------------------------------------------------------------- */

/* ----- main engine ----- */
namespace gx_engine
  {
    const char* stopit = "go";
    float  checky      = 1.0;
    float* get_frame   = NULL;
    float* get_frame1   = NULL;
    float* checkfreq   = NULL;
    float* oversample  = NULL;
    float* result      = NULL ;
    float 	GxEngine::ftbl0[65536];

    /* number of channels */
    int    gNumInChans;
    int    gNumOutChans;

    float* gInChannel [3];
    float* gOutChannel[4];

    /* latency warning  switch */
    float fwarn_swap;
    float fwarn;

    /* engine init state  */
    bool initialized = false;

    /* buffer ready state */
    bool buffers_ready = false;

    int is_setup = 0;

     /** disable fft need some fix for work prop **/
     /*
    // fftw buffer and plans
    fftw_complex *fftin, *fftout,*fftin1, *fftout1, *fftresult;
    fftw_plan p, p1, pf;
    */

  }


/* ------------------------------------------------------------------------- */

/* ----- jack namespace ----- */
namespace gx_jack
  {
    const int nIPorts = 3; // mono input
    const int nOPorts = 4; // stereo output + jconv
    int NO_CONNECTION = 1;

    /* variables */
    jack_nframes_t      jack_sr;   // jack sample rate
    jack_nframes_t      jack_bs;   // jack buffer size
    float               jcpu_load; // jack cpu_load
    float               xdel;      // last xrun delay
    int                 is_rt;

    jack_client_t*      client ;
    jack_port_t*        output_ports[nOPorts];
    jack_port_t*        input_ports [nIPorts];
    void*               midi_input_port_buf;
    void*               midi_port_buf;

    jack_port_t*        midi_input_port;

    jack_port_t*        midi_output_ports;
    jack_nframes_t      time_is;

    bool                jack_is_down = false;
    bool                jack_is_exit = false;
    GxJackLatencyChange change_latency;

#ifdef USE_RINGBUFFER
    struct MidiMessage  ev;
    jack_ringbuffer_t*  jack_ringbuffer;
#endif

    string client_name  = "guitarix";
    string client_out_graph = "";

    string gx_port_names[] =
    {
      "in_0",
      "out_0",
      "out_1",
      "out_2",
      "out_3"
    };

  }

/* ------------------------------------------------------------------------- */

/* ----- JConv namespace ----- */
namespace gx_jconv
  {
    /* some global vars */
    float checkbox7;
    GtkWidget* mslider;
    bool jconv_is_running = false;
  }

/* ------------------------------------------------------------------------- */

/* ----- preset namespace ----- */
namespace gx_preset
  {
    /* global var declarations */
    GdkModifierType list_mod[] =
    {
      GDK_NO_MOD_MASK,
      GDK_CONTROL_MASK,
      GDK_MOD1_MASK,
      GdkModifierType(GDK_CONTROL_MASK|GDK_MOD1_MASK)
    };

    const char* preset_accel_path[] =
    {
      "<guitarix>/Load",
      "<guitarix>/Save",
      "<guitarix>/Rename",
      "<guitarix>/Delete"
    };

    const char* preset_menu_name[] =
    {
      "_Load Preset...",
      "_Save Preset...",
      "_Rename Preset...",
      "_Delete Preset..."
    };

    map<GtkMenuItem*, string> preset_list[GX_NUM_OF_PRESET_LISTS];

    string gx_current_preset;
    string old_preset_name;

    GtkWidget* presmenu[GX_NUM_OF_PRESET_LISTS];
    GtkWidget* presMenu[GX_NUM_OF_PRESET_LISTS];

    vector<string> plist;
    bool setting_is_preset = false;

    GCallback preset_action_func[] =
    {
      G_CALLBACK(gx_load_preset),
      G_CALLBACK(gx_save_oldpreset),
      G_CALLBACK(gx_rename_preset_dialog),
      G_CALLBACK(gx_delete_preset_dialog)
    };
  }

/* ------------------------------------------------------------------------- */

/* ----- child process namespace ----- */
namespace gx_child_process
  {
    /* global var declarations */

    FILE*    jcap_stream;
    FILE*    jconv_stream;
    string   mbg_pidfile;

    pid_t child_pid[NUM_OF_CHILD_PROC] =
    {
      NO_PID,
      NO_PID,
      NO_PID
    };
  }

/* ------------------------------------------------------------------------- */

/* ----- system namespace ----- */
namespace gx_system
  {
    /* variables and constants */
    const int SYSTEM_OK = 0;

    GtkTextIter iter1;
    GtkTextIter iter2;

    string rcpath;

    const char* guitarix_dir     = ".guitarix";
    const char* guitarix_reset   = "resettings";
    const char* guitarix_preset  = "guitarixprerc";
    const char* jcapsetup_file   = "ja_ca_ssetrc";
    const char* jcapfile_wavbase = "guitarix_session";
    const char* default_setting  =
      "0.12 1 5000 130 1 5000 130 1 0.01 0.64 2 \n"
      "0 0.3 0.7 \n"
      "20 440 2 \n"
      "0.62 0.12 0 \n"
      "84 0 -1 9 0 101 4 0 0 34 0 9 1 20 64 12 1 20 0 0 \n"
      "-64.0 0.52 10 1.5 1.5 0 \n"
      "0.32 0.022 0.1 0.5 \n"
      "5 2 1 3 4 0 6 7 \n";

    const string gx_pixmap_dir = string(GX_PIXMAPS_DIR) + "/";
    const string gx_style_dir  = string(GX_STYLE_DIR) + "/";
    const string gx_user_dir   = string(getenv ("HOME")) + string("/") + string(guitarix_dir) + "/";

    /* shell variable names */
    const char* shell_var_name[] =
    {
      "GUITARIX2JACK_INPUTS",
      "GUITARIX2JACK_OUTPUTS1",
      "GUITARIX2JACK_OUTPUTS2",
      "GUITARIX2JACK_MIDI",
      "GUITARIX_RC_STYLE"
    };
  }


/* ------------------------------------------------------------------------- */

/* ----- GUI namespace ----- */
namespace gx_gui
  {
    /* wave view globals */
    bool           new_wave_view;
    GxWaveviewMode wave_view_mode;

    /* global GUI widgets */
    GtkWidget* fWindow;
    GtkWidget* menuh;
    GtkWidget* pb;
    GtkWidget* midibox;
    GtkWidget* fbutton;
    GtkWidget* record_button;
    GtkWidget* jc_dialog;

    /* wave view widgets */
    GtkWidget* livewa;
    GdkPixbuf* ib;
    GdkPixbuf* ibm;
    GdkPixbuf* ibr;
    GdkPixbuf* bbr;


    /* jack server status icons */
    GtkWidget* gx_jackd_on_image;
    GtkWidget* gx_jackd_off_image;

    /* engine status images */
    GtkWidget* gx_engine_on_image;
    GtkWidget* gx_engine_off_image;
    GtkWidget* gx_engine_bypass_image;
    GtkWidget* gx_engine_item;

    /* some more widgets. Note: change names please! */
    GtkWidget* label1;
    GtkWidget* label6;

    GtkStatusIcon* status_icon;

    int showwave = 0;
    int shownote = -1;
    int smoth_tuner = 0;
    float tuner_snother = 0;

    /* skin handling */
    vector<string> skin_list;
    gint gx_current_skin = 0;
    int last_skin = 0;
    int no_opt_skin = 0;
    int set_knob = 0;

    /* for level display */
    int meter_falloff = 27; // in dB/sec.
    int meter_display_timeout = 60; // in millisec

    /* midi_in preset switch */
    volatile gint       program_change = -1;
    sem_t               program_change_sem;

    int show_eq;
    /* names of port lists (exclude MIDI for now) */
    string port_list_names[NUM_PORT_LISTS] =
    {
      string("AudioIP"),
      string("AudioOPL"),
      string("AudioOPR")
    };

    /* client port queues */
    class StringComp;

    multimap<string, int, StringComp> gx_client_port_queue;
    multimap<string, int, StringComp> gx_client_port_dequeue;
  }

/* ------------------------------------------------------------------------- */

/* ----- cairo namespace ----- */
namespace gx_cairo
  {
    GdkPixbuf *tribeimage;
    GdkPixbuf *tribeimage1;
    GdkPixbuf *_image;

  }
