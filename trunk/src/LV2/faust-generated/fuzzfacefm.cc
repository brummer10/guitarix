// generated from file '../src/LV2/faust/fuzzfacefm.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "trany.h"

namespace fuzzfacefm {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec8[2];
	double fConst0;
	double fConst2;
	double fConst4;
	double fConst5;
	double fConst7;
	double fConst9;
	double fConst11;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec9[2];
	double fConst13;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec10[2];
	double fConst15;
	double fConst17;
	double fConst19;
	double fConst21;
	double fConst23;
	double fConst25;
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fRec11[2];
	double fConst27;
	double fConst29;
	double fConst30;
	double fConst32;
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
	double fConst48;
	double fConst50;
	double fConst52;
	double fConst54;
	double fConst56;
	double fConst58;
	double fConst60;
	double fConst62;
	double fConst64;
	double fConst66;
	double fConst68;
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
	double fRec12[4];
	double fConst84;
	double fConst86;
	double fConst88;
	double fConst90;
	double fConst91;
	double fConst92;
	double fConst93;
	double fConst94;
	double fConst95;
	double fConst96;
	double fConst97;
	double fConst98;
	double fVec0[2];
	double fRec7[2];
	double fRec6[3];
	double fRec5[2];
	double fConst100;
	double fConst101;
	double fRec4[2];
	double fRec3[2];
	double fRec2[3];
	double fRec1[2];
	double fRec0[2];

	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(uint32_t sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(uint32_t sample_rate, PluginLV2*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginLV2() {
	version = PLUGINLV2_VERSION;
	id = "fuzzfacefm";
	name = N_("Fuzz Face Fuller");
	mono_audio = compute_static;
	stereo_audio = 0;
	set_samplerate = init_static;
	activate_plugin = 0;
	connect_ports = connect_static;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec8[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec9[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec10[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec11[l3] = 0.0;
	for (int l4 = 0; l4 < 4; l4 = l4 + 1) fRec12[l4] = 0.0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fVec0[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fRec7[l6] = 0.0;
	for (int l7 = 0; l7 < 3; l7 = l7 + 1) fRec6[l7] = 0.0;
	for (int l8 = 0; l8 < 2; l8 = l8 + 1) fRec5[l8] = 0.0;
	for (int l9 = 0; l9 < 2; l9 = l9 + 1) fRec4[l9] = 0.0;
	for (int l10 = 0; l10 < 2; l10 = l10 + 1) fRec3[l10] = 0.0;
	for (int l11 = 0; l11 < 3; l11 = l11 + 1) fRec2[l11] = 0.0;
	for (int l12 = 0; l12 < 2; l12 = l12 + 1) fRec1[l12] = 0.0;
	for (int l13 = 0; l13 < 2; l13 = l13 + 1) fRec0[l13] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = 7.09868387007524e-14 * fConst0;
	fConst2 = fConst1 + 7.07787491781686e-12;
	double fConst3 = 7.09616600760317e-14 * fConst0;
	fConst4 = -7.07536443616085e-12 - fConst3;
	fConst5 = mydsp_faustpower2_f(fConst0);
	double fConst6 = 1.41557498356337e-16 * fConst0;
	fConst7 = 7.17715343346006e-56 - fConst6;
	double fConst8 = 1.41507288723217e-16 * fConst0;
	fConst9 = fConst8 + -7.60754167271764e-56;
	double fConst10 = 5.02096331201311e-20 * fConst0;
	fConst11 = fConst0 * (fConst0 * (fConst10 + 3.21835699976039e-15) + -1.53335572595511e-54);
	double fConst12 = 2.51786247207522e-17 * fConst0;
	fConst13 = fConst0 * (fConst0 * (-1.61641996632585e-12 - fConst12) + -1.6091784998802e-10);
	double fConst14 = 1.42504059392599e-16 * fConst0;
	fConst15 = fConst0 * (fConst14 + 6.43443174346988e-16) + -3.26234246975457e-55;
	double fConst16 = 1.42392288693486e-16 * fConst0;
	fConst17 = fConst0 * (-6.43214948741896e-16 - fConst16) + 3.45797348759893e-55;
	double fConst18 = 1.1177069911304e-19 * fConst0;
	fConst19 = fConst0 * (-3.24149709132582e-15 - fConst18) + -1.46288954534563e-14;
	double fConst20 = 7.14615106636066e-14 * fConst0;
	fConst21 = fConst0 * (-7.44787041826973e-12 - fConst20) + -3.21721587173494e-11;
	double fConst22 = 7.14054610111223e-14 * fConst0;
	fConst23 = fConst0 * (fConst22 + 7.44216743501989e-12) + 3.21607474370948e-11;
	double fConst24 = 5.60496524842164e-17 * fConst0;
	fConst25 = fConst0 * (fConst24 + 1.63110208134281e-12) + 1.69410806769336e-10;
	double fConst26 = 1.65448303380752e-13 * fConst0;
	fConst27 = fConst26 + -3.79791692463729e-12;
	double fConst28 = 2.0681037922594e-13 * fConst0;
	fConst29 = 4.74739615579661e-12 - fConst28;
	fConst30 = mydsp_faustpower3_f(fConst0);
	double fConst31 = 1.12549866245409e-13 * fConst0;
	fConst32 = 2.58361695553557e-12 - fConst31;
	double fConst33 = 1.40687332806762e-13 * fConst0;
	fConst34 = fConst33 + -3.22952119441946e-12;
	fConst35 = 7.07787491781686e-12 - fConst1;
	fConst36 = fConst3 + -7.07536443616085e-12;
	fConst37 = fConst6 + 7.17715343346006e-56;
	fConst38 = -7.60754167271764e-56 - fConst8;
	fConst39 = fConst0 * (fConst0 * (3.21835699976039e-15 - fConst10) + 1.53335572595511e-54);
	fConst40 = fConst0 * (fConst0 * (fConst12 + -1.61641996632585e-12) + 1.6091784998802e-10);
	fConst41 = fConst0 * (6.43443174346988e-16 - fConst14) + 3.26234246975457e-55;
	fConst42 = fConst0 * (fConst16 + -6.43214948741896e-16) + -3.45797348759893e-55;
	fConst43 = fConst0 * (fConst18 + -3.24149709132582e-15) + 1.46288954534563e-14;
	fConst44 = fConst0 * (fConst20 + -7.44787041826973e-12) + 3.21721587173494e-11;
	fConst45 = fConst0 * (7.44216743501989e-12 - fConst22) + -3.21607474370948e-11;
	fConst46 = fConst0 * (1.63110208134281e-12 - fConst24) + -1.69410806769336e-10;
	double fConst47 = 2.12960516102257e-13 * fConst0;
	fConst48 = fConst47 + -7.07787491781686e-12;
	double fConst49 = 2.12884980228095e-13 * fConst0;
	fConst50 = 7.07536443616085e-12 - fConst49;
	double fConst51 = 4.24672495069012e-16 * fConst0;
	fConst52 = -7.17715343346006e-56 - fConst51;
	double fConst53 = 4.24521866169651e-16 * fConst0;
	fConst54 = fConst53 + 7.60754167271764e-56;
	double fConst55 = 1.50628899360393e-19 * fConst0;
	fConst56 = fConst0 * (fConst0 * (fConst55 + -3.21835699976039e-15) + 1.53335572595511e-54);
	double fConst57 = 7.55358741622564e-17 * fConst0;
	fConst58 = fConst0 * (fConst0 * (1.61641996632585e-12 - fConst57) + 1.6091784998802e-10);
	double fConst59 = 4.27512178177797e-16 * fConst0;
	fConst60 = fConst0 * (fConst59 + -6.43443174346988e-16) + 3.26234246975457e-55;
	double fConst61 = 4.27176866080457e-16 * fConst0;
	fConst62 = fConst0 * (6.43214948741896e-16 - fConst61) + -3.45797348759893e-55;
	double fConst63 = 3.35312097339121e-19 * fConst0;
	fConst64 = fConst0 * (3.24149709132582e-15 - fConst63) + 1.46288954534563e-14;
	double fConst65 = 2.1438453199082e-13 * fConst0;
	fConst66 = fConst0 * (7.44787041826973e-12 - fConst65) + 3.21721587173494e-11;
	double fConst67 = 2.14216383033367e-13 * fConst0;
	fConst68 = fConst0 * (fConst67 + -7.44216743501989e-12) + -3.21607474370948e-11;
	double fConst69 = 1.68148957452649e-16 * fConst0;
	fConst70 = fConst0 * (fConst69 + -1.63110208134281e-12) + -1.69410806769336e-10;
	fConst71 = -7.07787491781686e-12 - fConst47;
	fConst72 = fConst49 + 7.07536443616085e-12;
	fConst73 = fConst51 + -7.17715343346006e-56;
	fConst74 = 7.60754167271764e-56 - fConst53;
	fConst75 = fConst0 * (fConst0 * (-3.21835699976039e-15 - fConst55) + -1.53335572595511e-54);
	fConst76 = fConst0 * (fConst0 * (fConst57 + 1.61641996632585e-12) + -1.6091784998802e-10);
	fConst77 = fConst0 * (-6.43443174346988e-16 - fConst59) + -3.26234246975457e-55;
	fConst78 = fConst0 * (fConst61 + 6.43214948741896e-16) + 3.45797348759893e-55;
	fConst79 = fConst0 * (fConst63 + 3.24149709132582e-15) + -1.46288954534563e-14;
	fConst80 = fConst0 * (fConst65 + 7.44787041826973e-12) + -3.21721587173494e-11;
	fConst81 = fConst0 * (-7.44216743501989e-12 - fConst67) + 3.21607474370948e-11;
	fConst82 = fConst0 * (-1.63110208134281e-12 - fConst69) + 1.69410806769336e-10;
	double fConst83 = 4.96344910142255e-13 * fConst0;
	fConst84 = 3.79791692463729e-12 - fConst83;
	double fConst85 = 6.20431137677819e-13 * fConst0;
	fConst86 = fConst85 + -4.74739615579661e-12;
	double fConst87 = 3.37649598736228e-13 * fConst0;
	fConst88 = fConst87 + -2.58361695553557e-12;
	double fConst89 = 4.22061998420285e-13 * fConst0;
	fConst90 = 3.22952119441946e-12 - fConst89;
	fConst91 = fConst83 + 3.79791692463729e-12;
	fConst92 = -4.74739615579661e-12 - fConst85;
	fConst93 = -2.58361695553557e-12 - fConst87;
	fConst94 = fConst89 + 3.22952119441946e-12;
	fConst95 = -3.79791692463729e-12 - fConst26;
	fConst96 = fConst28 + 4.74739615579661e-12;
	fConst97 = fConst31 + 2.58361695553557e-12;
	fConst98 = -3.22952119441946e-12 - fConst33;
	double fConst99 = 3.141592653589793 / fConst0;
	fConst100 = 1.0 - fConst99;
	fConst101 = 1.0 / (fConst99 + 1.0);
	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fVslider0 (*fVslider0_)
#define fVslider1 (*fVslider1_)
#define fVslider2 (*fVslider2_)
#define fVslider3 (*fVslider3_)
	double fSlow0 = 0.007000000000000006 * (1.0 - double(fVslider0));
	double fSlow1 = 0.007000000000000006 * (1.0 - double(fVslider1));
	double fSlow2 = 0.007000000000000006 * double(fVslider2);
	double fSlow3 = 0.007000000000000006 * (1.0 - double(fVslider3));
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec8[0] = fSlow0 + 0.993 * fRec8[1];
		fRec9[0] = fSlow1 + 0.993 * fRec9[1];
		fRec10[0] = fSlow2 + 0.993 * fRec10[1];
		double fTemp0 = fConst0 * (fConst25 + fRec8[0] * (fConst23 + fConst21 * fRec8[0])) + fRec9[0] * (fConst0 * (fConst19 + fRec8[0] * (fConst17 + fConst15 * fRec8[0])) + 6.96979875434139e-54) + fRec10[0] * (fConst13 + fRec9[0] * (fConst11 + fConst5 * fRec8[0] * (fConst9 + fConst7 * fRec8[0])) + fConst5 * fRec8[0] * (fConst4 + fConst2 * fRec8[0])) + 7.31444772672817e-10;
		fRec11[0] = fSlow3 + 0.993 * fRec11[1];
		double fTemp1 = 1.63788262077463e-13 * fRec11[0];
		double fTemp2 = 1.66004130328897e-15 * fRec11[0];
		double fTemp3 = 1.12927979815576e-15 * fRec11[0];
		double fTemp4 = 1.11420586447254e-13 * fRec11[0];
		fRec12[0] = double(input0[i0]) - (fRec12[1] * (fConst0 * (fConst82 + fRec8[0] * (fConst81 + fConst80 * fRec8[0])) + fRec9[0] * (fConst0 * (fConst79 + fRec8[0] * (fConst78 + fConst77 * fRec8[0])) + 2.09093962630242e-53) + fRec10[0] * (fConst76 + fRec9[0] * (fConst75 + fConst5 * fRec8[0] * (fConst74 + fConst73 * fRec8[0])) + fConst5 * fRec8[0] * (fConst72 + fConst71 * fRec8[0])) + 2.19433431801845e-09) + fRec12[2] * (fConst0 * (fConst70 + fRec8[0] * (fConst68 + fConst66 * fRec8[0])) + fRec9[0] * (fConst0 * (fConst64 + fRec8[0] * (fConst62 + fConst60 * fRec8[0])) + 2.09093962630242e-53) + fRec10[0] * (fConst58 + fRec9[0] * (fConst56 + fConst5 * fRec8[0] * (fConst54 + fConst52 * fRec8[0])) + fConst5 * fRec8[0] * (fConst50 + fConst48 * fRec8[0])) + 2.19433431801845e-09) + fRec12[3] * (fConst0 * (fConst46 + fRec8[0] * (fConst45 + fConst44 * fRec8[0])) + fRec9[0] * (fConst0 * (fConst43 + fRec8[0] * (fConst42 + fConst41 * fRec8[0])) + 6.96979875434139e-54) + fRec10[0] * (fConst40 + fRec9[0] * (fConst39 + fConst5 * fRec8[0] * (fConst38 + fConst37 * fRec8[0])) + fConst5 * fRec8[0] * (fConst36 + fConst35 * fRec8[0])) + 7.31444772672817e-10)) / fTemp0;
		double fTemp5 = 4.98012390986691e-15 * fRec11[0];
		double fTemp6 = 4.91364786232388e-13 * fRec11[0];
		double fTemp7 = 3.34261759341761e-13 * fRec11[0];
		double fTemp8 = 3.38783939446729e-15 * fRec11[0];
		double fTemp9 = (fRec12[0] * (fRec9[0] * (fConst30 * fRec8[0] * (fRec8[0] * (0.0 - fTemp3 + 1.4115997476947e-15) - fTemp4 + 1.39275733059067e-13) + fConst5 * (fConst98 + fConst97 * fRec11[0])) + fConst30 * fRec8[0] * (fTemp1 + fRec8[0] * (fTemp2 + -2.07505162911121e-15) + -2.04735327596828e-13) + fConst5 * (fConst96 + fConst95 * fRec11[0])) + fRec12[1] * (fRec9[0] * (fConst30 * fRec8[0] * (fTemp7 + fRec8[0] * (fTemp8 + -4.23479924308411e-15) + -4.17827199177201e-13) + fConst5 * (fConst94 + fConst93 * fRec11[0])) + fConst30 * fRec8[0] * (fRec8[0] * (0.0 - fTemp5 + 6.22515488733364e-15) - fTemp6 + 6.14205982790485e-13) + fConst5 * (fConst92 + fConst91 * fRec11[0])) + fRec12[2] * (fRec9[0] * (fConst30 * fRec8[0] * (fRec8[0] * (0.0 - fTemp8 + 4.23479924308411e-15) - fTemp7 + 4.17827199177201e-13) + fConst5 * (fConst90 + fConst88 * fRec11[0])) + fConst30 * fRec8[0] * (fTemp6 + fRec8[0] * (fTemp5 + -6.22515488733364e-15) + -6.14205982790485e-13) + fConst5 * (fConst86 + fConst84 * fRec11[0])) + fRec12[3] * (fRec9[0] * (fConst30 * fRec8[0] * (fTemp4 + fRec8[0] * (fTemp3 + -1.4115997476947e-15) + -1.39275733059067e-13) + fConst5 * (fConst34 + fConst32 * fRec11[0])) + fConst30 * fRec8[0] * (fRec8[0] * (0.0 - fTemp2 + 2.07505162911121e-15) - fTemp1 + 2.04735327596828e-13) + fConst5 * (fConst29 + fConst27 * fRec11[0]))) / fTemp0;
		fVec0[0] = fTemp9;
		fRec7[0] = 0.9302847925323914 * (fTemp9 + fVec0[1]) - 0.8605695850647829 * fRec7[1];
		fRec6[0] = fRec7[0] - (1.8405051250752198 * fRec6[1] + 0.8612942439318627 * fRec6[2]);
		double fTemp10 = 1.8508996845035413 * fRec6[1] + 0.9254498422517706 * (fRec6[0] + fRec6[2]);
		double fTemp11 = Ftrany(TRANY_TABLE_KT88_68k, fTemp10 + 2.7e+03 * (fTemp10 / (Rtrany(TRANY_TABLE_KT88_68k, fRec5[1]) + 1e+05)) + -5.562895);
		fRec5[0] = fTemp11 + 0.0020603314814814817 * (Rtrany(TRANY_TABLE_KT88_68k, fTemp11) + 1e+05) + -2.5e+02;
		fRec4[0] = fConst101 * (fConst100 * fRec4[1] + 0.025 * (fRec5[0] - fRec5[1]));
		fRec3[0] = 0.9302847925323914 * (fRec4[0] + fRec4[1]) - 0.8605695850647829 * fRec3[1];
		fRec2[0] = fRec3[0] - (1.8405051250752198 * fRec2[1] + 0.8612942439318627 * fRec2[2]);
		double fTemp12 = 1.8508996845035413 * fRec2[1] + 0.9254498422517706 * (fRec2[0] + fRec2[2]);
		double fTemp13 = Ftrany(TRANY_TABLE_KT88_68k, fTemp12 + 2.7e+03 * (fTemp12 / (Rtrany(TRANY_TABLE_KT88_68k, fRec1[1]) + 1e+05)) + -5.562895);
		fRec1[0] = fTemp13 + 0.0020603314814814817 * (Rtrany(TRANY_TABLE_KT88_68k, fTemp13) + 1e+05) + -2.5e+02;
		fRec0[0] = fConst101 * (fConst100 * fRec0[1] + 0.025 * (fRec1[0] - fRec1[1]));
		output0[i0] = FAUSTFLOAT(fRec0[0]);
		fRec8[1] = fRec8[0];
		fRec9[1] = fRec9[0];
		fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		for (int j0 = 3; j0 > 0; j0 = j0 - 1) {
			fRec12[j0] = fRec12[j0 - 1];
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
#undef fVslider0
#undef fVslider1
#undef fVslider2
#undef fVslider3
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case DRIVE: 
		fVslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case FUZZ: 
		fVslider0_ = (float*)data; // , 0.5, 0.0, 0.99, 0.01 
		break;
	case AUDIO_IN: 
		fVslider2_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case LEVEL: 
		fVslider3_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	default:
		break;
	}
}

void Dsp::connect_static(uint32_t port,void* data, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->connect(port, data);
}


PluginLV2 *plugin() {
	return new Dsp();
}

void Dsp::del_instance(PluginLV2 *p)
{
	delete static_cast<Dsp*>(p);
}

/*
typedef enum
{
   DRIVE, 
   FUZZ, 
   INPUT, 
   LEVEL, 
} PortIndex;
*/

} // end namespace fuzzfacefm
