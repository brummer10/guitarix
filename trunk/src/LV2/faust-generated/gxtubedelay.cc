// generated from file '../src/LV2/faust/gxtubedelay.dsp' by dsp2cc:
// Code generated with Faust 2.15.11 (https://faust.grame.fr)


namespace gxtubedelay {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	double fConst4;
	double fConst5;
	double fConst6;
	double fConst7;
	double fConst8;
	double fConst9;
	double fConst10;
	double fConst11;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fConst12;
	double fConst13;
	double fRec3[3];
	double fConst14;
	double fConst15;
	double fConst16;
	double fRec2[3];
	double fConst17;
	double fConst18;
	double fConst19;
	double fConst20;
	double fRec4[2];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec5[2];
	int IOTA;
	double *fVec0;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec6[2];
	double fConst21;
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fConst22;
	double fConst23;
	double fRec7[2];
	double fRec8[2];
	double fRec9[2];
	double fRec10[2];
	double fRec1[2];
	double fConst24;
	double fRec0[2];
	FAUSTFLOAT fVslider4;
	FAUSTFLOAT	*fVslider4_;
	double fRec11[2];

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
	  fVec0(0),
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
	for (int l0 = 0; (l0 < 3); l0 = (l0 + 1)) fRec3[l0] = 0.0;
	for (int l1 = 0; (l1 < 3); l1 = (l1 + 1)) fRec2[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec4[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fRec5[l3] = 0.0;
	for (int l4 = 0; (l4 < 262144); l4 = (l4 + 1)) fVec0[l4] = 0.0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fRec6[l5] = 0.0;
	for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) fRec7[l6] = 0.0;
	for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) fRec8[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fRec9[l8] = 0.0;
	for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) fRec10[l9] = 0.0;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) fRec1[l10] = 0.0;
	for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) fRec0[l11] = 0.0;
	for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) fRec11[l12] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSamplingFreq)));
	fConst1 = (2.08237464507809e-05 * fConst0);
	fConst2 = (fConst1 + 0.00046017036251682698);
	fConst3 = (0.10000000000000001 * (fConst0 / fConst2));
	fConst4 = std::tan((37699.111843077517 / fConst0));
	fConst5 = (1.0 / fConst4);
	fConst6 = (1.0 / (((fConst5 + 1.4142135623730949) / fConst4) + 1.0));
	fConst7 = std::tan((376.99111843077515 / fConst0));
	fConst8 = (1.0 / fConst7);
	fConst9 = (1.0 / (((fConst8 + 1.4142135623730949) / fConst7) + 1.0));
	fConst10 = mydsp_faustpower2_f(fConst7);
	fConst11 = (1.0 / fConst10);
	fConst12 = (((fConst8 + -1.4142135623730949) / fConst7) + 1.0);
	fConst13 = (2.0 * (1.0 - fConst11));
	fConst14 = (0.0 - (2.0 / fConst10));
	fConst15 = (((fConst5 + -1.4142135623730949) / fConst4) + 1.0);
	fConst16 = (2.0 * (1.0 - (1.0 / mydsp_faustpower2_f(fConst4))));
	fConst17 = (2.08237299868718e-05 * fConst0);
	fConst18 = (fConst17 + 0.000460960630154374);
	fConst19 = (0.10000000000000001 * (fConst0 / fConst18));
	fConst20 = ((0.000460960630154374 - fConst17) / fConst18);
	fConst21 = (0.001 * fConst0);
	fConst22 = (10.0 / fConst0);
	fConst23 = (0.0 - fConst22);
	fConst24 = ((0.00046017036251682698 - fConst1) / fConst2);
	fVslider0 = FAUSTFLOAT(0.0);
	fVslider1 = FAUSTFLOAT(0.5);
	fVslider2 = FAUSTFLOAT(0.0);
	fVslider3 = FAUSTFLOAT(0.10000000000000001);
	fVslider4 = FAUSTFLOAT(0.5);
	IOTA = 0;
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void Dsp::mem_alloc()
{
	if (!fVec0) fVec0 = new double[262144];
	mem_allocated = true;
}

void Dsp::mem_free()
{
	mem_allocated = false;
	if (fVec0) { delete fVec0; fVec0 = 0; }
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
#define fVslider0 (*fVslider0_)
#define fVslider1 (*fVslider1_)
#define fVslider2 (*fVslider2_)
#define fVslider3 (*fVslider3_)
#define fVslider4 (*fVslider4_)
	double fSlow0 = double(fVslider0);
	double fSlow1 = (0.004073836948085289 * (std::exp(double(fVslider1)) + -1.0));
	double fSlow2 = (0.004073836948085289 * (std::exp(double(fVslider2)) + -1.0));
	double fSlow3 = (fConst21 * double(fVslider3));
	double fSlow4 = (0.004073836948085289 * (std::exp((1.0 - double(fVslider4))) + -1.0));
	for (int i = 0; (i < count); i = (i + 1)) {
		fRec3[0] = ((fSlow0 * fRec1[1]) - (fConst9 * ((fConst12 * fRec3[2]) + (fConst13 * fRec3[1]))));
		fRec2[0] = ((fConst9 * (((fConst11 * fRec3[0]) + (fConst14 * fRec3[1])) + (fConst11 * fRec3[2]))) - (fConst6 * ((fConst15 * fRec2[2]) + (fConst16 * fRec2[1]))));
		fRec4[0] = (double(input0[i]) - (fConst20 * fRec4[1]));
		fRec5[0] = (fSlow1 + (0.99299999999999999 * fRec5[1]));
		double fTemp0 = ((fConst6 * (fRec2[2] + (fRec2[0] + (2.0 * fRec2[1])))) + (fConst19 * ((fRec4[0] * (0.0 - (0.00027592369187322898 * fRec5[0]))) + (0.00027592369187322898 * (fRec5[0] * fRec4[1])))));
		fVec0[(IOTA & 262143)] = fTemp0;
		fRec6[0] = (fSlow2 + (0.99299999999999999 * fRec6[1]));
		double fTemp1 = ((fRec7[1] != 0.0)?(((fRec8[1] > 0.0) & (fRec8[1] < 1.0))?fRec7[1]:0.0):(((fRec8[1] == 0.0) & (fSlow3 != fRec9[1]))?fConst22:(((fRec8[1] == 1.0) & (fSlow3 != fRec10[1]))?fConst23:0.0)));
		fRec7[0] = fTemp1;
		fRec8[0] = std::max<double>(0.0, std::min<double>(1.0, (fRec8[1] + fTemp1)));
		fRec9[0] = (((fRec8[1] >= 1.0) & (fRec10[1] != fSlow3))?fSlow3:fRec9[1]);
		fRec10[0] = (((fRec8[1] <= 0.0) & (fRec9[1] != fSlow3))?fSlow3:fRec10[1]);
		fRec1[0] = (fTemp0 + (fRec6[0] * (((1.0 - fRec8[0]) * fVec0[((IOTA - int(std::min<double>(131072.0, std::max<double>(0.0, fRec9[0])))) & 262143)]) + (fRec8[0] * fVec0[((IOTA - int(std::min<double>(131072.0, std::max<double>(0.0, fRec10[0])))) & 262143)]))));
		fRec0[0] = (fRec1[0] - (fConst24 * fRec0[1]));
		fRec11[0] = (fSlow4 + (0.99299999999999999 * fRec11[1]));
		output0[i] = FAUSTFLOAT((fConst3 * ((fRec0[1] * ((0.0 - (0.00025707732809075701 * fRec11[0])) + 0.00025707732809075701)) + (0.00025707732809075701 * (fRec0[0] * (fRec11[0] + -1.0))))));
		fRec3[2] = fRec3[1];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		IOTA = (IOTA + 1);
		fRec6[1] = fRec6[0];
		fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
		fRec9[1] = fRec9[0];
		fRec10[1] = fRec10[0];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
		fRec11[1] = fRec11[0];
	}
#undef fVslider0
#undef fVslider1
#undef fVslider2
#undef fVslider3
#undef fVslider4
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
		fVslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case GAIN: 
		fVslider4_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case DELAY: 
		fVslider3_ = (float*)data; // , 0.10000000000000001, 0.10000000000000001, 2500.0, 0.10000000000000001 
		break;
	case FEEDBACK: 
		fVslider0_ = (float*)data; // , 0.0, 0.0, 0.69999999999999996, 0.01 
		break;
	case LEVEL: 
		fVslider2_ = (float*)data; // , 0.0, 0.0, 1.0, 0.10000000000000001 
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
