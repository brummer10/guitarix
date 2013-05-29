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
 */

#pragma once

#ifndef SRC_HEADERS_JSONRPC_H_
#define SRC_HEADERS_JSONRPC_H_

#include "engine.h"
#include <giomm/init.h>     // NOLINT
#include <giomm/socketservice.h>

class MyService: public Gio::SocketService {
private:
    gx_preset::GxSettings& settings;
    gx_jack::GxJack& jack;
    sigc::slot<void> quit_mainloop;
    TunerSwitcher tuner_switcher;
    gx_ui::UiSignal<bool> switcher_signal;
    time_t oldest_unsaved;
    time_t last_change;
    sigc::connection save_conn;
    virtual bool on_incoming(const Glib::RefPtr<Gio::SocketConnection>& connection,
			     const Glib::RefPtr<Glib::Object>& source_object);
    void on_switcher_toggled(bool v);
    void on_selection_done();
    void save_state();
    friend class CmdConnection;
public:
    MyService(gx_preset::GxSettings& settings_, gx_jack::GxJack& jack_,
	      sigc::slot<void> quit_mainloop_, int port);
    ~MyService() {}
};

#endif // SRC_HEADERS_JSONRPC_H_
