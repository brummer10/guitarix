// generated from file '../src/plugins/fuzzfacerm.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

#include "trany.h"

namespace pluginlib {
namespace fuzzfacerm {

class Dsp: public PluginDef {
private:
	int fSampleRate;
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	double fConst4;
	double fConst5;
	double fVec0[2];
	double fConst6;
	double fConst7;
	double fRec1[2];
	FAUSTFLOAT fVslider0;
	double fRec2[2];
	double fConst8;
	double fConst9;
	double fConst10;
	double fConst11;
	double fConst12;
	double fConst13;
	FAUSTFLOAT fVslider1;
	double fRec3[2];
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
	double fRec0[4];
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
	void init(unsigned int sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static int load_ui_f_static(const UiBuilder& b, int form);
	static void init_static(unsigned int sample_rate, PluginDef*);
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fVec0[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec1[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec2[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fRec3[l3] = 0.0;
	for (int l4 = 0; (l4 < 4); l4 = (l4 + 1)) fRec0[l4] = 0.0;

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

inline void Dsp::init(unsigned int sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = mydsp_faustpower2_f(fConst0);
	fConst2 = std::tan((97.389372261283583 / fConst0));
	fConst3 = (1.0 / fConst2);
	fConst4 = (fConst3 + 1.0);
	fConst5 = (0.0 - (1.0 / (fConst2 * fConst4)));
	fConst6 = (1.0 / fConst4);
	fConst7 = (1.0 - fConst3);
	fConst8 = (2.0307873230135699e-32 * fConst0);
	fConst9 = (fConst0 * ((fConst0 * (-8.8888681269608693e-30 - fConst8)) + 2.81644355092887e-27));
	fConst10 = (9.9508578827377004e-30 * fConst0);
	fConst11 = ((fConst0 * ((fConst0 * (-8.2687237414539291e-28 - fConst10)) + 5.0040587809689198e-25)) + -6.3883357623002696e-39);
	fConst12 = (5.18561792814375e-15 * fConst0);
	fConst13 = ((fConst0 * (-4.3273899882224502e-13 - fConst12)) + 2.6123081073531499e-10);
	fConst14 = (9.1535919421650802e-14 * fConst0);
	fConst15 = ((fConst0 * (-2.08816784713571e-11 - fConst14)) + 2.2157896733672402e-11);
	fConst16 = (9.6721537349794504e-14 * fConst0);
	fConst17 = ((fConst0 * (fConst16 + 2.0889804323188e-11)) + -2.2164580281252099e-11);
	fConst18 = (3.7878006948085699e-31 * fConst0);
	fConst19 = ((fConst0 * (fConst18 + 2.1599346423442701e-28)) + -8.6887543255114101e-26);
	fConst20 = (1.8560223404508299e-28 * fConst0);
	fConst21 = ((fConst0 * (fConst20 + 4.0020402423305203e-26)) + 1.7030426647182999e-40);
	fConst22 = (3.5847219625072098e-31 * fConst0);
	fConst23 = ((fConst0 * (-2.08767462535429e-28 - fConst22)) + 8.6861343028353e-26);
	fConst24 = (1.7565137616234499e-28 * fConst0);
	fConst25 = ((fConst0 * (-4.0008334598859102e-26 - fConst24)) + -1.70252912615652e-40);
	fConst26 = (fConst0 * ((fConst0 * (fConst8 + -8.8888681269608693e-30)) + -2.81644355092887e-27));
	fConst27 = ((fConst0 * ((fConst0 * (fConst10 + -8.2687237414539291e-28)) + -5.0040587809689198e-25)) + -6.3883357623002696e-39);
	fConst28 = ((fConst0 * (fConst12 + -4.3273899882224502e-13)) + -2.6123081073531499e-10);
	fConst29 = ((fConst0 * (fConst14 + -2.08816784713571e-11)) + -2.2157896733672402e-11);
	fConst30 = ((fConst0 * (2.0889804323188e-11 - fConst16)) + 2.2164580281252099e-11);
	fConst31 = ((fConst0 * (2.1599346423442701e-28 - fConst18)) + 8.6887543255114101e-26);
	fConst32 = ((fConst0 * (4.0020402423305203e-26 - fConst20)) + -1.7030426647182999e-40);
	fConst33 = ((fConst0 * (fConst22 + -2.08767462535429e-28)) + -8.6861343028353e-26);
	fConst34 = ((fConst0 * (fConst24 + -4.0008334598859102e-26)) + 1.70252912615652e-40);
	fConst35 = (6.7692910767119105e-33 * fConst0);
	fConst36 = (fConst0 * ((fConst0 * (8.8888681269608693e-30 - fConst35)) + -2.81644355092887e-27));
	fConst37 = (3.31695262757923e-30 * fConst0);
	fConst38 = ((fConst0 * ((fConst0 * (8.2687237414539291e-28 - fConst37)) + -5.0040587809689198e-25)) + -2.12944525410009e-39);
	fConst39 = (1.7285393093812501e-15 * fConst0);
	fConst40 = ((fConst0 * (4.3273899882224502e-13 - fConst39)) + -2.6123081073531499e-10);
	fConst41 = (3.0511973140550299e-14 * fConst0);
	fConst42 = ((fConst0 * (2.08816784713571e-11 - fConst41)) + -2.2157896733672402e-11);
	fConst43 = (3.2240512449931499e-14 * fConst0);
	fConst44 = ((fConst0 * (fConst43 + -2.0889804323188e-11)) + 2.2164580281252099e-11);
	fConst45 = (1.26260023160286e-31 * fConst0);
	fConst46 = ((fConst0 * (fConst45 + -2.1599346423442701e-28)) + 8.6887543255114101e-26);
	fConst47 = (6.1867411348360897e-29 * fConst0);
	fConst48 = ((fConst0 * (fConst47 + -4.0020402423305203e-26)) + -1.7030426647182999e-40);
	fConst49 = (1.19490732083574e-31 * fConst0);
	fConst50 = ((fConst0 * (2.08767462535429e-28 - fConst49)) + -8.6861343028353e-26);
	fConst51 = (5.8550458720781601e-29 * fConst0);
	fConst52 = ((fConst0 * (4.0008334598859102e-26 - fConst51)) + 1.70252912615652e-40);
	fConst53 = (fConst0 * ((fConst0 * (fConst35 + 8.8888681269608693e-30)) + 2.81644355092887e-27));
	fConst54 = ((fConst0 * ((fConst0 * (fConst37 + 8.2687237414539291e-28)) + 5.0040587809689198e-25)) + -2.12944525410009e-39);
	fConst55 = ((fConst0 * (fConst39 + 4.3273899882224502e-13)) + 2.6123081073531499e-10);
	fConst56 = ((fConst0 * (fConst41 + 2.08816784713571e-11)) + 2.2157896733672402e-11);
	fConst57 = ((fConst0 * (-2.0889804323188e-11 - fConst43)) + -2.2164580281252099e-11);
	fConst58 = ((fConst0 * (-2.1599346423442701e-28 - fConst45)) + -8.6887543255114101e-26);
	fConst59 = ((fConst0 * (-4.0020402423305203e-26 - fConst47)) + 1.7030426647182999e-40);
	fConst60 = ((fConst0 * (fConst49 + 2.08767462535429e-28)) + 8.6861343028353e-26);
	fConst61 = ((fConst0 * (fConst51 + 4.0008334598859102e-26)) + -1.70252912615652e-40);
	fConst62 = (2.2773426522999199e-12 * fConst0);
	fConst63 = (fConst62 + 2.90381282711199e-11);
	fConst64 = (2.2317957992539201e-12 * fConst0);
	fConst65 = (-2.84573657056975e-11 - fConst64);
	fConst66 = (6.8320279568997501e-12 * fConst0);
	fConst67 = (-2.90381282711199e-11 - fConst66);
	fConst68 = (6.6953873977617502e-12 * fConst0);
	fConst69 = (fConst68 + 2.84573657056975e-11);
	fConst70 = (fConst66 + -2.90381282711199e-11);
	fConst71 = (2.84573657056975e-11 - fConst68);
	fConst72 = (2.90381282711199e-11 - fConst62);
	fConst73 = (fConst64 + -2.84573657056975e-11);

	sample_rate = 96000;
	smpCl.setup(fSampleRate, sample_rate);
	fSampleRate = sample_rate;
	fConstCl0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	fConstCl1 = std::tan((97.389372261283583 / fConstCl0));
	fConstCl2 = (1.0 / fConstCl1);
	fConstCl3 = (fConstCl2 + 1.0);
	fConstCl4 = (1.0 / (fConstCl1 * fConstCl3));
	fConstCl5 = (1.0 / std::tan((270.1769682087222 / fConstCl0)));
	fConstCl6 = (1.0 / (fConstCl5 + 1.0));
	fConstCl7 = (1.0 - fConstCl5);
	fConstCl8 = (0.0 - fConstCl4);
	fConstCl9 = ((1.0 - fConstCl2) / fConstCl3);

	clear_state_f();
}

void Dsp::init_static(unsigned int sample_rate, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double fSlow0 = (0.0070000000000000062 * (1.0 - double(fVslider0)));
	double fSlow1 = (0.0070000000000000062 * (1.0 - double(fVslider1)));
	for (int i = 0; (i < count); i = (i + 1)) {
		double fTemp0 = double(input0[i]);
		fVec0[0] = fTemp0;
		fRec1[0] = ((fConst5 * fVec0[1]) - (fConst6 * ((fConst7 * fRec1[1]) - (fConst3 * fTemp0))));
		fRec2[0] = (fSlow0 + (0.99299999999999999 * fRec2[1]));
		fRec3[0] = (fSlow1 + (0.99299999999999999 * fRec3[1]));
		double fTemp1 = (((fRec2[0] * (fConst53 + ((fConst54 * fRec2[0]) + 1.08642179352344e-24))) + (fConst0 * (fConst55 + (fRec3[0] * (fConst56 + ((fRec3[0] * (fConst57 + (fRec2[0] * (fConst58 + (fConst59 * fRec2[0]))))) + (fRec2[0] * (fConst60 + (fConst61 * fRec2[0]))))))))) + 2.7714079786039801e-10);
		fRec0[0] = ((0.5 * fRec1[0]) - ((((fRec0[1] * (((fRec2[0] * (fConst9 + ((fConst11 * fRec2[0]) + 3.2592653805703199e-24))) + (fConst0 * (fConst13 + (fRec3[0] * (fConst15 + ((fRec3[0] * (fConst17 + (fRec2[0] * (fConst19 + (fConst21 * fRec2[0]))))) + (fRec2[0] * (fConst23 + (fConst25 * fRec2[0]))))))))) + 8.3142239358119399e-10)) + (fRec0[2] * (((fRec2[0] * (fConst26 + ((fConst27 * fRec2[0]) + 3.2592653805703199e-24))) + (fConst0 * (fConst28 + (fRec3[0] * (fConst29 + ((fRec3[0] * (fConst30 + (fRec2[0] * (fConst31 + (fConst32 * fRec2[0]))))) + (fRec2[0] * (fConst33 + (fConst34 * fRec2[0]))))))))) + 8.3142239358119399e-10))) + (fRec0[3] * (((fRec2[0] * (fConst36 + ((fConst38 * fRec2[0]) + 1.08642179352344e-24))) + (fConst0 * (fConst40 + (fRec3[0] * (fConst42 + ((fRec3[0] * (fConst44 + (fRec2[0] * (fConst46 + (fConst48 * fRec2[0]))))) + (fRec2[0] * (fConst50 + (fConst52 * fRec2[0]))))))))) + 2.7714079786039801e-10))) / fTemp1));
		double fTemp2 = (2.1870023420520399e-12 * fRec2[0]);
		double fTemp3 = (4.4793457201878903e-14 * fRec2[0]);
		double fTemp4 = (1.3438037160563701e-13 * fRec2[0]);
		double fTemp5 = (6.5610070261561101e-12 * fRec2[0]);
		output0[i] = FAUSTFLOAT((fConst1 * (((((fRec0[0] * (fConst63 + ((fConst0 * (fRec3[0] * ((fTemp2 + (fRec3[0] * (fTemp3 + -4.57076093896724e-14))) + -2.2316350429102402e-12))) + (fConst65 * fRec2[0])))) + (fRec0[1] * (fConst67 + ((fConst0 * (fRec3[0] * (((fRec3[0] * ((0.0 - fTemp4) + 1.3712282816901699e-13)) - fTemp5) + 6.6949051287307302e-12))) + (fConst69 * fRec2[0]))))) + (fRec0[2] * (fConst70 + ((fConst0 * (fRec3[0] * ((fTemp5 + (fRec3[0] * (fTemp4 + -1.3712282816901699e-13))) + -6.6949051287307302e-12))) + (fConst71 * fRec2[0]))))) + (fRec0[3] * (fConst72 + ((fConst0 * (fRec3[0] * (((fRec3[0] * ((0.0 - fTemp3) + 4.57076093896724e-14)) - fTemp2) + 2.2316350429102402e-12))) + (fConst73 * fRec2[0]))))) / fTemp1)));
		fVec0[1] = fVec0[0];
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
		double fTemp0 = double(bufCl[i]);
		fVecCl0[0] = fTemp0;
		fRecCl7[0] = ((0.93028479253239138 * (fTemp0 + fVecCl0[1])) - (0.86056958506478287 * fRecCl7[1]));
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
	reg.registerFloatVar("fuzzfacerm.Fuzz",N_("Fuzz"),"S","",&fVslider1, 0.5, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("fuzzfacerm.Level",N_("Level"),"S","",&fVslider0, 0.5, 0.0, 1.0, 0.01, 0);
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
