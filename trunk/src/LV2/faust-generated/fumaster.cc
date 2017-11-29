// generated from file '../src/LV2/faust/fumaster.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)

#include "trany.h"

namespace fumaster {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec12[2];
	double 	fConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	double 	fConst9;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec13[2];
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
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec14[7];
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
	double 	fVec0[2];
	double 	fConst64;
	double 	fRec11[2];
	double 	fRec10[3];
	double 	fConst65;
	double 	fConst66;
	double 	fConst67;
	double 	fConst68;
	double 	fRec15[2];
	double 	fRec9[3];
	double 	fConst69;
	double 	fConst70;
	double 	fConst71;
	double 	fConst72;
	double 	fConst73;
	double 	fRec8[2];
	double 	fRec7[2];
	double 	fRec6[3];
	double 	fRec16[2];
	double 	fRec5[3];
	double 	fRec4[2];
	double 	fRec3[2];
	double 	fRec2[3];
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
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<7; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<3; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<3; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
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
	fConst0 = min(1.92e+05, max(1.0, (double)fSamplingFreq));
	fConst1 = double(fConst0);
	fConst2 = (1.00799506674223e-28 * fConst1);
	fConst3 = ((fConst1 * ((fConst1 * ((fConst1 * (0 - (2.59175366383786e-25 + fConst2))) - 4.35259230096405e-22)) - 1.02583553103419e-19)) - 2.16974948431515e-18);
	fConst4 = (1.5016846937505e-31 * fConst1);
	fConst5 = (5.11414335446406e-17 + (fConst1 * (2.16655787499057e-19 + (fConst1 * (1.27917670111645e-22 + (fConst1 * (4.96235474586462e-26 - fConst4)))))));
	fConst6 = (1.00949675143598e-28 * fConst1);
	fConst7 = (3.94912717206244e-15 + (fConst1 * (7.52873102578757e-17 + (fConst1 * (3.72110810064138e-19 + (fConst1 * (5.95381363906935e-22 + (fConst1 * (3.20513868924941e-25 + fConst6)))))))));
	fConst8 = (1.41775270516311e-29 * fConst1);
	fConst9 = (4.71779589725812e-24 + fConst8);
	fConst10 = (1.41775270516311e-27 * fConst1);
	fConst11 = (0 - (4.71779589725812e-22 + fConst10));
	fConst12 = (4.70999825737972e-24 + fConst8);
	fConst13 = ((fConst1 * (4.70999825737972e-22 + fConst10)) - 2.59478774349197e-19);
	fConst14 = ((fConst1 * (1.02583553103419e-19 + (fConst1 * ((fConst1 * (2.59175366383786e-25 - fConst2)) - 4.35259230096405e-22)))) - 2.16974948431515e-18);
	fConst15 = (5.11414335446406e-17 + (fConst1 * ((fConst1 * (1.27917670111645e-22 + (fConst1 * (0 - (4.96235474586462e-26 + fConst4))))) - 2.16655787499057e-19)));
	fConst16 = ((fConst1 * (7.52873102578757e-17 + (fConst1 * ((fConst1 * (5.95381363906935e-22 + (fConst1 * (fConst6 - 3.20513868924941e-25)))) - 3.72110810064138e-19)))) - 3.94912717206244e-15);
	fConst17 = (6.0479704004534e-28 * fConst1);
	fConst18 = faustpower<2>(fConst1);
	fConst19 = ((fConst18 * (8.70518460192809e-22 + (fConst1 * (fConst17 - 1.03670146553514e-24)))) - 4.3394989686303e-18);
	fConst20 = (9.01010816250298e-31 * fConst1);
	fConst21 = (1.02282867089281e-16 + (fConst18 * ((fConst1 * (1.98494189834585e-25 + fConst20)) - 2.5583534022329e-22)));
	fConst22 = (6.0569805086159e-28 * fConst1);
	fConst23 = ((fConst1 * (1.50574620515751e-16 + (fConst18 * ((fConst1 * (1.28205547569977e-24 - fConst22)) - 1.19076272781387e-21)))) - 1.57965086882498e-14);
	fConst24 = (1.51199260011335e-27 * fConst1);
	fConst25 = (2.16974948431515e-18 + (fConst1 * ((fConst1 * (4.35259230096405e-22 + (fConst1 * (1.29587683191893e-24 - fConst24)))) - 3.07750659310257e-19)));
	fConst26 = (2.25252704062574e-30 * fConst1);
	fConst27 = ((fConst1 * (6.4996736249717e-19 + (fConst1 * ((fConst1 * (0 - (2.48117737293231e-25 + fConst26))) - 1.27917670111645e-22)))) - 5.11414335446406e-17);
	fConst28 = (1.51424512715397e-27 * fConst1);
	fConst29 = ((fConst1 * ((fConst1 * (1.11633243019242e-18 + (fConst1 * ((fConst1 * (fConst28 - 1.60256934462471e-24)) - 5.95381363906935e-22)))) - 7.52873102578757e-17)) - 1.97456358603122e-14);
	fConst30 = (8.6789979372606e-18 + (fConst18 * ((2.01599013348447e-27 * fConst18) - 1.74103692038562e-21)));
	fConst31 = ((fConst18 * (5.11670680446579e-22 + (3.00336938750099e-30 * fConst18))) - 2.04565734178562e-16);
	fConst32 = ((fConst18 * (2.38152545562774e-21 - (2.01899350287197e-27 * fConst18))) - 3.01149241031503e-16);
	fConst33 = (2.16974948431515e-18 + (fConst1 * (3.07750659310257e-19 + (fConst1 * (4.35259230096405e-22 + (fConst1 * (0 - (1.29587683191893e-24 + fConst24))))))));
	fConst34 = ((fConst1 * ((fConst1 * ((fConst1 * (2.48117737293231e-25 - fConst26)) - 1.27917670111645e-22)) - 6.4996736249717e-19)) - 5.11414335446406e-17);
	fConst35 = (1.97456358603122e-14 + (fConst1 * ((fConst1 * ((fConst1 * ((fConst1 * (1.60256934462471e-24 + fConst28)) - 5.95381363906935e-22)) - 1.11633243019242e-18)) - 7.52873102578757e-17)));
	fConst36 = ((fConst18 * (8.70518460192809e-22 + (fConst1 * (1.03670146553514e-24 + fConst17)))) - 4.3394989686303e-18);
	fConst37 = (1.02282867089281e-16 + (fConst18 * ((fConst1 * (fConst20 - 1.98494189834585e-25)) - 2.5583534022329e-22)));
	fConst38 = (1.57965086882498e-14 + (fConst1 * (1.50574620515751e-16 + (fConst18 * ((fConst1 * (0 - (1.28205547569977e-24 + fConst22))) - 1.19076272781387e-21)))));
	fConst39 = (8.50651623097868e-27 * fConst1);
	fConst40 = (1.88711835890325e-21 + fConst39);
	fConst41 = (8.50651623097868e-29 * fConst1);
	fConst42 = (1.88711835890325e-23 + fConst41);
	fConst43 = (0 - (1.88399930295189e-23 + fConst41));
	fConst44 = (5.18957548698393e-19 + (fConst1 * (0 - (1.88399930295189e-21 + fConst39))));
	fConst45 = (2.12662905774467e-28 * fConst1);
	fConst46 = (2.35889794862906e-23 + fConst45);
	fConst47 = (2.12662905774467e-26 * fConst1);
	fConst48 = (0 - (2.35889794862906e-21 + fConst47));
	fConst49 = (2.35499912868986e-23 + fConst45);
	fConst50 = (2.59478774349197e-19 + (fConst1 * (2.35499912868986e-21 + fConst47)));
	fConst51 = (0 - (1.03791509739679e-18 + (2.83550541032623e-26 * fConst18)));
	fConst52 = (2.35889794862906e-21 - fConst47);
	fConst53 = (2.35889794862906e-23 - fConst45);
	fConst54 = (fConst45 - 2.35499912868986e-23);
	fConst55 = (2.59478774349197e-19 + (fConst1 * (fConst47 - 2.35499912868986e-21)));
	fConst56 = (fConst39 - 1.88711835890325e-21);
	fConst57 = (fConst41 - 1.88711835890325e-23);
	fConst58 = (1.88399930295189e-23 - fConst41);
	fConst59 = (5.18957548698393e-19 + (fConst1 * (1.88399930295189e-21 - fConst39)));
	fConst60 = (4.71779589725812e-22 - fConst10);
	fConst61 = (4.71779589725812e-24 - fConst8);
	fConst62 = (fConst8 - 4.70999825737972e-24);
	fConst63 = ((fConst1 * (fConst10 - 4.70999825737972e-22)) - 2.59478774349197e-19);
	fConst64 = (0.9302847925323914 * faustpower<4>(fConst1));
	fConst65 = (1.0 / tan((270.1769682087222 / fConst0)));
	fConst66 = (1 + fConst65);
	fConst67 = (0 - ((1 - fConst65) / fConst66));
	fConst68 = (0.027 / fConst66);
	fConst69 = (1.0 / tan((97.38937226128358 / fConst0)));
	fConst70 = (0 - fConst69);
	fConst71 = (1 + fConst69);
	fConst72 = (0.025 / fConst71);
	fConst73 = (0 - ((1 - fConst69) / fConst71));
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
#define fslider2 (*fslider2_)
	double 	fSlow0 = (0.007000000000000006 * double(fslider0));
	double 	fSlow1 = (0.007000000000000006 * double(fslider1));
	double 	fSlow2 = (0.01 * double(fslider2));
	double 	fSlow3 = (1 - fSlow2);
	for (int i=0; i<count; i++) {
		fRec12[0] = (fSlow0 + (0.993 * fRec12[1]));
		double fTemp0 = (5.42437371078787e-14 + (fConst1 * (fConst7 + (fRec12[0] * (1.08487474215758e-15 + (fConst1 * (fConst5 + (fConst3 * fRec12[0]))))))));
		fRec13[0] = (fSlow1 + (0.993 * fRec13[1]));
		double fTemp1 = (double)input0[i];
		fRec14[0] = ((fSlow2 * fTemp1) - (((((((fRec14[1] * (3.25462422647273e-13 + (fConst1 * (fConst38 + (fRec12[0] * (4.3394989686303e-15 + (fConst1 * (fConst37 + (fConst36 * fRec12[0]))))))))) + (fRec14[2] * (8.13656056618181e-13 + (fConst1 * (fConst35 + (fRec12[0] * (5.42437371078788e-15 + (fConst1 * (fConst34 + (fConst33 * fRec12[0])))))))))) + (fRec14[3] * (1.08487474215758e-12 + (fConst18 * (fConst32 + (fRec12[0] * (fConst31 + (fConst30 * fRec12[0])))))))) + (fRec14[4] * (8.13656056618181e-13 + (fConst1 * (fConst29 + (fRec12[0] * ((fConst1 * (fConst27 + (fConst25 * fRec12[0]))) - 5.42437371078788e-15))))))) + (fRec14[5] * (3.25462422647273e-13 + (fConst1 * (fConst23 + (fRec12[0] * ((fConst1 * (fConst21 + (fConst19 * fRec12[0]))) - 4.3394989686303e-15))))))) + (fRec14[6] * (5.42437371078787e-14 + (fConst1 * (fConst16 + (fRec12[0] * ((fConst1 * (fConst15 + (fConst14 * fRec12[0]))) - 1.08487474215758e-15))))))) / fTemp0));
		double fTemp2 = ((((((((fRec14[0] * (((fConst63 * fRec13[0]) + (fConst1 * (fConst62 + (fRec12[0] * (fConst61 + (fConst60 * fRec13[0])))))) - 2.59478774349197e-21)) + (fRec14[1] * (5.18957548698393e-21 + ((fConst59 * fRec13[0]) + (fConst1 * (fConst58 + (fRec12[0] * (fConst57 + (fConst56 * fRec13[0]))))))))) + (fRec14[2] * (2.59478774349197e-21 + ((fConst55 * fRec13[0]) + (fConst1 * (fConst54 + (fRec12[0] * (fConst53 + (fConst52 * fRec13[0]))))))))) + (fRec14[3] * (((fConst51 * fRec13[0]) + (fConst18 * ((fRec12[0] * (2.83550541032623e-28 + (2.83550541032623e-26 * fRec13[0]))) - 2.83550541032623e-28))) - 1.03791509739679e-20))) + (fRec14[4] * (2.59478774349197e-21 + ((fConst50 * fRec13[0]) + (fConst1 * (fConst49 + (fRec12[0] * ((fConst48 * fRec13[0]) - fConst46)))))))) + (fRec14[5] * (5.18957548698393e-21 + ((fConst44 * fRec13[0]) + (fConst1 * (fConst43 + (fRec12[0] * (fConst42 + (fConst40 * fRec13[0]))))))))) + (fRec14[6] * (((fConst13 * fRec13[0]) + (fConst1 * (fConst12 + (fRec12[0] * ((fConst11 * fRec13[0]) - fConst9))))) - 2.59478774349197e-21))) / fTemp0);
		fVec0[0] = fTemp2;
		fRec11[0] = ((fConst64 * (fVec0[0] + fVec0[1])) - (0.8605695850647829 * fRec11[1]));
		fRec10[0] = (fRec11[0] - ((1.8405051250752198 * fRec10[1]) + (0.8612942439318627 * fRec10[2])));
		fRec15[0] = ((fConst68 * (fRec9[1] + fRec9[2])) + (fConst67 * fRec15[1]));
		fRec9[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec15[0] + (0.9254498422517706 * (fRec10[0] + (fRec10[2] + (2.0 * fRec10[1]))))) - 3.571981)) - 117.70440740740739);
		fRec8[0] = ((fConst73 * fRec8[1]) + (fConst72 * ((fConst69 * fRec9[0]) + (fConst70 * fRec9[1]))));
		fRec7[0] = ((0.9302847925323914 * (fRec8[1] + fRec8[0])) - (0.8605695850647829 * fRec7[1]));
		fRec6[0] = (fRec7[0] - ((1.8405051250752198 * fRec6[1]) + (0.8612942439318627 * fRec6[2])));
		fRec16[0] = ((fConst68 * (fRec5[1] + fRec5[2])) + (fConst67 * fRec16[1]));
		fRec5[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec16[0] + (0.9254498422517706 * (fRec6[0] + (fRec6[2] + (2.0 * fRec6[1]))))) - 3.571981)) - 117.70440740740739);
		fRec4[0] = ((fConst73 * fRec4[1]) + (fConst72 * ((fConst69 * fRec5[0]) + (fConst70 * fRec5[1]))));
		fRec3[0] = ((0.9302847925323914 * (fRec4[1] + fRec4[0])) - (0.8605695850647829 * fRec3[1]));
		fRec2[0] = (fRec3[0] - ((1.8405051250752198 * fRec2[1]) + (0.8612942439318627 * fRec2[2])));
		fRec17[0] = ((fConst68 * (fRec1[1] + fRec1[2])) + (fConst67 * fRec17[1]));
		fRec1[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec17[0] + (0.9254498422517706 * (fRec2[0] + (fRec2[2] + (2.0 * fRec2[1]))))) - 3.571981)) - 117.70440740740739);
		fRec0[0] = ((fConst73 * fRec0[1]) + (fConst72 * ((fConst69 * fRec1[0]) + (fConst70 * fRec1[1]))));
		output0[i] = (FAUSTFLOAT)((fSlow3 * fTemp1) + fRec0[0]);
		// post processing
		fRec0[1] = fRec0[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec17[1] = fRec17[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec16[1] = fRec16[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec15[1] = fRec15[0];
		fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		fVec0[1] = fVec0[0];
		for (int i=6; i>0; i--) fRec14[i] = fRec14[i-1];
		fRec13[1] = fRec13[0];
		fRec12[1] = fRec12[0];
	}
#undef fslider0
#undef fslider1
#undef fslider2
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
	case WET_DRY: 
		fslider2_ = (float*)data; // , 1e+02, 0.0, 1e+02, 1.0 
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
