// generated from file '../src/LV2/faust/mbc.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)


namespace mbc {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	double 	fConst0;
	double 	fConst1;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fConst2;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fVec0[2];
	double 	fRec15[2];
	double 	fRec14[3];
	double 	fVec1[2];
	double 	fRec13[2];
	double 	fRec12[3];
	double 	fVec2[2];
	double 	fRec11[2];
	double 	fRec10[3];
	double 	fVec3[2];
	double 	fRec9[2];
	double 	fRec8[3];
	double 	fRec4[2];
	int 	iRec5[2];
	double 	fRec6[2];
	FAUSTFLOAT 	fbargraph0;
	FAUSTFLOAT	*fbargraph0_;
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT	*fslider4_;
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT	*fslider5_;
	FAUSTFLOAT 	fslider6;
	FAUSTFLOAT	*fslider6_;
	double 	fRec18[2];
	double 	fRec17[2];
	FAUSTFLOAT 	fslider7;
	FAUSTFLOAT	*fslider7_;
	double 	fConst3;
	FAUSTFLOAT 	fslider8;
	FAUSTFLOAT	*fslider8_;
	double 	fRec16[2];
	FAUSTFLOAT 	fslider9;
	FAUSTFLOAT	*fslider9_;
	double 	fRec19[2];
	double 	fRec0[2];
	int 	iRec1[2];
	double 	fRec2[2];
	FAUSTFLOAT 	fbargraph1;
	FAUSTFLOAT	*fbargraph1_;
	double 	fRec29[2];
	double 	fRec28[3];
	double 	fRec24[2];
	int 	iRec25[2];
	double 	fRec26[2];
	FAUSTFLOAT 	fbargraph2;
	FAUSTFLOAT	*fbargraph2_;
	FAUSTFLOAT 	fslider10;
	FAUSTFLOAT	*fslider10_;
	FAUSTFLOAT 	fslider11;
	FAUSTFLOAT	*fslider11_;
	FAUSTFLOAT 	fslider12;
	FAUSTFLOAT	*fslider12_;
	double 	fRec32[2];
	double 	fRec31[2];
	FAUSTFLOAT 	fslider13;
	FAUSTFLOAT	*fslider13_;
	FAUSTFLOAT 	fslider14;
	FAUSTFLOAT	*fslider14_;
	double 	fRec30[2];
	FAUSTFLOAT 	fslider15;
	FAUSTFLOAT	*fslider15_;
	double 	fRec33[2];
	double 	fRec20[2];
	int 	iRec21[2];
	double 	fRec22[2];
	FAUSTFLOAT 	fbargraph3;
	FAUSTFLOAT	*fbargraph3_;
	double 	fRec44[2];
	double 	fRec43[3];
	double 	fRec42[3];
	double 	fRec38[2];
	int 	iRec39[2];
	double 	fRec40[2];
	FAUSTFLOAT 	fbargraph4;
	FAUSTFLOAT	*fbargraph4_;
	FAUSTFLOAT 	fslider16;
	FAUSTFLOAT	*fslider16_;
	FAUSTFLOAT 	fslider17;
	FAUSTFLOAT	*fslider17_;
	FAUSTFLOAT 	fslider18;
	FAUSTFLOAT	*fslider18_;
	double 	fRec47[2];
	double 	fRec46[2];
	FAUSTFLOAT 	fslider19;
	FAUSTFLOAT	*fslider19_;
	FAUSTFLOAT 	fslider20;
	FAUSTFLOAT	*fslider20_;
	double 	fRec45[2];
	FAUSTFLOAT 	fslider21;
	FAUSTFLOAT	*fslider21_;
	double 	fRec48[2];
	double 	fRec34[2];
	int 	iRec35[2];
	double 	fRec36[2];
	FAUSTFLOAT 	fbargraph5;
	FAUSTFLOAT	*fbargraph5_;
	double 	fRec60[2];
	double 	fRec59[3];
	double 	fRec58[3];
	double 	fRec57[3];
	double 	fRec53[2];
	int 	iRec54[2];
	double 	fRec55[2];
	FAUSTFLOAT 	fbargraph6;
	FAUSTFLOAT	*fbargraph6_;
	FAUSTFLOAT 	fslider22;
	FAUSTFLOAT	*fslider22_;
	FAUSTFLOAT 	fslider23;
	FAUSTFLOAT	*fslider23_;
	FAUSTFLOAT 	fslider24;
	FAUSTFLOAT	*fslider24_;
	double 	fRec63[2];
	double 	fRec62[2];
	FAUSTFLOAT 	fslider25;
	FAUSTFLOAT	*fslider25_;
	FAUSTFLOAT 	fslider26;
	FAUSTFLOAT	*fslider26_;
	double 	fRec61[2];
	FAUSTFLOAT 	fslider27;
	FAUSTFLOAT	*fslider27_;
	double 	fRec64[2];
	double 	fRec49[2];
	int 	iRec50[2];
	double 	fRec51[2];
	FAUSTFLOAT 	fbargraph7;
	FAUSTFLOAT	*fbargraph7_;
	double 	fRec77[2];
	double 	fRec76[3];
	double 	fRec75[3];
	double 	fRec74[3];
	double 	fRec73[3];
	double 	fRec69[2];
	int 	iRec70[2];
	double 	fRec71[2];
	FAUSTFLOAT 	fbargraph8;
	FAUSTFLOAT	*fbargraph8_;
	FAUSTFLOAT 	fslider28;
	FAUSTFLOAT	*fslider28_;
	FAUSTFLOAT 	fslider29;
	FAUSTFLOAT	*fslider29_;
	FAUSTFLOAT 	fslider30;
	FAUSTFLOAT	*fslider30_;
	double 	fRec80[2];
	double 	fRec79[2];
	FAUSTFLOAT 	fslider31;
	FAUSTFLOAT	*fslider31_;
	FAUSTFLOAT 	fslider32;
	FAUSTFLOAT	*fslider32_;
	double 	fRec78[2];
	FAUSTFLOAT 	fslider33;
	FAUSTFLOAT	*fslider33_;
	double 	fRec81[2];
	double 	fRec65[2];
	int 	iRec66[2];
	double 	fRec67[2];
	FAUSTFLOAT 	fbargraph9;
	FAUSTFLOAT	*fbargraph9_;

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
	id = "mbc";
	name = N_("Multi Band Compressor");
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
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<3; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<3; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<3; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<3; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) iRec5[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) iRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec29[i] = 0;
	for (int i=0; i<3; i++) fRec28[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) iRec25[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<2; i++) fRec32[i] = 0;
	for (int i=0; i<2; i++) fRec31[i] = 0;
	for (int i=0; i<2; i++) fRec30[i] = 0;
	for (int i=0; i<2; i++) fRec33[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) iRec21[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fRec44[i] = 0;
	for (int i=0; i<3; i++) fRec43[i] = 0;
	for (int i=0; i<3; i++) fRec42[i] = 0;
	for (int i=0; i<2; i++) fRec38[i] = 0;
	for (int i=0; i<2; i++) iRec39[i] = 0;
	for (int i=0; i<2; i++) fRec40[i] = 0;
	for (int i=0; i<2; i++) fRec47[i] = 0;
	for (int i=0; i<2; i++) fRec46[i] = 0;
	for (int i=0; i<2; i++) fRec45[i] = 0;
	for (int i=0; i<2; i++) fRec48[i] = 0;
	for (int i=0; i<2; i++) fRec34[i] = 0;
	for (int i=0; i<2; i++) iRec35[i] = 0;
	for (int i=0; i<2; i++) fRec36[i] = 0;
	for (int i=0; i<2; i++) fRec60[i] = 0;
	for (int i=0; i<3; i++) fRec59[i] = 0;
	for (int i=0; i<3; i++) fRec58[i] = 0;
	for (int i=0; i<3; i++) fRec57[i] = 0;
	for (int i=0; i<2; i++) fRec53[i] = 0;
	for (int i=0; i<2; i++) iRec54[i] = 0;
	for (int i=0; i<2; i++) fRec55[i] = 0;
	for (int i=0; i<2; i++) fRec63[i] = 0;
	for (int i=0; i<2; i++) fRec62[i] = 0;
	for (int i=0; i<2; i++) fRec61[i] = 0;
	for (int i=0; i<2; i++) fRec64[i] = 0;
	for (int i=0; i<2; i++) fRec49[i] = 0;
	for (int i=0; i<2; i++) iRec50[i] = 0;
	for (int i=0; i<2; i++) fRec51[i] = 0;
	for (int i=0; i<2; i++) fRec77[i] = 0;
	for (int i=0; i<3; i++) fRec76[i] = 0;
	for (int i=0; i<3; i++) fRec75[i] = 0;
	for (int i=0; i<3; i++) fRec74[i] = 0;
	for (int i=0; i<3; i++) fRec73[i] = 0;
	for (int i=0; i<2; i++) fRec69[i] = 0;
	for (int i=0; i<2; i++) iRec70[i] = 0;
	for (int i=0; i<2; i++) fRec71[i] = 0;
	for (int i=0; i<2; i++) fRec80[i] = 0;
	for (int i=0; i<2; i++) fRec79[i] = 0;
	for (int i=0; i<2; i++) fRec78[i] = 0;
	for (int i=0; i<2; i++) fRec81[i] = 0;
	for (int i=0; i<2; i++) fRec65[i] = 0;
	for (int i=0; i<2; i++) iRec66[i] = 0;
	for (int i=0; i<2; i++) fRec67[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = min(1.92e+05, max(1.0, (double)fSamplingFreq));
	fConst1 = (1.0 / fConst0);
	fConst2 = (3.141592653589793 / fConst0);
	fConst3 = (2.0 / fConst0);
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
#define fslider7 (*fslider7_)
#define fslider8 (*fslider8_)
#define fslider9 (*fslider9_)
#define fbargraph1 (*fbargraph1_)
#define fbargraph2 (*fbargraph2_)
#define fslider10 (*fslider10_)
#define fslider11 (*fslider11_)
#define fslider12 (*fslider12_)
#define fslider13 (*fslider13_)
#define fslider14 (*fslider14_)
#define fslider15 (*fslider15_)
#define fbargraph3 (*fbargraph3_)
#define fbargraph4 (*fbargraph4_)
#define fslider16 (*fslider16_)
#define fslider17 (*fslider17_)
#define fslider18 (*fslider18_)
#define fslider19 (*fslider19_)
#define fslider20 (*fslider20_)
#define fslider21 (*fslider21_)
#define fbargraph5 (*fbargraph5_)
#define fbargraph6 (*fbargraph6_)
#define fslider22 (*fslider22_)
#define fslider23 (*fslider23_)
#define fslider24 (*fslider24_)
#define fslider25 (*fslider25_)
#define fslider26 (*fslider26_)
#define fslider27 (*fslider27_)
#define fbargraph7 (*fbargraph7_)
#define fbargraph8 (*fbargraph8_)
#define fslider28 (*fslider28_)
#define fslider29 (*fslider29_)
#define fslider30 (*fslider30_)
#define fslider31 (*fslider31_)
#define fslider32 (*fslider32_)
#define fslider33 (*fslider33_)
#define fbargraph9 (*fbargraph9_)
	double 	fSlow0 = tan((fConst2 * double(fslider0)));
	double 	fSlow1 = (1.0 / fSlow0);
	double 	fSlow2 = (1 + ((fSlow1 - 1.0000000000000004) / fSlow0));
	double 	fSlow3 = (1.0 / faustpower<2>(fSlow0));
	double 	fSlow4 = (2 * (1 - fSlow3));
	double 	fSlow5 = (1.0 / (1 + ((fSlow1 + 1.0000000000000004) / fSlow0)));
	double 	fSlow6 = tan((fConst2 * double(fslider1)));
	double 	fSlow7 = (1.0 / fSlow6);
	double 	fSlow8 = (1 + ((fSlow7 - 1.0000000000000004) / fSlow6));
	double 	fSlow9 = (1.0 / faustpower<2>(fSlow6));
	double 	fSlow10 = (2 * (1 - fSlow9));
	double 	fSlow11 = (1 + ((fSlow7 + 1.0000000000000004) / fSlow6));
	double 	fSlow12 = (1.0 / fSlow11);
	double 	fSlow13 = tan((fConst2 * double(fslider2)));
	double 	fSlow14 = (1.0 / fSlow13);
	double 	fSlow15 = (1 + ((fSlow14 - 1.0000000000000004) / fSlow13));
	double 	fSlow16 = (1.0 / faustpower<2>(fSlow13));
	double 	fSlow17 = (2 * (1 - fSlow16));
	double 	fSlow18 = (1 + ((fSlow14 + 1.0000000000000004) / fSlow13));
	double 	fSlow19 = (1.0 / fSlow18);
	double 	fSlow20 = tan((fConst2 * double(fslider3)));
	double 	fSlow21 = (1.0 / faustpower<2>(fSlow20));
	double 	fSlow22 = (2 * (1 - fSlow21));
	double 	fSlow23 = (1.0 / fSlow20);
	double 	fSlow24 = (1 + ((fSlow23 - 1.0000000000000004) / fSlow20));
	double 	fSlow25 = (1 + ((1.0000000000000004 + fSlow23) / fSlow20));
	double 	fSlow26 = (1.0 / fSlow25);
	double 	fSlow27 = (1 + fSlow23);
	double 	fSlow28 = (0 - ((1 - fSlow23) / fSlow27));
	double 	fSlow29 = (1.0 / fSlow27);
	double 	fSlow30 = (1 + fSlow14);
	double 	fSlow31 = (1.0 / fSlow30);
	double 	fSlow32 = (0 - ((1 - fSlow14) / fSlow30));
	double 	fSlow33 = (1 + fSlow7);
	double 	fSlow34 = (1.0 / fSlow33);
	double 	fSlow35 = (0 - ((1 - fSlow7) / fSlow33));
	double 	fSlow36 = (1 + fSlow1);
	double 	fSlow37 = (1.0 / fSlow36);
	double 	fSlow38 = (0 - ((1 - fSlow1) / fSlow36));
	double 	fSlow39 = double(fslider4);
	double 	fSlow40 = max((double)0, (fSlow39 - 1));
	int 	iSlow41 = int(fSlow40);
	double 	fSlow42 = double(fslider5);
	double 	fSlow43 = exp((0 - (fConst1 / fSlow42)));
	double 	fSlow44 = exp((0 - (fConst1 / double(fslider6))));
	double 	fSlow45 = double(fslider7);
	double 	fSlow46 = exp((0 - (fConst3 / fSlow42)));
	double 	fSlow47 = (((1.0 / double(double(fslider8))) - 1.0) * (1.0 - fSlow46));
	double 	fSlow48 = (0.0010000000000000009 * pow(10,(0.05 * ((fSlow45 - double(fslider9)) * fabs((fSlow40 - 1))))));
	double 	fSlow49 = fabs((max((double)0, (fSlow39 - 2)) - 1));
	double 	fSlow50 = (0 - fSlow1);
	double 	fSlow51 = (1.0 / (fSlow0 * fSlow11));
	double 	fSlow52 = (2 * (0 - fSlow3));
	double 	fSlow53 = double(fslider10);
	double 	fSlow54 = max((double)0, (fSlow53 - 1));
	int 	iSlow55 = int(fSlow54);
	double 	fSlow56 = double(fslider11);
	double 	fSlow57 = exp((0 - (fConst1 / fSlow56)));
	double 	fSlow58 = exp((0 - (fConst1 / double(fslider12))));
	double 	fSlow59 = double(fslider13);
	double 	fSlow60 = exp((0 - (fConst3 / fSlow56)));
	double 	fSlow61 = (((1.0 / double(double(fslider14))) - 1.0) * (1.0 - fSlow60));
	double 	fSlow62 = (0.0010000000000000009 * pow(10,(0.05 * ((fSlow59 - double(fslider15)) * fabs((fSlow54 - 1))))));
	double 	fSlow63 = fabs((max((double)0, (fSlow53 - 2)) - 1));
	double 	fSlow64 = (1 + ((fSlow1 - 1.0) / fSlow0));
	double 	fSlow65 = (1.0 / (1 + ((1.0 + fSlow1) / fSlow0)));
	double 	fSlow66 = (0 - fSlow7);
	double 	fSlow67 = (1.0 / (fSlow6 * fSlow18));
	double 	fSlow68 = (2 * (0 - fSlow9));
	double 	fSlow69 = double(fslider16);
	double 	fSlow70 = max((double)0, (fSlow69 - 1));
	int 	iSlow71 = int(fSlow70);
	double 	fSlow72 = double(fslider17);
	double 	fSlow73 = exp((0 - (fConst1 / fSlow72)));
	double 	fSlow74 = exp((0 - (fConst1 / double(fslider18))));
	double 	fSlow75 = double(fslider19);
	double 	fSlow76 = exp((0 - (fConst3 / fSlow72)));
	double 	fSlow77 = (((1.0 / double(double(fslider20))) - 1.0) * (1.0 - fSlow76));
	double 	fSlow78 = (0.0010000000000000009 * pow(10,(0.05 * ((fSlow75 - double(fslider21)) * fabs((fSlow70 - 1))))));
	double 	fSlow79 = fabs((max((double)0, (fSlow69 - 2)) - 1));
	double 	fSlow80 = (1 + ((fSlow7 - 1.0) / fSlow6));
	double 	fSlow81 = (1.0 / (1 + ((1.0 + fSlow7) / fSlow6)));
	double 	fSlow82 = (0 - fSlow14);
	double 	fSlow83 = (1.0 / (fSlow13 * fSlow25));
	double 	fSlow84 = (2 * (0 - fSlow16));
	double 	fSlow85 = double(fslider22);
	double 	fSlow86 = max((double)0, (fSlow85 - 1));
	int 	iSlow87 = int(fSlow86);
	double 	fSlow88 = double(fslider23);
	double 	fSlow89 = exp((0 - (fConst1 / fSlow88)));
	double 	fSlow90 = exp((0 - (fConst1 / double(fslider24))));
	double 	fSlow91 = double(fslider25);
	double 	fSlow92 = exp((0 - (fConst3 / fSlow88)));
	double 	fSlow93 = (((1.0 / double(double(fslider26))) - 1.0) * (1.0 - fSlow92));
	double 	fSlow94 = (0.0010000000000000009 * pow(10,(0.05 * ((fSlow91 - double(fslider27)) * fabs((fSlow86 - 1))))));
	double 	fSlow95 = fabs((max((double)0, (fSlow85 - 2)) - 1));
	double 	fSlow96 = (1 + ((fSlow14 - 1.0) / fSlow13));
	double 	fSlow97 = (1.0 / (1 + ((1.0 + fSlow14) / fSlow13)));
	double 	fSlow98 = (0 - fSlow23);
	double 	fSlow99 = (2 * (0 - fSlow21));
	double 	fSlow100 = double(fslider28);
	double 	fSlow101 = max((double)0, (fSlow100 - 1));
	int 	iSlow102 = int(fSlow101);
	double 	fSlow103 = double(fslider29);
	double 	fSlow104 = exp((0 - (fConst1 / fSlow103)));
	double 	fSlow105 = exp((0 - (fConst1 / double(fslider30))));
	double 	fSlow106 = double(fslider31);
	double 	fSlow107 = exp((0 - (fConst3 / fSlow103)));
	double 	fSlow108 = (((1.0 / double(double(fslider32))) - 1.0) * (1.0 - fSlow107));
	double 	fSlow109 = (0.0010000000000000009 * pow(10,(0.05 * ((fSlow106 - double(fslider33)) * fabs((fSlow101 - 1))))));
	double 	fSlow110 = fabs((max((double)0, (fSlow100 - 2)) - 1));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fVec0[0] = fTemp0;
		fRec15[0] = ((fSlow29 * (fVec0[0] + fVec0[1])) + (fSlow28 * fRec15[1]));
		fRec14[0] = (fRec15[0] - (fSlow26 * ((fSlow24 * fRec14[2]) + (fSlow22 * fRec14[1]))));
		double fTemp1 = (fRec14[0] + (fRec14[2] + (2 * fRec14[1])));
		double fTemp2 = (fSlow26 * fTemp1);
		fVec1[0] = fTemp2;
		fRec13[0] = ((fSlow32 * fRec13[1]) + (fSlow31 * (fVec1[0] + fVec1[1])));
		fRec12[0] = (fRec13[0] - (fSlow19 * ((fSlow17 * fRec12[1]) + (fSlow15 * fRec12[2]))));
		double fTemp3 = (fRec12[0] + (fRec12[2] + (2 * fRec12[1])));
		double fTemp4 = (fSlow19 * fTemp3);
		fVec2[0] = fTemp4;
		fRec11[0] = ((fSlow35 * fRec11[1]) + (fSlow34 * (fVec2[0] + fVec2[1])));
		fRec10[0] = (fRec11[0] - (fSlow12 * ((fSlow10 * fRec10[1]) + (fSlow8 * fRec10[2]))));
		double fTemp5 = (fRec10[0] + (fRec10[2] + (2 * fRec10[1])));
		double fTemp6 = (fSlow12 * fTemp5);
		fVec3[0] = fTemp6;
		fRec9[0] = ((fSlow38 * fRec9[1]) + (fSlow37 * (fVec3[0] + fVec3[1])));
		fRec8[0] = (fRec9[0] - (fSlow5 * ((fSlow4 * fRec8[1]) + (fSlow2 * fRec8[2]))));
		double fTemp7 = (fSlow5 * (fRec8[0] + (fRec8[2] + (2 * fRec8[1]))));
		double 	fRec7 = max(fConst1, fabs(fTemp7));
		int iTemp8 = int((iRec5[1] < 4096));
		fRec4[0] = ((iTemp8)?max(fRec4[1], fRec7):fRec7);
		iRec5[0] = ((iTemp8)?(1 + iRec5[1]):1);
		fRec6[0] = ((iTemp8)?fRec6[1]:fRec4[1]);
		fbargraph0 = fRec6[0];
		double fTemp9 = fTemp7;
		double fTemp10 = ((iSlow41)?0:fTemp9);
		double fTemp11 = fabs(fTemp10);
		double fTemp12 = ((int((fRec17[1] > fTemp11)))?fSlow44:fSlow43);
		fRec18[0] = ((fRec18[1] * fTemp12) + (fTemp11 * (1.0 - fTemp12)));
		fRec17[0] = fRec18[0];
		fRec16[0] = ((fSlow46 * fRec16[1]) + (fSlow47 * max((fSlow45 + (20 * log10(fRec17[0]))), 0.0)));
		fRec19[0] = (fSlow48 + (0.999 * fRec19[1]));
		double fTemp13 = (fSlow49 * (fRec19[0] * ((iSlow41)?fTemp9:(pow(10,(0.05 * fRec16[0])) * fTemp10))));
		double 	fRec3 = max(fConst1, fabs(fTemp13));
		int iTemp14 = int((iRec1[1] < 4096));
		fRec0[0] = ((iTemp14)?max(fRec0[1], fRec3):fRec3);
		iRec1[0] = ((iTemp14)?(1 + iRec1[1]):1);
		fRec2[0] = ((iTemp14)?fRec2[1]:fRec0[1]);
		fbargraph1 = fRec2[0];
		fRec29[0] = ((fSlow38 * fRec29[1]) + (fSlow37 * ((fSlow51 * fTemp5) + (fSlow50 * fVec3[1]))));
		fRec28[0] = (fRec29[0] - (fSlow5 * ((fSlow4 * fRec28[1]) + (fSlow2 * fRec28[2]))));
		double fTemp15 = (fSlow5 * ((fSlow52 * fRec28[1]) + (fSlow3 * (fRec28[2] + fRec28[0]))));
		double 	fRec27 = max(fConst1, fabs(fTemp15));
		int iTemp16 = int((iRec25[1] < 4096));
		fRec24[0] = ((iTemp16)?max(fRec24[1], fRec27):fRec27);
		iRec25[0] = ((iTemp16)?(1 + iRec25[1]):1);
		fRec26[0] = ((iTemp16)?fRec26[1]:fRec24[1]);
		fbargraph2 = fRec26[0];
		double fTemp17 = fTemp15;
		double fTemp18 = ((iSlow55)?0:fTemp17);
		double fTemp19 = fabs(fTemp18);
		double fTemp20 = ((int((fRec31[1] > fTemp19)))?fSlow58:fSlow57);
		fRec32[0] = ((fRec32[1] * fTemp20) + (fTemp19 * (1.0 - fTemp20)));
		fRec31[0] = fRec32[0];
		fRec30[0] = ((fSlow60 * fRec30[1]) + (fSlow61 * max((fSlow59 + (20 * log10(fRec31[0]))), 0.0)));
		fRec33[0] = (fSlow62 + (0.999 * fRec33[1]));
		double fTemp21 = (fSlow63 * (fRec33[0] * ((iSlow55)?fTemp17:(pow(10,(0.05 * fRec30[0])) * fTemp18))));
		double 	fRec23 = max(fConst1, fabs(fTemp21));
		int iTemp22 = int((iRec21[1] < 4096));
		fRec20[0] = ((iTemp22)?max(fRec20[1], fRec23):fRec23);
		iRec21[0] = ((iTemp22)?(1 + iRec21[1]):1);
		fRec22[0] = ((iTemp22)?fRec22[1]:fRec20[1]);
		fbargraph3 = fRec22[0];
		double fTemp23 = (fSlow4 * fRec42[1]);
		fRec44[0] = ((fSlow35 * fRec44[1]) + (fSlow34 * ((fSlow67 * fTemp3) + (fSlow66 * fVec2[1]))));
		fRec43[0] = (fRec44[0] - (fSlow12 * ((fSlow10 * fRec43[1]) + (fSlow8 * fRec43[2]))));
		fRec42[0] = ((fSlow12 * ((fSlow68 * fRec43[1]) + (fSlow9 * (fRec43[2] + fRec43[0])))) - (fSlow65 * ((fSlow64 * fRec42[2]) + fTemp23)));
		double fTemp24 = (fRec42[2] + (fSlow65 * (fTemp23 + (fSlow64 * fRec42[0]))));
		double 	fRec41 = max(fConst1, fabs(fTemp24));
		int iTemp25 = int((iRec39[1] < 4096));
		fRec38[0] = ((iTemp25)?max(fRec38[1], fRec41):fRec41);
		iRec39[0] = ((iTemp25)?(1 + iRec39[1]):1);
		fRec40[0] = ((iTemp25)?fRec40[1]:fRec38[1]);
		fbargraph4 = fRec40[0];
		double fTemp26 = fTemp24;
		double fTemp27 = ((iSlow71)?0:fTemp26);
		double fTemp28 = fabs(fTemp27);
		double fTemp29 = ((int((fRec46[1] > fTemp28)))?fSlow74:fSlow73);
		fRec47[0] = ((fRec47[1] * fTemp29) + (fTemp28 * (1.0 - fTemp29)));
		fRec46[0] = fRec47[0];
		fRec45[0] = ((fSlow76 * fRec45[1]) + (fSlow77 * max((fSlow75 + (20 * log10(fRec46[0]))), 0.0)));
		fRec48[0] = (fSlow78 + (0.999 * fRec48[1]));
		double fTemp30 = (fSlow79 * (fRec48[0] * ((iSlow71)?fTemp26:(pow(10,(0.05 * fRec45[0])) * fTemp27))));
		double 	fRec37 = max(fConst1, fabs(fTemp30));
		int iTemp31 = int((iRec35[1] < 4096));
		fRec34[0] = ((iTemp31)?max(fRec34[1], fRec37):fRec37);
		iRec35[0] = ((iTemp31)?(1 + iRec35[1]):1);
		fRec36[0] = ((iTemp31)?fRec36[1]:fRec34[1]);
		fbargraph5 = fRec36[0];
		double fTemp32 = (fSlow4 * fRec57[1]);
		double fTemp33 = (fSlow10 * fRec58[1]);
		fRec60[0] = ((fSlow32 * fRec60[1]) + (fSlow31 * ((fSlow83 * fTemp1) + (fSlow82 * fVec1[1]))));
		fRec59[0] = (fRec60[0] - (fSlow19 * ((fSlow17 * fRec59[1]) + (fSlow15 * fRec59[2]))));
		fRec58[0] = ((fSlow19 * ((fSlow84 * fRec59[1]) + (fSlow16 * (fRec59[2] + fRec59[0])))) - (fSlow81 * ((fSlow80 * fRec58[2]) + fTemp33)));
		fRec57[0] = ((fRec58[2] + (fSlow81 * (fTemp33 + (fSlow80 * fRec58[0])))) - (fSlow65 * ((fSlow64 * fRec57[2]) + fTemp32)));
		double fTemp34 = (fRec57[2] + (fSlow65 * (fTemp32 + (fSlow64 * fRec57[0]))));
		double 	fRec56 = max(fConst1, fabs(fTemp34));
		int iTemp35 = int((iRec54[1] < 4096));
		fRec53[0] = ((iTemp35)?max(fRec53[1], fRec56):fRec56);
		iRec54[0] = ((iTemp35)?(1 + iRec54[1]):1);
		fRec55[0] = ((iTemp35)?fRec55[1]:fRec53[1]);
		fbargraph6 = fRec55[0];
		double fTemp36 = fTemp34;
		double fTemp37 = ((iSlow87)?0:fTemp36);
		double fTemp38 = fabs(fTemp37);
		double fTemp39 = ((int((fRec62[1] > fTemp38)))?fSlow90:fSlow89);
		fRec63[0] = ((fRec63[1] * fTemp39) + (fTemp38 * (1.0 - fTemp39)));
		fRec62[0] = fRec63[0];
		fRec61[0] = ((fSlow92 * fRec61[1]) + (fSlow93 * max((fSlow91 + (20 * log10(fRec62[0]))), 0.0)));
		fRec64[0] = (fSlow94 + (0.999 * fRec64[1]));
		double fTemp40 = (fSlow95 * (fRec64[0] * ((iSlow87)?fTemp36:(pow(10,(0.05 * fRec61[0])) * fTemp37))));
		double 	fRec52 = max(fConst1, fabs(fTemp40));
		int iTemp41 = int((iRec50[1] < 4096));
		fRec49[0] = ((iTemp41)?max(fRec49[1], fRec52):fRec52);
		iRec50[0] = ((iTemp41)?(1 + iRec50[1]):1);
		fRec51[0] = ((iTemp41)?fRec51[1]:fRec49[1]);
		fbargraph7 = fRec51[0];
		double fTemp42 = (fSlow4 * fRec73[1]);
		double fTemp43 = (fSlow10 * fRec74[1]);
		double fTemp44 = (fSlow17 * fRec75[1]);
		fRec77[0] = ((fSlow29 * ((fSlow23 * fVec0[0]) + (fSlow98 * fVec0[1]))) + (fSlow28 * fRec77[1]));
		fRec76[0] = (fRec77[0] - (fSlow26 * ((fSlow24 * fRec76[2]) + (fSlow22 * fRec76[1]))));
		fRec75[0] = ((fSlow26 * ((fSlow99 * fRec76[1]) + (fSlow21 * (fRec76[2] + fRec76[0])))) - (fSlow97 * ((fSlow96 * fRec75[2]) + fTemp44)));
		fRec74[0] = ((fRec75[2] + (fSlow97 * (fTemp44 + (fSlow96 * fRec75[0])))) - (fSlow81 * ((fSlow80 * fRec74[2]) + fTemp43)));
		fRec73[0] = ((fRec74[2] + (fSlow81 * (fTemp43 + (fSlow80 * fRec74[0])))) - (fSlow65 * ((fSlow64 * fRec73[2]) + fTemp42)));
		double fTemp45 = (fRec73[2] + (fSlow65 * (fTemp42 + (fSlow64 * fRec73[0]))));
		double 	fRec72 = max(fConst1, fabs(fTemp45));
		int iTemp46 = int((iRec70[1] < 4096));
		fRec69[0] = ((iTemp46)?max(fRec69[1], fRec72):fRec72);
		iRec70[0] = ((iTemp46)?(1 + iRec70[1]):1);
		fRec71[0] = ((iTemp46)?fRec71[1]:fRec69[1]);
		fbargraph8 = fRec71[0];
		double fTemp47 = fTemp45;
		double fTemp48 = ((iSlow102)?0:fTemp47);
		double fTemp49 = fabs(fTemp48);
		double fTemp50 = ((int((fRec79[1] > fTemp49)))?fSlow105:fSlow104);
		fRec80[0] = ((fRec80[1] * fTemp50) + (fTemp49 * (1.0 - fTemp50)));
		fRec79[0] = fRec80[0];
		fRec78[0] = ((fSlow107 * fRec78[1]) + (fSlow108 * max((fSlow106 + (20 * log10(fRec79[0]))), 0.0)));
		fRec81[0] = (fSlow109 + (0.999 * fRec81[1]));
		double fTemp51 = (fSlow110 * (fRec81[0] * ((iSlow102)?fTemp47:(pow(10,(0.05 * fRec78[0])) * fTemp48))));
		double 	fRec68 = max(fConst1, fabs(fTemp51));
		int iTemp52 = int((iRec66[1] < 4096));
		fRec65[0] = ((iTemp52)?max(fRec65[1], fRec68):fRec68);
		iRec66[0] = ((iTemp52)?(1 + iRec66[1]):1);
		fRec67[0] = ((iTemp52)?fRec67[1]:fRec65[1]);
		fbargraph9 = fRec67[0];
		output0[i] = (FAUSTFLOAT)((((fTemp51 + fTemp40) + fTemp30) + fTemp21) + fTemp13);
		// post processing
		fRec67[1] = fRec67[0];
		iRec66[1] = iRec66[0];
		fRec65[1] = fRec65[0];
		fRec81[1] = fRec81[0];
		fRec78[1] = fRec78[0];
		fRec79[1] = fRec79[0];
		fRec80[1] = fRec80[0];
		fRec71[1] = fRec71[0];
		iRec70[1] = iRec70[0];
		fRec69[1] = fRec69[0];
		fRec73[2] = fRec73[1]; fRec73[1] = fRec73[0];
		fRec74[2] = fRec74[1]; fRec74[1] = fRec74[0];
		fRec75[2] = fRec75[1]; fRec75[1] = fRec75[0];
		fRec76[2] = fRec76[1]; fRec76[1] = fRec76[0];
		fRec77[1] = fRec77[0];
		fRec51[1] = fRec51[0];
		iRec50[1] = iRec50[0];
		fRec49[1] = fRec49[0];
		fRec64[1] = fRec64[0];
		fRec61[1] = fRec61[0];
		fRec62[1] = fRec62[0];
		fRec63[1] = fRec63[0];
		fRec55[1] = fRec55[0];
		iRec54[1] = iRec54[0];
		fRec53[1] = fRec53[0];
		fRec57[2] = fRec57[1]; fRec57[1] = fRec57[0];
		fRec58[2] = fRec58[1]; fRec58[1] = fRec58[0];
		fRec59[2] = fRec59[1]; fRec59[1] = fRec59[0];
		fRec60[1] = fRec60[0];
		fRec36[1] = fRec36[0];
		iRec35[1] = iRec35[0];
		fRec34[1] = fRec34[0];
		fRec48[1] = fRec48[0];
		fRec45[1] = fRec45[0];
		fRec46[1] = fRec46[0];
		fRec47[1] = fRec47[0];
		fRec40[1] = fRec40[0];
		iRec39[1] = iRec39[0];
		fRec38[1] = fRec38[0];
		fRec42[2] = fRec42[1]; fRec42[1] = fRec42[0];
		fRec43[2] = fRec43[1]; fRec43[1] = fRec43[0];
		fRec44[1] = fRec44[0];
		fRec22[1] = fRec22[0];
		iRec21[1] = iRec21[0];
		fRec20[1] = fRec20[0];
		fRec33[1] = fRec33[0];
		fRec30[1] = fRec30[0];
		fRec31[1] = fRec31[0];
		fRec32[1] = fRec32[0];
		fRec26[1] = fRec26[0];
		iRec25[1] = iRec25[0];
		fRec24[1] = fRec24[0];
		fRec28[2] = fRec28[1]; fRec28[1] = fRec28[0];
		fRec29[1] = fRec29[0];
		fRec2[1] = fRec2[0];
		iRec1[1] = iRec1[0];
		fRec0[1] = fRec0[0];
		fRec19[1] = fRec19[0];
		fRec16[1] = fRec16[0];
		fRec17[1] = fRec17[0];
		fRec18[1] = fRec18[0];
		fRec6[1] = fRec6[0];
		iRec5[1] = iRec5[0];
		fRec4[1] = fRec4[0];
		fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
		fRec9[1] = fRec9[0];
		fVec3[1] = fVec3[0];
		fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		fVec2[1] = fVec2[0];
		fRec12[2] = fRec12[1]; fRec12[1] = fRec12[0];
		fRec13[1] = fRec13[0];
		fVec1[1] = fVec1[0];
		fRec14[2] = fRec14[1]; fRec14[1] = fRec14[0];
		fRec15[1] = fRec15[0];
		fVec0[1] = fVec0[0];
	}
#undef fslider0
#undef fslider1
#undef fslider2
#undef fslider3
#undef fbargraph0
#undef fslider4
#undef fslider5
#undef fslider6
#undef fslider7
#undef fslider8
#undef fslider9
#undef fbargraph1
#undef fbargraph2
#undef fslider10
#undef fslider11
#undef fslider12
#undef fslider13
#undef fslider14
#undef fslider15
#undef fbargraph3
#undef fbargraph4
#undef fslider16
#undef fslider17
#undef fslider18
#undef fslider19
#undef fslider20
#undef fslider21
#undef fbargraph5
#undef fbargraph6
#undef fslider22
#undef fslider23
#undef fslider24
#undef fslider25
#undef fslider26
#undef fslider27
#undef fbargraph7
#undef fbargraph8
#undef fslider28
#undef fslider29
#undef fslider30
#undef fslider31
#undef fslider32
#undef fslider33
#undef fbargraph9
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	// static const value_pair fslider4_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	case MODE1: 
		fslider4_ = (float*)data; // , 1.0, 1.0, 3.0, 1.0 
		break;
	// static const value_pair fslider10_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	case MODE2: 
		fslider10_ = (float*)data; // , 1.0, 1.0, 3.0, 1.0 
		break;
	// static const value_pair fslider16_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	case MODE3: 
		fslider16_ = (float*)data; // , 1.0, 1.0, 3.0, 1.0 
		break;
	// static const value_pair fslider22_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	case MODE4: 
		fslider22_ = (float*)data; // , 1.0, 1.0, 3.0, 1.0 
		break;
	// static const value_pair fslider28_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	case MODE5: 
		fslider28_ = (float*)data; // , 1.0, 1.0, 3.0, 1.0 
		break;
	case MAKEUP1: 
		fslider7_ = (float*)data; // , 13.0, -5e+01, 5e+01, 0.1 
		break;
	case MAKEUP2: 
		fslider13_ = (float*)data; // , 1e+01, -5e+01, 5e+01, 0.1 
		break;
	case MAKEUP3: 
		fslider19_ = (float*)data; // , 4.0, -5e+01, 5e+01, 0.1 
		break;
	case MAKEUP4: 
		fslider25_ = (float*)data; // , 8.0, -5e+01, 5e+01, 0.1 
		break;
	case MAKEUP5: 
		fslider31_ = (float*)data; // , 11.0, -5e+01, 5e+01, 0.1 
		break;
	case MAKEUPTHRESHOLD1: 
		fslider9_ = (float*)data; // , 2.0, 0.0, 1e+01, 0.1 
		break;
	case MAKEUPTHRESHOLD2: 
		fslider15_ = (float*)data; // , 2.0, 0.0, 1e+01, 0.1 
		break;
	case MAKEUPTHRESHOLD3: 
		fslider21_ = (float*)data; // , 2.0, 0.0, 1e+01, 0.1 
		break;
	case MAKEUPTHRESHOLD4: 
		fslider27_ = (float*)data; // , 2.0, 0.0, 1e+01, 0.1 
		break;
	case MAKEUPTHRESHOLD5: 
		fslider33_ = (float*)data; // , 2.0, 0.0, 1e+01, 0.1 
		break;
	case RATIO1: 
		fslider8_ = (float*)data; // , 2.0, 1.0, 1e+02, 0.1 
		break;
	case RATIO2: 
		fslider14_ = (float*)data; // , 2.0, 1.0, 1e+02, 0.1 
		break;
	case RATIO3: 
		fslider20_ = (float*)data; // , 2.0, 1.0, 1e+02, 0.1 
		break;
	case RATIO4: 
		fslider26_ = (float*)data; // , 2.0, 1.0, 1e+02, 0.1 
		break;
	case RATIO5: 
		fslider32_ = (float*)data; // , 2.0, 1.0, 1e+02, 0.1 
		break;
	case ATTACK1: 
		fslider5_ = (float*)data; // , 0.012, 0.001, 1.0, 0.001 
		break;
	case ATTACK2: 
		fslider11_ = (float*)data; // , 0.012, 0.001, 1.0, 0.001 
		break;
	case ATTACK3: 
		fslider17_ = (float*)data; // , 0.012, 0.001, 1.0, 0.001 
		break;
	case ATTACK4: 
		fslider23_ = (float*)data; // , 0.012, 0.001, 1.0, 0.001 
		break;
	case ATTACK5: 
		fslider29_ = (float*)data; // , 0.012, 0.001, 1.0, 0.001 
		break;
	case RELEASE1: 
		fslider6_ = (float*)data; // , 1.25, 0.01, 1e+01, 0.01 
		break;
	case RELEASE2: 
		fslider12_ = (float*)data; // , 1.25, 0.01, 1e+01, 0.01 
		break;
	case RELEASE3: 
		fslider18_ = (float*)data; // , 1.25, 0.01, 1e+01, 0.01 
		break;
	case RELEASE4: 
		fslider24_ = (float*)data; // , 1.25, 0.01, 1e+01, 0.01 
		break;
	case RELEASE5: 
		fslider30_ = (float*)data; // , 1.25, 0.01, 1e+01, 0.01 
		break;
	case CROSSOVER_B1_B2: 
		fslider0_ = (float*)data; // , 8e+01, 2e+01, 2e+04, 1.08 
		break;
	case CROSSOVER_B2_B3: 
		fslider1_ = (float*)data; // , 2.1e+02, 2e+01, 2e+04, 1.08 
		break;
	case CROSSOVER_B3_B4: 
		fslider2_ = (float*)data; // , 1.7e+03, 2e+01, 2e+04, 1.08 
		break;
	case CROSSOVER_B4_B5: 
		fslider3_ = (float*)data; // , 5e+03, 2e+01, 2e+04, 1.08 
		break;
	case V10: 
		fbargraph8_ = (float*)data; // , -70.0, -70.0, 4.0, 0.00001 
		break;
	case V1: 
		fbargraph1_ = (float*)data; // , -70.0, -70.0, 4.0, 0.00001 
		break;
	case V2: 
		fbargraph3_ = (float*)data; // , -70.0, -70.0, 4.0, 0.00001 
		break;
	case V3: 
		fbargraph5_ = (float*)data; // , -70.0, -70.0, 4.0, 0.00001 
		break;
	case V4: 
		fbargraph7_ = (float*)data; // , -70.0, -70.0, 4.0, 0.00001 
		break;
	case V5: 
		fbargraph9_ = (float*)data; // , -70.0, -70.0, 4.0, 0.00001 
		break;
	case V6: 
		fbargraph0_ = (float*)data; // , -70.0, -70.0, 4.0, 0.00001 
		break;
	case V7: 
		fbargraph2_ = (float*)data; // , -70.0, -70.0, 4.0, 0.00001 
		break;
	case V8: 
		fbargraph4_ = (float*)data; // , -70.0, -70.0, 4.0, 0.00001 
		break;
	case V9: 
		fbargraph6_ = (float*)data; // , -70.0, -70.0, 4.0, 0.00001 
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
   MODE1, 
   MODE2, 
   MODE3, 
   MODE4, 
   MODE5, 
   MAKEUP1, 
   MAKEUP2, 
   MAKEUP3, 
   MAKEUP4, 
   MAKEUP5, 
   MAKEUPTHRESHOLD1, 
   MAKEUPTHRESHOLD2, 
   MAKEUPTHRESHOLD3, 
   MAKEUPTHRESHOLD4, 
   MAKEUPTHRESHOLD5, 
   RATIO1, 
   RATIO2, 
   RATIO3, 
   RATIO4, 
   RATIO5, 
   ATTACK1, 
   ATTACK2, 
   ATTACK3, 
   ATTACK4, 
   ATTACK5, 
   RELEASE1, 
   RELEASE2, 
   RELEASE3, 
   RELEASE4, 
   RELEASE5, 
   CROSSOVER_B1_B2, 
   CROSSOVER_B2_B3, 
   CROSSOVER_B3_B4, 
   CROSSOVER_B4_B5, 
   V10, 
   V1, 
   V2, 
   V3, 
   V4, 
   V5, 
   V6, 
   V7, 
   V8, 
   V9, 
} PortIndex;
*/

} // end namespace mbc
