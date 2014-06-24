// generated from file './faust/switched_tremolo.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)


namespace switched_tremolo {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	class SIG0 {
	  private:
		int 	fSamplingFreq;
		int 	iRec0[2];
	  public:
		int getNumInputs() 	{ return 0; }
		int getNumOutputs() 	{ return 1; }
		void init(int samplingFreq) {
			fSamplingFreq = samplingFreq;
			for (int i=0; i<2; i++) iRec0[i] = 0;
		}
		void fill (int count, double output[]) {
			for (int i=0; i<count; i++) {
				iRec0[0] = (1 + iRec0[1]);
				output[i] = sin((9.587379924285257e-05 * double((iRec0[0] - 1))));
				// post processing
				iRec0[1] = iRec0[0];
			}
		}
	};
			static double 	ftbl0[65536];
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fRec1[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec3[2];
	double 	fConst3;
	double 	fConst4;
	double 	fRec2[2];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fRec4[2];
	double 	fRec5[2];
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT	*fslider4_;
	double 	fRec6[2];
	double 	fRec7[2];
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT	*fslider5_;
	double 	fRec8[2];
	double 	fRec9[2];
	FAUSTFLOAT 	fslider6;
	FAUSTFLOAT	*fslider6_;
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


double Dsp::ftbl0[65536];

Dsp::Dsp()
	: PluginLV2() {
	version = PLUGINLV2_VERSION;
	id = "switched_tremolo";
	name = "?switched_tremolo";
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
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	SIG0 sig0;
	sig0.init(samplingFreq);
	sig0.fill(65536,ftbl0);
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = double(iConst0);
	fConst2 = (1.0 / fConst1);
	fConst3 = exp((0 - (2e+01 / double(iConst0))));
	fConst4 = (1.0 - fConst3);
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
#define fslider6 (*fslider6_)
	double 	fSlow0 = (fConst2 * double(fslider0));
	double 	fSlow1 = double(fslider1);
	double 	fSlow2 = (double(4) / fSlow1);
	double 	fSlow3 = double(fslider2);
	double 	fSlow4 = (fConst1 / fSlow3);
	double 	fSlow5 = (fConst2 * fSlow3);
	double 	fSlow6 = (double(3) / fSlow1);
	double 	fSlow7 = (fConst2 * double(fslider3));
	double 	fSlow8 = (double(2) / fSlow1);
	double 	fSlow9 = (fConst2 * double(fslider4));
	double 	fSlow10 = (1.0 / fSlow1);
	double 	fSlow11 = (fConst2 * double(fslider5));
	double 	fSlow12 = double(fslider6);
	for (int i=0; i<count; i++) {
		double fTemp0 = (fRec1[1] + fSlow0);
		fRec1[0] = (fTemp0 - floor(fTemp0));
		fRec3[0] = fmod((1.0 + fRec3[1]),fSlow4);
		double fTemp1 = (fSlow5 * fRec3[0]);
		fRec2[0] = ((fConst3 * fRec2[1]) + (fConst4 * ((fTemp1 > fSlow6) * (fTemp1 <= fSlow2))));
		double fTemp2 = (fRec4[1] + fSlow7);
		fRec4[0] = (fTemp2 - floor(fTemp2));
		fRec5[0] = ((fConst4 * ((fTemp1 > fSlow8) * (fTemp1 <= fSlow6))) + (fConst3 * fRec5[1]));
		double fTemp3 = (fRec6[1] + fSlow9);
		fRec6[0] = (fTemp3 - floor(fTemp3));
		fRec7[0] = ((fConst3 * fRec7[1]) + (fConst4 * ((fTemp1 > fSlow10) * (fTemp1 <= fSlow8))));
		double fTemp4 = (fRec8[1] + fSlow11);
		fRec8[0] = (fTemp4 - floor(fTemp4));
		fRec9[0] = ((fConst3 * fRec9[1]) + (fConst4 * ((fTemp1 > 0) * (fTemp1 <= fSlow10))));
		output0[i] = (FAUSTFLOAT)((double)input0[i] * (1 + (fSlow12 * (((((fRec9[0] * ftbl0[int((65536.0 * fRec8[0]))]) + (fRec7[0] * ftbl0[int((65536.0 * fRec6[0]))])) + (fRec5[0] * ftbl0[int((65536.0 * fRec4[0]))])) + (fRec2[0] * ftbl0[int((65536.0 * fRec1[0]))])) - 1))));
		// post processing
		fRec9[1] = fRec9[0];
		fRec8[1] = fRec8[0];
		fRec7[1] = fRec7[0];
		fRec6[1] = fRec6[0];
		fRec5[1] = fRec5[0];
		fRec4[1] = fRec4[0];
		fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fRec1[1] = fRec1[0];
	}
#undef fslider0
#undef fslider1
#undef fslider2
#undef fslider3
#undef fslider4
#undef fslider5
#undef fslider6
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
		fslider6_ = (float*)data; // , 0.5, 0.0, 1.0, 0.05 
		break;
	case FREQ0: 
		fslider5_ = (float*)data; // , 1.0, 0.25, 15.0, 0.5 
		break;
	case FREQ1: 
		fslider4_ = (float*)data; // , 1.0, 0.25, 15.0, 0.5 
		break;
	case FREQ2: 
		fslider3_ = (float*)data; // , 1.0, 0.25, 15.0, 0.5 
		break;
	case FREQ3: 
		fslider0_ = (float*)data; // , 1.0, 0.25, 15.0, 0.5 
		break;
	case STEPS: 
		fslider1_ = (float*)data; // , 4.0, 1.0, 4.0, 1.0 
		break;
	case SWITCHFREQ: 
		fslider2_ = (float*)data; // , 1.0, 0.25, 5.0, 0.25 
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
   FREQ0, 
   FREQ1, 
   FREQ2, 
   FREQ3, 
   STEPS, 
   SWITCHFREQ, 
} PortIndex;
*/

} // end namespace switched_tremolo
