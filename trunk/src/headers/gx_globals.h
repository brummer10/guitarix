/*
 * Copyright (C) 2009, 2010 Hermann Meyer, James Warden, Andreas Degert
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
 *  This is the guitarix global variable declarations for all namespaces
 *  These global vars are created  /  initialized in gx_globals.cpp
 *
 * --------------------------------------------------------------------------
 */

#pragma once

#include <semaphore.h>

/* ----- main engine ----- */
namespace gx_engine
{
/* engine state : can be on or off or bypassed */
typedef enum {
	kEngineOff    = 0,
	kEngineOn     = 1,
	kEngineBypass = 2
} GxEngineState;

typedef enum {
	kMidiOff    = 0,
	kMidiOn     = 1
} GxMidiState;

/* global var  declarations */
extern const char* stopit;
extern float  checky;
extern float* get_frame;
extern float* get_frame1;
extern float* checkfreq;
extern float* oversample;
extern float* result;


/* number of channels */
extern int    gNumInChans;
extern int    gNumOutChans;

extern float* gInChannel [3];
extern float* gOutChannel[4];

/* latency warning  switch */
extern float fwarn_swap;
extern float fwarn;

/* engine init state  */
extern bool initialized;

/* buffer ready state */
extern bool buffers_ready;

extern int is_setup;

/** disable fft need some fix for work prop **/
/*
// fftw buffer and plans
extern fftw_complex *fftin, *fftout,*fftin1, *fftout1, *fftresult;
extern fftw_plan p, p1, pf;
*/
}

/* -------------------------------------------------------------------------- */

/* ----- jack namespace ----- */
namespace gx_jack
{
/* latency change confirmation */
typedef enum {
	kChangeLatency = 1,
	kKeepLatency   = 2
} GxJackLatencyChange;

extern const int nIPorts; // mono input
extern const int nOPorts; // stereo output + jconv
extern int NO_CONNECTION;

/* variables */
extern jack_nframes_t      jack_sr;   // jack sample rate
extern jack_nframes_t      jack_bs;   // jack buffer size
extern float               jcpu_load; // jack cpu_load
extern float               xdel;      // last xrun delay
extern int                 is_rt;     // jack is realtime ?

extern jack_client_t*      client ;
extern jack_port_t*        output_ports[];
extern jack_port_t*        input_ports [];

extern void*               midi_input_port_buf;
extern void*               midi_port_buf;

extern GxJackLatencyChange change_latency;

#ifdef USE_RINGBUFFER
extern struct MidiMessage  ev;
extern jack_ringbuffer_t*  jack_ringbuffer;
#endif

extern jack_port_t*        midi_input_port;
extern jack_port_t*        midi_output_ports;
extern jack_nframes_t      time_is;
extern bool                jack_is_down;
extern bool                jack_is_exit;
extern string              client_name;

extern string              client_out_graph;
extern string              gx_port_names[];

/* lists of jack port types for menu items */
enum {
	kAudioInput    = 0,
	kAudioOutput1  = 1,
	kAudioOutput2  = 2,
	kMidiInput     = 3,
	kMidiOutput    = 4
};
}

/* -------------------------------------------------------------------------- */

/* ----- JConv namespace ----- */
namespace gx_jconv
{
/* some global vars */
extern float checkbox7;
extern GtkWidget* mslider;
extern bool jconv_is_running;
}

/* -------------------------------------------------------------------------- */

/* ----- preset namespace ----- */
namespace gx_preset
{
/* global var declarations */
extern GdkModifierType list_mod[];
extern const char* preset_accel_path[];
extern const char* preset_menu_name[];
extern map<GtkMenuItem*, string> preset_list[];

extern string gx_current_preset;
extern string old_preset_name;

extern GtkWidget* presmenu[];
extern GtkWidget* presMenu[];

extern vector<string> plist;
extern bool setting_is_preset;

extern GCallback preset_action_func[];
}

/* -------------------------------------------------------------------------- */

/* ----- child process namespace ----- */
namespace gx_child_process
{
/* global var declarations  */

extern FILE*    jcap_stream;
extern FILE*    jconv_stream;
extern string   mbg_pidfile;

extern pid_t child_pid[];
}


/* -------------------------------------------------------------------------- */

/* ----- system namespace ----- */
namespace gx_system
{
/* message handling */
typedef enum {
	kInfo    = 1,
	kWarning,
	kError
} GxMsgType;

/* variables and constants */
extern const int SYSTEM_OK;
extern GtkTextIter iter1;
extern GtkTextIter iter2;

extern string rcpath;

extern const char*  guitarix_dir;
extern const char*  guitarix_reset;
extern const char*  guitarix_preset;
extern const char*  jcapsetup_file;
extern const char*  jcapfile_wavbase;
extern const char*  default_setting;
extern const string gx_pixmap_dir;
extern const string gx_style_dir;
extern const string gx_user_dir;
extern string gx_builder_dir;

/* shell variable names */
extern const char* shell_var_name[];
}

/* -------------------------------------------------------------------------- */

/* ----- GUI namespace ----- */
namespace gx_gui
{
typedef enum {
	kWvMode1 = 1,
	kWvMode2,
	kWvMode3
} GxWaveviewMode;

/* wave view globals */
extern bool           new_wave_view;
extern GxWaveviewMode wave_view_mode;

/* global GUI widgets */
extern GtkWidget* fWindow;
extern GtkWidget* menuh;
extern GtkWidget* pb;
extern GtkWidget* midibox;
extern GtkWidget* fbutton;
extern GtkWidget* record_button;
extern GtkWidget* jc_dialog;

/* wave view widgets */
extern GtkWidget* livewa;
extern GdkPixbuf* ib;
extern GdkPixbuf* ibm;
extern GdkPixbuf* ibr;

/* jack server status */
extern GtkWidget* gx_jackd_on_image;
extern GtkWidget* gx_jackd_off_image;

/* engine status images */
extern GtkWidget* gx_engine_on_image;
extern GtkWidget* gx_engine_off_image;
extern GtkWidget* gx_engine_bypass_image;
extern GtkWidget* gx_engine_item;

/* some more widgets */
extern GtkWidget* label6;
extern GtkWidget* label1;
extern GtkStatusIcon* status_icon;

/* tuner and osilloscope*/
extern int showwave;
extern int shownote;

/* skin handling */
extern vector<string> skin_list;
extern gint gx_current_skin;
extern int last_skin;
extern int no_opt_skin;
extern int set_knob;

/* for level display */
extern int meter_falloff;
extern int meter_display_timeout;

/*midi_in preset switch */
extern volatile gint       program_change;
extern sem_t               program_change_sem;

extern int show_eq;

extern int g_threads[];

/* names of port lists (exclude MIDI for now) */
extern string port_list_names[];

/* client port queues */
class StringComp
{
public:
	bool operator()(const string s1, const string s2) const
		{
			return s1.size() < s2.size();
		}
};

extern multimap<string, int, StringComp> gx_client_port_queue;
extern multimap<string, int, StringComp> gx_client_port_dequeue;
}

/* -------------------------------------------------------------------------- */

/* ----- cairo namespace ----- */
namespace gx_cairo
{
extern GdkPixbuf *tribeimage;
extern GdkPixbuf *tribeimage1;
extern GdkPixbuf *_image;

}
