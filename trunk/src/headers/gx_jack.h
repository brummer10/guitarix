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

/* ------- This is the JACK namespace ------- */

#pragma once

#ifndef SRC_HEADERS_GX_JACK_H_
#define SRC_HEADERS_GX_JACK_H_

/* On Intel set FZ (Flush to Zero) and DAZ (Denormals Are Zero)
   flags to avoid costly denormals */
#ifdef __SSE__
#include <xmmintrin.h>
#ifdef __SSE2__
#define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8040)
#else
#define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8000)
#endif
#else
#define AVOIDDENORMALS
#endif

#include <jack/jack.h>          // NOLINT
#include <jack/midiport.h>
#include <jack/ringbuffer.h>

#ifdef HAVE_JACK_SESSION
#include <jack/session.h>
#endif

namespace gx_jack {

/****************************************************************
 ** port connection callback
 */

struct PortConnData {
public:
    PortConnData() {} // no init
    PortConnData(const char *a, const char *b, bool conn)
	: name_a(a), name_b(b), connect(conn) {}
    ~PortConnData() {}
    const char *name_a;
    const char *name_b;
    bool connect;
};

class PortConnRing {
private:
    jack_ringbuffer_t *ring;
    bool send_changes;
    int overflow;  // should be bool but gives compiler error
    void set_overflow() { gx_system::atomic_set(&overflow, true); }
    void clear_overflow()  { gx_system::atomic_set(&overflow, false); }
    bool is_overflow() { return gx_system::atomic_get(overflow); }
public:
    Glib::Dispatcher new_data;
    Glib::Dispatcher portchange;
    void push(const char *a, const char *b, bool conn);
    bool pop(PortConnData*);
    void set_send(bool v) { send_changes = v; }
    PortConnRing();
    ~PortConnRing();
};


/****************************************************************
 ** class GxJack
 */

class PortConnection {
public:
    jack_port_t *port;
    list<string> conn;
};

class JackPorts {
public:
    PortConnection input;
    PortConnection midi_input;
    PortConnection insert_out;
    PortConnection midi_output;
    PortConnection insert_in;
    PortConnection output1;
    PortConnection output2;
};

#ifdef HAVE_JACK_SESSION
extern "C" {
    typedef int (*jack_set_session_callback_type)(
	jack_client_t *, JackSessionCallback, void *arg);
    typedef char *(*jack_get_uuid_for_client_name_type)(
	jack_client_t *, const char *);
    typedef char *(*jack_client_get_uuid_type)(jack_client_t *);
}
#endif

class GxJack: public sigc::trackable {
 private:
    gx_engine::GxEngine& engine;
    bool                jack_is_down;
    bool                jack_is_exit;
    static int          gx_jack_srate_callback(jack_nframes_t, void* arg);
    static int          gx_jack_xrun_callback(void* arg);
    static int          gx_jack_buffersize_callback(jack_nframes_t, void* arg);
    static int          gx_jack_process(jack_nframes_t, void* arg);
    static int          gx_jack_insert_process(jack_nframes_t, void* arg);

    static void         shutdown_callback_client(void* arg);
    static void         shutdown_callback_client_insert(void* arg);
    void                gx_jack_shutdown_callback();
    static void         gx_jack_portreg_callback(jack_port_id_t, int, void* arg);
    static void         gx_jack_portconn_callback(jack_port_id_t a, jack_port_id_t b, int connect, void* arg);
#ifdef HAVE_JACK_SESSION
    jack_session_event_t *session_event;
    jack_session_event_t *session_event_ins;
    int                 session_callback_seen;
    static void         gx_jack_session_callback(jack_session_event_t *event, void *arg);
    static void         gx_jack_session_callback_ins(jack_session_event_t *event, void *arg);
    static jack_set_session_callback_type jack_set_session_callback_fp;
    static jack_get_uuid_for_client_name_type jack_get_uuid_for_client_name_fp;
    static jack_client_get_uuid_type jack_client_get_uuid_fp;
#endif
    void                cleanup_slot(bool otherthread);
    void                fetch_connection_data();
    PortConnRing        connection_queue;
    sigc::signal<void,string,string,bool> connection_changed;
    Glib::Dispatcher    buffersize_change;

    sigc::signal<void>  client_change;
    string              client_instance;
    jack_nframes_t      jack_sr;   // jack sample rate
    jack_nframes_t      jack_bs;   // jack buffer size
    float               last_xrun;
    void write_jack_port_connections(
	gx_system::JsonWriter& w, const char *key, const PortConnection& pc);
    bool                gx_jack_init();
    void                gx_jack_init_port_connection();
    void                gx_jack_callbacks();
    void                gx_jack_cleanup();

 public:
    JackPorts           ports;

    jack_client_t*      client;
    jack_client_t*      client_insert;

    jack_nframes_t      get_jack_sr() { return jack_sr; }
    jack_nframes_t      get_jack_bs() { return jack_bs; }
    float               get_jcpu_load() { return client ? jack_cpu_load(client) : -1; }
    bool                get_is_rt() { return client ? jack_is_realtime(client) : false; }
    jack_nframes_t      get_time_is() { return client ? jack_frame_time(client) : 0; }

public:
    GxJack(gx_engine::GxEngine& engine_);
    ~GxJack();

    void                set_jack_down(bool v) { jack_is_down = v; }
    void                set_jack_exit(bool v) { jack_is_exit = v; }

    bool                gx_jack_connection(bool connect);
    float               get_last_xrun() { return last_xrun; }
    void*               get_midi_buffer(jack_nframes_t nframes);

    void                read_connections(gx_system::JsonParser& jp);
    void                write_connections(gx_system::JsonWriter& w);
    void                clear_insert_connections();
    static string       get_default_instancename();
    const string&       get_instancename() { return client_instance; }
    string              client_name;
    string              client_insert_name;
    Glib::Dispatcher    xrun;
    Glib::Dispatcher    session;
    Glib::Dispatcher    session_ins;
    Glib::Dispatcher    shutdown;
    bool                is_jack_down() { return jack_is_down; }
    Glib::Dispatcher    connection;
    bool                is_jack_exit() { return jack_is_exit; }
    sigc::signal<void>& signal_client_change() { return client_change; }
    sigc::signal<void,string,string,bool>& signal_connection_changed() { return connection_changed; }
    Glib::Dispatcher&   signal_portchange() { return connection_queue.portchange; }
    Glib::Dispatcher&   signal_buffersize_change() { return buffersize_change; }
    void                send_connection_changes(bool v) { connection_queue.set_send(v); }

#ifdef HAVE_JACK_SESSION
    jack_session_event_t *get_last_session_event() {
	return gx_system::atomic_get(session_event);
    }
    jack_session_event_t *get_last_session_event_ins() {
	return gx_system::atomic_get(session_event_ins);
    }
    int                 return_last_session_event();
    int                 return_last_session_event_ins();
    string              get_uuid_insert();
#endif
};

} /* end of jack namespace */

#endif  // SRC_HEADERS_GX_JACK_H_
