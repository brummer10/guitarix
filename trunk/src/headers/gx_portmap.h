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

#ifndef SRC_HEADERS_GX_PORTMAP_H_
#define SRC_HEADERS_GX_PORTMAP_H_

#include <gtk/gtk.h>
#include <gtkmm.h>
#include <jack/jack.h>

#include <list>
#include <string>

namespace gx_portmap {

/****************************************************************
 ** PortMapWindow
 */

struct PortAttr {
    const int client_num;
    const bool is_insert;
    const char *port_name;
    bool is_input;
    const char *port_type;
};

struct PortSection {
    Glib::RefPtr<Gtk::TreeStore> treestore;
    Gtk::ScrolledWindow *scrolled_window;
    Gtk::Expander *expander;
    Gtk::Label *label;
    PortAttr *port_attr;
};

class PortMapWindow: public sigc::trackable {
private:
    enum {
	number_of_ports = 7
    };
    struct ModelColumns : public Gtk::TreeModelColumnRecord {
	Gtk::TreeModelColumn<Glib::ustring> port;
	Gtk::TreeModelColumn<bool> connected;
	Gtk::TreeModelColumn<bool> is_port;
	ModelColumns() { add(port); add(connected); add(is_port); }
    };
    const ModelColumns columns;
    PortSection portsection[number_of_ports];
    list<string> excluded_clients;
    gx_jack::GxJack& jack;
    Gtk::Widget *monitored_expander_child;
    void on_expander(Gtk::Expander& expander);
    void on_check_resize();
    void on_cell_toggle(Glib::ustring path, PortSection& p);
    void update_summary(PortSection& p, string *port = 0, bool connect = false);
    void redraw_expander(Gtk::Expander* expander);
    list<string> walk(Glib::RefPtr<Gtk::TreeStore> ts, string *port, int connect);
    bool walk_remove(Glib::RefPtr<Gtk::TreeStore> ts, bool (*compare)(const string&, const char*), string data);
    void walk_insert(Glib::RefPtr<Gtk::TreeStore> ts, string data);
    void load(int sect, jack_port_t*);
    void load_all();
    int sort_func(const Gtk::TreeIter& a, const Gtk::TreeIter& b);
    explicit PortMapWindow(Glib::RefPtr<gx_gui::GxBuilder> bld, gx_jack::GxJack& jack, Glib::RefPtr<Gtk::AccelGroup> ag);
    Gtk::Dialog *window;
    void client_removed(string name);
    void port_changed(string name, const char *tp, int flags, bool reg);
public:
    ~PortMapWindow();
    static PortMapWindow* create(gx_jack::GxJack& jack, gx_ui::GxUI& ui, Glib::RefPtr<Gtk::AccelGroup> ag);
    void refresh();
    void connection_changed(string port1, string port2, bool conn);
    Glib::SignalProxy1<void,int> signal_response() { return window->signal_response(); }
};

} // end namespace gx_portmap
#endif  // SRC_HEADERS_GX_PORTMAP_H_
