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
 *
 *    gx_head portmap window
 *
 * ----------------------------------------------------------------------------
 */

#include "guitarix.h"    // NOLINT

#include <cstring>       // NOLINT
#include <list>          // NOLINT
#include <string>        // NOLINT

/****************************************************************
 ** PortMapWindow
 */

namespace gx_portmap {

static PortAttr gx_head_ports[] = {
    // client_num, is_insert, port_name, is_input, port_type
    { 0, false, "in_0", true, JACK_DEFAULT_AUDIO_TYPE },
    { 1, false, "out_0", false, JACK_DEFAULT_AUDIO_TYPE },
    { 1, false, "out_1", false, JACK_DEFAULT_AUDIO_TYPE },
    { 0, false, "midi_in_1", true, JACK_DEFAULT_MIDI_TYPE },
    { 0, false, "midi_out_1", false, JACK_DEFAULT_MIDI_TYPE },
    { 1, true,  "in_0", true, JACK_DEFAULT_AUDIO_TYPE },
    { 0, true,  "out_0", false, JACK_DEFAULT_AUDIO_TYPE },
};

#define ALSA_PCM "alsa_pcm"  // special alsa sequencer gxjack.client
#define ALSA_PCM_LEN_1 9

/****************************************************************
** ClientList
**
** (helper to convert the jack port list into a sorted list with sub-lists)
*/

struct ClientPortList {
    const char *client;
    int len;
    list<const char*> ports;
    explicit ClientPortList(const char *p);
    inline void add(const char *p) { ports.push_back(p); }
    inline bool sameclient(const char *p) { return strncmp(client, p, len) == 0; }
    string clientname() { return string(*ports.begin()).substr(0, len-1); }
};

ClientPortList::ClientPortList(const char *p) {
    client = p;
    const char *q = strchr(p, ':');
    if (q) {
        len = (q - p) + 1;
        if (strncmp(p, (ALSA_PCM ":"), ALSA_PCM_LEN_1) == 0) {
            q = strchr(p+len, '/');
            if (q) {
                len = (q - p) + 1;
            } else {
                len = strlen(p);
            }
        }
    } else { // should not happen
        len = strlen(p);
    }
}

struct ClientList: list<ClientPortList*> {
    static bool str_compare(const char *a, const char *b);
    explicit ClientList(const char**);
    ~ClientList();
    void remove(string excl);
};

bool ClientList::str_compare(const char *a, const char *b) {
    return strcmp(b, a) > 0;
}

ClientList::ClientList(const char **ports) {
    list<const char*> l;
    for (int i = 0; ports[i]; ++i) {
        l.push_back(ports[i]);
    }
    l.sort(str_compare);
    if (l.empty()) {
        return;
    }
    ClientPortList *cp = new ClientPortList(*l.begin());
    for (list<const char*>::iterator j = l.begin(); j != l.end(); ++j) {
        if (!cp->sameclient(*j)) {
            push_back(cp);
            cp = new ClientPortList(*j);
        }
        cp->add(*j);
    }
    push_back(cp);
}

ClientList::~ClientList() {
    for (list<ClientPortList*>::iterator i = begin(); i != end(); ++i) {
        delete *i;
    }
}

void ClientList::remove(string excl) {
    for (list<ClientPortList*>::iterator i = begin(); i != end();) {
        if ((*i)->sameclient(excl.c_str())) {
            list<ClientPortList*>::iterator n = i++;
            delete *n;
            erase(n);
            break;
        } else {
            ++i;
        }
    }
}


/****************************************************************
** PortMapWindow
*/

/*
** port registration / removal
*/

static string client_from_port(const string& port) {
    size_t pos = port.find_first_of(':');
    if (pos == string::npos) {
        return port;
    }
    string s = port.substr(0, pos);
    if (s.compare(ALSA_PCM) != 0) {
        return s;
    }
    size_t p2 = port.find_first_of('/', ALSA_PCM_LEN_1);
    if (p2 == string::npos) {
        return port;
    }
    return port.substr(0, p2);
}

static bool compare_client(const string& name, const string& p) {
    if (name.compare(0, name.size(), p, 0, name.size()) == 0) {
        if (p[name.size()] == ':' || p.size() == name.size()) {
            return true;
        }
    }
    if (p.compare(0, ALSA_PCM_LEN_1, (ALSA_PCM ":"))) {
        if (name.compare(0, name.size(), p, ALSA_PCM_LEN_1, name.size()) == 0) {
            if (p[ALSA_PCM_LEN_1+name.size()] == '/' || p.size() == ALSA_PCM_LEN_1+name.size()) {
                return true;
            }
        }
    }
    return false;
}

static bool compare_port(const string& name, const char *p) {
    return name.compare(p) == 0;
}

bool PortMapWindow::walk_remove(Glib::RefPtr<Gtk::TreeStore> ts, bool (*compare)  //  NOLINT
                               (const string&, const char*), string data) {
    bool changed = false;
    Gtk::TreeIter i(ts->children().begin());
    while (i) {
	if ((*i)[columns.is_port]) {
            if (data == (*i)[columns.port]) {
                changed = true;
                i = ts->erase(i);
		continue;
            }
        } else {
	    Gtk::TreeIter j(i->children().begin());
            while (j) {
                if (data == (*j)[columns.port]) {
                    changed = true;
		    j = ts->erase(j);
		    continue;
                }
		++j;
            }
        }
	++i;
    }
    return changed;
}

void PortMapWindow::walk_insert(Glib::RefPtr<Gtk::TreeStore> ts, string name) {
    // clients and ports on top level
    for (Gtk::TreeIter i(ts->children().begin()); i; ++i) {
	Glib::ustring p = (*i)[columns.port];
	if (name == p) {
	    return;
	}
	if (!(*i)[columns.is_port] && compare_client(client_from_port(name), p)) {
	    // ports of a gxjack.client, 2nd level
	    for (Gtk::TreeIter j(i->children().begin()); j; ++j) {
		// if we already have the port get out
		if (name == (*j)[columns.port]) {
		    return;
		}
	    }
	    Gtk::TreeRow row = *ts->append(i->children());
	    row[columns.port] = name;
	    row[columns.connected] = false;
	    row[columns.is_port] = true;
	    return;
	}
    }
    Gtk::TreeRow row = *ts->append();
    row[columns.port] = name;
    row[columns.connected] = false;
    row[columns.is_port] = true;
}

void PortMapWindow::port_changed(string name, const char *tp, int flags, bool reg) {
    if (reg == 0) {
        for (int i = 0; i < number_of_ports; ++i) {
            PortSection& p = portsection[i];
            if (walk_remove(p.treestore, compare_port, name)) {
                update_summary(p);
            }
        }
    } else {
        for (list<string>::iterator j = excluded_clients.begin();
            j != excluded_clients.end(); ++j) {
            if (name.compare(0, j->size(), *j) == 0) {
                return;
            }
        }
        for (int i = 0; i < number_of_ports; ++i) {
            PortSection *p = &portsection[i];
            if (strcmp(p->port_attr->port_type, tp) != 0) {
                continue;
            }
            if (p->port_attr->is_input) {
                if (!(flags & JackPortIsOutput)) {
                    continue;
                }
            } else {
                if (!(flags & JackPortIsInput)) {
                    continue;
                }
            }
            walk_insert(p->treestore, name);
        }
    }
}


/*
** port connection change
*/

list<string> PortMapWindow::walk(Glib::RefPtr<Gtk::TreeStore> ts, string *port, int connect) {
    list<string> l;
    for (Gtk::TreeIter i(ts->children().begin()); i; ++i) {
	Glib::ustring p = (*i)[columns.port];
	bool is_connected = (*i)[columns.connected];
        if ((*i)[columns.is_port]) {
            if (port && port->compare(p) == 0) {
                is_connected = connect;
		(*i)[columns.connected] = connect;
            }
            if (is_connected) {
                l.push_back(p);
            }
        } else {
	    for (Gtk::TreeIter j(i->children().begin()); j; ++j) {
		Glib::ustring p = (*j)[columns.port];
		bool is_connected = (*j)[columns.connected];
                if (port && port->compare(p) == 0) {
                    is_connected = connect;
		    (*j)[columns.connected] = connect;
                }
                if (is_connected) {
                    l.push_back(p);
                }
	    }
	}
    }
    return l;
}

void PortMapWindow::update_summary(PortSection& p, string *port, bool conn) {
    list<string> l = walk(p.treestore, port, conn);
    if (!p.expander) {
        return;
    }
    string q;
    list<string>::iterator i = l.begin();
    if (i != l.end()) {
        q = *i++;
    }
    for (; i != l.end(); ++i) {
        q += "\n" + *i;
    }
    p.label->set_text(q);
    Glib::signal_idle().connect_once(
	sigc::bind(
	    sigc::mem_fun(*this, &PortMapWindow::redraw_expander), p.expander));
}

void PortMapWindow::connection_changed(string port1, string port2, bool conn) {
    for (int i = 0; i < number_of_ports; ++i) {
        PortSection& p = portsection[i];

        string s = (p.port_attr->client_num == 0 ?
                    jack.client_name : jack.client_insert_name)
            + ":" + p.port_attr->port_name;
        if (s.compare(port1) == 0) {
            update_summary(p, &port2, conn);
        } else if (s.compare(port2) == 0) {
            update_summary(p, &port1, conn);
        }
    }
}


/*
** gtk callback functions
*/

void PortMapWindow::on_check_resize() {
    // cf. comment at the end of on_expander()
    if (monitored_expander_child &&
        !monitored_expander_child->get_child_visible()) {
        monitored_expander_child = 0;
        int x, y, width, height;
        window->get_window()->get_geometry(x, y, width, height);
        window->resize(width, 1);
    }
}

void PortMapWindow::on_expander(Gtk::Expander& expander) {
    gboolean expanded = expander.get_expanded();
    if (expanded) {
        // close all other expanders and unset their expand child property
        for (int i = 0; i < number_of_ports; ++i) {
	    Gtk::Expander *w = portsection[i].expander;
            if (&expander != w) {
		/*
                GValue v = {0};
                g_value_init(&v, G_TYPE_BOOLEAN);
                g_value_set_boolean(&v, FALSE);
		w->get_parent()->child_set_property(w, "expand", &v);
		*/
                w->set_expanded(false);
            }
        }
    }
    // set the expand child property of the current expander if its expanded
    /*
    GValue value = {0};
    g_value_init(&value, G_TYPE_BOOLEAN);
    g_value_set_boolean(&value, expanded);
    expander.get_parent().child_set_property(expander, "expand", &value);
    */
    expander.set_expanded(expanded);
    if (!expanded) {
        // when the expander is explicitely closed (so all expanders are
        // closed now) we want to shrink the portmap window with
        // gtk_window_resize().
        // But GtkExpander uses a timer before the child is made
        // unvisible and a resize of the window is triggered.
        // So we defer resizing to the "check-resize"-signal handler
        monitored_expander_child = expander.get_child();
    }
}

void PortMapWindow::redraw_expander(Gtk::Expander* ex) {
    ex->queue_draw();
}

void PortMapWindow::on_cell_toggle(Glib::ustring path, PortSection& p) {
    Gtk::TreeIter iter(p.treestore->get_iter(path));
    Glib::ustring q1 = (*iter)[columns.port];
    bool v = (*iter)[columns.connected];
    string gcln;
    jack_client_t *gcl;
    if (p.port_attr->client_num == 0) {
        gcl = jack.client;
        gcln = jack.client_name;
    } else {
        gcl = jack.client_insert;
        gcln = jack.client_insert_name;
    }
    Glib::ustring q2(gcln + ":" + p.port_attr->port_name);
    if (!p.port_attr->is_input) {
	Glib::ustring sw = q1;
        q1 = q2;
        q2 = sw;
    }

    v = !v;
    int ret;

    if (v) {
        ret = jack_connect(gcl, q1.c_str(), q2.c_str());
    } else {
        ret = jack_disconnect(gcl, q1.c_str(), q2.c_str());
    }

    if (ret != 0) {
        ostringstream buf;
        buf << "couldn't " << (v ? "" : "dis") << "connect " << q2 << " -> " << q1;
        gx_print_error("port connection", buf.str());
        return;
    }
    (*iter)[columns.connected] = v;
    update_summary(p);
}

/*
** constuctor / destructor
*/

inline bool getnumber(const Glib::ustring& p, long *pi) {  //  NOLINT
    char *q;
    *pi = strtol(p.c_str(), &q, 10);
    return !*q;
}

int PortMapWindow::sort_func(const Gtk::TreeModel::iterator& a, const Gtk::TreeModel::iterator& b) {
    Glib::ustring pa((*a)[columns.port]), pb((*b)[columns.port]);
    int i = 0;
    for (; ; ++i) {
        if (pa[i] != pb[i]) {
            break;
        }
        if (!pa[i]) {
            return 0;
        }
    }
    long ia = 0, ib = 0;  // initialize to silence compiler warning...
    if (getnumber(pa.substr(i), &ia) && getnumber(pb.substr(i), &ib)) {
        return ia - ib;
    }
    return pa.compare(pb);
}

void PortMapWindow::load(int sect, jack_port_t *jack_port) {
    if (jack.client) {
        const unsigned int max_items_unfolded = 1;
        PortSection& ps = portsection[sect];
	Glib::RefPtr<Gtk::TreeStore> tree = ps.treestore;
        assert(tree);
	tree->set_sort_func(0, sigc::mem_fun(*this, &PortMapWindow::sort_func));
        tree->set_sort_column(0, Gtk::SORT_ASCENDING);
        tree->clear();
        const char **ports;
        
        jack_client_t *gcl = (ps.port_attr->client_num == 0 ? jack.client
                              : jack.client_insert);
        if (jack.single_client) {
            gcl = jack.client;
        }
        
        ports = jack_get_ports(gcl, NULL, ps.port_attr->port_type,
                               (ps.port_attr->is_input ? JackPortIsOutput : JackPortIsInput));
        if (!ports) {
            return;
        }
        const char** conn_ports = jack_port_get_connections(jack_port);
        ClientList cl(ports);
        // the following loop depends on the first 2 entries being
        // gxjack.client_name and gxjack.client_insert_name
        int idx = 0;
        for (list<string>::iterator j = excluded_clients.begin(); j !=
                                        excluded_clients.end(); ++j, idx++) {
            if (!ps.port_attr->is_insert || ps.port_attr->client_num != idx) {
                cl.remove(*j);
            }
        }
	Gtk::TreeIter iter, parent, *parentp;
        for (ClientList::iterator i = cl.begin(); i != cl.end(); ++i) {
            ClientPortList *p = *i;
            if (cl.size() > 1 && p->ports.size() > max_items_unfolded) {
                parent = tree->append();
		(*parent)[columns.port] = p->clientname();
		(*parent)[columns.connected] = false;
		(*parent)[columns.is_port] = false;
                parentp = &parent;
            } else {
                parentp = 0;
            }
	    //printf("Client: %s\n", p->clientname().c_str());
            for (list<const char*>::iterator j = p->ports.begin(); j != p->ports.end(); ++j) {
		//printf("Port: %s\n", *j);
                bool conn = false;
                if (conn_ports) {
                    for (const char** q = conn_ports; *q; q++) {
                        if (strcmp(*q, *j) == 0) {
                            conn = true;
                            break;
                        }
                    }
                }
		if (parentp) {
		    iter = tree->append((*parentp)->children());
		} else {
		    iter = tree->append();
		}
		(*iter)[columns.port] = *j;
		(*iter)[columns.connected] = conn;
		(*iter)[columns.is_port] = true;
            }
        }
        free(conn_ports);
        free(ports);
        update_summary(portsection[sect]);
    }
}

void PortMapWindow::load_all() {
#define uslp() usleep(10); // prevents xruns?? (bug in jackd?)
    load(0, jack.ports.input.port);
    uslp();
    load(1, jack.ports.output1.port);
    uslp();
    load(2, jack.ports.output2.port);
    uslp();
    load(3, jack.ports.midi_input.port);
    uslp();
#if defined(USE_MIDI_OUT) || defined(USE_MIDI_CC_OUT)
    load(4, jack.ports.midi_output.port);
    uslp();
#endif
    if (!jack.single_client) {
        load(5, jack.ports.insert_in.port);
        uslp();
        load(6, jack.ports.insert_out.port);
    }
#undef uslp
}

PortMapWindow* PortMapWindow::create(gx_engine::GxMachineBase& machine, Glib::RefPtr<Gtk::AccelGroup> ag) {
    gx_jack::GxJack *jack = machine.get_jack();
    if (!jack) {
	return 0;
    }
    Glib::RefPtr<gx_gui::GxBuilder> bld = gx_gui::GxBuilder::create_from_file(
	gx_system::get_options().get_builder_filepath("ports.glade"), &machine);
    return new PortMapWindow(bld, *jack, ag);
}

PortMapWindow::PortMapWindow(Glib::RefPtr<gx_gui::GxBuilder> bld, gx_jack::GxJack& jack_, Glib::RefPtr<Gtk::AccelGroup> ag)
    : portsection(),
      excluded_clients(),
      jack(jack_),
      monitored_expander_child(0) {
    bld->get_toplevel("PortMapWindow", window);
    monitored_expander_child = 0;

    // order of first 2 entries is important (check load())
    excluded_clients.push_back(string(jack.client_insert_name) + ":");
    excluded_clients.push_back(string(jack.client_name) + ":");
    excluded_clients.push_back(string(jack.get_instancename()) + "_meterbridge:");
    excluded_clients.push_back(string("jack_capture:"));

    // no need to set, its transient window
    //window->set_icon(Glib::wrap(GDK_PIXBUF(gx_gui::gw.ib),true));
    Gtk::Widget *b;
    bld->find_widget("button1",b);
    assert(b);
    b->set_name("rack_button");
    //Gtk::VBox *vbox1;
    //bld->find_widget("dialog-vbox1", vbox1);
    //g_signal_connect(GTK_WIDGET(vbox1->gobj()), "expose-event",
                     //G_CALLBACK(gx_cairo::rectangle_skin_color_expose), NULL);
   // vbox1->signal_expose_event().connect(
	//sigc::group(&gx_cairo::rectangle_skin_color_expose,GTK_WIDGET(vbox1->gobj()),sigc::_1,(void*)0),false);
    //Gtk::VBox *vbox2;
    //bld->find_widget("dialog-vbox2", vbox2);
    //g_signal_connect(GTK_WIDGET(vbox2->gobj()), "expose-event",
                     //G_CALLBACK(gx_cairo::rectangle_skin_color_expose), NULL);
  //  vbox2->signal_expose_event().connect(
//	sigc::group(&gx_cairo::rectangle_skin_color_expose,GTK_WIDGET(vbox2->gobj()),sigc::_1,(void*)0),false);
    //vbox1->set_redraw_on_allocate(true);
    //vbox2->set_redraw_on_allocate(true);
    for (int i = 0; i < number_of_ports; ++i) {
        portsection[i].port_attr = &gx_head_ports[i];
        char name[30];
        snprintf(name, sizeof(name), "scrolledwindow%d", i+1);
	bld->find_widget(name, portsection[i].scrolled_window);
        snprintf(name, sizeof(name), "treeview%d", i+1);
	Gtk::TreeView *view;
	bld->find_widget(name, view);
	Gtk::CellRendererToggle *cell = dynamic_cast<Gtk::CellRendererToggle*>(view->get_column_cell_renderer(0));
	portsection[i].treestore = Gtk::TreeStore::create(columns);
	view->set_model(portsection[i].treestore);
        //snprintf(name, sizeof(name), "treestore%d", i+1);
        //bld->find_widget(name, portsection[i].treestore);
        //snprintf(name, sizeof(name), "cellrenderertoggle%d", i+1);
	//Gtk::CellRendererToggle *tg;
	//bld->find_widget(name, tg);
	cell->signal_toggled().connect(
	    sigc::bind(
		sigc::mem_fun(*this, &PortMapWindow::on_cell_toggle),
		sigc::ref(portsection[i])));
        snprintf(name, sizeof(name), "expander%d", i+1);
	//bld->find_widget(name, portsection[i].expander);
        if (portsection[i].expander) {
	    portsection[i].expander->property_expanded().signal_changed().connect(
		sigc::bind(
		    sigc::mem_fun(*this, &PortMapWindow::on_expander),
		    sigc::ref(*portsection[i].expander)));
            snprintf(name, sizeof(name), "port%d", i+1);
            bld->find_widget(name, portsection[i].label);
        }
    }

    load_all();

    window->add_accel_group(ag);
    window->signal_check_resize().connect(sigc::mem_fun(*this, &PortMapWindow::on_check_resize),true);
    window->show();
    Gtk::Notebook *n;
    bld->find_widget("notebook1",n);
    Gtk::Widget *t;
    t = n->get_nth_page(1);
    if (jack.single_client) t->hide();
    jack.signal_portchange().connect(sigc::mem_fun(*this, &PortMapWindow::refresh));
    jack.signal_connection_changed().connect(sigc::mem_fun(*this, &PortMapWindow::connection_changed));
    jack.send_connection_changes(true);
}

// refresh portmap widget when connect/disconnect with jack server
void PortMapWindow::refresh() {
    if (!jack.client) {
	for (int i = 0; i< number_of_ports; ++i) {
	    PortSection& ps = portsection[i];
	    Glib::RefPtr<Gtk::TreeStore> tree = ps.treestore;
	    assert(tree);
	    tree->set_sort_func(0, sigc::mem_fun(*this, &PortMapWindow::sort_func));
	    tree->set_sort_column(0, Gtk::SORT_ASCENDING);
	    tree->clear();
	    update_summary(portsection[i]);
	}
    } else {
	load_all();
    }
}

PortMapWindow::~PortMapWindow() {
    jack.send_connection_changes(false);
    delete window;
}

} // namespace gui
