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

/* ------- This is the GUI namespace ------- */


#pragma once

#include <gtk/gtk.h>
#include <jack/jack.h>
#include <list>

#ifndef NJACKLAT
#define NJACKLAT (9)
#endif

namespace gx_portmap
{

/****************************************************************
 ** PortMapWindow
 */

enum {
	number_of_ports = 7
};

struct PortAttr {
	const int client_num;
	const bool is_insert;
	const char *port_name;
	bool is_input;
	const char *port_type;
};

extern PortAttr guitarix_ports[number_of_ports];

struct PortSection
{
	GtkTreeStore *treestore;
	GtkScrolledWindow *scrolled_window;
	GtkExpander *expander;
	GtkLabel *label;
	PortAttr *port_attr;
};

class PortMapWindow
{
private:
	PortSection portsection[number_of_ports];
	GtkCheckMenuItem *menuitem;
	list<string> excluded_clients;
	GtkWidget *monitored_expander_child;
	static void on_expander(GtkWidget *widget, gpointer data);
	static void on_check_resize(GtkWidget *widget, gpointer data);
	static void response_cb(GtkWidget *widget, gint response_id, gpointer data);
	static void destroy_cb(GtkWidget*, gpointer data);
	static void on_cell_toggle(GtkCellRendererToggle *widget, gchar *path, gpointer data);
	static void update_summary(PortSection* p, string *port=0, bool connect=false);
	static gboolean redraw_expander(gpointer data);
	static list<string> walk(GtkTreeStore *ts, string *port, int connect);
	bool walk_remove(GtkTreeStore *ts, bool (*compare)(const string&, const char*), string data);
	void walk_insert(GtkTreeStore *ts, string data);
	void load(int sect, jack_port_t*);
	void load_all();
	PortMapWindow(GtkCheckMenuItem *item);
	~PortMapWindow();
public:
	static GtkWidget *window; // there can only be 1 window
	static PortMapWindow* instance;
	void client_removed(string name);
	void refresh();
	void port_changed(string name, const char *tp, int flags, bool reg);
	void connection_changed(string port1, string port2, bool conn);
	static void toggle(GtkWidget* widget, gpointer data);
};

} // end namespace gx_portmap

