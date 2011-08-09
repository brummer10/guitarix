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
 * ---------------------------------------------------------------------------
 *
 *    This is the gx_head system interface
 *
 * ----------------------------------------------------------------------------
 */

#include "guitarix.h"               // NOLINT

#include <sys/stat.h>               // NOLINT
#include <jack/jack.h>              // NOLINT
#include <glibmm/optioncontext.h>   // NOLINT
#include <glibmm/i18n.h>            // NOLINT

#include <cstring>                  // NOLINT
#include <string>                   // NOLINT
#include <fstream>                  // NOLINT
#include <iostream>                 // NOLINT
#include <iomanip>                  // NOLINT
#include <list>                     // NOLINT
#include <vector>                   // NOLINT

namespace gx_system {

SystemVars sysvar;
/****************************************************************
 ** Measuring times (only when debugging)
 */

#ifndef NDEBUG

/* return time difference in ns, fail if > sec (doesn't fit int 32 bit int) */
int Measure::ts_diff(struct timespec ts1, struct timespec ts2) {
    time_t df = ts1.tv_sec - ts2.tv_sec;
    if (abs(df) > 2) {
        return -1; // failed
    }
    return df * 1000000000 + (ts1.tv_nsec - ts2.tv_nsec);
}

void Measure::print_accum(Accum& accum, const char* prefix, bool verbose, int total) {
    cout << prefix << "mean: " << fixed << setprecision(4) << ns2ms(accum.mean());
    if (total > 0) {
        cout << " (" << setprecision(2) << 100.0*accum.mean()/static_cast<float>(total) << "%)";
    }
    cout << ", min: " << setprecision(4) << ns2ms(accum.minimum())
         << ", max: " << ns2ms(accum.maximum());
    if (total > 0) {
        cout << " (" << setprecision(2) << 100.0*accum.maximum()/static_cast<float>(total) << "%)";
    }
    if (verbose) {
        cout << ", stddev: " << setprecision(4) << ns2ms(accum.stddev())
             << ", n: " << accum.count();
    }
    cout << endl;
}

void Measure::print(bool verbose) {
    if (verbose) {
        print_accum(period,   "period    ", verbose);
    }
    print_accum(duration, "duration  ", verbose, period.mean());
}

void MeasureThreadsafe::print(bool verbose) {
    Measure *p = pmeasure;
    Measure *pn;
    if (p == m) {
        pn = m+1;
    } else {
        pn = m;
    }
    g_atomic_pointer_set(&pmeasure, pn);
    p->print(verbose);
    p->reset();
}

MeasureThreadsafe measure;

static int print_measures(gpointer data) {
    bool verbose = GPOINTER_TO_INT(data);
    measure.print(verbose);
    return TRUE;
}

void add_time_measurement() {
    char *p = getenv("GUITARIX_MEASURE");
    if (!p) {
        return;
    }
    bool verbose = false;
    if (strcmp(p, "1") == 0) {
        verbose = true;
    }
    g_timeout_add(1000, print_measures, (gpointer)verbose);
}

#endif


/****************************************************************
 ** OS functions and helper
 */


const int SystemVars::SYSTEM_OK           = 0;
const char* SystemVars::gx_head_dir       = ".gx_head";
const char* SystemVars::jcapsetup_file    = "ja_ca_ssetrc";
const char* SystemVars::jcapfile_wavbase  = "gx_head_session";
const string SystemVars::gx_pixmap_dir    = string(GX_PIXMAPS_DIR) + "/";
const string SystemVars::gx_user_dir      = string(getenv("HOME")) + string("/")
                                             + string(gx_head_dir) + "/";
const char* SystemVars::shell_var_name[] = {
    "GUITARIX2JACK_INPUTS",
    "GUITARIX2JACK_OUTPUTS1",
    "GUITARIX2JACK_OUTPUTS2",
    "GUITARIX2JACK_MIDI",
    "GUITARIX_RC_STYLE",
    "GUITARIX2JACK_UUID",
    "GUITARIX_LOAD_FILE"
};

void SystemVars::sysvar_init() {
    is_session = false;
    gx_style_dir  = string(GX_STYLE_DIR1) + "/";
    gx_builder_dir = string(GX_BUILDER_DIR1) + "/";
}


// ---- retrieve and store the shell variable if not NULL
void gx_assign_shell_var(const char* name, string& value) {
    const char* val = getenv(name);
    value = (val != NULL) ? val : "";
}

// ---- OS signal handler -----
void gx_signal_handler(int sig) {
    // print out a warning
    if (sig == SIGABRT) {
        if(!gx_jack::gxjack.client) {
            printf(_(" SIGABRT . .received, try to clean up and exit. . .  \n"));
            exit(1);
        }
        else {
            gx_clean_exit(NULL, NULL);
        }
    }
    string msg = string(_("signal ")) + gx_i2a(sig) + _(" received, exiting ...");
    gx_print_warning(_("signal_handler"), msg);

    gx_clean_exit(NULL, NULL);
}

// ---- ladi signal handler -----
gboolean  gx_ladi_handler(gpointer) {
    gx_print_warning(_("signal_handler"), _("signal USR1 received, save settings"));

    saveStateToFile(sysvar.gx_user_dir + gx_jack::gxjack.client_instance + "_rc");
    return false;
}

bool terminal  = true; // make messages before main() appear on terminal

// ---- command line options
void gx_process_cmdline_options(int& argc, char**& argv, string* optvar) {
    // store shell variable content
    for (int i = 0; i < NUM_SHELL_VAR; i++) {
        gx_assign_shell_var(sysvar.shell_var_name[i], optvar[i]);
    }
    // initialize number of skins. We just count the number of rc files
    unsigned int n = gx_gui::gx_fetch_available_skins();
    if (n < 1) {
        gx_print_error(_("main"), string(_("number of skins is 0, aborting ...")));
        exit(1);
    }

    // ---- parse command line arguments
    bool version = false;
    Glib::OptionContext opt_context;
    opt_context.set_summary(
        "All parameters are optional. Examples:\n"
        "\tgx_head\n"
        "\tgx_head -r black -i system:capture_3\n"
        "\tgx_head -c -o system:playback_1 -o system:playback_2");
    Glib::OptionEntry opt_version;
    opt_version.set_short_name('v');
    opt_version.set_long_name("version");
    opt_version.set_description("Print version string and exit");
    Glib::OptionGroup main_group("bla1", "bla2", "bla3");
    main_group.add_entry(opt_version, version);
    opt_context.set_main_group(main_group);

    // GTK options: rc style (aka skin)
    string opskin("Style to use");

    vector<string>::iterator it;

    for (it = gx_gui::skin.skin_list.begin(); it != gx_gui::skin.skin_list.end(); it++) {
        opskin += ", '" + *it + "'";
    }

    bool clear = false;
    Glib::ustring rcset;
    Glib::OptionGroup optgroup_gtk(
        "gtk",
        "\033[1;32mGTK configuration options\033[0m",
        "\033[1;32mGTK configuration options\033[0m");
    Glib::OptionEntry opt_clear;
    opt_clear.set_short_name('c');
    opt_clear.set_long_name("clear");
    opt_clear.set_description("Use 'default' GTK style");
    Glib::OptionEntry opt_rcset;
    opt_rcset.set_short_name('r');
    opt_rcset.set_long_name("rcset");
    opt_rcset.set_description(opskin);
    opt_rcset.set_arg_description("STYLE");
    optgroup_gtk.add_entry(opt_clear, clear);
    optgroup_gtk.add_entry(opt_rcset, rcset);

    // JACK options: input and output ports
    Glib::ustring jack_input;
    Glib::ustring jack_midi;
    vector<Glib::ustring> jack_outputs;
    Glib::ustring jack_uuid;
    Glib::OptionGroup optgroup_jack(
        "jack",
        "\033[1;32mJACK configuration options\033[0m",
        "\033[1;32mJACK configuration options\033[0m");
    Glib::OptionEntry opt_jack_input;
    opt_jack_input.set_short_name('i');
    opt_jack_input.set_long_name("jack-input");
    opt_jack_input.set_description("Guitarix JACK input");
    opt_jack_input.set_arg_description("PORT");
    Glib::OptionEntry opt_jack_output;
    opt_jack_output.set_short_name('o');
    opt_jack_output.set_long_name("jack-output");
    opt_jack_output.set_description("Guitarix JACK outputs");
    opt_jack_output.set_arg_description("PORT");
    Glib::OptionEntry opt_jack_midi;
    opt_jack_midi.set_short_name('m');
    opt_jack_midi.set_long_name("jack-midi");
    opt_jack_midi.set_description("Guitarix JACK midi control");
    opt_jack_midi.set_arg_description("PORT");
    Glib::OptionEntry opt_jack_uuid;
    opt_jack_uuid.set_short_name('U');
    opt_jack_uuid.set_long_name("jack-uuid");
    opt_jack_uuid.set_description("JackSession ID");
    optgroup_jack.add_entry(opt_jack_input, jack_input);
    optgroup_jack.add_entry(opt_jack_output, jack_outputs);
    optgroup_jack.add_entry(opt_jack_midi, jack_midi);
    optgroup_jack.add_entry(opt_jack_uuid, jack_uuid);

    // FILE options
    string load_file;

    Glib::OptionGroup optgroup_file(
        "file",
        "\033[1;32mFile options\033[0m",
        "\033[1;32mFile options\033[0m");
    Glib::OptionEntry opt_load_file;
    opt_load_file.set_short_name('f');
    opt_load_file.set_long_name("load-file");
    opt_load_file.set_description(_("load state file on startup"));
    opt_load_file.set_arg_description("FILE");
    optgroup_file.add_entry_filename(opt_load_file, load_file);

    // DEBUG options
    string builder_dir;
    string style_dir;
    bool lterminal = false;
    Glib::OptionGroup optgroup_debug(
        "debug",
        "\033[1;32mDebug options\033[0m",
        "\033[1;32mDebug options\033[0m");
    Glib::OptionEntry opt_builder_dir;
    opt_builder_dir.set_short_name('B');
    opt_builder_dir.set_long_name("builder-dir");
    opt_builder_dir.set_description(_("directory from which .glade files are loaded"));
    opt_builder_dir.set_arg_description("DIR");
    optgroup_debug.add_entry_filename(opt_builder_dir, builder_dir);
    Glib::OptionEntry opt_style_dir;
    opt_style_dir.set_short_name('S');
    opt_style_dir.set_long_name("style-dir");
    opt_style_dir.set_description(_("directory with skin style definitions (.rc files)"));
    opt_style_dir.set_arg_description("DIR");
    optgroup_debug.add_entry_filename(opt_style_dir, style_dir);
    Glib::OptionEntry opt_log_terminal;
    opt_log_terminal.set_short_name('t');
    opt_log_terminal.set_long_name("log-terminal");
    opt_log_terminal.set_description(_("print log on terminal"));
    optgroup_debug.add_entry(opt_log_terminal, lterminal);

    // collecting all option groups
    opt_context.add_group(optgroup_gtk);
    opt_context.add_group(optgroup_jack);
    opt_context.add_group(optgroup_file);
    opt_context.add_group(optgroup_debug);

    // parsing command options
    try {
        opt_context.parse(argc, argv);
    } catch(Glib::OptionError ex) {
        gx_print_error(_("main"), _("Error in user options! ") + ex.what());
        exit(1);
    }


    // ----------- processing user options -----------

    terminal = lterminal;

    // *** display version if requested
    if (version) {
        std::cout << "Guitarix version \033[1;32m"
             << GX_VERSION << endl
             << "\033[0m   Copyright " << static_cast<char>(0x40) << " 2010 "
             << "Hermman Meyer - James Warden - Andreas Degert"
             << endl;
        exit(0);
    }

    // *** process GTK rc style
    bool previous_conflict = false;
    if (!rcset.empty()) {
        // retrieve user value
        string tmp = rcset;

        // check contradiction (clear and rcset cannot be used in the same call)
        if (clear) {
            gx_print_error(_("main"),
              string(_("-c and -r cannot be used together, defaulting to 'default' style")));
            tmp = "default";
            previous_conflict = true;
        }

        // if garbage, let's initialize to gx_head_default.rc
        guint s = 0;
        while (s < gx_gui::skin.skin_list.size()) {
            if (tmp == gx_gui::skin.skin_list[s])
                break;
            s++;
        }

        if (s == gx_gui::skin.skin_list.size()) {
            gx_print_error(_("main"),
                           string(_("rcset value is garbage, defaulting to 'default' style")));
            tmp = "default";
        }
        optvar[RC_STYLE] = tmp;

    // else, if no shell var defined for it, defaulting to gx_head_default.rc
    } else if (optvar[RC_STYLE].empty()) {
        optvar[RC_STYLE] = "default";
        // enable set last used skin
        gx_gui::skin.no_opt_skin = 1;
    }

    // *** process GTK clear
    if (clear) {
        // check contradiction (clear and rcset cannot be used in the same call)
        if (rcset != NULL && !previous_conflict)
            gx_print_error(_("main"),
              string(_("-c and -r cannot be used together, defaulting to 'default' style")));

        optvar[RC_STYLE] = "default";
    }

    // *** process builder_dir
    if (!builder_dir.empty()) {
        sysvar.gx_builder_dir = builder_dir;
        if (sysvar.gx_builder_dir[sysvar.gx_builder_dir.size()-1] != '/') {
            sysvar.gx_builder_dir += "/";
        }
    }

    // *** process style_dir
    if (!style_dir.empty()) {
        sysvar.gx_style_dir = style_dir;
        if (sysvar.gx_style_dir[sysvar.gx_style_dir.size()-1] != '/') {
            sysvar.gx_style_dir += "/";
        }
    }

    // *** process jack input
    if (!jack_input.empty()) {
        optvar[JACK_INP] = jack_input;
    }

    // *** process jack midi
    if (!jack_midi.empty()) {
        optvar[JACK_MIDI] = jack_midi;
    }

    optvar[JACK_UUID] = jack_uuid;

    // *** process jack outputs
    if (!jack_outputs.empty()) {
        int idx = JACK_OUT1;
        for (unsigned int i = 0; i < jack_outputs.size(); i++, idx++) {
            if (i >= 2) {
                gx_print_warning(_("main"),
                _("Warning --> provided more than 2 output ports, ignoring extra ports"));
                break;
            }
            optvar[idx] = jack_outputs[i];
        }
    } else {
        if (optvar[JACK_OUT1].empty()) {
            optvar[JACK_OUT1] = "";
        }
        if (optvar[JACK_OUT2].empty()) {
            optvar[JACK_OUT2] = "";
        }
    }

    optvar[LOAD_FILE] = load_file;

    sysvar.rcpath = sysvar.gx_style_dir + string("gx_head_") + optvar[RC_STYLE] + ".rc";
}

void gx_set_override_options(string* optvar) {
    if (!gx_gui::skin.no_opt_skin) {
        gx_gui::gx_actualize_skin_index(optvar[RC_STYLE]);
        gx_engine::audio.fskin = gx_gui::skin.last_skin = gx_gui::skin.gx_current_skin;
    }
}

struct logmsg {
    string msg;
    GxMsgType msgtype;
    logmsg(string m, GxMsgType t): msg(m), msgtype(t) {}
};

// ---- log message handler
void gx_print_logmsg(const char* func, const string& msg, GxMsgType msgtype) {
    static list<logmsg> msglist;

    // timestamp
    time_t now;
    time(&now);
    struct tm *tm_now = localtime(&now);
    ostringstream msgbuf;
    msgbuf << "[" << setfill('0')
           << setw(2) << tm_now->tm_hour << ":"
           << setw(2) << tm_now->tm_min  << ":"
           << setw(2) << tm_now->tm_sec  << "]"
           << "  " << func << "  ***  " << msg;

    // log the stuff to the log message window if possible
    bool written = false;
    if (gx_gui::GxMainInterface::fInitialized) {
        gx_gui::GxMainInterface* interface = gx_gui::GxMainInterface::instance();

        if (interface->getLoggingWindow()) {
            if (!msglist.empty()) {
                for (list<logmsg>::iterator i = msglist.begin(); i != msglist.end(); i++) {
                    interface->show_msg(i->msg, i->msgtype);
                }
                msglist.clear();
            }
            interface->show_msg(msgbuf.str(), msgtype);
            written = true;
        }
    }

    if (!written) { // queue the messages
        msglist.push_back(logmsg(msgbuf.str(), msgtype));
    }
    if (terminal) {
        std::cerr << msgbuf.str() << endl;
    }
}


// warning
void gx_print_warning(const char* func, const string& msg) {
    gx_print_logmsg(func, msg, kWarning);
}

// error
void gx_print_error(const char* func, const string& msg) {
    gx_print_logmsg(func, msg, kError);
}

// fatal error
void gx_print_fatal(const char* func, const string& msg) {
    string msgbuf = string(_("fatal system error: ")) + func + "  ***  " + msg + "\n";
    std::cerr << msgbuf;
    GtkWidget* widget = gtk_message_dialog_new(NULL,
                                               GtkDialogFlags(GTK_DIALOG_MODAL|
                                                              GTK_DIALOG_DESTROY_WITH_PARENT),
                                               GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE,
                                               "%s", msgbuf.c_str());
    gtk_window_set_title(GTK_WINDOW(widget), "gx_head");
    gtk_dialog_run(GTK_DIALOG(widget));
    gx_clean_exit(NULL, (gpointer)1);
}

// info
void gx_print_info(const char* func, const string& msg) {
    gx_print_logmsg(func, msg, kInfo);
}


// ---- check version and if directory exists and create it if it not exist
bool gx_version_check() {
    struct stat my_stat;

    // ----- this check dont need to be against real version, we only need to know
    // ----- if the presethandling is working with the courent version, we only count this
    // ----- string when we must remove the old preset files.
    string rcfilename =
        sysvar.gx_user_dir + string("version-") + string("0.03.3");

    if  (stat(sysvar.gx_user_dir.c_str(), &my_stat) == 0) { // directory exists
        // check which version we're dealing with
        if  (stat(rcfilename.c_str(), &my_stat) != 0) {
            // current version not there, let's create it and refresh the whole shebang
            string oldfiles = sysvar.gx_user_dir + string("gx_head*rc");
            (void)gx_system_call("rm -f", oldfiles.c_str(), false);

            oldfiles = sysvar.gx_user_dir + string("version*");
            (void)gx_system_call("rm -f", oldfiles.c_str(), false);

            oldfiles = sysvar.gx_user_dir + string("*.conf");
            (void)gx_system_call("rm -f", oldfiles.c_str(), false);

            // setting file for current version
            ofstream f(rcfilename.c_str());
            string cim = string("gx_head-") + GX_VERSION;
            f << cim <<endl;
            f.close();

            // --- create jack_capture setting file
            /*string tmpstr = sysvar.gx_user_dir + sysvar.jcapsetup_file;

            (void)gx_system_call("touch", tmpstr.c_str(), false);
            (void)gx_system_call(
                "echo 'jack_capture -c 2 --silent --disable-meter --port gx_head:out* ' >",
                tmpstr.c_str(),
                false
                ); */
        }
    } else { // directory does not exist
        // create .gx_head directory
        (void)gx_system_call("mkdir -p", sysvar.gx_user_dir.c_str(), false);

        // setting file for current version
        ofstream f(rcfilename.c_str());
        string cim = string("gx_head-") + GX_VERSION;
        f << cim <<endl;
        f.close();

        // --- create jack_capture setting file
        string tmpstr = sysvar.gx_user_dir + sysvar.jcapsetup_file;

    /*    (void)gx_system_call("touch", tmpstr.c_str(), false);
        (void)gx_system_call(
            "echo 'jack_capture -c 2 --silent --disable-meter --port gx_head:out* ' >",
            tmpstr.c_str(),
            false
            ); */

        // --- version file
        // same here, we only change this file, when the presethandling is broken,
        // otherwise we can let it untouched
        tmpstr = sysvar.gx_user_dir + string("version-") + string("0.03.3");
        (void)gx_system_call("touch", tmpstr.c_str(), false);

        cim = string("echo 'gx_head-") + string(GX_VERSION) + "' >";
        (void)gx_system_call(cim.c_str(), tmpstr.c_str(), false);

        // create empty preset file
        tmpstr = sysvar.gx_user_dir + string("gx_headpre_rc");
        ofstream nfile(tmpstr.c_str());
        JsonWriter jw(nfile);
        jw.begin_array();
        writeHeader(jw);
        jw.end_array(true);
        jw.close();
        nfile.close();
    }

    return TRUE;
}

// ----- we must make sure that the images for the status icon be there
int gx_pixmap_check() {
    struct stat my_stat;

    string gx_pix   = sysvar.gx_pixmap_dir + "gx_head.png";
    string midi_pix = sysvar.gx_pixmap_dir + "gx_head-midi.png";
    string warn_pix = sysvar.gx_pixmap_dir + "gx_head-warn.png";

    if ((stat(gx_pix.c_str(), &my_stat) != 0)   ||
        (stat(midi_pix.c_str(), &my_stat) != 0) ||
        (stat(warn_pix.c_str(), &my_stat) != 0)) {
        gx_print_error(_("Pixmap Check"), _(" cannot find installed pixmaps! giving up ..."));

        // giving up
        return 1;
    }

    GtkWidget *ibf =  gtk_image_new_from_file(gx_pix.c_str());
    gx_gui::gw.ib = gtk_image_get_pixbuf(GTK_IMAGE(ibf));

    GtkWidget *stim = gtk_image_new_from_file(midi_pix.c_str());
    gx_gui::gw.ibm = gtk_image_get_pixbuf(GTK_IMAGE(stim));

    GtkWidget *stir = gtk_image_new_from_file(warn_pix.c_str());
    gx_gui::gw.ibr = gtk_image_get_pixbuf(GTK_IMAGE(stir));

    return 0;
}

// ----convert int to string
void gx_IntToString(int i, string & s) {
    s = "";

    int abs_i = abs(i);
    do {
        // note: using base 10 since 10 digits (0123456789)
        char c = static_cast<char>(ASCII_START+abs_i%10);
        s.insert(0, &c, 1);
    }
    while ((abs_i /= 10) > 0);
    if (i < 0) s.insert(0, "-");
}

const string& gx_i2a(int i) {
    static string str;
    gx_IntToString(i, str);

    return str;
}

// ----clean up preset name given by user
void gx_nospace_in_name(string& name, const char* subs) {
    int p = name.find(' ', 0);
    while (p != -1) {
        name.replace(p++, 1, subs);
        p = name.find(' ', p);
    }
}

// ----abort gx_head
void gx_abort(void* arg) {
    gx_print_warning(_("gx_abort"), _("Aborting gx_head, ciao!"));
    exit(1);
}

// ---- gx_head system function
int gx_system_call(const char* name1,
                   const char* name2,
                   const bool  devnull,
                   const bool  escape) {
    string str(name1);
    str.append(" ");
    str.append(name2);

    if (devnull)
        str.append(" 1>/dev/null 2>&1");

    if (escape)
        str.append("&");

    //    cerr << " ********* \n system command = " << str.c_str() << endl;

    sigset_t waitset;
    sigemptyset(&waitset);
    sigaddset(&waitset, SIGCHLD);
    sigprocmask(SIG_UNBLOCK, &waitset, NULL);
    int rc = system(str.c_str());
    sigprocmask(SIG_BLOCK, &waitset, NULL);
    return rc;
}

// polymorph1
int gx_system_call(const char*   name1,
                   const string& name2,
                   const bool  devnull,
                   const bool  escape) {
    return gx_system_call(name1, name2.c_str(), devnull, escape);
}

// polymorph2
// int gx_system_call(const string& name1,
//             const string& name2,
//              const bool  devnull,
//              const bool  escape)
// {
//   return gx_system_call(name1.c_str(), name2.c_str(), devnull, escape);
// }

// polymorph3
int gx_system_call(const string& name1,
                   const char*   name2,
                   const bool  devnull,
                   const bool  escape) {
    return gx_system_call(name1.c_str(), name2, devnull, escape);
}


// ----- clean up when shut down
void gx_destroy_event() {
    // remove image buffers
    if (G_IS_OBJECT(gx_gui::gw.ib))
        g_object_unref(gx_gui::gw.ib);

    if (G_IS_OBJECT(gx_gui::gw.ibm))
        g_object_unref(gx_gui::gw.ibm);

    if (G_IS_OBJECT(gx_gui::gw.ibr))
        g_object_unref(gx_gui::gw.ibr);

    // remove threads from main GTK thread
    for (unsigned int i = 0; i < sizeof(gx_gui::guivar.g_threads)/sizeof(gx_gui::guivar.g_threads[0]); i++) {
        if (gx_gui::guivar.g_threads[i] > 0) {
            g_source_remove(gx_gui::guivar.g_threads[i]);
        }
    }

    gtk_main_quit();
}

// -----Function that must be called before complete shutdown
void gx_clean_exit(GtkWidget* widget, gpointer data) {
    // save DSP state
    if (gx_engine::isInitialized()) {
        gx_engine::get_latency_warning_change();
        gx_gui::gx_get_skin_change(&gx_engine::audio.fskin);

        if (gtk_widget_get_visible(GTK_WIDGET(gx_gui::gw.fWindow))) {
            gint mainxorg, mainyorg;
            gtk_window_get_position(GTK_WINDOW(gx_gui::gw.fWindow), &mainxorg, &mainyorg);
            gx_gui::guivar.main_xorg = static_cast<float>(mainxorg);
            gx_gui::guivar.main_yorg = static_cast<float>(mainyorg);
        }

        // only save if we are not in a preset or session context
        if (!gx_preset::gxpreset.setting_is_preset && !gx_preset::gxpreset.setting_is_factory
                                          && !sysvar.is_session
                                          && gx_jack::gxjack.client) {
            saveStateToFile(sysvar.gx_user_dir + gx_jack::gxjack.client_instance + "_rc");
        }
    }

    gx_gui::guivar.shownote = -1;
    gx_gui::guivar.showwave = 0;
    gx_jack::gxjack.NO_CONNECTION = 1;

    gx_engine::turnOffMidi();

    // clean jack gxjack.client stuff
    gx_jack::gxjack.gx_jack_cleanup();

    // clean GTK stuff
    if (gx_gui::gw.fWindow) {
        gx_destroy_event();
    }
    // delete the locked mem buffers
    if (gx_engine::audio.checkfreq) {
        delete[] gx_engine::audio.checkfreq;
        gx_engine::audio.checkfreq = NULL;
    }
    if (gx_engine::audio.get_frame) {
        delete[] gx_engine::audio.get_frame;
        gx_engine::audio.get_frame = NULL;
    }
    if (gx_engine::audio.get_frame1) {
        delete[] gx_engine::audio.get_frame1;
        gx_engine::audio.get_frame1 = NULL;
    }
    if (gx_engine::audio.oversample) {
        delete[] gx_engine::audio.oversample;
        gx_engine::audio.oversample = NULL;
    }
    if (gx_engine::audio.result) {
        delete[] gx_engine::audio.result;
        gx_engine::audio.result = NULL;
    }
    delete gx_engine::_modulpointer;
    gx_resample::_glob_resamp->delete_resampler_ref();
    gx_engine::pitch_tracker.stop_thread();
    delete gx_jack::_jackbuffer_ptr;

    if (sysvar.is_session) {
        jack_session_event_t *event = reinterpret_cast<jack_session_event_t *>(data);
        jack_session_event_free(event);
        printf(_("  gx_head session exit  ***  ciao . . \n"));
        return;
    } else {    
        printf(_("  gx_head exit  ***  ciao . . \n"));
    }
    exit(GPOINTER_TO_INT(data));
}
} /* end of gx_system namespace */

