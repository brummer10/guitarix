// generated from file '../src/plugins/ruin.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

#include "trany.h"
#include <string.h>

namespace pluginlib {
namespace ruin {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	double 	fConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	FAUSTFLOAT 	fslider0;
	double 	fRec0[2];
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	FAUSTFLOAT 	fslider1;
	double 	fRec1[2];
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
	double 	fRec2[6];
	double 	fConst55;

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

	FAUSTFLOAT fsliderdw0;
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
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<6; i++) fRec2[i] = 0;

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

}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = double(min(192000, max(1, fSamplingFreq)));
	fConst1 = (2.17193258571938e-24 * fConst0);
	fConst2 = (6.63702362788267e-13 + (fConst0 * (1.70492707442481e-15 + (fConst0 * (4.19596910358881e-18 + (fConst0 * (2.95819574097976e-21 + fConst1)))))));
	fConst3 = (2.80672888565836e-24 * fConst0);
	fConst4 = (5.80512966791183e-13 + (fConst0 * (1.24804042577715e-14 + (fConst0 * (1.48752851885156e-17 + (fConst0 * (1.81905884616603e-20 + fConst3)))))));
	fConst5 = (2.77619078700135e-25 * fConst0);
	fConst6 = (fConst0 * ((fConst0 * ((fConst0 * (0 - (1.77177960077957e-21 + fConst5))) - 1.30282134265895e-18)) - 1.15986606751485e-15));
	fConst7 = (2.74842887913133e-25 * fConst0);
	fConst8 = (5.79933033757426e-14 + (fConst0 * (1.22360789786831e-15 + (fConst0 * (1.45999906472023e-18 + (fConst0 * (1.78182371264179e-21 + fConst7)))))));
	fConst9 = (2.14830127173034e-25 * fConst0);
	fConst10 = ((fConst0 * ((fConst0 * ((fConst0 * (0 - (2.7133044348957e-22 + fConst9))) - 3.93508698145447e-19)) - 1.44426081917549e-16)) - 5.79933033757426e-14);
	fConst11 = (2.12681825901304e-25 * fConst0);
	fConst12 = (6.51446456326455e-14 + (fConst0 * (1.67435306237073e-16 + (fConst0 * (4.11311489819172e-19 + (fConst0 * (2.90100151771978e-22 + fConst11)))))));
	fConst13 = ((fConst0 * (1.70492707442481e-15 + (fConst0 * ((fConst0 * (2.95819574097976e-21 - fConst1)) - 4.19596910358881e-18)))) - 6.63702362788267e-13);
	fConst14 = ((fConst0 * (1.24804042577715e-14 + (fConst0 * ((fConst0 * (1.81905884616603e-20 - fConst3)) - 1.48752851885156e-17)))) - 5.80512966791183e-13);
	fConst15 = (fConst0 * ((fConst0 * (1.30282134265895e-18 + (fConst0 * (fConst5 - 1.77177960077957e-21)))) - 1.15986606751485e-15));
	fConst16 = ((fConst0 * (1.22360789786831e-15 + (fConst0 * ((fConst0 * (1.78182371264179e-21 - fConst7)) - 1.45999906472023e-18)))) - 5.79933033757426e-14);
	fConst17 = (5.79933033757426e-14 + (fConst0 * ((fConst0 * (3.93508698145447e-19 + (fConst0 * (fConst9 - 2.7133044348957e-22)))) - 1.44426081917549e-16)));
	fConst18 = ((fConst0 * (1.67435306237073e-16 + (fConst0 * ((fConst0 * (2.90100151771978e-22 - fConst11)) - 4.11311489819172e-19)))) - 6.51446456326455e-14);
	fConst19 = (1.08596629285969e-23 * fConst0);
	fConst20 = ((fConst0 * (1.70492707442481e-15 + (fConst0 * (4.19596910358881e-18 + (fConst0 * (fConst19 - 8.87458722293927e-21)))))) - 1.9911070883648e-12);
	fConst21 = (1.40336444282918e-23 * fConst0);
	fConst22 = ((fConst0 * (1.24804042577715e-14 + (fConst0 * (1.48752851885156e-17 + (fConst0 * (fConst21 - 5.4571765384981e-20)))))) - 1.74153890037355e-12);
	fConst23 = (1.38809539350067e-24 * fConst0);
	fConst24 = (fConst0 * ((fConst0 * ((fConst0 * (5.31533880233872e-21 - fConst23)) - 1.30282134265895e-18)) - 1.15986606751485e-15));
	fConst25 = (1.37421443956567e-24 * fConst0);
	fConst26 = ((fConst0 * (1.22360789786831e-15 + (fConst0 * (1.45999906472023e-18 + (fConst0 * (fConst25 - 5.34547113792538e-21)))))) - 1.73979910127228e-13);
	fConst27 = (1.07415063586517e-24 * fConst0);
	fConst28 = (1.73979910127228e-13 + (fConst0 * ((fConst0 * ((fConst0 * (8.13991330468709e-22 - fConst27)) - 3.93508698145447e-19)) - 1.44426081917549e-16)));
	fConst29 = (1.06340912950652e-24 * fConst0);
	fConst30 = ((fConst0 * (1.67435306237073e-16 + (fConst0 * (4.11311489819172e-19 + (fConst0 * (fConst29 - 8.70300455315933e-22)))))) - 1.95433936897936e-13);
	fConst31 = (2.17193258571938e-23 * fConst0);
	fConst32 = ((fConst0 * ((fConst0 * (8.39193820717763e-18 + (fConst0 * (5.91639148195952e-21 - fConst31)))) - 3.40985414884961e-15)) - 1.32740472557653e-12);
	fConst33 = (2.80672888565836e-23 * fConst0);
	fConst34 = ((fConst0 * ((fConst0 * (2.97505703770311e-17 + (fConst0 * (3.63811769233207e-20 - fConst33)))) - 2.49608085155429e-14)) - 1.16102593358237e-12);
	fConst35 = (2.77619078700135e-24 * fConst0);
	fConst36 = (fConst0 * (2.3197321350297e-15 + (fConst0 * ((fConst0 * (fConst35 - 3.54355920155915e-21)) - 2.60564268531789e-18))));
	fConst37 = (2.74842887913133e-24 * fConst0);
	fConst38 = ((fConst0 * ((fConst0 * (2.91999812944046e-18 + (fConst0 * (3.56364742528358e-21 - fConst37)))) - 2.44721579573661e-15)) - 1.15986606751485e-13);
	fConst39 = (2.14830127173034e-24 * fConst0);
	fConst40 = (1.15986606751485e-13 + (fConst0 * (2.88852163835099e-16 + (fConst0 * ((fConst0 * (fConst39 - 5.4266088697914e-22)) - 7.87017396290893e-19)))));
	fConst41 = (2.12681825901304e-24 * fConst0);
	fConst42 = ((fConst0 * ((fConst0 * (8.22622979638344e-19 + (fConst0 * (5.80200303543955e-22 - fConst41)))) - 3.34870612474147e-16)) - 1.30289291265291e-13);
	fConst43 = (1.32740472557653e-12 + (fConst0 * ((fConst0 * ((fConst0 * (5.91639148195952e-21 + fConst31)) - 8.39193820717763e-18)) - 3.40985414884961e-15)));
	fConst44 = (1.16102593358237e-12 + (fConst0 * ((fConst0 * ((fConst0 * (3.63811769233207e-20 + fConst33)) - 2.97505703770311e-17)) - 2.49608085155429e-14)));
	fConst45 = (fConst0 * (2.3197321350297e-15 + (fConst0 * (2.60564268531789e-18 + (fConst0 * (0 - (3.54355920155915e-21 + fConst35)))))));
	fConst46 = (1.15986606751485e-13 + (fConst0 * ((fConst0 * ((fConst0 * (3.56364742528358e-21 + fConst37)) - 2.91999812944046e-18)) - 2.44721579573661e-15)));
	fConst47 = ((fConst0 * (2.88852163835099e-16 + (fConst0 * (7.87017396290893e-19 + (fConst0 * (0 - (5.4266088697914e-22 + fConst39))))))) - 1.15986606751485e-13);
	fConst48 = (1.30289291265291e-13 + (fConst0 * ((fConst0 * ((fConst0 * (5.80200303543955e-22 + fConst41)) - 8.22622979638344e-19)) - 3.34870612474147e-16)));
	fConst49 = (1.9911070883648e-12 + (fConst0 * (1.70492707442481e-15 + (fConst0 * ((fConst0 * (0 - (8.87458722293927e-21 + fConst19))) - 4.19596910358881e-18)))));
	fConst50 = (1.74153890037355e-12 + (fConst0 * (1.24804042577715e-14 + (fConst0 * ((fConst0 * (0 - (5.4571765384981e-20 + fConst21))) - 1.48752851885156e-17)))));
	fConst51 = (fConst0 * ((fConst0 * (1.30282134265895e-18 + (fConst0 * (5.31533880233872e-21 + fConst23)))) - 1.15986606751485e-15));
	fConst52 = (1.73979910127228e-13 + (fConst0 * (1.22360789786831e-15 + (fConst0 * ((fConst0 * (0 - (5.34547113792538e-21 + fConst25))) - 1.45999906472023e-18)))));
	fConst53 = ((fConst0 * ((fConst0 * (3.93508698145447e-19 + (fConst0 * (8.13991330468709e-22 + fConst27)))) - 1.44426081917549e-16)) - 1.73979910127228e-13);
	fConst54 = (1.95433936897936e-13 + (fConst0 * (1.67435306237073e-16 + (fConst0 * ((fConst0 * (0 - (8.70300455315933e-22 + fConst29))) - 4.11311489819172e-19)))));
	fConst55 = (0.8 * faustpower<3>(fConst0));

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

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlowdw0 = (0.01 * fsliderdw0);
	double 	fSlowdw1 = (1 - fSlowdw0);
	FAUSTFLOAT 	dryinput[count];
	memcpy(&dryinput, input0, count * sizeof(float));

	double 	fSlow0 = (0.0021000000000000016 * double(fslider0));
	double 	fSlow1 = (0.007000000000000006 * (1 - double(fslider1)));
	for (int i=0; i<count; i++) {
		fRec0[0] = ((0.993 * fRec0[1]) + fSlow0);
		fRec1[0] = ((0.993 * fRec1[1]) + fSlow1);
		double fTemp0 = (2.90256483395592e-11 + ((fRec0[0] * (2.89966516878713e-12 + (fConst0 * (fConst12 + (fConst10 * fRec0[0]))))) + (fConst0 * ((fRec1[0] * ((fRec0[0] * (fConst8 + (fConst6 * fRec0[0]))) + fConst4)) + fConst2))));
		double fTemp1 = (4.66576522119352e-14 * fRec0[0]);
		double fTemp2 = ((0 - fTemp1) - 4.66576522119352e-16);
		fRec2[0] = ((double)input0[i] - ((((((fRec2[1] * (1.45128241697796e-10 + ((fRec0[0] * (1.44983258439356e-11 + (fConst0 * (fConst54 + (fConst53 * fRec0[0]))))) + (fConst0 * ((fRec1[0] * ((fRec0[0] * (fConst52 + (fConst51 * fRec0[0]))) + fConst50)) + fConst49))))) + (fRec2[2] * (2.90256483395592e-10 + ((fRec0[0] * (2.89966516878713e-11 + (fConst0 * (fConst48 + (fConst47 * fRec0[0]))))) + (fConst0 * ((fRec1[0] * ((fRec0[0] * (fConst46 + (fConst45 * fRec0[0]))) + fConst44)) + fConst43)))))) + (fRec2[3] * (2.90256483395592e-10 + ((fRec0[0] * (2.89966516878713e-11 + (fConst0 * (fConst42 + (fConst40 * fRec0[0]))))) + (fConst0 * ((fRec1[0] * ((fRec0[0] * (fConst38 + (fConst36 * fRec0[0]))) + fConst34)) + fConst32)))))) + (fRec2[4] * (1.45128241697796e-10 + ((fRec0[0] * (1.44983258439356e-11 + (fConst0 * (fConst30 + (fConst28 * fRec0[0]))))) + (fConst0 * ((fRec1[0] * ((fRec0[0] * (fConst26 + (fConst24 * fRec0[0]))) + fConst22)) + fConst20)))))) + (fRec2[5] * (2.90256483395592e-11 + ((fRec0[0] * (2.89966516878713e-12 + (fConst0 * (fConst18 + (fConst17 * fRec0[0]))))) + (fConst0 * ((fRec1[0] * ((fRec0[0] * (fConst16 + (fConst15 * fRec0[0]))) + fConst14)) + fConst13)))))) / fTemp0));
		double fTemp3 = (4.66576522119352e-16 + fTemp1);
		double fTemp4 = (9.33153044238704e-14 * fRec0[0]);
		output0[i] = (FAUSTFLOAT)(fConst55 * (((((((fRec2[0] * fTemp3) + (fRec2[1] * fTemp2)) + (fRec2[2] * ((0 - fTemp4) - 9.33153044238704e-16))) + (fRec2[3] * (9.33153044238704e-16 + fTemp4))) + (fRec2[4] * fTemp3)) + (fRec2[5] * fTemp2)) / fTemp0));
		// post processing
		for (int i=5; i>0; i--) fRec2[i] = fRec2[i-1];
		fRec1[1] = fRec1[0];
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
		fRecCl5[0] = (Ftrany(TRANY_TABLE_KT88_68k, ((fRecCl8[0] + (0.9254498422517706 * (fRecCl6[2] + (fRecCl6[0] + (2.0 * fRecCl6[1]))))) - 5.562895)) - 43.96685185185183);
		fRecCl4[0] = ((fConstCl9 * fRecCl4[1]) + (fConstCl8 * ((fConstCl5 * fRecCl5[0]) + (fConstCl6 * fRecCl5[1]))));
		fRecCl3[0] = ((0.9302847925323914 * (fRecCl4[0] + fRecCl4[1])) - (0.8605695850647829 * fRecCl3[1]));
		fRecCl2[0] = (fRecCl3[0] - ((1.8405051250752198 * fRecCl2[1]) + (0.8612942439318627 * fRecCl2[2])));
		fRecCl9[0] = ((fConstCl4 * fRecCl9[1]) + (fConstCl3 * (fRecCl1[1] + fRecCl1[2])));
		fRecCl1[0] = (Ftrany(TRANY_TABLE_KT88_68k, ((fRecCl9[0] + (0.9254498422517706 * (fRecCl2[2] + (fRecCl2[0] + (2.0 * fRecCl2[1]))))) - 5.562895)) - 43.96685185185183);
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
		output0[i] = ((fSlowdw1 * (double)dryinput[i]) + (fSlowdw0 * (double)output0[i]));
	}

}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("ruin.wet_dry",N_("Dry/Wet"),"S",N_("percentage of processed signal in output signal"),&fsliderdw0, 1e+02, 0.0, 1e+02, 1.0);
	reg.registerVar("ruin.Intensity",N_("Intensity"),"S","",&fslider1, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("ruin.Level",N_("Level"),"S","",&fslider0, 0.5, 0.0, 1.0, 0.01);
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
                        <property name=\"var_id\">ruin.Intensity</property>\n\
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
                        <property name=\"var_id\">ruin.Level</property>\n\
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
                <child>\n\
                  <object class=\"GtkVBox\" id=\"vbox4\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label3:rack_label\">\n\
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
                      <object class=\"GxSmallKnobR\" id=\"gxbigknob3\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">ruin.wet_dry</property>\n\
                        <property name=\"label_ref\">label3:rack_label</property>\n\
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
                    <property name=\"position\">2</property>\n\
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
                <property name=\"var_id\">ruin.Intensity</property>\n\
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
                <property name=\"label\" translatable=\"yes\">Intensity</property>\n\
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
