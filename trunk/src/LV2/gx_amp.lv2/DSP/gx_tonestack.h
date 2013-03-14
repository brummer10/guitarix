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

#ifndef SRC_HEADERS_GX_TONESTACK_H_
#define SRC_HEADERS_GX_TONESTACK_H_

#include "gx_pluginlv2.h"

#include "tonestack_default.cc"
#include "tonestack_bassman.cc"
#include "tonestack_twin.cc"
#include "tonestack_princeton.cc"
#include "tonestack_jcm800.cc"
#include "tonestack_jcm2000.cc"
#include "tonestack_mlead.cc"
#include "tonestack_m2199.cc"
#include "tonestack_ac30.cc"
#include "tonestack_mesa.cc"
#include "tonestack_soldano.cc"
#include "tonestack_jtm45.cc"
#include "tonestack_ac15.cc"
#include "tonestack_peavey.cc"
#include "tonestack_ibanez.cc"
#include "tonestack_roland.cc"
#include "tonestack_ampeg.cc"
#include "tonestack_ampeg_rev.cc"
#include "tonestack_sovtek.cc"
#include "tonestack_bogner.cc"
#include "tonestack_groove.cc"
#include "tonestack_crunch.cc"
#include "tonestack_fender_blues.cc"
#include "tonestack_fender_default.cc"
#include "tonestack_fender_deville.cc"
#include "tonestack_gibsen.cc"


static plug tonestack_model[] = {
    tonestack_default::plugin,
    tonestack_bassman::plugin,
    tonestack_twin::plugin,
    tonestack_princeton::plugin,
    tonestack_jcm800::plugin,
    tonestack_jcm2000::plugin,
    tonestack_mlead::plugin,
    tonestack_m2199::plugin,
    tonestack_ac30::plugin,
    tonestack_soldano::plugin,
    tonestack_mesa::plugin,
    tonestack_jtm45::plugin,
    tonestack_ac15::plugin,
    tonestack_peavey::plugin,
    tonestack_ibanez::plugin,
    tonestack_roland::plugin,
    tonestack_ampeg::plugin,
    tonestack_ampeg_rev::plugin,
    tonestack_sovtek::plugin,
    tonestack_bogner::plugin,
    tonestack_groove::plugin,
    tonestack_crunch::plugin,
    tonestack_fender_blues::plugin,
    tonestack_fender_default::plugin,
    tonestack_fender_deville::plugin,
    tonestack_gibsen::plugin,
};

static const size_t TS_COUNT = sizeof(tonestack_model) / sizeof(tonestack_model[0]);


#endif  //SRC_HEADERS_GX_TONESTACK_H_

