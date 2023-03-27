// generated from file '../src/LV2/faust/gx_distortion.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace gx_distortion {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	int iVec0[2];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec0[2];
	FAUSTFLOAT fEntry0;
	FAUSTFLOAT	*fEntry0_;
	double fConst1;
	FAUSTFLOAT fEntry1;
	FAUSTFLOAT	*fEntry1_;
	FAUSTFLOAT fEntry2;
	FAUSTFLOAT	*fEntry2_;
	double fConst5;
	double fConst7;
	double fConst9;
	double fConst10;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT	*fCheckbox0_;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fVec1[2];
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fRec10[2];
	double fRec11[2];
	double fRec9[3];
	double fVec2[2];
	double fConst11;
	double fConst12;
	double fRec8[2];
	double fRec7[2];
	double fRec6[3];
	double fVec3[2];
	double fRec5[2];
	double fRec4[3];
	double fVec4[2];
	double fRec3[2];
	double fRec2[3];
	FAUSTFLOAT fVslider4;
	FAUSTFLOAT	*fVslider4_;
	FAUSTFLOAT fVslider5;
	FAUSTFLOAT	*fVslider5_;
	FAUSTFLOAT fVslider6;
	FAUSTFLOAT	*fVslider6_;
	FAUSTFLOAT fVslider7;
	FAUSTFLOAT	*fVslider7_;
	double fRec12[2];
	double fRec14[2];
	double fRec13[3];
	FAUSTFLOAT fVslider8;
	FAUSTFLOAT	*fVslider8_;
	FAUSTFLOAT fVslider9;
	FAUSTFLOAT	*fVslider9_;
	double fRec15[2];
	double fRec18[2];
	double fRec17[3];
	double fRec16[3];
	FAUSTFLOAT fVslider10;
	FAUSTFLOAT	*fVslider10_;
	FAUSTFLOAT fVslider11;
	FAUSTFLOAT	*fVslider11_;
	double fRec19[2];
	double fRec23[2];
	double fRec22[3];
	double fRec21[3];
	double fRec20[3];
	FAUSTFLOAT fVslider12;
	FAUSTFLOAT	*fVslider12_;
	FAUSTFLOAT fVslider13;
	FAUSTFLOAT	*fVslider13_;
	double fRec24[2];
	double fVec5[2];
	double fConst14;
	double fConst15;
	double fRec1[2];

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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) iVec0[l0] = 0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec0[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fVec1[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec10[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fRec11[l4] = 0.0;
	for (int l5 = 0; l5 < 3; l5 = l5 + 1) fRec9[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fVec2[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec8[l7] = 0.0;
	for (int l8 = 0; l8 < 2; l8 = l8 + 1) fRec7[l8] = 0.0;
	for (int l9 = 0; l9 < 3; l9 = l9 + 1) fRec6[l9] = 0.0;
	for (int l10 = 0; l10 < 2; l10 = l10 + 1) fVec3[l10] = 0.0;
	for (int l11 = 0; l11 < 2; l11 = l11 + 1) fRec5[l11] = 0.0;
	for (int l12 = 0; l12 < 3; l12 = l12 + 1) fRec4[l12] = 0.0;
	for (int l13 = 0; l13 < 2; l13 = l13 + 1) fVec4[l13] = 0.0;
	for (int l14 = 0; l14 < 2; l14 = l14 + 1) fRec3[l14] = 0.0;
	for (int l15 = 0; l15 < 3; l15 = l15 + 1) fRec2[l15] = 0.0;
	for (int l16 = 0; l16 < 2; l16 = l16 + 1) fRec12[l16] = 0.0;
	for (int l17 = 0; l17 < 2; l17 = l17 + 1) fRec14[l17] = 0.0;
	for (int l18 = 0; l18 < 3; l18 = l18 + 1) fRec13[l18] = 0.0;
	for (int l19 = 0; l19 < 2; l19 = l19 + 1) fRec15[l19] = 0.0;
	for (int l20 = 0; l20 < 2; l20 = l20 + 1) fRec18[l20] = 0.0;
	for (int l21 = 0; l21 < 3; l21 = l21 + 1) fRec17[l21] = 0.0;
	for (int l22 = 0; l22 < 3; l22 = l22 + 1) fRec16[l22] = 0.0;
	for (int l23 = 0; l23 < 2; l23 = l23 + 1) fRec19[l23] = 0.0;
	for (int l24 = 0; l24 < 2; l24 = l24 + 1) fRec23[l24] = 0.0;
	for (int l25 = 0; l25 < 3; l25 = l25 + 1) fRec22[l25] = 0.0;
	for (int l26 = 0; l26 < 3; l26 = l26 + 1) fRec21[l26] = 0.0;
	for (int l27 = 0; l27 < 3; l27 = l27 + 1) fRec20[l27] = 0.0;
	for (int l28 = 0; l28 < 2; l28 = l28 + 1) fRec24[l28] = 0.0;
	for (int l29 = 0; l29 < 2; l29 = l29 + 1) fVec5[l29] = 0.0;
	for (int l30 = 0; l30 < 2; l30 = l30 + 1) fRec1[l30] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = 3.141592653589793 / fConst0;
	double fConst2 = std::tan(97.38937226128358 / fConst0);
	double fConst3 = 1.0 / fConst2;
	double fConst4 = fConst3 + 1.0;
	fConst5 = (1.0 - fConst3) / fConst4;
	double fConst6 = std::tan(47123.8898038469 / fConst0);
	fConst7 = 2.0 * (1.0 - 1.0 / mydsp_faustpower2_f(fConst6));
	double fConst8 = 1.0 / fConst6;
	fConst9 = (fConst8 + -1.414213562373095) / fConst6 + 1.0;
	fConst10 = 1.0 / ((fConst8 + 1.414213562373095) / fConst6 + 1.0);
	fConst11 = 1.0 / (fConst2 * fConst4);
	fConst12 = 0.0 - fConst11;
	double fConst13 = 1.0 / std::tan(20517.741620594938 / fConst0);
	fConst14 = 1.0 - fConst13;
	fConst15 = 1.0 / (fConst13 + 1.0);
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
#define fEntry0 (*fEntry0_)
#define fEntry1 (*fEntry1_)
#define fEntry2 (*fEntry2_)
#define fCheckbox0 (*fCheckbox0_)
#define fVslider2 (*fVslider2_)
#define fVslider3 (*fVslider3_)
#define fVslider4 (*fVslider4_)
#define fVslider5 (*fVslider5_)
#define fVslider6 (*fVslider6_)
#define fVslider7 (*fVslider7_)
#define fVslider8 (*fVslider8_)
#define fVslider9 (*fVslider9_)
#define fVslider10 (*fVslider10_)
#define fVslider11 (*fVslider11_)
#define fVslider12 (*fVslider12_)
#define fVslider13 (*fVslider13_)
	double fSlow0 = 0.01 * double(fVslider0);
	double fSlow1 = 1.0 - fSlow0;
	double fSlow2 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * (double(fVslider1) + -1e+01));
	double fSlow3 = std::tan(fConst1 * double(fEntry0));
	double fSlow4 = mydsp_faustpower2_f(fSlow3);
	double fSlow5 = 1.0 / fSlow4;
	double fSlow6 = 2.0 * (1.0 - fSlow5);
	double fSlow7 = 1.0 / fSlow3;
	double fSlow8 = (fSlow7 + -1.0000000000000004) / fSlow3 + 1.0;
	double fSlow9 = (fSlow7 + 1.0000000000000004) / fSlow3 + 1.0;
	double fSlow10 = 1.0 / fSlow9;
	double fSlow11 = std::tan(fConst1 * double(fEntry1));
	double fSlow12 = mydsp_faustpower2_f(fSlow11);
	double fSlow13 = 1.0 / fSlow12;
	double fSlow14 = 2.0 * (1.0 - fSlow13);
	double fSlow15 = 1.0 / fSlow11;
	double fSlow16 = (fSlow15 + -1.0000000000000004) / fSlow11 + 1.0;
	double fSlow17 = (fSlow15 + 1.0000000000000004) / fSlow11 + 1.0;
	double fSlow18 = 1.0 / fSlow17;
	double fSlow19 = std::tan(fConst1 * double(fEntry2));
	double fSlow20 = mydsp_faustpower2_f(fSlow19);
	double fSlow21 = 1.0 / fSlow20;
	double fSlow22 = 2.0 * (1.0 - fSlow21);
	double fSlow23 = 1.0 / fSlow19;
	double fSlow24 = (fSlow23 + -1.0000000000000004) / fSlow19 + 1.0;
	double fSlow25 = (fSlow23 + 1.0000000000000004) / fSlow19 + 1.0;
	double fSlow26 = 1.0 / fSlow25;
	int iSlow27 = int(double(fCheckbox0));
	double fSlow28 = 1.0 - double(fVslider2);
	double fSlow29 = double(fVslider3);
	int iSlow30 = int(std::min<double>(4096.0, std::max<double>(0.0, fSlow29)));
	int iSlow31 = int(std::min<double>(4096.0, std::max<double>(0.0, fSlow29 + -1.0)));
	double fSlow32 = 1.0 - fSlow23;
	double fSlow33 = fSlow23 + 1.0;
	double fSlow34 = 1.0 / fSlow33;
	double fSlow35 = 1.0 - fSlow15;
	double fSlow36 = fSlow15 + 1.0;
	double fSlow37 = 1.0 / fSlow36;
	double fSlow38 = 1.0 - fSlow7;
	double fSlow39 = fSlow7 + 1.0;
	double fSlow40 = 1.0 / fSlow39;
	double fSlow41 = double(fVslider5);
	double fSlow42 = std::pow(1e+01, 2.0 * fSlow41 * double(fVslider4)) / fSlow9;
	double fSlow43 = double(fVslider6);
	double fSlow44 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * (double(fVslider7) + -1e+01));
	double fSlow45 = 1.0 / (fSlow3 * fSlow17);
	double fSlow46 = 0.0 - 1.0 / (fSlow3 * fSlow39);
	double fSlow47 = 0.0 - 2.0 / fSlow4;
	double fSlow48 = std::pow(1e+01, 2.0 * fSlow41 * double(fVslider8)) / fSlow9;
	double fSlow49 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * (double(fVslider9) + -1e+01));
	double fSlow50 = 1.0 - fSlow38 / fSlow3;
	double fSlow51 = 1.0 / (fSlow39 / fSlow3 + 1.0);
	double fSlow52 = 1.0 / (fSlow25 * fSlow11);
	double fSlow53 = 0.0 - 1.0 / (fSlow11 * fSlow36);
	double fSlow54 = 0.0 - 2.0 / fSlow12;
	double fSlow55 = std::pow(1e+01, 2.0 * fSlow41 * double(fVslider10));
	double fSlow56 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * (double(fVslider11) + -1e+01));
	double fSlow57 = 1.0 - fSlow35 / fSlow11;
	double fSlow58 = 1.0 / (fSlow36 / fSlow11 + 1.0);
	double fSlow59 = 0.0 - 1.0 / (fSlow19 * fSlow33);
	double fSlow60 = 0.0 - 2.0 / fSlow20;
	double fSlow61 = std::pow(1e+01, 2.0 * fSlow41 * double(fVslider12));
	double fSlow62 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * (double(fVslider13) + -1e+01));
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		double fTemp0 = double(input0[i0]);
		iVec0[0] = 1;
		fRec0[0] = fSlow2 + 0.999 * fRec0[1];
		double fTemp1 = fSlow0 * fTemp0;
		double fTemp2 = fTemp1 + fSlow28 * fRec10[1];
		fVec1[0] = fTemp2;
		fRec10[0] = 0.5 * (fVec1[iSlow31] + fVec1[iSlow30]);
		fRec11[0] = 1e-20 * double(1 - iVec0[1]) - fRec11[1];
		fRec9[0] = fRec11[0] + ((iSlow27) ? fRec10[0] : fTemp1) - fConst10 * (fConst9 * fRec9[2] + fConst7 * fRec9[1]);
		double fTemp3 = fRec9[2] + fRec9[0] + 2.0 * fRec9[1];
		fVec2[0] = fTemp3;
		fRec8[0] = fConst10 * (fConst11 * fTemp3 + fConst12 * fVec2[1]) - fConst5 * fRec8[1];
		fRec7[0] = 0.0 - fSlow34 * (fSlow32 * fRec7[1] - (fRec8[0] + fRec8[1]));
		fRec6[0] = fRec7[0] - fSlow26 * (fSlow24 * fRec6[2] + fSlow22 * fRec6[1]);
		double fTemp4 = fRec6[2] + fRec6[0] + 2.0 * fRec6[1];
		double fTemp5 = fSlow26 * fTemp4;
		fVec3[0] = fTemp5;
		fRec5[0] = 0.0 - fSlow37 * (fSlow35 * fRec5[1] - (fTemp5 + fVec3[1]));
		fRec4[0] = fRec5[0] - fSlow18 * (fSlow16 * fRec4[2] + fSlow14 * fRec4[1]);
		double fTemp6 = fRec4[2] + fRec4[0] + 2.0 * fRec4[1];
		double fTemp7 = fSlow18 * fTemp6;
		fVec4[0] = fTemp7;
		fRec3[0] = 0.0 - fSlow40 * (fSlow38 * fRec3[1] - (fTemp7 + fVec4[1]));
		fRec2[0] = fRec3[0] - fSlow10 * (fSlow8 * fRec2[2] + fSlow6 * fRec2[1]);
		double fTemp8 = std::max<double>(-1.0, std::min<double>(1.0, fSlow43 + fSlow42 * (fRec2[2] + fRec2[0] + 2.0 * fRec2[1])));
		fRec12[0] = fSlow44 + 0.999 * fRec12[1];
		fRec14[0] = fSlow46 * fVec4[1] - fSlow40 * (fSlow38 * fRec14[1] - fSlow45 * fTemp6);
		fRec13[0] = fRec14[0] - fSlow10 * (fSlow8 * fRec13[2] + fSlow6 * fRec13[1]);
		double fTemp9 = std::max<double>(-1.0, std::min<double>(1.0, fSlow43 + fSlow48 * (fSlow5 * fRec13[0] + fSlow47 * fRec13[1] + fSlow5 * fRec13[2])));
		fRec15[0] = fSlow49 + 0.999 * fRec15[1];
		double fTemp10 = fSlow6 * fRec16[1];
		fRec18[0] = fSlow53 * fVec3[1] - fSlow37 * (fSlow35 * fRec18[1] - fSlow52 * fTemp4);
		fRec17[0] = fRec18[0] - fSlow18 * (fSlow16 * fRec17[2] + fSlow14 * fRec17[1]);
		fRec16[0] = fSlow18 * (fSlow13 * fRec17[0] + fSlow54 * fRec17[1] + fSlow13 * fRec17[2]) - fSlow51 * (fSlow50 * fRec16[2] + fTemp10);
		double fTemp11 = std::max<double>(-1.0, std::min<double>(1.0, fSlow43 + fSlow55 * (fRec16[2] + fSlow51 * (fTemp10 + fSlow50 * fRec16[0]))));
		fRec19[0] = fSlow56 + 0.999 * fRec19[1];
		double fTemp12 = fSlow6 * fRec20[1];
		double fTemp13 = fSlow14 * fRec21[1];
		fRec23[0] = fSlow59 * fRec8[1] - fSlow34 * (fSlow32 * fRec23[1] - fSlow23 * fRec8[0]);
		fRec22[0] = fRec23[0] - fSlow26 * (fSlow24 * fRec22[2] + fSlow22 * fRec22[1]);
		fRec21[0] = fSlow26 * (fSlow21 * fRec22[0] + fSlow60 * fRec22[1] + fSlow21 * fRec22[2]) - fSlow58 * (fSlow57 * fRec21[2] + fTemp13);
		fRec20[0] = fRec21[2] + fSlow58 * (fTemp13 + fSlow57 * fRec21[0]) - fSlow51 * (fSlow50 * fRec20[2] + fTemp12);
		double fTemp14 = std::max<double>(-1.0, std::min<double>(1.0, fSlow43 + fSlow61 * (fRec20[2] + fSlow51 * (fTemp12 + fSlow50 * fRec20[0]))));
		fRec24[0] = fSlow62 + 0.999 * fRec24[1];
		double fTemp15 = fRec24[0] * fTemp14 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp14)) + fRec19[0] * fTemp11 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp11)) + fRec15[0] * fTemp9 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp9)) + fRec12[0] * fTemp8 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp8));
		fVec5[0] = fTemp15;
		fRec1[0] = 0.0 - fConst15 * (fConst14 * fRec1[1] - (fTemp15 + fVec5[1]));
		output0[i0] = FAUSTFLOAT(fRec1[0] * fRec0[0] + fSlow1 * fTemp0);
		iVec0[1] = iVec0[0];
		fRec0[1] = fRec0[0];
		fVec1[1] = fVec1[0];
		fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		fRec9[2] = fRec9[1];
		fRec9[1] = fRec9[0];
		fVec2[1] = fVec2[0];
		fRec8[1] = fRec8[0];
		fRec7[1] = fRec7[0];
		fRec6[2] = fRec6[1];
		fRec6[1] = fRec6[0];
		fVec3[1] = fVec3[0];
		fRec5[1] = fRec5[0];
		fRec4[2] = fRec4[1];
		fRec4[1] = fRec4[0];
		fVec4[1] = fVec4[0];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fRec12[1] = fRec12[0];
		fRec14[1] = fRec14[0];
		fRec13[2] = fRec13[1];
		fRec13[1] = fRec13[0];
		fRec15[1] = fRec15[0];
		fRec18[1] = fRec18[0];
		fRec17[2] = fRec17[1];
		fRec17[1] = fRec17[0];
		fRec16[2] = fRec16[1];
		fRec16[1] = fRec16[0];
		fRec19[1] = fRec19[0];
		fRec23[1] = fRec23[0];
		fRec22[2] = fRec22[1];
		fRec22[1] = fRec22[0];
		fRec21[2] = fRec21[1];
		fRec21[1] = fRec21[0];
		fRec20[2] = fRec20[1];
		fRec20[1] = fRec20[0];
		fRec24[1] = fRec24[0];
		fVec5[1] = fVec5[0];
		fRec1[1] = fRec1[0];
	}
#undef fVslider0
#undef fVslider1
#undef fEntry0
#undef fEntry1
#undef fEntry2
#undef fCheckbox0
#undef fVslider2
#undef fVslider3
#undef fVslider4
#undef fVslider5
#undef fVslider6
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
	case ON_OFF: 
		fCheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case DRIVE: 
		fVslider5_ = (float*)data; // , 0.64, 0.0, 1.0, 0.01 
		break;
	case GAIN: 
		fVslider1_ = (float*)data; // , 2.0, -1e+01, 1e+01, 0.1 
		break;
	case HIGH_DRIVE: 
		fVslider12_ = (float*)data; // , 1.0, 0.0, 1.0, 0.01 
		break;
	case HIGH_GAIN: 
		fVslider13_ = (float*)data; // , 1e+01, -1e+01, 2e+01, 0.1 
		break;
	case LEVEL: 
		fVslider6_ = (float*)data; // , 0.0, 0.0, 0.5, 0.01 
		break;
	case LOW_DRIVE: 
		fVslider4_ = (float*)data; // , 1.0, 0.0, 1.0, 0.01 
		break;
	case LOW_GAIN: 
		fVslider7_ = (float*)data; // , 1e+01, -1e+01, 2e+01, 0.1 
		break;
	case MIDDLE_H_DRIVE: 
		fVslider10_ = (float*)data; // , 1.0, 0.0, 1.0, 0.01 
		break;
	case MIDDLE_H_GAIN: 
		fVslider11_ = (float*)data; // , 1e+01, -1e+01, 2e+01, 0.1 
		break;
	case MIDDLE_L_DRIVE: 
		fVslider8_ = (float*)data; // , 1.0, 0.0, 1.0, 0.01 
		break;
	case MIDDLE_L_GAIN: 
		fVslider9_ = (float*)data; // , 1e+01, -1e+01, 2e+01, 0.1 
		break;
	case TRIGGER: 
		fVslider2_ = (float*)data; // , 0.12, 0.0, 1.0, 0.01 
		break;
	case VIBRATO: 
		fVslider3_ = (float*)data; // , 1.0, 0.0, 1.0, 0.01 
		break;
	case WET_DRY: 
		fVslider0_ = (float*)data; // , 1e+02, 0.0, 1e+02, 1.0 
		break;
	case SPLIT_HIGH_FREQ: 
		fEntry2_ = (float*)data; // , 1.25e+03, 1.25e+03, 1.2e+04, 1e+01 
		break;
	case SPLIT_LOW_FREQ: 
		fEntry0_ = (float*)data; // , 2.5e+02, 2e+01, 6e+02, 1e+01 
		break;
	case SPLIT_MIDDLE_FREQ: 
		fEntry1_ = (float*)data; // , 6.5e+02, 6e+02, 1.25e+03, 1e+01 
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
