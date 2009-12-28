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
#include <set>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <cstdio>

using namespace std;

#include <sys/stat.h>
#include <string.h>
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

    // ---- parse command line arguments
    try {
      gboolean version = FALSE;
      GOptionEntry opt_entries[] = {
        { "version", 'v', 0, G_OPTION_ARG_NONE, &version, "Print version string and exit", NULL },
        { NULL }
      };
      GError* error = NULL;
      GOptionContext* opt_context = NULL;

      opt_context = g_option_context_new(NULL);
      g_option_context_set_summary(opt_context,
          "All parameters are optional. Examples:\n"
          "\tguitarix\n"
          "\tguitarix -r black -i system:capture_3\n"
          "\tguitarix -c -o system:playback_1 -o system:playback_2");
      g_option_context_add_main_entries(opt_context, opt_entries, NULL);

      // GTK options: rc style (aka skin)
      string opskin("Style to use");

      vector<string>::iterator it;

      for (it = gx_gui::skin_list.begin(); it != gx_gui::skin_list.end(); it++)
      {
	opskin += ", '" + *it + "'";
      }

      gboolean clear = FALSE;
      gchar* rcset = NULL;
      GOptionGroup* optgroup_gtk = g_option_group_new("gtk",
          "\033[1;32mGTK configuration options\033[0m",
          "\033[1;32mGTK configuration options\033[0m",
          NULL, NULL);
      GOptionEntry opt_entries_gtk[] = {
        { "clear", 'c', 0, G_OPTION_ARG_NONE, &clear, "Use 'default' GTK style", NULL },
        { "rcset", 'r', 0, G_OPTION_ARG_STRING, &rcset, opskin.c_str(), "STYLE" },
        { NULL }
      };
      g_option_group_add_entries(optgroup_gtk, opt_entries_gtk);

      // JACK options: input and output ports
      gchar* jack_input = NULL;
      gchar** jack_outputs = NULL;
      GOptionGroup* optgroup_jack = g_option_group_new("jack",
          "\033[1;32mJACK configuration options\033[0m",
          "\033[1;32mJACK configuration options\033[0m",
          NULL, NULL);
      GOptionEntry opt_entries_jack[] = {
        { "jack-input", 'i', 0, G_OPTION_ARG_STRING, &jack_input, "Guitarix JACK input", "PORT" },
        {"jack-output", 'o', 0, G_OPTION_ARG_STRING_ARRAY, &jack_outputs, "Guitarix JACK outputs", "PORT" },
        { NULL }
      };
      g_option_group_add_entries(optgroup_jack, opt_entries_jack);

      // collecting all option groups
      g_option_context_add_group(opt_context, optgroup_gtk);
      g_option_context_add_group(opt_context, optgroup_jack);

      // parsing command options
      if (!g_option_context_parse(opt_context, &argc, &argv, &error)) {
        throw string(error->message);
      }
      g_option_context_free(opt_context);


      // ----------- processing user options -----------

      // *** display version if requested
      if (version) {
	cout << "Guitarix version \033[1;32m"
	     << GX_VERSION << endl
	     << "\033[0m   Copyright " << (char)0x40 << " 2009 "
	     << "Hermman Meyer - James Warden"
	     << endl;
	exit(0);
      }

      // *** process GTK rc style
      bool previous_conflict = false;
      if (rcset != NULL) {
	// retrieve user value
	string tmp = rcset;

	// check contradiction (clear and rcset cannot be used in the same call)
	if (clear) {
	  gx_print_error("main",
			 string("-c and -r cannot be used together, defaulting to 'default' style"));
	  tmp = "default";
	  previous_conflict = true;
	}

	// if garbage, let's initialize to guitarix_default.rc
	guint s = 0;
	while (s < gx_gui::skin_list.size()) {
	  if (tmp == gx_gui::skin_list[s])
	    break;
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
        gx_gui::no_opt_skin = 1;
      }

      // *** process GTK clear
      if (clear) {
	// check contradiction (clear and rcset cannot be used in the same call)
	if (rcset != NULL && !previous_conflict)
	  gx_print_error("main",
			 string("-c and -r cannot be used together, defaulting to 'default' style"));

	optvar[RC_STYLE] = "default";
      }

      if (rcset != NULL) {
        g_free(rcset);
      }

      // *** process jack input
      if (jack_input != NULL) {
	optvar[JACK_INP] = jack_input;
        g_free(jack_input);
      }
      else if (!gx_shellvar_exists(optvar[JACK_INP])) {
	optvar[JACK_INP] = ""; // leads to no automatic connection
      }

      // *** process jack outputs
      if (jack_outputs != NULL) {
        int idx = JACK_OUT1;
        unsigned int i = 0;

        while (jack_outputs[i] != NULL) {
          if (i >= 2) {
            gx_print_warning("main",
                "Warning --> provided more than 2 output ports, ignoring extra ports");
            break;
          }
          optvar[idx] = string(jack_outputs[i]);
          i++;
          idx++;
        }
        g_strfreev(jack_outputs);
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
    catch(string& e) {
      string msg = string("Error in user options! ") + e;
      gx_print_error("main", msg);
      exit(1);
    }
  }

  // ---- log message handler
  void gx_print_logmsg(const char* func, const string& msg, GxMsgType msgtype)
  {
    string msgbuf("  ");
    msgbuf += func;
    msgbuf += "  ***  ";
    msgbuf += msg;

    // log the stuff to the log message window if possible
    bool terminal  = true;
    bool gui_is_up = gx_gui::GxMainInterface::fInitialized;

    if (gui_is_up)
    {
      gx_gui::GxMainInterface* interface =
	gx_gui::GxMainInterface::instance();

      // retrievw window
      GtkTextView* logw = interface->getLoggingWindow();

      if (logw)
      {
	terminal = false;

	// retrieve gtk text buffer
	GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(logw));

	// number of lines (we only keep ~ 50 lines all the time)
	const int nlines = gtk_text_buffer_get_line_count(buffer);

	// counter
	static int i = 0;
	int j = i;

	// cosmetic
	time_t now;
        struct tm *tm_now;
        char buf[16];

        time(&now);
        tm_now = localtime (&now);

        sprintf(buf, "[%02d:%02d:%02d]",
		tm_now->tm_hour, tm_now->tm_min, tm_now->tm_sec);
	ostringstream spos; spos << buf;
	msgbuf.insert(0, spos.str());


	GtkTextIter iter1;
	GtkTextIter iter2;

	// delete first line when window filled up
	if (i >= nlines)
	{
	  gtk_text_buffer_get_iter_at_line(buffer, &iter1, 0);
	  gtk_text_buffer_get_iter_at_line(buffer, &iter2, 1);
	  gtk_text_buffer_delete(buffer, &iter1, &iter2);

	  GtkTextIter iter;
	  gtk_text_buffer_get_end_iter(buffer, &iter);
	  gtk_text_buffer_insert(buffer, &iter, "\n", -1);

	  j = nlines-1;
	}

	// replace existing text between marks
	gtk_text_buffer_get_iter_at_line(buffer, &iter1, j);
	gtk_text_buffer_insert(buffer, &iter1, msgbuf.c_str(), -1);

	gtk_text_buffer_get_iter_at_line(buffer, &iter1, j);
	GtkTextMark* scroll_to =
	  gtk_text_buffer_create_mark(buffer, NULL, &iter1, true);
	gtk_text_view_scroll_mark_onscreen (GTK_TEXT_VIEW(logw),scroll_to);

	// add color depending on msg type
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

	gtk_text_buffer_get_iter_at_line(buffer, &iter1, j);
	gtk_text_buffer_get_iter_at_line(buffer, &iter2, j+1);

	if (j+1 == nlines)
	  gtk_text_buffer_get_end_iter(buffer, &iter2);

	gtk_text_buffer_apply_tag(buffer, tag, &iter1, &iter2);

	// modify expander bg color is closed
	GtkExpander* exbox = interface->getLoggingBox();
	if (gtk_expander_get_expanded(exbox) == FALSE)
	{
	  GdkColor exp_color;
	  gdk_color_parse(col.c_str(), &exp_color);
	  gtk_widget_modify_fg(GTK_WIDGET(exbox), GTK_STATE_NORMAL, &exp_color);
	}

	i++;

      }
    }

    // if no window, then terminal
    if (terminal) cerr << msgbuf << endl;

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

    int abs_i = abs(double(i));
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
    gx_jack::NO_CONNECTION = 1;

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

    if (G_IS_OBJECT(gx_gui::tribeimage))
        g_object_unref(gx_gui::tribeimage);

    if (G_IS_OBJECT(gx_gui::_image))
        g_object_unref(gx_gui::_image);

    gtk_main_quit();
  }

  //-----Function that must be called before complete shutdown
  void gx_clean_exit(GtkWidget* widget, gpointer data)
  {
    // save DSP state
    GxEngine* engine = GxEngine::instance();
    if (engine->isInitialized()) {
      string previous_state = gx_user_dir + client_name + "rc";
      engine->get_latency_warning_change();
      gx_gui::gx_get_skin_change(&engine->fskin);

      // only save if we are not in a preset context
      if (!setting_is_preset)
	gx_gui::GxMainInterface::instance()->
	  saveStateToFile(previous_state.c_str());
    }

     if (gx_gui::fWindow)
       gx_destroy_event();

     // clean jack client stuff
     gx_jack_cleanup();
     // delete the locked mem buffers
     if (checkfreq)
       delete[] checkfreq;
     if (get_frame)
       delete[] get_frame;
     if (get_frame1)
       delete[] get_frame1;
     if (oversample)
       delete[] oversample;

     exit(GPOINTER_TO_INT(data));
  }


} /* end of gx_system namespace */
