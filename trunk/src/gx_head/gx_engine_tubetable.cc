/*
 * Copyright (C) 2009-2010 Hermann Meyer, James Warden, Andreas Degert
 * 
 * Copyright (C) 2011, Pete Shorthose
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
 *
 *
 *    This file is part of the Guitarix Audio Engine
 *
 *
 * --------------------------------------------------------------------------
 */
 

namespace gx_tubes {

#define TAB_SIZE (2001)

struct tabled {
	float low;
	float high;
	float istep;
	float data[TAB_SIZE];
};

#include "12ax7.cc"
#include "12AU7.cc"
#include "6V6.cc"
#include "6DJ8.cc"

}

inline float Ftube(int table, float Vgk)
{
	struct gx_tubes::tabled& tab = gx_tubes::tubetable[table];
	float f = (Vgk - tab.low) * tab.istep;
	int i = int(f);
	if (i < 0)
		return tab.data[0];
	if (i >= TAB_SIZE-1)
		return tab.data[TAB_SIZE-1];
	f -= i;
	return tab.data[i]*(1-f) + tab.data[i+1]*f;
}

inline float Ftube2(int table, float Vgk)
{
	struct gx_tubes::tabled& tab = gx_tubes::tubetable2[table];
	float f = (Vgk - tab.low) * tab.istep;
	int i = int(f);
	if (i < 0)
		return tab.data[0];
	if (i >= TAB_SIZE-1)
		return tab.data[TAB_SIZE-1];
	f -= i;
	return tab.data[i]*(1-f) + tab.data[i+1]*f;
}

inline float Ftube3(int table, float Vgk)
{
	struct gx_tubes::tabled& tab = gx_tubes::tubetable3[table];
	float f = (Vgk - tab.low) * tab.istep;
	int i = int(f);
	if (i < 0)
		return tab.data[0];
	if (i >= TAB_SIZE-1)
		return tab.data[TAB_SIZE-1];
	f -= i;
	return tab.data[i]*(1-f) + tab.data[i+1]*f;
}

inline float Ftube4(int table, float Vgk)
{
	struct gx_tubes::tabled& tab = gx_tubes::tubetable4[table];
	float f = (Vgk - tab.low) * tab.istep;
	int i = int(f);
	if (i < 0)
		return tab.data[0];
	if (i >= TAB_SIZE-1)
		return tab.data[TAB_SIZE-1];
	f -= i;
	return tab.data[i]*(1-f) + tab.data[i+1]*f;
}



