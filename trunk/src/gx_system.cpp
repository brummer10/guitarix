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
 * ---------------------------------------------------------------------------
 *
 *    This is the guitarix system interface
 *
 * ----------------------------------------------------------------------------
 */

#include <sys/stat.h>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <jack/jack.h>
#include <glibmm/optioncontext.h>
#include "guitarix.h"

using namespace gx_engine;
using namespace gx_jack;
using namespace gx_preset;

namespace gx_system
{

/****************************************************************
 ** JsonWriter
 */

JsonWriter::JsonWriter(ostream &o):
	os(o),
	first(true),
	deferred_nl(false),
	indent("")
{
}

inline void JsonWriter::komma()
{
	if (first)
		first = false;
	else if (!deferred_nl)
		os << ", ";
	else
		os << ",";
	flush();
}

inline void JsonWriter::space()
{
	if (first)
		first = false;
	else if (!deferred_nl)
		os << " ";
	flush();
}

inline void JsonWriter::iplus()
{
	indent += "  ";
}

inline void JsonWriter::iminus()
{
	if (!indent.empty()) {
		indent = indent.substr(0, indent.size() - 2);
	}
}

void JsonWriter::write(float v, bool nl)
{
	komma();
	os << v;
	snl(nl);
}

void JsonWriter::write(double v, bool nl)
{
	komma();
	os << v;
	snl(nl);
}

void JsonWriter::write(int i, bool nl)
{
	komma();
	os << i;
	snl(nl);
}

void JsonWriter::write(unsigned int i, bool nl)
{
	komma();
	os << i;
	snl(nl);
}

void JsonWriter::write_lit(string s, bool nl)
{
	komma();
	os << s;
	snl(nl);
}

void JsonWriter::write(const char* p, bool nl)
{
	komma();
	os << '"';
	while (*p) {
		switch (*p) {
		case '\\': case '"': os << '\\'; break;
		case '\b': os << '\\'; os << 'b'; continue;
		case '\f': os << '\\'; os << 'f'; continue;
		case '\n': os << '\\'; os << 'n'; continue;
		case '\r': os << '\\'; os << 'r'; continue;
		case '\t': os << '\\'; os << 't'; continue;
		}
		os << *p++;
	}
	os << '"';
	snl(nl);
}

void JsonWriter::begin_object(bool nl)
{
	komma();
	os << '{';
	snl(nl);
	first = true;
	iplus();
}

void JsonWriter::end_object(bool nl)
{
	iminus();
	flush();
	os << '}';
	snl(nl);
}

void JsonWriter::begin_array(bool nl)
{
	komma();
	os << '[';
	snl(nl);
	first = true;
	iplus();
}

void JsonWriter::end_array(bool nl)
{
	iminus();
	flush();
	first = false;
	os << ']';
	snl(nl);
}

void JsonWriter::write_key(const char* p, bool nl)
{
	write(p, nl);
	os << ": ";
	first = true;
}

void JsonWriter::write_key(string p, bool nl)
{
	write(p, nl);
	os << ": ";
	first = true;
}

// called before output of next element
void JsonWriter::flush()
{
	if (deferred_nl) {
		os << endl;
		deferred_nl = false;
		os << indent;
	}
}


/****************************************************************
 ** JsonParser
 */

const char* JsonParser::token_names[] = {
	"no_token", "end_token", "begin_object", "end_object",
	"begin_array", "end_array",	"value_string", "value_number",
	"value_key" };

JsonException::JsonException(const char* desc)
{
	what_str = string("Json parse error: ") + desc;
}

JsonParser::JsonParser(istream& i):
	is(i),
	depth(0),
	cur_tok(no_token),
	nl(false),
	next_depth(0),
	next_tok(no_token)
{
}

void JsonParser::throw_unexpected(token expect)
{
	ostringstream b;
	b << "unexpected token: " << token_names[cur_tok]
	  << " (expected: " << token_names[expect] << ")"
	  << endl;
	throw JsonException(b.str().c_str());
}

const char* unicode2utf8(unsigned int input)
{
	const int maskbits   = 0x3F;
	const int maskbyte   = 0x80;
	const int mask2bytes = 0xC0;
	const int mask3bytes = 0xE0;
	static char result[4];
	int n = 0;
	// 0xxxxxxx
	if (input < 0x80) {
		result[n++] = (char)input;
	}
	// 110xxxxx 10xxxxxx
	else if (input < 0x800) {
		result[n++] = ((char)(mask2bytes | (input >> 6)));
		result[n++] = ((char)(maskbyte | (input & maskbits)));
	}
	// 1110xxxx 10xxxxxx 10xxxxxx
	else {
		result[n++] = ((char)(mask3bytes | (input >> 12)));
		result[n++] = ((char)(maskbyte | ((input >> 6) & maskbits)));
		result[n++] = ((char)(maskbyte | (input & maskbits)));
	}
	result[n++] = '\0';
	return result;
}

const char* JsonParser::readcode()
{
	int code = 0;
	for (int i = 0; i < 4; i++) {
		int n = is.get();
		if (!is.good())
			throw JsonException("eof");
		if ('0' <= n && n <= '9')
			n = n - '0';
		else
			n = 10 + (toupper(n) - 'A');
		code = code * 16 + n;
	}
	return unicode2utf8(code);
}

string JsonParser::readstring()
{
	ostringstream os("");
	char c;
	do {
		is.get(c);
		if (!is.good())
			return "";
		if (c == '\\') {
			is.get(c);
			if (!is.good())
				return "";
			switch (c) {
			case 'b': os << '\b'; break;
			case 'f': os << '\f'; break;
			case 'n': os << '\n'; break;
			case 'r': os << '\r'; break;
			case 't': os << '\t'; break;
			case 'u': os << readcode(); break;
			default: is.get(c); os << c; break;
			}
		}
		else if (c == '"')
			return os.str();
		else
			os << c;
	} while (true);
}

string JsonParser::readnumber(char c)
{
	ostringstream os("");
	do {
		os << c;
		c = is.peek();
		switch (c) {
		case '+': case '-': case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9': case 'e': case 'E':
		case '.':
			break;
		default:
			return os.str();
		}
		is.get(c);
	} while (is.good());
	return "";
}

void JsonParser::read_next()
{
	if (next_tok == end_token)
		return;
	if (next_tok != no_token and next_depth == 0) {
		next_tok = end_token;
		return;
	}
	char c;
	nl = false;
	while (true) {
		do {
			is.get(c);
			if (!is.good())
				throw JsonException("eof");
			if (c == '\n')
				nl = true;
		} while (c == ' ' || c == '\t' || c == '\r' || c == '\n');
		switch (c) {
		case '[': next_tok = begin_array; next_depth++; break;

		case ']': next_tok = end_array; next_depth--; break;

		case '{': next_tok = begin_object; next_depth++; break;

		case '}': next_tok = end_object; next_depth--; break;

		case ',': continue;

		case '"':
			next_str = readstring();
			is >> c;
			if (!is.good())
				throw JsonException("eof");
			if (c == ':')
				next_tok = value_key;
			else {
				is.unget();
				next_tok = value_string;
			}
			break;

		case '-': case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			next_str = readnumber(c);
			next_tok = value_number;
			break;

		default:
			throw JsonException("bad token");
		}
		break;
	}
}

JsonParser::token JsonParser::next(token expect)
{
	if (cur_tok != end_token) {
		if (next_tok == no_token)
			read_next();
		depth = next_depth;
		cur_tok = next_tok;
		str = next_str;
		if (next_tok != end_token)
			read_next();
	}
	if (expect != no_token)
		check_expect(expect);
	return cur_tok;
}


void JsonParser::copy_object(JsonWriter& jw)
{
	int curdepth = depth;
	do {
		switch (next()) {
		case begin_object:
			jw.begin_object(nl);
			break;
		case end_object:
			jw.end_object(nl);
			break;
		case begin_array:
			jw.begin_array(nl);
			break;
		case end_array:
			jw.end_array(nl);
			break;
		case value_string:
			jw.write(current_value(),nl);
			break;
		case value_number:
			jw.write_lit(current_value(),nl);
			break;
		case value_key:
			jw.write_key(current_value().c_str(),nl);
			break;
		default:
			throw JsonException("unexpected token");
		}
	} while (curdepth != depth);
}

void JsonParser::skip_object()
{
	int curdepth = depth;
	do {
		if (next() == end_token) {
			throw JsonException("unexpected eof");
		}
	} while (curdepth != depth);
}


/****************************************************************
 ** loading of saving application data
 */

static void write_parameters(JsonWriter &w, bool preset)
{
	w.begin_object(true);
	for (gx_gui::ParamMap::iterator i = gx_gui::parameter_map.begin(); i != gx_gui::parameter_map.end(); i++) {
		gx_gui::Parameter *param = i->second;
		if ((preset and param->isInPreset()) or (!preset and !param->isInPreset())) {
			param->writeJSON(w);
			w.newline();
		}
	}
	w.end_object(true);
}

static void read_parameters(JsonParser &jp, gx_gui::paramlist& plist, bool preset)
{
	jp.next(JsonParser::begin_object);
	do {
		jp.next(JsonParser::value_key);
		if (!gx_gui::parameter_map.hasId(jp.current_value())) {
			gx_print_warning("recall settings", "unknown parameter: "+jp.current_value());
			jp.skip_object();
			continue;
		}
		gx_gui::Parameter& param = gx_gui::parameter_map[jp.current_value()];
		if (!preset and param.isInPreset()) {
			gx_print_warning("recall settings", "preset-parameter "+param.id()+" in settings");
			jp.skip_object();
			continue;
		} else if (preset and !param.isInPreset()) {
			gx_print_warning("recall settings", "non preset-parameter "+param.id()+" in preset");
			jp.skip_object();
			continue;
		}
		param.readJSON_value(jp);
		plist.push_back(&param);
	} while (jp.peek() == JsonParser::value_key);
	jp.next(JsonParser::end_object);
}

void write_preset(JsonWriter &w, bool write_midi, bool force_midi)
{
	w.begin_object(true);
	w.write_key("engine");
	write_parameters(w, true);
	w.write_key("jconv");
	gx_jconv::GxJConvSettings::instance()->writeJSON(w);
	if (force_midi || (write_midi && gx_gui::parameter_map["system.midi_in_preset"].getSwitch().get())) {
		w.write_key("midi_controller");
		gx_gui::controller_map.writeJSON(w);
	}
	w.newline();
	w.end_object(true);
}

void read_preset(JsonParser &jp, bool *has_midi)
{
	gx_gui::paramlist plist;
	if (has_midi) {
		*has_midi = false;
	}
	gx_gui::MidiControllerList::controller_array *m = 0;
	jp.next(JsonParser::begin_object);
	do {
		jp.next(JsonParser::value_key);
		if (jp.current_value() == "engine") {
			read_parameters(jp, plist, true);
		} else if (jp.current_value() == "jconv") {
			*gx_jconv::GxJConvSettings::instance() = gx_jconv::GxJConvSettings(jp);
		} else if (jp.current_value() == "midi_controller") {
			if (has_midi || gx_gui::parameter_map["system.midi_in_preset"].getSwitch().get()) {
				m = new gx_gui::MidiControllerList::controller_array(gx_gui::MidiControllerList::controller_array_size);
				gx_gui::controller_map.readJSON(jp, *m);
				if (has_midi) {
					*has_midi = true;
				}
			} else {
				jp.skip_object();
			}
		} else {
			gx_print_warning("recall settings",
			                 "unknown preset section: " + jp.current_value());
		}
	} while (jp.peek() == JsonParser::value_key);
	jp.next(JsonParser::end_object);
	gx_gui::controller_map.remove_controlled_parameters(plist, m);
	for (gx_gui::paramlist::iterator i = plist.begin(); i != plist.end(); i++) {
		(*i)->setJSON_value();
	}
	if (m) {
		gx_gui::controller_map.set_controller_array(*m);
		delete m;
	}
}

void writeHeader(JsonWriter& jw)
{
	jw.write("guitarix_file_version");
	jw.begin_array();
	jw.write(majorversion); // major format version
	jw.write(minorversion); // minor format version
	jw.write(GX_VERSION);
	jw.end_array(true);
}

bool readHeader(JsonParser& jp, int *major, int *minor)
{
	jp.next(JsonParser::value_string);
	if (jp.current_value() != "guitarix_file_version") {
		throw JsonException("invalid guitarix file header");
	}
	jp.next(JsonParser::begin_array);
	jp.next(JsonParser::value_number);
	int m = jp.current_value_int();
	if (major) {
		*major = m;
	}
	jp.next(JsonParser::value_number); // minorversion
	int n = jp.current_value_int();
	if (minor) {
		*minor = n;
	}
	jp.next(JsonParser::value_string); // guitarix version
	jp.next(JsonParser::end_array);
	return m == majorversion && n == minorversion;
}

static void write_jack_port_connections(JsonWriter& w, const char *key, jack_port_t *port)
{
	w.write_key(key);
	w.begin_array();
	const char** pl = jack_port_get_connections(port);
	if (pl) {
		for (const char **p = pl; *p; p++) {
			w.write(*p);
		}
		free(pl);
	}
	w.end_array(true);
}

void write_jack_connections(JsonWriter& w)
{
	w.begin_object(true);
	write_jack_port_connections(w, "input", input_ports[0]);
	write_jack_port_connections(w, "output1", output_ports[2]);
	write_jack_port_connections(w, "output2", output_ports[3]);
	write_jack_port_connections(w, "midi_input", midi_input_port);
	write_jack_port_connections(w, "midi_output", midi_output_ports);
	write_jack_port_connections(w, "insert_out", output_ports[0]);
	write_jack_port_connections(w, "insert_in", input_ports[1]);
	w.end_object(true);
}

// -- save state including current preset data
bool saveStateToFile( const string &filename )
{
    gx_print_info( "wrinting to ", filename.c_str() );
	string tmpfile = filename + "_tmp";
	ofstream f(tmpfile.c_str());
	JsonWriter w(f);

	w.begin_array();
	writeHeader(w);

	w.write("settings");
	write_parameters(w, false);

	w.write("midi_controller");
	gx_gui::controller_map.writeJSON(w);

	w.write("midi_ctrl_names");
	gx_gui::midi_std_ctr.writeJSON(w);

	w.write("current_preset");
	write_preset(w, false);

	w.write("jack_connections");
	write_jack_connections(w);

	w.newline();
	w.end_array(true);
	w.close();
	f.close();
	if (!f.good()) {
		return false;
	}
	int rc = rename(tmpfile.c_str(), filename.c_str());
	return rc == 0;
}

list<string> jack_connection_lists[7];

static void read_jack_connections(JsonParser& jp)
{
	jp.next(JsonParser::begin_object);
	while (jp.peek() == JsonParser::value_key) {
		int i;
		jp.next(JsonParser::value_key);
		if (jp.current_value() == "input") {
			i = kAudioInput;
		} else if (jp.current_value() == "output1") {
			i = kAudioOutput1;
		} else if (jp.current_value() == "output2") {
			i = kAudioOutput2;
		} else if (jp.current_value() == "midi_input") {
			i = kMidiInput;
		} else if (jp.current_value() == "midi_output") {
			i = kMidiOutput;
		} else if (jp.current_value() == "insert_out") {
			i = kAudioInsertOut;
		} else if (jp.current_value() == "insert_in") {
			i = kAudioInsertIn;
		} else {
			gx_print_warning("recall state","unknown jack ports sections" + jp.current_value());
			jp.skip_object();
			continue;
		}
		jp.next(JsonParser::begin_array);
		while (jp.peek() == JsonParser::value_string) {
			jp.next();
			jack_connection_lists[i].push_back(jp.current_value());
		}
		jp.next(JsonParser::end_array);
	}
	jp.next(JsonParser::end_object);
}

// -- recallState(filename) : load state from file
bool recallState( const string &filename )
{
	ifstream f(filename.c_str());
	if (!f.good()) {
		return false;
	}
	gx_gui::paramlist plist;
	gx_gui::MidiControllerList::controller_array m(gx_gui::MidiControllerList::controller_array_size);
	gx_system::JsonParser jp(f);
	try {
		jp.next(JsonParser::begin_array);

		int major;
		readHeader(jp, &major);
		if (major != majorversion) {
			if (major == 0) {
				gx_print_info("recall settings", "loading converted state");
			} else {
				stringstream s;
				s << "major version mismatch in "+filename+": found "
				  << major << ", expected " << majorversion << endl;
				gx_print_warning("recall settings", s.str());
			}
		}

		// other sections (settings, current_preset)
		do {
			jp.next(JsonParser::value_string);
			if (jp.current_value() == "settings") {
				read_parameters(jp, plist, false);
			} else if (jp.current_value() == "current_preset") {
				read_preset(jp);
			} else if (jp.current_value() == "midi_controller") {
				gx_gui::controller_map.readJSON(jp, m);
			} else if (jp.current_value() == "midi_ctrl_names") {
				gx_gui::midi_std_ctr.readJSON(jp);
			} else if (jp.current_value() == "jack_connections") {
				read_jack_connections(jp);
			} else {
				gx_print_warning("recall settings",
				                 "unknown section: " + jp.current_value());
				jp.skip_object();
			}
		} while (jp.peek() == JsonParser::value_string);
		jp.next(JsonParser::end_array);
		jp.next(JsonParser::end_token);
	} catch (JsonException& e) {
		gx_print_error("recall settings", "invalid settings file: " + filename);
		return false;
	}
	for (gx_gui::paramlist::iterator i = plist.begin(); i != plist.end(); i++) {
		(*i)->setJSON_value();
	}
	gx_gui::controller_map.set_controller_array(m);
	return true;
}

/****************************************************************
 ** Measuring times (only when debugging)
 */

#ifndef NDEBUG

/* return time difference in ns, fail if > sec (doesn't fit int 32 bit int) */
int Measure::ts_diff(struct timespec ts1, struct timespec ts2)
{
	time_t df = ts1.tv_sec - ts2.tv_sec;
	if (abs(df) > 2) {
		return -1; // failed
	}
	return df * 1000000000 + (ts1.tv_nsec - ts2.tv_nsec);
}

void Measure::print_accum(Accum& accum, const char* prefix, bool verbose, int total)
{
	cout << prefix << "mean: " << fixed << setprecision(4) << ns2ms(accum.mean());
	if (total > 0) {
		cout << " (" << setprecision(2) << 100.0*accum.mean()/float(total) << "%)";
	}
	cout << ", min: " << setprecision(4) << ns2ms(accum.minimum())
	     << ", max: " << ns2ms(accum.maximum());
	if (total > 0) {
		cout << " (" << setprecision(2) << 100.0*accum.maximum()/float(total) << "%)";
	}
	if (verbose) {
		cout << ", stddev: " << setprecision(4) << ns2ms(accum.stddev())
		     << ", n: " << accum.count();
	}
	cout << endl;
}

void Measure::print(bool verbose)
{
	if (verbose) {
		print_accum(period,   "period    ", verbose);
	}
	print_accum(duration, "duration  ", verbose, period.mean());
}

void MeasureThreadsafe::print(bool verbose)
{
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

static int print_measures(gpointer data)
{
	bool verbose = GPOINTER_TO_INT(data);
	measure.print(verbose);
	return TRUE;
}

void add_time_measurement()
{
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

// ---- retrieve and store the shell variable if not NULL
void gx_assign_shell_var(const char* name, string& value)
{
	const char* val = getenv(name);
	value = (val != NULL) ? val : "" ;
}

// ---- OS signal handler -----
void gx_signal_handler(int sig)
{
	// print out a warning
	string msg = string("signal ") + gx_i2a(sig) + " received, exiting ...";
	gx_print_warning("signal_handler", msg);

	gx_clean_exit(NULL, NULL);
}

// ---- ladi signal handler -----
gboolean  gx_ladi_handler(gpointer)
{
	gx_print_warning("signal_handler", "signal USR1 received, save settings");

	saveStateToFile(gx_user_dir + client_instance + "_rc");
	return false;
}

bool terminal  = true; // make messages before main() appear on terminal

// ---- command line options
void gx_process_cmdline_options(int& argc, char**& argv, string* optvar)
{
	// store shell variable content
	for (int i = 0; i < NUM_SHELL_VAR; i++) {
		gx_assign_shell_var(shell_var_name[i], optvar[i]);
	}
	// initialize number of skins. We just count the number of rc files
	unsigned int n = gx_gui::gx_fetch_available_skins();
	if (n < 1) {
		gx_print_error("main", string("number of skins is 0, aborting ..."));
		exit(1);
	}

	// ---- parse command line arguments
	bool version = false;
	Glib::OptionContext opt_context;
	opt_context.set_summary(
		"All parameters are optional. Examples:\n"
		"\tguitarix\n"
		"\tguitarix -r black -i system:capture_3\n"
		"\tguitarix -c -o system:playback_1 -o system:playback_2");
	Glib::OptionEntry opt_version;
	opt_version.set_short_name('v');
	opt_version.set_long_name("version");
	opt_version.set_description("Print version string and exit");
	Glib::OptionGroup main_group("bla1","bla2","bla3");
	main_group.add_entry(opt_version, version);
	opt_context.set_main_group(main_group);

	// GTK options: rc style (aka skin)
	string opskin("Style to use");

	vector<string>::iterator it;

	for (it = gx_gui::skin_list.begin(); it != gx_gui::skin_list.end(); it++) {
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
	opt_load_file.set_description("load state file on startup");
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
	opt_builder_dir.set_description("directory from which .glade files are loaded");
	opt_builder_dir.set_arg_description("DIR");
	optgroup_debug.add_entry_filename(opt_builder_dir, builder_dir);
	Glib::OptionEntry opt_style_dir;
	opt_style_dir.set_short_name('S');
	opt_style_dir.set_long_name("style-dir");
	opt_style_dir.set_description("directory with skin style definitions (.rc files)");
	opt_style_dir.set_arg_description("DIR");
	optgroup_debug.add_entry_filename(opt_style_dir, style_dir);
	Glib::OptionEntry opt_log_terminal;
	opt_log_terminal.set_short_name('t');
	opt_log_terminal.set_long_name("log-terminal");
	opt_log_terminal.set_description("print log on terminal");
	optgroup_debug.add_entry(opt_log_terminal, lterminal);

	// collecting all option groups
	opt_context.add_group(optgroup_gtk);
	opt_context.add_group(optgroup_jack);
	opt_context.add_group(optgroup_file);
	opt_context.add_group(optgroup_debug);

	// parsing command options
	try {
		opt_context.parse(argc, argv);
	} catch (Glib::OptionError ex) {
		gx_print_error("main", "Error in user options! " + ex.what());
		exit(1);
	}


	// ----------- processing user options -----------

	terminal = lterminal;

	// *** display version if requested
	if (version) {
		cout << "Guitarix version \033[1;32m"
			 << GX_VERSION << endl
			 << "\033[0m   Copyright " << (char)0x40 << " 2010 "
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
			gx_print_error("main",
						   string("-c and -r cannot be used together, defaulting to 'default' style"));
			tmp = "default";
			previous_conflict = true;
		}

		// if garbage, let's initialize to guitarix_default.rc
		guint s = 0;
		while (s < gx_gui::skin_list.size()) {
			if (tmp == gx_gui::skin_list[s])
				break;
			s++;
		}

		if (s == gx_gui::skin_list.size()) {
			gx_print_error("main",
						   string("rcset value is garbage, defaulting to 'default' style"));
			tmp = "default";
		}
		optvar[RC_STYLE] = tmp;
	}

	// else, if no shell var defined for it, defaulting to guitarix_default.rc
	else if (optvar[RC_STYLE].empty()) {
		optvar[RC_STYLE] = "default";
		// enable set last used skin
		gx_gui::no_opt_skin = 1;
	}

	// *** process GTK clear
	if (clear) {
		// check contradiction (clear and rcset cannot be used in the same call)
		if (rcset != NULL && !previous_conflict)
			gx_print_error("main",
						   string("-c and -r cannot be used together, defaulting to 'default' style"));

		optvar[RC_STYLE] = "default";
	}

	// *** process builder_dir
	if (!builder_dir.empty()) {
		gx_builder_dir = builder_dir;
		if (gx_builder_dir[gx_builder_dir.size()-1] != '/') {
			gx_builder_dir += "/";
		}
	}

	// *** process style_dir
	if (!style_dir.empty()) {
		gx_style_dir = style_dir;
		if (gx_style_dir[gx_style_dir.size()-1] != '/') {
			gx_style_dir += "/";
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
				gx_print_warning("main",
				                 "Warning --> provided more than 2 output ports, ignoring extra ports");
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

	rcpath = gx_style_dir + string("guitarix_") + optvar[RC_STYLE] + ".rc";
}

void gx_set_override_options(string* optvar)
{
	if (!gx_gui::no_opt_skin) {
		gx_gui::gx_actualize_skin_index(optvar[RC_STYLE]);
		audio.fskin = gx_gui::last_skin = gx_gui::gx_current_skin;
	}
}

struct logmsg {
	string msg;
	GxMsgType msgtype;
	logmsg(string m, GxMsgType t): msg(m), msgtype(t) {}
};

// ---- log message handler
void gx_print_logmsg(const char* func, const string& msg, GxMsgType msgtype)
{
	static list<logmsg> msglist;

	// timestamp
	time_t now;
	time(&now);
	struct tm *tm_now = localtime (&now);
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
		cerr << msgbuf.str() << endl;
	}
}


// warning
void gx_print_warning(const char* func, const string& msg)
{
	gx_print_logmsg(func, msg, kWarning);
}

// error
void gx_print_error(const char* func, const string& msg)
{
	gx_print_logmsg(func, msg, kError);
}

// fatal error
void gx_print_fatal(const char* func, const string& msg)
{
	string msgbuf = string("fatal system error: ") + func + "  ***  " + msg + "\n";
	cerr << msgbuf;
	GtkWidget* widget = gtk_message_dialog_new(NULL,
	                                           GtkDialogFlags(GTK_DIALOG_MODAL|
	                                                          GTK_DIALOG_DESTROY_WITH_PARENT),
	                                           GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE,
	                                           "%s", msgbuf.c_str());
	gtk_window_set_title(GTK_WINDOW(widget), "guitarix");
	gtk_dialog_run(GTK_DIALOG(widget));
	gx_clean_exit(NULL, (gpointer)1);
}

// info
void gx_print_info(const char* func, const string& msg)
{
	gx_print_logmsg(func, msg, kInfo);
}


// ---- check version and if directory exists and create it if it not exist
bool gx_version_check()
{
	struct stat my_stat;

	//----- this check dont need to be against real version, we only need to know
	//----- if the presethandling is working with the courent version, we only count this
	//----- string when we must remove the old preset files.
	string rcfilename =
		gx_user_dir + string("version-") + string("0.03.3") ;

	if  (stat(gx_user_dir.c_str(), &my_stat) == 0) // directory exists
	{
		// check which version we're dealing with
		if  (stat(rcfilename.c_str(), &my_stat) != 0)
		{
			// current version not there, let's create it and refresh the whole shebang
			string oldfiles = gx_user_dir + string("guitarix*rc");
			(void)gx_system_call ("rm -f", oldfiles.c_str(), false);

			oldfiles = gx_user_dir + string("version*");
			(void)gx_system_call ("rm -f", oldfiles.c_str(), false);

			oldfiles = gx_user_dir + string("*.conf");
			(void)gx_system_call ("rm -f", oldfiles.c_str(), false);

			// setting file for current version
			ofstream f(rcfilename.c_str());
			string cim = string("guitarix-") + GX_VERSION;
			f << cim <<endl;
			f.close();

			// --- create jack_capture setting file
			/*string tmpstr = gx_user_dir + jcapsetup_file;

			(void)gx_system_call("touch", tmpstr.c_str(), false);
			(void)gx_system_call(
				"echo 'jack_capture -c 2 --silent --disable-meter --port guitarix:out* ' >",
				tmpstr.c_str(),
				false
				); */
		}
	}
	else // directory does not exist
	{
		// create .guitarix directory
		(void)gx_system_call("mkdir -p", gx_user_dir.c_str(), false);

		// setting file for current version
		ofstream f(rcfilename.c_str());
		string cim = string("guitarix-") + GX_VERSION;
		f << cim <<endl;
		f.close();

		// --- create jack_capture setting file
		string tmpstr = gx_user_dir + jcapsetup_file;

	/*	(void)gx_system_call("touch", tmpstr.c_str(), false);
		(void)gx_system_call(
			"echo 'jack_capture -c 2 --silent --disable-meter --port guitarix:out* ' >",
			tmpstr.c_str(),
			false
			); */

		// --- version file
		//same here, we only change this file, when the presethandling is broken,
		// otherwise we can let it untouched
		tmpstr = gx_user_dir + string("version-") + string("0.03.3");
		(void)gx_system_call("touch", tmpstr.c_str(), false);

		cim = string("echo 'guitarix-") + string(GX_VERSION) + "' >";
		(void)gx_system_call(cim.c_str(), tmpstr.c_str(), false);


	}

	return TRUE;
}

//----- we must make sure that the images for the status icon be there
int gx_pixmap_check()
{
	struct stat my_stat;

	string gx_pix   = gx_pixmap_dir + "guitarix.png";
	string midi_pix = gx_pixmap_dir + "guitarix-midi.png";
	string warn_pix = gx_pixmap_dir + "guitarix-warn.png";

	if ((stat(gx_pix.c_str(), &my_stat) != 0)   ||
	    (stat(midi_pix.c_str(), &my_stat) != 0) ||
	    (stat(warn_pix.c_str(), &my_stat) != 0))

	{
		gx_print_error("Pixmap Check", " cannot find installed pixmaps! giving up ...");

		// giving up
		return 1;
	}

	GtkWidget *ibf =  gtk_image_new_from_file (gx_pix.c_str());
	gx_gui::ib = gtk_image_get_pixbuf (GTK_IMAGE(ibf));

	GtkWidget *stim = gtk_image_new_from_file (midi_pix.c_str());
	gx_gui::ibm = gtk_image_get_pixbuf (GTK_IMAGE(stim));

	GtkWidget *stir = gtk_image_new_from_file (warn_pix.c_str());
	gx_gui::ibr = gtk_image_get_pixbuf (GTK_IMAGE(stir));

	return 0;
}

//----convert int to string
void gx_IntToString(int i, string & s)
{
	s = "";

	int abs_i = abs(double(i));
	do
	{
		// note: using base 10 since 10 digits (0123456789)
		char c = static_cast<char>(ASCII_START+abs_i%10);
		s.insert(0, &c, 1);
	}
	while ((abs_i /= 10) > 0);
	if (i < 0) s.insert(0, "-");
}

const string& gx_i2a(int i)
{
	static string str;
	gx_IntToString(i, str);

	return str;
}

//----clean up preset name given by user
void gx_nospace_in_name(string& name, const char* subs)
{
	int p = name.find(' ', 0);
	while (p != -1)
	{
		name.replace(p++, 1, subs);
		p = name.find(' ', p);
	}
}

//----abort guitarix
void gx_abort(void* arg)
{
	gx_print_warning("gx_abort", "Aborting guitarix, ciao!");
	exit(1);
}

//---- guitarix system function
int gx_system_call(const char* name1,
                   const char* name2,
                   const bool  devnull,
                   const bool  escape)
{
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
                   const bool  escape)
{
	return gx_system_call(name1, name2.c_str(), devnull, escape);
}

// polymorph2
// int gx_system_call(const string& name1,
//    	     const string& name2,
// 		     const bool  devnull,
// 		     const bool  escape)
// {
//   return gx_system_call(name1.c_str(), name2.c_str(), devnull, escape);
// }

// polymorph3
int gx_system_call(const string& name1,
                   const char*   name2,
                   const bool  devnull,
                   const bool  escape)
{
	return gx_system_call(name1.c_str(), name2, devnull, escape);
}


//----- clean up when shut down
void gx_destroy_event()
{
	// remove image buffers
	if (G_IS_OBJECT(gx_gui::ib))
		g_object_unref(gx_gui::ib);

	if (G_IS_OBJECT(gx_gui::ibm))
		g_object_unref(gx_gui::ibm);

	if (G_IS_OBJECT(gx_gui::ibr))
		g_object_unref(gx_gui::ibr);

	if (G_IS_OBJECT(gx_cairo::tribeimage))
		g_object_unref(gx_cairo::tribeimage);

	if (G_IS_OBJECT(gx_cairo::tribeimage1))
		g_object_unref(gx_cairo::tribeimage1);

	if (G_IS_OBJECT(gx_cairo::tribeimage2))
		g_object_unref(gx_cairo::tribeimage2);

	// remove threads from main GTK thread
	for (unsigned int i = 0; i < sizeof(gx_gui::g_threads)/sizeof(gx_gui::g_threads[0]); i++) {
		if(gx_gui::g_threads[i] > 0) {
			g_source_remove(gx_gui::g_threads[i]);
		}
	}

	GtkRegler::gtk_regler_destroy();

	gx_waveview_destroy(GTK_WIDGET(gx_gui::livewa), NULL);

	gtk_main_quit();
}

//-----Function that must be called before complete shutdown
void gx_clean_exit(GtkWidget* widget, gpointer data)
{
	// save DSP state
	if (isInitialized()) {
		get_latency_warning_change();
		gx_gui::gx_get_skin_change(&audio.fskin);

		// only save if we are not in a preset context
		if (!setting_is_preset && gx_jack::client) {
			saveStateToFile(gx_user_dir + client_instance + "_rc");
		}
	}

	gx_gui::shownote = -1;
	gx_gui::showwave = 0;
	gx_jack::NO_CONNECTION = 1;

	turnOffMidi();

	// clean jack client stuff
	gx_jack_cleanup();

	// clean GTK stuff
	if (gx_gui::fWindow) {
		gx_destroy_event();
	}
	// delete the locked mem buffers
	if (checkfreq) {
		delete[] checkfreq;
		checkfreq = NULL;
	}
	if (get_frame) {
		delete[] get_frame;
		get_frame = NULL;
	}
	if (get_frame1) {
		delete[] get_frame1;
		get_frame1 = NULL;
	}
	if (oversample) {
		delete[] oversample;
		oversample = NULL;
	}
	if (result) {
		delete[] result;
		result = NULL;
	}

	printf("  guitarix exit  ***  ciao . . \n");
	exit(GPOINTER_TO_INT(data));
}


} /* end of gx_system namespace */
