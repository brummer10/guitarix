// generated from file '../src/plugins/mbc.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

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
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT 	fslider3;
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
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT 	fslider5;
	double 	fRec6[2];
	FAUSTFLOAT 	fslider6;
	double 	fRec5[2];
	FAUSTFLOAT 	fslider7;
	double 	fConst3;
	FAUSTFLOAT 	fslider8;
	double 	fRec4[2];
	FAUSTFLOAT 	fslider9;
	double 	fRec15[2];
	double 	fRec0[2];
	int 	iRec1[2];
	double 	fRec2[2];
	FAUSTFLOAT 	fbargraph0;
	double 	fRec24[2];
	double 	fRec23[3];
	FAUSTFLOAT 	fslider10;
	FAUSTFLOAT 	fslider11;
	double 	fRec22[2];
	FAUSTFLOAT 	fslider12;
	double 	fRec21[2];
	FAUSTFLOAT 	fslider13;
	FAUSTFLOAT 	fslider14;
	double 	fRec20[2];
	FAUSTFLOAT 	fslider15;
	double 	fRec25[2];
	double 	fRec16[2];
	int 	iRec17[2];
	double 	fRec18[2];
	FAUSTFLOAT 	fbargraph1;
	double 	fRec35[2];
	double 	fRec34[3];
	double 	fRec33[3];
	FAUSTFLOAT 	fslider16;
	FAUSTFLOAT 	fslider17;
	double 	fRec32[2];
	FAUSTFLOAT 	fslider18;
	double 	fRec31[2];
	FAUSTFLOAT 	fslider19;
	FAUSTFLOAT 	fslider20;
	double 	fRec30[2];
	FAUSTFLOAT 	fslider21;
	double 	fRec36[2];
	double 	fRec26[2];
	int 	iRec27[2];
	double 	fRec28[2];
	FAUSTFLOAT 	fbargraph2;
	double 	fRec47[2];
	double 	fRec46[3];
	double 	fRec45[3];
	double 	fRec44[3];
	FAUSTFLOAT 	fslider22;
	FAUSTFLOAT 	fslider23;
	double 	fRec43[2];
	FAUSTFLOAT 	fslider24;
	double 	fRec42[2];
	FAUSTFLOAT 	fslider25;
	FAUSTFLOAT 	fslider26;
	double 	fRec41[2];
	FAUSTFLOAT 	fslider27;
	double 	fRec48[2];
	double 	fRec37[2];
	int 	iRec38[2];
	double 	fRec39[2];
	FAUSTFLOAT 	fbargraph3;
	double 	fRec60[2];
	double 	fRec59[3];
	double 	fRec58[3];
	double 	fRec57[3];
	double 	fRec56[3];
	FAUSTFLOAT 	fslider28;
	FAUSTFLOAT 	fslider29;
	double 	fRec55[2];
	FAUSTFLOAT 	fslider30;
	double 	fRec54[2];
	FAUSTFLOAT 	fslider31;
	FAUSTFLOAT 	fslider32;
	double 	fRec53[2];
	FAUSTFLOAT 	fslider33;
	double 	fRec61[2];
	double 	fRec49[2];
	int 	iRec50[2];
	double 	fRec51[2];
	FAUSTFLOAT 	fbargraph4;
	void clear_state_f();
	int load_ui_f(const UiBuilder& b, int form);
	void init(unsigned int samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static int load_ui_f_static(const UiBuilder& b, int form);
	static void init_static(unsigned int samplingFreq, PluginDef*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef*);
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
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) iRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<3; i++) fRec23[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec25[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) iRec17[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fRec35[i] = 0;
	for (int i=0; i<3; i++) fRec34[i] = 0;
	for (int i=0; i<3; i++) fRec33[i] = 0;
	for (int i=0; i<2; i++) fRec32[i] = 0;
	for (int i=0; i<2; i++) fRec31[i] = 0;
	for (int i=0; i<2; i++) fRec30[i] = 0;
	for (int i=0; i<2; i++) fRec36[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<2; i++) iRec27[i] = 0;
	for (int i=0; i<2; i++) fRec28[i] = 0;
	for (int i=0; i<2; i++) fRec47[i] = 0;
	for (int i=0; i<3; i++) fRec46[i] = 0;
	for (int i=0; i<3; i++) fRec45[i] = 0;
	for (int i=0; i<3; i++) fRec44[i] = 0;
	for (int i=0; i<2; i++) fRec43[i] = 0;
	for (int i=0; i<2; i++) fRec42[i] = 0;
	for (int i=0; i<2; i++) fRec41[i] = 0;
	for (int i=0; i<2; i++) fRec48[i] = 0;
	for (int i=0; i<2; i++) fRec37[i] = 0;
	for (int i=0; i<2; i++) iRec38[i] = 0;
	for (int i=0; i<2; i++) fRec39[i] = 0;
	for (int i=0; i<2; i++) fRec60[i] = 0;
	for (int i=0; i<3; i++) fRec59[i] = 0;
	for (int i=0; i<3; i++) fRec58[i] = 0;
	for (int i=0; i<3; i++) fRec57[i] = 0;
	for (int i=0; i<3; i++) fRec56[i] = 0;
	for (int i=0; i<2; i++) fRec55[i] = 0;
	for (int i=0; i<2; i++) fRec54[i] = 0;
	for (int i=0; i<2; i++) fRec53[i] = 0;
	for (int i=0; i<2; i++) fRec61[i] = 0;
	for (int i=0; i<2; i++) fRec49[i] = 0;
	for (int i=0; i<2; i++) iRec50[i] = 0;
	for (int i=0; i<2; i++) fRec51[i] = 0;
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

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
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
		fRec14[0] = ((fSlow29 * fRec14[1]) + (fSlow28 * (fVec0[0] + fVec0[1])));
		fRec13[0] = (fRec14[0] - (fSlow26 * ((fSlow24 * fRec13[2]) + (fSlow22 * fRec13[1]))));
		double fTemp1 = (fRec13[2] + (fRec13[0] + (2 * fRec13[1])));
		double fTemp2 = (fSlow26 * fTemp1);
		fVec1[0] = fTemp2;
		fRec12[0] = ((fSlow32 * fRec12[1]) + (fSlow31 * (fVec1[0] + fVec1[1])));
		fRec11[0] = (fRec12[0] - (fSlow19 * ((fSlow17 * fRec11[2]) + (fSlow15 * fRec11[1]))));
		double fTemp3 = (fRec11[2] + (fRec11[0] + (2 * fRec11[1])));
		double fTemp4 = (fSlow19 * fTemp3);
		fVec2[0] = fTemp4;
		fRec10[0] = ((fSlow35 * fRec10[1]) + (fSlow34 * (fVec2[0] + fVec2[1])));
		fRec9[0] = (fRec10[0] - (fSlow12 * ((fSlow10 * fRec9[2]) + (fSlow8 * fRec9[1]))));
		double fTemp5 = (fRec9[2] + (fRec9[0] + (2 * fRec9[1])));
		double fTemp6 = (fSlow12 * fTemp5);
		fVec3[0] = fTemp6;
		fRec8[0] = ((fSlow38 * fRec8[1]) + (fSlow37 * (fVec3[0] + fVec3[1])));
		fRec7[0] = (fRec8[0] - (fSlow5 * ((fSlow4 * fRec7[2]) + (fSlow2 * fRec7[1]))));
		double fTemp7 = (fSlow5 * (fRec7[2] + (fRec7[0] + (2 * fRec7[1]))));
		double fTemp8 = ((iSlow41)?0:fTemp7);
		double fTemp9 = fabs(fTemp8);
		fRec6[0] = ((fSlow42 * max(fTemp9, fRec6[1])) + (fSlow43 * fTemp9));
		fRec5[0] = ((fSlow45 * fRec5[1]) + (fSlow46 * fRec6[0]));
		fRec4[0] = ((fSlow48 * fRec4[1]) + (fSlow49 * max((fSlow47 + (20 * log10(fRec5[0]))), 0.0)));
		fRec15[0] = ((0.999 * fRec15[1]) + fSlow50);
		double fTemp10 = (fSlow51 * (fRec15[0] * ((iSlow41)?fTemp7:(fTemp8 * pow(10,(0.05 * fRec4[0]))))));
		double 	fRec3 = max(fConst1, fabs(fTemp10));
		int iTemp11 = int((iRec1[1] < 4096));
		fRec0[0] = ((iTemp11)?max(fRec0[1], fRec3):fRec3);
		iRec1[0] = ((iTemp11)?(1 + iRec1[1]):1);
		fRec2[0] = ((iTemp11)?fRec2[1]:fRec0[1]);
		fbargraph0 = fRec2[0];
		fRec24[0] = ((fSlow38 * fRec24[1]) + (fSlow37 * ((fSlow53 * fTemp5) + (fSlow52 * fVec3[1]))));
		fRec23[0] = (fRec24[0] - (fSlow5 * ((fSlow4 * fRec23[2]) + (fSlow2 * fRec23[1]))));
		double fTemp12 = (fSlow5 * (((fSlow1 * fRec23[0]) + (fSlow54 * fRec23[1])) + (fSlow1 * fRec23[2])));
		double fTemp13 = ((iSlow57)?0:fTemp12);
		double fTemp14 = fabs(fTemp13);
		fRec22[0] = ((fSlow58 * max(fTemp14, fRec22[1])) + (fSlow59 * fTemp14));
		fRec21[0] = ((fSlow61 * fRec21[1]) + (fSlow62 * fRec22[0]));
		fRec20[0] = ((fSlow64 * fRec20[1]) + (fSlow65 * max((fSlow63 + (20 * log10(fRec21[0]))), 0.0)));
		fRec25[0] = ((0.999 * fRec25[1]) + fSlow66);
		double fTemp15 = (fSlow67 * (fRec25[0] * ((iSlow57)?fTemp12:(fTemp13 * pow(10,(0.05 * fRec20[0]))))));
		double 	fRec19 = max(fConst1, fabs(fTemp15));
		int iTemp16 = int((iRec17[1] < 4096));
		fRec16[0] = ((iTemp16)?max(fRec16[1], fRec19):fRec19);
		iRec17[0] = ((iTemp16)?(1 + iRec17[1]):1);
		fRec18[0] = ((iTemp16)?fRec18[1]:fRec16[1]);
		fbargraph1 = fRec18[0];
		double fTemp17 = (fSlow2 * fRec33[1]);
		fRec35[0] = ((fSlow35 * fRec35[1]) + (fSlow34 * ((fSlow71 * fTemp3) + (fSlow70 * fVec2[1]))));
		fRec34[0] = (fRec35[0] - (fSlow12 * ((fSlow10 * fRec34[2]) + (fSlow8 * fRec34[1]))));
		fRec33[0] = ((fSlow12 * (((fSlow7 * fRec34[0]) + (fSlow72 * fRec34[1])) + (fSlow7 * fRec34[2]))) - (fSlow69 * ((fSlow68 * fRec33[2]) + fTemp17)));
		double fTemp18 = (fRec33[2] + (fSlow69 * (fTemp17 + (fSlow68 * fRec33[0]))));
		double fTemp19 = ((iSlow75)?0:fTemp18);
		double fTemp20 = fabs(fTemp19);
		fRec32[0] = ((fSlow76 * max(fTemp20, fRec32[1])) + (fSlow77 * fTemp20));
		fRec31[0] = ((fSlow79 * fRec31[1]) + (fSlow80 * fRec32[0]));
		fRec30[0] = ((fSlow82 * fRec30[1]) + (fSlow83 * max((fSlow81 + (20 * log10(fRec31[0]))), 0.0)));
		fRec36[0] = ((0.999 * fRec36[1]) + fSlow84);
		double fTemp21 = (fSlow85 * (fRec36[0] * ((iSlow75)?fTemp18:(fTemp19 * pow(10,(0.05 * fRec30[0]))))));
		double 	fRec29 = max(fConst1, fabs(fTemp21));
		int iTemp22 = int((iRec27[1] < 4096));
		fRec26[0] = ((iTemp22)?max(fRec26[1], fRec29):fRec29);
		iRec27[0] = ((iTemp22)?(1 + iRec27[1]):1);
		fRec28[0] = ((iTemp22)?fRec28[1]:fRec26[1]);
		fbargraph2 = fRec28[0];
		double fTemp23 = (fSlow2 * fRec44[1]);
		double fTemp24 = (fSlow8 * fRec45[1]);
		fRec47[0] = ((fSlow32 * fRec47[1]) + (fSlow31 * ((fSlow89 * fTemp1) + (fSlow88 * fVec1[1]))));
		fRec46[0] = (fRec47[0] - (fSlow19 * ((fSlow17 * fRec46[2]) + (fSlow15 * fRec46[1]))));
		fRec45[0] = ((fSlow19 * (((fSlow14 * fRec46[0]) + (fSlow90 * fRec46[1])) + (fSlow14 * fRec46[2]))) - (fSlow87 * ((fSlow86 * fRec45[2]) + fTemp24)));
		fRec44[0] = ((fRec45[2] + (fSlow87 * (fTemp24 + (fSlow86 * fRec45[0])))) - (fSlow69 * ((fSlow68 * fRec44[2]) + fTemp23)));
		double fTemp25 = (fRec44[2] + (fSlow69 * (fTemp23 + (fSlow68 * fRec44[0]))));
		double fTemp26 = ((iSlow93)?0:fTemp25);
		double fTemp27 = fabs(fTemp26);
		fRec43[0] = ((fSlow94 * max(fTemp27, fRec43[1])) + (fSlow95 * fTemp27));
		fRec42[0] = ((fSlow97 * fRec42[1]) + (fSlow98 * fRec43[0]));
		fRec41[0] = ((fSlow100 * fRec41[1]) + (fSlow101 * max((fSlow99 + (20 * log10(fRec42[0]))), 0.0)));
		fRec48[0] = ((0.999 * fRec48[1]) + fSlow102);
		double fTemp28 = (fSlow103 * (fRec48[0] * ((iSlow93)?fTemp25:(fTemp26 * pow(10,(0.05 * fRec41[0]))))));
		double 	fRec40 = max(fConst1, fabs(fTemp28));
		int iTemp29 = int((iRec38[1] < 4096));
		fRec37[0] = ((iTemp29)?max(fRec37[1], fRec40):fRec40);
		iRec38[0] = ((iTemp29)?(1 + iRec38[1]):1);
		fRec39[0] = ((iTemp29)?fRec39[1]:fRec37[1]);
		fbargraph3 = fRec39[0];
		double fTemp30 = (fSlow2 * fRec56[1]);
		double fTemp31 = (fSlow8 * fRec57[1]);
		double fTemp32 = (fSlow15 * fRec58[1]);
		fRec60[0] = ((fSlow29 * fRec60[1]) + (fSlow28 * ((fSlow23 * fVec0[0]) + (fSlow106 * fVec0[1]))));
		fRec59[0] = (fRec60[0] - (fSlow26 * ((fSlow24 * fRec59[2]) + (fSlow22 * fRec59[1]))));
		fRec58[0] = ((fSlow26 * (((fSlow21 * fRec59[0]) + (fSlow107 * fRec59[1])) + (fSlow21 * fRec59[2]))) - (fSlow105 * ((fSlow104 * fRec58[2]) + fTemp32)));
		fRec57[0] = ((fRec58[2] + (fSlow105 * (fTemp32 + (fSlow104 * fRec58[0])))) - (fSlow87 * ((fSlow86 * fRec57[2]) + fTemp31)));
		fRec56[0] = ((fRec57[2] + (fSlow87 * (fTemp31 + (fSlow86 * fRec57[0])))) - (fSlow69 * ((fSlow68 * fRec56[2]) + fTemp30)));
		double fTemp33 = (fRec56[2] + (fSlow69 * (fTemp30 + (fSlow68 * fRec56[0]))));
		double fTemp34 = ((iSlow110)?0:fTemp33);
		double fTemp35 = fabs(fTemp34);
		fRec55[0] = ((fSlow111 * max(fTemp35, fRec55[1])) + (fSlow112 * fTemp35));
		fRec54[0] = ((fSlow114 * fRec54[1]) + (fSlow115 * fRec55[0]));
		fRec53[0] = ((fSlow117 * fRec53[1]) + (fSlow118 * max((fSlow116 + (20 * log10(fRec54[0]))), 0.0)));
		fRec61[0] = ((0.999 * fRec61[1]) + fSlow119);
		double fTemp36 = (fSlow120 * (fRec61[0] * ((iSlow110)?fTemp33:(fTemp34 * pow(10,(0.05 * fRec53[0]))))));
		double 	fRec52 = max(fConst1, fabs(fTemp36));
		int iTemp37 = int((iRec50[1] < 4096));
		fRec49[0] = ((iTemp37)?max(fRec49[1], fRec52):fRec52);
		iRec50[0] = ((iTemp37)?(1 + iRec50[1]):1);
		fRec51[0] = ((iTemp37)?fRec51[1]:fRec49[1]);
		fbargraph4 = fRec51[0];
		output0[i] = (FAUSTFLOAT)((((fTemp36 + fTemp28) + fTemp21) + fTemp15) + fTemp10);
		// post processing
		fRec51[1] = fRec51[0];
		iRec50[1] = iRec50[0];
		fRec49[1] = fRec49[0];
		fRec61[1] = fRec61[0];
		fRec53[1] = fRec53[0];
		fRec54[1] = fRec54[0];
		fRec55[1] = fRec55[0];
		fRec56[2] = fRec56[1]; fRec56[1] = fRec56[0];
		fRec57[2] = fRec57[1]; fRec57[1] = fRec57[0];
		fRec58[2] = fRec58[1]; fRec58[1] = fRec58[0];
		fRec59[2] = fRec59[1]; fRec59[1] = fRec59[0];
		fRec60[1] = fRec60[0];
		fRec39[1] = fRec39[0];
		iRec38[1] = iRec38[0];
		fRec37[1] = fRec37[0];
		fRec48[1] = fRec48[0];
		fRec41[1] = fRec41[0];
		fRec42[1] = fRec42[0];
		fRec43[1] = fRec43[0];
		fRec44[2] = fRec44[1]; fRec44[1] = fRec44[0];
		fRec45[2] = fRec45[1]; fRec45[1] = fRec45[0];
		fRec46[2] = fRec46[1]; fRec46[1] = fRec46[0];
		fRec47[1] = fRec47[0];
		fRec28[1] = fRec28[0];
		iRec27[1] = iRec27[0];
		fRec26[1] = fRec26[0];
		fRec36[1] = fRec36[0];
		fRec30[1] = fRec30[0];
		fRec31[1] = fRec31[0];
		fRec32[1] = fRec32[0];
		fRec33[2] = fRec33[1]; fRec33[1] = fRec33[0];
		fRec34[2] = fRec34[1]; fRec34[1] = fRec34[0];
		fRec35[1] = fRec35[0];
		fRec18[1] = fRec18[0];
		iRec17[1] = iRec17[0];
		fRec16[1] = fRec16[0];
		fRec25[1] = fRec25[0];
		fRec20[1] = fRec20[0];
		fRec21[1] = fRec21[0];
		fRec22[1] = fRec22[0];
		fRec23[2] = fRec23[1]; fRec23[1] = fRec23[0];
		fRec24[1] = fRec24[0];
		fRec2[1] = fRec2[0];
		iRec1[1] = iRec1[0];
		fRec0[1] = fRec0[0];
		fRec15[1] = fRec15[0];
		fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
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

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	static const value_pair fslider4_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	reg.registerEnumVar("mbc.Mode1","","S",N_("Compress or Mute the selected band, or Bypass The Compressor"),fslider4_values,&fslider4, 1.0, 1.0, 3.0, 1.0);
	static const value_pair fslider10_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	reg.registerEnumVar("mbc.Mode2","","S",N_("Compress or Mute the selected band, or Bypass The Compressor"),fslider10_values,&fslider10, 1.0, 1.0, 3.0, 1.0);
	static const value_pair fslider16_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	reg.registerEnumVar("mbc.Mode3","","S",N_("Compress or Mute the selected band, or Bypass The Compressor"),fslider16_values,&fslider16, 1.0, 1.0, 3.0, 1.0);
	static const value_pair fslider22_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	reg.registerEnumVar("mbc.Mode4","","S",N_("Compress or Mute the selected band, or Bypass The Compressor"),fslider22_values,&fslider22, 1.0, 1.0, 3.0, 1.0);
	static const value_pair fslider28_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	reg.registerEnumVar("mbc.Mode5","","S",N_("Compress or Mute the selected band, or Bypass The Compressor"),fslider28_values,&fslider28, 1.0, 1.0, 3.0, 1.0);
	reg.registerVar("mbc.Makeup1","","S",N_("Post amplification and threshold"),&fslider7, 13.0, -5e+01, 5e+01, 0.1);
	reg.registerVar("mbc.Makeup2","","S",N_("Post amplification and threshold"),&fslider13, 1e+01, -5e+01, 5e+01, 0.1);
	reg.registerVar("mbc.Makeup3","","S",N_("Post amplification and threshold"),&fslider19, 4.0, -5e+01, 5e+01, 0.1);
	reg.registerVar("mbc.Makeup4","","S",N_("Post amplification and threshold"),&fslider25, 8.0, -5e+01, 5e+01, 0.1);
	reg.registerVar("mbc.Makeup5","","S",N_("Post amplification and threshold"),&fslider31, 11.0, -5e+01, 5e+01, 0.1);
	reg.registerVar("mbc.Makeup-Threshold1","","S",N_("Threshold correction, an anticlip measure"),&fslider9, 2.0, 0.0, 1e+01, 0.1);
	reg.registerVar("mbc.Makeup-Threshold2","","S",N_("Threshold correction, an anticlip measure"),&fslider15, 2.0, 0.0, 1e+01, 0.1);
	reg.registerVar("mbc.Makeup-Threshold3","","S",N_("Threshold correction, an anticlip measure"),&fslider21, 2.0, 0.0, 1e+01, 0.1);
	reg.registerVar("mbc.Makeup-Threshold4","","S",N_("Threshold correction, an anticlip measure"),&fslider27, 2.0, 0.0, 1e+01, 0.1);
	reg.registerVar("mbc.Makeup-Threshold5","","S",N_("Threshold correction, an anticlip measure"),&fslider33, 2.0, 0.0, 1e+01, 0.1);
	reg.registerVar("mbc.Ratio1","","S",N_("Compression ratio"),&fslider8, 2.0, 1.0, 1e+02, 0.1);
	reg.registerVar("mbc.Ratio2","","S",N_("Compression ratio"),&fslider14, 2.0, 1.0, 1e+02, 0.1);
	reg.registerVar("mbc.Ratio3","","S",N_("Compression ratio"),&fslider20, 2.0, 1.0, 1e+02, 0.1);
	reg.registerVar("mbc.Ratio4","","S",N_("Compression ratio"),&fslider26, 2.0, 1.0, 1e+02, 0.1);
	reg.registerVar("mbc.Ratio5","","S",N_("Compression ratio"),&fslider32, 2.0, 1.0, 1e+02, 0.1);
	reg.registerVar("mbc.Attack1","","S",N_("Time before the compressor starts to kick in"),&fslider6, 0.012, 0.001, 1.0, 0.001);
	reg.registerVar("mbc.Attack2","","S",N_("Time before the compressor starts to kick in"),&fslider12, 0.012, 0.001, 1.0, 0.001);
	reg.registerVar("mbc.Attack3","","S",N_("Time before the compressor starts to kick in"),&fslider18, 0.012, 0.001, 1.0, 0.001);
	reg.registerVar("mbc.Attack4","","S",N_("Time before the compressor starts to kick in"),&fslider24, 0.012, 0.001, 1.0, 0.001);
	reg.registerVar("mbc.Attack5","","S",N_("Time before the compressor starts to kick in"),&fslider30, 0.012, 0.001, 1.0, 0.001);
	reg.registerVar("mbc.Release1","","S",N_("Time before the compressor releases the sound"),&fslider5, 1.25, 0.01, 1e+01, 0.01);
	reg.registerVar("mbc.Release2","","S",N_("Time before the compressor releases the sound"),&fslider11, 1.25, 0.01, 1e+01, 0.01);
	reg.registerVar("mbc.Release3","","S",N_("Time before the compressor releases the sound"),&fslider17, 1.25, 0.01, 1e+01, 0.01);
	reg.registerVar("mbc.Release4","","S",N_("Time before the compressor releases the sound"),&fslider23, 1.25, 0.01, 1e+01, 0.01);
	reg.registerVar("mbc.Release5","","S",N_("Time before the compressor releases the sound"),&fslider29, 1.25, 0.01, 1e+01, 0.01);
	reg.registerVar("mbc.crossover_b1_b2",N_("Crossover B1-B2 (hz)"),"SL",N_("Crossover bandpass frequency"),&fslider0, 8e+01, 2e+01, 2e+04, 1.08);
	reg.registerVar("mbc.crossover_b2_b3",N_("Crossover B2-B3 (hz)"),"SL",N_("Crossover bandpass frequency"),&fslider1, 2.1e+02, 2e+01, 2e+04, 1.08);
	reg.registerVar("mbc.crossover_b3_b4",N_("Crossover B3-B4 (hz)"),"SL",N_("Crossover bandpass frequency"),&fslider2, 1.7e+03, 2e+01, 2e+04, 1.08);
	reg.registerVar("mbc.crossover_b4_b5",N_("Crossover B4-B5 (hz)"),"SL",N_("Crossover bandpass frequency"),&fslider3, 5e+03, 2e+01, 2e+04, 1.08);
	reg.registerNonMidiFloatVar("mbc.v1",&fbargraph0, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbc.v2",&fbargraph1, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbc.v3",&fbargraph2, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbc.v4",&fbargraph3, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbc.v5",&fbargraph4, false, true, -70.0, -70.0, 4.0, 0.00001);
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
b.create_small_rackknob(PARAM("Release1"), N_("Release"));
b.closeBox();
b.closeBox();
b.closeBox();
b.closeBox();

b.openHorizontalBox(N_("Band 2"));
b.openpaintampBox("");
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
b.openpaintampBox("");
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
