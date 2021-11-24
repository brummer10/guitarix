// generated from file '../src/faust/gxfeed.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace gxfeed {

class Dsp: public PluginDef {
private:
	int fSampleRate;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fVslider0;
	int IOTA;
	double fVec0[2048];
	double fRec6[2];
	double fVec1[1024];
	double fRec8[2];
	double fVec2[1024];
	double fRec10[2];
	double fVec3[1024];
	double fRec12[2];
	double fVec4[128];
	double fRec4[2];
	double fVec5[64];
	double fRec2[2];
	double fVec6[12];
	double fRec0[2];

	void clear_state_f();
	void init(unsigned int sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static void init_static(unsigned int sample_rate, PluginDef*);
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
	id = "gxfeed";
	name = N_("gxfeed");
	groups = 0;
	description = ""; // description (tooltip)
	category = "";       // category
	shortname = "";     // shortname
	mono_audio = 0;
	stereo_audio = compute_static;
	set_samplerate = init_static;
	activate_plugin = 0;
	register_params = register_params_static;
	load_ui = 0;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int l0 = 0; (l0 < 2048); l0 = (l0 + 1)) fVec0[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec6[l1] = 0.0;
	for (int l2 = 0; (l2 < 1024); l2 = (l2 + 1)) fVec1[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fRec8[l3] = 0.0;
	for (int l4 = 0; (l4 < 1024); l4 = (l4 + 1)) fVec2[l4] = 0.0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fRec10[l5] = 0.0;
	for (int l6 = 0; (l6 < 1024); l6 = (l6 + 1)) fVec3[l6] = 0.0;
	for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) fRec12[l7] = 0.0;
	for (int l8 = 0; (l8 < 128); l8 = (l8 + 1)) fVec4[l8] = 0.0;
	for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) fRec4[l9] = 0.0;
	for (int l10 = 0; (l10 < 64); l10 = (l10 + 1)) fVec5[l10] = 0.0;
	for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) fRec2[l11] = 0.0;
	for (int l12 = 0; (l12 < 12); l12 = (l12 + 1)) fVec6[l12] = 0.0;
	for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) fRec0[l13] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int sample_rate)
{
	fSampleRate = sample_rate;
	IOTA = 0;
	clear_state_f();
}

void Dsp::init_static(unsigned int sample_rate, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
	int iSlow0 = int(double(fCheckbox0));
	double fSlow1 = double(fVslider0);
	double fSlow2 = (1.0 - std::max<double>(0.0, fSlow1));
	double fSlow3 = (1.0 - std::max<double>(0.0, (-1.0 * fSlow1)));
	for (int i0 = 0; (i0 < count); i0 = (i0 + 1)) {
		double fTemp0 = double(input1[i0]);
		double fTemp1 = (0.20000000000000001 * fTemp0);
		double fTemp2 = (fTemp1 + (0.76400000000000001 * fRec6[1]));
		fVec0[(IOTA & 2047)] = fTemp2;
		fRec6[0] = fVec0[((IOTA - 1123) & 2047)];
		double fRec7 = fTemp2;
		double fTemp3 = (fTemp1 + (0.78300000000000003 * fRec8[1]));
		fVec1[(IOTA & 1023)] = fTemp3;
		fRec8[0] = fVec1[((IOTA - 1011) & 1023)];
		double fRec9 = fTemp3;
		double fTemp4 = ((0.82699999999999996 * fRec10[1]) + fTemp1);
		fVec2[(IOTA & 1023)] = fTemp4;
		fRec10[0] = fVec2[((IOTA - 778) & 1023)];
		double fRec11 = fTemp4;
		double fTemp5 = (fTemp1 + (0.80500000000000005 * fRec12[1]));
		fVec3[(IOTA & 1023)] = fTemp5;
		fRec12[0] = fVec3[((IOTA - 901) & 1023)];
		double fRec13 = fTemp5;
		double fTemp6 = ((0.69999999999999996 * fRec4[1]) + (fRec7 + (fRec9 + (fRec11 + fRec13))));
		fVec4[(IOTA & 127)] = fTemp6;
		fRec4[0] = fVec4[((IOTA - 124) & 127)];
		double fRec5 = (0.0 - (0.69999999999999996 * fTemp6));
		double fTemp7 = (fRec4[1] + (fRec5 + (0.69999999999999996 * fRec2[1])));
		fVec5[(IOTA & 63)] = fTemp7;
		fRec2[0] = fVec5[((IOTA - 41) & 63)];
		double fRec3 = (0.0 - (0.69999999999999996 * fTemp7));
		double fTemp8 = (fRec2[1] + (fRec3 + (0.69999999999999996 * fRec0[1])));
		fVec6[0] = fTemp8;
		fRec0[0] = fVec6[11];
		double fRec1 = (0.0 - (0.69999999999999996 * fTemp8));
		double fTemp9 = (iSlow0 ? ((fSlow2 * fTemp0) + (fSlow3 * (fRec1 + fRec0[1]))) : double(input0[i0]));
		output0[i0] = FAUSTFLOAT(fTemp9);
		output1[i0] = FAUSTFLOAT(fTemp9);
		IOTA = (IOTA + 1);
		fRec6[1] = fRec6[0];
		fRec8[1] = fRec8[0];
		fRec10[1] = fRec10[0];
		fRec12[1] = fRec12[0];
		fRec4[1] = fRec4[0];
		fRec2[1] = fRec2[0];
		for (int j0 = 11; (j0 > 0); j0 = (j0 - 1)) {
			fVec6[j0] = fVec6[(j0 - 1)];
		}
		fRec0[1] = fRec0[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerFloatVar("amp.feed_on_off",N_("reverb_on_of"),"B","",&fCheckbox0, 0.0, 0.0, 1.0, 1.0, 0);
	reg.registerFloatVar("amp.wet_dry","","S","",&fVslider0, 0.0, -1.0, 1.0, 0.01, 0);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

PluginDef *plugin() {
	return new Dsp();
}

void Dsp::del_instance(PluginDef *p)
{
	delete static_cast<Dsp*>(p);
}

} // end namespace gxfeed
