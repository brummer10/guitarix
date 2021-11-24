// generated from file '../src/LV2/faust/fuzzfacefm.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "trany.h"

namespace fuzzfacefm {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	double fConst0;
	double fConst2;
	double fConst3;
	double fConst4;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec9[2];
	double fConst6;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec10[2];
	double fConst8;
	double fConst10;
	double fConst12;
	double fConst14;
	double fConst16;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec11[2];
	double fConst18;
	double fConst20;
	double fConst22;
	double fConst24;
	double fConst26;
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
	double fConst42;
	double fConst44;
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
	double fRec8[4];
	double fConst78;
	double fConst80;
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fRec12[2];
	double fConst82;
	double fConst84;
	double fConst86;
	double fConst88;
	double fConst90;
	double fConst92;
	double fConst93;
	double fConst94;
	double fConst95;
	double fConst96;
	double fConst97;
	double fConst98;
	double fConst99;
	double fConst100;
	double fVec0[2];
	double fRec7[2];
	double fRec6[3];
	double fRec5[2];
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec9[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec10[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec11[l2] = 0.0;
	for (int l3 = 0; (l3 < 4); l3 = (l3 + 1)) fRec8[l3] = 0.0;
	for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) fRec12[l4] = 0.0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fVec0[l5] = 0.0;
	for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) fRec7[l6] = 0.0;
	for (int l7 = 0; (l7 < 3); l7 = (l7 + 1)) fRec6[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fRec5[l8] = 0.0;
	for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) fRec4[l9] = 0.0;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) fRec3[l10] = 0.0;
	for (int l11 = 0; (l11 < 3); l11 = (l11 + 1)) fRec2[l11] = 0.0;
	for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) fRec1[l12] = 0.0;
	for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) fRec0[l13] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = (3.1415926535897931 / fConst0);
	fConst2 = (1.0 / (fConst1 + 1.0));
	fConst3 = (1.0 - fConst1);
	fConst4 = (0.93028479253239138 * mydsp_faustpower2_f(fConst0));
	double fConst5 = (3.3531209733912099e-19 * fConst0);
	fConst6 = ((fConst0 * (fConst5 + 3.24149709132582e-15)) + -1.4628895453456301e-14);
	double fConst7 = (4.2717686608045702e-16 * fConst0);
	fConst8 = ((fConst0 * (fConst7 + 6.4321494874189598e-16)) + 3.45797348759893e-55);
	double fConst9 = (4.27512178177797e-16 * fConst0);
	fConst10 = ((fConst0 * (-6.4344317434698802e-16 - fConst9)) + -3.2623424697545702e-55);
	double fConst11 = (1.6814895745264899e-16 * fConst0);
	fConst12 = ((fConst0 * (-1.63110208134281e-12 - fConst11)) + 1.69410806769336e-10);
	double fConst13 = (2.1421638303336699e-13 * fConst0);
	fConst14 = ((fConst0 * (-7.4421674350198897e-12 - fConst13)) + 3.2160747437094799e-11);
	double fConst15 = (2.1438453199081999e-13 * fConst0);
	fConst16 = ((fConst0 * (fConst15 + 7.4478704182697307e-12)) + -3.2172158717349402e-11);
	double fConst17 = (7.5535874162256398e-17 * fConst0);
	fConst18 = ((fConst0 * (fConst17 + 1.61641996632585e-12)) + -1.6091784998802001e-10);
	double fConst19 = (1.5062889936039299e-19 * fConst0);
	fConst20 = ((fConst0 * (-3.2183569997603901e-15 - fConst19)) + -1.5333557259551101e-54);
	double fConst21 = (4.2452186616965102e-16 * fConst0);
	fConst22 = (7.6075416727176396e-56 - fConst21);
	double fConst23 = (4.2467249506901202e-16 * fConst0);
	fConst24 = (fConst23 + -7.1771534334600597e-56);
	double fConst25 = (2.1288498022809499e-13 * fConst0);
	fConst26 = (fConst25 + 7.0753644361608499e-12);
	double fConst27 = (2.1296051610225699e-13 * fConst0);
	fConst28 = (-7.0778749178168597e-12 - fConst27);
	fConst29 = ((fConst0 * (3.24149709132582e-15 - fConst5)) + 1.4628895453456301e-14);
	fConst30 = ((fConst0 * (6.4321494874189598e-16 - fConst7)) + -3.45797348759893e-55);
	fConst31 = ((fConst0 * (fConst9 + -6.4344317434698802e-16)) + 3.2623424697545702e-55);
	fConst32 = ((fConst0 * (fConst11 + -1.63110208134281e-12)) + -1.69410806769336e-10);
	fConst33 = ((fConst0 * (fConst13 + -7.4421674350198897e-12)) + -3.2160747437094799e-11);
	fConst34 = ((fConst0 * (7.4478704182697307e-12 - fConst15)) + 3.2172158717349402e-11);
	fConst35 = ((fConst0 * (1.61641996632585e-12 - fConst17)) + 1.6091784998802001e-10);
	fConst36 = ((fConst0 * (fConst19 + -3.2183569997603901e-15)) + 1.5333557259551101e-54);
	fConst37 = (fConst21 + 7.6075416727176396e-56);
	fConst38 = (-7.1771534334600597e-56 - fConst23);
	fConst39 = (7.0753644361608499e-12 - fConst25);
	fConst40 = (fConst27 + -7.0778749178168597e-12);
	double fConst41 = (1.1177069911303999e-19 * fConst0);
	fConst42 = ((fConst0 * (fConst41 + -3.24149709132582e-15)) + 1.4628895453456301e-14);
	double fConst43 = (1.4239228869348599e-16 * fConst0);
	fConst44 = ((fConst0 * (fConst43 + -6.4321494874189598e-16)) + -3.45797348759893e-55);
	double fConst45 = (1.42504059392599e-16 * fConst0);
	fConst46 = ((fConst0 * (6.4344317434698802e-16 - fConst45)) + 3.2623424697545702e-55);
	double fConst47 = (5.6049652484216404e-17 * fConst0);
	fConst48 = ((fConst0 * (1.63110208134281e-12 - fConst47)) + -1.69410806769336e-10);
	double fConst49 = (7.1405461011122294e-14 * fConst0);
	fConst50 = ((fConst0 * (7.4421674350198897e-12 - fConst49)) + -3.2160747437094799e-11);
	double fConst51 = (7.1461510663606604e-14 * fConst0);
	fConst52 = ((fConst0 * (fConst51 + -7.4478704182697307e-12)) + 3.2172158717349402e-11);
	double fConst53 = (2.5178624720752199e-17 * fConst0);
	fConst54 = ((fConst0 * (fConst53 + -1.61641996632585e-12)) + 1.6091784998802001e-10);
	double fConst55 = (5.0209633120131098e-20 * fConst0);
	fConst56 = ((fConst0 * (3.2183569997603901e-15 - fConst55)) + 1.5333557259551101e-54);
	double fConst57 = (1.4150728872321699e-16 * fConst0);
	fConst58 = (-7.6075416727176396e-56 - fConst57);
	double fConst59 = (1.4155749835633699e-16 * fConst0);
	fConst60 = (fConst59 + 7.1771534334600597e-56);
	double fConst61 = (7.0961660076031701e-14 * fConst0);
	fConst62 = (fConst61 + -7.0753644361608499e-12);
	double fConst63 = (7.0986838700752397e-14 * fConst0);
	fConst64 = (7.0778749178168597e-12 - fConst63);
	fConst65 = ((fConst0 * (-3.24149709132582e-15 - fConst41)) + -1.4628895453456301e-14);
	fConst66 = ((fConst0 * (-6.4321494874189598e-16 - fConst43)) + 3.45797348759893e-55);
	fConst67 = ((fConst0 * (fConst45 + 6.4344317434698802e-16)) + -3.2623424697545702e-55);
	fConst68 = ((fConst0 * (fConst47 + 1.63110208134281e-12)) + 1.69410806769336e-10);
	fConst69 = ((fConst0 * (fConst49 + 7.4421674350198897e-12)) + 3.2160747437094799e-11);
	fConst70 = ((fConst0 * (-7.4478704182697307e-12 - fConst51)) + -3.2172158717349402e-11);
	fConst71 = ((fConst0 * (-1.61641996632585e-12 - fConst53)) + -1.6091784998802001e-10);
	fConst72 = ((fConst0 * (fConst55 + 3.2183569997603901e-15)) + -1.5333557259551101e-54);
	fConst73 = (fConst57 + -7.6075416727176396e-56);
	fConst74 = (7.1771534334600597e-56 - fConst59);
	fConst75 = (-7.0753644361608499e-12 - fConst61);
	fConst76 = (fConst63 + 7.0778749178168597e-12);
	double fConst77 = (2.0681037922594001e-13 * fConst0);
	fConst78 = (fConst77 + 4.7473961557966103e-12);
	double fConst79 = (1.4068733280676199e-13 * fConst0);
	fConst80 = (-3.22952119441946e-12 - fConst79);
	double fConst81 = (1.1254986624540899e-13 * fConst0);
	fConst82 = (fConst81 + 2.5836169555355699e-12);
	double fConst83 = (1.6544830338075201e-13 * fConst0);
	fConst84 = (-3.7979169246372897e-12 - fConst83);
	double fConst85 = (6.2043113767781895e-13 * fConst0);
	fConst86 = (-4.7473961557966103e-12 - fConst85);
	double fConst87 = (4.2206199842028502e-13 * fConst0);
	fConst88 = (fConst87 + 3.22952119441946e-12);
	double fConst89 = (3.3764959873622802e-13 * fConst0);
	fConst90 = (-2.5836169555355699e-12 - fConst89);
	double fConst91 = (4.9634491014225504e-13 * fConst0);
	fConst92 = (fConst91 + 3.7979169246372897e-12);
	fConst93 = (fConst85 + -4.7473961557966103e-12);
	fConst94 = (3.22952119441946e-12 - fConst87);
	fConst95 = (fConst89 + -2.5836169555355699e-12);
	fConst96 = (3.7979169246372897e-12 - fConst91);
	fConst97 = (4.7473961557966103e-12 - fConst77);
	fConst98 = (fConst79 + -3.22952119441946e-12);
	fConst99 = (2.5836169555355699e-12 - fConst81);
	fConst100 = (fConst83 + -3.7979169246372897e-12);
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
	double fSlow0 = (0.0070000000000000062 * (1.0 - double(fVslider0)));
	double fSlow1 = (0.0070000000000000062 * (1.0 - double(fVslider1)));
	double fSlow2 = (0.0070000000000000062 * double(fVslider2));
	double fSlow3 = (0.0070000000000000062 * (1.0 - double(fVslider3)));
	for (int i0 = 0; (i0 < count); i0 = (i0 + 1)) {
		fRec9[0] = (fSlow0 + (0.99299999999999999 * fRec9[1]));
		fRec10[0] = (fSlow1 + (0.99299999999999999 * fRec10[1]));
		fRec11[0] = (fSlow2 + (0.99299999999999999 * fRec11[1]));
		double fTemp0 = (((fRec9[0] * ((fConst0 * (fConst65 + (fRec10[0] * (fConst66 + (fConst67 * fRec10[0]))))) + 6.9697987543413902e-54)) + (fConst0 * (fConst68 + ((fRec10[0] * (fConst69 + (fConst70 * fRec10[0]))) + (fRec11[0] * (fConst71 + ((fRec9[0] * (fConst72 + (fConst0 * (fRec10[0] * (fConst73 + (fConst74 * fRec10[0])))))) + (fConst0 * (fRec10[0] * (fConst75 + (fConst76 * fRec10[0]))))))))))) + 7.3144477267281697e-10);
		fRec8[0] = (double(input0[i0]) - ((((fRec8[1] * (((fRec9[0] * ((fConst0 * (fConst6 + (fRec10[0] * (fConst8 + (fConst10 * fRec10[0]))))) + 2.0909396263024202e-53)) + (fConst0 * (fConst12 + ((fRec10[0] * (fConst14 + (fConst16 * fRec10[0]))) + (fRec11[0] * (fConst18 + ((fRec9[0] * (fConst20 + (fConst0 * (fRec10[0] * (fConst22 + (fConst24 * fRec10[0])))))) + (fConst0 * (fRec10[0] * (fConst26 + (fConst28 * fRec10[0]))))))))))) + 2.19433431801845e-09)) + (fRec8[2] * (((fRec9[0] * ((fConst0 * (fConst29 + (fRec10[0] * (fConst30 + (fConst31 * fRec10[0]))))) + 2.0909396263024202e-53)) + (fConst0 * (fConst32 + ((fRec10[0] * (fConst33 + (fConst34 * fRec10[0]))) + (fRec11[0] * (fConst35 + ((fRec9[0] * (fConst36 + (fConst0 * (fRec10[0] * (fConst37 + (fConst38 * fRec10[0])))))) + (fConst0 * (fRec10[0] * (fConst39 + (fConst40 * fRec10[0]))))))))))) + 2.19433431801845e-09))) + (fRec8[3] * (((fRec9[0] * ((fConst0 * (fConst42 + (fRec10[0] * (fConst44 + (fConst46 * fRec10[0]))))) + 6.9697987543413902e-54)) + (fConst0 * (fConst48 + ((fRec10[0] * (fConst50 + (fConst52 * fRec10[0]))) + (fRec11[0] * (fConst54 + ((fRec9[0] * (fConst56 + (fConst0 * (fRec10[0] * (fConst58 + (fConst60 * fRec10[0])))))) + (fConst0 * (fRec10[0] * (fConst62 + (fConst64 * fRec10[0]))))))))))) + 7.3144477267281697e-10))) / fTemp0));
		fRec12[0] = (fSlow3 + (0.99299999999999999 * fRec12[1]));
		double fTemp1 = (1.1292797981557601e-15 * fRec12[0]);
		double fTemp2 = (1.1142058644725399e-13 * fRec12[0]);
		double fTemp3 = (1.6378826207746301e-13 * fRec12[0]);
		double fTemp4 = (1.66004130328897e-15 * fRec12[0]);
		double fTemp5 = (3.34261759341761e-13 * fRec12[0]);
		double fTemp6 = (3.3878393944672901e-15 * fRec12[0]);
		double fTemp7 = (4.9801239098669099e-15 * fRec12[0]);
		double fTemp8 = (4.9136478623238799e-13 * fRec12[0]);
		double fTemp9 = (((((fRec8[0] * (fConst78 + (((fRec9[0] * (fConst80 + ((fConst0 * (fRec10[0] * (((fRec10[0] * ((0.0 - fTemp1) + 1.4115997476947001e-15)) - fTemp2) + 1.3927573305906699e-13))) + (fConst82 * fRec12[0])))) + (fConst0 * (fRec10[0] * ((fTemp3 + (fRec10[0] * (fTemp4 + -2.0750516291112099e-15))) + -2.0473532759682801e-13)))) + (fConst84 * fRec12[0])))) + (fRec8[1] * (fConst86 + (((fRec9[0] * (fConst88 + ((fConst0 * (fRec10[0] * ((fTemp5 + (fRec10[0] * (fTemp6 + -4.2347992430841103e-15))) + -4.1782719917720101e-13))) + (fConst90 * fRec12[0])))) + (fConst0 * (fRec10[0] * (((fRec10[0] * ((0.0 - fTemp7) + 6.2251548873336404e-15)) - fTemp8) + 6.1420598279048502e-13)))) + (fConst92 * fRec12[0]))))) + (fRec8[2] * (fConst93 + (((fRec9[0] * (fConst94 + ((fConst0 * (fRec10[0] * (((fRec10[0] * ((0.0 - fTemp6) + 4.2347992430841103e-15)) - fTemp5) + 4.1782719917720101e-13))) + (fConst95 * fRec12[0])))) + (fConst0 * (fRec10[0] * ((fTemp8 + (fRec10[0] * (fTemp7 + -6.2251548873336404e-15))) + -6.1420598279048502e-13)))) + (fConst96 * fRec12[0]))))) + (fRec8[3] * (fConst97 + (((fRec9[0] * (fConst98 + ((fConst0 * (fRec10[0] * ((fTemp2 + (fRec10[0] * (fTemp1 + -1.4115997476947001e-15))) + -1.3927573305906699e-13))) + (fConst99 * fRec12[0])))) + (fConst0 * (fRec10[0] * (((fRec10[0] * ((0.0 - fTemp4) + 2.0750516291112099e-15)) - fTemp3) + 2.0473532759682801e-13)))) + (fConst100 * fRec12[0]))))) / fTemp0);
		fVec0[0] = fTemp9;
		fRec7[0] = ((fConst4 * (fTemp9 + fVec0[1])) - (0.86056958506478287 * fRec7[1]));
		fRec6[0] = (fRec7[0] - ((1.8405051250752198 * fRec6[1]) + (0.86129424393186271 * fRec6[2])));
		double fTemp10 = ((1.8508996845035413 * fRec6[1]) + (0.92544984225177063 * (fRec6[0] + fRec6[2])));
		double fTemp11 = double(Ftrany(int(TRANY_TABLE_KT88_68k), double(((fTemp10 + (2700.0 * (fTemp10 / (double(Rtrany(int(TRANY_TABLE_KT88_68k), double(fRec5[1]))) + 100000.0)))) + -5.5628950000000001))));
		fRec5[0] = ((fTemp11 + (0.0020603314814814817 * (double(Rtrany(int(TRANY_TABLE_KT88_68k), double(fTemp11))) + 100000.0))) + -250.0);
		fRec4[0] = (fConst2 * ((fConst3 * fRec4[1]) + (0.025000000000000001 * (fRec5[0] - fRec5[1]))));
		fRec3[0] = ((0.93028479253239138 * (fRec4[0] + fRec4[1])) - (0.86056958506478287 * fRec3[1]));
		fRec2[0] = (fRec3[0] - ((1.8405051250752198 * fRec2[1]) + (0.86129424393186271 * fRec2[2])));
		double fTemp12 = ((1.8508996845035413 * fRec2[1]) + (0.92544984225177063 * (fRec2[0] + fRec2[2])));
		double fTemp13 = double(Ftrany(int(TRANY_TABLE_KT88_68k), double(((fTemp12 + (2700.0 * (fTemp12 / (double(Rtrany(int(TRANY_TABLE_KT88_68k), double(fRec1[1]))) + 100000.0)))) + -5.5628950000000001))));
		fRec1[0] = ((fTemp13 + (0.0020603314814814817 * (double(Rtrany(int(TRANY_TABLE_KT88_68k), double(fTemp13))) + 100000.0))) + -250.0);
		fRec0[0] = (fConst2 * ((fConst3 * fRec0[1]) + (0.025000000000000001 * (fRec1[0] - fRec1[1]))));
		output0[i0] = FAUSTFLOAT(fRec0[0]);
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
