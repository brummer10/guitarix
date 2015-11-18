// generated from file '../src/LV2/faust/muff.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "trany.h"

namespace muff {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
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
	double 	fConst14;
	double 	fConst15;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec13[2];
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
	double 	fRec14[7];
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
	double 	fRec11[3];
	double 	fVec0[2];
	double 	fRec10[2];
	double 	fConst72;
	double 	fConst73;
	double 	fConst74;
	double 	fConst75;
	double 	fRec15[2];
	double 	fRec9[3];
	double 	fConst76;
	double 	fConst77;
	double 	fConst78;
	double 	fConst79;
	double 	fConst80;
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
	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(uint32_t samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(uint32_t samplingFreq, PluginLV2*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginLV2() {
	version = PLUGINLV2_VERSION;
	id = "muff";
	name = N_("Muff");
	mono_audio = compute_static;
	stereo_audio = 0;
	set_samplerate = init_static;
	activate_plugin = 0;
	connect_ports = connect_static;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<7; i++) fRec14[i] = 0;
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

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
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

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
	double 	fSlow0 = (0.007000000000000006 * double(fslider0));
	double 	fSlow1 = (0.007000000000000006 * double(fslider1));
	for (int i=0; i<count; i++) {
		double fTemp0 = (2.0 * fRec3[1]);
		double fTemp1 = (2.0 * fRec7[1]);
		double fTemp2 = (2.0 * fRec11[1]);
		fRec12[0] = ((0.993 * fRec12[1]) + fSlow0);
		double fTemp3 = (3.91224189243262e-14 + (fConst1 * ((fRec12[0] * (fConst7 + (fConst5 * fRec12[0]))) + fConst3)));
		fRec13[0] = ((0.993 * fRec13[1]) + fSlow1);
		fRec14[0] = ((double)input0[i] - (((((((fRec14[1] * (2.34734513545957e-13 + (fConst1 * ((fRec12[0] * (fConst40 + (fConst39 * fRec12[0]))) + fConst38)))) + (fRec14[2] * (5.86836283864892e-13 + (fConst1 * ((fRec12[0] * (fConst37 + (fConst36 * fRec12[0]))) + fConst35))))) + (fRec14[3] * (7.82448378486523e-13 + (fConst20 * ((fRec12[0] * (fConst34 + (fConst33 * fRec12[0]))) + fConst32))))) + (fRec14[4] * (5.86836283864892e-13 + (fConst1 * ((fRec12[0] * (fConst31 + (fConst29 * fRec12[0]))) + fConst27))))) + (fRec14[5] * (2.34734513545957e-13 + (fConst1 * ((fRec12[0] * (fConst25 + (fConst23 * fRec12[0]))) + fConst21))))) + (fRec14[6] * (3.91224189243262e-14 + (fConst1 * ((fRec12[0] * (fConst18 + (fConst17 * fRec12[0]))) + fConst16))))) / fTemp3));
		fRec11[0] = ((fConst71 * ((((((((fRec14[0] * (((fRec13[0] * (fConst70 + (fConst69 * fRec12[0]))) + (fConst68 * fRec12[0])) + fConst67)) + (fConst1 * (fRec14[1] * (fConst66 + ((fRec13[0] * (fConst65 + (fConst64 * fRec12[0]))) + (fConst63 * fRec12[0])))))) + (fRec14[2] * (((fRec13[0] * (fConst62 + (fConst61 * fRec12[0]))) + (fConst60 * fRec12[0])) + fConst59))) + (fConst1 * (fRec14[3] * (3.50493411219602e-21 + ((fRec13[0] * (1.59315186918001e-19 + (fConst58 * fRec12[0]))) + (fConst57 * fRec12[0])))))) + (fRec14[4] * (((fRec13[0] * (fConst56 + (fConst54 * fRec12[0]))) + (fConst52 * fRec12[0])) + fConst50))) + (fConst1 * (fRec14[5] * (((fRec13[0] * (fConst48 + (fConst46 * fRec12[0]))) + (fConst44 * fRec12[0])) + fConst42)))) + (fRec14[6] * (((fRec13[0] * (fConst15 + (fConst13 * fRec12[0]))) + (fConst11 * fRec12[0])) + fConst9))) / fTemp3)) - (fTemp2 + fRec11[2]));
		double fTemp4 = (fRec11[2] + (fRec11[0] + fTemp2));
		fVec0[0] = fTemp4;
		fRec10[0] = ((1.0000000000000002 * (fVec0[0] + fVec0[1])) - (0.9999999999999998 * fRec10[1]));
		fRec15[0] = ((fConst75 * fRec15[1]) + (fConst74 * (fRec9[1] + fRec9[2])));
		fRec9[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec15[0] + fRec10[0]) - 3.571981)) - 117.70440740740739);
		fRec8[0] = ((fConst80 * fRec8[1]) + (fConst79 * ((fConst76 * fRec9[0]) + (fConst77 * fRec9[1]))));
		fRec7[0] = (fRec8[0] - (fTemp1 + fRec7[2]));
		double fTemp5 = (fRec7[2] + (fRec7[0] + fTemp1));
		fVec1[0] = fTemp5;
		fRec6[0] = ((1.0000000000000002 * (fVec1[0] + fVec1[1])) - (0.9999999999999998 * fRec6[1]));
		fRec16[0] = ((fConst75 * fRec16[1]) + (fConst74 * (fRec5[1] + fRec5[2])));
		fRec5[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec16[0] + fRec6[0]) - 3.571981)) - 117.70440740740739);
		fRec4[0] = ((fConst80 * fRec4[1]) + (fConst79 * ((fConst76 * fRec5[0]) + (fConst77 * fRec5[1]))));
		fRec3[0] = (fRec4[0] - (fTemp0 + fRec3[2]));
		double fTemp6 = (fRec3[2] + (fRec3[0] + fTemp0));
		fVec2[0] = fTemp6;
		fRec2[0] = ((1.0000000000000002 * (fVec2[0] + fVec2[1])) - (0.9999999999999998 * fRec2[1]));
		fRec17[0] = ((fConst75 * fRec17[1]) + (fConst74 * (fRec1[1] + fRec1[2])));
		fRec1[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec17[0] + fRec2[0]) - 3.571981)) - 117.70440740740739);
		fRec0[0] = ((fConst80 * fRec0[1]) + (fConst79 * ((fConst76 * fRec1[0]) + (fConst77 * fRec1[1]))));
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
		for (int i=6; i>0; i--) fRec14[i] = fRec14[i-1];
		fRec13[1] = fRec13[0];
		fRec12[1] = fRec12[0];
	}
#undef fslider0
#undef fslider1
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case TONE: 
		fslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case VOLUME: 
		fslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
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
   TONE, 
   VOLUME, 
} PortIndex;
*/

} // end namespace muff
