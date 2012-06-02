/*
 * Copyright (C) 2012 Andreas Degert, Hermann Meyer
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

template <int tab_size>
struct table1d_imp {
    float low;
    float high;
    float istep;
    int size;
    float data[tab_size];
};

#include "ts9nonlin.cc"

static inline double ts9nonlin(double x) {
    double f = fabs(x);
    f = (f/(3.0 + f) - ts9table.low) * ts9table.istep;
    int i = static_cast<int>(f);
    if (i < 0) {
        f = ts9table.data[0];
    } else if (i >= ts9table.size-1) {
        f = ts9table.data[ts9table.size-1];
    } else {
	f -= i;
	f = ts9table.data[i]*(1-f) + ts9table.data[i+1]*f;
    }
    return copysign(f, -x);
}
