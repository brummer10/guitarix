// generated from file '../src/LV2/faust/selecteq.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)


namespace selecteq {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fConst0;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT	*fslider4_;
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT	*fslider5_;
	FAUSTFLOAT 	fslider6;
	FAUSTFLOAT	*fslider6_;
	FAUSTFLOAT 	fslider7;
	FAUSTFLOAT	*fslider7_;
	FAUSTFLOAT 	fslider8;
	FAUSTFLOAT	*fslider8_;
	FAUSTFLOAT 	fslider9;
	FAUSTFLOAT	*fslider9_;
	FAUSTFLOAT 	fslider10;
	FAUSTFLOAT	*fslider10_;
	FAUSTFLOAT 	fslider11;
	FAUSTFLOAT	*fslider11_;
	FAUSTFLOAT 	fslider12;
	FAUSTFLOAT	*fslider12_;
	FAUSTFLOAT 	fslider13;
	FAUSTFLOAT	*fslider13_;
	FAUSTFLOAT 	fslider14;
	FAUSTFLOAT	*fslider14_;
	FAUSTFLOAT 	fslider15;
	FAUSTFLOAT	*fslider15_;
	FAUSTFLOAT 	fslider16;
	FAUSTFLOAT	*fslider16_;
	FAUSTFLOAT 	fslider17;
	FAUSTFLOAT	*fslider17_;
	FAUSTFLOAT 	fslider18;
	FAUSTFLOAT	*fslider18_;
	FAUSTFLOAT 	fslider19;
	FAUSTFLOAT	*fslider19_;
	FAUSTFLOAT 	fslider20;
	FAUSTFLOAT	*fslider20_;
	FAUSTFLOAT 	fslider21;
	FAUSTFLOAT	*fslider21_;
	FAUSTFLOAT 	fslider22;
	FAUSTFLOAT	*fslider22_;
	FAUSTFLOAT 	fslider23;
	FAUSTFLOAT	*fslider23_;
	FAUSTFLOAT 	fslider24;
	FAUSTFLOAT	*fslider24_;
	FAUSTFLOAT 	fslider25;
	FAUSTFLOAT	*fslider25_;
	FAUSTFLOAT 	fslider26;
	FAUSTFLOAT	*fslider26_;
	FAUSTFLOAT 	fslider27;
	FAUSTFLOAT	*fslider27_;
	FAUSTFLOAT 	fslider28;
	FAUSTFLOAT	*fslider28_;
	FAUSTFLOAT 	fslider29;
	FAUSTFLOAT	*fslider29_;
	double 	fRec9[3];
	double 	fRec8[3];
	double 	fRec7[3];
	double 	fRec6[3];
	double 	fRec5[3];
	double 	fRec4[3];
	double 	fRec3[3];
	double 	fRec2[3];
	double 	fRec1[3];
	double 	fRec0[3];

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
	for (int i=0; i<3; i++) fRec9[i] = 0;
	for (int i=0; i<3; i++) fRec8[i] = 0;
	for (int i=0; i<3; i++) fRec7[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<3; i++) fRec4[i] = 0;
	for (int i=0; i<3; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<3; i++) fRec1[i] = 0;
	for (int i=0; i<3; i++) fRec0[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = (3.141592653589793 / min(1.92e+05, max(1.0, (double)fSamplingFreq)));
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
#define fslider14 (*fslider14_)
#define fslider15 (*fslider15_)
#define fslider16 (*fslider16_)
#define fslider17 (*fslider17_)
#define fslider18 (*fslider18_)
#define fslider19 (*fslider19_)
#define fslider20 (*fslider20_)
#define fslider21 (*fslider21_)
#define fslider22 (*fslider22_)
#define fslider23 (*fslider23_)
#define fslider24 (*fslider24_)
#define fslider25 (*fslider25_)
#define fslider26 (*fslider26_)
#define fslider27 (*fslider27_)
#define fslider28 (*fslider28_)
#define fslider29 (*fslider29_)
	double 	fSlow0 = tan((fConst0 * double(fslider0)));
	double 	fSlow1 = (2 * (faustpower<2>(fSlow0) - 1));
	double 	fSlow2 = double(fslider1);
	double 	fSlow3 = (pow(10,(0.05 * (0 - double(fslider2)))) / fSlow2);
	double 	fSlow4 = (1 + (fSlow0 * (fSlow0 - fSlow3)));
	double 	fSlow5 = (1.0 / (1 + (fSlow0 * (fSlow0 + fSlow3))));
	double 	fSlow6 = tan((fConst0 * double(fslider3)));
	double 	fSlow7 = (2 * (faustpower<2>(fSlow6) - 1));
	double 	fSlow8 = double(fslider4);
	double 	fSlow9 = (pow(10,(0.05 * (0 - double(fslider5)))) / fSlow8);
	double 	fSlow10 = (1 + (fSlow6 * (fSlow6 - fSlow9)));
	double 	fSlow11 = (1.0 / (1 + (fSlow6 * (fSlow6 + fSlow9))));
	double 	fSlow12 = tan((fConst0 * double(fslider6)));
	double 	fSlow13 = (2 * (faustpower<2>(fSlow12) - 1));
	double 	fSlow14 = double(fslider7);
	double 	fSlow15 = (pow(10,(0.05 * (0 - double(fslider8)))) / fSlow14);
	double 	fSlow16 = (1 + (fSlow12 * (fSlow12 - fSlow15)));
	double 	fSlow17 = (1.0 / (1 + (fSlow12 * (fSlow12 + fSlow15))));
	double 	fSlow18 = tan((fConst0 * double(fslider9)));
	double 	fSlow19 = (2 * (faustpower<2>(fSlow18) - 1));
	double 	fSlow20 = double(fslider10);
	double 	fSlow21 = (pow(10,(0.05 * (0 - double(fslider11)))) / fSlow20);
	double 	fSlow22 = (1 + (fSlow18 * (fSlow18 - fSlow21)));
	double 	fSlow23 = (1.0 / (1 + (fSlow18 * (fSlow18 + fSlow21))));
	double 	fSlow24 = tan((fConst0 * double(fslider12)));
	double 	fSlow25 = (2 * (faustpower<2>(fSlow24) - 1));
	double 	fSlow26 = double(fslider13);
	double 	fSlow27 = (pow(10,(0.05 * (0 - double(fslider14)))) / fSlow26);
	double 	fSlow28 = (1 + (fSlow24 * (fSlow24 - fSlow27)));
	double 	fSlow29 = (1.0 / (1 + (fSlow24 * (fSlow24 + fSlow27))));
	double 	fSlow30 = tan((fConst0 * double(fslider15)));
	double 	fSlow31 = (2 * (faustpower<2>(fSlow30) - 1));
	double 	fSlow32 = double(fslider16);
	double 	fSlow33 = (pow(10,(0.05 * (0 - double(fslider17)))) / fSlow32);
	double 	fSlow34 = (1 + (fSlow30 * (fSlow30 - fSlow33)));
	double 	fSlow35 = (1.0 / (1 + (fSlow30 * (fSlow30 + fSlow33))));
	double 	fSlow36 = tan((fConst0 * double(fslider18)));
	double 	fSlow37 = (2 * (faustpower<2>(fSlow36) - 1));
	double 	fSlow38 = double(fslider19);
	double 	fSlow39 = (pow(10,(0.05 * (0 - double(fslider20)))) / fSlow38);
	double 	fSlow40 = (1 + (fSlow36 * (fSlow36 - fSlow39)));
	double 	fSlow41 = (1.0 / (1 + (fSlow36 * (fSlow36 + fSlow39))));
	double 	fSlow42 = tan((fConst0 * double(fslider21)));
	double 	fSlow43 = (2 * (faustpower<2>(fSlow42) - 1));
	double 	fSlow44 = double(fslider22);
	double 	fSlow45 = (pow(10,(0.05 * (0 - double(fslider23)))) / fSlow44);
	double 	fSlow46 = (1 + (fSlow42 * (fSlow42 - fSlow45)));
	double 	fSlow47 = (1.0 / (1 + (fSlow42 * (fSlow42 + fSlow45))));
	double 	fSlow48 = tan((fConst0 * double(fslider24)));
	double 	fSlow49 = (2 * (faustpower<2>(fSlow48) - 1));
	double 	fSlow50 = double(fslider25);
	double 	fSlow51 = (pow(10,(0.05 * (0 - double(fslider26)))) / fSlow50);
	double 	fSlow52 = (1 + (fSlow48 * (fSlow48 - fSlow51)));
	double 	fSlow53 = (1.0 / (1 + (fSlow48 * (fSlow48 + fSlow51))));
	double 	fSlow54 = tan((fConst0 * double(fslider27)));
	double 	fSlow55 = (2 * (faustpower<2>(fSlow54) - 1));
	double 	fSlow56 = double(fslider28);
	double 	fSlow57 = (pow(10,(0.05 * (0 - double(fslider29)))) / fSlow56);
	double 	fSlow58 = (1 + (fSlow54 * (fSlow54 - fSlow57)));
	double 	fSlow59 = (1.0 / (1 + (fSlow54 * (fSlow54 + fSlow57))));
	double 	fSlow60 = (1.0 / fSlow56);
	double 	fSlow61 = (1 + (fSlow54 * (fSlow54 - fSlow60)));
	double 	fSlow62 = (1 + (fSlow54 * (fSlow54 + fSlow60)));
	double 	fSlow63 = (1.0 / fSlow50);
	double 	fSlow64 = (1 + (fSlow48 * (fSlow48 - fSlow63)));
	double 	fSlow65 = (1 + (fSlow48 * (fSlow48 + fSlow63)));
	double 	fSlow66 = (1.0 / fSlow44);
	double 	fSlow67 = (1 + (fSlow42 * (fSlow42 - fSlow66)));
	double 	fSlow68 = (1 + (fSlow42 * (fSlow42 + fSlow66)));
	double 	fSlow69 = (1.0 / fSlow38);
	double 	fSlow70 = (1 + (fSlow36 * (fSlow36 - fSlow69)));
	double 	fSlow71 = (1 + (fSlow36 * (fSlow36 + fSlow69)));
	double 	fSlow72 = (1.0 / fSlow32);
	double 	fSlow73 = (1 + (fSlow30 * (fSlow30 - fSlow72)));
	double 	fSlow74 = (1 + (fSlow30 * (fSlow30 + fSlow72)));
	double 	fSlow75 = (1.0 / fSlow26);
	double 	fSlow76 = (1 + (fSlow24 * (fSlow24 - fSlow75)));
	double 	fSlow77 = (1 + (fSlow24 * (fSlow24 + fSlow75)));
	double 	fSlow78 = (1.0 / fSlow20);
	double 	fSlow79 = (1 + (fSlow18 * (fSlow18 - fSlow78)));
	double 	fSlow80 = (1 + (fSlow18 * (fSlow18 + fSlow78)));
	double 	fSlow81 = (1.0 / fSlow14);
	double 	fSlow82 = (1 + (fSlow12 * (fSlow12 - fSlow81)));
	double 	fSlow83 = (1 + (fSlow12 * (fSlow12 + fSlow81)));
	double 	fSlow84 = (1.0 / fSlow8);
	double 	fSlow85 = (1 + (fSlow6 * (fSlow6 - fSlow84)));
	double 	fSlow86 = (1 + (fSlow6 * (fSlow6 + fSlow84)));
	double 	fSlow87 = (1.0 / fSlow2);
	double 	fSlow88 = (1 + (fSlow0 * (fSlow0 - fSlow87)));
	double 	fSlow89 = (1 + (fSlow0 * (fSlow0 + fSlow87)));
	for (int i=0; i<count; i++) {
		double fTemp0 = (fSlow1 * fRec0[1]);
		double fTemp1 = (fSlow7 * fRec1[1]);
		double fTemp2 = (fSlow13 * fRec2[1]);
		double fTemp3 = (fSlow19 * fRec3[1]);
		double fTemp4 = (fSlow25 * fRec4[1]);
		double fTemp5 = (fSlow31 * fRec5[1]);
		double fTemp6 = (fSlow37 * fRec6[1]);
		double fTemp7 = (fSlow43 * fRec7[1]);
		double fTemp8 = (fSlow49 * fRec8[1]);
		double fTemp9 = (fSlow55 * fRec9[1]);
		fRec9[0] = ((double)input0[i] - (fSlow59 * ((fSlow58 * fRec9[2]) + fTemp9)));
		fRec8[0] = ((fSlow59 * (fTemp9 + ((fSlow62 * fRec9[0]) + (fSlow61 * fRec9[2])))) - (fSlow53 * ((fSlow52 * fRec8[2]) + fTemp8)));
		fRec7[0] = ((fSlow53 * (fTemp8 + ((fSlow65 * fRec8[0]) + (fSlow64 * fRec8[2])))) - (fSlow47 * ((fSlow46 * fRec7[2]) + fTemp7)));
		fRec6[0] = ((fSlow47 * (fTemp7 + ((fSlow68 * fRec7[0]) + (fSlow67 * fRec7[2])))) - (fSlow41 * ((fSlow40 * fRec6[2]) + fTemp6)));
		fRec5[0] = ((fSlow41 * (fTemp6 + ((fSlow71 * fRec6[0]) + (fSlow70 * fRec6[2])))) - (fSlow35 * ((fSlow34 * fRec5[2]) + fTemp5)));
		fRec4[0] = ((fSlow35 * (fTemp5 + ((fSlow74 * fRec5[0]) + (fSlow73 * fRec5[2])))) - (fSlow29 * ((fSlow28 * fRec4[2]) + fTemp4)));
		fRec3[0] = ((fSlow29 * (fTemp4 + ((fSlow77 * fRec4[0]) + (fSlow76 * fRec4[2])))) - (fSlow23 * ((fSlow22 * fRec3[2]) + fTemp3)));
		fRec2[0] = ((fSlow23 * (fTemp3 + ((fSlow80 * fRec3[0]) + (fSlow79 * fRec3[2])))) - (fSlow17 * ((fSlow16 * fRec2[2]) + fTemp2)));
		fRec1[0] = ((fSlow17 * (fTemp2 + ((fSlow83 * fRec2[0]) + (fSlow82 * fRec2[2])))) - (fSlow11 * ((fSlow10 * fRec1[2]) + fTemp1)));
		fRec0[0] = ((fSlow11 * (fTemp1 + ((fSlow86 * fRec1[0]) + (fSlow85 * fRec1[2])))) - (fSlow5 * ((fSlow4 * fRec0[2]) + fTemp0)));
		output0[i] = (FAUSTFLOAT)(fSlow5 * (fTemp0 + ((fSlow89 * fRec0[0]) + (fSlow88 * fRec0[2]))));
		// post processing
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
		fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
		fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
	}
#undef fslider0
#undef fslider1
#undef fslider2
#undef fslider3
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
#undef fslider14
#undef fslider15
#undef fslider16
#undef fslider17
#undef fslider18
#undef fslider19
#undef fslider20
#undef fslider21
#undef fslider22
#undef fslider23
#undef fslider24
#undef fslider25
#undef fslider26
#undef fslider27
#undef fslider28
#undef fslider29
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
		fslider22_ = (float*)data; // , 5e+01, 1.0, 1e+02, 1.0 
		break;
	case QS16K: 
		fslider1_ = (float*)data; // , 5e+01, 1.0, 1e+02, 1.0 
		break;
	case QS1K: 
		fslider13_ = (float*)data; // , 5e+01, 1.0, 1e+02, 1.0 
		break;
	case QS250: 
		fslider19_ = (float*)data; // , 5e+01, 1.0, 1e+02, 1.0 
		break;
	case QS2K: 
		fslider10_ = (float*)data; // , 5e+01, 1.0, 1e+02, 1.0 
		break;
	case QS31_25: 
		fslider28_ = (float*)data; // , 5e+01, 1.0, 1e+02, 1.0 
		break;
	case QS4K: 
		fslider7_ = (float*)data; // , 5e+01, 1.0, 1e+02, 1.0 
		break;
	case QS500: 
		fslider16_ = (float*)data; // , 5e+01, 1.0, 1e+02, 1.0 
		break;
	case QS62_5: 
		fslider25_ = (float*)data; // , 5e+01, 1.0, 1e+02, 1.0 
		break;
	case QS8K: 
		fslider4_ = (float*)data; // , 5e+01, 1.0, 1e+02, 1.0 
		break;
	case FREQ125: 
		fslider21_ = (float*)data; // , 125.0, 2e+01, 2e+04, 1.0 
		break;
	case FREQ16K: 
		fslider0_ = (float*)data; // , 1.6e+04, 2e+01, 2e+04, 1.0 
		break;
	case FREQ1K: 
		fslider12_ = (float*)data; // , 1e+03, 2e+01, 2e+04, 1.0 
		break;
	case FREQ250: 
		fslider18_ = (float*)data; // , 2.5e+02, 2e+01, 2e+04, 1.0 
		break;
	case FREQ2K: 
		fslider9_ = (float*)data; // , 2e+03, 2e+01, 2e+04, 1.0 
		break;
	case FREQ31_25: 
		fslider27_ = (float*)data; // , 31.0, 2e+01, 2e+04, 1.0 
		break;
	case FREQ4K: 
		fslider6_ = (float*)data; // , 4e+03, 2e+01, 2e+04, 1.0 
		break;
	case FREQ500: 
		fslider15_ = (float*)data; // , 5e+02, 2e+01, 2e+04, 1.0 
		break;
	case FREQ62_5: 
		fslider24_ = (float*)data; // , 62.0, 2e+01, 2e+04, 1.0 
		break;
	case FREQ8K: 
		fslider3_ = (float*)data; // , 8e+03, 2e+01, 2e+04, 1.0 
		break;
	case FS125: 
		fslider23_ = (float*)data; // , 0.0, -5e+01, 1e+01, 0.1 
		break;
	case FS16K: 
		fslider2_ = (float*)data; // , 0.0, -5e+01, 1e+01, 0.1 
		break;
	case FS1K: 
		fslider14_ = (float*)data; // , 0.0, -5e+01, 1e+01, 0.1 
		break;
	case FS250: 
		fslider20_ = (float*)data; // , 0.0, -5e+01, 1e+01, 0.1 
		break;
	case FS2K: 
		fslider11_ = (float*)data; // , 0.0, -5e+01, 1e+01, 0.1 
		break;
	case FS31_25: 
		fslider29_ = (float*)data; // , 0.0, -5e+01, 1e+01, 0.1 
		break;
	case FS4K: 
		fslider8_ = (float*)data; // , 0.0, -5e+01, 1e+01, 0.1 
		break;
	case FS500: 
		fslider17_ = (float*)data; // , 0.0, -5e+01, 1e+01, 0.1 
		break;
	case FS62_5: 
		fslider26_ = (float*)data; // , 0.0, -5e+01, 1e+01, 0.1 
		break;
	case FS8K: 
		fslider5_ = (float*)data; // , 0.0, -5e+01, 1e+01, 0.1 
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
