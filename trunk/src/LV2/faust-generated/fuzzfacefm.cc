// generated from file '../src/LV2/faust/fuzzfacefm.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "trany.h"

namespace fuzzfacefm {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec4[2];
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
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec5[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec6[2];
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
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fRec7[2];
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
	double 	fRec8[4];
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
	double 	fRec9[2];
	double 	fRec3[3];
	double 	fConst103;
	double 	fConst104;
	double 	fConst105;
	double 	fConst106;
	double 	fConst107;
	double 	fRec2[2];
	double 	fRec10[2];
	double 	fRec1[3];
	double 	fRec0[2];
	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(uint32_t samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(uint32_t samplingFreq, PluginLV2*);
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
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<4; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<3; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<3; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = double(iConst0);
	fConst2 = (5.60496524842164e-17 * fConst1);
	fConst3 = (1.69410806769336e-10 + (fConst1 * (1.63110208134281e-12 + fConst2)));
	fConst4 = (2.51786247207522e-17 * fConst1);
	fConst5 = ((fConst1 * (0 - (1.61641996632585e-12 + fConst4))) - 1.6091784998802e-10);
	fConst6 = (7.09868387007524e-14 * fConst1);
	fConst7 = (7.07787491781686e-12 + fConst6);
	fConst8 = (7.09616600760317e-14 * fConst1);
	fConst9 = (0 - (7.07536443616085e-12 + fConst8));
	fConst10 = (1.41557498356337e-16 * fConst1);
	fConst11 = (7.17715343346006e-56 - fConst10);
	fConst12 = (1.41507288723217e-16 * fConst1);
	fConst13 = (fConst12 - 7.60754167271764e-56);
	fConst14 = (5.02096331201311e-20 * fConst1);
	fConst15 = ((fConst1 * (3.21835699976039e-15 + fConst14)) - 1.53335572595511e-54);
	fConst16 = (7.14615106636066e-14 * fConst1);
	fConst17 = ((fConst1 * (0 - (7.44787041826973e-12 + fConst16))) - 3.21721587173494e-11);
	fConst18 = (7.14054610111223e-14 * fConst1);
	fConst19 = (3.21607474370948e-11 + (fConst1 * (7.44216743501989e-12 + fConst18)));
	fConst20 = (1.1177069911304e-19 * fConst1);
	fConst21 = ((fConst1 * (0 - (3.24149709132582e-15 + fConst20))) - 1.46288954534563e-14);
	fConst22 = (1.42504059392599e-16 * fConst1);
	fConst23 = ((fConst1 * (6.43443174346988e-16 + fConst22)) - 3.26234246975457e-55);
	fConst24 = (1.42392288693486e-16 * fConst1);
	fConst25 = (3.45797348759893e-55 + (fConst1 * (0 - (6.43214948741896e-16 + fConst24))));
	fConst26 = (2.0681037922594e-13 * fConst1);
	fConst27 = (4.74739615579661e-12 - fConst26);
	fConst28 = (1.65448303380752e-13 * fConst1);
	fConst29 = (fConst28 - 3.79791692463729e-12);
	fConst30 = (1.12549866245409e-13 * fConst1);
	fConst31 = (2.58361695553557e-12 - fConst30);
	fConst32 = (1.40687332806762e-13 * fConst1);
	fConst33 = (fConst32 - 3.22952119441946e-12);
	fConst34 = ((fConst1 * (1.63110208134281e-12 - fConst2)) - 1.69410806769336e-10);
	fConst35 = (1.6091784998802e-10 + (fConst1 * (fConst4 - 1.61641996632585e-12)));
	fConst36 = (7.07787491781686e-12 - fConst6);
	fConst37 = (fConst8 - 7.07536443616085e-12);
	fConst38 = (7.17715343346006e-56 + fConst10);
	fConst39 = (0 - (7.60754167271764e-56 + fConst12));
	fConst40 = (1.53335572595511e-54 + (fConst1 * (3.21835699976039e-15 - fConst14)));
	fConst41 = (3.21721587173494e-11 + (fConst1 * (fConst16 - 7.44787041826973e-12)));
	fConst42 = ((fConst1 * (7.44216743501989e-12 - fConst18)) - 3.21607474370948e-11);
	fConst43 = (1.46288954534563e-14 + (fConst1 * (fConst20 - 3.24149709132582e-15)));
	fConst44 = (3.26234246975457e-55 + (fConst1 * (6.43443174346988e-16 - fConst22)));
	fConst45 = ((fConst1 * (fConst24 - 6.43214948741896e-16)) - 3.45797348759893e-55);
	fConst46 = (7.55358741622564e-17 * fConst1);
	fConst47 = (1.6091784998802e-10 + (fConst1 * (1.61641996632585e-12 - fConst46)));
	fConst48 = (2.12960516102257e-13 * fConst1);
	fConst49 = (fConst48 - 7.07787491781686e-12);
	fConst50 = (2.12884980228095e-13 * fConst1);
	fConst51 = (7.07536443616085e-12 - fConst50);
	fConst52 = (4.24672495069012e-16 * fConst1);
	fConst53 = (0 - (7.17715343346006e-56 + fConst52));
	fConst54 = (4.24521866169651e-16 * fConst1);
	fConst55 = (7.60754167271764e-56 + fConst54);
	fConst56 = (1.50628899360393e-19 * fConst1);
	fConst57 = (1.53335572595511e-54 + (fConst1 * (fConst56 - 3.21835699976039e-15)));
	fConst58 = (2.1438453199082e-13 * fConst1);
	fConst59 = (3.21721587173494e-11 + (fConst1 * (7.44787041826973e-12 - fConst58)));
	fConst60 = (2.14216383033367e-13 * fConst1);
	fConst61 = ((fConst1 * (fConst60 - 7.44216743501989e-12)) - 3.21607474370948e-11);
	fConst62 = (1.68148957452649e-16 * fConst1);
	fConst63 = ((fConst1 * (fConst62 - 1.63110208134281e-12)) - 1.69410806769336e-10);
	fConst64 = (3.35312097339121e-19 * fConst1);
	fConst65 = (1.46288954534563e-14 + (fConst1 * (3.24149709132582e-15 - fConst64)));
	fConst66 = (4.27512178177797e-16 * fConst1);
	fConst67 = (3.26234246975457e-55 + (fConst1 * (fConst66 - 6.43443174346988e-16)));
	fConst68 = (4.27176866080457e-16 * fConst1);
	fConst69 = ((fConst1 * (6.43214948741896e-16 - fConst68)) - 3.45797348759893e-55);
	fConst70 = (1.69410806769336e-10 + (fConst1 * (0 - (1.63110208134281e-12 + fConst62))));
	fConst71 = ((fConst1 * (1.61641996632585e-12 + fConst46)) - 1.6091784998802e-10);
	fConst72 = (0 - (7.07787491781686e-12 + fConst48));
	fConst73 = (7.07536443616085e-12 + fConst50);
	fConst74 = (fConst52 - 7.17715343346006e-56);
	fConst75 = (7.60754167271764e-56 - fConst54);
	fConst76 = ((fConst1 * (0 - (3.21835699976039e-15 + fConst56))) - 1.53335572595511e-54);
	fConst77 = ((fConst1 * (7.44787041826973e-12 + fConst58)) - 3.21721587173494e-11);
	fConst78 = (3.21607474370948e-11 + (fConst1 * (0 - (7.44216743501989e-12 + fConst60))));
	fConst79 = ((fConst1 * (3.24149709132582e-15 + fConst64)) - 1.46288954534563e-14);
	fConst80 = ((fConst1 * (0 - (6.43443174346988e-16 + fConst66))) - 3.26234246975457e-55);
	fConst81 = (3.45797348759893e-55 + (fConst1 * (6.43214948741896e-16 + fConst68)));
	fConst82 = (4.96344910142255e-13 * fConst1);
	fConst83 = (3.79791692463729e-12 - fConst82);
	fConst84 = (4.22061998420285e-13 * fConst1);
	fConst85 = (3.22952119441946e-12 - fConst84);
	fConst86 = (3.37649598736228e-13 * fConst1);
	fConst87 = (fConst86 - 2.58361695553557e-12);
	fConst88 = (6.20431137677819e-13 * fConst1);
	fConst89 = (fConst88 - 4.74739615579661e-12);
	fConst90 = (0 - (4.74739615579661e-12 + fConst88));
	fConst91 = (3.79791692463729e-12 + fConst82);
	fConst92 = (3.22952119441946e-12 + fConst84);
	fConst93 = (0 - (2.58361695553557e-12 + fConst86));
	fConst94 = (4.74739615579661e-12 + fConst26);
	fConst95 = (0 - (3.79791692463729e-12 + fConst28));
	fConst96 = (0 - (3.22952119441946e-12 + fConst32));
	fConst97 = (2.58361695553557e-12 + fConst30);
	fConst98 = faustpower<2>(fConst1);
	fConst99 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst100 = (1 + fConst99);
	fConst101 = (0.027 / fConst100);
	fConst102 = (0 - ((1 - fConst99) / fConst100));
	fConst103 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst104 = (0 - fConst103);
	fConst105 = (1 + fConst103);
	fConst106 = (0.025 / fConst105);
	fConst107 = (0 - ((1 - fConst103) / fConst105));
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
#define fslider2 (*fslider2_)
#define fslider3 (*fslider3_)
	double 	fSlow0 = (0.007000000000000006 * (1 - double(fslider0)));
	double 	fSlow1 = (0.007000000000000006 * (1 - double(fslider1)));
	double 	fSlow2 = (0.007000000000000006 * double(fslider2));
	double 	fSlow3 = (0.007000000000000006 * (1 - double(fslider3)));
	for (int i=0; i<count; i++) {
		fRec4[0] = ((0.993 * fRec4[1]) + fSlow0);
		fRec5[0] = ((0.993 * fRec5[1]) + fSlow1);
		fRec6[0] = ((0.993 * fRec6[1]) + fSlow2);
		double fTemp0 = (7.31444772672817e-10 + ((fRec5[0] * (6.96979875434139e-54 + (fConst1 * ((fRec4[0] * (fConst25 + (fConst23 * fRec4[0]))) + fConst21)))) + (fConst1 * (((fRec4[0] * (fConst19 + (fConst17 * fRec4[0]))) + (fRec6[0] * (((fRec5[0] * (fConst15 + (fConst1 * (fRec4[0] * (fConst13 + (fConst11 * fRec4[0])))))) + (fConst1 * (fRec4[0] * (fConst9 + (fConst7 * fRec4[0]))))) + fConst5))) + fConst3))));
		fRec7[0] = ((0.993 * fRec7[1]) + fSlow3);
		double fTemp1 = (1.63788262077463e-13 * fRec7[0]);
		double fTemp2 = (1.66004130328897e-15 * fRec7[0]);
		double fTemp3 = (1.12927979815576e-15 * fRec7[0]);
		double fTemp4 = (1.11420586447254e-13 * fRec7[0]);
		fRec8[0] = ((double)input0[i] - ((((fRec8[1] * (2.19433431801845e-09 + ((fRec5[0] * (2.09093962630242e-53 + (fConst1 * ((fRec4[0] * (fConst81 + (fConst80 * fRec4[0]))) + fConst79)))) + (fConst1 * (((fRec4[0] * (fConst78 + (fConst77 * fRec4[0]))) + (fRec6[0] * (((fRec5[0] * (fConst76 + (fConst1 * (fRec4[0] * (fConst75 + (fConst74 * fRec4[0])))))) + (fConst1 * (fRec4[0] * (fConst73 + (fConst72 * fRec4[0]))))) + fConst71))) + fConst70))))) + (fRec8[2] * (2.19433431801845e-09 + ((fRec5[0] * (2.09093962630242e-53 + (fConst1 * ((fRec4[0] * (fConst69 + (fConst67 * fRec4[0]))) + fConst65)))) + (fConst1 * (fConst63 + ((fRec4[0] * (fConst61 + (fConst59 * fRec4[0]))) + (fRec6[0] * (((fRec5[0] * (fConst57 + (fConst1 * (fRec4[0] * (fConst55 + (fConst53 * fRec4[0])))))) + (fConst1 * (fRec4[0] * (fConst51 + (fConst49 * fRec4[0]))))) + fConst47))))))))) + (fRec8[3] * (7.31444772672817e-10 + ((fRec5[0] * (6.96979875434139e-54 + (fConst1 * ((fRec4[0] * (fConst45 + (fConst44 * fRec4[0]))) + fConst43)))) + (fConst1 * (((fRec4[0] * (fConst42 + (fConst41 * fRec4[0]))) + (fRec6[0] * (((fRec5[0] * (fConst40 + (fConst1 * (fRec4[0] * (fConst39 + (fConst38 * fRec4[0])))))) + (fConst1 * (fRec4[0] * (fConst37 + (fConst36 * fRec4[0]))))) + fConst35))) + fConst34)))))) / fTemp0));
		double fTemp5 = (4.98012390986691e-15 * fRec7[0]);
		double fTemp6 = (4.91364786232388e-13 * fRec7[0]);
		double fTemp7 = (3.34261759341761e-13 * fRec7[0]);
		double fTemp8 = (3.38783939446729e-15 * fRec7[0]);
		fRec9[0] = ((fConst102 * fRec9[1]) + (fConst101 * (fRec3[1] + fRec3[2])));
		fRec3[0] = (Ftrany(TRANY_TABLE_KT88_68k, ((fRec9[0] + (fConst98 * (((((fRec8[0] * ((((fRec5[0] * (((fConst1 * (fRec4[0] * (1.39275733059067e-13 + ((fRec4[0] * (1.4115997476947e-15 + (0 - fTemp3))) - fTemp4)))) + (fConst97 * fRec7[0])) + fConst96)) + (fConst1 * (fRec4[0] * ((fTemp1 + (fRec4[0] * (fTemp2 - 2.07505162911121e-15))) - 2.04735327596828e-13)))) + (fConst95 * fRec7[0])) + fConst94)) + (fRec8[1] * ((((fRec5[0] * (((fConst1 * (fRec4[0] * ((fTemp7 + (fRec4[0] * (fTemp8 - 4.23479924308411e-15))) - 4.17827199177201e-13))) + (fConst93 * fRec7[0])) + fConst92)) + (fConst1 * (fRec4[0] * (6.14205982790485e-13 + ((fRec4[0] * (6.22515488733364e-15 + (0 - fTemp5))) - fTemp6))))) + (fConst91 * fRec7[0])) + fConst90))) + (fRec8[2] * (fConst89 + (((fRec5[0] * (((fConst1 * (fRec4[0] * (4.17827199177201e-13 + ((fRec4[0] * (4.23479924308411e-15 + (0 - fTemp8))) - fTemp7)))) + (fConst87 * fRec7[0])) + fConst85)) + (fConst1 * (fRec4[0] * ((fTemp6 + (fRec4[0] * (fTemp5 - 6.22515488733364e-15))) - 6.14205982790485e-13)))) + (fConst83 * fRec7[0]))))) + (fRec8[3] * ((((fRec5[0] * (fConst33 + ((fConst1 * (fRec4[0] * ((fTemp4 + (fRec4[0] * (fTemp3 - 1.4115997476947e-15))) - 1.39275733059067e-13))) + (fConst31 * fRec7[0])))) + (fConst1 * (fRec4[0] * (2.04735327596828e-13 + ((fRec4[0] * (2.07505162911121e-15 + (0 - fTemp2))) - fTemp1))))) + (fConst29 * fRec7[0])) + fConst27))) / fTemp0))) - 5.562895)) - 43.96685185185183);
		fRec2[0] = ((fConst107 * fRec2[1]) + (fConst106 * ((fConst103 * fRec3[0]) + (fConst104 * fRec3[1]))));
		fRec10[0] = ((fConst102 * fRec10[1]) + (fConst101 * (fRec1[1] + fRec1[2])));
		fRec1[0] = (Ftrany(TRANY_TABLE_KT88_68k, ((fRec10[0] + fRec2[0]) - 5.562895)) - 43.96685185185183);
		fRec0[0] = ((fConst107 * fRec0[1]) + (fConst106 * ((fConst103 * fRec1[0]) + (fConst104 * fRec1[1]))));
		output0[i] = (FAUSTFLOAT)fRec0[0];
		// post processing
		fRec0[1] = fRec0[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec10[1] = fRec10[0];
		fRec2[1] = fRec2[0];
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
		fRec9[1] = fRec9[0];
		for (int i=3; i>0; i--) fRec8[i] = fRec8[i-1];
		fRec7[1] = fRec7[0];
		fRec6[1] = fRec6[0];
		fRec5[1] = fRec5[0];
		fRec4[1] = fRec4[0];
	}
#undef fslider0
#undef fslider1
#undef fslider2
#undef fslider3
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
		fslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case FUZZ: 
		fslider0_ = (float*)data; // , 0.5, 0.0, 0.99, 0.01 
		break;
	case INPUT: 
		fslider2_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case LEVEL: 
		fslider3_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
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
