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
 *  This is the gx_head interface to the jackd audio / midi server
 *
 * --------------------------------------------------------------------------
 */

#include "guitarix.h"           // NOLINT

#include <errno.h>              // NOLINT
#include <jack/statistics.h>    // NOLINT
#include <jack/jack.h>          // NOLINT
#include <glibmm/i18n.h>        // NOLINT

#ifdef HAVE_JACK_SESSION
#include <jack/session.h>      // NOLINT
#endif

#include <cstring>             // NOLINT
#include <string>              // NOLINT
#include <fstream>             // NOLINT
#include <list>                // NOLINT


namespace gx_jack {

sem_t jack_sync_sem;

GxJack gxjack;

// ----- pop up a dialog for starting jack
bool gx_jack_init(const string *optvar) {
    jack_status_t jackstat;
    client_name = "gx_head_amp";
    client_insert_name = "gx_head_fx";
    client_instance = "gx_head";
    int jack_is_fresh = 0;

    AVOIDDENORMALS;

    sem_init(&jack_sync_sem, 0, 0);

    // init the pointer to the jackbuffer
    for (int i = 0; i < gxjack.nOPorts; i++) gxjack.output_ports[i] = 0;
    for (int i = 0; i < gxjack.nIPorts; i++) gxjack.input_ports[i] = 0;

#ifdef HAVE_JACK_SESSION
    // try to open jack gxjack.client
    if (!optvar[JACK_UUID].empty()) {

        gxjack.client = jack_client_open(client_name.c_str(),
                        jack_options_t(JackNoStartServer | JackSessionID),
                        &jackstat, optvar[JACK_UUID].c_str());
    } else {
        gxjack.client = jack_client_open(client_name.c_str(), JackNoStartServer, &jackstat);
    }
#else
    gxjack.client = jack_client_open(client_name.c_str(), JackNoStartServer, &jackstat);
#endif
    // ----- only start the insert gxjack.client when the amp gxjack.client is true
    if (gxjack.client) {
        gxjack.client_insert = jack_client_open(client_insert_name.c_str(),
                               JackNoStartServer, &jackstat);
    }
    if (gxjack.client == 0) {
        // skip useless message
        // gx_print_warning("Jack Init", "not yet a jack gxjack.client");

        // if jackd is running, let's call ourselves again
        if (gx_system::gx_system_call("pgrep", "jackd", true) == gx_system::SYSTEM_OK) {
            gx_system::gx_print_warning(_("Jack Init"),
                       _("jackd OK, trying to be a gxjack.client"));
            usleep(500000);
            return gx_jack_init( optvar );
        }

        // start a dialog
        if (gx_start_jack_dialog()) {
            usleep(500000);
            // so let's try to be a jack gxjack.client again
            gxjack.client = jack_client_open(client_name.c_str(), JackNoStartServer,
                                              &jackstat);
            gxjack.client_insert = jack_client_open(client_insert_name.c_str(),
                                   JackNoStartServer, &jackstat);

            if (!gxjack.client) {
                gx_system::gx_print_error(_("main"),
                               string(_("I really tried to get jack up and running, sorry ... ")));
                return false;
            }
            jack_is_fresh = 1;
        } else {   // we give up
            gx_system::gx_print_error(_("main"),
                           string(_("Ignoring jackd ...")));
            return false;
        }
    }

    // ----------------------------------
    jack_is_down = false;
    gxjack.is_rt = jack_is_realtime(gxjack.client);

    // it is maybe not the 1st gx_head instance ?
    if (jackstat & JackNameNotUnique) {
        client_name = jack_get_client_name(gxjack.client);
        client_insert_name = jack_get_client_name(gxjack.client_insert);
        assert(client_name.substr(0, 11) == "gx_head_amp");
        client_instance = client_name.substr(0, 8) + client_name.substr(12);
    }

    gxjack.jack_sr = jack_get_sample_rate(gxjack.client); // jack sample rate
    ostringstream s;
    s << _("The jack sample rate is ") << gxjack.jack_sr << _("/sec");
    gx_system::gx_print_info(_("Jack init"), s.str().c_str());

    gxjack.jack_bs = jack_get_buffer_size(gxjack.client); // jack buffer size
    s.str("");
    s << _("The jack buffer size is ") << gxjack.jack_bs << _("/frames ... ");

    gx_system::gx_print_info(_("Jack init"), s.str());


    if (gx_gui::gw.fWindow) {
     string window_name = "gx_head";
        gtk_window_set_title(GTK_WINDOW(gx_gui::gw.fWindow), window_name.c_str());
    }
    if (jack_is_fresh) sleep(8);
    return true;
}

struct PortConnData {
    string name_a, name_b;
    int connect;
    PortConnData(string a, string b, int conn): name_a(a), name_b(b), connect(conn) {}
};

static gboolean gx_jack_portconn_helper(gpointer data) {
    PortConnData *pc = reinterpret_cast<PortConnData*>(data);
    if (gx_portmap::PortMapWindow::instance) {
        gx_portmap::PortMapWindow::instance->connection_changed(pc->name_a, pc->name_b,
                                             pc->connect);
    }
    delete pc;
    return FALSE;
}

static void gx_jack_portconn_callback(jack_port_id_t a, jack_port_id_t b, int connect, void*) {
    if (!gxjack.client) {
        return;
    }
    jack_port_t* port_a = jack_port_by_id(gxjack.client, a);
    jack_port_t* port_b = jack_port_by_id(gxjack.client, b);
    if (!port_a || !port_b) {
        return;
    }
    gtk_idle_add(gx_jack_portconn_helper,
                 new PortConnData(jack_port_name(port_a), jack_port_name(port_b),
                                  connect));
    // check if we are connected
    const char** port = jack_port_get_connections(gxjack.input_ports[0]);
    if (port) { // might be 0 (e.g. due to race conditions)

        NO_CONNECTION = 0;
        free(port);
    } else {
        NO_CONNECTION = 1;
    }
}


// ----- set gxjack.client callbacks and activate gxjack.client
// Note: to be called after gx_engine::gx_engine_init()
void gx_jack_callbacks_and_activate() {
    // ----- set the jack callbacks
    jack_set_xrun_callback(gxjack.client, gx_jack_xrun_callback, NULL);
    jack_set_sample_rate_callback(gxjack.client, gx_jack_srate_callback, 0);
    jack_on_shutdown(gxjack.client, gx_jack_shutdown_callback, NULL);
    jack_set_buffer_size_callback(gxjack.client, gx_jack_buffersize_callback, 0);
    jack_set_process_callback(gxjack.client, gx_jack_process, 0);
    jack_set_process_callback(gxjack.client_insert, gx_jack_insert_process, 0);
    jack_set_port_registration_callback(gxjack.client, gx_jack_portreg_callback, 0);
    jack_set_port_connect_callback(gxjack.client, gx_jack_portconn_callback, 0);
#ifdef HAVE_JACK_SESSION
    if (jack_set_session_callback) {
        jack_set_session_callback(gxjack.client, gx_jack_session_callback, 0);
    }
#endif

    // ----- register the midi input channel
    gxjack.midi_input_port =
        jack_port_register(gxjack.client, "midi_in_1", JACK_DEFAULT_MIDI_TYPE,
                           JackPortIsInput, 0);

    // ----- register the input channel
    gxjack.input_ports[0] =
        jack_port_register(gxjack.client, "in_0", JACK_DEFAULT_AUDIO_TYPE,
                           JackPortIsInput, 0);
    gxjack.input_ports[1] =
        jack_port_register(gxjack.client_insert, "in_0", JACK_DEFAULT_AUDIO_TYPE,
                           JackPortIsInput, 0);

    // ----- register the midi output channel
    gxjack.midi_output_ports =
        jack_port_register(gxjack.client, "midi_out_1", JACK_DEFAULT_MIDI_TYPE,
                           JackPortIsOutput, 0);

    // ----- register the audio output channels
    for (int i = 0; i < 1; i++) {
        ostringstream buf;
        buf <<  "out_" << i;
        gxjack.output_ports[i] =
            jack_port_register(gxjack.client, buf.str().c_str(),
                               JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
    }
    // ----- register the audio fx output channels
    for (int i = 2; i < 4; i++) {
        ostringstream buf;
        buf <<  "out_" << i-2;
    gxjack.output_ports[i] =
            jack_port_register(gxjack.client_insert, buf.str().c_str(),
                               JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
    }

    // ----- ready to go
    if (jack_activate(gxjack.client)) {
        gx_system::gx_print_error(_("Jack Activation"),
                       string(_("Can't activate JACK gxjack.client")));
        gx_system::gx_clean_exit(NULL, NULL);
    }
    if (jack_activate(gxjack.client_insert)) {
        gx_system::gx_print_error(_("Jack Activation"),
                       string(_("Can't activate JACK gxjack.client")));
        gx_system::gx_clean_exit(NULL, NULL);
    }
}

static gboolean gx_engine_restart(gpointer data) {
    usleep(5);
    gx_engine::checky = gx_engine::kEngineOn;
    return false;
}

// ----- connect ports if we know them
void gx_jack_init_port_connection(const string* optvar) {
    // set engine off for one GTK thread cycle to avoid Xrun at startup
    gx_gui::g_threads[4] = g_idle_add_full(G_PRIORITY_HIGH_IDLE+20, gx_engine_restart,
                                           NULL, NULL);
    gx_engine::checky = gx_engine::kEngineOff;

    // set autoconnect capture to user capture port
    if (!optvar[JACK_INP].empty()) {
        jack_connect(gxjack.client, optvar[JACK_INP].c_str(),
                     jack_port_name(gxjack.input_ports[0]));
    } else {
        list<string>& l = gx_system::jack_connection_lists[kAudioInput];
        for (list<string>::iterator i = l.begin(); i != l.end(); i++) {
            jack_connect(gxjack.client, i->c_str(), jack_port_name(gxjack.input_ports[0]));
        }
    }

    // set autoconnect midi to user midi port
    if (gxjack.midi_input_port && !optvar[JACK_MIDI].empty()) {
        jack_connect(gxjack.client, optvar[JACK_MIDI].c_str(),
                     jack_port_name(gxjack.midi_input_port));
    } else {
        list<string>& l = gx_system::jack_connection_lists[kMidiInput];
        for (list<string>::iterator i = l.begin(); i != l.end(); i++) {
            jack_connect(gxjack.client, i->c_str(), jack_port_name(gxjack.midi_input_port));
        }
    }

    // set autoconnect to user playback ports
    if (optvar[JACK_OUT1].empty() && optvar[JACK_OUT2].empty()) {
        list<string>& l1 = gx_system::jack_connection_lists[kAudioOutput1];
        for (list<string>::iterator i = l1.begin(); i != l1.end(); i++) {
            jack_connect(gxjack.client_insert, jack_port_name(gxjack.output_ports[2]), i->c_str());
        }
        list<string>& l2 = gx_system::jack_connection_lists[kAudioOutput2];
        for (list<string>::iterator i = l2.begin(); i != l2.end(); i++) {
            jack_connect(gxjack.client_insert, jack_port_name(gxjack.output_ports[3]), i->c_str());
        }
    } else {
        int idx = JACK_OUT1;
        for (int i = 2; i < 4; i++) {
            if (!optvar[idx].empty()) {
                jack_connect(gxjack.client_insert,
                             jack_port_name(gxjack.output_ports[i]), optvar[idx].c_str());
            }
            idx++;
        }
    }

    // autoconnect midi output port
    list<string>& lmo = gx_system::jack_connection_lists[kMidiOutput];
    for (list<string>::iterator i = lmo.begin(); i != lmo.end(); i++) {
        jack_connect(gxjack.client, jack_port_name(gxjack.midi_output_ports), i->c_str());
    }

    // autoconnect to insert ports
    list<string>& lins_in = gx_system::jack_connection_lists[kAudioInsertIn];
    list<string>& lins_out = gx_system::jack_connection_lists[kAudioInsertOut];
    bool ifound = false, ofound = false;
    for (list<string>::iterator i = lins_in.begin(); i != lins_in.end(); i++) {
        int rc = jack_connect(gxjack.client_insert, i->c_str(),
                              jack_port_name(gxjack.input_ports[1]));
        if (rc == 0 || rc == EEXIST) {
            ifound = true;
        }
    }
    for (list<string>::iterator i = lins_out.begin(); i != lins_out.end(); i++) {
        int rc = jack_connect(gxjack.client, jack_port_name(gxjack.output_ports[0]), i->c_str());
        if (rc == 0 || rc == EEXIST) {
            ofound = true;
        }
    }
    if (!ifound || !ofound) {
        jack_connect(gxjack.client_insert, jack_port_name(gxjack.output_ports[0]),
                    (client_insert_name+":in_0").c_str());
    }
}

// ----- pop up a dialog for starting jack
bool gx_start_jack_dialog() {
    // --- run dialog and check response
    const guint nchoices    = 3;

    const char* labels[]    = {
            _("Start Jack"), _("Ignore Jack"), _("Exit")
        };

    const gint  responses[] = {
            GTK_RESPONSE_YES, GTK_RESPONSE_NO, GTK_RESPONSE_CANCEL
        };

    gint response =
        gx_gui::gx_nchoice_dialog_without_entry(
            _(" Jack Starter "),
            _("\n                        WARNING                        \n\n"
            "   The jack server is not currently running\n"
            "   You can choose to activate it or terminate gx_head   \n\n"
            "       1) activate jack   \n"
            "       2) ignore jack, start gx_head anyway   \n"
            "       3) exit gx_head   \n"),
            nchoices,
            labels,
            responses,
            GTK_RESPONSE_YES);

    // we are cancelling
    bool retstat = false;

    switch (response) {
    case GTK_RESPONSE_NO:
        jack_is_down = true;
        break;

    case GTK_RESPONSE_CANCEL:
        gx_system::gx_abort(NULL);
        break;

    default:
    case GTK_RESPONSE_YES:
        retstat = gx_start_jack(NULL);
        break;
    }

    // start jack
    return retstat;
}


// ----start jack if possible
bool gx_start_jack(void* arg) {
    // first, let's try via qjackctl
    if (gx_system::gx_system_call("which", "qjackctl", true) == gx_system::SYSTEM_OK) {
        if (gx_system::gx_system_call("qjackctl", "--start", true, true) == gx_system::SYSTEM_OK) {
            sleep(5);

            // let's check it is really running
            if (gx_system::gx_system_call("pgrep", "jackd", true) == gx_system::SYSTEM_OK) {
                return true;
            }
        }
    }

    // qjackctl not found or not started, let's try .jackdrc
    string jackdrc = "$HOME/.jackdrc";
    if (gx_system::gx_system_call("ls", jackdrc.c_str(), true, false) == gx_system::SYSTEM_OK) {
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
            if (gx_system::gx_system_call(cmdline.c_str(), "", true, true) ==
                gx_system::SYSTEM_OK) {

                sleep(2);

                // let's check it is really running
                if (gx_system::gx_system_call("pgrep", "jackd", true) == gx_system::SYSTEM_OK) {
                    return true;
                }
            }
    }

    return false;
}

static gboolean gx_ports_refresh(gpointer data) {
        // reload ports for portmap widget when needed
    if (gx_portmap::PortMapWindow::instance) {
        gx_portmap::PortMapWindow::instance->refresh();
    }
    return false;
}

// ---- Jack server connection / disconnection
void gx_jack_connection(GtkCheckMenuItem *menuitem, gpointer arg) {
    if (gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(menuitem)) == TRUE) {
        if (!gxjack.client) {
            string optvar[NUM_SHELL_VAR];
            gx_system::gx_assign_shell_var(gx_system::shell_var_name[JACK_INP], optvar[JACK_INP]);
            gx_system::gx_assign_shell_var(gx_system::shell_var_name[JACK_MIDI], optvar[JACK_MIDI]);
            gx_system::gx_assign_shell_var(gx_system::shell_var_name[JACK_OUT1], optvar[JACK_OUT1]);
            gx_system::gx_assign_shell_var(gx_system::shell_var_name[JACK_OUT2], optvar[JACK_OUT2]);
            gx_system::gx_assign_shell_var(gx_system::shell_var_name[JACK_UUID], optvar[JACK_UUID]);

            if (gx_jack_init(optvar)) {

                // initialize gx_head engine if necessary
                if (!gx_engine::initialized) {
                    gx_engine::gx_engine_init(optvar);
                }
                gx_jack_callbacks_and_activate();
                gx_jack_init_port_connection(optvar);

                // refresh latency check menu
                gx_gui::GxMainInterface* gui = gx_gui::GxMainInterface::instance();
                GtkWidget* wd = gui->getJackLatencyItem(gx_jack::gxjack.jack_bs);
                if (wd) {
                    gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(wd), TRUE);
                }
                if (!gx_engine::pt_initialized) {
                    sleep(5);
                    // -------- pitch tracker (needs jack thread running) -------------
                    gx_engine::pitch_tracker.init();
                }
            }
        }

        if (gxjack.client) {
            if (gx_gui::gw.gx_jackd_on_image) {
                gtk_widget_show(gx_gui::gw.gx_jackd_on_image);
                gtk_widget_hide(gx_gui::gw.gx_jackd_off_image);
            }
            jack_is_exit = false;

            gx_system::gx_print_info(_("Jack Server"), _("Connected to Jack Server"));
        }
    } else {
        gx_jack_cleanup();

        // we bring down jack capture and meterbridge
        gx_child_process::Meterbridge::stop();
        gx_child_process::JackCapture::stop();

        if (gx_gui::gw.gx_jackd_on_image) {
            gtk_widget_hide(gx_gui::gw.gx_jackd_on_image);
            gtk_widget_show(gx_gui::gw.gx_jackd_off_image);
        }

        // engine buffers no longer ready
        gx_engine::buffers_ready = false;

        gx_system::gx_print_warning(_("Jack Server"), _("Disconnected from Jack Server"));
    }
    g_idle_add(gx_ports_refresh, NULL);
}

// ----jack latency change
void gx_set_jack_buffer_size(GtkCheckMenuItem* menuitem, gpointer arg) {
    // are we a proper jack gxjack.client ?
    if (!gxjack.client) {
        gx_system::gx_print_error(
            _("Jack Buffer Size setting"),
            _("we are not a jack gxjack.client, server may be down")
            );

        return;
    }

    // ----- if check button triggered menually

    // let's avoid triggering the jack server on "inactive"
    if (gtk_check_menu_item_get_active(menuitem) == false) {
        return;
    }
    // requested latency
    jack_nframes_t buf_size = (jack_nframes_t)GPOINTER_TO_INT(arg);

    // if the actual buffer size is the same, no need further action
    if (buf_size == jack_get_buffer_size(gxjack.client)) {
        return;
    }

    // first time useage warning
    GxJackLatencyChange change_latency = kChangeLatency;

    // if user still wants to be given a choice, let's trigger dialog
    if (gx_engine::fwarn == 0.0)
        change_latency = (GxJackLatencyChange)gx_gui::gx_wait_latency_warn();

    // let's see
    if (change_latency == kChangeLatency) {
        // let's resize the buffer
        if (jack_set_buffer_size(gxjack.client, buf_size) != 0)
            gx_system::gx_print_warning(_("Setting Jack Buffer Size"),
                             _("Could not change latency"));
    } else { // restore latency status
        // refresh latency check menu
        gx_gui::GxMainInterface* gui = gx_gui::GxMainInterface::instance();
        GtkWidget* wd = gui->getJackLatencyItem(gxjack.jack_bs);
        if (wd) gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(wd), TRUE);
    }
    gx_system::gx_print_info(_("Jack Buffer Size"),
                  string(_("latency is ")) +
                  gx_system::gx_i2a(jack_get_buffer_size(gxjack.client)));
}

// -----Function that cleans the jack stuff on shutdown
void gx_jack_cleanup() {
    if (gxjack.client && !jack_is_down) {
        jack_is_exit = true;
        // disable input ports
        jack_port_unregister(gxjack.client, gxjack.input_ports[0]);
        jack_port_unregister(gxjack.client_insert, gxjack.input_ports[1]);
        if (gxjack.midi_input_port != NULL) {
            jack_port_unregister(gxjack.client, gxjack.midi_input_port);
        }
        for (int i = 0; i < 1; i++) {
            jack_port_unregister(gxjack.client, gxjack.output_ports[i]);
        }
        for (int i = 2; i < 4; i++) {
            jack_port_unregister(gxjack.client_insert, gxjack.output_ports[i]);
        }
        if (gxjack.midi_output_ports != NULL) {
            jack_port_unregister(gxjack.client, gxjack.midi_output_ports);
        }

        jack_deactivate(gxjack.client);
        jack_client_close(gxjack.client);
        gxjack.client = NULL;
        jack_deactivate(gxjack.client_insert);
        jack_client_close(gxjack.client_insert);
        gxjack.client_insert = NULL;
    }
}

// ----jack sample rate change callback
int gx_jack_srate_callback(jack_nframes_t frames, void* arg) {
    /* Note: just reporting log for now  */

    /*  ostringstream s;
        s << " jack sample rate changed to " << frames;
        gx_print_warning("Jack sample rate", s.str()); */

    return 0;
}

// ---- jack shutdown callback in case jackd shuts down on us
void gx_jack_shutdown_callback(void *arg) {
    // global var to let all know that jack is down
    jack_is_down = true;
    // helper funktion to start gx_survive_jack_shutdown thread
    gx_gui::gx_jack_is_down();
}

// ---- jack xrun callback
int gx_jack_xrun_callback(void* arg) {
    gxjack.xdel = jack_get_xrun_delayed_usecs(gxjack.client);
    gx_gui::gx_jack_report_xrun();
    return 0;
}

// ---- jack buffer size change callback
int gx_jack_buffersize_callback(jack_nframes_t nframes, void* arg) {
    gx_engine::GxEngineState estate = gx_engine::checky;

    // turn off engine
    // Note: simply changing checky is enough to "stop" processing
    // incoming jack buffers. The mydsp::compute method is owned by
    // the jack audio thread. It always runs as long as jack runs
    // independently of the non-RT GUI thread. The value of
    // checky is checked at each jack cycle in mydsp::compute
    // so changing it here affects the behavior of mydsp::compute
    // immediately during the jack_processing of jack cycles.

    if (estate != gx_engine::kEngineOff)
        gx_engine::checky = gx_engine::kEngineOff;

    gxjack.jack_bs = nframes;


    if (gx_engine::checkfreq)  delete[] gx_engine::checkfreq;
    if (gx_engine::get_frame)  delete[] gx_engine::get_frame;
    if (gx_engine::get_frame1)  delete[] gx_engine::get_frame1;
    if (gx_engine::oversample) delete[] gx_engine::oversample;
    if (gx_engine::result) delete[] gx_engine::result;

    gx_engine::get_frame = new float[gxjack.jack_bs];
    (void)memset(gx_engine::get_frame, 0, sizeof(float)*gxjack.jack_bs);

    gx_engine::get_frame1 = new float[gxjack.jack_bs];
    (void)memset(gx_engine::get_frame1, 0, sizeof(float)*gxjack.jack_bs);

    gx_engine::checkfreq = new float[gxjack.jack_bs];
    (void)memset(gx_engine::checkfreq, 0, sizeof(float)*gxjack.jack_bs);

    gx_engine::oversample = new float[gxjack.jack_bs*MAX_UPSAMPLE];
    (void)memset(gx_engine::oversample, 0, sizeof(float)*gxjack.jack_bs*MAX_UPSAMPLE);

    gx_engine::result = new float[gxjack.jack_bs+46];
    (void)memset(gx_engine::result, 0, sizeof(float)*gxjack.jack_bs+46);

    gx_gui::GxMainInterface::instance()->set_waveview_buffer();
    if (gx_engine::cab_conv.is_runnable()) {
        gx_engine::cab_conv.set_not_runnable();
        Glib::signal_idle().connect(
            sigc::bind_return(sigc::ptr_fun(gx_gui::cab_conv_restart), false));
    }
    if (gx_engine::contrast_conv.is_runnable()) {
        gx_engine::contrast_conv.set_not_runnable();
        Glib::signal_idle().connect(
            sigc::bind_return(sigc::ptr_fun(gx_gui::contrast_conv_restart), false));
    }
    if (gx_engine::conv.is_runnable()) {
        gx_engine::conv.set_not_runnable();
        Glib::signal_idle().connect(
            sigc::bind_return(sigc::ptr_fun(gx_gui::conv_restart), false));
    }

    // restore previous state
    gx_engine::checky = estate;
    // return 0 to jack
    return 0;
}

// ---- jack midi control input processing
int gx_jack_midi_input_process(jack_nframes_t nframes, void *arg) {
    if (gxjack.midi_input_port != NULL) {
        midi_input_port_buf =  jack_port_get_buffer(gxjack.midi_input_port, nframes);
        gx_engine::compute_midi_in(midi_input_port_buf);
    }
    return 0;
}

// ---- jack midi processing

int gx_jack_midi_process(jack_nframes_t nframes, void *arg) {
    if (gxjack.midi_output_ports != NULL) {
        AVOIDDENORMALS;

        midi_port_buf =  jack_port_get_buffer(gxjack.midi_output_ports, nframes);
        jack_midi_clear_buffer(midi_port_buf);

        if ((gx_engine::isMidiOn() == true) || (gx_gui::showwave == 1))
            gxjack.jcpu_load = jack_cpu_load(gxjack.client);

        gx_engine::compute_midi(nframes);
    }
    return 0;
}

// ----- main jack process method
int gx_jack_process(jack_nframes_t nframes, void *arg) {
    int val;
    gx_system::measure_start();
    if (sem_getvalue(&jack_sync_sem, &val) == 0 && val == 0) {
        sem_post(&jack_sync_sem);
    }
    if (!jack_is_exit) {
        AVOIDDENORMALS;

        // retrieve buffers at jack ports
        float *input = reinterpret_cast<float *>
                       (jack_port_get_buffer(gxjack.input_ports[0], nframes));
        float *output0 = reinterpret_cast<float *>
                        (jack_port_get_buffer(gxjack.output_ports[0], nframes));

        // gx_head DSP computing
        gx_engine::compute(nframes, input, output0);

        // ready to go for e.g. level display
        gx_engine::buffers_ready = true;

        // midi input processing
        gx_jack_midi_input_process(nframes, 0);

        // midi processing

        gx_jack_midi_process(nframes, 0);


        // some info display
        if (gx_gui::showwave == 1) {
            gxjack.time_is =  jack_frame_time(gxjack.client);
        }
    } else {
        gx_engine::buffers_ready = false;
    }
    // measure_stop();
    return 0;
}

// ----- main jack process method
int gx_jack_insert_process(jack_nframes_t nframes, void *arg) {
    // measure_start();
    if (!jack_is_exit) {
        AVOIDDENORMALS;

        float *input1 = reinterpret_cast<float *>
                        (jack_port_get_buffer(gxjack.input_ports[1], nframes));
        float *output2 = reinterpret_cast<float *>
                         (jack_port_get_buffer(gxjack.output_ports[2], nframes));
        float *output3 = reinterpret_cast<float *>
                         (jack_port_get_buffer(gxjack.output_ports[3], nframes));
        // gx_head DSP computing
        gx_engine::compute_insert(nframes, input1, output2, output3);
    }
    gx_system::measure_stop();
    return 0;
}

struct PortRegData {
    string name;
    const char *tp;
    int jackflags;
    int reg;
    PortRegData(string nm, const char *t, int flags, int r): name(nm), tp(t),
                jackflags(flags), reg(r) {}
};

static gboolean gx_jack_portreg_helper(gpointer data) {
    if (gx_portmap::PortMapWindow::instance) {
        gx_portmap::PortMapWindow::instance->refresh();
    }
    // delete pm;
    return FALSE;
}

// ----- fetch available jack ports other than gx_head ports
void gx_jack_portreg_callback(jack_port_id_t pid, int reg, void* arg) {
    if (!gxjack.client) {
        return;
    }
    jack_port_t* port = jack_port_by_id(gxjack.client, pid);
    if (!port || jack_port_is_mine(gxjack.client, port)) {
        return;
    }
    gtk_idle_add(gx_jack_portreg_helper,
                 new PortRegData(jack_port_name(port), jack_port_type(port),
                                 jack_port_flags(port), reg));
}

#ifdef HAVE_JACK_SESSION
static int gx_jack_session_callback_helper(gpointer data) {
    jack_session_event_t *event = reinterpret_cast<jack_session_event_t *>(data);
    string fname(event->session_dir);
    fname += "gx_head.state";
    string cmd("guitarix -U ");
    cmd += event->client_uuid;
    cmd += " -f ${SESSION_DIR}gx_head.state";

    gx_system::saveStateToFile(fname);

    event->command_line = strdup(cmd.c_str());

    jack_session_reply(gxjack.client, event);

    if (event->type == JackSessionSaveAndQuit) {
        gx_system::is_session = true;
        gx_system::gx_clean_exit(NULL, NULL);
        jack_session_event_free(event);
        exit(0);
    }
    jack_session_event_free(event);
    return 0;
}

void gx_jack_session_callback(jack_session_event_t *event, void *arg) {
    gtk_idle_add(gx_jack_session_callback_helper, reinterpret_cast<void *>(event));
}
#endif

} /* end of gx_jack namespace */

