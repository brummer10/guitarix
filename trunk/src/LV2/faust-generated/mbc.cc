// generated from file '../src/LV2/faust/mbc.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)


namespace mbc {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	int 	iConst0;
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
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT	*fslider4_;
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT	*fslider5_;
	double 	fRec6[2];
	FAUSTFLOAT 	fslider6;
	FAUSTFLOAT	*fslider6_;
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
	double 	fRec32[2];
	double 	fRec31[3];
	double 	fRec27[2];
	int 	iRec28[2];
	double 	fRec29[2];
	FAUSTFLOAT 	fbargraph2;
	FAUSTFLOAT	*fbargraph2_;
	FAUSTFLOAT 	fslider10;
	FAUSTFLOAT	*fslider10_;
	FAUSTFLOAT 	fslider11;
	FAUSTFLOAT	*fslider11_;
	double 	fRec26[2];
	FAUSTFLOAT 	fslider12;
	FAUSTFLOAT	*fslider12_;
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
	double 	fRec47[2];
	double 	fRec46[3];
	double 	fRec45[3];
	double 	fRec41[2];
	int 	iRec42[2];
	double 	fRec43[2];
	FAUSTFLOAT 	fbargraph4;
	FAUSTFLOAT	*fbargraph4_;
	FAUSTFLOAT 	fslider16;
	FAUSTFLOAT	*fslider16_;
	FAUSTFLOAT 	fslider17;
	FAUSTFLOAT	*fslider17_;
	double 	fRec40[2];
	FAUSTFLOAT 	fslider18;
	FAUSTFLOAT	*fslider18_;
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
	double 	fRec63[2];
	double 	fRec62[3];
	double 	fRec61[3];
	double 	fRec60[3];
	double 	fRec56[2];
	int 	iRec57[2];
	double 	fRec58[2];
	FAUSTFLOAT 	fbargraph6;
	FAUSTFLOAT	*fbargraph6_;
	FAUSTFLOAT 	fslider22;
	FAUSTFLOAT	*fslider22_;
	FAUSTFLOAT 	fslider23;
	FAUSTFLOAT	*fslider23_;
	double 	fRec55[2];
	FAUSTFLOAT 	fslider24;
	FAUSTFLOAT	*fslider24_;
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
	FAUSTFLOAT 	fslider28;
	FAUSTFLOAT	*fslider28_;
	FAUSTFLOAT 	fslider29;
	FAUSTFLOAT	*fslider29_;
	double 	fRec71[2];
	FAUSTFLOAT 	fslider30;
	FAUSTFLOAT	*fslider30_;
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
	double 	fSlow1 = (1.0 / faustpower<2>(fSlow0));
	double 	fSlow2 = (2 * (1 - fSlow1));
	double 	fSlow3 = (1.0 / fSlow0);
	double 	fSlow4 = (1 + ((fSlow3 - 1.0000000000000004) / fSlow0));
	double 	fSlow5 = (1.0 / (1 + ((fSlow3 + 1.0000000000000004) / fSlow0)));
	double 	fSlow6 = tan((fConst2 * double(fslider1)));
	double 	fSlow7 = (1.0 / faustpower<2>(fSlow6));
	double 	fSlow8 = (2 * (1 - fSlow7));
	double 	fSlow9 = (1.0 / fSlow6);
	double 	fSlow10 = (1 + ((fSlow9 - 1.0000000000000004) / fSlow6));
	double 	fSlow11 = (1 + ((fSlow9 + 1.0000000000000004) / fSlow6));
	double 	fSlow12 = (1.0 / fSlow11);
	double 	fSlow13 = tan((fConst2 * double(fslider2)));
	double 	fSlow14 = (1.0 / faustpower<2>(fSlow13));
	double 	fSlow15 = (2 * (1 - fSlow14));
	double 	fSlow16 = (1.0 / fSlow13);
	double 	fSlow17 = (1 + ((fSlow16 - 1.0000000000000004) / fSlow13));
	double 	fSlow18 = (1 + ((fSlow16 + 1.0000000000000004) / fSlow13));
	double 	fSlow19 = (1.0 / fSlow18);
	double 	fSlow20 = tan((fConst2 * double(fslider3)));
	double 	fSlow21 = (1.0 / faustpower<2>(fSlow20));
	double 	fSlow22 = (2 * (1 - fSlow21));
	double 	fSlow23 = (1.0 / fSlow20);
	double 	fSlow24 = (1 + ((fSlow23 - 1.0000000000000004) / fSlow20));
	double 	fSlow25 = (1 + ((1.0000000000000004 + fSlow23) / fSlow20));
	double 	fSlow26 = (1.0 / fSlow25);
	double 	fSlow27 = (1 + fSlow23);
	double 	fSlow28 = (1.0 / fSlow27);
	double 	fSlow29 = (0 - ((1 - fSlow23) / fSlow27));
	double 	fSlow30 = (1 + fSlow16);
	double 	fSlow31 = (1.0 / fSlow30);
	double 	fSlow32 = (0 - ((1 - fSlow16) / fSlow30));
	double 	fSlow33 = (1 + fSlow9);
	double 	fSlow34 = (1.0 / fSlow33);
	double 	fSlow35 = (0 - ((1 - fSlow9) / fSlow33));
	double 	fSlow36 = (1 + fSlow3);
	double 	fSlow37 = (1.0 / fSlow36);
	double 	fSlow38 = (0 - ((1 - fSlow3) / fSlow36));
	double 	fSlow39 = double(fslider4);
	double 	fSlow40 = max((double)0, (fSlow39 - 1));
	int 	iSlow41 = int(fSlow40);
	double 	fSlow42 = exp((0 - (fConst1 / double(fslider5))));
	double 	fSlow43 = (1.0 - fSlow42);
	double 	fSlow44 = double(fslider6);
	double 	fSlow45 = exp((0 - (fConst1 / fSlow44)));
	double 	fSlow46 = (1.0 - fSlow45);
	double 	fSlow47 = double(fslider7);
	double 	fSlow48 = exp((0 - (fConst3 / fSlow44)));
	double 	fSlow49 = (((1.0 / double(double(fslider8))) - 1.0) * (1.0 - fSlow48));
	double 	fSlow50 = (0.0010000000000000009 * pow(10,(0.05 * ((fSlow47 - double(fslider9)) * fabs((fSlow40 - 1))))));
	double 	fSlow51 = fabs((max((double)0, (fSlow39 - 2)) - 1));
	double 	fSlow52 = (0 - fSlow3);
	double 	fSlow53 = (1.0 / (fSlow0 * fSlow11));
	double 	fSlow54 = (2 * (0 - fSlow1));
	double 	fSlow55 = double(fslider10);
	double 	fSlow56 = max((double)0, (fSlow55 - 1));
	int 	iSlow57 = int(fSlow56);
	double 	fSlow58 = exp((0 - (fConst1 / double(fslider11))));
	double 	fSlow59 = (1.0 - fSlow58);
	double 	fSlow60 = double(fslider12);
	double 	fSlow61 = exp((0 - (fConst1 / fSlow60)));
	double 	fSlow62 = (1.0 - fSlow61);
	double 	fSlow63 = double(fslider13);
	double 	fSlow64 = exp((0 - (fConst3 / fSlow60)));
	double 	fSlow65 = (((1.0 / double(double(fslider14))) - 1.0) * (1.0 - fSlow64));
	double 	fSlow66 = (0.0010000000000000009 * pow(10,(0.05 * ((fSlow63 - double(fslider15)) * fabs((fSlow56 - 1))))));
	double 	fSlow67 = fabs((max((double)0, (fSlow55 - 2)) - 1));
	double 	fSlow68 = (1 + ((fSlow3 - 1.0) / fSlow0));
	double 	fSlow69 = (1.0 / (1 + ((1.0 + fSlow3) / fSlow0)));
	double 	fSlow70 = (0 - fSlow9);
	double 	fSlow71 = (1.0 / (fSlow6 * fSlow18));
	double 	fSlow72 = (2 * (0 - fSlow7));
	double 	fSlow73 = double(fslider16);
	double 	fSlow74 = max((double)0, (fSlow73 - 1));
	int 	iSlow75 = int(fSlow74);
	double 	fSlow76 = exp((0 - (fConst1 / double(fslider17))));
	double 	fSlow77 = (1.0 - fSlow76);
	double 	fSlow78 = double(fslider18);
	double 	fSlow79 = exp((0 - (fConst1 / fSlow78)));
	double 	fSlow80 = (1.0 - fSlow79);
	double 	fSlow81 = double(fslider19);
	double 	fSlow82 = exp((0 - (fConst3 / fSlow78)));
	double 	fSlow83 = (((1.0 / double(double(fslider20))) - 1.0) * (1.0 - fSlow82));
	double 	fSlow84 = (0.0010000000000000009 * pow(10,(0.05 * ((fSlow81 - double(fslider21)) * fabs((fSlow74 - 1))))));
	double 	fSlow85 = fabs((max((double)0, (fSlow73 - 2)) - 1));
	double 	fSlow86 = (1 + ((fSlow9 - 1.0) / fSlow6));
	double 	fSlow87 = (1.0 / (1 + ((1.0 + fSlow9) / fSlow6)));
	double 	fSlow88 = (0 - fSlow16);
	double 	fSlow89 = (1.0 / (fSlow13 * fSlow25));
	double 	fSlow90 = (2 * (0 - fSlow14));
	double 	fSlow91 = double(fslider22);
	double 	fSlow92 = max((double)0, (fSlow91 - 1));
	int 	iSlow93 = int(fSlow92);
	double 	fSlow94 = exp((0 - (fConst1 / double(fslider23))));
	double 	fSlow95 = (1.0 - fSlow94);
	double 	fSlow96 = double(fslider24);
	double 	fSlow97 = exp((0 - (fConst1 / fSlow96)));
	double 	fSlow98 = (1.0 - fSlow97);
	double 	fSlow99 = double(fslider25);
	double 	fSlow100 = exp((0 - (fConst3 / fSlow96)));
	double 	fSlow101 = (((1.0 / double(double(fslider26))) - 1.0) * (1.0 - fSlow100));
	double 	fSlow102 = (0.0010000000000000009 * pow(10,(0.05 * ((fSlow99 - double(fslider27)) * fabs((fSlow92 - 1))))));
	double 	fSlow103 = fabs((max((double)0, (fSlow91 - 2)) - 1));
	double 	fSlow104 = (1 + ((fSlow16 - 1.0) / fSlow13));
	double 	fSlow105 = (1.0 / (1 + ((1.0 + fSlow16) / fSlow13)));
	double 	fSlow106 = (0 - fSlow23);
	double 	fSlow107 = (2 * (0 - fSlow21));
	double 	fSlow108 = double(fslider28);
	double 	fSlow109 = max((double)0, (fSlow108 - 1));
	int 	iSlow110 = int(fSlow109);
	double 	fSlow111 = exp((0 - (fConst1 / double(fslider29))));
	double 	fSlow112 = (1.0 - fSlow111);
	double 	fSlow113 = double(fslider30);
	double 	fSlow114 = exp((0 - (fConst1 / fSlow113)));
	double 	fSlow115 = (1.0 - fSlow114);
	double 	fSlow116 = double(fslider31);
	double 	fSlow117 = exp((0 - (fConst3 / fSlow113)));
	double 	fSlow118 = (((1.0 / double(double(fslider32))) - 1.0) * (1.0 - fSlow117));
	double 	fSlow119 = (0.0010000000000000009 * pow(10,(0.05 * ((fSlow116 - double(fslider33)) * fabs((fSlow109 - 1))))));
	double 	fSlow120 = fabs((max((double)0, (fSlow108 - 2)) - 1));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fVec0[0] = fTemp0;
		fRec18[0] = ((fSlow29 * fRec18[1]) + (fSlow28 * (fVec0[0] + fVec0[1])));
		fRec17[0] = (fRec18[0] - (fSlow26 * ((fSlow24 * fRec17[2]) + (fSlow22 * fRec17[1]))));
		double fTemp1 = (fRec17[2] + (fRec17[0] + (2 * fRec17[1])));
		double fTemp2 = (fSlow26 * fTemp1);
		fVec1[0] = fTemp2;
		fRec16[0] = ((fSlow32 * fRec16[1]) + (fSlow31 * (fVec1[0] + fVec1[1])));
		fRec15[0] = (fRec16[0] - (fSlow19 * ((fSlow17 * fRec15[2]) + (fSlow15 * fRec15[1]))));
		double fTemp3 = (fRec15[2] + (fRec15[0] + (2 * fRec15[1])));
		double fTemp4 = (fSlow19 * fTemp3);
		fVec2[0] = fTemp4;
		fRec14[0] = ((fSlow35 * fRec14[1]) + (fSlow34 * (fVec2[0] + fVec2[1])));
		fRec13[0] = (fRec14[0] - (fSlow12 * ((fSlow10 * fRec13[2]) + (fSlow8 * fRec13[1]))));
		double fTemp5 = (fRec13[2] + (fRec13[0] + (2 * fRec13[1])));
		double fTemp6 = (fSlow12 * fTemp5);
		fVec3[0] = fTemp6;
		fRec12[0] = ((fSlow38 * fRec12[1]) + (fSlow37 * (fVec3[0] + fVec3[1])));
		fRec11[0] = (fRec12[0] - (fSlow5 * ((fSlow4 * fRec11[2]) + (fSlow2 * fRec11[1]))));
		double fTemp7 = (fSlow5 * (fRec11[2] + (fRec11[0] + (2 * fRec11[1]))));
		double 	fRec10 = max(fConst1, fabs(fTemp7));
		int iTemp8 = int((iRec8[1] < 4096));
		fRec7[0] = ((iTemp8)?max(fRec7[1], fRec10):fRec10);
		iRec8[0] = ((iTemp8)?(1 + iRec8[1]):1);
		fRec9[0] = ((iTemp8)?fRec9[1]:fRec7[1]);
		fbargraph0 = fRec9[0];
		double fTemp9 = fTemp7;
		double fTemp10 = ((iSlow41)?0:fTemp9);
		double fTemp11 = fabs(fTemp10);
		fRec6[0] = ((fSlow42 * max(fTemp11, fRec6[1])) + (fSlow43 * fTemp11));
		fRec5[0] = ((fSlow45 * fRec5[1]) + (fSlow46 * fRec6[0]));
		fRec4[0] = ((fSlow48 * fRec4[1]) + (fSlow49 * max((fSlow47 + (20 * log10(fRec5[0]))), 0.0)));
		fRec19[0] = ((0.999 * fRec19[1]) + fSlow50);
		double fTemp12 = (fSlow51 * (fRec19[0] * ((iSlow41)?fTemp9:(fTemp10 * pow(10,(0.05 * fRec4[0]))))));
		double 	fRec3 = max(fConst1, fabs(fTemp12));
		int iTemp13 = int((iRec1[1] < 4096));
		fRec0[0] = ((iTemp13)?max(fRec0[1], fRec3):fRec3);
		iRec1[0] = ((iTemp13)?(1 + iRec1[1]):1);
		fRec2[0] = ((iTemp13)?fRec2[1]:fRec0[1]);
		fbargraph1 = fRec2[0];
		fRec32[0] = ((fSlow38 * fRec32[1]) + (fSlow37 * ((fSlow53 * fTemp5) + (fSlow52 * fVec3[1]))));
		fRec31[0] = (fRec32[0] - (fSlow5 * ((fSlow4 * fRec31[2]) + (fSlow2 * fRec31[1]))));
		double fTemp14 = (fSlow5 * (((fSlow1 * fRec31[0]) + (fSlow54 * fRec31[1])) + (fSlow1 * fRec31[2])));
		double 	fRec30 = max(fConst1, fabs(fTemp14));
		int iTemp15 = int((iRec28[1] < 4096));
		fRec27[0] = ((iTemp15)?max(fRec27[1], fRec30):fRec30);
		iRec28[0] = ((iTemp15)?(1 + iRec28[1]):1);
		fRec29[0] = ((iTemp15)?fRec29[1]:fRec27[1]);
		fbargraph2 = fRec29[0];
		double fTemp16 = fTemp14;
		double fTemp17 = ((iSlow57)?0:fTemp16);
		double fTemp18 = fabs(fTemp17);
		fRec26[0] = ((fSlow58 * max(fTemp18, fRec26[1])) + (fSlow59 * fTemp18));
		fRec25[0] = ((fSlow61 * fRec25[1]) + (fSlow62 * fRec26[0]));
		fRec24[0] = ((fSlow64 * fRec24[1]) + (fSlow65 * max((fSlow63 + (20 * log10(fRec25[0]))), 0.0)));
		fRec33[0] = ((0.999 * fRec33[1]) + fSlow66);
		double fTemp19 = (fSlow67 * (fRec33[0] * ((iSlow57)?fTemp16:(fTemp17 * pow(10,(0.05 * fRec24[0]))))));
		double 	fRec23 = max(fConst1, fabs(fTemp19));
		int iTemp20 = int((iRec21[1] < 4096));
		fRec20[0] = ((iTemp20)?max(fRec20[1], fRec23):fRec23);
		iRec21[0] = ((iTemp20)?(1 + iRec21[1]):1);
		fRec22[0] = ((iTemp20)?fRec22[1]:fRec20[1]);
		fbargraph3 = fRec22[0];
		double fTemp21 = (fSlow2 * fRec45[1]);
		fRec47[0] = ((fSlow35 * fRec47[1]) + (fSlow34 * ((fSlow71 * fTemp3) + (fSlow70 * fVec2[1]))));
		fRec46[0] = (fRec47[0] - (fSlow12 * ((fSlow10 * fRec46[2]) + (fSlow8 * fRec46[1]))));
		fRec45[0] = ((fSlow12 * (((fSlow7 * fRec46[0]) + (fSlow72 * fRec46[1])) + (fSlow7 * fRec46[2]))) - (fSlow69 * ((fSlow68 * fRec45[2]) + fTemp21)));
		double fTemp22 = (fRec45[2] + (fSlow69 * (fTemp21 + (fSlow68 * fRec45[0]))));
		double 	fRec44 = max(fConst1, fabs(fTemp22));
		int iTemp23 = int((iRec42[1] < 4096));
		fRec41[0] = ((iTemp23)?max(fRec41[1], fRec44):fRec44);
		iRec42[0] = ((iTemp23)?(1 + iRec42[1]):1);
		fRec43[0] = ((iTemp23)?fRec43[1]:fRec41[1]);
		fbargraph4 = fRec43[0];
		double fTemp24 = fTemp22;
		double fTemp25 = ((iSlow75)?0:fTemp24);
		double fTemp26 = fabs(fTemp25);
		fRec40[0] = ((fSlow76 * max(fTemp26, fRec40[1])) + (fSlow77 * fTemp26));
		fRec39[0] = ((fSlow79 * fRec39[1]) + (fSlow80 * fRec40[0]));
		fRec38[0] = ((fSlow82 * fRec38[1]) + (fSlow83 * max((fSlow81 + (20 * log10(fRec39[0]))), 0.0)));
		fRec48[0] = ((0.999 * fRec48[1]) + fSlow84);
		double fTemp27 = (fSlow85 * (fRec48[0] * ((iSlow75)?fTemp24:(fTemp25 * pow(10,(0.05 * fRec38[0]))))));
		double 	fRec37 = max(fConst1, fabs(fTemp27));
		int iTemp28 = int((iRec35[1] < 4096));
		fRec34[0] = ((iTemp28)?max(fRec34[1], fRec37):fRec37);
		iRec35[0] = ((iTemp28)?(1 + iRec35[1]):1);
		fRec36[0] = ((iTemp28)?fRec36[1]:fRec34[1]);
		fbargraph5 = fRec36[0];
		double fTemp29 = (fSlow2 * fRec60[1]);
		double fTemp30 = (fSlow8 * fRec61[1]);
		fRec63[0] = ((fSlow32 * fRec63[1]) + (fSlow31 * ((fSlow89 * fTemp1) + (fSlow88 * fVec1[1]))));
		fRec62[0] = (fRec63[0] - (fSlow19 * ((fSlow17 * fRec62[2]) + (fSlow15 * fRec62[1]))));
		fRec61[0] = ((fSlow19 * (((fSlow14 * fRec62[0]) + (fSlow90 * fRec62[1])) + (fSlow14 * fRec62[2]))) - (fSlow87 * ((fSlow86 * fRec61[2]) + fTemp30)));
		fRec60[0] = ((fRec61[2] + (fSlow87 * (fTemp30 + (fSlow86 * fRec61[0])))) - (fSlow69 * ((fSlow68 * fRec60[2]) + fTemp29)));
		double fTemp31 = (fRec60[2] + (fSlow69 * (fTemp29 + (fSlow68 * fRec60[0]))));
		double 	fRec59 = max(fConst1, fabs(fTemp31));
		int iTemp32 = int((iRec57[1] < 4096));
		fRec56[0] = ((iTemp32)?max(fRec56[1], fRec59):fRec59);
		iRec57[0] = ((iTemp32)?(1 + iRec57[1]):1);
		fRec58[0] = ((iTemp32)?fRec58[1]:fRec56[1]);
		fbargraph6 = fRec58[0];
		double fTemp33 = fTemp31;
		double fTemp34 = ((iSlow93)?0:fTemp33);
		double fTemp35 = fabs(fTemp34);
		fRec55[0] = ((fSlow94 * max(fTemp35, fRec55[1])) + (fSlow95 * fTemp35));
		fRec54[0] = ((fSlow97 * fRec54[1]) + (fSlow98 * fRec55[0]));
		fRec53[0] = ((fSlow100 * fRec53[1]) + (fSlow101 * max((fSlow99 + (20 * log10(fRec54[0]))), 0.0)));
		fRec64[0] = ((0.999 * fRec64[1]) + fSlow102);
		double fTemp36 = (fSlow103 * (fRec64[0] * ((iSlow93)?fTemp33:(fTemp34 * pow(10,(0.05 * fRec53[0]))))));
		double 	fRec52 = max(fConst1, fabs(fTemp36));
		int iTemp37 = int((iRec50[1] < 4096));
		fRec49[0] = ((iTemp37)?max(fRec49[1], fRec52):fRec52);
		iRec50[0] = ((iTemp37)?(1 + iRec50[1]):1);
		fRec51[0] = ((iTemp37)?fRec51[1]:fRec49[1]);
		fbargraph7 = fRec51[0];
		double fTemp38 = (fSlow2 * fRec76[1]);
		double fTemp39 = (fSlow8 * fRec77[1]);
		double fTemp40 = (fSlow15 * fRec78[1]);
		fRec80[0] = ((fSlow29 * fRec80[1]) + (fSlow28 * ((fSlow23 * fVec0[0]) + (fSlow106 * fVec0[1]))));
		fRec79[0] = (fRec80[0] - (fSlow26 * ((fSlow24 * fRec79[2]) + (fSlow22 * fRec79[1]))));
		fRec78[0] = ((fSlow26 * (((fSlow21 * fRec79[0]) + (fSlow107 * fRec79[1])) + (fSlow21 * fRec79[2]))) - (fSlow105 * ((fSlow104 * fRec78[2]) + fTemp40)));
		fRec77[0] = ((fRec78[2] + (fSlow105 * (fTemp40 + (fSlow104 * fRec78[0])))) - (fSlow87 * ((fSlow86 * fRec77[2]) + fTemp39)));
		fRec76[0] = ((fRec77[2] + (fSlow87 * (fTemp39 + (fSlow86 * fRec77[0])))) - (fSlow69 * ((fSlow68 * fRec76[2]) + fTemp38)));
		double fTemp41 = (fRec76[2] + (fSlow69 * (fTemp38 + (fSlow68 * fRec76[0]))));
		double 	fRec75 = max(fConst1, fabs(fTemp41));
		int iTemp42 = int((iRec73[1] < 4096));
		fRec72[0] = ((iTemp42)?max(fRec72[1], fRec75):fRec75);
		iRec73[0] = ((iTemp42)?(1 + iRec73[1]):1);
		fRec74[0] = ((iTemp42)?fRec74[1]:fRec72[1]);
		fbargraph8 = fRec74[0];
		double fTemp43 = fTemp41;
		double fTemp44 = ((iSlow110)?0:fTemp43);
		double fTemp45 = fabs(fTemp44);
		fRec71[0] = ((fSlow111 * max(fTemp45, fRec71[1])) + (fSlow112 * fTemp45));
		fRec70[0] = ((fSlow114 * fRec70[1]) + (fSlow115 * fRec71[0]));
		fRec69[0] = ((fSlow117 * fRec69[1]) + (fSlow118 * max((fSlow116 + (20 * log10(fRec70[0]))), 0.0)));
		fRec81[0] = ((0.999 * fRec81[1]) + fSlow119);
		double fTemp46 = (fSlow120 * (fRec81[0] * ((iSlow110)?fTemp43:(fTemp44 * pow(10,(0.05 * fRec69[0]))))));
		double 	fRec68 = max(fConst1, fabs(fTemp46));
		int iTemp47 = int((iRec66[1] < 4096));
		fRec65[0] = ((iTemp47)?max(fRec65[1], fRec68):fRec68);
		iRec66[0] = ((iTemp47)?(1 + iRec66[1]):1);
		fRec67[0] = ((iTemp47)?fRec67[1]:fRec65[1]);
		fbargraph9 = fRec67[0];
		output0[i] = (FAUSTFLOAT)((((fTemp46 + fTemp36) + fTemp27) + fTemp19) + fTemp12);
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
		fslider6_ = (float*)data; // , 0.012, 0.001, 1.0, 0.001 
		break;
	case ATTACK2: 
		fslider12_ = (float*)data; // , 0.012, 0.001, 1.0, 0.001 
		break;
	case ATTACK3: 
		fslider18_ = (float*)data; // , 0.012, 0.001, 1.0, 0.001 
		break;
	case ATTACK4: 
		fslider24_ = (float*)data; // , 0.012, 0.001, 1.0, 0.001 
		break;
	case ATTACK5: 
		fslider30_ = (float*)data; // , 0.012, 0.001, 1.0, 0.001 
		break;
	case RELEASE1: 
		fslider5_ = (float*)data; // , 1.25, 0.01, 1e+01, 0.01 
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
