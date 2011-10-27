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
 *
 *  This is the gx_head interface to the jackd audio / midi server
 *
 * --------------------------------------------------------------------------
 */

#include <errno.h>              // NOLINT
#include <jack/statistics.h>    // NOLINT
#include <jack/jack.h>          // NOLINT
#include <jack/thread.h>        // NOLINT

#ifdef HAVE_JACK_SESSION
#include <jack/session.h>      // NOLINT
#endif

#include "engine.h"           // NOLINT


namespace gx_jack {

/****************************************************************
 ** class GxJack
 ****************************************************************/

static const char *jack_amp_postfix = "_amp";
static const char *jack_fx_postfix = "_fx";

string GxJack::get_default_instancename() {
    static const char *default_jack_instancename = "gx_head";
    return default_jack_instancename;
}

/****************************************************************
 ** GxJack ctor, dtor
 */

GxJack::GxJack(gx_engine::GxEngine& engine_)
    : engine(engine_),
      jack_is_down(false),
      jack_is_exit(true),
#ifdef HAVE_JACK_SESSION
      session_event(0),
#endif
      client_change(),
      client_instance(),
      jack_sr(),
      jack_bs(),
      ports(),
      client(0),
      client_insert(0),
      client_name(),
      client_insert_name(),
      xrun() {
    connection_queue.new_data.connect(sigc::mem_fun(*this, &GxJack::fetch_connection_data));
}

GxJack::~GxJack() {
    gx_jack_cleanup();
}

/****************************************************************
 ** load state, save state
 */

void GxJack::read_connections(gx_system::JsonParser& jp) {
    jp.next(gx_system::JsonParser::begin_object);
    while (jp.peek() == gx_system::JsonParser::value_key) {
        list<string> *i;
        jp.next(gx_system::JsonParser::value_key);
        if (jp.current_value() == "input") {
            i = &ports.input.conn;
        } else if (jp.current_value() == "output1") {
            i = &ports.output1.conn;
        } else if (jp.current_value() == "output2") {
            i = &ports.output2.conn;
        } else if (jp.current_value() == "midi_input") {
            i = &ports.midi_input.conn;
        } else if (jp.current_value() == "midi_output") {
            i = &ports.midi_output.conn;
        } else if (jp.current_value() == "insert_out") {
            i = &ports.insert_out.conn;
        } else if (jp.current_value() == "insert_in") {
            i = &ports.insert_in.conn;
        } else {
	    gx_system::gx_print_warning(
		_("recall state"),
		_("unknown jack ports section: ") + jp.current_value());
            jp.skip_object();
            continue;
        }
        jp.next(gx_system::JsonParser::begin_array);
        while (jp.peek() == gx_system::JsonParser::value_string) {
            jp.next();
            i->push_back(jp.current_value());
        }
        jp.next(gx_system::JsonParser::end_array);
    }
    jp.next(gx_system::JsonParser::end_object);
}

void GxJack::write_jack_port_connections(
    gx_system::JsonWriter& w, const char *key, const PortConnection& pc) {
    w.write_key(key);
    w.begin_array();
    if (client) {
	const char** pl = jack_port_get_connections(pc.port);
	if (pl) {
	    for (const char **p = pl; *p; p++) {
		w.write(*p);
	    }
	    free(pl);
	}
    } else {
	for (list<string>::const_iterator i = pc.conn.begin(); i != pc.conn.end(); ++i) {
	    w.write(*i);
	}
    }
    w.end_array(true);
}

void GxJack::write_connections(gx_system::JsonWriter& w) {
    w.begin_object(true);
    write_jack_port_connections(w, "input", ports.input);
    write_jack_port_connections(w, "output1", ports.output1);
    write_jack_port_connections(w, "output2", ports.output2);
    write_jack_port_connections(w, "midi_input", ports.midi_input);
    write_jack_port_connections(w, "midi_output", ports.midi_output);
    write_jack_port_connections(w, "insert_out", ports.insert_out);
    write_jack_port_connections(w, "insert_in", ports.insert_in);
    w.end_object(true);
}


/****************************************************************
 ** client connection init and cleanup
 */

// ----- pop up a dialog for starting jack
bool GxJack::gx_jack_init() {
    AVOIDDENORMALS;
    int jackopt = JackNoStartServer;
    gx_system::CmdlineOptions& opt = gx_system::get_options();
    client_instance = opt.get_jack_instancename();
    if (client_instance.empty()) {
	client_instance = get_default_instancename();
    } else {
	jackopt |= JackUseExactName;
    }
    client_name =        client_instance + jack_amp_postfix;
    client_insert_name = client_instance + jack_fx_postfix;

    set_jack_down(false);
    set_jack_exit(true);
    engine.set_stateflag(gx_engine::GxEngine::SF_INITIALIZING);

    //ports = JackPorts(); //FIXME

    jack_status_t jackstat;
#ifdef HAVE_JACK_SESSION
    // try to open jack gxjack.client
    if (!opt.get_jack_uuid().empty()) {
        client = jack_client_open(
	    client_name.c_str(), JackOptions(jackopt | JackSessionID),
	    &jackstat, opt.get_jack_uuid().c_str());
    } else {
        client = jack_client_open(client_name.c_str(), JackOptions(jackopt), &jackstat);
    }
    // ----- only start the insert gxjack.client when the amp gxjack.client is true
    if (client) {
        if (!opt.get_jack_uuid2().empty()) {
            client_insert = jack_client_open(
		client_insert_name.c_str(),
		JackOptions(jackopt | JackSessionID),
		&jackstat, opt.get_jack_uuid2().c_str());
        } else {
            client_insert = jack_client_open(client_insert_name.c_str(),
					     JackOptions(jackopt), &jackstat);
        }
    }
#else
    client = jack_client_open(client_name.c_str(), jack_option_t(jackopt), &jackstat);
     // ----- only start the insert gxjack.client when the amp gxjack.client is true
    if (client) {
        client_insert = jack_client_open(client_insert_name.c_str(),
					 JackOptions(jackopt), &jackstat);
    }
#endif

    if (client == 0) {
	if (jackstat & JackServerFailed) {
	    return false;
	} else if ((jackstat & JackServerError) && (jackopt & JackUseExactName)) {
	    gx_system::gx_print_fatal(
		_("Jack Init"),
		boost::format(_("can't get requested jack instance name '%1%'"))
		% client_instance);
	} else {
	    gx_system::gx_print_fatal(
		_("Jack Init"),
		_("unknown jack server communication error"));
	}
    }

    // ----------------------------------
    set_jack_down(false);

    // it is maybe not the 1st gx_head instance ?
    if (jackstat & JackNameNotUnique) {
	string name = jack_get_client_name(client);
        client_instance =
	    name.substr(0, client_name.size()-strlen(jack_amp_postfix))
	    + name.substr(client_name.size());
	client_name = name;
        client_insert_name = jack_get_client_name(client_insert);
    }

    jack_sr = jack_get_sample_rate(client); // jack sample rate
    gx_system::gx_print_info(
	_("Jack init"),
	boost::format(_("The jack sample rate is %1%/sec")) % jack_sr);

    jack_bs = jack_get_buffer_size(client); // jack buffer size

    gx_system::gx_print_info(
	_("Jack init"),
	boost::format(_("The jack buffer size is %1%/frames ... "))
	% jack_bs);

    gx_system::GxExit::get_instance().signal_exit().connect(
	sigc::mem_fun(*this, &GxJack::cleanup_slot));
    gx_jack_callbacks();
    client_change();
    gx_jack_init_port_connection();
    set_jack_exit(false);

    return true;
}

void GxJack::cleanup_slot(bool otherthread) {
    if (!client || is_jack_down()) {
	return;
    }
    engine.start_ramp_down();
    engine.wait_ramp_down_finished();
    jack_client_close(client);
    client = 0;
    jack_client_close(client_insert);
    client_insert = 0;
}

// -----Function that cleans the jack stuff on shutdown
void GxJack::gx_jack_cleanup() {
    if (!client || is_jack_down()) {
	return;
    }
    engine.start_ramp_down();
    engine.wait_ramp_down_finished();
    set_jack_exit(true);
    engine.set_stateflag(gx_engine::GxEngine::SF_INITIALIZING);
    jack_deactivate(client);
    jack_deactivate(client_insert);
    jack_port_unregister(client, ports.input.port);
    jack_port_unregister(client, ports.midi_input.port);
    jack_port_unregister(client, ports.insert_out.port);
    jack_port_unregister(client, ports.midi_output.port);
    jack_port_unregister(client_insert, ports.insert_in.port);
    jack_port_unregister(client_insert, ports.output1.port);
    jack_port_unregister(client_insert, ports.output2.port);
    jack_client_close(client);
    client = 0;
    jack_client_close(client_insert);
    client_insert = 0;
}

// ---- Jack server connection / disconnection
bool GxJack::gx_jack_connection(bool connect) {
    if (connect) {
	if (client) {
	    return true;
	}
	if (!gx_jack_init()) {
	    return false;
	}
    } else {
	if (!client) {
	    return true;
	}
	gx_jack_cleanup();
    }
    connection();
    connection_queue.portchange();
    return true;
}


/****************************************************************
 ** port connections
 */

// ----- connect ports if we know them
void GxJack::gx_jack_init_port_connection() {
    gx_system::CmdlineOptions& opt = gx_system::get_options();
    // set autoconnect capture to user capture port
    if (!opt.get_jack_input().empty()) {
        jack_connect(client, opt.get_jack_input().c_str(),
                     jack_port_name(ports.input.port));
    } else {
        list<string>& l = ports.input.conn;
        for (list<string>::iterator i = l.begin(); i != l.end(); ++i) {
            jack_connect(client, i->c_str(), jack_port_name(ports.input.port));
        }
    }

    // set autoconnect midi to user midi port
    if (ports.midi_input.port && !opt.get_jack_midi().empty()) {
        jack_connect(client, opt.get_jack_midi().c_str(),
                     jack_port_name(ports.midi_input.port));
    } else {
        list<string>& l = ports.midi_input.conn;
        for (list<string>::iterator i = l.begin(); i != l.end(); ++i) {
            jack_connect(client, i->c_str(), jack_port_name(ports.midi_input.port));
        }
    }

    // set autoconnect to user playback ports
    if (opt.get_jack_output(0).empty() && opt.get_jack_output(1).empty()) {
        list<string>& l1 = ports.output1.conn;
        for (list<string>::iterator i = l1.begin(); i != l1.end(); ++i) {
            jack_connect(client_insert, jack_port_name(ports.output1.port), i->c_str());
        }
        list<string>& l2 = ports.output2.conn;
        for (list<string>::iterator i = l2.begin(); i != l2.end(); ++i) {
            jack_connect(client_insert, jack_port_name(ports.output2.port), i->c_str());
        }
    } else {
	if (!opt.get_jack_output(0).empty()) {
	    jack_connect(client_insert,
			 jack_port_name(ports.output1.port),
			 opt.get_jack_output(0).c_str());
	}
	if (!opt.get_jack_output(1).empty()) {
	    jack_connect(client_insert,
			 jack_port_name(ports.output2.port),
			 opt.get_jack_output(1).c_str());
	}
    }

    // autoconnect midi output port
    list<string>& lmo = ports.midi_output.conn;
    for (list<string>::iterator i = lmo.begin(); i != lmo.end(); ++i) {
        jack_connect(client, jack_port_name(ports.midi_output.port), i->c_str());
    }

    // autoconnect to insert ports
    list<string>& lins_in = ports.insert_in.conn;
    list<string>& lins_out = ports.insert_out.conn;
    bool ifound = false, ofound = false;
    for (list<string>::iterator i = lins_in.begin(); i != lins_in.end(); ++i) {
        int rc = jack_connect(client_insert, i->c_str(),
                              jack_port_name(ports.insert_in.port));
        if (rc == 0 || rc == EEXIST) {
            ifound = true;
        }
    }
    jack_port_t* port_a = jack_port_by_name(client, jack_port_name(ports.insert_out.port));
    for (list<string>::iterator i = lins_out.begin(); i != lins_out.end(); ++i) {
	if (!jack_port_connected_to(port_a, i->c_str())) {
	    int rc = jack_connect(client, jack_port_name(ports.insert_out.port), i->c_str());
	    if (rc == 0 || rc == EEXIST) {
		ofound = true;
	    }
	} else {
	    ofound = true;
	}
    }
    if (!ifound || !ofound) {
        jack_connect(client_insert, jack_port_name(ports.insert_out.port),
		     (client_insert_name+":in_0").c_str());
    }
}

void GxJack::clear_insert_connections() {
    ports.insert_in.conn.clear();
    ports.insert_out.conn.clear();
}

/****************************************************************
 ** callback installation and port registration
 */

// ----- set gxjack.client callbacks and activate gxjack.client
void GxJack::gx_jack_callbacks() {
    // ----- set the jack callbacks
    jack_set_xrun_callback(client, gx_jack_xrun_callback, this);
    jack_set_sample_rate_callback(client, gx_jack_srate_callback, this);
    jack_on_shutdown(client, gx_jack_shutdown_callback, this);
    jack_set_buffer_size_callback(client, gx_jack_buffersize_callback, this);
    jack_set_port_registration_callback(client, gx_jack_portreg_callback, this);
    jack_set_port_connect_callback(client, gx_jack_portconn_callback, this);
#ifdef HAVE_JACK_SESSION
    if (jack_set_session_callback) {
        jack_set_session_callback(client, gx_jack_session_callback, this);
    }
#endif

    // register ports for gx_amp
    ports.input.port = jack_port_register(
	client, "in_0", JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);
    ports.midi_input.port = jack_port_register(
	client, "midi_in_1", JACK_DEFAULT_MIDI_TYPE, JackPortIsInput, 0);
    ports.insert_out.port = jack_port_register(
	client, "out_0", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
    ports.midi_output.port = jack_port_register(
	client, "midi_out_1", JACK_DEFAULT_MIDI_TYPE, JackPortIsOutput, 0);

    // register ports for gx_amp_fx
    ports.insert_in.port = jack_port_register(
	client_insert, "in_0", JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);
    ports.output1.port = jack_port_register(
	client_insert, "out_0", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
    ports.output2.port = jack_port_register(
	client_insert, "out_1", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);

    engine.init(jack_sr, jack_bs, SCHED_FIFO,
		jack_client_real_time_priority(client));
    jack_set_process_callback(client, gx_jack_process, this);
    jack_set_process_callback(client_insert, gx_jack_insert_process, this);
    if (jack_activate(client) != 0) {
        gx_system::gx_print_fatal(
	    _("Jack Activation"),
	    string(_("Can't activate JACK gx_amp client")));
    }
    if (jack_activate(client_insert) != 0) {
        gx_system::gx_print_fatal(_("Jack Activation"),
                       string(_("Can't activate JACK gx_amp_fx client")));
    }
}


/****************************************************************
 ** jack process callbacks
 */

// must only be used inside gx_jack_process
void *GxJack::get_midi_buffer(jack_nframes_t nframes) {
    if (!ports.midi_output.port) {
	return 0;
    }
    void *midi_port_buf = jack_port_get_buffer(ports.midi_output.port, nframes);
    if (midi_port_buf) {
	jack_midi_clear_buffer(midi_port_buf);
    }
    return midi_port_buf;
}

static inline float *get_float_buf(jack_port_t *port, jack_nframes_t nframes) {
    return static_cast<float *>(jack_port_get_buffer(port, nframes));
}

// ----- main jack process method gx_amp, mono -> mono
// RT process thread
int GxJack::gx_jack_process(jack_nframes_t nframes, void *arg) {
    gx_system::measure_start();
    GxJack& self = *static_cast<GxJack*>(arg);
    if (!self.is_jack_exit()) {
        AVOIDDENORMALS;

        // gx_head DSP computing
	self.engine.mono_chain.process(
	    nframes,
	    get_float_buf(self.ports.input.port, nframes),
	    get_float_buf(self.ports.insert_out.port, nframes));

        // midi input processing
	if (self.ports.midi_input.port) {
	    gx_gui::controller_map.compute_midi_in(
		jack_port_get_buffer(self.ports.midi_input.port, nframes));
	}
    }
    gx_system::measure_pause();
    self.engine.mono_chain.post_rt_finished();
    return 0;
}

// ----- main jack process method, gx_fx_amp, mono -> stereo
// RT process_insert thread
int GxJack::gx_jack_insert_process(jack_nframes_t nframes, void *arg) {
    GxJack& self = *static_cast<GxJack*>(arg);
    gx_system::measure_cont();
    if (!self.is_jack_exit()) {
        AVOIDDENORMALS;
        // gx_head DSP computing
	self.engine.stereo_chain.process(
	    nframes,
	    get_float_buf(self.ports.insert_in.port, nframes),
	    get_float_buf(self.ports.output1.port, nframes),
	    get_float_buf(self.ports.output2.port, nframes));
    }
    gx_system::measure_stop();
    self.engine.stereo_chain.post_rt_finished();
    return 0;
}


/****************************************************************
 ** port connection callback
 */

PortConnRing::PortConnRing()
    : ring(jack_ringbuffer_create(20*sizeof(PortConnData))), // just a number...
      send_changes(false),
      overflow(false),
      new_data(),
      portchange() {
    if (!ring) {
	gx_system::gx_print_fatal(
	    _("Jack init"), _("can't get memory for ringbuffer"));
    }
    jack_ringbuffer_mlock(ring);
}

PortConnRing::~PortConnRing() {
    jack_ringbuffer_free(ring);
}

void PortConnRing::push(const char *a, const char *b, bool conn) {
    if (is_overflow()) {
	return;
    }
    if (send_changes) {
	PortConnData p(a, b, conn);
	size_t sz = jack_ringbuffer_write(ring, reinterpret_cast<const char*>(&p), sizeof(p));
	if (sz != sizeof(p)) {
	    set_overflow();
	} else {
	    jack_ringbuffer_write_advance(ring, sz);
	}
    }
    new_data();
}

bool PortConnRing::pop(PortConnData *p) {
    if (is_overflow()) {
	jack_ringbuffer_reset(ring);
	portchange();
	clear_overflow();
	return false;
    }
    size_t sz = jack_ringbuffer_read(ring, reinterpret_cast<char*>(p), sizeof(*p));
    if (sz == 0) {
	return false;
    }
    assert(sz == sizeof(*p));
    jack_ringbuffer_read_advance(ring, sz);
    return true;
}

void GxJack::fetch_connection_data() {
    // check if we are connected
    const char** port = jack_port_get_connections(ports.input.port);
    if (port) { // might be 0 (e.g. due to race conditions)
	engine.clear_stateflag(gx_engine::GxEngine::SF_NO_CONNECTION);
        free(port);
    } else {
	engine.set_stateflag(gx_engine::GxEngine::SF_NO_CONNECTION);
    }
    while (true) {
	PortConnData p;
	bool fetched = connection_queue.pop(&p);
	if (!fetched) {
	    break;
	}
	if (client) {
	    connection_changed(p.name_a, p.name_b, p.connect);
	}
    }
}

// jackd1: RT process thread
// jackd2: not RT thread
void GxJack::gx_jack_portconn_callback(jack_port_id_t a, jack_port_id_t b, int connect, void* arg) {
    GxJack& self = *static_cast<GxJack*>(arg);
    if (!self.client) {
	return;
    }
    jack_port_t* port_a = jack_port_by_id(self.client, a);
    jack_port_t* port_b = jack_port_by_id(self.client, b);
    if (!port_a || !port_b) {
        return;
    }
    self.connection_queue.push(jack_port_name(port_a), jack_port_name(port_b), connect);
}


/****************************************************************
 ** callbacks: portreg, buffersize, samplerate, shutdown, xrun
 */

// ----- fetch available jack ports other than gx_head ports
// jackd1: RT process thread
// jackd2: not RT thread
void GxJack::gx_jack_portreg_callback(jack_port_id_t pid, int reg, void* arg) {
    GxJack& self = *static_cast<GxJack*>(arg);
    if (!self.client) {
        return;
    }
    jack_port_t* port = jack_port_by_id(self.client, pid);
    if (!port || jack_port_is_mine(self.client, port)) {
        return;
    }
    self.connection_queue.portchange();
}

// ----jack sample rate change callback
// seems to be run in main thread (just once, no possibility
// to change the samplerate when jack is running?)
int GxJack::gx_jack_srate_callback(jack_nframes_t samplerate, void* arg) {
    GxJack& self = *static_cast<GxJack*>(arg);
    if (self.jack_sr == samplerate) {
	return 0;
    }
    self.engine.set_stateflag(gx_engine::GxEngine::SF_JACK_RECONFIG);
    self.jack_sr = samplerate;
    self.engine.samplerate_change(samplerate);
    self.engine.clear_stateflag(gx_engine::GxEngine::SF_JACK_RECONFIG);
    return 0;
}

// ---- jack buffer size change callback
// RT process thread
int GxJack::gx_jack_buffersize_callback(jack_nframes_t nframes, void* arg) {
    GxJack& self = *static_cast<GxJack*>(arg);
    if (self.jack_bs == nframes) {
	return 0;
    }
    self.engine.set_stateflag(gx_engine::GxEngine::SF_JACK_RECONFIG);
    self.jack_bs = nframes;
    self.engine.buffersize_change(nframes);
    self.engine.clear_stateflag(gx_engine::GxEngine::SF_JACK_RECONFIG);
    self.buffersize_change();
    return 0;
}

// ---- jack shutdown callback in case jackd shuts down on us
void GxJack::gx_jack_shutdown_callback(void *arg) {
    GxJack& self = *static_cast<GxJack*>(arg);
    self.set_jack_exit(true);
    self.engine.set_stateflag(gx_engine::GxEngine::SF_JACK_RECONFIG);
    self.client = self.client_insert = 0;
    self.shutdown();
}

// ---- jack xrun callback
int GxJack::gx_jack_xrun_callback(void* arg) {
    GxJack& self = *static_cast<GxJack*>(arg);
    self.xrun();
    return 0;
}

float GxJack::get_last_xrun() {
    return jack_get_xrun_delayed_usecs(client);
}

/****************************************************************
 ** jack session
 */

#ifdef HAVE_JACK_SESSION
void GxJack::return_last_session_event() {
    jack_session_event_t *event = get_last_session_event();
    if (event) {
	jack_session_reply(client, event);
	jack_session_event_free(event);
	g_atomic_pointer_set(&session_event, 0);
    }
}

string GxJack::get_uuid_insert() {
    // should be const char* but jack_free doesn't like it
    char* uuid = jack_client_get_uuid(client_insert);
    string ret(uuid);
    jack_free(uuid);
    return ret;
}

void GxJack::gx_jack_session_callback(jack_session_event_t *event, void *arg) {
    GxJack& self = *static_cast<GxJack*>(arg);
    if (!g_atomic_pointer_compare_and_exchange(
	    reinterpret_cast<void* volatile*>(&self.session_event), 0, event)) {
	gx_system::gx_print_error("jack","last session not cleared");
	return;
    }
    self.session();
}
#endif

} /* end of gx_jack namespace */
