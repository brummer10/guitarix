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

#include <gtk/gtk.h>
#include <glibmm/optioncontext.h>   // NOLINT

#include <cmath>
#include <sstream>
#include <list>
#include <string>
#include <algorithm>


/* constant defines */
#define ASCII_START (48)
#define GDK_NO_MOD_MASK (GdkModifierType)0

enum {
    JACK_INP,
    JACK_OUT1,
    JACK_OUT2,
    JACK_MIDI,
    RC_STYLE,
    JACK_UUID,
    JACK_UUID2,
    LOAD_FILE,
    NUM_SHELL_VAR,
};

namespace gx_system {

/* message handling */
typedef enum {
    kInfo,
    kWarning,
    kError,
    kMessageTypeCount // just count, must be last
} GxMsgType;


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
    timespec t;
    static int ts_diff(struct timespec ts1, struct timespec ts2);
    inline float ns2ms(int n) { return n * 1e-6; }

 public:
    inline void reset() {
        period.reset();
        duration.reset();
        t.tv_sec = 0;
        t.tv_nsec = 0;
    }
    Measure() { reset(); }
    void start_process();
    void stop_process();
    void print_accum(Accum& accum, const char* prefix, bool verbose, int total = 0);
    void print(bool verbose);
};

inline void Measure::start_process() {
    timespec n;
    clock_gettime(CLOCK_MONOTONIC, &n);
    if (!(t.tv_sec == 0 and t.tv_nsec == 0)) {
        period.add(ts_diff(n, t));
    }
    t = n;
}

inline void Measure::stop_process() {
    timespec n;
    clock_gettime(CLOCK_MONOTONIC, &n);
    duration.add(ts_diff(n, t));
}

class MeasureThreadsafe {
 private:
    Measure *pmeasure;
    Measure m[2];
    inline Measure *access() { return reinterpret_cast<Measure*>(g_atomic_pointer_get(&pmeasure)); }
 public:
    MeasureThreadsafe(): pmeasure(m) {}
    inline void start() { access()->start_process(); }
    inline void stop() { access()->stop_process(); }
    void print(bool verbose = false);
};

extern MeasureThreadsafe measure;

void add_time_measurement();

inline void measure_start() { measure.start(); }
inline void measure_stop()  { measure.stop(); }

#else

inline void measure_start() {}
inline void measure_stop()  {}

#endif

class SystemVars {
 public:
    static const int                      SYSTEM_OK;

    static const char*                    gx_head_dir;
    static const char*                    jcapsetup_file;
    static const char*                    jcapfile_wavbase;

    static const string                   gx_pixmap_dir;
    static const string                   gx_user_dir;

    /* shell variable names */
    static const char*                    shell_var_name[NUM_SHELL_VAR];
    
    bool                                  is_session;
    string                                rcpath;
    string                                gx_style_dir;
    string                                gx_builder_dir;

    void                                  sysvar_init();
};

extern SystemVars sysvar;

/****************************************************************
 ** CmdlineParser
 */

class CmdlineParser {
private:
    int& argc;
    char**& argv;
    bool version;
    bool clear;
    Glib::ustring rcset;
    Glib::ustring jack_input;
    Glib::ustring jack_midi;
    vector<Glib::ustring> jack_outputs;
    Glib::ustring jack_uuid;
    Glib::ustring jack_uuid2;
    string load_file;
    string builder_dir;
    string style_dir;
    bool lterminal;
    string get_opskin();
public:
    string plugin_dir;
    string optvar[NUM_SHELL_VAR];
public:
    CmdlineParser(int& argc_, char**& argv_);
    void process_early();
    void process();
    void set_override();
};

/****************************************************************
 ** misc function declarations
 */

void  gx_print_logmsg(const char*, const string&, GxMsgType);
void  gx_print_warning(const char*, const string&);
void  gx_print_error(const char*, const string&);
void  gx_print_fatal(const char*, const string&);
void  gx_print_info(const char*, const string&);

void  gx_process_cmdline_options(int&, char**&, string*);
void  gx_set_override_options(string* optvar);
void  gx_assign_shell_var(const char*, string&);
bool  gx_shellvar_exists(const string&);
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
//  int   gx_system_call(const string&,
//                      const string&,
//                      const bool devnull = false,
//                      const bool escape  = false);

extern list<string> jack_connection_lists[7];

bool  gx_version_check();
int   gx_pixmap_check();
void  gx_signal_handler(int sig);
gboolean gx_ladi_handler(gpointer);
void  gx_abort(void* arg);
void  gx_log_window(GtkWidget*, gpointer null);
void  gx_nospace_in_name(string& presname, const char* subs = "-");
void  gx_destroy_event();
void  gx_clean_exit(GtkWidget*, gpointer);

/* wrapper that takes an int and returns a string */
void gx_IntToString(int i, string & s);
const string& gx_i2a(int i);
/* ---------------------------------------------------------------- */
} /* end of gx_system namespace */

#endif  // SRC_HEADERS_GX_SYSTEM_H_

