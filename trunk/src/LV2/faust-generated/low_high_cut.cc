// generated from file '../src/LV2/faust/low_high_cut.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)


namespace low_high_cut {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	int 	iVec0[2];
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
	double 	fRec5[2];
	double 	fVec1[2];
	double 	fConst11;
	double 	fRec4[2];
	double 	fRec3[2];
	double 	fRec2[3];
	double 	fRec1[3];
	double 	fVec2[2];
	double 	fConst12;
	double 	fConst13;
	double 	fConst14;
	double 	fConst15;
	double 	fConst16;
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
	id = "low_highcut";
	name = N_("low high cut");
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
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<3; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
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
	fConst1 = tan((3138.4510609362032 / double(iConst0)));
	fConst2 = (2 * (1 - (1.0 / faustpower<2>(fConst1))));
	fConst3 = (1.0 / fConst1);
	fConst4 = (1 + ((fConst3 - 0.7653668647301795) / fConst1));
	fConst5 = (1 + ((0.7653668647301795 + fConst3) / fConst1));
	fConst6 = (1.0 / fConst5);
	fConst7 = (1 + ((fConst3 - 1.8477590650225735) / fConst1));
	fConst8 = (1.0 / (1 + ((fConst3 + 1.8477590650225735) / fConst1)));
	fConst9 = (94.24777960769379 / double(iConst0));
	fConst10 = (1 - fConst9);
	fConst11 = (1.0 / (1 + fConst9));
	fConst12 = (1.0 / tan((314.1592653589793 / double(iConst0))));
	fConst13 = (0 - fConst12);
	fConst14 = (1 + fConst12);
	fConst15 = (1.0 / (fConst14 * fConst5));
	fConst16 = (0 - ((1 - fConst12) / fConst14));
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		fRec5[0] = ((1e-20 * (1 - iVec0[1])) - fRec5[1]);
		double fTemp0 = ((double)input0[i] + fRec5[0]);
		fVec1[0] = fTemp0;
		fRec4[0] = (fConst11 * ((fVec1[0] - fVec1[1]) + (fConst10 * fRec4[1])));
		fRec3[0] = (fConst11 * ((fRec4[0] - fRec4[1]) + (fConst10 * fRec3[1])));
		fRec2[0] = (fRec3[0] - (fConst8 * ((fConst7 * fRec2[2]) + (fConst2 * fRec2[1]))));
		fRec1[0] = ((fConst8 * (fRec2[2] + (fRec2[0] + (2 * fRec2[1])))) - (fConst6 * ((fConst4 * fRec1[2]) + (fConst2 * fRec1[1]))));
		double fTemp1 = (fRec1[2] + (fRec1[0] + (2 * fRec1[1])));
		fVec2[0] = fTemp1;
		fRec0[0] = ((fConst16 * fRec0[1]) + (fConst15 * ((fConst12 * fVec2[0]) + (fConst13 * fVec2[1]))));
		output0[i] = (FAUSTFLOAT)fRec0[0];
		// post processing
		fRec0[1] = fRec0[0];
		fVec2[1] = fVec2[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fVec1[1] = fVec1[0];
		fRec5[1] = fRec5[0];
		iVec0[1] = iVec0[0];
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

} // end namespace low_high_cut
