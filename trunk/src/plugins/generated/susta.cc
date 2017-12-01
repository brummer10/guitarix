// generated from file '../src/plugins/susta.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

#include "trany.h"

namespace pluginlib {
namespace susta {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	double 	fConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	FAUSTFLOAT 	fslider0;
	double 	fRec0[2];
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	double 	fConst9;
	double 	fConst10;
	double 	fConst11;
	double 	fConst12;
	double 	fConst13;
	double 	fConst14;
	double 	fConst15;
	double 	fConst16;
	double 	fConst17;
	double 	fConst18;
	double 	fConst19;
	double 	fConst20;
	double 	fConst21;
	double 	fConst22;
	double 	fConst23;
	double 	fConst24;
	double 	fConst25;
	double 	fConst26;
	double 	fConst27;
	double 	fConst28;
	double 	fConst29;
	double 	fConst30;
	double 	fConst31;
	double 	fConst32;
	double 	fConst33;
	double 	fConst34;
	double 	fConst35;
	double 	fConst36;
	double 	fConst37;
	double 	fConst38;
	double 	fConst39;
	double 	fConst40;
	double 	fConst41;
	double 	fConst42;
	double 	fConst43;
	double 	fConst44;
	double 	fConst45;
	double 	fConst46;
	double 	fConst47;
	double 	fConst48;
	double 	fConst49;
	double 	fConst50;
	double 	fConst51;
	double 	fConst52;
	double 	fConst53;
	double 	fConst54;
	double 	fRec1[6];
	double 	fConst55;
	double 	fConst56;
	double 	fConst57;
	double 	fConst58;
	double 	fConst59;
	double 	fConst60;
	double 	fConst61;
	double 	fConst62;
	double 	fConst63;
	double 	fConst64;
	double 	fConst65;
	double 	fConst66;
	double 	fConst67;
	double 	fConst68;
	double 	fConst69;
	double 	fConst70;
	double 	fConst71;
	double 	fConst72;
	double 	fConst73;


	int samplingFreq;
	gx_resample::FixedRateResampler smpCl;
	double 	fVecCl0[2];
	double 	fRecCl7[2];
	double 	fRecCl6[3];
	double 	fConstCl0;
	double 	fConstCl1;
	double 	fConstCl2;
	double 	fConstCl3;
	double 	fConstCl4;
	double 	fRecCl8[2];
	double 	fRecCl5[3];
	double 	fConstCl5;
	double 	fConstCl6;
	double 	fConstCl7;
	double 	fConstCl8;
	double 	fConstCl9;
	double 	fRecCl4[2];
	double 	fRecCl3[2];
	double 	fRecCl2[3];
	double 	fRecCl9[2];
	double 	fRecCl1[3];
	double 	fRecCl0[2];

	FAUSTFLOAT 	fsliderV0;
	double 	fRecV0[2];
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
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<6; i++) fRec1[i] = 0;

	for (int i=0; i<2; i++) fVecCl0[i] = 0;
	for (int i=0; i<2; i++) fRecCl7[i] = 0;
	for (int i=0; i<3; i++) fRecCl6[i] = 0;
	for (int i=0; i<2; i++) fRecCl8[i] = 0;
	for (int i=0; i<3; i++) fRecCl5[i] = 0;
	for (int i=0; i<2; i++) fRecCl4[i] = 0;
	for (int i=0; i<2; i++) fRecCl3[i] = 0;
	for (int i=0; i<3; i++) fRecCl2[i] = 0;
	for (int i=0; i<2; i++) fRecCl9[i] = 0;
	for (int i=0; i<3; i++) fRecCl1[i] = 0;
	for (int i=0; i<2; i++) fRecCl0[i] = 0;

	for (int i=0; i<2; i++) fRecV0[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = double(min(1.92e+05, max(1.0, (double)fSamplingFreq)));
	fConst1 = (1.58888527196851e-24 * fConst0);
	fConst2 = (1.03973026841637e-24 * fConst0);
	fConst3 = (4.997034139323402e-15 + (fConst0 * (((fConst0 * ((fConst0 * (0 - (5.71785438210912e-20 + fConst2))) - 1.41224926366503e-16)) - 3.77185698680303e-15) + (4.14135154627774e-15 + (fConst0 * (1.4867852143994e-16 + (fConst0 * (6.14378170525581e-20 + fConst1))))))));
	fConst4 = (5.11091507074998e-24 * fConst0);
	fConst5 = (1.75646845862514e-15 + (fConst0 * (1.4095256819997e-16 + (fConst0 * (6.98874158230498e-20 + fConst4)))));
	fConst6 = (5.07545362580621e-24 * fConst0);
	fConst7 = ((fConst0 * ((fConst0 * (0 - (7.00613593632107e-20 + fConst6))) - 1.47460849525455e-16)) - 2.81034919192636e-15);
	fConst8 = (9.91377586985301e-24 * fConst0);
	fConst9 = ((fConst0 * ((fConst0 * (0 - (9.36483991458906e-20 + fConst8))) - 1.70486053448624e-16)) - 2.12307123308889e-15);
	fConst10 = (9.84499037599778e-24 * fConst0);
	fConst11 = (3.39775512445924e-15 + (fConst0 * (1.78421312766784e-16 + (fConst0 * (9.42766173980015e-20 + fConst10)))));
	fConst12 = (4.07249439024394e-29 * fConst0);
	fConst13 = (3.9514408494262e-29 * fConst0);
	fConst14 = ((fConst0 * ((1.26300907176988e-22 + fConst13) + (0 - (1.34118849842818e-22 + fConst12)))) - 1.2621421969268167e-17);
	fConst15 = (3.9514408494262e-27 * fConst0);
	fConst16 = (4.07249439024394e-27 * fConst0);
	fConst17 = (((fConst0 * (0 - (1.34118849842818e-20 + fConst16))) - 1.23525177556824e-15) + ((fConst0 * (1.26300907176988e-20 + fConst15)) - 2.68904213585766e-17));
	fConst18 = ((fConst0 * (((fConst0 * (1.41224926366503e-16 + (fConst0 * (fConst2 - 5.71785438210912e-20)))) - 3.77185698680303e-15) + (4.14135154627774e-15 + (fConst0 * ((fConst0 * (6.14378170525581e-20 - fConst1)) - 1.4867852143994e-16))))) - 4.997034139323402e-15);
	fConst19 = (1.75646845862514e-15 + (fConst0 * ((fConst0 * (6.98874158230498e-20 - fConst4)) - 1.4095256819997e-16)));
	fConst20 = ((fConst0 * (1.47460849525455e-16 + (fConst0 * (fConst6 - 7.00613593632107e-20)))) - 2.81034919192636e-15);
	fConst21 = ((fConst0 * (1.70486053448624e-16 + (fConst0 * (fConst8 - 9.36483991458906e-20)))) - 2.12307123308889e-15);
	fConst22 = (3.39775512445924e-15 + (fConst0 * ((fConst0 * (9.42766173980015e-20 - fConst10)) - 1.78421312766784e-16)));
	fConst23 = (7.94442635984257e-24 * fConst0);
	fConst24 = (5.19865134208184e-24 * fConst0);
	fConst25 = ((fConst0 * (((fConst0 * ((fConst0 * (1.71535631463274e-19 - fConst24)) - 1.41224926366503e-16)) - 3.77185698680303e-15) + (4.14135154627774e-15 + (fConst0 * (1.4867852143994e-16 + (fConst0 * (fConst23 - 1.84313451157674e-19))))))) - 1.4991102417970515e-14);
	fConst26 = (2.55545753537499e-23 * fConst0);
	fConst27 = (1.75646845862514e-15 + (fConst0 * (1.4095256819997e-16 + (fConst0 * (fConst26 - 2.09662247469149e-19)))));
	fConst28 = (2.53772681290311e-23 * fConst0);
	fConst29 = ((fConst0 * ((fConst0 * (2.10184078089632e-19 - fConst28)) - 1.47460849525455e-16)) - 2.81034919192636e-15);
	fConst30 = (4.95688793492651e-23 * fConst0);
	fConst31 = ((fConst0 * ((fConst0 * (2.80945197437672e-19 - fConst30)) - 1.70486053448624e-16)) - 2.12307123308889e-15);
	fConst32 = (4.92249518799889e-23 * fConst0);
	fConst33 = (3.39775512445924e-15 + (fConst0 * (1.78421312766784e-16 + (fConst0 * (fConst32 - 2.82829852194005e-19)))));
	fConst34 = (1.58888527196851e-23 * fConst0);
	fConst35 = (1.03973026841637e-23 * fConst0);
	fConst36 = ((fConst0 * ((7.54371397360606e-15 + (fConst0 * ((fConst0 * (fConst35 - 1.14357087642182e-19)) - 2.82449852733007e-16))) + ((fConst0 * (2.97357042879881e-16 + (fConst0 * (1.22875634105116e-19 - fConst34)))) - 8.28270309255548e-15))) - 9.994068278646804e-15);
	fConst37 = (5.11091507074998e-23 * fConst0);
	fConst38 = ((fConst0 * (2.81905136399941e-16 + (fConst0 * (1.397748316461e-19 - fConst37)))) - 3.51293691725028e-15);
	fConst39 = (5.07545362580621e-23 * fConst0);
	fConst40 = (5.62069838385272e-15 + (fConst0 * ((fConst0 * (fConst39 - 1.40122718726421e-19)) - 2.94921699050911e-16)));
	fConst41 = (9.91377586985301e-23 * fConst0);
	fConst42 = (4.24614246617778e-15 + (fConst0 * ((fConst0 * (fConst41 - 1.87296798291781e-19)) - 3.40972106897249e-16)));
	fConst43 = (9.84499037599778e-23 * fConst0);
	fConst44 = ((fConst0 * (3.56842625533568e-16 + (fConst0 * (1.88553234796003e-19 - fConst43)))) - 6.79551024891847e-15);
	fConst45 = (9.994068278646804e-15 + (fConst0 * ((7.54371397360606e-15 + (fConst0 * (2.82449852733007e-16 + (fConst0 * (0 - (1.14357087642182e-19 + fConst35)))))) + ((fConst0 * ((fConst0 * (1.22875634105116e-19 + fConst34)) - 2.97357042879881e-16)) - 8.28270309255548e-15))));
	fConst46 = ((fConst0 * ((fConst0 * (1.397748316461e-19 + fConst37)) - 2.81905136399941e-16)) - 3.51293691725028e-15);
	fConst47 = (5.62069838385272e-15 + (fConst0 * (2.94921699050911e-16 + (fConst0 * (0 - (1.40122718726421e-19 + fConst39))))));
	fConst48 = (4.24614246617778e-15 + (fConst0 * (3.40972106897249e-16 + (fConst0 * (0 - (1.87296798291781e-19 + fConst41))))));
	fConst49 = ((fConst0 * ((fConst0 * (1.88553234796003e-19 + fConst43)) - 3.56842625533568e-16)) - 6.79551024891847e-15);
	fConst50 = (1.4991102417970515e-14 + (fConst0 * (((fConst0 * (1.41224926366503e-16 + (fConst0 * (1.71535631463274e-19 + fConst24)))) - 3.77185698680303e-15) + (4.14135154627774e-15 + (fConst0 * ((fConst0 * (0 - (1.84313451157674e-19 + fConst23))) - 1.4867852143994e-16))))));
	fConst51 = (1.75646845862514e-15 + (fConst0 * ((fConst0 * (0 - (2.09662247469149e-19 + fConst26))) - 1.4095256819997e-16)));
	fConst52 = ((fConst0 * (1.47460849525455e-16 + (fConst0 * (2.10184078089632e-19 + fConst28)))) - 2.81034919192636e-15);
	fConst53 = ((fConst0 * (1.70486053448624e-16 + (fConst0 * (2.80945197437672e-19 + fConst30)))) - 2.12307123308889e-15);
	fConst54 = (3.39775512445924e-15 + (fConst0 * ((fConst0 * (0 - (2.82829852194005e-19 + fConst32))) - 1.78421312766784e-16)));
	fConst55 = (2.03624719512197e-28 * fConst0);
	fConst56 = (1.9757204247131e-28 * fConst0);
	fConst57 = (1.2621421969268167e-17 + (fConst0 * ((0 - (3.78902721530964e-22 + fConst56)) + (4.02356549528453e-22 + fConst55))));
	fConst58 = (1.9757204247131e-26 * fConst0);
	fConst59 = (2.03624719512197e-26 * fConst0);
	fConst60 = ((1.23525177556824e-15 + (fConst0 * (4.02356549528453e-20 + fConst59))) + (2.68904213585766e-17 + (fConst0 * (0 - (3.78902721530964e-20 + fConst58)))));
	fConst61 = (4.07249439024394e-28 * fConst0);
	fConst62 = (3.9514408494262e-28 * fConst0);
	fConst63 = (2.5242843938536432e-17 + (fConst0 * ((2.52601814353976e-22 + fConst62) + (0 - (2.68237699685635e-22 + fConst61)))));
	fConst64 = (3.9514408494262e-26 * fConst0);
	fConst65 = (4.07249439024394e-26 * fConst0);
	fConst66 = ((2.47050355113649e-15 + (fConst0 * (0 - (2.68237699685635e-20 + fConst65)))) + (5.37808427171532e-17 + (fConst0 * (2.52601814353976e-20 + fConst64))));
	fConst67 = ((fConst0 * ((fConst61 - 2.68237699685635e-22) + (2.52601814353976e-22 - fConst62))) - 2.5242843938536432e-17);
	fConst68 = (((fConst0 * (fConst65 - 2.68237699685635e-20)) - 2.47050355113649e-15) + ((fConst0 * (2.52601814353976e-20 - fConst64)) - 5.37808427171532e-17));
	fConst69 = ((fConst0 * ((fConst56 - 3.78902721530964e-22) + (4.02356549528453e-22 - fConst55))) - 1.2621421969268167e-17);
	fConst70 = (((fConst0 * (fConst58 - 3.78902721530964e-20)) - 2.68904213585766e-17) + ((fConst0 * (4.02356549528453e-20 - fConst59)) - 1.23525177556824e-15));
	fConst71 = (1.2621421969268167e-17 + (fConst0 * ((fConst12 - 1.34118849842818e-22) + (1.26300907176988e-22 - fConst13))));
	fConst72 = ((1.23525177556824e-15 + (fConst0 * (fConst16 - 1.34118849842818e-20))) + (2.68904213585766e-17 + (fConst0 * (1.26300907176988e-20 - fConst15))));
	fConst73 = faustpower<3>(fConst0);

	samplingFreq = 96000;
	smpCl.setup(fSamplingFreq, samplingFreq);
	fSamplingFreq = samplingFreq;
	fConstCl0 = min(1.92e+05, max(1.0, (double)fSamplingFreq));
	fConstCl1 = (1.0 / tan((270.1769682087222 / fConstCl0)));
	fConstCl2 = (1 + fConstCl1);
	fConstCl3 = (0 - ((1 - fConstCl1) / fConstCl2));
	fConstCl4 = (0.027 / fConstCl2);
	fConstCl5 = (1.0 / tan((97.38937226128358 / fConstCl0)));
	fConstCl6 = (0 - fConstCl5);
	fConstCl7 = (1 + fConstCl5);
	fConstCl8 = (0.025 / fConstCl7);
	fConstCl9 = (0 - ((1 - fConstCl5) / fConstCl7));

	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlowV0 = (0.0010000000000000009 * double(fsliderV0));

	double 	fSlow0 = (0.007000000000000006 * double(fslider0));
	for (int i=0; i<count; i++) {
		fRec0[0] = (fSlow0 + (0.993 * fRec0[1]));
		double fTemp0 = (1.982065173355061e-14 + (fConst0 * ((fRec0[0] * ((1.56108178903595e-14 + (fConst0 * (fConst11 + (fConst9 * fRec0[0])))) + ((fConst0 * (fConst7 + (fConst5 * fRec0[0]))) - 1.29152092545966e-14))) + fConst3)));
		fRec1[0] = ((double)input0[i] - ((((((fRec1[1] * (9.910325866775292e-14 + (fConst0 * ((fRec0[0] * ((4.68324536710785e-14 + (fConst0 * (fConst54 + (fConst53 * fRec0[0])))) + ((fConst0 * (fConst52 + (fConst51 * fRec0[0]))) - 3.87456277637898e-14))) + fConst50)))) + (fRec1[2] * (1.9820651733550584e-13 + (fConst0 * ((fRec0[0] * ((3.1221635780719e-14 + (fConst0 * (fConst49 + (fConst48 * fRec0[0])))) + ((fConst0 * (fConst47 + (fConst46 * fRec0[0]))) - 2.58304185091932e-14))) + fConst45))))) + (fRec1[3] * (1.9820651733550584e-13 + (fConst0 * ((fRec0[0] * (((fConst0 * (fConst44 + (fConst42 * fRec0[0]))) - 3.1221635780719e-14) + (2.58304185091932e-14 + (fConst0 * (fConst40 + (fConst38 * fRec0[0])))))) + fConst36))))) + (fRec1[4] * (9.910325866775292e-14 + (fConst0 * ((fRec0[0] * (((fConst0 * (fConst33 + (fConst31 * fRec0[0]))) - 4.68324536710785e-14) + (3.87456277637898e-14 + (fConst0 * (fConst29 + (fConst27 * fRec0[0])))))) + fConst25))))) + (fRec1[5] * (1.982065173355061e-14 + (fConst0 * ((fRec0[0] * (((fConst0 * (fConst22 + (fConst21 * fRec0[0]))) - 1.56108178903595e-14) + (1.29152092545966e-14 + (fConst0 * (fConst20 + (fConst19 * fRec0[0])))))) + fConst18))))) / fTemp0));
		output0[i] = (FAUSTFLOAT)(fConst73 * (((((((fRec1[0] * ((fConst72 * fRec0[0]) + fConst71)) + (fRec1[1] * ((fConst70 * fRec0[0]) + fConst69))) + (fRec1[2] * ((fConst68 * fRec0[0]) + fConst67))) + (fRec1[3] * ((fConst66 * fRec0[0]) + fConst63))) + (fRec1[4] * ((fConst60 * fRec0[0]) + fConst57))) + (fRec1[5] * ((fConst17 * fRec0[0]) + fConst14))) / fTemp0));
		// post processing
		for (int i=5; i>0; i--) fRec1[i] = fRec1[i-1];
		fRec0[1] = fRec0[0];
	}

	FAUSTFLOAT bufCl[smpCl.max_out_count(count)];
	int ReCount = smpCl.up(count, output0, bufCl);
	for (int i=0; i<ReCount; i++) {
		double fTemp0 = (double)bufCl[i];
		fVecCl0[0] = fTemp0;
		fRecCl7[0] = ((0.9302847925323914 * (fVecCl0[0] + fVecCl0[1])) - (0.8605695850647829 * fRecCl7[1]));
		fRecCl6[0] = (fRecCl7[0] - ((1.8405051250752198 * fRecCl6[1]) + (0.8612942439318627 * fRecCl6[2])));
		fRecCl8[0] = ((fConstCl4 * (fRecCl5[1] + fRecCl5[2])) + (fConstCl3 * fRecCl8[1]));
		fRecCl5[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRecCl8[0] + (0.9254498422517706 * (fRecCl6[0] + (fRecCl6[2] + (2.0 * fRecCl6[1]))))) - 3.571981)) - 117.70440740740739);
		fRecCl4[0] = ((fConstCl9 * fRecCl4[1]) + (fConstCl8 * ((fConstCl5 * fRecCl5[0]) + (fConstCl6 * fRecCl5[1]))));
		fRecCl3[0] = ((0.9302847925323914 * (fRecCl4[1] + fRecCl4[0])) - (0.8605695850647829 * fRecCl3[1]));
		fRecCl2[0] = (fRecCl3[0] - ((1.8405051250752198 * fRecCl2[1]) + (0.8612942439318627 * fRecCl2[2])));
		fRecCl9[0] = ((fConstCl4 * (fRecCl1[1] + fRecCl1[2])) + (fConstCl3 * fRecCl9[1]));
		fRecCl1[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRecCl9[0] + (0.9254498422517706 * (fRecCl2[0] + (fRecCl2[2] + (2.0 * fRecCl2[1]))))) - 3.571981)) - 117.70440740740739);
		fRecCl0[0] = ((fConstCl9 * fRecCl0[1]) + (fConstCl8 * ((fConstCl5 * fRecCl1[0]) + (fConstCl6 * fRecCl1[1]))));
		bufCl[i] = (FAUSTFLOAT)fRecCl0[0];
		// post processing
		fRecCl0[1] = fRecCl0[0];
		fRecCl1[2] = fRecCl1[1]; fRecCl1[1] = fRecCl1[0];
		fRecCl9[1] = fRecCl9[0];
		fRecCl2[2] = fRecCl2[1]; fRecCl2[1] = fRecCl2[0];
		fRecCl3[1] = fRecCl3[0];
		fRecCl4[1] = fRecCl4[0];
		fRecCl5[2] = fRecCl5[1]; fRecCl5[1] = fRecCl5[0];
		fRecCl8[1] = fRecCl8[0];
		fRecCl6[2] = fRecCl6[1]; fRecCl6[1] = fRecCl6[0];
		fRecCl7[1] = fRecCl7[0];
		fVecCl0[1] = fVecCl0[0];
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
	reg.registerVar("susta.Volume",N_("Volume"),"S","",&fsliderV0, 0.5, 0.0, 1, 0.01);
	reg.registerVar("susta.Sustain",N_("Sustain"),"S","",&fslider0, 0.5, 0.0, 1.0, 0.01);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

const char *Dsp::glade_def = "\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<interface>\n\
  <!-- interface-requires gxwidgets 0.0 -->\n\
  <requires lib=\"gtk+\" version=\"2.20\"/>\n\
  <!-- interface-naming-policy project-wide -->\n\
  <object class=\"GtkWindow\" id=\"window1\">\n\
    <property name=\"can_focus\">False</property>\n\
    <child>\n\
      <object class=\"GtkVBox\" id=\"vbox1\">\n\
        <property name=\"visible\">True</property>\n\
        <property name=\"can_focus\">False</property>\n\
        <child>\n\
          <object class=\"GtkHBox\" id=\"rackbox\">\n\
            <property name=\"visible\">True</property>\n\
            <property name=\"can_focus\">False</property>\n\
            <property name=\"spacing\">4</property>\n\
            <child>\n\
              <object class=\"GtkHBox\" id=\"hbox1\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">False</property>\n\
                <property name=\"spacing\">10</property>\n\
                <child>\n\
                  <object class=\"GtkVBox\" id=\"vbox2\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
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
                  <object class=\"GtkVBox\" id=\"vbox3\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
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
          <object class=\"GtkHBox\" id=\"minibox\">\n\
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
                <property name=\"xalign\">0</property>\n\
                <property name=\"label\" translatable=\"yes\">Sustain</property>\n\
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
