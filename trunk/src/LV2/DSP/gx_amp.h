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

#include "gxamp.cc"
#include "gxamp2.cc"
#include "gxamp3.cc"
#include "gxamp4.cc"
#include "gxamp5.cc"
#include "gxamp6.cc"
#include "gxamp7.cc"
#include "gxamp8.cc"
#include "gxamp9.cc"
#include "gxamp10.cc"
#include "gxamp11.cc"
#include "gxamp12.cc"
#include "gxamp13.cc"
#include "gxamp14.cc"
#include "gxamp15.cc"
#include "gxamp16.cc"
#include "gxamp17.cc"
#include "gxamp18.cc"


static plug amp_model [] = {
    gxamp::plugin, //0
    gxamp3::plugin, //1
    gxamp14::plugin, //2
    gxamp10::plugin, //3
    gxamp18::plugin, //4

    gxamp2::plugin, //5

    gxamp9::plugin, //6
    gxamp11::plugin, //7
    gxamp17::plugin, //8
    gxamp13::plugin, //9

    gxamp5::plugin, //10
    gxamp4::plugin, //11
    gxamp15::plugin, //12
    gxamp12::plugin, //13

    gxamp7::plugin, //14
    gxamp8::plugin, //15
    gxamp16::plugin, //16
    gxamp6::plugin, //17
};

static const size_t AMP_COUNT = sizeof(amp_model) / sizeof(amp_model[0]);


#endif  //SRC_HEADERS_GX_AMP_H_
