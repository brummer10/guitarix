// generated from file '../src/plugins/fuzzfacefm.dsp' by dsp2cc:
// Code generated with Faust 2.15.11 (https://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

#include "clipping.h"

namespace pluginlib {
namespace fuzzfacefm {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT fVslider0;
	double fRec1[2];
	double fConst0;
	double fConst1;
	double fConst2;
	FAUSTFLOAT fVslider1;
	double fRec2[2];
	double fConst3;
	double fConst4;
	double fConst5;
	double fConst6;
	double fConst7;
	double fConst8;
	double fConst9;
	double fConst10;
	double fConst11;
	double fConst12;
	FAUSTFLOAT fVslider2;
	double fRec3[2];
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
	double fRec0[4];
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
	double fConst102;
	double fConst103;
	double fConst104;


	int samplingFreq;
	gx_resample::FixedRateResampler smpCl;

	FAUSTFLOAT 	fsliderV0;
	double 	fRecV0[2];
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
	id = "fuzzfacefm";
	name = N_("Fuzz Face Fuller");
	groups = 0;
	description = N_("Micke Fuller Fuzz Face simulation"); // description (tooltip)
	category = N_("Fuzz");       // category
	shortname = N_("FF Fuller");     // shortname
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
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec2[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec3[l2] = 0.0;
	for (int l3 = 0; (l3 < 4); l3 = (l3 + 1)) fRec0[l3] = 0.0;


	for (int i=0; i<2; i++) fRecV0[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSamplingFreq)));
	fConst1 = (3.3531209733912099e-19 * fConst0);
	fConst2 = (((fConst1 + 3.24149709132582e-15) * fConst0) + -1.4628895453456301e-14);
	fConst3 = (4.2717686608045702e-16 * fConst0);
	fConst4 = (((fConst3 + 6.4321494874189598e-16) * fConst0) + 3.45797348759893e-55);
	fConst5 = (4.27512178177797e-16 * fConst0);
	fConst6 = (((-6.4344317434698802e-16 - fConst5) * fConst0) + -3.2623424697545702e-55);
	fConst7 = (1.6814895745264899e-16 * fConst0);
	fConst8 = (((-1.63110208134281e-12 - fConst7) * fConst0) + 1.69410806769336e-10);
	fConst9 = (2.1421638303336699e-13 * fConst0);
	fConst10 = (((-7.4421674350198897e-12 - fConst9) * fConst0) + 3.2160747437094799e-11);
	fConst11 = (2.1438453199081999e-13 * fConst0);
	fConst12 = (((fConst11 + 7.4478704182697307e-12) * fConst0) + -3.2172158717349402e-11);
	fConst13 = (7.5535874162256398e-17 * fConst0);
	fConst14 = (((fConst13 + 1.61641996632585e-12) * fConst0) + -1.6091784998802001e-10);
	fConst15 = (1.5062889936039299e-19 * fConst0);
	fConst16 = (((-3.2183569997603901e-15 - fConst15) * fConst0) + -1.5333557259551101e-54);
	fConst17 = (4.2452186616965102e-16 * fConst0);
	fConst18 = (7.6075416727176396e-56 - fConst17);
	fConst19 = (4.2467249506901202e-16 * fConst0);
	fConst20 = (fConst19 + -7.1771534334600597e-56);
	fConst21 = (2.1288498022809499e-13 * fConst0);
	fConst22 = (fConst21 + 7.0753644361608499e-12);
	fConst23 = (2.1296051610225699e-13 * fConst0);
	fConst24 = (-7.0778749178168597e-12 - fConst23);
	fConst25 = (((3.24149709132582e-15 - fConst1) * fConst0) + 1.4628895453456301e-14);
	fConst26 = (((6.4321494874189598e-16 - fConst3) * fConst0) + -3.45797348759893e-55);
	fConst27 = (((fConst5 + -6.4344317434698802e-16) * fConst0) + 3.2623424697545702e-55);
	fConst28 = (((fConst7 + -1.63110208134281e-12) * fConst0) + -1.69410806769336e-10);
	fConst29 = (((fConst9 + -7.4421674350198897e-12) * fConst0) + -3.2160747437094799e-11);
	fConst30 = (((7.4478704182697307e-12 - fConst11) * fConst0) + 3.2172158717349402e-11);
	fConst31 = (((1.61641996632585e-12 - fConst13) * fConst0) + 1.6091784998802001e-10);
	fConst32 = (((fConst15 + -3.2183569997603901e-15) * fConst0) + 1.5333557259551101e-54);
	fConst33 = (fConst17 + 7.6075416727176396e-56);
	fConst34 = (-7.1771534334600597e-56 - fConst19);
	fConst35 = (7.0753644361608499e-12 - fConst21);
	fConst36 = (fConst23 + -7.0778749178168597e-12);
	fConst37 = (1.1177069911303999e-19 * fConst0);
	fConst38 = (((fConst37 + -3.24149709132582e-15) * fConst0) + 1.4628895453456301e-14);
	fConst39 = (1.4239228869348599e-16 * fConst0);
	fConst40 = (((fConst39 + -6.4321494874189598e-16) * fConst0) + -3.45797348759893e-55);
	fConst41 = (1.42504059392599e-16 * fConst0);
	fConst42 = (((6.4344317434698802e-16 - fConst41) * fConst0) + 3.2623424697545702e-55);
	fConst43 = (5.6049652484216404e-17 * fConst0);
	fConst44 = (((1.63110208134281e-12 - fConst43) * fConst0) + -1.69410806769336e-10);
	fConst45 = (7.1405461011122294e-14 * fConst0);
	fConst46 = (((7.4421674350198897e-12 - fConst45) * fConst0) + -3.2160747437094799e-11);
	fConst47 = (7.1461510663606604e-14 * fConst0);
	fConst48 = (((fConst47 + -7.4478704182697307e-12) * fConst0) + 3.2172158717349402e-11);
	fConst49 = (2.5178624720752199e-17 * fConst0);
	fConst50 = (((fConst49 + -1.61641996632585e-12) * fConst0) + 1.6091784998802001e-10);
	fConst51 = (5.0209633120131098e-20 * fConst0);
	fConst52 = (((3.2183569997603901e-15 - fConst51) * fConst0) + 1.5333557259551101e-54);
	fConst53 = (1.4150728872321699e-16 * fConst0);
	fConst54 = (-7.6075416727176396e-56 - fConst53);
	fConst55 = (1.4155749835633699e-16 * fConst0);
	fConst56 = (fConst55 + 7.1771534334600597e-56);
	fConst57 = (7.0961660076031701e-14 * fConst0);
	fConst58 = (fConst57 + -7.0753644361608499e-12);
	fConst59 = (7.0986838700752397e-14 * fConst0);
	fConst60 = (7.0778749178168597e-12 - fConst59);
	fConst61 = (((-3.24149709132582e-15 - fConst37) * fConst0) + -1.4628895453456301e-14);
	fConst62 = (((-6.4321494874189598e-16 - fConst39) * fConst0) + 3.45797348759893e-55);
	fConst63 = (((fConst41 + 6.4344317434698802e-16) * fConst0) + -3.2623424697545702e-55);
	fConst64 = (((fConst43 + 1.63110208134281e-12) * fConst0) + 1.69410806769336e-10);
	fConst65 = (((fConst45 + 7.4421674350198897e-12) * fConst0) + 3.2160747437094799e-11);
	fConst66 = (((-7.4478704182697307e-12 - fConst47) * fConst0) + -3.2172158717349402e-11);
	fConst67 = (((-1.61641996632585e-12 - fConst49) * fConst0) + -1.6091784998802001e-10);
	fConst68 = (((fConst51 + 3.2183569997603901e-15) * fConst0) + -1.5333557259551101e-54);
	fConst69 = (fConst53 + -7.6075416727176396e-56);
	fConst70 = (7.1771534334600597e-56 - fConst55);
	fConst71 = (-7.0753644361608499e-12 - fConst57);
	fConst72 = (fConst59 + 7.0778749178168597e-12);
	fConst73 = mydsp_faustpower3_f(fConst0);
	fConst74 = (0.0 - (4.1501032582223993e-16 * fConst73));
	fConst75 = (4.0947065519365001e-14 * fConst73);
	fConst76 = mydsp_faustpower2_f(fConst0);
	fConst77 = (2.0681037922594001e-13 * fConst0);
	fConst78 = (fConst77 + 4.7473961557966103e-12);
	fConst79 = (1.6544830338075201e-13 * fConst0);
	fConst80 = (-3.7979169246372897e-12 - fConst79);
	fConst81 = (1.4068733280676199e-13 * fConst0);
	fConst82 = (-3.22952119441946e-12 - fConst81);
	fConst83 = (1.1254986624540899e-13 * fConst0);
	fConst84 = (fConst83 + 2.5836169555355699e-12);
	fConst85 = (4.2206199842028502e-13 * fConst0);
	fConst86 = (3.3764959873622802e-13 * fConst0);
	fConst87 = (((fConst85 + 3.22952119441946e-12) + (-2.5836169555355699e-12 - fConst86)) * fConst76);
	fConst88 = (0.0 - (8.4695984861682025e-16 * fConst73));
	fConst89 = (8.356543983544001e-14 * fConst73);
	fConst90 = (6.2043113767781895e-13 * fConst0);
	fConst91 = (-4.7473961557966103e-12 - fConst90);
	fConst92 = (4.9634491014225504e-13 * fConst0);
	fConst93 = (fConst92 + 3.7979169246372897e-12);
	fConst94 = (0.0 - (1.2450309774667304e-15 * fConst73));
	fConst95 = (1.2284119655809702e-13 * fConst73);
	fConst96 = (fConst90 + -4.7473961557966103e-12);
	fConst97 = (3.7979169246372897e-12 - fConst92);
	fConst98 = (3.22952119441946e-12 - fConst85);
	fConst99 = (fConst86 + -2.5836169555355699e-12);
	fConst100 = (((2.5836169555355699e-12 - fConst83) + (fConst81 + -3.22952119441946e-12)) * fConst76);
	fConst101 = (0.0 - (2.8231994953894002e-16 * fConst73));
	fConst102 = (2.7855146611813e-14 * fConst73);
	fConst103 = (4.7473961557966103e-12 - fConst77);
	fConst104 = (fConst79 + -3.7979169246372897e-12);
	fVslider0 = FAUSTFLOAT(0.5);
	fVslider1 = FAUSTFLOAT(0.5);
	fVslider2 = FAUSTFLOAT(0.5);

	samplingFreq = 96000;
	smpCl.setup(fSamplingFreq, samplingFreq);
	fSamplingFreq = samplingFreq;

	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlowV0 = (0.0010000000000000009 * double(fsliderV0));

	double fSlow0 = (0.0070000000000000062 * (1.0 - double(fVslider0)));
	double fSlow1 = (0.0070000000000000062 * (1.0 - double(fVslider1)));
	double fSlow2 = (0.0070000000000000062 * double(fVslider2));
	for (int i = 0; (i < count); i = (i + 1)) {
		fRec1[0] = (fSlow0 + (0.99299999999999999 * fRec1[1]));
		fRec2[0] = (fSlow1 + (0.99299999999999999 * fRec2[1]));
		fRec3[0] = (fSlow2 + (0.99299999999999999 * fRec3[1]));
		double fTemp0 = (((fRec1[0] * ((fConst0 * (fConst61 + (fRec2[0] * (fConst62 + (fConst63 * fRec2[0]))))) + 6.9697987543413902e-54)) + (fConst0 * (fConst64 + ((fRec2[0] * (fConst65 + (fConst66 * fRec2[0]))) + (fRec3[0] * (fConst67 + ((fRec1[0] * (fConst68 + (fConst0 * (fRec2[0] * (fConst69 + (fConst70 * fRec2[0])))))) + (fConst0 * (fRec2[0] * (fConst71 + (fConst72 * fRec2[0]))))))))))) + 7.3144477267281697e-10);
		fRec0[0] = (double(input0[i]) - ((((fRec0[1] * (((fRec1[0] * ((fConst0 * (fConst2 + (fRec2[0] * (fConst4 + (fConst6 * fRec2[0]))))) + 2.0909396263024202e-53)) + (fConst0 * (fConst8 + ((fRec2[0] * (fConst10 + (fConst12 * fRec2[0]))) + (fRec3[0] * (fConst14 + ((fRec1[0] * (fConst16 + (fConst0 * (fRec2[0] * (fConst18 + (fConst20 * fRec2[0])))))) + (fConst0 * (fRec2[0] * (fConst22 + (fConst24 * fRec2[0]))))))))))) + 2.19433431801845e-09)) + (fRec0[2] * (((fRec1[0] * ((fConst0 * (fConst25 + (fRec2[0] * (fConst26 + (fConst27 * fRec2[0]))))) + 2.0909396263024202e-53)) + (fConst0 * (fConst28 + ((fRec2[0] * (fConst29 + (fConst30 * fRec2[0]))) + (fRec3[0] * (fConst31 + ((fRec1[0] * (fConst32 + (fConst0 * (fRec2[0] * (fConst33 + (fConst34 * fRec2[0])))))) + (fConst0 * (fRec2[0] * (fConst35 + (fConst36 * fRec2[0]))))))))))) + 2.19433431801845e-09))) + (fRec0[3] * (((fRec1[0] * ((fConst0 * (fConst38 + (fRec2[0] * (fConst40 + (fConst42 * fRec2[0]))))) + 6.9697987543413902e-54)) + (fConst0 * (fConst44 + ((fRec2[0] * (fConst46 + (fConst48 * fRec2[0]))) + (fRec3[0] * (fConst50 + ((fRec1[0] * (fConst52 + (fConst0 * (fRec2[0] * (fConst54 + (fConst56 * fRec2[0])))))) + (fConst0 * (fRec2[0] * (fConst58 + (fConst60 * fRec2[0]))))))))))) + 7.3144477267281697e-10))) / fTemp0));
		output0[i] = FAUSTFLOAT((((((fRec0[0] * ((fRec2[0] * ((fConst74 * fRec2[0]) - fConst75)) + (fConst76 * (fConst78 + (fConst80 + (fRec1[0] * (fConst82 + (fConst84 + (fConst0 * (fRec2[0] * (((2.8231994953894002e-16 * fRec2[0]) + -1.1142058644725399e-13) + 1.3927573305906699e-13))))))))))) + (fRec0[1] * ((fRec1[0] * (fConst87 + (fRec2[0] * ((fConst88 * fRec2[0]) - fConst89)))) + (fConst76 * (fConst91 + (fConst93 + (fConst0 * (fRec2[0] * (((1.2450309774667304e-15 * fRec2[0]) + -4.9136478623238799e-13) + 6.1420598279048502e-13))))))))) + (fRec0[2] * ((fRec2[0] * ((fConst94 * fRec2[0]) - fConst95)) + (fConst76 * (fConst96 + (fConst97 + (fRec1[0] * (fConst98 + (fConst99 + (fConst0 * (fRec2[0] * (((8.4695984861682025e-16 * fRec2[0]) + -3.34261759341761e-13) + 4.1782719917720101e-13)))))))))))) + (fRec0[3] * ((fRec1[0] * (fConst100 + (fRec2[0] * ((fConst101 * fRec2[0]) - fConst102)))) + (fConst76 * (fConst103 + (fConst104 + (fConst0 * (fRec2[0] * (((4.1501032582223993e-16 * fRec2[0]) + -1.6378826207746301e-13) + 2.0473532759682801e-13))))))))) / fTemp0));
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		for (int j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
			fRec0[j0] = fRec0[(j0 - 1)];
		}
	}

	FAUSTFLOAT bufCl[smpCl.max_out_count(count)];
	int ReCount = smpCl.up(count, output0, bufCl);
	for (int i = 0; (i < ReCount); i = (i + 1)) {
		bufCl[i] = FAUSTFLOAT(double(asymclip4(double(double(bufCl[i])))));
	}
	smpCl.down(bufCl, output0);

	for (int i=0; i<count; i++) {
		fRecV0[0] = ((0.999 * fRecV0[1]) + fSlowV0);
		output0[i] = (FAUSTFLOAT)((double)output0[i] * fRecV0[0]);
		// post processing
		fRecV0[1] = fRecV0[0];
	}

}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("fuzzfacefm.Level",N_("Level"),"S","",&fsliderV0, 0.5, 0.0, 1, 0.01);
	reg.registerVar("fuzzfacefm.Drive",N_("Drive"),"S","",&fVslider0, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("fuzzfacefm.Fuzz",N_("Fuzz"),"S","",&fVslider1, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("fuzzfacefm.Input",N_("Input"),"S","",&fVslider2, 0.5, 0.0, 1.0, 0.01);
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
                        <property name=\"var_id\">fuzzfacefm.Input</property>\n\
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
                      <object class=\"GxSmallKnobR\" id=\"gxbigknob2\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">fuzzfacefm.Drive</property>\n\
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
                        <property name=\"var_id\">fuzzfacefm.Fuzz</property>\n\
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
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox5\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label4:rack_label\">\n\
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
                      <object class=\"GxMidKnob\" id=\"gxbigknob4\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">fuzzfacefm.Level</property>\n\
                        <property name=\"label_ref\">label4:rack_label</property>\n\
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
                <property name=\"var_id\">fuzzfacefm.Level</property>\n\
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
