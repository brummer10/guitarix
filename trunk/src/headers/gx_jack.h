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
#include <semaphore.h>

#ifdef HAVE_JACK_SESSION
#include <jack/session.h>
#endif

#include <string>

namespace gx_jack {

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

class GxJack {
 private:
    bool                gx_start_jack_dialog();
    gx_engine::GxEngine& engine;
    bool                jack_is_down;
    bool                jack_is_exit;
    static int          gx_jack_srate_callback(jack_nframes_t, void* arg);
    static int          gx_jack_xrun_callback(void* arg);
    static int          gx_jack_buffersize_callback(jack_nframes_t, void* arg);
    static int          gx_jack_process(jack_nframes_t, void* arg);
    static int          gx_jack_insert_process(jack_nframes_t, void* arg);

    static void         gx_jack_shutdown_callback(void* arg);
    static void         gx_jack_portreg_callback(jack_port_id_t, int, void* arg);
    static void         gx_jack_portconn_callback(jack_port_id_t a, jack_port_id_t b, int connect, void* arg);
#ifdef HAVE_JACK_SESSION
    jack_session_event_t *session_event;
    static void         gx_jack_session_callback(jack_session_event_t *event, void *arg);
#endif
    sigc::signal<void>  client_change;
    string              client_instance;
 public:
    JackPorts           ports;
    jack_nframes_t      jack_sr;   // jack sample rate
    jack_nframes_t      jack_bs;   // jack buffer size
    jack_nframes_t      time_is;

    jack_client_t*      client;
    jack_client_t*      client_insert;

    float               jcpu_load; // jack cpu_load

    int                 is_rt;
    void                cleanup_slot(bool otherthread);
public:
    GxJack(gx_engine::GxEngine& engine_);
    ~GxJack();

    void                set_jack_down(bool);
    void                set_jack_exit(bool);

    bool                gx_jack_init( );
    
    void                gx_jack_connection(bool connect);
    float               get_last_xrun();
    void*               get_midi_buffer(jack_nframes_t nframes);

    void                gx_jack_init_port_connection();
    void                read_connections(gx_system::JsonParser& jp);
    void                write_connections(gx_system::JsonWriter& w);
    void                gx_jack_callbacks();
    void                gx_jack_cleanup();
    static string       get_default_instancename();
    const string&       get_instancename() { return client_instance; }
    string              client_name;
    string              client_insert_name;
    Glib::Dispatcher    xrun;
    Glib::Dispatcher    portchange;
    Glib::Dispatcher    session;
    Glib::Dispatcher    shutdown;
    bool                is_jack_down() { return jack_is_down; }
    Glib::Dispatcher    connection;
    bool                is_jack_exit() { return jack_is_exit; }
    sigc::signal<void>  signal_client_change() { return client_change; }
#ifdef HAVE_JACK_SESSION
    jack_session_event_t *get_last_session_event() {
	return static_cast<jack_session_event_t *>g_atomic_pointer_get(&session_event);
    }
    void                return_last_session_event();
    string              get_uuid_insert();
#endif
};

} /* end of jack namespace */

#endif  // SRC_HEADERS_GX_JACK_H_
