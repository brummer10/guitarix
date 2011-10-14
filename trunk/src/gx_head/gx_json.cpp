
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



/****************************************************************
 ** JsonWriter
 */

JsonWriter::JsonWriter(ostream &o)
    : os(o),
    first(true),
    deferred_nl(false),
    indent("") {}

inline void JsonWriter::komma() {
    if (first)
        first = false;
    else if (!deferred_nl)
        os << ", ";
    else
        os << ",";
    flush();
}

inline void JsonWriter::space() {
    if (first)
        first = false;
    else if (!deferred_nl)
        os << " ";
    flush();
}

inline void JsonWriter::iplus() {
    indent += "  ";
}

inline void JsonWriter::iminus() {
    if (!indent.empty()) {
        indent = indent.substr(0, indent.size() - 2);
    }
}

void JsonWriter::write(float v, bool nl) {
    komma();
    os << v;
    snl(nl);
}

void JsonWriter::write(double v, bool nl) {
    komma();
    os << v;
    snl(nl);
}

void JsonWriter::write(int i, bool nl) {
    komma();
    os << i;
    snl(nl);
}

void JsonWriter::write(unsigned int i, bool nl) {
    komma();
    os << i;
    snl(nl);
}

void JsonWriter::write_lit(string s, bool nl) {
    komma();
    os << s;
    snl(nl);
}

void JsonWriter::write(const char* p, bool nl) {
    komma();
    os << '"';
    while (*p) {
        switch (*p) {
        case '\\': case '"': os << '\\'; break;
        case '\b': os << '\\'; os << 'b'; continue;       // NOLINT
        case '\f': os << '\\'; os << 'f'; continue;       // NOLINT
        case '\n': os << '\\'; os << 'n'; continue;       // NOLINT
        case '\r': os << '\\'; os << 'r'; continue;       // NOLINT
        case '\t': os << '\\'; os << 't'; continue;       // NOLINT
        }
        os << *p++;
    }
    os << '"';
    snl(nl);
}

void JsonWriter::begin_object(bool nl) {
    komma();
    os << '{';
    snl(nl);
    first = true;
    iplus();
}

void JsonWriter::end_object(bool nl) {
    iminus();
    flush();
    first = false;
    os << '}';
    snl(nl);
}

void JsonWriter::begin_array(bool nl) {
    komma();
    os << '[';
    snl(nl);
    first = true;
    iplus();
}

void JsonWriter::end_array(bool nl) {
    iminus();
    flush();
    first = false;
    os << ']';
    snl(nl);
}

void JsonWriter::write_key(const char* p, bool nl) {
    write(p, nl);
    os << ": ";
    first = true;
}

void JsonWriter::write_key(string p, bool nl) {
    write(p, nl);
    os << ": ";
    first = true;
}

// called before output of next element
void JsonWriter::flush() {
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
    "begin_array", "end_array", "value_string", "value_number",
    "value_key" };

JsonException::JsonException(const char* desc) {
    what_str = string("Json parse error: ") + desc;
}

JsonParser::JsonParser(istream& i)
    : is(i),
    depth(0),
    cur_tok(no_token),
    nl(false),
    next_depth(0),
    next_tok(no_token) {}

void JsonParser::throw_unexpected(token expect) {
    ostringstream b;
    b << "unexpected token: " << token_names[cur_tok]
      << " (expected: " << token_names[expect] << ")"
      << endl;
    throw JsonException(b.str().c_str());
}

const char* unicode2utf8(unsigned int input) {
    const int maskbits   = 0x3F;
    const int maskbyte   = 0x80;
    const int mask2bytes = 0xC0;
    const int mask3bytes = 0xE0;
    static char result[4];
    int n = 0;
    // 0xxxxxxx
    if (input < 0x80) {
        result[n++] = static_cast<char>(input);

    // 110xxxxx 10xxxxxx
    } else if (input < 0x800) {
        result[n++] = (static_cast<char>(mask2bytes | (input >> 6)));
        result[n++] = (static_cast<char>(maskbyte | (input & maskbits)));

    // 1110xxxx 10xxxxxx 10xxxxxx
    } else {
        result[n++] = (static_cast<char>(mask3bytes | (input >> 12)));
        result[n++] = (static_cast<char>(maskbyte | ((input >> 6) & maskbits)));
        result[n++] = (static_cast<char>(maskbyte | (input & maskbits)));
    }
    result[n++] = '\0';
    return result;
}

const char* JsonParser::readcode() {
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

string JsonParser::readstring() {
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
        } else if (c == '"') {
            return os.str();
        } else {
            os << c;
        }
    } while (true);
}

string JsonParser::readnumber(char c) {
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

void JsonParser::read_next() {
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
            if (c == ':') {
                next_tok = value_key;
            } else {
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

JsonParser::token JsonParser::next(token expect) {
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


void JsonParser::copy_object(JsonWriter& jw) {
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
            jw.write(current_value(), nl);
            break;
        case value_number:
            jw.write_lit(current_value(), nl);
            break;
        case value_key:
            jw.write_key(current_value().c_str(), nl);
            break;
        default:
            throw JsonException("unexpected token");
        }
    } while (curdepth != depth);
}

void JsonParser::skip_object() {
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

static void write_parameters(JsonWriter &w, bool preset) {
    w.begin_object(true);
    for (gx_gui::ParamMap::iterator i = gx_gui::parameter_map.begin();
                                   i != gx_gui::parameter_map.end(); i++) {
        gx_gui::Parameter *param = i->second;
        if ((preset and param->isInPreset()) or(!preset and !param->isInPreset())) {
            param->writeJSON(w);
            w.newline();
        }
    }
    w.end_object(true);
}

static void read_parameters(JsonParser &jp, gx_gui::paramlist& plist, bool preset) {
    jp.next(JsonParser::begin_object);
    do {
        jp.next(JsonParser::value_key);
        if (!gx_gui::parameter_map.hasId(jp.current_value())) {
            gx_print_warning(_("recall settings"),
                             _("unknown parameter: ")+jp.current_value());
            jp.skip_object();
            continue;
        }
        gx_gui::Parameter& param = gx_gui::parameter_map[jp.current_value()];
        if (!preset and param.isInPreset()) {
            gx_print_warning(_("recall settings"),
                             _("preset-parameter ")+param.id()+_(" in settings"));
            jp.skip_object();
            continue;
        } else if (preset and !param.isInPreset()) {
            gx_print_warning(_("recall settings"),
                             _("non preset-parameter ")+param.id()+_(" in preset"));
            jp.skip_object();
            continue;
        }
        param.readJSON_value(jp);
        plist.push_back(&param);
    } while (jp.peek() == JsonParser::value_key);
    jp.next(JsonParser::end_object);
}

void write_preset(JsonWriter &w, bool write_midi, bool force_midi) {
    w.begin_object(true);
    w.write_key("engine");
    write_parameters(w, true);
    w.write_key("jconv");
    gx_engine::GxEngine::get_engine().convolver.jcset.writeJSON(w); //FIXME
    if (force_midi || (write_midi &&
                       gx_gui::parameter_map["system.midi_in_preset"].getSwitch().get())) {
        w.write_key("midi_controller");
        gx_gui::controller_map.writeJSON(w);
    }
    w.newline();
    w.end_object(true);
}

void fixup_parameters(int major, int minor) {
    assert(gx_gui::parameter_map.hasId("jconv.wet_dry"));
    if (major == majorversion && minor == minorversion) {
        return;
    }
    if (major == 1 && minor < 2) {
        if (gx_gui::parameter_map.hasId("jconv.wet_dry")) {
            gx_gui::Parameter& p = gx_gui::parameter_map["jconv.wet_dry"];
            if (p.isFloat()) {
                p.getFloat().convert_from_range(-1, 1);
            }
        }
    }
}

void PresetReader::clear() {
    plist.clear();
    if (m) {
        delete m;
        m = 0;
    }
}

void PresetReader::read(JsonParser &jp, bool *has_midi, int major, int minor) {
    clear();
    if (has_midi) {
        *has_midi = false;
    }
    jp.next(JsonParser::begin_object);
    do {
        jp.next(JsonParser::value_key);
        if (jp.current_value() == "engine") {
            read_parameters(jp, plist, true);
        } else if (jp.current_value() == "jconv") {
            gx_engine::GxEngine::get_engine().convolver.jcset = gx_engine::GxJConvSettings(jp); //FIXME
        } else if (jp.current_value() == "midi_controller") {
            if (has_midi || gx_gui::parameter_map["system.midi_in_preset"].getSwitch().get()) {
                m = new gx_gui::MidiControllerList::controller_array
                               (gx_gui::MidiControllerList::controller_array_size);
                gx_gui::controller_map.readJSON(jp, *m);
                if (has_midi) {
                    *has_midi = true;
                }
            } else {
                jp.skip_object();
            }
        } else {
            gx_print_warning(_("recall settings"),
                             _("unknown preset section: ") + jp.current_value());
        }
    } while (jp.peek() == JsonParser::value_key);
    jp.next(JsonParser::end_object);
    gx_gui::controller_map.remove_controlled_parameters(plist, m);
    fixup_parameters(major, minor);
}

void PresetReader::commit() {
    for (gx_gui::paramlist::iterator i = plist.begin(); i != plist.end(); i++) {
        (*i)->setJSON_value();
    }
    if (m) {
        gx_gui::controller_map.set_controller_array(*m);
    }
    clear();
}

void writeHeader(JsonWriter& jw) {
    jw.write("gx_head_file_version");
    jw.begin_array();
    jw.write(majorversion); // major format version
    jw.write(minorversion); // minor format version
    jw.write(GX_VERSION);
    jw.end_array(true);
}

bool readHeader(JsonParser& jp, int *major, int *minor) {
    jp.next(JsonParser::value_string);
    if (jp.current_value() != "gx_head_file_version") {
        throw JsonException("invalid gx_head file header");
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
    jp.next(JsonParser::value_string); // gx_head version
    jp.next(JsonParser::end_array);
    return m == majorversion && n == minorversion;
}

static void write_jack_port_connections(JsonWriter& w, const char *key, jack_port_t *port) {
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

void write_jack_connections(JsonWriter& w, gx_jack::GxJack& jack) {
    w.begin_object(true);
    write_jack_port_connections(w, "input", jack.input_ports[0]);
    write_jack_port_connections(w, "output1", jack.output_ports[2]);
    write_jack_port_connections(w, "output2", jack.output_ports[3]);
    write_jack_port_connections(w, "midi_input", jack.midi_input_port);
    write_jack_port_connections(w, "midi_output", jack.midi_output_ports);
    write_jack_port_connections(w, "insert_out", jack.output_ports[0]);
    write_jack_port_connections(w, "insert_in", jack.input_ports[1]);
    w.end_object(true);
}

// -- save state including current preset data
bool saveStateToFile(const string &filename, gx_jack::GxJack& jack) {
    gx_print_info(_("writing to "), filename.c_str());
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
    write_jack_connections(w, jack);

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

static void read_jack_connections(JsonParser& jp) {
    jp.next(JsonParser::begin_object);
    while (jp.peek() == JsonParser::value_key) {
        int i;
        jp.next(JsonParser::value_key);
        if (jp.current_value() == "input") {
            i = gx_jack::GxJack::kAudioInput;
        } else if (jp.current_value() == "output1") {
            i = gx_jack::GxJack::kAudioOutput1;
        } else if (jp.current_value() == "output2") {
            i = gx_jack::GxJack::kAudioOutput2;
        } else if (jp.current_value() == "midi_input") {
            i = gx_jack::GxJack::kMidiInput;
        } else if (jp.current_value() == "midi_output") {
            i = gx_jack::GxJack::kMidiOutput;
        } else if (jp.current_value() == "insert_out") {
            i = gx_jack::GxJack::kAudioInsertOut;
        } else if (jp.current_value() == "insert_in") {
            i = gx_jack::GxJack::kAudioInsertIn;
        } else {
            gx_print_warning(_("recall state"),
                             _("unknown jack ports sections") + jp.current_value());
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
bool recallState(const string &filename) {
    ifstream f(filename.c_str());
    if (!f.good()) {
        return false;
    }
    gx_gui::paramlist plist;
    gx_gui::MidiControllerList::controller_array m
            (gx_gui::MidiControllerList::controller_array_size);
    gx_system::JsonParser jp(f);
    try {
        jp.next(JsonParser::begin_array);

        int major, minor;
        readHeader(jp, &major, &minor);
        if (major != majorversion) {
            if (major == 0) {
                gx_print_info(_("recall settings"), _("loading converted state"));
            } else {
                stringstream s;
                s << _("major version mismatch in ")+filename+_(": found ")
                  << major << _(", expected ") << majorversion << endl;
                gx_print_warning(_("recall settings"), s.str());
            }
        }

        // other sections (settings, current_preset)
        do {
            jp.next(JsonParser::value_string);
            if (jp.current_value() == "settings") {
                read_parameters(jp, plist, false);
            } else if (jp.current_value() == "current_preset") {
                PresetReader p(jp, 0, major, minor);
            } else if (jp.current_value() == "midi_controller") {
                gx_gui::controller_map.readJSON(jp, m);
            } else if (jp.current_value() == "midi_ctrl_names") {
                gx_gui::midi_std_ctr.readJSON(jp);
            } else if (jp.current_value() == "jack_connections") {
                read_jack_connections(jp);
            } else {
                gx_print_warning(_("recall settings"),
                                 _("unknown section: ") + jp.current_value());
                jp.skip_object();
            }
        } while (jp.peek() == JsonParser::value_string);
        jp.next(JsonParser::end_array);
        jp.next(JsonParser::end_token);
    } catch(JsonException& e) {
        gx_print_error(_("recall settings"), _("invalid settings file: ") + filename);
        return false;
    }
    for (gx_gui::paramlist::iterator i = plist.begin(); i != plist.end(); i++) {
        (*i)->setJSON_value();
    }
    gx_gui::controller_map.set_controller_array(m);
    return true;
}
} /* end of gx_system namespace */
