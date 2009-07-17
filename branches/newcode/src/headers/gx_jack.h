/*
 * Copyright (C) 2009 Hermann Meyer and James Warden
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

  /* -------- functions ---------- */
  void gx_jack_init(int&, char**&);
  void gx_jack_callbacks_and_activate(const string* optvar);
  
  void gx_start_jack_dialog(int*  argc, char*** argv);
  void gx_start_jack(void* arg);
  void gx_set_jack_buffer_size(GtkCheckMenuItem*, gpointer);
  void gx_jack_cleanup();

  /* client callbacks */
  int  gx_jack_srate_callback      (jack_nframes_t, void*);
  void gx_jack_shutdown_callback   (void*);
  int  gx_jack_graph_callback      (void*);
  int  gx_jack_xrun_callback       (void*);
  void gx_jack_port_callback       (jack_port_id_t, int, void*);
  int  gx_jack_buffersize_callback (jack_nframes_t, void*);

  /* processing */
  int gx_jack_process (jack_nframes_t, void*);

#ifndef USE_RINGBUFFER
  int gx_jack_midi_process(jack_nframes_t, void*);
#else
  int gx_jack_midi_process_ringbuffer(jack_nframes_t, void*);
#endif

  /* latency change confirmation */
  void gx_confirm_latency_change(void);
  void gx_cancel_latency_change(void);

} /* end of jack namespace */
