// generated from file '../src/LV2/faust/uniBar.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)


namespace uniBar {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT	*fcheckbox0_;
	double 	fConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fRec7[2];
	double 	fConst3;
	double 	fConst4;
	double 	fRec6[2];
	double 	fConst5;
	double 	fRec8[2];
	double 	fConst6;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	int 	IOTA;
	double 	fVec0[4096];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fConst7;
	double 	fConst8;
	double 	fConst9;
	double 	fConst10;
	double 	fRec5[3];
	double 	fConst11;
	double 	fConst12;
	double 	fConst13;
	double 	fRec4[2];
	double 	fRec0[2];
	double 	fVec1[4096];
	double 	fConst14;
	double 	fConst15;
	double 	fRec10[3];
	double 	fRec9[2];
	double 	fRec1[2];
	double 	fVec2[2048];
	double 	fConst16;
	double 	fConst17;
	double 	fRec12[3];
	double 	fRec11[2];
	double 	fRec2[2];
	double 	fVec3[2048];
	double 	fConst18;
	double 	fConst19;
	double 	fRec14[3];
	double 	fRec13[2];
	double 	fRec3[2];

	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(uint32_t samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(uint32_t samplingFreq, PluginLV2*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginLV2() {
	version = PLUGINLV2_VERSION;
	id = "uniBar";
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
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<4096; i++) fVec0[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<4096; i++) fVec1[i] = 0;
	for (int i=0; i<3; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2048; i++) fVec2[i] = 0;
	for (int i=0; i<3; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2048; i++) fVec3[i] = 0;
	for (int i=0; i<3; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = min(1.92e+05, max(1.0, (double)fSamplingFreq));
	fConst1 = (0.02 * fConst0);
	fConst2 = (0.025 * fConst0);
	fConst3 = (199.99999999999997 / fConst0);
	fConst4 = (5e+01 / fConst0);
	fConst5 = (0.01 * fConst0);
	fConst6 = (1e+02 / fConst0);
	fConst7 = (1 - (100.53096491487338 / fConst0));
	fConst8 = faustpower<2>(fConst7);
	fConst9 = (6.283185307179586 / fConst0);
	fConst10 = (0 - (2 * fConst7));
	fConst11 = (0.5 * fConst8);
	fConst12 = (fConst11 - 0.5);
	fConst13 = (0.5 - fConst11);
	fConst14 = (0.362844702467344 * fConst0);
	fConst15 = (17.31645870658694 / fConst0);
	fConst16 = (0.1850481125092524 * fConst0);
	fConst17 = (33.95433339999848 / fConst0);
	fConst18 = (0.1119444755401321 * fConst0);
	fConst19 = (56.127694349035245 / fConst0);
	IOTA = 0;
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fcheckbox0 (*fcheckbox0_)
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
	double 	fSlow0 = double(fcheckbox0);
	double 	fSlow1 = (0.9 * fSlow0);
	int 	iSlow2 = int(((fSlow0 == 0) > 0));
	double 	fSlow3 = (fConst3 * (fSlow1 - 1));
	int 	iSlow4 = (fSlow0 > 0);
	int 	iSlow5 = faustpower<2>(iSlow4);
	int 	iSlow6 = (1 - iSlow4);
	int 	iSlow7 = int((iSlow4 > 0));
	double 	fSlow8 = double(fslider0);
	double 	fSlow9 = (0.03 + fSlow8);
	double 	fSlow10 = (2.5 * (fSlow0 * fSlow8));
	double 	fSlow11 = double(fslider1);
	int 	iSlow12 = int((int((fConst0 / fSlow11)) & 4095));
	double 	fSlow13 = (fConst10 * cos((fConst9 * fSlow11)));
	int 	iSlow14 = int((int((fConst14 / fSlow11)) & 4095));
	double 	fSlow15 = (fConst10 * cos((fConst15 * fSlow11)));
	int 	iSlow16 = int((int((fConst16 / fSlow11)) & 4095));
	double 	fSlow17 = (fConst10 * cos((fConst17 * fSlow11)));
	int 	iSlow18 = int((int((fConst18 / fSlow11)) & 4095));
	double 	fSlow19 = (fConst10 * cos((fConst19 * fSlow11)));
	for (int i=0; i<count; i++) {
		fRec7[0] = ((iSlow2)?0:min(fConst2, (1 + fRec7[1])));
		int iTemp0 = int((fRec7[0] < fConst1));
		fRec6[0] = ((iSlow6 * fRec6[1]) + (iSlow5 * ((iTemp0)?((int((fRec7[0] < 0)))?0:((iTemp0)?(fConst4 * fRec7[0]):1)):((int((fRec7[0] < fConst2)))?(1 + (fSlow3 * (fRec7[0] - fConst1))):fSlow1))));
		fRec8[0] = ((iSlow7)?0:min(fConst5, (1 + fRec8[1])));
		double fTemp1 = ((fSlow9 * ((int((fRec8[0] < 0)))?fRec6[0]:((int((fRec8[0] < fConst5)))?(fRec6[0] + (fConst6 * (fRec8[0] * (0 - fRec6[0])))):0))) - (0.9999999999999999 * (0.8000000000000002 + (fRec3[1] + ((fRec0[1] + fRec2[1]) + fRec1[1])))));
		double fTemp2 = faustpower<4>((0.75 + fabs(fTemp1)));
		double fTemp3 = (1.0 / fTemp2);
		double fTemp4 = (0.25 * (fTemp1 * ((fTemp3 > 1) + (double((fTemp3 <= 1)) / fTemp2))));
		fVec0[IOTA&4095] = (fSlow10 + (fRec4[1] + fTemp4));
		fRec5[0] = (0 - (((fSlow13 * fRec5[1]) + (fConst8 * fRec5[2])) - (0.9 * fVec0[(IOTA-iSlow12)&4095])));
		fRec4[0] = ((fConst13 * fRec5[0]) + (fConst12 * fRec5[2]));
		fRec0[0] = fRec4[0];
		fVec1[IOTA&4095] = (fSlow10 + (fRec9[1] + fTemp4));
		fRec10[0] = (0 - (((fConst8 * fRec10[2]) + (fSlow15 * fRec10[1])) - (0.81 * fVec1[(IOTA-iSlow14)&4095])));
		fRec9[0] = ((fConst13 * fRec10[0]) + (fConst12 * fRec10[2]));
		fRec1[0] = fRec9[0];
		fVec2[IOTA&2047] = (fSlow10 + (fRec11[1] + fTemp4));
		fRec12[0] = (0 - (((fConst8 * fRec12[2]) + (fSlow17 * fRec12[1])) - (0.7290000000000001 * fVec2[(IOTA-iSlow16)&2047])));
		fRec11[0] = ((fConst13 * fRec12[0]) + (fConst12 * fRec12[2]));
		fRec2[0] = fRec11[0];
		fVec3[IOTA&2047] = (fSlow10 + (fRec13[1] + fTemp4));
		fRec14[0] = (0 - (((fConst8 * fRec14[2]) + (fSlow19 * fRec14[1])) - (0.6561 * fVec3[(IOTA-iSlow18)&2047])));
		fRec13[0] = ((fConst13 * fRec14[0]) + (fConst12 * fRec14[2]));
		fRec3[0] = fRec13[0];
		output0[i] = (FAUSTFLOAT)(fRec0[0] + (fRec1[0] + (fRec2[0] + ((double)input0[i] + fRec3[0]))));
		// post processing
		fRec3[1] = fRec3[0];
		fRec13[1] = fRec13[0];
		fRec14[2] = fRec14[1]; fRec14[1] = fRec14[0];
		fRec2[1] = fRec2[0];
		fRec11[1] = fRec11[0];
		fRec12[2] = fRec12[1]; fRec12[1] = fRec12[0];
		fRec1[1] = fRec1[0];
		fRec9[1] = fRec9[0];
		fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
		fRec0[1] = fRec0[0];
		fRec4[1] = fRec4[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		IOTA = IOTA+1;
		fRec8[1] = fRec8[0];
		fRec6[1] = fRec6[0];
		fRec7[1] = fRec7[0];
	}
#undef fcheckbox0
#undef fslider0
#undef fslider1
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case GAIN: 
		fslider0_ = (float*)data; // , 0.8, 0.0, 1e+01, 0.01 
		break;
	case GATE: 
		fcheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case SYNTHFREQ: 
		fslider1_ = (float*)data; // , 4.4e+02, 2e+01, 2e+04, 1.0 
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
   GAIN, 
   GATE, 
   SYNTHFREQ, 
} PortIndex;
*/

} // end namespace uniBar
