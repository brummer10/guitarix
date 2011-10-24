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
 */

/* ------- This is the System namespace ------- */

#pragma once

#ifndef SRC_HEADERS_GX_SYSTEM_H_
#define SRC_HEADERS_GX_SYSTEM_H_

#include <glibmm/optioncontext.h>   // NOLINT

#include <cmath>
#include <sstream>
#include <list>
#include <string>
#include <algorithm>
#include <boost/thread/mutex.hpp>
#include <glibmm/dispatcher.h>

/* constant defines */
#define ASCII_START (48)
#define GDK_NO_MOD_MASK (GdkModifierType)0
#define SYSTEM_OK   (0)


namespace gx_system {

/****************************************************************
 ** Measuring times
 */

#ifndef NDEBUG

class Accum {
 private:
    int n;
    int mn;
    int mx;
    float sx;
    float sx2;
 public:
    Accum() { reset(); }
    inline void reset() {
        n = 0;
        mn = 1e9;
        mx = 0;
        sx = 0;
        sx2 = 0;
    }
    void add(int diff);
    int count() const { return n; }
    float mean() const { return sx / n; }
    float stddev() const { return sqrt((n * sx2 - sx * sx) / (n * (n-1))); }
    float minimum() const { return mn; }
    float maximum() const { return mx; }
};

inline void Accum::add(int diff) {
    n += 1;
    sx += diff;
    sx2 += static_cast<float>(diff) * diff;
    mn = min(mn, diff);
    mx = max(mx, diff);
}


class Measure {
 private:
    Accum period;
    Accum duration;
    Accum duration1;
    Accum duration2;
    timespec t1;
    timespec t2;
    static int ts_diff(struct timespec ts1, struct timespec ts2);
    inline float ns2ms(int n) const { return n * 1e-6; }

 public:
    inline void reset() {
        period.reset();
        duration.reset();
        duration1.reset();
        duration2.reset();
        t1.tv_sec = 0;
        t1.tv_nsec = 0;
        t2.tv_sec = 0;
        t2.tv_nsec = 0;
    }
    Measure() { reset(); }
    void start_process();
    void pause_process();
    void cont_process();
    void stop_process();
    void print_accum(const Accum& accum, const char* prefix, bool verbose, int total = 0) const;
    void print(bool verbose) const;
};

inline void Measure::start_process() {
    timespec n;
    clock_gettime(CLOCK_MONOTONIC, &n);
    if (!(t1.tv_sec == 0 and t1.tv_nsec == 0)) {
        period.add(ts_diff(n, t1));
    }
    t1 = n;
}

inline void Measure::pause_process() {
    timespec n;
    clock_gettime(CLOCK_MONOTONIC, &n);
    duration1.add(ts_diff(n, t1));
}

inline void Measure::cont_process() {
    clock_gettime(CLOCK_MONOTONIC, &t2);
}

inline void Measure::stop_process() {
    timespec n;
    clock_gettime(CLOCK_MONOTONIC, &n);
    duration2.add(ts_diff(n, t2));
    duration.add(ts_diff(n, t1));
}

class MeasureThreadsafe {
 private:
    Measure *pmeasure;
    Measure m[2];
    inline Measure *access() { return reinterpret_cast<Measure*>(g_atomic_pointer_get(&pmeasure)); }
 public:
    MeasureThreadsafe(): pmeasure(m) {}
    inline void start() { access()->start_process(); }
    inline void pause() { access()->pause_process(); }
    inline void cont() { access()->cont_process(); }
    inline void stop() { access()->stop_process(); }
    void print(bool verbose = false);
};

extern MeasureThreadsafe measure;

void add_time_measurement();

inline void measure_start() { measure.start(); }
inline void measure_pause() { measure.pause(); }
inline void measure_cont() { measure.cont(); }
inline void measure_stop()  { measure.stop(); }

#else

inline void measure_start() {}
inline void measure_pause() {}
inline void measure_cont() {}
inline void measure_stop()  {}

#endif

/****************************************************************/

class SkinHandling {
public:
    vector<string>   skin_list;
    SkinHandling(const string& styledir)
	: skin_list() { set_styledir(styledir); }
    void set_styledir(const string& styledir);
    bool is_in_list(const string& name);
};

/****************************************************************
 ** CmdlineParser
 */

class CmdlineOptions: public Glib::OptionContext, boost::noncopyable {
private:
    Glib::OptionGroup main_group;
    Glib::OptionGroup optgroup_style;
    Glib::OptionGroup optgroup_jack;
    Glib::OptionGroup optgroup_file;
    Glib::OptionGroup optgroup_debug;
    bool version;
    bool clear;
    Glib::ustring jack_input;
    Glib::ustring jack_midi;
    Glib::ustring jack_instance;
    vector<Glib::ustring> jack_outputs;
    Glib::ustring jack_uuid;
    Glib::ustring jack_uuid2;
    string load_file;
    string builder_dir;
    string style_dir;
    string pixmap_dir;
    string user_dir;
    string plugin_dir;
    Glib::ustring rcset;
    bool lterminal;
    static CmdlineOptions *instance;
    void make_ending_slash(string& dirpath);
    string get_opskin();
    friend CmdlineOptions& get_options();

public:
    SkinHandling skin;
public:
    CmdlineOptions();
    ~CmdlineOptions();
    void process(int argc, char** argv);
    string get_style_filepath(const string& basename) { return style_dir + basename; }
    string get_pixmap_filepath(const string& basename) { return pixmap_dir + basename; }
    string get_builder_filepath(const string& basename) { return builder_dir + basename; }
    string get_user_filepath(const string& basename) { return user_dir + basename; }
    string get_factory_filepath(const string& basename) {
	return get_style_filepath(basename); } //FIXME should be changed
    const string& get_user_dir() { return user_dir; }
    const string& get_plugin_dir() { return plugin_dir; }
    const Glib::ustring& get_rcset() { return rcset; }
    const string& get_loadfile() { return load_file; }
    const Glib::ustring& get_jack_instancename() { return jack_instance; }
    const Glib::ustring& get_jack_uuid() { return jack_uuid; }
    const Glib::ustring& get_jack_uuid2() { return jack_uuid2; }
    const Glib::ustring& get_jack_midi() { return jack_midi; }
    const Glib::ustring& get_jack_input() { return jack_input; }
    Glib::ustring get_jack_output(unsigned int n);
};

inline CmdlineOptions& get_options() {
    assert(CmdlineOptions::instance);
    return *CmdlineOptions::instance;
}

/****************************************************************
 ** Logging
 */

typedef enum {
    kInfo,
    kWarning,
    kError,
    kMessageTypeCount // just count, must be last
} GxMsgType;

class Logger: public sigc::trackable {
private:
    typedef sigc::signal<void, const string&, GxMsgType> msg_signal;
    struct logmsg {
	string msg;
	GxMsgType msgtype;
	logmsg(string m, GxMsgType t): msg(m), msgtype(t) {}
    };
    list<logmsg> msglist;
    boost::mutex msgmutex;
    Glib::Dispatcher* got_new_msg;
    pthread_t ui_thread;
    msg_signal handlers;
    string format(const char* func, const string& msg);
    void set_ui_thread();
    Logger();
    ~Logger();
public:
    msg_signal& signal_message();
    void write_queued();
    void print(const char* func, const string& msg, GxMsgType msgtype);
    static Logger& get_logger();
};

void  gx_print_logmsg(const char*, const string&, GxMsgType);
void  gx_print_warning(const char*, const string&);
inline void gx_print_warning(const char* fnc, const boost::basic_format<char>& msg) {
    gx_print_warning(fnc, msg.str());
}
void  gx_print_error(const char*, const string&);
inline void gx_print_error(const char* fnc, const boost::basic_format<char>& msg) {
    gx_print_error(fnc, msg.str());
}
void  gx_print_fatal(const char*, const string&);
inline void gx_print_fatal(const char* fnc, const boost::basic_format<char>& msg) {
    gx_print_fatal(fnc, msg.str());
}
void  gx_print_info(const char*, const string&);
inline void gx_print_info(const char* fnc, const boost::basic_format<char>& msg) {
    gx_print_info(fnc, msg.str());
}

class GxFatalError: public exception {
private:
    string msg;
public:
    virtual const char* what() const throw() {
	return msg.c_str();
    }
    GxFatalError(string m): msg(m) {}
    GxFatalError(boost::basic_format<char>& m): msg(m.str()) {}
    ~GxFatalError() throw();
};


/****************************************************************
 ** class GxExit
 */

class GxExit {
private:
    sigc::signal<void, bool> exit_sig;
    pthread_t ui_thread;
public:
    GxExit();
    ~GxExit();
    void set_ui_thread() { ui_thread = pthread_self(); }
    sigc::signal<void, bool>& signal_exit() { return exit_sig; }
    void exit_program(string msg = "", int errcode = 1);
    static GxExit& get_instance();
};


/****************************************************************
 ** misc function declarations
 */

bool  gx_start_jack();
int   gx_system_call(const char*,
                     const char*,
                     const bool devnull = false,
                     const bool escape  = false);
int   gx_system_call(const char*,
                     const string&,
                     const bool devnull = false,
                     const bool escape  = false);
int   gx_system_call(const string&,
                     const char*,
                     const bool devnull = false,
                     const bool escape  = false);

template <class T>
inline string to_string(const T& t) {
    stringstream ss;
    ss << t;
    return ss.str();
}

} /* end of gx_system namespace */

#endif  // SRC_HEADERS_GX_SYSTEM_H_
