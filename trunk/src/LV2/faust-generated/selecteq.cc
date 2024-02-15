// generated from file '../src/LV2/faust/selecteq.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace selecteq {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fConst0;
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
	for (int l0 = 0; l0 < 3; l0 = l0 + 1) fRec9[l0] = 0.0;
	for (int l1 = 0; l1 < 3; l1 = l1 + 1) fRec8[l1] = 0.0;
	for (int l2 = 0; l2 < 3; l2 = l2 + 1) fRec7[l2] = 0.0;
	for (int l3 = 0; l3 < 3; l3 = l3 + 1) fRec6[l3] = 0.0;
	for (int l4 = 0; l4 < 3; l4 = l4 + 1) fRec5[l4] = 0.0;
	for (int l5 = 0; l5 < 3; l5 = l5 + 1) fRec4[l5] = 0.0;
	for (int l6 = 0; l6 < 3; l6 = l6 + 1) fRec3[l6] = 0.0;
	for (int l7 = 0; l7 < 3; l7 = l7 + 1) fRec2[l7] = 0.0;
	for (int l8 = 0; l8 < 3; l8 = l8 + 1) fRec1[l8] = 0.0;
	for (int l9 = 0; l9 < 3; l9 = l9 + 1) fRec0[l9] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = 3.141592653589793 / std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
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
	double fSlow0 = std::tan(fConst0 * double(fVslider0));
	double fSlow1 = 2.0 * (mydsp_faustpower2_f(fSlow0) + -1.0);
	double fSlow2 = double(fVslider1);
	double fSlow3 = double(fVslider2);
	double fSlow4 = std::pow(1e+01, -(0.05 * fSlow3)) / fSlow2;
	double fSlow5 = fSlow0 * (fSlow0 - fSlow4) + 1.0;
	double fSlow6 = 1.0 / (fSlow0 * (fSlow4 + fSlow0) + 1.0);
	double fSlow7 = std::tan(fConst0 * double(fVslider3));
	double fSlow8 = 2.0 * (mydsp_faustpower2_f(fSlow7) + -1.0);
	double fSlow9 = double(fVslider4);
	double fSlow10 = std::pow(1e+01, -(0.05 * double(fVslider5))) / fSlow9;
	double fSlow11 = fSlow7 * (fSlow7 - fSlow10) + 1.0;
	double fSlow12 = 1.0 / (fSlow7 * (fSlow10 + fSlow7) + 1.0);
	double fSlow13 = std::tan(fConst0 * double(fVslider6));
	double fSlow14 = 2.0 * (mydsp_faustpower2_f(fSlow13) + -1.0);
	double fSlow15 = double(fVslider7);
	double fSlow16 = std::pow(1e+01, -(0.05 * double(fVslider8))) / fSlow15;
	double fSlow17 = fSlow13 * (fSlow13 - fSlow16) + 1.0;
	double fSlow18 = 1.0 / (fSlow13 * (fSlow16 + fSlow13) + 1.0);
	double fSlow19 = std::tan(fConst0 * double(fVslider9));
	double fSlow20 = 2.0 * (mydsp_faustpower2_f(fSlow19) + -1.0);
	double fSlow21 = double(fVslider10);
	double fSlow22 = std::pow(1e+01, -(0.05 * double(fVslider11))) / fSlow21;
	double fSlow23 = fSlow19 * (fSlow19 - fSlow22) + 1.0;
	double fSlow24 = 1.0 / (fSlow19 * (fSlow22 + fSlow19) + 1.0);
	double fSlow25 = std::tan(fConst0 * double(fVslider12));
	double fSlow26 = 2.0 * (mydsp_faustpower2_f(fSlow25) + -1.0);
	double fSlow27 = double(fVslider13);
	double fSlow28 = std::pow(1e+01, -(0.05 * double(fVslider14))) / fSlow27;
	double fSlow29 = fSlow25 * (fSlow25 - fSlow28) + 1.0;
	double fSlow30 = 1.0 / (fSlow25 * (fSlow28 + fSlow25) + 1.0);
	double fSlow31 = std::tan(fConst0 * double(fVslider15));
	double fSlow32 = 2.0 * (mydsp_faustpower2_f(fSlow31) + -1.0);
	double fSlow33 = double(fVslider16);
	double fSlow34 = std::pow(1e+01, -(0.05 * double(fVslider17))) / fSlow33;
	double fSlow35 = fSlow31 * (fSlow31 - fSlow34) + 1.0;
	double fSlow36 = 1.0 / (fSlow31 * (fSlow34 + fSlow31) + 1.0);
	double fSlow37 = std::tan(fConst0 * double(fVslider18));
	double fSlow38 = 2.0 * (mydsp_faustpower2_f(fSlow37) + -1.0);
	double fSlow39 = double(fVslider19);
	double fSlow40 = std::pow(1e+01, -(0.05 * double(fVslider20))) / fSlow39;
	double fSlow41 = fSlow37 * (fSlow37 - fSlow40) + 1.0;
	double fSlow42 = 1.0 / (fSlow37 * (fSlow40 + fSlow37) + 1.0);
	double fSlow43 = std::tan(fConst0 * double(fVslider21));
	double fSlow44 = 2.0 * (mydsp_faustpower2_f(fSlow43) + -1.0);
	double fSlow45 = double(fVslider22);
	double fSlow46 = std::pow(1e+01, -(0.05 * double(fVslider23))) / fSlow45;
	double fSlow47 = fSlow43 * (fSlow43 - fSlow46) + 1.0;
	double fSlow48 = 1.0 / (fSlow43 * (fSlow46 + fSlow43) + 1.0);
	double fSlow49 = std::tan(fConst0 * double(fVslider24));
	double fSlow50 = 2.0 * (mydsp_faustpower2_f(fSlow49) + -1.0);
	double fSlow51 = double(fVslider25);
	double fSlow52 = std::pow(1e+01, -(0.05 * double(fVslider26))) / fSlow51;
	double fSlow53 = fSlow49 * (fSlow49 - fSlow52) + 1.0;
	double fSlow54 = 1.0 / (fSlow49 * (fSlow52 + fSlow49) + 1.0);
	double fSlow55 = std::tan(fConst0 * double(fVslider27));
	double fSlow56 = 2.0 * (mydsp_faustpower2_f(fSlow55) + -1.0);
	double fSlow57 = double(fVslider28);
	double fSlow58 = std::pow(1e+01, -(0.05 * double(fVslider29))) / fSlow57;
	double fSlow59 = fSlow55 * (fSlow55 - fSlow58) + 1.0;
	double fSlow60 = 1.0 / (fSlow55 * (fSlow58 + fSlow55) + 1.0);
	double fSlow61 = 1.0 / fSlow57;
	double fSlow62 = 1.0 - fSlow55 * (fSlow61 - fSlow55);
	double fSlow63 = fSlow55 * (fSlow61 + fSlow55) + 1.0;
	double fSlow64 = 1.0 / fSlow51;
	double fSlow65 = 1.0 - fSlow49 * (fSlow64 - fSlow49);
	double fSlow66 = fSlow49 * (fSlow64 + fSlow49) + 1.0;
	double fSlow67 = 1.0 / fSlow45;
	double fSlow68 = 1.0 - fSlow43 * (fSlow67 - fSlow43);
	double fSlow69 = fSlow43 * (fSlow67 + fSlow43) + 1.0;
	double fSlow70 = 1.0 / fSlow39;
	double fSlow71 = 1.0 - fSlow37 * (fSlow70 - fSlow37);
	double fSlow72 = fSlow37 * (fSlow70 + fSlow37) + 1.0;
	double fSlow73 = 1.0 / fSlow33;
	double fSlow74 = 1.0 - fSlow31 * (fSlow73 - fSlow31);
	double fSlow75 = fSlow31 * (fSlow73 + fSlow31) + 1.0;
	double fSlow76 = 1.0 / fSlow27;
	double fSlow77 = 1.0 - fSlow25 * (fSlow76 - fSlow25);
	double fSlow78 = fSlow25 * (fSlow76 + fSlow25) + 1.0;
	double fSlow79 = 1.0 / fSlow21;
	double fSlow80 = 1.0 - fSlow19 * (fSlow79 - fSlow19);
	double fSlow81 = fSlow19 * (fSlow79 + fSlow19) + 1.0;
	double fSlow82 = 1.0 / fSlow15;
	double fSlow83 = 1.0 - fSlow13 * (fSlow82 - fSlow13);
	double fSlow84 = fSlow13 * (fSlow82 + fSlow13) + 1.0;
	double fSlow85 = 1.0 / fSlow9;
	double fSlow86 = 1.0 - fSlow7 * (fSlow85 - fSlow7);
	double fSlow87 = fSlow7 * (fSlow85 + fSlow7) + 1.0;
	double fSlow88 = 1.0 / fSlow2;
	double fSlow89 = 1.0 - fSlow0 * (fSlow88 - fSlow0);
	double fSlow90 = fSlow0 * (fSlow88 + fSlow0) + 1.0;
	double fSlow91 = 1.0 / (fSlow0 * (std::pow(1e+01, -0.05 * fSlow3) / fSlow2 + fSlow0) + 1.0);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		double fTemp0 = fSlow1 * fRec0[1];
		double fTemp1 = fSlow8 * fRec1[1];
		double fTemp2 = fSlow14 * fRec2[1];
		double fTemp3 = fSlow20 * fRec3[1];
		double fTemp4 = fSlow26 * fRec4[1];
		double fTemp5 = fSlow32 * fRec5[1];
		double fTemp6 = fSlow38 * fRec6[1];
		double fTemp7 = fSlow44 * fRec7[1];
		double fTemp8 = fSlow50 * fRec8[1];
		double fTemp9 = fSlow56 * fRec9[1];
		fRec9[0] = double(input0[i0]) - fSlow60 * (fSlow59 * fRec9[2] + fTemp9);
		fRec8[0] = fSlow60 * (fTemp9 + fSlow63 * fRec9[0] + fSlow62 * fRec9[2]) - fSlow54 * (fSlow53 * fRec8[2] + fTemp8);
		fRec7[0] = fSlow54 * (fTemp8 + fSlow66 * fRec8[0] + fSlow65 * fRec8[2]) - fSlow48 * (fSlow47 * fRec7[2] + fTemp7);
		fRec6[0] = fSlow48 * (fTemp7 + fSlow69 * fRec7[0] + fSlow68 * fRec7[2]) - fSlow42 * (fSlow41 * fRec6[2] + fTemp6);
		fRec5[0] = fSlow42 * (fTemp6 + fSlow72 * fRec6[0] + fSlow71 * fRec6[2]) - fSlow36 * (fSlow35 * fRec5[2] + fTemp5);
		fRec4[0] = fSlow36 * (fTemp5 + fSlow75 * fRec5[0] + fSlow74 * fRec5[2]) - fSlow30 * (fSlow29 * fRec4[2] + fTemp4);
		fRec3[0] = fSlow30 * (fTemp4 + fSlow78 * fRec4[0] + fSlow77 * fRec4[2]) - fSlow24 * (fSlow23 * fRec3[2] + fTemp3);
		fRec2[0] = fSlow24 * (fTemp3 + fSlow81 * fRec3[0] + fSlow80 * fRec3[2]) - fSlow18 * (fSlow17 * fRec2[2] + fTemp2);
		fRec1[0] = fSlow18 * (fTemp2 + fSlow84 * fRec2[0] + fSlow83 * fRec2[2]) - fSlow12 * (fSlow11 * fRec1[2] + fTemp1);
		fRec0[0] = fSlow12 * (fTemp1 + fSlow87 * fRec1[0] + fSlow86 * fRec1[2]) - fSlow6 * (fSlow5 * fRec0[2] + fTemp0);
		output0[i0] = FAUSTFLOAT(fSlow91 * (fTemp0 + fSlow90 * fRec0[0] + fSlow89 * fRec0[2]));
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
		fVslider22_ = (float*)data; // , 5e+01, 1.0, 1e+02, 1.0 
		break;
	case QS16K: 
		fVslider1_ = (float*)data; // , 5e+01, 1.0, 1e+02, 1.0 
		break;
	case QS1K: 
		fVslider13_ = (float*)data; // , 5e+01, 1.0, 1e+02, 1.0 
		break;
	case QS250: 
		fVslider19_ = (float*)data; // , 5e+01, 1.0, 1e+02, 1.0 
		break;
	case QS2K: 
		fVslider10_ = (float*)data; // , 5e+01, 1.0, 1e+02, 1.0 
		break;
	case QS31_25: 
		fVslider28_ = (float*)data; // , 5e+01, 1.0, 1e+02, 1.0 
		break;
	case QS4K: 
		fVslider7_ = (float*)data; // , 5e+01, 1.0, 1e+02, 1.0 
		break;
	case QS500: 
		fVslider16_ = (float*)data; // , 5e+01, 1.0, 1e+02, 1.0 
		break;
	case QS62_5: 
		fVslider25_ = (float*)data; // , 5e+01, 1.0, 1e+02, 1.0 
		break;
	case QS8K: 
		fVslider4_ = (float*)data; // , 5e+01, 1.0, 1e+02, 1.0 
		break;
	case FREQ125: 
		fVslider21_ = (float*)data; // , 125.0, 2e+01, 2e+04, 1.0 
		break;
	case FREQ16K: 
		fVslider0_ = (float*)data; // , 1.6e+04, 2e+01, 2e+04, 1.0 
		break;
	case FREQ1K: 
		fVslider12_ = (float*)data; // , 1e+03, 2e+01, 2e+04, 1.0 
		break;
	case FREQ250: 
		fVslider18_ = (float*)data; // , 2.5e+02, 2e+01, 2e+04, 1.0 
		break;
	case FREQ2K: 
		fVslider9_ = (float*)data; // , 2e+03, 2e+01, 2e+04, 1.0 
		break;
	case FREQ31_25: 
		fVslider27_ = (float*)data; // , 31.0, 2e+01, 2e+04, 1.0 
		break;
	case FREQ4K: 
		fVslider6_ = (float*)data; // , 4e+03, 2e+01, 2e+04, 1.0 
		break;
	case FREQ500: 
		fVslider15_ = (float*)data; // , 5e+02, 2e+01, 2e+04, 1.0 
		break;
	case FREQ62_5: 
		fVslider24_ = (float*)data; // , 62.0, 2e+01, 2e+04, 1.0 
		break;
	case FREQ8K: 
		fVslider3_ = (float*)data; // , 8e+03, 2e+01, 2e+04, 1.0 
		break;
	case FS125: 
		fVslider23_ = (float*)data; // , 0.0, -5e+01, 1e+01, 0.1 
		break;
	case FS16K: 
		fVslider2_ = (float*)data; // , 0.0, -5e+01, 1e+01, 0.1 
		break;
	case FS1K: 
		fVslider14_ = (float*)data; // , 0.0, -5e+01, 1e+01, 0.1 
		break;
	case FS250: 
		fVslider20_ = (float*)data; // , 0.0, -5e+01, 1e+01, 0.1 
		break;
	case FS2K: 
		fVslider11_ = (float*)data; // , 0.0, -5e+01, 1e+01, 0.1 
		break;
	case FS31_25: 
		fVslider29_ = (float*)data; // , 0.0, -5e+01, 1e+01, 0.1 
		break;
	case FS4K: 
		fVslider8_ = (float*)data; // , 0.0, -5e+01, 1e+01, 0.1 
		break;
	case FS500: 
		fVslider17_ = (float*)data; // , 0.0, -5e+01, 1e+01, 0.1 
		break;
	case FS62_5: 
		fVslider26_ = (float*)data; // , 0.0, -5e+01, 1e+01, 0.1 
		break;
	case FS8K: 
		fVslider5_ = (float*)data; // , 0.0, -5e+01, 1e+01, 0.1 
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
