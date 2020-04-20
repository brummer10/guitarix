// generated from file '../src/plugins/fuzzfacerm.dsp' by dsp2cc:
// Code generated with Faust 2.15.11 (https://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

#include "trany.h"

namespace pluginlib {
namespace fuzzfacerm {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	double fConst0;
	double fConst1;
	FAUSTFLOAT fVslider0;
	double fRec1[2];
	double fConst2;
	double fConst3;
	double fConst4;
	double fConst5;
	double fConst6;
	double fConst7;
	FAUSTFLOAT fVslider1;
	double fRec2[2];
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
	double fRec0[4];
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


	int samplingFreq;
	gx_resample::FixedRateResampler smpCl;
	double fConstCl0;
	double fConstCl1;
	double fConstCl2;
	double fConstCl3;
	double fConstCl4;
	double fVecCl0[2];
	double fRecCl7[2];
	double fRecCl6[3];
	double fConstCl5;
	double fConstCl6;
	double fConstCl7;
	double fRecCl8[2];
	double fRecCl5[3];
	double fConstCl8;
	double fConstCl9;
	double fRecCl4[2];
	double fRecCl3[2];
	double fRecCl2[3];
	double fRecCl9[2];
	double fRecCl1[3];
	double fRecCl0[2];

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
	id = "fuzzfacerm";
	name = N_("Fuzz Face Mayer");
	groups = 0;
	description = N_("Roger Mayer Fuzz Face simulation"); // description (tooltip)
	category = N_("Fuzz");       // category
	shortname = N_("FF Mayer");     // shortname
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
	for (int l2 = 0; (l2 < 4); l2 = (l2 + 1)) fRec0[l2] = 0.0;

	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fVecCl0[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRecCl7[l1] = 0.0;
	for (int l2 = 0; (l2 < 3); l2 = (l2 + 1)) fRecCl6[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fRecCl8[l3] = 0.0;
	for (int l4 = 0; (l4 < 3); l4 = (l4 + 1)) fRecCl5[l4] = 0.0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fRecCl4[l5] = 0.0;
	for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) fRecCl3[l6] = 0.0;
	for (int l7 = 0; (l7 < 3); l7 = (l7 + 1)) fRecCl2[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fRecCl9[l8] = 0.0;
	for (int l9 = 0; (l9 < 3); l9 = (l9 + 1)) fRecCl1[l9] = 0.0;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) fRecCl0[l10] = 0.0;

}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSamplingFreq)));
	fConst1 = mydsp_faustpower2_f(fConst0);
	fConst2 = (2.0307859405637e-32 * fConst0);
	fConst3 = ((((-8.8888620759015093e-30 - fConst2) * fConst0) + 2.8164416336467701e-27) * fConst0);
	fConst4 = (9.9508577426340807e-30 * fConst0);
	fConst5 = (((((-8.2687471495045495e-28 - fConst4) * fConst0) + 5.0040645748528796e-25) * fConst0) + 1.0646926328610301e-27);
	fConst6 = (5.1856178516789402e-15 * fConst0);
	fConst7 = (((-4.3274021590667601e-13 - fConst6) * fConst0) + 2.6123111187704002e-10);
	fConst8 = (9.1535918071901097e-14 * fConst0);
	fConst9 = (((-2.08816997599123e-11 - fConst8) * fConst0) + 2.2172653570876899e-11);
	fConst10 = (9.6721535923580095e-14 * fConst0);
	fConst11 = (((fConst10 + 2.08898268350887e-11) * fConst0) + -2.2179341569602201e-11);
	fConst12 = (3.7877981162792101e-31 * fConst0);
	fConst13 = (((fConst12 + 2.1599331719778501e-28) * fConst0) + -8.6887484106783095e-26);
	fConst14 = (1.8560223143188301e-28 * fConst0);
	fConst15 = (((fConst14 + 4.0020445737400903e-26) * fConst0) + -2.8383244808045302e-29);
	fConst16 = (3.5847195222228401e-31 * fConst0);
	fConst17 = (((-2.0876732041785599e-28 - fConst16) * fConst0) + 8.6861283897857698e-26);
	fConst18 = (1.7565137368924901e-28 * fConst0);
	fConst19 = (((-4.0008375560677603e-26 - fConst18) * fConst0) + 2.8374686073129699e-29);
	fConst20 = ((((fConst2 + -8.8888620759015093e-30) * fConst0) + -2.8164416336467701e-27) * fConst0);
	fConst21 = (((((fConst4 + -8.2687471495045495e-28) * fConst0) + -5.0040645748528796e-25) * fConst0) + 1.0646926328610301e-27);
	fConst22 = (((fConst6 + -4.3274021590667601e-13) * fConst0) + -2.6123111187704002e-10);
	fConst23 = (((fConst8 + -2.08816997599123e-11) * fConst0) + -2.2172653570876899e-11);
	fConst24 = (((2.08898268350887e-11 - fConst10) * fConst0) + 2.2179341569602201e-11);
	fConst25 = (((2.1599331719778501e-28 - fConst12) * fConst0) + 8.6887484106783095e-26);
	fConst26 = (((4.0020445737400903e-26 - fConst14) * fConst0) + 2.8383244808045302e-29);
	fConst27 = (((fConst16 + -2.0876732041785599e-28) * fConst0) + -8.6861283897857698e-26);
	fConst28 = (((fConst18 + -4.0008375560677603e-26) * fConst0) + -2.8374686073129699e-29);
	fConst29 = (6.7692864685456698e-33 * fConst0);
	fConst30 = ((((8.8888620759015093e-30 - fConst29) * fConst0) + -2.8164416336467701e-27) * fConst0);
	fConst31 = (3.3169525808780299e-30 * fConst0);
	fConst32 = (((((8.2687471495045495e-28 - fConst31) * fConst0) + -5.0040645748528796e-25) * fConst0) + 3.5489754428701101e-28);
	fConst33 = (1.7285392838929801e-15 * fConst0);
	fConst34 = (((4.3274021590667601e-13 - fConst33) * fConst0) + -2.6123111187704002e-10);
	fConst35 = (3.0511972690633699e-14 * fConst0);
	fConst36 = (((2.08816997599123e-11 - fConst35) * fConst0) + -2.2172653570876899e-11);
	fConst37 = (3.2240511974526703e-14 * fConst0);
	fConst38 = (((fConst37 + -2.08898268350887e-11) * fConst0) + 2.2179341569602201e-11);
	fConst39 = (1.26259937209307e-31 * fConst0);
	fConst40 = (((fConst39 + -2.1599331719778501e-28) * fConst0) + 8.6887484106783095e-26);
	fConst41 = (6.1867410477294198e-29 * fConst0);
	fConst42 = (((fConst41 + -4.0020445737400903e-26) * fConst0) + 2.8383244808045302e-29);
	fConst43 = (1.1949065074076101e-31 * fConst0);
	fConst44 = (((2.0876732041785599e-28 - fConst43) * fConst0) + -8.6861283897857698e-26);
	fConst45 = (5.8550457896416201e-29 * fConst0);
	fConst46 = (((4.0008375560677603e-26 - fConst45) * fConst0) + -2.8374686073129699e-29);
	fConst47 = ((((fConst29 + 8.8888620759015093e-30) * fConst0) + 2.8164416336467701e-27) * fConst0);
	fConst48 = (((((fConst31 + 8.2687471495045495e-28) * fConst0) + 5.0040645748528796e-25) * fConst0) + 3.5489754428701101e-28);
	fConst49 = (((fConst33 + 4.3274021590667601e-13) * fConst0) + 2.6123111187704002e-10);
	fConst50 = (((fConst35 + 2.08816997599123e-11) * fConst0) + 2.2172653570876899e-11);
	fConst51 = (((-2.08898268350887e-11 - fConst37) * fConst0) + -2.2179341569602201e-11);
	fConst52 = (((-2.1599331719778501e-28 - fConst39) * fConst0) + -8.6887484106783095e-26);
	fConst53 = (((-4.0020445737400903e-26 - fConst41) * fConst0) + -2.8383244808045302e-29);
	fConst54 = (((fConst43 + 2.0876732041785599e-28) * fConst0) + 8.6861283897857698e-26);
	fConst55 = (((fConst45 + 4.0008375560677603e-26) * fConst0) + 2.8374686073129699e-29);
	fConst56 = (2.2773411020084502e-12 * fConst0);
	fConst57 = (fConst56 + 2.9038108503536499e-11);
	fConst58 = (2.23179427996828e-12 * fConst0);
	fConst59 = (-2.8457346333465799e-11 - fConst58);
	fConst60 = (6.8320233060253497e-12 * fConst0);
	fConst61 = (-2.9038108503536499e-11 - fConst60);
	fConst62 = (6.69538283990485e-12 * fConst0);
	fConst63 = (fConst62 + 2.8457346333465799e-11);
	fConst64 = (fConst60 + -2.9038108503536499e-11);
	fConst65 = (2.8457346333465799e-11 - fConst62);
	fConst66 = (2.9038108503536499e-11 - fConst56);
	fConst67 = (fConst58 + -2.8457346333465799e-11);
	fVslider0 = FAUSTFLOAT(0.5);
	fVslider1 = FAUSTFLOAT(0.5);

	samplingFreq = 96000;
	smpCl.setup(fSamplingFreq, samplingFreq);
	fSamplingFreq = samplingFreq;
	fConstCl0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSamplingFreq)));
	fConstCl1 = std::tan((97.389372261283583 / fConstCl0));
	fConstCl2 = (1.0 / fConstCl1);
	fConstCl3 = (fConstCl2 + 1.0);
	fConstCl4 = (1.0 / (fConstCl3 * fConstCl1));
	fConstCl5 = (1.0 / std::tan((270.1769682087222 / fConstCl0)));
	fConstCl6 = (1.0 / (fConstCl5 + 1.0));
	fConstCl7 = (1.0 - fConstCl5);
	fConstCl8 = (0.0 - fConstCl4);
	fConstCl9 = ((1.0 - fConstCl2) / fConstCl3);

	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double fSlow0 = (0.0070000000000000062 * (1.0 - double(fVslider0)));
	double fSlow1 = (0.0070000000000000062 * (1.0 - double(fVslider1)));
	for (int i = 0; (i < count); i = (i + 1)) {
		fRec1[0] = (fSlow0 + (0.99299999999999999 * fRec1[1]));
		fRec2[0] = (fSlow1 + (0.99299999999999999 * fRec2[1]));
		double fTemp0 = (((fRec1[0] * (fConst47 + ((fConst48 * fRec1[0]) + 1.08642105394636e-24))) + (fConst0 * (fConst49 + (fRec2[0] * (fConst50 + ((fRec2[0] * (fConst51 + (fRec1[0] * (fConst52 + (fConst53 * fRec1[0]))))) + (fRec1[0] * (fConst54 + (fConst55 * fRec1[0]))))))))) + 2.7732536960409302e-10);
		fRec0[0] = (double(input0[i]) - ((((fRec0[1] * (((fRec1[0] * (fConst3 + ((fConst5 * fRec1[0]) + 3.2592631618390701e-24))) + (fConst0 * (fConst7 + (fRec2[0] * (fConst9 + ((fRec2[0] * (fConst11 + (fRec1[0] * (fConst13 + (fConst15 * fRec1[0]))))) + (fRec1[0] * (fConst17 + (fConst19 * fRec1[0]))))))))) + 8.3197610881228e-10)) + (fRec0[2] * (((fRec1[0] * (fConst20 + ((fConst21 * fRec1[0]) + 3.2592631618390701e-24))) + (fConst0 * (fConst22 + (fRec2[0] * (fConst23 + ((fRec2[0] * (fConst24 + (fRec1[0] * (fConst25 + (fConst26 * fRec1[0]))))) + (fRec1[0] * (fConst27 + (fConst28 * fRec1[0]))))))))) + 8.3197610881228e-10))) + (fRec0[3] * (((fRec1[0] * (fConst30 + ((fConst32 * fRec1[0]) + 1.08642105394636e-24))) + (fConst0 * (fConst34 + (fRec2[0] * (fConst36 + ((fRec2[0] * (fConst38 + (fRec1[0] * (fConst40 + (fConst42 * fRec1[0]))))) + (fRec1[0] * (fConst44 + (fConst46 * fRec1[0]))))))))) + 2.7732536960409302e-10))) / fTemp0));
		double fTemp1 = (2.1870008532593e-12 * fRec1[0]);
		double fTemp2 = (4.47934267089816e-14 * fRec1[0]);
		double fTemp3 = (1.3438028012694499e-13 * fRec1[0]);
		double fTemp4 = (6.5610025597778999e-12 * fRec1[0]);
		output0[i] = FAUSTFLOAT((fConst1 * (((((fRec0[0] * (fConst57 + ((fConst0 * (fRec2[0] * ((fTemp1 + (fRec2[0] * (fTemp2 + -4.5707578274471097e-14))) + -2.2316335237339801e-12))) + (fConst59 * fRec1[0])))) + (fRec0[1] * (fConst61 + ((fConst0 * (fRec2[0] * (((fRec2[0] * ((0.0 - fTemp3) + 1.3712273482341299e-13)) - fTemp4) + 6.6949005712019396e-12))) + (fConst63 * fRec1[0]))))) + (fRec0[2] * (fConst64 + ((fConst0 * (fRec2[0] * ((fTemp4 + (fRec2[0] * (fTemp3 + -1.3712273482341299e-13))) + -6.6949005712019396e-12))) + (fConst65 * fRec1[0]))))) + (fRec0[3] * (fConst66 + ((fConst0 * (fRec2[0] * (((fRec2[0] * ((0.0 - fTemp2) + 4.5707578274471097e-14)) - fTemp1) + 2.2316335237339801e-12))) + (fConst67 * fRec1[0]))))) / fTemp0)));
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		for (int j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
			fRec0[j0] = fRec0[(j0 - 1)];
		}
	}

	FAUSTFLOAT bufCl[smpCl.max_out_count(count)];
	int ReCount = smpCl.up(count, output0, bufCl);
	for (int i = 0; (i < ReCount); i = (i + 1)) {
		double fTemp0 = double(bufCl[i]);
		fVecCl0[0] = fTemp0;
		fRecCl7[0] = ((0.93028479253239138 * (fVecCl0[1] + fTemp0)) - (0.86056958506478287 * fRecCl7[1]));
		fRecCl6[0] = (fRecCl7[0] - ((1.8405051250752198 * fRecCl6[1]) + (0.86129424393186271 * fRecCl6[2])));
		fRecCl8[0] = (fConstCl6 * ((0.027 * (fRecCl5[1] + fRecCl5[2])) - (fConstCl7 * fRecCl8[1])));
		fRecCl5[0] = (double(Ftrany(int(TRANY_TABLE_KT88_68k), double((((0.92544984225177063 * (fRecCl6[0] + fRecCl6[2])) + (fRecCl8[0] + (1.8508996845035413 * fRecCl6[1]))) + -5.5628950000000001)))) + -43.966851851851828);
		fRecCl4[0] = ((0.025000000000000001 * ((fConstCl4 * fRecCl5[0]) + (fConstCl8 * fRecCl5[1]))) - (fConstCl9 * fRecCl4[1]));
		fRecCl3[0] = ((0.93028479253239138 * (fRecCl4[0] + fRecCl4[1])) - (0.86056958506478287 * fRecCl3[1]));
		fRecCl2[0] = (fRecCl3[0] - ((1.8405051250752198 * fRecCl2[1]) + (0.86129424393186271 * fRecCl2[2])));
		fRecCl9[0] = (fConstCl6 * ((0.027 * (fRecCl1[1] + fRecCl1[2])) - (fConstCl7 * fRecCl9[1])));
		fRecCl1[0] = (double(Ftrany(int(TRANY_TABLE_KT88_68k), double((((0.92544984225177063 * (fRecCl2[0] + fRecCl2[2])) + (fRecCl9[0] + (1.8508996845035413 * fRecCl2[1]))) + -5.5628950000000001)))) + -43.966851851851828);
		fRecCl0[0] = ((0.025000000000000001 * ((fConstCl4 * fRecCl1[0]) + (fConstCl8 * fRecCl1[1]))) - (fConstCl9 * fRecCl0[1]));
		bufCl[i] = FAUSTFLOAT(fRecCl0[0]);
		fVecCl0[1] = fVecCl0[0];
		fRecCl7[1] = fRecCl7[0];
		fRecCl6[2] = fRecCl6[1];
		fRecCl6[1] = fRecCl6[0];
		fRecCl8[1] = fRecCl8[0];
		fRecCl5[2] = fRecCl5[1];
		fRecCl5[1] = fRecCl5[0];
		fRecCl4[1] = fRecCl4[0];
		fRecCl3[1] = fRecCl3[0];
		fRecCl2[2] = fRecCl2[1];
		fRecCl2[1] = fRecCl2[0];
		fRecCl9[1] = fRecCl9[0];
		fRecCl1[2] = fRecCl1[1];
		fRecCl1[1] = fRecCl1[0];
		fRecCl0[1] = fRecCl0[0];
	}
	smpCl.down(bufCl, output0);

}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("fuzzfacerm.Fuzz",N_("Fuzz"),"S","",&fVslider1, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("fuzzfacerm.Level",N_("Level"),"S","",&fVslider0, 0.5, 0.0, 1.0, 0.01);
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
                        <property name=\"var_id\">fuzzfacerm.Fuzz</property>\n\
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
                      <object class=\"GxMidKnob\" id=\"gxbigknob2\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">fuzzfacerm.Level</property>\n\
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
                <property name=\"var_id\">fuzzfacerm.Level</property>\n\
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
#define PARAM(p) ("fuzzfacerm" "." p)

b.openHorizontalhideBox("");
    b.create_master_slider(PARAM("Fuzz"), N_("Fuzz"));
b.closeBox();
b.openHorizontalBox("");

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

} // end namespace fuzzfacerm
} // end namespace pluginlib
