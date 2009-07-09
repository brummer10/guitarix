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
*/

/******************************************************************************
*******************************************************************************

								gx_funktions from guitarix
	guitarix.cpp
	here are the unsortet global funktions from guitarix
*******************************************************************************
*******************************************************************************/
#define GDK_NO_MOD_MASK (GdkModifierType)0

// global static fields
GtkWidget* fWindow, *menuh;
GtkWidget* pb, *midibox, *fbutton, *label1;
GdkPixbuf*   ib, *ibm, *ibr;
GtkStatusIcon*  status_icon;
GtkWidget* livewa, *warn_dialog,*disable_warn ;
GtkWidget* gx_engine_on_image;
GtkWidget* gx_engine_off_image;
GtkWidget* gx_engine_bypass_image;
GtkWidget* gx_engine_item;
GtkWidget* label6;

static float      checkbutton7;

float jackframe; // jack sample freq
float cpu_load;  // jack cpu_load
float checkbox7    = 1.0;
float checky       = 1.0;
float *get_frame   = NULL;
float *checkfreq   = NULL;
float *oversample  = NULL;


// engine state : can be on or off or bypassed
typedef enum {
  kEngineOff    = 0,
  kEngineOn     = 1,
  kEngineBypass = 2
} GxEngineState;

const char* stopit = "go";
const char* rcpath = " " ;
string jconvwav ;
string mbg_pidfile;

// guitarix setting, location and related stuff
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
  "-64.0 0.52 10 1.5 1.5 0 \n";

const string gx_pixmap_dir = 
  string(GX_PIXMAPS_DIR) + "/";
const string gx_style_dir = 
  string(GX_STYLE_DIR) + "/";
const string gx_user_dir = 
  string(getenv ("HOME")) + string("/") + string(guitarix_dir) + "/";

int offcut;
int lenghtcut;
int cm = 0;
int shownote = -1;
int view_mode = 0;
int showwave = 0;
int playmidi = 0;
int showit = 0;
int		gNumOutChans;
int frag;   // jack frame size
int NO_CONNECTION = 0;
int runjc = 0;
float fwarn_swap = 0;
int doit = 0;

FILE*              jcap_stream;
FILE*              control_stream1;
GTKUI*                 interface;

jack_client_t*      client ;
jack_port_t *output_ports[4];
jack_port_t *input_ports[1];
#ifndef USE_RINGBUFFER
void   *midi_port_buf;
#else
jack_ringbuffer_t *jack_ringbuffer;
#endif

jack_port_t *midi_output_ports;
jack_nframes_t time_is;
jack_nframes_t  jackframes;

#define ASCII_START (48)

//---- skin defines
vector<string> skin_list;
gint gx_current_skin = 0;

// skin handling
static void  gx_change_skin(GtkCheckMenuItem *menuitem, gpointer arg);
static void  gx_cycle_through_skin(GtkWidget *widget, gpointer arg);
static bool  gx_update_skin(const gint idx, const char* calling_func);
static void  gx_actualize_skin_index(const string& skin_name);

//---- system related defines and function proto
bool jack_is_running = false;

#define SYSTEM_OK (0)

#define NUM_OF_CHILD_PROC (3)
#define NO_PID (-1)

#define JACKCAP_IDX (0)
#define METERBG_IDX (1)
#define JCONV_IDX   (2)

pid_t child_pid[NUM_OF_CHILD_PROC] = {
  NO_PID,
  NO_PID,
  NO_PID
};

static FILE* gx_popen(const char*, const char*, const int);
static int   gx_pclose(FILE*, const int);
static pid_t gx_find_child_pid(const char*); 
static bool  gx_lookup_pid(const pid_t); 
static gint  gx_message_popup(const char*);
static bool  gx_capture_command(const int, string&);
static int   gx_system(const char*,
		       const char*,
		       const bool devnull = false,
		       const bool escape  = false);
static int   gx_system(const char*,
		       const string&,
		       const bool devnull = false,
		       const bool escape  = false);
static int   gx_system(const string&,
		       const char*,
		       const bool devnull = false,
		       const bool escape  = false);
// static int   gx_system(const string&,
// 		       const string&,
// 		       const bool devnull = false,
// 		       const bool escape  = false);

static void  gx_abort(void* arg);
static void  gx_start_jack(void* arg);
static void  gx_log_window(GtkWidget*, gpointer);

// choice dialog windows
static void gx_get_text_entry(GtkEntry*, string&);

static gint gx_choice_dialog_with_text_entry (
   const char* window_title,
   const char* msg,
   const char* label1,
   const char* label2,
   const gint resp1,
   const gint resp2,
   const gint default_response,
   GCallback func
);

static gint gx_choice_dialog_without_entry (
   const char* window_title,
   const char* msg,
   const char* label1,
   const char* label2,
   const gint resp1,
   const gint resp2,
   const gint default_response
);

//----- preset handling
#define GX_NUM_OF_PRESET_LISTS (3)
#define SAVE_PRESET_LIST   (0)
#define LOAD_PRESET_LIST   (1)
#define RENAME_PRESET_LIST (2)
#define DELETE_PRESET_LIST (3)

GdkModifierType list_mod[] = {
  GDK_CONTROL_MASK,
  GDK_NO_MOD_MASK,
  GDK_MOD1_MASK,
  GdkModifierType(GDK_CONTROL_MASK|GDK_MOD1_MASK)
};

const char* preset_accel_path[] = {
  "<guitarix>/Save",
  "<guitarix>/Load",
  "<guitarix>/Rename",
  "<guitarix>/Delete"
};

const char* preset_menu_name[] = {
  "_Save Preset...",
  "_Load Preset...",
  "_Rename Preset...",
  "_Delete Preset..."
};

map<GtkMenuItem*, string> preset_list[GX_NUM_OF_PRESET_LISTS];

string gx_current_preset;
string old_preset_name;

GtkWidget* presmenu[GX_NUM_OF_PRESET_LISTS];
GtkWidget* presMenu[GX_NUM_OF_PRESET_LISTS];

static void  gx_save_newpreset_dialog (GtkMenuItem*, gpointer);
static void  gx_save_newpreset (GtkEntry*);
static void  gx_save_preset (const gchar*, bool);
static void  gx_save_oldpreset (GtkMenuItem*, gpointer);

static void  gx_load_preset (GtkMenuItem*, gpointer);
static void  gx_recall_main_setting(GtkMenuItem*, gpointer);
static void  gx_save_main_setting(GtkMenuItem*, gpointer);

static void  gx_rename_preset (GtkEntry*);
static void  gx_rename_preset_dialog (GtkMenuItem*, gpointer);
static void  gx_rename_active_preset_dialog(GtkWidget*, gpointer);

static void  gx_delete_preset(GtkMenuItem*, gpointer);
static void  gx_delete_preset_dialog (GtkMenuItem*, gpointer);
static void  gx_delete_active_preset_dialog(GtkWidget*, gpointer);

static void  gx_delete_all_presets_dialog(GtkMenuItem*, gpointer);
static void  gx_delete_all_presets();

static void  gx_add_preset_to_menus(const string&);
static void  gx_add_single_preset_menu_item(const string&,
					    const gint,
					    GCallback);

static void  gx_del_single_preset_menu_item(const string&,
					    const gint);
static void  gx_del_preset_from_menus(const string&);
static void  gx_refresh_preset_menus();
static void  gx_cleanup_preset_name(string& presname);

static void  gx_next_preset(GtkWidget*, gpointer);
static void  gx_previous_preset(GtkWidget*, gpointer);

GtkMenuItem* const gx_get_preset_item_from_name(int, const string&);


GCallback preset_action_func[] = {
  G_CALLBACK(gx_save_oldpreset),
  G_CALLBACK(gx_load_preset),
  G_CALLBACK(gx_rename_preset_dialog),
  G_CALLBACK(gx_delete_preset_dialog)
};

// which kind of setting we currently are in
bool setting_is_preset = false;

// warpper that takes an int and returns a string
static const string& gx_i2a(int);


// ---- log message handling
typedef enum {
  kInfo    = 1,
  kWarning = 2,
  kError   = 3
} GxMsgType;

// ---- log message handler
void gx_print_logmsg(const char* func, const string& msg, GxMsgType msgtype)
{

  string msgbuf = ">  ";
  msgbuf += func;
  msgbuf += "  ***  ";
  msgbuf += msg;

  // log the stuff to the log message window if possible
  bool terminal = false;
  if (interface)
  {
    // retrievw window
    GtkTextView* logw = interface->getLoggingWindow();

    if (logw)
    {

      GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(logw));
      gtk_text_buffer_set_text(buffer, msgbuf.c_str(), -1);

      static GtkTextTag* taginfo = 
	gtk_text_buffer_create_tag(buffer, "colinfo", "foreground", "#00ced1", NULL);

      static GtkTextTag* tagwarn = 
	gtk_text_buffer_create_tag(buffer, "colwarn", "foreground", "#ff8800", NULL);

      static GtkTextTag* tagerror = 
	gtk_text_buffer_create_tag(buffer, "colerr", "foreground", "#ff0000", NULL);

      GtkTextTag* tag = taginfo;

      static string col;
      switch (msgtype)
      {
      case kInfo: default: col = "#00ced1"; break;
      case kWarning: col = "#ff8800"; tag = tagwarn;  break;
      case kError:   col = "#ff0000"; tag = tagerror; break;
      }  


      GtkTextIter start, end;
      gtk_text_buffer_get_bounds (buffer, &start, &end);
      gtk_text_buffer_apply_tag(buffer, tag, &start, &end);

      // modify expander bg color is closed
      GtkExpander* exbox = interface->getLoggingBox();
      if (gtk_expander_get_expanded(exbox) == FALSE)
      {
	GdkColor exp_color;
	gdk_color_parse(col.c_str(), &exp_color);
	gtk_widget_modify_fg(GTK_WIDGET(exbox), GTK_STATE_NORMAL, &exp_color);
      }
    }
    else
      terminal = true;
  }
  else terminal = true;
      
  // if no window, then terminal
  if (terminal)
    {  msgbuf += "\n"; cerr << msgbuf; }
}

// warning
void gx_print_warning(const char* func, const string& msg)
{
  gx_print_logmsg(func, msg, kWarning);
}

// error
void gx_print_error(const char* func, const string& msg)
{
  gx_print_logmsg(func, msg, kError);
}

// info
void gx_print_info(const char* func, const string& msg)
{
  gx_print_logmsg(func, msg, kInfo);
}


// ---- check version and if directory exists and create it if it not exist
bool gx_version_check()
{
    struct stat my_stat;

//----- this check dont need to be against real version, we only need to know
//----- if the presethandling is working with the courent version, we only count this
//----- string when we must remove the old preset files.
    string rcfilename = 
      gx_user_dir + string("version-") + string("0.03.3") ;

    if  (stat(gx_user_dir.c_str(), &my_stat) == 0) // directory exists
    {
      // check which version we're dealing with
      if  (stat(rcfilename.c_str(), &my_stat) != 0) 
      {
	// current version not there, let's create it and refresh the whole shebang
	string oldfiles = gx_user_dir + string("guitarix*rc");
	(void)gx_system ("rm -f", oldfiles.c_str(), false);

	oldfiles = gx_user_dir + string("version*");
	(void)gx_system ("rm -f", oldfiles.c_str(), false);

	oldfiles = gx_user_dir + string("*.conf");
	(void)gx_system ("rm -f", oldfiles.c_str(), false);

	// setting file for current version
	ofstream f(rcfilename.c_str());
	string cim = string("guitarix-") + GX_VERSION;
	f << cim <<endl;
	f.close();

	string resetfile = gx_user_dir + "resettings";
	ofstream fa(resetfile.c_str());
	fa <<  default_setting <<endl;
	fa.close();
      }
    }
    else // directory does not exist
    {
      // create .guitarix directory
      (void)gx_system("mkdir -p", gx_user_dir.c_str(), false);

      // setting file for current version
      ofstream f(rcfilename.c_str());
      string cim = string("guitarix-") + GX_VERSION;
      f << cim <<endl;
      f.close();

      // --- create jack_capture setting file
      string tmpstr = gx_user_dir + jcapsetup_file;

      (void)gx_system("touch", tmpstr.c_str(), false);
      (void)gx_system(
	 "echo 'jack_capture -c 2 --silent --disable-meter --port guitarix:out* ' >",
	 tmpstr.c_str(),
	 false
      );

      // --- version file
      //same here, we only change this file, when the presethandling is broken,
      // otherwise we can let it untouched
      tmpstr = gx_user_dir + string("version-") + string("0.03.3");
      (void)gx_system("touch", tmpstr.c_str(), false);

      cim = string("echo 'guitarix-") + string(GX_VERSION) + "' >";
      (void)gx_system(cim.c_str(), tmpstr.c_str(), false);

      // --- guitarix own default settings
      tmpstr = gx_user_dir + guitarix_reset;
      (void)gx_system("touch", tmpstr.c_str(), false);

      cim = "echo -e '" + string(default_setting) + "' >";
      (void)gx_system(cim.c_str(), tmpstr.c_str(), false);
    }

    return TRUE;
}

//----- we must make sure that the images for the status icon be there
int gx_pixmap_check()
{
    struct stat my_stat;

    string gx_pix   = gx_pixmap_dir + "guitarix.png";
    string midi_pix = gx_pixmap_dir + "guitarix-midi.png";
    string warn_pix = gx_pixmap_dir + "guitarix-warn.png";

    if ((stat(gx_pix.c_str(), &my_stat) != 0)   || 
	(stat(midi_pix.c_str(), &my_stat) != 0) ||	
	(stat(warn_pix.c_str(), &my_stat) != 0))
	
    {
      gx_print_error(
	 "Pixmap Check",
	 string(" cannot find installed pixmaps! giving up ...")
      );

      // giving up
      return 1;
    }

    GtkWidget *ibf =  gtk_image_new_from_file (gx_pix.c_str());
    ib = gtk_image_get_pixbuf (GTK_IMAGE(ibf));
    GtkWidget *stim = gtk_image_new_from_file (midi_pix.c_str());
    ibm = gtk_image_get_pixbuf (GTK_IMAGE(stim));
    GtkWidget *stir = gtk_image_new_from_file (warn_pix.c_str());
    ibr = gtk_image_get_pixbuf (GTK_IMAGE(stir));

    return 0;
}

//----convert int to string
void gx_IntToString(int i, string & s)
{
  s = "";

  int abs_i = abs(i);
  do {
    // note: using base 10 since 10 digits (0123456789)
    char c = static_cast<char>(ASCII_START+abs_i%10);
    s.insert(0, &c, 1);
  } while ((abs_i /= 10) > 0);
  if (i < 0) s.insert(0, "-");
}

const string& gx_i2a(int i)
{
  static string str;
  gx_IntToString(i, str);
  
  return str;
}

//----use jack_capture for record the session
bool gx_capture(const char* capturas)
{
  // open a write stream for controling the stop function
  jcap_stream = gx_popen(capturas, "w", JACKCAP_IDX);
  return (jcap_stream != NULL);
}

bool		GTKUI::fInitialized = false;
list<UI*>	UI::fGuiList;

//----refresh status display
void gx_refresh_engine_status_display()
{
  GxEngineState estate = (GxEngineState)checky;
  string state;

  switch (estate) {

  case kEngineOff:
    gtk_widget_show(gx_engine_off_image);
    gtk_widget_hide(gx_engine_on_image);
    gtk_widget_hide(gx_engine_bypass_image);

    gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(gx_engine_item), FALSE);
    state = "OFF";
    break;

  case kEngineBypass:
    gtk_widget_show(gx_engine_bypass_image);
    gtk_widget_hide(gx_engine_off_image);
    gtk_widget_hide(gx_engine_on_image);

    gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(gx_engine_item), TRUE);
    state = "BYPASSED";
    break;

  case kEngineOn:
  default: // ON
    gtk_widget_show(gx_engine_on_image);
    gtk_widget_hide(gx_engine_off_image);
    gtk_widget_hide(gx_engine_bypass_image);

    gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(gx_engine_item), TRUE);
    state = "ON";
  }

  gx_print_info("Engine State: ", state);
}

//----menu function play stop
void gx_engine_switch (GtkWidget* widget, gpointer arg)
{
  GxEngineState estate = (GxEngineState)checky;

  switch (estate) 
  {
  case kEngineOn:
    estate = kEngineOff;
    if (arg)
    {  
      // need to activate item
      gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(gx_engine_item), TRUE);
      estate = kEngineBypass;
    }

    break;

  case kEngineOff:
    if (!arg)
      estate = kEngineOn;
    break;
    
  default:
    estate = kEngineOn;
    gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(gx_engine_item), TRUE);
  }


  checky = (float)estate;
  gx_refresh_engine_status_display();
}

//----menu function gx_meterbridge
void gx_meterbridge (GtkCheckMenuItem *menuitem, gpointer checkplay)
{

  // no need to do all this if jack is not running
  if (!jack_is_running)
  {
    // let's make sure we have no proc stuff left
    string old_lock = gx_user_dir + string(".mbg_") + "*";
    (void)gx_system("rm -f", old_lock.c_str());
    child_pid[METERBG_IDX] = NO_PID;

    return;
  }
   
  // PID file (used as lock file)
  const char* app_name = "meterbridge";
  mbg_pidfile = gx_user_dir + string(".mbg_") + jack_get_client_name(client);

  // is it installed ?
  int meterbridge_ok = gx_system("which", app_name);
  if (meterbridge_ok != SYSTEM_OK) // no meterbridge installed
  {
    // reset meterbridge GUI button state to inactive
    gtk_check_menu_item_set_active(menuitem, FALSE);
    gx_message_popup(
       "  "
       " WARNING [meterbridge]\n\n "
       " meterbridge is not installed! "
    );
    return;
  }


  // ---- if triggered by GUI or Alt + M
  if (gtk_check_menu_item_get_active(menuitem) == TRUE)
  {
    if (gx_system("ls", mbg_pidfile.c_str()) == SYSTEM_OK)
    {
      // get PID from lock file
      pid_t old_pid;
      
      ifstream fi(mbg_pidfile.c_str());
      if (fi.good()) { fi >> old_pid; fi.close(); }

      // do we have meterbridge running ?
      if (gx_lookup_pid(old_pid)) // yeps
      {	
	// refresh internal pid store
	child_pid[METERBG_IDX] = old_pid;
	gx_print_info("Meterbridge", 
		      string("meterbridge started at PID = ") + 
		      gx_i2a(old_pid));
	return;
      }

      // if not running, preliminary clean up
      (void)gx_system("rm -f", mbg_pidfile.c_str());
      child_pid[METERBG_IDX] = NO_PID;
    }

    string mbg_opt("-n ");
    mbg_opt += jack_get_client_name(client);
    mbg_opt += "_";
    mbg_opt += app_name;
    mbg_opt += " -t sco guitarix:in_0  guitarix:out_0";

    meterbridge_ok = gx_system(app_name, mbg_opt.c_str(), true, true);
    usleep(1000); // let's give it 1ms

    // not running, ? oops ...
    if (meterbridge_ok != SYSTEM_OK) 
    {
      // reset meterbridge GUI button state to inactive
      gtk_check_menu_item_set_active(menuitem, FALSE);
      gx_message_popup(
         "  "
	 "WARNING [meterbridge]\n\n  "
         "meterbridge could not be launched!"
      );

      gx_print_error("Meterbridge", 
		     string("meterbridge could not be launched!"));

      return;
    }

    // running, so let's store PID in lock file
    ofstream fo(mbg_pidfile.c_str());
    if (fo.good())
    {
      child_pid[METERBG_IDX] = gx_find_child_pid(app_name);
      fo << child_pid[METERBG_IDX];
      fo.close();

      gx_print_info("Meterbridge", 
		    string("meterbridge started at PID = ") +
		    gx_i2a(child_pid[METERBG_IDX]));
    }
  }

  else // -- deactivate meterbridge
  {
    if (child_pid[METERBG_IDX] != NO_PID)
    {
      // do we really have meterbridge running ?
      if (!gx_lookup_pid(child_pid[METERBG_IDX])) // nope
      {
	// it could be that the user closed meterbridge
	// by hand and is trying to bring it back via guitarix
	child_pid[METERBG_IDX] = NO_PID;

	// try again
	gtk_check_menu_item_set_active(menuitem, TRUE);
	gx_meterbridge (menuitem, 0);
	return;
      }

      // remove lock file
      (void)gx_system("rm -f", mbg_pidfile.c_str());

      // kill process
      (void)kill(child_pid[METERBG_IDX], SIGTERM);
      gx_print_warning("Meterbridge", 
		       string("meterbridge terminated - was PID ") +
		       gx_i2a(child_pid[METERBG_IDX]));

      child_pid[METERBG_IDX] = NO_PID;
    }
  }
}

//----menu function gx_show_oscilloscope
void gx_show_oscilloscope (GtkCheckMenuItem *menuitem, gpointer checkplay)
{
    if (gtk_check_menu_item_get_active(menuitem) == TRUE)
    {
        showwave = 1;
        gtk_widget_show(livewa);
 
    }
    else
    {
        showwave = 0;
        gtk_widget_hide(livewa);
 
    }
}

//----menu function gx_tuner
void gx_tuner (GtkCheckMenuItem *menuitem, gpointer checkplay)
{
    if (gtk_check_menu_item_get_active(menuitem) == TRUE)
    {
        shownote = 1;
        gtk_widget_show(pb);
    }
    else
    {
        shownote = 0;
        gtk_widget_hide(pb);
    }
}

//---- menu function gx_midi_out
void gx_midi_out (GtkCheckMenuItem *menuitem, gpointer checkplay)
{
    if (gtk_check_menu_item_get_active(menuitem) == TRUE)
    {
        playmidi = 1;
        gtk_widget_show(midibox);
    }
    else
    {
        playmidi = 0;
        gtk_widget_hide(midibox);
    }
}


//---- menu function gx_midi_out
void gx_log_window (GtkWidget* menuitem, gpointer arg)
{
  // ugly init hack (GTK peculiar init stuff).
  static bool init = false;
  if (!init)
  {
    init = true;
    return;
  }

  GtkExpander* const exbox = interface->getLoggingBox();

  // we could be called before UI is built up
  if (!exbox) return;

  // open it
  if (gtk_expander_get_expanded(exbox) ==  TRUE)
    gtk_expander_set_expanded(exbox, FALSE);

  // close it
  else
    gtk_expander_set_expanded(exbox, TRUE);

  // in any case, reset handle color
  GdkColor exp_color;
  gdk_color_parse("#ffffff", &exp_color);
  gtk_widget_modify_fg (GTK_WIDGET(exbox), GTK_STATE_NORMAL, &exp_color);
}


//---- start or stop record when toggle_button record is pressed
void gx_run_jack_capture (GtkWidget *widget, gpointer data)
{
    // here, const applies to pointer, not pointed data ;)
    GtkToggleButton* const cap_button = (GtkToggleButton*)widget;

    // avoid running it at startup
    // (ugly hack due to GTK+ signalling side effect)
    static bool cap_init = false;
    if (!cap_init)
    {
      gtk_toggle_button_set_active(cap_button, FALSE);
      cap_init = true;
      return;
    }

    // is the button toggled ?
    const gboolean tggl_state = gtk_toggle_button_get_active(cap_button);

    // increment if capturing more than once
    static int capas = 0;

    // ---- stop recording
    if (tggl_state == FALSE) // nope
    {
      // get jack_cap pid spawned by guitarix
      const pid_t cap_pid = child_pid[JACKCAP_IDX];

      if (cap_pid != NO_PID) // running
      {
	if (kill(cap_pid, SIGINT) == -1)
	  gx_print_error("Record",
			 string(" Sorry, could not stop (Ctrl-C) jack_capture"));
	else
	  gx_print_info("Record",
			string(" Terminated jack_capture, session file #") +
			gx_i2a(capas-1));

	(void)gx_pclose(jcap_stream, JACKCAP_IDX);
	jcap_stream = NULL;
      }

      // reset pid nonetheless
      child_pid[JACKCAP_IDX] = NO_PID;

      // let's get out of here
      return;
    }


    // ---- button has been toggled, let's try to record
    int const jack_cap_ok = gx_system("which", "jack_capture");

    // popup message if something goes funny
    string warning("  WARNING [jack_capture]\n  ");

    if (jack_cap_ok != SYSTEM_OK) // no jack_capture in PATH! :(
    {
      warning.append(
	"You need jack_capture <= 0.9.30 "
	"by Kjetil S. Matheussen  \n  "
	"please look here\n  "
	"http://old.notam02.no/arkiv/src/?M=D\n"
      );
    }
    else
    {
      // so far so good, start capture
      string capturas;

      if (gx_capture_command(capas, capturas))
      {
	if (!gx_capture(capturas.c_str()))
	  warning.append("Sorry, could not start jack_capture");
      }
      else
      {
	warning.append("Could not open wav capture file");
      }
    }

    // are we running ?
    if (child_pid[JACKCAP_IDX] != NO_PID)
    {
      gx_print_info("Record",
		    string("Started jack_capture, session file #") + gx_i2a(capas));
      capas++;
      return;
    }

    // nope :(
    gtk_toggle_button_set_active(cap_button, FALSE);
    gx_print_warning("Record", warning);
}

//----menu funktion load
void gx_load_preset (GtkMenuItem *menuitem, gpointer load_preset)
{
  // check that we do have presets
  if (preset_list[LOAD_PRESET_LIST].size() == 0)
  {
    gx_print_warning("Preset Loading", 
		     "Preset list is empty, make some :)");
    return;
  }

  JCONV_SETTINGS myJCONV_SETTINGS;
  checkbutton7 = 0;
  
  interface->updateAllGuis();

  // retrieve preset name
  string preset_name = preset_list[LOAD_PRESET_LIST][menuitem];

  // load jconv setting
  string jc_preset   = gx_user_dir + string("jconv_") + preset_name + ".conf ";
  string jc_file     = gx_user_dir + string("jconv_set.conf");
  string file_copy   = jc_preset + jc_file;
  (void)gx_system("cp -f", file_copy.c_str(), true);
  
  // set jconv
  myJCONV_SETTINGS.get_jconfset ();

  // recall preset by name
  // Note: the UI does not know anything about guitarix's directory stuff
  // Need to pass it on
  string presetfile = gx_user_dir + "guitarixprerc";
  bool preset_ok = interface->recallPresetByname(presetfile.c_str(), 
						 preset_name.c_str());
  
  // check result
  if (!preset_ok)
  {
    gx_print_error("Preset Loading", string("Could not load preset ") + preset_name);
    return;
  }
  
  // refresh main window name
  string title = string("guitarix ") + preset_name;
  gtk_window_set_title (GTK_WINDOW (fWindow), title.c_str());
  
  // print out info
  gx_print_info("Preset Loading", string("loaded preset ") + preset_name);
  
  setting_is_preset = true;
  gx_current_preset = preset_name;
}


//---- funktion save
void gx_save_preset (const char* presname, bool expand_menu)
{

    string setting;
    interface->updateAllGuis();
    interface->getState(setting);

    // save preset and update menus
    if (setting.empty())
    {  
      gx_print_error("Preset Saving", 
		     string("setting EMPTY!! could not save preset ") 
		     + string(presname));
      return;
    }
    
    // append preset name in front
    setting.insert(0, presname);

    // manipulate preset file
    string presetfile = gx_user_dir + guitarix_preset;
    string tmpfile    = presetfile + "_tmp";
    
    (void)gx_system("touch", presetfile.c_str());
    usleep(200);

    (void)gx_system("touch", tmpfile.c_str());
    usleep(200);

    // copy actual presetfile to tmpfile minus preset to be saved
    ostringstream cat_tmpfile; string space = " ";
    cat_tmpfile << presetfile << space 
		<< "| grep -v" << space << presname << space
		<< ">" << tmpfile;    

    (void)gx_system("cat", cat_tmpfile.str());
    usleep(200);

    // append saved preset to tmpfile
    (void)gx_system("echo", setting + string(" >> ") + tmpfile); 
    usleep(200);

    // rename tmp file to preset file
    rename(tmpfile.c_str(), presetfile.c_str());


    // remove tmp file (not necessary)
    (void)gx_system("rm -f", tmpfile);

    // update preset menus if needed
    if (expand_menu)
      gx_add_preset_to_menus(string(presname));

    // refresh display
    string ttle = string("guitarix ") + presname;
    gtk_window_set_title (GTK_WINDOW (fWindow), (gchar*)ttle.c_str());

    string jc_file      = gx_user_dir + string("jconv_set.conf ");
    string jc_preset    = gx_user_dir + string("jconv_") + string(presname) + ".conf";
    string file_copy    = jc_file + jc_preset; 
    (void)gx_system("cp", file_copy);

    // we are now in a preset setting
    setting_is_preset = true;
    gx_current_preset = presname;

    gx_print_info("Preset Saving", string("saved preset ") + string(presname));
}

//----menu funktion save
void gx_save_oldpreset (GtkMenuItem *menuitem, gpointer arg)
{
  guint save_active = GPOINTER_TO_UINT(arg);
  string presname;
  
  // are saving an active preset
  if (save_active)
  {
    if (gx_current_preset.empty())
    {
      gx_print_warning("Saving Active Preset", 
		       "We are in main setting, load a preset first");
      return;
    }
    presname = gx_current_preset;
  }

  // we are saving another preset from the menu
  else 
    presname = preset_list[SAVE_PRESET_LIST][menuitem];

  gx_save_preset(presname.c_str(), false);
}

//----clean up preset name given by user
void gx_cleanup_preset_name(string& presname)
{
  int p = presname.find(' ', 0);
  while (p != -1)
  {
    presname.replace(p++, 1, "-");
    p = presname.find(' ', p);
  }
}

//----menu funktion save
void gx_save_newpreset (GtkEntry* entry)
{
  string presname;
  gx_get_text_entry(entry, presname);

  // no text ?
  if (presname.empty())
  {
    gx_print_error("Saving new preset", "no preset name given");
    return;
  }

  // replace spaces by -
  gx_cleanup_preset_name(presname);

  // is the name alrady taken ?
  map<GtkMenuItem*, string>::iterator it;
  for (it  = preset_list[SAVE_PRESET_LIST].begin(); 
       it != preset_list[SAVE_PRESET_LIST].end();
       it++)
  {
    // found a match 
    if (presname == it->second)
    {
      gx_print_error("New Preset Saving", 
		     string("preset name ") + 
		     presname + 
		     string(" already in use, choose another one"));
      gx_save_newpreset_dialog(it->first, NULL);
      return;
    }
  }

  // finally save to preset file
  gx_save_preset(presname.c_str(), true);
}

// read name for presset
void gx_recall_main_setting(GtkMenuItem* item, gpointer arg)
{
  if (!client || !jack_is_running)
  {
    gx_print_warning("Main Setting recalling", "We are not a jack client!");
    return;
  }

  string jname = jack_get_client_name(client);
  string previous_state = gx_user_dir + jname + "rc";
  interface->recallState(previous_state.c_str());
  gtk_window_set_title(GTK_WINDOW(fWindow), jname.c_str());

  gx_print_info("Main Setting recalling", 
		string("Called back main setting"));

  setting_is_preset = false;
  gx_current_preset = "";
}

// ----- save current setting as main setting
void gx_save_main_setting(GtkMenuItem* item, gpointer arg)
{
  if (!client || !jack_is_running)
  {
    gx_print_warning("Main Setting Saving", "We are not a jack client!");
    return;
  }

  string jname = jack_get_client_name(client);
  string previous_state = gx_user_dir + jname + "rc";
  interface->saveState(previous_state.c_str());

  if (setting_is_preset)
    gx_print_info("Main Setting", 
		  string("Saved current preset into main setting"));
  else
    gx_print_info("Main Setting", 
		  string("Saved main setting"));

  gtk_window_set_title(GTK_WINDOW(fWindow), jname.c_str());
  setting_is_preset = false;
}

//----menu function save new preset
void gx_save_newpreset_dialog (GtkMenuItem *menuitem, gpointer save_preset)
{
  // preset name to save
  string presname;

  // running dialog and get response
  gint response = gx_choice_dialog_with_text_entry (
       "Save new preset ... ",
       "\n   Please enter a valid preset name:   \n",
       "Save Preset", "Cancel", 
       GTK_RESPONSE_YES, GTK_RESPONSE_CANCEL, GTK_RESPONSE_YES,
       G_CALLBACK(gx_save_newpreset)
  );
						       
  // check response
  if (response == GTK_RESPONSE_CANCEL)
  {
    gx_print_warning("Saving New Preset Dialog", " Preset saving has been cancelled");
    return;
  }
}


//----preset renaming
void gx_rename_preset (GtkEntry* entry)
{
  // rename preset
  string newname; 
  gx_get_text_entry(entry, newname);

  if (newname.empty())
  {
    gx_print_error("Preset Renaming", "no preset name given");
    old_preset_name = "";
    return;
  }

  // replace spaces by -
  gx_cleanup_preset_name(newname);

  // get the UI to manipulate the preset file
  string presetfile = gx_user_dir + guitarix_preset;
  if (!interface->renamePreset(presetfile.c_str(), 
			       old_preset_name.c_str(),
			       newname.c_str()))
  {
    gx_print_error("Preset Renaming", 
		   string("Could not rename preset ") + old_preset_name);
    old_preset_name = "";
    return;
  }

  // if jconv file
  string jc_preset   = gx_user_dir + string("jconv_") + old_preset_name + ".conf ";
  string jc_file     = gx_user_dir + string("jconv_") + newname + ".conf ";
  string file_move   = jc_preset + jc_file;
  (void)gx_system("mv", file_move.c_str(), true);

  // refresh the menus
  for (int i = 0; i < GX_NUM_OF_PRESET_LISTS; i++)
  {
    GtkMenuItem* const item  = 
      gx_get_preset_item_from_name(i, old_preset_name);
    
    if (!item) continue;

    string label = gtk_menu_item_get_label(item);
    label.erase(label.find("  ") + 2);
    label.append(newname);
    gtk_menu_item_set_label(item, label.c_str());

    preset_list[i][item] = newname;

    // refresh main window name
    string jname = string(jack_get_client_name(client)) + " ";
    string title = jname + newname;
    gtk_window_set_title (GTK_WINDOW (fWindow), title.c_str());

    gx_current_preset = newname;
  }

  gx_print_info("Preset Renaming", string("preset ") + old_preset_name +
		string(" renamed into ") + newname);
  old_preset_name = "";
}

//----preset renaming dialog
void gx_rename_preset_dialog (GtkMenuItem *menuitem, gpointer arg)
{
  static string title;
  if (menuitem)
  { 
    title += "Renaming preset "; 
    title += preset_list[RENAME_PRESET_LIST][menuitem];
  }
  
  old_preset_name = preset_list[RENAME_PRESET_LIST][menuitem]; 

  // running dialog and get response
  gint response = gx_choice_dialog_with_text_entry (
       title.c_str(),
       " Please enter a valid preset name:                                    ",
       "Validate", "Cancel", 
       GTK_RESPONSE_YES, GTK_RESPONSE_CANCEL, GTK_RESPONSE_YES,
       G_CALLBACK(gx_rename_preset)
  );

  if (response == GTK_RESPONSE_CANCEL)
  {
    gx_print_warning("Rename Preset Dialog", " Preset renaming has been cancelled");
    old_preset_name = "";
    return;
  }
}

// ----------
void gx_rename_active_preset_dialog(GtkWidget* item, gpointer arg)
{
  if (!setting_is_preset || gx_current_preset.empty())
  {
    gx_print_warning("Renaming Active Preset", 
		     "This is the main setting, "
		     "load a preset first");
    return;
  }

  string presname = gx_current_preset;

  // get current preset menu item
  GtkMenuItem* const rnm_item = 
    gx_get_preset_item_from_name(RENAME_PRESET_LIST, presname);

  // call delete dialog
  if (rnm_item)
    gx_rename_preset_dialog (rnm_item, NULL);

  if (presname == gx_current_preset)
  {
    gx_print_warning("Renaming Active Preset", 
		     "The preset name is unchanged");
    return;
  }

  if (!gx_current_preset.empty() && setting_is_preset)
    gx_print_info("Renaming Active Preset", 
		  string("Renamed preset ") + presname +
		  string(" to ") + gx_current_preset);
}


//----preset deletion
void gx_delete_preset (GtkMenuItem* item, gpointer arg)
{
  
  // delete it via interface
  const string presname = 
    item ? preset_list[DELETE_PRESET_LIST][item] : gx_current_preset;

  const string presfile = gx_user_dir + guitarix_preset;
  const string tmpfile  = presfile + "_tmp";
  const string space    = " ";

  // let's use a tmp file that does not contain the preset 
  ostringstream cat_tmpfile("cat"); 
  cat_tmpfile << presfile << space 
	      << "| grep -v" << space << presname << space
	      << ">" << tmpfile;    
      
  cerr << cat_tmpfile.str() << endl;

  (void)gx_system("cat", cat_tmpfile.str());
  usleep(200);

  // rename tmp file
  rename(tmpfile.c_str(), presfile.c_str());

  // did we really delete it ?
  if (gx_system("grep", presname + space + presfile) == SYSTEM_OK)
  {  
    gx_print_error("Preset Deleting", 
		   string("Could not deleted preset ") + 
		   preset_list[DELETE_PRESET_LIST][item]);
    return;
  }

  // remove tmp file (not necessary)
  (void)gx_system("rm -f", tmpfile);

  // remove jconv file
  string jc_preset = gx_user_dir + string("jconv_") + presname + ".conf";
  (void)gx_system("rm -f", jc_preset);

  // update menu
  gx_del_preset_from_menus(presname);

  // recalling main setting
  gx_recall_main_setting(NULL, NULL);

  gx_print_warning("Preset Deleting", 
		   string("Deleted preset ") + 
		   presname + string(", recalled main setting"));
}

//----delete all presets
void  gx_delete_all_presets()
{
  // this function will simply delete the preset file,
  // clear the preset list and refresh the menus
  
  // delete preset file
  string filename = gx_user_dir + guitarix_preset;
  (void)gx_system("rm -f", filename.c_str(), true);

  // delete jconv files
  ostringstream cmd; cmd << "cd " << gx_user_dir << " && ls -1";
  (void)gx_system(cmd.str(), "jconv* | grep -v jconv_set | xargs rm -f"); 

  // clear list
  for (int i = 0; i < GX_NUM_OF_PRESET_LISTS; i++)
  {  
    map<GtkMenuItem*, string>::iterator it = preset_list[i].begin();
    
    while (it != preset_list[i].end())
    {
      GtkMenuItem* item = it->first;
      gtk_widget_destroy(GTK_WIDGET(item));
      it++;
    }

    preset_list[i].clear();
  }

  gx_print_info("All Presets Deleting", string("deleted ALL presets!"));
}

//----delete all presets dialog
void gx_delete_all_presets_dialog (GtkMenuItem *menuitem, gpointer arg)
{
  //--- if no presets, then just pop up some info
  if (preset_list[DELETE_PRESET_LIST].empty())
  {
    gx_print_warning("Delete All Presets Dialog",
		     string("There is no presets to delete"));
    return;
  }

  //--- run dialog and check response
  gint response = 
    gx_choice_dialog_without_entry (
        "Deleting ALL Presets! ",
	"   Are you sure you want to delete ALL your cool presets ? ",
	"Yes, DO IT NOW!", "Maybe Later ...", 
	GTK_RESPONSE_YES, GTK_RESPONSE_CANCEL, GTK_RESPONSE_YES
    );

  // we are cancelling
  if (response == GTK_RESPONSE_CANCEL)
  {
    gx_print_warning("Delete All Presets Dialog", 
		     "All Presets deletion has been cancelled");
    return;
  }

  // we want to delete all the buggers!
  gx_delete_all_presets ();  
    
}

//----preset deletion dialog
void gx_delete_preset_dialog (GtkMenuItem *menuitem, gpointer arg)
{
  string presname = 
    menuitem ? preset_list[DELETE_PRESET_LIST][menuitem] : gx_current_preset;

  string msg = "   Are you sure you want to delete preset ";
  msg += presname;
  msg += " ?? ";

  string title = "Deleting preset ";
  title += presname;

  //--- run dialog and check response
  gint response = 
    gx_choice_dialog_without_entry (
	title.c_str(), msg.c_str(),
	"Delete Preset", "Keep Preset", 
	GTK_RESPONSE_YES, GTK_RESPONSE_CANCEL, GTK_RESPONSE_YES
    );

  // we are cancelling
  if (response == GTK_RESPONSE_CANCEL)
  {
    gx_print_warning("Preset Deleting", 
		     string(" Deletion of preset ") + presname +
		     string(" has been cancelled"));
    return;
  }

  // we want to delete the bugger!
  gx_delete_preset (menuitem, arg);  
    
}

// ----------
void gx_delete_active_preset_dialog(GtkWidget* item, gpointer arg)
{

  if (!setting_is_preset || gx_current_preset.empty())
  {
    gx_print_warning("Deleting Active Preset", 
		     "No active preset, this is the main setting");
    return;
  }

  // tmp store 
  string presname = gx_current_preset;

  // call dialog
  gx_delete_preset_dialog (NULL, NULL);

  if (gx_current_preset.empty() && !setting_is_preset)
    gx_print_info("Deleting Active Preset", 
		  string("Deleted preset ") + presname +
		  string(", recalled main setting"));
}

//----menu funktion about
static void gx_show_about( GtkWidget *widget, gpointer data )
{
  static string about;
  if (about.empty())
  { 
    about += 
      "\n This Aplication is to a large extent provided"
      "\n with the marvelous faust compiler.Yann Orlary"
      "\n <http://faust.grame.fr/>"
      "\n A large part is based on the work of Julius Orion Smith"
      "\n<http://ccrma.stanford.edu/realsimple/faust/>"
      "\n and Albert Graef\n <http://www.musikwissenschaft.uni-mainz.de/~ag/ag.html> "
      "\n\n\n guitarix ";
    
    about += GX_VERSION;
    
    about += 
      " use jack_capture >= 0.9.30for record"
      "\n by Kjetil S. Matheussen "
      "\n http://old.notam02.no/arkiv/src/?M=D"
      "\n  it will allways record to ~/guitarix_sessionX.xxx "
      "\n for impulse response it use jconv "
      "\n byFons Adriaensen "
      "\n  http://www.kokkinizita.net/linuxaudio/index.html "
      "\n\n authors: Hermann Meyer <brummer-@web.de>"
      "\n authors: James Warden <warjamy@yahoo.com>"
      "\n home: http://guitarix.sourceforge.net/\n";
  }

  gx_message_popup(about.c_str());
}



//--------- class wrapper--------------------------
void flr( GtkWidget *widget, gpointer data )
{
    Resample myResample;
    myResample.fileread(widget, data);
}

void fls( GtkWidget *widget, gpointer data )
{
    JCONV_SETTINGS myJCONV_SETTINGS;
    myJCONV_SETTINGS.fileselected(widget, data);
}

void rjv( GtkWidget *widget, gpointer data )
{
    JCONV_SETTINGS myJCONV_SETTINGS;
    myJCONV_SETTINGS.runjconv(widget, data);
}

void wv( GtkWidget *widget, gpointer data )
{
    GtkWaveView myGtkWaveView;
    myGtkWaveView.gtk_waveview_set_value(widget, data);
}

//----- read the result from the latency change warning widget
int gx_dont_doit()
{
    doit =1;
    return 1;
}
int gx_doit()
{
    doit = 2;
    return 2;
}

//----- change the jack buffersize on the fly is still experimental, give a warning
void gx_wait_warn()
{
    warn_dialog = gtk_dialog_new();
    gtk_window_set_destroy_with_parent(GTK_WINDOW(warn_dialog), TRUE);
    GtkWidget * box = gtk_vbox_new (0, 4);
    GtkWidget * labelt = gtk_label_new ("\nWARNING\n");
    GtkWidget * labelt1 = gtk_label_new ("CHANGING THE JACK_BUFFER_SIZE ON THE FLY \nMAY CAUSE UNPREDICTABLE EFFECTS \nTO OTHER RUNNING JACK APPLICATIONS. \nDO YOU WANT TO PROCEED ?");
    GdkColor colorGreen;
    gdk_color_parse("#a6a9aa", &colorGreen);
    gtk_widget_modify_fg (labelt1, GTK_STATE_NORMAL, &colorGreen);
    GtkStyle *style1 = gtk_widget_get_style(labelt1);
    pango_font_description_set_size(style1->font_desc, 10*PANGO_SCALE);
    pango_font_description_set_weight(style1->font_desc, PANGO_WEIGHT_BOLD);
    gtk_widget_modify_font(labelt1, style1->font_desc);
    gdk_color_parse("#ffffff", &colorGreen);
    gtk_widget_modify_fg (labelt, GTK_STATE_NORMAL, &colorGreen);
    style1 = gtk_widget_get_style(labelt);
    pango_font_description_set_size(style1->font_desc, 14*PANGO_SCALE);
    pango_font_description_set_weight(style1->font_desc, PANGO_WEIGHT_BOLD);
    gtk_widget_modify_font(labelt, style1->font_desc);
    GtkWidget * box2 = gtk_hbox_new (0, 4);
    GtkWidget * button1  = gtk_dialog_add_button(GTK_DIALOG (warn_dialog),"Yes",1);
    GtkWidget * button2  = gtk_dialog_add_button(GTK_DIALOG (warn_dialog),"No",2);
    GtkWidget * box1 = gtk_hbox_new (0, 4);
    disable_warn = gtk_check_button_new ();
    GtkWidget * labelt2 = gtk_label_new ("Don't bother me again with such a question, I know what I am doing");

    gtk_container_add (GTK_CONTAINER(box), labelt);
    gtk_container_add (GTK_CONTAINER(box), labelt1);
    gtk_container_add (GTK_CONTAINER(box), box2);
    gtk_container_add (GTK_CONTAINER(box), box1);
    gtk_container_add (GTK_CONTAINER(box1), disable_warn);
    gtk_container_add (GTK_CONTAINER(box1), labelt2);
    gtk_container_add (GTK_CONTAINER(GTK_DIALOG(warn_dialog)->vbox), box);

    gtk_widget_modify_fg (labelt2, GTK_STATE_NORMAL, &colorGreen);
    GtkStyle *style = gtk_widget_get_style(labelt2);
    pango_font_description_set_size(style->font_desc, 8*PANGO_SCALE);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_LIGHT);
    gtk_widget_modify_font(labelt2, style->font_desc);

    g_signal_connect (button1, "clicked",  G_CALLBACK (gx_doit), warn_dialog);
    g_signal_connect (button2, "clicked",  G_CALLBACK (gx_dont_doit), warn_dialog);
    gtk_widget_show_all(box);

    gtk_dialog_run (GTK_DIALOG (warn_dialog));
    int woff = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(disable_warn));
    fwarn_swap = woff;
    gtk_widget_destroy (warn_dialog);
}

//----- pop up a dialog for starting jack
void gx_start_jack_dialog(int* argc, char*** argv)
{
  gtk_init(argc, argv);

  //--- run dialog and check response
  gint response = 
    gx_choice_dialog_without_entry (
        " Jack Starter ",
	"\n                        WARNING                        \n\n"
	"   The jack server is not currently running\n"
	"   You can choose to activate it or terminate guitarix   \n",
	"Start Jack", "Exit", 1, 2, 1
    );

  // we are cancelling
  if (response == 2)
  {
    gx_abort(NULL);
    return;
  }

  // start jack
  gx_start_jack(NULL);
}


//----start jack if possible
void gx_start_jack(void* arg)
{
  // first, let's try via qjackctl
  if (gx_system("which", "qjackctl", false) == SYSTEM_OK)
  {  
    if (gx_system("qjackctl", "--start", true, true) == SYSTEM_OK)
    {
      sleep(2);

      // let's check it is really running
      if (gx_system("pgrep", "jackd", true) == SYSTEM_OK)
      {
	jack_is_running = true;
	return;
      }
    }
  }

  // qjackctl not found or not started, let's try .jackdrc
  string jackdrc = "$HOME/.jackdrc";
  if (gx_system("ls", jackdrc.c_str(), true, false) == SYSTEM_OK)
  {
    // open it
    jackdrc = string(getenv("HOME")) + string("/") + ".jackdrc";
    string cmdline = "";

    ifstream f(jackdrc.c_str());
    if (f.good())
    {
      // should contain only one command line
      getline(f, cmdline);
      f.close();
    }

    // launch jackd
    if (!cmdline.empty())
      if (gx_system(cmdline.c_str(), "", true, true) == SYSTEM_OK)
      {
	sleep(2);

	// let's check it is really running
	if (gx_system("pgrep", "jackd", true) == SYSTEM_OK)
        {
	  jack_is_running = true;
	  return;
	}
      }

  }

  // TODO: what about jack-DBUS systems ? ... mmm ...  
}

//----abort guitarix
void gx_abort(void* arg)
{
  gx_print_warning("gx_abort", "Aborting guitarix, ciao!");
  exit(1);
}

//----menu function latency
void gx_set_jack_buffer_size(GtkCheckMenuItem *menuitem, gpointer arg)
{
    // are we a proper jack client ?
    if (!client)
    {
      gx_print_error(
        "Jack Buffer Size setting",
        string("we are not a jack client, server may be down")
      );
	
      return;
    }

    // static variable that keeps track of active item
    static GtkCheckMenuItem* refreshItem = NULL;

    // ----- if check button triggered menually
    if (menuitem)
    {
      // let's avoid triggering the jack server on "inactive"
      if (gtk_check_menu_item_get_active(menuitem) == false)
        return;

      // requested latency
      jack_nframes_t buf_size = (jack_nframes_t)GPOINTER_TO_INT(arg);
      
      if (buf_size == jack_get_buffer_size(client))
      {
	// let's save the item for eventual display refreshing
	refreshItem = menuitem;

	// since the actual buffer size is the same, no need further action
	return;
      }

      // first time useage warning
      if (fwarn_swap == 0.0)
      {
        gx_wait_warn();
      }
      else doit =2;

      if (doit ==2)
      {
        int jcio = 0;
        if (runjc == 1)
        {
            jcio = 1;
            checkbutton7 = 0;
            checkbox7 = 0.0;
            rjv( NULL, NULL );
        }

        // let's resize the buffer
        if ( jack_set_buffer_size (client, buf_size) != 0)
	  gx_print_warning("Setting Jack Buffer Size", string("Could not change latency"));

	else // save the item pointer for eventual display refreshing
	  refreshItem = menuitem;

        if (jcio == 1)
        {
            jcio = 0;
            checkbutton7 = 1;
            checkbox7 = 1.0;
            rjv( NULL, NULL );
        }
        doit = 0;
      }
    }

    // we are called only to refresh the menu display
    if (refreshItem)
      gtk_check_menu_item_set_active (refreshItem, TRUE);

    if (menuitem)
      gx_print_info(
	"Jack Buffer Size", 
	string("latency is ") + gx_i2a(jack_get_buffer_size(client))
      );
}



//--------------------------- jack_capture settings ----------------------------------------
static void gx_show_j_c_gui( GtkWidget *widget, gpointer data )
{
    (void)system ("jack_capture_gui2 -o yes -f ~/guitarix_session -n guitarix -p /.guitarix/ja_ca_ssetrc &");
}

//----- terminate child processes
static gint gx_terminate_child_procs()
{
    if (child_pid[METERBG_IDX] != NO_PID)
    {
      (void)kill(child_pid[METERBG_IDX], SIGTERM);
      (void)gx_system("rm -f", mbg_pidfile.c_str(), true);
      child_pid[METERBG_IDX] = NO_PID;
    }

    if (child_pid[JACKCAP_IDX] != NO_PID)
    {
      (void)kill(child_pid[JACKCAP_IDX], SIGINT);
      (void)gx_pclose(jcap_stream, JACKCAP_IDX);
    }

    if (system(" pidof jconv > /dev/null") == 0)
    {
      (void)system("command kill -2 `pidof  jconv ` 2> /dev/null") ;
      (void)gx_pclose(control_stream1, JCONV_IDX);
    }
    return 0;
}

//----- clean up when shut down
static void gx_destroy_event()
{
    (void)gx_terminate_child_procs();

    shownote = -1;
    stopit = "stop";
    showwave = 0;
    playmidi = 0;

    GtkWaveView myGtkWaveView;
    myGtkWaveView.gtk_waveview_destroy (GTK_WIDGET(livewa), NULL );

    GtkRegler myGtkRegler;
    myGtkRegler.gtk_regler_destroy ( );

    if (G_IS_OBJECT(ib))
        g_object_unref( ib);
    if (G_IS_OBJECT(ibm))
        g_object_unref( ibm);
    if (G_IS_OBJECT(ibr))
        g_object_unref(ibr);

    gtk_main_quit ();
}

// reset the extended sliders to default settings
static void gx_reset_units( GtkWidget *widget, gpointer data )
{
    const char* witchres = gtk_window_get_title(GTK_WINDOW(data));

    string filename = gx_user_dir + guitarix_reset;

    if (strcmp(witchres, "distortion") == 0) 
      interface->recalladState(filename.c_str(),  4,  16, 0);

    else if (strcmp(witchres, "freeverb") == 0) 
      interface->recalladState(filename.c_str(),  20,  24, 1);

    else if (strcmp(witchres, "ImpulseResponse") == 0) 
      interface->recalladState(filename.c_str(),  28,  32, 2);

    else if (strcmp(witchres, "crybaby") == 0) 
      interface->recalladState(filename.c_str(),  16,  20, 3);

    else if (strcmp(witchres, "midi out") == 0) 
      interface->recalladState(filename.c_str(),  44,  50, 4);

    else if (strcmp(witchres, "compressor") == 0) 
      interface->recalladState(filename.c_str(),  72,  78, 5);
}

//----- show extendend settings slider
void gx_show_extendet_settings(GtkWidget *widget, gpointer data)
{
    if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(widget)) == TRUE)
    {
        gtk_widget_show(GTK_WIDGET(data));
        gint root_x, root_y;
        gtk_window_get_position (GTK_WINDOW(data), &root_x, &root_y);
        root_y -= 120;
        gtk_window_move(GTK_WINDOW(data), root_x, root_y);
    }
    else gtk_widget_hide(GTK_WIDGET(data));
}

//----- hide the extendend settings slider
static void gx_hide_extendet_settings( GtkWidget *widget, gpointer data )
{
    if (showit == 0)
    {
        gtk_widget_hide(GTK_WIDGET(fWindow));
        showit = 1;
    }
    else
    {
        gtk_widget_show(GTK_WIDGET(fWindow));
        showit = 0;
    }
}

//----- systray menu
static void gx_sytray_menu( GtkWidget *widget, gpointer data )
{
    guint32 tim = gtk_get_current_event_time ();
    gtk_menu_popup (GTK_MENU(menuh),NULL,NULL,NULL,(gpointer) menuh,2,tim);
}

//---- popen revisited for guitarix
static FILE* gx_popen(const char *cmdstring,
		      const char *type,
		      const int proc_idx)
{
  int   i, pfd[2];
  pid_t	pid;
  FILE	*fp;

  /* only allow "r" or "w" */
  if ((type[0] != 'r' && type[0] != 'w') || type[1] != 0) {
    errno = EINVAL;		/* required by POSIX.2 */
    return(NULL);
  }

  if (pipe(pfd) < 0)
    return(NULL);	/* errno set by pipe() */

  if ((pid = fork()) < 0)
    return(NULL);	/* errno set by fork() */

  else if (pid == 0)
  {
    if (*type == 'r')
    {
      close(pfd[0]);
      if (pfd[1] != STDOUT_FILENO)
      {
	dup2(pfd[1], STDOUT_FILENO);
	close(pfd[1]);
      }
    }
    else
    {
      close(pfd[1]);

      if (pfd[0] != STDIN_FILENO)
      {
	dup2(pfd[0], STDIN_FILENO);
	close(pfd[0]);
      }
    }

    /* close all descriptors in child_pid[] */
    for (i = 0; i < NUM_OF_CHILD_PROC; i++)
      if (child_pid[i] > 0)
	close(i);

    execl("/bin/sh", "sh", "-c", cmdstring, (char *) 0);
    _exit(127);
  }

  /* parent */
  if (*type == 'r')
  {
    close(pfd[1]);

    if ((fp = fdopen(pfd[0], type)) == NULL)
      return(NULL);

  }
  else
  {
    close(pfd[0]);

    if ((fp = fdopen(pfd[1], type)) == NULL)
      return(NULL);
  }

  child_pid[proc_idx] = pid; /* remember child pid for this fd */
  return(fp);
}

//---- pclose revisited for guitarix
static int gx_pclose(FILE *fp, const int proc_idx)
{
  int stat;
  pid_t	pid;

  if ((pid = child_pid[proc_idx]) == 0)
    return(-1);	/* fp wasn't opened by gx_popen() */

  // reset internal process pid
  child_pid[proc_idx] = NO_PID;

  // check control stream
  if (!fp)
    return(-1);

  // close it
  if (fclose(fp) == EOF)
    return(-1);

  while (waitpid(pid, &stat, 0) < 0)
    if (errno != EINTR)
      return(-1); /* error other than EINTR from waitpid() */

  return(stat);	/* return child's termination status */
}

//---- guitarix system function
static int gx_system(const char* name1,
	      const char* name2,
	      const bool  devnull,
	      const bool  escape)
{
  string str(name1);
  str.append(" ");
  str.append(name2);

  if (devnull)
    str.append(" 1>/dev/null 2>&1");

  if (escape)
    str.append("&");

  //  cerr << " ********* \n system command = " << str.c_str() << endl;

  return system(str.c_str());
}

// polymorph1
static int gx_system(const char*   name1,
		     const string& name2,
		     const bool  devnull,
		     const bool  escape)
{
  return gx_system(name1, name2.c_str(), devnull, escape);
}

// polymorph2
// static int gx_system(const string& name1,
// 		     const string& name2,
// 		     const bool  devnull,
// 		     const bool  escape)
// {
//   return gx_system(name1.c_str(), name2.c_str(), devnull, escape);
// }

// polymorph3
static int gx_system(const string& name1,
		     const char*   name2,
		     const bool  devnull,
		     const bool  escape)
{
  return gx_system(name1.c_str(), name2, devnull, escape);
}

// -------------------------------------------
bool gx_lookup_pid(const pid_t child_pid) 
{
  // --- this function looks up the given PID from the lost of processes
  // it returns true if a match is found.
  string pstr;
  gx_IntToString(child_pid, pstr);
  
  pstr += " -o pid";
  
  return (gx_system("ps -p", pstr.c_str(), true) == SYSTEM_OK) ? true : false;
}

//---- find latest process ID by reading stdout from pgrep -n 
pid_t gx_find_child_pid(const char* procname) 
{
  // --- this function retrieves the latest PID of a named process.
  // it is to be called just after guitarix spawns a child process

  // file desc
  int fd[2];
  pid_t pid = NO_PID;

  // piping
  if (pipe(fd) < 0)
    return NO_PID;

  // forking
  if ((pid = fork()) < 0)
    return NO_PID;

  else if (pid == 0) // child
  {
    close(fd[0]);

    if (fd[1] != STDOUT_FILENO)
    {  
      dup2(fd[1], STDOUT_FILENO);
      close(fd[1]);
    }

    // executing 'pgrep -n <proc name>'
    if (execl("/usr/bin/pgrep", "pgrep", "-n", procname, NULL) < 0)
      return NO_PID;
  }
  else // parent
  {
    close(fd[1]);

    int rv;
    char line[16];
    
    // read stdout
    if ( (rv = read(fd[0], line, 16)) > 0)
    {
      string str = line;
      str.resize(rv-1); // remove extra character crap
      pid = atoi(str.c_str());
    }
  }

  return pid;
}

//---- popup warning
static gint gx_message_popup(const char* msg)
{
  // check msg validity
  if (!msg)
  {
    gx_print_warning("Message Popup", 
		     string("warning message does not exist"));
    return -1;
  }

  // build popup window
  GtkWidget *about;
  GtkWidget *label;
  GtkWidget *ok_button;

  about = gtk_dialog_new();
  ok_button  = gtk_button_new_from_stock(GTK_STOCK_OK);

  label = gtk_label_new (msg);

  GtkStyle *style = gtk_widget_get_style(label);

  pango_font_description_set_size(style->font_desc, 10*PANGO_SCALE);
  pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);

  gtk_widget_modify_font(label, style->font_desc);

  gtk_label_set_selectable(GTK_LABEL(label), TRUE);

  gtk_container_add (GTK_CONTAINER (GTK_DIALOG(about)->vbox), label);

  GTK_BOX(GTK_DIALOG(about)->action_area)->spacing = 3;
  gtk_container_add (GTK_CONTAINER (GTK_DIALOG(about)->action_area), ok_button);

  g_signal_connect_swapped (ok_button, "clicked",
			    G_CALLBACK (gtk_widget_destroy), about);

  gtk_widget_show (ok_button);
  gtk_widget_show (label);
  return gtk_dialog_run (GTK_DIALOG(about));
}

//---- wav file construction for jack_capture
static bool gx_capture_command(const int idx, string& capcmd)
{
  bool ret_status = false;

  // jack_capture setup file
  string gfilename = gx_user_dir + jcapsetup_file;

  // open jack_capture setup file
  ifstream f(gfilename.c_str());

  if (f.good())
  {
    // jack_capture command
    // Note: this version of the code does not add a wav file by
    // default to ja_ca_ssetrc, so we try to avoid the wav filename if one
    // by putting the / delimiter in getline
    // it is backward compatible with older ja_ca_ssetrc files

    getline(f, capcmd, '/');
    f.close();

    // remove trailing \n if any
    int pos = capcmd.size()-1;

    if (capcmd.c_str()[pos] == '\n')
      capcmd.resize(pos);

    ret_status = true;
  }

  // are we good ?
  if (!ret_status)
    return false;

  // we're OK
  string idx_str;
  gx_IntToString(idx, idx_str);

  capcmd += " ";
  capcmd += getenv("HOME");
  capcmd += "/";
  capcmd += jcapfile_wavbase;
  capcmd += idx_str;
  capcmd += ".wav";

  return true;
}

// ----- skin change
static void  gx_change_skin(GtkCheckMenuItem *menuitem, gpointer arg)
{
  // no action needed on false
  if (gtk_check_menu_item_get_active(menuitem) == FALSE)
    return;

  // update the skin to the one picked by user
  const int idx = (int)GPOINTER_TO_INT(arg);
  (void)gx_update_skin(idx, "gx_change_skin");
}

// ----- cycling through skin
static void  gx_cycle_through_skin(GtkWidget *widget, gpointer arg)
{
  
  gint idx = gx_current_skin + 1;
  idx %= skin_list.size();

  // did it work ? if yes, update current skin
  if (gx_update_skin(idx, "gx_cycle_through_skin"))
    gx_current_skin = idx;
}

// ---- skin changer, used internally frm callbacks
static bool gx_update_skin(const gint idx, const char* calling_func)
{ 
  // check skin validity 
  if (idx < 0 || idx >= (gint)skin_list.size())
  {
    gx_print_warning(calling_func, "skin index out of range, keeping actual skin");
    return false;
  }
      

  string rcfile = GX_STYLE_DIR + string("/") + "guitarix_";
  rcfile += skin_list[idx];
  rcfile += ".rc";

  gtk_rc_parse(rcfile.c_str());
  gtk_rc_reset_styles(gtk_settings_get_default());

  gx_current_skin = idx;

  GtkWaveView myGtkWaveView;
  myGtkWaveView.gtk_waveview_refresh (GTK_WIDGET(livewa), NULL );

  // refresh latency check menu
  gx_set_jack_buffer_size(NULL, NULL);

  return true;
}

//---- retrive skin array index from skin name
static void gx_actualize_skin_index(const string& skin_name)
{
  for (guint s = 0; s < skin_list.size(); s++)
    if (skin_name == skin_list[s])
    {
      gx_current_skin = s;
      return;
    }
}  

//---- parsing preset file to build up a string vector of preset names
void gx_build_preset_list(vector<string>& plist)
{
  // preset filename
  string filename = gx_user_dir + guitarix_preset;

  // initialize list
  plist.clear();

  // parse it if any
  ifstream f(filename.c_str());
  if (f.good())
  {
    string buffer;
    while (!f.eof())
    {
      // get line
      getline(f, buffer);
      if (buffer.empty()) continue;

      // parse buffer
      istringstream values(buffer);

      // grab first item in line
      string pname; values >> pname; 
      plist.push_back(pname);
    }
    f.close();
  }

  // ---- how many did we get ?
  gx_print_warning("Preset List Building", 
		   gx_i2a(plist.size()) + string(" presets found"));
}

//---- choice dialog without text entry
gint gx_choice_dialog_without_entry (
   const char* window_title,
   const char* msg,
   const char* label1,
   const char* label2,
   const gint resp1,
   const gint resp2,
   const gint default_response
)
{
  GtkWidget* dialog   = gtk_dialog_new();
  GtkWidget* button1  = gtk_dialog_add_button(GTK_DIALOG (dialog), label1, resp1);
  GtkWidget* button2  = gtk_dialog_add_button(GTK_DIALOG (dialog), label2, resp2);

  GtkWidget* text_label = gtk_label_new (msg);
  gtk_container_add (GTK_CONTAINER (GTK_DIALOG(dialog)->vbox), text_label);

  GdkColor colorGreen;
  gdk_color_parse("#a6a9aa", &colorGreen);
  gtk_widget_modify_fg (text_label, GTK_STATE_NORMAL, &colorGreen);

  GdkColor colorBlack;
  gdk_color_parse("#000000", &colorBlack);
  gtk_widget_modify_bg (dialog, GTK_STATE_NORMAL, &colorBlack);

  GtkStyle* text_style = gtk_widget_get_style(text_label);
  pango_font_description_set_size(text_style->font_desc, 10*PANGO_SCALE);
  pango_font_description_set_weight(text_style->font_desc, PANGO_WEIGHT_BOLD);

  gtk_widget_modify_font(text_label, text_style->font_desc);

  gdk_color_parse("#555555", &colorBlack);
  gtk_widget_modify_bg (button1, GTK_STATE_NORMAL, &colorBlack);

  gdk_color_parse("#555555", &colorBlack);
  gtk_widget_modify_bg (button2, GTK_STATE_NORMAL, &colorBlack);

  g_signal_connect_swapped(button1, "clicked",  G_CALLBACK (gtk_widget_destroy), dialog);
  g_signal_connect_swapped(button2, "clicked",  G_CALLBACK (gtk_widget_destroy), dialog);

  // set default
  gtk_dialog_set_has_separator(GTK_DIALOG(dialog), TRUE); 
  gtk_dialog_set_default_response(GTK_DIALOG(dialog), default_response);
  gtk_window_set_title(GTK_WINDOW(dialog), window_title);

  gtk_widget_show(text_label);

  //--- run dialog and check response
  gint response = gtk_dialog_run (GTK_DIALOG (dialog));
  return response;
}


//---- get text entry from dialog
void gx_get_text_entry(GtkEntry* entry, string& output)
{
  if (gtk_entry_get_text(entry)[0])
    output = gtk_entry_get_text(entry);
}

//---- choice dialog with text entry
gint gx_choice_dialog_with_text_entry (
   const char* window_title,
   const char* msg,
   const char* label1,
   const char* label2,
   const gint resp1,
   const gint resp2,
   const gint default_response,
   GCallback func
)
{
  GtkWidget *dialog, *button1, *button2;
  dialog  = gtk_dialog_new();
  button1 = gtk_dialog_add_button(GTK_DIALOG (dialog), label1, resp1);
  button2 = gtk_dialog_add_button(GTK_DIALOG (dialog), label2, resp2);
  
  GtkWidget* text_label = gtk_label_new (msg);
  gtk_container_add (GTK_CONTAINER (GTK_DIALOG(dialog)->vbox), text_label);


  GtkWidget* gtk_entry = gtk_entry_new_with_max_length(32);
  gtk_entry_set_text(GTK_ENTRY(gtk_entry), "");
  gtk_container_add (GTK_CONTAINER (GTK_DIALOG(dialog)->vbox), gtk_entry);
  
  g_signal_connect_swapped (button1, "clicked",  G_CALLBACK (func), gtk_entry);
  g_signal_connect_swapped (button2, "clicked",  G_CALLBACK (gtk_widget_destroy), dialog);
  
  gtk_dialog_set_has_separator(GTK_DIALOG(dialog), TRUE); 
  gtk_dialog_set_default_response(GTK_DIALOG(dialog), default_response);
  gtk_entry_set_activates_default(GTK_ENTRY(gtk_entry), TRUE);
  GTK_BOX(GTK_DIALOG(dialog)->action_area)->spacing = 4;

  // some display style
  GdkColor colorGreen;
  gdk_color_parse("#a6a9aa", &colorGreen);
  gtk_widget_modify_fg (text_label, GTK_STATE_NORMAL, &colorGreen);

  GdkColor colorBlack;
  gdk_color_parse("#000000", &colorBlack);
  gtk_widget_modify_bg (dialog, GTK_STATE_NORMAL, &colorBlack);

  GtkStyle* text_style = gtk_widget_get_style(text_label);
  pango_font_description_set_size(text_style->font_desc, 10*PANGO_SCALE);
  pango_font_description_set_weight(text_style->font_desc, PANGO_WEIGHT_BOLD);

  gtk_widget_modify_font(text_label, text_style->font_desc);

  gdk_color_parse("#555555", &colorBlack);
  gtk_widget_modify_bg (button1, GTK_STATE_NORMAL, &colorBlack);

  gdk_color_parse("#555555", &colorBlack);
  gtk_widget_modify_bg (button2, GTK_STATE_NORMAL, &colorBlack);

  // display extra stuff
  gtk_widget_show (text_label);
  gtk_widget_show (gtk_entry);
  gtk_window_set_title(GTK_WINDOW(dialog), window_title);

  // run the dialog and wait for response
  gint response = gtk_dialog_run (GTK_DIALOG(dialog));

  if (dialog) gtk_widget_destroy(dialog);

  return response;
}

//------- count the number of available skins
unsigned int gx_fetch_available_skins()
{
  string tmpfile = gx_user_dir + ".n_skins";

  // make sure user dir exists
  gx_system("mkdir -p", gx_user_dir);

  // create a tmpfile
  gx_system("rm -f", tmpfile.c_str());
  gx_system("touch", tmpfile.c_str());

  string filelist  = 
    gx_style_dir + string("guitarix*.rc") + " > " + tmpfile;

  gx_system("ls -1", filelist.c_str(), false);
  
  // read out number of files
  ifstream f(tmpfile.c_str());

  string rcfile;
  if (f.good())
  {
    while (!f.eof())
    {
      // retrieve filename
      getline(f, rcfile);
      
      // trim it
      if (!rcfile.empty())
      {
	rcfile.erase(rcfile.find(".rc"));
	rcfile.erase(0, rcfile.find("_")+1);
	skin_list.push_back(rcfile);
      }
    }      

    f.close();
  }

  // remove tmp file
  gx_system("rm -f", tmpfile.c_str());

  return skin_list.size();
}

// ----------- add new preset to menus
void gx_add_preset_to_menus(const string& presname)
{

  for (int i = 0; i < GX_NUM_OF_PRESET_LISTS; i++)
    gx_add_single_preset_menu_item(presname, i, preset_action_func[i]);
}

//---- add a single preset to a given preset menu
void gx_add_single_preset_menu_item(const string& presname,
				    const gint lindex,
				    GCallback func)
{
  // menu
  GtkWidget* menu = presmenu[lindex];

  // index for keyboard shortcut (can take any list)
  int pos = preset_list[lindex].size() + 1;

  // add small mnemonic
  string name("_");
  name += gx_i2a(pos) + "  ";
  name += presname;

  // GDK numbers
  guint accel_key = GDK_1  + pos - 1;

  // create item
  GtkWidget* menuitem = gtk_menu_item_new_with_mnemonic (name.c_str());
  g_signal_connect (GTK_OBJECT (menuitem), "activate", 
		    G_CALLBACK (func), 
		    NULL);

  gtk_menu_shell_append(GTK_MENU_SHELL(menu), menuitem);

  string acc_path = gtk_menu_get_accel_path(GTK_MENU(menu));
  acc_path += "/";
  acc_path += gx_i2a(accel_key);

  // add accelerator in accel path if not added
  if (!gtk_accel_map_lookup_entry(acc_path.c_str(), NULL))
      gtk_accel_map_add_entry(acc_path.c_str(), accel_key, list_mod[lindex]);

  gtk_widget_set_accel_path(menuitem, acc_path.c_str(), interface->fAccelGroup);
  gtk_widget_show (menuitem);
  preset_list[lindex].insert(pair<GtkMenuItem*,string>(GTK_MENU_ITEM(menuitem), presname));
}

// ----------- remove old preset from menus
void gx_del_preset_from_menus(const string& presname)
{
  for (int i = 0; i < GX_NUM_OF_PRESET_LISTS; i++) 
    gx_del_single_preset_menu_item(presname, i);

  gx_refresh_preset_menus();
}

void  gx_del_single_preset_menu_item(const string& presname, const gint lindex)
{
  GtkMenuItem* const item = gx_get_preset_item_from_name(lindex, presname);
  if (item)
  {
    preset_list[lindex].erase(item);
    gtk_widget_destroy(GTK_WIDGET(item));
  }
}

// ----------- retrieve menu item given a name
GtkMenuItem* const gx_get_preset_item_from_name(int lindex, const string& name)
{
  map<GtkMenuItem*, string>::iterator it;
  for (it  = preset_list[lindex].begin(); it != preset_list[lindex].end(); it++)
    if (name == it->second)
      return it->first;

  return NULL;
}

// ----------- update preset numbering in menus
void gx_refresh_preset_menus()
{

  string acc_path;

  for (int i = 0; i < GX_NUM_OF_PRESET_LISTS; i++)
  {
    guint n = 1;

    map<GtkMenuItem*, string>::iterator it;
    for (it = preset_list[i].begin(); it != preset_list[i].end(); it++)
    {
      GtkMenuItem* const item = it->first;
      string label = gtk_menu_item_get_label(item);
      label.replace(1, 1, gx_i2a(n));
      gtk_menu_item_set_label(item, label.c_str());

      // refresh acc path for this item
      guint accel_key = GDK_1 + n - 1;
      acc_path = gtk_menu_get_accel_path(GTK_MENU(presmenu[i]));
      acc_path += "/";
      acc_path += gx_i2a(accel_key);
      gtk_widget_set_accel_path(GTK_WIDGET(item), acc_path.c_str(), interface->fAccelGroup);

      n++;
    }
    cerr << endl;
  }
}
    
// ---------- switch to next preset in queue
void gx_next_preset(GtkWidget* item, gpointer arg)
{
  // check that we do have presets
  if (preset_list[LOAD_PRESET_LIST].size() == 0)
  {
    gx_print_warning("Preset Switching", 
		     "Preset list is empty, make some :)");
    return;
  }

  // start from this element
  map<GtkMenuItem*, string>::iterator it;

  // initialize iterator
  if (!setting_is_preset) 
    it = preset_list[LOAD_PRESET_LIST].begin();
  else
  {
    GtkMenuItem* const item = 
      gx_get_preset_item_from_name(LOAD_PRESET_LIST, gx_current_preset);

    it = preset_list[LOAD_PRESET_LIST].find(item);

    // increment iterator and load preset
    it++;
  }


  // check if we are on edge
  if (it == preset_list[LOAD_PRESET_LIST].end())
    it = preset_list[LOAD_PRESET_LIST].begin();

  // load the preset
  gx_load_preset(it->first, NULL);
}

// ---------- switch to next preset in queue
void gx_previous_preset(GtkWidget* item, gpointer arg)
{
  // check that we do have presets
  if (preset_list[LOAD_PRESET_LIST].size() == 0)
  {
    gx_print_warning("Preset Switching", 
		     "Preset list is empty, make some :)");
    return;
  }

  // start from this element
  map<GtkMenuItem*, string>::iterator it;

  // initialize iterator
  if (!setting_is_preset) 
    it = preset_list[LOAD_PRESET_LIST].end();
  else
  {
    GtkMenuItem* const item = 
      gx_get_preset_item_from_name(LOAD_PRESET_LIST, gx_current_preset);

    it = preset_list[LOAD_PRESET_LIST].find(item);

  }

  // check if we are on edge
  if (it == preset_list[LOAD_PRESET_LIST].begin())
    it = preset_list[LOAD_PRESET_LIST].end();

  // decrement iterator and load preset
  it--;


  // load the preset
  gx_load_preset(it->first, NULL);
}
