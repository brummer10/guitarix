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

#include "engine.h"               // NOLINT

#include <sys/stat.h>

namespace gx_system {

static bool check_mtime(const std::string& filename, time_t& mtime) {
    struct stat st;
    if (stat(filename.c_str(), &st) != 0) {
	mtime = 0;
	return false;
    }
    time_t t = max(st.st_mtime, st.st_ctime);
    if (t == mtime) {
	return true;
    }
    mtime = t;
    return false;
}

/****************************************************************
 ** JsonWriter
 */

JsonWriter::JsonWriter(ostream *o, bool enable_newlines)
    : os(o),
      first(true),
      deferred_nl(enable_newlines ? 0 : -1),
      indent("") {}

JsonWriter::~JsonWriter() {
    close();
}

void JsonWriter::reset() {
    os->flush();
    first = true;
    if (deferred_nl == 1) {
	deferred_nl = 0;
    }
    indent.clear();
}

void JsonWriter::close() {
    if (is_closed()) {
	return;
    }
    if (deferred_nl == 1) {
	*os << endl;
    }
    os = 0;
}

inline void JsonWriter::komma() {
    if (first)
        first = false;
    else if (deferred_nl == 0)
        *os << ", ";
    else
        *os << ",";
    flush();
}

inline void JsonWriter::space() {
    if (first)
        first = false;
    else if (deferred_nl == 0)
        *os << " ";
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

template<class T> static inline T fp_sanitize(T v) {
    switch (fpclassify(v)) {
    case FP_NORMAL: return v;
    case FP_NAN: assert(false); return 1e50;
    case FP_INFINITE: assert(false); return (v < 0 ? -1e50 : 1e50);
    case FP_SUBNORMAL: return 0;
    }
    return v;
}

void JsonWriter::write(float v, bool nl) {
    komma();
    *os << fp_sanitize(v);
    snl(nl);
}

void JsonWriter::write(double v, bool nl) {
    komma();
    *os << fp_sanitize(v);
    snl(nl);
}

void JsonWriter::write(int i, bool nl) {
    komma();
    *os << i;
    snl(nl);
}

void JsonWriter::write(unsigned int i, bool nl) {
    komma();
    *os << i;
    snl(nl);
}

void JsonWriter::write_lit(const string& s, bool nl) {
    komma();
    *os << s;
    snl(nl);
}

void JsonWriter::write(const char* p, bool nl) {
    if (p) {
	komma();
	*os << '"';
	for (; *p; p++) {
	    switch (*p) {
	    case '\\': case '"': *os << '\\'; break;
	    case '\b': *os << '\\'; *os << 'b'; continue;       // NOLINT
	    case '\f': *os << '\\'; *os << 'f'; continue;       // NOLINT
	    case '\n': *os << '\\'; *os << 'n'; continue;       // NOLINT
	    case '\r': *os << '\\'; *os << 'r'; continue;       // NOLINT
	    case '\t': *os << '\\'; *os << 't'; continue;       // NOLINT
	    }
	    *os << *p;
	}
	*os << '"';
    } else {
	write_null();
    }
    snl(nl);
}

void JsonWriter::begin_object(bool nl) {
    komma();
    *os << '{';
    snl(nl);
    first = true;
    iplus();
}

void JsonWriter::end_object(bool nl) {
    iminus();
    flush();
    first = false;
    *os << '}';
    snl(nl);
}

void JsonWriter::begin_array(bool nl) {
    komma();
    *os << '[';
    snl(nl);
    first = true;
    iplus();
}

void JsonWriter::end_array(bool nl) {
    iminus();
    flush();
    first = false;
    *os << ']';
    snl(nl);
}

void JsonWriter::write_key(const char* p, bool nl) {
    write(p, nl);
    *os << ": ";
    first = true;
}

void JsonWriter::write_key(const string& p, bool nl) {
    write(p, nl);
    *os << ": ";
    first = true;
}

// called before output of next element
void JsonWriter::flush() {
    if (deferred_nl == 1) {
        *os << endl;
        deferred_nl = false;
        *os << indent;
    }
}


/****************************************************************
 ** class JsonStringWriter
 */

void JsonStringWriter::send_notify_begin(const char *method) {
    begin_object();
    write_key("jsonrpc");
    write("2.0");
    write_key("method");
    write(method);
    write_key("params");
    begin_array();
}

void JsonStringWriter::send_notify_end() {
    end_array();
    end_object();
}


/****************************************************************
 ** JsonParser
 */

JsonException::JsonException(const Glib::ustring& desc) {
    what_str = "Json parse error: " + desc;
}

void JsonParser::reset() {
    depth = 0;
    cur_tok = no_token;
    str.clear();
    nl = false;
    next_depth = 0;
    next_tok = no_token;
    next_str.clear();
    next_pos = 0;
}

JsonParser::JsonParser(istream* i)
    : is(i),
      depth(0),
      cur_tok(no_token),
      str(),
      nl(false),
      next_depth(0),
      next_tok(no_token),
      next_str(),
      next_pos(0) {
}

JsonParser::~JsonParser() {
    close();
}

void JsonParser::close() {
    if (is_closed()) {
	return;
    }
    is = 0;
}

const char* JsonParser::get_token_name(token tok) {
    switch (tok) {
    case no_token: return "no_token";
    case end_token: return "end_token";
    case begin_object: return "begin_object";
    case end_object: return "end_object";
    case begin_array: return "begin_array";
    case end_array: return "end_array";
    case value_string: return "value_string";
    case value_number: return "value_number";
    case value_key: return "value_key";
    case value_null: return "value_null";
    case value_bool: return "value_bool";
    case value_false: return "value_false";
    case value_true: return "value_true";
    default: assert(false); return 0;
    }
}

void JsonParser::throw_unexpected(token expect) {
    ostringstream b;
    b << "unexpected token: " << get_token_name(cur_tok)
      << " (expected: " << get_token_name(expect) << ")"
      << endl;
    //cerr << b.str() << endl; assert(false);
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
        int n = is->get();
        if (!is->good())
            throw JsonExceptionEOF("eof");
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
        is->get(c);
        if (!is->good())
            return "";
        if (c == '\\') {
            is->get(c);
            if (!is->good())
                return "";
            switch (c) {
            case 'b': os << '\b'; break;
            case 'f': os << '\f'; break;
            case 'n': os << '\n'; break;
            case 'r': os << '\r'; break;
            case 't': os << '\t'; break;
	    case '"': os << '"'; break;
            case 'u': os << readcode(); break;
            default: is->get(c); os << c; break;
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
    static int count_dn = 0;
    do {
        os << c;
        c = is->peek();
        switch (c) {
        case '+': case '-': case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9': case 'e': case 'E':
        case '.': 
            break;
        // read denormal value
        case 'n': case 'a': case 'i': case 'f':
			++count_dn;
			if (count_dn >=3) {
				gx_print_warning("JsonParser", Glib::ustring::compose("DENORMAL VALUE DETECTED in %1", log_tok));
				count_dn = 0;
			}
			break;
        default:
            return os.str();
        }
        is->get(c);
    } while (is->good());
    return "";
}

JsonParser::token JsonParser::read_value_token(char c) {
    ostringstream os("");
    do {
        os << c;
        c = is->peek();
	if (c < 'a' || c > 'z') {
	    break;
        }
        is->get(c);
    } while (is->good());
    next_str = os.str();
    if (next_str == "null") {
	return value_null;
    }
    if (next_str == "true") {
	return value_true;
    }
    if (next_str == "false") {
	return value_false;
    }
    return no_token;
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
            is->get(c);
            if (!is->good())
                throw JsonExceptionEOF("eof");
            if (c == '\n')
                nl = true;
        } while (c == ' ' || c == '\t' || c == '\r' || c == '\n');
	next_pos = is->tellg();
        switch (c) {
        case '[': next_tok = begin_array; next_depth++; break;

        case ']': next_tok = end_array; next_depth--; break;

        case '{': next_tok = begin_object; next_depth++; break;

        case '}': next_tok = end_object; next_depth--; break;

        case ',': continue;

        case '"':
            next_str = log_tok = readstring();
             *is >> c;
            if (!is->good())
                throw JsonExceptionEOF("eof");
            if (c == ':') {
                next_tok = value_key;
            } else {
                is->unget();
                next_tok = value_string;
            }
            break;

        case '-': case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            next_str = readnumber(c);
            next_tok = value_number;
            break;
        // read denormal value
		case 'a': case 'i': case 'f':
            next_str = readnumber(c);
            next_tok = value_number;
            break;

        default:
	    next_tok = read_value_token(c);
	    if (next_tok == no_token) {
		throw JsonException("bad token");
	    }
	    break;
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

bool JsonParser::read_kv(const char *key, float& v) {
    if (str == key) {
	next(value_number);
	v = current_value_float();
	return true;
    } else {
	return false;
    }
}

bool JsonParser::read_kv(const char *key, double& v) {
    if (str == key) {
	next(value_number);
	v = current_value_double();
	return true;
    } else {
	return false;
    }
}

bool JsonParser::read_kv(const char *key, int& i) {
    if (str == key) {
	next(value_number);
	i = current_value_int();
	return true;
    } else {
	return false;
    }
}

bool JsonParser::read_kv(const char *key, unsigned int& i) {
    if (str == key) {
	next(value_number);
	i = current_value_uint();
	return true;
    } else {
	return false;
    }
}

bool JsonParser::read_kv(const char *key, string& s) {
    if (str == key) {
	next(value_string);
	s = current_value();
	return true;
    } else {
	return false;
    }
}

bool JsonParser::read_kv(const char *key, Glib::ustring& s) {
    if (str == key) {
	next(value_string);
	s = current_value();
	return true;
    } else {
	return false;
    }
}

void JsonParser::set_streampos(streampos pos) {
    is->seekg(pos);
    depth = 0;
    cur_tok = no_token;
    nl = false;
    next_depth = 0;
    next_tok = no_token;
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

JsonSubParser::JsonSubParser(JsonParser& jp, streampos pos)
    : JsonParser() {
    set_stream(jp.get_stream());
    position = get_stream()->tellg();
    set_streampos(pos);
}

JsonSubParser::~JsonSubParser() {
    get_stream()->seekg(position);
}

/****************************************************************
 ** class SettingsFileHeader
 */

const string SettingsFileHeader::gx_version = GX_VERSION;

void SettingsFileHeader::read(JsonParser& jp) {
    jp.next(JsonParser::value_string);
    if (jp.current_value() != "gx_head_file_version") {
        throw JsonException("invalid gx_head file header");
    }
    jp.next(JsonParser::begin_array);
    jp.next(JsonParser::value_number);
    file_major = jp.current_value_int();
    jp.next(JsonParser::value_number);
    file_minor = jp.current_value_int();
    jp.next(JsonParser::value_string);
    file_gx_version = jp.current_value();
    jp.next(JsonParser::end_array);
}

void SettingsFileHeader::write(JsonWriter& jw) {
    jw.write("gx_head_file_version");
    jw.begin_array();
    jw.write(major); // major format version
    jw.write(minor); // minor format version
    jw.write(gx_version);
    jw.end_array(true);
}

void SettingsFileHeader::write_current_major_minor(JsonWriter& jw) {
    jw.begin_array();
    jw.write(major);
    jw.write(minor);
    jw.end_array();
}

void SettingsFileHeader::write_major_minor(JsonWriter& jw) {
    jw.begin_array();
    jw.write(file_major);
    jw.write(file_minor);
    jw.end_array();
}

void SettingsFileHeader::read_major_minor(JsonParser& jp) {
    jp.next(JsonParser::begin_array);
    jp.next(JsonParser::value_number);
    file_major = jp.current_value_int();
    jp.next(JsonParser::value_number);
    file_minor = jp.current_value_int();
    jp.next(JsonParser::end_array);
}

bool SettingsFileHeader::make_empty_settingsfile(const string& name) {
    ofstream os(name.c_str());
    if (!os.good()) {
	return false;
    }
    os.imbue(std::locale::classic());
    JsonWriter jw(&os);
    jw.begin_array();
    SettingsFileHeader::write(jw);
    jw.end_array(true);
    jw.close();
    os.close();
    return true;
}


/****************************************************************
 ** class StateFile
 */

class JsonReader: public JsonParser {
public:
    JsonReader(istream* is) : JsonParser(is) {}
    ~JsonReader();
    void close();
};

JsonReader::~JsonReader() {
    close();
}

void JsonReader::close() {
    if (is_closed()) {
	return;
    }
    next(JsonParser::end_array);
    next(JsonParser::end_token);
    JsonParser::close();
}

JsonParser *StateFile::create_reader() {
    if (is) {
    is->imbue(std::locale::classic());
	is->seekg(0);
    } else {
	check_mtime(filename, mtime);
	is = new ifstream(filename.c_str());
    is->imbue(std::locale::classic());
    }
    JsonReader *jp = new JsonReader(is);
    jp->next(JsonParser::begin_array);
    header.read(*jp);
    if (header.is_major_diff()) {
	if (header.get_major() == 0) {
	    gx_print_info(_("recall settings"), _("loading converted state"));
	} else {
	    gx_print_warning(
		_("recall settings"),
		boost::format(_("major version mismatch in %1%: found %2%, expected %3%"))
		% filename % header.get_major() % static_cast<int>(SettingsFileHeader::major));
	}
    }
    return jp;
}

void StateFile::set_filename(const string& fn) {
    filename = fn;
    delete is;
    is = 0;
}

void StateFile::ensure_is_current() {
    if (filename.empty() || !mtime) {
	return;
    }
    if (check_mtime(filename, mtime)) {
	return;
    }
    delete is;
    is = 0;
}


class ModifyState: public JsonWriter {
private:
    string filename;
    string tmpfile;
    ofstream os;
public:
    ModifyState(const string& name);
    ~ModifyState();
    virtual void close();
};

ModifyState::ModifyState(const string& name)
    : filename(name),
      tmpfile(filename + "_tmp"),
      os(tmpfile.c_str()) {
    set_stream(&os);
    begin_array();
    SettingsFileHeader::write(*this);
}

ModifyState::~ModifyState() {
    close();
}

void ModifyState::close() {
    if (is_closed()) {
	return;
    }
    end_array(true);
    JsonWriter::close();
    os.close();
    if (!os.good()) {
	gx_print_error(_("save preset"),
		       boost::format(_("couldn't write %1%")) % tmpfile);
    } else {
	int rc = rename(tmpfile.c_str(), filename.c_str());
	if (rc != 0) {
	    gx_print_error(_("save preset"),
			   boost::format(_("couldn't rename %1% to %2%"))
			   % tmpfile % filename);
	}
    }
}

class ModifyStatePreservePreset: public ModifyState {
private:
    ifstream is;
    JsonParser jp;
public:
    ModifyStatePreservePreset(const string& name, bool *preserve_preset);
    ~ModifyStatePreservePreset();
};

ModifyStatePreservePreset::ModifyStatePreservePreset(const string& name, bool *preserve_preset)
    : ModifyState(name),
      is(name.c_str()),
      jp(&is) {
    bool copied = false;
    if (is.good()) {
	try {
	    jp.next(JsonParser::begin_array);
	    SettingsFileHeader header;
	    header.read(jp);
	    while (jp.peek() != JsonParser::end_array) {
		jp.next(JsonParser::value_string);
		if (jp.current_value() == "current_preset") {
		    write(jp.current_value());
		    jp.copy_object(*this);
		    copied = true;
		} else {
		    jp.skip_object();
		}
	    }
	} catch(JsonException& e) {
	    // just ignore
	}
    }
    if (!copied) {
	*preserve_preset = false;
    }
}

ModifyStatePreservePreset::~ModifyStatePreservePreset() {
}

JsonWriter *StateFile::create_writer(bool *preserve_preset) {
    JsonWriter *jw;
    if (*preserve_preset) {
	jw = new ModifyStatePreservePreset(filename, preserve_preset);
    } else {
	jw = new ModifyState(filename);
    }
    delete is;
    is = 0;
    return jw;
}


/****************************************************************
 ** class PresetFile
 */

PresetFile::PresetFile()
    : filename(),
      is(0),
      mtime(),
      header(),
      entries(),
      name(),
      tp(),
      flags() {
}

void PresetFile::readJSON_remote(JsonParser& jp) {
    entries.clear();
    flags = 0;
    name = "";
    tp = PresetFile::PRESET_FILE;
    jp.next(JsonParser::begin_object);
    while (jp.peek() != JsonParser::end_object) {
	jp.next(JsonParser::value_key);
	if (jp.current_value() == "name") {
	    jp.next(JsonParser::value_string);
	    name = jp.current_value();
	} else if (jp.current_value() == "type") {
	    jp.next(JsonParser::value_string);
	    if (jp.current_value() == "scratch") {
		tp = PresetFile::PRESET_SCRATCH;
	    } else if (jp.current_value() == "factory") {
		tp = PresetFile::PRESET_FACTORY;
	    } else if (jp.current_value() == "file") {
		tp = PresetFile::PRESET_FILE;
	    }
	} else if (jp.current_value() == "mutable") {
	    jp.skip_object();
	} else if (jp.current_value() == "flag_invalid") {
	    flags |= PRESET_FLAG_INVALID;
	} else if (jp.current_value() == "flag_readonly") {
	    flags |= PRESET_FLAG_READONLY;
	} else if (jp.current_value() == "flag_versiondiff") {
	    flags |= PRESET_FLAG_VERSIONDIFF;
	} else if (jp.current_value() == "presets") {
	    jp.next(JsonParser::begin_array);
	    while (jp.peek() != JsonParser::end_array) {
		jp.next(JsonParser::value_string);
		entries.push_back(Position(jp.current_value(), 0));
	    }
	    jp.next(JsonParser::end_array);
	} else {
	    gx_print_warning(
		"PresetFile", Glib::ustring::compose("%1: unknown remote key: %2", name, jp.current_value()));
	}
    }
    jp.next(JsonParser::end_object);
}

void PresetFile::writeJSON_remote(gx_system::JsonWriter& jw) {
    jw.begin_object();
    jw.write_key("name");
    jw.write(name);
    jw.write_key("mutable");
    jw.write(is_mutable());
    jw.write_key("type");
    switch (tp) {
    case gx_system::PresetFile::PRESET_SCRATCH: jw.write("scratch"); break;
    case gx_system::PresetFile::PRESET_FACTORY: jw.write("factory"); break;
    case gx_system::PresetFile::PRESET_FILE: jw.write("file"); break;
    default: jw.write("unknown"); break;
    }
    if (flags & gx_system::PRESET_FLAG_INVALID) {
	jw.write_key("flag_invalid");
    }
    if (flags & gx_system::PRESET_FLAG_READONLY) {
	jw.write_key("flag_readonly");
    }
    if (flags & gx_system::PRESET_FLAG_VERSIONDIFF) {
	jw.write_key("flag_versiondiff");
    }
    jw.write_key("presets");
    jw.begin_array();
    for (int i = 0; i < size(); i++) {
	jw.write(entries[i].name);
    }
    jw.end_array();
    jw.end_object();
}

bool PresetFile::set_factory(const Glib::ustring& name_, const std::string& path) {
    check_mtime(path, mtime);
    if (mtime == 0) {
	gx_print_error(
	    _("open factory preset"),
	    boost::format(_("couldn't open %1%")) % path);
	return false;
    }
    name = name_;
    filename = path;
    tp = PRESET_FACTORY;
    flags = 0;
    header.set_to_current();
    return true;
}

bool PresetFile::fail() {
    try {
	reopen();
    } catch (gx_system::JsonException& e) {
	gx_print_error(filename.c_str(), _("parse error"));
	return true;
    }
    return is->fail();
}

bool PresetFile::open_file(const Glib::ustring& name_, const std::string& path, int tp_, int flags_) {
    name = name_;
    filename = path;
    tp = tp_;
    flags = flags_;
    if (fail()) {
	set_flag(PRESET_FLAG_INVALID, true);
	return false;
    }
    set_flag(PRESET_FLAG_INVALID, false);
    check_flags();
    return true;
}

bool PresetFile::create_file(const Glib::ustring& name_, const std::string& path, int tp_, int flags_) {
    name = name_;
    filename = path;
    tp = tp_;
    flags = flags_;
    bool res = SettingsFileHeader::make_empty_settingsfile(path);
    if (res) {
	header.set_to_current();
	check_mtime(path, mtime);
    } else {
	gx_print_error(
	    _("create preset bank"),
	    boost::format(_("couldn't create %1%")) % path);
    }
    return res;
}

void PresetFile::check_flags() {
    set_flag(PRESET_FLAG_READONLY, access(filename.c_str(), W_OK) != 0);
    set_flag(PRESET_FLAG_VERSIONDIFF, !header.is_current());
}

bool PresetFile::readJSON(const std::string& dirpath, JsonParser &jp, bool *mtime_diff) {
    jp.next(gx_system::JsonParser::begin_array);
    jp.next(gx_system::JsonParser::value_string);
    name = jp.current_value();
    jp.next(gx_system::JsonParser::value_string);
    filename = Glib::build_filename(dirpath, jp.current_value());
    jp.next(gx_system::JsonParser::value_number);
    tp = jp.current_value_int();
    jp.next(gx_system::JsonParser::value_number);
    flags = jp.current_value_int();
    header.read_major_minor(jp);
    jp.next(gx_system::JsonParser::value_number);
    mtime = jp.current_value_int();
    jp.next(gx_system::JsonParser::end_array);
    if (!check_mtime(filename, mtime)) {
	*mtime_diff = true;
	if (mtime == 0) {
	    gx_print_error(filename.c_str(), _("not found"));
	    return false;
	}
	try {
	    open();
	} catch (gx_system::JsonException& e) {
	    set_flag(PRESET_FLAG_INVALID, true);
	    gx_print_error(filename.c_str(), _("parse error"));
	    return false;
	}
	set_flag(PRESET_FLAG_INVALID, false);
	check_flags();
    }
    return true;
}

void PresetFile::writeJSON(JsonWriter& jw) {
    assert(tp == PRESET_FILE || tp == PRESET_SCRATCH);
    jw.begin_array();
    jw.write(name);
    jw.write(Gio::File::create_for_path(filename)->get_basename());
    jw.write(tp);
    jw.write(flags);
    header.write_major_minor(jw);
    jw.write(static_cast<int>(mtime));
    jw.end_array(true);
}

void PresetFile::open() {
    close();
    entries.clear();
    if (filename.empty()) {
	return;
    }
    check_mtime(filename, mtime);
    is = new ifstream(filename.c_str());
    is->imbue(std::locale::classic());
    JsonParser jp(is);
    jp.next(JsonParser::begin_array);
    header.read(jp);
    while (jp.peek() == JsonParser::value_string) {
	jp.next();
	if (jp.current_value() == "midi_controller") { //FIXME there should be a file signature
	    if (jp.peek() == JsonParser::begin_array) {
		entries.clear();
		is->setstate(istream::failbit);
		gx_print_error(
		    _("open preset"),
		    boost::format(_("%1% is a state file, not a preset file")) % filename);
		throw JsonException(_("This is a state file, not a preset file"));
	    }
	}
	streampos pos = jp.get_streampos();
	entries.push_back(Position(jp.current_value(), pos));
	jp.skip_object();
    }
    jp.next(JsonParser::end_array);
    jp.next(JsonParser::end_token);
}

int PresetFile::size() {
    try {
	reopen();
    } catch (gx_system::JsonException& e) {
	gx_print_error(filename.c_str(), _("parse error"));
    }
    return entries.size();
}

bool PresetFile::ensure_is_current() {
    if (filename.empty() || check_mtime(filename, mtime)) {
	return true;
    }
    if (!mtime) {
	return true;
    }
    close();
    return false;
}

bool PresetFile::is_newer(time_t m) {
    check_mtime(filename, mtime);
    return mtime >= m;
}

void PresetFile::open(const std::string& fname) {
    filename = fname;
    open();
}

const SettingsFileHeader& PresetFile::get_header() {
    reopen();
    return header;
}

void PresetFile::fill_names(vector<Glib::ustring>& l) {
    reopen();
    for (vector<Position>::const_iterator i = entries.begin(); i != entries.end(); ++i) {
	l.push_back(i->name);
    }
}

const Glib::ustring& PresetFile::get_name(int n) {
    reopen();
    return entries.at(n).name;
}

int PresetFile::get_index(const Glib::ustring& name) {
    try {
	reopen();
    } catch (gx_system::JsonException& e) {
	// will be reported elsewhere
	return -1;
    }
    for (int i = 0; i < size(); i++) {
	if (name == entries[i].name) {
	    return i;
	}
    }
    return -1;
}

JsonParser *PresetFile::create_reader(int n) {
    reopen();
    JsonParser *jp = new JsonParser(is);
    jp->set_streampos(entries.at(n).pos);
    return jp;
}

PresetTransformer::PresetTransformer(string fname, istream* is_)
    : JsonWriter(),
      filename(fname),
      tmpfile(filename + "_tmp"),
      os(tmpfile.c_str()),
      is(is_),
      jp(is_),
      header() {
    set_stream(&os);
    if (!is->fail()) {
	is->seekg(0);
	jp.next(JsonParser::begin_array);
	header.read(jp);
    }
    begin_array();
    header.write(*this);
}

PresetTransformer::~PresetTransformer() {
    // JsonParser destructor will only run JsonParser::close()
    close();
}

void PresetTransformer::abort() {
    if (is_closed()) {
	return;
    }
    JsonWriter::close();
    delete is;
    is = 0;
    os.close();
    remove(tmpfile.c_str());
}

void PresetTransformer::close_nocheck() {
    end_array(true);
    JsonWriter::close();
    delete is;
    is = 0;
    os.close();
    if (!os.good()) {
	gx_print_error(_("save preset"),
		       boost::format(_("couldn't write %1%")) % tmpfile);
	return;
    }
    int rc = rename(tmpfile.c_str(), filename.c_str());
    if (rc != 0) {
	gx_print_error(_("save preset"),
		       boost::format(_("couldn't rename %1% to %2%"))
		       % tmpfile % filename);
    }
}

void PresetTransformer::close() {
    if (is_closed()) {
	return;
    }
    if (!is->fail()) {
	jp.next(JsonParser::end_array);
	jp.next(JsonParser::end_token);
    }
    close_nocheck();
}

class ModifyPreset: public PresetTransformer {
public:
    ModifyPreset(string filename, istream* is, const Glib::ustring& presname);
    ~ModifyPreset();
    void close();
    void copy_object();
};

ModifyPreset::~ModifyPreset() {
    close();
}

ModifyPreset::ModifyPreset(string fname, istream* is, const Glib::ustring& presname)
    : PresetTransformer(fname, is) {
    if (!is->fail()) {
	while (jp.peek() != JsonParser::end_array) {
	    jp.next(JsonParser::value_string);
	    if (jp.current_value() == presname) {
		return;
	    } else {
		write(jp.current_value());
		jp.copy_object(*this);
	    }
	}
    }
}

void ModifyPreset::close() {
    if (is_closed()) {
	return;
    }
    if (!is->fail()) {
	while (jp.peek() != JsonParser::end_array) {
	    jp.next(JsonParser::value_string);
	    write(jp.current_value());
	    jp.copy_object(*this);
	}
    }
    PresetTransformer::close();
}

void ModifyPreset::copy_object() {
    jp.copy_object(*this);
}

JsonWriter *PresetFile::create_writer(const Glib::ustring& name) {
    reopen();
    ModifyPreset *jw = new ModifyPreset(filename, is, name);
    jw->write(name);
    if (!is->fail()) {
	if (jw->jp.peek() != JsonParser::end_array) {
	    jw->jp.skip_object(); // we are replacing a setting
	}
    }
    is = 0;
    return jw;
}

JsonWriter *PresetFile::create_writer_at(const Glib::ustring& pos, const Glib::ustring& name) {
    reopen();
    ModifyPreset *jw = new ModifyPreset(filename, is, pos);
    jw->write(name);
    is = 0;
    return jw;
}

PresetTransformer *PresetFile::create_transformer() {
    reopen();
    PresetTransformer *tr = new PresetTransformer(filename, is);
    is = 0;
    return tr;
}

bool PresetFile::erase(const Glib::ustring& name) {
    reopen();
    if (get_index(name) < 0) {
	return false;
    }
    ModifyPreset jw(filename, is, name);
    is = 0;
    jw.jp.skip_object();
    return true;
}

bool PresetFile::clear() {
    if (!SettingsFileHeader::make_empty_settingsfile(filename)) {
	return false;
    }
    open(filename);
    return true;
}

bool PresetFile::rename(const Glib::ustring& name, Glib::ustring newname) {
    reopen();
    if (get_index(name) < 0) {
	return false;
    }
    ModifyPreset jw(filename, is, name);
    is = 0;
    jw.write(newname);
    jw.jp.copy_object(jw);
    return true;
}

bool PresetFile::set_name(const Glib::ustring& n, const std::string& newfile) {
    if (!Gio::File::create_for_path(filename)->move(Gio::File::create_for_path(newfile))) {
	gx_print_error(_("rename bank"),
		       boost::format(_("couldn't move to %1%")) % newfile);
	return false;
    }
    name = n;
    filename = newfile;
    return true;
}

bool PresetFile::remove_file() {
    if (!Gio::File::create_for_path(filename)->remove()) {
	gx_print_error(_("remove bank"),
		       boost::format(_("couldn't remove %1%")) % filename);
	return false;
    }
    filename = "";
    return true;
}

PresetFile::iterator PresetFile::begin() {
    if (flags & PRESET_FLAG_INVALID) {
	return entries.end();
    }
    try {
	reopen();
    } catch (gx_system::JsonException& e) {
	gx_print_error(filename.c_str(), _("parse error"));
    }
    return entries.begin();
}


/****************************************************************
 ** class PresetBanks
 */

static const char *std_presetname_postfix = ".gx";

PresetBanks::PresetBanks()
    : banklist(), filepath(), mtime(), preset_dir() {
}

PresetBanks::~PresetBanks() {
    for (iterator i = begin(); i != end(); ++i) {
	delete *i;
    }
}

void PresetBanks::readJSON_remote(gx_system::JsonParser& jp) {
    for (iterator i = begin(); i != end(); ++i) {
	delete *i;
    }
    banklist.clear();
    jp.next(gx_system::JsonParser::begin_array);
    while (jp.peek() != gx_system::JsonParser::end_array) {
	gx_system::PresetFile *pf = new gx_system::PresetFile;
	pf->readJSON_remote(jp);
	banklist.push_back(pf);
    }
    jp.next(gx_system::JsonParser::end_array);
}

bool PresetBanks::check_reparse() {
    if (check_mtime(filepath, mtime)) {
	bool reload = false;
	for (iterator i = begin(); i != end(); ++i) {
	    int tp = i->get_type();
	    if (tp == PresetFile::PRESET_FILE || tp == PresetFile::PRESET_SCRATCH) {
		if (!i->ensure_is_current()) {
		    try {
			i->reopen();
			i->set_flag(PRESET_FLAG_INVALID, false);
		    } catch (gx_system::JsonException& e) {
			i->set_flag(PRESET_FLAG_INVALID, true);
			// no message, we already know the error
		    }
		    i->check_flags();
		    reload = true;
		}
	    }
	}
	return reload;
    }
    for (bl_type::iterator i = banklist.begin(); i != banklist.end();) {
	int tp = (*i)->get_type();
	if (tp == PresetFile::PRESET_FILE || tp == PresetFile::PRESET_SCRATCH) {
	    bl_type::iterator j = i;
	    ++i;
	    delete *j;
	    banklist.erase(j);
	} else {
	    ++i;
	}
    }
    parse_bank_list(banklist.begin());
    return true;
}

void PresetBanks::parse(const std::string& bank_path, const std::string& preset_dir_,
			const std::string& factory_dir, const char* scratchpad_name,
			const char* scratchpad_file) {
    filepath = bank_path;
    preset_dir = preset_dir_;
    banklist.clear();
    parse_bank_list(banklist.end());
    collect_lost_banks(scratchpad_name, scratchpad_file);
    parse_factory_list(factory_dir);
}

void PresetBanks::make_valid_utf8(Glib::ustring& s) {
   Glib::ustring::iterator i;
   while (!s.validate(i)) {
       Glib::ustring::iterator j = i;
       s.replace(i,++j,1,'?');
   }
   if (s.empty()) {
       s = "?";
   }
}

std::string PresetBanks::add_preset_postfix(const std::string& filename) {
    return filename + std_presetname_postfix;
}

bool PresetBanks::strip_preset_postfix(std::string& name) {
    if (name.compare(name.size()-3, 3, std_presetname_postfix) != 0) {
	return false;
    }
    name = name.substr(0, name.size()-3);
    return true;
}

void PresetBanks::make_bank_unique(Glib::ustring& name, std::string *file) {
    int n = 1;
    Glib::ustring t = name;
    while (true) {
	if (file) {
	    *file = add_preset_postfix(Glib::build_filename(preset_dir, encode_filename(name)));
	}
	if (!has_entry(name)) {
	    if (!file || !Gio::File::create_for_path(*file)->query_exists()) {
		return;
	    }
	}
	name = t + "-" + gx_system::to_string(n);
	n += 1;
    }
}

bool PresetBanks::has_file(const std::string& file) const {
    for (bl_type::const_iterator i = banklist.begin(); i != banklist.end(); ++i) {
	if ((*i)->get_filename() == file) {
	    return true;
	}
    }
    return false;
}

void PresetBanks::collect_lost_banks(const char* scratchpad_name, const char* scratchpad_file) {
    Glib::RefPtr<Gio::FileEnumerator> en = Gio::File::create_for_path(
	preset_dir)->enumerate_children(G_FILE_ATTRIBUTE_STANDARD_NAME);
    while (true) {
	Glib::RefPtr<Gio::FileInfo> fi = en->next_file();
	if (!fi) {
	    break;
	}
	std::string n = fi->get_name();
	if (n.size() <= 3 || n.substr(n.size()-3) != std_presetname_postfix) {
	    continue;
	}
	std::string path = Glib::build_filename(preset_dir, n);
	if (has_file(path)) {
	    continue;
	}
	PresetFile *f = new PresetFile();
	if (n == scratchpad_file) {
	    Glib::ustring nm = scratchpad_name;
	    make_bank_unique(nm);
	    f->open_file(nm, path, PresetFile::PRESET_SCRATCH, 0);
	} else {
	    strip_preset_postfix(n);
	    Glib::ustring nm = decode_filename(n);
	    make_valid_utf8(nm);
	    make_bank_unique(nm);
	    f->open_file(nm, path, PresetFile::PRESET_FILE, 0);
	}
	insert(f);
    }
}


void PresetBanks::insert(PresetFile* f, int position) {
    std::list<PresetFile*>::iterator i = banklist.begin();
    for (; position > 0 && i != banklist.end(); ++i, --position);
    banklist.insert(i, f);
    save();
}

void PresetBanks::check_save() {
    for (iterator i = begin(); i != end(); ++i) {
	int tp = i->get_type();
	if (tp == PresetFile::PRESET_FILE || tp == PresetFile::PRESET_SCRATCH) {
	    if (i->is_newer(mtime)) {
		save();
		return;
	    }
	}
    }
}

void PresetBanks::save() {
    if (filepath.empty()) { //FIXME remote operation hack
	return;
    }
    std::string tmpfile = filepath + "_tmp";
    ofstream os(tmpfile.c_str());
    os.imbue(std::locale::classic());
    gx_system::JsonWriter jw(&os);
    jw.begin_array(true);
    for (iterator i = begin(); i != end(); ++i) {
	int tp = i->get_type();
	if (tp == PresetFile::PRESET_FILE || tp == PresetFile::PRESET_SCRATCH) {
	    i->writeJSON(jw);
	}
    }
    jw.end_array(true);
    jw.close();
    os.close();
    if (!os.good()) {
	gx_print_error(_("save banklist"),
		       boost::format(_("couldn't write %1%")) % tmpfile);
    } else {
	int rc = ::rename(tmpfile.c_str(), filepath.c_str());
	if (rc != 0) {
	    gx_print_error(_("save banklist"),
			   boost::format(_("couldn't rename %1% to %2%"))
			   % tmpfile % filepath);
	}
    }
    check_mtime(filepath, mtime);
}

void PresetBanks::parse_factory_list(const std::string& path) {
    ifstream is(Glib::build_filename(path, "dirlist.js").c_str());
    if (is.fail()) {
	gx_print_error(_("Presets"), _("factory preset list not found"));
	return;
    }
    gx_system::JsonParser jp(&is);
    PresetFile *f = 0;
    try {
	jp.next(gx_system::JsonParser::begin_array);
	while (jp.peek() != gx_system::JsonParser::end_array) {
	    jp.next(gx_system::JsonParser::begin_array);
	    jp.next(gx_system::JsonParser::value_string);
	    string name = jp.current_value();
	    jp.next(gx_system::JsonParser::value_string);
	    string fname = Glib::build_filename(path, jp.current_value());
	    PresetFile *f = new PresetFile();
	    try {
		if (f->set_factory(name, fname)) {
		    banklist.push_back(f);
		} else {
		    delete f;
		}
	    } catch (gx_system::JsonException& e) {
		delete f;
		gx_print_error(fname.c_str(), _("not found or parse error"));
	    }
	    f = 0;
	    jp.next(gx_system::JsonParser::end_array);
	}
	jp.next(gx_system::JsonParser::end_array);
	jp.next(gx_system::JsonParser::end_token);
    } catch (gx_system::JsonException& e) {
	delete f;
    }
    jp.close();
    is.close();
}

void PresetBanks::parse_bank_list(bl_type::iterator pos) {
    ifstream is(filepath.c_str());
    if (is.fail()) {
	gx_print_error(
	    _("Presets"), boost::format(_("banks not found: '%1%'")) % filepath);
	return;
    }
    is.imbue(std::locale::classic());
    gx_system::JsonParser jp(&is);
    bool mtime_diff = false;
    PresetFile *f = 0;
    try {
	jp.next(gx_system::JsonParser::begin_array);
	while (jp.peek() != gx_system::JsonParser::end_array) {
	    f = new PresetFile();
	    if (!f->readJSON(preset_dir, jp, &mtime_diff)) {
		delete f;
	    } else {
		banklist.insert(pos, f);
	    }
	    f = 0;
	}
	jp.next(gx_system::JsonParser::end_array);
	jp.next(gx_system::JsonParser::end_token);
    } catch (gx_system::JsonException& e) {
	delete f;
	gx_print_error(filepath.c_str(), _("parse error"));
    }
    jp.close();
    is.close();
    if (mtime_diff) {
	save();
    } else {
	check_mtime(filepath, mtime);
    }
}

PresetFile *PresetBanks::get_file(const Glib::ustring& bank) const {
    for (bl_type::const_iterator i = banklist.begin(); i != banklist.end(); ++i) {
	if ((*i)->get_name() == bank) {
	    return *i;
	}
    }
    return 0;
}

int PresetBanks::get_index(const Glib::ustring& bank) const {
    int n = 0;
    for (bl_type::const_iterator i = banklist.begin(); i != banklist.end(); ++i) {
	if ((*i)->get_name() == bank) {
	    return n;
	}
	n += 1;
    }
    return -1;
}

bool PresetBanks::rename(const Glib::ustring& oldname, const Glib::ustring& newname, const std::string& newfile) {
    PresetFile *f = get_file(oldname);
    if (!f) {
	return false;
    }
    if (!f->set_name(newname, newfile)) {
	return false;
    }
    save();
    return true;
}

bool PresetBanks::remove(const Glib::ustring& bank) {
    PresetFile *f = get_file(bank);
    if (!f) {
	return false;
    }
    if (!f->remove_file()) {
	return false;
    }
    banklist.remove(f);
    delete f;
    save();
    return true;
}

void PresetBanks::reorder(const std::vector<Glib::ustring>& neworder) {
    bl_type::iterator j = banklist.begin();
    for (std::vector<Glib::ustring>::const_iterator i = neworder.begin(); i != neworder.end(); ++i) {
	assert(j != banklist.end());
	if (*i == (*j)->get_name()) {
	    ++j;
	} else {
	    for (bl_type::iterator k = j; k != banklist.end(); ++k) {
		if (*i == (*k)->get_name()) {
		    banklist.splice(j, banklist, k);
		    break;
		}
	    }
	}
    }
    save();
}

Glib::ustring PresetBanks::get_name(int n) {
	for (iterator i = begin(); i != end(); ++i, --n) {
	if (n == 0) {
	    return i->get_name();
	}
    }
    return "";
}

/****************************************************************
 ** class GxSettingsBase
 */

AbstractStateIO::~AbstractStateIO() {}
AbstractPresetIO::~AbstractPresetIO() {}

// seq_ may not yet be initialized, only use address!
GxSettingsBase::GxSettingsBase(gx_engine::EngineControl& seq_)
    : state_io(),
      preset_io(),
      statefile(),
      banks(),
      current_bank(),
      current_name(),
      seq(seq_),
      selection_changed(),
      presetlist_changed() {
}

GxSettingsBase::~GxSettingsBase() {
}

bool GxSettingsBase::loadsetting(PresetFile *p, const Glib::ustring& name) {
    try {
	if (p) {
	    JsonParser *jp = p->create_reader(name);
	    preset_io->read_preset(*jp, p->get_header());
	    seq.wait_ramp_down_finished();
	    preset_io->commit_preset();
	    delete jp;
	    gx_print_info(
		_("loaded preset"),
		boost::format(_("%1% from file %2%")) % name % p->get_filename());
		
	} else {
	    JsonParser *jp = statefile.create_reader();
	    state_io->read_state(*jp, statefile.get_header());
	    seq.wait_ramp_down_finished();
	    state_io->commit_state();
	    delete jp;
	    gx_print_info(
		_("loaded state"),
		boost::format(_("from file %1%")) % statefile.get_filename());
	}
	return seq.update_module_lists();
    } catch(JsonException& e) {
	if (p) {
	    gx_print_error(
		_("load preset"),
		boost::format(_("error loading %1% from file %2%")) % name % p->get_filename());
	} else {
	    gx_print_warning(
		_("load state"),
		boost::format(_("error loading state from file %1%"))
		% statefile.get_filename());
	}
	return false;
    }
}

void GxSettingsBase::load_preset(PresetFile* pf, const Glib::ustring& name) {
    PresetFile *p = get_current_bank_file();
    if (p && p->has_entry(current_name) && p->get_type() == gx_system::PresetFile::PRESET_SCRATCH) {
        JsonWriter *jw = 0;
        try {
            jw = p->create_writer(current_name);
            preset_io->write_preset(*jw);
        } catch(JsonException& e) {
            gx_print_warning(
                _("save preset"),
                boost::format(_("parse error in %1%"))
                % p->get_filename());
        }
        delete jw;
    }
    if (!pf->has_entry(name)) {
        gx_print_error(_("open preset"), Glib::ustring::compose("bank %1 does not contain preset %2", pf->get_name(), name));
        pf = 0;
    }
    if (!pf) {
        if (setting_is_preset()) {
            current_bank = "";
            current_name = "";
            selection_changed();
        }
        return;
    }
    current_bank = pf->get_name();
    current_name = name;
    seq.start_ramp_down();
    bool modules_changed = loadsetting(pf, name);
    seq.start_ramp_up();
    // if no modules changed either there was no change (then
    // rack_changed should not be set anyhow) or the modules
    // could not be installed because jack is not initialized.
    // In that case there is still a rack change left to be
    // done
    if (modules_changed) {
        seq.clear_rack_changed();
    }
    selection_changed();
}

void GxSettingsBase::loadstate() {
    current_bank = current_name = "";
    seq.start_ramp_down();
    bool modules_changed = loadsetting(0, current_name);
    seq.start_ramp_up();
    if (modules_changed) { // see comment in load_preset()
	seq.clear_rack_changed();
    }
    presetlist_changed();
    selection_changed();
}

void GxSettingsBase::set_source_to_state() {
    current_bank = current_name = "";
    selection_changed();
}

void GxSettingsBase::save_to_state(bool preserve_preset) {
    gx_print_info("write state",boost::format("%2% [%1%]")
			     % preserve_preset % statefile.get_filename());
    JsonWriter *jw = statefile.create_writer(&preserve_preset);
    state_io->write_state(*jw, preserve_preset);
    delete jw;
#if 0
    if (!preserve_preset && setting_is_preset()) {
	set_source_to_state();
	presetlist_changed();
    }
#endif
}

void GxSettingsBase::append(PresetFile& pf, const Glib::ustring& src, PresetFile& pftgt, const Glib::ustring& name) {
    JsonWriter *jw = 0;
    JsonParser *jp = 0;
    try {
	jp = pf.create_reader(src);
	jw = pftgt.create_writer(name);
	jp->copy_object(*jw);
    } catch(JsonException& e) {
	gx_print_warning(
	    _("save preset"),
	    boost::format(_("parse error in %1%"))
	    % pf.get_filename());
    }
    delete jp;
    delete jw;
    presetlist_changed();
}

void GxSettingsBase::insert_before(PresetFile& pf, const Glib::ustring& src, PresetFile& pftgt, const Glib::ustring& pos, const Glib::ustring& name) {
    JsonWriter *jw = 0;
    JsonParser *jp = 0;
    try {
	jp = pf.create_reader(src);
	jw = pftgt.create_writer_at(pos, name);
	jp->copy_object(*jw);
	jw->write(pos);
	dynamic_cast<ModifyPreset*>(jw)->copy_object();
    } catch(JsonException& e) {
	gx_print_warning(
	    _("save preset"),
	    boost::format(_("parse error in %1%"))
	    % pf.get_filename());
    }
    delete jp;
    delete jw;
    presetlist_changed();
}

void GxSettingsBase::insert_after(PresetFile& pf, const Glib::ustring& src, PresetFile& pftgt, const Glib::ustring& pos, const Glib::ustring& name) {
    int i = pftgt.get_index(pos) + 1;
    if (i >= pftgt.size()) {
	append(pf, src, pftgt, name);
    } else {
	insert_before(pf, src, pftgt, pftgt.get_name(i), name);
    }
}

void GxSettingsBase::save(PresetFile& pf, const Glib::ustring& name) {
    bool newentry = (pf.get_index(name) < 0);
    JsonWriter *jw = 0;
    try {
	jw = pf.create_writer(name);
	preset_io->write_preset(*jw);
    } catch(JsonException& e) {
	gx_print_warning(
	    _("save preset"),
	    boost::format(_("parse error in %1%"))
	    % pf.get_filename());
    }
    delete jw;
    if (newentry) {
	presetlist_changed();
    }
    if (!setting_is_preset()
	|| (setting_is_preset() && current_name != name)) {
	current_name = name;
	current_bank = pf.get_name();
	presetlist_changed();
	selection_changed();
    }
}

void GxSettingsBase::reorder_preset(PresetFile& pf, const std::vector<Glib::ustring>& neworder) {
    PresetTransformer *jw = 0;
    try {
	jw = pf.create_transformer();
	for (std::vector<Glib::ustring>::const_iterator i = neworder.begin(); i != neworder.end(); ++i) {
	    JsonParser *jp = pf.create_reader(*i);
	    jw->write(*i);
	    jp->copy_object(*jw);
	    delete jp;
	}
	jw->close_nocheck();
    } catch(JsonException& e) {
	gx_print_error(
	    _("reorder presetfile"),
	    boost::format(_("parse error in %1%"))
	    % pf.get_filename());
	jw->abort();
    }
    delete jw;
    pf.close();
    presetlist_changed();
}

void GxSettingsBase::erase_preset(PresetFile& pf, const Glib::ustring& name) {
    try {
	pf.erase(name);
    } catch(JsonException& e) {
	gx_print_warning(
	    _("delete preset"),
	    boost::format(_("parse error in %1%"))
	    % pf.get_filename());
    }
    if (pf.get_name() == current_bank && name == current_name) {
	set_source_to_state();
    }
    presetlist_changed();
}

bool GxSettingsBase::convert_preset(PresetFile& pf) {
    seq.start_ramp_down();
    bool preset_preset = false;
    JsonWriter *sw = statefile.create_writer(&preset_preset);
    state_io->write_state(*sw, preset_preset);
    delete sw;
    seq.wait_ramp_down_finished();
    PresetTransformer *jw = 0;
    bool res = true;
    try {
	jw = pf.create_transformer();
	while (jw->jp.peek() != JsonParser::end_array) {
	    jw->jp.next(JsonParser::value_string);
	    jw->write(jw->jp.current_value());
	    preset_io->copy_preset(jw->jp, jw->header, *jw);
	}
	pf.set_flag(PRESET_FLAG_VERSIONDIFF, false);
    } catch(JsonException& e) {
	gx_print_warning(
	    _("convert presetfile"),
	    boost::format(_("parse error in %1%"))
	    % pf.get_filename());
	res = false;
    }
    delete jw;
    JsonParser *sp = statefile.create_reader();
    state_io->read_state(*sp, statefile.get_header());
    state_io->commit_state();
    delete sp;
    seq.start_ramp_up();
    if (res) {
	presetlist_changed();
    }
    return res;
}

bool GxSettingsBase::rename_bank(const Glib::ustring& oldname, const Glib::ustring& newname, const std::string& newfile) {
    if (!banks.rename(oldname, newname, newfile)) {
	return false;
    }
    if (setting_is_preset() && oldname == current_bank) {
	current_bank = newname;
	presetlist_changed();
	selection_changed();
    } else {
	presetlist_changed();
    }
    return true;
}

bool GxSettingsBase::remove_bank(const Glib::ustring& bank) {
    if (!banks.remove(bank)) {
	return false;
    }
    if (bank == current_bank) {
	set_source_to_state();
	presetlist_changed();
	selection_changed();
    } else {
	presetlist_changed();
    }
    return true;
}

bool GxSettingsBase::rename_preset(PresetFile& pf, const Glib::ustring& oldname, const Glib::ustring& newname) {
    if (!pf.rename(oldname, newname)) {
	return false;
    }
    presetlist_changed();
    if (setting_is_preset() && current_bank == pf.get_name()) {
	if (current_name == oldname) {
	    current_name = newname;
	    selection_changed();
	}
    }
    return true;
}

} /* end of gx_system namespace */
