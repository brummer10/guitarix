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
	int iVec0[2];
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
	double fVec1[2];
	double fConst35;
	double fConst37;
	double fRec9[2];
	double fRec8[3];
	double fVec2[2];
	double fConst38;
	double fConst40;
	double fRec7[2];
	double fRec6[3];
	double fVec3[2];
	double fConst41;
	double fConst43;
	double fRec5[2];
	double fRec4[3];
	double fVec4[2];
	double fConst44;
	double fConst46;
	double fRec3[2];
	double fRec2[3];
	double fRec1[2];
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec10[2];
	double fConst47;
	int IOTA0;
	double *fVec5;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT	*fCheckbox0_;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fConst48;
	int iRec16[2];
	int iRec15[2];
	double fConst49;
	double fRec19[2];
	double fRec18[2];
	double fRec17[2];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fConst50;
	double fConst51;
	double fConst52;
	double fRec11[2];
	double fRec12[2];
	double fRec13[2];
	double fRec14[2];
	double fRec0[2];
	double fConst53;
	double fConst54;
	double fConst55;
	double fConst56;
	double fConst57;
	double fConst58;
	double fRec23[2];
	double fRec22[3];
	double fConst59;
	double fRec21[2];
	double *fVec6;
	double fRec20[2];
	double fConst60;
	double fConst61;
	double fConst62;
	double fConst63;
	double fConst64;
	double fRec28[2];
	double fRec27[3];
	double fConst65;
	double fRec26[3];
	double fRec25[2];
	double *fVec7;
	double fRec24[2];
	double fConst66;
	double fConst67;
	double fConst68;
	double fConst69;
	double fConst70;
	double fRec34[2];
	double fRec33[3];
	double fConst71;
	double fRec32[3];
	double fRec31[3];
	double fRec30[2];
	double *fVec8;
	double fRec29[2];
	double fConst72;
	double fConst73;
	double fConst74;
	double fRec41[2];
	double fRec40[3];
	double fConst75;
	double fRec39[3];
	double fRec38[3];
	double fRec37[3];
	double fRec36[2];
	double *fVec9;
	double fRec35[2];
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fRec42[2];

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
	  fVec5(0),
	  fVec6(0),
	  fVec7(0),
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) iVec0[l0] = 0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fVec1[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec9[l2] = 0.0;
	for (int l3 = 0; l3 < 3; l3 = l3 + 1) fRec8[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fVec2[l4] = 0.0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fRec7[l5] = 0.0;
	for (int l6 = 0; l6 < 3; l6 = l6 + 1) fRec6[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fVec3[l7] = 0.0;
	for (int l8 = 0; l8 < 2; l8 = l8 + 1) fRec5[l8] = 0.0;
	for (int l9 = 0; l9 < 3; l9 = l9 + 1) fRec4[l9] = 0.0;
	for (int l10 = 0; l10 < 2; l10 = l10 + 1) fVec4[l10] = 0.0;
	for (int l11 = 0; l11 < 2; l11 = l11 + 1) fRec3[l11] = 0.0;
	for (int l12 = 0; l12 < 3; l12 = l12 + 1) fRec2[l12] = 0.0;
	for (int l13 = 0; l13 < 2; l13 = l13 + 1) fRec1[l13] = 0.0;
	for (int l14 = 0; l14 < 2; l14 = l14 + 1) fRec10[l14] = 0.0;
	for (int l15 = 0; l15 < 131072; l15 = l15 + 1) fVec5[l15] = 0.0;
	for (int l16 = 0; l16 < 2; l16 = l16 + 1) iRec16[l16] = 0;
	for (int l17 = 0; l17 < 2; l17 = l17 + 1) iRec15[l17] = 0;
	for (int l18 = 0; l18 < 2; l18 = l18 + 1) fRec19[l18] = 0.0;
	for (int l19 = 0; l19 < 2; l19 = l19 + 1) fRec18[l19] = 0.0;
	for (int l20 = 0; l20 < 2; l20 = l20 + 1) fRec17[l20] = 0.0;
	for (int l21 = 0; l21 < 2; l21 = l21 + 1) fRec11[l21] = 0.0;
	for (int l22 = 0; l22 < 2; l22 = l22 + 1) fRec12[l22] = 0.0;
	for (int l23 = 0; l23 < 2; l23 = l23 + 1) fRec13[l23] = 0.0;
	for (int l24 = 0; l24 < 2; l24 = l24 + 1) fRec14[l24] = 0.0;
	for (int l25 = 0; l25 < 2; l25 = l25 + 1) fRec0[l25] = 0.0;
	for (int l26 = 0; l26 < 2; l26 = l26 + 1) fRec23[l26] = 0.0;
	for (int l27 = 0; l27 < 3; l27 = l27 + 1) fRec22[l27] = 0.0;
	for (int l28 = 0; l28 < 2; l28 = l28 + 1) fRec21[l28] = 0.0;
	for (int l29 = 0; l29 < 131072; l29 = l29 + 1) fVec6[l29] = 0.0;
	for (int l30 = 0; l30 < 2; l30 = l30 + 1) fRec20[l30] = 0.0;
	for (int l31 = 0; l31 < 2; l31 = l31 + 1) fRec28[l31] = 0.0;
	for (int l32 = 0; l32 < 3; l32 = l32 + 1) fRec27[l32] = 0.0;
	for (int l33 = 0; l33 < 3; l33 = l33 + 1) fRec26[l33] = 0.0;
	for (int l34 = 0; l34 < 2; l34 = l34 + 1) fRec25[l34] = 0.0;
	for (int l35 = 0; l35 < 131072; l35 = l35 + 1) fVec7[l35] = 0.0;
	for (int l36 = 0; l36 < 2; l36 = l36 + 1) fRec24[l36] = 0.0;
	for (int l37 = 0; l37 < 2; l37 = l37 + 1) fRec34[l37] = 0.0;
	for (int l38 = 0; l38 < 3; l38 = l38 + 1) fRec33[l38] = 0.0;
	for (int l39 = 0; l39 < 3; l39 = l39 + 1) fRec32[l39] = 0.0;
	for (int l40 = 0; l40 < 3; l40 = l40 + 1) fRec31[l40] = 0.0;
	for (int l41 = 0; l41 < 2; l41 = l41 + 1) fRec30[l41] = 0.0;
	for (int l42 = 0; l42 < 131072; l42 = l42 + 1) fVec8[l42] = 0.0;
	for (int l43 = 0; l43 < 2; l43 = l43 + 1) fRec29[l43] = 0.0;
	for (int l44 = 0; l44 < 2; l44 = l44 + 1) fRec41[l44] = 0.0;
	for (int l45 = 0; l45 < 3; l45 = l45 + 1) fRec40[l45] = 0.0;
	for (int l46 = 0; l46 < 3; l46 = l46 + 1) fRec39[l46] = 0.0;
	for (int l47 = 0; l47 < 3; l47 = l47 + 1) fRec38[l47] = 0.0;
	for (int l48 = 0; l48 < 3; l48 = l48 + 1) fRec37[l48] = 0.0;
	for (int l49 = 0; l49 < 2; l49 = l49 + 1) fRec36[l49] = 0.0;
	for (int l50 = 0; l50 < 131072; l50 = l50 + 1) fVec9[l50] = 0.0;
	for (int l51 = 0; l51 < 2; l51 = l51 + 1) fRec35[l51] = 0.0;
	for (int l52 = 0; l52 < 2; l52 = l52 + 1) fRec42[l52] = 0.0;
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
	fConst48 = 0.5 * fConst0;
	fConst49 = 6.283185307179586 / fConst0;
	fConst50 = 0.005 * fConst0;
	fConst51 = 1e+01 / fConst0;
	fConst52 = 0.0 - fConst51;
	fConst53 = 0.000617187446540506 * fConst0;
	fConst54 = 0.0 - fConst53;
	fConst55 = 1.0 / fConst2;
	fConst56 = fConst44 / fConst45;
	fConst57 = 1.0 / (fConst7 * fConst45);
	fConst58 = 0.0 - fConst57;
	fConst59 = 0.0 - 2.0 / fConst8;
	fConst60 = 1.0 - fConst44 / fConst7;
	fConst61 = 1.0 / (fConst45 / fConst7 + 1.0);
	fConst62 = fConst41 / fConst42;
	fConst63 = 1.0 / (fConst14 * fConst42);
	fConst64 = 0.0 - fConst63;
	fConst65 = 0.0 - 2.0 / fConst15;
	fConst66 = 1.0 - fConst41 / fConst14;
	fConst67 = 1.0 / (fConst42 / fConst14 + 1.0);
	fConst68 = fConst38 / fConst39;
	fConst69 = 1.0 / (fConst21 * fConst39);
	fConst70 = 0.0 - fConst69;
	fConst71 = 0.0 - 2.0 / fConst22;
	fConst72 = 1.0 - fConst38 / fConst21;
	fConst73 = 1.0 / (fConst39 / fConst21 + 1.0);
	fConst74 = 0.0 - 1.0 / (fConst28 * fConst36);
	fConst75 = 0.0 - 2.0 / fConst29;
	IOTA0 = 0;
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void Dsp::mem_alloc()
{
	if (!fVec5) fVec5 = new double[131072];
	if (!fVec6) fVec6 = new double[131072];
	if (!fVec7) fVec7 = new double[131072];
	if (!fVec8) fVec8 = new double[131072];
	if (!fVec9) fVec9 = new double[131072];
	mem_allocated = true;
}

void Dsp::mem_free()
{
	mem_allocated = false;
	if (fVec5) { delete fVec5; fVec5 = 0; }
	if (fVec6) { delete fVec6; fVec6 = 0; }
	if (fVec7) { delete fVec7; fVec7 = 0; }
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
#define fCheckbox0 (*fCheckbox0_)
#define fVslider1 (*fVslider1_)
#define fVslider2 (*fVslider2_)
#define fVslider3 (*fVslider3_)
	double fSlow0 = 0.004073836948085289 * (std::exp(double(fVslider0)) + -1.0);
	int iSlow1 = int(double(fCheckbox0));
	double fSlow2 = double(fVslider1);
	int iSlow3 = int(fConst48 / fSlow2);
	double fSlow4 = 1.0 / double(iSlow3);
	double fSlow5 = fConst49 * fSlow2;
	double fSlow6 = fConst50 * double(fVslider2);
	double fSlow7 = 0.007000000000000006 * std::pow(1e+01, 0.05 * double(fVslider3));
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		iVec0[0] = 1;
		double fTemp0 = double(input0[i0]);
		fVec1[0] = fTemp0;
		fRec9[0] = 0.0 - fConst37 * (fConst35 * fRec9[1] - (fTemp0 + fVec1[1]));
		fRec8[0] = fRec9[0] - fConst34 * (fConst33 * fRec8[2] + fConst31 * fRec8[1]);
		double fTemp1 = fRec8[2] + fRec8[0] + 2.0 * fRec8[1];
		fVec2[0] = fTemp1;
		fRec7[0] = 0.0 - fConst40 * (fConst38 * fRec7[1] - fConst34 * (fTemp1 + fVec2[1]));
		fRec6[0] = fRec7[0] - fConst27 * (fConst26 * fRec6[2] + fConst24 * fRec6[1]);
		double fTemp2 = fRec6[2] + fRec6[0] + 2.0 * fRec6[1];
		fVec3[0] = fTemp2;
		fRec5[0] = 0.0 - fConst43 * (fConst41 * fRec5[1] - fConst27 * (fTemp2 + fVec3[1]));
		fRec4[0] = fRec5[0] - fConst20 * (fConst19 * fRec4[2] + fConst17 * fRec4[1]);
		double fTemp3 = fRec4[2] + fRec4[0] + 2.0 * fRec4[1];
		fVec4[0] = fTemp3;
		fRec3[0] = 0.0 - fConst46 * (fConst44 * fRec3[1] - fConst20 * (fTemp3 + fVec4[1]));
		fRec2[0] = fRec3[0] - fConst13 * (fConst12 * fRec2[2] + fConst10 * fRec2[1]);
		fRec1[0] = fConst13 * (fRec2[2] + fRec2[0] + 2.0 * fRec2[1]) - fConst6 * fRec1[1];
		fRec10[0] = fSlow0 + 0.993 * fRec10[1];
		double fTemp4 = 0.0 - 0.000697428436220861 * fRec10[0];
		double fTemp5 = fConst47 * (fRec1[0] * fTemp4 + 0.000697428436220861 * fRec10[0] * fRec1[1]);
		double fTemp6 = ((signbit(fTemp5)) ? input12ax7_negclip(fTemp5) : input12ax7clip(fTemp5));
		fVec5[IOTA0 & 131071] = fTemp6;
		iRec16[0] = ((iRec16[1] > 0) ? 2 * (iRec15[1] < iSlow3) + -1 : 1 - 2 * (iRec15[1] > 0));
		iRec15[0] = iRec16[0] + iRec15[1];
		fRec19[0] = fRec19[1] + fSlow5 * (0.0 - fRec17[1]);
		fRec18[0] = fSlow5 * fRec19[0] + double(1 - iVec0[1]) + fRec18[1];
		fRec17[0] = fRec18[0];
		double fTemp7 = fSlow6 * (((iSlow1) ? std::max<double>(0.0, 0.5 * (fRec17[0] + 1.0)) : fSlow4 * double(iRec15[0])) + 1.0 + 1.0);
		double fTemp8 = ((fRec11[1] != 0.0) ? (((fRec12[1] > 0.0) & (fRec12[1] < 1.0)) ? fRec11[1] : 0.0) : (((fRec12[1] == 0.0) & (fTemp7 != fRec13[1])) ? fConst51 : (((fRec12[1] == 1.0) & (fTemp7 != fRec14[1])) ? fConst52 : 0.0)));
		fRec11[0] = fTemp8;
		fRec12[0] = std::max<double>(0.0, std::min<double>(1.0, fRec12[1] + fTemp8));
		fRec13[0] = (((fRec12[1] >= 1.0) & (fRec14[1] != fTemp7)) ? fTemp7 : fRec13[1]);
		fRec14[0] = (((fRec12[1] <= 0.0) & (fRec13[1] != fTemp7)) ? fTemp7 : fRec14[1]);
		int iTemp9 = int(std::min<double>(65536.0, std::max<double>(0.0, fRec13[0])));
		double fTemp10 = fVec5[(IOTA0 - iTemp9) & 131071];
		int iTemp11 = int(std::min<double>(65536.0, std::max<double>(0.0, fRec14[0])));
		fRec0[0] = fTemp10 + fRec12[0] * (fVec5[(IOTA0 - iTemp11) & 131071] - fTemp10) - fConst3 * fRec0[1];
		double fTemp12 = fConst55 * (fConst54 * fRec0[0] + fConst53 * fRec0[1]);
		fRec23[0] = fConst20 * (fConst57 * fTemp3 + fConst58 * fVec4[1]) - fConst56 * fRec23[1];
		fRec22[0] = fRec23[0] - fConst13 * (fConst12 * fRec22[2] + fConst10 * fRec22[1]);
		fRec21[0] = fConst13 * (fConst9 * fRec22[0] + fConst59 * fRec22[1] + fConst9 * fRec22[2]) - fConst6 * fRec21[1];
		double fTemp13 = fConst47 * (fRec21[0] * fTemp4 + 0.000697428436220861 * fRec10[0] * fRec21[1]);
		double fTemp14 = ((signbit(fTemp13)) ? input12ax7_negclip(fTemp13) : input12ax7clip(fTemp13));
		fVec6[IOTA0 & 131071] = fTemp14;
		double fTemp15 = fVec6[(IOTA0 - iTemp9) & 131071];
		fRec20[0] = fTemp15 + fRec12[0] * (fVec6[(IOTA0 - iTemp11) & 131071] - fTemp15) - fConst3 * fRec20[1];
		double fTemp16 = fConst55 * (fConst54 * fRec20[0] + fConst53 * fRec20[1]);
		double fTemp17 = fConst10 * fRec26[1];
		fRec28[0] = fConst27 * (fConst63 * fTemp2 + fConst64 * fVec3[1]) - fConst62 * fRec28[1];
		fRec27[0] = fRec28[0] - fConst20 * (fConst19 * fRec27[2] + fConst17 * fRec27[1]);
		fRec26[0] = fConst20 * (fConst16 * fRec27[0] + fConst65 * fRec27[1] + fConst16 * fRec27[2]) - fConst61 * (fConst60 * fRec26[2] + fTemp17);
		fRec25[0] = fRec26[2] + fConst61 * (fTemp17 + fConst60 * fRec26[0]) - fConst6 * fRec25[1];
		double fTemp18 = fConst47 * (fRec25[0] * fTemp4 + 0.000697428436220861 * fRec10[0] * fRec25[1]);
		double fTemp19 = ((signbit(fTemp18)) ? input12ax7_negclip(fTemp18) : input12ax7clip(fTemp18));
		fVec7[IOTA0 & 131071] = fTemp19;
		double fTemp20 = fVec7[(IOTA0 - iTemp9) & 131071];
		fRec24[0] = fTemp20 + fRec12[0] * (fVec7[(IOTA0 - iTemp11) & 131071] - fTemp20) - fConst3 * fRec24[1];
		double fTemp21 = fConst55 * (fConst54 * fRec24[0] + fConst53 * fRec24[1]);
		double fTemp22 = fConst10 * fRec31[1];
		double fTemp23 = fConst17 * fRec32[1];
		fRec34[0] = fConst34 * (fConst69 * fTemp1 + fConst70 * fVec2[1]) - fConst68 * fRec34[1];
		fRec33[0] = fRec34[0] - fConst27 * (fConst26 * fRec33[2] + fConst24 * fRec33[1]);
		fRec32[0] = fConst27 * (fConst23 * fRec33[0] + fConst71 * fRec33[1] + fConst23 * fRec33[2]) - fConst67 * (fConst66 * fRec32[2] + fTemp23);
		fRec31[0] = fRec32[2] + fConst67 * (fTemp23 + fConst66 * fRec32[0]) - fConst61 * (fConst60 * fRec31[2] + fTemp22);
		fRec30[0] = fRec31[2] + fConst61 * (fTemp22 + fConst60 * fRec31[0]) - fConst6 * fRec30[1];
		double fTemp24 = fConst47 * (fRec30[0] * fTemp4 + 0.000697428436220861 * fRec10[0] * fRec30[1]);
		double fTemp25 = ((signbit(fTemp24)) ? input12ax7_negclip(fTemp24) : input12ax7clip(fTemp24));
		fVec8[IOTA0 & 131071] = fTemp25;
		double fTemp26 = fVec8[(IOTA0 - iTemp9) & 131071];
		fRec29[0] = fTemp26 + fRec12[0] * (fVec8[(IOTA0 - iTemp11) & 131071] - fTemp26) - fConst3 * fRec29[1];
		double fTemp27 = fConst55 * (fConst54 * fRec29[0] + fConst53 * fRec29[1]);
		double fTemp28 = fConst10 * fRec37[1];
		double fTemp29 = fConst17 * fRec38[1];
		double fTemp30 = fConst24 * fRec39[1];
		fRec41[0] = fConst74 * fVec1[1] - fConst37 * (fConst35 * fRec41[1] - fConst32 * fTemp0);
		fRec40[0] = fRec41[0] - fConst34 * (fConst33 * fRec40[2] + fConst31 * fRec40[1]);
		fRec39[0] = fConst34 * (fConst30 * fRec40[0] + fConst75 * fRec40[1] + fConst30 * fRec40[2]) - fConst73 * (fConst72 * fRec39[2] + fTemp30);
		fRec38[0] = fRec39[2] + fConst73 * (fTemp30 + fConst72 * fRec39[0]) - fConst67 * (fConst66 * fRec38[2] + fTemp29);
		fRec37[0] = fRec38[2] + fConst67 * (fTemp29 + fConst66 * fRec38[0]) - fConst61 * (fConst60 * fRec37[2] + fTemp28);
		fRec36[0] = fRec37[2] + fConst61 * (fTemp28 + fConst60 * fRec37[0]) - fConst6 * fRec36[1];
		double fTemp31 = fConst47 * (fRec36[0] * fTemp4 + 0.000697428436220861 * fRec10[0] * fRec36[1]);
		double fTemp32 = ((signbit(fTemp31)) ? input12ax7_negclip(fTemp31) : input12ax7clip(fTemp31));
		fVec9[IOTA0 & 131071] = fTemp32;
		double fTemp33 = fVec9[(IOTA0 - iTemp9) & 131071];
		fRec35[0] = fTemp33 + fRec12[0] * (fVec9[(IOTA0 - iTemp11) & 131071] - fTemp33) - fConst3 * fRec35[1];
		double fTemp34 = fConst55 * (fConst54 * fRec35[0] + fConst53 * fRec35[1]);
		fRec42[0] = fSlow7 + 0.993 * fRec42[1];
		output0[i0] = FAUSTFLOAT(fRec42[0] * (((signbit(fTemp34)) ? output12ax7_negclip(fTemp34) : output12ax7clip(fTemp34)) + ((signbit(fTemp27)) ? output12ax7_negclip(fTemp27) : output12ax7clip(fTemp27)) + ((signbit(fTemp21)) ? output12ax7_negclip(fTemp21) : output12ax7clip(fTemp21)) + ((signbit(fTemp16)) ? output12ax7_negclip(fTemp16) : output12ax7clip(fTemp16)) + ((signbit(fTemp12)) ? output12ax7_negclip(fTemp12) : output12ax7clip(fTemp12))));
		iVec0[1] = iVec0[0];
		fVec1[1] = fVec1[0];
		fRec9[1] = fRec9[0];
		fRec8[2] = fRec8[1];
		fRec8[1] = fRec8[0];
		fVec2[1] = fVec2[0];
		fRec7[1] = fRec7[0];
		fRec6[2] = fRec6[1];
		fRec6[1] = fRec6[0];
		fVec3[1] = fVec3[0];
		fRec5[1] = fRec5[0];
		fRec4[2] = fRec4[1];
		fRec4[1] = fRec4[0];
		fVec4[1] = fVec4[0];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
		fRec10[1] = fRec10[0];
		IOTA0 = IOTA0 + 1;
		iRec16[1] = iRec16[0];
		iRec15[1] = iRec15[0];
		fRec19[1] = fRec19[0];
		fRec18[1] = fRec18[0];
		fRec17[1] = fRec17[0];
		fRec11[1] = fRec11[0];
		fRec12[1] = fRec12[0];
		fRec13[1] = fRec13[0];
		fRec14[1] = fRec14[0];
		fRec0[1] = fRec0[0];
		fRec23[1] = fRec23[0];
		fRec22[2] = fRec22[1];
		fRec22[1] = fRec22[0];
		fRec21[1] = fRec21[0];
		fRec20[1] = fRec20[0];
		fRec28[1] = fRec28[0];
		fRec27[2] = fRec27[1];
		fRec27[1] = fRec27[0];
		fRec26[2] = fRec26[1];
		fRec26[1] = fRec26[0];
		fRec25[1] = fRec25[0];
		fRec24[1] = fRec24[0];
		fRec34[1] = fRec34[0];
		fRec33[2] = fRec33[1];
		fRec33[1] = fRec33[0];
		fRec32[2] = fRec32[1];
		fRec32[1] = fRec32[0];
		fRec31[2] = fRec31[1];
		fRec31[1] = fRec31[0];
		fRec30[1] = fRec30[0];
		fRec29[1] = fRec29[0];
		fRec41[1] = fRec41[0];
		fRec40[2] = fRec40[1];
		fRec40[1] = fRec40[0];
		fRec39[2] = fRec39[1];
		fRec39[1] = fRec39[0];
		fRec38[2] = fRec38[1];
		fRec38[1] = fRec38[0];
		fRec37[2] = fRec37[1];
		fRec37[1] = fRec37[0];
		fRec36[1] = fRec36[0];
		fRec35[1] = fRec35[0];
		fRec42[1] = fRec42[0];
	}
#undef fVslider0
#undef fCheckbox0
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
	// static const value_pair fCheckbox0_values[] = {{"os.triangle"},{"sine"},{0}};
	case SINEWAVE: 
		fCheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case DRIVE: 
		fVslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case DEPTH: 
		fVslider2_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case OUTPUT: 
		fVslider3_ = (float*)data; // , 0.0, -2e+01, 2e+01, 0.1 
		break;
	case SPEED: 
		fVslider1_ = (float*)data; // , 5.0, 0.0, 14.0, 0.1 
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
