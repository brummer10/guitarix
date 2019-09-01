// generated from file '../src/plugins/zita_rev1.dsp' by dsp2cc:
// Code generated with Faust 2.15.11 (https://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

namespace pluginlib {
namespace zita_rev1 {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT fVslider0;
	double fRec0[2];
	int IOTA;
	double fVec0[16384];
	double fConst0;
	double fConst1;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT fVslider4;
	FAUSTFLOAT fVslider5;
	double fConst2;
	double fConst3;
	FAUSTFLOAT fVslider6;
	FAUSTFLOAT fVslider7;
	double fConst4;
	FAUSTFLOAT fVslider8;
	double fRec14[2];
	double fRec13[2];
	double fVec1[32768];
	double fConst5;
	int iConst6;
	double fVec2[16384];
	double fConst7;
	FAUSTFLOAT fVslider9;
	double fVec3[2048];
	int iConst8;
	double fRec11[2];
	double fConst9;
	double fConst10;
	double fRec18[2];
	double fRec17[2];
	double fVec4[32768];
	double fConst11;
	int iConst12;
	double fVec5[4096];
	int iConst13;
	double fRec15[2];
	double fConst14;
	double fConst15;
	double fRec22[2];
	double fRec21[2];
	double fVec6[16384];
	double fConst16;
	int iConst17;
	double fVec7[4096];
	int iConst18;
	double fRec19[2];
	double fConst19;
	double fConst20;
	double fRec26[2];
	double fRec25[2];
	double fVec8[32768];
	double fConst21;
	int iConst22;
	double fVec9[4096];
	int iConst23;
	double fRec23[2];
	double fConst24;
	double fConst25;
	double fRec30[2];
	double fRec29[2];
	double fVec10[16384];
	double fConst26;
	int iConst27;
	double fVec11[2048];
	int iConst28;
	double fRec27[2];
	double fConst29;
	double fConst30;
	double fRec34[2];
	double fRec33[2];
	double fVec12[16384];
	double fConst31;
	int iConst32;
	double fVec13[4096];
	int iConst33;
	double fRec31[2];
	double fConst34;
	double fConst35;
	double fRec38[2];
	double fRec37[2];
	double fVec14[16384];
	double fConst36;
	int iConst37;
	double fVec15[4096];
	int iConst38;
	double fRec35[2];
	double fConst39;
	double fConst40;
	double fRec42[2];
	double fRec41[2];
	double fVec16[16384];
	double fConst41;
	int iConst42;
	double fVec17[2048];
	int iConst43;
	double fRec39[2];
	double fRec3[3];
	double fRec4[3];
	double fRec5[3];
	double fRec6[3];
	double fRec7[3];
	double fRec8[3];
	double fRec9[3];
	double fRec10[3];
	double fRec2[3];
	double fRec1[3];
	FAUSTFLOAT fVslider10;
	double fRec43[2];
	double fRec45[3];
	double fRec44[3];

	void clear_state_f();
	int load_ui_f(const UiBuilder& b, int form);
	static const char *glade_def;
	void init(unsigned int samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static int load_ui_f_static(const UiBuilder& b, int form);
	static void init_static(unsigned int samplingFreq, PluginDef*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginDef*);
	static int register_params_static(const ParamReg& reg);
	static void del_instance(PluginDef *p);
public:
	Dsp();
	~Dsp();
};



static const char* parm_groups[] = {
	"decay_times", N_("Decay Times in Bands"),
	"equalizer1", N_("RM Peaking Equalizer 1"),
	"equalizer2", N_("RM Peaking Equalizer 2"),
	"input", N_("Input"),
	"output", N_("Output"),
	0
	};

Dsp::Dsp()
	: PluginDef() {
	version = PLUGINDEF_VERSION;
	flags = 0;
	id = "zita_rev1";
	name = N_("Zita Rev1");
	groups = parm_groups;
	description = ""; // description (tooltip)
	category = N_("Reverb");       // category
	shortname = "";     // shortname
	mono_audio = 0;
	stereo_audio = compute_static;
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec0[l0] = 0.0;
	for (int l1 = 0; (l1 < 16384); l1 = (l1 + 1)) fVec0[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec14[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fRec13[l3] = 0.0;
	for (int l4 = 0; (l4 < 32768); l4 = (l4 + 1)) fVec1[l4] = 0.0;
	for (int l5 = 0; (l5 < 16384); l5 = (l5 + 1)) fVec2[l5] = 0.0;
	for (int l6 = 0; (l6 < 2048); l6 = (l6 + 1)) fVec3[l6] = 0.0;
	for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) fRec11[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fRec18[l8] = 0.0;
	for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) fRec17[l9] = 0.0;
	for (int l10 = 0; (l10 < 32768); l10 = (l10 + 1)) fVec4[l10] = 0.0;
	for (int l11 = 0; (l11 < 4096); l11 = (l11 + 1)) fVec5[l11] = 0.0;
	for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) fRec15[l12] = 0.0;
	for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) fRec22[l13] = 0.0;
	for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) fRec21[l14] = 0.0;
	for (int l15 = 0; (l15 < 16384); l15 = (l15 + 1)) fVec6[l15] = 0.0;
	for (int l16 = 0; (l16 < 4096); l16 = (l16 + 1)) fVec7[l16] = 0.0;
	for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) fRec19[l17] = 0.0;
	for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) fRec26[l18] = 0.0;
	for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) fRec25[l19] = 0.0;
	for (int l20 = 0; (l20 < 32768); l20 = (l20 + 1)) fVec8[l20] = 0.0;
	for (int l21 = 0; (l21 < 4096); l21 = (l21 + 1)) fVec9[l21] = 0.0;
	for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) fRec23[l22] = 0.0;
	for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) fRec30[l23] = 0.0;
	for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) fRec29[l24] = 0.0;
	for (int l25 = 0; (l25 < 16384); l25 = (l25 + 1)) fVec10[l25] = 0.0;
	for (int l26 = 0; (l26 < 2048); l26 = (l26 + 1)) fVec11[l26] = 0.0;
	for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) fRec27[l27] = 0.0;
	for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) fRec34[l28] = 0.0;
	for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) fRec33[l29] = 0.0;
	for (int l30 = 0; (l30 < 16384); l30 = (l30 + 1)) fVec12[l30] = 0.0;
	for (int l31 = 0; (l31 < 4096); l31 = (l31 + 1)) fVec13[l31] = 0.0;
	for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) fRec31[l32] = 0.0;
	for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) fRec38[l33] = 0.0;
	for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) fRec37[l34] = 0.0;
	for (int l35 = 0; (l35 < 16384); l35 = (l35 + 1)) fVec14[l35] = 0.0;
	for (int l36 = 0; (l36 < 4096); l36 = (l36 + 1)) fVec15[l36] = 0.0;
	for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) fRec35[l37] = 0.0;
	for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) fRec42[l38] = 0.0;
	for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) fRec41[l39] = 0.0;
	for (int l40 = 0; (l40 < 16384); l40 = (l40 + 1)) fVec16[l40] = 0.0;
	for (int l41 = 0; (l41 < 2048); l41 = (l41 + 1)) fVec17[l41] = 0.0;
	for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) fRec39[l42] = 0.0;
	for (int l43 = 0; (l43 < 3); l43 = (l43 + 1)) fRec3[l43] = 0.0;
	for (int l44 = 0; (l44 < 3); l44 = (l44 + 1)) fRec4[l44] = 0.0;
	for (int l45 = 0; (l45 < 3); l45 = (l45 + 1)) fRec5[l45] = 0.0;
	for (int l46 = 0; (l46 < 3); l46 = (l46 + 1)) fRec6[l46] = 0.0;
	for (int l47 = 0; (l47 < 3); l47 = (l47 + 1)) fRec7[l47] = 0.0;
	for (int l48 = 0; (l48 < 3); l48 = (l48 + 1)) fRec8[l48] = 0.0;
	for (int l49 = 0; (l49 < 3); l49 = (l49 + 1)) fRec9[l49] = 0.0;
	for (int l50 = 0; (l50 < 3); l50 = (l50 + 1)) fRec10[l50] = 0.0;
	for (int l51 = 0; (l51 < 3); l51 = (l51 + 1)) fRec2[l51] = 0.0;
	for (int l52 = 0; (l52 < 3); l52 = (l52 + 1)) fRec1[l52] = 0.0;
	for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) fRec43[l53] = 0.0;
	for (int l54 = 0; (l54 < 3); l54 = (l54 + 1)) fRec45[l54] = 0.0;
	for (int l55 = 0; (l55 < 3); l55 = (l55 + 1)) fRec44[l55] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSamplingFreq)));
	fConst1 = (6.2831853071795862 / fConst0);
	fConst2 = std::floor(((0.21999099999999999 * fConst0) + 0.5));
	fConst3 = ((0.0 - (6.9077552789821377 * fConst2)) / fConst0);
	fConst4 = (3.1415926535897931 / fConst0);
	fConst5 = std::floor(((0.019123000000000001 * fConst0) + 0.5));
	iConst6 = int(std::min<double>(16384.0, std::max<double>(0.0, (fConst2 - fConst5))));
	fConst7 = (0.001 * fConst0);
	iConst8 = int(std::min<double>(1024.0, std::max<double>(0.0, (fConst5 + -1.0))));
	fConst9 = std::floor(((0.25689099999999998 * fConst0) + 0.5));
	fConst10 = ((0.0 - (6.9077552789821377 * fConst9)) / fConst0);
	fConst11 = std::floor(((0.027333 * fConst0) + 0.5));
	iConst12 = int(std::min<double>(16384.0, std::max<double>(0.0, (fConst9 - fConst11))));
	iConst13 = int(std::min<double>(2048.0, std::max<double>(0.0, (fConst11 + -1.0))));
	fConst14 = std::floor(((0.192303 * fConst0) + 0.5));
	fConst15 = ((0.0 - (6.9077552789821377 * fConst14)) / fConst0);
	fConst16 = std::floor(((0.029291000000000001 * fConst0) + 0.5));
	iConst17 = int(std::min<double>(8192.0, std::max<double>(0.0, (fConst14 - fConst16))));
	iConst18 = int(std::min<double>(2048.0, std::max<double>(0.0, (fConst16 + -1.0))));
	fConst19 = std::floor(((0.21038899999999999 * fConst0) + 0.5));
	fConst20 = ((0.0 - (6.9077552789821377 * fConst19)) / fConst0);
	fConst21 = std::floor(((0.024421000000000002 * fConst0) + 0.5));
	iConst22 = int(std::min<double>(16384.0, std::max<double>(0.0, (fConst19 - fConst21))));
	iConst23 = int(std::min<double>(2048.0, std::max<double>(0.0, (fConst21 + -1.0))));
	fConst24 = std::floor(((0.125 * fConst0) + 0.5));
	fConst25 = ((0.0 - (6.9077552789821377 * fConst24)) / fConst0);
	fConst26 = std::floor(((0.013457999999999999 * fConst0) + 0.5));
	iConst27 = int(std::min<double>(8192.0, std::max<double>(0.0, (fConst24 - fConst26))));
	iConst28 = int(std::min<double>(1024.0, std::max<double>(0.0, (fConst26 + -1.0))));
	fConst29 = std::floor(((0.12783700000000001 * fConst0) + 0.5));
	fConst30 = ((0.0 - (6.9077552789821377 * fConst29)) / fConst0);
	fConst31 = std::floor(((0.031604 * fConst0) + 0.5));
	iConst32 = int(std::min<double>(8192.0, std::max<double>(0.0, (fConst29 - fConst31))));
	iConst33 = int(std::min<double>(2048.0, std::max<double>(0.0, (fConst31 + -1.0))));
	fConst34 = std::floor(((0.17471300000000001 * fConst0) + 0.5));
	fConst35 = ((0.0 - (6.9077552789821377 * fConst34)) / fConst0);
	fConst36 = std::floor(((0.022904000000000001 * fConst0) + 0.5));
	iConst37 = int(std::min<double>(8192.0, std::max<double>(0.0, (fConst34 - fConst36))));
	iConst38 = int(std::min<double>(2048.0, std::max<double>(0.0, (fConst36 + -1.0))));
	fConst39 = std::floor(((0.15312899999999999 * fConst0) + 0.5));
	fConst40 = ((0.0 - (6.9077552789821377 * fConst39)) / fConst0);
	fConst41 = std::floor(((0.020346 * fConst0) + 0.5));
	iConst42 = int(std::min<double>(8192.0, std::max<double>(0.0, (fConst39 - fConst41))));
	iConst43 = int(std::min<double>(1024.0, std::max<double>(0.0, (fConst41 + -1.0))));
	fVslider0 = FAUSTFLOAT(0.0);
	fVslider1 = FAUSTFLOAT(1500.0);
	fVslider2 = FAUSTFLOAT(0.0);
	fVslider3 = FAUSTFLOAT(315.0);
	fVslider4 = FAUSTFLOAT(0.0);
	fVslider5 = FAUSTFLOAT(6000.0);
	fVslider6 = FAUSTFLOAT(2.0);
	fVslider7 = FAUSTFLOAT(3.0);
	fVslider8 = FAUSTFLOAT(200.0);
	fVslider9 = FAUSTFLOAT(60.0);
	fVslider10 = FAUSTFLOAT(0.0);
			IOTA = 0;
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
	double fSlow0 = (0.0010000000000000009 * double(fVslider0));
	double fSlow1 = double(fVslider1);
	double fSlow2 = std::pow(10.0, (0.050000000000000003 * double(fVslider2)));
	double fSlow3 = (fConst1 * (fSlow1 / std::sqrt(fSlow2)));
	double fSlow4 = ((1.0 - fSlow3) / (fSlow3 + 1.0));
	double fSlow5 = double(fVslider3);
	double fSlow6 = std::pow(10.0, (0.050000000000000003 * double(fVslider4)));
	double fSlow7 = (fConst1 * (fSlow5 / std::sqrt(fSlow6)));
	double fSlow8 = ((1.0 - fSlow7) / (fSlow7 + 1.0));
	double fSlow9 = std::cos((fConst1 * double(fVslider5)));
	double fSlow10 = double(fVslider6);
	double fSlow11 = std::exp((fConst3 / fSlow10));
	double fSlow12 = mydsp_faustpower2_f(fSlow11);
	double fSlow13 = (1.0 - (fSlow9 * fSlow12));
	double fSlow14 = (1.0 - fSlow12);
	double fSlow15 = (fSlow13 / fSlow14);
	double fSlow16 = std::sqrt(std::max<double>(0.0, ((mydsp_faustpower2_f(fSlow13) / mydsp_faustpower2_f(fSlow14)) + -1.0)));
	double fSlow17 = (fSlow15 - fSlow16);
	double fSlow18 = ((fSlow16 + (1.0 - fSlow15)) * fSlow11);
	double fSlow19 = double(fVslider7);
	double fSlow20 = ((std::exp((fConst3 / fSlow19)) / fSlow11) + -1.0);
	double fSlow21 = (1.0 / std::tan((fConst4 * double(fVslider8))));
	double fSlow22 = (1.0 / (fSlow21 + 1.0));
	double fSlow23 = (1.0 - fSlow21);
	int iSlow24 = int(std::min<double>(8192.0, std::max<double>(0.0, (fConst7 * double(fVslider9)))));
	double fSlow25 = std::exp((fConst10 / fSlow10));
	double fSlow26 = mydsp_faustpower2_f(fSlow25);
	double fSlow27 = (1.0 - (fSlow9 * fSlow26));
	double fSlow28 = (1.0 - fSlow26);
	double fSlow29 = (fSlow27 / fSlow28);
	double fSlow30 = std::sqrt(std::max<double>(0.0, ((mydsp_faustpower2_f(fSlow27) / mydsp_faustpower2_f(fSlow28)) + -1.0)));
	double fSlow31 = (fSlow29 - fSlow30);
	double fSlow32 = ((fSlow30 + (1.0 - fSlow29)) * fSlow25);
	double fSlow33 = ((std::exp((fConst10 / fSlow19)) / fSlow25) + -1.0);
	double fSlow34 = std::exp((fConst15 / fSlow10));
	double fSlow35 = mydsp_faustpower2_f(fSlow34);
	double fSlow36 = (1.0 - (fSlow9 * fSlow35));
	double fSlow37 = (1.0 - fSlow35);
	double fSlow38 = (fSlow36 / fSlow37);
	double fSlow39 = std::sqrt(std::max<double>(0.0, ((mydsp_faustpower2_f(fSlow36) / mydsp_faustpower2_f(fSlow37)) + -1.0)));
	double fSlow40 = (fSlow38 - fSlow39);
	double fSlow41 = ((fSlow39 + (1.0 - fSlow38)) * fSlow34);
	double fSlow42 = ((std::exp((fConst15 / fSlow19)) / fSlow34) + -1.0);
	double fSlow43 = std::exp((fConst20 / fSlow10));
	double fSlow44 = mydsp_faustpower2_f(fSlow43);
	double fSlow45 = (1.0 - (fSlow9 * fSlow44));
	double fSlow46 = (1.0 - fSlow44);
	double fSlow47 = (fSlow45 / fSlow46);
	double fSlow48 = std::sqrt(std::max<double>(0.0, ((mydsp_faustpower2_f(fSlow45) / mydsp_faustpower2_f(fSlow46)) + -1.0)));
	double fSlow49 = (fSlow47 - fSlow48);
	double fSlow50 = ((fSlow48 + (1.0 - fSlow47)) * fSlow43);
	double fSlow51 = ((std::exp((fConst20 / fSlow19)) / fSlow43) + -1.0);
	double fSlow52 = std::exp((fConst25 / fSlow10));
	double fSlow53 = mydsp_faustpower2_f(fSlow52);
	double fSlow54 = (1.0 - (fSlow9 * fSlow53));
	double fSlow55 = (1.0 - fSlow53);
	double fSlow56 = (fSlow54 / fSlow55);
	double fSlow57 = std::sqrt(std::max<double>(0.0, ((mydsp_faustpower2_f(fSlow54) / mydsp_faustpower2_f(fSlow55)) + -1.0)));
	double fSlow58 = (fSlow56 - fSlow57);
	double fSlow59 = ((fSlow57 + (1.0 - fSlow56)) * fSlow52);
	double fSlow60 = ((std::exp((fConst25 / fSlow19)) / fSlow52) + -1.0);
	double fSlow61 = std::exp((fConst30 / fSlow10));
	double fSlow62 = mydsp_faustpower2_f(fSlow61);
	double fSlow63 = (1.0 - (fSlow9 * fSlow62));
	double fSlow64 = (1.0 - fSlow62);
	double fSlow65 = (fSlow63 / fSlow64);
	double fSlow66 = std::sqrt(std::max<double>(0.0, ((mydsp_faustpower2_f(fSlow63) / mydsp_faustpower2_f(fSlow64)) + -1.0)));
	double fSlow67 = (fSlow65 - fSlow66);
	double fSlow68 = ((fSlow66 + (1.0 - fSlow65)) * fSlow61);
	double fSlow69 = ((std::exp((fConst30 / fSlow19)) / fSlow61) + -1.0);
	double fSlow70 = std::exp((fConst35 / fSlow10));
	double fSlow71 = mydsp_faustpower2_f(fSlow70);
	double fSlow72 = (1.0 - (fSlow9 * fSlow71));
	double fSlow73 = (1.0 - fSlow71);
	double fSlow74 = (fSlow72 / fSlow73);
	double fSlow75 = std::sqrt(std::max<double>(0.0, ((mydsp_faustpower2_f(fSlow72) / mydsp_faustpower2_f(fSlow73)) + -1.0)));
	double fSlow76 = (fSlow74 - fSlow75);
	double fSlow77 = ((fSlow75 + (1.0 - fSlow74)) * fSlow70);
	double fSlow78 = ((std::exp((fConst35 / fSlow19)) / fSlow70) + -1.0);
	double fSlow79 = std::exp((fConst40 / fSlow10));
	double fSlow80 = mydsp_faustpower2_f(fSlow79);
	double fSlow81 = (1.0 - (fSlow9 * fSlow80));
	double fSlow82 = (1.0 - fSlow80);
	double fSlow83 = (fSlow81 / fSlow82);
	double fSlow84 = std::sqrt(std::max<double>(0.0, ((mydsp_faustpower2_f(fSlow81) / mydsp_faustpower2_f(fSlow82)) + -1.0)));
	double fSlow85 = (fSlow83 - fSlow84);
	double fSlow86 = ((fSlow84 + (1.0 - fSlow83)) * fSlow79);
	double fSlow87 = ((std::exp((fConst40 / fSlow19)) / fSlow79) + -1.0);
	double fSlow88 = (0.0 - ((fSlow8 + 1.0) * std::cos((fConst1 * fSlow5))));
	double fSlow89 = (0.0 - ((fSlow4 + 1.0) * std::cos((fConst1 * fSlow1))));
	double fSlow90 = (0.0010000000000000009 * double(fVslider10));
	for (int i = 0; (i < count); i = (i + 1)) {
		fRec0[0] = (fSlow0 + (0.999 * fRec0[1]));
		double fTemp0 = (fRec0[0] + 1.0);
		double fTemp1 = (1.0 - (0.5 * fTemp0));
		double fTemp2 = double(input0[i]);
		fVec0[(IOTA & 16383)] = fTemp2;
		fRec14[0] = (0.0 - (fSlow22 * ((fSlow23 * fRec14[1]) - (fRec10[1] + fRec10[2]))));
		fRec13[0] = ((fSlow17 * fRec13[1]) + (fSlow18 * (fRec10[1] + (fSlow20 * fRec14[0]))));
		fVec1[(IOTA & 32767)] = ((0.35355339059327373 * fRec13[0]) + 9.9999999999999995e-21);
		double fTemp3 = double(input1[i]);
		fVec2[(IOTA & 16383)] = fTemp3;
		double fTemp4 = (0.29999999999999999 * fVec2[((IOTA - iSlow24) & 16383)]);
		double fTemp5 = (((0.59999999999999998 * fRec11[1]) + fVec1[((IOTA - iConst6) & 32767)]) - fTemp4);
		fVec3[(IOTA & 2047)] = fTemp5;
		fRec11[0] = fVec3[((IOTA - iConst8) & 2047)];
		double fRec12 = (0.0 - (0.59999999999999998 * fTemp5));
		fRec18[0] = (0.0 - (fSlow22 * ((fSlow23 * fRec18[1]) - (fRec6[1] + fRec6[2]))));
		fRec17[0] = ((fSlow31 * fRec17[1]) + (fSlow32 * (fRec6[1] + (fSlow33 * fRec18[0]))));
		fVec4[(IOTA & 32767)] = ((0.35355339059327373 * fRec17[0]) + 9.9999999999999995e-21);
		double fTemp6 = (((0.59999999999999998 * fRec15[1]) + fVec4[((IOTA - iConst12) & 32767)]) - fTemp4);
		fVec5[(IOTA & 4095)] = fTemp6;
		fRec15[0] = fVec5[((IOTA - iConst13) & 4095)];
		double fRec16 = (0.0 - (0.59999999999999998 * fTemp6));
		fRec22[0] = (0.0 - (fSlow22 * ((fSlow23 * fRec22[1]) - (fRec8[1] + fRec8[2]))));
		fRec21[0] = ((fSlow40 * fRec21[1]) + (fSlow41 * (fRec8[1] + (fSlow42 * fRec22[0]))));
		fVec6[(IOTA & 16383)] = ((0.35355339059327373 * fRec21[0]) + 9.9999999999999995e-21);
		double fTemp7 = (fVec6[((IOTA - iConst17) & 16383)] + (fTemp4 + (0.59999999999999998 * fRec19[1])));
		fVec7[(IOTA & 4095)] = fTemp7;
		fRec19[0] = fVec7[((IOTA - iConst18) & 4095)];
		double fRec20 = (0.0 - (0.59999999999999998 * fTemp7));
		fRec26[0] = (0.0 - (fSlow22 * ((fSlow23 * fRec26[1]) - (fRec4[1] + fRec4[2]))));
		fRec25[0] = ((fSlow49 * fRec25[1]) + (fSlow50 * (fRec4[1] + (fSlow51 * fRec26[0]))));
		fVec8[(IOTA & 32767)] = ((0.35355339059327373 * fRec25[0]) + 9.9999999999999995e-21);
		double fTemp8 = (fTemp4 + ((0.59999999999999998 * fRec23[1]) + fVec8[((IOTA - iConst22) & 32767)]));
		fVec9[(IOTA & 4095)] = fTemp8;
		fRec23[0] = fVec9[((IOTA - iConst23) & 4095)];
		double fRec24 = (0.0 - (0.59999999999999998 * fTemp8));
		fRec30[0] = (0.0 - (fSlow22 * ((fSlow23 * fRec30[1]) - (fRec9[1] + fRec9[2]))));
		fRec29[0] = ((fSlow58 * fRec29[1]) + (fSlow59 * (fRec9[1] + (fSlow60 * fRec30[0]))));
		fVec10[(IOTA & 16383)] = ((0.35355339059327373 * fRec29[0]) + 9.9999999999999995e-21);
		double fTemp9 = (0.29999999999999999 * fVec0[((IOTA - iSlow24) & 16383)]);
		double fTemp10 = (fVec10[((IOTA - iConst27) & 16383)] - (fTemp9 + (0.59999999999999998 * fRec27[1])));
		fVec11[(IOTA & 2047)] = fTemp10;
		fRec27[0] = fVec11[((IOTA - iConst28) & 2047)];
		double fRec28 = (0.59999999999999998 * fTemp10);
		fRec34[0] = (0.0 - (fSlow22 * ((fSlow23 * fRec34[1]) - (fRec5[1] + fRec5[2]))));
		fRec33[0] = ((fSlow67 * fRec33[1]) + (fSlow68 * (fRec5[1] + (fSlow69 * fRec34[0]))));
		fVec12[(IOTA & 16383)] = ((0.35355339059327373 * fRec33[0]) + 9.9999999999999995e-21);
		double fTemp11 = (fVec12[((IOTA - iConst32) & 16383)] - (fTemp9 + (0.59999999999999998 * fRec31[1])));
		fVec13[(IOTA & 4095)] = fTemp11;
		fRec31[0] = fVec13[((IOTA - iConst33) & 4095)];
		double fRec32 = (0.59999999999999998 * fTemp11);
		fRec38[0] = (0.0 - (fSlow22 * ((fSlow23 * fRec38[1]) - (fRec7[1] + fRec7[2]))));
		fRec37[0] = ((fSlow76 * fRec37[1]) + (fSlow77 * (fRec7[1] + (fSlow78 * fRec38[0]))));
		fVec14[(IOTA & 16383)] = ((0.35355339059327373 * fRec37[0]) + 9.9999999999999995e-21);
		double fTemp12 = ((fTemp9 + fVec14[((IOTA - iConst37) & 16383)]) - (0.59999999999999998 * fRec35[1]));
		fVec15[(IOTA & 4095)] = fTemp12;
		fRec35[0] = fVec15[((IOTA - iConst38) & 4095)];
		double fRec36 = (0.59999999999999998 * fTemp12);
		fRec42[0] = (0.0 - (fSlow22 * ((fSlow23 * fRec42[1]) - (fRec3[1] + fRec3[2]))));
		fRec41[0] = ((fSlow85 * fRec41[1]) + (fSlow86 * (fRec3[1] + (fSlow87 * fRec42[0]))));
		fVec16[(IOTA & 16383)] = ((0.35355339059327373 * fRec41[0]) + 9.9999999999999995e-21);
		double fTemp13 = ((fVec16[((IOTA - iConst42) & 16383)] + fTemp9) - (0.59999999999999998 * fRec39[1]));
		fVec17[(IOTA & 2047)] = fTemp13;
		fRec39[0] = fVec17[((IOTA - iConst43) & 2047)];
		double fRec40 = (0.59999999999999998 * fTemp13);
		double fTemp14 = (fRec40 + fRec36);
		double fTemp15 = (fRec28 + (fRec32 + fTemp14));
		fRec3[0] = (fRec11[1] + (fRec15[1] + (fRec19[1] + (fRec23[1] + (fRec27[1] + (fRec31[1] + (fRec35[1] + (fRec39[1] + (fRec12 + (fRec16 + (fRec20 + (fRec24 + fTemp15))))))))))));
		fRec4[0] = ((fRec27[1] + (fRec31[1] + (fRec35[1] + (fRec39[1] + fTemp15)))) - (fRec11[1] + (fRec15[1] + (fRec19[1] + (fRec23[1] + (fRec12 + (fRec16 + (fRec24 + fRec20))))))));
		double fTemp16 = (fRec32 + fRec28);
		fRec5[0] = ((fRec19[1] + (fRec23[1] + (fRec35[1] + (fRec39[1] + (fRec20 + (fRec24 + fTemp14)))))) - (fRec11[1] + (fRec15[1] + (fRec27[1] + (fRec31[1] + (fRec12 + (fRec16 + fTemp16)))))));
		fRec6[0] = ((fRec11[1] + (fRec15[1] + (fRec35[1] + (fRec39[1] + (fRec12 + (fRec16 + fTemp14)))))) - (fRec19[1] + (fRec23[1] + (fRec27[1] + (fRec31[1] + (fRec20 + (fRec24 + fTemp16)))))));
		double fTemp17 = (fRec40 + fRec32);
		double fTemp18 = (fRec36 + fRec28);
		fRec7[0] = ((fRec15[1] + (fRec23[1] + (fRec31[1] + (fRec39[1] + (fRec16 + (fRec24 + fTemp17)))))) - (fRec11[1] + (fRec19[1] + (fRec27[1] + (fRec35[1] + (fRec12 + (fRec20 + fTemp18)))))));
		fRec8[0] = ((fRec11[1] + (fRec19[1] + (fRec31[1] + (fRec39[1] + (fRec12 + (fRec20 + fTemp17)))))) - (fRec15[1] + (fRec23[1] + (fRec27[1] + (fRec35[1] + (fRec16 + (fRec24 + fTemp18)))))));
		double fTemp19 = (fRec40 + fRec28);
		double fTemp20 = (fRec36 + fRec32);
		fRec9[0] = ((fRec11[1] + (fRec23[1] + (fRec27[1] + (fRec39[1] + (fRec12 + (fRec24 + fTemp19)))))) - (fRec15[1] + (fRec19[1] + (fRec31[1] + (fRec35[1] + (fRec16 + (fRec20 + fTemp20)))))));
		fRec10[0] = ((fRec15[1] + (fRec19[1] + (fRec27[1] + (fRec39[1] + (fRec16 + (fRec20 + fTemp19)))))) - (fRec11[1] + (fRec23[1] + (fRec31[1] + (fRec35[1] + (fRec12 + (fRec24 + fTemp20)))))));
		double fTemp21 = (0.37 * (fRec4[0] + fRec5[0]));
		double fTemp22 = (fSlow88 * fRec2[1]);
		fRec2[0] = (fTemp21 - (fTemp22 + (fSlow8 * fRec2[2])));
		double fTemp23 = (fSlow8 * fRec2[0]);
		double fTemp24 = (0.5 * ((fTemp23 + (fRec2[2] + (fTemp21 + fTemp22))) + (fSlow6 * ((fTemp23 + (fTemp22 + fRec2[2])) - fTemp21))));
		double fTemp25 = (fSlow89 * fRec1[1]);
		fRec1[0] = (fTemp24 - (fTemp25 + (fSlow4 * fRec1[2])));
		double fTemp26 = (fSlow4 * fRec1[0]);
		fRec43[0] = (fSlow90 + (0.999 * fRec43[1]));
		double fTemp27 = std::pow(10.0, (0.050000000000000003 * fRec43[0]));
		output0[i] = FAUSTFLOAT((((fTemp1 * fTemp2) + (0.25 * (fTemp0 * ((fTemp26 + (fRec1[2] + (fTemp24 + fTemp25))) + (fSlow2 * ((fTemp26 + (fTemp25 + fRec1[2])) - fTemp24)))))) * fTemp27));
		double fTemp28 = (0.37 * (fRec4[0] - fRec5[0]));
		double fTemp29 = (fSlow88 * fRec45[1]);
		fRec45[0] = (fTemp28 - (fTemp29 + (fSlow8 * fRec45[2])));
		double fTemp30 = (fSlow8 * fRec45[0]);
		double fTemp31 = (0.5 * ((fTemp30 + (fRec45[2] + (fTemp28 + fTemp29))) + (fSlow6 * ((fTemp30 + (fTemp29 + fRec45[2])) - fTemp28))));
		double fTemp32 = (fSlow89 * fRec44[1]);
		fRec44[0] = (fTemp31 - (fTemp32 + (fSlow4 * fRec44[2])));
		double fTemp33 = (fSlow4 * fRec44[0]);
		output1[i] = FAUSTFLOAT((fTemp27 * ((fTemp1 * fTemp3) + (0.25 * (fTemp0 * ((fTemp33 + (fRec44[2] + (fTemp31 + fTemp32))) + (fSlow2 * ((fTemp33 + (fTemp32 + fRec44[2])) - fTemp31))))))));
		fRec0[1] = fRec0[0];
		IOTA = (IOTA + 1);
		fRec14[1] = fRec14[0];
		fRec13[1] = fRec13[0];
		fRec11[1] = fRec11[0];
		fRec18[1] = fRec18[0];
		fRec17[1] = fRec17[0];
		fRec15[1] = fRec15[0];
		fRec22[1] = fRec22[0];
		fRec21[1] = fRec21[0];
		fRec19[1] = fRec19[0];
		fRec26[1] = fRec26[0];
		fRec25[1] = fRec25[0];
		fRec23[1] = fRec23[0];
		fRec30[1] = fRec30[0];
		fRec29[1] = fRec29[0];
		fRec27[1] = fRec27[0];
		fRec34[1] = fRec34[0];
		fRec33[1] = fRec33[0];
		fRec31[1] = fRec31[0];
		fRec38[1] = fRec38[0];
		fRec37[1] = fRec37[0];
		fRec35[1] = fRec35[0];
		fRec42[1] = fRec42[0];
		fRec41[1] = fRec41[0];
		fRec39[1] = fRec39[0];
		fRec3[2] = fRec3[1];
		fRec3[1] = fRec3[0];
		fRec4[2] = fRec4[1];
		fRec4[1] = fRec4[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		fRec6[2] = fRec6[1];
		fRec6[1] = fRec6[0];
		fRec7[2] = fRec7[1];
		fRec7[1] = fRec7[0];
		fRec8[2] = fRec8[1];
		fRec8[1] = fRec8[0];
		fRec9[2] = fRec9[1];
		fRec9[1] = fRec9[0];
		fRec10[2] = fRec10[1];
		fRec10[1] = fRec10[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fRec1[2] = fRec1[1];
		fRec1[1] = fRec1[0];
		fRec43[1] = fRec43[0];
		fRec45[2] = fRec45[1];
		fRec45[1] = fRec45[0];
		fRec44[2] = fRec44[1];
		fRec44[1] = fRec44[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("zita_rev1.decay_times.hf_damping",N_("HF Damp"),"SL",N_("Frequency (Hz) at which the high-frequency T60 is half the middle-band's T60"),&fVslider5, 6000.0, 1500.0, 23520.0, 1.0800000000000001);
	reg.registerVar("zita_rev1.decay_times.lf_x",N_("Freq X"),"SL",N_("Crossover frequency (Hz) separating low and middle frequencies"),&fVslider8, 200.0, 50.0, 1000.0, 1.0800000000000001);
	reg.registerVar("zita_rev1.decay_times.low_rt60",N_("Low"),"SL",N_("T60 = time (in seconds) to decay 60dB in low-frequency band"),&fVslider7, 3.0, 1.0, 8.0, 1.0800000000000001);
	reg.registerVar("zita_rev1.decay_times.mid_rt60",N_("Mid"),"SL",N_("T60 = time (in seconds) to decay 60dB in middle band"),&fVslider6, 2.0, 1.0, 8.0, 1.0800000000000001);
	reg.registerVar("zita_rev1.equalizer1.eq1_freq",N_("Freq"),"SL",N_("Center-frequency of second-order Regalia-Mitra peaking equalizer section 1"),&fVslider3, 315.0, 40.0, 2500.0, 1.0800000000000001);
	reg.registerVar("zita_rev1.equalizer1.eq1_level",N_("Level"),"S",N_("Peak level in dB of second-order Regalia-Mitra peaking equalizer section 1"),&fVslider4, 0.0, -15.0, 15.0, 0.10000000000000001);
	reg.registerVar("zita_rev1.equalizer2.eq2_freq",N_("Freq"),"SL",N_("Center-frequency of second-order Regalia-Mitra peaking equalizer section 2"),&fVslider1, 1500.0, 160.0, 10000.0, 1.0800000000000001);
	reg.registerVar("zita_rev1.equalizer2.eq2_level",N_("Level"),"S",N_("Peak level in dB of second-order Regalia-Mitra peaking equalizer section 2"),&fVslider2, 0.0, -15.0, 15.0, 0.10000000000000001);
	reg.registerVar("zita_rev1.input.in_delay",N_("Pre Delay"),"S",N_("Delay in ms before reverberation begins"),&fVslider9, 60.0, 20.0, 100.0, 1.0);
	reg.registerVar("zita_rev1.output.dry_wet_mix",N_("Dry/Wet"),"S",N_("-1 = dry, 1 = wet"),&fVslider0, 0.0, -1.0, 1.0, 0.01);
	reg.registerVar("zita_rev1.output.level",N_("Level"),"S",N_("Output scale factor"),&fVslider10, 0.0, -70.0, 40.0, 0.10000000000000001);
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
    <property name=\"resizable\">False</property>\n\
    <property name=\"default_width\">0</property>\n\
    <property name=\"default_height\">0</property>\n\
    <child>\n\
      <placeholder/>\n\
    </child>\n\
    <child>\n\
      <object class=\"GtkBox\" id=\"vbox12\">\n\
        <property name=\"visible\">True</property>\n\
        <property name=\"can_focus\">False</property>\n\
        <property name=\"orientation\">vertical</property>\n\
        <property name=\"spacing\">10</property>\n\
        <child>\n\
          <object class=\"GtkBox\" id=\"minibox\">\n\
            <property name=\"visible\">True</property>\n\
            <property name=\"can_focus\">False</property>\n\
            <property name=\"spacing\">5</property>\n\
            <child>\n\
              <object class=\"GxHSlider\" id=\"gxhslider1\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">True</property>\n\
                <property name=\"receives_default\">True</property>\n\
                <property name=\"round_digits\">0</property>\n\
                <property name=\"var_id\">zita_rev1.output.dry_wet_mix</property>\n\
                <property name=\"show_value\">False</property>\n\
                <property name=\"value_position\">right</property>\n\
                <property name=\"value_xalign\">0.52000000000000002</property>\n\
                <property name=\"label_ref\">label12:rack_label</property>\n\
              </object>\n\
              <packing>\n\
                <property name=\"expand\">False</property>\n\
                <property name=\"fill\">False</property>\n\
                <property name=\"position\">0</property>\n\
              </packing>\n\
            </child>\n\
            <child>\n\
              <object class=\"GtkLabel\" id=\"label12:rack_label\">\n\
                <property name=\"height_request\">12</property>\n\
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
            <property name=\"position\">0</property>\n\
          </packing>\n\
        </child>\n\
        <child>\n\
          <object class=\"GtkBox\" id=\"rackbox\">\n\
            <property name=\"visible\">True</property>\n\
            <property name=\"can_focus\">False</property>\n\
            <child>\n\
              <object class=\"GtkBox\" id=\"vbox\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">False</property>\n\
                <property name=\"orientation\">vertical</property>\n\
                <property name=\"spacing\">16</property>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"hbox2\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"spacing\">5</property>\n\
                    <child>\n\
                      <object class=\"GtkFrame\" id=\"frame4\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label_xalign\">0.5</property>\n\
                        <child>\n\
                          <object class=\"GtkAlignment\" id=\"alignment4\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"top_padding\">2</property>\n\
                            <property name=\"bottom_padding\">2</property>\n\
                            <property name=\"left_padding\">2</property>\n\
                            <property name=\"right_padding\">2</property>\n\
                            <child>\n\
                              <object class=\"GtkBox\" id=\"hbox6\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <child>\n\
                                  <object class=\"GtkBox\" id=\"vbox7\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <property name=\"orientation\">vertical</property>\n\
                                    <child>\n\
                                      <object class=\"GtkLabel\" id=\"label1:rack_label\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"label\">label</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">False</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">0</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GxSmallKnobR\" id=\"gxsmallknob1\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">True</property>\n\
                                        <property name=\"receives_default\">True</property>\n\
                                        <property name=\"round_digits\">0</property>\n\
                                        <property name=\"var_id\">zita_rev1.input.in_delay</property>\n\
                                        <property name=\"label_ref\">label1:rack_label</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">False</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">1</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">True</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"position\">0</property>\n\
                                  </packing>\n\
                                </child>\n\
                                <child>\n\
                                  <object class=\"GtkBox\" id=\"vbox9\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <property name=\"orientation\">vertical</property>\n\
                                    <child>\n\
                                      <object class=\"GtkLabel\" id=\"label3:rack_label\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"label\">label</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">0</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GxSmallKnobR\" id=\"gxsmallknob3\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">True</property>\n\
                                        <property name=\"receives_default\">True</property>\n\
                                        <property name=\"round_digits\">0</property>\n\
                                        <property name=\"var_id\">zita_rev1.decay_times.low_rt60</property>\n\
                                        <property name=\"label_ref\">label3:rack_label</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
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
                                <child>\n\
                                  <object class=\"GtkBox\" id=\"vbox8\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <property name=\"orientation\">vertical</property>\n\
                                    <child>\n\
                                      <object class=\"GtkLabel\" id=\"label2:rack_label\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"label\">label</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">False</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">0</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GxSmallKnob\" id=\"gxminislider1\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">True</property>\n\
                                        <property name=\"receives_default\">True</property>\n\
                                        <property name=\"round_digits\">0</property>\n\
                                        <property name=\"var_id\">zita_rev1.decay_times.lf_x</property>\n\
                                        <property name=\"show_value\">False</property>\n\
                                        <property name=\"label_ref\">label2:rack_label</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">1</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GtkAlignment\" id=\"alignment6\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"xscale\">0</property>\n\
                                        <property name=\"yscale\">0</property>\n\
                                        <child>\n\
                                          <object class=\"GxValueDisplay\" id=\"gxvaluedisplay1\">\n\
                                            <property name=\"visible\">True</property>\n\
                                            <property name=\"can_focus\">True</property>\n\
                                            <property name=\"receives_default\">True</property>\n\
                                            <property name=\"round_digits\">0</property>\n\
                                            <property name=\"var_id\">zita_rev1.decay_times.lf_x</property>\n\
                                          </object>\n\
                                        </child>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">False</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">2</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">True</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"position\">2</property>\n\
                                  </packing>\n\
                                </child>\n\
                                <child>\n\
                                  <object class=\"GtkBox\" id=\"vbox10\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <property name=\"orientation\">vertical</property>\n\
                                    <child>\n\
                                      <object class=\"GtkLabel\" id=\"label4:rack_label\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"label\">label</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">0</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GxSmallKnobR\" id=\"gxsmallknob4\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">True</property>\n\
                                        <property name=\"receives_default\">True</property>\n\
                                        <property name=\"round_digits\">0</property>\n\
                                        <property name=\"var_id\">zita_rev1.decay_times.mid_rt60</property>\n\
                                        <property name=\"label_ref\">label4:rack_label</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">1</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">True</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"position\">3</property>\n\
                                  </packing>\n\
                                </child>\n\
                                <child>\n\
                                  <object class=\"GtkBox\" id=\"vbox11\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <property name=\"orientation\">vertical</property>\n\
                                    <child>\n\
                                      <object class=\"GtkLabel\" id=\"label5:rack_label\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"label\">label</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">0</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GxSmallKnobR\" id=\"gxsmallknob5\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">True</property>\n\
                                        <property name=\"receives_default\">True</property>\n\
                                        <property name=\"round_digits\">0</property>\n\
                                        <property name=\"var_id\">zita_rev1.decay_times.hf_damping</property>\n\
                                        <property name=\"label_ref\">label5:rack_label</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">1</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">True</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"position\">4</property>\n\
                                  </packing>\n\
                                </child>\n\
                              </object>\n\
                            </child>\n\
                          </object>\n\
                        </child>\n\
                        <child type=\"label\">\n\
                          <object class=\"GtkLabel\" id=\"label121:rack_label\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"label\" translatable=\"yes\">Reverb</property>\n\
                            <property name=\"use_markup\">True</property>\n\
                          </object>\n\
                        </child>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">True</property>\n\
                        <property name=\"fill\">True</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">False</property>\n\
                    <property name=\"fill\">True</property>\n\
                    <property name=\"position\">0</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"hbox3\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"spacing\">4</property>\n\
                    <child>\n\
                      <object class=\"GtkFrame\" id=\"frame1:frame_inversed\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label_xalign\">0.5</property>\n\
                        <child>\n\
                          <object class=\"GtkAlignment\" id=\"alignment1\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"top_padding\">5</property>\n\
                            <property name=\"bottom_padding\">5</property>\n\
                            <property name=\"left_padding\">5</property>\n\
                            <property name=\"right_padding\">5</property>\n\
                            <child>\n\
                              <object class=\"GtkBox\" id=\"hbox4\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <child>\n\
                                  <object class=\"GtkBox\" id=\"vbox1\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <child>\n\
                                      <object class=\"GtkLabel\" id=\"label6:rack_label_inverse\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"label\">label</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">0</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GxSmallKnob\" id=\"gxsmallknob6\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">True</property>\n\
                                        <property name=\"receives_default\">True</property>\n\
                                        <property name=\"round_digits\">0</property>\n\
                                        <property name=\"var_id\">zita_rev1.equalizer1.eq1_freq</property>\n\
                                        <property name=\"label_ref\">label6:rack_label_inverse</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">1</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">True</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"padding\">2</property>\n\
                                    <property name=\"position\">0</property>\n\
                                  </packing>\n\
                                </child>\n\
                                <child>\n\
                                  <object class=\"GtkBox\" id=\"vbox2\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <child>\n\
                                      <object class=\"GtkLabel\" id=\"label7:rack_label_inverse\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"label\">label</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">0</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GxSmallKnob\" id=\"gxsmallknob7\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">True</property>\n\
                                        <property name=\"receives_default\">True</property>\n\
                                        <property name=\"round_digits\">0</property>\n\
                                        <property name=\"var_id\">zita_rev1.equalizer1.eq1_level</property>\n\
                                        <property name=\"label_ref\">label7:rack_label_inverse</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">1</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">True</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"padding\">2</property>\n\
                                    <property name=\"position\">1</property>\n\
                                  </packing>\n\
                                </child>\n\
                              </object>\n\
                            </child>\n\
                          </object>\n\
                        </child>\n\
                        <child type=\"label\">\n\
                          <object class=\"GtkLabel\" id=\"label15:rack_label_inverse\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"label\" translatable=\"yes\">Filter 1</property>\n\
                            <property name=\"use_markup\">True</property>\n\
                          </object>\n\
                        </child>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">True</property>\n\
                        <property name=\"fill\">True</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GtkFrame\" id=\"frame2:frame_inversed\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label_xalign\">0.5</property>\n\
                        <child>\n\
                          <object class=\"GtkAlignment\" id=\"alignment2\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"top_padding\">5</property>\n\
                            <property name=\"bottom_padding\">5</property>\n\
                            <property name=\"left_padding\">5</property>\n\
                            <property name=\"right_padding\">5</property>\n\
                            <child>\n\
                              <object class=\"GtkBox\" id=\"hbox7\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <child>\n\
                                  <object class=\"GtkBox\" id=\"vbox3\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <child>\n\
                                      <object class=\"GtkLabel\" id=\"label8:rack_label_inverse\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"label\">label</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">0</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GxSmallKnob\" id=\"gxsmallknob8\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">True</property>\n\
                                        <property name=\"receives_default\">True</property>\n\
                                        <property name=\"round_digits\">0</property>\n\
                                        <property name=\"var_id\">zita_rev1.equalizer2.eq2_freq</property>\n\
                                        <property name=\"label_ref\">label8:rack_label_inverse</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">1</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">True</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"padding\">2</property>\n\
                                    <property name=\"position\">0</property>\n\
                                  </packing>\n\
                                </child>\n\
                                <child>\n\
                                  <object class=\"GtkBox\" id=\"vbox4\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <child>\n\
                                      <object class=\"GtkLabel\" id=\"label9:rack_label_inverse\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"label\">label</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">0</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GxSmallKnob\" id=\"gxsmallknob9\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">True</property>\n\
                                        <property name=\"receives_default\">True</property>\n\
                                        <property name=\"round_digits\">0</property>\n\
                                        <property name=\"var_id\">zita_rev1.equalizer2.eq2_level</property>\n\
                                        <property name=\"label_ref\">label9:rack_label_inverse</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">1</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">True</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"padding\">2</property>\n\
                                    <property name=\"position\">1</property>\n\
                                  </packing>\n\
                                </child>\n\
                              </object>\n\
                            </child>\n\
                          </object>\n\
                        </child>\n\
                        <child type=\"label\">\n\
                          <object class=\"GtkLabel\" id=\"label14:rack_label_inverse\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"label\" translatable=\"yes\">Filter 2</property>\n\
                            <property name=\"use_markup\">True</property>\n\
                          </object>\n\
                        </child>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">True</property>\n\
                        <property name=\"fill\">True</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">False</property>\n\
                    <property name=\"fill\">True</property>\n\
                    <property name=\"position\">1</property>\n\
                  </packing>\n\
                </child>\n\
              </object>\n\
              <packing>\n\
                <property name=\"expand\">True</property>\n\
                <property name=\"fill\">True</property>\n\
                <property name=\"position\">0</property>\n\
              </packing>\n\
            </child>\n\
            <child>\n\
              <object class=\"GtkBox\" id=\"vbox13\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">False</property>\n\
                <property name=\"orientation\">vertical</property>\n\
                <property name=\"spacing\">20</property>\n\
                <child>\n\
                  <object class=\"GtkAlignment\" id=\"alignment3\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"top_padding\">18</property>\n\
                    <child>\n\
                      <object class=\"GtkBox\" id=\"vbox5\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"orientation\">vertical</property>\n\
                        <child>\n\
                          <object class=\"GtkLabel\" id=\"label10:rack_label\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"label\">label</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">0</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GxSmallKnobR\" id=\"gxsmallknob10\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">True</property>\n\
                            <property name=\"receives_default\">True</property>\n\
                            <property name=\"round_digits\">0</property>\n\
                            <property name=\"var_id\">zita_rev1.output.dry_wet_mix</property>\n\
                            <property name=\"label_ref\">label10:rack_label</property>\n\
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
                  <packing>\n\
                    <property name=\"expand\">True</property>\n\
                    <property name=\"fill\">True</property>\n\
                    <property name=\"position\">0</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox6\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label11:rack_label_inverse\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\">label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">True</property>\n\
                        <property name=\"fill\">True</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSmallKnobR\" id=\"gxsmallknob11\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"round_digits\">0</property>\n\
                        <property name=\"var_id\">zita_rev1.output.level</property>\n\
                        <property name=\"label_ref\">label11:rack_label_inverse</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">True</property>\n\
                        <property name=\"fill\">True</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">True</property>\n\
                    <property name=\"fill\">True</property>\n\
                    <property name=\"padding\">2</property>\n\
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
#define PARAM(p) ("zita_rev1" "." p)
b.openHorizontalhideBox("");
{
    b.create_master_slider(PARAM("output.level"), "Level");
}
b.closeBox();
b.openVerticalBox("");
{
    b.create_small_rackknob(PARAM("input.in_delay"), "In Delay");
    b.create_small_rackknob(PARAM("output.dry_wet_mix"), "Dry/Wet");
    b.create_small_rackknob(PARAM("output.level"), "Level");

    b.openHorizontalBox("Reverb Time T60");
    {
	b.create_small_rackknob(PARAM("decay_times.lf_x"), "Freq X");
	b.create_small_rackknob(PARAM("decay_times.low_rt60"), "Low");
	b.create_small_rackknob(PARAM("decay_times.mid_rt60"), "Mid");
	b.create_small_rackknob(PARAM("decay_times.hf_damping"), "HF Damping");
    }
    b.closeBox();

    b.openHorizontalBox("Eq1");
    {
	b.create_small_rackknob(PARAM("equalizer1.eq1_freq"), "Freq");
	b.create_small_rackknob(PARAM("equalizer1.eq1_level"), "Level");
    }
    b.closeBox();

    b.openHorizontalBox("Eq2");
    {
	b.create_small_rackknob(PARAM("equalizer2.eq2_freq"), "Freq");
	b.create_small_rackknob(PARAM("equalizer2.eq2_level"), "Level");
    }
    b.closeBox();
}
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

} // end namespace zita_rev1
} // end namespace pluginlib
