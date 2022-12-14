/*
 * Copyright (C) 2009, 2010 Hermann Meyer, James Warden, Andreas Degert
 * Copyright (C) 2011 Pete Shorthose
 * Copyright (C) 2022 Maxim Alexanian
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
 *  This is the gx_jack wrapper around the jackd audio / midi server dependency
 *  to build guitarix as plugin
 *
 * --------------------------------------------------------------------------
 */

#include <errno.h>              // NOLINT

#ifdef GUITARIX_AS_PLUGIN

#include "engine.h"           // NOLINT

namespace gx_jack {

std::string GxJack::get_default_instancename() {
    static const char *default_jack_instancename = "gx_head";
    return default_jack_instancename;
}

GxJack::GxJack(gx_engine::GxEngine& engine_)
    : sigc::trackable(),
      engine(&engine_),
      client_instance(),
      jack_sr(0),
      jack_bs(0),
	  connected(false),
      insert_buffer(NULL)
{
}

GxJack::~GxJack() 
{
	gx_jack_cleanup();
	delete[] insert_buffer;
	insert_buffer = NULL;
}

/****************************************************************
 ** client connection init and cleanup
 */

bool GxJack::gx_jack_init(bool startserver, int wait_after_connect, const gx_system::CmdlineOptions& opt) 
{
    AVOIDDENORMALS();
    engine->set_stateflag(gx_engine::GxEngine::SF_INITIALIZING);

    client_instance = get_default_instancename();
    jack_sr = 22050; // TODO
    jack_bs = 1000; // TODO
    // create buffer to bypass the insert ports
    insert_buffer = new float[jack_bs];
    connected = true;

    return true;
}

bool GxJack::gx_jack_connection(bool connect, bool startserver, int wait_after_connect, const gx_system::CmdlineOptions& opt) 
{
    if (connect) {
		if (connected) {
			return true;
		}
		if (!gx_jack_init(startserver, wait_after_connect, opt)) {
			return false;
		}
		engine->set_rack_changed();
		engine->clear_stateflag(gx_engine::GxEngine::SF_INITIALIZING);
	} else {
		if (!connected) {
			return true;
		}
		gx_jack_cleanup();
    }

	return true;
}

void GxJack::gx_jack_cleanup()
{
	engine->set_stateflag(gx_engine::GxEngine::SF_INITIALIZING);
}

void GxJack::process(jack_nframes_t nframes, float* input_buffer, float *output_buffer[2])
{
	gx_system::measure_start();

	float *obuf = insert_buffer;
	engine->mono_chain.process(
		nframes,
		input_buffer,
		obuf);

	gx_system::measure_pause();
	//engine->mono_chain.post_rt_finished();

	gx_system::measure_cont();

	float *ibuf = insert_buffer;

	engine->stereo_chain.process(
		nframes, ibuf, ibuf,
		output_buffer[0],
		output_buffer[1],
		true
	);

	gx_system::measure_stop();
	//engine->stereo_chain.post_rt_finished();
}

void GxJack::process_mono(jack_nframes_t nframes, float* input_buffer, float *output_buffer)
{
	gx_system::measure_start();
	
    engine->mono_chain.process(
	    nframes,
	    input_buffer,
		output_buffer);

	gx_system::measure_stop();
	//engine->mono_chain.post_rt_finished();
}

void GxJack::process_stereo(jack_nframes_t nframes, float* input_buffer[2], float *output_buffer[2])
{
	gx_system::measure_start();

	engine->stereo_chain.process(
		nframes, 
		input_buffer[0], input_buffer[1],
		output_buffer[0], output_buffer[1],
		false
	);

	gx_system::measure_stop();
	//engine->stereo_chain.post_rt_finished();
}

void GxJack::process_ramp(jack_nframes_t nframes)
{
	engine->mono_chain.process_ramp(nframes);
	engine->stereo_chain.process_ramp(nframes);
}
void GxJack::process_ramp_mono(jack_nframes_t nframes)
{
	engine->mono_chain.process_ramp(nframes);
}
void GxJack::process_ramp_stereo(jack_nframes_t nframes)
{
	engine->stereo_chain.process_ramp(nframes);
}

void GxJack::finish_process()
{
	engine->mono_chain.post_rt_finished();
	engine->stereo_chain.post_rt_finished();
}

void GxJack::srate_callback(jack_nframes_t samplerate)
{
    if (jack_sr == samplerate) return;
    
    engine->set_stateflag(gx_engine::GxEngine::SF_JACK_RECONFIG);
    jack_sr = samplerate;
    engine->set_samplerate(samplerate);
    engine->clear_stateflag(gx_engine::GxEngine::SF_JACK_RECONFIG);
}

void GxJack::buffersize_callback(jack_nframes_t nframes)
{
    if (jack_bs == nframes) return;
    
    engine->set_stateflag(gx_engine::GxEngine::SF_JACK_RECONFIG);
    jack_bs = nframes;
    engine->set_buffersize(nframes);
    engine->clear_stateflag(gx_engine::GxEngine::SF_JACK_RECONFIG);
    // create buffer to bypass the insert ports
	delete[] insert_buffer;
	insert_buffer = NULL;
    insert_buffer = new float[jack_bs];
}

void GxJack::read_connections(gx_system::JsonParser& jp) {
	jp.next(gx_system::JsonParser::begin_object);
	while (jp.peek() == gx_system::JsonParser::value_key) {
		list<string> *i;
		jp.next(gx_system::JsonParser::value_key);
		if (jp.current_value() == "input") {
			//i = &ports.input.conn;
		}
		else if (jp.current_value() == "output1") {
			//i = &ports.output1.conn;
		}
		else if (jp.current_value() == "output2") {
			//i = &ports.output2.conn;
		}
		else if (jp.current_value() == "midi_input") {
			//i = &ports.midi_input.conn;
		}
		else if (jp.current_value() == "midi_output") {
			//i = &ports.midi_output.conn;
		}
		else if (jp.current_value() == "insert_out") {
			//i = &ports.insert_out.conn;
		}
		else if (jp.current_value() == "insert_in") {
			//i = &ports.insert_in.conn;
		}
		else {
			gx_print_warning(
				_("recall state"),
				_("unknown jack ports section: ") + jp.current_value());
			jp.skip_object();
			continue;
		}
		jp.next(gx_system::JsonParser::begin_array);
		while (jp.peek() == gx_system::JsonParser::value_string) {
			jp.next();
			//i->push_back(jp.current_value());
		}
		jp.next(gx_system::JsonParser::end_array);
	}
	jp.next(gx_system::JsonParser::end_object);
}

} /* end of gx_jack namespace */

#endif // GUITARIX_AS_PLUGIN
