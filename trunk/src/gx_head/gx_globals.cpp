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
 * --------------------------------------------------------------------------
 *
 *  This is the gx_head global variable definitions for all namespaces
 *
 * --------------------------------------------------------------------------
 */

#include "guitarix.h"
#include <glibmm/i18n.h>

/* ------------------------------------------------------------------------- */

/* ----- main engine ----- */
namespace gx_engine
{
GxEngineState checky = kEngineOn;
float* get_frame   = NULL;
float* get_frame1   = NULL;
float* checkfreq   = NULL;
float* oversample  = NULL;
float* result      = NULL ;

/* latency warning  switch */
float fwarn;
float fwarn_swap;

/* engine init state  */
bool initialized = false;

/* engine init state  */
bool pt_initialized = false;

/* buffer ready state */
bool buffers_ready = false;

}


/* ------------------------------------------------------------------------- */

/* ----- jack namespace ----- */
namespace gx_jack
{

int NO_CONNECTION = 1;

void*               midi_input_port_buf;
void*               midi_port_buf;

bool                jack_is_down = false;
bool                jack_is_exit = false;
GxJackLatencyChange change_latency;

#ifdef USE_RINGBUFFER
struct MidiMessage  ev;
jack_ringbuffer_t*  jack_ringbuffer;
#endif

string client_name  = "gx_head_amp";
string client_insert_name  = "gx_head_fx";
string client_instance  = "gx_head";

string client_out_graph = "";

string gx_port_names[] =
{
	"in_0",
	"out_0",
	"out_1",
	"midi_in_1",
	"out_3"
};

}

/* ------------------------------------------------------------------------- */

/* ----- system namespace ----- */
namespace gx_system
{
/* variables and constants */
const int SYSTEM_OK = 0;

string rcpath;

const char* gx_head_dir     = ".gx_head";
const char* jcapsetup_file   = "ja_ca_ssetrc";
const char* jcapfile_wavbase = "gx_head_session";

const string gx_pixmap_dir = string(GX_PIXMAPS_DIR) + "/";
const string gx_user_dir   = string(getenv ("HOME")) + string("/") + string(gx_head_dir) + "/";

string gx_style_dir  = string(GX_STYLE_DIR1) + "/";
string gx_builder_dir = string(GX_BUILDER_DIR1) + "/";

/* shell variable names */
const char* shell_var_name[] =
{
	"GUITARIX2JACK_INPUTS",
	"GUITARIX2JACK_OUTPUTS1",
	"GUITARIX2JACK_OUTPUTS2",
	"GUITARIX2JACK_MIDI",
	"GUITARIX_RC_STYLE",
	"GUITARIX2JACK_UUID",
	"GUITARIX_LOAD_FILE"
};
}


/* ------------------------------------------------------------------------- */

/* ----- preset namespace ----- */
namespace gx_preset
{
/* global var declarations */

gx_gui::FileParameter gx_preset_file("system.current_preset_file");
gx_gui::FileParameter gx_factory_preset_file("system.factory_preset_file");

GdkModifierType list_mod[] =
{
	GDK_NO_MOD_MASK,
	GDK_CONTROL_MASK,
	GDK_MOD1_MASK,
	GdkModifierType(GDK_CONTROL_MASK|GDK_MOD1_MASK)
};

const char* preset_accel_path[] =
{
	"<gx_head>/Load",
	"<gx_head>/Save",
	"<gx_head>/Rename",
	"<gx_head>/Delete"
};

const char* preset_menu_name[] =
{
	N_("_Load Preset..."),
	N_("_Save Preset..."),
	N_("_Rename Preset..."),
	N_("_Delete Preset...")
};

//map<GtkMenuItem*, string> preset_list[GX_NUM_OF_PRESET_LISTS];

string gx_current_preset;
string gx_factory_preset;
string old_preset_name;

GtkWidget* presmenu[GX_NUM_OF_PRESET_LISTS];
GtkWidget* presMenu[GX_NUM_OF_PRESET_LISTS];

vector<string> plist;
vector<GtkMenuItem*> pm_list[GX_NUM_OF_PRESET_LISTS];

GtkWidget* fpresmenu;

GtkWidget* ffpresmenu[GX_NUM_OF_FACTORY_PRESET];
vector<string> fplist[GX_NUM_OF_FACTORY_PRESET];
vector<GtkMenuItem*> fpm_list[GX_NUM_OF_FACTORY_PRESET];


bool setting_is_preset = false;
bool setting_is_factory = false;

GCallback preset_action_func[] =
{
	G_CALLBACK(gx_load_preset),
	G_CALLBACK(gx_save_oldpreset),
	G_CALLBACK(gx_rename_preset_dialog),
	G_CALLBACK(gx_delete_preset_dialog)
};
}

/* ------------------------------------------------------------------------- */

/* ----- GUI namespace ----- */
namespace gx_gui
{



int showwave = 0;
int shownote = -1;
float show_patch_info = 0;



/* rack handlig */
int mono_plugs = 1;
int stereo_plugs = 1;
int refresh_size = 0;

int g_threads[10]={0,0,0,0,0,0,0,0,0,0};

/* for level display */
int meter_falloff = 27; // in dB/sec.
int meter_display_timeout = 60; // in millisec

/* midi_in preset switch */
volatile gint       program_change = -1;
sem_t               program_change_sem;

/* widget orientation */
float main_xorg;
float main_yorg;

}

/* ------------------------------------------------------------------------- */

/* ----- cairo namespace ----- */
namespace gx_cairo
{
GdkPixbuf *tribeimage;
GdkPixbuf *tribeimage1;
GdkPixbuf *tribeimage2;
}
