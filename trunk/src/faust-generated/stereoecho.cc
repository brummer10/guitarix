// generated from file '../src/faust/stereoecho.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)


namespace stereoecho {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	int 	iVec0[2];
	FAUSTFLOAT 	fslider0;
	int 	iConst0;
	float 	fConst1;
	float 	fRec1[2];
	float 	fRec2[2];
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT 	fslider1;
	int 	iConst2;
	float 	fRec3[2];
	float 	fRec4[2];
	int 	iRec5[2];
	int 	iRec6[2];
	FAUSTFLOAT 	fslider2;
	int 	IOTA;
	float *fRec0;
	FAUSTFLOAT 	fslider3;
	float 	fRec8[2];
	float 	fRec9[2];
	int 	iRec10[2];
	int 	iRec11[2];
	FAUSTFLOAT 	fslider4;
	float *fRec7;
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
	  fRec0(0),
	  fRec7(0),
	  mem_allocated(false) {
	version = PLUGINDEF_VERSION;
	flags = 0;
	id = "stereoecho";
	name = N_("Stereo Echo");
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
	for (int i=0; i<2; i++) iVec0[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) iRec5[i] = 0;
	for (int i=0; i<2; i++) iRec6[i] = 0;
	for (int i=0; i<1048576; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) iRec10[i] = 0;
	for (int i=0; i<2; i++) iRec11[i] = 0;
	for (int i=0; i<1048576; i++) fRec7[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (0.10471975511965977f / float(iConst0));
	iConst2 = (60 * iConst0);
	IOTA = 0;
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void Dsp::mem_alloc()
{
	if (!fRec0) fRec0 = new float[1048576];
	if (!fRec7) fRec7 = new float[1048576];
	mem_allocated = true;
}

void Dsp::mem_free()
{
	mem_allocated = false;
	if (fRec0) { delete fRec0; fRec0 = 0; }
	if (fRec7) { delete fRec7; fRec7 = 0; }
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
	float 	fSlow1 = cosf(fSlow0);
	float 	fSlow2 = sinf(fSlow0);
	float 	fSlow3 = (0 - fSlow2);
	float 	fSlow4 = float(fcheckbox0);
	int 	iSlow5 = (int((float(iConst2) / float(fslider1))) - 1);
	float 	fSlow6 = (0.01f * float(fslider2));
	int 	iSlow7 = (int((float(iConst2) / float(fslider3))) - 1);
	float 	fSlow8 = (0.01f * float(fslider4));
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		fRec1[0] = ((fSlow2 * fRec2[1]) + (fSlow1 * fRec1[1]));
		fRec2[0] = ((1 + ((fSlow1 * fRec2[1]) + (fSlow3 * fRec1[1]))) - iVec0[1]);
		float fTemp0 = ((int((fRec3[1] != 0.0f)))?((int(((fRec4[1] > 0.0f) & (fRec4[1] < 1.0f))))?fRec3[1]:0):((int(((fRec4[1] == 0.0f) & (iSlow5 != iRec5[1]))))?0.0009765625f:((int(((fRec4[1] == 1.0f) & (iSlow5 != iRec6[1]))))?-0.0009765625f:0)));
		fRec3[0] = fTemp0;
		fRec4[0] = max(0.0f, min(1.0f, (fRec4[1] + fTemp0)));
		iRec5[0] = ((int(((fRec4[1] >= 1.0f) & (iRec6[1] != iSlow5))))?iSlow5:iRec5[1]);
		iRec6[0] = ((int(((fRec4[1] <= 0.0f) & (iRec5[1] != iSlow5))))?iSlow5:iRec6[1]);
		fRec0[IOTA&1048575] = ((float)input0[i] + (fSlow6 * ((((1.0f - fRec4[0]) * fRec0[(IOTA-int((1 + int((int(iRec5[0]) & 524287)))))&1048575]) + (fRec4[0] * fRec0[(IOTA-int((1 + int((int(iRec6[0]) & 524287)))))&1048575])) * (1 - (fSlow4 * fRec1[0])))));
		output0[i] = (FAUSTFLOAT)fRec0[(IOTA-0)&1048575];
		float fTemp1 = ((int((fRec8[1] != 0.0f)))?((int(((fRec9[1] > 0.0f) & (fRec9[1] < 1.0f))))?fRec8[1]:0):((int(((fRec9[1] == 0.0f) & (iSlow7 != iRec10[1]))))?0.0009765625f:((int(((fRec9[1] == 1.0f) & (iSlow7 != iRec11[1]))))?-0.0009765625f:0)));
		fRec8[0] = fTemp1;
		fRec9[0] = max(0.0f, min(1.0f, (fRec9[1] + fTemp1)));
		iRec10[0] = ((int(((fRec9[1] >= 1.0f) & (iRec11[1] != iSlow7))))?iSlow7:iRec10[1]);
		iRec11[0] = ((int(((fRec9[1] <= 0.0f) & (iRec10[1] != iSlow7))))?iSlow7:iRec11[1]);
		fRec7[IOTA&1048575] = ((float)input1[i] + (fSlow8 * ((((1.0f - fRec9[0]) * fRec7[(IOTA-int((1 + int((int(iRec10[0]) & 524287)))))&1048575]) + (fRec9[0] * fRec7[(IOTA-int((1 + int((int(iRec11[0]) & 524287)))))&1048575])) * (1 - (fSlow4 * (0 - fRec1[0]))))));
		output1[i] = (FAUSTFLOAT)fRec7[(IOTA-0)&1048575];
		// post processing
		iRec11[1] = iRec11[0];
		iRec10[1] = iRec10[0];
		fRec9[1] = fRec9[0];
		fRec8[1] = fRec8[0];
		IOTA = IOTA+1;
		iRec6[1] = iRec6[0];
		iRec5[1] = iRec5[0];
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
		iVec0[1] = iVec0[0];
	}

}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}

int Dsp::register_par(const ParamReg& reg)
{
	static const value_pair fcheckbox0_values[] = {{"linear"},{"pingpong"},{0}};
	reg.registerEnumVar("stereoecho.invert","","B","",fcheckbox0_values,&fcheckbox0, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("stereoecho.lbpm",N_("time (bpm)"),"S",N_("Echo in Beats per Minute"),&fslider1, 1.2e+02f, 24.0f, 3.6e+02f, 1.0f);
	reg.registerVar("stereoecho.lfobpm",N_("LFO freq (bpm)"),"S",N_("LFO in Beats per Minute"),&fslider0, 24.0f, 24.0f, 3.6e+02f, 1.0f);
	reg.registerVar("stereoecho.percent_l","","S","",&fslider2, 0.0f, 0.0f, 1e+02f, 0.1f);
	reg.registerVar("stereoecho.percent_r","","S","",&fslider4, 0.0f, 0.0f, 1e+02f, 0.1f);
	reg.registerVar("stereoecho.rbpm",N_("time (bpm)"),"S",N_("Echo in Beats per Minute"),&fslider3, 1.2e+02f, 24.0f, 3.6e+02f, 1.0f);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("stereoecho" "." p)
// echo
b.openHorizontalhideBox("");
b.closeBox();
b.openHorizontalBox("");
{
    b.openVerticalBox("");
    {
	b.create_small_rackknob(PARAM("percent_l"), _("left %"));
	b.insertSpacer();
    }
    b.closeBox();
    b.openVerticalBox("");
    {
	b.create_small_rackknob(PARAM("lbpm"), _("left time (bpm)"));
	b.insertSpacer();
    }
    b.closeBox();
    b.openVerticalBox("");
    {
	b.create_small_rackknobr(PARAM("lfobpm"), _("LFO (bpm)"));
	b.insertSpacer();
	b.create_selector(PARAM("invert"), "invert");
	b.openFrameBox("");
	b.closeBox();
    }
    b.closeBox();
    b.openVerticalBox("");
    {
	b.create_small_rackknob(PARAM("percent_r"), _("right %"));
	b.insertSpacer();
    }
    b.closeBox();
    b.openVerticalBox("");
    {
	b.create_small_rackknob(PARAM("rbpm"), _("right time (bpm)"));
	b.insertSpacer();
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

} // end namespace stereoecho
