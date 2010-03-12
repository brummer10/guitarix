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

#include <assert.h>
#include <cstring>
#include <list>
#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include <cmath>
#include <gtk/gtk.h>
#include <jack/jack.h>
#include <jack/midiport.h>
#include <sndfile.h>
using namespace std;

#include "guitarix.h"

namespace gx_engine {
// static convolution filters
static float filter0[45] = {0.0222473, 0.0253601, 0.0159607, 0.0184326, 0.0240784,
                            0.02771, 0.0483398, 0.0802917, 0.12915, 0.196259, 0.259521,
                            0.334656, 0.398376, 0.421448, 0.401306, 0.340759, 0.216827,
                            0.058197, -0.117432, -0.287354, -0.438507, -0.540161,
                            0.0583801, 0.0596924, 0.0499573, 0.0406799, 0.0445862,
                            0.0334473, 0.0296021, 0.022644, 0.0142212, 0.0027771,
                            -0.00805664, -0.0206909, -0.0270386, -0.0247498,
                            -0.0259399, -0.0132751, 0.216827, 0.058197, -0.117432,
                            -0.287354, -0.438507, -0.540161, -0.438507
};

static float filter1[45]= {0.19,0.15,0.12,0.05,-0.08,-0.15,-0.18,-0.12,-0.05,0.07,
                           0.12,0.16,0.14,0.11,0.05,0.01,0.04,0.12,0.14,0.08,0.02,
                           -0.01,0.8,0.19,0.15,0.12,0.05,-0.08,-0.15,-0.18,-0.12,
                           -0.05,0.07,0.12,0.16,0.14,0.11,0.05,0.01,0.04,0.12,0.14,
                           0.08,0.02,-0.01
};

static float filter2[45]= {0.19265,0.19265,0.19265,0.19265,0.19265,0.19265,0.19265,
                           0.19265,0.19265,0.19265,0.19265,0.19265,0.19265,0.19265,
                           0.19265,0.19265,0.19265,0.19265,0.19265,0.19265,0.19265,
                           0.19265,0.19265,0.19265,0.19265,0.19265,0.19265,0.19265,
                           0.19265,0.19265,0.19265,0.19265,0.19265,0.19265,0.19265,
                           0.19265,0.19265,0.19265,0.19265,0.19265,0.19265,0.19265,
                           0.19265,0.19265,0.19265
};

static float filter3[45]= {-0.1111851,-0.1811851,-0.1811851,-0.1811851,-0.1811851,
                           -0.1111851,-0.1811851,-0.1811851,-0.1811851,-0.1811851,
                           -0.1111851,-0.1811851,-0.1811851,-0.1811851,-0.1811851,
                           -0.1111851,-0.1811851,-0.1811851,-0.1811851,-0.1811851,
                           -0.1111851,-0.1811851,-0.1811851,-0.1811851,-0.1811851,
                           -0.1111851,-0.1811851,-0.1811851,-0.1811851,-0.1811851,
                           -0.1111851,-0.1811851,-0.1811851,-0.1811851,-0.1811851,
                           -0.1111851,-0.1811851,-0.1811851,-0.1811851,-0.1811851,
                           -0.1111851,-0.1811851,-0.1811851,-0.1811851,-0.1811851
};

static float filter4[45]= {-0.0400391, 0.0591736, 0.0404663, 0.065155, 0.065094,
                           0.0524597, 0.0325012, -0.0254211, -0.0797119, -0.118561,
                           -0.192902, -0.1763, -0.169861, -0.0974426, 0.0567932,
                           0.207458, 0.468079, 0.637085, 0.786072, 0.911835, 0.868347,
                           0.873199, 0.720001, 0.598633, 0.416168, 0.24173, 0.0201416,
                           -0.177277, -0.397614, -0.538208, -0.64505, -0.582642,
                           -0.43161, -0.0495605, 0.361603, 0.724304, 0.981934, 0.953583,
                           0.770233, 0.515625, 0.21106, -0.0998535, -0.162781,
                           -0.171173, 0.042572
};

static float filter5[45]= {0.000610352, 0.00604248, 0.0153809, 0.0246277, 0.0340576,
                           0.0418701, 0.0494385, 0.059082, 0.069458, 0.0871277,
                           0.0636292, -0.0269165, -0.208862, -0.453522, -0.7146,
                           -0.915344, -0.999939, -0.938538, -0.752472, -0.494629,
                           -0.240662, -0.0461426, 0.0594788, 0.0810852, 0.0621643,
                           0.0324707, 0.00180054, -0.0244751, -0.0487061,
                           -0.0654602, -0.0780334, -0.0823669, -0.0776978, -0.0677185,
                           -0.0529175, -0.0342102, -0.0135803, 0.00839233, 0.0301208,
                           0.053833, 0.0252563, 0.0058252, 0.002138, 0.0012851, 0.0009252
};

static float filter6[45]= {-0.0573425, 0.0429382, 0.1698, 0.325623, 0.496429,
                           0.673615, 0.831726, 0.948944, 0.999939, 0.962616,
                           0.822021, 0.57666, 0.25769, -0.091156, -0.393341,
                           -0.568726, -0.545746, -0.315643, 0.052948, 0.422028,
                           0.634552, 0.612579, 0.383606, 0.0856323, -0.142151,
                           -0.233185, -0.185608, -0.0593262, 0.0916748, 0.228333,
                           0.302521, 0.295105, 0.226959, 0.130402, 0.0578308,
                           0.0231018, 0.0189514, 0.0299988, 0.0453186, 0.0602722,
                           0.079834, 0.092804, 0.0980225, 0.0977783, 0.0834351
};

// denormal prevention is needed in the distortion unit for the low/high/cut part.
inline void GxEngine::add_dc (float& val)
{
	static const float anti_denormal = 1e-20;
	val += anti_denormal;
}

inline float GxEngine::my2powf(float y)
{
	return exp(log_2 * y);
}

inline float GxEngine::my4powf(float y)
{
	return exp(log_4 * y);
}

inline float GxEngine::clip (float x, float a)
{
	float x1,x2;
	float b = -a;

	x1 = fabs (x-a);
	x2 = fabs (x-b);
	x = x1 + (a+b);
	x -= x2;
	x *= 0.5;

	return x;
}

// the hard_cut unit run on sample base
inline float GxEngine::hard_cut(float in, float threshold)
{
	if ( in > threshold) {
		in = threshold;
	} else if ( in < -threshold) {
		in = -threshold;
	}

	return in;
}

// foldback distortion, run on sample base
inline float GxEngine::foldback(float in, float threshold)
{
	if (threshold == 0) threshold = 0.01f;

	if (fabs(in) > threshold) {
		in = fabs(fabs(fmod(in - threshold, threshold*4)) - threshold*2) - threshold;
	}
	return in;
}

// it isn't normalize, it's more a waveshaper funktion
inline float GxEngine::normalize(float in, float atan_shape, float shape)
{
	return atan_shape * atan(in*shape);
}


inline float GxEngine::sigmoid(float x)
{
	return x*(1.5f - 0.5f*x*x);
}

inline float GxEngine::saturate(float x, float t)
{
	if (fabs(x)<t)
		return x;
	else {
		if (x > 0.f)
			return t + (1.f-t)*sigmoid((x-t)/((1-t)*1.5f));
		else
			return -(t + (1.f-t)*sigmoid((-x-t)/((1-t)*1.5f)));
	}
}

// tube unit to run on sample base, it's unused for now, dont know if we need it any more
inline float GxEngine::valve(float in, float out)
{
	float a = 2.000 ;
	float b = 1.000 ;

	if ( in >= 0.0 ) {
		out = a * in - b * in * in;
	} else {
		out = a * in + b * in * in;
	}

	return out;
}

inline void GxEngine::moving_filter(float** input, float** output, int sf)
{
	float *in = input[0];
	float * out = output[0];

	*out++ = (in[0]+in[1])*0.5;

	for (int i=1; i<sf-1; i++) {
		*out++ = (in[i-1]+in[i]+in[i+1])*0.3333334f;
	}
	*out++ = (in[sf]+in[sf-1])*0.5;

}

inline void GxEngine::convolver_filter(float** input, float** output, int sf, int iconvolvefilter)
{


	float * in = input[0];
	/** disable fft need some fix for work prop **/
	/*  float * out = output[0];

	    for (int i = 0; i < sf; i++ )
	    {
	    fftin[i][0] = *in++;
	    fftin[i][1] = 0;
	    }


	    fftw_execute(p);
	    // Set result to zero:
	    int j = 0;
	    for (int i = 0; i < sf; i++ )
	    {
	    fftin1[i][0] = filter[j];
	    fftin1[i][1] = 0;
	    j++;
	    if(j>45)j=0;
	    }
	    fftw_execute(pf);
	    for (int i = 0; i < sf; i++ )
	    {
	    fftout[i][0] *= 1.3666  ;
	    fftout[i][1] *= 1.3322  ;
	    }
	    fftw_execute(p1);
	    for (int i = 0; i < sf; i++ )
	    {
	    *out++ = fftresult[i][0] /sf  ;

	    }*/
	static float*filter_use = &filter0[0];
	switch (iconvolvefilter) {
	case 0:
		filter_use = &filter0[0];
		break;
	case 1:
		filter_use = &filter1[0];
		break;
	case 2:
		filter_use = &filter2[0];
		break;
	case 3:
		filter_use = &filter3[0];
		break;
	case 4:
		filter_use = &filter4[0];
		break;
	case 5:
		filter_use = &filter5[0];
		break;
	case 6:
		filter_use = &filter6[0];
		break;
	default:
		filter_use = &filter0[0];
		break;
	}

	for (int i=0; i < 45; i++) result[i] = result[sf+i];
	for (int i=45; i < sf+46; i++) result[i] = 0;

// Do convolution:
	for (int i=0; i < sf; i++)
		for (int j=0; j < 45; j++)
			result[i+j] += in[i] * filter_use[j];
	for (int i=0; i < sf; i++)
		*in++ = result[i];


}
// oversample the input signal 2*, give a nice antialised effect
inline void GxEngine::over_sample(float** input, float** output, int sf)
{
	float * in = input[0];
	float * out = output[0];
	float x = in[0];
	float y = 0;
	for (int i=0; i<sf; i++) {
		x = in[i];
		*out++ = x;
		y = in[i+1];
		*out++ = (y+ x)*0.5;
	}
}

// downsample the processed signal to the jack_buffer size
inline void GxEngine::down_sample(float **input,float **output, int sf)
{
	float * in = input[0];
	float * out = output[0];
	float x = in[0];
	float y = 0;
	for (int i=0; i<sf; i++) {

		y = *in++;
		out[i] = x*0.75 + y*0.3;
		x = *in++;
	}
}

inline void GxEngine::noise_gate (int sf, float** input)
{
	float* in = input[0];
	float noisepulse = 0;
	float sumnoise = 0;
	int count = 0;
	float f_gate = fnglevel*0.01;

	for (int i=0; i<sf; i++) {
		count += 1;
		sumnoise += sqrf(fabs(*in++));
		noisepulse = sqrtf(sumnoise/count);
	}
	if (noisepulse > f_gate) ngate = 1; // -75db 0.001 = 65db
	else if (ngate > 0.01)ngate *= 0.996;

}

inline void GxEngine::noise_shaper (int sf, float** input, float** output)
{
	float* in = input[0];
	float* out = output[0];
	//float sharp = fsharp0;
	float press = fsharp0 * 5;




	for (int i=0; i<sf; i++) {
		float fTempgate0 = *in++;
		float fTempgate1 = max(1, fabsf(fTempgate0));
		float fTempgate2 = ((fSlowgate3 * (fRecgate0[1] >= fTempgate1)) + (fSlowgate2 * (fRecgate0[1] < fTempgate1)));
		fRecgate0[0] = ((fTempgate1 * (0 - (fTempgate2 - 1))) + (fRecgate0[1] * fTempgate2));
		float fTempgate3 = max(0, ((20 * log10f(fRecgate0[0])) + press));
		float fTempgate4 = (0.5f * min(1, max(0, (fSlowgate4 * fTempgate3))));
		*out++ = (fTempgate0 * powf(10, (5.000000e-02f * (fsharp0+((fTempgate3 * (0 - fTempgate4)) / (1 + fTempgate4))))));
		// post processing
		fRecgate0[1] = fRecgate0[0];
	}


}

// anti aliasing the sine wav, this unit can nicly run oversampeled
inline void GxEngine::AntiAlias (int sf, float** input, float** output)
{
	float* in = input[0];
	float* out = output[0];
	float alias[gx_jack::jack_bs] ;
	int state = 0;
	for (int i=0; i<sf; i++) {
		float x = *in++;
		add_dc(x);
		float a = alias[state];
		alias[state++] = x + a * faas1;
		if (state > 1.5)
			state = 0;
		*out++ = a ;
	}
}

// the resonace tube unit on frame base
inline void GxEngine::reso_tube (float fuzzy, int sf, float reso, float vibra,
                                 float** input, float** output)
{
	float* in = input[0];
	float* out = output[0];
	float ot = 0;
	float x = in[0];

	//----- resonator
	int 	iSlowRESO2 = int((int((vibra - 1)) & 4095));
	int 	iSlowRESO3 = int((int(vibra) & 4095));

	for (int i=0; i<sf; i++) {
		x = *in++;
		add_dc(x);
		if ( x >= 0.0 ) {
			ot = ((2.f * x - 1.f * x * x) -x)*0.5;
		} else {
			ot =  ((2.f * x + 1.f * x * x) -x)*0.5;
		}
		//bit shifting
		// ot = ot*0.001;
		//----- resonator
		fVecRESO0[IOTARESO&4095] = (ot + (reso * fRecRESO0[1]));
		fRecRESO0[0] = (0.5f * (fVecRESO0[(IOTARESO-iSlowRESO3)&4095] + fVecRESO0[(IOTARESO-iSlowRESO2)&4095]));
		ot = fRecRESO0[0];
		//bit shift back
		ot = (ot*fuzzy); // *1000;
		*out++ = hard_cut(x + clip(ot*0.5,0.7),0.7);
		// post processing
		fRecRESO0[1] = fRecRESO0[0];
		IOTARESO = IOTARESO+1;

	}
}


// the oscilate tube unit on frame base
inline void GxEngine::osc_tube (float fuzzy, int sf, float reso, float vibra,
                                float** input, float** output)
{
	//moving_filter(input,input,sf);
	float* in = input[0];
	float* out = output[0];
	float ot = 0;
	float x = in[0];

	//----- resonator
	int 	iSlowRESO2 = int((int((vibra - 1)) & 4095));
	int 	iSlowRESO3 = int((int(vibra) & 4095));

	for (int i=0; i<sf; i++) {
		x = *in++;
		add_dc(x);
		if ( x >= 0.0 ) {
			ot = ((2.f * x - 1.f * x * x) -x)*0.5;
		} else {
			ot =  ((2.f * x + 1.f * x * x) -x)*0.5;
		}
		// ocsillator
		iVecoscb0[0] = 1;
		fRecoscb0[0] = (0 - (((fRecoscb0[2] + (fConstoscb0 * fRecoscb0[1])) + iVecoscb0[1]) - 1));
		//bit shifting
		// ot = ot*0.001;

		// resonator
		fVecRESO0[IOTARESO&4095] = (ot + (reso * fRecRESO0[1]));
		fRecRESO0[0] = (0.5f * (fVecRESO0[(IOTARESO-iSlowRESO3)&4095] + fVecRESO0[(IOTARESO-iSlowRESO2)&4095]));
		// speaker emulation 130Hz - 5000Hz
		fVecsp0[0] = fRecRESO0[0] * (3+fRecoscb0[0])*0.25f;
		fRecsp3[0] = (fConstsp9 * ((fVecsp0[0] - fVecsp0[1]) + (fConstsp8 * fRecsp3[1])));
		fRecsp2[0] = (fConstsp9 * ((fRecsp3[0] - fRecsp3[1]) + (fConstsp8 * fRecsp2[1])));
		fRecsp1[0] = (fRecsp2[0] - (fConstsp6 * ((fConstsp5 * fRecsp1[2]) + (fConstsp1 * fRecsp1[1]))));
		fRecsp0[0] = ((fConstsp6 * (fRecsp1[2] + (fRecsp1[0] + (2 * fRecsp1[1])))) - (fConstsp4 * ((fConstsp3 * fRecsp0[2]) + (fConstsp1 * fRecsp0[1]))));
		ot = (fConstsp4 * (fRecsp0[2] + (fRecsp0[0] + (2 * fRecsp0[1]))));
		//bit shift back
		ot = (ot*fuzzy);// *1000;
		// output
		*out++ = clip(x + (ot*0.5),0.7);
		// post processing
		// resonator
		fRecRESO0[1] = fRecRESO0[0];
		IOTARESO = IOTARESO+1;
		// oscilloscope
		fRecoscb0[2] = fRecoscb0[1];
		fRecoscb0[1] = fRecoscb0[0];
		iVecoscb0[1] = iVecoscb0[0];
		// speaker emulation
		fRecsp0[2] = fRecsp0[1];
		fRecsp0[1] = fRecsp0[0];
		fRecsp1[2] = fRecsp1[1];
		fRecsp1[1] = fRecsp1[0];
		fRecsp2[1] = fRecsp2[0];
		fRecsp3[1] = fRecsp3[0];
		fVecsp0[1] = fVecsp0[0];
	}
}

// the tube unit on frame base, it's also the drive unit just with other variables
inline void GxEngine::fuzzy_tube (float fuzzy, int mode, int sf,
                                  float** input, float** output)
{
	float* in = input[0];
	float* out = output[0];
	float ot = 0;
	float x = in[0];
	float a = 2.000 ;
	float b = 1.000 ;
	double c = 0.5;

	if (mode) {
		a = 4.000 ;
		b = 4.000 ;
		c = 0.125;
	}

	for (int i=0; i<sf; i++) {
		x = *in++;
		if ( x >= 0.0 ) {
			ot = ((a * x - b * x * x) -x)*c;
		} else {
			ot =  ((a * x + b * x * x) -x)*c;
		}
		*out++ = hard_cut(x + ot*fuzzy*0.5,0.7);
	}
}

// the preamp on frame base, it's a gloubi-boulga followed by a third-degree polynomial
// and then the "normalize", output will smoth down by 0.75
inline void GxEngine::preamp(int sf, float** input, float** output,
                             float atan_shape,float f_atan)
{
	moving_filter(input,input,sf);
	float* in = input[0];
	float* out = output[0];

	for (int i=0; i<sf; i++) {
		float  x = *in++ *0.001 ;
		float  fTemp0in = (x-0.15*(x*x))-(0.15*(x*x*x));
		x = 1.5f * fTemp0in - 0.5f * fTemp0in *fTemp0in * fTemp0in;
		fTemp0in = normalize(x,atan_shape,f_atan);
		*out++ = fTemp0in*750;

	}
// moving_filter(output,output,sf);
}

void GxEngine::get_jconv_output(float **input,float **output,int sf)
{
	float*  input1 = input[1];
	float*  input2 = input[2];
	float*  out1 = output[0];
	float*  out2 = output[1];

	for (int i=0; i<sf; i++) {
		*out1++ +=  (*input1++ );
		*out2++ +=  (*input2++ );
	}

}

//==============================================================================
//
//             this is the process callback called from jack
//
//==============================================================================
void GxEngine::compute (int count, float** input, float** output)
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
		if (old_new) {
			process_buffers_new(count, input, output);
		} else {
			process_buffers(count, input, output);
		}
		break;

		// --------- just copy input to outputs
	case JUSTCOPY_BUFFERS:

		if (conv.is_runnable()) {
			conv.checkstate();
		}
		// only when jconv is not running: copy input to output
		if (!gx_jconv::jconv_is_running) {
			// copy input to output
			(void)memcpy(output[0], input[0], sizeof(float)*count);
			(void)memcpy(output[1], input[0], sizeof(float)*count);

			int tuner_on = gx_gui::shownote + (int)dsp::isMidiOn() + 1;

			// copy clean audio input for the tuner and midi_process
			if (tuner_on > 0) {
				float sumt = 0;
				int cts = 0;

				(void)memcpy(checkfreq, input[0], sizeof(float)*count);
				for (int i=0; i<count; i++) {

					//if (gx_gui::showwave == 1) vivi = checkfreq[i];

					float fTemphp0 = checkfreq[i] *2;
					// low and highpass filter
					tunerstage1=tunerstage1+(tunerfilter*(fTemphp0-tunerstage1));
					tunerstage2=tunerstage2+(tunerfilter*(tunerstage1-tunerstage2));
					tunerstageh1=tunerstageh1+(tunerfilterh*(tunerstage2-tunerstageh1));
					tunerstageh2=tunerstageh2+(tunerfilterh*(tunerstageh1-tunerstageh2));
					fTemphp0 = tunerstage2-tunerstageh2;
					// waveshaper
					float fTemphps0 = (1.5f * fTemphp0 - 0.5f * fTemphp0 *fTemphp0 * fTemphp0);
					// now run a fft
					fVechp0[0] = fTemphps0;
					fRechp0[0] = ((fConsthp3 * (fVechp0[0] - fVechp0[1])) + (fConsthp2 * fRechp0[1]));
					float fTemphp1  = fRechp0[0];
					int iTempt0 = (1 + iRect2[1]);
					float fTempt1 = (1.0f / tanf((fConstan0 * max(100, fRect0[1]))));
					float fTempt2 = (1 + fTempt1);
					fVect0[0] = fTemphp1;
					fRect5[0] = (fConstan3 * ((fVect0[0] - fVect0[1]) + (fConstan2 * fRect5[1])));
					fVect1[0] = (fRect5[0] / fTempt2);
					fRect4[0] = (fVect1[1] + ((fRect5[0] + ((fTempt1 - 1) * fRect4[1])) / fTempt2));
					int iTempt4 = ((fRect4[1] < 0) & (fRect4[0] >= 0));
					iRect3[0] = (iTempt4 + (iRect3[1] % 10));
					iRect2[0] = ((1 - (iTempt4 & (iRect3[0] ==  10.0f))) * iTempt0);
					int iTempt5 = (iRect2[0] == 0);
					iRect1[0] = ((iTempt5 * iTempt0) + ((1 - iTempt5) * iRect1[1]));
					fRect0[0] = (fSamplingFreq * ((10.0f / max(iRect1[0], 1)) - (10.0f * (iRect1[0] == 0))));
					// get the frequence here
					float fConsta4s = fRect0[0];
					// smoth tuner output by rms the value peer frame
					cts += 1;
					sumt += sqrf(fConsta4s);
					fConsta4 = sqrtf(sumt/cts);

					if (gx_gui::shownote == 0) {
						fConsta1 = 1000.0f;
						gx_gui::shownote = -1;
					}

					fRect0[1] = fRect0[0];
					iRect1[1] = iRect1[0];
					iRect2[1] = iRect2[0];
					iRect3[1] = iRect3[0];
					fRect4[1] = fRect4[0];
					fVect1[1] = fVect1[0];
					fRect5[1] = fRect5[0];
					fVect0[1] = fVect0[0];
					fRechp0[1] = fRechp0[0];
					fVechp0[1] = fVechp0[0];


				}



			}

			(void)memcpy(get_frame, output[0], sizeof(float)*count);
			(void)memcpy(get_frame1, output[1], sizeof(float)*count);


		} else { // when jconv is running, init the wet/dry slider and run a minimal loop
			// get the wet/dry slider settings
			float fSlow81 = fslider24;
			float fSlow82 = (1 - max(0, (0 - fSlow81)));
			float fSlow83 = fslider25;
			float fSlow84 = (1 - max(0, fSlow83));
			float fSlow85 = (fSlow84 * fSlow82);
			float fSlow89 = (1 - max(0, (0 - fSlow83)));
			float fSlow90 = (fSlow89 * fSlow82);
			float sumt = 0;

			// pointer to the jack_buffer
			float*  input0 = input[0];
			float* output0 = output[2];
			float* output1 = output[0];
			float* output2 = output[3];
			float* output3 = output[1];

			int cts = 0;
			int tuner_on = gx_gui::shownote + (int)dsp::isMidiOn() + 1;

			// copy clean audio input for the tuner and midi_process
			if (tuner_on > 0)
				(void)memcpy(checkfreq, input0, sizeof(float)*count);

			for (int i=0; i<count; i++) {

				//  if (gx_gui::showwave == 1) vivi = input0[i];

				if (tuner_on > 0) { // enable tuner when show note or play midi
					float fTemphp0 = checkfreq[i] *2;
					// low and highpass filter
					tunerstage1=tunerstage1+(tunerfilter*(fTemphp0-tunerstage1));
					tunerstage2=tunerstage2+(tunerfilter*(tunerstage1-tunerstage2));
					tunerstageh1=tunerstageh1+(tunerfilterh*(tunerstage2-tunerstageh1));
					tunerstageh2=tunerstageh2+(tunerfilterh*(tunerstageh1-tunerstageh2));
					fTemphp0 = tunerstage2-tunerstageh2;
					// waveshaper
					float fTemphps0 = (1.5f * fTemphp0 - 0.5f * fTemphp0 *fTemphp0 * fTemphp0);
					// now run a fft
					fVechp0[0] = fTemphps0;
					fRechp0[0] = ((fConsthp3 * (fVechp0[0] - fVechp0[1])) + (fConsthp2 * fRechp0[1]));
					float fTemphp1  = fRechp0[0];
					int iTempt0 = (1 + iRect2[1]);
					float fTempt1 = (1.0f / tanf((fConstan0 * max(100, fRect0[1]))));
					float fTempt2 = (1 + fTempt1);
					fVect0[0] = fTemphp1;
					fRect5[0] = (fConstan3 * ((fVect0[0] - fVect0[1]) + (fConstan2 * fRect5[1])));
					fVect1[0] = (fRect5[0] / fTempt2);
					fRect4[0] = (fVect1[1] + ((fRect5[0] + ((fTempt1 - 1) * fRect4[1])) / fTempt2));
					int iTempt4 = ((fRect4[1] < 0) & (fRect4[0] >= 0));
					iRect3[0] = (iTempt4 + (iRect3[1] % 10));
					iRect2[0] = ((1 - (iTempt4 & (iRect3[0] ==  10.0f))) * iTempt0);
					int iTempt5 = (iRect2[0] == 0);
					iRect1[0] = ((iTempt5 * iTempt0) + ((1 - iTempt5) * iRect1[1]));
					fRect0[0] = (fSamplingFreq * ((10.0f / max(iRect1[0], 1)) - (10.0f * (iRect1[0] == 0))));
					// get the frequence here
					float fConsta4s = fRect0[0];
					// smoth tuner output by rms the value peer frame
					cts += 1;
					sumt += sqrf(fConsta4s);
					fConsta4 = sqrtf(sumt/cts);
				}
				if (gx_gui::shownote == 0) {
					fConsta1 = 1000.0f;
					gx_gui::shownote = -1;
				}


				// this is the left "extra" port to run jconv in bybass mode
				*output0++ = (fSlow85 * input0[i]);
				// the left output port
				*output1++ = (fSlow84 * input0[i]);
				// this is the right "extra" port to run jconv in bybass mode
				*output2++ = (fSlow90 * input0[i]);
				// the right output port
				*output3++ = (fSlow89 * input0[i]);

				// post processing tuner
				if (tuner_on > 0) { // enable tuner when show note or play midi
					fRect0[1] = fRect0[0];
					iRect1[1] = iRect1[0];
					iRect2[1] = iRect2[0];
					iRect3[1] = iRect3[0];
					fRect4[1] = fRect4[0];
					fVect1[1] = fVect1[0];
					fRect5[1] = fRect5[0];
					fVect0[1] = fVect0[0];
					fRechp0[1] = fRechp0[0];
					fVechp0[1] = fVechp0[0];
				}

			}



			output1 = output[0];
			output3 = output[1];
			(void)memcpy(get_frame, output1, sizeof(float)*count);
			(void)memcpy(get_frame1, output3, sizeof(float)*count);
		}


		break;


		// ------- zeroize buffers
	case ZEROIZE_BUFFERS:
	default:

		if (conv.is_runnable()) {
			conv.checkstate();
		}
		// the extra port register can only run clean on frame base, therfor the
		// variable jconv_is_running must check on frame base, not in the inner loop.

		// no need of loop.
		// You will avoid triggering an if statement for each frame
		(void)memset(output[0], 0, count*sizeof(float));
		(void)memset(output[1], 0, count*sizeof(float));

		// only when jconv is running
		if (gx_jconv::jconv_is_running) {
			(void)memset(output[2], 0, count*sizeof(float));
			(void)memset(output[3], 0, count*sizeof(float));
		}

		break;
	}
}

/****************************************************************
 ** GxConvolver
 **
 ** some parts are copied from jconvolver
 */

Audiofile::Audiofile (void)
{
	reset();
}


Audiofile::~Audiofile (void)
{
	close();
}


void Audiofile::reset (void)
{
	_sndfile = 0;
	_type = TYPE_OTHER;
	_form = FORM_OTHER;
	_rate = 0;
	_chan = 0;
	_size = 0;
}


int Audiofile::open_read (string name)
{
	SF_INFO I;

	reset ();

	if ((_sndfile = sf_open (name.c_str(), SFM_READ, &I)) == 0) return ERR_OPEN;

	switch (I.format & SF_FORMAT_TYPEMASK)
	{
	case SF_FORMAT_CAF:
		_type = TYPE_CAF;
		break;
	case SF_FORMAT_WAV:
		_type = TYPE_WAV;
		break;
	case SF_FORMAT_WAVEX:
		if (sf_command (_sndfile, SFC_WAVEX_GET_AMBISONIC, 0, 0) == SF_AMBISONIC_B_FORMAT)
			_type = TYPE_AMB;
		else
			_type = TYPE_WAV;
	}

	switch (I.format & SF_FORMAT_SUBMASK)
	{
	case SF_FORMAT_PCM_16:
		_form = FORM_16BIT;
		break;
	case SF_FORMAT_PCM_24:
		_form = FORM_24BIT;
		break;
	case SF_FORMAT_PCM_32:
		_form = FORM_32BIT;
		break;
	case SF_FORMAT_FLOAT:
		_form = FORM_FLOAT;
		break;
	}

	_rate = I.samplerate;
	_chan = I.channels;
	_size = I.frames;

	return 0;
}


int Audiofile::close (void)
{
	if (_sndfile) sf_close (_sndfile);
	reset ();
	return 0;
}


int Audiofile::seek (uint32_t posit)
{
	if (!_sndfile) return ERR_MODE;
	if (sf_seek (_sndfile, posit, SEEK_SET) != posit) return ERR_SEEK;
	return 0;
}


int Audiofile::read (float *data, uint32_t frames)
{
	return sf_readf_float (_sndfile, data, frames);
}


bool GxConvolver::read_sndfile (
	Audiofile& audio, int nchan, const float *gain,
	unsigned int *delay, unsigned int offset, unsigned int length)
{
	unsigned int nfram;
	float *buff, *p;
	const unsigned int BSIZE = 0x4000;

	nfram = audio.size();
	if (offset && audio.seek(offset)) {
		gx_system::gx_print_error("convolver", "Can't seek to offset");
		audio.close ();
		return false;
	}
	try {
		buff = new float [BSIZE * nchan];
	} catch (...) {
		audio.close ();
		gx_system::gx_print_error("convolver", "out of memory");
		return false;
	}

	while (length) {
		nfram = (length > BSIZE) ? BSIZE : length;
		nfram = audio.read(buff, nfram);
		if (nfram < 0) {
			gx_system::gx_print_error("convolver", "Error reading file");
			audio.close ();
			delete[] buff;
			return false;
		}
		if (nfram) {
			for (int ichan = 0; ichan < nchan; ichan++) {
				int rc;
				if (ichan >= audio.chan()) {
					rc = impdata_copy(0, 0, ichan, ichan);
				} else {
					p = buff + ichan;
					if (gain[ichan] != 1.0) {
						for (unsigned int ifram = 0; ifram < nfram; ifram++) {
							p[ifram * nchan] *= gain[ichan];
						}
					}
					rc = impdata_create(ichan, ichan, audio.chan(), p,
					                    delay[ichan], delay[ichan] + nfram);
				}
				if (rc) {
					audio.close ();
					delete[] buff;
					gx_system::gx_print_error("convolver", "out of memory");
					return false;
				}
				delay[ichan] += nfram;
			}
			length -= nfram;
		}
	}

	audio.close ();
	delete[] buff;
	return true;
}

void GxConvolver::adjust_values(
	unsigned int audio_size, unsigned int& count, unsigned int& offset,
	unsigned int& delay, unsigned int& ldelay, unsigned int& length,
	unsigned int& size, unsigned int& bufsize)
{
	if (bufsize < count) {
		bufsize = count;
	}
	if (offset > audio_size) {
		offset = audio_size;
	}
	if (!size) {
		if (offset + length > audio_size) {
			gx_system::gx_print_warning("convolver", "data truncated");
			length = audio_size - offset;
		}
		if (!length) {
			length = audio_size - offset;
		}
		size = max(delay, ldelay) + offset + length;
	} else {
		if (delay > size) {
			delay = size;
		}
		if (ldelay > size) {
			ldelay = size;
		}
		if (offset > size - max(delay, ldelay)) {
			offset = size - max(delay, ldelay);
		}
		if (length > size - max(delay, ldelay) - offset) {
			length = size - max(delay, ldelay) - offset;
			gx_system::gx_print_warning("convolver", "data truncated");
		}
		if (!length) {
			length = size - max(delay, ldelay) - offset;
		}
	}
}

bool GxConvolver::configure(
	unsigned int count, int samplerate, string fname, float gain, float lgain,
	unsigned int delay, unsigned int ldelay, unsigned int offset,
	unsigned int length, unsigned int size, unsigned int bufsize)
{
    Audiofile     audio;
    cleanup();
	if (audio.open_read (fname)) {
		gx_system::gx_print_error("convolver", "Unable to open '" + fname + "'");
		return false;
	}
	if (audio.rate() != samplerate) {
		ostringstream buf;
		buf << "sample rate (" << audio.rate() << ") of '" << fname << "' does not match.";
		gx_system::gx_print_warning("convolver", buf.str());
	}
	if (audio.chan() > 2) {
		ostringstream buf;
		buf << "only taking 2 of " << audio.chan() << " channels in impulse response";
		gx_system::gx_print_error("convolver", buf.str());
		return false;
	}
	adjust_values(audio.size(), count, offset, delay, ldelay, length, size, bufsize);
	cout << "state=" << state() << ", ready=" << ready << endl;
	cout << "fname=" << fname << ", size=" << audio.size()
	     << ", channels=" << audio.chan() << endl;
	cout << "convolver: size=" << size << ", count=" << count << ", bufsize="
	     << bufsize << ", offset=" << offset << ", delay=" << delay
	     << ", ldelay=" << ldelay << ", length=" << length << ", gain" << gain
	     << ", lgain" << lgain << endl;
	if (Convproc::configure(2, 2, size, count, bufsize, Convproc::MAXPART)) {
		gx_system::gx_print_error("convolver", "error in Convproc::configure");
		return false;
	}
	float gain_a[2] = {gain, lgain};
	unsigned int delay_a[2] = {delay, ldelay};
	return read_sndfile(audio, 2, gain_a, delay_a, offset, length);
}

bool GxConvolver::start()
{
	int abspri, policy;
    struct sched_param  spar;
    pthread_getschedparam(jack_client_thread_id(gx_jack::client), &policy, &spar);
    abspri = spar.sched_priority;
	int rc = start_process(abspri, policy);
	if (rc != 0) {
		gx_system::gx_print_error("convolver", "can't start convolver");
		return false;
	}
	ready = true;
	return true;
}

void GxConvolver::checkstate()
{
	if (state() == Convproc::ST_WAIT) {
		check();
	} else if (state() == ST_STOP) {
		ready = false;
	}
}

bool GxConvolver::compute(int count, float* input1, float *input2, float *output1, float *output2)
{
	if (state() == Convproc::ST_WAIT) {
		check();
	}
	if (state() != Convproc::ST_PROC) {
		if (input1 != output1) {
			memcpy(output1, input1, count * sizeof(float));
		}
		if (input2 != output2) {
			memcpy(output2, input2, count * sizeof(float));
		}
		if (state() == ST_STOP) {
			ready = false;
			return flags() == 0;
		}
		return true;
	}
	memcpy(inpdata(0), input1, count * sizeof(float));
	memcpy(inpdata(1), input2, count * sizeof(float));

	process();

	memcpy (output1, outdata(0), count * sizeof(float));
	memcpy (output2, outdata(1), count * sizeof(float));
	return true;
}

GxConvolver conv;

namespace HighShelf { void compute(int, float*, float*); } //FIXME remove when done

//======== private method: process buffers on demand
void GxEngine::process_buffers(int count, float** input, float** output)
{
	// precalculate values with need update peer frame
	// compressor
	float fSlowcom0 = fentrycom0;
	float fSlowcom1 = expf((0 - (fConstcom2 / max(fConstcom2, fslidercom0))));
	float fSlowcom2 = expf((0 - (fConstcom2 / max(fConstcom2, fslidercom1))));
	float fSlowcom3 = fentrycom1;
	float fSlowcom4 = (1.000000f / (1.000000e-03f + fSlowcom3));
	float fSlowcom5 = fentrycom2;
	// compressor end
	float 	fSlow0 = fslider0;

	// float 	fSlow15 = checky;
	// float 	fSlow16 = (7.118644f * fSlow15);
	float fSlow18 = (9.999871e-04f * powf(10, (5.000000e-02f * fslider3)));
	// distortion
	float fSlow19 = (1.0f - fslider4);
	float fSlow20 = fslider5;
	float fSlow23 = (1.0f / tanf((fConst6 * fentry0)));
	float fSlow24 = (fSlow23 - 1);
	float fSlow25 = (1.0f / (1 + fSlow23));
	float fSlow26 = (1.0f / tanf((fConst8 * (fConst7 - (6.283185f * fentry1)))));
	float fSlow27 = (1 + fSlow26);
	float fSlow28 = (1.0f / fSlow27);
	float fSlow29 = (0 - ((fSlow26 - 1) / fSlow27));
	float fSlow31 = tanf((fConst6 * fslider6));
	float fSlow32 = (2 * (1 - (1.0f / (fSlow31 * fSlow31))));
	float fSlow33 = (1.0f / fSlow31);
	float fSlow34 = (1 + ((fSlow33 - 0.765367f) / fSlow31));
	float fSlow35 = (1.0f / (1 + ((0.765367f + fSlow33) / fSlow31)));
	float fSlow36 = (1 + ((fSlow33 - 1.847759f) / fSlow31));
	float fSlow37 = (1.0f / (1 + ((1.847759f + fSlow33) / fSlow31)));
	float fSlow38 = (fConst6 * fslider7);
	float fSlow39 = (1.0f / (1 + fSlow38));
	float fSlow40 = (1 - fSlow38);
	float fSlow42 = fslider8;
	float fSlow43 = powf(10.0f, (2 * fslider9));
	float fSlow44 = (9.999871e-04f * powf(10, (5.000000e-02f * (fslider10 - 10))));
	// distortion end
	float fSlow56 = fslider11;
	float fmapping = (2.384186e-10f*(20*fSlow56));
	float fSlow57 = (9.999872e-05f * powf(4.0f, fSlow56));
	float fSlow58 = fslider13;
	float fSlow59 = ((1 - max(0, (0 - fSlow58))) * fslider12);
	float fSlow60 = powf(2.0f, (2.3f * fSlow56));
	float fSlow61 = (1 - (fConst10 * (fSlow60 / powf(2.0f, (1.0f + (2.0f * (1.0f - fSlow56)))))));
	float fSlow62 = (9.999871e-04f * (0 - (2.0f * (fSlow61 * cosf((fConst9 * fSlow60))))));
	float fSlow63 = (9.999871e-04f * (fSlow61 * fSlow61));
	float fSlow64 = (1 - max(0, fSlow58));
	float fSlow66 = (0.5 + fslider14);
	float fSlow67 = (2 * (1 - fSlow66));
	float fSlow68 = fslider15;
	float fSlow69 = (1 - fSlow68);
	float fSlow70 = (0.7f + (0.28f * fslider16));
	float fSlow72 = (9.999871e-04f * powf(10, (5.000000e-02f * fslider17)));
	float fSlow74 = (1.000000e-02f * fslider19);
	float fSlow76 = expf((0 - (fConst6 * fslider20)));
	float fSlow77 = (2 * cosf((fConst12 * fslider21)));
	float fSlow78 = (0.5f * (fslider22 * (1 - (fSlow76 * fSlow76))));
	float fSlow80 = fslider23;
	float fSlow81 = fslider24;
	float fSlow82 = (1 - max(0, (0 - fSlow81)));
	float fSlow83 = fslider25;
	float fSlow84 = (1 - max(0, fSlow83));
	float fSlow85 = (fSlow84 * fSlow82);
	float fSlow86 = (1 - max(0, fSlow81));
	float fSlow87 = (fSlow84 * fSlow86);
	float fSlow89 = (1 - max(0, (0 - fSlow83)));
	float fSlow90 = (fSlow89 * fSlow82);
	float fSlow91 = (fSlow89 * fSlow86);
	float drivem1 = drive - 1.0f;
	float fSlowover0 = (9.999871e-04f * powf(10, (5.000000e-02f * (drive*-0.5))));
	float fSlowvib0 = fvibrato;
	float sumt = 0;
	float atan_shape = 1.0/atan(fatan);
	float f_atan = fatan;
	float threshold = fthreshold;
	float	f_resotube1 = fresotube1;
	float f_resotube2 = fresotube2;
	//chorus
	float 	fSlow_CH0 = (fConst_CH0 * fslider_CH0);
	float 	fSlow_CH1 = fslider_CH1;
	float 	fSlow_CH2 = (fConst_CH1 * fslider_CH2);
	float 	fSlow_CH3 = fslider_CH3;

	float fSlowinjc = (9.999871e-04f * powf(10, (5.000000e-02f * fjc_ingain)));
	float fSlowinjcr = (9.999871e-04f * powf(10, (5.000000e-02f * fjc_ingain1)));
	float fdelgain = (9.999871e-04f * powf(10, (5.000000e-02f * fdel_gain1)));

	float out_to_1 = fRec0[0];
	float out_to_2 = fRec0[0];

	//----- tone only reset when value have change
	fslider_tone_check1 = (fslider_tone1+fslider_tone0+fslider_tone2)*100;
	if (fslider_tone_check1 != fslider_tone_check) {
		fSlow_mid_tone = (fslider_tone1*0.5);
		fSlow_tone0 = powf(10, (2.500000e-02f * (fslider_tone0- fSlow_mid_tone)));
		fSlow_tone1 = (1 + fSlow_tone0);
		fSlow_tone2 = (fConst_tone1 * fSlow_tone1);
		fSlow_tone3 = (2 * (0 - ((1 + fSlow_tone2) - fSlow_tone0)));
		fSlow_tone4 = (fConst_tone1 * (fSlow_tone0 - 1));
		fSlow_tone5 = (fConst_tone2 * sqrtf(fSlow_tone0));
		fSlow_tone6 = (fSlow_tone1 - (fSlow_tone5 + fSlow_tone4));
		fSlow_tone7 = powf(10, (2.500000e-02f * fSlow_mid_tone));
		fSlow_tone8 = (1 + fSlow_tone7);
		fSlow_tone9 = (fConst_tone4 * fSlow_tone8);
		fSlow_tone10 = (2 * (0 - ((1 + fSlow_tone9) - fSlow_tone7)));
		fSlow_tone11 = (fSlow_tone7 - 1);
		fSlow_tone12 = (fConst_tone4 * fSlow_tone11);
		fSlow_tone13 = sqrtf(fSlow_tone7);
		fSlow_tone14 = (fConst_tone5 * fSlow_tone13);
		fSlow_tone15 = (fSlow_tone8 - (fSlow_tone14 + fSlow_tone12));
		fSlow_tone16 = (fConst_tone1 * fSlow_tone8);
		fSlow_tone17 = (0 - (2 * ((fSlow_tone7 + fSlow_tone16) - 1)));
		fSlow_tone18 = (fConst_tone2 * fSlow_tone13);
		fSlow_tone19 = (fConst_tone1 * fSlow_tone11);
		fSlow_tone20 = ((1 + (fSlow_tone7 + fSlow_tone19)) - fSlow_tone18);
		fSlow_tone21 = powf(10, (2.500000e-02f * (fslider_tone2-fSlow_mid_tone)));
		fSlow_tone22 = (1 + fSlow_tone21);
		fSlow_tone23 = (fConst_tone4 * fSlow_tone22);
		fSlow_tone24 = (0 - (2 * ((fSlow_tone21 + fSlow_tone23) - 1)));
		fSlow_tone25 = (fConst_tone5 * sqrtf(fSlow_tone21));
		fSlow_tone26 = (fConst_tone4 * (fSlow_tone21 - 1));
		fSlow_tone27 = ((1 + (fSlow_tone21 + fSlow_tone26)) - fSlow_tone25);
		fSlow_tone28 = (2 * (0 - ((1 + fSlow_tone23) - fSlow_tone21)));
		fSlow_tone29 = (fSlow_tone21 + fSlow_tone25);
		fSlow_tone30 = ((1 + fSlow_tone29) - fSlow_tone26);
		fSlow_tone31 = (fSlow_tone22 - (fSlow_tone25 + fSlow_tone26));
		fSlow_tone32 = (1.0f / (1 + (fSlow_tone26 + fSlow_tone29)));
		fSlow_tone33 = (fSlow_tone8 - (fSlow_tone18 + fSlow_tone19));
		fSlow_tone34 = (2 * (0 - ((1 + fSlow_tone16) - fSlow_tone7)));
		fSlow_tone35 = (fSlow_tone7 + fSlow_tone18);
		fSlow_tone36 = ((1 + fSlow_tone35) - fSlow_tone19);
		fSlow_tone37 = (1.0f / (1 + (fSlow_tone19 + fSlow_tone35)));
		fSlow_tone38 = (fSlow_tone7 * ((1 + (fSlow_tone7 + fSlow_tone12)) - fSlow_tone14));
		fSlow_tone39 = (fSlow_tone7 + fSlow_tone14);
		fSlow_tone40 = (fSlow_tone7 * (1 + (fSlow_tone12 + fSlow_tone39)));
		fSlow_tone41 = (((fSlow_tone7 + fSlow_tone9) - 1) * (0 - (2 * fSlow_tone7)));
		fSlow_tone42 = (1.0f / ((1 + fSlow_tone39) - fSlow_tone12));
		fSlow_tone43 = (fSlow_tone0 * ((1 + (fSlow_tone0 + fSlow_tone4)) - fSlow_tone5));
		fSlow_tone44 = (fSlow_tone0 + fSlow_tone5);
		fSlow_tone45 = (fSlow_tone0 * (1 + (fSlow_tone4 + fSlow_tone44)));
		fSlow_tone46 = (((fSlow_tone0 + fSlow_tone2) - 1) * (0 - (2 * fSlow_tone0)));
		fSlow_tone47 = (1.0f / ((1 + fSlow_tone44) - fSlow_tone4));
		fslider_tone_check = (fslider_tone1+fslider_tone0+fslider_tone2)*100;
	}
	// tone end
	frefreshfilter = (fslMulti0 + fslMulti1 + fslMulti2 + fslMulti3 + fslMulti4 +
	                  fslMulti5 + fslMulti6 + fslMulti7 + fslMulti8 + fslMulti9)*100;
	if (frefreshfilter != foldfilter) {
// multibandfilter
		fSlMulti0 = (1.000000e-02f * powf(10, (5.000000e-02f * (0 - fslMulti0))));
		fSlMulti1 = (1 + (fCoMulti0 * (fCoMulti0 - fSlMulti0)));
		fSlMulti2 = (1.0f / (1 + (fCoMulti0 * (fCoMulti0 + fSlMulti0))));
		fSlMulti3 = (1.000000e-02f * powf(10, (5.000000e-02f * (0 - fslMulti1))));
		fSlMulti4 = (1 + (fCoMulti2 * (fCoMulti2 - fSlMulti3)));
		fSlMulti5 = (1.0f / (1 + (fCoMulti2 * (fCoMulti2 + fSlMulti3))));
		fSlMulti6 = (1.000000e-02f * powf(10, (5.000000e-02f * (0 - fslMulti2))));
		fSlMulti7 = (1 + (fCoMulti4 * (fCoMulti4 - fSlMulti6)));
		fSlMulti8 = (1.0f / (1 + (fCoMulti4 * (fCoMulti4 + fSlMulti6))));
		fSlMulti9 = (1.000000e-02f * powf(10, (5.000000e-02f * (0 - fslMulti3))));
		fSlMulti10 = (1 + (fCoMulti6 * (fCoMulti6 - fSlMulti9)));
		fSlMulti11 = (1.0f / (1 + (fCoMulti6 * (fCoMulti6 + fSlMulti9))));
		fSlMulti12 = (1.000000e-02f * powf(10, (5.000000e-02f * (0 - fslMulti4))));
		fSlMulti13 = (1 + (fCoMulti8 * (fCoMulti8 - fSlMulti12)));
		fSlMulti14 = (1.0f / (1 + (fCoMulti8 * (fCoMulti8 + fSlMulti12))));
		fSlMulti15 = (1.000000e-02f * powf(10, (5.000000e-02f * (0 - fslMulti5))));
		fSlMulti16 = (1 + (fCoMulti10 * (fCoMulti10 - fSlMulti15)));
		fSlMulti17 = (1.0f / (1 + (fCoMulti10 * (fCoMulti10 + fSlMulti15))));
		fSlMulti18 = (1.000000e-02f * powf(10, (5.000000e-02f * (0 - fslMulti6))));
		fSlMulti19 = (1 + (fCoMulti12 * (fCoMulti12 - fSlMulti18)));
		fSlMulti20 = (1.0f / (1 + (fCoMulti12 * (fCoMulti12 + fSlMulti18))));
		fSlMulti21 = (1.000000e-02f * powf(10, (5.000000e-02f * (0 - fslMulti7))));
		fSlMulti22 = (1 + (fCoMulti14 * (fCoMulti14 - fSlMulti21)));
		fSlMulti23 = (1.0f / (1 + (fCoMulti14 * (fCoMulti14 + fSlMulti21))));
		fSlMulti24 = (1.000000e-02f * powf(10, (5.000000e-02f * (0 - fslMulti8))));
		fSlMulti25 = (1 + (fCoMulti16 * (fCoMulti16 - fSlMulti24)));
		fSlMulti26 = (1.0f / (1 + (fCoMulti16 * (fCoMulti16 + fSlMulti24))));
		fSlMulti27 = (1.000000e-02f * powf(10, (5.000000e-02f * (0 - fslMulti9))));
		fSlMulti28 = (1 + (fCoMulti18 * (fCoMulti18 - fSlMulti27)));
		fSlMulti29 = (1.0f / (1 + (fCoMulti18 * (fCoMulti18 + fSlMulti27))));
// multibandfilter end
		foldfilter = (fslMulti0 + fslMulti1 + fslMulti2 + fslMulti3 + fslMulti4 +
		              fslMulti5 + fslMulti6 + fslMulti7 + fslMulti8 + fslMulti9)*100;
	}

	int iSlow21 = int((int((fSlow20 - 1)) & 4095));
	int iSlow22 = int((int(fSlow20) & 4095));
	int iSlow40 = max(0,min(1,(fcheckbox3)));
	int iSlow41 = max(0,min(1,(fcheckbox2)));
	int iSlow73 = int((1 + int((int((int((fConst11 * fslider18)) - 1)) & 131071))));
	int iSlow88 = int(gx_jconv::checkbox7);
	int cts = 0;
	int ifuse = int(ffuse);
	int tuner_on = gx_gui::shownote + (int)dsp::isMidiOn() + 1;
	int 	iSlowdel0 = int((int((fConstdel0 * fsliderdel0)) & 262143));
	int 	iSlowdel1 = int((int((fConstdel0 * fsliderdel1)) & 262143));
	int 	iSlowdel2 = int((int((fConstdel0 * fsliderdel2)) & 262143));
	int iconvolvefilter = (int)convolvefilter;

	//switch effects on/off on frame base to avoid clicks
	int resonator = fresoon;
	int crybaby = fcheckbox5;
	int autowah = fautowah;
	int compressor = fcheckboxcom1;
	int overdrive = foverdrive4;
	int distortion = fcheckbox4;
	int freeverb = fcheckbox6;
	int echo = fcheckbox7;
	int ir = fcheckbox8;
	int delay = fdelay;
	int multifilter = fmultifilter;
	int boost = fboost;
	int chorus = fchorus;

	// pointer to the jack_buffer
	float*  input0 = input[0];
	// copy clean audio input for the tuner and midi_process
	if (tuner_on > 0) {
		(void)memcpy(checkfreq, input0, sizeof(float)*count);
		moving_filter(&checkfreq, &checkfreq, count);
	}
	//moving_filter(input,input,count);
	HighShelf::compute(count,input0,input0);
	// run pre_funktions on frame base
	if (fnoise_g) noise_gate (count,input);
	else ngate = 1;
	if (fng) noise_shaper(count,input,input);

	if (fcheckbox1) preamp(count,input,input,atan_shape,f_atan);

	// 2*oversample
	if (fupsample) {
		over_sample(input,&oversample,count);


		if (antialis0) AntiAlias(count*2,&oversample,&oversample);
		if (ftube)    fuzzy_tube(ffuzzytube, 0,count*2,&oversample,&oversample);
		if (ftube3)   reso_tube(fresotube3,count*2,f_resotube1, f_resotube2, &oversample,&oversample);
		if (fprdr)    fuzzy_tube(fpredrive, 1,count*2,&oversample,&oversample);

		down_sample(&oversample,input,count);
	}
	// or plain sample
	else {

		if (antialis0)   AntiAlias(count,input,input);
		if (ftube)    fuzzy_tube(ffuzzytube, 0,count,input,input);
		if (ftube3)   osc_tube(fresotube3,count,f_resotube1, f_resotube2,input,input);
		if (fprdr)    fuzzy_tube(fpredrive, 1,count,input,input);
	}
	if (fconvolve)convolver_filter(input, input, count,iconvolvefilter);
	// pointers to the jack_output_buffers
	float* output0 = output[2];
	float* output1 = output[0];
	float* output2 = output[3];
	float* output3 = output[1];
	float* conv_out0 = oversample;        //FIXME ... see below
	float* conv_out1 = oversample+count;  //FIXME
	register  float fTemp0 = input0[0];

	// start the inner loop count = jack_frame
	for (int i=0; i<count; i++) {

		fTemp0 = *input0++;
		// when the ocilloscope draw wav by sample (mode 3) get the input value
		//if (gx_gui::showwave == 1) vivi = fTemp0;

		if (tuner_on > 0) { // enable tuner when show note or play midi
			float fTemphp0 = checkfreq[i] *2;
			add_dc(fTemphp0);
			// low and highpass filter
			tunerstage1=tunerstage1+(tunerfilter*(fTemphp0-tunerstage1));
			tunerstage2=tunerstage2+(tunerfilter*(tunerstage1-tunerstage2));
			tunerstageh1=tunerstageh1+(tunerfilterh*(tunerstage2-tunerstageh1));
			tunerstageh2=tunerstageh2+(tunerfilterh*(tunerstageh1-tunerstageh2));
			fTemphp0 = tunerstage2-tunerstageh2;
			// waveshaper
			float fTemphps0 = (1.5f * fTemphp0 - 0.5f * fTemphp0 *fTemphp0 * fTemphp0);
			// now calculate the frequence
			fVechp0[0] = fTemphps0;
			fRechp0[0] = ((fConsthp3 * (fVechp0[0] - fVechp0[1])) + (fConsthp2 * fRechp0[1]));
			float fTemphp1  = fRechp0[0];
			int iTempt0 = (1 + iRect2[1]);
			float fTempt1 = (1.0f / tanf((fConstan0 * max(100, fRect0[1]))));
			float fTempt2 = (1 + fTempt1);
			fVect0[0] = fTemphp1;
			fRect5[0] = (fConstan3 * ((fVect0[0] - fVect0[1]) + (fConstan2 * fRect5[1])));
			fVect1[0] = (fRect5[0] / fTempt2);
			fRect4[0] = (fVect1[1] + ((fRect5[0] + ((fTempt1 - 1) * fRect4[1])) / fTempt2));
			int iTempt4 = ((fRect4[1] < 0) & (fRect4[0] >= 0));
			iRect3[0] = (iTempt4 + (iRect3[1] % 10));
			iRect2[0] = ((1 - (iTempt4 & (iRect3[0] ==  10.0f))) * iTempt0);
			int iTempt5 = (iRect2[0] == 0);
			iRect1[0] = ((iTempt5 * iTempt0) + ((1 - iTempt5) * iRect1[1]));
			fRect0[0] = (fSamplingFreq * ((10.0f / max(iRect1[0], 1)) - (10.0f * (iRect1[0] == 0))));
			// get the frequence here
			float fConsta4s = fRect0[0];
			// smoth tuner output by rms the value peer frame
			if (fTemphp0>0.0001) {
				cts += 1;
				sumt += sqrf(old_freq);
				cts += 1;
				sumt += sqrf(fConsta4s);
				fConsta4 = sqrtf(sumt/cts);
			}
			// else if (fConsta4>0) fConsta4 -= 0.05;
		}
		if (gx_gui::shownote == 0) {
			fConsta1 = 1000.0f;
			gx_gui::shownote = -1;
		}

		add_dc(fTemp0);
		// gain in
		fRec4[0] = ((0.999f * fRec4[1]) + fSlow18);
		fTemp0 = (fRec4[0] * fTemp0);

		/* *****DEPRACTED***** */
		/*  if (fcheckbox1)     // preamp
		    {
		    float  fTemp0in = (fTemp0-0.15*(fTemp0*fTemp0))-(0.15*(fTemp0*fTemp0*fTemp0));
		    fTemp0 = 1.5f * fTemp0in - 0.5f * fTemp0in *fTemp0in * fTemp0in;
		    fTemp0in = normalize(fTemp0,atan_shape,f_atan);
		    //fTemp0 = valve(fTemp0in,fTemp0in)*0.75;
		    fTemp0 = hard_cut(fTemp0in,0.7);
		    }  //preamp ende
		*/

		// tone
		fVec_tone0[0] = fTemp0;
		fRec_tone3[0] = (fSlow_tone32 * ((fSlow_tone21 * ((fSlow_tone31 * fVec_tone0[2]) + ((fSlow_tone30 * fVec_tone0[0]) + (fSlow_tone28 * fVec_tone0[1])))) - ((fSlow_tone27 * fRec_tone3[2]) + (fSlow_tone24 * fRec_tone3[1]))));
		fRec_tone2[0] = (fSlow_tone37 * ((fSlow_tone7 * (((fSlow_tone36 * fRec_tone3[0]) + (fSlow_tone34 * fRec_tone3[1])) + (fSlow_tone33 * fRec_tone3[2]))) - ((fSlow_tone20 * fRec_tone2[2]) + (fSlow_tone17 * fRec_tone2[1]))));
		fRec_tone1[0] = (fSlow_tone42 * ((((fSlow_tone41 * fRec_tone2[1]) + (fSlow_tone40 * fRec_tone2[0])) + (fSlow_tone38 * fRec_tone2[2])) + (0 - ((fSlow_tone15 * fRec_tone1[2]) + (fSlow_tone10 * fRec_tone1[1])))));
		fRec_tone0[0] = (fSlow_tone47 * ((((fSlow_tone46 * fRec_tone1[1]) + (fSlow_tone45 * fRec_tone1[0])) + (fSlow_tone43 * fRec_tone1[2])) + (0 - ((fSlow_tone6 * fRec_tone0[2]) + (fSlow_tone3 * fRec_tone0[1])))));
		// tone end

		fTemp0 = fRec_tone0[0];

		// vibrato
		if (resonator) {
			fRec3[0] = hard_cut (0.5f * ((2.0 * fTemp0) + ( fSlowvib0* fRec3[1])),0.7);  //resonanz 1.76f
			fTemp0 = fRec3[0];
		}


		for (int m=0; m<8; m++) {
			if (posit0==m) {
				if (crybaby) {  //crybaby

					if (autowah) {
						//float fTempw0 = (fTemp0*0.001);
						//fTempw0 = (fTempw0*1000);
						int iTempwah1 = abs(int((4194304 * (fTemp0+ 1e-20))));
						iVecwah0[IOTAWAH&1023] = iTempwah1;
						iRecwah2[0] = ((iVecwah0[IOTAWAH&1023] + iRecwah2[1]) - iVecwah0[(IOTAWAH-1000)&1023]);
						float fTempwah2 = min(1, max(0, (fmapping * float(iRecwah2[0]))));
						fRec19[0] = ((9.999872e-05f * my4powf( fTempwah2)) + (0.999f * fRec19[1]));
						add_dc(fTempwah2);
						float fTempwah3 = my2powf(2.3f * fTempwah2);
						float fTempwah4 = (1 - (fConst10 * (fTempwah3 / my2powf(1.0f + (2.0f * (1.0f - fTempwah2))))));
						fRec20[0] = ((9.999871e-04f * (0 - (2.0f * (fTempwah4 * cosf((fConst9 * fTempwah3)))))) + (0.999f * fRec20[1]));
						fRec21[0] = ((9.999871e-04f * (fTempwah4 * fTempwah4)) + (0.999f * fRec21[1]));
						fRec18[0] = (0 - (((fRec21[0] * fRec18[2]) + (fRec20[0] * fRec18[1])) - (fSlow59 * (fTemp0 * fRec19[0]))));
						fTemp0 = (((fSlow64 *fTemp0) + fRec18[0]) - fRec18[1]);
					} else {

						fRec19[0] = (fSlow57 + (0.999f * fRec19[1])); //wah slider
						fRec20[0] = (fSlow62 + (0.999f * fRec20[1]));
						fRec21[0] = (fSlow63 + (0.999f * fRec21[1]));  // wah slider


						fRec18[0] = (0 - (((fRec21[0] * fRec18[2]) + (fRec20[0] * fRec18[1])) - (fSlow59 * (fTemp0 * fRec19[0]))));
						fTemp0 = ((fRec18[0] + (fSlow64 * fTemp0)) - fRec18[1]);
					}
				}
			}                                   //crybaby ende

			else if (posit5==m) {
				if (compressor) {   // compressor
					add_dc(fTemp0);
					float fTempcom0 = fTemp0;
					fReccom1[0] = ((fConstcom1 * fabsf(fTempcom0)) + (fConstcom0 * fReccom1[1]));
					float fTempcom2 = max(fReccom1[0], fReccom1[0]);
					float fTempcom3 = ((fSlowcom2 * (fReccom0[1] >= fTempcom2)) + (fSlowcom1 * (fReccom0[1] < fTempcom2)));
					fReccom0[0] = ((fTempcom2 * (1 - fTempcom3)) + (fReccom0[1] * fTempcom3));
					float fTempcom4 = max(0, ((fSlowcom3 + (20 * log10f(fReccom0[0]))) - fSlowcom0));
					float fTempcom5 = min(1, max(0, (fSlowcom4 * fTempcom4)));
					float fTempcom6 = (fSlowcom5 * fTempcom5);
					float fTempcom7 = ((fTempcom4 / ((1 + fTempcom6) - fTempcom5)) * (fTempcom5 - fTempcom6));
					float fTempcom8 = powf(10, (5.000000e-02f * fTempcom7));
					fTemp0 = (fTempcom0 * fTempcom8);
				}
				// else  add_dc(fTemp0);
				// compressor end
			}


			else if (posit1==m) {
				if (overdrive) {  // overdrive
					//float fTempdr0 = fTemp0;
					float fTempdr1 = fabs(fTemp0);
					fRecover0[0] = (fSlowover0 + (0.999000f * fRecover0[1]));
					fTemp0 = (fTemp0*(fTempdr1 + drive)/(fTemp0*fTemp0 + drivem1*fTempdr1 + 1.0f)) * fRecover0[0];

				}
			}

			else if (posit2==m) {
				if (distortion) {    // distortion
					float 	S6[2];
					float 	S7[2];
					float 	S8[2];
					fTemp0 = (fTemp0*0.001);
					fVec1[IOTA&4095] = ((fTemp0*1000) + (fSlow19 * fRec6[1]));
					fRec6[0] = (0.5f * (fVec1[(IOTA-iSlow22)&4095] + fVec1[(IOTA-iSlow21)&4095]));
					add_dc(fRec6[0]);
					S8[0] = fRec6[0];
					fVec2[0] = (fSlow25 * fRec6[0]);
					fRec8[0] = (fVec2[1] + (fSlow25 * (fRec6[0] + (fSlow24 * fRec8[1]))));
					fVec3[0] = (fSlow28 * fRec8[0]);
					fRec7[0] = ((fVec3[0] + (fSlow29 * fRec7[1])) - fVec3[1]);
					S8[1] = fRec7[0];
					float fTemp3 = S8[iSlow41];
					add_dc(fTemp3);
					S7[0] = fTemp3;
					fVec4[0] = (fSlow39 * fTemp3);
					fRec12[0] = ((fSlow39 * (fTemp3 + (fSlow40 * fRec12[1]))) - fVec4[1]);
					fVec5[0] = (fSlow39 * fRec12[0]);
					fRec11[0] = ((fSlow39 * (fRec12[0] + (fSlow40 * fRec11[1]))) - fVec5[1]);
					fRec10[0] = (fRec11[0] - (fSlow37 * ((fSlow36 * fRec10[2]) + (fSlow32 * fRec10[1]))));
					fRec9[0] = ((fSlow37 * (fRec10[2] + (fRec10[0] + (2 * fRec10[1])))) - (fSlow35 * ((fSlow34 * fRec9[2]) + (fSlow32 * fRec9[1]))));
					S7[1] = (fSlow35 * (fRec9[2] + (fRec9[0] + (2 * fRec9[1]))));
					add_dc(S7[1]);
					float fTemp4 = max(-1, min(1, (fSlow43 * (fSlow42 + S7[iSlow40]))));
					add_dc(fTemp4);
					fVec6[0] = (fTemp4 * (1 - (0.333333f * (fTemp4 * fTemp4))));
					fRec5[0] = ((fVec6[0] + (0.995f * fRec5[1])) - fVec6[1]);
					fRec13[0] = (fSlow44 + (0.999f * fRec13[1]));
					float fTemp6 = (fRec13[0] * fRec5[0]);
					add_dc(fTemp6);
					S6[0] = fTemp6;
					fVec7[0] = (fSlow39 * fTemp6);
					fRec17[0] = ((fSlow39 * (fTemp6 + (fSlow40 * fRec17[1]))) - fVec7[1]);
					fVec8[0] = (fSlow39 * fRec17[0]);
					fRec16[0] = ((fSlow39 * (fRec17[0] + (fSlow40 * fRec16[1]))) - fVec8[1]);
					fRec15[0] = (fRec16[0] - (fSlow37 * ((fSlow36 * fRec15[2]) + (fSlow32 * fRec15[1]))));
					fRec14[0] = ((fSlow37 * (fRec15[2] + (fRec15[0] + (2 * fRec15[1])))) - (fSlow35 * ((fSlow34 * fRec14[2]) + (fSlow32 * fRec14[1]))));
					S6[1] = (fSlow35 * (fRec14[2] + (fRec14[0] + (2 * fRec14[1]))));
					fTemp0 = S6[iSlow40];

				}
			}
			//else if (m==0)   		// distortion end


			else if (posit3==m) {
				if (freeverb) {    //freeverb
					float fTemp9 = (1.500000e-02f * fTemp0);
					fRec31[0] = ((fSlow69 * fRec30[1]) + (fSlow68 * fRec31[1]));
					fVec10[IOTA&2047] = (fTemp9 + (fSlow70 * fRec31[0]));
					fRec30[0] = fVec10[(IOTA-1640)&2047];
					fRec33[0] = ((fSlow69 * fRec32[1]) + (fSlow68 * fRec33[1]));
					fVec11[IOTA&2047] = (fTemp9 + (fSlow70 * fRec33[0]));
					fRec32[0] = fVec11[(IOTA-1580)&2047];
					fRec35[0] = ((fSlow69 * fRec34[1]) + (fSlow68 * fRec35[1]));
					fVec12[IOTA&2047] = (fTemp9 + (fSlow70 * fRec35[0]));
					fRec34[0] = fVec12[(IOTA-1514)&2047];
					fRec37[0] = ((fSlow69 * fRec36[1]) + (fSlow68 * fRec37[1]));
					fVec13[IOTA&2047] = (fTemp9 + (fSlow70 * fRec37[0]));
					fRec36[0] = fVec13[(IOTA-1445)&2047];
					fRec39[0] = ((fSlow69 * fRec38[1]) + (fSlow68 * fRec39[1]));
					fVec14[IOTA&2047] = (fTemp9 + (fSlow70 * fRec39[0]));
					fRec38[0] = fVec14[(IOTA-1379)&2047];
					fRec41[0] = ((fSlow69 * fRec40[1]) + (fSlow68 * fRec41[1]));
					fVec15[IOTA&2047] = (fTemp9 + (fSlow70 * fRec41[0]));
					fRec40[0] = fVec15[(IOTA-1300)&2047];
					fRec43[0] = ((fSlow69 * fRec42[1]) + (fSlow68 * fRec43[1]));
					fVec16[IOTA&2047] = (fTemp9 + (fSlow70 * fRec43[0]));
					fRec42[0] = fVec16[(IOTA-1211)&2047];
					fRec45[0] = ((fSlow69 * fRec44[1]) + (fSlow68 * fRec45[1]));
					fVec17[IOTA&2047] = (fTemp9 + (fSlow70 * fRec45[0]));
					fRec44[0] = fVec17[(IOTA-1139)&2047];
					float fTemp10 = (((((((fRec44[0] + fRec42[0]) + fRec40[0]) + fRec38[0]) + fRec36[0]) + fRec34[0]) + fRec32[0]) + fRec30[0]);
					fVec18[IOTA&1023] = (fTemp10 + (0.5f * fRec28[1]));
					fRec28[0] = fVec18[(IOTA-579)&1023];
					float 	fRec29 = (0 - (fTemp10 - fRec28[1]));
					fVec19[IOTA&511] = (fRec29 + (0.5f * fRec26[1]));
					fRec26[0] = fVec19[(IOTA-464)&511];
					float 	fRec27 = (fRec26[1] - fRec29);
					fVec20[IOTA&511] = (fRec27 + (0.5f * fRec24[1]));
					fRec24[0] = fVec20[(IOTA-364)&511];
					float 	fRec25 = (fRec24[1] - fRec27);
					fVec21[IOTA&255] = (fRec25 + (0.5f * fRec22[1]));
					fRec22[0] = fVec21[(IOTA-248)&255];
					float 	fRec23 = (fRec22[1] - fRec25);
					fTemp0 = ((fSlow66 * (fRec23 + fTemp9)) + (fSlow67 * fTemp0));
				}
			}

			else if (posit6==m) {
				if (echo) { //echo
					fRec47[IOTA&262143] = (fTemp0 + (fSlow74 * fRec47[(IOTA-iSlow73)&262143]));
					fTemp0 = fRec47[(IOTA-0)&262143];
				}
			}                                    //echo ende
			else if (posit4==m) {
				if (ir) {   //impulseResponse
					fVec22[0] = fTemp0;

					if (auto_ir) fSlow77 = min(0.6, max(-0.6,fTemp0));
					fRec48[0] = ((fSlow78 * (fVec22[0] - fVec22[2])) + (fSlow76 * ((fSlow77 * fRec48[1]) - (fSlow76 * fRec48[2]))));
					fTemp0 = (fRec48[0] + fVec22[0]);
				}
			} else if (posit7==m) {
				if (delay) {   //delay
					fRecdel[0] = (fdelgain + (0.999f * fRecdel[1]));
					fVecdel2[IOTAdel&262143] = fTemp0;
					fTemp0 += fVecdel2[(IOTAdel-iSlowdel2)&262143] * fRecdel[0];
				}
			}


			// else  fVec23[0] = fTemp0;   //impulseResponse ende
		}

		// Multibandfilter
		if (multifilter) {
			float fTeMulti0 = (fCoMulti1 * fReMulti0[1]);
			float fTeMulti1 = (fCoMulti3 * fReMulti1[1]);
			float fTeMulti2 = (fCoMulti5 * fReMulti2[1]);
			float fTeMulti3 = (fCoMulti7 * fReMulti3[1]);
			float fTeMulti4 = (fCoMulti9 * fReMulti4[1]);
			float fTeMulti5 = (fCoMulti11 * fReMulti5[1]);
			float fTeMulti6 = (fCoMulti13 * fReMulti6[1]);
			float fTeMulti7 = (fCoMulti15 * fReMulti7[1]);
			float fTeMulti8 = (fCoMulti17 * fReMulti8[1]);
			float fTeMulti9 = (fCoMulti19 * fReMulti9[1]);
			fReMulti9[0] = (fTemp0 - (fSlMulti29 * ((fSlMulti28 * fReMulti9[2]) + fTeMulti9)));
			fReMulti8[0] = ((fSlMulti29 * ((fTeMulti9 + (fCoMulti21 * fReMulti9[0])) + (fCoMulti20 * fReMulti9[2]))) - (fSlMulti26 * ((fSlMulti25 * fReMulti8[2]) + fTeMulti8)));
			fReMulti7[0] = ((fSlMulti26 * ((fTeMulti8 + (fCoMulti23 * fReMulti8[0])) + (fCoMulti22 * fReMulti8[2]))) - (fSlMulti23 * ((fSlMulti22 * fReMulti7[2]) + fTeMulti7)));
			fReMulti6[0] = ((fSlMulti23 * ((fTeMulti7 + (fCoMulti25 * fReMulti7[0])) + (fCoMulti24 * fReMulti7[2]))) - (fSlMulti20 * ((fSlMulti19 * fReMulti6[2]) + fTeMulti6)));
			fReMulti5[0] = ((fSlMulti20 * ((fTeMulti6 + (fCoMulti27 * fReMulti6[0])) + (fCoMulti26 * fReMulti6[2]))) - (fSlMulti17 * ((fSlMulti16 * fReMulti5[2]) + fTeMulti5)));
			fReMulti4[0] = ((fSlMulti17 * ((fTeMulti5 + (fCoMulti29 * fReMulti5[0])) + (fCoMulti28 * fReMulti5[2]))) - (fSlMulti14 * ((fSlMulti13 * fReMulti4[2]) + fTeMulti4)));
			fReMulti3[0] = ((fSlMulti14 * ((fTeMulti4 + (fCoMulti31 * fReMulti4[0])) + (fCoMulti30 * fReMulti4[2]))) - (fSlMulti11 * ((fSlMulti10 * fReMulti3[2]) + fTeMulti3)));
			fReMulti2[0] = ((fSlMulti11 * ((fTeMulti3 + (fCoMulti33 * fReMulti3[0])) + (fCoMulti32 * fReMulti3[2]))) - (fSlMulti8 * ((fSlMulti7 * fReMulti2[2]) + fTeMulti2)));
			fReMulti1[0] = ((fSlMulti8 * ((fTeMulti2 + (fCoMulti35 * fReMulti2[0])) + (fCoMulti34 * fReMulti2[2]))) - (fSlMulti5 * ((fSlMulti4 * fReMulti1[2]) + fTeMulti1)));
			fReMulti0[0] = ((fSlMulti5 * ((fTeMulti1 + (fCoMulti37 * fReMulti1[0])) + (fCoMulti36 * fReMulti1[2]))) - (fSlMulti2 * ((fSlMulti1 * fReMulti0[2]) + fTeMulti0)));
			fTemp0 = (fSlMulti2 * ((fTeMulti0 + (fCoMulti39 * fReMulti0[0])) + (fCoMulti38 * fReMulti0[2])));
		}

		// gain out
		fRec46[0] = (fSlow72 + (0.999f * fRec46[1]));
		fTemp0 =  (fRec46[0] * fTemp0);

		// bass booster
		if (boost) {
			fRec_boost0[0] = (fTemp0 - (fConst_boost4 * ((fConst_boost3 * fRec_boost0[2]) + (fConst_boost2 * fRec_boost0[1]))));
			fTemp0 = (fConst_boost4 * (((fConst_boost8 * fRec_boost0[0]) + (fConst_boost7 * fRec_boost0[1])) + (fConst_boost6 * fRec_boost0[2])));
		}

		fVec23[0] = fTemp0;
		// this is the output value from the mono process
		fRec0[0] = ((fVec23[0] + (fSlow80 * fVec23[3])) - (fSlow0 * fRec0[5]))*ngate;

		// switch between hard_cut or foldback distortion, or plain output
		switch (ifuse) {
		case 0:
			break;
		case 1:
			fRec0[0] = hard_cut(saturate(fRec0[0],threshold),threshold);
			break;
		case 2:
			fRec0[0] = foldback(fRec0[0],threshold);
			break;
		}

		// split into left and right channel
		out_to_1 = fRec0[0];
		out_to_2 = fRec0[0];

		// stereo chorus
		if (chorus) {
			// left channel
			fVec_CH0[IOTA_CH&65535] = out_to_1;
			float fTemp_CH1 = (fSlow_CH0 + fRec_CH0[1]);
			fRec_CH0[0] = (fTemp_CH1 - floorf(fTemp_CH1));
			float fTemp_CH2 = (65536 * (fRec_CH0[0] - floorf(fRec_CH0[0])));
			float fTemp_CH3 = floorf(fTemp_CH2);
			int iTemp_CH4 = int(fTemp_CH3);
			float fTemp_CH5 = (fSlow_CH2 * (1 + (fSlow_CH1 * ((ftbl0[((1 + iTemp_CH4) & 65535)] * (fTemp_CH2 - fTemp_CH3)) + (ftbl0[(iTemp_CH4 & 65535)] * ((1 + fTemp_CH3) - fTemp_CH2))))));
			int iTemp_CH6 = int(fTemp_CH5);
			int iTemp_CH7 = (1 + iTemp_CH6);
			out_to_1 = (fVec_CH0[IOTA_CH&65535] + (fSlow_CH3 * (((fTemp_CH5 - iTemp_CH6) * fVec_CH0[(IOTA_CH-int((int(iTemp_CH7) & 65535)))&65535]) + ((iTemp_CH7 - fTemp_CH5) * fVec_CH0[(IOTA_CH-int((iTemp_CH6 & 65535)))&65535]))));
			// right channel
			float fTemp_CH8 = out_to_2;
			fVec_CH1[IOTA_CH&65535] = fTemp_CH8;
			float fTemp_CH9 = (0.25f + fRec_CH0[0]);
			float fTemp_CH10 = (65536 * (fTemp_CH9 - floorf(fTemp_CH9)));
			float fTemp_CH11 = floorf(fTemp_CH10);
			int iTemp_CH12 = int(fTemp_CH11);
			float fTemp_CH13 = (fSlow_CH2 * (1 + (fSlow_CH1 * ((ftbl0[((1 + iTemp_CH12) & 65535)] * (fTemp_CH10 - fTemp_CH11)) + (ftbl0[(iTemp_CH12 & 65535)] * ((1 + fTemp_CH11) - fTemp_CH10))))));
			int iTemp_CH14 = int(fTemp_CH13);
			int iTemp_CH15 = (1 + iTemp_CH14);
			out_to_2 = (fVec_CH1[IOTA_CH&65535] + (fSlow_CH3 * (((fTemp_CH13 - iTemp_CH14) * fVec_CH1[(IOTA_CH-int((int(iTemp_CH15) & 65535)))&65535]) + ((iTemp_CH15 - fTemp_CH13) * fVec_CH1[(IOTA_CH-int((iTemp_CH14 & 65535)))&65535]))));
		}

		// the left output port
		float 	S9[2];
		S9[0] = (fSlow87 * out_to_1);
		S9[1] = (fSlow84 * out_to_1);
		*output1++ = S9[iSlow88];

		// the right output port
		float 	S10[2];
		S10[0] = (fSlow91 * out_to_2);
		S10[1] = (fSlow89 * out_to_2);
		*output3++ = S10[iSlow88];

		if (conv.is_runnable()) {
			//FIXME dirty hack for the moment...
			// delay to jconv
			fVecdel0[IOTAdel&262143] = out_to_1;
			float out_to_jc1 = fVecdel0[(IOTAdel-iSlowdel0)&262143];
			fVecdel1[IOTAdel&262143] = out_to_2;
			float out_to_jc2 = fVecdel1[(IOTAdel-iSlowdel1)&262143];

			// gain to jconv
			fRecinjc[0] = (fSlowinjc + (0.999f * fRecinjc[1]));
			fRecinjcr[0] = (fSlowinjcr + (0.999f * fRecinjcr[1]));
			*conv_out0++ = (fSlow85 * out_to_jc1* fRecinjc[0]);
			*conv_out1++ = (fSlow90 * out_to_jc2* fRecinjcr[0]);
		}
		if (gx_jconv::jconv_is_running) {
			// delay to jconv
			fVecdel0[IOTAdel&262143] = out_to_1;
			float out_to_jc1 = fVecdel0[(IOTAdel-iSlowdel0)&262143];
			fVecdel1[IOTAdel&262143] = out_to_2;
			float out_to_jc2 = fVecdel1[(IOTAdel-iSlowdel1)&262143];

			// gain to jconv
			fRecinjc[0] = (fSlowinjc + (0.999f * fRecinjc[1]));
			fRecinjcr[0] = (fSlowinjcr + (0.999f * fRecinjcr[1]));
			// this is the left "extra" port to run jconv in bybass mode
			*output0++ = (fSlow85 * out_to_jc1* fRecinjc[0]);
			// this is the right "extra" port to run jconv in bybass mode
			*output2++ = (fSlow90 * out_to_jc2* fRecinjcr[0]);
		}

		// post processing
		for (int i=5; i>0; i--) fRec0[i] = fRec0[i-1];
		for (int i=3; i>0; i--) fVec23[i] = fVec23[i-1];
		fRec48[2] = fRec48[1];
		fRec48[1] = fRec48[0];
		fVec22[2] = fVec22[1];
		fVec22[1] = fVec22[0];
		fRec46[1] = fRec46[0];
		fRec22[1] = fRec22[0];
		fRec24[1] = fRec24[0];
		fRec26[1] = fRec26[0];
		fRec28[1] = fRec28[0];
		fRec44[1] = fRec44[0];
		fRec45[1] = fRec45[0];
		fRec42[1] = fRec42[0];
		fRec43[1] = fRec43[0];
		fRec40[1] = fRec40[0];
		fRec41[1] = fRec41[0];
		fRec38[1] = fRec38[0];
		fRec39[1] = fRec39[0];
		fRec36[1] = fRec36[0];
		fRec37[1] = fRec37[0];
		fRec34[1] = fRec34[0];
		fRec35[1] = fRec35[0];
		fRec32[1] = fRec32[0];
		fRec33[1] = fRec33[0];
		fRec30[1] = fRec30[0];
		fRec31[1] = fRec31[0];
		fRec18[2] = fRec18[1];
		fRec18[1] = fRec18[0] *0.996f;
		fRec21[1] = fRec21[0];
		fRec20[1] = fRec20[0];
		fRec19[1] = fRec19[0];
		//----- tone
		fRec_tone0[2] = fRec_tone0[1];
		fRec_tone0[1] = fRec_tone0[0];
		fRec_tone1[2] = fRec_tone1[1];
		fRec_tone1[1] = fRec_tone1[0];
		fRec_tone2[2] = fRec_tone2[1];
		fRec_tone2[1] = fRec_tone2[0];
		fRec_tone3[2] = fRec_tone3[1];
		fRec_tone3[1] = fRec_tone3[0];
		fVec_tone0[2] = fVec_tone0[1];
		fVec_tone0[1] = fVec_tone0[0];
		// tone end
		// distortion
		fRec14[2] = fRec14[1];
		fRec14[1] = fRec14[0];
		fRec15[2] = fRec15[1];
		fRec15[1] = fRec15[0];
		fRec16[1] = fRec16[0];
		fVec8[1] = fVec8[0];
		fRec17[1] = fRec17[0];
		fVec7[1] = fVec7[0];
		fRec13[1] = fRec13[0];
		fRec5[1] = fRec5[0];
		fVec6[1] = fVec6[0];
		fRec9[2] = fRec9[1];
		fRec9[1] = fRec9[0];
		fRec10[2] = fRec10[1];
		fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		fVec5[1] = fVec5[0];
		fRec12[1] = fRec12[0];
		fVec4[1] = fVec4[0];
		fRec7[1] = fRec7[0];
		fVec3[1] = fVec3[0];
		fRec8[1] = fRec8[0];
		fVec2[1] = fVec2[0];
		fRec6[1] = fRec6[0];
		// distortion end
		IOTA = IOTA+1;
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fReccom0[1] = fReccom0[0];
		fReccom1[1] = fReccom1[0];
		//fVec0[1] = fVec0[0];
		fRecover0[1] = fRecover0[0];
		// post processing tuner
		fRect0[1] = fRect0[0];
		iRect1[1] = iRect1[0];
		iRect2[1] = iRect2[0];
		iRect3[1] = iRect3[0];
		fRect4[1] = fRect4[0];
		fVect1[1] = fVect1[0];
		fRect5[1] = fRect5[0];
		fVect0[1] = fVect0[0];
		fRechp0[1] = fRechp0[0];
		fVechp0[1] = fVechp0[0];
		// post processing bass booster
		fRec_boost0[2] = fRec_boost0[1];
		fRec_boost0[1] = fRec_boost0[0];
		//autowah
		iRecwah2[1] = iRecwah2[0];
		IOTAWAH = IOTAWAH+1;
		//chorus
		fRec_CH0[1] = fRec_CH0[0];
		IOTA_CH = IOTA_CH+1;
		fRecinjc[1] = fRecinjc[0];
		fRecinjcr[1] = fRecinjcr[0];
		fRecdel[1] = fRecdel[0];
		old_freq = fConsta4;
		IOTAdel = IOTAdel+1;

		if (fmultifilter) {
			//Multibandfilter
			fReMulti0[2] = fReMulti0[1];
			fReMulti0[1] = fReMulti0[0];
			fReMulti1[2] = fReMulti1[1];
			fReMulti1[1] = fReMulti1[0];
			fReMulti2[2] = fReMulti2[1];
			fReMulti2[1] = fReMulti2[0];
			fReMulti3[2] = fReMulti3[1];
			fReMulti3[1] = fReMulti3[0];
			fReMulti4[2] = fReMulti4[1];
			fReMulti4[1] = fReMulti4[0];
			fReMulti5[2] = fReMulti5[1];
			fReMulti5[1] = fReMulti5[0];
			fReMulti6[2] = fReMulti6[1];
			fReMulti6[1] = fReMulti6[0];
			fReMulti7[2] = fReMulti7[1];
			fReMulti7[1] = fReMulti7[0];
			fReMulti8[2] = fReMulti8[1];
			fReMulti8[1] = fReMulti8[0];
			fReMulti9[2] = fReMulti9[1];
			fReMulti9[1] = fReMulti9[0];
		}
	}

	//FIXME resusing the oversampling buffer is a dirty hack..
	if (conv.is_runnable()) {
		if (!conv.compute(count, oversample, oversample+count, oversample, oversample+count)) {
			gx_jconv::GxJConvSettings::checkbutton7 = 0;
			cout << "overload" << endl;
			//FIXME error message??
		} else {
			output1 = output[0];
			output3 = output[1];
			conv_out0 = oversample;
			conv_out1 = oversample+count;
			for (int i = 0; i < count; i++) {
				*output1++ += *conv_out0++;
				*output3++ += *conv_out1++;
			}
		}
	}
	output1 = output[0];
	output3 = output[1];
	(void)memcpy(get_frame, output1, sizeof(float)*count);
	(void)memcpy(get_frame1, output3, sizeof(float)*count);
}

/****************************************************************
 ** functions and variables used by faust dsp files
 */

inline float sigmoid(float x)
{
	return x*(1.5f - 0.5f*x*x);
}

inline float saturate(float x, float t)
{
	if (fabs(x)<t)
		return x;
	else {
		if (x > 0.f)
			return t + (1.f-t)*sigmoid((x-t)/((1-t)*1.5f));
		else
			return -(t + (1.f-t)*sigmoid((-x-t)/((1-t)*1.5f)));
	}
}

inline float hard_cut(float in, float threshold)
{
	if ( in > threshold) {
		in = threshold;
	} else if ( in < -threshold) {
		in = -threshold;
	}

	return in;
}

inline float foldback(float in, float threshold)
{
	if (threshold == 0) threshold = 0.01f;

	if (fabs(in) > threshold) {
		in = fabs(fabs(fmod(in - threshold, threshold*4)) - threshold*2) - threshold;
	}
	return in;
}

inline float fold(float threshold, float v)
{
	float& ffuse = GxEngine::instance()->ffuse;
	// switch between hard_cut or foldback distortion, or plain output
	switch ((int)ffuse) {
	case 0:
		break;
	case 1:
		v = hard_cut(saturate(v,threshold),threshold);
		break;
	case 2:
		v = foldback(v,threshold);
		break;
	}
	return v;
}

inline float add_dc (float val)
{
	return val + 1e-20; // avoid denormals
}

// foreign variable added to faust module feed
// it's set in process_buffers()
namespace feed { float ngate = 1; }  // noise-gate, modifies output gain


/****************************************************************
 ** definitions for code generated with faust / dsp2cc
 */

typedef void (*inifunc)(int);
list<inifunc> inilist;

void faust_init(int samplingFreq)
{
	for (list<inifunc>::iterator i = inilist.begin(); i != inilist.end(); i++) {
		(*i)(samplingFreq);
	}
}

void registerVar(const char* id, const char* name, const char* tp,
                 const char* tooltip, float* var, float val=0,
                 float low=0, float up=0, float step=0)
{
	gx_gui::initParams(GxEngine::instance());
	//cout << id << endl;
	if (!name[0]) {
		assert(strrchr(id, '.'));
		name = strrchr(id, '.')+1;
	}
	gx_gui::Parameter& p = gx_gui::parameter_map[id];
	assert(p.name() == name);
	assert(strcmp(tp,"S") == 0);
	if (p.isFloat()) {
		assert(p.getControlType() == gx_gui::Parameter::Continuous);
		gx_gui::FloatParameter& fp = p.getFloat();
		assert(&fp.value == var);
		assert(fp.value == val);
		assert(fp.lower == low);
		assert(fp.upper == up);
		assert(fp.step == step);
	} else {
		assert(p.getControlType() == gx_gui::Parameter::Switch);
		gx_gui::IntParameter& ip = p.getInt();
		assert((float*)&ip.value == var);
		assert(ip.value == val);
		assert(ip.lower == low);
		up = 1065353216; //...
		assert(ip.upper == up);
		assert(0 == step);
	}
	//gx_gui::parameter_map.insert(new gx_gui::FloatParameter(id, name, gx_gui::Parameter::Continuous, true, *var, val, low, up, step, true));
}

void registerInit(inifunc f)
{
	inilist.push_back(f);
}

template <int N> inline float faustpower(float x)       { return powf(x,N); }
template <int N> inline double faustpower(double x)     { return pow(x,N); }
template <int N> inline int faustpower(int x)           { return faustpower<N/2>(x) * faustpower<N-N/2>(x); }
template <>      inline int faustpower<0>(int x)        { return 1; }
template <>      inline int faustpower<1>(int x)        { return x; }
#define FAUSTFLOAT float

// amp
#include "faust-cc/preamp.cc"
#include "faust-cc/inputgain.cc"
#include "faust-cc/noise_shaper.cc"
#include "faust-cc/AntiAlias.cc"
#include "faust-cc/HighShelf.cc"
#include "faust-cc/drive.cc"
#include "faust-cc/osc_tube.cc"
#include "faust-cc/reso_tube.cc"
#include "faust-cc/tube.cc"
#include "faust-cc/tubevibrato.cc"
#include "faust-cc/tone.cc"
#include "faust-cc/multifilter.cc"
#include "faust-cc/bassbooster.cc"
#include "faust-cc/feed.cc"
#include "faust-cc/outputgain.cc"
#include "faust-cc/jconv_post.cc"
#include "faust-cc/balance.cc"

// effects
#include "faust-cc/overdrive.cc"
#include "faust-cc/compressor.cc"
#include "faust-cc/crybaby.cc"
#include "faust-cc/autowah.cc"
#include "faust-cc/echo.cc"
#include "faust-cc/delay.cc"
#include "faust-cc/distortion.cc"
#include "faust-cc/freeverb.cc"
#include "faust-cc/impulseresponse.cc"
#include "faust-cc/chorus.cc"

bool old_new = true, test_switch = false; //FIXME remove when done

void GxEngine::tuner(int count, float* input, float* workbuf)
{
	moving_filter(&input, &workbuf, count);
	float sumt = 0;
	int cts = 0;
	for (int i=0; i<count; i++) {
		// when the ocilloscope draw wav by sample (mode 3) get the input value
		//if (gx_gui::showwave == 1) vivi = fTemp0;
		float fTemphp0 = workbuf[i] *2;
		add_dc(fTemphp0);
		// low and highpass filter
		tunerstage1=tunerstage1+(tunerfilter*(fTemphp0-tunerstage1));
		tunerstage2=tunerstage2+(tunerfilter*(tunerstage1-tunerstage2));
		tunerstageh1=tunerstageh1+(tunerfilterh*(tunerstage2-tunerstageh1));
		tunerstageh2=tunerstageh2+(tunerfilterh*(tunerstageh1-tunerstageh2));
		fTemphp0 = tunerstage2-tunerstageh2;
		// waveshaper
		float fTemphps0 = (1.5f * fTemphp0 - 0.5f * fTemphp0 *fTemphp0 * fTemphp0);
		// now calculate the frequence
		fVechp0[0] = fTemphps0;
		fRechp0[0] = ((fConsthp3 * (fVechp0[0] - fVechp0[1])) + (fConsthp2 * fRechp0[1]));
		float fTemphp1  = fRechp0[0];
		int iTempt0 = (1 + iRect2[1]);
		float fTempt1 = (1.0f / tanf((fConstan0 * max(100, fRect0[1]))));
		float fTempt2 = (1 + fTempt1);
		fVect0[0] = fTemphp1;
		fRect5[0] = (fConstan3 * ((fVect0[0] - fVect0[1]) + (fConstan2 * fRect5[1])));
		fVect1[0] = (fRect5[0] / fTempt2);
		fRect4[0] = (fVect1[1] + ((fRect5[0] + ((fTempt1 - 1) * fRect4[1])) / fTempt2));
		int iTempt4 = ((fRect4[1] < 0) & (fRect4[0] >= 0));
		iRect3[0] = (iTempt4 + (iRect3[1] % 10));
		iRect2[0] = ((1 - (iTempt4 & (iRect3[0] ==  10.0f))) * iTempt0);
		int iTempt5 = (iRect2[0] == 0);
		iRect1[0] = ((iTempt5 * iTempt0) + ((1 - iTempt5) * iRect1[1]));
		fRect0[0] = (fSamplingFreq * ((10.0f / max(iRect1[0], 1)) - (10.0f * (iRect1[0] == 0))));
		// get the frequence here
		float fConsta4s = fRect0[0];
		// smoth tuner output by rms the value peer frame
		if (fTemphp0>0.0001) {
			cts += 1;
			sumt += sqrf(old_freq);
			cts += 1;
			sumt += sqrf(fConsta4s);
			fConsta4 = sqrtf(sumt/cts);
		}
		// post processing tuner
		fRect0[1] = fRect0[0];
		iRect1[1] = iRect1[0];
		iRect2[1] = iRect2[0];
		iRect3[1] = iRect3[0];
		fRect4[1] = fRect4[0];
		fVect1[1] = fVect1[0];
		fRect5[1] = fRect5[0];
		fVect0[1] = fVect0[0];
		fRechp0[1] = fRechp0[0];
		fVechp0[1] = fVechp0[0];
	}
	if (gx_gui::shownote == 0) {
		fConsta1 = 1000.0f;
		gx_gui::shownote = -1;
	}
}

inline float noise_gateX(int sf, float* input, float ngate)
{
	float sumnoise = 0;
	for (int i = 0; i < sf; i++) {
		sumnoise += sqrf(fabs(input[i]));
	}
	float noisepulse = sqrtf(sumnoise/sf);
	if (noisepulse > GxEngine::instance()->fnglevel * 0.01) {
		return 1; // -75db 0.001 = 65db
	} else if (ngate > 0.01) {
		return ngate * 0.996;
	} else {
		return ngate;
	}
}

inline void over_sampleX(int sf, float *input, float *output)
{
	static float old = 0;
	for (int i = 0; i < sf; i++) {
		float x = *input++;
		*output++ = (old + x) * 0.5;
		*output++ = x;
		old = x;
	}
}

inline void down_sampleX(int sf, float *input, float *output)
{
	for (int i=0; i<sf; i++) {
		float x = *input++;
		*output++ = (x + *input++) * 0.5;
	}
}

void GxEngine::process_buffers_new(int count, float** input, float** output)
{
	// pointer to the jack_buffer
	float* workbuf = output[0];
	float* workbuf2 = output[1];

	int tuner_on = gx_gui::shownote + (int)dsp::isMidiOn() + 1;
	if (tuner_on > 0) {
		tuner(count, input[0], workbuf);
	}
	HighShelf::compute(count, input[0], workbuf);

	if (fnoise_g) {
		feed::ngate = noise_gateX(count,workbuf, feed::ngate);
    } else {
		feed::ngate = 1;
    }
    if (fng) {
	    noise_shaper::compute(count, workbuf, workbuf);
    }
    if (fcheckbox1) {
	    preamp::compute(count, workbuf, workbuf);
    }

    // *** Start (maybe) oversampled processing ***
    static int fupsample_old = 0; // startup always initialises with SR
    int ovs_count, ovs_sr;
    float *ovs_buffer;
    if (fupsample) {
		// 2*oversample
	    over_sampleX(count, workbuf, oversample);
	    ovs_sr = 2 * gx_jack::jack_sr;
	    ovs_count = 2 * count;
	    ovs_buffer = oversample;
    } else {
	    ovs_sr = gx_jack::jack_sr;
	    ovs_count = count;
	    ovs_buffer = workbuf;
    }
    if (fupsample != fupsample_old) {
	    fupsample_old = fupsample;
	    osc_tube::init(ovs_sr);
    }
    if (antialis0) {
	    AntiAlias::compute(ovs_count, ovs_buffer, ovs_buffer);
    }
    if (ftube) {
	    tube::compute(ovs_count, ovs_buffer, ovs_buffer);
    }
    if (ftube3) {
	    osc_tube::compute(ovs_count, ovs_buffer, ovs_buffer);
	    //reso_tube::compute(ovs_count, ovs_buffer, ovs_buffer);
    }
    if (fprdr) {
	    drive::compute(ovs_count, ovs_buffer, ovs_buffer);
    }
    if (fupsample) {
	    down_sampleX(count, oversample, workbuf);
    }
    //*** End (maybe) oversampled processing ***

    if (fconvolve) {
	    convolver_filter(&workbuf, &workbuf, count, (int)convolvefilter);
    }
    inputgain::compute(count, workbuf, workbuf);
    tone::compute(count, workbuf, workbuf);
    if (fresoon) {
	    tone::compute(count, workbuf, workbuf);
    }
    for (int m = 0; m < 8; m++) {
	    if (posit0 == m && fcheckbox5 && !fautowah) {
		    crybaby::compute(count, workbuf, workbuf);
	    } else if (posit0 == m && fcheckbox5 && fautowah) {
		    autowah::compute(count, workbuf, workbuf);
	    } else if (posit5 == m && fcheckboxcom1) {
		    compressor::compute(count, workbuf, workbuf);
	    } else if (posit1 == m && foverdrive4) {
		    overdrive::compute(count, workbuf, workbuf);
	    } else if (posit2 == m && fcheckbox4) {
		    distortion::compute(count, workbuf, workbuf);
	    } else if (posit3 == m && fcheckbox6) {
		    freeverb::compute(count, workbuf, workbuf);
	    } else if (posit6 == m && fcheckbox7) {
		    echo::compute(count, workbuf, workbuf);
	    } else if (posit4 == m && fcheckbox8) {
		    impulseresponse::compute(count, workbuf, workbuf);
	    } else if (posit7 == m && fdelay) {
		    delay::compute(count, workbuf, workbuf);
	    }
    }

    // Multibandfilter
    if (fmultifilter) {
		multifilter::compute(count, workbuf, workbuf);
	}

    outputgain::compute(count, workbuf, workbuf);
    if (fboost) {
	    bassbooster::compute(count, workbuf, workbuf);
    }
    feed::compute(count, workbuf, workbuf, workbuf2);
    if (fchorus) {
	    chorus::compute(count, workbuf, workbuf2, workbuf, workbuf2);
    }
    if (conv.is_runnable()) {
	    // reuse oversampling buffer
	    float *conv_out0 = oversample;
	    float *conv_out1 = oversample+count;
	    if (!conv.compute(count, workbuf, workbuf2, conv_out0, conv_out1)) {
		    gx_jconv::GxJConvSettings::checkbutton7 = 0;
		    cout << "overload" << endl;
		    //FIXME error message??
	    } else {
		    jconv_post::compute(count, workbuf, workbuf2, conv_out0, conv_out1, workbuf, workbuf2);
	    }
    } else {
	    balance::compute(count, workbuf, workbuf2, workbuf, workbuf2);
    }
	(void)memcpy(get_frame, output[0], sizeof(float)*count);
	(void)memcpy(get_frame1, output[1], sizeof(float)*count);
}

} // namespace gx_engine
