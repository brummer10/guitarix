// generated from file '../src/LV2/faust/selecteq.dsp' by dsp2cc:
// Code generated with Faust 2.15.11 (https://faust.grame.fr)


namespace selecteq {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	double fConst0;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	FAUSTFLOAT fVslider4;
	FAUSTFLOAT	*fVslider4_;
	FAUSTFLOAT fVslider5;
	FAUSTFLOAT	*fVslider5_;
	FAUSTFLOAT fVslider6;
	FAUSTFLOAT	*fVslider6_;
	FAUSTFLOAT fVslider7;
	FAUSTFLOAT	*fVslider7_;
	FAUSTFLOAT fVslider8;
	FAUSTFLOAT	*fVslider8_;
	FAUSTFLOAT fVslider9;
	FAUSTFLOAT	*fVslider9_;
	FAUSTFLOAT fVslider10;
	FAUSTFLOAT	*fVslider10_;
	FAUSTFLOAT fVslider11;
	FAUSTFLOAT	*fVslider11_;
	FAUSTFLOAT fVslider12;
	FAUSTFLOAT	*fVslider12_;
	FAUSTFLOAT fVslider13;
	FAUSTFLOAT	*fVslider13_;
	FAUSTFLOAT fVslider14;
	FAUSTFLOAT	*fVslider14_;
	FAUSTFLOAT fVslider15;
	FAUSTFLOAT	*fVslider15_;
	FAUSTFLOAT fVslider16;
	FAUSTFLOAT	*fVslider16_;
	FAUSTFLOAT fVslider17;
	FAUSTFLOAT	*fVslider17_;
	FAUSTFLOAT fVslider18;
	FAUSTFLOAT	*fVslider18_;
	FAUSTFLOAT fVslider19;
	FAUSTFLOAT	*fVslider19_;
	FAUSTFLOAT fVslider20;
	FAUSTFLOAT	*fVslider20_;
	FAUSTFLOAT fVslider21;
	FAUSTFLOAT	*fVslider21_;
	FAUSTFLOAT fVslider22;
	FAUSTFLOAT	*fVslider22_;
	FAUSTFLOAT fVslider23;
	FAUSTFLOAT	*fVslider23_;
	FAUSTFLOAT fVslider24;
	FAUSTFLOAT	*fVslider24_;
	FAUSTFLOAT fVslider25;
	FAUSTFLOAT	*fVslider25_;
	FAUSTFLOAT fVslider26;
	FAUSTFLOAT	*fVslider26_;
	FAUSTFLOAT fVslider27;
	FAUSTFLOAT	*fVslider27_;
	FAUSTFLOAT fVslider28;
	FAUSTFLOAT	*fVslider28_;
	FAUSTFLOAT fVslider29;
	FAUSTFLOAT	*fVslider29_;
	double fRec9[3];
	double fRec8[3];
	double fRec7[3];
	double fRec6[3];
	double fRec5[3];
	double fRec4[3];
	double fRec3[3];
	double fRec2[3];
	double fRec1[3];
	double fRec0[3];

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
	id = "eqs";
	name = N_("Scaleable EQ");
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
	for (int l0 = 0; (l0 < 3); l0 = (l0 + 1)) fRec9[l0] = 0.0;
	for (int l1 = 0; (l1 < 3); l1 = (l1 + 1)) fRec8[l1] = 0.0;
	for (int l2 = 0; (l2 < 3); l2 = (l2 + 1)) fRec7[l2] = 0.0;
	for (int l3 = 0; (l3 < 3); l3 = (l3 + 1)) fRec6[l3] = 0.0;
	for (int l4 = 0; (l4 < 3); l4 = (l4 + 1)) fRec5[l4] = 0.0;
	for (int l5 = 0; (l5 < 3); l5 = (l5 + 1)) fRec4[l5] = 0.0;
	for (int l6 = 0; (l6 < 3); l6 = (l6 + 1)) fRec3[l6] = 0.0;
	for (int l7 = 0; (l7 < 3); l7 = (l7 + 1)) fRec2[l7] = 0.0;
	for (int l8 = 0; (l8 < 3); l8 = (l8 + 1)) fRec1[l8] = 0.0;
	for (int l9 = 0; (l9 < 3); l9 = (l9 + 1)) fRec0[l9] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = (3.1415926535897931 / std::min<double>(192000.0, std::max<double>(1.0, double(fSamplingFreq))));
	fVslider0 = FAUSTFLOAT(16000.0);
	fVslider1 = FAUSTFLOAT(0.0);
	fVslider2 = FAUSTFLOAT(50.0);
	fVslider3 = FAUSTFLOAT(8000.0);
	fVslider4 = FAUSTFLOAT(0.0);
	fVslider5 = FAUSTFLOAT(50.0);
	fVslider6 = FAUSTFLOAT(4000.0);
	fVslider7 = FAUSTFLOAT(0.0);
	fVslider8 = FAUSTFLOAT(50.0);
	fVslider9 = FAUSTFLOAT(2000.0);
	fVslider10 = FAUSTFLOAT(0.0);
	fVslider11 = FAUSTFLOAT(50.0);
	fVslider12 = FAUSTFLOAT(1000.0);
	fVslider13 = FAUSTFLOAT(0.0);
	fVslider14 = FAUSTFLOAT(50.0);
	fVslider15 = FAUSTFLOAT(500.0);
	fVslider16 = FAUSTFLOAT(0.0);
	fVslider17 = FAUSTFLOAT(50.0);
	fVslider18 = FAUSTFLOAT(250.0);
	fVslider19 = FAUSTFLOAT(0.0);
	fVslider20 = FAUSTFLOAT(50.0);
	fVslider21 = FAUSTFLOAT(125.0);
	fVslider22 = FAUSTFLOAT(0.0);
	fVslider23 = FAUSTFLOAT(50.0);
	fVslider24 = FAUSTFLOAT(62.0);
	fVslider25 = FAUSTFLOAT(0.0);
	fVslider26 = FAUSTFLOAT(50.0);
	fVslider27 = FAUSTFLOAT(31.0);
	fVslider28 = FAUSTFLOAT(0.0);
	fVslider29 = FAUSTFLOAT(50.0);
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
#define fVslider14 (*fVslider14_)
#define fVslider15 (*fVslider15_)
#define fVslider16 (*fVslider16_)
#define fVslider17 (*fVslider17_)
#define fVslider18 (*fVslider18_)
#define fVslider19 (*fVslider19_)
#define fVslider20 (*fVslider20_)
#define fVslider21 (*fVslider21_)
#define fVslider22 (*fVslider22_)
#define fVslider23 (*fVslider23_)
#define fVslider24 (*fVslider24_)
#define fVslider25 (*fVslider25_)
#define fVslider26 (*fVslider26_)
#define fVslider27 (*fVslider27_)
#define fVslider28 (*fVslider28_)
#define fVslider29 (*fVslider29_)
	double fSlow0 = std::tan((fConst0 * double(fVslider0)));
	double fSlow1 = double(fVslider2);
	double fSlow2 = (std::pow(10.0, (0.0 - (0.050000000000000003 * double(fVslider1)))) / fSlow1);
	double fSlow3 = (1.0 / ((fSlow0 * (fSlow0 + fSlow2)) + 1.0));
	double fSlow4 = (2.0 * (mydsp_faustpower2_f(fSlow0) + -1.0));
	double fSlow5 = std::tan((fConst0 * double(fVslider3)));
	double fSlow6 = double(fVslider5);
	double fSlow7 = (std::pow(10.0, (0.0 - (0.050000000000000003 * double(fVslider4)))) / fSlow6);
	double fSlow8 = (1.0 / ((fSlow5 * (fSlow5 + fSlow7)) + 1.0));
	double fSlow9 = (2.0 * (mydsp_faustpower2_f(fSlow5) + -1.0));
	double fSlow10 = std::tan((fConst0 * double(fVslider6)));
	double fSlow11 = double(fVslider8);
	double fSlow12 = (std::pow(10.0, (0.0 - (0.050000000000000003 * double(fVslider7)))) / fSlow11);
	double fSlow13 = (1.0 / ((fSlow10 * (fSlow10 + fSlow12)) + 1.0));
	double fSlow14 = (2.0 * (mydsp_faustpower2_f(fSlow10) + -1.0));
	double fSlow15 = std::tan((fConst0 * double(fVslider9)));
	double fSlow16 = double(fVslider11);
	double fSlow17 = (std::pow(10.0, (0.0 - (0.050000000000000003 * double(fVslider10)))) / fSlow16);
	double fSlow18 = (1.0 / ((fSlow15 * (fSlow15 + fSlow17)) + 1.0));
	double fSlow19 = (2.0 * (mydsp_faustpower2_f(fSlow15) + -1.0));
	double fSlow20 = std::tan((fConst0 * double(fVslider12)));
	double fSlow21 = double(fVslider14);
	double fSlow22 = (std::pow(10.0, (0.0 - (0.050000000000000003 * double(fVslider13)))) / fSlow21);
	double fSlow23 = (1.0 / ((fSlow20 * (fSlow20 + fSlow22)) + 1.0));
	double fSlow24 = (2.0 * (mydsp_faustpower2_f(fSlow20) + -1.0));
	double fSlow25 = std::tan((fConst0 * double(fVslider15)));
	double fSlow26 = double(fVslider17);
	double fSlow27 = (std::pow(10.0, (0.0 - (0.050000000000000003 * double(fVslider16)))) / fSlow26);
	double fSlow28 = (1.0 / ((fSlow25 * (fSlow25 + fSlow27)) + 1.0));
	double fSlow29 = (2.0 * (mydsp_faustpower2_f(fSlow25) + -1.0));
	double fSlow30 = std::tan((fConst0 * double(fVslider18)));
	double fSlow31 = double(fVslider20);
	double fSlow32 = (std::pow(10.0, (0.0 - (0.050000000000000003 * double(fVslider19)))) / fSlow31);
	double fSlow33 = (1.0 / ((fSlow30 * (fSlow30 + fSlow32)) + 1.0));
	double fSlow34 = (2.0 * (mydsp_faustpower2_f(fSlow30) + -1.0));
	double fSlow35 = std::tan((fConst0 * double(fVslider21)));
	double fSlow36 = double(fVslider23);
	double fSlow37 = (std::pow(10.0, (0.0 - (0.050000000000000003 * double(fVslider22)))) / fSlow36);
	double fSlow38 = (1.0 / ((fSlow35 * (fSlow35 + fSlow37)) + 1.0));
	double fSlow39 = (2.0 * (mydsp_faustpower2_f(fSlow35) + -1.0));
	double fSlow40 = std::tan((fConst0 * double(fVslider24)));
	double fSlow41 = double(fVslider26);
	double fSlow42 = (std::pow(10.0, (0.0 - (0.050000000000000003 * double(fVslider25)))) / fSlow41);
	double fSlow43 = (1.0 / ((fSlow40 * (fSlow40 + fSlow42)) + 1.0));
	double fSlow44 = (2.0 * (mydsp_faustpower2_f(fSlow40) + -1.0));
	double fSlow45 = std::tan((fConst0 * double(fVslider27)));
	double fSlow46 = double(fVslider29);
	double fSlow47 = (std::pow(10.0, (0.0 - (0.050000000000000003 * double(fVslider28)))) / fSlow46);
	double fSlow48 = (1.0 / ((fSlow45 * (fSlow45 + fSlow47)) + 1.0));
	double fSlow49 = (2.0 * (mydsp_faustpower2_f(fSlow45) + -1.0));
	double fSlow50 = ((fSlow45 * (fSlow45 - fSlow47)) + 1.0);
	double fSlow51 = (1.0 / fSlow46);
	double fSlow52 = ((fSlow45 * (fSlow45 + fSlow51)) + 1.0);
	double fSlow53 = (1.0 - (fSlow45 * (fSlow51 - fSlow45)));
	double fSlow54 = ((fSlow40 * (fSlow40 - fSlow42)) + 1.0);
	double fSlow55 = (1.0 / fSlow41);
	double fSlow56 = ((fSlow40 * (fSlow40 + fSlow55)) + 1.0);
	double fSlow57 = (1.0 - (fSlow40 * (fSlow55 - fSlow40)));
	double fSlow58 = ((fSlow35 * (fSlow35 - fSlow37)) + 1.0);
	double fSlow59 = (1.0 / fSlow36);
	double fSlow60 = ((fSlow35 * (fSlow35 + fSlow59)) + 1.0);
	double fSlow61 = (1.0 - (fSlow35 * (fSlow59 - fSlow35)));
	double fSlow62 = ((fSlow30 * (fSlow30 - fSlow32)) + 1.0);
	double fSlow63 = (1.0 / fSlow31);
	double fSlow64 = ((fSlow30 * (fSlow30 + fSlow63)) + 1.0);
	double fSlow65 = (1.0 - (fSlow30 * (fSlow63 - fSlow30)));
	double fSlow66 = ((fSlow25 * (fSlow25 - fSlow27)) + 1.0);
	double fSlow67 = (1.0 / fSlow26);
	double fSlow68 = ((fSlow25 * (fSlow25 + fSlow67)) + 1.0);
	double fSlow69 = (1.0 - (fSlow25 * (fSlow67 - fSlow25)));
	double fSlow70 = ((fSlow20 * (fSlow20 - fSlow22)) + 1.0);
	double fSlow71 = (1.0 / fSlow21);
	double fSlow72 = ((fSlow20 * (fSlow20 + fSlow71)) + 1.0);
	double fSlow73 = (1.0 - (fSlow20 * (fSlow71 - fSlow20)));
	double fSlow74 = ((fSlow15 * (fSlow15 - fSlow17)) + 1.0);
	double fSlow75 = (1.0 / fSlow16);
	double fSlow76 = ((fSlow15 * (fSlow15 + fSlow75)) + 1.0);
	double fSlow77 = (1.0 - (fSlow15 * (fSlow75 - fSlow15)));
	double fSlow78 = ((fSlow10 * (fSlow10 - fSlow12)) + 1.0);
	double fSlow79 = (1.0 / fSlow11);
	double fSlow80 = ((fSlow10 * (fSlow10 + fSlow79)) + 1.0);
	double fSlow81 = (1.0 - (fSlow10 * (fSlow79 - fSlow10)));
	double fSlow82 = ((fSlow5 * (fSlow5 - fSlow7)) + 1.0);
	double fSlow83 = (1.0 / fSlow6);
	double fSlow84 = ((fSlow5 * (fSlow5 + fSlow83)) + 1.0);
	double fSlow85 = (1.0 - (fSlow5 * (fSlow83 - fSlow5)));
	double fSlow86 = ((fSlow0 * (fSlow0 - fSlow2)) + 1.0);
	double fSlow87 = (1.0 / fSlow1);
	double fSlow88 = ((fSlow0 * (fSlow0 + fSlow87)) + 1.0);
	double fSlow89 = (1.0 - (fSlow0 * (fSlow87 - fSlow0)));
	for (int i = 0; (i < count); i = (i + 1)) {
		double fTemp0 = (fSlow49 * fRec9[1]);
		fRec9[0] = (double(input0[i]) - (fSlow48 * ((fSlow50 * fRec9[2]) + fTemp0)));
		double fTemp1 = (fSlow44 * fRec8[1]);
		fRec8[0] = ((fSlow48 * ((fTemp0 + (fSlow52 * fRec9[0])) + (fSlow53 * fRec9[2]))) - (fSlow43 * ((fSlow54 * fRec8[2]) + fTemp1)));
		double fTemp2 = (fSlow39 * fRec7[1]);
		fRec7[0] = ((fSlow43 * ((fTemp1 + (fSlow56 * fRec8[0])) + (fSlow57 * fRec8[2]))) - (fSlow38 * ((fSlow58 * fRec7[2]) + fTemp2)));
		double fTemp3 = (fSlow34 * fRec6[1]);
		fRec6[0] = ((fSlow38 * ((fTemp2 + (fSlow60 * fRec7[0])) + (fSlow61 * fRec7[2]))) - (fSlow33 * ((fSlow62 * fRec6[2]) + fTemp3)));
		double fTemp4 = (fSlow29 * fRec5[1]);
		fRec5[0] = ((fSlow33 * ((fTemp3 + (fSlow64 * fRec6[0])) + (fSlow65 * fRec6[2]))) - (fSlow28 * ((fSlow66 * fRec5[2]) + fTemp4)));
		double fTemp5 = (fSlow24 * fRec4[1]);
		fRec4[0] = ((fSlow28 * ((fTemp4 + (fSlow68 * fRec5[0])) + (fSlow69 * fRec5[2]))) - (fSlow23 * ((fSlow70 * fRec4[2]) + fTemp5)));
		double fTemp6 = (fSlow19 * fRec3[1]);
		fRec3[0] = ((fSlow23 * ((fTemp5 + (fSlow72 * fRec4[0])) + (fSlow73 * fRec4[2]))) - (fSlow18 * ((fSlow74 * fRec3[2]) + fTemp6)));
		double fTemp7 = (fSlow14 * fRec2[1]);
		fRec2[0] = ((fSlow18 * ((fTemp6 + (fSlow76 * fRec3[0])) + (fSlow77 * fRec3[2]))) - (fSlow13 * ((fSlow78 * fRec2[2]) + fTemp7)));
		double fTemp8 = (fSlow9 * fRec1[1]);
		fRec1[0] = ((fSlow13 * ((fTemp7 + (fSlow80 * fRec2[0])) + (fSlow81 * fRec2[2]))) - (fSlow8 * ((fSlow82 * fRec1[2]) + fTemp8)));
		double fTemp9 = (fSlow4 * fRec0[1]);
		fRec0[0] = ((fSlow8 * ((fTemp8 + (fSlow84 * fRec1[0])) + (fSlow85 * fRec1[2]))) - (fSlow3 * ((fSlow86 * fRec0[2]) + fTemp9)));
		output0[i] = FAUSTFLOAT((fSlow3 * ((fTemp9 + (fSlow88 * fRec0[0])) + (fSlow89 * fRec0[2]))));
		fRec9[2] = fRec9[1];
		fRec9[1] = fRec9[0];
		fRec8[2] = fRec8[1];
		fRec8[1] = fRec8[0];
		fRec7[2] = fRec7[1];
		fRec7[1] = fRec7[0];
		fRec6[2] = fRec6[1];
		fRec6[1] = fRec6[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		fRec4[2] = fRec4[1];
		fRec4[1] = fRec4[0];
		fRec3[2] = fRec3[1];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fRec1[2] = fRec1[1];
		fRec1[1] = fRec1[0];
		fRec0[2] = fRec0[1];
		fRec0[1] = fRec0[0];
	}
#undef fVslider0
#undef fVslider1
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
#undef fVslider14
#undef fVslider15
#undef fVslider16
#undef fVslider17
#undef fVslider18
#undef fVslider19
#undef fVslider20
#undef fVslider21
#undef fVslider22
#undef fVslider23
#undef fVslider24
#undef fVslider25
#undef fVslider26
#undef fVslider27
#undef fVslider28
#undef fVslider29
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case QS125: 
		fVslider23_ = (float*)data; // , 50.0, 1.0, 100.0, 1.0 
		break;
	case QS16K: 
		fVslider2_ = (float*)data; // , 50.0, 1.0, 100.0, 1.0 
		break;
	case QS1K: 
		fVslider14_ = (float*)data; // , 50.0, 1.0, 100.0, 1.0 
		break;
	case QS250: 
		fVslider20_ = (float*)data; // , 50.0, 1.0, 100.0, 1.0 
		break;
	case QS2K: 
		fVslider11_ = (float*)data; // , 50.0, 1.0, 100.0, 1.0 
		break;
	case QS31_25: 
		fVslider29_ = (float*)data; // , 50.0, 1.0, 100.0, 1.0 
		break;
	case QS4K: 
		fVslider8_ = (float*)data; // , 50.0, 1.0, 100.0, 1.0 
		break;
	case QS500: 
		fVslider17_ = (float*)data; // , 50.0, 1.0, 100.0, 1.0 
		break;
	case QS62_5: 
		fVslider26_ = (float*)data; // , 50.0, 1.0, 100.0, 1.0 
		break;
	case QS8K: 
		fVslider5_ = (float*)data; // , 50.0, 1.0, 100.0, 1.0 
		break;
	case FREQ125: 
		fVslider21_ = (float*)data; // , 125.0, 20.0, 20000.0, 1.0 
		break;
	case FREQ16K: 
		fVslider0_ = (float*)data; // , 16000.0, 20.0, 20000.0, 1.0 
		break;
	case FREQ1K: 
		fVslider12_ = (float*)data; // , 1000.0, 20.0, 20000.0, 1.0 
		break;
	case FREQ250: 
		fVslider18_ = (float*)data; // , 250.0, 20.0, 20000.0, 1.0 
		break;
	case FREQ2K: 
		fVslider9_ = (float*)data; // , 2000.0, 20.0, 20000.0, 1.0 
		break;
	case FREQ31_25: 
		fVslider27_ = (float*)data; // , 31.0, 20.0, 20000.0, 1.0 
		break;
	case FREQ4K: 
		fVslider6_ = (float*)data; // , 4000.0, 20.0, 20000.0, 1.0 
		break;
	case FREQ500: 
		fVslider15_ = (float*)data; // , 500.0, 20.0, 20000.0, 1.0 
		break;
	case FREQ62_5: 
		fVslider24_ = (float*)data; // , 62.0, 20.0, 20000.0, 1.0 
		break;
	case FREQ8K: 
		fVslider3_ = (float*)data; // , 8000.0, 20.0, 20000.0, 1.0 
		break;
	case FS125: 
		fVslider22_ = (float*)data; // , 0.0, -50.0, 10.0, 0.10000000000000001 
		break;
	case FS16K: 
		fVslider1_ = (float*)data; // , 0.0, -50.0, 10.0, 0.10000000000000001 
		break;
	case FS1K: 
		fVslider13_ = (float*)data; // , 0.0, -50.0, 10.0, 0.10000000000000001 
		break;
	case FS250: 
		fVslider19_ = (float*)data; // , 0.0, -50.0, 10.0, 0.10000000000000001 
		break;
	case FS2K: 
		fVslider10_ = (float*)data; // , 0.0, -50.0, 10.0, 0.10000000000000001 
		break;
	case FS31_25: 
		fVslider28_ = (float*)data; // , 0.0, -50.0, 10.0, 0.10000000000000001 
		break;
	case FS4K: 
		fVslider7_ = (float*)data; // , 0.0, -50.0, 10.0, 0.10000000000000001 
		break;
	case FS500: 
		fVslider16_ = (float*)data; // , 0.0, -50.0, 10.0, 0.10000000000000001 
		break;
	case FS62_5: 
		fVslider25_ = (float*)data; // , 0.0, -50.0, 10.0, 0.10000000000000001 
		break;
	case FS8K: 
		fVslider4_ = (float*)data; // , 0.0, -50.0, 10.0, 0.10000000000000001 
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
   QS125, 
   QS16K, 
   QS1K, 
   QS250, 
   QS2K, 
   QS31_25, 
   QS4K, 
   QS500, 
   QS62_5, 
   QS8K, 
   FREQ125, 
   FREQ16K, 
   FREQ1K, 
   FREQ250, 
   FREQ2K, 
   FREQ31_25, 
   FREQ4K, 
   FREQ500, 
   FREQ62_5, 
   FREQ8K, 
   FS125, 
   FS16K, 
   FS1K, 
   FS250, 
   FS2K, 
   FS31_25, 
   FS4K, 
   FS500, 
   FS62_5, 
   FS8K, 
} PortIndex;
*/

} // end namespace selecteq
