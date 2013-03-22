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

#include "tonestack_default_stereo.cc"
#include "tonestack_bassman_stereo.cc"
#include "tonestack_twin_stereo.cc"
#include "tonestack_princeton_stereo.cc"
#include "tonestack_jcm800_stereo.cc"
#include "tonestack_jcm2000_stereo.cc"
#include "tonestack_mlead_stereo.cc"
#include "tonestack_m2199_stereo.cc"
#include "tonestack_ac30_stereo.cc"
#include "tonestack_mesa_stereo.cc"
#include "tonestack_soldano_stereo.cc"
#include "tonestack_jtm45_stereo.cc"
#include "tonestack_ac15_stereo.cc"
#include "tonestack_peavey_stereo.cc"
#include "tonestack_ibanez_stereo.cc"
#include "tonestack_roland_stereo.cc"
#include "tonestack_ampeg_stereo.cc"
#include "tonestack_ampeg_rev_stereo.cc"
#include "tonestack_sovtek_stereo.cc"
#include "tonestack_bogner_stereo.cc"
#include "tonestack_groove_stereo.cc"
#include "tonestack_crunch_stereo.cc"
#include "tonestack_fender_blues_stereo.cc"
#include "tonestack_fender_default_stereo.cc"
#include "tonestack_fender_deville_stereo.cc"
#include "tonestack_gibsen_stereo.cc"


static plug tonestack_model[] = {
    tonestack_default_stereo::plugin,
    tonestack_bassman_stereo::plugin,
    tonestack_twin_stereo::plugin,
    tonestack_princeton_stereo::plugin,
    tonestack_jcm800_stereo::plugin,
    tonestack_jcm2000_stereo::plugin,
    tonestack_mlead_stereo::plugin,
    tonestack_m2199_stereo::plugin,
    tonestack_ac30_stereo::plugin,
    tonestack_soldano_stereo::plugin,
    tonestack_mesa_stereo::plugin,
    tonestack_jtm45_stereo::plugin,
    tonestack_ac15_stereo::plugin,
    tonestack_peavey_stereo::plugin,
    tonestack_ibanez_stereo::plugin,
    tonestack_roland_stereo::plugin,
    tonestack_ampeg_stereo::plugin,
    tonestack_ampeg_rev_stereo::plugin,
    tonestack_sovtek_stereo::plugin,
    tonestack_bogner_stereo::plugin,
    tonestack_groove_stereo::plugin,
    tonestack_crunch_stereo::plugin,
    tonestack_fender_blues_stereo::plugin,
    tonestack_fender_default_stereo::plugin,
    tonestack_fender_deville_stereo::plugin,
    tonestack_gibsen_stereo::plugin,
};

static const size_t TS_COUNT = sizeof(tonestack_model) / sizeof(tonestack_model[0]);


#endif  //SRC_HEADERS_GX_TONESTACK_H_

