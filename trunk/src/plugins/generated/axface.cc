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
	FAUSTFLOAT 	fslider0;
	double 	fRec8[2];
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	double 	fConst9;
	FAUSTFLOAT 	fslider1;
	double 	fRec9[2];
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
	double 	fRec10[6];
	double 	fConst62;
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
	FAUSTFLOAT 	fslider2;
	double 	fRec11[2];
	double 	fVec0[2];
	double 	fConst80;
	double 	fRec7[2];
	double 	fRec6[3];
	double 	fConst81;
	double 	fConst82;
	double 	fConst83;
	double 	fConst84;
	double 	fRec12[2];
	double 	fRec5[3];
	double 	fConst85;
	double 	fConst86;
	double 	fConst87;
	double 	fConst88;
	double 	fConst89;
	double 	fRec4[2];
	double 	fRec3[2];
	double 	fRec2[3];
	double 	fRec13[2];
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
	fConst1 = double(iConst0);
	fConst2 = (1.70577582462647e-23 * fConst1);
	fConst3 = (2.48486653834396e-10 + (fConst1 * (4.99896625096522e-13 + (fConst1 * (3.79447735554928e-17 + fConst2)))));
	fConst4 = (3.77313513934094e-25 * fConst1);
	fConst5 = (7.08146057587431e-12 + (fConst1 * (1.48978106454603e-14 + (fConst1 * (1.13011470525257e-18 + fConst4)))));
	fConst6 = (4.4415330562134e-25 * fConst1);
	fConst7 = ((fConst1 * ((fConst1 * (0 - (1.13263345455505e-18 + fConst6))) - 1.49120085362402e-14)) - 7.08786388106065e-12);
	fConst8 = (1.4805110187378e-23 * fConst1);
	fConst9 = ((fConst1 * ((fConst1 * (0 - (3.77544484851683e-17 + fConst8))) - 4.97066951208006e-13)) - 2.36262129368688e-10);
	fConst10 = (4.03791059191999e-25 * fConst1);
	fConst11 = ((fConst1 * ((fConst1 * ((fConst1 * (0 - (1.13427407987086e-18 + fConst10))) - 1.49739128868709e-14)) - 7.44393603614497e-12)) - 1.60942285815325e-10);
	fConst12 = (5.1173274738794e-25 * fConst1);
	fConst13 = (1.61087815478651e-10 + (fConst1 * (7.45459961503187e-12 + (fConst1 * (1.49968987528957e-14 + (fConst1 * (1.13834320666478e-18 + fConst12)))))));
	fConst14 = (3.38149630023061e-21 * fConst1);
	fConst15 = (1.69477435943983e-16 + fConst14);
	fConst16 = (3.86160790724035e-21 * fConst1);
	fConst17 = (0 - (1.70600223084551e-14 + fConst16));
	fConst18 = (1.28720263574678e-19 * fConst1);
	fConst19 = (5.68667410281837e-13 + fConst18);
	fConst20 = ((fConst1 * (4.99896625096522e-13 + (fConst1 * (fConst2 - 3.79447735554928e-17)))) - 2.48486653834396e-10);
	fConst21 = (7.08146057587431e-12 + (fConst1 * ((fConst1 * (1.13011470525257e-18 - fConst4)) - 1.48978106454603e-14)));
	fConst22 = ((fConst1 * (1.49120085362402e-14 + (fConst1 * (fConst6 - 1.13263345455505e-18)))) - 7.08786388106065e-12);
	fConst23 = (2.36262129368688e-10 + (fConst1 * ((fConst1 * (3.77544484851683e-17 - fConst8)) - 4.97066951208006e-13)));
	fConst24 = (1.60942285815325e-10 + (fConst1 * ((fConst1 * (1.49739128868709e-14 + (fConst1 * (fConst10 - 1.13427407987086e-18)))) - 7.44393603614497e-12)));
	fConst25 = ((fConst1 * (7.45459961503187e-12 + (fConst1 * ((fConst1 * (1.13834320666478e-18 - fConst12)) - 1.49968987528957e-14)))) - 1.61087815478651e-10);
	fConst26 = (5.1173274738794e-23 * fConst1);
	fConst27 = ((fConst1 * (4.99896625096522e-13 + (fConst1 * (3.79447735554928e-17 - fConst26)))) - 7.45459961503187e-10);
	fConst28 = (1.88656756967047e-24 * fConst1);
	fConst29 = (7.08146057587431e-12 + (fConst1 * (1.48978106454603e-14 + (fConst1 * (fConst28 - 3.39034411575772e-18)))));
	fConst30 = (2.2207665281067e-24 * fConst1);
	fConst31 = ((fConst1 * ((fConst1 * (3.39790036366515e-18 - fConst30)) - 1.49120085362402e-14)) - 7.08786388106065e-12);
	fConst32 = (4.4415330562134e-23 * fConst1);
	fConst33 = (7.08786388106065e-10 + (fConst1 * ((fConst1 * (fConst32 - 3.77544484851683e-17)) - 4.97066951208006e-13)));
	fConst34 = (2.01895529596e-24 * fConst1);
	fConst35 = (4.82826857445976e-10 + (fConst1 * ((fConst1 * ((fConst1 * (3.40282223961257e-18 - fConst34)) - 1.49739128868709e-14)) - 7.44393603614497e-12)));
	fConst36 = (2.5586637369397e-24 * fConst1);
	fConst37 = ((fConst1 * (7.45459961503187e-12 + (fConst1 * (1.49968987528957e-14 + (fConst1 * (fConst36 - 3.41502961999435e-18)))))) - 4.83263446435953e-10);
	fConst38 = (3.41155164925293e-23 * fConst1);
	fConst39 = ((fConst1 * ((fConst1 * (7.58895471109855e-17 + fConst38)) - 9.99793250193045e-13)) - 4.96973307668791e-10);
	fConst40 = (3.77313513934094e-24 * fConst1);
	fConst41 = ((fConst1 * (2.97956212909206e-14 + (fConst1 * (2.26022941050514e-18 - fConst40)))) - 1.41629211517486e-11);
	fConst42 = (4.4415330562134e-24 * fConst1);
	fConst43 = (1.41757277621213e-11 + (fConst1 * ((fConst1 * (fConst42 - 2.2652669091101e-18)) - 2.98240170724803e-14)));
	fConst44 = (2.9610220374756e-23 * fConst1);
	fConst45 = (4.72524258737377e-10 + (fConst1 * (9.94133902416011e-13 + (fConst1 * (0 - (7.55088969703365e-17 + fConst44))))));
	fConst46 = (4.03791059191999e-24 * fConst1);
	fConst47 = (3.21884571630651e-10 + (fConst1 * (1.48878720722899e-11 + (fConst1 * ((fConst1 * (fConst46 - 2.26854815974171e-18)) - 2.99478257737419e-14)))));
	fConst48 = (5.1173274738794e-24 * fConst1);
	fConst49 = ((fConst1 * ((fConst1 * (2.99937975057913e-14 + (fConst1 * (2.27668641332957e-18 - fConst48)))) - 1.49091992300637e-11)) - 3.22175630957302e-10);
	fConst50 = (4.96973307668791e-10 + (fConst1 * ((fConst1 * (fConst38 - 7.58895471109855e-17)) - 9.99793250193045e-13)));
	fConst51 = ((fConst1 * ((fConst1 * (2.26022941050514e-18 + fConst40)) - 2.97956212909206e-14)) - 1.41629211517486e-11);
	fConst52 = (1.41757277621213e-11 + (fConst1 * (2.98240170724803e-14 + (fConst1 * (0 - (2.2652669091101e-18 + fConst42))))));
	fConst53 = ((fConst1 * (9.94133902416011e-13 + (fConst1 * (7.55088969703365e-17 - fConst44)))) - 4.72524258737377e-10);
	fConst54 = ((fConst1 * (1.48878720722899e-11 + (fConst1 * (2.99478257737419e-14 + (fConst1 * (0 - (2.26854815974171e-18 + fConst46))))))) - 3.21884571630651e-10);
	fConst55 = (3.22175630957302e-10 + (fConst1 * ((fConst1 * ((fConst1 * (2.27668641332957e-18 + fConst48)) - 2.99937975057913e-14)) - 1.49091992300637e-11)));
	fConst56 = (7.45459961503187e-10 + (fConst1 * (4.99896625096522e-13 + (fConst1 * (0 - (3.79447735554928e-17 + fConst26))))));
	fConst57 = (7.08146057587431e-12 + (fConst1 * ((fConst1 * (0 - (3.39034411575772e-18 + fConst28))) - 1.48978106454603e-14)));
	fConst58 = ((fConst1 * (1.49120085362402e-14 + (fConst1 * (3.39790036366515e-18 + fConst30)))) - 7.08786388106065e-12);
	fConst59 = ((fConst1 * ((fConst1 * (3.77544484851683e-17 + fConst32)) - 4.97066951208006e-13)) - 7.08786388106065e-10);
	fConst60 = ((fConst1 * ((fConst1 * (1.49739128868709e-14 + (fConst1 * (3.40282223961257e-18 + fConst34)))) - 7.44393603614497e-12)) - 4.82826857445976e-10);
	fConst61 = (4.83263446435953e-10 + (fConst1 * (7.45459961503187e-12 + (fConst1 * ((fConst1 * (0 - (3.41502961999435e-18 + fConst36))) - 1.49968987528957e-14)))));
	fConst62 = (1.01444889006918e-20 * fConst1);
	fConst63 = (0 - (1.69477435943983e-16 + fConst62));
	fConst64 = (1.15848237217211e-20 * fConst1);
	fConst65 = (1.70600223084551e-14 + fConst64);
	fConst66 = (5.68667410281837e-13 - fConst18);
	fConst67 = (6.76299260046122e-21 * fConst1);
	fConst68 = (fConst67 - 3.38954871887967e-16);
	fConst69 = (7.7232158144807e-21 * fConst1);
	fConst70 = (3.41200446169102e-14 - fConst69);
	fConst71 = (2.57440527149357e-19 * fConst1);
	fConst72 = (0 - (1.13733482056367e-12 + fConst71));
	fConst73 = (3.38954871887967e-16 + fConst67);
	fConst74 = (0 - (3.41200446169102e-14 + fConst69));
	fConst75 = (fConst71 - 1.13733482056367e-12);
	fConst76 = (1.69477435943983e-16 - fConst62);
	fConst77 = (fConst64 - 1.70600223084551e-14);
	fConst78 = (fConst14 - 1.69477435943983e-16);
	fConst79 = (1.70600223084551e-14 - fConst16);
	fConst80 = (0.9302847925323914 * faustpower<2>(fConst1));
	fConst81 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst82 = (1 + fConst81);
	fConst83 = (0.027 / fConst82);
	fConst84 = (0 - ((1 - fConst81) / fConst82));
	fConst85 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst86 = (0 - fConst85);
	fConst87 = (1 + fConst85);
	fConst88 = (0.025 / fConst87);
	fConst89 = (0 - ((1 - fConst85) / fConst87));
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
		double fTemp0 = (5.36959384928837e-09 + (fConst1 * (((fRec8[0] * (fConst13 + (fConst11 * fRec8[0]))) + (fRec9[0] * (fConst9 + (fConst1 * (fRec8[0] * (fConst7 + (fConst5 * fRec8[0]))))))) + fConst3)));
		fRec10[0] = ((double)input0[i] - ((((((fRec10[1] * (2.68479692464418e-08 + (fConst1 * (((fRec8[0] * (fConst61 + (fConst60 * fRec8[0]))) + (fRec9[0] * (fConst59 + (fConst1 * (fRec8[0] * (fConst58 + (fConst57 * fRec8[0]))))))) + fConst56)))) + (fRec10[2] * (5.36959384928837e-08 + (fConst1 * (((fRec8[0] * (fConst55 + (fConst54 * fRec8[0]))) + (fRec9[0] * (fConst53 + (fConst1 * (fRec8[0] * (fConst52 + (fConst51 * fRec8[0]))))))) + fConst50))))) + (fRec10[3] * (5.36959384928837e-08 + (fConst1 * (((fRec8[0] * (fConst49 + (fConst47 * fRec8[0]))) + (fRec9[0] * (fConst45 + (fConst1 * (fRec8[0] * (fConst43 + (fConst41 * fRec8[0]))))))) + fConst39))))) + (fRec10[4] * (2.68479692464418e-08 + (fConst1 * (((fRec8[0] * (fConst37 + (fConst35 * fRec8[0]))) + (fRec9[0] * (fConst33 + (fConst1 * (fRec8[0] * (fConst31 + (fConst29 * fRec8[0]))))))) + fConst27))))) + (fRec10[5] * (5.36959384928837e-09 + (fConst1 * (((fRec8[0] * (fConst25 + (fConst24 * fRec8[0]))) + (fRec9[0] * (fConst23 + (fConst1 * (fRec8[0] * (fConst22 + (fConst21 * fRec8[0]))))))) + fConst20))))) / fTemp0));
		fRec11[0] = ((0.993 * fRec11[1]) + fSlow2);
		double fTemp1 = ((fRec11[0] * ((((((fRec10[0] * (fConst66 + (fConst1 * (fRec8[0] * (fConst79 + (fConst78 * fRec8[0])))))) + (fRec10[1] * (fConst19 + (fConst1 * (fRec8[0] * (fConst77 + (fConst76 * fRec8[0]))))))) + (fRec10[2] * (fConst75 + (fConst1 * (fRec8[0] * (fConst74 + (fConst73 * fRec8[0]))))))) + (fRec10[3] * (fConst72 + (fConst1 * (fRec8[0] * (fConst70 + (fConst68 * fRec8[0]))))))) + (fRec10[4] * (fConst66 + (fConst1 * (fRec8[0] * (fConst65 + (fConst63 * fRec8[0]))))))) + (fRec10[5] * (fConst19 + (fConst1 * (fRec8[0] * (fConst17 + (fConst15 * fRec8[0])))))))) / fTemp0);
		fVec0[0] = fTemp1;
		fRec7[0] = ((fConst80 * (fVec0[0] + fVec0[1])) - (0.8605695850647829 * fRec7[1]));
		fRec6[0] = (fRec7[0] - ((1.8405051250752198 * fRec6[1]) + (0.8612942439318627 * fRec6[2])));
		fRec12[0] = ((fConst84 * fRec12[1]) + (fConst83 * (fRec5[1] + fRec5[2])));
		fRec5[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec12[0] + (0.9254498422517706 * (fRec6[2] + (fRec6[0] + (2.0 * fRec6[1]))))) - 3.571981)) - 117.70440740740739);
		fRec4[0] = ((fConst89 * fRec4[1]) + (fConst88 * ((fConst85 * fRec5[0]) + (fConst86 * fRec5[1]))));
		fRec3[0] = ((0.9302847925323914 * (fRec4[0] + fRec4[1])) - (0.8605695850647829 * fRec3[1]));
		fRec2[0] = (fRec3[0] - ((1.8405051250752198 * fRec2[1]) + (0.8612942439318627 * fRec2[2])));
		fRec13[0] = ((fConst84 * fRec13[1]) + (fConst83 * (fRec1[1] + fRec1[2])));
		fRec1[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec13[0] + (0.9254498422517706 * (fRec2[2] + (fRec2[0] + (2.0 * fRec2[1]))))) - 3.571981)) - 117.70440740740739);
		fRec0[0] = ((fConst89 * fRec0[1]) + (fConst88 * ((fConst85 * fRec1[0]) + (fConst86 * fRec1[1]))));
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
                <property name=\"xalign\">0</property>\n\
                <property name=\"label\" translatable=\"yes\">Level</property>\n\
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
