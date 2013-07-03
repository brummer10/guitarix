/*
 * Copyright (C) 2009, 2010, 2013 Hermann Meyer, James Warden, Andreas Degert
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

#pragma once

#ifndef SRC_HEADERS_GX_LOGGING_H_
#define SRC_HEADERS_GX_LOGGING_H_

#include <glib/gi18n.h>
#include <glibmm/dispatcher.h>
#include <boost/thread/mutex.hpp>
#include <boost/format.hpp>

/****************************************************************
 ** Logging
 */

class GxLogger: public sigc::trackable {
public:
    typedef enum {
	kInfo,
	kWarning,
	kError,
	kMessageTypeCount // just count, must be last
    } MsgType;
private:
    typedef sigc::signal<void, const std::string&, MsgType, bool> msg_signal;
    struct logmsg {
	std::string msg;
	MsgType msgtype;
	bool plugged;
	logmsg(std::string m, MsgType t, bool p): msg(m), msgtype(t), plugged(p) {}
    };
    std::list<logmsg> msglist;
    boost::mutex msgmutex;
    Glib::Dispatcher* got_new_msg;
    pthread_t ui_thread;
    msg_signal handlers;
    bool queue_all_msgs;
    std::string format(const char* func, const std::string& msg);
    void set_ui_thread();
    GxLogger();
    ~GxLogger();
    void write_queued();
    friend class GxLoggerGuard;
public:
    void unplug_queue();
    msg_signal& signal_message();
    void print(const char* func, const std::string& msg, MsgType msgtype);
    void print(const std::string& formatted_msg, MsgType msgtype);
    static GxLogger& get_logger();
    static void destroy();
};

void  gx_print_logmsg(const char*, const std::string&, GxLogger::MsgType);
void  gx_print_warning(const char*, const std::string&);
inline void gx_print_warning(const char* fnc, const boost::basic_format<char>& msg) {
    gx_print_warning(fnc, msg.str());
}
void  gx_print_error(const char*, const std::string&);
inline void gx_print_error(const char* fnc, const boost::basic_format<char>& msg) {
    gx_print_error(fnc, msg.str());
}
void  gx_print_fatal(const char*, const std::string&);
inline void gx_print_fatal(const char* fnc, const boost::basic_format<char>& msg) {
    gx_print_fatal(fnc, msg.str());
}
void  gx_print_info(const char*, const std::string&);
inline void gx_print_info(const char* fnc, const boost::basic_format<char>& msg) {
    gx_print_info(fnc, msg.str());
}

class GxFatalError: public std::exception {
private:
    std::string msg;
public:
    virtual const char* what() const throw() {
	return msg.c_str();
    }
    GxFatalError(std::string m): msg(m) {}
    GxFatalError(boost::basic_format<char>& m): msg(m.str()) {}
    ~GxFatalError() throw();
};


/****************************************************************
 ** class GxExit
 */

class GxExit {
private:
    sigc::signal<void, bool> exit_sig;
    pthread_t ui_thread;
    sigc::signal<void,std::string> message;
public:
    GxExit();
    ~GxExit();
    void set_ui_thread() { ui_thread = pthread_self(); }
    sigc::signal<void, bool>& signal_exit() { return exit_sig; }
    sigc::signal<void,std::string>& signal_msg() { return message; }
    void exit_program(std::string msg = "", int errcode = 1);
    void fatal_msg(const std::string& msg) { message(msg); exit_program(msg); }
    static GxExit& get_instance();
};

#endif  // SRC_HEADERS_GX_LOGGING_H_
