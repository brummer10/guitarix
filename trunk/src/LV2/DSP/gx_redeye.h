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

#ifndef SRC_HEADERS_GX_REDEYE_H_
#define SRC_HEADERS_GX_REDEYE_H_

#include "gx_pluginlv2.h"

#include "gx_chump.cc"
#include "gx_bigchump.cc"
#include "gx_vibrochump.cc"

static plug amp_model [] = {
    gx_chump::plugin, //0
    gx_bigchump::plugin, //1
    gx_vibrochump::plugin, //2
 };

static const size_t AMP_COUNT = sizeof(amp_model) / sizeof(amp_model[0]);


#endif  //SRC_HEADERS_GX_REDEYE_H_
