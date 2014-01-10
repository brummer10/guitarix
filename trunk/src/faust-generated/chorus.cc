// generated from file '../src/faust/chorus.dsp' by dsp2cc:
// Code generated with Faust 0.9.58 (http://faust.grame.fr)


namespace chorus {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	class SIG0 {
	  private:
		int 	fSamplingFreq;
		int 	iRec1[2];
	  public:
		int getNumInputs() 	{ return 0; }
		int getNumOutputs() 	{ return 1; }
		void init(int samplingFreq) {
			fSamplingFreq = samplingFreq;
			for (int i=0; i<2; i++) iRec1[i] = 0;
		}
		void fill (int count, float output[]) {
			for (int i=0; i<count; i++) {
				iRec1[0] = (1 + iRec1[1]);
				output[i] = sinf((9.587379924285257e-05f * (iRec1[0] - 1)));
				// post processing
				iRec1[1] = iRec1[0];
			}
		}
	};
			int 	IOTA;
	float *fVec0;
	FAUSTFLOAT 	fslider0;
	int 	iConst0;
	float 	fConst1;
	float 	fRec0[2];
	static float 	ftbl0[65536];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT 	fslider2;
	float 	fRec2[2];
	float 	fConst2;
	FAUSTFLOAT 	fslider3;
	float *fVec1;
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


float Dsp::ftbl0[65536];

Dsp::Dsp()
	: PluginDef(),
	  fVec0(0),
	  fVec1(0),
	  mem_allocated(false) {
	version = PLUGINDEF_VERSION;
	flags = 0;
	id = "chorus";
	name = N_("Chorus");
	groups = 0;
	description = ""; // description (tooltip)
	category = N_("Modulation");       // category
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
	for (int i=0; i<65536; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<65536; i++) fVec1[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	SIG0 sig0;
	sig0.init(samplingFreq);
	sig0.fill(65536,ftbl0);
	fSamplingFreq = samplingFreq;
	IOTA = 0;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (1.0f / float(iConst0));
	fConst2 = (0.5f * iConst0);
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void Dsp::mem_alloc()
{
	if (!fVec0) fVec0 = new float[65536];
	if (!fVec1) fVec1 = new float[65536];
	mem_allocated = true;
}

void Dsp::mem_free()
{
	mem_allocated = false;
	if (fVec0) { delete fVec0; fVec0 = 0; }
	if (fVec1) { delete fVec1; fVec1 = 0; }
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
	float 	fSlow0 = (fConst1 * fslider0);
	float 	fSlow1 = fslider1;
	float 	fSlow2 = (0.0010000000000000009f * fslider2);
	float 	fSlow3 = fslider3;
	for (int i=0; i<count; i++) {
		float fTemp0 = (float)input0[i];
		fVec0[IOTA&65535] = fTemp0;
		float fTemp1 = (fSlow0 + fRec0[1]);
		fRec0[0] = (fTemp1 - floorf(fTemp1));
		float fTemp2 = (65536 * (fRec0[0] - floorf(fRec0[0])));
		float fTemp3 = floorf(fTemp2);
		int iTemp4 = int(fTemp3);
		fRec2[0] = (fSlow2 + (0.999f * fRec2[1]));
		float fTemp5 = (fConst2 * (fRec2[0] * (1 + (fSlow1 * ((ftbl0[((1 + iTemp4) & 65535)] * (fTemp2 - fTemp3)) + (ftbl0[(iTemp4 & 65535)] * ((1 + fTemp3) - fTemp2)))))));
		int iTemp6 = int(fTemp5);
		int iTemp7 = (1 + iTemp6);
		output0[i] = (FAUSTFLOAT)(fVec0[IOTA&65535] + (fSlow3 * (((fTemp5 - iTemp6) * fVec0[(IOTA-int((int(iTemp7) & 65535)))&65535]) + ((iTemp7 - fTemp5) * fVec0[(IOTA-int((iTemp6 & 65535)))&65535]))));
		float fTemp8 = (float)input1[i];
		fVec1[IOTA&65535] = fTemp8;
		float fTemp9 = (0.25f + fRec0[0]);
		float fTemp10 = (65536 * (fTemp9 - floorf(fTemp9)));
		float fTemp11 = floorf(fTemp10);
		int iTemp12 = int(fTemp11);
		float fTemp13 = (fConst2 * (fRec2[0] * (1 + (fSlow1 * ((ftbl0[((1 + iTemp12) & 65535)] * (fTemp10 - fTemp11)) + (ftbl0[(iTemp12 & 65535)] * ((1 + fTemp11) - fTemp10)))))));
		int iTemp14 = int(fTemp13);
		int iTemp15 = (1 + iTemp14);
		output1[i] = (FAUSTFLOAT)(fVec1[IOTA&65535] + (fSlow3 * (((fTemp13 - iTemp14) * fVec1[(IOTA-int((int(iTemp15) & 65535)))&65535]) + ((iTemp15 - fTemp13) * fVec1[(IOTA-int((iTemp14 & 65535)))&65535]))));
		// post processing
		fRec2[1] = fRec2[0];
		fRec0[1] = fRec0[0];
		IOTA = IOTA+1;
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("chorus.delay","","S","",&fslider2, 0.02f, 0.0f, 0.2f, 0.01f);
	reg.registerVar("chorus.depth","","S","",&fslider1, 0.02f, 0.0f, 1.0f, 0.01f);
	reg.registerVar("chorus.freq","","S","",&fslider0, 3.0f, 0.0f, 1e+01f, 0.01f);
	reg.registerVar("chorus.level","","S","",&fslider3, 0.5f, 0.0f, 1.0f, 0.01f);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("chorus" "." p)
// ----- chorus
b.openHorizontalhideBox("");
b.create_master_slider(PARAM("level"), _("level"));
b.closeBox();
b.openHorizontalBox("");
{
    b.create_small_rackknobr(PARAM("level"), _("  level  "));
    b.create_small_rackknob(PARAM("delay"), _("  delay  "));
    b.create_small_rackknob(PARAM("depth"), _("  depth  "));
    b.create_small_rackknob(PARAM("freq"), _("  freq  "));
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

} // end namespace chorus
