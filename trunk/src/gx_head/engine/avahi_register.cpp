/*
 * Copyright (C) 2013 Andreas Degert
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

#include <avahi-common/error.h>
#include <avahi-common/alternative.h>
#include <avahi-common/malloc.h>
#include "avahi_register.h"
#include "gx_logging.h"

/****************************************************************
 ** class AvahiService
 */

AvahiService::AvahiService()
    : client(0), group(0), current_name(), registered_port(-1) {
    client = ga_client_new(GaClientFlags(0));
    GError *error = 0;
    if (!ga_client_start(client, &error)) {
	gx_print_error("avahi registration", error->message);
	return;
    }
    group = ga_entry_group_new();
    g_signal_connect(group, "state-changed", G_CALLBACK(state_changed), this);
    error = 0;
    ga_entry_group_attach(group, client, &error);
}

AvahiService::~AvahiService() {
    if (client) {
	g_object_unref(client);
    }
    if (group) {
	g_object_unref(group);
    }
}

//static
void AvahiService::state_changed(GaEntryGroup *group, GaEntryGroupState state, void *data) {
    AvahiService& self = *static_cast<AvahiService*>(data);
    switch (state) {
    case GA_ENTRY_GROUP_STATE_UNCOMMITED: break;
    case GA_ENTRY_GROUP_STATE_REGISTERING: break;
    case GA_ENTRY_GROUP_STATE_ESTABLISHED:
	gx_print_info("avahi registration", "established");
	break;
    case GA_ENTRY_GROUP_STATE_COLLISTION: { // typo in header??
	gx_print_info("avahi registration", "collision");
	char *n = avahi_alternative_service_name(self.current_name.c_str());
	std::string name = n;
	avahi_free(n);
	self.register_service(name, self.registered_port);
	break;
    }
    case GA_ENTRY_GROUP_STATE_FAILURE:
	gx_print_error("avahi registration", "failure");
	break;
    }
}

bool AvahiService::register_service(std::string name, int port) {
    if (!group) {
	return false;
    }
    for (int i = 0; i < 10; ++i) {
	GError *error = 0;
	ga_entry_group_add_service(group, name.c_str(), "_guitarix._tcp", port, &error, 0);
	if (!error) {
	    break;
	}
	if (error->code != AVAHI_ERR_COLLISION) {
	    gx_print_error("avahi registration", error->message);
	    return false;
	}
	char *n = avahi_alternative_service_name(name.c_str());
	name = n;
	avahi_free(n);
    }
    ga_entry_group_commit(group, 0);
    current_name = name;
    registered_port = port;
    return true;
}
