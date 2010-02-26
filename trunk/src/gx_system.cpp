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

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <cstdio>

using namespace std;

#include <sys/stat.h>
#include <string.h>
#include <sndfile.h>
//#include <fftw3.h>
#include <jack/jack.h>
#include <gtk/gtk.h>

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

void write_parameters(JsonWriter &w, bool preset)
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

void read_parameters(JsonParser &jp, bool preset)
{
	jp.next(JsonParser::begin_object);
	do {
		jp.next(JsonParser::value_key);
		gx_gui::Parameter *param = gx_gui::parameter_map.find(jp.current_value());
		if (!param) {
			gx_print_warning("recall settings", "unknown parameter: "+jp.current_value());
			jp.skip_object();
			continue;
		}
		if (!preset and param->isInPreset()) {
			gx_print_warning("recall settings", "preset-parameter "+param->id()+" in settings");
			jp.skip_object();
			continue;
		} else if (preset and !param->isInPreset()) {
			gx_print_warning("recall settings", "non preset-parameter "+param->id()+" in preset");
			jp.skip_object();
			continue;
		}
		param->readJSON_value(jp);
	} while (jp.peek() == JsonParser::value_key);
	jp.next(JsonParser::end_object);
}

void write_preset(JsonWriter &w, bool write_midi)
{
	w.begin_object(true);
	w.write_key("engine");
	write_parameters(w, true);
	w.write_key("jconv");
	gx_jconv::GxJConvSettings::instance()->writeJSON(w);
	if (write_midi && gx_gui::parameter_map["system.midi_in_preset"].getSwitch().get()) {
		w.write_key("midi_controller");
		gx_gui::controller_map.writeJSON(w);
	}
	w.newline();
	w.end_object(true);
}

void read_preset(JsonParser &jp)
{
	jp.next(JsonParser::begin_object);
	do {
		jp.next(JsonParser::value_key);
		if (jp.current_value() == "engine") {
			read_parameters(jp, true);
		} else if (jp.current_value() == "jconv") {
			*gx_jconv::GxJConvSettings::instance() = gx_jconv::GxJConvSettings(jp);
		} else if (jp.current_value() == "midi_controller") {
			if (gx_gui::parameter_map["system.midi_in_preset"].getSwitch().get()) {
				//FIXME: clash with jack rt thread (unprobable)
				gx_gui::controller_map.readJSON(jp);
			} else {
				jp.skip_object();
			}
		} else {
			gx_print_warning("recall settings",
			                 "unknown preset section: " + jp.current_value());
		}
	} while (jp.peek() == JsonParser::value_key);
	jp.next(JsonParser::end_object);
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
	write_jack_port_connections(w, "output1", output_ports[0]);
	write_jack_port_connections(w, "output2", output_ports[1]);
	write_jack_port_connections(w, "midi_input", midi_input_port);
	w.end_object(true);
}

// -- save state including current preset data
bool saveStateToFile()
{
	string filename = gx_user_dir + client_name + "_rc";
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

list<string> jack_connection_lists[4];

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
bool recallState()
{
	string filename = gx_user_dir + client_name + "_rc";
	ifstream f(filename);
	if (!f.good()) {
		return false; 
	}
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
				read_parameters(jp, false);
			} else if (jp.current_value() == "current_preset") {
				read_preset(jp);
			} else if (jp.current_value() == "midi_controller") {
				gx_gui::controller_map.readJSON(jp);
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
	return true;
}

/****************************************************************
 ** OS functions and helper
 */

// ---- retrieve and store the shell variable if not NULL
void gx_assign_shell_var(const char* name, string& value)
{
	const char* val = getenv(name);
	value = (val != NULL) ? val : "" ;
}

// ---- is the shell variable set ?
bool gx_shellvar_exists(const string& var)
{
	return !var.empty();
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
	saveStateToFile();
	return false;
}

gboolean terminal  = FALSE;

// ---- command line options
void gx_process_cmdline_options(int& argc, char**& argv, string* optvar)
{
	// store shell variable content
	for (int i = 0; i < NUM_SHELL_VAR; i++)
		gx_assign_shell_var(shell_var_name[i], optvar[i]);

	// initialize number of skins. We just count the number of rc files
	unsigned int n = gx_gui::gx_fetch_available_skins();
	if (n < 1)
	{
		gx_print_error("main", string("number of skins is 0, aborting ..."));
		exit(1);
	}

	// ---- parse command line arguments
	try	{
		gboolean version = FALSE;
		GOptionEntry opt_entries[] =
			{
				{ "version", 'v', 0, G_OPTION_ARG_NONE, &version, "Print version string and exit", NULL },
				{ NULL }
			};
		GError* error = NULL;
		GOptionContext* opt_context = NULL;

		opt_context = g_option_context_new(NULL);
		g_option_context_set_summary(opt_context,
		                             "All parameters are optional. Examples:\n"
		                             "\tguitarix\n"
		                             "\tguitarix -r black -i system:capture_3\n"
		                             "\tguitarix -c -o system:playback_1 -o system:playback_2");
		g_option_context_add_main_entries(opt_context, opt_entries, NULL);

		// GTK options: rc style (aka skin)
		string opskin("Style to use");

		vector<string>::iterator it;

		for (it = gx_gui::skin_list.begin(); it != gx_gui::skin_list.end(); it++)
		{
			opskin += ", '" + *it + "'";
		}

		gboolean clear = FALSE;
		gchar* rcset = NULL;
		GOptionGroup* optgroup_gtk = g_option_group_new("gtk",
		                                                "\033[1;32mGTK configuration options\033[0m",
		                                                "\033[1;32mGTK configuration options\033[0m",
		                                                NULL, NULL);
		GOptionEntry opt_entries_gtk[] =
			{
				{ "clear", 'c', 0, G_OPTION_ARG_NONE, &clear, "Use 'default' GTK style", NULL },
				{ "rcset", 'r', 0, G_OPTION_ARG_STRING, &rcset, opskin.c_str(), "STYLE" },

				{ NULL }
			};
		g_option_group_add_entries(optgroup_gtk, opt_entries_gtk);

		// JACK options: input and output ports
		gchar* jack_input = NULL;
		gchar* jack_midi = NULL;
		gchar** jack_outputs = NULL;
		GOptionGroup* optgroup_jack = g_option_group_new("jack",
		                                                 "\033[1;32mJACK configuration options\033[0m",
		                                                 "\033[1;32mJACK configuration options\033[0m",
		                                                 NULL, NULL);
		GOptionEntry opt_entries_jack[] =
			{
				{ "jack-input", 'i', 0, G_OPTION_ARG_STRING, &jack_input, "Guitarix JACK input", "PORT" },
				{"jack-output", 'o', 0, G_OPTION_ARG_STRING_ARRAY, &jack_outputs, "Guitarix JACK outputs", "PORT" },
				{ "jack-midi",  'm', 0, G_OPTION_ARG_STRING, &jack_midi, "Guitarix JACK midi control", "PORT" },
				{ NULL }
			};
		g_option_group_add_entries(optgroup_jack, opt_entries_jack);

		// DEBUG options
		gchar* builder_dir = NULL;

		GOptionGroup* optgroup_debug = g_option_group_new("debug",
		                                                "\033[1;32mDebug options\033[0m",
		                                                "\033[1;32mDebug options\033[0m",
		                                                NULL, NULL);
		GOptionEntry opt_entries_debug[] =
			{
				{ "builder-dir", 'B', 0, G_OPTION_ARG_STRING, &builder_dir, "directory from which .glade files are loaded", "DIR" },
				{ "log-terminal", 't', 0, G_OPTION_ARG_NONE, &terminal, "print log on terminal", NULL },
				{ NULL }
			};
		g_option_group_add_entries(optgroup_debug, opt_entries_debug);

		// collecting all option groups
		g_option_context_add_group(opt_context, optgroup_gtk);
		g_option_context_add_group(opt_context, optgroup_jack);
		g_option_context_add_group(opt_context, optgroup_debug);

		// parsing command options
		if (!g_option_context_parse(opt_context, &argc, &argv, &error))
		{
			throw string(error->message);
		}
		g_option_context_free(opt_context);


		// ----------- processing user options -----------

		// *** display version if requested
		if (version)
		{
			cout << "Guitarix version \033[1;32m"
			     << GX_VERSION << endl
			     << "\033[0m   Copyright " << (char)0x40 << " 2009 "
			     << "Hermman Meyer - James Warden"
			     << endl;
			exit(0);
		}

		// *** process GTK rc style
		bool previous_conflict = false;
		if (rcset != NULL)
		{
			// retrieve user value
			string tmp = rcset;

			// check contradiction (clear and rcset cannot be used in the same call)
			if (clear)
			{
				gx_print_error("main",
				               string("-c and -r cannot be used together, defaulting to 'default' style"));
				tmp = "default";
				previous_conflict = true;
			}

			// if garbage, let's initialize to guitarix_default.rc
			guint s = 0;
			while (s < gx_gui::skin_list.size())
			{
				if (tmp == gx_gui::skin_list[s])
					break;
				s++;
			}

			if (s == gx_gui::skin_list.size())
			{
				gx_print_error("main",
				               string("rcset value is garbage, defaulting to 'default' style"));
				tmp = "default";
			}
			optvar[RC_STYLE] = tmp;
		}

		// else, if no shell var defined for it, defaulting to guitarix_default.rc
		else if (!gx_shellvar_exists(optvar[RC_STYLE]))
		{
			optvar[RC_STYLE] = "default";
			// enable set last used skin
			gx_gui::no_opt_skin = 1;
		}

		// *** process GTK clear
		if (clear)
		{
			// check contradiction (clear and rcset cannot be used in the same call)
			if (rcset != NULL && !previous_conflict)
				gx_print_error("main",
				               string("-c and -r cannot be used together, defaulting to 'default' style"));

			optvar[RC_STYLE] = "default";
		}

		if (rcset != NULL)
		{
			g_free(rcset);
		}

		// *** process builder_dir
		if (builder_dir != NULL) {
			gx_builder_dir = builder_dir;
			if (!gx_builder_dir.empty() && gx_builder_dir[gx_builder_dir.size()-1] != '/')
				gx_builder_dir += "/";
			g_free(builder_dir);
		}

		// *** process jack input
		if (jack_input != NULL)
		{
			optvar[JACK_INP] = jack_input;
			g_free(jack_input);
		}
		else if (!gx_shellvar_exists(optvar[JACK_INP]))
		{
			optvar[JACK_INP] = ""; // leads to no automatic connection
		}

		// *** process jack midi
		if (jack_midi != NULL)
		{
			optvar[JACK_MIDI] = jack_midi;
			g_free(jack_midi);
		}
		else if (!gx_shellvar_exists(optvar[JACK_MIDI]))
		{
			optvar[JACK_MIDI] = ""; // leads to no automatic connection
		}

		// *** process jack outputs
		if (jack_outputs != NULL) {
			int idx = JACK_OUT1;
			unsigned int i = 0;

			while (jack_outputs[i] != NULL) {
				if (i >= 2) {
					gx_print_warning("main",
					                 "Warning --> provided more than 2 output ports, ignoring extra ports");
					break;
				}
				optvar[idx] = string(jack_outputs[i]);
				i++;
				idx++;
			}
			g_strfreev(jack_outputs);
		} else {
			if (!gx_shellvar_exists(optvar[JACK_OUT1])) optvar[JACK_OUT1] = "";
			if (!gx_shellvar_exists(optvar[JACK_OUT2])) optvar[JACK_OUT2] = "";
		}


		//
		rcpath = GX_STYLE_DIR + string("/") + string("guitarix_") + optvar[RC_STYLE] + ".rc";

		gx_gui::gx_actualize_skin_index(optvar[RC_STYLE]);
	}

	// ---- catch exceptions that occured during user option parsing
	catch (string& e) {
		string msg = string("Error in user options! ") + e;
		gx_print_error("main", msg);
		exit(1);
	}
}

struct logmsg {
	string msg;
	GxMsgType msgtype;
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
		msglist.push_back(logmsg{msgbuf.str(), msgtype});
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
	gtk_window_set_title(GTK_WINDOW(widget), "Guitarix");
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

			string resetfile = gx_user_dir + "resettings";
			ofstream fa(resetfile.c_str());
			fa <<  default_setting <<endl;
			fa.close();

			// --- create jack_capture setting file
			string tmpstr = gx_user_dir + jcapsetup_file;

			(void)gx_system_call("touch", tmpstr.c_str(), false);
			(void)gx_system_call(
				"echo 'jack_capture -c 2 --silent --disable-meter --port guitarix:out* ' >",
				tmpstr.c_str(),
				false
				);

			// --- default jconv setting
			(void)gx_jconv::gx_save_jconv_settings(NULL, NULL);
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

		(void)gx_system_call("touch", tmpstr.c_str(), false);
		(void)gx_system_call(
			"echo 'jack_capture -c 2 --silent --disable-meter --port guitarix:out* ' >",
			tmpstr.c_str(),
			false
			);

		// --- default jconv setting
		(void)gx_jconv::gx_save_jconv_settings(NULL, NULL);

		// --- version file
		//same here, we only change this file, when the presethandling is broken,
		// otherwise we can let it untouched
		tmpstr = gx_user_dir + string("version-") + string("0.03.3");
		(void)gx_system_call("touch", tmpstr.c_str(), false);

		cim = string("echo 'guitarix-") + string(GX_VERSION) + "' >";
		(void)gx_system_call(cim.c_str(), tmpstr.c_str(), false);

		// --- guitarix own default settings
		tmpstr = gx_user_dir + guitarix_reset;
		(void)gx_system_call("touch", tmpstr.c_str(), false);

		cim = "echo -e '" + string(default_setting) + "' >";
		(void)gx_system_call(cim.c_str(), tmpstr.c_str(), false);
	}

	// initialize with what we already have, if we have something
	string s;
	gx_jconv::GxJConvSettings::instance()->configureJConvSettings(s);

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

	return system(str.c_str());
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
	(void)gx_child_process::gx_terminate_child_procs();

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

	if (G_IS_OBJECT(gx_cairo::_image))
		g_object_unref(gx_cairo::_image);

	// remove threads from main GTK thread
	if(gx_gui::g_threads[0] > 0)g_source_remove(gx_gui::g_threads[0]);
	if(gx_gui::g_threads[1] > 0)g_source_remove(gx_gui::g_threads[1]);
	if(gx_gui::g_threads[2] > 0)g_source_remove(gx_gui::g_threads[2]);
	if(gx_gui::g_threads[3] > 0)g_source_remove(gx_gui::g_threads[3]);
	if(gx_gui::g_threads[4] > 0)g_source_remove(gx_gui::g_threads[4]);

	GtkRegler::gtk_regler_destroy();

	gx_waveview_destroy(GTK_WIDGET(gx_gui::livewa), NULL);

	gtk_main_quit();
}

//-----Function that must be called before complete shutdown
void gx_clean_exit(GtkWidget* widget, gpointer data)
{
	// save DSP state
	GxEngine* engine = GxEngine::instance();
	if (engine->isInitialized())
	{
		engine->get_latency_warning_change();
		gx_gui::gx_get_skin_change(&engine->fskin);

		// only save if we are not in a preset context
		if (!setting_is_preset)
			saveStateToFile();
	}

	gx_gui::shownote = -1;
	gx_gui::showwave = 0;
	gx_jack::NO_CONNECTION = 1;

	gx_engine::stopit = "stop";
	dsp::turnOffMidi();

	// clean jack client stuff
	gx_jack_cleanup();

	// clean GTK stuff
	if (gx_gui::fWindow)
		gx_destroy_event();

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
	if (get_frame2) {
		delete[] get_frame2;
		get_frame2 = NULL;
	}
	if (get_frame3) {
		delete[] get_frame3;
		get_frame3 = NULL;
	}
	if (oversample) {
		delete[] oversample;
		oversample = NULL;
	}
	if (result) {
		delete[] result;
		result = NULL;
	}

	/** disable fft need some fix for work prop **/
	/*
	  fftw_destroy_plan(p);
	  fftw_destroy_plan(p1);
	  fftw_destroy_plan(pf);
	  fftw_free(fftin);
	  fftw_free(fftout);
	  fftw_free(fftin1);
	  fftw_free(fftout1);
	  fftw_free(fftresult);
	*/
	printf("  guitarix exit  ***  ciao . . \n");
	exit(GPOINTER_TO_INT(data));
}


} /* end of gx_system namespace */
