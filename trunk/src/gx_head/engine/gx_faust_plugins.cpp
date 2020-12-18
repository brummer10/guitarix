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

#include <glibmm/i18n.h>
#include <cstdlib>
#include <cmath>
#include "gx_faust_plugins.h"
#include "gx_faust_support.h"

namespace gx_engine {

namespace gx_amps {
#include "faust/gxamp.cc"
#include "faust/gxamp2.cc"
#include "faust/gxamp3.cc"
#include "faust/gxamp4.cc"
#include "faust/gxamp5.cc"
#include "faust/gxamp6.cc"
#include "faust/gxamp7.cc"
#include "faust/gxamp8.cc"
#include "faust/gxamp9.cc"
#include "faust/gxamp10.cc"
#include "faust/gxamp11.cc"
#include "faust/gxamp12.cc"
#include "faust/gxamp13.cc"
#include "faust/gxamp14.cc"
#include "faust/gxamp15.cc"
#include "faust/gxamp16.cc"
#include "faust/gxamp17.cc"
#include "faust/gxamp18.cc"
#include "faust/gxnoamp.cc"
#include "faust/gx_ampmodul.cc"
}

namespace gx_tonestacks {
#include "faust/tonestack_default.cc"
#include "faust/tonestack_bassman.cc"
#include "faust/tonestack_twin.cc"
#include "faust/tonestack_princeton.cc"
#include "faust/tonestack_jcm800.cc"
#include "faust/tonestack_jcm2000.cc"
#include "faust/tonestack_mlead.cc"
#include "faust/tonestack_m2199.cc"
#include "faust/tonestack_ac30.cc"
#include "faust/tonestack_mesa.cc"
#include "faust/tonestack_soldano.cc"
#include "faust/tonestack_jtm45.cc"
#include "faust/tonestack_ac15.cc"
#include "faust/tonestack_peavey.cc"
#include "faust/tonestack_ibanez.cc"
#include "faust/tonestack_roland.cc"
#include "faust/tonestack_ampeg.cc"
#include "faust/tonestack_ampeg_rev.cc"
#include "faust/tonestack_sovtek.cc"
#include "faust/tonestack_bogner.cc"
#include "faust/tonestack_groove.cc"
#include "faust/tonestack_crunch.cc"
#include "faust/tonestack_fender_blues.cc"
#include "faust/tonestack_fender_default.cc"
#include "faust/tonestack_fender_deville.cc"
#include "faust/tonestack_gibsen.cc"
#include "faust/tonestack_engl.cc"
}

namespace gx_effects {
#include "faust/bassbooster.cc"
#include "faust/highbooster.cc"
#include "faust/gxfeed.cc"
#include "faust/gx_feedback.cc"
#include "faust/gx_outputlevel.cc"
#include "faust/gx_ampout.cc"
#include "faust/overdrive.cc"
#include "faust/compressor.cc"
#include "faust/expander.cc"
#include "faust/crybaby.cc"
#include "faust/autowah.cc"
#include "faust/echo.cc"
#include "faust/delay.cc"
#include "faust/stereodelay.cc"
#include "faust/stereoecho.cc"
#include "faust/noise_shaper.cc"
#include "faust/gx_distortion.cc"
#include "faust/bitdowner.cc"
#include "faust/thick_distortion.cc"
#include "faust/freeverb.cc"
#include "faust/impulseresponse.cc"
#include "faust/chorus.cc"
#include "faust/moog.cc"
#include "faust/biquad.cc"
#include "faust/flanger.cc"
#include "faust/selecteq.cc"
#include "faust/phaser.cc"
#include "faust/low_high_pass.cc"
#include "faust/softclip.cc"
#include "faust/tonecontroll.cc"
#include "faust/tremolo.cc"
#include "faust/phaser_mono.cc"
#include "faust/chorus_mono.cc"
#include "faust/flanger_mono.cc"
#include "faust/stereoverb.cc"
#include "faust/peak_eq.cc"
#include "faust/digital_delay.cc"
#include "faust/digital_delay_st.cc"
#include "faust/dattorros_progenitor.cc"
#include "faust/ring_modulator.cc"
#include "faust/ring_modulator_st.cc"
#include "faust/panoram_enhancer.cc"
#include "faust/graphiceq.cc"
#include "faust/bass_enhancer.cc"
#include "faust/gain.cc"
#include "faust/duck_delay.cc"
#include "faust/duck_delay_st.cc"
#include "faust/baxandall.cc"
#include "faust/distortion2.cc"
#include "faust/fuzzface.cc"
#include "faust/trbuff.cc"
#include "faust/colwah.cc"
#include "faust/dallaswah.cc"
#include "faust/foxwah.cc"
#include "faust/maestrowah.cc"
#include "faust/voxwah.cc"
#include "faust/selwah.cc"
#include "faust/jenwah.cc"
#include "faust/colbwah.cc"
#include "faust/rolwah.cc"
#include "faust/jenbasswah.cc"

}
namespace gx_poweramps {
#include "faust/champ.cc"
#include "faust/epiphone.cc"
#include "faust/orangedarkterror.cc"
#include "faust/princeton.cc"
#include "faust/plexiel34.cc"
#include "faust/supersonic.cc"

}
#include "faust/balance.cc"
#include "faust/dcblocker.cc"
#include "faust/hardlim.cc"

}
