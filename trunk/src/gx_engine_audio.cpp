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
#include <cstdlib>

#include <array>
#include <zita-convolver.h>
#include <fftw3.h>
#include <zita-resampler.h>

#include <cassert>
#include <sigc++/sigc++.h>
#include <semaphore.h>

#include <cmath>
#include <gtk/gtk.h>
#include <jack/jack.h>
#include <jack/midiport.h>
#include <sndfile.h>

using namespace std;

#include "guitarix.h"

namespace gx_engine {


// static convolution filters
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

/****************************************************************
 ** registering of audio variables
 */

inline void registerNonPresetParam(const char*a, float*c, bool d, float std=0, float lower=0, float upper=1)
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
	// switch between hard_cut or foldback distortion, or plain output
	switch ((int)audio.ffuse) {
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

float& get_alias(const char *id)
{
	static float dummy;
	if (!gx_gui::parameter_map.hasId(id)) {
		gx_system::gx_print_error("engine", string("can't define alias for unknown (or not yet defined) parameter id: ") + id);
		return dummy;
	} else {
		return gx_gui::parameter_map[id].getFloat().value;
	}
}

void registerVar(const char* id, const char* name, const char* tp,
                 const char* tooltip, float* var, float val=0,
                 float low=0, float up=0, float step=0, bool exp=false)
{
	if (!name[0]) {
		assert(strrchr(id, '.'));
		name = strrchr(id, '.')+1;
	}
	gx_gui::parameter_map.insert(new gx_gui::FloatParameter(id, name, gx_gui::Parameter::Continuous, true, *var, val, low, up, step, true, exp));
}

void registerInit(inifunc f)
{
	inilist.push_back(f);
}

#define max(x,y) (((x)>(y)) ? (x) : (y))
#define min(x,y) (((x)<(y)) ? (x) : (y))

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
#include "faust-cc/balance.cc"
#include "faust-cc/jconv_post.cc"
#include "faust-cc/balance1.cc"
#include "faust-cc/eq.cc"

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
#include "faust-cc/moog.cc"
#include "faust-cc/flanger.cc"

#ifdef EXPERIMENTAL
typedef void (*setupfunc)(GtkWidget *);
list<setupfunc> setuplist;

void registerSetup(setupfunc f)
{
	setuplist.push_back(f);
}

#define registerVar(id,name,tp,tooltip,var,val,low,up,step) registerVar(id,name,tp,tooltip,var,val,low,up,step,true)

#include  "faust-cc/ExpFilter.cc"
#include  "faust-cc/Exp.cc"

#undef registerVar

static GtkWidget *exp_window = 0;

static gint delete_event(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	gtk_widget_hide(widget);
    return TRUE;
}

static void on_show(GtkWidget *widget, gpointer data)
{
	gx_gui::parameter_map["system.show_exp_window"].getSwitch().set(true);
}

static void on_hide(GtkWidget *widget, gpointer data)
{
	gx_gui::parameter_map["system.show_exp_window"].getSwitch().set(false);
}

volatile int exp_upsample;
volatile bool exp_hs;
GtkWidget *exp_sample_spin;
SimpleResampler resampExp;

static void exp_sr_changed(GtkWidget *widget, gpointer data)
{
	exp_upsample = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(widget));
}

static void exp_hs_toggled(GtkWidget *widget, gpointer data)
{
	exp_hs = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));
}

void faust_setup()
{
	registerEnumParam("test.upsample", "Upsample", (int*)&exp_upsample, 4, 1, 8, true);
	gx_gui::registerParam("test.highshelf", "HighShelf", (bool*)&exp_hs, true, true);
    exp_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW(exp_window), "Experimental");
    gtk_window_set_transient_for(GTK_WINDOW(exp_window), GTK_WINDOW(gx_gui::fWindow));
    //FIXME prevents digit entry (-> preset selection)
    //gtk_window_add_accel_group(GTK_WINDOW(exp_window),
    //                           gx_gui::GxMainInterface::instance()->fAccelGroup);
    gtk_signal_connect (GTK_OBJECT (exp_window), "delete_event", GTK_SIGNAL_FUNC(delete_event), NULL);
    gtk_signal_connect (GTK_OBJECT (exp_window), "hide", GTK_SIGNAL_FUNC(on_hide), NULL);
    gtk_signal_connect (GTK_OBJECT (exp_window), "show", GTK_SIGNAL_FUNC(on_show), NULL);
    GtkWidget *vbox = gtk_vbox_new(false, 10);
    gtk_widget_show(vbox);
    GtkWidget *hbox = gtk_hbox_new(false, 10);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, 0, 0, 5);
    GtkWidget *w = gtk_label_new("Upsample:");
    gtk_widget_show(w);
    gtk_box_pack_start(GTK_BOX(hbox), w, 0, 0, 5);
	GtkObject *adj = gtk_adjustment_new(4, 1, 8, 1, 2, 0);
	exp_sample_spin = gtk_spin_button_new(GTK_ADJUSTMENT(adj), 1, 0);
    gtk_signal_connect (GTK_OBJECT(exp_sample_spin), "value-changed", GTK_SIGNAL_FUNC(exp_sr_changed), NULL);
    gtk_widget_show(exp_sample_spin);
    gtk_box_pack_start(GTK_BOX(hbox), exp_sample_spin, 0, 0, 5);
    w = gtk_check_button_new_with_label("HighShelf");
    gtk_widget_show(w);
    gtk_box_pack_start(GTK_BOX(hbox), w, 0, 0, 20);
    gtk_signal_connect(GTK_OBJECT(w), "toggled", GTK_SIGNAL_FUNC(exp_hs_toggled), NULL);
    hbox = gtk_hbox_new(false, 10);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, 0, 0, 5);
    gtk_container_add(GTK_CONTAINER(exp_window), vbox);
    gtk_window_set_type_hint (GTK_WINDOW(exp_window), GDK_WINDOW_TYPE_HINT_UTILITY);
	for (list<setupfunc>::iterator i = setuplist.begin(); i != setuplist.end(); i++) {
		(*i)(hbox);
	}
}

void toggle_exp_window(bool v)
{
	if (v) {
		if (!GTK_WIDGET_VISIBLE(exp_window)) {
			gtk_spin_button_set_value(GTK_SPIN_BUTTON(exp_sample_spin), exp_upsample);
			gtk_window_present(GTK_WINDOW(exp_window));
		}
	} else {
		if (GTK_WIDGET_VISIBLE(exp_window)) {
			gtk_widget_hide(exp_window);
		}
	}
}

#define IF_HS(fn) {if (exp_hs) { fn; }}
#else
#define IF_HS(fn) {fn;}
#endif // EXPERIMENTAL

//==============================================================================
//
//             this is the process callback called from jack
//
//==============================================================================
void compute (int count, float* input, float* output0, float* output1)
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
		process_buffers(count, input, output0, output1);
		break;

		// --------- just copy input to outputs
	case JUSTCOPY_BUFFERS:
		if (conv.is_runnable()) {
			conv.checkstate();
		}
	    balance1::compute(count, input, output0, output1);
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

//****************************************************************

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

AudioVariables::AudioVariables()
{
	registerEnumParam("amp.threshold", "threshold", &ffuse, 0.f, 0.f, 3.f, 1.0f);
	gx_gui::registerParam("MultiBandFilter.on_off", "on/off", &fmultifilter, 0);
	gx_gui::registerParam("crybaby.autowah", "autowah", &fautowah, 0);
	gx_gui::registerParam("overdrive.on_off", "on/off", &foverdrive4, 0);
	gx_gui::registerParam("distortion.on_off", "on/off", &fcheckbox4, 0);
	gx_gui::registerParam("freeverb.on_off", "on/off", &fcheckbox6, 0);
	gx_gui::registerParam("IR.on_off", "on/off", &fcheckbox8, 0);
	gx_gui::registerParam("crybaby.on_off", "on/off", &fcheckbox5, 0);
	gx_gui::registerParam("echo.on_off", "on/off", &fcheckbox7, 0);
	gx_gui::registerParam("delay.on_off", "on/off", &fdelay, 0);
	gx_gui::registerParam("chorus.on_off", "on/off", &fchorus, 0);
	gx_gui::registerParam("compressor.on_off", "on/off", &fcheckboxcom1, 0);
	gx_gui::registerParam("tube2.on_off", "on/off", &ftube3, 0);
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
	gx_gui::registerParam("flanger.on_off", "on/off", &fflanger, 0);
	gx_gui::registerParam("jconv.on_off", "Run", &gx_jconv::GxJConvSettings::checkbutton7);

	// only save and restore, no midi control

	// positions of effects
	registerNonPresetParam("crybaby.position", &posit0, true, 5, 0, 8);
	registerNonPresetParam("overdrive.position", &posit1, true, 2, 0, 8);
	registerNonPresetParam("distortion.position", &posit2, true, 1, 0, 8);
	registerNonPresetParam("freeverb.position", &posit3, true, 3, 0, 8);
	registerNonPresetParam("IR.position", &posit4, true, 4, 0, 8);
	registerNonPresetParam("compressor.position", &posit5, true, 0, 0, 8);
	registerNonPresetParam("echo.position", &posit6, true, 6, 0, 8);
	registerNonPresetParam("delay.position", &posit7, true, 8, 0, 8);
	registerNonPresetParam("chorus.position", &posit8, true, 7, 0, 8);
	registerNonPresetParam("flanger.position", &posit9, true, 9, 0, 8);

	// togglebuttons for dialogboxes and expander for effect details
	registerNonPresetParam("compressor.dialog", &fdialogbox8, false);
	registerNonPresetParam("distortion.dialog", &fdialogbox1, false);
	registerNonPresetParam("freeverb.dialog", &fdialogbox2, false);
	registerNonPresetParam("IR.dialog", &fdialogbox3, false);
	registerNonPresetParam("crybaby.dialog", &fdialogbox4, false);
	registerNonPresetParam("chorus.dialog", &fchorusbox, false);
	registerNonPresetParam("midi_out.dialog", &fdialogbox6, false);
	registerNonPresetParam("jconv.dialog", &fdialogboxj, false);
	registerNonPresetParam("jconv.expander", &fexpand2, false);
	registerNonPresetParam("jconv.filedialog", &filebutton, false);
	registerNonPresetParam("eq.dialog", &fdialogbox_eq, false);
	registerNonPresetParam("MultiBandFilter.dialog", &fdialogbox_mbf, false);
	registerNonPresetParam("moog.dialog", &fdialogbox_moo, false);
	registerNonPresetParam("flanger.dialog", &fflangerbox, false);

	// user interface options
	registerNonPresetParam("ui.latency_nowarn", &fwarn, false, 0);
	registerNonPresetParam("ui.skin", &fskin, false, 0, 0, 100);
	registerNonPresetParam("ui.main_expander", &fexpand, false);

	// shouldn't be saved, only output?
	registerNonPresetParam("system.fConsta1t", &fConsta1t, false);
	registerNonPresetParam("system.midistat", &midistat, false);
	registerNonPresetParam("system.waveview", &viv, false);
}

AudioVariables audio;

void SimpleResampler::setup(int sampleRate, unsigned int fact)
{
	assert(fact <= MAX_UPSAMPLE);
	const int qual = 16;
	r_up.setup(sampleRate, sampleRate*fact, 1, qual);
	r_up.inp_count = (2*qual);
	r_up.out_count = (2*qual) * fact;
	r_up.inp_data = r_up.out_data = 0;
	r_up.process();
	assert(r_up.inp_count == 0);
	assert(r_up.out_count != (2*qual) * fact);
	r_down.setup(sampleRate*fact, sampleRate, 1, qual);
	r_down.inp_count = (2*qual) * fact;
	r_down.out_count = (2*qual);
	r_down.inp_data = r_down.out_data = 0;
	r_down.process();
	m_fact = fact;
	assert(r_down.inp_count == 0);
	assert(r_down.out_count != (2*qual));
}

void SimpleResampler::up(int count, float *input, float *output)
{
	r_up.inp_count = count;
	r_up.inp_data = input;
	r_up.out_count = count * m_fact;
	r_up.out_data = output;
	r_up.process();
	assert(r_up.inp_count == 0);
	//assert(r_up.out_count == 0);
	//if (r_up.out_count != 0) cout << "# " << r_up.out_count << endl;
}

void SimpleResampler::down(int count, float *input, float *output)
{
	r_down.inp_count = count * m_fact;
	r_down.inp_data = input;
	r_down.out_count = count;
	r_down.out_data = output;
	r_down.process();
	assert(r_down.inp_count == 0);
	assert(r_down.out_count == 0);
}

SimpleResampler resampTube, resampDist;

void process_buffers(int count, float* input, float* output0, float* output1)
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
	IF_HS(HighShelf::compute(count, input, output0));
	memcpy(output0, input, count*sizeof(float));

    if (audio.feq) {
	    eq::compute(count, output0, output0);
    }
	if (audio.fnoise_g) {
		feed::ngate = noise_gate(count,output0, feed::ngate);
    } else {
		feed::ngate = 1;
    }
    if (audio.fng) {
	    noise_shaper::compute(count, output0, output0);
    }
    if (audio.fcheckbox1) {
	    preamp::compute(count, output0, output0);
    }

    // *** Start (maybe) oversampled processing ***
    static int fupsample_old = 0; // startup always initialises with SR
    int ovs_count, ovs_sr;
    float *ovs_buffer;
    if (audio.fupsample) {
		// 2*oversample
	    resampTube.up(count, output0, oversample);
	    //over_sample(count, output0, oversample);
	    ovs_sr = 2 * gx_jack::jack_sr;
	    ovs_count = 2 * count;
	    ovs_buffer = oversample;
    } else {
	    ovs_sr = gx_jack::jack_sr;
	    ovs_count = count;
	    ovs_buffer = output0;
    }
    if (audio.fupsample != fupsample_old) {
	    fupsample_old = audio.fupsample;
	    osc_tube::init(ovs_sr);
	    distortion::init(ovs_sr);
    }
    if (audio.antialis0) {
	    AntiAlias::compute(ovs_count, ovs_buffer, ovs_buffer);
    }
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
    if (audio.fupsample) {
	    //down_sample(count, oversample, output0);
	    resampTube.down(count, oversample, output0);
    }
    //*** End (maybe) oversampled processing ***

#ifdef EXPERIMENTAL
    ExpFilter::compute(count, output0, output0);
    static int exp_upsample_old = 0;
    if (exp_upsample != exp_upsample_old) {
	    exp_upsample_old = exp_upsample;
	    if (exp_upsample > 1) {
		    //FIXME non-rt
		    resampExp.setup(gx_jack::jack_sr, exp_upsample);
	    }
	    Exp::init(exp_upsample * gx_jack::jack_sr);
    }
    if (exp_upsample > 1) {
	    resampExp.up(count, output0, oversample);
	    ovs_sr = exp_upsample * gx_jack::jack_sr;
	    ovs_count = exp_upsample * count;
	    ovs_buffer = oversample;
    } else {
	    ovs_sr = gx_jack::jack_sr;
	    ovs_count = count;
	    ovs_buffer = output0;
    }
    Exp::compute(ovs_count, ovs_buffer, ovs_buffer);
    if (exp_upsample > 1) {
	    resampExp.down(count, oversample, output0);
    }
#endif // EXPERIMENTAL

    if (audio.fconvolve) {
	    convolver_filter(output0, output0, count, (unsigned int)audio.convolvefilter);
    }
    inputgain::compute(count, output0, output0);
    tone::compute(count, output0, output0);
    if (audio.fresoon) {
	    tubevibrato::compute(count, output0, output0);
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
                distortion::compute(ovs_count, oversample, oversample);
                resampDist.down(count, oversample, output0);
                //down_sample(count, oversample, output0);
	        } else {
                distortion::compute(count, output0, output0);
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
