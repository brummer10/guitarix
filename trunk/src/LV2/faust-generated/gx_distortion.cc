// generated from file '../src/LV2/faust/gx_distortion.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace gx_distortion {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	int iVec0[2];
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec1[2];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fConst4;
	FAUSTFLOAT fEntry0;
	FAUSTFLOAT	*fEntry0_;
	double fConst5;
	double fConst6;
	double fConst7;
	double fConst8;
	double fConst9;
	double fConst10;
	double fConst11;
	double fRec8[2];
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT	*fCheckbox0_;
	FAUSTFLOAT fVslider4;
	FAUSTFLOAT	*fVslider4_;
	FAUSTFLOAT fVslider5;
	FAUSTFLOAT	*fVslider5_;
	double fVec1[2];
	FAUSTFLOAT fVslider6;
	FAUSTFLOAT	*fVslider6_;
	double fRec9[2];
	double fConst12;
	double fConst13;
	double fRec7[3];
	double fVec2[2];
	double fConst14;
	double fConst15;
	double fRec6[2];
	double fRec5[2];
	double fRec4[3];
	FAUSTFLOAT fEntry1;
	FAUSTFLOAT	*fEntry1_;
	double fRec3[3];
	FAUSTFLOAT fEntry2;
	FAUSTFLOAT	*fEntry2_;
	double fRec2[3];
	FAUSTFLOAT fVslider7;
	FAUSTFLOAT	*fVslider7_;
	double fRec10[2];
	FAUSTFLOAT fVslider8;
	FAUSTFLOAT	*fVslider8_;
	double fRec15[2];
	double fRec14[3];
	double fVec3[2];
	double fRec13[2];
	double fRec12[3];
	double fRec11[3];
	FAUSTFLOAT fVslider9;
	FAUSTFLOAT	*fVslider9_;
	double fRec16[2];
	FAUSTFLOAT fVslider10;
	FAUSTFLOAT	*fVslider10_;
	double fRec20[2];
	double fRec19[3];
	double fVec4[2];
	double fRec18[2];
	double fRec17[3];
	FAUSTFLOAT fVslider11;
	FAUSTFLOAT	*fVslider11_;
	double fRec21[2];
	FAUSTFLOAT fVslider12;
	FAUSTFLOAT	*fVslider12_;
	double fRec23[2];
	double fRec22[3];
	double fVec5[2];
	double fRec0[2];
	FAUSTFLOAT fVslider13;
	FAUSTFLOAT	*fVslider13_;
	double fRec24[2];

	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(uint32_t sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(uint32_t sample_rate, PluginLV2*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	Dsp();
	~Dsp();
};



static const char* parm_groups[] = {
	"resonator", N_("Distortion resonator"),
	0
	};

Dsp::Dsp()
	: PluginLV2() {
	version = PLUGINLV2_VERSION;
	id = "gx_distortion";
	name = N_("Multi Band Distortion");
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
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec8[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fVec1[l3] = 0.0;
	for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) fRec9[l4] = 0.0;
	for (int l5 = 0; (l5 < 3); l5 = (l5 + 1)) fRec7[l5] = 0.0;
	for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) fVec2[l6] = 0.0;
	for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) fRec6[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fRec5[l8] = 0.0;
	for (int l9 = 0; (l9 < 3); l9 = (l9 + 1)) fRec4[l9] = 0.0;
	for (int l10 = 0; (l10 < 3); l10 = (l10 + 1)) fRec3[l10] = 0.0;
	for (int l11 = 0; (l11 < 3); l11 = (l11 + 1)) fRec2[l11] = 0.0;
	for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) fRec10[l12] = 0.0;
	for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) fRec15[l13] = 0.0;
	for (int l14 = 0; (l14 < 3); l14 = (l14 + 1)) fRec14[l14] = 0.0;
	for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) fVec3[l15] = 0.0;
	for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) fRec13[l16] = 0.0;
	for (int l17 = 0; (l17 < 3); l17 = (l17 + 1)) fRec12[l17] = 0.0;
	for (int l18 = 0; (l18 < 3); l18 = (l18 + 1)) fRec11[l18] = 0.0;
	for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) fRec16[l19] = 0.0;
	for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) fRec20[l20] = 0.0;
	for (int l21 = 0; (l21 < 3); l21 = (l21 + 1)) fRec19[l21] = 0.0;
	for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) fVec4[l22] = 0.0;
	for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) fRec18[l23] = 0.0;
	for (int l24 = 0; (l24 < 3); l24 = (l24 + 1)) fRec17[l24] = 0.0;
	for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) fRec21[l25] = 0.0;
	for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) fRec23[l26] = 0.0;
	for (int l27 = 0; (l27 < 3); l27 = (l27 + 1)) fRec22[l27] = 0.0;
	for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) fVec5[l28] = 0.0;
	for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) fRec0[l29] = 0.0;
	for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) fRec24[l30] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = (1.0 / std::tan((20517.741620594938 / fConst0)));
	fConst2 = (1.0 / (fConst1 + 1.0));
	fConst3 = (1.0 - fConst1);
	fConst4 = (3.1415926535897931 / fConst0);
	fConst5 = std::tan((47123.889803846898 / fConst0));
	fConst6 = (1.0 / fConst5);
	fConst7 = (1.0 / (((fConst6 + 1.4142135623730949) / fConst5) + 1.0));
	fConst8 = std::tan((97.389372261283583 / fConst0));
	fConst9 = (1.0 / fConst8);
	fConst10 = (fConst9 + 1.0);
	fConst11 = (1.0 / (fConst8 * fConst10));
	fConst12 = (((fConst6 + -1.4142135623730949) / fConst5) + 1.0);
	fConst13 = (2.0 * (1.0 - (1.0 / mydsp_faustpower2_f(fConst5))));
	fConst14 = (0.0 - fConst11);
	fConst15 = ((1.0 - fConst9) / fConst10);
	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fVslider0 (*fVslider0_)
#define fVslider1 (*fVslider1_)
#define fVslider2 (*fVslider2_)
#define fVslider3 (*fVslider3_)
#define fEntry0 (*fEntry0_)
#define fCheckbox0 (*fCheckbox0_)
#define fVslider4 (*fVslider4_)
#define fVslider5 (*fVslider5_)
#define fVslider6 (*fVslider6_)
#define fEntry1 (*fEntry1_)
#define fEntry2 (*fEntry2_)
#define fVslider7 (*fVslider7_)
#define fVslider8 (*fVslider8_)
#define fVslider9 (*fVslider9_)
#define fVslider10 (*fVslider10_)
#define fVslider11 (*fVslider11_)
#define fVslider12 (*fVslider12_)
#define fVslider13 (*fVslider13_)
	double fSlow0 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * (double(fVslider0) + -10.0))));
	double fSlow1 = double(fVslider1);
	double fSlow2 = double(fVslider2);
	double fSlow3 = std::pow(10.0, (2.0 * (fSlow2 * double(fVslider3))));
	double fSlow4 = std::tan((fConst4 * double(fEntry0)));
	double fSlow5 = (1.0 / fSlow4);
	double fSlow6 = (((fSlow5 + 1.0000000000000004) / fSlow4) + 1.0);
	double fSlow7 = (1.0 / fSlow6);
	double fSlow8 = mydsp_faustpower2_f(fSlow4);
	double fSlow9 = (1.0 / fSlow8);
	double fSlow10 = (fSlow5 + 1.0);
	double fSlow11 = (0.0 - (1.0 / (fSlow4 * fSlow10)));
	int iSlow12 = int(double(fCheckbox0));
	double fSlow13 = (0.01 * double(fVslider4));
	double fSlow14 = (1.0 - double(fVslider5));
	double fSlow15 = double(fVslider6);
	int iSlow16 = int(std::min<double>(4096.0, std::max<double>(0.0, (fSlow15 + -1.0))));
	int iSlow17 = int(std::min<double>(4096.0, std::max<double>(0.0, fSlow15)));
	double fSlow18 = (1.0 / fSlow10);
	double fSlow19 = (1.0 - fSlow5);
	double fSlow20 = (((fSlow5 + -1.0000000000000004) / fSlow4) + 1.0);
	double fSlow21 = (2.0 * (1.0 - fSlow9));
	double fSlow22 = (0.0 - (2.0 / fSlow8));
	double fSlow23 = std::tan((fConst4 * double(fEntry1)));
	double fSlow24 = (1.0 / fSlow23);
	double fSlow25 = (fSlow24 + 1.0);
	double fSlow26 = (1.0 / ((fSlow25 / fSlow23) + 1.0));
	double fSlow27 = (1.0 - fSlow24);
	double fSlow28 = (1.0 - (fSlow27 / fSlow23));
	double fSlow29 = mydsp_faustpower2_f(fSlow23);
	double fSlow30 = (1.0 / fSlow29);
	double fSlow31 = (2.0 * (1.0 - fSlow30));
	double fSlow32 = std::tan((fConst4 * double(fEntry2)));
	double fSlow33 = (1.0 / fSlow32);
	double fSlow34 = (fSlow33 + 1.0);
	double fSlow35 = (1.0 / ((fSlow34 / fSlow32) + 1.0));
	double fSlow36 = (1.0 - fSlow33);
	double fSlow37 = (1.0 - (fSlow36 / fSlow32));
	double fSlow38 = mydsp_faustpower2_f(fSlow32);
	double fSlow39 = (1.0 / fSlow38);
	double fSlow40 = (2.0 * (1.0 - fSlow39));
	double fSlow41 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * (double(fVslider7) + -10.0))));
	double fSlow42 = std::pow(10.0, (2.0 * (fSlow2 * double(fVslider8))));
	double fSlow43 = (((fSlow24 + 1.0000000000000004) / fSlow23) + 1.0);
	double fSlow44 = (1.0 / fSlow43);
	double fSlow45 = (0.0 - (1.0 / (fSlow23 * fSlow25)));
	double fSlow46 = (1.0 / fSlow25);
	double fSlow47 = (1.0 / (fSlow23 * fSlow6));
	double fSlow48 = (((fSlow24 + -1.0000000000000004) / fSlow23) + 1.0);
	double fSlow49 = (0.0 - (2.0 / fSlow29));
	double fSlow50 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * (double(fVslider9) + -10.0))));
	double fSlow51 = (((fSlow33 + 1.0000000000000004) / fSlow32) + 1.0);
	double fSlow52 = (std::pow(10.0, (2.0 * (fSlow2 * double(fVslider10)))) / fSlow51);
	double fSlow53 = (0.0 - (1.0 / (fSlow32 * fSlow34)));
	double fSlow54 = (1.0 / fSlow34);
	double fSlow55 = (1.0 / (fSlow32 * fSlow43));
	double fSlow56 = (1.0 / fSlow51);
	double fSlow57 = (((fSlow33 + -1.0000000000000004) / fSlow32) + 1.0);
	double fSlow58 = (0.0 - (2.0 / fSlow38));
	double fSlow59 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * (double(fVslider11) + -10.0))));
	double fSlow60 = (std::pow(10.0, (2.0 * (fSlow2 * double(fVslider12)))) / fSlow51);
	double fSlow61 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * (double(fVslider13) + -10.0))));
	double fSlow62 = (1.0 - fSlow13);
	for (int i = 0; (i < count); i = (i + 1)) {
		iVec0[0] = 1;
		fRec1[0] = (fSlow0 + (0.999 * fRec1[1]));
		fRec8[0] = ((9.9999999999999995e-21 * double((1 - iVec0[1]))) - fRec8[1]);
		double fTemp0 = double(input0[i]);
		double fTemp1 = (fSlow13 * fTemp0);
		double fTemp2 = (fTemp1 + (fSlow14 * fRec9[1]));
		fVec1[0] = fTemp2;
		fRec9[0] = (0.5 * (fVec1[iSlow16] + fVec1[iSlow17]));
		fRec7[0] = ((fRec8[0] + (iSlow12 ? fRec9[0] : fTemp1)) - (fConst7 * ((fConst12 * fRec7[2]) + (fConst13 * fRec7[1]))));
		double fTemp3 = (fRec7[2] + (fRec7[0] + (2.0 * fRec7[1])));
		fVec2[0] = fTemp3;
		fRec6[0] = ((fConst7 * ((fConst11 * fTemp3) + (fConst14 * fVec2[1]))) - (fConst15 * fRec6[1]));
		fRec5[0] = ((fSlow11 * fRec6[1]) - (fSlow18 * ((fSlow19 * fRec5[1]) - (fSlow5 * fRec6[0]))));
		fRec4[0] = (fRec5[0] - (fSlow7 * ((fSlow20 * fRec4[2]) + (fSlow21 * fRec4[1]))));
		double fTemp4 = (fSlow31 * fRec3[1]);
		fRec3[0] = ((fSlow7 * (((fSlow9 * fRec4[0]) + (fSlow22 * fRec4[1])) + (fSlow9 * fRec4[2]))) - (fSlow26 * ((fSlow28 * fRec3[2]) + fTemp4)));
		double fTemp5 = (fSlow40 * fRec2[1]);
		fRec2[0] = ((fRec3[2] + (fSlow26 * (fTemp4 + (fSlow28 * fRec3[0])))) - (fSlow35 * ((fSlow37 * fRec2[2]) + fTemp5)));
		double fTemp6 = std::max<double>(-1.0, std::min<double>(1.0, (fSlow1 + (fSlow3 * (fRec2[2] + (fSlow35 * (fTemp5 + (fSlow37 * fRec2[0]))))))));
		fRec10[0] = (fSlow41 + (0.999 * fRec10[1]));
		fRec15[0] = (0.0 - (fSlow18 * ((fSlow19 * fRec15[1]) - (fRec6[0] + fRec6[1]))));
		fRec14[0] = (fRec15[0] - (fSlow7 * ((fSlow20 * fRec14[2]) + (fSlow21 * fRec14[1]))));
		double fTemp7 = (fRec14[2] + (fRec14[0] + (2.0 * fRec14[1])));
		double fTemp8 = (fSlow7 * fTemp7);
		fVec3[0] = fTemp8;
		fRec13[0] = ((fSlow45 * fVec3[1]) - (fSlow46 * ((fSlow27 * fRec13[1]) - (fSlow47 * fTemp7))));
		fRec12[0] = (fRec13[0] - (fSlow44 * ((fSlow48 * fRec12[2]) + (fSlow31 * fRec12[1]))));
		double fTemp9 = (fSlow40 * fRec11[1]);
		fRec11[0] = ((fSlow44 * (((fSlow30 * fRec12[0]) + (fSlow49 * fRec12[1])) + (fSlow30 * fRec12[2]))) - (fSlow35 * ((fSlow37 * fRec11[2]) + fTemp9)));
		double fTemp10 = std::max<double>(-1.0, std::min<double>(1.0, (fSlow1 + (fSlow42 * (fRec11[2] + (fSlow35 * (fTemp9 + (fSlow37 * fRec11[0]))))))));
		fRec16[0] = (fSlow50 + (0.999 * fRec16[1]));
		fRec20[0] = (0.0 - (fSlow46 * ((fSlow27 * fRec20[1]) - (fTemp8 + fVec3[1]))));
		fRec19[0] = (fRec20[0] - (fSlow44 * ((fSlow48 * fRec19[2]) + (fSlow31 * fRec19[1]))));
		double fTemp11 = (fRec19[2] + (fRec19[0] + (2.0 * fRec19[1])));
		double fTemp12 = (fSlow44 * fTemp11);
		fVec4[0] = fTemp12;
		fRec18[0] = ((fSlow53 * fVec4[1]) - (fSlow54 * ((fSlow36 * fRec18[1]) - (fSlow55 * fTemp11))));
		fRec17[0] = (fRec18[0] - (fSlow56 * ((fSlow57 * fRec17[2]) + (fSlow40 * fRec17[1]))));
		double fTemp13 = std::max<double>(-1.0, std::min<double>(1.0, (fSlow1 + (fSlow52 * (((fSlow39 * fRec17[0]) + (fSlow58 * fRec17[1])) + (fSlow39 * fRec17[2]))))));
		fRec21[0] = (fSlow59 + (0.999 * fRec21[1]));
		fRec23[0] = (0.0 - (fSlow54 * ((fSlow36 * fRec23[1]) - (fTemp12 + fVec4[1]))));
		fRec22[0] = (fRec23[0] - (fSlow56 * ((fSlow57 * fRec22[2]) + (fSlow40 * fRec22[1]))));
		double fTemp14 = std::max<double>(-1.0, std::min<double>(1.0, (fSlow1 + (fSlow60 * (fRec22[2] + (fRec22[0] + (2.0 * fRec22[1])))))));
		double fTemp15 = (((((fRec1[0] * fTemp6) * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp6)))) + ((fRec10[0] * fTemp10) * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp10))))) + ((fRec16[0] * fTemp13) * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp13))))) + ((fRec21[0] * fTemp14) * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp14)))));
		fVec5[0] = fTemp15;
		fRec0[0] = (0.0 - (fConst2 * ((fConst3 * fRec0[1]) - (fTemp15 + fVec5[1]))));
		fRec24[0] = (fSlow61 + (0.999 * fRec24[1]));
		output0[i] = FAUSTFLOAT(((fRec0[0] * fRec24[0]) + (fSlow62 * fTemp0)));
		iVec0[1] = iVec0[0];
		fRec1[1] = fRec1[0];
		fRec8[1] = fRec8[0];
		fVec1[1] = fVec1[0];
		fRec9[1] = fRec9[0];
		fRec7[2] = fRec7[1];
		fRec7[1] = fRec7[0];
		fVec2[1] = fVec2[0];
		fRec6[1] = fRec6[0];
		fRec5[1] = fRec5[0];
		fRec4[2] = fRec4[1];
		fRec4[1] = fRec4[0];
		fRec3[2] = fRec3[1];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fRec10[1] = fRec10[0];
		fRec15[1] = fRec15[0];
		fRec14[2] = fRec14[1];
		fRec14[1] = fRec14[0];
		fVec3[1] = fVec3[0];
		fRec13[1] = fRec13[0];
		fRec12[2] = fRec12[1];
		fRec12[1] = fRec12[0];
		fRec11[2] = fRec11[1];
		fRec11[1] = fRec11[0];
		fRec16[1] = fRec16[0];
		fRec20[1] = fRec20[0];
		fRec19[2] = fRec19[1];
		fRec19[1] = fRec19[0];
		fVec4[1] = fVec4[0];
		fRec18[1] = fRec18[0];
		fRec17[2] = fRec17[1];
		fRec17[1] = fRec17[0];
		fRec21[1] = fRec21[0];
		fRec23[1] = fRec23[0];
		fRec22[2] = fRec22[1];
		fRec22[1] = fRec22[0];
		fVec5[1] = fVec5[0];
		fRec0[1] = fRec0[0];
		fRec24[1] = fRec24[0];
	}
#undef fVslider0
#undef fVslider1
#undef fVslider2
#undef fVslider3
#undef fEntry0
#undef fCheckbox0
#undef fVslider4
#undef fVslider5
#undef fVslider6
#undef fEntry1
#undef fEntry2
#undef fVslider7
#undef fVslider8
#undef fVslider9
#undef fVslider10
#undef fVslider11
#undef fVslider12
#undef fVslider13
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
		fVslider2_ = (float*)data; // , 0.64000000000000001, 0.0, 1.0, 0.01 
		break;
	case GAIN: 
		fVslider13_ = (float*)data; // , 2.0, -10.0, 10.0, 0.10000000000000001 
		break;
	case HIGH_DRIVE: 
		fVslider3_ = (float*)data; // , 1.0, 0.0, 1.0, 0.01 
		break;
	case HIGH_GAIN: 
		fVslider0_ = (float*)data; // , 10.0, -10.0, 20.0, 0.10000000000000001 
		break;
	case LEVEL: 
		fVslider1_ = (float*)data; // , 0.0, 0.0, 0.5, 0.01 
		break;
	case LOW_DRIVE: 
		fVslider12_ = (float*)data; // , 1.0, 0.0, 1.0, 0.01 
		break;
	case LOW_GAIN: 
		fVslider11_ = (float*)data; // , 10.0, -10.0, 20.0, 0.10000000000000001 
		break;
	case MIDDLE_H_DRIVE: 
		fVslider8_ = (float*)data; // , 1.0, 0.0, 1.0, 0.01 
		break;
	case MIDDLE_H_GAIN: 
		fVslider7_ = (float*)data; // , 10.0, -10.0, 20.0, 0.10000000000000001 
		break;
	case MIDDLE_L_DRIVE: 
		fVslider10_ = (float*)data; // , 1.0, 0.0, 1.0, 0.01 
		break;
	case MIDDLE_L_GAIN: 
		fVslider9_ = (float*)data; // , 10.0, -10.0, 20.0, 0.10000000000000001 
		break;
	case ON_OFF: 
		fCheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case SPLIT_HIGH_FREQ: 
		fEntry0_ = (float*)data; // , 1250.0, 1250.0, 12000.0, 10.0 
		break;
	case SPLIT_LOW_FREQ: 
		fEntry2_ = (float*)data; // , 250.0, 20.0, 600.0, 10.0 
		break;
	case SPLIT_MIDDLE_FREQ: 
		fEntry1_ = (float*)data; // , 650.0, 600.0, 1250.0, 10.0 
		break;
	case TRIGGER: 
		fVslider5_ = (float*)data; // , 0.12, 0.0, 1.0, 0.01 
		break;
	case VIBRATO: 
		fVslider6_ = (float*)data; // , 1.0, 0.0, 1.0, 0.01 
		break;
	case WET_DRY: 
		fVslider4_ = (float*)data; // , 100.0, 0.0, 100.0, 1.0 
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
   HIGH_DRIVE, 
   HIGH_GAIN, 
   LEVEL, 
   LOW_DRIVE, 
   LOW_GAIN, 
   MIDDLE_H_DRIVE, 
   MIDDLE_H_GAIN, 
   MIDDLE_L_DRIVE, 
   MIDDLE_L_GAIN, 
   ON_OFF, 
   SPLIT_HIGH_FREQ, 
   SPLIT_LOW_FREQ, 
   SPLIT_MIDDLE_FREQ, 
   TRIGGER, 
   VIBRATO, 
   WET_DRY, 
} PortIndex;
*/

} // end namespace gx_distortion
