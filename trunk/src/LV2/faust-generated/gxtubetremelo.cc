// generated from file '../src/LV2/faust/gxtubetremelo.dsp' by dsp2cc:
// Code generated with Faust 2.15.11 (https://faust.grame.fr)


namespace gxtubetremelo {

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
	int iVec0[2];
	double fRec1[2];
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec2[2];
	double fConst8;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT	*fCheckbox0_;
	double fConst9;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	int iRec5[2];
	int iRec4[2];
	double fConst10;
	double fRec8[2];
	double fRec7[2];
	double fRec6[2];
	double fRec3[2];
	double fConst11;
	double fRec0[2];
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fRec9[2];

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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) iVec0[l0] = 0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec1[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec2[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) iRec5[l3] = 0;
	for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) iRec4[l4] = 0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fRec8[l5] = 0.0;
	for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) fRec7[l6] = 0.0;
	for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) fRec6[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fRec3[l8] = 0.0;
	for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) fRec0[l9] = 0.0;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) fRec9[l10] = 0.0;
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
	fConst4 = (2.0823902452746101e-05 * fConst0);
	fConst5 = (fConst4 + 0.00045268226818868002);
	fConst6 = (270.0 * (fConst0 / fConst5));
	fConst7 = ((0.00045268226818868002 - fConst4) / fConst5);
	fConst8 = (1.0 / fConst0);
	fConst9 = (0.5 * fConst0);
	fConst10 = (6.2831853071795862 / fConst0);
	fConst11 = ((0.00046017036251682698 - fConst1) / fConst2);
	fVslider0 = FAUSTFLOAT(0.5);
	fVslider1 = FAUSTFLOAT(0.5);
	fCheckbox0 = FAUSTFLOAT(0.0);
	fVslider2 = FAUSTFLOAT(5.0);
	fVslider3 = FAUSTFLOAT(0.5);
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fVslider0 (*fVslider0_)
#define fVslider1 (*fVslider1_)
#define fCheckbox0 (*fCheckbox0_)
#define fVslider2 (*fVslider2_)
#define fVslider3 (*fVslider3_)
	double fSlow0 = (0.004073836948085289 * (std::exp(double(fVslider0)) + -1.0));
	double fSlow1 = double(fVslider1);
	int iSlow2 = int(double(fCheckbox0));
	double fSlow3 = double(fVslider2);
	int iSlow4 = int((fConst9 / fSlow3));
	double fSlow5 = (1.0 / double(iSlow4));
	double fSlow6 = (fConst10 * fSlow3);
	double fSlow7 = (0.004073836948085289 * (std::exp((1.0 - double(fVslider3))) + -1.0));
	for (int i = 0; (i < count); i = (i + 1)) {
		iVec0[0] = 1;
		fRec1[0] = (double(input0[i]) - (fConst7 * fRec1[1]));
		fRec2[0] = (fSlow0 + (0.99299999999999999 * fRec2[1]));
		double fTemp0 = (fRec3[1] * (1.0 - (fConst8 / (fConst8 + (0.059999999999999998 * std::exp((0.0 - (2.4849066497880004 * fRec3[1]))))))));
		iRec5[0] = ((iRec5[1] > 0)?((2 * (iRec4[1] < iSlow4)) + -1):(1 - (2 * (iRec4[1] > 0))));
		iRec4[0] = (iRec5[0] + iRec4[1]);
		fRec8[0] = (fRec8[1] + (fSlow6 * (0.0 - fRec6[1])));
		fRec7[0] = ((fSlow6 * fRec8[0]) + (double((1 - iVec0[1])) + fRec7[1]));
		fRec6[0] = fRec7[0];
		fRec3[0] = (fTemp0 + (fConst8 * (std::pow(((fSlow1 * ((iSlow2?std::max<double>(0.0, (0.5 * (fRec6[0] + 1.0))):(fSlow5 * double(iRec4[0]))) + -1.0)) + 1.0), 1.8999999999999999) / (fConst8 + (0.059999999999999998 * std::exp((0.0 - (2.4849066497880004 * fTemp0))))))));
		fRec0[0] = ((fConst6 * (((fRec1[0] * (0.0 - (0.00056464147870750696 * fRec2[0]))) + (0.00056464147870750696 * (fRec2[0] * fRec1[1]))) / (std::exp((13.815510557964274 / std::log(((8.5519675079294171 * fRec3[0]) + 2.7182818284590451)))) + 2700.0))) - (fConst11 * fRec0[1]));
		fRec9[0] = (fSlow7 + (0.99299999999999999 * fRec9[1]));
		output0[i] = FAUSTFLOAT((fConst3 * ((fRec0[1] * ((0.0 - (0.00025707732809075701 * fRec9[0])) + 0.00025707732809075701)) + (0.00025707732809075701 * (fRec0[0] * (fRec9[0] + -1.0))))));
		iVec0[1] = iVec0[0];
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		iRec5[1] = iRec5[0];
		iRec4[1] = iRec4[0];
		fRec8[1] = fRec8[0];
		fRec7[1] = fRec7[0];
		fRec6[1] = fRec6[0];
		fRec3[1] = fRec3[0];
		fRec0[1] = fRec0[0];
		fRec9[1] = fRec9[0];
	}
#undef fVslider0
#undef fVslider1
#undef fCheckbox0
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
		fVslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case GAIN: 
		fVslider3_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	// static const value_pair fCheckbox0_values[] = {{"os.triangle"},{"sine"},{0}};
	case SINEWAVE: 
		fCheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case DEPTH: 
		fVslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case SPEED: 
		fVslider2_ = (float*)data; // , 5.0, 0.10000000000000001, 14.0, 0.10000000000000001 
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
