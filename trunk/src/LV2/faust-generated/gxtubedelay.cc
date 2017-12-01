// generated from file '../src/LV2/faust/gxtubedelay.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)


namespace gxtubedelay {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec0[2];
	double 	fConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec3[2];
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fRec4[2];
	double 	fConst8;
	double 	fConst9;
	double 	fConst10;
	double 	fConst11;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fVec0[2];
	double 	fConst12;
	double 	fConst13;
	double 	fRec6[2];
	double 	fConst14;
	double 	fConst15;
	double 	fConst16;
	double 	fConst17;
	double 	fRec5[2];
	int 	IOTA;
	double *fVec1;
	double 	fConst18;
	double 	fConst19;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fConst20;
	double 	fRec7[2];
	double 	fRec8[2];
	double 	fRec9[2];
	double 	fRec10[2];
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT	*fslider4_;
	double 	fRec11[2];
	double 	fRec2[2];
	double 	fRec1[2];
	double 	fConst21;

	bool mem_allocated;
	void mem_alloc();
	void mem_free();
	void connect(uint32_t port,void* data);
	void clear_state_f();
	int activate(bool start);
	void init(uint32_t samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);

	static void clear_state_f_static(PluginLV2*);
	static int activate_static(bool start, PluginLV2*);
	static void init_static(uint32_t samplingFreq, PluginLV2*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginLV2(),
	  fVec1(0),
	  mem_allocated(false) {
	version = PLUGINLV2_VERSION;
	id = "gxtubedelay";
	name = N_("Tube Delay");
	mono_audio = compute_static;
	stereo_audio = 0;
	set_samplerate = init_static;
	activate_plugin = activate_static;
	connect_ports = connect_static;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<131072; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = min(1.92e+05, max(1.0, (double)fSamplingFreq));
	fConst1 = double(fConst0);
	fConst2 = (2.08237464507809e-05 * fConst1);
	fConst3 = (0.000460170362516827 + fConst2);
	fConst4 = ((0.000460170362516827 - fConst2) / fConst3);
	fConst5 = (2.08237299868718e-05 * fConst1);
	fConst6 = (0.000460960630154374 + fConst5);
	fConst7 = ((0.000460960630154374 - fConst5) / fConst6);
	fConst8 = (0.1 * (fConst1 / fConst6));
	fConst9 = (1.0 / tan((376.99111843077515 / fConst0)));
	fConst10 = (1 + fConst9);
	fConst11 = (0 - ((1 - fConst9) / fConst10));
	fConst12 = (0 - fConst9);
	fConst13 = (1.0 / fConst10);
	fConst14 = (1.0 / tan((37699.11184307752 / fConst0)));
	fConst15 = (1 + fConst14);
	fConst16 = (1.0 / fConst15);
	fConst17 = (0 - ((1 - fConst14) / fConst15));
	fConst18 = (1e+01 / fConst0);
	fConst19 = (0 - fConst18);
	fConst20 = (0.001 * fConst0);
	fConst21 = (fConst1 / fConst3);
	IOTA = 0;
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void Dsp::mem_alloc()
{
	if (!fVec1) fVec1 = new double[131072];
	mem_allocated = true;
}

void Dsp::mem_free()
{
	mem_allocated = false;
	if (fVec1) { delete fVec1; fVec1 = 0; }
}

int Dsp::activate(bool start)
{
	if (start) {
		if (!mem_allocated) {
			mem_alloc();
			clear_state_f();
		}
	} else if (mem_allocated) {
		mem_free();
	}
	return 0;
}

int Dsp::activate_static(bool start, PluginLV2 *p)
{
	return static_cast<Dsp*>(p)->activate(start);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
#define fslider2 (*fslider2_)
#define fslider3 (*fslider3_)
#define fslider4 (*fslider4_)
	double 	fSlow0 = (0.004073836948085289 * (exp((1 - double(fslider0))) - 1));
	double 	fSlow1 = (0.004073836948085289 * (exp(double(fslider1)) - 1));
	double 	fSlow2 = double(fslider2);
	double 	fSlow3 = (fConst9 * fSlow2);
	double 	fSlow4 = (fConst20 * double(fslider3));
	double 	fSlow5 = (0.004073836948085289 * (exp(double(fslider4)) - 1));
	for (int i=0; i<count; i++) {
		fRec0[0] = (fSlow0 + (0.993 * fRec0[1]));
		double fTemp0 = (0.000257077328090757 * fRec0[0]);
		fRec3[0] = (fSlow1 + (0.993 * fRec3[1]));
		fRec4[0] = ((double)input0[i] - (fConst7 * fRec4[1]));
		fVec0[0] = (fSlow2 * fRec2[1]);
		fRec6[0] = ((fConst13 * ((fSlow3 * fRec2[1]) + (fConst12 * fVec0[1]))) + (fConst11 * fRec6[1]));
		fRec5[0] = ((fConst17 * fRec5[1]) + (fConst16 * (fRec6[1] + fRec6[0])));
		double fTemp1 = (fRec5[0] + (fConst8 * ((fRec4[0] * (0 - (0.000275923691873229 * fRec3[0]))) + (0.000275923691873229 * (fRec4[1] * fRec3[0])))));
		fVec1[IOTA&131071] = fTemp1;
		double fTemp2 = ((int((fRec7[1] != 0.0)))?((int(((fRec8[1] > 0.0) & (fRec8[1] < 1.0))))?fRec7[1]:0):((int(((fRec8[1] == 0.0) & (fSlow4 != fRec9[1]))))?fConst18:((int(((fRec8[1] == 1.0) & (fSlow4 != fRec10[1]))))?fConst19:0)));
		fRec7[0] = fTemp2;
		fRec8[0] = max(0.0, min(1.0, (fRec8[1] + fTemp2)));
		fRec9[0] = ((int(((fRec8[1] >= 1.0) & (fRec10[1] != fSlow4))))?fSlow4:fRec9[1]);
		fRec10[0] = ((int(((fRec8[1] <= 0.0) & (fRec9[1] != fSlow4))))?fSlow4:fRec10[1]);
		fRec11[0] = (fSlow5 + (0.993 * fRec11[1]));
		fRec2[0] = (fVec1[IOTA&131071] + (fRec11[0] * (((1.0 - fRec8[0]) * fVec1[(IOTA-int((int(fRec9[0]) & 131071)))&131071]) + (fRec8[0] * fVec1[(IOTA-int((int(fRec10[0]) & 131071)))&131071]))));
		fRec1[0] = (fRec2[0] - (fConst4 * fRec1[1]));
		output0[i] = (FAUSTFLOAT)(fConst21 * ((fRec1[0] * (fTemp0 - 0.000257077328090757)) + (fRec1[1] * (0.000257077328090757 - fTemp0))));
		// post processing
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec11[1] = fRec11[0];
		fRec10[1] = fRec10[0];
		fRec9[1] = fRec9[0];
		fRec8[1] = fRec8[0];
		fRec7[1] = fRec7[0];
		IOTA = IOTA+1;
		fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		fVec0[1] = fVec0[0];
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		fRec0[1] = fRec0[0];
	}
#undef fslider0
#undef fslider1
#undef fslider2
#undef fslider3
#undef fslider4
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
		fslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case GAIN: 
		fslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case DELAY: 
		fslider3_ = (float*)data; // , 0.0, 0.1, 2.5e+03, 0.1 
		break;
	case FEEDBACK: 
		fslider2_ = (float*)data; // , 0.0, 0.0, 1.0, 0.01 
		break;
	case LEVEL: 
		fslider4_ = (float*)data; // , 0.0, 0.0, 1.0, 0.1 
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
   DELAY, 
   FEEDBACK, 
   LEVEL, 
} PortIndex;
*/

} // end namespace gxtubedelay
