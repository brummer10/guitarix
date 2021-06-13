// generated from file '../src/LV2/faust/gxtubedelay.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "input12ax7_neg_table.h"
#include "input12ax7_table.h"
#include "math.h"
#include "output12ax7_neg_table.h"
#include "output12ax7_table.h"

namespace gxtubedelay {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec0[2];
	double fConst0;
	double fConst1;
	double fConst2;
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
	double fConst13;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fConst14;
	double fConst15;
	double fRec4[3];
	double fConst16;
	double fConst17;
	double fConst18;
	double fRec3[3];
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
	double fVec0[2];
	double fConst29;
	double fConst30;
	double fRec10[2];
	double fConst31;
	double fConst32;
	double fRec9[3];
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
	double fRec8[3];
	double fConst43;
	double fConst44;
	double fConst45;
	double fConst46;
	double fConst47;
	double fConst48;
	double fConst49;
	double fConst50;
	double fConst51;
	double fRec7[3];
	double fConst52;
	double fConst53;
	double fConst54;
	double fConst55;
	double fConst56;
	double fConst57;
	double fConst58;
	double fConst59;
	double fConst60;
	double fRec6[3];
	double fConst61;
	double fRec5[2];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec11[2];
	int IOTA;
	double *fVec1;
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fRec12[2];
	double fConst62;
	FAUSTFLOAT fVslider4;
	FAUSTFLOAT	*fVslider4_;
	double fConst63;
	double fConst64;
	double fRec13[2];
	double fRec14[2];
	double fRec15[2];
	double fRec16[2];
	double fRec2[2];
	double fConst65;
	double fRec1[2];
	double fRec20[3];
	double fRec19[3];
	double fConst66;
	double fConst67;
	double fRec27[2];
	double fRec26[3];
	double fVec2[2];
	double fConst68;
	double fConst69;
	double fRec25[2];
	double fConst70;
	double fRec24[3];
	double fConst71;
	double fRec23[3];
	double fRec22[3];
	double fRec21[2];
	double *fVec3;
	double fRec18[2];
	double fRec17[2];
	double fRec31[3];
	double fRec30[3];
	double fConst72;
	double fConst73;
	double fConst74;
	double fRec37[2];
	double fRec36[3];
	double fVec4[2];
	double fConst75;
	double fConst76;
	double fRec35[2];
	double fConst77;
	double fRec34[3];
	double fConst78;
	double fRec33[3];
	double fRec32[2];
	double *fVec5;
	double fRec29[2];
	double fRec28[2];
	double fRec41[3];
	double fRec40[3];
	double fConst79;
	double fConst80;
	double fConst81;
	double fRec46[2];
	double fRec45[3];
	double fVec6[2];
	double fConst82;
	double fConst83;
	double fRec44[2];
	double fConst84;
	double fRec43[3];
	double fConst85;
	double fRec42[2];
	double *fVec7;
	double fRec39[2];
	double fRec38[2];
	double fRec50[3];
	double fRec49[3];
	double fConst86;
	double fRec53[2];
	double fRec52[3];
	double fRec51[2];
	double *fVec8;
	double fRec48[2];
	double fRec47[2];

	bool mem_allocated;
	void mem_alloc();
	void mem_free();
	void connect(uint32_t port,void* data);
	void clear_state_f();
	int activate(bool start);
	void init(uint32_t sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);

	static void clear_state_f_static(PluginLV2*);
	static int activate_static(bool start, PluginLV2*);
	static void init_static(uint32_t sample_rate, PluginLV2*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginLV2(),
	  fVec1(0),
	  fVec3(0),
	  fVec5(0),
	  fVec7(0),
	  fVec8(0),
	  mem_allocated(false) {
	version = PLUGINLV2_VERSION;
	id = "gxtubedelay";
	name = N_("Tube Delay");
	mono_audio = compute_static;
	stereo_audio = 0;
	set_samplerate = init_static;
	activate_plugin = activate_static;
	connect_ports = connect_static;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec0[l0] = 0.0;
	for (int l1 = 0; (l1 < 3); l1 = (l1 + 1)) fRec4[l1] = 0.0;
	for (int l2 = 0; (l2 < 3); l2 = (l2 + 1)) fRec3[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fVec0[l3] = 0.0;
	for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) fRec10[l4] = 0.0;
	for (int l5 = 0; (l5 < 3); l5 = (l5 + 1)) fRec9[l5] = 0.0;
	for (int l6 = 0; (l6 < 3); l6 = (l6 + 1)) fRec8[l6] = 0.0;
	for (int l7 = 0; (l7 < 3); l7 = (l7 + 1)) fRec7[l7] = 0.0;
	for (int l8 = 0; (l8 < 3); l8 = (l8 + 1)) fRec6[l8] = 0.0;
	for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) fRec5[l9] = 0.0;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) fRec11[l10] = 0.0;
	for (int l11 = 0; (l11 < 262144); l11 = (l11 + 1)) fVec1[l11] = 0.0;
	for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) fRec12[l12] = 0.0;
	for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) fRec13[l13] = 0.0;
	for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) fRec14[l14] = 0.0;
	for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) fRec15[l15] = 0.0;
	for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) fRec16[l16] = 0.0;
	for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) fRec2[l17] = 0.0;
	for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) fRec1[l18] = 0.0;
	for (int l19 = 0; (l19 < 3); l19 = (l19 + 1)) fRec20[l19] = 0.0;
	for (int l20 = 0; (l20 < 3); l20 = (l20 + 1)) fRec19[l20] = 0.0;
	for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) fRec27[l21] = 0.0;
	for (int l22 = 0; (l22 < 3); l22 = (l22 + 1)) fRec26[l22] = 0.0;
	for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) fVec2[l23] = 0.0;
	for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) fRec25[l24] = 0.0;
	for (int l25 = 0; (l25 < 3); l25 = (l25 + 1)) fRec24[l25] = 0.0;
	for (int l26 = 0; (l26 < 3); l26 = (l26 + 1)) fRec23[l26] = 0.0;
	for (int l27 = 0; (l27 < 3); l27 = (l27 + 1)) fRec22[l27] = 0.0;
	for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) fRec21[l28] = 0.0;
	for (int l29 = 0; (l29 < 262144); l29 = (l29 + 1)) fVec3[l29] = 0.0;
	for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) fRec18[l30] = 0.0;
	for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) fRec17[l31] = 0.0;
	for (int l32 = 0; (l32 < 3); l32 = (l32 + 1)) fRec31[l32] = 0.0;
	for (int l33 = 0; (l33 < 3); l33 = (l33 + 1)) fRec30[l33] = 0.0;
	for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) fRec37[l34] = 0.0;
	for (int l35 = 0; (l35 < 3); l35 = (l35 + 1)) fRec36[l35] = 0.0;
	for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) fVec4[l36] = 0.0;
	for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) fRec35[l37] = 0.0;
	for (int l38 = 0; (l38 < 3); l38 = (l38 + 1)) fRec34[l38] = 0.0;
	for (int l39 = 0; (l39 < 3); l39 = (l39 + 1)) fRec33[l39] = 0.0;
	for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) fRec32[l40] = 0.0;
	for (int l41 = 0; (l41 < 262144); l41 = (l41 + 1)) fVec5[l41] = 0.0;
	for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) fRec29[l42] = 0.0;
	for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) fRec28[l43] = 0.0;
	for (int l44 = 0; (l44 < 3); l44 = (l44 + 1)) fRec41[l44] = 0.0;
	for (int l45 = 0; (l45 < 3); l45 = (l45 + 1)) fRec40[l45] = 0.0;
	for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) fRec46[l46] = 0.0;
	for (int l47 = 0; (l47 < 3); l47 = (l47 + 1)) fRec45[l47] = 0.0;
	for (int l48 = 0; (l48 < 2); l48 = (l48 + 1)) fVec6[l48] = 0.0;
	for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) fRec44[l49] = 0.0;
	for (int l50 = 0; (l50 < 3); l50 = (l50 + 1)) fRec43[l50] = 0.0;
	for (int l51 = 0; (l51 < 2); l51 = (l51 + 1)) fRec42[l51] = 0.0;
	for (int l52 = 0; (l52 < 262144); l52 = (l52 + 1)) fVec7[l52] = 0.0;
	for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) fRec39[l53] = 0.0;
	for (int l54 = 0; (l54 < 2); l54 = (l54 + 1)) fRec38[l54] = 0.0;
	for (int l55 = 0; (l55 < 3); l55 = (l55 + 1)) fRec50[l55] = 0.0;
	for (int l56 = 0; (l56 < 3); l56 = (l56 + 1)) fRec49[l56] = 0.0;
	for (int l57 = 0; (l57 < 2); l57 = (l57 + 1)) fRec53[l57] = 0.0;
	for (int l58 = 0; (l58 < 3); l58 = (l58 + 1)) fRec52[l58] = 0.0;
	for (int l59 = 0; (l59 < 2); l59 = (l59 + 1)) fRec51[l59] = 0.0;
	for (int l60 = 0; (l60 < 262144); l60 = (l60 + 1)) fVec8[l60] = 0.0;
	for (int l61 = 0; (l61 < 2); l61 = (l61 + 1)) fRec48[l61] = 0.0;
	for (int l62 = 0; (l62 < 2); l62 = (l62 + 1)) fRec47[l62] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = (2.0824083016883199e-05 * fConst0);
	fConst2 = (fConst1 + 0.00044401518960621899);
	fConst3 = (1.0 / fConst2);
	fConst4 = (0.00061718744654050601 * fConst0);
	fConst5 = (0.0 - fConst4);
	fConst6 = std::tan((37699.111843077517 / fConst0));
	fConst7 = (1.0 / fConst6);
	fConst8 = (1.0 / (((fConst7 + 1.4142135623730949) / fConst6) + 1.0));
	fConst9 = std::tan((376.99111843077515 / fConst0));
	fConst10 = (1.0 / fConst9);
	fConst11 = (1.0 / (((fConst10 + 1.4142135623730949) / fConst9) + 1.0));
	fConst12 = mydsp_faustpower2_f(fConst9);
	fConst13 = (1.0 / fConst12);
	fConst14 = (((fConst10 + -1.4142135623730949) / fConst9) + 1.0);
	fConst15 = (2.0 * (1.0 - fConst13));
	fConst16 = (0.0 - (2.0 / fConst12));
	fConst17 = (((fConst7 + -1.4142135623730949) / fConst6) + 1.0);
	fConst18 = (2.0 * (1.0 - (1.0 / mydsp_faustpower2_f(fConst6))));
	fConst19 = (2.0824050069881302e-05 * fConst0);
	fConst20 = (fConst19 + 0.00044559664569599199);
	fConst21 = (fConst0 / fConst20);
	fConst22 = std::tan((20517.741620594938 / fConst0));
	fConst23 = (1.0 / fConst22);
	fConst24 = (1.0 / (((fConst23 + 1.0000000000000004) / fConst22) + 1.0));
	fConst25 = mydsp_faustpower2_f(fConst22);
	fConst26 = (1.0 / fConst25);
	fConst27 = (fConst23 + 1.0);
	fConst28 = (0.0 - (1.0 / (fConst22 * fConst27)));
	fConst29 = (1.0 / fConst27);
	fConst30 = (1.0 - fConst23);
	fConst31 = (((fConst23 + -1.0000000000000004) / fConst22) + 1.0);
	fConst32 = (2.0 * (1.0 - fConst26));
	fConst33 = (0.0 - (2.0 / fConst25));
	fConst34 = std::tan((3769.9111843077517 / fConst0));
	fConst35 = (1.0 / fConst34);
	fConst36 = (fConst35 + 1.0);
	fConst37 = (1.0 / ((fConst36 / fConst34) + 1.0));
	fConst38 = (1.0 - fConst35);
	fConst39 = (1.0 - (fConst38 / fConst34));
	fConst40 = mydsp_faustpower2_f(fConst34);
	fConst41 = (1.0 / fConst40);
	fConst42 = (2.0 * (1.0 - fConst41));
	fConst43 = std::tan((659.73445725385659 / fConst0));
	fConst44 = (1.0 / fConst43);
	fConst45 = (fConst44 + 1.0);
	fConst46 = (1.0 / ((fConst45 / fConst43) + 1.0));
	fConst47 = (1.0 - fConst44);
	fConst48 = (1.0 - (fConst47 / fConst43));
	fConst49 = mydsp_faustpower2_f(fConst43);
	fConst50 = (1.0 / fConst49);
	fConst51 = (2.0 * (1.0 - fConst50));
	fConst52 = std::tan((270.1769682087222 / fConst0));
	fConst53 = (1.0 / fConst52);
	fConst54 = (fConst53 + 1.0);
	fConst55 = (1.0 / ((fConst54 / fConst52) + 1.0));
	fConst56 = (1.0 - fConst53);
	fConst57 = (1.0 - (fConst56 / fConst52));
	fConst58 = mydsp_faustpower2_f(fConst52);
	fConst59 = (1.0 / fConst58);
	fConst60 = (2.0 * (1.0 - fConst59));
	fConst61 = ((0.00044559664569599199 - fConst19) / fConst20);
	fConst62 = (0.001 * fConst0);
	fConst63 = (10.0 / fConst0);
	fConst64 = (0.0 - fConst63);
	fConst65 = ((0.00044401518960621899 - fConst1) / fConst2);
	fConst66 = (1.0 / (((fConst35 + 1.0000000000000004) / fConst34) + 1.0));
	fConst67 = (1.0 / (fConst34 * fConst36));
	fConst68 = (0.0 - fConst67);
	fConst69 = (fConst38 / fConst36);
	fConst70 = (((fConst35 + -1.0000000000000004) / fConst34) + 1.0);
	fConst71 = (0.0 - (2.0 / fConst40));
	fConst72 = (1.0 / (((fConst44 + 1.0000000000000004) / fConst43) + 1.0));
	fConst73 = (1.0 / (fConst43 * fConst45));
	fConst74 = (1.0 / fConst36);
	fConst75 = (0.0 - fConst73);
	fConst76 = (fConst47 / fConst45);
	fConst77 = (((fConst44 + -1.0000000000000004) / fConst43) + 1.0);
	fConst78 = (0.0 - (2.0 / fConst49));
	fConst79 = (1.0 / (((fConst53 + 1.0000000000000004) / fConst52) + 1.0));
	fConst80 = (1.0 / (fConst52 * fConst54));
	fConst81 = (1.0 / fConst45);
	fConst82 = (0.0 - fConst80);
	fConst83 = (fConst56 / fConst54);
	fConst84 = (((fConst53 + -1.0000000000000004) / fConst52) + 1.0);
	fConst85 = (0.0 - (2.0 / fConst58));
	fConst86 = (1.0 / fConst54);
	IOTA = 0;
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void Dsp::mem_alloc()
{
	if (!fVec1) fVec1 = new double[262144];
	if (!fVec3) fVec3 = new double[262144];
	if (!fVec5) fVec5 = new double[262144];
	if (!fVec7) fVec7 = new double[262144];
	if (!fVec8) fVec8 = new double[262144];
	mem_allocated = true;
}

void Dsp::mem_free()
{
	mem_allocated = false;
	if (fVec1) { delete fVec1; fVec1 = 0; }
	if (fVec3) { delete fVec3; fVec3 = 0; }
	if (fVec5) { delete fVec5; fVec5 = 0; }
	if (fVec7) { delete fVec7; fVec7 = 0; }
	if (fVec8) { delete fVec8; fVec8 = 0; }
}

int Dsp::activate(bool start)
{
	if (start) {
		if (!mem_allocated) {
			mem_alloc();
			clear_state_f();
		}
	} else if (mem_allocated) {
		mem_free();
	}
	return 0;
}

int Dsp::activate_static(bool start, PluginLV2 *p)
{
	return static_cast<Dsp*>(p)->activate(start);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fVslider0 (*fVslider0_)
#define fVslider1 (*fVslider1_)
#define fVslider2 (*fVslider2_)
#define fVslider3 (*fVslider3_)
#define fVslider4 (*fVslider4_)
	double fSlow0 = (0.0070000000000000062 * std::pow(10.0, (0.050000000000000003 * double(fVslider0))));
	double fSlow1 = double(fVslider1);
	double fSlow2 = (0.004073836948085289 * (std::exp(double(fVslider2)) + -1.0));
	double fSlow3 = (0.004073836948085289 * (std::exp(double(fVslider3)) + -1.0));
	double fSlow4 = (fConst62 * double(fVslider4));
	for (int i = 0; (i < count); i = (i + 1)) {
		fRec0[0] = (fSlow0 + (0.99299999999999999 * fRec0[1]));
		fRec4[0] = ((fSlow1 * fRec2[1]) - (fConst11 * ((fConst14 * fRec4[2]) + (fConst15 * fRec4[1]))));
		fRec3[0] = ((fConst11 * (((fConst13 * fRec4[0]) + (fConst16 * fRec4[1])) + (fConst13 * fRec4[2]))) - (fConst8 * ((fConst17 * fRec3[2]) + (fConst18 * fRec3[1]))));
		double fTemp0 = double(input0[i]);
		fVec0[0] = fTemp0;
		fRec10[0] = ((fConst28 * fVec0[1]) - (fConst29 * ((fConst30 * fRec10[1]) - (fConst23 * fTemp0))));
		fRec9[0] = (fRec10[0] - (fConst24 * ((fConst31 * fRec9[2]) + (fConst32 * fRec9[1]))));
		double fTemp1 = (fConst42 * fRec8[1]);
		fRec8[0] = ((fConst24 * (((fConst26 * fRec9[0]) + (fConst33 * fRec9[1])) + (fConst26 * fRec9[2]))) - (fConst37 * ((fConst39 * fRec8[2]) + fTemp1)));
		double fTemp2 = (fConst51 * fRec7[1]);
		fRec7[0] = ((fRec8[2] + (fConst37 * (fTemp1 + (fConst39 * fRec8[0])))) - (fConst46 * ((fConst48 * fRec7[2]) + fTemp2)));
		double fTemp3 = (fConst60 * fRec6[1]);
		fRec6[0] = ((fRec7[2] + (fConst46 * (fTemp2 + (fConst48 * fRec7[0])))) - (fConst55 * ((fConst57 * fRec6[2]) + fTemp3)));
		fRec5[0] = ((fRec6[2] + (fConst55 * (fTemp3 + (fConst57 * fRec6[0])))) - (fConst61 * fRec5[1]));
		fRec11[0] = (fSlow2 + (0.99299999999999999 * fRec11[1]));
		double fTemp4 = (0.0 - (0.00069742843622086102 * fRec11[0]));
		double fTemp5 = (fConst21 * ((fRec5[0] * fTemp4) + (0.00069742843622086102 * (fRec11[0] * fRec5[1]))));
		double fTemp6 = ((fConst8 * (fRec3[2] + (fRec3[0] + (2.0 * fRec3[1])))) + (int(signbit(double(fTemp5))) ? double(input12ax7_negclip(double(fTemp5))) : double(input12ax7clip(double(fTemp5)))));
		fVec1[(IOTA & 262143)] = fTemp6;
		fRec12[0] = (fSlow3 + (0.99299999999999999 * fRec12[1]));
		double fTemp7 = ((fRec13[1] != 0.0) ? (((fRec14[1] > 0.0) & (fRec14[1] < 1.0)) ? fRec13[1] : 0.0) : (((fRec14[1] == 0.0) & (fSlow4 != fRec15[1])) ? fConst63 : (((fRec14[1] == 1.0) & (fSlow4 != fRec16[1])) ? fConst64 : 0.0)));
		fRec13[0] = fTemp7;
		fRec14[0] = std::max<double>(0.0, std::min<double>(1.0, (fRec14[1] + fTemp7)));
		fRec15[0] = (((fRec14[1] >= 1.0) & (fRec16[1] != fSlow4)) ? fSlow4 : fRec15[1]);
		fRec16[0] = (((fRec14[1] <= 0.0) & (fRec15[1] != fSlow4)) ? fSlow4 : fRec16[1]);
		int iTemp8 = int(std::min<double>(131072.0, std::max<double>(0.0, fRec15[0])));
		double fTemp9 = fVec1[((IOTA - iTemp8) & 262143)];
		int iTemp10 = int(std::min<double>(131072.0, std::max<double>(0.0, fRec16[0])));
		fRec2[0] = (fTemp6 + (fRec12[0] * (fTemp9 + (fRec14[0] * (fVec1[((IOTA - iTemp10) & 262143)] - fTemp9)))));
		fRec1[0] = (fRec2[0] - (fConst65 * fRec1[1]));
		double fTemp11 = (fConst3 * ((fConst5 * fRec1[0]) + (fConst4 * fRec1[1])));
		fRec20[0] = ((fSlow1 * fRec18[1]) - (fConst11 * ((fConst14 * fRec20[2]) + (fConst15 * fRec20[1]))));
		fRec19[0] = ((fConst11 * (((fConst13 * fRec20[0]) + (fConst16 * fRec20[1])) + (fConst13 * fRec20[2]))) - (fConst8 * ((fConst17 * fRec19[2]) + (fConst18 * fRec19[1]))));
		fRec27[0] = (0.0 - (fConst29 * ((fConst30 * fRec27[1]) - (fTemp0 + fVec0[1]))));
		fRec26[0] = (fRec27[0] - (fConst24 * ((fConst31 * fRec26[2]) + (fConst32 * fRec26[1]))));
		double fTemp12 = (fRec26[2] + (fRec26[0] + (2.0 * fRec26[1])));
		fVec2[0] = fTemp12;
		fRec25[0] = ((fConst24 * ((fConst67 * fTemp12) + (fConst68 * fVec2[1]))) - (fConst69 * fRec25[1]));
		fRec24[0] = (fRec25[0] - (fConst66 * ((fConst70 * fRec24[2]) + (fConst42 * fRec24[1]))));
		double fTemp13 = (fConst51 * fRec23[1]);
		fRec23[0] = ((fConst66 * (((fConst41 * fRec24[0]) + (fConst71 * fRec24[1])) + (fConst41 * fRec24[2]))) - (fConst46 * ((fConst48 * fRec23[2]) + fTemp13)));
		double fTemp14 = (fConst60 * fRec22[1]);
		fRec22[0] = ((fRec23[2] + (fConst46 * (fTemp13 + (fConst48 * fRec23[0])))) - (fConst55 * ((fConst57 * fRec22[2]) + fTemp14)));
		fRec21[0] = ((fRec22[2] + (fConst55 * (fTemp14 + (fConst57 * fRec22[0])))) - (fConst61 * fRec21[1]));
		double fTemp15 = (fConst21 * ((fRec21[0] * fTemp4) + (0.00069742843622086102 * (fRec11[0] * fRec21[1]))));
		double fTemp16 = ((fConst8 * (fRec19[2] + (fRec19[0] + (2.0 * fRec19[1])))) + (int(signbit(double(fTemp15))) ? double(input12ax7_negclip(double(fTemp15))) : double(input12ax7clip(double(fTemp15)))));
		fVec3[(IOTA & 262143)] = fTemp16;
		double fTemp17 = fVec3[((IOTA - iTemp8) & 262143)];
		fRec18[0] = (fTemp16 + (fRec12[0] * (fTemp17 + (fRec14[0] * (fVec3[((IOTA - iTemp10) & 262143)] - fTemp17)))));
		fRec17[0] = (fRec18[0] - (fConst65 * fRec17[1]));
		double fTemp18 = (fConst3 * ((fConst5 * fRec17[0]) + (fConst4 * fRec17[1])));
		fRec31[0] = ((fSlow1 * fRec29[1]) - (fConst11 * ((fConst14 * fRec31[2]) + (fConst15 * fRec31[1]))));
		fRec30[0] = ((fConst11 * (((fConst13 * fRec31[0]) + (fConst16 * fRec31[1])) + (fConst13 * fRec31[2]))) - (fConst8 * ((fConst17 * fRec30[2]) + (fConst18 * fRec30[1]))));
		fRec37[0] = (0.0 - (fConst74 * ((fConst38 * fRec37[1]) - (fConst24 * (fTemp12 + fVec2[1])))));
		fRec36[0] = (fRec37[0] - (fConst66 * ((fConst70 * fRec36[2]) + (fConst42 * fRec36[1]))));
		double fTemp19 = (fRec36[2] + (fRec36[0] + (2.0 * fRec36[1])));
		fVec4[0] = fTemp19;
		fRec35[0] = ((fConst66 * ((fConst73 * fTemp19) + (fConst75 * fVec4[1]))) - (fConst76 * fRec35[1]));
		fRec34[0] = (fRec35[0] - (fConst72 * ((fConst77 * fRec34[2]) + (fConst51 * fRec34[1]))));
		double fTemp20 = (fConst60 * fRec33[1]);
		fRec33[0] = ((fConst72 * (((fConst50 * fRec34[0]) + (fConst78 * fRec34[1])) + (fConst50 * fRec34[2]))) - (fConst55 * ((fConst57 * fRec33[2]) + fTemp20)));
		fRec32[0] = ((fRec33[2] + (fConst55 * (fTemp20 + (fConst57 * fRec33[0])))) - (fConst61 * fRec32[1]));
		double fTemp21 = (fConst21 * ((fRec32[0] * fTemp4) + (0.00069742843622086102 * (fRec11[0] * fRec32[1]))));
		double fTemp22 = ((fConst8 * (fRec30[2] + (fRec30[0] + (2.0 * fRec30[1])))) + (int(signbit(double(fTemp21))) ? double(input12ax7_negclip(double(fTemp21))) : double(input12ax7clip(double(fTemp21)))));
		fVec5[(IOTA & 262143)] = fTemp22;
		double fTemp23 = fVec5[((IOTA - iTemp8) & 262143)];
		fRec29[0] = (fTemp22 + (fRec12[0] * (fTemp23 + (fRec14[0] * (fVec5[((IOTA - iTemp10) & 262143)] - fTemp23)))));
		fRec28[0] = (fRec29[0] - (fConst65 * fRec28[1]));
		double fTemp24 = (fConst3 * ((fConst5 * fRec28[0]) + (fConst4 * fRec28[1])));
		fRec41[0] = ((fSlow1 * fRec39[1]) - (fConst11 * ((fConst14 * fRec41[2]) + (fConst15 * fRec41[1]))));
		fRec40[0] = ((fConst11 * (((fConst13 * fRec41[0]) + (fConst16 * fRec41[1])) + (fConst13 * fRec41[2]))) - (fConst8 * ((fConst17 * fRec40[2]) + (fConst18 * fRec40[1]))));
		fRec46[0] = (0.0 - (fConst81 * ((fConst47 * fRec46[1]) - (fConst66 * (fTemp19 + fVec4[1])))));
		fRec45[0] = (fRec46[0] - (fConst72 * ((fConst77 * fRec45[2]) + (fConst51 * fRec45[1]))));
		double fTemp25 = (fRec45[2] + (fRec45[0] + (2.0 * fRec45[1])));
		fVec6[0] = fTemp25;
		fRec44[0] = ((fConst72 * ((fConst80 * fTemp25) + (fConst82 * fVec6[1]))) - (fConst83 * fRec44[1]));
		fRec43[0] = (fRec44[0] - (fConst79 * ((fConst84 * fRec43[2]) + (fConst60 * fRec43[1]))));
		fRec42[0] = ((fConst79 * (((fConst59 * fRec43[0]) + (fConst85 * fRec43[1])) + (fConst59 * fRec43[2]))) - (fConst61 * fRec42[1]));
		double fTemp26 = (fConst21 * ((fRec42[0] * fTemp4) + (0.00069742843622086102 * (fRec11[0] * fRec42[1]))));
		double fTemp27 = ((fConst8 * (fRec40[2] + (fRec40[0] + (2.0 * fRec40[1])))) + (int(signbit(double(fTemp26))) ? double(input12ax7_negclip(double(fTemp26))) : double(input12ax7clip(double(fTemp26)))));
		fVec7[(IOTA & 262143)] = fTemp27;
		double fTemp28 = fVec7[((IOTA - iTemp8) & 262143)];
		fRec39[0] = (fTemp27 + (fRec12[0] * (fTemp28 + (fRec14[0] * (fVec7[((IOTA - iTemp10) & 262143)] - fTemp28)))));
		fRec38[0] = (fRec39[0] - (fConst65 * fRec38[1]));
		double fTemp29 = (fConst3 * ((fConst5 * fRec38[0]) + (fConst4 * fRec38[1])));
		fRec50[0] = ((fSlow1 * fRec48[1]) - (fConst11 * ((fConst14 * fRec50[2]) + (fConst15 * fRec50[1]))));
		fRec49[0] = ((fConst11 * (((fConst13 * fRec50[0]) + (fConst16 * fRec50[1])) + (fConst13 * fRec50[2]))) - (fConst8 * ((fConst17 * fRec49[2]) + (fConst18 * fRec49[1]))));
		fRec53[0] = (0.0 - (fConst86 * ((fConst56 * fRec53[1]) - (fConst72 * (fTemp25 + fVec6[1])))));
		fRec52[0] = (fRec53[0] - (fConst79 * ((fConst84 * fRec52[2]) + (fConst60 * fRec52[1]))));
		fRec51[0] = ((fConst79 * (fRec52[2] + (fRec52[0] + (2.0 * fRec52[1])))) - (fConst61 * fRec51[1]));
		double fTemp30 = (fConst21 * ((fRec51[0] * fTemp4) + (0.00069742843622086102 * (fRec11[0] * fRec51[1]))));
		double fTemp31 = ((fConst8 * (fRec49[2] + (fRec49[0] + (2.0 * fRec49[1])))) + (int(signbit(double(fTemp30))) ? double(input12ax7_negclip(double(fTemp30))) : double(input12ax7clip(double(fTemp30)))));
		fVec8[(IOTA & 262143)] = fTemp31;
		double fTemp32 = fVec8[((IOTA - iTemp8) & 262143)];
		fRec48[0] = (fTemp31 + (fRec12[0] * (fTemp32 + (fRec14[0] * (fVec8[((IOTA - iTemp10) & 262143)] - fTemp32)))));
		fRec47[0] = (fRec48[0] - (fConst65 * fRec47[1]));
		double fTemp33 = (fConst3 * ((fConst5 * fRec47[0]) + (fConst4 * fRec47[1])));
		output0[i] = FAUSTFLOAT((fRec0[0] * (((((int(signbit(double(fTemp11))) ? double(output12ax7_negclip(double(fTemp11))) : double(output12ax7clip(double(fTemp11)))) + (int(signbit(double(fTemp18))) ? double(output12ax7_negclip(double(fTemp18))) : double(output12ax7clip(double(fTemp18))))) + (int(signbit(double(fTemp24))) ? double(output12ax7_negclip(double(fTemp24))) : double(output12ax7clip(double(fTemp24))))) + (int(signbit(double(fTemp29))) ? double(output12ax7_negclip(double(fTemp29))) : double(output12ax7clip(double(fTemp29))))) + (int(signbit(double(fTemp33))) ? double(output12ax7_negclip(double(fTemp33))) : double(output12ax7clip(double(fTemp33)))))));
		fRec0[1] = fRec0[0];
		fRec4[2] = fRec4[1];
		fRec4[1] = fRec4[0];
		fRec3[2] = fRec3[1];
		fRec3[1] = fRec3[0];
		fVec0[1] = fVec0[0];
		fRec10[1] = fRec10[0];
		fRec9[2] = fRec9[1];
		fRec9[1] = fRec9[0];
		fRec8[2] = fRec8[1];
		fRec8[1] = fRec8[0];
		fRec7[2] = fRec7[1];
		fRec7[1] = fRec7[0];
		fRec6[2] = fRec6[1];
		fRec6[1] = fRec6[0];
		fRec5[1] = fRec5[0];
		fRec11[1] = fRec11[0];
		IOTA = (IOTA + 1);
		fRec12[1] = fRec12[0];
		fRec13[1] = fRec13[0];
		fRec14[1] = fRec14[0];
		fRec15[1] = fRec15[0];
		fRec16[1] = fRec16[0];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
		fRec20[2] = fRec20[1];
		fRec20[1] = fRec20[0];
		fRec19[2] = fRec19[1];
		fRec19[1] = fRec19[0];
		fRec27[1] = fRec27[0];
		fRec26[2] = fRec26[1];
		fRec26[1] = fRec26[0];
		fVec2[1] = fVec2[0];
		fRec25[1] = fRec25[0];
		fRec24[2] = fRec24[1];
		fRec24[1] = fRec24[0];
		fRec23[2] = fRec23[1];
		fRec23[1] = fRec23[0];
		fRec22[2] = fRec22[1];
		fRec22[1] = fRec22[0];
		fRec21[1] = fRec21[0];
		fRec18[1] = fRec18[0];
		fRec17[1] = fRec17[0];
		fRec31[2] = fRec31[1];
		fRec31[1] = fRec31[0];
		fRec30[2] = fRec30[1];
		fRec30[1] = fRec30[0];
		fRec37[1] = fRec37[0];
		fRec36[2] = fRec36[1];
		fRec36[1] = fRec36[0];
		fVec4[1] = fVec4[0];
		fRec35[1] = fRec35[0];
		fRec34[2] = fRec34[1];
		fRec34[1] = fRec34[0];
		fRec33[2] = fRec33[1];
		fRec33[1] = fRec33[0];
		fRec32[1] = fRec32[0];
		fRec29[1] = fRec29[0];
		fRec28[1] = fRec28[0];
		fRec41[2] = fRec41[1];
		fRec41[1] = fRec41[0];
		fRec40[2] = fRec40[1];
		fRec40[1] = fRec40[0];
		fRec46[1] = fRec46[0];
		fRec45[2] = fRec45[1];
		fRec45[1] = fRec45[0];
		fVec6[1] = fVec6[0];
		fRec44[1] = fRec44[0];
		fRec43[2] = fRec43[1];
		fRec43[1] = fRec43[0];
		fRec42[1] = fRec42[0];
		fRec39[1] = fRec39[0];
		fRec38[1] = fRec38[0];
		fRec50[2] = fRec50[1];
		fRec50[1] = fRec50[0];
		fRec49[2] = fRec49[1];
		fRec49[1] = fRec49[0];
		fRec53[1] = fRec53[0];
		fRec52[2] = fRec52[1];
		fRec52[1] = fRec52[0];
		fRec51[1] = fRec51[0];
		fRec48[1] = fRec48[0];
		fRec47[1] = fRec47[0];
	}
#undef fVslider0
#undef fVslider1
#undef fVslider2
#undef fVslider3
#undef fVslider4
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
		fVslider2_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case DELAY: 
		fVslider4_ = (float*)data; // , 0.10000000000000001, 0.10000000000000001, 2500.0, 0.10000000000000001 
		break;
	case FEEDBACK: 
		fVslider1_ = (float*)data; // , 0.0, 0.0, 0.69999999999999996, 0.01 
		break;
	case LEVEL: 
		fVslider3_ = (float*)data; // , 0.0, 0.0, 1.0, 0.10000000000000001 
		break;
	case OUTPUT: 
		fVslider0_ = (float*)data; // , 0.0, -20.0, 20.0, 0.10000000000000001 
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
   DELAY, 
   FEEDBACK, 
   LEVEL, 
   OUTPUT, 
} PortIndex;
*/

} // end namespace gxtubedelay
