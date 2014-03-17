// generated from file '../src/faust/duck_delay_st.dsp' by dsp2cc:
// Code generated with Faust 0.9.46 (http://faust.grame.fr)


namespace duck_delay_st {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT 	fslider1;
	int 	IOTA;
	double 	fVec0[524288];
	int 	iConst0;
	double 	fConst1;
	FAUSTFLOAT 	fslider2;
	double 	fConst2;
	double 	fRec3[2];
	double 	fConst3;
	double 	fRec2[2];
	double 	fRec0[2];
	double 	fVec1[524288];
	double 	fRec4[2];
	double 	fRec1[2];
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
	double 	fRec7[2];
	double 	fRec6[3];
	double 	fConst16;
	double 	fRec5[3];
	FAUSTFLOAT 	fslider3;
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
	double 	fRec10[2];
	double 	fRec9[3];
	double 	fRec8[3];
	FAUSTFLOAT 	fslider4;
	double 	fRec11[2];
	FAUSTFLOAT 	fslider5;
	double 	fConst27;
	FAUSTFLOAT 	fslider6;
	double 	fRec14[2];
	double 	fRec13[2];
	FAUSTFLOAT 	fslider7;
	double 	fRec12[2];
	double 	fRec17[2];
	double 	fRec16[3];
	double 	fRec15[3];
	double 	fRec20[2];
	double 	fRec19[3];
	double 	fRec18[3];
	double 	fRec23[2];
	double 	fRec22[2];
	double 	fRec21[2];
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
	id = "duckDelaySt";
	name = N_("Duck Delay St");
	groups = 0;
	description = ""; // description (tooltip)
	category = N_("Echo / Delay");       // category
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
	for (int i=0; i<524288; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<524288; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<3; i++) fRec9[i] = 0;
	for (int i=0; i<3; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<3; i++) fRec16[i] = 0;
	for (int i=0; i<3; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<3; i++) fRec19[i] = 0;
	for (int i=0; i<3; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	IOTA = 0;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = exp((0 - (1e+01 / iConst0)));
	fConst2 = (1.0 - fConst1);
	fConst3 = (0.001 * iConst0);
	fConst4 = tan((2764.601535159018 / iConst0));
	fConst5 = (1.0 / faustpower<2>(fConst4));
	fConst6 = (2 * (1 - fConst5));
	fConst7 = (1.0 / fConst4);
	fConst8 = (1 + ((fConst7 - 0.6180339887498947) / fConst4));
	fConst9 = (1.0 / (1 + ((0.6180339887498947 + fConst7) / fConst4)));
	fConst10 = (1 + ((fConst7 - 1.6180339887498947) / fConst4));
	fConst11 = (1.0 / (1 + ((1.6180339887498947 + fConst7) / fConst4)));
	fConst12 = (1 + fConst7);
	fConst13 = (0 - ((1 - fConst7) / fConst12));
	fConst14 = (0 - fConst7);
	fConst15 = (1.0 / fConst12);
	fConst16 = (2 * (0 - fConst5));
	fConst17 = tan((1382.300767579509 / iConst0));
	fConst18 = (2 * (1 - (1.0 / faustpower<2>(fConst17))));
	fConst19 = (1.0 / fConst17);
	fConst20 = (1 + ((fConst19 - 0.6180339887498947) / fConst17));
	fConst21 = (1.0 / (1 + ((0.6180339887498947 + fConst19) / fConst17)));
	fConst22 = (1 + ((fConst19 - 1.6180339887498947) / fConst17));
	fConst23 = (1.0 / (1 + ((fConst19 + 1.6180339887498947) / fConst17)));
	fConst24 = (1 + fConst19);
	fConst25 = (0 - ((1 - fConst19) / fConst24));
	fConst26 = (1.0 / fConst24);
	fConst27 = (1.0 / iConst0);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
	double 	fSlow0 = fslider0;
	double 	fSlow1 = (1 - fSlow0);
	double 	fSlow2 = fslider1;
	double 	fSlow3 = (fConst2 * fslider2);
	double 	fSlow4 = (1 - (fSlow0 * fSlow2));
	double 	fSlow5 = fslider3;
	double 	fSlow6 = (fConst9 * (pow(10,(0.6 * fSlow5)) - 1));
	double 	fSlow7 = (fConst21 * (pow(10,(0.6 * (1 - fSlow5))) - 1));
	double 	fSlow8 = (0.0010000000000000009 * pow(10,(0.05 * fslider4)));
	double 	fSlow9 = exp((0 - (fConst27 / fslider5)));
	double 	fSlow10 = exp((0 - (fConst27 / fslider6)));
	double 	fSlow11 = (1.0 - fSlow10);
	double 	fSlow12 = (1.0 - fSlow9);
	double 	fSlow13 = pow(10,(0.05 * fslider7));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		double fTemp1 = (fTemp0 + (fSlow2 * ((fSlow0 * fRec1[1]) + (fSlow1 * fRec2[1]))));
		fVec0[IOTA&524287] = fTemp1;
		fRec3[0] = (fSlow3 + (fConst1 * fRec3[1]));
		double fTemp2 = (fConst3 * fRec3[0]);
		int iTemp3 = int(fTemp2);
		int iTemp4 = int((iTemp3 & 393215));
		int iTemp5 = (1 + iTemp3);
		double fTemp6 = (iTemp5 - fTemp2);
		int iTemp7 = int((int(iTemp5) & 393215));
		double fTemp8 = (fTemp2 - iTemp3);
		fRec2[0] = ((fTemp8 * fVec0[(IOTA-iTemp7)&524287]) + (fTemp6 * fVec0[(IOTA-iTemp4)&524287]));
		fRec0[0] = fRec2[0];
		double fTemp9 = (double)input1[i];
		double fTemp10 = ((fSlow4 * fTemp9) + (fSlow2 * ((fSlow0 * fRec0[1]) + (fSlow1 * fRec4[1]))));
		fVec1[IOTA&524287] = fTemp10;
		fRec4[0] = ((fTemp8 * fVec1[(IOTA-iTemp7)&524287]) + (fTemp6 * fVec1[(IOTA-iTemp4)&524287]));
		fRec1[0] = fRec4[0];
		fRec7[0] = ((fConst15 * ((fConst14 * fRec0[1]) + (fConst7 * fRec0[0]))) + (fConst13 * fRec7[1]));
		fRec6[0] = (fRec7[0] - (fConst11 * ((fConst10 * fRec6[2]) + (fConst6 * fRec6[1]))));
		fRec5[0] = ((fConst11 * (((fConst5 * fRec6[0]) + (fConst16 * fRec6[1])) + (fConst5 * fRec6[2]))) - (fConst9 * ((fConst8 * fRec5[2]) + (fConst6 * fRec5[1]))));
		fRec10[0] = ((fConst26 * (fRec0[0] + fRec0[1])) + (fConst25 * fRec10[1]));
		fRec9[0] = (fRec10[0] - (fConst23 * ((fConst22 * fRec9[2]) + (fConst18 * fRec9[1]))));
		fRec8[0] = ((fConst23 * (fRec9[2] + (fRec9[0] + (2 * fRec9[1])))) - (fConst21 * ((fConst20 * fRec8[2]) + (fConst18 * fRec8[1]))));
		fRec11[0] = (fSlow8 + (0.999 * fRec11[1]));
		double fTemp11 = fabs(fTemp0);
		fRec14[0] = ((fSlow11 * fTemp11) + (fSlow10 * max(fTemp11, fRec14[1])));
		fRec13[0] = ((fSlow12 * fRec14[0]) + (fSlow9 * fRec13[1]));
		fRec12[0] = ((fConst2 * (1 - ((fSlow13 * fRec13[0]) > 1))) + (fConst1 * fRec12[1]));
		output0[i] = (FAUSTFLOAT)(fTemp0 + (0.1778279410038923 * ((fRec12[0] * fRec11[0]) * ((fSlow7 * (fRec8[2] + (fRec8[0] + (2 * fRec8[1])))) + ((fSlow6 * (((fConst5 * fRec5[0]) + (fConst16 * fRec5[1])) + (fConst5 * fRec5[2]))) + (2 * fRec0[0]))))));
		fRec17[0] = ((fConst15 * ((fConst14 * fRec1[1]) + (fConst7 * fRec1[0]))) + (fConst13 * fRec17[1]));
		fRec16[0] = (fRec17[0] - (fConst11 * ((fConst10 * fRec16[2]) + (fConst6 * fRec16[1]))));
		fRec15[0] = ((fConst11 * (((fConst5 * fRec16[0]) + (fConst16 * fRec16[1])) + (fConst5 * fRec16[2]))) - (fConst9 * ((fConst8 * fRec15[2]) + (fConst6 * fRec15[1]))));
		fRec20[0] = ((fConst26 * (fRec1[0] + fRec1[1])) + (fConst25 * fRec20[1]));
		fRec19[0] = (fRec20[0] - (fConst23 * ((fConst22 * fRec19[2]) + (fConst18 * fRec19[1]))));
		fRec18[0] = ((fConst23 * (fRec19[2] + (fRec19[0] + (2 * fRec19[1])))) - (fConst21 * ((fConst20 * fRec18[2]) + (fConst18 * fRec18[1]))));
		double fTemp12 = fabs(fTemp9);
		fRec23[0] = ((fSlow11 * fTemp12) + (fSlow10 * max(fTemp12, fRec23[1])));
		fRec22[0] = ((fSlow12 * fRec23[0]) + (fSlow9 * fRec22[1]));
		fRec21[0] = ((fConst2 * (1 - ((fSlow13 * fRec22[0]) > 1))) + (fConst1 * fRec21[1]));
		output1[i] = (FAUSTFLOAT)(fTemp9 + (0.1778279410038923 * ((fRec11[0] * fRec21[0]) * ((fSlow7 * (fRec18[2] + (fRec18[0] + (2 * fRec18[1])))) + ((fSlow6 * (((fConst5 * fRec15[0]) + (fConst16 * fRec15[1])) + (fConst5 * fRec15[2]))) + (2 * fRec1[0]))))));
		// post processing
		fRec21[1] = fRec21[0];
		fRec22[1] = fRec22[0];
		fRec23[1] = fRec23[0];
		fRec18[2] = fRec18[1]; fRec18[1] = fRec18[0];
		fRec19[2] = fRec19[1]; fRec19[1] = fRec19[0];
		fRec20[1] = fRec20[0];
		fRec15[2] = fRec15[1]; fRec15[1] = fRec15[0];
		fRec16[2] = fRec16[1]; fRec16[1] = fRec16[0];
		fRec17[1] = fRec17[0];
		fRec12[1] = fRec12[0];
		fRec13[1] = fRec13[0];
		fRec14[1] = fRec14[0];
		fRec11[1] = fRec11[0];
		fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec10[1] = fRec10[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec7[1] = fRec7[0];
		fRec1[1] = fRec1[0];
		fRec4[1] = fRec4[0];
		fRec0[1] = fRec0[0];
		fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		IOTA = IOTA+1;
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("duckDelaySt.amount","","S","",&fslider7, 0.5, 0.0, 56.0, 0.05);
	reg.registerVar("duckDelaySt.attack","","S","",&fslider5, 0.1, 0.05, 0.5, 0.05);
	reg.registerVar("duckDelaySt.coloration","","S","",&fslider3, 0.0, -1.0, 1.0, 0.05);
	reg.registerVar("duckDelaySt.effect","","S","",&fslider4, 0.0, -16.0, 4.0, 0.1);
	reg.registerVar("duckDelaySt.feedback","","S","",&fslider1, 0.0, 0.0, 1.0, 0.05);
	reg.registerVar("duckDelaySt.pingpong","","S","",&fslider0, 0.0, 0.0, 1.0, 0.05);
	reg.registerVar("duckDelaySt.release","","S","",&fslider6, 0.1, 0.05, 2.0, 0.05);
	reg.registerVar("duckDelaySt.time","","S","",&fslider2, 5e+02, 1.0, 2e+03, 1.0);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("duckDelaySt" "." p)
// ducking delay stereo

b.openHorizontalhideBox("");
b.create_master_slider(PARAM("effect"), _("effect"));
b.closeBox();


b.openHorizontalBox("");
b.openVerticalBox("");
b.openHorizontalBox("");
{
	b.create_small_rackknob(PARAM("time"),         _(" time ms "));
	b.create_small_rackknob(PARAM("feedback"),     _(" feedback "));
	b.create_small_rackknob(PARAM("pingpong"),     _(" ping-pong"));
	b.create_small_rackknob(PARAM("coloration"),   _("coloration"));	
}
b.closeBox();
b.openHorizontalBox("");
{
	b.create_small_rackknob(PARAM("attack"),        _(" attack "));
	b.create_small_rackknob(PARAM("release"),       _(" release "));
	b.create_small_rackknob(PARAM("amount"),        _(" amount "));
	b.create_small_rackknobr(PARAM("effect"),       _(" effect "));
}
b.closeBox();
b.closeBox();
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

} // end namespace duck_delay_st
