// generated from file '../src/LV2/faust/gx_distortion.dsp' by dsp2cc:
// Code generated with Faust 0.9.73 (http://faust.grame.fr)


namespace gx_distortion {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	int 	iVec0[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec0[2];
	FAUSTFLOAT 	fentry0;
	FAUSTFLOAT	*fentry0_;
	int 	iConst0;
	double 	fConst1;
	FAUSTFLOAT 	fentry1;
	FAUSTFLOAT	*fentry1_;
	FAUSTFLOAT 	fentry2;
	FAUSTFLOAT	*fentry2_;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	int 	IOTA;
	double 	fVec1[4096];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fRec10[2];
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT	*fcheckbox0_;
	double 	fRec11[2];
	double 	fRec9[3];
	double 	fVec2[2];
	double 	fConst8;
	double 	fConst9;
	double 	fConst10;
	double 	fConst11;
	double 	fConst12;
	double 	fRec8[2];
	double 	fRec7[2];
	double 	fRec6[3];
	double 	fVec3[2];
	double 	fRec5[2];
	double 	fRec4[3];
	double 	fVec4[2];
	double 	fRec3[2];
	double 	fRec2[3];
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT	*fslider4_;
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT	*fslider5_;
	FAUSTFLOAT 	fslider6;
	FAUSTFLOAT	*fslider6_;
	FAUSTFLOAT 	fslider7;
	FAUSTFLOAT	*fslider7_;
	double 	fRec12[2];
	double 	fRec14[2];
	double 	fRec13[3];
	FAUSTFLOAT 	fslider8;
	FAUSTFLOAT	*fslider8_;
	FAUSTFLOAT 	fslider9;
	FAUSTFLOAT	*fslider9_;
	double 	fRec15[2];
	double 	fRec18[2];
	double 	fRec17[3];
	double 	fRec16[3];
	FAUSTFLOAT 	fslider10;
	FAUSTFLOAT	*fslider10_;
	FAUSTFLOAT 	fslider11;
	FAUSTFLOAT	*fslider11_;
	double 	fRec19[2];
	double 	fRec23[2];
	double 	fRec22[3];
	double 	fRec21[3];
	double 	fRec20[3];
	FAUSTFLOAT 	fslider12;
	FAUSTFLOAT	*fslider12_;
	FAUSTFLOAT 	fslider13;
	FAUSTFLOAT	*fslider13_;
	double 	fRec24[2];
	double 	fVec5[2];
	double 	fConst13;
	double 	fConst14;
	double 	fConst15;
	double 	fConst16;
	double 	fRec1[2];
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
	for (int i=0; i<2; i++) iVec0[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<4096; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<3; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<3; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<3; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<3; i++) fRec17[i] = 0;
	for (int i=0; i<3; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<3; i++) fRec22[i] = 0;
	for (int i=0; i<3; i++) fRec21[i] = 0;
	for (int i=0; i<3; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
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
	fConst1 = (3.141592653589793 / double(iConst0));
	fConst2 = tan((47123.8898038469 / double(iConst0)));
	fConst3 = (2 * (1 - (1.0 / faustpower<2>(fConst2))));
	fConst4 = (1.0 / fConst2);
	fConst5 = (1 + ((fConst4 - 1.414213562373095) / fConst2));
	fConst6 = (1 + ((1.414213562373095 + fConst4) / fConst2));
	fConst7 = (1.0 / fConst6);
	IOTA = 0;
	fConst8 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst9 = (0 - fConst8);
	fConst10 = (1 + fConst8);
	fConst11 = (1.0 / (fConst10 * fConst6));
	fConst12 = (0 - ((1 - fConst8) / fConst10));
	fConst13 = (1.0 / tan((20517.741620594938 / double(iConst0))));
	fConst14 = (1 + fConst13);
	fConst15 = (1.0 / fConst14);
	fConst16 = (0 - ((1 - fConst13) / fConst14));
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
#define fentry0 (*fentry0_)
#define fentry1 (*fentry1_)
#define fentry2 (*fentry2_)
#define fslider2 (*fslider2_)
#define fslider3 (*fslider3_)
#define fcheckbox0 (*fcheckbox0_)
#define fslider4 (*fslider4_)
#define fslider5 (*fslider5_)
#define fslider6 (*fslider6_)
#define fslider7 (*fslider7_)
#define fslider8 (*fslider8_)
#define fslider9 (*fslider9_)
#define fslider10 (*fslider10_)
#define fslider11 (*fslider11_)
#define fslider12 (*fslider12_)
#define fslider13 (*fslider13_)
	double 	fSlow0 = (0.01 * double(fslider0));
	double 	fSlow1 = (1 - fSlow0);
	double 	fSlow2 = (0.0010000000000000009 * pow(10,(0.05 * (double(fslider1) - 10))));
	double 	fSlow3 = tan((fConst1 * double(fentry0)));
	double 	fSlow4 = (1.0 / faustpower<2>(fSlow3));
	double 	fSlow5 = (2 * (1 - fSlow4));
	double 	fSlow6 = (1.0 / fSlow3);
	double 	fSlow7 = (1 + ((fSlow6 - 1.0000000000000004) / fSlow3));
	double 	fSlow8 = (1 + ((fSlow6 + 1.0000000000000004) / fSlow3));
	double 	fSlow9 = (1.0 / fSlow8);
	double 	fSlow10 = tan((fConst1 * double(fentry1)));
	double 	fSlow11 = (1.0 / faustpower<2>(fSlow10));
	double 	fSlow12 = (2 * (1 - fSlow11));
	double 	fSlow13 = (1.0 / fSlow10);
	double 	fSlow14 = (1 + ((fSlow13 - 1.0000000000000004) / fSlow10));
	double 	fSlow15 = (1 + ((fSlow13 + 1.0000000000000004) / fSlow10));
	double 	fSlow16 = (1.0 / fSlow15);
	double 	fSlow17 = tan((fConst1 * double(fentry2)));
	double 	fSlow18 = (1.0 / faustpower<2>(fSlow17));
	double 	fSlow19 = (2 * (1 - fSlow18));
	double 	fSlow20 = (1.0 / fSlow17);
	double 	fSlow21 = (1 + ((fSlow20 - 1.0000000000000004) / fSlow17));
	double 	fSlow22 = (1 + ((1.0000000000000004 + fSlow20) / fSlow17));
	double 	fSlow23 = (1.0 / fSlow22);
	double 	fSlow24 = (1.0 - double(fslider2));
	double 	fSlow25 = double(fslider3);
	int 	iSlow26 = int((int(fSlow25) & 4095));
	int 	iSlow27 = int((int((fSlow25 - 1)) & 4095));
	int 	iSlow28 = int(double(fcheckbox0));
	double 	fSlow29 = (1 + fSlow20);
	double 	fSlow30 = (1.0 / fSlow29);
	double 	fSlow31 = (0 - ((1 - fSlow20) / fSlow29));
	double 	fSlow32 = (1 + fSlow13);
	double 	fSlow33 = (1.0 / fSlow32);
	double 	fSlow34 = (0 - ((1 - fSlow13) / fSlow32));
	double 	fSlow35 = (1 + fSlow6);
	double 	fSlow36 = (1.0 / fSlow35);
	double 	fSlow37 = (0 - ((1 - fSlow6) / fSlow35));
	double 	fSlow38 = double(fslider5);
	double 	fSlow39 = (pow(1e+01,(2 * (fSlow38 * double(fslider4)))) / fSlow8);
	double 	fSlow40 = double(fslider6);
	double 	fSlow41 = (0.0010000000000000009 * pow(10,(0.05 * (double(fslider7) - 10))));
	double 	fSlow42 = (0 - fSlow6);
	double 	fSlow43 = (1.0 / (fSlow3 * fSlow15));
	double 	fSlow44 = (2 * (0 - fSlow4));
	double 	fSlow45 = (pow(1e+01,(2 * (fSlow38 * double(fslider8)))) / fSlow8);
	double 	fSlow46 = (0.0010000000000000009 * pow(10,(0.05 * (double(fslider9) - 10))));
	double 	fSlow47 = (1 + ((fSlow6 - 1.0) / fSlow3));
	double 	fSlow48 = (1.0 / (1 + ((1.0 + fSlow6) / fSlow3)));
	double 	fSlow49 = (0 - fSlow13);
	double 	fSlow50 = (1.0 / (fSlow10 * fSlow22));
	double 	fSlow51 = (2 * (0 - fSlow11));
	double 	fSlow52 = pow(1e+01,(2 * (fSlow38 * double(fslider10))));
	double 	fSlow53 = (0.0010000000000000009 * pow(10,(0.05 * (double(fslider11) - 10))));
	double 	fSlow54 = (1 + ((fSlow13 - 1.0) / fSlow10));
	double 	fSlow55 = (1.0 / (1 + ((1.0 + fSlow13) / fSlow10)));
	double 	fSlow56 = (0 - fSlow20);
	double 	fSlow57 = (2 * (0 - fSlow18));
	double 	fSlow58 = pow(1e+01,(2 * (fSlow38 * double(fslider12))));
	double 	fSlow59 = (0.0010000000000000009 * pow(10,(0.05 * (double(fslider13) - 10))));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		iVec0[0] = 1;
		fRec0[0] = ((0.999 * fRec0[1]) + fSlow2);
		double fTemp1 = (fSlow0 * fTemp0);
		double fTemp2 = (fTemp1 + (fSlow24 * fRec10[1]));
		fVec1[IOTA&4095] = fTemp2;
		fRec10[0] = (0.5 * (fVec1[(IOTA-iSlow27)&4095] + fVec1[(IOTA-iSlow26)&4095]));
		fRec11[0] = ((1e-20 * (1 - iVec0[1])) - fRec11[1]);
		fRec9[0] = ((fRec11[0] + ((iSlow28)?fRec10[0]:fTemp1)) - (fConst7 * ((fConst5 * fRec9[2]) + (fConst3 * fRec9[1]))));
		double fTemp3 = (fRec9[2] + (fRec9[0] + (2 * fRec9[1])));
		fVec2[0] = fTemp3;
		fRec8[0] = ((fConst12 * fRec8[1]) + (fConst11 * ((fConst8 * fVec2[0]) + (fConst9 * fVec2[1]))));
		fRec7[0] = ((fSlow31 * fRec7[1]) + (fSlow30 * (fRec8[0] + fRec8[1])));
		fRec6[0] = (fRec7[0] - (fSlow23 * ((fSlow21 * fRec6[2]) + (fSlow19 * fRec6[1]))));
		double fTemp4 = (fRec6[2] + (fRec6[0] + (2 * fRec6[1])));
		double fTemp5 = (fSlow23 * fTemp4);
		fVec3[0] = fTemp5;
		fRec5[0] = ((fSlow34 * fRec5[1]) + (fSlow33 * (fVec3[0] + fVec3[1])));
		fRec4[0] = (fRec5[0] - (fSlow16 * ((fSlow14 * fRec4[2]) + (fSlow12 * fRec4[1]))));
		double fTemp6 = (fRec4[2] + (fRec4[0] + (2 * fRec4[1])));
		double fTemp7 = (fSlow16 * fTemp6);
		fVec4[0] = fTemp7;
		fRec3[0] = ((fSlow37 * fRec3[1]) + (fSlow36 * (fVec4[0] + fVec4[1])));
		fRec2[0] = (fRec3[0] - (fSlow9 * ((fSlow7 * fRec2[2]) + (fSlow5 * fRec2[1]))));
		double fTemp8 = max((double)-1, min((double)1, (fSlow40 + (fSlow39 * (fRec2[2] + (fRec2[0] + (2 * fRec2[1])))))));
		fRec12[0] = ((0.999 * fRec12[1]) + fSlow41);
		fRec14[0] = ((fSlow37 * fRec14[1]) + (fSlow36 * ((fSlow43 * fTemp6) + (fSlow42 * fVec4[1]))));
		fRec13[0] = (fRec14[0] - (fSlow9 * ((fSlow7 * fRec13[2]) + (fSlow5 * fRec13[1]))));
		double fTemp9 = max((double)-1, min((double)1, (fSlow40 + (fSlow45 * (((fSlow4 * fRec13[0]) + (fSlow44 * fRec13[1])) + (fSlow4 * fRec13[2]))))));
		fRec15[0] = ((0.999 * fRec15[1]) + fSlow46);
		double fTemp10 = (fSlow5 * fRec16[1]);
		fRec18[0] = ((fSlow34 * fRec18[1]) + (fSlow33 * ((fSlow50 * fTemp4) + (fSlow49 * fVec3[1]))));
		fRec17[0] = (fRec18[0] - (fSlow16 * ((fSlow14 * fRec17[2]) + (fSlow12 * fRec17[1]))));
		fRec16[0] = ((fSlow16 * (((fSlow11 * fRec17[0]) + (fSlow51 * fRec17[1])) + (fSlow11 * fRec17[2]))) - (fSlow48 * ((fSlow47 * fRec16[2]) + fTemp10)));
		double fTemp11 = max((double)-1, min((double)1, (fSlow40 + (fSlow52 * (fRec16[2] + (fSlow48 * (fTemp10 + (fSlow47 * fRec16[0]))))))));
		fRec19[0] = ((0.999 * fRec19[1]) + fSlow53);
		double fTemp12 = (fSlow5 * fRec20[1]);
		double fTemp13 = (fSlow12 * fRec21[1]);
		fRec23[0] = ((fSlow31 * fRec23[1]) + (fSlow30 * ((fSlow20 * fRec8[0]) + (fSlow56 * fRec8[1]))));
		fRec22[0] = (fRec23[0] - (fSlow23 * ((fSlow21 * fRec22[2]) + (fSlow19 * fRec22[1]))));
		fRec21[0] = ((fSlow23 * (((fSlow18 * fRec22[0]) + (fSlow57 * fRec22[1])) + (fSlow18 * fRec22[2]))) - (fSlow55 * ((fSlow54 * fRec21[2]) + fTemp13)));
		fRec20[0] = ((fRec21[2] + (fSlow55 * (fTemp13 + (fSlow54 * fRec21[0])))) - (fSlow48 * ((fSlow47 * fRec20[2]) + fTemp12)));
		double fTemp14 = max((double)-1, min((double)1, (fSlow40 + (fSlow58 * (fRec20[2] + (fSlow48 * ((fSlow47 * fRec20[0]) + fTemp12)))))));
		fRec24[0] = ((0.999 * fRec24[1]) + fSlow59);
		double fTemp15 = (((((fRec24[0] * fTemp14) * (1 - (0.3333333333333333 * faustpower<2>(fTemp14)))) + ((fRec19[0] * fTemp11) * (1 - (0.3333333333333333 * faustpower<2>(fTemp11))))) + ((fRec15[0] * fTemp9) * (1 - (0.3333333333333333 * faustpower<2>(fTemp9))))) + ((fRec12[0] * fTemp8) * (1 - (0.3333333333333333 * faustpower<2>(fTemp8)))));
		fVec5[0] = fTemp15;
		fRec1[0] = ((fConst16 * fRec1[1]) + (fConst15 * (fVec5[0] + fVec5[1])));
		output0[i] = (FAUSTFLOAT)((fRec1[0] * fRec0[0]) + (fSlow1 * fTemp0));
		// post processing
		fRec1[1] = fRec1[0];
		fVec5[1] = fVec5[0];
		fRec24[1] = fRec24[0];
		fRec20[2] = fRec20[1]; fRec20[1] = fRec20[0];
		fRec21[2] = fRec21[1]; fRec21[1] = fRec21[0];
		fRec22[2] = fRec22[1]; fRec22[1] = fRec22[0];
		fRec23[1] = fRec23[0];
		fRec19[1] = fRec19[0];
		fRec16[2] = fRec16[1]; fRec16[1] = fRec16[0];
		fRec17[2] = fRec17[1]; fRec17[1] = fRec17[0];
		fRec18[1] = fRec18[0];
		fRec15[1] = fRec15[0];
		fRec13[2] = fRec13[1]; fRec13[1] = fRec13[0];
		fRec14[1] = fRec14[0];
		fRec12[1] = fRec12[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fVec4[1] = fVec4[0];
		fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fVec3[1] = fVec3[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
		fVec2[1] = fVec2[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec11[1] = fRec11[0];
		fRec10[1] = fRec10[0];
		IOTA = IOTA+1;
		fRec0[1] = fRec0[0];
		iVec0[1] = iVec0[0];
	}
#undef fslider0
#undef fslider1
#undef fentry0
#undef fentry1
#undef fentry2
#undef fslider2
#undef fslider3
#undef fcheckbox0
#undef fslider4
#undef fslider5
#undef fslider6
#undef fslider7
#undef fslider8
#undef fslider9
#undef fslider10
#undef fslider11
#undef fslider12
#undef fslider13
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
		fslider5_ = (float*)data; // , 0.64, 0.0, 1.0, 0.01 
		break;
	case GAIN: 
		fslider1_ = (float*)data; // , 2.0, -1e+01, 1e+01, 0.1 
		break;
	case HIGH_DRIVE: 
		fslider12_ = (float*)data; // , 1.0, 0.0, 1.0, 0.01 
		break;
	case HIGH_GAIN: 
		fslider13_ = (float*)data; // , 1e+01, -1e+01, 2e+01, 0.1 
		break;
	case LEVEL: 
		fslider6_ = (float*)data; // , 0.0, 0.0, 0.5, 0.01 
		break;
	case LOW_DRIVE: 
		fslider4_ = (float*)data; // , 1.0, 0.0, 1.0, 0.01 
		break;
	case LOW_GAIN: 
		fslider7_ = (float*)data; // , 1e+01, -1e+01, 2e+01, 0.1 
		break;
	case MIDDLE_H_DRIVE: 
		fslider10_ = (float*)data; // , 1.0, 0.0, 1.0, 0.01 
		break;
	case MIDDLE_H_GAIN: 
		fslider11_ = (float*)data; // , 1e+01, -1e+01, 2e+01, 0.1 
		break;
	case MIDDLE_L_DRIVE: 
		fslider8_ = (float*)data; // , 1.0, 0.0, 1.0, 0.01 
		break;
	case MIDDLE_L_GAIN: 
		fslider9_ = (float*)data; // , 1e+01, -1e+01, 2e+01, 0.1 
		break;
	case ON_OFF: 
		fcheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case SPLIT_HIGH_FREQ: 
		fentry2_ = (float*)data; // , 1.25e+03, 1.25e+03, 1.2e+04, 1e+01 
		break;
	case SPLIT_LOW_FREQ: 
		fentry0_ = (float*)data; // , 2.5e+02, 2e+01, 6e+02, 1e+01 
		break;
	case SPLIT_MIDDLE_FREQ: 
		fentry1_ = (float*)data; // , 6.5e+02, 6e+02, 1.25e+03, 1e+01 
		break;
	case TRIGGER: 
		fslider2_ = (float*)data; // , 0.12, 0.0, 1.0, 0.01 
		break;
	case VIBRATO: 
		fslider3_ = (float*)data; // , 1.0, 0.0, 1.0, 0.01 
		break;
	case WET_DRY: 
		fslider0_ = (float*)data; // , 1e+02, 0.0, 1e+02, 1.0 
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
