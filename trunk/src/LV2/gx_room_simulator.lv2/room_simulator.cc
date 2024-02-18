// generated from file './faust/room_simulator.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)


namespace room_simulator {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	int 	IOTA;
	double 	fVec0[65536];
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fConst8;
	double 	fRec17[3];
	double 	fRec16[3];
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
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec19[3];
	double 	fConst21;
	double 	fRec18[3];
	double 	fConst22;
	double 	fVec1[8192];
	int 	iConst23;
	double 	fRec14[2];
	double 	fVec2[8192];
	int 	iConst24;
	double 	fRec12[2];
	double 	fVec3[4096];
	int 	iConst25;
	int 	iConst26;
	double 	fVec4[8192];
	int 	iConst27;
	double 	fVec5[8192];
	int 	iConst28;
	double 	fRec10[2];
	double 	fRec8[2];
	double 	fVec6[8192];
	int 	iConst29;
	int 	iConst30;
	double 	fVec7[8192];
	int 	iConst31;
	double 	fVec8[8192];
	int 	iConst32;
	double 	fVec9[8192];
	int 	iConst33;
	double 	fRec6[2];
	double 	fRec4[2];
	double 	fRec2[2];
	double 	fRec0[2];
	double 	fRec37[3];
	double 	fRec36[3];
	double 	fConst34;
	double 	fConst35;
	double 	fConst36;
	double 	fConst37;
	double 	fConst38;
	double 	fConst39;
	double 	fConst40;
	double 	fRec39[3];
	double 	fRec38[3];
	double 	fVec10[8192];
	int 	iConst41;
	double 	fVec11[8192];
	int 	iConst42;
	double 	fVec12[8192];
	int 	iConst43;
	double 	fRec33[2];
	double 	fRec31[2];
	double 	fRec29[2];
	double 	fVec13[1024];
	int 	iConst44;
	double 	fVec14[8192];
	double 	fRec27[2];
	double 	fVec15[16384];
	int 	iConst45;
	int 	iConst46;
	double 	fVec16[8192];
	int 	iConst47;
	double 	fVec17[8192];
	int 	iConst48;
	double 	fRec25[2];
	double 	fRec23[2];
	double 	fRec21[2];
	double 	fConst49;
	double 	fConst50;
	double 	fConst51;
	double 	fConst52;
	double 	fConst53;
	double 	fConst54;
	double 	fConst55;
	double 	fConst56;
	double 	fConst57;
	double 	fConst58;
	double 	fConst59;
	double 	fRec54[3];
	double 	fConst60;
	double 	fRec53[3];
	double 	fVec18[8192];
	int 	iConst61;
	double 	fVec19[8192];
	double 	fVec20[8192];
	double 	fVec21[8192];
	double 	fRec50[2];
	double 	fRec48[2];
	double 	fRec46[2];
	double 	fVec22[8192];
	int 	iConst62;
	double 	fVec23[8192];
	double 	fRec44[2];
	double 	fRec42[2];
	double 	fRec40[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT	*fcheckbox0_;
	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(uint32_t samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(uint32_t samplingFreq, PluginLV2*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginLV2() {
	version = PLUGINLV2_VERSION;
	id = "room_simulator";
	name = "?room_simulator";
	mono_audio = compute_static;
	stereo_audio = 0;
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
	for (int i=0; i<65536; i++) fVec0[i] = 0;
	for (int i=0; i<3; i++) fRec17[i] = 0;
	for (int i=0; i<3; i++) fRec16[i] = 0;
	for (int i=0; i<3; i++) fRec19[i] = 0;
	for (int i=0; i<3; i++) fRec18[i] = 0;
	for (int i=0; i<8192; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<8192; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<4096; i++) fVec3[i] = 0;
	for (int i=0; i<8192; i++) fVec4[i] = 0;
	for (int i=0; i<8192; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<8192; i++) fVec6[i] = 0;
	for (int i=0; i<8192; i++) fVec7[i] = 0;
	for (int i=0; i<8192; i++) fVec8[i] = 0;
	for (int i=0; i<8192; i++) fVec9[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<3; i++) fRec37[i] = 0;
	for (int i=0; i<3; i++) fRec36[i] = 0;
	for (int i=0; i<3; i++) fRec39[i] = 0;
	for (int i=0; i<3; i++) fRec38[i] = 0;
	for (int i=0; i<8192; i++) fVec10[i] = 0;
	for (int i=0; i<8192; i++) fVec11[i] = 0;
	for (int i=0; i<8192; i++) fVec12[i] = 0;
	for (int i=0; i<2; i++) fRec33[i] = 0;
	for (int i=0; i<2; i++) fRec31[i] = 0;
	for (int i=0; i<2; i++) fRec29[i] = 0;
	for (int i=0; i<1024; i++) fVec13[i] = 0;
	for (int i=0; i<8192; i++) fVec14[i] = 0;
	for (int i=0; i<2; i++) fRec27[i] = 0;
	for (int i=0; i<16384; i++) fVec15[i] = 0;
	for (int i=0; i<8192; i++) fVec16[i] = 0;
	for (int i=0; i<8192; i++) fVec17[i] = 0;
	for (int i=0; i<2; i++) fRec25[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<3; i++) fRec54[i] = 0;
	for (int i=0; i<3; i++) fRec53[i] = 0;
	for (int i=0; i<8192; i++) fVec18[i] = 0;
	for (int i=0; i<8192; i++) fVec19[i] = 0;
	for (int i=0; i<8192; i++) fVec20[i] = 0;
	for (int i=0; i<8192; i++) fVec21[i] = 0;
	for (int i=0; i<2; i++) fRec50[i] = 0;
	for (int i=0; i<2; i++) fRec48[i] = 0;
	for (int i=0; i<2; i++) fRec46[i] = 0;
	for (int i=0; i<8192; i++) fVec22[i] = 0;
	for (int i=0; i<8192; i++) fVec23[i] = 0;
	for (int i=0; i<2; i++) fRec44[i] = 0;
	for (int i=0; i<2; i++) fRec42[i] = 0;
	for (int i=0; i<2; i++) fRec40[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	IOTA = 0;
	iConst0 = std::min(192000, std::max(1, (int)fSamplingFreq));
	fConst1 = tan((12566.370614359172 / double(iConst0)));
	fConst2 = (2 * (1 - (1.0 / faustpower<2>(fConst1))));
	fConst3 = (1.0 / fConst1);
	fConst4 = (1 + ((fConst3 - 0.7653668647301795) / fConst1));
	fConst5 = (1.0 / (1 + ((0.7653668647301795 + fConst3) / fConst1)));
	fConst6 = (1 + ((fConst3 - 1.8477590650225735) / fConst1));
	fConst7 = (1.0 / (1 + ((fConst3 + 1.8477590650225735) / fConst1)));
	fConst8 = (0.001 * iConst0);
	fConst9 = tan((3141.592653589793 / double(iConst0)));
	fConst10 = (2 * (1 - (1.0 / faustpower<2>(fConst9))));
	fConst11 = (1.0 / fConst9);
	fConst12 = (1 + ((fConst11 - 1.414213562373095) / fConst9));
	fConst13 = (1 + ((1.414213562373095 + fConst11) / fConst9));
	fConst14 = (1.0 / fConst13);
	fConst15 = tan((1570.7963267948965 / double(iConst0)));
	fConst16 = (1.0 / faustpower<2>(fConst15));
	fConst17 = (2 * (1 - fConst16));
	fConst18 = (1.0 / fConst15);
	fConst19 = (1 + ((fConst18 - 1.414213562373095) / fConst15));
	fConst20 = (1.0 / (1 + ((1.414213562373095 + fConst18) / fConst15)));
	fConst21 = (2 * (0 - fConst16));
	fConst22 = (1.799 / fConst13);
	iConst23 = int((int(((0.008 * iConst0) - 1)) & 8191));
	iConst24 = int((int(((0.012 * iConst0) - 1)) & 8191));
	iConst25 = int((0.004 * iConst0));
	iConst26 = int((iConst25 + int((0.017 * iConst0))));
	iConst27 = int((int(((0.08700000000000001 * iConst0) - 1)) & 8191));
	iConst28 = int((int(((0.062 * iConst0) - 1)) & 8191));
	iConst29 = int((0.031 * iConst0));
	iConst30 = int((iConst29 + int((0.003 * iConst0))));
	iConst31 = int((int(((0.12 * iConst0) - 1)) & 8191));
	iConst32 = int((int(((0.076 * iConst0) - 1)) & 8191));
	iConst33 = int((int(((0.03 * iConst0) - 1)) & 8191));
	fConst34 = tan((18849.55592153876 / double(iConst0)));
	fConst35 = (2 * (1 - (1.0 / faustpower<2>(fConst34))));
	fConst36 = (1.0 / fConst34);
	fConst37 = (1 + ((fConst36 - 0.7653668647301795) / fConst34));
	fConst38 = (1.0 / (1 + ((0.7653668647301795 + fConst36) / fConst34)));
	fConst39 = (1 + ((fConst36 - 1.8477590650225735) / fConst34));
	fConst40 = (1.0 / (1 + ((1.8477590650225735 + fConst36) / fConst34)));
	iConst41 = int((int(((0.035 * iConst0) - 1)) & 8191));
	iConst42 = int((int(((0.0083 * iConst0) - 1)) & 8191));
	iConst43 = int((int(((0.022 * iConst0) - 1)) & 8191));
	iConst44 = int((0.005 * iConst0));
	iConst45 = int((0.067 * iConst0));
	iConst46 = int((iConst45 + int((0.015 * iConst0))));
	iConst47 = int((int(((0.039 * iConst0) - 1)) & 8191));
	iConst48 = int((int(((0.009800000000000001 * iConst0) - 1)) & 8191));
	fConst49 = tan((5026.548245743669 / double(iConst0)));
	fConst50 = (2 * (1 - (1.0 / faustpower<2>(fConst49))));
	fConst51 = (1.0 / fConst49);
	fConst52 = (1 + ((fConst51 - 1.414213562373095) / fConst49));
	fConst53 = (1.0 / (1 + ((1.414213562373095 + fConst51) / fConst49)));
	fConst54 = tan((2513.2741228718346 / double(iConst0)));
	fConst55 = (1.0 / faustpower<2>(fConst54));
	fConst56 = (2 * (1 - fConst55));
	fConst57 = (1.0 / fConst54);
	fConst58 = (1 + ((fConst57 - 1.414213562373095) / fConst54));
	fConst59 = (1.0 / (1 + ((1.414213562373095 + fConst57) / fConst54)));
	fConst60 = (2 * (0 - fConst55));
	iConst61 = int((0.024 * iConst0));
	iConst62 = int((int(((0.066 * iConst0) - 1)) & 8191));
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
#define fslider2 (*fslider2_)
#define fslider3 (*fslider3_)
#define fcheckbox0 (*fcheckbox0_)
	double 	fSlow0 = (fConst8 * double(fslider0));
	int 	iSlow1 = int(fSlow0);
	int 	iSlow2 = (1 + iSlow1);
	int 	iSlow3 = int((int(iSlow2) & 65535));
	double 	fSlow4 = (fSlow0 - iSlow1);
	int 	iSlow5 = int((iSlow1 & 65535));
	double 	fSlow6 = (iSlow2 - fSlow0);
	double 	fSlow7 = double(fslider1);
	double 	fSlow8 = (0.5 * fSlow7);
	double 	fSlow9 = (1.799 * fSlow7);
	double 	fSlow10 = (0.4 * fSlow7);
	double 	fSlow11 = (fConst53 * fSlow7);
	double 	fSlow12 = double(fslider2);
	int 	iSlow13 = int((1 + fSlow12));
	double 	fSlow14 = floor(fSlow12);
	double 	fSlow15 = (fSlow12 - fSlow14);
	int 	iSlow16 = int(fSlow12);
	double 	fSlow17 = ((1 + fSlow14) - fSlow12);
	double 	fSlow18 = double(fslider3);
	double 	fSlow19 = (1 - fSlow18);
	int 	iSlow20 = int(double(fcheckbox0));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fVec0[IOTA&65535] = fTemp0;
		double fTemp1 = ((fSlow6 * fVec0[(IOTA-iSlow5)&65535]) + (fSlow4 * fVec0[(IOTA-iSlow3)&65535]));
		fRec17[0] = (fTemp1 - (fConst7 * ((fConst6 * fRec17[2]) + (fConst2 * fRec17[1]))));
		fRec16[0] = ((fConst7 * (fRec17[2] + (fRec17[0] + (2 * fRec17[1])))) - (fConst5 * ((fConst4 * fRec16[2]) + (fConst2 * fRec16[1]))));
		double 	fRec20 = (fSlow8 * fRec0[1]);
		fRec19[0] = (fRec20 - (fConst20 * ((fConst19 * fRec19[2]) + (fConst17 * fRec19[1]))));
		fRec18[0] = ((fConst20 * (((fConst16 * fRec19[0]) + (fConst21 * fRec19[1])) + (fConst16 * fRec19[2]))) - (fConst14 * ((fConst12 * fRec18[2]) + (fConst10 * fRec18[1]))));
		double fTemp2 = (((fConst22 * (fRec18[2] + (fRec18[0] + (2 * fRec18[1])))) + (fConst5 * (fRec16[2] + (fRec16[0] + (2 * fRec16[1]))))) - (0.3 * fRec14[1]));
		fVec1[IOTA&8191] = fTemp2;
		fRec14[0] = fVec1[(IOTA-iConst23)&8191];
		double 	fRec15 = (0.3 * fVec1[IOTA&8191]);
		double fTemp3 = ((fRec15 + fRec14[1]) - (0.3 * fRec12[1]));
		fVec2[IOTA&8191] = fTemp3;
		fRec12[0] = fVec2[(IOTA-iConst24)&8191];
		double 	fRec13 = (0.3 * fVec2[IOTA&8191]);
		double fTemp4 = (fRec13 + fRec12[1]);
		fVec3[IOTA&4095] = fTemp4;
		double fTemp5 = (fVec3[(IOTA-iConst26)&4095] - (0.5 * fRec8[1]));
		fVec4[IOTA&8191] = fTemp5;
		double fTemp6 = (fVec4[(IOTA-iConst27)&8191] - (0.25 * fRec10[1]));
		fVec5[IOTA&8191] = fTemp6;
		fRec10[0] = fVec5[(IOTA-iConst28)&8191];
		double 	fRec11 = (0.25 * fVec5[IOTA&8191]);
		fRec8[0] = (fRec11 + fRec10[1]);
		double 	fRec9 = (0.5 * fVec4[IOTA&8191]);
		double fTemp7 = (fRec9 + fRec8[1]);
		fVec6[IOTA&8191] = fTemp7;
		double fTemp8 = (fVec6[(IOTA-iConst30)&8191] - (0.5 * fRec2[1]));
		fVec7[IOTA&8191] = fTemp8;
		double fTemp9 = (fVec7[(IOTA-iConst31)&8191] - (0.25 * fRec4[1]));
		fVec8[IOTA&8191] = fTemp9;
		double fTemp10 = (fVec8[(IOTA-iConst32)&8191] - (0.25 * fRec6[1]));
		fVec9[IOTA&8191] = fTemp10;
		fRec6[0] = fVec9[(IOTA-iConst33)&8191];
		double 	fRec7 = (0.25 * fVec9[IOTA&8191]);
		fRec4[0] = (fRec7 + fRec6[1]);
		double 	fRec5 = (0.25 * fVec8[IOTA&8191]);
		fRec2[0] = (fRec5 + fRec4[1]);
		double 	fRec3 = (0.5 * fVec7[IOTA&8191]);
		fRec0[0] = (fRec3 + fRec2[1]);
		double 	fRec1 = ((0.8 * fVec6[(IOTA-iConst29)&8191]) + (1.5 * fVec3[(IOTA-iConst25)&4095]));
		double fTemp11 = (fRec0[0] + (0.8 * fRec1));
		fRec37[0] = (fRec21[1] - (fConst20 * ((fConst19 * fRec37[2]) + (fConst17 * fRec37[1]))));
		fRec36[0] = ((fConst20 * (((fConst16 * fRec37[0]) + (fConst21 * fRec37[1])) + (fConst16 * fRec37[2]))) - (fConst14 * ((fConst12 * fRec36[2]) + (fConst10 * fRec36[1]))));
		double 	fRec35 = (fConst14 * (fRec36[2] + (fRec36[0] + (2 * fRec36[1]))));
		fRec39[0] = (fTemp1 - (fConst40 * ((fConst39 * fRec39[2]) + (fConst35 * fRec39[1]))));
		fRec38[0] = ((fConst40 * (fRec39[2] + (fRec39[0] + (2 * fRec39[1])))) - (fConst38 * ((fConst37 * fRec38[2]) + (fConst35 * fRec38[1]))));
		double fTemp12 = (fConst38 * (fRec38[2] + (fRec38[0] + (2 * fRec38[1]))));
		double fTemp13 = ((fTemp12 + (fSlow9 * fRec35)) - (0.25 * fRec29[1]));
		fVec10[IOTA&8191] = fTemp13;
		double fTemp14 = (fVec10[(IOTA-iConst41)&8191] - (0.35 * fRec31[1]));
		fVec11[IOTA&8191] = fTemp14;
		double fTemp15 = (fVec11[(IOTA-iConst42)&8191] - (0.45 * fRec33[1]));
		fVec12[IOTA&8191] = fTemp15;
		fRec33[0] = fVec12[(IOTA-iConst43)&8191];
		double 	fRec34 = (0.45 * fVec12[IOTA&8191]);
		fRec31[0] = (fRec34 + fRec33[1]);
		double 	fRec32 = (0.35 * fVec11[IOTA&8191]);
		fRec29[0] = (fRec32 + fRec31[1]);
		double 	fRec30 = (0.25 * fVec10[IOTA&8191]);
		double fTemp16 = (fRec30 + fRec29[1]);
		fVec13[IOTA&1023] = fTemp16;
		double fTemp17 = (fVec13[(IOTA-iConst44)&1023] - (0.45 * fRec27[1]));
		fVec14[IOTA&8191] = fTemp17;
		fRec27[0] = fVec14[(IOTA-iConst33)&8191];
		double 	fRec28 = (0.45 * fVec14[IOTA&8191]);
		double fTemp18 = (fRec28 + fRec27[1]);
		fVec15[IOTA&16383] = fTemp18;
		double fTemp19 = ((fTemp1 + (fSlow10 * fVec15[(IOTA-iConst46)&16383])) - (0.25 * fRec23[1]));
		fVec16[IOTA&8191] = fTemp19;
		double fTemp20 = (fVec16[(IOTA-iConst47)&8191] - (0.35 * fRec25[1]));
		fVec17[IOTA&8191] = fTemp20;
		fRec25[0] = fVec17[(IOTA-iConst48)&8191];
		double 	fRec26 = (0.35 * fVec17[IOTA&8191]);
		fRec23[0] = (fRec26 + fRec25[1]);
		double 	fRec24 = (0.25 * fVec16[IOTA&8191]);
		fRec21[0] = (fRec24 + fRec23[1]);
		double 	fRec22 = (0.5 * (fVec13[IOTA&1023] + fVec15[(IOTA-iConst45)&16383]));
		double fTemp21 = (fRec22 + (0.5 * fRec21[0]));
		fRec54[0] = ((1.199 * fRec40[1]) - (fConst59 * ((fConst58 * fRec54[2]) + (fConst56 * fRec54[1]))));
		fRec53[0] = ((fConst59 * (((fConst55 * fRec54[0]) + (fConst60 * fRec54[1])) + (fConst55 * fRec54[2]))) - (fConst53 * ((fConst52 * fRec53[2]) + (fConst50 * fRec53[1]))));
		double 	fRec52 = (fSlow11 * (fRec53[2] + (fRec53[0] + (2 * fRec53[1]))));
		fVec18[IOTA&8191] = (fRec52 + fTemp12);
		double fTemp22 = (fVec18[(IOTA-iConst61)&8191] - (0.15 * fRec46[1]));
		fVec19[IOTA&8191] = fTemp22;
		double fTemp23 = (fVec19[(IOTA-iConst41)&8191] - (0.25 * fRec48[1]));
		fVec20[IOTA&8191] = fTemp23;
		double fTemp24 = (fVec20[(IOTA-iConst43)&8191] - (0.3 * fRec50[1]));
		fVec21[IOTA&8191] = fTemp24;
		fRec50[0] = fVec21[(IOTA-iConst42)&8191];
		double 	fRec51 = (0.3 * fVec21[IOTA&8191]);
		fRec48[0] = (fRec51 + fRec50[1]);
		double 	fRec49 = (0.25 * fVec20[IOTA&8191]);
		fRec46[0] = (fRec49 + fRec48[1]);
		double 	fRec47 = (0.15 * fVec19[IOTA&8191]);
		double fTemp25 = (fRec47 + fRec46[1]);
		double fTemp26 = (fTemp25 - (0.08 * fRec42[1]));
		fVec22[IOTA&8191] = fTemp26;
		double fTemp27 = (fVec22[(IOTA-iConst62)&8191] - (0.3 * fRec44[1]));
		fVec23[IOTA&8191] = fTemp27;
		fRec44[0] = fVec23[(IOTA-iConst33)&8191];
		double 	fRec45 = (0.3 * fVec23[IOTA&8191]);
		fRec42[0] = (fRec45 + fRec44[1]);
		double 	fRec43 = (0.08 * fVec22[IOTA&8191]);
		fRec40[0] = (fRec43 + fRec42[1]);
		double 	fRec41 = fTemp25;
		double fTemp28 = (0.5 * (fRec40[0] + fRec41));
		output0[i] = (FAUSTFLOAT)((iSlow20)?((fSlow19 * fVec0[IOTA&65535]) + (fSlow18 * ((fSlow17 * ((iSlow16==0)? fTemp28 : ((iSlow16==1)?fTemp21:fTemp11) )) + (fSlow15 * ((iSlow13==0)? fTemp28 : ((iSlow13==1)?fTemp21:fTemp11) ))))):fVec0[IOTA&65535]);
		// post processing
		fRec40[1] = fRec40[0];
		fRec42[1] = fRec42[0];
		fRec44[1] = fRec44[0];
		fRec46[1] = fRec46[0];
		fRec48[1] = fRec48[0];
		fRec50[1] = fRec50[0];
		fRec53[2] = fRec53[1]; fRec53[1] = fRec53[0];
		fRec54[2] = fRec54[1]; fRec54[1] = fRec54[0];
		fRec21[1] = fRec21[0];
		fRec23[1] = fRec23[0];
		fRec25[1] = fRec25[0];
		fRec27[1] = fRec27[0];
		fRec29[1] = fRec29[0];
		fRec31[1] = fRec31[0];
		fRec33[1] = fRec33[0];
		fRec38[2] = fRec38[1]; fRec38[1] = fRec38[0];
		fRec39[2] = fRec39[1]; fRec39[1] = fRec39[0];
		fRec36[2] = fRec36[1]; fRec36[1] = fRec36[0];
		fRec37[2] = fRec37[1]; fRec37[1] = fRec37[0];
		fRec0[1] = fRec0[0];
		fRec2[1] = fRec2[0];
		fRec4[1] = fRec4[0];
		fRec6[1] = fRec6[0];
		fRec8[1] = fRec8[0];
		fRec10[1] = fRec10[0];
		fRec12[1] = fRec12[0];
		fRec14[1] = fRec14[0];
		fRec18[2] = fRec18[1]; fRec18[1] = fRec18[0];
		fRec19[2] = fRec19[1]; fRec19[1] = fRec19[0];
		fRec16[2] = fRec16[1]; fRec16[1] = fRec16[0];
		fRec17[2] = fRec17[1]; fRec17[1] = fRec17[0];
		IOTA = IOTA+1;
	}
#undef fslider0
#undef fslider1
#undef fslider2
#undef fslider3
#undef fcheckbox0
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case EFFECT: 
		fcheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case PREDELAYMS: 
		fslider0_ = (float*)data; // , 2e+01, 1.0, 2e+02, 1.0 
		break;
	case RT: 
		fslider1_ = (float*)data; // , 0.3, 0.0, 1.0, 0.05 
		break;
	case ROOMSIZE: 
		fslider2_ = (float*)data; // , 1.0, 0.0, 3.0, 0.05 
		break;
	case DRYWET: 
		fslider3_ = (float*)data; // , 0.5, 0.0, 1.0, 0.05 
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
   EFFECT, 
   PREDELAYMS, 
   RT, 
   ROOMSIZE, 
   DRYWET, 
} PortIndex;
*/

} // end namespace room_simulator
