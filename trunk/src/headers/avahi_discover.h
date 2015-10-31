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

#pragma once

#ifndef SRC_HEADERS_AVAHI_DISCOVER_H_
#define SRC_HEADERS_AVAHI_DISCOVER_H_

#include "guitarix.h"
#include <avahi-gobject/ga-client.h>
#include <avahi-gobject/ga-service-browser.h>
#include <avahi-gobject/ga-service-resolver.h>

class AvahiBrowser {
public:
    struct Entry {
	AvahiIfIndex interface;
	AvahiProtocol protocol;
	Glib::ustring name;
	std::string type;
	std::string domain;
	AvahiLookupResultFlags flags;
	Entry() {}
	Entry(AvahiIfIndex interface_, AvahiProtocol protocol_, const char *name_,
	      const char *type_, const char *domain_, AvahiLookupResultFlags flags_)
	    : interface(interface_), protocol(protocol_), name(name_), type(type_),
	      domain(domain_), flags(flags_) {}
	bool operator==(const Entry& e) const {
	    return interface == e.interface && protocol == e.protocol && name == e.name
		&& type == e.type && domain == e.domain;
	}
    };
private:
    GaClient *client;
    GaServiceBrowser *browser;
    GaServiceResolver *resolver;
    std::list<Entry> services;
    std::map<Glib::ustring,int> service_names;
    sigc::signal<void> changed;
    bool cache_done;
    Glib::ustring found_name;
    Glib::ustring found_host;
    static void new_service(
	GaServiceBrowser *browser, AvahiIfIndex interface, AvahiProtocol protocol,
	const char *name, const char *type, const char *domain, AvahiLookupResultFlags flags, void *data);
    static void removed_service(
	GaServiceBrowser *browser, AvahiIfIndex interface, AvahiProtocol protocol,
	const char *name, const char *type, const char *domain, AvahiLookupResultFlags flags, void *data);
    static void cache_exhausted(GaServiceBrowser *browser, void *data);
    static void on_found(GaServiceResolver *resolver, AvahiIfIndex interface, AvahiProtocol protocol,
			 const char *name, const char *type, const char *domain, const char *host_name,
			 const AvahiAddress * a, uint16_t port, AvahiStringList * txt,
			 AvahiLookupResultFlags flags, void *data);
    static void on_failure(GaServiceResolver *resolver, GError *error, void *data);
public:
    AvahiBrowser();
    ~AvahiBrowser();
    sigc::signal<void>& signal_changed() { return changed; }
    void get_service_names(std::vector<Glib::ustring>& r);
    bool invoke_resolver(const Glib::ustring& name);
    bool get_address_port(Glib::ustring& address, int& port, Glib::ustring& name, Glib::ustring& host);
};

class SelectInstance {
private:
    Gtk::Window *splash;
    Gtk::Dialog *win;
    Gtk::TreeView *view;
    AvahiBrowser av;
    class ModelColumns: public Gtk::TreeModelColumnRecord {
    public:
	Gtk::TreeModelColumn<Glib::ustring> name;
	ModelColumns() { add(name); }
    } cols;
private:
    void on_response(int response_id);
    void on_row(const Gtk::TreePath& path, Gtk::TreeViewColumn* column);
    void on_avahi_changed();
    void on_selection_changed();
public:
    SelectInstance(gx_system::CmdlineOptions& options, Gtk::Window  *splash);
    ~SelectInstance();
    bool get_address_port(Glib::ustring& address, int& port, Glib::ustring& name, Glib::ustring& host)
	{ return av.get_address_port(address, port, name, host); }
};

#endif  // SRC_HEADERS_AVAHI_DISCOVER_H_
