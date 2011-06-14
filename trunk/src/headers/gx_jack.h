/*
 * Copyright (C) 2009, 2010 Hermann Meyer, James Warden, Andreas Degert
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
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 * --------------------------------------------------------------------------
 */

/* ------- This is the JACK namespace ------- */

#pragma once

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

#ifdef HAVE_JACK_SESSION
#include <jack/session.h>
#endif

namespace gx_jack
{
#ifdef USE_RINGBUFFER
typedef struct
{
	jack_nframes_t time;
	int		   len;	/* Length of MIDI message, in bytes. */
	unsigned char  data[3];
} MidiMessage;
#endif

class GxJack
{
public:
	static const int nIPorts = 3; // mono input + jconv
	static const int nOPorts = 4; // stereo output + jconv
	/* variables */
	jack_nframes_t      jack_sr;   // jack sample rate
	jack_nframes_t      jack_bs;   // jack buffer size
	float               jcpu_load; // jack cpu_load
	float               xdel;      // last xrun delay
	int                 is_rt;

	jack_client_t*      client ;
	jack_client_t*      client_insert ;
	jack_port_t*        output_ports[nOPorts];
	jack_port_t*        input_ports [nIPorts];
	jack_port_t*        midi_input_port;
	jack_port_t*        midi_output_ports;

	jack_nframes_t      time_is;
};
extern GxJack gxjack;

extern sem_t jack_sync_sem;

/* -------- functions ---------- */
bool gx_jack_init( const string *optvar );
void gx_jack_callbacks_and_activate();

bool gx_start_jack_dialog();
bool gx_start_jack(void* arg);

void gx_set_jack_buffer_size(GtkCheckMenuItem*, gpointer);
void gx_jack_connection(GtkCheckMenuItem*, gpointer);
void gx_jack_cleanup();

/* client callbacks */
int  gx_jack_srate_callback      (jack_nframes_t, void*);
void gx_jack_shutdown_callback   (void*);
int  gx_jack_xrun_callback       (void*);
int  gx_jack_buffersize_callback (jack_nframes_t, void*);
void gx_jack_portreg_callback    (jack_port_id_t, int, void*);
void gx_jack_init_port_connection(const string*);
#ifdef HAVE_JACK_SESSION
void gx_jack_session_callback(jack_session_event_t *event, void *arg);
#endif

/* processing */
int gx_jack_process (jack_nframes_t, void*);
int gx_jack_insert_process (jack_nframes_t, void*);

#ifndef USE_RINGBUFFER
int gx_jack_midi_process(jack_nframes_t, void*);
#else
int gx_jack_midi_process_ringbuffer(jack_nframes_t, void*);
#endif
int gx_jack_midi_input_process(jack_nframes_t, void*);

} /* end of jack namespace */
