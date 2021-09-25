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
 ** class SkinHandling
 */

void SkinHandling::set_styledir(const string& style_dir) {
    // fetch all skin names in directory
    DIR *d;
    d = opendir(style_dir.c_str());
    if (!d) {
        return;
    }
    // look for gx_head_*.css and extract *-part
    struct dirent *de;
    skin_list.clear();
    while ((de = readdir(d)) != 0) {
        char *p = de->d_name;
        if (strncmp(p, "gx_head_", 8) != 0) {
            continue;
        }
        if (strncmp(p, "gx_head_gx", 10) == 0) {
            continue;
        }
        p += 8;
        int n = strlen(p) - 4;
        if (strcmp(p+n, ".css") != 0) {
            continue;
        }
        skin_list.push_back(string(p, n));
    }
    closedir(d);
    sort(skin_list.begin(), skin_list.end());
}

string SkinHandling::get_cssfile() const {
    if (name.empty()) {
	return "minimal.css";
    }
    return "gx_head_" + name + ".css";
}

bool SkinHandling::is_in_list(const string& name) {
    return index(name) < skin_list.size();
}

unsigned int SkinHandling::index(const Glib::ustring& name) {
    unsigned int i = 0;
    for (; i < skin_list.size(); ++i) {
	if (skin_list[i] == name) {
	    break;
	}
    }
    return i;
}

const Glib::ustring& SkinHandling::operator[](unsigned int idx) {
    if (idx < skin_list.size()) {
	return skin_list[idx];
    } else {
	static Glib::ustring empty;
	return empty;
    }
}

void SkinHandling::set_default_skin_name() {
    name = "Guitarix";
}

/****************************************************************
 ** class PathList
 */

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


/****************************************************************
 ** class PrefixConverter
 */

void PrefixConverter::add(char s, const std::string& d) {
    assert(s != '%');
    dirs[s] = (d[d.size()-1] == '/' ? d.substr(0,d.size()-1) : d);
}

std::string PrefixConverter::replace_symbol(const std::string& dir) const {
    if (dir.size() < 2 || dir[0] != '%') {
	return dir;
    }
    symbol_path_map::const_iterator i = dirs.find(dir[1]);
    if (i != dirs.end()) {
	return Glib::build_filename(i->second, dir.substr(2));
    }
    if (dir.compare(0, 2, "%%")) {
	return dir.substr(1);
    }
    return dir;
}

std::string PrefixConverter::replace_path(const std::string& dir) const {
    for (symbol_path_map::const_iterator i = dirs.begin(); i != dirs.end(); ++i) {
	size_t n = i->second.size();
	if (dir.compare(0, n, i->second) == 0) {
	    std::string tail = dir.substr(n);
	    if (Glib::build_filename(i->second, tail) == dir) {
		std::string sym = "%";
		sym.push_back(i->first);
		return sym + tail;
	    }
	}
    }
    if (dir.size() < 2 || dir[0] != '%') {
	return dir;
    }
    return "%" + dir;
}


/*****************************************************************
 ** class DirectoryListing
 */

IRFileListing::IRFileListing(const std::string& path) {
    Glib::RefPtr<Gio::File> file = Gio::File::create_for_path(path);
    if (file->query_exists()) {
        Glib::RefPtr<Gio::FileEnumerator> child_enumeration =
              file->enumerate_children(G_FILE_ATTRIBUTE_STANDARD_NAME
				       "," G_FILE_ATTRIBUTE_STANDARD_DISPLAY_NAME
				       "," G_FILE_ATTRIBUTE_STANDARD_FAST_CONTENT_TYPE);
        Glib::RefPtr<Gio::FileInfo> file_info;
        while ((file_info = child_enumeration->next_file())) {
            std::string content_type = file_info->get_attribute_string(
                G_FILE_ATTRIBUTE_STANDARD_FAST_CONTENT_TYPE);
	    if (content_type.substr(0, 6) == "audio/") {
		listing.push_back(
		    FileName(
			file_info->get_attribute_byte_string(G_FILE_ATTRIBUTE_STANDARD_NAME),
			file_info->get_attribute_string(G_FILE_ATTRIBUTE_STANDARD_DISPLAY_NAME)));
	    }
        }
    } else {
        gx_print_error(
	    "jconvolver",
	    boost::format(_("Error reading file path %1%")) % path);
    }
}

static void list_subdirs(const Glib::RefPtr<Gio::File>& file, std::vector<FileName>& dirs, const Glib::ustring& prefix) {
    Glib::RefPtr<Gio::FileEnumerator> child_enumeration =
	file->enumerate_children(G_FILE_ATTRIBUTE_STANDARD_NAME
				 "," G_FILE_ATTRIBUTE_STANDARD_DISPLAY_NAME);
    Glib::RefPtr<Gio::FileInfo> file_info;
    while ((file_info = child_enumeration->next_file())) {
	if (file_info->get_file_type() == Gio::FILE_TYPE_DIRECTORY) {
	    Glib::RefPtr<Gio::File> child = file->get_child(
		file_info->get_attribute_byte_string(G_FILE_ATTRIBUTE_STANDARD_NAME));
	    dirs.push_back(
		FileName(
		    child->get_path(),
		    prefix+file_info->get_attribute_string(G_FILE_ATTRIBUTE_STANDARD_DISPLAY_NAME)));
	    list_subdirs(child, dirs, prefix+"  ");
	}
    }
}

void list_subdirs(PathList pl, std::vector<FileName>& dirs) {
    for (PathList::iterator i = pl.begin(); i != pl.end(); ++i) {
	std::string fn = (*i)->get_path();
	dirs.push_back(FileName(fn, fn));
	list_subdirs(*i, dirs, "  ");
    }
}


/****************************************************************
 ** class BasicOptions
 */

BasicOptions *BasicOptions::instance = 0;

BasicOptions::BasicOptions()
    : user_dir(),
      user_IR_dir(),
      sys_IR_dir(GX_SOUND_DIR),
      IR_pathlist(),
      IR_prefixmap(),
    builder_dir(GX_BUILDER_DIR) {
    user_dir = Glib::build_filename(Glib::get_user_config_dir(), "guitarix");
    user_IR_dir = Glib::build_filename(user_dir, "IR");

    make_ending_slash(user_dir);
    make_ending_slash(user_IR_dir);
    make_ending_slash(sys_IR_dir);
    make_ending_slash(builder_dir);

    // for legacy presets
    IR_pathlist.add(get_user_IR_dir());
    IR_pathlist.add(get_sys_IR_dir());

    // for current presets
    IR_prefixmap.add('U', get_user_IR_dir());
    IR_prefixmap.add('S', get_sys_IR_dir());

    instance = this;
}

BasicOptions::~BasicOptions() {
    instance = 0;
}

void BasicOptions::make_ending_slash(string& dirpath) {
    if (dirpath.empty()) {
	return;
    }
    if (dirpath[dirpath.size()-1] != '/') {
	dirpath += "/";
    }
}


/****************************************************************
 ** class CmdlineOptions
 */

static inline const char *shellvar(const char *name) {
    const char *p = getenv(name);
    return p ? p : "";
}

#define TCLR(s)  "\033[1;32m" s "\033[0m" // light green
#define TCLR2(s) TCLR(s), s

CmdlineOptions::CmdlineOptions()
    : BasicOptions(),
      main_group("",""),
      optgroup_style("style", TCLR2("GTK style configuration options")),
      optgroup_jack("jack", TCLR2("JACK configuration options")),
      optgroup_overload("overload", TCLR2("Switch to bypass mode on overload condition")),
      optgroup_file("file", TCLR2("File options")),
      optgroup_debug("debug", TCLR2("Debug options")),
      version(false), clear(false),
      jack_input(shellvar("GUITARIX2JACK_INPUTS")),
      jack_midi(shellvar("GUITARIX2JACK_MIDI")),
      jack_outputs(),
      jack_uuid(),
      jack_uuid2(),
      jack_noconnect(false),
      jack_single(false),
      jack_servername(),
      load_file(shellvar("GUITARIX_LOAD_FILE")),
      style_dir(GX_STYLE_DIR),
      factory_dir(GX_FACTORY_DIR),
      pixmap_dir(GX_PIXMAPS_DIR),
      old_user_dir(),
      preset_dir(),
      pluginpreset_dir(),
      lv2_preset_dir(),
      temp_dir(),
      plugin_dir(),
      loop_dir(),
      rcset(shellvar("GUITARIX_RC_STYLE")),
      nogui(false),
      rpcport(RPCPORT_DEFAULT),
      rpcaddress(),
      onlygui(false),
      liveplaygui(false),
      hideonquit(false),
      mute(false),
      setbank(),
      cmdline_bank(),
      cmdline_preset(),
      tuner_tet(),
      tuner_ref(),
      sporadic_overload(0),
      idle_thread_timeout(0),
      convolver_watchdog(true),
      watchdog_warning(true),
      xrun_watchdog(false),
      lterminal(false),
      a_save(false),
      auto_save(false),
#ifndef NDEBUG
      dump_parameter(false),
#endif
      skin(style_dir),
      mainwin_visible(0),
      mainwin_x(-1),
      mainwin_y(-1),
      mainwin_height(-1),
      window_height(600),
      preset_window_height(220),
      mul_buffer(1),
      no_warn_latency(false),
      system_order_rack_h(false),
      system_show_value(false),
      system_show_tooltips(true),
      system_animations(true),
      system_show_presets(false),
      system_show_toolbar(false),
      system_show_rack(false),
      system_midiout(false),
      reload_lv2_presets(true) {
    const char* home = getenv("HOME");
    if (!home) {
	throw GxFatalError(_("no HOME environment variable"));
    }
    old_user_dir = string(home) + "/.gx_head/";
    plugin_dir = Glib::build_filename(get_user_dir(), "plugins");
    preset_dir = Glib::build_filename(get_user_dir(), "banks");
    pluginpreset_dir = Glib::build_filename(get_user_dir(), "pluginpresets");
    lv2_preset_dir = Glib::build_filename(get_user_dir(), "pluginpresets/lv2");
    loop_dir = Glib::build_filename(get_pluginpreset_dir(), "loops");
    temp_dir = Glib::build_filename(get_user_dir(), "temp");
    const char *tmp = getenv("GUITARIX2JACK_OUTPUTS1");
    if (tmp && *tmp) {
	jack_outputs.push_back(tmp);
    }
    tmp = getenv("GUITARIX2JACK_OUTPUTS2");
    if (tmp && *tmp) {
	jack_outputs.push_back(tmp);
    }

    const char *nsm_url = getenv( "NSM_URL" );

    if (!nsm_url) {
        read_ui_vars();
    }

    // ---- parse command line arguments
    set_summary(
        "All parameters are optional. Examples:\n"
        "\tguitarix\n"
        "\tguitarix -r gx4-black -i system:capture_3\n"
        "\tguitarix -c -o system:playback_1 -o system:playback_2");

    // main group
    Glib::OptionEntry opt_version;
    opt_version.set_short_name('v');
    opt_version.set_long_name("version");
    opt_version.set_description("Print version string and exit");
    Glib::OptionEntry opt_nogui;
    opt_nogui.set_short_name('N');
    opt_nogui.set_long_name("nogui");
    opt_nogui.set_description("start without GUI");
    Glib::OptionEntry opt_rpcport;
    opt_rpcport.set_short_name('p');
    opt_rpcport.set_long_name("rpcport");
    opt_rpcport.set_description("start a JSON-RPC server listening on port PORT");
    opt_rpcport.set_arg_description("PORT");
    Glib::OptionEntry opt_rpchost;
    opt_rpchost.set_short_name('H');
    opt_rpchost.set_long_name("rpchost");
    opt_rpchost.set_description("set hostname to connect to");
    opt_rpchost.set_arg_description("HOSTNAME");
    Glib::OptionEntry opt_onlygui;
    opt_onlygui.set_short_name('G');
    opt_onlygui.set_long_name("onlygui");
    opt_onlygui.set_description("start only GUI");
    Glib::OptionEntry opt_liveplaygui;
    opt_liveplaygui.set_short_name('L');
    opt_liveplaygui.set_long_name("liveplaygui");
    opt_liveplaygui.set_description("start with Live Play GUI");
    Glib::OptionEntry opt_hideonquit;
    opt_hideonquit.set_short_name('E');
    opt_hideonquit.set_long_name("hideonquit");
    opt_hideonquit.set_description("only hide GUI instead quit engine");
    Glib::OptionEntry opt_mute;
    opt_mute.set_short_name('M');
    opt_mute.set_long_name("mute");
    opt_mute.set_description("start with engine muted");
    Glib::OptionEntry opt_bank;
    opt_bank.set_short_name('b');
    opt_bank.set_long_name("bank");
    opt_bank.set_description("set bank and preset to load at startup");
    opt_bank.set_arg_description("BANK:PRESET (A:0-Z:9)");
    Glib::OptionEntry opt_tuner_tet;
    opt_tuner_tet.set_short_name('t');
    opt_tuner_tet.set_long_name("tuner_tet");
    opt_tuner_tet.set_description("set tuner temperament at startup");
    opt_tuner_tet.set_arg_description("tuner temperament (12, 19, 24, 31, 53)");
    Glib::OptionEntry opt_tuner_ref;
    opt_tuner_ref.set_short_name('F');
    opt_tuner_ref.set_long_name("reference_pitch");
    opt_tuner_ref.set_description("set tuner reference pitch at startup");
    opt_tuner_ref.set_arg_description("tuner reference pitch (225 - 453)");
    Glib::OptionEntry opt_tuner_feedback;
    opt_tuner_feedback.set_long_name("tuner-midi-feedback");
    opt_tuner_feedback.set_description("send tuner midi feedback");
    main_group.add_entry(opt_version, version);
    main_group.add_entry(opt_nogui, nogui);
    main_group.add_entry(opt_rpcport, rpcport);
    main_group.add_entry(opt_rpchost, rpcaddress);
    main_group.add_entry(opt_onlygui, onlygui);
    main_group.add_entry(opt_liveplaygui, liveplaygui);
    main_group.add_entry(opt_hideonquit, hideonquit);
    main_group.add_entry(opt_mute, mute);
    main_group.add_entry(opt_bank, setbank);
    main_group.add_entry(opt_tuner_tet, tuner_tet);
    main_group.add_entry(opt_tuner_ref, tuner_ref);
    main_group.add_entry(opt_tuner_feedback, system_tuner_midiout);
    set_main_group(main_group);

    // style options
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

    // JACK options
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
    Glib::OptionEntry opt_jack_midi_feedback;
    opt_jack_midi_feedback.set_long_name("jack-midi-feedback");
    opt_jack_midi_feedback.set_description("Guitarix send JACK midi feedback");
    Glib::OptionEntry opt_jack_noconnect;
    opt_jack_noconnect.set_short_name('J');
    opt_jack_noconnect.set_long_name("jack-no-connect");
    opt_jack_noconnect.set_description("disable self-connect JACK ports");
    Glib::OptionEntry opt_jack_instance;
    opt_jack_instance.set_short_name('n');
    opt_jack_instance.set_long_name("name");
    opt_jack_instance.set_description("instance name (default gx_head)");
    opt_jack_instance.set_arg_description("NAME");
    Glib::OptionEntry opt_jack_single;
    opt_jack_single.set_short_name('D');
    opt_jack_single.set_long_name("disable-multi-client");
    opt_jack_single.set_description("run guitarix as single client");
    Glib::OptionEntry opt_jack_uuid;
    opt_jack_uuid.set_short_name('U');
    opt_jack_uuid.set_long_name("jack-uuid");
    opt_jack_uuid.set_description("JackSession ID");
    opt_jack_uuid.set_arg_description("UUID");
    Glib::OptionEntry opt_jack_uuid2;
    opt_jack_uuid2.set_short_name('A');
    opt_jack_uuid2.set_long_name("jack-uuid2");
    opt_jack_uuid2.set_description("JackSession ID");
    opt_jack_uuid2.set_arg_description("UUID2");
    Glib::OptionEntry opt_jack_servername;
    opt_jack_servername.set_short_name('s');
    opt_jack_servername.set_long_name("server-name");
    opt_jack_servername.set_description("JACK server name to connect to");
    opt_jack_servername.set_arg_description("NAME");
    optgroup_jack.add_entry(opt_jack_input, jack_input);
    optgroup_jack.add_entry(opt_jack_output, jack_outputs);
    optgroup_jack.add_entry(opt_jack_midi, jack_midi);
    optgroup_jack.add_entry(opt_jack_midi_feedback, system_midiout);
    optgroup_jack.add_entry(opt_jack_noconnect, jack_noconnect);
    optgroup_jack.add_entry(opt_jack_instance, jack_instance);
    optgroup_jack.add_entry(opt_jack_single, jack_single);
    optgroup_jack.add_entry(opt_jack_uuid, jack_uuid);
    optgroup_jack.add_entry(opt_jack_uuid2, jack_uuid2);
    optgroup_jack.add_entry(opt_jack_servername, jack_servername);

    // Engine overload options
    Glib::OptionEntry opt_watchdog_idle;
    opt_watchdog_idle.set_short_name('I');
    opt_watchdog_idle.set_long_name("idle-timeout");
    opt_watchdog_idle.set_description(
	"starved idle thread probe (default: disabled)");
    opt_watchdog_idle.set_arg_description("SECONDS");
    Glib::OptionEntry opt_watchdog_convolver;
    opt_watchdog_convolver.set_short_name('C');
    opt_watchdog_convolver.set_long_name("no-convolver-overload");
    opt_watchdog_convolver.set_description(
	"disable overload on convolver missed deadline");
    opt_watchdog_convolver.set_flags(Glib::OptionEntry::FLAG_REVERSE);
    Glib::OptionEntry opt_watchdog_warning;
    opt_watchdog_warning.set_short_name('W');
    opt_watchdog_warning.set_long_name("no-watchdog-warning");
    opt_watchdog_warning.set_description(
	"do not pop-up warning for bypassed overload condition");
    opt_watchdog_warning.set_flags(Glib::OptionEntry::FLAG_REVERSE);
    Glib::OptionEntry opt_watchdog_xrun;
    opt_watchdog_xrun.set_short_name('X');
    opt_watchdog_xrun.set_long_name("xrun-overload");
    opt_watchdog_xrun.set_description(
	"JACK xrun (default: false)");
    Glib::OptionEntry opt_sporadic_overload;
    opt_sporadic_overload.set_short_name('S');
    opt_sporadic_overload.set_long_name("sporadic");
    opt_sporadic_overload.set_description(
	"allow single overload events per interval (default: disabled)");
    opt_sporadic_overload.set_arg_description("SECONDS");
    optgroup_overload.add_entry(opt_watchdog_idle, idle_thread_timeout);
    optgroup_overload.add_entry(opt_watchdog_convolver, convolver_watchdog);
    optgroup_overload.add_entry(opt_watchdog_warning, watchdog_warning);
    optgroup_overload.add_entry(opt_watchdog_xrun, xrun_watchdog);
    optgroup_overload.add_entry(opt_sporadic_overload, sporadic_overload);

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
    Glib::OptionEntry opt_save_on_exit;
    opt_save_on_exit.set_short_name('K');
    opt_save_on_exit.set_long_name("disable-save-on-exit");
    opt_save_on_exit.set_description(_("disable auto save to state file when quit"));
    optgroup_file.add_entry(opt_save_on_exit, a_save);
    Glib::OptionEntry opt_auto_save;
    opt_auto_save.set_short_name('a');
    opt_auto_save.set_long_name("auto-save");
    opt_auto_save.set_description(_("enable auto save (only in server mode)"));
    optgroup_file.add_entry(opt_auto_save, auto_save);

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
    opt_style_dir.set_description(_("directory with skin style definitions (.css files)"));
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
    add_group(optgroup_overload);
    add_group(optgroup_file);
    add_group(optgroup_debug);
}

CmdlineOptions::~CmdlineOptions() {
    write_ui_vars();
}

void CmdlineOptions::read_ui_vars() {
    ifstream i(Glib::build_filename(get_user_dir(), "ui_rc").c_str());
    if (i.fail()) {
        return;
    }
    JsonParser jp(&i);
    try {
        jp.next(JsonParser::begin_object);
        while (jp.peek() != JsonParser::end_object) {
            jp.next(JsonParser::value_key);
            if (jp.current_value() == "system.mainwin_visible") {
                jp.next(JsonParser::value_number);
                mainwin_visible = jp.current_value_int();
            } else if (jp.current_value() == "system.mainwin_x") {
                jp.next(JsonParser::value_number);
                mainwin_x = jp.current_value_int();
            } else if (jp.current_value() == "system.mainwin_y") {
                jp.next(JsonParser::value_number);
                mainwin_y = jp.current_value_int();
            } else if (jp.current_value() == "system.mainwin_height") {
                jp.next(JsonParser::value_number);
                mainwin_height = jp.current_value_int();
            } else if (jp.current_value() == "system.mainwin_rack_height") {
                jp.next(JsonParser::value_number);
                window_height = jp.current_value_int();
            } else if (jp.current_value() == "system.preset_window_height") {
                jp.next(JsonParser::value_number);
                preset_window_height = jp.current_value_int();
            } else if (jp.current_value() == "system.mul_buffer") {
                jp.next(JsonParser::value_number);
                mul_buffer = jp.current_value_int();
            } else if (jp.current_value() == "ui.skin_name") {
                jp.next(JsonParser::value_string);
                if (skin.is_in_list(jp.current_value())) {
                    skin.name = jp.current_value();
                } else {
                    gx_print_error(
                        _("load state"),
                        Glib::ustring::compose(_("Skin '%1' not found"), jp.current_value()));
                }
            } else if (jp.current_value() == "ui.latency_nowarn") {
                jp.next(JsonParser::value_number);
                no_warn_latency = jp.current_value_int();
            } else if (jp.current_value() == "system.order_rack_h") {
                jp.next(JsonParser::value_number);
                system_order_rack_h = jp.current_value_int();
            } else if (jp.current_value() == "system.show_value") {
                jp.next(JsonParser::value_number);
                system_show_value = jp.current_value_int();
            } else if (jp.current_value() == "system.show_tooltips") {
                jp.next(JsonParser::value_number);
                system_show_tooltips = jp.current_value_int();
            } else if (jp.current_value() == "system.animations") {
                jp.next(JsonParser::value_number);
                system_animations = jp.current_value_int();
            } else if (jp.current_value() == "system.show_presets") {
                jp.next(JsonParser::value_number);
                system_show_presets = jp.current_value_int();
            } else if (jp.current_value() == "system.show_toolbar") {
                jp.next(JsonParser::value_number);
                system_show_toolbar = jp.current_value_int();
            } else if (jp.current_value() == "system.show_rack") {
                jp.next(JsonParser::value_number);
                system_show_rack = jp.current_value_int();
            } else if (jp.current_value() == "system.midiout") {
                jp.next(JsonParser::value_number);
                system_midiout = jp.current_value_int();
            }
        }
        jp.next(JsonParser::end_object);
        jp.close();
    } catch (JsonException&) {
        gx_print_warning("main", "can't read/parse ui_rc");
    }
    i.close();
}

void CmdlineOptions::write_ui_vars() {
    ofstream o(Glib::build_filename(get_user_dir(), "ui_rc").c_str());
    if (o.fail()) {
	return;
    }
    JsonWriter jw(&o);
    try {
	jw.begin_object(true);
	jw.write_kv("system.mainwin_visible", mainwin_visible);
	jw.write_kv("system.mainwin_x", mainwin_x);
	jw.write_kv("system.mainwin_y", mainwin_y);
	jw.write_kv("system.mainwin_height", mainwin_height);
	jw.write_kv("system.mainwin_rack_height", window_height);
	jw.write_kv("system.preset_window_height", preset_window_height);
	jw.write_kv("system.mul_buffer", mul_buffer);
	jw.write_kv("ui.skin_name", skin.name);
	jw.write_kv("ui.latency_nowarn", no_warn_latency);
	jw.write_kv("system.order_rack_h", system_order_rack_h);
	jw.write_kv("system.show_value", system_show_value);
	jw.write_kv("system.show_tooltips", system_show_tooltips);
	jw.write_kv("system.animations", system_animations);
	jw.write_kv("system.show_presets", system_show_presets);
	jw.write_kv("system.show_toolbar", system_show_toolbar);
	jw.write_kv("system.show_rack", system_show_rack);
	jw.write_kv("system.midiout", system_midiout);
	jw.end_object(true);
	jw.close();
    } catch (JsonException&) {
	gx_print_warning("main", "can't write ui_rc");
    }
    o.close();
}

Glib::ustring CmdlineOptions::get_jack_output(unsigned int n) const {
    if (n >= jack_outputs.size()) {
	return "";
    }
    return jack_outputs.at(n);
}

string CmdlineOptions::get_opskin() {
    // GTK options: rc style (aka skin)
    string opskin("Style to use");

    // initialize number of skins. We just count the number of rc files
    unsigned int n = skin.skin_list.size();
    if (n < 1) {
        return opskin;
    }

    vector<Glib::ustring>::iterator it;

    for (it = skin.skin_list.begin(); it != skin.skin_list.end(); ++it) {
        opskin += ", '" + *it + "'";
    }
    return opskin;
}

static void log_terminal(const string& msg, GxLogger::MsgType tp, bool plugged) {
    const char *t;
    switch (tp) {
    case GxLogger::kInfo:    t = "I"; break;
    case GxLogger::kWarning: t = "W"; break;
    case GxLogger::kError:   t = "E"; break;
    default:       t = "?"; break;
    }
    if (!plugged) {
	cerr << t << " " << msg << endl;
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
	throw GxFatalError(
	    string("unknown argument on command line: ")+argv[1]);
    }
#endif
    if (clear) {
	if (!rcset.empty()) {
	    throw Glib::OptionError(
		Glib::OptionError::BAD_VALUE,
		_("-c and -r cannot be used together"));
	}
	skin.name = "";
    } else if (skin.name.empty()) {
	skin.set_default_skin_name();
    }
    if (nogui && liveplaygui) {
		throw Glib::OptionError(
	    Glib::OptionError::BAD_VALUE,
	    _("-N and -L cannot be used together"));
	}
    if (onlygui && !setbank.empty()) {
		throw Glib::OptionError(
	    Glib::OptionError::BAD_VALUE,
	    _("-G and -b cannot be used together"));
	}
    if (lterminal) {
	GxLogger::get_logger().signal_message().connect(
	    sigc::ptr_fun(log_terminal));
	if (nogui) {
	    GxLogger::get_logger().unplug_queue();
	}
    }

    make_ending_slash(builder_dir);
    make_ending_slash(style_dir);
    make_ending_slash(factory_dir);
    make_ending_slash(pixmap_dir);
    make_ending_slash(preset_dir);
    make_ending_slash(pluginpreset_dir);
    make_ending_slash(lv2_preset_dir);
    make_ending_slash(loop_dir);
    make_ending_slash(temp_dir);
    make_ending_slash(plugin_dir);

    skin.set_styledir(style_dir);
    unsigned int n = skin.skin_list.size();
    if (n < 1) {
        gx_print_fatal(_("main"), string(_("number of skins is 0")));
    }
    if (!rcset.empty()) {
	if (skin.is_in_list(rcset)) {
	    skin.name = rcset;
	} else {
	    throw Glib::OptionError(
		Glib::OptionError::BAD_VALUE,
		(boost::format(_("invalid style '%1%' on command line"))
		 % rcset).str());
	}
    }
    if (jack_outputs.size() > 2) {
	gx_print_warning(
	    _("main"),
	    _("Warning --> provided more than 2 output ports, ignoring extra ports"));
    }
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

/*
** encoding / decoding filenames
*/

static inline bool check_char(unsigned char c) {
    static const char *badchars = "/%?*<>\\:#&$'\"(){}[]~;`|.";
    if (c < 32) {
	return false;
    }
    for (const char *p = badchars; *p; p++) {
	if (c == *p) {
	    return false;
	}
    }
    return true;
}

std::string encode_filename(const std::string& s) {
   std::string res;
   res.reserve(s.size());
   for (unsigned int i = 0; i < s.size(); i++) {
      unsigned char c = s[i];
      if (!check_char(c)) {
	 res.append(1, '%');
	 static const unsigned char code[16] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
	 res.append(1, code[c / 16]);
	 res.append(1, code[c % 16]);
      } else {
	 res.append(1, c);
      }
   }
   return res;
}

static inline bool dct(unsigned char c, int &n) {
   if (c < '0') {
      return false;
   }
   if (c <= '9') {
      n = c - '0';
      return true;
   }
   if (c < 'a') {
      return false;
   }
   if (c <= 'f') {
      n = c - 'a';
      return true;
   }
   return false;
}

std::string decode_filename(const std::string& s) {
   std::string res;
   res.reserve(s.size());
   for (unsigned int i = 0; i < s.size(); i++) {
      unsigned char c = s[i];
      if (c == '%') {
	 int n1, n2;
	 if (s.size() - i < 3 || !dct(s[i+1],n1) || !dct(s[i+2],n2)) {
	    // error, don't do any decoding
	    return s;
	 }
	 res.push_back(n1*16 + n2);
	 i += 2;
      } else {
	 res.push_back(c);
      }
   }
   return res;
}


} /* end of gx_system namespace */
