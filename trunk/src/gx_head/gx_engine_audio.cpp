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
#include <glibmm/i18n.h>

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
	gx_gui::parameter_map.insert(new gx_gui::FloatEnumParameter(a,b,vl,true,*c,std,true,exp)); //false == no_midi_var
}

inline void registerEnumParam(const char*a,const char*b,const char** vl, int*c,int std=0,bool exp=false)
{
	gx_gui::parameter_map.insert(new gx_gui::EnumParameter(a,b,vl,true,*c,std,true,exp)); //false == no_midi_var
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
	static const char *on_off = N_("on/off");
	gx_gui::registerParam("amp.bass_boost.on_off", on_off, &fboost, 0);
	gx_gui::registerParam("compressor.on_off", on_off, &fcheckboxcom1, 0);
	gx_gui::registerParam("jconv.on_off", "Run", &gx_jconv::GxJConvSettings::checkbutton7);
	gx_gui::registerParam("crybaby.on_off", on_off, &fcheckbox5, 0);
	gx_gui::registerParam("cab.on_off", "Cab-ImpResp", &fcab,0);
	gx_gui::registerParam("overdrive.on_off", on_off, &foverdrive4, 0);
	gx_gui::registerParam("gx_distortion.on_off", on_off, &fcheckbox4, 0);
	gx_gui::registerParam("freeverb.on_off", on_off, &fcheckbox6, 0);
	gx_gui::registerParam("IR.on_off", on_off, &fcheckbox8, 0);
	gx_gui::registerParam("echo.on_off", on_off, (float*) &fcheckbox7, 0.);
	gx_gui::registerParam("delay.on_off", on_off, (float*) &fdelay, 0.);
	gx_gui::registerParam("chorus.on_off", on_off, (float*) &fchorus, 0.);
	gx_gui::registerParam("eqs.on_off", on_off, &feq, 0);
	gx_gui::registerParam("moog.on_off", on_off, &fmoog, 0);
	gx_gui::registerParam("biquad.on_off", "on_off", &fbiquad, 0);
	gx_gui::registerParam("flanger.on_off", on_off, &fflanger, 0);
	//gx_gui::registerParam("SampleLooper.on_off", "on_off", (float*) &fsloop, 0.);
	gx_gui::registerParam("phaser.on_off", on_off, (float*) &fphaser, 0.);
	gx_gui::registerParam("shaper.on_off", on_off, &fng, 0);
	gx_gui::registerParam("low_highpass.on_off", on_off, &flh, 0);
	gx_gui::registerParam("stereodelay.on_off", on_off,(float*) &fsd, 0);
	gx_gui::registerParam("stereoecho.on_off", on_off,(float*) &fse, 0);
	gx_gui::registerParam("midi_out.on_off", on_off, &fmi, 0);
	gx_gui::registerParam("oscilloscope.on_off", on_off, &fwv, 0);
	gx_gui::registerParam("ampmodul.on_off", on_off, &famp, 0);
	gx_gui::registerParam("noise_gate.on_off", "on/off", &fnoise_g, 0);
	gx_gui::registerParam("amp.on_off", on_off, &fampout, 0);
	gx_gui::registerParam("amp.clip.on_off", on_off, &ftube, 0);
	gx_gui::registerParam("tonemodul.on_off", on_off, &ftone, 0);
	gx_gui::registerParam("tremolo.on_off", on_off, &ftremolo, 0);
	
	gx_gui::registerParam("noise_gate.threshold", "Threshold", &fnglevel, 0.017f, 0.01f, 0.31f, 0.001f);
	
	static const char *tonestack_model[] = {N_("default"),N_("Bassman"),N_("Twin Reverb"),N_("Princeton"),N_("JCM-800"),N_("JCM-2000"),N_("M-Lead"),N_("M2199"),N_("AC-30"),N_("Off"),0};
	registerEnumParam("amp.tonestack.select","select",tonestack_model,&tonestack, 0);
	
	static const char *post_pre[] = {N_("post"),N_("pre"),0};
	registerEnumParam("compressor.pp","select",post_pre,&compressorpp, 0);
	registerEnumParam("crybaby.pp","select",post_pre,&crybabypp, 0);
	registerEnumParam("overdrive.pp","select",post_pre,&overdrivepp, 0);
	registerEnumParam("gx_distortion.pp","select",post_pre,&distortionpp, 0);
	registerEnumParam("freeverb.pp","select",post_pre,&freeverbpp, 0);
	registerEnumParam("IR.pp","select",post_pre,&IRpp, 0);
	registerEnumParam("echo.pp","select",post_pre,&echopp, 0);
	registerEnumParam("delay.pp","select",post_pre,&delaypp, 0);
	registerEnumParam("eqs.pp","select",post_pre,&eqpp, 0);
	registerEnumParam("low_highpass.pp","select",post_pre,&lhpp, 0);
	registerEnumParam("oscilloscope.pp","select",post_pre,&wvpp, 0);
	registerEnumParam("biquad.pp","select",post_pre,&bipp, 0);
	registerEnumParam("tremolo.pp","select",post_pre,&trpp, 0);
	
	static const char *crybaby_autowah[] = {N_("manual"),N_("auto"),0};
	registerEnumParam("crybaby.autowah", "select", crybaby_autowah, &fautowah, 0);
	
	//static const char *eqt_onetwo[] = {"fixed","scale",0};
	//registerEnumParam("eqt.onetwo", "select", eqt_onetwo, &witcheq, 0);
	
	registerNonMidiParam("compressor.position", &posit5, true, 6, 1, 14);
	registerNonMidiParam("crybaby.position", &posit0, true, 3, 1, 14);
	registerNonMidiParam("overdrive.position", &posit1, true, 7, 1, 14);
	registerNonMidiParam("gx_distortion.position", &posit2, true, 4, 1, 14);
	registerNonMidiParam("freeverb.position", &posit3, true, 10, 1, 14);
	registerNonMidiParam("IR.position", &posit4, true, 5, 1, 14);
	registerNonMidiParam("echo.position", &posit6, true, 8, 1, 14);
	registerNonMidiParam("delay.position", &posit7, true, 9, 1, 14);
	registerNonMidiParam("eqs.position", &posit10, true, 2, 1, 14);
	registerNonMidiParam("chorus.position", &posit8, true, 1, 1, 10);
	registerNonMidiParam("flanger.position", &posit9, true, 2, 1, 10);
	registerNonMidiParam("moog.position", &posit11, true, 6, 1, 10);
	registerNonMidiParam("phaser.position", &posit12, true, 3, 1, 10);
	registerNonMidiParam("low_highpass.position", &posit14, true, 1, 1, 14);
	registerNonMidiParam("stereodelay.position", &posit15, true, 4, 1, 10);
	registerNonMidiParam("stereoecho.position", &posit16, true, 5, 1, 10);
	registerNonMidiParam("oscilloscope.position", &posit17, true, 11, 1, 14);
	registerNonMidiParam("biquad.position", &posit18, true, 12, 1, 14);
	registerNonMidiParam("midi_out.position", &posit00, true, 14, 1, 14);
	registerNonMidiParam("ampmodul.position", &posit19, true, 7, 1, 10);
	registerNonMidiParam("tonemodul.position", &posit20, true, 8, 1, 10);
	registerNonMidiParam("tremolo.position", &posit21, true, 13, 1, 14);
	
	registerNonMidiParam("compressor.dialog", &fdialogbox8, false);
	registerNonMidiParam("crybaby.dialog", &fdialogbox4, false);
	registerNonMidiParam("gx_distortion.dialog", &fdialogbox1, false);
	registerNonMidiParam("freeverb.dialog", &fdialogbox2, false);
	registerNonMidiParam("IR.dialog", &fdialogbox3, false);
	registerNonMidiParam("chorus.dialog", &fchorusbox, false);
	registerNonMidiParam("eq.dialog", &fdialogbox_eq, false);
	registerNonMidiParam("eqs.dialog", &fdialogbox_eqs, false);
	registerNonMidiParam("MultiBandFilter.dialog", &fdialogbox_mbf, false);
	registerNonMidiParam("moog.dialog", &fdialogbox_moo, false);
	registerNonMidiParam("biquad.dialog", &fbiquadbox, false);
	registerNonMidiParam("flanger.dialog", &fflangerbox, false);
	registerNonMidiParam("echo.dialog", &fdialogbox_echo, false);
	registerNonMidiParam("delay.dialog", &fdialogbox_delay, false);
	registerNonMidiParam("overdrive.dialog", &fdialogbox_ovd, false);
	registerNonMidiParam("phaser.dialog", &fdialogbox_pha, false);
	registerNonMidiParam("low_highpass.dialog", &fdialogbox_lh, false);
	registerNonMidiParam("stereodelay.dialog", &fdialogbox_sd, false);
	registerNonMidiParam("stereoecho.dialog", &fdialogbox_se, false);
	registerNonMidiParam("midi_out.dialog", &fdialogbox6, false);
	registerNonMidiParam("oscilloscope.dialog", &fdialogbox_wv, false);
	registerNonMidiParam("ampmodul.dialog", &fampmodul, false);
	registerNonMidiParam("tonemodul.dialog", &ftonemodule, false);
	registerNonMidiParam("tremolo.dialog", &ftremolo_dialog, false);
	
	registerNonMidiParam("system.waveview", &viv, false);
	registerNonMidiParam("midi_out.midistat", &midistat, false);
	registerNonMidiParam("midi_out.midistat1", &midistat1, false);
	registerNonMidiParam("midi_out.midistat2", &midistat2, false);
	registerNonMidiParam("midi_out.midistat3", &midistat3, false);

	// user interface options
	registerNonMidiParam("ui.latency_nowarn", &fwarn, false, 0);
	registerNonMidiParam("ui.skin", &fskin, false, 0, 0, 100);

}

AudioVariables audio;

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
	if(audio.fmi && !isMidiOn()) turnOnMidi();
	else if(!audio.fmi && isMidiOn()) turnOffMidi();
	
	if(audio.fwv != audio.fwv_on) {
		(void)memset(result, 0, count*sizeof(float));
		audio.fwv_on = audio.fwv;
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
		if(audio.fwv)(void)memset(result, 0, count*sizeof(float));
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
	
	if (audio.fnoise_g) {
		noisegate::ngate = noise_gate(count,output0, noisegate::ngate);
    } else {
		noisegate::ngate = 1;
    }
	
	if (audio.fng) {
	    noise_shaper::compute(count, output0, output0);
    }
	  
	for (int m = 1; m < audio.mono_plug_counter; m++) {
	    if (audio.posit0 == m && audio.fcheckbox5 && !audio.fautowah && audio.crybabypp) {
		    crybaby::compute(count, output0, output0);
	    } else if (audio.posit0 == m && audio.fcheckbox5 && audio.fautowah && audio.crybabypp) {
		    autowah::compute(count, output0, output0);
	    } else if (audio.posit5 == m && audio.fcheckboxcom1 && audio.compressorpp) {
		    compressor::compute(count, output0, output0);
	    } else if (audio.posit1 == m && audio.foverdrive4 && audio.overdrivepp) {
		    overdrive::compute(count, output0, output0);
	    } else if (audio.posit2 == m && audio.fcheckbox4 && audio.distortionpp) {
	         gx_distortion::compute(count, output0, output0);
	    } else if (audio.posit3 == m && audio.fcheckbox6 && audio.freeverbpp) {
		    freeverb::compute(count, output0, output0);
	    } else if (audio.posit6 == m && audio.fcheckbox7 && echo::is_inited() && audio.echopp) {
		    echo::compute(count, output0, output0);
	    } else if (audio.posit4 == m && audio.fcheckbox8 && audio.IRpp) {
		    impulseresponse::compute(count, output0, output0);
	    } else if (audio.posit7 == m && audio.fdelay && delay::is_inited() && audio.delaypp) {
		    delay::compute(count, output0, output0);
	    } else if (audio.posit10 == m && audio.feq && audio.eqpp) {
		    selecteq::compute(count, output0, output0);
	    } else if (audio.posit14 == m && audio.flh && audio.lhpp) {
		    low_high_pass::compute(count, output0, output0);
	    } else if (audio.posit17 == m && audio.fwv && audio.wvpp) {
		    (void)memcpy(result, output0, sizeof(float)*count);
	    } else if (audio.posit18 == m && audio.fbiquad && audio.bipp) {
		    biquad::compute(count, output0, output0);
	    } else if (audio.posit21 == m && audio.ftremolo && audio.trpp) {
		    tremolo::compute(count, output0, output0);
	    } 

    }


    gxdistortion::compute(count, output0, output0);
	switch (audio.gxtube) {
	case 0: //"never"
		gxamp::compute(count, output0, output0);
		break;
	case 1: //"default"
		gxamp::compute(count, output0, output0);
		break;
	case 2: 
		gxamp3::compute(count, output0, output0);
		break;
	case 3: 
		gxamp2::compute(count, output0, output0);
		break;
	case 4: 
		gxamp4::compute(count, output0, output0);
		break;
	case 5: 
		gxamp5::compute(count, output0, output0);
		break;
	}
	
	if (audio.ftube) {
        softclip::compute(count, output0, output0);
    }
    
    for (int m = 1; m < audio.mono_plug_counter; m++) {
	    if (audio.posit0 == m && audio.fcheckbox5 && !audio.fautowah && !audio.crybabypp) {
		    crybaby::compute(count, output0, output0);
	    } else if (audio.posit0 == m && audio.fcheckbox5 && audio.fautowah && !audio.crybabypp) {
		    autowah::compute(count, output0, output0);
	    } else if (audio.posit5 == m && audio.fcheckboxcom1 && !audio.compressorpp) {
		    compressor::compute(count, output0, output0);
	    } else if (audio.posit1 == m && audio.foverdrive4 && !audio.overdrivepp) {
		    overdrive::compute(count, output0, output0);
	    } else if (audio.posit2 == m && audio.fcheckbox4 && !audio.distortionpp) {
	         gx_distortion::compute(count, output0, output0);
	    } else if (audio.posit3 == m && audio.fcheckbox6 && !audio.freeverbpp) {
		    freeverb::compute(count, output0, output0);
	    } else if (audio.posit6 == m && audio.fcheckbox7 && echo::is_inited() && !audio.echopp) {
		    echo::compute(count, output0, output0);
	    } else if (audio.posit4 == m && audio.fcheckbox8 && !audio.IRpp) {
		    impulseresponse::compute(count, output0, output0);
	    } else if (audio.posit7 == m && audio.fdelay && delay::is_inited() && !audio.delaypp) {
		    delay::compute(count, output0, output0);
	    } else if (audio.posit10 == m && audio.feq && !audio.eqpp) {
		    selecteq::compute(count, output0, output0);
	    } else if (audio.posit14 == m && audio.flh && !audio.lhpp) {
		    low_high_pass::compute(count, output0, output0);
	    } else if (audio.posit17 == m && audio.fwv && !audio.wvpp) {
		    (void)memcpy(result, output0, sizeof(float)*count);
	    } else if (audio.posit18 == m && audio.fbiquad && !audio.bipp) {
		    biquad::compute(count, output0, output0);
	    } else if (audio.posit21 == m && audio.ftremolo && !audio.trpp) {
		    tremolo::compute(count, output0, output0);
	    } 
    }

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
    
    if (audio.fampout) {
        gx_ampout::compute(count, output0, output0);
    }
    
    if (audio.fnoise_g) {
		noisegate::compute(count,output0, output0);
    }

}

void process_insert_buffers (int count, float* input1, float* output0, float* output1)
{
	
    memcpy(output0, input1, count*sizeof(float));
    gxfeed::compute(count, output0, output0, output1);
    
    for (int m = 1; m < audio.stereo_plug_counter; m++) {
		if (audio.posit8 == m && audio.fchorus && chorus::is_inited()) {
			chorus::compute(count, output0, output1, output0, output1);
		} else if (audio.posit9 == m && audio.fflanger) {
			flanger::compute(count, output0, output1, output0, output1);
		} else if (audio.posit11 == m && audio.fmoog) {
			moog::compute(count, output0, output1, output0, output1);
		} else if (audio.posit12 == m && audio.fphaser) {
			phaser::compute(count, output0, output1, output0, output1);
		} else if (audio.posit15 == m && audio.fsd && stereodelay::is_inited()) {
			stereodelay::compute(count, output0, output1, output0, output1);
		}else if (audio.posit16 == m && audio.fse && stereoecho::is_inited()) {
			stereoecho::compute(count, output0, output1, output0, output1);
		}else if (audio.posit19 == m && audio.famp ) {
			gx_ampmodul::compute(count, output0, output1, output0, output1);
		}else if (audio.posit20 == m && audio.ftone ) {
			tonecontroll::compute(count, output0, output1, output0, output1);
		}
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
    }
    gx_outputlevel::compute(count, output0, output1, output0, output1);
	(void)memcpy(get_frame, output0, sizeof(float)*count);
	(void)memcpy(get_frame1, output1, sizeof(float)*count);
}

} // namespace gx_engine

