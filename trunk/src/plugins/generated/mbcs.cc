// generated from file '../src/plugins/mbcs.dsp' by dsp2cc:
// Code generated with Faust 0.9.58 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

namespace pluginlib {
namespace mbcs {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	FAUSTFLOAT 	fslider1;
	double 	fConst3;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT 	fslider4;
	double 	fVec0[2];
	double 	fRec10[2];
	double 	fRec9[3];
	double 	fVec1[2];
	double 	fRec8[2];
	double 	fRec7[3];
	double 	fVec2[2];
	double 	fRec6[2];
	double 	fRec5[3];
	double 	fVec3[2];
	double 	fRec4[2];
	double 	fRec3[3];
	FAUSTFLOAT 	fslider5;
	double 	fVec4[2];
	double 	fRec18[2];
	double 	fRec17[3];
	double 	fVec5[2];
	double 	fRec16[2];
	double 	fRec15[3];
	double 	fVec6[2];
	double 	fRec14[2];
	double 	fRec13[3];
	double 	fVec7[2];
	double 	fRec12[2];
	double 	fRec11[3];
	FAUSTFLOAT 	fslider6;
	double 	fRec2[2];
	double 	fRec1[2];
	FAUSTFLOAT 	fslider7;
	FAUSTFLOAT 	fslider8;
	double 	fRec0[2];
	FAUSTFLOAT 	fslider9;
	double 	fRec19[2];
	FAUSTFLOAT 	fslider10;
	double 	fRec24[2];
	double 	fRec23[3];
	FAUSTFLOAT 	fslider11;
	double 	fRec26[2];
	double 	fRec25[3];
	FAUSTFLOAT 	fslider12;
	double 	fRec22[2];
	double 	fRec21[2];
	FAUSTFLOAT 	fslider13;
	FAUSTFLOAT 	fslider14;
	double 	fRec20[2];
	FAUSTFLOAT 	fslider15;
	double 	fRec27[2];
	FAUSTFLOAT 	fslider16;
	double 	fRec33[2];
	double 	fRec32[3];
	double 	fRec31[3];
	FAUSTFLOAT 	fslider17;
	double 	fRec36[2];
	double 	fRec35[3];
	double 	fRec34[3];
	FAUSTFLOAT 	fslider18;
	double 	fRec30[2];
	double 	fRec29[2];
	FAUSTFLOAT 	fslider19;
	FAUSTFLOAT 	fslider20;
	double 	fRec28[2];
	FAUSTFLOAT 	fslider21;
	double 	fRec37[2];
	FAUSTFLOAT 	fslider22;
	double 	fRec44[2];
	double 	fRec43[3];
	double 	fRec42[3];
	double 	fRec41[3];
	FAUSTFLOAT 	fslider23;
	double 	fRec48[2];
	double 	fRec47[3];
	double 	fRec46[3];
	double 	fRec45[3];
	FAUSTFLOAT 	fslider24;
	double 	fRec40[2];
	double 	fRec39[2];
	FAUSTFLOAT 	fslider25;
	FAUSTFLOAT 	fslider26;
	double 	fRec38[2];
	FAUSTFLOAT 	fslider27;
	double 	fRec49[2];
	FAUSTFLOAT 	fslider28;
	double 	fRec57[2];
	double 	fRec56[3];
	double 	fRec55[3];
	double 	fRec54[3];
	double 	fRec53[3];
	FAUSTFLOAT 	fslider29;
	double 	fRec62[2];
	double 	fRec61[3];
	double 	fRec60[3];
	double 	fRec59[3];
	double 	fRec58[3];
	FAUSTFLOAT 	fslider30;
	double 	fRec52[2];
	double 	fRec51[2];
	FAUSTFLOAT 	fslider31;
	FAUSTFLOAT 	fslider32;
	double 	fRec50[2];
	FAUSTFLOAT 	fslider33;
	double 	fRec63[2];
	void clear_state_f();
	int load_ui_f(const UiBuilder& b, int form);
	void init(unsigned int samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static int load_ui_f_static(const UiBuilder& b, int form);
	static void init_static(unsigned int samplingFreq, PluginDef*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginDef*);
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
	id = "mbcs";
	name = N_("Multi Band Compressor stereo");
	groups = 0;
	description = N_("Multi Band Compressor contributed by kokoko3k"); // description (tooltip)
	category = N_("Guitar Effects");       // category
	shortname = N_("MB Compressor St");     // shortname
	mono_audio = 0;
	stereo_audio = compute_static;
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
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<3; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<3; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<3; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<3; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fVec7[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<3; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<3; i++) fRec23[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<3; i++) fRec25[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec27[i] = 0;
	for (int i=0; i<2; i++) fRec33[i] = 0;
	for (int i=0; i<3; i++) fRec32[i] = 0;
	for (int i=0; i<3; i++) fRec31[i] = 0;
	for (int i=0; i<2; i++) fRec36[i] = 0;
	for (int i=0; i<3; i++) fRec35[i] = 0;
	for (int i=0; i<3; i++) fRec34[i] = 0;
	for (int i=0; i<2; i++) fRec30[i] = 0;
	for (int i=0; i<2; i++) fRec29[i] = 0;
	for (int i=0; i<2; i++) fRec28[i] = 0;
	for (int i=0; i<2; i++) fRec37[i] = 0;
	for (int i=0; i<2; i++) fRec44[i] = 0;
	for (int i=0; i<3; i++) fRec43[i] = 0;
	for (int i=0; i<3; i++) fRec42[i] = 0;
	for (int i=0; i<3; i++) fRec41[i] = 0;
	for (int i=0; i<2; i++) fRec48[i] = 0;
	for (int i=0; i<3; i++) fRec47[i] = 0;
	for (int i=0; i<3; i++) fRec46[i] = 0;
	for (int i=0; i<3; i++) fRec45[i] = 0;
	for (int i=0; i<2; i++) fRec40[i] = 0;
	for (int i=0; i<2; i++) fRec39[i] = 0;
	for (int i=0; i<2; i++) fRec38[i] = 0;
	for (int i=0; i<2; i++) fRec49[i] = 0;
	for (int i=0; i<2; i++) fRec57[i] = 0;
	for (int i=0; i<3; i++) fRec56[i] = 0;
	for (int i=0; i<3; i++) fRec55[i] = 0;
	for (int i=0; i<3; i++) fRec54[i] = 0;
	for (int i=0; i<3; i++) fRec53[i] = 0;
	for (int i=0; i<2; i++) fRec62[i] = 0;
	for (int i=0; i<3; i++) fRec61[i] = 0;
	for (int i=0; i<3; i++) fRec60[i] = 0;
	for (int i=0; i<3; i++) fRec59[i] = 0;
	for (int i=0; i<3; i++) fRec58[i] = 0;
	for (int i=0; i<2; i++) fRec52[i] = 0;
	for (int i=0; i<2; i++) fRec51[i] = 0;
	for (int i=0; i<2; i++) fRec50[i] = 0;
	for (int i=0; i<2; i++) fRec63[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (2.0 / double(iConst0));
	fConst2 = (1.0 / double(iConst0));
	fConst3 = (3.141592653589793 / double(iConst0));
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
	double 	fSlow0 = fslider0;
	double 	fSlow1 = exp((0 - (fConst1 / fSlow0)));
	double 	fSlow2 = exp((0 - (fConst2 / fSlow0)));
	double 	fSlow3 = tan((fConst3 * fslider1));
	double 	fSlow4 = (1.0 / faustpower<2>(fSlow3));
	double 	fSlow5 = (2 * (1 - fSlow4));
	double 	fSlow6 = (1.0 / fSlow3);
	double 	fSlow7 = (1 + ((fSlow6 - 1.0000000000000004) / fSlow3));
	double 	fSlow8 = (1.0 / (1 + ((fSlow6 + 1.0000000000000004) / fSlow3)));
	double 	fSlow9 = (1 + fSlow6);
	double 	fSlow10 = (0 - ((1 - fSlow6) / fSlow9));
	double 	fSlow11 = tan((fConst3 * fslider2));
	double 	fSlow12 = (1.0 / faustpower<2>(fSlow11));
	double 	fSlow13 = (2 * (1 - fSlow12));
	double 	fSlow14 = (1.0 / fSlow11);
	double 	fSlow15 = (1 + ((fSlow14 - 1.0000000000000004) / fSlow11));
	double 	fSlow16 = (1 + ((fSlow14 + 1.0000000000000004) / fSlow11));
	double 	fSlow17 = (1.0 / fSlow16);
	double 	fSlow18 = (1 + fSlow14);
	double 	fSlow19 = (0 - ((1 - fSlow14) / fSlow18));
	double 	fSlow20 = tan((fConst3 * fslider3));
	double 	fSlow21 = (1.0 / faustpower<2>(fSlow20));
	double 	fSlow22 = (2 * (1 - fSlow21));
	double 	fSlow23 = (1.0 / fSlow20);
	double 	fSlow24 = (1 + ((fSlow23 - 1.0000000000000004) / fSlow20));
	double 	fSlow25 = (1 + ((fSlow23 + 1.0000000000000004) / fSlow20));
	double 	fSlow26 = (1.0 / fSlow25);
	double 	fSlow27 = (1 + fSlow23);
	double 	fSlow28 = (0 - ((1 - fSlow23) / fSlow27));
	double 	fSlow29 = tan((fConst3 * fslider4));
	double 	fSlow30 = (1.0 / faustpower<2>(fSlow29));
	double 	fSlow31 = (2 * (1 - fSlow30));
	double 	fSlow32 = (1.0 / fSlow29);
	double 	fSlow33 = (1 + ((fSlow32 - 1.0000000000000004) / fSlow29));
	double 	fSlow34 = (1 + ((1.0000000000000004 + fSlow32) / fSlow29));
	double 	fSlow35 = (1.0 / fSlow34);
	double 	fSlow36 = (1 + fSlow32);
	double 	fSlow37 = (0 - ((1 - fSlow32) / fSlow36));
	double 	fSlow38 = (1.0 / fSlow36);
	double 	fSlow39 = (1.0 / fSlow27);
	double 	fSlow40 = (1.0 / fSlow18);
	double 	fSlow41 = (1.0 / (fSlow3 * fSlow16));
	double 	fSlow42 = (0 - fSlow6);
	double 	fSlow43 = (1.0 / fSlow9);
	double 	fSlow44 = (2 * (0 - fSlow4));
	double 	fSlow45 = fslider5;
	double 	fSlow46 = max((double)0, (fSlow45 - 1));
	int 	iSlow47 = int(fSlow46);
	double 	fSlow48 = exp((0 - (fConst2 / fslider6)));
	double 	fSlow49 = (1.0 - fSlow48);
	double 	fSlow50 = (1.0 - fSlow2);
	double 	fSlow51 = fslider7;
	double 	fSlow52 = (((1.0 / double(fslider8)) - 1.0) * (1.0 - fSlow1));
	double 	fSlow53 = (0.0010000000000000009 * pow(10,(0.05 * ((fSlow51 - fslider9) * fabs((fSlow46 - 1))))));
	double 	fSlow54 = fabs((max((double)0, (fSlow45 - 2)) - 1));
	double 	fSlow55 = fslider10;
	double 	fSlow56 = exp((0 - (fConst1 / fSlow55)));
	double 	fSlow57 = exp((0 - (fConst2 / fSlow55)));
	double 	fSlow58 = fslider11;
	double 	fSlow59 = max((double)0, (fSlow58 - 1));
	int 	iSlow60 = int(fSlow59);
	double 	fSlow61 = exp((0 - (fConst2 / fslider12)));
	double 	fSlow62 = (1.0 - fSlow61);
	double 	fSlow63 = (1.0 - fSlow57);
	double 	fSlow64 = fslider13;
	double 	fSlow65 = (((1.0 / double(fslider14)) - 1.0) * (1.0 - fSlow56));
	double 	fSlow66 = (0.0010000000000000009 * pow(10,(0.05 * ((fSlow64 - fslider15) * fabs((fSlow59 - 1))))));
	double 	fSlow67 = fabs((max((double)0, (fSlow58 - 2)) - 1));
	double 	fSlow68 = fslider16;
	double 	fSlow69 = exp((0 - (fConst1 / fSlow68)));
	double 	fSlow70 = exp((0 - (fConst2 / fSlow68)));
	double 	fSlow71 = (1 + ((fSlow6 - 1.0) / fSlow3));
	double 	fSlow72 = (1.0 / (1 + ((1.0 + fSlow6) / fSlow3)));
	double 	fSlow73 = (1.0 / (fSlow11 * fSlow25));
	double 	fSlow74 = (0 - fSlow14);
	double 	fSlow75 = (2 * (0 - fSlow12));
	double 	fSlow76 = fslider17;
	double 	fSlow77 = max((double)0, (fSlow76 - 1));
	int 	iSlow78 = int(fSlow77);
	double 	fSlow79 = exp((0 - (fConst2 / fslider18)));
	double 	fSlow80 = (1.0 - fSlow79);
	double 	fSlow81 = (1.0 - fSlow70);
	double 	fSlow82 = fslider19;
	double 	fSlow83 = (((1.0 / double(fslider20)) - 1.0) * (1.0 - fSlow69));
	double 	fSlow84 = (0.0010000000000000009 * pow(10,(0.05 * ((fSlow82 - fslider21) * fabs((fSlow77 - 1))))));
	double 	fSlow85 = fabs((max((double)0, (fSlow76 - 2)) - 1));
	double 	fSlow86 = fslider22;
	double 	fSlow87 = exp((0 - (fConst1 / fSlow86)));
	double 	fSlow88 = exp((0 - (fConst2 / fSlow86)));
	double 	fSlow89 = (1 + ((fSlow14 - 1.0) / fSlow11));
	double 	fSlow90 = (1.0 / (1 + ((1.0 + fSlow14) / fSlow11)));
	double 	fSlow91 = (1.0 / (fSlow20 * fSlow34));
	double 	fSlow92 = (0 - fSlow23);
	double 	fSlow93 = (2 * (0 - fSlow21));
	double 	fSlow94 = fslider23;
	double 	fSlow95 = max((double)0, (fSlow94 - 1));
	int 	iSlow96 = int(fSlow95);
	double 	fSlow97 = exp((0 - (fConst2 / fslider24)));
	double 	fSlow98 = (1.0 - fSlow97);
	double 	fSlow99 = (1.0 - fSlow88);
	double 	fSlow100 = fslider25;
	double 	fSlow101 = (((1.0 / double(fslider26)) - 1.0) * (1.0 - fSlow87));
	double 	fSlow102 = (0.0010000000000000009 * pow(10,(0.05 * ((fSlow100 - fslider27) * fabs((fSlow95 - 1))))));
	double 	fSlow103 = fabs((max((double)0, (fSlow94 - 2)) - 1));
	double 	fSlow104 = fslider28;
	double 	fSlow105 = exp((0 - (fConst1 / fSlow104)));
	double 	fSlow106 = exp((0 - (fConst2 / fSlow104)));
	double 	fSlow107 = (1 + ((fSlow23 - 1.0) / fSlow20));
	double 	fSlow108 = (1.0 / (1 + ((1.0 + fSlow23) / fSlow20)));
	double 	fSlow109 = (0 - fSlow32);
	double 	fSlow110 = (2 * (0 - fSlow30));
	double 	fSlow111 = fslider29;
	double 	fSlow112 = max((double)0, (fSlow111 - 1));
	int 	iSlow113 = int(fSlow112);
	double 	fSlow114 = exp((0 - (fConst2 / fslider30)));
	double 	fSlow115 = (1.0 - fSlow114);
	double 	fSlow116 = (1.0 - fSlow106);
	double 	fSlow117 = fslider31;
	double 	fSlow118 = (((1.0 / double(fslider32)) - 1.0) * (1.0 - fSlow105));
	double 	fSlow119 = (0.0010000000000000009 * pow(10,(0.05 * ((fSlow117 - fslider33) * fabs((fSlow112 - 1))))));
	double 	fSlow120 = fabs((max((double)0, (fSlow111 - 2)) - 1));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fVec0[0] = fTemp0;
		fRec10[0] = ((fSlow38 * (fVec0[0] + fVec0[1])) + (fSlow37 * fRec10[1]));
		fRec9[0] = (fRec10[0] - (fSlow35 * ((fSlow33 * fRec9[2]) + (fSlow31 * fRec9[1]))));
		double fTemp1 = (fRec9[2] + (fRec9[0] + (2 * fRec9[1])));
		double fTemp2 = (fSlow35 * fTemp1);
		fVec1[0] = fTemp2;
		fRec8[0] = ((fSlow39 * (fVec1[0] + fVec1[1])) + (fSlow28 * fRec8[1]));
		fRec7[0] = (fRec8[0] - (fSlow26 * ((fSlow24 * fRec7[2]) + (fSlow22 * fRec7[1]))));
		double fTemp3 = (fRec7[2] + (fRec7[0] + (2 * fRec7[1])));
		double fTemp4 = (fSlow26 * fTemp3);
		fVec2[0] = fTemp4;
		fRec6[0] = ((fSlow40 * (fVec2[0] + fVec2[1])) + (fSlow19 * fRec6[1]));
		fRec5[0] = (fRec6[0] - (fSlow17 * ((fSlow15 * fRec5[2]) + (fSlow13 * fRec5[1]))));
		double fTemp5 = (fRec5[2] + (fRec5[0] + (2 * fRec5[1])));
		double fTemp6 = (fSlow17 * fTemp5);
		fVec3[0] = fTemp6;
		fRec4[0] = ((fSlow43 * ((fSlow42 * fVec3[1]) + (fSlow41 * fTemp5))) + (fSlow10 * fRec4[1]));
		fRec3[0] = (fRec4[0] - (fSlow8 * ((fSlow7 * fRec3[2]) + (fSlow5 * fRec3[1]))));
		double fTemp7 = (fSlow8 * (((fSlow4 * fRec3[0]) + (fSlow44 * fRec3[1])) + (fSlow4 * fRec3[2])));
		double fTemp8 = ((iSlow47)?0:fTemp7);
		double fTemp9 = (double)input1[i];
		fVec4[0] = fTemp9;
		fRec18[0] = ((fSlow38 * (fVec4[0] + fVec4[1])) + (fSlow37 * fRec18[1]));
		fRec17[0] = (fRec18[0] - (fSlow35 * ((fSlow33 * fRec17[2]) + (fSlow31 * fRec17[1]))));
		double fTemp10 = (fRec17[2] + (fRec17[0] + (2 * fRec17[1])));
		double fTemp11 = (fSlow35 * fTemp10);
		fVec5[0] = fTemp11;
		fRec16[0] = ((fSlow39 * (fVec5[0] + fVec5[1])) + (fSlow28 * fRec16[1]));
		fRec15[0] = (fRec16[0] - (fSlow26 * ((fSlow24 * fRec15[2]) + (fSlow22 * fRec15[1]))));
		double fTemp12 = (fRec15[2] + (fRec15[0] + (2 * fRec15[1])));
		double fTemp13 = (fSlow26 * fTemp12);
		fVec6[0] = fTemp13;
		fRec14[0] = ((fSlow40 * (fVec6[0] + fVec6[1])) + (fSlow19 * fRec14[1]));
		fRec13[0] = (fRec14[0] - (fSlow17 * ((fSlow15 * fRec13[2]) + (fSlow13 * fRec13[1]))));
		double fTemp14 = (fRec13[2] + (fRec13[0] + (2 * fRec13[1])));
		double fTemp15 = (fSlow17 * fTemp14);
		fVec7[0] = fTemp15;
		fRec12[0] = ((fSlow43 * ((fSlow42 * fVec7[1]) + (fSlow41 * fTemp14))) + (fSlow10 * fRec12[1]));
		fRec11[0] = (fRec12[0] - (fSlow8 * ((fSlow7 * fRec11[2]) + (fSlow5 * fRec11[1]))));
		double fTemp16 = (fSlow8 * (((fSlow4 * fRec11[0]) + (fSlow44 * fRec11[1])) + (fSlow4 * fRec11[2])));
		double fTemp17 = ((iSlow47)?0:fTemp16);
		double fTemp18 = fabs((fabs(fTemp17) + fabs(fTemp8)));
		fRec2[0] = ((fSlow49 * fTemp18) + (fSlow48 * max(fTemp18, fRec2[1])));
		fRec1[0] = ((fSlow50 * fRec2[0]) + (fSlow2 * fRec1[1]));
		fRec0[0] = ((fSlow52 * max((fSlow51 + (20 * log10(fRec1[0]))), 0.0)) + (fSlow1 * fRec0[1]));
		double fTemp19 = pow(10,(0.05 * fRec0[0]));
		fRec19[0] = (fSlow53 + (0.999 * fRec19[1]));
		fRec24[0] = ((fSlow43 * (fVec3[0] + fVec3[1])) + (fSlow10 * fRec24[1]));
		fRec23[0] = (fRec24[0] - (fSlow8 * ((fSlow7 * fRec23[2]) + (fSlow5 * fRec23[1]))));
		double fTemp20 = (fSlow8 * (fRec23[2] + (fRec23[0] + (2 * fRec23[1]))));
		double fTemp21 = ((iSlow60)?0:fTemp20);
		fRec26[0] = ((fSlow43 * (fVec7[0] + fVec7[1])) + (fSlow10 * fRec26[1]));
		fRec25[0] = (fRec26[0] - (fSlow8 * ((fSlow7 * fRec25[2]) + (fSlow5 * fRec25[1]))));
		double fTemp22 = (fSlow8 * (fRec25[2] + (fRec25[0] + (2 * fRec25[1]))));
		double fTemp23 = ((iSlow60)?0:fTemp22);
		double fTemp24 = fabs((fabs(fTemp23) + fabs(fTemp21)));
		fRec22[0] = ((fSlow62 * fTemp24) + (fSlow61 * max(fTemp24, fRec22[1])));
		fRec21[0] = ((fSlow63 * fRec22[0]) + (fSlow57 * fRec21[1]));
		fRec20[0] = ((fSlow65 * max((fSlow64 + (20 * log10(fRec21[0]))), 0.0)) + (fSlow56 * fRec20[1]));
		double fTemp25 = pow(10,(0.05 * fRec20[0]));
		fRec27[0] = (fSlow66 + (0.999 * fRec27[1]));
		double fTemp26 = (fSlow5 * fRec31[1]);
		fRec33[0] = ((fSlow40 * ((fSlow74 * fVec2[1]) + (fSlow73 * fTemp3))) + (fSlow19 * fRec33[1]));
		fRec32[0] = (fRec33[0] - (fSlow17 * ((fSlow15 * fRec32[2]) + (fSlow13 * fRec32[1]))));
		fRec31[0] = ((fSlow17 * (((fSlow12 * fRec32[0]) + (fSlow75 * fRec32[1])) + (fSlow12 * fRec32[2]))) - (fSlow72 * ((fSlow71 * fRec31[2]) + fTemp26)));
		double fTemp27 = (fRec31[2] + (fSlow72 * (fTemp26 + (fSlow71 * fRec31[0]))));
		double fTemp28 = ((iSlow78)?0:fTemp27);
		double fTemp29 = (fSlow5 * fRec34[1]);
		fRec36[0] = ((fSlow40 * ((fSlow74 * fVec6[1]) + (fSlow73 * fTemp12))) + (fSlow19 * fRec36[1]));
		fRec35[0] = (fRec36[0] - (fSlow17 * ((fSlow15 * fRec35[2]) + (fSlow13 * fRec35[1]))));
		fRec34[0] = ((fSlow17 * (((fSlow12 * fRec35[0]) + (fSlow75 * fRec35[1])) + (fSlow12 * fRec35[2]))) - (fSlow72 * ((fSlow71 * fRec34[2]) + fTemp29)));
		double fTemp30 = (fRec34[2] + (fSlow72 * (fTemp29 + (fSlow71 * fRec34[0]))));
		double fTemp31 = ((iSlow78)?0:fTemp30);
		double fTemp32 = fabs((fabs(fTemp31) + fabs(fTemp28)));
		fRec30[0] = ((fSlow80 * fTemp32) + (fSlow79 * max(fTemp32, fRec30[1])));
		fRec29[0] = ((fSlow81 * fRec30[0]) + (fSlow70 * fRec29[1]));
		fRec28[0] = ((fSlow83 * max((fSlow82 + (20 * log10(fRec29[0]))), 0.0)) + (fSlow69 * fRec28[1]));
		double fTemp33 = pow(10,(0.05 * fRec28[0]));
		fRec37[0] = (fSlow84 + (0.999 * fRec37[1]));
		double fTemp34 = (fSlow5 * fRec41[1]);
		double fTemp35 = (fSlow13 * fRec42[1]);
		fRec44[0] = ((fSlow39 * ((fSlow92 * fVec1[1]) + (fSlow91 * fTemp1))) + (fSlow28 * fRec44[1]));
		fRec43[0] = (fRec44[0] - (fSlow26 * ((fSlow24 * fRec43[2]) + (fSlow22 * fRec43[1]))));
		fRec42[0] = ((fSlow26 * (((fSlow21 * fRec43[0]) + (fSlow93 * fRec43[1])) + (fSlow21 * fRec43[2]))) - (fSlow90 * ((fSlow89 * fRec42[2]) + fTemp35)));
		fRec41[0] = ((fRec42[2] + (fSlow90 * (fTemp35 + (fSlow89 * fRec42[0])))) - (fSlow72 * ((fSlow71 * fRec41[2]) + fTemp34)));
		double fTemp36 = (fRec41[2] + (fSlow72 * (fTemp34 + (fSlow71 * fRec41[0]))));
		double fTemp37 = ((iSlow96)?0:fTemp36);
		double fTemp38 = (fSlow5 * fRec45[1]);
		double fTemp39 = (fSlow13 * fRec46[1]);
		fRec48[0] = ((fSlow39 * ((fSlow92 * fVec5[1]) + (fSlow91 * fTemp10))) + (fSlow28 * fRec48[1]));
		fRec47[0] = (fRec48[0] - (fSlow26 * ((fSlow24 * fRec47[2]) + (fSlow22 * fRec47[1]))));
		fRec46[0] = ((fSlow26 * (((fSlow21 * fRec47[0]) + (fSlow93 * fRec47[1])) + (fSlow21 * fRec47[2]))) - (fSlow90 * ((fSlow89 * fRec46[2]) + fTemp39)));
		fRec45[0] = ((fRec46[2] + (fSlow90 * (fTemp39 + (fSlow89 * fRec46[0])))) - (fSlow72 * ((fSlow71 * fRec45[2]) + fTemp38)));
		double fTemp40 = (fRec45[2] + (fSlow72 * (fTemp38 + (fSlow71 * fRec45[0]))));
		double fTemp41 = ((iSlow96)?0:fTemp40);
		double fTemp42 = fabs((fabs(fTemp41) + fabs(fTemp37)));
		fRec40[0] = ((fSlow98 * fTemp42) + (fSlow97 * max(fTemp42, fRec40[1])));
		fRec39[0] = ((fSlow99 * fRec40[0]) + (fSlow88 * fRec39[1]));
		fRec38[0] = ((fSlow101 * max((fSlow100 + (20 * log10(fRec39[0]))), 0.0)) + (fSlow87 * fRec38[1]));
		double fTemp43 = pow(10,(0.05 * fRec38[0]));
		fRec49[0] = (fSlow102 + (0.999 * fRec49[1]));
		double fTemp44 = (fSlow5 * fRec53[1]);
		double fTemp45 = (fSlow13 * fRec54[1]);
		double fTemp46 = (fSlow22 * fRec55[1]);
		fRec57[0] = ((fSlow38 * ((fSlow109 * fVec0[1]) + (fSlow32 * fVec0[0]))) + (fSlow37 * fRec57[1]));
		fRec56[0] = (fRec57[0] - (fSlow35 * ((fSlow33 * fRec56[2]) + (fSlow31 * fRec56[1]))));
		fRec55[0] = ((fSlow35 * (((fSlow30 * fRec56[0]) + (fSlow110 * fRec56[1])) + (fSlow30 * fRec56[2]))) - (fSlow108 * ((fSlow107 * fRec55[2]) + fTemp46)));
		fRec54[0] = ((fRec55[2] + (fSlow108 * (fTemp46 + (fSlow107 * fRec55[0])))) - (fSlow90 * ((fSlow89 * fRec54[2]) + fTemp45)));
		fRec53[0] = ((fRec54[2] + (fSlow90 * (fTemp45 + (fSlow89 * fRec54[0])))) - (fSlow72 * ((fSlow71 * fRec53[2]) + fTemp44)));
		double fTemp47 = (fRec53[2] + (fSlow72 * (fTemp44 + (fSlow71 * fRec53[0]))));
		double fTemp48 = ((iSlow113)?0:fTemp47);
		double fTemp49 = (fSlow5 * fRec58[1]);
		double fTemp50 = (fSlow13 * fRec59[1]);
		double fTemp51 = (fSlow22 * fRec60[1]);
		fRec62[0] = ((fSlow38 * ((fSlow109 * fVec4[1]) + (fSlow32 * fVec4[0]))) + (fSlow37 * fRec62[1]));
		fRec61[0] = (fRec62[0] - (fSlow35 * ((fSlow33 * fRec61[2]) + (fSlow31 * fRec61[1]))));
		fRec60[0] = ((fSlow35 * (((fSlow30 * fRec61[0]) + (fSlow110 * fRec61[1])) + (fSlow30 * fRec61[2]))) - (fSlow108 * ((fSlow107 * fRec60[2]) + fTemp51)));
		fRec59[0] = ((fRec60[2] + (fSlow108 * (fTemp51 + (fSlow107 * fRec60[0])))) - (fSlow90 * ((fSlow89 * fRec59[2]) + fTemp50)));
		fRec58[0] = ((fRec59[2] + (fSlow90 * (fTemp50 + (fSlow89 * fRec59[0])))) - (fSlow72 * ((fSlow71 * fRec58[2]) + fTemp49)));
		double fTemp52 = (fRec58[2] + (fSlow72 * (fTemp49 + (fSlow71 * fRec58[0]))));
		double fTemp53 = ((iSlow113)?0:fTemp52);
		double fTemp54 = fabs((fabs(fTemp53) + fabs(fTemp48)));
		fRec52[0] = ((fSlow115 * fTemp54) + (fSlow114 * max(fTemp54, fRec52[1])));
		fRec51[0] = ((fSlow116 * fRec52[0]) + (fSlow106 * fRec51[1]));
		fRec50[0] = ((fSlow118 * max((fSlow117 + (20 * log10(fRec51[0]))), 0.0)) + (fSlow105 * fRec50[1]));
		double fTemp55 = pow(10,(0.05 * fRec50[0]));
		fRec63[0] = (fSlow119 + (0.999 * fRec63[1]));
		output0[i] = (FAUSTFLOAT)((fSlow120 * (fRec63[0] * ((iSlow113)?fTemp47:(fTemp48 * fTemp55)))) + ((fSlow103 * (fRec49[0] * ((iSlow96)?fTemp36:(fTemp37 * fTemp43)))) + ((fSlow85 * (fRec37[0] * ((iSlow78)?fTemp27:(fTemp28 * fTemp33)))) + ((fSlow67 * (fRec27[0] * ((iSlow60)?fTemp20:(fTemp21 * fTemp25)))) + (fSlow54 * (fRec19[0] * ((iSlow47)?fTemp7:(fTemp8 * fTemp19))))))));
		output1[i] = (FAUSTFLOAT)((fSlow120 * (fRec63[0] * ((iSlow113)?fTemp52:(fTemp53 * fTemp55)))) + ((fSlow103 * (fRec49[0] * ((iSlow96)?fTemp40:(fTemp41 * fTemp43)))) + ((fSlow85 * (fRec37[0] * ((iSlow78)?fTemp30:(fTemp31 * fTemp33)))) + ((fSlow67 * (fRec27[0] * ((iSlow60)?fTemp22:(fTemp23 * fTemp25)))) + (fSlow54 * (fRec19[0] * ((iSlow47)?fTemp16:(fTemp17 * fTemp19))))))));
		// post processing
		fRec63[1] = fRec63[0];
		fRec50[1] = fRec50[0];
		fRec51[1] = fRec51[0];
		fRec52[1] = fRec52[0];
		fRec58[2] = fRec58[1]; fRec58[1] = fRec58[0];
		fRec59[2] = fRec59[1]; fRec59[1] = fRec59[0];
		fRec60[2] = fRec60[1]; fRec60[1] = fRec60[0];
		fRec61[2] = fRec61[1]; fRec61[1] = fRec61[0];
		fRec62[1] = fRec62[0];
		fRec53[2] = fRec53[1]; fRec53[1] = fRec53[0];
		fRec54[2] = fRec54[1]; fRec54[1] = fRec54[0];
		fRec55[2] = fRec55[1]; fRec55[1] = fRec55[0];
		fRec56[2] = fRec56[1]; fRec56[1] = fRec56[0];
		fRec57[1] = fRec57[0];
		fRec49[1] = fRec49[0];
		fRec38[1] = fRec38[0];
		fRec39[1] = fRec39[0];
		fRec40[1] = fRec40[0];
		fRec45[2] = fRec45[1]; fRec45[1] = fRec45[0];
		fRec46[2] = fRec46[1]; fRec46[1] = fRec46[0];
		fRec47[2] = fRec47[1]; fRec47[1] = fRec47[0];
		fRec48[1] = fRec48[0];
		fRec41[2] = fRec41[1]; fRec41[1] = fRec41[0];
		fRec42[2] = fRec42[1]; fRec42[1] = fRec42[0];
		fRec43[2] = fRec43[1]; fRec43[1] = fRec43[0];
		fRec44[1] = fRec44[0];
		fRec37[1] = fRec37[0];
		fRec28[1] = fRec28[0];
		fRec29[1] = fRec29[0];
		fRec30[1] = fRec30[0];
		fRec34[2] = fRec34[1]; fRec34[1] = fRec34[0];
		fRec35[2] = fRec35[1]; fRec35[1] = fRec35[0];
		fRec36[1] = fRec36[0];
		fRec31[2] = fRec31[1]; fRec31[1] = fRec31[0];
		fRec32[2] = fRec32[1]; fRec32[1] = fRec32[0];
		fRec33[1] = fRec33[0];
		fRec27[1] = fRec27[0];
		fRec20[1] = fRec20[0];
		fRec21[1] = fRec21[0];
		fRec22[1] = fRec22[0];
		fRec25[2] = fRec25[1]; fRec25[1] = fRec25[0];
		fRec26[1] = fRec26[0];
		fRec23[2] = fRec23[1]; fRec23[1] = fRec23[0];
		fRec24[1] = fRec24[0];
		fRec19[1] = fRec19[0];
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
		fRec12[1] = fRec12[0];
		fVec7[1] = fVec7[0];
		fRec13[2] = fRec13[1]; fRec13[1] = fRec13[0];
		fRec14[1] = fRec14[0];
		fVec6[1] = fVec6[0];
		fRec15[2] = fRec15[1]; fRec15[1] = fRec15[0];
		fRec16[1] = fRec16[0];
		fVec5[1] = fVec5[0];
		fRec17[2] = fRec17[1]; fRec17[1] = fRec17[0];
		fRec18[1] = fRec18[0];
		fVec4[1] = fVec4[0];
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fVec3[1] = fVec3[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		fVec2[1] = fVec2[0];
		fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
		fVec1[1] = fVec1[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec10[1] = fRec10[0];
		fVec0[1] = fVec0[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}

int Dsp::register_par(const ParamReg& reg)
{
	static const value_pair fslider11_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	reg.registerEnumVar("mbcs.Mode1","","S",N_("Compress or Mute the selected band, or Bypass The Compressor"),fslider11_values,&fslider11, 1.0, 1.0, 3.0, 1.0);
	static const value_pair fslider5_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	reg.registerEnumVar("mbcs.Mode2","","S",N_("Compress or Mute the selected band, or Bypass The Compressor"),fslider5_values,&fslider5, 1.0, 1.0, 3.0, 1.0);
	static const value_pair fslider17_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	reg.registerEnumVar("mbcs.Mode3","","S",N_("Compress or Mute the selected band, or Bypass The Compressor"),fslider17_values,&fslider17, 1.0, 1.0, 3.0, 1.0);
	static const value_pair fslider23_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	reg.registerEnumVar("mbcs.Mode4","","S",N_("Compress or Mute the selected band, or Bypass The Compressor"),fslider23_values,&fslider23, 1.0, 1.0, 3.0, 1.0);
	static const value_pair fslider29_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	reg.registerEnumVar("mbcs.Mode5","","S",N_("Compress or Mute the selected band, or Bypass The Compressor"),fslider29_values,&fslider29, 1.0, 1.0, 3.0, 1.0);
	reg.registerVar("mbcs.Makeup1","","S",N_("Post amplification and threshold"),&fslider13, 13.0, -5e+01, 5e+01, 0.1);
	reg.registerVar("mbcs.Makeup2","","S",N_("Post amplification and threshold"),&fslider7, 1e+01, -5e+01, 5e+01, 0.1);
	reg.registerVar("mbcs.Makeup3","","S",N_("Post amplification and threshold"),&fslider19, 4.0, -5e+01, 5e+01, 0.1);
	reg.registerVar("mbcs.Makeup4","","S",N_("Post amplification and threshold"),&fslider25, 8.0, -5e+01, 5e+01, 0.1);
	reg.registerVar("mbcs.Makeup5","","S",N_("Post amplification and threshold"),&fslider31, 11.0, -5e+01, 5e+01, 0.1);
	reg.registerVar("mbcs.Makeup-Threshold1","","S",N_("Threshold correction, an anticlip measure"),&fslider15, 2.0, 0.0, 1e+01, 0.1);
	reg.registerVar("mbcs.Makeup-Threshold2","","S",N_("Threshold correction, an anticlip measure"),&fslider9, 2.0, 0.0, 1e+01, 0.1);
	reg.registerVar("mbcs.Makeup-Threshold3","","S",N_("Threshold correction, an anticlip measure"),&fslider21, 2.0, 0.0, 1e+01, 0.1);
	reg.registerVar("mbcs.Makeup-Threshold4","","S",N_("Threshold correction, an anticlip measure"),&fslider27, 2.0, 0.0, 1e+01, 0.1);
	reg.registerVar("mbcs.Makeup-Threshold5","","S",N_("Threshold correction, an anticlip measure"),&fslider33, 2.0, 0.0, 1e+01, 0.1);
	reg.registerVar("mbcs.Ratio1","","S",N_("Compression ratio"),&fslider14, 2.0, 1.0, 1e+02, 0.1);
	reg.registerVar("mbcs.Ratio2","","S",N_("Compression ratio"),&fslider8, 2.0, 1.0, 1e+02, 0.1);
	reg.registerVar("mbcs.Ratio3","","S",N_("Compression ratio"),&fslider20, 2.0, 1.0, 1e+02, 0.1);
	reg.registerVar("mbcs.Ratio4","","S",N_("Compression ratio"),&fslider26, 2.0, 1.0, 1e+02, 0.1);
	reg.registerVar("mbcs.Ratio5","","S",N_("Compression ratio"),&fslider32, 2.0, 1.0, 1e+02, 0.1);
	reg.registerVar("mbcs.Attack1","","S",N_("Time before the compressor starts to kick in"),&fslider10, 0.012, 0.001, 1.0, 0.001);
	reg.registerVar("mbcs.Attack2","","S",N_("Time before the compressor starts to kick in"),&fslider0, 0.012, 0.001, 1.0, 0.001);
	reg.registerVar("mbcs.Attack3","","S",N_("Time before the compressor starts to kick in"),&fslider16, 0.012, 0.001, 1.0, 0.001);
	reg.registerVar("mbcs.Attack4","","S",N_("Time before the compressor starts to kick in"),&fslider22, 0.012, 0.001, 1.0, 0.001);
	reg.registerVar("mbcs.Attack5","","S",N_("Time before the compressor starts to kick in"),&fslider28, 0.012, 0.001, 1.0, 0.001);
	reg.registerVar("mbcs.Release1","","S",N_("Time before the compressor releases the sound"),&fslider12, 1.25, 0.01, 1e+01, 0.01);
	reg.registerVar("mbcs.Release2","","S",N_("Time before the compressor releases the sound"),&fslider6, 1.25, 0.01, 1e+01, 0.01);
	reg.registerVar("mbcs.Release3","","S",N_("Time before the compressor releases the sound"),&fslider18, 1.25, 0.01, 1e+01, 0.01);
	reg.registerVar("mbcs.Release4","","S",N_("Time before the compressor releases the sound"),&fslider24, 1.25, 0.01, 1e+01, 0.01);
	reg.registerVar("mbcs.Release5","","S",N_("Time before the compressor releases the sound"),&fslider30, 1.25, 0.01, 1e+01, 0.01);
	reg.registerVar("mbcs.crossover_b1_b2",N_("Crossover B1-B2 (hz)"),"SL",N_("Crossover bandpass frequency"),&fslider1, 8e+01, 2e+01, 2e+04, 1.08);
	reg.registerVar("mbcs.crossover_b2_b3",N_("Crossover B2-B3 (hz)"),"SL",N_("Crossover bandpass frequency"),&fslider2, 2.1e+02, 2e+01, 2e+04, 1.08);
	reg.registerVar("mbcs.crossover_b3_b4",N_("Crossover B3-B4 (hz)"),"SL",N_("Crossover bandpass frequency"),&fslider3, 1.7e+03, 2e+01, 2e+04, 1.08);
	reg.registerVar("mbcs.crossover_b4_b5",N_("Crossover B4-B5 (hz)"),"SL",N_("Crossover bandpass frequency"),&fslider4, 5e+03, 2e+01, 2e+04, 1.08);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("mbcs" "." p)

b.openHorizontalhideBox("");
b.closeBox();

b.openHorizontalBox("");
b.openVerticalBox("");

b.openTabBox("");

b.openHorizontalBox(N_("Band 1"));
b.openpaintampBox("");
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
b.create_small_rackknob(PARAM("Release1") ,N_("Release"));
b.closeBox();
b.closeBox();
b.closeBox();
b.closeBox();

b.openHorizontalBox(N_("Band 2"));
b.openpaintampBox("");
b.openVerticalBox("");
b.openHorizontalBox("");
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Makeup2"), N_("Makeup (db)"));
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
b.openpaintampBox("");
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
b.openpaintampBox("");
b.openVerticalBox("");
b.openHorizontalBox("");
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Makeup4"), N_("Makeup (db)"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Makeup-Threshold4"), N_("Anticlip (db)"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b3_b4"),N_("Low (hz)"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b4_b5"),N_("High (hz)"));
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
b.openpaintampBox("");
b.openVerticalBox("");
b.openHorizontalBox("");
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Makeup5"), N_("Makeup (db)"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Makeup-Threshold5"), N_( "Anticlip (db)"));
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

} // end namespace mbcs
} // end namespace pluginlib
