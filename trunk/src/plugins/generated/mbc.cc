// generated from file '../src/plugins/mbc.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

namespace pluginlib {
namespace mbc {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	double 	fConst0;
	double 	fConst1;
	FAUSTFLOAT 	fslider0;
	double 	fConst2;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT 	fslider3;
	double 	fVec0[2];
	double 	fRec11[2];
	double 	fRec10[3];
	double 	fVec1[2];
	double 	fRec9[2];
	double 	fRec8[3];
	double 	fVec2[2];
	double 	fRec7[2];
	double 	fRec6[3];
	double 	fVec3[2];
	double 	fRec5[2];
	double 	fRec4[3];
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT 	fslider6;
	double 	fRec14[2];
	double 	fRec13[2];
	FAUSTFLOAT 	fslider7;
	double 	fConst3;
	FAUSTFLOAT 	fslider8;
	double 	fRec12[2];
	FAUSTFLOAT 	fslider9;
	double 	fRec15[2];
	double 	fRec0[2];
	int 	iRec1[2];
	double 	fRec2[2];
	FAUSTFLOAT 	fbargraph0;
	double 	fRec21[2];
	double 	fRec20[3];
	FAUSTFLOAT 	fslider10;
	FAUSTFLOAT 	fslider11;
	FAUSTFLOAT 	fslider12;
	double 	fRec24[2];
	double 	fRec23[2];
	FAUSTFLOAT 	fslider13;
	FAUSTFLOAT 	fslider14;
	double 	fRec22[2];
	FAUSTFLOAT 	fslider15;
	double 	fRec25[2];
	double 	fRec16[2];
	int 	iRec17[2];
	double 	fRec18[2];
	FAUSTFLOAT 	fbargraph1;
	double 	fRec32[2];
	double 	fRec31[3];
	double 	fRec30[3];
	FAUSTFLOAT 	fslider16;
	FAUSTFLOAT 	fslider17;
	FAUSTFLOAT 	fslider18;
	double 	fRec35[2];
	double 	fRec34[2];
	FAUSTFLOAT 	fslider19;
	FAUSTFLOAT 	fslider20;
	double 	fRec33[2];
	FAUSTFLOAT 	fslider21;
	double 	fRec36[2];
	double 	fRec26[2];
	int 	iRec27[2];
	double 	fRec28[2];
	FAUSTFLOAT 	fbargraph2;
	double 	fRec44[2];
	double 	fRec43[3];
	double 	fRec42[3];
	double 	fRec41[3];
	FAUSTFLOAT 	fslider22;
	FAUSTFLOAT 	fslider23;
	FAUSTFLOAT 	fslider24;
	double 	fRec47[2];
	double 	fRec46[2];
	FAUSTFLOAT 	fslider25;
	FAUSTFLOAT 	fslider26;
	double 	fRec45[2];
	FAUSTFLOAT 	fslider27;
	double 	fRec48[2];
	double 	fRec37[2];
	int 	iRec38[2];
	double 	fRec39[2];
	FAUSTFLOAT 	fbargraph3;
	double 	fRec57[2];
	double 	fRec56[3];
	double 	fRec55[3];
	double 	fRec54[3];
	double 	fRec53[3];
	FAUSTFLOAT 	fslider28;
	FAUSTFLOAT 	fslider29;
	FAUSTFLOAT 	fslider30;
	double 	fRec60[2];
	double 	fRec59[2];
	FAUSTFLOAT 	fslider31;
	FAUSTFLOAT 	fslider32;
	double 	fRec58[2];
	FAUSTFLOAT 	fslider33;
	double 	fRec61[2];
	double 	fRec49[2];
	int 	iRec50[2];
	double 	fRec51[2];
	FAUSTFLOAT 	fbargraph4;

	void clear_state_f();
	int load_ui_f(const UiBuilder& b, int form);
	static const char *glade_def;
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
	shortname = N_("MB Comp");     // shortname
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
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<3; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<3; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<3; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) iRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<3; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fRec25[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) iRec17[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fRec32[i] = 0;
	for (int i=0; i<3; i++) fRec31[i] = 0;
	for (int i=0; i<3; i++) fRec30[i] = 0;
	for (int i=0; i<2; i++) fRec35[i] = 0;
	for (int i=0; i<2; i++) fRec34[i] = 0;
	for (int i=0; i<2; i++) fRec33[i] = 0;
	for (int i=0; i<2; i++) fRec36[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<2; i++) iRec27[i] = 0;
	for (int i=0; i<2; i++) fRec28[i] = 0;
	for (int i=0; i<2; i++) fRec44[i] = 0;
	for (int i=0; i<3; i++) fRec43[i] = 0;
	for (int i=0; i<3; i++) fRec42[i] = 0;
	for (int i=0; i<3; i++) fRec41[i] = 0;
	for (int i=0; i<2; i++) fRec47[i] = 0;
	for (int i=0; i<2; i++) fRec46[i] = 0;
	for (int i=0; i<2; i++) fRec45[i] = 0;
	for (int i=0; i<2; i++) fRec48[i] = 0;
	for (int i=0; i<2; i++) fRec37[i] = 0;
	for (int i=0; i<2; i++) iRec38[i] = 0;
	for (int i=0; i<2; i++) fRec39[i] = 0;
	for (int i=0; i<2; i++) fRec57[i] = 0;
	for (int i=0; i<3; i++) fRec56[i] = 0;
	for (int i=0; i<3; i++) fRec55[i] = 0;
	for (int i=0; i<3; i++) fRec54[i] = 0;
	for (int i=0; i<3; i++) fRec53[i] = 0;
	for (int i=0; i<2; i++) fRec60[i] = 0;
	for (int i=0; i<2; i++) fRec59[i] = 0;
	for (int i=0; i<2; i++) fRec58[i] = 0;
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
	fConst0 = min(1.92e+05, max(1.0, (double)fSamplingFreq));
	fConst1 = (1.0 / fConst0);
	fConst2 = (3.141592653589793 / fConst0);
	fConst3 = (2.0 / fConst0);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
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
		fRec11[0] = ((fSlow29 * (fVec0[0] + fVec0[1])) + (fSlow28 * fRec11[1]));
		fRec10[0] = (fRec11[0] - (fSlow26 * ((fSlow24 * fRec10[2]) + (fSlow22 * fRec10[1]))));
		double fTemp1 = (fRec10[0] + (fRec10[2] + (2 * fRec10[1])));
		double fTemp2 = (fSlow26 * fTemp1);
		fVec1[0] = fTemp2;
		fRec9[0] = ((fSlow32 * fRec9[1]) + (fSlow31 * (fVec1[0] + fVec1[1])));
		fRec8[0] = (fRec9[0] - (fSlow19 * ((fSlow17 * fRec8[1]) + (fSlow15 * fRec8[2]))));
		double fTemp3 = (fRec8[0] + (fRec8[2] + (2 * fRec8[1])));
		double fTemp4 = (fSlow19 * fTemp3);
		fVec2[0] = fTemp4;
		fRec7[0] = ((fSlow35 * fRec7[1]) + (fSlow34 * (fVec2[0] + fVec2[1])));
		fRec6[0] = (fRec7[0] - (fSlow12 * ((fSlow10 * fRec6[1]) + (fSlow8 * fRec6[2]))));
		double fTemp5 = (fRec6[0] + (fRec6[2] + (2 * fRec6[1])));
		double fTemp6 = (fSlow12 * fTemp5);
		fVec3[0] = fTemp6;
		fRec5[0] = ((fSlow38 * fRec5[1]) + (fSlow37 * (fVec3[0] + fVec3[1])));
		fRec4[0] = (fRec5[0] - (fSlow5 * ((fSlow4 * fRec4[1]) + (fSlow2 * fRec4[2]))));
		double fTemp7 = (fSlow5 * (fRec4[0] + (fRec4[2] + (2 * fRec4[1]))));
		double fTemp8 = ((iSlow41)?0:fTemp7);
		double fTemp9 = fabs(fTemp8);
		double fTemp10 = ((int((fRec13[1] > fTemp9)))?fSlow44:fSlow43);
		fRec14[0] = ((fRec14[1] * fTemp10) + (fTemp9 * (1.0 - fTemp10)));
		fRec13[0] = fRec14[0];
		fRec12[0] = ((fSlow46 * fRec12[1]) + (fSlow47 * max((fSlow45 + (20 * log10(fRec13[0]))), 0.0)));
		fRec15[0] = (fSlow48 + (0.999 * fRec15[1]));
		double fTemp11 = (fSlow49 * (fRec15[0] * ((iSlow41)?fTemp7:(pow(10,(0.05 * fRec12[0])) * fTemp8))));
		double 	fRec3 = max(fConst1, fabs(fTemp11));
		int iTemp12 = int((iRec1[1] < 4096));
		fRec0[0] = ((iTemp12)?max(fRec0[1], fRec3):fRec3);
		iRec1[0] = ((iTemp12)?(1 + iRec1[1]):1);
		fRec2[0] = ((iTemp12)?fRec2[1]:fRec0[1]);
		fbargraph0 = fRec2[0];
		fRec21[0] = ((fSlow38 * fRec21[1]) + (fSlow37 * ((fSlow51 * fTemp5) + (fSlow50 * fVec3[1]))));
		fRec20[0] = (fRec21[0] - (fSlow5 * ((fSlow4 * fRec20[1]) + (fSlow2 * fRec20[2]))));
		double fTemp13 = (fSlow5 * ((fSlow52 * fRec20[1]) + (fSlow3 * (fRec20[2] + fRec20[0]))));
		double fTemp14 = ((iSlow55)?0:fTemp13);
		double fTemp15 = fabs(fTemp14);
		double fTemp16 = ((int((fRec23[1] > fTemp15)))?fSlow58:fSlow57);
		fRec24[0] = ((fRec24[1] * fTemp16) + (fTemp15 * (1.0 - fTemp16)));
		fRec23[0] = fRec24[0];
		fRec22[0] = ((fSlow60 * fRec22[1]) + (fSlow61 * max((fSlow59 + (20 * log10(fRec23[0]))), 0.0)));
		fRec25[0] = (fSlow62 + (0.999 * fRec25[1]));
		double fTemp17 = (fSlow63 * (fRec25[0] * ((iSlow55)?fTemp13:(pow(10,(0.05 * fRec22[0])) * fTemp14))));
		double 	fRec19 = max(fConst1, fabs(fTemp17));
		int iTemp18 = int((iRec17[1] < 4096));
		fRec16[0] = ((iTemp18)?max(fRec16[1], fRec19):fRec19);
		iRec17[0] = ((iTemp18)?(1 + iRec17[1]):1);
		fRec18[0] = ((iTemp18)?fRec18[1]:fRec16[1]);
		fbargraph1 = fRec18[0];
		double fTemp19 = (fSlow4 * fRec30[1]);
		fRec32[0] = ((fSlow35 * fRec32[1]) + (fSlow34 * ((fSlow67 * fTemp3) + (fSlow66 * fVec2[1]))));
		fRec31[0] = (fRec32[0] - (fSlow12 * ((fSlow10 * fRec31[1]) + (fSlow8 * fRec31[2]))));
		fRec30[0] = ((fSlow12 * ((fSlow68 * fRec31[1]) + (fSlow9 * (fRec31[2] + fRec31[0])))) - (fSlow65 * ((fSlow64 * fRec30[2]) + fTemp19)));
		double fTemp20 = (fRec30[2] + (fSlow65 * (fTemp19 + (fSlow64 * fRec30[0]))));
		double fTemp21 = ((iSlow71)?0:fTemp20);
		double fTemp22 = fabs(fTemp21);
		double fTemp23 = ((int((fRec34[1] > fTemp22)))?fSlow74:fSlow73);
		fRec35[0] = ((fRec35[1] * fTemp23) + (fTemp22 * (1.0 - fTemp23)));
		fRec34[0] = fRec35[0];
		fRec33[0] = ((fSlow76 * fRec33[1]) + (fSlow77 * max((fSlow75 + (20 * log10(fRec34[0]))), 0.0)));
		fRec36[0] = (fSlow78 + (0.999 * fRec36[1]));
		double fTemp24 = (fSlow79 * (fRec36[0] * ((iSlow71)?fTemp20:(pow(10,(0.05 * fRec33[0])) * fTemp21))));
		double 	fRec29 = max(fConst1, fabs(fTemp24));
		int iTemp25 = int((iRec27[1] < 4096));
		fRec26[0] = ((iTemp25)?max(fRec26[1], fRec29):fRec29);
		iRec27[0] = ((iTemp25)?(1 + iRec27[1]):1);
		fRec28[0] = ((iTemp25)?fRec28[1]:fRec26[1]);
		fbargraph2 = fRec28[0];
		double fTemp26 = (fSlow4 * fRec41[1]);
		double fTemp27 = (fSlow10 * fRec42[1]);
		fRec44[0] = ((fSlow32 * fRec44[1]) + (fSlow31 * ((fSlow83 * fTemp1) + (fSlow82 * fVec1[1]))));
		fRec43[0] = (fRec44[0] - (fSlow19 * ((fSlow17 * fRec43[1]) + (fSlow15 * fRec43[2]))));
		fRec42[0] = ((fSlow19 * ((fSlow84 * fRec43[1]) + (fSlow16 * (fRec43[2] + fRec43[0])))) - (fSlow81 * ((fSlow80 * fRec42[2]) + fTemp27)));
		fRec41[0] = ((fRec42[2] + (fSlow81 * (fTemp27 + (fSlow80 * fRec42[0])))) - (fSlow65 * ((fSlow64 * fRec41[2]) + fTemp26)));
		double fTemp28 = (fRec41[2] + (fSlow65 * (fTemp26 + (fSlow64 * fRec41[0]))));
		double fTemp29 = ((iSlow87)?0:fTemp28);
		double fTemp30 = fabs(fTemp29);
		double fTemp31 = ((int((fRec46[1] > fTemp30)))?fSlow90:fSlow89);
		fRec47[0] = ((fRec47[1] * fTemp31) + (fTemp30 * (1.0 - fTemp31)));
		fRec46[0] = fRec47[0];
		fRec45[0] = ((fSlow92 * fRec45[1]) + (fSlow93 * max((fSlow91 + (20 * log10(fRec46[0]))), 0.0)));
		fRec48[0] = (fSlow94 + (0.999 * fRec48[1]));
		double fTemp32 = (fSlow95 * (fRec48[0] * ((iSlow87)?fTemp28:(pow(10,(0.05 * fRec45[0])) * fTemp29))));
		double 	fRec40 = max(fConst1, fabs(fTemp32));
		int iTemp33 = int((iRec38[1] < 4096));
		fRec37[0] = ((iTemp33)?max(fRec37[1], fRec40):fRec40);
		iRec38[0] = ((iTemp33)?(1 + iRec38[1]):1);
		fRec39[0] = ((iTemp33)?fRec39[1]:fRec37[1]);
		fbargraph3 = fRec39[0];
		double fTemp34 = (fSlow4 * fRec53[1]);
		double fTemp35 = (fSlow10 * fRec54[1]);
		double fTemp36 = (fSlow17 * fRec55[1]);
		fRec57[0] = ((fSlow29 * ((fSlow23 * fVec0[0]) + (fSlow98 * fVec0[1]))) + (fSlow28 * fRec57[1]));
		fRec56[0] = (fRec57[0] - (fSlow26 * ((fSlow24 * fRec56[2]) + (fSlow22 * fRec56[1]))));
		fRec55[0] = ((fSlow26 * ((fSlow99 * fRec56[1]) + (fSlow21 * (fRec56[2] + fRec56[0])))) - (fSlow97 * ((fSlow96 * fRec55[2]) + fTemp36)));
		fRec54[0] = ((fRec55[2] + (fSlow97 * (fTemp36 + (fSlow96 * fRec55[0])))) - (fSlow81 * ((fSlow80 * fRec54[2]) + fTemp35)));
		fRec53[0] = ((fRec54[2] + (fSlow81 * (fTemp35 + (fSlow80 * fRec54[0])))) - (fSlow65 * ((fSlow64 * fRec53[2]) + fTemp34)));
		double fTemp37 = (fRec53[2] + (fSlow65 * (fTemp34 + (fSlow64 * fRec53[0]))));
		double fTemp38 = ((iSlow102)?0:fTemp37);
		double fTemp39 = fabs(fTemp38);
		double fTemp40 = ((int((fRec59[1] > fTemp39)))?fSlow105:fSlow104);
		fRec60[0] = ((fRec60[1] * fTemp40) + (fTemp39 * (1.0 - fTemp40)));
		fRec59[0] = fRec60[0];
		fRec58[0] = ((fSlow107 * fRec58[1]) + (fSlow108 * max((fSlow106 + (20 * log10(fRec59[0]))), 0.0)));
		fRec61[0] = (fSlow109 + (0.999 * fRec61[1]));
		double fTemp41 = (fSlow110 * (fRec61[0] * ((iSlow102)?fTemp37:(pow(10,(0.05 * fRec58[0])) * fTemp38))));
		double 	fRec52 = max(fConst1, fabs(fTemp41));
		int iTemp42 = int((iRec50[1] < 4096));
		fRec49[0] = ((iTemp42)?max(fRec49[1], fRec52):fRec52);
		iRec50[0] = ((iTemp42)?(1 + iRec50[1]):1);
		fRec51[0] = ((iTemp42)?fRec51[1]:fRec49[1]);
		fbargraph4 = fRec51[0];
		output0[i] = (FAUSTFLOAT)((((fTemp41 + fTemp32) + fTemp24) + fTemp17) + fTemp11);
		// post processing
		fRec51[1] = fRec51[0];
		iRec50[1] = iRec50[0];
		fRec49[1] = fRec49[0];
		fRec61[1] = fRec61[0];
		fRec58[1] = fRec58[0];
		fRec59[1] = fRec59[0];
		fRec60[1] = fRec60[0];
		fRec53[2] = fRec53[1]; fRec53[1] = fRec53[0];
		fRec54[2] = fRec54[1]; fRec54[1] = fRec54[0];
		fRec55[2] = fRec55[1]; fRec55[1] = fRec55[0];
		fRec56[2] = fRec56[1]; fRec56[1] = fRec56[0];
		fRec57[1] = fRec57[0];
		fRec39[1] = fRec39[0];
		iRec38[1] = iRec38[0];
		fRec37[1] = fRec37[0];
		fRec48[1] = fRec48[0];
		fRec45[1] = fRec45[0];
		fRec46[1] = fRec46[0];
		fRec47[1] = fRec47[0];
		fRec41[2] = fRec41[1]; fRec41[1] = fRec41[0];
		fRec42[2] = fRec42[1]; fRec42[1] = fRec42[0];
		fRec43[2] = fRec43[1]; fRec43[1] = fRec43[0];
		fRec44[1] = fRec44[0];
		fRec28[1] = fRec28[0];
		iRec27[1] = iRec27[0];
		fRec26[1] = fRec26[0];
		fRec36[1] = fRec36[0];
		fRec33[1] = fRec33[0];
		fRec34[1] = fRec34[0];
		fRec35[1] = fRec35[0];
		fRec30[2] = fRec30[1]; fRec30[1] = fRec30[0];
		fRec31[2] = fRec31[1]; fRec31[1] = fRec31[0];
		fRec32[1] = fRec32[0];
		fRec18[1] = fRec18[0];
		iRec17[1] = iRec17[0];
		fRec16[1] = fRec16[0];
		fRec25[1] = fRec25[0];
		fRec22[1] = fRec22[0];
		fRec23[1] = fRec23[0];
		fRec24[1] = fRec24[0];
		fRec20[2] = fRec20[1]; fRec20[1] = fRec20[0];
		fRec21[1] = fRec21[0];
		fRec2[1] = fRec2[0];
		iRec1[1] = iRec1[0];
		fRec0[1] = fRec0[0];
		fRec15[1] = fRec15[0];
		fRec12[1] = fRec12[0];
		fRec13[1] = fRec13[0];
		fRec14[1] = fRec14[0];
		fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fVec3[1] = fVec3[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec7[1] = fRec7[0];
		fVec2[1] = fVec2[0];
		fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
		fRec9[1] = fRec9[0];
		fVec1[1] = fVec1[0];
		fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
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
	reg.registerVar("mbc.Attack1","","S",N_("Time before the compressor starts to kick in"),&fslider5, 0.012, 0.001, 1.0, 0.001);
	reg.registerVar("mbc.Attack2","","S",N_("Time before the compressor starts to kick in"),&fslider11, 0.012, 0.001, 1.0, 0.001);
	reg.registerVar("mbc.Attack3","","S",N_("Time before the compressor starts to kick in"),&fslider17, 0.012, 0.001, 1.0, 0.001);
	reg.registerVar("mbc.Attack4","","S",N_("Time before the compressor starts to kick in"),&fslider23, 0.012, 0.001, 1.0, 0.001);
	reg.registerVar("mbc.Attack5","","S",N_("Time before the compressor starts to kick in"),&fslider29, 0.012, 0.001, 1.0, 0.001);
	reg.registerVar("mbc.Release1","","S",N_("Time before the compressor releases the sound"),&fslider6, 1.25, 0.01, 1e+01, 0.01);
	reg.registerVar("mbc.Release2","","S",N_("Time before the compressor releases the sound"),&fslider12, 1.25, 0.01, 1e+01, 0.01);
	reg.registerVar("mbc.Release3","","S",N_("Time before the compressor releases the sound"),&fslider18, 1.25, 0.01, 1e+01, 0.01);
	reg.registerVar("mbc.Release4","","S",N_("Time before the compressor releases the sound"),&fslider24, 1.25, 0.01, 1e+01, 0.01);
	reg.registerVar("mbc.Release5","","S",N_("Time before the compressor releases the sound"),&fslider30, 1.25, 0.01, 1e+01, 0.01);
	reg.registerVar("mbc.crossover_b1_b2",N_("Crossover B1-B2 (hz)"),"SL",N_("Crossover fi.bandpass frequency"),&fslider0, 8e+01, 2e+01, 2e+04, 1.08);
	reg.registerVar("mbc.crossover_b2_b3",N_("Crossover B2-B3 (hz)"),"SL",N_("Crossover fi.bandpass frequency"),&fslider1, 2.1e+02, 2e+01, 2e+04, 1.08);
	reg.registerVar("mbc.crossover_b3_b4",N_("Crossover B3-B4 (hz)"),"SL",N_("Crossover fi.bandpass frequency"),&fslider2, 1.7e+03, 2e+01, 2e+04, 1.08);
	reg.registerVar("mbc.crossover_b4_b5",N_("Crossover B4-B5 (hz)"),"SL",N_("Crossover fi.bandpass frequency"),&fslider3, 5e+03, 2e+01, 2e+04, 1.08);
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
                                        <property name=\"var_id\">mbc.Ratio1</property>\n\
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
                                        <property name=\"var_id\">mbc.Makeup1</property>\n\
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
                                        <property name=\"var_id\">mbc.Makeup-Threshold1</property>\n\
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
                                <property name=\"var_id\">mbc.Mode1</property>\n\
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
                                <property name=\"var_id\">mbc.Attack1</property>\n\
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
                                <property name=\"var_id\">mbc.crossover_b1_b2</property>\n\
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
                                <property name=\"var_id\">mbc.Release1</property>\n\
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
                                        <property name=\"var_id\">mbc.Ratio2</property>\n\
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
                                        <property name=\"var_id\">mbc.Makeup2</property>\n\
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
                                        <property name=\"var_id\">mbc.Makeup-Threshold2</property>\n\
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
                                <property name=\"var_id\">mbc.Mode2</property>\n\
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
                                <property name=\"var_id\">mbc.Attack2</property>\n\
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
                                <property name=\"var_id\">mbc.crossover_b2_b3</property>\n\
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
                                <property name=\"var_id\">mbc.crossover_b1_b2</property>\n\
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
                                <property name=\"var_id\">mbc.Release2</property>\n\
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
                                        <property name=\"var_id\">mbc.Ratio3</property>\n\
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
                                        <property name=\"var_id\">mbc.Makeup3</property>\n\
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
                                        <property name=\"var_id\">mbc.Makeup-Threshold3</property>\n\
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
                                <property name=\"var_id\">mbc.Mode3</property>\n\
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
                                <property name=\"var_id\">mbc.Attack3</property>\n\
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
                                <property name=\"var_id\">mbc.crossover_b3_b4</property>\n\
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
                                <property name=\"var_id\">mbc.crossover_b2_b3</property>\n\
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
                                <property name=\"var_id\">mbc.Release3</property>\n\
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
                                        <property name=\"var_id\">mbc.Ratio4</property>\n\
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
                                        <property name=\"var_id\">mbc.Makeup4</property>\n\
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
                                        <property name=\"var_id\">mbc.Makeup-Threshold4</property>\n\
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
                                <property name=\"var_id\">mbc.Mode4</property>\n\
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
                                <property name=\"var_id\">mbc.Attack4</property>\n\
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
                                <property name=\"var_id\">mbc.crossover_b4_b5</property>\n\
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
                                <property name=\"var_id\">mbc.crossover_b3_b4</property>\n\
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
                                <property name=\"var_id\">mbc.Release4</property>\n\
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
                                        <property name=\"var_id\">mbc.Ratio5</property>\n\
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
                                        <property name=\"var_id\">mbc.Makeup5</property>\n\
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
                                        <property name=\"var_id\">mbc.Makeup-Threshold5</property>\n\
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
                                <property name=\"var_id\">mbc.Mode5</property>\n\
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
                                <property name=\"var_id\">mbc.Attack5</property>\n\
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
                                <property name=\"var_id\">mbc.crossover_b4_b5</property>\n\
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
                                <property name=\"var_id\">mbc.Release5</property>\n\
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
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">mbc.v1</property>\n\
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
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">mbc.v2</property>\n\
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
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">mbc.v3</property>\n\
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
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">mbc.v4</property>\n\
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
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">mbc.v5</property>\n\
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
