// generated from file '../src/LV2/faust/gxtubevibrato.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "valve.h"

namespace gxtubevibrato {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	int 	iVec0[2];
	double 	fVec1[2];
	double 	fRec8[2];
	double 	fRec7[3];
	double 	fVec2[2];
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fRec9[2];
	double 	fRec6[2];
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	double 	fConst9;
	int 	IOTA;
	double *fRec5;
	double 	fConst10;
	double 	fConst11;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fConst12;
	int 	iRec15[2];
	int 	iRec14[2];
	double 	fConst13;
	double 	fRec18[2];
	double 	fRec17[2];
	double 	fRec16[2];
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT	*fcheckbox0_;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fConst14;
	double 	fRec10[2];
	double 	fRec11[2];
	double 	fRec12[2];
	double 	fRec13[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec19[2];
	double 	fVec3[2];
	double 	fConst15;
	double 	fConst16;
	double 	fConst17;
	double 	fConst18;
	double 	fRec4[2];
	double 	fVec4[2];
	double 	fRec3[2];
	double 	fRec2[3];
	double 	fVec5[2];
	double 	fConst19;
	double 	fConst20;
	double 	fConst21;
	double 	fConst22;
	double 	fRec20[2];
	double 	fRec1[2];
	double 	fRec0[2];
	bool mem_allocated;
	void mem_alloc();
	void mem_free();
	void connect(uint32_t port,void* data);
	void clear_state_f();
	int activate(bool start);
	void init(uint32_t samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);

	static void clear_state_f_static(PluginLV2*);
	static int activate_static(bool start, PluginLV2*);
	static void init_static(uint32_t samplingFreq, PluginLV2*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginLV2(),
	  fRec5(0),
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
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<3; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<65536; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) iRec15[i] = 0;
	for (int i=0; i<2; i++) iRec14[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
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
	fConst1 = (1.0 / tan((376.99111843077515 / double(iConst0))));
	fConst2 = (1 + fConst1);
	fConst3 = (1.0 / fConst2);
	fConst4 = (0 - ((1 - fConst1) / fConst2));
	fConst5 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst6 = (0 - fConst5);
	fConst7 = (1 + fConst5);
	fConst8 = (0.025 / fConst7);
	fConst9 = (0 - ((1 - fConst5) / fConst7));
	IOTA = 0;
	fConst10 = (1e+01 / double(iConst0));
	fConst11 = (0 - fConst10);
	fConst12 = (0.5 * iConst0);
	fConst13 = (6.283185307179586 / double(iConst0));
	fConst14 = (0.005 * iConst0);
	fConst15 = (1.0 / tan((20517.741620594938 / double(iConst0))));
	fConst16 = (1 + fConst15);
	fConst17 = (1.0 / fConst16);
	fConst18 = (0 - ((1 - fConst15) / fConst16));
	fConst19 = (1.0 / tan((251.32741228718345 / double(iConst0))));
	fConst20 = (1 + fConst19);
	fConst21 = (1.0 / fConst20);
	fConst22 = (0 - ((1 - fConst19) / fConst20));
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void Dsp::mem_alloc()
{
	if (!fRec5) fRec5 = new double[65536];
	mem_allocated = true;
}

void Dsp::mem_free()
{
	mem_allocated = false;
	if (fRec5) { delete fRec5; fRec5 = 0; }
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

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fslider0 (*fslider0_)
#define fcheckbox0 (*fcheckbox0_)
#define fslider1 (*fslider1_)
#define fslider2 (*fslider2_)
	double 	fSlow0 = double(fslider0);
	int 	iSlow1 = int((fConst12 / double(fSlow0)));
	double 	fSlow2 = (1.0 / double(iSlow1));
	double 	fSlow3 = (fConst13 * fSlow0);
	int 	iSlow4 = int(double(fcheckbox0));
	double 	fSlow5 = (fConst14 * double(fslider1));
	double 	fSlow6 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider2))));
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		double fTemp0 = ((double)input0[i] + 1e-15);
		fVec1[0] = fTemp0;
		fRec8[0] = ((0.9302847925323914 * (fVec1[0] + fVec1[1])) - (0.8605695850647829 * fRec8[1]));
		fRec7[0] = (fRec8[0] - ((1.8405051250752198 * fRec7[1]) + (0.8612942439318627 * fRec7[2])));
		double fTemp1 = (1e-15 + (0.015 * fRec6[1]));
		fVec2[0] = fTemp1;
		fRec9[0] = ((fConst4 * fRec9[1]) + (fConst3 * (fVec2[0] + fVec2[1])));
		fRec6[0] = (Ftube(TUBE_TABLE_12AX7_68k, ((fRec9[0] + (0.9254498422517706 * (fRec7[2] + (fRec7[0] + (2.0 * fRec7[1]))))) - 1.204541)) - 169.69726666666665);
		fRec5[IOTA&65535] = ((fConst9 * fRec5[(IOTA-1)&65535]) + (fConst8 * ((fConst5 * fRec6[0]) + (fConst6 * fRec6[1]))));
		iRec15[0] = ((int((iRec15[1] > 0)))?((2 * (iRec14[1] < iSlow1)) - 1):(1 - (2 * (iRec14[1] > 0))));
		iRec14[0] = (iRec15[0] + iRec14[1]);
		fRec18[0] = (fRec18[1] + (fSlow3 * (0 - fRec16[1])));
		fRec17[0] = ((1 + (fRec17[1] + (fSlow3 * fRec18[0]))) - iVec0[1]);
		fRec16[0] = fRec17[0];
		double fTemp2 = (fSlow5 * (1 + (1 + ((iSlow4)?max((double)0, (0.5 * (1 + fRec16[0]))):(fSlow2 * iRec14[0])))));
		double fTemp3 = ((int((fRec10[1] != 0.0)))?((int(((fRec11[1] > 0.0) & (fRec11[1] < 1.0))))?fRec10[1]:0):((int(((fRec11[1] == 0.0) & (fTemp2 != fRec12[1]))))?fConst10:((int(((fRec11[1] == 1.0) & (fTemp2 != fRec13[1]))))?fConst11:0)));
		fRec10[0] = fTemp3;
		fRec11[0] = max(0.0, min(1.0, (fRec11[1] + fTemp3)));
		fRec12[0] = ((int(((fRec11[1] >= 1.0) & (fRec13[1] != fTemp2))))?fTemp2:fRec12[1]);
		fRec13[0] = ((int(((fRec11[1] <= 0.0) & (fRec12[1] != fTemp2))))?fTemp2:fRec13[1]);
		fRec19[0] = ((0.999 * fRec19[1]) + fSlow6);
		double fTemp4 = (fRec19[0] * (((1.0 - fRec11[0]) * fRec5[(IOTA-int((int(fRec12[0]) & 65535)))&65535]) + (fRec11[0] * fRec5[(IOTA-int((int(fRec13[0]) & 65535)))&65535])));
		fVec3[0] = fTemp4;
		fRec4[0] = ((fConst18 * fRec4[1]) + (fConst17 * (fVec3[0] + fVec3[1])));
		double fTemp5 = (1e-15 + fRec4[0]);
		fVec4[0] = fTemp5;
		fRec3[0] = ((0.9302847925323914 * (fVec4[0] + fVec4[1])) - (0.8605695850647829 * fRec3[1]));
		fRec2[0] = (fRec3[0] - ((1.8405051250752198 * fRec2[1]) + (0.8612942439318627 * fRec2[2])));
		double fTemp6 = (1e-15 + (0.015 * fRec1[1]));
		fVec5[0] = fTemp6;
		fRec20[0] = ((fConst22 * fRec20[1]) + (fConst21 * (fVec5[0] + fVec5[1])));
		fRec1[0] = (Ftube(TUBE_TABLE_12AX7_250k, ((fRec20[0] + (0.9254498422517706 * (fRec2[2] + (fRec2[0] + (2.0 * fRec2[1]))))) - 1.204285)) - 169.71433333333334);
		fRec0[0] = ((fConst9 * fRec0[1]) + (fConst8 * ((fConst5 * fRec1[0]) + (fConst6 * fRec1[1]))));
		output0[i] = (FAUSTFLOAT)fRec0[0];
		// post processing
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fRec20[1] = fRec20[0];
		fVec5[1] = fVec5[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fVec4[1] = fVec4[0];
		fRec4[1] = fRec4[0];
		fVec3[1] = fVec3[0];
		fRec19[1] = fRec19[0];
		fRec13[1] = fRec13[0];
		fRec12[1] = fRec12[0];
		fRec11[1] = fRec11[0];
		fRec10[1] = fRec10[0];
		fRec16[1] = fRec16[0];
		fRec17[1] = fRec17[0];
		fRec18[1] = fRec18[0];
		iRec14[1] = iRec14[0];
		iRec15[1] = iRec15[0];
		IOTA = IOTA+1;
		fRec6[1] = fRec6[0];
		fRec9[1] = fRec9[0];
		fVec2[1] = fVec2[0];
		fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
		fVec1[1] = fVec1[0];
		iVec0[1] = iVec0[0];
	}
#undef fslider0
#undef fcheckbox0
#undef fslider1
#undef fslider2
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
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
	case SPEED: 
		fslider0_ = (float*)data; // , 5.0, 0.0, 14.0, 0.1 
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
   SINEWAVE, 
   DEPTH, 
   GAIN, 
   SPEED, 
} PortIndex;
*/

} // end namespace gxtubevibrato
