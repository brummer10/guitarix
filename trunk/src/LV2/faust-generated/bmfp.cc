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
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fConst7;
	double 	fConst8;
	double 	fConst9;
	double 	fConst10;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec3[2];
	double 	fConst11;
	double 	fVec0[2];
	double 	fConst12;
	double 	fConst13;
	double 	fRec2[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fConst14;
	double 	fConst15;
	double 	fConst16;
	double 	fConst17;
	double 	fRec4[2];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fVec1[2];
	double 	fConst18;
	double 	fRec1[2];
	double 	fConst19;
	double 	fConst20;
	double 	fRec0[2];
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
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
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
	fConst1 = (1.0 / tan((251.32741228718345 / double(iConst0))));
	fConst2 = (1 + fConst1);
	fConst3 = (0 - ((1 - fConst1) / fConst2));
	fConst4 = (1.0 / tan((17690.308232364125 / double(iConst0))));
	fConst5 = (1 + fConst4);
	fConst6 = (0 - ((1 - fConst4) / fConst5));
	fConst7 = tan((5830.795965062656 / double(iConst0)));
	fConst8 = (1.0 / fConst7);
	fConst9 = (1 + fConst8);
	fConst10 = (0 - ((1 - fConst8) / fConst9));
	fConst11 = (0.01 / fConst7);
	fConst12 = (0 - fConst8);
	fConst13 = (1.0 / fConst9);
	fConst14 = (1.0 / tan((1281.7698026646356 / double(iConst0))));
	fConst15 = (1 + fConst14);
	fConst16 = (0 - ((1 - fConst14) / fConst15));
	fConst17 = (1.0 / fConst15);
	fConst18 = (1.0 / fConst5);
	fConst19 = (0 - fConst1);
	fConst20 = (1.0 / fConst2);
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
#define fslider2 (*fslider2_)
#define fslider3 (*fslider3_)
	double 	fSlow0 = fslider0;
	double 	fSlow1 = (0.01 * fSlow0);
	double 	fSlow2 = (1 - fSlow1);
	double 	fSlow3 = (0.0010000000000000009 * pow(10,(0.05 * fslider1)));
	double 	fSlow4 = (fConst11 * fSlow0);
	double 	fSlow5 = fslider2;
	double 	fSlow6 = (1 - fSlow5);
	double 	fSlow7 = fslider3;
	double 	fSlow8 = (0.009900990099009901 * fSlow7);
	double 	fSlow9 = (1 + fSlow8);
	double 	fSlow10 = (0.25 * fSlow7);
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fRec3[0] = (fSlow3 + (0.999 * fRec3[1]));
		double fTemp1 = (fTemp0 * fRec3[0]);
		double fTemp2 = (fSlow1 * fTemp1);
		fVec0[0] = fTemp2;
		fRec2[0] = ((fConst13 * ((fConst12 * fVec0[1]) + (fSlow4 * fTemp1))) + (fConst10 * fRec2[1]));
		fRec4[0] = ((fConst17 * (fVec0[0] + fVec0[1])) + (fConst16 * fRec4[1]));
		double fTemp3 = ((fSlow6 * fRec4[0]) + (fSlow5 * fRec2[0]));
		double fTemp4 = (1 + (fSlow8 * fabs(fTemp3)));
		double fTemp5 = (max(-0.7, min(0.7, (fSlow9 * ((fTemp3 * (1 + (fSlow10 * ((2 - fabs((fSlow9 * (fTemp3 / fTemp4)))) - 1)))) / fTemp4)))) + (fSlow2 * fTemp0));
		fVec1[0] = fTemp5;
		fRec1[0] = ((fConst18 * (fVec1[0] + fVec1[1])) + (fConst6 * fRec1[1]));
		fRec0[0] = ((fConst20 * ((fConst19 * fRec1[1]) + (fConst1 * fRec1[0]))) + (fConst3 * fRec0[1]));
		output0[i] = (FAUSTFLOAT)fRec0[0];
		// post processing
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fVec1[1] = fVec1[0];
		fRec4[1] = fRec4[0];
		fRec2[1] = fRec2[0];
		fVec0[1] = fVec0[0];
		fRec3[1] = fRec3[0];
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
} PortIndex;
*/

} // end namespace bmfp
