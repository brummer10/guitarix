// generated from file '../src/LV2/faust/gx_flanger.dsp' by dsp2cc:
// Code generated with Faust 0.9.73 (http://faust.grame.fr)


namespace gx_flanger {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	int 	iVec0[2];
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	int 	iConst0;
	double 	fConst1;
	double 	fRec2[2];
	double 	fRec3[2];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT	*fslider4_;
	double 	fConst2;
	int 	IOTA;
	double 	fVec1[1024];
	double 	fVec2[1024];
	double 	fRec1[2];
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT	*fslider5_;
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
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<1024; i++) fVec1[i] = 0;
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
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (6.283185307179586 / double(iConst0));
	fConst2 = (0.5 * iConst0);
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
	double 	fSlow3 = (fConst1 * double(fslider2));
	double 	fSlow4 = cos(fSlow3);
	double 	fSlow5 = sin(fSlow3);
	double 	fSlow6 = (0 - fSlow5);
	double 	fSlow7 = (0.0005 * double(fslider3));
	double 	fSlow8 = (0.001 * double(fslider4));
	double 	fSlow9 = double(fslider5);
	double 	fSlow10 = (0.01 * (fSlow9 * min((double)1, (1 + fSlow0))));
	double 	fSlow11 = (2 - fSlow10);
	double 	fSlow12 = (0.01 * (min((double)1, (1 - fSlow0)) * fSlow9));
	double 	fSlow13 = (2 - fSlow12);
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		fRec2[0] = ((fSlow5 * fRec3[1]) + (fSlow4 * fRec2[1]));
		fRec3[0] = ((1 + ((fSlow4 * fRec3[1]) + (fSlow6 * fRec2[1]))) - iVec0[1]);
		double fTemp0 = (fSlow8 + (fSlow7 * (1 + fRec2[0])));
		double fTemp1 = (fConst2 * fTemp0);
		int iTemp2 = int(fTemp1);
		int iTemp3 = (1 + iTemp2);
		double fTemp4 = (iTemp3 - fTemp1);
		double fTemp5 = (double)input0[i];
		fVec1[IOTA&1023] = fTemp5;
		int iTemp6 = int((iTemp2 & 1023));
		int iTemp7 = int((int(iTemp3) & 1023));
		double fTemp8 = (fTemp1 - iTemp2);
		double fTemp9 = ((fTemp8 * fVec1[(IOTA-iTemp7)&1023]) + ((fSlow1 * fRec1[1]) + (fVec1[(IOTA-iTemp6)&1023] * fTemp4)));
		fVec2[IOTA&1023] = fTemp9;
		fRec1[0] = ((fTemp4 * fVec2[(IOTA-iTemp6)&1023]) + (fTemp8 * fVec2[(IOTA-iTemp7)&1023]));
		double fTemp10 = ((fSlow11 * fVec1[IOTA&1023]) + (fSlow10 * fRec1[0]));
		double fTemp11 = (fTemp10 + (fSlow2 * fRec0[1]));
		fVec3[IOTA&2047] = fTemp11;
		double fTemp12 = (iConst0 * fTemp0);
		int iTemp13 = int(fTemp12);
		int iTemp14 = (1 + iTemp13);
		fRec0[0] = ((fVec3[(IOTA-int((iTemp13 & 2047)))&2047] * (iTemp14 - fTemp12)) + ((fTemp12 - iTemp13) * fVec3[(IOTA-int((int(iTemp14) & 2047)))&2047]));
		output0[i] = (FAUSTFLOAT)(0.25 * ((fSlow13 * fTemp10) + (fSlow12 * fRec0[0])));
		// post processing
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		IOTA = IOTA+1;
		fRec3[1] = fRec3[0];
		fRec2[1] = fRec2[0];
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
		fslider4_ = (float*)data; // , 0.5, 0.0, 5.0, 0.01 
		break;
	case FEEDBACK: 
		fslider0_ = (float*)data; // , -0.707, -0.99, 0.99, 0.01 
		break;
	case FREQ: 
		fslider2_ = (float*)data; // , 0.2, 0.05, 1e+01, 1.06 
		break;
	case MIX: 
		fslider1_ = (float*)data; // , 0.0, -1.0, 1.0, 0.1 
		break;
	case WET: 
		fslider5_ = (float*)data; // , 1e+02, 0.0, 1e+02, 1.0 
		break;
	case WIDTH: 
		fslider3_ = (float*)data; // , 5.0, 0.0, 1e+01, 0.01 
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
