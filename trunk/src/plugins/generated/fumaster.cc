// generated from file '../src/plugins/fumaster.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

#include "trany.h"
#include <string.h>

namespace pluginlib {
namespace fumaster {

class Dsp: public PluginDef {
private:
	int fSampleRate;
	FAUSTFLOAT fVslider0;
	double fRec0[2];
	double fConst2;
	double fConst3;
	double fConst5;
	double fConst7;
	double fConst10;
	double fConst14;
	double fConst15;
	double fConst16;
	double fConst17;
	double fConst19;
	double fConst21;
	double fConst23;
	double fConst25;
	double fConst27;
	double fConst29;
	double fConst30;
	double fConst31;
	double fConst32;
	double fConst33;
	double fConst34;
	double fConst35;
	double fConst36;
	double fConst37;
	double fConst38;
	double fRec1[7];
	double fConst40;
	double fConst43;
	double fConst45;
	double fConst48;
	double fConst49;
	double fConst50;
	double fConst51;
	double fConst52;
	double fConst53;
	double fConst54;
	double fConst55;
	double fConst56;


	gx_resample::FixedRateResampler smpCl;
	double fConstCl3;
	double fVecCl0[2];
	double fRecCl7[2];
	double fRecCl6[3];
	double fConstCl5;
	double fConstCl6;
	double fRecCl8[2];
	double fRecCl5[3];
	double fConstCl7;
	double fConstCl8;
	double fRecCl4[2];
	double fRecCl3[2];
	double fRecCl2[3];
	double fRecCl9[2];
	double fRecCl1[3];
	double fRecCl0[2];

	FAUSTFLOAT fsliderdw0;
	FAUSTFLOAT 	fsliderV0;
	double 	fRecV0[2];
	void clear_state_f();
	int load_ui_f(const UiBuilder& b, int form);
	static const char *glade_def;
	void init(unsigned int sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static int load_ui_f_static(const UiBuilder& b, int form);
	static void init_static(unsigned int sample_rate, PluginDef*);
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
	id = "fumaster";
	name = N_("Fuzz Master");
	groups = 0;
	description = N_("Vintage Fuzz Master simulation"); // description (tooltip)
	category = N_("Fuzz");       // category
	shortname = N_("Fuzz Master");     // shortname
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec0[l0] = 0.0;
	for (int l1 = 0; l1 < 7; l1 = l1 + 1) fRec1[l1] = 0.0;

	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fVecCl0[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRecCl7[l1] = 0.0;
	for (int l2 = 0; l2 < 3; l2 = l2 + 1) fRecCl6[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRecCl8[l3] = 0.0;
	for (int l4 = 0; l4 < 3; l4 = l4 + 1) fRecCl5[l4] = 0.0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fRecCl4[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fRecCl3[l6] = 0.0;
	for (int l7 = 0; l7 < 3; l7 = l7 + 1) fRecCl2[l7] = 0.0;
	for (int l8 = 0; l8 < 2; l8 = l8 + 1) fRecCl9[l8] = 0.0;
	for (int l9 = 0; l9 < 3; l9 = l9 + 1) fRecCl1[l9] = 0.0;
	for (int l10 = 0; l10 < 2; l10 = l10 + 1) fRecCl0[l10] = 0.0;

	for (int i=0; i<2; i++) fRecV0[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int sample_rate)
{
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = 1.00799506674223e-28 * fConst0;
	fConst2 = mydsp_faustpower2_f(fConst0);
	fConst3 = fConst2 * (fConst0 * (fConst0 * (fConst0 * (-2.59175366383786e-25 - fConst1) + -4.35259230096405e-22) + -1.02583553103419e-19) + -2.16974948431515e-18);
	double fConst4 = 1.5016846937505e-31 * fConst0;
	fConst5 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (4.96235474586462e-26 - fConst4) + 1.27917670111645e-22) + 2.16655787499057e-19) + 5.11414335446406e-17) + 1.08487474215758e-15);
	double fConst6 = 1.00949675143598e-28 * fConst0;
	fConst7 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst6 + 3.20513868924941e-25) + 5.95381363906935e-22) + 3.72110810064138e-19) + 7.52873102578757e-17) + 3.94912717206244e-15);
	double fConst8 = 1.4319302322147411e-27 * fConst0;
	double fConst9 = mydsp_faustpower5_f(fConst0);
	fConst10 = fConst9 * (-4.764973856230702e-22 - fConst8);
	double fConst11 = 1.41775270516311e-27 * fConst0;
	double fConst12 = 1.41775270516311e-29 * fConst0;
	double fConst13 = mydsp_faustpower4_f(fConst0);
	fConst14 = fConst13 * (fConst0 * (fConst12 + 4.70999825737972e-24) + 0.1 * (fConst0 * (fConst11 + 4.70999825737972e-22) + -2.59478774349197e-19) + -2.59478774349197e-21);
	fConst15 = fConst2 * (fConst0 * (fConst0 * (fConst0 * (2.59175366383786e-25 - fConst1) + -4.35259230096405e-22) + 1.02583553103419e-19) + -2.16974948431515e-18);
	fConst16 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (-4.96235474586462e-26 - fConst4) + 1.27917670111645e-22) + -2.16655787499057e-19) + 5.11414335446406e-17) + -1.08487474215758e-15);
	fConst17 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst6 + -3.20513868924941e-25) + 5.95381363906935e-22) + -3.72110810064138e-19) + 7.52873102578757e-17) + -3.94912717206244e-15);
	double fConst18 = 6.0479704004534e-28 * fConst0;
	fConst19 = fConst2 * (fConst2 * (fConst0 * (fConst18 + -1.03670146553514e-24) + 8.70518460192809e-22) + -4.3394989686303e-18);
	double fConst20 = 9.01010816250298e-31 * fConst0;
	fConst21 = fConst0 * (fConst0 * (fConst2 * (fConst0 * (fConst20 + 1.98494189834585e-25) + -2.5583534022329e-22) + 1.02282867089281e-16) + -4.3394989686303e-15);
	double fConst22 = 6.0569805086159e-28 * fConst0;
	fConst23 = fConst0 * (fConst0 * (fConst2 * (fConst0 * (1.28205547569977e-24 - fConst22) + -1.19076272781387e-21) + 1.50574620515751e-16) + -1.57965086882498e-14);
	double fConst24 = 1.51199260011335e-27 * fConst0;
	fConst25 = fConst2 * (fConst0 * (fConst0 * (fConst0 * (1.29587683191893e-24 - fConst24) + 4.35259230096405e-22) + -3.07750659310257e-19) + 2.16974948431515e-18);
	double fConst26 = 2.25252704062574e-30 * fConst0;
	fConst27 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (-2.48117737293231e-25 - fConst26) + -1.27917670111645e-22) + 6.4996736249717e-19) + -5.11414335446406e-17) + -5.42437371078788e-15);
	double fConst28 = 1.51424512715397e-27 * fConst0;
	fConst29 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst28 + -1.60256934462471e-24) + -5.95381363906935e-22) + 1.11633243019242e-18) + -7.52873102578757e-17) + -1.97456358603122e-14);
	fConst30 = fConst2 * (2.01599013348447e-27 * fConst2 + -1.74103692038562e-21) + 8.6789979372606e-18;
	fConst31 = fConst2 * (3.00336938750099e-30 * fConst2 + 5.11670680446579e-22) + -2.04565734178562e-16;
	fConst32 = fConst2 * (2.38152545562774e-21 - 2.01899350287197e-27 * fConst2) + -3.01149241031503e-16;
	fConst33 = fConst2 * (fConst0 * (fConst0 * (fConst0 * (-1.29587683191893e-24 - fConst24) + 4.35259230096405e-22) + 3.07750659310257e-19) + 2.16974948431515e-18);
	fConst34 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (2.48117737293231e-25 - fConst26) + -1.27917670111645e-22) + -6.4996736249717e-19) + -5.11414335446406e-17) + 5.42437371078788e-15);
	fConst35 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst28 + 1.60256934462471e-24) + -5.95381363906935e-22) + -1.11633243019242e-18) + -7.52873102578757e-17) + 1.97456358603122e-14);
	fConst36 = fConst2 * (fConst2 * (fConst0 * (fConst18 + 1.03670146553514e-24) + 8.70518460192809e-22) + -4.3394989686303e-18);
	fConst37 = fConst0 * (fConst0 * (fConst2 * (fConst0 * (fConst20 + -1.98494189834585e-25) + -2.5583534022329e-22) + 1.02282867089281e-16) + 4.3394989686303e-15);
	fConst38 = fConst0 * (fConst0 * (fConst2 * (fConst0 * (-1.28205547569977e-24 - fConst22) + -1.19076272781387e-21) + 1.50574620515751e-16) + 1.57965086882498e-14);
	double fConst39 = 8.591581393288467e-27 * fConst0;
	fConst40 = fConst9 * (fConst39 + 1.9059895424922826e-21);
	double fConst41 = 8.50651623097868e-27 * fConst0;
	double fConst42 = 8.50651623097868e-29 * fConst0;
	fConst43 = fConst13 * (fConst0 * (-1.88399930295189e-23 - fConst42) + 0.1 * (fConst0 * (-1.88399930295189e-21 - fConst41) + 5.18957548698393e-19) + 5.18957548698393e-21);
	double fConst44 = 2.1478953483221167e-26 * fConst0;
	fConst45 = fConst9 * (-2.3824869281153507e-21 - fConst44);
	double fConst46 = 2.12662905774467e-26 * fConst0;
	double fConst47 = 2.12662905774467e-28 * fConst0;
	fConst48 = fConst13 * (fConst0 * (fConst47 + 2.35499912868986e-23) + 0.1 * (fConst0 * (fConst46 + 2.35499912868986e-21) + 2.59478774349197e-19) + 2.59478774349197e-21);
	fConst49 = 2.863860464429492e-26 * mydsp_faustpower6_f(fConst0);
	fConst50 = fConst13 * (0.1 * (-1.03791509739679e-18 - 2.83550541032623e-26 * fConst2) + (-1.03791509739679e-20 - 2.83550541032623e-28 * fConst2));
	fConst51 = fConst9 * (2.3824869281153507e-21 - fConst44);
	fConst52 = fConst13 * (fConst0 * (fConst47 + -2.35499912868986e-23) + 0.1 * (fConst0 * (fConst46 + -2.35499912868986e-21) + 2.59478774349197e-19) + 2.59478774349197e-21);
	fConst53 = fConst9 * (fConst39 + -1.9059895424922826e-21);
	fConst54 = fConst13 * (fConst0 * (1.88399930295189e-23 - fConst42) + 0.1 * (fConst0 * (1.88399930295189e-21 - fConst41) + 5.18957548698393e-19) + 5.18957548698393e-21);
	fConst55 = fConst9 * (4.764973856230702e-22 - fConst8);
	fConst56 = fConst13 * (fConst0 * (fConst12 + -4.70999825737972e-24) + 0.1 * (fConst0 * (fConst11 + -4.70999825737972e-22) + -2.59478774349197e-19) + -2.59478774349197e-21);

	sample_rate = 96000;
	smpCl.setup(fSampleRate, sample_rate);
	fSampleRate = sample_rate;
	double fConstCl0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	double fConstCl1 = std::tan(97.38937226128358 / fConstCl0);
	double fConstCl2 = 1.0 / fConstCl1;
	fConstCl3 = 1.0 - fConstCl2;
	double fConstCl4 = 1.0 / std::tan(270.1769682087222 / fConstCl0);
	fConstCl5 = 1.0 - fConstCl4;
	fConstCl6 = 1.0 / (fConstCl4 + 1.0);
	fConstCl7 = 0.025 / fConstCl1;
	fConstCl8 = 1.0 / (fConstCl2 + 1.0);

	clear_state_f();
}

void Dsp::init_static(unsigned int sample_rate, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlowdw0 = (0.01 * fsliderdw0);
	double 	fSlowdw1 = (1 - fSlowdw0);
	FAUSTFLOAT 	dryinput[count];
	memcpy(&dryinput, input0, count * sizeof(float));

	double 	fSlowV0 = (0.0010000000000000009 * double(fsliderV0));

	double fSlow0 = 0.007000000000000006 * double(fVslider0);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec0[0] = fSlow0 + 0.993 * fRec0[1];
		double fTemp0 = fConst7 + fRec0[0] * (fConst5 + fConst3 * fRec0[0]) + 5.42437371078787e-14;
		fRec1[0] = double(input0[i0]) - (fRec1[1] * (fConst38 + fRec0[0] * (fConst37 + fConst36 * fRec0[0]) + 3.25462422647273e-13) + fRec1[2] * (fConst35 + fRec0[0] * (fConst34 + fConst33 * fRec0[0]) + 8.13656056618181e-13) + fRec1[3] * (fConst2 * (fConst32 + fRec0[0] * (fConst31 + fConst30 * fRec0[0])) + 1.08487474215758e-12) + fRec1[4] * (fConst29 + fRec0[0] * (fConst27 + fConst25 * fRec0[0]) + 8.13656056618181e-13) + fRec1[5] * (fConst23 + fRec0[0] * (fConst21 + fConst19 * fRec0[0]) + 3.25462422647273e-13) + fRec1[6] * (fConst17 + fRec0[0] * (fConst16 + fConst15 * fRec0[0]) + 5.42437371078787e-14)) / fTemp0;
		output0[i0] = FAUSTFLOAT((fRec1[0] * (fConst56 + fConst55 * fRec0[0]) + fRec1[1] * (fConst54 + fConst53 * fRec0[0]) + fRec1[2] * (fConst52 + fConst51 * fRec0[0]) + fRec1[3] * (fConst50 + fConst49 * fRec0[0]) + fRec1[4] * (fConst48 + fConst45 * fRec0[0]) + fRec1[5] * (fConst43 + fConst40 * fRec0[0]) + fRec1[6] * (fConst14 + fConst10 * fRec0[0])) / fTemp0);
		fRec0[1] = fRec0[0];
		for (int j0 = 6; j0 > 0; j0 = j0 - 1) {
			fRec1[j0] = fRec1[j0 - 1];
		}
	}

	FAUSTFLOAT bufCl[smpCl.max_out_count(count)];
	int ReCount = smpCl.up(count, output0, bufCl);
	for (int i0 = 0; i0 < ReCount; i0 = i0 + 1) {
		double fTemp0 = double(bufCl[i0]);
		fVecCl0[0] = fTemp0;
		fRecCl7[0] = 0.9302847925323914 * (fTemp0 + fVecCl0[1]) - 0.8605695850647829 * fRecCl7[1];
		fRecCl6[0] = fRecCl7[0] - (1.8405051250752198 * fRecCl6[1] + 0.8612942439318627 * fRecCl6[2]);
		fRecCl8[0] = fConstCl6 * (0.027 * (fRecCl5[1] + fRecCl5[2]) - fConstCl5 * fRecCl8[1]);
		fRecCl5[0] = Ftrany(TRANY_TABLE_7199P_68k, 0.9254498422517706 * (fRecCl6[0] + fRecCl6[2]) + fRecCl8[0] + 1.8508996845035413 * fRecCl6[1] + -3.571981) + -117.70440740740739;
		fRecCl4[0] = fConstCl8 * (fConstCl7 * (fRecCl5[0] - fRecCl5[1]) - fConstCl3 * fRecCl4[1]);
		fRecCl3[0] = 0.9302847925323914 * (fRecCl4[0] + fRecCl4[1]) - 0.8605695850647829 * fRecCl3[1];
		fRecCl2[0] = fRecCl3[0] - (1.8405051250752198 * fRecCl2[1] + 0.8612942439318627 * fRecCl2[2]);
		fRecCl9[0] = fConstCl6 * (0.027 * (fRecCl1[1] + fRecCl1[2]) - fConstCl5 * fRecCl9[1]);
		fRecCl1[0] = Ftrany(TRANY_TABLE_7199P_68k, 0.9254498422517706 * (fRecCl2[0] + fRecCl2[2]) + fRecCl9[0] + 1.8508996845035413 * fRecCl2[1] + -3.571981) + -117.70440740740739;
		fRecCl0[0] = fConstCl8 * (fConstCl7 * (fRecCl1[0] - fRecCl1[1]) - fConstCl3 * fRecCl0[1]);
		bufCl[i0] = FAUSTFLOAT(fRecCl0[0]);
		fVecCl0[1] = fVecCl0[0];
		fRecCl7[1] = fRecCl7[0];
		fRecCl6[2] = fRecCl6[1];
		fRecCl6[1] = fRecCl6[0];
		fRecCl8[1] = fRecCl8[0];
		fRecCl5[2] = fRecCl5[1];
		fRecCl5[1] = fRecCl5[0];
		fRecCl4[1] = fRecCl4[0];
		fRecCl3[1] = fRecCl3[0];
		fRecCl2[2] = fRecCl2[1];
		fRecCl2[1] = fRecCl2[0];
		fRecCl9[1] = fRecCl9[0];
		fRecCl1[2] = fRecCl1[1];
		fRecCl1[1] = fRecCl1[0];
		fRecCl0[1] = fRecCl0[0];
	}
	smpCl.down(bufCl, output0);

	for (int i=0; i<count; i++) {
		fRecV0[0] = ((0.999 * fRecV0[1]) + fSlowV0);
		output0[i] = (FAUSTFLOAT)((double)output0[i] * fRecV0[0]);
		// post processing
		fRecV0[1] = fRecV0[0];
	}

	for (int i=0; i<count; i++) {
		output0[i] = ((fSlowdw1 * (double)dryinput[i]) + (fSlowdw0 * (double)output0[i]));
	}

}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerFloatVar("fumaster.wet_dry",N_("Dry/Wet"),"S",N_("percentage of processed signal in output signal"),&fsliderdw0, 1e+02, 0.0, 1e+02, 1.0, 0);
	reg.registerFloatVar("fumaster.Level",N_("Level"),"S","",&fsliderV0, 0.5, 0.0, 1, 0.01, 0);
	reg.registerFloatVar("fumaster.Tone",N_("Tone"),"S","",&fVslider0, 0.5, 0.0, 0.99, 0.01, 0);
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
            <property name=\"spacing\">4</property>\n\
            <child>\n\
              <object class=\"GtkBox\" id=\"hbox1\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">False</property>\n\
                <property name=\"spacing\">10</property>\n\
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
                      <object class=\"GxSmallKnobR\" id=\"gxbigknob1\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">fumaster.Tone</property>\n\
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
                      <object class=\"GxMidKnob\" id=\"gxbigknob2\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">fumaster.Level</property>\n\
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
                        <property name=\"var_id\">fumaster.wet_dry</property>\n\
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
                <property name=\"var_id\">fumaster.Level</property>\n\
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
#define PARAM(p) ("fumaster" "." p)

b.openHorizontalhideBox("");
    b.create_master_slider(PARAM("Tone"), "Tone");
b.closeBox();
b.openHorizontalBox("");

    b.create_small_rackknobr(PARAM("Tone"), "Tone");

    b.create_small_rackknobr(PARAM("Level"), "Level");
    b.create_small_rackknobr(PARAM("Volume"), "Volume");
    b.create_small_rackknobr(PARAM("wet_dry"), "dry/wet");
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

} // end namespace fumaster
} // end namespace pluginlib
