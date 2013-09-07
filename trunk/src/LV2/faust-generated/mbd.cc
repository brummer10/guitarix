// generated from file '../src/LV2/faust/mbd.dsp' by dsp2cc:
// Code generated with Faust 0.9.58 (http://faust.grame.fr)


namespace mbd {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	int 	iVec0[2];
	int 	iConst0;
	double 	fConst1;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fConst2;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec5[2];
	double 	fVec1[2];
	double 	fRec4[2];
	double 	fRec3[3];
	double 	fVec2[2];
	double 	fRec2[2];
	double 	fRec1[3];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	FAUSTFLOAT 	fbargraph0;
	FAUSTFLOAT	*fbargraph0_;
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT	*fslider4_;
	double 	fRec8[2];
	double 	fRec7[3];
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT	*fslider5_;
	FAUSTFLOAT 	fbargraph1;
	FAUSTFLOAT	*fbargraph1_;
	FAUSTFLOAT 	fslider6;
	FAUSTFLOAT	*fslider6_;
	FAUSTFLOAT 	fslider7;
	FAUSTFLOAT	*fslider7_;
	double 	fRec13[2];
	double 	fRec12[3];
	double 	fVec3[2];
	double 	fRec11[2];
	double 	fRec10[3];
	FAUSTFLOAT 	fslider8;
	FAUSTFLOAT	*fslider8_;
	FAUSTFLOAT 	fbargraph2;
	FAUSTFLOAT	*fbargraph2_;
	FAUSTFLOAT 	fslider9;
	FAUSTFLOAT	*fslider9_;
	FAUSTFLOAT 	fslider10;
	FAUSTFLOAT	*fslider10_;
	double 	fRec18[2];
	double 	fRec17[3];
	double 	fVec4[2];
	double 	fRec16[2];
	double 	fRec15[3];
	FAUSTFLOAT 	fslider11;
	FAUSTFLOAT	*fslider11_;
	FAUSTFLOAT 	fbargraph3;
	FAUSTFLOAT	*fbargraph3_;
	FAUSTFLOAT 	fslider12;
	FAUSTFLOAT	*fslider12_;
	double 	fRec21[2];
	double 	fRec20[3];
	FAUSTFLOAT 	fslider13;
	FAUSTFLOAT	*fslider13_;
	FAUSTFLOAT 	fbargraph4;
	FAUSTFLOAT	*fbargraph4_;
	FAUSTFLOAT 	fslider14;
	FAUSTFLOAT	*fslider14_;
	double 	fRec22[2];
	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(uint32_t samplingFreq);
	void compute(int count, float *input0, float *output0);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(uint32_t samplingFreq, PluginLV2*);
	static void compute_static(int count, float *input0, float *output0, PluginLV2*);
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
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<3; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<3; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<3; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<3; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<3; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<3; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<3; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<3; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
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

void always_inline Dsp::compute(int count, float *input0, float *output0)
{
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
#define fslider2 (*fslider2_)
#define fslider3 (*fslider3_)
#define fbargraph0 (*fbargraph0_)
#define fslider4 (*fslider4_)
#define fslider5 (*fslider5_)
#define fbargraph1 (*fbargraph1_)
#define fslider6 (*fslider6_)
#define fslider7 (*fslider7_)
#define fslider8 (*fslider8_)
#define fbargraph2 (*fbargraph2_)
#define fslider9 (*fslider9_)
#define fslider10 (*fslider10_)
#define fslider11 (*fslider11_)
#define fbargraph3 (*fbargraph3_)
#define fslider12 (*fslider12_)
#define fslider13 (*fslider13_)
#define fbargraph4 (*fbargraph4_)
#define fslider14 (*fslider14_)
	double 	fSlow0 = fslider0;
	double 	fSlow1 = tan((fConst2 * fslider1));
	double 	fSlow2 = (1.0 / faustpower<2>(fSlow1));
	double 	fSlow3 = (2 * (1 - fSlow2));
	double 	fSlow4 = (1.0 / fSlow1);
	double 	fSlow5 = (1 + ((fSlow4 - 1.0000000000000004) / fSlow1));
	double 	fSlow6 = (1 + ((1.0000000000000004 + fSlow4) / fSlow1));
	double 	fSlow7 = (1.0 / fSlow6);
	double 	fSlow8 = (1 + fSlow4);
	double 	fSlow9 = (0 - ((1 - fSlow4) / fSlow8));
	double 	fSlow10 = tan((fConst2 * fslider2));
	double 	fSlow11 = (1.0 / faustpower<2>(fSlow10));
	double 	fSlow12 = (2 * (1 - fSlow11));
	double 	fSlow13 = (1.0 / fSlow10);
	double 	fSlow14 = (1 + ((fSlow13 - 1.0000000000000004) / fSlow10));
	double 	fSlow15 = (1 + ((1.0000000000000004 + fSlow13) / fSlow10));
	double 	fSlow16 = (1.0 / fSlow15);
	double 	fSlow17 = (1 + fSlow13);
	double 	fSlow18 = (0 - ((1 - fSlow13) / fSlow17));
	double 	fSlow19 = (1.0 / fSlow17);
	double 	fSlow20 = (1.0 / (fSlow15 * fSlow1));
	double 	fSlow21 = (0 - fSlow4);
	double 	fSlow22 = (1.0 / fSlow8);
	double 	fSlow23 = (2 * (0 - fSlow2));
	double 	fSlow24 = (pow(1e+01,(2 * fslider3)) / fSlow6);
	double 	fSlow25 = fslider4;
	double 	fSlow26 = (0 - fSlow13);
	double 	fSlow27 = (2 * (0 - fSlow11));
	double 	fSlow28 = (pow(1e+01,(2 * fslider5)) / fSlow15);
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
	double 	fSlow39 = (1.0 / (fSlow6 * fSlow30));
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
	double 	fSlow61 = (0.0010000000000000009 * pow(10,(0.05 * fslider14)));
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		fRec5[0] = ((1e-20 * (1 - iVec0[1])) - fRec5[1]);
		double fTemp0 = ((double)input0[i] + fRec5[0]);
		fVec1[0] = fTemp0;
		double fTemp1 = (fVec1[0] + fVec1[1]);
		fRec4[0] = ((fSlow19 * fTemp1) + (fSlow18 * fRec4[1]));
		fRec3[0] = (fRec4[0] - (fSlow16 * ((fSlow14 * fRec3[2]) + (fSlow12 * fRec3[1]))));
		double fTemp2 = (fRec3[2] + (fRec3[0] + (2 * fRec3[1])));
		fVec2[0] = (fSlow16 * fTemp2);
		fRec2[0] = ((fSlow22 * ((fSlow21 * fVec2[1]) + (fSlow20 * fTemp2))) + (fSlow9 * fRec2[1]));
		fRec1[0] = (fRec2[0] - (fSlow7 * ((fSlow5 * fRec1[2]) + (fSlow3 * fRec1[1]))));
		double fTemp3 = max((double)-1, min((double)1, (fSlow0 + (fSlow24 * (((fSlow2 * fRec1[0]) + (fSlow23 * fRec1[1])) + (fSlow2 * fRec1[2]))))));
		double fTemp4 = (fTemp3 * (1 - (0.3333333333333333 * faustpower<2>(fTemp3))));
		double 	fRec0 = max(fConst1, fabs((fTemp4 - fSlow0)));
		fbargraph0 = fRec0;
		fRec8[0] = ((fSlow19 * ((fSlow26 * fVec1[1]) + (fSlow13 * fVec1[0]))) + (fSlow18 * fRec8[1]));
		fRec7[0] = (fRec8[0] - (fSlow16 * ((fSlow14 * fRec7[2]) + (fSlow12 * fRec7[1]))));
		double fTemp5 = max((double)-1, min((double)1, (fSlow25 + (fSlow28 * (((fSlow11 * fRec7[0]) + (fSlow27 * fRec7[1])) + (fSlow11 * fRec7[2]))))));
		double fTemp6 = (fTemp5 * (1 - (0.3333333333333333 * faustpower<2>(fTemp5))));
		double 	fRec6 = max(fConst1, fabs((fTemp6 - fSlow25)));
		fbargraph1 = fRec6;
		fRec13[0] = ((fSlow22 * fTemp1) + (fSlow9 * fRec13[1]));
		fRec12[0] = (fRec13[0] - (fSlow7 * ((fSlow5 * fRec12[2]) + (fSlow3 * fRec12[1]))));
		double fTemp7 = (fRec12[2] + (fRec12[0] + (2 * fRec12[1])));
		fVec3[0] = (fSlow7 * fTemp7);
		fRec11[0] = ((fSlow41 * ((fSlow40 * fVec3[1]) + (fSlow39 * fTemp7))) + (fSlow38 * fRec11[1]));
		fRec10[0] = (fRec11[0] - (fSlow36 * ((fSlow34 * fRec10[2]) + (fSlow32 * fRec10[1]))));
		double fTemp8 = max((double)-1, min((double)1, (fSlow29 + (fSlow43 * (((fSlow31 * fRec10[0]) + (fSlow42 * fRec10[1])) + (fSlow31 * fRec10[2]))))));
		double fTemp9 = (fTemp8 * (1 - (0.3333333333333333 * faustpower<2>(fTemp8))));
		double 	fRec9 = max(fConst1, fabs((fTemp9 - fSlow29)));
		fbargraph2 = fRec9;
		fRec18[0] = ((fSlow41 * fTemp1) + (fSlow38 * fRec18[1]));
		fRec17[0] = (fRec18[0] - (fSlow36 * ((fSlow34 * fRec17[2]) + (fSlow32 * fRec17[1]))));
		double fTemp10 = (fRec17[2] + (fRec17[0] + (2 * fRec17[1])));
		fVec4[0] = (fSlow36 * fTemp10);
		fRec16[0] = ((fSlow56 * ((fSlow55 * fVec4[1]) + (fSlow54 * fTemp10))) + (fSlow53 * fRec16[1]));
		fRec15[0] = (fRec16[0] - (fSlow51 * ((fSlow49 * fRec15[2]) + (fSlow47 * fRec15[1]))));
		double fTemp11 = max((double)-1, min((double)1, (fSlow44 + (fSlow58 * (((fSlow46 * fRec15[0]) + (fSlow57 * fRec15[1])) + (fSlow46 * fRec15[2]))))));
		double fTemp12 = (fTemp11 * (1 - (0.3333333333333333 * faustpower<2>(fTemp11))));
		double 	fRec14 = max(fConst1, fabs((fTemp12 - fSlow44)));
		fbargraph3 = fRec14;
		fRec21[0] = ((fSlow56 * fTemp1) + (fSlow53 * fRec21[1]));
		fRec20[0] = (fRec21[0] - (fSlow51 * ((fSlow49 * fRec20[2]) + (fSlow47 * fRec20[1]))));
		double fTemp13 = max((double)-1, min((double)1, (fSlow59 + (fSlow60 * (fRec20[2] + (fRec20[0] + (2 * fRec20[1])))))));
		double fTemp14 = (fTemp13 * (1 - (0.3333333333333333 * faustpower<2>(fTemp13))));
		double 	fRec19 = max(fConst1, fabs((fTemp14 - fSlow59)));
		fbargraph4 = fRec19;
		fRec22[0] = (fSlow61 + (0.999 * fRec22[1]));
		output0[i] = (FAUSTFLOAT)(fRec22[0] * (fTemp14 + (fTemp12 + (fTemp9 + (fTemp6 + fTemp4)))));
		// post processing
		fRec22[1] = fRec22[0];
		fRec20[2] = fRec20[1]; fRec20[1] = fRec20[0];
		fRec21[1] = fRec21[0];
		fRec15[2] = fRec15[1]; fRec15[1] = fRec15[0];
		fRec16[1] = fRec16[0];
		fVec4[1] = fVec4[0];
		fRec17[2] = fRec17[1]; fRec17[1] = fRec17[0];
		fRec18[1] = fRec18[0];
		fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		fVec3[1] = fVec3[0];
		fRec12[2] = fRec12[1]; fRec12[1] = fRec12[0];
		fRec13[1] = fRec13[0];
		fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fVec2[1] = fVec2[0];
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fVec1[1] = fVec1[0];
		fRec5[1] = fRec5[0];
		iVec0[1] = iVec0[0];
	}
#undef fslider0
#undef fslider1
#undef fslider2
#undef fslider3
#undef fbargraph0
#undef fslider4
#undef fslider5
#undef fbargraph1
#undef fslider6
#undef fslider7
#undef fslider8
#undef fbargraph2
#undef fslider9
#undef fslider10
#undef fslider11
#undef fbargraph3
#undef fslider12
#undef fslider13
#undef fbargraph4
#undef fslider14
}

void __rt_func Dsp::compute_static(int count, float *input0, float *output0, PluginLV2 *p)
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
		fslider3_ = (float*)data; // , 0.0, 0.0, 1.0, 0.01 
		break;
	case DRIVE5: 
		fslider5_ = (float*)data; // , 0.0, 0.0, 1.0, 0.01 
		break;
	case GAIN: 
		fslider14_ = (float*)data; // , 0.0, -4e+01, 4.0, 0.1 
		break;
	case OFFSET1: 
		fslider12_ = (float*)data; // , 0.0, 0.0, 0.5, 0.01 
		break;
	case OFFSET2: 
		fslider9_ = (float*)data; // , 0.0, 0.0, 0.5, 0.01 
		break;
	case OFFSET3: 
		fslider6_ = (float*)data; // , 0.0, 0.0, 0.5, 0.01 
		break;
	case OFFSET4: 
		fslider0_ = (float*)data; // , 0.0, 0.0, 0.5, 0.01 
		break;
	case OFFSET5: 
		fslider4_ = (float*)data; // , 0.0, 0.0, 0.5, 0.01 
		break;
	case CROSSOVER_B1_B2: 
		fslider10_ = (float*)data; // , 8e+01, 2e+01, 2e+04, 1.08 
		break;
	case CROSSOVER_B2_B3: 
		fslider7_ = (float*)data; // , 2.1e+02, 2e+01, 2e+04, 1.08 
		break;
	case CROSSOVER_B3_B4: 
		fslider1_ = (float*)data; // , 1.7e+03, 2e+01, 2e+04, 1.08 
		break;
	case CROSSOVER_B4_B5: 
		fslider2_ = (float*)data; // , 5e+03, 2e+01, 2e+04, 1.08 
		break;
	case V1: 
		fbargraph4_ = (float*)data; // , -70.0, -70.0, 4.0, 1.0 
		break;
	case V2: 
		fbargraph3_ = (float*)data; // , -70.0, -70.0, 4.0, 1.0 
		break;
	case V3: 
		fbargraph2_ = (float*)data; // , -70.0, -70.0, 4.0, 1.0 
		break;
	case V4: 
		fbargraph0_ = (float*)data; // , -70.0, -70.0, 4.0, 1.0 
		break;
	case V5: 
		fbargraph1_ = (float*)data; // , -70.0, -70.0, 4.0, 1.0 
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
