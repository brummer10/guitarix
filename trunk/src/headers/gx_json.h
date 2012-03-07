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

namespace gx_system {

/****************************************************************
 ** class JsonParser, class JsonWriter, class JsonException
 ** classes for reading and writing JSON files
 */

class JsonException: public exception {
 private:
    Glib::ustring what_str;
 public:
    JsonException(const char* desc);
    ~JsonException() throw() { }
    virtual const char* what() const throw() { return what_str.c_str(); }
};

class JsonWriter {
 private:
    ostream *os;
    bool first;
    bool deferred_nl;
    string indent;
    void snl(bool v) { deferred_nl = v; }
    void komma();
    void space();
    void iplus();
    void iminus();
 public:
    JsonWriter(ostream* o = 0);
    virtual ~JsonWriter();
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
    void write_lit(const string& s, bool nl = false);
    void begin_object(bool nl = false);
    void end_object(bool nl = false);
    void begin_array(bool nl = false);
    void end_array(bool nl = false);
    void write_key(const char* p, bool nl = false);
    void write_key(const string& p, bool nl = false);
    void newline() { snl(true); }
};

class JsonParser {
 public:
    JsonParser(istream* i = 0);
    virtual ~JsonParser();
    virtual void close();
    bool is_closed() { return !is; }
    void set_stream(istream* i) { is = i; }
    enum token {
        no_token, end_token, begin_object, end_object, begin_array, end_array,
        value_string, value_number, value_key };
    static const char* token_names[];
    bool good() { return is->good(); }
    token next(token expect = no_token);
    token peek() { return next_tok; }
    streampos get_streampos() { return next_pos + streamoff(-1); }
    void set_streampos(streampos pos);
    void check_expect(token expect) { if (cur_tok != expect) throw_unexpected(expect); }
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
    void copy_object(JsonWriter& jw);
    void skip_object();
 private:
    istream* is;
    int depth;
    token cur_tok;
    string str;
    bool nl;
    int next_depth;
    token next_tok;
    string next_str;
    streampos next_pos;
    const char* readcode();
    string readstring();
    string readnumber(char c);
    void read_next();
    void throw_unexpected(token expect);
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
    void set_filename(const string& fn) { filename = fn; }
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
protected:
    void open();
public:
    typedef std::vector<Position>::iterator iterator;
    PresetFile();
    ~PresetFile() { delete is; }
    bool open_file(const Glib::ustring& name, const std::string& path, int tp, int flags);
    bool create_file(const Glib::ustring& name, const std::string& path, int tp, int flags);
    bool set_factory(const Glib::ustring& name_, const std::string& path);
    bool readJSON(const std::string& dirpath, JsonParser &jp, bool *mtime_diff);
    void writeJSON(JsonWriter& jw);
    void reopen() { if (!is) open(); }
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
    bool is_mutable() { return (tp == PRESET_SCRATCH || tp == PRESET_FILE) && !flags; }
};

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
    void collect_lost_banks();
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
    bool check_reparse();
    void parse(const std::string& bank_path, const std::string& preset_dir,
	       const std::string& factory_path);
    PresetFile* get_file(const Glib::ustring& bank) const;
    int get_index(const Glib::ustring& bank) const;
    iterator begin() { return iterator(banklist.begin()); }
    iterator end() { return iterator(banklist.end()); }
    bool remove(const Glib::ustring& bank);
    void save();
    int size() { return banklist.size(); }
    Glib::ustring get_name(int n);
    void insert(PresetFile* f) { banklist.push_front(f); save(); }
    bool has_entry(const Glib::ustring& bank) const { return get_file(bank) != 0; }
    bool has_file(const std::string& file) const;
    bool rename(const Glib::ustring& oldname, const Glib::ustring& newname, const std::string& newfile);
    void reorder(const std::vector<Glib::ustring>& neworder);
    static std::string encode_filename(const std::string& s);
    static std::string decode_filename(const std::string& s);
    static void make_valid_utf8(Glib::ustring& s);
    static std::string add_preset_postfix(const std::string& filename);
    static bool strip_preset_postfix(std::string& name);
    void make_bank_unique(Glib::ustring& name, std::string *file = 0);
};

class GxSettingsBase {
public:
    enum Source {
	state,
	preset,
    };
protected:
    AbstractStateIO*   state_io;
    AbstractPresetIO*  preset_io;
    StateFile          statefile;
    PresetBanks        banks;
    Source             current_source;
    Glib::ustring      current_bank;
    Glib::ustring      current_name;
    gx_engine::EngineControl& seq;
    sigc::signal<void> selection_changed;
    sigc::signal<void> presetlist_changed;
    bool               in_load;
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
    Source get_current_source() { return current_source; }
    const Glib::ustring& get_current_bank() { return current_bank; }
    PresetFile *get_current_bank_file() { return setting_is_preset() ? banks.get_file(current_bank) : 0; }
    const Glib::ustring& get_current_name() { return current_name; }
    void set_statefilename(const std::string& fn) { statefile.set_filename(fn); }
    void save_to_state(bool preserve_preset=false);
    void set_source_to_state();
    void erase_preset(const Glib::ustring& name);
    bool setting_is_preset() { return current_source == preset; }
    bool convert_preset(PresetFile& pf);
    void reorder_preset(PresetFile& pf, const std::vector<Glib::ustring>& neworder);
    void erase_preset(PresetFile& pf, const Glib::ustring& name);
    void save(PresetFile& pf, const Glib::ustring& name);
    void append(PresetFile& pf, const Glib::ustring& src, PresetFile& pftgt, const Glib::ustring& name);
    void insert_before(PresetFile& pf, const Glib::ustring& src, PresetFile& pftgt, const Glib::ustring& pos, const Glib::ustring& name);
    void insert_after(PresetFile& pf, const Glib::ustring& src, PresetFile& pftgt, const Glib::ustring& pos, const Glib::ustring& name);
    void load_preset(PresetFile *pf, const Glib::ustring& name);
    bool is_loading() { return in_load; }
    bool rename_bank(const Glib::ustring& oldname, const Glib::ustring& newname, const std::string& newfile);
    bool rename_preset(PresetFile& pf, const Glib::ustring& oldname, const Glib::ustring& newname);
};

} /* end of gx_system namespace */
#endif  // SRC_HEADERS_GX_JSON_H_
