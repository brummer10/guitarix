// generated from file '../src/LV2/faust/gxtubedelay.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "valve.h"

namespace gxtubedelay {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec5[2];
	double 	fVec0[2];
	double 	fRec11[2];
	double 	fRec10[3];
	double 	fVec1[2];
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fRec12[2];
	double 	fRec9[2];
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	double 	fConst9;
	double 	fRec8[2];
	double 	fConst10;
	double 	fConst11;
	double 	fConst12;
	double 	fConst13;
	double 	fRec7[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fConst14;
	double 	fConst15;
	double 	fVec2[2];
	double 	fConst16;
	double 	fConst17;
	double 	fConst18;
	double 	fConst19;
	double 	fConst20;
	double 	fRec14[2];
	double 	fConst21;
	double 	fConst22;
	double 	fConst23;
	double 	fConst24;
	double 	fRec13[2];
	int 	IOTA;
	double *fVec3;
	double 	fConst25;
	double 	fConst26;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fConst27;
	double 	fRec15[2];
	double 	fRec16[2];
	double 	fRec17[2];
	double 	fRec18[2];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fRec6[2];
	double 	fVec4[2];
	double 	fRec4[2];
	double 	fRec3[3];
	double 	fVec5[2];
	double 	fRec19[2];
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
	  fVec3(0),
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
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<3; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<262144; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<3; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
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
	fConst1 = (1.0 / tan((6.5973445725385655 / double(iConst0))));
	fConst2 = (1 + fConst1);
	fConst3 = (1.0 / fConst2);
	fConst4 = (0 - ((1 - fConst1) / fConst2));
	fConst5 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst6 = (0 - fConst5);
	fConst7 = (1 + fConst5);
	fConst8 = (0.025 / fConst7);
	fConst9 = (0 - ((1 - fConst5) / fConst7));
	fConst10 = (1.0 / tan((20517.741620594938 / double(iConst0))));
	fConst11 = (1 + fConst10);
	fConst12 = (1.0 / fConst11);
	fConst13 = (0 - ((1 - fConst10) / fConst11));
	fConst14 = tan((376.99111843077515 / double(iConst0)));
	fConst15 = (0.1 / fConst14);
	fConst16 = (1.0 / fConst14);
	fConst17 = (0 - fConst16);
	fConst18 = (1 + fConst16);
	fConst19 = (1.0 / fConst18);
	fConst20 = (0 - ((1 - fConst16) / fConst18));
	fConst21 = (1.0 / tan((37699.11184307752 / double(iConst0))));
	fConst22 = (1 + fConst21);
	fConst23 = (1.0 / fConst22);
	fConst24 = (0 - ((1 - fConst21) / fConst22));
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
	if (!fVec3) fVec3 = new double[262144];
	mem_allocated = true;
}

void Dsp::mem_free()
{
	mem_allocated = false;
	if (fVec3) { delete fVec3; fVec3 = 0; }
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
#define fslider1 (*fslider1_)
#define fslider2 (*fslider2_)
#define fslider3 (*fslider3_)
	double 	fSlow0 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider0))));
	double 	fSlow1 = double(fslider1);
	double 	fSlow2 = (fConst15 * fSlow1);
	double 	fSlow3 = (0.1 * fSlow1);
	double 	fSlow4 = (fConst27 * double(fslider2));
	double 	fSlow5 = (0.1 * double(fslider3));
	for (int i=0; i<count; i++) {
		fRec5[0] = ((0.999 * fRec5[1]) + fSlow0);
		double fTemp0 = ((double)input0[i] + 1e-15);
		fVec0[0] = fTemp0;
		fRec11[0] = ((0.9302847925323914 * (fVec0[0] + fVec0[1])) - (0.8605695850647829 * fRec11[1]));
		fRec10[0] = (fRec11[0] - ((1.8405051250752198 * fRec10[1]) + (0.8612942439318627 * fRec10[2])));
		double fTemp1 = (1e-15 + (0.015 * fRec9[1]));
		fVec1[0] = fTemp1;
		fRec12[0] = ((fConst4 * fRec12[1]) + (fConst3 * (fVec1[0] + fVec1[1])));
		fRec9[0] = (Ftube(TUBE_TABLE_12AX7_68k, ((fRec12[0] + (0.9254498422517706 * (fRec10[2] + (fRec10[0] + (2.0 * fRec10[1]))))) - 1.204541)) - 169.69726666666665);
		fRec8[0] = ((fConst9 * fRec8[1]) + (fConst8 * ((fConst5 * fRec9[0]) + (fConst6 * fRec9[1]))));
		fRec7[0] = ((fConst13 * fRec7[1]) + (fConst12 * (fRec8[0] + fRec8[1])));
		fVec2[0] = (fSlow3 * fRec6[1]);
		fRec14[0] = ((fConst20 * fRec14[1]) + (fConst19 * ((fConst17 * fVec2[1]) + (fSlow2 * fRec6[1]))));
		fRec13[0] = ((fConst24 * fRec13[1]) + (fConst23 * (fRec14[0] + fRec14[1])));
		double fTemp2 = (fRec13[0] + fRec7[0]);
		fVec3[IOTA&262143] = fTemp2;
		double fTemp3 = ((int((fRec15[1] != 0.0)))?((int(((fRec16[1] > 0.0) & (fRec16[1] < 1.0))))?fRec15[1]:0):((int(((fRec16[1] == 0.0) & (fSlow4 != fRec17[1]))))?fConst25:((int(((fRec16[1] == 1.0) & (fSlow4 != fRec18[1]))))?fConst26:0)));
		fRec15[0] = fTemp3;
		fRec16[0] = max(0.0, min(1.0, (fRec16[1] + fTemp3)));
		fRec17[0] = ((int(((fRec16[1] >= 1.0) & (fRec18[1] != fSlow4))))?fSlow4:fRec17[1]);
		fRec18[0] = ((int(((fRec16[1] <= 0.0) & (fRec17[1] != fSlow4))))?fSlow4:fRec18[1]);
		fRec6[0] = (fVec3[IOTA&262143] + (fSlow5 * (((1.0 - fRec16[0]) * fVec3[(IOTA-int((int(fRec17[0]) & 262143)))&262143]) + (fRec16[0] * fVec3[(IOTA-int((int(fRec18[0]) & 262143)))&262143]))));
		double fTemp4 = (1e-15 + (fRec6[0] * fRec5[0]));
		fVec4[0] = fTemp4;
		fRec4[0] = ((0.9302847925323914 * (fVec4[0] + fVec4[1])) - (0.8605695850647829 * fRec4[1]));
		fRec3[0] = (fRec4[0] - ((1.8405051250752198 * fRec3[1]) + (0.8612942439318627 * fRec3[2])));
		double fTemp5 = (1e-15 + (0.015 * fRec2[1]));
		fVec5[0] = fTemp5;
		fRec19[0] = ((fConst4 * fRec19[1]) + (fConst3 * (fVec5[0] + fVec5[1])));
		fRec2[0] = (Ftube(TUBE_TABLE_12AX7_250k, ((fRec19[0] + (0.9254498422517706 * (fRec3[2] + (fRec3[0] + (2.0 * fRec3[1]))))) - 1.204285)) - 169.71433333333334);
		fRec1[0] = ((fConst9 * fRec1[1]) + (fConst8 * ((fConst5 * fRec2[0]) + (fConst6 * fRec2[1]))));
		fRec0[0] = ((fConst13 * fRec0[1]) + (fConst12 * (fRec1[0] + fRec1[1])));
		output0[i] = (FAUSTFLOAT)fRec0[0];
		// post processing
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec19[1] = fRec19[0];
		fVec5[1] = fVec5[0];
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fVec4[1] = fVec4[0];
		fRec6[1] = fRec6[0];
		fRec18[1] = fRec18[0];
		fRec17[1] = fRec17[0];
		fRec16[1] = fRec16[0];
		fRec15[1] = fRec15[0];
		IOTA = IOTA+1;
		fRec13[1] = fRec13[0];
		fRec14[1] = fRec14[0];
		fVec2[1] = fVec2[0];
		fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
		fRec9[1] = fRec9[0];
		fRec12[1] = fRec12[0];
		fVec1[1] = fVec1[0];
		fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		fVec0[1] = fVec0[0];
		fRec5[1] = fRec5[0];
	}
#undef fslider0
#undef fslider1
#undef fslider2
#undef fslider3
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
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
