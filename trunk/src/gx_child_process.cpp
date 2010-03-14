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
 *
 *  This is the guitarix module handling child processes spawned from it
 *
 * --------------------------------------------------------------------------
 */

#include <sys/wait.h>
#include <errno.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>
#include <set>
#include <list>
#include <map>
#include <cstdlib>
#include <cstdio>
#include <cmath>


using namespace std;

#include <gtk/gtk.h>
#include <jack/jack.h>
#include <sndfile.h>
//#include <fftw3.h>

#include "guitarix.h"

using namespace gx_system;
using namespace gx_engine;

namespace gx_child_process
{

gboolean gx_sigchld_handler(gpointer)
{
	int status;
	pid_t pid = waitpid(-1, &status, WNOHANG);
	if (pid == 0 || pid == -1) {
		return false;
	}
	bool not_found = false;
	if (WIFEXITED(status)) {
		if (WEXITSTATUS(status) == 127) {
			not_found = true;
		}
	} else if (!WIFSIGNALED(status)) {
		return false;
	}
	// child pid has terminated
	int idx;
	for (idx = 0; idx < NUM_OF_CHILD_PROC; idx++) {
		if (child_pid[idx] == pid) {
			child_pid[idx] = NO_PID;
			break;
		}
	}
	switch (idx) {
	case JACKCAP_IDX:
		//FIXME
		break;
	case METERBG_IDX:
		if (not_found) {
			gx_gui::gx_message_popup(
				"  "
				" WARNING [meterbridge]\n\n "
				" meterbridge is not installed! "
				);
		}
		gx_gui::GxMainInterface::instance()->meterbridge_terminated();
		break;
	}
	return false;
}

//----- terminate child processes
int gx_terminate_child_procs()
{
	// meterbridge
	if (child_pid[METERBG_IDX] != NO_PID) {
		(void)kill(child_pid[METERBG_IDX], SIGTERM);
	}

	// jack_capture
	if (child_pid[JACKCAP_IDX] != NO_PID)
	{
		(void)kill(child_pid[JACKCAP_IDX], SIGINT);
		(void)gx_pclose(jcap_stream, JACKCAP_IDX);
	}

	// jconv
	if (child_pid[JCONV_IDX] != NO_PID)
	{
		(void)kill(child_pid[JCONV_IDX], SIGINT);
		(void)gx_pclose(jconv_stream, JCONV_IDX);
	}
	return 0;
}

//---- popen revisited for guitarix
FILE* gx_popen(const char *cmdstring,
               const char *type,
               const int proc_idx)
{
	int   i, pfd[2];
	pid_t	pid;
	FILE	*fp;

	/* only allow "r" or "w" */
	if ((type[0] != 'r' && type[0] != 'w') || type[1] != 0)
	{
		errno = EINVAL;		/* required by POSIX.2 */
		return(NULL);
	}

	if (pipe(pfd) < 0)
		return(NULL);	/* errno set by pipe() */

	if ((pid = fork()) < 0)
		return(NULL);	/* errno set by fork() */

	else if (pid == 0)
	{
		if (*type == 'r')
		{
			close(pfd[0]);
			if (pfd[1] != STDOUT_FILENO)
			{
				dup2(pfd[1], STDOUT_FILENO);
				close(pfd[1]);
			}
		}
		else
		{
			close(pfd[1]);

			if (pfd[0] != STDIN_FILENO)
			{
				dup2(pfd[0], STDIN_FILENO);
				close(pfd[0]);
			}
		}

		/* close all descriptors in child_pid[] */
		for (i = 0; i < NUM_OF_CHILD_PROC; i++)
			if (child_pid[i] > 0)
				close(i);

		execl("/bin/sh", "sh", "-c", cmdstring, (char *) 0);
		_exit(127);
	}

	/* parent */
	if (*type == 'r')
	{
		close(pfd[1]);

		if ((fp = fdopen(pfd[0], type)) == NULL)
			return(NULL);

	}
	else
	{
		close(pfd[0]);

		if ((fp = fdopen(pfd[1], type)) == NULL)
			return(NULL);
	}

	child_pid[proc_idx] = pid; /* remember child pid for this fd */
	return(fp);
}

//---- pclose revisited for guitarix
int gx_pclose(FILE *fp, const int proc_idx)
{
	int stat;
	pid_t	pid;

	if ((pid = child_pid[proc_idx]) == 0)
		return(-1);	/* fp wasn't opened by gx_popen() */

	// reset internal process pid
	child_pid[proc_idx] = NO_PID;

	// check control stream
	if (!fp)
		return(-1);

	// close it
	if (fclose(fp) == EOF)
		return(-1);

	while (waitpid(pid, &stat, 0) < 0)
		if (errno != EINTR)
			return(-1); /* error other than EINTR from waitpid() */

	return(stat);	/* return child's termination status */
}

// -------------------------------------------
bool gx_lookup_pid(const pid_t child_pid)
{
	// --- this function looks up the given PID from the list of processes
	// it returns true if a match is found.
	string pstr = gx_i2a(child_pid) + " -o pid";

	return (gx_system_call("ps -p", pstr.c_str(), true) == SYSTEM_OK) ?
		true : false;
}

//---- find latest process ID by reading stdout from pgrep -n
pid_t gx_find_child_pid(const char* procname)
{
	// --- this function retrieves the latest PID of a named process.
	// it is to be called just after guitarix spawns a child process

	// file desc
	int fd[2];
	pid_t pid = NO_PID;

	// piping
	if (pipe(fd) < 0)
		return NO_PID;

	// forking
	if ((pid = fork()) < 0)
		return NO_PID;

	else if (pid == 0)
	{
		close(fd[0]);

		if (fd[1] != STDOUT_FILENO)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
		}

		// executing 'pgrep -n <proc name>'
		if (execl("/usr/bin/pgrep", "pgrep", "-n", procname, NULL) < 0)
			return NO_PID;
	}
	else
	{
		close(fd[1]);

		int rv;
		char line[16];

		// read stdout
		if ( (rv = read(fd[0], line, 16)) > 0)
		{
			string str = line;
			str.resize(rv-1); // remove extra character crap
			pid = atoi(str.c_str());
		}
	}

	return pid;
}

//----------------------- jack_capture settings ---------------------------
void gx_show_jack_capture_gui( GtkWidget *widget, gpointer data )
{
	// Note: to be updated ...
	int ret = system("jack_capture_gui2 -o yes -f ~/guitarix_session -n guitarix -p /.guitarix/ja_ca_ssetrc &");
	if (ret != 0) {
		ostringstream buf;
		buf << "error code: " << ret;
		gx_print_error("jack_capture_gui2", buf.str());
	}
}

//---- wav file construction for jack_capture
bool gx_capture_command(const int idx, string& capcmd)
{
	// bool ret_status = false;

	// jack_capture setup file
	string gfilename = gx_user_dir + jcapsetup_file;
	string bufi;
	// open jack_capture setup file
	ifstream f(gfilename.c_str());

	if (f.good())
	{

		getline(f, bufi);

		std::string a(bufi);
		std::string b(".");
		std::string::size_type in = a.find(b);
		in -= 1;
		if (int(in) >= 0) a.replace(in,1,gx_i2a(idx));
		else
		{
			(void)gx_gui::gx_message_popup(
				"  WARNING [Record]\n\n  "
				"  Please run jack capture settings first [alt+j]"
				);
			return false;
		}

		bufi = a;
		capcmd = bufi.c_str();
		f.close();
	}

	// jack_capture command
	// Note: this version of the code does not add a wav file by
	// default to ja_ca_ssetrc, so we try to avoid the wav filename if one
	// by putting the / delimiter in getline
	// it is backward compatible with older ja_ca_ssetrc files

// this version didn't work for ogg and mp3, so I have switch back to pre version.

	/*
	  getline(f, capcmd, '/');
	  f.close();

	  // remove trailing \n if any
	  int pos = capcmd.size()-1;

	  if (capcmd.c_str()[pos] == '\n')
	  capcmd.resize(pos);

	  ret_status = true;
	  }

	  // are we good ?
	  if (!ret_status)
	  return false;

	  // we're OK
	  capcmd += " ";
	  capcmd += getenv("HOME");
	  capcmd += "/";
	  capcmd += jcapfile_wavbase;
	  capcmd += gx_i2a(idx);
	  capcmd += ".wav";
	*/
	return true;
}

//---- start or stop record when toggle_button record is pressed
void gx_start_stop_jack_capture(GtkWidget *widget, gpointer data)
{
	// here, const applies to pointer, not pointed data ;)
	GtkToggleButton* const cap_button = (GtkToggleButton*)widget;

	// avoid running it at startup
	// (ugly hack due to GTK+ signalling side effect)
	/*#if ( __GNUC__ == 4 && __GNUC_MINOR__ >= 3 )
	  static bool cap_init = false;
	  if (!cap_init)
	  {
	  gtk_toggle_button_set_active(cap_button, FALSE);
	  cap_init = true;
	  return;
	  }
	  #endif */

	// is the button toggled ?
	const gboolean tggl_state = gtk_toggle_button_get_active(cap_button);

	// increment if capturing more than once
	static int capas = 0;

	// ---- stop recording
	if (tggl_state == FALSE)
	{
		// get jack_cap pid spawned by guitarix
		const pid_t cap_pid = child_pid[JACKCAP_IDX];

		if (cap_pid != NO_PID)   // running
		{
			if (kill(cap_pid, SIGINT) == -1)
				gx_print_error("Record",
				               string(" Sorry, could not stop (Ctrl-C) jack_capture"));
			else
				gx_print_info("Record",
				              string(" Terminated jack_capture, session file #") +
				              gx_i2a(capas-1));

			(void)gx_pclose(jcap_stream, JACKCAP_IDX);
			jcap_stream = NULL;
		}

		// reset pid nonetheless
		child_pid[JACKCAP_IDX] = NO_PID;

		// let's get out of here
		return;
	}


	// ---- button has been toggled, let's try to record

	// check that we are a valid jack client
	if (gx_jack::client == NULL)
	{
		gtk_toggle_button_set_active(cap_button, FALSE);

		(void)gx_gui::gx_message_popup(
			"  WARNING [Record]\n\n  "
			"  Reconnect to Jack server first (Shift+C)"
			);

		child_pid[JACKCAP_IDX] = NO_PID;
		return;
	}

	gx_print_info("Record", " Trying to run jack_capture");

	int const jack_cap_ok = gx_system_call("which", "jack_capture");

	// popup message if something goes funny
	string warning("  WARNING [jack_capture]\n  ");

	if (jack_cap_ok != SYSTEM_OK)   // no jack_capture in PATH! :(
	{
		warning.append(
			"  You need jack_capture >= 0.9.30 by Kjetil S. Matheussen  \n  "
			"  Please look here\n  "
			"  http://old.notam02.no/arkiv/src/?M=D\n"
			);
	}
	else
	{
		// so far so good, start capture
		string capturas;

		if (gx_capture_command(capas, capturas))
		{
			if (!gx_capture(capturas.c_str()))
				warning.append("Sorry, could not start jack_capture");
		}
		else
		{
			warning.append("Could not open wav capture file");
		}
	}

	// are we running ?
	if (child_pid[JACKCAP_IDX] != NO_PID)
	{
		gx_print_info("Record",
		              string("Started jack_capture, session file #") + gx_i2a(capas));
		capas++;
		return;
	}

	// nope :(
	gtk_toggle_button_set_active(cap_button, FALSE);
	gx_print_warning("Record", warning);
}

void gx_start_stop_jconv(GtkWidget *widget, gpointer data)
{
	if (gx_jconv::GxJConvSettings::checkbutton7 == 0) {
		conv.stop();
	} else {
		gx_jconv::GxJConvSettings* jcset = gx_jconv::GxJConvSettings::instance();
		bool rc = conv.configure(
			gx_jack::jack_bs, gx_jack::jack_sr, jcset->getIRDir()+"/"+jcset->getIRFile(),
			jcset->getGain(), jcset->getlGain(), jcset->getDelay(), jcset->getlDelay(),
			jcset->getOffset(), jcset->getLength(), jcset->getMem(), jcset->getBufferSize());
		if (!rc || !conv.start()) {
			gx_jconv::GxJConvSettings::checkbutton7 = 0;
			return;
		}
	}
}

#if FALSE
// ---------------  start stop JConv
void gx_start_stop_jconv(GtkWidget *widget, gpointer data)
{
	if (gx_jconv::GxJConvSettings::checkbutton7 == 0) {
		gx_jconv::checkbox7 = 1.0;

		pid_t pid = gx_child_process::child_pid[JCONV_IDX];

		// if jconv is already running, we have to kill it
		// applying a new jconv setting is not a runtime thing ... :(
		if (pid != NO_PID) {
			gx_print_info("JConv Start / Stop", string("killing JConv, PID = ") +
			              gx_system::gx_i2a(pid));

			(void)kill(pid, SIGINT);
			usleep(100000);

			gx_jconv::jconv_is_running = false;
			for (int c = 0; c < 2; c++)
				gtk_widget_hide(gx_gui::GxMainInterface::instance()->
				                getJCLevelMeters()[c]);

			// unregister our own jconv dedicated ports
			if (gx_jack::client) {
				if (jack_port_is_mine (gx_jack::client, gx_jack::output_ports[3])) {
					jack_port_unregister(gx_jack::client, gx_jack::output_ports[3]);
					gx_engine::gNumOutChans--;
				}

				if (jack_port_is_mine (gx_jack::client, gx_jack::output_ports[2])) {
					jack_port_unregister(gx_jack::client, gx_jack::output_ports[2]);
					gx_engine::gNumOutChans--;
				}

				if (jack_port_is_mine (gx_jack::client, gx_jack::input_ports[2])) {
					jack_port_unregister(gx_jack::client, gx_jack::input_ports[2]);
					gx_engine::gNumInChans--;
				}

				if (jack_port_is_mine (gx_jack::client, gx_jack::input_ports[1])) {
					jack_port_unregister(gx_jack::client, gx_jack::input_ports[1]);
					gx_engine::gNumInChans--;
				}

				usleep(100000);
				(void)gx_pclose(jconv_stream, JCONV_IDX);
			}
		}
	} else if (gx_engine::is_setup == 1) {
		// check whether jconv is installed in PATH
		int  jconv_ok = gx_system_call("which", "jconvolver");

		// popup message if something goes funny
		string warning;
		string witch_convolver = "jconvolver";

		// is jconvolver installed ?
		if (jconv_ok != SYSTEM_OK) { // no jconvolver in PATH! :(
			jconv_ok = gx_system_call("which", "jconv");
			witch_convolver = "jconv";
		}
		// is jconv installed ?
		if (jconv_ok != SYSTEM_OK) { // no jconv in PATH! :(
			warning +=
				"  WARNING [JConv]\n\n  "
				"  You need jconv by  Fons Adriaensen "
				"  Please look here\n  "
				"  http://www.kokkinizita.net/linuxaudio/index.html\n";
		} else { // yeps
			if (gx_jack::client == NULL) {
				warning +=
					"  WARNING [JConv]\n\n  "
					"  Reconnect to Jack server first (Shift+C)";
				gx_jconv::GxJConvSettings::checkbutton7 = 0;
				gx_jconv::jconv_is_running = false;

				gx_child_process::child_pid[JCONV_IDX] = NO_PID;
			} else{
				string conffile = gx_user_dir + "jconv_set.conf";
				gx_jconv::gx_jconv_write_conffile(conffile); //FIXME check return
				string cmd(witch_convolver);
				cmd += " -N jconvgx";
				cmd += " " + conffile + " 2> /dev/null";

				jconv_stream = gx_popen (cmd.c_str(), "r", JCONV_IDX);
				sleep (2);

				// let's fetch the pid of the new jconv process
				pid_t pid = gx_find_child_pid(witch_convolver.c_str());

				string check_double(" pidof ");
				check_double += witch_convolver;
				check_double += " > /dev/null";

				// failed ?
				if (pid == NO_PID) {
					warning +=
						"  WARNING [JConv]\n\n  "
						"  Sorry, jconv startup failed ... giving up!";
				} else if (!system(check_double.c_str()) == 0) {
					warning +=
						"  WARNING [JConv]\n\n  "
						"  Sorry, jconv startup failed ... giving up!";
				} else {
					// store pid for future process monitoring
					child_pid[JCONV_IDX] = pid;

					// let's (re)open our dedicated ports to jconv
					if (!gx_jconv::jconv_is_running) {
						ostringstream buf;

						// extra guitarix jack ports for jconv
						for (int i = 2; i < 4; i++) {
							buf.str("");
							buf << "out_" << i;

							gx_jack::output_ports[i] =
								jack_port_register(gx_jack::client,
								                   buf.str().c_str(),
								                   JACK_DEFAULT_AUDIO_TYPE,
								                   JackPortIsOutput, 0);
							gx_engine::gNumOutChans++;
						}
						for (int i = 2; i < 4; i++) {
							buf.str("");
							buf << "in_" << i-1;

							gx_jack::input_ports[i-1] =
								jack_port_register(gx_jack::client,
								                   buf.str().c_str(),
								                   JACK_DEFAULT_AUDIO_TYPE,
								                   JackPortIsInput, 0);
							gx_engine::gNumInChans++;

						}

						// ---- port connection
						witch_convolver = "jconvgx";
						string jc_port = witch_convolver +":In-1";
						if (jack_port_by_name(gx_jack::client,jc_port.c_str()))	{
							// guitarix outs to jconv ins
							jack_connect(gx_jack::client, jack_port_name(gx_jack::output_ports[2]), jc_port.c_str());
							jc_port = witch_convolver +":In-2";
							jack_connect(gx_jack::client, jack_port_name(gx_jack::output_ports[3]), jc_port.c_str());

							//  jconv to guitarix monitor
							jc_port = witch_convolver +":Out-1";
							jack_connect(gx_jack::client, jc_port.c_str(), jack_port_name(gx_jack::input_ports[1]));
							jc_port = witch_convolver +":Out-2";
							jack_connect(gx_jack::client, jc_port.c_str(), jack_port_name(gx_jack::input_ports[2]));
						} else {
							(void)gx_gui::gx_message_popup("sorry, connection faild");
						}

					}

					// tell the compute method that JConv is running
					gx_jconv::jconv_is_running = true;

					for (int c = 0; c < 2; c++) {
						gtk_widget_show(gx_gui::GxMainInterface::instance()->
						                getJCLevelMeters()[c]);
					}
					gx_print_info("JConv Start / Stop", string("Started JConv, PID = ") +
					              gx_system::gx_i2a(child_pid[JCONV_IDX]));
				}
			}
		}

		// pop up warning if any
		if (!warning.empty()) {
			(void)gx_gui::gx_message_popup(warning.c_str());
			gx_jconv::GxJConvSettings::checkbutton7 = 0;
			gx_jconv::jconv_is_running = false;
			gx_child_process::child_pid[JCONV_IDX] = NO_PID;
		}
		gx_jconv::checkbox7 = 0.0;
	}
}
#endif

//----menu function gx_meterbridge
void gx_start_stop_meterbridge(GtkCheckMenuItem *menuitem, gpointer checkplay)
{

	// no need to do all this if jack is not running
	if (!gx_jack::client) {
		(void)gx_gui::gx_message_popup(
			"  WARNING [Meterbridge]\n\n  "
			"  Reconnect to Jack server first (Shift+C)"
			);
		return;
	}

	// ---- if triggered by GUI or Alt + M
	if (gtk_check_menu_item_get_active(menuitem) == TRUE) {
		const char *app_name = "meterbridge";
		string mbg_opt("-n ");
		mbg_opt += gx_jack::client_name;
		mbg_opt += "_";
		mbg_opt += app_name;
		mbg_opt += " -t sco guitarix:in_0  guitarix:out_0";

		int pid = fork();
		if (pid == -1) {
			gx_gui::gx_message_popup(
				"  "
				"WARNING [meterbridge]\n\n  "
				"meterbridge could not be launched!"
				);

			gx_print_error("Meterbridge",
			               string("meterbridge could not be launched (fork failed)!"));
			gtk_check_menu_item_set_active(menuitem, FALSE);
			return;
		}
		if (pid == 0) {
			execlp(app_name, app_name, "-t", "sco", "guitarix:in_0", "guitarix:out_0", 0);
			exit(1);
		}
		child_pid[METERBG_IDX] = pid;
	} else {  // -- deactivate meterbridge
		if (child_pid[METERBG_IDX] == NO_PID) {
			return;
		}
		(void)kill(child_pid[METERBG_IDX], SIGTERM);
		gx_print_info("Meterbridge",
		              string("meterbridge terminated - was PID ") +
		              gx_i2a(child_pid[METERBG_IDX]));
	}
}

//----use jack_capture for record the session
bool gx_capture(const char* capturas)
{
	// open a write stream for controling the stop function
	jcap_stream = gx_popen(capturas, "w", JACKCAP_IDX);
	return (jcap_stream != NULL);
}

} /* end of gx_child_process namespace */
