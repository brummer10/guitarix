// generated from file '../src/faust/peak_eq.dsp' by dsp2cc:
// Code generated with Faust 0.9.46 (http://faust.grame.fr)


namespace peak_eq {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT 	fslider2;
	double 	fConst4;
	double 	fRec2_perm[4];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT 	fslider5;
	double 	fRec1_perm[4];
	FAUSTFLOAT 	fslider6;
	FAUSTFLOAT 	fslider7;
	FAUSTFLOAT 	fslider8;
	double 	fRec0_perm[4];
	void clear_state_f();
	void init(unsigned int samplingFreq);
	void compute(int fullcount, float *inputX0, float *outputX0);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static void init_static(unsigned int samplingFreq, PluginDef*);
	static void compute_static(int fullcount, float *inputX0, float *outputX0, PluginDef*);
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
	id = "eq";
	name = N_("Peak EQ");
	groups = 0;
	description = ""; // description (tooltip)
	category = N_("Tone control");       // category
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
	for (int i=0; i<4; i++) fRec2_perm[i]=0;
	for (int i=0; i<4; i++) fRec1_perm[i]=0;
	for (int i=0; i<4; i++) fRec0_perm[i]=0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (3.141592653589793 / iConst0);
	fConst2 = double((1.0 / iConst0));
	fConst3 = (6.283185307179586 * fConst2);
	fConst4 = (3.141592653589793 * fConst2);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int fullcount, float *inputX0, float *outputX0)
{
	double 	fZec0[128];
	double 	fRec2_tmp[128+4];
	double 	fZec1[128];
	double 	fRec1_tmp[128+4];
	double 	fZec2[128];
	double 	fRec0_tmp[128+4];
	double 	fSlow0 = fslider0;
	double 	fSlow1 = tan((fConst1 * fSlow0));
	double 	fSlow2 = (1.0 / fSlow1);
	double 	fSlow3 = sin((fConst3 * fSlow0));
	double 	fSlow4 = fslider1;
	double 	fSlow5 = fslider2;
	double 	fSlow6 = (fConst4 * ((fSlow5 * pow(10,(0.05 * fabs(fSlow4)))) / fSlow3));
	double 	fSlow7 = (fConst4 * (fSlow5 / fSlow3));
	int 	iSlow8 = int((fSlow4 > 0));
	double 	fSlow9 = ((iSlow8)?fSlow7:fSlow6);
	double 	fSlow10 = (1 + (fSlow2 * (fSlow9 + fSlow2)));
	double 	fSlow11 = (2 * (1 - (1.0 / faustpower<2>(fSlow1))));
	double 	fSlow12 = (1 + (fSlow2 * (fSlow2 - fSlow9)));
	double* 	fRec2 = &fRec2_tmp[4];
	double 	fSlow13 = fslider3;
	double 	fSlow14 = tan((fConst1 * fSlow13));
	double 	fSlow15 = (1.0 / fSlow14);
	double 	fSlow16 = sin((fConst3 * fSlow13));
	double 	fSlow17 = fslider4;
	double 	fSlow18 = fslider5;
	double 	fSlow19 = (fConst4 * ((fSlow18 * pow(10,(0.05 * fabs(fSlow17)))) / fSlow16));
	double 	fSlow20 = (fConst4 * (fSlow18 / fSlow16));
	int 	iSlow21 = int((fSlow17 > 0));
	double 	fSlow22 = ((iSlow21)?fSlow20:fSlow19);
	double 	fSlow23 = (1 + (fSlow15 * (fSlow22 + fSlow15)));
	double 	fSlow24 = (2 * (1 - (1.0 / faustpower<2>(fSlow14))));
	double 	fSlow25 = (1 + (fSlow15 * (fSlow15 - fSlow22)));
	double 	fSlow26 = ((iSlow8)?fSlow6:fSlow7);
	double 	fSlow27 = (1 + (fSlow2 * (fSlow26 + fSlow2)));
	double 	fSlow28 = (1 + (fSlow2 * (fSlow2 - fSlow26)));
	double* 	fRec1 = &fRec1_tmp[4];
	double 	fSlow29 = fslider6;
	double 	fSlow30 = tan((fConst1 * fSlow29));
	double 	fSlow31 = (1.0 / fSlow30);
	double 	fSlow32 = sin((fConst3 * fSlow29));
	double 	fSlow33 = fslider7;
	double 	fSlow34 = fslider8;
	double 	fSlow35 = (fConst4 * ((fSlow34 * pow(10,(0.05 * fabs(fSlow33)))) / fSlow32));
	double 	fSlow36 = (fConst4 * (fSlow34 / fSlow32));
	int 	iSlow37 = int((fSlow33 > 0));
	double 	fSlow38 = ((iSlow37)?fSlow36:fSlow35);
	double 	fSlow39 = (1 + (fSlow31 * (fSlow38 + fSlow31)));
	double 	fSlow40 = (2 * (1 - (1.0 / faustpower<2>(fSlow30))));
	double 	fSlow41 = (1 + (fSlow31 * (fSlow31 - fSlow38)));
	double 	fSlow42 = ((iSlow21)?fSlow19:fSlow20);
	double 	fSlow43 = (1 + (fSlow15 * (fSlow42 + fSlow15)));
	double 	fSlow44 = (1 + (fSlow15 * (fSlow15 - fSlow42)));
	double* 	fRec0 = &fRec0_tmp[4];
	double 	fSlow45 = ((iSlow37)?fSlow35:fSlow36);
	double 	fSlow46 = (1 + (fSlow31 * (fSlow45 + fSlow31)));
	double 	fSlow47 = (1 + (fSlow31 * (fSlow31 - fSlow45)));
	int index;
	for (index = 0; index <= fullcount - 128; index += 128) {
		// compute by blocks of 128 samples
		const int count = 128;
		FAUSTFLOAT* input0 = &inputX0[index];
		FAUSTFLOAT* output0 = &outputX0[index];
		// SECTION : 1
		// LOOP 0x9262b98
		// pre processing
		for (int i=0; i<4; i++) fRec2_tmp[i]=fRec2_perm[i];
		// exec code
		for (int i=0; i<count; i++) {
			fZec0[i] = (fSlow11 * fRec2[i-1]);
			fRec2[i] = ((double)input0[i] - (((fSlow12 * fRec2[i-2]) + fZec0[i]) / fSlow10));
		}
		// post processing
		for (int i=0; i<4; i++) fRec2_perm[i]=fRec2_tmp[count+i];
		
		// SECTION : 2
		// LOOP 0x9262968
		// pre processing
		for (int i=0; i<4; i++) fRec1_tmp[i]=fRec1_perm[i];
		// exec code
		for (int i=0; i<count; i++) {
			fZec1[i] = (fSlow24 * fRec1[i-1]);
			fRec1[i] = ((((fSlow28 * fRec2[i-2]) + (fZec0[i] + (fSlow27 * fRec2[i]))) / fSlow10) - (((fSlow25 * fRec1[i-2]) + fZec1[i]) / fSlow23));
		}
		// post processing
		for (int i=0; i<4; i++) fRec1_perm[i]=fRec1_tmp[count+i];
		
		// SECTION : 3
		// LOOP 0x92627b8
		// pre processing
		for (int i=0; i<4; i++) fRec0_tmp[i]=fRec0_perm[i];
		// exec code
		for (int i=0; i<count; i++) {
			fZec2[i] = (fSlow40 * fRec0[i-1]);
			fRec0[i] = ((((fSlow44 * fRec1[i-2]) + (fZec1[i] + (fSlow43 * fRec1[i]))) / fSlow23) - (((fSlow41 * fRec0[i-2]) + fZec2[i]) / fSlow39));
		}
		// post processing
		for (int i=0; i<4; i++) fRec0_perm[i]=fRec0_tmp[count+i];
		
		// SECTION : 4
		// LOOP 0x92626d8
		// exec code
		for (int i=0; i<count; i++) {
			output0[i] = (FAUSTFLOAT)(((fSlow47 * fRec0[i-2]) + (fZec2[i] + (fSlow46 * fRec0[i]))) / fSlow39);
		}
		
	}
	if (index < fullcount) {
		// compute the remaining samples if any
		int count = fullcount-index;
		FAUSTFLOAT* input0 = &inputX0[index];
		FAUSTFLOAT* output0 = &outputX0[index];
		// SECTION : 1
		// LOOP 0x9262b98
		// pre processing
		for (int i=0; i<4; i++) fRec2_tmp[i]=fRec2_perm[i];
		// exec code
		for (int i=0; i<count; i++) {
			fZec0[i] = (fSlow11 * fRec2[i-1]);
			fRec2[i] = ((double)input0[i] - (((fSlow12 * fRec2[i-2]) + fZec0[i]) / fSlow10));
		}
		// post processing
		for (int i=0; i<4; i++) fRec2_perm[i]=fRec2_tmp[count+i];
		
		// SECTION : 2
		// LOOP 0x9262968
		// pre processing
		for (int i=0; i<4; i++) fRec1_tmp[i]=fRec1_perm[i];
		// exec code
		for (int i=0; i<count; i++) {
			fZec1[i] = (fSlow24 * fRec1[i-1]);
			fRec1[i] = ((((fSlow28 * fRec2[i-2]) + (fZec0[i] + (fSlow27 * fRec2[i]))) / fSlow10) - (((fSlow25 * fRec1[i-2]) + fZec1[i]) / fSlow23));
		}
		// post processing
		for (int i=0; i<4; i++) fRec1_perm[i]=fRec1_tmp[count+i];
		
		// SECTION : 3
		// LOOP 0x92627b8
		// pre processing
		for (int i=0; i<4; i++) fRec0_tmp[i]=fRec0_perm[i];
		// exec code
		for (int i=0; i<count; i++) {
			fZec2[i] = (fSlow40 * fRec0[i-1]);
			fRec0[i] = ((((fSlow44 * fRec1[i-2]) + (fZec1[i] + (fSlow43 * fRec1[i]))) / fSlow23) - (((fSlow41 * fRec0[i-2]) + fZec2[i]) / fSlow39));
		}
		// post processing
		for (int i=0; i<4; i++) fRec0_perm[i]=fRec0_tmp[count+i];
		
		// SECTION : 4
		// LOOP 0x92626d8
		// exec code
		for (int i=0; i<count; i++) {
			output0[i] = (FAUSTFLOAT)(((fSlow47 * fRec0[i-2]) + (fZec2[i] + (fSlow46 * fRec0[i]))) / fSlow39);
		}
		
	}
}

void __rt_func Dsp::compute_static(int fullcount, float *inputX0, float *outputX0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(fullcount, inputX0, outputX0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("eq.level3","","S",N_("gain (dB)"),&fslider7, 0.0, -4e+01, 4e+01, 0.1);
	reg.registerVar("eq.peak3","","S",N_("frequency (hz)"),&fslider6, 1.76e+03, 1318.0, 2637.0, 1.0);
	reg.registerVar("eq.bandwidth2","","S",N_("frequency (hz)"),&fslider5, 2.2e+02, 5.0, 329.0, 1.0);
	reg.registerVar("eq.level2","","S",N_("gain (dB)"),&fslider4, 0.0, -4e+01, 4e+01, 0.1);
	reg.registerVar("eq.peak2","","S",N_("frequency (hz)"),&fslider3, 4.4e+02, 329.0, 1318.0, 1.0);
	reg.registerVar("eq.bandwidth1","","S",N_("frequency (hz)"),&fslider2, 41.0, 5.0, 41.0, 1.0);
	reg.registerVar("eq.level1","","S",N_("gain (dB)"),&fslider1, 0.0, -4e+01, 4e+01, 0.1);
	reg.registerVar("eq.peak1","","S",N_("frequency (hz)"),&fslider0, 1.1e+02, 41.0, 329.0, 1.0);
	reg.registerVar("eq.bandwidth3","","S",N_("frequency (hz)"),&fslider8, 8.8e+02, 5.0, 1318.0, 1.0);
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

} // end namespace peak_eq
