// generated from file '../src/faust/phaser.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)


namespace phaser {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT 	fcheckbox1;
	int 	iVec0[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT 	fslider3;
	int 	iConst0;
	float 	fConst1;
	FAUSTFLOAT 	fslider4;
	float 	fConst2;
	float 	fRec5[2];
	float 	fRec6[2];
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT 	fslider6;
	FAUSTFLOAT 	fslider7;
	float 	fRec4[3];
	float 	fRec3[3];
	float 	fRec2[3];
	float 	fRec1[3];
	float 	fRec0[2];
	float 	fRec11[3];
	float 	fRec10[3];
	float 	fRec9[3];
	float 	fRec8[3];
	float 	fRec7[2];
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
	id = "phaser";
	name = N_("Phaser");
	groups = 0;
	description = ""; // description (tooltip)
	category = N_("Modulation");       // category
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
	for (int i=0; i<2; i++) iVec0[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<3; i++) fRec4[i] = 0;
	for (int i=0; i<3; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<3; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<3; i++) fRec11[i] = 0;
	for (int i=0; i<3; i++) fRec10[i] = 0;
	for (int i=0; i<3; i++) fRec9[i] = 0;
	for (int i=0; i<3; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (1.0f / float(iConst0));
	fConst2 = (0.10471975511965977f / float(iConst0));
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
	float 	fSlow0 = (0.5f * ((int(float(fcheckbox0)))?2:float(fslider0)));
	float 	fSlow1 = ((int(float(fcheckbox1)))?(0 - fSlow0):fSlow0);
	float 	fSlow2 = float(fslider1);
	float 	fSlow3 = powf(10,(0.05f * float(fslider2)));
	float 	fSlow4 = expf((fConst1 * (0 - (3.141592653589793f * float(fslider3)))));
	float 	fSlow5 = faustpower<2>(fSlow4);
	float 	fSlow6 = (fConst2 * float(fslider4));
	float 	fSlow7 = cosf(fSlow6);
	float 	fSlow8 = sinf(fSlow6);
	float 	fSlow9 = (0 - fSlow8);
	float 	fSlow10 = float(fslider5);
	float 	fSlow11 = (6.283185307179586f * fSlow10);
	float 	fSlow12 = (0.5f * ((6.283185307179586f * max(fSlow10, float(fslider6))) - fSlow11));
	float 	fSlow13 = float(fslider7);
	float 	fSlow14 = (fConst1 * fSlow13);
	float 	fSlow15 = (0 - (2 * fSlow4));
	float 	fSlow16 = (fConst1 * faustpower<2>(fSlow13));
	float 	fSlow17 = (fConst1 * faustpower<3>(fSlow13));
	float 	fSlow18 = (fConst1 * faustpower<4>(fSlow13));
	float 	fSlow19 = (1 - fSlow0);
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		float fTemp0 = (float)input0[i];
		fRec5[0] = ((fSlow8 * fRec6[1]) + (fSlow7 * fRec5[1]));
		fRec6[0] = ((1 + ((fSlow7 * fRec6[1]) + (fSlow9 * fRec5[1]))) - iVec0[1]);
		float fTemp1 = (fSlow11 + (fSlow12 * (1 - fRec5[0])));
		float fTemp2 = (fRec4[1] * cosf((fSlow14 * fTemp1)));
		fRec4[0] = (0 - (((fSlow15 * fTemp2) + (fSlow5 * fRec4[2])) - ((fSlow3 * fTemp0) + (fSlow2 * fRec0[1]))));
		float fTemp3 = (fRec3[1] * cosf((fSlow16 * fTemp1)));
		fRec3[0] = ((fSlow15 * (fTemp2 - fTemp3)) + (fRec4[2] + (fSlow5 * (fRec4[0] - fRec3[2]))));
		float fTemp4 = (fRec2[1] * cosf((fSlow17 * fTemp1)));
		fRec2[0] = ((fSlow15 * (fTemp3 - fTemp4)) + (fRec3[2] + (fSlow5 * (fRec3[0] - fRec2[2]))));
		float fTemp5 = (fRec1[1] * cosf((fSlow18 * fTemp1)));
		fRec1[0] = ((fSlow15 * (fTemp4 - fTemp5)) + (fRec2[2] + (fSlow5 * (fRec2[0] - fRec1[2]))));
		fRec0[0] = ((fSlow5 * fRec1[0]) + ((fSlow15 * fTemp5) + fRec1[2]));
		output0[i] = (FAUSTFLOAT)((fSlow3 * (fTemp0 * fSlow19)) + (fRec0[0] * fSlow1));
		float fTemp6 = (float)input1[i];
		float fTemp7 = (fSlow11 + (fSlow12 * (1 - fRec6[0])));
		float fTemp8 = (fRec11[1] * cosf((fSlow14 * fTemp7)));
		fRec11[0] = (0 - (((fSlow15 * fTemp8) + (fSlow5 * fRec11[2])) - ((fSlow3 * fTemp6) + (fSlow2 * fRec7[1]))));
		float fTemp9 = (fRec10[1] * cosf((fSlow16 * fTemp7)));
		fRec10[0] = ((fSlow15 * (fTemp8 - fTemp9)) + (fRec11[2] + (fSlow5 * (fRec11[0] - fRec10[2]))));
		float fTemp10 = (fRec9[1] * cosf((fSlow17 * fTemp7)));
		fRec9[0] = ((fSlow15 * (fTemp9 - fTemp10)) + (fRec10[2] + (fSlow5 * (fRec10[0] - fRec9[2]))));
		float fTemp11 = (fRec8[1] * cosf((fSlow18 * fTemp7)));
		fRec8[0] = ((fSlow15 * (fTemp10 - fTemp11)) + (fRec9[2] + (fSlow5 * (fRec9[0] - fRec8[2]))));
		fRec7[0] = ((fSlow5 * fRec8[0]) + ((fSlow15 * fTemp11) + fRec8[2]));
		output1[i] = (FAUSTFLOAT)((fSlow3 * (fTemp6 * fSlow19)) + (fRec7[0] * fSlow1));
		// post processing
		fRec7[1] = fRec7[0];
		fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
		fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
		fRec0[1] = fRec0[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
		fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
		fRec6[1] = fRec6[0];
		fRec5[1] = fRec5[0];
		iVec0[1] = iVec0[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("phaser.MaxNotch1Freq","","S","",&fslider6, 8e+02f, 2e+01f, 1e+04f, 1.0f);
	reg.registerVar("phaser.MinNotch1Freq","","S","",&fslider5, 1e+02f, 2e+01f, 5e+03f, 1.0f);
	reg.registerVar("phaser.Notch width","","S","",&fslider3, 1e+03f, 1e+01f, 5e+03f, 1.0f);
	reg.registerVar("phaser.NotchFreq","","S","",&fslider7, 1.5f, 1.1f, 4.0f, 0.01f);
	static const value_pair fcheckbox0_values[] = {{"direct "},{" vibrato"},{0}};
	reg.registerEnumVar("phaser.VibratoMode","","B","",fcheckbox0_values,&fcheckbox0, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("phaser.depth","","S","",&fslider0, 1.0f, 0.0f, 1.0f, 0.01f);
	reg.registerVar("phaser.feedback gain","","S","",&fslider1, 0.0f, 0.0f, 1.0f, 0.01f);
	static const value_pair fcheckbox1_values[] = {{"linear"},{"invert"},{0}};
	reg.registerEnumVar("phaser.invert","","B","",fcheckbox1_values,&fcheckbox1, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("phaser.level","","S","",&fslider2, 0.0f, -6e+01f, 1e+01f, 0.1f);
	reg.registerVar("phaser.lfobpm",N_("Speed (bpm)"),"S",N_("Speed in Beats per Minute"),&fslider4, 3e+01f, 24.0f, 3.6e+02f, 1.0f);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("phaser" "." p)
// phaser
b.openHorizontalhideBox("");
b.create_master_slider(PARAM("level"), _("level"));
b.closeBox();
b.openHorizontalBox("");
{
    b.openHorizontalBox("");
    {
	b.create_small_rackknobr(PARAM("level"), _("  level "));
    }
    b.closeBox();
    b.openVerticalBox("");
    {
	b.openHorizontalBox("");
	{
	    b.create_small_rackknob(PARAM("feedback gain"), _(" feedback "));
	    b.create_small_rackknob(PARAM("depth"), _("depth"));
	    b.create_small_rackknob(PARAM("Notch width"), _("width"));
	    b.create_small_rackknob(PARAM("NotchFreq"), _("freq"));
	    b.create_small_rackknob(PARAM("MaxNotch1Freq"), _("max Hz"));
	    b.create_small_rackknob(PARAM("MinNotch1Freq"), _("min Hz"));
	    b.create_small_rackknob(PARAM("lfobpm"), _("speed (bpm)"));
	}
	b.closeBox();
	b.insertSpacer();
	b.openHorizontalBox("");
	{
	    b.insertSpacer();
	    b.create_selector(PARAM("invert"), "invert");
	    b.insertSpacer();
	    b.create_selector(PARAM("VibratoMode"),"VibratoMode" );
	    b.insertSpacer();
	    b.insertSpacer();
	    b.insertSpacer();
	    b.insertSpacer();
	    b.insertSpacer();
	}
	b.closeBox();
	b.openFrameBox("");
	b.closeBox();
    }
    b.closeBox();
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

} // end namespace phaser
