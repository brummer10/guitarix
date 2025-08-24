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
#ifndef GUITARIX_AS_PLUGIN
#include <jack/statistics.h>    // NOLINT
#include <jack/jack.h>          // NOLINT
#include <jack/thread.h>        // NOLINT
#endif
#include "engine.h"           // NOLINT

#ifdef HAVE_JACK_SESSION
#include <dlfcn.h>
#endif


namespace gx_jack {
#ifndef GUITARIX_AS_PLUGIN

/****************************************************************
 ** class GxRtCheck
 ** check if user have realtime priority
 */

GxRtCheck::GxRtCheck() :
    isRT(false),
    _execute(true)
    {run();}

GxRtCheck::~GxRtCheck() {}

bool GxRtCheck::run_check() {
    isRT = true;
#if defined(__linux__) || defined(_UNIX) || defined(__APPLE__)
    sched_param sch_params;
    sch_params.sched_priority = 50;
    if (pthread_setschedparam(_thd.native_handle(), SCHED_FIFO, &sch_params)) {
        gx_print_info(
            _("Jack init"),
            boost::format(_("Can't use Realtime Priority")));
        isRT = false;
    }
#elif defined(_WIN32)
    // HIGH_PRIORITY_CLASS, THREAD_PRIORITY_TIME_CRITICAL
    if (SetThreadPriority(_thd.native_handle(), 15)) {
        isRT = false;
    }
#else
    //system does not supports thread priority!
    isRT = false;
#endif
    _execute.store(false, std::memory_order_release);
    if (_thd.joinable()) {
        cv.notify_one();
        _thd.join();
    }
    return isRT;
}

void GxRtCheck::run() {
    _thd = std::thread([this]() {
        while (_execute.load(std::memory_order_acquire)) {
            std::unique_lock<std::mutex> lk(m);
            cv.wait(lk);
        }
    });
}

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
 ** rt_watchdog
 */

static unsigned int rt_watchdog_counter;

#ifndef SCHED_IDLE
#define SCHED_IDLE SCHED_OTHER  // non-linux systems
#endif

static void *rt_watchdog_run(void *p) {
    struct sched_param  spar;
    spar.sched_priority = 0;
    pthread_setschedparam(pthread_self(), SCHED_IDLE, &spar);
    while (true) {
	gx_system::atomic_set(&rt_watchdog_counter, 0);
	usleep(1000000);
    }
    return NULL;
}

static int rt_watchdog_limit = 0;

static void rt_watchdog_start() {
    if (rt_watchdog_limit > 0) {
	pthread_attr_t      attr;
	pthread_attr_init(&attr);
	pthread_t pthr;
	if (pthread_create(&pthr, &attr, rt_watchdog_run, 0)) {
	    gx_print_error("watchdog", _("can't create thread"));
	}
	pthread_attr_destroy(&attr);
    }
}

static inline bool rt_watchdog_check_alive(unsigned int bs, unsigned int sr) {
    if (rt_watchdog_limit > 0) {
	if (gx_system::atomic_get(rt_watchdog_counter) > rt_watchdog_limit*(2*sr)/bs) {
	    return false;
	}
	gx_system::atomic_inc(&rt_watchdog_counter);
    }
    return true;
}


/****************************************************************
 ** class MidiCC
 */

MidiCC::MidiCC(gx_engine::GxEngine& engine_)
    : engine(engine_) {
    for (int i = 0; i < max_midi_cc_cnt; i++) {
        send_cc[i] = false;
    }
}

bool MidiCC::send_midi_cc(int _cc, int _pg, int _bgn, int _num) {
    int c = engine.controller_map.get_midi_channel();
    if (c) _cc |=c-1;
    for(int i = 0; i < max_midi_cc_cnt; i++) {
        if (send_cc[i].load(std::memory_order_acquire)) {
            if (cc_num[i] == _cc && pg_num[i] == _pg &&
                bg_num[i] == _bgn && me_num[i] == _num)
                return true;
        } else if (!send_cc[i].load(std::memory_order_acquire)) {
            cc_num[i] = _cc;
            pg_num[i] = _pg;
            bg_num[i] = _bgn;
            me_num[i] = _num;
            send_cc[i].store(true, std::memory_order_release);
            return true;
        }
    }
#ifndef NDEBUG
    cerr << "Internal error: MidiCC overflow" << endl;
    assert(false);
#endif
    return false;
}

/****************************************************************
 ** GxJack ctor, dtor
 */

GxJack::GxJack(gx_engine::GxEngine& engine_)
    : sigc::trackable(),
      rtc(),
      IS_RT(false),
      engine(engine_),
      jack_is_down(false),
      jack_is_exit(true),
      bypass_insert(false),
      mmessage(engine_),
#ifdef HAVE_JACK_SESSION
      session_event(0),
      session_event_ins(0),
      session_callback_seen(0),
#endif
      connection_queue(),
      connection_changed(),
      buffersize_change(),
      client_change_rt(),
      client_change(),
      client_instance(),
      jack_sr(),
      jack_bs(),
      insert_buffer(NULL),
      xrun(),
      last_xrun(0),
      xrun_msg_blocked(false),
      ports(),
      client(0),
      client_insert(0),
      client_name(),
      client_insert_name(),
      session(),
      session_ins(),
      shutdown(),
      connection(),
      single_client(false) {
    connection_queue.new_data.connect(sigc::mem_fun(*this, &GxJack::fetch_connection_data));
    client_change_rt.connect(client_change);
    GxExit::get_instance().signal_exit().connect(
	sigc::mem_fun(*this, &GxJack::cleanup_slot));
    xrun.connect(sigc::mem_fun(this, &GxJack::report_xrun));
}

GxJack::~GxJack() {
    gx_jack_cleanup();
}

void GxJack::rt_watchdog_set_limit(int limit) {
    rt_watchdog_limit = limit;
    if (limit > 0) {
	rt_watchdog_start();
    }
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
	    gx_print_warning(
		_("recall state"),
		_("unknown jack ports section: ") + jp.current_value());
            jp.skip_object();
            continue;
        }
	i->clear();
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
    gx_system::JsonWriter& w, const char *key, const PortConnection& pc, bool replace) {
    w.write_key(key);
    w.begin_array();
    if (client && pc.port) {
	const char** pl = jack_port_get_connections(pc.port);
	if (pl) {
	    for (const char **p = pl; *p; p++) {
		if (replace) {
		    w.write(make_clientvar(*p));
		} else {
		    w.write(*p);
		}
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
    if (!single_client) {
    write_jack_port_connections(w, "insert_out", ports.insert_out, true);
    write_jack_port_connections(w, "insert_in", ports.insert_in, true);
    }
    w.end_object(true);
}


/****************************************************************
 ** client connection init and cleanup
 */
int GxJack::is_power_of_two (unsigned int x)
{
    return ((x != 0) && ((x & (~x + 1)) == x));
}

// ----- pop up a dialog for starting jack
bool GxJack::gx_jack_init(bool startserver, int wait_after_connect, const gx_system::CmdlineOptions& opt) {
    AVOIDDENORMALS();
    IS_RT = rtc.run_check();
    single_client = opt.get_jack_single();
    int jackopt = (startserver ? JackNullOption : JackNoStartServer);
    client_instance = opt.get_jack_instancename();
    if (client_instance.empty()) {
    if (!single_client) {
        client_instance = get_default_instancename();
    } else {
        client_instance = "guitarix";
    }
    } else {
	jackopt |= JackUseExactName;
    }

    std::string ServerName = opt.get_jack_servername();

    set_jack_down(false);
    set_jack_exit(true);
    engine.set_stateflag(gx_engine::GxEngine::SF_INITIALIZING);

    //ports = JackPorts(); //FIXME

    if (!single_client) {
        client_name = client_instance + jack_amp_postfix;
    } else {
        client_name = client_instance;
    }
    client_insert_name = client_instance + jack_fx_postfix;
    jack_status_t jackstat;
#ifdef HAVE_JACK_SESSION
    // try to open jack gxjack.client
    if (!opt.get_jack_uuid().empty()) {
        client = jack_client_open(
	    client_name.c_str(), JackOptions(jackopt | JackSessionID),
	    &jackstat, opt.get_jack_uuid().c_str());
    } else {
        if (ServerName.empty()) {
        client = jack_client_open(client_name.c_str(), JackOptions(jackopt), &jackstat);
        } else {
        client = jack_client_open(client_name.c_str(), JackOptions(jackopt | JackServerName),
        &jackstat, ServerName.c_str());
        }
    }
#else
    if (ServerName.empty()) {
    client = jack_client_open(client_name.c_str(), JackOptions(jackopt), &jackstat);
    } else {
    client = jack_client_open(client_name.c_str(), JackOptions(jackopt | JackServerName),
    &jackstat, ServerName.c_str());
    }
#endif
    // ----- only start the insert gxjack.client when the amp gxjack.client is true
    if (client && !single_client) {
	// it is maybe not the 1st gx_head instance ?
	// session handler can change name without setting JackNameNotUnique in return status; jack bug??
	// this code depends on jackd only appending a suffix to make a client name unique
	std::string name = jack_get_client_name(client);
	std::string generated_suffix = name.substr(client_name.size());
	std::string base = name.substr(0, client_name.size()-strlen(jack_amp_postfix));
	client_instance = base + generated_suffix;
	client_name = name;
	client_insert_name = base + jack_fx_postfix + generated_suffix;
#ifdef HAVE_JACK_SESSION
        if (!opt.get_jack_uuid2().empty()) {
            client_insert = jack_client_open(
		client_insert_name.c_str(),
		JackOptions(jackopt | JackSessionID | JackUseExactName),
		&jackstat, opt.get_jack_uuid2().c_str());
        } else {
            if (ServerName.empty()) {
            client_insert = jack_client_open(
		client_insert_name.c_str(),
		JackOptions(jackopt | JackUseExactName ), &jackstat);
        } else {
            client_insert = jack_client_open(
		client_insert_name.c_str(),
		JackOptions(jackopt | JackUseExactName | JackServerName),
        &jackstat, ServerName.c_str());
        }
        }
#else
        if (ServerName.empty()) {
        client_insert = jack_client_open(
	    client_insert_name.c_str(),
	    JackOptions(jackopt | JackUseExactName), &jackstat);
        } else {
        client_insert = jack_client_open(
	    client_insert_name.c_str(),
	    JackOptions(jackopt | JackUseExactName | JackServerName),
        &jackstat, ServerName.c_str());
        }
#endif
	if (!client_insert) {
	    jack_client_close(client);
	    client = 0;
	}
    }

    if (!client) {
	if (!(jackstat & JackServerFailed)) {
	    if ((jackstat & JackServerError) && (jackopt & JackUseExactName)) {
		gx_print_error(
		    _("Jack Init"),
		    boost::format(_("can't get requested jack instance name '%1%'"))
		    % client_instance);
	    } else {
		gx_print_error(
		    _("Jack Init"),
		    _("unknown jack server communication error"));
	    }
	}
	return false;
    }

    // ----------------------------------
    set_jack_down(false);

    if (wait_after_connect) {
	usleep(wait_after_connect);
    }
    jack_sr = jack_get_sample_rate(client); // jack sample rate
    gx_print_info(
	_("Jack init"),
	boost::format(_("The jack sample rate is %1%/sec")) % jack_sr);

    jack_bs = jack_get_buffer_size(client); // jack buffer size
	if (!is_power_of_two(jack_bs)) {
    gx_print_warning(
	_("Jack init"),
	boost::format(_("The jack buffer size is %1%/frames is not power of two, Convolver won't run"))
	% jack_bs);
	} else {
    gx_print_info(
	_("Jack init"),
	boost::format(_("The jack buffer size is %1%/frames ... "))
	% jack_bs);
	}
		
	// create buffer to bypass the insert ports
    insert_buffer = new float[jack_bs];
    
    gx_jack_callbacks();
    client_change(); // might load port connection definitions
    if (opt.get_jack_uuid().empty() && !opt.get_jack_noconnect()) {
	// when not loaded by session manager
	gx_jack_init_port_connection(opt);
    }
    set_jack_exit(false);
	if (jack_sr > 96000) {
    gx_print_fatal(
		    _("Jack Init"),
		    _("Sample rates above 96kHz ain't be supported"));
		return false;
	}
    return true;
}

void GxJack::cleanup_slot(bool otherthread) {
    if (!otherthread) {
	gx_jack_cleanup();
    } else {
	// called from other thread. Since most cleanup functions are
	// not thread safe, just do minimal jack cleanup
	if (client) {
	    if (!is_jack_down()) {
		engine.start_ramp_down();
		engine.wait_ramp_down_finished();
	    }
	    jack_deactivate(client);
	    jack_client_close(client);
	    client = 0;
	}
	if (client_insert) {
	    jack_deactivate(client_insert);
	    jack_client_close(client_insert);
	    client_insert = 0;
	}
    }
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
    if (!single_client) jack_deactivate(client_insert);
    jack_port_unregister(client, ports.input.port);
    jack_port_unregister(client, ports.midi_input.port);
    if (!single_client) {
        jack_port_unregister(client, ports.insert_out.port);
    } else {
        jack_port_unregister(client, ports.output1.port);
        jack_port_unregister(client, ports.output2.port);
    }
#if defined(USE_MIDI_OUT) || defined(USE_MIDI_CC_OUT)
    jack_port_unregister(client, ports.midi_output.port);
#endif
    if (!single_client) {
        jack_port_unregister(client_insert, ports.insert_in.port);
        jack_port_unregister(client_insert, ports.output1.port);
        jack_port_unregister(client_insert, ports.output2.port);
    }
    jack_client_close(client);
    client = 0;
    if (!single_client) jack_client_close(client_insert);
    client_insert = 0;
    delete[] insert_buffer;
    insert_buffer = NULL;
    client_change();
}

// ---- Jack server connection / disconnection
bool GxJack::gx_jack_connection(bool connect, bool startserver, int wait_after_connect, const gx_system::CmdlineOptions& opt) {
    if (connect) {
	if (client) {
	    return true;
	}
	if (!gx_jack_init(startserver, wait_after_connect, opt)) {
	    return false;
	}
	engine.set_rack_changed();
	engine.clear_stateflag(gx_engine::GxEngine::SF_INITIALIZING);
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

std::string GxJack::make_clientvar(const std::string& s) {
    std::size_t n = s.find(':');
    if (n == s.npos) {
	return s; // no ':' in jack port name??
    }
    if (s.compare(0, n, client_name) == 0) {
	return "%A" + s.substr(n);
    }
    if (s.compare(0, n, client_insert_name) == 0) {
	return "%F" + s.substr(n);
    }
    return s;
}

std::string GxJack::replace_clientvar(const std::string& s) {
    if (s.compare(0, 3, "%A:") == 0) {
	return client_name + s.substr(2);
    }
    if (s.compare(0, 3, "%F:") == 0) {
	return client_insert_name + s.substr(2);
    }
    return s;
}

// ----- connect ports if we know them
void GxJack::gx_jack_init_port_connection(const gx_system::CmdlineOptions& opt) {
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

    if (!single_client) {
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
    
    } else {
// set autoconnect to user playback ports
    if (opt.get_jack_output(0).empty() && opt.get_jack_output(1).empty()) {
        list<string>& l1 = ports.output1.conn;
        for (list<string>::iterator i = l1.begin(); i != l1.end(); ++i) {
            jack_connect(client, jack_port_name(ports.output1.port), i->c_str());
        }
        list<string>& l2 = ports.output2.conn;
        for (list<string>::iterator i = l2.begin(); i != l2.end(); ++i) {
            jack_connect(client, jack_port_name(ports.output2.port), i->c_str());
        }
    } else {
	if (!opt.get_jack_output(0).empty()) {
	    jack_connect(client,
			 jack_port_name(ports.output1.port),
			 opt.get_jack_output(0).c_str());
	}
	if (!opt.get_jack_output(1).empty()) {
	    jack_connect(client,
			 jack_port_name(ports.output2.port),
			 opt.get_jack_output(1).c_str());
	}
    }
        
    }

#if defined(USE_MIDI_OUT) || defined(USE_MIDI_CC_OUT)
    // autoconnect midi output port
    list<string>& lmo = ports.midi_output.conn;
    for (list<string>::iterator i = lmo.begin(); i != lmo.end(); ++i) {
        jack_connect(client, jack_port_name(ports.midi_output.port), i->c_str());
    }
#endif

    if (!single_client) {
    // autoconnect to insert ports
    list<string>& lins_in = ports.insert_in.conn;
    list<string>& lins_out = ports.insert_out.conn;
    bool ifound = false, ofound = false;
    for (list<string>::iterator i = lins_in.begin(); i != lins_in.end(); ++i) {
        int rc = jack_connect(client_insert, replace_clientvar(*i).c_str(),
                              jack_port_name(ports.insert_in.port));
        if (rc == 0 || rc == EEXIST) {
            ifound = true;
        }
    }
    jack_port_t* port_a = jack_port_by_name(client, jack_port_name(ports.insert_out.port));
    for (list<string>::iterator i = lins_out.begin(); i != lins_out.end(); ++i) {
	std::string port = replace_clientvar(*i);
	if (!jack_port_connected_to(port_a, port.c_str())) {
	    int rc = jack_connect(client, jack_port_name(ports.insert_out.port),
				  port.c_str());
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
}


/****************************************************************
 ** callback installation and port registration
 */

// ----- set gxjack.client callbacks and activate gxjack.client
void GxJack::gx_jack_callbacks() {
    // ----- set the jack callbacks
    jack_set_xrun_callback(client, gx_jack_xrun_callback, this);
    jack_set_sample_rate_callback(client, gx_jack_srate_callback, this);
    jack_on_shutdown(client, shutdown_callback_client, this);
    if (!single_client) {
        jack_on_shutdown(client_insert, shutdown_callback_client_insert, this);
    }
    jack_set_buffer_size_callback(client, gx_jack_buffersize_callback, this);
    jack_set_port_registration_callback(client, gx_jack_portreg_callback, this);
    jack_set_port_connect_callback(client, gx_jack_portconn_callback, this);
#ifdef HAVE_JACK_SESSION
    if (jack_set_session_callback_fp) {
        jack_set_session_callback_fp(client, gx_jack_session_callback, this);
        if (!single_client) jack_set_session_callback_fp(client_insert, gx_jack_session_callback_ins, this);
    }
#endif

    // register ports for gx_amp
    ports.input.port = jack_port_register(
	client, "in_0", JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);
    ports.midi_input.port = jack_port_register(
	client, "midi_in_1", JACK_DEFAULT_MIDI_TYPE, JackPortIsInput, 0);
    if (!single_client) {
        ports.insert_out.port = jack_port_register(
        client, "out_0", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
    } else {
        ports.output1.port = jack_port_register(
        client, "out_0", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
        ports.output2.port = jack_port_register(
        client, "out_1", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
    }
#if defined(USE_MIDI_OUT) || defined(USE_MIDI_CC_OUT)
    ports.midi_output.port = jack_port_register(
	client, "midi_out_1", JACK_DEFAULT_MIDI_TYPE, JackPortIsOutput, 0);
#else
    ports.midi_output.port = 0;
#endif

    if (!single_client) {
    // register ports for gx_amp_fx
        ports.insert_in.port = jack_port_register(
          client_insert, "in_0", JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);
        ports.output1.port = jack_port_register(
          client_insert, "out_0", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
        ports.output2.port = jack_port_register(
          client_insert, "out_1", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
    }

    engine.init(jack_sr, jack_bs, get_is_rt() ? SCHED_FIFO : SCHED_OTHER,
		get_is_rt() ? jack_client_real_time_priority(client) : 0);
    jack_set_process_callback(client, gx_jack_process, this);
    if (!single_client) jack_set_process_callback(client_insert, gx_jack_insert_process, this);
    if (jack_activate(client) != 0) {
        gx_print_fatal(
	    _("Jack Activation"),
	    string(_("Can't activate JACK gx_amp client")));
    }
    if (!single_client) {
        if (jack_activate(client_insert) != 0) {
            gx_print_fatal(_("Jack Activation"),
                        string(_("Can't activate JACK gx_amp_fx client")));
        }
    }
}


/****************************************************************
 ** jack process callbacks
 */

void __rt_func GxJack::process_midi_cc(void *buf, jack_nframes_t nframes) {
    // midi CC output processing
    for (int i = mmessage.next(); i >= 0; i = mmessage.next(i)) {
        unsigned char* midi_send = jack_midi_event_reserve(buf, i, mmessage.size(i));
        if (midi_send) {
            mmessage.fill(midi_send, i);
        }
    }
}

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

inline void GxJack::check_overload() {
    if (!rt_watchdog_check_alive(jack_bs, jack_sr)) {
	engine.overload(gx_engine::EngineControl::ov_User, "watchdog thread");
    }
}

// ----- main jack process method gx_amp, mono -> mono
// RT process thread
int __rt_func GxJack::gx_jack_process(jack_nframes_t nframes, void *arg) {
    gx_system::measure_start();
    GxJack& self = *static_cast<GxJack*>(arg);
    if (!self.is_jack_exit()) {
	if (!self.engine.mono_chain.is_stopped()) {
	    self.check_overload();
	}
	self.transport_state = jack_transport_query (self.client, &self.current);
        // gx_head DSP computing
    float *obuf = self.insert_buffer;
    if (!self.single_client) {
        obuf = get_float_buf(self.ports.insert_out.port, nframes);
    } 
	self.engine.mono_chain.process(
	    nframes,
	    get_float_buf(self.ports.input.port, nframes),
	    obuf);

    if (self.bypass_insert && !self.single_client) {
        memcpy(self.insert_buffer, obuf, nframes*sizeof(float));
    }

        // midi input processing
	if (self.ports.midi_input.port) {
	    self.engine.controller_map.compute_midi_in(
		jack_port_get_buffer(self.ports.midi_input.port, nframes), arg);
	}
        // jack transport support
    if ( self.transport_state != self.old_transport_state) {
        self.engine.controller_map.process_trans(self.transport_state);
        self.old_transport_state = self.transport_state;
    }
    }
    // midi CC output processing
    void *buf = self.get_midi_buffer(nframes);
    self.process_midi_cc(buf, nframes);

    gx_system::measure_pause();
    self.engine.mono_chain.post_rt_finished();
    if (self.single_client) {
        self.gx_jack_insert_process(nframes, arg);
    }
    return 0;
}

// ----- main jack process method, gx_fx_amp, mono -> stereo
// RT process_insert thread
int __rt_func GxJack::gx_jack_insert_process(jack_nframes_t nframes, void *arg) {
    GxJack& self = *static_cast<GxJack*>(arg);
    gx_system::measure_cont();
    if (!self.is_jack_exit()) {
	if (!self.engine.stereo_chain.is_stopped()) {
	    self.check_overload();
	}
        // gx_head DSP computing
    float *ibuf = NULL;
    if (!self.bypass_insert && !self.single_client) {
	    ibuf = get_float_buf(self.ports.insert_in.port, nframes);
	} else {
	    ibuf = self.insert_buffer;
	}
	self.engine.stereo_chain.process(
	    nframes, ibuf, ibuf,
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
	gx_print_fatal(
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
    if (client) {
	const char** port = jack_port_get_connections(ports.input.port);
	if (port) { // might be 0 (e.g. due to race conditions)
	    engine.clear_stateflag(gx_engine::GxEngine::SF_NO_CONNECTION);
	    free(port);
	} else {
	    engine.set_stateflag(gx_engine::GxEngine::SF_NO_CONNECTION);
	}
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
    self.engine.set_samplerate(samplerate);
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
    self.engine.set_buffersize(nframes);
    self.engine.clear_stateflag(gx_engine::GxEngine::SF_JACK_RECONFIG);
    self.buffersize_change();
	// create buffer to bypass the insert ports
	delete[] self.insert_buffer;
	self.insert_buffer = NULL;
    self.insert_buffer = new float[self.jack_bs];
    return 0;
}

// ---- jack shutdown callback in case jackd shuts down on us
void GxJack::gx_jack_shutdown_callback() {
    set_jack_exit(true);
    engine.set_stateflag(gx_engine::GxEngine::SF_INITIALIZING);
    shutdown();
}

void GxJack::shutdown_callback_client(void *arg) {
    GxJack& self = *static_cast<GxJack*>(arg);
    if (self.client) {
	self.client = 0;
	self.client_change_rt();
    }
    if (!self.single_client) {
    if (self.client_insert) {
	jack_client_close(self.client_insert);
	self.client_insert = 0;
    }
    }
    self.gx_jack_shutdown_callback();
}

void GxJack::shutdown_callback_client_insert(void *arg) {
    GxJack& self = *static_cast<GxJack*>(arg);
    self.client_insert = 0;
    if (self.client) {
	jack_client_close(self.client);
	self.client = 0;
	self.client_change_rt();
    }
    self.gx_jack_shutdown_callback();
}

void GxJack::report_xrun_clear() {
    xrun_msg_blocked = false;
}

void GxJack::report_xrun() {
    if (xrun_msg_blocked) {
	return;
    }
    xrun_msg_blocked = true;
    Glib::signal_timeout().connect_once(
	sigc::mem_fun(this, &GxJack::report_xrun_clear), 100);
    gx_print_warning(
	_("Jack XRun"),
	(boost::format(_(" delay of at least %1% microsecs")) % last_xrun).str());
}

// ---- jack xrun callback
int GxJack::gx_jack_xrun_callback(void* arg) {
    GxJack& self = *static_cast<GxJack*>(arg);
    if (!self.client) {
	return 0;
    }
    self.last_xrun = jack_get_xrun_delayed_usecs(self.client);
    if (!self.engine.mono_chain.is_stopped()) {
	self.engine.overload(gx_engine::EngineControl::ov_XRun, "xrun");
    }
    self.xrun();
    return 0;
}

/****************************************************************
 ** jack session
 */

#ifdef HAVE_JACK_SESSION
jack_set_session_callback_type GxJack::jack_set_session_callback_fp =
    reinterpret_cast<jack_set_session_callback_type>(
	dlsym(RTLD_DEFAULT, "jack_set_session_callback"));
jack_get_uuid_for_client_name_type GxJack::jack_get_uuid_for_client_name_fp =
    reinterpret_cast<jack_get_uuid_for_client_name_type>(
	dlsym(RTLD_DEFAULT, "jack_get_uuid_for_client_name"));
jack_client_get_uuid_type GxJack::jack_client_get_uuid_fp =
    reinterpret_cast<jack_client_get_uuid_type>(
	dlsym(RTLD_DEFAULT, "jack_client_get_uuid"));

int GxJack::return_last_session_event() {
    jack_session_event_t *event = get_last_session_event();
    if (event) {
	session_callback_seen += 1;
	jack_session_reply(client, event);
	jack_session_event_free(event);
	gx_system::atomic_set_0(&session_event);
    }
    return session_callback_seen;
}

int GxJack::return_last_session_event_ins() {
    jack_session_event_t *event = get_last_session_event_ins();
    if (event) {
	session_callback_seen -= 1;
	jack_session_reply(client_insert, event);
	jack_session_event_free(event);
	gx_system::atomic_set_0(&session_event_ins);
    }
    return session_callback_seen;
}

string GxJack::get_uuid_insert() {
    // should be const char* but jack_free doesn't like it
    char* uuid;
    if (jack_client_get_uuid_fp) {
	uuid = jack_client_get_uuid_fp(client_insert);
    } else if (jack_get_uuid_for_client_name_fp) {
	uuid = jack_get_uuid_for_client_name_fp(
	    client_insert, client_insert_name.c_str());
    } else {
	assert(false);
	gx_print_error(_("session save"), _("can't get client uuid"));
	return "";
    }
    string ret(uuid);
    jack_free(uuid);
    return ret;
}

void GxJack::gx_jack_session_callback(jack_session_event_t *event, void *arg) {
    GxJack& self = *static_cast<GxJack*>(arg);
    jack_session_event_t *np = 0;
    if (!gx_system::atomic_compare_and_exchange(&self.session_event, np, event)) {
	gx_print_error("jack","last session not cleared");
	return;
    }
    self.session();
}

void GxJack::gx_jack_session_callback_ins(jack_session_event_t *event, void *arg) {
    GxJack& self = *static_cast<GxJack*>(arg);
    jack_session_event_t *np = 0;
    if (!gx_system::atomic_compare_and_exchange(&self.session_event_ins, np, event)) {
	gx_print_error("jack","last session not cleared");
	return;
    }
    self.session_ins();
}
#endif // HAVE_JACK_SESSION
#endif // GUITARIX_AS_PLUGIN
} /* end of gx_jack namespace */
