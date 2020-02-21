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

#ifndef SRC_HEADERS_GX_JSON_H_
#define SRC_HEADERS_GX_JSON_H_

namespace gx_engine {
class GxMachine;
class GxMachineRemote;
}

namespace gx_system {

/****************************************************************
 ** class JsonParser, class JsonWriter, class JsonException
 ** classes for reading and writing JSON files
 */

class JsonException: public exception {
 protected:
    Glib::ustring what_str;
 public:
    JsonException(const Glib::ustring& desc);
    ~JsonException() throw() { }
    virtual const char* what() const throw() { return what_str.c_str(); }
};

class JsonExceptionEOF: public JsonException {
 public:
    JsonExceptionEOF(const char* desc): JsonException(desc) {}
    ~JsonExceptionEOF() throw() { }
};

class JsonWriter {
 private:
    ostream *os;
    bool first;
    int deferred_nl;
    string indent;
    void snl(bool v) { if (deferred_nl >= 0) deferred_nl = (v ? 1 : 0); }
    void komma();
    void space();
    void iplus();
    void iminus();
 public:
    JsonWriter(ostream* o = 0, bool enable_newlines = true);
    virtual ~JsonWriter();
    void reset();
    void set_stream(ostream* o) { os = o; }
    bool good() { return os->good(); }
    void flush();
    virtual void close();
    bool is_closed() { return !os; }
    void write(float v, bool nl = false);
    void write(double v, bool nl = false);
    void write(int i, bool nl = false);
    void write(unsigned int i, bool nl = false);
    void write(const char* p, bool nl = false);
    void write(const string& s, bool nl = false) { write(s.c_str(), nl); }
    void write_kv(const char *key, float v) { write_key(key); write(v, true); }
    void write_kv(const char *key, double v) { write_key(key); write(v, true); }
    void write_kv(const char *key, int i) { write_key(key); write(i, true); }
    void write_kv(const char *key, unsigned int i) { write_key(key); write(i, true); }
    void write_kv(const char *key, const char* p) { write_key(key); write(p, true); }
    void write_kv(const char *key, const std::string& s) { write_key(key); write(s, true); }
    void write_lit(const string& s, bool nl = false);
    void begin_object(bool nl = false);
    void end_object(bool nl = false);
    void begin_array(bool nl = false);
    void end_array(bool nl = false);
    void write_key(const char* p, bool nl = false);
    void write_key(const string& p, bool nl = false);
    void write_null(bool nl = false) { write_lit("null", nl); }
    void newline() { snl(true); }
};


class JsonStringWriter: public JsonWriter {
private:
    ostringstream stream;
public:
    JsonStringWriter(): JsonWriter(0, false) { set_stream(&stream); }
    void send_notify_begin(const char *method);
    void send_notify_end();
    void reset() { stream.str(""); }
    void finish() { stream << endl; }
    std::string get_string() { return stream.str(); }
};


class JsonParser {
 public:
    JsonParser(istream* i = 0);
    virtual ~JsonParser();
    virtual void close();
    void reset();
    bool is_closed() { return !is; }
    void set_stream(istream* i) { is = i; }
    istream *get_stream() { return is; }
    enum token {
        no_token = 0x0000,
	end_token = 0x0001,
	begin_object = 0x002,
	end_object = 0x0004,
	begin_array = 0x0008,
	end_array = 0x0010,
	value_string = 0x0020,
	value_number = 0x0040,
	value_key = 0x0080,
	value_null = 0x0100,
	value_false = 0x0200,
	value_true = 0x0400,
	value_bool = 0x0600, // value_false | value_true
    };
    const char* get_token_name(token tok);
    bool good() { return is->good(); }
    token next(token expect = no_token);
    token peek() { return next_tok; }
    streampos get_streampos() { return next_pos + streamoff(-1); }
    void set_streampos(streampos pos);
    void check_expect(token expect) { if ((cur_tok & expect) == 0) throw_unexpected(expect); }
    inline string current_value() const { return str; }
    int current_value_int() { return atoi(str.c_str()); }
    unsigned int current_value_uint() { return atoi(str.c_str()); }
    float current_value_float() {
        istringstream b(str);
        float f;
        b >> f;
        return f;
    }
    double current_value_double() {
        istringstream b(str);
        double d;
        b >> d;
        return d;
    }
    bool read_kv(const char *key, float& v);
    bool read_kv(const char *key, double& v);
    bool read_kv(const char *key, int& i);
    bool read_kv(const char *key, unsigned int& i);
    bool read_kv(const char *key, std::string& s);
    bool read_kv(const char *key, Glib::ustring& s);
    template<class T> inline bool read_kv(const char *key, T& v) {
	int i;
	if (read_kv(key, i)) {
	    v = static_cast<T>(i);
	    return true;
	}
	return false;
    }
    void copy_object(JsonWriter& jw);
    void skip_object();
    void throw_unexpected(token expect);
 private:
    istream* is;
    int depth;
    token cur_tok;
    string str;
    bool nl;
    int next_depth;
    token next_tok;
    string next_str;
    string log_tok;
    streampos next_pos;
    const char* readcode();
    string readstring();
    token read_value_token(char c);
    string readnumber(char c);
    void read_next();
};


class JsonSubParser: public JsonParser {
private:
    std::streampos position;
public:
    JsonSubParser(JsonParser& jp, streampos pos);
    ~JsonSubParser();
};

class JsonStringParser: public JsonParser {
private:
    std::stringstream stream;
public:
    JsonStringParser() {}
    void put(char c) { stream.put(c); }
    std::ostream& get_ostream() { return stream; }
    void start_parser() { stream.seekg(0); set_stream(&stream); }
    std::string get_string() { return stream.str(); }
    void reset() { stream.str(""); JsonParser::reset(); }
    char peek_first_char() { stream >> ws; return stream.peek(); }
};


/****************************************************************
 ** Setting file handling
 ** class SettingsFileHeader, class StateFile, class PresetFile,
 ** class AbstractStateIO, class AbstractPresetIO
 ** class PresetBanks
 ** class GxSettingsBase
 */

class SettingsFileHeader {
    int file_major;
    int file_minor;
    string file_gx_version;
public:
    enum {
	major = 1,
	minor = 2
    };
    static const string gx_version; // = GX_VERSION
    SettingsFileHeader()
	: file_major(), file_minor(), file_gx_version() {}
    void read(JsonParser&);
    static void write(JsonWriter&);
    void set_to_current() { file_major = major; file_minor = minor; file_gx_version = gx_version; }
    int get_major() const { return file_major; }
    int get_minor() const { return file_minor; }
    string get_revision() const { return file_gx_version; }
    bool is_major_diff() const { return major != file_major; }
    bool is_minor_diff() const { return minor != file_minor; }
    bool is_current() const { return !is_major_diff() && !is_minor_diff(); }
    bool is_equal() const { return is_current() && gx_version == file_gx_version; }
    string display() const { ostringstream s; s << file_major << "." << file_minor << "." << file_gx_version; return s.str(); }
    Glib::ustring version_string() const { return Glib::ustring::compose("%1.%2", file_major, file_minor); }
    inline Glib::ustring current_version_string() const { return Glib::ustring::compose("%1.%2", int(major), int(minor)); }
    static bool make_empty_settingsfile(const string& name);
    static void write_current_major_minor(JsonWriter& jw);
    void write_major_minor(JsonWriter& jw);
    void read_major_minor(JsonParser& jp);
};

class StateFile {
private:
    string filename;
    istream *is;
    time_t mtime;
    SettingsFileHeader header;
    void open();
public:
    StateFile()
	: filename(), is(0), mtime(), header() {}
    ~StateFile() { delete is; }
    void set_filename(const string& fn);
    const SettingsFileHeader& get_header() const { return header; }
    string get_filename() const { return filename; }
    JsonParser *create_reader();
    JsonWriter *create_writer(bool *preserve_preset);
    void ensure_is_current();
};

class PresetTransformer: public JsonWriter {
private:
    string filename;
    string tmpfile;
    ofstream os;
protected:
    istream *is;
public:
    JsonParser jp;
    SettingsFileHeader header;
    void close();
    void close_nocheck();
    void abort();
    PresetTransformer(string filename, istream* is);
    ~PresetTransformer();
};

enum {
    PRESET_FLAG_VERSIONDIFF = 1,
    PRESET_FLAG_READONLY = 2,
    PRESET_FLAG_INVALID = 4,
};

class PresetFileGui;

class PresetFile : boost::noncopyable {
public:
    enum { PRESET_SEP = -1, PRESET_SCRATCH = 0, PRESET_FILE = 1, PRESET_FACTORY = 2 };
protected:
    class Position {
    public:
	Glib::ustring name;
	streampos pos;
	Position(Glib::ustring n, streampos p): name(n), pos(p) {}
    };
    std::string filename;
    ifstream *is;
    time_t mtime;
    SettingsFileHeader header;
    std::vector<Position> entries;
    Glib::ustring name;
    int tp;
    int flags;
    friend class gx_engine::GxMachineRemote;
protected:
    void open();
public:
    typedef std::vector<Position>::iterator iterator;
    PresetFile();
    ~PresetFile() { delete is; }
    void readJSON_remote(JsonParser& jp);
    void writeJSON_remote(JsonWriter& jw);
    bool open_file(const Glib::ustring& name, const std::string& path, int tp, int flags);
    bool create_file(const Glib::ustring& name, const std::string& path, int tp, int flags);
    bool set_factory(const Glib::ustring& name_, const std::string& path);
    bool readJSON(const std::string& dirpath, JsonParser &jp, bool *mtime_diff);
    void writeJSON(JsonWriter& jw);
    void reopen() { if (!is && !filename.empty()) open(); }
    void open(const std::string& fname);
    void close() { delete is; is = 0; }
    bool fail();
    bool ensure_is_current();
    void check_flags();
    const std::string& get_filename() const { return filename; }
    const SettingsFileHeader& get_header();
    int size();
    void fill_names(vector<Glib::ustring>&);
    const Glib::ustring& get_name(int n);
    int get_index(const Glib::ustring& name);
    JsonParser *create_reader(int n);
    JsonParser *create_reader(const Glib::ustring& name) {
	return create_reader(get_index(name)); }
    JsonWriter *create_writer(int n) {
	return create_writer(get_name(n)); }
    JsonWriter *create_writer(const Glib::ustring& name);
    JsonWriter *create_writer_at(const Glib::ustring& pos, const Glib::ustring& name);
    PresetTransformer *create_transformer();
    bool clear();
    bool erase(const Glib::ustring& name);
    bool rename(const Glib::ustring& name, Glib::ustring newname);
    bool has_entry(const Glib::ustring& name) { return get_index(name) >= 0; }
    void append(const Glib::ustring& name);
    void insert_before(const Glib::ustring& nm, const Glib::ustring& newentry);
    void insert_after(const Glib::ustring& nm, const Glib::ustring& newentry);
    int get_flags() const { return flags; }
    void set_flags(int f) { flags = f; }
    void set_flag(int flag, bool v) { flags = (flags & ~flag) | (v ? flag : 0); }
    int get_type() const { return tp; }
    const Glib::ustring& get_name() const { return name; }
    bool set_name(const Glib::ustring& n, const std::string& newfile);
    bool remove_file();
    iterator begin();
    iterator end() { return entries.end(); }
    bool is_moveable() const { return tp == PRESET_SCRATCH || tp == PRESET_FILE; }
    bool is_mutable() const { return is_moveable() && !flags; }
    PresetFileGui *get_guiwrapper();
};

class PresetFileGui: private PresetFile {
private:
    PresetFileGui();
    ~PresetFileGui();
    friend class PresetFile;
    friend class gx_engine::GxMachine;
    friend class gx_engine::GxMachineRemote;
public:
    using PresetFile::get_header;
    using PresetFile::size;
    using PresetFile::fill_names;
    using PresetFile::get_name;
    using PresetFile::get_index;
    using PresetFile::has_entry;
    using PresetFile::get_flags;
    using PresetFile::get_type;
    using PresetFile::begin;
    using PresetFile::end;
    using PresetFile::is_moveable;
    using PresetFile::is_mutable;
    operator PresetFile*() { return this; }
};

inline PresetFileGui *PresetFile::get_guiwrapper() { return static_cast<PresetFileGui*>(this); }

class AbstractStateIO {
public:
    virtual ~AbstractStateIO();
    virtual void read_state(JsonParser&,const SettingsFileHeader&) = 0;
    virtual void commit_state() = 0;
    virtual void write_state(JsonWriter&, bool) = 0;
};

class AbstractPresetIO {
public:
    virtual ~AbstractPresetIO();
    virtual void read_preset(JsonParser&,const SettingsFileHeader&) = 0;
    virtual void read_online(JsonParser&) = 0;
    virtual void commit_preset() = 0;
    virtual void write_preset(JsonWriter&) = 0;
    virtual void copy_preset(JsonParser&,const SettingsFileHeader&,JsonWriter&) = 0;
};

class PresetBanks {
private:
    typedef std::list<PresetFile*> bl_type;
    bl_type banklist;
    std::string filepath;
    time_t mtime;
    std::string preset_dir;
    void parse_factory_list(const std::string& path);
    void parse_bank_list(bl_type::iterator pos);
    void collect_lost_banks(const char* scratchpad_name, const char* scratchpad_file);
    friend class gx_engine::GxMachineRemote;
public:
    class iterator {
    private:
	bl_type::iterator it;
    public:
	iterator(bl_type::iterator i): it(i) {}
	bool operator!=(const iterator& i) const { return it != i.it; }
	iterator& operator++() { ++it; return *this; }
	PresetFile* operator->() { return *it; }
	PresetFile* operator*() { return *it; }
    };
    PresetBanks();
    ~PresetBanks();
    void readJSON_remote(gx_system::JsonParser& jp);
    bool check_reparse();
    void parse(const std::string& bank_path, const std::string& preset_dir,
	       const std::string& factory_path, const char* scratchpad_name, const char* scratchpad_file);
    PresetFile* get_file(const Glib::ustring& bank) const;
    int get_index(const Glib::ustring& bank) const;
    iterator begin() { return iterator(banklist.begin()); }
    iterator end() { return iterator(banklist.end()); }
    bool remove(const Glib::ustring& bank);
    void save();
    int size() { return banklist.size(); }
    Glib::ustring get_name(int n);
    void insert(PresetFile* f, int position = 0);
    bool has_entry(const Glib::ustring& bank) const { return get_file(bank) != 0; }
    bool has_file(const std::string& file) const;
    bool rename(const Glib::ustring& oldname, const Glib::ustring& newname, const std::string& newfile);
    void reorder(const std::vector<Glib::ustring>& neworder);
    static void make_valid_utf8(Glib::ustring& s);
    static std::string add_preset_postfix(const std::string& filename);
    static bool strip_preset_postfix(std::string& name);
    void make_bank_unique(Glib::ustring& name, std::string *file = 0);
};

class GxSettingsBase {
protected:
    AbstractStateIO*   state_io;
    AbstractPresetIO*  preset_io;
    StateFile          statefile;
    PresetBanks        banks;
    Glib::ustring      current_bank;
    Glib::ustring      current_name;
    gx_engine::EngineControl& seq;
    sigc::signal<void> selection_changed;
    sigc::signal<void> presetlist_changed;
    bool loadsetting(PresetFile *p, const Glib::ustring& name);
protected:
    void loadstate();
    void set_io(AbstractStateIO* st, AbstractPresetIO* pr) { state_io = st; preset_io = pr; }
public:
    inline sigc::signal<void>& signal_selection_changed() {
	return selection_changed; }
    inline sigc::signal<void>& signal_presetlist_changed() {
	return presetlist_changed; }
    GxSettingsBase(gx_engine::EngineControl& seq_);
    ~GxSettingsBase();
    const Glib::ustring& get_current_bank() { return current_bank; }
    PresetFile *get_current_bank_file() { return setting_is_preset() ? banks.get_file(current_bank) : 0; }
    const Glib::ustring& get_current_name() { return current_name; }
    void set_statefilename(const std::string& fn) { statefile.set_filename(fn); }
    void save_to_state(bool preserve_preset=false);
    void set_source_to_state();
    void erase_preset(const Glib::ustring& name);
    bool setting_is_preset() { return !current_bank.empty(); }
    bool convert_preset(PresetFile& pf);
    void reorder_preset(PresetFile& pf, const std::vector<Glib::ustring>& neworder);
    void erase_preset(PresetFile& pf, const Glib::ustring& name);
    void save(PresetFile& pf, const Glib::ustring& name);
    void append(PresetFile& pf, const Glib::ustring& src, PresetFile& pftgt, const Glib::ustring& name);
    void insert_before(PresetFile& pf, const Glib::ustring& src, PresetFile& pftgt, const Glib::ustring& pos, const Glib::ustring& name);
    void insert_after(PresetFile& pf, const Glib::ustring& src, PresetFile& pftgt, const Glib::ustring& pos, const Glib::ustring& name);
    void load_preset(PresetFile *pf, const Glib::ustring& name);
    void load_online_presets();
    bool rename_bank(const Glib::ustring& oldname, const Glib::ustring& newname, const std::string& newfile);
    bool remove_bank(const Glib::ustring& bank);
    bool rename_preset(PresetFile& pf, const Glib::ustring& oldname, const Glib::ustring& newname);
};

} /* end of gx_system namespace */
#endif  // SRC_HEADERS_GX_JSON_H_
