// generated from file '../src/LV2/faust/autowah.dsp' by dsp2cc:
// Code generated with Faust 0.9.58 (http://faust.grame.fr)


namespace autowah {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	int 	IOTA;
	int 	iVec0[1024];
	int 	iRec2[2];
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec1[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fRec3[2];
	double 	fRec4[2];
	double 	fRec0[3];
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
	id = "auto";
	name = N_("auto");
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
	for (int i=0; i<1024; i++) iVec0[i] = 0;
	for (int i=0; i<2; i++) iRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<3; i++) fRec0[i] = 0;
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
	fConst1 = (2827.4333882308138 / double(iConst0));
	fConst2 = (1413.7166941154069 / double(iConst0));
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
	double 	fSlow0 = (2.384185791015625e-10 * fslider0);
	double 	fSlow1 = fslider2;
	double 	fSlow2 = (0.01 * (fSlow1 * fslider1));
	double 	fSlow3 = (1 - (0.01 * fSlow1));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		int iTemp1 = abs(int((4194304 * fTemp0)));
		iVec0[IOTA&1023] = iTemp1;
		iRec2[0] = ((iVec0[IOTA&1023] + iRec2[1]) - iVec0[(IOTA-1000)&1023]);
		double fTemp2 = min((double)1, max((double)0, (fSlow0 * double(iRec2[0]))));
		fRec1[0] = ((0.0001000000000000001 * pow(4.0,fTemp2)) + (0.999 * fRec1[1]));
		double fTemp3 = pow(2.0,(2.3 * fTemp2));
		double fTemp4 = (1 - (fConst2 * (fTemp3 / pow(2.0,(1.0 + (2.0 * (1.0 - fTemp2)))))));
		fRec3[0] = ((0.0010000000000000009 * (0 - (2.0 * (fTemp4 * cos((fConst1 * fTemp3)))))) + (0.999 * fRec3[1]));
		fRec4[0] = ((0.0010000000000000009 * faustpower<2>(fTemp4)) + (0.999 * fRec4[1]));
		fRec0[0] = (0 - (((fRec4[0] * fRec0[2]) + (fRec3[0] * fRec0[1])) - (fSlow2 * (fTemp0 * fRec1[0]))));
		output0[i] = (FAUSTFLOAT)((fRec0[0] + (fSlow3 * fTemp0)) - fRec0[1]);
		// post processing
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		fRec1[1] = fRec1[0];
		iRec2[1] = iRec2[0];
		IOTA = IOTA+1;
	}
#undef fslider0
#undef fslider1
#undef fslider2
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case LEVEL: 
		fslider1_ = (float*)data; // , 0.1, 0.0, 1.0, 0.01 
		break;
	case WAH: 
		fslider0_ = (float*)data; // , 0.0, 0.0, 1.0, 0.01 
		break;
	case WET_DRY: 
		fslider2_ = (float*)data; // , 1e+02, 0.0, 1e+02, 1.0 
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
   LEVEL, 
   WAH, 
   WET_DRY, 
} PortIndex;
*/

} // end namespace autowah
