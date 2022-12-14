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
 */

/*** This is a wrapper around the jack dependency in the guitarix engine.
 *   use this instead gx_jack.h to build guitarix as plugin
***/

/* ------- This is the JACK namespace ------- */

#pragma once

#ifndef SRC_HEADERS_GX_JACK_WRAPPER_H_
#define SRC_HEADERS_GX_JACK_WRAPPER_H_

#include <atomic>

#ifdef GUITARIX_AS_PLUGIN

#include <sigc++/sigc++.h>

typedef uint32_t        jack_nframes_t;
namespace gx_engine { class GxEngine; }
namespace gx_system { class CmdlineOptions; class JsonParser; }

namespace gx_jack {

/****************************************************************
 ** class GxJack
 */

class GxJack: public sigc::trackable {
 private:
    gx_engine::GxEngine* engine;

	bool				connected;

    std::string         client_instance;
    jack_nframes_t      jack_sr;   // jack sample rate
    jack_nframes_t      jack_bs;   // jack buffer size
    float               *insert_buffer;
    bool                gx_jack_init(bool startserver, int wait_after_connect,
						     const gx_system::CmdlineOptions& opt);
public:

    jack_nframes_t      get_jack_sr() { return jack_sr; }
    jack_nframes_t      get_jack_bs() { return jack_bs; }
    float               get_jcpu_load() { return -1; }
    bool                get_is_rt() { return true; }
    jack_nframes_t      get_time_is() { return 0; }

public:
    GxJack(gx_engine::GxEngine& engine_);
    ~GxJack();

    void                set_jack_insert(bool v) {}
    bool                gx_jack_connection(bool connect, bool startserver,
						   int wait_after_connect, const gx_system::CmdlineOptions& opt);
	void                send_midi_cc(int cc_num, int pgm_num, int bgn, int num) {}
	void				gx_jack_cleanup();
    static std::string  get_default_instancename();
    const std::string&  get_instancename() { return client_instance; }

	gx_engine::GxEngine& get_engine() { return *engine; }

	void				process(jack_nframes_t nframes, float* input_buffer, float *output_buffer[2]);
	void				process_mono(jack_nframes_t nframes, float* input_buffer, float *output_buffer);
	void				process_stereo(jack_nframes_t nframes, float* input_buffer[2], float *output_buffer[2]);
    void				process_ramp(jack_nframes_t nframes);
    void				process_ramp_mono(jack_nframes_t nframes);
    void				process_ramp_stereo(jack_nframes_t nframes);
    void				finish_process();
    void				srate_callback(jack_nframes_t samplerate);
	void				buffersize_callback(jack_nframes_t nframes);

	void				read_connections(gx_system::JsonParser& jp);
};

} /* end of jack namespace */

#endif // GUITARIX_AS_PLUGIN

#endif // SRC_HEADERS_GX_JACK_WRAPPER_H_
