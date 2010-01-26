/*
 * Copyright (C) 2009 Hermann Meyer and James Warden
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
