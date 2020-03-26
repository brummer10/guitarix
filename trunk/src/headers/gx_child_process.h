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

/* ------- This is the Child Processes namespace ------- */

#pragma once

#ifndef SRC_HEADERS_GX_CHILD_PROCESS_H_
#define SRC_HEADERS_GX_CHILD_PROCESS_H_

#include <sigc++/sigc++.h>

#include <string>
#include <list>

namespace gx_child_process {

class GxChild {
 public:
    sigc::signal<void, bool> terminated;
    bool kill();
    bool hasPid(pid_t pid) { return pid == m_pid; }
    bool hasName(string name) { return name == m_name; }

 private:
    string m_name;
    int m_killsignal;
    int m_pid;
    GxChild(string name, int killsignal, int pid):
            m_name(name), m_killsignal(killsignal), m_pid(pid) {}
    friend class GxChildProcs;
};

class GxChildProcs {
 private:
    list<GxChild*> children;

 public:
    ~GxChildProcs();
    bool killall();
    bool kill(string name);
    GxChild *find(string name);
    GxChild *launch(string name, const char* const args[], int killsignal);
    GxChild *launch(string name, list<string> args, int killsignal);
    friend void gx_sigchld_handler();
};

extern GxChildProcs childprocs;
void gx_sigchld_handler();


/****************************************************************
 ** classes for UI callbacks
 */

#if false  // unused
class JackCaptureGui: public sigc::trackable {
 private:
    GtkCheckMenuItem *item;
    void terminated(bool pgm_found);
    JackCaptureGui(GxChild *p, GtkCheckMenuItem *i);
 public:
    static void start_stop(GtkCheckMenuItem *menuitem, gpointer);
};

class JackCapture: public sigc::trackable {
 private:
    GtkToggleButton *button;
    void terminated(bool pgm_found);
    static string make_fname(string buf, size_t j, size_t i, int n);
    static list<string> capture_command(int& seq);
    JackCapture(GxChild *p, GtkToggleButton *b);
 public:
    static void start_stop(GtkWidget *widget, gpointer data);
    static void stop();
};
#endif

class Meterbridge: public sigc::trackable {
 private:
    Glib::RefPtr<ToggleAction> action;
    void terminated(bool pgm_found);
    Meterbridge(GxChild *p, Glib::RefPtr<ToggleAction>& a);
 public:
    static void start_stop(Glib::RefPtr<ToggleAction>& action, gx_jack::GxJack& jack);
    static void stop();
};

/* -------------------------------------------------------------------------- */
} /* end of gx_child_process namespace */
#endif  // SRC_HEADERS_GX_CHILD_PROCESS_H_
