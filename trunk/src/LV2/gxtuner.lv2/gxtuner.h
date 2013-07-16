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
#include "lv2/lv2plug.in/ns/ext/state/state.h"
#include "lv2/lv2plug.in/ns/ext/presets/presets.h"
#include <lv2/lv2plug.in/ns/ext/buf-size/buf-size.h>
#include <lv2/lv2plug.in/ns/ext/options/options.h>
#include <lv2/lv2plug.in/ns/ext/atom/atom.h>
#include <lv2/lv2plug.in/ns/ext/log/log.h>
#include <lv2/lv2plug.in/ns/ext/urid/urid.h>
#include <lv2/lv2plug.in/ns/ext/event/event.h>
#include <lv2/lv2plug.in/ns/ext/event/event-helpers.h>
#include <lv2/lv2plug.in/ns/ext/uri-map/uri-map.h>

#define GXPLUGIN_URI "http://guitarix.sourceforge.net/plugins/gxtuner"
#define GXPLUGIN_UI_URI "http://guitarix.sourceforge.net/plugins/gxtuner#gui"


typedef enum
{
  FREQ, 
  REFFREQ,
  TUNEMODE,
  THRESHOLD,
  MAXL,
  RESET,
  LEVEL,
  CHANNEL,
  ONMIDI,
  FASTNOTE,
  PITCHBEND,
  SINGLENOTE,
  BPM,
  VELOCITY,

  GATE, 
  SYNTHFREQ, 
  GAIN, 
  VERIFY,
  MIDIOUT,  
  EFFECTS_OUTPUT,
  EFFECTS_INPUT,
} PortIndex;
/*
typedef enum
{
  C1  = 24,
  Cb1 = 25,
  D1  = 26,
  Db1 = 27,
  E1  = 28,
  F1  = 29,
  Fb1 = 30,
  G1  = 31,
  Gb1 = 32,
  A1  = 33,
  Ab1 = 34,
  B1  = 35,

  C2  = 36,
  Cb2 = 37,
  D2  = 38,
  Db2 = 39,
  E2  = 40,
  F2  = 41,
  Fb2 = 42,
  G2  = 43,
  Gb2 = 44,
  A2  = 45,
  Ab2 = 46,
  B2  = 47,

  C3  = 48,
  Cb3 = 49,
  D3  = 50,
  Db3 = 51,
  E3  = 52,
  F3  = 53,
  Fb3 = 54,
  G3  = 55,
  Gb3 = 56,
  A3  = 57,
  Ab3 = 58,
  B3  = 59,

  C4  = 60,
  Cb4 = 61,
  D4  = 62,
  Db4 = 63,
  E4  = 64,
  F4  = 65,
  Fb4 = 66,
  G4  = 67,
  Gb4 = 68,
  A4  = 69,
  Ab4 = 70,
  B4  = 71,

  C5  = 72,
  Cb5 = 73,
  D5  = 74,
  Db5 = 75,
  E5  = 76,
  F5  = 77,
  Fb5 = 78,
  G5  = 79,
  Gb5 = 80,
  A5  = 81,
  Ab5 = 82,
  B5  = 83,
 
} NOTES;
*/
#endif //SRC_HEADERS_GXEFFECTS_H_
