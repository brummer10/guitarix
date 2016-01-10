// generated from file '../src/faust/tonecontroll.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)


namespace tonecontroll {

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
	double 	fConst11;
	double 	fConst12;
	double 	fConst13;
	double 	fVec0[2];
	double 	fConst14;
	double 	fConst15;
	double 	fConst16;
	double 	fRec3[2];
	double 	fRec2[3];
	double 	fVec1[2];
	double 	fConst17;
	double 	fConst18;
	double 	fConst19;
	double 	fRec1[2];
	double 	fRec0[3];
	FAUSTFLOAT 	fslider0;
	double 	fRec4[2];
	double 	fConst20;
	double 	fRec6[2];
	double 	fRec5[3];
	double 	fConst21;
	FAUSTFLOAT 	fslider1;
	double 	fRec7[2];
	double 	fConst22;
	double 	fConst23;
	double 	fConst24;
	double 	fRec10[2];
	double 	fRec9[3];
	double 	fConst25;
	double 	fRec8[3];
	FAUSTFLOAT 	fslider2;
	double 	fRec11[2];
	FAUSTFLOAT 	fslider3;
	double 	fConst26;
	double 	fConst27;
	double 	fRec12[2];
	FAUSTFLOAT 	fcheckbox0;
	double 	fVec2[2];
	double 	fRec16[2];
	double 	fRec15[3];
	double 	fVec3[2];
	double 	fRec14[2];
	double 	fRec13[3];
	double 	fRec18[2];
	double 	fRec17[3];
	double 	fRec21[2];
	double 	fRec20[3];
	double 	fRec19[3];
	double 	fRec22[2];
	void clear_state_f();
	int load_ui_f(const UiBuilder& b, int form);
	void init(unsigned int samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static int load_ui_f_static(const UiBuilder& b, int form);
	static void init_static(unsigned int samplingFreq, PluginDef*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginDef*);
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
	id = "tonemodul";
	name = N_("3 Band EQ");
	groups = 0;
	description = ""; // description (tooltip)
	category = N_("Tone Control");       // category
	shortname = "";     // shortname
	mono_audio = 0;
	stereo_audio = compute_static;
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
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<3; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<3; i++) fRec9[i] = 0;
	for (int i=0; i<3; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<3; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<3; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<3; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<3; i++) fRec20[i] = 0;
	for (int i=0; i<3; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = tan((1884.9555921538758 / double(iConst0)));
	fConst2 = (1.0 / faustpower<2>(fConst1));
	fConst3 = (2 * (1 - fConst2));
	fConst4 = (1.0 / fConst1);
	fConst5 = (1 + ((fConst4 - 1.0000000000000004) / fConst1));
	fConst6 = (1.0 / (1 + ((fConst4 + 1.0000000000000004) / fConst1)));
	fConst7 = tan((7539.822368615503 / double(iConst0)));
	fConst8 = (1.0 / faustpower<2>(fConst7));
	fConst9 = (2 * (1 - fConst8));
	fConst10 = (1.0 / fConst7);
	fConst11 = (1 + ((fConst10 - 1.0000000000000004) / fConst7));
	fConst12 = (1 + ((1.0000000000000004 + fConst10) / fConst7));
	fConst13 = (1.0 / fConst12);
	fConst14 = (1 + fConst10);
	fConst15 = (1.0 / fConst14);
	fConst16 = (0 - ((1 - fConst10) / fConst14));
	fConst17 = (1 + fConst4);
	fConst18 = (1.0 / (fConst17 * fConst12));
	fConst19 = (0 - ((1 - fConst4) / fConst17));
	fConst20 = (0 - fConst4);
	fConst21 = (2 * (0 - fConst2));
	fConst22 = (1 + ((fConst4 - 1.0) / fConst1));
	fConst23 = (1.0 / (1 + ((1.0 + fConst4) / fConst1)));
	fConst24 = (0 - fConst10);
	fConst25 = (2 * (0 - fConst8));
	fConst26 = exp((0 - (0.2 / double(iConst0))));
	fConst27 = exp((0 - (2e+02 / double(iConst0))));
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
	double 	fSlow0 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider0))));
	double 	fSlow1 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider1))));
	double 	fSlow2 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider2))));
	double 	fSlow3 = double(fslider3);
	double 	fSlow4 = (5.0 * fSlow3);
	int 	iSlow5 = int(double(fcheckbox0));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fVec0[0] = fTemp0;
		fRec3[0] = ((fConst16 * fRec3[1]) + (fConst15 * (fVec0[0] + fVec0[1])));
		fRec2[0] = (fRec3[0] - (fConst13 * ((fConst11 * fRec2[2]) + (fConst9 * fRec2[1]))));
		double fTemp1 = (fRec2[2] + (fRec2[0] + (2 * fRec2[1])));
		fVec1[0] = fTemp1;
		fRec1[0] = ((fConst19 * fRec1[1]) + (fConst18 * (fVec1[0] + fVec1[1])));
		fRec0[0] = (fRec1[0] - (fConst6 * ((fConst5 * fRec0[2]) + (fConst3 * fRec0[1]))));
		fRec4[0] = ((0.999 * fRec4[1]) + fSlow0);
		fRec6[0] = ((fConst19 * fRec6[1]) + (fConst18 * ((fConst4 * fVec1[0]) + (fConst20 * fVec1[1]))));
		fRec5[0] = (fRec6[0] - (fConst6 * ((fConst5 * fRec5[2]) + (fConst3 * fRec5[1]))));
		fRec7[0] = ((0.999 * fRec7[1]) + fSlow1);
		double fTemp2 = (fConst3 * fRec8[1]);
		fRec10[0] = ((fConst16 * fRec10[1]) + (fConst15 * ((fConst10 * fVec0[0]) + (fConst24 * fVec0[1]))));
		fRec9[0] = (fRec10[0] - (fConst13 * ((fConst11 * fRec9[2]) + (fConst9 * fRec9[1]))));
		fRec8[0] = ((fConst13 * (((fConst8 * fRec9[0]) + (fConst25 * fRec9[1])) + (fConst8 * fRec9[2]))) - (fConst23 * ((fConst22 * fRec8[2]) + fTemp2)));
		fRec11[0] = ((0.999 * fRec11[1]) + fSlow2);
		double fTemp3 = ((fRec11[0] * (fRec8[2] + (fConst23 * (fTemp2 + (fConst22 * fRec8[0]))))) + (fConst6 * ((fRec7[0] * (((fConst2 * fRec5[0]) + (fConst21 * fRec5[1])) + (fConst2 * fRec5[2]))) + (fRec4[0] * (fRec0[2] + (fRec0[0] + (2 * fRec0[1])))))));
		double fTemp4 = max((double)1, fabs(fTemp3));
		double fTemp5 = ((fConst27 * (fRec12[1] < fTemp4)) + (fConst26 * (fRec12[1] >= fTemp4)));
		fRec12[0] = ((fRec12[1] * fTemp5) + (fTemp4 * (0 - (fTemp5 - 1))));
		double fTemp6 = max((double)0, ((20 * log10(fRec12[0])) + fSlow4));
		double fTemp7 = (2.0 * min((double)1, max((double)0, (0.09522902580706599 * fTemp6))));
		output0[i] = (FAUSTFLOAT)((iSlow5)?(fTemp3 * pow(10,(0.05 * (fSlow3 + ((fTemp6 * (0 - fTemp7)) / (1 + fTemp7)))))):fTemp3);
		double fTemp8 = (double)input1[i];
		fVec2[0] = fTemp8;
		fRec16[0] = ((fConst16 * fRec16[1]) + (fConst15 * (fVec2[0] + fVec2[1])));
		fRec15[0] = (fRec16[0] - (fConst13 * ((fConst11 * fRec15[2]) + (fConst9 * fRec15[1]))));
		double fTemp9 = (fRec15[2] + (fRec15[0] + (2 * fRec15[1])));
		fVec3[0] = fTemp9;
		fRec14[0] = ((fConst19 * fRec14[1]) + (fConst18 * (fVec3[0] + fVec3[1])));
		fRec13[0] = (fRec14[0] - (fConst6 * ((fConst5 * fRec13[2]) + (fConst3 * fRec13[1]))));
		fRec18[0] = ((fConst19 * fRec18[1]) + (fConst18 * ((fConst4 * fVec3[0]) + (fConst20 * fVec3[1]))));
		fRec17[0] = (fRec18[0] - (fConst6 * ((fConst5 * fRec17[2]) + (fConst3 * fRec17[1]))));
		double fTemp10 = (fConst3 * fRec19[1]);
		fRec21[0] = ((fConst16 * fRec21[1]) + (fConst15 * ((fConst10 * fVec2[0]) + (fConst24 * fVec2[1]))));
		fRec20[0] = (fRec21[0] - (fConst13 * ((fConst11 * fRec20[2]) + (fConst9 * fRec20[1]))));
		fRec19[0] = ((fConst13 * (((fConst8 * fRec20[0]) + (fConst25 * fRec20[1])) + (fConst8 * fRec20[2]))) - (fConst23 * ((fConst22 * fRec19[2]) + fTemp10)));
		double fTemp11 = ((fRec11[0] * (fRec19[2] + (fConst23 * (fTemp10 + (fConst22 * fRec19[0]))))) + (fConst6 * ((fRec7[0] * (((fConst2 * fRec17[0]) + (fConst21 * fRec17[1])) + (fConst2 * fRec17[2]))) + (fRec4[0] * (fRec13[2] + (fRec13[0] + (2 * fRec13[1])))))));
		double fTemp12 = max((double)1, fabs(fTemp11));
		double fTemp13 = ((fConst27 * (fRec22[1] < fTemp12)) + (fConst26 * (fRec22[1] >= fTemp12)));
		fRec22[0] = ((fRec22[1] * fTemp13) + (fTemp12 * (0 - (fTemp13 - 1))));
		double fTemp14 = max((double)0, ((20 * log10(fRec22[0])) + fSlow4));
		double fTemp15 = (2.0 * min((double)1, max((double)0, (0.09522902580706599 * fTemp14))));
		output1[i] = (FAUSTFLOAT)((iSlow5)?(fTemp11 * pow(10,(0.05 * (fSlow3 + ((fTemp14 * (0 - fTemp15)) / (1 + fTemp15)))))):fTemp11);
		// post processing
		fRec22[1] = fRec22[0];
		fRec19[2] = fRec19[1]; fRec19[1] = fRec19[0];
		fRec20[2] = fRec20[1]; fRec20[1] = fRec20[0];
		fRec21[1] = fRec21[0];
		fRec17[2] = fRec17[1]; fRec17[1] = fRec17[0];
		fRec18[1] = fRec18[0];
		fRec13[2] = fRec13[1]; fRec13[1] = fRec13[0];
		fRec14[1] = fRec14[0];
		fVec3[1] = fVec3[0];
		fRec15[2] = fRec15[1]; fRec15[1] = fRec15[0];
		fRec16[1] = fRec16[0];
		fVec2[1] = fVec2[0];
		fRec12[1] = fRec12[0];
		fRec11[1] = fRec11[0];
		fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec10[1] = fRec10[0];
		fRec7[1] = fRec7[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		fRec4[1] = fRec4[0];
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fVec1[1] = fVec1[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fVec0[1] = fVec0[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("tonemodul.Bass","","S","",&fslider0, 0.0, -5.0, 5.0, 0.01);
	reg.registerVar("tonemodul.Middle","","S","",&fslider1, 0.0, -5.0, 5.0, 0.01);
	reg.registerVar("tonemodul.ON","","B","",&fcheckbox0, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("tonemodul.Treble","","S","",&fslider2, 0.0, -5.0, 5.0, 0.01);
	reg.registerVar("tonemodul.sharper",N_("sharper"),"S","",&fslider3, -2.0, -2.5, 5.0, 0.1);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("tonemodul" "." p)
// 3 band eq
b.openHorizontalhideBox("");
b.closeBox();
b.openHorizontalBox("");
{
    b.create_small_rackknob(PARAM("Bass"), _("bass"));
    b.create_small_rackknob(PARAM("Middle"), _("middle"));
    b.create_small_rackknob(PARAM("Treble"), _("treble"));
    b.insertSpacer();
    b.create_switch_no_caption(sw_switchit, PARAM("ON"));
    b.create_small_rackknob(PARAM("sharper"), _("sharp"));
}
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

} // end namespace tonecontroll
