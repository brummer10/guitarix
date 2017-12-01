// generated from file '../src/LV2/faust/moog.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)


namespace moog {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	int 	iVec0[2];
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec3[2];
	double 	fConst0;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec6[2];
	double 	fRec5[2];
	double 	fRec4[2];
	double 	fRec2[2];
	double 	fRec1[2];
	double 	fRec0[2];
	double 	fRec11[2];
	double 	fRec10[2];
	double 	fRec9[2];
	double 	fRec8[2];
	double 	fRec7[2];

	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(uint32_t samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(uint32_t samplingFreq, PluginLV2*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginLV2() {
	version = PLUGINLV2_VERSION;
	id = "moog";
	name = N_("Moog Filter");
	mono_audio = 0;
	stereo_audio = compute_static;
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
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = (6.283185307179586 / min(1.92e+05, max(1.0, (double)fSamplingFreq)));
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
	double 	fSlow0 = (0.0010000000000000009 * double(fslider0));
	double 	fSlow1 = (0 - double(fslider1));
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		fRec3[0] = (fSlow0 + (0.999 * fRec3[1]));
		double fTemp0 = (fConst0 * fRec3[0]);
		double fTemp1 = (1.0 - fTemp0);
		fRec6[0] = ((1e-20 * (1 - iVec0[1])) - fRec6[1]);
		fRec5[0] = ((fTemp1 * fRec5[1]) + (fRec6[0] + ((double)input0[i] + (fSlow1 * fRec0[1]))));
		fRec4[0] = (fRec5[0] + (fTemp1 * fRec4[1]));
		fRec2[0] = (fRec4[0] + (fTemp1 * fRec2[1]));
		fRec1[0] = ((fRec1[1] * fTemp1) + fRec2[0]);
		double fTemp2 = faustpower<4>(fTemp0);
		fRec0[0] = (fTemp2 * fRec1[0]);
		output0[i] = (FAUSTFLOAT)fRec0[0];
		fRec11[0] = ((fTemp1 * fRec11[1]) + ((fSlow1 * fRec7[1]) + ((double)input1[i] + fRec6[0])));
		fRec10[0] = (fRec11[0] + (fTemp1 * fRec10[1]));
		fRec9[0] = (fRec10[0] + (fTemp1 * fRec9[1]));
		fRec8[0] = (fRec9[0] + (fTemp1 * fRec8[1]));
		fRec7[0] = (fTemp2 * fRec8[0]);
		output1[i] = (FAUSTFLOAT)fRec7[0];
		// post processing
		fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
		fRec9[1] = fRec9[0];
		fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		fRec3[1] = fRec3[0];
		iVec0[1] = iVec0[0];
	}
#undef fslider0
#undef fslider1
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case Q: 
		fslider1_ = (float*)data; // , 1.0, 0.0, 4.0, 0.1 
		break;
	case FR: 
		fslider0_ = (float*)data; // , 3e+03, 4.4e+02, 6e+03, 1e+01 
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
   Q, 
   FR, 
} PortIndex;
*/

} // end namespace moog
