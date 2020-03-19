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

#define GXPLUGIN_URI "http://guitarix.sourceforge.net/plugins/gx_livelooper_"
#define GXPLUGIN_UI_URI "http://guitarix.sourceforge.net/plugins/gx_livelooper_#gui"


typedef enum
{
   EFFECTS_OUTPUT,
   EFFECTS_INPUT,
    clip1,
    clip2,
    clip3,
    clip4,
    clips1,
    clips2,
    clips3,
    clips4,
    speed1,
    speed2,
    speed3,
    speed4,
    bar1,
    bar2,
    bar3,
    bar4,
    gain,
    level1,
    level2,
    level3,
    level4,
    mix,
    play1,
    play2,
    play3,
    play4,
    rplay1,
    rplay2,
    rplay3,
    rplay4,
    playh1,
    playh2,
    playh3,
    playh4,
    rec1,
    rec2,
    rec3,
    rec4,
    reset1,
    reset2,
    reset3,
    reset4,
    rback1,
    rback2,
    rback3,
    rback4,
    synct,
} PortIndex;

#endif //SRC_HEADERS_GXEFFECTS_H_
