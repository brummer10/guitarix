// generated from file '../src/LV2/faust/cstb.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)


namespace cstb {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	double 	fConst0;
	double 	fConst1;
	double 	fConst2;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec0[2];
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec1[2];
	double 	fConst7;
	double 	fConst8;
	double 	fConst9;
	double 	fConst10;
	double 	fConst11;
	double 	fConst12;
	double 	fConst13;
	double 	fConst14;
	double 	fConst15;
	double 	fConst16;
	double 	fConst17;
	double 	fConst18;
	double 	fConst19;
	double 	fConst20;
	double 	fConst21;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec2[5];
	double 	fConst22;
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
	id = "cstb";
	name = N_("Colorsound Tone Blender");
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
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<5; i++) fRec2[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = double(min(192000, max(1, fSamplingFreq)));
	fConst1 = (7.72761004436121e-17 * fConst0);
	fConst2 = (1.90124164300881e-12 + (fConst0 * (4.0705776699833e-14 + fConst1)));
	fConst3 = (7.13788307669893e-19 * fConst0);
	fConst4 = ((fConst0 * ((fConst0 * (0 - (3.81274375281155e-16 + fConst3))) - 1.78337596435683e-14)) - 3.57720562427687e-14);
	fConst5 = (7.26395344169953e-19 * fConst0);
	fConst6 = (3.58457860428614e-14 + (fConst0 * (1.78716714442828e-14 + (fConst0 * (3.82634300978431e-16 + fConst5)))));
	fConst7 = ((fConst0 * (4.0705776699833e-14 - fConst1)) - 1.90124164300881e-12);
	fConst8 = (3.57720562427687e-14 + (fConst0 * ((fConst0 * (3.81274375281155e-16 - fConst3)) - 1.78337596435683e-14)));
	fConst9 = ((fConst0 * (1.78716714442828e-14 + (fConst0 * (fConst5 - 3.82634300978431e-16)))) - 3.58457860428614e-14);
	fConst10 = (2.85515323067957e-18 * fConst0);
	fConst11 = faustpower<2>(fConst0);
	fConst12 = (7.15441124855374e-14 + (fConst11 * (fConst10 - 7.6254875056231e-16)));
	fConst13 = (2.90558137667981e-18 * fConst0);
	fConst14 = ((fConst11 * (7.65268601956861e-16 - fConst13)) - 7.16915720857228e-14);
	fConst15 = (1.54552200887224e-16 * fConst11);
	fConst16 = (fConst15 - 3.80248328601762e-12);
	fConst17 = (3.56675192871367e-14 - (4.28272984601936e-18 * fConst11));
	fConst18 = ((4.35837206501972e-18 * fConst11) - 3.57433428885656e-14);
	fConst19 = (3.80248328601762e-12 - fConst15);
	fConst20 = ((fConst11 * (7.6254875056231e-16 + fConst10)) - 7.15441124855374e-14);
	fConst21 = (7.16915720857228e-14 + (fConst11 * (0 - (7.65268601956861e-16 + fConst13))));
	fConst22 = faustpower<3>(fConst0);
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
	double 	fSlow0 = (0.007000000000000006 * double(fslider0));
	double 	fSlow1 = (0.007000000000000006 * double(fslider1));
	double 	fSlow2 = (0.01 * double(fslider2));
	double 	fSlow3 = (1 - fSlow2);
	for (int i=0; i<count; i++) {
		fRec0[0] = ((0.993 * fRec0[1]) + fSlow0);
		double fTemp0 = (3.81338149392143e-12 + (fConst0 * ((fRec0[0] * (fConst6 + (fConst4 * fRec0[0]))) + fConst2)));
		fRec1[0] = ((0.993 * fRec1[1]) + fSlow1);
		double fTemp1 = (fConst0 * (fRec0[0] * (((fRec0[0] * (2.34677954600673e-22 + (2.34677954600673e-19 * fRec1[0]))) - (2.35728909376724e-17 * fRec1[0])) - 2.35728909376724e-20)));
		double fTemp2 = (2.50775435507154e-15 * fRec1[0]);
		double fTemp3 = (double)input0[i];
		fRec2[0] = ((fSlow2 * fTemp3) - (((((fRec2[1] * (1.52535259756857e-11 + (fConst0 * ((fRec0[0] * (fConst21 + (fConst20 * fRec0[0]))) + fConst19)))) + (fRec2[2] * (2.28802889635286e-11 + (fConst11 * ((fRec0[0] * (fConst18 + (fConst17 * fRec0[0]))) - 8.14115533996661e-14))))) + (fRec2[3] * (1.52535259756857e-11 + (fConst0 * (fConst16 + (fRec0[0] * (fConst14 + (fConst12 * fRec0[0])))))))) + (fRec2[4] * (3.81338149392143e-12 + (fConst0 * ((fRec0[0] * (fConst9 + (fConst8 * fRec0[0]))) + fConst7))))) / fTemp0));
		double fTemp4 = (5.01550871014307e-15 * fRec1[0]);
		double fTemp5 = (fConst0 * (fRec0[0] * (9.42915637506898e-20 + ((9.42915637506898e-17 * fRec1[0]) + (fRec0[0] * ((0 - (9.38711818402692e-19 * fRec1[0])) - 9.38711818402692e-22))))));
		output0[i] = (FAUSTFLOAT)((fSlow3 * fTemp3) + (0.3 * min(0.7514, max(-0.4514, (fConst22 * ((((((fRec2[0] * ((fTemp1 - fTemp2) - 2.50775435507154e-18)) + (fRec2[1] * (5.01550871014307e-18 + (fTemp4 + fTemp5)))) + (fConst0 * ((fRec0[0] * fRec2[2]) * (((fRec0[0] * (1.40806772760404e-21 + (1.40806772760404e-18 * fRec1[0]))) - (1.41437345626035e-16 * fRec1[0])) - 1.41437345626035e-19)))) + (fRec2[3] * ((fTemp5 - fTemp4) - 5.01550871014307e-18))) + (fRec2[4] * (2.50775435507154e-18 + (fTemp2 + fTemp1)))) / fTemp0))))));
		// post processing
		for (int i=4; i>0; i--) fRec2[i] = fRec2[i-1];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
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
	case ATTACK: 
		fslider0_ = (float*)data; // , 0.5, 0.0, 0.95, 0.01 
		break;
	case LEVEL: 
		fslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
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
   ATTACK, 
   LEVEL, 
   WET_DRY, 
} PortIndex;
*/

} // end namespace cstb
