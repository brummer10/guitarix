// generated from file '../src/faust/gx_ampmodul.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "valve.h"

namespace gx_ampmodul {

class Dsp: public PluginDef {
private:
	gx_resample::FixedRateResampler smp;
	gx_resample::FixedRateResampler smps;
	int sample_rate;
	int fSampleRate;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT fHslider0;
	double fRec0[6];
	FAUSTFLOAT fHslider1;
	double fConst0;
	double fConst1;
	double fConst2;
	FAUSTFLOAT fVslider1;
	double fRec13[2];
	double fVec0[2];
	double fRec12[2];
	double fRec11[3];
	double fConst3;
	double fConst4;
	double fConst5;
	double fRec14[2];
	double fRec10[3];
	double fConst6;
	double fRec9[2];
	FAUSTFLOAT fVslider2;
	double fRec15[2];
	double fVec1[2];
	double fRec8[2];
	double fRec7[3];
	double fConst7;
	double fConst8;
	double fConst9;
	double fRec16[2];
	double fRec6[3];
	double fRec5[2];
	FAUSTFLOAT fVslider3;
	double fRec17[2];
	double fVec2[2];
	double fRec4[2];
	double fRec3[3];
	double fConst10;
	double fConst11;
	double fConst12;
	double fRec18[2];
	double fRec2[3];
	double fRec1[6];
	double fRec19[6];
	double fVec3[2];
	double fRec31[2];
	double fRec30[3];
	double fRec32[2];
	double fRec29[3];
	double fRec28[2];
	double fVec4[2];
	double fRec27[2];
	double fRec26[3];
	double fRec33[2];
	double fRec25[3];
	double fRec24[2];
	double fVec5[2];
	double fRec23[2];
	double fRec22[3];
	double fRec34[2];
	double fRec21[3];
	double fRec20[6];

	void clear_state_f();
	int load_ui_f(const UiBuilder& b, int form);
	static const char *glade_def;
	void init(unsigned int sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static int load_ui_f_static(const UiBuilder& b, int form);
	static void init_static(unsigned int sample_rate, PluginDef*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginDef*);
	static int register_params_static(const ParamReg& reg);
	static void del_instance(PluginDef *p);
public:
	Dsp();
	~Dsp();
};



static const char* parm_groups[] = {
	"amp2.stage2", N_("Postamp Tube2"),
	"amp2.stage1", N_("Postamp Tube1"),
	0
	};

Dsp::Dsp()
	: PluginDef() {
	version = PLUGINDEF_VERSION;
	flags = 0;
	id = "ampmodul";
	name = N_("Postamp");
	groups = parm_groups;
	description = ""; // description (tooltip)
	category = N_("Distortion");       // category
	shortname = "";     // shortname
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
	for (int l0 = 0; (l0 < 6); l0 = (l0 + 1)) fRec0[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec13[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fVec0[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fRec12[l3] = 0.0;
	for (int l4 = 0; (l4 < 3); l4 = (l4 + 1)) fRec11[l4] = 0.0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fRec14[l5] = 0.0;
	for (int l6 = 0; (l6 < 3); l6 = (l6 + 1)) fRec10[l6] = 0.0;
	for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) fRec9[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fRec15[l8] = 0.0;
	for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) fVec1[l9] = 0.0;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) fRec8[l10] = 0.0;
	for (int l11 = 0; (l11 < 3); l11 = (l11 + 1)) fRec7[l11] = 0.0;
	for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) fRec16[l12] = 0.0;
	for (int l13 = 0; (l13 < 3); l13 = (l13 + 1)) fRec6[l13] = 0.0;
	for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) fRec5[l14] = 0.0;
	for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) fRec17[l15] = 0.0;
	for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) fVec2[l16] = 0.0;
	for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) fRec4[l17] = 0.0;
	for (int l18 = 0; (l18 < 3); l18 = (l18 + 1)) fRec3[l18] = 0.0;
	for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) fRec18[l19] = 0.0;
	for (int l20 = 0; (l20 < 3); l20 = (l20 + 1)) fRec2[l20] = 0.0;
	for (int l21 = 0; (l21 < 6); l21 = (l21 + 1)) fRec1[l21] = 0.0;
	for (int l22 = 0; (l22 < 6); l22 = (l22 + 1)) fRec19[l22] = 0.0;
	for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) fVec3[l23] = 0.0;
	for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) fRec31[l24] = 0.0;
	for (int l25 = 0; (l25 < 3); l25 = (l25 + 1)) fRec30[l25] = 0.0;
	for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) fRec32[l26] = 0.0;
	for (int l27 = 0; (l27 < 3); l27 = (l27 + 1)) fRec29[l27] = 0.0;
	for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) fRec28[l28] = 0.0;
	for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) fVec4[l29] = 0.0;
	for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) fRec27[l30] = 0.0;
	for (int l31 = 0; (l31 < 3); l31 = (l31 + 1)) fRec26[l31] = 0.0;
	for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) fRec33[l32] = 0.0;
	for (int l33 = 0; (l33 < 3); l33 = (l33 + 1)) fRec25[l33] = 0.0;
	for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) fRec24[l34] = 0.0;
	for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) fVec5[l35] = 0.0;
	for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) fRec23[l36] = 0.0;
	for (int l37 = 0; (l37 < 3); l37 = (l37 + 1)) fRec22[l37] = 0.0;
	for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) fRec34[l38] = 0.0;
	for (int l39 = 0; (l39 < 3); l39 = (l39 + 1)) fRec21[l39] = 0.0;
	for (int l40 = 0; (l40 < 6); l40 = (l40 + 1)) fRec20[l40] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int RsamplingFreq)
{
	sample_rate = 96000;
	smp.setup(RsamplingFreq, sample_rate);
	smps.setup(RsamplingFreq, sample_rate);
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = (1.0 / std::tan((20517.741620594938 / fConst0)));
	fConst2 = (1.0 / (fConst1 + 1.0));
	fConst3 = (1.0 / std::tan((270.1769682087222 / fConst0)));
	fConst4 = (1.0 / (fConst3 + 1.0));
	fConst5 = (1.0 - fConst3);
	fConst6 = (1.0 - fConst1);
	fConst7 = (1.0 / std::tan((414.69023027385271 / fConst0)));
	fConst8 = (1.0 / (fConst7 + 1.0));
	fConst9 = (1.0 - fConst7);
	fConst10 = (1.0 / std::tan((609.46897479641984 / fConst0)));
	fConst11 = (1.0 / (fConst10 + 1.0));
	fConst12 = (1.0 - fConst10);
	clear_state_f();
}

void Dsp::init_static(unsigned int sample_rate, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
	FAUSTFLOAT buf[smp.max_out_count(count)];
	FAUSTFLOAT bufs[smps.max_out_count(count)];
	smps.up(count, input1, bufs);
	int ReCount = smp.up(count, input0, buf);
	double fSlow0 = double(fVslider0);
	double fSlow1 = (1.0 - std::max<double>(0.0, fSlow0));
	double fSlow2 = double(fHslider0);
	double fSlow3 = (1.0 - std::max<double>(0.0, (-1.0 * fSlow0)));
	double fSlow4 = double(fHslider1);
	double fSlow5 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider1))));
	double fSlow6 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider2))));
	double fSlow7 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider3))));
	for (int i = 0; (i < ReCount); i = (i + 1)) {
		double fTemp0 = double(buf[i]);
		fRec0[0] = (-1.0 * ((fSlow2 * fRec0[5]) - fTemp0));
		fRec13[0] = (fSlow5 + (0.999 * fRec13[1]));
		double fTemp1 = (fTemp0 * fRec13[0]);
		fVec0[0] = fTemp1;
		fRec12[0] = ((0.93028479253239138 * (fTemp1 + fVec0[1])) - (0.86056958506478287 * fRec12[1]));
		fRec11[0] = (fRec12[0] - ((1.8405051250752198 * fRec11[1]) + (0.86129424393186271 * fRec11[2])));
		fRec14[0] = (fConst4 * ((0.027 * (fRec10[1] + fRec10[2])) - (fConst5 * fRec14[1])));
		fRec10[0] = (double(Ftube(int(TUBE_TABLE_6V6_68k), double((((0.92544984225177063 * (fRec11[0] + fRec11[2])) + (fRec14[0] + (1.8508996845035413 * fRec11[1]))) + -2.2961499999999999)))) + -164.9574074074074);
		fRec9[0] = (fConst2 * ((0.025000000000000001 * (fRec10[0] + fRec10[1])) - (fConst6 * fRec9[1])));
		fRec15[0] = (fSlow6 + (0.999 * fRec15[1]));
		double fTemp2 = (fRec9[0] * fRec15[0]);
		fVec1[0] = fTemp2;
		fRec8[0] = ((0.93028479253239138 * (fTemp2 + fVec1[1])) - (0.86056958506478287 * fRec8[1]));
		fRec7[0] = (fRec8[0] - ((1.8405051250752198 * fRec7[1]) + (0.86129424393186271 * fRec7[2])));
		fRec16[0] = (fConst8 * ((0.014999999999999999 * (fRec6[1] + fRec6[2])) - (fConst9 * fRec16[1])));
		fRec6[0] = (double(Ftube(int(TUBE_TABLE_6V6_250k), double((((0.92544984225177063 * (fRec7[0] + fRec7[2])) + (fRec16[0] + (1.8508996845035413 * fRec7[1]))) + -1.6755869999999999)))) + -138.29419999999999);
		fRec5[0] = (fConst2 * ((0.025000000000000001 * (fRec6[0] + fRec6[1])) - (fConst6 * fRec5[1])));
		fRec17[0] = (fSlow7 + (0.999 * fRec17[1]));
		double fTemp3 = (fRec5[0] * fRec17[0]);
		fVec2[0] = fTemp3;
		fRec4[0] = ((0.93028479253239138 * (fTemp3 + fVec2[1])) - (0.86056958506478287 * fRec4[1]));
		fRec3[0] = (fRec4[0] - ((1.8405051250752198 * fRec3[1]) + (0.86129424393186271 * fRec3[2])));
		fRec18[0] = (fConst11 * ((0.0082000000000000007 * (fRec2[1] + fRec2[2])) - (fConst12 * fRec18[1])));
		fRec2[0] = (double(Ftube(int(TUBE_TABLE_6V6_250k), double((((0.92544984225177063 * (fRec3[0] + fRec3[2])) + (fRec18[0] + (1.8508996845035413 * fRec3[1]))) + -1.1304620000000001)))) + -112.13878048780487);
		fRec1[0] = (-1.0 * ((fSlow4 * fRec1[5]) - (0.025000000000000001 * fRec2[0])));
		buf[i] = FAUSTFLOAT(((fSlow1 * fRec0[0]) + (fSlow3 * fRec1[0])));
		double fTemp4 = double(bufs[i]);
		fRec19[0] = (-1.0 * ((fSlow2 * fRec19[5]) - fTemp4));
		double fTemp5 = (fTemp4 * fRec13[0]);
		fVec3[0] = fTemp5;
		fRec31[0] = ((0.93028479253239138 * (fTemp5 + fVec3[1])) - (0.86056958506478287 * fRec31[1]));
		fRec30[0] = (fRec31[0] - ((1.8405051250752198 * fRec30[1]) + (0.86129424393186271 * fRec30[2])));
		fRec32[0] = (fConst4 * ((0.027 * (fRec29[1] + fRec29[2])) - (fConst5 * fRec32[1])));
		fRec29[0] = (double(Ftube(int(TUBE_TABLE_6V6_68k), double((((0.92544984225177063 * (fRec30[0] + fRec30[2])) + (fRec32[0] + (1.8508996845035413 * fRec30[1]))) + -2.2961499999999999)))) + -164.9574074074074);
		fRec28[0] = (fConst2 * ((0.025000000000000001 * (fRec29[0] + fRec29[1])) - (fConst6 * fRec28[1])));
		double fTemp6 = (fRec15[0] * fRec28[0]);
		fVec4[0] = fTemp6;
		fRec27[0] = ((0.93028479253239138 * (fTemp6 + fVec4[1])) - (0.86056958506478287 * fRec27[1]));
		fRec26[0] = (fRec27[0] - ((1.8405051250752198 * fRec26[1]) + (0.86129424393186271 * fRec26[2])));
		fRec33[0] = (fConst8 * ((0.014999999999999999 * (fRec25[1] + fRec25[2])) - (fConst9 * fRec33[1])));
		fRec25[0] = (double(Ftube(int(TUBE_TABLE_6V6_250k), double((((0.92544984225177063 * (fRec26[0] + fRec26[2])) + (fRec33[0] + (1.8508996845035413 * fRec26[1]))) + -1.6755869999999999)))) + -138.29419999999999);
		fRec24[0] = (fConst2 * ((0.025000000000000001 * (fRec25[0] + fRec25[1])) - (fConst6 * fRec24[1])));
		double fTemp7 = (fRec17[0] * fRec24[0]);
		fVec5[0] = fTemp7;
		fRec23[0] = ((0.93028479253239138 * (fTemp7 + fVec5[1])) - (0.86056958506478287 * fRec23[1]));
		fRec22[0] = (fRec23[0] - ((1.8405051250752198 * fRec22[1]) + (0.86129424393186271 * fRec22[2])));
		fRec34[0] = (fConst11 * ((0.0082000000000000007 * (fRec21[1] + fRec21[2])) - (fConst12 * fRec34[1])));
		fRec21[0] = (double(Ftube(int(TUBE_TABLE_6V6_250k), double((((0.92544984225177063 * (fRec22[0] + fRec22[2])) + (fRec34[0] + (1.8508996845035413 * fRec22[1]))) + -1.1304620000000001)))) + -112.13878048780487);
		fRec20[0] = (-1.0 * ((fSlow4 * fRec20[5]) - (0.025000000000000001 * fRec21[0])));
		bufs[i] = FAUSTFLOAT(((fSlow1 * fRec19[0]) + (fSlow3 * fRec20[0])));
		for (int j0 = 5; (j0 > 0); j0 = (j0 - 1)) {
			fRec0[j0] = fRec0[(j0 - 1)];
		}
		fRec13[1] = fRec13[0];
		fVec0[1] = fVec0[0];
		fRec12[1] = fRec12[0];
		fRec11[2] = fRec11[1];
		fRec11[1] = fRec11[0];
		fRec14[1] = fRec14[0];
		fRec10[2] = fRec10[1];
		fRec10[1] = fRec10[0];
		fRec9[1] = fRec9[0];
		fRec15[1] = fRec15[0];
		fVec1[1] = fVec1[0];
		fRec8[1] = fRec8[0];
		fRec7[2] = fRec7[1];
		fRec7[1] = fRec7[0];
		fRec16[1] = fRec16[0];
		fRec6[2] = fRec6[1];
		fRec6[1] = fRec6[0];
		fRec5[1] = fRec5[0];
		fRec17[1] = fRec17[0];
		fVec2[1] = fVec2[0];
		fRec4[1] = fRec4[0];
		fRec3[2] = fRec3[1];
		fRec3[1] = fRec3[0];
		fRec18[1] = fRec18[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		for (int j1 = 5; (j1 > 0); j1 = (j1 - 1)) {
			fRec1[j1] = fRec1[(j1 - 1)];
		}
		for (int j2 = 5; (j2 > 0); j2 = (j2 - 1)) {
			fRec19[j2] = fRec19[(j2 - 1)];
		}
		fVec3[1] = fVec3[0];
		fRec31[1] = fRec31[0];
		fRec30[2] = fRec30[1];
		fRec30[1] = fRec30[0];
		fRec32[1] = fRec32[0];
		fRec29[2] = fRec29[1];
		fRec29[1] = fRec29[0];
		fRec28[1] = fRec28[0];
		fVec4[1] = fVec4[0];
		fRec27[1] = fRec27[0];
		fRec26[2] = fRec26[1];
		fRec26[1] = fRec26[0];
		fRec33[1] = fRec33[0];
		fRec25[2] = fRec25[1];
		fRec25[1] = fRec25[0];
		fRec24[1] = fRec24[0];
		fVec5[1] = fVec5[0];
		fRec23[1] = fRec23[0];
		fRec22[2] = fRec22[1];
		fRec22[1] = fRec22[0];
		fRec34[1] = fRec34[0];
		fRec21[2] = fRec21[1];
		fRec21[1] = fRec21[0];
		for (int j3 = 5; (j3 > 0); j3 = (j3 - 1)) {
			fRec20[j3] = fRec20[(j3 - 1)];
		}
	}
	smp.down(buf, output0);
	smps.down(bufs, output1);
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerFloatVar("ampmodul.feedbac",N_("Dry/FB"),"S","",&fHslider0, 0.0, -1.0, 1.0, 0.01, 0);
	reg.registerFloatVar("ampmodul.feedback",N_("Wet/FB"),"S","",&fHslider1, 0.0, -1.0, 1.0, 0.01, 0);
	reg.registerFloatVar("ampmodul.level",N_("Level"),"S","",&fVslider1, -20.0, -40.0, 4.0, 0.10000000000000001, 0);
	reg.registerFloatVar("ampmodul.amp2.stage1.tube1",N_("Tube I"),"S","",&fVslider2, 6.0, -20.0, 20.0, 0.10000000000000001, 0);
	reg.registerFloatVar("ampmodul.amp2.stage2.tube2",N_("Tube II"),"S","",&fVslider3, 6.0, -20.0, 20.0, 0.10000000000000001, 0);
	reg.registerFloatVar("ampmodul.wet_dry",N_("Dry/Wet"),"S","",&fVslider0, 0.0, -1.0, 1.0, 0.10000000000000001, 0);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

const char *Dsp::glade_def = "\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<!-- Generated with glade 3.22.1 -->\n\
<interface>\n\
  <requires lib=\"gtk+\" version=\"3.20\"/>\n\
  <requires lib=\"gxwidgets\" version=\"0.0\"/>\n\
  <object class=\"GtkWindow\" id=\"window1\">\n\
    <property name=\"can_focus\">False</property>\n\
    <child>\n\
      <placeholder/>\n\
    </child>\n\
    <child>\n\
      <object class=\"GtkBox\" id=\"vbox1\">\n\
        <property name=\"visible\">True</property>\n\
        <property name=\"can_focus\">False</property>\n\
        <property name=\"orientation\">vertical</property>\n\
        <child>\n\
          <object class=\"GtkBox\" id=\"rackbox\">\n\
            <property name=\"visible\">True</property>\n\
            <property name=\"can_focus\">False</property>\n\
            <property name=\"spacing\">8</property>\n\
            <child>\n\
              <object class=\"GtkBox\" id=\"hbox1\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">False</property>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox2\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label1:rack_label\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxMidKnob\" id=\"gxbigknob1\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">ampmodul.feedbac</property>\n\
                        <property name=\"label_ref\">label1:rack_label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">False</property>\n\
                    <property name=\"fill\">False</property>\n\
                    <property name=\"position\">0</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox3\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label2:rack_label\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSmallKnobR\" id=\"gxbigknob2\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">ampmodul.wet_dry</property>\n\
                        <property name=\"label_ref\">label2:rack_label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">False</property>\n\
                    <property name=\"fill\">False</property>\n\
                    <property name=\"position\">1</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox4\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label3:rack_label\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSmallKnobR\" id=\"gxbigknob3\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">ampmodul.level</property>\n\
                        <property name=\"label_ref\">label3:rack_label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">False</property>\n\
                    <property name=\"fill\">False</property>\n\
                    <property name=\"position\">2</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox5\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label4:rack_label\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSmallKnobR\" id=\"gxbigknob4\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">ampmodul.amp2.stage1.tube1</property>\n\
                        <property name=\"label_ref\">label4:rack_label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">False</property>\n\
                    <property name=\"fill\">False</property>\n\
                    <property name=\"position\">3</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox6\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label5:rack_label\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSmallKnobR\" id=\"gxbigknob5\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">ampmodul.amp2.stage2.tube2</property>\n\
                        <property name=\"label_ref\">label5:rack_label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">False</property>\n\
                    <property name=\"fill\">False</property>\n\
                    <property name=\"position\">4</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox7\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label6:rack_label\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxMidKnob\" id=\"gxbigknob6\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">ampmodul.feedback</property>\n\
                        <property name=\"label_ref\">label6:rack_label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">False</property>\n\
                    <property name=\"fill\">False</property>\n\
                    <property name=\"position\">5</property>\n\
                  </packing>\n\
                </child>\n\
              </object>\n\
              <packing>\n\
                <property name=\"expand\">True</property>\n\
                <property name=\"fill\">False</property>\n\
                <property name=\"pack_type\">end</property>\n\
                <property name=\"position\">0</property>\n\
              </packing>\n\
            </child>\n\
          </object>\n\
          <packing>\n\
            <property name=\"expand\">True</property>\n\
            <property name=\"fill\">False</property>\n\
            <property name=\"position\">0</property>\n\
          </packing>\n\
        </child>\n\
        <child>\n\
          <object class=\"GtkBox\" id=\"minibox\">\n\
            <property name=\"visible\">True</property>\n\
            <property name=\"can_focus\">False</property>\n\
            <property name=\"spacing\">4</property>\n\
            <child>\n\
              <object class=\"GxHSlider\" id=\"gxhslider1\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">True</property>\n\
                <property name=\"receives_default\">True</property>\n\
                <property name=\"round_digits\">0</property>\n\
                <property name=\"var_id\">ampmodul.level</property>\n\
                <property name=\"show_value\">False</property>\n\
                <property name=\"value_position\">right</property>\n\
                <property name=\"value_xalign\">0.52000000000000002</property>\n\
                <property name=\"label_ref\">label0:rack_label</property>\n\
              </object>\n\
              <packing>\n\
                <property name=\"expand\">False</property>\n\
                <property name=\"fill\">False</property>\n\
                <property name=\"position\">0</property>\n\
              </packing>\n\
            </child>\n\
            <child>\n\
              <object class=\"GtkLabel\" id=\"label0:rack_label\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">False</property>\n\
                <property name=\"label\" translatable=\"yes\">Level</property>\n\
                <property name=\"xalign\">0</property>\n\
              </object>\n\
              <packing>\n\
                <property name=\"expand\">False</property>\n\
                <property name=\"fill\">False</property>\n\
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
#define PARAM(p) ("ampmodul" "." p)
// postamp
b.openHorizontalhideBox("");
b.create_master_slider(PARAM("level"), _("level"));
b.closeBox();
b.openHorizontalBox("");
{
    b.insertSpacer();
    b.create_small_rackknobr(PARAM("feedbac"), _("dry/feedback  "));
    b.create_small_rackknob(PARAM("wet_dry"), _("dry/wet"));
    b.create_small_rackknob(PARAM("level"), _("level"));
    b.create_small_rackknob(PARAM("amp2.stage1.tube1"), _("tube1"));
    b.create_small_rackknob(PARAM("amp2.stage2.tube2"), _("tube2"));
    b.create_small_rackknobr(PARAM("feedback"), _("  wet/feedback"));
    b.insertSpacer();
}
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

} // end namespace gx_ampmodul
