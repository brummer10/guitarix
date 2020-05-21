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
#include "lv2/lv2plug.in/ns/ext/atom/atom.h"
#include "lv2/lv2plug.in/ns/ext/atom/util.h"
#include "lv2/lv2plug.in/ns/ext/time/time.h"
#include "lv2/lv2plug.in/ns/ext/urid/urid.h"
#include "lv2/lv2plug.in/ns/lv2core/lv2.h"

#define GXPLUGIN_URI "http://guitarix.sourceforge.net/plugins/gx_digital_delay_"
#define GXPLUGIN_UI_URI "http://guitarix.sourceforge.net/plugins/gx_digital_delay_#gui"

typedef struct {
        LV2_URID atom_Blank;
        LV2_URID atom_Float;
        LV2_URID atom_Object;
        LV2_URID atom_Path;
        LV2_URID atom_Resource;
        LV2_URID atom_Sequence;
        LV2_URID time_Position;
        LV2_URID time_barBeat;
        LV2_URID time_beatsPerMinute;
        LV2_URID time_speed;
} GxDDURIs;

typedef enum
{
   EFFECTS_OUTPUT,
   EFFECTS_INPUT,
   BPM, 
   FEEDBACK, 
   GAIN, 
   HIGHPASS, 
   HOWPASS, 
   LEVEL, 
   MODE, 
   NOTES, 
   DD_CONTROL,
   DD_NOTIFY,
   SYNC,
   //SPEED,
   HOSTBPM,
   BYPASS,
} PortIndex;

#endif //SRC_HEADERS_GXEFFECTS_H_
