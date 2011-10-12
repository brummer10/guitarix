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

#include <semaphore.h>

#include <cmath>
#include <sstream>
#include <list>
#include <string>
#include <algorithm>

namespace gx_jack { class GxJack; } // FIXME

namespace gx_system {


/* classes for reading and writing JSON files */
class JsonException: public exception {
 private:
    string what_str;
 public:
    explicit JsonException(const char* desc);
    ~JsonException() throw() { }
    virtual const char* what() const throw() { return what_str.c_str(); }
};

class JsonWriter {
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
    explicit JsonWriter(ostream& o);
    ~JsonWriter() { close(); }
    bool good() { return os.good(); }
    void flush();
    void close() { if (deferred_nl) os << endl; }
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
    explicit JsonParser(istream& i);
    enum token {
        no_token, end_token, begin_object, end_object, begin_array, end_array,
        value_string, value_number, value_key };
    static const char* token_names[];
    bool good() { return is.good(); }
    token next(token expect = no_token);
    token peek() { return next_tok; }
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

class PresetReader {
private:
    gx_gui::paramlist plist;
    gx_gui::MidiControllerList::controller_array *m;
    void clear();
public:
    PresetReader(): m(0) {}
    PresetReader(JsonParser &jp, bool *has_midi, int major, int minor): m(0) {
	read(jp, has_midi, major, minor);
	commit();
    }
    void read(JsonParser &jp, bool *has_midi, int major, int minor);
    void commit();
};

void writeHeader(JsonWriter& jw);
bool readHeader(JsonParser& jp, int *major = 0, int *minor = 0);
void write_preset(JsonWriter& w, bool write_midi = true, bool force_midi = false);
bool saveStateToFile(const string & filename, gx_jack::GxJack& jack);
bool recallState(const string & filename);

// file format versions
const int majorversion = 1;
const int minorversion = 2;
} /* end of gx_system namespace */
#endif  // SRC_HEADERS_GX_JSON_H_
