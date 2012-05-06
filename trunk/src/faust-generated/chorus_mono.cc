// generated from file '../src/faust/chorus_mono.dsp' by dsp2cc:
// Code generated with Faust 0.9.43 (http://faust.grame.fr)


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
		void fill (int count, double output[]) {
			for (int i=0; i<count; i++) {
				iRec1[0] = (1 + iRec1[1]);
				output[i] = sin((9.587379924285257e-05 * (iRec1[0] - 1)));
				// post processing
				iRec1[1] = iRec1[0];
			}
		}
	};
			FAUSTFLOAT 	fslider0;
	int 	IOTA;
	double 	fVec0[65536];
	FAUSTFLOAT 	fslider1;
	int 	iConst0;
	double 	fConst1;
	double 	fRec0[2];
	static double 	ftbl0[65536];
	double 	fConst2;
	FAUSTFLOAT 	fslider2;
	void clear_state_f();
	void init(unsigned int samplingFreq);
	void compute(int count, float *input0, float *output0);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static void init_static(unsigned int samplingFreq, PluginDef*);
	static void compute_static(int count, float *input0, float *output0, PluginDef*);
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
	id = "chorus_mono";
	name = N_("Chorus Mono");
	groups = 0;
	description = ""; // description (tooltip)
	category = N_("Modulation");       // category
	shortname = "";     // shortname
	mono_audio = compute_static;
	stereo_audio = 0;
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
	fConst1 = (1.0 / iConst0);
	fConst2 = (0.01 * iConst0);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

inline void Dsp::compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = (0.01 * fslider0);
	double 	fSlow1 = (fSlow0 + (1 - fSlow0));
	double 	fSlow2 = (fConst1 * fslider1);
	double 	fSlow3 = fslider2;
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		double fTemp1 = (fSlow0 * fTemp0);
		fVec0[IOTA&65535] = fTemp1;
		double fTemp2 = (fSlow2 + fRec0[1]);
		fRec0[0] = (fTemp2 - floor(fTemp2));
		double fTemp3 = (65536 * (fRec0[0] - floor(fRec0[0])));
		double fTemp4 = floor(fTemp3);
		int iTemp5 = int(fTemp4);
		double fTemp6 = (fConst2 * (1 + (0.02 * ((ftbl0[((1 + iTemp5) & 65535)] * (fTemp3 - fTemp4)) + (ftbl0[(iTemp5 & 65535)] * ((1 + fTemp4) - fTemp3))))));
		int iTemp7 = int(fTemp6);
		int iTemp8 = (1 + iTemp7);
		output0[i] = (FAUSTFLOAT)((fSlow3 * (((fTemp6 - iTemp7) * fVec0[(IOTA-int((int(iTemp8) & 65535)))&65535]) + ((iTemp8 - fTemp6) * fVec0[(IOTA-int((iTemp7 & 65535)))&65535]))) + (fSlow1 * fTemp0));
		// post processing
		fRec0[1] = fRec0[0];
		IOTA = IOTA+1;
	}
}

void Dsp::compute_static(int count, float *input0, float *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("chorus_mono.level","","S","",&fslider2, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("chorus_mono.freq","","S","",&fslider1, 2.0, 0.0, 1e+01, 0.01);
	reg.registerVar("chorus_mono.wet_dry",N_("wet/dry"),"S",N_("percentage of processed signal in output signal"),&fslider0, 1e+02, 0.0, 1e+02, 1.0);
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
