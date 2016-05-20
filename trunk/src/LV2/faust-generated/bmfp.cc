// generated from file '../src/LV2/faust/bmfp.dsp' by dsp2cc:
// Code generated with Faust 0.9.73 (http://faust.grame.fr)


namespace bmfp {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec3[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fVec0[2];
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fRec2[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	double 	fConst9;
	double 	fConst10;
	double 	fConst11;
	double 	fRec4[2];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fVec1[2];
	double 	fConst12;
	double 	fConst13;
	double 	fConst14;
	double 	fConst15;
	double 	fRec1[2];
	double 	fConst16;
	double 	fConst17;
	double 	fConst18;
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
	fConst1 = (1.0 / tan((1281.7698026646356 / double(iConst0))));
	fConst2 = (1 + fConst1);
	fConst3 = (1.0 / fConst2);
	fConst4 = (0 - ((1 - fConst1) / fConst2));
	fConst5 = tan((5830.795965062656 / double(iConst0)));
	fConst6 = (0.01 / fConst5);
	fConst7 = (1.0 / fConst5);
	fConst8 = (0 - fConst7);
	fConst9 = (1 + fConst7);
	fConst10 = (1.0 / fConst9);
	fConst11 = (0 - ((1 - fConst7) / fConst9));
	fConst12 = (1.0 / tan((17690.308232364125 / double(iConst0))));
	fConst13 = (1 + fConst12);
	fConst14 = (1.0 / fConst13);
	fConst15 = (0 - ((1 - fConst12) / fConst13));
	fConst16 = (1.0 / tan((251.32741228718345 / double(iConst0))));
	fConst17 = (0 - fConst16);
	fConst18 = (1 + fConst16);
	fConst19 = (1.0 / fConst18);
	fConst20 = (0 - ((1 - fConst16) / fConst18));
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
	double 	fSlow0 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider0))));
	double 	fSlow1 = double(fslider1);
	double 	fSlow2 = (0.01 * fSlow1);
	double 	fSlow3 = double(fslider2);
	double 	fSlow4 = (1 - fSlow3);
	double 	fSlow5 = (fConst6 * fSlow1);
	double 	fSlow6 = double(fslider3);
	double 	fSlow7 = (0.009900990099009901 * fSlow6);
	double 	fSlow8 = (1 + fSlow7);
	double 	fSlow9 = (0.25 * fSlow6);
	double 	fSlow10 = (1 - fSlow2);
	for (int i=0; i<count; i++) {
		fRec3[0] = ((0.999 * fRec3[1]) + fSlow0);
		double fTemp0 = (double)input0[i];
		double fTemp1 = (fTemp0 * fRec3[0]);
		double fTemp2 = (fSlow2 * fTemp1);
		fVec0[0] = fTemp2;
		fRec2[0] = ((fConst4 * fRec2[1]) + (fConst3 * (fVec0[0] + fVec0[1])));
		fRec4[0] = ((fConst11 * fRec4[1]) + (fConst10 * ((fConst8 * fVec0[1]) + (fSlow5 * fTemp1))));
		double fTemp3 = ((fSlow3 * fRec4[0]) + (fSlow4 * fRec2[0]));
		double fTemp4 = (1 + (fSlow7 * fabs(fTemp3)));
		double fTemp5 = max(-0.7, min(0.7, (fSlow8 * ((fTemp3 * (1 + (fSlow9 * ((2 - fabs((fSlow8 * (fTemp3 / fTemp4)))) - 1)))) / fTemp4))));
		double fTemp6 = ((fSlow10 * fTemp0) + (fTemp5 * (1 + faustpower<6>(fTemp5))));
		fVec1[0] = fTemp6;
		fRec1[0] = ((fConst15 * fRec1[1]) + (fConst14 * (fVec1[0] + fVec1[1])));
		fRec0[0] = ((fConst20 * fRec0[1]) + (fConst19 * ((fConst16 * fRec1[0]) + (fConst17 * fRec1[1]))));
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
		fslider0_ = (float*)data; // , 0.0, -24.0, 2e+01, 0.1 
		break;
	case OUTPUT: 
		fslider1_ = (float*)data; // , 1e+02, 5e+01, 1e+02, 1.0 
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
