// generated from file '../src/LV2/faust/gxtubevibrato.dsp' by dsp2cc:
// Code generated with Faust 2.15.11 (https://faust.grame.fr)


namespace gxtubevibrato {

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
	int iVec0[2];
	double fConst7;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT	*fCheckbox0_;
	double fConst8;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	int iRec6[2];
	int iRec5[2];
	double fConst9;
	double fRec9[2];
	double fRec8[2];
	double fRec7[2];
	double fConst10;
	double fConst11;
	double fRec1[2];
	double fRec2[2];
	double fRec3[2];
	double fRec4[2];
	double fConst12;
	double fRec10[2];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec11[2];
	int IOTA;
	double *fVec1;
	double fConst13;
	double fRec0[2];
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fRec12[2];

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
	id = "gxtubevibrato";
	name = N_("gxtubevibrato");
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) iVec0[l0] = 0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) iRec6[l1] = 0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) iRec5[l2] = 0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fRec9[l3] = 0.0;
	for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) fRec8[l4] = 0.0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fRec7[l5] = 0.0;
	for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) fRec1[l6] = 0.0;
	for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) fRec2[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fRec3[l8] = 0.0;
	for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) fRec4[l9] = 0.0;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) fRec10[l10] = 0.0;
	for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) fRec11[l11] = 0.0;
	for (int l12 = 0; (l12 < 131072); l12 = (l12 + 1)) fVec1[l12] = 0.0;
	for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) fRec0[l13] = 0.0;
	for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) fRec12[l14] = 0.0;
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
	fConst3 = (fConst0 / fConst2);
	fConst4 = (2.08237299868718e-05 * fConst0);
	fConst5 = (fConst4 + 0.000460960630154374);
	fConst6 = (0.10000000000000001 * (fConst0 / fConst5));
	fConst7 = (0.0050000000000000001 * fConst0);
	fConst8 = (0.5 * fConst0);
	fConst9 = (6.2831853071795862 / fConst0);
	fConst10 = (10.0 / fConst0);
	fConst11 = (0.0 - fConst10);
	fConst12 = ((0.000460960630154374 - fConst4) / fConst5);
	fConst13 = ((0.00046017036251682698 - fConst1) / fConst2);
	fVslider0 = FAUSTFLOAT(0.5);
	fCheckbox0 = FAUSTFLOAT(0.0);
	fVslider1 = FAUSTFLOAT(5.0);
	fVslider2 = FAUSTFLOAT(0.5);
	fVslider3 = FAUSTFLOAT(0.5);
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
#define fVslider0 (*fVslider0_)
#define fCheckbox0 (*fCheckbox0_)
#define fVslider1 (*fVslider1_)
#define fVslider2 (*fVslider2_)
#define fVslider3 (*fVslider3_)
	double fSlow0 = (fConst7 * double(fVslider0));
	int iSlow1 = int(double(fCheckbox0));
	double fSlow2 = double(fVslider1);
	int iSlow3 = int((fConst8 / fSlow2));
	double fSlow4 = (1.0 / double(iSlow3));
	double fSlow5 = (fConst9 * fSlow2);
	double fSlow6 = (0.004073836948085289 * (std::exp(double(fVslider2)) + -1.0));
	double fSlow7 = (0.004073836948085289 * (std::exp((1.0 - double(fVslider3))) + -1.0));
	for (int i = 0; (i < count); i = (i + 1)) {
		iVec0[0] = 1;
		iRec6[0] = ((iRec6[1] > 0)?((2 * (iRec5[1] < iSlow3)) + -1):(1 - (2 * (iRec5[1] > 0))));
		iRec5[0] = (iRec6[0] + iRec5[1]);
		fRec9[0] = (fRec9[1] + (fSlow5 * (0.0 - fRec7[1])));
		fRec8[0] = ((fSlow5 * fRec9[0]) + (double((1 - iVec0[1])) + fRec8[1]));
		fRec7[0] = fRec8[0];
		double fTemp0 = (fSlow0 * (((iSlow1?std::max<double>(0.0, (0.5 * (fRec7[0] + 1.0))):(fSlow4 * double(iRec5[0]))) + 1.0) + 1.0));
		double fTemp1 = ((fRec1[1] != 0.0)?(((fRec2[1] > 0.0) & (fRec2[1] < 1.0))?fRec1[1]:0.0):(((fRec2[1] == 0.0) & (fTemp0 != fRec3[1]))?fConst10:(((fRec2[1] == 1.0) & (fTemp0 != fRec4[1]))?fConst11:0.0)));
		fRec1[0] = fTemp1;
		fRec2[0] = std::max<double>(0.0, std::min<double>(1.0, (fRec2[1] + fTemp1)));
		fRec3[0] = (((fRec2[1] >= 1.0) & (fRec4[1] != fTemp0))?fTemp0:fRec3[1]);
		fRec4[0] = (((fRec2[1] <= 0.0) & (fRec3[1] != fTemp0))?fTemp0:fRec4[1]);
		fRec10[0] = (double(input0[i]) - (fConst12 * fRec10[1]));
		fRec11[0] = (fSlow6 + (0.99299999999999999 * fRec11[1]));
		double fTemp2 = ((fRec10[0] * (0.0 - (0.00027592369187322898 * fRec11[0]))) + (0.00027592369187322898 * (fRec11[0] * fRec10[1])));
		fVec1[(IOTA & 131071)] = fTemp2;
		fRec0[0] = ((fConst6 * (((1.0 - fRec2[0]) * fVec1[((IOTA - int(std::min<double>(65536.0, std::max<double>(0.0, fRec3[0])))) & 131071)]) + (fRec2[0] * fVec1[((IOTA - int(std::min<double>(65536.0, std::max<double>(0.0, fRec4[0])))) & 131071)]))) - (fConst13 * fRec0[1]));
		fRec12[0] = (fSlow7 + (0.99299999999999999 * fRec12[1]));
		output0[i] = FAUSTFLOAT((fConst3 * ((fRec0[1] * ((0.0 - (0.00025707732809075701 * fRec12[0])) + 0.00025707732809075701)) + (0.00025707732809075701 * (fRec0[0] * (fRec12[0] + -1.0))))));
		iVec0[1] = iVec0[0];
		iRec6[1] = iRec6[0];
		iRec5[1] = iRec5[0];
		fRec9[1] = fRec9[0];
		fRec8[1] = fRec8[0];
		fRec7[1] = fRec7[0];
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		IOTA = (IOTA + 1);
		fRec0[1] = fRec0[0];
		fRec12[1] = fRec12[0];
	}
#undef fVslider0
#undef fCheckbox0
#undef fVslider1
#undef fVslider2
#undef fVslider3
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
		fVslider2_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case GAIN: 
		fVslider3_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	// static const value_pair fCheckbox0_values[] = {{"os.triangle"},{"sine"},{0}};
	case SINEWAVE: 
		fCheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case DEPTH: 
		fVslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case SPEED: 
		fVslider1_ = (float*)data; // , 5.0, 0.0, 14.0, 0.10000000000000001 
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

} // end namespace gxtubevibrato
