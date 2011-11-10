/*
 * Copyright (C) 2009, 2010 Hermann Meyer, James Warden, Andreas Degert
 * Copyright (C) 2011 Pete Shorthose
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
 *
 *
 *    This is the guitarix engine definitions
 *
 *
 * --------------------------------------------------------------------------
 */

#include "engine.h"

namespace gx_engine {

/****************************************************************
 ** register audio variables to paramtable
 */

void AudioVariables::register_parameter(ParamMap& pmap) {
    // user interface options
    pmap.reg_non_midi_par("ui.latency_nowarn", &fwarn, false, false);
    pmap.reg_non_midi_par("ui.skin",           &fskin, false, 0, 0, 100);
}

} /* end of gx_engine namespace */
