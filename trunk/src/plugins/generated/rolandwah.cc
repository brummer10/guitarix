// generated from file '../src/plugins/rolandwah.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"
#include "trany.h"

namespace pluginlib {
namespace rolandwah {

class Dsp: public PluginDef {
private:
	int fSampleRate;
	FAUSTFLOAT fVslider0;
	int iVec0[2];
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fVslider1;
	double fConst4;
	double fRec10[2];
	double fRec9[2];
	double fRec8[2];
	double fConst5;
	FAUSTFLOAT fVslider2;
	double fRec13[2];
	double fConst6;
	double fConst7;
	double fConst8;
	double fConst9;
	double fConst10;
	double fConst11;
	double fConst12;
	double fConst13;
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
	double fConst24;
	double fConst25;
	double fConst26;
	double fConst27;
	double fConst28;
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
	double fRec14[9];
	double fConst39;
	double fConst40;
	double fConst41;
	double fConst42;
	double fConst43;
	double fConst44;
	double fConst45;
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
	double fConst60;
	double fConst61;
	double fConst62;
	double fConst63;
	double fConst64;
	double fConst65;
	double fRec12[2];
	double fConst66;
	double fRec11[2];
	FAUSTFLOAT fVslider3;
	double fRec15[2];
	double fConst67;
	double fConst68;
	double fConst69;
	double fConst70;
	double fConst71;
	double fConst72;
	double fConst73;
	double fConst74;
	double fConst75;
	double fConst76;
	double fConst77;
	double fConst78;
	double fConst79;
	double fConst80;
	double fConst81;
	double fConst82;
	double fConst83;
	double fConst84;
	double fConst85;
	double fConst86;
	double fConst87;
	double fConst88;
	double fConst89;
	double fConst90;
	double fConst91;
	double fConst92;
	double fConst93;
	double fConst94;
	double fConst95;
	double fConst96;
	double fConst97;
	double fConst98;
	double fConst99;
	double fConst100;
	double fConst101;
	double fConst102;
	double fRec16[7];
	double fConst103;
	double fConst104;
	double fConst105;
	double fConst106;
	double fConst107;
	double fConst108;
	double fConst109;
	double fConst110;
	double fConst111;
	double fConst112;
	double fConst113;
	double fConst114;
	double fConst115;
	double fConst116;
	double fConst117;
	double fConst118;
	double fConst119;
	double fConst120;
	double fConst121;
	double fConst122;
	double fConst123;
	double fConst124;
	double fConst125;
	double fConst126;
	double fVec1[2];
	double fRec7[2];
	double fRec6[3];
	double fConst127;
	double fConst128;
	double fConst129;
	double fRec17[2];
	double fRec5[3];
	double fConst130;
	double fConst131;
	double fRec4[2];
	double fRec3[2];
	double fRec2[3];
	double fRec18[2];
	double fRec1[3];
	double fRec0[2];

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
	id = "rolandwah";
	name = N_("Roland Double Beat");
	groups = 0;
	description = N_("Roland Double Beat"); // description (tooltip)
	category = N_("Guitar Effects");       // category
	shortname = N_("Double Beat");     // shortname
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) iVec0[l0] = 0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec10[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec9[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec8[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fRec13[l4] = 0.0;
	for (int l5 = 0; l5 < 9; l5 = l5 + 1) fRec14[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fRec12[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec11[l7] = 0.0;
	for (int l8 = 0; l8 < 2; l8 = l8 + 1) fRec15[l8] = 0.0;
	for (int l9 = 0; l9 < 7; l9 = l9 + 1) fRec16[l9] = 0.0;
	for (int l10 = 0; l10 < 2; l10 = l10 + 1) fVec1[l10] = 0.0;
	for (int l11 = 0; l11 < 2; l11 = l11 + 1) fRec7[l11] = 0.0;
	for (int l12 = 0; l12 < 3; l12 = l12 + 1) fRec6[l12] = 0.0;
	for (int l13 = 0; l13 < 2; l13 = l13 + 1) fRec17[l13] = 0.0;
	for (int l14 = 0; l14 < 3; l14 = l14 + 1) fRec5[l14] = 0.0;
	for (int l15 = 0; l15 < 2; l15 = l15 + 1) fRec4[l15] = 0.0;
	for (int l16 = 0; l16 < 2; l16 = l16 + 1) fRec3[l16] = 0.0;
	for (int l17 = 0; l17 < 3; l17 = l17 + 1) fRec2[l17] = 0.0;
	for (int l18 = 0; l18 < 2; l18 = l18 + 1) fRec18[l18] = 0.0;
	for (int l19 = 0; l19 < 3; l19 = l19 + 1) fRec1[l19] = 0.0;
	for (int l20 = 0; l20 < 2; l20 = l20 + 1) fRec0[l20] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = std::tan(97.38937226128358 / fConst0);
	fConst2 = 1.0 / fConst1;
	fConst3 = 1.0 - fConst2;
	fConst4 = 0.10471975511965977 / fConst0;
	fConst5 = std::exp(-(1e+02 / fConst0));
	fConst6 = 9.64198439050231e-55 * fConst0;
	fConst7 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst6 + -5.76952472985784e-34) + -1.84629565839962e-29) + -5.28116058056682e-26) + -3.4488417342687e-23) + -6.7753494863719e-21) + -1.6046797673707e-19) + -6.03074438986166e-19;
	fConst8 = 1.08067210692624e-54 * fConst0;
	fConst9 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (1.6917880698614e-33 - fConst8) + 2.29812823706864e-29) + 5.73340871630524e-26) + 3.80795187898005e-23) + 8.56555972538848e-21) + 5.00114968075696e-19) + 8.62923424920947e-18;
	fConst10 = 8.60349117319693e-33 * fConst0;
	fConst11 = mydsp_faustpower4_f(fConst0);
	fConst12 = fConst11 * (fConst0 * (fConst0 * (7.42470650533226e-26 - fConst10) + -3.80828462584721e-23) + 8.28085042193987e-22);
	fConst13 = 2.62267793598193e-32 * fConst0;
	fConst14 = mydsp_faustpower3_f(fConst0);
	fConst15 = fConst14 * (fConst0 * (fConst0 * (fConst0 * (fConst13 + -2.30252524666021e-25) + 1.21809214941527e-22) + -4.47006878788668e-21) + 4.14042521096994e-20);
	fConst16 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst6 + 5.76952472985784e-34) + -1.84629565839962e-29) + 5.28116058056682e-26) + -3.4488417342687e-23) + 6.7753494863719e-21) + -1.6046797673707e-19) + 6.03074438986166e-19;
	fConst17 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (-1.6917880698614e-33 - fConst8) + 2.29812823706864e-29) + -5.73340871630524e-26) + 3.80795187898005e-23) + -8.56555972538848e-21) + 5.00114968075696e-19) + -8.62923424920947e-18;
	fConst18 = 7.71358751240185e-54 * fConst0;
	fConst19 = mydsp_faustpower2_f(fConst0);
	fConst20 = fConst0 * (fConst0 * (fConst19 * (fConst0 * (fConst0 * (-3.46171483791471e-33 - fConst18) + 7.38518263359847e-29) + -1.05623211611336e-25) + 1.35506989727438e-20) + -6.41871906948282e-19) + 3.618446633917e-18;
	fConst21 = 8.64537685540996e-54 * fConst0;
	fConst22 = fConst0 * (fConst0 * (fConst19 * (fConst0 * (fConst0 * (fConst21 + 1.01507284191684e-32) + -9.19251294827458e-29) + 1.14668174326105e-25) + -1.7131119450777e-20) + 2.00045987230279e-18) + -5.17754054952568e-17;
	fConst23 = 2.69975562934065e-53 * fConst0;
	fConst24 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst23 + 8.07733462180098e-33) + -7.38518263359847e-29) + -1.05623211611336e-25) + 1.37953669370748e-22) + -1.35506989727438e-20) + -6.41871906948282e-19) + 8.44304214580633e-18;
	fConst25 = 3.02588189939348e-53 * fConst0;
	fConst26 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (-2.36850329780596e-32 - fConst25) + 9.19251294827458e-29) + 1.14668174326105e-25) + -1.52318075159202e-22) + 1.7131119450777e-20) + 2.00045987230279e-18) + -1.20809279488933e-16;
	fConst27 = 5.3995112586813e-53 * fConst0;
	fConst28 = fConst0 * (fConst0 * (fConst19 * (fConst0 * (fConst0 * (-8.07733462180098e-33 - fConst27) + -7.38518263359847e-29) + 3.16869634834009e-25) + -4.06520969182314e-20) + 6.41871906948282e-19) + 8.44304214580633e-18;
	fConst29 = 6.05176379878697e-53 * fConst0;
	fConst30 = fConst0 * (fConst0 * (fConst19 * (fConst0 * (fConst0 * (fConst29 + 2.36850329780596e-32) + 9.19251294827458e-29) + -3.44004522978315e-25) + 5.13933583523309e-20) + -2.00045987230279e-18) + -1.20809279488933e-16;
	fConst31 = fConst19 * (fConst19 * (6.74938907335162e-53 * fConst19 + 1.84629565839962e-28) + -2.06930504056122e-22) + 1.6046797673707e-18;
	fConst32 = fConst19 * (fConst19 * (-2.29812823706864e-28 - 7.56470474848371e-53 * fConst19) + 2.28477112738803e-22) + -5.00114968075697e-18;
	fConst33 = fConst0 * (fConst0 * (fConst19 * (fConst0 * (fConst0 * (8.07733462180098e-33 - fConst27) + -7.38518263359847e-29) + -3.16869634834009e-25) + 4.06520969182314e-20) + 6.41871906948282e-19) + -8.44304214580633e-18;
	fConst34 = fConst0 * (fConst0 * (fConst19 * (fConst0 * (fConst0 * (fConst29 + -2.36850329780596e-32) + 9.19251294827458e-29) + 3.44004522978315e-25) + -5.13933583523309e-20) + -2.00045987230279e-18) + 1.20809279488933e-16;
	fConst35 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst23 + -8.07733462180098e-33) + -7.38518263359847e-29) + 1.05623211611336e-25) + 1.37953669370748e-22) + 1.35506989727438e-20) + -6.41871906948282e-19) + -8.44304214580633e-18;
	fConst36 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (2.36850329780596e-32 - fConst25) + 9.19251294827458e-29) + -1.14668174326105e-25) + -1.52318075159202e-22) + -1.7131119450777e-20) + 2.00045987230279e-18) + 1.20809279488933e-16;
	fConst37 = fConst0 * (fConst0 * (fConst19 * (fConst0 * (fConst0 * (3.46171483791471e-33 - fConst18) + 7.38518263359847e-29) + 1.05623211611336e-25) + -1.35506989727438e-20) + -6.41871906948282e-19) + -3.618446633917e-18;
	fConst38 = fConst0 * (fConst0 * (fConst19 * (fConst0 * (fConst0 * (fConst21 + -1.01507284191684e-32) + -9.19251294827458e-29) + -1.14668174326105e-25) + 1.7131119450777e-20) + 2.00045987230279e-18) + 5.17754054952568e-17;
	fConst39 = 5.16209470391816e-32 * fConst0;
	fConst40 = mydsp_faustpower5_f(fConst0);
	fConst41 = fConst40 * (fConst0 * (fConst39 + -2.9698826021329e-25) + 7.61656925169443e-23);
	fConst42 = 1.57360676158916e-31 * fConst0;
	fConst43 = fConst14 * (fConst19 * (fConst0 * (9.21010098664083e-25 - fConst42) + -2.43618429883054e-22) + 8.28085042193987e-20);
	fConst44 = 1.20448876424757e-31 * fConst0;
	fConst45 = fConst0 * (2.9698826021329e-25 - fConst44);
	fConst46 = fConst11 * (fConst0 * (fConst45 + 7.61656925169443e-23) + -3.31234016877595e-21);
	fConst47 = 3.6717491103747e-31 * fConst0;
	fConst48 = fConst0 * (fConst47 + -9.21010098664083e-25);
	fConst49 = fConst14 * (fConst0 * (fConst0 * (fConst48 + -2.43618429883054e-22) + 1.78802751515467e-20) + -8.28085042193987e-20);
	fConst50 = fConst0 * (fConst44 + 2.9698826021329e-25);
	fConst51 = fConst40 * (fConst50 + -2.28497077550833e-22);
	fConst52 = fConst0 * (-9.21010098664083e-25 - fConst47);
	fConst53 = fConst14 * (fConst19 * (fConst52 + 7.30855289649162e-22) + -2.48425512658196e-19);
	fConst54 = 4.96851025316392e-21 - 7.42470650533226e-25 * fConst19;
	fConst55 = 2.30252524666021e-24 * fConst19 + -2.68204127273201e-20;
	fConst56 = fConst40 * (fConst45 + 2.28497077550833e-22);
	fConst57 = fConst14 * (fConst19 * (fConst48 + -7.30855289649162e-22) + 2.48425512658196e-19);
	fConst58 = fConst11 * (fConst0 * (fConst50 + -7.61656925169443e-23) + -3.31234016877595e-21);
	fConst59 = fConst14 * (fConst0 * (fConst0 * (fConst52 + 2.43618429883054e-22) + 1.78802751515467e-20) + 8.28085042193987e-20);
	fConst60 = fConst40 * (fConst0 * (-2.9698826021329e-25 - fConst39) + -7.61656925169443e-23);
	fConst61 = fConst14 * (fConst19 * (fConst0 * (fConst42 + 9.21010098664083e-25) + 2.43618429883054e-22) + -8.28085042193987e-20);
	fConst62 = fConst11 * (fConst0 * (fConst0 * (fConst10 + 7.42470650533226e-26) + 3.80828462584721e-23) + 8.28085042193987e-22);
	fConst63 = fConst14 * (fConst0 * (fConst0 * (fConst0 * (-2.30252524666021e-25 - fConst13) + -1.21809214941527e-22) + -4.47006878788668e-21) + -4.14042521096994e-20);
	fConst64 = std::exp(-(1e+01 / fConst0));
	fConst65 = 1.0 - fConst64;
	fConst66 = 1.0 - fConst5;
	fConst67 = 4.29845675581904e-29 * fConst0;
	fConst68 = fConst19 * (fConst0 * (fConst0 * (fConst0 * (-3.19373566665743e-26 - fConst67) + -8.90038927961101e-23) + -4.87042253786579e-20) + -3.50713071672392e-19);
	fConst69 = 1.72206886126217e-28 * fConst0;
	fConst70 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst69 + 1.1453389852842e-25) + 9.7683567600612e-23) + 5.2144154673581e-20) + 1.07969798611464e-18) + 5.31383441927866e-18);
	fConst71 = 5.0345082751012e-30 * fConst0;
	fConst72 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst71 + 1.05561747816346e-26) + 2.55142258602227e-22) + 1.48648313435063e-19) + 3.76182116601294e-18) + 3.09198451037471e-17);
	fConst73 = 7.18082556296232e-31 * fConst0;
	fConst74 = fConst14 * (fConst0 * (fConst0 * (fConst73 + -1.2196809675607e-26) + 1.81635217972948e-23) + -9.8345184835125e-22);
	fConst75 = 7.16633351212421e-31 * fConst0;
	fConst76 = fConst19 * (fConst0 * (fConst0 * (fConst0 * (1.22012125074374e-26 - fConst75) + -1.83126711766163e-23) + 1.21592229012527e-21) + -1.2608516331659e-20);
	fConst77 = 9.65744972703433e-31 * fConst0;
	fConst78 = fConst19 * (fConst0 * (fConst0 * (fConst0 * (3.08822188644282e-26 - fConst77) + -4.82624719521696e-23) + 2.88264605310366e-21) + -1.49007855810795e-20);
	fConst79 = fConst19 * (fConst0 * (fConst0 * (fConst0 * (3.19373566665743e-26 - fConst67) + -8.90038927961101e-23) + 4.87042253786579e-20) + -3.50713071672392e-19);
	fConst80 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst69 + -1.1453389852842e-25) + 9.7683567600612e-23) + -5.2144154673581e-20) + 1.07969798611464e-18) + -5.31383441927866e-18);
	fConst81 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst71 + -1.05561747816346e-26) + 2.55142258602227e-22) + -1.48648313435063e-19) + 3.76182116601294e-18) + -3.09198451037471e-17);
	fConst82 = 2.57907405349142e-28 * fConst0;
	fConst83 = fConst19 * (fConst19 * (fConst0 * (fConst82 + -1.27749426666297e-25) + 1.7800778559222e-22) + -7.01426143344783e-19);
	fConst84 = 1.0332413167573e-27 * fConst0;
	fConst85 = fConst0 * (fConst0 * (fConst19 * (fConst0 * (4.5813559411368e-25 - fConst84) + -1.95367135201224e-22) + 2.15939597222928e-18) + -2.12553376771146e-17);
	fConst86 = 3.02070496506072e-29 * fConst0;
	fConst87 = fConst0 * (fConst0 * (fConst19 * (fConst0 * (4.22246991265385e-26 - fConst86) + -5.10284517204454e-22) + 7.52364233202588e-18) + -1.23679380414989e-16);
	fConst88 = 6.44768513372856e-28 * fConst0;
	fConst89 = fConst19 * (fConst0 * (fConst0 * (fConst0 * (1.59686783332872e-25 - fConst88) + 8.90038927961101e-23) + -1.46112676135974e-19) + 3.50713071672392e-19);
	fConst90 = 2.58310329189325e-27 * fConst0;
	fConst91 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst90 + -5.726694926421e-25) + -9.7683567600612e-23) + 1.56432464020743e-19) + -1.07969798611464e-18) + -2.65691720963933e-17);
	fConst92 = 7.55176241265181e-29 * fConst0;
	fConst93 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst92 + -5.27808739081731e-26) + -2.55142258602227e-22) + 4.4594494030519e-19) + -3.76182116601294e-18) + -1.54599225518736e-16);
	fConst94 = fConst19 * (8.59691351163808e-28 * fConst19 + -3.5601557118444e-22) + 1.40285228668957e-18;
	fConst95 = fConst19 * (3.90734270402448e-22 - 3.44413772252433e-27 * fConst19) + -4.31879194445857e-18;
	fConst96 = fConst19 * (1.02056903440891e-21 - 1.00690165502024e-28 * fConst19) + -1.50472846640518e-17;
	fConst97 = fConst19 * (fConst0 * (fConst0 * (fConst0 * (-1.59686783332872e-25 - fConst88) + 8.90038927961101e-23) + 1.46112676135974e-19) + 3.50713071672392e-19);
	fConst98 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst90 + 5.726694926421e-25) + -9.7683567600612e-23) + -1.56432464020743e-19) + -1.07969798611464e-18) + 2.65691720963933e-17);
	fConst99 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst92 + 5.27808739081731e-26) + -2.55142258602227e-22) + -4.4594494030519e-19) + -3.76182116601294e-18) + 1.54599225518736e-16);
	fConst100 = fConst19 * (fConst19 * (fConst0 * (fConst82 + 1.27749426666297e-25) + 1.7800778559222e-22) + -7.01426143344783e-19);
	fConst101 = fConst0 * (fConst0 * (fConst19 * (fConst0 * (-4.5813559411368e-25 - fConst84) + -1.95367135201224e-22) + 2.15939597222928e-18) + 2.12553376771146e-17);
	fConst102 = fConst0 * (fConst0 * (fConst19 * (fConst0 * (-4.22246991265385e-26 - fConst86) + -5.10284517204454e-22) + 7.52364233202588e-18) + 1.23679380414989e-16);
	fConst103 = 4.30849533777739e-30 * fConst0;
	fConst104 = fConst11 * (fConst0 * (4.87872387024281e-26 - fConst103) + -3.63270435945895e-23);
	fConst105 = 4.29980010727452e-30 * fConst0;
	fConst106 = fConst19 * (fConst19 * (fConst0 * (fConst105 + -4.88048500297496e-26) + 3.66253423532326e-23) + -2.5217032663318e-20);
	fConst107 = 5.7944698362206e-30 * fConst0;
	fConst108 = fConst19 * (fConst19 * (fConst0 * (fConst107 + -1.23528875457713e-25) + 9.65249439043393e-23) + -2.98015711621591e-20);
	fConst109 = 1.07712383444435e-29 * fConst0;
	fConst110 = fConst14 * (fConst0 * (fConst0 * (fConst109 + -6.09840483780351e-26) + -1.81635217972948e-23) + 2.95035554505375e-21);
	fConst111 = 1.07495002681863e-29 * fConst0;
	fConst112 = fConst19 * (fConst0 * (fConst0 * (fConst0 * (6.1006062537187e-26 - fConst111) + 1.83126711766163e-23) + -3.64776687037582e-21) + 1.2608516331659e-20);
	fConst113 = 1.44861745905515e-29 * fConst0;
	fConst114 = fConst19 * (fConst0 * (fConst0 * (fConst0 * (1.54411094322141e-25 - fConst113) + 4.82624719521696e-23) + -8.64793815931099e-21) + 1.49007855810795e-20);
	fConst115 = fConst11 * (7.2654087189179e-23 - 1.43616511259246e-29 * fConst19);
	fConst116 = fConst19 * (fConst19 * (1.43326670242484e-29 * fConst19 + -7.32506847064652e-23) + 5.0434065326636e-20);
	fConst117 = fConst19 * (fConst19 * (1.93148994540687e-29 * fConst19 + -1.93049887808679e-22) + 5.96031423243182e-20);
	fConst118 = fConst14 * (fConst0 * (fConst0 * (fConst109 + 6.09840483780351e-26) + -1.81635217972948e-23) + -2.95035554505375e-21);
	fConst119 = fConst19 * (fConst0 * (fConst0 * (fConst0 * (-6.1006062537187e-26 - fConst111) + 1.83126711766163e-23) + 3.64776687037582e-21) + 1.2608516331659e-20);
	fConst120 = fConst19 * (fConst0 * (fConst0 * (fConst0 * (-1.54411094322141e-25 - fConst113) + 4.82624719521696e-23) + 8.64793815931099e-21) + 1.49007855810795e-20);
	fConst121 = fConst11 * (fConst0 * (-4.87872387024281e-26 - fConst103) + -3.63270435945895e-23);
	fConst122 = fConst19 * (fConst19 * (fConst0 * (fConst105 + 4.88048500297496e-26) + 3.66253423532326e-23) + -2.5217032663318e-20);
	fConst123 = fConst19 * (fConst19 * (fConst0 * (fConst107 + 1.23528875457713e-25) + 9.65249439043393e-23) + -2.98015711621591e-20);
	fConst124 = fConst14 * (fConst0 * (fConst0 * (fConst73 + 1.2196809675607e-26) + 1.81635217972948e-23) + 9.8345184835125e-22);
	fConst125 = fConst19 * (fConst0 * (fConst0 * (fConst0 * (-1.22012125074374e-26 - fConst75) + -1.83126711766163e-23) + -1.21592229012527e-21) + -1.2608516331659e-20);
	fConst126 = fConst19 * (fConst0 * (fConst0 * (fConst0 * (-3.08822188644282e-26 - fConst77) + -4.82624719521696e-23) + -2.88264605310366e-21) + -1.49007855810795e-20);
	fConst127 = 1.0 / std::tan(270.1769682087222 / fConst0);
	fConst128 = 1.0 - fConst127;
	fConst129 = 1.0 / (fConst127 + 1.0);
	fConst130 = 0.025 / fConst1;
	fConst131 = 1.0 / (fConst2 + 1.0);
	clear_state_f();
}

void Dsp::init_static(unsigned int sample_rate, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double fSlow0 = 0.01 * double(fVslider0);
	double fSlow1 = 1.0 - fSlow0;
	double fSlow2 = double(fCheckbox0);
	int iSlow3 = fSlow2 == 0.0;
	int iSlow4 = fSlow2 == 1.0;
	double fSlow5 = fConst4 * double(fVslider1);
	double fSlow6 = 0.007000000000000006 * double(fVslider2);
	double fSlow7 = 0.004073836948085289 * (std::exp(1.0 - double(fVslider3)) + -1.0);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		double fTemp0 = double(input0[i0]);
		iVec0[0] = 1;
		fRec10[0] = fRec10[1] - fSlow5 * fRec8[1];
		fRec9[0] = fSlow5 * fRec10[0] + double(1 - iVec0[1]) + fRec9[1];
		fRec8[0] = fRec9[0];
		fRec13[0] = fSlow6 + 0.993 * fRec13[1];
		double fTemp1 = fConst0 * (fConst9 + fConst7 * fRec13[0]) + 3.01537219493083e-17;
		fRec14[0] = fSlow0 * fTemp0 - (fRec14[1] * (fConst0 * (fConst38 + fConst37 * fRec13[0]) + 2.41229775594467e-16) + fRec14[2] * (fConst0 * (fConst36 + fConst35 * fRec13[0]) + 8.44304214580633e-16) + fRec14[3] * (fConst0 * (fConst34 + fConst33 * fRec13[0]) + 1.68860842916127e-15) + fRec14[4] * (fConst19 * (fConst32 + fConst31 * fRec13[0]) + 2.11076053645158e-15) + fRec14[5] * (fConst0 * (fConst30 + fConst28 * fRec13[0]) + 1.68860842916127e-15) + fRec14[6] * (fConst0 * (fConst26 + fConst24 * fRec13[0]) + 8.44304214580633e-16) + fRec14[7] * (fConst0 * (fConst22 + fConst20 * fRec13[0]) + 2.41229775594467e-16) + fRec14[8] * (fConst0 * (fConst17 + fConst16 * fRec13[0]) + 3.01537219493083e-17)) / fTemp1;
		double fTemp2 = (fRec14[0] * (fConst63 + fConst62 * fRec13[0]) + fRec14[1] * (fConst61 + fConst60 * fRec13[0]) + fRec14[2] * (fConst59 + fConst58 * fRec13[0]) + fRec14[3] * (fConst57 + fConst56 * fRec13[0]) + fConst11 * fRec14[4] * (fConst55 + fConst54 * fRec13[0]) + fRec14[5] * (fConst53 + fConst51 * fRec13[0]) + fRec14[6] * (fConst49 + fConst46 * fRec13[0]) + fRec14[7] * (fConst43 + fConst41 * fRec13[0]) + fRec14[8] * (fConst15 + fConst12 * fRec13[0])) / fTemp1;
		double fTemp3 = std::fabs(fTemp2);
		fRec12[0] = std::max<double>(fTemp3, fConst64 * fRec12[1] + fConst65 * fTemp3);
		fRec11[0] = fConst66 * fRec12[0] + fConst5 * fRec11[1];
		fRec15[0] = fSlow7 + 0.993 * fRec15[1];
		double fTemp4 = ((iSlow3) ? fRec15[0] : ((iSlow4) ? std::max<double>(0.09, std::min<double>(0.9, fRec11[0])) : 1.0 - std::max<double>(0.09, std::min<double>(0.9, 0.5 * (fRec8[0] + 1.0)))));
		double fTemp5 = fConst72 + fTemp4 * (fConst70 + fConst68 * fTemp4) + 8.05126427163433e-17;
		fRec16[0] = fTemp2 - (fRec16[1] * (fConst102 + fTemp4 * (fConst101 + fConst100 * fTemp4) + 4.8307585629806e-16) + fRec16[2] * (fConst99 + fTemp4 * (fConst98 + fConst97 * fTemp4) + 1.20768964074515e-15) + fRec16[3] * (fConst19 * (fConst96 + fTemp4 * (fConst95 + fConst94 * fTemp4)) + 1.61025285432687e-15) + fRec16[4] * (fConst93 + fTemp4 * (fConst91 + fConst89 * fTemp4) + 1.20768964074515e-15) + fRec16[5] * (fConst87 + fTemp4 * (fConst85 + fConst83 * fTemp4) + 4.8307585629806e-16) + fRec16[6] * (fConst81 + fTemp4 * (fConst80 + fConst79 * fTemp4) + 8.05126427163433e-17)) / fTemp5;
		double fTemp6 = (fRec16[0] * (fConst126 + fTemp4 * (fConst125 + fConst124 * fTemp4)) + fRec16[1] * (fConst123 + fTemp4 * (fConst122 + fConst121 * fTemp4)) + fRec16[2] * (fConst120 + fTemp4 * (fConst119 + fConst118 * fTemp4)) + fRec16[3] * (fConst117 + fTemp4 * (fConst116 + fConst115 * fTemp4)) + fRec16[4] * (fConst114 + fTemp4 * (fConst112 + fConst110 * fTemp4)) + fRec16[5] * (fConst108 + fTemp4 * (fConst106 + fConst104 * fTemp4)) + fRec16[6] * (fConst78 + fTemp4 * (fConst76 + fConst74 * fTemp4))) / fTemp5;
		fVec1[0] = fTemp6;
		fRec7[0] = 0.9302847925323914 * (fTemp6 + fVec1[1]) - 0.8605695850647829 * fRec7[1];
		fRec6[0] = fRec7[0] - (1.8405051250752198 * fRec6[1] + 0.8612942439318627 * fRec6[2]);
		fRec17[0] = fConst129 * (0.027 * (fRec5[1] + fRec5[2]) - fConst128 * fRec17[1]);
		fRec5[0] = Ftrany(TRANY_TABLE_KT88_68k, 0.9254498422517706 * (fRec6[0] + fRec6[2]) + fRec17[0] + 1.8508996845035413 * fRec6[1] + -5.562895) + -43.96685185185183;
		fRec4[0] = fConst131 * (fConst130 * (fRec5[0] - fRec5[1]) - fConst3 * fRec4[1]);
		fRec3[0] = 0.9302847925323914 * (fRec4[0] + fRec4[1]) - 0.8605695850647829 * fRec3[1];
		fRec2[0] = fRec3[0] - (1.8405051250752198 * fRec2[1] + 0.8612942439318627 * fRec2[2]);
		fRec18[0] = fConst129 * (0.027 * (fRec1[1] + fRec1[2]) - fConst128 * fRec18[1]);
		fRec1[0] = Ftrany(TRANY_TABLE_KT88_68k, 0.9254498422517706 * (fRec2[0] + fRec2[2]) + fRec18[0] + 1.8508996845035413 * fRec2[1] + -5.562895) + -43.96685185185183;
		fRec0[0] = fConst131 * (fConst130 * (fRec1[0] - fRec1[1]) - fConst3 * fRec0[1]);
		output0[i0] = FAUSTFLOAT(fRec0[0] + fSlow1 * fTemp0);
		iVec0[1] = iVec0[0];
		fRec10[1] = fRec10[0];
		fRec9[1] = fRec9[0];
		fRec8[1] = fRec8[0];
		fRec13[1] = fRec13[0];
		for (int j0 = 8; j0 > 0; j0 = j0 - 1) {
			fRec14[j0] = fRec14[j0 - 1];
		}
		fRec12[1] = fRec12[0];
		fRec11[1] = fRec11[0];
		fRec15[1] = fRec15[0];
		for (int j1 = 6; j1 > 0; j1 = j1 - 1) {
			fRec16[j1] = fRec16[j1 - 1];
		}
		fVec1[1] = fVec1[0];
		fRec7[1] = fRec7[0];
		fRec6[2] = fRec6[1];
		fRec6[1] = fRec6[0];
		fRec17[1] = fRec17[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fRec18[1] = fRec18[0];
		fRec1[2] = fRec1[1];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerFloatVar("rolandwah.Fuzz",N_("Fuzz"),"S","",&fVslider2, 0.5, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("rolandwah.Wah",N_("Wah"),"S","",&fVslider3, 0.5, 0.02, 1.0, 0.01, 0);
	reg.registerFloatVar("rolandwah.lfobpm",N_("Alien Freq"),"S",N_("LFO in Beats per Minute"),&fVslider1, 24.0, 24.0, 3.6e+02, 1.0, 0);
	static const value_pair fCheckbox0_values[] = {{"manual"},{"auto"},{"alien"},{0}};
	reg.registerFloatVar("rolandwah.mode","","B","",&fCheckbox0, 0.0, 0.0, 1.0, 1.0, fCheckbox0_values);
	reg.registerFloatVar("rolandwah.wet_dry",N_("Dry/Wet"),"S",N_("percentage of processed signal in output signal"),&fVslider0, 1e+02, 0.0, 1e+02, 1.0, 0);
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
                  <object class=\"GtkBox\" id=\"vbox6\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <property name=\"spacing\">23</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label01:rack_label\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">Mode</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSelector\" id=\"gxselector1\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">rolandwah.mode</property>\n\
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
                        <property name=\"var_id\">rolandwah.lfobpm</property>\n\
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
                    <property name=\"position\">1</property>\n\
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
                        <property name=\"var_id\">rolandwah.Fuzz</property>\n\
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
                    <property name=\"position\">2</property>\n\
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
                      <object class=\"GxMidKnob\" id=\"gxbigknob3\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">rolandwah.Wah</property>\n\
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
                    <property name=\"position\">3</property>\n\
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
                        <property name=\"var_id\">rolandwah.wet_dry</property>\n\
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
                    <property name=\"position\">4</property>\n\
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
                <property name=\"var_id\">rolandwah.Wah</property>\n\
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
                <property name=\"label\" translatable=\"yes\">Wah</property>\n\
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
#define PARAM(p) ("rolandwah" "." p)

b.openHorizontalhideBox("");
    b.create_master_slider(PARAM("Wah"), "Wah");
b.closeBox();
b.openHorizontalBox("");

    b.create_selector(PARAM("mode"), "Mode");
    b.create_small_rackknobr(PARAM("lfobpm"), "Alien Freq");
    b.create_small_rackknobr(PARAM("Fuzz"), "Fuzz");
   // b.create_small_rackknobr(PARAM("Gain"), "Gain");
    b.create_small_rackknobr(PARAM("Wah"), "Wah");
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

} // end namespace rolandwah
} // end namespace pluginlib
