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

#ifndef NDEBUG
#include <fenv.h>

#ifdef __i386__
#define FE_DENORM __FE_DENORM
inline void clear_fpu_status_bits() { __asm__ ("fnclex"); }
inline unsigned int get_fpu_status_bits() {
    unsigned int fpu_status __attribute__ ((__mode__ (__HI__)));
    __asm__("fnstsw %0" : "=m" (*&fpu_status));
	return fpu_status;
}
#else
inline void clear_fpu_status_bits() { feclearexcept(FE_ALL_EXCEPT); }
inline unsigned int get_fpu_status_bits() {
    fexcept_t flagp;
    int ret = fegetexceptflag(&flagp, FE_ALL_EXCEPT);
    assert(ret == 0);
    return flagp;
}
#endif //__i386__
#endif // !NDEBUG
#ifdef __SSE__

/* On Intel set FZ (Flush to Zero) and DAZ (Denormals Are Zero)
   flags to avoid costly denormals */
#ifdef __SSE3__
#include <pmmintrin.h>
inline void AVOIDDENORMALS() {
    _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
    _MM_SET_DENORMALS_ZERO_MODE(_MM_DENORMALS_ZERO_ON);
}
#else
#include <xmmintrin.h>
inline void AVOIDDENORMALS() { _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON); }
#endif //__SSE3__

#else

inline void _MM_SET_EXCEPTION_STATE(unsigned int __mask) {}
inline unsigned int _MM_GET_EXCEPTION_STATE(void) { return 0; }
inline void AVOIDDENORMALS() {}

#endif //__SSE__


/* constant defines */
#define ASCII_START (48)
#define GDK_NO_MOD_MASK (GdkModifierType)0
#define SYSTEM_OK   (0)


namespace gx_system {

/****************************************************************
 ** "atomic" value access
 */

inline void atomic_set(volatile int* p, int v) {
    g_atomic_int_set(p, v);
}

inline int atomic_get(volatile int& p) {
    return g_atomic_int_get(&p);
}

inline bool atomic_compare_and_exchange(volatile int *p, int oldv, int newv) {
    return g_atomic_int_compare_and_exchange(p, oldv, newv);
}

template <class T>
inline void atomic_set(T **p, T *v) {
    g_atomic_pointer_set(p, v);
}

template <class T>
inline void atomic_set_0(T **p) {
    g_atomic_pointer_set(p, 0);
}

template <class T>
inline T *atomic_get(T*& p) {
    return static_cast<T*>(g_atomic_pointer_get(&p));
}

template <class T>
inline bool atomic_compare_and_exchange(T **p, T *oldv, T *newv) {
    return g_atomic_pointer_compare_and_exchange(reinterpret_cast<void* volatile*>(p), oldv, newv);
}


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


struct Measure {
    Accum period;
    Accum duration;
    Accum duration1;
    Accum duration2;
    unsigned int FPUStatus1;
    unsigned int MXStatus1;
    unsigned int FPUStatus2;
    unsigned int MXStatus2;
    inline float ns2ms(int n) const { return n * 1e-6; }
    void reset();
    Measure() { reset(); }
    void print_accum(const Accum& accum, const char* prefix, bool verbose, int total = 0) const;
    void print(bool verbose) const;
};

class MeasureThreadsafe {
 private:
    Measure m[2];
    Measure *pmeasure;
    timespec t1s;
    timespec t1e;
    timespec t2s;
    timespec t1old;
    unsigned int FPUStatus;
    unsigned int MXStatus;
    inline Measure *access() { return atomic_get(pmeasure); }
    inline int ts_diff(const timespec& ts1, const timespec& ts2);
 public:
    MeasureThreadsafe();
    inline void start() {
	clear_fpu_status_bits();
	_MM_SET_EXCEPTION_STATE(0);
	clock_gettime(CLOCK_MONOTONIC, &t1s);
    }
    inline void pause() {
	clock_gettime(CLOCK_MONOTONIC, &t1e);
	FPUStatus = get_fpu_status_bits();
	MXStatus = _MM_GET_EXCEPTION_STATE();
    }
    inline void cont() {
	clear_fpu_status_bits();
	_MM_SET_EXCEPTION_STATE(0);
	clock_gettime(CLOCK_MONOTONIC, &t2s);
    }
    inline void stop();
    void print(bool verbose = false);
};

/* return time difference in ns, fail if > sec (doesn't fit int 32 bit int) */
inline int MeasureThreadsafe::ts_diff(const timespec& ts1, const timespec& ts2) {
    time_t df = ts1.tv_sec - ts2.tv_sec;
    if (abs(df) > 2) {
        return -1; // failed
    }
    return df * 1000000000 + (ts1.tv_nsec - ts2.tv_nsec);
}


inline void MeasureThreadsafe::stop() {
    Measure& m = *access();
    timespec n;
    clock_gettime(CLOCK_MONOTONIC, &n);
    m.FPUStatus2 |= get_fpu_status_bits();
    m.MXStatus2 |= _MM_GET_EXCEPTION_STATE();
    m.FPUStatus1 |= FPUStatus;
    m.MXStatus1 |= MXStatus;
    if (!(t1old.tv_sec == 0 && t1old.tv_nsec == 0)) {
        m.period.add(ts_diff(t1s, t1old));
    }
    t1old = t1s;
    m.duration1.add(ts_diff(t1e, t1s));
    m.duration2.add(ts_diff(n, t2s));
    m.duration.add(ts_diff(n, t1s));
}

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

/****************************************************************/

class PathList {
public:
    typedef std::list< Glib::RefPtr<Gio::File> > pathlist;
    typedef std::list< Glib::RefPtr<Gio::File> >::const_iterator iterator;
private:
    pathlist dirs;
public:
    PathList(const char *env_name = 0);
    void add(const string& d) { dirs.push_back(Gio::File::create_for_path(d)); }
    bool contains(const string& d) const;
    bool find_dir(string *d, const string& filename) const;
    size_t size() { return dirs.size(); }
    iterator begin() { return dirs.begin(); }
    iterator end() { return dirs.end(); }
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
    string path_to_program;
    bool version;
    bool clear;
    Glib::ustring jack_input;
    Glib::ustring jack_midi;
    Glib::ustring jack_instance;
    vector<Glib::ustring> jack_outputs;
    Glib::ustring jack_uuid;
    Glib::ustring jack_uuid2;
    bool jack_noconnect;
    Glib::ustring jack_servername;
    string load_file;
    string builder_dir;
    string style_dir;
    string factory_dir;
    string pixmap_dir;
    string user_dir;
    string old_user_dir;
    string preset_dir;
    string pluginpreset_dir;
    string plugin_dir;
    string sys_IR_dir;
    PathList IR_pathlist;
    Glib::ustring rcset;
    bool lterminal;
    bool a_save;
    static CmdlineOptions *instance;
    void make_ending_slash(string& dirpath);
    string get_opskin();
    friend CmdlineOptions& get_options();

public:
#ifndef NDEBUG
    bool dump_parameter;
#endif
    SkinHandling skin;
public:
    CmdlineOptions();
    ~CmdlineOptions();
    void process(int argc, char** argv);
    const string& get_path_to_program() const { return path_to_program; }
    string get_style_filepath(const string& basename) const { return style_dir + basename; }
    string get_pixmap_filepath(const string& basename) const { return pixmap_dir + basename; }
    string get_builder_filepath(const string& basename) const { return builder_dir + basename; }
    string get_user_filepath(const string& basename) const { return user_dir + basename; }
    string get_preset_filepath(const string& basename) const { return preset_dir + basename; }
    string get_plugin_filepath(const string& basename) const { return plugin_dir + basename; }
    string get_factory_filepath(const string& basename) const { return factory_dir + basename; }
    string get_pluginpreset_filepath(const string& id) const { return pluginpreset_dir + id; }
    const string& get_user_dir() const { return user_dir; }
    const string& get_old_user_dir() const { return old_user_dir; }
    const string& get_plugin_dir() const { return plugin_dir; }
    const string& get_preset_dir() const { return preset_dir; }
    const string& get_pluginpreset_dir() const { return pluginpreset_dir; }
    const string& get_factory_dir() const { return factory_dir; }
    const string& get_sys_IR_dir() const { return sys_IR_dir; }
    const Glib::ustring& get_rcset() const { return rcset; }
    const string& get_loadfile() const { return load_file; }
    const Glib::ustring& get_jack_instancename() const { return jack_instance; }
    const Glib::ustring& get_jack_uuid() const { return jack_uuid; }
    const Glib::ustring& get_jack_uuid2() const { return jack_uuid2; }
    const Glib::ustring& get_jack_midi() const { return jack_midi; }
    const Glib::ustring& get_jack_input() const { return jack_input; }
    const Glib::ustring& get_jack_servername() const { return jack_servername; }
    bool get_jack_noconnect() const { return jack_noconnect; }
    bool get_opt_auto_save() const { return a_save; }
    const PathList& get_IR_pathlist() const { return IR_pathlist; }
    Glib::ustring get_jack_output(unsigned int n) const;
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
    typedef sigc::signal<void, const string&, GxMsgType, bool> msg_signal;
    struct logmsg {
	string msg;
	GxMsgType msgtype;
	bool plugged;
	logmsg(string m, GxMsgType t, bool p): msg(m), msgtype(t), plugged(p) {}
    };
    list<logmsg> msglist;
    boost::mutex msgmutex;
    Glib::Dispatcher* got_new_msg;
    pthread_t ui_thread;
    msg_signal handlers;
    bool queue_all_msgs;
    string format(const char* func, const string& msg);
    void set_ui_thread();
    Logger();
    ~Logger();
    void write_queued();
    friend class LoggerGuard;
public:
    void unplug_queue();
    msg_signal& signal_message();
    void print(const char* func, const string& msg, GxMsgType msgtype);
    static Logger& get_logger();
    static void destroy();
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
    sigc::signal<void,string> message;
public:
    GxExit();
    ~GxExit();
    void set_ui_thread() { ui_thread = pthread_self(); }
    sigc::signal<void, bool>& signal_exit() { return exit_sig; }
    sigc::signal<void,string>& signal_msg() { return message; }
    void exit_program(string msg = "", int errcode = 1);
    void fatal_msg(const string& msg) { message(msg); exit_program(msg); }
    static GxExit& get_instance();
};


/****************************************************************
 ** misc function declarations
 */

int  gx_system_call(const string&, bool devnull = false, bool escape = false);
void strip(Glib::ustring& s);

template <class T>
inline string to_string(const T& t) {
    stringstream ss;
    ss << t;
    return ss.str();
}

} /* end of gx_system namespace */

#endif  // SRC_HEADERS_GX_SYSTEM_H_
