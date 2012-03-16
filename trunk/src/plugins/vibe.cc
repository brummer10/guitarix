/*
  rakarrack - a guitar effects software

  Vibe Effect

  Copyright (C) 2008-2010 Ryan Billing
  Author: Josep Andreu & Ryan Billing

  EffectLFO.C - Stereo LFO used by some effects
  Copyright (C) 2002-2005 Nasca Octavian Paul
  Author: Nasca Octavian Paul

  Modified for rakarrack by Josep Andreu & Ryan Billing

 This program is free software; you can redistribute it and/or modify
 it under the terms of version 2 of the GNU General Public License
 as published by the Free Software Foundation.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License (version 2) for more details.

 You should have received a copy of the GNU General Public License
 (version2)  along with this program; if not, write to the Free Software
 Foundation,
 Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA

*/

#include <cstdlib>
#include <cmath>
#include "gx_plugin.h"

#define DENORMAL_GUARD 1e-18f   // Make it smaller until CPU problem re-appears
#define RND (rand()/(RAND_MAX+1.0))
#define D_PI (2*M_PI)
#define RND1 (((float) rand())/(((float) RAND_MAX)+1.0f))

#define N_(x) (x)

/****************************************************************
 ** class EffectLFO
 */

class EffectLFO {
public:
    EffectLFO();
    ~EffectLFO();
    void effectlfoout(float * outl, float * outr);
    void updateparams();
    void init(float samplingFreq, int per);
    float Pfreq;
    float Prandomness;
    unsigned int PLFOtype;
    float Pstereo;
    int PERIOD;          // jack buffer size
private:
    float getlfoshape(float x);

    float xl, xr;
    float incx;
    float ampl1, ampl2, ampr1, ampr2;	//necesar pentru "randomness"
    float lfointensity;
    float lfornd;
    int lfotype;
  
    //Lorenz Fractal parameters
    float x0,y0,z0,x1,y1,z1,radius;
    float h;
    float a;
    float b;
    float c;
    float scale;
    float iperiod; 
    float ratediv;

    //Sample/Hold
    int holdflag;  //toggle left/right channel changes
    float tca, tcb, maxrate;
    float rreg, lreg, xlreg,xrreg, oldrreg, oldlreg;
    //---------------------------
    float fSAMPLE_RATE;  // jack sample rate as float
};

EffectLFO::EffectLFO() {
    PERIOD = 0;
    xl = 0.0;
    xr = 0.0;

    a = 10.0f;
    b = 28.0f;
    c = 8.0f / 5.0f;
    scale = 1.0f/36.0f;
    ratediv = 0.1f;
    holdflag = 0;
    rreg = lreg = oldrreg = oldlreg = 0.0f;
};

EffectLFO::~EffectLFO() {
};

void EffectLFO::init(float samplingFreq, int per) {
    PERIOD = per;
    fSAMPLE_RATE = samplingFreq;
    iperiod = static_cast<float>(PERIOD)/fSAMPLE_RATE;
    h = iperiod;
    tca = iperiod/(iperiod + 0.02);  //20ms default
    tcb = 1.0f - tca;
    updateparams ();

    ampl1 = (1.0f - lfornd) + lfornd * (float)RND;
    ampl2 = (1.0f - lfornd) + lfornd * (float)RND;
    ampr1 = (1.0f - lfornd) + lfornd * (float)RND;
    ampr2 = (1.0f - lfornd) + lfornd * (float)RND;
}

/*
 * Update the changed parameters
 */
void EffectLFO::updateparams() {
    incx = Pfreq * static_cast<float>(PERIOD) / (fSAMPLE_RATE * 60.0f);

    if (incx > 0.49999999) {
	incx = 0.499999999f;		//Limit the Frequency
    }
    lfornd = Prandomness;
    if (lfornd < 0.0) {
	lfornd = 0.0;
    } else if (lfornd > 1.0) {
	lfornd = 1.0;
    }
    lfotype = PLFOtype;

    xr = fmodf (xl + Pstereo + 1.0f, 1.0f);
  
    if ((h = incx*ratediv) > 0.02) {  //keeps it stable
	h = 0.02;
    }
    a = 10.0f + (((float) RND) - 0.5f)*8.0f;
    b = 28.0f + (((float) RND) - 0.5f)*12.0f;
    c = 1.25f + 3.0f * ((float) RND);

    // printf("incx %f x0 %f y0 %f z0 %f out %f c %f b %f a %f\n",incx,x0,y0,z0, (2.0f * radius - 1.0f), c, b, a);  
    x0 = 0.1f + 0.1f * ((float) RND);
    y0 = 0.0f;
    z0 = 0.2f;
    x1 = y1 = z1 = radius = 0.0f;
   
    float tmp = 6.0f / Pfreq;  //S/H time attack  0.2*60=12.0
    tca = iperiod/(iperiod + tmp);  //
    tcb = 1.0f - tca;
    maxrate = 4.0f*iperiod;
};


/*
 * Compute the shape of the LFO
 */
float EffectLFO::getlfoshape (float x) {
    float tmpv;
    float out=0.0;
    int iterations = 1;  //make fractal go faster
    switch (lfotype) {
    case 1:			//EffectLFO_TRIANGLE
	if ((x > 0.0) && (x < 0.25)) {
	    out = 4.0f * x;
	} else if ((x > 0.25) && (x < 0.75)) {
	    out = 2.0f - 4.0f * x;
	} else {
	    out = 4.0f * x - 4.0f;
	}
	break;
    case 2:			//EffectLFO_RAMP Ramp+
	out = 2.0f * x - 1.0f;	 
	break;  
    case 3:			//EffectLFO_RAMP Ramp-
	out = - 2.0f * x + 1.0f;	 
	break; 
    case 4:                     //ZigZag
	x = x * 2.0f - 1.0f;
        tmpv = 0.33f * sinf(x);
        out = sinf(sinf(x*D_PI)*x/tmpv);       
	break;  
    case 5:                     //Modulated Square ?? ;-)
	tmpv = x * D_PI;
	out=sinf(tmpv+sinf(2.0f*tmpv));  
	break; 
    case 6:                     // Modulated Saw 
	tmpv = x * D_PI;
	out=sinf(tmpv+sinf(tmpv));  
	break; 
    case 8:                       //Lorenz Fractal, faster, using X,Y outputs
	iterations = 4;
    case 7:			// Lorenz Fractal
	for(int j=0; j<iterations;j++) {
	    x1 = x0 + h * a * (y0 - x0);
	    y1 = y0 + h * (x0 * (b - z0) - y0);
	    z1 = z0 + h * (x0 * y0 - c * z0);
	    x0 = x1;
	    y0 = y1;
	    z0 = z1;
	}
	if(lfotype==7) {
	    if((radius = (sqrtf(x0*x0 + y0*y0 + z0*z0) * scale) - 0.25f)  > 1.0f) radius = 1.0f;
	    if(radius < 0.0) {
		radius = 0.0; 
	    }
	    out = 2.0f * radius - 1.0f;
	}
	break;
    case 9:                  //Sample/Hold Random
	if(fmod(x,0.5f) <= (2.0f*incx)) {   //this function is called by left, then right...so must toggle each time called
	    rreg = lreg;
	    lreg = RND1;
	}
	if (xlreg < lreg) {
	    xlreg += maxrate;
	} else {
	    xlreg -= maxrate;
	}
	if (xrreg < rreg) {
	    xrreg += maxrate;
	} else {
	    xrreg -= maxrate;
	}
	oldlreg = xlreg*tca + oldlreg*tcb;
	oldrreg = xrreg*tca + oldrreg*tcb;

	if (holdflag) {
	    out = 2.0f*oldlreg -1.0f;
	    holdflag = (1 + holdflag)%2;
	} else {
	    out = 2.0f*oldrreg - 1.0f;        
	}
	break; 

	//more to be added here; also ::updateparams() need to be updated (to allow more lfotypes)
    default:
	out = cosf (x * D_PI);	//EffectLFO_SINE
    };
    return (out);
};

/*
 * LFO output
 */
void EffectLFO::effectlfoout (float * outl, float * outr) {
    float out;

    out = getlfoshape (xl);
    out *= (ampl1 + xl * (ampl2 - ampl1));
    xl += incx;
    if (xl > 1.0) {
	xl -= 1.0f;
	ampl1 = ampl2;
	ampl2 = (1.0f - lfornd) + lfornd * (float)RND;
    };
    if (lfotype == 8) {
	out = scale*x0;  //fractal parameter
    }
    *outl = (out + 1.0f) * 0.5f;

    if (lfotype == 8) {
	out = scale*y0;  //fractal parameter
    }
    else {
	out = getlfoshape (xr);
    }
    out *= (ampr1 + xr * (ampr2 - ampr1));
    xr += incx;
    if (xr > 1.0) {
	xr -= 1.0f;
	ampr1 = ampr2;
	ampr2 = (1.0f - lfornd) + lfornd * (float)RND;
    };
    *outr = (out + 1.0f) * 0.5f;
};


/****************************************************************
 ** class Vibe
 */

class Vibe: public PluginDef {
public:
    Vibe();
    ~Vibe();

    void out (int count, float * smpsl, float * smpsr, float * efxoutl, float * efxoutr);
    static void init(unsigned int samplingFreq, PluginDef *plugin);
    static void process(int count, float * smpsl, float * smpsr, float * efxoutl, float * efxoutr, PluginDef *plugin);
    static int registerparam(const ParamReg& reg);
    static int uiloader(const UiBuilder& builder);
    void setpanning();

private:
    float Ppanning;
  
    float fwidth;
    float fdepth;
    float rpanning, lpanning;
    float wet_dry;
    float flrcross, fcross;
    float fb;
    EffectLFO lfo;
  
    float Ra, Rb, b, dTC, dRCl, dRCr, lampTC, ilampTC, minTC, alphal, alphar, stepl, stepr, oldstepl, oldstepr;
    float fbr, fbl;
    float dalphal, dalphar;
    float lstep,rstep;
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
    } vc[8], vcvo[8], ecvc[8], vevo[8], bootstrap[8];

    void init_vibes(unsigned int samplerate);
    void modulate(float ldrl, float ldrr);

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

    float fSAMPLE_RATE;  // jack sample rate as float
    float cSAMPLE_RATE;  // 1 / fSAMPLE_RATE
};

Vibe::Vibe()
    : PluginDef() {
    version = PLUGINDEF_VERSION;
    id = "univibe";
    name = N_("Vibe");
    stereo_audio = process;
    set_samplerate = init;
    register_params = registerparam;
    load_ui = uiloader;
}

Vibe::~Vibe () {
}

void Vibe::init(unsigned int samplingFreq, PluginDef *plugin) {
    static_cast<Vibe*>(plugin)->init_vibes(samplingFreq);
}

void Vibe::process(int count, float *smpsl, float *smpsr, float *efxoutl, float *efxoutr, PluginDef *plugin) {
    static_cast<Vibe*>(plugin)->out(count, smpsl, smpsr, efxoutl, efxoutr);
}

int Vibe::registerparam(const ParamReg& reg) {
    Vibe& self = *static_cast<Vibe*>(reg.plugin);
    static const value_pair lfo_types[] = {
	{"sine",             N_("Sine") },
	{"tri",              N_("Tri") },
	{"ramp_up",          N_("Ramp Up") },
	{"ramp_down",        N_("Ramp Down") },
	{"zigzig",           N_("ZigZag") },
	{"modulated_square", N_("M. Sqare") },
	{"modulated_saw",    N_("M.Saw") },
	//{"fractal",          N_("L. Fractal") },
	//{"fractal_xy",       N_("L. Fractal XY") },
	//{"s_h_random",       N_("S/H Random") },
	{0,0}
    };
    reg.registerVar("univibe.freq",N_("Tempo"),"S", N_("LFO frequency (Hz)"),&self.lfo.Pfreq, 40, 1, 600, 0.1);
    reg.registerUEnumVar("univibe.lfo_type",N_("LFO Type"),"B","",lfo_types,&self.lfo.PLFOtype,0);
    reg.registerVar("univibe.width",N_("Width"),"S",N_("LFO amplitude"),&self.fwidth, 0.7, 0, 127/90.0, 0.1);
    reg.registerVar("univibe.depth",N_("Depth"),"S",N_("DC level in LFO"),&self.fdepth,1,0,1,0.01);
    reg.registerVar("univibe.randomness",N_("Rnd"),"S",N_("randomness of LFO"),&self.lfo.Prandomness, 0, 0, 1, 0.01);
    reg.registerVar("univibe.stereo",N_("St.df"),"S",N_("LFO phase shift between left and right channels"),&self.lfo.Pstereo,0.25,-0.5,0.5,0.01);
    reg.registerVar("univibe.panning",N_("Pan"),"S",N_("panning of output (left / right)"),&self.Ppanning,0,-1,1,0.01);
    reg.registerVar("univibe.wet_dry",N_("Wet/Dry"),"S",N_("output mix (signal / effect)"),&self.wet_dry,1,0,1,0.01);
    reg.registerVar("univibe.fb",N_("Fb"),"S",N_("sound modification by feedback"),&self.fb,0,-1,1,0.01);
    reg.registerVar("univibe.lrcross",N_("L/R.Cr"),"S",N_("left/right channel crossing"),&self.flrcross,0,-1,1,0.01);
    return 0;
}

int Vibe::uiloader(const UiBuilder& b) {
    b.openHorizontalhideBox("");
    {
        b.create_master_slider("univibe.wet_dry",0);
    }
    b.closeBox();
    b.openVerticalBox("");
    {
	b.openHorizontalBox("");
	{
	    b.create_selector("univibe.lfo_type");
	    b.create_small_rackknob("univibe.freq",0);
	    b.create_small_rackknob("univibe.depth",0);
	    b.create_small_rackknob("univibe.width",0);
	    b.create_small_rackknob("univibe.randomness",0);
	}
	b.closeBox();
	b.openHorizontalBox("");
	{
	    b.create_small_rackknob("univibe.fb",0);
	    b.create_small_rackknob("univibe.stereo",0);
	    b.create_small_rackknob("univibe.panning",0);
	    b.create_small_rackknob("univibe.lrcross",0);
	    b.create_small_rackknob("univibe.wet_dry",0);
	}
	b.closeBox();
    }
    b.closeBox();
    return 0;
}

void Vibe::out(int count, float *smpsl, float *smpsr, float * efxoutl, float * efxoutr) {
    if (lfo.PERIOD != count) {
	lfo.init(fSAMPLE_RATE, count);
    }
    fcross = 1 - std::abs(flrcross);
    setpanning();
    lfo.updateparams();
    int i,j;
    float lfol, lfor, xl, xr, fxl, fxr;
    float vbe,vin;
    float cvolt, ocvolt, evolt, input;
    float emitterfb = 0.0f;
    float outl, outr;
  
    input = cvolt = ocvolt = evolt = 0.0f;
  
    lfo.effectlfoout (&lfol, &lfor);

    lfol = 1 - fdepth + lfol*fwidth;
    lfor = 1 - fdepth + lfor*fwidth;   
  
    if (lfol > 1.0f) {
	lfol = 1.0f;
    } else if (lfol < 0.0f) {
	lfol = 0.0f;
    }
    if (lfor > 1.0f) {
	lfor = 1.0f;
    } else if (lfor < 0.0f) {
	lfor = 0.0f;  
    }
    lfor = 2.0f - 2.0f/(lfor + 1.0f);   // 
    lfol = 2.0f - 2.0f/(lfol + 1.0f); //emulate lamp turn on/off characteristic by typical curves 
      
    for (i = 0; i < count; i++) {
	//Left Lamp
	gl = lfol*lampTC + oldgl*ilampTC; 
	oldgl = gl;  
	//Right Lamp
	gr = lfor*lampTC + oldgr*ilampTC; 
	oldgr = gr;   

	//Left Cds   
	stepl = gl*alphal + dalphal*oldstepl;
	oldstepl = stepl;
	dRCl = dTC*expf(stepl*minTC);
	alphal = cSAMPLE_RATE/(dRCl + cSAMPLE_RATE);  
	dalphal = 1.0f - cSAMPLE_RATE/(0.5f*dRCl + cSAMPLE_RATE);     //different attack & release character
	xl = M_E + stepl*b;
	fxl = expf(Ra/logf(xl));   

	//Right Cds   
	stepr = gr*alphar + dalphar*oldstepr;
	oldstepr = stepr;
	dRCr = dTC*expf(stepr*minTC);
	alphar = cSAMPLE_RATE/(dRCr + cSAMPLE_RATE);  
	dalphar = 1.0f - cSAMPLE_RATE/(0.5f*dRCr + cSAMPLE_RATE);      //different attack & release character
	xr = M_E + stepr*b;
	fxr = expf(Ra/logf(xr));

	if(i%16 == 0) {
	    modulate(fxl, fxr);
	}
     
	//Left Channel  

	vin = 7.5f*(1.0f + fbl+smpsl[i]);
	if (vin<0.0f) {
	    vin = 0.0f;
	}
	if (vin>15.0f) {
	    vin = 15.0f;
	}
	vbe = 0.8f - 0.8f/(vin + 1.0f);  //really rough, simplistic bjt turn-on emulator
	input = vin - vbe;
	input = input*0.1333333333f -0.90588f;  //some magic numbers to return gain to unity & zero the DC
    
	emitterfb = 25.0f/fxl;     
	for(j=0;j<4;j++) { //4 stages phasing
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
	    if (vin>15.0f) {
		vin = 15.0f;
	    }
	    vbe = 0.8f - 0.8f/(vin + 1.0f);  //really rough, simplistic bjt turn-on emulator
	    input = vin - vbe;
	    input = input*0.1333333333f -0.90588f;  //some magic numbers to return gain to unity & zero the DC

	}
	fbl = fb*ocvolt;
	outl = lpanning*input;    
    
	//Right channel

	vin = 7.5f*(1.0f + fbr+smpsr[i]);
	if (vin<0.0f) {
	    vin = 0.0f;
	}
	if (vin>15.0f) {
	    vin = 15.0f;
	}
	vbe = 0.8f - 0.8f/(vin + 1.0f);  //really rough, simplistic bjt turn-on emulator
	input = vin - vbe;
	input = input*0.1333333333f -0.90588f;  //some magic numbers to return gain to unity & zero the DC

	emitterfb = 25.0f/fxr;     
	for (j = 4; j < 8; j++) { //4 stages phasing
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
	    if (vin < 0.0f) {
		vin = 0.0f;
	    }
	    if (vin > 15.0f) {
		vin = 15.0f;
	    }
	    vbe = 0.8f - 0.8f/(vin + 1.0f);  //really rough, simplistic bjt turn-on emulator
	    input = vin - vbe;
	    input = input*0.1333333333f -0.90588f;  //some magic numbers to return gain to unity & zero the DC

	}

	fbr = fb*ocvolt;
	outr = rpanning*input;  

	float v1, v2;
	if (wet_dry < 0.5) {
	    v1 = 1.0;
	    v2 = wet_dry * 2;
	} else {
	    v1 = (1 - wet_dry) * 2;
	    v2 = 1.0;
	}
	efxoutl[i] = v2 * (outl*fcross + outr*flrcross) + v1 * smpsl[i];
	efxoutr[i] = v2 * (outr*fcross + outl*flrcross) + v1 * smpsr[i];
    };
};

void Vibe::init_vibes(unsigned int samplerate) {
    fSAMPLE_RATE = samplerate;
    cSAMPLE_RATE = 1 / fSAMPLE_RATE;

    //Swing was measured on operating device of: 10K to 250k.  
    //400K is reported to sound better for the "low end" (high resistance) 
    //Because of time response, Rb needs to be driven further.
    //End resistance will max out to around 10k for most LFO freqs.
    //pushing low end a little lower for kicks and giggles
    Ra = 500000.0f;  //Cds cell dark resistance.
    Ra = logf(Ra);		//this is done for clarity 
    Rb = 600.0f;         //Cds cell full illumination
    b = exp(Ra/logf(Rb)) - M_E;
    dTC = 0.085f;
    dRCl = dTC;
    dRCr = dTC;   //Right & left channel dynamic time contsants
    minTC = logf(0.005f/dTC);
    alphal = 1.0f - cSAMPLE_RATE/(dRCl + cSAMPLE_RATE);
    alphar = alphal;
    dalphal = dalphar = alphal;
    lampTC = cSAMPLE_RATE/(0.02 + cSAMPLE_RATE);  //guessing 10ms
    ilampTC = 1.0f - lampTC;
    lstep = 0.0f;
    rstep = 0.0f;
    lpanning = 1.0f;
    rpanning = 1.0f;
    oldgl = 0.0f;
    oldgr = 0.0f;
    gl = 0.0f;
    gr = 0.0f;
    for(int jj = 0; jj < 8; jj++) {
	oldcvolt[jj] = 0.0f;
    }

    k = 2.0f*fSAMPLE_RATE;
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

void Vibe::setpanning () {
    rpanning = Ppanning+1;
    lpanning = 2.0f - rpanning;
    lpanning = 10.0f * powf(lpanning, 4);
    rpanning = 10.0f * powf(rpanning, 4);
    lpanning = 1.0f - 1.0f/(lpanning + 1.0f);
    rpanning = 1.0f - 1.0f/(rpanning + 1.0f); 
    lpanning *= 1.3f;
    rpanning *= 1.3f; 
};

extern "C" __attribute__ ((visibility ("default"))) int
get_gx_plugins(int *count, PluginDef **pplugin)
{
    static Vibe vibe;
    *count = 1;
    *pplugin = &vibe;
    return 0;
}
