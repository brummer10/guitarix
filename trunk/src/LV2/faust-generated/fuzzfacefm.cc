// generated from file '../src/LV2/faust/fuzzfacefm.dsp' by dsp2cc:
// Code generated with Faust 2.15.11 (https://faust.grame.fr)

#include "trany.h"

namespace fuzzfacefm {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	double fConst4;
	double fConst5;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec9[2];
	double fConst6;
	double fConst7;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec10[2];
	double fConst8;
	double fConst9;
	double fConst10;
	double fConst11;
	double fConst12;
	double fConst13;
	double fConst14;
	double fConst15;
	double fConst16;
	double fConst17;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec11[2];
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
	double fRec8[4];
	double fConst78;
	double fConst79;
	double fConst80;
	double fConst81;
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fRec12[2];
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
	double fConst97;
	double fConst98;
	double fConst99;
	double fConst100;
	double fConst101;
	double fVec0[2];
	double fRec7[2];
	double fRec6[3];
	double fConst102;
	double fConst103;
	double fConst104;
	double fRec13[2];
	double fRec5[3];
	double fConst105;
	double fConst106;
	double fRec4[2];
	double fRec3[2];
	double fRec2[3];
	double fRec14[2];
	double fRec1[3];
	double fRec0[2];

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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec9[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec10[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec11[l2] = 0.0;
	for (int l3 = 0; (l3 < 4); l3 = (l3 + 1)) fRec8[l3] = 0.0;
	for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) fRec12[l4] = 0.0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fVec0[l5] = 0.0;
	for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) fRec7[l6] = 0.0;
	for (int l7 = 0; (l7 < 3); l7 = (l7 + 1)) fRec6[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fRec13[l8] = 0.0;
	for (int l9 = 0; (l9 < 3); l9 = (l9 + 1)) fRec5[l9] = 0.0;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) fRec4[l10] = 0.0;
	for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) fRec3[l11] = 0.0;
	for (int l12 = 0; (l12 < 3); l12 = (l12 + 1)) fRec2[l12] = 0.0;
	for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) fRec14[l13] = 0.0;
	for (int l14 = 0; (l14 < 3); l14 = (l14 + 1)) fRec1[l14] = 0.0;
	for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) fRec0[l15] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSamplingFreq)));
	fConst1 = std::tan((97.389372261283583 / fConst0));
	fConst2 = (1.0 / fConst1);
	fConst3 = (fConst2 + 1.0);
	fConst4 = (1.0 / (fConst3 * fConst1));
	fConst5 = (0.93028479253239138 * mydsp_faustpower2_f(fConst0));
	fConst6 = (3.3531209733912099e-19 * fConst0);
	fConst7 = (((fConst6 + 3.24149709132582e-15) * fConst0) + -1.4628895453456301e-14);
	fConst8 = (4.2717686608045702e-16 * fConst0);
	fConst9 = (((fConst8 + 6.4321494874189598e-16) * fConst0) + 3.45797348759893e-55);
	fConst10 = (4.27512178177797e-16 * fConst0);
	fConst11 = (((-6.4344317434698802e-16 - fConst10) * fConst0) + -3.2623424697545702e-55);
	fConst12 = (1.6814895745264899e-16 * fConst0);
	fConst13 = (((-1.63110208134281e-12 - fConst12) * fConst0) + 1.69410806769336e-10);
	fConst14 = (2.1421638303336699e-13 * fConst0);
	fConst15 = (((-7.4421674350198897e-12 - fConst14) * fConst0) + 3.2160747437094799e-11);
	fConst16 = (2.1438453199081999e-13 * fConst0);
	fConst17 = (((fConst16 + 7.4478704182697307e-12) * fConst0) + -3.2172158717349402e-11);
	fConst18 = (7.5535874162256398e-17 * fConst0);
	fConst19 = (((fConst18 + 1.61641996632585e-12) * fConst0) + -1.6091784998802001e-10);
	fConst20 = (1.5062889936039299e-19 * fConst0);
	fConst21 = (((-3.2183569997603901e-15 - fConst20) * fConst0) + -1.5333557259551101e-54);
	fConst22 = (4.2452186616965102e-16 * fConst0);
	fConst23 = (7.6075416727176396e-56 - fConst22);
	fConst24 = (4.2467249506901202e-16 * fConst0);
	fConst25 = (fConst24 + -7.1771534334600597e-56);
	fConst26 = (2.1288498022809499e-13 * fConst0);
	fConst27 = (fConst26 + 7.0753644361608499e-12);
	fConst28 = (2.1296051610225699e-13 * fConst0);
	fConst29 = (-7.0778749178168597e-12 - fConst28);
	fConst30 = (((3.24149709132582e-15 - fConst6) * fConst0) + 1.4628895453456301e-14);
	fConst31 = (((6.4321494874189598e-16 - fConst8) * fConst0) + -3.45797348759893e-55);
	fConst32 = (((fConst10 + -6.4344317434698802e-16) * fConst0) + 3.2623424697545702e-55);
	fConst33 = (((fConst12 + -1.63110208134281e-12) * fConst0) + -1.69410806769336e-10);
	fConst34 = (((fConst14 + -7.4421674350198897e-12) * fConst0) + -3.2160747437094799e-11);
	fConst35 = (((7.4478704182697307e-12 - fConst16) * fConst0) + 3.2172158717349402e-11);
	fConst36 = (((1.61641996632585e-12 - fConst18) * fConst0) + 1.6091784998802001e-10);
	fConst37 = (((fConst20 + -3.2183569997603901e-15) * fConst0) + 1.5333557259551101e-54);
	fConst38 = (fConst22 + 7.6075416727176396e-56);
	fConst39 = (-7.1771534334600597e-56 - fConst24);
	fConst40 = (7.0753644361608499e-12 - fConst26);
	fConst41 = (fConst28 + -7.0778749178168597e-12);
	fConst42 = (1.1177069911303999e-19 * fConst0);
	fConst43 = (((fConst42 + -3.24149709132582e-15) * fConst0) + 1.4628895453456301e-14);
	fConst44 = (1.4239228869348599e-16 * fConst0);
	fConst45 = (((fConst44 + -6.4321494874189598e-16) * fConst0) + -3.45797348759893e-55);
	fConst46 = (1.42504059392599e-16 * fConst0);
	fConst47 = (((6.4344317434698802e-16 - fConst46) * fConst0) + 3.2623424697545702e-55);
	fConst48 = (5.6049652484216404e-17 * fConst0);
	fConst49 = (((1.63110208134281e-12 - fConst48) * fConst0) + -1.69410806769336e-10);
	fConst50 = (7.1405461011122294e-14 * fConst0);
	fConst51 = (((7.4421674350198897e-12 - fConst50) * fConst0) + -3.2160747437094799e-11);
	fConst52 = (7.1461510663606604e-14 * fConst0);
	fConst53 = (((fConst52 + -7.4478704182697307e-12) * fConst0) + 3.2172158717349402e-11);
	fConst54 = (2.5178624720752199e-17 * fConst0);
	fConst55 = (((fConst54 + -1.61641996632585e-12) * fConst0) + 1.6091784998802001e-10);
	fConst56 = (5.0209633120131098e-20 * fConst0);
	fConst57 = (((3.2183569997603901e-15 - fConst56) * fConst0) + 1.5333557259551101e-54);
	fConst58 = (1.4150728872321699e-16 * fConst0);
	fConst59 = (-7.6075416727176396e-56 - fConst58);
	fConst60 = (1.4155749835633699e-16 * fConst0);
	fConst61 = (fConst60 + 7.1771534334600597e-56);
	fConst62 = (7.0961660076031701e-14 * fConst0);
	fConst63 = (fConst62 + -7.0753644361608499e-12);
	fConst64 = (7.0986838700752397e-14 * fConst0);
	fConst65 = (7.0778749178168597e-12 - fConst64);
	fConst66 = (((-3.24149709132582e-15 - fConst42) * fConst0) + -1.4628895453456301e-14);
	fConst67 = (((-6.4321494874189598e-16 - fConst44) * fConst0) + 3.45797348759893e-55);
	fConst68 = (((fConst46 + 6.4344317434698802e-16) * fConst0) + -3.2623424697545702e-55);
	fConst69 = (((fConst48 + 1.63110208134281e-12) * fConst0) + 1.69410806769336e-10);
	fConst70 = (((fConst50 + 7.4421674350198897e-12) * fConst0) + 3.2160747437094799e-11);
	fConst71 = (((-7.4478704182697307e-12 - fConst52) * fConst0) + -3.2172158717349402e-11);
	fConst72 = (((-1.61641996632585e-12 - fConst54) * fConst0) + -1.6091784998802001e-10);
	fConst73 = (((fConst56 + 3.2183569997603901e-15) * fConst0) + -1.5333557259551101e-54);
	fConst74 = (fConst58 + -7.6075416727176396e-56);
	fConst75 = (7.1771534334600597e-56 - fConst60);
	fConst76 = (-7.0753644361608499e-12 - fConst62);
	fConst77 = (fConst64 + 7.0778749178168597e-12);
	fConst78 = (2.0681037922594001e-13 * fConst0);
	fConst79 = (fConst78 + 4.7473961557966103e-12);
	fConst80 = (1.4068733280676199e-13 * fConst0);
	fConst81 = (-3.22952119441946e-12 - fConst80);
	fConst82 = (1.1254986624540899e-13 * fConst0);
	fConst83 = (fConst82 + 2.5836169555355699e-12);
	fConst84 = (1.6544830338075201e-13 * fConst0);
	fConst85 = (-3.7979169246372897e-12 - fConst84);
	fConst86 = (6.2043113767781895e-13 * fConst0);
	fConst87 = (-4.7473961557966103e-12 - fConst86);
	fConst88 = (4.2206199842028502e-13 * fConst0);
	fConst89 = (fConst88 + 3.22952119441946e-12);
	fConst90 = (3.3764959873622802e-13 * fConst0);
	fConst91 = (-2.5836169555355699e-12 - fConst90);
	fConst92 = (4.9634491014225504e-13 * fConst0);
	fConst93 = (fConst92 + 3.7979169246372897e-12);
	fConst94 = (fConst86 + -4.7473961557966103e-12);
	fConst95 = (3.22952119441946e-12 - fConst88);
	fConst96 = (fConst90 + -2.5836169555355699e-12);
	fConst97 = (3.7979169246372897e-12 - fConst92);
	fConst98 = (4.7473961557966103e-12 - fConst78);
	fConst99 = (fConst80 + -3.22952119441946e-12);
	fConst100 = (2.5836169555355699e-12 - fConst82);
	fConst101 = (fConst84 + -3.7979169246372897e-12);
	fConst102 = (1.0 / std::tan((270.1769682087222 / fConst0)));
	fConst103 = (1.0 / (fConst102 + 1.0));
	fConst104 = (1.0 - fConst102);
	fConst105 = (0.0 - fConst4);
	fConst106 = ((1.0 - fConst2) / fConst3);
	fVslider0 = FAUSTFLOAT(0.5);
	fVslider1 = FAUSTFLOAT(0.5);
	fVslider2 = FAUSTFLOAT(0.5);
	fVslider3 = FAUSTFLOAT(0.5);
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fVslider0 (*fVslider0_)
#define fVslider1 (*fVslider1_)
#define fVslider2 (*fVslider2_)
#define fVslider3 (*fVslider3_)
	double fSlow0 = (0.0070000000000000062 * (1.0 - double(fVslider0)));
	double fSlow1 = (0.0070000000000000062 * (1.0 - double(fVslider1)));
	double fSlow2 = (0.0070000000000000062 * double(fVslider2));
	double fSlow3 = (0.0070000000000000062 * (1.0 - double(fVslider3)));
	for (int i = 0; (i < count); i = (i + 1)) {
		fRec9[0] = (fSlow0 + (0.99299999999999999 * fRec9[1]));
		fRec10[0] = (fSlow1 + (0.99299999999999999 * fRec10[1]));
		fRec11[0] = (fSlow2 + (0.99299999999999999 * fRec11[1]));
		double fTemp0 = (((fRec9[0] * ((fConst0 * (fConst66 + (fRec10[0] * (fConst67 + (fConst68 * fRec10[0]))))) + 6.9697987543413902e-54)) + (fConst0 * (fConst69 + ((fRec10[0] * (fConst70 + (fConst71 * fRec10[0]))) + (fRec11[0] * (fConst72 + ((fRec9[0] * (fConst73 + (fConst0 * (fRec10[0] * (fConst74 + (fConst75 * fRec10[0])))))) + (fConst0 * (fRec10[0] * (fConst76 + (fConst77 * fRec10[0]))))))))))) + 7.3144477267281697e-10);
		fRec8[0] = (double(input0[i]) - ((((fRec8[1] * (((fRec9[0] * ((fConst0 * (fConst7 + (fRec10[0] * (fConst9 + (fConst11 * fRec10[0]))))) + 2.0909396263024202e-53)) + (fConst0 * (fConst13 + ((fRec10[0] * (fConst15 + (fConst17 * fRec10[0]))) + (fRec11[0] * (fConst19 + ((fRec9[0] * (fConst21 + (fConst0 * (fRec10[0] * (fConst23 + (fConst25 * fRec10[0])))))) + (fConst0 * (fRec10[0] * (fConst27 + (fConst29 * fRec10[0]))))))))))) + 2.19433431801845e-09)) + (fRec8[2] * (((fRec9[0] * ((fConst0 * (fConst30 + (fRec10[0] * (fConst31 + (fConst32 * fRec10[0]))))) + 2.0909396263024202e-53)) + (fConst0 * (fConst33 + ((fRec10[0] * (fConst34 + (fConst35 * fRec10[0]))) + (fRec11[0] * (fConst36 + ((fRec9[0] * (fConst37 + (fConst0 * (fRec10[0] * (fConst38 + (fConst39 * fRec10[0])))))) + (fConst0 * (fRec10[0] * (fConst40 + (fConst41 * fRec10[0]))))))))))) + 2.19433431801845e-09))) + (fRec8[3] * (((fRec9[0] * ((fConst0 * (fConst43 + (fRec10[0] * (fConst45 + (fConst47 * fRec10[0]))))) + 6.9697987543413902e-54)) + (fConst0 * (fConst49 + ((fRec10[0] * (fConst51 + (fConst53 * fRec10[0]))) + (fRec11[0] * (fConst55 + ((fRec9[0] * (fConst57 + (fConst0 * (fRec10[0] * (fConst59 + (fConst61 * fRec10[0])))))) + (fConst0 * (fRec10[0] * (fConst63 + (fConst65 * fRec10[0]))))))))))) + 7.3144477267281697e-10))) / fTemp0));
		fRec12[0] = (fSlow3 + (0.99299999999999999 * fRec12[1]));
		double fTemp1 = (1.1292797981557601e-15 * fRec12[0]);
		double fTemp2 = (1.1142058644725399e-13 * fRec12[0]);
		double fTemp3 = (1.6378826207746301e-13 * fRec12[0]);
		double fTemp4 = (1.66004130328897e-15 * fRec12[0]);
		double fTemp5 = (3.34261759341761e-13 * fRec12[0]);
		double fTemp6 = (3.3878393944672901e-15 * fRec12[0]);
		double fTemp7 = (4.9801239098669099e-15 * fRec12[0]);
		double fTemp8 = (4.9136478623238799e-13 * fRec12[0]);
		double fTemp9 = (((((fRec8[0] * (fConst79 + (((fRec9[0] * (fConst81 + ((fConst0 * (fRec10[0] * (((fRec10[0] * ((0.0 - fTemp1) + 1.4115997476947001e-15)) - fTemp2) + 1.3927573305906699e-13))) + (fConst83 * fRec12[0])))) + (fConst0 * (fRec10[0] * ((fTemp3 + (fRec10[0] * (fTemp4 + -2.0750516291112099e-15))) + -2.0473532759682801e-13)))) + (fConst85 * fRec12[0])))) + (fRec8[1] * (fConst87 + (((fRec9[0] * (fConst89 + ((fConst0 * (fRec10[0] * ((fTemp5 + (fRec10[0] * (fTemp6 + -4.2347992430841103e-15))) + -4.1782719917720101e-13))) + (fConst91 * fRec12[0])))) + (fConst0 * (fRec10[0] * (((fRec10[0] * ((0.0 - fTemp7) + 6.2251548873336404e-15)) - fTemp8) + 6.1420598279048502e-13)))) + (fConst93 * fRec12[0]))))) + (fRec8[2] * (fConst94 + (((fRec9[0] * (fConst95 + ((fConst0 * (fRec10[0] * (((fRec10[0] * ((0.0 - fTemp6) + 4.2347992430841103e-15)) - fTemp5) + 4.1782719917720101e-13))) + (fConst96 * fRec12[0])))) + (fConst0 * (fRec10[0] * ((fTemp8 + (fRec10[0] * (fTemp7 + -6.2251548873336404e-15))) + -6.1420598279048502e-13)))) + (fConst97 * fRec12[0]))))) + (fRec8[3] * (fConst98 + (((fRec9[0] * (fConst99 + ((fConst0 * (fRec10[0] * ((fTemp2 + (fRec10[0] * (fTemp1 + -1.4115997476947001e-15))) + -1.3927573305906699e-13))) + (fConst100 * fRec12[0])))) + (fConst0 * (fRec10[0] * (((fRec10[0] * ((0.0 - fTemp4) + 2.0750516291112099e-15)) - fTemp3) + 2.0473532759682801e-13)))) + (fConst101 * fRec12[0]))))) / fTemp0);
		fVec0[0] = fTemp9;
		fRec7[0] = ((fConst5 * (fTemp9 + fVec0[1])) - (0.86056958506478287 * fRec7[1]));
		fRec6[0] = (fRec7[0] - ((1.8405051250752198 * fRec6[1]) + (0.86129424393186271 * fRec6[2])));
		fRec13[0] = (fConst103 * ((0.027 * (fRec5[1] + fRec5[2])) - (fConst104 * fRec13[1])));
		fRec5[0] = (double(Ftrany(int(TRANY_TABLE_KT88_68k), double((((0.92544984225177063 * (fRec6[0] + fRec6[2])) + (fRec13[0] + (1.8508996845035413 * fRec6[1]))) + -5.5628950000000001)))) + -43.966851851851828);
		fRec4[0] = ((0.025000000000000001 * ((fConst4 * fRec5[0]) + (fConst105 * fRec5[1]))) - (fConst106 * fRec4[1]));
		fRec3[0] = ((0.93028479253239138 * (fRec4[0] + fRec4[1])) - (0.86056958506478287 * fRec3[1]));
		fRec2[0] = (fRec3[0] - ((1.8405051250752198 * fRec2[1]) + (0.86129424393186271 * fRec2[2])));
		fRec14[0] = (fConst103 * ((0.027 * (fRec1[1] + fRec1[2])) - (fConst104 * fRec14[1])));
		fRec1[0] = (double(Ftrany(int(TRANY_TABLE_KT88_68k), double((((0.92544984225177063 * (fRec2[0] + fRec2[2])) + (fRec14[0] + (1.8508996845035413 * fRec2[1]))) + -5.5628950000000001)))) + -43.966851851851828);
		fRec0[0] = ((0.025000000000000001 * ((fConst4 * fRec1[0]) + (fConst105 * fRec1[1]))) - (fConst106 * fRec0[1]));
		output0[i] = FAUSTFLOAT(fRec0[0]);
		fRec9[1] = fRec9[0];
		fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		for (int j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
			fRec8[j0] = fRec8[(j0 - 1)];
		}
		fRec12[1] = fRec12[0];
		fVec0[1] = fVec0[0];
		fRec7[1] = fRec7[0];
		fRec6[2] = fRec6[1];
		fRec6[1] = fRec6[0];
		fRec13[1] = fRec13[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fRec14[1] = fRec14[0];
		fRec1[2] = fRec1[1];
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
		fVslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case FUZZ: 
		fVslider1_ = (float*)data; // , 0.5, 0.0, 0.98999999999999999, 0.01 
		break;
	case INPUT: 
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
