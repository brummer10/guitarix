// generated from file '../src/plugins/ruin.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"
#include "trany.h"

namespace pluginlib {
namespace ruin {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	double 	fConst9;
	double 	fConst10;
	FAUSTFLOAT 	fslider1;
	double 	fRec8[2];
	double 	fConst11;
	double 	fConst12;
	double 	fConst13;
	double 	fConst14;
	FAUSTFLOAT 	fslider2;
	double 	fRec9[2];
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
	double 	fRec10[6];
	double 	fVec0[2];
	double 	fConst61;
	double 	fConst62;
	double 	fConst63;
	double 	fRec7[2];
	double 	fRec6[3];
	double 	fConst64;
	double 	fConst65;
	double 	fConst66;
	double 	fConst67;
	double 	fRec11[2];
	double 	fRec5[3];
	double 	fConst68;
	double 	fConst69;
	double 	fConst70;
	double 	fConst71;
	double 	fConst72;
	double 	fRec4[2];
	double 	fConst73;
	double 	fRec3[2];
	double 	fRec2[3];
	double 	fRec12[2];
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
	id = "ruin";
	name = N_("Ruiner");
	groups = 0;
	description = N_("Devi Ever Dark Boost"); // description (tooltip)
	category = N_("Fuzz");       // category
	shortname = N_("Ruiner");     // shortname
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
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<6; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
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
	fConst1 = tan((50265.48245743669 / double(iConst0)));
	fConst2 = (2 * (1 - (1.0 / faustpower<2>(fConst1))));
	fConst3 = (1.0 / fConst1);
	fConst4 = (1 + ((fConst3 - 1.0000000000000004) / fConst1));
	fConst5 = (1.0 / (1 + ((1.0000000000000004 + fConst3) / fConst1)));
	fConst6 = double(iConst0);
	fConst7 = (2.17193258571938e-24 * fConst6);
	fConst8 = (6.63702362788267e-13 + (fConst6 * (1.70492707442481e-15 + (fConst6 * (4.19596910358881e-18 + (fConst6 * (2.95819574097976e-21 + fConst7)))))));
	fConst9 = (2.80672888565836e-24 * fConst6);
	fConst10 = (5.80512966791183e-13 + (fConst6 * (1.24804042577715e-14 + (fConst6 * (1.48752851885156e-17 + (fConst6 * (1.81905884616603e-20 + fConst9)))))));
	fConst11 = (2.77619078700135e-25 * fConst6);
	fConst12 = (fConst6 * ((fConst6 * ((fConst6 * (0 - (1.77177960077957e-21 + fConst11))) - 1.30282134265895e-18)) - 1.15986606751485e-15));
	fConst13 = (2.74842887913133e-25 * fConst6);
	fConst14 = (5.79933033757426e-14 + (fConst6 * (1.22360789786831e-15 + (fConst6 * (1.45999906472023e-18 + (fConst6 * (1.78182371264179e-21 + fConst13)))))));
	fConst15 = (2.14830127173034e-25 * fConst6);
	fConst16 = ((fConst6 * ((fConst6 * ((fConst6 * (0 - (2.7133044348957e-22 + fConst15))) - 3.93508698145447e-19)) - 1.44426081917549e-16)) - 5.79933033757426e-14);
	fConst17 = (2.12681825901304e-25 * fConst6);
	fConst18 = (6.51446456326455e-14 + (fConst6 * (1.67435306237073e-16 + (fConst6 * (4.11311489819172e-19 + (fConst6 * (2.90100151771978e-22 + fConst17)))))));
	fConst19 = ((fConst6 * (1.70492707442481e-15 + (fConst6 * ((fConst6 * (2.95819574097976e-21 - fConst7)) - 4.19596910358881e-18)))) - 6.63702362788267e-13);
	fConst20 = ((fConst6 * (1.24804042577715e-14 + (fConst6 * ((fConst6 * (1.81905884616603e-20 - fConst9)) - 1.48752851885156e-17)))) - 5.80512966791183e-13);
	fConst21 = (fConst6 * ((fConst6 * (1.30282134265895e-18 + (fConst6 * (fConst11 - 1.77177960077957e-21)))) - 1.15986606751485e-15));
	fConst22 = ((fConst6 * (1.22360789786831e-15 + (fConst6 * ((fConst6 * (1.78182371264179e-21 - fConst13)) - 1.45999906472023e-18)))) - 5.79933033757426e-14);
	fConst23 = (5.79933033757426e-14 + (fConst6 * ((fConst6 * (3.93508698145447e-19 + (fConst6 * (fConst15 - 2.7133044348957e-22)))) - 1.44426081917549e-16)));
	fConst24 = ((fConst6 * (1.67435306237073e-16 + (fConst6 * ((fConst6 * (2.90100151771978e-22 - fConst17)) - 4.11311489819172e-19)))) - 6.51446456326455e-14);
	fConst25 = (1.08596629285969e-23 * fConst6);
	fConst26 = ((fConst6 * (1.70492707442481e-15 + (fConst6 * (4.19596910358881e-18 + (fConst6 * (fConst25 - 8.87458722293927e-21)))))) - 1.9911070883648e-12);
	fConst27 = (1.40336444282918e-23 * fConst6);
	fConst28 = ((fConst6 * (1.24804042577715e-14 + (fConst6 * (1.48752851885156e-17 + (fConst6 * (fConst27 - 5.4571765384981e-20)))))) - 1.74153890037355e-12);
	fConst29 = (1.38809539350067e-24 * fConst6);
	fConst30 = (fConst6 * ((fConst6 * ((fConst6 * (5.31533880233872e-21 - fConst29)) - 1.30282134265895e-18)) - 1.15986606751485e-15));
	fConst31 = (1.37421443956567e-24 * fConst6);
	fConst32 = ((fConst6 * (1.22360789786831e-15 + (fConst6 * (1.45999906472023e-18 + (fConst6 * (fConst31 - 5.34547113792538e-21)))))) - 1.73979910127228e-13);
	fConst33 = (1.07415063586517e-24 * fConst6);
	fConst34 = (1.73979910127228e-13 + (fConst6 * ((fConst6 * ((fConst6 * (8.13991330468709e-22 - fConst33)) - 3.93508698145447e-19)) - 1.44426081917549e-16)));
	fConst35 = (1.06340912950652e-24 * fConst6);
	fConst36 = ((fConst6 * (1.67435306237073e-16 + (fConst6 * (4.11311489819172e-19 + (fConst6 * (fConst35 - 8.70300455315933e-22)))))) - 1.95433936897936e-13);
	fConst37 = (2.17193258571938e-23 * fConst6);
	fConst38 = ((fConst6 * ((fConst6 * (8.39193820717763e-18 + (fConst6 * (5.91639148195952e-21 - fConst37)))) - 3.40985414884961e-15)) - 1.32740472557653e-12);
	fConst39 = (2.80672888565836e-23 * fConst6);
	fConst40 = ((fConst6 * ((fConst6 * (2.97505703770311e-17 + (fConst6 * (3.63811769233207e-20 - fConst39)))) - 2.49608085155429e-14)) - 1.16102593358237e-12);
	fConst41 = (2.77619078700135e-24 * fConst6);
	fConst42 = (fConst6 * (2.3197321350297e-15 + (fConst6 * ((fConst6 * (fConst41 - 3.54355920155915e-21)) - 2.60564268531789e-18))));
	fConst43 = (2.74842887913133e-24 * fConst6);
	fConst44 = ((fConst6 * ((fConst6 * (2.91999812944046e-18 + (fConst6 * (3.56364742528358e-21 - fConst43)))) - 2.44721579573661e-15)) - 1.15986606751485e-13);
	fConst45 = (2.14830127173034e-24 * fConst6);
	fConst46 = (1.15986606751485e-13 + (fConst6 * (2.88852163835099e-16 + (fConst6 * ((fConst6 * (fConst45 - 5.4266088697914e-22)) - 7.87017396290893e-19)))));
	fConst47 = (2.12681825901304e-24 * fConst6);
	fConst48 = ((fConst6 * ((fConst6 * (8.22622979638344e-19 + (fConst6 * (5.80200303543955e-22 - fConst47)))) - 3.34870612474147e-16)) - 1.30289291265291e-13);
	fConst49 = (1.32740472557653e-12 + (fConst6 * ((fConst6 * ((fConst6 * (5.91639148195952e-21 + fConst37)) - 8.39193820717763e-18)) - 3.40985414884961e-15)));
	fConst50 = (1.16102593358237e-12 + (fConst6 * ((fConst6 * ((fConst6 * (3.63811769233207e-20 + fConst39)) - 2.97505703770311e-17)) - 2.49608085155429e-14)));
	fConst51 = (fConst6 * (2.3197321350297e-15 + (fConst6 * (2.60564268531789e-18 + (fConst6 * (0 - (3.54355920155915e-21 + fConst41)))))));
	fConst52 = (1.15986606751485e-13 + (fConst6 * ((fConst6 * ((fConst6 * (3.56364742528358e-21 + fConst43)) - 2.91999812944046e-18)) - 2.44721579573661e-15)));
	fConst53 = ((fConst6 * (2.88852163835099e-16 + (fConst6 * (7.87017396290893e-19 + (fConst6 * (0 - (5.4266088697914e-22 + fConst45))))))) - 1.15986606751485e-13);
	fConst54 = (1.30289291265291e-13 + (fConst6 * ((fConst6 * ((fConst6 * (5.80200303543955e-22 + fConst47)) - 8.22622979638344e-19)) - 3.34870612474147e-16)));
	fConst55 = (1.9911070883648e-12 + (fConst6 * (1.70492707442481e-15 + (fConst6 * ((fConst6 * (0 - (8.87458722293927e-21 + fConst25))) - 4.19596910358881e-18)))));
	fConst56 = (1.74153890037355e-12 + (fConst6 * (1.24804042577715e-14 + (fConst6 * ((fConst6 * (0 - (5.4571765384981e-20 + fConst27))) - 1.48752851885156e-17)))));
	fConst57 = (fConst6 * ((fConst6 * (1.30282134265895e-18 + (fConst6 * (5.31533880233872e-21 + fConst29)))) - 1.15986606751485e-15));
	fConst58 = (1.73979910127228e-13 + (fConst6 * (1.22360789786831e-15 + (fConst6 * ((fConst6 * (0 - (5.34547113792538e-21 + fConst31))) - 1.45999906472023e-18)))));
	fConst59 = ((fConst6 * ((fConst6 * (3.93508698145447e-19 + (fConst6 * (8.13991330468709e-22 + fConst33)))) - 1.44426081917549e-16)) - 1.73979910127228e-13);
	fConst60 = (1.95433936897936e-13 + (fConst6 * (1.67435306237073e-16 + (fConst6 * ((fConst6 * (0 - (8.70300455315933e-22 + fConst35))) - 4.11311489819172e-19)))));
	fConst61 = (1 + fConst3);
	fConst62 = (0.5 * (faustpower<3>(fConst6) / fConst61));
	fConst63 = (0 - ((1 - fConst3) / fConst61));
	fConst64 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst65 = (1 + fConst64);
	fConst66 = (0.027 / fConst65);
	fConst67 = (0 - ((1 - fConst64) / fConst65));
	fConst68 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst69 = (0 - fConst68);
	fConst70 = (1 + fConst68);
	fConst71 = (0.025 / fConst70);
	fConst72 = (0 - ((1 - fConst68) / fConst70));
	fConst73 = (1.0 / fConst61);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlow0 = (0.01 * double(fslider0));
	double 	fSlow1 = (1 - fSlow0);
	double 	fSlow2 = (0.007000000000000006 * double(fslider1));
	double 	fSlow3 = (0.007000000000000006 * (1 - double(fslider2)));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fRec8[0] = ((0.993 * fRec8[1]) + fSlow2);
		fRec9[0] = ((0.993 * fRec9[1]) + fSlow3);
		double fTemp1 = (2.90256483395592e-11 + ((fRec8[0] * (2.89966516878713e-12 + (fConst6 * (fConst18 + (fConst16 * fRec8[0]))))) + (fConst6 * ((fRec9[0] * ((fRec8[0] * (fConst14 + (fConst12 * fRec8[0]))) + fConst10)) + fConst8))));
		double fTemp2 = (4.66576522119352e-14 * fRec8[0]);
		double fTemp3 = ((0 - fTemp2) - 4.66576522119352e-16);
		fRec10[0] = ((fSlow0 * fTemp0) - ((((((fRec10[1] * (1.45128241697796e-10 + ((fRec8[0] * (1.44983258439356e-11 + (fConst6 * (fConst60 + (fConst59 * fRec8[0]))))) + (fConst6 * ((fRec9[0] * ((fRec8[0] * (fConst58 + (fConst57 * fRec8[0]))) + fConst56)) + fConst55))))) + (fRec10[2] * (2.90256483395592e-10 + ((fRec8[0] * (2.89966516878713e-11 + (fConst6 * (fConst54 + (fConst53 * fRec8[0]))))) + (fConst6 * ((fRec9[0] * ((fRec8[0] * (fConst52 + (fConst51 * fRec8[0]))) + fConst50)) + fConst49)))))) + (fRec10[3] * (2.90256483395592e-10 + ((fRec8[0] * (2.89966516878713e-11 + (fConst6 * (fConst48 + (fConst46 * fRec8[0]))))) + (fConst6 * ((fRec9[0] * ((fRec8[0] * (fConst44 + (fConst42 * fRec8[0]))) + fConst40)) + fConst38)))))) + (fRec10[4] * (1.45128241697796e-10 + ((fRec8[0] * (1.44983258439356e-11 + (fConst6 * (fConst36 + (fConst34 * fRec8[0]))))) + (fConst6 * ((fRec9[0] * ((fRec8[0] * (fConst32 + (fConst30 * fRec8[0]))) + fConst28)) + fConst26)))))) + (fRec10[5] * (2.90256483395592e-11 + ((fRec8[0] * (2.89966516878713e-12 + (fConst6 * (fConst24 + (fConst23 * fRec8[0]))))) + (fConst6 * ((fRec9[0] * ((fRec8[0] * (fConst22 + (fConst21 * fRec8[0]))) + fConst20)) + fConst19)))))) / fTemp1));
		double fTemp4 = (4.66576522119352e-16 + fTemp2);
		double fTemp5 = (9.33153044238704e-14 * fRec8[0]);
		double fTemp6 = (((((((fRec10[0] * fTemp4) + (fRec10[1] * fTemp3)) + (fRec10[2] * ((0 - fTemp5) - 9.33153044238704e-16))) + (fRec10[3] * (9.33153044238704e-16 + fTemp5))) + (fRec10[4] * fTemp4)) + (fRec10[5] * fTemp3)) / fTemp1);
		fVec0[0] = fTemp6;
		fRec7[0] = ((fConst63 * fRec7[1]) + (fConst62 * (fVec0[0] + fVec0[1])));
		fRec6[0] = (fRec7[0] - (fConst5 * ((fConst4 * fRec6[2]) + (fConst2 * fRec6[1]))));
		fRec11[0] = ((fConst67 * fRec11[1]) + (fConst66 * (fRec5[1] + fRec5[2])));
		fRec5[0] = (Ftrany(TRANY_TABLE_SVEL34_250k, ((fRec11[0] + (fConst5 * (fRec6[2] + (fRec6[0] + (2 * fRec6[1]))))) - 3.571981)) - 117.70440740740739);
		fRec4[0] = ((fConst72 * fRec4[1]) + (fConst71 * ((fConst68 * fRec5[0]) + (fConst69 * fRec5[1]))));
		fRec3[0] = ((fConst63 * fRec3[1]) + (fConst73 * (fRec4[0] + fRec4[1])));
		fRec2[0] = (fRec3[0] - (fConst5 * ((fConst4 * fRec2[2]) + (fConst2 * fRec2[1]))));
		fRec12[0] = ((fConst67 * fRec12[1]) + (fConst66 * (fRec1[1] + fRec1[2])));
		fRec1[0] = (Ftrany(TRANY_TABLE_KT88_68k, ((fRec12[0] + (fConst5 * (fRec2[2] + (fRec2[0] + (2 * fRec2[1]))))) - 5.562895)) - 43.96685185185183);
		fRec0[0] = ((fConst72 * fRec0[1]) + (fConst71 * ((fConst68 * fRec1[0]) + (fConst69 * fRec1[1]))));
		output0[i] = (FAUSTFLOAT)(fRec0[0] + (fSlow1 * fTemp0));
		// post processing
		fRec0[1] = fRec0[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec12[1] = fRec12[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec11[1] = fRec11[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec7[1] = fRec7[0];
		fVec0[1] = fVec0[0];
		for (int i=5; i>0; i--) fRec10[i] = fRec10[i-1];
		fRec9[1] = fRec9[0];
		fRec8[1] = fRec8[0];
	}

}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("ruin.Intensity",N_("Intensity"),"S","",&fslider2, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("ruin.Level",N_("Level"),"S","",&fslider1, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("ruin.wet_dry",N_("wet/dry"),"S",N_("percentage of processed signal in output signal"),&fslider0, 1e+02, 0.0, 1e+02, 1.0);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("ruin" "." p)

b.openHorizontalhideBox("");
    b.create_master_slider(PARAM("Intensity"), "Intensity");
b.closeBox();
b.openHorizontalBox("");

    b.create_small_rackknobr(PARAM("Level"), "Level");

    b.create_small_rackknobr(PARAM("Intensity"), "Intensity");
    b.create_small_rackknobr(PARAM("wet_dry"), "dry/wet");
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

} // end namespace ruin
} // end namespace pluginlib
