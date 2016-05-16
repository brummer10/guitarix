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

#ifndef __GAINLINE_H__
#define __GAINLINE_H__

#include <gxw/gainpoints.h>
#include <vector>

inline bool operator==(const gain_points& p1, const gain_points& p2) { return p1.i == p2.i && std::abs(p1.g - p2.g) < 1e-4 * (p1.g + p2.g); }
inline bool operator!=(const gain_points& p1, const gain_points& p2) { return !(p1 == p2); }

class Gainline: public std::vector<gain_points>
{
public:
	Gainline(gain_points *p, int n) { while (n-- > 0) push_back(*p++); }
	Gainline() {}
	const gain_points *points() const { return &(*begin()); }
};

inline bool operator==(const Gainline& g1, const Gainline& g2) {
    if (g1.size() != g2.size()) {
	return false;
    }
    for (unsigned int i = 0; i < g1.size(); ++i) {
	if (g1.points()[i] != g2.points()[i]) {
	    return false;
	}
    }
    return true;
}

inline bool operator!=(const Gainline& g1, const Gainline& g2) { return !(g1 == g2); }

#endif /* __GAINLINE_H__ */
