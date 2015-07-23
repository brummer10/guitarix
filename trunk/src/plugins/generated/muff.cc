// generated from file '../src/plugins/muff.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"
#include "trany.h"

namespace pluginlib {
namespace muff {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	FAUSTFLOAT 	fslider0;
	double 	fRec6[2];
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
	FAUSTFLOAT 	fslider1;
	double 	fRec7[2];
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
	double 	fRec8[7];
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
	double 	fRec9[2];
	double 	fRec5[3];
	double 	fConst76;
	double 	fConst77;
	double 	fConst78;
	double 	fConst79;
	double 	fConst80;
	double 	fRec4[2];
	double 	fRec10[2];
	double 	fRec3[3];
	double 	fRec2[2];
	double 	fRec11[2];
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
	id = "muff";
	name = N_("Muff");
	groups = 0;
	description = N_("Muff"); // description (tooltip)
	category = N_("Fuzz");       // category
	shortname = N_("Muff");     // shortname
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
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<7; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<3; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
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
	fConst2 = (4.64196013276193e-29 * fConst1);
	fConst3 = (1.16723639524299e-14 + (fConst1 * (8.93675308928682e-16 + (fConst1 * (3.60543982135142e-18 + (fConst1 * (2.87245155338884e-21 + (fConst1 * (7.1140905248404e-25 + fConst2)))))))));
	fConst4 = (5.75452574944698e-29 * fConst1);
	fConst5 = ((fConst1 * ((fConst1 * ((fConst1 * ((fConst1 * (0 - (7.27469124190795e-25 + fConst4))) - 2.36761929650589e-21)) - 2.15665382234029e-18)) - 5.3389212423117e-16)) - 3.40686364113531e-15);
	fConst6 = (5.77317651704237e-29 * fConst1);
	fConst7 = (3.33278467477534e-15 + (fConst1 * (5.21709009014916e-16 + (fConst1 * (2.02385759012812e-18 + (fConst1 * (2.5773097315087e-21 + (fConst1 * (7.91492198040202e-25 + fConst6)))))))));
	fConst8 = (3.05635183529265e-28 * fConst1);
	fConst9 = ((fConst1 * (8.76233528049005e-22 + fConst8)) - 4.06318752662282e-18);
	fConst10 = (1.29955117406144e-31 * fConst1);
	fConst11 = (3.19936025718332e-18 + (fConst1 * (1.11415567049164e-24 + (fConst1 * (0 - (3.73173380397863e-25 + fConst10))))));
	fConst12 = (5.90705079118838e-30 * fConst1);
	fConst13 = (1.45425466235606e-16 + (fConst1 * (5.06434395678016e-23 + (fConst1 * (0 - (1.6962426381721e-23 + fConst12))))));
	fConst14 = (1.38925083422393e-26 * fConst1);
	fConst15 = ((fConst1 * (3.98287967295002e-20 + fConst14)) - 1.84690342119219e-16);
	fConst16 = ((fConst1 * (8.93675308928682e-16 + (fConst1 * ((fConst1 * (2.87245155338884e-21 + (fConst1 * (fConst2 - 7.1140905248404e-25)))) - 3.60543982135142e-18)))) - 1.16723639524299e-14);
	fConst17 = (3.40686364113531e-15 + (fConst1 * ((fConst1 * (2.15665382234029e-18 + (fConst1 * ((fConst1 * (7.27469124190795e-25 - fConst4)) - 2.36761929650589e-21)))) - 5.3389212423117e-16)));
	fConst18 = ((fConst1 * (5.21709009014916e-16 + (fConst1 * ((fConst1 * (2.5773097315087e-21 + (fConst1 * (fConst6 - 7.91492198040202e-25)))) - 2.02385759012812e-18)))) - 3.33278467477534e-15);
	fConst19 = (2.78517607965716e-28 * fConst1);
	fConst20 = faustpower<2>(fConst1);
	fConst21 = ((fConst1 * (1.78735061785736e-15 + (fConst20 * ((fConst1 * (2.84563620993616e-24 - fConst19)) - 5.74490310677768e-21)))) - 4.66894558097195e-14);
	fConst22 = (3.45271544966819e-28 * fConst1);
	fConst23 = (1.36274545645413e-14 + (fConst1 * ((fConst20 * (4.73523859301178e-21 + (fConst1 * (fConst22 - 2.90987649676318e-24)))) - 1.06778424846234e-15)));
	fConst24 = (3.46390591022542e-28 * fConst1);
	fConst25 = ((fConst1 * (1.04341801802983e-15 + (fConst20 * ((fConst1 * (3.16596879216081e-24 - fConst24)) - 5.15461946301739e-21)))) - 1.33311386991013e-14);
	fConst26 = (6.96294019914289e-28 * fConst1);
	fConst27 = ((fConst1 * ((fConst1 * (1.08163194640543e-17 + (fConst1 * ((fConst1 * (fConst26 - 3.5570452624202e-24)) - 2.87245155338884e-21)))) - 8.93675308928682e-16)) - 5.83618197621494e-14);
	fConst28 = (8.63178862417047e-28 * fConst1);
	fConst29 = (1.70343182056766e-14 + (fConst1 * (5.3389212423117e-16 + (fConst1 * ((fConst1 * (2.36761929650589e-21 + (fConst1 * (3.63734562095397e-24 - fConst28)))) - 6.46996146702087e-18)))));
	fConst30 = (8.65976477556356e-28 * fConst1);
	fConst31 = ((fConst1 * ((fConst1 * (6.07157277038437e-18 + (fConst1 * ((fConst1 * (fConst30 - 3.95746099020101e-24)) - 2.5773097315087e-21)))) - 5.21709009014916e-16)) - 1.66639233738767e-14);
	fConst32 = ((fConst20 * (1.14898062135554e-20 - (9.28392026552386e-28 * fConst20))) - 3.57470123571473e-15);
	fConst33 = (2.13556849692468e-15 + (fConst20 * ((1.1509051498894e-27 * fConst20) - 9.47047718602356e-21)));
	fConst34 = ((fConst20 * (1.03092389260348e-20 - (1.15463530340847e-27 * fConst20))) - 2.08683603605967e-15);
	fConst35 = (5.83618197621494e-14 + (fConst1 * ((fConst1 * ((fConst1 * ((fConst1 * (3.5570452624202e-24 + fConst26)) - 2.87245155338884e-21)) - 1.08163194640543e-17)) - 8.93675308928682e-16)));
	fConst36 = ((fConst1 * (5.3389212423117e-16 + (fConst1 * (6.46996146702087e-18 + (fConst1 * (2.36761929650589e-21 + (fConst1 * (0 - (3.63734562095397e-24 + fConst28))))))))) - 1.70343182056766e-14);
	fConst37 = (1.66639233738767e-14 + (fConst1 * ((fConst1 * ((fConst1 * ((fConst1 * (3.95746099020101e-24 + fConst30)) - 2.5773097315087e-21)) - 6.07157277038437e-18)) - 5.21709009014916e-16)));
	fConst38 = (4.66894558097195e-14 + (fConst1 * (1.78735061785736e-15 + (fConst20 * ((fConst1 * (0 - (2.84563620993616e-24 + fConst19))) - 5.74490310677768e-21)))));
	fConst39 = ((fConst1 * ((fConst20 * (4.73523859301178e-21 + (fConst1 * (2.90987649676318e-24 + fConst22)))) - 1.06778424846234e-15)) - 1.36274545645413e-14);
	fConst40 = (1.33311386991013e-14 + (fConst1 * (1.04341801802983e-15 + (fConst20 * ((fConst1 * (0 - (3.16596879216081e-24 + fConst24))) - 5.15461946301739e-21)))));
	fConst41 = (1.22254073411706e-27 * fConst1);
	fConst42 = (0 - (1.75246705609801e-21 + fConst41));
	fConst43 = (7.79730704436866e-31 * fConst1);
	fConst44 = ((fConst1 * (1.49269352159145e-24 + fConst43)) - 2.22831134098327e-24);
	fConst45 = (3.54423047471303e-29 * fConst1);
	fConst46 = ((fConst1 * (6.78497055268842e-23 + fConst45)) - 1.01286879135603e-22);
	fConst47 = (5.55700333689573e-26 * fConst1);
	fConst48 = (0 - (7.96575934590005e-20 + fConst47));
	fConst49 = (1.52817591764633e-27 * fConst1);
	fConst50 = (1.21895625798685e-17 + (fConst1 * (fConst49 - 8.76233528049005e-22)));
	fConst51 = (1.94932676109216e-30 * fConst1);
	fConst52 = ((fConst1 * ((fConst1 * (0 - (1.86586690198932e-24 + fConst51))) - 1.11415567049164e-24)) - 9.59808077154997e-18);
	fConst53 = (8.86057618678257e-29 * fConst1);
	fConst54 = ((fConst1 * ((fConst1 * (0 - (8.48121319086052e-23 + fConst53))) - 5.06434395678016e-23)) - 4.36276398706817e-16);
	fConst55 = (6.94625417111967e-26 * fConst1);
	fConst56 = (5.54071026357658e-16 + (fConst1 * (fConst55 - 3.98287967295002e-20)));
	fConst57 = (4.45662268196654e-24 + (2.59910234812289e-30 * fConst20));
	fConst58 = (2.02573758271206e-22 + (1.18141015823768e-28 * fConst20));
	fConst59 = ((fConst1 * (0 - (8.76233528049005e-22 + fConst49))) - 1.21895625798685e-17);
	fConst60 = (9.59808077154997e-18 + (fConst1 * ((fConst1 * (1.86586690198932e-24 - fConst51)) - 1.11415567049164e-24)));
	fConst61 = (4.36276398706817e-16 + (fConst1 * ((fConst1 * (8.48121319086052e-23 - fConst53)) - 5.06434395678016e-23)));
	fConst62 = ((fConst1 * (0 - (3.98287967295002e-20 + fConst55))) - 5.54071026357658e-16);
	fConst63 = ((fConst1 * (fConst43 - 1.49269352159145e-24)) - 2.22831134098327e-24);
	fConst64 = ((fConst1 * (fConst45 - 6.78497055268842e-23)) - 1.01286879135603e-22);
	fConst65 = (fConst47 - 7.96575934590005e-20);
	fConst66 = (fConst41 - 1.75246705609801e-21);
	fConst67 = (4.06318752662282e-18 + (fConst1 * (8.76233528049005e-22 - fConst8)));
	fConst68 = ((fConst1 * (1.11415567049164e-24 + (fConst1 * (3.73173380397863e-25 - fConst10)))) - 3.19936025718332e-18);
	fConst69 = ((fConst1 * (5.06434395678016e-23 + (fConst1 * (1.6962426381721e-23 - fConst12)))) - 1.45425466235606e-16);
	fConst70 = (1.84690342119219e-16 + (fConst1 * (3.98287967295002e-20 - fConst14)));
	fConst71 = faustpower<3>(fConst1);
	fConst72 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst73 = (1 + fConst72);
	fConst74 = (0.027 / fConst73);
	fConst75 = (0 - ((1 - fConst72) / fConst73));
	fConst76 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst77 = (0 - fConst76);
	fConst78 = (1 + fConst76);
	fConst79 = (0.025 / fConst78);
	fConst80 = (0 - ((1 - fConst76) / fConst78));
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
		fRec6[0] = ((0.993 * fRec6[1]) + fSlow0);
		double fTemp0 = (3.91224189243262e-14 + (fConst1 * ((fRec6[0] * (fConst7 + (fConst5 * fRec6[0]))) + fConst3)));
		fRec7[0] = ((0.993 * fRec7[1]) + fSlow1);
		fRec8[0] = ((double)input0[i] - (((((((fRec8[1] * (2.34734513545957e-13 + (fConst1 * ((fRec6[0] * (fConst40 + (fConst39 * fRec6[0]))) + fConst38)))) + (fRec8[2] * (5.86836283864892e-13 + (fConst1 * ((fRec6[0] * (fConst37 + (fConst36 * fRec6[0]))) + fConst35))))) + (fRec8[3] * (7.82448378486523e-13 + (fConst20 * ((fRec6[0] * (fConst34 + (fConst33 * fRec6[0]))) + fConst32))))) + (fRec8[4] * (5.86836283864892e-13 + (fConst1 * ((fRec6[0] * (fConst31 + (fConst29 * fRec6[0]))) + fConst27))))) + (fRec8[5] * (2.34734513545957e-13 + (fConst1 * ((fRec6[0] * (fConst25 + (fConst23 * fRec6[0]))) + fConst21))))) + (fRec8[6] * (3.91224189243262e-14 + (fConst1 * ((fRec6[0] * (fConst18 + (fConst17 * fRec6[0]))) + fConst16))))) / fTemp0));
		fRec9[0] = ((fConst75 * fRec9[1]) + (fConst74 * (fRec5[1] + fRec5[2])));
		fRec5[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec9[0] + (fConst71 * ((((((((fRec8[0] * (((fRec7[0] * (fConst70 + (fConst69 * fRec6[0]))) + (fConst68 * fRec6[0])) + fConst67)) + (fConst1 * (fRec8[1] * (fConst66 + ((fRec7[0] * (fConst65 + (fConst64 * fRec6[0]))) + (fConst63 * fRec6[0])))))) + (fRec8[2] * (((fRec7[0] * (fConst62 + (fConst61 * fRec6[0]))) + (fConst60 * fRec6[0])) + fConst59))) + (fConst1 * (fRec8[3] * (3.50493411219602e-21 + ((fRec7[0] * (1.59315186918001e-19 + (fConst58 * fRec6[0]))) + (fConst57 * fRec6[0])))))) + (fRec8[4] * (((fRec7[0] * (fConst56 + (fConst54 * fRec6[0]))) + (fConst52 * fRec6[0])) + fConst50))) + (fConst1 * (fRec8[5] * (((fRec7[0] * (fConst48 + (fConst46 * fRec6[0]))) + (fConst44 * fRec6[0])) + fConst42)))) + (fRec8[6] * (((fRec7[0] * (fConst15 + (fConst13 * fRec6[0]))) + (fConst11 * fRec6[0])) + fConst9))) / fTemp0))) - 3.571981)) - 117.70440740740739);
		fRec4[0] = ((fConst80 * fRec4[1]) + (fConst79 * ((fConst76 * fRec5[0]) + (fConst77 * fRec5[1]))));
		fRec10[0] = ((fConst75 * fRec10[1]) + (fConst74 * (fRec3[1] + fRec3[2])));
		fRec3[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec10[0] + fRec4[0]) - 3.571981)) - 117.70440740740739);
		fRec2[0] = ((fConst80 * fRec2[1]) + (fConst79 * ((fConst76 * fRec3[0]) + (fConst77 * fRec3[1]))));
		fRec11[0] = ((fConst75 * fRec11[1]) + (fConst74 * (fRec1[1] + fRec1[2])));
		fRec1[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec11[0] + fRec2[0]) - 3.571981)) - 117.70440740740739);
		fRec0[0] = ((fConst80 * fRec0[1]) + (fConst79 * ((fConst76 * fRec1[0]) + (fConst77 * fRec1[1]))));
		output0[i] = (FAUSTFLOAT)fRec0[0];
		// post processing
		fRec0[1] = fRec0[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec11[1] = fRec11[0];
		fRec2[1] = fRec2[0];
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
		fRec10[1] = fRec10[0];
		fRec4[1] = fRec4[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec9[1] = fRec9[0];
		for (int i=6; i>0; i--) fRec8[i] = fRec8[i-1];
		fRec7[1] = fRec7[0];
		fRec6[1] = fRec6[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("muff.Level",N_("Level"),"S","",&fslider1, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("muff.Tone",N_("Tone"),"S","",&fslider0, 0.5, 0.0, 1.0, 0.01);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("muff" "." p)

b.openHorizontalhideBox("");
    b.create_master_slider(PARAM("Tone"), N_("Tone"));
b.closeBox();
b.openHorizontalBox("");

    b.create_small_rackknobr(PARAM("Tone"), N_("Tone"));

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

} // end namespace muff
} // end namespace pluginlib
