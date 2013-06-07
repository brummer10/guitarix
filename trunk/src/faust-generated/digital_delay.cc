// generated from file '../src/faust/digital_delay.dsp' by dsp2cc:
// Code generated with Faust 0.9.57 (http://faust.grame.fr)


namespace digital_delay {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT 	fslider1;
	int 	iConst0;
	float 	fConst1;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT 	fslider3;
	float 	fRec2[3];
	float 	fRec1[3];
	int 	IOTA;
	float *fVec0;
	float 	fConst2;
	float 	fConst3;
	FAUSTFLOAT 	fslider4;
	float 	fConst4;
	float 	fRec3[2];
	float 	fRec4[2];
	float 	fRec5[2];
	float 	fRec6[2];
	FAUSTFLOAT 	fslider5;
	float 	fRec0[2];
	bool mem_allocated;
	void mem_alloc();
	void mem_free();
	void clear_state_f();
	int activate(bool start);
	void init(unsigned int samplingFreq);
	void compute(int count, float *input0, float *output0);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static int activate_static(bool start, PluginDef*);
	static void init_static(unsigned int samplingFreq, PluginDef*);
	static void compute_static(int count, float *input0, float *output0, PluginDef*);
	static int register_params_static(const ParamReg& reg);
	static void del_instance(PluginDef *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginDef(),
	  fVec0(0),
	  mem_allocated(false) {
	version = PLUGINDEF_VERSION;
	flags = 0;
	id = "dide";
	name = N_("Digital Delay");
	groups = 0;
	description = N_("Digital Delay"); // description (tooltip)
	category = N_("Echo / Delay");       // category
	shortname = "";     // shortname
	mono_audio = compute_static;
	stereo_audio = 0;
	set_samplerate = init_static;
	activate_plugin = activate_static;
	register_params = register_params_static;
	load_ui = 0;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<3; i++) fRec1[i] = 0;
	for (int i=0; i<262144; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
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
	fConst1 = (3.141592653589793f / float(iConst0));
	IOTA = 0;
	fConst2 = (1e+01f / float(iConst0));
	fConst3 = (0 - fConst2);
	fConst4 = (0.001f * iConst0);
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void Dsp::mem_alloc()
{
	if (!fVec0) fVec0 = new float[262144];
	mem_allocated = true;
}

void Dsp::mem_free()
{
	mem_allocated = false;
	if (fVec0) { delete fVec0; fVec0 = 0; }
}

int Dsp::activate(bool start)
{
	if (start) {
		if (!mem_allocated) {
			mem_alloc();
			clear_state_f();
		}
	} else if (!mem_allocated) {
		mem_free();
	}
	return 0;
}

int Dsp::activate_static(bool start, PluginDef *p)
{
	return static_cast<Dsp*>(p)->activate(start);
}

void always_inline Dsp::compute(int count, float *input0, float *output0)
{
	float 	fSlow0 = fslider0;
	float 	fSlow1 = (0.01f * fSlow0);
	float 	fSlow2 = (1 - fSlow1);
	float 	fSlow3 = tanf((fConst1 * fslider1));
	float 	fSlow4 = (2 * (1 - (1.0f / faustpower<2>(fSlow3))));
	float 	fSlow5 = (1.0f / fSlow3);
	float 	fSlow6 = (1 + ((fSlow5 - 1.414213562373095f) / fSlow3));
	float 	fSlow7 = (1 + ((1.414213562373095f + fSlow5) / fSlow3));
	float 	fSlow8 = (1.0f / fSlow7);
	float 	fSlow9 = tanf((fConst1 * fslider2));
	float 	fSlow10 = (1.0f / faustpower<2>(fSlow9));
	float 	fSlow11 = (2 * (1 - fSlow10));
	float 	fSlow12 = (1.0f / fSlow9);
	float 	fSlow13 = (1 + ((fSlow12 - 1.414213562373095f) / fSlow9));
	float 	fSlow14 = (1.0f / (1 + ((1.414213562373095f + fSlow12) / fSlow9)));
	float 	fSlow15 = (0.01f * fslider3);
	float 	fSlow16 = (2 * (0 - fSlow10));
	float 	fSlow17 = (1e+02f / fSlow7);
	float 	fSlow18 = (fConst4 * fslider4);
	float 	fSlow19 = fslider5;
	for (int i=0; i<count; i++) {
		float fTemp0 = (float)input0[i];
		fRec2[0] = ((fSlow15 * fRec0[1]) - (fSlow14 * ((fSlow13 * fRec2[2]) + (fSlow11 * fRec2[1]))));
		fRec1[0] = ((fSlow14 * (((fSlow10 * fRec2[0]) + (fSlow16 * fRec2[1])) + (fSlow10 * fRec2[2]))) - (fSlow8 * ((fSlow6 * fRec1[2]) + (fSlow4 * fRec1[1]))));
		float fTemp1 = (fRec1[2] + (fRec1[0] + (2 * fRec1[1])));
		float fTemp2 = ((fSlow1 * fTemp0) + (fSlow8 * fTemp1));
		fVec0[IOTA&262143] = fTemp2;
		float fTemp3 = ((int((fRec3[1] != 0.0f)))?((int(((fRec4[1] > 0.0f) & (fRec4[1] < 1.0f))))?fRec3[1]:0):((int(((fRec4[1] == 0.0f) & (fSlow18 != fRec5[1]))))?fConst2:((int(((fRec4[1] == 1.0f) & (fSlow18 != fRec6[1]))))?fConst3:0)));
		fRec3[0] = fTemp3;
		fRec4[0] = max(0.0f, min(1.0f, (fRec4[1] + fTemp3)));
		fRec5[0] = ((int(((fRec4[1] >= 1.0f) & (fRec6[1] != fSlow18))))?fSlow18:fRec5[1]);
		fRec6[0] = ((int(((fRec4[1] <= 0.0f) & (fRec5[1] != fSlow18))))?fSlow18:fRec6[1]);
		fRec0[0] = (0.01f * ((fSlow19 * ((fRec4[0] * fVec0[(IOTA-int((int(fRec6[0]) & 262143)))&262143]) + ((1.0f - fRec4[0]) * fVec0[(IOTA-int((int(fRec5[0]) & 262143)))&262143]))) + ((fSlow0 * fTemp0) + (fSlow17 * fTemp1))));
		output0[i] = (FAUSTFLOAT)(fRec0[0] + (fSlow2 * fTemp0));
		// post processing
		fRec0[1] = fRec0[0];
		fRec6[1] = fRec6[0];
		fRec5[1] = fRec5[0];
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		IOTA = IOTA+1;
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
	}
}

void __rt_func Dsp::compute_static(int count, float *input0, float *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("dide.level","","S",N_("percentage of the delay gain level"),&fslider5, 5e+01f, 0.0f, 1e+02f, 1.0f);
	reg.registerVar("dide.delay","","S",N_("Delay Time in ms"),&fslider4, 2.5e+03f, 0.1f, 5e+03f, 0.1f);
	reg.registerVar("dide.feedback","","S",N_("percentage of the feedback level in the delay loop"),&fslider3, 5e+01f, 0.0f, 1e+02f, 1.0f);
	reg.registerVar("dide.show_always_highpass",N_("highpass (hz)"),"S",N_("highpass filter frequency in the feddback loop"),&fslider2, 1.2e+02f, 2e+01f, 2e+04f, 1.0f);
	reg.registerVar("dide.show_always_howpass",N_("lowpass (hz)"),"S",N_("lowpass filter frequency in the feddback loop"),&fslider1, 1.2e+04f, 2e+01f, 2e+04f, 1.0f);
	reg.registerVar("dide.gain","","S",N_("overall gain of the delay line in percent"),&fslider0, 1e+02f, 0.0f, 1e+02f, 1.0f);
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

} // end namespace digital_delay
