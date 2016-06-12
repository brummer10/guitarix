// generated from file '../src/LV2/faust/duck_delay.dsp' by dsp2cc:
// Code generated with Faust 0.9.73 (http://faust.grame.fr)


namespace duck_delay {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	int 	iConst0;
	double 	fConst1;
	double 	fRec2[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec1[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fConst2;
	double 	fConst3;
	double 	fRec0[2];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	int 	IOTA;
	double 	fVec0[524288];
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT	*fslider4_;
	double 	fRec4[2];
	double 	fConst4;
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
	id = "duckDelay";
	name = N_("Duck Delay");
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
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<524288; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
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
	fConst1 = (1.0 / double(iConst0));
	fConst2 = exp((0 - (1e+01 / double(iConst0))));
	fConst3 = (1.0 - fConst2);
	IOTA = 0;
	fConst4 = (0.001 * iConst0);
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
	double 	fSlow0 = exp((0 - (fConst1 / double(fslider0))));
	double 	fSlow1 = (1.0 - fSlow0);
	double 	fSlow2 = exp((0 - (fConst1 / double(fslider1))));
	double 	fSlow3 = (1.0 - fSlow2);
	double 	fSlow4 = pow(10,(0.05 * double(fslider2)));
	double 	fSlow5 = double(fslider3);
	double 	fSlow6 = (fConst3 * double(fslider4));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		double fTemp1 = fabs(fTemp0);
		fRec2[0] = max(fTemp1, ((fSlow0 * fRec2[1]) + (fSlow1 * fTemp1)));
		fRec1[0] = ((fSlow2 * fRec1[1]) + (fSlow3 * fRec2[0]));
		fRec0[0] = ((fConst2 * fRec0[1]) + (fConst3 * (1 - ((fSlow4 * fRec1[0]) > 1))));
		double fTemp2 = (fTemp0 + (fSlow5 * fRec3[1]));
		fVec0[IOTA&524287] = fTemp2;
		fRec4[0] = (fSlow6 + (fConst2 * fRec4[1]));
		double fTemp3 = (fConst4 * fRec4[0]);
		int iTemp4 = int(fTemp3);
		int iTemp5 = (1 + iTemp4);
		fRec3[0] = ((fVec0[(IOTA-int((iTemp4 & 393215)))&524287] * (iTemp5 - fTemp3)) + ((fTemp3 - iTemp4) * fVec0[(IOTA-int((int(iTemp5) & 393215)))&524287]));
		output0[i] = (FAUSTFLOAT)(fTemp0 + (fRec3[0] * fRec0[0]));
		// post processing
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		IOTA = IOTA+1;
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
	}
#undef fslider0
#undef fslider1
#undef fslider2
#undef fslider3
#undef fslider4
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case AMOUNT: 
		fslider2_ = (float*)data; // , 0.5, 0.0, 56.0, 0.05 
		break;
	case ATTACK: 
		fslider1_ = (float*)data; // , 0.1, 0.05, 0.5, 0.05 
		break;
	case FEEDBACK: 
		fslider3_ = (float*)data; // , 0.0, 0.0, 1.0, 0.05 
		break;
	case RELESE: 
		fslider0_ = (float*)data; // , 0.1, 0.05, 2.0, 0.05 
		break;
	case TIME: 
		fslider4_ = (float*)data; // , 5e+02, 1.0, 2e+03, 1.0 
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
   AMOUNT, 
   ATTACK, 
   FEEDBACK, 
   RELESE, 
   TIME, 
} PortIndex;
*/

} // end namespace duck_delay
