// generated from file '../src/LV2/faust/tremolo.dsp' by dsp2cc:
// Code generated with Faust 0.9.58 (http://faust.grame.fr)


namespace tremolo {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	int 	iVec0[2];
	int 	iConst0;
	double 	fConst1;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fConst2;
	int 	iRec2[2];
	int 	iRec1[2];
	double 	fConst3;
	double 	fRec5[2];
	double 	fRec4[2];
	double 	fRec3[2];
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT	*fcheckbox0_;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec0[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
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
	id = "tremolo";
	name = N_("Tremolo");
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
	for (int i=0; i<2; i++) iRec2[i] = 0;
	for (int i=0; i<2; i++) iRec1[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
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
	fConst1 = (1.0 / double(iConst0));
	fConst2 = (0.5 * iConst0);
	fConst3 = (6.283185307179586 / double(iConst0));
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fslider0 (*fslider0_)
#define fcheckbox0 (*fcheckbox0_)
#define fslider1 (*fslider1_)
#define fslider2 (*fslider2_)
	double 	fSlow0 = fslider0;
	int 	iSlow1 = int((fConst2 / double(fSlow0)));
	double 	fSlow2 = (1.0 / double(iSlow1));
	double 	fSlow3 = (fConst3 * fSlow0);
	int 	iSlow4 = int(fcheckbox0);
	double 	fSlow5 = fslider1;
	double 	fSlow6 = fslider2;
	double 	fSlow7 = (27.0 * fSlow6);
	double 	fSlow8 = (1 - (0.01 * fSlow6));
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		double fTemp0 = (fRec0[1] * (1 - (fConst1 / (fConst1 + (0.06 * exp((0 - (2.4849066497880004 * fRec0[1]))))))));
		iRec2[0] = ((int((iRec2[1] > 0)))?((2 * (iRec1[1] < iSlow1)) - 1):(1 - (2 * (iRec1[1] > 0))));
		iRec1[0] = (iRec2[0] + iRec1[1]);
		fRec5[0] = ((fSlow3 * (0 - fRec3[1])) + fRec5[1]);
		fRec4[0] = ((1 + ((fSlow3 * fRec5[0]) + fRec4[1])) - iVec0[1]);
		fRec3[0] = fRec4[0];
		fRec0[0] = (fTemp0 + (fConst1 * (pow((1 + (fSlow5 * (((iSlow4)?max((double)0, (0.5 * (1 + fRec3[0]))):(fSlow2 * iRec1[0])) - 1))),1.9) / (fConst1 + (0.06 * exp((0 - (2.4849066497880004 * fTemp0))))))));
		output0[i] = (FAUSTFLOAT)((double)input0[i] * (fSlow8 + (fSlow7 / (2700 + exp((13.815510557964274 / log((2.718281828459045 + (8.551967507929417 * fRec0[0])))))))));
		// post processing
		fRec0[1] = fRec0[0];
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		iRec1[1] = iRec1[0];
		iRec2[1] = iRec2[0];
		iVec0[1] = iVec0[0];
	}
#undef fslider0
#undef fcheckbox0
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
	// static const value_pair fcheckbox0_values[] = {{"triangle"},{"sine"},{0}};
	case SINE: 
		fcheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case DEPTH: 
		fslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case FREQ: 
		fslider0_ = (float*)data; // , 5.0, 0.1, 5e+01, 0.1 
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
   SINE, 
   DEPTH, 
   FREQ, 
   WET_DRY, 
} PortIndex;
*/

} // end namespace tremolo
