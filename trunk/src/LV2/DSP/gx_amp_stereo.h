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

#ifndef SRC_HEADERS_GX_AMP_H_
#define SRC_HEADERS_GX_AMP_H_

#include "gx_pluginlv2.h"

#include "gxamp_stereo.cc"
#include "gxamp2_stereo.cc"
#include "gxamp3_stereo.cc"
#include "gxamp4_stereo.cc"
#include "gxamp5_stereo.cc"
#include "gxamp6_stereo.cc"
#include "gxamp7_stereo.cc"
#include "gxamp8_stereo.cc"
#include "gxamp9_stereo.cc"
#include "gxamp10_stereo.cc"
#include "gxamp11_stereo.cc"
#include "gxamp12_stereo.cc"
#include "gxamp13_stereo.cc"
#include "gxamp14_stereo.cc"
#include "gxamp15_stereo.cc"
#include "gxamp16_stereo.cc"
#include "gxamp17_stereo.cc"
#include "gxamp18_stereo.cc"


static plug amp_model [] = {
    gxamp_stereo::plugin, //0
    gxamp3_stereo::plugin, //1
    gxamp14_stereo::plugin, //2
    gxamp10_stereo::plugin, //3
    gxamp18_stereo::plugin, //4

    gxamp2_stereo::plugin, //5

    gxamp9_stereo::plugin, //6
    gxamp11_stereo::plugin, //7
    gxamp17_stereo::plugin, //8
    gxamp13_stereo::plugin, //9

    gxamp5_stereo::plugin, //10
    gxamp4_stereo::plugin, //11
    gxamp15_stereo::plugin, //12
    gxamp12_stereo::plugin, //13

    gxamp7_stereo::plugin, //14
    gxamp8_stereo::plugin, //15
    gxamp16_stereo::plugin, //16
    gxamp6_stereo::plugin, //17
};

static const size_t AMP_COUNT = sizeof(amp_model) / sizeof(amp_model[0]);


#endif  //SRC_HEADERS_GX_AMP_H_
