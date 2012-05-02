// generated from file '../src/faust/stereoverb.dsp' by dsp2cc:
// Code generated with Faust 0.9.43 (http://faust.grame.fr)


namespace stereoverb {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT 	fslider1;
	double 	fRec9[2];
	FAUSTFLOAT 	fslider2;
	int 	IOTA;
	double 	fVec0[2048];
	double 	fRec8[2];
	double 	fRec11[2];
	double 	fVec1[2048];
	double 	fRec10[2];
	double 	fRec13[2];
	double 	fVec2[2048];
	double 	fRec12[2];
	double 	fRec15[2];
	double 	fVec3[2048];
	double 	fRec14[2];
	double 	fRec17[2];
	double 	fVec4[2048];
	double 	fRec16[2];
	double 	fRec19[2];
	double 	fVec5[2048];
	double 	fRec18[2];
	double 	fRec21[2];
	double 	fVec6[2048];
	double 	fRec20[2];
	double 	fRec23[2];
	double 	fVec7[2048];
	double 	fRec22[2];
	double 	fVec8[1024];
	double 	fRec6[2];
	double 	fVec9[512];
	double 	fRec4[2];
	double 	fVec10[512];
	double 	fRec2[2];
	double 	fVec11[256];
	double 	fRec0[2];
	double 	fRec33[2];
	double 	fVec12[2048];
	double 	fRec32[2];
	double 	fRec35[2];
	double 	fVec13[2048];
	double 	fRec34[2];
	double 	fRec37[2];
	double 	fVec14[2048];
	double 	fRec36[2];
	double 	fRec39[2];
	double 	fVec15[2048];
	double 	fRec38[2];
	double 	fRec41[2];
	double 	fVec16[2048];
	double 	fRec40[2];
	double 	fRec43[2];
	double 	fVec17[2048];
	double 	fRec42[2];
	double 	fRec45[2];
	double 	fVec18[2048];
	double 	fRec44[2];
	double 	fRec47[2];
	double 	fVec19[2048];
	double 	fRec46[2];
	double 	fVec20[1024];
	double 	fRec30[2];
	double 	fVec21[512];
	double 	fRec28[2];
	double 	fVec22[512];
	double 	fRec26[2];
	double 	fVec23[256];
	double 	fRec24[2];
	void clear_state_f();
	void init(unsigned int samplingFreq);
	void compute(int count, float *input0, float *input1, float *output0, float *output1);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static void init_static(unsigned int samplingFreq, PluginDef*);
	static void compute_static(int count, float *input0, float *input1, float *output0, float *output1, PluginDef*);
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
	id = "stereoverb";
	name = N_("Stereo Verb");
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
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2048; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2048; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2048; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2048; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<2048; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<2048; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<2048; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<2048; i++) fVec7[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<1024; i++) fVec8[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<512; i++) fVec9[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<512; i++) fVec10[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<256; i++) fVec11[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec33[i] = 0;
	for (int i=0; i<2048; i++) fVec12[i] = 0;
	for (int i=0; i<2; i++) fRec32[i] = 0;
	for (int i=0; i<2; i++) fRec35[i] = 0;
	for (int i=0; i<2048; i++) fVec13[i] = 0;
	for (int i=0; i<2; i++) fRec34[i] = 0;
	for (int i=0; i<2; i++) fRec37[i] = 0;
	for (int i=0; i<2048; i++) fVec14[i] = 0;
	for (int i=0; i<2; i++) fRec36[i] = 0;
	for (int i=0; i<2; i++) fRec39[i] = 0;
	for (int i=0; i<2048; i++) fVec15[i] = 0;
	for (int i=0; i<2; i++) fRec38[i] = 0;
	for (int i=0; i<2; i++) fRec41[i] = 0;
	for (int i=0; i<2048; i++) fVec16[i] = 0;
	for (int i=0; i<2; i++) fRec40[i] = 0;
	for (int i=0; i<2; i++) fRec43[i] = 0;
	for (int i=0; i<2048; i++) fVec17[i] = 0;
	for (int i=0; i<2; i++) fRec42[i] = 0;
	for (int i=0; i<2; i++) fRec45[i] = 0;
	for (int i=0; i<2048; i++) fVec18[i] = 0;
	for (int i=0; i<2; i++) fRec44[i] = 0;
	for (int i=0; i<2; i++) fRec47[i] = 0;
	for (int i=0; i<2048; i++) fVec19[i] = 0;
	for (int i=0; i<2; i++) fRec46[i] = 0;
	for (int i=0; i<1024; i++) fVec20[i] = 0;
	for (int i=0; i<2; i++) fRec30[i] = 0;
	for (int i=0; i<512; i++) fVec21[i] = 0;
	for (int i=0; i<2; i++) fRec28[i] = 0;
	for (int i=0; i<512; i++) fVec22[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<256; i++) fVec23[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	IOTA = 0;
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

inline void Dsp::compute(int count, float *input0, float *input1, float *output0, float *output1)
{
	double 	fSlow0 = fslider0;
	double 	fSlow1 = (1 - (0.01 * fSlow0));
	double 	fSlow2 = (fSlow1 + (fSlow0 * (0.00015 + (0.01 * fSlow1))));
	double 	fSlow3 = fslider1;
	double 	fSlow4 = (1 - fSlow3);
	double 	fSlow5 = (0.7 + (0.28 * fslider2));
	double 	fSlow6 = (0.00015 * fSlow0);
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fRec9[0] = ((fSlow4 * fRec8[1]) + (fSlow3 * fRec9[1]));
		double fTemp1 = (fSlow6 * fTemp0);
		fVec0[IOTA&2047] = (fTemp1 + (fSlow5 * fRec9[0]));
		fRec8[0] = fVec0[(IOTA-1640)&2047];
		fRec11[0] = ((fSlow4 * fRec10[1]) + (fSlow3 * fRec11[1]));
		fVec1[IOTA&2047] = (fTemp1 + (fSlow5 * fRec11[0]));
		fRec10[0] = fVec1[(IOTA-1580)&2047];
		fRec13[0] = ((fSlow4 * fRec12[1]) + (fSlow3 * fRec13[1]));
		fVec2[IOTA&2047] = (fTemp1 + (fSlow5 * fRec13[0]));
		fRec12[0] = fVec2[(IOTA-1514)&2047];
		fRec15[0] = ((fSlow4 * fRec14[1]) + (fSlow3 * fRec15[1]));
		fVec3[IOTA&2047] = (fTemp1 + (fSlow5 * fRec15[0]));
		fRec14[0] = fVec3[(IOTA-1445)&2047];
		fRec17[0] = ((fSlow4 * fRec16[1]) + (fSlow3 * fRec17[1]));
		fVec4[IOTA&2047] = (fTemp1 + (fSlow5 * fRec17[0]));
		fRec16[0] = fVec4[(IOTA-1379)&2047];
		fRec19[0] = ((fSlow4 * fRec18[1]) + (fSlow3 * fRec19[1]));
		fVec5[IOTA&2047] = (fTemp1 + (fSlow5 * fRec19[0]));
		fRec18[0] = fVec5[(IOTA-1300)&2047];
		fRec21[0] = ((fSlow4 * fRec20[1]) + (fSlow3 * fRec21[1]));
		fVec6[IOTA&2047] = (fTemp1 + (fSlow5 * fRec21[0]));
		fRec20[0] = fVec6[(IOTA-1211)&2047];
		fRec23[0] = ((fSlow4 * fRec22[1]) + (fSlow3 * fRec23[1]));
		fVec7[IOTA&2047] = (fTemp1 + (fSlow5 * fRec23[0]));
		fRec22[0] = fVec7[(IOTA-1139)&2047];
		double fTemp2 = (((((((fRec22[0] + fRec20[0]) + fRec18[0]) + fRec16[0]) + fRec14[0]) + fRec12[0]) + fRec10[0]) + fRec8[0]);
		fVec8[IOTA&1023] = (fTemp2 + (0.5 * fRec6[1]));
		fRec6[0] = fVec8[(IOTA-579)&1023];
		double 	fRec7 = (0 - (fTemp2 - fRec6[1]));
		fVec9[IOTA&511] = (fRec7 + (0.5 * fRec4[1]));
		fRec4[0] = fVec9[(IOTA-464)&511];
		double 	fRec5 = (fRec4[1] - fRec7);
		fVec10[IOTA&511] = (fRec5 + (0.5 * fRec2[1]));
		fRec2[0] = fVec10[(IOTA-364)&511];
		double 	fRec3 = (fRec2[1] - fRec5);
		fVec11[IOTA&255] = (fRec3 + (0.5 * fRec0[1]));
		fRec0[0] = fVec11[(IOTA-248)&255];
		double 	fRec1 = (fRec0[1] - fRec3);
		output0[i] = (FAUSTFLOAT)(fRec1 + (fSlow2 * fTemp0));
		double fTemp3 = (double)input1[i];
		fRec33[0] = ((fSlow4 * fRec32[1]) + (fSlow3 * fRec33[1]));
		double fTemp4 = (fSlow6 * fTemp3);
		fVec12[IOTA&2047] = (fTemp4 + (fSlow5 * fRec33[0]));
		fRec32[0] = fVec12[(IOTA-1640)&2047];
		fRec35[0] = ((fSlow4 * fRec34[1]) + (fSlow3 * fRec35[1]));
		fVec13[IOTA&2047] = (fTemp4 + (fSlow5 * fRec35[0]));
		fRec34[0] = fVec13[(IOTA-1580)&2047];
		fRec37[0] = ((fSlow4 * fRec36[1]) + (fSlow3 * fRec37[1]));
		fVec14[IOTA&2047] = (fTemp4 + (fSlow5 * fRec37[0]));
		fRec36[0] = fVec14[(IOTA-1514)&2047];
		fRec39[0] = ((fSlow4 * fRec38[1]) + (fSlow3 * fRec39[1]));
		fVec15[IOTA&2047] = (fTemp4 + (fSlow5 * fRec39[0]));
		fRec38[0] = fVec15[(IOTA-1445)&2047];
		fRec41[0] = ((fSlow4 * fRec40[1]) + (fSlow3 * fRec41[1]));
		fVec16[IOTA&2047] = (fTemp4 + (fSlow5 * fRec41[0]));
		fRec40[0] = fVec16[(IOTA-1379)&2047];
		fRec43[0] = ((fSlow4 * fRec42[1]) + (fSlow3 * fRec43[1]));
		fVec17[IOTA&2047] = (fTemp4 + (fSlow5 * fRec43[0]));
		fRec42[0] = fVec17[(IOTA-1300)&2047];
		fRec45[0] = ((fSlow4 * fRec44[1]) + (fSlow3 * fRec45[1]));
		fVec18[IOTA&2047] = (fTemp4 + (fSlow5 * fRec45[0]));
		fRec44[0] = fVec18[(IOTA-1211)&2047];
		fRec47[0] = ((fSlow4 * fRec46[1]) + (fSlow3 * fRec47[1]));
		fVec19[IOTA&2047] = (fTemp4 + (fSlow5 * fRec47[0]));
		fRec46[0] = fVec19[(IOTA-1139)&2047];
		double fTemp5 = (((((((fRec46[0] + fRec44[0]) + fRec42[0]) + fRec40[0]) + fRec38[0]) + fRec36[0]) + fRec34[0]) + fRec32[0]);
		fVec20[IOTA&1023] = (fTemp5 + (0.5 * fRec30[1]));
		fRec30[0] = fVec20[(IOTA-579)&1023];
		double 	fRec31 = (0 - (fTemp5 - fRec30[1]));
		fVec21[IOTA&511] = (fRec31 + (0.5 * fRec28[1]));
		fRec28[0] = fVec21[(IOTA-464)&511];
		double 	fRec29 = (fRec28[1] - fRec31);
		fVec22[IOTA&511] = (fRec29 + (0.5 * fRec26[1]));
		fRec26[0] = fVec22[(IOTA-364)&511];
		double 	fRec27 = (fRec26[1] - fRec29);
		fVec23[IOTA&255] = (fRec27 + (0.5 * fRec24[1]));
		fRec24[0] = fVec23[(IOTA-248)&255];
		double 	fRec25 = (fRec24[1] - fRec27);
		output1[i] = (FAUSTFLOAT)(fRec25 + (fSlow2 * fTemp3));
		// post processing
		fRec24[1] = fRec24[0];
		fRec26[1] = fRec26[0];
		fRec28[1] = fRec28[0];
		fRec30[1] = fRec30[0];
		fRec46[1] = fRec46[0];
		fRec47[1] = fRec47[0];
		fRec44[1] = fRec44[0];
		fRec45[1] = fRec45[0];
		fRec42[1] = fRec42[0];
		fRec43[1] = fRec43[0];
		fRec40[1] = fRec40[0];
		fRec41[1] = fRec41[0];
		fRec38[1] = fRec38[0];
		fRec39[1] = fRec39[0];
		fRec36[1] = fRec36[0];
		fRec37[1] = fRec37[0];
		fRec34[1] = fRec34[0];
		fRec35[1] = fRec35[0];
		fRec32[1] = fRec32[0];
		fRec33[1] = fRec33[0];
		fRec0[1] = fRec0[0];
		fRec2[1] = fRec2[0];
		fRec4[1] = fRec4[0];
		fRec6[1] = fRec6[0];
		fRec22[1] = fRec22[0];
		fRec23[1] = fRec23[0];
		fRec20[1] = fRec20[0];
		fRec21[1] = fRec21[0];
		fRec18[1] = fRec18[0];
		fRec19[1] = fRec19[0];
		fRec16[1] = fRec16[0];
		fRec17[1] = fRec17[0];
		fRec14[1] = fRec14[0];
		fRec15[1] = fRec15[0];
		fRec12[1] = fRec12[0];
		fRec13[1] = fRec13[0];
		fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		fRec8[1] = fRec8[0];
		IOTA = IOTA+1;
		fRec9[1] = fRec9[0];
	}
}

void Dsp::compute_static(int count, float *input0, float *input1, float *output0, float *output1, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("stereoverb.RoomSize","","S","",&fslider2, 0.5, 0.0, 1.0, 0.025);
	reg.registerVar("stereoverb.damp","","S","",&fslider1, 0.5, 0.0, 1.0, 0.025);
	reg.registerVar("stereoverb.wet_dry",N_("wet/dry"),"S","",&fslider0, 5e+01, 0.0, 1e+02, 1.0);
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

} // end namespace stereoverb
