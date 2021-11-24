// generated from file '../src/plugins/foxeylady.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

#include "trany.h"

namespace pluginlib {
namespace foxeylady {

class Dsp: public PluginDef {
private:
	int fSampleRate;
	double fConst0;
	double fConst1;
	double fConst3;
	FAUSTFLOAT fVslider0;
	double fRec1[2];
	double fConst5;
	double fConst7;
	double fConst9;
	double fConst11;
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
	double fConst24;
	double fConst26;
	double fConst28;
	double fConst29;
	double fConst30;
	double fConst31;
	double fRec0[7];
	double fConst33;
	double fConst35;
	double fConst37;
	FAUSTFLOAT fVslider1;
	double fRec2[2];
	double fConst39;
	double fConst41;
	double fConst43;
	double fConst45;
	double fConst47;
	double fConst49;
	double fConst51;
	double fConst53;
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


	gx_resample::FixedRateResampler smpCl;
	double fConstCl4;
	double fVecCl0[2];
	double fRecCl7[2];
	double fRecCl6[3];
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
	id = "foxeylady";
	name = N_("Foxey Lady");
	groups = 0;
	description = N_("Foxey Lady fuzz pedal simulation"); // description (tooltip)
	category = N_("Fuzz");       // category
	shortname = N_("Foxey Lady");     // shortname
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
	for (int l1 = 0; (l1 < 7); l1 = (l1 + 1)) fRec0[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec2[l2] = 0.0;

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
	double fConst2 = (3.1475333855746001e-28 * fConst0);
	fConst3 = (fConst0 * ((fConst0 * ((fConst1 * ((fConst0 * (-2.8113782970788801e-24 - fConst2)) + -5.7879261248821598e-21)) + 2.5938692286594999e-15)) + 6.8512509260461802e-13));
	double fConst4 = (2.7462252994168298e-28 * fConst0);
	fConst5 = ((fConst0 * ((fConst1 * ((fConst0 * (-1.64888439074065e-24 - fConst4)) + -5.1175570978275895e-22)) + -9.8941733262222305e-16)) + -2.9282622862202601e-13);
	double fConst6 = (2.7563232936246999e-28 * fConst0);
	fConst7 = ((fConst0 * ((fConst1 * ((fConst0 * (fConst6 + 1.7477348814441801e-24)) + 1.7930796246169299e-21)) + -9.9347658753478499e-17)) + -8.2272827521515899e-15);
	double fConst8 = (7.8688334639365003e-28 * fConst0);
	fConst9 = (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst8 + 3.5142228713485898e-24)) + -2.8939630624410799e-21)) + -1.08566698299625e-17)) + -1.29693461432975e-15)) + 8.5640636575577199e-13));
	double fConst10 = (6.8655632485420604e-28 * fConst0);
	fConst11 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst10 + 2.0611054884258201e-24)) + -2.5587785489137901e-22)) + 2.9876237353435801e-18)) + 4.9470866631111202e-16)) + -3.6603278577753198e-13);
	double fConst12 = (6.8908082340617503e-28 * fConst0);
	fConst13 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (-2.1846686018052201e-24 - fConst12)) + 8.96539812308464e-22)) + 1.07814146784378e-18)) + 4.96738293767392e-17)) + -1.02841034401895e-14);
	fConst14 = (fConst1 * ((fConst1 * (1.15758522497643e-20 - (1.0491777951915301e-27 * fConst1))) + -5.1877384573189904e-15));
	fConst15 = ((fConst1 * (1.02351141956552e-21 - (9.1540843313894192e-28 * fConst1))) + 1.97883466524445e-15);
	fConst16 = ((fConst1 * ((9.1877443120823307e-28 * fConst1) + -3.5861592492338598e-21)) + 1.98695317506957e-16);
	fConst17 = (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst8 + -3.5142228713485898e-24)) + -2.8939630624410799e-21)) + 1.08566698299625e-17)) + -1.29693461432975e-15)) + -8.5640636575577199e-13));
	fConst18 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst10 + -2.0611054884258201e-24)) + -2.5587785489137901e-22)) + -2.9876237353435801e-18)) + 4.9470866631111202e-16)) + 3.6603278577753198e-13);
	fConst19 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (2.1846686018052201e-24 - fConst12)) + 8.96539812308464e-22)) + -1.07814146784378e-18)) + 4.96738293767392e-17)) + 1.02841034401895e-14);
	fConst20 = (fConst0 * ((fConst0 * ((fConst1 * ((fConst0 * (2.8113782970788801e-24 - fConst2)) + -5.7879261248821598e-21)) + 2.5938692286594999e-15)) + -6.8512509260461802e-13));
	fConst21 = ((fConst0 * ((fConst1 * ((fConst0 * (1.64888439074065e-24 - fConst4)) + -5.1175570978275895e-22)) + -9.8941733262222305e-16)) + 2.9282622862202601e-13);
	fConst22 = ((fConst0 * ((fConst1 * ((fConst0 * (fConst6 + -1.7477348814441801e-24)) + 1.7930796246169299e-21)) + -9.9347658753478499e-17)) + 8.2272827521515899e-15);
	double fConst23 = (5.2458889759576695e-29 * fConst0);
	fConst24 = (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst23 + -7.0284457426971902e-25)) + 2.8939630624410799e-21)) + -3.6188899433208304e-18)) + 1.29693461432975e-15)) + -1.71281273151154e-13));
	double fConst25 = (4.5770421656947102e-29 * fConst0);
	fConst26 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst25 + -4.1222109768516301e-25)) + 2.5587785489137901e-22)) + 9.9587457844785995e-19)) + -4.9470866631111202e-16)) + 7.3206557155506402e-14);
	double fConst27 = (4.5938721560411602e-29 * fConst0);
	fConst28 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (4.3693372036104401e-25 - fConst27)) + -8.96539812308464e-22)) + 3.5938048928125998e-19)) + -4.96738293767392e-17)) + 2.0568206880378998e-15);
	fConst29 = (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst23 + 7.0284457426971902e-25)) + 2.8939630624410799e-21)) + 3.6188899433208304e-18)) + 1.29693461432975e-15)) + 1.71281273151154e-13));
	fConst30 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst25 + 4.1222109768516301e-25)) + 2.5587785489137901e-22)) + -9.9587457844785995e-19)) + -4.9470866631111202e-16)) + -7.3206557155506402e-14);
	fConst31 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (-4.3693372036104401e-25 - fConst27)) + -8.96539812308464e-22)) + -3.5938048928125998e-19)) + -4.96738293767392e-17)) + -2.0568206880378998e-15);
	double fConst32 = (3.2834419736704901e-30 * fConst0);
	fConst33 = ((fConst0 * ((fConst0 * ((fConst0 * (-1.8701619702637e-25 - fConst32)) + -2.1615732406285901e-21)) + -4.3352437489571401e-19)) + -5.90848481409701e-18);
	double fConst34 = (6.4266937863876197e-29 * fConst0);
	fConst35 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst34 + 2.8624059300559101e-25)) + 1.79551930386446e-21)) + 3.5566837987402799e-19)) + 4.8430203394237801e-18);
	double fConst36 = (6.4266937863876199e-27 * fConst0);
	fConst37 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst36 + 2.8624059300559097e-23)) + 1.79551930386446e-19)) + 3.5566837987402801e-17)) + 4.8430203394237796e-16);
	double fConst38 = (3.2834419736704899e-28 * fConst0);
	fConst39 = ((fConst0 * ((fConst0 * ((fConst0 * (-1.8701619702637001e-23 - fConst38)) + -2.16157324062859e-19)) + -4.3352437489571397e-17)) + -5.9084848140970105e-16);
	double fConst40 = (1.9700651842022901e-29 * fConst0);
	fConst41 = ((fConst1 * ((fConst0 * (fConst40 + 7.48064788105479e-25)) + 4.3231464812571802e-21)) + -1.1816969628194e-17);
	double fConst42 = (3.85601627183257e-28 * fConst0);
	fConst43 = ((fConst1 * ((fConst0 * (-1.1449623720223699e-24 - fConst42)) + -3.59103860772892e-21)) + 9.6860406788475602e-18);
	double fConst44 = (3.8560162718325702e-26 * fConst0);
	fConst45 = ((fConst1 * ((fConst0 * (-1.14496237202237e-22 - fConst44)) + -3.59103860772892e-19)) + 9.6860406788475592e-16);
	double fConst46 = (1.9700651842022901e-27 * fConst0);
	fConst47 = ((fConst1 * ((fConst0 * (fConst46 + 7.4806478810547898e-23)) + 4.32314648125718e-19)) + -1.1816969628193999e-15);
	double fConst48 = (4.9251629605057299e-29 * fConst0);
	fConst49 = ((fConst0 * ((fConst0 * ((fConst0 * (-9.3508098513184898e-25 - fConst48)) + 2.1615732406285901e-21)) + 1.3005731246871401e-18)) + 5.90848481409701e-18);
	double fConst50 = (9.6400406795814309e-28 * fConst0);
	fConst51 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst50 + 1.4312029650279601e-24)) + -1.79551930386446e-21)) + -1.06700513962208e-18)) + -4.8430203394237801e-18);
	double fConst52 = (9.6400406795814301e-26 * fConst0);
	fConst53 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst52 + 1.43120296502796e-22)) + -1.79551930386446e-19)) + -1.06700513962208e-16)) + -4.8430203394237796e-16);
	double fConst54 = (4.9251629605057298e-27 * fConst0);
	fConst55 = ((fConst0 * ((fConst0 * ((fConst0 * (-9.3508098513184898e-23 - fConst54)) + 2.16157324062859e-19)) + 1.30057312468714e-16)) + 5.9084848140970105e-16);
	fConst56 = ((fConst1 * ((6.5668839473409795e-29 * fConst1) + -8.6462929625143499e-21)) + 2.3633939256388e-17);
	fConst57 = ((fConst1 * (7.1820772154578399e-21 - (1.28533875727752e-27 * fConst1))) + -1.9372081357695099e-17);
	fConst58 = ((fConst1 * (7.18207721545784e-19 - (1.28533875727752e-25 * fConst1))) + -1.9372081357695099e-15);
	fConst59 = ((fConst1 * ((6.5668839473409803e-27 * fConst1) + -8.6462929625143505e-19)) + 2.3633939256387999e-15);
	fConst60 = ((fConst0 * ((fConst0 * ((fConst0 * (9.3508098513184898e-25 - fConst48)) + 2.1615732406285901e-21)) + -1.3005731246871401e-18)) + 5.90848481409701e-18);
	fConst61 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst50 + -1.4312029650279601e-24)) + -1.79551930386446e-21)) + 1.06700513962208e-18)) + -4.8430203394237801e-18);
	fConst62 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst52 + -1.43120296502796e-22)) + -1.79551930386446e-19)) + 1.06700513962208e-16)) + -4.8430203394237796e-16);
	fConst63 = ((fConst0 * ((fConst0 * ((fConst0 * (9.3508098513184898e-23 - fConst54)) + 2.16157324062859e-19)) + -1.30057312468714e-16)) + 5.9084848140970105e-16);
	fConst64 = ((fConst1 * ((fConst0 * (fConst40 + -7.48064788105479e-25)) + 4.3231464812571802e-21)) + -1.1816969628194e-17);
	fConst65 = ((fConst1 * ((fConst0 * (1.1449623720223699e-24 - fConst42)) + -3.59103860772892e-21)) + 9.6860406788475602e-18);
	fConst66 = ((fConst1 * ((fConst0 * (1.14496237202237e-22 - fConst44)) + -3.59103860772892e-19)) + 9.6860406788475592e-16);
	fConst67 = ((fConst1 * ((fConst0 * (fConst46 + -7.4806478810547898e-23)) + 4.32314648125718e-19)) + -1.1816969628193999e-15);
	fConst68 = ((fConst0 * ((fConst0 * ((fConst0 * (1.8701619702637e-25 - fConst32)) + -2.1615732406285901e-21)) + 4.3352437489571401e-19)) + -5.90848481409701e-18);
	fConst69 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst34 + -2.8624059300559101e-25)) + 1.79551930386446e-21)) + -3.5566837987402799e-19)) + 4.8430203394237801e-18);
	fConst70 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst36 + -2.8624059300559097e-23)) + 1.79551930386446e-19)) + -3.5566837987402801e-17)) + 4.8430203394237796e-16);
	fConst71 = ((fConst0 * ((fConst0 * ((fConst0 * (1.8701619702637001e-23 - fConst38)) + -2.16157324062859e-19)) + 4.3352437489571397e-17)) + -5.9084848140970105e-16);

	sample_rate = 96000;
	smpCl.setup(fSampleRate, sample_rate);
	fSampleRate = sample_rate;
	double fConstCl0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	double fConstCl1 = std::tan((97.389372261283583 / fConstCl0));
	double fConstCl2 = (1.0 / fConstCl1);
	double fConstCl3 = (fConstCl2 + 1.0);
	fConstCl4 = (1.0 / (fConstCl1 * fConstCl3));
	double fConstCl5 = (1.0 / std::tan((270.1769682087222 / fConstCl0)));
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
	double fSlow1 = (0.0070000000000000062 * double(fVslider1));
	for (int i0 = 0; (i0 < count); i0 = (i0 + 1)) {
		fRec1[0] = (fSlow0 + (0.99299999999999999 * fRec1[1]));
		double fTemp0 = (fConst29 + ((fRec1[0] * ((fConst0 * (fConst30 + (fConst31 * fRec1[0]))) + -3.1163949818755998e-12)) + 6.9495608095825903e-12));
		fRec0[0] = (double(input0[i0]) - (((((((fRec0[1] * (fConst3 + ((fRec1[0] * ((fConst0 * (fConst5 + (fConst7 * fRec1[0]))) + -1.8698369891253599e-11)) + 4.1697364857495598e-11))) + (fRec0[2] * (fConst9 + ((fRec1[0] * ((fConst0 * (fConst11 + (fConst13 * fRec1[0]))) + -4.6745924728133999e-11)) + 1.0424341214373901e-10)))) + (fRec0[3] * (fConst14 + ((fRec1[0] * ((fConst1 * (fConst15 + (fConst16 * fRec1[0]))) + -6.2327899637512106e-11)) + 1.3899121619165199e-10)))) + (fRec0[4] * (fConst17 + ((fRec1[0] * ((fConst0 * (fConst18 + (fConst19 * fRec1[0]))) + -4.6745924728133999e-11)) + 1.0424341214373901e-10)))) + (fRec0[5] * (fConst20 + ((fRec1[0] * ((fConst0 * (fConst21 + (fConst22 * fRec1[0]))) + -1.8698369891253599e-11)) + 4.1697364857495598e-11)))) + (fRec0[6] * (fConst24 + ((fRec1[0] * ((fConst0 * (fConst26 + (fConst28 * fRec1[0]))) + -3.1163949818755998e-12)) + 6.9495608095825903e-12)))) / fTemp0));
		fRec2[0] = (fSlow1 + (0.99299999999999999 * fRec2[1]));
		output0[i0] = FAUSTFLOAT((fConst1 * ((((((((fRec0[0] * (fConst33 + ((fRec1[0] * (fConst35 + (fConst37 * fRec2[0]))) + (fConst39 * fRec2[0])))) + (fRec0[1] * (fConst41 + ((fRec1[0] * (fConst43 + (fConst45 * fRec2[0]))) + (fConst47 * fRec2[0]))))) + (fRec0[2] * (fConst49 + ((fRec1[0] * (fConst51 + (fConst53 * fRec2[0]))) + (fConst55 * fRec2[0]))))) + (fRec0[3] * (fConst56 + ((fRec1[0] * (fConst57 + (fConst58 * fRec2[0]))) + (fConst59 * fRec2[0]))))) + (fRec0[4] * (fConst60 + ((fRec1[0] * (fConst61 + (fConst62 * fRec2[0]))) + (fConst63 * fRec2[0]))))) + (fRec0[5] * (fConst64 + ((fRec1[0] * (fConst65 + (fConst66 * fRec2[0]))) + (fConst67 * fRec2[0]))))) + (fRec0[6] * (fConst68 + ((fRec1[0] * (fConst69 + (fConst70 * fRec2[0]))) + (fConst71 * fRec2[0]))))) / fTemp0)));
		fRec1[1] = fRec1[0];
		for (int j0 = 6; (j0 > 0); j0 = (j0 - 1)) {
			fRec0[j0] = fRec0[(j0 - 1)];
		}
		fRec2[1] = fRec2[0];
	}

	FAUSTFLOAT bufCl[smpCl.max_out_count(count)];
	int ReCount = smpCl.up(count, output0, bufCl);
	for (int i0 = 0; (i0 < ReCount); i0 = (i0 + 1)) {
		double fTemp0 = double(bufCl[i0]);
		fVecCl0[0] = fTemp0;
		fRecCl7[0] = ((0.93028479253239138 * (fTemp0 + fVecCl0[1])) - (0.86056958506478287 * fRecCl7[1]));
		fRecCl6[0] = (fRecCl7[0] - ((1.8405051250752198 * fRecCl6[1]) + (0.86129424393186271 * fRecCl6[2])));
		fRecCl8[0] = (fConstCl6 * ((0.027 * (fRecCl5[1] + fRecCl5[2])) - (fConstCl7 * fRecCl8[1])));
		fRecCl5[0] = (double(Ftrany(int(TRANY_TABLE_7199P_68k), double((((0.92544984225177063 * (fRecCl6[0] + fRecCl6[2])) + (fRecCl8[0] + (1.8508996845035413 * fRecCl6[1]))) + -3.5719810000000001)))) + -117.70440740740739);
		fRecCl4[0] = ((0.025000000000000001 * ((fConstCl4 * fRecCl5[0]) + (fConstCl8 * fRecCl5[1]))) - (fConstCl9 * fRecCl4[1]));
		fRecCl3[0] = ((0.93028479253239138 * (fRecCl4[0] + fRecCl4[1])) - (0.86056958506478287 * fRecCl3[1]));
		fRecCl2[0] = (fRecCl3[0] - ((1.8405051250752198 * fRecCl2[1]) + (0.86129424393186271 * fRecCl2[2])));
		fRecCl9[0] = (fConstCl6 * ((0.027 * (fRecCl1[1] + fRecCl1[2])) - (fConstCl7 * fRecCl9[1])));
		fRecCl1[0] = (double(Ftrany(int(TRANY_TABLE_7199P_68k), double((((0.92544984225177063 * (fRecCl2[0] + fRecCl2[2])) + (fRecCl9[0] + (1.8508996845035413 * fRecCl2[1]))) + -3.5719810000000001)))) + -117.70440740740739);
		fRecCl0[0] = ((0.025000000000000001 * ((fConstCl4 * fRecCl1[0]) + (fConstCl8 * fRecCl1[1]))) - (fConstCl9 * fRecCl0[1]));
		bufCl[i0] = FAUSTFLOAT(fRecCl0[0]);
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
	reg.registerFloatVar("foxeylady.Fuzz",N_("Fuzz"),"S","",&fVslider0, 0.5, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("foxeylady.Level",N_("Level"),"S","",&fVslider1, 0.5, 0.0, 1.0, 0.01, 0);
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
                        <property name=\"var_id\">foxeylady.Fuzz</property>\n\
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
                        <property name=\"var_id\">foxeylady.Level</property>\n\
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
                <property name=\"var_id\">foxeylady.Fuzz</property>\n\
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
                <property name=\"label\" translatable=\"yes\">Fuzz</property>\n\
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
#define PARAM(p) ("foxeylady" "." p)

b.openHorizontalhideBox("");
    b.create_master_slider(PARAM("Fuzz"), "Fuzz");
b.closeBox();
b.openHorizontalBox("");

    b.create_small_rackknobr(PARAM("Level"), "Level");

    b.create_small_rackknobr(PARAM("Fuzz"), "Fuzz");
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

} // end namespace foxeylady
} // end namespace pluginlib
