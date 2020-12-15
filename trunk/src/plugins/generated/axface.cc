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
	double fConst4;
	FAUSTFLOAT fVslider0;
	double fRec8[2];
	double fConst5;
	double fConst6;
	FAUSTFLOAT fVslider1;
	double fRec10[2];
	double fConst7;
	double fConst8;
	double fConst9;
	double fConst10;
	FAUSTFLOAT fVslider2;
	double fRec11[2];
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
	double fRec9[6];
	double fConst59;
	double fConst60;
	double fConst61;
	double fConst62;
	double fConst63;
	double fConst64;
	double fConst65;
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
	double fVec0[2];
	double fRec7[2];
	double fRec6[3];
	double fRec5[2];
	double fRec4[2];
	double fRec3[2];
	double fRec2[3];
	double fRec1[2];
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec8[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec10[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec11[l2] = 0.0;
	for (int l3 = 0; (l3 < 6); l3 = (l3 + 1)) fRec9[l3] = 0.0;
	for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) fVec0[l4] = 0.0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fRec7[l5] = 0.0;
	for (int l6 = 0; (l6 < 3); l6 = (l6 + 1)) fRec6[l6] = 0.0;
	for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) fRec5[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fRec4[l8] = 0.0;
	for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) fRec3[l9] = 0.0;
	for (int l10 = 0; (l10 < 3); l10 = (l10 + 1)) fRec2[l10] = 0.0;
	for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) fRec1[l11] = 0.0;
	for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) fRec0[l12] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = (3.1415926535897931 / fConst0);
	fConst2 = (1.0 / (fConst1 + 1.0));
	fConst3 = (1.0 - fConst1);
	fConst4 = (0.93028479253239138 * mydsp_faustpower2_f(fConst0));
	fConst5 = (5.1173274738794002e-23 * fConst0);
	fConst6 = ((fConst0 * ((fConst0 * (-3.7944773555492801e-17 - fConst5)) + 4.9989662509652203e-13)) + 7.45459961503187e-10);
	fConst7 = (2.5586637369397002e-24 * fConst0);
	fConst8 = ((fConst0 * ((fConst0 * ((fConst0 * (-3.4150296199943501e-18 - fConst7)) + -1.4996898752895701e-14)) + 7.4545996150318701e-12)) + 4.8326344643595296e-10);
	fConst9 = (2.01895529596e-24 * fConst0);
	fConst10 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst9 + 3.4028222396125701e-18)) + 1.49739128868709e-14)) + -7.4439360361449699e-12)) + -4.8282685744597599e-10);
	fConst11 = (4.4415330562134001e-23 * fConst0);
	fConst12 = ((fConst0 * ((fConst0 * (fConst11 + 3.7754448485168298e-17)) + -4.9706695120800598e-13)) + -7.0878638810606497e-10);
	fConst13 = (2.2207665281067002e-24 * fConst0);
	fConst14 = ((fConst0 * ((fConst0 * (fConst13 + 3.3979003636651499e-18)) + 1.4912008536240202e-14)) + -7.08786388106065e-12);
	fConst15 = (1.88656756967047e-24 * fConst0);
	fConst16 = ((fConst0 * ((fConst0 * (-3.3903441157577201e-18 - fConst15)) + -1.4897810645460301e-14)) + 7.08146057587431e-12);
	fConst17 = (3.4115516492529297e-23 * fConst0);
	fConst18 = ((fConst0 * ((fConst0 * (fConst17 + -7.5889547110985503e-17)) + -9.9979325019304507e-13)) + 4.9697330766879095e-10);
	fConst19 = (5.1173274738794003e-24 * fConst0);
	fConst20 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst19 + 2.2766864133295699e-18)) + -2.99937975057913e-14)) + -1.4909199230063702e-11)) + 3.2217563095730201e-10);
	fConst21 = (4.0379105919199897e-24 * fConst0);
	fConst22 = ((fConst0 * ((fConst0 * ((fConst0 * (-2.2685481597417102e-18 - fConst21)) + 2.9947825773741901e-14)) + 1.4887872072289901e-11)) + -3.2188457163065099e-10);
	fConst23 = (2.9610220374756002e-23 * fConst0);
	fConst24 = ((fConst0 * ((fConst0 * (7.5508896970336498e-17 - fConst23)) + 9.9413390241601095e-13)) + -4.7252425873737703e-10);
	fConst25 = (4.4415330562134003e-24 * fConst0);
	fConst26 = ((fConst0 * ((fConst0 * (-2.2652669091101002e-18 - fConst25)) + 2.9824017072480302e-14)) + 1.41757277621213e-11);
	fConst27 = (3.7731351393409399e-24 * fConst0);
	fConst28 = ((fConst0 * ((fConst0 * (fConst27 + 2.26022941050514e-18)) + -2.9795621290920602e-14)) + -1.4162921151748601e-11);
	fConst29 = ((fConst0 * ((fConst0 * (fConst17 + 7.5889547110985503e-17)) + -9.9979325019304507e-13)) + -4.9697330766879095e-10);
	fConst30 = ((fConst0 * ((fConst0 * ((fConst0 * (2.2766864133295699e-18 - fConst19)) + 2.99937975057913e-14)) + -1.4909199230063702e-11)) + -3.2217563095730201e-10);
	fConst31 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst21 + -2.2685481597417102e-18)) + -2.9947825773741901e-14)) + 1.4887872072289901e-11)) + 3.2188457163065099e-10);
	fConst32 = ((fConst0 * ((fConst0 * (-7.5508896970336498e-17 - fConst23)) + 9.9413390241601095e-13)) + 4.7252425873737703e-10);
	fConst33 = ((fConst0 * ((fConst0 * (fConst25 + -2.2652669091101002e-18)) + -2.9824017072480302e-14)) + 1.41757277621213e-11);
	fConst34 = ((fConst0 * ((fConst0 * (2.26022941050514e-18 - fConst27)) + 2.9795621290920602e-14)) + -1.4162921151748601e-11);
	fConst35 = ((fConst0 * ((fConst0 * (3.7944773555492801e-17 - fConst5)) + 4.9989662509652203e-13)) + -7.45459961503187e-10);
	fConst36 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst7 + -3.4150296199943501e-18)) + 1.4996898752895701e-14)) + 7.4545996150318701e-12)) + -4.8326344643595296e-10);
	fConst37 = ((fConst0 * ((fConst0 * ((fConst0 * (3.4028222396125701e-18 - fConst9)) + -1.49739128868709e-14)) + -7.4439360361449699e-12)) + 4.8282685744597599e-10);
	fConst38 = ((fConst0 * ((fConst0 * (fConst11 + -3.7754448485168298e-17)) + -4.9706695120800598e-13)) + 7.0878638810606497e-10);
	fConst39 = ((fConst0 * ((fConst0 * (3.3979003636651499e-18 - fConst13)) + -1.4912008536240202e-14)) + -7.08786388106065e-12);
	fConst40 = ((fConst0 * ((fConst0 * (fConst15 + -3.3903441157577201e-18)) + 1.4897810645460301e-14)) + 7.08146057587431e-12);
	fConst41 = (1.7057758246264699e-23 * fConst0);
	fConst42 = ((fConst0 * ((fConst0 * (fConst41 + -3.7944773555492801e-17)) + 4.9989662509652203e-13)) + -2.4848665383439599e-10);
	fConst43 = (5.1173274738793998e-25 * fConst0);
	fConst44 = ((fConst0 * ((fConst0 * ((fConst0 * (1.13834320666478e-18 - fConst43)) + -1.4996898752895701e-14)) + 7.4545996150318701e-12)) + -1.61087815478651e-10);
	fConst45 = (4.0379105919199901e-25 * fConst0);
	fConst46 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst45 + -1.1342740798708601e-18)) + 1.49739128868709e-14)) + -7.4439360361449699e-12)) + 1.60942285815325e-10);
	fConst47 = (1.4805110187378001e-23 * fConst0);
	fConst48 = ((fConst0 * ((fConst0 * (3.7754448485168298e-17 - fConst47)) + -4.9706695120800598e-13)) + 2.36262129368688e-10);
	fConst49 = (4.4415330562133998e-25 * fConst0);
	fConst50 = ((fConst0 * ((fConst0 * (fConst49 + -1.1326334545550501e-18)) + 1.4912008536240202e-14)) + -7.08786388106065e-12);
	fConst51 = (3.7731351393409399e-25 * fConst0);
	fConst52 = ((fConst0 * ((fConst0 * (1.13011470525257e-18 - fConst51)) + -1.4897810645460301e-14)) + 7.08146057587431e-12);
	fConst53 = ((fConst0 * ((fConst0 * (fConst41 + 3.7944773555492801e-17)) + 4.9989662509652203e-13)) + 2.4848665383439599e-10);
	fConst54 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst43 + 1.13834320666478e-18)) + 1.4996898752895701e-14)) + 7.4545996150318701e-12)) + 1.61087815478651e-10);
	fConst55 = ((fConst0 * ((fConst0 * ((fConst0 * (-1.1342740798708601e-18 - fConst45)) + -1.49739128868709e-14)) + -7.4439360361449699e-12)) + -1.60942285815325e-10);
	fConst56 = ((fConst0 * ((fConst0 * (-3.7754448485168298e-17 - fConst47)) + -4.9706695120800598e-13)) + -2.36262129368688e-10);
	fConst57 = ((fConst0 * ((fConst0 * (-1.1326334545550501e-18 - fConst49)) + -1.4912008536240202e-14)) + -7.08786388106065e-12);
	fConst58 = ((fConst0 * ((fConst0 * (fConst51 + 1.13011470525257e-18)) + 1.4897810645460301e-14)) + 7.08146057587431e-12);
	fConst59 = (1.2872026357467801e-19 * fConst0);
	fConst60 = (5.6866741028183699e-13 - fConst59);
	fConst61 = (3.8616079072403502e-21 * fConst0);
	fConst62 = (1.7060022308455101e-14 - fConst61);
	fConst63 = (3.3814963002306101e-21 * fConst0);
	fConst64 = (fConst63 + -1.6947743594398299e-16);
	fConst65 = (fConst59 + 5.6866741028183699e-13);
	fConst66 = (1.15848237217211e-20 * fConst0);
	fConst67 = (fConst66 + -1.7060022308455101e-14);
	fConst68 = (1.01444889006918e-20 * fConst0);
	fConst69 = (1.6947743594398299e-16 - fConst68);
	fConst70 = (2.5744052714935698e-19 * fConst0);
	fConst71 = (fConst70 + -1.1373348205636699e-12);
	fConst72 = (7.7232158144807004e-21 * fConst0);
	fConst73 = (-3.4120044616910201e-14 - fConst72);
	fConst74 = (6.7629926004612202e-21 * fConst0);
	fConst75 = (fConst74 + 3.3895487188796698e-16);
	fConst76 = (-1.1373348205636699e-12 - fConst70);
	fConst77 = (3.4120044616910201e-14 - fConst72);
	fConst78 = (fConst74 + -3.3895487188796698e-16);
	fConst79 = (fConst66 + 1.7060022308455101e-14);
	fConst80 = (-1.6947743594398299e-16 - fConst68);
	fConst81 = (-1.7060022308455101e-14 - fConst61);
	fConst82 = (fConst63 + 1.6947743594398299e-16);
	clear_state_f();
}

void Dsp::init_static(unsigned int sample_rate, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double fSlow0 = (0.0070000000000000062 * double(fVslider0));
	double fSlow1 = (0.0070000000000000062 * double(fVslider1));
	double fSlow2 = (0.0070000000000000062 * double(fVslider2));
	for (int i = 0; (i < count); i = (i + 1)) {
		fRec8[0] = (fSlow0 + (0.99299999999999999 * fRec8[1]));
		fRec10[0] = (fSlow1 + (0.99299999999999999 * fRec10[1]));
		fRec11[0] = (fSlow2 + (0.99299999999999999 * fRec11[1]));
		double fTemp0 = ((fConst0 * (fConst53 + ((fRec10[0] * (fConst54 + (fConst55 * fRec10[0]))) + (fRec11[0] * (fConst56 + (fConst0 * (fRec10[0] * (fConst57 + (fConst58 * fRec10[0]))))))))) + 5.3695938492883697e-09);
		fRec9[0] = (double(input0[i]) - ((((((fRec9[1] * ((fConst0 * (fConst6 + ((fRec10[0] * (fConst8 + (fConst10 * fRec10[0]))) + (fRec11[0] * (fConst12 + (fConst0 * (fRec10[0] * (fConst14 + (fConst16 * fRec10[0]))))))))) + 2.6847969246441801e-08)) + (fRec9[2] * ((fConst0 * (fConst18 + ((fRec10[0] * (fConst20 + (fConst22 * fRec10[0]))) + (fRec11[0] * (fConst24 + (fConst0 * (fRec10[0] * (fConst26 + (fConst28 * fRec10[0]))))))))) + 5.3695938492883701e-08))) + (fRec9[3] * ((fConst0 * (fConst29 + ((fRec10[0] * (fConst30 + (fConst31 * fRec10[0]))) + (fRec11[0] * (fConst32 + (fConst0 * (fRec10[0] * (fConst33 + (fConst34 * fRec10[0]))))))))) + 5.3695938492883701e-08))) + (fRec9[4] * ((fConst0 * (fConst35 + ((fRec10[0] * (fConst36 + (fConst37 * fRec10[0]))) + (fRec11[0] * (fConst38 + (fConst0 * (fRec10[0] * (fConst39 + (fConst40 * fRec10[0]))))))))) + 2.6847969246441801e-08))) + (fRec9[5] * ((fConst0 * (fConst42 + ((fRec10[0] * (fConst44 + (fConst46 * fRec10[0]))) + (fRec11[0] * (fConst48 + (fConst0 * (fRec10[0] * (fConst50 + (fConst52 * fRec10[0]))))))))) + 5.3695938492883697e-09))) / fTemp0));
		double fTemp1 = ((fRec8[0] * ((((((fRec9[0] * (fConst60 + (fConst0 * (fRec10[0] * (fConst62 + (fConst64 * fRec10[0])))))) + (fRec9[1] * (fConst65 + (fConst0 * (fRec10[0] * (fConst67 + (fConst69 * fRec10[0]))))))) + (fRec9[2] * (fConst71 + (fConst0 * (fRec10[0] * (fConst73 + (fConst75 * fRec10[0]))))))) + (fRec9[3] * (fConst76 + (fConst0 * (fRec10[0] * (fConst77 + (fConst78 * fRec10[0]))))))) + (fRec9[4] * (fConst60 + (fConst0 * (fRec10[0] * (fConst79 + (fConst80 * fRec10[0]))))))) + (fRec9[5] * (fConst65 + (fConst0 * (fRec10[0] * (fConst81 + (fConst82 * fRec10[0])))))))) / fTemp0);
		fVec0[0] = fTemp1;
		fRec7[0] = ((fConst4 * (fTemp1 + fVec0[1])) - (0.86056958506478287 * fRec7[1]));
		fRec6[0] = (fRec7[0] - ((1.8405051250752198 * fRec6[1]) + (0.86129424393186271 * fRec6[2])));
		double fTemp2 = ((1.8508996845035413 * fRec6[1]) + (0.92544984225177063 * (fRec6[0] + fRec6[2])));
		double fTemp3 = double(Ftrany(int(TRANY_TABLE_7199P_68k), double(((fTemp2 + (2700.0 * (fTemp2 / (double(Rtrany(int(TRANY_TABLE_7199P_68k), double(fRec5[1]))) + 100000.0)))) + -3.5719810000000001))));
		fRec5[0] = ((fTemp3 + (0.001322955925925926 * (double(Rtrany(int(TRANY_TABLE_7199P_68k), double(fTemp3))) + 100000.0))) + -250.0);
		fRec4[0] = (fConst2 * ((fConst3 * fRec4[1]) + (0.025000000000000001 * (fRec5[0] - fRec5[1]))));
		fRec3[0] = ((0.93028479253239138 * (fRec4[0] + fRec4[1])) - (0.86056958506478287 * fRec3[1]));
		fRec2[0] = (fRec3[0] - ((1.8405051250752198 * fRec2[1]) + (0.86129424393186271 * fRec2[2])));
		double fTemp4 = ((1.8508996845035413 * fRec2[1]) + (0.92544984225177063 * (fRec2[0] + fRec2[2])));
		double fTemp5 = double(Ftrany(int(TRANY_TABLE_7199P_68k), double(((fTemp4 + (2700.0 * (fTemp4 / (double(Rtrany(int(TRANY_TABLE_7199P_68k), double(fRec1[1]))) + 100000.0)))) + -3.5719810000000001))));
		fRec1[0] = ((fTemp5 + (0.001322955925925926 * (double(Rtrany(int(TRANY_TABLE_7199P_68k), double(fTemp5))) + 100000.0))) + -250.0);
		fRec0[0] = (fConst2 * ((fConst3 * fRec0[1]) + (0.025000000000000001 * (fRec1[0] - fRec1[1]))));
		output0[i] = FAUSTFLOAT(fRec0[0]);
		fRec8[1] = fRec8[0];
		fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		for (int j0 = 5; (j0 > 0); j0 = (j0 - 1)) {
			fRec9[j0] = fRec9[(j0 - 1)];
		}
		fVec0[1] = fVec0[0];
		fRec7[1] = fRec7[0];
		fRec6[2] = fRec6[1];
		fRec6[1] = fRec6[0];
		fRec5[1] = fRec5[0];
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
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
	reg.registerFloatVar("axface.Attack",N_("Attack"),"S","",&fVslider1, 0.5, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("axface.Level",N_("Level"),"S","",&fVslider0, 0.5, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("axface.Smooth",N_("Smooth"),"S","",&fVslider2, 0.5, 0.0, 1.0, 0.01, 0);
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
