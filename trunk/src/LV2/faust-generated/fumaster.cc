// generated from file '../src/LV2/faust/fumaster.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "trany.h"

namespace fumaster {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	double fConst4;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fConst5;
	double fConst6;
	double fConst7;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec13[2];
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
	double fRec12[7];
	double fConst36;
	double fConst37;
	double fConst38;
	double fConst39;
	double fConst40;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec14[2];
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
	double fVec0[2];
	double fRec11[2];
	double fRec10[3];
	double fRec9[2];
	double fRec8[2];
	double fRec7[2];
	double fRec6[3];
	double fRec5[2];
	double fRec4[2];
	double fRec3[2];
	double fRec2[3];
	double fRec1[2];
	double fRec0[2];

	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(uint32_t sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(uint32_t sample_rate, PluginLV2*);
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
	id = "fumaster";
	name = N_("Fuzz Master");
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec13[l0] = 0.0;
	for (int l1 = 0; (l1 < 7); l1 = (l1 + 1)) fRec12[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec14[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fVec0[l3] = 0.0;
	for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) fRec11[l4] = 0.0;
	for (int l5 = 0; (l5 < 3); l5 = (l5 + 1)) fRec10[l5] = 0.0;
	for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) fRec9[l6] = 0.0;
	for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) fRec8[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fRec7[l8] = 0.0;
	for (int l9 = 0; (l9 < 3); l9 = (l9 + 1)) fRec6[l9] = 0.0;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) fRec5[l10] = 0.0;
	for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) fRec4[l11] = 0.0;
	for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) fRec3[l12] = 0.0;
	for (int l13 = 0; (l13 < 3); l13 = (l13 + 1)) fRec2[l13] = 0.0;
	for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) fRec1[l14] = 0.0;
	for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) fRec0[l15] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = (3.1415926535897931 / fConst0);
	fConst2 = (1.0 / (fConst1 + 1.0));
	fConst3 = (1.0 - fConst1);
	fConst4 = (0.93028479253239138 * mydsp_faustpower4_f(fConst0));
	fConst5 = mydsp_faustpower2_f(fConst0);
	fConst6 = (6.0569805086158998e-28 * fConst0);
	fConst7 = ((fConst0 * ((fConst5 * ((fConst0 * (-1.28205547569977e-24 - fConst6)) + -1.19076272781387e-21)) + 1.50574620515751e-16)) + 1.57965086882498e-14);
	fConst8 = (9.0101081625029807e-31 * fConst0);
	fConst9 = ((fConst0 * ((fConst5 * ((fConst0 * (fConst8 + -1.9849418983458499e-25)) + -2.5583534022328998e-22)) + 1.02282867089281e-16)) + 4.3394989686302998e-15);
	fConst10 = (6.0479704004534004e-28 * fConst0);
	fConst11 = (fConst0 * ((fConst5 * ((fConst0 * (fConst10 + 1.0367014655351399e-24)) + 8.7051846019280894e-22)) + -4.3394989686303002e-18));
	fConst12 = (1.5142451271539699e-27 * fConst0);
	fConst13 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst12 + 1.60256934462471e-24)) + -5.9538136390693501e-22)) + -1.11633243019242e-18)) + -7.5287310257875699e-17)) + 1.9745635860312201e-14);
	fConst14 = (2.2525270406257401e-30 * fConst0);
	fConst15 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (2.4811773729323101e-25 - fConst14)) + -1.2791767011164499e-22)) + -6.4996736249717003e-19)) + -5.1141433544640603e-17)) + 5.4243737107878799e-15);
	fConst16 = (1.5119926001133501e-27 * fConst0);
	fConst17 = (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (-1.29587683191893e-24 - fConst16)) + 4.3525923009640504e-22)) + 3.0775065931025701e-19)) + 2.1697494843151501e-18));
	fConst18 = ((fConst5 * (2.38152545562774e-21 - (2.01899350287197e-27 * fConst5))) + -3.0114924103150299e-16);
	fConst19 = ((fConst5 * ((3.0033693875009901e-30 * fConst5) + 5.1167068044657902e-22)) + -2.0456573417856199e-16);
	fConst20 = ((fConst5 * ((2.01599013348447e-27 * fConst5) + -1.7410369203856201e-21)) + 8.6789979372606003e-18);
	fConst21 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst12 + -1.60256934462471e-24)) + -5.9538136390693501e-22)) + 1.11633243019242e-18)) + -7.5287310257875699e-17)) + -1.9745635860312201e-14);
	fConst22 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (-2.4811773729323101e-25 - fConst14)) + -1.2791767011164499e-22)) + 6.4996736249717003e-19)) + -5.1141433544640603e-17)) + -5.4243737107878799e-15);
	fConst23 = (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (1.29587683191893e-24 - fConst16)) + 4.3525923009640504e-22)) + -3.0775065931025701e-19)) + 2.1697494843151501e-18));
	fConst24 = ((fConst0 * ((fConst5 * ((fConst0 * (1.28205547569977e-24 - fConst6)) + -1.19076272781387e-21)) + 1.50574620515751e-16)) + -1.57965086882498e-14);
	fConst25 = ((fConst0 * ((fConst5 * ((fConst0 * (fConst8 + 1.9849418983458499e-25)) + -2.5583534022328998e-22)) + 1.02282867089281e-16)) + -4.3394989686302998e-15);
	fConst26 = (fConst0 * ((fConst5 * ((fConst0 * (fConst10 + -1.0367014655351399e-24)) + 8.7051846019280894e-22)) + -4.3394989686303002e-18));
	fConst27 = (1.00949675143598e-28 * fConst0);
	fConst28 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst27 + -3.2051386892494098e-25)) + 5.9538136390693501e-22)) + -3.7211081006413802e-19)) + 7.5287310257875699e-17)) + -3.9491271720624398e-15);
	fConst29 = (1.5016846937505001e-31 * fConst0);
	fConst30 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (-4.9623547458646202e-26 - fConst29)) + 1.2791767011164499e-22)) + -2.1665578749905701e-19)) + 5.1141433544640603e-17)) + -1.0848747421575801e-15);
	fConst31 = (1.00799506674223e-28 * fConst0);
	fConst32 = (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (2.5917536638378599e-25 - fConst31)) + -4.3525923009640504e-22)) + 1.02583553103419e-19)) + -2.1697494843151501e-18));
	fConst33 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst27 + 3.2051386892494098e-25)) + 5.9538136390693501e-22)) + 3.7211081006413802e-19)) + 7.5287310257875699e-17)) + 3.9491271720624398e-15);
	fConst34 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (4.9623547458646202e-26 - fConst29)) + 1.2791767011164499e-22)) + 2.1665578749905701e-19)) + 5.1141433544640603e-17)) + 1.0848747421575801e-15);
	fConst35 = (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (-2.5917536638378599e-25 - fConst31)) + -4.3525923009640504e-22)) + -1.02583553103419e-19)) + -2.1697494843151501e-18));
	fConst36 = (1.4177527051631099e-29 * fConst0);
	fConst37 = ((fConst0 * (fConst36 + -4.7099982573797203e-24)) + -2.5947877434919699e-21);
	fConst38 = (4.7177958972581202e-24 - fConst36);
	fConst39 = (1.41775270516311e-27 * fConst0);
	fConst40 = (4.7177958972581202e-22 - fConst39);
	fConst41 = ((fConst0 * (fConst39 + -4.7099982573797198e-22)) + -2.59478774349197e-19);
	fConst42 = (8.5065162309786795e-29 * fConst0);
	fConst43 = ((fConst0 * (1.8839993029518899e-23 - fConst42)) + 5.18957548698393e-21);
	fConst44 = (fConst42 + -1.8871183589032501e-23);
	fConst45 = (8.5065162309786799e-27 * fConst0);
	fConst46 = (fConst45 + -1.88711835890325e-21);
	fConst47 = ((fConst0 * (1.8839993029518902e-21 - fConst45)) + 5.1895754869839304e-19);
	fConst48 = (2.1266290577446699e-28 * fConst0);
	fConst49 = ((fConst0 * (fConst48 + -2.3549991286898599e-23)) + 2.5947877434919699e-21);
	fConst50 = (2.3588979486290599e-23 - fConst48);
	fConst51 = (2.1266290577446701e-26 * fConst0);
	fConst52 = (2.3588979486290601e-21 - fConst51);
	fConst53 = ((fConst0 * (fConst51 + -2.3549991286898602e-21)) + 2.59478774349197e-19);
	fConst54 = (-1.0379150973967901e-20 - (2.8355054103262301e-28 * fConst5));
	fConst55 = (-1.0379150973967899e-18 - (2.8355054103262299e-26 * fConst5));
	fConst56 = ((fConst0 * (fConst48 + 2.3549991286898599e-23)) + 2.5947877434919699e-21);
	fConst57 = (-2.3588979486290599e-23 - fConst48);
	fConst58 = (-2.3588979486290601e-21 - fConst51);
	fConst59 = ((fConst0 * (fConst51 + 2.3549991286898602e-21)) + 2.59478774349197e-19);
	fConst60 = ((fConst0 * (-1.8839993029518899e-23 - fConst42)) + 5.18957548698393e-21);
	fConst61 = (fConst42 + 1.8871183589032501e-23);
	fConst62 = (fConst45 + 1.88711835890325e-21);
	fConst63 = ((fConst0 * (-1.8839993029518902e-21 - fConst45)) + 5.1895754869839304e-19);
	fConst64 = ((fConst0 * (fConst36 + 4.7099982573797203e-24)) + -2.5947877434919699e-21);
	fConst65 = (-4.7177958972581202e-24 - fConst36);
	fConst66 = (-4.7177958972581202e-22 - fConst39);
	fConst67 = ((fConst0 * (fConst39 + 4.7099982573797198e-22)) + -2.59478774349197e-19);
	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fVslider0 (*fVslider0_)
#define fVslider1 (*fVslider1_)
#define fVslider2 (*fVslider2_)
	double fSlow0 = (0.01 * double(fVslider0));
	double fSlow1 = (0.0070000000000000062 * double(fVslider1));
	double fSlow2 = (0.0070000000000000062 * double(fVslider2));
	double fSlow3 = (1.0 - fSlow0);
	for (int i = 0; (i < count); i = (i + 1)) {
		double fTemp0 = double(input0[i]);
		fRec13[0] = (fSlow1 + (0.99299999999999999 * fRec13[1]));
		double fTemp1 = ((fConst0 * (fConst33 + (fRec13[0] * (fConst34 + (fConst35 * fRec13[0]))))) + 5.4243737107878698e-14);
		fRec12[0] = ((fSlow0 * fTemp0) - (((((((fRec12[1] * ((fConst0 * (fConst7 + (fRec13[0] * (fConst9 + (fConst11 * fRec13[0]))))) + 3.2546242264727301e-13)) + (fRec12[2] * ((fConst0 * (fConst13 + (fRec13[0] * (fConst15 + (fConst17 * fRec13[0]))))) + 8.1365605661818103e-13))) + (fRec12[3] * ((fConst5 * (fConst18 + (fRec13[0] * (fConst19 + (fConst20 * fRec13[0]))))) + 1.0848747421575801e-12))) + (fRec12[4] * ((fConst0 * (fConst21 + (fRec13[0] * (fConst22 + (fConst23 * fRec13[0]))))) + 8.1365605661818103e-13))) + (fRec12[5] * ((fConst0 * (fConst24 + (fRec13[0] * (fConst25 + (fConst26 * fRec13[0]))))) + 3.2546242264727301e-13))) + (fRec12[6] * ((fConst0 * (fConst28 + (fRec13[0] * (fConst30 + (fConst32 * fRec13[0]))))) + 5.4243737107878698e-14))) / fTemp1));
		fRec14[0] = (fSlow2 + (0.99299999999999999 * fRec14[1]));
		double fTemp2 = ((((((((fRec12[0] * (fConst37 + ((fConst0 * (fRec13[0] * (fConst38 + (fConst40 * fRec14[0])))) + (fConst41 * fRec14[0])))) + (fRec12[1] * (fConst43 + ((fConst0 * (fRec13[0] * (fConst44 + (fConst46 * fRec14[0])))) + (fConst47 * fRec14[0]))))) + (fRec12[2] * (fConst49 + ((fConst0 * (fRec13[0] * (fConst50 + (fConst52 * fRec14[0])))) + (fConst53 * fRec14[0]))))) + (fRec12[3] * (fConst54 + ((fConst5 * (fRec13[0] * ((2.8355054103262299e-26 * fRec14[0]) + 2.8355054103262301e-28))) + (fConst55 * fRec14[0]))))) + (fRec12[4] * (fConst56 + ((fConst0 * (fRec13[0] * (fConst57 + (fConst58 * fRec14[0])))) + (fConst59 * fRec14[0]))))) + (fRec12[5] * (fConst60 + ((fConst0 * (fRec13[0] * (fConst61 + (fConst62 * fRec14[0])))) + (fConst63 * fRec14[0]))))) + (fRec12[6] * (fConst64 + ((fConst0 * (fRec13[0] * (fConst65 + (fConst66 * fRec14[0])))) + (fConst67 * fRec14[0]))))) / fTemp1);
		fVec0[0] = fTemp2;
		fRec11[0] = ((fConst4 * (fTemp2 + fVec0[1])) - (0.86056958506478287 * fRec11[1]));
		fRec10[0] = (fRec11[0] - ((1.8405051250752198 * fRec10[1]) + (0.86129424393186271 * fRec10[2])));
		double fTemp3 = ((1.8508996845035413 * fRec10[1]) + (0.92544984225177063 * (fRec10[0] + fRec10[2])));
		double fTemp4 = double(Ftrany(int(TRANY_TABLE_7199P_68k), double(((fTemp3 + (2700.0 * (fTemp3 / (double(Rtrany(int(TRANY_TABLE_7199P_68k), double(fRec9[1]))) + 100000.0)))) + -3.5719810000000001))));
		fRec9[0] = ((fTemp4 + (0.001322955925925926 * (double(Rtrany(int(TRANY_TABLE_7199P_68k), double(fTemp4))) + 100000.0))) + -250.0);
		fRec8[0] = (fConst2 * ((fConst3 * fRec8[1]) + (0.025000000000000001 * (fRec9[0] - fRec9[1]))));
		fRec7[0] = ((0.93028479253239138 * (fRec8[0] + fRec8[1])) - (0.86056958506478287 * fRec7[1]));
		fRec6[0] = (fRec7[0] - ((1.8405051250752198 * fRec6[1]) + (0.86129424393186271 * fRec6[2])));
		double fTemp5 = ((1.8508996845035413 * fRec6[1]) + (0.92544984225177063 * (fRec6[0] + fRec6[2])));
		double fTemp6 = double(Ftrany(int(TRANY_TABLE_7199P_68k), double(((fTemp5 + (2700.0 * (fTemp5 / (double(Rtrany(int(TRANY_TABLE_7199P_68k), double(fRec5[1]))) + 100000.0)))) + -3.5719810000000001))));
		fRec5[0] = ((fTemp6 + (0.001322955925925926 * (double(Rtrany(int(TRANY_TABLE_7199P_68k), double(fTemp6))) + 100000.0))) + -250.0);
		fRec4[0] = (fConst2 * ((fConst3 * fRec4[1]) + (0.025000000000000001 * (fRec5[0] - fRec5[1]))));
		fRec3[0] = ((0.93028479253239138 * (fRec4[0] + fRec4[1])) - (0.86056958506478287 * fRec3[1]));
		fRec2[0] = (fRec3[0] - ((1.8405051250752198 * fRec2[1]) + (0.86129424393186271 * fRec2[2])));
		double fTemp7 = ((1.8508996845035413 * fRec2[1]) + (0.92544984225177063 * (fRec2[0] + fRec2[2])));
		double fTemp8 = double(Ftrany(int(TRANY_TABLE_7199P_68k), double(((fTemp7 + (2700.0 * (fTemp7 / (double(Rtrany(int(TRANY_TABLE_7199P_68k), double(fRec1[1]))) + 100000.0)))) + -3.5719810000000001))));
		fRec1[0] = ((fTemp8 + (0.001322955925925926 * (double(Rtrany(int(TRANY_TABLE_7199P_68k), double(fTemp8))) + 100000.0))) + -250.0);
		fRec0[0] = (fConst2 * ((fConst3 * fRec0[1]) + (0.025000000000000001 * (fRec1[0] - fRec1[1]))));
		output0[i] = FAUSTFLOAT((fRec0[0] + (fSlow3 * fTemp0)));
		fRec13[1] = fRec13[0];
		for (int j0 = 6; (j0 > 0); j0 = (j0 - 1)) {
			fRec12[j0] = fRec12[(j0 - 1)];
		}
		fRec14[1] = fRec14[0];
		fVec0[1] = fVec0[0];
		fRec11[1] = fRec11[0];
		fRec10[2] = fRec10[1];
		fRec10[1] = fRec10[0];
		fRec9[1] = fRec9[0];
		fRec8[1] = fRec8[0];
		fRec7[1] = fRec7[0];
		fRec6[2] = fRec6[1];
		fRec6[1] = fRec6[0];
		fRec5[1] = fRec5[0];
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
	}
#undef fVslider0
#undef fVslider1
#undef fVslider2
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
		fVslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case VOLUME: 
		fVslider2_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case WET_DRY: 
		fVslider0_ = (float*)data; // , 100.0, 0.0, 100.0, 1.0 
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
   WET_DRY, 
} PortIndex;
*/

} // end namespace fumaster
