// generated from file '../src/plugins/susta.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

#include "trany.h"

namespace pluginlib {
namespace susta {

class Dsp: public PluginDef {
private:
	int fSampleRate;
	FAUSTFLOAT fVslider0;
	double fRec0[2];
	double fConst3;
	double fConst5;
	double fConst7;
	double fConst9;
	double fConst12;
	double fConst14;
	double fConst16;
	double fConst18;
	double fConst20;
	double fConst21;
	double fConst22;
	double fConst23;
	double fConst24;
	double fConst25;
	double fConst27;
	double fConst29;
	double fConst31;
	double fConst33;
	double fConst36;
	double fConst38;
	double fConst40;
	double fConst42;
	double fConst44;
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
	double fRec1[6];
	double fConst59;
	double fConst61;
	double fConst63;
	double fConst65;
	double fConst67;
	double fConst69;
	double fConst71;
	double fConst73;
	double fConst74;
	double fConst75;
	double fConst76;
	double fConst77;
	double fConst78;
	double fConst79;
	double fConst80;
	double fConst81;
	double fConst82;
	double fConst83;
	double fConst84;
	double fConst85;
	double fConst86;


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

	FAUSTFLOAT 	fsliderV0;
	double 	fRecV0[2];
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
	id = "susta";
	name = N_("Sustainer");
	groups = 0;
	description = N_("Sustainer"); // description (tooltip)
	category = N_("Fuzz");       // category
	shortname = N_("Sustainer");     // shortname
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
	for (int l1 = 0; l1 < 6; l1 = l1 + 1) fRec1[l1] = 0.0;

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

	for (int i=0; i<2; i++) fRecV0[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int sample_rate)
{
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = mydsp_faustpower2_f(fConst0);
	double fConst2 = 5.11091507074998e-24 * fConst0;
	fConst3 = (fConst0 * (fConst0 * (fConst2 + 6.98874158230498e-20) + 1.4095256819997e-16) + 1.75646845862514e-15) * fConst1;
	double fConst4 = 5.07545362580621e-24 * fConst0;
	fConst5 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (-7.00613593632107e-20 - fConst4) + -1.47460849525455e-16) + -2.81034919192636e-15) + -1.29152092545966e-14);
	double fConst6 = 9.91377586985301e-24 * fConst0;
	fConst7 = fConst1 * (fConst0 * (fConst0 * (-9.36483991458906e-20 - fConst6) + -1.70486053448624e-16) + -2.12307123308889e-15);
	double fConst8 = 9.84499037599778e-24 * fConst0;
	fConst9 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst8 + 9.42766173980015e-20) + 1.78421312766784e-16) + 3.39775512445924e-15) + 1.56108178903595e-14);
	double fConst10 = 1.03973026841637e-24 * fConst0;
	double fConst11 = 1.58888527196851e-24 * fConst0;
	fConst12 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst11 + 6.14378170525581e-20) + 1.4867852143994e-16) + 4.14135154627774e-15) + 3.80287926742832e-14 + fConst0 * (fConst0 * (fConst0 * (-5.71785438210912e-20 - fConst10) + -1.41224926366503e-16) + -3.77185698680303e-15) + -3.30317585349598e-14);
	double fConst13 = 4.07249439024394e-27 * fConst0;
	fConst14 = fConst0 * (-1.34118849842818e-20 - fConst13) + -1.23525177556824e-15;
	double fConst15 = 3.9514408494262e-27 * fConst0;
	fConst16 = fConst0 * (fConst15 + 1.26300907176988e-20) + -2.68904213585766e-17;
	double fConst17 = 3.9514408494262e-29 * fConst0;
	fConst18 = fConst0 * (fConst17 + 1.26300907176988e-22) + -2.68904213585766e-19;
	double fConst19 = 4.07249439024394e-29 * fConst0;
	fConst20 = fConst0 * (-1.34118849842818e-22 - fConst19) + -1.23525177556824e-17;
	fConst21 = fConst1 * (fConst0 * (fConst0 * (6.98874158230498e-20 - fConst2) + -1.4095256819997e-16) + 1.75646845862514e-15);
	fConst22 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst4 + -7.00613593632107e-20) + 1.47460849525455e-16) + -2.81034919192636e-15) + 1.29152092545966e-14);
	fConst23 = fConst1 * (fConst0 * (fConst0 * (fConst6 + -9.36483991458906e-20) + 1.70486053448624e-16) + -2.12307123308889e-15);
	fConst24 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (9.42766173980015e-20 - fConst8) + -1.78421312766784e-16) + 3.39775512445924e-15) + -1.56108178903595e-14);
	fConst25 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst10 + -5.71785438210912e-20) + 1.41224926366503e-16) + -3.77185698680303e-15) + 3.30317585349598e-14 + fConst0 * (fConst0 * (fConst0 * (6.14378170525581e-20 - fConst11) + -1.4867852143994e-16) + 4.14135154627774e-15) + -3.80287926742832e-14);
	double fConst26 = 2.55545753537499e-23 * fConst0;
	fConst27 = fConst1 * (fConst0 * (fConst0 * (fConst26 + -2.09662247469149e-19) + 1.4095256819997e-16) + 1.75646845862514e-15);
	double fConst28 = 2.53772681290311e-23 * fConst0;
	fConst29 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (2.10184078089632e-19 - fConst28) + -1.47460849525455e-16) + -2.81034919192636e-15) + 3.87456277637898e-14);
	double fConst30 = 4.95688793492651e-23 * fConst0;
	fConst31 = fConst1 * (fConst0 * (fConst0 * (2.80945197437672e-19 - fConst30) + -1.70486053448624e-16) + -2.12307123308889e-15);
	double fConst32 = 4.92249518799889e-23 * fConst0;
	fConst33 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst32 + -2.82829852194005e-19) + 1.78421312766784e-16) + 3.39775512445924e-15) + -4.68324536710785e-14);
	double fConst34 = 7.94442635984257e-24 * fConst0;
	double fConst35 = 5.19865134208184e-24 * fConst0;
	fConst36 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (1.71535631463274e-19 - fConst35) + -1.41224926366503e-16) + -3.77185698680303e-15) + 9.90952756048795e-14 + fConst0 * (fConst0 * (fConst0 * (fConst34 + -1.84313451157674e-19) + 1.4867852143994e-16) + 4.14135154627774e-15) + -1.1408637802285e-13);
	double fConst37 = 5.11091507074998e-23 * fConst0;
	fConst38 = fConst1 * (fConst0 * (fConst0 * (1.397748316461e-19 - fConst37) + 2.81905136399941e-16) + -3.51293691725028e-15);
	double fConst39 = 5.07545362580621e-23 * fConst0;
	fConst40 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst39 + -1.40122718726421e-19) + -2.94921699050911e-16) + 5.62069838385272e-15) + 2.58304185091932e-14);
	double fConst41 = 9.91377586985301e-23 * fConst0;
	fConst42 = fConst1 * (fConst0 * (fConst0 * (fConst41 + -1.87296798291781e-19) + -3.40972106897249e-16) + 4.24614246617778e-15);
	double fConst43 = 9.84499037599778e-23 * fConst0;
	fConst44 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (1.88553234796003e-19 - fConst43) + 3.56842625533568e-16) + -6.79551024891847e-15) + -3.1221635780719e-14);
	double fConst45 = 1.58888527196851e-23 * fConst0;
	double fConst46 = 1.03973026841637e-23 * fConst0;
	fConst47 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst46 + -1.14357087642182e-19) + -2.82449852733007e-16) + 7.54371397360606e-15) + 6.60635170699196e-14 + fConst0 * (fConst0 * (fConst0 * (1.22875634105116e-19 - fConst45) + 2.97357042879881e-16) + -8.28270309255548e-15) + -7.60575853485664e-14);
	fConst48 = fConst1 * (fConst0 * (fConst0 * (fConst37 + 1.397748316461e-19) + -2.81905136399941e-16) + -3.51293691725028e-15);
	fConst49 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (-1.40122718726421e-19 - fConst39) + 2.94921699050911e-16) + 5.62069838385272e-15) + -2.58304185091932e-14);
	fConst50 = fConst1 * (fConst0 * (fConst0 * (-1.87296798291781e-19 - fConst41) + 3.40972106897249e-16) + 4.24614246617778e-15);
	fConst51 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst43 + 1.88553234796003e-19) + -3.56842625533568e-16) + -6.79551024891847e-15) + 3.1221635780719e-14);
	fConst52 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (-1.14357087642182e-19 - fConst46) + 2.82449852733007e-16) + 7.54371397360606e-15) + -6.60635170699196e-14 + fConst0 * (fConst0 * (fConst0 * (fConst45 + 1.22875634105116e-19) + -2.97357042879881e-16) + -8.28270309255548e-15) + 7.60575853485664e-14);
	fConst53 = fConst1 * (fConst0 * (fConst0 * (-2.09662247469149e-19 - fConst26) + -1.4095256819997e-16) + 1.75646845862514e-15);
	fConst54 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst28 + 2.10184078089632e-19) + 1.47460849525455e-16) + -2.81034919192636e-15) + -3.87456277637898e-14);
	fConst55 = fConst1 * (fConst0 * (fConst0 * (fConst30 + 2.80945197437672e-19) + 1.70486053448624e-16) + -2.12307123308889e-15);
	fConst56 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (-2.82829852194005e-19 - fConst32) + -1.78421312766784e-16) + 3.39775512445924e-15) + 4.68324536710785e-14);
	fConst57 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst35 + 1.71535631463274e-19) + 1.41224926366503e-16) + -3.77185698680303e-15) + -9.90952756048795e-14 + fConst0 * (fConst0 * (fConst0 * (-1.84313451157674e-19 - fConst34) + -1.4867852143994e-16) + 4.14135154627774e-15) + 1.1408637802285e-13);
	double fConst58 = 2.03624719512197e-26 * fConst0;
	fConst59 = fConst0 * (fConst58 + 4.02356549528453e-20) + 1.23525177556824e-15;
	double fConst60 = 1.9757204247131e-26 * fConst0;
	fConst61 = fConst0 * (-3.78902721530964e-20 - fConst60) + 2.68904213585766e-17;
	double fConst62 = 1.9757204247131e-28 * fConst0;
	fConst63 = fConst0 * (-3.78902721530964e-22 - fConst62) + 2.68904213585766e-19;
	double fConst64 = 2.03624719512197e-28 * fConst0;
	fConst65 = fConst0 * (fConst64 + 4.02356549528453e-22) + 1.23525177556824e-17;
	double fConst66 = 4.07249439024394e-26 * fConst0;
	fConst67 = fConst0 * (-2.68237699685635e-20 - fConst66) + 2.47050355113649e-15;
	double fConst68 = 3.9514408494262e-26 * fConst0;
	fConst69 = fConst0 * (fConst68 + 2.52601814353976e-20) + 5.37808427171532e-17;
	double fConst70 = 3.9514408494262e-28 * fConst0;
	fConst71 = fConst0 * (fConst70 + 2.52601814353976e-22) + 5.37808427171532e-19;
	double fConst72 = 4.07249439024394e-28 * fConst0;
	fConst73 = fConst0 * (-2.68237699685635e-22 - fConst72) + 2.47050355113649e-17;
	fConst74 = fConst0 * (fConst66 + -2.68237699685635e-20) + -2.47050355113649e-15;
	fConst75 = fConst0 * (2.52601814353976e-20 - fConst68) + -5.37808427171532e-17;
	fConst76 = fConst0 * (2.52601814353976e-22 - fConst70) + -5.37808427171532e-19;
	fConst77 = fConst0 * (fConst72 + -2.68237699685635e-22) + -2.47050355113649e-17;
	fConst78 = fConst0 * (4.02356549528453e-20 - fConst58) + -1.23525177556824e-15;
	fConst79 = fConst0 * (fConst60 + -3.78902721530964e-20) + -2.68904213585766e-17;
	fConst80 = fConst0 * (fConst62 + -3.78902721530964e-22) + -2.68904213585766e-19;
	fConst81 = fConst0 * (4.02356549528453e-22 - fConst64) + -1.23525177556824e-17;
	fConst82 = fConst0 * (fConst13 + -1.34118849842818e-20) + 1.23525177556824e-15;
	fConst83 = fConst0 * (1.26300907176988e-20 - fConst15) + 2.68904213585766e-17;
	fConst84 = fConst0 * (1.26300907176988e-22 - fConst17) + 2.68904213585766e-19;
	fConst85 = fConst0 * (fConst19 + -1.34118849842818e-22) + 1.23525177556824e-17;
	fConst86 = mydsp_faustpower3_f(fConst0);

	sample_rate = 96000;
	smpCl.setup(fSampleRate, sample_rate);
	fSampleRate = sample_rate;
	double fConstCl0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	double fConstCl1 = std::tan(97.38937226128358 / fConstCl0);
	double fConstCl2 = 1.0 / fConstCl1;
	double fConstCl3 = fConstCl2 + 1.0;
	fConstCl4 = (1.0 - fConstCl2) / fConstCl3;
	double fConstCl5 = 1.0 / std::tan(270.1769682087222 / fConstCl0);
	fConstCl6 = 1.0 - fConstCl5;
	fConstCl7 = 1.0 / (fConstCl5 + 1.0);
	fConstCl8 = 1.0 / (fConstCl1 * fConstCl3);
	fConstCl9 = 0.0 - fConstCl8;

	clear_state_f();
}

void Dsp::init_static(unsigned int sample_rate, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlowV0 = (0.0010000000000000009 * double(fsliderV0));

	double fSlow0 = 0.007000000000000006 * double(fVslider0);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec0[0] = fSlow0 + 0.993 * fRec0[1];
		double fTemp0 = fConst12 + fRec0[0] * (fConst9 + fConst7 * fRec0[0] + fConst5 + fConst3 * fRec0[0]) + 1.982065173355061e-14;
		fRec1[0] = double(input0[i0]) - (fRec1[1] * (fConst57 + fRec0[0] * (fConst56 + fConst55 * fRec0[0] + fConst54 + fConst53 * fRec0[0]) + 9.910325866775292e-14) + fRec1[2] * (fConst52 + fRec0[0] * (fConst51 + fConst50 * fRec0[0] + fConst49 + fConst48 * fRec0[0]) + 1.9820651733550584e-13) + fRec1[3] * (fConst47 + fRec0[0] * (fConst44 + fConst42 * fRec0[0] + fConst40 + fConst38 * fRec0[0]) + 1.9820651733550584e-13) + fRec1[4] * (fConst36 + fRec0[0] * (fConst33 + fConst31 * fRec0[0] + fConst29 + fConst27 * fRec0[0]) + 9.910325866775292e-14) + fRec1[5] * (fConst25 + fRec0[0] * (fConst24 + fConst23 * fRec0[0] + fConst22 + fConst21 * fRec0[0]) + 1.982065173355061e-14)) / fTemp0;
		output0[i0] = FAUSTFLOAT(fConst86 * ((fRec1[0] * (fConst85 + fConst84 + fConst83 * fRec0[0] + fConst82 * fRec0[0]) + fRec1[1] * (fConst81 + fConst80 + fConst79 * fRec0[0] + fConst78 * fRec0[0]) + fRec1[2] * (fConst77 + fConst76 + fConst75 * fRec0[0] + fConst74 * fRec0[0]) + fRec1[3] * (fConst73 + fConst71 + fConst69 * fRec0[0] + fConst67 * fRec0[0]) + fRec1[4] * (fConst65 + fConst63 + fConst61 * fRec0[0] + fConst59 * fRec0[0]) + fRec1[5] * (fConst20 + fConst18 + fConst16 * fRec0[0] + fConst14 * fRec0[0])) / fTemp0));
		fRec0[1] = fRec0[0];
		for (int j0 = 5; j0 > 0; j0 = j0 - 1) {
			fRec1[j0] = fRec1[j0 - 1];
		}
	}

	FAUSTFLOAT bufCl[smpCl.max_out_count(count)];
	int ReCount = smpCl.up(count, output0, bufCl);
	for (int i0 = 0; i0 < ReCount; i0 = i0 + 1) {
		double fTemp0 = double(bufCl[i0]);
		fVecCl0[0] = fTemp0;
		fRecCl7[0] = 0.9302847925323914 * (fTemp0 + fVecCl0[1]) - 0.8605695850647829 * fRecCl7[1];
		fRecCl6[0] = fRecCl7[0] - (1.8405051250752198 * fRecCl6[1] + 0.8612942439318627 * fRecCl6[2]);
		fRecCl8[0] = fConstCl7 * (0.027 * (fRecCl5[1] + fRecCl5[2]) - fConstCl6 * fRecCl8[1]);
		fRecCl5[0] = Ftrany(TRANY_TABLE_7199P_68k, 0.9254498422517706 * (fRecCl6[0] + fRecCl6[2]) + fRecCl8[0] + 1.8508996845035413 * fRecCl6[1] + -3.571981) + -117.70440740740739;
		fRecCl4[0] = 0.025 * (fConstCl8 * fRecCl5[0] + fConstCl9 * fRecCl5[1]) - fConstCl4 * fRecCl4[1];
		fRecCl3[0] = 0.9302847925323914 * (fRecCl4[0] + fRecCl4[1]) - 0.8605695850647829 * fRecCl3[1];
		fRecCl2[0] = fRecCl3[0] - (1.8405051250752198 * fRecCl2[1] + 0.8612942439318627 * fRecCl2[2]);
		fRecCl9[0] = fConstCl7 * (0.027 * (fRecCl1[1] + fRecCl1[2]) - fConstCl6 * fRecCl9[1]);
		fRecCl1[0] = Ftrany(TRANY_TABLE_7199P_68k, 0.9254498422517706 * (fRecCl2[0] + fRecCl2[2]) + fRecCl9[0] + 1.8508996845035413 * fRecCl2[1] + -3.571981) + -117.70440740740739;
		fRecCl0[0] = 0.025 * (fConstCl8 * fRecCl1[0] + fConstCl9 * fRecCl1[1]) - fConstCl4 * fRecCl0[1];
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

	for (int i=0; i<count; i++) {
		fRecV0[0] = ((0.999 * fRecV0[1]) + fSlowV0);
		output0[i] = (FAUSTFLOAT)((double)output0[i] * fRecV0[0]);
		// post processing
		fRecV0[1] = fRecV0[0];
	}

}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerFloatVar("susta.Volume",N_("Volume"),"S","",&fsliderV0, 0.5, 0.0, 1, 0.01, 0);
	reg.registerFloatVar("susta.Sustain",N_("Sustain"),"S","",&fVslider0, 0.5, 0.0, 1.0, 0.01, 0);
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
                        <property name=\"var_id\">susta.Sustain</property>\n\
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
                        <property name=\"var_id\">susta.Volume</property>\n\
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
                <property name=\"var_id\">susta.Sustain</property>\n\
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
                <property name=\"label\" translatable=\"yes\">Sustain</property>\n\
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
#define PARAM(p) ("susta" "." p)

b.openHorizontalhideBox("");
    b.create_master_slider(PARAM("Sustain"), N_("Sustain"));
b.closeBox();
b.openHorizontalBox("");

    b.create_small_rackknobr(PARAM("Sustain"), N_("Sustain"));

    b.create_small_rackknobr(PARAM("Volume"), N_("Volume"));
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

} // end namespace susta
} // end namespace pluginlib
