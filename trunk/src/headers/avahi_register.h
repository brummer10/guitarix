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

#pragma once

#ifndef SRC_HEADERS_AVAHI_REGISTER_H_
#define SRC_HEADERS_AVAHI_REGISTER_H_

#include <string>
#include <avahi-gobject/ga-client.h>
#include <avahi-gobject/ga-entry-group.h>

class AvahiService {
private:
    GaClient *client;
    GaEntryGroup *group;
    std::string current_name;
    int registered_port;
    static void state_changed(GaEntryGroup *group, GaEntryGroupState state, void *data);
public:
    AvahiService();
    ~AvahiService();
    bool register_service(std::string name, int port);
};

#endif  // SRC_HEADERS_AVAHI_REGISTER_H_
