// generated from file '../src/LV2/faust/mbd.dsp' by dsp2cc:
// Code generated with Faust 0.9.58 (http://faust.grame.fr)


namespace mbd {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	int 	iVec0[2];
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec0[2];
	int 	iConst0;
	double 	fConst1;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fConst2;
	double 	fRec8[2];
	double 	fVec1[2];
	double 	fRec7[2];
	double 	fRec6[3];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fVec2[2];
	double 	fRec5[2];
	double 	fRec1[2];
	int 	iRec2[2];
	double 	fRec3[2];
	FAUSTFLOAT 	fbargraph0;
	FAUSTFLOAT	*fbargraph0_;
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT	*fslider4_;
	double 	fRec17[2];
	double 	fRec16[3];
	double 	fVec3[2];
	double 	fRec15[2];
	double 	fRec14[3];
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT	*fslider5_;
	FAUSTFLOAT 	fslider6;
	FAUSTFLOAT	*fslider6_;
	double 	fVec4[2];
	double 	fRec13[2];
	double 	fRec9[2];
	int 	iRec10[2];
	double 	fRec11[2];
	FAUSTFLOAT 	fbargraph1;
	FAUSTFLOAT	*fbargraph1_;
	FAUSTFLOAT 	fslider7;
	FAUSTFLOAT	*fslider7_;
	double 	fRec26[2];
	double 	fRec25[3];
	double 	fVec5[2];
	double 	fRec24[2];
	double 	fRec23[3];
	FAUSTFLOAT 	fslider8;
	FAUSTFLOAT	*fslider8_;
	FAUSTFLOAT 	fslider9;
	FAUSTFLOAT	*fslider9_;
	double 	fVec6[2];
	double 	fRec22[2];
	double 	fRec18[2];
	int 	iRec19[2];
	double 	fRec20[2];
	FAUSTFLOAT 	fbargraph2;
	FAUSTFLOAT	*fbargraph2_;
	FAUSTFLOAT 	fslider10;
	FAUSTFLOAT	*fslider10_;
	double 	fRec35[2];
	double 	fRec34[3];
	double 	fVec7[2];
	double 	fRec33[2];
	double 	fRec32[3];
	FAUSTFLOAT 	fslider11;
	FAUSTFLOAT	*fslider11_;
	FAUSTFLOAT 	fslider12;
	FAUSTFLOAT	*fslider12_;
	double 	fVec8[2];
	double 	fRec31[2];
	double 	fRec27[2];
	int 	iRec28[2];
	double 	fRec29[2];
	FAUSTFLOAT 	fbargraph3;
	FAUSTFLOAT	*fbargraph3_;
	double 	fRec42[2];
	double 	fRec41[3];
	FAUSTFLOAT 	fslider13;
	FAUSTFLOAT	*fslider13_;
	FAUSTFLOAT 	fslider14;
	FAUSTFLOAT	*fslider14_;
	double 	fVec9[2];
	double 	fRec40[2];
	double 	fRec36[2];
	int 	iRec37[2];
	double 	fRec38[2];
	FAUSTFLOAT 	fbargraph4;
	FAUSTFLOAT	*fbargraph4_;
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
	id = "mbd";
	name = N_("MultiBand Distortion");
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
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) iRec2[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<3; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<3; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) iRec10[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<3; i++) fRec25[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<3; i++) fRec23[i] = 0;
	for (int i=0; i<2; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) iRec19[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec35[i] = 0;
	for (int i=0; i<3; i++) fRec34[i] = 0;
	for (int i=0; i<2; i++) fVec7[i] = 0;
	for (int i=0; i<2; i++) fRec33[i] = 0;
	for (int i=0; i<3; i++) fRec32[i] = 0;
	for (int i=0; i<2; i++) fVec8[i] = 0;
	for (int i=0; i<2; i++) fRec31[i] = 0;
	for (int i=0; i<2; i++) fRec27[i] = 0;
	for (int i=0; i<2; i++) iRec28[i] = 0;
	for (int i=0; i<2; i++) fRec29[i] = 0;
	for (int i=0; i<2; i++) fRec42[i] = 0;
	for (int i=0; i<3; i++) fRec41[i] = 0;
	for (int i=0; i<2; i++) fVec9[i] = 0;
	for (int i=0; i<2; i++) fRec40[i] = 0;
	for (int i=0; i<2; i++) fRec36[i] = 0;
	for (int i=0; i<2; i++) iRec37[i] = 0;
	for (int i=0; i<2; i++) fRec38[i] = 0;
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
	fConst2 = (3.141592653589793 / double(iConst0));
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
#define fslider2 (*fslider2_)
#define fslider3 (*fslider3_)
#define fbargraph0 (*fbargraph0_)
#define fslider4 (*fslider4_)
#define fslider5 (*fslider5_)
#define fslider6 (*fslider6_)
#define fbargraph1 (*fbargraph1_)
#define fslider7 (*fslider7_)
#define fslider8 (*fslider8_)
#define fslider9 (*fslider9_)
#define fbargraph2 (*fbargraph2_)
#define fslider10 (*fslider10_)
#define fslider11 (*fslider11_)
#define fslider12 (*fslider12_)
#define fbargraph3 (*fbargraph3_)
#define fslider13 (*fslider13_)
#define fslider14 (*fslider14_)
#define fbargraph4 (*fbargraph4_)
	double 	fSlow0 = (0.0010000000000000009 * pow(10,(0.05 * fslider0)));
	double 	fSlow1 = tan((fConst2 * fslider1));
	double 	fSlow2 = (1.0 / faustpower<2>(fSlow1));
	double 	fSlow3 = (2 * (1 - fSlow2));
	double 	fSlow4 = (1.0 / fSlow1);
	double 	fSlow5 = (1 + ((fSlow4 - 1.0000000000000004) / fSlow1));
	double 	fSlow6 = (1 + ((1.0000000000000004 + fSlow4) / fSlow1));
	double 	fSlow7 = (1.0 / fSlow6);
	double 	fSlow8 = (1 + fSlow4);
	double 	fSlow9 = (0 - ((1 - fSlow4) / fSlow8));
	double 	fSlow10 = (0 - fSlow4);
	double 	fSlow11 = (1.0 / fSlow8);
	double 	fSlow12 = (2 * (0 - fSlow2));
	double 	fSlow13 = (pow(1e+01,(2 * fslider2)) / fSlow6);
	double 	fSlow14 = fslider3;
	double 	fSlow15 = tan((fConst2 * fslider4));
	double 	fSlow16 = (1.0 / faustpower<2>(fSlow15));
	double 	fSlow17 = (2 * (1 - fSlow16));
	double 	fSlow18 = (1.0 / fSlow15);
	double 	fSlow19 = (1 + ((fSlow18 - 1.0000000000000004) / fSlow15));
	double 	fSlow20 = (1 + ((1.0000000000000004 + fSlow18) / fSlow15));
	double 	fSlow21 = (1.0 / fSlow20);
	double 	fSlow22 = (1 + fSlow18);
	double 	fSlow23 = (0 - ((1 - fSlow18) / fSlow22));
	double 	fSlow24 = (1.0 / (fSlow6 * fSlow15));
	double 	fSlow25 = (0 - fSlow18);
	double 	fSlow26 = (1.0 / fSlow22);
	double 	fSlow27 = (2 * (0 - fSlow16));
	double 	fSlow28 = (pow(1e+01,(2 * fslider5)) / fSlow20);
	double 	fSlow29 = fslider6;
	double 	fSlow30 = tan((fConst2 * fslider7));
	double 	fSlow31 = (1.0 / faustpower<2>(fSlow30));
	double 	fSlow32 = (2 * (1 - fSlow31));
	double 	fSlow33 = (1.0 / fSlow30);
	double 	fSlow34 = (1 + ((fSlow33 - 1.0000000000000004) / fSlow30));
	double 	fSlow35 = (1 + ((1.0000000000000004 + fSlow33) / fSlow30));
	double 	fSlow36 = (1.0 / fSlow35);
	double 	fSlow37 = (1 + fSlow33);
	double 	fSlow38 = (0 - ((1 - fSlow33) / fSlow37));
	double 	fSlow39 = (1.0 / (fSlow20 * fSlow30));
	double 	fSlow40 = (0 - fSlow33);
	double 	fSlow41 = (1.0 / fSlow37);
	double 	fSlow42 = (2 * (0 - fSlow31));
	double 	fSlow43 = (pow(1e+01,(2 * fslider8)) / fSlow35);
	double 	fSlow44 = fslider9;
	double 	fSlow45 = tan((fConst2 * fslider10));
	double 	fSlow46 = (1.0 / faustpower<2>(fSlow45));
	double 	fSlow47 = (2 * (1 - fSlow46));
	double 	fSlow48 = (1.0 / fSlow45);
	double 	fSlow49 = (1 + ((fSlow48 - 1.0000000000000004) / fSlow45));
	double 	fSlow50 = (1 + ((1.0000000000000004 + fSlow48) / fSlow45));
	double 	fSlow51 = (1.0 / fSlow50);
	double 	fSlow52 = (1 + fSlow48);
	double 	fSlow53 = (0 - ((1 - fSlow48) / fSlow52));
	double 	fSlow54 = (1.0 / (fSlow35 * fSlow45));
	double 	fSlow55 = (0 - fSlow48);
	double 	fSlow56 = (1.0 / fSlow52);
	double 	fSlow57 = (2 * (0 - fSlow46));
	double 	fSlow58 = (pow(1e+01,(2 * fslider11)) / fSlow50);
	double 	fSlow59 = fslider12;
	double 	fSlow60 = (pow(1e+01,(2 * fslider13)) / fSlow50);
	double 	fSlow61 = fslider14;
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		fRec0[0] = (fSlow0 + (0.999 * fRec0[1]));
		fRec8[0] = ((1e-20 * (1 - iVec0[1])) - fRec8[1]);
		double fTemp0 = ((double)input0[i] + fRec8[0]);
		fVec1[0] = fTemp0;
		fRec7[0] = ((fSlow11 * ((fSlow10 * fVec1[1]) + (fSlow4 * fVec1[0]))) + (fSlow9 * fRec7[1]));
		fRec6[0] = (fRec7[0] - (fSlow7 * ((fSlow5 * fRec6[2]) + (fSlow3 * fRec6[1]))));
		double fTemp1 = max((double)-1, min((double)1, (fSlow14 + (fSlow13 * (((fSlow2 * fRec6[0]) + (fSlow12 * fRec6[1])) + (fSlow2 * fRec6[2]))))));
		double fTemp2 = (fTemp1 * (1 - (0.3333333333333333 * faustpower<2>(fTemp1))));
		fVec2[0] = fTemp2;
		fRec5[0] = ((fVec2[0] + (0.995 * fRec5[1])) - fVec2[1]);
		double 	fRec4 = max(fConst1, fabs(fRec5[0]));
		int iTemp3 = int((iRec2[1] < 4096));
		fRec1[0] = ((iTemp3)?max(fRec1[1], fRec4):fRec4);
		iRec2[0] = ((iTemp3)?(1 + iRec2[1]):1);
		fRec3[0] = ((iTemp3)?fRec3[1]:fRec1[1]);
		fbargraph0 = fRec3[0];
		double fTemp4 = (fVec1[0] + fVec1[1]);
		fRec17[0] = ((fSlow11 * fTemp4) + (fSlow9 * fRec17[1]));
		fRec16[0] = (fRec17[0] - (fSlow7 * ((fSlow5 * fRec16[2]) + (fSlow3 * fRec16[1]))));
		double fTemp5 = (fRec16[2] + (fRec16[0] + (2 * fRec16[1])));
		fVec3[0] = (fSlow7 * fTemp5);
		fRec15[0] = ((fSlow26 * ((fSlow25 * fVec3[1]) + (fSlow24 * fTemp5))) + (fSlow23 * fRec15[1]));
		fRec14[0] = (fRec15[0] - (fSlow21 * ((fSlow19 * fRec14[2]) + (fSlow17 * fRec14[1]))));
		double fTemp6 = max((double)-1, min((double)1, (fSlow29 + (fSlow28 * (((fSlow16 * fRec14[0]) + (fSlow27 * fRec14[1])) + (fSlow16 * fRec14[2]))))));
		double fTemp7 = (fTemp6 * (1 - (0.3333333333333333 * faustpower<2>(fTemp6))));
		fVec4[0] = fTemp7;
		fRec13[0] = ((fVec4[0] + (0.995 * fRec13[1])) - fVec4[1]);
		double 	fRec12 = max(fConst1, fabs(fRec13[0]));
		int iTemp8 = int((iRec10[1] < 4096));
		fRec9[0] = ((iTemp8)?max(fRec9[1], fRec12):fRec12);
		iRec10[0] = ((iTemp8)?(1 + iRec10[1]):1);
		fRec11[0] = ((iTemp8)?fRec11[1]:fRec9[1]);
		fbargraph1 = fRec11[0];
		fRec26[0] = ((fSlow26 * fTemp4) + (fSlow23 * fRec26[1]));
		fRec25[0] = (fRec26[0] - (fSlow21 * ((fSlow19 * fRec25[2]) + (fSlow17 * fRec25[1]))));
		double fTemp9 = (fRec25[2] + (fRec25[0] + (2 * fRec25[1])));
		fVec5[0] = (fSlow21 * fTemp9);
		fRec24[0] = ((fSlow41 * ((fSlow40 * fVec5[1]) + (fSlow39 * fTemp9))) + (fSlow38 * fRec24[1]));
		fRec23[0] = (fRec24[0] - (fSlow36 * ((fSlow34 * fRec23[2]) + (fSlow32 * fRec23[1]))));
		double fTemp10 = max((double)-1, min((double)1, (fSlow44 + (fSlow43 * (((fSlow31 * fRec23[0]) + (fSlow42 * fRec23[1])) + (fSlow31 * fRec23[2]))))));
		double fTemp11 = (fTemp10 * (1 - (0.3333333333333333 * faustpower<2>(fTemp10))));
		fVec6[0] = fTemp11;
		fRec22[0] = ((fVec6[0] + (0.995 * fRec22[1])) - fVec6[1]);
		double 	fRec21 = max(fConst1, fabs(fRec22[0]));
		int iTemp12 = int((iRec19[1] < 4096));
		fRec18[0] = ((iTemp12)?max(fRec18[1], fRec21):fRec21);
		iRec19[0] = ((iTemp12)?(1 + iRec19[1]):1);
		fRec20[0] = ((iTemp12)?fRec20[1]:fRec18[1]);
		fbargraph2 = fRec20[0];
		fRec35[0] = ((fSlow41 * fTemp4) + (fSlow38 * fRec35[1]));
		fRec34[0] = (fRec35[0] - (fSlow36 * ((fSlow34 * fRec34[2]) + (fSlow32 * fRec34[1]))));
		double fTemp13 = (fRec34[2] + (fRec34[0] + (2 * fRec34[1])));
		fVec7[0] = (fSlow36 * fTemp13);
		fRec33[0] = ((fSlow56 * ((fSlow55 * fVec7[1]) + (fSlow54 * fTemp13))) + (fSlow53 * fRec33[1]));
		fRec32[0] = (fRec33[0] - (fSlow51 * ((fSlow49 * fRec32[2]) + (fSlow47 * fRec32[1]))));
		double fTemp14 = max((double)-1, min((double)1, (fSlow59 + (fSlow58 * (((fSlow46 * fRec32[0]) + (fSlow57 * fRec32[1])) + (fSlow46 * fRec32[2]))))));
		double fTemp15 = (fTemp14 * (1 - (0.3333333333333333 * faustpower<2>(fTemp14))));
		fVec8[0] = fTemp15;
		fRec31[0] = ((fVec8[0] + (0.995 * fRec31[1])) - fVec8[1]);
		double 	fRec30 = max(fConst1, fabs(fRec31[0]));
		int iTemp16 = int((iRec28[1] < 4096));
		fRec27[0] = ((iTemp16)?max(fRec27[1], fRec30):fRec30);
		iRec28[0] = ((iTemp16)?(1 + iRec28[1]):1);
		fRec29[0] = ((iTemp16)?fRec29[1]:fRec27[1]);
		fbargraph3 = fRec29[0];
		fRec42[0] = ((fSlow56 * fTemp4) + (fSlow53 * fRec42[1]));
		fRec41[0] = (fRec42[0] - (fSlow51 * ((fSlow49 * fRec41[2]) + (fSlow47 * fRec41[1]))));
		double fTemp17 = max((double)-1, min((double)1, (fSlow61 + (fSlow60 * (fRec41[2] + (fRec41[0] + (2 * fRec41[1])))))));
		double fTemp18 = (fTemp17 * (1 - (0.3333333333333333 * faustpower<2>(fTemp17))));
		fVec9[0] = fTemp18;
		fRec40[0] = ((fVec9[0] + (0.995 * fRec40[1])) - fVec9[1]);
		double 	fRec39 = max(fConst1, fabs(fRec40[0]));
		int iTemp19 = int((iRec37[1] < 4096));
		fRec36[0] = ((iTemp19)?max(fRec36[1], fRec39):fRec39);
		iRec37[0] = ((iTemp19)?(1 + iRec37[1]):1);
		fRec38[0] = ((iTemp19)?fRec38[1]:fRec36[1]);
		fbargraph4 = fRec38[0];
		output0[i] = (FAUSTFLOAT)(((((fRec40[0] + fRec31[0]) + fRec22[0]) + fRec13[0]) + fRec5[0]) * fRec0[0]);
		// post processing
		fRec38[1] = fRec38[0];
		iRec37[1] = iRec37[0];
		fRec36[1] = fRec36[0];
		fRec40[1] = fRec40[0];
		fVec9[1] = fVec9[0];
		fRec41[2] = fRec41[1]; fRec41[1] = fRec41[0];
		fRec42[1] = fRec42[0];
		fRec29[1] = fRec29[0];
		iRec28[1] = iRec28[0];
		fRec27[1] = fRec27[0];
		fRec31[1] = fRec31[0];
		fVec8[1] = fVec8[0];
		fRec32[2] = fRec32[1]; fRec32[1] = fRec32[0];
		fRec33[1] = fRec33[0];
		fVec7[1] = fVec7[0];
		fRec34[2] = fRec34[1]; fRec34[1] = fRec34[0];
		fRec35[1] = fRec35[0];
		fRec20[1] = fRec20[0];
		iRec19[1] = iRec19[0];
		fRec18[1] = fRec18[0];
		fRec22[1] = fRec22[0];
		fVec6[1] = fVec6[0];
		fRec23[2] = fRec23[1]; fRec23[1] = fRec23[0];
		fRec24[1] = fRec24[0];
		fVec5[1] = fVec5[0];
		fRec25[2] = fRec25[1]; fRec25[1] = fRec25[0];
		fRec26[1] = fRec26[0];
		fRec11[1] = fRec11[0];
		iRec10[1] = iRec10[0];
		fRec9[1] = fRec9[0];
		fRec13[1] = fRec13[0];
		fVec4[1] = fVec4[0];
		fRec14[2] = fRec14[1]; fRec14[1] = fRec14[0];
		fRec15[1] = fRec15[0];
		fVec3[1] = fVec3[0];
		fRec16[2] = fRec16[1]; fRec16[1] = fRec16[0];
		fRec17[1] = fRec17[0];
		fRec3[1] = fRec3[0];
		iRec2[1] = iRec2[0];
		fRec1[1] = fRec1[0];
		fRec5[1] = fRec5[0];
		fVec2[1] = fVec2[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec7[1] = fRec7[0];
		fVec1[1] = fVec1[0];
		fRec8[1] = fRec8[0];
		fRec0[1] = fRec0[0];
		iVec0[1] = iVec0[0];
	}
#undef fslider0
#undef fslider1
#undef fslider2
#undef fslider3
#undef fbargraph0
#undef fslider4
#undef fslider5
#undef fslider6
#undef fbargraph1
#undef fslider7
#undef fslider8
#undef fslider9
#undef fbargraph2
#undef fslider10
#undef fslider11
#undef fslider12
#undef fbargraph3
#undef fslider13
#undef fslider14
#undef fbargraph4
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case DRIVE1: 
		fslider13_ = (float*)data; // , 0.0, 0.0, 1.0, 0.01 
		break;
	case DRIVE2: 
		fslider11_ = (float*)data; // , 0.0, 0.0, 1.0, 0.01 
		break;
	case DRIVE3: 
		fslider8_ = (float*)data; // , 0.0, 0.0, 1.0, 0.01 
		break;
	case DRIVE4: 
		fslider5_ = (float*)data; // , 0.0, 0.0, 1.0, 0.01 
		break;
	case DRIVE5: 
		fslider2_ = (float*)data; // , 0.0, 0.0, 1.0, 0.01 
		break;
	case GAIN: 
		fslider0_ = (float*)data; // , 0.0, -4e+01, 4.0, 0.1 
		break;
	case OFFSET1: 
		fslider14_ = (float*)data; // , 0.0, 0.0, 0.5, 0.01 
		break;
	case OFFSET2: 
		fslider12_ = (float*)data; // , 0.0, 0.0, 0.5, 0.01 
		break;
	case OFFSET3: 
		fslider9_ = (float*)data; // , 0.0, 0.0, 0.5, 0.01 
		break;
	case OFFSET4: 
		fslider6_ = (float*)data; // , 0.0, 0.0, 0.5, 0.01 
		break;
	case OFFSET5: 
		fslider3_ = (float*)data; // , 0.0, 0.0, 0.5, 0.01 
		break;
	case CROSSOVER_B1_B2: 
		fslider10_ = (float*)data; // , 8e+01, 2e+01, 2e+04, 1.08 
		break;
	case CROSSOVER_B2_B3: 
		fslider7_ = (float*)data; // , 2.1e+02, 2e+01, 2e+04, 1.08 
		break;
	case CROSSOVER_B3_B4: 
		fslider4_ = (float*)data; // , 1.7e+03, 2e+01, 2e+04, 1.08 
		break;
	case CROSSOVER_B4_B5: 
		fslider1_ = (float*)data; // , 5e+03, 2e+01, 2e+04, 1.08 
		break;
	case V1: 
		fbargraph4_ = (float*)data; // , -70.0, -70.0, 4.0, 0.00001 
		break;
	case V2: 
		fbargraph3_ = (float*)data; // , -70.0, -70.0, 4.0, 0.00001 
		break;
	case V3: 
		fbargraph2_ = (float*)data; // , -70.0, -70.0, 4.0, 0.00001 
		break;
	case V4: 
		fbargraph1_ = (float*)data; // , -70.0, -70.0, 4.0, 0.00001 
		break;
	case V5: 
		fbargraph0_ = (float*)data; // , -70.0, -70.0, 4.0, 0.00001 
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
   DRIVE1, 
   DRIVE2, 
   DRIVE3, 
   DRIVE4, 
   DRIVE5, 
   GAIN, 
   OFFSET1, 
   OFFSET2, 
   OFFSET3, 
   OFFSET4, 
   OFFSET5, 
   CROSSOVER_B1_B2, 
   CROSSOVER_B2_B3, 
   CROSSOVER_B3_B4, 
   CROSSOVER_B4_B5, 
   V1, 
   V2, 
   V3, 
   V4, 
   V5, 
} PortIndex;
*/

} // end namespace mbd
