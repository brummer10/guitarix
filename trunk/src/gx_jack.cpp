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
 *  This is the guitarix interface to the jackd audio / midi server
 *
 * --------------------------------------------------------------------------
 */
#include <errno.h>

#include <cstring>
#include <vector>
#include <list>
#include <map>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>

using namespace std;

#include <sndfile.h>
#include <jack/jack.h>
#include <jack/statistics.h>
#include <jack/midiport.h>
#include <gtk/gtk.h>
#include "guitarix.h"

using namespace gx_system;
using namespace gx_engine;
using namespace gx_jconv;
using namespace gx_child_process;

namespace gx_jack
{

  //----- pop up a dialog for starting jack
  bool gx_jack_init()
  {
    jack_status_t jackstat;
    client_name = "guitarix";

    // init the pointer to the jackbuffer
    for (int i=0; i < nOPorts; i++) output_ports[i] = 0;
    for (int i=0; i < nIPorts; i++) input_ports [i] = 0;

    AVOIDDENORMALS;

    // try to open jack client
    client = jack_client_open (client_name.c_str(), JackNoStartServer, &jackstat);

    if (client == 0) {
      gx_print_warning("Jack Init", "not yet a jack client");

      // if jackd is running, let's call ourselves again
      if (gx_system_call("pgrep", "jackd", true) == SYSTEM_OK)
      {
	gx_print_warning("Jack Init", "jackd OK, trying to be a client");
	usleep(500000);
	return gx_jack_init();
      }

      // start a dialog
      if (gx_start_jack_dialog()) {
	// so let's try to be a jack client again
	client = jack_client_open (client_name.c_str(), JackNoStartServer, &jackstat);

	if (!client) {
	  gx_print_error("main",
			 string("I really tried to get jack up and running, sorry ... "));
	  return false;
	}
      }

      else { // we give up
	gx_print_error("main",
		       string("Ignoring jackd ..."));
	return false;
      }
    }

    // ----------------------------------
    jack_is_down = false;

    // it is maybe not the 1st guitarix instance ?
    if (jackstat & JackNameNotUnique)
      client_name = jack_get_client_name (client);

#ifdef USE_RINGBUFFER
    jack_ringbuffer = jack_ringbuffer_create(2048*sizeof(struct MidiMessage));

    if (jack_ringbuffer == NULL) {
      g_critical("Cannot create JACK ringbuffer.");
      gx_clean_exit(NULL, NULL);
    }

    jack_ringbuffer_reset(jack_ringbuffer);
    jack_ringbuffer_mlock(jack_ringbuffer);

#endif

    jack_sr = jack_get_sample_rate (client); // jack sample rate
    ostringstream s; s << "The jack sample rate is " << jack_sr << "/sec";
    gx_print_info("Jack init", s.str().c_str());

    jack_bs = jack_get_buffer_size (client); // jack buffer size
    s.str(""); s << "The jack buffer size is " << jack_bs << "/frames ... ";

    gx_print_info("Jack init", s.str());


    if (gx_gui::fWindow)
      gtk_window_set_title (GTK_WINDOW (gx_gui::fWindow), client_name.c_str());

    return true;
  }

  //----- set client callbacks and activate client
  // Note: to be called after gx_engine::gx_engine_init()
  void gx_jack_callbacks_and_activate()
  {
    //----- set the jack callbacks
    jack_set_port_registration_callback (client, gx_jack_port_callback, NULL);
    jack_set_graph_order_callback (client, gx_jack_graph_callback, NULL);
    jack_set_xrun_callback(client, gx_jack_xrun_callback, NULL);
    jack_set_sample_rate_callback(client, gx_jack_srate_callback, 0);
    jack_on_shutdown(client, gx_jack_shutdown_callback, NULL);
    jack_set_buffer_size_callback (client, gx_jack_buffersize_callback, 0);
    jack_set_process_callback(client, gx_jack_process, 0);
    jack_set_client_registration_callback(client, gx_jack_clientreg_callback, 0);
    jack_set_port_registration_callback(client, gx_jack_portreg_callback, 0);

    //----- register the input channel
    for (int i = 0; i < gNumInChans; i++) {
      ostringstream buf; buf <<  "in_" << i;
      input_ports[i] =
	jack_port_register(client, buf.str().c_str(),
			   JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);
    }

    //----- register the midi output channel
    midi_output_ports =
      jack_port_register(client, "midi_out_1", JACK_DEFAULT_MIDI_TYPE, JackPortIsOutput, 0);

    //----- register the audio output channels
    for (int i = 0; i < gNumOutChans; i++) {
      ostringstream buf; buf <<  "out_" << i;
      output_ports[i] =
	jack_port_register(client, buf.str().c_str(),
			   JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
    }

    //----- ready to go
    if (jack_activate(client))
    {
      gx_print_error("Jack Activation",
		     string("Can't activate JACK client"));
      gx_clean_exit(NULL, NULL);
    }
  }

  //----- connect ports if we know them
  void gx_jack_init_port_connection(const string* optvar)
  {
    // set autoconnect capture to user capture port
    if (!optvar[JACK_INP].empty())
    {
      for (int i = 0; i < gNumInChans; i++)
      {
	jack_connect(client, optvar[JACK_INP].c_str(),
		     jack_port_name(input_ports[i]));
      }
    }

    // set autoconnect to user playback ports
    int idx = JACK_OUT1;
    for (int i = 0; i < 2; i++)
    {
      if (!optvar[idx].empty())
	jack_connect(client,
		     jack_port_name(output_ports[i]), optvar[idx].c_str());

      idx++;
    }
  }

  //----- pop up a dialog for starting jack
  bool gx_start_jack_dialog()
  {
    //--- run dialog and check response
    const guint nchoices    = 3;

    const char* labels[]    = {
      "Start Jack", "Ignore Jack", "Exit"
    };

    const gint  responses[] = {
      GTK_RESPONSE_YES, GTK_RESPONSE_NO, GTK_RESPONSE_CANCEL
    };

    gint response =
      gx_gui::gx_nchoice_dialog_without_entry (
	" Jack Starter ",
	"\n                        WARNING                        \n\n"
	"   The jack server is not currently running\n"
	"   You can choose to activate it or terminate guitarix   \n\n"
	"       1) activate jack   \n"
	"       2) ignore jack, start guitarix anyway   \n"
	"       3) exit guitarix   \n",
	nchoices,
	labels,
	responses,
	GTK_RESPONSE_YES
      );

    // we are cancelling
    bool retstat = false;

    switch (response)
    {
    case GTK_RESPONSE_NO:
      jack_is_down = true;
      break;

    case GTK_RESPONSE_CANCEL:
      gx_abort(NULL);
      break;

    default:
    case GTK_RESPONSE_YES:
      retstat = gx_start_jack(NULL);
      break;
    }

    // start jack
    return retstat;
  }


  //----start jack if possible
  bool gx_start_jack(void* arg)
  {
    // first, let's try via qjackctl
    if (gx_system_call("which", "qjackctl", true) == SYSTEM_OK) {
      if (gx_system_call("qjackctl", "--start", true, true) == SYSTEM_OK) {
	sleep(1);

	// let's check it is really running
	if (gx_system_call("pgrep", "jackd", true) == SYSTEM_OK) {
	  return true;
	}
      }
    }

    // qjackctl not found or not started, let's try .jackdrc
    string jackdrc = "$HOME/.jackdrc";
    if (gx_system_call("ls", jackdrc.c_str(), true, false) == SYSTEM_OK) {
      // open it
      jackdrc = string(getenv("HOME")) + string("/") + ".jackdrc";
      string cmdline = "";

      ifstream f(jackdrc.c_str());
      if (f.good()) {
	// should contain only one command line
	getline(f, cmdline);
	f.close();
      }

      // launch jackd
      if (!cmdline.empty())
	if (gx_system_call(cmdline.c_str(), "", true, true) == SYSTEM_OK) {
	  sleep(1);

	  // let's check it is really running
	  if (gx_system_call("pgrep", "jackd", true) == SYSTEM_OK) {
	    return true;
	  }
	}

    }

    return false;
  }

  //---- Jack server connection / disconnection
  void gx_jack_connection(GtkCheckMenuItem *menuitem, gpointer arg)
  {
    if (gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM (menuitem)) == TRUE)
    {
      if (!client)
      {
	if (gx_jack_init())
	{
	  string optvar[NUM_SHELL_VAR];
	  gx_assign_shell_var(shell_var_name[JACK_INP],  optvar[JACK_INP] );
	  gx_assign_shell_var(shell_var_name[JACK_OUT1], optvar[JACK_OUT1]);
	  gx_assign_shell_var(shell_var_name[JACK_OUT2], optvar[JACK_OUT2]);

	  // initialize guitarix engine if necessary
	  if (!gx_engine::initialized)
	    gx_engine::gx_engine_init();

	  gx_jack_callbacks_and_activate();
	  gx_jack_init_port_connection(optvar);

	  // refresh latency check menu
	  gx_gui::GxMainInterface* gui = gx_gui::GxMainInterface::instance();
	  GtkWidget* wd = gui->getJackLatencyItem(gx_jack::jack_bs);
	  if (wd)
	    gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(wd), TRUE);

	  // check jconv stuff
	  if (gx_jconv::jconv_is_running)
	  {
	    ostringstream buf;

	    // extra guitarix jack ports for jconv
	    for (int i = 2; i < 4; i++)
	    {
	      buf.str("");
	      buf << "out_" << i;

	      output_ports[i] =
		  jack_port_register(client,
				   buf.str().c_str(),
				   JACK_DEFAULT_AUDIO_TYPE,
				   JackPortIsOutput, 0);
	      gx_engine::gNumOutChans++;
	    }
	    for (int i = 2; i < 4; i++)
	    {

	      buf.str("");
          buf << "in_" << i-1;

          input_ports[i-1] =
          jack_port_register(client,
				       buf.str().c_str(),
				       JACK_DEFAULT_AUDIO_TYPE,
				       JackPortIsInput, 0);
		  gx_engine::gNumInChans++;
	    }

	    // ---- port connection

	    // guitarix outs to jconv ins
	    jack_connect(client, jack_port_name(output_ports[2]), "jconv:In-1");
	    jack_connect(client, jack_port_name(output_ports[3]), "jconv:In-2");
	  }

	  // restore jack client menus
	  gx_gui::GxMainInterface::instance()->initJackClientMenus();

	}
      }

      if (client)
      {
	if (gx_gui::gx_jackd_on_image)
	{
	  gtk_widget_show(gx_gui::gx_jackd_on_image);
	  gtk_widget_hide(gx_gui::gx_jackd_off_image);
	}

	gx_print_info("Jack Server", "Connected to Jack Server");
      }
    }
    else
    {
      gx_jack_cleanup();

      if (gx_jconv::jconv_is_running)
	gNumOutChans -= 2;


      // we bring down jack capture and meterbridge but not jconv
      // meterbridge
      if (child_pid[METERBG_IDX] != NO_PID)
      {
	(void)kill(child_pid[METERBG_IDX], SIGTERM);
	(void)gx_system_call("rm -f", mbg_pidfile.c_str(), true);
	child_pid[METERBG_IDX] = NO_PID;
      }

      // jack_capture
      if (child_pid[JACKCAP_IDX] != NO_PID)
      {
	(void)kill(child_pid[JACKCAP_IDX], SIGINT);
	(void)gx_pclose(jcap_stream, JACKCAP_IDX);

	if (gx_gui::record_button)
	  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gx_gui::record_button),
				       FALSE);
      }

      if (gx_gui::gx_jackd_on_image)
      {
	gtk_widget_hide(gx_gui::gx_jackd_on_image);
	gtk_widget_show(gx_gui::gx_jackd_off_image);
      }

      // engine buffers no longer ready
      gx_engine::buffers_ready = false;

      // delete all jack client menus
      gx_gui::GxMainInterface::instance()->deleteAllJackClientMenus();

      gx_print_warning("Jack Server", "Disconnected from Jack Server");
    }
  }

  //----jack latency change
  void gx_set_jack_buffer_size(GtkCheckMenuItem *menuitem, gpointer arg)
  {
    // are we a proper jack client ?
    if (!client) {
      gx_print_error(
	"Jack Buffer Size setting",
	"we are not a jack client, server may be down"
      );

      return;
    }

    // ----- if check button triggered menually

    // let's avoid triggering the jack server on "inactive"
    if (gtk_check_menu_item_get_active(menuitem) == false)
      return;

    // requested latency
    jack_nframes_t buf_size = (jack_nframes_t)GPOINTER_TO_INT(arg);

    // if the actual buffer size is the same, no need further action
    if (buf_size == jack_get_buffer_size(client))
      return;


    // first time useage warning
    if (fwarn_swap == 0.0)
      gx_gui::gx_wait_latency_warn();

    else change_latency = kChangeLatency;

    if (change_latency == kChangeLatency)
    {
      int jcio = 0;
      if (jconv_is_running) {
	jcio = 1;
	gx_jconv::GxJConvSettings::checkbutton7 = 0;
	gx_jconv::checkbox7 = 0.0;
	gx_child_process::gx_start_stop_jconv(NULL, NULL);
      }

      // let's resize the buffer
      if (jack_set_buffer_size (client, buf_size) != 0)
	gx_print_warning("Setting Jack Buffer Size",
			 "Could not change latency");

      if (jcio == 1)
      {
	jcio = 0;
	gx_jconv::GxJConvSettings::checkbutton7 = 1;
	gx_jconv::checkbox7 = 1.0;
	gx_child_process::gx_start_stop_jconv(NULL, NULL);
      }
      change_latency = kUnknownAction;
    }

    gx_print_info("Jack Buffer Size",
		  string("latency is ") +
		  gx_i2a(jack_get_buffer_size(client)));
  }

  //-----Function that cleans the jack stuff on shutdown
  void gx_jack_cleanup()
  {
    if (client) {
      // disable input ports
      for (int i = 0; i < gNumInChans; i++)
	jack_port_unregister(client, input_ports[i]);

      for (int i = 0; i < gNumOutChans; i++)
	jack_port_unregister(client, output_ports[i]);

      if (midi_output_ports != NULL)
	jack_port_unregister(client, midi_output_ports);

#ifdef USE_RINGBUFFER
      jack_ringbuffer_free(jack_ringbuffer);
#endif

      jack_deactivate(client);
      jack_client_close(client);
      client = NULL;
    }
  }

  //----jack sample rate change callback
  int gx_jack_srate_callback(jack_nframes_t frames, void* arg)
  {
    /* Note: just reporting log for now  */

    ostringstream s;
    s << " jack sample rate changed to " << frames;
    gx_print_warning("Jack sample rate", s.str());

    return 0;
  }

  //---- jack shutdown callback in case jackd shuts down on us
  void gx_jack_shutdown_callback(void *arg)
  {
    gx_print_warning("Jack Shutdown",
		     "jack has bumped us out!!");

    jack_is_down = true;
  }

  //---- jack client callbacks
  int gx_jack_graph_callback (void* arg)
  {

    if (jack_port_connected(input_ports[0]))
    {
      const char** port = jack_port_get_connections(input_ports[0]);
      setenv("GUITARIX2JACK_INPUTS",port[0],0);
      NO_CONNECTION = 0;
      free(port);
    }
    else NO_CONNECTION = 1;
    if (jack_port_connected (output_ports[0]))
    {
      const char** port1 = jack_port_get_connections(output_ports[0]);
      setenv("GUITARIX2JACK_OUTPUTS1",port1[0],0);
      free(port1);
    }
    if (jack_port_connected (output_ports[1]))
    {
      const char** port2 = jack_port_get_connections(output_ports[1]);
      setenv("GUITARIX2JACK_OUTPUTS2",port2[0],0);
      free(port2);
    }
    return 0;
  }


  //---- jack xrun callback
  int gx_jack_xrun_callback (void* arg)
  {
    if ((last_xrun_time + 1000) < jack_last_frame_time(client)) {
    float xdel = jack_get_xrun_delayed_usecs(client);
    ostringstream s; s << " delay of at least " << xdel << " microsecs";
    gx_print_warning("Jack XRun", s.str());
      }
    last_xrun_time = jack_last_frame_time(client);
    return 0;
  }

  //---- jack port callback
  void gx_jack_port_callback (jack_port_id_t port, int yn, void* arg)
  {
    //printf ("Port %d %s\n", port, (yn ? "registered" : "unregistered"));
  }

  //---- jack buffer size change callback
  int gx_jack_buffersize_callback (jack_nframes_t nframes,void* arg)
  {
    GxEngineState estate = (GxEngineState)checky;

    // turn off engine
    // Note: simply changing checky is enough to "stop" processing
    // incoming jack buffers. The mydsp::compute method is owned by
    // the jack audio thread. It always runs as long as jack runs
    // independently of the non-RT GUI thread. The value of
    // checky is checked at each jack cycle in mydsp::compute
    // so changing it here affects the behavior of mydsp::compute
    // immediately during the jack_processing of jack cycles.

    if (estate != kEngineOff)
      checky = (float)kEngineOff;

    jack_bs = nframes;
    gx_print_info("buffersize_callback",
		  string("the buffer size is now ") +
		  gx_i2a(jack_bs) + string("/frames"));

    if (checkfreq)  delete[] checkfreq;
    if (get_frame)  delete[] get_frame;
    if (get_frame1)  delete[] get_frame1;
    if (oversample) delete[] oversample;

    get_frame = new float[jack_bs];
    (void)memset(get_frame, 0, sizeof(float)*jack_bs);

    get_frame1 = new float[jack_bs];
    (void)memset(get_frame1, 0, sizeof(float)*jack_bs);

    checkfreq = new float[jack_bs];
    (void)memset(checkfreq, 0, sizeof(float)*jack_bs);

    oversample = new float[jack_bs*2];
    (void)memset(oversample, 0, sizeof(float)*jack_bs*2);

    // restore previous state
    checky = (float)estate;
    return 0;
  }

  //---- jack midi processing
#ifndef USE_RINGBUFFER
  int gx_jack_midi_process (jack_nframes_t nframes, void *arg)
  {
    if (midi_output_ports != NULL) {
      AVOIDDENORMALS;

      midi_port_buf =  jack_port_get_buffer(midi_output_ports, nframes);
      jack_midi_clear_buffer(midi_port_buf);

      if ((dsp::isMidiOn() == true) || (gx_gui::showwave == 1))
	jcpu_load = jack_cpu_load(client);

      GxEngine::instance()->compute_midi(nframes);
    }
    return 0;
  }

#else
  int gx_jack_midi_process_ringbuffer (jack_nframes_t nframes, void *arg)
  {

    /*************************************************************************
    The code for the jack_ringbuffer is take from
    jack-keyboard 2.4, a virtual keyboard for JACK MIDI.
    from Edward Tomasz Napierala <trasz@FreeBSD.org>.
    **************************************************************************/
    int read, t;
    unsigned char* buffer ;

    jack_nframes_t last_frame_time = jack_last_frame_time(client);

    midi_port_buf = jack_port_get_buffer(midi_output_ports, nframes);
    jack_midi_clear_buffer( midi_port_buf);

    if (dsp::playmidi == 1) jcpu_load = jack_cpu_load(client);
    GxEngine::instance()->compute_midi(nframes);

    while (jack_ringbuffer_read_space(jack_ringbuffer)) {
      read = jack_ringbuffer_peek(jack_ringbuffer, (char *)&ev, sizeof(ev));

      if (read != sizeof(ev)) {
	// fprintf(stderr, " Short read from the ringbuffer, possible note loss.\n");
	continue;
      }

      t = ev.time + nframes - last_frame_time;
      if ((t >= (int)nframes) || (cpu_load > 75.0))
	break;

      if (t < 0)
	t = 0;

      jack_ringbuffer_read_advance(jack_ringbuffer, sizeof(ev));

      if (jack_midi_max_event_size(midi_port_buf) > sizeof(ev))
	buffer = jack_midi_event_reserve(midi_port_buf, t, ev.len);
      else
	break;

      if (ev.len > 2)
	buffer[2] = ev.data[2];
      if (ev.len > 1)
	  buffer[1] = ev.data[1];

      buffer[0] = ev.data[0];
    }

    /********************************************************************
    Thanks Edward for your friendly permision
    Edward Tomasz Napierala <trasz@FreeBSD.org>.
    *********************************************************************/
    return 0;
  }
#endif

  // ----- main jack process method
  int gx_jack_process (jack_nframes_t nframes, void *arg)
  {
    AVOIDDENORMALS;

    // retrieve buffers at jack ports
    for (int i = 0; i < 1; i++)
      gInChannel[i] = (float *)jack_port_get_buffer(input_ports[i], nframes);

    for (int i = 0; i < gNumOutChans; i++)
      gOutChannel[i] = (float *)jack_port_get_buffer(output_ports[i], nframes);

    // guitarix DSP computing
    GxEngine::instance()->compute(nframes, gInChannel, gOutChannel);

    if (gx_jconv::jconv_is_running) {
     for (int i = 1; i < gNumInChans; i++)
      gInChannel[i] = (float *)jack_port_get_buffer(input_ports[i], nframes);
    GxEngine::instance()->get_jconv_output( gInChannel, gOutChannel,nframes);
    }
    // ready to go for e.g. level display
    gx_engine::buffers_ready = true;

    // midi processing
#ifdef USE_RINGBUFFER
    gx_jack_midi_process_ringbuffer(nframes, 0);
#else
    gx_jack_midi_process(nframes, 0);
#endif

    // some info display
    if (gx_gui::showwave == 1)
      time_is =  jack_frame_time (client);

    return 0;
  }

  //----- read the result from the latency change warning widget
  void gx_confirm_latency_change()
  {
    change_latency = kChangeLatency;
  }

  void gx_cancel_latency_change()
  {
    change_latency = kKeepLatency;
  }


  //----- fetch available jack ports other than guitarix ports
  void gx_jack_portreg_callback(jack_port_id_t pid, int reg, void* arg)
  {
    // just to be safe
    if (!client) return;

    // retrieve port
    jack_port_t* port = jack_port_by_id(client, pid);

    // if it is our own, get out of here
    if (jack_port_is_mine(client, port)) return;

    // OK, let's get to it
    const char* name  = jack_port_name(port);
    const char* type  = jack_port_type(port);
    const int   flags = jack_port_flags(port);

    // get GUI to act upon the stuff
    gx_gui::GxMainInterface* gui = gx_gui::GxMainInterface::instance();
    switch(reg)
    {

    case 0: gui->deleteJackPortItem(name); break;
    case 1: gui->addJackPortItem(name, type, flags); break;

    default: break;
    }
  }

  //----- client registration callback
  void gx_jack_clientreg_callback(const char* clname, int reg, void* arg)
  {
    // just to be safe
    if (!client) return;

    // if it is outselves, get out of here
    if (client_name == clname) return;

    client_out_graph = "";
    client_in_graph = "";

    // get GUI to act upon the stuff
    // see gx_gui::gx_monitor_jack_clients
    switch(reg)
    {
    case 0: client_out_graph = clname; break;
    case 1: client_in_graph = clname; break;
    default: break;
    }
  }

  //---- GTK callback from port item for port connection
  void gx_jack_port_connect(GtkWidget* wd, gpointer data)
  {
    GtkCheckMenuItem* item = GTK_CHECK_MENU_ITEM(wd);

    // don't bother if not a jack client
    if (!client)
    {
      gtk_check_menu_item_set_active(item,  FALSE);
      return;
    }

    // check client port name
    string wname = gtk_widget_get_name(wd);
    if (wname.empty())
    {
      gtk_check_menu_item_set_active(item,  FALSE);
      return;
    }

    // configure connection
    // Note: for some reason, jack_connect is not symmetric and one has to
    // connect out-to-in, jack_connect() does not take in-to-out.
    // weird but that's how it is, so we must know if we deal with
    // an input or output port (yeah, it sucks a bit).

    gint gxport_type = GPOINTER_TO_INT(data);

    // check we do have a proper gxport_type
    if (gxport_type < kAudioInput || gxport_type > kAudioOutput2)
      return;

    string port1;
    string port2;

    jack_port_t* ports[] = {
      input_ports [0],
      output_ports[0],
      output_ports[1]
    };


    switch (gxport_type)
    {
    case kAudioInput:
      port1  = wname;
      port2  = client_name + string(":") + gx_port_names[kAudioInput];
      break;

    default:
      port1 = client_name + string(":") + gx_port_names[gxport_type];
      port2 = wname;
      break;
    }

    // check direct connection
    int nconn = jack_port_connected_to(ports[gxport_type], wname.c_str());
    if (gtk_check_menu_item_get_active(item) == TRUE)
    {
      if (nconn == 0)
      {
	int ret = jack_connect(client, port1.c_str(), port2.c_str());

	switch (ret)
        {
	case 0:
	  gx_print_info("Jack Port Connect",
			port1 + string(" and  ") + port2
			+ string(" are now _CONNECTED_"));
	  break;

	case EEXIST: // already connected
	  gx_print_info("Jack Port Connect",
			port1 + string(" and  ") + port2 +
			string(" ALREADY connected"));
	  break;

	default:
	  gx_print_warning("Jack Port Connect",
			   string("Could NOT CONNECT ") +
			   port1 + string(" and  ") + port2);

	  gtk_check_menu_item_set_active(item,  FALSE);
	  break;
	}
      }
    }
    else
    {
      if (nconn > 0)
      {
	int ret = jack_disconnect(client, port1.c_str(), port2.c_str());

	switch (ret)
        {
	case 0:
	  gx_print_info("Jack Port Connect",
			port1 + string(" and  ") + port2
			+ string(" are now _DISCONNECTED_"));
	  break;

	default:
	  gx_print_warning("Jack Port Disconnect",
			   string("Could NOT DISCONNECT ") +
			   port1 + string(" and  ") + port2);
	  gtk_check_menu_item_set_active(item,  TRUE);
	  break;
	}
      }
    }
  }

} /* end of gx_jack namespace */

