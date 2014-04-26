/*
 * Copyright (C) 2012 Hermann Meyer, Andreas Degert, Pete Shorthose, Steve Poskitt
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

#pragma once

#ifndef SRC_HEADERS_GXEFFECTS_H_
#define SRC_HEADERS_GXEFFECTS_H_

#include <lv2.h>

#define GXPLUGIN_URI "http://guitarix.sourceforge.net/plugins/gx_barkgraphiceq_"
#define GXPLUGIN_UI_URI "http://guitarix.sourceforge.net/plugins/gx_barkgraphiceq_#gui"


typedef enum
{
	G1, 
	G2, 
	G3, 
	G4, 
	G5, 
	G6, 
	G7, 
	G8, 
	G9,
	G10, 
	G11, 
	G12, 
	G13, 
	G14, 
	G15, 
	G16, 
	G17, 
	G18, 
	G19, 
	G20, 
	G21, 
	G22, 
	G23, 
	G24, 
   
	V1, 
	V2, 
	V3, 
	V4, 
	V5, 
	V6, 
	V7, 
	V8, 
	V9,
	V10, 
	V11, 
	V12, 
	V13, 
	V14, 
	V15, 
	V16, 
	V17, 
	V18, 
	V19, 
	V20, 
	V21, 
	V22, 
	V23, 
	V24, 

   EFFECTS_OUTPUT,
   EFFECTS_INPUT,
} PortIndex;

#endif //SRC_HEADERS_GXEFFECTS_H_
