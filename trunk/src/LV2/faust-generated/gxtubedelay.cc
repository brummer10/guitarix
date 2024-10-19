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
	double fVec0[2];
	double fConst35;
	double fConst36;
	double fRec10[2];
	double fRec9[3];
	double fVec1[2];
	double fConst37;
	double fConst38;
	double fConst39;
	double fRec8[2];
	double fRec7[3];
	double fVec2[2];
	double fConst40;
	double fConst41;
	double fConst42;
	double fRec6[2];
	double fRec5[3];
	double fVec3[2];
	double fConst43;
	double fConst44;
	double fConst45;
	double fRec4[2];
	double fRec3[3];
	double fRec2[2];
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec11[2];
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
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec13[3];
	double fConst59;
	double fRec12[3];
	int IOTA0;
	double *fVec4;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fConst60;
	double fConst61;
	double fRec14[2];
	double fRec15[2];
	double fRec16[2];
	double fRec17[2];
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fRec18[2];
	double fRec1[2];
	double fRec0[2];
	double fConst62;
	double fConst63;
	double fRec23[2];
	double fRec22[3];
	double fConst64;
	double fRec21[2];
	double fRec25[3];
	double fRec24[3];
	double *fVec5;
	double fRec20[2];
	double fRec19[2];
	double fConst65;
	double fConst66;
	double fConst67;
	double fRec31[2];
	double fRec30[3];
	double fConst68;
	double fRec29[3];
	double fRec28[2];
	double fRec33[3];
	double fRec32[3];
	double *fVec6;
	double fRec27[2];
	double fRec26[2];
	double fConst69;
	double fConst70;
	double fConst71;
	double fRec40[2];
	double fRec39[3];
	double fConst72;
	double fRec38[3];
	double fRec37[3];
	double fRec36[2];
	double fRec42[3];
	double fRec41[3];
	double *fVec7;
	double fRec35[2];
	double fRec34[2];
	double fConst73;
	double fConst74;
	double fRec50[2];
	double fRec49[3];
	double fConst75;
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
	fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = 2.08240830168832e-05 * fConst0;
	fConst2 = fConst1 + 0.000444015189606219;
	fConst3 = (0.000444015189606219 - fConst1) / fConst2;
	fConst4 = 2.08240500698813e-05 * fConst0;
	fConst5 = fConst4 + 0.000445596645695992;
	fConst6 = (0.000445596645695992 - fConst4) / fConst5;
	fConst7 = std::tan(270.1769682087222 / fConst0);
	fConst8 = mydsp_faustpower2_f(fConst7);
	fConst9 = 2.0 * (1.0 - 1.0 / fConst8);
	fConst10 = 1.0 / fConst7;
	fConst11 = (fConst10 + -1.0000000000000004) / fConst7 + 1.0;
	fConst12 = (fConst10 + 1.0000000000000004) / fConst7 + 1.0;
	fConst13 = 1.0 / fConst12;
	fConst14 = std::tan(659.7344572538566 / fConst0);
	fConst15 = mydsp_faustpower2_f(fConst14);
	fConst16 = 2.0 * (1.0 - 1.0 / fConst15);
	fConst17 = 1.0 / fConst14;
	fConst18 = (fConst17 + -1.0000000000000004) / fConst14 + 1.0;
	fConst19 = (fConst17 + 1.0000000000000004) / fConst14 + 1.0;
	fConst20 = 1.0 / fConst19;
	fConst21 = std::tan(3769.9111843077517 / fConst0);
	fConst22 = mydsp_faustpower2_f(fConst21);
	fConst23 = 2.0 * (1.0 - 1.0 / fConst22);
	fConst24 = 1.0 / fConst21;
	fConst25 = (fConst24 + -1.0000000000000004) / fConst21 + 1.0;
	fConst26 = (fConst24 + 1.0000000000000004) / fConst21 + 1.0;
	fConst27 = 1.0 / fConst26;
	fConst28 = std::tan(20517.741620594938 / fConst0);
	fConst29 = mydsp_faustpower2_f(fConst28);
	fConst30 = 2.0 * (1.0 - 1.0 / fConst29);
	fConst31 = 1.0 / fConst28;
	fConst32 = (fConst31 + -1.0000000000000004) / fConst28 + 1.0;
	fConst33 = (fConst31 + 1.0000000000000004) / fConst28 + 1.0;
	fConst34 = 1.0 / fConst33;
	fConst35 = 1.0 - fConst31;
	fConst36 = 1.0 / (fConst31 + 1.0);
	fConst37 = 1.0 - fConst24;
	fConst38 = fConst24 + 1.0;
	fConst39 = 1.0 / fConst38;
	fConst40 = 1.0 - fConst17;
	fConst41 = fConst17 + 1.0;
	fConst42 = 1.0 / fConst41;
	fConst43 = 1.0 - fConst10;
	fConst44 = fConst10 + 1.0;
	fConst45 = 1.0 / fConst44;
	fConst46 = 0.000697428436220861 * (fConst0 / fConst5);
	fConst47 = std::tan(37699.11184307752 / fConst0);
	fConst48 = 2.0 * (1.0 - 1.0 / mydsp_faustpower2_f(fConst47));
	fConst49 = 1.0 / fConst47;
	fConst50 = (fConst49 + -1.414213562373095) / fConst47 + 1.0;
	fConst51 = 1.0 / ((fConst49 + 1.414213562373095) / fConst47 + 1.0);
	fConst52 = std::tan(376.99111843077515 / fConst0);
	fConst53 = mydsp_faustpower2_f(fConst52);
	fConst54 = 2.0 * (1.0 - 1.0 / fConst53);
	fConst55 = 1.0 / fConst52;
	fConst56 = (fConst55 + -1.414213562373095) / fConst52 + 1.0;
	fConst57 = (fConst55 + 1.414213562373095) / fConst52 + 1.0;
	fConst58 = 1.0 / fConst57;
	fConst59 = 1.0 / (fConst53 * fConst57);
	fConst60 = 0.001 * fConst0;
	fConst61 = 1e+01 / fConst0;
	fConst62 = 0.000617187446540506 * (fConst0 / fConst2);
	fConst63 = 1.0 / (fConst7 * fConst19);
	fConst64 = 1.0 / (fConst8 * fConst12);
	fConst65 = 1.0 - fConst43 / fConst7;
	fConst66 = 1.0 / (fConst44 / fConst7 + 1.0);
	fConst67 = 1.0 / (fConst14 * fConst26);
	fConst68 = 1.0 / (fConst15 * fConst19);
	fConst69 = 1.0 - fConst40 / fConst14;
	fConst70 = 1.0 / (fConst41 / fConst14 + 1.0);
	fConst71 = 1.0 / (fConst21 * fConst33);
	fConst72 = 1.0 / (fConst22 * fConst26);
	fConst73 = 1.0 - fConst37 / fConst21;
	fConst74 = 1.0 / (fConst38 / fConst21 + 1.0);
	fConst75 = 1.0 / (fConst29 * fConst33);
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
	double fSlow2 = fConst60 * double(fVslider2);
	double fSlow3 = 0.004073836948085289 * (std::exp(double(fVslider3)) + -1.0);
	double fSlow4 = 0.007000000000000006 * std::pow(1e+01, 0.05 * double(fVslider4));
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		double fTemp0 = double(input0[i0]);
		fVec0[0] = fTemp0;
		fRec10[0] = -(fConst36 * (fConst35 * fRec10[1] - (fTemp0 + fVec0[1])));
		fRec9[0] = fRec10[0] - fConst34 * (fConst32 * fRec9[2] + fConst30 * fRec9[1]);
		double fTemp1 = fRec9[2] + fRec9[0] + 2.0 * fRec9[1];
		fVec1[0] = fTemp1;
		fRec8[0] = -(fConst39 * (fConst37 * fRec8[1] - fConst34 * (fTemp1 + fVec1[1])));
		fRec7[0] = fRec8[0] - fConst27 * (fConst25 * fRec7[2] + fConst23 * fRec7[1]);
		double fTemp2 = fRec7[2] + fRec7[0] + 2.0 * fRec7[1];
		fVec2[0] = fTemp2;
		fRec6[0] = -(fConst42 * (fConst40 * fRec6[1] - fConst27 * (fTemp2 + fVec2[1])));
		fRec5[0] = fRec6[0] - fConst20 * (fConst18 * fRec5[2] + fConst16 * fRec5[1]);
		double fTemp3 = fRec5[2] + fRec5[0] + 2.0 * fRec5[1];
		fVec3[0] = fTemp3;
		fRec4[0] = -(fConst45 * (fConst43 * fRec4[1] - fConst20 * (fTemp3 + fVec3[1])));
		fRec3[0] = fRec4[0] - fConst13 * (fConst11 * fRec3[2] + fConst9 * fRec3[1]);
		fRec2[0] = fConst13 * (fRec3[2] + fRec3[0] + 2.0 * fRec3[1]) - fConst6 * fRec2[1];
		fRec11[0] = fSlow0 + 0.993 * fRec11[1];
		double fTemp4 = fConst46 * fRec11[0] * (fRec2[0] - fRec2[1]);
		fRec13[0] = fSlow1 * fRec1[1] - fConst58 * (fConst56 * fRec13[2] + fConst54 * fRec13[1]);
		fRec12[0] = fConst59 * (fRec13[2] + (fRec13[0] - 2.0 * fRec13[1])) - fConst51 * (fConst50 * fRec12[2] + fConst48 * fRec12[1]);
		double fTemp5 = fConst51 * (fRec12[2] + fRec12[0] + 2.0 * fRec12[1]) + ((signbit(-fTemp4)) ? input12ax7_negclip(-fTemp4) : input12ax7clip(-fTemp4));
		fVec4[IOTA0 & 262143] = fTemp5;
		double fTemp6 = ((fRec14[1] != 0.0) ? (((fRec15[1] > 0.0) & (fRec15[1] < 1.0)) ? fRec14[1] : 0.0) : (((fRec15[1] == 0.0) & (fSlow2 != fRec16[1])) ? fConst61 : (((fRec15[1] == 1.0) & (fSlow2 != fRec17[1])) ? -fConst61 : 0.0)));
		fRec14[0] = fTemp6;
		fRec15[0] = std::max<double>(0.0, std::min<double>(1.0, fRec15[1] + fTemp6));
		fRec16[0] = (((fRec15[1] >= 1.0) & (fRec17[1] != fSlow2)) ? fSlow2 : fRec16[1]);
		fRec17[0] = (((fRec15[1] <= 0.0) & (fRec16[1] != fSlow2)) ? fSlow2 : fRec17[1]);
		int iTemp7 = int(std::min<double>(131072.0, std::max<double>(0.0, fRec16[0])));
		double fTemp8 = fVec4[(IOTA0 - iTemp7) & 262143];
		int iTemp9 = int(std::min<double>(131072.0, std::max<double>(0.0, fRec17[0])));
		fRec18[0] = fSlow3 + 0.993 * fRec18[1];
		fRec1[0] = fTemp5 + fRec18[0] * (fTemp8 + fRec15[0] * (fVec4[(IOTA0 - iTemp9) & 262143] - fTemp8));
		fRec0[0] = fRec1[0] - fConst3 * fRec0[1];
		double fTemp10 = fConst62 * (fRec0[0] - fRec0[1]);
		fRec23[0] = -(fConst45 * (fConst43 * fRec23[1] - fConst63 * (fTemp3 - fVec3[1])));
		fRec22[0] = fRec23[0] - fConst13 * (fConst11 * fRec22[2] + fConst9 * fRec22[1]);
		fRec21[0] = fConst64 * (fRec22[2] + (fRec22[0] - 2.0 * fRec22[1])) - fConst6 * fRec21[1];
		double fTemp11 = fConst46 * fRec11[0] * (fRec21[0] - fRec21[1]);
		fRec25[0] = fSlow1 * fRec20[1] - fConst58 * (fConst56 * fRec25[2] + fConst54 * fRec25[1]);
		fRec24[0] = fConst59 * (fRec25[2] + (fRec25[0] - 2.0 * fRec25[1])) - fConst51 * (fConst50 * fRec24[2] + fConst48 * fRec24[1]);
		double fTemp12 = fConst51 * (fRec24[2] + fRec24[0] + 2.0 * fRec24[1]) + ((signbit(-fTemp11)) ? input12ax7_negclip(-fTemp11) : input12ax7clip(-fTemp11));
		fVec5[IOTA0 & 262143] = fTemp12;
		double fTemp13 = fVec5[(IOTA0 - iTemp7) & 262143];
		fRec20[0] = fTemp12 + fRec18[0] * (fTemp13 + fRec15[0] * (fVec5[(IOTA0 - iTemp9) & 262143] - fTemp13));
		fRec19[0] = fRec20[0] - fConst3 * fRec19[1];
		double fTemp14 = fConst62 * (fRec19[0] - fRec19[1]);
		double fTemp15 = fConst9 * fRec29[1];
		fRec31[0] = -(fConst42 * (fConst40 * fRec31[1] - fConst67 * (fTemp2 - fVec2[1])));
		fRec30[0] = fRec31[0] - fConst20 * (fConst18 * fRec30[2] + fConst16 * fRec30[1]);
		fRec29[0] = fConst68 * (fRec30[2] + (fRec30[0] - 2.0 * fRec30[1])) - fConst66 * (fConst65 * fRec29[2] + fTemp15);
		fRec28[0] = fRec29[2] + fConst66 * (fTemp15 + fConst65 * fRec29[0]) - fConst6 * fRec28[1];
		double fTemp16 = fConst46 * fRec11[0] * (fRec28[0] - fRec28[1]);
		fRec33[0] = fSlow1 * fRec27[1] - fConst58 * (fConst56 * fRec33[2] + fConst54 * fRec33[1]);
		fRec32[0] = fConst59 * (fRec33[2] + (fRec33[0] - 2.0 * fRec33[1])) - fConst51 * (fConst50 * fRec32[2] + fConst48 * fRec32[1]);
		double fTemp17 = fConst51 * (fRec32[2] + fRec32[0] + 2.0 * fRec32[1]) + ((signbit(-fTemp16)) ? input12ax7_negclip(-fTemp16) : input12ax7clip(-fTemp16));
		fVec6[IOTA0 & 262143] = fTemp17;
		double fTemp18 = fVec6[(IOTA0 - iTemp7) & 262143];
		fRec27[0] = fTemp17 + fRec18[0] * (fTemp18 + fRec15[0] * (fVec6[(IOTA0 - iTemp9) & 262143] - fTemp18));
		fRec26[0] = fRec27[0] - fConst3 * fRec26[1];
		double fTemp19 = fConst62 * (fRec26[0] - fRec26[1]);
		double fTemp20 = fConst9 * fRec37[1];
		double fTemp21 = fConst16 * fRec38[1];
		fRec40[0] = -(fConst39 * (fConst37 * fRec40[1] - fConst71 * (fTemp1 - fVec1[1])));
		fRec39[0] = fRec40[0] - fConst27 * (fConst25 * fRec39[2] + fConst23 * fRec39[1]);
		fRec38[0] = fConst72 * (fRec39[2] + (fRec39[0] - 2.0 * fRec39[1])) - fConst70 * (fConst69 * fRec38[2] + fTemp21);
		fRec37[0] = fRec38[2] + fConst70 * (fTemp21 + fConst69 * fRec38[0]) - fConst66 * (fConst65 * fRec37[2] + fTemp20);
		fRec36[0] = fRec37[2] + fConst66 * (fTemp20 + fConst65 * fRec37[0]) - fConst6 * fRec36[1];
		double fTemp22 = fConst46 * fRec11[0] * (fRec36[0] - fRec36[1]);
		fRec42[0] = fSlow1 * fRec35[1] - fConst58 * (fConst56 * fRec42[2] + fConst54 * fRec42[1]);
		fRec41[0] = fConst59 * (fRec42[2] + (fRec42[0] - 2.0 * fRec42[1])) - fConst51 * (fConst50 * fRec41[2] + fConst48 * fRec41[1]);
		double fTemp23 = fConst51 * (fRec41[2] + fRec41[0] + 2.0 * fRec41[1]) + ((signbit(-fTemp22)) ? input12ax7_negclip(-fTemp22) : input12ax7clip(-fTemp22));
		fVec7[IOTA0 & 262143] = fTemp23;
		double fTemp24 = fVec7[(IOTA0 - iTemp7) & 262143];
		fRec35[0] = fTemp23 + fRec18[0] * (fTemp24 + fRec15[0] * (fVec7[(IOTA0 - iTemp9) & 262143] - fTemp24));
		fRec34[0] = fRec35[0] - fConst3 * fRec34[1];
		double fTemp25 = fConst62 * (fRec34[0] - fRec34[1]);
		double fTemp26 = fConst9 * fRec46[1];
		double fTemp27 = fConst16 * fRec47[1];
		double fTemp28 = fConst23 * fRec48[1];
		fRec50[0] = -(fConst36 * (fConst35 * fRec50[1] - fConst31 * (fTemp0 - fVec0[1])));
		fRec49[0] = fRec50[0] - fConst34 * (fConst32 * fRec49[2] + fConst30 * fRec49[1]);
		fRec48[0] = fConst75 * (fRec49[2] + (fRec49[0] - 2.0 * fRec49[1])) - fConst74 * (fConst73 * fRec48[2] + fTemp28);
		fRec47[0] = fRec48[2] + fConst74 * (fTemp28 + fConst73 * fRec48[0]) - fConst70 * (fConst69 * fRec47[2] + fTemp27);
		fRec46[0] = fRec47[2] + fConst70 * (fTemp27 + fConst69 * fRec47[0]) - fConst66 * (fConst65 * fRec46[2] + fTemp26);
		fRec45[0] = fRec46[2] + fConst66 * (fTemp26 + fConst65 * fRec46[0]) - fConst6 * fRec45[1];
		double fTemp29 = fConst46 * fRec11[0] * (fRec45[0] - fRec45[1]);
		fRec52[0] = fSlow1 * fRec44[1] - fConst58 * (fConst56 * fRec52[2] + fConst54 * fRec52[1]);
		fRec51[0] = fConst59 * (fRec52[2] + (fRec52[0] - 2.0 * fRec52[1])) - fConst51 * (fConst50 * fRec51[2] + fConst48 * fRec51[1]);
		double fTemp30 = fConst51 * (fRec51[2] + fRec51[0] + 2.0 * fRec51[1]) + ((signbit(-fTemp29)) ? input12ax7_negclip(-fTemp29) : input12ax7clip(-fTemp29));
		fVec8[IOTA0 & 262143] = fTemp30;
		double fTemp31 = fVec8[(IOTA0 - iTemp7) & 262143];
		fRec44[0] = fTemp30 + fRec18[0] * (fTemp31 + fRec15[0] * (fVec8[(IOTA0 - iTemp9) & 262143] - fTemp31));
		fRec43[0] = fRec44[0] - fConst3 * fRec43[1];
		double fTemp32 = fConst62 * (fRec43[0] - fRec43[1]);
		fRec53[0] = fSlow4 + 0.993 * fRec53[1];
		output0[i0] = FAUSTFLOAT(fRec53[0] * (((signbit(-fTemp32)) ? output12ax7_negclip(-fTemp32) : output12ax7clip(-fTemp32)) + ((signbit(-fTemp25)) ? output12ax7_negclip(-fTemp25) : output12ax7clip(-fTemp25)) + ((signbit(-fTemp19)) ? output12ax7_negclip(-fTemp19) : output12ax7clip(-fTemp19)) + ((signbit(-fTemp14)) ? output12ax7_negclip(-fTemp14) : output12ax7clip(-fTemp14)) + ((signbit(-fTemp10)) ? output12ax7_negclip(-fTemp10) : output12ax7clip(-fTemp10))));
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
