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
		int 	iRec4[2];
	  public:
		int getNumInputs() 	{ return 0; }
		int getNumOutputs() 	{ return 1; }
		void init(int samplingFreq) {
			fSamplingFreq = samplingFreq;
			for (int i=0; i<2; i++) iRec4[i] = 0;
		}
		void fill (int count, double output[]) {
			for (int i=0; i<count; i++) {
				iRec4[0] = (1 + iRec4[1]);
				output[i] = sin((9.587379924285257e-05 * (iRec4[0] - 1)));
				// post processing
				iRec4[1] = iRec4[0];
			}
		}
	};
			int 	iConst0;
	double 	fConst1;
	FAUSTFLOAT 	fslider0;
	double 	fConst2;
	double 	fVec0[2];
	double 	fRec2[2];
	double 	fRec1[3];
	int 	IOTA;
	double 	fVec1[65536];
	FAUSTFLOAT 	fslider1;
	double 	fConst3;
	double 	fRec3[2];
	static double 	ftbl0[65536];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT 	fslider3;
	double 	fRec5[2];
	double 	fConst4;
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT 	fbargraph0;
	FAUSTFLOAT 	fslider5;
	double 	fRec10[2];
	double 	fRec9[3];
	double 	fVec2[2];
	double 	fRec8[2];
	double 	fRec7[3];
	double 	fVec3[65536];
	FAUSTFLOAT 	fslider6;
	double 	fRec11[2];
	FAUSTFLOAT 	fslider7;
	FAUSTFLOAT 	fslider8;
	double 	fRec12[2];
	FAUSTFLOAT 	fslider9;
	FAUSTFLOAT 	fbargraph1;
	FAUSTFLOAT 	fslider10;
	double 	fRec17[2];
	double 	fRec16[3];
	double 	fVec4[2];
	double 	fRec15[2];
	double 	fRec14[3];
	double 	fVec5[65536];
	FAUSTFLOAT 	fslider11;
	double 	fRec18[2];
	FAUSTFLOAT 	fslider12;
	FAUSTFLOAT 	fslider13;
	double 	fRec19[2];
	FAUSTFLOAT 	fslider14;
	FAUSTFLOAT 	fbargraph2;
	FAUSTFLOAT 	fslider15;
	double 	fRec24[2];
	double 	fRec23[3];
	double 	fVec6[2];
	double 	fRec22[2];
	double 	fRec21[3];
	double 	fVec7[65536];
	FAUSTFLOAT 	fslider16;
	double 	fRec25[2];
	FAUSTFLOAT 	fslider17;
	FAUSTFLOAT 	fslider18;
	double 	fRec26[2];
	FAUSTFLOAT 	fslider19;
	FAUSTFLOAT 	fbargraph3;
	double 	fRec29[2];
	double 	fRec28[3];
	double 	fVec8[65536];
	FAUSTFLOAT 	fslider20;
	double 	fRec30[2];
	FAUSTFLOAT 	fslider21;
	FAUSTFLOAT 	fslider22;
	double 	fRec31[2];
	FAUSTFLOAT 	fslider23;
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
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<3; i++) fRec1[i] = 0;
	for (int i=0; i<65536; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<3; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<3; i++) fRec7[i] = 0;
	for (int i=0; i<65536; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<3; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<3; i++) fRec14[i] = 0;
	for (int i=0; i<65536; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<3; i++) fRec23[i] = 0;
	for (int i=0; i<2; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<3; i++) fRec21[i] = 0;
	for (int i=0; i<65536; i++) fVec7[i] = 0;
	for (int i=0; i<2; i++) fRec25[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<2; i++) fRec29[i] = 0;
	for (int i=0; i<3; i++) fRec28[i] = 0;
	for (int i=0; i<65536; i++) fVec8[i] = 0;
	for (int i=0; i<2; i++) fRec30[i] = 0;
	for (int i=0; i<2; i++) fRec31[i] = 0;
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

void always_inline Dsp::compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = tan((fConst2 * fslider0));
	double 	fSlow1 = (1.0 / faustpower<2>(fSlow0));
	double 	fSlow2 = (2 * (1 - fSlow1));
	double 	fSlow3 = (1.0 / fSlow0);
	double 	fSlow4 = (1 + ((fSlow3 - 1.0000000000000004) / fSlow0));
	double 	fSlow5 = (1 + ((1.0000000000000004 + fSlow3) / fSlow0));
	double 	fSlow6 = (1.0 / fSlow5);
	double 	fSlow7 = (1 + fSlow3);
	double 	fSlow8 = (0 - ((1 - fSlow3) / fSlow7));
	double 	fSlow9 = (0 - fSlow3);
	double 	fSlow10 = (1.0 / fSlow7);
	double 	fSlow11 = (2 * (0 - fSlow1));
	double 	fSlow12 = (fConst3 * fslider1);
	double 	fSlow13 = (0.1 * fslider2);
	double 	fSlow14 = (0.0010000000000000009 * fslider3);
	double 	fSlow15 = fslider4;
	double 	fSlow16 = tan((fConst2 * fslider5));
	double 	fSlow17 = (1.0 / faustpower<2>(fSlow16));
	double 	fSlow18 = (2 * (1 - fSlow17));
	double 	fSlow19 = (1.0 / fSlow16);
	double 	fSlow20 = (1 + ((fSlow19 - 1.0000000000000004) / fSlow16));
	double 	fSlow21 = (1 + ((1.0000000000000004 + fSlow19) / fSlow16));
	double 	fSlow22 = (1.0 / fSlow21);
	double 	fSlow23 = (1 + fSlow19);
	double 	fSlow24 = (0 - ((1 - fSlow19) / fSlow23));
	double 	fSlow25 = (1.0 / (fSlow5 * fSlow16));
	double 	fSlow26 = (0 - fSlow19);
	double 	fSlow27 = (1.0 / fSlow23);
	double 	fSlow28 = (2 * (0 - fSlow17));
	double 	fSlow29 = (fConst3 * fslider6);
	double 	fSlow30 = (0.1 * fslider7);
	double 	fSlow31 = (0.0010000000000000009 * fslider8);
	double 	fSlow32 = fslider9;
	double 	fSlow33 = tan((fConst2 * fslider10));
	double 	fSlow34 = (1.0 / faustpower<2>(fSlow33));
	double 	fSlow35 = (2 * (1 - fSlow34));
	double 	fSlow36 = (1.0 / fSlow33);
	double 	fSlow37 = (1 + ((fSlow36 - 1.0000000000000004) / fSlow33));
	double 	fSlow38 = (1 + ((1.0000000000000004 + fSlow36) / fSlow33));
	double 	fSlow39 = (1.0 / fSlow38);
	double 	fSlow40 = (1 + fSlow36);
	double 	fSlow41 = (0 - ((1 - fSlow36) / fSlow40));
	double 	fSlow42 = (1.0 / (fSlow21 * fSlow33));
	double 	fSlow43 = (0 - fSlow36);
	double 	fSlow44 = (1.0 / fSlow40);
	double 	fSlow45 = (2 * (0 - fSlow34));
	double 	fSlow46 = (fConst3 * fslider11);
	double 	fSlow47 = (0.1 * fslider12);
	double 	fSlow48 = (0.0010000000000000009 * fslider13);
	double 	fSlow49 = fslider14;
	double 	fSlow50 = tan((fConst2 * fslider15));
	double 	fSlow51 = (1.0 / faustpower<2>(fSlow50));
	double 	fSlow52 = (2 * (1 - fSlow51));
	double 	fSlow53 = (1.0 / fSlow50);
	double 	fSlow54 = (1 + ((fSlow53 - 1.0000000000000004) / fSlow50));
	double 	fSlow55 = (1.0 / (1 + ((1.0000000000000004 + fSlow53) / fSlow50)));
	double 	fSlow56 = (1 + fSlow53);
	double 	fSlow57 = (0 - ((1 - fSlow53) / fSlow56));
	double 	fSlow58 = (1.0 / (fSlow38 * fSlow50));
	double 	fSlow59 = (0 - fSlow53);
	double 	fSlow60 = (1.0 / fSlow56);
	double 	fSlow61 = (2 * (0 - fSlow51));
	double 	fSlow62 = (fConst3 * fslider16);
	double 	fSlow63 = (0.1 * fslider17);
	double 	fSlow64 = (0.0010000000000000009 * fslider18);
	double 	fSlow65 = fslider19;
	double 	fSlow66 = (fConst3 * fslider20);
	double 	fSlow67 = (0.1 * fslider21);
	double 	fSlow68 = (0.0010000000000000009 * fslider22);
	double 	fSlow69 = fslider23;
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fVec0[0] = fTemp0;
		fRec2[0] = ((fSlow10 * ((fSlow9 * fVec0[1]) + (fSlow3 * fVec0[0]))) + (fSlow8 * fRec2[1]));
		fRec1[0] = (fRec2[0] - (fSlow6 * ((fSlow4 * fRec1[2]) + (fSlow2 * fRec1[1]))));
		double fTemp1 = (fSlow6 * (((fSlow1 * fRec1[0]) + (fSlow11 * fRec1[1])) + (fSlow1 * fRec1[2])));
		fVec1[IOTA&65535] = fTemp1;
		double fTemp2 = (fSlow12 + fRec3[1]);
		fRec3[0] = (fTemp2 - floor(fTemp2));
		double fTemp3 = (65536 * (fRec3[0] - floor(fRec3[0])));
		double fTemp4 = floor(fTemp3);
		int iTemp5 = int(fTemp4);
		fRec5[0] = (fSlow14 + (0.999 * fRec5[1]));
		double fTemp6 = (fConst4 * (fRec5[0] * (1 + (fSlow13 * ((ftbl0[((1 + iTemp5) & 65535)] * (fTemp3 - fTemp4)) + (ftbl0[(iTemp5 & 65535)] * ((1 + fTemp4) - fTemp3)))))));
		int iTemp7 = int(fTemp6);
		int iTemp8 = (1 + iTemp7);
		double fTemp9 = (fSlow15 * (fVec1[IOTA&65535] + (fSlow15 * (((fTemp6 - iTemp7) * fVec1[(IOTA-int((int(iTemp8) & 65535)))&65535]) + ((iTemp8 - fTemp6) * fVec1[(IOTA-int((iTemp7 & 65535)))&65535])))));
		double 	fRec0 = max(fConst1, fabs(fTemp9));
		fbargraph0 = fRec0;
		double fTemp10 = (fVec0[0] + fVec0[1]);
		fRec10[0] = ((fSlow10 * fTemp10) + (fSlow8 * fRec10[1]));
		fRec9[0] = (fRec10[0] - (fSlow6 * ((fSlow4 * fRec9[2]) + (fSlow2 * fRec9[1]))));
		double fTemp11 = (fRec9[2] + (fRec9[0] + (2 * fRec9[1])));
		fVec2[0] = (fSlow6 * fTemp11);
		fRec8[0] = ((fSlow27 * ((fSlow26 * fVec2[1]) + (fSlow25 * fTemp11))) + (fSlow24 * fRec8[1]));
		fRec7[0] = (fRec8[0] - (fSlow22 * ((fSlow20 * fRec7[2]) + (fSlow18 * fRec7[1]))));
		double fTemp12 = (fSlow22 * (((fSlow17 * fRec7[0]) + (fSlow28 * fRec7[1])) + (fSlow17 * fRec7[2])));
		fVec3[IOTA&65535] = fTemp12;
		double fTemp13 = (fSlow29 + fRec11[1]);
		fRec11[0] = (fTemp13 - floor(fTemp13));
		double fTemp14 = (65536 * (fRec11[0] - floor(fRec11[0])));
		double fTemp15 = floor(fTemp14);
		int iTemp16 = int(fTemp15);
		fRec12[0] = (fSlow31 + (0.999 * fRec12[1]));
		double fTemp17 = (fConst4 * (fRec12[0] * (1 + (fSlow30 * ((ftbl0[((1 + iTemp16) & 65535)] * (fTemp14 - fTemp15)) + (ftbl0[(iTemp16 & 65535)] * ((1 + fTemp15) - fTemp14)))))));
		int iTemp18 = int(fTemp17);
		int iTemp19 = (1 + iTemp18);
		double fTemp20 = (fSlow32 * (fVec3[IOTA&65535] + (fSlow32 * (((fTemp17 - iTemp18) * fVec3[(IOTA-int((int(iTemp19) & 65535)))&65535]) + ((iTemp19 - fTemp17) * fVec3[(IOTA-int((iTemp18 & 65535)))&65535])))));
		double 	fRec6 = max(fConst1, fabs(fTemp20));
		fbargraph1 = fRec6;
		fRec17[0] = ((fSlow27 * fTemp10) + (fSlow24 * fRec17[1]));
		fRec16[0] = (fRec17[0] - (fSlow22 * ((fSlow20 * fRec16[2]) + (fSlow18 * fRec16[1]))));
		double fTemp21 = (fRec16[2] + (fRec16[0] + (2 * fRec16[1])));
		fVec4[0] = (fSlow22 * fTemp21);
		fRec15[0] = ((fSlow44 * ((fSlow43 * fVec4[1]) + (fSlow42 * fTemp21))) + (fSlow41 * fRec15[1]));
		fRec14[0] = (fRec15[0] - (fSlow39 * ((fSlow37 * fRec14[2]) + (fSlow35 * fRec14[1]))));
		double fTemp22 = (fSlow39 * (((fSlow34 * fRec14[0]) + (fSlow45 * fRec14[1])) + (fSlow34 * fRec14[2])));
		fVec5[IOTA&65535] = fTemp22;
		double fTemp23 = (fSlow46 + fRec18[1]);
		fRec18[0] = (fTemp23 - floor(fTemp23));
		double fTemp24 = (65536 * (fRec18[0] - floor(fRec18[0])));
		double fTemp25 = floor(fTemp24);
		int iTemp26 = int(fTemp25);
		fRec19[0] = (fSlow48 + (0.999 * fRec19[1]));
		double fTemp27 = (fConst4 * (fRec19[0] * (1 + (fSlow47 * ((ftbl0[((1 + iTemp26) & 65535)] * (fTemp24 - fTemp25)) + (ftbl0[(iTemp26 & 65535)] * ((1 + fTemp25) - fTemp24)))))));
		int iTemp28 = int(fTemp27);
		int iTemp29 = (1 + iTemp28);
		double fTemp30 = (fSlow49 * (fVec5[IOTA&65535] + (fSlow49 * (((fTemp27 - iTemp28) * fVec5[(IOTA-int((int(iTemp29) & 65535)))&65535]) + ((iTemp29 - fTemp27) * fVec5[(IOTA-int((iTemp28 & 65535)))&65535])))));
		double 	fRec13 = max(fConst1, fabs(fTemp30));
		fbargraph2 = fRec13;
		fRec24[0] = ((fSlow44 * fTemp10) + (fSlow41 * fRec24[1]));
		fRec23[0] = (fRec24[0] - (fSlow39 * ((fSlow37 * fRec23[2]) + (fSlow35 * fRec23[1]))));
		double fTemp31 = (fRec23[2] + (fRec23[0] + (2 * fRec23[1])));
		fVec6[0] = (fSlow39 * fTemp31);
		fRec22[0] = ((fSlow60 * ((fSlow59 * fVec6[1]) + (fSlow58 * fTemp31))) + (fSlow57 * fRec22[1]));
		fRec21[0] = (fRec22[0] - (fSlow55 * ((fSlow54 * fRec21[2]) + (fSlow52 * fRec21[1]))));
		double fTemp32 = (fSlow55 * (((fSlow51 * fRec21[0]) + (fSlow61 * fRec21[1])) + (fSlow51 * fRec21[2])));
		fVec7[IOTA&65535] = fTemp32;
		double fTemp33 = (fSlow62 + fRec25[1]);
		fRec25[0] = (fTemp33 - floor(fTemp33));
		double fTemp34 = (65536 * (fRec25[0] - floor(fRec25[0])));
		double fTemp35 = floor(fTemp34);
		int iTemp36 = int(fTemp35);
		fRec26[0] = (fSlow64 + (0.999 * fRec26[1]));
		double fTemp37 = (fConst4 * (fRec26[0] * (1 + (fSlow63 * ((ftbl0[((1 + iTemp36) & 65535)] * (fTemp34 - fTemp35)) + (ftbl0[(iTemp36 & 65535)] * ((1 + fTemp35) - fTemp34)))))));
		int iTemp38 = int(fTemp37);
		int iTemp39 = (1 + iTemp38);
		double fTemp40 = (fSlow65 * (fVec7[IOTA&65535] + (fSlow65 * (((fTemp37 - iTemp38) * fVec7[(IOTA-int((int(iTemp39) & 65535)))&65535]) + ((iTemp39 - fTemp37) * fVec7[(IOTA-int((iTemp38 & 65535)))&65535])))));
		double 	fRec20 = max(fConst1, fabs(fTemp40));
		fbargraph3 = fRec20;
		fRec29[0] = ((fSlow60 * fTemp10) + (fSlow57 * fRec29[1]));
		fRec28[0] = (fRec29[0] - (fSlow55 * ((fSlow54 * fRec28[2]) + (fSlow52 * fRec28[1]))));
		double fTemp41 = (fSlow55 * (fRec28[2] + (fRec28[0] + (2 * fRec28[1]))));
		fVec8[IOTA&65535] = fTemp41;
		double fTemp42 = (fSlow66 + fRec30[1]);
		fRec30[0] = (fTemp42 - floor(fTemp42));
		double fTemp43 = (65536 * (fRec30[0] - floor(fRec30[0])));
		double fTemp44 = floor(fTemp43);
		int iTemp45 = int(fTemp44);
		fRec31[0] = (fSlow68 + (0.999 * fRec31[1]));
		double fTemp46 = (fConst4 * (fRec31[0] * (1 + (fSlow67 * ((ftbl0[((1 + iTemp45) & 65535)] * (fTemp43 - fTemp44)) + (ftbl0[(iTemp45 & 65535)] * ((1 + fTemp44) - fTemp43)))))));
		int iTemp47 = int(fTemp46);
		int iTemp48 = (1 + iTemp47);
		double fTemp49 = (fSlow69 * (fVec8[IOTA&65535] + (fSlow69 * (((fTemp46 - iTemp47) * fVec8[(IOTA-int((int(iTemp48) & 65535)))&65535]) + ((iTemp48 - fTemp46) * fVec8[(IOTA-int((iTemp47 & 65535)))&65535])))));
		double 	fRec27 = max(fConst1, fabs(fTemp49));
		fbargraph4 = fRec27;
		output0[i] = (FAUSTFLOAT)(fTemp49 + (fTemp40 + (fTemp30 + (fTemp20 + (fVec0[0] + fTemp9)))));
		// post processing
		fRec31[1] = fRec31[0];
		fRec30[1] = fRec30[0];
		fRec28[2] = fRec28[1]; fRec28[1] = fRec28[0];
		fRec29[1] = fRec29[0];
		fRec26[1] = fRec26[0];
		fRec25[1] = fRec25[0];
		fRec21[2] = fRec21[1]; fRec21[1] = fRec21[0];
		fRec22[1] = fRec22[0];
		fVec6[1] = fVec6[0];
		fRec23[2] = fRec23[1]; fRec23[1] = fRec23[0];
		fRec24[1] = fRec24[0];
		fRec19[1] = fRec19[0];
		fRec18[1] = fRec18[0];
		fRec14[2] = fRec14[1]; fRec14[1] = fRec14[0];
		fRec15[1] = fRec15[0];
		fVec4[1] = fVec4[0];
		fRec16[2] = fRec16[1]; fRec16[1] = fRec16[0];
		fRec17[1] = fRec17[0];
		fRec12[1] = fRec12[0];
		fRec11[1] = fRec11[0];
		fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
		fVec2[1] = fVec2[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec10[1] = fRec10[0];
		fRec5[1] = fRec5[0];
		fRec3[1] = fRec3[0];
		IOTA = IOTA+1;
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fVec0[1] = fVec0[0];
	}
}

void __rt_func Dsp::compute_static(int count, float *input0, float *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("mbchor.crossover_b1_b2",N_("Crossover B1-B2 (hz)"),"SL",N_("Crossover bandpass frequency"),&fslider15, 8e+01, 2e+01, 2e+04, 1.08);
	reg.registerVar("mbchor.crossover_b2_b3",N_("Crossover B2-B3 (hz)"),"SL",N_("Crossover bandpass frequency"),&fslider10, 2.1e+02, 2e+01, 2e+04, 1.08);
	reg.registerVar("mbchor.crossover_b3_b4",N_("Crossover B3-B4 (hz)"),"SL",N_("Crossover bandpass frequency"),&fslider5, 1.7e+03, 2e+01, 2e+04, 1.08);
	reg.registerVar("mbchor.crossover_b4_b5",N_("Crossover B4-B5 (hz)"),"SL",N_("Crossover bandpass frequency"),&fslider0, 5e+03, 2e+01, 2e+04, 1.08);
	reg.registerVar("mbchor.delay1","","S","",&fslider22, 0.02, 0.0, 0.2, 0.01);
	reg.registerVar("mbchor.delay2","","S","",&fslider18, 0.04, 0.0, 0.2, 0.01);
	reg.registerVar("mbchor.delay3","","S","",&fslider13, 0.06, 0.0, 0.2, 0.01);
	reg.registerVar("mbchor.delay4","","S","",&fslider8, 0.08, 0.0, 0.2, 0.01);
	reg.registerVar("mbchor.delay5","","S","",&fslider3, 0.1, 0.0, 0.2, 0.01);
	reg.registerVar("mbchor.depth1","","S","",&fslider21, 0.02, 0.01, 1.0, 0.01);
	reg.registerVar("mbchor.depth2","","S","",&fslider17, 0.04, 0.01, 1.0, 0.01);
	reg.registerVar("mbchor.depth3","","S","",&fslider12, 0.06, 0.01, 1.0, 0.01);
	reg.registerVar("mbchor.depth4","","S","",&fslider7, 0.08, 0.01, 1.0, 0.01);
	reg.registerVar("mbchor.depth5","","S","",&fslider2, 0.1, 0.01, 1.0, 0.01);
	reg.registerVar("mbchor.freq1","","S",N_("Beats per Minute"),&fslider20, 3e+01, 24.0, 3.6e+02, 1.0);
	reg.registerVar("mbchor.freq2","","S",N_("Beats per Minute"),&fslider16, 6e+01, 24.0, 3.6e+02, 1.0);
	reg.registerVar("mbchor.freq3","","S",N_("Beats per Minute"),&fslider11, 9e+01, 24.0, 3.6e+02, 1.0);
	reg.registerVar("mbchor.freq4","","S",N_("Beats per Minute"),&fslider6, 1.2e+02, 24.0, 3.6e+02, 1.0);
	reg.registerVar("mbchor.freq5","","S",N_("Beats per Minute"),&fslider1, 1.5e+02, 24.0, 3.6e+02, 1.0);
	reg.registerVar("mbchor.level1","","S","",&fslider23, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("mbchor.level2","","S","",&fslider19, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("mbchor.level3","","S","",&fslider14, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("mbchor.level4","","S","",&fslider9, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("mbchor.level5","","S","",&fslider4, 0.5, 0.0, 1.0, 0.01);
	reg.registerNonMidiFloatVar("mbchor.v1",&fbargraph4, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbchor.v2",&fbargraph3, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbchor.v3",&fbargraph2, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbchor.v4",&fbargraph1, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbchor.v5",&fbargraph0, false, true, -70.0, -70.0, 4.0, 0.00001);
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

b.openHorizontalBox(N_("Band 2"));
b.openVerticalBox("");
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

b.openHorizontalBox(N_("Band 3"));
b.openVerticalBox("");
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

b.openHorizontalBox(N_("Band 4"));
b.openVerticalBox("");
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

b.openHorizontalBox(N_("Band 5"));
b.openVerticalBox("");
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
b.create_simple_meter(PARAM("v1"));
b.create_simple_meter(PARAM("v2"));
b.create_simple_meter(PARAM("v3"));
b.create_simple_meter(PARAM("v4"));
b.create_simple_meter(PARAM("v5"));
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
