// generated from file '../src/LV2/faust/gxtubevibrato.dsp' by dsp2cc:
// Code generated with Faust 0.9.46 (http://faust.grame.fr)

#include "valve.h"

namespace gxtubevibrato {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	int 	iVec0[2];
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	double 	fConst9;
	double 	fVec1[2];
	double 	fConst10;
	double 	fRec5[2];
	double 	fRec4[2];
	double 	fConst11;
	double 	fConst12;
	int 	IOTA;
	double *fRec3;
	double 	fConst13;
	double 	fConst14;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fConst15;
	int 	iRec11[2];
	int 	iRec10[2];
	double 	fConst16;
	double 	fRec14[2];
	double 	fRec13[2];
	double 	fRec12[2];
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT	*fcheckbox0_;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fConst17;
	double 	fRec6[2];
	double 	fRec7[2];
	double 	fRec8[2];
	double 	fRec9[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec15[2];
	double 	fVec2[2];
	double 	fConst18;
	double 	fRec2[2];
	double 	fConst19;
	double 	fConst20;
	double 	fConst21;
	double 	fVec3[2];
	double 	fConst22;
	double 	fRec16[2];
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
	  fRec3(0),
	  mem_allocated(false) {
	version = PLUGINLV2_VERSION;
	id = "gxtubevibrato";
	name = "?gxtubevibrato";
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
	for (int i=0; i<2; i++) iVec0[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<65536; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) iRec11[i] = 0;
	for (int i=0; i<2; i++) iRec10[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
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
	fConst1 = (1.0 / tan((97.38937226128358 / iConst0)));
	fConst2 = (1 + fConst1);
	fConst3 = (0 - ((1 - fConst1) / fConst2));
	fConst4 = (1.0 / tan((20517.741620594938 / iConst0)));
	fConst5 = (1 + fConst4);
	fConst6 = (0 - ((1 - fConst4) / fConst5));
	fConst7 = (1.0 / tan((376.99111843077515 / iConst0)));
	fConst8 = (1 + fConst7);
	fConst9 = (0 - ((1 - fConst7) / fConst8));
	fConst10 = (1.0 / fConst8);
	fConst11 = (0 - fConst1);
	fConst12 = (0.025 / fConst2);
	IOTA = 0;
	fConst13 = (1e+01 / iConst0);
	fConst14 = (0 - fConst13);
	fConst15 = (0.5 * iConst0);
	fConst16 = (6.283185307179586 / iConst0);
	fConst17 = (0.005 * iConst0);
	fConst18 = (1.0 / fConst5);
	fConst19 = (1.0 / tan((251.32741228718345 / iConst0)));
	fConst20 = (1 + fConst19);
	fConst21 = (0 - ((1 - fConst19) / fConst20));
	fConst22 = (1.0 / fConst20);
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void Dsp::mem_alloc()
{
	if (!fRec3) fRec3 = new double[65536];
	mem_allocated = true;
}

void Dsp::mem_free()
{
	mem_allocated = false;
	if (fRec3) { delete fRec3; fRec3 = 0; }
}

int Dsp::activate(bool start)
{
	if (start) {
		if (!mem_allocated) {
			mem_alloc();
			clear_state_f();
		}
	} else if (!mem_allocated) {
		mem_free();
	}
	return 0;
}

int Dsp::activate_static(bool start, PluginLV2 *p)
{
	return static_cast<Dsp*>(p)->activate(start);
}

inline void Dsp::compute(int count, float *input0, float *output0)
{
#define fslider0 (*fslider0_)
#define fcheckbox0 (*fcheckbox0_)
#define fslider1 (*fslider1_)
#define fslider2 (*fslider2_)
	double 	fSlow0 = fslider0;
	int 	iSlow1 = int((fConst15 / double(fSlow0)));
	double 	fSlow2 = (1.0 / iSlow1);
	double 	fSlow3 = (fConst16 * fSlow0);
	int 	iSlow4 = int(fcheckbox0);
	double 	fSlow5 = (fConst17 * fslider1);
	double 	fSlow6 = (0.0010000000000000009 * pow(10,(0.05 * fslider2)));
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		double fTemp0 = (1e-15 + (0.015 * fRec4[1]));
		fVec1[0] = fTemp0;
		fRec5[0] = ((fConst10 * (fVec1[0] + fVec1[1])) + (fConst9 * fRec5[1]));
		fRec4[0] = (Ftube(TUBE_TABLE_12AX7_68k, (((double)input0[i] + fRec5[0]) - 1.204540999999999)) - 169.69726666666665);
		fRec3[IOTA&65535] = ((fConst12 * ((fConst11 * fRec4[1]) + (fConst1 * fRec4[0]))) + (fConst3 * fRec3[(IOTA-1)&65535]));
		iRec11[0] = ((int((iRec11[1] > 0)))?((2 * (iRec10[1] < iSlow1)) - 1):(1 - (2 * (iRec10[1] > 0))));
		iRec10[0] = (iRec11[0] + iRec10[1]);
		fRec14[0] = ((fSlow3 * (0 - fRec12[1])) + fRec14[1]);
		fRec13[0] = ((1 + ((fSlow3 * fRec14[0]) + fRec13[1])) - iVec0[1]);
		fRec12[0] = fRec13[0];
		double fTemp1 = (fSlow5 * (1 + (1 + ((iSlow4)?max(0, (0.5 * (1 + fRec12[0]))):(fSlow2 * iRec10[0])))));
		double fTemp2 = ((int((fRec6[1] != 0.0)))?((int(((fRec7[1] > 0.0) & (fRec7[1] < 1.0))))?fRec6[1]:0):((int(((fRec7[1] == 0.0) & (fTemp1 != fRec8[1]))))?fConst13:((int(((fRec7[1] == 1.0) & (fTemp1 != fRec9[1]))))?fConst14:0)));
		fRec6[0] = fTemp2;
		fRec7[0] = max(0.0, min(1.0, (fRec7[1] + fTemp2)));
		fRec8[0] = ((int(((fRec7[1] >= 1.0) & (fRec9[1] != fTemp1))))?fTemp1:fRec8[1]);
		fRec9[0] = ((int(((fRec7[1] <= 0.0) & (fRec8[1] != fTemp1))))?fTemp1:fRec9[1]);
		fRec15[0] = (fSlow6 + (0.999 * fRec15[1]));
		double fTemp3 = (fRec15[0] * ((fRec7[0] * fRec3[(IOTA-int((int(fRec9[0]) & 65535)))&65535]) + ((1.0 - fRec7[0]) * fRec3[(IOTA-int((int(fRec8[0]) & 65535)))&65535])));
		fVec2[0] = fTemp3;
		fRec2[0] = ((fConst18 * (fVec2[0] + fVec2[1])) + (fConst6 * fRec2[1]));
		double fTemp4 = (1e-15 + (0.015 * fRec1[1]));
		fVec3[0] = fTemp4;
		fRec16[0] = ((fConst22 * (fVec3[0] + fVec3[1])) + (fConst21 * fRec16[1]));
		fRec1[0] = (Ftube(TUBE_TABLE_12AX7_250k, ((fRec16[0] + fRec2[0]) - 1.204284999999999)) - 169.71433333333334);
		fRec0[0] = ((fConst12 * ((fConst11 * fRec1[1]) + (fConst1 * fRec1[0]))) + (fConst3 * fRec0[1]));
		output0[i] = (FAUSTFLOAT)fRec0[0];
		// post processing
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fRec16[1] = fRec16[0];
		fVec3[1] = fVec3[0];
		fRec2[1] = fRec2[0];
		fVec2[1] = fVec2[0];
		fRec15[1] = fRec15[0];
		fRec9[1] = fRec9[0];
		fRec8[1] = fRec8[0];
		fRec7[1] = fRec7[0];
		fRec6[1] = fRec6[0];
		fRec12[1] = fRec12[0];
		fRec13[1] = fRec13[0];
		fRec14[1] = fRec14[0];
		iRec10[1] = iRec10[0];
		iRec11[1] = iRec11[0];
		IOTA = IOTA+1;
		fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fVec1[1] = fVec1[0];
		iVec0[1] = iVec0[0];
	}
#undef fslider0
#undef fcheckbox0
#undef fslider1
#undef fslider2
}

void __rt_func Dsp::compute_static(int count, float *input0, float *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case SPEED: 
		fslider0_ = (float*)data; // , 5.0, 0.0, 14.0, 0.1 
		break;
	// static const value_pair fcheckbox0_values[] = {{"triangle"},{"sine"},{0}};
	case SINEWAVE: 
		fcheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case DEPTH: 
		fslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case GAIN: 
		fslider2_ = (float*)data; // , 0.0, -64.0, 6.0, 0.1 
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
   SPEED, 
   SINEWAVE, 
   DEPTH, 
   GAIN, 
} PortIndex;
*/

} // end namespace gxtubevibrato
