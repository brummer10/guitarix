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
 */

#include "gx_logging.h"
#include <iostream>
#include <iomanip>

/****************************************************************
 ** Logging
 */

GxLogger::GxLogger()
    : trackable(),
      msglist(),
      msgmutex(),
      got_new_msg(),
      ui_thread(),
      handlers(),
      queue_all_msgs(true) {
}

static class GxLoggerGuard {
private:
    GxLogger *logger_instance;
public:
    GxLoggerGuard() : logger_instance(0) {}
    ~GxLoggerGuard() { destroy(); }
    void create() { logger_instance = new GxLogger; }
    void destroy() { if (logger_instance) { delete logger_instance; logger_instance = 0; }}
    GxLogger *get() { return logger_instance; }
} logger_guard;

GxLogger& GxLogger::get_logger() {
    GxLogger *l = logger_guard.get();
    if (!l) {
	logger_guard.create();
	l = logger_guard.get();
    }
    return *l;
}

void GxLogger::destroy() {
    logger_guard.destroy();
}

GxLogger::~GxLogger() {
    delete got_new_msg;
}

void GxLogger::set_ui_thread() {
    if (ui_thread) {
	assert(pthread_equal(pthread_self(), ui_thread));
    } else {
	got_new_msg = new Glib::Dispatcher;
	ui_thread = pthread_self();
	got_new_msg->connect(mem_fun(*this, &GxLogger::write_queued));
    }
}

GxLogger::msg_signal& GxLogger::signal_message() {
    set_ui_thread();
    return handlers;
}

void GxLogger::unplug_queue() {
    if (!queue_all_msgs) {
	return;
    }
    queue_all_msgs = false;
    write_queued();
}

void GxLogger::write_queued() {
    if (handlers.empty()) {
	return;
    }

    // quick copy list
    msgmutex.lock();
    std::list<logmsg> l = msglist;
    if (!queue_all_msgs) {
	msglist.clear();
    }
    msgmutex.unlock();

    // feed throught the handler(s)
    for (std::list<logmsg>::iterator i = l.begin(); i != l.end(); ++i) {
	if (queue_all_msgs) {
	    if (!i->plugged) {
		handlers(i->msg, i->msgtype, i->plugged);
		i->plugged = true;
	    }
	} else {
	    handlers(i->msg, i->msgtype, i->plugged);
	}
    }
}

std::string GxLogger::format(const char* func, const std::string& msg) {
    // timestamp
    time_t now;
    time(&now);
    struct tm *tm_now = localtime(&now);
    std::ostringstream msgbuf;
    msgbuf << "[" << std::setfill('0')
           << std::setw(2) << tm_now->tm_hour << ":"
           << std::setw(2) << tm_now->tm_min  << ":"
           << std::setw(2) << tm_now->tm_sec  << "]"
           << "  " << func << "  ***  " << msg;
    return msgbuf.str();
}

void GxLogger::print(const char* func, const std::string& msg, GxLogger::MsgType msgtype) {
    GxLogger::print(format(func, msg), msgtype);
}

void GxLogger::print(const std::string& formatted_msg, GxLogger::MsgType msgtype) {
    if (handlers.empty() || !(pthread_equal(pthread_self(), ui_thread))) {
	boost::mutex::scoped_lock lock(msgmutex);
	// defer output
        msglist.push_back(logmsg(formatted_msg, msgtype, false));
	if (!handlers.empty() && msglist.size() == 1) {
	    (*got_new_msg)();
	}
    } else {
	write_queued();
	handlers(formatted_msg, msgtype, false);
	if (queue_all_msgs) {
	    msglist.push_back(logmsg(formatted_msg, msgtype, true));
	}
    }
}

/*
** utility logger functions
*/

// ---- log message handler
void gx_print_logmsg(const char* func, const std::string& msg, GxLogger::MsgType msgtype) {
    GxLogger::get_logger().print(func, msg, msgtype);
}

// warning
void gx_print_warning(const char* func, const std::string& msg) {
    gx_print_logmsg(func, msg, GxLogger::kWarning);
}

// error
void gx_print_error(const char* func, const std::string& msg) {
    gx_print_logmsg(func, msg, GxLogger::kError);
}

GxFatalError::~GxFatalError() throw() {
}

// fatal error
// - do not use before Gtk::Main() ctor
// - do not use when main loop is blocked (modal dialog or something)
//
void gx_print_fatal(const char* func, const std::string& msg) {
    std::string msgbuf = std::string(_("fatal system error: ")) + func + "  ***  " + msg + "\n";
    GxExit::get_instance().fatal_msg(msgbuf);
}

// info
void gx_print_info(const char* func, const std::string& msg) {
    gx_print_logmsg(func, msg, GxLogger::kInfo);
}


/****************************************************************
 ** class GxExit
 */

GxExit::GxExit(): exit_sig(), ui_thread() {}

GxExit::~GxExit() {}

void GxExit::exit_program(std::string msg, int errcode) {
    exit_sig.emit_reverse(!pthread_equal(pthread_self(), ui_thread));
    if (msg.empty()) {
	msg = "** guitarix exit **";
    }
    std::cerr << msg << std::endl;
    _exit(errcode);
}

GxExit& GxExit::get_instance() {
    static GxExit instance;
    return instance;
}
