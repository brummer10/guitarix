// generated from file '../src/plugins/rolandwah.dsp' by dsp2cc:
// Code generated with Faust 2.15.11 (https://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"
#include "trany.h"

namespace pluginlib {
namespace rolandwah {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	double fConst4;
	double fConst5;
	double fConst6;
	double fConst7;
	FAUSTFLOAT fVslider0;
	int iVec0[2];
	double fConst8;
	double fConst9;
	double fConst10;
	double fConst11;
	FAUSTFLOAT fVslider1;
	double fRec10[2];
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
	double fRec9[9];
	double fConst34;
	double fConst35;
	double fConst36;
	double fConst37;
	double fConst38;
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
	FAUSTFLOAT fCheckbox0;
	double fConst64;
	FAUSTFLOAT fVslider2;
	double fRec13[2];
	double fRec12[2];
	double fRec11[2];
	double fConst65;
	double fConst66;
	double fConst67;
	double fConst68;
	double fRec15[2];
	double fRec14[2];
	FAUSTFLOAT fVslider3;
	double fRec16[2];
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
	double fRec8[7];
	double fConst97;
	double fConst98;
	double fConst99;
	double fConst100;
	double fConst101;
	double fConst102;
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) iVec0[l0] = 0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec10[l1] = 0.0;
	for (int l2 = 0; (l2 < 9); l2 = (l2 + 1)) fRec9[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fRec13[l3] = 0.0;
	for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) fRec12[l4] = 0.0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fRec11[l5] = 0.0;
	for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) fRec15[l6] = 0.0;
	for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) fRec14[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fRec16[l8] = 0.0;
	for (int l9 = 0; (l9 < 7); l9 = (l9 + 1)) fRec8[l9] = 0.0;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) fVec1[l10] = 0.0;
	for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) fRec7[l11] = 0.0;
	for (int l12 = 0; (l12 < 3); l12 = (l12 + 1)) fRec6[l12] = 0.0;
	for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) fRec17[l13] = 0.0;
	for (int l14 = 0; (l14 < 3); l14 = (l14 + 1)) fRec5[l14] = 0.0;
	for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) fRec4[l15] = 0.0;
	for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) fRec3[l16] = 0.0;
	for (int l17 = 0; (l17 < 3); l17 = (l17 + 1)) fRec2[l17] = 0.0;
	for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) fRec18[l18] = 0.0;
	for (int l19 = 0; (l19 < 3); l19 = (l19 + 1)) fRec1[l19] = 0.0;
	for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) fRec0[l20] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSamplingFreq)));
	fConst1 = std::tan((97.389372261283583 / fConst0));
	fConst2 = (1.0 / fConst1);
	fConst3 = (fConst2 + 1.0);
	fConst4 = (1.0 / (fConst3 * fConst1));
	fConst5 = mydsp_faustpower2_f(fConst0);
	fConst6 = (0.93028479253239138 * fConst5);
	fConst7 = mydsp_faustpower3_f(fConst0);
	fConst8 = (8.6453768554099601e-54 * fConst0);
	fConst9 = (((((((((((fConst8 + -1.01507284191684e-32) * fConst0) + -9.1925129482745801e-29) * fConst0) + -1.14668174326105e-25) * fConst5) + 1.7131119450777e-20) * fConst0) + 2.0004598723027898e-18) * fConst0) + 5.17754054952568e-17);
	fConst10 = (7.7135875124018505e-54 * fConst0);
	fConst11 = (((((((((((3.4617148379147101e-33 - fConst10) * fConst0) + 7.3851826335984701e-29) * fConst0) + 1.0562321161133599e-25) * fConst5) + -1.35506989727438e-20) * fConst0) + -6.4187190694828203e-19) * fConst0) + -3.6184466339169999e-18);
	fConst12 = (3.02588189939348e-53 * fConst0);
	fConst13 = (((((((((((((2.3685032978059599e-32 - fConst12) * fConst0) + 9.1925129482745801e-29) * fConst0) + -1.14668174326105e-25) * fConst0) + -1.52318075159202e-22) * fConst0) + -1.7131119450777e-20) * fConst0) + 2.0004598723027898e-18) * fConst0) + 1.20809279488933e-16);
	fConst14 = (2.6997556293406501e-53 * fConst0);
	fConst15 = (((((((((((((fConst14 + -8.0773346218009802e-33) * fConst0) + -7.3851826335984701e-29) * fConst0) + 1.0562321161133599e-25) * fConst0) + 1.3795366937074801e-22) * fConst0) + 1.35506989727438e-20) * fConst0) + -6.4187190694828203e-19) * fConst0) + -8.4430421458063305e-18);
	fConst16 = (6.0517637987869703e-53 * fConst0);
	fConst17 = (((((((((((fConst16 + -2.3685032978059599e-32) * fConst0) + 9.1925129482745801e-29) * fConst0) + 3.44004522978315e-25) * fConst5) + -5.13933583523309e-20) * fConst0) + -2.0004598723027898e-18) * fConst0) + 1.20809279488933e-16);
	fConst18 = (5.3995112586813002e-53 * fConst0);
	fConst19 = (((((((((((8.0773346218009802e-33 - fConst18) * fConst0) + -7.3851826335984701e-29) * fConst0) + -3.1686963483400899e-25) * fConst5) + 4.0652096918231401e-20) * fConst0) + 6.4187190694828203e-19) * fConst0) + -8.4430421458063305e-18);
	fConst20 = (((((-2.29812823706864e-28 - (7.5647047484837103e-53 * fConst5)) * fConst5) + 2.2847711273880299e-22) * fConst5) + -5.0011496807569701e-18);
	fConst21 = ((((((6.7493890733516199e-53 * fConst5) + 1.8462956583996199e-28) * fConst5) + -2.0693050405612199e-22) * fConst5) + 1.6046797673707001e-18);
	fConst22 = (((((((((((fConst16 + 2.3685032978059599e-32) * fConst0) + 9.1925129482745801e-29) * fConst0) + -3.44004522978315e-25) * fConst5) + 5.13933583523309e-20) * fConst0) + -2.0004598723027898e-18) * fConst0) + -1.20809279488933e-16);
	fConst23 = (((((((((((-8.0773346218009802e-33 - fConst18) * fConst0) + -7.3851826335984701e-29) * fConst0) + 3.1686963483400899e-25) * fConst5) + -4.0652096918231401e-20) * fConst0) + 6.4187190694828203e-19) * fConst0) + 8.4430421458063305e-18);
	fConst24 = (((((((((((((-2.3685032978059599e-32 - fConst12) * fConst0) + 9.1925129482745801e-29) * fConst0) + 1.14668174326105e-25) * fConst0) + -1.52318075159202e-22) * fConst0) + 1.7131119450777e-20) * fConst0) + 2.0004598723027898e-18) * fConst0) + -1.20809279488933e-16);
	fConst25 = (((((((((((((fConst14 + 8.0773346218009802e-33) * fConst0) + -7.3851826335984701e-29) * fConst0) + -1.0562321161133599e-25) * fConst0) + 1.3795366937074801e-22) * fConst0) + -1.35506989727438e-20) * fConst0) + -6.4187190694828203e-19) * fConst0) + 8.4430421458063305e-18);
	fConst26 = (((((((((((fConst8 + 1.01507284191684e-32) * fConst0) + -9.1925129482745801e-29) * fConst0) + 1.14668174326105e-25) * fConst5) + -1.7131119450777e-20) * fConst0) + 2.0004598723027898e-18) * fConst0) + -5.17754054952568e-17);
	fConst27 = (((((((((((-3.4617148379147101e-33 - fConst10) * fConst0) + 7.3851826335984701e-29) * fConst0) + -1.0562321161133599e-25) * fConst5) + 1.35506989727438e-20) * fConst0) + -6.4187190694828203e-19) * fConst0) + 3.6184466339169999e-18);
	fConst28 = (1.0806721069262399e-54 * fConst0);
	fConst29 = (((((((((((((-1.6917880698614e-33 - fConst28) * fConst0) + 2.29812823706864e-29) * fConst0) + -5.7334087163052396e-26) * fConst0) + 3.8079518789800499e-23) * fConst0) + -8.5655597253884803e-21) * fConst0) + 5.0011496807569601e-19) * fConst0) + -8.6292342492094698e-18);
	fConst30 = (9.6419843905023102e-55 * fConst0);
	fConst31 = (((((((((((((fConst30 + 5.7695247298578402e-34) * fConst0) + -1.8462956583996201e-29) * fConst0) + 5.2811605805668203e-26) * fConst0) + -3.4488417342687002e-23) * fConst0) + 6.7753494863719001e-21) * fConst0) + -1.6046797673707e-19) * fConst0) + 6.0307443898616604e-19);
	fConst32 = (((((((((((((1.6917880698614e-33 - fConst28) * fConst0) + 2.29812823706864e-29) * fConst0) + 5.7334087163052396e-26) * fConst0) + 3.8079518789800499e-23) * fConst0) + 8.5655597253884803e-21) * fConst0) + 5.0011496807569601e-19) * fConst0) + 8.6292342492094698e-18);
	fConst33 = (((((((((((((fConst30 + -5.7695247298578402e-34) * fConst0) + -1.8462956583996201e-29) * fConst0) + -5.2811605805668203e-26) * fConst0) + -3.4488417342687002e-23) * fConst0) + -6.7753494863719001e-21) * fConst0) + -1.6046797673707e-19) * fConst0) + -6.0307443898616604e-19);
	fConst34 = (2.6226779359819302e-32 * fConst0);
	fConst35 = (((((((-2.30252524666021e-25 - fConst34) * fConst0) + -1.21809214941527e-22) * fConst0) + -4.4700687878866801e-21) * fConst0) + -4.1404252109699403e-20);
	fConst36 = (8.60349117319693e-33 * fConst0);
	fConst37 = ((((((fConst36 + 7.4247065053322598e-26) * fConst0) + 3.8082846258472101e-23) * fConst0) + 8.2808504219398703e-22) * fConst0);
	fConst38 = (1.5736067615891601e-31 * fConst0);
	fConst39 = (((((fConst38 + 9.2101009866408307e-25) * fConst0) + 2.4361842988305401e-22) * fConst5) + -8.2808504219398697e-20);
	fConst40 = (5.1620947039181596e-32 * fConst0);
	fConst41 = ((((-2.9698826021328998e-25 - fConst40) * fConst0) + -7.6165692516944296e-23) * fConst5);
	fConst42 = (3.6717491103746999e-31 * fConst0);
	fConst43 = ((-9.2101009866408307e-25 - fConst42) * fConst0);
	fConst44 = (((((fConst43 + 2.4361842988305401e-22) * fConst0) + 1.7880275151546699e-20) * fConst0) + 8.2808504219398697e-20);
	fConst45 = (1.20448876424757e-31 * fConst0);
	fConst46 = ((fConst45 + 2.9698826021328998e-25) * fConst0);
	fConst47 = ((((fConst46 + -7.6165692516944296e-23) * fConst0) + -3.31234016877595e-21) * fConst0);
	fConst48 = ((fConst42 + -9.2101009866408307e-25) * fConst0);
	fConst49 = (((fConst48 + -7.3085528964916198e-22) * fConst5) + 2.4842551265819602e-19);
	fConst50 = ((2.9698826021328998e-25 - fConst45) * fConst0);
	fConst51 = ((fConst50 + 2.2849707755083301e-22) * fConst5);
	fConst52 = ((2.3025252466602099e-24 * fConst5) + -2.6820412727320099e-20);
	fConst53 = (4.9685102531639197e-21 - (7.4247065053322603e-25 * fConst5));
	fConst54 = (((fConst43 + 7.3085528964916198e-22) * fConst5) + -2.4842551265819602e-19);
	fConst55 = ((fConst46 + -2.2849707755083301e-22) * fConst5);
	fConst56 = (((((fConst48 + -2.4361842988305401e-22) * fConst0) + 1.7880275151546699e-20) * fConst0) + -8.2808504219398697e-20);
	fConst57 = ((((fConst50 + 7.6165692516944296e-23) * fConst0) + -3.31234016877595e-21) * fConst0);
	fConst58 = (((((9.2101009866408307e-25 - fConst38) * fConst0) + -2.4361842988305401e-22) * fConst5) + 8.2808504219398697e-20);
	fConst59 = ((((fConst40 + -2.9698826021328998e-25) * fConst0) + 7.6165692516944296e-23) * fConst5);
	fConst60 = (((((((fConst34 + -2.30252524666021e-25) * fConst0) + 1.21809214941527e-22) * fConst0) + -4.4700687878866801e-21) * fConst0) + 4.1404252109699403e-20);
	fConst61 = ((((((7.4247065053322598e-26 - fConst36) * fConst0) + -3.8082846258472101e-23) * fConst0) + 8.2808504219398703e-22) * fConst0);
	fConst62 = (3.0207049650607199e-29 * fConst0);
	fConst63 = (((((((-4.2224699126538501e-26 - fConst62) * fConst0) + -5.1028451720445405e-22) * fConst5) + 7.5236423320258805e-18) * fConst0) + 1.2367938041498899e-16);
	fConst64 = (0.10471975511965977 / fConst0);
	fConst65 = std::exp((0.0 - (100.0 / fConst0)));
	fConst66 = (1.0 - fConst65);
	fConst67 = std::exp((0.0 - (10.0 / fConst0)));
	fConst68 = (1.0 - fConst67);
	fConst69 = (1.0332413167573e-27 * fConst0);
	fConst70 = (((((((-4.5813559411368004e-25 - fConst69) * fConst0) + -1.9536713520122399e-22) * fConst5) + 2.1593959722292799e-18) * fConst0) + 2.1255337677114601e-17);
	fConst71 = (2.5790740534914202e-28 * fConst0);
	fConst72 = ((((((fConst71 + 1.2774942666629701e-25) * fConst0) + 1.7800778559222001e-22) * fConst5) + -7.0142614334478301e-19) * fConst0);
	fConst73 = (7.5517624126518095e-29 * fConst0);
	fConst74 = (((((((((fConst73 + 5.27808739081731e-26) * fConst0) + -2.5514225860222702e-22) * fConst0) + -4.4594494030519004e-19) * fConst0) + -3.7618211660129403e-18) * fConst0) + 1.54599225518736e-16);
	fConst75 = (2.5831032918932499e-27 * fConst0);
	fConst76 = (((((((((fConst75 + 5.7266949264210002e-25) * fConst0) + -9.7683567600611997e-23) * fConst0) + -1.5643246402074301e-19) * fConst0) + -1.07969798611464e-18) * fConst0) + 2.6569172096393299e-17);
	fConst77 = (6.4476851337285599e-28 * fConst0);
	fConst78 = ((((((((-1.59686783332872e-25 - fConst77) * fConst0) + 8.9003892796110098e-23) * fConst0) + 1.46112676135974e-19) * fConst0) + 3.5071307167239199e-19) * fConst0);
	fConst79 = (((1.02056903440891e-21 - (1.00690165502024e-28 * fConst5)) * fConst5) + -1.5047284664051801e-17);
	fConst80 = (((3.9073427040244799e-22 - (3.4441377225243296e-27 * fConst5)) * fConst5) + -4.3187919444585699e-18);
	fConst81 = ((((8.5969135116380804e-28 * fConst5) + -3.5601557118444002e-22) * fConst5) + 1.4028522866895701e-18);
	fConst82 = (((((((((fConst73 + -5.27808739081731e-26) * fConst0) + -2.5514225860222702e-22) * fConst0) + 4.4594494030519004e-19) * fConst0) + -3.7618211660129403e-18) * fConst0) + -1.54599225518736e-16);
	fConst83 = (((((((((fConst75 + -5.7266949264210002e-25) * fConst0) + -9.7683567600611997e-23) * fConst0) + 1.5643246402074301e-19) * fConst0) + -1.07969798611464e-18) * fConst0) + -2.6569172096393299e-17);
	fConst84 = ((((((((1.59686783332872e-25 - fConst77) * fConst0) + 8.9003892796110098e-23) * fConst0) + -1.46112676135974e-19) * fConst0) + 3.5071307167239199e-19) * fConst0);
	fConst85 = (((((((4.2224699126538501e-26 - fConst62) * fConst0) + -5.1028451720445405e-22) * fConst5) + 7.5236423320258805e-18) * fConst0) + -1.2367938041498899e-16);
	fConst86 = (((((((4.5813559411368004e-25 - fConst69) * fConst0) + -1.9536713520122399e-22) * fConst5) + 2.1593959722292799e-18) * fConst0) + -2.1255337677114601e-17);
	fConst87 = ((((((fConst71 + -1.2774942666629701e-25) * fConst0) + 1.7800778559222001e-22) * fConst5) + -7.0142614334478301e-19) * fConst0);
	fConst88 = (5.0345082751012003e-30 * fConst0);
	fConst89 = (((((((((fConst88 + -1.0556174781634599e-26) * fConst0) + 2.5514225860222702e-22) * fConst0) + -1.4864831343506299e-19) * fConst0) + 3.7618211660129403e-18) * fConst0) + -3.0919845103747099e-17);
	fConst90 = (1.72206886126217e-28 * fConst0);
	fConst91 = (((((((((fConst90 + -1.1453389852842001e-25) * fConst0) + 9.7683567600611997e-23) * fConst0) + -5.2144154673581001e-20) * fConst0) + 1.07969798611464e-18) * fConst0) + -5.3138344192786603e-18);
	fConst92 = (4.29845675581904e-29 * fConst0);
	fConst93 = ((((((((3.1937356666574297e-26 - fConst92) * fConst0) + -8.9003892796110098e-23) * fConst0) + 4.8704225378657897e-20) * fConst0) + -3.5071307167239199e-19) * fConst0);
	fConst94 = (((((((((fConst88 + 1.0556174781634599e-26) * fConst0) + 2.5514225860222702e-22) * fConst0) + 1.4864831343506299e-19) * fConst0) + 3.7618211660129403e-18) * fConst0) + 3.0919845103747099e-17);
	fConst95 = (((((((((fConst90 + 1.1453389852842001e-25) * fConst0) + 9.7683567600611997e-23) * fConst0) + 5.2144154673581001e-20) * fConst0) + 1.07969798611464e-18) * fConst0) + 5.3138344192786603e-18);
	fConst96 = ((((((((-3.1937356666574297e-26 - fConst92) * fConst0) + -8.9003892796110098e-23) * fConst0) + -4.8704225378657897e-20) * fConst0) + -3.5071307167239199e-19) * fConst0);
	fConst97 = (9.6574497270343303e-31 * fConst0);
	fConst98 = (((((((-3.0882218864428199e-26 - fConst97) * fConst0) + -4.8262471952169603e-23) * fConst0) + -2.8826460531036599e-21) * fConst0) + -1.4900785581079499e-20);
	fConst99 = (7.1663335121242097e-31 * fConst0);
	fConst100 = (((((((-1.2201212507437399e-26 - fConst99) * fConst0) + -1.8312671176616301e-23) * fConst0) + -1.2159222901252701e-21) * fConst0) + -1.2608516331659e-20);
	fConst101 = (7.1808255629623197e-31 * fConst0);
	fConst102 = ((((((fConst101 + 1.2196809675606999e-26) * fConst0) + 1.8163521797294801e-23) * fConst0) + 9.8345184835124996e-22) * fConst0);
	fConst103 = (5.7944698362206003e-30 * fConst0);
	fConst104 = (((((fConst103 + 1.23528875457713e-25) * fConst0) + 9.6524943904339299e-23) * fConst5) + -2.9801571162159101e-20);
	fConst105 = (4.2998001072745197e-30 * fConst0);
	fConst106 = (((((fConst105 + 4.8804850029749597e-26) * fConst0) + 3.6625342353232602e-23) * fConst5) + -2.5217032663318e-20);
	fConst107 = (4.3084953377773899e-30 * fConst0);
	fConst108 = ((((-4.8787238702428101e-26 - fConst107) * fConst0) + -3.6327043594589501e-23) * fConst5);
	fConst109 = (1.44861745905515e-29 * fConst0);
	fConst110 = (((((((-1.54411094322141e-25 - fConst109) * fConst0) + 4.8262471952169603e-23) * fConst0) + 8.6479381593109902e-21) * fConst0) + 1.4900785581079499e-20);
	fConst111 = (1.07495002681863e-29 * fConst0);
	fConst112 = (((((((-6.1006062537187001e-26 - fConst111) * fConst0) + 1.8312671176616301e-23) * fConst0) + 3.6477668703758198e-21) * fConst0) + 1.2608516331659e-20);
	fConst113 = (1.07712383444435e-29 * fConst0);
	fConst114 = ((((((fConst113 + 6.0984048378035096e-26) * fConst0) + -1.8163521797294801e-23) * fConst0) + -2.9503555450537499e-21) * fConst0);
	fConst115 = ((((1.93148994540687e-29 * fConst5) + -1.93049887808679e-22) * fConst5) + 5.9603142324318202e-20);
	fConst116 = ((((1.4332667024248399e-29 * fConst5) + -7.3250684706465204e-23) * fConst5) + 5.0434065326635999e-20);
	fConst117 = ((7.2654087189179003e-23 - (1.43616511259246e-29 * fConst5)) * fConst5);
	fConst118 = (((((((1.54411094322141e-25 - fConst109) * fConst0) + 4.8262471952169603e-23) * fConst0) + -8.6479381593109902e-21) * fConst0) + 1.4900785581079499e-20);
	fConst119 = (((((((6.1006062537187001e-26 - fConst111) * fConst0) + 1.8312671176616301e-23) * fConst0) + -3.6477668703758198e-21) * fConst0) + 1.2608516331659e-20);
	fConst120 = ((((((fConst113 + -6.0984048378035096e-26) * fConst0) + -1.8163521797294801e-23) * fConst0) + 2.9503555450537499e-21) * fConst0);
	fConst121 = (((((fConst103 + -1.23528875457713e-25) * fConst0) + 9.6524943904339299e-23) * fConst5) + -2.9801571162159101e-20);
	fConst122 = (((((fConst105 + -4.8804850029749597e-26) * fConst0) + 3.6625342353232602e-23) * fConst5) + -2.5217032663318e-20);
	fConst123 = ((((4.8787238702428101e-26 - fConst107) * fConst0) + -3.6327043594589501e-23) * fConst5);
	fConst124 = (((((((3.0882218864428199e-26 - fConst97) * fConst0) + -4.8262471952169603e-23) * fConst0) + 2.8826460531036599e-21) * fConst0) + -1.4900785581079499e-20);
	fConst125 = (((((((1.2201212507437399e-26 - fConst99) * fConst0) + -1.8312671176616301e-23) * fConst0) + 1.2159222901252701e-21) * fConst0) + -1.2608516331659e-20);
	fConst126 = ((((((fConst101 + -1.2196809675606999e-26) * fConst0) + 1.8163521797294801e-23) * fConst0) + -9.8345184835124996e-22) * fConst0);
	fConst127 = (1.0 / std::tan((270.1769682087222 / fConst0)));
	fConst128 = (1.0 / (fConst127 + 1.0));
	fConst129 = (1.0 - fConst127);
	fConst130 = (0.0 - fConst4);
	fConst131 = ((1.0 - fConst2) / fConst3);
	fVslider0 = FAUSTFLOAT(100.0);
	fVslider1 = FAUSTFLOAT(0.5);
	fCheckbox0 = FAUSTFLOAT(0.0);
	fVslider2 = FAUSTFLOAT(24.0);
	fVslider3 = FAUSTFLOAT(0.5);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double fSlow0 = (0.01 * double(fVslider0));
	double fSlow1 = (0.0070000000000000062 * double(fVslider1));
	int iSlow2 = int(double(fCheckbox0));
	int iSlow3 = (iSlow2 == 0);
	int iSlow4 = (iSlow2 == 1);
	double fSlow5 = (fConst64 * double(fVslider2));
	double fSlow6 = (0.004073836948085289 * (std::exp((1.0 - double(fVslider3))) + -1.0));
	double fSlow7 = (1.0 - fSlow0);
	for (int i = 0; (i < count); i = (i + 1)) {
		double fTemp0 = double(input0[i]);
		iVec0[0] = 1;
		fRec10[0] = (fSlow1 + (0.99299999999999999 * fRec10[1]));
		double fTemp1 = ((fConst0 * (fConst32 + (fConst33 * fRec10[0]))) + 3.0153721949308302e-17);
		fRec9[0] = ((fSlow0 * fTemp0) - (((((((((fRec9[1] * ((fConst0 * (fConst9 + (fConst11 * fRec10[0]))) + 2.4122977559446701e-16)) + (fRec9[2] * ((fConst0 * (fConst13 + (fConst15 * fRec10[0]))) + 8.4430421458063303e-16))) + (fRec9[3] * ((fConst0 * (fConst17 + (fConst19 * fRec10[0]))) + 1.68860842916127e-15))) + (fRec9[4] * ((fConst5 * (fConst20 + (fConst21 * fRec10[0]))) + 2.1107605364515801e-15))) + (fRec9[5] * ((fConst0 * (fConst22 + (fConst23 * fRec10[0]))) + 1.68860842916127e-15))) + (fRec9[6] * ((fConst0 * (fConst24 + (fConst25 * fRec10[0]))) + 8.4430421458063303e-16))) + (fRec9[7] * ((fConst0 * (fConst26 + (fConst27 * fRec10[0]))) + 2.4122977559446701e-16))) + (fRec9[8] * ((fConst0 * (fConst29 + (fConst31 * fRec10[0]))) + 3.0153721949308302e-17))) / fTemp1));
		double fTemp2 = (fConst7 * ((((((((((fRec9[0] * (fConst35 + (fConst37 * fRec10[0]))) + (fRec9[1] * (fConst39 + (fConst41 * fRec10[0])))) + (fRec9[2] * (fConst44 + (fConst47 * fRec10[0])))) + (fRec9[3] * (fConst49 + (fConst51 * fRec10[0])))) + (fConst0 * (fRec9[4] * (fConst52 + (fConst53 * fRec10[0]))))) + (fRec9[5] * (fConst54 + (fConst55 * fRec10[0])))) + (fRec9[6] * (fConst56 + (fConst57 * fRec10[0])))) + (fRec9[7] * (fConst58 + (fConst59 * fRec10[0])))) + (fRec9[8] * (fConst60 + (fConst61 * fRec10[0])))) / fTemp1));
		fRec13[0] = (fRec13[1] + (fSlow5 * (0.0 - fRec11[1])));
		fRec12[0] = ((fSlow5 * fRec13[0]) + (double((1 - iVec0[1])) + fRec12[1]));
		fRec11[0] = fRec12[0];
		double fTemp3 = std::fabs(fTemp2);
		fRec15[0] = std::max<double>(fTemp3, ((fConst67 * fRec15[1]) + (fConst68 * fTemp3)));
		fRec14[0] = ((fConst65 * fRec14[1]) + (fConst66 * fRec15[0]));
		fRec16[0] = (fSlow6 + (0.99299999999999999 * fRec16[1]));
		double fTemp4 = (iSlow3?fRec16[0]:(iSlow4?std::max<double>(0.089999999999999997, std::min<double>(0.90000000000000002, fRec14[0])):(1.0 - std::max<double>(0.089999999999999997, std::min<double>(0.90000000000000002, (0.5 * (fRec11[0] + 1.0)))))));
		double fTemp5 = ((fConst0 * (fConst94 + (fTemp4 * (fConst95 + (fConst96 * fTemp4))))) + 8.0512642716343297e-17);
		fRec8[0] = (fTemp2 - (((((((fRec8[1] * ((fConst0 * (fConst63 + (fTemp4 * (fConst70 + (fConst72 * fTemp4))))) + 4.8307585629805998e-16)) + (fRec8[2] * ((fConst0 * (fConst74 + (fTemp4 * (fConst76 + (fConst78 * fTemp4))))) + 1.2076896407451501e-15))) + (fRec8[3] * ((fConst5 * (fConst79 + (fTemp4 * (fConst80 + (fConst81 * fTemp4))))) + 1.6102528543268701e-15))) + (fRec8[4] * ((fConst0 * (fConst82 + (fTemp4 * (fConst83 + (fConst84 * fTemp4))))) + 1.2076896407451501e-15))) + (fRec8[5] * ((fConst0 * (fConst85 + (fTemp4 * (fConst86 + (fConst87 * fTemp4))))) + 4.8307585629805998e-16))) + (fRec8[6] * ((fConst0 * (fConst89 + (fTemp4 * (fConst91 + (fConst93 * fTemp4))))) + 8.0512642716343297e-17))) / fTemp5));
		double fTemp6 = ((((((((fRec8[0] * (fConst98 + (fTemp4 * (fConst100 + (fConst102 * fTemp4))))) + (fRec8[1] * (fConst104 + (fTemp4 * (fConst106 + (fConst108 * fTemp4)))))) + (fRec8[2] * (fConst110 + (fTemp4 * (fConst112 + (fConst114 * fTemp4)))))) + (fRec8[3] * (fConst115 + (fTemp4 * (fConst116 + (fConst117 * fTemp4)))))) + (fRec8[4] * (fConst118 + (fTemp4 * (fConst119 + (fConst120 * fTemp4)))))) + (fRec8[5] * (fConst121 + (fTemp4 * (fConst122 + (fConst123 * fTemp4)))))) + (fRec8[6] * (fConst124 + (fTemp4 * (fConst125 + (fConst126 * fTemp4)))))) / fTemp5);
		fVec1[0] = fTemp6;
		fRec7[0] = ((fConst6 * (fTemp6 + fVec1[1])) - (0.86056958506478287 * fRec7[1]));
		fRec6[0] = (fRec7[0] - ((1.8405051250752198 * fRec6[1]) + (0.86129424393186271 * fRec6[2])));
		fRec17[0] = (fConst128 * ((0.027 * (fRec5[1] + fRec5[2])) - (fConst129 * fRec17[1])));
		fRec5[0] = (double(Ftrany(int(TRANY_TABLE_KT88_68k), double((((0.92544984225177063 * (fRec6[0] + fRec6[2])) + (fRec17[0] + (1.8508996845035413 * fRec6[1]))) + -5.5628950000000001)))) + -43.966851851851828);
		fRec4[0] = ((0.025000000000000001 * ((fConst4 * fRec5[0]) + (fConst130 * fRec5[1]))) - (fConst131 * fRec4[1]));
		fRec3[0] = ((0.93028479253239138 * (fRec4[0] + fRec4[1])) - (0.86056958506478287 * fRec3[1]));
		fRec2[0] = (fRec3[0] - ((1.8405051250752198 * fRec2[1]) + (0.86129424393186271 * fRec2[2])));
		fRec18[0] = (fConst128 * ((0.027 * (fRec1[1] + fRec1[2])) - (fConst129 * fRec18[1])));
		fRec1[0] = (double(Ftrany(int(TRANY_TABLE_KT88_68k), double((((0.92544984225177063 * (fRec2[0] + fRec2[2])) + (fRec18[0] + (1.8508996845035413 * fRec2[1]))) + -5.5628950000000001)))) + -43.966851851851828);
		fRec0[0] = ((0.025000000000000001 * ((fConst4 * fRec1[0]) + (fConst130 * fRec1[1]))) - (fConst131 * fRec0[1]));
		output0[i] = FAUSTFLOAT((fRec0[0] + (fSlow7 * fTemp0)));
		iVec0[1] = iVec0[0];
		fRec10[1] = fRec10[0];
		for (int j0 = 8; (j0 > 0); j0 = (j0 - 1)) {
			fRec9[j0] = fRec9[(j0 - 1)];
		}
		fRec13[1] = fRec13[0];
		fRec12[1] = fRec12[0];
		fRec11[1] = fRec11[0];
		fRec15[1] = fRec15[0];
		fRec14[1] = fRec14[0];
		fRec16[1] = fRec16[0];
		for (int j1 = 6; (j1 > 0); j1 = (j1 - 1)) {
			fRec8[j1] = fRec8[(j1 - 1)];
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
	reg.registerVar("rolandwah.Fuzz",N_("Fuzz"),"S","",&fVslider1, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("rolandwah.Wah",N_("Wah"),"S","",&fVslider3, 0.5, 0.02, 1.0, 0.01);
	reg.registerVar("rolandwah.lfobpm",N_("Alien Freq"),"S",N_("LFO in Beats per Minute"),&fVslider2, 24.0, 24.0, 360.0, 1.0);
	static const value_pair fCheckbox0_values[] = {{"manual"},{"auto"},{"alien"},{0}};
	reg.registerEnumVar("rolandwah.mode","","B","",fCheckbox0_values,&fCheckbox0, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("rolandwah.wet_dry",N_("Dry/Wet"),"S",N_("percentage of processed signal in output signal"),&fVslider0, 100.0, 0.0, 100.0, 1.0);
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
