// generated from file '../src/LV2/faust/gxtubedelay.dsp' by dsp2cc:
// Code generated with Faust 0.9.58 (http://faust.grame.fr)

#include "valve.h"

namespace gxtubedelay {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec3[2];
	double 	fConst7;
	double 	fConst8;
	double 	fConst9;
	double 	fVec0[2];
	double 	fConst10;
	double 	fRec8[2];
	double 	fRec7[2];
	double 	fConst11;
	double 	fConst12;
	double 	fRec6[2];
	double 	fConst13;
	double 	fRec5[2];
	double 	fConst14;
	double 	fConst15;
	double 	fConst16;
	double 	fConst17;
	double 	fConst18;
	double 	fConst19;
	double 	fConst20;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fConst21;
	double 	fVec1[2];
	double 	fConst22;
	double 	fConst23;
	double 	fRec10[2];
	double 	fConst24;
	double 	fRec9[2];
	int 	IOTA;
	double *fVec2;
	double 	fConst25;
	double 	fConst26;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fConst27;
	double 	fRec11[2];
	double 	fRec12[2];
	double 	fRec13[2];
	double 	fRec14[2];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fRec4[2];
	double 	fVec3[2];
	double 	fRec15[2];
	double 	fRec2[2];
	double 	fRec1[2];
	double 	fRec0[2];
	bool mem_allocated;
	void mem_alloc();
	void mem_free();
	void connect(uint32_t port,void* data);
	void clear_state_f();
	int activate(bool start);
	void init(uint32_t samplingFreq);
	void compute(int count, float *input0, float *output0);

	static void clear_state_f_static(PluginLV2*);
	static int activate_static(bool start, PluginLV2*);
	static void init_static(uint32_t samplingFreq, PluginLV2*);
	static void compute_static(int count, float *input0, float *output0, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginLV2(),
	  fVec2(0),
	  mem_allocated(false) {
	version = PLUGINLV2_VERSION;
	id = "gxtubedelay";
	name = N_("Tube Delay");
	mono_audio = compute_static;
	stereo_audio = 0;
	set_samplerate = init_static;
	activate_plugin = activate_static;
	connect_ports = connect_static;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<262144; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (1.0 / tan((20517.741620594938 / double(iConst0))));
	fConst2 = (1 + fConst1);
	fConst3 = (0 - ((1 - fConst1) / fConst2));
	fConst4 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst5 = (1 + fConst4);
	fConst6 = (0 - ((1 - fConst4) / fConst5));
	fConst7 = (1.0 / tan((6.5973445725385655 / double(iConst0))));
	fConst8 = (1 + fConst7);
	fConst9 = (0 - ((1 - fConst7) / fConst8));
	fConst10 = (1.0 / fConst8);
	fConst11 = (0 - fConst4);
	fConst12 = (0.025 / fConst5);
	fConst13 = (1.0 / fConst2);
	fConst14 = (1.0 / tan((37699.11184307752 / double(iConst0))));
	fConst15 = (1 + fConst14);
	fConst16 = (0 - ((1 - fConst14) / fConst15));
	fConst17 = tan((376.99111843077515 / double(iConst0)));
	fConst18 = (1.0 / fConst17);
	fConst19 = (1 + fConst18);
	fConst20 = (0 - ((1 - fConst18) / fConst19));
	fConst21 = (0.1 / fConst17);
	fConst22 = (0 - fConst18);
	fConst23 = (1.0 / fConst19);
	fConst24 = (1.0 / fConst15);
	IOTA = 0;
	fConst25 = (1e+01 / double(iConst0));
	fConst26 = (0 - fConst25);
	fConst27 = (0.001 * iConst0);
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void Dsp::mem_alloc()
{
	if (!fVec2) fVec2 = new double[262144];
	mem_allocated = true;
}

void Dsp::mem_free()
{
	mem_allocated = false;
	if (fVec2) { delete fVec2; fVec2 = 0; }
}

int Dsp::activate(bool start)
{
	if (start) {
		if (!mem_allocated) {
			mem_alloc();
			clear_state_f();
		}
	} else if (mem_allocated) {
		mem_free();
	}
	return 0;
}

int Dsp::activate_static(bool start, PluginLV2 *p)
{
	return static_cast<Dsp*>(p)->activate(start);
}

void always_inline Dsp::compute(int count, float *input0, float *output0)
{
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
#define fslider2 (*fslider2_)
#define fslider3 (*fslider3_)
	double 	fSlow0 = (0.0010000000000000009 * pow(10,(0.05 * fslider0)));
	double 	fSlow1 = fslider1;
	double 	fSlow2 = (fConst21 * fSlow1);
	double 	fSlow3 = (0.1 * fSlow1);
	double 	fSlow4 = (fConst27 * fslider2);
	double 	fSlow5 = (0.1 * fslider3);
	for (int i=0; i<count; i++) {
		fRec3[0] = (fSlow0 + (0.999 * fRec3[1]));
		double fTemp0 = (1e-15 + (0.015 * fRec7[1]));
		fVec0[0] = fTemp0;
		fRec8[0] = ((fConst10 * (fVec0[0] + fVec0[1])) + (fConst9 * fRec8[1]));
		fRec7[0] = (Ftube(TUBE_TABLE_12AX7_68k, (((double)input0[i] + fRec8[0]) - 1.204540999999999)) - 169.69726666666665);
		fRec6[0] = ((fConst12 * ((fConst11 * fRec7[1]) + (fConst4 * fRec7[0]))) + (fConst6 * fRec6[1]));
		fRec5[0] = ((fConst13 * (fRec6[0] + fRec6[1])) + (fConst3 * fRec5[1]));
		fVec1[0] = (fSlow3 * fRec4[1]);
		fRec10[0] = ((fConst23 * ((fConst22 * fVec1[1]) + (fSlow2 * fRec4[1]))) + (fConst20 * fRec10[1]));
		fRec9[0] = ((fConst24 * (fRec10[0] + fRec10[1])) + (fConst16 * fRec9[1]));
		double fTemp1 = (fRec9[0] + fRec5[0]);
		fVec2[IOTA&262143] = fTemp1;
		double fTemp2 = ((int((fRec11[1] != 0.0)))?((int(((fRec12[1] > 0.0) & (fRec12[1] < 1.0))))?fRec11[1]:0):((int(((fRec12[1] == 0.0) & (fSlow4 != fRec13[1]))))?fConst25:((int(((fRec12[1] == 1.0) & (fSlow4 != fRec14[1]))))?fConst26:0)));
		fRec11[0] = fTemp2;
		fRec12[0] = max(0.0, min(1.0, (fRec12[1] + fTemp2)));
		fRec13[0] = ((int(((fRec12[1] >= 1.0) & (fRec14[1] != fSlow4))))?fSlow4:fRec13[1]);
		fRec14[0] = ((int(((fRec12[1] <= 0.0) & (fRec13[1] != fSlow4))))?fSlow4:fRec14[1]);
		fRec4[0] = (fVec2[IOTA&262143] + (fSlow5 * ((fRec12[0] * fVec2[(IOTA-int((int(fRec14[0]) & 262143)))&262143]) + ((1.0 - fRec12[0]) * fVec2[(IOTA-int((int(fRec13[0]) & 262143)))&262143]))));
		double fTemp3 = (1e-15 + (0.015 * fRec2[1]));
		fVec3[0] = fTemp3;
		fRec15[0] = ((fConst10 * (fVec3[0] + fVec3[1])) + (fConst9 * fRec15[1]));
		fRec2[0] = (Ftube(TUBE_TABLE_12AX7_250k, ((fRec15[0] + (fRec4[0] * fRec3[0])) - 1.204284999999999)) - 169.71433333333334);
		fRec1[0] = ((fConst12 * ((fConst11 * fRec2[1]) + (fConst4 * fRec2[0]))) + (fConst6 * fRec1[1]));
		fRec0[0] = ((fConst13 * (fRec1[0] + fRec1[1])) + (fConst3 * fRec0[1]));
		output0[i] = (FAUSTFLOAT)fRec0[0];
		// post processing
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec15[1] = fRec15[0];
		fVec3[1] = fVec3[0];
		fRec4[1] = fRec4[0];
		fRec14[1] = fRec14[0];
		fRec13[1] = fRec13[0];
		fRec12[1] = fRec12[0];
		fRec11[1] = fRec11[0];
		IOTA = IOTA+1;
		fRec9[1] = fRec9[0];
		fRec10[1] = fRec10[0];
		fVec1[1] = fVec1[0];
		fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
		fVec0[1] = fVec0[0];
		fRec3[1] = fRec3[0];
	}
#undef fslider0
#undef fslider1
#undef fslider2
#undef fslider3
}

void __rt_func Dsp::compute_static(int count, float *input0, float *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case DELAY: 
		fslider2_ = (float*)data; // , 0.0, 0.1, 5e+03, 0.1 
		break;
	case FEEDBACK: 
		fslider1_ = (float*)data; // , 0.0, 0.0, 1e+01, 0.1 
		break;
	case GAIN: 
		fslider0_ = (float*)data; // , 0.0, -3e+01, 6.0, 0.1 
		break;
	case LEVEL: 
		fslider3_ = (float*)data; // , 0.0, 0.0, 1e+01, 0.1 
		break;
	default:
		break;
	}
}

void Dsp::connect_static(uint32_t port,void* data, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->connect(port, data);
}


PluginLV2 *plugin() {
	return new Dsp();
}

void Dsp::del_instance(PluginLV2 *p)
{
	delete static_cast<Dsp*>(p);
}

/*
typedef enum
{
   DELAY, 
   FEEDBACK, 
   GAIN, 
   LEVEL, 
} PortIndex;
*/

} // end namespace gxtubedelay
