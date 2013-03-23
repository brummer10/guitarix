// generated from file '../src/LV2/faust/phaser_mono.dsp' by dsp2cc:
// Code generated with Faust 0.9.46 (http://faust.grame.fr)


namespace phaser_mono {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	int 	iVec0[2];
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	int 	iConst0;
	double 	fConst1;
	double 	fRec1[2];
	double 	fRec2[2];
	double 	fConst2;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fRec6[3];
	double 	fConst7;
	double 	fRec5[3];
	double 	fConst8;
	double 	fRec4[3];
	double 	fRec3[3];
	double 	fRec0[2];
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
	id = "phaser_mono";
	name = N_("Phaser Mono");
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
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<3; i++) fRec4[i] = 0;
	for (int i=0; i<3; i++) fRec3[i] = 0;
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
	fConst1 = (6.283185307179586 / iConst0);
	fConst2 = (16.0 / iConst0);
	fConst3 = (2.0 / iConst0);
	fConst4 = exp((0 - (3141.592653589793 / iConst0)));
	fConst5 = (0 - (2 * fConst4));
	fConst6 = faustpower<2>(fConst4);
	fConst7 = (4.0 / iConst0);
	fConst8 = (8.0 / iConst0);
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

inline void Dsp::compute(int count, float *input0, float *output0)
{
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
#define fslider2 (*fslider2_)
	double 	fSlow0 = (fConst1 * fslider0);
	double 	fSlow1 = sin(fSlow0);
	double 	fSlow2 = cos(fSlow0);
	double 	fSlow3 = (0 - fSlow1);
	double 	fSlow4 = fslider2;
	double 	fSlow5 = (0.01 * (fSlow4 * pow(10,(0.05 * fslider1))));
	double 	fSlow6 = (1 - (0.01 * fSlow4));
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		fRec1[0] = ((fSlow2 * fRec1[1]) + (fSlow1 * fRec2[1]));
		fRec2[0] = ((1 + ((fSlow3 * fRec1[1]) + (fSlow2 * fRec2[1]))) - iVec0[1]);
		double fTemp0 = (628.3185307179587 + (2199.1148575128555 * (1 - fRec1[0])));
		double fTemp1 = (double)input0[i];
		double fTemp2 = (fRec6[1] * cos((fConst3 * fTemp0)));
		fRec6[0] = (0 - (((fConst6 * fRec6[2]) + (fConst5 * fTemp2)) - ((fSlow5 * fTemp1) + (0.5 * fRec0[1]))));
		double fTemp3 = (fRec5[1] * cos((fConst7 * fTemp0)));
		fRec5[0] = ((fConst5 * (fTemp2 - fTemp3)) + (fRec6[2] + (fConst6 * (fRec6[0] - fRec5[2]))));
		double fTemp4 = (fRec4[1] * cos((fConst8 * fTemp0)));
		fRec4[0] = ((fConst5 * (fTemp3 - fTemp4)) + (fRec5[2] + (fConst6 * (fRec5[0] - fRec4[2]))));
		double fTemp5 = (fRec3[1] * cos((fConst2 * fTemp0)));
		fRec3[0] = ((fConst5 * (fTemp4 - fTemp5)) + (fRec4[2] + (fConst6 * (fRec4[0] - fRec3[2]))));
		fRec0[0] = ((fConst6 * fRec3[0]) + (fRec3[2] + (fConst5 * fTemp5)));
		output0[i] = (FAUSTFLOAT)((fSlow6 * fTemp1) - fRec0[0]);
		// post processing
		fRec0[1] = fRec0[0];
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
		fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
		iVec0[1] = iVec0[0];
	}
#undef fslider0
#undef fslider1
#undef fslider2
}

void Dsp::compute_static(int count, float *input0, float *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case WET_DRY: 
		fslider2_ = (float*)data; // , 1e+02, 0.0, 1e+02, 1.0 
		break;
	case LEVEL: 
		fslider1_ = (float*)data; // , 0.0, -6e+01, 1e+01, 0.1 
		break;
	case SPEED: 
		fslider0_ = (float*)data; // , 0.5, 0.0, 1e+01, 0.01 
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

} // end namespace phaser_mono
