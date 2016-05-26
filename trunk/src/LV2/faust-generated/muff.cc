// generated from file '../src/LV2/faust/muff.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)


#include "trany.h"

namespace muff {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	double 	fConst0;
	double 	fConst1;
	double 	fConst2;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec0[2];
	double 	fConst3;
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
	double 	fRec1[7];
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
	double 	fConst64;
	double 	fConst65;
	double 	fConst66;
	double 	fConst67;
	double 	fConst68;
	double 	fConst69;
	double 	fConst70;

	int samplingFreq;
	gx_resample::FixedRateResampler smpCl;
	double 	fVecCl0[2];
	double 	fRecCl7[2];
	double 	fRecCl6[3];
	int 	iConstCl0;
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
	FAUSTFLOAT 	*fsliderV0_;
	double 	fRecV0[2];
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
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<7; i++) fRec1[i] = 0;

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

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = double(min(192000, max(1, fSamplingFreq)));
	fConst1 = (4.64196013276193e-29 * fConst0);
	fConst2 = (1.16723639524299e-14 + (fConst0 * (8.93675308928682e-16 + (fConst0 * (3.60543982135142e-18 + (fConst0 * (2.87245155338884e-21 + (fConst0 * (7.1140905248404e-25 + fConst1)))))))));
	fConst3 = (5.75452574944698e-29 * fConst0);
	fConst4 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (0 - (7.27469124190795e-25 + fConst3))) - 2.36761929650589e-21)) - 2.15665382234029e-18)) - 5.3389212423117e-16)) - 3.40686364113531e-15);
	fConst5 = (5.77317651704237e-29 * fConst0);
	fConst6 = (3.33278467477534e-15 + (fConst0 * (5.21709009014916e-16 + (fConst0 * (2.02385759012812e-18 + (fConst0 * (2.5773097315087e-21 + (fConst0 * (7.91492198040202e-25 + fConst5)))))))));
	fConst7 = (3.05635183529265e-28 * fConst0);
	fConst8 = ((fConst0 * (8.76233528049005e-22 + fConst7)) - 4.06318752662282e-18);
	fConst9 = (1.29955117406144e-31 * fConst0);
	fConst10 = (3.19936025718332e-18 + (fConst0 * (1.11415567049164e-24 + (fConst0 * (0 - (3.73173380397863e-25 + fConst9))))));
	fConst11 = (5.90705079118838e-30 * fConst0);
	fConst12 = (1.45425466235606e-16 + (fConst0 * (5.06434395678016e-23 + (fConst0 * (0 - (1.6962426381721e-23 + fConst11))))));
	fConst13 = (1.38925083422393e-26 * fConst0);
	fConst14 = ((fConst0 * (3.98287967295002e-20 + fConst13)) - 1.84690342119219e-16);
	fConst15 = ((fConst0 * (8.93675308928682e-16 + (fConst0 * ((fConst0 * (2.87245155338884e-21 + (fConst0 * (fConst1 - 7.1140905248404e-25)))) - 3.60543982135142e-18)))) - 1.16723639524299e-14);
	fConst16 = (3.40686364113531e-15 + (fConst0 * ((fConst0 * (2.15665382234029e-18 + (fConst0 * ((fConst0 * (7.27469124190795e-25 - fConst3)) - 2.36761929650589e-21)))) - 5.3389212423117e-16)));
	fConst17 = ((fConst0 * (5.21709009014916e-16 + (fConst0 * ((fConst0 * (2.5773097315087e-21 + (fConst0 * (fConst5 - 7.91492198040202e-25)))) - 2.02385759012812e-18)))) - 3.33278467477534e-15);
	fConst18 = (2.78517607965716e-28 * fConst0);
	fConst19 = faustpower<2>(fConst0);
	fConst20 = ((fConst0 * (1.78735061785736e-15 + (fConst19 * ((fConst0 * (2.84563620993616e-24 - fConst18)) - 5.74490310677768e-21)))) - 4.66894558097195e-14);
	fConst21 = (3.45271544966819e-28 * fConst0);
	fConst22 = (1.36274545645413e-14 + (fConst0 * ((fConst19 * (4.73523859301178e-21 + (fConst0 * (fConst21 - 2.90987649676318e-24)))) - 1.06778424846234e-15)));
	fConst23 = (3.46390591022542e-28 * fConst0);
	fConst24 = ((fConst0 * (1.04341801802983e-15 + (fConst19 * ((fConst0 * (3.16596879216081e-24 - fConst23)) - 5.15461946301739e-21)))) - 1.33311386991013e-14);
	fConst25 = (6.96294019914289e-28 * fConst0);
	fConst26 = ((fConst0 * ((fConst0 * (1.08163194640543e-17 + (fConst0 * ((fConst0 * (fConst25 - 3.5570452624202e-24)) - 2.87245155338884e-21)))) - 8.93675308928682e-16)) - 5.83618197621494e-14);
	fConst27 = (8.63178862417047e-28 * fConst0);
	fConst28 = (1.70343182056766e-14 + (fConst0 * (5.3389212423117e-16 + (fConst0 * ((fConst0 * (2.36761929650589e-21 + (fConst0 * (3.63734562095397e-24 - fConst27)))) - 6.46996146702087e-18)))));
	fConst29 = (8.65976477556356e-28 * fConst0);
	fConst30 = ((fConst0 * ((fConst0 * (6.07157277038437e-18 + (fConst0 * ((fConst0 * (fConst29 - 3.95746099020101e-24)) - 2.5773097315087e-21)))) - 5.21709009014916e-16)) - 1.66639233738767e-14);
	fConst31 = ((fConst19 * (1.14898062135554e-20 - (9.28392026552386e-28 * fConst19))) - 3.57470123571473e-15);
	fConst32 = (2.13556849692468e-15 + (fConst19 * ((1.1509051498894e-27 * fConst19) - 9.47047718602356e-21)));
	fConst33 = ((fConst19 * (1.03092389260348e-20 - (1.15463530340847e-27 * fConst19))) - 2.08683603605967e-15);
	fConst34 = (5.83618197621494e-14 + (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (3.5570452624202e-24 + fConst25)) - 2.87245155338884e-21)) - 1.08163194640543e-17)) - 8.93675308928682e-16)));
	fConst35 = ((fConst0 * (5.3389212423117e-16 + (fConst0 * (6.46996146702087e-18 + (fConst0 * (2.36761929650589e-21 + (fConst0 * (0 - (3.63734562095397e-24 + fConst27))))))))) - 1.70343182056766e-14);
	fConst36 = (1.66639233738767e-14 + (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (3.95746099020101e-24 + fConst29)) - 2.5773097315087e-21)) - 6.07157277038437e-18)) - 5.21709009014916e-16)));
	fConst37 = (4.66894558097195e-14 + (fConst0 * (1.78735061785736e-15 + (fConst19 * ((fConst0 * (0 - (2.84563620993616e-24 + fConst18))) - 5.74490310677768e-21)))));
	fConst38 = ((fConst0 * ((fConst19 * (4.73523859301178e-21 + (fConst0 * (2.90987649676318e-24 + fConst21)))) - 1.06778424846234e-15)) - 1.36274545645413e-14);
	fConst39 = (1.33311386991013e-14 + (fConst0 * (1.04341801802983e-15 + (fConst19 * ((fConst0 * (0 - (3.16596879216081e-24 + fConst23))) - 5.15461946301739e-21)))));
	fConst40 = (1.22254073411706e-27 * fConst0);
	fConst41 = (0 - (1.75246705609801e-21 + fConst40));
	fConst42 = (7.79730704436866e-31 * fConst0);
	fConst43 = ((fConst0 * (1.49269352159145e-24 + fConst42)) - 2.22831134098327e-24);
	fConst44 = (3.54423047471303e-29 * fConst0);
	fConst45 = ((fConst0 * (6.78497055268842e-23 + fConst44)) - 1.01286879135603e-22);
	fConst46 = (5.55700333689573e-26 * fConst0);
	fConst47 = (0 - (7.96575934590005e-20 + fConst46));
	fConst48 = (1.52817591764633e-27 * fConst0);
	fConst49 = (1.21895625798685e-17 + (fConst0 * (fConst48 - 8.76233528049005e-22)));
	fConst50 = (1.94932676109216e-30 * fConst0);
	fConst51 = ((fConst0 * ((fConst0 * (0 - (1.86586690198932e-24 + fConst50))) - 1.11415567049164e-24)) - 9.59808077154997e-18);
	fConst52 = (8.86057618678257e-29 * fConst0);
	fConst53 = ((fConst0 * ((fConst0 * (0 - (8.48121319086052e-23 + fConst52))) - 5.06434395678016e-23)) - 4.36276398706817e-16);
	fConst54 = (6.94625417111967e-26 * fConst0);
	fConst55 = (5.54071026357658e-16 + (fConst0 * (fConst54 - 3.98287967295002e-20)));
	fConst56 = (4.45662268196654e-24 + (2.59910234812289e-30 * fConst19));
	fConst57 = (2.02573758271206e-22 + (1.18141015823768e-28 * fConst19));
	fConst58 = ((fConst0 * (0 - (8.76233528049005e-22 + fConst48))) - 1.21895625798685e-17);
	fConst59 = (9.59808077154997e-18 + (fConst0 * ((fConst0 * (1.86586690198932e-24 - fConst50)) - 1.11415567049164e-24)));
	fConst60 = (4.36276398706817e-16 + (fConst0 * ((fConst0 * (8.48121319086052e-23 - fConst52)) - 5.06434395678016e-23)));
	fConst61 = ((fConst0 * (0 - (3.98287967295002e-20 + fConst54))) - 5.54071026357658e-16);
	fConst62 = ((fConst0 * (fConst42 - 1.49269352159145e-24)) - 2.22831134098327e-24);
	fConst63 = ((fConst0 * (fConst44 - 6.78497055268842e-23)) - 1.01286879135603e-22);
	fConst64 = (fConst46 - 7.96575934590005e-20);
	fConst65 = (fConst40 - 1.75246705609801e-21);
	fConst66 = (4.06318752662282e-18 + (fConst0 * (8.76233528049005e-22 - fConst7)));
	fConst67 = ((fConst0 * (1.11415567049164e-24 + (fConst0 * (3.73173380397863e-25 - fConst9)))) - 3.19936025718332e-18);
	fConst68 = ((fConst0 * (5.06434395678016e-23 + (fConst0 * (1.6962426381721e-23 - fConst11)))) - 1.45425466235606e-16);
	fConst69 = (1.84690342119219e-16 + (fConst0 * (3.98287967295002e-20 - fConst13)));
	fConst70 = faustpower<3>(fConst0);

	samplingFreq = 96000;
	smpCl.setup(fSamplingFreq, samplingFreq);
	fSamplingFreq = samplingFreq;
	iConstCl0 = min(192000, max(1, fSamplingFreq));
	fConstCl1 = (1.0 / tan((270.1769682087222 / double(iConstCl0))));
	fConstCl2 = (1 + fConstCl1);
	fConstCl3 = (0.027 / fConstCl2);
	fConstCl4 = (0 - ((1 - fConstCl1) / fConstCl2));
	fConstCl5 = (1.0 / tan((97.38937226128358 / double(iConstCl0))));
	fConstCl6 = (0 - fConstCl5);
	fConstCl7 = (1 + fConstCl5);
	fConstCl8 = (0.025 / fConstCl7);
	fConstCl9 = (0 - ((1 - fConstCl5) / fConstCl7));

	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fslider0 (*fslider0_)
#define fsliderV0 (*fsliderV0_)
	double 	fSlowV0 = (0.0010000000000000009 * double(fsliderV0));

	double 	fSlow0 = (0.007000000000000006 * double(fslider0));
	for (int i=0; i<count; i++) {
		fRec0[0] = ((0.993 * fRec0[1]) + fSlow0);
		double fTemp0 = (3.91224189243262e-14 + (fConst0 * ((fRec0[0] * (fConst6 + (fConst4 * fRec0[0]))) + fConst2)));
		fRec1[0] = ((double)input0[i] - (((((((fRec1[1] * (2.34734513545957e-13 + (fConst0 * ((fRec0[0] * (fConst39 + (fConst38 * fRec0[0]))) + fConst37)))) + (fRec1[2] * (5.86836283864892e-13 + (fConst0 * ((fRec0[0] * (fConst36 + (fConst35 * fRec0[0]))) + fConst34))))) + (fRec1[3] * (7.82448378486523e-13 + (fConst19 * ((fRec0[0] * (fConst33 + (fConst32 * fRec0[0]))) + fConst31))))) + (fRec1[4] * (5.86836283864892e-13 + (fConst0 * ((fRec0[0] * (fConst30 + (fConst28 * fRec0[0]))) + fConst26))))) + (fRec1[5] * (2.34734513545957e-13 + (fConst0 * ((fRec0[0] * (fConst24 + (fConst22 * fRec0[0]))) + fConst20))))) + (fRec1[6] * (3.91224189243262e-14 + (fConst0 * ((fRec0[0] * (fConst17 + (fConst16 * fRec0[0]))) + fConst15))))) / fTemp0));
		output0[i] = (FAUSTFLOAT)(fConst70 * ((((((((fRec1[0] * (((fConst69 + (fConst68 * fRec0[0])) + (fConst67 * fRec0[0])) + fConst66)) + (fConst0 * (fRec1[1] * (fConst65 + ((fConst64 + (fConst63 * fRec0[0])) + (fConst62 * fRec0[0])))))) + (fRec1[2] * (((fConst61 + (fConst60 * fRec0[0])) + (fConst59 * fRec0[0])) + fConst58))) + (fConst0 * (fRec1[3] * (3.50493411219602e-21 + ((1.59315186918001e-19 + (fConst57 * fRec0[0])) + (fConst56 * fRec0[0])))))) + (fRec1[4] * (((fConst55 + (fConst53 * fRec0[0])) + (fConst51 * fRec0[0])) + fConst49))) + (fConst0 * (fRec1[5] * (((fConst47 + (fConst45 * fRec0[0])) + (fConst43 * fRec0[0])) + fConst41)))) + (fRec1[6] * (((fConst14 + (fConst12 * fRec0[0])) + (fConst10 * fRec0[0])) + fConst8))) / fTemp0));
		// post processing
		for (int i=6; i>0; i--) fRec1[i] = fRec1[i-1];
		fRec0[1] = fRec0[0];
	}

	FAUSTFLOAT bufCl[smpCl.max_out_count(count)];
	int ReCount = smpCl.up(count, output0, bufCl);
	for (int i=0; i<ReCount; i++) {
		double fTemp0 = (double)bufCl[i];
		fVecCl0[0] = fTemp0;
		fRecCl7[0] = ((0.9302847925323914 * (fVecCl0[0] + fVecCl0[1])) - (0.8605695850647829 * fRecCl7[1]));
		fRecCl6[0] = (fRecCl7[0] - ((1.8405051250752198 * fRecCl6[1]) + (0.8612942439318627 * fRecCl6[2])));
		fRecCl8[0] = ((fConstCl4 * fRecCl8[1]) + (fConstCl3 * (fRecCl5[1] + fRecCl5[2])));
		fRecCl5[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRecCl8[0] + (0.9254498422517706 * (fRecCl6[2] + (fRecCl6[0] + (2.0 * fRecCl6[1]))))) - 3.571981)) - 117.70440740740739);
		fRecCl4[0] = ((fConstCl9 * fRecCl4[1]) + (fConstCl8 * ((fConstCl5 * fRecCl5[0]) + (fConstCl6 * fRecCl5[1]))));
		fRecCl3[0] = ((0.9302847925323914 * (fRecCl4[0] + fRecCl4[1])) - (0.8605695850647829 * fRecCl3[1]));
		fRecCl2[0] = (fRecCl3[0] - ((1.8405051250752198 * fRecCl2[1]) + (0.8612942439318627 * fRecCl2[2])));
		fRecCl9[0] = ((fConstCl4 * fRecCl9[1]) + (fConstCl3 * (fRecCl1[1] + fRecCl1[2])));
		fRecCl1[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRecCl9[0] + (0.9254498422517706 * (fRecCl2[2] + (fRecCl2[0] + (2.0 * fRecCl2[1]))))) - 3.571981)) - 117.70440740740739);
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

#undef fsliderV0 
#undef fslider0
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
		fsliderV0_ = (float*)data; // , 0.5, 0.0, 1, 0.01 
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
