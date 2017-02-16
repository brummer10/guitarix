// generated from file '../src/LV2/faust/gxtubetremelo.dsp' by dsp2cc:
// Code generated with Faust 0.9.73 (http://faust.grame.fr)


namespace gxtubetremelo {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	int 	iVec0[2];
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec0[2];
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fConst6;
	int 	iRec4[2];
	int 	iRec3[2];
	double 	fConst7;
	double 	fRec7[2];
	double 	fRec6[2];
	double 	fRec5[2];
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT	*fcheckbox0_;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec2[2];
	double 	fConst8;
	double 	fConst9;
	double 	fConst10;
	double 	fRec8[2];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fRec9[2];
	double 	fConst11;
	double 	fRec1[2];
	double 	fConst12;
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
	id = "gxtubetremelo";
	name = N_("Tube Tremolo");
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
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) iRec4[i] = 0;
	for (int i=0; i<2; i++) iRec3[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = double(iConst0);
	fConst2 = (2.08237464507809e-05 * fConst1);
	fConst3 = (0.000460170362516827 + fConst2);
	fConst4 = ((0.000460170362516827 - fConst2) / fConst3);
	fConst5 = (1.0 / double(iConst0));
	fConst6 = (0.5 * iConst0);
	fConst7 = (6.283185307179586 / double(iConst0));
	fConst8 = (2.08239024527461e-05 * fConst1);
	fConst9 = (0.00045268226818868 + fConst8);
	fConst10 = ((0.00045268226818868 - fConst8) / fConst9);
	fConst11 = (2.7e+02 * (fConst1 / fConst9));
	fConst12 = (fConst1 / fConst3);
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
#define fcheckbox0 (*fcheckbox0_)
#define fslider2 (*fslider2_)
#define fslider3 (*fslider3_)
	double 	fSlow0 = (0.004073836948085289 * (exp((1 - double(fslider0))) - 1));
	double 	fSlow1 = double(fslider1);
	int 	iSlow2 = int((fConst6 / double(fSlow1)));
	double 	fSlow3 = (1.0 / double(iSlow2));
	double 	fSlow4 = (fConst7 * fSlow1);
	int 	iSlow5 = int(double(fcheckbox0));
	double 	fSlow6 = double(fslider2);
	double 	fSlow7 = (0.004073836948085289 * (exp(double(fslider3)) - 1));
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		fRec0[0] = ((0.993 * fRec0[1]) + fSlow0);
		double fTemp0 = (0.000257077328090757 * fRec0[0]);
		double fTemp1 = (fRec2[1] * (1 - (fConst5 / (fConst5 + (0.06 * exp((0 - (2.4849066497880004 * fRec2[1]))))))));
		iRec4[0] = ((int((iRec4[1] > 0)))?((2 * (iRec3[1] < iSlow2)) - 1):(1 - (2 * (iRec3[1] > 0))));
		iRec3[0] = (iRec4[0] + iRec3[1]);
		fRec7[0] = (fRec7[1] + (fSlow4 * (0 - fRec5[1])));
		fRec6[0] = ((1 + (fRec6[1] + (fSlow4 * fRec7[0]))) - iVec0[1]);
		fRec5[0] = fRec6[0];
		fRec2[0] = (fTemp1 + (fConst5 * (pow((1 + (fSlow6 * (((iSlow5)?max((double)0, (0.5 * (1 + fRec5[0]))):(fSlow3 * iRec3[0])) - 1))),1.9) / (fConst5 + (0.06 * exp((0 - (2.4849066497880004 * fTemp1))))))));
		fRec8[0] = ((double)input0[i] - (fConst10 * fRec8[1]));
		fRec9[0] = ((0.993 * fRec9[1]) + fSlow7);
		fRec1[0] = ((fConst11 * (((fRec8[0] * (0 - (0.000564641478707507 * fRec9[0]))) + (0.000564641478707507 * (fRec9[0] * fRec8[1]))) / (2700 + exp((13.815510557964274 / log((2.718281828459045 + (8.551967507929417 * fRec2[0])))))))) - (fConst4 * fRec1[1]));
		output0[i] = (FAUSTFLOAT)(fConst12 * ((fRec1[0] * (fTemp0 - 0.000257077328090757)) + (fRec1[1] * (0.000257077328090757 + (0 - fTemp0)))));
		// post processing
		fRec1[1] = fRec1[0];
		fRec9[1] = fRec9[0];
		fRec8[1] = fRec8[0];
		fRec2[1] = fRec2[0];
		fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		fRec7[1] = fRec7[0];
		iRec3[1] = iRec3[0];
		iRec4[1] = iRec4[0];
		fRec0[1] = fRec0[0];
		iVec0[1] = iVec0[0];
	}
#undef fslider0
#undef fslider1
#undef fcheckbox0
#undef fslider2
#undef fslider3
}
		
void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case DRIVE: 
		fslider3_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case GAIN: 
		fslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	// static const value_pair fcheckbox0_values[] = {{"triangle"},{"sine"},{0}};
	case SINEWAVE: 
		fcheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case DEPTH: 
		fslider2_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case SPEED: 
		fslider1_ = (float*)data; // , 5.0, 0.1, 14.0, 0.1 
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
   DRIVE, 
   GAIN, 
   SINEWAVE, 
   DEPTH, 
   SPEED, 
} PortIndex;
*/

} // end namespace gxtubetremelo
