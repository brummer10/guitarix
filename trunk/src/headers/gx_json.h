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
    string what_str;
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
    void write(string s, bool nl = false) { write(s.c_str(), nl); }
    void write_lit(string s, bool nl = false);
    void begin_object(bool nl = false);
    void end_object(bool nl = false);
    void begin_array(bool nl = false);
    void end_array(bool nl = false);
    void write_key(const char* p, bool nl = false);
    void write_key(string p, bool nl = false);
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
    void set_streampos(streampos pos) { is->seekg(pos); }
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
    void read(gx_system::JsonParser&);
    static void write(gx_system::JsonWriter&);
    int get_major() const { return file_major; }
    int get_minor() const { return file_minor; }
    string get_revision() const { return file_gx_version; }
    bool is_major_diff() const { return major != file_major; }
    bool is_minor_diff() const { return minor != file_minor; }
    bool is_current() const { return !is_major_diff() && !is_minor_diff(); }
    bool is_equal() const { return is_current() && gx_version == file_gx_version; }
    string display() const { ostringstream s; s << file_major << "." << file_minor << "." << file_gx_version; return s.str(); }
    static bool make_empty_settingsfile(const string& name);
};

class StateFile {
private:
    string filename;
    istream *is;
    SettingsFileHeader header;
    void open();
public:
    StateFile()
	: filename(), is(0), header() {}
    ~StateFile() { delete is; }
    void set_filename(const string& fn) { filename = fn; }
    const SettingsFileHeader& get_header() const { return header; }
    string get_filename() const { return filename; }
    gx_system::JsonParser *create_reader();
    gx_system::JsonWriter *create_writer(bool *preserve_preset);
};

class PresetTransformer: public gx_system::JsonWriter {
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
    PresetTransformer(string filename, istream* is);
    ~PresetTransformer();
};

class PresetFile : boost::noncopyable {
private:
    class Position {
    public:
	string name;
	streampos pos;
	Position(string n, streampos p): name(n), pos(p) {}
    };
    string filename;
    ifstream *is;
    SettingsFileHeader header;
    vector<Position> entries;
    void open();
public:
    PresetFile();
    ~PresetFile() { delete is; }
    void reopen() { if (!is) open(); }
    void open(const string& fname);
    bool fail() { reopen(); return is->fail(); }
    const string& get_filename() { return filename; }
    const SettingsFileHeader& get_header();
    int size() const { return entries.size(); }
    void fill_names(vector<string>&);
    string get_name(int n);
    int get_index(const string& name);
    gx_system::JsonParser *create_reader(int n);
    gx_system::JsonParser *create_reader(const string& name) {
	return create_reader(get_index(name)); }
    gx_system::JsonWriter *create_writer(int n) {
	return create_writer(get_name(n)); }
    gx_system::JsonWriter *create_writer(const string& name);
    PresetTransformer *create_transformer();
    bool clear();
    bool erase(const string& name);
    bool rename(const string& name, string newname);
};

class AbstractStateIO {
public:
    virtual ~AbstractStateIO();
    virtual void read_state(gx_system::JsonParser&,const SettingsFileHeader&) = 0;
    virtual void commit_state() = 0;
    virtual void write_state(gx_system::JsonWriter&, bool) = 0;
};

class AbstractPresetIO {
public:
    virtual ~AbstractPresetIO();
    virtual void read_preset(gx_system::JsonParser&,const SettingsFileHeader&) = 0;
    virtual void commit_preset() = 0;
    virtual void write_preset(gx_system::JsonWriter&) = 0;
    virtual void copy_preset(gx_system::JsonParser&,const SettingsFileHeader&,gx_system::JsonWriter&) = 0;
};

class GxSettingsBase {
public:
    enum Source {
	state,
	preset,
	factory,
    };
protected:
    class Factory {
    public:
	string     name;
	PresetFile setting;
	Factory(string n): name(n), setting() {}
    };
    AbstractStateIO*   state_io;
    AbstractPresetIO*  preset_io;
    StateFile          statefile;
    PresetFile         presetfile;
    vector<Factory*>   factory_presets;
    Source             current_source;
    string             current_factory;
    string             current_name;
    gx_engine::ModuleSequencer& seq;
    sigc::signal<void> selection_changed;
    void clear_factory();
    PresetFile* get_factory(const string& name) const;
    void loadsetting(PresetFile *p, const string& name);
protected:
    void load(Source src, const string& name, const string& factory);
    void set_io(AbstractStateIO* st, AbstractPresetIO* pr) { state_io = st; preset_io = pr; }
    void convert_presetfile();
    void change_preset_file(const string& newfile);
public:
    inline sigc::signal<void>& signal_selection_changed() {
	return selection_changed; }
    GxSettingsBase(gx_engine::ModuleSequencer& seq_);
    ~GxSettingsBase();
    Source get_current_source() { return current_source; }
    const string& get_current_factory() { return current_factory; }
    const string& get_current_name() { return current_name; }
    const string& get_factory(unsigned int idx) { //FIXME fix usage and remove
	return factory_presets.at(idx)->name; }
    void set_statefilename(const string& fn) { statefile.set_filename(fn); }
    void save_to_state(bool preserve_preset=false);
    void save_to_current_preset() {
	if (current_source == preset) save_to_preset(current_name); }
    void save_to_preset(const string& name);
    int get_preset_index(const string& name) {	return presetfile.get_index(name); }
    bool rename_preset(const string& name, const string& newname);
    void erase_current_preset() {
	if (current_source == preset) erase_preset(current_name); }
    void erase_preset(const string& name);
    bool presetfile_fail() { return presetfile.fail(); }
    bool clear_preset() { return presetfile.clear(); }
    void fill_preset_names(vector<string>& l) {  presetfile.fill_names(l); }
    void fill_factory_names(vector<string>& l) const;
    void fill_factory_preset_names(const string& fact, vector<string>& l) const;
    bool setting_is_preset() { return current_source == preset; }
    bool idx_in_preset(int idx) { return idx >= 0 && idx < presetfile.size(); }
    void load_preset_by_idx(int idx) { load(preset, presetfile.get_name(idx), ""); }
};

} /* end of gx_system namespace */
#endif  // SRC_HEADERS_GX_JSON_H_
