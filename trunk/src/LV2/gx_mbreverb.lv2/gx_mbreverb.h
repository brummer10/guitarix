/*
 * Copyright (C) 2014 Guitarix project MOD project
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

#define GXPLUGIN_URI "http://guitarix.sourceforge.net/plugins/gx_mbreverb_"
#define GXPLUGIN_UI_URI "http://guitarix.sourceforge.net/plugins/gx_mbreverb_#gui"


typedef enum
{
   EFFECTS_OUTPUT,
   EFFECTS_INPUT,
   ROOMSIZE1, 
   ROOMSIZE2, 
   ROOMSIZE3, 
   ROOMSIZE4, 
   ROOMSIZE5, 
   CROSSOVER_B1_B2, 
   CROSSOVER_B2_B3, 
   CROSSOVER_B3_B4, 
   CROSSOVER_B4_B5, 
   DAMP1, 
   DAMP2, 
   DAMP3, 
   DAMP4, 
   DAMP5, 
   V1, 
   V2, 
   V3, 
   V4, 
   V5, 
   WET_DRY1, 
   WET_DRY2, 
   WET_DRY3, 
   WET_DRY4, 
   WET_DRY5, 
} PortIndex;

#endif //SRC_HEADERS_GXEFFECTS_H_
