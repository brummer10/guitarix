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
 *
 *  This is the guitarix module handling child processes spawned from it
 *
 * --------------------------------------------------------------------------
 */

#include "guitarix.h"

#include <sys/wait.h>

#include <fstream>
#include <string>
#include <list>

namespace gx_child_process {

/****************************************************************
 ** GxChild, GxChildProcs
 */

bool GxChild::kill() {
    return ::kill(m_pid, m_killsignal) != -1;
}

GxChildProcs::~GxChildProcs() {
    for (list<GxChild*>::iterator i = children.begin(); i != children.end(); ++i) {
        (*i)->kill();
        delete *i;
    }
}

bool GxChildProcs::killall() {
    int ret = true;
    for (list<GxChild*>::iterator i = children.begin(); i != children.end(); ++i) {
        if (!(*i)->kill()) {
            ret = false;
        }
    }
    return ret;
}

bool GxChildProcs::kill(string name) {
    GxChild *p = find(name);
    if (p) {
        return p->kill();
    }
    return true;
}

GxChild *GxChildProcs::find(string name) {
    for (list<GxChild*>::iterator i = children.begin(); i != children.end(); ++i) {
        if ((*i)->hasName(name)) {
            return *i;
        }
    }
    return 0;
}

#define EXIT_PGM_NOT_FOUND 127

void gx_sigchld_handler() {
    int status;
    pid_t pid = waitpid(-1, &status, WNOHANG);
    if (pid == 0 || pid == -1) {
        return;
    }
    bool pgm_found = true;
    if (WIFEXITED(status)) {
        if (WEXITSTATUS(status) == EXIT_PGM_NOT_FOUND) {
            pgm_found = false;
        }
    } else if (!WIFSIGNALED(status)) {
        // process didn't terminate
        return;
    }
    // child pid has terminated
    list<GxChild*>& cl = childprocs.children;
    GxChild *p = 0;
    for (list<GxChild*>::iterator i = cl.begin(); i != cl.end(); ++i) {
        if ((*i)->hasPid(pid)) {
            p = *i;
            cl.erase(i);
            break;
        }
    }
    if (p) {
        p->terminated(pgm_found);
    }
}

GxChild *GxChildProcs::launch(string name, const char *const args[], int killsignal) {
    // fork produces about 3ms latency on linux 2.6.31-9-rt
    // vfork works
    // FIXME check if its a version-specific bug
    int pid = vfork();
    switch (pid) {
    case -1: // error, in parent
        return 0;

    case 0: // in child
        execvp(args[0], (char**)args);
        _exit(EXIT_PGM_NOT_FOUND);
        /*NOTREACHED*/
        return 0;

    default: // in parent
        GxChild *p = new GxChild(name, killsignal, pid);
        children.push_back(p);
        return p;
    }
}

GxChild *GxChildProcs::launch(string name, list<string> args, int killsignal) {
    const char **p = new const char*[args.size()+1];
    unsigned int i = 0;
    for (list<string>::iterator j = args.begin(); j != args.end(); ++j) {
        // cout << *j << endl;
        p[++i] = j->c_str();
    }
    assert(i == args.size());
    p[i] = 0;
    GxChild *c = launch(name, p, killsignal);
    delete p;
    return c;
}

GxChildProcs childprocs;

/****************************************************************
 ** Menu Callbacks
 */

//----------------------- jack_capture settings ---------------------------
JackCaptureGui::JackCaptureGui(GxChild *p, GtkCheckMenuItem *i)
                               : item(i) {
    gtk_widget_ref(GTK_WIDGET(item));
    p->terminated.connect(sigc::mem_fun(*this, &JackCaptureGui::terminated));
}

void JackCaptureGui::terminated(bool pgm_found) {
    gtk_check_menu_item_set_active(item, false);
    if (pgm_found) {
        gx_system::gx_print_info("Jack capture gui", "jack_capture_gui2 terminated");
    } else {
        gx_gui::gx_message_popup(
            "  "
            " ERORR [Jack Capture GUI]\n\n "
            " jack_capture_gui2 is not installed! "
            );
    }
    gtk_widget_unref(GTK_WIDGET(item));
    delete this;
}

void JackCaptureGui::start_stop(GtkCheckMenuItem *menuitem, gpointer) {
    const char *app_name = "jack_capture_gui2";
    if (gtk_check_menu_item_get_active(menuitem)) {
        if (childprocs.find(app_name)) {
            return;
        }
        string sess = string(getenv("HOME")) + "/guitarix_session";
        const char * const args[] = {
            app_name, "-o", "yes", "-f", sess.c_str(),
            "-n", "guitarix", "-p", "/.guitarix/ja_ca_ssetrc", 0 };
        GxChild *jack_cap_gui = childprocs.launch(app_name, args, SIGTERM);
        if (jack_cap_gui) {
            new JackCaptureGui(jack_cap_gui, menuitem);
        } else {
            gx_gui::gx_message_popup(
                "  "
                "ERROR [Jack capture gui]\n\n  "
                "jack_capture_gui2 could not be launched!"
                );
            gx_system::gx_print_error("Jack capture gui",
                           string("jack_capture_gui2 could not be launched (fork failed)!"));
            gtk_check_menu_item_set_active(menuitem, FALSE);
        }
    } else {
        childprocs.kill(app_name);
    }
}

//---------------------------- Jack Capture -------------------------------

#if 0 // unused
JackCapture::JackCapture(GxChild *p, GtkToggleButton *b)
    : button(b) {
    gtk_widget_ref(GTK_WIDGET(button));
    p->terminated.connect(sigc::mem_fun(*this, &JackCapture::terminated));
}

void JackCapture::terminated(bool pgm_found) {
    gtk_toggle_button_set_active(button, false);
    if (pgm_found) {
        gx_system::gx_print_info("Jack Capture", "jack_capture terminated");
    } else {
        gx_system::gx_print_warning("Record",
                         "  WARNING [jack_capture]\n  "
                         "  You need jack_capture >= 0.9.30 by Kjetil S. Matheussen  \n  "
                         "  Please look here\n  "
                         "  http://old.notam02.no/arkiv/src/?M=D\n");
    }
    gtk_widget_unref(GTK_WIDGET(button));
    delete this;
}

// ---- wav file construction for jack_capture
string JackCapture::make_fname(string buf, size_t j, size_t i, int n) {
    ostringstream str;
    str << buf.substr(0, j+1) << n << buf.substr(i);
    return str.str();
}

list<string> JackCapture::capture_command(int& seq) {
    // open jack_capture setup file
    string gfilename = gx_system::sysvar.gx_user_dir + gx_system::sysvar.jcapsetup_file;
    ifstream f(gfilename.c_str());

    list<string> l;
    string buf;
    while (true) {
        f >> buf;
        if (!f.good()) {
            break;
        }
        l.push_back(buf);
    }
    f.close();
    if (l.empty()) {
        (void)gx_gui::gx_message_popup(
            "  ERROR [Record]\n\n  "
            "  Please run jack capture settings first [alt+j]"
            );
        return l;
    }
    buf = *l.rbegin(); // last argument should be filename
    l.pop_back(); // pop last argument (re-add later after processing)
    l.push_back("--hide-buffer-usage"); // add additional option
    size_t i = buf.find_last_of(".");
    if (i == string::npos) {
        gx_system::gx_print_error("Record", "could not parse cmd file (internal error)");
        l.clear();
        return l;
    }
    size_t j = buf.find_last_not_of("0123456789", i-1);
    int n;
    string fname;
    for (n = 1; n < 1000; ++n) {
        fname = make_fname(buf, j, i, n);
        if (access(fname.c_str(), F_OK) != 0) {
            break;
        }
    }
    if (n == 1000) {
        gx_system::gx_print_error("Record", "more than 999 capture files in directory?!");
        l.clear();
        return l;
    }
    seq = n;
    l.push_back(fname); // add filename
    return l;
}

void JackCapture::stop() {
    childprocs.kill("jack_capture");
}

void JackCapture::start_stop(GtkWidget *widget, gpointer data) {
    static int last_seqno;
    // here, const applies to pointer, not pointed data ;)
    GtkToggleButton* const cap_button = reinterpret_cast<GtkToggleButton*>(widget);
    const char *app_name = "jack_capture";
    if (gtk_toggle_button_get_active(cap_button) == FALSE) {
        // ---- stop recording
        GxChild *jack_capture = childprocs.find(app_name);
        if (jack_capture) {
            if (jack_capture->kill()) {
                gx_system::gx_print_info(
		    "Record",
		    boost::format(" Terminated jack_capture, session file #%1%")
		    % last_seqno);
            } else {
                gx_system::gx_print_error(
		    "Record", " Sorry, could not stop (Ctrl-C) jack_capture");
            }
        }
        return;
    }

    if (gx_gui::GxMainInterface::get_instance().jack.client == NULL) {
        gtk_toggle_button_set_active(cap_button, FALSE);
        (void)gx_gui::gx_message_popup(
            "  WARNING [Record]\n\n  "
            "  Reconnect to Jack server first (Shift+C)"
            );
        return;
    }

    gx_system::gx_print_info("Record", " Trying to run jack_capture");
    list<string> capturas = capture_command(last_seqno);
    if (capturas.empty()) {
        gtk_toggle_button_set_active(cap_button, FALSE);
        return; // messages to user already done
    }
    GxChild *jack_capture = childprocs.launch(app_name, capturas, SIGINT);
    if (!jack_capture) {
        gtk_toggle_button_set_active(cap_button, FALSE);
        gx_system::gx_print_error("Record",
                                 "  WARNING [jack_capture]  Sorry, could not start jack_capture");
        return;
    }
    new JackCapture(jack_capture, cap_button);
    gx_system::gx_print_info(
	"Record",
	boost::format("Started jack_capture, session file #%1%") % last_seqno);
}
#endif

//-------------------- meterbridge --------------------------

Meterbridge::Meterbridge(GxChild *p, GtkCheckMenuItem *i)
    : item(i) {
    gtk_widget_ref(GTK_WIDGET(item));
    p->terminated.connect(sigc::mem_fun(*this, &Meterbridge::terminated));
}

void Meterbridge::terminated(bool pgm_found) {
    gtk_check_menu_item_set_active(item, false);
    if (pgm_found) {
        gx_system::gx_print_info("Meterbridge", "meterbridge terminated");
    } else {
        gx_gui::gx_message_popup(
            "  "
            " WARNING [meterbridge]\n\n "
            " meterbridge is not installed! "
            );
    }
    gtk_widget_unref(GTK_WIDGET(item));
    delete this;
}

void Meterbridge::stop() {
    childprocs.kill("meterbridge");
}

void Meterbridge::start_stop(GtkCheckMenuItem *menuitem, gpointer) {
    // no need to do all this if jack is not running
    if (!gx_gui::GxMainInterface::get_instance().jack.client) {
        (void)gx_gui::gx_message_popup(
            "  WARNING [Meterbridge]\n\n  "
            "  Reconnect to Jack server first (Shift+C)"
            );
        return;
    }

    const char *app_name = "meterbridge";
    if (gtk_check_menu_item_get_active(menuitem)) {
        if (childprocs.find(app_name)) {
            return;
        }
        string s = gx_gui::GxMainInterface::get_instance().jack.get_instancename() + "_" + app_name;
        const char * const args[] = {
            app_name, "-n", s.c_str(), "-t", "sco", "-c", "3",
            (gx_gui::GxMainInterface::get_instance().jack.client_name+":in_0").c_str(),
            (gx_gui::GxMainInterface::get_instance().jack.client_name+":out_0").c_str(),
            (gx_gui::GxMainInterface::get_instance().jack.client_insert_name+":in_0").c_str(),
            (gx_gui::GxMainInterface::get_instance().jack.client_insert_name+":out_0").c_str(),
            (gx_gui::GxMainInterface::get_instance().jack.client_insert_name+":out_1").c_str(),
            0 };
        GxChild *meterbridge = childprocs.launch(app_name, args, SIGTERM);
        if (meterbridge) {
            new Meterbridge(meterbridge, menuitem);
        } else {
            gx_gui::gx_message_popup(
                "  "
                "WARNING [meterbridge]\n\n  "
                "meterbridge could not be launched!"
                );
            gx_system::gx_print_error("Meterbridge",
                           string("meterbridge could not be launched (fork failed)!"));
            gtk_check_menu_item_set_active(menuitem, FALSE);
        }
    } else {  // -- deactivate meterbridge
        childprocs.kill(app_name);
    }
}
} /* end of gx_child_process namespace */
