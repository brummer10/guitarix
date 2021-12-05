// generated from file '../src/plugins/coverd.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

namespace pluginlib {
namespace coverd {

class Dsp: public PluginDef {
private:
	int fSampleRate;
	FAUSTFLOAT fVslider0;
	double fConst0;
	FAUSTFLOAT fVslider1;
	double fRec1[2];
	double fConst2;
	double fConst4;
	double fConst6;
	double fConst8;
	double fConst9;
	double fConst10;
	double fConst11;
	double fConst12;
	double fConst14;
	double fConst16;
	double fConst17;
	double fConst18;
	double fRec2[6];
	double fConst20;
	double fConst22;
	double fConst24;
	double fConst26;
	double fConst28;
	double fConst30;
	double fConst31;
	double fConst32;
	double fConst33;
	double fConst34;
	double fConst35;
	double fConst36;
	double fConst37;
	FAUSTFLOAT fVslider2;
	double fRec3[2];
	double fConst39;
	double fConst41;
	double fConst43;
	FAUSTFLOAT fVslider3;
	double fRec4[2];
	double fConst45;
	double fConst47;
	double fConst49;
	double fConst51;
	double fConst53;
	double fConst55;
	double fConst57;
	double fConst59;
	double fConst61;
	double fConst63;
	double fConst65;
	double fConst67;
	double fConst69;
	double fConst71;
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
	double fConst93;
	double fConst95;
	double fConst97;
	double fConst99;
	double fConst101;
	double fConst103;
	double fConst105;
	double fConst107;
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
	double fRec0[6];
	double fConst120;
	double fConst122;
	double fConst124;
	double fConst126;
	double fConst128;
	double fConst130;
	double fConst132;
	double fConst133;
	double fConst135;
	double fConst137;
	double fConst139;
	double fConst141;
	double fConst143;
	double fConst145;
	double fConst147;
	double fConst148;
	double fConst150;
	double fConst152;
	double fConst154;
	double fConst156;
	double fConst158;
	double fConst160;
	double fConst162;
	double fConst163;
	double fConst164;
	double fConst165;
	double fConst166;
	double fConst167;
	double fConst168;
	double fConst169;
	double fConst170;
	double fConst171;
	double fConst172;
	double fConst173;
	double fConst174;
	double fConst175;
	double fConst176;
	double fConst177;
	double fConst178;
	double fConst179;
	double fConst180;
	double fConst181;
	double fConst182;
	double fConst183;
	double fConst184;
	double fConst185;
	double fConst186;
	double fConst187;

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
	id = "coverd";
	name = N_("C Overdrive");
	groups = 0;
	description = N_("Colorsound Overdrive"); // description (tooltip)
	category = N_("Distortion");       // category
	shortname = N_("C Overdrive");     // shortname
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec1[l0] = 0.0;
	for (int l1 = 0; (l1 < 6); l1 = (l1 + 1)) fRec2[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec3[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fRec4[l3] = 0.0;
	for (int l4 = 0; (l4 < 6); l4 = (l4 + 1)) fRec0[l4] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = (1.3935652083025701e-23 * fConst0);
	fConst2 = (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (-6.1172363286913801e-19 - fConst1)) + -1.2527269516161201e-17)) + 3.1313786604836201e-16)) + 4.2805640104643799e-15));
	double fConst3 = (1.2039412336362801e-23 * fConst0);
	fConst4 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst3 + 5.5001126756994203e-19)) + 1.0884037880131e-17)) + -2.1766309285101399e-16)) + -1.57013189894617e-15)) + -2.3308303074176399e-28);
	double fConst5 = (2.7871304166051302e-23 * fConst0);
	fConst6 = (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst5 + 4.0781575524609202e-19)) + -2.50545390323223e-17)) + -6.2627573209672402e-16)) + 2.8537093403095901e-15));
	double fConst7 = (2.4078824672725701e-23 * fConst0);
	fConst8 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (-3.66674178379961e-19 - fConst7)) + 2.1768075760262099e-17)) + 4.35326185702027e-16)) + -1.0467545992974399e-15)) + -4.6616606148352897e-28);
	fConst9 = (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (4.0781575524609202e-19 - fConst5)) + 2.50545390323223e-17)) + -6.2627573209672402e-16)) + -2.8537093403095901e-15));
	fConst10 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst7 + -3.66674178379961e-19)) + -2.1768075760262099e-17)) + 4.35326185702027e-16)) + 1.0467545992974399e-15)) + -4.6616606148352897e-28);
	fConst11 = (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst1 + -6.1172363286913801e-19)) + 1.2527269516161201e-17)) + 3.1313786604836201e-16)) + -4.2805640104643799e-15));
	fConst12 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (5.5001126756994203e-19 - fConst3)) + -1.0884037880131e-17)) + -2.1766309285101399e-16)) + 1.57013189894617e-15)) + -2.3308303074176399e-28);
	double fConst13 = (2.7871304166051298e-24 * fConst0);
	fConst14 = (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (2.0390787762304601e-19 - fConst13)) + -1.2527269516161201e-17)) + 3.1313786604836201e-16)) + -1.4268546701547899e-15));
	double fConst15 = (2.40788246727257e-24 * fConst0);
	fConst16 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst15 + -1.83337089189981e-19)) + 1.0884037880131e-17)) + -2.1766309285101399e-16)) + 5.2337729964872204e-16)) + -4.6616606148352897e-29);
	fConst17 = (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst13 + 2.0390787762304601e-19)) + 1.2527269516161201e-17)) + 3.1313786604836201e-16)) + 1.4268546701547899e-15));
	fConst18 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (-1.83337089189981e-19 - fConst15)) + -1.0884037880131e-17)) + -2.1766309285101399e-16)) + -5.2337729964872204e-16)) + -4.6616606148352897e-29);
	double fConst19 = (7.4270205864411701e-27 * fConst0);
	fConst20 = ((fConst0 * ((fConst0 * ((fConst0 * (7.8988913319958496e-19 - fConst19)) + 3.4887541215073902e-17)) + 5.0459837350811799e-17)) + 6.5717299047663398e-18);
	double fConst21 = (3.9764719032260303e-27 * fConst0);
	fConst22 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst21 + -4.9588063178614504e-19)) + -2.1228287579292599e-17)) + -2.9572784571466399e-18)) + -2.6340134583647699e-31);
	double fConst23 = (3.7135102932205898e-26 * fConst0);
	fConst24 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst23 + -2.3696673995987601e-18)) + -3.4887541215073902e-17)) + 5.0459837350811799e-17)) + 1.9715189714299001e-17);
	double fConst25 = (1.98823595161302e-26 * fConst0);
	fConst26 = ((fConst0 * ((fConst0 * ((fConst0 * (1.48764189535843e-18 - fConst25)) + 2.1228287579292599e-17)) + -2.9572784571466399e-18)) + -7.9020403750943e-31);
	double fConst27 = (7.4270205864411703e-26 * fConst0);
	fConst28 = ((fConst0 * ((fConst0 * ((fConst0 * (1.5797782663991699e-18 - fConst27)) + -6.9775082430147902e-17)) + -1.0091967470162401e-16)) + 1.31434598095327e-17);
	double fConst29 = (3.9764719032260302e-26 * fConst0);
	fConst30 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst29 + -9.9176126357228893e-19)) + 4.2456575158585297e-17)) + 5.9145569142932797e-18)) + -5.2680269167295398e-31);
	fConst31 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst27 + 1.5797782663991699e-18)) + 6.9775082430147902e-17)) + -1.0091967470162401e-16)) + -1.31434598095327e-17);
	fConst32 = ((fConst0 * ((fConst0 * ((fConst0 * (-9.9176126357228893e-19 - fConst29)) + -4.2456575158585297e-17)) + 5.9145569142932797e-18)) + 5.2680269167295398e-31);
	fConst33 = ((fConst0 * ((fConst0 * ((fConst0 * (-2.3696673995987601e-18 - fConst23)) + 3.4887541215073902e-17)) + 5.0459837350811799e-17)) + -1.9715189714299001e-17);
	fConst34 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst25 + 1.48764189535843e-18)) + -2.1228287579292599e-17)) + -2.9572784571466399e-18)) + 7.9020403750943e-31);
	fConst35 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst19 + 7.8988913319958496e-19)) + -3.4887541215073902e-17)) + 5.0459837350811799e-17)) + -6.5717299047663398e-18);
	fConst36 = ((fConst0 * ((fConst0 * ((fConst0 * (-4.9588063178614504e-19 - fConst21)) + 2.1228287579292599e-17)) + -2.9572784571466399e-18)) + 2.6340134583647699e-31);
	fConst37 = mydsp_faustpower2_f(fConst0);
	double fConst38 = (3.5474588667410602e-23 * fConst0);
	fConst39 = (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (-2.43110421538011e-20 - fConst38)) + -2.5587299331515599e-18)) + 1.6778555476929999e-16)) + 2.5428356096907501e-16));
	double fConst40 = (3.3629084026700199e-23 * fConst0);
	fConst41 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst40 + 1.3247598004229199e-20)) + 7.4737153078838796e-19)) + -9.5797093535955601e-17)) + 5.3660171004202004e-28)) + 2.2567506272856599e-42);
	double fConst42 = (1.61159196619408e-23 * fConst0);
	fConst43 = ((fConst0 * ((fConst0 * ((fConst0 * (-6.9746931237572006e-21 - fConst42)) + -5.4419601638721403e-19)) + 9.6602972982548806e-17)) + 1.35817220395143e-14);
	double fConst44 = (1.11898736808855e-23 * fConst0);
	fConst45 = ((fConst0 * ((fConst0 * (fConst44 + -5.2454712430393197e-22)) + -1.74198245202729e-20)) + 6.9746947775131901e-35);
	double fConst46 = (5.5791036766132897e-24 * fConst0);
	fConst47 = ((fConst0 * ((fConst0 * (-9.7063067310167796e-22 - fConst46)) + -8.5311710434333001e-22)) + 3.3904474795950297e-20);
	double fConst48 = (2.7471371814015202e-23 * fConst0);
	fConst49 = ((fConst0 * ((fConst0 * (9.43033341552612e-23 - fConst48)) + -3.39044747960198e-22)) + -7.6054643763389698e-34);
	double fConst50 = (4.53805402033319e-24 * fConst0);
	fConst51 = ((fConst0 * ((fConst0 * (fConst50 + 9.4191462908095105e-22)) + 1.8007723957611699e-20)) + -1.6952237397974799e-20);
	double fConst52 = (3.86104353299586e-23 * fConst0);
	fConst53 = ((fConst0 * ((fConst0 * (fConst52 + 1.8179090443363001e-21)) + 3.3904474795876898e-22)) + 7.6054643763389997e-34);
	double fConst54 = (5.56953175797167e-24 * fConst0);
	fConst55 = ((fConst0 * ((fConst0 * (-9.5610618924578009e-22 - fConst54)) + 7.1410882010216502e-34)) + -1.80540050182853e-48);
	double fConst56 = (7.0949177334821299e-23 * fConst0);
	fConst57 = (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst56 + 1.62073614358674e-20)) + -5.1174598663031098e-18)) + -3.35571109538599e-16)) + 1.6952237397938301e-16));
	double fConst58 = (6.7258168053400399e-23 * fConst0);
	fConst59 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (-8.8317320028194406e-21 - fConst58)) + 1.49474306157678e-18)) + 1.9159418707191101e-16)) + 3.5773447336134699e-28)) + 4.5135012545713299e-42);
	double fConst60 = (3.2231839323881501e-23 * fConst0);
	fConst61 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst60 + 4.64979541583813e-21)) + -1.08839203277443e-18)) + -1.9320594596509801e-16)) + 9.0544813596761893e-15);
	double fConst62 = (2.23797473617709e-23 * fConst0);
	fConst63 = ((fConst0 * ((fConst0 * (3.4969808286928801e-22 - fConst62)) + -3.4839649040545799e-20)) + -1.3949389555026399e-34);
	double fConst64 = (1.11582073532266e-23 * fConst0);
	fConst65 = ((fConst0 * ((fConst0 * (fConst64 + 6.4708711540111902e-22)) + -1.70623420868666e-21)) + -6.7808949591900498e-20);
	double fConst66 = (5.4942743628030499e-23 * fConst0);
	fConst67 = ((fConst0 * ((fConst0 * (fConst66 + -6.2868889436840796e-23)) + -6.7808949592039497e-22)) + 1.52109287526779e-33);
	double fConst68 = (9.0761080406663903e-24 * fConst0);
	fConst69 = ((fConst0 * ((fConst0 * (-6.2794308605396699e-22 - fConst68)) + 3.6015447915223398e-20)) + 3.3904474795949701e-20);
	double fConst70 = (7.7220870659917106e-23 * fConst0);
	fConst71 = ((fConst0 * ((fConst0 * (-1.21193936289087e-21 - fConst70)) + 6.7808949591753899e-22)) + -1.5210928752677999e-33);
	double fConst72 = (1.11390635159433e-23 * fConst0);
	fConst73 = ((fConst0 * ((fConst0 * (fConst72 + 6.3740412616385301e-22)) + 1.42821764020433e-33)) + 3.61080100365706e-48);
	fConst74 = (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (1.62073614358674e-20 - fConst56)) + 5.1174598663031098e-18)) + -3.35571109538599e-16)) + -1.6952237397938301e-16));
	fConst75 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst58 + -8.8317320028194406e-21)) + -1.49474306157678e-18)) + 1.9159418707191101e-16)) + -3.5773447336134699e-28)) + 4.5135012545713299e-42);
	fConst76 = ((fConst0 * ((fConst0 * ((fConst0 * (4.64979541583813e-21 - fConst60)) + 1.08839203277443e-18)) + -1.9320594596509801e-16)) + -9.0544813596761893e-15);
	fConst77 = ((fConst0 * ((fConst0 * (fConst62 + 3.4969808286928801e-22)) + 3.4839649040545799e-20)) + -1.3949389555026399e-34);
	fConst78 = ((fConst0 * ((fConst0 * (6.4708711540111902e-22 - fConst64)) + 1.70623420868666e-21)) + -6.7808949591900498e-20);
	fConst79 = ((fConst0 * ((fConst0 * (-6.2868889436840796e-23 - fConst66)) + 6.7808949592039497e-22)) + 1.52109287526779e-33);
	fConst80 = ((fConst0 * ((fConst0 * (fConst68 + -6.2794308605396699e-22)) + -3.6015447915223398e-20)) + 3.3904474795949701e-20);
	fConst81 = ((fConst0 * ((fConst0 * (fConst70 + -1.21193936289087e-21)) + -6.7808949591753899e-22)) + -1.5210928752677999e-33);
	fConst82 = ((fConst0 * ((fConst0 * (6.3740412616385301e-22 - fConst72)) + -1.42821764020433e-33)) + 3.61080100365706e-48);
	fConst83 = (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst38 + -2.43110421538011e-20)) + 2.5587299331515599e-18)) + 1.6778555476929999e-16)) + -2.5428356096907501e-16));
	fConst84 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (1.3247598004229199e-20 - fConst40)) + -7.4737153078838796e-19)) + -9.5797093535955601e-17)) + -5.3660171004202004e-28)) + 2.2567506272856599e-42);
	fConst85 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst42 + -6.9746931237572006e-21)) + 5.4419601638721403e-19)) + 9.6602972982548806e-17)) + -1.35817220395143e-14);
	fConst86 = ((fConst0 * ((fConst0 * (-5.2454712430393197e-22 - fConst44)) + 1.74198245202729e-20)) + 6.9746947775131901e-35);
	fConst87 = ((fConst0 * ((fConst0 * (fConst46 + -9.7063067310167796e-22)) + 8.5311710434333001e-22)) + 3.3904474795950297e-20);
	fConst88 = ((fConst0 * ((fConst0 * (fConst48 + 9.43033341552612e-23)) + 3.39044747960198e-22)) + -7.6054643763389698e-34);
	fConst89 = ((fConst0 * ((fConst0 * (9.4191462908095105e-22 - fConst50)) + -1.8007723957611699e-20)) + -1.6952237397974799e-20);
	fConst90 = ((fConst0 * ((fConst0 * (1.8179090443363001e-21 - fConst52)) + -3.3904474795876898e-22)) + 7.6054643763389997e-34);
	fConst91 = ((fConst0 * ((fConst0 * (fConst54 + -9.5610618924578009e-22)) + -7.1410882010216502e-34)) + -1.80540050182853e-48);
	double fConst92 = (7.0949177334821307e-24 * fConst0);
	fConst93 = (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (8.1036807179336998e-21 - fConst92)) + -2.5587299331515599e-18)) + 1.6778555476929999e-16)) + -8.4761186989691604e-17));
	double fConst94 = (6.7258168053400396e-24 * fConst0);
	fConst95 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst94 + -4.4158660014097203e-21)) + 7.4737153078838796e-19)) + -9.5797093535955601e-17)) + -1.78867236680673e-28)) + 4.5135012545713298e-43);
	double fConst96 = (3.2231839323881499e-24 * fConst0);
	fConst97 = ((fConst0 * ((fConst0 * ((fConst0 * (2.3248977079190699e-21 - fConst96)) + -5.4419601638721403e-19)) + 9.6602972982548806e-17)) + -4.5272406798381002e-15);
	double fConst98 = (2.23797473617709e-24 * fConst0);
	fConst99 = ((fConst0 * ((fConst0 * (fConst98 + 1.7484904143464401e-22)) + -1.74198245202729e-20)) + 6.9746947775131901e-35);
	double fConst100 = (1.11582073532266e-24 * fConst0);
	fConst101 = ((fConst0 * ((fConst0 * (3.2354355770055899e-22 - fConst100)) + -8.5311710434333001e-22)) + 3.3904474795950297e-20);
	double fConst102 = (5.4942743628030497e-24 * fConst0);
	fConst103 = ((fConst0 * ((fConst0 * (-3.1434444718420398e-23 - fConst102)) + -3.39044747960198e-22)) + -7.6054643763389698e-34);
	double fConst104 = (9.0761080406663907e-25 * fConst0);
	fConst105 = ((fConst0 * ((fConst0 * (fConst104 + -3.1397154302698401e-22)) + 1.8007723957611699e-20)) + -1.6952237397974799e-20);
	double fConst106 = (7.7220870659917094e-24 * fConst0);
	fConst107 = ((fConst0 * ((fConst0 * (fConst106 + -6.0596968144543303e-22)) + 3.3904474795876898e-22)) + 7.6054643763389997e-34);
	double fConst108 = (1.11390635159433e-24 * fConst0);
	fConst109 = ((fConst0 * ((fConst0 * (3.1870206308192698e-22 - fConst108)) + 7.1410882010216502e-34)) + -1.80540050182853e-48);
	fConst110 = (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst92 + 8.1036807179336998e-21)) + 2.5587299331515599e-18)) + 1.6778555476929999e-16)) + 8.4761186989691604e-17));
	fConst111 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (-4.4158660014097203e-21 - fConst94)) + -7.4737153078838796e-19)) + -9.5797093535955601e-17)) + 1.78867236680673e-28)) + 4.5135012545713298e-43);
	fConst112 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst96 + 2.3248977079190699e-21)) + 5.4419601638721403e-19)) + 9.6602972982548806e-17)) + 4.5272406798381002e-15);
	fConst113 = ((fConst0 * ((fConst0 * (1.7484904143464401e-22 - fConst98)) + 1.74198245202729e-20)) + 6.9746947775131901e-35);
	fConst114 = ((fConst0 * ((fConst0 * (fConst100 + 3.2354355770055899e-22)) + 8.5311710434333001e-22)) + 3.3904474795950297e-20);
	fConst115 = ((fConst0 * ((fConst0 * (fConst102 + -3.1434444718420398e-23)) + 3.39044747960198e-22)) + -7.6054643763389698e-34);
	fConst116 = ((fConst0 * ((fConst0 * (-3.1397154302698401e-22 - fConst104)) + -1.8007723957611699e-20)) + -1.6952237397974799e-20);
	fConst117 = ((fConst0 * ((fConst0 * (-6.0596968144543303e-22 - fConst106)) + -3.3904474795876898e-22)) + 7.6054643763389997e-34);
	fConst118 = ((fConst0 * ((fConst0 * (fConst108 + 3.1870206308192698e-22)) + -7.1410882010216502e-34)) + -1.80540050182853e-48);
	double fConst119 = (3.8335982187147998e-25 * fConst0);
	fConst120 = ((fConst0 * ((fConst0 * ((fConst0 * (-5.4225162236968602e-21 - fConst119)) + -1.9578646983364802e-18)) + -7.3999388068597105e-17)) + -2.8521353999220098e-18);
	double fConst121 = (3.7005812000625201e-25 * fConst0);
	fConst122 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst121 + 3.8495592865380798e-22)) + 1.6627319745875501e-18)) + 7.0086493617754001e-17)) + 1.7699227103214199e-31);
	double fConst123 = (2.0800094665695601e-27 * fConst0);
	fConst124 = (fConst0 * ((fConst0 * ((fConst0 * (3.29838842203039e-21 - fConst123)) + 1.4018439577710801e-19)) + 3.53984542064284e-34));
	double fConst125 = (1.0025039931634e-23 * fConst0);
	fConst126 = ((fConst0 * (-4.2469290531386701e-22 - fConst125)) + -6.0836639392632101e-36);
	double fConst127 = (1.91438372832372e-27 * fConst0);
	fConst128 = ((fConst0 * (fConst127 + -9.2889473512725402e-24)) + -2.2817083199364499e-23);
	double fConst129 = (6.5881304000686802e-24 * fConst0);
	fConst130 = ((fConst0 * (fConst129 + 2.8034597447101602e-22)) + 7.07969084128568e-37);
	double fConst131 = (6.8889957144195502e-24 * fConst0);
	fConst132 = ((fConst0 * (fConst131 + 2.9592942046395499e-22)) + 1.1408541599688001e-23);
	fConst133 = ((fConst0 * (-2.8034597447101602e-22 - fConst129)) + -7.07969084128568e-37);
	double fConst134 = (1.9167991093574001e-24 * fConst0);
	fConst135 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst134 + 1.6267548671090599e-20)) + 1.9578646983364802e-18)) + -7.3999388068597105e-17)) + -8.5564061997660207e-18);
	double fConst136 = (1.85029060003126e-24 * fConst0);
	fConst137 = ((fConst0 * ((fConst0 * ((fConst0 * (-1.15486778596142e-21 - fConst136)) + -1.6627319745875501e-18)) + 7.0086493617754001e-17)) + 5.3097681309642603e-31);
	double fConst138 = (1.04000473328478e-26 * fConst0);
	fConst139 = (fConst0 * ((fConst0 * ((fConst0 * (fConst138 + -9.8951652660911702e-21)) + -1.4018439577710801e-19)) + 3.53984542064284e-34));
	double fConst140 = (5.0125199658170002e-23 * fConst0);
	fConst141 = ((fConst0 * (fConst140 + 1.2740787159415999e-21)) + 6.0836639392632101e-36);
	double fConst142 = (9.57191864161859e-27 * fConst0);
	fConst143 = ((fConst0 * (2.7866842053817597e-23 - fConst142)) + 2.2817083199364499e-23);
	double fConst144 = (3.2940652000343399e-23 * fConst0);
	fConst145 = ((fConst0 * (-8.4103792341304904e-22 - fConst144)) + -7.07969084128568e-37);
	double fConst146 = (3.4444978572097798e-23 * fConst0);
	fConst147 = ((fConst0 * (-8.8778826139186502e-22 - fConst146)) + -1.1408541599688001e-23);
	fConst148 = ((fConst0 * (fConst144 + 8.4103792341304904e-22)) + 7.07969084128568e-37);
	double fConst149 = (3.8335982187148002e-24 * fConst0);
	fConst150 = ((fConst0 * ((fConst0 * ((fConst0 * (-1.0845032447393699e-20 - fConst149)) + 3.9157293966729503e-18)) + 1.4799877613719401e-16)) + -5.7042707998440097e-18);
	double fConst151 = (3.7005812000625201e-24 * fConst0);
	fConst152 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst151 + 7.6991185730761596e-22)) + -3.3254639491750901e-18)) + -1.40172987235508e-16)) + 3.5398454206428399e-31);
	double fConst153 = (2.0800094665695601e-26 * fConst0);
	fConst154 = (fConst0 * ((fConst0 * ((fConst0 * (6.5967768440607799e-21 - fConst153)) + -2.8036879155421602e-19)) + -7.0796908412856799e-34));
	double fConst155 = (1.0025039931634e-22 * fConst0);
	fConst156 = ((fConst0 * (-8.4938581062773309e-22 - fConst155)) + 1.2167327878526399e-35);
	double fConst157 = (1.91438372832372e-26 * fConst0);
	fConst158 = ((fConst0 * (fConst157 + -1.8577894702545101e-23)) + 4.5634166398729098e-23);
	double fConst159 = (6.5881304000686798e-23 * fConst0);
	fConst160 = ((fConst0 * (fConst159 + 5.6069194894203204e-22)) + -1.41593816825714e-36);
	double fConst161 = (6.8889957144195502e-23 * fConst0);
	fConst162 = ((fConst0 * (fConst161 + 5.9185884092790998e-22)) + -2.2817083199376101e-23);
	fConst163 = ((fConst0 * (-5.6069194894203204e-22 - fConst159)) + 1.41593816825714e-36);
	fConst164 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst149 + -1.0845032447393699e-20)) + -3.9157293966729503e-18)) + 1.4799877613719401e-16)) + 5.7042707998440097e-18);
	fConst165 = ((fConst0 * ((fConst0 * ((fConst0 * (7.6991185730761596e-22 - fConst151)) + 3.3254639491750901e-18)) + -1.40172987235508e-16)) + -3.5398454206428399e-31);
	fConst166 = (fConst0 * ((fConst0 * ((fConst0 * (fConst153 + 6.5967768440607799e-21)) + 2.8036879155421602e-19)) + -7.0796908412856799e-34));
	fConst167 = ((fConst0 * (fConst155 + -8.4938581062773309e-22)) + -1.2167327878526399e-35);
	fConst168 = ((fConst0 * (-1.8577894702545101e-23 - fConst157)) + -4.5634166398729098e-23);
	fConst169 = ((fConst0 * (5.6069194894203204e-22 - fConst159)) + 1.41593816825714e-36);
	fConst170 = ((fConst0 * (5.9185884092790998e-22 - fConst161)) + 2.2817083199376101e-23);
	fConst171 = ((fConst0 * (fConst159 + -5.6069194894203204e-22)) + -1.41593816825714e-36);
	fConst172 = ((fConst0 * ((fConst0 * ((fConst0 * (1.6267548671090599e-20 - fConst134)) + -1.9578646983364802e-18)) + -7.3999388068597105e-17)) + 8.5564061997660207e-18);
	fConst173 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst136 + -1.15486778596142e-21)) + 1.6627319745875501e-18)) + 7.0086493617754001e-17)) + -5.3097681309642603e-31);
	fConst174 = (fConst0 * ((fConst0 * ((fConst0 * (-9.8951652660911702e-21 - fConst138)) + 1.4018439577710801e-19)) + 3.53984542064284e-34));
	fConst175 = ((fConst0 * (1.2740787159415999e-21 - fConst140)) + -6.0836639392632101e-36);
	fConst176 = ((fConst0 * (fConst142 + 2.7866842053817597e-23)) + -2.2817083199364499e-23);
	fConst177 = ((fConst0 * (fConst144 + -8.4103792341304904e-22)) + 7.07969084128568e-37);
	fConst178 = ((fConst0 * (fConst146 + -8.8778826139186502e-22)) + 1.1408541599688001e-23);
	fConst179 = ((fConst0 * (8.4103792341304904e-22 - fConst144)) + -7.07969084128568e-37);
	fConst180 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst119 + -5.4225162236968602e-21)) + 1.9578646983364802e-18)) + -7.3999388068597105e-17)) + 2.8521353999220098e-18);
	fConst181 = ((fConst0 * ((fConst0 * ((fConst0 * (3.8495592865380798e-22 - fConst121)) + -1.6627319745875501e-18)) + 7.0086493617754001e-17)) + -1.7699227103214199e-31);
	fConst182 = (fConst0 * ((fConst0 * ((fConst0 * (fConst123 + 3.29838842203039e-21)) + -1.4018439577710801e-19)) + 3.53984542064284e-34));
	fConst183 = ((fConst0 * (fConst125 + -4.2469290531386701e-22)) + 6.0836639392632101e-36);
	fConst184 = ((fConst0 * (-9.2889473512725402e-24 - fConst127)) + 2.2817083199364499e-23);
	fConst185 = ((fConst0 * (2.8034597447101602e-22 - fConst129)) + -7.07969084128568e-37);
	fConst186 = ((fConst0 * (2.9592942046395499e-22 - fConst131)) + -1.1408541599688001e-23);
	fConst187 = ((fConst0 * (fConst129 + -2.8034597447101602e-22)) + 7.07969084128568e-37);
	clear_state_f();
}

void Dsp::init_static(unsigned int sample_rate, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double fSlow0 = (0.01 * double(fVslider0));
	double fSlow1 = (1.0 - fSlow0);
	double fSlow2 = (0.004073836948085289 * (std::exp(double(fVslider1)) + -1.0));
	double fSlow3 = (0.0070000000000000062 * (1.0 - double(fVslider2)));
	double fSlow4 = (0.0070000000000000062 * double(fVslider3));
	for (int i0 = 0; (i0 < count); i0 = (i0 + 1)) {
		double fTemp0 = double(input0[i0]);
		fRec1[0] = (fSlow2 + (0.99299999999999999 * fRec1[1]));
		double fTemp1 = (fConst17 + ((fConst18 * fRec1[0]) + 1.16306066588601e-15));
		fRec2[0] = ((fSlow0 * fTemp0) - ((((((fRec2[1] * (fConst2 + ((fConst4 * fRec1[0]) + 5.8153033294300802e-15))) + (fRec2[2] * (fConst6 + ((fConst8 * fRec1[0]) + 1.16306066588602e-14)))) + (fRec2[3] * (fConst9 + ((fConst10 * fRec1[0]) + 1.16306066588602e-14)))) + (fRec2[4] * (fConst11 + ((fConst12 * fRec1[0]) + 5.8153033294300802e-15)))) + (fRec2[5] * (fConst14 + ((fConst16 * fRec1[0]) + 1.16306066588601e-15)))) / fTemp1));
		double fTemp2 = ((((((fRec2[0] * (fConst20 + (fConst22 * fRec1[0]))) + (fRec2[1] * (fConst24 + (fConst26 * fRec1[0])))) + (fRec2[2] * (fConst28 + (fConst30 * fRec1[0])))) + (fRec2[3] * (fConst31 + (fConst32 * fRec1[0])))) + (fRec2[4] * (fConst33 + (fConst34 * fRec1[0])))) + (fRec2[5] * (fConst35 + (fConst36 * fRec1[0]))));
		double fTemp3 = std::fabs((fConst0 * (fTemp2 / fTemp1)));
		fRec3[0] = (fSlow3 + (0.99299999999999999 * fRec3[1]));
		fRec4[0] = (fSlow4 + (0.99299999999999999 * fRec4[1]));
		double fTemp4 = (((fRec3[0] * (fConst110 + ((fConst111 * fRec3[0]) + -1.9013660940847501e-28))) + (fConst0 * (fConst112 + (fConst0 * (fRec4[0] * (fConst113 + ((fRec3[0] * (fConst114 + (fConst115 * fRec3[0]))) + (fRec4[0] * (fConst116 + (fRec3[0] * (fConst117 + (fConst118 * fRec3[0])))))))))))) + 4.2380593494937101e-15);
		fRec0[0] = ((fConst0 * (((fRec1[0] * fTemp2) * (fTemp3 + 0.5)) / (fTemp1 * ((fConst37 * (mydsp_faustpower2_f(fTemp2) / mydsp_faustpower2_f(fTemp1))) + (1.0 - (0.5 * fTemp3)))))) - ((((((fRec0[1] * (((fRec3[0] * (fConst39 + ((fConst41 * fRec3[0]) + -9.5068304704237505e-28))) + (fConst0 * (fConst43 + (fConst0 * (fRec4[0] * (fConst45 + ((fRec3[0] * (fConst47 + (fConst49 * fRec3[0]))) + (fRec4[0] * (fConst51 + (fRec3[0] * (fConst53 + (fConst55 * fRec3[0])))))))))))) + 2.1190296747468499e-14)) + (fRec0[2] * (((fRec3[0] * (fConst57 + ((fConst59 * fRec3[0]) + -1.9013660940847501e-27))) + (fConst0 * (fConst61 + (fConst0 * (fRec4[0] * (fConst63 + ((fRec3[0] * (fConst65 + (fConst67 * fRec3[0]))) + (fRec4[0] * (fConst69 + (fRec3[0] * (fConst71 + (fConst73 * fRec3[0])))))))))))) + 4.2380593494937099e-14))) + (fRec0[3] * (((fRec3[0] * (fConst74 + ((fConst75 * fRec3[0]) + -1.9013660940847501e-27))) + (fConst0 * (fConst76 + (fConst0 * (fRec4[0] * (fConst77 + ((fRec3[0] * (fConst78 + (fConst79 * fRec3[0]))) + (fRec4[0] * (fConst80 + (fRec3[0] * (fConst81 + (fConst82 * fRec3[0])))))))))))) + 4.2380593494937099e-14))) + (fRec0[4] * (((fRec3[0] * (fConst83 + ((fConst84 * fRec3[0]) + -9.5068304704237505e-28))) + (fConst0 * (fConst85 + (fConst0 * (fRec4[0] * (fConst86 + ((fRec3[0] * (fConst87 + (fConst88 * fRec3[0]))) + (fRec4[0] * (fConst89 + (fRec3[0] * (fConst90 + (fConst91 * fRec3[0])))))))))))) + 2.1190296747468499e-14))) + (fRec0[5] * (((fRec3[0] * (fConst93 + ((fConst95 * fRec3[0]) + -1.9013660940847501e-28))) + (fConst0 * (fConst97 + (fConst0 * (fRec4[0] * (fConst99 + ((fRec3[0] * (fConst101 + (fConst103 * fRec3[0]))) + (fRec4[0] * (fConst105 + (fRec3[0] * (fConst107 + (fConst109 * fRec3[0])))))))))))) + 4.2380593494937101e-15))) / fTemp4));
		output0[i0] = FAUSTFLOAT(((fSlow1 * fTemp0) + (fConst0 * (((((((fRec0[0] * (fConst120 + ((fRec3[0] * (fConst122 + (fConst124 * fRec3[0]))) + (fConst37 * (fRec4[0] * (fConst126 + ((fRec3[0] * (fConst128 + (fConst130 * fRec3[0]))) + (fRec4[0] * (fConst132 + (fConst133 * fRec3[0])))))))))) + (fRec0[1] * (fConst135 + ((fRec3[0] * (fConst137 + (fConst139 * fRec3[0]))) + (fConst37 * (fRec4[0] * (fConst141 + ((fRec3[0] * (fConst143 + (fConst145 * fRec3[0]))) + (fRec4[0] * (fConst147 + (fConst148 * fRec3[0]))))))))))) + (fRec0[2] * (fConst150 + ((fRec3[0] * (fConst152 + (fConst154 * fRec3[0]))) + (fConst37 * (fRec4[0] * (fConst156 + ((fRec3[0] * (fConst158 + (fConst160 * fRec3[0]))) + (fRec4[0] * (fConst162 + (fConst163 * fRec3[0]))))))))))) + (fRec0[3] * (fConst164 + ((fRec3[0] * (fConst165 + (fConst166 * fRec3[0]))) + (fConst37 * (fRec4[0] * (fConst167 + ((fRec3[0] * (fConst168 + (fConst169 * fRec3[0]))) + (fRec4[0] * (fConst170 + (fConst171 * fRec3[0]))))))))))) + (fRec0[4] * (fConst172 + ((fRec3[0] * (fConst173 + (fConst174 * fRec3[0]))) + (fConst37 * (fRec4[0] * (fConst175 + ((fRec3[0] * (fConst176 + (fConst177 * fRec3[0]))) + (fRec4[0] * (fConst178 + (fConst179 * fRec3[0]))))))))))) + (fRec0[5] * (fConst180 + ((fRec3[0] * (fConst181 + (fConst182 * fRec3[0]))) + (fConst37 * (fRec4[0] * (fConst183 + ((fRec3[0] * (fConst184 + (fConst185 * fRec3[0]))) + (fRec4[0] * (fConst186 + (fConst187 * fRec3[0]))))))))))) / fTemp4))));
		fRec1[1] = fRec1[0];
		for (int j0 = 5; (j0 > 0); j0 = (j0 - 1)) {
			fRec2[j0] = fRec2[(j0 - 1)];
		}
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		for (int j1 = 5; (j1 > 0); j1 = (j1 - 1)) {
			fRec0[j1] = fRec0[(j1 - 1)];
		}
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerFloatVar("coverd.Bass",N_("Bass"),"S","",&fVslider2, 0.5, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("coverd.Treble",N_("Treble"),"S","",&fVslider3, 0.5, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("coverd.Volume",N_("Volume"),"S","",&fVslider1, 0.5, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("coverd.wet_dry",N_("Wet/Dry"),"S",N_("percentage of processed signal in output signal"),&fVslider0, 100.0, 0.0, 100.0, 1.0, 0);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

const char *Dsp::glade_def = "\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<!-- Generated with glade 3.38.2 -->\n\
<interface>\n\
  <requires lib=\"gtk+\" version=\"3.20\"/>\n\
  <requires lib=\"gxwidgets\" version=\"0.0\"/>\n\
  <object class=\"GtkWindow\" id=\"window1\">\n\
    <property name=\"can-focus\">False</property>\n\
    <child>\n\
      <object class=\"GtkBox\" id=\"vbox1\">\n\
        <property name=\"visible\">True</property>\n\
        <property name=\"can-focus\">False</property>\n\
        <property name=\"orientation\">vertical</property>\n\
        <child>\n\
          <object class=\"GtkBox\" id=\"rackbox\">\n\
            <property name=\"visible\">True</property>\n\
            <property name=\"can-focus\">False</property>\n\
            <property name=\"spacing\">4</property>\n\
            <child>\n\
              <object class=\"GtkBox\" id=\"hbox1\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can-focus\">False</property>\n\
                <property name=\"spacing\">10</property>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox2\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can-focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label1:rack_label\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can-focus\">False</property>\n\
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
                        <property name=\"can-focus\">True</property>\n\
                        <property name=\"receives-default\">True</property>\n\
                        <property name=\"var_id\">coverd.Bass</property>\n\
                        <property name=\"label-ref\">label1:rack_label</property>\n\
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
                    <property name=\"can-focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label2:rack_label\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can-focus\">False</property>\n\
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
                        <property name=\"can-focus\">True</property>\n\
                        <property name=\"receives-default\">True</property>\n\
                        <property name=\"var_id\">coverd.Treble</property>\n\
                        <property name=\"label-ref\">label2:rack_label</property>\n\
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
                    <property name=\"can-focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label3:rack_label\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can-focus\">False</property>\n\
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
                        <property name=\"can-focus\">True</property>\n\
                        <property name=\"receives-default\">True</property>\n\
                        <property name=\"var_id\">coverd.Volume</property>\n\
                        <property name=\"label-ref\">label3:rack_label</property>\n\
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
                  <object class=\"GtkBox\" id=\"vbox5\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can-focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label4:rack_label\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can-focus\">False</property>\n\
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
                        <property name=\"can-focus\">True</property>\n\
                        <property name=\"receives-default\">True</property>\n\
                        <property name=\"var_id\">coverd.wet_dry</property>\n\
                        <property name=\"label-ref\">label4:rack_label</property>\n\
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
              </object>\n\
              <packing>\n\
                <property name=\"expand\">True</property>\n\
                <property name=\"fill\">False</property>\n\
                <property name=\"pack-type\">end</property>\n\
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
            <property name=\"can-focus\">False</property>\n\
            <property name=\"spacing\">4</property>\n\
            <child>\n\
              <object class=\"GxHSlider\" id=\"gxhslider1\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can-focus\">True</property>\n\
                <property name=\"receives-default\">True</property>\n\
                <property name=\"round-digits\">0</property>\n\
                <property name=\"var_id\">coverd.Volume</property>\n\
                <property name=\"show-value\">False</property>\n\
                <property name=\"value-position\">right</property>\n\
                <property name=\"value-xalign\">0.52</property>\n\
                <property name=\"label-ref\">label0:rack_label</property>\n\
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
                <property name=\"can-focus\">False</property>\n\
                <property name=\"label\" translatable=\"yes\">Volume</property>\n\
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
#define PARAM(p) ("coverd" "." p)

b.openHorizontalhideBox("");
    b.create_master_slider(PARAM("Volume"), "Volume");
b.closeBox();
b.openHorizontalBox("");

    b.create_small_rackknobr(PARAM("Volume"), "Volume");
    b.create_small_rackknobr(PARAM("Bass"), "Bass");
    b.create_small_rackknobr(PARAM("Treble"), "Treble");
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

} // end namespace coverd
} // end namespace pluginlib
