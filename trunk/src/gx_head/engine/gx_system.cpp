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

#include <dirent.h>
#include <iostream>
#include <iomanip>                  // NOLINT

#include "engine.h"

namespace gx_system {

/****************************************************************
 ** Measuring times (only when debugging)
 */

#ifndef NDEBUG

void Measure::reset() {
    period.reset();
    duration.reset();
    duration1.reset();
    duration2.reset();
    FPUStatus1 = 0;
    FPUStatus2 = 0;
    MXStatus1 = 0;
    MXStatus2 = 0;
}

void Measure::print_accum(const Accum& accum, const char* prefix, bool verbose, int total) const {
    streamsize prec = cout.precision();
    ios_base::fmtflags flags = cout.flags();
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
    cout.precision(prec);
    cout.flags(flags);
}

static void print_status(const char *title, unsigned int status) {
    // print list of names for active bits in "status"
    // bits for mmx and x87 have different symbolic names in
    // header files but are actually identical so that this function
    // can be used for both types status word
    Glib::ustring s;
    if (status & FE_INVALID) {
	if (!s.empty()) {
	    s += ",";
	}
	s += "invalid";
    }
#ifdef FE_DENORM
    if (status & FE_DENORM) {
	if (!s.empty()) {
	    s += ",";
	}
	s += "denormal";
    }
#endif
    if (status & FE_DIVBYZERO) {
	if (!s.empty()) {
	    s += ",";
	}
	s += "zerodivide";
    }
    if (status & FE_OVERFLOW) {
	if (!s.empty()) {
	    s += ",";
	}
	s += "overflow";
    }
    if (status & FE_UNDERFLOW) {
	if (!s.empty()) {
	    s += ",";
	}
	s += "underflow";
    }
    if (!s.empty()) {
	cout << title << s << endl;
    }
}

void Measure::print(bool verbose) const {
    if (verbose) {
        print_accum(period,    "period     ", verbose);
	print_accum(duration1, "duration1  ", verbose, period.mean());
	print_accum(duration2, "duration2  ", verbose, period.mean());
	print_accum(duration,  "duration   ", verbose, period.mean());
    } else {
        print_accum(duration, "duration  ", false, period.mean());
    }
    print_status("FPU status: ", FPUStatus1 | FPUStatus2);
    print_status("MX status: ", MXStatus1 | MXStatus2);
}

MeasureThreadsafe::MeasureThreadsafe()
    : m(), pmeasure(m), t1s(), t1e(), t2s(), t1old(), FPUStatus(), MXStatus() {
}

void MeasureThreadsafe::print(bool verbose) {
    Measure *p = pmeasure;
    Measure *pn;
    if (p == m) {
        pn = m+1;
    } else {
        pn = m;
    }
    atomic_set(&pmeasure, pn);
    p->print(verbose);
    p->reset();
}

MeasureThreadsafe measure;

void add_time_measurement() {
    char *p = getenv("GUITARIX_MEASURE");
    if (!p) {
        return;
    }
    bool verbose = false;
    if (strcmp(p, "1") == 0) {
        verbose = true;
    }
    Glib::signal_timeout().connect(
	sigc::bind_return(
	    sigc::bind(
		sigc::mem_fun(measure, &MeasureThreadsafe::print),
		verbose),
	    true),
	1000);
}

#endif


/****************************************************************
 ** CmdlineOptions
 ** command line options
 */

void SkinHandling::set_styledir(const string& style_dir) {
    // fetch all skin names in directory
    DIR *d;
    d = opendir(style_dir.c_str());
    if (!d) {
        return;
    }
    // look for gx_head_*.rc and extract *-part
    struct dirent *de;
    skin_list.clear();
    while ((de = readdir(d)) != 0) {
        char *p = de->d_name;
        if (strncmp(p, "gx_head_", 8) != 0) {
            continue;
        }
        p += 8;
        int n = strlen(p) - 3;
        if (strcmp(p+n, ".rc") != 0) {
            continue;
        }
        skin_list.push_back(string(p, n));
    }
    closedir(d);
    sort(skin_list.begin(), skin_list.end());
}

bool SkinHandling::is_in_list(const string& name) {
    for (vector<string>::iterator i = skin_list.begin(); i != skin_list.end(); ++i) {
	if (*i == name) {
	    return true;
	}
    }
    return false;
}

PathList::PathList(const char *env_name): dirs() {
    if (!env_name) {
	return;
    }
    const char *p = getenv(env_name);
    if (!p) {
	return;
    }
    while (true) {
	const char *q = strchr(p, ':');
	if (q) {
	    int n = q - p;
	    if (n) {
		add(std::string(p, n));
	    }
	    p = q+1;
	} else {
	    if (*p) {
		add(p);
	    }
	    break;
	}
    }
}

bool PathList::contains(const string& d) const {
    Glib::RefPtr<Gio::File> f = Gio::File::create_for_path(d);
    for (pathlist::const_iterator i = dirs.begin();
	 i != dirs.end(); ++i) {
	if (f->equal(*i)) {
	    return true;
	}
    }
    return false;
}


bool PathList::find_dir(std::string* d, const std::string& filename) const {
    for (pathlist::const_iterator i = dirs.begin();
	 i != dirs.end(); ++i) {
	string p = (*i)->get_path();
	string fn = Glib::build_filename(p, filename);
	if (access(fn.c_str(), R_OK) == 0) {
	    *d = p;
	    return true;
	    }
	}
    return false;
}

CmdlineOptions *CmdlineOptions::instance = 0;

static inline const char *shellvar(const char *name) {
    const char *p = getenv(name);
    return p ? p : "";
}

#define TCLR(s)  "\033[1;32m" s "\033[0m" // light green
#define TCLR2(s) TCLR(s), s

CmdlineOptions::CmdlineOptions()
    : main_group("",""),
      optgroup_style("style", TCLR2("GTK style configuration options")),
      optgroup_jack("jack", TCLR2("JACK configuration options")),
      optgroup_file("file", TCLR2("File options")),
      optgroup_debug("debug", TCLR2("Debug options")),
      version(false), clear(false),
      jack_input(shellvar("GUITARIX2JACK_INPUTS")),
      jack_midi(shellvar("GUITARIX2JACK_MIDI")),
      jack_outputs(),
      jack_uuid(),
      jack_uuid2(),
      load_file(shellvar("GUITARIX_LOAD_FILE")),
      builder_dir(GX_BUILDER_DIR),
      style_dir(GX_STYLE_DIR),
      factory_dir(GX_FACTORY_DIR),
      pixmap_dir(GX_PIXMAPS_DIR),
      user_dir(),
      old_user_dir(),
      preset_dir(),
      pluginpreset_dir(),
      plugin_dir(),
      sys_IR_dir(GX_SOUND_DIR),
      IR_pathlist(),
      rcset(shellvar("GUITARIX_RC_STYLE")),
      lterminal(false),
#ifndef NDEBUG
      dump_parameter(false),
#endif
      skin(style_dir) {
    const char* home = getenv("HOME");
    if (!home) {
	throw GxFatalError(_("no HOME environment variable"));
    }
    old_user_dir = string(home) + "/.gx_head/";
    user_dir = Glib::build_filename(Glib::get_user_config_dir(), "guitarix");
    plugin_dir = Glib::build_filename(user_dir, "plugins");
    preset_dir = Glib::build_filename(user_dir, "banks");
    pluginpreset_dir = Glib::build_filename(user_dir, "pluginpresets");
    const char *tmp = getenv("GUITARIX2JACK_OUTPUTS1");
    if (tmp && *tmp) {
	jack_outputs.push_back(tmp);
    }
    tmp = getenv("GUITARIX2JACK_OUTPUTS2");
    if (tmp && *tmp) {
	jack_outputs.push_back(tmp);
    }

    // ---- parse command line arguments
    set_summary(
        "All parameters are optional. Examples:\n"
        "\tguitarix\n"
        "\tguitarix -r gx4-black -i system:capture_3\n"
        "\tguitarix -c -o system:playback_1 -o system:playback_2");
    Glib::OptionEntry opt_version;
    opt_version.set_short_name('v');
    opt_version.set_long_name("version");
    opt_version.set_description("Print version string and exit");
    main_group.add_entry(opt_version, version);
    set_main_group(main_group);

    Glib::OptionEntry opt_clear;
    opt_clear.set_short_name('c');
    opt_clear.set_long_name("clear");
    opt_clear.set_description("Use 'default' GTK style");
    Glib::OptionEntry opt_rcset;
    opt_rcset.set_short_name('r');
    opt_rcset.set_long_name("rcset");
    opt_rcset.set_description(get_opskin());
    opt_rcset.set_arg_description("STYLE");
    optgroup_style.add_entry(opt_clear, clear);
    optgroup_style.add_entry(opt_rcset, rcset);

    // JACK options: input and output ports
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
    Glib::OptionEntry opt_jack_instance;
    opt_jack_instance.set_short_name('n');
    opt_jack_instance.set_long_name("name");
    opt_jack_instance.set_description("instance name (default gx_head)");
    opt_jack_instance.set_arg_description("NAME");
    Glib::OptionEntry opt_jack_uuid;
    opt_jack_uuid.set_short_name('U');
    opt_jack_uuid.set_long_name("jack-uuid");
    opt_jack_uuid.set_description("JackSession ID");
    Glib::OptionEntry opt_jack_uuid2;
    opt_jack_uuid2.set_short_name('A');
    opt_jack_uuid2.set_long_name("jack-uuid2");
    opt_jack_uuid2.set_description("JackSession ID");
    optgroup_jack.add_entry(opt_jack_input, jack_input);
    optgroup_jack.add_entry(opt_jack_output, jack_outputs);
    optgroup_jack.add_entry(opt_jack_midi, jack_midi);
    optgroup_jack.add_entry(opt_jack_instance, jack_instance);
    optgroup_jack.add_entry(opt_jack_uuid, jack_uuid);
    optgroup_jack.add_entry(opt_jack_uuid2, jack_uuid2);

    // FILE options

    Glib::OptionEntry opt_load_file;
    opt_load_file.set_short_name('f');
    opt_load_file.set_long_name("load-file");
    opt_load_file.set_description(_("load state file on startup"));
    opt_load_file.set_arg_description("FILE");
    optgroup_file.add_entry_filename(opt_load_file, load_file);
    Glib::OptionEntry opt_plugin_dir;
    opt_plugin_dir.set_short_name('P');
    opt_plugin_dir.set_long_name("plugin-dir");
    opt_plugin_dir.set_description(_("directory with guitarix plugins (.so files)"));
    opt_plugin_dir.set_arg_description("DIR");
    optgroup_file.add_entry_filename(opt_plugin_dir, plugin_dir);

    // DEBUG options
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
#ifndef NDEBUG
    Glib::OptionEntry opt_dump_parameter;
    opt_dump_parameter.set_short_name('d');
    opt_dump_parameter.set_long_name("dump-parameter");
    opt_dump_parameter.set_description(_("dump parameter table in json format"));
    optgroup_debug.add_entry(opt_dump_parameter, dump_parameter);
#endif

    // collecting all option groups
    add_group(optgroup_style);
    add_group(optgroup_jack);
    add_group(optgroup_file);
    add_group(optgroup_debug);

    instance = this;
}

CmdlineOptions::~CmdlineOptions() {
    instance = 0;
}

Glib::ustring CmdlineOptions::get_jack_output(unsigned int n) const {
    if (n >= jack_outputs.size()) {
	return "";
    }
    return jack_outputs.at(n);
}

string CmdlineOptions::get_opskin() {
    // initialize number of skins. We just count the number of rc files
    unsigned int n = skin.skin_list.size();
    if (n < 1) {
        gx_print_error(_("main"), string(_("number of skins is 0")));
	GxExit::get_instance().exit_program();
    }

    // GTK options: rc style (aka skin)
    string opskin("Style to use");

    vector<string>::iterator it;

    for (it = skin.skin_list.begin(); it != skin.skin_list.end(); ++it) {
        opskin += ", '" + *it + "'";
    }
    return opskin;
}

static void log_terminal(const string& msg, GxMsgType tp, bool plugged) {
    const char *t;
    switch (tp) {
    case kInfo:    t = "I"; break;
    case kWarning: t = "W"; break;
    case kError:   t = "E"; break;
    default:       t = "?"; break;
    }
    if (!plugged) {
	cerr << t << " " << msg << endl;
    }
}

void CmdlineOptions::make_ending_slash(string& dirpath) {
    if (dirpath.empty()) {
	return;
    }
    if (dirpath[dirpath.size()-1] != '/') {
	dirpath += "/";
    }
}

void CmdlineOptions::process(int argc, char** argv) {
    path_to_program = Gio::File::create_for_path(argv[0])->get_path();
    if (version) {
        std::cout << "Guitarix version \033[1;32m"
             << GX_VERSION << endl
             << "\033[0m   Copyright " << static_cast<char>(0x40) << " 2010 "
             << "Hermman Meyer - James Warden - Andreas Degert"
             << endl;
        exit(0);
    }
#ifdef NDEBUG
    if (argc > 1) {
	throw gx_system::GxFatalError(
	    string("unknown argument on command line: ")+argv[1]);
    }
#endif
    if (clear && !rcset.empty()) {
	throw Glib::OptionError(
	    Glib::OptionError::BAD_VALUE,
	    _("-c and -r cannot be used together"));
    }
    if (lterminal) {
	Logger::get_logger().signal_message().connect(
	    sigc::ptr_fun(log_terminal));
    }

    make_ending_slash(builder_dir);
    make_ending_slash(style_dir);
    make_ending_slash(factory_dir);
    make_ending_slash(pixmap_dir);
    make_ending_slash(user_dir);
    make_ending_slash(preset_dir);
    make_ending_slash(pluginpreset_dir);
    make_ending_slash(plugin_dir);
    make_ending_slash(sys_IR_dir);

    IR_pathlist.add(get_user_dir());
    IR_pathlist.add(get_sys_IR_dir());

    skin.set_styledir(style_dir);
    if (!rcset.empty() && !skin.is_in_list(rcset)) {
	throw Glib::OptionError(
	    Glib::OptionError::BAD_VALUE,
	    (boost::format(_("invalid style '%1%' on command line"))
	     % rcset).str());
    }
    if (jack_outputs.size() >= 2) {
	gx_print_warning(
	    _("main"),
	    _("Warning --> provided more than 2 output ports, ignoring extra ports"));
    }
}


/****************************************************************
 ** Logging
 */

Logger::Logger()
    : trackable(),
      msglist(),
      msgmutex(),
      got_new_msg(),
      ui_thread(),
      handlers(),
      queue_all_msgs(true) {
}

static class LoggerGuard {
private:
    Logger *logger_instance;
public:
    LoggerGuard() : logger_instance(0) {}
    ~LoggerGuard() { destroy(); }
    void create() { logger_instance = new Logger; }
    void destroy() { if (logger_instance) { delete logger_instance; logger_instance = 0; }}
    Logger *get() { return logger_instance; }
} logger_guard;

Logger& Logger::get_logger() {
    Logger *l = logger_guard.get();
    if (!l) {
	logger_guard.create();
	l = logger_guard.get();
    }
    return *l;
}

void Logger::destroy() {
    logger_guard.destroy();
}

Logger::~Logger() {
    delete got_new_msg;
}

void Logger::set_ui_thread() {
    if (ui_thread) {
	assert(pthread_equal(pthread_self(), ui_thread));
    } else {
	got_new_msg = new Glib::Dispatcher;
	ui_thread = pthread_self();
	got_new_msg->connect(mem_fun(*this, &Logger::write_queued));
    }
}

Logger::msg_signal& Logger::signal_message() {
    set_ui_thread();
    return handlers;
}

void Logger::unplug_queue() {
    if (!queue_all_msgs) {
	return;
    }
    queue_all_msgs = false;
    write_queued();
}

void Logger::write_queued() {
    if (handlers.empty()) {
	return;
    }

    // quick copy list
    msgmutex.lock();
    list<logmsg> l = msglist;
    if (!queue_all_msgs) {
	msglist.clear();
    }
    msgmutex.unlock();

    // feed throught the handler(s)
    for (list<logmsg>::iterator i = l.begin(); i != l.end(); ++i) {
	if (queue_all_msgs) {
	    if (!i->plugged) {
		handlers(i->msg, i->msgtype, i->plugged);
		i->plugged = true;
	    }
	} else {
	    handlers(i->msg, i->msgtype, i->plugged);
	}
    }
}

string Logger::format(const char* func, const string& msg) {
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
    return msgbuf.str();
}

void Logger::print(const char* func, const string& msg, GxMsgType msgtype) {
    string m = format(func, msg);
    if (handlers.empty() || !(pthread_equal(pthread_self(), ui_thread))) {
	boost::mutex::scoped_lock lock(msgmutex);
	// defer output
        msglist.push_back(logmsg(m, msgtype, false));
	if (!handlers.empty() && msglist.size() == 1) {
	    (*got_new_msg)();
	}
    } else {
	write_queued();
	handlers(m, msgtype, false);
	if (queue_all_msgs) {
	    msglist.push_back(logmsg(m, msgtype, true));
	}
    }
}

/*
** utility logger functions
*/

// ---- log message handler
void gx_print_logmsg(const char* func, const string& msg, GxMsgType msgtype) {
    Logger::get_logger().print(func, msg, msgtype);
}

// warning
void gx_print_warning(const char* func, const string& msg) {
    gx_print_logmsg(func, msg, kWarning);
}

// error
void gx_print_error(const char* func, const string& msg) {
    gx_print_logmsg(func, msg, kError);
}

GxFatalError::~GxFatalError() throw() {
}

// fatal error
// - do not use before Gtk::Main() ctor
// - do not use when main loop is blocked (modal dialog or something)
//
void gx_print_fatal(const char* func, const string& msg) {
    string msgbuf = string(_("fatal system error: ")) + func + "  ***  " + msg + "\n";
    GxExit::get_instance().fatal_msg(msgbuf);
}

// info
void gx_print_info(const char* func, const string& msg) {
    gx_print_logmsg(func, msg, kInfo);
}


/****************************************************************
 ** class GxExit
 */

GxExit::GxExit(): exit_sig(), ui_thread() {}

GxExit::~GxExit() {}

void GxExit::exit_program(string msg, int errcode) {
    exit_sig(pthread_equal(pthread_self(), ui_thread));
    if (msg.empty()) {
	msg = "** guitarix exit **";
    }
    cerr << msg << endl;
    _exit(errcode);
}

GxExit& GxExit::get_instance() {
    static GxExit instance;
    return instance;
}


/****************************************************************
 ** misc functions
 */

// ---- gx_head system function
int gx_system_call(const string& cmd,
                   const bool  devnull,
                   const bool  escape) {
    string str = cmd;

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

void strip(Glib::ustring& s) {
    size_t n = s.find_first_not_of(' ');
    if (n == Glib::ustring::npos) {
	s.erase();
	return;
    }
    if (n != 0) {
	s.erase(0, n);
    }
    s.erase(s.find_last_not_of(' ')+1);
}

} /* end of gx_system namespace */
