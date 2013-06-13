// generated from file '../src/LV2/faust/uniBar.dsp' by dsp2cc:
// Code generated with Faust 0.9.57 (http://faust.grame.fr)


namespace uniBar {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT	*fcheckbox0_;
	int 	iRec6[2];
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fRec7[2];
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	int 	IOTA;
	double 	fVec0[4096];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fRec5[3];
	double 	fConst8;
	double 	fConst9;
	double 	fConst10;
	double 	fRec4[2];
	double 	fRec0[2];
	double 	fVec1[4096];
	double 	fConst11;
	double 	fConst12;
	double 	fRec9[3];
	double 	fRec8[2];
	double 	fRec1[2];
	double 	fVec2[2048];
	double 	fConst13;
	double 	fConst14;
	double 	fRec11[3];
	double 	fRec10[2];
	double 	fRec2[2];
	double 	fVec3[2048];
	double 	fConst15;
	double 	fConst16;
	double 	fRec13[3];
	double 	fRec12[2];
	double 	fRec3[2];
	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(uint32_t samplingFreq);
	void compute(int count, float *input0, float *output0);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(uint32_t samplingFreq, PluginLV2*);
	static void compute_static(int count, float *input0, float *output0, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginLV2() {
	version = PLUGINLV2_VERSION;
	id = "Basic Parameters";
	name = N_("Nonlinear Banded Waveguide Models");
	mono_audio = compute_static;
	stereo_audio = 0;
	set_samplerate = init_static;
	activate_plugin = 0;
	connect_ports = connect_static;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int i=0; i<2; i++) iRec6[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<4096; i++) fVec0[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<4096; i++) fVec1[i] = 0;
	for (int i=0; i<3; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2048; i++) fVec2[i] = 0;
	for (int i=0; i<3; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2048; i++) fVec3[i] = 0;
	for (int i=0; i<3; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (1 - (1.0 / pow(9e+04,(1e+02 / double(iConst0)))));
	fConst2 = (1 - pow(9e+01,(2e+02 / double(iConst0))));
	fConst3 = (5e+01 / double(iConst0));
	IOTA = 0;
	fConst4 = (6.283185307179586 / double(iConst0));
	fConst5 = (1 - (100.53096491487338 / double(iConst0)));
	fConst6 = (0 - (2 * fConst5));
	fConst7 = faustpower<2>(fConst5);
	fConst8 = (0.5 * fConst7);
	fConst9 = (0.5 - fConst8);
	fConst10 = (fConst8 - 0.5);
	fConst11 = (0.362844702467344 * iConst0);
	fConst12 = (17.31645870658694 / double(iConst0));
	fConst13 = (0.1850481125092524 * iConst0);
	fConst14 = (33.95433339999848 / double(iConst0));
	fConst15 = (0.1119444755401321 * iConst0);
	fConst16 = (56.127694349035245 / double(iConst0));
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, float *input0, float *output0)
{
#define fcheckbox0 (*fcheckbox0_)
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
	double 	fSlow0 = fcheckbox0;
	int 	iSlow1 = (fSlow0 > 0);
	int 	iSlow2 = (fSlow0 <= 0);
	double 	fSlow3 = fslider0;
	double 	fSlow4 = (0.03 + fSlow3);
	double 	fSlow5 = (2.5 * (fSlow0 * fSlow3));
	double 	fSlow6 = fslider1;
	int 	iSlow7 = int((int((double(iConst0) / fSlow6)) & 4095));
	double 	fSlow8 = (fConst6 * cos((fConst4 * fSlow6)));
	int 	iSlow9 = int((int((fConst11 / fSlow6)) & 4095));
	double 	fSlow10 = (fConst6 * cos((fConst12 * fSlow6)));
	int 	iSlow11 = int((int((fConst13 / fSlow6)) & 4095));
	double 	fSlow12 = (fConst6 * cos((fConst14 * fSlow6)));
	int 	iSlow13 = int((int((fConst15 / fSlow6)) & 4095));
	double 	fSlow14 = (fConst6 * cos((fConst16 * fSlow6)));
	for (int i=0; i<count; i++) {
		iRec6[0] = (iSlow1 & (iRec6[1] | (fRec7[1] >= 1)));
		int iTemp0 = (iSlow2 & (fRec7[1] > 0));
		fRec7[0] = (((iTemp0 == 0) | (fRec7[1] >= 1e-06)) * ((fConst3 * (((iRec6[1] == 0) & iSlow1) & (fRec7[1] < 1))) + (fRec7[1] * ((1 - (fConst2 * (iRec6[1] & (fRec7[1] > 90)))) - (fConst1 * iTemp0)))));
		double fTemp1 = ((fSlow4 * fRec7[0]) - (0.9999999999999999 * ((fRec3[1] + fRec1[1]) + (0.8000000000000002 + (fRec2[1] + fRec0[1])))));
		double fTemp2 = faustpower<4>((0.75 + fabs(fTemp1)));
		double fTemp3 = (1.0 / fTemp2);
		double fTemp4 = (0.25 * (fTemp1 * ((double((fTemp3 <= 1)) / fTemp2) + (fTemp3 > 1))));
		fVec0[IOTA&4095] = (fSlow5 + (fTemp4 + fRec4[1]));
		fRec5[0] = (0 - (((fConst7 * fRec5[2]) + (fSlow8 * fRec5[1])) - (0.9 * fVec0[(IOTA-iSlow7)&4095])));
		fRec4[0] = ((fConst10 * fRec5[2]) + (fConst9 * fRec5[0]));
		fRec0[0] = fRec4[0];
		fVec1[IOTA&4095] = (fSlow5 + (fTemp4 + fRec8[1]));
		fRec9[0] = (0 - (((fConst7 * fRec9[2]) + (fSlow10 * fRec9[1])) - (0.81 * fVec1[(IOTA-iSlow9)&4095])));
		fRec8[0] = ((fConst10 * fRec9[2]) + (fConst9 * fRec9[0]));
		fRec1[0] = fRec8[0];
		fVec2[IOTA&2047] = (fSlow5 + (fTemp4 + fRec10[1]));
		fRec11[0] = (0 - (((fConst7 * fRec11[2]) + (fSlow12 * fRec11[1])) - (0.7290000000000001 * fVec2[(IOTA-iSlow11)&2047])));
		fRec10[0] = ((fConst10 * fRec11[2]) + (fConst9 * fRec11[0]));
		fRec2[0] = fRec10[0];
		fVec3[IOTA&2047] = (fSlow5 + (fTemp4 + fRec12[1]));
		fRec13[0] = (0 - (((fConst7 * fRec13[2]) + (fSlow14 * fRec13[1])) - (0.6561 * fVec3[(IOTA-iSlow13)&2047])));
		fRec12[0] = ((fConst10 * fRec13[2]) + (fConst9 * fRec13[0]));
		fRec3[0] = fRec12[0];
		output0[i] = (FAUSTFLOAT)(fRec3[0] + (fRec2[0] + (fRec1[0] + ((double)input0[i] + fRec0[0]))));
		// post processing
		fRec3[1] = fRec3[0];
		fRec12[1] = fRec12[0];
		fRec13[2] = fRec13[1]; fRec13[1] = fRec13[0];
		fRec2[1] = fRec2[0];
		fRec10[1] = fRec10[0];
		fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
		fRec1[1] = fRec1[0];
		fRec8[1] = fRec8[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec0[1] = fRec0[0];
		fRec4[1] = fRec4[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		IOTA = IOTA+1;
		fRec7[1] = fRec7[0];
		iRec6[1] = iRec6[0];
	}
#undef fcheckbox0
#undef fslider0
#undef fslider1
}

void __rt_func Dsp::compute_static(int count, float *input0, float *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case GATE: 
		fcheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case SYNTHFREQ: 
		fslider1_ = (float*)data; // , 4.4e+02, 2e+01, 2e+04, 1.0 
		break;
	case GAIN: 
		fslider0_ = (float*)data; // , 0.8, 0.0, 1e+01, 0.01 
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
   GATE, 
   SYNTHFREQ, 
   GAIN, 
} PortIndex;
*/

} // end namespace uniBar
