// generated from file '../src/plugins/susta.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"
#include "trany.h"

namespace pluginlib {
namespace susta {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	FAUSTFLOAT 	fslider0;
	double 	fRec12[2];
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
	FAUSTFLOAT 	fslider1;
	double 	fRec13[2];
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
	double 	fConst55;
	double 	fConst56;
	double 	fConst57;
	double 	fConst58;
	double 	fConst59;
	double 	fConst60;
	double 	fConst61;
	double 	fConst62;
	double 	fConst63;
	double 	fRec14[6];
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
	double 	fConst74;
	double 	fConst75;
	double 	fConst76;
	double 	fConst77;
	double 	fConst78;
	double 	fConst79;
	double 	fConst80;
	double 	fConst81;
	double 	fConst82;
	double 	fConst83;
	double 	fConst84;
	double 	fConst85;
	double 	fConst86;
	double 	fConst87;
	double 	fConst88;
	double 	fConst89;
	double 	fConst90;
	double 	fConst91;
	double 	fConst92;
	double 	fRec11[3];
	double 	fVec0[2];
	double 	fRec10[2];
	double 	fConst93;
	double 	fConst94;
	double 	fConst95;
	double 	fConst96;
	double 	fRec15[2];
	double 	fRec9[3];
	double 	fConst97;
	double 	fConst98;
	double 	fConst99;
	double 	fConst100;
	double 	fConst101;
	double 	fRec8[2];
	double 	fRec7[3];
	double 	fVec1[2];
	double 	fRec6[2];
	double 	fRec16[2];
	double 	fRec5[3];
	double 	fRec4[2];
	double 	fRec3[3];
	double 	fVec2[2];
	double 	fRec2[2];
	double 	fRec17[2];
	double 	fRec1[3];
	double 	fRec0[2];
	void clear_state_f();
	int load_ui_f(const UiBuilder& b, int form);
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
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<6; i++) fRec14[i] = 0;
	for (int i=0; i<3; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<3; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<3; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<3; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<3; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = double(iConst0);
	fConst2 = (1.58888527196851e-24 * fConst1);
	fConst3 = (3.80287926742832e-14 + (fConst1 * (4.14135154627774e-15 + (fConst1 * (1.4867852143994e-16 + (fConst1 * (6.14378170525581e-20 + fConst2)))))));
	fConst4 = (9.91377586985301e-24 * fConst1);
	fConst5 = (fConst1 * ((fConst1 * ((fConst1 * (0 - (9.36483991458906e-20 + fConst4))) - 1.70486053448624e-16)) - 2.12307123308889e-15));
	fConst6 = (9.84499037599778e-24 * fConst1);
	fConst7 = (1.56108178903595e-14 + (fConst1 * (3.39775512445924e-15 + (fConst1 * (1.78421312766784e-16 + (fConst1 * (9.42766173980015e-20 + fConst6)))))));
	fConst8 = (1.03973026841637e-24 * fConst1);
	fConst9 = ((fConst1 * ((fConst1 * ((fConst1 * (0 - (5.71785438210912e-20 + fConst8))) - 1.41224926366503e-16)) - 3.77185698680303e-15)) - 3.30317585349598e-14);
	fConst10 = (5.11091507074998e-24 * fConst1);
	fConst11 = (fConst1 * (1.75646845862514e-15 + (fConst1 * (1.4095256819997e-16 + (fConst1 * (6.98874158230498e-20 + fConst10))))));
	fConst12 = (5.07545362580621e-24 * fConst1);
	fConst13 = ((fConst1 * ((fConst1 * ((fConst1 * (0 - (7.00613593632107e-20 + fConst12))) - 1.47460849525455e-16)) - 2.81034919192636e-15)) - 1.29152092545966e-14);
	fConst14 = (4.07249439024394e-29 * fConst1);
	fConst15 = ((fConst1 * (0 - (1.34118849842818e-22 + fConst14))) - 1.23525177556824e-17);
	fConst16 = (4.07249439024394e-27 * fConst1);
	fConst17 = ((fConst1 * (0 - (1.34118849842818e-20 + fConst16))) - 1.23525177556824e-15);
	fConst18 = (3.9514408494262e-27 * fConst1);
	fConst19 = ((fConst1 * (1.26300907176988e-20 + fConst18)) - 2.68904213585766e-17);
	fConst20 = (3.9514408494262e-29 * fConst1);
	fConst21 = ((fConst1 * (1.26300907176988e-22 + fConst20)) - 2.68904213585766e-19);
	fConst22 = ((fConst1 * (4.14135154627774e-15 + (fConst1 * ((fConst1 * (6.14378170525581e-20 - fConst2)) - 1.4867852143994e-16)))) - 3.80287926742832e-14);
	fConst23 = (fConst1 * ((fConst1 * (1.70486053448624e-16 + (fConst1 * (fConst4 - 9.36483991458906e-20)))) - 2.12307123308889e-15));
	fConst24 = ((fConst1 * (3.39775512445924e-15 + (fConst1 * ((fConst1 * (9.42766173980015e-20 - fConst6)) - 1.78421312766784e-16)))) - 1.56108178903595e-14);
	fConst25 = (3.30317585349598e-14 + (fConst1 * ((fConst1 * (1.41224926366503e-16 + (fConst1 * (fConst8 - 5.71785438210912e-20)))) - 3.77185698680303e-15)));
	fConst26 = (fConst1 * (1.75646845862514e-15 + (fConst1 * ((fConst1 * (6.98874158230498e-20 - fConst10)) - 1.4095256819997e-16))));
	fConst27 = (1.29152092545966e-14 + (fConst1 * ((fConst1 * (1.47460849525455e-16 + (fConst1 * (fConst12 - 7.00613593632107e-20)))) - 2.81034919192636e-15)));
	fConst28 = (7.94442635984257e-24 * fConst1);
	fConst29 = ((fConst1 * (4.14135154627774e-15 + (fConst1 * (1.4867852143994e-16 + (fConst1 * (fConst28 - 1.84313451157674e-19)))))) - 1.1408637802285e-13);
	fConst30 = (4.95688793492651e-23 * fConst1);
	fConst31 = (fConst1 * ((fConst1 * ((fConst1 * (2.80945197437672e-19 - fConst30)) - 1.70486053448624e-16)) - 2.12307123308889e-15));
	fConst32 = (4.92249518799889e-23 * fConst1);
	fConst33 = ((fConst1 * (3.39775512445924e-15 + (fConst1 * (1.78421312766784e-16 + (fConst1 * (fConst32 - 2.82829852194005e-19)))))) - 4.68324536710785e-14);
	fConst34 = (5.19865134208184e-24 * fConst1);
	fConst35 = (9.90952756048795e-14 + (fConst1 * ((fConst1 * ((fConst1 * (1.71535631463274e-19 - fConst34)) - 1.41224926366503e-16)) - 3.77185698680303e-15)));
	fConst36 = (2.55545753537499e-23 * fConst1);
	fConst37 = (fConst1 * (1.75646845862514e-15 + (fConst1 * (1.4095256819997e-16 + (fConst1 * (fConst36 - 2.09662247469149e-19))))));
	fConst38 = (2.53772681290311e-23 * fConst1);
	fConst39 = (3.87456277637898e-14 + (fConst1 * ((fConst1 * ((fConst1 * (2.10184078089632e-19 - fConst38)) - 1.47460849525455e-16)) - 2.81034919192636e-15)));
	fConst40 = (1.58888527196851e-23 * fConst1);
	fConst41 = ((fConst1 * ((fConst1 * (2.97357042879881e-16 + (fConst1 * (1.22875634105116e-19 - fConst40)))) - 8.28270309255548e-15)) - 7.60575853485664e-14);
	fConst42 = (9.91377586985301e-23 * fConst1);
	fConst43 = (fConst1 * (4.24614246617778e-15 + (fConst1 * ((fConst1 * (fConst42 - 1.87296798291781e-19)) - 3.40972106897249e-16))));
	fConst44 = (9.84499037599778e-23 * fConst1);
	fConst45 = ((fConst1 * ((fConst1 * (3.56842625533568e-16 + (fConst1 * (1.88553234796003e-19 - fConst44)))) - 6.79551024891847e-15)) - 3.1221635780719e-14);
	fConst46 = (1.03973026841637e-23 * fConst1);
	fConst47 = (6.60635170699196e-14 + (fConst1 * (7.54371397360606e-15 + (fConst1 * ((fConst1 * (fConst46 - 1.14357087642182e-19)) - 2.82449852733007e-16)))));
	fConst48 = (5.11091507074998e-23 * fConst1);
	fConst49 = (fConst1 * ((fConst1 * (2.81905136399941e-16 + (fConst1 * (1.397748316461e-19 - fConst48)))) - 3.51293691725028e-15));
	fConst50 = (5.07545362580621e-23 * fConst1);
	fConst51 = (2.58304185091932e-14 + (fConst1 * (5.62069838385272e-15 + (fConst1 * ((fConst1 * (fConst50 - 1.40122718726421e-19)) - 2.94921699050911e-16)))));
	fConst52 = (7.60575853485664e-14 + (fConst1 * ((fConst1 * ((fConst1 * (1.22875634105116e-19 + fConst40)) - 2.97357042879881e-16)) - 8.28270309255548e-15)));
	fConst53 = (fConst1 * (4.24614246617778e-15 + (fConst1 * (3.40972106897249e-16 + (fConst1 * (0 - (1.87296798291781e-19 + fConst42)))))));
	fConst54 = (3.1221635780719e-14 + (fConst1 * ((fConst1 * ((fConst1 * (1.88553234796003e-19 + fConst44)) - 3.56842625533568e-16)) - 6.79551024891847e-15)));
	fConst55 = ((fConst1 * (7.54371397360606e-15 + (fConst1 * (2.82449852733007e-16 + (fConst1 * (0 - (1.14357087642182e-19 + fConst46))))))) - 6.60635170699196e-14);
	fConst56 = (fConst1 * ((fConst1 * ((fConst1 * (1.397748316461e-19 + fConst48)) - 2.81905136399941e-16)) - 3.51293691725028e-15));
	fConst57 = ((fConst1 * (5.62069838385272e-15 + (fConst1 * (2.94921699050911e-16 + (fConst1 * (0 - (1.40122718726421e-19 + fConst50))))))) - 2.58304185091932e-14);
	fConst58 = (1.1408637802285e-13 + (fConst1 * (4.14135154627774e-15 + (fConst1 * ((fConst1 * (0 - (1.84313451157674e-19 + fConst28))) - 1.4867852143994e-16)))));
	fConst59 = (fConst1 * ((fConst1 * (1.70486053448624e-16 + (fConst1 * (2.80945197437672e-19 + fConst30)))) - 2.12307123308889e-15));
	fConst60 = (4.68324536710785e-14 + (fConst1 * (3.39775512445924e-15 + (fConst1 * ((fConst1 * (0 - (2.82829852194005e-19 + fConst32))) - 1.78421312766784e-16)))));
	fConst61 = ((fConst1 * ((fConst1 * (1.41224926366503e-16 + (fConst1 * (1.71535631463274e-19 + fConst34)))) - 3.77185698680303e-15)) - 9.90952756048795e-14);
	fConst62 = (fConst1 * (1.75646845862514e-15 + (fConst1 * ((fConst1 * (0 - (2.09662247469149e-19 + fConst36))) - 1.4095256819997e-16))));
	fConst63 = ((fConst1 * ((fConst1 * (1.47460849525455e-16 + (fConst1 * (2.10184078089632e-19 + fConst38)))) - 2.81034919192636e-15)) - 3.87456277637898e-14);
	fConst64 = (2.03624719512197e-28 * fConst1);
	fConst65 = (1.23525177556824e-17 + (fConst1 * (4.02356549528453e-22 + fConst64)));
	fConst66 = (2.03624719512197e-26 * fConst1);
	fConst67 = (1.23525177556824e-15 + (fConst1 * (4.02356549528453e-20 + fConst66)));
	fConst68 = (1.9757204247131e-26 * fConst1);
	fConst69 = (2.68904213585766e-17 + (fConst1 * (0 - (3.78902721530964e-20 + fConst68))));
	fConst70 = (1.9757204247131e-28 * fConst1);
	fConst71 = (2.68904213585766e-19 + (fConst1 * (0 - (3.78902721530964e-22 + fConst70))));
	fConst72 = (4.07249439024394e-28 * fConst1);
	fConst73 = (2.47050355113649e-17 + (fConst1 * (0 - (2.68237699685635e-22 + fConst72))));
	fConst74 = (4.07249439024394e-26 * fConst1);
	fConst75 = (2.47050355113649e-15 + (fConst1 * (0 - (2.68237699685635e-20 + fConst74))));
	fConst76 = (3.9514408494262e-26 * fConst1);
	fConst77 = (5.37808427171532e-17 + (fConst1 * (2.52601814353976e-20 + fConst76)));
	fConst78 = (3.9514408494262e-28 * fConst1);
	fConst79 = (5.37808427171532e-19 + (fConst1 * (2.52601814353976e-22 + fConst78)));
	fConst80 = ((fConst1 * (fConst74 - 2.68237699685635e-20)) - 2.47050355113649e-15);
	fConst81 = ((fConst1 * (2.52601814353976e-20 - fConst76)) - 5.37808427171532e-17);
	fConst82 = ((fConst1 * (2.52601814353976e-22 - fConst78)) - 5.37808427171532e-19);
	fConst83 = ((fConst1 * (fConst72 - 2.68237699685635e-22)) - 2.47050355113649e-17);
	fConst84 = ((fConst1 * (4.02356549528453e-22 - fConst64)) - 1.23525177556824e-17);
	fConst85 = ((fConst1 * (4.02356549528453e-20 - fConst66)) - 1.23525177556824e-15);
	fConst86 = ((fConst1 * (fConst68 - 3.78902721530964e-20)) - 2.68904213585766e-17);
	fConst87 = ((fConst1 * (fConst70 - 3.78902721530964e-22)) - 2.68904213585766e-19);
	fConst88 = (1.23525177556824e-17 + (fConst1 * (fConst14 - 1.34118849842818e-22)));
	fConst89 = (1.23525177556824e-15 + (fConst1 * (fConst16 - 1.34118849842818e-20)));
	fConst90 = (2.68904213585766e-17 + (fConst1 * (1.26300907176988e-20 - fConst18)));
	fConst91 = (2.68904213585766e-19 + (fConst1 * (1.26300907176988e-22 - fConst20)));
	fConst92 = faustpower<3>(fConst1);
	fConst93 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst94 = (1 + fConst93);
	fConst95 = (0.027 / fConst94);
	fConst96 = (0 - ((1 - fConst93) / fConst94));
	fConst97 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst98 = (0 - fConst97);
	fConst99 = (1 + fConst97);
	fConst100 = (0.025 / fConst99);
	fConst101 = (0 - ((1 - fConst97) / fConst99));
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlow0 = (0.007000000000000006 * double(fslider0));
	double 	fSlow1 = (0.007000000000000006 * double(fslider1));
	for (int i=0; i<count; i++) {
		double fTemp0 = (2.0 * fRec3[1]);
		double fTemp1 = (2.0 * fRec7[1]);
		double fTemp2 = (2.0 * fRec11[1]);
		fRec12[0] = ((0.993 * fRec12[1]) + fSlow0);
		fRec13[0] = ((0.993 * fRec13[1]) + fSlow1);
		double fTemp3 = (1.14785425664408e-13 + ((fRec13[0] * ((fConst1 * ((fRec12[0] * (fConst13 + (fConst11 * fRec12[0]))) + fConst9)) - 9.49647739308574e-14)) + (fConst1 * ((fRec12[0] * (fConst7 + (fConst5 * fRec12[0]))) + fConst3))));
		fRec14[0] = ((double)input0[i] - ((((((fRec14[1] * (5.7392712832204e-13 + ((fRec13[0] * ((fConst1 * ((fRec12[0] * (fConst63 + (fConst62 * fRec12[0]))) + fConst61)) - 4.74823869654287e-13)) + (fConst1 * ((fRec12[0] * (fConst60 + (fConst59 * fRec12[0]))) + fConst58))))) + (fRec14[2] * (1.14785425664408e-12 + ((fRec13[0] * ((fConst1 * ((fRec12[0] * (fConst57 + (fConst56 * fRec12[0]))) + fConst55)) - 9.49647739308574e-13)) + (fConst1 * ((fRec12[0] * (fConst54 + (fConst53 * fRec12[0]))) + fConst52)))))) + (fRec14[3] * (1.14785425664408e-12 + ((fRec13[0] * ((fConst1 * ((fRec12[0] * (fConst51 + (fConst49 * fRec12[0]))) + fConst47)) - 9.49647739308574e-13)) + (fConst1 * ((fRec12[0] * (fConst45 + (fConst43 * fRec12[0]))) + fConst41)))))) + (fRec14[4] * (5.7392712832204e-13 + ((fRec13[0] * ((fConst1 * ((fRec12[0] * (fConst39 + (fConst37 * fRec12[0]))) + fConst35)) - 4.74823869654287e-13)) + (fConst1 * ((fRec12[0] * (fConst33 + (fConst31 * fRec12[0]))) + fConst29)))))) + (fRec14[5] * (1.14785425664408e-13 + ((fRec13[0] * ((fConst1 * ((fRec12[0] * (fConst27 + (fConst26 * fRec12[0]))) + fConst25)) - 9.49647739308574e-14)) + (fConst1 * ((fRec12[0] * (fConst24 + (fConst23 * fRec12[0]))) + fConst22)))))) / fTemp3));
		fRec11[0] = ((fConst92 * (((((((fRec14[0] * (((fRec13[0] * (fConst91 + (fConst90 * fRec12[0]))) + (fConst89 * fRec12[0])) + fConst88)) + (fRec14[1] * (((fRec13[0] * (fConst87 + (fConst86 * fRec12[0]))) + (fConst85 * fRec12[0])) + fConst84))) + (fRec14[2] * (fConst83 + ((fRec13[0] * (fConst82 + (fConst81 * fRec12[0]))) + (fConst80 * fRec12[0]))))) + (fRec14[3] * (((fRec13[0] * (fConst79 + (fConst77 * fRec12[0]))) + (fConst75 * fRec12[0])) + fConst73))) + (fRec14[4] * (((fRec13[0] * (fConst71 + (fConst69 * fRec12[0]))) + (fConst67 * fRec12[0])) + fConst65))) + (fRec14[5] * (((fRec13[0] * (fConst21 + (fConst19 * fRec12[0]))) + (fConst17 * fRec12[0])) + fConst15))) / fTemp3)) - (fTemp2 + fRec11[2]));
		double fTemp4 = (fRec11[2] + (fRec11[0] + fTemp2));
		fVec0[0] = fTemp4;
		fRec10[0] = ((1.0000000000000002 * (fVec0[0] + fVec0[1])) - (0.9999999999999998 * fRec10[1]));
		fRec15[0] = ((fConst96 * fRec15[1]) + (fConst95 * (fRec9[1] + fRec9[2])));
		fRec9[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec15[0] + fRec10[0]) - 3.571981)) - 117.70440740740739);
		fRec8[0] = ((fConst101 * fRec8[1]) + (fConst100 * ((fConst97 * fRec9[0]) + (fConst98 * fRec9[1]))));
		fRec7[0] = (fRec8[0] - (fTemp1 + fRec7[2]));
		double fTemp5 = (fRec7[2] + (fRec7[0] + fTemp1));
		fVec1[0] = fTemp5;
		fRec6[0] = ((1.0000000000000002 * (fVec1[0] + fVec1[1])) - (0.9999999999999998 * fRec6[1]));
		fRec16[0] = ((fConst96 * fRec16[1]) + (fConst95 * (fRec5[1] + fRec5[2])));
		fRec5[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec16[0] + fRec6[0]) - 3.571981)) - 117.70440740740739);
		fRec4[0] = ((fConst101 * fRec4[1]) + (fConst100 * ((fConst97 * fRec5[0]) + (fConst98 * fRec5[1]))));
		fRec3[0] = (fRec4[0] - (fTemp0 + fRec3[2]));
		double fTemp6 = (fRec3[2] + (fRec3[0] + fTemp0));
		fVec2[0] = fTemp6;
		fRec2[0] = ((1.0000000000000002 * (fVec2[0] + fVec2[1])) - (0.9999999999999998 * fRec2[1]));
		fRec17[0] = ((fConst96 * fRec17[1]) + (fConst95 * (fRec1[1] + fRec1[2])));
		fRec1[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec17[0] + fRec2[0]) - 3.571981)) - 117.70440740740739);
		fRec0[0] = ((fConst101 * fRec0[1]) + (fConst100 * ((fConst97 * fRec1[0]) + (fConst98 * fRec1[1]))));
		output0[i] = (FAUSTFLOAT)fRec0[0];
		// post processing
		fRec0[1] = fRec0[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec17[1] = fRec17[0];
		fRec2[1] = fRec2[0];
		fVec2[1] = fVec2[0];
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec16[1] = fRec16[0];
		fRec6[1] = fRec6[0];
		fVec1[1] = fVec1[0];
		fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec15[1] = fRec15[0];
		fRec10[1] = fRec10[0];
		fVec0[1] = fVec0[0];
		fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
		for (int i=5; i>0; i--) fRec14[i] = fRec14[i-1];
		fRec13[1] = fRec13[0];
		fRec12[1] = fRec12[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("susta.Sustain",N_("Sustain"),"S","",&fslider0, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("susta.Volume",N_("Volume"),"S","",&fslider1, 0.5, 0.0, 1.0, 0.01);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
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
