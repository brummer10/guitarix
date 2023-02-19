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
	double fConst3;
	double fConst6;
	double fConst9;
	double fConst10;
	double fConst12;
	double fConst13;
	double fConst16;
	double fConst17;
	double fConst19;
	double fConst20;
	double fConst23;
	double fConst24;
	double fConst26;
	double fConst27;
	double fConst30;
	double fConst31;
	double fConst32;
	double fConst33;
	double fConst34;
	double fVec0[2];
	double fConst35;
	double fConst37;
	double fRec10[2];
	double fRec9[3];
	double fVec1[2];
	double fConst38;
	double fConst40;
	double fRec8[2];
	double fRec7[3];
	double fVec2[2];
	double fConst41;
	double fConst43;
	double fRec6[2];
	double fRec5[3];
	double fVec3[2];
	double fConst44;
	double fConst46;
	double fRec4[2];
	double fRec3[3];
	double fRec2[2];
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec11[2];
	double fConst47;
	double fConst49;
	double fConst51;
	double fConst52;
	double fConst55;
	double fConst56;
	double fConst58;
	double fConst59;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec13[3];
	double fConst60;
	double fRec12[3];
	int IOTA0;
	double *fVec4;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fConst61;
	double fConst62;
	double fConst63;
	double fRec14[2];
	double fRec15[2];
	double fRec16[2];
	double fRec17[2];
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fRec18[2];
	double fRec1[2];
	double fRec0[2];
	double fConst64;
	double fConst65;
	double fConst66;
	double fConst67;
	double fConst68;
	double fConst69;
	double fRec23[2];
	double fRec22[3];
	double fConst70;
	double fRec21[2];
	double fRec25[3];
	double fRec24[3];
	double *fVec5;
	double fRec20[2];
	double fRec19[2];
	double fConst71;
	double fConst72;
	double fConst73;
	double fConst74;
	double fConst75;
	double fRec31[2];
	double fRec30[3];
	double fConst76;
	double fRec29[3];
	double fRec28[2];
	double fRec33[3];
	double fRec32[3];
	double *fVec6;
	double fRec27[2];
	double fRec26[2];
	double fConst77;
	double fConst78;
	double fConst79;
	double fConst80;
	double fConst81;
	double fRec40[2];
	double fRec39[3];
	double fConst82;
	double fRec38[3];
	double fRec37[3];
	double fRec36[2];
	double fRec42[3];
	double fRec41[3];
	double *fVec7;
	double fRec35[2];
	double fRec34[2];
	double fConst83;
	double fConst84;
	double fConst85;
	double fRec50[2];
	double fRec49[3];
	double fConst86;
	double fRec48[3];
	double fRec47[3];
	double fRec46[3];
	double fRec45[2];
	double fRec52[3];
	double fRec51[3];
	double *fVec8;
	double fRec44[2];
	double fRec43[2];
	FAUSTFLOAT fVslider4;
	FAUSTFLOAT	*fVslider4_;
	double fRec53[2];

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
	  fVec4(0),
	  fVec5(0),
	  fVec6(0),
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fVec0[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec10[l1] = 0.0;
	for (int l2 = 0; l2 < 3; l2 = l2 + 1) fRec9[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fVec1[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fRec8[l4] = 0.0;
	for (int l5 = 0; l5 < 3; l5 = l5 + 1) fRec7[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fVec2[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec6[l7] = 0.0;
	for (int l8 = 0; l8 < 3; l8 = l8 + 1) fRec5[l8] = 0.0;
	for (int l9 = 0; l9 < 2; l9 = l9 + 1) fVec3[l9] = 0.0;
	for (int l10 = 0; l10 < 2; l10 = l10 + 1) fRec4[l10] = 0.0;
	for (int l11 = 0; l11 < 3; l11 = l11 + 1) fRec3[l11] = 0.0;
	for (int l12 = 0; l12 < 2; l12 = l12 + 1) fRec2[l12] = 0.0;
	for (int l13 = 0; l13 < 2; l13 = l13 + 1) fRec11[l13] = 0.0;
	for (int l14 = 0; l14 < 3; l14 = l14 + 1) fRec13[l14] = 0.0;
	for (int l15 = 0; l15 < 3; l15 = l15 + 1) fRec12[l15] = 0.0;
	for (int l16 = 0; l16 < 262144; l16 = l16 + 1) fVec4[l16] = 0.0;
	for (int l17 = 0; l17 < 2; l17 = l17 + 1) fRec14[l17] = 0.0;
	for (int l18 = 0; l18 < 2; l18 = l18 + 1) fRec15[l18] = 0.0;
	for (int l19 = 0; l19 < 2; l19 = l19 + 1) fRec16[l19] = 0.0;
	for (int l20 = 0; l20 < 2; l20 = l20 + 1) fRec17[l20] = 0.0;
	for (int l21 = 0; l21 < 2; l21 = l21 + 1) fRec18[l21] = 0.0;
	for (int l22 = 0; l22 < 2; l22 = l22 + 1) fRec1[l22] = 0.0;
	for (int l23 = 0; l23 < 2; l23 = l23 + 1) fRec0[l23] = 0.0;
	for (int l24 = 0; l24 < 2; l24 = l24 + 1) fRec23[l24] = 0.0;
	for (int l25 = 0; l25 < 3; l25 = l25 + 1) fRec22[l25] = 0.0;
	for (int l26 = 0; l26 < 2; l26 = l26 + 1) fRec21[l26] = 0.0;
	for (int l27 = 0; l27 < 3; l27 = l27 + 1) fRec25[l27] = 0.0;
	for (int l28 = 0; l28 < 3; l28 = l28 + 1) fRec24[l28] = 0.0;
	for (int l29 = 0; l29 < 262144; l29 = l29 + 1) fVec5[l29] = 0.0;
	for (int l30 = 0; l30 < 2; l30 = l30 + 1) fRec20[l30] = 0.0;
	for (int l31 = 0; l31 < 2; l31 = l31 + 1) fRec19[l31] = 0.0;
	for (int l32 = 0; l32 < 2; l32 = l32 + 1) fRec31[l32] = 0.0;
	for (int l33 = 0; l33 < 3; l33 = l33 + 1) fRec30[l33] = 0.0;
	for (int l34 = 0; l34 < 3; l34 = l34 + 1) fRec29[l34] = 0.0;
	for (int l35 = 0; l35 < 2; l35 = l35 + 1) fRec28[l35] = 0.0;
	for (int l36 = 0; l36 < 3; l36 = l36 + 1) fRec33[l36] = 0.0;
	for (int l37 = 0; l37 < 3; l37 = l37 + 1) fRec32[l37] = 0.0;
	for (int l38 = 0; l38 < 262144; l38 = l38 + 1) fVec6[l38] = 0.0;
	for (int l39 = 0; l39 < 2; l39 = l39 + 1) fRec27[l39] = 0.0;
	for (int l40 = 0; l40 < 2; l40 = l40 + 1) fRec26[l40] = 0.0;
	for (int l41 = 0; l41 < 2; l41 = l41 + 1) fRec40[l41] = 0.0;
	for (int l42 = 0; l42 < 3; l42 = l42 + 1) fRec39[l42] = 0.0;
	for (int l43 = 0; l43 < 3; l43 = l43 + 1) fRec38[l43] = 0.0;
	for (int l44 = 0; l44 < 3; l44 = l44 + 1) fRec37[l44] = 0.0;
	for (int l45 = 0; l45 < 2; l45 = l45 + 1) fRec36[l45] = 0.0;
	for (int l46 = 0; l46 < 3; l46 = l46 + 1) fRec42[l46] = 0.0;
	for (int l47 = 0; l47 < 3; l47 = l47 + 1) fRec41[l47] = 0.0;
	for (int l48 = 0; l48 < 262144; l48 = l48 + 1) fVec7[l48] = 0.0;
	for (int l49 = 0; l49 < 2; l49 = l49 + 1) fRec35[l49] = 0.0;
	for (int l50 = 0; l50 < 2; l50 = l50 + 1) fRec34[l50] = 0.0;
	for (int l51 = 0; l51 < 2; l51 = l51 + 1) fRec50[l51] = 0.0;
	for (int l52 = 0; l52 < 3; l52 = l52 + 1) fRec49[l52] = 0.0;
	for (int l53 = 0; l53 < 3; l53 = l53 + 1) fRec48[l53] = 0.0;
	for (int l54 = 0; l54 < 3; l54 = l54 + 1) fRec47[l54] = 0.0;
	for (int l55 = 0; l55 < 3; l55 = l55 + 1) fRec46[l55] = 0.0;
	for (int l56 = 0; l56 < 2; l56 = l56 + 1) fRec45[l56] = 0.0;
	for (int l57 = 0; l57 < 3; l57 = l57 + 1) fRec52[l57] = 0.0;
	for (int l58 = 0; l58 < 3; l58 = l58 + 1) fRec51[l58] = 0.0;
	for (int l59 = 0; l59 < 262144; l59 = l59 + 1) fVec8[l59] = 0.0;
	for (int l60 = 0; l60 < 2; l60 = l60 + 1) fRec44[l60] = 0.0;
	for (int l61 = 0; l61 < 2; l61 = l61 + 1) fRec43[l61] = 0.0;
	for (int l62 = 0; l62 < 2; l62 = l62 + 1) fRec53[l62] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = 2.08240830168832e-05 * fConst0;
	double fConst2 = fConst1 + 0.000444015189606219;
	fConst3 = (0.000444015189606219 - fConst1) / fConst2;
	double fConst4 = 2.08240500698813e-05 * fConst0;
	double fConst5 = fConst4 + 0.000445596645695992;
	fConst6 = (0.000445596645695992 - fConst4) / fConst5;
	double fConst7 = std::tan(270.1769682087222 / fConst0);
	double fConst8 = mydsp_faustpower2_f(fConst7);
	fConst9 = 1.0 / fConst8;
	fConst10 = 2.0 * (1.0 - fConst9);
	double fConst11 = 1.0 / fConst7;
	fConst12 = (fConst11 + -1.0000000000000004) / fConst7 + 1.0;
	fConst13 = 1.0 / ((fConst11 + 1.0000000000000004) / fConst7 + 1.0);
	double fConst14 = std::tan(659.7344572538566 / fConst0);
	double fConst15 = mydsp_faustpower2_f(fConst14);
	fConst16 = 1.0 / fConst15;
	fConst17 = 2.0 * (1.0 - fConst16);
	double fConst18 = 1.0 / fConst14;
	fConst19 = (fConst18 + -1.0000000000000004) / fConst14 + 1.0;
	fConst20 = 1.0 / ((fConst18 + 1.0000000000000004) / fConst14 + 1.0);
	double fConst21 = std::tan(3769.9111843077517 / fConst0);
	double fConst22 = mydsp_faustpower2_f(fConst21);
	fConst23 = 1.0 / fConst22;
	fConst24 = 2.0 * (1.0 - fConst23);
	double fConst25 = 1.0 / fConst21;
	fConst26 = (fConst25 + -1.0000000000000004) / fConst21 + 1.0;
	fConst27 = 1.0 / ((fConst25 + 1.0000000000000004) / fConst21 + 1.0);
	double fConst28 = std::tan(20517.741620594938 / fConst0);
	double fConst29 = mydsp_faustpower2_f(fConst28);
	fConst30 = 1.0 / fConst29;
	fConst31 = 2.0 * (1.0 - fConst30);
	fConst32 = 1.0 / fConst28;
	fConst33 = (fConst32 + -1.0000000000000004) / fConst28 + 1.0;
	fConst34 = 1.0 / ((fConst32 + 1.0000000000000004) / fConst28 + 1.0);
	fConst35 = 1.0 - fConst32;
	double fConst36 = fConst32 + 1.0;
	fConst37 = 1.0 / fConst36;
	fConst38 = 1.0 - fConst25;
	double fConst39 = fConst25 + 1.0;
	fConst40 = 1.0 / fConst39;
	fConst41 = 1.0 - fConst18;
	double fConst42 = fConst18 + 1.0;
	fConst43 = 1.0 / fConst42;
	fConst44 = 1.0 - fConst11;
	double fConst45 = fConst11 + 1.0;
	fConst46 = 1.0 / fConst45;
	fConst47 = fConst0 / fConst5;
	double fConst48 = std::tan(37699.11184307752 / fConst0);
	fConst49 = 2.0 * (1.0 - 1.0 / mydsp_faustpower2_f(fConst48));
	double fConst50 = 1.0 / fConst48;
	fConst51 = (fConst50 + -1.414213562373095) / fConst48 + 1.0;
	fConst52 = 1.0 / ((fConst50 + 1.414213562373095) / fConst48 + 1.0);
	double fConst53 = std::tan(376.99111843077515 / fConst0);
	double fConst54 = mydsp_faustpower2_f(fConst53);
	fConst55 = 1.0 / fConst54;
	fConst56 = 2.0 * (1.0 - fConst55);
	double fConst57 = 1.0 / fConst53;
	fConst58 = (fConst57 + -1.414213562373095) / fConst53 + 1.0;
	fConst59 = 1.0 / ((fConst57 + 1.414213562373095) / fConst53 + 1.0);
	fConst60 = 0.0 - 2.0 / fConst54;
	fConst61 = 0.001 * fConst0;
	fConst62 = 1e+01 / fConst0;
	fConst63 = 0.0 - fConst62;
	fConst64 = 0.000617187446540506 * fConst0;
	fConst65 = 0.0 - fConst64;
	fConst66 = 1.0 / fConst2;
	fConst67 = fConst44 / fConst45;
	fConst68 = 1.0 / (fConst7 * fConst45);
	fConst69 = 0.0 - fConst68;
	fConst70 = 0.0 - 2.0 / fConst8;
	fConst71 = 1.0 - fConst44 / fConst7;
	fConst72 = 1.0 / (fConst45 / fConst7 + 1.0);
	fConst73 = fConst41 / fConst42;
	fConst74 = 1.0 / (fConst14 * fConst42);
	fConst75 = 0.0 - fConst74;
	fConst76 = 0.0 - 2.0 / fConst15;
	fConst77 = 1.0 - fConst41 / fConst14;
	fConst78 = 1.0 / (fConst42 / fConst14 + 1.0);
	fConst79 = fConst38 / fConst39;
	fConst80 = 1.0 / (fConst21 * fConst39);
	fConst81 = 0.0 - fConst80;
	fConst82 = 0.0 - 2.0 / fConst22;
	fConst83 = 1.0 - fConst38 / fConst21;
	fConst84 = 1.0 / (fConst39 / fConst21 + 1.0);
	fConst85 = 0.0 - 1.0 / (fConst28 * fConst36);
	fConst86 = 0.0 - 2.0 / fConst29;
	IOTA0 = 0;
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void Dsp::mem_alloc()
{
	if (!fVec4) fVec4 = new double[262144];
	if (!fVec5) fVec5 = new double[262144];
	if (!fVec6) fVec6 = new double[262144];
	if (!fVec7) fVec7 = new double[262144];
	if (!fVec8) fVec8 = new double[262144];
	mem_allocated = true;
}

void Dsp::mem_free()
{
	mem_allocated = false;
	if (fVec4) { delete fVec4; fVec4 = 0; }
	if (fVec5) { delete fVec5; fVec5 = 0; }
	if (fVec6) { delete fVec6; fVec6 = 0; }
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
	double fSlow0 = 0.004073836948085289 * (std::exp(double(fVslider0)) + -1.0);
	double fSlow1 = double(fVslider1);
	double fSlow2 = fConst61 * double(fVslider2);
	double fSlow3 = 0.004073836948085289 * (std::exp(double(fVslider3)) + -1.0);
	double fSlow4 = 0.007000000000000006 * std::pow(1e+01, 0.05 * double(fVslider4));
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		double fTemp0 = double(input0[i0]);
		fVec0[0] = fTemp0;
		fRec10[0] = 0.0 - fConst37 * (fConst35 * fRec10[1] - (fTemp0 + fVec0[1]));
		fRec9[0] = fRec10[0] - fConst34 * (fConst33 * fRec9[2] + fConst31 * fRec9[1]);
		double fTemp1 = fRec9[2] + fRec9[0] + 2.0 * fRec9[1];
		fVec1[0] = fTemp1;
		fRec8[0] = 0.0 - fConst40 * (fConst38 * fRec8[1] - fConst34 * (fTemp1 + fVec1[1]));
		fRec7[0] = fRec8[0] - fConst27 * (fConst26 * fRec7[2] + fConst24 * fRec7[1]);
		double fTemp2 = fRec7[2] + fRec7[0] + 2.0 * fRec7[1];
		fVec2[0] = fTemp2;
		fRec6[0] = 0.0 - fConst43 * (fConst41 * fRec6[1] - fConst27 * (fTemp2 + fVec2[1]));
		fRec5[0] = fRec6[0] - fConst20 * (fConst19 * fRec5[2] + fConst17 * fRec5[1]);
		double fTemp3 = fRec5[2] + fRec5[0] + 2.0 * fRec5[1];
		fVec3[0] = fTemp3;
		fRec4[0] = 0.0 - fConst46 * (fConst44 * fRec4[1] - fConst20 * (fTemp3 + fVec3[1]));
		fRec3[0] = fRec4[0] - fConst13 * (fConst12 * fRec3[2] + fConst10 * fRec3[1]);
		fRec2[0] = fConst13 * (fRec3[2] + fRec3[0] + 2.0 * fRec3[1]) - fConst6 * fRec2[1];
		fRec11[0] = fSlow0 + 0.993 * fRec11[1];
		double fTemp4 = 0.0 - 0.000697428436220861 * fRec11[0];
		double fTemp5 = fConst47 * (fRec2[0] * fTemp4 + 0.000697428436220861 * fRec11[0] * fRec2[1]);
		fRec13[0] = fSlow1 * fRec1[1] - fConst59 * (fConst58 * fRec13[2] + fConst56 * fRec13[1]);
		fRec12[0] = fConst59 * (fConst55 * fRec13[0] + fConst60 * fRec13[1] + fConst55 * fRec13[2]) - fConst52 * (fConst51 * fRec12[2] + fConst49 * fRec12[1]);
		double fTemp6 = fConst52 * (fRec12[2] + fRec12[0] + 2.0 * fRec12[1]) + ((signbit(fTemp5)) ? input12ax7_negclip(fTemp5) : input12ax7clip(fTemp5));
		fVec4[IOTA0 & 262143] = fTemp6;
		double fTemp7 = ((fRec14[1] != 0.0) ? (((fRec15[1] > 0.0) & (fRec15[1] < 1.0)) ? fRec14[1] : 0.0) : (((fRec15[1] == 0.0) & (fSlow2 != fRec16[1])) ? fConst62 : (((fRec15[1] == 1.0) & (fSlow2 != fRec17[1])) ? fConst63 : 0.0)));
		fRec14[0] = fTemp7;
		fRec15[0] = std::max<double>(0.0, std::min<double>(1.0, fRec15[1] + fTemp7));
		fRec16[0] = (((fRec15[1] >= 1.0) & (fRec17[1] != fSlow2)) ? fSlow2 : fRec16[1]);
		fRec17[0] = (((fRec15[1] <= 0.0) & (fRec16[1] != fSlow2)) ? fSlow2 : fRec17[1]);
		int iTemp8 = int(std::min<double>(131072.0, std::max<double>(0.0, fRec16[0])));
		double fTemp9 = fVec4[(IOTA0 - iTemp8) & 262143];
		int iTemp10 = int(std::min<double>(131072.0, std::max<double>(0.0, fRec17[0])));
		fRec18[0] = fSlow3 + 0.993 * fRec18[1];
		fRec1[0] = fTemp6 + fRec18[0] * (fTemp9 + fRec15[0] * (fVec4[(IOTA0 - iTemp10) & 262143] - fTemp9));
		fRec0[0] = fRec1[0] - fConst3 * fRec0[1];
		double fTemp11 = fConst66 * (fConst65 * fRec0[0] + fConst64 * fRec0[1]);
		fRec23[0] = fConst20 * (fConst68 * fTemp3 + fConst69 * fVec3[1]) - fConst67 * fRec23[1];
		fRec22[0] = fRec23[0] - fConst13 * (fConst12 * fRec22[2] + fConst10 * fRec22[1]);
		fRec21[0] = fConst13 * (fConst9 * fRec22[0] + fConst70 * fRec22[1] + fConst9 * fRec22[2]) - fConst6 * fRec21[1];
		double fTemp12 = fConst47 * (fRec21[0] * fTemp4 + 0.000697428436220861 * fRec11[0] * fRec21[1]);
		fRec25[0] = fSlow1 * fRec20[1] - fConst59 * (fConst58 * fRec25[2] + fConst56 * fRec25[1]);
		fRec24[0] = fConst59 * (fConst55 * fRec25[0] + fConst60 * fRec25[1] + fConst55 * fRec25[2]) - fConst52 * (fConst51 * fRec24[2] + fConst49 * fRec24[1]);
		double fTemp13 = fConst52 * (fRec24[2] + fRec24[0] + 2.0 * fRec24[1]) + ((signbit(fTemp12)) ? input12ax7_negclip(fTemp12) : input12ax7clip(fTemp12));
		fVec5[IOTA0 & 262143] = fTemp13;
		double fTemp14 = fVec5[(IOTA0 - iTemp8) & 262143];
		fRec20[0] = fTemp13 + fRec18[0] * (fTemp14 + fRec15[0] * (fVec5[(IOTA0 - iTemp10) & 262143] - fTemp14));
		fRec19[0] = fRec20[0] - fConst3 * fRec19[1];
		double fTemp15 = fConst66 * (fConst65 * fRec19[0] + fConst64 * fRec19[1]);
		double fTemp16 = fConst10 * fRec29[1];
		fRec31[0] = fConst27 * (fConst74 * fTemp2 + fConst75 * fVec2[1]) - fConst73 * fRec31[1];
		fRec30[0] = fRec31[0] - fConst20 * (fConst19 * fRec30[2] + fConst17 * fRec30[1]);
		fRec29[0] = fConst20 * (fConst16 * fRec30[0] + fConst76 * fRec30[1] + fConst16 * fRec30[2]) - fConst72 * (fConst71 * fRec29[2] + fTemp16);
		fRec28[0] = fRec29[2] + fConst72 * (fTemp16 + fConst71 * fRec29[0]) - fConst6 * fRec28[1];
		double fTemp17 = fConst47 * (fRec28[0] * fTemp4 + 0.000697428436220861 * fRec11[0] * fRec28[1]);
		fRec33[0] = fSlow1 * fRec27[1] - fConst59 * (fConst58 * fRec33[2] + fConst56 * fRec33[1]);
		fRec32[0] = fConst59 * (fConst55 * fRec33[0] + fConst60 * fRec33[1] + fConst55 * fRec33[2]) - fConst52 * (fConst51 * fRec32[2] + fConst49 * fRec32[1]);
		double fTemp18 = fConst52 * (fRec32[2] + fRec32[0] + 2.0 * fRec32[1]) + ((signbit(fTemp17)) ? input12ax7_negclip(fTemp17) : input12ax7clip(fTemp17));
		fVec6[IOTA0 & 262143] = fTemp18;
		double fTemp19 = fVec6[(IOTA0 - iTemp8) & 262143];
		fRec27[0] = fTemp18 + fRec18[0] * (fTemp19 + fRec15[0] * (fVec6[(IOTA0 - iTemp10) & 262143] - fTemp19));
		fRec26[0] = fRec27[0] - fConst3 * fRec26[1];
		double fTemp20 = fConst66 * (fConst65 * fRec26[0] + fConst64 * fRec26[1]);
		double fTemp21 = fConst10 * fRec37[1];
		double fTemp22 = fConst17 * fRec38[1];
		fRec40[0] = fConst34 * (fConst80 * fTemp1 + fConst81 * fVec1[1]) - fConst79 * fRec40[1];
		fRec39[0] = fRec40[0] - fConst27 * (fConst26 * fRec39[2] + fConst24 * fRec39[1]);
		fRec38[0] = fConst27 * (fConst23 * fRec39[0] + fConst82 * fRec39[1] + fConst23 * fRec39[2]) - fConst78 * (fConst77 * fRec38[2] + fTemp22);
		fRec37[0] = fRec38[2] + fConst78 * (fTemp22 + fConst77 * fRec38[0]) - fConst72 * (fConst71 * fRec37[2] + fTemp21);
		fRec36[0] = fRec37[2] + fConst72 * (fTemp21 + fConst71 * fRec37[0]) - fConst6 * fRec36[1];
		double fTemp23 = fConst47 * (fRec36[0] * fTemp4 + 0.000697428436220861 * fRec11[0] * fRec36[1]);
		fRec42[0] = fSlow1 * fRec35[1] - fConst59 * (fConst58 * fRec42[2] + fConst56 * fRec42[1]);
		fRec41[0] = fConst59 * (fConst55 * fRec42[0] + fConst60 * fRec42[1] + fConst55 * fRec42[2]) - fConst52 * (fConst51 * fRec41[2] + fConst49 * fRec41[1]);
		double fTemp24 = fConst52 * (fRec41[2] + fRec41[0] + 2.0 * fRec41[1]) + ((signbit(fTemp23)) ? input12ax7_negclip(fTemp23) : input12ax7clip(fTemp23));
		fVec7[IOTA0 & 262143] = fTemp24;
		double fTemp25 = fVec7[(IOTA0 - iTemp8) & 262143];
		fRec35[0] = fTemp24 + fRec18[0] * (fTemp25 + fRec15[0] * (fVec7[(IOTA0 - iTemp10) & 262143] - fTemp25));
		fRec34[0] = fRec35[0] - fConst3 * fRec34[1];
		double fTemp26 = fConst66 * (fConst65 * fRec34[0] + fConst64 * fRec34[1]);
		double fTemp27 = fConst10 * fRec46[1];
		double fTemp28 = fConst17 * fRec47[1];
		double fTemp29 = fConst24 * fRec48[1];
		fRec50[0] = fConst85 * fVec0[1] - fConst37 * (fConst35 * fRec50[1] - fConst32 * fTemp0);
		fRec49[0] = fRec50[0] - fConst34 * (fConst33 * fRec49[2] + fConst31 * fRec49[1]);
		fRec48[0] = fConst34 * (fConst30 * fRec49[0] + fConst86 * fRec49[1] + fConst30 * fRec49[2]) - fConst84 * (fConst83 * fRec48[2] + fTemp29);
		fRec47[0] = fRec48[2] + fConst84 * (fTemp29 + fConst83 * fRec48[0]) - fConst78 * (fConst77 * fRec47[2] + fTemp28);
		fRec46[0] = fRec47[2] + fConst78 * (fTemp28 + fConst77 * fRec47[0]) - fConst72 * (fConst71 * fRec46[2] + fTemp27);
		fRec45[0] = fRec46[2] + fConst72 * (fTemp27 + fConst71 * fRec46[0]) - fConst6 * fRec45[1];
		double fTemp30 = fConst47 * (fRec45[0] * fTemp4 + 0.000697428436220861 * fRec11[0] * fRec45[1]);
		fRec52[0] = fSlow1 * fRec44[1] - fConst59 * (fConst58 * fRec52[2] + fConst56 * fRec52[1]);
		fRec51[0] = fConst59 * (fConst55 * fRec52[0] + fConst60 * fRec52[1] + fConst55 * fRec52[2]) - fConst52 * (fConst51 * fRec51[2] + fConst49 * fRec51[1]);
		double fTemp31 = fConst52 * (fRec51[2] + fRec51[0] + 2.0 * fRec51[1]) + ((signbit(fTemp30)) ? input12ax7_negclip(fTemp30) : input12ax7clip(fTemp30));
		fVec8[IOTA0 & 262143] = fTemp31;
		double fTemp32 = fVec8[(IOTA0 - iTemp8) & 262143];
		fRec44[0] = fTemp31 + fRec18[0] * (fTemp32 + fRec15[0] * (fVec8[(IOTA0 - iTemp10) & 262143] - fTemp32));
		fRec43[0] = fRec44[0] - fConst3 * fRec43[1];
		double fTemp33 = fConst66 * (fConst65 * fRec43[0] + fConst64 * fRec43[1]);
		fRec53[0] = fSlow4 + 0.993 * fRec53[1];
		output0[i0] = FAUSTFLOAT(fRec53[0] * (((signbit(fTemp33)) ? output12ax7_negclip(fTemp33) : output12ax7clip(fTemp33)) + ((signbit(fTemp26)) ? output12ax7_negclip(fTemp26) : output12ax7clip(fTemp26)) + ((signbit(fTemp20)) ? output12ax7_negclip(fTemp20) : output12ax7clip(fTemp20)) + ((signbit(fTemp15)) ? output12ax7_negclip(fTemp15) : output12ax7clip(fTemp15)) + ((signbit(fTemp11)) ? output12ax7_negclip(fTemp11) : output12ax7clip(fTemp11))));
		fVec0[1] = fVec0[0];
		fRec10[1] = fRec10[0];
		fRec9[2] = fRec9[1];
		fRec9[1] = fRec9[0];
		fVec1[1] = fVec1[0];
		fRec8[1] = fRec8[0];
		fRec7[2] = fRec7[1];
		fRec7[1] = fRec7[0];
		fVec2[1] = fVec2[0];
		fRec6[1] = fRec6[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		fVec3[1] = fVec3[0];
		fRec4[1] = fRec4[0];
		fRec3[2] = fRec3[1];
		fRec3[1] = fRec3[0];
		fRec2[1] = fRec2[0];
		fRec11[1] = fRec11[0];
		fRec13[2] = fRec13[1];
		fRec13[1] = fRec13[0];
		fRec12[2] = fRec12[1];
		fRec12[1] = fRec12[0];
		IOTA0 = IOTA0 + 1;
		fRec14[1] = fRec14[0];
		fRec15[1] = fRec15[0];
		fRec16[1] = fRec16[0];
		fRec17[1] = fRec17[0];
		fRec18[1] = fRec18[0];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
		fRec23[1] = fRec23[0];
		fRec22[2] = fRec22[1];
		fRec22[1] = fRec22[0];
		fRec21[1] = fRec21[0];
		fRec25[2] = fRec25[1];
		fRec25[1] = fRec25[0];
		fRec24[2] = fRec24[1];
		fRec24[1] = fRec24[0];
		fRec20[1] = fRec20[0];
		fRec19[1] = fRec19[0];
		fRec31[1] = fRec31[0];
		fRec30[2] = fRec30[1];
		fRec30[1] = fRec30[0];
		fRec29[2] = fRec29[1];
		fRec29[1] = fRec29[0];
		fRec28[1] = fRec28[0];
		fRec33[2] = fRec33[1];
		fRec33[1] = fRec33[0];
		fRec32[2] = fRec32[1];
		fRec32[1] = fRec32[0];
		fRec27[1] = fRec27[0];
		fRec26[1] = fRec26[0];
		fRec40[1] = fRec40[0];
		fRec39[2] = fRec39[1];
		fRec39[1] = fRec39[0];
		fRec38[2] = fRec38[1];
		fRec38[1] = fRec38[0];
		fRec37[2] = fRec37[1];
		fRec37[1] = fRec37[0];
		fRec36[1] = fRec36[0];
		fRec42[2] = fRec42[1];
		fRec42[1] = fRec42[0];
		fRec41[2] = fRec41[1];
		fRec41[1] = fRec41[0];
		fRec35[1] = fRec35[0];
		fRec34[1] = fRec34[0];
		fRec50[1] = fRec50[0];
		fRec49[2] = fRec49[1];
		fRec49[1] = fRec49[0];
		fRec48[2] = fRec48[1];
		fRec48[1] = fRec48[0];
		fRec47[2] = fRec47[1];
		fRec47[1] = fRec47[0];
		fRec46[2] = fRec46[1];
		fRec46[1] = fRec46[0];
		fRec45[1] = fRec45[0];
		fRec52[2] = fRec52[1];
		fRec52[1] = fRec52[0];
		fRec51[2] = fRec51[1];
		fRec51[1] = fRec51[0];
		fRec44[1] = fRec44[0];
		fRec43[1] = fRec43[0];
		fRec53[1] = fRec53[0];
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
		fVslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case DELAY: 
		fVslider2_ = (float*)data; // , 0.1, 0.1, 2.5e+03, 0.1 
		break;
	case FEEDBACK: 
		fVslider1_ = (float*)data; // , 0.0, 0.0, 0.7, 0.01 
		break;
	case LEVEL: 
		fVslider3_ = (float*)data; // , 0.0, 0.0, 1.0, 0.1 
		break;
	case OUTPUT: 
		fVslider4_ = (float*)data; // , 0.0, -2e+01, 2e+01, 0.1 
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
