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

#ifndef SRC_HEADERS_GXREDEYE_H_
#define SRC_HEADERS_GXREDEYE_H_

#include <lv2.h>
#include "lv2/lv2plug.in/ns/ext/state/state.h"
#include "lv2/lv2plug.in/ns/ext/presets/presets.h"
#include <lv2/lv2plug.in/ns/ext/buf-size/buf-size.h>
#include <lv2/lv2plug.in/ns/ext/options/options.h>
#include <lv2/lv2plug.in/ns/ext/atom/atom.h>
#include <lv2/lv2plug.in/ns/ext/log/log.h>
#include <lv2/lv2plug.in/ns/ext/worker/worker.h>
#include <lv2/lv2plug.in/ns/ext/urid/urid.h>

#define GXPLUGIN_URI "http://guitarix.sourceforge.net/plugins/gx_redeye"
#define GXPLUGIN_UI_URI "http://guitarix.sourceforge.net/plugins/gx_redeye#gui"


typedef enum
{
  GAIN = 0,
  TONE,
  VOLUME,
  FEEDBACK,
  VIBE,
  SPEED,
  INTENSITY,
  SINEWAVE,
  AMP_OUTPUT,
  AMP_INPUT,
  AMP_OUTPUT1,
  AMP_INPUT1,
} PortIndex;

#endif //SRC_HEADERS_GXREDEYE_H_
