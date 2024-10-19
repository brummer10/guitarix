// generated from file '../src/plugins/axface.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"
#include "trany.h"

namespace pluginlib {
namespace axface {

class Dsp: public PluginDef {
private:
	int fSampleRate;
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	FAUSTFLOAT fVslider0;
	double fRec8[2];
	double fConst4;
	double fConst5;
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
	FAUSTFLOAT fVslider1;
	double fRec9[2];
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
	double fRec10[6];
	double fConst66;
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
	FAUSTFLOAT fVslider2;
	double fRec11[2];
	double fVec0[2];
	double fRec7[2];
	double fRec6[3];
	double fConst84;
	double fConst85;
	double fConst86;
	double fRec12[2];
	double fRec5[3];
	double fConst87;
	double fConst88;
	double fRec4[2];
	double fRec3[2];
	double fRec2[3];
	double fRec13[2];
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
	id = "axface";
	name = N_("Axis Face");
	groups = 0;
	description = N_("Axis Face"); // description (tooltip)
	category = N_("Fuzz");       // category
	shortname = N_("Axis Face");     // shortname
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec8[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec9[l1] = 0.0;
	for (int l2 = 0; l2 < 6; l2 = l2 + 1) fRec10[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec11[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fVec0[l4] = 0.0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fRec7[l5] = 0.0;
	for (int l6 = 0; l6 < 3; l6 = l6 + 1) fRec6[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec12[l7] = 0.0;
	for (int l8 = 0; l8 < 3; l8 = l8 + 1) fRec5[l8] = 0.0;
	for (int l9 = 0; l9 < 2; l9 = l9 + 1) fRec4[l9] = 0.0;
	for (int l10 = 0; l10 < 2; l10 = l10 + 1) fRec3[l10] = 0.0;
	for (int l11 = 0; l11 < 3; l11 = l11 + 1) fRec2[l11] = 0.0;
	for (int l12 = 0; l12 < 2; l12 = l12 + 1) fRec13[l12] = 0.0;
	for (int l13 = 0; l13 < 3; l13 = l13 + 1) fRec1[l13] = 0.0;
	for (int l14 = 0; l14 < 2; l14 = l14 + 1) fRec0[l14] = 0.0;
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
	fConst4 = 4.03791059191999e-25 * fConst0;
	fConst5 = fConst0 * (fConst0 * (fConst0 * (-1.13427407987086e-18 - fConst4) + -1.49739128868709e-14) + -7.44393603614497e-12) + -1.60942285815325e-10;
	fConst6 = 5.1173274738794e-25 * fConst0;
	fConst7 = fConst0 * (fConst0 * (fConst0 * (fConst6 + 1.13834320666478e-18) + 1.49968987528957e-14) + 7.45459961503187e-12) + 1.61087815478651e-10;
	fConst8 = 1.70577582462647e-23 * fConst0;
	fConst9 = fConst0 * (fConst0 * (fConst8 + 3.79447735554928e-17) + 4.99896625096522e-13) + 2.48486653834396e-10;
	fConst10 = 3.77313513934094e-25 * fConst0;
	fConst11 = fConst0 * (fConst0 * (fConst10 + 1.13011470525257e-18) + 1.48978106454603e-14) + 7.08146057587431e-12;
	fConst12 = 4.4415330562134e-25 * fConst0;
	fConst13 = fConst0 * (fConst0 * (-1.13263345455505e-18 - fConst12) + -1.49120085362402e-14) + -7.08786388106065e-12;
	fConst14 = mydsp_faustpower2_f(fConst0);
	fConst15 = 1.4805110187378e-23 * fConst0;
	fConst16 = fConst0 * (fConst0 * (fConst0 * (-3.77544484851683e-17 - fConst15) + -4.97066951208006e-13) + -2.36262129368688e-10);
	fConst17 = 3.38149630023061e-21 * fConst0;
	fConst18 = fConst17 + 1.69477435943983e-16;
	fConst19 = 3.86160790724035e-21 * fConst0;
	fConst20 = -1.70600223084551e-14 - fConst19;
	fConst21 = mydsp_faustpower3_f(fConst0);
	fConst22 = 1.28720263574678e-19 * fConst0;
	fConst23 = fConst14 * (fConst22 + 5.68667410281837e-13);
	fConst24 = fConst0 * (fConst0 * (fConst0 * (fConst4 + -1.13427407987086e-18) + 1.49739128868709e-14) + -7.44393603614497e-12) + 1.60942285815325e-10;
	fConst25 = fConst0 * (fConst0 * (fConst0 * (1.13834320666478e-18 - fConst6) + -1.49968987528957e-14) + 7.45459961503187e-12) + -1.61087815478651e-10;
	fConst26 = fConst0 * (fConst0 * (fConst8 + -3.79447735554928e-17) + 4.99896625096522e-13) + -2.48486653834396e-10;
	fConst27 = fConst0 * (fConst0 * (1.13011470525257e-18 - fConst10) + -1.48978106454603e-14) + 7.08146057587431e-12;
	fConst28 = fConst0 * (fConst0 * (fConst12 + -1.13263345455505e-18) + 1.49120085362402e-14) + -7.08786388106065e-12;
	fConst29 = fConst0 * (fConst0 * (fConst0 * (3.77544484851683e-17 - fConst15) + -4.97066951208006e-13) + 2.36262129368688e-10);
	fConst30 = 2.01895529596e-24 * fConst0;
	fConst31 = fConst0 * (fConst0 * (fConst0 * (3.40282223961257e-18 - fConst30) + -1.49739128868709e-14) + -7.44393603614497e-12) + 4.82826857445976e-10;
	fConst32 = 2.5586637369397e-24 * fConst0;
	fConst33 = fConst0 * (fConst0 * (fConst0 * (fConst32 + -3.41502961999435e-18) + 1.49968987528957e-14) + 7.45459961503187e-12) + -4.83263446435953e-10;
	fConst34 = 5.1173274738794e-23 * fConst0;
	fConst35 = fConst0 * (fConst0 * (3.79447735554928e-17 - fConst34) + 4.99896625096522e-13) + -7.45459961503187e-10;
	fConst36 = 1.88656756967047e-24 * fConst0;
	fConst37 = fConst0 * (fConst0 * (fConst36 + -3.39034411575772e-18) + 1.48978106454603e-14) + 7.08146057587431e-12;
	fConst38 = 2.2207665281067e-24 * fConst0;
	fConst39 = fConst0 * (fConst0 * (3.39790036366515e-18 - fConst38) + -1.49120085362402e-14) + -7.08786388106065e-12;
	fConst40 = 4.4415330562134e-23 * fConst0;
	fConst41 = fConst0 * (fConst0 * (fConst0 * (fConst40 + -3.77544484851683e-17) + -4.97066951208006e-13) + 7.08786388106065e-10);
	fConst42 = 4.03791059191999e-24 * fConst0;
	fConst43 = fConst0 * (fConst0 * (fConst0 * (fConst42 + -2.26854815974171e-18) + -2.99478257737419e-14) + 1.48878720722899e-11) + 3.21884571630651e-10;
	fConst44 = 5.1173274738794e-24 * fConst0;
	fConst45 = fConst0 * (fConst0 * (fConst0 * (2.27668641332957e-18 - fConst44) + 2.99937975057913e-14) + -1.49091992300637e-11) + -3.22175630957302e-10;
	fConst46 = 3.41155164925293e-23 * fConst0;
	fConst47 = fConst0 * (fConst0 * (fConst46 + 7.58895471109855e-17) + -9.99793250193045e-13) + -4.96973307668791e-10;
	fConst48 = 3.77313513934094e-24 * fConst0;
	fConst49 = fConst0 * (fConst0 * (2.26022941050514e-18 - fConst48) + 2.97956212909206e-14) + -1.41629211517486e-11;
	fConst50 = 4.4415330562134e-24 * fConst0;
	fConst51 = fConst0 * (fConst0 * (fConst50 + -2.2652669091101e-18) + -2.98240170724803e-14) + 1.41757277621213e-11;
	fConst52 = 2.9610220374756e-23 * fConst0;
	fConst53 = fConst0 * (fConst0 * (fConst0 * (-7.55088969703365e-17 - fConst52) + 9.94133902416011e-13) + 4.72524258737377e-10);
	fConst54 = fConst0 * (fConst0 * (fConst0 * (-2.26854815974171e-18 - fConst42) + 2.99478257737419e-14) + 1.48878720722899e-11) + -3.21884571630651e-10;
	fConst55 = fConst0 * (fConst0 * (fConst0 * (fConst44 + 2.27668641332957e-18) + -2.99937975057913e-14) + -1.49091992300637e-11) + 3.22175630957302e-10;
	fConst56 = fConst0 * (fConst0 * (fConst46 + -7.58895471109855e-17) + -9.99793250193045e-13) + 4.96973307668791e-10;
	fConst57 = fConst0 * (fConst0 * (fConst48 + 2.26022941050514e-18) + -2.97956212909206e-14) + -1.41629211517486e-11;
	fConst58 = fConst0 * (fConst0 * (-2.2652669091101e-18 - fConst50) + 2.98240170724803e-14) + 1.41757277621213e-11;
	fConst59 = fConst0 * (fConst0 * (fConst0 * (7.55088969703365e-17 - fConst52) + 9.94133902416011e-13) + -4.72524258737377e-10);
	fConst60 = fConst0 * (fConst0 * (fConst0 * (fConst30 + 3.40282223961257e-18) + 1.49739128868709e-14) + -7.44393603614497e-12) + -4.82826857445976e-10;
	fConst61 = fConst0 * (fConst0 * (fConst0 * (-3.41502961999435e-18 - fConst32) + -1.49968987528957e-14) + 7.45459961503187e-12) + 4.83263446435953e-10;
	fConst62 = fConst0 * (fConst0 * (-3.79447735554928e-17 - fConst34) + 4.99896625096522e-13) + 7.45459961503187e-10;
	fConst63 = fConst0 * (fConst0 * (-3.39034411575772e-18 - fConst36) + -1.48978106454603e-14) + 7.08146057587431e-12;
	fConst64 = fConst0 * (fConst0 * (fConst38 + 3.39790036366515e-18) + 1.49120085362402e-14) + -7.08786388106065e-12;
	fConst65 = fConst0 * (fConst0 * (fConst0 * (fConst40 + 3.77544484851683e-17) + -4.97066951208006e-13) + -7.08786388106065e-10);
	fConst66 = 1.01444889006918e-20 * fConst0;
	fConst67 = -1.69477435943983e-16 - fConst66;
	fConst68 = 1.15848237217211e-20 * fConst0;
	fConst69 = fConst68 + 1.70600223084551e-14;
	fConst70 = fConst14 * (5.68667410281837e-13 - fConst22);
	fConst71 = 6.76299260046122e-21 * fConst0;
	fConst72 = fConst71 + -3.38954871887967e-16;
	fConst73 = 7.7232158144807e-21 * fConst0;
	fConst74 = 3.41200446169102e-14 - fConst73;
	fConst75 = 2.57440527149357e-19 * fConst0;
	fConst76 = fConst14 * (-1.13733482056367e-12 - fConst75);
	fConst77 = fConst71 + 3.38954871887967e-16;
	fConst78 = -3.41200446169102e-14 - fConst73;
	fConst79 = fConst14 * (fConst75 + -1.13733482056367e-12);
	fConst80 = 1.69477435943983e-16 - fConst66;
	fConst81 = fConst68 + -1.70600223084551e-14;
	fConst82 = fConst17 + -1.69477435943983e-16;
	fConst83 = 1.70600223084551e-14 - fConst19;
	fConst84 = 1.0 / std::tan(270.1769682087222 / fConst0);
	fConst85 = 1.0 - fConst84;
	fConst86 = 1.0 / (fConst84 + 1.0);
	fConst87 = 0.025 / fConst1;
	fConst88 = 1.0 / (fConst2 + 1.0);
	clear_state_f();
}

void Dsp::init_static(unsigned int sample_rate, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double fSlow0 = 0.007000000000000006 * double(fVslider0);
	double fSlow1 = 0.007000000000000006 * double(fVslider1);
	double fSlow2 = 0.007000000000000006 * double(fVslider2);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec8[0] = fSlow0 + 0.993 * fRec8[1];
		fRec9[0] = fSlow1 + 0.993 * fRec9[1];
		double fTemp0 = fRec9[0] * (fConst16 + fConst14 * fRec8[0] * (fConst13 + fConst11 * fRec8[0])) + fConst0 * (fConst9 + fRec8[0] * (fConst7 + fConst5 * fRec8[0])) + 5.36959384928837e-09;
		fRec10[0] = double(input0[i0]) - (fRec10[1] * (fRec9[0] * (fConst65 + fConst14 * fRec8[0] * (fConst64 + fConst63 * fRec8[0])) + fConst0 * (fConst62 + fRec8[0] * (fConst61 + fConst60 * fRec8[0])) + 2.68479692464418e-08) + fRec10[2] * (fRec9[0] * (fConst59 + fConst14 * fRec8[0] * (fConst58 + fConst57 * fRec8[0])) + fConst0 * (fConst56 + fRec8[0] * (fConst55 + fConst54 * fRec8[0])) + 5.36959384928837e-08) + fRec10[3] * (fRec9[0] * (fConst53 + fConst14 * fRec8[0] * (fConst51 + fConst49 * fRec8[0])) + fConst0 * (fConst47 + fRec8[0] * (fConst45 + fConst43 * fRec8[0])) + 5.36959384928837e-08) + fRec10[4] * (fRec9[0] * (fConst41 + fConst14 * fRec8[0] * (fConst39 + fConst37 * fRec8[0])) + fConst0 * (fConst35 + fRec8[0] * (fConst33 + fConst31 * fRec8[0])) + 2.68479692464418e-08) + fRec10[5] * (fRec9[0] * (fConst29 + fConst14 * fRec8[0] * (fConst28 + fConst27 * fRec8[0])) + fConst0 * (fConst26 + fRec8[0] * (fConst25 + fConst24 * fRec8[0])) + 5.36959384928837e-09)) / fTemp0;
		fRec11[0] = fSlow2 + 0.993 * fRec11[1];
		double fTemp1 = fRec11[0] * (fRec10[0] * (fConst70 + fConst21 * fRec8[0] * (fConst83 + fConst82 * fRec8[0])) + fRec10[1] * (fConst23 + fConst21 * fRec8[0] * (fConst81 + fConst80 * fRec8[0])) + fRec10[2] * (fConst79 + fConst21 * fRec8[0] * (fConst78 + fConst77 * fRec8[0])) + fRec10[3] * (fConst76 + fConst21 * fRec8[0] * (fConst74 + fConst72 * fRec8[0])) + fRec10[4] * (fConst70 + fConst21 * fRec8[0] * (fConst69 + fConst67 * fRec8[0])) + fRec10[5] * (fConst23 + fConst21 * fRec8[0] * (fConst20 + fConst18 * fRec8[0]))) / fTemp0;
		fVec0[0] = fTemp1;
		fRec7[0] = 0.9302847925323914 * (fTemp1 + fVec0[1]) - 0.8605695850647829 * fRec7[1];
		fRec6[0] = fRec7[0] - (1.8405051250752198 * fRec6[1] + 0.8612942439318627 * fRec6[2]);
		fRec12[0] = fConst86 * (0.027 * (fRec5[1] + fRec5[2]) - fConst85 * fRec12[1]);
		fRec5[0] = Ftrany(TRANY_TABLE_7199P_68k, 0.9254498422517706 * (fRec6[0] + fRec6[2]) + fRec12[0] + 1.8508996845035413 * fRec6[1] + -3.571981) + -117.70440740740739;
		fRec4[0] = fConst88 * (fConst87 * (fRec5[0] - fRec5[1]) - fConst3 * fRec4[1]);
		fRec3[0] = 0.9302847925323914 * (fRec4[0] + fRec4[1]) - 0.8605695850647829 * fRec3[1];
		fRec2[0] = fRec3[0] - (1.8405051250752198 * fRec2[1] + 0.8612942439318627 * fRec2[2]);
		fRec13[0] = fConst86 * (0.027 * (fRec1[1] + fRec1[2]) - fConst85 * fRec13[1]);
		fRec1[0] = Ftrany(TRANY_TABLE_7199P_68k, 0.9254498422517706 * (fRec2[0] + fRec2[2]) + fRec13[0] + 1.8508996845035413 * fRec2[1] + -3.571981) + -117.70440740740739;
		fRec0[0] = fConst88 * (fConst87 * (fRec1[0] - fRec1[1]) - fConst3 * fRec0[1]);
		output0[i0] = FAUSTFLOAT(fRec0[0]);
		fRec8[1] = fRec8[0];
		fRec9[1] = fRec9[0];
		for (int j0 = 5; j0 > 0; j0 = j0 - 1) {
			fRec10[j0] = fRec10[j0 - 1];
		}
		fRec11[1] = fRec11[0];
		fVec0[1] = fVec0[0];
		fRec7[1] = fRec7[0];
		fRec6[2] = fRec6[1];
		fRec6[1] = fRec6[0];
		fRec12[1] = fRec12[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fRec13[1] = fRec13[0];
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
	reg.registerFloatVar("axface.Attack",N_("Attack"),"S","",&fVslider0, 0.5, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("axface.Level",N_("Level"),"S","",&fVslider2, 0.5, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("axface.Smooth",N_("Smooth"),"S","",&fVslider1, 0.5, 0.0, 1.0, 0.01, 0);
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
                        <property name=\"var_id\">axface.Attack</property>\n\
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
                        <property name=\"var_id\">axface.Level</property>\n\
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
                        <property name=\"var_id\">axface.Smooth</property>\n\
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
                <property name=\"var_id\">axface.Level</property>\n\
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
#define PARAM(p) ("axface" "." p)

b.openHorizontalhideBox("");
    b.create_master_slider(PARAM("Attack"), "Attack");
b.closeBox();
b.openHorizontalBox("");

    b.create_small_rackknobr(PARAM("Attack"), "Attack");

    b.create_small_rackknobr(PARAM("Smooth"), "Smooth");

    b.create_small_rackknobr(PARAM("Level"), "Level");
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

} // end namespace axface
} // end namespace pluginlib
