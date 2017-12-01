// generated from file '../src/LV2/faust/hfb.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)


namespace hfb {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec0[2];
	double 	fConst0;
	double 	fConst1;
	double 	fConst2;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec1[2];
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	double 	fConst9;
	double 	fConst10;
	double 	fRec2[3];

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
	id = "hfb";
	name = N_("HF Brightener");
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
	for (int i=0; i<3; i++) fRec2[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = double(min(1.92e+05, max(1.0, (double)fSamplingFreq)));
	fConst1 = (2.36551040815034e-10 * fConst0);
	fConst2 = (1.32257544516629e-08 + fConst1);
	fConst3 = (1.17023754306854e-09 * fConst0);
	fConst4 = (0 - (6.50608604711861e-08 + fConst3));
	fConst5 = (1.18275520407517e-09 * fConst0);
	fConst6 = (6.61287722583147e-08 + fConst5);
	fConst7 = (fConst1 - 1.32257544516629e-08);
	fConst8 = (6.50608604711861e-08 - fConst3);
	fConst9 = (fConst5 - 6.61287722583147e-08);
	fConst10 = faustpower<2>(fConst0);
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
	double 	fSlow0 = (0.007000000000000006 * (1 - double(fslider0)));
	double 	fSlow1 = (0.007000000000000006 * double(fslider1));
	for (int i=0; i<count; i++) {
		fRec0[0] = (fSlow0 + (0.993 * fRec0[1]));
		fRec1[0] = (fSlow1 + (0.993 * fRec1[1]));
		double fTemp0 = (4.40858481722098e-05 + (fConst0 * (7.88503469383447e-07 + ((fRec1[0] * (fConst6 + (fConst4 * fRec1[0]))) + (fConst2 * fRec0[0])))));
		double fTemp1 = (fConst0 * ((fRec1[0] * ((5.12666523663255e-23 * fRec1[0]) - 1.59041010538546e-09)) - (3.18082021077091e-10 * fRec0[0])));
		fRec2[0] = ((double)input0[i] - (((fRec2[1] * (8.81716963444196e-05 + (fConst10 * ((fRec1[0] * ((2.34047508613708e-09 * fRec1[0]) - 2.36551040815034e-09)) - (4.73102081630068e-10 * fRec0[0]))))) + (fRec2[2] * (4.40858481722098e-05 + (fConst0 * (((fRec1[0] * (fConst9 + (fConst8 * fRec1[0]))) + (fConst7 * fRec0[0])) - 7.88503469383447e-07))))) / fTemp0));
		output0[i] = (FAUSTFLOAT)(fConst0 * (((fConst0 * (fRec2[1] * ((6.36164042154183e-10 * fRec0[0]) + (fRec1[0] * (3.18082021077092e-09 - (1.02533304732651e-22 * fRec1[0])))))) + ((fRec2[0] * (fTemp1 - 1.06027340359031e-06)) + (fRec2[2] * (1.06027340359031e-06 + fTemp1)))) / fTemp0));
		// post processing
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
	}
#undef fslider0
#undef fslider1
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case INTENSITY: 
		fslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case VOLUME: 
		fslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
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
   INTENSITY, 
   VOLUME, 
} PortIndex;
*/

} // end namespace hfb
