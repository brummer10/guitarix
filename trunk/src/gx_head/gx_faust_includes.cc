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
 * --------------------------------------------------------------------------
 */

// foreign variable added to faust module feed
// it's set in process_buffers()
namespace feed { float ngate = 1; }  // noise-gate, modifies output gain

/****************************************************************
 **  definitions for code generated with faust / dsp2cc
 */

typedef void (*inifunc)(int);

typedef struct {
	inifunc func;
	const char *name;
} inidef;


static list<inidef>& get_inilist()
{
	static list<inidef> inilist;
	return inilist;
}

static list<gx_gui::Parameter*>& get_paramlist()
{
	static list<gx_gui::Parameter*> paramlist;
	return paramlist;
}

void register_faust_parameters()
{
	list<gx_gui::Parameter*>& paramlist = get_paramlist();
	for (list<gx_gui::Parameter*>::iterator i = paramlist.begin(); i != paramlist.end(); i++) {
		gx_gui::parameter_map.insert(*i);
	}
	paramlist.clear();
}

static gx_gui::Parameter *find_parameter(const char *id)
{
	list<gx_gui::Parameter*>& paramlist = get_paramlist();
	for (list<gx_gui::Parameter*>::iterator i = paramlist.begin(); i != paramlist.end(); i++) {
		if ((*i)->id() == id) {
			return *i;
		}
	}
	return 0;
}

static float& get_alias(const char *id)
{
	static float dummy;
	gx_gui::Parameter *p = find_parameter(id);
	if (!p) {
		gx_system::gx_print_error("engine", string("can't define alias for unknown (or not yet defined) parameter id: ") + id);
		return dummy;
	} else {
		return p->getFloat().value;
	}
}

static void registerVar(const char* id, const char* name, const char* tp,
                        const char* tooltip, float* var, float val=0,
                        float low=0, float up=0, float step=0, bool exp=false)
{
	if (!name[0]) {
		assert(strrchr(id, '.'));
		name = strrchr(id, '.')+1;
	}
	gx_gui::Parameter *p = new gx_gui::FloatParameter(
		id, name, gx_gui::Parameter::Continuous, true, *var, val, low, up, step, true, exp);
	if (tooltip) {
		p->set_desc(tooltip);
	}
	get_paramlist().push_back(p);
}

static void registerEnumVar(const char *id, const char* name, const char* tp,
                            const char* tooltip, const char** values, float *var, float val,
                            float low=0, float up=0, float step=1, bool exp=false)
{
	if (!name[0]) {
		assert(strrchr(id, '.'));
		name = strrchr(id, '.')+1;
	}
	assert(low == 0.0 && step == 1.0);
	gx_gui::FloatEnumParameter *p = new gx_gui::FloatEnumParameter(
		id, name, values, true, *var, (int)round(val), true, exp); //false == no_midi_var
	assert(up == p->upper); // calculated by constructor
	get_paramlist().push_back(p);
}

static inline void registerIntParam(const char*a,const char*b,int*c,int std=0,int lower=0,int upper=1,bool exp=false)
 {
	 get_paramlist().push_back(
		 new gx_gui::IntParameter(a,b,gx_gui::Parameter::Enum,true,*c,std,
		                          lower,upper,true,exp));
 }

static void registerInit(const char *name, inifunc f)
{
	inidef i;
	i.func = f;
	i.name = name;
	get_inilist().push_back(i);
}

static void jack_sync()
{
	while (sem_wait(&gx_jack::jack_sync_sem) == EINTR);
}

#define max(x,y) (((x)>(y)) ? (x) : (y))
#define min(x,y) (((x)<(y)) ? (x) : (y))

//FIXME (temporary)hack to support older compiler versions
inline float  pow(float b, float e) { return ::powf(b, e); }
inline double pow(double b, double e){return ::pow(b, e); }
inline double pow(double b, int e)  { return ::pow(b, (double)e); }
inline double pow(int b, double e)  { return ::pow((double)b, e); }
inline double pow(double b, float e){ return ::pow(b, (double)e); }
inline double pow(float b, double e){ return ::pow((double)b, e); }
inline float  pow(float b, int e)   { return ::powf(b, (float) e); }
inline float  pow(int b, float e)   { return ::powf((float)b,  e); }

template <int N> inline float faustpower(float x)       { return powf(x,N); }
template <int N> inline double faustpower(double x)     { return pow(x,N); }
template <int N> inline int faustpower(int x)           { return faustpower<N/2>(x) * faustpower<N-N/2>(x); }
template <>      inline int faustpower<0>(int x)        { return 1; }
template <>      inline int faustpower<1>(int x)        { return x; }

#define FAUSTFLOAT float

/****************************************************************
 **  include faust/dsp2cc generated files
 */

#include "faust/gxamp.cc"
#include "faust/gxamp2.cc"
#include "faust/gxamp3.cc"
#include "faust/gxamp4.cc"
#include "faust/gxamp5.cc"
#include "faust/bassbooster.cc"
#include "faust/gxfeed.cc"
#include "faust/gxdistortion.cc"
#include "faust/balance.cc"
#include "faust/jconv_post.cc"
#include "faust/balance1.cc"
#include "faust/gx_outputlevel.cc"

// effects
#include "faust/overdrive.cc"
#include "faust/compressor.cc"
#include "faust/crybaby.cc"
#include "faust/autowah.cc"
#include "faust/echo.cc"
#include "faust/delay.cc"
#include "faust/stereodelay.cc"
#include "faust/stereoecho.cc"
#include "faust/noise_shaper.cc"
#include "faust/gx_distortion.cc"
#include "faust/freeverb.cc"
#include "faust/impulseresponse.cc"
#include "faust/chorus.cc"
#include "faust/moog.cc"
#include "faust/biquad.cc"
#include "faust/flanger.cc"
#include "faust/selecteq.cc"
//#include "faust/eq.cc"
//#include "faust/sloop.cc"
#include "faust/phaser.cc"
#include "faust/low_high_pass.cc"

// tone stack
static struct ToneStackParams { ToneStackParams(); } ToneStackParams;
ToneStackParams::ToneStackParams() {
	static FAUSTFLOAT v1, v2, v3;
	registerVar("amp.tonestack.Treble","","S","",&v1, 0.5, 0.0, 1.0, 0.01);
	registerVar("amp.tonestack.Bass",  "","S","",&v2, 0.5, 0.0, 1.0, 0.01);
	registerVar("amp.tonestack.Middle","","S","",&v3, 0.5, 0.0, 1.0, 0.01);
}

#include "faust/tonestack_default.cc"
#include "faust/tonestack_bassman.cc"
#include "faust/tonestack_twin.cc"
#include "faust/tonestack_princeton.cc"
#include "faust/tonestack_jcm800.cc"
#include "faust/tonestack_jcm2000.cc"
#include "faust/tonestack_mlead.cc"
#include "faust/tonestack_m2199.cc"
#include "faust/tonestack_ac30.cc"


static void activate_callback(float val, void *data)
{
	((void (*)(bool,int))data)(!(val == 0.0), gx_jack::jack_sr);
}

static void faust_add_callback(const char* id, void (*func)(bool,int))
{
	new gx_ui::GxUiCallbackItemFloat(gx_gui::GxMainInterface::instance(),
	                                 (float*)gx_gui::parameter_map[id].zone(),
	                                 activate_callback, (void*)func);
}

void faust_init(int samplingFreq)
{
	//faust_add_callback("SampleLooper.on_off", sloop::activate);
	faust_add_callback("delay.on_off", delay::activate);
	faust_add_callback("echo.on_off", echo::activate);
	faust_add_callback("chorus.on_off", chorus::activate);
	faust_add_callback("stereodelay.on_off", stereodelay::activate);
	faust_add_callback("stereoecho.on_off", stereoecho::activate);
	list<inidef>& inilist = get_inilist();
	for (list<inidef>::iterator i = inilist.begin(); i != inilist.end(); i++) {
		try {
			i->func(samplingFreq);
		} catch (bad_alloc) {
			string name = gx_gui::param_group(i->name, true);
			gx_system::gx_print_error("DSP Module", (boost::format("not enough memory to initialize module %1%") % i->name).str());
		}
	}
}

