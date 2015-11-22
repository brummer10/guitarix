// generated from file '../src/plugins/axface.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"
#include "trany.h"

namespace pluginlib {
namespace axface {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	FAUSTFLOAT 	fslider0;
	double 	fRec8[2];
	double 	fConst9;
	double 	fConst10;
	double 	fConst11;
	double 	fConst12;
	double 	fConst13;
	double 	fConst14;
	FAUSTFLOAT 	fslider1;
	double 	fRec9[2];
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
	double 	fRec10[6];
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
	FAUSTFLOAT 	fslider2;
	double 	fRec11[2];
	double 	fVec0[2];
	double 	fConst85;
	double 	fConst86;
	double 	fConst87;
	double 	fRec7[2];
	double 	fRec6[3];
	double 	fConst88;
	double 	fConst89;
	double 	fConst90;
	double 	fConst91;
	double 	fRec12[2];
	double 	fRec5[3];
	double 	fConst92;
	double 	fConst93;
	double 	fConst94;
	double 	fConst95;
	double 	fConst96;
	double 	fRec4[2];
	double 	fConst97;
	double 	fRec3[2];
	double 	fRec2[3];
	double 	fRec13[2];
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
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<6; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
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
	fConst7 = (1.70577582462647e-23 * fConst6);
	fConst8 = (2.48486653834396e-10 + (fConst6 * (4.99896625096522e-13 + (fConst6 * (3.79447735554928e-17 + fConst7)))));
	fConst9 = (3.77313513934094e-25 * fConst6);
	fConst10 = (7.08146057587431e-12 + (fConst6 * (1.48978106454603e-14 + (fConst6 * (1.13011470525257e-18 + fConst9)))));
	fConst11 = (4.4415330562134e-25 * fConst6);
	fConst12 = ((fConst6 * ((fConst6 * (0 - (1.13263345455505e-18 + fConst11))) - 1.49120085362402e-14)) - 7.08786388106065e-12);
	fConst13 = (1.4805110187378e-23 * fConst6);
	fConst14 = ((fConst6 * ((fConst6 * (0 - (3.77544484851683e-17 + fConst13))) - 4.97066951208006e-13)) - 2.36262129368688e-10);
	fConst15 = (4.03791059191999e-25 * fConst6);
	fConst16 = ((fConst6 * ((fConst6 * ((fConst6 * (0 - (1.13427407987086e-18 + fConst15))) - 1.49739128868709e-14)) - 7.44393603614497e-12)) - 1.60942285815325e-10);
	fConst17 = (5.1173274738794e-25 * fConst6);
	fConst18 = (1.61087815478651e-10 + (fConst6 * (7.45459961503187e-12 + (fConst6 * (1.49968987528957e-14 + (fConst6 * (1.13834320666478e-18 + fConst17)))))));
	fConst19 = (3.38149630023061e-21 * fConst6);
	fConst20 = (1.69477435943983e-16 + fConst19);
	fConst21 = (3.86160790724035e-21 * fConst6);
	fConst22 = (0 - (1.70600223084551e-14 + fConst21));
	fConst23 = (1.28720263574678e-19 * fConst6);
	fConst24 = (5.68667410281837e-13 + fConst23);
	fConst25 = ((fConst6 * (4.99896625096522e-13 + (fConst6 * (fConst7 - 3.79447735554928e-17)))) - 2.48486653834396e-10);
	fConst26 = (7.08146057587431e-12 + (fConst6 * ((fConst6 * (1.13011470525257e-18 - fConst9)) - 1.48978106454603e-14)));
	fConst27 = ((fConst6 * (1.49120085362402e-14 + (fConst6 * (fConst11 - 1.13263345455505e-18)))) - 7.08786388106065e-12);
	fConst28 = (2.36262129368688e-10 + (fConst6 * ((fConst6 * (3.77544484851683e-17 - fConst13)) - 4.97066951208006e-13)));
	fConst29 = (1.60942285815325e-10 + (fConst6 * ((fConst6 * (1.49739128868709e-14 + (fConst6 * (fConst15 - 1.13427407987086e-18)))) - 7.44393603614497e-12)));
	fConst30 = ((fConst6 * (7.45459961503187e-12 + (fConst6 * ((fConst6 * (1.13834320666478e-18 - fConst17)) - 1.49968987528957e-14)))) - 1.61087815478651e-10);
	fConst31 = (5.1173274738794e-23 * fConst6);
	fConst32 = ((fConst6 * (4.99896625096522e-13 + (fConst6 * (3.79447735554928e-17 - fConst31)))) - 7.45459961503187e-10);
	fConst33 = (1.88656756967047e-24 * fConst6);
	fConst34 = (7.08146057587431e-12 + (fConst6 * (1.48978106454603e-14 + (fConst6 * (fConst33 - 3.39034411575772e-18)))));
	fConst35 = (2.2207665281067e-24 * fConst6);
	fConst36 = ((fConst6 * ((fConst6 * (3.39790036366515e-18 - fConst35)) - 1.49120085362402e-14)) - 7.08786388106065e-12);
	fConst37 = (4.4415330562134e-23 * fConst6);
	fConst38 = (7.08786388106065e-10 + (fConst6 * ((fConst6 * (fConst37 - 3.77544484851683e-17)) - 4.97066951208006e-13)));
	fConst39 = (2.01895529596e-24 * fConst6);
	fConst40 = (4.82826857445976e-10 + (fConst6 * ((fConst6 * ((fConst6 * (3.40282223961257e-18 - fConst39)) - 1.49739128868709e-14)) - 7.44393603614497e-12)));
	fConst41 = (2.5586637369397e-24 * fConst6);
	fConst42 = ((fConst6 * (7.45459961503187e-12 + (fConst6 * (1.49968987528957e-14 + (fConst6 * (fConst41 - 3.41502961999435e-18)))))) - 4.83263446435953e-10);
	fConst43 = (3.41155164925293e-23 * fConst6);
	fConst44 = ((fConst6 * ((fConst6 * (7.58895471109855e-17 + fConst43)) - 9.99793250193045e-13)) - 4.96973307668791e-10);
	fConst45 = (3.77313513934094e-24 * fConst6);
	fConst46 = ((fConst6 * (2.97956212909206e-14 + (fConst6 * (2.26022941050514e-18 - fConst45)))) - 1.41629211517486e-11);
	fConst47 = (4.4415330562134e-24 * fConst6);
	fConst48 = (1.41757277621213e-11 + (fConst6 * ((fConst6 * (fConst47 - 2.2652669091101e-18)) - 2.98240170724803e-14)));
	fConst49 = (2.9610220374756e-23 * fConst6);
	fConst50 = (4.72524258737377e-10 + (fConst6 * (9.94133902416011e-13 + (fConst6 * (0 - (7.55088969703365e-17 + fConst49))))));
	fConst51 = (4.03791059191999e-24 * fConst6);
	fConst52 = (3.21884571630651e-10 + (fConst6 * (1.48878720722899e-11 + (fConst6 * ((fConst6 * (fConst51 - 2.26854815974171e-18)) - 2.99478257737419e-14)))));
	fConst53 = (5.1173274738794e-24 * fConst6);
	fConst54 = ((fConst6 * ((fConst6 * (2.99937975057913e-14 + (fConst6 * (2.27668641332957e-18 - fConst53)))) - 1.49091992300637e-11)) - 3.22175630957302e-10);
	fConst55 = (4.96973307668791e-10 + (fConst6 * ((fConst6 * (fConst43 - 7.58895471109855e-17)) - 9.99793250193045e-13)));
	fConst56 = ((fConst6 * ((fConst6 * (2.26022941050514e-18 + fConst45)) - 2.97956212909206e-14)) - 1.41629211517486e-11);
	fConst57 = (1.41757277621213e-11 + (fConst6 * (2.98240170724803e-14 + (fConst6 * (0 - (2.2652669091101e-18 + fConst47))))));
	fConst58 = ((fConst6 * (9.94133902416011e-13 + (fConst6 * (7.55088969703365e-17 - fConst49)))) - 4.72524258737377e-10);
	fConst59 = ((fConst6 * (1.48878720722899e-11 + (fConst6 * (2.99478257737419e-14 + (fConst6 * (0 - (2.26854815974171e-18 + fConst51))))))) - 3.21884571630651e-10);
	fConst60 = (3.22175630957302e-10 + (fConst6 * ((fConst6 * ((fConst6 * (2.27668641332957e-18 + fConst53)) - 2.99937975057913e-14)) - 1.49091992300637e-11)));
	fConst61 = (7.45459961503187e-10 + (fConst6 * (4.99896625096522e-13 + (fConst6 * (0 - (3.79447735554928e-17 + fConst31))))));
	fConst62 = (7.08146057587431e-12 + (fConst6 * ((fConst6 * (0 - (3.39034411575772e-18 + fConst33))) - 1.48978106454603e-14)));
	fConst63 = ((fConst6 * (1.49120085362402e-14 + (fConst6 * (3.39790036366515e-18 + fConst35)))) - 7.08786388106065e-12);
	fConst64 = ((fConst6 * ((fConst6 * (3.77544484851683e-17 + fConst37)) - 4.97066951208006e-13)) - 7.08786388106065e-10);
	fConst65 = ((fConst6 * ((fConst6 * (1.49739128868709e-14 + (fConst6 * (3.40282223961257e-18 + fConst39)))) - 7.44393603614497e-12)) - 4.82826857445976e-10);
	fConst66 = (4.83263446435953e-10 + (fConst6 * (7.45459961503187e-12 + (fConst6 * ((fConst6 * (0 - (3.41502961999435e-18 + fConst41))) - 1.49968987528957e-14)))));
	fConst67 = (1.01444889006918e-20 * fConst6);
	fConst68 = (0 - (1.69477435943983e-16 + fConst67));
	fConst69 = (1.15848237217211e-20 * fConst6);
	fConst70 = (1.70600223084551e-14 + fConst69);
	fConst71 = (5.68667410281837e-13 - fConst23);
	fConst72 = (6.76299260046122e-21 * fConst6);
	fConst73 = (fConst72 - 3.38954871887967e-16);
	fConst74 = (7.7232158144807e-21 * fConst6);
	fConst75 = (3.41200446169102e-14 - fConst74);
	fConst76 = (2.57440527149357e-19 * fConst6);
	fConst77 = (0 - (1.13733482056367e-12 + fConst76));
	fConst78 = (3.38954871887967e-16 + fConst72);
	fConst79 = (0 - (3.41200446169102e-14 + fConst74));
	fConst80 = (fConst76 - 1.13733482056367e-12);
	fConst81 = (1.69477435943983e-16 - fConst67);
	fConst82 = (fConst69 - 1.70600223084551e-14);
	fConst83 = (fConst19 - 1.69477435943983e-16);
	fConst84 = (1.70600223084551e-14 - fConst21);
	fConst85 = (1 + fConst3);
	fConst86 = (faustpower<2>(fConst6) / fConst85);
	fConst87 = (0 - ((1 - fConst3) / fConst85));
	fConst88 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst89 = (1 + fConst88);
	fConst90 = (0.027 / fConst89);
	fConst91 = (0 - ((1 - fConst88) / fConst89));
	fConst92 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst93 = (0 - fConst92);
	fConst94 = (1 + fConst92);
	fConst95 = (0.025 / fConst94);
	fConst96 = (0 - ((1 - fConst92) / fConst94));
	fConst97 = (1.0 / fConst85);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlow0 = (0.007000000000000006 * double(fslider0));
	double 	fSlow1 = (0.007000000000000006 * double(fslider1));
	double 	fSlow2 = (0.007000000000000006 * double(fslider2));
	for (int i=0; i<count; i++) {
		fRec8[0] = ((0.993 * fRec8[1]) + fSlow0);
		fRec9[0] = ((0.993 * fRec9[1]) + fSlow1);
		double fTemp0 = (5.36959384928837e-09 + (fConst6 * (((fRec8[0] * (fConst18 + (fConst16 * fRec8[0]))) + (fRec9[0] * (fConst14 + (fConst6 * (fRec8[0] * (fConst12 + (fConst10 * fRec8[0]))))))) + fConst8)));
		fRec10[0] = ((double)input0[i] - ((((((fRec10[1] * (2.68479692464418e-08 + (fConst6 * (((fRec8[0] * (fConst66 + (fConst65 * fRec8[0]))) + (fRec9[0] * (fConst64 + (fConst6 * (fRec8[0] * (fConst63 + (fConst62 * fRec8[0]))))))) + fConst61)))) + (fRec10[2] * (5.36959384928837e-08 + (fConst6 * (((fRec8[0] * (fConst60 + (fConst59 * fRec8[0]))) + (fRec9[0] * (fConst58 + (fConst6 * (fRec8[0] * (fConst57 + (fConst56 * fRec8[0]))))))) + fConst55))))) + (fRec10[3] * (5.36959384928837e-08 + (fConst6 * (((fRec8[0] * (fConst54 + (fConst52 * fRec8[0]))) + (fRec9[0] * (fConst50 + (fConst6 * (fRec8[0] * (fConst48 + (fConst46 * fRec8[0]))))))) + fConst44))))) + (fRec10[4] * (2.68479692464418e-08 + (fConst6 * (((fRec8[0] * (fConst42 + (fConst40 * fRec8[0]))) + (fRec9[0] * (fConst38 + (fConst6 * (fRec8[0] * (fConst36 + (fConst34 * fRec8[0]))))))) + fConst32))))) + (fRec10[5] * (5.36959384928837e-09 + (fConst6 * (((fRec8[0] * (fConst30 + (fConst29 * fRec8[0]))) + (fRec9[0] * (fConst28 + (fConst6 * (fRec8[0] * (fConst27 + (fConst26 * fRec8[0]))))))) + fConst25))))) / fTemp0));
		fRec11[0] = ((0.993 * fRec11[1]) + fSlow2);
		double fTemp1 = ((fRec11[0] * ((((((fRec10[0] * (fConst71 + (fConst6 * (fRec8[0] * (fConst84 + (fConst83 * fRec8[0])))))) + (fRec10[1] * (fConst24 + (fConst6 * (fRec8[0] * (fConst82 + (fConst81 * fRec8[0]))))))) + (fRec10[2] * (fConst80 + (fConst6 * (fRec8[0] * (fConst79 + (fConst78 * fRec8[0]))))))) + (fRec10[3] * (fConst77 + (fConst6 * (fRec8[0] * (fConst75 + (fConst73 * fRec8[0]))))))) + (fRec10[4] * (fConst71 + (fConst6 * (fRec8[0] * (fConst70 + (fConst68 * fRec8[0]))))))) + (fRec10[5] * (fConst24 + (fConst6 * (fRec8[0] * (fConst22 + (fConst20 * fRec8[0])))))))) / fTemp0);
		fVec0[0] = fTemp1;
		fRec7[0] = ((fConst87 * fRec7[1]) + (fConst86 * (fVec0[0] + fVec0[1])));
		fRec6[0] = (fRec7[0] - (fConst5 * ((fConst4 * fRec6[2]) + (fConst2 * fRec6[1]))));
		fRec12[0] = ((fConst91 * fRec12[1]) + (fConst90 * (fRec5[1] + fRec5[2])));
		fRec5[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec12[0] + (fConst5 * (fRec6[2] + (fRec6[0] + (2 * fRec6[1]))))) - 3.571981)) - 117.70440740740739);
		fRec4[0] = ((fConst96 * fRec4[1]) + (fConst95 * ((fConst92 * fRec5[0]) + (fConst93 * fRec5[1]))));
		fRec3[0] = ((fConst87 * fRec3[1]) + (fConst97 * (fRec4[0] + fRec4[1])));
		fRec2[0] = (fRec3[0] - (fConst5 * ((fConst4 * fRec2[2]) + (fConst2 * fRec2[1]))));
		fRec13[0] = ((fConst91 * fRec13[1]) + (fConst90 * (fRec1[1] + fRec1[2])));
		fRec1[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec13[0] + (fConst5 * (fRec2[2] + (fRec2[0] + (2 * fRec2[1]))))) - 3.571981)) - 117.70440740740739);
		fRec0[0] = ((fConst96 * fRec0[1]) + (fConst95 * ((fConst92 * fRec1[0]) + (fConst93 * fRec1[1]))));
		output0[i] = (FAUSTFLOAT)fRec0[0];
		// post processing
		fRec0[1] = fRec0[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec13[1] = fRec13[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec12[1] = fRec12[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec7[1] = fRec7[0];
		fVec0[1] = fVec0[0];
		fRec11[1] = fRec11[0];
		for (int i=5; i>0; i--) fRec10[i] = fRec10[i-1];
		fRec9[1] = fRec9[0];
		fRec8[1] = fRec8[0];
	}

}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("axface.Attack",N_("Attack"),"S","",&fslider0, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("axface.Level",N_("Level"),"S","",&fslider2, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("axface.Smooth",N_("Smooth"),"S","",&fslider1, 0.5, 0.0, 1.0, 0.01);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
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
