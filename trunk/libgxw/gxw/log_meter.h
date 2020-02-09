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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef __LOG_METER_H__
#define __LOG_METER_H__

inline double log_meter (double db)
{
    // keep log_meter_inv in sync when changing anying!
    gfloat def = 0.0f; /* Meter deflection %age */

    if (db < -70.0f) {
        def = 0.0f;
    } else if (db < -60.0f) {
        def = (db + 70.0f) * 0.25f;
    } else if (db < -50.0f) {
        def = (db + 60.0f) * 0.5f + 2.5f;
    } else if (db < -40.0f) {
        def = (db + 50.0f) * 0.75f + 7.5f;
    } else if (db < -30.0f) {
        def = (db + 40.0f) * 1.5f + 15.0f;
    } else if (db < -20.0f) {
        def = (db + 30.0f) * 2.0f + 30.0f;
    } else if (db < 6.0f) {
        def = (db + 20.0f) * 2.5f + 50.0f;
    } else {
        def = 115.0f;
    }

    /* 115 is the deflection %age that would be
       when db=6.0. this is an arbitrary
       endpoint for our scaling.
    */

    return def/115.0f;
}

inline double log_meter_inv(double def)
{
    def *= 115.0;
    if (def <= 0.0) {
        return -70.0;
	}
    if (def <= 2.5) {
        return def/0.25 - 70;
	}
    if (def <= 7.5) {
        return (def-2.5)/0.5 - 60;
	}
    if (def <= 15.0) {
        return (def-7.5)/0.75 - 50;
	}
    if (def <= 30.0) {
        return (def-15.0)/1.5 - 40;
	}
    if (def <= 50.0) {
        return (def-30.0)/2.0 - 30;
	}
    if (def <= 115) {
        return (def-50.0)/2.5 - 20;
	}
    return 6.0;
}

#endif /* __LOG_METER_H__ */
