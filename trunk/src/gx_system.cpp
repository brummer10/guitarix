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
 *    This is the guitarix system interface
 *
 * ----------------------------------------------------------------------------
 */

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <map>


using namespace std;

#include <boost/program_options.hpp>
namespace bpo = boost::program_options;

#include <sys/stat.h>
#include <sndfile.h>
#include <jack/jack.h>
#include <gtk/gtk.h>
#include "guitarix.h"

using namespace gx_engine;
using namespace gx_jack;
using namespace gx_preset;

namespace gx_system
{
  // ---- retrieve and store the shell variable if not NULL
  void gx_assign_shell_var(const char* name, string& value)
  {
    const char* val = getenv(name);
    value = (val != NULL) ? val : "" ;
  }

  // ---- is the shell variable set ?
  bool gx_shellvar_exists(const string& var)
  {
    return !var.empty();
  }

  // ---- OS signal handler ----- 
  void gx_signal_handler(int sig)
  {
    // print out a warning
    string msg = string("signal ") + gx_i2a(sig) + " received, exiting ...";
    gx_print_warning("signal_handler", msg);
    
    gx_clean_exit(NULL, NULL);
  }

  // ---- command line options
  void gx_process_cmdline_options(int& argc, char**& argv, string* optvar)
  {
    // store shell variable content
    for (int i = 0; i < NUM_SHELL_VAR; i++)
      gx_assign_shell_var(shell_var_name[i], optvar[i]);

    // initialize number of skins. We just count the number of rc files
    unsigned int n = gx_gui::gx_fetch_available_skins();
    if (n < 1) {
      gx_print_error("main", string("number of skins is 0, aborting ..."));
      exit(1);
    }
    
    // ---- parse command line arguments, using the boost::program_options lib
    try {
      // Note: using the boost_program_options framework
      // We could set defaults in option declaration but we won't
      // 
    
      // generic options: version and help
      bpo::options_description opt_gen;
      opt_gen.add_options()
	("help,h",    "Print this help")
	("version,v", "Print version string and exit")
	;
    
      // GTK options: rc style (aka skin) 
      ostringstream opskin("Style to use"); 

      vector<string>::iterator it;

      for (it = gx_gui::skin_list.begin(); it != gx_gui::skin_list.end(); it++)
      {
	gx_print_info("skin", *it);
	opskin << ", '" << *it << "'";
      }

      bpo::options_description opt_gtk("\033[1;32m GTK configuration options\033[0m");
      opt_gtk.add_options()
	("clear,c", "Use 'default' GTK style")
	("rcset,r", bpo::value<string>(), opskin.str().c_str())
	;
     
      // JACK options: input and output ports
      bpo::options_description opt_jack("\033[1;32m JACK configuration options\033[0m");
      opt_jack.add_options()
	("jack-input,i",   bpo::value<string>(), "Guitarix jack input")
	("jack-output,o",  bpo::value<vector <string> >()->multitoken(), 
	 "Guitarix jack outputs")
	;
        
      // collecting all option groups
      bpo::options_description cmdline_opt(
          "\033[1;34m guitarix usage\033[0m\n"
          " all parameters are optional. Examples:\n"
          "\tguitarix\n"
          "\tguitarix -r black -i system:capture_3\n"
          "\tguitarix -c -o system:playback_1 system:playback_2\n"
      );
      cmdline_opt.add(opt_gen).add(opt_gtk).add(opt_jack);
    
    
      // parsing command options
      bpo::variables_map vm;
      bpo::store(bpo::parse_command_line(argc, argv, cmdline_opt), vm);
      bpo::notify(vm);
    
      
      // ----------- processing user options -----------
      bool gx_exit = false;
    
      // *** display help if requested
      if (vm.count("help")) {
	cout << cmdline_opt << endl;
	gx_exit = true;
      }
      
      // *** display version if requested
      if (vm.count("version")) {
	cout << "Guitarix version \033[1;32m" 
	     << GX_VERSION << endl
	     << "\033[0m   Copyright " << (char)0x40 << " 2009 " 
	     << "Hermman Meyer - James Warden"
	     << endl;
	gx_exit = true;
      }
    
      if (gx_exit) exit(0);
    
      // *** process GTK rc style
      bool previous_conflict = false;
      if (vm.count("rcset")) {
	// retrieve user value
	string tmp = vm["rcset"].as<string>();
	
	// check contradiction (clear and rcset cannot be used in the same call)
	if (vm.count("clear")) { 
	  gx_print_error("main",
			 string("-c and -r cannot be used together, defaulting to 'default' style"));
	  tmp = "default";
	  previous_conflict = true;
	}
    
	// if garbage, let's initialize to guitarix_default.rc
	guint s = 0;
	while (s < gx_gui::skin_list.size()) {
	  if (tmp == gx_gui::skin_list[s]) break;
	  s++;
	}
	
	if (s == gx_gui::skin_list.size()) {  
	  gx_print_error("main",
			 string("rcset value is garbage, defaulting to 'default' style"));
	  tmp = "default";
	}
	optvar[RC_STYLE] = tmp;
      }
    
      // else, if no shell var defined for it, defaulting to guitarix_default.rc
      else if (!gx_shellvar_exists(optvar[RC_STYLE])) {  
	optvar[RC_STYLE] = "default";
        // enable set last used skin
        no_opt_skin = 1;
      }

      // *** process GTK clear
      if (vm.count("clear")) {
	// check contradiction (clear and rcset cannot be used in the same call)
	if (vm.count("rcset") && !previous_conflict)
	  gx_print_error("main",
			 string("-c and -r cannot be used together, defaulting to 'default' style"));
	
	optvar[RC_STYLE] = "default";
      }
    
      // *** process jack input
      if (vm.count("jack-input")) {
	optvar[JACK_INP] = vm["jack-input"].as<string>();
      }
      else if (!gx_shellvar_exists(optvar[JACK_INP])) {  
	optvar[JACK_INP] = ""; // leads to no automatic connection
      }
    
      // *** process jack outputs
      if (vm.count("jack-output")) {
	// loop through output port strings
	const vector<string>& s = vm["jack-output"].as<vector <string> >();

	int idx = JACK_OUT1;
	for (unsigned int i = 0; i < min(2, s.size()); i++)
	  optvar[idx++] = s[i];

	if (s.size() > 2)
	  gx_print_warning("main",
			   string("Warning --> provided more than 2 output ports, " 
				  "ignoring extra ports")
			   ); 
      }
      else {  
	if (!gx_shellvar_exists(optvar[JACK_OUT1])) optvar[JACK_OUT1] = "";
	if (!gx_shellvar_exists(optvar[JACK_OUT2])) optvar[JACK_OUT2] = "";
      }


      // 
      rcpath = GX_STYLE_DIR + string("/") + string("guitarix_") + optvar[RC_STYLE] + ".rc";

      gx_gui::gx_actualize_skin_index(optvar[RC_STYLE]);
    }

    // ---- catch exceptions that occured during user option parsing
    catch(exception& e) {
      string msg = string("Error in user options! ") + e.what();
      gx_print_error("main", msg);
      exit(1);
    }
  }

  // ---- log message handler
  void gx_print_logmsg(const char* func, const string& msg, GxMsgType msgtype)
  {
    
    string msgbuf = ">  ";
    msgbuf += func;
    msgbuf += "  ***  ";
    msgbuf += msg;

    // log the stuff to the log message window if possible
    bool terminal  = false;
    bool gui_is_up = gx_gui::GxMainInterface::fInitialized;

    if (gui_is_up)
    {
      gx_gui::GxMainInterface* interface = 
	gx_gui::GxMainInterface::instance();

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
	(void)gx_system_call ("rm -f", oldfiles.c_str(), false);

	oldfiles = gx_user_dir + string("version*");
	(void)gx_system_call ("rm -f", oldfiles.c_str(), false);

	oldfiles = gx_user_dir + string("*.conf");
	(void)gx_system_call ("rm -f", oldfiles.c_str(), false);

	// setting file for current version
	ofstream f(rcfilename.c_str());
	string cim = string("guitarix-") + GX_VERSION;
	f << cim <<endl;
	f.close();

	string resetfile = gx_user_dir + "resettings";
	ofstream fa(resetfile.c_str());
	fa <<  default_setting <<endl;
	fa.close();

	// --- create jack_capture setting file
	string tmpstr = gx_user_dir + jcapsetup_file;

	(void)gx_system_call("touch", tmpstr.c_str(), false);
	(void)gx_system_call(
	      "echo 'jack_capture -c 2 --silent --disable-meter --port guitarix:out* ' >",
	      tmpstr.c_str(),
	      false
	);
	
	// --- default jconv setting 
	(void)gx_jconv::gx_save_jconv_settings(NULL, NULL);
      }
    }
    else // directory does not exist
    {
      // create .guitarix directory
      (void)gx_system_call("mkdir -p", gx_user_dir.c_str(), false);
      
      // setting file for current version
      ofstream f(rcfilename.c_str());
      string cim = string("guitarix-") + GX_VERSION;
      f << cim <<endl;
      f.close();

      // --- create jack_capture setting file
      string tmpstr = gx_user_dir + jcapsetup_file;

      (void)gx_system_call("touch", tmpstr.c_str(), false);
      (void)gx_system_call(
	 "echo 'jack_capture -c 2 --silent --disable-meter --port guitarix:out* ' >",
	 tmpstr.c_str(),
	 false
      );
      
      // --- default jconv setting 
      (void)gx_jconv::gx_save_jconv_settings(NULL, NULL);

      // --- version file
      //same here, we only change this file, when the presethandling is broken,
      // otherwise we can let it untouched
      tmpstr = gx_user_dir + string("version-") + string("0.03.3");
      (void)gx_system_call("touch", tmpstr.c_str(), false);

      cim = string("echo 'guitarix-") + string(GX_VERSION) + "' >";
      (void)gx_system_call(cim.c_str(), tmpstr.c_str(), false);

      // --- guitarix own default settings
      tmpstr = gx_user_dir + guitarix_reset;
      (void)gx_system_call("touch", tmpstr.c_str(), false);

      cim = "echo -e '" + string(default_setting) + "' >";
      (void)gx_system_call(cim.c_str(), tmpstr.c_str(), false);
    }

    // initialize with what we already have, if we have something
    string s; gx_jconv::GxJConvSettings::instance()->configureJConvSettings(s);
    
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
      gx_print_error("Pixmap Check", " cannot find installed pixmaps! giving up ...");

      // giving up
      return 1;
    }

    GtkWidget *ibf =  gtk_image_new_from_file (gx_pix.c_str());
    gx_gui::ib = gtk_image_get_pixbuf (GTK_IMAGE(ibf));

    GtkWidget *stim = gtk_image_new_from_file (midi_pix.c_str());
    gx_gui::ibm = gtk_image_get_pixbuf (GTK_IMAGE(stim));

    GtkWidget *stir = gtk_image_new_from_file (warn_pix.c_str());
    gx_gui::ibr = gtk_image_get_pixbuf (GTK_IMAGE(stir));

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

  //----clean up preset name given by user
  void gx_nospace_in_name(string& name, const char* subs)
  {
    int p = name.find(' ', 0);
    while (p != -1) {
      name.replace(p++, 1, subs);
      p = name.find(' ', p);
    }
  }

  //----abort guitarix
  void gx_abort(void* arg)
  {
    gx_print_warning("gx_abort", "Aborting guitarix, ciao!");
    exit(1);
  }
  
  //---- guitarix system function
  int gx_system_call(const char* name1,
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
    
    //    cerr << " ********* \n system command = " << str.c_str() << endl;
    
    return system(str.c_str());
  }
  
  // polymorph1
  int gx_system_call(const char*   name1,
		     const string& name2,
		     const bool  devnull,
		     const bool  escape)
  {
    return gx_system_call(name1, name2.c_str(), devnull, escape);
  }
  
  // polymorph2
  // int gx_system_call(const string& name1,
  //    	     const string& name2,
  // 		     const bool  devnull,
  // 		     const bool  escape)
  // {
  //   return gx_system_call(name1.c_str(), name2.c_str(), devnull, escape);
  // }
  
  // polymorph3
  int gx_system_call(const string& name1,
		     const char*   name2,
		     const bool  devnull,
		     const bool  escape)
  {
    return gx_system_call(name1.c_str(), name2, devnull, escape);
  }


  //----- clean up when shut down
  void gx_destroy_event()
  {
    (void)gx_child_process::gx_terminate_child_procs();

    gx_gui::shownote = -1;
    gx_gui::showwave = 0;

    gx_engine::stopit = "stop";
    dsp::turnOffMidi();

    gx_waveview_destroy(GTK_WIDGET(gx_gui::livewa), NULL);

    GtkRegler::gtk_regler_destroy();

    if (G_IS_OBJECT(gx_gui::ib))
      g_object_unref(gx_gui::ib);

    if (G_IS_OBJECT(gx_gui::ibm))
      g_object_unref(gx_gui::ibm);

    if (G_IS_OBJECT(gx_gui::ibr))
      g_object_unref(gx_gui::ibr);

    gtk_main_quit();
  }

  //-----Function that must be called before complete shutdown
  void gx_clean_exit(GtkWidget* widget, gpointer data)
  {

    // clean jack client stuff
    string jcl_name = "guitarix";
    
    if (jack_is_running) {
      jcl_name = jack_get_client_name(client);
      gx_jack_cleanup();
      jack_is_running = false;
    }

    // save DSP state
    GxEngine* engine = GxEngine::instance();
    if (engine->isInitialized()) {
      string previous_state = gx_user_dir + jcl_name + "rc";
      engine->get_latency_warning_change();
      engine->get_skin_change();
      
      // only save if we are not in a preset context
      if (!setting_is_preset)
	gx_gui::GxMainInterface::instance()->
	  saveStateToFile(previous_state.c_str());
    }

    if (gx_gui::fWindow)
      gx_destroy_event();

    // delete the locked mem buffers
    if (checkfreq)
      delete[] checkfreq;
    if (get_frame)
      delete[] get_frame;
    if (oversample)
      delete[] oversample;

    exit(GPOINTER_TO_INT(data));
  }


} /* end of gx_system namespace */
