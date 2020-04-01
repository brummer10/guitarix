// generated from file '../src/LV2/faust/gxtape_st.dsp' by dsp2cc:
// Code generated with Faust 2.15.11 (https://faust.grame.fr)


namespace gxtape_st {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	double fConst4;
	double fConst5;
	double fConst6;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT	*fCheckbox0_;
	double fConst7;
	double fConst8;
	double fConst9;
	double fConst10;
	int iVec0[2];
	double fRec2[2];
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec3[2];
	double fVec1[2];
	double fConst11;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fConst12;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec11[2];
	double fRec10[2];
	double fRec9[2];
	double fConst13;
	double fConst14;
	double fRec5[2];
	double fRec6[2];
	double fRec7[2];
	double fRec8[2];
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	FAUSTFLOAT fVslider4;
	FAUSTFLOAT	*fVslider4_;
	double fRec18[2];
	double fRec17[2];
	double fRec16[2];
	double fRec12[2];
	double fRec13[2];
	double fRec14[2];
	double fRec15[2];
	FAUSTFLOAT fVslider5;
	FAUSTFLOAT	*fVslider5_;
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT	*fCheckbox1_;
	double fConst15;
	double fConst16;
	double fConst17;
	double fConst18;
	double fConst19;
	double fConst20;
	double fConst21;
	double fConst22;
	double fConst23;
	double fConst24;
	double fConst25;
	double fConst26;
	double fConst27;
	double fConst28;
	double fConst29;
	double fConst30;
	double fConst31;
	double fConst32;
	double fConst33;
	double fConst34;
	double fConst35;
	double fConst36;
	double fConst37;
	double fConst38;
	double fRec28[2];
	double fRec27[2];
	double fRec26[2];
	double fRec25[2];
	double fConst39;
	double fConst40;
	double fRec24[3];
	double fVec2[2];
	double fConst41;
	double fConst42;
	double fRec23[2];
	double fConst43;
	double fRec22[2];
	double fConst44;
	double fRec21[3];
	double fConst45;
	double fConst46;
	double fConst47;
	double fVec3[2];
	double fRec20[2];
	double fConst48;
	double fRec19[3];
	double fConst49;
	double fConst50;
	double fConst51;
	double fConst52;
	double fConst53;
	double fRec30[2];
	double fConst54;
	double fConst55;
	double fRec29[3];
	double fConst56;
	double fConst57;
	double fConst58;
	double fConst59;
	double fConst60;
	double fConst61;
	double fConst62;
	double fConst63;
	double fConst64;
	double fConst65;
	double fConst66;
	double fConst67;
	double fConst68;
	double fConst69;
	double fRec35[2];
	double fConst70;
	double fRec34[3];
	double fConst71;
	double fConst72;
	double fConst73;
	double fRec36[2];
	double fRec33[3];
	double fConst74;
	double fRec32[3];
	double fConst75;
	double fRec31[3];
	double fConst76;
	double fConst77;
	double fRec40[3];
	double fRec41[2];
	double fRec39[3];
	double fConst78;
	double fConst79;
	double fRec38[3];
	double fConst80;
	double fRec37[3];
	double fConst81;
	double fConst82;
	double fConst83;
	FAUSTFLOAT fVslider6;
	FAUSTFLOAT	*fVslider6_;
	double fRec44[2];
	int iRec45[2];
	double fVec4[2];
	double fConst84;
	double fRec43[2];
	double fConst85;
	double fConst86;
	double fConst87;
	double fConst88;
	double fConst89;
	double fConst90;
	double fRec46[2];
	double fRec42[3];
	int IOTA;
	double *fVec5;
	double *fVec6;
	double fRec47[2];
	double fRec4[3];
	double fConst91;
	double fRec1[2];
	FAUSTFLOAT fVslider7;
	FAUSTFLOAT	*fVslider7_;
	double fRec48[2];
	double fConst92;
	double fConst93;
	double fRec0[3];
	double fRec51[2];
	double fVec7[2];
	double fRec62[2];
	double fRec61[2];
	double fRec60[2];
	double fRec59[2];
	double fRec58[3];
	double fVec8[2];
	double fRec57[2];
	double fRec56[2];
	double fRec55[3];
	double fVec9[2];
	double fRec54[2];
	double fRec53[3];
	double fRec64[2];
	double fRec63[3];
	double fRec69[2];
	double fRec68[3];
	double fRec70[2];
	double fRec67[3];
	double fRec66[3];
	double fRec65[3];
	double fRec74[3];
	double fRec75[2];
	double fRec73[3];
	double fRec72[3];
	double fRec71[3];
	double *fVec10;
	double *fVec11;
	double fRec76[2];
	double fRec52[3];
	double fRec50[2];
	double fRec49[3];

	bool mem_allocated;
	void mem_alloc();
	void mem_free();
	void connect(uint32_t port,void* data);
	void clear_state_f();
	int activate(bool start);
	void init(uint32_t samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1);

	static void clear_state_f_static(PluginLV2*);
	static int activate_static(bool start, PluginLV2*);
	static void init_static(uint32_t samplingFreq, PluginLV2*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginLV2(),
	  fVec5(0),
	  fVec6(0),
	  fVec10(0),
	  fVec11(0),
	  mem_allocated(false) {
	version = PLUGINLV2_VERSION;
	id = "gxtape_st";
	name = N_("gxtape_st");
	mono_audio = 0;
	stereo_audio = compute_static;
	set_samplerate = init_static;
	activate_plugin = activate_static;
	connect_ports = connect_static;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) iVec0[l0] = 0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec2[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec3[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fVec1[l3] = 0.0;
	for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) fRec11[l4] = 0.0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fRec10[l5] = 0.0;
	for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) fRec9[l6] = 0.0;
	for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) fRec5[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fRec6[l8] = 0.0;
	for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) fRec7[l9] = 0.0;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) fRec8[l10] = 0.0;
	for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) fRec18[l11] = 0.0;
	for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) fRec17[l12] = 0.0;
	for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) fRec16[l13] = 0.0;
	for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) fRec12[l14] = 0.0;
	for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) fRec13[l15] = 0.0;
	for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) fRec14[l16] = 0.0;
	for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) fRec15[l17] = 0.0;
	for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) fRec28[l18] = 0.0;
	for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) fRec27[l19] = 0.0;
	for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) fRec26[l20] = 0.0;
	for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) fRec25[l21] = 0.0;
	for (int l22 = 0; (l22 < 3); l22 = (l22 + 1)) fRec24[l22] = 0.0;
	for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) fVec2[l23] = 0.0;
	for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) fRec23[l24] = 0.0;
	for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) fRec22[l25] = 0.0;
	for (int l26 = 0; (l26 < 3); l26 = (l26 + 1)) fRec21[l26] = 0.0;
	for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) fVec3[l27] = 0.0;
	for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) fRec20[l28] = 0.0;
	for (int l29 = 0; (l29 < 3); l29 = (l29 + 1)) fRec19[l29] = 0.0;
	for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) fRec30[l30] = 0.0;
	for (int l31 = 0; (l31 < 3); l31 = (l31 + 1)) fRec29[l31] = 0.0;
	for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) fRec35[l32] = 0.0;
	for (int l33 = 0; (l33 < 3); l33 = (l33 + 1)) fRec34[l33] = 0.0;
	for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) fRec36[l34] = 0.0;
	for (int l35 = 0; (l35 < 3); l35 = (l35 + 1)) fRec33[l35] = 0.0;
	for (int l36 = 0; (l36 < 3); l36 = (l36 + 1)) fRec32[l36] = 0.0;
	for (int l37 = 0; (l37 < 3); l37 = (l37 + 1)) fRec31[l37] = 0.0;
	for (int l38 = 0; (l38 < 3); l38 = (l38 + 1)) fRec40[l38] = 0.0;
	for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) fRec41[l39] = 0.0;
	for (int l40 = 0; (l40 < 3); l40 = (l40 + 1)) fRec39[l40] = 0.0;
	for (int l41 = 0; (l41 < 3); l41 = (l41 + 1)) fRec38[l41] = 0.0;
	for (int l42 = 0; (l42 < 3); l42 = (l42 + 1)) fRec37[l42] = 0.0;
	for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) fRec44[l43] = 0.0;
	for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) iRec45[l44] = 0;
	for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) fVec4[l45] = 0.0;
	for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) fRec43[l46] = 0.0;
	for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) fRec46[l47] = 0.0;
	for (int l48 = 0; (l48 < 3); l48 = (l48 + 1)) fRec42[l48] = 0.0;
	for (int l49 = 0; (l49 < 8192); l49 = (l49 + 1)) fVec5[l49] = 0.0;
	for (int l50 = 0; (l50 < 8192); l50 = (l50 + 1)) fVec6[l50] = 0.0;
	for (int l51 = 0; (l51 < 2); l51 = (l51 + 1)) fRec47[l51] = 0.0;
	for (int l52 = 0; (l52 < 3); l52 = (l52 + 1)) fRec4[l52] = 0.0;
	for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) fRec1[l53] = 0.0;
	for (int l54 = 0; (l54 < 2); l54 = (l54 + 1)) fRec48[l54] = 0.0;
	for (int l55 = 0; (l55 < 3); l55 = (l55 + 1)) fRec0[l55] = 0.0;
	for (int l56 = 0; (l56 < 2); l56 = (l56 + 1)) fRec51[l56] = 0.0;
	for (int l57 = 0; (l57 < 2); l57 = (l57 + 1)) fVec7[l57] = 0.0;
	for (int l58 = 0; (l58 < 2); l58 = (l58 + 1)) fRec62[l58] = 0.0;
	for (int l59 = 0; (l59 < 2); l59 = (l59 + 1)) fRec61[l59] = 0.0;
	for (int l60 = 0; (l60 < 2); l60 = (l60 + 1)) fRec60[l60] = 0.0;
	for (int l61 = 0; (l61 < 2); l61 = (l61 + 1)) fRec59[l61] = 0.0;
	for (int l62 = 0; (l62 < 3); l62 = (l62 + 1)) fRec58[l62] = 0.0;
	for (int l63 = 0; (l63 < 2); l63 = (l63 + 1)) fVec8[l63] = 0.0;
	for (int l64 = 0; (l64 < 2); l64 = (l64 + 1)) fRec57[l64] = 0.0;
	for (int l65 = 0; (l65 < 2); l65 = (l65 + 1)) fRec56[l65] = 0.0;
	for (int l66 = 0; (l66 < 3); l66 = (l66 + 1)) fRec55[l66] = 0.0;
	for (int l67 = 0; (l67 < 2); l67 = (l67 + 1)) fVec9[l67] = 0.0;
	for (int l68 = 0; (l68 < 2); l68 = (l68 + 1)) fRec54[l68] = 0.0;
	for (int l69 = 0; (l69 < 3); l69 = (l69 + 1)) fRec53[l69] = 0.0;
	for (int l70 = 0; (l70 < 2); l70 = (l70 + 1)) fRec64[l70] = 0.0;
	for (int l71 = 0; (l71 < 3); l71 = (l71 + 1)) fRec63[l71] = 0.0;
	for (int l72 = 0; (l72 < 2); l72 = (l72 + 1)) fRec69[l72] = 0.0;
	for (int l73 = 0; (l73 < 3); l73 = (l73 + 1)) fRec68[l73] = 0.0;
	for (int l74 = 0; (l74 < 2); l74 = (l74 + 1)) fRec70[l74] = 0.0;
	for (int l75 = 0; (l75 < 3); l75 = (l75 + 1)) fRec67[l75] = 0.0;
	for (int l76 = 0; (l76 < 3); l76 = (l76 + 1)) fRec66[l76] = 0.0;
	for (int l77 = 0; (l77 < 3); l77 = (l77 + 1)) fRec65[l77] = 0.0;
	for (int l78 = 0; (l78 < 3); l78 = (l78 + 1)) fRec74[l78] = 0.0;
	for (int l79 = 0; (l79 < 2); l79 = (l79 + 1)) fRec75[l79] = 0.0;
	for (int l80 = 0; (l80 < 3); l80 = (l80 + 1)) fRec73[l80] = 0.0;
	for (int l81 = 0; (l81 < 3); l81 = (l81 + 1)) fRec72[l81] = 0.0;
	for (int l82 = 0; (l82 < 3); l82 = (l82 + 1)) fRec71[l82] = 0.0;
	for (int l83 = 0; (l83 < 8192); l83 = (l83 + 1)) fVec10[l83] = 0.0;
	for (int l84 = 0; (l84 < 8192); l84 = (l84 + 1)) fVec11[l84] = 0.0;
	for (int l85 = 0; (l85 < 2); l85 = (l85 + 1)) fRec76[l85] = 0.0;
	for (int l86 = 0; (l86 < 3); l86 = (l86 + 1)) fRec52[l86] = 0.0;
	for (int l87 = 0; (l87 < 2); l87 = (l87 + 1)) fRec50[l87] = 0.0;
	for (int l88 = 0; (l88 < 3); l88 = (l88 + 1)) fRec49[l88] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSamplingFreq)));
	fConst1 = std::tan((62831.853071795864 / fConst0));
	fConst2 = (1.0 / fConst1);
	fConst3 = (1.0 / (((fConst2 + 1.4142135623730949) / fConst1) + 1.0));
	fConst4 = (2.08237464507809e-05 * fConst0);
	fConst5 = (fConst4 + 0.00046017036251682698);
	fConst6 = (0.10000000000000001 * (fConst0 / fConst5));
	fConst7 = (2.08237299868718e-05 * fConst0);
	fConst8 = (fConst7 + 0.000460960630154374);
	fConst9 = (0.10000000000000001 * (fConst0 / fConst8));
	fConst10 = ((0.000460960630154374 - fConst7) / fConst8);
	fConst11 = (0.0050000000000000001 * fConst0);
	fConst12 = (6.2831853071795862 / fConst0);
	fConst13 = (10.0 / fConst0);
	fConst14 = (0.0 - fConst13);
	fConst15 = std::tan((47123.889803846898 / fConst0));
	fConst16 = (1.0 / fConst15);
	fConst17 = (1.0 / (((fConst16 + 1.4142135623730949) / fConst15) + 1.0));
	fConst18 = std::tan((39269.908169872411 / fConst0));
	fConst19 = (1.0 / fConst18);
	fConst20 = (1.0 / (fConst19 + 1.0));
	fConst21 = (1.0 - fConst19);
	fConst22 = (std::sin((314.15926535897933 / fConst0)) * fConst0);
	fConst23 = (392.69908169872411 / fConst22);
	fConst24 = std::tan((157.07963267948966 / fConst0));
	fConst25 = (1.0 / fConst24);
	fConst26 = (1.0 / (((fConst23 + fConst25) / fConst24) + 1.0));
	fConst27 = (2.0 * (1.0 - (1.0 / mydsp_faustpower2_f(fConst24))));
	fConst28 = std::tan((78.539816339744831 / fConst0));
	fConst29 = (1.0 / fConst28);
	fConst30 = (fConst29 + 1.0);
	fConst31 = (1.0 / (fConst30 * fConst28));
	fConst32 = (0.0 - fConst31);
	fConst33 = (1.0 / (((fConst16 + 1.0000000000000004) / fConst15) + 1.0));
	fConst34 = (1.0 / (fConst16 + 1.0));
	fConst35 = (1.0 - fConst16);
	fConst36 = (1.0 / std::tan((14137.16694115407 / fConst0)));
	fConst37 = (1.0 / (fConst36 + 1.0));
	fConst38 = (1.0 - fConst36);
	fConst39 = (((fConst16 + -1.0000000000000004) / fConst15) + 1.0);
	fConst40 = (2.0 * (1.0 - (1.0 / mydsp_faustpower2_f(fConst15))));
	fConst41 = (1.0 - fConst29);
	fConst42 = (fConst41 / fConst30);
	fConst43 = (1.0 / fConst30);
	fConst44 = (((fConst25 - fConst23) / fConst24) + 1.0);
	fConst45 = (554.7021966383262 / fConst22);
	fConst46 = (((fConst45 + fConst25) / fConst24) + 1.0);
	fConst47 = (((fConst25 - fConst45) / fConst24) + 1.0);
	fConst48 = (((fConst16 + -1.4142135623730949) / fConst15) + 1.0);
	fConst49 = (1.0 / (((fConst19 + 1.4142135623730949) / fConst18) + 1.0));
	fConst50 = std::tan((31415.926535897932 / fConst0));
	fConst51 = (1.0 / fConst50);
	fConst52 = (1.0 / (fConst51 + 1.0));
	fConst53 = (1.0 - fConst51);
	fConst54 = (((fConst19 + -1.4142135623730949) / fConst18) + 1.0);
	fConst55 = (2.0 * (1.0 - (1.0 / mydsp_faustpower2_f(fConst18))));
	fConst56 = (1.0 / (((fConst16 + 0.76536686473017945) / fConst15) + 1.0));
	fConst57 = (1.0 / (((fConst16 + 1.8477590650225735) / fConst15) + 1.0));
	fConst58 = (std::sin((471.23889803846896 / fConst0)) * fConst0);
	fConst59 = (589.0486225480862 / fConst58);
	fConst60 = std::tan((235.61944901923448 / fConst0));
	fConst61 = (1.0 / fConst60);
	fConst62 = (1.0 / (((fConst59 + fConst61) / fConst60) + 1.0));
	fConst63 = (2.0 * (1.0 - (1.0 / mydsp_faustpower2_f(fConst60))));
	fConst64 = std::tan((109.95574287564276 / fConst0));
	fConst65 = (1.0 / fConst64);
	fConst66 = (fConst65 + 1.0);
	fConst67 = (0.0 - (1.0 / (fConst66 * fConst64)));
	fConst68 = (1.0 / fConst66);
	fConst69 = (1.0 - fConst65);
	fConst70 = (((fConst61 - fConst59) / fConst60) + 1.0);
	fConst71 = (1175.3065182545242 / fConst58);
	fConst72 = (((fConst71 + fConst61) / fConst60) + 1.0);
	fConst73 = (((fConst61 - fConst71) / fConst60) + 1.0);
	fConst74 = (((fConst16 + -1.8477590650225735) / fConst15) + 1.0);
	fConst75 = (((fConst16 + -0.76536686473017945) / fConst15) + 1.0);
	fConst76 = (1.0 / (((fConst51 + 0.76536686473017945) / fConst50) + 1.0));
	fConst77 = (1.0 / (((fConst51 + 1.8477590650225735) / fConst50) + 1.0));
	fConst78 = (((fConst51 + -1.8477590650225735) / fConst50) + 1.0);
	fConst79 = (2.0 * (1.0 - (1.0 / mydsp_faustpower2_f(fConst50))));
	fConst80 = (((fConst51 + -0.76536686473017945) / fConst50) + 1.0);
	fConst81 = (23561.944901923449 / fConst0);
	fConst82 = (1.0 / std::tan((785.39816339744823 / fConst0)));
	fConst83 = (1.0 / (fConst82 + 1.0));
	fConst84 = (1.0 - fConst82);
	fConst85 = std::tan((9424.7779607693792 / fConst0));
	fConst86 = (1.0 / fConst85);
	fConst87 = (fConst86 + 1.0);
	fConst88 = (1.0 / (fConst87 * fConst85));
	fConst89 = (0.0 - fConst88);
	fConst90 = ((1.0 - fConst86) / fConst87);
	fConst91 = ((0.00046017036251682698 - fConst4) / fConst5);
	fConst92 = (((fConst2 + -1.4142135623730949) / fConst1) + 1.0);
	fConst93 = (2.0 * (1.0 - (1.0 / mydsp_faustpower2_f(fConst1))));
	fCheckbox0 = FAUSTFLOAT(0.0);
	fVslider0 = FAUSTFLOAT(0.5);
	fVslider1 = FAUSTFLOAT(0.0);
	fVslider2 = FAUSTFLOAT(4.0);
	fVslider3 = FAUSTFLOAT(0.0);
	fVslider4 = FAUSTFLOAT(0.0);
	fVslider5 = FAUSTFLOAT(0.0);
	fCheckbox1 = FAUSTFLOAT(0.0);
	fVslider6 = FAUSTFLOAT(0.0);
	fVslider7 = FAUSTFLOAT(0.5);
	IOTA = 0;
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void Dsp::mem_alloc()
{
	if (!fVec5) fVec5 = new double[8192];
	if (!fVec6) fVec6 = new double[8192];
	if (!fVec10) fVec10 = new double[8192];
	if (!fVec11) fVec11 = new double[8192];
	mem_allocated = true;
}

void Dsp::mem_free()
{
	mem_allocated = false;
	if (fVec5) { delete fVec5; fVec5 = 0; }
	if (fVec6) { delete fVec6; fVec6 = 0; }
	if (fVec10) { delete fVec10; fVec10 = 0; }
	if (fVec11) { delete fVec11; fVec11 = 0; }
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

int Dsp::activate_static(bool start, PluginLV2 *p)
{
	return static_cast<Dsp*>(p)->activate(start);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
#define fCheckbox0 (*fCheckbox0_)
#define fVslider0 (*fVslider0_)
#define fVslider1 (*fVslider1_)
#define fVslider2 (*fVslider2_)
#define fVslider3 (*fVslider3_)
#define fVslider4 (*fVslider4_)
#define fVslider5 (*fVslider5_)
#define fCheckbox1 (*fCheckbox1_)
#define fVslider6 (*fVslider6_)
#define fVslider7 (*fVslider7_)
	int iSlow0 = int(double(fCheckbox0));
	double fSlow1 = (0.004073836948085289 * (std::exp(double(fVslider0)) + -1.0));
	double fSlow2 = (fConst11 * double(fVslider1));
	double fSlow3 = (fConst12 * double(fVslider2));
	double fSlow4 = (fConst11 * double(fVslider3));
	double fSlow5 = (fConst12 * double(fVslider4));
	int iSlow6 = int(double(fVslider5));
	double fSlow7 = double(fCheckbox1);
	int iSlow8 = int(fSlow7);
	double fSlow9 = std::tan((fConst81 * (2.0 - fSlow7)));
	double fSlow10 = (1.0 / fSlow9);
	double fSlow11 = (1.0 / (((fSlow10 + 1.4142135623730949) / fSlow9) + 1.0));
	double fSlow12 = (4.7399999999994777e-06 * double(fVslider6));
	double fSlow13 = (((fSlow10 + -1.4142135623730949) / fSlow9) + 1.0);
	double fSlow14 = (2.0 * (1.0 - (1.0 / mydsp_faustpower2_f(fSlow9))));
	double fSlow15 = (0.004073836948085289 * (std::exp((1.0 - double(fVslider7))) + -1.0));
	for (int i = 0; (i < count); i = (i + 1)) {
		iVec0[0] = 1;
		fRec2[0] = (double(input0[i]) - (fConst10 * fRec2[1]));
		fRec3[0] = (fSlow1 + (0.99299999999999999 * fRec3[1]));
		double fTemp0 = (0.0 - (0.00027592369187322898 * fRec3[0]));
		double fTemp1 = ((fRec2[0] * fTemp0) + (0.00027592369187322898 * (fRec3[0] * fRec2[1])));
		fVec1[0] = fTemp1;
		fRec11[0] = (fRec11[1] + (fSlow3 * (0.0 - fRec9[1])));
		double fTemp2 = double((1 - iVec0[1]));
		fRec10[0] = ((fSlow3 * fRec11[0]) + (fTemp2 + fRec10[1]));
		fRec9[0] = fRec10[0];
		double fTemp3 = (fSlow2 * (std::max<double>(0.0, (0.5 * (fRec9[0] + 1.0))) + 1.0));
		double fTemp4 = ((fRec5[1] != 0.0)?(((fRec6[1] > 0.0) & (fRec6[1] < 1.0))?fRec5[1]:0.0):(((fRec6[1] == 0.0) & (fTemp3 != fRec7[1]))?fConst13:(((fRec6[1] == 1.0) & (fTemp3 != fRec8[1]))?fConst14:0.0)));
		fRec5[0] = fTemp4;
		fRec6[0] = std::max<double>(0.0, std::min<double>(1.0, (fRec6[1] + fTemp4)));
		fRec7[0] = (((fRec6[1] >= 1.0) & (fRec8[1] != fTemp3))?fTemp3:fRec7[1]);
		fRec8[0] = (((fRec6[1] <= 0.0) & (fRec7[1] != fTemp3))?fTemp3:fRec8[1]);
		double fTemp5 = (1.0 - fRec6[0]);
		fRec18[0] = (fRec18[1] + (fSlow5 * (0.0 - fRec16[1])));
		fRec17[0] = ((fSlow5 * fRec18[0]) + (fTemp2 + fRec17[1]));
		fRec16[0] = fRec17[0];
		double fTemp6 = (fSlow4 * (std::max<double>(0.0, (0.5 * (fRec16[0] + 1.0))) + 1.0));
		double fTemp7 = ((fRec12[1] != 0.0)?(((fRec13[1] > 0.0) & (fRec13[1] < 1.0))?fRec12[1]:0.0):(((fRec13[1] == 0.0) & (fTemp6 != fRec14[1]))?fConst13:(((fRec13[1] == 1.0) & (fTemp6 != fRec15[1]))?fConst14:0.0)));
		fRec12[0] = fTemp7;
		fRec13[0] = std::max<double>(0.0, std::min<double>(1.0, (fRec13[1] + fTemp7)));
		fRec14[0] = (((fRec13[1] >= 1.0) & (fRec15[1] != fTemp6))?fTemp6:fRec14[1]);
		fRec15[0] = (((fRec13[1] <= 0.0) & (fRec14[1] != fTemp6))?fTemp6:fRec15[1]);
		double fTemp8 = (1.0 - fRec13[0]);
		fRec28[0] = (fConst37 * ((fConst9 * (fTemp1 + fVec1[1])) - (fConst38 * fRec28[1])));
		fRec27[0] = (fRec28[0] - (0.29999999999999999 * fRec27[1]));
		fRec26[0] = (((2.0 / (std::exp((0.0 - (5.0 * fRec27[0]))) + 1.0)) + (0.29999999999999999 * fRec26[1])) + -1.0);
		fRec25[0] = (0.0 - (fConst34 * ((fConst35 * fRec25[1]) - (fRec26[0] + fRec26[1]))));
		fRec24[0] = (fRec25[0] - (fConst33 * ((fConst39 * fRec24[2]) + (fConst40 * fRec24[1]))));
		double fTemp9 = (fRec24[2] + (fRec24[0] + (2.0 * fRec24[1])));
		fVec2[0] = fTemp9;
		fRec23[0] = ((fConst33 * ((fConst31 * fTemp9) + (fConst32 * fVec2[1]))) - (fConst42 * fRec23[1]));
		fRec22[0] = ((fConst32 * fRec23[1]) - (fConst43 * ((fConst41 * fRec22[1]) - (fConst29 * fRec23[0]))));
		double fTemp10 = (fConst27 * fRec21[1]);
		fRec21[0] = (fRec22[0] - (fConst26 * ((fConst44 * fRec21[2]) + fTemp10)));
		double fTemp11 = ((fTemp10 + (fConst46 * fRec21[0])) + (fConst47 * fRec21[2]));
		fVec3[0] = fTemp11;
		fRec20[0] = (0.0 - (fConst20 * ((fConst21 * fRec20[1]) - (fConst26 * (fTemp11 + fVec3[1])))));
		fRec19[0] = (fRec20[0] - (fConst17 * ((fConst48 * fRec19[2]) + (fConst40 * fRec19[1]))));
		fRec30[0] = (0.0 - (fConst52 * ((fConst53 * fRec30[1]) - (fRec22[0] + fRec22[1]))));
		fRec29[0] = (fRec30[0] - (fConst49 * ((fConst54 * fRec29[2]) + (fConst55 * fRec29[1]))));
		fRec35[0] = ((fConst67 * fRec23[1]) - (fConst68 * ((fConst69 * fRec35[1]) - (fConst65 * fRec23[0]))));
		double fTemp12 = (fConst63 * fRec34[1]);
		fRec34[0] = (fRec35[0] - (fConst62 * ((fConst70 * fRec34[2]) + fTemp12)));
		fRec36[0] = (0.0 - (fConst37 * ((fConst38 * fRec36[1]) - (fRec33[1] + fRec33[2]))));
		fRec33[0] = ((fConst62 * ((fTemp12 + (fConst72 * fRec34[0])) + (fConst73 * fRec34[2]))) - fRec36[0]);
		fRec32[0] = (fRec33[0] - (fConst57 * ((fConst74 * fRec32[2]) + (fConst40 * fRec32[1]))));
		fRec31[0] = ((fConst57 * (fRec32[2] + (fRec32[0] + (2.0 * fRec32[1])))) - (fConst56 * ((fConst75 * fRec31[2]) + (fConst40 * fRec31[1]))));
		double fTemp13 = (fConst63 * fRec40[1]);
		fRec40[0] = (fRec22[0] - (fConst62 * ((fConst70 * fRec40[2]) + fTemp13)));
		fRec41[0] = (0.0 - (fConst37 * ((fConst38 * fRec41[1]) - (fRec39[1] + fRec39[2]))));
		fRec39[0] = ((fConst62 * ((fTemp13 + (fConst72 * fRec40[0])) + (fConst73 * fRec40[2]))) - fRec41[0]);
		fRec38[0] = (fRec39[0] - (fConst77 * ((fConst78 * fRec38[2]) + (fConst79 * fRec38[1]))));
		fRec37[0] = ((fConst77 * (fRec38[2] + (fRec38[0] + (2.0 * fRec38[1])))) - (fConst76 * ((fConst80 * fRec37[2]) + (fConst79 * fRec37[1]))));
		fRec44[0] = (fSlow12 + (0.99990000000000001 * fRec44[1]));
		iRec45[0] = ((1103515245 * iRec45[1]) + 12345);
		double fTemp14 = (fRec44[0] * double(iRec45[0]));
		fVec4[0] = fTemp14;
		fRec43[0] = (fConst83 * ((4.6566128752457969e-10 * (fTemp14 + fVec4[1])) - (fConst84 * fRec43[1])));
		fRec46[0] = ((4.6566128752457969e-10 * ((fConst88 * fTemp14) + (fConst89 * fVec4[1]))) - (fConst90 * fRec46[1]));
		fRec42[0] = ((fRec43[0] + (0.20000000000000001 * fRec46[0])) - (fSlow11 * ((fSlow13 * fRec42[2]) + (fSlow14 * fRec42[1]))));
		double fTemp15 = (fSlow11 * (fRec42[2] + (fRec42[0] + (2.0 * fRec42[1]))));
		double fTemp16 = ((iSlow6?(iSlow8?(fConst76 * (fRec37[2] + (fRec37[0] + (2.0 * fRec37[1])))):(fConst56 * (fRec31[2] + (fRec31[0] + (2.0 * fRec31[1]))))):(iSlow8?(fConst49 * (fRec29[2] + (fRec29[0] + (2.0 * fRec29[1])))):(fConst17 * (fRec19[2] + (fRec19[0] + (2.0 * fRec19[1])))))) + fTemp15);
		fVec5[(IOTA & 8191)] = fTemp16;
		int iTemp17 = int(std::min<double>(4096.0, std::max<double>(0.0, fRec14[0])));
		int iTemp18 = int(std::min<double>(4096.0, std::max<double>(0.0, fRec15[0])));
		double fTemp19 = ((fTemp8 * fVec5[((IOTA - iTemp17) & 8191)]) + (fRec13[0] * fVec5[((IOTA - iTemp18) & 8191)]));
		fVec6[(IOTA & 8191)] = fTemp19;
		int iTemp20 = int(std::min<double>(4096.0, std::max<double>(0.0, fRec7[0])));
		int iTemp21 = int(std::min<double>(4096.0, std::max<double>(0.0, fRec8[0])));
		fRec47[0] = (0.0 - (fConst37 * ((fConst38 * fRec47[1]) - (fRec4[1] + fRec4[2]))));
		fRec4[0] = (((fTemp5 * fVec6[((IOTA - iTemp20) & 8191)]) + (fRec6[0] * fVec6[((IOTA - iTemp21) & 8191)])) - fRec47[0]);
		fRec1[0] = ((iSlow0?fRec4[0]:(fConst9 * fTemp1)) - (fConst91 * fRec1[1]));
		fRec48[0] = (fSlow15 + (0.99299999999999999 * fRec48[1]));
		double fTemp22 = ((0.0 - (0.00025707732809075701 * fRec48[0])) + 0.00025707732809075701);
		double fTemp23 = (fRec48[0] + -1.0);
		fRec0[0] = ((fConst6 * ((fRec1[1] * fTemp22) + (0.00025707732809075701 * (fRec1[0] * fTemp23)))) - (fConst3 * ((fConst92 * fRec0[2]) + (fConst93 * fRec0[1]))));
		output0[i] = FAUSTFLOAT((fConst3 * (fRec0[2] + (fRec0[0] + (2.0 * fRec0[1])))));
		fRec51[0] = (double(input1[i]) - (fConst10 * fRec51[1]));
		double fTemp24 = ((fRec51[0] * fTemp0) + (0.00027592369187322898 * (fRec3[0] * fRec51[1])));
		fVec7[0] = fTemp24;
		fRec62[0] = (fConst37 * ((fConst9 * (fTemp24 + fVec7[1])) - (fConst38 * fRec62[1])));
		fRec61[0] = (fRec62[0] - (0.29999999999999999 * fRec61[1]));
		fRec60[0] = (((2.0 / (std::exp((0.0 - (5.0 * fRec61[0]))) + 1.0)) + (0.29999999999999999 * fRec60[1])) + -1.0);
		fRec59[0] = (0.0 - (fConst34 * ((fConst35 * fRec59[1]) - (fRec60[0] + fRec60[1]))));
		fRec58[0] = (fRec59[0] - (fConst33 * ((fConst39 * fRec58[2]) + (fConst40 * fRec58[1]))));
		double fTemp25 = (fRec58[2] + (fRec58[0] + (2.0 * fRec58[1])));
		fVec8[0] = fTemp25;
		fRec57[0] = ((fConst33 * ((fConst31 * fTemp25) + (fConst32 * fVec8[1]))) - (fConst42 * fRec57[1]));
		fRec56[0] = ((fConst32 * fRec57[1]) - (fConst43 * ((fConst41 * fRec56[1]) - (fConst29 * fRec57[0]))));
		double fTemp26 = (fConst27 * fRec55[1]);
		fRec55[0] = (fRec56[0] - (fConst26 * ((fConst44 * fRec55[2]) + fTemp26)));
		double fTemp27 = ((fTemp26 + (fConst46 * fRec55[0])) + (fConst47 * fRec55[2]));
		fVec9[0] = fTemp27;
		fRec54[0] = (0.0 - (fConst20 * ((fConst21 * fRec54[1]) - (fConst26 * (fTemp27 + fVec9[1])))));
		fRec53[0] = (fRec54[0] - (fConst17 * ((fConst48 * fRec53[2]) + (fConst40 * fRec53[1]))));
		fRec64[0] = (0.0 - (fConst52 * ((fConst53 * fRec64[1]) - (fRec56[0] + fRec56[1]))));
		fRec63[0] = (fRec64[0] - (fConst49 * ((fConst54 * fRec63[2]) + (fConst55 * fRec63[1]))));
		fRec69[0] = ((fConst67 * fRec57[1]) - (fConst68 * ((fConst69 * fRec69[1]) - (fConst65 * fRec57[0]))));
		double fTemp28 = (fConst63 * fRec68[1]);
		fRec68[0] = (fRec69[0] - (fConst62 * ((fConst70 * fRec68[2]) + fTemp28)));
		fRec70[0] = (0.0 - (fConst37 * ((fConst38 * fRec70[1]) - (fRec67[1] + fRec67[2]))));
		fRec67[0] = ((fConst62 * ((fTemp28 + (fConst72 * fRec68[0])) + (fConst73 * fRec68[2]))) - fRec70[0]);
		fRec66[0] = (fRec67[0] - (fConst57 * ((fConst74 * fRec66[2]) + (fConst40 * fRec66[1]))));
		fRec65[0] = ((fConst57 * (fRec66[2] + (fRec66[0] + (2.0 * fRec66[1])))) - (fConst56 * ((fConst75 * fRec65[2]) + (fConst40 * fRec65[1]))));
		double fTemp29 = (fConst63 * fRec74[1]);
		fRec74[0] = (fRec56[0] - (fConst62 * ((fConst70 * fRec74[2]) + fTemp29)));
		fRec75[0] = (0.0 - (fConst37 * ((fConst38 * fRec75[1]) - (fRec73[1] + fRec73[2]))));
		fRec73[0] = ((fConst62 * ((fTemp29 + (fConst72 * fRec74[0])) + (fConst73 * fRec74[2]))) - fRec75[0]);
		fRec72[0] = (fRec73[0] - (fConst77 * ((fConst78 * fRec72[2]) + (fConst79 * fRec72[1]))));
		fRec71[0] = ((fConst77 * (fRec72[2] + (fRec72[0] + (2.0 * fRec72[1])))) - (fConst76 * ((fConst80 * fRec71[2]) + (fConst79 * fRec71[1]))));
		double fTemp30 = (fTemp15 + (iSlow6?(iSlow8?(fConst76 * (fRec71[2] + (fRec71[0] + (2.0 * fRec71[1])))):(fConst56 * (fRec65[2] + (fRec65[0] + (2.0 * fRec65[1]))))):(iSlow8?(fConst49 * (fRec63[2] + (fRec63[0] + (2.0 * fRec63[1])))):(fConst17 * (fRec53[2] + (fRec53[0] + (2.0 * fRec53[1])))))));
		fVec10[(IOTA & 8191)] = fTemp30;
		double fTemp31 = ((fTemp8 * fVec10[((IOTA - iTemp17) & 8191)]) + (fRec13[0] * fVec10[((IOTA - iTemp18) & 8191)]));
		fVec11[(IOTA & 8191)] = fTemp31;
		fRec76[0] = (0.0 - (fConst37 * ((fConst38 * fRec76[1]) - (fRec52[1] + fRec52[2]))));
		fRec52[0] = (((fTemp5 * fVec11[((IOTA - iTemp20) & 8191)]) + (fRec6[0] * fVec11[((IOTA - iTemp21) & 8191)])) - fRec76[0]);
		fRec50[0] = ((iSlow0?fRec52[0]:(fConst9 * fTemp24)) - (fConst91 * fRec50[1]));
		fRec49[0] = ((fConst6 * ((fTemp22 * fRec50[1]) + (0.00025707732809075701 * (fRec50[0] * fTemp23)))) - (fConst3 * ((fConst92 * fRec49[2]) + (fConst93 * fRec49[1]))));
		output1[i] = FAUSTFLOAT((fConst3 * (fRec49[2] + (fRec49[0] + (2.0 * fRec49[1])))));
		iVec0[1] = iVec0[0];
		fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fVec1[1] = fVec1[0];
		fRec11[1] = fRec11[0];
		fRec10[1] = fRec10[0];
		fRec9[1] = fRec9[0];
		fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
		fRec18[1] = fRec18[0];
		fRec17[1] = fRec17[0];
		fRec16[1] = fRec16[0];
		fRec12[1] = fRec12[0];
		fRec13[1] = fRec13[0];
		fRec14[1] = fRec14[0];
		fRec15[1] = fRec15[0];
		fRec28[1] = fRec28[0];
		fRec27[1] = fRec27[0];
		fRec26[1] = fRec26[0];
		fRec25[1] = fRec25[0];
		fRec24[2] = fRec24[1];
		fRec24[1] = fRec24[0];
		fVec2[1] = fVec2[0];
		fRec23[1] = fRec23[0];
		fRec22[1] = fRec22[0];
		fRec21[2] = fRec21[1];
		fRec21[1] = fRec21[0];
		fVec3[1] = fVec3[0];
		fRec20[1] = fRec20[0];
		fRec19[2] = fRec19[1];
		fRec19[1] = fRec19[0];
		fRec30[1] = fRec30[0];
		fRec29[2] = fRec29[1];
		fRec29[1] = fRec29[0];
		fRec35[1] = fRec35[0];
		fRec34[2] = fRec34[1];
		fRec34[1] = fRec34[0];
		fRec36[1] = fRec36[0];
		fRec33[2] = fRec33[1];
		fRec33[1] = fRec33[0];
		fRec32[2] = fRec32[1];
		fRec32[1] = fRec32[0];
		fRec31[2] = fRec31[1];
		fRec31[1] = fRec31[0];
		fRec40[2] = fRec40[1];
		fRec40[1] = fRec40[0];
		fRec41[1] = fRec41[0];
		fRec39[2] = fRec39[1];
		fRec39[1] = fRec39[0];
		fRec38[2] = fRec38[1];
		fRec38[1] = fRec38[0];
		fRec37[2] = fRec37[1];
		fRec37[1] = fRec37[0];
		fRec44[1] = fRec44[0];
		iRec45[1] = iRec45[0];
		fVec4[1] = fVec4[0];
		fRec43[1] = fRec43[0];
		fRec46[1] = fRec46[0];
		fRec42[2] = fRec42[1];
		fRec42[1] = fRec42[0];
		IOTA = (IOTA + 1);
		fRec47[1] = fRec47[0];
		fRec4[2] = fRec4[1];
		fRec4[1] = fRec4[0];
		fRec1[1] = fRec1[0];
		fRec48[1] = fRec48[0];
		fRec0[2] = fRec0[1];
		fRec0[1] = fRec0[0];
		fRec51[1] = fRec51[0];
		fVec7[1] = fVec7[0];
		fRec62[1] = fRec62[0];
		fRec61[1] = fRec61[0];
		fRec60[1] = fRec60[0];
		fRec59[1] = fRec59[0];
		fRec58[2] = fRec58[1];
		fRec58[1] = fRec58[0];
		fVec8[1] = fVec8[0];
		fRec57[1] = fRec57[0];
		fRec56[1] = fRec56[0];
		fRec55[2] = fRec55[1];
		fRec55[1] = fRec55[0];
		fVec9[1] = fVec9[0];
		fRec54[1] = fRec54[0];
		fRec53[2] = fRec53[1];
		fRec53[1] = fRec53[0];
		fRec64[1] = fRec64[0];
		fRec63[2] = fRec63[1];
		fRec63[1] = fRec63[0];
		fRec69[1] = fRec69[0];
		fRec68[2] = fRec68[1];
		fRec68[1] = fRec68[0];
		fRec70[1] = fRec70[0];
		fRec67[2] = fRec67[1];
		fRec67[1] = fRec67[0];
		fRec66[2] = fRec66[1];
		fRec66[1] = fRec66[0];
		fRec65[2] = fRec65[1];
		fRec65[1] = fRec65[0];
		fRec74[2] = fRec74[1];
		fRec74[1] = fRec74[0];
		fRec75[1] = fRec75[0];
		fRec73[2] = fRec73[1];
		fRec73[1] = fRec73[0];
		fRec72[2] = fRec72[1];
		fRec72[1] = fRec72[0];
		fRec71[2] = fRec71[1];
		fRec71[1] = fRec71[0];
		fRec76[1] = fRec76[0];
		fRec52[2] = fRec52[1];
		fRec52[1] = fRec52[0];
		fRec50[1] = fRec50[0];
		fRec49[2] = fRec49[1];
		fRec49[1] = fRec49[0];
	}
#undef fCheckbox0
#undef fVslider0
#undef fVslider1
#undef fVslider2
#undef fVslider3
#undef fVslider4
#undef fVslider5
#undef fCheckbox1
#undef fVslider6
#undef fVslider7
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
		fVslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case FLUTTERDEPTH: 
		fVslider1_ = (float*)data; // , 0.0, 0.0, 0.029999999999999999, 0.001 
		break;
	case FLUTTERFREQ: 
		fVslider2_ = (float*)data; // , 4.0, 4.0, 60.0, 0.10000000000000001 
		break;
	case GAIN: 
		fVslider7_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case ON: 
		fCheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case WOWDEPTH: 
		fVslider3_ = (float*)data; // , 0.0, 0.0, 0.029999999999999999, 0.001 
		break;
	case WOWFREQ: 
		fVslider4_ = (float*)data; // , 0.0, 0.0, 4.0, 0.10000000000000001 
		break;
	case SPEED: 
		fCheckbox1_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case TAPEHISS: 
		fVslider6_ = (float*)data; // , 0.0, 0.0, 1.0, 0.01 
		break;
	case TAPETYPE: 
		fVslider5_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
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
