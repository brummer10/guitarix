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
 * ---------------------------------------------------------------------------
 *
 *    guitarix portmap window
 *
 * ----------------------------------------------------------------------------
 */

#include <cstring>
#include <jack/jack.h>
#include "guitarix.h"

/****************************************************************
 ** PortMapWindow
 */

namespace gx_gui
{

PortAttr guitarix_ports[] = {
	//client_num, is_insert, port_name, is_input, port_type
	{ 0, false, "in_0", true, JACK_DEFAULT_AUDIO_TYPE },
	{ 1, false, "out_0", false, JACK_DEFAULT_AUDIO_TYPE },
	{ 1, false, "out_1", false, JACK_DEFAULT_AUDIO_TYPE },
	{ 0, false, "midi_in_1", true, JACK_DEFAULT_MIDI_TYPE },
	{ 0, false, "midi_out_1", false, JACK_DEFAULT_MIDI_TYPE },
	{ 1, true,  "in_0", true, JACK_DEFAULT_AUDIO_TYPE },
	{ 0, true,  "out_0", false, JACK_DEFAULT_AUDIO_TYPE },
};

#define ALSA_PCM "alsa_pcm"  // special alsa sequencer client


/****************************************************************
** ClientList
**
** (helper to convert the jack port list into a sorted list with sub-lists)
*/

struct ClientPortList {
	const char *client;
	int len;
	list<const char*> ports;
	ClientPortList(const char *p);
	inline void add(const char *p) { ports.push_back(p); }
	inline bool sameclient(const char *p) { return strncmp(client, p, len) == 0; }
	string clientname() { return string(*ports.begin()).substr(0,len-1); }
};

ClientPortList::ClientPortList(const char *p)
{
	client = p;
	const char *q = strchr(p, ':');
	if (q) {
		len = (q - p) + 1;
		if (strncmp(p, (ALSA_PCM ":"), 9) == 0) {
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

struct ClientList: list<ClientPortList*>
{
	static bool str_compare(const char *a, const char *b);
	ClientList(const char**);
	~ClientList();
	void remove(string excl);
};

bool ClientList::str_compare(const char *a, const char *b)
{
	return strcmp(b, a) > 0;
}

ClientList::ClientList(const char **ports)
{
	list<const char*> l;
	for (int i = 0; ports[i]; i++) {
		l.push_back(ports[i]);
	}
	l.sort(str_compare);
	if (l.empty()) {
		return;
	}
	ClientPortList *cp = new ClientPortList(*l.begin());
	for (list<const char*>::iterator j = l.begin(); j != l.end(); j++) {
		if (!cp->sameclient(*j)) {
			push_back(cp);
			cp = new ClientPortList(*j);
		}
		cp->add(*j);
	}
	push_back(cp);
}

ClientList::~ClientList()
{
	for (list<ClientPortList*>::iterator i = begin(); i != end(); i++) {
		delete *i;
	}
}

void ClientList::remove(string excl)
{
	for (list<ClientPortList*>::iterator i = begin(); i != end();) {
		if ((*i)->sameclient(excl.c_str())) {
			list<ClientPortList*>::iterator n = i++;
			delete *n;
			erase(n);
			break;
		} else {
			i++;
		}
	}
}


/****************************************************************
** PortMapWindow
*/

GtkWidget *PortMapWindow::window = 0;
PortMapWindow *PortMapWindow::instance = 0;

/*
** port registration / removal
*/

static string client_from_port(const string& port)
{
	size_t pos = port.find_first_of(':');
	if (pos == string::npos) {
		return port;
	}
	string s = port.substr(0, pos);
	if (s.compare(ALSA_PCM) != 0) {
		return s;
	}
	size_t p2 = port.find_first_of('/', 9);
	if (p2 == string::npos) {
		return port;
	}
	return port.substr(0, p2);
}

static bool compare_client(const string& name, const char *p)
{
	if (name.compare(0, name.size(), p, name.size()) == 0) {
		if (p[name.size()] == ':' || p[name.size()] == '\0') {
			return true;
		}
	}
	if (strncmp(p, (ALSA_PCM ":"), 9) == 0) {
		p += 9;
		if (name.compare(0, name.size(), p, name.size()) == 0) {
			if (p[name.size()] == '/' || p[name.size()] == '\0') {
				return true;
			}
		}
	}
	return false;
}

static bool compare_port(const string& name, const char *p)
{
	return name.compare(p) == 0;
}

bool PortMapWindow::walk_remove(GtkTreeStore *ts, bool (*compare)(const string&, const char*), string data)
{
	bool changed = false;
	GtkTreeIter p_iter;
	if (!gtk_tree_model_get_iter_first(GTK_TREE_MODEL(ts), &p_iter)) {
		return changed;
	}
	while (true) {
		gboolean is_port;
		gtk_tree_model_get(GTK_TREE_MODEL(ts), &p_iter, 2, &is_port, -1);
		if (is_port) {
			gchararray p;
			gtk_tree_model_get(GTK_TREE_MODEL(ts), &p_iter, 0, &p, -1);
			if (compare(data, p)) {
				changed = true;
				if (!gtk_tree_store_remove(ts, &p_iter)) {
					break;
				}
				continue;
			}
		} else {
			GtkTreeIter c_iter;
			gtk_tree_model_iter_children(GTK_TREE_MODEL(ts), &c_iter, &p_iter);
			while (true) {
				gchararray p;
				gtk_tree_model_get(GTK_TREE_MODEL(ts), &c_iter, 0, &p, -1);
				if (compare(data, p)) {
					changed = true;
					if (!gtk_tree_store_remove(ts, &c_iter)) {
						break;
					}
					continue;
				}
				if (!gtk_tree_model_iter_next(GTK_TREE_MODEL(ts), &c_iter)) {
					break;
				}
			}
			if (!gtk_tree_model_iter_has_child(GTK_TREE_MODEL(ts), &p_iter)) {
				changed = true;
				if (!gtk_tree_store_remove(ts, &p_iter)) {
					break;
				}
				continue;
			}
		}
		if (!gtk_tree_model_iter_next(GTK_TREE_MODEL(ts), &p_iter)) {
			break;
		}
	}
	return changed;
}

void PortMapWindow::walk_insert(GtkTreeStore *ts, string name)
{
	GtkTreeIter p_iter; // clients and ports on top level
	if (gtk_tree_model_get_iter_first(GTK_TREE_MODEL(ts), &p_iter)) {
		while (true) {
			gboolean is_port;
			gchararray p;
			gtk_tree_model_get(GTK_TREE_MODEL(ts), &p_iter, 0, &p, 2, &is_port, -1);
			if (name.compare(p) == 0) {
				return;
			}
			if (!is_port && compare_client(client_from_port(name), p)) {
				GtkTreeIter c_iter; // ports of a client, 2nd level
				if (gtk_tree_model_iter_children(GTK_TREE_MODEL(ts), &c_iter, &p_iter)) {
					while (true) {
						// if we already have the port get out
						gtk_tree_model_get(GTK_TREE_MODEL(ts), &c_iter, 0, &p, -1);
						if (name.compare(p) == 0) {
							return;
						}
						if (!gtk_tree_model_iter_next(GTK_TREE_MODEL(ts), &c_iter)) {
							break;
						}
					}
				}
				gtk_tree_store_insert_with_values(ts, 0, &p_iter, 0,
				                                  0, name.c_str(),
				                                  1, false,
				                                  2, true,
				                                  -1);
				return;
			}
			if (!gtk_tree_model_iter_next(GTK_TREE_MODEL(ts), &p_iter)) {
				break;
			}
		}
	}
	gtk_tree_store_insert_with_values(ts, 0, 0, 0,
	                                  0, name.c_str(),
	                                  1, false,
	                                  2, true,
	                                  -1);
}

void PortMapWindow::port_changed(string name, const char *tp, int flags, bool reg)
{
	if (reg == 0) {
		for (int i = 0; i < number_of_ports; i++) {
			PortSection *p = &portsection[i];
			if (walk_remove(p->treestore, compare_port, name)) {
				update_summary(p);
			}
		}
	} else {
		for (list<string>::iterator j = excluded_clients.begin(); j != excluded_clients.end(); j++) {
			if (name.compare(0, j->size(), *j) == 0) {
				return;
			}
		}
		for (int i = 0; i < number_of_ports; i++) {
			PortSection *p = &portsection[i];
			if (strcmp(p->port_attr->port_type, tp) != 0) {
				continue;
			}
			if (p->port_attr->is_input) {
				if (! (flags & JackPortIsOutput)) {
					continue;
				}
			} else {
				if (! (flags & JackPortIsInput)) {
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

list<string> PortMapWindow::walk(GtkTreeStore *ts, string *port, int connect)
{
	list<string> l;
	GtkTreeIter p_iter;
	if (!gtk_tree_model_get_iter_first(GTK_TREE_MODEL(ts), &p_iter)) {
		return l;
	}
	do {
		gboolean is_port, is_connected;
		gchararray p;
		gtk_tree_model_get(GTK_TREE_MODEL(ts), &p_iter, 0, &p, 1, &is_connected, 2, &is_port, -1);
		if (is_port) {
			if (port && port->compare(p) == 0) {
				is_connected = connect;
				gtk_tree_store_set(ts, &p_iter, 1, is_connected, -1);
			}
			if (is_connected) {
				l.push_back(p);
			}
		} else {
			GtkTreeIter c_iter;
			gtk_tree_model_iter_children(GTK_TREE_MODEL(ts), &c_iter, &p_iter);
			do {
				gchararray p;
				gtk_tree_model_get(GTK_TREE_MODEL(ts), &c_iter, 0, &p, 1, &is_connected, -1);
				if (port && port->compare(p) == 0) {
					is_connected = connect;
					gtk_tree_store_set(ts, &c_iter, 1, is_connected, -1);
				}
				if (is_connected) {
					l.push_back(p);
				}
			} while (gtk_tree_model_iter_next(GTK_TREE_MODEL(ts), &c_iter));
		}
	} while (gtk_tree_model_iter_next(GTK_TREE_MODEL(ts), &p_iter));
	return l;
}

void PortMapWindow::update_summary(PortSection *p, string *port, bool conn)
{
	list<string> l = walk(p->treestore, port, conn);
	if (!p->expander) {
		return;
	}
	string q;
	list<string>::iterator i = l.begin();
	if (i != l.end()) {
		q = *i++;
	}
	for (; i != l.end(); i++) {
		q += "\n" + *i;
	}
	gtk_label_set_text(p->label, q.c_str());
	g_idle_add(redraw_expander, p->expander);
}

void PortMapWindow::connection_changed(string port1, string port2, bool conn)
{
	for (int i = 0; i < number_of_ports; i++) {
		PortSection *p = &portsection[i];

		string s = (p->port_attr->client_num == 0 ? gx_jack::client_name : gx_jack::client_insert_name)
			+ ":" + p->port_attr->port_name;
		if (s.compare(port1) == 0) {
			update_summary(p, &port2, conn);
		}
		else if (s.compare(port2) == 0) {
			update_summary(p, &port1, conn);
		}
	}
}


/*
** gtk callback functions
*/

void PortMapWindow::on_check_resize(GtkWidget *widget, gpointer data)
{
	// cf. comment at the end of on_expander()
	PortMapWindow *p = (PortMapWindow*)data;
	if (p->monitored_expander_child &&
	    !gtk_widget_get_child_visible(p->monitored_expander_child)) {
		p->monitored_expander_child = 0;
		gint width;
		gdk_window_get_geometry(window->window, 0, 0, &width, 0, 0);
		gtk_window_resize(GTK_WINDOW(window), width, 1);
	}
}

void PortMapWindow::on_expander(GtkWidget *widget, gpointer data)
{
	PortMapWindow *p = (PortMapWindow*)data;
	gboolean expanded = gtk_expander_get_expanded(GTK_EXPANDER(widget));
	if (expanded) {
		// close all other expanders and unset their expand child property
		for (int i = 0; i < number_of_ports; i++) {
			GtkWidget *w = GTK_WIDGET(p->portsection[i].expander);
			if (widget != w) {
				GValue v = {0};
				g_value_init(&v, G_TYPE_BOOLEAN);
				g_value_set_boolean(&v, FALSE);
				gtk_container_child_set_property(GTK_CONTAINER(gtk_widget_get_parent(w)), w, "expand", &v);
				gtk_expander_set_expanded(GTK_EXPANDER(w), FALSE);
			}
		}
	}
	// set the expand child property of the current expander if its expanded
	GValue value = {0};
	g_value_init(&value, G_TYPE_BOOLEAN);
	g_value_set_boolean(&value, expanded);
	gtk_container_child_set_property(GTK_CONTAINER(gtk_widget_get_parent(widget)), widget, "expand", &value);
	if (!expanded) {
		// when the expander is explicitely closed (so all expanders are
		// closed now) we want to shrink the portmap window with
		// gtk_window_resize().
		// But GtkExpander uses a timer before the child is made
		// unvisible and a resize of the window is triggered.
		// So we defer resizing to the "check-resize"-signal handler
		p->monitored_expander_child = gtk_bin_get_child(GTK_BIN(widget));
	}
}

void PortMapWindow::response_cb(GtkWidget *widget, gint response_id, gpointer data)
{
	PortMapWindow& m = *(PortMapWindow*)data;
	gtk_check_menu_item_set_active(m.menuitem, FALSE);
}

void PortMapWindow::destroy_cb(GtkWidget*, gpointer data)
{
	delete (PortMapWindow*)data;
}

void PortMapWindow::toggle(GtkWidget* widget, gpointer data)
{
	if (!gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(data))) {
		if (window) {
			gtk_widget_destroy(window);
		}
	} else {
		if (!window) {
			new PortMapWindow(GTK_CHECK_MENU_ITEM(data));
		}
	}
}

gboolean PortMapWindow::redraw_expander(gpointer data)
{
	gtk_widget_queue_draw(GTK_WIDGET(data));
	return FALSE;
}

void PortMapWindow::on_cell_toggle(GtkCellRendererToggle *widget, gchar *path, gpointer data)
{
	PortSection *p = (PortSection*)data;

	GtkTreeIter iter;
	gtk_tree_model_get_iter_from_string(GTK_TREE_MODEL(p->treestore), &iter, path);
	gboolean v;
	const char *q1, *q2;
	gtk_tree_model_get(GTK_TREE_MODEL(p->treestore), &iter, 0, &q1, 1, &v, -1);
	string gcln;
	jack_client_t *gcl;
	if (p->port_attr->client_num == 0) {
		gcl = gx_jack::client;
		gcln = gx_jack::client_name;
	} else {
		gcl = gx_jack::client_insert;
		gcln = gx_jack::client_insert_name;
	}
	string s = gcln + ":" + p->port_attr->port_name;
    q2 = s.c_str();
    if (!p->port_attr->is_input) {
		const char *sw = q1;
		q1 = q2;
		q2 = sw;
	}

	v = !v;
	int ret;

    if (v) {
        ret = jack_connect(gcl, q1, q2);
    } else {
        ret = jack_disconnect(gcl, q1, q2);
    }

	if (ret != 0) {
		ostringstream buf;
		buf << "couldn't " << (v ? "" : "dis") << "connect " << q2 << " -> " << q1;
		gx_system::gx_print_error("port connection", buf.str());
		return;
	}
	gtk_tree_store_set(GTK_TREE_STORE(p->treestore), &iter, 1, v, -1);
	update_summary(p);
}


/*
** constuctor / destructor
*/

inline bool getnumber(gchararray p, long *pi)
{
	char *q;
	*pi = strtol(p, &q, 10);
	return !*q;
}

static gint sort_func(GtkTreeModel *model, GtkTreeIter *a, GtkTreeIter *b, gpointer user_data)
{
	gchararray pa, pb;
	gtk_tree_model_get(model, a, 0, &pa, -1);
	gtk_tree_model_get(model, b, 0, &pb, -1);
	int i = 0;
	for (; ; i++) {
		if (pa[i] != pb[i]) {
			break;
		}
		if (!pa[i]) {
			return 0;
		}
	}
	long ia, ib;
	if (getnumber(&pa[i],&ia) && getnumber(&pb[i],&ib)) {
		return ia - ib;
	}
	return strcmp(pa, pb);
}

void PortMapWindow::load(int sect, jack_port_t *jack_port)
{
    if (gx_jack::client) {
        const unsigned int max_items_unfolded = 1;
        PortSection& ps = portsection[sect];
        GtkTreeStore *tree = ps.treestore;
        assert(tree);
        assert(GTK_IS_TREE_STORE(tree));
        gtk_tree_sortable_set_sort_func(GTK_TREE_SORTABLE(tree), 0, sort_func, 0, 0);
        gtk_tree_sortable_set_sort_column_id(GTK_TREE_SORTABLE(tree), 0, GTK_SORT_ASCENDING);
        gtk_tree_store_clear(tree);
        const char **ports;
        jack_client_t *gcl = (ps.port_attr->client_num == 0 ? gx_jack::client : gx_jack::client_insert);
        ports = jack_get_ports(gcl, NULL, ps.port_attr->port_type,
                               (ps.port_attr->is_input ? JackPortIsOutput : JackPortIsInput));
        if (!ports) {
	        return;
        }
        const char** conn_ports = jack_port_get_connections(jack_port);
        ClientList cl(ports);
        // the following loop depends on the first 2 entries being client_name and client_insert_name
        int idx = 0;
        for (list<string>::iterator j = excluded_clients.begin(); j != excluded_clients.end(); j++, idx++) {
	        if (!ps.port_attr->is_insert || ps.port_attr->client_num != idx) {
		        cl.remove(*j);
	        }
        }
        GtkTreeIter iter, parent, *parentp;
        for (ClientList::iterator i = cl.begin(); i != cl.end(); i++) {
            ClientPortList *p = *i;
            if (cl.size() > 1 && p->ports.size() > max_items_unfolded) {
                gtk_tree_store_append(tree, &parent, 0);
                gtk_tree_store_set(tree, &parent,
                                    0, p->clientname().c_str(),
                                    1, false,
                                    2, false,
                                    -1);
                parentp = &parent;
            } else {
                parentp = 0;
            }
            for (list<const char*>::iterator j = p->ports.begin(); j != p->ports.end(); j++) {
                bool conn = false;
                if (conn_ports) {
                    for (const char** q = conn_ports; *q; q++) {
                        if (strcmp(*q, *j) == 0) {
                            conn = true;
                            break;
                        }
                    }
                }
                gtk_tree_store_append(tree, &iter, parentp);
                gtk_tree_store_set(tree, &iter,
                                    0, *j,
                                    1, conn,
                                    2, true,
                                    -1);
            }
        }
        free(conn_ports);
        free(ports);
        update_summary(&portsection[sect]);
    }
}

void PortMapWindow::load_all()
{
#define uslp() usleep(10); // prevents xruns?? (bug in jackd?)
	load(0, gx_jack::input_ports[0]);
	uslp();
	load(1, gx_jack::output_ports[2]);
	uslp();
	load(2, gx_jack::output_ports[3]);
	uslp();
	load(3, gx_jack::midi_input_port);
	uslp();
	load(4, gx_jack::midi_output_ports);
	uslp();
	load(5, gx_jack::input_ports[1]);
	uslp();
	load(6, gx_jack::output_ports[0]);
#undef uslp
}

PortMapWindow::PortMapWindow(GtkCheckMenuItem *item)
{
	monitored_expander_child = 0;
	menuitem = item;
	gtk_widget_ref(GTK_WIDGET(item));

	// order of first 2 entries is important (check load())
	excluded_clients.push_back(string(gx_jack::client_insert_name) + ":");
	excluded_clients.push_back(string(gx_jack::client_name) + ":");
	excluded_clients.push_back(string(gx_jack::client_instance) + "_meterbridge:");
	excluded_clients.push_back(string("jack_capture:"));

	GtkBuilder * builder = gtk_builder_new();
	window = load_toplevel(builder, "ports.glade", "PortMapWindow");
	gtk_window_set_icon(GTK_WINDOW (window), GDK_PIXBUF(ib));
	memset(portsection, 0, sizeof(portsection));
	for (int i = 0; i < number_of_ports; i++) {
		portsection[i].port_attr = &guitarix_ports[i];
		char name[30];
		snprintf(name, sizeof(name), "scrolledwindow%d", i+1);
		portsection[i].scrolled_window = GTK_SCROLLED_WINDOW(gtk_builder_get_object(builder, name));
		snprintf(name, sizeof(name), "treestore%d", i+1);
		portsection[i].treestore = GTK_TREE_STORE(gtk_builder_get_object(builder, name));
		snprintf(name, sizeof(name), "cellrenderertoggle%d", i+1);
		g_signal_connect(gtk_builder_get_object(builder, name), "toggled", G_CALLBACK(on_cell_toggle), &portsection[i]);
		snprintf(name, sizeof(name), "expander%d", i+1);
		GObject *w = gtk_builder_get_object(builder, name);
		if (w) {
			portsection[i].expander = GTK_EXPANDER(w);
			g_signal_connect_after(portsection[i].expander, "activate", G_CALLBACK(on_expander), this);
			snprintf(name, sizeof(name), "port%d", i+1);
			portsection[i].label = GTK_LABEL(gtk_builder_get_object(builder, name));
		}
	}

	load_all();

	g_signal_connect(window, "destroy", G_CALLBACK(destroy_cb), this);
	g_signal_connect(window, "response", G_CALLBACK(response_cb), this);
	gtk_window_add_accel_group(GTK_WINDOW(window),
	                           GxMainInterface::instance()->fAccelGroup);
	g_signal_connect_after(window, "check-resize", G_CALLBACK(on_check_resize), this);
	gtk_widget_show(window);
	g_object_unref(G_OBJECT(builder));
	instance = this;
}

// refresh portmap widget when connect/disconnect with jack server
void PortMapWindow::refresh()
{
    if(window) {
        if(!gx_jack::client) {
            for(int i = 0; i< number_of_ports;i++){
                PortSection& ps = portsection[i];
                GtkTreeStore *tree = ps.treestore;
                assert(tree);
                assert(GTK_IS_TREE_STORE(tree));
                gtk_tree_sortable_set_sort_func(GTK_TREE_SORTABLE(tree), 0, sort_func, 0, 0);
                gtk_tree_sortable_set_sort_column_id(GTK_TREE_SORTABLE(tree), 0, GTK_SORT_ASCENDING);
                gtk_tree_store_clear(tree);
                update_summary(&portsection[i]);
            }
        } else {
	        load_all();
        }
    }
}

PortMapWindow::~PortMapWindow()
{
	instance = 0;
	window = NULL;
	monitored_expander_child = 0;
	gtk_widget_unref(GTK_WIDGET(menuitem));
}

} // namespace gui
