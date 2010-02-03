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
      void snl(bool v) { deferred_nl = v; }
      void komma();
      void space();
    public:
      JsonWriter(ostream& o);
      ~JsonWriter() { flush(); }
      bool good() { return os.good(); }
      void flush() { if (deferred_nl) { newline(); deferred_nl = false; } }
      void write(float v, bool nl=false) { komma(); os << v; snl(nl); }
      void write(double v, bool nl=false) { komma(); os << v; snl(nl); }
      void write(int i, bool nl=false) { komma(); os << i; snl(nl); }
      void write(unsigned int i, bool nl=false) { komma(); os << i; snl(nl); }
      void write(const char* p, bool nl=false);
      void begin_object(bool nl=false) { space(); os << '{'; snl(nl); first = true; }
      void end_object(bool nl=false) { space(); os << '}'; snl(nl); }
      void begin_array(bool nl=false) { space(); os << '['; snl(nl); first = true; }
      void end_array(bool nl=false) { space(); os << ']'; snl(nl); }
      void write_key(const char* p, bool nl=false) { write(p, nl); os << ": "; first = true; }
      void newline() { os << '\n'; deferred_nl = false; }
    };

    class JsonParser
    {
    public:
      JsonParser(istream& i);
      enum token {
	no_token, end_token, begin_object, end_object, begin_array, end_array,
	value_string, value_number, value_key };
      bool good() { return is.good(); }
      token next(token expect=no_token);
      token peek() { return next_tok; }
      void check_expect(token expect) { if (cur_tok != expect) throw JsonException("unexpected token"); }
      string current_value() { return str; }
      int current_value_int() { return atoi(str.c_str()); }
      float current_value_float() { return strtof(str.c_str(), NULL); }
      double current_value_double() { return strtod(str.c_str(), NULL); }
    private:
      istream& is;
      int depth;
      token cur_tok;
      string str;
      token next_tok;
      string next_str;
      const char* readcode();
      string readstring();
      string readnumber(char c);
      void read_next();
    };

    inline void JsonWriter::komma()
    {
      if (first)
	first = false;
      else
	os << ", ";
      flush();
    }

    inline void JsonWriter::space()
    {
      if (first)
	first = false;
      else
	os << " ";
      flush();
    }

  /* function declaration */
  void  gx_print_logmsg (const char*, const string&, GxMsgType);
  void  gx_print_warning(const char*, const string&);
  void  gx_print_error  (const char*, const string&);
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
