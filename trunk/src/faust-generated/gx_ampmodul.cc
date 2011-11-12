// generated from file '../src/faust/gx_ampmodul.dsp' by dsp2cc:
// Code generated with Faust 0.9.43 (http://faust.grame.fr)

#include "valve.h"

namespace gx_ampmodul {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	double 	fRec0[6];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT 	fslider2;
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	FAUSTFLOAT 	fslider3;
	double 	fRec4[2];
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	FAUSTFLOAT 	fslider4;
	double 	fRec8[2];
	FAUSTFLOAT 	fslider5;
	double 	fRec12[2];
	double 	fConst7;
	double 	fConst8;
	double 	fConst9;
	double 	fConst10;
	double 	fRec13[2];
	double 	fRec11[3];
	double 	fConst11;
	double 	fConst12;
	double 	fRec10[2];
	double 	fConst13;
	double 	fRec9[2];
	double 	fConst14;
	double 	fConst15;
	double 	fConst16;
	double 	fConst17;
	double 	fRec14[2];
	double 	fRec7[3];
	double 	fRec6[2];
	double 	fRec5[2];
	double 	fConst18;
	double 	fConst19;
	double 	fConst20;
	double 	fConst21;
	double 	fRec15[2];
	double 	fRec3[3];
	double 	fRec2[2];
	double 	fRec1[6];
	double 	fRec16[6];
	double 	fRec26[2];
	double 	fRec25[3];
	double 	fRec24[2];
	double 	fRec23[2];
	double 	fRec27[2];
	double 	fRec22[3];
	double 	fRec21[2];
	double 	fRec20[2];
	double 	fRec28[2];
	double 	fRec19[3];
	double 	fRec18[2];
	double 	fRec17[6];
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



static const char* parm_groups[] = {
	"amp2.stage2", N_("Postamp Tube2"),
	"amp2.stage1", N_("Postamp Tube1"),
	0
	};

Dsp::Dsp()
	: PluginDef() {
	version = PLUGINDEF_VERSION;
	flags = 0;
	id = "ampmodul";
	name = N_("Postamp");
	groups = parm_groups;
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
	for (int i=0; i<6; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<3; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<3; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<3; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<6; i++) fRec1[i] = 0;
	for (int i=0; i<6; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<3; i++) fRec25[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<2; i++) fRec27[i] = 0;
	for (int i=0; i<3; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec28[i] = 0;
	for (int i=0; i<3; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<6; i++) fRec17[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (1.0 / tan((97.38937226128358 / iConst0)));
	fConst2 = (1 + fConst1);
	fConst3 = (0 - ((1 - fConst1) / fConst2));
	fConst4 = (1.0 / tan((20517.741620594938 / iConst0)));
	fConst5 = (1 + fConst4);
	fConst6 = (0 - ((1 - fConst4) / fConst5));
	fConst7 = (1.0 / tan((270.1769682087222 / iConst0)));
	fConst8 = (1 + fConst7);
	fConst9 = (0 - ((1 - fConst7) / fConst8));
	fConst10 = (0.027 / fConst8);
	fConst11 = (0 - fConst1);
	fConst12 = (0.025 / fConst2);
	fConst13 = (1.0 / fConst5);
	fConst14 = (1.0 / tan((414.6902302738527 / iConst0)));
	fConst15 = (1 + fConst14);
	fConst16 = (0 - ((1 - fConst14) / fConst15));
	fConst17 = (0.015 / fConst15);
	fConst18 = (1.0 / tan((609.4689747964198 / iConst0)));
	fConst19 = (1 + fConst18);
	fConst20 = (0 - ((1 - fConst18) / fConst19));
	fConst21 = (0.0082 / fConst19);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

inline void Dsp::compute(int count, float *input0, float *input1, float *output0, float *output1)
{
	double 	fSlow0 = fslider0;
	double 	fSlow1 = fslider1;
	double 	fSlow2 = (1 - max(0, fSlow1));
	double 	fSlow3 = fslider2;
	double 	fSlow4 = (0.0010000000000000009 * pow(10,(0.05 * fslider3)));
	double 	fSlow5 = (0.0010000000000000009 * pow(10,(0.05 * fslider4)));
	double 	fSlow6 = (0.0010000000000000009 * pow(10,(0.05 * fslider5)));
	double 	fSlow7 = (1 - max(0, (0 - fSlow1)));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fRec0[0] = (fTemp0 - (fSlow0 * fRec0[5]));
		fRec4[0] = (fSlow4 + (0.999 * fRec4[1]));
		fRec8[0] = (fSlow5 + (0.999 * fRec8[1]));
		fRec12[0] = (fSlow6 + (0.999 * fRec12[1]));
		fRec13[0] = ((fConst10 * (fRec11[1] + fRec11[2])) + (fConst9 * fRec13[1]));
		fRec11[0] = (Ftube(TUBE_TABLE_6V6_68k, ((fRec13[0] + (fTemp0 * fRec12[0])) - 2.29615)) - 164.9574074074074);
		fRec10[0] = ((fConst12 * ((fConst11 * fRec11[1]) + (fConst1 * fRec11[0]))) + (fConst3 * fRec10[1]));
		fRec9[0] = ((fConst13 * (fRec10[0] + fRec10[1])) + (fConst6 * fRec9[1]));
		fRec14[0] = ((fConst17 * (fRec7[1] + fRec7[2])) + (fConst16 * fRec14[1]));
		fRec7[0] = (Ftube(TUBE_TABLE_6V6_250k, ((fRec14[0] + (fRec9[0] * fRec8[0])) - 1.675587)) - 138.2942);
		fRec6[0] = ((fConst12 * ((fConst11 * fRec7[1]) + (fConst1 * fRec7[0]))) + (fConst3 * fRec6[1]));
		fRec5[0] = ((fConst13 * (fRec6[0] + fRec6[1])) + (fConst6 * fRec5[1]));
		fRec15[0] = ((fConst21 * (fRec3[1] + fRec3[2])) + (fConst20 * fRec15[1]));
		fRec3[0] = (Ftube(TUBE_TABLE_6V6_250k, ((fRec15[0] + (fRec5[0] * fRec4[0])) - 1.130462)) - 112.13878048780487);
		fRec2[0] = ((fConst12 * ((fConst11 * fRec3[1]) + (fConst1 * fRec3[0]))) + (fConst3 * fRec2[1]));
		fRec1[0] = (fRec2[0] - (fSlow3 * fRec1[5]));
		output0[i] = (FAUSTFLOAT)((fSlow7 * fRec1[0]) + (fSlow2 * fRec0[0]));
		double fTemp1 = (double)input1[i];
		fRec16[0] = (fTemp1 - (fSlow0 * fRec16[5]));
		fRec26[0] = ((fConst10 * (fRec25[1] + fRec25[2])) + (fConst9 * fRec26[1]));
		fRec25[0] = (Ftube(TUBE_TABLE_6V6_68k, ((fRec26[0] + (fTemp1 * fRec12[0])) - 2.29615)) - 164.9574074074074);
		fRec24[0] = ((fConst12 * ((fConst11 * fRec25[1]) + (fConst1 * fRec25[0]))) + (fConst3 * fRec24[1]));
		fRec23[0] = ((fConst13 * (fRec24[0] + fRec24[1])) + (fConst6 * fRec23[1]));
		fRec27[0] = ((fConst17 * (fRec22[1] + fRec22[2])) + (fConst16 * fRec27[1]));
		fRec22[0] = (Ftube(TUBE_TABLE_6V6_250k, ((fRec27[0] + (fRec8[0] * fRec23[0])) - 1.675587)) - 138.2942);
		fRec21[0] = ((fConst12 * ((fConst11 * fRec22[1]) + (fConst1 * fRec22[0]))) + (fConst3 * fRec21[1]));
		fRec20[0] = ((fConst13 * (fRec21[0] + fRec21[1])) + (fConst6 * fRec20[1]));
		fRec28[0] = ((fConst21 * (fRec19[1] + fRec19[2])) + (fConst20 * fRec28[1]));
		fRec19[0] = (Ftube(TUBE_TABLE_6V6_250k, ((fRec28[0] + (fRec4[0] * fRec20[0])) - 1.130462)) - 112.13878048780487);
		fRec18[0] = ((fConst12 * ((fConst11 * fRec19[1]) + (fConst1 * fRec19[0]))) + (fConst3 * fRec18[1]));
		fRec17[0] = (fRec18[0] - (fSlow3 * fRec17[5]));
		output1[i] = (FAUSTFLOAT)((fSlow7 * fRec17[0]) + (fSlow2 * fRec16[0]));
		// post processing
		for (int i=5; i>0; i--) fRec17[i] = fRec17[i-1];
		fRec18[1] = fRec18[0];
		fRec19[2] = fRec19[1]; fRec19[1] = fRec19[0];
		fRec28[1] = fRec28[0];
		fRec20[1] = fRec20[0];
		fRec21[1] = fRec21[0];
		fRec22[2] = fRec22[1]; fRec22[1] = fRec22[0];
		fRec27[1] = fRec27[0];
		fRec23[1] = fRec23[0];
		fRec24[1] = fRec24[0];
		fRec25[2] = fRec25[1]; fRec25[1] = fRec25[0];
		fRec26[1] = fRec26[0];
		for (int i=5; i>0; i--) fRec16[i] = fRec16[i-1];
		for (int i=5; i>0; i--) fRec1[i] = fRec1[i-1];
		fRec2[1] = fRec2[0];
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
		fRec15[1] = fRec15[0];
		fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
		fRec14[1] = fRec14[0];
		fRec9[1] = fRec9[0];
		fRec10[1] = fRec10[0];
		fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
		fRec13[1] = fRec13[0];
		fRec12[1] = fRec12[0];
		fRec8[1] = fRec8[0];
		fRec4[1] = fRec4[0];
		for (int i=5; i>0; i--) fRec0[i] = fRec0[i-1];
	}
}

void Dsp::compute_static(int count, float *input0, float *input1, float *output0, float *output1, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("ampmodul.level","","S","",&fslider5, -2e+01, -4e+01, 4.0, 0.1);
	reg.registerVar("ampmodul.amp2.stage1.tube1","","S","",&fslider4, 6.0, -2e+01, 2e+01, 0.1);
	reg.registerVar("ampmodul.amp2.stage2.tube2","","S","",&fslider3, 6.0, -2e+01, 2e+01, 0.1);
	reg.registerVar("ampmodul.feedback","","S","",&fslider2, 0.0, -1.0, 1.0, 0.01);
	reg.registerVar("ampmodul.wet_dry","","S","",&fslider1, 0.0, -1.0, 1.0, 0.1);
	reg.registerVar("ampmodul.feedbac","","S","",&fslider0, 0.0, -1.0, 1.0, 0.01);
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

} // end namespace gx_ampmodul
