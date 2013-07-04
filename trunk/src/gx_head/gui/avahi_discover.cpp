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

#include "avahi_discover.h"

/****************************************************************
 ** class AvahiBrowser
 */

AvahiBrowser::AvahiBrowser()
    : client(0),
      browser(0),
      resolver(0),
      services(),
      service_names(),
      changed(),
      cache_done(false),
      address(),
      port(0),
      found_name(),
      found_host() {
    client = ga_client_new(GaClientFlags(0));
    GError *error = 0;
    if (!ga_client_start(client, &error)) {
	cerr << "error" << endl;
    }
    browser = ga_service_browser_new("_guitarix._tcp");
    ga_service_browser_attach(browser, client, &error);
    g_signal_connect(browser, "new-service", G_CALLBACK(new_service), this);
    g_signal_connect(browser, "removed-service", G_CALLBACK(removed_service), this);
    g_signal_connect(browser, "cache-exhausted", G_CALLBACK(cache_exhausted), this);
}

AvahiBrowser::~AvahiBrowser() {
    if (resolver) {
	g_object_unref(resolver);
    }
    if (browser) {
	g_object_unref(browser);
    }
    if (client) {
	g_object_unref(client);
    }
}

static inline std::ostream& operator<<(std::ostream& o, const AvahiBrowser::Entry& e) {
    o << "<" << e.interface << ", " << e.protocol << ", " << e.name << ", " << e.type << ", " << e.domain << ", " << e.flags << ">";
    return o;
}

bool AvahiBrowser::get_address_port(Glib::ustring& address, int& port, Glib::ustring& name, Glib::ustring& host) {
    AvahiAddress a = AvahiAddress();
    uint16_t p = uint16_t();
    if (resolver && ga_service_resolver_get_address(resolver, &a, &p)) {
	char buf[AVAHI_ADDRESS_STR_MAX];
	address = avahi_address_snprint(buf, AVAHI_ADDRESS_STR_MAX, &a);
	port = p;
	name = found_name;
	host = found_host;
	return true;
    }
    return false;
}

void AvahiBrowser::get_service_names(std::vector<Glib::ustring>& r) {
    for (std::map<Glib::ustring,int>::iterator i = service_names.begin(); i != service_names.end(); ++i) {
	r.push_back(i->first);
    }
}

bool AvahiBrowser::invoke_resolver(const Glib::ustring& name) {
    AvahiProtocol protocol = AVAHI_PROTO_UNSPEC;
    AvahiIfIndex interface = AVAHI_IF_UNSPEC;
    Entry *e = 0;
    for (std::list<Entry>::iterator i = services.begin(); i != services.end(); ++i) {
	if (i->name != name) {
	    continue;
	}
	if (i->protocol < protocol) {
	    continue;
	}
	if (i->interface < interface) {
	    continue;
	}
	e = &(*i);
    }
    if (!e) {
	return false;
    }
    assert(!resolver);
    resolver = ga_service_resolver_new(
	e->interface, e->protocol, e->name.c_str(), e->type.c_str(), e->domain.c_str(), e->protocol, GA_LOOKUP_NO_FLAGS);
    g_signal_connect(resolver, "found", G_CALLBACK(on_found), this);
    g_signal_connect(resolver, "failure", G_CALLBACK(on_failure), this);
    GError *error = 0;
    ga_service_resolver_attach(resolver, client, &error);
    return true;
}

//static
void AvahiBrowser::new_service(
    GaServiceBrowser *browser, AvahiIfIndex interface, AvahiProtocol protocol,
    const char *name, const char *type, const char *domain, AvahiLookupResultFlags flags, void *data) {
    AvahiBrowser& self = *static_cast<AvahiBrowser*>(data);
    self.services.push_back(Entry(interface,protocol,name,type,domain,flags));
    if (self.service_names.find(name) == self.service_names.end()) {
	self.service_names[name] = 1;
	if (self.cache_done) {
	    self.changed();
	}
    } else {
	self.service_names[name] += 1;
    }
}

//static
void AvahiBrowser::removed_service(
    GaServiceBrowser *browser, AvahiIfIndex interface, AvahiProtocol protocol,
    const char *name, const char *type, const char *domain, AvahiLookupResultFlags flags, void *data) {
    AvahiBrowser& self = *static_cast<AvahiBrowser*>(data);
    Entry e(interface,protocol,name,type,domain,flags);
    for (std::list<Entry>::iterator i = self.services.begin(); i != self.services.end(); ++i) {
	if (*i == e) {
	    self.services.erase(i);
	    self.service_names[name] -= 1;
	    if (self.service_names[name] <= 0) {
		self.service_names.erase(name);
		if (self.cache_done) {
		    self.changed();
		}
	    }
	    break;
	}
    }
}

//static
void AvahiBrowser::cache_exhausted(GaServiceBrowser *browser, void *data) {
    AvahiBrowser& self = *static_cast<AvahiBrowser*>(data);
    self.cache_done = true;
    self.changed();
}

//static
void AvahiBrowser::on_found(
    GaServiceResolver *resolver, AvahiIfIndex interface, AvahiProtocol protocol,
    const char *name, const char *type, const char *domain, const char *host_name,
    const AvahiAddress * a, uint16_t port, AvahiStringList * txt,
    AvahiLookupResultFlags flags, void *data) {
    AvahiBrowser& self = *static_cast<AvahiBrowser*>(data);
    self.found_name = name;
    self.found_host = host_name;
    Gtk::Main::quit();
}

//static
void AvahiBrowser::on_failure(GaServiceResolver *resolver, GError *error, void *data) {
    Gtk::Main::quit();
}

/****************************************************************
 ** class SelectInstance
 */

SelectInstance::SelectInstance(gx_system::CmdlineOptions& options, Gtk::Window *splash_)
    : splash(splash_),
      win(0),
      view(0),
      av(),
      cols() {
    Glib::RefPtr<gx_gui::GxBuilder> bld = gx_gui::GxBuilder::create_from_file(
	options.get_builder_filepath("selectinstance.glade"));
    bld->get_toplevel("SelectInstance", win);
    win->signal_response().connect(sigc::mem_fun(this, &SelectInstance::on_response));
    bld->get_widget("treeview", view);
    view->signal_row_activated().connect(
	sigc::group(sigc::mem_fun(win, &Gtk::Dialog::response), 1));
    view->set_model(Gtk::ListStore::create(cols));
    view->get_selection()->set_mode(Gtk::SELECTION_BROWSE);
    view->get_selection()->signal_changed().connect(
	sigc::mem_fun(this, &SelectInstance::on_selection_changed));
    av.signal_changed().connect(sigc::mem_fun(this, &SelectInstance::on_avahi_changed));
    Gtk::Main::run();
};

SelectInstance::~SelectInstance() {
    delete win;
}

void SelectInstance::on_selection_changed() {
    win->get_widget_for_response(1)->set_sensitive(view->get_selection()->get_selected());
}

void SelectInstance::on_avahi_changed() {
    std::vector<Glib::ustring> r;
    av.get_service_names(r);
    if (!win->is_visible()) {
	if (r.size() == 1) {
	    av.invoke_resolver(*r.begin());
	} else {
	    if (splash) {
		splash->hide();
	    }
	    win->show();
	}
    }
    Glib::RefPtr<Gtk::ListStore> ls = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(view->get_model());
    Gtk::TreeIter s = view->get_selection()->get_selected();
    Glib::ustring old;
    if (s) {
	old = s->get_value(cols.name);
    }
    ls->clear();
    for (std::vector<Glib::ustring>::iterator i = r.begin(); i != r.end(); ++i) {
	Gtk::TreeIter j = ls->append();
	j->set_value(cols.name, *i);
	if (old.empty()) {
	    old = *i;
	}
	if (old == *i) {
	    view->get_selection()->select(j);
	}
    }
}

void SelectInstance::on_response(int response_id) {
    if (response_id == 1) {
	Gtk::TreeIter i = view->get_selection()->get_selected();
	if (!i) {
	    return;
	}
	av.invoke_resolver(i->get_value(cols.name));
	return;
    }
    Gtk::Main::quit();
}
