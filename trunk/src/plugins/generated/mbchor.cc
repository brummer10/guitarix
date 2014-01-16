// generated from file '../src/plugins/mbchor.dsp' by dsp2cc:
// Code generated with Faust 0.9.58 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

namespace pluginlib {
namespace mbchor {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	class SIG0 {
	  private:
		int 	fSamplingFreq;
		int 	iRec13[2];
	  public:
		int getNumInputs() 	{ return 0; }
		int getNumOutputs() 	{ return 1; }
		void init(int samplingFreq) {
			fSamplingFreq = samplingFreq;
			for (int i=0; i<2; i++) iRec13[i] = 0;
		}
		void fill (int count, double output[]) {
			for (int i=0; i<count; i++) {
				iRec13[0] = (1 + iRec13[1]);
				output[i] = sin((9.587379924285257e-05 * (iRec13[0] - 1)));
				// post processing
				iRec13[1] = iRec13[0];
			}
		}
	};
			int 	iConst0;
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
	int 	IOTA;
	double 	fVec4[65536];
	FAUSTFLOAT 	fslider4;
	double 	fConst3;
	double 	fRec12[2];
	static double 	ftbl0[65536];
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT 	fslider6;
	double 	fRec14[2];
	double 	fConst4;
	FAUSTFLOAT 	fslider7;
	double 	fRec0[2];
	int 	iRec1[2];
	double 	fRec2[2];
	FAUSTFLOAT 	fbargraph0;
	double 	fRec20[2];
	double 	fRec19[3];
	double 	fVec5[65536];
	FAUSTFLOAT 	fslider8;
	double 	fRec21[2];
	FAUSTFLOAT 	fslider9;
	FAUSTFLOAT 	fslider10;
	double 	fRec22[2];
	FAUSTFLOAT 	fslider11;
	double 	fRec15[2];
	int 	iRec16[2];
	double 	fRec17[2];
	FAUSTFLOAT 	fbargraph1;
	double 	fRec29[2];
	double 	fRec28[3];
	double 	fRec27[3];
	double 	fVec6[65536];
	FAUSTFLOAT 	fslider12;
	double 	fRec30[2];
	FAUSTFLOAT 	fslider13;
	FAUSTFLOAT 	fslider14;
	double 	fRec31[2];
	FAUSTFLOAT 	fslider15;
	double 	fRec23[2];
	int 	iRec24[2];
	double 	fRec25[2];
	FAUSTFLOAT 	fbargraph2;
	double 	fRec39[2];
	double 	fRec38[3];
	double 	fRec37[3];
	double 	fRec36[3];
	double 	fVec7[65536];
	FAUSTFLOAT 	fslider16;
	double 	fRec40[2];
	FAUSTFLOAT 	fslider17;
	FAUSTFLOAT 	fslider18;
	double 	fRec41[2];
	FAUSTFLOAT 	fslider19;
	double 	fRec32[2];
	int 	iRec33[2];
	double 	fRec34[2];
	FAUSTFLOAT 	fbargraph3;
	double 	fRec50[2];
	double 	fRec49[3];
	double 	fRec48[3];
	double 	fRec47[3];
	double 	fRec46[3];
	double 	fVec8[65536];
	FAUSTFLOAT 	fslider20;
	double 	fRec51[2];
	FAUSTFLOAT 	fslider21;
	FAUSTFLOAT 	fslider22;
	double 	fRec52[2];
	FAUSTFLOAT 	fslider23;
	double 	fRec42[2];
	int 	iRec43[2];
	double 	fRec44[2];
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


double Dsp::ftbl0[65536];

Dsp::Dsp()
	: PluginDef() {
	version = PLUGINDEF_VERSION;
	flags = 0;
	id = "mbchor";
	name = N_("MultiBand Chorus");
	groups = 0;
	description = N_("Multi Band Chorus"); // description (tooltip)
	category = N_("Modulation");       // category
	shortname = N_("MB Chorus");     // shortname
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
	for (int i=0; i<65536; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) iRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<3; i++) fRec19[i] = 0;
	for (int i=0; i<65536; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) iRec16[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) fRec29[i] = 0;
	for (int i=0; i<3; i++) fRec28[i] = 0;
	for (int i=0; i<3; i++) fRec27[i] = 0;
	for (int i=0; i<65536; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec30[i] = 0;
	for (int i=0; i<2; i++) fRec31[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<2; i++) iRec24[i] = 0;
	for (int i=0; i<2; i++) fRec25[i] = 0;
	for (int i=0; i<2; i++) fRec39[i] = 0;
	for (int i=0; i<3; i++) fRec38[i] = 0;
	for (int i=0; i<3; i++) fRec37[i] = 0;
	for (int i=0; i<3; i++) fRec36[i] = 0;
	for (int i=0; i<65536; i++) fVec7[i] = 0;
	for (int i=0; i<2; i++) fRec40[i] = 0;
	for (int i=0; i<2; i++) fRec41[i] = 0;
	for (int i=0; i<2; i++) fRec32[i] = 0;
	for (int i=0; i<2; i++) iRec33[i] = 0;
	for (int i=0; i<2; i++) fRec34[i] = 0;
	for (int i=0; i<2; i++) fRec50[i] = 0;
	for (int i=0; i<3; i++) fRec49[i] = 0;
	for (int i=0; i<3; i++) fRec48[i] = 0;
	for (int i=0; i<3; i++) fRec47[i] = 0;
	for (int i=0; i<3; i++) fRec46[i] = 0;
	for (int i=0; i<65536; i++) fVec8[i] = 0;
	for (int i=0; i<2; i++) fRec51[i] = 0;
	for (int i=0; i<2; i++) fRec52[i] = 0;
	for (int i=0; i<2; i++) fRec42[i] = 0;
	for (int i=0; i<2; i++) iRec43[i] = 0;
	for (int i=0; i<2; i++) fRec44[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	SIG0 sig0;
	sig0.init(samplingFreq);
	sig0.fill(65536,ftbl0);
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (1.0 / double(iConst0));
	fConst2 = (3.141592653589793 / double(iConst0));
	IOTA = 0;
	fConst3 = (0.016666666666666666 / double(iConst0));
	fConst4 = (0.5 * iConst0);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlow0 = tan((fConst2 * fslider0));
	double 	fSlow1 = (1.0 / faustpower<2>(fSlow0));
	double 	fSlow2 = (2 * (1 - fSlow1));
	double 	fSlow3 = (1.0 / fSlow0);
	double 	fSlow4 = (1 + ((fSlow3 - 1.0000000000000004) / fSlow0));
	double 	fSlow5 = (1.0 / (1 + ((fSlow3 + 1.0000000000000004) / fSlow0)));
	double 	fSlow6 = (1 + fSlow3);
	double 	fSlow7 = (0 - ((1 - fSlow3) / fSlow6));
	double 	fSlow8 = tan((fConst2 * fslider1));
	double 	fSlow9 = (1.0 / faustpower<2>(fSlow8));
	double 	fSlow10 = (2 * (1 - fSlow9));
	double 	fSlow11 = (1.0 / fSlow8);
	double 	fSlow12 = (1 + ((fSlow11 - 1.0000000000000004) / fSlow8));
	double 	fSlow13 = (1 + ((fSlow11 + 1.0000000000000004) / fSlow8));
	double 	fSlow14 = (1.0 / fSlow13);
	double 	fSlow15 = (1 + fSlow11);
	double 	fSlow16 = (0 - ((1 - fSlow11) / fSlow15));
	double 	fSlow17 = tan((fConst2 * fslider2));
	double 	fSlow18 = (1.0 / faustpower<2>(fSlow17));
	double 	fSlow19 = (2 * (1 - fSlow18));
	double 	fSlow20 = (1.0 / fSlow17);
	double 	fSlow21 = (1 + ((fSlow20 - 1.0000000000000004) / fSlow17));
	double 	fSlow22 = (1 + ((fSlow20 + 1.0000000000000004) / fSlow17));
	double 	fSlow23 = (1.0 / fSlow22);
	double 	fSlow24 = (1 + fSlow20);
	double 	fSlow25 = (0 - ((1 - fSlow20) / fSlow24));
	double 	fSlow26 = tan((fConst2 * fslider3));
	double 	fSlow27 = (1.0 / faustpower<2>(fSlow26));
	double 	fSlow28 = (2 * (1 - fSlow27));
	double 	fSlow29 = (1.0 / fSlow26);
	double 	fSlow30 = (1 + ((fSlow29 - 1.0000000000000004) / fSlow26));
	double 	fSlow31 = (1 + ((1.0000000000000004 + fSlow29) / fSlow26));
	double 	fSlow32 = (1.0 / fSlow31);
	double 	fSlow33 = (1 + fSlow29);
	double 	fSlow34 = (0 - ((1 - fSlow29) / fSlow33));
	double 	fSlow35 = (1.0 / fSlow33);
	double 	fSlow36 = (1.0 / fSlow24);
	double 	fSlow37 = (1.0 / fSlow15);
	double 	fSlow38 = (1.0 / fSlow6);
	double 	fSlow39 = (fConst3 * fslider4);
	double 	fSlow40 = (0.1 * fslider5);
	double 	fSlow41 = (0.0010000000000000009 * fslider6);
	double 	fSlow42 = fslider7;
	double 	fSlow43 = (1.0 / (fSlow0 * fSlow13));
	double 	fSlow44 = (0 - fSlow3);
	double 	fSlow45 = (2 * (0 - fSlow1));
	double 	fSlow46 = (fConst3 * fslider8);
	double 	fSlow47 = (0.1 * fslider9);
	double 	fSlow48 = (0.0010000000000000009 * fslider10);
	double 	fSlow49 = fslider11;
	double 	fSlow50 = (1 + ((fSlow3 - 1.0) / fSlow0));
	double 	fSlow51 = (1.0 / (1 + ((1.0 + fSlow3) / fSlow0)));
	double 	fSlow52 = (1.0 / (fSlow8 * fSlow22));
	double 	fSlow53 = (0 - fSlow11);
	double 	fSlow54 = (2 * (0 - fSlow9));
	double 	fSlow55 = (fConst3 * fslider12);
	double 	fSlow56 = (0.1 * fslider13);
	double 	fSlow57 = (0.0010000000000000009 * fslider14);
	double 	fSlow58 = fslider15;
	double 	fSlow59 = (1 + ((fSlow11 - 1.0) / fSlow8));
	double 	fSlow60 = (1.0 / (1 + ((1.0 + fSlow11) / fSlow8)));
	double 	fSlow61 = (1.0 / (fSlow17 * fSlow31));
	double 	fSlow62 = (0 - fSlow20);
	double 	fSlow63 = (2 * (0 - fSlow18));
	double 	fSlow64 = (fConst3 * fslider16);
	double 	fSlow65 = (0.1 * fslider17);
	double 	fSlow66 = (0.0010000000000000009 * fslider18);
	double 	fSlow67 = fslider19;
	double 	fSlow68 = (1 + ((fSlow20 - 1.0) / fSlow17));
	double 	fSlow69 = (1.0 / (1 + ((1.0 + fSlow20) / fSlow17)));
	double 	fSlow70 = (0 - fSlow29);
	double 	fSlow71 = (2 * (0 - fSlow27));
	double 	fSlow72 = (fConst3 * fslider20);
	double 	fSlow73 = (0.1 * fslider21);
	double 	fSlow74 = (0.0010000000000000009 * fslider22);
	double 	fSlow75 = fslider23;
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fVec0[0] = fTemp0;
		fRec11[0] = ((fSlow35 * (fVec0[0] + fVec0[1])) + (fSlow34 * fRec11[1]));
		fRec10[0] = (fRec11[0] - (fSlow32 * ((fSlow30 * fRec10[2]) + (fSlow28 * fRec10[1]))));
		double fTemp1 = (fRec10[2] + (fRec10[0] + (2 * fRec10[1])));
		double fTemp2 = (fSlow32 * fTemp1);
		fVec1[0] = fTemp2;
		fRec9[0] = ((fSlow36 * (fVec1[0] + fVec1[1])) + (fSlow25 * fRec9[1]));
		fRec8[0] = (fRec9[0] - (fSlow23 * ((fSlow21 * fRec8[2]) + (fSlow19 * fRec8[1]))));
		double fTemp3 = (fRec8[2] + (fRec8[0] + (2 * fRec8[1])));
		double fTemp4 = (fSlow23 * fTemp3);
		fVec2[0] = fTemp4;
		fRec7[0] = ((fSlow37 * (fVec2[0] + fVec2[1])) + (fSlow16 * fRec7[1]));
		fRec6[0] = (fRec7[0] - (fSlow14 * ((fSlow12 * fRec6[2]) + (fSlow10 * fRec6[1]))));
		double fTemp5 = (fRec6[2] + (fRec6[0] + (2 * fRec6[1])));
		double fTemp6 = (fSlow14 * fTemp5);
		fVec3[0] = fTemp6;
		fRec5[0] = ((fSlow38 * (fVec3[0] + fVec3[1])) + (fSlow7 * fRec5[1]));
		fRec4[0] = (fRec5[0] - (fSlow5 * ((fSlow4 * fRec4[2]) + (fSlow2 * fRec4[1]))));
		double fTemp7 = (fSlow5 * (fRec4[2] + (fRec4[0] + (2 * fRec4[1]))));
		fVec4[IOTA&65535] = fTemp7;
		double fTemp8 = (fSlow39 + fRec12[1]);
		fRec12[0] = (fTemp8 - floor(fTemp8));
		double fTemp9 = (65536 * (fRec12[0] - floor(fRec12[0])));
		double fTemp10 = floor(fTemp9);
		int iTemp11 = int(fTemp10);
		fRec14[0] = (fSlow41 + (0.999 * fRec14[1]));
		double fTemp12 = (fConst4 * (fRec14[0] * (1 + (fSlow40 * ((ftbl0[((1 + iTemp11) & 65535)] * (fTemp9 - fTemp10)) + (ftbl0[(iTemp11 & 65535)] * ((1 + fTemp10) - fTemp9)))))));
		int iTemp13 = int(fTemp12);
		int iTemp14 = (1 + iTemp13);
		double fTemp15 = (fSlow42 * (fVec4[IOTA&65535] + (fSlow42 * (((fTemp12 - iTemp13) * fVec4[(IOTA-int((int(iTemp14) & 65535)))&65535]) + ((iTemp14 - fTemp12) * fVec4[(IOTA-int((iTemp13 & 65535)))&65535])))));
		double 	fRec3 = max(fConst1, fabs(fTemp15));
		int iTemp16 = int((iRec1[1] < 4096));
		fRec0[0] = ((iTemp16)?max(fRec0[1], fRec3):fRec3);
		iRec1[0] = ((iTemp16)?(1 + iRec1[1]):1);
		fRec2[0] = ((iTemp16)?fRec2[1]:fRec0[1]);
		fbargraph0 = fRec2[0];
		fRec20[0] = ((fSlow38 * ((fSlow44 * fVec3[1]) + (fSlow43 * fTemp5))) + (fSlow7 * fRec20[1]));
		fRec19[0] = (fRec20[0] - (fSlow5 * ((fSlow4 * fRec19[2]) + (fSlow2 * fRec19[1]))));
		double fTemp17 = (fSlow5 * (((fSlow1 * fRec19[0]) + (fSlow45 * fRec19[1])) + (fSlow1 * fRec19[2])));
		fVec5[IOTA&65535] = fTemp17;
		double fTemp18 = (fSlow46 + fRec21[1]);
		fRec21[0] = (fTemp18 - floor(fTemp18));
		double fTemp19 = (65536 * (fRec21[0] - floor(fRec21[0])));
		double fTemp20 = floor(fTemp19);
		int iTemp21 = int(fTemp20);
		fRec22[0] = (fSlow48 + (0.999 * fRec22[1]));
		double fTemp22 = (fConst4 * (fRec22[0] * (1 + (fSlow47 * ((ftbl0[((1 + iTemp21) & 65535)] * (fTemp19 - fTemp20)) + (ftbl0[(iTemp21 & 65535)] * ((1 + fTemp20) - fTemp19)))))));
		int iTemp23 = int(fTemp22);
		int iTemp24 = (1 + iTemp23);
		double fTemp25 = (fSlow49 * (fVec5[IOTA&65535] + (fSlow49 * (((fTemp22 - iTemp23) * fVec5[(IOTA-int((int(iTemp24) & 65535)))&65535]) + ((iTemp24 - fTemp22) * fVec5[(IOTA-int((iTemp23 & 65535)))&65535])))));
		double 	fRec18 = max(fConst1, fabs(fTemp25));
		int iTemp26 = int((iRec16[1] < 4096));
		fRec15[0] = ((iTemp26)?max(fRec15[1], fRec18):fRec18);
		iRec16[0] = ((iTemp26)?(1 + iRec16[1]):1);
		fRec17[0] = ((iTemp26)?fRec17[1]:fRec15[1]);
		fbargraph1 = fRec17[0];
		double fTemp27 = (fSlow2 * fRec27[1]);
		fRec29[0] = ((fSlow37 * ((fSlow53 * fVec2[1]) + (fSlow52 * fTemp3))) + (fSlow16 * fRec29[1]));
		fRec28[0] = (fRec29[0] - (fSlow14 * ((fSlow12 * fRec28[2]) + (fSlow10 * fRec28[1]))));
		fRec27[0] = ((fSlow14 * (((fSlow9 * fRec28[0]) + (fSlow54 * fRec28[1])) + (fSlow9 * fRec28[2]))) - (fSlow51 * ((fSlow50 * fRec27[2]) + fTemp27)));
		double fTemp28 = (fRec27[2] + (fSlow51 * (fTemp27 + (fSlow50 * fRec27[0]))));
		fVec6[IOTA&65535] = fTemp28;
		double fTemp29 = (fSlow55 + fRec30[1]);
		fRec30[0] = (fTemp29 - floor(fTemp29));
		double fTemp30 = (65536 * (fRec30[0] - floor(fRec30[0])));
		double fTemp31 = floor(fTemp30);
		int iTemp32 = int(fTemp31);
		fRec31[0] = (fSlow57 + (0.999 * fRec31[1]));
		double fTemp33 = (fConst4 * (fRec31[0] * (1 + (fSlow56 * ((ftbl0[((1 + iTemp32) & 65535)] * (fTemp30 - fTemp31)) + (ftbl0[(iTemp32 & 65535)] * ((1 + fTemp31) - fTemp30)))))));
		int iTemp34 = int(fTemp33);
		int iTemp35 = (1 + iTemp34);
		double fTemp36 = (fSlow58 * (fVec6[IOTA&65535] + (fSlow58 * (((fTemp33 - iTemp34) * fVec6[(IOTA-int((int(iTemp35) & 65535)))&65535]) + ((iTemp35 - fTemp33) * fVec6[(IOTA-int((iTemp34 & 65535)))&65535])))));
		double 	fRec26 = max(fConst1, fabs(fTemp36));
		int iTemp37 = int((iRec24[1] < 4096));
		fRec23[0] = ((iTemp37)?max(fRec23[1], fRec26):fRec26);
		iRec24[0] = ((iTemp37)?(1 + iRec24[1]):1);
		fRec25[0] = ((iTemp37)?fRec25[1]:fRec23[1]);
		fbargraph2 = fRec25[0];
		double fTemp38 = (fSlow2 * fRec36[1]);
		double fTemp39 = (fSlow10 * fRec37[1]);
		fRec39[0] = ((fSlow36 * ((fSlow62 * fVec1[1]) + (fSlow61 * fTemp1))) + (fSlow25 * fRec39[1]));
		fRec38[0] = (fRec39[0] - (fSlow23 * ((fSlow21 * fRec38[2]) + (fSlow19 * fRec38[1]))));
		fRec37[0] = ((fSlow23 * (((fSlow18 * fRec38[0]) + (fSlow63 * fRec38[1])) + (fSlow18 * fRec38[2]))) - (fSlow60 * ((fSlow59 * fRec37[2]) + fTemp39)));
		fRec36[0] = ((fRec37[2] + (fSlow60 * (fTemp39 + (fSlow59 * fRec37[0])))) - (fSlow51 * ((fSlow50 * fRec36[2]) + fTemp38)));
		double fTemp40 = (fRec36[2] + (fSlow51 * (fTemp38 + (fSlow50 * fRec36[0]))));
		fVec7[IOTA&65535] = fTemp40;
		double fTemp41 = (fSlow64 + fRec40[1]);
		fRec40[0] = (fTemp41 - floor(fTemp41));
		double fTemp42 = (65536 * (fRec40[0] - floor(fRec40[0])));
		double fTemp43 = floor(fTemp42);
		int iTemp44 = int(fTemp43);
		fRec41[0] = (fSlow66 + (0.999 * fRec41[1]));
		double fTemp45 = (fConst4 * (fRec41[0] * (1 + (fSlow65 * ((ftbl0[((1 + iTemp44) & 65535)] * (fTemp42 - fTemp43)) + (ftbl0[(iTemp44 & 65535)] * ((1 + fTemp43) - fTemp42)))))));
		int iTemp46 = int(fTemp45);
		int iTemp47 = (1 + iTemp46);
		double fTemp48 = (fSlow67 * (fVec7[IOTA&65535] + (fSlow67 * (((fTemp45 - iTemp46) * fVec7[(IOTA-int((int(iTemp47) & 65535)))&65535]) + ((iTemp47 - fTemp45) * fVec7[(IOTA-int((iTemp46 & 65535)))&65535])))));
		double 	fRec35 = max(fConst1, fabs(fTemp48));
		int iTemp49 = int((iRec33[1] < 4096));
		fRec32[0] = ((iTemp49)?max(fRec32[1], fRec35):fRec35);
		iRec33[0] = ((iTemp49)?(1 + iRec33[1]):1);
		fRec34[0] = ((iTemp49)?fRec34[1]:fRec32[1]);
		fbargraph3 = fRec34[0];
		double fTemp50 = (fSlow2 * fRec46[1]);
		double fTemp51 = (fSlow10 * fRec47[1]);
		double fTemp52 = (fSlow19 * fRec48[1]);
		fRec50[0] = ((fSlow35 * ((fSlow70 * fVec0[1]) + (fSlow29 * fVec0[0]))) + (fSlow34 * fRec50[1]));
		fRec49[0] = (fRec50[0] - (fSlow32 * ((fSlow30 * fRec49[2]) + (fSlow28 * fRec49[1]))));
		fRec48[0] = ((fSlow32 * (((fSlow27 * fRec49[0]) + (fSlow71 * fRec49[1])) + (fSlow27 * fRec49[2]))) - (fSlow69 * ((fSlow68 * fRec48[2]) + fTemp52)));
		fRec47[0] = ((fRec48[2] + (fSlow69 * (fTemp52 + (fSlow68 * fRec48[0])))) - (fSlow60 * ((fSlow59 * fRec47[2]) + fTemp51)));
		fRec46[0] = ((fRec47[2] + (fSlow60 * (fTemp51 + (fSlow59 * fRec47[0])))) - (fSlow51 * ((fSlow50 * fRec46[2]) + fTemp50)));
		double fTemp53 = (fRec46[2] + (fSlow51 * (fTemp50 + (fSlow50 * fRec46[0]))));
		fVec8[IOTA&65535] = fTemp53;
		double fTemp54 = (fSlow72 + fRec51[1]);
		fRec51[0] = (fTemp54 - floor(fTemp54));
		double fTemp55 = (65536 * (fRec51[0] - floor(fRec51[0])));
		double fTemp56 = floor(fTemp55);
		int iTemp57 = int(fTemp56);
		fRec52[0] = (fSlow74 + (0.999 * fRec52[1]));
		double fTemp58 = (fConst4 * (fRec52[0] * (1 + (fSlow73 * ((ftbl0[((1 + iTemp57) & 65535)] * (fTemp55 - fTemp56)) + (ftbl0[(iTemp57 & 65535)] * ((1 + fTemp56) - fTemp55)))))));
		int iTemp59 = int(fTemp58);
		int iTemp60 = (1 + iTemp59);
		double fTemp61 = (fSlow75 * (fVec8[IOTA&65535] + (fSlow75 * (((fTemp58 - iTemp59) * fVec8[(IOTA-int((int(iTemp60) & 65535)))&65535]) + ((iTemp60 - fTemp58) * fVec8[(IOTA-int((iTemp59 & 65535)))&65535])))));
		double 	fRec45 = max(fConst1, fabs(fTemp61));
		int iTemp62 = int((iRec43[1] < 4096));
		fRec42[0] = ((iTemp62)?max(fRec42[1], fRec45):fRec45);
		iRec43[0] = ((iTemp62)?(1 + iRec43[1]):1);
		fRec44[0] = ((iTemp62)?fRec44[1]:fRec42[1]);
		fbargraph4 = fRec44[0];
		output0[i] = (FAUSTFLOAT)(fTemp61 + (fTemp48 + (fTemp36 + (fTemp25 + (fVec0[0] + fTemp15)))));
		// post processing
		fRec44[1] = fRec44[0];
		iRec43[1] = iRec43[0];
		fRec42[1] = fRec42[0];
		fRec52[1] = fRec52[0];
		fRec51[1] = fRec51[0];
		fRec46[2] = fRec46[1]; fRec46[1] = fRec46[0];
		fRec47[2] = fRec47[1]; fRec47[1] = fRec47[0];
		fRec48[2] = fRec48[1]; fRec48[1] = fRec48[0];
		fRec49[2] = fRec49[1]; fRec49[1] = fRec49[0];
		fRec50[1] = fRec50[0];
		fRec34[1] = fRec34[0];
		iRec33[1] = iRec33[0];
		fRec32[1] = fRec32[0];
		fRec41[1] = fRec41[0];
		fRec40[1] = fRec40[0];
		fRec36[2] = fRec36[1]; fRec36[1] = fRec36[0];
		fRec37[2] = fRec37[1]; fRec37[1] = fRec37[0];
		fRec38[2] = fRec38[1]; fRec38[1] = fRec38[0];
		fRec39[1] = fRec39[0];
		fRec25[1] = fRec25[0];
		iRec24[1] = iRec24[0];
		fRec23[1] = fRec23[0];
		fRec31[1] = fRec31[0];
		fRec30[1] = fRec30[0];
		fRec27[2] = fRec27[1]; fRec27[1] = fRec27[0];
		fRec28[2] = fRec28[1]; fRec28[1] = fRec28[0];
		fRec29[1] = fRec29[0];
		fRec17[1] = fRec17[0];
		iRec16[1] = iRec16[0];
		fRec15[1] = fRec15[0];
		fRec22[1] = fRec22[0];
		fRec21[1] = fRec21[0];
		fRec19[2] = fRec19[1]; fRec19[1] = fRec19[0];
		fRec20[1] = fRec20[0];
		fRec2[1] = fRec2[0];
		iRec1[1] = iRec1[0];
		fRec0[1] = fRec0[0];
		fRec14[1] = fRec14[0];
		fRec12[1] = fRec12[0];
		IOTA = IOTA+1;
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
	reg.registerVar("mbchor.crossover_b1_b2",N_("Crossover B1-B2 (hz)"),"SL",N_("Crossover bandpass frequency"),&fslider0, 8e+01, 2e+01, 2e+04, 1.08);
	reg.registerVar("mbchor.crossover_b2_b3",N_("Crossover B2-B3 (hz)"),"SL",N_("Crossover bandpass frequency"),&fslider1, 2.1e+02, 2e+01, 2e+04, 1.08);
	reg.registerVar("mbchor.crossover_b3_b4",N_("Crossover B3-B4 (hz)"),"SL",N_("Crossover bandpass frequency"),&fslider2, 1.7e+03, 2e+01, 2e+04, 1.08);
	reg.registerVar("mbchor.crossover_b4_b5",N_("Crossover B4-B5 (hz)"),"SL",N_("Crossover bandpass frequency"),&fslider3, 5e+03, 2e+01, 2e+04, 1.08);
	reg.registerVar("mbchor.delay1","","S","",&fslider6, 0.02, 0.0, 0.2, 0.01);
	reg.registerVar("mbchor.delay2","","S","",&fslider10, 0.04, 0.0, 0.2, 0.01);
	reg.registerVar("mbchor.delay3","","S","",&fslider14, 0.06, 0.0, 0.2, 0.01);
	reg.registerVar("mbchor.delay4","","S","",&fslider18, 0.08, 0.0, 0.2, 0.01);
	reg.registerVar("mbchor.delay5","","S","",&fslider22, 0.1, 0.0, 0.2, 0.01);
	reg.registerVar("mbchor.depth1","","S","",&fslider5, 0.02, 0.01, 1.0, 0.01);
	reg.registerVar("mbchor.depth2","","S","",&fslider9, 0.04, 0.01, 1.0, 0.01);
	reg.registerVar("mbchor.depth3","","S","",&fslider13, 0.06, 0.01, 1.0, 0.01);
	reg.registerVar("mbchor.depth4","","S","",&fslider17, 0.08, 0.01, 1.0, 0.01);
	reg.registerVar("mbchor.depth5","","S","",&fslider21, 0.1, 0.01, 1.0, 0.01);
	reg.registerVar("mbchor.freq1","","S",N_("Beats per Minute"),&fslider4, 3e+01, 24.0, 3.6e+02, 1.0);
	reg.registerVar("mbchor.freq2","","S",N_("Beats per Minute"),&fslider8, 6e+01, 24.0, 3.6e+02, 1.0);
	reg.registerVar("mbchor.freq3","","S",N_("Beats per Minute"),&fslider12, 9e+01, 24.0, 3.6e+02, 1.0);
	reg.registerVar("mbchor.freq4","","S",N_("Beats per Minute"),&fslider16, 1.2e+02, 24.0, 3.6e+02, 1.0);
	reg.registerVar("mbchor.freq5","","S",N_("Beats per Minute"),&fslider20, 1.5e+02, 24.0, 3.6e+02, 1.0);
	reg.registerVar("mbchor.level1","","S","",&fslider7, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("mbchor.level2","","S","",&fslider11, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("mbchor.level3","","S","",&fslider15, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("mbchor.level4","","S","",&fslider19, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("mbchor.level5","","S","",&fslider23, 0.5, 0.0, 1.0, 0.01);
	reg.registerNonMidiFloatVar("mbchor.v1",&fbargraph0, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbchor.v2",&fbargraph1, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbchor.v3",&fbargraph2, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbchor.v4",&fbargraph3, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbchor.v5",&fbargraph4, false, true, -70.0, -70.0, 4.0, 0.00001);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("mbchor" "." p)

b.openHorizontalhideBox("");
b.closeBox();

b.openHorizontalBox("");
b.openVerticalBox("");

b.openTabBox("");

b.openHorizontalBox(N_("Band 1"));
b.openVerticalBox("");
b.openpaintampBox("");
b.openHorizontalBox("");
b.openVerticalBox("");
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("level1"), N_("Level"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("freq1"), N_("BPM"));
b.closeBox();
b.openVerticalBox("");
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("delay1"), N_("Delay"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("depth1"), N_("Depth"));
b.closeBox();
b.openVerticalBox("");
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b1_b2"), N_("Low Shelf (Hz)"));
b.closeBox();
b.closeBox();
b.closeBox();
b.closeBox();
b.closeBox();

b.openHorizontalBox(N_("Band 2"));
b.openVerticalBox("");
b.openpaintampBox("");
b.openHorizontalBox("");
b.openVerticalBox("");
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("level2"), N_("Level"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("freq2"), N_("BPM"));
b.closeBox();
b.openVerticalBox("");
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("delay2"), N_("Delay"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("depth2"), N_("Depth"));
b.closeBox();
b.openVerticalBox("");
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b1_b2"), N_("Low (Hz)"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b2_b3"), N_("High (hz)"));
b.closeBox();
b.closeBox();
b.closeBox();
b.closeBox();
b.closeBox();

b.openHorizontalBox(N_("Band 3"));
b.openVerticalBox("");
b.openpaintampBox("");
b.openHorizontalBox("");
b.openVerticalBox("");
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("level3"), N_("Level"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("freq3"), N_("BPM"));
b.closeBox();
b.openVerticalBox("");
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("delay3"), N_("Delay"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("depth3"), N_("Depth"));
b.closeBox();
b.openVerticalBox("");
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b2_b3"), N_("Low (Hz)"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b3_b4"), N_("High (hz)"));
b.closeBox();
b.closeBox();
b.closeBox();
b.closeBox();
b.closeBox();

b.openHorizontalBox(N_("Band 4"));
b.openVerticalBox("");
b.openpaintampBox("");
b.openHorizontalBox("");
b.openVerticalBox("");
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("level4"), N_("Level"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("freq4"), N_("BPM"));
b.closeBox();
b.openVerticalBox("");
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("delay4"), N_("Delay"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("depth4"), N_("Depth"));
b.closeBox();
b.openVerticalBox("");
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b3_b4"), N_("Low (Hz)"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b4_b5"), N_("High (hz)"));
b.closeBox();
b.closeBox();
b.closeBox();
b.closeBox();
b.closeBox();

b.openHorizontalBox(N_("Band 5"));
b.openVerticalBox("");
b.openpaintampBox("");
b.openHorizontalBox("");
b.openVerticalBox("");
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("level5"), N_("Level"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("freq5"), N_("BPM"));
b.closeBox();
b.openVerticalBox("");
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("delay5"), N_("Delay"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("depth5"), N_("Depth"));
b.closeBox();
b.openVerticalBox("");
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b4_b5"), N_("High Shelf (Hz)"));
b.closeBox();
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

} // end namespace mbchor
} // end namespace pluginlib
