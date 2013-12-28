// generated from file '../src/LV2/faust/lowpass_up.dsp' by dsp2cc:
// Code generated with Faust 0.9.58 (http://faust.grame.fr)


namespace lowpass_up {

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
	double 	fConst10;
	double 	fConst11;
	double 	fConst12;
	double 	fConst13;
	double 	fConst14;
	double 	fConst15;
	double 	fVec0[2];
	double 	fConst16;
	double 	fRec3[2];
	double 	fConst17;
	double 	fConst18;
	double 	fRec2[2];
	double 	fConst19;
	double 	fRec1[2];
	double 	fRec0[3];
	double 	fConst20;
	double 	fRec5[2];
	double 	fRec4[3];
	double 	fConst21;
	double 	fConst22;
	double 	fConst23;
	double 	fConst24;
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
	id = "lowpass_up";
	name = "?lowpass_up";
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
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<3; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<3; i++) fRec4[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = tan((1099.5574287564275 / double(iConst0)));
	fConst2 = (1.0 / faustpower<2>(fConst1));
	fConst3 = (2 * (1 - fConst2));
	fConst4 = (1.0 / fConst1);
	fConst5 = (1 + ((fConst4 - 1.0000000000000004) / fConst1));
	fConst6 = (1 + ((1.0000000000000004 + fConst4) / fConst1));
	fConst7 = (1.0 / fConst6);
	fConst8 = (1 + fConst4);
	fConst9 = (0 - ((1 - fConst4) / fConst8));
	fConst10 = (1.0 / tan((251.32741228718345 / double(iConst0))));
	fConst11 = (1 + fConst10);
	fConst12 = (0 - ((1 - fConst10) / fConst11));
	fConst13 = (1.0 / tan((17690.308232364125 / double(iConst0))));
	fConst14 = (1 + fConst13);
	fConst15 = (0 - ((1 - fConst13) / fConst14));
	fConst16 = (1.0 / fConst14);
	fConst17 = (0 - fConst10);
	fConst18 = (1.0 / fConst11);
	fConst19 = (1.0 / fConst8);
	fConst20 = (0 - fConst4);
	fConst21 = (2 * (0 - fConst2));
	fConst22 = (1.4 / fConst6);
	fConst23 = (4.199999999999999 / fConst6);
	fConst24 = (2.8 / fConst6);
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fVec0[0] = fTemp0;
		fRec3[0] = ((fConst16 * (fVec0[0] + fVec0[1])) + (fConst15 * fRec3[1]));
		fRec2[0] = ((fConst18 * ((fConst17 * fRec3[1]) + (fConst10 * fRec3[0]))) + (fConst12 * fRec2[1]));
		fRec1[0] = ((fConst19 * (fRec2[0] + fRec2[1])) + (fConst9 * fRec1[1]));
		fRec0[0] = (fRec1[0] - (fConst7 * ((fConst5 * fRec0[2]) + (fConst3 * fRec0[1]))));
		fRec5[0] = ((fConst19 * ((fConst20 * fRec2[1]) + (fConst4 * fRec2[0]))) + (fConst9 * fRec5[1]));
		fRec4[0] = (fRec5[0] - (fConst7 * ((fConst5 * fRec4[2]) + (fConst3 * fRec4[1]))));
		double fTemp1 = ((((fConst2 * fRec4[0]) + (fConst21 * fRec4[1])) + (fConst2 * fRec4[2])) + (0.5011872336272722 * (fRec0[2] + (fRec0[0] + (2 * fRec0[1])))));
		double fTemp2 = (fConst22 * fTemp1);
		output0[i] = (FAUSTFLOAT)max(-0.9, min(0.9, ((int((fabs(fTemp2) < 0.33)))?(fConst24 * fTemp1):copysign(fTemp2, (0.3333333333333333 * (3 - faustpower<2>((2 - (fConst23 * fTemp1)))))))));
		// post processing
		fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fVec0[1] = fVec0[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
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
} PortIndex;
*/

} // end namespace lowpass_up
