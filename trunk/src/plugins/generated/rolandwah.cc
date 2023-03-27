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
	double fConst4;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fVslider1;
	double fConst5;
	double fRec10[2];
	double fRec9[2];
	double fRec8[2];
	double fConst6;
	FAUSTFLOAT fVslider2;
	double fRec13[2];
	double fConst8;
	double fConst10;
	double fConst12;
	double fConst13;
	double fConst16;
	double fConst17;
	double fConst18;
	double fConst20;
	double fConst21;
	double fConst23;
	double fConst25;
	double fConst27;
	double fConst29;
	double fConst31;
	double fConst32;
	double fConst33;
	double fConst34;
	double fConst35;
	double fConst36;
	double fConst37;
	double fConst38;
	double fConst39;
	double fRec14[9];
	double fConst42;
	double fConst44;
	double fConst47;
	double fConst50;
	double fConst52;
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
	double fConst66;
	double fRec12[2];
	double fConst67;
	double fRec11[2];
	FAUSTFLOAT fVslider3;
	double fRec15[2];
	double fConst69;
	double fConst71;
	double fConst73;
	double fConst75;
	double fConst77;
	double fConst79;
	double fConst80;
	double fConst81;
	double fConst82;
	double fConst84;
	double fConst86;
	double fConst88;
	double fConst90;
	double fConst92;
	double fConst94;
	double fConst95;
	double fConst96;
	double fConst97;
	double fConst98;
	double fConst99;
	double fConst100;
	double fConst101;
	double fConst102;
	double fConst103;
	double fRec16[7];
	double fConst105;
	double fConst107;
	double fConst109;
	double fConst111;
	double fConst113;
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
	double fConst127;
	double fVec1[2];
	double fRec7[2];
	double fRec6[3];
	double fConst129;
	double fConst130;
	double fRec17[2];
	double fRec5[3];
	double fConst131;
	double fConst132;
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
	double fConst1 = std::tan(97.38937226128358 / fConst0);
	double fConst2 = 1.0 / fConst1;
	double fConst3 = fConst2 + 1.0;
	fConst4 = (1.0 - fConst2) / fConst3;
	fConst5 = 0.10471975511965977 / fConst0;
	fConst6 = std::exp(0.0 - 1e+02 / fConst0);
	double fConst7 = 9.64198439050231e-55 * fConst0;
	fConst8 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst7 + -5.76952472985784e-34) + -1.84629565839962e-29) + -5.28116058056682e-26) + -3.4488417342687e-23) + -6.7753494863719e-21) + -1.6046797673707e-19) + -6.03074438986166e-19;
	double fConst9 = 1.08067210692624e-54 * fConst0;
	fConst10 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (1.6917880698614e-33 - fConst9) + 2.29812823706864e-29) + 5.73340871630524e-26) + 3.80795187898005e-23) + 8.56555972538848e-21) + 5.00114968075696e-19) + 8.62923424920947e-18;
	double fConst11 = 8.60349117319693e-33 * fConst0;
	fConst12 = mydsp_faustpower4_f(fConst0);
	fConst13 = fConst12 * (fConst0 * (fConst0 * (7.42470650533226e-26 - fConst11) + -3.80828462584721e-23) + 8.28085042193987e-22);
	double fConst14 = 2.62267793598193e-32 * fConst0;
	double fConst15 = mydsp_faustpower3_f(fConst0);
	fConst16 = fConst15 * (fConst0 * (fConst0 * (fConst0 * (fConst14 + -2.30252524666021e-25) + 1.21809214941527e-22) + -4.47006878788668e-21) + 4.14042521096994e-20);
	fConst17 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst7 + 5.76952472985784e-34) + -1.84629565839962e-29) + 5.28116058056682e-26) + -3.4488417342687e-23) + 6.7753494863719e-21) + -1.6046797673707e-19) + 6.03074438986166e-19;
	fConst18 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (-1.6917880698614e-33 - fConst9) + 2.29812823706864e-29) + -5.73340871630524e-26) + 3.80795187898005e-23) + -8.56555972538848e-21) + 5.00114968075696e-19) + -8.62923424920947e-18;
	double fConst19 = 7.71358751240185e-54 * fConst0;
	fConst20 = mydsp_faustpower2_f(fConst0);
	fConst21 = fConst0 * (fConst0 * (fConst20 * (fConst0 * (fConst0 * (-3.46171483791471e-33 - fConst19) + 7.38518263359847e-29) + -1.05623211611336e-25) + 1.35506989727438e-20) + -6.41871906948282e-19) + 3.618446633917e-18;
	double fConst22 = 8.64537685540996e-54 * fConst0;
	fConst23 = fConst0 * (fConst0 * (fConst20 * (fConst0 * (fConst0 * (fConst22 + 1.01507284191684e-32) + -9.19251294827458e-29) + 1.14668174326105e-25) + -1.7131119450777e-20) + 2.00045987230279e-18) + -5.17754054952568e-17;
	double fConst24 = 2.69975562934065e-53 * fConst0;
	fConst25 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst24 + 8.07733462180098e-33) + -7.38518263359847e-29) + -1.05623211611336e-25) + 1.37953669370748e-22) + -1.35506989727438e-20) + -6.41871906948282e-19) + 8.44304214580633e-18;
	double fConst26 = 3.02588189939348e-53 * fConst0;
	fConst27 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (-2.36850329780596e-32 - fConst26) + 9.19251294827458e-29) + 1.14668174326105e-25) + -1.52318075159202e-22) + 1.7131119450777e-20) + 2.00045987230279e-18) + -1.20809279488933e-16;
	double fConst28 = 5.3995112586813e-53 * fConst0;
	fConst29 = fConst0 * (fConst0 * (fConst20 * (fConst0 * (fConst0 * (-8.07733462180098e-33 - fConst28) + -7.38518263359847e-29) + 3.16869634834009e-25) + -4.06520969182314e-20) + 6.41871906948282e-19) + 8.44304214580633e-18;
	double fConst30 = 6.05176379878697e-53 * fConst0;
	fConst31 = fConst0 * (fConst0 * (fConst20 * (fConst0 * (fConst0 * (fConst30 + 2.36850329780596e-32) + 9.19251294827458e-29) + -3.44004522978315e-25) + 5.13933583523309e-20) + -2.00045987230279e-18) + -1.20809279488933e-16;
	fConst32 = fConst20 * (fConst20 * (6.74938907335162e-53 * fConst20 + 1.84629565839962e-28) + -2.06930504056122e-22) + 1.6046797673707e-18;
	fConst33 = fConst20 * (fConst20 * (-2.29812823706864e-28 - 7.56470474848371e-53 * fConst20) + 2.28477112738803e-22) + -5.00114968075697e-18;
	fConst34 = fConst0 * (fConst0 * (fConst20 * (fConst0 * (fConst0 * (8.07733462180098e-33 - fConst28) + -7.38518263359847e-29) + -3.16869634834009e-25) + 4.06520969182314e-20) + 6.41871906948282e-19) + -8.44304214580633e-18;
	fConst35 = fConst0 * (fConst0 * (fConst20 * (fConst0 * (fConst0 * (fConst30 + -2.36850329780596e-32) + 9.19251294827458e-29) + 3.44004522978315e-25) + -5.13933583523309e-20) + -2.00045987230279e-18) + 1.20809279488933e-16;
	fConst36 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst24 + -8.07733462180098e-33) + -7.38518263359847e-29) + 1.05623211611336e-25) + 1.37953669370748e-22) + 1.35506989727438e-20) + -6.41871906948282e-19) + -8.44304214580633e-18;
	fConst37 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (2.36850329780596e-32 - fConst26) + 9.19251294827458e-29) + -1.14668174326105e-25) + -1.52318075159202e-22) + -1.7131119450777e-20) + 2.00045987230279e-18) + 1.20809279488933e-16;
	fConst38 = fConst0 * (fConst0 * (fConst20 * (fConst0 * (fConst0 * (3.46171483791471e-33 - fConst19) + 7.38518263359847e-29) + 1.05623211611336e-25) + -1.35506989727438e-20) + -6.41871906948282e-19) + -3.618446633917e-18;
	fConst39 = fConst0 * (fConst0 * (fConst20 * (fConst0 * (fConst0 * (fConst22 + -1.01507284191684e-32) + -9.19251294827458e-29) + -1.14668174326105e-25) + 1.7131119450777e-20) + 2.00045987230279e-18) + 5.17754054952568e-17;
	double fConst40 = 5.16209470391816e-32 * fConst0;
	double fConst41 = mydsp_faustpower5_f(fConst0);
	fConst42 = fConst41 * (fConst0 * (fConst40 + -2.9698826021329e-25) + 7.61656925169443e-23);
	double fConst43 = 1.57360676158916e-31 * fConst0;
	fConst44 = fConst15 * (fConst20 * (fConst0 * (9.21010098664083e-25 - fConst43) + -2.43618429883054e-22) + 8.28085042193987e-20);
	double fConst45 = 1.20448876424757e-31 * fConst0;
	double fConst46 = fConst0 * (2.9698826021329e-25 - fConst45);
	fConst47 = fConst12 * (fConst0 * (fConst46 + 7.61656925169443e-23) + -3.31234016877595e-21);
	double fConst48 = 3.6717491103747e-31 * fConst0;
	double fConst49 = fConst0 * (fConst48 + -9.21010098664083e-25);
	fConst50 = fConst15 * (fConst0 * (fConst0 * (fConst49 + -2.43618429883054e-22) + 1.78802751515467e-20) + -8.28085042193987e-20);
	double fConst51 = fConst0 * (fConst45 + 2.9698826021329e-25);
	fConst52 = fConst41 * (fConst51 + -2.28497077550833e-22);
	double fConst53 = fConst0 * (-9.21010098664083e-25 - fConst48);
	fConst54 = fConst15 * (fConst20 * (fConst53 + 7.30855289649162e-22) + -2.48425512658196e-19);
	fConst55 = 4.96851025316392e-21 - 7.42470650533226e-25 * fConst20;
	fConst56 = 2.30252524666021e-24 * fConst20 + -2.68204127273201e-20;
	fConst57 = fConst41 * (fConst46 + 2.28497077550833e-22);
	fConst58 = fConst15 * (fConst20 * (fConst49 + -7.30855289649162e-22) + 2.48425512658196e-19);
	fConst59 = fConst12 * (fConst0 * (fConst51 + -7.61656925169443e-23) + -3.31234016877595e-21);
	fConst60 = fConst15 * (fConst0 * (fConst0 * (fConst53 + 2.43618429883054e-22) + 1.78802751515467e-20) + 8.28085042193987e-20);
	fConst61 = fConst41 * (fConst0 * (-2.9698826021329e-25 - fConst40) + -7.61656925169443e-23);
	fConst62 = fConst15 * (fConst20 * (fConst0 * (fConst43 + 9.21010098664083e-25) + 2.43618429883054e-22) + -8.28085042193987e-20);
	fConst63 = fConst12 * (fConst0 * (fConst0 * (fConst11 + 7.42470650533226e-26) + 3.80828462584721e-23) + 8.28085042193987e-22);
	fConst64 = fConst15 * (fConst0 * (fConst0 * (fConst0 * (-2.30252524666021e-25 - fConst14) + -1.21809214941527e-22) + -4.47006878788668e-21) + -4.14042521096994e-20);
	fConst65 = std::exp(0.0 - 1e+01 / fConst0);
	fConst66 = 1.0 - fConst65;
	fConst67 = 1.0 - fConst6;
	double fConst68 = 4.29845675581904e-29 * fConst0;
	fConst69 = fConst20 * (fConst0 * (fConst0 * (fConst0 * (-3.19373566665743e-26 - fConst68) + -8.90038927961101e-23) + -4.87042253786579e-20) + -3.50713071672392e-19);
	double fConst70 = 1.72206886126217e-28 * fConst0;
	fConst71 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst70 + 1.1453389852842e-25) + 9.7683567600612e-23) + 5.2144154673581e-20) + 1.07969798611464e-18) + 5.31383441927866e-18);
	double fConst72 = 5.0345082751012e-30 * fConst0;
	fConst73 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst72 + 1.05561747816346e-26) + 2.55142258602227e-22) + 1.48648313435063e-19) + 3.76182116601294e-18) + 3.09198451037471e-17);
	double fConst74 = 7.18082556296232e-31 * fConst0;
	fConst75 = fConst15 * (fConst0 * (fConst0 * (fConst74 + -1.2196809675607e-26) + 1.81635217972948e-23) + -9.8345184835125e-22);
	double fConst76 = 7.16633351212421e-31 * fConst0;
	fConst77 = fConst20 * (fConst0 * (fConst0 * (fConst0 * (1.22012125074374e-26 - fConst76) + -1.83126711766163e-23) + 1.21592229012527e-21) + -1.2608516331659e-20);
	double fConst78 = 9.65744972703433e-31 * fConst0;
	fConst79 = fConst20 * (fConst0 * (fConst0 * (fConst0 * (3.08822188644282e-26 - fConst78) + -4.82624719521696e-23) + 2.88264605310366e-21) + -1.49007855810795e-20);
	fConst80 = fConst20 * (fConst0 * (fConst0 * (fConst0 * (3.19373566665743e-26 - fConst68) + -8.90038927961101e-23) + 4.87042253786579e-20) + -3.50713071672392e-19);
	fConst81 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst70 + -1.1453389852842e-25) + 9.7683567600612e-23) + -5.2144154673581e-20) + 1.07969798611464e-18) + -5.31383441927866e-18);
	fConst82 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst72 + -1.05561747816346e-26) + 2.55142258602227e-22) + -1.48648313435063e-19) + 3.76182116601294e-18) + -3.09198451037471e-17);
	double fConst83 = 2.57907405349142e-28 * fConst0;
	fConst84 = fConst20 * (fConst20 * (fConst0 * (fConst83 + -1.27749426666297e-25) + 1.7800778559222e-22) + -7.01426143344783e-19);
	double fConst85 = 1.0332413167573e-27 * fConst0;
	fConst86 = fConst0 * (fConst0 * (fConst20 * (fConst0 * (4.5813559411368e-25 - fConst85) + -1.95367135201224e-22) + 2.15939597222928e-18) + -2.12553376771146e-17);
	double fConst87 = 3.02070496506072e-29 * fConst0;
	fConst88 = fConst0 * (fConst0 * (fConst20 * (fConst0 * (4.22246991265385e-26 - fConst87) + -5.10284517204454e-22) + 7.52364233202588e-18) + -1.23679380414989e-16);
	double fConst89 = 6.44768513372856e-28 * fConst0;
	fConst90 = fConst20 * (fConst0 * (fConst0 * (fConst0 * (1.59686783332872e-25 - fConst89) + 8.90038927961101e-23) + -1.46112676135974e-19) + 3.50713071672392e-19);
	double fConst91 = 2.58310329189325e-27 * fConst0;
	fConst92 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst91 + -5.726694926421e-25) + -9.7683567600612e-23) + 1.56432464020743e-19) + -1.07969798611464e-18) + -2.65691720963933e-17);
	double fConst93 = 7.55176241265181e-29 * fConst0;
	fConst94 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst93 + -5.27808739081731e-26) + -2.55142258602227e-22) + 4.4594494030519e-19) + -3.76182116601294e-18) + -1.54599225518736e-16);
	fConst95 = fConst20 * (8.59691351163808e-28 * fConst20 + -3.5601557118444e-22) + 1.40285228668957e-18;
	fConst96 = fConst20 * (3.90734270402448e-22 - 3.44413772252433e-27 * fConst20) + -4.31879194445857e-18;
	fConst97 = fConst20 * (1.02056903440891e-21 - 1.00690165502024e-28 * fConst20) + -1.50472846640518e-17;
	fConst98 = fConst20 * (fConst0 * (fConst0 * (fConst0 * (-1.59686783332872e-25 - fConst89) + 8.90038927961101e-23) + 1.46112676135974e-19) + 3.50713071672392e-19);
	fConst99 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst91 + 5.726694926421e-25) + -9.7683567600612e-23) + -1.56432464020743e-19) + -1.07969798611464e-18) + 2.65691720963933e-17);
	fConst100 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst93 + 5.27808739081731e-26) + -2.55142258602227e-22) + -4.4594494030519e-19) + -3.76182116601294e-18) + 1.54599225518736e-16);
	fConst101 = fConst20 * (fConst20 * (fConst0 * (fConst83 + 1.27749426666297e-25) + 1.7800778559222e-22) + -7.01426143344783e-19);
	fConst102 = fConst0 * (fConst0 * (fConst20 * (fConst0 * (-4.5813559411368e-25 - fConst85) + -1.95367135201224e-22) + 2.15939597222928e-18) + 2.12553376771146e-17);
	fConst103 = fConst0 * (fConst0 * (fConst20 * (fConst0 * (-4.22246991265385e-26 - fConst87) + -5.10284517204454e-22) + 7.52364233202588e-18) + 1.23679380414989e-16);
	double fConst104 = 4.30849533777739e-30 * fConst0;
	fConst105 = fConst12 * (fConst0 * (4.87872387024281e-26 - fConst104) + -3.63270435945895e-23);
	double fConst106 = 4.29980010727452e-30 * fConst0;
	fConst107 = fConst20 * (fConst20 * (fConst0 * (fConst106 + -4.88048500297496e-26) + 3.66253423532326e-23) + -2.5217032663318e-20);
	double fConst108 = 5.7944698362206e-30 * fConst0;
	fConst109 = fConst20 * (fConst20 * (fConst0 * (fConst108 + -1.23528875457713e-25) + 9.65249439043393e-23) + -2.98015711621591e-20);
	double fConst110 = 1.07712383444435e-29 * fConst0;
	fConst111 = fConst15 * (fConst0 * (fConst0 * (fConst110 + -6.09840483780351e-26) + -1.81635217972948e-23) + 2.95035554505375e-21);
	double fConst112 = 1.07495002681863e-29 * fConst0;
	fConst113 = fConst20 * (fConst0 * (fConst0 * (fConst0 * (6.1006062537187e-26 - fConst112) + 1.83126711766163e-23) + -3.64776687037582e-21) + 1.2608516331659e-20);
	double fConst114 = 1.44861745905515e-29 * fConst0;
	fConst115 = fConst20 * (fConst0 * (fConst0 * (fConst0 * (1.54411094322141e-25 - fConst114) + 4.82624719521696e-23) + -8.64793815931099e-21) + 1.49007855810795e-20);
	fConst116 = fConst12 * (7.2654087189179e-23 - 1.43616511259246e-29 * fConst20);
	fConst117 = fConst20 * (fConst20 * (1.43326670242484e-29 * fConst20 + -7.32506847064652e-23) + 5.0434065326636e-20);
	fConst118 = fConst20 * (fConst20 * (1.93148994540687e-29 * fConst20 + -1.93049887808679e-22) + 5.96031423243182e-20);
	fConst119 = fConst15 * (fConst0 * (fConst0 * (fConst110 + 6.09840483780351e-26) + -1.81635217972948e-23) + -2.95035554505375e-21);
	fConst120 = fConst20 * (fConst0 * (fConst0 * (fConst0 * (-6.1006062537187e-26 - fConst112) + 1.83126711766163e-23) + 3.64776687037582e-21) + 1.2608516331659e-20);
	fConst121 = fConst20 * (fConst0 * (fConst0 * (fConst0 * (-1.54411094322141e-25 - fConst114) + 4.82624719521696e-23) + 8.64793815931099e-21) + 1.49007855810795e-20);
	fConst122 = fConst12 * (fConst0 * (-4.87872387024281e-26 - fConst104) + -3.63270435945895e-23);
	fConst123 = fConst20 * (fConst20 * (fConst0 * (fConst106 + 4.88048500297496e-26) + 3.66253423532326e-23) + -2.5217032663318e-20);
	fConst124 = fConst20 * (fConst20 * (fConst0 * (fConst108 + 1.23528875457713e-25) + 9.65249439043393e-23) + -2.98015711621591e-20);
	fConst125 = fConst15 * (fConst0 * (fConst0 * (fConst74 + 1.2196809675607e-26) + 1.81635217972948e-23) + 9.8345184835125e-22);
	fConst126 = fConst20 * (fConst0 * (fConst0 * (fConst0 * (-1.22012125074374e-26 - fConst76) + -1.83126711766163e-23) + -1.21592229012527e-21) + -1.2608516331659e-20);
	fConst127 = fConst20 * (fConst0 * (fConst0 * (fConst0 * (-3.08822188644282e-26 - fConst78) + -4.82624719521696e-23) + -2.88264605310366e-21) + -1.49007855810795e-20);
	double fConst128 = 1.0 / std::tan(270.1769682087222 / fConst0);
	fConst129 = 1.0 - fConst128;
	fConst130 = 1.0 / (fConst128 + 1.0);
	fConst131 = 1.0 / (fConst1 * fConst3);
	fConst132 = 0.0 - fConst131;
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
	double fSlow5 = fConst5 * double(fVslider1);
	double fSlow6 = 0.007000000000000006 * double(fVslider2);
	double fSlow7 = 0.004073836948085289 * (std::exp(1.0 - double(fVslider3)) + -1.0);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		double fTemp0 = double(input0[i0]);
		iVec0[0] = 1;
		fRec10[0] = fRec10[1] + fSlow5 * (0.0 - fRec8[1]);
		fRec9[0] = fSlow5 * fRec10[0] + double(1 - iVec0[1]) + fRec9[1];
		fRec8[0] = fRec9[0];
		fRec13[0] = fSlow6 + 0.993 * fRec13[1];
		double fTemp1 = fConst0 * (fConst10 + fConst8 * fRec13[0]) + 3.01537219493083e-17;
		fRec14[0] = fSlow0 * fTemp0 - (fRec14[1] * (fConst0 * (fConst39 + fConst38 * fRec13[0]) + 2.41229775594467e-16) + fRec14[2] * (fConst0 * (fConst37 + fConst36 * fRec13[0]) + 8.44304214580633e-16) + fRec14[3] * (fConst0 * (fConst35 + fConst34 * fRec13[0]) + 1.68860842916127e-15) + fRec14[4] * (fConst20 * (fConst33 + fConst32 * fRec13[0]) + 2.11076053645158e-15) + fRec14[5] * (fConst0 * (fConst31 + fConst29 * fRec13[0]) + 1.68860842916127e-15) + fRec14[6] * (fConst0 * (fConst27 + fConst25 * fRec13[0]) + 8.44304214580633e-16) + fRec14[7] * (fConst0 * (fConst23 + fConst21 * fRec13[0]) + 2.41229775594467e-16) + fRec14[8] * (fConst0 * (fConst18 + fConst17 * fRec13[0]) + 3.01537219493083e-17)) / fTemp1;
		double fTemp2 = (fRec14[0] * (fConst64 + fConst63 * fRec13[0]) + fRec14[1] * (fConst62 + fConst61 * fRec13[0]) + fRec14[2] * (fConst60 + fConst59 * fRec13[0]) + fRec14[3] * (fConst58 + fConst57 * fRec13[0]) + fConst12 * fRec14[4] * (fConst56 + fConst55 * fRec13[0]) + fRec14[5] * (fConst54 + fConst52 * fRec13[0]) + fRec14[6] * (fConst50 + fConst47 * fRec13[0]) + fRec14[7] * (fConst44 + fConst42 * fRec13[0]) + fRec14[8] * (fConst16 + fConst13 * fRec13[0])) / fTemp1;
		double fTemp3 = std::fabs(fTemp2);
		fRec12[0] = std::max<double>(fTemp3, fConst65 * fRec12[1] + fConst66 * fTemp3);
		fRec11[0] = fConst67 * fRec12[0] + fConst6 * fRec11[1];
		fRec15[0] = fSlow7 + 0.993 * fRec15[1];
		double fTemp4 = ((iSlow3) ? fRec15[0] : ((iSlow4) ? std::max<double>(0.09, std::min<double>(0.9, fRec11[0])) : 1.0 - std::max<double>(0.09, std::min<double>(0.9, 0.5 * (fRec8[0] + 1.0)))));
		double fTemp5 = fConst73 + fTemp4 * (fConst71 + fConst69 * fTemp4) + 8.05126427163433e-17;
		fRec16[0] = fTemp2 - (fRec16[1] * (fConst103 + fTemp4 * (fConst102 + fConst101 * fTemp4) + 4.8307585629806e-16) + fRec16[2] * (fConst100 + fTemp4 * (fConst99 + fConst98 * fTemp4) + 1.20768964074515e-15) + fRec16[3] * (fConst20 * (fConst97 + fTemp4 * (fConst96 + fConst95 * fTemp4)) + 1.61025285432687e-15) + fRec16[4] * (fConst94 + fTemp4 * (fConst92 + fConst90 * fTemp4) + 1.20768964074515e-15) + fRec16[5] * (fConst88 + fTemp4 * (fConst86 + fConst84 * fTemp4) + 4.8307585629806e-16) + fRec16[6] * (fConst82 + fTemp4 * (fConst81 + fConst80 * fTemp4) + 8.05126427163433e-17)) / fTemp5;
		double fTemp6 = (fRec16[0] * (fConst127 + fTemp4 * (fConst126 + fConst125 * fTemp4)) + fRec16[1] * (fConst124 + fTemp4 * (fConst123 + fConst122 * fTemp4)) + fRec16[2] * (fConst121 + fTemp4 * (fConst120 + fConst119 * fTemp4)) + fRec16[3] * (fConst118 + fTemp4 * (fConst117 + fConst116 * fTemp4)) + fRec16[4] * (fConst115 + fTemp4 * (fConst113 + fConst111 * fTemp4)) + fRec16[5] * (fConst109 + fTemp4 * (fConst107 + fConst105 * fTemp4)) + fRec16[6] * (fConst79 + fTemp4 * (fConst77 + fConst75 * fTemp4))) / fTemp5;
		fVec1[0] = fTemp6;
		fRec7[0] = 0.9302847925323914 * (fTemp6 + fVec1[1]) - 0.8605695850647829 * fRec7[1];
		fRec6[0] = fRec7[0] - (1.8405051250752198 * fRec6[1] + 0.8612942439318627 * fRec6[2]);
		fRec17[0] = fConst130 * (0.027 * (fRec5[1] + fRec5[2]) - fConst129 * fRec17[1]);
		fRec5[0] = Ftrany(TRANY_TABLE_KT88_68k, 0.9254498422517706 * (fRec6[0] + fRec6[2]) + fRec17[0] + 1.8508996845035413 * fRec6[1] + -5.562895) + -43.96685185185183;
		fRec4[0] = 0.025 * (fConst131 * fRec5[0] + fConst132 * fRec5[1]) - fConst4 * fRec4[1];
		fRec3[0] = 0.9302847925323914 * (fRec4[0] + fRec4[1]) - 0.8605695850647829 * fRec3[1];
		fRec2[0] = fRec3[0] - (1.8405051250752198 * fRec2[1] + 0.8612942439318627 * fRec2[2]);
		fRec18[0] = fConst130 * (0.027 * (fRec1[1] + fRec1[2]) - fConst129 * fRec18[1]);
		fRec1[0] = Ftrany(TRANY_TABLE_KT88_68k, 0.9254498422517706 * (fRec2[0] + fRec2[2]) + fRec18[0] + 1.8508996845035413 * fRec2[1] + -5.562895) + -43.96685185185183;
		fRec0[0] = 0.025 * (fConst131 * fRec1[0] + fConst132 * fRec1[1]) - fConst4 * fRec0[1];
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
