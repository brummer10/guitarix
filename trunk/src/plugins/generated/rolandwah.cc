// generated from file '../src/plugins/rolandwah.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"
#include "trany.h"

namespace pluginlib {
namespace rolandwah {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	int 	iVec0[2];
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	FAUSTFLOAT 	fslider1;
	double 	fConst9;
	double 	fRec10[2];
	double 	fRec9[2];
	double 	fRec8[2];
	FAUSTFLOAT 	fslider2;
	double 	fRec13[2];
	double 	fConst10;
	double 	fConst11;
	double 	fConst12;
	double 	fConst13;
	double 	fConst14;
	double 	fConst15;
	double 	fConst16;
	double 	fConst17;
	double 	fConst18;
	double 	fConst19;
	double 	fConst20;
	double 	fConst21;
	double 	fConst22;
	double 	fConst23;
	double 	fConst24;
	double 	fConst25;
	double 	fConst26;
	double 	fConst27;
	double 	fConst28;
	double 	fConst29;
	double 	fConst30;
	double 	fConst31;
	double 	fConst32;
	double 	fConst33;
	double 	fConst34;
	double 	fConst35;
	double 	fConst36;
	double 	fConst37;
	double 	fConst38;
	double 	fConst39;
	double 	fConst40;
	double 	fRec14[9];
	double 	fConst41;
	double 	fConst42;
	double 	fConst43;
	double 	fConst44;
	double 	fConst45;
	double 	fConst46;
	double 	fConst47;
	double 	fConst48;
	double 	fConst49;
	double 	fConst50;
	double 	fConst51;
	double 	fConst52;
	double 	fConst53;
	double 	fConst54;
	double 	fConst55;
	double 	fConst56;
	double 	fConst57;
	double 	fConst58;
	double 	fConst59;
	double 	fConst60;
	double 	fConst61;
	double 	fConst62;
	double 	fConst63;
	double 	fConst64;
	double 	fConst65;
	double 	fConst66;
	double 	fConst67;
	double 	fRec12[2];
	double 	fConst68;
	double 	fConst69;
	double 	fRec11[2];
	FAUSTFLOAT 	fslider3;
	double 	fRec15[2];
	FAUSTFLOAT 	fcheckbox0;
	double 	fConst70;
	double 	fConst71;
	double 	fConst72;
	double 	fConst73;
	double 	fConst74;
	double 	fConst75;
	double 	fConst76;
	double 	fConst77;
	double 	fConst78;
	double 	fConst79;
	double 	fConst80;
	double 	fConst81;
	double 	fConst82;
	double 	fConst83;
	double 	fConst84;
	double 	fConst85;
	double 	fConst86;
	double 	fConst87;
	double 	fConst88;
	double 	fConst89;
	double 	fConst90;
	double 	fConst91;
	double 	fConst92;
	double 	fConst93;
	double 	fConst94;
	double 	fConst95;
	double 	fConst96;
	double 	fConst97;
	double 	fConst98;
	double 	fConst99;
	double 	fConst100;
	double 	fConst101;
	double 	fConst102;
	double 	fConst103;
	double 	fRec16[7];
	double 	fConst104;
	double 	fConst105;
	double 	fConst106;
	double 	fConst107;
	double 	fConst108;
	double 	fConst109;
	double 	fConst110;
	double 	fConst111;
	double 	fConst112;
	double 	fConst113;
	double 	fConst114;
	double 	fConst115;
	double 	fConst116;
	double 	fConst117;
	double 	fConst118;
	double 	fConst119;
	double 	fConst120;
	double 	fConst121;
	double 	fConst122;
	double 	fConst123;
	double 	fConst124;
	double 	fConst125;
	double 	fConst126;
	double 	fConst127;
	double 	fVec1[2];
	double 	fConst128;
	double 	fConst129;
	double 	fConst130;
	double 	fRec7[2];
	double 	fRec6[3];
	double 	fConst131;
	double 	fConst132;
	double 	fConst133;
	double 	fConst134;
	double 	fRec17[2];
	double 	fRec5[3];
	double 	fConst135;
	double 	fConst136;
	double 	fConst137;
	double 	fConst138;
	double 	fConst139;
	double 	fRec4[2];
	double 	fConst140;
	double 	fRec3[2];
	double 	fRec2[3];
	double 	fRec18[2];
	double 	fRec1[3];
	double 	fRec0[2];
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
	for (int i=0; i<2; i++) iVec0[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<9; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<7; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<3; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = tan((50265.48245743669 / double(iConst0)));
	fConst2 = (2 * (1 - (1.0 / faustpower<2>(fConst1))));
	fConst3 = (1.0 / fConst1);
	fConst4 = (1 + ((fConst3 - 1.0000000000000004) / fConst1));
	fConst5 = (1.0 / (1 + ((1.0000000000000004 + fConst3) / fConst1)));
	fConst6 = double(iConst0);
	fConst7 = (5.0345082751012e-30 * fConst6);
	fConst8 = (3.09198451037471e-17 + (fConst6 * (3.76182116601294e-18 + (fConst6 * (1.48648313435063e-19 + (fConst6 * (2.55142258602227e-22 + (fConst6 * (1.05561747816346e-26 + fConst7)))))))));
	fConst9 = (0.10471975511965977 / double(iConst0));
	fConst10 = (9.64198439050231e-55 * fConst6);
	fConst11 = ((fConst6 * ((fConst6 * ((fConst6 * ((fConst6 * ((fConst6 * ((fConst6 * (fConst10 - 5.76952472985784e-34)) - 1.84629565839962e-29)) - 5.28116058056682e-26)) - 3.4488417342687e-23)) - 6.7753494863719e-21)) - 1.6046797673707e-19)) - 6.03074438986166e-19);
	fConst12 = (1.08067210692624e-54 * fConst6);
	fConst13 = (8.62923424920947e-18 + (fConst6 * (5.00114968075696e-19 + (fConst6 * (8.56555972538848e-21 + (fConst6 * (3.80795187898005e-23 + (fConst6 * (5.73340871630524e-26 + (fConst6 * (2.29812823706864e-29 + (fConst6 * (1.6917880698614e-33 - fConst12)))))))))))));
	fConst14 = (8.60349117319693e-33 * fConst6);
	fConst15 = (fConst6 * (8.28085042193987e-22 + (fConst6 * ((fConst6 * (7.42470650533226e-26 - fConst14)) - 3.80828462584721e-23))));
	fConst16 = (2.62267793598193e-32 * fConst6);
	fConst17 = (4.14042521096994e-20 + (fConst6 * ((fConst6 * (1.21809214941527e-22 + (fConst6 * (fConst16 - 2.30252524666021e-25)))) - 4.47006878788668e-21)));
	fConst18 = (6.03074438986166e-19 + (fConst6 * ((fConst6 * (6.7753494863719e-21 + (fConst6 * ((fConst6 * (5.28116058056682e-26 + (fConst6 * ((fConst6 * (5.76952472985784e-34 + fConst10)) - 1.84629565839962e-29)))) - 3.4488417342687e-23)))) - 1.6046797673707e-19)));
	fConst19 = ((fConst6 * (5.00114968075696e-19 + (fConst6 * ((fConst6 * (3.80795187898005e-23 + (fConst6 * ((fConst6 * (2.29812823706864e-29 + (fConst6 * (0 - (1.6917880698614e-33 + fConst12))))) - 5.73340871630524e-26)))) - 8.56555972538848e-21)))) - 8.62923424920947e-18);
	fConst20 = (7.71358751240185e-54 * fConst6);
	fConst21 = faustpower<2>(fConst6);
	fConst22 = (3.618446633917e-18 + (fConst6 * ((fConst6 * (1.35506989727438e-20 + (fConst21 * ((fConst6 * (7.38518263359847e-29 + (fConst6 * (0 - (3.46171483791471e-33 + fConst20))))) - 1.05623211611336e-25)))) - 6.41871906948282e-19)));
	fConst23 = (8.64537685540996e-54 * fConst6);
	fConst24 = ((fConst6 * (2.00045987230279e-18 + (fConst6 * ((fConst21 * (1.14668174326105e-25 + (fConst6 * ((fConst6 * (1.01507284191684e-32 + fConst23)) - 9.19251294827458e-29)))) - 1.7131119450777e-20)))) - 5.17754054952568e-17);
	fConst25 = (2.69975562934065e-53 * fConst6);
	fConst26 = (8.44304214580633e-18 + (fConst6 * ((fConst6 * ((fConst6 * (1.37953669370748e-22 + (fConst6 * ((fConst6 * ((fConst6 * (8.07733462180098e-33 + fConst25)) - 7.38518263359847e-29)) - 1.05623211611336e-25)))) - 1.35506989727438e-20)) - 6.41871906948282e-19)));
	fConst27 = (3.02588189939348e-53 * fConst6);
	fConst28 = ((fConst6 * (2.00045987230279e-18 + (fConst6 * (1.7131119450777e-20 + (fConst6 * ((fConst6 * (1.14668174326105e-25 + (fConst6 * (9.19251294827458e-29 + (fConst6 * (0 - (2.36850329780596e-32 + fConst27))))))) - 1.52318075159202e-22)))))) - 1.20809279488933e-16);
	fConst29 = (5.3995112586813e-53 * fConst6);
	fConst30 = (8.44304214580633e-18 + (fConst6 * (6.41871906948282e-19 + (fConst6 * ((fConst21 * (3.16869634834009e-25 + (fConst6 * ((fConst6 * (0 - (8.07733462180098e-33 + fConst29))) - 7.38518263359847e-29)))) - 4.06520969182314e-20)))));
	fConst31 = (6.05176379878697e-53 * fConst6);
	fConst32 = ((fConst6 * ((fConst6 * (5.13933583523309e-20 + (fConst21 * ((fConst6 * (9.19251294827458e-29 + (fConst6 * (2.36850329780596e-32 + fConst31)))) - 3.44004522978315e-25)))) - 2.00045987230279e-18)) - 1.20809279488933e-16);
	fConst33 = (1.6046797673707e-18 + (fConst21 * ((fConst21 * (1.84629565839962e-28 + (6.74938907335162e-53 * fConst21))) - 2.06930504056122e-22)));
	fConst34 = ((fConst21 * (2.28477112738803e-22 + (fConst21 * (0 - (2.29812823706864e-28 + (7.56470474848371e-53 * fConst21)))))) - 5.00114968075697e-18);
	fConst35 = ((fConst6 * (6.41871906948282e-19 + (fConst6 * (4.06520969182314e-20 + (fConst21 * ((fConst6 * ((fConst6 * (8.07733462180098e-33 - fConst29)) - 7.38518263359847e-29)) - 3.16869634834009e-25)))))) - 8.44304214580633e-18);
	fConst36 = (1.20809279488933e-16 + (fConst6 * ((fConst6 * ((fConst21 * (3.44004522978315e-25 + (fConst6 * (9.19251294827458e-29 + (fConst6 * (fConst31 - 2.36850329780596e-32)))))) - 5.13933583523309e-20)) - 2.00045987230279e-18)));
	fConst37 = ((fConst6 * ((fConst6 * (1.35506989727438e-20 + (fConst6 * (1.37953669370748e-22 + (fConst6 * (1.05623211611336e-25 + (fConst6 * ((fConst6 * (fConst25 - 8.07733462180098e-33)) - 7.38518263359847e-29)))))))) - 6.41871906948282e-19)) - 8.44304214580633e-18);
	fConst38 = (1.20809279488933e-16 + (fConst6 * (2.00045987230279e-18 + (fConst6 * ((fConst6 * ((fConst6 * ((fConst6 * (9.19251294827458e-29 + (fConst6 * (2.36850329780596e-32 - fConst27)))) - 1.14668174326105e-25)) - 1.52318075159202e-22)) - 1.7131119450777e-20)))));
	fConst39 = ((fConst6 * ((fConst6 * ((fConst21 * (1.05623211611336e-25 + (fConst6 * (7.38518263359847e-29 + (fConst6 * (3.46171483791471e-33 - fConst20)))))) - 1.35506989727438e-20)) - 6.41871906948282e-19)) - 3.618446633917e-18);
	fConst40 = (5.17754054952568e-17 + (fConst6 * (2.00045987230279e-18 + (fConst6 * (1.7131119450777e-20 + (fConst21 * ((fConst6 * ((fConst6 * (fConst23 - 1.01507284191684e-32)) - 9.19251294827458e-29)) - 1.14668174326105e-25)))))));
	fConst41 = (5.16209470391816e-32 * fConst6);
	fConst42 = (fConst21 * (7.61656925169443e-23 + (fConst6 * (fConst41 - 2.9698826021329e-25))));
	fConst43 = (1.57360676158916e-31 * fConst6);
	fConst44 = (8.28085042193987e-20 + (fConst21 * ((fConst6 * (9.21010098664083e-25 - fConst43)) - 2.43618429883054e-22)));
	fConst45 = (1.20448876424757e-31 * fConst6);
	fConst46 = (fConst6 * (2.9698826021329e-25 - fConst45));
	fConst47 = (fConst6 * ((fConst6 * (7.61656925169443e-23 + fConst46)) - 3.31234016877595e-21));
	fConst48 = (3.6717491103747e-31 * fConst6);
	fConst49 = (fConst6 * (fConst48 - 9.21010098664083e-25));
	fConst50 = ((fConst6 * (1.78802751515467e-20 + (fConst6 * (fConst49 - 2.43618429883054e-22)))) - 8.28085042193987e-20);
	fConst51 = (fConst6 * (2.9698826021329e-25 + fConst45));
	fConst52 = (fConst21 * (fConst51 - 2.28497077550833e-22));
	fConst53 = (fConst6 * (0 - (9.21010098664083e-25 + fConst48)));
	fConst54 = ((fConst21 * (7.30855289649162e-22 + fConst53)) - 2.48425512658196e-19);
	fConst55 = (4.96851025316392e-21 - (7.42470650533226e-25 * fConst21));
	fConst56 = ((2.30252524666021e-24 * fConst21) - 2.68204127273201e-20);
	fConst57 = (fConst21 * (2.28497077550833e-22 + fConst46));
	fConst58 = (2.48425512658196e-19 + (fConst21 * (fConst49 - 7.30855289649162e-22)));
	fConst59 = (fConst6 * ((fConst6 * (fConst51 - 7.61656925169443e-23)) - 3.31234016877595e-21));
	fConst60 = (8.28085042193987e-20 + (fConst6 * (1.78802751515467e-20 + (fConst6 * (2.43618429883054e-22 + fConst53)))));
	fConst61 = (fConst21 * ((fConst6 * (0 - (2.9698826021329e-25 + fConst41))) - 7.61656925169443e-23));
	fConst62 = ((fConst21 * (2.43618429883054e-22 + (fConst6 * (9.21010098664083e-25 + fConst43)))) - 8.28085042193987e-20);
	fConst63 = (fConst6 * (8.28085042193987e-22 + (fConst6 * (3.80828462584721e-23 + (fConst6 * (7.42470650533226e-26 + fConst14))))));
	fConst64 = ((fConst6 * ((fConst6 * ((fConst6 * (0 - (2.30252524666021e-25 + fConst16))) - 1.21809214941527e-22)) - 4.47006878788668e-21)) - 4.14042521096994e-20);
	fConst65 = faustpower<3>(fConst6);
	fConst66 = exp((0 - (1e+01 / double(iConst0))));
	fConst67 = (1.0 - fConst66);
	fConst68 = exp((0 - (1e+02 / double(iConst0))));
	fConst69 = (1.0 - fConst68);
	fConst70 = (4.29845675581904e-29 * fConst6);
	fConst71 = (fConst6 * ((fConst6 * ((fConst6 * ((fConst6 * (0 - (3.19373566665743e-26 + fConst70))) - 8.90038927961101e-23)) - 4.87042253786579e-20)) - 3.50713071672392e-19));
	fConst72 = (1.72206886126217e-28 * fConst6);
	fConst73 = (5.31383441927866e-18 + (fConst6 * (1.07969798611464e-18 + (fConst6 * (5.2144154673581e-20 + (fConst6 * (9.7683567600612e-23 + (fConst6 * (1.1453389852842e-25 + fConst72)))))))));
	fConst74 = (9.65744972703433e-31 * fConst6);
	fConst75 = ((fConst6 * (2.88264605310366e-21 + (fConst6 * ((fConst6 * (3.08822188644282e-26 - fConst74)) - 4.82624719521696e-23)))) - 1.49007855810795e-20);
	fConst76 = (7.18082556296232e-31 * fConst6);
	fConst77 = (fConst6 * ((fConst6 * (1.81635217972948e-23 + (fConst6 * (fConst76 - 1.2196809675607e-26)))) - 9.8345184835125e-22));
	fConst78 = (7.16633351212421e-31 * fConst6);
	fConst79 = ((fConst6 * (1.21592229012527e-21 + (fConst6 * ((fConst6 * (1.22012125074374e-26 - fConst78)) - 1.83126711766163e-23)))) - 1.2608516331659e-20);
	fConst80 = ((fConst6 * (3.76182116601294e-18 + (fConst6 * ((fConst6 * (2.55142258602227e-22 + (fConst6 * (fConst7 - 1.05561747816346e-26)))) - 1.48648313435063e-19)))) - 3.09198451037471e-17);
	fConst81 = (fConst6 * ((fConst6 * (4.87042253786579e-20 + (fConst6 * ((fConst6 * (3.19373566665743e-26 - fConst70)) - 8.90038927961101e-23)))) - 3.50713071672392e-19));
	fConst82 = ((fConst6 * (1.07969798611464e-18 + (fConst6 * ((fConst6 * (9.7683567600612e-23 + (fConst6 * (fConst72 - 1.1453389852842e-25)))) - 5.2144154673581e-20)))) - 5.31383441927866e-18);
	fConst83 = (3.02070496506072e-29 * fConst6);
	fConst84 = ((fConst6 * (7.52364233202588e-18 + (fConst21 * ((fConst6 * (4.22246991265385e-26 - fConst83)) - 5.10284517204454e-22)))) - 1.23679380414989e-16);
	fConst85 = (2.57907405349142e-28 * fConst6);
	fConst86 = (fConst6 * ((fConst21 * (1.7800778559222e-22 + (fConst6 * (fConst85 - 1.27749426666297e-25)))) - 7.01426143344783e-19));
	fConst87 = (1.0332413167573e-27 * fConst6);
	fConst88 = ((fConst6 * (2.15939597222928e-18 + (fConst21 * ((fConst6 * (4.5813559411368e-25 - fConst87)) - 1.95367135201224e-22)))) - 2.12553376771146e-17);
	fConst89 = (7.55176241265181e-29 * fConst6);
	fConst90 = ((fConst6 * ((fConst6 * (4.4594494030519e-19 + (fConst6 * ((fConst6 * (fConst89 - 5.27808739081731e-26)) - 2.55142258602227e-22)))) - 3.76182116601294e-18)) - 1.54599225518736e-16);
	fConst91 = (6.44768513372856e-28 * fConst6);
	fConst92 = (fConst6 * (3.50713071672392e-19 + (fConst6 * ((fConst6 * (8.90038927961101e-23 + (fConst6 * (1.59686783332872e-25 - fConst91)))) - 1.46112676135974e-19))));
	fConst93 = (2.58310329189325e-27 * fConst6);
	fConst94 = ((fConst6 * ((fConst6 * (1.56432464020743e-19 + (fConst6 * ((fConst6 * (fConst93 - 5.726694926421e-25)) - 9.7683567600612e-23)))) - 1.07969798611464e-18)) - 2.65691720963933e-17);
	fConst95 = ((fConst21 * (1.02056903440891e-21 - (1.00690165502024e-28 * fConst21))) - 1.50472846640518e-17);
	fConst96 = (1.40285228668957e-18 + (fConst21 * ((8.59691351163808e-28 * fConst21) - 3.5601557118444e-22)));
	fConst97 = ((fConst21 * (3.90734270402448e-22 - (3.44413772252433e-27 * fConst21))) - 4.31879194445857e-18);
	fConst98 = (1.54599225518736e-16 + (fConst6 * ((fConst6 * ((fConst6 * ((fConst6 * (5.27808739081731e-26 + fConst89)) - 2.55142258602227e-22)) - 4.4594494030519e-19)) - 3.76182116601294e-18)));
	fConst99 = (fConst6 * (3.50713071672392e-19 + (fConst6 * (1.46112676135974e-19 + (fConst6 * (8.90038927961101e-23 + (fConst6 * (0 - (1.59686783332872e-25 + fConst91)))))))));
	fConst100 = (2.65691720963933e-17 + (fConst6 * ((fConst6 * ((fConst6 * ((fConst6 * (5.726694926421e-25 + fConst93)) - 9.7683567600612e-23)) - 1.56432464020743e-19)) - 1.07969798611464e-18)));
	fConst101 = (1.23679380414989e-16 + (fConst6 * (7.52364233202588e-18 + (fConst21 * ((fConst6 * (0 - (4.22246991265385e-26 + fConst83))) - 5.10284517204454e-22)))));
	fConst102 = (fConst6 * ((fConst21 * (1.7800778559222e-22 + (fConst6 * (1.27749426666297e-25 + fConst85)))) - 7.01426143344783e-19));
	fConst103 = (2.12553376771146e-17 + (fConst6 * (2.15939597222928e-18 + (fConst21 * ((fConst6 * (0 - (4.5813559411368e-25 + fConst87))) - 1.95367135201224e-22)))));
	fConst104 = (5.7944698362206e-30 * fConst6);
	fConst105 = ((fConst21 * (9.65249439043393e-23 + (fConst6 * (fConst104 - 1.23528875457713e-25)))) - 2.98015711621591e-20);
	fConst106 = (4.30849533777739e-30 * fConst6);
	fConst107 = (fConst21 * ((fConst6 * (4.87872387024281e-26 - fConst106)) - 3.63270435945895e-23));
	fConst108 = (4.29980010727452e-30 * fConst6);
	fConst109 = ((fConst21 * (3.66253423532326e-23 + (fConst6 * (fConst108 - 4.88048500297496e-26)))) - 2.5217032663318e-20);
	fConst110 = (1.44861745905515e-29 * fConst6);
	fConst111 = (1.49007855810795e-20 + (fConst6 * ((fConst6 * (4.82624719521696e-23 + (fConst6 * (1.54411094322141e-25 - fConst110)))) - 8.64793815931099e-21)));
	fConst112 = (1.07712383444435e-29 * fConst6);
	fConst113 = (fConst6 * (2.95035554505375e-21 + (fConst6 * ((fConst6 * (fConst112 - 6.09840483780351e-26)) - 1.81635217972948e-23))));
	fConst114 = (1.07495002681863e-29 * fConst6);
	fConst115 = (1.2608516331659e-20 + (fConst6 * ((fConst6 * (1.83126711766163e-23 + (fConst6 * (6.1006062537187e-26 - fConst114)))) - 3.64776687037582e-21)));
	fConst116 = (5.96031423243182e-20 + (fConst21 * ((1.93148994540687e-29 * fConst21) - 1.93049887808679e-22)));
	fConst117 = (fConst21 * (7.2654087189179e-23 - (1.43616511259246e-29 * fConst21)));
	fConst118 = (5.0434065326636e-20 + (fConst21 * ((1.43326670242484e-29 * fConst21) - 7.32506847064652e-23)));
	fConst119 = (1.49007855810795e-20 + (fConst6 * (8.64793815931099e-21 + (fConst6 * (4.82624719521696e-23 + (fConst6 * (0 - (1.54411094322141e-25 + fConst110))))))));
	fConst120 = (fConst6 * ((fConst6 * ((fConst6 * (6.09840483780351e-26 + fConst112)) - 1.81635217972948e-23)) - 2.95035554505375e-21));
	fConst121 = (1.2608516331659e-20 + (fConst6 * (3.64776687037582e-21 + (fConst6 * (1.83126711766163e-23 + (fConst6 * (0 - (6.1006062537187e-26 + fConst114))))))));
	fConst122 = ((fConst21 * (9.65249439043393e-23 + (fConst6 * (1.23528875457713e-25 + fConst104)))) - 2.98015711621591e-20);
	fConst123 = (fConst21 * ((fConst6 * (0 - (4.87872387024281e-26 + fConst106))) - 3.63270435945895e-23));
	fConst124 = ((fConst21 * (3.66253423532326e-23 + (fConst6 * (4.88048500297496e-26 + fConst108)))) - 2.5217032663318e-20);
	fConst125 = ((fConst6 * ((fConst6 * ((fConst6 * (0 - (3.08822188644282e-26 + fConst74))) - 4.82624719521696e-23)) - 2.88264605310366e-21)) - 1.49007855810795e-20);
	fConst126 = (fConst6 * (9.8345184835125e-22 + (fConst6 * (1.81635217972948e-23 + (fConst6 * (1.2196809675607e-26 + fConst76))))));
	fConst127 = ((fConst6 * ((fConst6 * ((fConst6 * (0 - (1.22012125074374e-26 + fConst78))) - 1.83126711766163e-23)) - 1.21592229012527e-21)) - 1.2608516331659e-20);
	fConst128 = (1 + fConst3);
	fConst129 = (fConst21 / fConst128);
	fConst130 = (0 - ((1 - fConst3) / fConst128));
	fConst131 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst132 = (1 + fConst131);
	fConst133 = (0.027 / fConst132);
	fConst134 = (0 - ((1 - fConst131) / fConst132));
	fConst135 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst136 = (0 - fConst135);
	fConst137 = (1 + fConst135);
	fConst138 = (0.025 / fConst137);
	fConst139 = (0 - ((1 - fConst135) / fConst137));
	fConst140 = (1.0 / fConst128);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlow0 = (0.01 * double(fslider0));
	double 	fSlow1 = (1 - fSlow0);
	double 	fSlow2 = (fConst9 * double(fslider1));
	double 	fSlow3 = (0.007000000000000006 * double(fslider2));
	double 	fSlow4 = (0.004073836948085289 * (exp((1 - double(fslider3))) - 1));
	int 	iSlow5 = int(double(fcheckbox0));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		iVec0[0] = 1;
		fRec10[0] = (fRec10[1] + (fSlow2 * (0 - fRec8[1])));
		fRec9[0] = ((1 + (fRec9[1] + (fSlow2 * fRec10[0]))) - iVec0[1]);
		fRec8[0] = fRec9[0];
		fRec13[0] = ((0.993 * fRec13[1]) + fSlow3);
		double fTemp1 = (3.01537219493083e-17 + (fConst6 * (fConst13 + (fConst11 * fRec13[0]))));
		fRec14[0] = ((fSlow0 * fTemp0) - (((((((((fRec14[1] * (2.41229775594467e-16 + (fConst6 * (fConst40 + (fConst39 * fRec13[0]))))) + (fRec14[2] * (8.44304214580633e-16 + (fConst6 * (fConst38 + (fConst37 * fRec13[0])))))) + (fRec14[3] * (1.68860842916127e-15 + (fConst6 * (fConst36 + (fConst35 * fRec13[0])))))) + (fRec14[4] * (2.11076053645158e-15 + (fConst21 * (fConst34 + (fConst33 * fRec13[0])))))) + (fRec14[5] * (1.68860842916127e-15 + (fConst6 * (fConst32 + (fConst30 * fRec13[0])))))) + (fRec14[6] * (8.44304214580633e-16 + (fConst6 * (fConst28 + (fConst26 * fRec13[0])))))) + (fRec14[7] * (2.41229775594467e-16 + (fConst6 * (fConst24 + (fConst22 * fRec13[0])))))) + (fRec14[8] * (3.01537219493083e-17 + (fConst6 * (fConst19 + (fConst18 * fRec13[0])))))) / fTemp1));
		double fTemp2 = (fConst65 * ((((((((((fRec14[0] * (fConst64 + (fConst63 * fRec13[0]))) + (fRec14[1] * (fConst62 + (fConst61 * fRec13[0])))) + (fRec14[2] * (fConst60 + (fConst59 * fRec13[0])))) + (fRec14[3] * (fConst58 + (fConst57 * fRec13[0])))) + (fConst6 * (fRec14[4] * (fConst56 + (fConst55 * fRec13[0]))))) + (fRec14[5] * (fConst54 + (fConst52 * fRec13[0])))) + (fRec14[6] * (fConst50 + (fConst47 * fRec13[0])))) + (fRec14[7] * (fConst44 + (fConst42 * fRec13[0])))) + (fRec14[8] * (fConst17 + (fConst15 * fRec13[0])))) / fTemp1));
		double fTemp3 = fabs(fTemp2);
		fRec12[0] = ((fConst66 * max(fTemp3, fRec12[1])) + (fConst67 * fTemp3));
		fRec11[0] = ((fConst68 * fRec11[1]) + (fConst69 * fRec12[0]));
		fRec15[0] = ((0.993 * fRec15[1]) + fSlow4);
		double fTemp4 = ((iSlow5==0)? fRec15[0] : ((iSlow5==1)?max(0.09, min(0.9, fRec11[0])):(1 - max(0.09, min(0.9, (0.5 * (1 + fRec8[0])))))) );
		double fTemp5 = (8.05126427163433e-17 + (fConst6 * ((fTemp4 * (fConst73 + (fConst71 * fTemp4))) + fConst8)));
		fRec16[0] = (fTemp2 - (((((((fRec16[1] * (4.8307585629806e-16 + (fConst6 * ((fTemp4 * (fConst103 + (fConst102 * fTemp4))) + fConst101)))) + (fRec16[2] * (1.20768964074515e-15 + (fConst6 * ((fTemp4 * (fConst100 + (fConst99 * fTemp4))) + fConst98))))) + (fRec16[3] * (1.61025285432687e-15 + (fConst21 * ((fTemp4 * (fConst97 + (fConst96 * fTemp4))) + fConst95))))) + (fRec16[4] * (1.20768964074515e-15 + (fConst6 * ((fTemp4 * (fConst94 + (fConst92 * fTemp4))) + fConst90))))) + (fRec16[5] * (4.8307585629806e-16 + (fConst6 * ((fTemp4 * (fConst88 + (fConst86 * fTemp4))) + fConst84))))) + (fRec16[6] * (8.05126427163433e-17 + (fConst6 * ((fTemp4 * (fConst82 + (fConst81 * fTemp4))) + fConst80))))) / fTemp5));
		double fTemp6 = ((((((((fRec16[0] * ((fTemp4 * (fConst127 + (fConst126 * fTemp4))) + fConst125)) + (fRec16[1] * ((fTemp4 * (fConst124 + (fConst123 * fTemp4))) + fConst122))) + (fRec16[2] * ((fTemp4 * (fConst121 + (fConst120 * fTemp4))) + fConst119))) + (fRec16[3] * ((fTemp4 * (fConst118 + (fConst117 * fTemp4))) + fConst116))) + (fRec16[4] * ((fTemp4 * (fConst115 + (fConst113 * fTemp4))) + fConst111))) + (fRec16[5] * ((fTemp4 * (fConst109 + (fConst107 * fTemp4))) + fConst105))) + (fRec16[6] * ((fTemp4 * (fConst79 + (fConst77 * fTemp4))) + fConst75))) / fTemp5);
		fVec1[0] = fTemp6;
		fRec7[0] = ((fConst130 * fRec7[1]) + (fConst129 * (fVec1[0] + fVec1[1])));
		fRec6[0] = (fRec7[0] - (fConst5 * ((fConst4 * fRec6[2]) + (fConst2 * fRec6[1]))));
		fRec17[0] = ((fConst134 * fRec17[1]) + (fConst133 * (fRec5[1] + fRec5[2])));
		fRec5[0] = (Ftrany(TRANY_TABLE_KT88_68k, ((fRec17[0] + (fConst5 * (fRec6[2] + (fRec6[0] + (2 * fRec6[1]))))) - 5.562895)) - 43.96685185185183);
		fRec4[0] = ((fConst139 * fRec4[1]) + (fConst138 * ((fConst135 * fRec5[0]) + (fConst136 * fRec5[1]))));
		fRec3[0] = ((fConst130 * fRec3[1]) + (fConst140 * (fRec4[0] + fRec4[1])));
		fRec2[0] = (fRec3[0] - (fConst5 * ((fConst4 * fRec2[2]) + (fConst2 * fRec2[1]))));
		fRec18[0] = ((fConst134 * fRec18[1]) + (fConst133 * (fRec1[1] + fRec1[2])));
		fRec1[0] = (Ftrany(TRANY_TABLE_KT88_68k, ((fRec18[0] + (fConst5 * (fRec2[2] + (fRec2[0] + (2 * fRec2[1]))))) - 5.562895)) - 43.96685185185183);
		fRec0[0] = ((fConst139 * fRec0[1]) + (fConst138 * ((fConst135 * fRec1[0]) + (fConst136 * fRec1[1]))));
		output0[i] = (FAUSTFLOAT)(fRec0[0] + (fSlow1 * fTemp0));
		// post processing
		fRec0[1] = fRec0[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec18[1] = fRec18[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec17[1] = fRec17[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec7[1] = fRec7[0];
		fVec1[1] = fVec1[0];
		for (int i=6; i>0; i--) fRec16[i] = fRec16[i-1];
		fRec15[1] = fRec15[0];
		fRec11[1] = fRec11[0];
		fRec12[1] = fRec12[0];
		for (int i=8; i>0; i--) fRec14[i] = fRec14[i-1];
		fRec13[1] = fRec13[0];
		fRec8[1] = fRec8[0];
		fRec9[1] = fRec9[0];
		fRec10[1] = fRec10[0];
		iVec0[1] = iVec0[0];
	}

}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("rolandwah.Fuzz",N_("Fuzz"),"S","",&fslider2, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("rolandwah.Wah",N_("Wah"),"S","",&fslider3, 0.5, 0.02, 1.0, 0.01);
	reg.registerVar("rolandwah.lfobpm",N_("Alien Freq"),"S",N_("LFO in Beats per Minute"),&fslider1, 24.0, 24.0, 3.6e+02, 1.0);
	static const value_pair fcheckbox0_values[] = {{"manual"},{"auto"},{"alien"},{0}};
	reg.registerEnumVar("rolandwah.mode","","B","",fcheckbox0_values,&fcheckbox0, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("rolandwah.wet_dry",N_("wet/dry"),"S",N_("percentage of processed signal in output signal"),&fslider0, 1e+02, 0.0, 1e+02, 1.0);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
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
