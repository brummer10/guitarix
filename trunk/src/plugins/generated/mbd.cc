// generated from file '../src/plugins/mbd.dsp' by dsp2cc:
// Code generated with Faust 0.9.58 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

namespace pluginlib {
namespace mbd {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	int 	iVec0[2];
	FAUSTFLOAT 	fslider0;
	double 	fConst0;
	FAUSTFLOAT 	fslider1;
	double 	fRec4[2];
	double 	fVec1[2];
	double 	fRec3[2];
	double 	fRec2[3];
	double 	fVec2[2];
	double 	fRec1[2];
	double 	fRec0[3];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT 	fslider3;
	double 	fRec6[2];
	double 	fRec5[3];
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT 	fslider6;
	double 	fRec10[2];
	double 	fRec9[3];
	double 	fVec3[2];
	double 	fRec8[2];
	double 	fRec7[3];
	FAUSTFLOAT 	fslider7;
	FAUSTFLOAT 	fslider8;
	FAUSTFLOAT 	fslider9;
	double 	fRec14[2];
	double 	fRec13[3];
	double 	fVec4[2];
	double 	fRec12[2];
	double 	fRec11[3];
	FAUSTFLOAT 	fslider10;
	FAUSTFLOAT 	fslider11;
	double 	fRec16[2];
	double 	fRec15[3];
	FAUSTFLOAT 	fslider12;
	FAUSTFLOAT 	fslider13;
	FAUSTFLOAT 	fslider14;
	double 	fRec17[2];
	void clear_state_f();
	int load_ui_f(const UiBuilder& b, int form);
	void init(unsigned int samplingFreq);
	void compute(int count, float *input0, float *output0);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static int load_ui_f_static(const UiBuilder& b, int form);
	static void init_static(unsigned int samplingFreq, PluginDef*);
	static void compute_static(int count, float *input0, float *output0, PluginDef*);
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
	id = "mbd";
	name = N_("MultiBand Distortion");
	groups = 0;
	description = N_("MultiBand Distortion"); // description (tooltip)
	category = N_("Distortion");       // category
	shortname = N_("MB Distortion");     // shortname
	mono_audio = compute_static;
	stereo_audio = 0;
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
	for (int i=0; i<2; i++) iVec0[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<3; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<3; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<3; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<3; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<3; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<3; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = (3.141592653589793 / double(min(192000, max(1, fSamplingFreq))));
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = tan((fConst0 * fslider0));
	double 	fSlow1 = (1.0 / faustpower<2>(fSlow0));
	double 	fSlow2 = (2 * (1 - fSlow1));
	double 	fSlow3 = (1.0 / fSlow0);
	double 	fSlow4 = (1 + ((fSlow3 - 1.0000000000000004) / fSlow0));
	double 	fSlow5 = (1 + ((1.0000000000000004 + fSlow3) / fSlow0));
	double 	fSlow6 = (1.0 / fSlow5);
	double 	fSlow7 = (1 + fSlow3);
	double 	fSlow8 = (0 - ((1 - fSlow3) / fSlow7));
	double 	fSlow9 = tan((fConst0 * fslider1));
	double 	fSlow10 = (1.0 / faustpower<2>(fSlow9));
	double 	fSlow11 = (2 * (1 - fSlow10));
	double 	fSlow12 = (1.0 / fSlow9);
	double 	fSlow13 = (1 + ((fSlow12 - 1.0000000000000004) / fSlow9));
	double 	fSlow14 = (1 + ((1.0000000000000004 + fSlow12) / fSlow9));
	double 	fSlow15 = (1.0 / fSlow14);
	double 	fSlow16 = (1 + fSlow12);
	double 	fSlow17 = (0 - ((1 - fSlow12) / fSlow16));
	double 	fSlow18 = (1.0 / fSlow16);
	double 	fSlow19 = (1.0 / (fSlow14 * fSlow0));
	double 	fSlow20 = (0 - fSlow3);
	double 	fSlow21 = (1.0 / fSlow7);
	double 	fSlow22 = (2 * (0 - fSlow1));
	double 	fSlow23 = (pow(1e+01,(2 * fslider2)) / fSlow5);
	double 	fSlow24 = fslider3;
	double 	fSlow25 = (0 - fSlow12);
	double 	fSlow26 = (2 * (0 - fSlow10));
	double 	fSlow27 = (pow(1e+01,(2 * fslider4)) / fSlow14);
	double 	fSlow28 = fslider5;
	double 	fSlow29 = tan((fConst0 * fslider6));
	double 	fSlow30 = (1.0 / faustpower<2>(fSlow29));
	double 	fSlow31 = (2 * (1 - fSlow30));
	double 	fSlow32 = (1.0 / fSlow29);
	double 	fSlow33 = (1 + ((fSlow32 - 1.0000000000000004) / fSlow29));
	double 	fSlow34 = (1 + ((1.0000000000000004 + fSlow32) / fSlow29));
	double 	fSlow35 = (1.0 / fSlow34);
	double 	fSlow36 = (1 + fSlow32);
	double 	fSlow37 = (0 - ((1 - fSlow32) / fSlow36));
	double 	fSlow38 = (1.0 / (fSlow5 * fSlow29));
	double 	fSlow39 = (0 - fSlow32);
	double 	fSlow40 = (1.0 / fSlow36);
	double 	fSlow41 = (2 * (0 - fSlow30));
	double 	fSlow42 = (pow(1e+01,(2 * fslider7)) / fSlow34);
	double 	fSlow43 = fslider8;
	double 	fSlow44 = tan((fConst0 * fslider9));
	double 	fSlow45 = (1.0 / faustpower<2>(fSlow44));
	double 	fSlow46 = (2 * (1 - fSlow45));
	double 	fSlow47 = (1.0 / fSlow44);
	double 	fSlow48 = (1 + ((fSlow47 - 1.0000000000000004) / fSlow44));
	double 	fSlow49 = (1 + ((1.0000000000000004 + fSlow47) / fSlow44));
	double 	fSlow50 = (1.0 / fSlow49);
	double 	fSlow51 = (1 + fSlow47);
	double 	fSlow52 = (0 - ((1 - fSlow47) / fSlow51));
	double 	fSlow53 = (1.0 / (fSlow34 * fSlow44));
	double 	fSlow54 = (0 - fSlow47);
	double 	fSlow55 = (1.0 / fSlow51);
	double 	fSlow56 = (2 * (0 - fSlow45));
	double 	fSlow57 = (pow(1e+01,(2 * fslider10)) / fSlow49);
	double 	fSlow58 = fslider11;
	double 	fSlow59 = (pow(1e+01,(2 * fslider12)) / fSlow49);
	double 	fSlow60 = fslider13;
	double 	fSlow61 = (0.0010000000000000009 * pow(10,(0.05 * fslider14)));
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		fRec4[0] = ((1e-20 * (1 - iVec0[1])) - fRec4[1]);
		double fTemp0 = ((double)input0[i] + fRec4[0]);
		fVec1[0] = fTemp0;
		double fTemp1 = (fVec1[0] + fVec1[1]);
		fRec3[0] = ((fSlow18 * fTemp1) + (fSlow17 * fRec3[1]));
		fRec2[0] = (fRec3[0] - (fSlow15 * ((fSlow13 * fRec2[2]) + (fSlow11 * fRec2[1]))));
		double fTemp2 = (fRec2[2] + (fRec2[0] + (2 * fRec2[1])));
		fVec2[0] = (fSlow15 * fTemp2);
		fRec1[0] = ((fSlow21 * ((fSlow20 * fVec2[1]) + (fSlow19 * fTemp2))) + (fSlow8 * fRec1[1]));
		fRec0[0] = (fRec1[0] - (fSlow6 * ((fSlow4 * fRec0[2]) + (fSlow2 * fRec0[1]))));
		double fTemp3 = max((double)-1, min((double)1, (fSlow24 + (fSlow23 * (((fSlow1 * fRec0[0]) + (fSlow22 * fRec0[1])) + (fSlow1 * fRec0[2]))))));
		fRec6[0] = ((fSlow18 * ((fSlow25 * fVec1[1]) + (fSlow12 * fVec1[0]))) + (fSlow17 * fRec6[1]));
		fRec5[0] = (fRec6[0] - (fSlow15 * ((fSlow13 * fRec5[2]) + (fSlow11 * fRec5[1]))));
		double fTemp4 = max((double)-1, min((double)1, (fSlow28 + (fSlow27 * (((fSlow10 * fRec5[0]) + (fSlow26 * fRec5[1])) + (fSlow10 * fRec5[2]))))));
		fRec10[0] = ((fSlow21 * fTemp1) + (fSlow8 * fRec10[1]));
		fRec9[0] = (fRec10[0] - (fSlow6 * ((fSlow4 * fRec9[2]) + (fSlow2 * fRec9[1]))));
		double fTemp5 = (fRec9[2] + (fRec9[0] + (2 * fRec9[1])));
		fVec3[0] = (fSlow6 * fTemp5);
		fRec8[0] = ((fSlow40 * ((fSlow39 * fVec3[1]) + (fSlow38 * fTemp5))) + (fSlow37 * fRec8[1]));
		fRec7[0] = (fRec8[0] - (fSlow35 * ((fSlow33 * fRec7[2]) + (fSlow31 * fRec7[1]))));
		double fTemp6 = max((double)-1, min((double)1, (fSlow43 + (fSlow42 * (((fSlow30 * fRec7[0]) + (fSlow41 * fRec7[1])) + (fSlow30 * fRec7[2]))))));
		fRec14[0] = ((fSlow40 * fTemp1) + (fSlow37 * fRec14[1]));
		fRec13[0] = (fRec14[0] - (fSlow35 * ((fSlow33 * fRec13[2]) + (fSlow31 * fRec13[1]))));
		double fTemp7 = (fRec13[2] + (fRec13[0] + (2 * fRec13[1])));
		fVec4[0] = (fSlow35 * fTemp7);
		fRec12[0] = ((fSlow55 * ((fSlow54 * fVec4[1]) + (fSlow53 * fTemp7))) + (fSlow52 * fRec12[1]));
		fRec11[0] = (fRec12[0] - (fSlow50 * ((fSlow48 * fRec11[2]) + (fSlow46 * fRec11[1]))));
		double fTemp8 = max((double)-1, min((double)1, (fSlow58 + (fSlow57 * (((fSlow45 * fRec11[0]) + (fSlow56 * fRec11[1])) + (fSlow45 * fRec11[2]))))));
		fRec16[0] = ((fSlow55 * fTemp1) + (fSlow52 * fRec16[1]));
		fRec15[0] = (fRec16[0] - (fSlow50 * ((fSlow48 * fRec15[2]) + (fSlow46 * fRec15[1]))));
		double fTemp9 = max((double)-1, min((double)1, (fSlow60 + (fSlow59 * (fRec15[2] + (fRec15[0] + (2 * fRec15[1])))))));
		fRec17[0] = (fSlow61 + (0.999 * fRec17[1]));
		output0[i] = (FAUSTFLOAT)(fRec17[0] * ((fTemp9 * (1 - (0.3333333333333333 * faustpower<2>(fTemp9)))) + ((fTemp8 * (1 - (0.3333333333333333 * faustpower<2>(fTemp8)))) + ((fTemp6 * (1 - (0.3333333333333333 * faustpower<2>(fTemp6)))) + ((fTemp4 * (1 - (0.3333333333333333 * faustpower<2>(fTemp4)))) + (fTemp3 * (1 - (0.3333333333333333 * faustpower<2>(fTemp3)))))))));
		// post processing
		fRec17[1] = fRec17[0];
		fRec15[2] = fRec15[1]; fRec15[1] = fRec15[0];
		fRec16[1] = fRec16[0];
		fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
		fRec12[1] = fRec12[0];
		fVec4[1] = fVec4[0];
		fRec13[2] = fRec13[1]; fRec13[1] = fRec13[0];
		fRec14[1] = fRec14[0];
		fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
		fVec3[1] = fVec3[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec10[1] = fRec10[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fVec2[1] = fVec2[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fVec1[1] = fVec1[0];
		fRec4[1] = fRec4[0];
		iVec0[1] = iVec0[0];
	}
}

void __rt_func Dsp::compute_static(int count, float *input0, float *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("mbd.Drive1","","S",N_("Amount of distortion"),&fslider12, 0.0, 0.0, 1.0, 0.01);
	reg.registerVar("mbd.Drive2","","S",N_("Amount of distortion"),&fslider10, 0.0, 0.0, 1.0, 0.01);
	reg.registerVar("mbd.Drive3","","S",N_("Amount of distortion"),&fslider7, 0.0, 0.0, 1.0, 0.01);
	reg.registerVar("mbd.Drive4","","S",N_("Amount of distortion"),&fslider2, 0.0, 0.0, 1.0, 0.01);
	reg.registerVar("mbd.Drive5","","S",N_("Amount of distortion"),&fslider4, 0.0, 0.0, 1.0, 0.01);
	reg.registerVar("mbd.Gain","","S","",&fslider14, 0.0, -4e+01, 4.0, 0.1);
	reg.registerVar("mbd.Offset1","","S",N_("Brings in even harmonics"),&fslider13, 0.0, 0.0, 0.5, 0.01);
	reg.registerVar("mbd.Offset2","","S",N_("Brings in even harmonics"),&fslider11, 0.0, 0.0, 0.5, 0.01);
	reg.registerVar("mbd.Offset3","","S",N_("Brings in even harmonics"),&fslider8, 0.0, 0.0, 0.5, 0.01);
	reg.registerVar("mbd.Offset4","","S",N_("Brings in even harmonics"),&fslider3, 0.0, 0.0, 0.5, 0.01);
	reg.registerVar("mbd.Offset5","","S",N_("Brings in even harmonics"),&fslider5, 0.0, 0.0, 0.5, 0.01);
	reg.registerVar("mbd.crossover_b1_b2",N_("Crossover B1-B2 (hz)"),"SL",N_("Crossover bandpass frequency"),&fslider9, 8e+01, 2e+01, 2e+04, 1.08);
	reg.registerVar("mbd.crossover_b2_b3",N_("Crossover B2-B3 (hz)"),"SL",N_("Crossover bandpass frequency"),&fslider6, 2.1e+02, 2e+01, 2e+04, 1.08);
	reg.registerVar("mbd.crossover_b3_b4",N_("Crossover B3-B4 (hz)"),"SL",N_("Crossover bandpass frequency"),&fslider0, 1.7e+03, 2e+01, 2e+04, 1.08);
	reg.registerVar("mbd.crossover_b4_b5",N_("Crossover B4-B5 (hz)"),"SL",N_("Crossover bandpass frequency"),&fslider1, 5e+03, 2e+01, 2e+04, 1.08);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("mbd" "." p)

b.openHorizontalhideBox("");
b.create_master_slider(PARAM("Gain"), N_("Gain"));
b.closeBox();

b.openHorizontalBox("");
b.openVerticalBox("");

b.openTabBox("");

b.openHorizontalBox(N_("Band 1"));
b.openVerticalBox("");
b.openHorizontalBox("");
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Drive1"), N_("Drive"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Offset1"), N_("Offset"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b1_b2"), N_("Low Shelf (Hz)"));
b.closeBox();
b.closeBox();
b.closeBox();

b.openHorizontalBox(N_("Band 2"));
b.openVerticalBox("");
b.openHorizontalBox("");
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Drive2"), N_("Drive"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Offset2"), N_("Offset"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b1_b2"), N_("Low (Hz)"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b2_b3"), N_("High (hz)"));
b.closeBox();
b.closeBox();
b.closeBox();

b.openHorizontalBox(N_("Band 3"));
b.openVerticalBox("");
b.openHorizontalBox("");
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Drive3"), N_("Drive"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Offset3"), N_("Offset"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b2_b3"), N_("Low (Hz)"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b3_b4"), N_("High (hz)"));
b.closeBox();
b.closeBox();
b.closeBox();

b.openHorizontalBox(N_("Band 4"));
b.openVerticalBox("");
b.openHorizontalBox("");
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Drive4"), N_("Drive"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Offset4"), N_("Offset"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b3_b4"), N_("Low (Hz)"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b4_b5"), N_("High (hz)"));
b.closeBox();
b.closeBox();
b.closeBox();

b.openHorizontalBox(N_("Band 5"));
b.openVerticalBox("");
b.openHorizontalBox("");
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Drive5"), N_("Drive"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Offset5"), N_("Offset"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b4_b5"), N_("High Shelf (Hz)"));
b.closeBox();
b.closeBox();
b.closeBox();

b.closeBox();
b.closeBox();
b.create_small_rackknob(PARAM("Gain"), N_("Gain"));
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

} // end namespace mbd
} // end namespace pluginlib
