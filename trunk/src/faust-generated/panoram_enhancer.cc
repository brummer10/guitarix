// generated from file '../src/faust/panoram_enhancer.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)


namespace panoram_enhancer {

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
	int 	IOTA;
	double 	fVec0[65536];
	double 	fVec1[65536];
	double 	fRec1[3];
	double 	fRec0[3];
	double 	fConst9;
	double 	fConst10;
	double 	fConst11;
	double 	fConst12;
	double 	fConst13;
	double 	fConst14;
	double 	fConst15;
	double 	fConst16;
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
	FAUSTFLOAT 	fslider0;
	double 	fRec8[2];
	double 	fConst28;
	double 	fRec7[3];
	double 	fConst29;
	double 	fRec6[3];
	double 	fRec5[3];
	double 	fRec4[3];
	double 	fRec3[3];
	double 	fRec2[3];
	FAUSTFLOAT 	fslider1;
	double 	fConst30;
	double 	fConst31;
	double 	fConst32;
	double 	fConst33;
	double 	fConst34;
	double 	fConst35;
	double 	fConst36;
	double 	fConst37;
	double 	fConst38;
	double 	fConst39;
	double 	fConst40;
	double 	fConst41;
	double 	fRec14[3];
	double 	fConst42;
	double 	fRec13[3];
	double 	fRec12[3];
	double 	fRec11[3];
	double 	fRec10[3];
	double 	fRec9[3];
	double 	fConst43;
	double 	fConst44;
	double 	fConst45;
	double 	fConst46;
	double 	fConst47;
	double 	fConst48;
	double 	fRec20[3];
	double 	fConst49;
	double 	fRec19[3];
	double 	fRec18[3];
	double 	fRec17[3];
	double 	fRec16[3];
	double 	fRec15[3];
	double 	fConst50;
	double 	fConst51;
	double 	fRec26[3];
	double 	fRec25[3];
	double 	fRec24[3];
	double 	fRec23[3];
	double 	fRec22[3];
	double 	fRec21[3];
	double 	fRec32[3];
	double 	fRec31[3];
	double 	fRec30[3];
	double 	fRec29[3];
	double 	fRec28[3];
	double 	fRec27[3];
	double 	fConst52;
	double 	fRec38[3];
	double 	fRec37[3];
	double 	fRec36[3];
	double 	fRec35[3];
	double 	fRec34[3];
	double 	fRec33[3];

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
	id = "panoram_enhancer";
	name = N_("Panoram Enhancer");
	groups = 0;
	description = ""; // description (tooltip)
	category = N_("Misc");       // category
	shortname = N_("Panoram");     // shortname
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
	for (int i=0; i<65536; i++) fVec0[i] = 0;
	for (int i=0; i<65536; i++) fVec1[i] = 0;
	for (int i=0; i<3; i++) fRec1[i] = 0;
	for (int i=0; i<3; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<3; i++) fRec7[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<3; i++) fRec4[i] = 0;
	for (int i=0; i<3; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<3; i++) fRec14[i] = 0;
	for (int i=0; i<3; i++) fRec13[i] = 0;
	for (int i=0; i<3; i++) fRec12[i] = 0;
	for (int i=0; i<3; i++) fRec11[i] = 0;
	for (int i=0; i<3; i++) fRec10[i] = 0;
	for (int i=0; i<3; i++) fRec9[i] = 0;
	for (int i=0; i<3; i++) fRec20[i] = 0;
	for (int i=0; i<3; i++) fRec19[i] = 0;
	for (int i=0; i<3; i++) fRec18[i] = 0;
	for (int i=0; i<3; i++) fRec17[i] = 0;
	for (int i=0; i<3; i++) fRec16[i] = 0;
	for (int i=0; i<3; i++) fRec15[i] = 0;
	for (int i=0; i<3; i++) fRec26[i] = 0;
	for (int i=0; i<3; i++) fRec25[i] = 0;
	for (int i=0; i<3; i++) fRec24[i] = 0;
	for (int i=0; i<3; i++) fRec23[i] = 0;
	for (int i=0; i<3; i++) fRec22[i] = 0;
	for (int i=0; i<3; i++) fRec21[i] = 0;
	for (int i=0; i<3; i++) fRec32[i] = 0;
	for (int i=0; i<3; i++) fRec31[i] = 0;
	for (int i=0; i<3; i++) fRec30[i] = 0;
	for (int i=0; i<3; i++) fRec29[i] = 0;
	for (int i=0; i<3; i++) fRec28[i] = 0;
	for (int i=0; i<3; i++) fRec27[i] = 0;
	for (int i=0; i<3; i++) fRec38[i] = 0;
	for (int i=0; i<3; i++) fRec37[i] = 0;
	for (int i=0; i<3; i++) fRec36[i] = 0;
	for (int i=0; i<3; i++) fRec35[i] = 0;
	for (int i=0; i<3; i++) fRec34[i] = 0;
	for (int i=0; i<3; i++) fRec33[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = min(1.92e+05, max(1.0, (double)fSamplingFreq));
	fConst1 = tan((5654.8667764616275 / fConst0));
	fConst2 = (1.0 / fConst1);
	fConst3 = (1 + ((fConst2 - 0.7653668647301795) / fConst1));
	fConst4 = (1.0 / faustpower<2>(fConst1));
	fConst5 = (2 * (1 - fConst4));
	fConst6 = (1.0 / (1 + ((0.7653668647301795 + fConst2) / fConst1)));
	fConst7 = (1 + ((fConst2 - 1.8477590650225735) / fConst1));
	fConst8 = (1.0 / (1 + ((fConst2 + 1.8477590650225735) / fConst1)));
	fConst9 = tan((62831.853071795864 / fConst0));
	fConst10 = (1.0 / fConst9);
	fConst11 = (1 + ((fConst10 - 0.5176380902050413) / fConst9));
	fConst12 = (2 * (1 - (1.0 / faustpower<2>(fConst9))));
	fConst13 = (1.0 / (1 + ((0.5176380902050413 + fConst10) / fConst9)));
	fConst14 = (1 + ((fConst10 - 1.414213562373095) / fConst9));
	fConst15 = (1.0 / (1 + ((1.414213562373095 + fConst10) / fConst9)));
	fConst16 = (1 + ((fConst10 - 1.9318516525781364) / fConst9));
	fConst17 = (1.0 / (1 + ((1.9318516525781364 + fConst10) / fConst9)));
	fConst18 = tan((20106.192982974677 / fConst0));
	fConst19 = (1.0 / fConst18);
	fConst20 = (1 + ((fConst19 - 0.5176380902050413) / fConst18));
	fConst21 = (1.0 / faustpower<2>(fConst18));
	fConst22 = (2 * (1 - fConst21));
	fConst23 = (1.0 / (1 + ((0.5176380902050413 + fConst19) / fConst18)));
	fConst24 = (1 + ((fConst19 - 1.414213562373095) / fConst18));
	fConst25 = (1.0 / (1 + ((1.414213562373095 + fConst19) / fConst18)));
	fConst26 = (1 + ((fConst19 - 1.9318516525781364) / fConst18));
	fConst27 = (1.0 / (1 + ((1.9318516525781364 + fConst19) / fConst18)));
	fConst28 = (0.13999999999999999 * fConst0);
	fConst29 = (2 * (0 - fConst21));
	fConst30 = tan((11309.733552923255 / fConst0));
	fConst31 = (1.0 / fConst30);
	fConst32 = (1 + ((fConst31 - 0.5176380902050413) / fConst30));
	fConst33 = (1.0 / faustpower<2>(fConst30));
	fConst34 = (2 * (1 - fConst33));
	fConst35 = (1.0 / (1 + ((0.5176380902050413 + fConst31) / fConst30)));
	fConst36 = (1 + ((fConst31 - 1.414213562373095) / fConst30));
	fConst37 = (1.0 / (1 + ((1.414213562373095 + fConst31) / fConst30)));
	fConst38 = (1 + ((fConst31 - 1.9318516525781364) / fConst30));
	fConst39 = (1.0 / (1 + ((1.9318516525781364 + fConst31) / fConst30)));
	fConst40 = (0.2 * fConst0);
	fConst41 = sqrt((0.3 + fConst40));
	fConst42 = (2 * (0 - fConst33));
	fConst43 = (1 + ((fConst2 - 0.5176380902050413) / fConst1));
	fConst44 = (1.0 / (1 + ((0.5176380902050413 + fConst2) / fConst1)));
	fConst45 = (1 + ((fConst2 - 1.414213562373095) / fConst1));
	fConst46 = (1.0 / (1 + ((1.414213562373095 + fConst2) / fConst1)));
	fConst47 = (1 + ((fConst2 - 1.9318516525781364) / fConst1));
	fConst48 = (1.0 / (1 + ((1.9318516525781364 + fConst2) / fConst1)));
	fConst49 = (2 * (0 - fConst4));
	fConst50 = (3.141592653589793 / fConst0);
	fConst51 = log10((9 + fConst40));
	fConst52 = cos((0.246 * fConst0));
	IOTA = 0;
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
	double 	fSlow0 = (0.0010000000000000009 * double(fslider0));
	double 	fSlow1 = double(fslider1);
	double 	fSlow2 = (0.6 + (0.4 * sin((3.14 * fSlow1))));
	double 	fSlow3 = (fConst13 * fSlow2);
	double 	fSlow4 = (0.6 + (0.27999999999999997 * fSlow1));
	double 	fSlow5 = (fConst23 * fSlow4);
	double 	fSlow6 = (fConst35 * (0.6 + (0.4 * cos((1.23 * fSlow1)))));
	double 	fSlow7 = (1500 * fSlow1);
	double 	fSlow8 = tan((fConst50 * (20000 - fSlow7)));
	double 	fSlow9 = (1.0 / fSlow8);
	double 	fSlow10 = (1 + ((fSlow9 - 0.5176380902050413) / fSlow8));
	double 	fSlow11 = (2 * (1 - (1.0 / faustpower<2>(fSlow8))));
	double 	fSlow12 = (1 + ((0.5176380902050413 + fSlow9) / fSlow8));
	double 	fSlow13 = (1.0 / fSlow12);
	double 	fSlow14 = (1 + ((fSlow9 - 1.414213562373095) / fSlow8));
	double 	fSlow15 = (1.0 / (1 + ((fSlow9 + 1.414213562373095) / fSlow8)));
	double 	fSlow16 = (1 + ((fSlow9 - 1.9318516525781364) / fSlow8));
	double 	fSlow17 = (1.0 / (1 + ((fSlow9 + 1.9318516525781364) / fSlow8)));
	double 	fSlow18 = tan((fConst50 * (6400 - fSlow7)));
	double 	fSlow19 = (1.0 / fSlow18);
	double 	fSlow20 = (1 + ((fSlow19 - 0.5176380902050413) / fSlow18));
	double 	fSlow21 = (1.0 / faustpower<2>(fSlow18));
	double 	fSlow22 = (2 * (1 - fSlow21));
	double 	fSlow23 = (1 + ((0.5176380902050413 + fSlow19) / fSlow18));
	double 	fSlow24 = (1.0 / fSlow23);
	double 	fSlow25 = (1 + ((fSlow19 - 1.414213562373095) / fSlow18));
	double 	fSlow26 = (1.0 / (1 + ((1.414213562373095 + fSlow19) / fSlow18)));
	double 	fSlow27 = (1 + ((fSlow19 - 1.9318516525781364) / fSlow18));
	double 	fSlow28 = (1.0 / (1 + ((1.9318516525781364 + fSlow19) / fSlow18)));
	double 	fSlow29 = (2 * (0 - fSlow21));
	double 	fSlow30 = (fSlow4 / fSlow12);
	double 	fSlow31 = tan((fConst50 * (3600 - fSlow7)));
	double 	fSlow32 = (1.0 / fSlow31);
	double 	fSlow33 = (1 + ((fSlow32 - 0.5176380902050413) / fSlow31));
	double 	fSlow34 = (1.0 / faustpower<2>(fSlow31));
	double 	fSlow35 = (2 * (1 - fSlow34));
	double 	fSlow36 = (1 + ((0.5176380902050413 + fSlow32) / fSlow31));
	double 	fSlow37 = (1.0 / fSlow36);
	double 	fSlow38 = (1 + ((fSlow32 - 1.414213562373095) / fSlow31));
	double 	fSlow39 = (1.0 / (1 + ((1.414213562373095 + fSlow32) / fSlow31)));
	double 	fSlow40 = (1 + ((fSlow32 - 1.9318516525781364) / fSlow31));
	double 	fSlow41 = (1.0 / (1 + ((1.9318516525781364 + fSlow32) / fSlow31)));
	double 	fSlow42 = (2 * (0 - fSlow34));
	double 	fSlow43 = (fSlow2 / fSlow23);
	double 	fSlow44 = tan((fConst50 * (1800 - fSlow7)));
	double 	fSlow45 = (1.0 / fSlow44);
	double 	fSlow46 = (1 + ((fSlow45 - 0.5176380902050413) / fSlow44));
	double 	fSlow47 = (1.0 / faustpower<2>(fSlow44));
	double 	fSlow48 = (2 * (1 - fSlow47));
	double 	fSlow49 = (1.0 / (1 + ((0.5176380902050413 + fSlow45) / fSlow44)));
	double 	fSlow50 = (1 + ((fSlow45 - 1.414213562373095) / fSlow44));
	double 	fSlow51 = (1.0 / (1 + ((1.414213562373095 + fSlow45) / fSlow44)));
	double 	fSlow52 = (1 + ((fSlow45 - 1.9318516525781364) / fSlow44));
	double 	fSlow53 = (1.0 / (1 + ((1.9318516525781364 + fSlow45) / fSlow44)));
	double 	fSlow54 = (2 * (0 - fSlow47));
	double 	fSlow55 = ((0.6 + (0.4 * sqrt((0.3 + fSlow1)))) / fSlow36);
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input1[i];
		fVec0[IOTA&65535] = fTemp0;
		double fTemp1 = (double)input0[i];
		fVec1[IOTA&65535] = fTemp1;
		fRec1[0] = ((0.5 * (fVec1[IOTA&65535] + fVec0[IOTA&65535])) - (fConst8 * ((fConst5 * fRec1[1]) + (fConst7 * fRec1[2]))));
		fRec0[0] = ((fConst8 * (fRec1[0] + (fRec1[2] + (2 * fRec1[1])))) - (fConst6 * ((fConst5 * fRec0[1]) + (fConst3 * fRec0[2]))));
		double fTemp2 = (fConst6 * (fRec0[0] + (fRec0[2] + (2 * fRec0[1]))));
		fRec8[0] = (fSlow0 + (0.999 * fRec8[1]));
		double fTemp3 = (fConst28 * fRec8[0]);
		int iTemp4 = int(fTemp3);
		double fTemp5 = floor(fTemp3);
		fRec7[0] = (((fVec1[(IOTA-int((iTemp4 & 65535)))&65535] * ((1 + fTemp5) - fTemp3)) + ((fTemp3 - fTemp5) * fVec1[(IOTA-int((int((1 + iTemp4)) & 65535)))&65535])) - (fConst27 * ((fConst26 * fRec7[2]) + (fConst22 * fRec7[1]))));
		fRec6[0] = ((fConst27 * ((fConst29 * fRec7[1]) + (fConst21 * (fRec7[2] + fRec7[0])))) - (fConst25 * ((fConst22 * fRec6[1]) + (fConst24 * fRec6[2]))));
		fRec5[0] = ((fConst25 * ((fConst29 * fRec6[1]) + (fConst21 * (fRec6[2] + fRec6[0])))) - (fConst23 * ((fConst22 * fRec5[1]) + (fConst20 * fRec5[2]))));
		fRec4[0] = ((fConst23 * ((fConst29 * fRec5[1]) + (fConst21 * (fRec5[2] + fRec5[0])))) - (fConst17 * ((fConst16 * fRec4[2]) + (fConst12 * fRec4[1]))));
		fRec3[0] = ((fConst17 * (fRec4[0] + (fRec4[2] + (2 * fRec4[1])))) - (fConst15 * ((fConst12 * fRec3[1]) + (fConst14 * fRec3[2]))));
		fRec2[0] = ((fConst15 * (fRec3[0] + (fRec3[2] + (2 * fRec3[1])))) - (fConst13 * ((fConst12 * fRec2[1]) + (fConst11 * fRec2[2]))));
		double fTemp6 = (fConst41 * fRec8[0]);
		int iTemp7 = int(fTemp6);
		double fTemp8 = floor(fTemp6);
		fRec14[0] = (((fVec1[(IOTA-int((iTemp7 & 65535)))&65535] * ((1 + fTemp8) - fTemp6)) + ((fTemp6 - fTemp8) * fVec1[(IOTA-int((int((1 + iTemp7)) & 65535)))&65535])) - (fConst39 * ((fConst38 * fRec14[2]) + (fConst34 * fRec14[1]))));
		fRec13[0] = ((fConst39 * ((fConst42 * fRec14[1]) + (fConst33 * (fRec14[2] + fRec14[0])))) - (fConst37 * ((fConst34 * fRec13[1]) + (fConst36 * fRec13[2]))));
		fRec12[0] = ((fConst37 * ((fConst42 * fRec13[1]) + (fConst33 * (fRec13[2] + fRec13[0])))) - (fConst35 * ((fConst34 * fRec12[1]) + (fConst32 * fRec12[2]))));
		fRec11[0] = ((fConst35 * ((fConst42 * fRec12[1]) + (fConst33 * (fRec12[2] + fRec12[0])))) - (fConst27 * ((fConst26 * fRec11[2]) + (fConst22 * fRec11[1]))));
		fRec10[0] = ((fConst27 * (fRec11[0] + (fRec11[2] + (2 * fRec11[1])))) - (fConst25 * ((fConst22 * fRec10[1]) + (fConst24 * fRec10[2]))));
		fRec9[0] = ((fConst25 * (fRec10[0] + (fRec10[2] + (2 * fRec10[1])))) - (fConst23 * ((fConst22 * fRec9[1]) + (fConst20 * fRec9[2]))));
		double fTemp9 = (fConst40 * fRec8[0]);
		int iTemp10 = int(fTemp9);
		int iTemp11 = int((int((1 + iTemp10)) & 65535));
		double fTemp12 = floor(fTemp9);
		double fTemp13 = (fTemp9 - fTemp12);
		double fTemp14 = ((1 + fTemp12) - fTemp9);
		int iTemp15 = int((iTemp10 & 65535));
		fRec20[0] = (((fVec1[(IOTA-iTemp15)&65535] * fTemp14) + (fTemp13 * fVec1[(IOTA-iTemp11)&65535])) - (fConst48 * ((fConst47 * fRec20[2]) + (fConst5 * fRec20[1]))));
		fRec19[0] = ((fConst48 * ((fConst49 * fRec20[1]) + (fConst4 * (fRec20[2] + fRec20[0])))) - (fConst46 * ((fConst5 * fRec19[1]) + (fConst45 * fRec19[2]))));
		fRec18[0] = ((fConst46 * ((fConst49 * fRec19[1]) + (fConst4 * (fRec19[2] + fRec19[0])))) - (fConst44 * ((fConst5 * fRec18[1]) + (fConst43 * fRec18[2]))));
		fRec17[0] = ((fConst44 * ((fConst49 * fRec18[1]) + (fConst4 * (fRec18[2] + fRec18[0])))) - (fConst39 * ((fConst38 * fRec17[2]) + (fConst34 * fRec17[1]))));
		fRec16[0] = ((fConst39 * (fRec17[0] + (fRec17[2] + (2 * fRec17[1])))) - (fConst37 * ((fConst34 * fRec16[1]) + (fConst36 * fRec16[2]))));
		fRec15[0] = ((fConst37 * (fRec16[0] + (fRec16[2] + (2 * fRec16[1])))) - (fConst35 * ((fConst34 * fRec15[1]) + (fConst32 * fRec15[2]))));
		output0[i] = (FAUSTFLOAT)((((fSlow6 * (fRec15[0] + (fRec15[2] + (2 * fRec15[1])))) + (fSlow5 * (fRec9[0] + (fRec9[2] + (2 * fRec9[1]))))) + (fSlow3 * (fRec2[0] + (fRec2[2] + (2 * fRec2[1]))))) + fTemp2);
		double fTemp16 = (fConst51 * fRec8[0]);
		int iTemp17 = int(fTemp16);
		double fTemp18 = floor(fTemp16);
		fRec26[0] = (((fVec0[(IOTA-int((iTemp17 & 65535)))&65535] * ((1 + fTemp18) - fTemp16)) + ((fTemp16 - fTemp18) * fVec0[(IOTA-int((int((1 + iTemp17)) & 65535)))&65535])) - (fSlow28 * ((fSlow27 * fRec26[2]) + (fSlow22 * fRec26[1]))));
		fRec25[0] = ((fSlow28 * ((fSlow29 * fRec26[1]) + (fSlow21 * (fRec26[2] + fRec26[0])))) - (fSlow26 * ((fSlow22 * fRec25[1]) + (fSlow25 * fRec25[2]))));
		fRec24[0] = ((fSlow26 * ((fSlow29 * fRec25[1]) + (fSlow21 * (fRec25[2] + fRec25[0])))) - (fSlow24 * ((fSlow22 * fRec24[1]) + (fSlow20 * fRec24[2]))));
		fRec23[0] = ((fSlow24 * ((fSlow29 * fRec24[1]) + (fSlow21 * (fRec24[2] + fRec24[0])))) - (fSlow17 * ((fSlow16 * fRec23[2]) + (fSlow11 * fRec23[1]))));
		fRec22[0] = ((fSlow17 * (fRec23[0] + (fRec23[2] + (2 * fRec23[1])))) - (fSlow15 * ((fSlow11 * fRec22[1]) + (fSlow14 * fRec22[2]))));
		fRec21[0] = ((fSlow15 * (fRec22[0] + (fRec22[2] + (2 * fRec22[1])))) - (fSlow13 * ((fSlow11 * fRec21[1]) + (fSlow10 * fRec21[2]))));
		fRec32[0] = (((fTemp14 * fVec0[(IOTA-iTemp15)&65535]) + (fTemp13 * fVec0[(IOTA-iTemp11)&65535])) - (fSlow41 * ((fSlow40 * fRec32[2]) + (fSlow35 * fRec32[1]))));
		fRec31[0] = ((fSlow41 * ((fSlow42 * fRec32[1]) + (fSlow34 * (fRec32[2] + fRec32[0])))) - (fSlow39 * ((fSlow35 * fRec31[1]) + (fSlow38 * fRec31[2]))));
		fRec30[0] = ((fSlow39 * ((fSlow42 * fRec31[1]) + (fSlow34 * (fRec31[2] + fRec31[0])))) - (fSlow37 * ((fSlow35 * fRec30[1]) + (fSlow33 * fRec30[2]))));
		fRec29[0] = ((fSlow37 * ((fSlow42 * fRec30[1]) + (fSlow34 * (fRec30[2] + fRec30[0])))) - (fSlow28 * ((fSlow27 * fRec29[2]) + (fSlow22 * fRec29[1]))));
		fRec28[0] = ((fSlow28 * (fRec29[0] + (fRec29[2] + (2 * fRec29[1])))) - (fSlow26 * ((fSlow22 * fRec28[1]) + (fSlow25 * fRec28[2]))));
		fRec27[0] = ((fSlow26 * (fRec28[0] + (fRec28[2] + (2 * fRec28[1])))) - (fSlow24 * ((fSlow22 * fRec27[1]) + (fSlow20 * fRec27[2]))));
		double fTemp19 = (fConst52 * fRec8[0]);
		int iTemp20 = int(fTemp19);
		double fTemp21 = floor(fTemp19);
		fRec38[0] = (((fVec0[(IOTA-int((iTemp20 & 65535)))&65535] * ((1 + fTemp21) - fTemp19)) + ((fTemp19 - fTemp21) * fVec0[(IOTA-int((int((1 + iTemp20)) & 65535)))&65535])) - (fSlow53 * ((fSlow52 * fRec38[2]) + (fSlow48 * fRec38[1]))));
		fRec37[0] = ((fSlow53 * ((fSlow54 * fRec38[1]) + (fSlow47 * (fRec38[2] + fRec38[0])))) - (fSlow51 * ((fSlow48 * fRec37[1]) + (fSlow50 * fRec37[2]))));
		fRec36[0] = ((fSlow51 * ((fSlow54 * fRec37[1]) + (fSlow47 * (fRec37[2] + fRec37[0])))) - (fSlow49 * ((fSlow48 * fRec36[1]) + (fSlow46 * fRec36[2]))));
		fRec35[0] = ((fSlow49 * ((fSlow54 * fRec36[1]) + (fSlow47 * (fRec36[2] + fRec36[0])))) - (fSlow41 * ((fSlow40 * fRec35[2]) + (fSlow35 * fRec35[1]))));
		fRec34[0] = ((fSlow41 * (fRec35[0] + (fRec35[2] + (2 * fRec35[1])))) - (fSlow39 * ((fSlow35 * fRec34[1]) + (fSlow38 * fRec34[2]))));
		fRec33[0] = ((fSlow39 * (fRec34[0] + (fRec34[2] + (2 * fRec34[1])))) - (fSlow37 * ((fSlow35 * fRec33[1]) + (fSlow33 * fRec33[2]))));
		output1[i] = (FAUSTFLOAT)((fSlow55 * (fRec33[0] + (fRec33[2] + (2 * fRec33[1])))) + ((fSlow43 * (fRec27[0] + (fRec27[2] + (2 * fRec27[1])))) + (fTemp2 + (fSlow30 * (fRec21[0] + (fRec21[2] + (2 * fRec21[1])))))));
		// post processing
		fRec33[2] = fRec33[1]; fRec33[1] = fRec33[0];
		fRec34[2] = fRec34[1]; fRec34[1] = fRec34[0];
		fRec35[2] = fRec35[1]; fRec35[1] = fRec35[0];
		fRec36[2] = fRec36[1]; fRec36[1] = fRec36[0];
		fRec37[2] = fRec37[1]; fRec37[1] = fRec37[0];
		fRec38[2] = fRec38[1]; fRec38[1] = fRec38[0];
		fRec27[2] = fRec27[1]; fRec27[1] = fRec27[0];
		fRec28[2] = fRec28[1]; fRec28[1] = fRec28[0];
		fRec29[2] = fRec29[1]; fRec29[1] = fRec29[0];
		fRec30[2] = fRec30[1]; fRec30[1] = fRec30[0];
		fRec31[2] = fRec31[1]; fRec31[1] = fRec31[0];
		fRec32[2] = fRec32[1]; fRec32[1] = fRec32[0];
		fRec21[2] = fRec21[1]; fRec21[1] = fRec21[0];
		fRec22[2] = fRec22[1]; fRec22[1] = fRec22[0];
		fRec23[2] = fRec23[1]; fRec23[1] = fRec23[0];
		fRec24[2] = fRec24[1]; fRec24[1] = fRec24[0];
		fRec25[2] = fRec25[1]; fRec25[1] = fRec25[0];
		fRec26[2] = fRec26[1]; fRec26[1] = fRec26[0];
		fRec15[2] = fRec15[1]; fRec15[1] = fRec15[0];
		fRec16[2] = fRec16[1]; fRec16[1] = fRec16[0];
		fRec17[2] = fRec17[1]; fRec17[1] = fRec17[0];
		fRec18[2] = fRec18[1]; fRec18[1] = fRec18[0];
		fRec19[2] = fRec19[1]; fRec19[1] = fRec19[0];
		fRec20[2] = fRec20[1]; fRec20[1] = fRec20[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
		fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
		fRec12[2] = fRec12[1]; fRec12[1] = fRec12[0];
		fRec13[2] = fRec13[1]; fRec13[1] = fRec13[0];
		fRec14[2] = fRec14[1]; fRec14[1] = fRec14[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
		fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		IOTA = IOTA+1;
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("panoram_enhancer.Delay width",N_("Delay"),"S",N_("Delay Width"),&fslider0, 0.0, 0.0, 1.0, 0.01);
	reg.registerVar("panoram_enhancer.Frequency width",N_("Frequency"),"S",N_("Frequency Width"),&fslider1, 0.0, 0.0, 1.0, 0.01);
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
                <property name=\"spacing\">10</property>\n\
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
                      <object class=\"GxMidKnob\" id=\"gxbigknob1\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">panoram_enhancer.Delay width</property>\n\
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
                    <property name=\"fill\">False</property>\n\
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
                        <property name=\"var_id\">panoram_enhancer.Frequency width</property>\n\
                        <property name=\"label_ref\">label2:rack_label</property>\n\
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
                    <property name=\"fill\">False</property>\n\
                    <property name=\"position\">1</property>\n\
                  </packing>\n\
                </child>\n\
              </object>\n\
              <packing>\n\
                <property name=\"expand\">True</property>\n\
                <property name=\"fill\">False</property>\n\
                <property name=\"pack_type\">end</property>\n\
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
                <property name=\"var_id\">panoram_enhancer.Delay width</property>\n\
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
                <property name=\"label\" translatable=\"yes\">Level</property>\n\
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
#define PARAM(p) ("panoram_enhancer" "." p)
// ----- panoram enhancer
b.openHorizontalhideBox("");
b.closeBox();
b.openVerticalBox("");
{
    b.openHorizontalTableBox("");
    {
	b.create_small_rackknob(PARAM("Delay width"), _("  delay width  "));
	b.create_small_rackknob(PARAM("Frequency width"), _("  freq width   "));
    }
    b.closeBox();
}
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

} // end namespace panoram_enhancer
