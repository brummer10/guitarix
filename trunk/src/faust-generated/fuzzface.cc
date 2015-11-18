// generated from file '../src/faust/fuzzface.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "trany.h"

namespace fuzzface {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	FAUSTFLOAT 	fslider0;
	double 	fRec8[2];
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	FAUSTFLOAT 	fslider1;
	double 	fRec9[2];
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
	double 	fRec10[6];
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
	double 	fVec0[2];
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
	id = "fuzzface";
	name = N_("Fuzz Face");
	groups = 0;
	description = N_("J Hendrix Fuzz Face simulation"); // description (tooltip)
	category = N_("Fuzz");       // category
	shortname = "";     // shortname
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
	fConst1 = double(iConst0);
	fConst2 = (3.98985774247549e-22 * fConst1);
	fConst3 = (5.31230624730483e-11 + (fConst1 * (1.83615604104971e-13 + (fConst1 * (1.99042653510896e-15 + fConst2)))));
	fConst4 = (3.73292075290073e-29 * fConst1);
	fConst5 = ((fConst1 * ((fConst1 * ((fConst1 * (0 - (1.05633134620746e-20 + fConst4))) - 3.11506369039915e-14)) - 2.30719916990074e-11)) - 1.07493164710329e-09);
	fConst6 = (1.07449105454163e-09 + (fConst1 * (2.29636966370042e-11 + (fConst1 * (2.91602352831988e-14 + (fConst1 * (1.01643277726662e-20 + fConst4)))))));
	fConst7 = (4.76991513499346e-20 * fConst1);
	fConst8 = (5.00346713698171e-13 + fConst7);
	fConst9 = (0 - fConst8);
	fConst10 = (fConst7 - 5.38351707988916e-15);
	fConst11 = (5.38351707988916e-15 - fConst7);
	fConst12 = (5.05730339185222e-13 * fConst1);
	fConst13 = (fConst12 - 1.16162215422261e-12);
	fConst14 = (1.16162215422261e-12 - fConst12);
	fConst15 = ((fConst1 * (1.83615604104971e-13 + (fConst1 * (fConst2 - 1.99042653510896e-15)))) - 5.31230624730483e-11);
	fConst16 = (1.07493164710329e-09 + (fConst1 * ((fConst1 * (3.11506369039915e-14 + (fConst1 * (fConst4 - 1.05633134620746e-20)))) - 2.30719916990074e-11)));
	fConst17 = ((fConst1 * (2.29636966370042e-11 + (fConst1 * ((fConst1 * (1.01643277726662e-20 - fConst4)) - 2.91602352831988e-14)))) - 1.07449105454163e-09);
	fConst18 = (1.19695732274265e-21 * fConst1);
	fConst19 = ((fConst1 * (1.83615604104971e-13 + (fConst1 * (1.99042653510896e-15 - fConst18)))) - 1.59369187419145e-10);
	fConst20 = (1.86646037645036e-28 * fConst1);
	fConst21 = (3.22479494130986e-09 + (fConst1 * ((fConst1 * ((fConst1 * (3.16899403862238e-20 - fConst20)) - 3.11506369039915e-14)) - 2.30719916990074e-11)));
	fConst22 = ((fConst1 * (2.29636966370042e-11 + (fConst1 * (2.91602352831988e-14 + (fConst1 * (fConst20 - 3.04929833179984e-20)))))) - 3.22347316362488e-09);
	fConst23 = (7.97971548495099e-22 * fConst1);
	fConst24 = ((fConst1 * ((fConst1 * (3.98085307021793e-15 + fConst23)) - 3.67231208209942e-13)) - 1.06246124946097e-10);
	fConst25 = (3.73292075290073e-28 * fConst1);
	fConst26 = (2.14986329420657e-09 + (fConst1 * (4.61439833980148e-11 + (fConst1 * ((fConst1 * (fConst25 - 2.11266269241492e-20)) - 6.2301273807983e-14)))));
	fConst27 = ((fConst1 * ((fConst1 * (5.83204705663976e-14 + (fConst1 * (2.03286555453323e-20 - fConst25)))) - 4.59273932740084e-11)) - 2.14898210908325e-09);
	fConst28 = (1.06246124946097e-10 + (fConst1 * ((fConst1 * (fConst23 - 3.98085307021793e-15)) - 3.67231208209942e-13)));
	fConst29 = ((fConst1 * (4.61439833980148e-11 + (fConst1 * (6.2301273807983e-14 + (fConst1 * (0 - (2.11266269241492e-20 + fConst25))))))) - 2.14986329420657e-09);
	fConst30 = (2.14898210908325e-09 + (fConst1 * ((fConst1 * ((fConst1 * (2.03286555453323e-20 + fConst25)) - 5.83204705663976e-14)) - 4.59273932740084e-11)));
	fConst31 = (1.59369187419145e-10 + (fConst1 * (1.83615604104971e-13 + (fConst1 * (0 - (1.99042653510896e-15 + fConst18))))));
	fConst32 = ((fConst1 * ((fConst1 * (3.11506369039915e-14 + (fConst1 * (3.16899403862238e-20 + fConst20)))) - 2.30719916990074e-11)) - 3.22479494130986e-09);
	fConst33 = (3.22347316362488e-09 + (fConst1 * (2.29636966370042e-11 + (fConst1 * ((fConst1 * (0 - (3.04929833179984e-20 + fConst20))) - 2.91602352831988e-14)))));
	fConst34 = (1.43097454049804e-19 * fConst1);
	fConst35 = (5.00346713698171e-13 + fConst34);
	fConst36 = (0 - fConst35);
	fConst37 = (5.38351707988916e-15 - fConst34);
	fConst38 = (fConst34 - 5.38351707988916e-15);
	fConst39 = (1.16162215422261e-12 + fConst12);
	fConst40 = (0 - fConst39);
	fConst41 = (1.01146067837044e-12 * fConst1);
	fConst42 = (2.32324430844522e-12 - fConst41);
	fConst43 = (9.53983026998693e-20 * fConst1);
	fConst44 = (1.00069342739634e-12 - fConst43);
	fConst45 = (1.07670341597783e-14 + fConst43);
	fConst46 = (0 - fConst45);
	fConst47 = (fConst43 - 1.00069342739634e-12);
	fConst48 = (fConst41 - 2.32324430844522e-12);
	fConst49 = (2.32324430844522e-12 + fConst41);
	fConst50 = (0 - fConst49);
	fConst51 = (1.00069342739634e-12 + fConst43);
	fConst52 = (0 - fConst51);
	fConst53 = (fConst43 - 1.07670341597783e-14);
	fConst54 = (1.07670341597783e-14 - fConst43);
	fConst55 = (5.00346713698171e-13 - fConst34);
	fConst56 = (fConst34 - 5.00346713698171e-13);
	fConst57 = (5.38351707988916e-15 + fConst34);
	fConst58 = (0 - fConst57);
	fConst59 = (5.00346713698171e-13 - fConst7);
	fConst60 = (5.38351707988916e-15 + fConst7);
	fConst61 = (0 - fConst60);
	fConst62 = (fConst7 - 5.00346713698171e-13);
	fConst63 = (0.9302847925323914 * faustpower<2>(fConst1));
	fConst64 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst65 = (1 + fConst64);
	fConst66 = (0.027 / fConst65);
	fConst67 = (0 - ((1 - fConst64) / fConst65));
	fConst68 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst69 = (0 - fConst68);
	fConst70 = (1 + fConst68);
	fConst71 = (0.025 / fConst70);
	fConst72 = (0 - ((1 - fConst68) / fConst70));
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
		double fTemp0 = (2.44402781742033e-09 + (fConst1 * ((fRec8[0] * (fConst6 + (fConst5 * fRec8[0]))) + fConst3)));
		fRec9[0] = ((0.993 * fRec9[1]) + fSlow1);
		double fTemp1 = (fConst13 * fRec9[0]);
		fRec10[0] = ((double)input0[i] - ((((((fRec10[1] * (1.22201390871017e-08 + (fConst1 * ((fRec8[0] * (fConst33 + (fConst32 * fRec8[0]))) + fConst31)))) + (fRec10[2] * (2.44402781742033e-08 + (fConst1 * ((fRec8[0] * (fConst30 + (fConst29 * fRec8[0]))) + fConst28))))) + (fRec10[3] * (2.44402781742033e-08 + (fConst1 * ((fRec8[0] * (fConst27 + (fConst26 * fRec8[0]))) + fConst24))))) + (fRec10[4] * (1.22201390871017e-08 + (fConst1 * ((fRec8[0] * (fConst22 + (fConst21 * fRec8[0]))) + fConst19))))) + (fRec10[5] * (2.44402781742033e-09 + (fConst1 * ((fRec8[0] * (fConst17 + (fConst16 * fRec8[0]))) + fConst15))))) / fTemp0));
		double fTemp2 = (fConst40 * fRec9[0]);
		double fTemp3 = (((((((fRec10[0] * (fConst39 + ((fConst1 * (fRec8[0] * (fConst62 + ((fRec8[0] * (fConst61 + (fConst60 * fRec9[0]))) + (fConst59 * fRec9[0]))))) + fTemp2))) + (fRec10[1] * (((fConst1 * (fRec8[0] * (((fRec8[0] * (fConst57 + (fConst58 * fRec9[0]))) + (fConst56 * fRec9[0])) + fConst55))) + fTemp1) + fConst14))) + (fRec10[2] * (((fConst1 * (fRec8[0] * (fConst51 + ((fRec8[0] * (fConst54 + (fConst53 * fRec9[0]))) + (fConst52 * fRec9[0]))))) + (fConst49 * fRec9[0])) + fConst50))) + (fRec10[3] * (fConst48 + ((fConst1 * (fRec8[0] * (fConst47 + ((fRec8[0] * (fConst46 + (fConst45 * fRec9[0]))) + (fConst44 * fRec9[0]))))) + (fConst42 * fRec9[0]))))) + (fRec10[4] * (fConst39 + (fTemp2 + (fConst1 * (fRec8[0] * (((fRec8[0] * (fConst38 + (fConst37 * fRec9[0]))) + (fConst35 * fRec9[0])) + fConst36))))))) + (fRec10[5] * (fConst14 + (fTemp1 + (fConst1 * (fRec8[0] * (fConst8 + ((fRec8[0] * (fConst11 + (fConst10 * fRec9[0]))) + (fConst9 * fRec9[0]))))))))) / fTemp0);
		fVec0[0] = fTemp3;
		fRec7[0] = ((fConst63 * (fVec0[0] + fVec0[1])) - (0.8605695850647829 * fRec7[1]));
		fRec6[0] = (fRec7[0] - ((1.8405051250752198 * fRec6[1]) + (0.8612942439318627 * fRec6[2])));
		fRec11[0] = ((fConst67 * fRec11[1]) + (fConst66 * (fRec5[1] + fRec5[2])));
		fRec5[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec11[0] + (0.9254498422517706 * (fRec6[2] + (fRec6[0] + (2.0 * fRec6[1]))))) - 3.571981)) - 117.70440740740739);
		fRec4[0] = ((fConst72 * fRec4[1]) + (fConst71 * ((fConst68 * fRec5[0]) + (fConst69 * fRec5[1]))));
		fRec3[0] = ((0.9302847925323914 * (fRec4[0] + fRec4[1])) - (0.8605695850647829 * fRec3[1]));
		fRec2[0] = (fRec3[0] - ((1.8405051250752198 * fRec2[1]) + (0.8612942439318627 * fRec2[2])));
		fRec12[0] = ((fConst67 * fRec12[1]) + (fConst66 * (fRec1[1] + fRec1[2])));
		fRec1[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec12[0] + (0.9254498422517706 * (fRec2[2] + (fRec2[0] + (2.0 * fRec2[1]))))) - 3.571981)) - 117.70440740740739);
		fRec0[0] = ((fConst72 * fRec0[1]) + (fConst71 * ((fConst68 * fRec1[0]) + (fConst69 * fRec1[1]))));
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
	reg.registerVar("fuzzface.Fuzz",N_("Fuzz"),"S","",&fslider0, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("fuzzface.Level",N_("Level"),"S","",&fslider1, 0.5, 0.0, 1.0, 0.01);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("fuzzface" "." p)

b.openHorizontalhideBox("");
    b.create_master_slider(PARAM("Fuzz"), "Fuzz");
b.closeBox();
b.openHorizontalBox("");

    b.create_small_rackknob(PARAM("Level"), "Level");

    b.create_small_rackknobr(PARAM("Fuzz"), "Fuzz");
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

} // end namespace fuzzface
