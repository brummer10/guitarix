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


// global static fields
GtkWidget* fWindow, *menul, *menus, *pb, *midibox, *fbutton, *label1, *menuh;
GdkPixbuf*   ib, *ibm, *ibr;
GtkStatusIcon*  status_icon;
GtkWidget* livewa, *warn_dialog,*disable_warn ;
GtkWidget* gx_engine_on_image;
GtkWidget* gx_engine_off_image;

static float      checkbutton7;

float jackframe; // jack sample freq
float cpu_load;  // jack cpu_load
float checkbox7    = 1.0;
float checky       = 1.0;
float *get_frame   = NULL;
float *checkfreq   = NULL;
float *oversample  = NULL;

const char* stopit = "go";
const char* rcpath = " " ;
string jconvwav ;
string mbg_pidfile;

// guitarix setting, location and related stuff
const char* guitarix_dir     = ".guitarix";
const char* guitarix_reset   = "resettings";
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
const string gx_user_dir = 
  string(getenv ("HOME")) + string("/") + string(guitarix_dir) + "/";

int offcut;
int lenghtcut;
int cm = 0;
int shownote = 2;
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
UI*                 interface;

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
#define GX_SKIN_START (0)
#define GX_NUM_OF_SKINS (4)

const char* skins[] = {
  "black",
  "pix",
  "sunburst",
  "default"
};

gint gx_current_skin = GX_SKIN_START;

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
static void  gx_message_popup(const char*);
static bool  gx_capture_command(const int, string&);
static int   gx_system(const char*,
		       const char*,
		       const bool devnull = true,
		       const bool escape  = false);
static void  gx_change_skin(GtkCheckMenuItem *menuitem, gpointer arg);
static void  gx_cycle_through_skin(GtkWidget *widget, gpointer arg);
static bool  gx_update_skin(const gint idx, const char* calling_func);
static void  gx_actualize_skin_index(const string& skin_name);
static void  gx_abort(void* arg);
static void  gx_start_jack(void* arg);

// ---- terminal warning message
void gx_print_warning(const char* func, const string& msg)
{
  cerr << "<*** " << func << ": WARNING - "
       << "\033[1;32m" << msg.c_str() << "\033[0m"
       << " ***>" << endl;
}

// ---- terminal error message
void gx_print_error(const char* func, const string& msg)
{
  cerr << "<*** " << func << ": ERROR - "
       << "\033[1;31m" << msg.c_str() << "\033[0m"
       << " ***>" << endl;
}

// ---- check version and if directory exists and create it if it not exist
bool gx_version_check(const char* Path)
{
    struct stat my_stat;

//----- this check dont need to be against real version, we only need to know
//----- if the presethandling is working with the courent version, we only count this
//----- string when we must remove the old preset files.
    string rcfilename = 
      gx_user_dir + string("version-") + string("0.03.3") ;

    if  (stat(Path, &my_stat) == 0) // directory exists
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
       //same here, we only change this file, when the presethandling is brocken,
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
	 "gx_pixmap_check",
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

//----use jack_capture for record the session
bool gx_capture(const char* capturas)
{
  // open a write stream for controling the stop function
  jcap_stream = gx_popen(capturas, "w", JACKCAP_IDX);
  return (jcap_stream != NULL);
}

bool		GTKUI::fInitialized = false;
list<UI*>	UI::fGuiList;

//----menu function play stop
void gx_engine_switch (GtkWidget* menuitem, gpointer arg)
{
  // switch engine on or off
  checky = (checky == 1.0) ? 0.0 : 1.0;
  
  // refresh status display
  if (checky == 1.0)
  {
    gtk_widget_show(gx_engine_on_image);
    gtk_widget_hide(gx_engine_off_image);
  }
  else
  {
    gtk_widget_show(gx_engine_off_image);
    gtk_widget_hide(gx_engine_on_image);
  }
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
      return;
    }

    // running, so let's store PID in lock file
    ofstream fo(mbg_pidfile.c_str());
    if (fo.good())
    {
      child_pid[METERBG_IDX] = gx_find_child_pid(app_name);
      fo << child_pid[METERBG_IDX];
      fo.close();
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

    // ---- stop recording
    if (tggl_state == FALSE) // nope
    {
      // get jack_cap pid spawned by guitarix
      const pid_t cap_pid = child_pid[JACKCAP_IDX];

      if (cap_pid != NO_PID) // running
      {
	if (kill(cap_pid, SIGINT) == -1)
	  gx_message_popup(" Sorry, could not stop (Ctrl-C) jack_capture");

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

    // increment if capturing more than once
    static int capas = 0;

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
      capas++;
      return;
    }

    // nope :(
    gtk_toggle_button_set_active(cap_button, FALSE);
    gx_message_popup(warning.c_str());
}

//----menu funktion load
void gx_load_preset (GtkMenuItem *menuitem, gpointer load_preset)
{
    JCONV_SETTINGS myJCONV_SETTINGS;
    checkbutton7 = 0;

    interface->updateAllGuis();

    GtkWidget* title = gtk_bin_get_child(GTK_BIN(menuitem));
    const gchar* text = gtk_label_get_text (GTK_LABEL(title));

    string rcfilenamere = gx_user_dir + "guitarixprerc";
    string tmpfilename  = gx_user_dir + "guitarixtmprc";
    string jc_preset    = gx_user_dir + string("jconv_") + string(text) + ".conf ";
    string jc_file      = gx_user_dir + string("jconv_set.conf");
    string file_copy    = jc_preset + jc_file;
    (void)gx_system("cp -f", file_copy.c_str());

    int lin;
    int zeile=0;
    int l=0;

    ifstream f(rcfilenamere.c_str());
    if (f.good())
    {
        string buffer;
        while (!f.eof())
        {
            getline(f, buffer);
            std::string b(" ");
            std::string::size_type in = buffer.find(b);
            if (int(in) != -1) buffer.erase(in);
            l++;
        }
        zeile = l-1;
    }
    f.close();
    lin = zeile;
    myJCONV_SETTINGS.get_jconfset ();
    interface->recallpreStatebyname(rcfilenamere.c_str(), tmpfilename.c_str(), text);
    string ttle = string("guitarix ") + text;
    gtk_window_set_title (GTK_WINDOW (fWindow), (gchar*)ttle.c_str());
}

//---- funktion save
void gx_save_preset (const gchar* presname)
{
    string rcfilenamere = gx_user_dir + "guitarixprerc";
    string tmpfilename  = gx_user_dir + "guitarixtmprc";

    interface->savepreStatebyname(rcfilenamere.c_str(), tmpfilename.c_str(), presname);
    if (cm == 0)
    {
        GtkWidget* menuitem = gtk_menu_item_new_with_label (presname);
        g_signal_connect (GTK_OBJECT (menuitem), "activate", G_CALLBACK (gx_load_preset), NULL);
        gtk_menu_append(GTK_MENU(menul), menuitem);
        gtk_widget_show (menuitem);
    }
    string ttle = string("guitarix ") + presname;
    gtk_window_set_title (GTK_WINDOW (fWindow), (gchar*)ttle.c_str());

    string jc_file      = gx_user_dir + string("jconv_set.conf ");
    string jc_preset    = gx_user_dir + string("jconv_") + string(presname) + ".conf";
    string file_copy    = jc_file + jc_preset; 
    (void)gx_system("cp", file_copy.c_str());
}

//----menu funktion save
void gx_save_presetn2 (GtkMenuItem *menuitem, gpointer save_preset)
{
    GtkWidget* title = gtk_bin_get_child(GTK_BIN(menuitem));
    const gchar* text = gtk_label_get_text (GTK_LABEL(title));
    gx_save_preset(text);
}

// read name for presset
void gx_get_text(GtkWidget *box)
{
    const gchar* presname = gtk_entry_get_text (GTK_ENTRY(box));
    gx_save_preset(presname);
    if (cm == 0)
    {
        GtkWidget*  menuitem = gtk_menu_item_new_with_label (presname);
        g_signal_connect (GTK_OBJECT (menuitem), "activate", G_CALLBACK (gx_save_presetn2), NULL);
        gtk_menu_append(GTK_MENU(menus), menuitem);
        gtk_widget_show (menuitem);
    }
    cm = 0;
}

//----menu funktion save
void gx_save_presetn1 (GtkMenuItem *menuitem, gpointer save_preset)
{
    GtkWidget *about, *button;
    about = gtk_dialog_new();
    button  = gtk_button_new_with_label("Ok");
    GtkWidget * box = gtk_entry_new ();
    gtk_container_add (GTK_CONTAINER (GTK_DIALOG(about)->vbox), box);
    gtk_container_add (GTK_CONTAINER (GTK_DIALOG(about)->vbox), button);
    g_signal_connect_swapped (button, "clicked",  G_CALLBACK (gx_get_text), box);
    g_signal_connect_swapped (button, "clicked",  G_CALLBACK (gtk_widget_destroy), about);
    gtk_widget_show (button);
    gtk_widget_show (box);
    gtk_widget_show (about);
}

//----menu funktion about
static void gx_show_about( GtkWidget *widget, gpointer data )
{
  string about;

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

  GtkWidget* jack_dialog = gtk_dialog_new();
  gtk_window_set_destroy_with_parent(GTK_WINDOW(jack_dialog), TRUE);

  GtkWidget* box = gtk_vbox_new (0, 4);
  GtkWidget* warning_label = gtk_label_new ("\nWARNING\n");
  GtkWidget* text_label = 
    gtk_label_new ("The jack server is not currently running\n"
		   "You can choose to activate it or terminate guitarix\n");

  GdkColor colorGreen;
  gdk_color_parse("#a6a9aa", &colorGreen);
  gtk_widget_modify_fg (text_label, GTK_STATE_NORMAL, &colorGreen);

  GdkColor colorBlack;
  gdk_color_parse("#000000", &colorBlack);
  gtk_widget_modify_bg (jack_dialog, GTK_STATE_NORMAL, &colorBlack);

  GtkStyle* text_style = gtk_widget_get_style(text_label);
  pango_font_description_set_size(text_style->font_desc, 10*PANGO_SCALE);
  pango_font_description_set_weight(text_style->font_desc, PANGO_WEIGHT_BOLD);

  gtk_widget_modify_font(text_label, text_style->font_desc);
  gdk_color_parse("#ffffff", &colorGreen);
  gtk_widget_modify_fg (warning_label, GTK_STATE_NORMAL, &colorGreen);

  text_style = gtk_widget_get_style(warning_label);
  pango_font_description_set_size(text_style->font_desc, 14*PANGO_SCALE);
  pango_font_description_set_weight(text_style->font_desc, PANGO_WEIGHT_BOLD);
  gtk_widget_modify_font(warning_label, text_style->font_desc);

  GtkWidget * box2 = gtk_hbox_new (0, 4);
  GtkWidget * button1  = gtk_dialog_add_button(GTK_DIALOG (jack_dialog),"Start jack",1);
  GtkWidget * button2  = gtk_dialog_add_button(GTK_DIALOG (jack_dialog),"Exit",2);

  gdk_color_parse("#555555", &colorBlack);
  gtk_widget_modify_bg (button1, GTK_STATE_NORMAL, &colorBlack);

  gdk_color_parse("#555555", &colorBlack);
  gtk_widget_modify_bg (button2, GTK_STATE_NORMAL, &colorBlack);

  gtk_container_add (GTK_CONTAINER(box), warning_label);
  gtk_container_add (GTK_CONTAINER(box), text_label);
  gtk_container_add (GTK_CONTAINER(box), box2);
  gtk_container_add (GTK_CONTAINER(GTK_DIALOG(jack_dialog)->vbox), box);

  g_signal_connect (button1, "clicked",  G_CALLBACK (gx_start_jack), NULL);
  g_signal_connect (button2, "clicked",  G_CALLBACK (gx_abort), NULL);
  gtk_widget_show_all(box);
  gtk_widget_show(jack_dialog);

  gtk_dialog_run (GTK_DIALOG (jack_dialog));
  gtk_widget_destroy (jack_dialog);
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
        "gx_set_jack_buffer_size",
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
	  gx_print_warning("gx_set_jack_buffer_size", string("Could not change latency"));

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
}



//--------------------------- jack_capture settings ----------------------------------------
static void gx_show_j_c_gui( GtkWidget *widget, gpointer data )
{
    (void)system ("jack_capture_gui2 -o yes -f ~/guitarix_session -n guitarix -p /.guitarix/ja_ca_ssetrc &");
}

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

    shownote = 2;
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
    const char*	  home;
    home = getenv ("HOME");
    if (home == 0) home = ".";
    char                filename[256];
    snprintf(filename, 256, "%s/.guitarix/resettings", home);
    if (strcmp(witchres, "distortion") == 0) interface->recalladState(filename,  4,  16, 0);
    else if (strcmp(witchres, "freeverb") == 0) interface->recalladState(filename,  20,  24, 1);
    else if (strcmp(witchres, "ImpulseResponse") == 0) interface->recalladState(filename,  28,  32, 2);
    else if (strcmp(witchres, "crybaby") == 0) interface->recalladState(filename,  16,  20, 3);
    else if (strcmp(witchres, "midi out") == 0) interface->recalladState(filename,  44,  50, 4);
    else if (strcmp(witchres, "compressor") == 0) interface->recalladState(filename,  72,  78, 5);
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

//---- find latest process ID
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
static void gx_message_popup(const char* msg)
{
  // check msg validity
  if (!msg)
  {
    gx_print_warning("gx_message_popup", 
		     string("warning message does not exist"));
    return;
  }

  // build popup window
  GtkWidget *about;
  GtkWidget *label;
  GtkWidget *ok_button;

  about = gtk_dialog_new();
  ok_button  = gtk_button_new_with_label("OK");

  label = gtk_label_new (msg);

  GtkStyle *style = gtk_widget_get_style(label);

  pango_font_description_set_size(style->font_desc, 10*PANGO_SCALE);
  pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);

  gtk_widget_modify_font(label, style->font_desc);

  gtk_label_set_selectable(GTK_LABEL(label), TRUE);

  gtk_container_add (GTK_CONTAINER (GTK_DIALOG(about)->vbox), label);
  gtk_container_add (GTK_CONTAINER (GTK_DIALOG(about)->vbox), ok_button);

  g_signal_connect_swapped (ok_button, "clicked",
			    G_CALLBACK (gtk_widget_destroy), about);
  gtk_widget_show (ok_button);
  gtk_widget_show (label);
  gtk_widget_show (about);
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
  idx %= GX_NUM_OF_SKINS;

  // did it work ? if yes, update current skin
  if (gx_update_skin(idx, "gx_cycle_through_skin"))
    gx_current_skin = idx;
}

// ---- skin changer, used internally frm callbacks
static bool gx_update_skin(const gint idx, const char* calling_func)
{ 
  // check skin validity 
  if (idx < GX_SKIN_START || idx >= GX_NUM_OF_SKINS)
  {
    gx_print_warning(calling_func, "skin index out of range, keeping actual skin");
    return false;
  }
      

  string rcfile = GX_STYLE_DIR + string("/") + "guitarix_";
  rcfile += skins[idx];
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
  for (int s = GX_SKIN_START; s < GX_NUM_OF_SKINS; s++)
    if (skin_name == skins[s])
    {
      gx_current_skin = s;
      return;
    }
}  
