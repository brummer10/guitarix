// generated from file '../src/LV2/faust/tonecontroll.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace tonecontroll {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT	*fCheckbox0_;
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
	double fConst12;
	double fConst13;
	double fVec0[2];
	double fConst14;
	double fConst15;
	double fRec3[2];
	double fRec2[3];
	double fVec1[2];
	double fConst16;
	double fConst17;
	double fConst18;
	double fConst19;
	double fRec1[2];
	double fRec0[3];
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec4[2];
	double fRec6[2];
	double fRec5[3];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec7[2];
	double fConst20;
	double fConst21;
	double fRec10[2];
	double fRec9[3];
	double fConst22;
	double fRec8[3];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec11[2];
	double fConst23;
	double fConst24;
	double fRec12[2];
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fVec2[2];
	double fRec16[2];
	double fRec15[3];
	double fVec3[2];
	double fRec14[2];
	double fRec13[3];
	double fRec18[2];
	double fRec17[3];
	double fRec21[2];
	double fRec20[3];
	double fRec19[3];
	double fRec22[2];

	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(uint32_t sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(uint32_t sample_rate, PluginLV2*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginLV2() {
	version = PLUGINLV2_VERSION;
	id = "tonemodul";
	name = N_("3 Band EQ");
	mono_audio = 0;
	stereo_audio = compute_static;
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fVec0[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec3[l1] = 0.0;
	for (int l2 = 0; l2 < 3; l2 = l2 + 1) fRec2[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fVec1[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fRec1[l4] = 0.0;
	for (int l5 = 0; l5 < 3; l5 = l5 + 1) fRec0[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fRec4[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec6[l7] = 0.0;
	for (int l8 = 0; l8 < 3; l8 = l8 + 1) fRec5[l8] = 0.0;
	for (int l9 = 0; l9 < 2; l9 = l9 + 1) fRec7[l9] = 0.0;
	for (int l10 = 0; l10 < 2; l10 = l10 + 1) fRec10[l10] = 0.0;
	for (int l11 = 0; l11 < 3; l11 = l11 + 1) fRec9[l11] = 0.0;
	for (int l12 = 0; l12 < 3; l12 = l12 + 1) fRec8[l12] = 0.0;
	for (int l13 = 0; l13 < 2; l13 = l13 + 1) fRec11[l13] = 0.0;
	for (int l14 = 0; l14 < 2; l14 = l14 + 1) fRec12[l14] = 0.0;
	for (int l15 = 0; l15 < 2; l15 = l15 + 1) fVec2[l15] = 0.0;
	for (int l16 = 0; l16 < 2; l16 = l16 + 1) fRec16[l16] = 0.0;
	for (int l17 = 0; l17 < 3; l17 = l17 + 1) fRec15[l17] = 0.0;
	for (int l18 = 0; l18 < 2; l18 = l18 + 1) fVec3[l18] = 0.0;
	for (int l19 = 0; l19 < 2; l19 = l19 + 1) fRec14[l19] = 0.0;
	for (int l20 = 0; l20 < 3; l20 = l20 + 1) fRec13[l20] = 0.0;
	for (int l21 = 0; l21 < 2; l21 = l21 + 1) fRec18[l21] = 0.0;
	for (int l22 = 0; l22 < 3; l22 = l22 + 1) fRec17[l22] = 0.0;
	for (int l23 = 0; l23 < 2; l23 = l23 + 1) fRec21[l23] = 0.0;
	for (int l24 = 0; l24 < 3; l24 = l24 + 1) fRec20[l24] = 0.0;
	for (int l25 = 0; l25 < 3; l25 = l25 + 1) fRec19[l25] = 0.0;
	for (int l26 = 0; l26 < 2; l26 = l26 + 1) fRec22[l26] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = std::tan(1884.9555921538758 / fConst0);
	fConst2 = 1.0 / mydsp_faustpower2_f(fConst1);
	fConst3 = 2.0 * (1.0 - fConst2);
	fConst4 = 1.0 / fConst1;
	fConst5 = (fConst4 + -1.0000000000000004) / fConst1 + 1.0;
	fConst6 = 1.0 / ((fConst4 + 1.0000000000000004) / fConst1 + 1.0);
	fConst7 = std::tan(7539.822368615503 / fConst0);
	fConst8 = mydsp_faustpower2_f(fConst7);
	fConst9 = 2.0 * (1.0 - 1.0 / fConst8);
	fConst10 = 1.0 / fConst7;
	fConst11 = (fConst10 + -1.0000000000000004) / fConst7 + 1.0;
	fConst12 = (fConst10 + 1.0000000000000004) / fConst7 + 1.0;
	fConst13 = 1.0 / fConst12;
	fConst14 = 1.0 - fConst10;
	fConst15 = 1.0 / (fConst10 + 1.0);
	fConst16 = 1.0 / (fConst1 * fConst12);
	fConst17 = 1.0 - fConst4;
	fConst18 = fConst4 + 1.0;
	fConst19 = 1.0 / fConst18;
	fConst20 = 1.0 - fConst17 / fConst1;
	fConst21 = 1.0 / (fConst18 / fConst1 + 1.0);
	fConst22 = 1.0 / (fConst8 * fConst12);
	fConst23 = std::exp(-(0.2 / fConst0));
	fConst24 = std::exp(-(2e+02 / fConst0));
	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
#define fCheckbox0 (*fCheckbox0_)
#define fVslider0 (*fVslider0_)
#define fVslider1 (*fVslider1_)
#define fVslider2 (*fVslider2_)
#define fVslider3 (*fVslider3_)
	int iSlow0 = int(double(fCheckbox0));
	double fSlow1 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider0));
	double fSlow2 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider1));
	double fSlow3 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider2));
	double fSlow4 = double(fVslider3);
	double fSlow5 = 5.0 * fSlow4;
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		double fTemp0 = double(input0[i0]);
		fVec0[0] = fTemp0;
		fRec3[0] = -(fConst15 * (fConst14 * fRec3[1] - (fTemp0 + fVec0[1])));
		fRec2[0] = fRec3[0] - fConst13 * (fConst11 * fRec2[2] + fConst9 * fRec2[1]);
		double fTemp1 = fRec2[2] + fRec2[0] + 2.0 * fRec2[1];
		fVec1[0] = fTemp1;
		fRec1[0] = -(fConst19 * (fConst17 * fRec1[1] - fConst16 * (fTemp1 - fVec1[1])));
		fRec0[0] = fRec1[0] - fConst6 * (fConst5 * fRec0[2] + fConst3 * fRec0[1]);
		double fTemp2 = 2.0 * fRec0[1];
		fRec4[0] = fSlow1 + 0.999 * fRec4[1];
		fRec6[0] = -(fConst19 * (fConst17 * fRec6[1] - fConst13 * (fTemp1 + fVec1[1])));
		fRec5[0] = fRec6[0] - fConst6 * (fConst5 * fRec5[2] + fConst3 * fRec5[1]);
		fRec7[0] = fSlow2 + 0.999 * fRec7[1];
		double fTemp3 = fRec7[0] * (fRec5[2] + fRec5[0] + 2.0 * fRec5[1]);
		double fTemp4 = fConst3 * fRec8[1];
		fRec10[0] = -(fConst15 * (fConst14 * fRec10[1] - fConst10 * (fTemp0 - fVec0[1])));
		fRec9[0] = fRec10[0] - fConst13 * (fConst11 * fRec9[2] + fConst9 * fRec9[1]);
		fRec8[0] = fConst22 * (fRec9[2] + (fRec9[0] - 2.0 * fRec9[1])) - fConst21 * (fConst20 * fRec8[2] + fTemp4);
		fRec11[0] = fSlow3 + 0.999 * fRec11[1];
		double fTemp5 = fRec11[0] * (fRec8[2] + fConst21 * (fTemp4 + fConst20 * fRec8[0]));
		double fTemp6 = fTemp5 + fConst6 * (fTemp3 + fConst2 * fRec4[0] * (fRec0[0] + fRec0[2] - fTemp2));
		double fTemp7 = std::max<double>(1.0, std::fabs(fTemp5 + fConst6 * (fTemp3 + fConst2 * fRec4[0] * (fRec0[2] + (fRec0[0] - fTemp2)))));
		double fTemp8 = fConst24 * double(fRec12[1] < fTemp7) + fConst23 * double(fRec12[1] >= fTemp7);
		fRec12[0] = fRec12[1] * fTemp8 + fTemp7 * (1.0 - fTemp8);
		double fTemp9 = std::max<double>(0.0, fSlow5 + 2e+01 * std::log10(std::max<double>(2.2250738585072014e-308, fRec12[0])));
		double fTemp10 = std::min<double>(1.0, std::max<double>(0.0, 0.09522902580706599 * fTemp9));
		output0[i0] = FAUSTFLOAT(((iSlow0) ? std::pow(1e+01, 0.05 * (fSlow4 - 2.0 * (fTemp9 * fTemp10 / (2.0 * fTemp10 + 1.0)))) * fTemp6 : fTemp6));
		double fTemp11 = double(input1[i0]);
		fVec2[0] = fTemp11;
		fRec16[0] = -(fConst15 * (fConst14 * fRec16[1] - (fTemp11 + fVec2[1])));
		fRec15[0] = fRec16[0] - fConst13 * (fConst11 * fRec15[2] + fConst9 * fRec15[1]);
		double fTemp12 = fRec15[2] + fRec15[0] + 2.0 * fRec15[1];
		fVec3[0] = fTemp12;
		fRec14[0] = -(fConst19 * (fConst17 * fRec14[1] - fConst16 * (fTemp12 - fVec3[1])));
		fRec13[0] = fRec14[0] - fConst6 * (fConst5 * fRec13[2] + fConst3 * fRec13[1]);
		double fTemp13 = 2.0 * fRec13[1];
		fRec18[0] = -(fConst19 * (fConst17 * fRec18[1] - fConst13 * (fTemp12 + fVec3[1])));
		fRec17[0] = fRec18[0] - fConst6 * (fConst5 * fRec17[2] + fConst3 * fRec17[1]);
		double fTemp14 = fRec7[0] * (fRec17[2] + fRec17[0] + 2.0 * fRec17[1]);
		double fTemp15 = fConst3 * fRec19[1];
		fRec21[0] = -(fConst15 * (fConst14 * fRec21[1] - fConst10 * (fTemp11 - fVec2[1])));
		fRec20[0] = fRec21[0] - fConst13 * (fConst11 * fRec20[2] + fConst9 * fRec20[1]);
		fRec19[0] = fConst22 * (fRec20[2] + (fRec20[0] - 2.0 * fRec20[1])) - fConst21 * (fConst20 * fRec19[2] + fTemp15);
		double fTemp16 = fRec11[0] * (fRec19[2] + fConst21 * (fTemp15 + fConst20 * fRec19[0]));
		double fTemp17 = fTemp16 + fConst6 * (fTemp14 + fConst2 * fRec4[0] * (fRec13[0] + fRec13[2] - fTemp13));
		double fTemp18 = std::max<double>(1.0, std::fabs(fTemp16 + fConst6 * (fTemp14 + fConst2 * fRec4[0] * (fRec13[2] + (fRec13[0] - fTemp13)))));
		double fTemp19 = fConst24 * double(fRec22[1] < fTemp18) + fConst23 * double(fRec22[1] >= fTemp18);
		fRec22[0] = fRec22[1] * fTemp19 + fTemp18 * (1.0 - fTemp19);
		double fTemp20 = std::max<double>(0.0, fSlow5 + 2e+01 * std::log10(std::max<double>(2.2250738585072014e-308, fRec22[0])));
		double fTemp21 = std::min<double>(1.0, std::max<double>(0.0, 0.09522902580706599 * fTemp20));
		output1[i0] = FAUSTFLOAT(((iSlow0) ? std::pow(1e+01, 0.05 * (fSlow4 - 2.0 * (fTemp20 * fTemp21 / (2.0 * fTemp21 + 1.0)))) * fTemp17 : fTemp17));
		fVec0[1] = fVec0[0];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fVec1[1] = fVec1[0];
		fRec1[1] = fRec1[0];
		fRec0[2] = fRec0[1];
		fRec0[1] = fRec0[0];
		fRec4[1] = fRec4[0];
		fRec6[1] = fRec6[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		fRec7[1] = fRec7[0];
		fRec10[1] = fRec10[0];
		fRec9[2] = fRec9[1];
		fRec9[1] = fRec9[0];
		fRec8[2] = fRec8[1];
		fRec8[1] = fRec8[0];
		fRec11[1] = fRec11[0];
		fRec12[1] = fRec12[0];
		fVec2[1] = fVec2[0];
		fRec16[1] = fRec16[0];
		fRec15[2] = fRec15[1];
		fRec15[1] = fRec15[0];
		fVec3[1] = fVec3[0];
		fRec14[1] = fRec14[0];
		fRec13[2] = fRec13[1];
		fRec13[1] = fRec13[0];
		fRec18[1] = fRec18[0];
		fRec17[2] = fRec17[1];
		fRec17[1] = fRec17[0];
		fRec21[1] = fRec21[0];
		fRec20[2] = fRec20[1];
		fRec20[1] = fRec20[0];
		fRec19[2] = fRec19[1];
		fRec19[1] = fRec19[0];
		fRec22[1] = fRec22[0];
	}
#undef fCheckbox0
#undef fVslider0
#undef fVslider1
#undef fVslider2
#undef fVslider3
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case ON: 
		fCheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case BASS: 
		fVslider1_ = (float*)data; // , 0.0, -5.0, 5.0, 0.01 
		break;
	case MIDDLE: 
		fVslider0_ = (float*)data; // , 0.0, -5.0, 5.0, 0.01 
		break;
	case TREBLE: 
		fVslider2_ = (float*)data; // , 0.0, -5.0, 5.0, 0.01 
		break;
	case SHARPER: 
		fVslider3_ = (float*)data; // , -2.0, -2.5, 5.0, 0.1 
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
   BASS, 
   MIDDLE, 
   ON, 
   TREBLE, 
   SHARPER, 
} PortIndex;
*/

} // end namespace tonecontroll
