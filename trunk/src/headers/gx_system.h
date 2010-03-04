/*
 * Copyright (C) 2009, 2010 Hermann Meyer, James Warden, Andreas Degert
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
 */

/* ------- This is the System namespace ------- */

#pragma once

/* constant defines */
#define ASCII_START (48)
#define GDK_NO_MOD_MASK (GdkModifierType)0

#define JACK_INP      (0)
#define JACK_OUT1     (1)
#define JACK_OUT2     (2)
#define JACK_MIDI     (3)
#define RC_STYLE      (4)

#define NUM_SHELL_VAR (5)

namespace gx_system
{
/* classes for reading and writing JSON files */
class JsonException: public exception
{
private:
	string what_str;
public:
	JsonException(const char* desc);
	~JsonException() throw() { }
	virtual const char* what() const throw() { return what_str.c_str(); }
};

class JsonWriter
{
private:
	ostream &os;
	bool first;
	bool deferred_nl;
	string indent;
	void snl(bool v) { deferred_nl = v; }
	void komma();
	void space();
	void iplus();
	void iminus();
public:
	JsonWriter(ostream& o);
	~JsonWriter() { close(); }
	bool good() { return os.good(); }
	void flush();
	void close() { if (deferred_nl) os << endl; }
	void write(float v, bool nl=false);
	void write(double v, bool nl=false);
	void write(int i, bool nl=false);
	void write(unsigned int i, bool nl=false);
	void write(const char* p, bool nl=false);
	void write(string s, bool nl=false) { write(s.c_str(), nl); }
	void write_lit(string s, bool nl=false);
	void begin_object(bool nl=false);
	void end_object(bool nl=false);
	void begin_array(bool nl=false);
	void end_array(bool nl=false);
	void write_key(const char* p, bool nl=false);
	void write_key(string p, bool nl=false);
	void newline() { snl(true); }
};

class JsonParser
{
public:
	JsonParser(istream& i);
	enum token {
		no_token, end_token, begin_object, end_object, begin_array, end_array,
		value_string, value_number, value_key };
	static const char* token_names[];
	bool good() { return is.good(); }
	token next(token expect=no_token);
	token peek() { return next_tok; }
	void check_expect(token expect) { if (cur_tok != expect) throw_unexpected(expect); }
	inline string current_value() const { return str; }
	int current_value_int() { return atoi(str.c_str()); }
	float current_value_float() { istringstream b(str); float f; b >> f; return f; }
	double current_value_double() { istringstream b(str); double d; b >> d; return d; }
	void copy_object(JsonWriter& jw);
	void skip_object();
private:
	istream& is;
	int depth;
	token cur_tok;
	string str;
	bool nl;
	int next_depth;
	token next_tok;
	string next_str;
	const char* readcode();
	string readstring();
	string readnumber(char c);
	void read_next();
	void throw_unexpected(token expect);
};

void writeHeader(JsonWriter& jw);
bool readHeader(JsonParser& jp, int *major=0, int *minor=0);
void write_preset(JsonWriter& w, bool write_midi = true);
void read_preset(JsonParser &jp);
bool saveStateToFile();
bool recallState();

// file format versions
const int majorversion = 1;
const int minorversion = 0;

/****************************************************************
 ** Measuring times
 */

#ifndef NDEBUG

class Accum
{
private:
	int n;
	int mn;
	int mx;
	float sx;
	float sx2;
public:
	inline void reset() { n = 0; mn = 1e9; mx = 0; sx = 0; sx2 = 0; }
	void add(int diff);
	int count() const { return n; }
	float mean() const { return sx / n; }
	float stddev() const { return sqrt((n * sx2 - sx * sx) / (n * (n-1))); }
	float minimum() const { return mn; }
	float maximum() const { return mx; }
};

inline void Accum::add(int diff)
{
	n += 1;
	sx += diff;
	sx2 += float(diff) * diff;
	mn = min(mn, diff);
	mx = max(mx, diff);
}


class Measure
{
private:
	typedef unsigned long long ts_type;
	Accum period;
	Accum duration;
	ts_type t;
	static inline void rdtscll(ts_type& val)
		{ __asm__ __volatile__ ("rdtsc" : "=A" (val)); }
	static inline int diff(ts_type t1, ts_type t2) { return (signed int)(t1 - t2); }
	static float ts_diff(struct timespec ts1, struct timespec ts2);

public:
	inline void reset() { period.reset(); duration.reset(); t = 0; }
	Measure() { reset(); }
	static float calibrate();
	void start_process();
	void stop_process();
	void print_accum(Accum& accum, const char* prefix, float scale, bool verbose, float total=0);
	void print(float scale, bool verbose);
};

inline void Measure::start_process()
{
	ts_type n;
	rdtscll(n);
	if (t != 0) {
		period.add(diff(n, t));
	}
	t = n;
}
	
inline void Measure::stop_process()
{
	ts_type n;
	rdtscll(n);
	duration.add(diff(n, t));
}

class MeasureThreadsafe
{
private:
	Measure *pmeasure;
	Measure m[2];
	float scale;
	inline Measure *access() { return (Measure*)g_atomic_pointer_get(&pmeasure); }
public:
	MeasureThreadsafe(): pmeasure(m), scale(Measure::calibrate()) {}
	inline void start() { access()->start_process(); }
	inline void stop() { access()->stop_process(); }
	void print(bool verbose=false);
};

extern MeasureThreadsafe measure;

void add_time_measurement();

inline void measure_start() { measure.start(); }
inline void measure_stop()  { measure.stop(); }

#else

inline void measure_start() {}
inline void measure_stop()  {}

#endif


/****************************************************************
 ** misc function declarations
 */

void  gx_print_logmsg (const char*, const string&, GxMsgType);
void  gx_print_warning(const char*, const string&);
void  gx_print_error  (const char*, const string&);
void  gx_print_fatal  (const char*, const string&);
void  gx_print_info(const char*, const string&);

void  gx_process_cmdline_options(int&, char**&, string*);
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
// 		             const string&,
// 		             const bool devnull = false,
// 		             const bool escape  = false);

extern list<string> jack_connection_lists[4];

bool  gx_version_check();
int   gx_pixmap_check();
void  gx_signal_handler(int);
gboolean gx_ladi_handler(gpointer);
void  gx_abort(void* arg);
void  gx_log_window(GtkWidget*, gpointer);
void  gx_nospace_in_name(string& presname, const char* subs = "-");
void  gx_destroy_event();
void  gx_clean_exit(GtkWidget*, gpointer);

/* wrapper that takes an int and returns a string */
void gx_IntToString(int i, string & s);
const string& gx_i2a(int);

/* ---------------------------------------------------------------- */
} /* end of gx_system namespace */
