// generated from file '../src/plugins/mbc.dsp' by dsp2cc:
// Code generated with Faust 0.9.58 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

namespace pluginlib {
namespace mbc {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	int 	iConst0;
	double 	fConst1;
	FAUSTFLOAT 	fslider0;
	double 	fConst2;
	FAUSTFLOAT 	fslider1;
	double 	fConst3;
	FAUSTFLOAT 	fslider2;
	double 	fVec0[2];
	double 	fRec10[2];
	double 	fRec9[3];
	double 	fVec1[2];
	double 	fRec8[2];
	double 	fRec7[3];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT 	fslider4;
	double 	fRec6[2];
	double 	fRec5[2];
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT 	fslider6;
	double 	fRec4[2];
	FAUSTFLOAT 	fslider7;
	double 	fRec11[2];
	double 	fRec0[2];
	int 	iRec1[2];
	double 	fRec2[2];
	FAUSTFLOAT 	fbargraph0;
	FAUSTFLOAT 	fslider8;
	double 	fRec20[2];
	double 	fRec19[3];
	FAUSTFLOAT 	fslider9;
	FAUSTFLOAT 	fslider10;
	double 	fRec18[2];
	double 	fRec17[2];
	FAUSTFLOAT 	fslider11;
	FAUSTFLOAT 	fslider12;
	double 	fRec16[2];
	FAUSTFLOAT 	fslider13;
	double 	fRec21[2];
	double 	fRec12[2];
	int 	iRec13[2];
	double 	fRec14[2];
	FAUSTFLOAT 	fbargraph1;
	FAUSTFLOAT 	fslider14;
	FAUSTFLOAT 	fslider15;
	double 	fRec32[2];
	double 	fRec31[3];
	double 	fVec2[2];
	double 	fRec30[2];
	double 	fRec29[3];
	FAUSTFLOAT 	fslider16;
	FAUSTFLOAT 	fslider17;
	double 	fRec28[2];
	double 	fRec27[2];
	FAUSTFLOAT 	fslider18;
	FAUSTFLOAT 	fslider19;
	double 	fRec26[2];
	FAUSTFLOAT 	fslider20;
	double 	fRec33[2];
	double 	fRec22[2];
	int 	iRec23[2];
	double 	fRec24[2];
	FAUSTFLOAT 	fbargraph2;
	FAUSTFLOAT 	fslider21;
	FAUSTFLOAT 	fslider22;
	double 	fRec44[2];
	double 	fRec43[3];
	double 	fVec3[2];
	double 	fRec42[2];
	double 	fRec41[3];
	FAUSTFLOAT 	fslider23;
	FAUSTFLOAT 	fslider24;
	double 	fRec40[2];
	double 	fRec39[2];
	FAUSTFLOAT 	fslider25;
	FAUSTFLOAT 	fslider26;
	double 	fRec38[2];
	FAUSTFLOAT 	fslider27;
	double 	fRec45[2];
	double 	fRec34[2];
	int 	iRec35[2];
	double 	fRec36[2];
	FAUSTFLOAT 	fbargraph3;
	FAUSTFLOAT 	fslider28;
	double 	fRec54[2];
	double 	fRec53[3];
	FAUSTFLOAT 	fslider29;
	FAUSTFLOAT 	fslider30;
	double 	fRec52[2];
	double 	fRec51[2];
	FAUSTFLOAT 	fslider31;
	FAUSTFLOAT 	fslider32;
	double 	fRec50[2];
	FAUSTFLOAT 	fslider33;
	double 	fRec55[2];
	double 	fRec46[2];
	int 	iRec47[2];
	double 	fRec48[2];
	FAUSTFLOAT 	fbargraph4;
	void clear_state_f();
	int load_ui_f(const UiBuilder& b, int form);
	void init(unsigned int samplingFreq);
	void compute(int count, float *input0, float *output0);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static int load_ui_f_static(const UiBuilder& b, int form);
	static void init_static(unsigned int samplingFreq, PluginDef*);
	static void compute_static(int count, float *input0, float *output0, PluginDef*);
	static int register_params_static(const ParamReg& reg);
	static void del_instance(PluginDef *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginDef() {
	version = PLUGINDEF_VERSION;
	flags = 0;
	id = "mbc";
	name = N_("Multi Band Compressor");
	groups = 0;
	description = N_("Multi Band Compressor contributed by kokoko3k"); // description (tooltip)
	category = N_("Guitar Effects");       // category
	shortname = N_("MB Compressor");     // shortname
	mono_audio = compute_static;
	stereo_audio = 0;
	set_samplerate = init_static;
	activate_plugin = 0;
	register_params = register_params_static;
	load_ui = load_ui_f_static;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<3; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<3; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) iRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<3; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) iRec13[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec32[i] = 0;
	for (int i=0; i<3; i++) fRec31[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec30[i] = 0;
	for (int i=0; i<3; i++) fRec29[i] = 0;
	for (int i=0; i<2; i++) fRec28[i] = 0;
	for (int i=0; i<2; i++) fRec27[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<2; i++) fRec33[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) iRec23[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fRec44[i] = 0;
	for (int i=0; i<3; i++) fRec43[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec42[i] = 0;
	for (int i=0; i<3; i++) fRec41[i] = 0;
	for (int i=0; i<2; i++) fRec40[i] = 0;
	for (int i=0; i<2; i++) fRec39[i] = 0;
	for (int i=0; i<2; i++) fRec38[i] = 0;
	for (int i=0; i<2; i++) fRec45[i] = 0;
	for (int i=0; i<2; i++) fRec34[i] = 0;
	for (int i=0; i<2; i++) iRec35[i] = 0;
	for (int i=0; i<2; i++) fRec36[i] = 0;
	for (int i=0; i<2; i++) fRec54[i] = 0;
	for (int i=0; i<3; i++) fRec53[i] = 0;
	for (int i=0; i<2; i++) fRec52[i] = 0;
	for (int i=0; i<2; i++) fRec51[i] = 0;
	for (int i=0; i<2; i++) fRec50[i] = 0;
	for (int i=0; i<2; i++) fRec55[i] = 0;
	for (int i=0; i<2; i++) fRec46[i] = 0;
	for (int i=0; i<2; i++) iRec47[i] = 0;
	for (int i=0; i<2; i++) fRec48[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (1.0 / double(iConst0));
	fConst2 = (2.0 / double(iConst0));
	fConst3 = (3.141592653589793 / double(iConst0));
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, float *input0, float *output0)
{
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
		fRec10[0] = ((fSlow21 * fTemp1) + (fSlow20 * fRec10[1]));
		fRec9[0] = (fRec10[0] - (fSlow18 * ((fSlow16 * fRec9[2]) + (fSlow14 * fRec9[1]))));
		double fTemp2 = (fRec9[2] + (fRec9[0] + (2 * fRec9[1])));
		fVec1[0] = (fSlow18 * fTemp2);
		fRec8[0] = ((fSlow24 * ((fSlow23 * fVec1[1]) + (fSlow22 * fTemp2))) + (fSlow11 * fRec8[1]));
		fRec7[0] = (fRec8[0] - (fSlow9 * ((fSlow7 * fRec7[2]) + (fSlow5 * fRec7[1]))));
		double fTemp3 = (fSlow9 * (((fSlow4 * fRec7[0]) + (fSlow25 * fRec7[1])) + (fSlow4 * fRec7[2])));
		double fTemp4 = ((iSlow28)?0:fTemp3);
		double fTemp5 = fabs(fTemp4);
		fRec6[0] = ((fSlow30 * fTemp5) + (fSlow29 * max(fTemp5, fRec6[1])));
		fRec5[0] = ((fSlow31 * fRec6[0]) + (fSlow2 * fRec5[1]));
		fRec4[0] = ((fSlow33 * max((fSlow32 + (20 * log10(fRec5[0]))), 0.0)) + (fSlow1 * fRec4[1]));
		fRec11[0] = (fSlow34 + (0.999 * fRec11[1]));
		double fTemp6 = (fSlow35 * (fRec11[0] * ((iSlow28)?fTemp3:(fTemp4 * pow(10,(0.05 * fRec4[0]))))));
		double 	fRec3 = max(fConst1, fabs(fTemp6));
		int iTemp7 = int((iRec1[1] < 4096));
		fRec0[0] = ((iTemp7)?max(fRec0[1], fRec3):fRec3);
		iRec1[0] = ((iTemp7)?(1 + iRec1[1]):1);
		fRec2[0] = ((iTemp7)?fRec2[1]:fRec0[1]);
		fbargraph0 = fRec2[0];
		fRec20[0] = ((fSlow21 * ((fSlow39 * fVec0[1]) + (fSlow15 * fVec0[0]))) + (fSlow20 * fRec20[1]));
		fRec19[0] = (fRec20[0] - (fSlow18 * ((fSlow16 * fRec19[2]) + (fSlow14 * fRec19[1]))));
		double fTemp8 = (fSlow18 * (((fSlow13 * fRec19[0]) + (fSlow40 * fRec19[1])) + (fSlow13 * fRec19[2])));
		double fTemp9 = ((iSlow43)?0:fTemp8);
		double fTemp10 = fabs(fTemp9);
		fRec18[0] = ((fSlow45 * fTemp10) + (fSlow44 * max(fTemp10, fRec18[1])));
		fRec17[0] = ((fSlow46 * fRec18[0]) + (fSlow38 * fRec17[1]));
		fRec16[0] = ((fSlow48 * max((fSlow47 + (20 * log10(fRec17[0]))), 0.0)) + (fSlow37 * fRec16[1]));
		fRec21[0] = (fSlow49 + (0.999 * fRec21[1]));
		double fTemp11 = (fSlow50 * (fRec21[0] * ((iSlow43)?fTemp8:(fTemp9 * pow(10,(0.05 * fRec16[0]))))));
		double 	fRec15 = max(fConst1, fabs(fTemp11));
		int iTemp12 = int((iRec13[1] < 4096));
		fRec12[0] = ((iTemp12)?max(fRec12[1], fRec15):fRec15);
		iRec13[0] = ((iTemp12)?(1 + iRec13[1]):1);
		fRec14[0] = ((iTemp12)?fRec14[1]:fRec12[1]);
		fbargraph1 = fRec14[0];
		fRec32[0] = ((fSlow24 * fTemp1) + (fSlow11 * fRec32[1]));
		fRec31[0] = (fRec32[0] - (fSlow9 * ((fSlow7 * fRec31[2]) + (fSlow5 * fRec31[1]))));
		double fTemp13 = (fRec31[2] + (fRec31[0] + (2 * fRec31[1])));
		fVec2[0] = (fSlow9 * fTemp13);
		fRec30[0] = ((fSlow65 * ((fSlow64 * fVec2[1]) + (fSlow63 * fTemp13))) + (fSlow62 * fRec30[1]));
		fRec29[0] = (fRec30[0] - (fSlow60 * ((fSlow58 * fRec29[2]) + (fSlow56 * fRec29[1]))));
		double fTemp14 = (fSlow60 * (((fSlow55 * fRec29[0]) + (fSlow66 * fRec29[1])) + (fSlow55 * fRec29[2])));
		double fTemp15 = ((iSlow69)?0:fTemp14);
		double fTemp16 = fabs(fTemp15);
		fRec28[0] = ((fSlow71 * fTemp16) + (fSlow70 * max(fTemp16, fRec28[1])));
		fRec27[0] = ((fSlow72 * fRec28[0]) + (fSlow53 * fRec27[1]));
		fRec26[0] = ((fSlow74 * max((fSlow73 + (20 * log10(fRec27[0]))), 0.0)) + (fSlow52 * fRec26[1]));
		fRec33[0] = (fSlow75 + (0.999 * fRec33[1]));
		double fTemp17 = (fSlow76 * (fRec33[0] * ((iSlow69)?fTemp14:(fTemp15 * pow(10,(0.05 * fRec26[0]))))));
		double 	fRec25 = max(fConst1, fabs(fTemp17));
		int iTemp18 = int((iRec23[1] < 4096));
		fRec22[0] = ((iTemp18)?max(fRec22[1], fRec25):fRec25);
		iRec23[0] = ((iTemp18)?(1 + iRec23[1]):1);
		fRec24[0] = ((iTemp18)?fRec24[1]:fRec22[1]);
		fbargraph2 = fRec24[0];
		fRec44[0] = ((fSlow65 * fTemp1) + (fSlow62 * fRec44[1]));
		fRec43[0] = (fRec44[0] - (fSlow60 * ((fSlow58 * fRec43[2]) + (fSlow56 * fRec43[1]))));
		double fTemp19 = (fRec43[2] + (fRec43[0] + (2 * fRec43[1])));
		fVec3[0] = (fSlow60 * fTemp19);
		fRec42[0] = ((fSlow90 * ((fSlow89 * fVec3[1]) + (fSlow88 * fTemp19))) + (fSlow87 * fRec42[1]));
		fRec41[0] = (fRec42[0] - (fSlow85 * ((fSlow84 * fRec41[2]) + (fSlow82 * fRec41[1]))));
		double fTemp20 = (fSlow85 * (((fSlow81 * fRec41[0]) + (fSlow91 * fRec41[1])) + (fSlow81 * fRec41[2])));
		double fTemp21 = ((iSlow94)?0:fTemp20);
		double fTemp22 = fabs(fTemp21);
		fRec40[0] = ((fSlow96 * fTemp22) + (fSlow95 * max(fTemp22, fRec40[1])));
		fRec39[0] = ((fSlow97 * fRec40[0]) + (fSlow79 * fRec39[1]));
		fRec38[0] = ((fSlow99 * max((fSlow98 + (20 * log10(fRec39[0]))), 0.0)) + (fSlow78 * fRec38[1]));
		fRec45[0] = (fSlow100 + (0.999 * fRec45[1]));
		double fTemp23 = (fSlow101 * (fRec45[0] * ((iSlow94)?fTemp20:(fTemp21 * pow(10,(0.05 * fRec38[0]))))));
		double 	fRec37 = max(fConst1, fabs(fTemp23));
		int iTemp24 = int((iRec35[1] < 4096));
		fRec34[0] = ((iTemp24)?max(fRec34[1], fRec37):fRec37);
		iRec35[0] = ((iTemp24)?(1 + iRec35[1]):1);
		fRec36[0] = ((iTemp24)?fRec36[1]:fRec34[1]);
		fbargraph3 = fRec36[0];
		fRec54[0] = ((fSlow90 * fTemp1) + (fSlow87 * fRec54[1]));
		fRec53[0] = (fRec54[0] - (fSlow85 * ((fSlow84 * fRec53[2]) + (fSlow82 * fRec53[1]))));
		double fTemp25 = (fSlow85 * (fRec53[2] + (fRec53[0] + (2 * fRec53[1]))));
		double fTemp26 = ((iSlow107)?0:fTemp25);
		double fTemp27 = fabs(fTemp26);
		fRec52[0] = ((fSlow109 * fTemp27) + (fSlow108 * max(fTemp27, fRec52[1])));
		fRec51[0] = ((fSlow110 * fRec52[0]) + (fSlow104 * fRec51[1]));
		fRec50[0] = ((fSlow112 * max((fSlow111 + (20 * log10(fRec51[0]))), 0.0)) + (fSlow103 * fRec50[1]));
		fRec55[0] = (fSlow113 + (0.999 * fRec55[1]));
		double fTemp28 = (fSlow114 * (fRec55[0] * ((iSlow107)?fTemp25:(fTemp26 * pow(10,(0.05 * fRec50[0]))))));
		double 	fRec49 = max(fConst1, fabs(fTemp28));
		int iTemp29 = int((iRec47[1] < 4096));
		fRec46[0] = ((iTemp29)?max(fRec46[1], fRec49):fRec49);
		iRec47[0] = ((iTemp29)?(1 + iRec47[1]):1);
		fRec48[0] = ((iTemp29)?fRec48[1]:fRec46[1]);
		fbargraph4 = fRec48[0];
		output0[i] = (FAUSTFLOAT)(fTemp28 + (fTemp23 + (fTemp17 + (fTemp11 + fTemp6))));
		// post processing
		fRec48[1] = fRec48[0];
		iRec47[1] = iRec47[0];
		fRec46[1] = fRec46[0];
		fRec55[1] = fRec55[0];
		fRec50[1] = fRec50[0];
		fRec51[1] = fRec51[0];
		fRec52[1] = fRec52[0];
		fRec53[2] = fRec53[1]; fRec53[1] = fRec53[0];
		fRec54[1] = fRec54[0];
		fRec36[1] = fRec36[0];
		iRec35[1] = iRec35[0];
		fRec34[1] = fRec34[0];
		fRec45[1] = fRec45[0];
		fRec38[1] = fRec38[0];
		fRec39[1] = fRec39[0];
		fRec40[1] = fRec40[0];
		fRec41[2] = fRec41[1]; fRec41[1] = fRec41[0];
		fRec42[1] = fRec42[0];
		fVec3[1] = fVec3[0];
		fRec43[2] = fRec43[1]; fRec43[1] = fRec43[0];
		fRec44[1] = fRec44[0];
		fRec24[1] = fRec24[0];
		iRec23[1] = iRec23[0];
		fRec22[1] = fRec22[0];
		fRec33[1] = fRec33[0];
		fRec26[1] = fRec26[0];
		fRec27[1] = fRec27[0];
		fRec28[1] = fRec28[0];
		fRec29[2] = fRec29[1]; fRec29[1] = fRec29[0];
		fRec30[1] = fRec30[0];
		fVec2[1] = fVec2[0];
		fRec31[2] = fRec31[1]; fRec31[1] = fRec31[0];
		fRec32[1] = fRec32[0];
		fRec14[1] = fRec14[0];
		iRec13[1] = iRec13[0];
		fRec12[1] = fRec12[0];
		fRec21[1] = fRec21[0];
		fRec16[1] = fRec16[0];
		fRec17[1] = fRec17[0];
		fRec18[1] = fRec18[0];
		fRec19[2] = fRec19[1]; fRec19[1] = fRec19[0];
		fRec20[1] = fRec20[0];
		fRec2[1] = fRec2[0];
		iRec1[1] = iRec1[0];
		fRec0[1] = fRec0[0];
		fRec11[1] = fRec11[0];
		fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
		fVec1[1] = fVec1[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec10[1] = fRec10[0];
		fVec0[1] = fVec0[0];
	}
}

void __rt_func Dsp::compute_static(int count, float *input0, float *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	static const value_pair fslider29_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	reg.registerEnumVar("mbc.Mode1","","S",N_("Compress or Mute the selected band, or Bypass The Compressor"),fslider29_values,&fslider29, 1.0, 1.0, 3.0, 1.0);
	static const value_pair fslider23_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	reg.registerEnumVar("mbc.Mode2","","S",N_("Compress or Mute the selected band, or Bypass The Compressor"),fslider23_values,&fslider23, 1.0, 1.0, 3.0, 1.0);
	static const value_pair fslider16_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	reg.registerEnumVar("mbc.Mode3","","S",N_("Compress or Mute the selected band, or Bypass The Compressor"),fslider16_values,&fslider16, 1.0, 1.0, 3.0, 1.0);
	static const value_pair fslider3_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	reg.registerEnumVar("mbc.Mode4","","S",N_("Compress or Mute the selected band, or Bypass The Compressor"),fslider3_values,&fslider3, 1.0, 1.0, 3.0, 1.0);
	static const value_pair fslider9_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	reg.registerEnumVar("mbc.Mode5","","S",N_("Compress or Mute the selected band, or Bypass The Compressor"),fslider9_values,&fslider9, 1.0, 1.0, 3.0, 1.0);
	reg.registerVar("mbc.Makeup1","","S",N_("Post amplification and threshold"),&fslider31, 13.0, -5e+01, 5e+01, 0.1);
	reg.registerVar("mbc.Makeup2","","S",N_("Post amplification and threshold"),&fslider25, 1e+01, -5e+01, 5e+01, 0.1);
	reg.registerVar("mbc.Makeup3","","S",N_("Post amplification and threshold"),&fslider18, 4.0, -5e+01, 5e+01, 0.1);
	reg.registerVar("mbc.Makeup4","","S",N_("Post amplification and threshold"),&fslider5, 8.0, -5e+01, 5e+01, 0.1);
	reg.registerVar("mbc.Makeup5","","S",N_("Post amplification and threshold"),&fslider11, 11.0, -5e+01, 5e+01, 0.1);
	reg.registerVar("mbc.Makeup-Threshold1","","S",N_("Threshold correction, an anticlip measure"),&fslider33, 2.0, 0.0, 1e+01, 0.1);
	reg.registerVar("mbc.Makeup-Threshold2","","S",N_("Threshold correction, an anticlip measure"),&fslider27, 2.0, 0.0, 1e+01, 0.1);
	reg.registerVar("mbc.Makeup-Threshold3","","S",N_("Threshold correction, an anticlip measure"),&fslider20, 2.0, 0.0, 1e+01, 0.1);
	reg.registerVar("mbc.Makeup-Threshold4","","S",N_("Threshold correction, an anticlip measure"),&fslider7, 2.0, 0.0, 1e+01, 0.1);
	reg.registerVar("mbc.Makeup-Threshold5","","S",N_("Threshold correction, an anticlip measure"),&fslider13, 2.0, 0.0, 1e+01, 0.1);
	reg.registerVar("mbc.Ratio1","","S",N_("Compression ratio"),&fslider32, 2.0, 1.0, 1e+02, 0.1);
	reg.registerVar("mbc.Ratio2","","S",N_("Compression ratio"),&fslider26, 2.0, 1.0, 1e+02, 0.1);
	reg.registerVar("mbc.Ratio3","","S",N_("Compression ratio"),&fslider19, 2.0, 1.0, 1e+02, 0.1);
	reg.registerVar("mbc.Ratio4","","S",N_("Compression ratio"),&fslider6, 2.0, 1.0, 1e+02, 0.1);
	reg.registerVar("mbc.Ratio5","","S",N_("Compression ratio"),&fslider12, 2.0, 1.0, 1e+02, 0.1);
	reg.registerVar("mbc.Attack1","","S",N_("Time before the compressor starts to kick in"),&fslider28, 0.012, 0.001, 1.0, 0.001);
	reg.registerVar("mbc.Attack2","","S",N_("Time before the compressor starts to kick in"),&fslider21, 0.012, 0.001, 1.0, 0.001);
	reg.registerVar("mbc.Attack3","","S",N_("Time before the compressor starts to kick in"),&fslider14, 0.012, 0.001, 1.0, 0.001);
	reg.registerVar("mbc.Attack4","","S",N_("Time before the compressor starts to kick in"),&fslider0, 0.012, 0.001, 1.0, 0.001);
	reg.registerVar("mbc.Attack5","","S",N_("Time before the compressor starts to kick in"),&fslider8, 0.012, 0.001, 1.0, 0.001);
	reg.registerVar("mbc.Release1","","S",N_("Time before the compressor releases the sound"),&fslider30, 1.25, 0.01, 1e+01, 0.01);
	reg.registerVar("mbc.Release2","","S",N_("Time before the compressor releases the sound"),&fslider24, 1.25, 0.01, 1e+01, 0.01);
	reg.registerVar("mbc.Release3","","S",N_("Time before the compressor releases the sound"),&fslider17, 1.25, 0.01, 1e+01, 0.01);
	reg.registerVar("mbc.Release4","","S",N_("Time before the compressor releases the sound"),&fslider4, 1.25, 0.01, 1e+01, 0.01);
	reg.registerVar("mbc.Release5","","S",N_("Time before the compressor releases the sound"),&fslider10, 1.25, 0.01, 1e+01, 0.01);
	reg.registerVar("mbc.crossover_b1_b2",N_("Crossover B1-B2 (hz)"),"SL",N_("Crossover bandpass frequency"),&fslider22, 8e+01, 2e+01, 2e+04, 1.08);
	reg.registerVar("mbc.crossover_b2_b3",N_("Crossover B2-B3 (hz)"),"SL",N_("Crossover bandpass frequency"),&fslider15, 2.1e+02, 2e+01, 2e+04, 1.08);
	reg.registerVar("mbc.crossover_b3_b4",N_("Crossover B3-B4 (hz)"),"SL",N_("Crossover bandpass frequency"),&fslider1, 1.7e+03, 2e+01, 2e+04, 1.08);
	reg.registerVar("mbc.crossover_b4_b5",N_("Crossover B4-B5 (hz)"),"SL",N_("Crossover bandpass frequency"),&fslider2, 5e+03, 2e+01, 2e+04, 1.08);
	reg.registerNonMidiFloatVar("mbc.v1",&fbargraph4, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbc.v2",&fbargraph3, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbc.v3",&fbargraph2, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbc.v4",&fbargraph0, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbc.v5",&fbargraph1, false, true, -70.0, -70.0, 4.0, 0.00001);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("mbc" "." p)

b.openHorizontalhideBox("");
b.closeBox();

b.openHorizontalBox("");
b.openVerticalBox("");

b.openTabBox("");

b.openHorizontalBox(N_("Band 1"));
b.openpaintampBox(" ");
b.openVerticalBox("");
b.openHorizontalBox("");
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Makeup1"), N_("Makeup (db)"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Makeup-Threshold1"), N_("Anticlip (db)"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b1_b2"), N_("Low Shelf (Hz)"));
b.closeBox();
b.openHorizontalBox("");
b.create_selector_no_caption(PARAM("Mode1"));
b.create_small_rackknob(PARAM("Ratio1"), N_("Ratio"));
b.create_small_rackknob(PARAM("Attack1"), N_("Attack"));
b.create_small_rackknob(PARAM("Release1"), N_("Release"));
b.closeBox();
b.closeBox();
b.closeBox();
b.closeBox();

b.openHorizontalBox(N_("Band 2"));
b.openpaintampBox(" ");
b.openVerticalBox("");
b.openHorizontalBox("");
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Makeup2"),  N_("Makeup (db)"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Makeup-Threshold2"), N_("Anticlip (db)"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b1_b2"), N_("Low (hz)"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b2_b3"), N_("High (hz)"));
b.closeBox();
b.openHorizontalBox("");
b.create_selector_no_caption(PARAM("Mode2"));
b.create_small_rackknob(PARAM("Ratio2"), N_("Ratio"));
b.create_small_rackknob(PARAM("Attack2"), N_("Attack"));
b.create_small_rackknob(PARAM("Release2"), N_("Release"));
b.closeBox();
b.closeBox();
b.closeBox();
b.closeBox();

b.openHorizontalBox(N_("Band 3"));
b.openpaintampBox(" ");
b.openVerticalBox("");
b.openHorizontalBox("");
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Makeup3"), N_("Makeup (db)"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Makeup-Threshold3"), N_("Anticlip (db)"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b2_b3"), N_("Low (hz)"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b3_b4"), N_("High (hz)"));
b.closeBox();
b.openHorizontalBox("");
b.create_selector_no_caption(PARAM("Mode3"));
b.create_small_rackknob(PARAM("Ratio3"), N_("Ratio"));
b.create_small_rackknob(PARAM("Attack3"), N_("Attack"));
b.create_small_rackknob(PARAM("Release3"), N_("Release"));
b.closeBox();
b.closeBox();
b.closeBox();
b.closeBox();

b.openHorizontalBox(N_("Band 4"));
b.openpaintampBox(" ");
b.openVerticalBox("");
b.openHorizontalBox("");
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Makeup4"), N_("Makeup (db)"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Makeup-Threshold4"), N_("Anticlip (db)"));
b.set_next_flags(UI_NUM_RIGHT);
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b3_b4"), N_("Low (hz)"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b4_b5"), N_("High (hz)"));
b.closeBox();
b.openHorizontalBox("");
b.create_selector_no_caption(PARAM("Mode4"));
b.create_small_rackknob(PARAM("Ratio4"), N_("Ratio"));
b.create_small_rackknob(PARAM("Attack4"), N_("Attack"));
b.create_small_rackknob(PARAM("Release4"), N_("Release"));
b.closeBox();
b.closeBox();
b.closeBox();
b.closeBox();

b.openHorizontalBox(N_("Band 5"));
b.openpaintampBox(" ");
b.openVerticalBox("");
b.openHorizontalBox("");
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Makeup5"), N_("Makeup (db)"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Makeup-Threshold5"), N_("Anticlip (db)"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b4_b5"), N_("High Shelf (hz)"));
b.closeBox();
b.openHorizontalBox("");
b.create_selector_no_caption(PARAM("Mode5"));
b.create_small_rackknob(PARAM("Ratio5"), N_("Ratio"));
b.create_small_rackknob(PARAM("Attack5"), N_("Attack"));
b.create_small_rackknob(PARAM("Release5"), N_("Release"));
b.closeBox();
b.closeBox();
b.closeBox();
b.closeBox();

b.closeBox();
b.closeBox();
b.openVerticalBox2("Analyze");
b.create_simple_meter(PARAM("v1"));
b.create_simple_meter(PARAM("v2"));
b.create_simple_meter(PARAM("v3"));
b.create_simple_meter(PARAM("v4"));
b.create_simple_meter(PARAM("v5"));
b.closeBox();
b.closeBox();

#undef PARAM
        return 0;
    }
	return -1;
}

int Dsp::load_ui_f_static(const UiBuilder& b, int form)
{
	return static_cast<Dsp*>(b.plugin)->load_ui_f(b, form);
}
PluginDef *plugin() {
	return new Dsp();
}

void Dsp::del_instance(PluginDef *p)
{
	delete static_cast<Dsp*>(p);
}

} // end namespace mbc
} // end namespace pluginlib
