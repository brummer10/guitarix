/*
 * Vibe Effect
 *
 * Copyright (C) 2008-2010 Ryan Billing
 *
 * Modified for Guitarix by Andreas Degert
 * License change from GPLV2 to GPLV2+ with permission of Ryan Billing
 * (cf. copy of email in git commit comment).
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
 */

#include <cassert>
#include "gx_pluginlv2.h"

namespace vibe_mono_lfo_sine {
static int 	iVec0[2];
FAUSTFLOAT 	fslider0;
FAUSTFLOAT	*fslider0_;
static double 	fConst0;
static double 	fRec2[2];
static double 	fRec1[2];
static double 	fRec0[2];
static int	fSamplingFreq;

static void clear_state_f()
{
	for (int i=0; i<2; i++) iVec0[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

static void init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = (100.53096491487338 / double(min(192000, max(1, fSamplingFreq))));
	clear_state_f();
}

void compute(int count, FAUSTFLOAT *output0)
{
#define fslider0 (*fslider0_)
	double 	fSlow0 = (fConst0 * double(fslider0));
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		fRec2[0] = (fRec2[1] + (fSlow0 * (0 - fRec0[1])));
		fRec1[0] = ((1 + (fRec1[1] + (fSlow0 * fRec2[0]))) - iVec0[1]);
		fRec0[0] = fRec1[0];
		output0[i] = (FAUSTFLOAT)(0.5 * (1 + fRec0[0]));
		// post processing
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		iVec0[1] = iVec0[0];
	}
#undef fslider0
}

} // end namespace vibe_mono_lfo_sine


namespace vibe_lfo_sine {
static int 	iVec0[2];
FAUSTFLOAT 	fslider0;
FAUSTFLOAT	*fslider0_;
static double 	fConst0;
static double 	fRec0[2];
static double 	fRec1[2];
FAUSTFLOAT 	fslider1;
FAUSTFLOAT	*fslider1_;
static int	fSamplingFreq;

static void clear_state_f()
{
	for (int i=0; i<2; i++) iVec0[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
}

static void init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = (100.53096491487338 / double(min(192000, max(1, fSamplingFreq))));
	clear_state_f();
}

void compute(int count, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
	double 	fSlow0 = (fConst0 * double(fslider0));
	double 	fSlow1 = cos(fSlow0);
	double 	fSlow2 = sin(fSlow0);
	double 	fSlow3 = (0 - fSlow2);
	double 	fSlow4 = (6.283185307179586 * double(fslider1));
	double 	fSlow5 = sin(fSlow4);
	double 	fSlow6 = cos(fSlow4);
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		fRec0[0] = ((fSlow2 * fRec1[1]) + (fSlow1 * fRec0[1]));
		fRec1[0] = ((1 + ((fSlow1 * fRec1[1]) + (fSlow3 * fRec0[1]))) - iVec0[1]);
		output0[i] = (FAUSTFLOAT)(0.5 * (1 + fRec0[0]));
		output1[i] = (FAUSTFLOAT)(0.5 * (1 + ((fSlow6 * fRec0[0]) + (fSlow5 * fRec1[0]))));
		// post processing
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
		iVec0[1] = iVec0[0];
	}
#undef fslider0
#undef fslider1
}

} // end namespace vibe_lfo_sine


namespace vibe {

#define DENORMAL_GUARD 1e-18f   // Make it smaller until CPU problem re-appears
#define CNST_E M_E
#define LN2R 1.442695041f  // 1/log(2)

static const float a[5] = {
    1.00000534060469, 0.693057900547259, 0.239411678986933, 0.0532229404911678, 0.00686649174914722
};

//lookup for positive powers of 2
static const float pw2[25] = {
    1.0f, 2.0f, 4.0f, 8.0f, 16.0f,
    32.0f, 64.0f, 128.0f, 256.0f, 512.0f,
    1024.0f, 2048.0f, 4096.0f, 8192.0f, 16384.0f,
    32768.0f, 65536.0f, 131072.0f, 262144.0f, 524288.0f,
    1048576.0f, 2097152.0f, 4194304.0f, 8388608.0f, 16777216.0f
};

//negative powers of 2, notice ipw2[0] will never be indexed.
static const float ipw2[25] = {
    1.0, 5.0e-01, 2.5e-01, 1.25e-01, 6.25e-02,
    3.125e-02, 1.5625e-02, 7.8125e-03, 3.90625e-03, 1.953125e-03,
    9.765625e-04, 4.8828125e-04, 2.44140625e-04, 1.220703125e-04, 6.103515625e-05,
    3.0517578125e-05, 1.52587890625e-05, 7.62939453125e-06, 3.814697265625e-06, 1.9073486328125e-06,
    9.5367431640625e-07, 4.76837158203125e-07, 2.38418579101562e-07, 1.19209289550781e-07, 5.96046447753906e-08
};

inline float f_pow2(float x)
{
    float y = 0.0f;
    if(x >= 24) {
	return pw2[24];
    } else if (x <= -24.0f) {
	return ipw2[24];
    } else {
        float whole =  ceilf(x);
        int xint = (int) whole;
        x = x - whole;
        if (xint >= 0) {
            y = pw2[xint]*(x*(x*(x*(x*a[4] + a[3]) + a[2]) + a[1]) + a[0]);
        } else  {
            y = ipw2[-xint]*(x*(x*(x*(x*a[4] + a[3]) + a[2]) + a[1]) + a[0]);
        }
        return y;
    }
}

#define f_exp(x) f_pow2(x * LN2R)

class NextValue {
private:
    enum  {
	size = 16,
	period = 16, // corresponding to factor in vibe[_mono]_lfo_ctrl
    };
    int idx;
    int sample;
    float store_l[size];
    float store_r[size];
public:
    NextValue(): idx(size), sample(0) {}
    inline bool hasValue() { return idx < size; }
    inline bool need_next() { sample %= period; return sample++ == 0; }
    inline void fetch(float& left, float& right) { left = store_l[idx]; right = store_r[idx]; ++idx; }
    inline void compute(void (*func)(int,float*));
    inline void compute(void (*func)(int,float*,float*));
};

inline void NextValue::compute(void (*func)(int,float*)) {
    func(size, store_l);
    idx = 0;
}

inline void NextValue::compute(void (*func)(int,float*,float*)) {
    func(size, store_l, store_r);
    idx = 0;
}

/****************************************************************
 ** class Vibe
 */

class Vibe: public PluginLV2 {
public:
    Vibe(bool stereo);
    ~Vibe();

    void out (int count, float * smpsl, float * smpsr, float * efxoutl, float * efxoutr);
    static void init(unsigned int samplingFreq, PluginLV2 *plugin);
    static void process(int count, float * smpsl, float * smpsr, float * efxoutl, float * efxoutr, PluginLV2 *plugin);
    static void process_mono(int count, float *smps, float *efxout, PluginLV2 *plugin);
    static void connect_static(uint32_t port,void* data, PluginLV2 *p);
    //static int registerparam(const ParamReg& reg);
   // static int uiloader(const UiBuilder& builder, int form);
    static void del_instance(PluginLV2 *plugin);

private:
    void connect(uint32_t port,void* data);
    bool Pstereo;
    float Ppanning;
    float *Ppanning_;
 
    float Pwidth;
    float Pdepth;
    float *Pwidth_;
    float *Pdepth_;
    float rpanning, lpanning;
    float wet_dry;
    float flrcross, fcross;
    float fb;
    float *wet_dry_;
    float *flrcross_, *fcross_;
    float *fb_;
  
    float Ra, Rb, b, dTC, dRCl, dRCr, lampTC, ilampTC, minTC, alphal, alphar, stepl, stepr, oldstepl, oldstepr;
    float fbr, fbl;
    float dalphal, dalphar;
    float lstep,rstep;
    float lfol, lfor;
    float gl, oldgl;
    float gr, oldgr; 
  
    class fparams {
    public:
	float x1;
	float y1;
	//filter coefficients
	float n0;
	float n1;
	float d0;
	float d1; 
    } vc[8], vcvo[8], ecvc[8], vevo[8];

    NextValue lfo;

    inline float vibefilter(float data, fparams *ftype, int stage);
    void init_vibes(unsigned int samplerate);
    void modulate(float ldrl, float ldrr);
    inline float bjt_shape(float data);

    float R1;
    float Rv;
    float C2;
    float C1[8];
    float beta;  //transistor forward gain.
    float gain, k;
    float oldcvolt[8];
    float en1[8], en0[8], ed1[8], ed0[8];
    float cn1[8], cn0[8], cd1[8], cd0[8];
    float ecn1[8], ecn0[8], ecd1[8], ecd0[8];
    float on1[8], on0[8], od1[8], od0[8];

    float cSAMPLE_RATE;  // 1 / fSAMPLE_RATE
};

Vibe::Vibe(bool stereo)
    : PluginLV2(), Pstereo(stereo) {
    version = PLUGINLV2_VERSION;
    if (Pstereo) {
	id = "univibe";
	name = N_("Vibe");
	stereo_audio = process;
    } else {
	id = "univibe_mono";
	name = N_("Vibe Mono");
	mono_audio = process_mono;
    }
    connect_ports = connect_static;
    set_samplerate = init;
   // register_params = registerparam;
   // load_ui = uiloader;
    delete_instance = del_instance;
}

void Vibe::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case PAN: 
		Ppanning_ = (float*)data; // , 0,-1,1,0.01 
		break;
	case CROSS: 
		flrcross_ = (float*)data; // , 0,-1,1,0.01 
		break;
	case WIDTH: 
		Pwidth_ = (float*)data; // , 0.5, 0, 1, 0.01 
		break;
	case DEPTH: 
		Pdepth_ = (float*)data; // , 0.37, 0, 1, 0.01 
		break;
	case WETDRY: 
		wet_dry_ = (float*)data; // , 1, 0, 1, 0.01 
		break;
	case FB: 
		fb_ = (float*)data; // , -0.6,-1,1,0.01 
		break;
	case TEMPO: 
		vibe_lfo_sine::fslider0_ = (float*)data; // , 4.4, 0.1, 1e+01, 0.1 
		vibe_mono_lfo_sine::fslider0_ = (float*)data; // , 4.4, 0.1, 1e+01, 0.1 
		break;
	case DF: 
		vibe_lfo_sine::fslider1_ = (float*)data; // , 0.11, -0.5, 0.5, 0.01
		break;
	default:
		break;
	}
}

void Vibe::connect_static(uint32_t port,void* data, PluginLV2 *p)
{
	static_cast<Vibe*>(p)->connect(port, data);
}

/*
typedef enum
{
   PAN,
   CROSS,
   WIDTH,
   DEPTH,
   WETDRY,
   FB,
   TEMPO,
   DF,
} PortIndex;
*/


Vibe::~Vibe () {
}

void Vibe::init(unsigned int samplingFreq, PluginLV2 *plugin) {
    static_cast<Vibe*>(plugin)->init_vibes(samplingFreq);
}

void Vibe::process(int count, float *smpsl, float *smpsr, float *efxoutl, float *efxoutr, PluginLV2 *plugin) {
    static_cast<Vibe*>(plugin)->out(count, smpsl, smpsr, efxoutl, efxoutr);
}

void Vibe::process_mono(int count, float *smps, float *efxout, PluginLV2 *plugin) {
    static_cast<Vibe*>(plugin)->out(count, smps, 0, efxout, 0);
}

inline float
Vibe::vibefilter(float data, fparams *ftype, int stage)
{
    float y0 = 0.0f;
    y0 = data*ftype[stage].n0 + ftype[stage].x1*ftype[stage].n1 - ftype[stage].y1*ftype[stage].d1;
    ftype[stage].y1 = y0 + DENORMAL_GUARD;
    ftype[stage].x1 = data;
    return y0;
};

inline float
Vibe::bjt_shape(float data)
{
    float vbe, vout;
    float vin = 7.5f*(1.0f + data);
    if(vin<0.0f) vin = 0.0f;
    if(vin>15.0f) vin = 15.0f;
    vbe = 0.8f - 0.8f/(vin + 1.0f);  //really rough, simplistic bjt turn-on emulator
    vout = vin - vbe;
    vout = vout*0.1333333333f - 0.90588f;  //some magic numbers to return gain to unity & zero the DC
    return vout;
}

void Vibe::out(int PERIOD, float *smpsl, float *smpsr, float * efxoutl, float * efxoutr) {

	Pwidth =(*Pwidth_);
	Pdepth =(*Pdepth_);
	wet_dry =(*wet_dry_);
	fb =(*fb_);
    float fdepth = (1 - pow(Pdepth, 0.2)) * 0.6;
    if (Pstereo) {
	Ppanning =(*Ppanning_);
	flrcross =(*flrcross_);
	fcross = 1 - std::abs(flrcross);
	rpanning = Ppanning+1;
	lpanning = 2.0f - rpanning;
	lpanning = 10.0f * powf(lpanning, 4);
	rpanning = 10.0f * powf(rpanning, 4);
	lpanning = 1.0f - 1.0f/(lpanning + 1.0f);
	rpanning = 1.0f - 1.0f/(rpanning + 1.0f); 
	lpanning *= 1.3f;
	rpanning *= 1.3f; 
    }

    float fact_d, fact_w;
    if (wet_dry < 0.5) {
	fact_d = 1.0;
	fact_w = wet_dry * 2;
    } else {
	fact_d = (1 - wet_dry) * 2;
	fact_w = 1.0;
    }
    float fwidth = pow(10, 2.14*Pwidth) * 0.01;

    // from rakarrack out()

    int i,j;
    float xl, xr;
    float  fxl=0.0f;
    float  fxr=0.0f;
    //float vbe,vin;
    float cvolt, ocvolt, evolt, input;
    float emitterfb = 0.0f;
    float outl, outr;

    input = cvolt = ocvolt = evolt = 0.0f;

    for (i = 0; i < PERIOD; i++) {
	if (lfo.need_next()) {
	    if (!lfo.hasValue()) {
		if (Pstereo) {
		    lfo.compute(vibe_lfo_sine::compute);
		} else {
		    lfo.compute(vibe_mono_lfo_sine::compute);
		}
	    }
	    lfo.fetch(lfol, lfor);
	    lfol = fdepth + lfol*fwidth;
	    if (lfol > 1.0f) {
		lfol = 1.0f;
	    } else if (lfol < 0.0f) {
		lfol = 0.0f;
	    }
	    lfol = 2.0f - 2.0f/(lfol + 1.0f); //emulate lamp turn on/off characteristic by typical curves

	    if(Pstereo) {
		lfor = fdepth + lfor*fwidth;   
		if (lfor > 1.0f) {
		    lfor = 1.0f;
		} else if (lfor < 0.0f) {
		    lfor = 0.0f;  
		}
		lfor = 2.0f - 2.0f/(lfor + 1.0f);   // 
	    }
	}

	//Left Lamp
	gl = lfol*lampTC + oldgl*ilampTC;
	oldgl = gl;  

	//Left Cds   
	stepl = gl*alphal + dalphal*oldstepl;
	oldstepl = stepl;
	dRCl = dTC*f_exp(stepl*minTC);
	alphal = cSAMPLE_RATE/(dRCl + cSAMPLE_RATE);  
	dalphal = 1.0f - cSAMPLE_RATE/(0.5f*dRCl + cSAMPLE_RATE);     //different attack & release character
	xl = CNST_E + stepl*b;
	fxl = f_exp(Ra/logf(xl));   

        //Right Lamp
        if(Pstereo) {
            gr = lfor*lampTC + oldgr*ilampTC;
            oldgr = gr;

            //Right Cds
            stepr = gr*alphar + dalphar*oldstepr;
            oldstepr = stepr;
            dRCr = dTC*f_exp(stepr*minTC);
            alphar = cSAMPLE_RATE/(dRCr + cSAMPLE_RATE);
            dalphar = 1.0f - cSAMPLE_RATE/(0.5f*dRCr + cSAMPLE_RATE);      //different attack & release character
            xr = CNST_E + stepr*b;
            fxr = f_exp(Ra/logf(xr));
        }

	if(i%4 == 0) modulate(fxl, fxr);
     
	//Left Channel  
        input = bjt_shape(fbl + smpsl[i]);

        /*
        //Inline BJT Shaper bleow
	vin = 7.5f*(1.0f + fbl+smpsl[i]);
	if (vin<0.0f) vin = 0.0f;
	if (vin>15.0f) vin = 15.0f;
	vbe = 0.8f - 0.8f/(vin + 1.0f);  //really rough, simplistic bjt turn-on emulator
	input = vin - vbe;
	input = input*0.1333333333f -0.90588f;  //some magic numbers to return gain to unity & zero the DC
    
        */

	emitterfb = 25.0f/fxl;     
	for(j=0;j<4;j++) { //4 stages phasing
            /*
            //Inline filter implementation below
	    float y0 = 0.0f;
	    y0 = input*ecvc[j].n0 + ecvc[j].x1*ecvc[j].n1 - ecvc[j].y1*ecvc[j].d1;
	    ecvc[j].y1 = y0 + DENORMAL_GUARD;
	    ecvc[j].x1 = input; 

	    float x0 = 0.0f;
	    float data = input + emitterfb*oldcvolt[j];
	    x0 = data*vc[j].n0 + vc[j].x1*vc[j].n1 - vc[j].y1*vc[j].d1;
	    vc[j].y1 = x0 + DENORMAL_GUARD;
	    vc[j].x1 = data; 

	    cvolt=y0+x0;
            
	    ocvolt= cvolt*vcvo[j].n0 + vcvo[j].x1*vcvo[j].n1 - vcvo[j].y1*vcvo[j].d1;
	    vcvo[j].y1 = ocvolt + DENORMAL_GUARD;
	    vcvo[j].x1 = cvolt; 

	    oldcvolt[j] = ocvolt;

	    evolt = input*vevo[j].n0 + vevo[j].x1*vevo[j].n1 - vevo[j].y1*vevo[j].d1;
	    vevo[j].y1 = evolt + DENORMAL_GUARD;
	    vevo[j].x1 = input; 

	    vin = 7.5f*(1.0f + ocvolt+evolt);
	    if(vin<0.0f) vin = 0.0f;
	    if (vin>15.0f) vin = 15.0f;
	    vbe = 0.8f - 0.8f/(vin + 1.0f);  //really rough, simplistic bjt turn-on emulator
	    input = vin - vbe;
	    input = input*0.1333333333f -0.90588f;  //some magic numbers to return gain to unity & zero the DC
	    */
// Orig code, Comment below if instead using inline
            cvolt = vibefilter(input,ecvc,j) + vibefilter(input + emitterfb*oldcvolt[j],vc,j);
            ocvolt = vibefilter(cvolt,vcvo,j);
            oldcvolt[j] = ocvolt;
            evolt = vibefilter(input, vevo,j);

            input = bjt_shape(ocvolt + evolt);
            //Close comment here if using inline

	}
	fbl = fb*ocvolt;
	outl = lpanning*input;    
    
	//Right channel

        if(Pstereo) {
            /*
            //Inline BJT shaper
	    vin = 7.5f*(1.0f + fbr+smpsr[i]);
	    if (vin<0.0f) vin = 0.0f;
	    if (vin>15.0f) vin = 15.0f;
	    vbe = 0.8f - 0.8f/(vin + 1.0f);  //really rough, simplistic bjt turn-on emulator
	    input = vin - vbe;
	    input = input*0.1333333333f -0.90588f;  //some magic numbers to return gain to unity & zero the DC
	    */

//Orig code
            input = bjt_shape(fbr + smpsr[i]);
            //Close Comment here if using Inline instead

	    emitterfb = 25.0f/fxr;     
	    for (j = 4; j < 8; j++) { //4 stages phasing
		/*
		//This is the inline version
		float y0 = 0.0f;
		y0 = input*ecvc[j].n0 + ecvc[j].x1*ecvc[j].n1 - ecvc[j].y1*ecvc[j].d1;
		ecvc[j].y1 = y0 + DENORMAL_GUARD;
		ecvc[j].x1 = input; 

		float x0 = 0.0f;
		float data = input + emitterfb*oldcvolt[j];
		x0 = data*vc[j].n0 + vc[j].x1*vc[j].n1 - vc[j].y1*vc[j].d1;
		vc[j].y1 = x0 + DENORMAL_GUARD;
		vc[j].x1 = data; 

		cvolt=y0+x0;

		ocvolt= cvolt*vcvo[j].n0 + vcvo[j].x1*vcvo[j].n1 - vcvo[j].y1*vcvo[j].d1;
		vcvo[j].y1 = ocvolt + DENORMAL_GUARD;
		vcvo[j].x1 = cvolt; 

		oldcvolt[j] = ocvolt;

		evolt = input*vevo[j].n0 + vevo[j].x1*vevo[j].n1 - vevo[j].y1*vevo[j].d1;
		vevo[j].y1 = evolt + DENORMAL_GUARD;
		vevo[j].x1 = input; 

		vin = 7.5f*(1.0f + ocvolt+evolt);
		if (vin < 0.0f) vin = 0.0f;
		if (vin > 15.0f) vin = 15.0f;
		vbe = 0.8f - 0.8f/(vin + 1.0f);  //really rough, simplistic bjt turn-on emulator
		input = vin - vbe;
		input = input*0.1333333333f -0.90588f;  //some magic numbers to return gain to unity & zero the DC

		*/

//  Comment block below if using inline code instead
		cvolt = vibefilter(input,ecvc,j) + vibefilter(input + emitterfb*oldcvolt[j],vc,j);
		ocvolt = vibefilter(cvolt,vcvo,j);
		oldcvolt[j] = ocvolt;
		evolt = vibefilter(input, vevo,j);

		input = bjt_shape(ocvolt + evolt);
// Close comment here if inlining
	    }

	    fbr = fb*ocvolt;
	    outr = rpanning*input;  

	    // changed from rakarrack to do dry/wet processing here
	    efxoutl[i] = fact_w * (outl*fcross + outr*flrcross) + fact_d * smpsl[i];
	    efxoutr[i] = fact_w * (outr*fcross + outl*flrcross) + fact_d * smpsr[i];
        } else {  //if(Pstereo)
	    efxoutl[i] = fact_w * outl + fact_d * smpsl[i];
	} 
    }
};

void Vibe::init_vibes(unsigned int samplerate) {
    if (Pstereo) {
	vibe_lfo_sine::init(samplerate);
    } else {
	vibe_mono_lfo_sine::init(samplerate);
    }

    cSAMPLE_RATE = 1.0 / samplerate;

    // from rakarrack ctor

    //Swing was measured on operating device of: 10K to 250k.  
    //400K is reported to sound better for the "low end" (high resistance) 
    //Because of time response, Rb needs to be driven further.
    //End resistance will max out to around 10k for most LFO freqs.
    //pushing low end a little lower for kicks and giggles
    Ra = 700000.0f;  //Cds cell dark resistance.
    Ra = logf(Ra);		//this is done for clarity
    Rb = 500.0f;         //Cds cell full illumination
    b = exp(Ra/logf(Rb)) - CNST_E;
    dTC = 0.085f;
    dRCl = dTC;
    dRCr = dTC;   //Right & left channel dynamic time contsants
    minTC = logf(0.005f/dTC);
    alphal = 1.0f - cSAMPLE_RATE/(dRCl + cSAMPLE_RATE);
    alphar = alphal;
    dalphal = dalphar = alphal;
    lampTC = cSAMPLE_RATE/(0.012 + cSAMPLE_RATE);  //guessing twiddle factor
    ilampTC = 1.0f - lampTC;
    lstep = 0.0f;
    rstep = 0.0f;
    lfol = 0.0f;
    lfor = 0.0f;
    lpanning = 1.0f;
    rpanning = 1.0f;
    oldgl = 0.0f;
    oldgr = 0.0f;
    gl = 0.0f;
    gr = 0.0f;
    for(int jj = 0; jj < 8; jj++) {
	oldcvolt[jj] = 0.0f;
    }

    // from rakarrack init_vibes

    k = 2.0f*samplerate;
    float tmpgain = 1.0f;
    R1 = 4700.0f;
    Rv = 4700.0f;
    C2 = 1e-6f;
    beta = 150.0f;  //transistor forward gain.
    gain = -beta/(beta + 1.0f); 

    //Univibe cap values 0.015uF, 0.22uF, 470pF, and 0.0047uF
    C1[0] = 0.015e-6f;
    C1[1] = 0.22e-6f;
    C1[2] = 470e-12f;
    C1[3] = 0.0047e-6f;
    C1[4] = 0.015e-6f;
    C1[5] = 0.22e-6f;
    C1[6] = 470e-12f;
    C1[7] = 0.0047e-6f;

    for(int i =0; i<8; i++) {
	//Vo/Ve driven from emitter
	en1[i] = k*R1*C1[i];
	en0[i] = 1.0f;
	ed1[i] = k*(R1 + Rv)*C1[i];
	ed0[i] = 1.0f + C1[i]/C2;

	// Vc~=Ve/(Ic*Re*alpha^2) collector voltage from current input.  
	//Output here represents voltage at the collector

	cn1[i] = k*gain*Rv*C1[i];
	cn0[i] = gain*(1.0f + C1[i]/C2);
	cd1[i] = k*(R1 + Rv)*C1[i];
	cd0[i] = 1.0f + C1[i]/C2;

	//Contribution from emitter load through passive filter network
	ecn1[i] = k*gain*R1*(R1 + Rv)*C1[i]*C2/(Rv*(C2 + C1[i]));
	ecn0[i] = 0.0f;
	ecd1[i] = k*(R1 + Rv)*C1[i]*C2/(C2 + C1[i]);
	ecd0[i] = 1.0f;

	// %Represents Vo/Vc.  Output over collector voltage
	on1[i] = k*Rv*C2;
	on0[i] = 1.0f;
	od1[i] = k*Rv*C2;
	od0[i] = 1.0f + C2/C1[i];

	//%Bilinear xform stuff
	tmpgain =  1.0f/(cd1[i] + cd0[i]);
	vc[i].n1 = tmpgain*(cn0[i] - cn1[i]);
	vc[i].n0 = tmpgain*(cn1[i] + cn0[i]);
	vc[i].d1 = tmpgain*(cd0[i] - cd1[i]);
	vc[i].d0 = 1.0f;

	tmpgain =  1.0f/(ecd1[i] + ecd0[i]);
	ecvc[i].n1 = tmpgain*(ecn0[i] - ecn1[i]);
	ecvc[i].n0 = tmpgain*(ecn1[i] + ecn0[i]);
	ecvc[i].d1 = tmpgain*(ecd0[i] - ecd1[i]);
	ecvc[i].d0 = 1.0f;

	tmpgain =  1.0f/(od1[i] + od0[i]);
	vcvo[i].n1 = tmpgain*(on0[i] - on1[i]);
	vcvo[i].n0 = tmpgain*(on1[i] + on0[i]);
	vcvo[i].d1 = tmpgain*(od0[i] - od1[i]);
	vcvo[i].d0 = 1.0f;

	tmpgain =  1.0f/(ed1[i] + ed0[i]);
	vevo[i].n1 = tmpgain*(en0[i] - en1[i]);
	vevo[i].n0 = tmpgain*(en1[i] + en0[i]);
	vevo[i].d1 = tmpgain*(ed0[i] - ed1[i]);
	vevo[i].d0 = 1.0f;
    }
};

void Vibe::modulate(float ldrl, float ldrr) {
    float tmpgain;
    float R1pRv;
    float C2pC1;
    Rv = 4700.0f + ldrl;
    R1pRv = R1 + Rv;

    for(int i =0; i<8; i++) {
	if (i==4) {
	    Rv = 4700.0f + ldrr;
	    R1pRv = R1 + Rv;
	}

	C2pC1 = C2 + C1[i];
	//Vo/Ve driven from emitter
	ed1[i] = k*(R1pRv)*C1[i];
	//ed1[i] = R1pRv*kC1[i];

	// Vc~=Ve/(Ic*Re*alpha^2) collector voltage from current input.  
	//Output here represents voltage at the collector
	cn1[i] = k*gain*Rv*C1[i];
	//cn1[i] = kgainCl[i]*Rv;
	//cd1[i] = (R1pRv)*C1[i];
	cd1[i]=ed1[i];

	//Contribution from emitter load through passive filter network
	ecn1[i] = k*gain*R1*cd1[i]*C2/(Rv*(C2pC1));
	//ecn1[i] = iC2pC1[i]*kgainR1C2*cd1[i]/Rv;
	ecd1[i] = k*cd1[i]*C2/(C2pC1);
	//ecd1[i] = iC2pC1[i]*k*cd1[i]*C2/(C2pC1);

	// %Represents Vo/Vc.  Output over collector voltage
	on1[i] = k*Rv*C2;
	od1[i] = on1[i];

	//%Bilinear xform stuff
	tmpgain =  1.0f/(cd1[i] + cd0[i]);
	vc[i].n1 = tmpgain*(cn0[i] - cn1[i]);
	vc[i].n0 = tmpgain*(cn1[i] + cn0[i]);
	vc[i].d1 = tmpgain*(cd0[i] - cd1[i]);

	tmpgain =  1.0f/(ecd1[i] + ecd0[i]);
	ecvc[i].n1 = tmpgain*(ecn0[i] - ecn1[i]);
	ecvc[i].n0 = tmpgain*(ecn1[i] + ecn0[i]);
	ecvc[i].d1 = tmpgain*(ecd0[i] - ecd1[i]);
	ecvc[i].d0 = 1.0f;

	tmpgain =  1.0f/(od1[i] + od0[i]);
	vcvo[i].n1 = tmpgain*(on0[i] - on1[i]);
	vcvo[i].n0 = tmpgain*(on1[i] + on0[i]);
	vcvo[i].d1 = tmpgain*(od0[i] - od1[i]);

	tmpgain =  1.0f/(ed1[i] + ed0[i]);
	vevo[i].n1 = tmpgain*(en0[i] - en1[i]);
	vevo[i].n0 = tmpgain*(en1[i] + en0[i]);
	vevo[i].d1 = tmpgain*(ed0[i] - ed1[i]);
    }
};

void Vibe::del_instance(PluginLV2 *p)
{
    delete static_cast<Vibe*>(p);
}


PluginLV2 *plugin_mono() {
    return new Vibe(false);
}

PluginLV2 *plugin_stereo() {
    return new Vibe(true);
}


} // end namespace vibe
