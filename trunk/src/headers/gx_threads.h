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

/* ------- This is the threads namespace ------- */

#pragma once

namespace gx_threads
{

/* --------------  function declarations ---------------- */
/* slow GTK threads, see GxMainInterface::run() */
gboolean gx_update_all_gui                (gpointer args);
gboolean gx_refresh_meter_level           (gpointer arg);
gboolean gx_survive_jack_shutdown         (gpointer arg);
gboolean gx_monitor_jack_clients          (gpointer args);
gboolean gx_do_program_change             (gpointer arg);
gboolean gx_xrun_report                   (gpointer xdel);
gboolean gx_check_cab_state               (gpointer args);
/* this are the glib threads*/

gpointer gx_signal_helper_thread          (gpointer data);
gpointer gx_program_change_helper_thread  (gpointer args);



/* -------- helper for level meter display -------- */
inline float
log_meter (float db)
{
	gfloat def = 0.0f; /* Meter deflection %age */

	if (db < -70.0f)
	{
		def = 0.0f;
	}
	else if (db < -60.0f)
	{
		def = (db + 70.0f) * 0.25f;
	}
	else if (db < -50.0f)
	{
		def = (db + 60.0f) * 0.5f + 2.5f;
	}
	else if (db < -40.0f)
	{
		def = (db + 50.0f) * 0.75f + 7.5f;
	}
	else if (db < -30.0f)
	{
		def = (db + 40.0f) * 1.5f + 15.0f;
	}
	else if (db < -20.0f)
	{
		def = (db + 30.0f) * 2.0f + 30.0f;
	}
	else if (db < 6.0f)
	{
		def = (db + 20.0f) * 2.5f + 50.0f;
	}
	else
	{
		def = 115.0f;
	}

	/* 115 is the deflection %age that would be
	   when db=6.0. this is an arbitrary
	   endpoint for our scaling.
	*/

	return def/115.0f;
}

/* --------- calculate power (percent) to decibel -------- */
// Note: could use fast_log10 (see ardour code) to make it faster
inline float power2db(float power)
{
	return  20.*log10(power);
}


}
