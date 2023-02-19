// generated from file '../src/LV2/faust/fumaster.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "trany.h"

namespace fumaster {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec12[2];
	double fConst2;
	double fConst3;
	double fConst5;
	double fConst7;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec13[2];
	double fConst9;
	double fConst11;
	double fConst12;
	double fConst13;
	double fConst14;
	double fConst15;
	double fConst16;
	double fConst17;
	double fConst18;
	double fConst20;
	double fConst22;
	double fConst24;
	double fConst26;
	double fConst28;
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
	double fRec14[7];
	double fConst41;
	double fConst43;
	double fConst44;
	double fConst45;
	double fConst47;
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
	double fVec0[2];
	double fRec11[2];
	double fRec10[3];
	double fRec9[2];
	double fConst68;
	double fConst69;
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec12[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec13[l1] = 0.0;
	for (int l2 = 0; l2 < 7; l2 = l2 + 1) fRec14[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fVec0[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fRec11[l4] = 0.0;
	for (int l5 = 0; l5 < 3; l5 = l5 + 1) fRec10[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fRec9[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec8[l7] = 0.0;
	for (int l8 = 0; l8 < 2; l8 = l8 + 1) fRec7[l8] = 0.0;
	for (int l9 = 0; l9 < 3; l9 = l9 + 1) fRec6[l9] = 0.0;
	for (int l10 = 0; l10 < 2; l10 = l10 + 1) fRec5[l10] = 0.0;
	for (int l11 = 0; l11 < 2; l11 = l11 + 1) fRec4[l11] = 0.0;
	for (int l12 = 0; l12 < 2; l12 = l12 + 1) fRec3[l12] = 0.0;
	for (int l13 = 0; l13 < 3; l13 = l13 + 1) fRec2[l13] = 0.0;
	for (int l14 = 0; l14 < 2; l14 = l14 + 1) fRec1[l14] = 0.0;
	for (int l15 = 0; l15 < 2; l15 = l15 + 1) fRec0[l15] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = 1.00799506674223e-28 * fConst0;
	fConst2 = mydsp_faustpower2_f(fConst0);
	fConst3 = fConst2 * (fConst0 * (fConst0 * (fConst0 * (-2.59175366383786e-25 - fConst1) + -4.35259230096405e-22) + -1.02583553103419e-19) + -2.16974948431515e-18);
	double fConst4 = 1.5016846937505e-31 * fConst0;
	fConst5 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (4.96235474586462e-26 - fConst4) + 1.27917670111645e-22) + 2.16655787499057e-19) + 5.11414335446406e-17) + 1.08487474215758e-15);
	double fConst6 = 1.00949675143598e-28 * fConst0;
	fConst7 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst6 + 3.20513868924941e-25) + 5.95381363906935e-22) + 3.72110810064138e-19) + 7.52873102578757e-17) + 3.94912717206244e-15);
	double fConst8 = 1.41775270516311e-27 * fConst0;
	fConst9 = fConst0 * (fConst8 + 4.70999825737972e-22) + -2.59478774349197e-19;
	double fConst10 = 1.41775270516311e-29 * fConst0;
	fConst11 = fConst0 * (fConst10 + 4.70999825737972e-24) + -2.59478774349197e-21;
	fConst12 = mydsp_faustpower4_f(fConst0);
	fConst13 = -4.71779589725812e-22 - fConst8;
	fConst14 = -4.71779589725812e-24 - fConst10;
	fConst15 = mydsp_faustpower5_f(fConst0);
	fConst16 = fConst2 * (fConst0 * (fConst0 * (fConst0 * (2.59175366383786e-25 - fConst1) + -4.35259230096405e-22) + 1.02583553103419e-19) + -2.16974948431515e-18);
	fConst17 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (-4.96235474586462e-26 - fConst4) + 1.27917670111645e-22) + -2.16655787499057e-19) + 5.11414335446406e-17) + -1.08487474215758e-15);
	fConst18 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst6 + -3.20513868924941e-25) + 5.95381363906935e-22) + -3.72110810064138e-19) + 7.52873102578757e-17) + -3.94912717206244e-15);
	double fConst19 = 6.0479704004534e-28 * fConst0;
	fConst20 = fConst2 * (fConst2 * (fConst0 * (fConst19 + -1.03670146553514e-24) + 8.70518460192809e-22) + -4.3394989686303e-18);
	double fConst21 = 9.01010816250298e-31 * fConst0;
	fConst22 = fConst0 * (fConst0 * (fConst2 * (fConst0 * (fConst21 + 1.98494189834585e-25) + -2.5583534022329e-22) + 1.02282867089281e-16) + -4.3394989686303e-15);
	double fConst23 = 6.0569805086159e-28 * fConst0;
	fConst24 = fConst0 * (fConst0 * (fConst2 * (fConst0 * (1.28205547569977e-24 - fConst23) + -1.19076272781387e-21) + 1.50574620515751e-16) + -1.57965086882498e-14);
	double fConst25 = 1.51199260011335e-27 * fConst0;
	fConst26 = fConst2 * (fConst0 * (fConst0 * (fConst0 * (1.29587683191893e-24 - fConst25) + 4.35259230096405e-22) + -3.07750659310257e-19) + 2.16974948431515e-18);
	double fConst27 = 2.25252704062574e-30 * fConst0;
	fConst28 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (-2.48117737293231e-25 - fConst27) + -1.27917670111645e-22) + 6.4996736249717e-19) + -5.11414335446406e-17) + -5.42437371078788e-15);
	double fConst29 = 1.51424512715397e-27 * fConst0;
	fConst30 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst29 + -1.60256934462471e-24) + -5.95381363906935e-22) + 1.11633243019242e-18) + -7.52873102578757e-17) + -1.97456358603122e-14);
	fConst31 = fConst2 * (2.01599013348447e-27 * fConst2 + -1.74103692038562e-21) + 8.6789979372606e-18;
	fConst32 = fConst2 * (3.00336938750099e-30 * fConst2 + 5.11670680446579e-22) + -2.04565734178562e-16;
	fConst33 = fConst2 * (2.38152545562774e-21 - 2.01899350287197e-27 * fConst2) + -3.01149241031503e-16;
	fConst34 = fConst2 * (fConst0 * (fConst0 * (fConst0 * (-1.29587683191893e-24 - fConst25) + 4.35259230096405e-22) + 3.07750659310257e-19) + 2.16974948431515e-18);
	fConst35 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (2.48117737293231e-25 - fConst27) + -1.27917670111645e-22) + -6.4996736249717e-19) + -5.11414335446406e-17) + 5.42437371078788e-15);
	fConst36 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst29 + 1.60256934462471e-24) + -5.95381363906935e-22) + -1.11633243019242e-18) + -7.52873102578757e-17) + 1.97456358603122e-14);
	fConst37 = fConst2 * (fConst2 * (fConst0 * (fConst19 + 1.03670146553514e-24) + 8.70518460192809e-22) + -4.3394989686303e-18);
	fConst38 = fConst0 * (fConst0 * (fConst2 * (fConst0 * (fConst21 + -1.98494189834585e-25) + -2.5583534022329e-22) + 1.02282867089281e-16) + 4.3394989686303e-15);
	fConst39 = fConst0 * (fConst0 * (fConst2 * (fConst0 * (-1.28205547569977e-24 - fConst23) + -1.19076272781387e-21) + 1.50574620515751e-16) + 1.57965086882498e-14);
	double fConst40 = 8.50651623097868e-27 * fConst0;
	fConst41 = fConst0 * (-1.88399930295189e-21 - fConst40) + 5.18957548698393e-19;
	double fConst42 = 8.50651623097868e-29 * fConst0;
	fConst43 = fConst0 * (-1.88399930295189e-23 - fConst42) + 5.18957548698393e-21;
	fConst44 = fConst40 + 1.88711835890325e-21;
	fConst45 = fConst42 + 1.88711835890325e-23;
	double fConst46 = 2.12662905774467e-26 * fConst0;
	fConst47 = fConst0 * (fConst46 + 2.35499912868986e-21) + 2.59478774349197e-19;
	double fConst48 = 2.12662905774467e-28 * fConst0;
	fConst49 = fConst0 * (fConst48 + 2.35499912868986e-23) + 2.59478774349197e-21;
	fConst50 = -2.35889794862906e-21 - fConst46;
	fConst51 = -2.35889794862906e-23 - fConst48;
	fConst52 = -1.03791509739679e-18 - 2.83550541032623e-26 * fConst2;
	fConst53 = -1.03791509739679e-20 - 2.83550541032623e-28 * fConst2;
	fConst54 = mydsp_faustpower6_f(fConst0);
	fConst55 = fConst0 * (fConst46 + -2.35499912868986e-21) + 2.59478774349197e-19;
	fConst56 = fConst0 * (fConst48 + -2.35499912868986e-23) + 2.59478774349197e-21;
	fConst57 = 2.35889794862906e-21 - fConst46;
	fConst58 = 2.35889794862906e-23 - fConst48;
	fConst59 = fConst0 * (1.88399930295189e-21 - fConst40) + 5.18957548698393e-19;
	fConst60 = fConst0 * (1.88399930295189e-23 - fConst42) + 5.18957548698393e-21;
	fConst61 = fConst40 + -1.88711835890325e-21;
	fConst62 = fConst42 + -1.88711835890325e-23;
	fConst63 = fConst0 * (fConst8 + -4.70999825737972e-22) + -2.59478774349197e-19;
	fConst64 = fConst0 * (fConst10 + -4.70999825737972e-24) + -2.59478774349197e-21;
	fConst65 = 4.71779589725812e-22 - fConst8;
	fConst66 = 4.71779589725812e-24 - fConst10;
	double fConst67 = 3.141592653589793 / fConst0;
	fConst68 = 1.0 - fConst67;
	fConst69 = 1.0 / (fConst67 + 1.0);
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
	double fSlow0 = 0.01 * double(fVslider0);
	double fSlow1 = 1.0 - fSlow0;
	double fSlow2 = 0.007000000000000006 * double(fVslider1);
	double fSlow3 = 0.007000000000000006 * double(fVslider2);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		double fTemp0 = double(input0[i0]);
		fRec12[0] = fSlow2 + 0.993 * fRec12[1];
		double fTemp1 = fConst7 + fRec12[0] * (fConst5 + fConst3 * fRec12[0]) + 5.42437371078787e-14;
		fRec13[0] = fSlow3 + 0.993 * fRec13[1];
		fRec14[0] = fSlow0 * fTemp0 - (fRec14[1] * (fConst39 + fRec12[0] * (fConst38 + fConst37 * fRec12[0]) + 3.25462422647273e-13) + fRec14[2] * (fConst36 + fRec12[0] * (fConst35 + fConst34 * fRec12[0]) + 8.13656056618181e-13) + fRec14[3] * (fConst2 * (fConst33 + fRec12[0] * (fConst32 + fConst31 * fRec12[0])) + 1.08487474215758e-12) + fRec14[4] * (fConst30 + fRec12[0] * (fConst28 + fConst26 * fRec12[0]) + 8.13656056618181e-13) + fRec14[5] * (fConst24 + fRec12[0] * (fConst22 + fConst20 * fRec12[0]) + 3.25462422647273e-13) + fRec14[6] * (fConst18 + fRec12[0] * (fConst17 + fConst16 * fRec12[0]) + 5.42437371078787e-14)) / fTemp1;
		double fTemp2 = (fRec14[0] * (fConst15 * fRec12[0] * (fConst66 + fConst65 * fRec13[0]) + fConst12 * (fConst64 + fConst63 * fRec13[0])) + fRec14[1] * (fConst15 * fRec12[0] * (fConst62 + fConst61 * fRec13[0]) + fConst12 * (fConst60 + fConst59 * fRec13[0])) + fRec14[2] * (fConst15 * fRec12[0] * (fConst58 + fConst57 * fRec13[0]) + fConst12 * (fConst56 + fConst55 * fRec13[0])) + fRec14[3] * (fConst54 * fRec12[0] * (2.83550541032623e-26 * fRec13[0] + 2.83550541032623e-28) + fConst12 * (fConst53 + fConst52 * fRec13[0])) + fRec14[4] * (fConst15 * fRec12[0] * (fConst51 + fConst50 * fRec13[0]) + fConst12 * (fConst49 + fConst47 * fRec13[0])) + fRec14[5] * (fConst15 * fRec12[0] * (fConst45 + fConst44 * fRec13[0]) + fConst12 * (fConst43 + fConst41 * fRec13[0])) + fRec14[6] * (fConst15 * fRec12[0] * (fConst14 + fConst13 * fRec13[0]) + fConst12 * (fConst11 + fConst9 * fRec13[0]))) / fTemp1;
		fVec0[0] = fTemp2;
		fRec11[0] = 0.9302847925323914 * (fTemp2 + fVec0[1]) - 0.8605695850647829 * fRec11[1];
		fRec10[0] = fRec11[0] - (1.8405051250752198 * fRec10[1] + 0.8612942439318627 * fRec10[2]);
		double fTemp3 = 1.8508996845035413 * fRec10[1] + 0.9254498422517706 * (fRec10[0] + fRec10[2]);
		double fTemp4 = Ftrany(TRANY_TABLE_7199P_68k, fTemp3 + 2.7e+03 * (fTemp3 / (Rtrany(TRANY_TABLE_7199P_68k, fRec9[1]) + 1e+05)) + -3.571981);
		fRec9[0] = fTemp4 + 0.001322955925925926 * (Rtrany(TRANY_TABLE_7199P_68k, fTemp4) + 1e+05) + -2.5e+02;
		fRec8[0] = fConst69 * (fConst68 * fRec8[1] + 0.025 * (fRec9[0] - fRec9[1]));
		fRec7[0] = 0.9302847925323914 * (fRec8[0] + fRec8[1]) - 0.8605695850647829 * fRec7[1];
		fRec6[0] = fRec7[0] - (1.8405051250752198 * fRec6[1] + 0.8612942439318627 * fRec6[2]);
		double fTemp5 = 1.8508996845035413 * fRec6[1] + 0.9254498422517706 * (fRec6[0] + fRec6[2]);
		double fTemp6 = Ftrany(TRANY_TABLE_7199P_68k, fTemp5 + 2.7e+03 * (fTemp5 / (Rtrany(TRANY_TABLE_7199P_68k, fRec5[1]) + 1e+05)) + -3.571981);
		fRec5[0] = fTemp6 + 0.001322955925925926 * (Rtrany(TRANY_TABLE_7199P_68k, fTemp6) + 1e+05) + -2.5e+02;
		fRec4[0] = fConst69 * (fConst68 * fRec4[1] + 0.025 * (fRec5[0] - fRec5[1]));
		fRec3[0] = 0.9302847925323914 * (fRec4[0] + fRec4[1]) - 0.8605695850647829 * fRec3[1];
		fRec2[0] = fRec3[0] - (1.8405051250752198 * fRec2[1] + 0.8612942439318627 * fRec2[2]);
		double fTemp7 = 1.8508996845035413 * fRec2[1] + 0.9254498422517706 * (fRec2[0] + fRec2[2]);
		double fTemp8 = Ftrany(TRANY_TABLE_7199P_68k, fTemp7 + 2.7e+03 * (fTemp7 / (Rtrany(TRANY_TABLE_7199P_68k, fRec1[1]) + 1e+05)) + -3.571981);
		fRec1[0] = fTemp8 + 0.001322955925925926 * (Rtrany(TRANY_TABLE_7199P_68k, fTemp8) + 1e+05) + -2.5e+02;
		fRec0[0] = fConst69 * (fConst68 * fRec0[1] + 0.025 * (fRec1[0] - fRec1[1]));
		output0[i0] = FAUSTFLOAT(fRec0[0] + fSlow1 * fTemp0);
		fRec12[1] = fRec12[0];
		fRec13[1] = fRec13[0];
		for (int j0 = 6; j0 > 0; j0 = j0 - 1) {
			fRec14[j0] = fRec14[j0 - 1];
		}
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
		fVslider0_ = (float*)data; // , 1e+02, 0.0, 1e+02, 1.0 
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
