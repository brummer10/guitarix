// generated from file '../src/plugins/rolandwah.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"
#include "trany.h"

namespace pluginlib {
namespace rolandwah {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	int 	iVec0[2];
	FAUSTFLOAT 	fslider0;
	double 	fConst0;
	double 	fConst1;
	double 	fRec10[2];
	double 	fRec9[2];
	double 	fRec8[2];
	FAUSTFLOAT 	fslider1;
	double 	fRec13[2];
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	double 	fConst9;
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
	FAUSTFLOAT 	fslider2;
	double 	fRec14[9];
	double 	fConst34;
	double 	fConst35;
	double 	fConst36;
	double 	fConst37;
	double 	fConst38;
	double 	fConst39;
	double 	fConst40;
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
	double 	fRec12[2];
	double 	fConst61;
	double 	fConst62;
	double 	fRec11[2];
	FAUSTFLOAT 	fslider3;
	double 	fRec15[2];
	FAUSTFLOAT 	fcheckbox0;
	double 	fConst63;
	double 	fConst64;
	double 	fConst65;
	double 	fConst66;
	double 	fConst67;
	double 	fConst68;
	double 	fConst69;
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
	double 	fRec16[7];
	double 	fConst99;
	double 	fConst100;
	double 	fConst101;
	double 	fConst102;
	double 	fConst103;
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
	double 	fVec1[2];
	double 	fConst123;
	double 	fRec7[2];
	double 	fRec6[3];
	double 	fConst124;
	double 	fConst125;
	double 	fConst126;
	double 	fConst127;
	double 	fRec17[2];
	double 	fRec5[3];
	double 	fConst128;
	double 	fConst129;
	double 	fConst130;
	double 	fConst131;
	double 	fConst132;
	double 	fRec4[2];
	double 	fRec3[2];
	double 	fRec2[3];
	double 	fRec18[2];
	double 	fRec1[3];
	double 	fRec0[2];

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
	fConst0 = min(1.92e+05, max(1.0, (double)fSamplingFreq));
	fConst1 = (0.10471975511965977 / fConst0);
	fConst2 = double(fConst0);
	fConst3 = (9.64198439050231e-55 * fConst2);
	fConst4 = ((fConst2 * ((fConst2 * ((fConst2 * ((fConst2 * ((fConst2 * ((fConst2 * (fConst3 - 5.76952472985784e-34)) - 1.84629565839962e-29)) - 5.28116058056682e-26)) - 3.4488417342687e-23)) - 6.7753494863719e-21)) - 1.6046797673707e-19)) - 6.03074438986166e-19);
	fConst5 = (1.08067210692624e-54 * fConst2);
	fConst6 = (8.62923424920947e-18 + (fConst2 * (5.00114968075696e-19 + (fConst2 * (8.56555972538848e-21 + (fConst2 * (3.80795187898005e-23 + (fConst2 * (5.73340871630524e-26 + (fConst2 * (2.29812823706864e-29 + (fConst2 * (1.6917880698614e-33 - fConst5)))))))))))));
	fConst7 = (8.60349117319693e-33 * fConst2);
	fConst8 = (8.28085042193987e-22 + (fConst2 * ((fConst2 * (7.42470650533226e-26 - fConst7)) - 3.80828462584721e-23)));
	fConst9 = (2.62267793598193e-32 * fConst2);
	fConst10 = ((fConst2 * (1.21809214941527e-22 + (fConst2 * (fConst9 - 2.30252524666021e-25)))) - 4.47006878788668e-21);
	fConst11 = (6.03074438986166e-19 + (fConst2 * ((fConst2 * (6.7753494863719e-21 + (fConst2 * ((fConst2 * (5.28116058056682e-26 + (fConst2 * ((fConst2 * (5.76952472985784e-34 + fConst3)) - 1.84629565839962e-29)))) - 3.4488417342687e-23)))) - 1.6046797673707e-19)));
	fConst12 = ((fConst2 * (5.00114968075696e-19 + (fConst2 * ((fConst2 * (3.80795187898005e-23 + (fConst2 * ((fConst2 * (2.29812823706864e-29 + (fConst2 * (0 - (1.6917880698614e-33 + fConst5))))) - 5.73340871630524e-26)))) - 8.56555972538848e-21)))) - 8.62923424920947e-18);
	fConst13 = (7.71358751240185e-54 * fConst2);
	fConst14 = faustpower<2>(fConst2);
	fConst15 = (3.618446633917e-18 + (fConst2 * ((fConst2 * (1.35506989727438e-20 + (fConst14 * ((fConst2 * (7.38518263359847e-29 + (fConst2 * (0 - (3.46171483791471e-33 + fConst13))))) - 1.05623211611336e-25)))) - 6.41871906948282e-19)));
	fConst16 = (8.64537685540996e-54 * fConst2);
	fConst17 = ((fConst2 * (2.00045987230279e-18 + (fConst2 * ((fConst14 * (1.14668174326105e-25 + (fConst2 * ((fConst2 * (1.01507284191684e-32 + fConst16)) - 9.19251294827458e-29)))) - 1.7131119450777e-20)))) - 5.17754054952568e-17);
	fConst18 = (2.69975562934065e-53 * fConst2);
	fConst19 = (8.44304214580633e-18 + (fConst2 * ((fConst2 * ((fConst2 * (1.37953669370748e-22 + (fConst2 * ((fConst2 * ((fConst2 * (8.07733462180098e-33 + fConst18)) - 7.38518263359847e-29)) - 1.05623211611336e-25)))) - 1.35506989727438e-20)) - 6.41871906948282e-19)));
	fConst20 = (3.02588189939348e-53 * fConst2);
	fConst21 = ((fConst2 * (2.00045987230279e-18 + (fConst2 * (1.7131119450777e-20 + (fConst2 * ((fConst2 * (1.14668174326105e-25 + (fConst2 * (9.19251294827458e-29 + (fConst2 * (0 - (2.36850329780596e-32 + fConst20))))))) - 1.52318075159202e-22)))))) - 1.20809279488933e-16);
	fConst22 = (5.3995112586813e-53 * fConst2);
	fConst23 = (8.44304214580633e-18 + (fConst2 * (6.41871906948282e-19 + (fConst2 * ((fConst14 * (3.16869634834009e-25 + (fConst2 * ((fConst2 * (0 - (8.07733462180098e-33 + fConst22))) - 7.38518263359847e-29)))) - 4.06520969182314e-20)))));
	fConst24 = (6.05176379878697e-53 * fConst2);
	fConst25 = ((fConst2 * ((fConst2 * (5.13933583523309e-20 + (fConst14 * ((fConst2 * (9.19251294827458e-29 + (fConst2 * (2.36850329780596e-32 + fConst24)))) - 3.44004522978315e-25)))) - 2.00045987230279e-18)) - 1.20809279488933e-16);
	fConst26 = (1.6046797673707e-18 + (fConst14 * ((fConst14 * (1.84629565839962e-28 + (6.74938907335162e-53 * fConst14))) - 2.06930504056122e-22)));
	fConst27 = ((fConst14 * (2.28477112738803e-22 + (fConst14 * (0 - (2.29812823706864e-28 + (7.56470474848371e-53 * fConst14)))))) - 5.00114968075697e-18);
	fConst28 = ((fConst2 * (6.41871906948282e-19 + (fConst2 * (4.06520969182314e-20 + (fConst14 * ((fConst2 * ((fConst2 * (8.07733462180098e-33 - fConst22)) - 7.38518263359847e-29)) - 3.16869634834009e-25)))))) - 8.44304214580633e-18);
	fConst29 = (1.20809279488933e-16 + (fConst2 * ((fConst2 * ((fConst14 * (3.44004522978315e-25 + (fConst2 * (9.19251294827458e-29 + (fConst2 * (fConst24 - 2.36850329780596e-32)))))) - 5.13933583523309e-20)) - 2.00045987230279e-18)));
	fConst30 = ((fConst2 * ((fConst2 * (1.35506989727438e-20 + (fConst2 * (1.37953669370748e-22 + (fConst2 * (1.05623211611336e-25 + (fConst2 * ((fConst2 * (fConst18 - 8.07733462180098e-33)) - 7.38518263359847e-29)))))))) - 6.41871906948282e-19)) - 8.44304214580633e-18);
	fConst31 = (1.20809279488933e-16 + (fConst2 * (2.00045987230279e-18 + (fConst2 * ((fConst2 * ((fConst2 * ((fConst2 * (9.19251294827458e-29 + (fConst2 * (2.36850329780596e-32 - fConst20)))) - 1.14668174326105e-25)) - 1.52318075159202e-22)) - 1.7131119450777e-20)))));
	fConst32 = ((fConst2 * ((fConst2 * ((fConst14 * (1.05623211611336e-25 + (fConst2 * (7.38518263359847e-29 + (fConst2 * (3.46171483791471e-33 - fConst13)))))) - 1.35506989727438e-20)) - 6.41871906948282e-19)) - 3.618446633917e-18);
	fConst33 = (5.17754054952568e-17 + (fConst2 * (2.00045987230279e-18 + (fConst2 * (1.7131119450777e-20 + (fConst14 * ((fConst2 * ((fConst2 * (fConst16 - 1.01507284191684e-32)) - 9.19251294827458e-29)) - 1.14668174326105e-25)))))));
	fConst34 = (5.16209470391816e-32 * fConst2);
	fConst35 = (7.61656925169443e-23 + (fConst2 * (fConst34 - 2.9698826021329e-25)));
	fConst36 = (1.57360676158916e-31 * fConst2);
	fConst37 = ((fConst2 * (9.21010098664083e-25 - fConst36)) - 2.43618429883054e-22);
	fConst38 = (1.20448876424757e-31 * fConst2);
	fConst39 = (fConst2 * (2.9698826021329e-25 - fConst38));
	fConst40 = ((fConst2 * (7.61656925169443e-23 + fConst39)) - 3.31234016877595e-21);
	fConst41 = (3.6717491103747e-31 * fConst2);
	fConst42 = (fConst2 * (fConst41 - 9.21010098664083e-25));
	fConst43 = (1.78802751515467e-20 + (fConst2 * (fConst42 - 2.43618429883054e-22)));
	fConst44 = (fConst2 * (2.9698826021329e-25 + fConst38));
	fConst45 = (fConst44 - 2.28497077550833e-22);
	fConst46 = (fConst2 * (0 - (9.21010098664083e-25 + fConst41)));
	fConst47 = (7.30855289649162e-22 + fConst46);
	fConst48 = (8.28085042193987e-22 + (fConst2 * (3.80828462584721e-23 + (fConst2 * (7.42470650533226e-26 + fConst7)))));
	fConst49 = ((fConst2 * ((fConst2 * (0 - (2.30252524666021e-25 + fConst9))) - 1.21809214941527e-22)) - 4.47006878788668e-21);
	fConst50 = (4.96851025316392e-21 - (7.42470650533226e-25 * fConst14));
	fConst51 = ((2.30252524666021e-24 * fConst14) - 2.68204127273201e-20);
	fConst52 = ((fConst2 * (0 - (2.9698826021329e-25 + fConst34))) - 7.61656925169443e-23);
	fConst53 = (2.43618429883054e-22 + (fConst2 * (9.21010098664083e-25 + fConst36)));
	fConst54 = ((fConst2 * (fConst44 - 7.61656925169443e-23)) - 3.31234016877595e-21);
	fConst55 = (1.78802751515467e-20 + (fConst2 * (2.43618429883054e-22 + fConst46)));
	fConst56 = (2.28497077550833e-22 + fConst39);
	fConst57 = (fConst42 - 7.30855289649162e-22);
	fConst58 = faustpower<3>(fConst2);
	fConst59 = exp((0 - (1e+01 / fConst0)));
	fConst60 = (1.0 - fConst59);
	fConst61 = exp((0 - (1e+02 / fConst0)));
	fConst62 = (1.0 - fConst61);
	fConst63 = (4.29845675581904e-29 * fConst2);
	fConst64 = ((fConst2 * ((fConst2 * ((fConst2 * (0 - (3.19373566665743e-26 + fConst63))) - 8.90038927961101e-23)) - 4.87042253786579e-20)) - 3.50713071672392e-19);
	fConst65 = (1.72206886126217e-28 * fConst2);
	fConst66 = (1.07969798611464e-18 + (fConst2 * (5.2144154673581e-20 + (fConst2 * (9.7683567600612e-23 + (fConst2 * (1.1453389852842e-25 + fConst65)))))));
	fConst67 = (5.0345082751012e-30 * fConst2);
	fConst68 = (3.09198451037471e-17 + (fConst2 * (3.76182116601294e-18 + (fConst2 * (1.48648313435063e-19 + (fConst2 * (2.55142258602227e-22 + (fConst2 * (1.05561747816346e-26 + fConst67)))))))));
	fConst69 = (7.18082556296232e-31 * fConst2);
	fConst70 = ((fConst2 * (1.81635217972948e-23 + (fConst2 * (fConst69 - 1.2196809675607e-26)))) - 9.8345184835125e-22);
	fConst71 = (7.16633351212421e-31 * fConst2);
	fConst72 = (1.21592229012527e-21 + (fConst2 * ((fConst2 * (1.22012125074374e-26 - fConst71)) - 1.83126711766163e-23)));
	fConst73 = (9.65744972703433e-31 * fConst2);
	fConst74 = ((fConst2 * (2.88264605310366e-21 + (fConst2 * ((fConst2 * (3.08822188644282e-26 - fConst73)) - 4.82624719521696e-23)))) - 1.49007855810795e-20);
	fConst75 = ((fConst2 * (4.87042253786579e-20 + (fConst2 * ((fConst2 * (3.19373566665743e-26 - fConst63)) - 8.90038927961101e-23)))) - 3.50713071672392e-19);
	fConst76 = (1.07969798611464e-18 + (fConst2 * ((fConst2 * (9.7683567600612e-23 + (fConst2 * (fConst65 - 1.1453389852842e-25)))) - 5.2144154673581e-20)));
	fConst77 = ((fConst2 * (3.76182116601294e-18 + (fConst2 * ((fConst2 * (2.55142258602227e-22 + (fConst2 * (fConst67 - 1.05561747816346e-26)))) - 1.48648313435063e-19)))) - 3.09198451037471e-17);
	fConst78 = (2.57907405349142e-28 * fConst2);
	fConst79 = ((fConst14 * (1.7800778559222e-22 + (fConst2 * (fConst78 - 1.27749426666297e-25)))) - 7.01426143344783e-19);
	fConst80 = (1.0332413167573e-27 * fConst2);
	fConst81 = (2.15939597222928e-18 + (fConst14 * ((fConst2 * (4.5813559411368e-25 - fConst80)) - 1.95367135201224e-22)));
	fConst82 = (3.02070496506072e-29 * fConst2);
	fConst83 = ((fConst2 * (7.52364233202588e-18 + (fConst14 * ((fConst2 * (4.22246991265385e-26 - fConst82)) - 5.10284517204454e-22)))) - 1.23679380414989e-16);
	fConst84 = (6.44768513372856e-28 * fConst2);
	fConst85 = (3.50713071672392e-19 + (fConst2 * ((fConst2 * (8.90038927961101e-23 + (fConst2 * (1.59686783332872e-25 - fConst84)))) - 1.46112676135974e-19)));
	fConst86 = (2.58310329189325e-27 * fConst2);
	fConst87 = ((fConst2 * (1.56432464020743e-19 + (fConst2 * ((fConst2 * (fConst86 - 5.726694926421e-25)) - 9.7683567600612e-23)))) - 1.07969798611464e-18);
	fConst88 = (7.55176241265181e-29 * fConst2);
	fConst89 = ((fConst2 * ((fConst2 * (4.4594494030519e-19 + (fConst2 * ((fConst2 * (fConst88 - 5.27808739081731e-26)) - 2.55142258602227e-22)))) - 3.76182116601294e-18)) - 1.54599225518736e-16);
	fConst90 = (1.40285228668957e-18 + (fConst14 * ((8.59691351163808e-28 * fConst14) - 3.5601557118444e-22)));
	fConst91 = ((fConst14 * (3.90734270402448e-22 - (3.44413772252433e-27 * fConst14))) - 4.31879194445857e-18);
	fConst92 = ((fConst14 * (1.02056903440891e-21 - (1.00690165502024e-28 * fConst14))) - 1.50472846640518e-17);
	fConst93 = (3.50713071672392e-19 + (fConst2 * (1.46112676135974e-19 + (fConst2 * (8.90038927961101e-23 + (fConst2 * (0 - (1.59686783332872e-25 + fConst84))))))));
	fConst94 = ((fConst2 * ((fConst2 * ((fConst2 * (5.726694926421e-25 + fConst86)) - 9.7683567600612e-23)) - 1.56432464020743e-19)) - 1.07969798611464e-18);
	fConst95 = (1.54599225518736e-16 + (fConst2 * ((fConst2 * ((fConst2 * ((fConst2 * (5.27808739081731e-26 + fConst88)) - 2.55142258602227e-22)) - 4.4594494030519e-19)) - 3.76182116601294e-18)));
	fConst96 = ((fConst14 * (1.7800778559222e-22 + (fConst2 * (1.27749426666297e-25 + fConst78)))) - 7.01426143344783e-19);
	fConst97 = (2.15939597222928e-18 + (fConst14 * ((fConst2 * (0 - (4.5813559411368e-25 + fConst80))) - 1.95367135201224e-22)));
	fConst98 = (1.23679380414989e-16 + (fConst2 * (7.52364233202588e-18 + (fConst14 * ((fConst2 * (0 - (4.22246991265385e-26 + fConst82))) - 5.10284517204454e-22)))));
	fConst99 = (4.30849533777739e-30 * fConst2);
	fConst100 = ((fConst2 * (4.87872387024281e-26 - fConst99)) - 3.63270435945895e-23);
	fConst101 = (4.29980010727452e-30 * fConst2);
	fConst102 = (3.66253423532326e-23 + (fConst2 * (fConst101 - 4.88048500297496e-26)));
	fConst103 = (5.7944698362206e-30 * fConst2);
	fConst104 = ((fConst14 * (9.65249439043393e-23 + (fConst2 * (fConst103 - 1.23528875457713e-25)))) - 2.98015711621591e-20);
	fConst105 = (1.07712383444435e-29 * fConst2);
	fConst106 = (2.95035554505375e-21 + (fConst2 * ((fConst2 * (fConst105 - 6.09840483780351e-26)) - 1.81635217972948e-23)));
	fConst107 = (1.07495002681863e-29 * fConst2);
	fConst108 = ((fConst2 * (1.83126711766163e-23 + (fConst2 * (6.1006062537187e-26 - fConst107)))) - 3.64776687037582e-21);
	fConst109 = (1.44861745905515e-29 * fConst2);
	fConst110 = (1.49007855810795e-20 + (fConst2 * ((fConst2 * (4.82624719521696e-23 + (fConst2 * (1.54411094322141e-25 - fConst109)))) - 8.64793815931099e-21)));
	fConst111 = (7.2654087189179e-23 - (1.43616511259246e-29 * fConst14));
	fConst112 = ((1.43326670242484e-29 * fConst14) - 7.32506847064652e-23);
	fConst113 = (5.96031423243182e-20 + (fConst14 * ((1.93148994540687e-29 * fConst14) - 1.93049887808679e-22)));
	fConst114 = ((fConst2 * ((fConst2 * (6.09840483780351e-26 + fConst105)) - 1.81635217972948e-23)) - 2.95035554505375e-21);
	fConst115 = (3.64776687037582e-21 + (fConst2 * (1.83126711766163e-23 + (fConst2 * (0 - (6.1006062537187e-26 + fConst107))))));
	fConst116 = (1.49007855810795e-20 + (fConst2 * (8.64793815931099e-21 + (fConst2 * (4.82624719521696e-23 + (fConst2 * (0 - (1.54411094322141e-25 + fConst109))))))));
	fConst117 = ((fConst2 * (0 - (4.87872387024281e-26 + fConst99))) - 3.63270435945895e-23);
	fConst118 = (3.66253423532326e-23 + (fConst2 * (4.88048500297496e-26 + fConst101)));
	fConst119 = ((fConst14 * (9.65249439043393e-23 + (fConst2 * (1.23528875457713e-25 + fConst103)))) - 2.98015711621591e-20);
	fConst120 = (9.8345184835125e-22 + (fConst2 * (1.81635217972948e-23 + (fConst2 * (1.2196809675607e-26 + fConst69)))));
	fConst121 = ((fConst2 * ((fConst2 * (0 - (1.22012125074374e-26 + fConst71))) - 1.83126711766163e-23)) - 1.21592229012527e-21);
	fConst122 = ((fConst2 * ((fConst2 * ((fConst2 * (0 - (3.08822188644282e-26 + fConst73))) - 4.82624719521696e-23)) - 2.88264605310366e-21)) - 1.49007855810795e-20);
	fConst123 = (0.9302847925323914 * fConst14);
	fConst124 = (1.0 / tan((270.1769682087222 / fConst0)));
	fConst125 = (1 + fConst124);
	fConst126 = (0 - ((1 - fConst124) / fConst125));
	fConst127 = (0.027 / fConst125);
	fConst128 = (1.0 / tan((97.38937226128358 / fConst0)));
	fConst129 = (0 - fConst128);
	fConst130 = (1 + fConst128);
	fConst131 = (0.025 / fConst130);
	fConst132 = (0 - ((1 - fConst128) / fConst130));
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlow0 = (fConst1 * double(fslider0));
	double 	fSlow1 = (0.007000000000000006 * double(fslider1));
	double 	fSlow2 = (0.01 * double(fslider2));
	double 	fSlow3 = (0.004073836948085289 * (exp((1 - double(fslider3))) - 1));
	int 	iSlow4 = int(double(fcheckbox0));
	double 	fSlow5 = (1 - fSlow2);
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		fRec10[0] = ((fSlow0 * (0 - fRec8[1])) + fRec10[1]);
		fRec9[0] = ((1 + (fRec9[1] + (fSlow0 * fRec10[0]))) - iVec0[1]);
		fRec8[0] = fRec9[0];
		fRec13[0] = (fSlow1 + (0.993 * fRec13[1]));
		double fTemp0 = (3.01537219493083e-17 + (fConst2 * (fConst6 + (fConst4 * fRec13[0]))));
		double fTemp1 = (double)input0[i];
		fRec14[0] = ((fSlow2 * fTemp1) - (((((((((fRec14[1] * (2.41229775594467e-16 + (fConst2 * (fConst33 + (fConst32 * fRec13[0]))))) + (fRec14[2] * (8.44304214580633e-16 + (fConst2 * (fConst31 + (fConst30 * fRec13[0])))))) + (fRec14[3] * (1.68860842916127e-15 + (fConst2 * (fConst29 + (fConst28 * fRec13[0])))))) + (fRec14[4] * (2.11076053645158e-15 + (fConst14 * (fConst27 + (fConst26 * fRec13[0])))))) + (fRec14[5] * (1.68860842916127e-15 + (fConst2 * (fConst25 + (fConst23 * fRec13[0])))))) + (fRec14[6] * (8.44304214580633e-16 + (fConst2 * (fConst21 + (fConst19 * fRec13[0])))))) + (fRec14[7] * (2.41229775594467e-16 + (fConst2 * (fConst17 + (fConst15 * fRec13[0])))))) + (fRec14[8] * (3.01537219493083e-17 + (fConst2 * (fConst12 + (fConst11 * fRec13[0])))))) / fTemp0));
		double fTemp2 = (fConst58 * (((((((fRec14[3] * (2.48425512658196e-19 + (fConst14 * (fConst57 + (fConst56 * fRec13[0]))))) + ((fRec14[2] * (8.28085042193987e-20 + (fConst2 * (fConst55 + (fConst54 * fRec13[0]))))) + ((fRec14[1] * ((fConst14 * (fConst53 + (fConst52 * fRec13[0]))) - 8.28085042193987e-20)) + ((fConst2 * (fRec14[4] * (fConst51 + (fConst50 * fRec13[0])))) + (fRec14[0] * ((fConst2 * (fConst49 + (fConst48 * fRec13[0]))) - 4.14042521096994e-20)))))) + (fRec14[5] * ((fConst14 * (fConst47 + (fConst45 * fRec13[0]))) - 2.48425512658196e-19))) + (fRec14[6] * ((fConst2 * (fConst43 + (fConst40 * fRec13[0]))) - 8.28085042193987e-20))) + (fRec14[7] * (8.28085042193987e-20 + (fConst14 * (fConst37 + (fConst35 * fRec13[0])))))) + (fRec14[8] * (4.14042521096994e-20 + (fConst2 * (fConst10 + (fConst8 * fRec13[0])))))) / fTemp0));
		double fTemp3 = fabs(fTemp2);
		fRec12[0] = max(fTemp3, ((fConst59 * fRec12[1]) + (fConst60 * fTemp3)));
		fRec11[0] = ((fConst61 * fRec11[1]) + (fConst62 * fRec12[0]));
		fRec15[0] = (fSlow3 + (0.993 * fRec15[1]));
		double fTemp4 = ((iSlow4==0)? fRec15[0] : ((iSlow4==1)?max(0.09, min(0.9, fRec11[0])):(1 - max(0.09, min(0.9, (0.5 * (1 + fRec8[0])))))) );
		double fTemp5 = (8.05126427163433e-17 + (fConst2 * (fConst68 + (fTemp4 * (5.31383441927866e-18 + (fConst2 * (fConst66 + (fConst64 * fTemp4))))))));
		fRec16[0] = (fTemp2 - (((((((fRec16[1] * (4.8307585629806e-16 + (fConst2 * (fConst98 + (fTemp4 * (2.12553376771146e-17 + (fConst2 * (fConst97 + (fConst96 * fTemp4))))))))) + (fRec16[2] * (1.20768964074515e-15 + (fConst2 * (fConst95 + (fTemp4 * (2.65691720963933e-17 + (fConst2 * (fConst94 + (fConst93 * fTemp4)))))))))) + (fRec16[3] * (1.61025285432687e-15 + (fConst14 * (fConst92 + (fTemp4 * (fConst91 + (fConst90 * fTemp4)))))))) + (fRec16[4] * (1.20768964074515e-15 + (fConst2 * (fConst89 + (fTemp4 * ((fConst2 * (fConst87 + (fConst85 * fTemp4))) - 2.65691720963933e-17))))))) + (fRec16[5] * (4.8307585629806e-16 + (fConst2 * (fConst83 + (fTemp4 * ((fConst2 * (fConst81 + (fConst79 * fTemp4))) - 2.12553376771146e-17))))))) + (fRec16[6] * (8.05126427163433e-17 + (fConst2 * (fConst77 + (fTemp4 * ((fConst2 * (fConst76 + (fConst75 * fTemp4))) - 5.31383441927866e-18))))))) / fTemp5));
		double fTemp6 = ((((((((fRec16[0] * (fConst122 + (fTemp4 * ((fConst2 * (fConst121 + (fConst120 * fTemp4))) - 1.2608516331659e-20)))) + (fRec16[1] * (fConst119 + (fTemp4 * ((fConst14 * (fConst118 + (fConst117 * fTemp4))) - 2.5217032663318e-20))))) + (fRec16[2] * (fConst116 + (fTemp4 * (1.2608516331659e-20 + (fConst2 * (fConst115 + (fConst114 * fTemp4)))))))) + (fRec16[3] * (fConst113 + (fTemp4 * (5.0434065326636e-20 + (fConst14 * (fConst112 + (fConst111 * fTemp4)))))))) + (fRec16[4] * (fConst110 + (fTemp4 * (1.2608516331659e-20 + (fConst2 * (fConst108 + (fConst106 * fTemp4)))))))) + (fRec16[5] * (fConst104 + (fTemp4 * ((fConst14 * (fConst102 + (fConst100 * fTemp4))) - 2.5217032663318e-20))))) + (fRec16[6] * (fConst74 + (fTemp4 * ((fConst2 * (fConst72 + (fConst70 * fTemp4))) - 1.2608516331659e-20))))) / fTemp5);
		fVec1[0] = fTemp6;
		fRec7[0] = ((fConst123 * (fVec1[0] + fVec1[1])) - (0.8605695850647829 * fRec7[1]));
		fRec6[0] = (fRec7[0] - ((1.8405051250752198 * fRec6[1]) + (0.8612942439318627 * fRec6[2])));
		fRec17[0] = ((fConst127 * (fRec5[1] + fRec5[2])) + (fConst126 * fRec17[1]));
		fRec5[0] = (Ftrany(TRANY_TABLE_KT88_68k, ((fRec17[0] + (0.9254498422517706 * (fRec6[0] + (fRec6[2] + (2.0 * fRec6[1]))))) - 5.562895)) - 43.96685185185183);
		fRec4[0] = ((fConst132 * fRec4[1]) + (fConst131 * ((fConst128 * fRec5[0]) + (fConst129 * fRec5[1]))));
		fRec3[0] = ((0.9302847925323914 * (fRec4[1] + fRec4[0])) - (0.8605695850647829 * fRec3[1]));
		fRec2[0] = (fRec3[0] - ((1.8405051250752198 * fRec2[1]) + (0.8612942439318627 * fRec2[2])));
		fRec18[0] = ((fConst127 * (fRec1[1] + fRec1[2])) + (fConst126 * fRec18[1]));
		fRec1[0] = (Ftrany(TRANY_TABLE_KT88_68k, ((fRec18[0] + (0.9254498422517706 * (fRec2[0] + (fRec2[2] + (2.0 * fRec2[1]))))) - 5.562895)) - 43.96685185185183);
		fRec0[0] = ((fConst132 * fRec0[1]) + (fConst131 * ((fConst128 * fRec1[0]) + (fConst129 * fRec1[1]))));
		output0[i] = (FAUSTFLOAT)((fSlow5 * fTemp1) + fRec0[0]);
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
	reg.registerVar("rolandwah.Fuzz",N_("Fuzz"),"S","",&fslider1, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("rolandwah.Wah",N_("Wah"),"S","",&fslider3, 0.5, 0.02, 1.0, 0.01);
	reg.registerVar("rolandwah.lfobpm",N_("Alien Freq"),"S",N_("LFO in Beats per Minute"),&fslider0, 24.0, 24.0, 3.6e+02, 1.0);
	static const value_pair fcheckbox0_values[] = {{"manual"},{"auto"},{"alien"},{0}};
	reg.registerEnumVar("rolandwah.mode","","B","",fcheckbox0_values,&fcheckbox0, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("rolandwah.wet_dry",N_("Dry/Wet"),"S",N_("percentage of processed signal in output signal"),&fslider2, 1e+02, 0.0, 1e+02, 1.0);
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
                <property name=\"spacing\">10</property>\n\
                <child>\n\
                  <object class=\"GtkVBox\" id=\"vbox6\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
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
                  <object class=\"GtkVBox\" id=\"vbox2\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
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
                  <object class=\"GtkVBox\" id=\"vbox3\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
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
                  <object class=\"GtkVBox\" id=\"vbox4\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
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
                  <object class=\"GtkVBox\" id=\"vbox5\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
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
          <object class=\"GtkHBox\" id=\"minibox\">\n\
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
                <property name=\"xalign\">0</property>\n\
                <property name=\"label\" translatable=\"yes\">Wah</property>\n\
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
