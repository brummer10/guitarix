// generated from file '../src/faust/chorus_mono.dsp' by dsp2cc:
// Code generated with Faust 0.9.58 (http://faust.grame.fr)


namespace chorus_mono {

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
			FAUSTFLOAT 	fslider0;
	int 	IOTA;
	float *fVec0;
	FAUSTFLOAT 	fslider1;
	int 	iConst0;
	float 	fConst1;
	float 	fRec0[2];
	static float 	ftbl0[65536];
	float 	fConst2;
	FAUSTFLOAT 	fslider2;
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


float Dsp::ftbl0[65536];

Dsp::Dsp()
	: PluginDef(),
	  fVec0(0),
	  mem_allocated(false) {
	version = PLUGINDEF_VERSION;
	flags = 0;
	id = "chorus_mono";
	name = N_("Chorus Mono");
	groups = 0;
	description = ""; // description (tooltip)
	category = N_("Modulation");       // category
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
	for (int i=0; i<65536; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
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
	fConst2 = (0.01f * iConst0);
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void Dsp::mem_alloc()
{
	if (!fVec0) fVec0 = new float[65536];
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
	} else if (mem_allocated) {
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
	float 	fSlow0 = (0.01f * fslider0);
	float 	fSlow1 = (fSlow0 + (1 - fSlow0));
	float 	fSlow2 = (fConst1 * fslider1);
	float 	fSlow3 = fslider2;
	for (int i=0; i<count; i++) {
		float fTemp0 = (float)input0[i];
		float fTemp1 = (fSlow0 * fTemp0);
		fVec0[IOTA&65535] = fTemp1;
		float fTemp2 = (fSlow2 + fRec0[1]);
		fRec0[0] = (fTemp2 - floorf(fTemp2));
		float fTemp3 = (65536 * (fRec0[0] - floorf(fRec0[0])));
		float fTemp4 = floorf(fTemp3);
		int iTemp5 = int(fTemp4);
		float fTemp6 = (fConst2 * (1 + (0.02f * ((ftbl0[((1 + iTemp5) & 65535)] * (fTemp3 - fTemp4)) + (ftbl0[(iTemp5 & 65535)] * ((1 + fTemp4) - fTemp3))))));
		int iTemp7 = int(fTemp6);
		int iTemp8 = (1 + iTemp7);
		output0[i] = (FAUSTFLOAT)((fSlow3 * (((fTemp6 - iTemp7) * fVec0[(IOTA-int((int(iTemp8) & 65535)))&65535]) + ((iTemp8 - fTemp6) * fVec0[(IOTA-int((iTemp7 & 65535)))&65535]))) + (fSlow1 * fTemp0));
		// post processing
		fRec0[1] = fRec0[0];
		IOTA = IOTA+1;
	}
}

void __rt_func Dsp::compute_static(int count, float *input0, float *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("chorus_mono.level","","S","",&fslider2, 0.5f, 0.0f, 1.0f, 0.01f);
	reg.registerVar("chorus_mono.freq","","S","",&fslider1, 2.0f, 0.0f, 1e+01f, 0.01f);
	reg.registerVar("chorus_mono.wet_dry",N_("wet/dry"),"S",N_("percentage of processed signal in output signal"),&fslider0, 1e+02f, 0.0f, 1e+02f, 1.0f);
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

} // end namespace chorus_mono
