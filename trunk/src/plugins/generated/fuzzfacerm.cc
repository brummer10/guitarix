// generated from file '../src/plugins/fuzzfacerm.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"
#include "trany.h"

namespace pluginlib {
namespace fuzzfacerm {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
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
	FAUSTFLOAT 	fslider0;
	double 	fRec8[2];
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
	FAUSTFLOAT 	fslider1;
	double 	fRec9[2];
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
	double 	fConst64;
	double 	fRec10[4];
	double 	fConst65;
	double 	fConst66;
	double 	fConst67;
	double 	fConst68;
	double 	fConst69;
	double 	fConst70;
	double 	fConst71;
	double 	fConst72;
	double 	fVec0[2];
	double 	fConst73;
	double 	fConst74;
	double 	fConst75;
	double 	fRec7[2];
	double 	fRec6[3];
	double 	fConst76;
	double 	fConst77;
	double 	fConst78;
	double 	fConst79;
	double 	fRec11[2];
	double 	fRec5[3];
	double 	fConst80;
	double 	fConst81;
	double 	fConst82;
	double 	fConst83;
	double 	fConst84;
	double 	fRec4[2];
	double 	fConst85;
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
	id = "fuzzfacerm";
	name = N_("Fuzz Face Mayer");
	groups = 0;
	description = N_("Roger Mayer Fuzz Face simulation"); // description (tooltip)
	category = N_("Fuzz");       // category
	shortname = N_("Fuzz Face RM");     // shortname
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
	for (int i=0; i<4; i++) fRec10[i] = 0;
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
	fConst7 = (1.72853928389298e-15 * fConst6);
	fConst8 = (2.6123111187704e-10 + (fConst6 * (4.32740215906676e-13 + fConst7)));
	fConst9 = (3.05119726906337e-14 * fConst6);
	fConst10 = (2.21726535708769e-11 + (fConst6 * (2.08816997599123e-11 + fConst9)));
	fConst11 = (5.85504578964162e-29 * fConst6);
	fConst12 = (2.83746860731297e-29 + (fConst6 * (4.00083755606776e-26 + fConst11)));
	fConst13 = (1.19490650740761e-31 * fConst6);
	fConst14 = (8.68612838978577e-26 + (fConst6 * (2.08767320417856e-28 + fConst13)));
	fConst15 = (3.22405119745267e-14 * fConst6);
	fConst16 = ((fConst6 * (0 - (2.08898268350887e-11 + fConst15))) - 2.21793415696022e-11);
	fConst17 = (6.18674104772942e-29 * fConst6);
	fConst18 = ((fConst6 * (0 - (4.00204457374009e-26 + fConst17))) - 2.83832448080453e-29);
	fConst19 = (1.26259937209307e-31 * fConst6);
	fConst20 = ((fConst6 * (0 - (2.15993317197785e-28 + fConst19))) - 8.68874841067831e-26);
	fConst21 = (6.76928646854567e-33 * fConst6);
	fConst22 = (1.08642105394636e-24 + (fConst6 * (2.81644163364677e-27 + (fConst6 * (8.88886207590151e-30 + fConst21)))));
	fConst23 = (3.31695258087803e-30 * fConst6);
	fConst24 = (3.54897544287011e-28 + (fConst6 * (5.00406457485288e-25 + (fConst6 * (8.26874714950455e-28 + fConst23)))));
	fConst25 = (2.27734110200845e-12 * fConst6);
	fConst26 = (2.90381085035365e-11 - fConst25);
	fConst27 = (2.23179427996828e-12 * fConst6);
	fConst28 = (fConst27 - 2.84573463334658e-11);
	fConst29 = ((fConst6 * (4.32740215906676e-13 - fConst7)) - 2.6123111187704e-10);
	fConst30 = ((fConst6 * (2.08816997599123e-11 - fConst9)) - 2.21726535708769e-11);
	fConst31 = ((fConst6 * (4.00083755606776e-26 - fConst11)) - 2.83746860731297e-29);
	fConst32 = ((fConst6 * (2.08767320417856e-28 - fConst13)) - 8.68612838978577e-26);
	fConst33 = (2.21793415696022e-11 + (fConst6 * (fConst15 - 2.08898268350887e-11)));
	fConst34 = (2.83832448080453e-29 + (fConst6 * (fConst17 - 4.00204457374009e-26)));
	fConst35 = (8.68874841067831e-26 + (fConst6 * (fConst19 - 2.15993317197785e-28)));
	fConst36 = (1.08642105394636e-24 + (fConst6 * ((fConst6 * (8.88886207590151e-30 - fConst21)) - 2.81644163364677e-27)));
	fConst37 = (3.54897544287011e-28 + (fConst6 * ((fConst6 * (8.26874714950455e-28 - fConst23)) - 5.00406457485288e-25)));
	fConst38 = (1.75651373689249e-28 * fConst6);
	fConst39 = ((fConst6 * (fConst38 - 4.00083755606776e-26)) - 2.83746860731297e-29);
	fConst40 = (3.58471952222284e-31 * fConst6);
	fConst41 = ((fConst6 * (fConst40 - 2.08767320417856e-28)) - 8.68612838978577e-26);
	fConst42 = (9.67215359235801e-14 * fConst6);
	fConst43 = (2.21793415696022e-11 + (fConst6 * (2.08898268350887e-11 - fConst42)));
	fConst44 = (1.85602231431883e-28 * fConst6);
	fConst45 = (2.83832448080453e-29 + (fConst6 * (4.00204457374009e-26 - fConst44)));
	fConst46 = (3.78779811627921e-31 * fConst6);
	fConst47 = (8.68874841067831e-26 + (fConst6 * (2.15993317197785e-28 - fConst46)));
	fConst48 = (9.15359180719011e-14 * fConst6);
	fConst49 = ((fConst6 * (fConst48 - 2.08816997599123e-11)) - 2.21726535708769e-11);
	fConst50 = (5.18561785167894e-15 * fConst6);
	fConst51 = ((fConst6 * (fConst50 - 4.32740215906676e-13)) - 2.6123111187704e-10);
	fConst52 = (2.0307859405637e-32 * fConst6);
	fConst53 = (3.25926316183907e-24 + (fConst6 * ((fConst6 * (fConst52 - 8.88886207590151e-30)) - 2.81644163364677e-27)));
	fConst54 = (9.95085774263408e-30 * fConst6);
	fConst55 = (1.06469263286103e-27 + (fConst6 * ((fConst6 * (fConst54 - 8.26874714950455e-28)) - 5.00406457485288e-25)));
	fConst56 = (2.6123111187704e-10 + (fConst6 * (0 - (4.32740215906676e-13 + fConst50))));
	fConst57 = (2.21726535708769e-11 + (fConst6 * (0 - (2.08816997599123e-11 + fConst48))));
	fConst58 = (2.83746860731297e-29 + (fConst6 * (0 - (4.00083755606776e-26 + fConst38))));
	fConst59 = (8.68612838978577e-26 + (fConst6 * (0 - (2.08767320417856e-28 + fConst40))));
	fConst60 = ((fConst6 * (2.08898268350887e-11 + fConst42)) - 2.21793415696022e-11);
	fConst61 = ((fConst6 * (4.00204457374009e-26 + fConst44)) - 2.83832448080453e-29);
	fConst62 = ((fConst6 * (2.15993317197785e-28 + fConst46)) - 8.68874841067831e-26);
	fConst63 = (3.25926316183907e-24 + (fConst6 * (2.81644163364677e-27 + (fConst6 * (0 - (8.88886207590151e-30 + fConst52))))));
	fConst64 = (1.06469263286103e-27 + (fConst6 * (5.00406457485288e-25 + (fConst6 * (0 - (8.26874714950455e-28 + fConst54))))));
	fConst65 = (6.69538283990485e-12 * fConst6);
	fConst66 = (2.84573463334658e-11 - fConst65);
	fConst67 = (6.83202330602535e-12 * fConst6);
	fConst68 = (fConst67 - 2.90381085035365e-11);
	fConst69 = (0 - (2.90381085035365e-11 + fConst67));
	fConst70 = (2.84573463334658e-11 + fConst65);
	fConst71 = (2.90381085035365e-11 + fConst25);
	fConst72 = (0 - (2.84573463334658e-11 + fConst27));
	fConst73 = (1 + fConst3);
	fConst74 = (faustpower<2>(fConst6) / fConst73);
	fConst75 = (0 - ((1 - fConst3) / fConst73));
	fConst76 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst77 = (1 + fConst76);
	fConst78 = (0.027 / fConst77);
	fConst79 = (0 - ((1 - fConst76) / fConst77));
	fConst80 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst81 = (0 - fConst80);
	fConst82 = (1 + fConst80);
	fConst83 = (0.025 / fConst82);
	fConst84 = (0 - ((1 - fConst80) / fConst82));
	fConst85 = (1.0 / fConst73);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlow0 = (0.007000000000000006 * (1 - double(fslider0)));
	double 	fSlow1 = (0.007000000000000006 * (1 - double(fslider1)));
	for (int i=0; i<count; i++) {
		fRec8[0] = ((0.993 * fRec8[1]) + fSlow0);
		fRec9[0] = ((0.993 * fRec9[1]) + fSlow1);
		double fTemp0 = (2.77325369604093e-10 + ((fRec8[0] * ((fConst24 * fRec8[0]) + fConst22)) + (fConst6 * ((fRec9[0] * (((fRec9[0] * ((fRec8[0] * (fConst20 + (fConst18 * fRec8[0]))) + fConst16)) + (fRec8[0] * (fConst14 + (fConst12 * fRec8[0])))) + fConst10)) + fConst8))));
		double fTemp1 = (2.1870008532593e-12 * fRec8[0]);
		double fTemp2 = (4.47934267089816e-14 * fRec8[0]);
		fRec10[0] = ((double)input0[i] - ((((fRec10[1] * (8.3197610881228e-10 + ((fRec8[0] * ((fConst64 * fRec8[0]) + fConst63)) + (fConst6 * ((fRec9[0] * (((fRec9[0] * ((fRec8[0] * (fConst62 + (fConst61 * fRec8[0]))) + fConst60)) + (fRec8[0] * (fConst59 + (fConst58 * fRec8[0])))) + fConst57)) + fConst56))))) + (fRec10[2] * (8.3197610881228e-10 + ((fRec8[0] * ((fConst55 * fRec8[0]) + fConst53)) + (fConst6 * (fConst51 + (fRec9[0] * (fConst49 + ((fRec9[0] * ((fRec8[0] * (fConst47 + (fConst45 * fRec8[0]))) + fConst43)) + (fRec8[0] * (fConst41 + (fConst39 * fRec8[0])))))))))))) + (fRec10[3] * (2.77325369604093e-10 + ((fRec8[0] * ((fConst37 * fRec8[0]) + fConst36)) + (fConst6 * ((fRec9[0] * (((fRec9[0] * ((fRec8[0] * (fConst35 + (fConst34 * fRec8[0]))) + fConst33)) + (fRec8[0] * (fConst32 + (fConst31 * fRec8[0])))) + fConst30)) + fConst29)))))) / fTemp0));
		double fTemp3 = (1.34380280126945e-13 * fRec8[0]);
		double fTemp4 = (6.5610025597779e-12 * fRec8[0]);
		double fTemp5 = (((((fRec10[0] * (((fConst6 * (fRec9[0] * ((fTemp1 + (fRec9[0] * (fTemp2 - 4.57075782744711e-14))) - 2.23163352373398e-12))) + (fConst72 * fRec8[0])) + fConst71)) + (fRec10[1] * (((fConst6 * (fRec9[0] * (6.69490057120194e-12 + ((fRec9[0] * (1.37122734823413e-13 + (0 - fTemp3))) - fTemp4)))) + (fConst70 * fRec8[0])) + fConst69))) + (fRec10[2] * (fConst68 + ((fConst6 * (fRec9[0] * ((fTemp4 + (fRec9[0] * (fTemp3 - 1.37122734823413e-13))) - 6.69490057120194e-12))) + (fConst66 * fRec8[0]))))) + (fRec10[3] * (((fConst6 * (fRec9[0] * (2.23163352373398e-12 + ((fRec9[0] * (4.57075782744711e-14 + (0 - fTemp2))) - fTemp1)))) + (fConst28 * fRec8[0])) + fConst26))) / fTemp0);
		fVec0[0] = fTemp5;
		fRec7[0] = ((fConst75 * fRec7[1]) + (fConst74 * (fVec0[0] + fVec0[1])));
		fRec6[0] = (fRec7[0] - (fConst5 * ((fConst4 * fRec6[2]) + (fConst2 * fRec6[1]))));
		fRec11[0] = ((fConst79 * fRec11[1]) + (fConst78 * (fRec5[1] + fRec5[2])));
		fRec5[0] = (Ftrany(TRANY_TABLE_KT88_68k, ((fRec11[0] + (fConst5 * (fRec6[2] + (fRec6[0] + (2 * fRec6[1]))))) - 5.562895)) - 43.96685185185183);
		fRec4[0] = ((fConst84 * fRec4[1]) + (fConst83 * ((fConst80 * fRec5[0]) + (fConst81 * fRec5[1]))));
		fRec3[0] = ((fConst75 * fRec3[1]) + (fConst85 * (fRec4[0] + fRec4[1])));
		fRec2[0] = (fRec3[0] - (fConst5 * ((fConst4 * fRec2[2]) + (fConst2 * fRec2[1]))));
		fRec12[0] = ((fConst79 * fRec12[1]) + (fConst78 * (fRec1[1] + fRec1[2])));
		fRec1[0] = (Ftrany(TRANY_TABLE_KT88_68k, ((fRec12[0] + (fConst5 * (fRec2[2] + (fRec2[0] + (2 * fRec2[1]))))) - 5.562895)) - 43.96685185185183);
		fRec0[0] = ((fConst84 * fRec0[1]) + (fConst83 * ((fConst80 * fRec1[0]) + (fConst81 * fRec1[1]))));
		output0[i] = (FAUSTFLOAT)fRec0[0];
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
		for (int i=3; i>0; i--) fRec10[i] = fRec10[i-1];
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
	reg.registerVar("fuzzfacerm.Fuzz",N_("Fuzz"),"S","",&fslider1, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("fuzzfacerm.Level",N_("Level"),"S","",&fslider0, 0.5, 0.0, 1.0, 0.01);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("fuzzfacerm" "." p)

b.openHorizontalhideBox("");
    b.create_master_slider(PARAM("Fuzz"), N_("Fuzz"));
b.closeBox();
b.openHorizontalBox("");

    b.create_small_rackknobr(PARAM("Fuzz"), N_("Fuzz"));

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

} // end namespace fuzzfacerm
} // end namespace pluginlib
