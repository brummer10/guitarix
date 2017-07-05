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
#ifndef _PMMINTRIN_H_INCLUDED
#include <pmmintrin.h>
#endif //ndef
inline void AVOIDDENORMALS() {
    _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
    _MM_SET_DENORMALS_ZERO_MODE(_MM_DENORMALS_ZERO_ON);
}
#else
#ifndef _XMMINTRIN_H_INCLUDED
#include <xmmintrin.h>
#endif //ndef
inline void AVOIDDENORMALS() { _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON); }
#endif //__SSE3__

#else
#ifndef _XMMINTRIN_H_INCLUDED
inline void _MM_SET_EXCEPTION_STATE(unsigned int __mask) {}
inline unsigned int _MM_GET_EXCEPTION_STATE(void) { return 0; }
#endif //ndef
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

inline void atomic_set(volatile unsigned int* p, unsigned int v) {
    g_atomic_int_set(reinterpret_cast<volatile int*>(p), v);
}

inline int atomic_get(volatile int& p) {
    return g_atomic_int_get(&p);
}

inline unsigned int atomic_get(volatile unsigned int& p) {
    return g_atomic_int_get(reinterpret_cast<volatile int*>(&p));
}

inline void atomic_inc(volatile int* p) {
    g_atomic_int_inc(p);
}

inline void atomic_inc(volatile unsigned int* p) {
    g_atomic_int_inc(reinterpret_cast<volatile int*>(p));
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
    float stddev() const { return std::sqrt((n * sx2 - sx * sx) / (n * (n-1))); }
    float minimum() const { return mn; }
    float maximum() const { return mx; }
};

inline void Accum::add(int diff) {
    n += 1;
    sx += diff;
    sx2 += static_cast<float>(diff) * diff;
    mn = std::min(mn, diff);
    mx = std::max(mx, diff);
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
    if (std::abs(df) > 2) {
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
private:
    Glib::ustring empty;
public:
    std::vector<Glib::ustring>   skin_list;
    SkinHandling(const std::string& styledir)
	: skin_list() { set_styledir(styledir); }
    void set_styledir(const std::string& styledir);
    bool is_in_list(const std::string& name);
    const Glib::ustring& operator[](unsigned int idx);
    unsigned int index(const Glib::ustring& name);
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
    void add(const std::string& d) { dirs.push_back(Gio::File::create_for_path(d)); }
    bool contains(const std::string& d) const;
    bool find_dir(std::string *d, const std::string& filename) const;
    size_t size() { return dirs.size(); }
    iterator begin() { return dirs.begin(); }
    iterator end() { return dirs.end(); }
};


/****************************************************************/

class PrefixConverter {
public:
    typedef std::map<char,std::string> symbol_path_map;
private:
    symbol_path_map dirs;
public:
    PrefixConverter(): dirs() {}
    ~PrefixConverter() {}
    std::string replace_symbol(const std::string& dir) const;
    std::string replace_path(const std::string& dir) const;
    void add(char s, const std::string& d);
};


/*****************************************************************
 ** class DirectoryListing
 */

class FileName {
public:
    std::string filename;
    Glib::ustring displayname;
    FileName(const std::string& filename_, const Glib::ustring& displayname_)
	: filename(filename_), displayname(displayname_) {}
};

class IRFileListing {
public:
private:
    std::vector<FileName> listing;
public:
    IRFileListing(const std::string& path);
    ~IRFileListing() {}
    std::vector<FileName>& get_listing() { return listing; }
};

void list_subdirs(PathList pl, std::vector<FileName>& dirs);

/****************************************************************
 ** class CmdlineOptions
 */

#define RPCPORT_DEFAULT (-2)
#define RPCPORT_NONE (-1)

class BasicOptions: boost::noncopyable {
private:
    std::string user_dir;
    std::string user_IR_dir;
    std::string sys_IR_dir;
    PathList IR_pathlist;
    PrefixConverter IR_prefixmap;
    static BasicOptions *instance;
protected:
    std::string builder_dir;

private:
    friend BasicOptions& get_options();
protected:
    static void make_ending_slash(std::string& dirpath);
public:
    BasicOptions();
    ~BasicOptions();
    std::string get_user_filepath(const std::string& basename) const { return user_dir + basename; }
    std::string get_user_ir_filepath(const std::string& basename) const { return user_IR_dir + basename; }
    std::string get_builder_filepath(const std::string& basename) const { return builder_dir + basename; }
    const std::string& get_user_dir() const { return user_dir; }
    const std::string& get_user_IR_dir() const { return user_IR_dir; }
    const std::string& get_sys_IR_dir() const { return sys_IR_dir; }
    const PathList& get_IR_pathlist() const { return IR_pathlist; }
    const PrefixConverter& get_IR_prefixmap() const { return IR_prefixmap; }
};

class CmdlineOptions: public BasicOptions, public Glib::OptionContext {
private:
    Glib::OptionGroup main_group;
    Glib::OptionGroup optgroup_style;
    Glib::OptionGroup optgroup_jack;
    Glib::OptionGroup optgroup_overload;
    Glib::OptionGroup optgroup_file;
    Glib::OptionGroup optgroup_debug;
    std::string path_to_program;
    bool version;
    bool clear;
    Glib::ustring jack_input;
    Glib::ustring jack_midi;
    Glib::ustring jack_instance;
    std::vector<Glib::ustring> jack_outputs;
    Glib::ustring jack_uuid;
    Glib::ustring jack_uuid2;
    bool jack_noconnect;
    Glib::ustring jack_servername;
    std::string load_file;
    std::string style_dir;
    std::string factory_dir;
    std::string pixmap_dir;
    std::string old_user_dir;
    std::string preset_dir;
    std::string pluginpreset_dir;
    std::string lv2_preset_dir;
    std::string temp_dir;
    std::string plugin_dir;
    std::string loop_dir;
    Glib::ustring rcset;
    bool nogui;
    int rpcport;
    Glib::ustring rpcaddress;
    bool onlygui;
    bool liveplaygui;
    bool mute;
    Glib::ustring setbank;
    Glib::ustring tuner_tet;
    Glib::ustring tuner_ref;
    int sporadic_overload;
    int idle_thread_timeout;
    bool convolver_watchdog;
    bool xrun_watchdog;
    bool lterminal;
    bool a_save;
    bool auto_save;
    std::string get_opskin();
    void read_ui_vars();
    void write_ui_vars();

public:
#ifndef NDEBUG
    bool dump_parameter;
#endif
    SkinHandling skin;

    // saved in ui_rc:
    int mainwin_x;
    int mainwin_y;
    int mainwin_height;
    int window_height;
    int preset_window_height;
    int mul_buffer;
    Glib::ustring skin_name;
    bool no_warn_latency;
    bool system_order_rack_h;
    bool system_show_value;
    bool system_show_tooltips;
    bool system_animations;
    bool system_show_presets;
    bool system_show_toolbar;
    bool system_show_rack;
    bool reload_lv2_presets;

public:
    CmdlineOptions();
    ~CmdlineOptions();
    void process(int argc, char** argv);
    const std::string& get_path_to_program() const { return path_to_program; }
    std::string get_style_filepath(const std::string& basename) const { return style_dir + basename; }
    std::string get_pixmap_filepath(const std::string& basename) const { return pixmap_dir + basename; }
    std::string get_preset_filepath(const std::string& basename) const { return preset_dir + basename; }
    std::string get_plugin_filepath(const std::string& basename) const { return plugin_dir + basename; }
    std::string get_factory_filepath(const std::string& basename) const { return factory_dir + basename; }
    std::string get_temp_filepath(const std::string& basename) const { return temp_dir + basename; }
    std::string get_pluginpreset_filepath(const std::string& id, bool factory) const {
	return (factory ? factory_dir : pluginpreset_dir) + id; }
    std::string get_lv2_preset_filepath(const std::string& id) const {
	return (lv2_preset_dir) + id; }
    const std::string& get_old_user_dir() const { return old_user_dir; }
    const std::string& get_plugin_dir() const { return plugin_dir; }
    const std::string& get_preset_dir() const { return preset_dir; }
    const std::string& get_pluginpreset_dir() const { return pluginpreset_dir; }
    const std::string& get_lv2_preset_dir() const { return lv2_preset_dir; }
    const std::string& get_loop_dir() const { return loop_dir; }
    const std::string& get_temp_dir() const { return temp_dir; }
    const std::string& get_factory_dir() const { return factory_dir; }
    std::string get_ladspa_config_filename() const { return get_user_filepath("ladspa_defs.js"); }
    std::string get_online_config_filename() const { return get_user_filepath("musical-artifacts.js"); }
    const Glib::ustring& get_rcset() const { return rcset; }
    bool get_clear_rc() const { return clear; }
    bool get_nogui() const { return nogui; }
    bool get_liveplaygui() const { return liveplaygui; }
    bool get_mute() const { return mute; }
    const Glib::ustring& get_setbank() { return setbank; }
    const Glib::ustring& get_tuner_tet() { return tuner_tet; }
    const Glib::ustring& get_tuner_ref() { return tuner_ref; }
    int get_rpcport() const { return rpcport; }
    void set_rpcport(int port) { rpcport = port; }
    const Glib::ustring& get_rpcaddress() { return rpcaddress; }
    void set_rpcaddress(const Glib::ustring& address) { rpcaddress = address; }
    const std::string& get_loadfile() const { return load_file; }
    const Glib::ustring& get_jack_instancename() const { return jack_instance; }
    const Glib::ustring& get_jack_uuid() const { return jack_uuid; }
    const Glib::ustring& get_jack_uuid2() const { return jack_uuid2; }
    const Glib::ustring& get_jack_midi() const { return jack_midi; }
    const Glib::ustring& get_jack_input() const { return jack_input; }
    const Glib::ustring& get_jack_servername() const { return jack_servername; }
    bool get_jack_noconnect() const { return jack_noconnect; }
    bool get_opt_save_on_exit() const { return a_save; }
    bool get_opt_autosave() const { return auto_save; }
    Glib::ustring get_jack_output(unsigned int n) const;
    int get_idle_thread_timeout() const { return idle_thread_timeout; }
    int get_sporadic_overload() const { return sporadic_overload; }
    bool get_xrun_watchdog() const { return xrun_watchdog; }
    bool get_convolver_watchdog() const { return convolver_watchdog; }
};

inline BasicOptions& get_options() {
    assert(BasicOptions::instance);
    return *BasicOptions::instance;
}


/****************************************************************
 ** misc function declarations
 */

int  gx_system_call(const std::string&, bool devnull = false, bool escape = false);
void strip(Glib::ustring& s);

template <class T>
inline std::string to_string(const T& t) {
    std::stringstream ss;
    ss << t;
    return ss.str();
}

std::string encode_filename(const std::string& s);
std::string decode_filename(const std::string& s);

} /* end of gx_system namespace */

#endif  // SRC_HEADERS_GX_SYSTEM_H_
