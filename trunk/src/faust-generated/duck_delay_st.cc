// generated from file '../src/faust/duck_delay_st.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)


namespace duck_delay_st {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	double 	fConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT 	fslider1;
	int 	IOTA;
	double 	fVec0[524288];
	double 	fConst9;
	FAUSTFLOAT 	fslider2;
	double 	fConst10;
	double 	fRec6[2];
	double 	fConst11;
	double 	fRec5[2];
	double 	fRec3[2];
	double 	fVec1[524288];
	double 	fRec7[2];
	double 	fRec4[2];
	double 	fConst12;
	double 	fConst13;
	double 	fConst14;
	double 	fConst15;
	double 	fRec2[2];
	double 	fRec1[3];
	double 	fConst16;
	double 	fRec0[3];
	FAUSTFLOAT 	fslider3;
	double 	fRec10[2];
	double 	fRec9[3];
	double 	fRec8[3];
	double 	fConst17;
	double 	fConst18;
	double 	fConst19;
	double 	fConst20;
	double 	fConst21;
	double 	fConst22;
	double 	fConst23;
	double 	fConst24;
	double 	fConst25;
	double 	fConst26;
	double 	fConst27;
	double 	fRec13[2];
	double 	fRec12[3];
	double 	fRec11[3];
	double 	fConst28;
	double 	fRec16[2];
	double 	fRec15[3];
	double 	fConst29;
	double 	fRec14[3];
	FAUSTFLOAT 	fslider4;
	double 	fRec17[2];
	FAUSTFLOAT 	fslider5;
	double 	fConst30;
	double 	fRec20[2];
	FAUSTFLOAT 	fslider6;
	double 	fRec19[2];
	FAUSTFLOAT 	fslider7;
	double 	fRec18[2];
	double 	fRec23[2];
	double 	fRec22[3];
	double 	fRec21[3];
	double 	fRec26[2];
	double 	fRec25[3];
	double 	fRec24[3];
	double 	fRec29[2];
	double 	fRec28[3];
	double 	fRec27[3];
	double 	fRec32[2];
	double 	fRec31[3];
	double 	fRec30[3];
	double 	fRec35[2];
	double 	fRec34[2];
	double 	fRec33[2];

	void clear_state_f();
	int load_ui_f(const UiBuilder& b, int form);
	static const char *glade_def;
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



Dsp::Dsp()
	: PluginDef() {
	version = PLUGINDEF_VERSION;
	flags = 0;
	id = "duckDelaySt";
	name = N_("Duck Delay St");
	groups = 0;
	description = ""; // description (tooltip)
	category = N_("Echo / Delay");       // category
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
	for (int i=0; i<524288; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<524288; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<3; i++) fRec1[i] = 0;
	for (int i=0; i<3; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<3; i++) fRec9[i] = 0;
	for (int i=0; i<3; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<3; i++) fRec12[i] = 0;
	for (int i=0; i<3; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<3; i++) fRec15[i] = 0;
	for (int i=0; i<3; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<3; i++) fRec22[i] = 0;
	for (int i=0; i<3; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<3; i++) fRec25[i] = 0;
	for (int i=0; i<3; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fRec29[i] = 0;
	for (int i=0; i<3; i++) fRec28[i] = 0;
	for (int i=0; i<3; i++) fRec27[i] = 0;
	for (int i=0; i<2; i++) fRec32[i] = 0;
	for (int i=0; i<3; i++) fRec31[i] = 0;
	for (int i=0; i<3; i++) fRec30[i] = 0;
	for (int i=0; i<2; i++) fRec35[i] = 0;
	for (int i=0; i<2; i++) fRec34[i] = 0;
	for (int i=0; i<2; i++) fRec33[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = min(1.92e+05, max(1.0, (double)fSamplingFreq));
	fConst1 = tan((2764.601535159018 / fConst0));
	fConst2 = (1.0 / fConst1);
	fConst3 = (1 + ((fConst2 - 0.6180339887498947) / fConst1));
	fConst4 = (1.0 / faustpower<2>(fConst1));
	fConst5 = (2 * (1 - fConst4));
	fConst6 = (1.0 / (1 + ((0.6180339887498947 + fConst2) / fConst1)));
	fConst7 = (1 + ((fConst2 - 1.6180339887498947) / fConst1));
	fConst8 = (1.0 / (1 + ((fConst2 + 1.6180339887498947) / fConst1)));
	fConst9 = exp((0 - (1e+01 / fConst0)));
	fConst10 = (1.0 - fConst9);
	fConst11 = (0.001 * fConst0);
	fConst12 = (0 - fConst2);
	fConst13 = (1 + fConst2);
	fConst14 = (1.0 / fConst13);
	fConst15 = (0 - ((1 - fConst2) / fConst13));
	fConst16 = (2 * (0 - fConst4));
	fConst17 = tan((1382.300767579509 / fConst0));
	fConst18 = (1.0 / fConst17);
	fConst19 = (1 + ((fConst18 - 0.6180339887498947) / fConst17));
	fConst20 = (1.0 / faustpower<2>(fConst17));
	fConst21 = (2 * (1 - fConst20));
	fConst22 = (1.0 / (1 + ((0.6180339887498947 + fConst18) / fConst17)));
	fConst23 = (1 + ((fConst18 - 1.6180339887498947) / fConst17));
	fConst24 = (1.0 / (1 + ((1.6180339887498947 + fConst18) / fConst17)));
	fConst25 = (1 + fConst18);
	fConst26 = (1.0 / fConst25);
	fConst27 = (0 - ((1 - fConst18) / fConst25));
	fConst28 = (0 - fConst18);
	fConst29 = (2 * (0 - fConst20));
	fConst30 = (1.0 / fConst0);
	IOTA = 0;
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
	double 	fSlow0 = double(fslider0);
	double 	fSlow1 = (1 - fSlow0);
	double 	fSlow2 = double(fslider1);
	double 	fSlow3 = (fConst10 * double(fslider2));
	double 	fSlow4 = (1 - (fSlow0 * fSlow2));
	double 	fSlow5 = double(fslider3);
	double 	fSlow6 = pow(10,(0.6 * fSlow5));
	double 	fSlow7 = pow(10,(0.6 * (1 - fSlow5)));
	double 	fSlow8 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider4))));
	double 	fSlow9 = exp((0 - (fConst30 / double(fslider5))));
	double 	fSlow10 = (1.0 - fSlow9);
	double 	fSlow11 = exp((0 - (fConst30 / double(fslider6))));
	double 	fSlow12 = (1.0 - fSlow11);
	double 	fSlow13 = pow(10,(0.05 * double(fslider7)));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		double fTemp1 = (fTemp0 + (fSlow2 * ((fSlow0 * fRec4[1]) + (fSlow1 * fRec5[1]))));
		fVec0[IOTA&524287] = fTemp1;
		fRec6[0] = (fSlow3 + (fConst9 * fRec6[1]));
		double fTemp2 = (fConst11 * fRec6[0]);
		int iTemp3 = int(fTemp2);
		int iTemp4 = int((int((1 + iTemp3)) & 393215));
		double fTemp5 = floor(fTemp2);
		double fTemp6 = (fTemp2 - fTemp5);
		int iTemp7 = int((iTemp3 & 393215));
		double fTemp8 = ((1 + fTemp5) - fTemp2);
		fRec5[0] = ((fTemp8 * fVec0[(IOTA-iTemp7)&524287]) + (fTemp6 * fVec0[(IOTA-iTemp4)&524287]));
		fRec3[0] = fRec5[0];
		double fTemp9 = (double)input1[i];
		double fTemp10 = ((fSlow4 * fTemp9) + (fSlow2 * ((fSlow0 * fRec3[1]) + (fSlow1 * fRec7[1]))));
		fVec1[IOTA&524287] = fTemp10;
		fRec7[0] = ((fTemp8 * fVec1[(IOTA-iTemp7)&524287]) + (fTemp6 * fVec1[(IOTA-iTemp4)&524287]));
		fRec4[0] = fRec7[0];
		fRec2[0] = ((fConst15 * fRec2[1]) + (fConst14 * ((fConst2 * fRec3[0]) + (fConst12 * fRec3[1]))));
		fRec1[0] = (fRec2[0] - (fConst8 * ((fConst7 * fRec1[2]) + (fConst5 * fRec1[1]))));
		fRec0[0] = ((fConst8 * ((fConst16 * fRec1[1]) + (fConst4 * (fRec1[2] + fRec1[0])))) - (fConst6 * ((fConst5 * fRec0[1]) + (fConst3 * fRec0[2]))));
		double fTemp11 = (fRec3[1] + fRec3[0]);
		fRec10[0] = ((fConst15 * fRec10[1]) + (fConst14 * fTemp11));
		fRec9[0] = (fRec10[0] - (fConst8 * ((fConst7 * fRec9[2]) + (fConst5 * fRec9[1]))));
		fRec8[0] = ((fConst8 * (fRec9[0] + (fRec9[2] + (2 * fRec9[1])))) - (fConst6 * ((fConst5 * fRec8[1]) + (fConst3 * fRec8[2]))));
		fRec13[0] = ((fConst27 * fRec13[1]) + (fConst26 * fTemp11));
		fRec12[0] = (fRec13[0] - (fConst24 * ((fConst23 * fRec12[2]) + (fConst21 * fRec12[1]))));
		fRec11[0] = ((fConst24 * (fRec12[0] + (fRec12[2] + (2 * fRec12[1])))) - (fConst22 * ((fConst21 * fRec11[1]) + (fConst19 * fRec11[2]))));
		fRec16[0] = ((fConst27 * fRec16[1]) + (fConst26 * ((fConst18 * fRec3[0]) + (fConst28 * fRec3[1]))));
		fRec15[0] = (fRec16[0] - (fConst24 * ((fConst23 * fRec15[2]) + (fConst21 * fRec15[1]))));
		fRec14[0] = ((fConst24 * ((fConst29 * fRec15[1]) + (fConst20 * (fRec15[2] + fRec15[0])))) - (fConst22 * ((fConst21 * fRec14[1]) + (fConst19 * fRec14[2]))));
		fRec17[0] = (fSlow8 + (0.999 * fRec17[1]));
		double fTemp12 = fabs(fTemp0);
		fRec20[0] = max(fTemp12, ((fSlow10 * fTemp12) + (fSlow9 * fRec20[1])));
		fRec19[0] = ((fSlow11 * fRec19[1]) + (fSlow12 * fRec20[0]));
		fRec18[0] = ((fConst9 * fRec18[1]) + (fConst10 * (1 - ((fSlow13 * fRec19[0]) > 1))));
		output0[i] = (FAUSTFLOAT)(fTemp0 + (0.1778279410038923 * ((fRec18[0] * fRec17[0]) * ((fConst22 * (((fConst29 * fRec14[1]) + (fConst20 * (fRec14[2] + fRec14[0]))) + (fSlow7 * (fRec11[0] + (fRec11[2] + (2 * fRec11[1])))))) + (fConst6 * ((fRec8[0] + (fRec8[2] + (2 * fRec8[1]))) + (fSlow6 * ((fConst16 * fRec0[1]) + (fConst4 * (fRec0[2] + fRec0[0]))))))))));
		fRec23[0] = ((fConst15 * fRec23[1]) + (fConst14 * ((fConst2 * fRec4[0]) + (fConst12 * fRec4[1]))));
		fRec22[0] = (fRec23[0] - (fConst8 * ((fConst7 * fRec22[2]) + (fConst5 * fRec22[1]))));
		fRec21[0] = ((fConst8 * ((fConst16 * fRec22[1]) + (fConst4 * (fRec22[2] + fRec22[0])))) - (fConst6 * ((fConst5 * fRec21[1]) + (fConst3 * fRec21[2]))));
		double fTemp13 = (fRec4[1] + fRec4[0]);
		fRec26[0] = ((fConst15 * fRec26[1]) + (fConst14 * fTemp13));
		fRec25[0] = (fRec26[0] - (fConst8 * ((fConst7 * fRec25[2]) + (fConst5 * fRec25[1]))));
		fRec24[0] = ((fConst8 * (fRec25[0] + (fRec25[2] + (2 * fRec25[1])))) - (fConst6 * ((fConst5 * fRec24[1]) + (fConst3 * fRec24[2]))));
		fRec29[0] = ((fConst27 * fRec29[1]) + (fConst26 * fTemp13));
		fRec28[0] = (fRec29[0] - (fConst24 * ((fConst23 * fRec28[2]) + (fConst21 * fRec28[1]))));
		fRec27[0] = ((fConst24 * (fRec28[0] + (fRec28[2] + (2 * fRec28[1])))) - (fConst22 * ((fConst21 * fRec27[1]) + (fConst19 * fRec27[2]))));
		fRec32[0] = ((fConst27 * fRec32[1]) + (fConst26 * ((fConst18 * fRec4[0]) + (fConst28 * fRec4[1]))));
		fRec31[0] = (fRec32[0] - (fConst24 * ((fConst23 * fRec31[2]) + (fConst21 * fRec31[1]))));
		fRec30[0] = ((fConst24 * ((fConst29 * fRec31[1]) + (fConst20 * (fRec31[2] + fRec31[0])))) - (fConst22 * ((fConst21 * fRec30[1]) + (fConst19 * fRec30[2]))));
		double fTemp14 = fabs(fTemp9);
		fRec35[0] = max(fTemp14, ((fSlow10 * fTemp14) + (fSlow9 * fRec35[1])));
		fRec34[0] = ((fSlow11 * fRec34[1]) + (fSlow12 * fRec35[0]));
		fRec33[0] = ((fConst9 * fRec33[1]) + (fConst10 * (1 - ((fSlow13 * fRec34[0]) > 1))));
		output1[i] = (FAUSTFLOAT)(fTemp9 + (0.1778279410038923 * ((fRec17[0] * fRec33[0]) * ((fConst22 * (((fConst29 * fRec30[1]) + (fConst20 * (fRec30[2] + fRec30[0]))) + (fSlow7 * (fRec27[0] + (fRec27[2] + (2 * fRec27[1])))))) + (fConst6 * ((fRec24[0] + (fRec24[2] + (2 * fRec24[1]))) + (fSlow6 * ((fConst16 * fRec21[1]) + (fConst4 * (fRec21[2] + fRec21[0]))))))))));
		// post processing
		fRec33[1] = fRec33[0];
		fRec34[1] = fRec34[0];
		fRec35[1] = fRec35[0];
		fRec30[2] = fRec30[1]; fRec30[1] = fRec30[0];
		fRec31[2] = fRec31[1]; fRec31[1] = fRec31[0];
		fRec32[1] = fRec32[0];
		fRec27[2] = fRec27[1]; fRec27[1] = fRec27[0];
		fRec28[2] = fRec28[1]; fRec28[1] = fRec28[0];
		fRec29[1] = fRec29[0];
		fRec24[2] = fRec24[1]; fRec24[1] = fRec24[0];
		fRec25[2] = fRec25[1]; fRec25[1] = fRec25[0];
		fRec26[1] = fRec26[0];
		fRec21[2] = fRec21[1]; fRec21[1] = fRec21[0];
		fRec22[2] = fRec22[1]; fRec22[1] = fRec22[0];
		fRec23[1] = fRec23[0];
		fRec18[1] = fRec18[0];
		fRec19[1] = fRec19[0];
		fRec20[1] = fRec20[0];
		fRec17[1] = fRec17[0];
		fRec14[2] = fRec14[1]; fRec14[1] = fRec14[0];
		fRec15[2] = fRec15[1]; fRec15[1] = fRec15[0];
		fRec16[1] = fRec16[0];
		fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
		fRec12[2] = fRec12[1]; fRec12[1] = fRec12[0];
		fRec13[1] = fRec13[0];
		fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec10[1] = fRec10[0];
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec4[1] = fRec4[0];
		fRec7[1] = fRec7[0];
		fRec3[1] = fRec3[0];
		fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		IOTA = IOTA+1;
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("duckDelaySt.amount",N_("Amount"),"S","",&fslider7, 0.5, 0.0, 56.0, 0.05);
	reg.registerVar("duckDelaySt.attack",N_("Attack"),"S","",&fslider6, 0.1, 0.05, 0.5, 0.05);
	reg.registerVar("duckDelaySt.coloration",N_("Coloration"),"S","",&fslider3, 0.0, -1.0, 1.0, 0.05);
	reg.registerVar("duckDelaySt.effect",N_("Effect"),"S","",&fslider4, 0.0, -16.0, 4.0, 0.1);
	reg.registerVar("duckDelaySt.feedback",N_("Feedback"),"S","",&fslider1, 0.0, 0.0, 1.0, 0.05);
	reg.registerVar("duckDelaySt.pingpong",N_("Ping Pong"),"S","",&fslider0, 0.0, 0.0, 1.0, 0.05);
	reg.registerVar("duckDelaySt.release",N_("Release"),"S","",&fslider5, 0.1, 0.05, 2.0, 0.05);
	reg.registerVar("duckDelaySt.time",N_("Delay"),"S","",&fslider2, 5e+02, 1.0, 2e+03, 1.0);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

const char *Dsp::glade_def = "\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<interface>\n\
  <!-- interface-requires gxwidgets 0.0 -->\n\
  <requires lib=\"gtk+\" version=\"2.20\"/>\n\
  <!-- interface-naming-policy project-wide -->\n\
  <object class=\"GtkWindow\" id=\"window1\">\n\
    <property name=\"can_focus\">False</property>\n\
    <child>\n\
      <object class=\"GtkVBox\" id=\"vbox1\">\n\
        <property name=\"visible\">True</property>\n\
        <property name=\"can_focus\">False</property>\n\
        <child>\n\
          <object class=\"GtkHBox\" id=\"rackbox\">\n\
            <property name=\"visible\">True</property>\n\
            <property name=\"can_focus\">False</property>\n\
            <property name=\"spacing\">4</property>\n\
            <child>\n\
              <object class=\"GtkHBox\" id=\"hbox1\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">False</property>\n\
                <child>\n\
                  <object class=\"GtkVBox\" id=\"vbox2\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label1:rack_label\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxBigKnob\" id=\"gxbigknob1\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">duckDelaySt.time</property>\n\
                        <property name=\"label_ref\">label1:rack_label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">False</property>\n\
                    <property name=\"fill\">True</property>\n\
                    <property name=\"position\">0</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkVBox\" id=\"vbox3\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label2:rack_label\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSmallKnobR\" id=\"gxbigknob2\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">duckDelaySt.feedback</property>\n\
                        <property name=\"label_ref\">label2:rack_label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSmallKnobR\" id=\"gxbigknob6\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">duckDelaySt.attack</property>\n\
                        <property name=\"label_ref\">label2:rack_label_inverse</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">2</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label2:rack_label_inverse\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">3</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">False</property>\n\
                    <property name=\"fill\">True</property>\n\
                    <property name=\"position\">1</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkVBox\" id=\"vbox4\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label3:rack_label\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSmallKnobR\" id=\"gxbigknob3\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">duckDelaySt.pingpong</property>\n\
                        <property name=\"label_ref\">label3:rack_label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSmallKnobR\" id=\"gxbigknob7\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">duckDelaySt.release</property>\n\
                        <property name=\"label_ref\">label3:rack_label_inverse</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">2</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label3:rack_label_inverse\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">3</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">False</property>\n\
                    <property name=\"fill\">True</property>\n\
                    <property name=\"position\">2</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkVBox\" id=\"vbox5\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label4:rack_label\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSmallKnobR\" id=\"gxbigknob4\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">duckDelaySt.coloration</property>\n\
                        <property name=\"label_ref\">label4:rack_label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSmallKnobR\" id=\"gxbigknob8\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">duckDelaySt.amount</property>\n\
                        <property name=\"label_ref\">label4:rack_label_inverse</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">2</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label4:rack_label_inverse\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">3</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">False</property>\n\
                    <property name=\"fill\">True</property>\n\
                    <property name=\"position\">3</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkVBox\" id=\"vbox6\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label5:rack_label\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxBigKnob\" id=\"gxbigknob5\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">duckDelaySt.effect</property>\n\
                        <property name=\"label_ref\">label5:rack_label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">False</property>\n\
                    <property name=\"fill\">True</property>\n\
                    <property name=\"position\">4</property>\n\
                  </packing>\n\
                </child>\n\
              </object>\n\
              <packing>\n\
                <property name=\"expand\">True</property>\n\
                <property name=\"fill\">False</property>\n\
                <property name=\"position\">0</property>\n\
              </packing>\n\
            </child>\n\
          </object>\n\
          <packing>\n\
            <property name=\"expand\">True</property>\n\
            <property name=\"fill\">False</property>\n\
            <property name=\"position\">0</property>\n\
          </packing>\n\
        </child>\n\
        <child>\n\
          <object class=\"GtkHBox\" id=\"minibox\">\n\
            <property name=\"visible\">True</property>\n\
            <property name=\"can_focus\">False</property>\n\
            <property name=\"spacing\">4</property>\n\
            <child>\n\
              <object class=\"GxHSlider\" id=\"gxhslider1\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">True</property>\n\
                <property name=\"receives_default\">True</property>\n\
                <property name=\"round_digits\">0</property>\n\
                <property name=\"var_id\">duckDelaySt.amount</property>\n\
                <property name=\"show_value\">False</property>\n\
                <property name=\"value_position\">right</property>\n\
                <property name=\"value_xalign\">0.52000000000000002</property>\n\
                <property name=\"label_ref\">label0:rack_label</property>\n\
              </object>\n\
              <packing>\n\
                <property name=\"expand\">False</property>\n\
                <property name=\"fill\">False</property>\n\
                <property name=\"position\">0</property>\n\
              </packing>\n\
            </child>\n\
            <child>\n\
              <object class=\"GtkLabel\" id=\"label0:rack_label\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">False</property>\n\
                <property name=\"xalign\">0</property>\n\
                <property name=\"label\" translatable=\"yes\">Amount</property>\n\
              </object>\n\
              <packing>\n\
                <property name=\"expand\">False</property>\n\
                <property name=\"fill\">False</property>\n\
                <property name=\"position\">1</property>\n\
              </packing>\n\
            </child>\n\
          </object>\n\
          <packing>\n\
            <property name=\"expand\">True</property>\n\
            <property name=\"fill\">True</property>\n\
            <property name=\"position\">1</property>\n\
          </packing>\n\
        </child>\n\
      </object>\n\
    </child>\n\
  </object>\n\
</interface>\n\
";

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_GLADE) {
        b.load_glade(glade_def);
        return 0;
    }
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("duckDelaySt" "." p)
// ducking delay stereo

b.openHorizontalhideBox("");
b.create_master_slider(PARAM("effect"), _("effect"));
b.closeBox();


b.openHorizontalBox("");
b.openVerticalBox("");
b.openHorizontalBox("");
{
	b.create_small_rackknob(PARAM("time"),         _(" time ms "));
	b.create_small_rackknob(PARAM("feedback"),     _(" feedback "));
	b.create_small_rackknob(PARAM("pingpong"),     _(" ping-pong"));
	b.create_small_rackknob(PARAM("coloration"),   _("coloration"));	
}
b.closeBox();
b.openHorizontalBox("");
{
	b.create_small_rackknob(PARAM("attack"),        _(" attack "));
	b.create_small_rackknob(PARAM("release"),       _(" release "));
	b.create_small_rackknob(PARAM("amount"),        _(" amount "));
	b.create_small_rackknobr(PARAM("effect"),       _(" effect "));
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

} // end namespace duck_delay_st
