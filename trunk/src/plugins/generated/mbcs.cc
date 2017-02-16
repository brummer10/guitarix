// generated from file '../src/plugins/mbcs.dsp' by dsp2cc:
// Code generated with Faust 0.9.73 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

namespace pluginlib {
namespace mbcs {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	int 	iConst0;
	double 	fConst1;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT 	fslider2;
	double 	fConst2;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT 	fslider5;
	double 	fVec0[2];
	double 	fRec14[2];
	double 	fRec13[3];
	double 	fVec1[2];
	double 	fRec12[2];
	double 	fRec11[3];
	double 	fVec2[2];
	double 	fRec10[2];
	double 	fRec9[3];
	double 	fVec3[2];
	double 	fRec8[2];
	double 	fRec7[3];
	FAUSTFLOAT 	fslider6;
	double 	fVec4[2];
	double 	fRec22[2];
	double 	fRec21[3];
	double 	fVec5[2];
	double 	fRec20[2];
	double 	fRec19[3];
	double 	fVec6[2];
	double 	fRec18[2];
	double 	fRec17[3];
	double 	fVec7[2];
	double 	fRec16[2];
	double 	fRec15[3];
	double 	fRec6[2];
	double 	fRec5[2];
	FAUSTFLOAT 	fslider7;
	double 	fConst3;
	FAUSTFLOAT 	fslider8;
	double 	fRec4[2];
	FAUSTFLOAT 	fslider9;
	double 	fRec23[2];
	double 	fRec0[2];
	int 	iRec1[2];
	double 	fRec2[2];
	FAUSTFLOAT 	fbargraph0;
	FAUSTFLOAT 	fslider10;
	FAUSTFLOAT 	fslider11;
	double 	fRec32[2];
	double 	fRec31[3];
	FAUSTFLOAT 	fslider12;
	double 	fRec34[2];
	double 	fRec33[3];
	double 	fRec30[2];
	double 	fRec29[2];
	FAUSTFLOAT 	fslider13;
	FAUSTFLOAT 	fslider14;
	double 	fRec28[2];
	FAUSTFLOAT 	fslider15;
	double 	fRec35[2];
	double 	fRec24[2];
	int 	iRec25[2];
	double 	fRec26[2];
	FAUSTFLOAT 	fbargraph1;
	FAUSTFLOAT 	fslider16;
	FAUSTFLOAT 	fslider17;
	double 	fRec45[2];
	double 	fRec44[3];
	double 	fRec43[3];
	FAUSTFLOAT 	fslider18;
	double 	fRec48[2];
	double 	fRec47[3];
	double 	fRec46[3];
	double 	fRec42[2];
	double 	fRec41[2];
	FAUSTFLOAT 	fslider19;
	FAUSTFLOAT 	fslider20;
	double 	fRec40[2];
	FAUSTFLOAT 	fslider21;
	double 	fRec49[2];
	double 	fRec36[2];
	int 	iRec37[2];
	double 	fRec38[2];
	FAUSTFLOAT 	fbargraph2;
	FAUSTFLOAT 	fslider22;
	FAUSTFLOAT 	fslider23;
	double 	fRec60[2];
	double 	fRec59[3];
	double 	fRec58[3];
	double 	fRec57[3];
	FAUSTFLOAT 	fslider24;
	double 	fRec64[2];
	double 	fRec63[3];
	double 	fRec62[3];
	double 	fRec61[3];
	double 	fRec56[2];
	double 	fRec55[2];
	FAUSTFLOAT 	fslider25;
	FAUSTFLOAT 	fslider26;
	double 	fRec54[2];
	FAUSTFLOAT 	fslider27;
	double 	fRec65[2];
	double 	fRec50[2];
	int 	iRec51[2];
	double 	fRec52[2];
	FAUSTFLOAT 	fbargraph3;
	FAUSTFLOAT 	fslider28;
	FAUSTFLOAT 	fslider29;
	double 	fRec77[2];
	double 	fRec76[3];
	double 	fRec75[3];
	double 	fRec74[3];
	double 	fRec73[3];
	FAUSTFLOAT 	fslider30;
	double 	fRec82[2];
	double 	fRec81[3];
	double 	fRec80[3];
	double 	fRec79[3];
	double 	fRec78[3];
	double 	fRec72[2];
	double 	fRec71[2];
	FAUSTFLOAT 	fslider31;
	FAUSTFLOAT 	fslider32;
	double 	fRec70[2];
	FAUSTFLOAT 	fslider33;
	double 	fRec83[2];
	double 	fRec66[2];
	int 	iRec67[2];
	double 	fRec68[2];
	FAUSTFLOAT 	fbargraph4;
	void clear_state_f();
	int load_ui_f(const UiBuilder& b, int form);
	static const char *glade_def;
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
	name = N_("Multi Band Compressor Stereo");
	groups = 0;
	description = N_("Multi Band Compressor contributed by kokoko3k"); // description (tooltip)
	category = N_("Guitar Effects");       // category
	shortname = N_("MB Comp St");     // shortname
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
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<3; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<3; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<3; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<3; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<3; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<3; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<3; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) fVec7[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<3; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) iRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec32[i] = 0;
	for (int i=0; i<3; i++) fRec31[i] = 0;
	for (int i=0; i<2; i++) fRec34[i] = 0;
	for (int i=0; i<3; i++) fRec33[i] = 0;
	for (int i=0; i<2; i++) fRec30[i] = 0;
	for (int i=0; i<2; i++) fRec29[i] = 0;
	for (int i=0; i<2; i++) fRec28[i] = 0;
	for (int i=0; i<2; i++) fRec35[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) iRec25[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<2; i++) fRec45[i] = 0;
	for (int i=0; i<3; i++) fRec44[i] = 0;
	for (int i=0; i<3; i++) fRec43[i] = 0;
	for (int i=0; i<2; i++) fRec48[i] = 0;
	for (int i=0; i<3; i++) fRec47[i] = 0;
	for (int i=0; i<3; i++) fRec46[i] = 0;
	for (int i=0; i<2; i++) fRec42[i] = 0;
	for (int i=0; i<2; i++) fRec41[i] = 0;
	for (int i=0; i<2; i++) fRec40[i] = 0;
	for (int i=0; i<2; i++) fRec49[i] = 0;
	for (int i=0; i<2; i++) fRec36[i] = 0;
	for (int i=0; i<2; i++) iRec37[i] = 0;
	for (int i=0; i<2; i++) fRec38[i] = 0;
	for (int i=0; i<2; i++) fRec60[i] = 0;
	for (int i=0; i<3; i++) fRec59[i] = 0;
	for (int i=0; i<3; i++) fRec58[i] = 0;
	for (int i=0; i<3; i++) fRec57[i] = 0;
	for (int i=0; i<2; i++) fRec64[i] = 0;
	for (int i=0; i<3; i++) fRec63[i] = 0;
	for (int i=0; i<3; i++) fRec62[i] = 0;
	for (int i=0; i<3; i++) fRec61[i] = 0;
	for (int i=0; i<2; i++) fRec56[i] = 0;
	for (int i=0; i<2; i++) fRec55[i] = 0;
	for (int i=0; i<2; i++) fRec54[i] = 0;
	for (int i=0; i<2; i++) fRec65[i] = 0;
	for (int i=0; i<2; i++) fRec50[i] = 0;
	for (int i=0; i<2; i++) iRec51[i] = 0;
	for (int i=0; i<2; i++) fRec52[i] = 0;
	for (int i=0; i<2; i++) fRec77[i] = 0;
	for (int i=0; i<3; i++) fRec76[i] = 0;
	for (int i=0; i<3; i++) fRec75[i] = 0;
	for (int i=0; i<3; i++) fRec74[i] = 0;
	for (int i=0; i<3; i++) fRec73[i] = 0;
	for (int i=0; i<2; i++) fRec82[i] = 0;
	for (int i=0; i<3; i++) fRec81[i] = 0;
	for (int i=0; i<3; i++) fRec80[i] = 0;
	for (int i=0; i<3; i++) fRec79[i] = 0;
	for (int i=0; i<3; i++) fRec78[i] = 0;
	for (int i=0; i<2; i++) fRec72[i] = 0;
	for (int i=0; i<2; i++) fRec71[i] = 0;
	for (int i=0; i<2; i++) fRec70[i] = 0;
	for (int i=0; i<2; i++) fRec83[i] = 0;
	for (int i=0; i<2; i++) fRec66[i] = 0;
	for (int i=0; i<2; i++) iRec67[i] = 0;
	for (int i=0; i<2; i++) fRec68[i] = 0;
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
	fConst2 = (3.141592653589793 / double(iConst0));
	fConst3 = (2.0 / double(iConst0));
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
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
		double fTemp0 = (double)input1[i];
		fVec0[0] = fTemp0;
		fRec14[0] = ((fSlow32 * fRec14[1]) + (fSlow31 * (fVec0[0] + fVec0[1])));
		fRec13[0] = (fRec14[0] - (fSlow29 * ((fSlow27 * fRec13[2]) + (fSlow25 * fRec13[1]))));
		double fTemp1 = (fRec13[2] + (fRec13[0] + (2 * fRec13[1])));
		double fTemp2 = (fSlow29 * fTemp1);
		fVec1[0] = fTemp2;
		fRec12[0] = ((fSlow35 * fRec12[1]) + (fSlow34 * (fVec1[0] + fVec1[1])));
		fRec11[0] = (fRec12[0] - (fSlow22 * ((fSlow20 * fRec11[2]) + (fSlow18 * fRec11[1]))));
		double fTemp3 = (fRec11[2] + (fRec11[0] + (2 * fRec11[1])));
		double fTemp4 = (fSlow22 * fTemp3);
		fVec2[0] = fTemp4;
		fRec10[0] = ((fSlow38 * fRec10[1]) + (fSlow37 * (fVec2[0] + fVec2[1])));
		fRec9[0] = (fRec10[0] - (fSlow15 * ((fSlow13 * fRec9[2]) + (fSlow11 * fRec9[1]))));
		double fTemp5 = (fRec9[2] + (fRec9[0] + (2 * fRec9[1])));
		double fTemp6 = (fSlow15 * fTemp5);
		fVec3[0] = fTemp6;
		fRec8[0] = ((fSlow41 * fRec8[1]) + (fSlow40 * (fVec3[0] + fVec3[1])));
		fRec7[0] = (fRec8[0] - (fSlow8 * ((fSlow7 * fRec7[2]) + (fSlow5 * fRec7[1]))));
		double fTemp7 = (fSlow8 * (fRec7[2] + (fRec7[0] + (2 * fRec7[1]))));
		double fTemp8 = ((iSlow44)?0:fTemp7);
		double fTemp9 = (double)input0[i];
		fVec4[0] = fTemp9;
		fRec22[0] = ((fSlow32 * fRec22[1]) + (fSlow31 * (fVec4[0] + fVec4[1])));
		fRec21[0] = (fRec22[0] - (fSlow29 * ((fSlow27 * fRec21[2]) + (fSlow25 * fRec21[1]))));
		double fTemp10 = (fRec21[2] + (fRec21[0] + (2 * fRec21[1])));
		double fTemp11 = (fSlow29 * fTemp10);
		fVec5[0] = fTemp11;
		fRec20[0] = ((fSlow35 * fRec20[1]) + (fSlow34 * (fVec5[0] + fVec5[1])));
		fRec19[0] = (fRec20[0] - (fSlow22 * ((fSlow20 * fRec19[2]) + (fSlow18 * fRec19[1]))));
		double fTemp12 = (fRec19[2] + (fRec19[0] + (2 * fRec19[1])));
		double fTemp13 = (fSlow22 * fTemp12);
		fVec6[0] = fTemp13;
		fRec18[0] = ((fSlow38 * fRec18[1]) + (fSlow37 * (fVec6[0] + fVec6[1])));
		fRec17[0] = (fRec18[0] - (fSlow15 * ((fSlow13 * fRec17[2]) + (fSlow11 * fRec17[1]))));
		double fTemp14 = (fRec17[2] + (fRec17[0] + (2 * fRec17[1])));
		double fTemp15 = (fSlow15 * fTemp14);
		fVec7[0] = fTemp15;
		fRec16[0] = ((fSlow41 * fRec16[1]) + (fSlow40 * (fVec7[0] + fVec7[1])));
		fRec15[0] = (fRec16[0] - (fSlow8 * ((fSlow7 * fRec15[2]) + (fSlow5 * fRec15[1]))));
		double fTemp16 = (fSlow8 * (fRec15[2] + (fRec15[0] + (2 * fRec15[1]))));
		double fTemp17 = ((iSlow44)?0:fTemp16);
		double fTemp18 = fabs((fabs(fTemp17) + fabs(fTemp8)));
		double fTemp19 = ((int((fRec5[1] > fTemp18)))?fSlow2:fSlow1);
		fRec6[0] = ((fRec6[1] * fTemp19) + (fTemp18 * (1.0 - fTemp19)));
		fRec5[0] = fRec6[0];
		fRec4[0] = ((fSlow46 * fRec4[1]) + (fSlow47 * max((fSlow45 + (20 * log10(fRec5[0]))), 0.0)));
		double fTemp20 = pow(10,(0.05 * fRec4[0]));
		fRec23[0] = ((0.999 * fRec23[1]) + fSlow48);
		double fTemp21 = (fSlow49 * (fRec23[0] * ((iSlow44)?fTemp7:(fTemp8 * fTemp20))));
		double fTemp22 = (fSlow49 * (fRec23[0] * ((iSlow44)?fTemp16:(fTemp17 * fTemp20))));
		double 	fRec3 = max(fConst1, (fabs(fTemp22) + fabs(fTemp21)));
		int iTemp23 = int((iRec1[1] < 4096));
		fRec0[0] = ((iTemp23)?max(fRec0[1], fRec3):fRec3);
		iRec1[0] = ((iTemp23)?(1 + iRec1[1]):1);
		fRec2[0] = ((iTemp23)?fRec2[1]:fRec0[1]);
		fbargraph0 = (0.5 * fRec2[0]);
		fRec32[0] = ((fSlow41 * fRec32[1]) + (fSlow40 * ((fSlow54 * fTemp5) + (fSlow53 * fVec3[1]))));
		fRec31[0] = (fRec32[0] - (fSlow8 * ((fSlow7 * fRec31[2]) + (fSlow5 * fRec31[1]))));
		double fTemp24 = (fSlow8 * (((fSlow4 * fRec31[0]) + (fSlow55 * fRec31[1])) + (fSlow4 * fRec31[2])));
		double fTemp25 = ((iSlow58)?0:fTemp24);
		fRec34[0] = ((fSlow41 * fRec34[1]) + (fSlow40 * ((fSlow54 * fTemp14) + (fSlow53 * fVec7[1]))));
		fRec33[0] = (fRec34[0] - (fSlow8 * ((fSlow7 * fRec33[2]) + (fSlow5 * fRec33[1]))));
		double fTemp26 = (fSlow8 * (((fSlow4 * fRec33[0]) + (fSlow55 * fRec33[1])) + (fSlow4 * fRec33[2])));
		double fTemp27 = ((iSlow58)?0:fTemp26);
		double fTemp28 = fabs((fabs(fTemp27) + fabs(fTemp25)));
		double fTemp29 = ((int((fRec29[1] > fTemp28)))?fSlow52:fSlow51);
		fRec30[0] = ((fRec30[1] * fTemp29) + (fTemp28 * (1.0 - fTemp29)));
		fRec29[0] = fRec30[0];
		fRec28[0] = ((fSlow60 * fRec28[1]) + (fSlow61 * max((fSlow59 + (20 * log10(fRec29[0]))), 0.0)));
		double fTemp30 = pow(10,(0.05 * fRec28[0]));
		fRec35[0] = ((0.999 * fRec35[1]) + fSlow62);
		double fTemp31 = (fSlow63 * (fRec35[0] * ((iSlow58)?fTemp24:(fTemp25 * fTemp30))));
		double fTemp32 = (fSlow63 * (fRec35[0] * ((iSlow58)?fTemp26:(fTemp27 * fTemp30))));
		double 	fRec27 = max(fConst1, (fabs(fTemp32) + fabs(fTemp31)));
		int iTemp33 = int((iRec25[1] < 4096));
		fRec24[0] = ((iTemp33)?max(fRec24[1], fRec27):fRec27);
		iRec25[0] = ((iTemp33)?(1 + iRec25[1]):1);
		fRec26[0] = ((iTemp33)?fRec26[1]:fRec24[1]);
		fbargraph1 = (0.5 * fRec26[0]);
		double fTemp34 = (fSlow5 * fRec43[1]);
		fRec45[0] = ((fSlow38 * fRec45[1]) + (fSlow37 * ((fSlow70 * fTemp3) + (fSlow69 * fVec2[1]))));
		fRec44[0] = (fRec45[0] - (fSlow15 * ((fSlow13 * fRec44[2]) + (fSlow11 * fRec44[1]))));
		fRec43[0] = ((fSlow15 * (((fSlow10 * fRec44[0]) + (fSlow71 * fRec44[1])) + (fSlow10 * fRec44[2]))) - (fSlow68 * ((fSlow67 * fRec43[2]) + fTemp34)));
		double fTemp35 = (fRec43[2] + (fSlow68 * (fTemp34 + (fSlow67 * fRec43[0]))));
		double fTemp36 = ((iSlow74)?0:fTemp35);
		double fTemp37 = (fSlow5 * fRec46[1]);
		fRec48[0] = ((fSlow38 * fRec48[1]) + (fSlow37 * ((fSlow70 * fTemp12) + (fSlow69 * fVec6[1]))));
		fRec47[0] = (fRec48[0] - (fSlow15 * ((fSlow13 * fRec47[2]) + (fSlow11 * fRec47[1]))));
		fRec46[0] = ((fSlow15 * (((fSlow10 * fRec47[0]) + (fSlow71 * fRec47[1])) + (fSlow10 * fRec47[2]))) - (fSlow68 * ((fSlow67 * fRec46[2]) + fTemp37)));
		double fTemp38 = (fRec46[2] + (fSlow68 * (fTemp37 + (fSlow67 * fRec46[0]))));
		double fTemp39 = ((iSlow74)?0:fTemp38);
		double fTemp40 = fabs((fabs(fTemp39) + fabs(fTemp36)));
		double fTemp41 = ((int((fRec41[1] > fTemp40)))?fSlow66:fSlow65);
		fRec42[0] = ((fRec42[1] * fTemp41) + (fTemp40 * (1.0 - fTemp41)));
		fRec41[0] = fRec42[0];
		fRec40[0] = ((fSlow76 * fRec40[1]) + (fSlow77 * max((fSlow75 + (20 * log10(fRec41[0]))), 0.0)));
		double fTemp42 = pow(10,(0.05 * fRec40[0]));
		fRec49[0] = ((0.999 * fRec49[1]) + fSlow78);
		double fTemp43 = (fSlow79 * (fRec49[0] * ((iSlow74)?fTemp35:(fTemp36 * fTemp42))));
		double fTemp44 = (fSlow79 * (fRec49[0] * ((iSlow74)?fTemp38:(fTemp39 * fTemp42))));
		double 	fRec39 = max(fConst1, (fabs(fTemp44) + fabs(fTemp43)));
		int iTemp45 = int((iRec37[1] < 4096));
		fRec36[0] = ((iTemp45)?max(fRec36[1], fRec39):fRec39);
		iRec37[0] = ((iTemp45)?(1 + iRec37[1]):1);
		fRec38[0] = ((iTemp45)?fRec38[1]:fRec36[1]);
		fbargraph2 = (0.5 * fRec38[0]);
		double fTemp46 = (fSlow5 * fRec57[1]);
		double fTemp47 = (fSlow11 * fRec58[1]);
		fRec60[0] = ((fSlow35 * fRec60[1]) + (fSlow34 * ((fSlow86 * fTemp1) + (fSlow85 * fVec1[1]))));
		fRec59[0] = (fRec60[0] - (fSlow22 * ((fSlow20 * fRec59[2]) + (fSlow18 * fRec59[1]))));
		fRec58[0] = ((fSlow22 * (((fSlow17 * fRec59[0]) + (fSlow87 * fRec59[1])) + (fSlow17 * fRec59[2]))) - (fSlow84 * ((fSlow83 * fRec58[2]) + fTemp47)));
		fRec57[0] = ((fRec58[2] + (fSlow84 * (fTemp47 + (fSlow83 * fRec58[0])))) - (fSlow68 * ((fSlow67 * fRec57[2]) + fTemp46)));
		double fTemp48 = (fRec57[2] + (fSlow68 * (fTemp46 + (fSlow67 * fRec57[0]))));
		double fTemp49 = ((iSlow90)?0:fTemp48);
		double fTemp50 = (fSlow5 * fRec61[1]);
		double fTemp51 = (fSlow11 * fRec62[1]);
		fRec64[0] = ((fSlow35 * fRec64[1]) + (fSlow34 * ((fSlow86 * fTemp10) + (fSlow85 * fVec5[1]))));
		fRec63[0] = (fRec64[0] - (fSlow22 * ((fSlow20 * fRec63[2]) + (fSlow18 * fRec63[1]))));
		fRec62[0] = ((fSlow22 * (((fSlow17 * fRec63[0]) + (fSlow87 * fRec63[1])) + (fSlow17 * fRec63[2]))) - (fSlow84 * ((fSlow83 * fRec62[2]) + fTemp51)));
		fRec61[0] = ((fRec62[2] + (fSlow84 * (fTemp51 + (fSlow83 * fRec62[0])))) - (fSlow68 * ((fSlow67 * fRec61[2]) + fTemp50)));
		double fTemp52 = (fRec61[2] + (fSlow68 * (fTemp50 + (fSlow67 * fRec61[0]))));
		double fTemp53 = ((iSlow90)?0:fTemp52);
		double fTemp54 = fabs((fabs(fTemp53) + fabs(fTemp49)));
		double fTemp55 = ((int((fRec55[1] > fTemp54)))?fSlow82:fSlow81);
		fRec56[0] = ((fRec56[1] * fTemp55) + (fTemp54 * (1.0 - fTemp55)));
		fRec55[0] = fRec56[0];
		fRec54[0] = ((fSlow92 * fRec54[1]) + (fSlow93 * max((fSlow91 + (20 * log10(fRec55[0]))), 0.0)));
		double fTemp56 = pow(10,(0.05 * fRec54[0]));
		fRec65[0] = ((0.999 * fRec65[1]) + fSlow94);
		double fTemp57 = (fSlow95 * (fRec65[0] * ((iSlow90)?fTemp48:(fTemp49 * fTemp56))));
		double fTemp58 = (fSlow95 * (fRec65[0] * ((iSlow90)?fTemp52:(fTemp53 * fTemp56))));
		double 	fRec53 = max(fConst1, (fabs(fTemp58) + fabs(fTemp57)));
		int iTemp59 = int((iRec51[1] < 4096));
		fRec50[0] = ((iTemp59)?max(fRec50[1], fRec53):fRec53);
		iRec51[0] = ((iTemp59)?(1 + iRec51[1]):1);
		fRec52[0] = ((iTemp59)?fRec52[1]:fRec50[1]);
		fbargraph3 = (0.5 * fRec52[0]);
		double fTemp60 = (fSlow5 * fRec73[1]);
		double fTemp61 = (fSlow11 * fRec74[1]);
		double fTemp62 = (fSlow18 * fRec75[1]);
		fRec77[0] = ((fSlow32 * fRec77[1]) + (fSlow31 * ((fSlow26 * fVec0[0]) + (fSlow101 * fVec0[1]))));
		fRec76[0] = (fRec77[0] - (fSlow29 * ((fSlow27 * fRec76[2]) + (fSlow25 * fRec76[1]))));
		fRec75[0] = ((fSlow29 * (((fSlow24 * fRec76[0]) + (fSlow102 * fRec76[1])) + (fSlow24 * fRec76[2]))) - (fSlow100 * ((fSlow99 * fRec75[2]) + fTemp62)));
		fRec74[0] = ((fRec75[2] + (fSlow100 * (fTemp62 + (fSlow99 * fRec75[0])))) - (fSlow84 * ((fSlow83 * fRec74[2]) + fTemp61)));
		fRec73[0] = ((fRec74[2] + (fSlow84 * (fTemp61 + (fSlow83 * fRec74[0])))) - (fSlow68 * ((fSlow67 * fRec73[2]) + fTemp60)));
		double fTemp63 = (fRec73[2] + (fSlow68 * (fTemp60 + (fSlow67 * fRec73[0]))));
		double fTemp64 = ((iSlow105)?0:fTemp63);
		double fTemp65 = (fSlow5 * fRec78[1]);
		double fTemp66 = (fSlow11 * fRec79[1]);
		double fTemp67 = (fSlow18 * fRec80[1]);
		fRec82[0] = ((fSlow32 * fRec82[1]) + (fSlow31 * ((fSlow26 * fVec4[0]) + (fSlow101 * fVec4[1]))));
		fRec81[0] = (fRec82[0] - (fSlow29 * ((fSlow27 * fRec81[2]) + (fSlow25 * fRec81[1]))));
		fRec80[0] = ((fSlow29 * (((fSlow24 * fRec81[0]) + (fSlow102 * fRec81[1])) + (fSlow24 * fRec81[2]))) - (fSlow100 * ((fSlow99 * fRec80[2]) + fTemp67)));
		fRec79[0] = ((fRec80[2] + (fSlow100 * (fTemp67 + (fSlow99 * fRec80[0])))) - (fSlow84 * ((fSlow83 * fRec79[2]) + fTemp66)));
		fRec78[0] = ((fRec79[2] + (fSlow84 * (fTemp66 + (fSlow83 * fRec79[0])))) - (fSlow68 * ((fSlow67 * fRec78[2]) + fTemp65)));
		double fTemp68 = (fRec78[2] + (fSlow68 * (fTemp65 + (fSlow67 * fRec78[0]))));
		double fTemp69 = ((iSlow105)?0:fTemp68);
		double fTemp70 = fabs((fabs(fTemp69) + fabs(fTemp64)));
		double fTemp71 = ((int((fRec71[1] > fTemp70)))?fSlow98:fSlow97);
		fRec72[0] = ((fRec72[1] * fTemp71) + (fTemp70 * (1.0 - fTemp71)));
		fRec71[0] = fRec72[0];
		fRec70[0] = ((fSlow107 * fRec70[1]) + (fSlow108 * max((fSlow106 + (20 * log10(fRec71[0]))), 0.0)));
		double fTemp72 = pow(10,(0.05 * fRec70[0]));
		fRec83[0] = ((0.999 * fRec83[1]) + fSlow109);
		double fTemp73 = (fSlow110 * (fRec83[0] * ((iSlow105)?fTemp63:(fTemp64 * fTemp72))));
		double fTemp74 = (fSlow110 * (fRec83[0] * ((iSlow105)?fTemp68:(fTemp69 * fTemp72))));
		double 	fRec69 = max(fConst1, (fabs(fTemp74) + fabs(fTemp73)));
		int iTemp75 = int((iRec67[1] < 4096));
		fRec66[0] = ((iTemp75)?max(fRec66[1], fRec69):fRec69);
		iRec67[0] = ((iTemp75)?(1 + iRec67[1]):1);
		fRec68[0] = ((iTemp75)?fRec68[1]:fRec66[1]);
		fbargraph4 = (0.5 * fRec68[0]);
		output0[i] = (FAUSTFLOAT)((((fTemp74 + fTemp58) + fTemp44) + fTemp32) + fTemp22);
		output1[i] = (FAUSTFLOAT)(fTemp21 + (fTemp31 + (fTemp43 + (fTemp73 + fTemp57))));
		// post processing
		fRec68[1] = fRec68[0];
		iRec67[1] = iRec67[0];
		fRec66[1] = fRec66[0];
		fRec83[1] = fRec83[0];
		fRec70[1] = fRec70[0];
		fRec71[1] = fRec71[0];
		fRec72[1] = fRec72[0];
		fRec78[2] = fRec78[1]; fRec78[1] = fRec78[0];
		fRec79[2] = fRec79[1]; fRec79[1] = fRec79[0];
		fRec80[2] = fRec80[1]; fRec80[1] = fRec80[0];
		fRec81[2] = fRec81[1]; fRec81[1] = fRec81[0];
		fRec82[1] = fRec82[0];
		fRec73[2] = fRec73[1]; fRec73[1] = fRec73[0];
		fRec74[2] = fRec74[1]; fRec74[1] = fRec74[0];
		fRec75[2] = fRec75[1]; fRec75[1] = fRec75[0];
		fRec76[2] = fRec76[1]; fRec76[1] = fRec76[0];
		fRec77[1] = fRec77[0];
		fRec52[1] = fRec52[0];
		iRec51[1] = iRec51[0];
		fRec50[1] = fRec50[0];
		fRec65[1] = fRec65[0];
		fRec54[1] = fRec54[0];
		fRec55[1] = fRec55[0];
		fRec56[1] = fRec56[0];
		fRec61[2] = fRec61[1]; fRec61[1] = fRec61[0];
		fRec62[2] = fRec62[1]; fRec62[1] = fRec62[0];
		fRec63[2] = fRec63[1]; fRec63[1] = fRec63[0];
		fRec64[1] = fRec64[0];
		fRec57[2] = fRec57[1]; fRec57[1] = fRec57[0];
		fRec58[2] = fRec58[1]; fRec58[1] = fRec58[0];
		fRec59[2] = fRec59[1]; fRec59[1] = fRec59[0];
		fRec60[1] = fRec60[0];
		fRec38[1] = fRec38[0];
		iRec37[1] = iRec37[0];
		fRec36[1] = fRec36[0];
		fRec49[1] = fRec49[0];
		fRec40[1] = fRec40[0];
		fRec41[1] = fRec41[0];
		fRec42[1] = fRec42[0];
		fRec46[2] = fRec46[1]; fRec46[1] = fRec46[0];
		fRec47[2] = fRec47[1]; fRec47[1] = fRec47[0];
		fRec48[1] = fRec48[0];
		fRec43[2] = fRec43[1]; fRec43[1] = fRec43[0];
		fRec44[2] = fRec44[1]; fRec44[1] = fRec44[0];
		fRec45[1] = fRec45[0];
		fRec26[1] = fRec26[0];
		iRec25[1] = iRec25[0];
		fRec24[1] = fRec24[0];
		fRec35[1] = fRec35[0];
		fRec28[1] = fRec28[0];
		fRec29[1] = fRec29[0];
		fRec30[1] = fRec30[0];
		fRec33[2] = fRec33[1]; fRec33[1] = fRec33[0];
		fRec34[1] = fRec34[0];
		fRec31[2] = fRec31[1]; fRec31[1] = fRec31[0];
		fRec32[1] = fRec32[0];
		fRec2[1] = fRec2[0];
		iRec1[1] = iRec1[0];
		fRec0[1] = fRec0[0];
		fRec23[1] = fRec23[0];
		fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		fRec15[2] = fRec15[1]; fRec15[1] = fRec15[0];
		fRec16[1] = fRec16[0];
		fVec7[1] = fVec7[0];
		fRec17[2] = fRec17[1]; fRec17[1] = fRec17[0];
		fRec18[1] = fRec18[0];
		fVec6[1] = fVec6[0];
		fRec19[2] = fRec19[1]; fRec19[1] = fRec19[0];
		fRec20[1] = fRec20[0];
		fVec5[1] = fVec5[0];
		fRec21[2] = fRec21[1]; fRec21[1] = fRec21[0];
		fRec22[1] = fRec22[0];
		fVec4[1] = fVec4[0];
		fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
		fVec3[1] = fVec3[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec10[1] = fRec10[0];
		fVec2[1] = fVec2[0];
		fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
		fRec12[1] = fRec12[0];
		fVec1[1] = fVec1[0];
		fRec13[2] = fRec13[1]; fRec13[1] = fRec13[0];
		fRec14[1] = fRec14[0];
		fVec0[1] = fVec0[0];
	}
}
		
void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}

int Dsp::register_par(const ParamReg& reg)
{
	static const value_pair fslider6_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	reg.registerEnumVar("mbcs.Mode1","","S",N_("Compress or Mute the selected band, or Bypass The Compressor"),fslider6_values,&fslider6, 1.0, 1.0, 3.0, 1.0);
	static const value_pair fslider12_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	reg.registerEnumVar("mbcs.Mode2","","S",N_("Compress or Mute the selected band, or Bypass The Compressor"),fslider12_values,&fslider12, 1.0, 1.0, 3.0, 1.0);
	static const value_pair fslider18_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	reg.registerEnumVar("mbcs.Mode3","","S",N_("Compress or Mute the selected band, or Bypass The Compressor"),fslider18_values,&fslider18, 1.0, 1.0, 3.0, 1.0);
	static const value_pair fslider24_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	reg.registerEnumVar("mbcs.Mode4","","S",N_("Compress or Mute the selected band, or Bypass The Compressor"),fslider24_values,&fslider24, 1.0, 1.0, 3.0, 1.0);
	static const value_pair fslider30_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	reg.registerEnumVar("mbcs.Mode5","","S",N_("Compress or Mute the selected band, or Bypass The Compressor"),fslider30_values,&fslider30, 1.0, 1.0, 3.0, 1.0);
	reg.registerVar("mbcs.Makeup1","","S",N_("Post amplification and threshold"),&fslider7, 13.0, -5e+01, 5e+01, 0.1);
	reg.registerVar("mbcs.Makeup2","","S",N_("Post amplification and threshold"),&fslider13, 1e+01, -5e+01, 5e+01, 0.1);
	reg.registerVar("mbcs.Makeup3","","S",N_("Post amplification and threshold"),&fslider19, 4.0, -5e+01, 5e+01, 0.1);
	reg.registerVar("mbcs.Makeup4","","S",N_("Post amplification and threshold"),&fslider25, 8.0, -5e+01, 5e+01, 0.1);
	reg.registerVar("mbcs.Makeup5","","S",N_("Post amplification and threshold"),&fslider31, 11.0, -5e+01, 5e+01, 0.1);
	reg.registerVar("mbcs.Makeup-Threshold1","","S",N_("Threshold correction, an anticlip measure"),&fslider9, 2.0, 0.0, 1e+01, 0.1);
	reg.registerVar("mbcs.Makeup-Threshold2","","S",N_("Threshold correction, an anticlip measure"),&fslider15, 2.0, 0.0, 1e+01, 0.1);
	reg.registerVar("mbcs.Makeup-Threshold3","","S",N_("Threshold correction, an anticlip measure"),&fslider21, 2.0, 0.0, 1e+01, 0.1);
	reg.registerVar("mbcs.Makeup-Threshold4","","S",N_("Threshold correction, an anticlip measure"),&fslider27, 2.0, 0.0, 1e+01, 0.1);
	reg.registerVar("mbcs.Makeup-Threshold5","","S",N_("Threshold correction, an anticlip measure"),&fslider33, 2.0, 0.0, 1e+01, 0.1);
	reg.registerVar("mbcs.Ratio1","","S",N_("Compression ratio"),&fslider8, 2.0, 1.0, 1e+02, 0.1);
	reg.registerVar("mbcs.Ratio2","","S",N_("Compression ratio"),&fslider14, 2.0, 1.0, 1e+02, 0.1);
	reg.registerVar("mbcs.Ratio3","","S",N_("Compression ratio"),&fslider20, 2.0, 1.0, 1e+02, 0.1);
	reg.registerVar("mbcs.Ratio4","","S",N_("Compression ratio"),&fslider26, 2.0, 1.0, 1e+02, 0.1);
	reg.registerVar("mbcs.Ratio5","","S",N_("Compression ratio"),&fslider32, 2.0, 1.0, 1e+02, 0.1);
	reg.registerVar("mbcs.Attack1","","S",N_("Time before the compressor starts to kick in"),&fslider0, 0.012, 0.001, 1.0, 0.001);
	reg.registerVar("mbcs.Attack2","","S",N_("Time before the compressor starts to kick in"),&fslider10, 0.012, 0.001, 1.0, 0.001);
	reg.registerVar("mbcs.Attack3","","S",N_("Time before the compressor starts to kick in"),&fslider16, 0.012, 0.001, 1.0, 0.001);
	reg.registerVar("mbcs.Attack4","","S",N_("Time before the compressor starts to kick in"),&fslider22, 0.012, 0.001, 1.0, 0.001);
	reg.registerVar("mbcs.Attack5","","S",N_("Time before the compressor starts to kick in"),&fslider28, 0.012, 0.001, 1.0, 0.001);
	reg.registerVar("mbcs.Release1","","S",N_("Time before the compressor releases the sound"),&fslider1, 1.25, 0.01, 1e+01, 0.01);
	reg.registerVar("mbcs.Release2","","S",N_("Time before the compressor releases the sound"),&fslider11, 1.25, 0.01, 1e+01, 0.01);
	reg.registerVar("mbcs.Release3","","S",N_("Time before the compressor releases the sound"),&fslider17, 1.25, 0.01, 1e+01, 0.01);
	reg.registerVar("mbcs.Release4","","S",N_("Time before the compressor releases the sound"),&fslider23, 1.25, 0.01, 1e+01, 0.01);
	reg.registerVar("mbcs.Release5","","S",N_("Time before the compressor releases the sound"),&fslider29, 1.25, 0.01, 1e+01, 0.01);
	reg.registerVar("mbcs.crossover_b1_b2",N_("Crossover B1-B2 (hz)"),"SL",N_("Crossover bandpass frequency"),&fslider2, 8e+01, 2e+01, 2e+04, 1.08);
	reg.registerVar("mbcs.crossover_b2_b3",N_("Crossover B2-B3 (hz)"),"SL",N_("Crossover bandpass frequency"),&fslider3, 2.1e+02, 2e+01, 2e+04, 1.08);
	reg.registerVar("mbcs.crossover_b3_b4",N_("Crossover B3-B4 (hz)"),"SL",N_("Crossover bandpass frequency"),&fslider4, 1.7e+03, 2e+01, 2e+04, 1.08);
	reg.registerVar("mbcs.crossover_b4_b5",N_("Crossover B4-B5 (hz)"),"SL",N_("Crossover bandpass frequency"),&fslider5, 5e+03, 2e+01, 2e+04, 1.08);
	reg.registerNonMidiFloatVar("mbcs.v1",&fbargraph0, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbcs.v2",&fbargraph1, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbcs.v3",&fbargraph2, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbcs.v4",&fbargraph3, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbcs.v5",&fbargraph4, false, true, -70.0, -70.0, 4.0, 0.00001);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

const char *Dsp::glade_def = "\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<interface>\n\
  <!-- interface-requires gxwidgets 0.0 -->\n\
  <requires lib=\"gtk+\" version=\"2.20\"/>\n\
  <!-- interface-naming-policy project-wide -->\n\
  <object class=\"GtkWindow\" id=\"window1\">\n\
    <property name=\"can_focus\">False</property>\n\
    <child>\n\
      <object class=\"GtkVBox\" id=\"vbox1\">\n\
        <property name=\"visible\">True</property>\n\
        <property name=\"can_focus\">False</property>\n\
        <child>\n\
          <object class=\"GtkHBox\" id=\"rackbox\">\n\
            <property name=\"visible\">True</property>\n\
            <property name=\"can_focus\">False</property>\n\
            <property name=\"spacing\">4</property>\n\
            <child>\n\
              <object class=\"GtkHBox\" id=\"hbox1\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">False</property>\n\
                <property name=\"spacing\">8</property>\n\
                <child>\n\
                  <object class=\"GtkNotebook\" id=\"notebook:tab_rack\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"tab_hborder\">0</property>\n\
                    <child>\n\
                      <object class=\"GtkHBox\" id=\"hbox2\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <child>\n\
                          <object class=\"GtkVBox\" id=\"vbox3\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"spacing\">4</property>\n\
                            <child>\n\
                              <object class=\"GtkHBox\" id=\"hbox4\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <child>\n\
                                  <object class=\"GtkVBox\" id=\"vbox4\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <child>\n\
                                      <object class=\"GtkLabel\" id=\"label_1:rack_label\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"label\" translatable=\"yes\">Ratio</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">False</property>\n\
                                        <property name=\"fill\">False</property>\n\
                                        <property name=\"position\">0</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GxSmallKnobR\" id=\"gxmediumknob1\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">True</property>\n\
                                        <property name=\"receives_default\">True</property>\n\
                                        <property name=\"var_id\">mbcs.Ratio1</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">1</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">True</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"position\">0</property>\n\
                                  </packing>\n\
                                </child>\n\
                                <child>\n\
                                  <object class=\"GtkVBox\" id=\"vbox5\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <child>\n\
                                      <object class=\"GtkLabel\" id=\"label_2:rack_label\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"label\" translatable=\"yes\">Makeup</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">False</property>\n\
                                        <property name=\"fill\">False</property>\n\
                                        <property name=\"position\">0</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GxSmallKnobR\" id=\"gxmediumknob2\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">True</property>\n\
                                        <property name=\"receives_default\">True</property>\n\
                                        <property name=\"var_id\">mbcs.Makeup1</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">1</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">True</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"position\">1</property>\n\
                                  </packing>\n\
                                </child>\n\
                                <child>\n\
                                  <object class=\"GtkVBox\" id=\"vbox6\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <child>\n\
                                      <object class=\"GtkLabel\" id=\"label_3:rack_label\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"label\" translatable=\"yes\">Anticlip</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">False</property>\n\
                                        <property name=\"fill\">False</property>\n\
                                        <property name=\"position\">0</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GxSmallKnobR\" id=\"gxmediumknob3\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">True</property>\n\
                                        <property name=\"receives_default\">True</property>\n\
                                        <property name=\"var_id\">mbcs.Makeup-Threshold1</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">1</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">True</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"position\">2</property>\n\
                                  </packing>\n\
                                </child>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"expand\">True</property>\n\
                                <property name=\"fill\">True</property>\n\
                                <property name=\"position\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSelector\" id=\"gxselector1\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbcs.Mode1</property>\n\
                                <property name=\"value_position\">right</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"expand\">True</property>\n\
                                <property name=\"fill\">True</property>\n\
                                <property name=\"position\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">0</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GtkTable\" id=\"table1\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"n_rows\">2</property>\n\
                            <property name=\"n_columns\">4</property>\n\
                            <property name=\"row_spacing\">4</property>\n\
                            <property name=\"homogeneous\">True</property>\n\
                            <child>\n\
                              <placeholder/>\n\
                            </child>\n\
                            <child>\n\
                              <placeholder/>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob1\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbcs.Attack1</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">1</property>\n\
                                <property name=\"right_attach\">2</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob4\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbcs.crossover_b1_b2</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">3</property>\n\
                                <property name=\"right_attach\">4</property>\n\
                                <property name=\"top_attach\">1</property>\n\
                                <property name=\"bottom_attach\">2</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_4:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"xalign\">1</property>\n\
                                <property name=\"label\" translatable=\"yes\">Att</property>\n\
                              </object>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_7:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"xalign\">1</property>\n\
                                <property name=\"label\" translatable=\"yes\">High</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">2</property>\n\
                                <property name=\"right_attach\">3</property>\n\
                                <property name=\"top_attach\">1</property>\n\
                                <property name=\"bottom_attach\">2</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_5:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"xalign\">1</property>\n\
                                <property name=\"label\" translatable=\"yes\">Rel</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">2</property>\n\
                                <property name=\"right_attach\">3</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob3\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbcs.Release1</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">3</property>\n\
                                <property name=\"right_attach\">4</property>\n\
                              </packing>\n\
                            </child>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">1</property>\n\
                          </packing>\n\
                        </child>\n\
                      </object>\n\
                    </child>\n\
                    <child type=\"tab\">\n\
                      <object class=\"GtkLabel\" id=\"label1\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">Band 1</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"tab_fill\">False</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GtkHBox\" id=\"hbox5\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <child>\n\
                          <object class=\"GtkVBox\" id=\"vbox7\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"spacing\">4</property>\n\
                            <child>\n\
                              <object class=\"GtkHBox\" id=\"hbox6\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <child>\n\
                                  <object class=\"GtkVBox\" id=\"vbox8\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <child>\n\
                                      <object class=\"GtkLabel\" id=\"label_8:rack_label\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"label\" translatable=\"yes\">Ratio</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">False</property>\n\
                                        <property name=\"fill\">False</property>\n\
                                        <property name=\"position\">0</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GxSmallKnobR\" id=\"gxmediumknob4\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">True</property>\n\
                                        <property name=\"receives_default\">True</property>\n\
                                        <property name=\"var_id\">mbcs.Ratio2</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">1</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">True</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"position\">0</property>\n\
                                  </packing>\n\
                                </child>\n\
                                <child>\n\
                                  <object class=\"GtkVBox\" id=\"vbox9\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <child>\n\
                                      <object class=\"GtkLabel\" id=\"label_9:rack_label\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"label\" translatable=\"yes\">Makeup</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">False</property>\n\
                                        <property name=\"fill\">False</property>\n\
                                        <property name=\"position\">0</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GxSmallKnobR\" id=\"gxmediumknob5\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">True</property>\n\
                                        <property name=\"receives_default\">True</property>\n\
                                        <property name=\"var_id\">mbcs.Makeup2</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">1</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">True</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"position\">1</property>\n\
                                  </packing>\n\
                                </child>\n\
                                <child>\n\
                                  <object class=\"GtkVBox\" id=\"vbox10\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <child>\n\
                                      <object class=\"GtkLabel\" id=\"label_10:rack_label\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"label\" translatable=\"yes\">Anticlip</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">False</property>\n\
                                        <property name=\"fill\">False</property>\n\
                                        <property name=\"position\">0</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GxSmallKnobR\" id=\"gxmediumknob6\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">True</property>\n\
                                        <property name=\"receives_default\">True</property>\n\
                                        <property name=\"var_id\">mbcs.Makeup-Threshold2</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">1</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">True</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"position\">2</property>\n\
                                  </packing>\n\
                                </child>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"expand\">True</property>\n\
                                <property name=\"fill\">True</property>\n\
                                <property name=\"position\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSelector\" id=\"gxselector2\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbcs.Mode2</property>\n\
                                <property name=\"value_position\">right</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"expand\">True</property>\n\
                                <property name=\"fill\">True</property>\n\
                                <property name=\"position\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">0</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GtkTable\" id=\"table2\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"n_rows\">2</property>\n\
                            <property name=\"n_columns\">4</property>\n\
                            <property name=\"row_spacing\">4</property>\n\
                            <property name=\"homogeneous\">True</property>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob5\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbcs.Attack2</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">1</property>\n\
                                <property name=\"right_attach\">2</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob6\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbcs.crossover_b2_b3</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">3</property>\n\
                                <property name=\"right_attach\">4</property>\n\
                                <property name=\"top_attach\">1</property>\n\
                                <property name=\"bottom_attach\">2</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_11:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"xalign\">1</property>\n\
                                <property name=\"label\" translatable=\"yes\">Att</property>\n\
                              </object>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_14:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"xalign\">1</property>\n\
                                <property name=\"label\" translatable=\"yes\">High</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">2</property>\n\
                                <property name=\"right_attach\">3</property>\n\
                                <property name=\"top_attach\">1</property>\n\
                                <property name=\"bottom_attach\">2</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_13:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"xalign\">1</property>\n\
                                <property name=\"label\" translatable=\"yes\">Low</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"top_attach\">1</property>\n\
                                <property name=\"bottom_attach\">2</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_12:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"xalign\">1</property>\n\
                                <property name=\"label\" translatable=\"yes\">Rel</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">2</property>\n\
                                <property name=\"right_attach\">3</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob7\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbcs.crossover_b1_b2</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">1</property>\n\
                                <property name=\"right_attach\">2</property>\n\
                                <property name=\"top_attach\">1</property>\n\
                                <property name=\"bottom_attach\">2</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob8\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbcs.Release2</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">3</property>\n\
                                <property name=\"right_attach\">4</property>\n\
                              </packing>\n\
                            </child>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">1</property>\n\
                          </packing>\n\
                        </child>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child type=\"tab\">\n\
                      <object class=\"GtkLabel\" id=\"label2\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">Band 2</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"position\">1</property>\n\
                        <property name=\"tab_fill\">False</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GtkHBox\" id=\"hbox7\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <child>\n\
                          <object class=\"GtkVBox\" id=\"vbox11\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"spacing\">4</property>\n\
                            <child>\n\
                              <object class=\"GtkHBox\" id=\"hbox8\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <child>\n\
                                  <object class=\"GtkVBox\" id=\"vbox12\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <child>\n\
                                      <object class=\"GtkLabel\" id=\"label_15:rack_label\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"label\" translatable=\"yes\">Ratio</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">False</property>\n\
                                        <property name=\"fill\">False</property>\n\
                                        <property name=\"position\">0</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GxSmallKnobR\" id=\"gxmediumknob7\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">True</property>\n\
                                        <property name=\"receives_default\">True</property>\n\
                                        <property name=\"var_id\">mbcs.Ratio3</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">1</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">True</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"position\">0</property>\n\
                                  </packing>\n\
                                </child>\n\
                                <child>\n\
                                  <object class=\"GtkVBox\" id=\"vbox13\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <child>\n\
                                      <object class=\"GtkLabel\" id=\"label_16:rack_label\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"label\" translatable=\"yes\">Makeup</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">False</property>\n\
                                        <property name=\"fill\">False</property>\n\
                                        <property name=\"position\">0</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GxSmallKnobR\" id=\"gxmediumknob8\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">True</property>\n\
                                        <property name=\"receives_default\">True</property>\n\
                                        <property name=\"var_id\">mbcs.Makeup3</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">1</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">True</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"position\">1</property>\n\
                                  </packing>\n\
                                </child>\n\
                                <child>\n\
                                  <object class=\"GtkVBox\" id=\"vbox14\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <child>\n\
                                      <object class=\"GtkLabel\" id=\"label_17:rack_label\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"label\" translatable=\"yes\">Anticlip</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">False</property>\n\
                                        <property name=\"fill\">False</property>\n\
                                        <property name=\"position\">0</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GxSmallKnobR\" id=\"gxmediumknob9\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">True</property>\n\
                                        <property name=\"receives_default\">True</property>\n\
                                        <property name=\"var_id\">mbcs.Makeup-Threshold3</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">1</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">True</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"position\">2</property>\n\
                                  </packing>\n\
                                </child>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"expand\">True</property>\n\
                                <property name=\"fill\">True</property>\n\
                                <property name=\"position\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSelector\" id=\"gxselector3\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbcs.Mode3</property>\n\
                                <property name=\"value_position\">right</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"expand\">True</property>\n\
                                <property name=\"fill\">True</property>\n\
                                <property name=\"position\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">0</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GtkTable\" id=\"table3\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"n_rows\">2</property>\n\
                            <property name=\"n_columns\">4</property>\n\
                            <property name=\"row_spacing\">4</property>\n\
                            <property name=\"homogeneous\">True</property>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob9\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbcs.Attack3</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">1</property>\n\
                                <property name=\"right_attach\">2</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob10\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbcs.crossover_b3_b4</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">3</property>\n\
                                <property name=\"right_attach\">4</property>\n\
                                <property name=\"top_attach\">1</property>\n\
                                <property name=\"bottom_attach\">2</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_18:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"xalign\">1</property>\n\
                                <property name=\"label\" translatable=\"yes\">Att</property>\n\
                              </object>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_21:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"xalign\">1</property>\n\
                                <property name=\"label\" translatable=\"yes\">High</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">2</property>\n\
                                <property name=\"right_attach\">3</property>\n\
                                <property name=\"top_attach\">1</property>\n\
                                <property name=\"bottom_attach\">2</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_20:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"xalign\">1</property>\n\
                                <property name=\"label\" translatable=\"yes\">Low</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"top_attach\">1</property>\n\
                                <property name=\"bottom_attach\">2</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_19:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"xalign\">1</property>\n\
                                <property name=\"label\" translatable=\"yes\">Rel</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">2</property>\n\
                                <property name=\"right_attach\">3</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob11\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbcs.crossover_b2_b3</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">1</property>\n\
                                <property name=\"right_attach\">2</property>\n\
                                <property name=\"top_attach\">1</property>\n\
                                <property name=\"bottom_attach\">2</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob12\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbcs.Release3</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">3</property>\n\
                                <property name=\"right_attach\">4</property>\n\
                              </packing>\n\
                            </child>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">1</property>\n\
                          </packing>\n\
                        </child>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"position\">2</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child type=\"tab\">\n\
                      <object class=\"GtkLabel\" id=\"label3\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">Band 3</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"position\">2</property>\n\
                        <property name=\"tab_fill\">False</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GtkHBox\" id=\"hbox9\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <child>\n\
                          <object class=\"GtkVBox\" id=\"vbox15\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"spacing\">4</property>\n\
                            <child>\n\
                              <object class=\"GtkHBox\" id=\"hbox10\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <child>\n\
                                  <object class=\"GtkVBox\" id=\"vbox16\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <child>\n\
                                      <object class=\"GtkLabel\" id=\"label_22:rack_label\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"label\" translatable=\"yes\">Ratio</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">False</property>\n\
                                        <property name=\"fill\">False</property>\n\
                                        <property name=\"position\">0</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GxSmallKnobR\" id=\"gxmediumknob10\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">True</property>\n\
                                        <property name=\"receives_default\">True</property>\n\
                                        <property name=\"var_id\">mbcs.Ratio4</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">1</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">True</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"position\">0</property>\n\
                                  </packing>\n\
                                </child>\n\
                                <child>\n\
                                  <object class=\"GtkVBox\" id=\"vbox17\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <child>\n\
                                      <object class=\"GtkLabel\" id=\"label_23:rack_label\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"label\" translatable=\"yes\">Makeup</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">False</property>\n\
                                        <property name=\"fill\">False</property>\n\
                                        <property name=\"position\">0</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GxSmallKnobR\" id=\"gxmediumknob11\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">True</property>\n\
                                        <property name=\"receives_default\">True</property>\n\
                                        <property name=\"var_id\">mbcs.Makeup4</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">1</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">True</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"position\">1</property>\n\
                                  </packing>\n\
                                </child>\n\
                                <child>\n\
                                  <object class=\"GtkVBox\" id=\"vbox18\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <child>\n\
                                      <object class=\"GtkLabel\" id=\"label_24:rack_label\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"label\" translatable=\"yes\">Anticlip</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">False</property>\n\
                                        <property name=\"fill\">False</property>\n\
                                        <property name=\"position\">0</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GxSmallKnobR\" id=\"gxmediumknob12\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">True</property>\n\
                                        <property name=\"receives_default\">True</property>\n\
                                        <property name=\"var_id\">mbcs.Makeup-Threshold4</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">1</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">True</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"position\">2</property>\n\
                                  </packing>\n\
                                </child>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"expand\">True</property>\n\
                                <property name=\"fill\">True</property>\n\
                                <property name=\"position\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSelector\" id=\"gxselector4\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbcs.Mode4</property>\n\
                                <property name=\"value_position\">right</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"expand\">True</property>\n\
                                <property name=\"fill\">True</property>\n\
                                <property name=\"position\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">0</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GtkTable\" id=\"table4\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"n_rows\">2</property>\n\
                            <property name=\"n_columns\">4</property>\n\
                            <property name=\"row_spacing\">4</property>\n\
                            <property name=\"homogeneous\">True</property>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob13\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbcs.Attack4</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">1</property>\n\
                                <property name=\"right_attach\">2</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob14\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbcs.crossover_b4_b5</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">3</property>\n\
                                <property name=\"right_attach\">4</property>\n\
                                <property name=\"top_attach\">1</property>\n\
                                <property name=\"bottom_attach\">2</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_25:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"xalign\">1</property>\n\
                                <property name=\"label\" translatable=\"yes\">Att</property>\n\
                              </object>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_28:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"xalign\">1</property>\n\
                                <property name=\"label\" translatable=\"yes\">High</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">2</property>\n\
                                <property name=\"right_attach\">3</property>\n\
                                <property name=\"top_attach\">1</property>\n\
                                <property name=\"bottom_attach\">2</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_27:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"xalign\">1</property>\n\
                                <property name=\"label\" translatable=\"yes\">Low</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"top_attach\">1</property>\n\
                                <property name=\"bottom_attach\">2</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_26:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"xalign\">1</property>\n\
                                <property name=\"label\" translatable=\"yes\">Rel</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">2</property>\n\
                                <property name=\"right_attach\">3</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob15\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbcs.crossover_b3_b4</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">1</property>\n\
                                <property name=\"right_attach\">2</property>\n\
                                <property name=\"top_attach\">1</property>\n\
                                <property name=\"bottom_attach\">2</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob16\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbcs.Release4</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">3</property>\n\
                                <property name=\"right_attach\">4</property>\n\
                              </packing>\n\
                            </child>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">1</property>\n\
                          </packing>\n\
                        </child>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"position\">3</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child type=\"tab\">\n\
                      <object class=\"GtkLabel\" id=\"label4\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">Band 4</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"position\">3</property>\n\
                        <property name=\"tab_fill\">False</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GtkHBox\" id=\"hbox11\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <child>\n\
                          <object class=\"GtkVBox\" id=\"vbox19\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"spacing\">4</property>\n\
                            <child>\n\
                              <object class=\"GtkHBox\" id=\"hbox12\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <child>\n\
                                  <object class=\"GtkVBox\" id=\"vbox20\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <child>\n\
                                      <object class=\"GtkLabel\" id=\"label_29:rack_label\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"label\" translatable=\"yes\">Ratio</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">False</property>\n\
                                        <property name=\"fill\">False</property>\n\
                                        <property name=\"position\">0</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GxSmallKnobR\" id=\"gxmediumknob13\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">True</property>\n\
                                        <property name=\"receives_default\">True</property>\n\
                                        <property name=\"var_id\">mbcs.Ratio5</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">1</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">True</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"position\">0</property>\n\
                                  </packing>\n\
                                </child>\n\
                                <child>\n\
                                  <object class=\"GtkVBox\" id=\"vbox21\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <child>\n\
                                      <object class=\"GtkLabel\" id=\"label_30:rack_label\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"label\" translatable=\"yes\">Makeup</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">False</property>\n\
                                        <property name=\"fill\">False</property>\n\
                                        <property name=\"position\">0</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GxSmallKnobR\" id=\"gxmediumknob14\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">True</property>\n\
                                        <property name=\"receives_default\">True</property>\n\
                                        <property name=\"var_id\">mbcs.Makeup5</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">1</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">True</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"position\">1</property>\n\
                                  </packing>\n\
                                </child>\n\
                                <child>\n\
                                  <object class=\"GtkVBox\" id=\"vbox22\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <child>\n\
                                      <object class=\"GtkLabel\" id=\"label_31:rack_label\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"label\" translatable=\"yes\">Anticlip</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">False</property>\n\
                                        <property name=\"fill\">False</property>\n\
                                        <property name=\"position\">0</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GxSmallKnobR\" id=\"gxmediumknob15\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">True</property>\n\
                                        <property name=\"receives_default\">True</property>\n\
                                        <property name=\"var_id\">mbcs.Makeup-Threshold5</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">1</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">True</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"position\">2</property>\n\
                                  </packing>\n\
                                </child>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"expand\">True</property>\n\
                                <property name=\"fill\">True</property>\n\
                                <property name=\"position\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSelector\" id=\"gxselector5\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbcs.Mode5</property>\n\
                                <property name=\"value_position\">right</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"expand\">True</property>\n\
                                <property name=\"fill\">True</property>\n\
                                <property name=\"position\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">0</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GtkTable\" id=\"table5\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"n_rows\">2</property>\n\
                            <property name=\"n_columns\">4</property>\n\
                            <property name=\"row_spacing\">4</property>\n\
                            <property name=\"homogeneous\">True</property>\n\
                            <child>\n\
                              <placeholder/>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob17\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbcs.Attack5</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">1</property>\n\
                                <property name=\"right_attach\">2</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_32:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"xalign\">1</property>\n\
                                <property name=\"label\" translatable=\"yes\">Att</property>\n\
                              </object>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_34:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"xalign\">1</property>\n\
                                <property name=\"label\" translatable=\"yes\">Low</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"top_attach\">1</property>\n\
                                <property name=\"bottom_attach\">2</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_33:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"xalign\">1</property>\n\
                                <property name=\"label\" translatable=\"yes\">Rel</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">2</property>\n\
                                <property name=\"right_attach\">3</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob19\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbcs.crossover_b4_b5</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">1</property>\n\
                                <property name=\"right_attach\">2</property>\n\
                                <property name=\"top_attach\">1</property>\n\
                                <property name=\"bottom_attach\">2</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob20\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbcs.Release5</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">3</property>\n\
                                <property name=\"right_attach\">4</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_35:rack_label\">\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"xalign\">1</property>\n\
                                <property name=\"label\" translatable=\"yes\">High</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">2</property>\n\
                                <property name=\"right_attach\">3</property>\n\
                                <property name=\"top_attach\">1</property>\n\
                                <property name=\"bottom_attach\">2</property>\n\
                              </packing>\n\
                            </child>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">1</property>\n\
                          </packing>\n\
                        </child>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"position\">4</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child type=\"tab\">\n\
                      <object class=\"GtkLabel\" id=\"label6\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">Band 5</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"position\">4</property>\n\
                        <property name=\"tab_fill\">False</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">True</property>\n\
                    <property name=\"fill\">True</property>\n\
                    <property name=\"position\">0</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkVBox\" id=\"vbox2\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label5:rack_label\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"xalign\">0</property>\n\
                        <property name=\"label\" translatable=\"yes\">Levels</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GtkHBox\" id=\"hbox3\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <child>\n\
                          <object class=\"GxFastMeter\" id=\"gxfastmeter1\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"tooltip_text\" translatable=\"yes\">Sum of Band1 </property>\n\
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">mbcs.v1</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">0</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GxFastMeter\" id=\"gxfastmeter2\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"tooltip_text\" translatable=\"yes\">Sum of Band2</property>\n\
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">mbcs.v2</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">1</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GxFastMeter\" id=\"gxfastmeter3\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"tooltip_text\" translatable=\"yes\">Sum of Band3</property>\n\
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">mbcs.v3</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">2</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GxFastMeter\" id=\"gxfastmeter4\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"tooltip_text\" translatable=\"yes\">Sum of Band4</property>\n\
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">mbcs.v4</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">3</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GxFastMeter\" id=\"gxfastmeter5\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"tooltip_text\" translatable=\"yes\">Sum of Band5</property>\n\
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">mbcs.v5</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">4</property>\n\
                          </packing>\n\
                        </child>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">True</property>\n\
                        <property name=\"fill\">True</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">True</property>\n\
                    <property name=\"fill\">True</property>\n\
                    <property name=\"position\">1</property>\n\
                  </packing>\n\
                </child>\n\
              </object>\n\
              <packing>\n\
                <property name=\"expand\">True</property>\n\
                <property name=\"fill\">True</property>\n\
                <property name=\"position\">0</property>\n\
              </packing>\n\
            </child>\n\
          </object>\n\
          <packing>\n\
            <property name=\"expand\">True</property>\n\
            <property name=\"fill\">True</property>\n\
            <property name=\"position\">0</property>\n\
          </packing>\n\
        </child>\n\
        <child>\n\
          <object class=\"GtkHBox\" id=\"minibox\">\n\
            <property name=\"visible\">True</property>\n\
            <property name=\"can_focus\">False</property>\n\
            <property name=\"spacing\">4</property>\n\
            <child>\n\
              <placeholder/>\n\
            </child>\n\
          </object>\n\
          <packing>\n\
            <property name=\"expand\">True</property>\n\
            <property name=\"fill\">True</property>\n\
            <property name=\"position\">1</property>\n\
          </packing>\n\
        </child>\n\
      </object>\n\
    </child>\n\
  </object>\n\
</interface>\n\
";

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_GLADE) {
        b.load_glade(glade_def);
        return 0;
    }
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
