// generated from file '../src/LV2/faust/gxtubevibrato.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "input12ax7_neg_table.h"
#include "input12ax7_table.h"
#include "math.h"
#include "output12ax7_neg_table.h"
#include "output12ax7_table.h"

namespace gxtubevibrato {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	int iVec0[2];
	double fRec0[2];
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	double fConst4;
	double fConst5;
	double fConst6;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT	*fCheckbox0_;
	double fConst7;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	int iRec7[2];
	int iRec6[2];
	double fConst8;
	double fRec10[2];
	double fRec9[2];
	double fRec8[2];
	double fConst9;
	double fConst10;
	double fRec2[2];
	double fRec3[2];
	double fRec4[2];
	double fRec5[2];
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
	double fVec1[2];
	double fConst21;
	double fConst22;
	double fRec16[2];
	double fConst23;
	double fConst24;
	double fRec15[3];
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
	double fRec14[3];
	double fConst35;
	double fConst36;
	double fConst37;
	double fConst38;
	double fConst39;
	double fConst40;
	double fConst41;
	double fConst42;
	double fConst43;
	double fRec13[3];
	double fConst44;
	double fConst45;
	double fConst46;
	double fConst47;
	double fConst48;
	double fConst49;
	double fConst50;
	double fConst51;
	double fConst52;
	double fRec12[3];
	double fConst53;
	double fRec11[2];
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fRec17[2];
	int IOTA;
	double *fVec2;
	double fConst54;
	double fRec1[2];
	double fConst55;
	double fConst56;
	double fRec25[2];
	double fRec24[3];
	double fVec3[2];
	double fConst57;
	double fConst58;
	double fRec23[2];
	double fConst59;
	double fRec22[3];
	double fConst60;
	double fRec21[3];
	double fRec20[3];
	double fRec19[2];
	double *fVec4;
	double fRec18[2];
	double fConst61;
	double fConst62;
	double fConst63;
	double fRec32[2];
	double fRec31[3];
	double fVec5[2];
	double fConst64;
	double fConst65;
	double fRec30[2];
	double fConst66;
	double fRec29[3];
	double fConst67;
	double fRec28[3];
	double fRec27[2];
	double *fVec6;
	double fRec26[2];
	double fConst68;
	double fConst69;
	double fConst70;
	double fRec38[2];
	double fRec37[3];
	double fVec7[2];
	double fConst71;
	double fConst72;
	double fRec36[2];
	double fConst73;
	double fRec35[3];
	double fConst74;
	double fRec34[2];
	double *fVec8;
	double fRec33[2];
	double fConst75;
	double fRec42[2];
	double fRec41[3];
	double fRec40[2];
	double *fVec9;
	double fRec39[2];

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
	  fVec2(0),
	  fVec4(0),
	  fVec6(0),
	  fVec8(0),
	  fVec9(0),
	  mem_allocated(false) {
	version = PLUGINLV2_VERSION;
	id = "gxtubevibrato";
	name = N_("gxtubevibrato");
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) iVec0[l0] = 0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec0[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) iRec7[l2] = 0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) iRec6[l3] = 0;
	for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) fRec10[l4] = 0.0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fRec9[l5] = 0.0;
	for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) fRec8[l6] = 0.0;
	for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) fRec2[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fRec3[l8] = 0.0;
	for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) fRec4[l9] = 0.0;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) fRec5[l10] = 0.0;
	for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) fVec1[l11] = 0.0;
	for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) fRec16[l12] = 0.0;
	for (int l13 = 0; (l13 < 3); l13 = (l13 + 1)) fRec15[l13] = 0.0;
	for (int l14 = 0; (l14 < 3); l14 = (l14 + 1)) fRec14[l14] = 0.0;
	for (int l15 = 0; (l15 < 3); l15 = (l15 + 1)) fRec13[l15] = 0.0;
	for (int l16 = 0; (l16 < 3); l16 = (l16 + 1)) fRec12[l16] = 0.0;
	for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) fRec11[l17] = 0.0;
	for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) fRec17[l18] = 0.0;
	for (int l19 = 0; (l19 < 131072); l19 = (l19 + 1)) fVec2[l19] = 0.0;
	for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) fRec1[l20] = 0.0;
	for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) fRec25[l21] = 0.0;
	for (int l22 = 0; (l22 < 3); l22 = (l22 + 1)) fRec24[l22] = 0.0;
	for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) fVec3[l23] = 0.0;
	for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) fRec23[l24] = 0.0;
	for (int l25 = 0; (l25 < 3); l25 = (l25 + 1)) fRec22[l25] = 0.0;
	for (int l26 = 0; (l26 < 3); l26 = (l26 + 1)) fRec21[l26] = 0.0;
	for (int l27 = 0; (l27 < 3); l27 = (l27 + 1)) fRec20[l27] = 0.0;
	for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) fRec19[l28] = 0.0;
	for (int l29 = 0; (l29 < 131072); l29 = (l29 + 1)) fVec4[l29] = 0.0;
	for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) fRec18[l30] = 0.0;
	for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) fRec32[l31] = 0.0;
	for (int l32 = 0; (l32 < 3); l32 = (l32 + 1)) fRec31[l32] = 0.0;
	for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) fVec5[l33] = 0.0;
	for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) fRec30[l34] = 0.0;
	for (int l35 = 0; (l35 < 3); l35 = (l35 + 1)) fRec29[l35] = 0.0;
	for (int l36 = 0; (l36 < 3); l36 = (l36 + 1)) fRec28[l36] = 0.0;
	for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) fRec27[l37] = 0.0;
	for (int l38 = 0; (l38 < 131072); l38 = (l38 + 1)) fVec6[l38] = 0.0;
	for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) fRec26[l39] = 0.0;
	for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) fRec38[l40] = 0.0;
	for (int l41 = 0; (l41 < 3); l41 = (l41 + 1)) fRec37[l41] = 0.0;
	for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) fVec7[l42] = 0.0;
	for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) fRec36[l43] = 0.0;
	for (int l44 = 0; (l44 < 3); l44 = (l44 + 1)) fRec35[l44] = 0.0;
	for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) fRec34[l45] = 0.0;
	for (int l46 = 0; (l46 < 131072); l46 = (l46 + 1)) fVec8[l46] = 0.0;
	for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) fRec33[l47] = 0.0;
	for (int l48 = 0; (l48 < 2); l48 = (l48 + 1)) fRec42[l48] = 0.0;
	for (int l49 = 0; (l49 < 3); l49 = (l49 + 1)) fRec41[l49] = 0.0;
	for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) fRec40[l50] = 0.0;
	for (int l51 = 0; (l51 < 131072); l51 = (l51 + 1)) fVec9[l51] = 0.0;
	for (int l52 = 0; (l52 < 2); l52 = (l52 + 1)) fRec39[l52] = 0.0;
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
	fConst6 = (0.0050000000000000001 * fConst0);
	fConst7 = (0.5 * fConst0);
	fConst8 = (6.2831853071795862 / fConst0);
	fConst9 = (10.0 / fConst0);
	fConst10 = (0.0 - fConst9);
	fConst11 = (2.0824050069881302e-05 * fConst0);
	fConst12 = (fConst11 + 0.00044559664569599199);
	fConst13 = (fConst0 / fConst12);
	fConst14 = std::tan((20517.741620594938 / fConst0));
	fConst15 = (1.0 / fConst14);
	fConst16 = (1.0 / (((fConst15 + 1.0000000000000004) / fConst14) + 1.0));
	fConst17 = mydsp_faustpower2_f(fConst14);
	fConst18 = (1.0 / fConst17);
	fConst19 = (fConst15 + 1.0);
	fConst20 = (0.0 - (1.0 / (fConst14 * fConst19)));
	fConst21 = (1.0 / fConst19);
	fConst22 = (1.0 - fConst15);
	fConst23 = (((fConst15 + -1.0000000000000004) / fConst14) + 1.0);
	fConst24 = (2.0 * (1.0 - fConst18));
	fConst25 = (0.0 - (2.0 / fConst17));
	fConst26 = std::tan((3769.9111843077517 / fConst0));
	fConst27 = (1.0 / fConst26);
	fConst28 = (fConst27 + 1.0);
	fConst29 = (1.0 / ((fConst28 / fConst26) + 1.0));
	fConst30 = (1.0 - fConst27);
	fConst31 = (1.0 - (fConst30 / fConst26));
	fConst32 = mydsp_faustpower2_f(fConst26);
	fConst33 = (1.0 / fConst32);
	fConst34 = (2.0 * (1.0 - fConst33));
	fConst35 = std::tan((659.73445725385659 / fConst0));
	fConst36 = (1.0 / fConst35);
	fConst37 = (fConst36 + 1.0);
	fConst38 = (1.0 / ((fConst37 / fConst35) + 1.0));
	fConst39 = (1.0 - fConst36);
	fConst40 = (1.0 - (fConst39 / fConst35));
	fConst41 = mydsp_faustpower2_f(fConst35);
	fConst42 = (1.0 / fConst41);
	fConst43 = (2.0 * (1.0 - fConst42));
	fConst44 = std::tan((270.1769682087222 / fConst0));
	fConst45 = (1.0 / fConst44);
	fConst46 = (fConst45 + 1.0);
	fConst47 = (1.0 / ((fConst46 / fConst44) + 1.0));
	fConst48 = (1.0 - fConst45);
	fConst49 = (1.0 - (fConst48 / fConst44));
	fConst50 = mydsp_faustpower2_f(fConst44);
	fConst51 = (1.0 / fConst50);
	fConst52 = (2.0 * (1.0 - fConst51));
	fConst53 = ((0.00044559664569599199 - fConst11) / fConst12);
	fConst54 = ((0.00044401518960621899 - fConst1) / fConst2);
	fConst55 = (1.0 / (((fConst27 + 1.0000000000000004) / fConst26) + 1.0));
	fConst56 = (1.0 / (fConst26 * fConst28));
	fConst57 = (0.0 - fConst56);
	fConst58 = (fConst30 / fConst28);
	fConst59 = (((fConst27 + -1.0000000000000004) / fConst26) + 1.0);
	fConst60 = (0.0 - (2.0 / fConst32));
	fConst61 = (1.0 / (((fConst36 + 1.0000000000000004) / fConst35) + 1.0));
	fConst62 = (1.0 / (fConst35 * fConst37));
	fConst63 = (1.0 / fConst28);
	fConst64 = (0.0 - fConst62);
	fConst65 = (fConst39 / fConst37);
	fConst66 = (((fConst36 + -1.0000000000000004) / fConst35) + 1.0);
	fConst67 = (0.0 - (2.0 / fConst41));
	fConst68 = (1.0 / (((fConst45 + 1.0000000000000004) / fConst44) + 1.0));
	fConst69 = (1.0 / (fConst44 * fConst46));
	fConst70 = (1.0 / fConst37);
	fConst71 = (0.0 - fConst69);
	fConst72 = (fConst48 / fConst46);
	fConst73 = (((fConst45 + -1.0000000000000004) / fConst44) + 1.0);
	fConst74 = (0.0 - (2.0 / fConst50));
	fConst75 = (1.0 / fConst46);
	IOTA = 0;
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void Dsp::mem_alloc()
{
	if (!fVec2) fVec2 = new double[131072];
	if (!fVec4) fVec4 = new double[131072];
	if (!fVec6) fVec6 = new double[131072];
	if (!fVec8) fVec8 = new double[131072];
	if (!fVec9) fVec9 = new double[131072];
	mem_allocated = true;
}

void Dsp::mem_free()
{
	mem_allocated = false;
	if (fVec2) { delete fVec2; fVec2 = 0; }
	if (fVec4) { delete fVec4; fVec4 = 0; }
	if (fVec6) { delete fVec6; fVec6 = 0; }
	if (fVec8) { delete fVec8; fVec8 = 0; }
	if (fVec9) { delete fVec9; fVec9 = 0; }
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
#define fCheckbox0 (*fCheckbox0_)
#define fVslider2 (*fVslider2_)
#define fVslider3 (*fVslider3_)
	double fSlow0 = (0.0070000000000000062 * std::pow(10.0, (0.050000000000000003 * double(fVslider0))));
	double fSlow1 = (fConst6 * double(fVslider1));
	int iSlow2 = int(double(fCheckbox0));
	double fSlow3 = double(fVslider2);
	int iSlow4 = int((fConst7 / fSlow3));
	double fSlow5 = (1.0 / double(iSlow4));
	double fSlow6 = (fConst8 * fSlow3);
	double fSlow7 = (0.004073836948085289 * (std::exp(double(fVslider3)) + -1.0));
	for (int i = 0; (i < count); i = (i + 1)) {
		iVec0[0] = 1;
		fRec0[0] = (fSlow0 + (0.99299999999999999 * fRec0[1]));
		iRec7[0] = ((iRec7[1] > 0) ? ((2 * (iRec6[1] < iSlow4)) + -1) : (1 - (2 * (iRec6[1] > 0))));
		iRec6[0] = (iRec7[0] + iRec6[1]);
		fRec10[0] = (fRec10[1] + (fSlow6 * (0.0 - fRec8[1])));
		fRec9[0] = ((fSlow6 * fRec10[0]) + (double((1 - iVec0[1])) + fRec9[1]));
		fRec8[0] = fRec9[0];
		double fTemp0 = (fSlow1 * (((iSlow2 ? std::max<double>(0.0, (0.5 * (fRec8[0] + 1.0))) : (fSlow5 * double(iRec6[0]))) + 1.0) + 1.0));
		double fTemp1 = ((fRec2[1] != 0.0) ? (((fRec3[1] > 0.0) & (fRec3[1] < 1.0)) ? fRec2[1] : 0.0) : (((fRec3[1] == 0.0) & (fTemp0 != fRec4[1])) ? fConst9 : (((fRec3[1] == 1.0) & (fTemp0 != fRec5[1])) ? fConst10 : 0.0)));
		fRec2[0] = fTemp1;
		fRec3[0] = std::max<double>(0.0, std::min<double>(1.0, (fRec3[1] + fTemp1)));
		fRec4[0] = (((fRec3[1] >= 1.0) & (fRec5[1] != fTemp0)) ? fTemp0 : fRec4[1]);
		fRec5[0] = (((fRec3[1] <= 0.0) & (fRec4[1] != fTemp0)) ? fTemp0 : fRec5[1]);
		double fTemp2 = (1.0 - fRec3[0]);
		double fTemp3 = double(input0[i]);
		fVec1[0] = fTemp3;
		fRec16[0] = ((fConst20 * fVec1[1]) - (fConst21 * ((fConst22 * fRec16[1]) - (fConst15 * fTemp3))));
		fRec15[0] = (fRec16[0] - (fConst16 * ((fConst23 * fRec15[2]) + (fConst24 * fRec15[1]))));
		double fTemp4 = (fConst34 * fRec14[1]);
		fRec14[0] = ((fConst16 * (((fConst18 * fRec15[0]) + (fConst25 * fRec15[1])) + (fConst18 * fRec15[2]))) - (fConst29 * ((fConst31 * fRec14[2]) + fTemp4)));
		double fTemp5 = (fConst43 * fRec13[1]);
		fRec13[0] = ((fRec14[2] + (fConst29 * (fTemp4 + (fConst31 * fRec14[0])))) - (fConst38 * ((fConst40 * fRec13[2]) + fTemp5)));
		double fTemp6 = (fConst52 * fRec12[1]);
		fRec12[0] = ((fRec13[2] + (fConst38 * (fTemp5 + (fConst40 * fRec13[0])))) - (fConst47 * ((fConst49 * fRec12[2]) + fTemp6)));
		fRec11[0] = ((fRec12[2] + (fConst47 * (fTemp6 + (fConst49 * fRec12[0])))) - (fConst53 * fRec11[1]));
		fRec17[0] = (fSlow7 + (0.99299999999999999 * fRec17[1]));
		double fTemp7 = (0.0 - (0.00069742843622086102 * fRec17[0]));
		double fTemp8 = (fConst13 * ((fRec11[0] * fTemp7) + (0.00069742843622086102 * (fRec17[0] * fRec11[1]))));
		double fTemp9 = (int(signbit(double(fTemp8))) ? double(input12ax7_negclip(double(fTemp8))) : double(input12ax7clip(double(fTemp8))));
		fVec2[(IOTA & 131071)] = fTemp9;
		int iTemp10 = int(std::min<double>(65536.0, std::max<double>(0.0, fRec4[0])));
		int iTemp11 = int(std::min<double>(65536.0, std::max<double>(0.0, fRec5[0])));
		fRec1[0] = (((fTemp2 * fVec2[((IOTA - iTemp10) & 131071)]) + (fRec3[0] * fVec2[((IOTA - iTemp11) & 131071)])) - (fConst54 * fRec1[1]));
		double fTemp12 = (fConst3 * ((fConst5 * fRec1[0]) + (fConst4 * fRec1[1])));
		fRec25[0] = (0.0 - (fConst21 * ((fConst22 * fRec25[1]) - (fTemp3 + fVec1[1]))));
		fRec24[0] = (fRec25[0] - (fConst16 * ((fConst23 * fRec24[2]) + (fConst24 * fRec24[1]))));
		double fTemp13 = (fRec24[2] + (fRec24[0] + (2.0 * fRec24[1])));
		fVec3[0] = fTemp13;
		fRec23[0] = ((fConst16 * ((fConst56 * fTemp13) + (fConst57 * fVec3[1]))) - (fConst58 * fRec23[1]));
		fRec22[0] = (fRec23[0] - (fConst55 * ((fConst59 * fRec22[2]) + (fConst34 * fRec22[1]))));
		double fTemp14 = (fConst43 * fRec21[1]);
		fRec21[0] = ((fConst55 * (((fConst33 * fRec22[0]) + (fConst60 * fRec22[1])) + (fConst33 * fRec22[2]))) - (fConst38 * ((fConst40 * fRec21[2]) + fTemp14)));
		double fTemp15 = (fConst52 * fRec20[1]);
		fRec20[0] = ((fRec21[2] + (fConst38 * (fTemp14 + (fConst40 * fRec21[0])))) - (fConst47 * ((fConst49 * fRec20[2]) + fTemp15)));
		fRec19[0] = ((fRec20[2] + (fConst47 * (fTemp15 + (fConst49 * fRec20[0])))) - (fConst53 * fRec19[1]));
		double fTemp16 = (fConst13 * ((fRec19[0] * fTemp7) + (0.00069742843622086102 * (fRec17[0] * fRec19[1]))));
		double fTemp17 = (int(signbit(double(fTemp16))) ? double(input12ax7_negclip(double(fTemp16))) : double(input12ax7clip(double(fTemp16))));
		fVec4[(IOTA & 131071)] = fTemp17;
		fRec18[0] = (((fTemp2 * fVec4[((IOTA - iTemp10) & 131071)]) + (fRec3[0] * fVec4[((IOTA - iTemp11) & 131071)])) - (fConst54 * fRec18[1]));
		double fTemp18 = (fConst3 * ((fConst5 * fRec18[0]) + (fConst4 * fRec18[1])));
		fRec32[0] = (0.0 - (fConst63 * ((fConst30 * fRec32[1]) - (fConst16 * (fTemp13 + fVec3[1])))));
		fRec31[0] = (fRec32[0] - (fConst55 * ((fConst59 * fRec31[2]) + (fConst34 * fRec31[1]))));
		double fTemp19 = (fRec31[2] + (fRec31[0] + (2.0 * fRec31[1])));
		fVec5[0] = fTemp19;
		fRec30[0] = ((fConst55 * ((fConst62 * fTemp19) + (fConst64 * fVec5[1]))) - (fConst65 * fRec30[1]));
		fRec29[0] = (fRec30[0] - (fConst61 * ((fConst66 * fRec29[2]) + (fConst43 * fRec29[1]))));
		double fTemp20 = (fConst52 * fRec28[1]);
		fRec28[0] = ((fConst61 * (((fConst42 * fRec29[0]) + (fConst67 * fRec29[1])) + (fConst42 * fRec29[2]))) - (fConst47 * ((fConst49 * fRec28[2]) + fTemp20)));
		fRec27[0] = ((fRec28[2] + (fConst47 * (fTemp20 + (fConst49 * fRec28[0])))) - (fConst53 * fRec27[1]));
		double fTemp21 = (fConst13 * ((fRec27[0] * fTemp7) + (0.00069742843622086102 * (fRec17[0] * fRec27[1]))));
		double fTemp22 = (int(signbit(double(fTemp21))) ? double(input12ax7_negclip(double(fTemp21))) : double(input12ax7clip(double(fTemp21))));
		fVec6[(IOTA & 131071)] = fTemp22;
		fRec26[0] = (((fTemp2 * fVec6[((IOTA - iTemp10) & 131071)]) + (fRec3[0] * fVec6[((IOTA - iTemp11) & 131071)])) - (fConst54 * fRec26[1]));
		double fTemp23 = (fConst3 * ((fConst5 * fRec26[0]) + (fConst4 * fRec26[1])));
		fRec38[0] = (0.0 - (fConst70 * ((fConst39 * fRec38[1]) - (fConst55 * (fTemp19 + fVec5[1])))));
		fRec37[0] = (fRec38[0] - (fConst61 * ((fConst66 * fRec37[2]) + (fConst43 * fRec37[1]))));
		double fTemp24 = (fRec37[2] + (fRec37[0] + (2.0 * fRec37[1])));
		fVec7[0] = fTemp24;
		fRec36[0] = ((fConst61 * ((fConst69 * fTemp24) + (fConst71 * fVec7[1]))) - (fConst72 * fRec36[1]));
		fRec35[0] = (fRec36[0] - (fConst68 * ((fConst73 * fRec35[2]) + (fConst52 * fRec35[1]))));
		fRec34[0] = ((fConst68 * (((fConst51 * fRec35[0]) + (fConst74 * fRec35[1])) + (fConst51 * fRec35[2]))) - (fConst53 * fRec34[1]));
		double fTemp25 = (fConst13 * ((fRec34[0] * fTemp7) + (0.00069742843622086102 * (fRec17[0] * fRec34[1]))));
		double fTemp26 = (int(signbit(double(fTemp25))) ? double(input12ax7_negclip(double(fTemp25))) : double(input12ax7clip(double(fTemp25))));
		fVec8[(IOTA & 131071)] = fTemp26;
		fRec33[0] = (((fTemp2 * fVec8[((IOTA - iTemp10) & 131071)]) + (fRec3[0] * fVec8[((IOTA - iTemp11) & 131071)])) - (fConst54 * fRec33[1]));
		double fTemp27 = (fConst3 * ((fConst5 * fRec33[0]) + (fConst4 * fRec33[1])));
		fRec42[0] = (0.0 - (fConst75 * ((fConst48 * fRec42[1]) - (fConst61 * (fTemp24 + fVec7[1])))));
		fRec41[0] = (fRec42[0] - (fConst68 * ((fConst73 * fRec41[2]) + (fConst52 * fRec41[1]))));
		fRec40[0] = ((fConst68 * (fRec41[2] + (fRec41[0] + (2.0 * fRec41[1])))) - (fConst53 * fRec40[1]));
		double fTemp28 = (fConst13 * ((fRec40[0] * fTemp7) + (0.00069742843622086102 * (fRec17[0] * fRec40[1]))));
		double fTemp29 = (int(signbit(double(fTemp28))) ? double(input12ax7_negclip(double(fTemp28))) : double(input12ax7clip(double(fTemp28))));
		fVec9[(IOTA & 131071)] = fTemp29;
		fRec39[0] = (((fTemp2 * fVec9[((IOTA - iTemp10) & 131071)]) + (fRec3[0] * fVec9[((IOTA - iTemp11) & 131071)])) - (fConst54 * fRec39[1]));
		double fTemp30 = (fConst3 * ((fConst5 * fRec39[0]) + (fConst4 * fRec39[1])));
		output0[i] = FAUSTFLOAT((fRec0[0] * (((((int(signbit(double(fTemp12))) ? double(output12ax7_negclip(double(fTemp12))) : double(output12ax7clip(double(fTemp12)))) + (int(signbit(double(fTemp18))) ? double(output12ax7_negclip(double(fTemp18))) : double(output12ax7clip(double(fTemp18))))) + (int(signbit(double(fTemp23))) ? double(output12ax7_negclip(double(fTemp23))) : double(output12ax7clip(double(fTemp23))))) + (int(signbit(double(fTemp27))) ? double(output12ax7_negclip(double(fTemp27))) : double(output12ax7clip(double(fTemp27))))) + (int(signbit(double(fTemp30))) ? double(output12ax7_negclip(double(fTemp30))) : double(output12ax7clip(double(fTemp30)))))));
		iVec0[1] = iVec0[0];
		fRec0[1] = fRec0[0];
		iRec7[1] = iRec7[0];
		iRec6[1] = iRec6[0];
		fRec10[1] = fRec10[0];
		fRec9[1] = fRec9[0];
		fRec8[1] = fRec8[0];
		fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fVec1[1] = fVec1[0];
		fRec16[1] = fRec16[0];
		fRec15[2] = fRec15[1];
		fRec15[1] = fRec15[0];
		fRec14[2] = fRec14[1];
		fRec14[1] = fRec14[0];
		fRec13[2] = fRec13[1];
		fRec13[1] = fRec13[0];
		fRec12[2] = fRec12[1];
		fRec12[1] = fRec12[0];
		fRec11[1] = fRec11[0];
		fRec17[1] = fRec17[0];
		IOTA = (IOTA + 1);
		fRec1[1] = fRec1[0];
		fRec25[1] = fRec25[0];
		fRec24[2] = fRec24[1];
		fRec24[1] = fRec24[0];
		fVec3[1] = fVec3[0];
		fRec23[1] = fRec23[0];
		fRec22[2] = fRec22[1];
		fRec22[1] = fRec22[0];
		fRec21[2] = fRec21[1];
		fRec21[1] = fRec21[0];
		fRec20[2] = fRec20[1];
		fRec20[1] = fRec20[0];
		fRec19[1] = fRec19[0];
		fRec18[1] = fRec18[0];
		fRec32[1] = fRec32[0];
		fRec31[2] = fRec31[1];
		fRec31[1] = fRec31[0];
		fVec5[1] = fVec5[0];
		fRec30[1] = fRec30[0];
		fRec29[2] = fRec29[1];
		fRec29[1] = fRec29[0];
		fRec28[2] = fRec28[1];
		fRec28[1] = fRec28[0];
		fRec27[1] = fRec27[0];
		fRec26[1] = fRec26[0];
		fRec38[1] = fRec38[0];
		fRec37[2] = fRec37[1];
		fRec37[1] = fRec37[0];
		fVec7[1] = fVec7[0];
		fRec36[1] = fRec36[0];
		fRec35[2] = fRec35[1];
		fRec35[1] = fRec35[0];
		fRec34[1] = fRec34[0];
		fRec33[1] = fRec33[0];
		fRec42[1] = fRec42[0];
		fRec41[2] = fRec41[1];
		fRec41[1] = fRec41[0];
		fRec40[1] = fRec40[0];
		fRec39[1] = fRec39[0];
	}
#undef fVslider0
#undef fVslider1
#undef fCheckbox0
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
		fVslider3_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	// static const value_pair fCheckbox0_values[] = {{"os.triangle"},{"sine"},{0}};
	case SINEWAVE: 
		fCheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case DEPTH: 
		fVslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case OUTPUT: 
		fVslider0_ = (float*)data; // , 0.0, -20.0, 20.0, 0.10000000000000001 
		break;
	case SPEED: 
		fVslider2_ = (float*)data; // , 5.0, 0.0, 14.0, 0.10000000000000001 
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
   SINEWAVE, 
   DEPTH, 
   OUTPUT, 
   SPEED, 
} PortIndex;
*/

} // end namespace gxtubevibrato
