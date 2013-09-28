// generated from file '../src/LV2/faust/bmfp.dsp' by dsp2cc:
// Code generated with Faust 0.9.58 (http://faust.grame.fr)


namespace bmfp {

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
	double 	fConst7;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fConst8;
	double 	fConst9;
	double 	fConst10;
	double 	fConst11;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec9[2];
	double 	fConst12;
	double 	fVec0[2];
	double 	fConst13;
	double 	fConst14;
	double 	fRec8[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fConst15;
	double 	fConst16;
	double 	fConst17;
	double 	fConst18;
	double 	fRec10[2];
	double 	fVec1[2];
	double 	fRec7[2];
	double 	fRec6[4];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fVec2[2];
	double 	fConst19;
	double 	fRec5[2];
	double 	fConst20;
	double 	fConst21;
	double 	fRec4[2];
	double 	fRec0[2];
	int 	iRec1[2];
	double 	fRec2[2];
	FAUSTFLOAT 	fbargraph0;
	FAUSTFLOAT	*fbargraph0_;
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
	id = "bmpf";
	name = N_("BigMuffFuzzPadel");
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
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<4; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) iRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (1.0 / double(iConst0));
	fConst2 = (1.0 / tan((251.32741228718345 / double(iConst0))));
	fConst3 = (1 + fConst2);
	fConst4 = (0 - ((1 - fConst2) / fConst3));
	fConst5 = (1.0 / tan((17690.308232364125 / double(iConst0))));
	fConst6 = (1 + fConst5);
	fConst7 = (0 - ((1 - fConst5) / fConst6));
	fConst8 = tan((5830.795965062656 / double(iConst0)));
	fConst9 = (1.0 / fConst8);
	fConst10 = (1 + fConst9);
	fConst11 = (0 - ((1 - fConst9) / fConst10));
	fConst12 = (0.01 / fConst8);
	fConst13 = (0 - fConst9);
	fConst14 = (1.0 / fConst10);
	fConst15 = (1.0 / tan((1281.7698026646356 / double(iConst0))));
	fConst16 = (1 + fConst15);
	fConst17 = (0 - ((1 - fConst15) / fConst16));
	fConst18 = (1.0 / fConst16);
	fConst19 = (1.0 / fConst6);
	fConst20 = (0 - fConst2);
	fConst21 = (1.0 / fConst3);
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, float *input0, float *output0)
{
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
#define fslider2 (*fslider2_)
#define fslider3 (*fslider3_)
#define fbargraph0 (*fbargraph0_)
	double 	fSlow0 = fslider0;
	double 	fSlow1 = (0.01 * fSlow0);
	double 	fSlow2 = (1 - fSlow1);
	double 	fSlow3 = (0.0010000000000000009 * pow(10,(0.05 * fslider1)));
	double 	fSlow4 = (fConst12 * fSlow0);
	double 	fSlow5 = fslider2;
	double 	fSlow6 = (1 - fSlow5);
	double 	fSlow7 = (0.25 * fslider3);
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fRec9[0] = (fSlow3 + (0.999 * fRec9[1]));
		double fTemp1 = (fTemp0 * fRec9[0]);
		double fTemp2 = (fSlow1 * fTemp1);
		fVec0[0] = fTemp2;
		fRec8[0] = ((fConst14 * ((fConst13 * fVec0[1]) + (fSlow4 * fTemp1))) + (fConst11 * fRec8[1]));
		fRec10[0] = ((fConst18 * (fVec0[0] + fVec0[1])) + (fConst17 * fRec10[1]));
		double fTemp3 = ((fSlow6 * fRec10[0]) + (fSlow5 * fRec8[0]));
		double fTemp4 = (0.15 * (faustpower<2>(fTemp3) * (1.0 + fTemp3)));
		fVec1[0] = (fTemp3 - fTemp4);
		fRec7[0] = ((fTemp3 + (0.995 * fRec7[1])) - (fTemp4 + fVec1[1]));
		fRec6[0] = (fRec7[0] + (0.3147 * fRec6[3]));
		double fTemp5 = (max(-0.7, min(0.7, (fRec6[0] * (1 + (fSlow7 * ((2 - fabs(fRec6[0])) - 1)))))) + (fSlow2 * fTemp0));
		fVec2[0] = fTemp5;
		fRec5[0] = ((fConst19 * (fVec2[0] + fVec2[1])) + (fConst7 * fRec5[1]));
		fRec4[0] = ((fConst21 * ((fConst20 * fRec5[1]) + (fConst2 * fRec5[0]))) + (fConst4 * fRec4[1]));
		double 	fRec3 = max(fConst1, fabs(fRec4[0]));
		int iTemp6 = int((iRec1[1] < 16384));
		fRec0[0] = ((iTemp6)?max(fRec0[1], fRec3):fRec3);
		iRec1[0] = ((iTemp6)?(1 + iRec1[1]):1);
		fRec2[0] = ((iTemp6)?fRec2[1]:fRec0[1]);
		fbargraph0 = fRec2[0];
		output0[i] = (FAUSTFLOAT)fRec4[0];
		// post processing
		fRec2[1] = fRec2[0];
		iRec1[1] = iRec1[0];
		fRec0[1] = fRec0[0];
		fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fVec2[1] = fVec2[0];
		for (int i=3; i>0; i--) fRec6[i] = fRec6[i-1];
		fRec7[1] = fRec7[0];
		fVec1[1] = fVec1[0];
		fRec10[1] = fRec10[0];
		fRec8[1] = fRec8[0];
		fVec0[1] = fVec0[0];
		fRec9[1] = fRec9[0];
	}
#undef fslider0
#undef fslider1
#undef fslider2
#undef fslider3
#undef fbargraph0
}

void __rt_func Dsp::compute_static(int count, float *input0, float *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case INPUT: 
		fslider1_ = (float*)data; // , 0.0, -24.0, 1e+01, 0.1 
		break;
	case OUTPUT: 
		fslider0_ = (float*)data; // , 1e+02, 5e+01, 1e+02, 1.0 
		break;
	case DRIVE: 
		fslider3_ = (float*)data; // , 1.0, -3.0, 1e+02, 1.0 
		break;
	case TONE: 
		fslider2_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case V1: 
		fbargraph0_ = (float*)data; // , -70.0, -70.0, 4.0, 0.00001 
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
   INPUT, 
   OUTPUT, 
   DRIVE, 
   TONE, 
   V1, 
} PortIndex;
*/

} // end namespace bmfp
