// generated from file '../src/LV2/faust/lowpass_down.dsp' by dsp2cc:
// Code generated with Faust 0.9.58 (http://faust.grame.fr)


namespace lowpass_down {

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
	double 	fConst7;
	double 	fConst8;
	double 	fConst9;
	double 	fVec0[2];
	double 	fConst10;
	double 	fRec5[2];
	double 	fRec4[3];
	double 	fConst11;
	double 	fRec7[2];
	double 	fRec6[3];
	double 	fConst12;
	double 	fRec0[2];
	int 	iRec1[2];
	double 	fRec2[2];
	FAUSTFLOAT 	fbargraph0;
	FAUSTFLOAT	*fbargraph0_;
	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(uint32_t samplingFreq);
	void compute(int count, float *input0, float *output0);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(uint32_t samplingFreq, PluginLV2*);
	static void compute_static(int count, float *input0, float *output0, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginLV2() {
	version = PLUGINLV2_VERSION;
	id = "lowpass_down";
	name = "?lowpass_down";
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
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<3; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) iRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
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
	fConst2 = tan((1099.5574287564275 / double(iConst0)));
	fConst3 = (1.0 / faustpower<2>(fConst2));
	fConst4 = (2 * (1 - fConst3));
	fConst5 = (1.0 / fConst2);
	fConst6 = (1 + ((fConst5 - 1.0000000000000004) / fConst2));
	fConst7 = (1.0 / (1 + ((1.0000000000000004 + fConst5) / fConst2)));
	fConst8 = (1 + fConst5);
	fConst9 = (0 - ((1 - fConst5) / fConst8));
	fConst10 = (0.5 / fConst8);
	fConst11 = (0 - fConst5);
	fConst12 = (2 * (0 - fConst3));
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, float *input0, float *output0)
{
#define fbargraph0 (*fbargraph0_)
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fVec0[0] = fTemp0;
		fRec5[0] = ((fConst10 * (fVec0[0] + fVec0[1])) + (fConst9 * fRec5[1]));
		fRec4[0] = (fRec5[0] - (fConst7 * ((fConst6 * fRec4[2]) + (fConst4 * fRec4[1]))));
		fRec7[0] = ((fConst10 * ((fConst11 * fVec0[1]) + (fConst5 * fVec0[0]))) + (fConst9 * fRec7[1]));
		fRec6[0] = (fRec7[0] - (fConst7 * ((fConst6 * fRec6[2]) + (fConst4 * fRec6[1]))));
		double fTemp1 = (fConst7 * ((((fConst3 * fRec6[0]) + (fConst12 * fRec6[1])) + (fConst3 * fRec6[2])) + (1.9952623149688795 * (fRec4[2] + (fRec4[0] + (2 * fRec4[1]))))));
		double 	fRec3 = max(fConst1, fabs(fTemp1));
		int iTemp2 = int((iRec1[1] < 4096));
		fRec0[0] = ((iTemp2)?max(fRec0[1], fRec3):fRec3);
		iRec1[0] = ((iTemp2)?(1 + iRec1[1]):1);
		fRec2[0] = ((iTemp2)?fRec2[1]:fRec0[1]);
		fbargraph0 = fRec2[0];
		output0[i] = (FAUSTFLOAT)fTemp1;
		// post processing
		fRec2[1] = fRec2[0];
		iRec1[1] = iRec1[0];
		fRec0[1] = fRec0[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec7[1] = fRec7[0];
		fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fVec0[1] = fVec0[0];
	}
#undef fbargraph0
}

void __rt_func Dsp::compute_static(int count, float *input0, float *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case V1: 
		fbargraph0_ = (float*)data; // , -70.0, -70.0, 4.0, 0.00001 
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
   V1, 
} PortIndex;
*/

} // end namespace lowpass_down
