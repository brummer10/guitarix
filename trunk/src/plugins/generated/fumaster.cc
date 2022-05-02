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
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst4;
	FAUSTFLOAT fVslider0;
	double fRec1[2];
	double fConst6;
	double fConst8;
	double fConst10;
	double fConst12;
	double fConst14;
	double fConst15;
	double fConst16;
	double fConst17;
	double fConst18;
	double fConst19;
	double fConst20;
	double fConst21;
	double fConst22;
	double fConst23;
	double fConst25;
	double fConst27;
	double fConst29;
	double fConst30;
	double fConst31;
	double fConst32;
	double fRec0[7];
	double fConst34;
	double fConst36;
	double fConst37;
	double fConst39;
	double fConst41;
	double fConst42;
	double fConst44;
	double fConst46;
	double fConst47;
	double fConst48;
	double fConst49;
	double fConst50;
	double fConst51;
	double fConst52;
	double fConst53;
	double fConst54;
	double fConst55;
	double fConst56;
	double fConst57;
	double fConst58;
	double fConst59;


	gx_resample::FixedRateResampler smpCl;
	double fConstCl4;
	double fVecCl0[2];
	double fRecCl7[2];
	double fRecCl6[3];
	double fConstCl6;
	double fConstCl7;
	double fRecCl8[2];
	double fRecCl5[3];
	double fConstCl8;
	double fConstCl9;
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec1[l0] = 0.0;
	for (int l1 = 0; l1 < 7; l1 = l1 + 1) fRec0[l1] = 0.0;

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
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = mydsp_faustpower4_f(fConst0);
	fConst2 = mydsp_faustpower2_f(fConst0);
	double fConst3 = 6.0569805086158998e-28 * fConst0;
	fConst4 = fConst0 * (fConst2 * (fConst0 * (-1.28205547569977e-24 - fConst3) + -1.19076272781387e-21) + 1.50574620515751e-16) + 1.57965086882498e-14;
	double fConst5 = 9.0101081625029807e-31 * fConst0;
	fConst6 = fConst0 * (fConst2 * (fConst0 * (fConst5 + -1.9849418983458499e-25) + -2.5583534022328998e-22) + 1.02282867089281e-16) + 4.3394989686302998e-15;
	double fConst7 = 6.0479704004534004e-28 * fConst0;
	fConst8 = fConst0 * (fConst2 * (fConst0 * (fConst7 + 1.0367014655351399e-24) + 8.7051846019280894e-22) + -4.3394989686303002e-18);
	double fConst9 = 1.5142451271539699e-27 * fConst0;
	fConst10 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst9 + 1.60256934462471e-24) + -5.9538136390693501e-22) + -1.11633243019242e-18) + -7.5287310257875699e-17) + 1.9745635860312201e-14;
	double fConst11 = 2.2525270406257401e-30 * fConst0;
	fConst12 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (2.4811773729323101e-25 - fConst11) + -1.2791767011164499e-22) + -6.4996736249717003e-19) + -5.1141433544640603e-17) + 5.4243737107878799e-15;
	double fConst13 = 1.5119926001133501e-27 * fConst0;
	fConst14 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (-1.29587683191893e-24 - fConst13) + 4.3525923009640504e-22) + 3.0775065931025701e-19) + 2.1697494843151501e-18);
	fConst15 = fConst2 * (2.38152545562774e-21 - 2.01899350287197e-27 * fConst2) + -3.0114924103150299e-16;
	fConst16 = fConst2 * (3.0033693875009901e-30 * fConst2 + 5.1167068044657902e-22) + -2.0456573417856199e-16;
	fConst17 = fConst2 * (2.01599013348447e-27 * fConst2 + -1.7410369203856201e-21) + 8.6789979372606003e-18;
	fConst18 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst9 + -1.60256934462471e-24) + -5.9538136390693501e-22) + 1.11633243019242e-18) + -7.5287310257875699e-17) + -1.9745635860312201e-14;
	fConst19 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (-2.4811773729323101e-25 - fConst11) + -1.2791767011164499e-22) + 6.4996736249717003e-19) + -5.1141433544640603e-17) + -5.4243737107878799e-15;
	fConst20 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (1.29587683191893e-24 - fConst13) + 4.3525923009640504e-22) + -3.0775065931025701e-19) + 2.1697494843151501e-18);
	fConst21 = fConst0 * (fConst2 * (fConst0 * (1.28205547569977e-24 - fConst3) + -1.19076272781387e-21) + 1.50574620515751e-16) + -1.57965086882498e-14;
	fConst22 = fConst0 * (fConst2 * (fConst0 * (fConst5 + 1.9849418983458499e-25) + -2.5583534022328998e-22) + 1.02282867089281e-16) + -4.3394989686302998e-15;
	fConst23 = fConst0 * (fConst2 * (fConst0 * (fConst7 + -1.0367014655351399e-24) + 8.7051846019280894e-22) + -4.3394989686303002e-18);
	double fConst24 = 1.00949675143598e-28 * fConst0;
	fConst25 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst24 + -3.2051386892494098e-25) + 5.9538136390693501e-22) + -3.7211081006413802e-19) + 7.5287310257875699e-17) + -3.9491271720624398e-15;
	double fConst26 = 1.5016846937505001e-31 * fConst0;
	fConst27 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (-4.9623547458646202e-26 - fConst26) + 1.2791767011164499e-22) + -2.1665578749905701e-19) + 5.1141433544640603e-17) + -1.0848747421575801e-15;
	double fConst28 = 1.00799506674223e-28 * fConst0;
	fConst29 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (2.5917536638378599e-25 - fConst28) + -4.3525923009640504e-22) + 1.02583553103419e-19) + -2.1697494843151501e-18);
	fConst30 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst24 + 3.2051386892494098e-25) + 5.9538136390693501e-22) + 3.7211081006413802e-19) + 7.5287310257875699e-17) + 3.9491271720624398e-15;
	fConst31 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (4.9623547458646202e-26 - fConst26) + 1.2791767011164499e-22) + 2.1665578749905701e-19) + 5.1141433544640603e-17) + 1.0848747421575801e-15;
	fConst32 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (-2.5917536638378599e-25 - fConst28) + -4.3525923009640504e-22) + -1.02583553103419e-19) + -2.1697494843151501e-18);
	double fConst33 = 1.4177527051631099e-29 * fConst0;
	fConst34 = fConst0 * (fConst33 + -4.7099982573797203e-24) + -2.5947877434919699e-21;
	double fConst35 = 1.41775270516311e-27 * fConst0;
	fConst36 = 0.10000000000000001 * (fConst0 * (fConst35 + -4.7099982573797198e-22) + -2.59478774349197e-19);
	fConst37 = fConst0 * (4.7177958972581202e-22 - fConst35 + 4.7177958972581202e-24 - fConst33);
	double fConst38 = 8.5065162309786795e-29 * fConst0;
	fConst39 = fConst0 * (1.8839993029518899e-23 - fConst38) + 5.18957548698393e-21;
	double fConst40 = 8.5065162309786799e-27 * fConst0;
	fConst41 = 0.10000000000000001 * (fConst0 * (1.8839993029518902e-21 - fConst40) + 5.1895754869839304e-19);
	fConst42 = fConst0 * (fConst40 + -1.88711835890325e-21 + fConst38 + -1.8871183589032501e-23);
	double fConst43 = 2.1266290577446699e-28 * fConst0;
	fConst44 = fConst0 * (fConst43 + -2.3549991286898599e-23) + 2.5947877434919699e-21;
	double fConst45 = 2.1266290577446701e-26 * fConst0;
	fConst46 = 0.10000000000000001 * (fConst0 * (fConst45 + -2.3549991286898602e-21) + 2.59478774349197e-19);
	fConst47 = fConst0 * (2.3588979486290601e-21 - fConst45 + 2.3588979486290599e-23 - fConst43);
	fConst48 = -1.0379150973967901e-20 - 2.8355054103262301e-28 * fConst2;
	fConst49 = 0.10000000000000001 * (-1.0379150973967899e-18 - 2.8355054103262299e-26 * fConst2);
	fConst50 = 2.863860464429492e-26 * fConst2;
	fConst51 = fConst0 * (fConst43 + 2.3549991286898599e-23) + 2.5947877434919699e-21;
	fConst52 = 0.10000000000000001 * (fConst0 * (fConst45 + 2.3549991286898602e-21) + 2.59478774349197e-19);
	fConst53 = fConst0 * (-2.3588979486290601e-21 - fConst45 + -2.3588979486290599e-23 - fConst43);
	fConst54 = fConst0 * (-1.8839993029518899e-23 - fConst38) + 5.18957548698393e-21;
	fConst55 = 0.10000000000000001 * (fConst0 * (-1.8839993029518902e-21 - fConst40) + 5.1895754869839304e-19);
	fConst56 = fConst0 * (fConst38 + 1.8871183589032501e-23 + fConst40 + 1.88711835890325e-21);
	fConst57 = fConst0 * (fConst33 + 4.7099982573797203e-24) + -2.5947877434919699e-21;
	fConst58 = 0.10000000000000001 * (fConst0 * (fConst35 + 4.7099982573797198e-22) + -2.59478774349197e-19);
	fConst59 = fConst0 * (-4.7177958972581202e-22 - fConst35 + -4.7177958972581202e-24 - fConst33);

	sample_rate = 96000;
	smpCl.setup(fSampleRate, sample_rate);
	fSampleRate = sample_rate;
	double fConstCl0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	double fConstCl1 = std::tan(97.389372261283583 / fConstCl0);
	double fConstCl2 = 1.0 / fConstCl1;
	double fConstCl3 = fConstCl2 + 1.0;
	fConstCl4 = 1.0 / (fConstCl1 * fConstCl3);
	double fConstCl5 = 1.0 / std::tan(270.1769682087222 / fConstCl0);
	fConstCl6 = 1.0 / (fConstCl5 + 1.0);
	fConstCl7 = 1.0 - fConstCl5;
	fConstCl8 = 0.0 - fConstCl4;
	fConstCl9 = (1.0 - fConstCl2) / fConstCl3;

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

	double fSlow0 = 0.0070000000000000062 * double(fVslider0);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec1[0] = fSlow0 + 0.99299999999999999 * fRec1[1];
		double fTemp0 = fConst0 * (fConst30 + fRec1[0] * (fConst31 + fConst32 * fRec1[0])) + 5.4243737107878698e-14;
		fRec0[0] = double(input0[i0]) - (fRec0[1] * (fConst0 * (fConst4 + fRec1[0] * (fConst6 + fConst8 * fRec1[0])) + 3.2546242264727301e-13) + fRec0[2] * (fConst0 * (fConst10 + fRec1[0] * (fConst12 + fConst14 * fRec1[0])) + 8.1365605661818103e-13) + fRec0[3] * (fConst2 * (fConst15 + fRec1[0] * (fConst16 + fConst17 * fRec1[0])) + 1.0848747421575801e-12) + fRec0[4] * (fConst0 * (fConst18 + fRec1[0] * (fConst19 + fConst20 * fRec1[0])) + 8.1365605661818103e-13) + fRec0[5] * (fConst0 * (fConst21 + fRec1[0] * (fConst22 + fConst23 * fRec1[0])) + 3.2546242264727301e-13) + fRec0[6] * (fConst0 * (fConst25 + fRec1[0] * (fConst27 + fConst29 * fRec1[0])) + 5.4243737107878698e-14)) / fTemp0;
		output0[i0] = FAUSTFLOAT(fConst1 * (fRec0[0] * (fConst34 + fConst36 + fConst37 * fRec1[0]) + fRec0[1] * (fConst39 + fConst41 + fConst42 * fRec1[0]) + fRec0[2] * (fConst44 + fConst46 + fConst47 * fRec1[0]) + fRec0[3] * (fConst48 + fConst49 + fConst50 * fRec1[0]) + fRec0[4] * (fConst51 + fConst52 + fConst53 * fRec1[0]) + fRec0[5] * (fConst54 + fConst55 + fConst56 * fRec1[0]) + fRec0[6] * (fConst57 + fConst58 + fConst59 * fRec1[0])) / fTemp0);
		fRec1[1] = fRec1[0];
		for (int j0 = 6; j0 > 0; j0 = j0 - 1) {
			fRec0[j0] = fRec0[j0 - 1];
		}
	}

	FAUSTFLOAT bufCl[smpCl.max_out_count(count)];
	int ReCount = smpCl.up(count, output0, bufCl);
	for (int i0 = 0; i0 < ReCount; i0 = i0 + 1) {
		double fTemp0 = double(bufCl[i0]);
		fVecCl0[0] = fTemp0;
		fRecCl7[0] = 0.93028479253239138 * (fTemp0 + fVecCl0[1]) - 0.86056958506478287 * fRecCl7[1];
		fRecCl6[0] = fRecCl7[0] - (1.8405051250752198 * fRecCl6[1] + 0.86129424393186271 * fRecCl6[2]);
		fRecCl8[0] = fConstCl6 * (0.027 * (fRecCl5[1] + fRecCl5[2]) - fConstCl7 * fRecCl8[1]);
		fRecCl5[0] = double(Ftrany(int(TRANY_TABLE_7199P_68k), double(0.92544984225177063 * (fRecCl6[0] + fRecCl6[2]) + fRecCl8[0] + 1.8508996845035413 * fRecCl6[1] + -3.5719810000000001))) + -117.70440740740739;
		fRecCl4[0] = 0.025000000000000001 * (fConstCl4 * fRecCl5[0] + fConstCl8 * fRecCl5[1]) - fConstCl9 * fRecCl4[1];
		fRecCl3[0] = 0.93028479253239138 * (fRecCl4[0] + fRecCl4[1]) - 0.86056958506478287 * fRecCl3[1];
		fRecCl2[0] = fRecCl3[0] - (1.8405051250752198 * fRecCl2[1] + 0.86129424393186271 * fRecCl2[2]);
		fRecCl9[0] = fConstCl6 * (0.027 * (fRecCl1[1] + fRecCl1[2]) - fConstCl7 * fRecCl9[1]);
		fRecCl1[0] = double(Ftrany(int(TRANY_TABLE_7199P_68k), double(0.92544984225177063 * (fRecCl2[0] + fRecCl2[2]) + fRecCl9[0] + 1.8508996845035413 * fRecCl2[1] + -3.5719810000000001))) + -117.70440740740739;
		fRecCl0[0] = 0.025000000000000001 * (fConstCl4 * fRecCl1[0] + fConstCl8 * fRecCl1[1]) - fConstCl9 * fRecCl0[1];
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
	reg.registerFloatVar("fumaster.Tone",N_("Tone"),"S","",&fVslider0, 0.5, 0.0, 0.98999999999999999, 0.01, 0);
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
