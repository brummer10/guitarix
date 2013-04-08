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

#ifndef SRC_HEADERS_GXPREAMP_H_
#define SRC_HEADERS_GXPREAMP_H_


#include <lv2.h>
#include "lv2/lv2plug.in/ns/lv2core/lv2.h"
#include "lv2/lv2plug.in/ns/ext/atom/forge.h"
#include "lv2/lv2plug.in/ns/ext/atom/util.h"
#include "lv2/lv2plug.in/ns/ext/log/log.h"
#include "lv2/lv2plug.in/ns/ext/patch/patch.h"
#include "lv2/lv2plug.in/ns/ext/state/state.h"
#include <lv2/lv2plug.in/ns/ext/buf-size/buf-size.h>
#include <lv2/lv2plug.in/ns/ext/options/options.h>
#include <lv2/lv2plug.in/ns/ext/atom/atom.h>
#include <lv2/lv2plug.in/ns/ext/log/log.h>
#include <lv2/lv2plug.in/ns/ext/worker/worker.h>
#include <lv2/lv2plug.in/ns/ext/urid/urid.h>

#define GXPLUGIN_URI "http://guitarix.sourceforge.net/plugins/gxpreamp"
#define GXPLUGIN_UI_URI "http://guitarix.sourceforge.net/plugins/gxpreamp#gui"

#include "fastlog.h" 

typedef enum
{
  OUTPUT_LEVEL = 0,
  DRIVE,
  INPUT_LEVEL,
  RESONANCE,
  PRESENCE,
  FEEDBACK,
  MAXLEVEL,
  AMP_OUTPUT,
  AMP_INPUT,
  AMP_OUTPUT1,
  AMP_INPUT1
} PortIndex;

// URIS for VUMeter
#define GXPLUGIN__Maxlevel        GXPLUGIN_URI"#Maxlevel"
#define GXPLUGIN__maxlevel        GXPLUGIN_URI"#maxlevel"
typedef struct {
	LV2_URID eg_Maxlevel;
	LV2_URID eg_maxlevel;
} PreampURIs;

static inline void
map_preamp_uris(LV2_URID_Map* map, PreampURIs* uris)
{
	uris->eg_Maxlevel = map->map(map->handle, GXPLUGIN__Maxlevel);
	uris->eg_maxlevel = map->map(map->handle, GXPLUGIN__maxlevel);
}
#endif //SRC_HEADERS_GXPREAMP_H_
