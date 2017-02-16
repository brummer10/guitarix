// generated from file '../src/LV2/faust/mbc.dsp' by dsp2cc:
// Code generated with Faust 0.9.73 (http://faust.grame.fr)


namespace mbc {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	int 	iConst0;
	double 	fConst1;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fConst2;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT	*fslider4_;
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT	*fslider5_;
	double 	fVec0[2];
	double 	fRec18[2];
	double 	fRec17[3];
	double 	fVec1[2];
	double 	fRec16[2];
	double 	fRec15[3];
	double 	fVec2[2];
	double 	fRec14[2];
	double 	fRec13[3];
	double 	fVec3[2];
	double 	fRec12[2];
	double 	fRec11[3];
	double 	fRec7[2];
	int 	iRec8[2];
	double 	fRec9[2];
	FAUSTFLOAT 	fbargraph0;
	FAUSTFLOAT	*fbargraph0_;
	FAUSTFLOAT 	fslider6;
	FAUSTFLOAT	*fslider6_;
	double 	fRec6[2];
	double 	fRec5[2];
	FAUSTFLOAT 	fslider7;
	FAUSTFLOAT	*fslider7_;
	double 	fConst3;
	FAUSTFLOAT 	fslider8;
	FAUSTFLOAT	*fslider8_;
	double 	fRec4[2];
	FAUSTFLOAT 	fslider9;
	FAUSTFLOAT	*fslider9_;
	double 	fRec19[2];
	double 	fRec0[2];
	int 	iRec1[2];
	double 	fRec2[2];
	FAUSTFLOAT 	fbargraph1;
	FAUSTFLOAT	*fbargraph1_;
	FAUSTFLOAT 	fslider10;
	FAUSTFLOAT	*fslider10_;
	FAUSTFLOAT 	fslider11;
	FAUSTFLOAT	*fslider11_;
	double 	fRec32[2];
	double 	fRec31[3];
	double 	fRec27[2];
	int 	iRec28[2];
	double 	fRec29[2];
	FAUSTFLOAT 	fbargraph2;
	FAUSTFLOAT	*fbargraph2_;
	FAUSTFLOAT 	fslider12;
	FAUSTFLOAT	*fslider12_;
	double 	fRec26[2];
	double 	fRec25[2];
	FAUSTFLOAT 	fslider13;
	FAUSTFLOAT	*fslider13_;
	FAUSTFLOAT 	fslider14;
	FAUSTFLOAT	*fslider14_;
	double 	fRec24[2];
	FAUSTFLOAT 	fslider15;
	FAUSTFLOAT	*fslider15_;
	double 	fRec33[2];
	double 	fRec20[2];
	int 	iRec21[2];
	double 	fRec22[2];
	FAUSTFLOAT 	fbargraph3;
	FAUSTFLOAT	*fbargraph3_;
	FAUSTFLOAT 	fslider16;
	FAUSTFLOAT	*fslider16_;
	FAUSTFLOAT 	fslider17;
	FAUSTFLOAT	*fslider17_;
	double 	fRec47[2];
	double 	fRec46[3];
	double 	fRec45[3];
	double 	fRec41[2];
	int 	iRec42[2];
	double 	fRec43[2];
	FAUSTFLOAT 	fbargraph4;
	FAUSTFLOAT	*fbargraph4_;
	FAUSTFLOAT 	fslider18;
	FAUSTFLOAT	*fslider18_;
	double 	fRec40[2];
	double 	fRec39[2];
	FAUSTFLOAT 	fslider19;
	FAUSTFLOAT	*fslider19_;
	FAUSTFLOAT 	fslider20;
	FAUSTFLOAT	*fslider20_;
	double 	fRec38[2];
	FAUSTFLOAT 	fslider21;
	FAUSTFLOAT	*fslider21_;
	double 	fRec48[2];
	double 	fRec34[2];
	int 	iRec35[2];
	double 	fRec36[2];
	FAUSTFLOAT 	fbargraph5;
	FAUSTFLOAT	*fbargraph5_;
	FAUSTFLOAT 	fslider22;
	FAUSTFLOAT	*fslider22_;
	FAUSTFLOAT 	fslider23;
	FAUSTFLOAT	*fslider23_;
	double 	fRec63[2];
	double 	fRec62[3];
	double 	fRec61[3];
	double 	fRec60[3];
	double 	fRec56[2];
	int 	iRec57[2];
	double 	fRec58[2];
	FAUSTFLOAT 	fbargraph6;
	FAUSTFLOAT	*fbargraph6_;
	FAUSTFLOAT 	fslider24;
	FAUSTFLOAT	*fslider24_;
	double 	fRec55[2];
	double 	fRec54[2];
	FAUSTFLOAT 	fslider25;
	FAUSTFLOAT	*fslider25_;
	FAUSTFLOAT 	fslider26;
	FAUSTFLOAT	*fslider26_;
	double 	fRec53[2];
	FAUSTFLOAT 	fslider27;
	FAUSTFLOAT	*fslider27_;
	double 	fRec64[2];
	double 	fRec49[2];
	int 	iRec50[2];
	double 	fRec51[2];
	FAUSTFLOAT 	fbargraph7;
	FAUSTFLOAT	*fbargraph7_;
	FAUSTFLOAT 	fslider28;
	FAUSTFLOAT	*fslider28_;
	FAUSTFLOAT 	fslider29;
	FAUSTFLOAT	*fslider29_;
	double 	fRec80[2];
	double 	fRec79[3];
	double 	fRec78[3];
	double 	fRec77[3];
	double 	fRec76[3];
	double 	fRec72[2];
	int 	iRec73[2];
	double 	fRec74[2];
	FAUSTFLOAT 	fbargraph8;
	FAUSTFLOAT	*fbargraph8_;
	FAUSTFLOAT 	fslider30;
	FAUSTFLOAT	*fslider30_;
	double 	fRec71[2];
	double 	fRec70[2];
	FAUSTFLOAT 	fslider31;
	FAUSTFLOAT	*fslider31_;
	FAUSTFLOAT 	fslider32;
	FAUSTFLOAT	*fslider32_;
	double 	fRec69[2];
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
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<3; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<3; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<3; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<3; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) iRec8[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) iRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec32[i] = 0;
	for (int i=0; i<3; i++) fRec31[i] = 0;
	for (int i=0; i<2; i++) fRec27[i] = 0;
	for (int i=0; i<2; i++) iRec28[i] = 0;
	for (int i=0; i<2; i++) fRec29[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<2; i++) fRec25[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fRec33[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) iRec21[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fRec47[i] = 0;
	for (int i=0; i<3; i++) fRec46[i] = 0;
	for (int i=0; i<3; i++) fRec45[i] = 0;
	for (int i=0; i<2; i++) fRec41[i] = 0;
	for (int i=0; i<2; i++) iRec42[i] = 0;
	for (int i=0; i<2; i++) fRec43[i] = 0;
	for (int i=0; i<2; i++) fRec40[i] = 0;
	for (int i=0; i<2; i++) fRec39[i] = 0;
	for (int i=0; i<2; i++) fRec38[i] = 0;
	for (int i=0; i<2; i++) fRec48[i] = 0;
	for (int i=0; i<2; i++) fRec34[i] = 0;
	for (int i=0; i<2; i++) iRec35[i] = 0;
	for (int i=0; i<2; i++) fRec36[i] = 0;
	for (int i=0; i<2; i++) fRec63[i] = 0;
	for (int i=0; i<3; i++) fRec62[i] = 0;
	for (int i=0; i<3; i++) fRec61[i] = 0;
	for (int i=0; i<3; i++) fRec60[i] = 0;
	for (int i=0; i<2; i++) fRec56[i] = 0;
	for (int i=0; i<2; i++) iRec57[i] = 0;
	for (int i=0; i<2; i++) fRec58[i] = 0;
	for (int i=0; i<2; i++) fRec55[i] = 0;
	for (int i=0; i<2; i++) fRec54[i] = 0;
	for (int i=0; i<2; i++) fRec53[i] = 0;
	for (int i=0; i<2; i++) fRec64[i] = 0;
	for (int i=0; i<2; i++) fRec49[i] = 0;
	for (int i=0; i<2; i++) iRec50[i] = 0;
	for (int i=0; i<2; i++) fRec51[i] = 0;
	for (int i=0; i<2; i++) fRec80[i] = 0;
	for (int i=0; i<3; i++) fRec79[i] = 0;
	for (int i=0; i<3; i++) fRec78[i] = 0;
	for (int i=0; i<3; i++) fRec77[i] = 0;
	for (int i=0; i<3; i++) fRec76[i] = 0;
	for (int i=0; i<2; i++) fRec72[i] = 0;
	for (int i=0; i<2; i++) iRec73[i] = 0;
	for (int i=0; i<2; i++) fRec74[i] = 0;
	for (int i=0; i<2; i++) fRec71[i] = 0;
	for (int i=0; i<2; i++) fRec70[i] = 0;
	for (int i=0; i<2; i++) fRec69[i] = 0;
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
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (1.0 / double(iConst0));
	fConst2 = (3.141592653589793 / double(iConst0));
	fConst3 = (2.0 / double(iConst0));
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
#define fbargraph0 (*fbargraph0_)
#define fslider6 (*fslider6_)
#define fslider7 (*fslider7_)
#define fslider8 (*fslider8_)
#define fslider9 (*fslider9_)
#define fbargraph1 (*fbargraph1_)
#define fslider10 (*fslider10_)
#define fslider11 (*fslider11_)
#define fbargraph2 (*fbargraph2_)
#define fslider12 (*fslider12_)
#define fslider13 (*fslider13_)
#define fslider14 (*fslider14_)
#define fslider15 (*fslider15_)
#define fbargraph3 (*fbargraph3_)
#define fslider16 (*fslider16_)
#define fslider17 (*fslider17_)
#define fbargraph4 (*fbargraph4_)
#define fslider18 (*fslider18_)
#define fslider19 (*fslider19_)
#define fslider20 (*fslider20_)
#define fslider21 (*fslider21_)
#define fbargraph5 (*fbargraph5_)
#define fslider22 (*fslider22_)
#define fslider23 (*fslider23_)
#define fbargraph6 (*fbargraph6_)
#define fslider24 (*fslider24_)
#define fslider25 (*fslider25_)
#define fslider26 (*fslider26_)
#define fslider27 (*fslider27_)
#define fbargraph7 (*fbargraph7_)
#define fslider28 (*fslider28_)
#define fslider29 (*fslider29_)
#define fbargraph8 (*fbargraph8_)
#define fslider30 (*fslider30_)
#define fslider31 (*fslider31_)
#define fslider32 (*fslider32_)
#define fslider33 (*fslider33_)
#define fbargraph9 (*fbargraph9_)
	double 	fSlow0 = double(fslider0);
	double 	fSlow1 = exp((0 - (fConst1 / fSlow0)));
	double 	fSlow2 = exp((0 - (fConst1 / double(fslider1))));
	double 	fSlow3 = tan((fConst2 * double(fslider2)));
	double 	fSlow4 = (1.0 / faustpower<2>(fSlow3));
	double 	fSlow5 = (2 * (1 - fSlow4));
	double 	fSlow6 = (1.0 / fSlow3);
	double 	fSlow7 = (1 + ((fSlow6 - 1.0000000000000004) / fSlow3));
	double 	fSlow8 = (1.0 / (1 + ((fSlow6 + 1.0000000000000004) / fSlow3)));
	double 	fSlow9 = tan((fConst2 * double(fslider3)));
	double 	fSlow10 = (1.0 / faustpower<2>(fSlow9));
	double 	fSlow11 = (2 * (1 - fSlow10));
	double 	fSlow12 = (1.0 / fSlow9);
	double 	fSlow13 = (1 + ((fSlow12 - 1.0000000000000004) / fSlow9));
	double 	fSlow14 = (1 + ((fSlow12 + 1.0000000000000004) / fSlow9));
	double 	fSlow15 = (1.0 / fSlow14);
	double 	fSlow16 = tan((fConst2 * double(fslider4)));
	double 	fSlow17 = (1.0 / faustpower<2>(fSlow16));
	double 	fSlow18 = (2 * (1 - fSlow17));
	double 	fSlow19 = (1.0 / fSlow16);
	double 	fSlow20 = (1 + ((fSlow19 - 1.0000000000000004) / fSlow16));
	double 	fSlow21 = (1 + ((fSlow19 + 1.0000000000000004) / fSlow16));
	double 	fSlow22 = (1.0 / fSlow21);
	double 	fSlow23 = tan((fConst2 * double(fslider5)));
	double 	fSlow24 = (1.0 / faustpower<2>(fSlow23));
	double 	fSlow25 = (2 * (1 - fSlow24));
	double 	fSlow26 = (1.0 / fSlow23);
	double 	fSlow27 = (1 + ((fSlow26 - 1.0000000000000004) / fSlow23));
	double 	fSlow28 = (1 + ((1.0000000000000004 + fSlow26) / fSlow23));
	double 	fSlow29 = (1.0 / fSlow28);
	double 	fSlow30 = (1 + fSlow26);
	double 	fSlow31 = (1.0 / fSlow30);
	double 	fSlow32 = (0 - ((1 - fSlow26) / fSlow30));
	double 	fSlow33 = (1 + fSlow19);
	double 	fSlow34 = (1.0 / fSlow33);
	double 	fSlow35 = (0 - ((1 - fSlow19) / fSlow33));
	double 	fSlow36 = (1 + fSlow12);
	double 	fSlow37 = (1.0 / fSlow36);
	double 	fSlow38 = (0 - ((1 - fSlow12) / fSlow36));
	double 	fSlow39 = (1 + fSlow6);
	double 	fSlow40 = (1.0 / fSlow39);
	double 	fSlow41 = (0 - ((1 - fSlow6) / fSlow39));
	double 	fSlow42 = double(fslider6);
	double 	fSlow43 = max((double)0, (fSlow42 - 1));
	int 	iSlow44 = int(fSlow43);
	double 	fSlow45 = double(fslider7);
	double 	fSlow46 = exp((0 - (fConst3 / fSlow0)));
	double 	fSlow47 = (((1.0 / double(double(fslider8))) - 1.0) * (1.0 - fSlow46));
	double 	fSlow48 = (0.0010000000000000009 * pow(10,(0.05 * ((fSlow45 - double(fslider9)) * fabs((fSlow43 - 1))))));
	double 	fSlow49 = fabs((max((double)0, (fSlow42 - 2)) - 1));
	double 	fSlow50 = double(fslider10);
	double 	fSlow51 = exp((0 - (fConst1 / fSlow50)));
	double 	fSlow52 = exp((0 - (fConst1 / double(fslider11))));
	double 	fSlow53 = (0 - fSlow6);
	double 	fSlow54 = (1.0 / (fSlow3 * fSlow14));
	double 	fSlow55 = (2 * (0 - fSlow4));
	double 	fSlow56 = double(fslider12);
	double 	fSlow57 = max((double)0, (fSlow56 - 1));
	int 	iSlow58 = int(fSlow57);
	double 	fSlow59 = double(fslider13);
	double 	fSlow60 = exp((0 - (fConst3 / fSlow50)));
	double 	fSlow61 = (((1.0 / double(double(fslider14))) - 1.0) * (1.0 - fSlow60));
	double 	fSlow62 = (0.0010000000000000009 * pow(10,(0.05 * ((fSlow59 - double(fslider15)) * fabs((fSlow57 - 1))))));
	double 	fSlow63 = fabs((max((double)0, (fSlow56 - 2)) - 1));
	double 	fSlow64 = double(fslider16);
	double 	fSlow65 = exp((0 - (fConst1 / fSlow64)));
	double 	fSlow66 = exp((0 - (fConst1 / double(fslider17))));
	double 	fSlow67 = (1 + ((fSlow6 - 1.0) / fSlow3));
	double 	fSlow68 = (1.0 / (1 + ((1.0 + fSlow6) / fSlow3)));
	double 	fSlow69 = (0 - fSlow12);
	double 	fSlow70 = (1.0 / (fSlow9 * fSlow21));
	double 	fSlow71 = (2 * (0 - fSlow10));
	double 	fSlow72 = double(fslider18);
	double 	fSlow73 = max((double)0, (fSlow72 - 1));
	int 	iSlow74 = int(fSlow73);
	double 	fSlow75 = double(fslider19);
	double 	fSlow76 = exp((0 - (fConst3 / fSlow64)));
	double 	fSlow77 = (((1.0 / double(double(fslider20))) - 1.0) * (1.0 - fSlow76));
	double 	fSlow78 = (0.0010000000000000009 * pow(10,(0.05 * ((fSlow75 - double(fslider21)) * fabs((fSlow73 - 1))))));
	double 	fSlow79 = fabs((max((double)0, (fSlow72 - 2)) - 1));
	double 	fSlow80 = double(fslider22);
	double 	fSlow81 = exp((0 - (fConst1 / fSlow80)));
	double 	fSlow82 = exp((0 - (fConst1 / double(fslider23))));
	double 	fSlow83 = (1 + ((fSlow12 - 1.0) / fSlow9));
	double 	fSlow84 = (1.0 / (1 + ((1.0 + fSlow12) / fSlow9)));
	double 	fSlow85 = (0 - fSlow19);
	double 	fSlow86 = (1.0 / (fSlow16 * fSlow28));
	double 	fSlow87 = (2 * (0 - fSlow17));
	double 	fSlow88 = double(fslider24);
	double 	fSlow89 = max((double)0, (fSlow88 - 1));
	int 	iSlow90 = int(fSlow89);
	double 	fSlow91 = double(fslider25);
	double 	fSlow92 = exp((0 - (fConst3 / fSlow80)));
	double 	fSlow93 = (((1.0 / double(double(fslider26))) - 1.0) * (1.0 - fSlow92));
	double 	fSlow94 = (0.0010000000000000009 * pow(10,(0.05 * ((fSlow91 - double(fslider27)) * fabs((fSlow89 - 1))))));
	double 	fSlow95 = fabs((max((double)0, (fSlow88 - 2)) - 1));
	double 	fSlow96 = double(fslider28);
	double 	fSlow97 = exp((0 - (fConst1 / fSlow96)));
	double 	fSlow98 = exp((0 - (fConst1 / double(fslider29))));
	double 	fSlow99 = (1 + ((fSlow19 - 1.0) / fSlow16));
	double 	fSlow100 = (1.0 / (1 + ((1.0 + fSlow19) / fSlow16)));
	double 	fSlow101 = (0 - fSlow26);
	double 	fSlow102 = (2 * (0 - fSlow24));
	double 	fSlow103 = double(fslider30);
	double 	fSlow104 = max((double)0, (fSlow103 - 1));
	int 	iSlow105 = int(fSlow104);
	double 	fSlow106 = double(fslider31);
	double 	fSlow107 = exp((0 - (fConst3 / fSlow96)));
	double 	fSlow108 = (((1.0 / double(double(fslider32))) - 1.0) * (1.0 - fSlow107));
	double 	fSlow109 = (0.0010000000000000009 * pow(10,(0.05 * ((fSlow106 - double(fslider33)) * fabs((fSlow104 - 1))))));
	double 	fSlow110 = fabs((max((double)0, (fSlow103 - 2)) - 1));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fVec0[0] = fTemp0;
		fRec18[0] = ((fSlow32 * fRec18[1]) + (fSlow31 * (fVec0[0] + fVec0[1])));
		fRec17[0] = (fRec18[0] - (fSlow29 * ((fSlow27 * fRec17[2]) + (fSlow25 * fRec17[1]))));
		double fTemp1 = (fRec17[2] + (fRec17[0] + (2 * fRec17[1])));
		double fTemp2 = (fSlow29 * fTemp1);
		fVec1[0] = fTemp2;
		fRec16[0] = ((fSlow35 * fRec16[1]) + (fSlow34 * (fVec1[0] + fVec1[1])));
		fRec15[0] = (fRec16[0] - (fSlow22 * ((fSlow20 * fRec15[2]) + (fSlow18 * fRec15[1]))));
		double fTemp3 = (fRec15[2] + (fRec15[0] + (2 * fRec15[1])));
		double fTemp4 = (fSlow22 * fTemp3);
		fVec2[0] = fTemp4;
		fRec14[0] = ((fSlow38 * fRec14[1]) + (fSlow37 * (fVec2[0] + fVec2[1])));
		fRec13[0] = (fRec14[0] - (fSlow15 * ((fSlow13 * fRec13[2]) + (fSlow11 * fRec13[1]))));
		double fTemp5 = (fRec13[2] + (fRec13[0] + (2 * fRec13[1])));
		double fTemp6 = (fSlow15 * fTemp5);
		fVec3[0] = fTemp6;
		fRec12[0] = ((fSlow41 * fRec12[1]) + (fSlow40 * (fVec3[0] + fVec3[1])));
		fRec11[0] = (fRec12[0] - (fSlow8 * ((fSlow7 * fRec11[2]) + (fSlow5 * fRec11[1]))));
		double fTemp7 = (fSlow8 * (fRec11[2] + (fRec11[0] + (2 * fRec11[1]))));
		double 	fRec10 = max(fConst1, fabs(fTemp7));
		int iTemp8 = int((iRec8[1] < 4096));
		fRec7[0] = ((iTemp8)?max(fRec7[1], fRec10):fRec10);
		iRec8[0] = ((iTemp8)?(1 + iRec8[1]):1);
		fRec9[0] = ((iTemp8)?fRec9[1]:fRec7[1]);
		fbargraph0 = fRec9[0];
		double fTemp9 = fTemp7;
		double fTemp10 = ((iSlow44)?0:fTemp9);
		double fTemp11 = fabs(fTemp10);
		double fTemp12 = ((int((fRec5[1] > fTemp11)))?fSlow2:fSlow1);
		fRec6[0] = ((fRec6[1] * fTemp12) + (fTemp11 * (1.0 - fTemp12)));
		fRec5[0] = fRec6[0];
		fRec4[0] = ((fSlow46 * fRec4[1]) + (fSlow47 * max((fSlow45 + (20 * log10(fRec5[0]))), 0.0)));
		fRec19[0] = ((0.999 * fRec19[1]) + fSlow48);
		double fTemp13 = (fSlow49 * (fRec19[0] * ((iSlow44)?fTemp9:(fTemp10 * pow(10,(0.05 * fRec4[0]))))));
		double 	fRec3 = max(fConst1, fabs(fTemp13));
		int iTemp14 = int((iRec1[1] < 4096));
		fRec0[0] = ((iTemp14)?max(fRec0[1], fRec3):fRec3);
		iRec1[0] = ((iTemp14)?(1 + iRec1[1]):1);
		fRec2[0] = ((iTemp14)?fRec2[1]:fRec0[1]);
		fbargraph1 = fRec2[0];
		fRec32[0] = ((fSlow41 * fRec32[1]) + (fSlow40 * ((fSlow54 * fTemp5) + (fSlow53 * fVec3[1]))));
		fRec31[0] = (fRec32[0] - (fSlow8 * ((fSlow7 * fRec31[2]) + (fSlow5 * fRec31[1]))));
		double fTemp15 = (fSlow8 * (((fSlow4 * fRec31[0]) + (fSlow55 * fRec31[1])) + (fSlow4 * fRec31[2])));
		double 	fRec30 = max(fConst1, fabs(fTemp15));
		int iTemp16 = int((iRec28[1] < 4096));
		fRec27[0] = ((iTemp16)?max(fRec27[1], fRec30):fRec30);
		iRec28[0] = ((iTemp16)?(1 + iRec28[1]):1);
		fRec29[0] = ((iTemp16)?fRec29[1]:fRec27[1]);
		fbargraph2 = fRec29[0];
		double fTemp17 = fTemp15;
		double fTemp18 = ((iSlow58)?0:fTemp17);
		double fTemp19 = fabs(fTemp18);
		double fTemp20 = ((int((fRec25[1] > fTemp19)))?fSlow52:fSlow51);
		fRec26[0] = ((fRec26[1] * fTemp20) + (fTemp19 * (1.0 - fTemp20)));
		fRec25[0] = fRec26[0];
		fRec24[0] = ((fSlow60 * fRec24[1]) + (fSlow61 * max((fSlow59 + (20 * log10(fRec25[0]))), 0.0)));
		fRec33[0] = ((0.999 * fRec33[1]) + fSlow62);
		double fTemp21 = (fSlow63 * (fRec33[0] * ((iSlow58)?fTemp17:(fTemp18 * pow(10,(0.05 * fRec24[0]))))));
		double 	fRec23 = max(fConst1, fabs(fTemp21));
		int iTemp22 = int((iRec21[1] < 4096));
		fRec20[0] = ((iTemp22)?max(fRec20[1], fRec23):fRec23);
		iRec21[0] = ((iTemp22)?(1 + iRec21[1]):1);
		fRec22[0] = ((iTemp22)?fRec22[1]:fRec20[1]);
		fbargraph3 = fRec22[0];
		double fTemp23 = (fSlow5 * fRec45[1]);
		fRec47[0] = ((fSlow38 * fRec47[1]) + (fSlow37 * ((fSlow70 * fTemp3) + (fSlow69 * fVec2[1]))));
		fRec46[0] = (fRec47[0] - (fSlow15 * ((fSlow13 * fRec46[2]) + (fSlow11 * fRec46[1]))));
		fRec45[0] = ((fSlow15 * (((fSlow10 * fRec46[0]) + (fSlow71 * fRec46[1])) + (fSlow10 * fRec46[2]))) - (fSlow68 * ((fSlow67 * fRec45[2]) + fTemp23)));
		double fTemp24 = (fRec45[2] + (fSlow68 * (fTemp23 + (fSlow67 * fRec45[0]))));
		double 	fRec44 = max(fConst1, fabs(fTemp24));
		int iTemp25 = int((iRec42[1] < 4096));
		fRec41[0] = ((iTemp25)?max(fRec41[1], fRec44):fRec44);
		iRec42[0] = ((iTemp25)?(1 + iRec42[1]):1);
		fRec43[0] = ((iTemp25)?fRec43[1]:fRec41[1]);
		fbargraph4 = fRec43[0];
		double fTemp26 = fTemp24;
		double fTemp27 = ((iSlow74)?0:fTemp26);
		double fTemp28 = fabs(fTemp27);
		double fTemp29 = ((int((fRec39[1] > fTemp28)))?fSlow66:fSlow65);
		fRec40[0] = ((fRec40[1] * fTemp29) + (fTemp28 * (1.0 - fTemp29)));
		fRec39[0] = fRec40[0];
		fRec38[0] = ((fSlow76 * fRec38[1]) + (fSlow77 * max((fSlow75 + (20 * log10(fRec39[0]))), 0.0)));
		fRec48[0] = ((0.999 * fRec48[1]) + fSlow78);
		double fTemp30 = (fSlow79 * (fRec48[0] * ((iSlow74)?fTemp26:(fTemp27 * pow(10,(0.05 * fRec38[0]))))));
		double 	fRec37 = max(fConst1, fabs(fTemp30));
		int iTemp31 = int((iRec35[1] < 4096));
		fRec34[0] = ((iTemp31)?max(fRec34[1], fRec37):fRec37);
		iRec35[0] = ((iTemp31)?(1 + iRec35[1]):1);
		fRec36[0] = ((iTemp31)?fRec36[1]:fRec34[1]);
		fbargraph5 = fRec36[0];
		double fTemp32 = (fSlow5 * fRec60[1]);
		double fTemp33 = (fSlow11 * fRec61[1]);
		fRec63[0] = ((fSlow35 * fRec63[1]) + (fSlow34 * ((fSlow86 * fTemp1) + (fSlow85 * fVec1[1]))));
		fRec62[0] = (fRec63[0] - (fSlow22 * ((fSlow20 * fRec62[2]) + (fSlow18 * fRec62[1]))));
		fRec61[0] = ((fSlow22 * (((fSlow17 * fRec62[0]) + (fSlow87 * fRec62[1])) + (fSlow17 * fRec62[2]))) - (fSlow84 * ((fSlow83 * fRec61[2]) + fTemp33)));
		fRec60[0] = ((fRec61[2] + (fSlow84 * (fTemp33 + (fSlow83 * fRec61[0])))) - (fSlow68 * ((fSlow67 * fRec60[2]) + fTemp32)));
		double fTemp34 = (fRec60[2] + (fSlow68 * (fTemp32 + (fSlow67 * fRec60[0]))));
		double 	fRec59 = max(fConst1, fabs(fTemp34));
		int iTemp35 = int((iRec57[1] < 4096));
		fRec56[0] = ((iTemp35)?max(fRec56[1], fRec59):fRec59);
		iRec57[0] = ((iTemp35)?(1 + iRec57[1]):1);
		fRec58[0] = ((iTemp35)?fRec58[1]:fRec56[1]);
		fbargraph6 = fRec58[0];
		double fTemp36 = fTemp34;
		double fTemp37 = ((iSlow90)?0:fTemp36);
		double fTemp38 = fabs(fTemp37);
		double fTemp39 = ((int((fRec54[1] > fTemp38)))?fSlow82:fSlow81);
		fRec55[0] = ((fRec55[1] * fTemp39) + (fTemp38 * (1.0 - fTemp39)));
		fRec54[0] = fRec55[0];
		fRec53[0] = ((fSlow92 * fRec53[1]) + (fSlow93 * max((fSlow91 + (20 * log10(fRec54[0]))), 0.0)));
		fRec64[0] = ((0.999 * fRec64[1]) + fSlow94);
		double fTemp40 = (fSlow95 * (fRec64[0] * ((iSlow90)?fTemp36:(fTemp37 * pow(10,(0.05 * fRec53[0]))))));
		double 	fRec52 = max(fConst1, fabs(fTemp40));
		int iTemp41 = int((iRec50[1] < 4096));
		fRec49[0] = ((iTemp41)?max(fRec49[1], fRec52):fRec52);
		iRec50[0] = ((iTemp41)?(1 + iRec50[1]):1);
		fRec51[0] = ((iTemp41)?fRec51[1]:fRec49[1]);
		fbargraph7 = fRec51[0];
		double fTemp42 = (fSlow5 * fRec76[1]);
		double fTemp43 = (fSlow11 * fRec77[1]);
		double fTemp44 = (fSlow18 * fRec78[1]);
		fRec80[0] = ((fSlow32 * fRec80[1]) + (fSlow31 * ((fSlow26 * fVec0[0]) + (fSlow101 * fVec0[1]))));
		fRec79[0] = (fRec80[0] - (fSlow29 * ((fSlow27 * fRec79[2]) + (fSlow25 * fRec79[1]))));
		fRec78[0] = ((fSlow29 * (((fSlow24 * fRec79[0]) + (fSlow102 * fRec79[1])) + (fSlow24 * fRec79[2]))) - (fSlow100 * ((fSlow99 * fRec78[2]) + fTemp44)));
		fRec77[0] = ((fRec78[2] + (fSlow100 * (fTemp44 + (fSlow99 * fRec78[0])))) - (fSlow84 * ((fSlow83 * fRec77[2]) + fTemp43)));
		fRec76[0] = ((fRec77[2] + (fSlow84 * (fTemp43 + (fSlow83 * fRec77[0])))) - (fSlow68 * ((fSlow67 * fRec76[2]) + fTemp42)));
		double fTemp45 = (fRec76[2] + (fSlow68 * (fTemp42 + (fSlow67 * fRec76[0]))));
		double 	fRec75 = max(fConst1, fabs(fTemp45));
		int iTemp46 = int((iRec73[1] < 4096));
		fRec72[0] = ((iTemp46)?max(fRec72[1], fRec75):fRec75);
		iRec73[0] = ((iTemp46)?(1 + iRec73[1]):1);
		fRec74[0] = ((iTemp46)?fRec74[1]:fRec72[1]);
		fbargraph8 = fRec74[0];
		double fTemp47 = fTemp45;
		double fTemp48 = ((iSlow105)?0:fTemp47);
		double fTemp49 = fabs(fTemp48);
		double fTemp50 = ((int((fRec70[1] > fTemp49)))?fSlow98:fSlow97);
		fRec71[0] = ((fRec71[1] * fTemp50) + (fTemp49 * (1.0 - fTemp50)));
		fRec70[0] = fRec71[0];
		fRec69[0] = ((fSlow107 * fRec69[1]) + (fSlow108 * max((fSlow106 + (20 * log10(fRec70[0]))), 0.0)));
		fRec81[0] = ((0.999 * fRec81[1]) + fSlow109);
		double fTemp51 = (fSlow110 * (fRec81[0] * ((iSlow105)?fTemp47:(fTemp48 * pow(10,(0.05 * fRec69[0]))))));
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
		fRec69[1] = fRec69[0];
		fRec70[1] = fRec70[0];
		fRec71[1] = fRec71[0];
		fRec74[1] = fRec74[0];
		iRec73[1] = iRec73[0];
		fRec72[1] = fRec72[0];
		fRec76[2] = fRec76[1]; fRec76[1] = fRec76[0];
		fRec77[2] = fRec77[1]; fRec77[1] = fRec77[0];
		fRec78[2] = fRec78[1]; fRec78[1] = fRec78[0];
		fRec79[2] = fRec79[1]; fRec79[1] = fRec79[0];
		fRec80[1] = fRec80[0];
		fRec51[1] = fRec51[0];
		iRec50[1] = iRec50[0];
		fRec49[1] = fRec49[0];
		fRec64[1] = fRec64[0];
		fRec53[1] = fRec53[0];
		fRec54[1] = fRec54[0];
		fRec55[1] = fRec55[0];
		fRec58[1] = fRec58[0];
		iRec57[1] = iRec57[0];
		fRec56[1] = fRec56[0];
		fRec60[2] = fRec60[1]; fRec60[1] = fRec60[0];
		fRec61[2] = fRec61[1]; fRec61[1] = fRec61[0];
		fRec62[2] = fRec62[1]; fRec62[1] = fRec62[0];
		fRec63[1] = fRec63[0];
		fRec36[1] = fRec36[0];
		iRec35[1] = iRec35[0];
		fRec34[1] = fRec34[0];
		fRec48[1] = fRec48[0];
		fRec38[1] = fRec38[0];
		fRec39[1] = fRec39[0];
		fRec40[1] = fRec40[0];
		fRec43[1] = fRec43[0];
		iRec42[1] = iRec42[0];
		fRec41[1] = fRec41[0];
		fRec45[2] = fRec45[1]; fRec45[1] = fRec45[0];
		fRec46[2] = fRec46[1]; fRec46[1] = fRec46[0];
		fRec47[1] = fRec47[0];
		fRec22[1] = fRec22[0];
		iRec21[1] = iRec21[0];
		fRec20[1] = fRec20[0];
		fRec33[1] = fRec33[0];
		fRec24[1] = fRec24[0];
		fRec25[1] = fRec25[0];
		fRec26[1] = fRec26[0];
		fRec29[1] = fRec29[0];
		iRec28[1] = iRec28[0];
		fRec27[1] = fRec27[0];
		fRec31[2] = fRec31[1]; fRec31[1] = fRec31[0];
		fRec32[1] = fRec32[0];
		fRec2[1] = fRec2[0];
		iRec1[1] = iRec1[0];
		fRec0[1] = fRec0[0];
		fRec19[1] = fRec19[0];
		fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		fRec9[1] = fRec9[0];
		iRec8[1] = iRec8[0];
		fRec7[1] = fRec7[0];
		fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
		fRec12[1] = fRec12[0];
		fVec3[1] = fVec3[0];
		fRec13[2] = fRec13[1]; fRec13[1] = fRec13[0];
		fRec14[1] = fRec14[0];
		fVec2[1] = fVec2[0];
		fRec15[2] = fRec15[1]; fRec15[1] = fRec15[0];
		fRec16[1] = fRec16[0];
		fVec1[1] = fVec1[0];
		fRec17[2] = fRec17[1]; fRec17[1] = fRec17[0];
		fRec18[1] = fRec18[0];
		fVec0[1] = fVec0[0];
	}
#undef fslider0
#undef fslider1
#undef fslider2
#undef fslider3
#undef fslider4
#undef fslider5
#undef fbargraph0
#undef fslider6
#undef fslider7
#undef fslider8
#undef fslider9
#undef fbargraph1
#undef fslider10
#undef fslider11
#undef fbargraph2
#undef fslider12
#undef fslider13
#undef fslider14
#undef fslider15
#undef fbargraph3
#undef fslider16
#undef fslider17
#undef fbargraph4
#undef fslider18
#undef fslider19
#undef fslider20
#undef fslider21
#undef fbargraph5
#undef fslider22
#undef fslider23
#undef fbargraph6
#undef fslider24
#undef fslider25
#undef fslider26
#undef fslider27
#undef fbargraph7
#undef fslider28
#undef fslider29
#undef fbargraph8
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
	// static const value_pair fslider6_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	case MODE1: 
		fslider6_ = (float*)data; // , 1.0, 1.0, 3.0, 1.0 
		break;
	// static const value_pair fslider12_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	case MODE2: 
		fslider12_ = (float*)data; // , 1.0, 1.0, 3.0, 1.0 
		break;
	// static const value_pair fslider18_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	case MODE3: 
		fslider18_ = (float*)data; // , 1.0, 1.0, 3.0, 1.0 
		break;
	// static const value_pair fslider24_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	case MODE4: 
		fslider24_ = (float*)data; // , 1.0, 1.0, 3.0, 1.0 
		break;
	// static const value_pair fslider30_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	case MODE5: 
		fslider30_ = (float*)data; // , 1.0, 1.0, 3.0, 1.0 
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
		fslider0_ = (float*)data; // , 0.012, 0.001, 1.0, 0.001 
		break;
	case ATTACK2: 
		fslider10_ = (float*)data; // , 0.012, 0.001, 1.0, 0.001 
		break;
	case ATTACK3: 
		fslider16_ = (float*)data; // , 0.012, 0.001, 1.0, 0.001 
		break;
	case ATTACK4: 
		fslider22_ = (float*)data; // , 0.012, 0.001, 1.0, 0.001 
		break;
	case ATTACK5: 
		fslider28_ = (float*)data; // , 0.012, 0.001, 1.0, 0.001 
		break;
	case RELEASE1: 
		fslider1_ = (float*)data; // , 1.25, 0.01, 1e+01, 0.01 
		break;
	case RELEASE2: 
		fslider11_ = (float*)data; // , 1.25, 0.01, 1e+01, 0.01 
		break;
	case RELEASE3: 
		fslider17_ = (float*)data; // , 1.25, 0.01, 1e+01, 0.01 
		break;
	case RELEASE4: 
		fslider23_ = (float*)data; // , 1.25, 0.01, 1e+01, 0.01 
		break;
	case RELEASE5: 
		fslider29_ = (float*)data; // , 1.25, 0.01, 1e+01, 0.01 
		break;
	case CROSSOVER_B1_B2: 
		fslider2_ = (float*)data; // , 8e+01, 2e+01, 2e+04, 1.08 
		break;
	case CROSSOVER_B2_B3: 
		fslider3_ = (float*)data; // , 2.1e+02, 2e+01, 2e+04, 1.08 
		break;
	case CROSSOVER_B3_B4: 
		fslider4_ = (float*)data; // , 1.7e+03, 2e+01, 2e+04, 1.08 
		break;
	case CROSSOVER_B4_B5: 
		fslider5_ = (float*)data; // , 5e+03, 2e+01, 2e+04, 1.08 
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
