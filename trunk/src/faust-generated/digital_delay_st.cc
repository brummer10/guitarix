// generated from file '../src/faust/digital_delay_st.dsp' by dsp2cc:
// Code generated with Faust 0.9.57 (http://faust.grame.fr)

#include "beat.h"

namespace digital_delay_st {

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
	FAUSTFLOAT 	fslider5;
	int 	iConst4;
	float 	fRec3[2];
	float 	fRec4[2];
	float 	fRec5[2];
	float 	fRec6[2];
	FAUSTFLOAT 	fslider6;
	float 	fRec0[2];
	float 	fRec9[3];
	float 	fRec8[3];
	float *fVec1;
	float 	fRec7[2];
	bool mem_allocated;
	void mem_alloc();
	void mem_free();
	void clear_state_f();
	int activate(bool start);
	void init(unsigned int samplingFreq);
	void compute(int count, float *input0, float *input1, float *output0, float *output1);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static int activate_static(bool start, PluginDef*);
	static void init_static(unsigned int samplingFreq, PluginDef*);
	static void compute_static(int count, float *input0, float *input1, float *output0, float *output1, PluginDef*);
	static int register_params_static(const ParamReg& reg);
	static void del_instance(PluginDef *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginDef(),
	  fVec0(0),
	  fVec1(0),
	  mem_allocated(false) {
	version = PLUGINDEF_VERSION;
	flags = 0;
	id = "didest";
	name = N_("Digital Stereo Delay");
	groups = 0;
	description = N_("Digital Delay Stereo Version"); // description (tooltip)
	category = N_("Echo / Delay");       // category
	shortname = N_("Digital Delay St");     // shortname
	mono_audio = 0;
	stereo_audio = compute_static;
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
	for (int i=0; i<524288; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<3; i++) fRec9[i] = 0;
	for (int i=0; i<3; i++) fRec8[i] = 0;
	for (int i=0; i<524288; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
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
	iConst4 = (60 * iConst0);
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void Dsp::mem_alloc()
{
	if (!fVec0) fVec0 = new float[524288];
	if (!fVec1) fVec1 = new float[524288];
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

void always_inline Dsp::compute(int count, float *input0, float *input1, float *output0, float *output1)
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
	float 	fSlow18 = min(524288.0f, B2N(fslider4, (float(iConst4) / fslider5)));
	float 	fSlow19 = fslider6;
	for (int i=0; i<count; i++) {
		float fTemp0 = (float)input0[i];
		fRec2[0] = ((fSlow15 * fRec0[1]) - (fSlow14 * ((fSlow13 * fRec2[2]) + (fSlow11 * fRec2[1]))));
		fRec1[0] = ((fSlow14 * (((fSlow10 * fRec2[0]) + (fSlow16 * fRec2[1])) + (fSlow10 * fRec2[2]))) - (fSlow8 * ((fSlow6 * fRec1[2]) + (fSlow4 * fRec1[1]))));
		float fTemp1 = (fRec1[2] + (fRec1[0] + (2 * fRec1[1])));
		float fTemp2 = ((fSlow1 * fTemp0) + (fSlow8 * fTemp1));
		fVec0[IOTA&524287] = fTemp2;
		float fTemp3 = ((int((fRec3[1] != 0.0f)))?((int(((fRec4[1] > 0.0f) & (fRec4[1] < 1.0f))))?fRec3[1]:0):((int(((fRec4[1] == 0.0f) & (fSlow18 != fRec5[1]))))?fConst2:((int(((fRec4[1] == 1.0f) & (fSlow18 != fRec6[1]))))?fConst3:0)));
		fRec3[0] = fTemp3;
		fRec4[0] = max(0.0f, min(1.0f, (fRec4[1] + fTemp3)));
		fRec5[0] = ((int(((fRec4[1] >= 1.0f) & (fRec6[1] != fSlow18))))?fSlow18:fRec5[1]);
		fRec6[0] = ((int(((fRec4[1] <= 0.0f) & (fRec5[1] != fSlow18))))?fSlow18:fRec6[1]);
		int iTemp4 = int((int(fRec5[0]) & 524287));
		float fTemp5 = (1.0f - fRec4[0]);
		int iTemp6 = int((int(fRec6[0]) & 524287));
		fRec0[0] = (0.01f * ((fSlow19 * ((fRec4[0] * fVec0[(IOTA-iTemp6)&524287]) + (fTemp5 * fVec0[(IOTA-iTemp4)&524287]))) + ((fSlow0 * fTemp0) + (fSlow17 * fTemp1))));
		output0[i] = (FAUSTFLOAT)(fRec0[0] + (fSlow2 * fTemp0));
		float fTemp7 = (float)input1[i];
		fRec9[0] = ((fSlow15 * fRec7[1]) - (fSlow14 * ((fSlow13 * fRec9[2]) + (fSlow11 * fRec9[1]))));
		fRec8[0] = ((fSlow14 * (((fSlow10 * fRec9[0]) + (fSlow16 * fRec9[1])) + (fSlow10 * fRec9[2]))) - (fSlow8 * ((fSlow6 * fRec8[2]) + (fSlow4 * fRec8[1]))));
		float fTemp8 = (fRec8[2] + (fRec8[0] + (2 * fRec8[1])));
		float fTemp9 = ((fSlow1 * fTemp7) + (fSlow8 * fTemp8));
		fVec1[IOTA&524287] = fTemp9;
		fRec7[0] = (0.01f * ((fSlow19 * ((fRec4[0] * fVec1[(IOTA-iTemp6)&524287]) + (fTemp5 * fVec1[(IOTA-iTemp4)&524287]))) + ((fSlow0 * fTemp7) + (fSlow17 * fTemp8))));
		output1[i] = (FAUSTFLOAT)(fRec7[0] + (fSlow2 * fTemp7));
		// post processing
		fRec7[1] = fRec7[0];
		fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
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

void __rt_func Dsp::compute_static(int count, float *input0, float *input1, float *output0, float *output1, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("didest.level","","S",N_("percentage of the delay gain level"),&fslider6, 5e+01f, 0.0f, 1e+02f, 1.0f);
	reg.registerVar("didest.bpm",N_("delay (bpm)"),"S",N_("Delay in Beats per Minute"),&fslider5, 1.2e+02f, 24.0f, 3.6e+02f, 1.0f);
	static const value_pair fslider4_values[] = {{"Dotted 1/2 note"},{"1/2 note"},{"1/2 note triplets"},{" Dotted 1/4 note"},{"1/4 note"},{"1/4 note triplets"},{"Dotted 1/8 note"},{"1/8 note"},{"1/8 note triplets"},{" Dotted 1/16 note"},{"1/16 note"},{"1/16 note triplets"},{"Dotted 1/32 note"},{"1/32 note"},{"1/32 note triplets"},{" Dotted 1/64 note"},{"1/64 note"},{"1/64 note triplets"},{0}};
	reg.registerEnumVar("didest.notes",N_("tact"),"S",N_("note setting for bpm"),fslider4_values,&fslider4, 5.0f, 1.0f, 18.0f, 1.0f);
	reg.registerVar("didest.feedback","","S",N_("percentage of the feedback level in the delay loop"),&fslider3, 5e+01f, 0.0f, 1e+02f, 1.0f);
	reg.registerVar("didest.highpass",N_("highpass (hz)"),"S",N_("highpass filter frequency in the feddback loop"),&fslider2, 1.2e+02f, 2e+01f, 2e+04f, 1.0f);
	reg.registerVar("didest.howpass",N_("lowpass (hz)"),"S",N_("lowpass filter frequency in the feddback loop"),&fslider1, 1.2e+04f, 2e+01f, 2e+04f, 1.0f);
	reg.registerVar("didest.gain","","S",N_("overall gain of the delay line in percent"),&fslider0, 1e+02f, 0.0f, 1.2e+02f, 1.0f);
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

} // end namespace digital_delay_st
