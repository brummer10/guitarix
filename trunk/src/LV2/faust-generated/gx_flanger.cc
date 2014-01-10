// generated from file '../src/LV2/faust/gx_flanger.dsp' by dsp2cc:
// Code generated with Faust 0.9.58 (http://faust.grame.fr)


namespace gx_flanger {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	int 	IOTA;
	double 	fVec0[1024];
	int 	iVec1[2];
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	int 	iConst0;
	double 	fConst1;
	double 	fRec1[2];
	double 	fRec2[2];
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT	*fslider4_;
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT	*fslider5_;
	double 	fConst2;
	double 	fVec2[1024];
	double 	fRec0[2];
	double 	fVec3[2048];
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
	for (int i=0; i<1024; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) iVec1[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<1024; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2048; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	IOTA = 0;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (6.283185307179586 / double(iConst0));
	fConst2 = (0.5 * iConst0);
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
	double 	fSlow0 = fslider0;
	double 	fSlow1 = fslider1;
	double 	fSlow2 = (0.01 * (fSlow1 * min((double)1, (1 + fSlow0))));
	double 	fSlow3 = (2 - fSlow2);
	double 	fSlow4 = (0.3333333333333333 * ((2 + fabs(fSlow0)) * fslider2));
	double 	fSlow5 = (fConst1 * fslider3);
	double 	fSlow6 = sin(fSlow5);
	double 	fSlow7 = cos(fSlow5);
	double 	fSlow8 = (0 - fSlow6);
	double 	fSlow9 = (0.0005 * fslider4);
	double 	fSlow10 = (0.001 * fslider5);
	double 	fSlow11 = (0.01 * (min((double)1, (1 - fSlow0)) * fSlow1));
	double 	fSlow12 = (2 - fSlow11);
	double 	fSlow13 = (0 - fSlow4);
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fVec0[IOTA&1023] = fTemp0;
		iVec1[0] = 1;
		fRec1[0] = ((fSlow7 * fRec1[1]) + (fSlow6 * fRec2[1]));
		fRec2[0] = ((1 + ((fSlow8 * fRec1[1]) + (fSlow7 * fRec2[1]))) - iVec1[1]);
		double fTemp1 = (fSlow10 + (fSlow9 * (1 + fRec1[0])));
		double fTemp2 = (fConst2 * fTemp1);
		int iTemp3 = int(fTemp2);
		int iTemp4 = int((iTemp3 & 1023));
		int iTemp5 = (1 + iTemp3);
		double fTemp6 = (iTemp5 - fTemp2);
		int iTemp7 = int((int(iTemp5) & 1023));
		double fTemp8 = (fTemp2 - iTemp3);
		double fTemp9 = (((fTemp8 * fVec0[(IOTA-iTemp7)&1023]) + (fTemp6 * fVec0[(IOTA-iTemp4)&1023])) + (fSlow4 * fRec0[1]));
		fVec2[IOTA&1023] = fTemp9;
		fRec0[0] = ((fTemp8 * fVec2[(IOTA-iTemp7)&1023]) + (fTemp6 * fVec2[(IOTA-iTemp4)&1023]));
		double fTemp10 = ((fSlow2 * fRec0[0]) + (fSlow3 * fVec0[IOTA&1023]));
		double fTemp11 = (fTemp10 + (fSlow13 * fRec3[1]));
		fVec3[IOTA&2047] = fTemp11;
		double fTemp12 = (iConst0 * fTemp1);
		int iTemp13 = int(fTemp12);
		int iTemp14 = (1 + iTemp13);
		fRec3[0] = (((fTemp12 - iTemp13) * fVec3[(IOTA-int((int(iTemp14) & 2047)))&2047]) + ((iTemp14 - fTemp12) * fVec3[(IOTA-int((iTemp13 & 2047)))&2047]));
		output0[i] = (FAUSTFLOAT)(0.25 * ((fSlow11 * fRec3[0]) + (fSlow12 * fTemp10)));
		// post processing
		fRec3[1] = fRec3[0];
		fRec0[1] = fRec0[0];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
		iVec1[1] = iVec1[0];
		IOTA = IOTA+1;
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
		fslider2_ = (float*)data; // , -0.707, -0.99, 0.99, 0.01 
		break;
	case FREQ: 
		fslider3_ = (float*)data; // , 0.2, 0.05, 1e+01, 1.06 
		break;
	case MIX: 
		fslider0_ = (float*)data; // , 0.0, -1.0, 1.0, 0.1 
		break;
	case WET: 
		fslider1_ = (float*)data; // , 1e+02, 0.0, 1e+02, 1.0 
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
