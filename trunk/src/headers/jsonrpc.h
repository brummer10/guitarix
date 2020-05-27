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
#include <bitset>
#include <queue>
#include <giomm/init.h>     // NOLINT
#include <giomm/socketservice.h>
#include "jsonrpc_methods.h"

class GxService;

class JsonValue {
protected:
    JsonValue() {}
    virtual ~JsonValue() {}
    friend class JsonArray;
public:
    virtual double getFloat() const;
    virtual int getInt() const;
    virtual const Glib::ustring& getString() const;
    virtual gx_system::JsonSubParser getSubParser() const;
};

class JsonArray: public std::vector<JsonValue*> {
public:
    JsonArray():std::vector<JsonValue*>() {}
    ~JsonArray();
    JsonValue *operator[](unsigned int i);
    void append(gx_system::JsonParser& jp);
};

class CmdConnection: public sigc::trackable {
public:
    struct methodnames {
	const char *name;
	jsonrpc_method m_id;
    };
    enum msg_type {
	f_preset_changed,
	f_state_changed,
	f_freq_changed,
	f_display,
	f_display_state,
	f_selection_done,
	f_presetlist_changed,
	f_log_message,
	f_midi_changed,
	f_midi_value_changed,
	f_parameter_change_notify,
	f_plugins_changed,
	f_misc_msg,
	f_units_changed,
	END_OF_FLAGS
    };
private:
    GxService& serv;
    Glib::RefPtr<Gio::SocketConnection> connection;
    std::list<std::string> outgoing;
    unsigned int current_offset;
    gx_system::JsonStringParser jp;
    bool midi_config_mode;
    std::bitset<END_OF_FLAGS> flags;
    std::map<string,float> maxlevel;
private:
    bool find_token(const Glib::ustring& token, msg_type *start, msg_type *end);
    void activate(int n, bool v) { flags.set(n, v); }
    void exec(Glib::ustring cmd);
    void call(gx_system::JsonWriter& jw, const methodnames *mn, JsonArray& params);
    void notify(gx_system::JsonStringWriter& jw, const methodnames *mn, JsonArray& params);
    bool request(gx_system::JsonStringParser& jp, gx_system::JsonStringWriter& jw, bool batch_start);
    void write_error(gx_system::JsonWriter& jw, int code, const char *message);
    void write_error(gx_system::JsonWriter& jw, int code, Glib::ustring& message) { write_error(jw, code, message.c_str()); }
    void error_response(gx_system::JsonWriter& jw, int code, const char *message);
    void error_response(gx_system::JsonWriter& jw, int code, const Glib::ustring& message) { error_response(jw, code, message.c_str()); }
    void send_notify_begin(gx_system::JsonStringWriter& jw, const char *method) { jw.send_notify_begin(method); }
    void send_notify_end(gx_system::JsonStringWriter& jw, bool send_out=true);
    void listen(const Glib::ustring& tp);
    void unlisten(const Glib::ustring& tp);
    void process(gx_system::JsonStringParser& jp);

public:
    CmdConnection(GxService& serv, const Glib::RefPtr<Gio::SocketConnection>& connection_);
    ~CmdConnection();
    bool on_data_in(Glib::IOCondition cond);
    bool on_data_out(Glib::IOCondition cond);
    void send(gx_system::JsonStringWriter& jw);
    bool is_activated(msg_type n) { return flags[n]; }
    void update_maxlevel(const std::string& id, float v) { float& m = maxlevel[id]; m = max(m, v); }
    friend class UiBuilderVirt;
};

struct broadcast_data {
    gx_system::JsonStringWriter *jw;
    CmdConnection::msg_type n;
    CmdConnection *sender;
};

class GxService: public Gio::SocketService {
private:
    struct ChangedPlugin {
	std::string id;
	gx_engine::PluginChange::pc status;
	ChangedPlugin(const std::string& id_, gx_engine::PluginChange::pc status_): id(id_), status(status_) {}
    };
private:
    gx_preset::GxSettings& settings;
    gx_jack::GxJack& jack;
    TunerSwitcher& tuner_switcher;
    sigc::slot<void> quit_mainloop;
    time_t oldest_unsaved;
    time_t last_change;
    sigc::connection save_conn;
    std::list<CmdConnection*> connection_list;
    std::queue<broadcast_data> broadcast_list;
    gx_system::JsonStringWriter *jwc;
    std::map<std::string,bool> *preg_map;
    std::map<std::string,float> maxlevel;
private:
    virtual bool on_incoming(const Glib::RefPtr<Gio::SocketConnection>& connection,
			     const Glib::RefPtr<Glib::Object>& source_object);
    void save_state();
    void remove_connection(CmdConnection* p);
    bool broadcast_listeners(CmdConnection::msg_type n, CmdConnection *sender = 0);
    void broadcast(gx_system::JsonStringWriter& jw, CmdConnection::msg_type n, CmdConnection *sender = 0);
    bool idle_broadcast_handler();
    void connect_value_changed_signal(gx_engine::Parameter *p);

    // message formatting functions
    void serialize_parameter_change(gx_system::JsonWriter& jw);
    void ladspaloader_write_changes(gx_system::JsonWriter& jw, std::vector<ChangedPlugin>& changed_plugins);

    // signal handler
    void on_param_insert_remove(gx_engine::Parameter *p, bool insert);
    void on_param_value_changed(gx_engine::Parameter *p);
    void preset_changed();
    void on_engine_state_change(gx_engine::GxEngineState state);
    void on_tuner_freq_changed();
    void display(const Glib::ustring& bank, const Glib::ustring& preset);
    void set_display_state(TunerSwitcher::SwitcherState newstate);
    void on_selection_done(bool v);
    void on_presetlist_changed();
    void on_log_message(const string& msg, GxLogger::MsgType tp, bool plugged);
    void on_midi_changed();
    void on_midi_value_changed(int ctl, int value);
    void on_rack_unit_changed(bool stereo);
    static void add_changed_plugin(gx_engine::Plugin* pl, gx_engine::PluginChange::pc v,
				   std::vector<ChangedPlugin>& vec);
    void create_bluetooth_sockets(const Glib::ustring& host);

    friend class CmdConnection;
public:
    GxService(gx_preset::GxSettings& settings_, gx_jack::GxJack& jack_,
	      TunerSwitcher& tunerswitcher, sigc::slot<void> quit_mainloop_,
	      const Glib::ustring& host, int *port);
    ~GxService();
    void send_rack_changed(bool stereo, CmdConnection *cmd);
    void ladspaloader_update_plugins(gx_system::JsonWriter *jw, CmdConnection *cmd);
    float update_maxlevel(const std::string& id, bool reset=false);
};

const char *engine_state_to_string(gx_engine::GxEngineState s);
gx_engine::GxEngineState string_to_engine_state(const std::string& s);

#endif // SRC_HEADERS_JSONRPC_H_
