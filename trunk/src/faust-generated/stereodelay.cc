// generated from file '../src/faust/stereodelay.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)


namespace stereodelay {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	int 	IOTA;
	float *fVec0;
	int 	iVec1[2];
	FAUSTFLOAT 	fslider0;
	int 	iConst0;
	float 	fConst1;
	float 	fRec0[2];
	float 	fRec1[2];
	float 	fRec2[2];
	float 	fRec3[2];
	FAUSTFLOAT 	fslider1;
	float 	fConst2;
	float 	fRec4[2];
	float 	fRec5[2];
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT 	fslider2;
	float 	fRec6[2];
	float *fVec2;
	FAUSTFLOAT 	fslider3;
	float 	fRec7[2];
	float 	fRec8[2];
	float 	fRec9[2];
	float 	fRec10[2];
	FAUSTFLOAT 	fslider4;
	float 	fRec11[2];
	bool mem_allocated;
	void mem_alloc();
	void mem_free();
	void clear_state_f();
	int activate(bool start);
	int load_ui_f(const UiBuilder& b, int form);
	void init(unsigned int samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static int activate_static(bool start, PluginDef*);
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
	: PluginDef(),
	  fVec0(0),
	  fVec2(0),
	  mem_allocated(false) {
	version = PLUGINDEF_VERSION;
	flags = 0;
	id = "stereodelay";
	name = N_("Stereo Delay");
	groups = 0;
	description = ""; // description (tooltip)
	category = N_("Echo / Delay");       // category
	shortname = "";     // shortname
	mono_audio = 0;
	stereo_audio = compute_static;
	set_samplerate = init_static;
	activate_plugin = activate_static;
	register_params = register_params_static;
	load_ui = load_ui_f_static;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int i=0; i<262144; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) iVec1[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<262144; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
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
	fConst1 = (0.001f * iConst0);
	fConst2 = (6.283185307179586f / float(iConst0));
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void Dsp::mem_alloc()
{
	if (!fVec0) fVec0 = new float[262144];
	if (!fVec2) fVec2 = new float[262144];
	mem_allocated = true;
}

void Dsp::mem_free()
{
	mem_allocated = false;
	if (fVec0) { delete fVec0; fVec0 = 0; }
	if (fVec2) { delete fVec2; fVec2 = 0; }
}

int Dsp::activate(bool start)
{
	if (start) {
		if (!mem_allocated) {
			mem_alloc();
			clear_state_f();
		}
	} else if (mem_allocated) {
		mem_free();
	}
	return 0;
}

int Dsp::activate_static(bool start, PluginDef *p)
{
	return static_cast<Dsp*>(p)->activate(start);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
	float 	fSlow0 = (fConst1 * float(fslider0));
	float 	fSlow1 = (fConst2 * float(fslider1));
	float 	fSlow2 = cosf(fSlow1);
	float 	fSlow3 = sinf(fSlow1);
	float 	fSlow4 = (0 - fSlow3);
	float 	fSlow5 = float(fcheckbox0);
	float 	fSlow6 = (0.0010000000000000009f * powf(10,(0.05f * float(fslider2))));
	float 	fSlow7 = (fConst1 * float(fslider3));
	float 	fSlow8 = (0.0010000000000000009f * powf(10,(0.05f * float(fslider4))));
	for (int i=0; i<count; i++) {
		float fTemp0 = (float)input0[i];
		fVec0[IOTA&262143] = fTemp0;
		iVec1[0] = 1;
		float fTemp1 = ((int((fRec0[1] != 0.0f)))?((int(((fRec1[1] > 0.0f) & (fRec1[1] < 1.0f))))?fRec0[1]:0):((int(((fRec1[1] == 0.0f) & (fSlow0 != fRec2[1]))))?0.0009765625f:((int(((fRec1[1] == 1.0f) & (fSlow0 != fRec3[1]))))?-0.0009765625f:0)));
		fRec0[0] = fTemp1;
		fRec1[0] = max(0.0f, min(1.0f, (fRec1[1] + fTemp1)));
		fRec2[0] = ((int(((fRec1[1] >= 1.0f) & (fRec3[1] != fSlow0))))?fSlow0:fRec2[1]);
		fRec3[0] = ((int(((fRec1[1] <= 0.0f) & (fRec2[1] != fSlow0))))?fSlow0:fRec3[1]);
		fRec4[0] = ((fSlow3 * fRec5[1]) + (fSlow2 * fRec4[1]));
		fRec5[0] = ((1 + ((fSlow2 * fRec5[1]) + (fSlow4 * fRec4[1]))) - iVec1[1]);
		fRec6[0] = ((0.999f * fRec6[1]) + fSlow6);
		output0[i] = (FAUSTFLOAT)(fVec0[IOTA&262143] + ((fRec6[0] * (1 - (fSlow5 * fRec4[0]))) * (((1.0f - fRec1[0]) * fVec0[(IOTA-int((int(fRec2[0]) & 262143)))&262143]) + (fRec1[0] * fVec0[(IOTA-int((int(fRec3[0]) & 262143)))&262143]))));
		float fTemp2 = (float)input1[i];
		fVec2[IOTA&262143] = fTemp2;
		float fTemp3 = ((int((fRec7[1] != 0.0f)))?((int(((fRec8[1] > 0.0f) & (fRec8[1] < 1.0f))))?fRec7[1]:0):((int(((fRec8[1] == 0.0f) & (fSlow7 != fRec9[1]))))?0.0009765625f:((int(((fRec8[1] == 1.0f) & (fSlow7 != fRec10[1]))))?-0.0009765625f:0)));
		fRec7[0] = fTemp3;
		fRec8[0] = max(0.0f, min(1.0f, (fRec8[1] + fTemp3)));
		fRec9[0] = ((int(((fRec8[1] >= 1.0f) & (fRec10[1] != fSlow7))))?fSlow7:fRec9[1]);
		fRec10[0] = ((int(((fRec8[1] <= 0.0f) & (fRec9[1] != fSlow7))))?fSlow7:fRec10[1]);
		fRec11[0] = ((0.999f * fRec11[1]) + fSlow8);
		output1[i] = (FAUSTFLOAT)(fVec2[IOTA&262143] + ((fRec11[0] * (1 - (fSlow5 * (0 - fRec4[0])))) * (((1.0f - fRec8[0]) * fVec2[(IOTA-int((int(fRec9[0]) & 262143)))&262143]) + (fRec8[0] * fVec2[(IOTA-int((int(fRec10[0]) & 262143)))&262143]))));
		// post processing
		fRec11[1] = fRec11[0];
		fRec10[1] = fRec10[0];
		fRec9[1] = fRec9[0];
		fRec8[1] = fRec8[0];
		fRec7[1] = fRec7[0];
		fRec6[1] = fRec6[0];
		fRec5[1] = fRec5[0];
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
		iVec1[1] = iVec1[0];
		IOTA = IOTA+1;
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("stereodelay.LFO freq","","S","",&fslider1, 0.2f, 0.0f, 5.0f, 0.01f);
	static const value_pair fcheckbox0_values[] = {{"linear"},{"pingpong"},{0}};
	reg.registerEnumVar("stereodelay.invert","","B","",fcheckbox0_values,&fcheckbox0, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("stereodelay.l_delay","","S","",&fslider0, 0.0f, 0.0f, 5e+03f, 1e+01f);
	reg.registerVar("stereodelay.l_gain","","S","",&fslider2, 0.0f, -2e+01f, 2e+01f, 0.1f);
	reg.registerVar("stereodelay.r_delay","","S","",&fslider3, 0.0f, 0.0f, 5e+03f, 1e+01f);
	reg.registerVar("stereodelay.r_gain","","S","",&fslider4, 0.0f, -2e+01f, 2e+01f, 0.1f);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("stereodelay" "." p)
// stereo delay
b.openHorizontalhideBox("");
b.closeBox();
b.openHorizontalBox("");
{
    b.create_small_rackknob(PARAM("l_gain"), _("left gain"));
    b.create_small_rackknob(PARAM("l_delay"), _("left delay"));
    b.openVerticalBox("");
    {
	b.create_small_rackknobr(PARAM("LFO freq"), _("LFO"));
	b.insertSpacer();
	b.create_selector(PARAM("invert"), 0);
	b.openFrameBox("");
	b.closeBox();
    }
    b.closeBox();
    b.create_small_rackknob(PARAM("r_gain"), _("right gain"));
    b.create_small_rackknob(PARAM("r_delay"), _("right delay"));
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

} // end namespace stereodelay
