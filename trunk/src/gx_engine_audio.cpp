/*
 * Copyright (C) 2009-2010 Hermann Meyer, James Warden, Andreas Degert
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
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 * --------------------------------------------------------------------------
 *
 *
 *    This is the Guitarix Audio Engine
 *
 *
 * --------------------------------------------------------------------------
 */

#include <cstring>
#include <fstream>
#include "guitarix.h"

using namespace gx_resample;

namespace gx_engine {

#include "gx_engine_tubetable.cc"

/****************************************************************
 ** registering of audio variables
 */

inline void registerNonMidiParam(const char*a, float*c, bool d, float std=0, float lower=0, float upper=1)
{
	gx_gui::parameter_map.insert(new gx_gui::FloatParameter(a,"",gx_gui::Parameter::None,d,*c,std,lower,upper,0,false));
}

// should be int
inline void registerEnumParam(const char*a,const char*b,float*c,float std=0,float lower=0,float upper=1,float step=1,bool exp=false)
{
	gx_gui::parameter_map.insert(new gx_gui::FloatParameter(a,b,gx_gui::Parameter::Enum,true,*c,std,lower,upper,step,true,exp));
}

inline void registerEnumParam(const char*a,const char*b,int*c,int std=0,int lower=0,int upper=1,bool exp=false)
{
	gx_gui::parameter_map.insert(new gx_gui::IntParameter(a,b,gx_gui::Parameter::Enum,true,*c,std,lower,upper,true,exp));
}

/****************************************************************
 ** definitions for code generated with faust / dsp2cc
 */

#include "gx_faust_includes.cc"

/****************************************************************
 ** register audio variables to paramtable
 */

AudioVariables::AudioVariables()
{
	registerEnumParam("amp.threshold", "threshold", &ffuse, 0.f, 0.f, 3.f, 1.0f);
	gx_gui::registerParam("MultiBandFilter.on_off", "on/off", &fmultifilter, 0);
	//gx_gui::registerParam("crybaby.autowah", "autowah", &fautowah, 0);
	registerEnumParam("crybaby.autowah", "select", &fautowah, 0.f, 0.f, 1.f, 1.0f);
	gx_gui::registerParam("overdrive.on_off", "on/off", &foverdrive4, 0);
	gx_gui::registerParam("distortion.on_off", "on/off", &fcheckbox4, 0);
	registerEnumParam("distortiont.onetwo", "select", &witchdistortion, 0.f, 0.f, 1.f, 1.0f);
	registerEnumParam("eqt.onetwo", "select", &witcheq, 0.f, 0.f, 1.f, 1.0f);
	gx_gui::registerParam("freeverb.on_off", "on/off", &fcheckbox6, 0);
	gx_gui::registerParam("IR.on_off", "on/off", &fcheckbox8, 0);
	gx_gui::registerParam("crybaby.on_off", "on/off", &fcheckbox5, 0);
	gx_gui::registerParam("echo.on_off", "on/off", &fcheckbox7, 0);
	gx_gui::registerParam("delay.on_off", "on/off", &fdelay, 0);
	gx_gui::registerParam("chorus.on_off", "on/off", &fchorus, 0);
	gx_gui::registerParam("compressor.on_off", "on/off", &fcheckboxcom1, 0);
	gx_gui::registerParam("tube2.on_off", "on/off", &ftube3, 0);
	gx_gui::registerParam("tube3.on_off", "on/off", &ftube3e, 0);
	gx_gui::registerParam("tube.vibrato.on_off", "on/off", &fresoon, 0);
	gx_gui::registerParam("tube.on_off", "on/off", &ftube, 0);
	gx_gui::registerParam("drive.on_off", "on/off", &fprdr, 0);
	gx_gui::registerParam("preamp.on_off", "on/off", &fcheckbox1, 0);
	registerEnumParam("convolve.select", "select", &convolvefilter, 0.f, 0.f, 7.f, 1.0f);
	gx_gui::registerParam("convolve.on_off", "on/off", &fconvolve, 0);
	gx_gui::registerParam("amp.bass_boost.on_off", "on/off", &fboost, 0);
	gx_gui::registerParam("amp.oversample.on_off", "on/off", &fupsample, 0);
	gx_gui::registerParam("anti_aliase.on_off", "on/off", &antialis0, 0);
	gx_gui::registerParam("noise_gate.on_off", "on/off", &fnoise_g, 0);
	gx_gui::registerParam("noise_gate.threshold", "Threshold", &fnglevel, 0.017f, 0.01f, 0.21f, 0.001f);
	gx_gui::registerParam("shaper.on_off", "on/off", &fng, 0);
	gx_gui::registerParam("eq.on_off", "on/off", &feq, 0);
	gx_gui::registerParam("moog.on_off", "on/off", &fmoog, 0);
	gx_gui::registerParam("biquad.on_off", "on/off", &fbiquad, 0);
	gx_gui::registerParam("flanger.on_off", "on/off", &fflanger, 0);
	gx_gui::registerParam("SampleLooper.on_off", "on/off", &fsloop, 0);
	gx_gui::registerParam("jconv.on_off", "Run", &gx_jconv::GxJConvSettings::checkbutton7);
	registerEnumParam("amp.select", "select", &upsample_mode, 4.f, 1.f, 8.f, 1.0f);
	registerEnumParam("amp.model", "select", &witchamp, 0.f, 0.f, 1.f, 1.0f);
	gx_gui::registerParam("cab.on_off", "Cab-ImpResp", &fcab,0);

	// only save and restore, no midi control

	// positions of effects
	registerNonMidiParam("crybaby.position", &posit0, true, 5, 0, 7);
	registerNonMidiParam("overdrive.position", &posit1, true, 2, 0, 7);
	registerNonMidiParam("distortion.position", &posit2, true, 1, 0, 7);
	registerNonMidiParam("freeverb.position", &posit3, true, 3, 0, 7);
	registerNonMidiParam("IR.position", &posit4, true, 4, 0, 7);
	registerNonMidiParam("compressor.position", &posit5, true, 0, 0, 7);
	registerNonMidiParam("echo.position", &posit6, true, 6, 0, 7);
	registerNonMidiParam("delay.position", &posit7, true, 7, 0, 7);
	registerNonMidiParam("chorus.position", &posit8, true, 8, 8, 8);
	registerNonMidiParam("flanger.position", &posit9, true, 9, 9, 9);

	// togglebuttons for dialogboxes and expander for effect details
	registerNonMidiParam("compressor.dialog", &fdialogbox8, false);
	registerNonMidiParam("distortion.dialog", &fdialogbox1, false);
	registerNonMidiParam("freeverb.dialog", &fdialogbox2, false);
	registerNonMidiParam("IR.dialog", &fdialogbox3, false);
	registerNonMidiParam("crybaby.dialog", &fdialogbox4, false);
	registerNonMidiParam("chorus.dialog", &fchorusbox, false);
	registerNonMidiParam("midi_out.dialog", &fdialogbox6, false);
	registerNonMidiParam("jconv.dialog", &fdialogboxj, false);
	registerNonMidiParam("jconv.expander", &fexpand2, false);
	registerNonMidiParam("jconv.filedialog", &filebutton, false);
	registerNonMidiParam("eq.dialog", &fdialogbox_eq, false);
	registerNonMidiParam("eqs.dialog", &fdialogbox_eqs, false);
	registerNonMidiParam("MultiBandFilter.dialog", &fdialogbox_mbf, false);
	registerNonMidiParam("moog.dialog", &fdialogbox_moo, false);
	registerNonMidiParam("biquad.dialog", &fbiquadbox, false);
	registerNonMidiParam("flanger.dialog", &fflangerbox, false);

	// user interface options
	registerNonMidiParam("ui.latency_nowarn", &fwarn, false, 0);
	registerNonMidiParam("ui.skin", &fskin, false, 0, 0, 100);
	registerNonMidiParam("ui.main_expander", &fexpand, false);
	registerNonMidiParam("ui.amp_expander", &fampexpand, false);

	// shouldn't be saved, only output?
	registerNonMidiParam("system.fConsta1t", &fConsta1t, false);
	registerNonMidiParam("system.midistat", &midistat, false);
	registerNonMidiParam("system.waveview", &viv, false);
}

AudioVariables audio;

/****************************************************************
 ** some dsp funktions
 */

static float filters[][45] = {

	// filter 0
	{0.0222473, 0.0253601, 0.0159607, 0.0184326, 0.0240784,
	 0.02771, 0.0483398, 0.0802917, 0.12915, 0.196259, 0.259521,
	 0.334656, 0.398376, 0.421448, 0.401306, 0.340759, 0.216827,
	 0.058197, -0.117432, -0.287354, -0.438507, -0.540161,
	 0.0583801, 0.0596924, 0.0499573, 0.0406799, 0.0445862,
	 0.0334473, 0.0296021, 0.022644, 0.0142212, 0.0027771,
	 -0.00805664, -0.0206909, -0.0270386, -0.0247498,
	 -0.0259399, -0.0132751, 0.216827, 0.058197, -0.117432,
	 -0.287354, -0.438507, -0.540161, -0.438507
	},

	// filter 1
	{0.19,0.15,0.12,0.05,-0.08,-0.15,-0.18,-0.12,-0.05,0.07,
	 0.12,0.16,0.14,0.11,0.05,0.01,0.04,0.12,0.14,0.08,0.02,
	 -0.01,0.8,0.19,0.15,0.12,0.05,-0.08,-0.15,-0.18,-0.12,
	 -0.05,0.07,0.12,0.16,0.14,0.11,0.05,0.01,0.04,0.12,0.14,
	 0.08,0.02,-0.01
	},

	// filter 2
	{0.19265,0.19265,0.19265,0.19265,0.19265,0.19265,0.19265,
	 0.19265,0.19265,0.19265,0.19265,0.19265,0.19265,0.19265,
	 0.19265,0.19265,0.19265,0.19265,0.19265,0.19265,0.19265,
	 0.19265,0.19265,0.19265,0.19265,0.19265,0.19265,0.19265,
	 0.19265,0.19265,0.19265,0.19265,0.19265,0.19265,0.19265,
	 0.19265,0.19265,0.19265,0.19265,0.19265,0.19265,0.19265,
	 0.19265,0.19265,0.19265
	},

	// filter 3
	{-0.1111851,-0.1811851,-0.1811851,-0.1811851,-0.1811851,
	 -0.1111851,-0.1811851,-0.1811851,-0.1811851,-0.1811851,
	 -0.1111851,-0.1811851,-0.1811851,-0.1811851,-0.1811851,
	 -0.1111851,-0.1811851,-0.1811851,-0.1811851,-0.1811851,
	 -0.1111851,-0.1811851,-0.1811851,-0.1811851,-0.1811851,
	 -0.1111851,-0.1811851,-0.1811851,-0.1811851,-0.1811851,
	 -0.1111851,-0.1811851,-0.1811851,-0.1811851,-0.1811851,
	 -0.1111851,-0.1811851,-0.1811851,-0.1811851,-0.1811851,
	 -0.1111851,-0.1811851,-0.1811851,-0.1811851,-0.1811851
	},

	// filter 4
	{-0.0400391, 0.0591736, 0.0404663, 0.065155, 0.065094,
	 0.0524597, 0.0325012, -0.0254211, -0.0797119, -0.118561,
	 -0.192902, -0.1763, -0.169861, -0.0974426, 0.0567932,
	 0.207458, 0.468079, 0.637085, 0.786072, 0.911835, 0.868347,
	 0.873199, 0.720001, 0.598633, 0.416168, 0.24173, 0.0201416,
	 -0.177277, -0.397614, -0.538208, -0.64505, -0.582642,
	 -0.43161, -0.0495605, 0.361603, 0.724304, 0.981934, 0.953583,
	 0.770233, 0.515625, 0.21106, -0.0998535, -0.162781,
	 -0.171173, 0.042572
	},

	// filter 5
	{0.000610352, 0.00604248, 0.0153809, 0.0246277, 0.0340576,
	 0.0418701, 0.0494385, 0.059082, 0.069458, 0.0871277,
	 0.0636292, -0.0269165, -0.208862, -0.453522, -0.7146,
	 -0.915344, -0.999939, -0.938538, -0.752472, -0.494629,
	 -0.240662, -0.0461426, 0.0594788, 0.0810852, 0.0621643,
	 0.0324707, 0.00180054, -0.0244751, -0.0487061,
	 -0.0654602, -0.0780334, -0.0823669, -0.0776978, -0.0677185,
	 -0.0529175, -0.0342102, -0.0135803, 0.00839233, 0.0301208,
	 0.053833, 0.0252563, 0.0058252, 0.002138, 0.0012851, 0.0009252
	},

	// filter 6
	{-0.0573425, 0.0429382, 0.1698, 0.325623, 0.496429,
	 0.673615, 0.831726, 0.948944, 0.999939, 0.962616,
	 0.822021, 0.57666, 0.25769, -0.091156, -0.393341,
	 -0.568726, -0.545746, -0.315643, 0.052948, 0.422028,
	 0.634552, 0.612579, 0.383606, 0.0856323, -0.142151,
	 -0.233185, -0.185608, -0.0593262, 0.0916748, 0.228333,
	 0.302521, 0.295105, 0.226959, 0.130402, 0.0578308,
	 0.0231018, 0.0189514, 0.0299988, 0.0453186, 0.0602722,
	 0.079834, 0.092804, 0.0980225, 0.0977783, 0.0834351
	},
};

inline void convolver_filter(float* input, float* output, int sf, unsigned int iconvolvefilter)
{
	if (iconvolvefilter >= sizeof(filters) / sizeof(filters[0])) {
		iconvolvefilter = 0;
	}
	for (int i=0; i < 45; i++) {
		result[i] = result[sf+i];
	}
	for (int i=45; i < sf+46; i++) {
		result[i] = 0;
	}

// Do convolution:
	for (int i = 0; i < sf; i++) {
		for (int j = 0; j < 45; j++) {
			result[i+j] += input[i] * filters[iconvolvefilter][j];
		}
	}
	for (int i = 0; i < sf; i++) {
		*output++ = result[i];
	}
}

inline void moving_filter(float* input, float* output, int sf)
{
	assert(input != output);
	*output++ = (input[0]+input[1])*0.5;
	for (int i=1; i<sf-1; i++) {
		*output++ = (input[i-1]+input[i]+input[i+1])*0.3333334f;
	}
	*output++ = (input[sf]+input[sf-1])*0.5;

}

inline float noise_gate(int sf, float* input, float ngate)
{
	float sumnoise = 0;
	for (int i = 0; i < sf; i++) {
		sumnoise += sqrf(fabs(input[i]));
	}
	float noisepulse = sqrtf(sumnoise/sf);
	if (noisepulse > audio.fnglevel * 0.01) {
		return 1; // -75db 0.001 = 65db
	} else if (ngate > 0.01) {
		return ngate * 0.996;
	} else {
		return ngate;
	}
}

inline void over_sample(int sf, float *input, float *output)
{
	static float old = 0;
	for (int i = 0; i < sf; i++) {
		float x = *input++;
		*output++ = (old + x) * 0.5;
		*output++ = x;
		old = x;
	}
}

inline void down_sample(int sf, float *input, float *output)
{
	for (int i=0; i<sf; i++) {
		float x = *input++;
		*output++ = (x + *input++) * 0.5;
	}
}

/****************************************************************
 **  this is the process callback called from jack
 **
 ***************************************************************/
void compute_insert (int count, float* input1, float* output0, float* output1)
{
// retrieve engine state
	const GxEngineState estate = (GxEngineState)checky;

	//------------ determine processing type
	unsigned short process_type = ZEROIZE_BUFFERS;

	if (gx_jack::NO_CONNECTION == 0) { // ports connected
		switch (estate) {
		case kEngineOn:
			process_type = PROCESS_BUFFERS;
			break;

		case kEngineBypass:
			process_type = JUSTCOPY_BUFFERS;
			break;

		default: // engine off or whatever: zeroize
			break;
		}
	}

	//------------ main processing routine
	switch (process_type) {

	case PROCESS_BUFFERS:
		process_insert_buffers(count, input1, output0,output1);
		break;

		// --------- just copy input to outputs
	case JUSTCOPY_BUFFERS:
		if (conv.is_runnable()) {
			conv.checkstate();
		}
	    balance1::compute(count, input1, output0,output1);
	    //(void)memcpy( output0, input1, sizeof(float)*count);
	    (void)memcpy(get_frame, output0, sizeof(float)*count);
        (void)memcpy(get_frame1, output1, sizeof(float)*count);
		break;


		// ------- zeroize buffers
	case ZEROIZE_BUFFERS:
	default:

		if (conv.is_runnable()) {
			conv.checkstate();
		}

		// no need of loop.

		(void)memset(output0, 0, count*sizeof(float));
		(void)memset(output1, 0, count*sizeof(float));
        (void)memset(get_frame, 0, count*sizeof(float));
		(void)memset(get_frame1, 0, count*sizeof(float));
		break;
	}
}

void compute (int count, float* input, float* output0)
{
	// retrieve engine state
	const GxEngineState estate = (GxEngineState)checky;

	//------------ determine processing type
	unsigned short process_type = ZEROIZE_BUFFERS;

	if (gx_jack::NO_CONNECTION == 0) { // ports connected
		switch (estate) {
		case kEngineOn:
			process_type = PROCESS_BUFFERS;
			break;

		case kEngineBypass:
			process_type = JUSTCOPY_BUFFERS;
			break;

		default: // engine off or whatever: zeroize
			break;
		}
	}

	//------------ main processing routine
	switch (process_type) {

	case PROCESS_BUFFERS:
		process_buffers(count, input, output0);
		break;

		// --------- just copy input to outputs
	case JUSTCOPY_BUFFERS:
		if (conv.is_runnable()) {
			conv.checkstate();
		}
	   // balance1::compute(count, input, output0);
	   (void)memcpy( output0, input, sizeof(float)*count);
	    //(void)memcpy(get_frame, output0, sizeof(float)*count);
        //(void)memcpy(get_frame1, output1, sizeof(float)*count);
		break;


		// ------- zeroize buffers
	case ZEROIZE_BUFFERS:
	default:

		if (conv.is_runnable()) {
			conv.checkstate();
		}

		// no need of loop.

		(void)memset(output0, 0, count*sizeof(float));
		//(void)memset(output1, 0, count*sizeof(float));
        (void)memset(get_frame, 0, count*sizeof(float));
		(void)memset(get_frame1, 0, count*sizeof(float));
		break;
	}
}

/****************************************************************
 ** this is the guitarix audio engine
 */

void process_buffers(int count, float* input, float* output0)
{
	int tuner_on = gx_gui::shownote + (int)isMidiOn() + 1;
	if (tuner_on > 0) {
		if (gx_gui::shownote == 0) {
			gx_gui::shownote = -1;
		} else {
			pitch_tracker.add(count, input);
			//moving_filter(input, checkfreq, count);
			(void)memcpy(checkfreq, input, sizeof(float)*count);
		}
	}
	memcpy(output0, input, count*sizeof(float));
	IF_HS(HighShelf::compute(count, input, output0));

    if (audio.feq) {
	    if(audio.witcheq)selecteq::compute(count, output0, output0);
	    else eq::compute(count, output0, output0);
    }
	if (audio.fnoise_g) {
		feed::ngate = noise_gate(count,output0, feed::ngate);
    } else {
		feed::ngate = 1;
    }
    if (audio.fng) {
	    noise_shaper::compute(count, output0, output0);
    }
    if (audio.fcheckbox1 && !audio.famp2) {
	    preamp::compute(count, output0, output0);
    }
    if (audio.fbiquad) {
	    biquad::compute(count, output0, output0);
    }
    EXPERIMENTAL_PROCESSING;

    // *** Start (maybe) oversampled processing ***
    static int fupsample_old = 0; // startup always initialises with SR
    static int t_upsample_old = 0;
    static int t_upsample = 0;
    int ovs_count, ovs_sr;
    float *ovs_buffer;
    if (audio.fupsample) {
		// *oversample
        t_upsample = min(8,audio.upsample_mode+1);
        if (t_upsample != t_upsample_old) {
            t_upsample_old = t_upsample;
            fupsample_old = audio.fupsample;
            //FIXME non-rt
            resampTube.setup(gx_jack::jack_sr, t_upsample);

            amp2::init(t_upsample * gx_jack::jack_sr);
            osc_tube::init(t_upsample * gx_jack::jack_sr);

            resampDist.setup(gx_jack::jack_sr, t_upsample);
            distortion1::init(t_upsample * gx_jack::jack_sr);
            distortion::init(t_upsample * gx_jack::jack_sr);
        }
	    resampTube.up(count, output0, oversample);
	    ovs_sr = t_upsample * gx_jack::jack_sr;
	    ovs_count = t_upsample * count;
	    ovs_buffer = oversample;
    } else {
	    ovs_sr = gx_jack::jack_sr;
	    ovs_count = count;
	    ovs_buffer = output0;
    }
    if (audio.fupsample != fupsample_old) {
	    fupsample_old = audio.fupsample;

        amp2::init(ovs_sr);
        osc_tube::init(ovs_sr);

	    distortion1::init(ovs_sr);
	    distortion::init(ovs_sr);
    }
    if (audio.antialis0) {
	    AntiAlias::compute(ovs_count, ovs_buffer, ovs_buffer);
    }
    if(audio.famp2) {
        amp2::compute(ovs_count, ovs_buffer, ovs_buffer);
    } else {
        if (audio.ftube) {
            tube::compute(ovs_count, ovs_buffer, ovs_buffer);
        }
        if (audio.ftube3) {
            osc_tube::compute(ovs_count, ovs_buffer, ovs_buffer);
            //reso_tube::compute(ovs_count, ovs_buffer, ovs_buffer);
        }
        if (audio.fprdr) {
            drive::compute(ovs_count, ovs_buffer, ovs_buffer);
        }
    }
    if (audio.fupsample) {
	    resampTube.down(count, oversample, output0);
    }
    //*** End (maybe) oversampled processing ***

    if (audio.fconvolve) {
	    convolver_filter(output0, output0, count, (unsigned int)audio.convolvefilter);
    }
    inputgain::compute(count, output0, output0);
    tonestack::compute(count, output0, output0);
    if (audio.fresoon && !audio.famp2) {
	    tubevibrato::compute(count, output0, output0);
    }
    if(audio.fcab) {
        if (!cab_conv.compute(count, output0))
            cout << "overload" << endl;
            //FIXME error message??
    }

    for (int m = 0; m < 8; m++) {
	    if (audio.posit0 == m && audio.fcheckbox5 && !audio.fautowah) {
		    crybaby::compute(count, output0, output0);
	    } else if (audio.posit0 == m && audio.fcheckbox5 && audio.fautowah) {
		    autowah::compute(count, output0, output0);
	    } else if (audio.posit5 == m && audio.fcheckboxcom1) {
		    compressor::compute(count, output0, output0);
	    } else if (audio.posit1 == m && audio.foverdrive4) {
		    overdrive::compute(count, output0, output0);
	    } else if (audio.posit2 == m && audio.fcheckbox4) {
	        if (audio.fupsample) {
                // 2*oversample
                //over_sample(count, output0, oversample);
                resampDist.up(count, output0, oversample);
                if(audio.witchdistortion) distortion1::compute(ovs_count, oversample, oversample);
                else distortion::compute(ovs_count, oversample, oversample);
                resampDist.down(count, oversample, output0);
                //down_sample(count, oversample, output0);
	        } else {
                if(audio.witchdistortion) distortion1::compute(count, output0, output0);
                else distortion::compute(count, output0, output0);
	        }
	    } else if (audio.posit3 == m && audio.fcheckbox6) {
		    freeverb::compute(count, output0, output0);
	    } else if (audio.posit6 == m && audio.fcheckbox7) {
		    echo::compute(count, output0, output0);
	    } else if (audio.posit4 == m && audio.fcheckbox8) {
		    impulseresponse::compute(count, output0, output0);
	    } else if (audio.posit7 == m && audio.fdelay) {
		    delay::compute(count, output0, output0);
	    }
    }

    // Multibandfilter
    if (audio.fmultifilter) {
		multifilter::compute(count, output0, output0);
	}

    outputgain::compute(count, output0, output0);

    if (audio.fboost) {
	    bassbooster::compute(count, output0, output0);
    }
    if(audio.famp2) {
        stage3::compute(count, output0, output0);
    } else if (audio.ftube3e) {
	    tube3::compute(count, output0, output0);
    }
    if (audio.fsloop) {
	    sloop::compute(count, output0, output0);
    }
}
void process_insert_buffers (int count, float* input1, float* output0, float* output1)
{
    memcpy(output0, input1, count*sizeof(float));
    feed::compute(count, output0, output0, output1);

    if (audio.fchorus) {
	    chorus::compute(count, output0, output1, output0, output1);
    }
    if (audio.fflanger) {
	    flanger::compute(count, output0, output1, output0, output1);
    }

    if (conv.is_runnable()) {
	    // reuse oversampling buffer
	    float *conv_out0 = oversample;
	    float *conv_out1 = oversample+count;
	    if (!conv.compute(count, output0, output1, conv_out0, conv_out1)) {
		    gx_jconv::GxJConvSettings::checkbutton7 = 0;
		    cout << "overload" << endl;
		    //FIXME error message??
	    } else {
		    jconv_post::compute(count, output0, output1, conv_out0, conv_out1, output0, output1);
	    }
    } else {
	    balance::compute(count, output0, output1, output0, output1);
    }
    if (audio.fmoog) {
        moog::compute(count, output0, output1, output0, output1);
    }
	(void)memcpy(get_frame, output0, sizeof(float)*count);
	(void)memcpy(get_frame1, output1, sizeof(float)*count);
}

} // namespace gx_engine

