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
#include <errno.h>
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

inline void registerNonMidiParam(const char*a, bool*c, bool d, float std=false)
{
	gx_gui::parameter_map.insert(new gx_gui::BoolParameter(a,"",gx_gui::Parameter::None,d,*c,std,0,false));
}

// should be int
inline void registerEnumParam(const char*a,const char*b,const char** vl,float*c,int std=0,bool exp=false)
{
	gx_gui::parameter_map.insert(new gx_gui::FloatEnumParameter(a,b,vl,true,*c,std,true,exp));
}

inline void registerEnumParam(const char*a,const char*b,const char** vl, int*c,int std=0,bool exp=false)
{
	gx_gui::parameter_map.insert(new gx_gui::EnumParameter(a,b,vl,true,*c,std,true,exp));
}

/****************************************************************
 ** definitions for code generated with faust / dsp2cc
 */

#include "gx_faust_includes.cc"

/****************************************************************
 ** register audio variables to paramtable
 */

void AudioVariables::register_parameter()
{
	gx_gui::registerParam("amp.bass_boost.on_off", "on/off", &fboost, 0);

	gx_gui::registerParam("jconv.on_off", "Run", &gx_jconv::GxJConvSettings::checkbutton7);

	gx_gui::registerParam("cab.on_off", "Cab-ImpResp", &fcab,0);
	static const char *tonestack_model[] = {"default","Bassman","Twin Reverb","Princeton","JCM-800","JCM-2000","M-Lead","M2199","AC-30","Off",0};
	registerEnumParam("amp.tonestack.select","select",tonestack_model,&tonestack, 0);

	// user interface options
	registerNonMidiParam("ui.latency_nowarn", &fwarn, false, 0);
	registerNonMidiParam("ui.skin", &fskin, false, 0, 0, 100);

}

AudioVariables audio;


/****************************************************************
 **  this is the process callback called from jack
 **
 ***************************************************************/
void compute_insert (int count, float* input1, float* output0, float* output1)
{
// retrieve engine state
	const GxEngineState estate = checky;

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
		break;
	}
}

void compute (int count, float* input, float* output0)
{
	// retrieve engine state
	const GxEngineState estate = checky;

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
		break;


		// ------- zeroize buffers
	case ZEROIZE_BUFFERS:
	default:

		if (conv.is_runnable()) {
			conv.checkstate();
		}

		// no need of loop.

		(void)memset(output0, 0, count*sizeof(float));
  		break;
	}
}

/****************************************************************
 ** this is the gx_head audio engine
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

    gxdistortion::compute(count, output0, output0);

    gxamp::compute(count, output0, output0);

    switch (audio.tonestack) {
    case 0: //"default"
	    tonestack_default::compute(count, output0, output0);
	    break;
    case 1: //"Bassman"
	    tonestack_bassman::compute(count, output0, output0);
	    break;
    case 2: //"Twin Reverb"
	    tonestack_twin::compute(count, output0, output0);
	    break;
    case 3: //"Princeton"
	    tonestack_princeton::compute(count, output0, output0);
	    break;
    case 4: //"JCM-800"
	    tonestack_jcm800::compute(count, output0, output0);
	    break;
    case 5: //"JCM-2000"
	    tonestack_jcm2000::compute(count, output0, output0);
	    break;
    case 6: //"M-Lead"
	    tonestack_mlead::compute(count, output0, output0);
	    break;
    case 7: //"M2199"
	    tonestack_m2199::compute(count, output0, output0);
	    break;
    case 8: //"AC-30"
	    tonestack_ac30::compute(count, output0, output0);
	    break;
    case 9: //"Off"
	    break;
    }

    if(audio.fcab) {
        if (!cab_conv.compute(count, output0))
            cout << "overload" << endl;
            //FIXME error message??
    }

    if (audio.fboost) {
	    bassbooster::compute(count, output0, output0);
    }

}

void process_insert_buffers (int count, float* input1, float* output0, float* output1)
{
    memcpy(output0, input1, count*sizeof(float));
    gxfeed::compute(count, output0, output0, output1);

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
    }
	(void)memcpy(get_frame, output0, sizeof(float)*count);
	(void)memcpy(get_frame1, output1, sizeof(float)*count);
}

} // namespace gx_engine

