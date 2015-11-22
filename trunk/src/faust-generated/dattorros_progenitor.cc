// generated from file '../src/faust/dattorros_progenitor.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)


namespace dattorros_progenitor {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	class SIG0 {
	  private:
		int 	fSamplingFreq;
		int 	iRec18[2];
	  public:
		int getNumInputs() 	{ return 0; }
		int getNumOutputs() 	{ return 1; }
		void init(int samplingFreq) {
			fSamplingFreq = samplingFreq;
			for (int i=0; i<2; i++) iRec18[i] = 0;
		}
		void fill (int count, double output[]) {
			for (int i=0; i<count; i++) {
				iRec18[0] = (1 + iRec18[1]);
				output[i] = sin((9.587379924285257e-05 * double((iRec18[0] - 1))));
				// post processing
				iRec18[1] = iRec18[0];
			}
		}
	};
			FAUSTFLOAT 	fslider0;
	FAUSTFLOAT 	fslider1;
	int 	IOTA;
	double 	fVec0[65536];
	FAUSTFLOAT 	fslider2;
	int 	iConst0;
	double 	fConst1;
	FAUSTFLOAT 	fslider3;
	double 	fRec17[3];
	double 	fVec1[1024];
	int 	iConst2;
	double 	fRec15[2];
	double 	fVec2[1024];
	int 	iConst3;
	double 	fRec13[2];
	double 	fVec3[4096];
	int 	iConst4;
	double 	fRec11[2];
	double 	fVec4[2048];
	int 	iConst5;
	double 	fRec9[2];
	FAUSTFLOAT 	fslider4;
	double 	fVec5[8192];
	static double 	ftbl0[65536];
	double 	fConst6;
	double 	fRec19[2];
	FAUSTFLOAT 	fslider5;
	int 	iConst7;
	double 	fRec7[2];
	double 	fRec8[32768];
	int 	iConst8;
	FAUSTFLOAT 	fslider6;
	double 	fRec6[3];
	FAUSTFLOAT 	fslider7;
	FAUSTFLOAT 	fslider8;
	double 	fVec6[16384];
	int 	iConst9;
	double 	fRec4[2];
	double 	fRec5[32768];
	int 	iConst10;
	double 	fRec0[2];
	double 	fVec7[8192];
	int 	iConst11;
	double 	fRec23[2];
	double 	fRec24[32768];
	int 	iConst12;
	double 	fRec22[3];
	double 	fVec8[32768];
	int 	iConst13;
	double 	fRec20[2];
	double 	fRec21[32768];
	int 	iConst14;
	double 	fRec1[2];
	FAUSTFLOAT 	fslider9;
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


double Dsp::ftbl0[65536];

Dsp::Dsp()
	: PluginDef() {
	version = PLUGINDEF_VERSION;
	flags = 0;
	id = "dattorros_progenitor";
	name = N_("Plate reverb");
	groups = 0;
	description = ""; // description (tooltip)
	category = N_("Reverb");       // category
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
	for (int i=0; i<65536; i++) fVec0[i] = 0;
	for (int i=0; i<3; i++) fRec17[i] = 0;
	for (int i=0; i<1024; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<1024; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<4096; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2048; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<8192; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<32768; i++) fRec8[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<16384; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<32768; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<8192; i++) fVec7[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<32768; i++) fRec24[i] = 0;
	for (int i=0; i<3; i++) fRec22[i] = 0;
	for (int i=0; i<32768; i++) fVec8[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<32768; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
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
	fConst1 = (0.001 * iConst0);
	iConst2 = int((0.004771345048889486 * iConst0));
	iConst3 = int((0.0035953092974026412 * iConst0));
	iConst4 = int((0.01273478713752898 * iConst0));
	iConst5 = int((0.009307482947481604 * iConst0));
	fConst6 = (1.0 / double(iConst0));
	iConst7 = int((0.022042270085010585 * iConst0));
	iConst8 = int((0.14962534861059776 * iConst0));
	iConst9 = int((0.060481838647894894 * iConst0));
	iConst10 = int((0.12499579987231611 * iConst0));
	iConst11 = int((0.029972111152179026 * iConst0));
	iConst12 = int((0.14169550754342933 * iConst0));
	iConst13 = int((0.08924431302711602 * iConst0));
	iConst14 = int((0.10628003091293975 * iConst0));
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
	double 	fSlow0 = double(fslider0);
	double 	fSlow1 = double(fslider1);
	double 	fSlow2 = (fConst1 * double(fslider2));
	int 	iSlow3 = int(fSlow2);
	int 	iSlow4 = (1 + iSlow3);
	int 	iSlow5 = int((int(iSlow4) & 65535));
	double 	fSlow6 = (fSlow2 - iSlow3);
	int 	iSlow7 = int((iSlow3 & 65535));
	double 	fSlow8 = (iSlow4 - fSlow2);
	double 	fSlow9 = double(fslider3);
	double 	fSlow10 = (0.5 * fSlow9);
	double 	fSlow11 = (1 - fSlow9);
	double 	fSlow12 = double(fslider4);
	double 	fSlow13 = (0.5 * double(fslider5));
	double 	fSlow14 = double(fslider6);
	double 	fSlow15 = (1 - fSlow14);
	double 	fSlow16 = double(fslider7);
	double 	fSlow17 = double(fslider8);
	double 	fSlow18 = double(fslider9);
	double 	fSlow19 = (1 - fSlow18);
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input1[i];
		double fTemp1 = (double)input0[i];
		double fTemp2 = (fTemp1 + fTemp0);
		fVec0[IOTA&65535] = fTemp2;
		fRec17[0] = ((fSlow11 * fRec17[2]) + (fSlow10 * ((fSlow8 * fVec0[(IOTA-iSlow7)&65535]) + (fSlow6 * fVec0[(IOTA-iSlow5)&65535]))));
		fVec1[IOTA&1023] = (fRec17[0] + (fSlow1 * fRec15[1]));
		fRec15[0] = fVec1[(IOTA-iConst2)&1023];
		double 	fRec16 = (fRec15[1] - fRec17[0]);
		fVec2[IOTA&1023] = (fRec16 + (fSlow1 * fRec13[1]));
		fRec13[0] = fVec2[(IOTA-iConst3)&1023];
		double 	fRec14 = (fRec13[1] - fRec16);
		fVec3[IOTA&4095] = (fRec14 + (fSlow0 * fRec11[1]));
		fRec11[0] = fVec3[(IOTA-iConst4)&4095];
		double 	fRec12 = (fRec11[1] - fRec14);
		fVec4[IOTA&2047] = (fRec12 + (fSlow0 * fRec9[1]));
		fRec9[0] = fVec4[(IOTA-iConst5)&2047];
		double 	fRec10 = (fRec9[1] - fRec12);
		double fTemp3 = (0.3 * fRec10);
		double fTemp4 = (0.5 * fRec1[1]);
		double fTemp5 = (fTemp4 + ((fSlow12 * fRec7[1]) + fTemp3));
		fVec5[IOTA&8191] = fTemp5;
		double fTemp6 = (fConst6 + fRec19[1]);
		fRec19[0] = (fTemp6 - floor(fTemp6));
		double fTemp7 = (fSlow13 * (1 + ftbl0[int((65536.0 * fRec19[0]))]));
		int iTemp8 = int(fTemp7);
		int iTemp9 = (1 + iTemp8);
		int iTemp10 = int((int(iTemp9) & 16));
		double fTemp11 = (fTemp7 - iTemp8);
		double fTemp12 = (iTemp9 - fTemp7);
		int iTemp13 = int((iTemp8 & 16));
		fRec7[0] = ((fVec5[(IOTA-int((iConst7 + iTemp13)))&8191] * fTemp12) + (fTemp11 * fVec5[(IOTA-int((iConst7 + iTemp10)))&8191]));
		fRec8[IOTA&32767] = (fRec7[1] - (fTemp4 + fTemp3));
		fRec6[0] = ((fSlow14 * fRec6[2]) + (fSlow15 * fRec8[(IOTA-iConst8)&32767]));
		double fTemp14 = (fSlow16 * fRec6[0]);
		fVec6[IOTA&16383] = ((fSlow17 * fRec4[1]) + fTemp14);
		fRec4[0] = fVec6[(IOTA-iConst9)&16383];
		fRec5[IOTA&32767] = (fRec4[1] - fTemp14);
		fRec0[0] = (fSlow16 * fRec5[(IOTA-iConst10)&32767]);
		double fTemp15 = (0.5 * fRec0[1]);
		double fTemp16 = (fTemp15 + (fTemp3 + (fSlow12 * fRec23[1])));
		fVec7[IOTA&8191] = fTemp16;
		fRec23[0] = ((fTemp12 * fVec7[(IOTA-int((iConst11 + iTemp13)))&8191]) + (fTemp11 * fVec7[(IOTA-int((iConst11 + iTemp10)))&8191]));
		fRec24[IOTA&32767] = (fRec23[1] - (fTemp3 + fTemp15));
		fRec22[0] = ((fSlow14 * fRec22[2]) + (fSlow15 * fRec24[(IOTA-iConst12)&32767]));
		double fTemp17 = (fSlow16 * fRec22[0]);
		fVec8[IOTA&32767] = ((fSlow17 * fRec20[1]) + fTemp17);
		fRec20[0] = fVec8[(IOTA-iConst13)&32767];
		fRec21[IOTA&32767] = (fRec20[1] - fTemp17);
		fRec1[0] = (fSlow16 * fRec21[(IOTA-iConst14)&32767]);
		double 	fRec2 = fRec8[(IOTA-0)&32767];
		double 	fRec3 = fRec24[(IOTA-0)&32767];
		output0[i] = (FAUSTFLOAT)((fSlow19 * fTemp1) + (fSlow18 * (fRec0[0] + fRec2)));
		output1[i] = (FAUSTFLOAT)((fSlow19 * fTemp0) + (fSlow18 * (fRec1[0] + fRec3)));
		// post processing
		fRec1[1] = fRec1[0];
		fRec20[1] = fRec20[0];
		fRec22[2] = fRec22[1]; fRec22[1] = fRec22[0];
		fRec23[1] = fRec23[0];
		fRec0[1] = fRec0[0];
		fRec4[1] = fRec4[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec7[1] = fRec7[0];
		fRec19[1] = fRec19[0];
		fRec9[1] = fRec9[0];
		fRec11[1] = fRec11[0];
		fRec13[1] = fRec13[0];
		fRec15[1] = fRec15[0];
		fRec17[2] = fRec17[1]; fRec17[1] = fRec17[0];
		IOTA = IOTA+1;
	}

}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("dattorros_progenitor.bandwidth","","S","",&fslider3, 0.9, 0.1, 0.95, 0.0005);
	reg.registerVar("dattorros_progenitor.damping","","S","",&fslider6, 0.0005, 0.1, 0.95, 0.0005);
	reg.registerVar("dattorros_progenitor.decay","","S","",&fslider7, 0.1, 0.0, 0.5, 0.01);
	reg.registerVar("dattorros_progenitor.decay diff 1","","S","",&fslider4, 0.1, 0.0, 0.7, 0.01);
	reg.registerVar("dattorros_progenitor.decay diff 2","","S","",&fslider8, 0.1, 0.0, 0.5, 0.01);
	reg.registerVar("dattorros_progenitor.dry/wet","","S","",&fslider9, 0.5, 0.0, 1.0, 0.05);
	reg.registerVar("dattorros_progenitor.excursion","","S","",&fslider5, 0.0, 0.0, 16.0, 0.5);
	reg.registerVar("dattorros_progenitor.input diff 1","","S","",&fslider1, 0.1, 0.0, 0.75, 0.01);
	reg.registerVar("dattorros_progenitor.input diff 2","","S","",&fslider0, 0.1, 0.0, 0.625, 0.01);
	reg.registerVar("dattorros_progenitor.predelay ms","","S","",&fslider2, 0.0, 0.0, 2e+02, 1e+01);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("dattorros_progenitor" "." p)
// dattorros progenitor (Plate reverb)

b.openHorizontalhideBox("");
b.create_master_slider(PARAM("dry/wet"), _("drt/wet"));
b.closeBox();

b.openHorizontalBox("");
b.openVerticalBox("");
b.openHorizontalBox("");
{
	b.create_small_rackknob(PARAM("predelay ms"),  _("predelay ms"));
	b.create_small_rackknob(PARAM("bandwidth"),    _(" bandwidth "));
	b.create_small_rackknob(PARAM("input diff 1"), _(" in diff 1 "));
	b.create_small_rackknob(PARAM("input diff 2"), _(" in diff 2 "));
	b.create_small_rackknob(PARAM("excursion"),    _(" excursion "));

	
}
b.closeBox();
b.openHorizontalBox("");
{
	b.create_small_rackknob(PARAM("decay"),        _("  decay   "));
	b.create_small_rackknob(PARAM("decay diff 1"), _("dec diff 1"));
	b.create_small_rackknob(PARAM("decay diff 2"), _("dec diff 2"));
	b.create_small_rackknob(PARAM("damping"),      _("HF damping"));
	b.create_small_rackknobr(PARAM("dry/wet"),     _("  dry/wet "));
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

} // end namespace dattorros_progenitor
