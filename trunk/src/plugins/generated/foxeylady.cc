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
	FAUSTFLOAT fVslider0;
	double fRec0[2];
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	double fConst4;
	double fConst5;
	double fConst6;
	FAUSTFLOAT fVslider1;
	double fRec1[2];
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
	double fConst35;
	double fConst36;
	double fConst37;
	double fConst38;
	double fConst39;
	double fRec2[7];
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


	gx_resample::FixedRateResampler smpCl;
	double fConstCl0;
	double fConstCl1;
	double fConstCl2;
	double fConstCl3;
	double fVecCl0[2];
	double fRecCl7[2];
	double fRecCl6[3];
	double fConstCl4;
	double fConstCl5;
	double fConstCl6;
	double fRecCl8[2];
	double fRecCl5[3];
	double fConstCl7;
	double fConstCl8;
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec0[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec1[l1] = 0.0;
	for (int l2 = 0; l2 < 7; l2 = l2 + 1) fRec2[l2] = 0.0;

	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fVecCl0[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRecCl7[l1] = 0.0;
	for (int l2 = 0; l2 < 3; l2 = l2 + 1) fRecCl6[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRecCl8[l3] = 0.0;
	for (int l4 = 0; l4 < 3; l4 = l4 + 1) fRecCl5[l4] = 0.0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fRecCl4[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fRecCl3[l6] = 0.0;
	for (int l7 = 0; l7 < 3; l7 = l7 + 1) fRecCl2[l7] = 0.0;
	for (int l8 = 0; l8 < 2; l8 = l8 + 1) fRecCl9[l8] = 0.0;
	for (int l9 = 0; l9 < 3; l9 = l9 + 1) fRecCl1[l9] = 0.0;
	for (int l10 = 0; l10 < 2; l10 = l10 + 1) fRecCl0[l10] = 0.0;

}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = 4.59387215604116e-29 * fConst0;
	fConst2 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (-4.36933720361044e-25 - fConst1) + -8.96539812308464e-22) + -3.5938048928126e-19) + -4.96738293767392e-17) + -2.0568206880379e-15;
	fConst3 = 4.57704216569471e-29 * fConst0;
	fConst4 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst3 + 4.12221097685163e-25) + 2.55877854891379e-22) + -9.9587457844786e-19) + -4.94708666311112e-16) + -7.32065571555064e-14;
	fConst5 = 5.24588897595767e-29 * fConst0;
	fConst6 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst5 + 7.02844574269719e-25) + 2.89396306244108e-21) + 3.61888994332083e-18) + 1.29693461432975e-15) + 1.71281273151154e-13);
	fConst7 = 3.28344197367049e-28 * fConst0;
	fConst8 = fConst0 * (fConst0 * (fConst0 * (1.8701619702637e-23 - fConst7) + -2.16157324062859e-19) + 4.33524374895714e-17) + -5.90848481409701e-16;
	fConst9 = 6.42669378638762e-27 * fConst0;
	fConst10 = fConst0 * (fConst0 * (fConst0 * (fConst9 + -2.86240593005591e-23) + 1.79551930386446e-19) + -3.55668379874028e-17) + 4.84302033942378e-16;
	fConst11 = 6.42669378638762e-29 * fConst0;
	fConst12 = fConst0 * (fConst0 * (fConst0 * (fConst11 + -2.86240593005591e-25) + 1.79551930386446e-21) + -3.55668379874028e-19) + 4.84302033942378e-18;
	fConst13 = 3.28344197367049e-30 * fConst0;
	fConst14 = fConst0 * (fConst0 * (fConst0 * (1.8701619702637e-25 - fConst13) + -2.16157324062859e-21) + 4.33524374895714e-19) + -5.90848481409701e-18;
	fConst15 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (4.36933720361044e-25 - fConst1) + -8.96539812308464e-22) + 3.5938048928126e-19) + -4.96738293767392e-17) + 2.0568206880379e-15;
	fConst16 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst3 + -4.12221097685163e-25) + 2.55877854891379e-22) + 9.9587457844786e-19) + -4.94708666311112e-16) + 7.32065571555064e-14;
	fConst17 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst5 + -7.02844574269719e-25) + 2.89396306244108e-21) + -3.61888994332083e-18) + 1.29693461432975e-15) + -1.71281273151154e-13);
	fConst18 = 2.7563232936247e-28 * fConst0;
	fConst19 = mydsp_faustpower2_f(fConst0);
	fConst20 = fConst0 * (fConst19 * (fConst0 * (fConst18 + -1.74773488144418e-24) + 1.79307962461693e-21) + -9.93476587534785e-17) + 8.22728275215159e-15;
	fConst21 = 2.74622529941683e-28 * fConst0;
	fConst22 = fConst0 * (fConst19 * (fConst0 * (1.64888439074065e-24 - fConst21) + -5.11755709782759e-22) + -9.89417332622223e-16) + 2.92826228622026e-13;
	fConst23 = 3.1475333855746e-28 * fConst0;
	fConst24 = fConst0 * (fConst0 * (fConst19 * (fConst0 * (2.81137829707888e-24 - fConst23) + -5.78792612488216e-21) + 2.5938692286595e-15) + -6.85125092604618e-13);
	fConst25 = 6.89080823406175e-28 * fConst0;
	fConst26 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (2.18466860180522e-24 - fConst25) + 8.96539812308464e-22) + -1.07814146784378e-18) + 4.96738293767392e-17) + 1.02841034401895e-14;
	fConst27 = 6.86556324854206e-28 * fConst0;
	fConst28 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst27 + -2.06110548842582e-24) + -2.55877854891379e-22) + -2.98762373534358e-18) + 4.94708666311112e-16) + 3.66032785777532e-13;
	fConst29 = 7.8688334639365e-28 * fConst0;
	fConst30 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst29 + -3.51422287134859e-24) + -2.89396306244108e-21) + 1.08566698299625e-17) + -1.29693461432975e-15) + -8.56406365755772e-13);
	fConst31 = fConst19 * (9.18774431208233e-28 * fConst19 + -3.58615924923386e-21) + 1.98695317506957e-16;
	fConst32 = fConst19 * (1.02351141956552e-21 - 9.15408433138942e-28 * fConst19) + 1.97883466524445e-15;
	fConst33 = fConst19 * (fConst19 * (1.15758522497643e-20 - 1.04917779519153e-27 * fConst19) + -5.18773845731899e-15);
	fConst34 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (-2.18466860180522e-24 - fConst25) + 8.96539812308464e-22) + 1.07814146784378e-18) + 4.96738293767392e-17) + -1.02841034401895e-14;
	fConst35 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst27 + 2.06110548842582e-24) + -2.55877854891379e-22) + 2.98762373534358e-18) + 4.94708666311112e-16) + -3.66032785777532e-13;
	fConst36 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst29 + 3.51422287134859e-24) + -2.89396306244108e-21) + -1.08566698299625e-17) + -1.29693461432975e-15) + 8.56406365755772e-13);
	fConst37 = fConst0 * (fConst19 * (fConst0 * (fConst18 + 1.74773488144418e-24) + 1.79307962461693e-21) + -9.93476587534785e-17) + -8.22728275215159e-15;
	fConst38 = fConst0 * (fConst19 * (fConst0 * (-1.64888439074065e-24 - fConst21) + -5.11755709782759e-22) + -9.89417332622223e-16) + -2.92826228622026e-13;
	fConst39 = fConst0 * (fConst0 * (fConst19 * (fConst0 * (-2.81137829707888e-24 - fConst23) + -5.78792612488216e-21) + 2.5938692286595e-15) + 6.85125092604618e-13);
	fConst40 = 1.97006518420229e-27 * fConst0;
	fConst41 = fConst19 * (fConst0 * (fConst40 + -7.48064788105479e-23) + 4.32314648125718e-19) + -1.1816969628194e-15;
	fConst42 = 3.85601627183257e-26 * fConst0;
	fConst43 = fConst19 * (fConst0 * (1.14496237202237e-22 - fConst42) + -3.59103860772892e-19) + 9.68604067884756e-16;
	fConst44 = 3.85601627183257e-28 * fConst0;
	fConst45 = fConst19 * (fConst0 * (1.14496237202237e-24 - fConst44) + -3.59103860772892e-21) + 9.68604067884756e-18;
	fConst46 = 1.97006518420229e-29 * fConst0;
	fConst47 = fConst19 * (fConst0 * (fConst46 + -7.48064788105479e-25) + 4.32314648125718e-21) + -1.1816969628194e-17;
	fConst48 = 4.92516296050573e-27 * fConst0;
	fConst49 = fConst0 * (fConst0 * (fConst0 * (9.35080985131849e-23 - fConst48) + 2.16157324062859e-19) + -1.30057312468714e-16) + 5.90848481409701e-16;
	fConst50 = 9.64004067958143e-26 * fConst0;
	fConst51 = fConst0 * (fConst0 * (fConst0 * (fConst50 + -1.43120296502796e-22) + -1.79551930386446e-19) + 1.06700513962208e-16) + -4.84302033942378e-16;
	fConst52 = 9.64004067958143e-28 * fConst0;
	fConst53 = fConst0 * (fConst0 * (fConst0 * (fConst52 + -1.43120296502796e-24) + -1.79551930386446e-21) + 1.06700513962208e-18) + -4.84302033942378e-18;
	fConst54 = 4.92516296050573e-29 * fConst0;
	fConst55 = fConst0 * (fConst0 * (fConst0 * (9.35080985131849e-25 - fConst54) + 2.16157324062859e-21) + -1.30057312468714e-18) + 5.90848481409701e-18;
	fConst56 = fConst19 * (6.56688394734098e-27 * fConst19 + -8.64629296251435e-19) + 2.3633939256388e-15;
	fConst57 = fConst19 * (7.18207721545784e-19 - 1.28533875727752e-25 * fConst19) + -1.93720813576951e-15;
	fConst58 = fConst19 * (7.18207721545784e-21 - 1.28533875727752e-27 * fConst19) + -1.93720813576951e-17;
	fConst59 = fConst19 * (6.56688394734098e-29 * fConst19 + -8.64629296251435e-21) + 2.3633939256388e-17;
	fConst60 = fConst0 * (fConst0 * (fConst0 * (-9.35080985131849e-23 - fConst48) + 2.16157324062859e-19) + 1.30057312468714e-16) + 5.90848481409701e-16;
	fConst61 = fConst0 * (fConst0 * (fConst0 * (fConst50 + 1.43120296502796e-22) + -1.79551930386446e-19) + -1.06700513962208e-16) + -4.84302033942378e-16;
	fConst62 = fConst0 * (fConst0 * (fConst0 * (fConst52 + 1.43120296502796e-24) + -1.79551930386446e-21) + -1.06700513962208e-18) + -4.84302033942378e-18;
	fConst63 = fConst0 * (fConst0 * (fConst0 * (-9.35080985131849e-25 - fConst54) + 2.16157324062859e-21) + 1.30057312468714e-18) + 5.90848481409701e-18;
	fConst64 = fConst19 * (fConst0 * (fConst40 + 7.48064788105479e-23) + 4.32314648125718e-19) + -1.1816969628194e-15;
	fConst65 = fConst19 * (fConst0 * (-1.14496237202237e-22 - fConst42) + -3.59103860772892e-19) + 9.68604067884756e-16;
	fConst66 = fConst19 * (fConst0 * (-1.14496237202237e-24 - fConst44) + -3.59103860772892e-21) + 9.68604067884756e-18;
	fConst67 = fConst19 * (fConst0 * (fConst46 + 7.48064788105479e-25) + 4.32314648125718e-21) + -1.1816969628194e-17;
	fConst68 = fConst0 * (fConst0 * (fConst0 * (-1.8701619702637e-23 - fConst7) + -2.16157324062859e-19) + -4.33524374895714e-17) + -5.90848481409701e-16;
	fConst69 = fConst0 * (fConst0 * (fConst0 * (fConst9 + 2.86240593005591e-23) + 1.79551930386446e-19) + 3.55668379874028e-17) + 4.84302033942378e-16;
	fConst70 = fConst0 * (fConst0 * (fConst0 * (fConst11 + 2.86240593005591e-25) + 1.79551930386446e-21) + 3.55668379874028e-19) + 4.84302033942378e-18;
	fConst71 = fConst0 * (fConst0 * (fConst0 * (-1.8701619702637e-25 - fConst13) + -2.16157324062859e-21) + -4.33524374895714e-19) + -5.90848481409701e-18;

	sample_rate = 96000;
	smpCl.setup(fSampleRate, sample_rate);
	fSampleRate = sample_rate;
	fConstCl0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	fConstCl1 = std::tan(97.38937226128358 / fConstCl0);
	fConstCl2 = 1.0 / fConstCl1;
	fConstCl3 = 1.0 - fConstCl2;
	fConstCl4 = 1.0 / std::tan(270.1769682087222 / fConstCl0);
	fConstCl5 = 1.0 - fConstCl4;
	fConstCl6 = 1.0 / (fConstCl4 + 1.0);
	fConstCl7 = 0.025 / fConstCl1;
	fConstCl8 = 1.0 / (fConstCl2 + 1.0);

	clear_state_f();
}

void Dsp::init_static(unsigned int sample_rate, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double fSlow0 = 0.007000000000000006 * (1.0 - double(fVslider0));
	double fSlow1 = 0.007000000000000006 * double(fVslider1);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec0[0] = fSlow0 + 0.993 * fRec0[1];
		double fTemp0 = fConst6 + fRec0[0] * (fConst0 * (fConst4 + fConst2 * fRec0[0]) + -3.1163949818756e-12) + 6.94956080958259e-12;
		fRec1[0] = fSlow1 + 0.993 * fRec1[1];
		fRec2[0] = double(input0[i0]) - (fRec2[1] * (fConst39 + fRec0[0] * (fConst0 * (fConst38 + fConst37 * fRec0[0]) + -1.86983698912536e-11) + 4.16973648574956e-11) + fRec2[2] * (fConst36 + fRec0[0] * (fConst0 * (fConst35 + fConst34 * fRec0[0]) + -4.6745924728134e-11) + 1.04243412143739e-10) + fRec2[3] * (fConst33 + fRec0[0] * (fConst19 * (fConst32 + fConst31 * fRec0[0]) + -6.23278996375121e-11) + 1.38991216191652e-10) + fRec2[4] * (fConst30 + fRec0[0] * (fConst0 * (fConst28 + fConst26 * fRec0[0]) + -4.6745924728134e-11) + 1.04243412143739e-10) + fRec2[5] * (fConst24 + fRec0[0] * (fConst0 * (fConst22 + fConst20 * fRec0[0]) + -1.86983698912536e-11) + 4.16973648574956e-11) + fRec2[6] * (fConst17 + fRec0[0] * (fConst0 * (fConst16 + fConst15 * fRec0[0]) + -3.1163949818756e-12) + 6.94956080958259e-12)) / fTemp0;
		output0[i0] = FAUSTFLOAT(fConst19 * ((fRec2[0] * (fConst71 + fRec0[0] * (fConst70 + fConst69 * fRec1[0]) + fConst68 * fRec1[0]) + fRec2[1] * (fConst67 + fRec0[0] * (fConst66 + fConst65 * fRec1[0]) + fConst64 * fRec1[0]) + fRec2[2] * (fConst63 + fRec0[0] * (fConst62 + fConst61 * fRec1[0]) + fConst60 * fRec1[0]) + fRec2[3] * (fConst59 + fRec0[0] * (fConst58 + fConst57 * fRec1[0]) + fConst56 * fRec1[0]) + fRec2[4] * (fConst55 + fRec0[0] * (fConst53 + fConst51 * fRec1[0]) + fConst49 * fRec1[0]) + fRec2[5] * (fConst47 + fRec0[0] * (fConst45 + fConst43 * fRec1[0]) + fConst41 * fRec1[0]) + fRec2[6] * (fConst14 + fRec0[0] * (fConst12 + fConst10 * fRec1[0]) + fConst8 * fRec1[0])) / fTemp0));
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		for (int j0 = 6; j0 > 0; j0 = j0 - 1) {
			fRec2[j0] = fRec2[j0 - 1];
		}
	}

	FAUSTFLOAT bufCl[smpCl.max_out_count(count)];
	int ReCount = smpCl.up(count, output0, bufCl);
	for (int i0 = 0; i0 < ReCount; i0 = i0 + 1) {
		double fTemp0 = double(bufCl[i0]);
		fVecCl0[0] = fTemp0;
		fRecCl7[0] = 0.9302847925323914 * (fTemp0 + fVecCl0[1]) - 0.8605695850647829 * fRecCl7[1];
		fRecCl6[0] = fRecCl7[0] - (1.8405051250752198 * fRecCl6[1] + 0.8612942439318627 * fRecCl6[2]);
		fRecCl8[0] = fConstCl6 * (0.027 * (fRecCl5[1] + fRecCl5[2]) - fConstCl5 * fRecCl8[1]);
		fRecCl5[0] = Ftrany(TRANY_TABLE_7199P_68k, 0.9254498422517706 * (fRecCl6[0] + fRecCl6[2]) + fRecCl8[0] + 1.8508996845035413 * fRecCl6[1] + -3.571981) + -117.70440740740739;
		fRecCl4[0] = fConstCl8 * (fConstCl7 * (fRecCl5[0] - fRecCl5[1]) - fConstCl3 * fRecCl4[1]);
		fRecCl3[0] = 0.9302847925323914 * (fRecCl4[0] + fRecCl4[1]) - 0.8605695850647829 * fRecCl3[1];
		fRecCl2[0] = fRecCl3[0] - (1.8405051250752198 * fRecCl2[1] + 0.8612942439318627 * fRecCl2[2]);
		fRecCl9[0] = fConstCl6 * (0.027 * (fRecCl1[1] + fRecCl1[2]) - fConstCl5 * fRecCl9[1]);
		fRecCl1[0] = Ftrany(TRANY_TABLE_7199P_68k, 0.9254498422517706 * (fRecCl2[0] + fRecCl2[2]) + fRecCl9[0] + 1.8508996845035413 * fRecCl2[1] + -3.571981) + -117.70440740740739;
		fRecCl0[0] = fConstCl8 * (fConstCl7 * (fRecCl1[0] - fRecCl1[1]) - fConstCl3 * fRecCl0[1]);
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
