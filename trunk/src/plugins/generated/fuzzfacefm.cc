// generated from file '../src/plugins/fuzzfacefm.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"
#include "trany.h"

namespace pluginlib {
namespace fuzzfacefm {

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
	double 	fConst9;
	double 	fConst10;
	FAUSTFLOAT 	fslider0;
	double 	fRec8[2];
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
	FAUSTFLOAT 	fslider1;
	double 	fRec9[2];
	FAUSTFLOAT 	fslider2;
	double 	fRec10[2];
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
	FAUSTFLOAT 	fslider3;
	double 	fRec11[2];
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
	double 	fRec12[4];
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
	double 	fVec0[2];
	double 	fConst103;
	double 	fConst104;
	double 	fConst105;
	double 	fRec7[2];
	double 	fRec6[3];
	double 	fConst106;
	double 	fConst107;
	double 	fConst108;
	double 	fConst109;
	double 	fRec13[2];
	double 	fRec5[3];
	double 	fConst110;
	double 	fConst111;
	double 	fConst112;
	double 	fConst113;
	double 	fConst114;
	double 	fRec4[2];
	double 	fConst115;
	double 	fRec3[2];
	double 	fRec2[3];
	double 	fRec14[2];
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
	id = "fuzzfacefm";
	name = N_("Fuzz Face Fuller");
	groups = 0;
	description = N_("Micke Fuller Fuzz Face simulation"); // description (tooltip)
	category = N_("Fuzz");       // category
	shortname = N_("Fuzz Face FM");     // shortname
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
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<4; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
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
	fConst7 = (5.60496524842164e-17 * fConst6);
	fConst8 = (1.69410806769336e-10 + (fConst6 * (1.63110208134281e-12 + fConst7)));
	fConst9 = (2.51786247207522e-17 * fConst6);
	fConst10 = ((fConst6 * (0 - (1.61641996632585e-12 + fConst9))) - 1.6091784998802e-10);
	fConst11 = (7.09868387007524e-14 * fConst6);
	fConst12 = (7.07787491781686e-12 + fConst11);
	fConst13 = (7.09616600760317e-14 * fConst6);
	fConst14 = (0 - (7.07536443616085e-12 + fConst13));
	fConst15 = (1.41557498356337e-16 * fConst6);
	fConst16 = (7.17715343346006e-56 - fConst15);
	fConst17 = (1.41507288723217e-16 * fConst6);
	fConst18 = (fConst17 - 7.60754167271764e-56);
	fConst19 = (5.02096331201311e-20 * fConst6);
	fConst20 = ((fConst6 * (3.21835699976039e-15 + fConst19)) - 1.53335572595511e-54);
	fConst21 = (7.14615106636066e-14 * fConst6);
	fConst22 = ((fConst6 * (0 - (7.44787041826973e-12 + fConst21))) - 3.21721587173494e-11);
	fConst23 = (7.14054610111223e-14 * fConst6);
	fConst24 = (3.21607474370948e-11 + (fConst6 * (7.44216743501989e-12 + fConst23)));
	fConst25 = (1.1177069911304e-19 * fConst6);
	fConst26 = ((fConst6 * (0 - (3.24149709132582e-15 + fConst25))) - 1.46288954534563e-14);
	fConst27 = (1.42504059392599e-16 * fConst6);
	fConst28 = ((fConst6 * (6.43443174346988e-16 + fConst27)) - 3.26234246975457e-55);
	fConst29 = (1.42392288693486e-16 * fConst6);
	fConst30 = (3.45797348759893e-55 + (fConst6 * (0 - (6.43214948741896e-16 + fConst29))));
	fConst31 = (2.0681037922594e-13 * fConst6);
	fConst32 = (4.74739615579661e-12 - fConst31);
	fConst33 = (1.65448303380752e-13 * fConst6);
	fConst34 = (fConst33 - 3.79791692463729e-12);
	fConst35 = (1.12549866245409e-13 * fConst6);
	fConst36 = (2.58361695553557e-12 - fConst35);
	fConst37 = (1.40687332806762e-13 * fConst6);
	fConst38 = (fConst37 - 3.22952119441946e-12);
	fConst39 = ((fConst6 * (1.63110208134281e-12 - fConst7)) - 1.69410806769336e-10);
	fConst40 = (1.6091784998802e-10 + (fConst6 * (fConst9 - 1.61641996632585e-12)));
	fConst41 = (7.07787491781686e-12 - fConst11);
	fConst42 = (fConst13 - 7.07536443616085e-12);
	fConst43 = (7.17715343346006e-56 + fConst15);
	fConst44 = (0 - (7.60754167271764e-56 + fConst17));
	fConst45 = (1.53335572595511e-54 + (fConst6 * (3.21835699976039e-15 - fConst19)));
	fConst46 = (3.21721587173494e-11 + (fConst6 * (fConst21 - 7.44787041826973e-12)));
	fConst47 = ((fConst6 * (7.44216743501989e-12 - fConst23)) - 3.21607474370948e-11);
	fConst48 = (1.46288954534563e-14 + (fConst6 * (fConst25 - 3.24149709132582e-15)));
	fConst49 = (3.26234246975457e-55 + (fConst6 * (6.43443174346988e-16 - fConst27)));
	fConst50 = ((fConst6 * (fConst29 - 6.43214948741896e-16)) - 3.45797348759893e-55);
	fConst51 = (7.55358741622564e-17 * fConst6);
	fConst52 = (1.6091784998802e-10 + (fConst6 * (1.61641996632585e-12 - fConst51)));
	fConst53 = (2.12960516102257e-13 * fConst6);
	fConst54 = (fConst53 - 7.07787491781686e-12);
	fConst55 = (2.12884980228095e-13 * fConst6);
	fConst56 = (7.07536443616085e-12 - fConst55);
	fConst57 = (4.24672495069012e-16 * fConst6);
	fConst58 = (0 - (7.17715343346006e-56 + fConst57));
	fConst59 = (4.24521866169651e-16 * fConst6);
	fConst60 = (7.60754167271764e-56 + fConst59);
	fConst61 = (1.50628899360393e-19 * fConst6);
	fConst62 = (1.53335572595511e-54 + (fConst6 * (fConst61 - 3.21835699976039e-15)));
	fConst63 = (2.1438453199082e-13 * fConst6);
	fConst64 = (3.21721587173494e-11 + (fConst6 * (7.44787041826973e-12 - fConst63)));
	fConst65 = (2.14216383033367e-13 * fConst6);
	fConst66 = ((fConst6 * (fConst65 - 7.44216743501989e-12)) - 3.21607474370948e-11);
	fConst67 = (1.68148957452649e-16 * fConst6);
	fConst68 = ((fConst6 * (fConst67 - 1.63110208134281e-12)) - 1.69410806769336e-10);
	fConst69 = (3.35312097339121e-19 * fConst6);
	fConst70 = (1.46288954534563e-14 + (fConst6 * (3.24149709132582e-15 - fConst69)));
	fConst71 = (4.27512178177797e-16 * fConst6);
	fConst72 = (3.26234246975457e-55 + (fConst6 * (fConst71 - 6.43443174346988e-16)));
	fConst73 = (4.27176866080457e-16 * fConst6);
	fConst74 = ((fConst6 * (6.43214948741896e-16 - fConst73)) - 3.45797348759893e-55);
	fConst75 = (1.69410806769336e-10 + (fConst6 * (0 - (1.63110208134281e-12 + fConst67))));
	fConst76 = ((fConst6 * (1.61641996632585e-12 + fConst51)) - 1.6091784998802e-10);
	fConst77 = (0 - (7.07787491781686e-12 + fConst53));
	fConst78 = (7.07536443616085e-12 + fConst55);
	fConst79 = (fConst57 - 7.17715343346006e-56);
	fConst80 = (7.60754167271764e-56 - fConst59);
	fConst81 = ((fConst6 * (0 - (3.21835699976039e-15 + fConst61))) - 1.53335572595511e-54);
	fConst82 = ((fConst6 * (7.44787041826973e-12 + fConst63)) - 3.21721587173494e-11);
	fConst83 = (3.21607474370948e-11 + (fConst6 * (0 - (7.44216743501989e-12 + fConst65))));
	fConst84 = ((fConst6 * (3.24149709132582e-15 + fConst69)) - 1.46288954534563e-14);
	fConst85 = ((fConst6 * (0 - (6.43443174346988e-16 + fConst71))) - 3.26234246975457e-55);
	fConst86 = (3.45797348759893e-55 + (fConst6 * (6.43214948741896e-16 + fConst73)));
	fConst87 = (4.96344910142255e-13 * fConst6);
	fConst88 = (3.79791692463729e-12 - fConst87);
	fConst89 = (4.22061998420285e-13 * fConst6);
	fConst90 = (3.22952119441946e-12 - fConst89);
	fConst91 = (3.37649598736228e-13 * fConst6);
	fConst92 = (fConst91 - 2.58361695553557e-12);
	fConst93 = (6.20431137677819e-13 * fConst6);
	fConst94 = (fConst93 - 4.74739615579661e-12);
	fConst95 = (0 - (4.74739615579661e-12 + fConst93));
	fConst96 = (3.79791692463729e-12 + fConst87);
	fConst97 = (3.22952119441946e-12 + fConst89);
	fConst98 = (0 - (2.58361695553557e-12 + fConst91));
	fConst99 = (4.74739615579661e-12 + fConst31);
	fConst100 = (0 - (3.79791692463729e-12 + fConst33));
	fConst101 = (0 - (3.22952119441946e-12 + fConst37));
	fConst102 = (2.58361695553557e-12 + fConst35);
	fConst103 = (1 + fConst3);
	fConst104 = (faustpower<2>(fConst6) / fConst103);
	fConst105 = (0 - ((1 - fConst3) / fConst103));
	fConst106 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst107 = (1 + fConst106);
	fConst108 = (0.027 / fConst107);
	fConst109 = (0 - ((1 - fConst106) / fConst107));
	fConst110 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst111 = (0 - fConst110);
	fConst112 = (1 + fConst110);
	fConst113 = (0.025 / fConst112);
	fConst114 = (0 - ((1 - fConst110) / fConst112));
	fConst115 = (1.0 / fConst103);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlow0 = (0.007000000000000006 * (1 - double(fslider0)));
	double 	fSlow1 = (0.007000000000000006 * (1 - double(fslider1)));
	double 	fSlow2 = (0.007000000000000006 * double(fslider2));
	double 	fSlow3 = (0.007000000000000006 * (1 - double(fslider3)));
	for (int i=0; i<count; i++) {
		fRec8[0] = ((0.993 * fRec8[1]) + fSlow0);
		fRec9[0] = ((0.993 * fRec9[1]) + fSlow1);
		fRec10[0] = ((0.993 * fRec10[1]) + fSlow2);
		double fTemp0 = (7.31444772672817e-10 + ((fRec9[0] * (6.96979875434139e-54 + (fConst6 * ((fRec8[0] * (fConst30 + (fConst28 * fRec8[0]))) + fConst26)))) + (fConst6 * (((fRec8[0] * (fConst24 + (fConst22 * fRec8[0]))) + (fRec10[0] * (((fRec9[0] * (fConst20 + (fConst6 * (fRec8[0] * (fConst18 + (fConst16 * fRec8[0])))))) + (fConst6 * (fRec8[0] * (fConst14 + (fConst12 * fRec8[0]))))) + fConst10))) + fConst8))));
		fRec11[0] = ((0.993 * fRec11[1]) + fSlow3);
		double fTemp1 = (1.63788262077463e-13 * fRec11[0]);
		double fTemp2 = (1.66004130328897e-15 * fRec11[0]);
		double fTemp3 = (1.12927979815576e-15 * fRec11[0]);
		double fTemp4 = (1.11420586447254e-13 * fRec11[0]);
		fRec12[0] = ((double)input0[i] - ((((fRec12[1] * (2.19433431801845e-09 + ((fRec9[0] * (2.09093962630242e-53 + (fConst6 * ((fRec8[0] * (fConst86 + (fConst85 * fRec8[0]))) + fConst84)))) + (fConst6 * (((fRec8[0] * (fConst83 + (fConst82 * fRec8[0]))) + (fRec10[0] * (((fRec9[0] * (fConst81 + (fConst6 * (fRec8[0] * (fConst80 + (fConst79 * fRec8[0])))))) + (fConst6 * (fRec8[0] * (fConst78 + (fConst77 * fRec8[0]))))) + fConst76))) + fConst75))))) + (fRec12[2] * (2.19433431801845e-09 + ((fRec9[0] * (2.09093962630242e-53 + (fConst6 * ((fRec8[0] * (fConst74 + (fConst72 * fRec8[0]))) + fConst70)))) + (fConst6 * (fConst68 + ((fRec8[0] * (fConst66 + (fConst64 * fRec8[0]))) + (fRec10[0] * (((fRec9[0] * (fConst62 + (fConst6 * (fRec8[0] * (fConst60 + (fConst58 * fRec8[0])))))) + (fConst6 * (fRec8[0] * (fConst56 + (fConst54 * fRec8[0]))))) + fConst52))))))))) + (fRec12[3] * (7.31444772672817e-10 + ((fRec9[0] * (6.96979875434139e-54 + (fConst6 * ((fRec8[0] * (fConst50 + (fConst49 * fRec8[0]))) + fConst48)))) + (fConst6 * (((fRec8[0] * (fConst47 + (fConst46 * fRec8[0]))) + (fRec10[0] * (((fRec9[0] * (fConst45 + (fConst6 * (fRec8[0] * (fConst44 + (fConst43 * fRec8[0])))))) + (fConst6 * (fRec8[0] * (fConst42 + (fConst41 * fRec8[0]))))) + fConst40))) + fConst39)))))) / fTemp0));
		double fTemp5 = (4.98012390986691e-15 * fRec11[0]);
		double fTemp6 = (4.91364786232388e-13 * fRec11[0]);
		double fTemp7 = (3.34261759341761e-13 * fRec11[0]);
		double fTemp8 = (3.38783939446729e-15 * fRec11[0]);
		double fTemp9 = (((((fRec12[0] * ((((fRec9[0] * (((fConst6 * (fRec8[0] * (1.39275733059067e-13 + ((fRec8[0] * (1.4115997476947e-15 + (0 - fTemp3))) - fTemp4)))) + (fConst102 * fRec11[0])) + fConst101)) + (fConst6 * (fRec8[0] * ((fTemp1 + (fRec8[0] * (fTemp2 - 2.07505162911121e-15))) - 2.04735327596828e-13)))) + (fConst100 * fRec11[0])) + fConst99)) + (fRec12[1] * ((((fRec9[0] * (((fConst6 * (fRec8[0] * ((fTemp7 + (fRec8[0] * (fTemp8 - 4.23479924308411e-15))) - 4.17827199177201e-13))) + (fConst98 * fRec11[0])) + fConst97)) + (fConst6 * (fRec8[0] * (6.14205982790485e-13 + ((fRec8[0] * (6.22515488733364e-15 + (0 - fTemp5))) - fTemp6))))) + (fConst96 * fRec11[0])) + fConst95))) + (fRec12[2] * (fConst94 + (((fRec9[0] * (((fConst6 * (fRec8[0] * (4.17827199177201e-13 + ((fRec8[0] * (4.23479924308411e-15 + (0 - fTemp8))) - fTemp7)))) + (fConst92 * fRec11[0])) + fConst90)) + (fConst6 * (fRec8[0] * ((fTemp6 + (fRec8[0] * (fTemp5 - 6.22515488733364e-15))) - 6.14205982790485e-13)))) + (fConst88 * fRec11[0]))))) + (fRec12[3] * ((((fRec9[0] * (fConst38 + ((fConst6 * (fRec8[0] * ((fTemp4 + (fRec8[0] * (fTemp3 - 1.4115997476947e-15))) - 1.39275733059067e-13))) + (fConst36 * fRec11[0])))) + (fConst6 * (fRec8[0] * (2.04735327596828e-13 + ((fRec8[0] * (2.07505162911121e-15 + (0 - fTemp2))) - fTemp1))))) + (fConst34 * fRec11[0])) + fConst32))) / fTemp0);
		fVec0[0] = fTemp9;
		fRec7[0] = ((fConst105 * fRec7[1]) + (fConst104 * (fVec0[0] + fVec0[1])));
		fRec6[0] = (fRec7[0] - (fConst5 * ((fConst4 * fRec6[2]) + (fConst2 * fRec6[1]))));
		fRec13[0] = ((fConst109 * fRec13[1]) + (fConst108 * (fRec5[1] + fRec5[2])));
		fRec5[0] = (Ftrany(TRANY_TABLE_KT88_68k, ((fRec13[0] + (fConst5 * (fRec6[2] + (fRec6[0] + (2 * fRec6[1]))))) - 5.562895)) - 43.96685185185183);
		fRec4[0] = ((fConst114 * fRec4[1]) + (fConst113 * ((fConst110 * fRec5[0]) + (fConst111 * fRec5[1]))));
		fRec3[0] = ((fConst105 * fRec3[1]) + (fConst115 * (fRec4[0] + fRec4[1])));
		fRec2[0] = (fRec3[0] - (fConst5 * ((fConst4 * fRec2[2]) + (fConst2 * fRec2[1]))));
		fRec14[0] = ((fConst109 * fRec14[1]) + (fConst108 * (fRec1[1] + fRec1[2])));
		fRec1[0] = (Ftrany(TRANY_TABLE_KT88_68k, ((fRec14[0] + (fConst5 * (fRec2[2] + (fRec2[0] + (2 * fRec2[1]))))) - 5.562895)) - 43.96685185185183);
		fRec0[0] = ((fConst114 * fRec0[1]) + (fConst113 * ((fConst110 * fRec1[0]) + (fConst111 * fRec1[1]))));
		output0[i] = (FAUSTFLOAT)fRec0[0];
		// post processing
		fRec0[1] = fRec0[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec14[1] = fRec14[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec13[1] = fRec13[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec7[1] = fRec7[0];
		fVec0[1] = fVec0[0];
		for (int i=3; i>0; i--) fRec12[i] = fRec12[i-1];
		fRec11[1] = fRec11[0];
		fRec10[1] = fRec10[0];
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
	reg.registerVar("fuzzfacefm.Drive",N_("Drive"),"S","",&fslider1, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("fuzzfacefm.Fuzz",N_("Fuzz"),"S","",&fslider0, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("fuzzfacefm.Input",N_("Input"),"S","",&fslider2, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("fuzzfacefm.Level",N_("Level"),"S","",&fslider3, 0.5, 0.0, 1.0, 0.01);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("fuzzfacefm" "." p)

b.openHorizontalhideBox("");
    b.create_master_slider(PARAM("Fuzz"), N_("Fuzz"));
b.closeBox();
b.openHorizontalBox("");

    b.create_small_rackknobr(PARAM("Input"), N_("Input"));

    b.create_small_rackknobr(PARAM("Drive"), N_("Drive"));

    b.create_small_rackknobr(PARAM("Fuzz"), N_("Fuzz"));

    b.create_small_rackknobr(PARAM("Level"), N_("Level"));
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

} // end namespace fuzzfacefm
} // end namespace pluginlib
