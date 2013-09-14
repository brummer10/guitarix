// generated from file '../src/LV2/faust/mbc.dsp' by dsp2cc:
// Code generated with Faust 0.9.58 (http://faust.grame.fr)


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
	double 	fConst3;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fVec0[2];
	double 	fRec7[2];
	double 	fRec6[3];
	double 	fVec1[2];
	double 	fRec5[2];
	double 	fRec4[3];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT	*fslider4_;
	double 	fRec3[2];
	double 	fRec2[2];
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT	*fslider5_;
	FAUSTFLOAT 	fslider6;
	FAUSTFLOAT	*fslider6_;
	double 	fRec1[2];
	FAUSTFLOAT 	fslider7;
	FAUSTFLOAT	*fslider7_;
	double 	fRec8[2];
	FAUSTFLOAT 	fbargraph0;
	FAUSTFLOAT	*fbargraph0_;
	FAUSTFLOAT 	fslider8;
	FAUSTFLOAT	*fslider8_;
	double 	fRec14[2];
	double 	fRec13[3];
	FAUSTFLOAT 	fslider9;
	FAUSTFLOAT	*fslider9_;
	FAUSTFLOAT 	fslider10;
	FAUSTFLOAT	*fslider10_;
	double 	fRec12[2];
	double 	fRec11[2];
	FAUSTFLOAT 	fslider11;
	FAUSTFLOAT	*fslider11_;
	FAUSTFLOAT 	fslider12;
	FAUSTFLOAT	*fslider12_;
	double 	fRec10[2];
	FAUSTFLOAT 	fslider13;
	FAUSTFLOAT	*fslider13_;
	double 	fRec15[2];
	FAUSTFLOAT 	fbargraph1;
	FAUSTFLOAT	*fbargraph1_;
	FAUSTFLOAT 	fslider14;
	FAUSTFLOAT	*fslider14_;
	FAUSTFLOAT 	fslider15;
	FAUSTFLOAT	*fslider15_;
	double 	fRec23[2];
	double 	fRec22[3];
	double 	fVec2[2];
	double 	fRec21[2];
	double 	fRec20[3];
	FAUSTFLOAT 	fslider16;
	FAUSTFLOAT	*fslider16_;
	FAUSTFLOAT 	fslider17;
	FAUSTFLOAT	*fslider17_;
	double 	fRec19[2];
	double 	fRec18[2];
	FAUSTFLOAT 	fslider18;
	FAUSTFLOAT	*fslider18_;
	FAUSTFLOAT 	fslider19;
	FAUSTFLOAT	*fslider19_;
	double 	fRec17[2];
	FAUSTFLOAT 	fslider20;
	FAUSTFLOAT	*fslider20_;
	double 	fRec24[2];
	FAUSTFLOAT 	fbargraph2;
	FAUSTFLOAT	*fbargraph2_;
	FAUSTFLOAT 	fslider21;
	FAUSTFLOAT	*fslider21_;
	FAUSTFLOAT 	fslider22;
	FAUSTFLOAT	*fslider22_;
	double 	fRec32[2];
	double 	fRec31[3];
	double 	fVec3[2];
	double 	fRec30[2];
	double 	fRec29[3];
	FAUSTFLOAT 	fslider23;
	FAUSTFLOAT	*fslider23_;
	FAUSTFLOAT 	fslider24;
	FAUSTFLOAT	*fslider24_;
	double 	fRec28[2];
	double 	fRec27[2];
	FAUSTFLOAT 	fslider25;
	FAUSTFLOAT	*fslider25_;
	FAUSTFLOAT 	fslider26;
	FAUSTFLOAT	*fslider26_;
	double 	fRec26[2];
	FAUSTFLOAT 	fslider27;
	FAUSTFLOAT	*fslider27_;
	double 	fRec33[2];
	FAUSTFLOAT 	fbargraph3;
	FAUSTFLOAT	*fbargraph3_;
	FAUSTFLOAT 	fslider28;
	FAUSTFLOAT	*fslider28_;
	double 	fRec39[2];
	double 	fRec38[3];
	FAUSTFLOAT 	fslider29;
	FAUSTFLOAT	*fslider29_;
	FAUSTFLOAT 	fslider30;
	FAUSTFLOAT	*fslider30_;
	double 	fRec37[2];
	double 	fRec36[2];
	FAUSTFLOAT 	fslider31;
	FAUSTFLOAT	*fslider31_;
	FAUSTFLOAT 	fslider32;
	FAUSTFLOAT	*fslider32_;
	double 	fRec35[2];
	FAUSTFLOAT 	fslider33;
	FAUSTFLOAT	*fslider33_;
	double 	fRec40[2];
	FAUSTFLOAT 	fbargraph4;
	FAUSTFLOAT	*fbargraph4_;
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
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<3; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<3; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<3; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<3; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fRec32[i] = 0;
	for (int i=0; i<3; i++) fRec31[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec30[i] = 0;
	for (int i=0; i<3; i++) fRec29[i] = 0;
	for (int i=0; i<2; i++) fRec28[i] = 0;
	for (int i=0; i<2; i++) fRec27[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<2; i++) fRec33[i] = 0;
	for (int i=0; i<2; i++) fRec39[i] = 0;
	for (int i=0; i<3; i++) fRec38[i] = 0;
	for (int i=0; i<2; i++) fRec37[i] = 0;
	for (int i=0; i<2; i++) fRec36[i] = 0;
	for (int i=0; i<2; i++) fRec35[i] = 0;
	for (int i=0; i<2; i++) fRec40[i] = 0;
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
	fConst2 = (2.0 / double(iConst0));
	fConst3 = (3.141592653589793 / double(iConst0));
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
#define fslider4 (*fslider4_)
#define fslider5 (*fslider5_)
#define fslider6 (*fslider6_)
#define fslider7 (*fslider7_)
#define fbargraph0 (*fbargraph0_)
#define fslider8 (*fslider8_)
#define fslider9 (*fslider9_)
#define fslider10 (*fslider10_)
#define fslider11 (*fslider11_)
#define fslider12 (*fslider12_)
#define fslider13 (*fslider13_)
#define fbargraph1 (*fbargraph1_)
#define fslider14 (*fslider14_)
#define fslider15 (*fslider15_)
#define fslider16 (*fslider16_)
#define fslider17 (*fslider17_)
#define fslider18 (*fslider18_)
#define fslider19 (*fslider19_)
#define fslider20 (*fslider20_)
#define fbargraph2 (*fbargraph2_)
#define fslider21 (*fslider21_)
#define fslider22 (*fslider22_)
#define fslider23 (*fslider23_)
#define fslider24 (*fslider24_)
#define fslider25 (*fslider25_)
#define fslider26 (*fslider26_)
#define fslider27 (*fslider27_)
#define fbargraph3 (*fbargraph3_)
#define fslider28 (*fslider28_)
#define fslider29 (*fslider29_)
#define fslider30 (*fslider30_)
#define fslider31 (*fslider31_)
#define fslider32 (*fslider32_)
#define fslider33 (*fslider33_)
#define fbargraph4 (*fbargraph4_)
	double 	fSlow0 = fslider0;
	double 	fSlow1 = exp((0 - (fConst2 / fSlow0)));
	double 	fSlow2 = exp((0 - (fConst1 / fSlow0)));
	double 	fSlow3 = tan((fConst3 * fslider1));
	double 	fSlow4 = (1.0 / faustpower<2>(fSlow3));
	double 	fSlow5 = (2 * (1 - fSlow4));
	double 	fSlow6 = (1.0 / fSlow3);
	double 	fSlow7 = (1 + ((fSlow6 - 1.0000000000000004) / fSlow3));
	double 	fSlow8 = (1 + ((1.0000000000000004 + fSlow6) / fSlow3));
	double 	fSlow9 = (1.0 / fSlow8);
	double 	fSlow10 = (1 + fSlow6);
	double 	fSlow11 = (0 - ((1 - fSlow6) / fSlow10));
	double 	fSlow12 = tan((fConst3 * fslider2));
	double 	fSlow13 = (1.0 / faustpower<2>(fSlow12));
	double 	fSlow14 = (2 * (1 - fSlow13));
	double 	fSlow15 = (1.0 / fSlow12);
	double 	fSlow16 = (1 + ((fSlow15 - 1.0000000000000004) / fSlow12));
	double 	fSlow17 = (1 + ((1.0000000000000004 + fSlow15) / fSlow12));
	double 	fSlow18 = (1.0 / fSlow17);
	double 	fSlow19 = (1 + fSlow15);
	double 	fSlow20 = (0 - ((1 - fSlow15) / fSlow19));
	double 	fSlow21 = (1.0 / fSlow19);
	double 	fSlow22 = (1.0 / (fSlow17 * fSlow3));
	double 	fSlow23 = (0 - fSlow6);
	double 	fSlow24 = (1.0 / fSlow10);
	double 	fSlow25 = (2 * (0 - fSlow4));
	double 	fSlow26 = fslider3;
	double 	fSlow27 = max((double)0, (fSlow26 - 1));
	int 	iSlow28 = int(fSlow27);
	double 	fSlow29 = exp((0 - (fConst1 / fslider4)));
	double 	fSlow30 = (1.0 - fSlow29);
	double 	fSlow31 = (1.0 - fSlow2);
	double 	fSlow32 = fslider5;
	double 	fSlow33 = (((1.0 / double(fslider6)) - 1.0) * (1.0 - fSlow1));
	double 	fSlow34 = (0.0010000000000000009 * pow(10,(0.05 * ((fSlow32 - fslider7) * fabs((fSlow27 - 1))))));
	double 	fSlow35 = fabs((max((double)0, (fSlow26 - 2)) - 1));
	double 	fSlow36 = fslider8;
	double 	fSlow37 = exp((0 - (fConst2 / fSlow36)));
	double 	fSlow38 = exp((0 - (fConst1 / fSlow36)));
	double 	fSlow39 = (0 - fSlow15);
	double 	fSlow40 = (2 * (0 - fSlow13));
	double 	fSlow41 = fslider9;
	double 	fSlow42 = max((double)0, (fSlow41 - 1));
	int 	iSlow43 = int(fSlow42);
	double 	fSlow44 = exp((0 - (fConst1 / fslider10)));
	double 	fSlow45 = (1.0 - fSlow44);
	double 	fSlow46 = (1.0 - fSlow38);
	double 	fSlow47 = fslider11;
	double 	fSlow48 = (((1.0 / double(fslider12)) - 1.0) * (1.0 - fSlow37));
	double 	fSlow49 = (0.0010000000000000009 * pow(10,(0.05 * ((fSlow47 - fslider13) * fabs((fSlow42 - 1))))));
	double 	fSlow50 = fabs((max((double)0, (fSlow41 - 2)) - 1));
	double 	fSlow51 = fslider14;
	double 	fSlow52 = exp((0 - (fConst2 / fSlow51)));
	double 	fSlow53 = exp((0 - (fConst1 / fSlow51)));
	double 	fSlow54 = tan((fConst3 * fslider15));
	double 	fSlow55 = (1.0 / faustpower<2>(fSlow54));
	double 	fSlow56 = (2 * (1 - fSlow55));
	double 	fSlow57 = (1.0 / fSlow54);
	double 	fSlow58 = (1 + ((fSlow57 - 1.0000000000000004) / fSlow54));
	double 	fSlow59 = (1 + ((1.0000000000000004 + fSlow57) / fSlow54));
	double 	fSlow60 = (1.0 / fSlow59);
	double 	fSlow61 = (1 + fSlow57);
	double 	fSlow62 = (0 - ((1 - fSlow57) / fSlow61));
	double 	fSlow63 = (1.0 / (fSlow8 * fSlow54));
	double 	fSlow64 = (0 - fSlow57);
	double 	fSlow65 = (1.0 / fSlow61);
	double 	fSlow66 = (2 * (0 - fSlow55));
	double 	fSlow67 = fslider16;
	double 	fSlow68 = max((double)0, (fSlow67 - 1));
	int 	iSlow69 = int(fSlow68);
	double 	fSlow70 = exp((0 - (fConst1 / fslider17)));
	double 	fSlow71 = (1.0 - fSlow70);
	double 	fSlow72 = (1.0 - fSlow53);
	double 	fSlow73 = fslider18;
	double 	fSlow74 = (((1.0 / double(fslider19)) - 1.0) * (1.0 - fSlow52));
	double 	fSlow75 = (0.0010000000000000009 * pow(10,(0.05 * ((fSlow73 - fslider20) * fabs((fSlow68 - 1))))));
	double 	fSlow76 = fabs((max((double)0, (fSlow67 - 2)) - 1));
	double 	fSlow77 = fslider21;
	double 	fSlow78 = exp((0 - (fConst2 / fSlow77)));
	double 	fSlow79 = exp((0 - (fConst1 / fSlow77)));
	double 	fSlow80 = tan((fConst3 * fslider22));
	double 	fSlow81 = (1.0 / faustpower<2>(fSlow80));
	double 	fSlow82 = (2 * (1 - fSlow81));
	double 	fSlow83 = (1.0 / fSlow80);
	double 	fSlow84 = (1 + ((fSlow83 - 1.0000000000000004) / fSlow80));
	double 	fSlow85 = (1.0 / (1 + ((1.0000000000000004 + fSlow83) / fSlow80)));
	double 	fSlow86 = (1 + fSlow83);
	double 	fSlow87 = (0 - ((1 - fSlow83) / fSlow86));
	double 	fSlow88 = (1.0 / (fSlow59 * fSlow80));
	double 	fSlow89 = (0 - fSlow83);
	double 	fSlow90 = (1.0 / fSlow86);
	double 	fSlow91 = (2 * (0 - fSlow81));
	double 	fSlow92 = fslider23;
	double 	fSlow93 = max((double)0, (fSlow92 - 1));
	int 	iSlow94 = int(fSlow93);
	double 	fSlow95 = exp((0 - (fConst1 / fslider24)));
	double 	fSlow96 = (1.0 - fSlow95);
	double 	fSlow97 = (1.0 - fSlow79);
	double 	fSlow98 = fslider25;
	double 	fSlow99 = (((1.0 / double(fslider26)) - 1.0) * (1.0 - fSlow78));
	double 	fSlow100 = (0.0010000000000000009 * pow(10,(0.05 * ((fSlow98 - fslider27) * fabs((fSlow93 - 1))))));
	double 	fSlow101 = fabs((max((double)0, (fSlow92 - 2)) - 1));
	double 	fSlow102 = fslider28;
	double 	fSlow103 = exp((0 - (fConst2 / fSlow102)));
	double 	fSlow104 = exp((0 - (fConst1 / fSlow102)));
	double 	fSlow105 = fslider29;
	double 	fSlow106 = max((double)0, (fSlow105 - 1));
	int 	iSlow107 = int(fSlow106);
	double 	fSlow108 = exp((0 - (fConst1 / fslider30)));
	double 	fSlow109 = (1.0 - fSlow108);
	double 	fSlow110 = (1.0 - fSlow104);
	double 	fSlow111 = fslider31;
	double 	fSlow112 = (((1.0 / double(fslider32)) - 1.0) * (1.0 - fSlow103));
	double 	fSlow113 = (0.0010000000000000009 * pow(10,(0.05 * ((fSlow111 - fslider33) * fabs((fSlow106 - 1))))));
	double 	fSlow114 = fabs((max((double)0, (fSlow105 - 2)) - 1));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fVec0[0] = fTemp0;
		double fTemp1 = (fVec0[0] + fVec0[1]);
		fRec7[0] = ((fSlow21 * fTemp1) + (fSlow20 * fRec7[1]));
		fRec6[0] = (fRec7[0] - (fSlow18 * ((fSlow16 * fRec6[2]) + (fSlow14 * fRec6[1]))));
		double fTemp2 = (fRec6[2] + (fRec6[0] + (2 * fRec6[1])));
		fVec1[0] = (fSlow18 * fTemp2);
		fRec5[0] = ((fSlow24 * ((fSlow23 * fVec1[1]) + (fSlow22 * fTemp2))) + (fSlow11 * fRec5[1]));
		fRec4[0] = (fRec5[0] - (fSlow9 * ((fSlow7 * fRec4[2]) + (fSlow5 * fRec4[1]))));
		double fTemp3 = (fSlow9 * (((fSlow4 * fRec4[0]) + (fSlow25 * fRec4[1])) + (fSlow4 * fRec4[2])));
		double fTemp4 = ((iSlow28)?0:fTemp3);
		double fTemp5 = fabs(fTemp4);
		fRec3[0] = ((fSlow30 * fTemp5) + (fSlow29 * max(fTemp5, fRec3[1])));
		fRec2[0] = ((fSlow31 * fRec3[0]) + (fSlow2 * fRec2[1]));
		fRec1[0] = ((fSlow33 * max((fSlow32 + (20 * log10(fRec2[0]))), 0.0)) + (fSlow1 * fRec1[1]));
		fRec8[0] = (fSlow34 + (0.999 * fRec8[1]));
		double fTemp6 = (fSlow35 * (fRec8[0] * ((iSlow28)?fTemp3:(fTemp4 * pow(10,(0.05 * fRec1[0]))))));
		double 	fRec0 = max(fConst1, fabs(fTemp6));
		fbargraph0 = fRec0;
		fRec14[0] = ((fSlow21 * ((fSlow39 * fVec0[1]) + (fSlow15 * fVec0[0]))) + (fSlow20 * fRec14[1]));
		fRec13[0] = (fRec14[0] - (fSlow18 * ((fSlow16 * fRec13[2]) + (fSlow14 * fRec13[1]))));
		double fTemp7 = (fSlow18 * (((fSlow13 * fRec13[0]) + (fSlow40 * fRec13[1])) + (fSlow13 * fRec13[2])));
		double fTemp8 = ((iSlow43)?0:fTemp7);
		double fTemp9 = fabs(fTemp8);
		fRec12[0] = ((fSlow45 * fTemp9) + (fSlow44 * max(fTemp9, fRec12[1])));
		fRec11[0] = ((fSlow46 * fRec12[0]) + (fSlow38 * fRec11[1]));
		fRec10[0] = ((fSlow48 * max((fSlow47 + (20 * log10(fRec11[0]))), 0.0)) + (fSlow37 * fRec10[1]));
		fRec15[0] = (fSlow49 + (0.999 * fRec15[1]));
		double fTemp10 = (fSlow50 * (fRec15[0] * ((iSlow43)?fTemp7:(fTemp8 * pow(10,(0.05 * fRec10[0]))))));
		double 	fRec9 = max(fConst1, fabs(fTemp10));
		fbargraph1 = fRec9;
		fRec23[0] = ((fSlow24 * fTemp1) + (fSlow11 * fRec23[1]));
		fRec22[0] = (fRec23[0] - (fSlow9 * ((fSlow7 * fRec22[2]) + (fSlow5 * fRec22[1]))));
		double fTemp11 = (fRec22[2] + (fRec22[0] + (2 * fRec22[1])));
		fVec2[0] = (fSlow9 * fTemp11);
		fRec21[0] = ((fSlow65 * ((fSlow64 * fVec2[1]) + (fSlow63 * fTemp11))) + (fSlow62 * fRec21[1]));
		fRec20[0] = (fRec21[0] - (fSlow60 * ((fSlow58 * fRec20[2]) + (fSlow56 * fRec20[1]))));
		double fTemp12 = (fSlow60 * (((fSlow55 * fRec20[0]) + (fSlow66 * fRec20[1])) + (fSlow55 * fRec20[2])));
		double fTemp13 = ((iSlow69)?0:fTemp12);
		double fTemp14 = fabs(fTemp13);
		fRec19[0] = ((fSlow71 * fTemp14) + (fSlow70 * max(fTemp14, fRec19[1])));
		fRec18[0] = ((fSlow72 * fRec19[0]) + (fSlow53 * fRec18[1]));
		fRec17[0] = ((fSlow74 * max((fSlow73 + (20 * log10(fRec18[0]))), 0.0)) + (fSlow52 * fRec17[1]));
		fRec24[0] = (fSlow75 + (0.999 * fRec24[1]));
		double fTemp15 = (fSlow76 * (fRec24[0] * ((iSlow69)?fTemp12:(fTemp13 * pow(10,(0.05 * fRec17[0]))))));
		double 	fRec16 = max(fConst1, fabs(fTemp15));
		fbargraph2 = fRec16;
		fRec32[0] = ((fSlow65 * fTemp1) + (fSlow62 * fRec32[1]));
		fRec31[0] = (fRec32[0] - (fSlow60 * ((fSlow58 * fRec31[2]) + (fSlow56 * fRec31[1]))));
		double fTemp16 = (fRec31[2] + (fRec31[0] + (2 * fRec31[1])));
		fVec3[0] = (fSlow60 * fTemp16);
		fRec30[0] = ((fSlow90 * ((fSlow89 * fVec3[1]) + (fSlow88 * fTemp16))) + (fSlow87 * fRec30[1]));
		fRec29[0] = (fRec30[0] - (fSlow85 * ((fSlow84 * fRec29[2]) + (fSlow82 * fRec29[1]))));
		double fTemp17 = (fSlow85 * (((fSlow81 * fRec29[0]) + (fSlow91 * fRec29[1])) + (fSlow81 * fRec29[2])));
		double fTemp18 = ((iSlow94)?0:fTemp17);
		double fTemp19 = fabs(fTemp18);
		fRec28[0] = ((fSlow96 * fTemp19) + (fSlow95 * max(fTemp19, fRec28[1])));
		fRec27[0] = ((fSlow97 * fRec28[0]) + (fSlow79 * fRec27[1]));
		fRec26[0] = ((fSlow99 * max((fSlow98 + (20 * log10(fRec27[0]))), 0.0)) + (fSlow78 * fRec26[1]));
		fRec33[0] = (fSlow100 + (0.999 * fRec33[1]));
		double fTemp20 = (fSlow101 * (fRec33[0] * ((iSlow94)?fTemp17:(fTemp18 * pow(10,(0.05 * fRec26[0]))))));
		double 	fRec25 = max(fConst1, fabs(fTemp20));
		fbargraph3 = fRec25;
		fRec39[0] = ((fSlow90 * fTemp1) + (fSlow87 * fRec39[1]));
		fRec38[0] = (fRec39[0] - (fSlow85 * ((fSlow84 * fRec38[2]) + (fSlow82 * fRec38[1]))));
		double fTemp21 = (fSlow85 * (fRec38[2] + (fRec38[0] + (2 * fRec38[1]))));
		double fTemp22 = ((iSlow107)?0:fTemp21);
		double fTemp23 = fabs(fTemp22);
		fRec37[0] = ((fSlow109 * fTemp23) + (fSlow108 * max(fTemp23, fRec37[1])));
		fRec36[0] = ((fSlow110 * fRec37[0]) + (fSlow104 * fRec36[1]));
		fRec35[0] = ((fSlow112 * max((fSlow111 + (20 * log10(fRec36[0]))), 0.0)) + (fSlow103 * fRec35[1]));
		fRec40[0] = (fSlow113 + (0.999 * fRec40[1]));
		double fTemp24 = (fSlow114 * (fRec40[0] * ((iSlow107)?fTemp21:(fTemp22 * pow(10,(0.05 * fRec35[0]))))));
		double 	fRec34 = max(fConst1, fabs(fTemp24));
		fbargraph4 = fRec34;
		output0[i] = (FAUSTFLOAT)(fTemp24 + (fTemp20 + (fTemp15 + (fTemp10 + fTemp6))));
		// post processing
		fRec40[1] = fRec40[0];
		fRec35[1] = fRec35[0];
		fRec36[1] = fRec36[0];
		fRec37[1] = fRec37[0];
		fRec38[2] = fRec38[1]; fRec38[1] = fRec38[0];
		fRec39[1] = fRec39[0];
		fRec33[1] = fRec33[0];
		fRec26[1] = fRec26[0];
		fRec27[1] = fRec27[0];
		fRec28[1] = fRec28[0];
		fRec29[2] = fRec29[1]; fRec29[1] = fRec29[0];
		fRec30[1] = fRec30[0];
		fVec3[1] = fVec3[0];
		fRec31[2] = fRec31[1]; fRec31[1] = fRec31[0];
		fRec32[1] = fRec32[0];
		fRec24[1] = fRec24[0];
		fRec17[1] = fRec17[0];
		fRec18[1] = fRec18[0];
		fRec19[1] = fRec19[0];
		fRec20[2] = fRec20[1]; fRec20[1] = fRec20[0];
		fRec21[1] = fRec21[0];
		fVec2[1] = fVec2[0];
		fRec22[2] = fRec22[1]; fRec22[1] = fRec22[0];
		fRec23[1] = fRec23[0];
		fRec15[1] = fRec15[0];
		fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		fRec12[1] = fRec12[0];
		fRec13[2] = fRec13[1]; fRec13[1] = fRec13[0];
		fRec14[1] = fRec14[0];
		fRec8[1] = fRec8[0];
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fVec1[1] = fVec1[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec7[1] = fRec7[0];
		fVec0[1] = fVec0[0];
	}
#undef fslider0
#undef fslider1
#undef fslider2
#undef fslider3
#undef fslider4
#undef fslider5
#undef fslider6
#undef fslider7
#undef fbargraph0
#undef fslider8
#undef fslider9
#undef fslider10
#undef fslider11
#undef fslider12
#undef fslider13
#undef fbargraph1
#undef fslider14
#undef fslider15
#undef fslider16
#undef fslider17
#undef fslider18
#undef fslider19
#undef fslider20
#undef fbargraph2
#undef fslider21
#undef fslider22
#undef fslider23
#undef fslider24
#undef fslider25
#undef fslider26
#undef fslider27
#undef fbargraph3
#undef fslider28
#undef fslider29
#undef fslider30
#undef fslider31
#undef fslider32
#undef fslider33
#undef fbargraph4
}

void __rt_func Dsp::compute_static(int count, float *input0, float *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	// static const value_pair fslider29_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	case MODE1: 
		fslider29_ = (float*)data; // , 1.0, 1.0, 3.0, 1.0 
		break;
	// static const value_pair fslider23_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	case MODE2: 
		fslider23_ = (float*)data; // , 1.0, 1.0, 3.0, 1.0 
		break;
	// static const value_pair fslider16_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	case MODE3: 
		fslider16_ = (float*)data; // , 1.0, 1.0, 3.0, 1.0 
		break;
	// static const value_pair fslider3_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	case MODE4: 
		fslider3_ = (float*)data; // , 1.0, 1.0, 3.0, 1.0 
		break;
	// static const value_pair fslider9_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	case MODE5: 
		fslider9_ = (float*)data; // , 1.0, 1.0, 3.0, 1.0 
		break;
	case MAKEUP1: 
		fslider31_ = (float*)data; // , 13.0, -5e+01, 5e+01, 0.1 
		break;
	case MAKEUP2: 
		fslider25_ = (float*)data; // , 1e+01, -5e+01, 5e+01, 0.1 
		break;
	case MAKEUP3: 
		fslider18_ = (float*)data; // , 4.0, -5e+01, 5e+01, 0.1 
		break;
	case MAKEUP4: 
		fslider5_ = (float*)data; // , 8.0, -5e+01, 5e+01, 0.1 
		break;
	case MAKEUP5: 
		fslider11_ = (float*)data; // , 11.0, -5e+01, 5e+01, 0.1 
		break;
	case MAKEUPTHRESHOLD1: 
		fslider33_ = (float*)data; // , 2.0, 0.0, 1e+01, 0.1 
		break;
	case MAKEUPTHRESHOLD2: 
		fslider27_ = (float*)data; // , 2.0, 0.0, 1e+01, 0.1 
		break;
	case MAKEUPTHRESHOLD3: 
		fslider20_ = (float*)data; // , 2.0, 0.0, 1e+01, 0.1 
		break;
	case MAKEUPTHRESHOLD4: 
		fslider7_ = (float*)data; // , 2.0, 0.0, 1e+01, 0.1 
		break;
	case MAKEUPTHRESHOLD5: 
		fslider13_ = (float*)data; // , 2.0, 0.0, 1e+01, 0.1 
		break;
	case RATIO1: 
		fslider32_ = (float*)data; // , 2.0, 1.0, 1e+02, 0.1 
		break;
	case RATIO2: 
		fslider26_ = (float*)data; // , 2.0, 1.0, 1e+02, 0.1 
		break;
	case RATIO3: 
		fslider19_ = (float*)data; // , 2.0, 1.0, 1e+02, 0.1 
		break;
	case RATIO4: 
		fslider6_ = (float*)data; // , 2.0, 1.0, 1e+02, 0.1 
		break;
	case RATIO5: 
		fslider12_ = (float*)data; // , 2.0, 1.0, 1e+02, 0.1 
		break;
	case ATTACK1: 
		fslider28_ = (float*)data; // , 0.012, 0.0, 1.0, 0.001 
		break;
	case ATTACK2: 
		fslider21_ = (float*)data; // , 0.012, 0.0, 1.0, 0.001 
		break;
	case ATTACK3: 
		fslider14_ = (float*)data; // , 0.012, 0.0, 1.0, 0.001 
		break;
	case ATTACK4: 
		fslider0_ = (float*)data; // , 0.012, 0.0, 1.0, 0.001 
		break;
	case ATTACK5: 
		fslider8_ = (float*)data; // , 0.012, 0.0, 1.0, 0.001 
		break;
	case RELEASE1: 
		fslider30_ = (float*)data; // , 1.25, 0.0, 1e+01, 0.01 
		break;
	case RELEASE2: 
		fslider24_ = (float*)data; // , 1.25, 0.0, 1e+01, 0.01 
		break;
	case RELEASE3: 
		fslider17_ = (float*)data; // , 1.25, 0.0, 1e+01, 0.01 
		break;
	case RELEASE4: 
		fslider4_ = (float*)data; // , 1.25, 0.0, 1e+01, 0.01 
		break;
	case RELEASE5: 
		fslider10_ = (float*)data; // , 1.25, 0.0, 1e+01, 0.01 
		break;
	case CROSSOVER_B1_B2: 
		fslider22_ = (float*)data; // , 8e+01, 2e+01, 2e+04, 1.08 
		break;
	case CROSSOVER_B2_B3: 
		fslider15_ = (float*)data; // , 2.1e+02, 2e+01, 2e+04, 1.08 
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
   V1, 
   V2, 
   V3, 
   V4, 
   V5, 
} PortIndex;
*/

} // end namespace mbc
