// generated from file '../src/LV2/faust/gxtape_st.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)


namespace gxtape_st {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	int 	iVec0[2];
	double 	fConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec1[2];
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	double 	fConst9;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec3[2];
	double 	fConst10;
	double 	fConst11;
	double 	fConst12;
	double 	fRec4[2];
	double 	fVec1[2];
	double 	fConst13;
	double 	fConst14;
	double 	fConst15;
	double 	fConst16;
	double 	fConst17;
	double 	fRec6[2];
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT	*fcheckbox0_;
	double 	fConst18;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec9[2];
	int 	iRec10[2];
	double 	fVec2[2];
	double 	fConst19;
	double 	fConst20;
	double 	fConst21;
	double 	fConst22;
	double 	fRec8[2];
	double 	fConst23;
	double 	fConst24;
	double 	fConst25;
	double 	fConst26;
	double 	fConst27;
	double 	fRec11[2];
	double 	fRec7[3];
	double 	fConst28;
	double 	fConst29;
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
	double 	fConst42;
	double 	fConst43;
	double 	fConst44;
	double 	fConst45;
	double 	fRec21[2];
	double 	fRec20[2];
	double 	fRec19[2];
	double 	fConst46;
	double 	fConst47;
	double 	fConst48;
	double 	fRec18[2];
	double 	fRec17[3];
	double 	fVec3[2];
	double 	fConst49;
	double 	fConst50;
	double 	fConst51;
	double 	fConst52;
	double 	fConst53;
	double 	fRec16[2];
	double 	fConst54;
	double 	fRec15[2];
	double 	fRec14[3];
	double 	fConst55;
	double 	fConst56;
	double 	fConst57;
	double 	fVec4[2];
	double 	fConst58;
	double 	fConst59;
	double 	fConst60;
	double 	fConst61;
	double 	fConst62;
	double 	fRec13[2];
	double 	fRec12[3];
	double 	fConst63;
	double 	fConst64;
	double 	fConst65;
	double 	fConst66;
	double 	fConst67;
	double 	fConst68;
	double 	fConst69;
	double 	fConst70;
	double 	fRec23[2];
	double 	fRec22[3];
	double 	fConst71;
	double 	fConst72;
	double 	fConst73;
	double 	fConst74;
	double 	fRec27[2];
	double 	fConst75;
	double 	fConst76;
	double 	fConst77;
	double 	fConst78;
	double 	fConst79;
	double 	fConst80;
	double 	fConst81;
	double 	fConst82;
	double 	fConst83;
	double 	fConst84;
	double 	fConst85;
	double 	fConst86;
	double 	fRec29[2];
	double 	fRec28[3];
	double 	fConst87;
	double 	fConst88;
	double 	fConst89;
	double 	fRec26[3];
	double 	fRec25[3];
	double 	fRec24[3];
	double 	fConst90;
	double 	fConst91;
	double 	fConst92;
	double 	fConst93;
	double 	fConst94;
	double 	fRec33[2];
	double 	fRec34[3];
	double 	fRec32[3];
	double 	fRec31[3];
	double 	fRec30[3];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	int 	IOTA;
	double 	fVec5[4096];
	double 	fConst95;
	double 	fConst96;
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT	*fslider4_;
	double 	fConst97;
	double 	fRec41[2];
	double 	fRec40[2];
	double 	fRec39[2];
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT	*fslider5_;
	double 	fConst98;
	double 	fRec35[2];
	double 	fRec36[2];
	double 	fRec37[2];
	double 	fRec38[2];
	double 	fVec6[4096];
	FAUSTFLOAT 	fslider6;
	FAUSTFLOAT	*fslider6_;
	double 	fRec48[2];
	double 	fRec47[2];
	double 	fRec46[2];
	FAUSTFLOAT 	fslider7;
	FAUSTFLOAT	*fslider7_;
	double 	fRec42[2];
	double 	fRec43[2];
	double 	fRec44[2];
	double 	fRec45[2];
	double 	fRec5[3];
	FAUSTFLOAT 	fcheckbox1;
	FAUSTFLOAT	*fcheckbox1_;
	double 	fRec2[2];
	double 	fConst99;
	double 	fRec0[3];
	double 	fRec51[2];
	double 	fVec7[2];
	double 	fRec53[2];
	double 	fRec63[2];
	double 	fRec62[2];
	double 	fRec61[2];
	double 	fRec60[2];
	double 	fRec59[3];
	double 	fVec8[2];
	double 	fRec58[2];
	double 	fRec57[2];
	double 	fRec56[3];
	double 	fVec9[2];
	double 	fRec55[2];
	double 	fRec54[3];
	double 	fRec65[2];
	double 	fRec64[3];
	double 	fRec69[2];
	double 	fRec71[2];
	double 	fRec70[3];
	double 	fRec68[3];
	double 	fRec67[3];
	double 	fRec66[3];
	double 	fRec75[2];
	double 	fRec76[3];
	double 	fRec74[3];
	double 	fRec73[3];
	double 	fRec72[3];
	double 	fVec10[4096];
	double 	fVec11[4096];
	double 	fRec52[3];
	double 	fRec50[2];
	double 	fRec49[3];

	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(uint32_t samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(uint32_t samplingFreq, PluginLV2*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginLV2() {
	version = PLUGINLV2_VERSION;
	id = "gxtape_st";
	name = "?gxtape_st";
	mono_audio = 0;
	stereo_audio = compute_static;
	set_samplerate = init_static;
	activate_plugin = 0;
	connect_ports = connect_static;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int i=0; i<2; i++) iVec0[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) iRec10[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<3; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<3; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<3; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<3; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<3; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fRec27[i] = 0;
	for (int i=0; i<2; i++) fRec29[i] = 0;
	for (int i=0; i<3; i++) fRec28[i] = 0;
	for (int i=0; i<3; i++) fRec26[i] = 0;
	for (int i=0; i<3; i++) fRec25[i] = 0;
	for (int i=0; i<3; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fRec33[i] = 0;
	for (int i=0; i<3; i++) fRec34[i] = 0;
	for (int i=0; i<3; i++) fRec32[i] = 0;
	for (int i=0; i<3; i++) fRec31[i] = 0;
	for (int i=0; i<3; i++) fRec30[i] = 0;
	for (int i=0; i<4096; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec41[i] = 0;
	for (int i=0; i<2; i++) fRec40[i] = 0;
	for (int i=0; i<2; i++) fRec39[i] = 0;
	for (int i=0; i<2; i++) fRec35[i] = 0;
	for (int i=0; i<2; i++) fRec36[i] = 0;
	for (int i=0; i<2; i++) fRec37[i] = 0;
	for (int i=0; i<2; i++) fRec38[i] = 0;
	for (int i=0; i<4096; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec48[i] = 0;
	for (int i=0; i<2; i++) fRec47[i] = 0;
	for (int i=0; i<2; i++) fRec46[i] = 0;
	for (int i=0; i<2; i++) fRec42[i] = 0;
	for (int i=0; i<2; i++) fRec43[i] = 0;
	for (int i=0; i<2; i++) fRec44[i] = 0;
	for (int i=0; i<2; i++) fRec45[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<3; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec51[i] = 0;
	for (int i=0; i<2; i++) fVec7[i] = 0;
	for (int i=0; i<2; i++) fRec53[i] = 0;
	for (int i=0; i<2; i++) fRec63[i] = 0;
	for (int i=0; i<2; i++) fRec62[i] = 0;
	for (int i=0; i<2; i++) fRec61[i] = 0;
	for (int i=0; i<2; i++) fRec60[i] = 0;
	for (int i=0; i<3; i++) fRec59[i] = 0;
	for (int i=0; i<2; i++) fVec8[i] = 0;
	for (int i=0; i<2; i++) fRec58[i] = 0;
	for (int i=0; i<2; i++) fRec57[i] = 0;
	for (int i=0; i<3; i++) fRec56[i] = 0;
	for (int i=0; i<2; i++) fVec9[i] = 0;
	for (int i=0; i<2; i++) fRec55[i] = 0;
	for (int i=0; i<3; i++) fRec54[i] = 0;
	for (int i=0; i<2; i++) fRec65[i] = 0;
	for (int i=0; i<3; i++) fRec64[i] = 0;
	for (int i=0; i<2; i++) fRec69[i] = 0;
	for (int i=0; i<2; i++) fRec71[i] = 0;
	for (int i=0; i<3; i++) fRec70[i] = 0;
	for (int i=0; i<3; i++) fRec68[i] = 0;
	for (int i=0; i<3; i++) fRec67[i] = 0;
	for (int i=0; i<3; i++) fRec66[i] = 0;
	for (int i=0; i<2; i++) fRec75[i] = 0;
	for (int i=0; i<3; i++) fRec76[i] = 0;
	for (int i=0; i<3; i++) fRec74[i] = 0;
	for (int i=0; i<3; i++) fRec73[i] = 0;
	for (int i=0; i<3; i++) fRec72[i] = 0;
	for (int i=0; i<4096; i++) fVec10[i] = 0;
	for (int i=0; i<4096; i++) fVec11[i] = 0;
	for (int i=0; i<3; i++) fRec52[i] = 0;
	for (int i=0; i<2; i++) fRec50[i] = 0;
	for (int i=0; i<3; i++) fRec49[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = min(1.92e+05, max(1.0, (double)fSamplingFreq));
	fConst1 = tan((62831.853071795864 / fConst0));
	fConst2 = (2 * (1 - (1.0 / faustpower<2>(fConst1))));
	fConst3 = (1.0 / fConst1);
	fConst4 = (1 + ((fConst3 - 1.414213562373095) / fConst1));
	fConst5 = (1.0 / (1 + ((1.414213562373095 + fConst3) / fConst1)));
	fConst6 = double(fConst0);
	fConst7 = (2.08237464507809e-05 * fConst6);
	fConst8 = (0.000460170362516827 + fConst7);
	fConst9 = ((0.000460170362516827 - fConst7) / fConst8);
	fConst10 = (2.08237299868718e-05 * fConst6);
	fConst11 = (0.000460960630154374 + fConst10);
	fConst12 = ((0.000460960630154374 - fConst10) / fConst11);
	fConst13 = (0.1 * (fConst6 / fConst11));
	fConst14 = (1.0 / tan((14137.16694115407 / fConst0)));
	fConst15 = (1 + fConst14);
	fConst16 = (0 - ((1 - fConst14) / fConst15));
	fConst17 = (1.0 / fConst15);
	fConst18 = (23561.94490192345 / fConst0);
	fConst19 = (1.0 / tan((785.3981633974482 / fConst0)));
	fConst20 = (1 + fConst19);
	fConst21 = (4.656612875245797e-10 / fConst20);
	fConst22 = (0 - ((1 - fConst19) / fConst20));
	fConst23 = (1.0 / tan((9424.77796076938 / fConst0)));
	fConst24 = (0 - fConst23);
	fConst25 = (1 + fConst23);
	fConst26 = (4.656612875245797e-10 / fConst25);
	fConst27 = (0 - ((1 - fConst23) / fConst25));
	fConst28 = tan((47123.8898038469 / fConst0));
	fConst29 = (1.0 / fConst28);
	fConst30 = (1 + ((fConst29 - 1.414213562373095) / fConst28));
	fConst31 = (2 * (1 - (1.0 / faustpower<2>(fConst28))));
	fConst32 = (1.0 / (1 + ((1.414213562373095 + fConst29) / fConst28)));
	fConst33 = tan((157.07963267948966 / fConst0));
	fConst34 = (2 * (1 - (1.0 / faustpower<2>(fConst33))));
	fConst35 = double((1.0 / fConst0));
	fConst36 = (fConst35 / sin((314.1592653589793 * fConst35)));
	fConst37 = (392.6990816987241 * fConst36);
	fConst38 = (1.0 / fConst33);
	fConst39 = (1 + ((fConst38 - fConst37) / fConst33));
	fConst40 = (1 + ((fConst37 + fConst38) / fConst33));
	fConst41 = (1.0 / fConst40);
	fConst42 = (1 + ((fConst29 - 1.0000000000000004) / fConst28));
	fConst43 = (1 + ((fConst29 + 1.0000000000000004) / fConst28));
	fConst44 = (1.0 / fConst43);
	fConst45 = (0.1 * (fConst6 / (fConst15 * fConst11)));
	fConst46 = (1 + fConst29);
	fConst47 = (1.0 / fConst46);
	fConst48 = (0 - ((1 - fConst29) / fConst46));
	fConst49 = (1.0 / tan((78.53981633974483 / fConst0)));
	fConst50 = (0 - fConst49);
	fConst51 = (1 + fConst49);
	fConst52 = (1.0 / (fConst51 * fConst43));
	fConst53 = (0 - ((1 - fConst49) / fConst51));
	fConst54 = (1.0 / fConst51);
	fConst55 = (554.7021966383262 * fConst36);
	fConst56 = (1 + ((fConst38 - fConst55) / fConst33));
	fConst57 = (1 + ((fConst55 + fConst38) / fConst33));
	fConst58 = tan((39269.90816987241 / fConst0));
	fConst59 = (1.0 / fConst58);
	fConst60 = (1 + fConst59);
	fConst61 = (1.0 / (fConst60 * fConst40));
	fConst62 = (0 - ((1 - fConst59) / fConst60));
	fConst63 = (2 * (1 - (1.0 / faustpower<2>(fConst58))));
	fConst64 = (1 + ((fConst59 - 1.414213562373095) / fConst58));
	fConst65 = (1.0 / (1 + ((1.414213562373095 + fConst59) / fConst58)));
	fConst66 = tan((31415.926535897932 / fConst0));
	fConst67 = (1.0 / fConst66);
	fConst68 = (1 + fConst67);
	fConst69 = (1.0 / fConst68);
	fConst70 = (0 - ((1 - fConst67) / fConst68));
	fConst71 = (1 + ((fConst29 - 0.7653668647301795) / fConst28));
	fConst72 = (1.0 / (1 + ((0.7653668647301795 + fConst29) / fConst28)));
	fConst73 = (1 + ((fConst29 - 1.8477590650225735) / fConst28));
	fConst74 = (1.0 / (1 + ((1.8477590650225735 + fConst29) / fConst28)));
	fConst75 = tan((235.61944901923448 / fConst0));
	fConst76 = (2 * (1 - (1.0 / faustpower<2>(fConst75))));
	fConst77 = (fConst35 / sin((471.23889803846896 * fConst35)));
	fConst78 = (589.0486225480862 * fConst77);
	fConst79 = (1.0 / fConst75);
	fConst80 = (1 + ((fConst79 - fConst78) / fConst75));
	fConst81 = (1.0 / (1 + ((fConst78 + fConst79) / fConst75)));
	fConst82 = (1.0 / tan((109.95574287564276 / fConst0)));
	fConst83 = (0 - fConst82);
	fConst84 = (1 + fConst82);
	fConst85 = (1.0 / fConst84);
	fConst86 = (0 - ((1 - fConst82) / fConst84));
	fConst87 = (1175.3065182545242 * fConst77);
	fConst88 = (1 + ((fConst79 - fConst87) / fConst75));
	fConst89 = (1 + ((fConst87 + fConst79) / fConst75));
	fConst90 = (1 + ((fConst67 - 0.7653668647301795) / fConst66));
	fConst91 = (2 * (1 - (1.0 / faustpower<2>(fConst66))));
	fConst92 = (1.0 / (1 + ((0.7653668647301795 + fConst67) / fConst66)));
	fConst93 = (1 + ((fConst67 - 1.8477590650225735) / fConst66));
	fConst94 = (1.0 / (1 + ((fConst67 + 1.8477590650225735) / fConst66)));
	fConst95 = (1e+01 / fConst0);
	fConst96 = (0 - fConst95);
	fConst97 = (6.283185307179586 / fConst0);
	fConst98 = (0.005 * fConst0);
	fConst99 = (fConst6 / fConst8);
	IOTA = 0;
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
#define fcheckbox0 (*fcheckbox0_)
#define fslider2 (*fslider2_)
#define fslider3 (*fslider3_)
#define fslider4 (*fslider4_)
#define fslider5 (*fslider5_)
#define fslider6 (*fslider6_)
#define fslider7 (*fslider7_)
#define fcheckbox1 (*fcheckbox1_)
	double 	fSlow0 = (0.004073836948085289 * (exp((1 - double(fslider0))) - 1));
	double 	fSlow1 = (0.004073836948085289 * (exp(double(fslider1)) - 1));
	double 	fSlow2 = double(fcheckbox0);
	double 	fSlow3 = tan((fConst18 * (2.0 - fSlow2)));
	double 	fSlow4 = (2 * (1 - (1.0 / faustpower<2>(fSlow3))));
	double 	fSlow5 = (1.0 / fSlow3);
	double 	fSlow6 = (1 + ((fSlow5 - 1.414213562373095) / fSlow3));
	double 	fSlow7 = (1.0 / (1 + ((1.414213562373095 + fSlow5) / fSlow3)));
	double 	fSlow8 = (3.159999999999652e-06 * double(fslider2));
	int 	iSlow9 = int(fSlow2);
	int 	iSlow10 = int(double(fslider3));
	double 	fSlow11 = (fConst97 * double(fslider4));
	double 	fSlow12 = (fConst98 * double(fslider5));
	double 	fSlow13 = (fConst97 * double(fslider6));
	double 	fSlow14 = (fConst98 * double(fslider7));
	int 	iSlow15 = int(double(fcheckbox1));
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		fRec1[0] = (fSlow0 + (0.993 * fRec1[1]));
		double fTemp0 = (0.000257077328090757 * fRec1[0]);
		double fTemp1 = (0.000257077328090757 - fTemp0);
		fRec3[0] = (fSlow1 + (0.993 * fRec3[1]));
		fRec4[0] = ((double)input0[i] - (fConst12 * fRec4[1]));
		double fTemp2 = (0 - (0.000275923691873229 * fRec3[0]));
		double fTemp3 = ((fRec4[0] * fTemp2) + (0.000275923691873229 * (fRec4[1] * fRec3[0])));
		fVec1[0] = fTemp3;
		fRec6[0] = ((fConst17 * (fRec5[1] + fRec5[2])) + (fConst16 * fRec6[1]));
		fRec9[0] = (fSlow8 + (0.9999 * fRec9[1]));
		iRec10[0] = (12345 + (1103515245 * iRec10[1]));
		double fTemp4 = (iRec10[0] * fRec9[0]);
		fVec2[0] = fTemp4;
		fRec8[0] = ((fConst22 * fRec8[1]) + (fConst21 * (fVec2[0] + fVec2[1])));
		fRec11[0] = ((fConst27 * fRec11[1]) + (fConst26 * ((fConst23 * fVec2[0]) + (fConst24 * fVec2[1]))));
		fRec7[0] = (((0.2 * fRec11[0]) + fRec8[0]) - (fSlow7 * ((fSlow6 * fRec7[2]) + (fSlow4 * fRec7[1]))));
		double fTemp5 = (fSlow7 * (fRec7[0] + (fRec7[2] + (2 * fRec7[1]))));
		double fTemp6 = (fConst34 * fRec14[1]);
		fRec21[0] = ((fConst16 * fRec21[1]) + (fConst45 * (fVec1[0] + fVec1[1])));
		fRec20[0] = (fRec21[0] - (0.3 * fRec20[1]));
		fRec19[0] = (((0.3 * fRec19[1]) + (2.0 / (1.0 + exp((0 - (5.0 * fRec20[0])))))) - 1.0);
		fRec18[0] = ((fConst48 * fRec18[1]) + (fConst47 * (fRec19[1] + fRec19[0])));
		fRec17[0] = (fRec18[0] - (fConst44 * ((fConst42 * fRec17[2]) + (fConst31 * fRec17[1]))));
		double fTemp7 = (fRec17[0] + (fRec17[2] + (2 * fRec17[1])));
		fVec3[0] = fTemp7;
		fRec16[0] = ((fConst53 * fRec16[1]) + (fConst52 * ((fConst49 * fVec3[0]) + (fConst50 * fVec3[1]))));
		fRec15[0] = ((fConst53 * fRec15[1]) + (fConst54 * ((fConst49 * fRec16[0]) + (fConst50 * fRec16[1]))));
		fRec14[0] = (fRec15[0] - (fConst41 * ((fConst39 * fRec14[2]) + fTemp6)));
		double fTemp8 = (fTemp6 + ((fConst57 * fRec14[0]) + (fConst56 * fRec14[2])));
		fVec4[0] = fTemp8;
		fRec13[0] = ((fConst62 * fRec13[1]) + (fConst61 * (fVec4[0] + fVec4[1])));
		fRec12[0] = (fRec13[0] - (fConst32 * ((fConst31 * fRec12[1]) + (fConst30 * fRec12[2]))));
		fRec23[0] = ((fConst70 * fRec23[1]) + (fConst69 * (fRec15[1] + fRec15[0])));
		fRec22[0] = (fRec23[0] - (fConst65 * ((fConst64 * fRec22[2]) + (fConst63 * fRec22[1]))));
		fRec27[0] = ((fConst17 * (fRec26[1] + fRec26[2])) + (fConst16 * fRec27[1]));
		double fTemp9 = (fConst76 * fRec28[1]);
		fRec29[0] = ((fConst86 * fRec29[1]) + (fConst85 * ((fConst82 * fRec16[0]) + (fConst83 * fRec16[1]))));
		fRec28[0] = (fRec29[0] - (fConst81 * ((fConst80 * fRec28[2]) + fTemp9)));
		fRec26[0] = ((fConst81 * (fTemp9 + ((fConst89 * fRec28[0]) + (fConst88 * fRec28[2])))) - fRec27[0]);
		fRec25[0] = (fRec26[0] - (fConst74 * ((fConst31 * fRec25[1]) + (fConst73 * fRec25[2]))));
		fRec24[0] = ((fConst74 * (fRec25[0] + (fRec25[2] + (2 * fRec25[1])))) - (fConst72 * ((fConst31 * fRec24[1]) + (fConst71 * fRec24[2]))));
		fRec33[0] = ((fConst17 * (fRec32[1] + fRec32[2])) + (fConst16 * fRec33[1]));
		double fTemp10 = (fConst76 * fRec34[1]);
		fRec34[0] = (fRec15[0] - (fConst81 * ((fConst80 * fRec34[2]) + fTemp10)));
		fRec32[0] = ((fConst81 * (fTemp10 + ((fConst89 * fRec34[0]) + (fConst88 * fRec34[2])))) - fRec33[0]);
		fRec31[0] = (fRec32[0] - (fConst94 * ((fConst93 * fRec31[2]) + (fConst91 * fRec31[1]))));
		fRec30[0] = ((fConst94 * (fRec31[0] + (fRec31[2] + (2 * fRec31[1])))) - (fConst92 * ((fConst91 * fRec30[1]) + (fConst90 * fRec30[2]))));
		double fTemp11 = (((iSlow10)?((iSlow9)?(fConst92 * (fRec30[0] + (fRec30[2] + (2 * fRec30[1])))):(fConst72 * (fRec24[0] + (fRec24[2] + (2 * fRec24[1]))))):((iSlow9)?(fConst65 * (fRec22[0] + (fRec22[2] + (2 * fRec22[1])))):(fConst32 * (fRec12[0] + (fRec12[2] + (2 * fRec12[1])))))) + fTemp5);
		fVec5[IOTA&4095] = fTemp11;
		fRec41[0] = ((fSlow11 * (0 - fRec39[1])) + fRec41[1]);
		fRec40[0] = ((1 + (fRec40[1] + (fSlow11 * fRec41[0]))) - iVec0[1]);
		fRec39[0] = fRec40[0];
		double fTemp12 = (fSlow12 * (1 + max((double)0, (0.5 * (1 + fRec39[0])))));
		double fTemp13 = ((int((fRec35[1] != 0.0)))?((int(((fRec36[1] > 0.0) & (fRec36[1] < 1.0))))?fRec35[1]:0):((int(((fRec36[1] == 0.0) & (fTemp12 != fRec37[1]))))?fConst95:((int(((fRec36[1] == 1.0) & (fTemp12 != fRec38[1]))))?fConst96:0)));
		fRec35[0] = fTemp13;
		fRec36[0] = max(0.0, min(1.0, (fRec36[1] + fTemp13)));
		fRec37[0] = ((int(((fRec36[1] >= 1.0) & (fRec38[1] != fTemp12))))?fTemp12:fRec37[1]);
		fRec38[0] = ((int(((fRec36[1] <= 0.0) & (fRec37[1] != fTemp12))))?fTemp12:fRec38[1]);
		int iTemp14 = int((int(fRec38[0]) & 4095));
		int iTemp15 = int((int(fRec37[0]) & 4095));
		double fTemp16 = (1.0 - fRec36[0]);
		double fTemp17 = ((fTemp16 * fVec5[(IOTA-iTemp15)&4095]) + (fRec36[0] * fVec5[(IOTA-iTemp14)&4095]));
		fVec6[IOTA&4095] = fTemp17;
		fRec48[0] = ((fSlow13 * (0 - fRec46[1])) + fRec48[1]);
		fRec47[0] = ((1 + (fRec47[1] + (fSlow13 * fRec48[0]))) - iVec0[1]);
		fRec46[0] = fRec47[0];
		double fTemp18 = (fSlow14 * (1 + max((double)0, (0.5 * (1 + fRec46[0])))));
		double fTemp19 = ((int((fRec42[1] != 0.0)))?((int(((fRec43[1] > 0.0) & (fRec43[1] < 1.0))))?fRec42[1]:0):((int(((fRec43[1] == 0.0) & (fTemp18 != fRec44[1]))))?fConst95:((int(((fRec43[1] == 1.0) & (fTemp18 != fRec45[1]))))?fConst96:0)));
		fRec42[0] = fTemp19;
		fRec43[0] = max(0.0, min(1.0, (fRec43[1] + fTemp19)));
		fRec44[0] = ((int(((fRec43[1] >= 1.0) & (fRec45[1] != fTemp18))))?fTemp18:fRec44[1]);
		fRec45[0] = ((int(((fRec43[1] <= 0.0) & (fRec44[1] != fTemp18))))?fTemp18:fRec45[1]);
		int iTemp20 = int((int(fRec45[0]) & 4095));
		int iTemp21 = int((int(fRec44[0]) & 4095));
		double fTemp22 = (1.0 - fRec43[0]);
		fRec5[0] = (((fTemp22 * fVec6[(IOTA-iTemp21)&4095]) + (fRec43[0] * fVec6[(IOTA-iTemp20)&4095])) - fRec6[0]);
		fRec2[0] = (((iSlow15)?fRec5[0]:(fConst13 * fVec1[0])) - (fConst9 * fRec2[1]));
		double fTemp23 = (fTemp0 - 0.000257077328090757);
		fRec0[0] = ((fConst99 * ((fRec2[0] * fTemp23) + (fRec2[1] * fTemp1))) - (fConst5 * ((fConst4 * fRec0[2]) + (fConst2 * fRec0[1]))));
		output0[i] = (FAUSTFLOAT)(fConst5 * (fRec0[0] + (fRec0[2] + (2 * fRec0[1]))));
		fRec51[0] = ((double)input1[i] - (fConst12 * fRec51[1]));
		double fTemp24 = ((fTemp2 * fRec51[0]) + (0.000275923691873229 * (fRec3[0] * fRec51[1])));
		fVec7[0] = fTemp24;
		fRec53[0] = ((fConst17 * (fRec52[1] + fRec52[2])) + (fConst16 * fRec53[1]));
		double fTemp25 = (fConst34 * fRec56[1]);
		fRec63[0] = ((fConst16 * fRec63[1]) + (fConst45 * (fVec7[0] + fVec7[1])));
		fRec62[0] = (fRec63[0] - (0.3 * fRec62[1]));
		fRec61[0] = (((0.3 * fRec61[1]) + (2.0 / (1.0 + exp((0 - (5.0 * fRec62[0])))))) - 1.0);
		fRec60[0] = ((fConst48 * fRec60[1]) + (fConst47 * (fRec61[1] + fRec61[0])));
		fRec59[0] = (fRec60[0] - (fConst44 * ((fConst42 * fRec59[2]) + (fConst31 * fRec59[1]))));
		double fTemp26 = (fRec59[0] + (fRec59[2] + (2 * fRec59[1])));
		fVec8[0] = fTemp26;
		fRec58[0] = ((fConst53 * fRec58[1]) + (fConst52 * ((fConst49 * fVec8[0]) + (fConst50 * fVec8[1]))));
		fRec57[0] = ((fConst53 * fRec57[1]) + (fConst54 * ((fConst49 * fRec58[0]) + (fConst50 * fRec58[1]))));
		fRec56[0] = (fRec57[0] - (fConst41 * ((fConst39 * fRec56[2]) + fTemp25)));
		double fTemp27 = (fTemp25 + ((fConst57 * fRec56[0]) + (fConst56 * fRec56[2])));
		fVec9[0] = fTemp27;
		fRec55[0] = ((fConst62 * fRec55[1]) + (fConst61 * (fVec9[0] + fVec9[1])));
		fRec54[0] = (fRec55[0] - (fConst32 * ((fConst31 * fRec54[1]) + (fConst30 * fRec54[2]))));
		fRec65[0] = ((fConst70 * fRec65[1]) + (fConst69 * (fRec57[1] + fRec57[0])));
		fRec64[0] = (fRec65[0] - (fConst65 * ((fConst64 * fRec64[2]) + (fConst63 * fRec64[1]))));
		fRec69[0] = ((fConst17 * (fRec68[1] + fRec68[2])) + (fConst16 * fRec69[1]));
		double fTemp28 = (fConst76 * fRec70[1]);
		fRec71[0] = ((fConst86 * fRec71[1]) + (fConst85 * ((fConst82 * fRec58[0]) + (fConst83 * fRec58[1]))));
		fRec70[0] = (fRec71[0] - (fConst81 * ((fConst80 * fRec70[2]) + fTemp28)));
		fRec68[0] = ((fConst81 * (fTemp28 + ((fConst89 * fRec70[0]) + (fConst88 * fRec70[2])))) - fRec69[0]);
		fRec67[0] = (fRec68[0] - (fConst74 * ((fConst31 * fRec67[1]) + (fConst73 * fRec67[2]))));
		fRec66[0] = ((fConst74 * (fRec67[0] + (fRec67[2] + (2 * fRec67[1])))) - (fConst72 * ((fConst31 * fRec66[1]) + (fConst71 * fRec66[2]))));
		fRec75[0] = ((fConst17 * (fRec74[1] + fRec74[2])) + (fConst16 * fRec75[1]));
		double fTemp29 = (fConst76 * fRec76[1]);
		fRec76[0] = (fRec57[0] - (fConst81 * ((fConst80 * fRec76[2]) + fTemp29)));
		fRec74[0] = ((fConst81 * (fTemp29 + ((fConst89 * fRec76[0]) + (fConst88 * fRec76[2])))) - fRec75[0]);
		fRec73[0] = (fRec74[0] - (fConst94 * ((fConst93 * fRec73[2]) + (fConst91 * fRec73[1]))));
		fRec72[0] = ((fConst94 * (fRec73[0] + (fRec73[2] + (2 * fRec73[1])))) - (fConst92 * ((fConst91 * fRec72[1]) + (fConst90 * fRec72[2]))));
		double fTemp30 = (fTemp5 + ((iSlow10)?((iSlow9)?(fConst92 * (fRec72[0] + (fRec72[2] + (2 * fRec72[1])))):(fConst72 * (fRec66[0] + (fRec66[2] + (2 * fRec66[1]))))):((iSlow9)?(fConst65 * (fRec64[0] + (fRec64[2] + (2 * fRec64[1])))):(fConst32 * (fRec54[0] + (fRec54[2] + (2 * fRec54[1])))))));
		fVec10[IOTA&4095] = fTemp30;
		double fTemp31 = ((fTemp16 * fVec10[(IOTA-iTemp15)&4095]) + (fRec36[0] * fVec10[(IOTA-iTemp14)&4095]));
		fVec11[IOTA&4095] = fTemp31;
		fRec52[0] = (((fTemp22 * fVec11[(IOTA-iTemp21)&4095]) + (fRec43[0] * fVec11[(IOTA-iTemp20)&4095])) - fRec53[0]);
		fRec50[0] = (((iSlow15)?fRec52[0]:(fConst13 * fVec7[0])) - (fConst9 * fRec50[1]));
		fRec49[0] = ((fConst99 * ((fTemp23 * fRec50[0]) + (fRec50[1] * fTemp1))) - (fConst5 * ((fConst4 * fRec49[2]) + (fConst2 * fRec49[1]))));
		output1[i] = (FAUSTFLOAT)(fConst5 * (fRec49[0] + (fRec49[2] + (2 * fRec49[1]))));
		// post processing
		fRec49[2] = fRec49[1]; fRec49[1] = fRec49[0];
		fRec50[1] = fRec50[0];
		fRec52[2] = fRec52[1]; fRec52[1] = fRec52[0];
		fRec72[2] = fRec72[1]; fRec72[1] = fRec72[0];
		fRec73[2] = fRec73[1]; fRec73[1] = fRec73[0];
		fRec74[2] = fRec74[1]; fRec74[1] = fRec74[0];
		fRec76[2] = fRec76[1]; fRec76[1] = fRec76[0];
		fRec75[1] = fRec75[0];
		fRec66[2] = fRec66[1]; fRec66[1] = fRec66[0];
		fRec67[2] = fRec67[1]; fRec67[1] = fRec67[0];
		fRec68[2] = fRec68[1]; fRec68[1] = fRec68[0];
		fRec70[2] = fRec70[1]; fRec70[1] = fRec70[0];
		fRec71[1] = fRec71[0];
		fRec69[1] = fRec69[0];
		fRec64[2] = fRec64[1]; fRec64[1] = fRec64[0];
		fRec65[1] = fRec65[0];
		fRec54[2] = fRec54[1]; fRec54[1] = fRec54[0];
		fRec55[1] = fRec55[0];
		fVec9[1] = fVec9[0];
		fRec56[2] = fRec56[1]; fRec56[1] = fRec56[0];
		fRec57[1] = fRec57[0];
		fRec58[1] = fRec58[0];
		fVec8[1] = fVec8[0];
		fRec59[2] = fRec59[1]; fRec59[1] = fRec59[0];
		fRec60[1] = fRec60[0];
		fRec61[1] = fRec61[0];
		fRec62[1] = fRec62[0];
		fRec63[1] = fRec63[0];
		fRec53[1] = fRec53[0];
		fVec7[1] = fVec7[0];
		fRec51[1] = fRec51[0];
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		fRec2[1] = fRec2[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec45[1] = fRec45[0];
		fRec44[1] = fRec44[0];
		fRec43[1] = fRec43[0];
		fRec42[1] = fRec42[0];
		fRec46[1] = fRec46[0];
		fRec47[1] = fRec47[0];
		fRec48[1] = fRec48[0];
		fRec38[1] = fRec38[0];
		fRec37[1] = fRec37[0];
		fRec36[1] = fRec36[0];
		fRec35[1] = fRec35[0];
		fRec39[1] = fRec39[0];
		fRec40[1] = fRec40[0];
		fRec41[1] = fRec41[0];
		IOTA = IOTA+1;
		fRec30[2] = fRec30[1]; fRec30[1] = fRec30[0];
		fRec31[2] = fRec31[1]; fRec31[1] = fRec31[0];
		fRec32[2] = fRec32[1]; fRec32[1] = fRec32[0];
		fRec34[2] = fRec34[1]; fRec34[1] = fRec34[0];
		fRec33[1] = fRec33[0];
		fRec24[2] = fRec24[1]; fRec24[1] = fRec24[0];
		fRec25[2] = fRec25[1]; fRec25[1] = fRec25[0];
		fRec26[2] = fRec26[1]; fRec26[1] = fRec26[0];
		fRec28[2] = fRec28[1]; fRec28[1] = fRec28[0];
		fRec29[1] = fRec29[0];
		fRec27[1] = fRec27[0];
		fRec22[2] = fRec22[1]; fRec22[1] = fRec22[0];
		fRec23[1] = fRec23[0];
		fRec12[2] = fRec12[1]; fRec12[1] = fRec12[0];
		fRec13[1] = fRec13[0];
		fVec4[1] = fVec4[0];
		fRec14[2] = fRec14[1]; fRec14[1] = fRec14[0];
		fRec15[1] = fRec15[0];
		fRec16[1] = fRec16[0];
		fVec3[1] = fVec3[0];
		fRec17[2] = fRec17[1]; fRec17[1] = fRec17[0];
		fRec18[1] = fRec18[0];
		fRec19[1] = fRec19[0];
		fRec20[1] = fRec20[0];
		fRec21[1] = fRec21[0];
		fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
		fRec11[1] = fRec11[0];
		fRec8[1] = fRec8[0];
		fVec2[1] = fVec2[0];
		iRec10[1] = iRec10[0];
		fRec9[1] = fRec9[0];
		fRec6[1] = fRec6[0];
		fVec1[1] = fVec1[0];
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		fRec1[1] = fRec1[0];
		iVec0[1] = iVec0[0];
	}
#undef fslider0
#undef fslider1
#undef fcheckbox0
#undef fslider2
#undef fslider3
#undef fslider4
#undef fslider5
#undef fslider6
#undef fslider7
#undef fcheckbox1
}
		
void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case DRIVE: 
		fslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case FLUTTERDEPTH: 
		fslider7_ = (float*)data; // , 0.0, 0.0, 0.03, 0.001 
		break;
	case FLUTTERFREQ: 
		fslider6_ = (float*)data; // , 4.0, 4.0, 6e+01, 0.1 
		break;
	case GAIN: 
		fslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case ON: 
		fcheckbox1_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case WOWDEPTH: 
		fslider5_ = (float*)data; // , 0.0, 0.0, 0.03, 0.001 
		break;
	case WOWFREQ: 
		fslider4_ = (float*)data; // , 0.0, 0.0, 4.0, 0.1 
		break;
	case SPEED: 
		fcheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case TAPEHISS: 
		fslider2_ = (float*)data; // , 0.0, 0.0, 1.0, 0.01 
		break;
	case TAPETYPE: 
		fslider3_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	default:
		break;
	}
}

void Dsp::connect_static(uint32_t port,void* data, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->connect(port, data);
}


PluginLV2 *plugin() {
	return new Dsp();
}

void Dsp::del_instance(PluginLV2 *p)
{
	delete static_cast<Dsp*>(p);
}

/*
typedef enum
{
   DRIVE, 
   FLUTTERDEPTH, 
   FLUTTERFREQ, 
   GAIN, 
   ON, 
   WOWDEPTH, 
   WOWFREQ, 
   SPEED, 
   TAPEHISS, 
   TAPETYPE, 
} PortIndex;
*/

} // end namespace gxtape_st
