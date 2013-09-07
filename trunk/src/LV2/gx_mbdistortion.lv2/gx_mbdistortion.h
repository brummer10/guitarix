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

#define GXPLUGIN_URI "http://guitarix.sourceforge.net/plugins/gx_mbdistortion_"
#define GXPLUGIN_UI_URI "http://guitarix.sourceforge.net/plugins/gx_mbdistortion_#gui"


typedef enum
{
   DRIVE1, 
   DRIVE2, 
   DRIVE3, 
   DRIVE4, 
   DRIVE5, 
   GAIN, 
   OFFSET1, 
   OFFSET2, 
   OFFSET3, 
   OFFSET4, 
   OFFSET5, 
   CROSSOVER_B1_B2, 
   CROSSOVER_B2_B3, 
   CROSSOVER_B3_B4, 
   CROSSOVER_B4_B5, 
   V1, 
   V2, 
   V3, 
   V4, 
   V5, 
   EFFECTS_OUTPUT,
   EFFECTS_INPUT,
} PortIndex;

#endif //SRC_HEADERS_GXEFFECTS_H_
