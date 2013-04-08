/*
 * Copyright (C) 2012 Hermann Meyer, Andreas Degert, Pete Shorthose
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

#define GXPLUGIN_URI "http://guitarix.sourceforge.net/plugins/gx_studiopre_st"
#define GXPLUGIN_UI_URI "http://guitarix.sourceforge.net/plugins/gx_studiopre_st#gui"


typedef enum
{
  BRIGHT_L,
  VOLUME_L,
  BASS_L,
  MIDDLE_L,
  TREBLE_L,
  BRIGHT_R,
  VOLUME_R,
  BASS_R,
  MIDDLE_R,
  TREBLE_R,
  EFFECTS_OUTPUT,
  EFFECTS_INPUT,
  EFFECTS_OUTPUT1,
  EFFECTS_INPUT1,
} PortIndex;

#endif //SRC_HEADERS_GXEFFECTS_H_
