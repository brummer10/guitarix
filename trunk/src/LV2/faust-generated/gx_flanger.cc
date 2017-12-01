// generated from file '../src/LV2/faust/gx_flanger.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)


namespace gx_flanger {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	int 	iVec0[2];
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	int 	IOTA;
	double 	fVec1[1024];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fConst0;
	double 	fConst1;
	double 	fRec2[2];
	double 	fRec3[2];
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT	*fslider4_;
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT	*fslider5_;
	double 	fConst2;
	double 	fVec2[1024];
	double 	fRec1[2];
	double 	fVec3[2048];
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
	id = "flanger_mono_gx";
	name = N_("Flanger GX");
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
	for (int i=0; i<2; i++) iVec0[i] = 0;
	for (int i=0; i<1024; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<1024; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2048; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = min(1.92e+05, max(1.0, (double)fSamplingFreq));
	fConst1 = (6.283185307179586 / fConst0);
	fConst2 = (0.5 * fConst0);
	IOTA = 0;
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
#define fslider4 (*fslider4_)
#define fslider5 (*fslider5_)
	double 	fSlow0 = double(fslider1);
	double 	fSlow1 = (0.3333333333333333 * ((2 + fabs(fSlow0)) * double(fslider0)));
	double 	fSlow2 = (0 - fSlow1);
	double 	fSlow3 = double(fslider2);
	double 	fSlow4 = (0.01 * (fSlow3 * min((double)1, (1 + fSlow0))));
	double 	fSlow5 = (2 - fSlow4);
	double 	fSlow6 = (fConst1 * double(fslider3));
	double 	fSlow7 = cos(fSlow6);
	double 	fSlow8 = sin(fSlow6);
	double 	fSlow9 = (0 - fSlow8);
	double 	fSlow10 = (0.0005 * double(fslider4));
	double 	fSlow11 = (0.001 * double(fslider5));
	double 	fSlow12 = (0.01 * (min((double)1, (1 - fSlow0)) * fSlow3));
	double 	fSlow13 = (2 - fSlow12);
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		double fTemp0 = (double)input0[i];
		fVec1[IOTA&1023] = fTemp0;
		double fTemp1 = (fSlow5 * fVec1[IOTA&1023]);
		fRec2[0] = ((fSlow8 * fRec3[1]) + (fSlow7 * fRec2[1]));
		fRec3[0] = ((1 + ((fSlow7 * fRec3[1]) + (fSlow9 * fRec2[1]))) - iVec0[1]);
		double fTemp2 = (fSlow11 + (fSlow10 * (1 + fRec2[0])));
		double fTemp3 = (fConst2 * fTemp2);
		int iTemp4 = int(fTemp3);
		int iTemp5 = int((int((1 + iTemp4)) & 1023));
		double fTemp6 = floor(fTemp3);
		double fTemp7 = (fTemp3 - fTemp6);
		int iTemp8 = int((iTemp4 & 1023));
		double fTemp9 = ((1 + fTemp6) - fTemp3);
		double fTemp10 = ((fTemp9 * fVec1[(IOTA-iTemp8)&1023]) + ((fSlow1 * fRec1[1]) + (fTemp7 * fVec1[(IOTA-iTemp5)&1023])));
		fVec2[IOTA&1023] = fTemp10;
		fRec1[0] = ((fTemp9 * fVec2[(IOTA-iTemp8)&1023]) + (fTemp7 * fVec2[(IOTA-iTemp5)&1023]));
		double fTemp11 = (fSlow4 * fRec1[0]);
		double fTemp12 = (fTemp11 + (fTemp1 + (fSlow2 * fRec0[1])));
		fVec3[IOTA&2047] = fTemp12;
		double fTemp13 = (fConst0 * fTemp2);
		int iTemp14 = int(fTemp13);
		double fTemp15 = floor(fTemp13);
		fRec0[0] = ((((1 + fTemp15) - fTemp13) * fVec3[(IOTA-int((iTemp14 & 2047)))&2047]) + ((fTemp13 - fTemp15) * fVec3[(IOTA-int((int((1 + iTemp14)) & 2047)))&2047]));
		output0[i] = (FAUSTFLOAT)(0.25 * ((fSlow13 * (fTemp1 + fTemp11)) + (fSlow12 * fRec0[0])));
		// post processing
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fRec3[1] = fRec3[0];
		fRec2[1] = fRec2[0];
		IOTA = IOTA+1;
		iVec0[1] = iVec0[0];
	}
#undef fslider0
#undef fslider1
#undef fslider2
#undef fslider3
#undef fslider4
#undef fslider5
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case DEPTH: 
		fslider5_ = (float*)data; // , 0.5, 0.0, 5.0, 0.01 
		break;
	case FEEDBACK: 
		fslider0_ = (float*)data; // , -0.707, -0.99, 0.99, 0.01 
		break;
	case FREQ: 
		fslider3_ = (float*)data; // , 0.2, 0.05, 1e+01, 1.06 
		break;
	case MIX: 
		fslider1_ = (float*)data; // , 0.0, -1.0, 1.0, 0.1 
		break;
	case WET: 
		fslider2_ = (float*)data; // , 1e+02, 0.0, 1e+02, 1.0 
		break;
	case WIDTH: 
		fslider4_ = (float*)data; // , 5.0, 0.0, 1e+01, 0.01 
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
   DEPTH, 
   FEEDBACK, 
   FREQ, 
   MIX, 
   WET, 
   WIDTH, 
} PortIndex;
*/

} // end namespace gx_flanger
