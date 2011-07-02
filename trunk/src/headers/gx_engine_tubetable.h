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
 *
 *    This file is part of the Guitarix Audio Engine
 *
 *
 * --------------------------------------------------------------------------
 */
#pragma once

#ifndef SRC_HEADERS_GX_ENGINE_TUBETABLE_H_
#define SRC_HEADERS_GX_ENGINE_TUBETABLE_H_

#define TAB_SIZE (2001)

namespace gx_tubes {

struct tabled {
    float low;
    float high;
    float istep;
    float data[TAB_SIZE];
};

extern struct tabled tubetable[];
extern struct tabled tubetable2[];
extern struct tabled tubetable3[];
extern struct tabled tubetable4[];
} // end namespace
#endif  // SRC_HEADERS_GX_ENGINE_TUBETABLE_H_

