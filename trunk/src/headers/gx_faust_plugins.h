/*
 * Copyright (C) 2009, 2010 Hermann Meyer, James Warden
 * Copyright (C) 2011 Pete Shorthose, Andreas Degert
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
 * --------------------------------------------------------------------------
 */

#pragma once

#include "gx_plugin.h"

#define declare(n) namespace n { PluginDef *plugin(); }

namespace gx_engine {

namespace gx_amps {
declare(gxamp)
declare(gxamp3)
declare(gxamp14)
declare(gxamp10)
declare(gxamp2)
declare(gxamp9)
declare(gxamp11)
declare(gxamp17)
declare(gxamp13)
declare(gxamp5)
declare(gxamp4)
declare(gxamp15)
declare(gxamp12)
declare(gxamp7)
declare(gxamp8)
declare(gxamp16)
declare(gxamp6)
declare(gxamp18)
declare(gxnoamp)
declare(gx_ampmodul)
}

namespace gx_tonestacks {
declare(tonestack_default)
declare(tonestack_bassman)
declare(tonestack_twin)
declare(tonestack_princeton)
declare(tonestack_jcm800)
declare(tonestack_jcm2000)
declare(tonestack_mlead)
declare(tonestack_m2199)
declare(tonestack_ac30)
declare(tonestack_soldano)
declare(tonestack_mesa)
declare(tonestack_jtm45)
declare(tonestack_ac15)
declare(tonestack_peavey)
declare(tonestack_ibanez)
declare(tonestack_roland)
declare(tonestack_ampeg)
declare(tonestack_ampeg_rev)
declare(tonestack_sovtek)
declare(tonestack_bogner)
declare(tonestack_groove)
declare(tonestack_crunch)
declare(tonestack_fender_blues)
declare(tonestack_fender_default)
declare(tonestack_fender_deville)
declare(tonestack_gibsen)
declare(tonestack_engl)
}

namespace gx_effects {
declare(crybaby)
declare(autowah)
declare(noise_shaper)
declare(softclip)
declare(bassbooster)
declare(highbooster)
declare(gx_ampout)
declare(gxfeed)
declare(gx_outputlevel)
declare(low_high_pass)
declare(selecteq)
declare(gx_distortion)
declare(bitdowner)
declare(thick_distortion)
declare(impulseresponse)
declare(compressor)
declare(expander)
declare(overdrive)
declare(echo)
declare(delay)
declare(freeverb)
declare(biquad)
declare(tremolo)
declare(phaser_mono)
declare(chorus_mono)
declare(flanger_mono)
declare(gx_feedback)
declare(chorus)
declare(flanger)
declare(phaser)
declare(stereodelay)
declare(stereoecho)
declare(moog)
declare(tonecontroll)
declare(stereoverb)
declare(peak_eq)
declare(digital_delay)
declare(digital_delay_st)
declare(dattorros_progenitor)
declare(ring_modulator)
declare(ring_modulator_st)
declare(panoram_enhancer)
declare(graphiceq)
declare(bass_enhancer)
declare(gain)
declare(duck_delay)
declare(duck_delay_st)
declare(baxandall)
declare(distortion2)
declare(fuzzface)
declare(trbuff)
declare(colwah)
declare(dallaswah)
declare(foxwah)
declare(maestrowah)
declare(voxwah)
declare(selwah)
declare(jenwah)
declare(colbwah)
declare(rolwah)
declare(jenbasswah)
}

namespace gx_poweramps {
declare(champ)
declare(epiphone)
declare(orangedarkterror)
declare(princeton)
declare(plexiel34)
declare(supersonic)
}

declare(balance)
declare(dcblocker)
declare(hardlim)

} // namespace gx_engine

#undef declare
