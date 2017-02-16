// generated from file '../src/LV2/faust/gx_zita_rev1.dsp' by dsp2cc:
// Code generated with Faust 0.9.73 (http://faust.grame.fr)


namespace gx_zita_rev1 {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec0[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec1[2];
	int 	IOTA;
	double 	fVec0[8192];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	int 	iConst0;
	double 	fConst1;
	double 	fRec13[2];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fConst2;
	double 	fConst3;
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT	*fslider4_;
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT	*fslider5_;
	double 	fConst4;
	double 	fRec12[2];
	double 	fVec1[8192];
	double 	fConst5;
	int 	iConst6;
	FAUSTFLOAT 	fslider6;
	FAUSTFLOAT	*fslider6_;
	double 	fConst7;
	double 	fVec2[2048];
	int 	iConst8;
	double 	fRec10[2];
	double 	fRec17[2];
	double 	fConst9;
	double 	fConst10;
	double 	fRec16[2];
	double 	fVec3[8192];
	double 	fConst11;
	int 	iConst12;
	double 	fVec4[1024];
	int 	iConst13;
	double 	fRec14[2];
	double 	fRec21[2];
	double 	fConst14;
	double 	fConst15;
	double 	fRec20[2];
	double 	fVec5[8192];
	double 	fConst16;
	int 	iConst17;
	double 	fVec6[2048];
	int 	iConst18;
	double 	fRec18[2];
	double 	fRec25[2];
	double 	fConst19;
	double 	fConst20;
	double 	fRec24[2];
	double 	fVec7[8192];
	double 	fConst21;
	int 	iConst22;
	double 	fVec8[1024];
	int 	iConst23;
	double 	fRec22[2];
	double 	fRec29[2];
	double 	fConst24;
	double 	fConst25;
	double 	fRec28[2];
	double 	fVec9[16384];
	double 	fConst26;
	int 	iConst27;
	double 	fVec10[8192];
	double 	fVec11[2048];
	int 	iConst28;
	double 	fRec26[2];
	double 	fRec33[2];
	double 	fConst29;
	double 	fConst30;
	double 	fRec32[2];
	double 	fVec12[8192];
	double 	fConst31;
	int 	iConst32;
	double 	fVec13[2048];
	int 	iConst33;
	double 	fRec30[2];
	double 	fRec37[2];
	double 	fConst34;
	double 	fConst35;
	double 	fRec36[2];
	double 	fVec14[16384];
	double 	fConst36;
	int 	iConst37;
	double 	fVec15[2048];
	int 	iConst38;
	double 	fRec34[2];
	double 	fRec41[2];
	double 	fConst39;
	double 	fConst40;
	double 	fRec40[2];
	double 	fVec16[16384];
	double 	fConst41;
	int 	iConst42;
	double 	fVec17[1024];
	int 	iConst43;
	double 	fRec38[2];
	double 	fRec2[3];
	double 	fRec3[3];
	double 	fRec4[3];
	double 	fRec5[3];
	double 	fRec6[3];
	double 	fRec7[3];
	double 	fRec8[3];
	double 	fRec9[3];
	FAUSTFLOAT 	fslider7;
	FAUSTFLOAT	*fslider7_;
	FAUSTFLOAT 	fslider8;
	FAUSTFLOAT	*fslider8_;
	double 	fConst44;
	double 	fRec42[3];
	FAUSTFLOAT 	fslider9;
	FAUSTFLOAT	*fslider9_;
	FAUSTFLOAT 	fslider10;
	FAUSTFLOAT	*fslider10_;
	double 	fRec43[3];
	double 	fRec44[3];
	double 	fRec45[3];
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



static const char* parm_groups[] = {
	"decay_times", N_("Decay Times in Bands"),
	"equalizer1", N_("RM Peaking Equalizer 1"),
	"equalizer2", N_("RM Peaking Equalizer 2"),
	"input", N_("Input"),
	"output", N_("Output"),
	0
	};

Dsp::Dsp()
	: PluginLV2() {
	version = PLUGINLV2_VERSION;
	id = "zita_rev1";
	name = N_("Zita Rev1");
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
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<8192; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<8192; i++) fVec1[i] = 0;
	for (int i=0; i<2048; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<8192; i++) fVec3[i] = 0;
	for (int i=0; i<1024; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<8192; i++) fVec5[i] = 0;
	for (int i=0; i<2048; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fRec25[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<8192; i++) fVec7[i] = 0;
	for (int i=0; i<1024; i++) fVec8[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fRec29[i] = 0;
	for (int i=0; i<2; i++) fRec28[i] = 0;
	for (int i=0; i<16384; i++) fVec9[i] = 0;
	for (int i=0; i<8192; i++) fVec10[i] = 0;
	for (int i=0; i<2048; i++) fVec11[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<2; i++) fRec33[i] = 0;
	for (int i=0; i<2; i++) fRec32[i] = 0;
	for (int i=0; i<8192; i++) fVec12[i] = 0;
	for (int i=0; i<2048; i++) fVec13[i] = 0;
	for (int i=0; i<2; i++) fRec30[i] = 0;
	for (int i=0; i<2; i++) fRec37[i] = 0;
	for (int i=0; i<2; i++) fRec36[i] = 0;
	for (int i=0; i<16384; i++) fVec14[i] = 0;
	for (int i=0; i<2048; i++) fVec15[i] = 0;
	for (int i=0; i<2; i++) fRec34[i] = 0;
	for (int i=0; i<2; i++) fRec41[i] = 0;
	for (int i=0; i<2; i++) fRec40[i] = 0;
	for (int i=0; i<16384; i++) fVec16[i] = 0;
	for (int i=0; i<1024; i++) fVec17[i] = 0;
	for (int i=0; i<2; i++) fRec38[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<3; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec4[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<3; i++) fRec7[i] = 0;
	for (int i=0; i<3; i++) fRec8[i] = 0;
	for (int i=0; i<3; i++) fRec9[i] = 0;
	for (int i=0; i<3; i++) fRec42[i] = 0;
	for (int i=0; i<3; i++) fRec43[i] = 0;
	for (int i=0; i<3; i++) fRec44[i] = 0;
	for (int i=0; i<3; i++) fRec45[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	IOTA = 0;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (3.141592653589793 / double(iConst0));
	fConst2 = floor((0.5 + (0.174713 * iConst0)));
	fConst3 = ((0 - (6.907755278982138 * fConst2)) / double(iConst0));
	fConst4 = (6.283185307179586 / double(iConst0));
	fConst5 = floor((0.5 + (0.022904 * iConst0)));
	iConst6 = int((int((fConst2 - fConst5)) & 8191));
	fConst7 = (0.001 * iConst0);
	iConst8 = int((int((fConst5 - 1)) & 2047));
	fConst9 = floor((0.5 + (0.153129 * iConst0)));
	fConst10 = ((0 - (6.907755278982138 * fConst9)) / double(iConst0));
	fConst11 = floor((0.5 + (0.020346 * iConst0)));
	iConst12 = int((int((fConst9 - fConst11)) & 8191));
	iConst13 = int((int((fConst11 - 1)) & 1023));
	fConst14 = floor((0.5 + (0.127837 * iConst0)));
	fConst15 = ((0 - (6.907755278982138 * fConst14)) / double(iConst0));
	fConst16 = floor((0.5 + (0.031604 * iConst0)));
	iConst17 = int((int((fConst14 - fConst16)) & 8191));
	iConst18 = int((int((fConst16 - 1)) & 2047));
	fConst19 = floor((0.5 + (0.125 * iConst0)));
	fConst20 = ((0 - (6.907755278982138 * fConst19)) / double(iConst0));
	fConst21 = floor((0.5 + (0.013458 * iConst0)));
	iConst22 = int((int((fConst19 - fConst21)) & 8191));
	iConst23 = int((int((fConst21 - 1)) & 1023));
	fConst24 = floor((0.5 + (0.210389 * iConst0)));
	fConst25 = ((0 - (6.907755278982138 * fConst24)) / double(iConst0));
	fConst26 = floor((0.5 + (0.024421 * iConst0)));
	iConst27 = int((int((fConst24 - fConst26)) & 16383));
	iConst28 = int((int((fConst26 - 1)) & 2047));
	fConst29 = floor((0.5 + (0.192303 * iConst0)));
	fConst30 = ((0 - (6.907755278982138 * fConst29)) / double(iConst0));
	fConst31 = floor((0.5 + (0.029291 * iConst0)));
	iConst32 = int((int((fConst29 - fConst31)) & 8191));
	iConst33 = int((int((fConst31 - 1)) & 2047));
	fConst34 = floor((0.5 + (0.256891 * iConst0)));
	fConst35 = ((0 - (6.907755278982138 * fConst34)) / double(iConst0));
	fConst36 = floor((0.5 + (0.027333 * iConst0)));
	iConst37 = int((int((fConst34 - fConst36)) & 16383));
	iConst38 = int((int((fConst36 - 1)) & 2047));
	fConst39 = floor((0.5 + (0.219991 * iConst0)));
	fConst40 = ((0 - (6.907755278982138 * fConst39)) / double(iConst0));
	fConst41 = floor((0.5 + (0.019123 * iConst0)));
	iConst42 = int((int((fConst39 - fConst41)) & 16383));
	iConst43 = int((int((fConst41 - 1)) & 1023));
	fConst44 = (6.283185307179586 / double(iConst0));
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
#define fslider2 (*fslider2_)
#define fslider3 (*fslider3_)
#define fslider4 (*fslider4_)
#define fslider5 (*fslider5_)
#define fslider6 (*fslider6_)
#define fslider7 (*fslider7_)
#define fslider8 (*fslider8_)
#define fslider9 (*fslider9_)
#define fslider10 (*fslider10_)
	double 	fSlow0 = (0.0010000000000000009 * double(fslider0));
	double 	fSlow1 = (0.0010000000000000009 * double(fslider1));
	double 	fSlow2 = (1.0 / tan((fConst1 * double(fslider2))));
	double 	fSlow3 = (1 + fSlow2);
	double 	fSlow4 = (1.0 / fSlow3);
	double 	fSlow5 = (0 - ((1 - fSlow2) / fSlow3));
	double 	fSlow6 = double(fslider3);
	double 	fSlow7 = exp((fConst3 / fSlow6));
	double 	fSlow8 = double(fslider4);
	double 	fSlow9 = ((exp((fConst3 / fSlow8)) / fSlow7) - 1);
	double 	fSlow10 = faustpower<2>(fSlow7);
	double 	fSlow11 = (1.0 - fSlow10);
	double 	fSlow12 = cos((fConst4 * double(fslider5)));
	double 	fSlow13 = (1.0 - (fSlow12 * fSlow10));
	double 	fSlow14 = (fSlow13 / fSlow11);
	double 	fSlow15 = sqrt(max((double)0, ((faustpower<2>(fSlow13) / faustpower<2>(fSlow11)) - 1.0)));
	double 	fSlow16 = (fSlow7 * ((1.0 + fSlow15) - fSlow14));
	double 	fSlow17 = (fSlow14 - fSlow15);
	int 	iSlow18 = int((int((fConst7 * double(fslider6))) & 8191));
	double 	fSlow19 = exp((fConst10 / fSlow6));
	double 	fSlow20 = ((exp((fConst10 / fSlow8)) / fSlow19) - 1);
	double 	fSlow21 = faustpower<2>(fSlow19);
	double 	fSlow22 = (1.0 - fSlow21);
	double 	fSlow23 = (1.0 - (fSlow12 * fSlow21));
	double 	fSlow24 = (fSlow23 / fSlow22);
	double 	fSlow25 = sqrt(max((double)0, ((faustpower<2>(fSlow23) / faustpower<2>(fSlow22)) - 1.0)));
	double 	fSlow26 = (fSlow19 * ((1.0 + fSlow25) - fSlow24));
	double 	fSlow27 = (fSlow24 - fSlow25);
	double 	fSlow28 = exp((fConst15 / fSlow6));
	double 	fSlow29 = ((exp((fConst15 / fSlow8)) / fSlow28) - 1);
	double 	fSlow30 = faustpower<2>(fSlow28);
	double 	fSlow31 = (1.0 - fSlow30);
	double 	fSlow32 = (1.0 - (fSlow12 * fSlow30));
	double 	fSlow33 = (fSlow32 / fSlow31);
	double 	fSlow34 = sqrt(max((double)0, ((faustpower<2>(fSlow32) / faustpower<2>(fSlow31)) - 1.0)));
	double 	fSlow35 = (fSlow28 * ((1.0 + fSlow34) - fSlow33));
	double 	fSlow36 = (fSlow33 - fSlow34);
	double 	fSlow37 = exp((fConst20 / fSlow6));
	double 	fSlow38 = ((exp((fConst20 / fSlow8)) / fSlow37) - 1);
	double 	fSlow39 = faustpower<2>(fSlow37);
	double 	fSlow40 = (1.0 - fSlow39);
	double 	fSlow41 = (1.0 - (fSlow12 * fSlow39));
	double 	fSlow42 = (fSlow41 / fSlow40);
	double 	fSlow43 = sqrt(max((double)0, ((faustpower<2>(fSlow41) / faustpower<2>(fSlow40)) - 1.0)));
	double 	fSlow44 = (fSlow37 * ((1.0 + fSlow43) - fSlow42));
	double 	fSlow45 = (fSlow42 - fSlow43);
	double 	fSlow46 = exp((fConst25 / fSlow6));
	double 	fSlow47 = ((exp((fConst25 / fSlow8)) / fSlow46) - 1);
	double 	fSlow48 = faustpower<2>(fSlow46);
	double 	fSlow49 = (1.0 - fSlow48);
	double 	fSlow50 = (1.0 - (fSlow12 * fSlow48));
	double 	fSlow51 = (fSlow50 / fSlow49);
	double 	fSlow52 = sqrt(max((double)0, ((faustpower<2>(fSlow50) / faustpower<2>(fSlow49)) - 1.0)));
	double 	fSlow53 = (fSlow46 * ((1.0 + fSlow52) - fSlow51));
	double 	fSlow54 = (fSlow51 - fSlow52);
	double 	fSlow55 = exp((fConst30 / fSlow6));
	double 	fSlow56 = ((exp((fConst30 / fSlow8)) / fSlow55) - 1);
	double 	fSlow57 = faustpower<2>(fSlow55);
	double 	fSlow58 = (1.0 - fSlow57);
	double 	fSlow59 = (1.0 - (fSlow12 * fSlow57));
	double 	fSlow60 = (fSlow59 / fSlow58);
	double 	fSlow61 = sqrt(max((double)0, ((faustpower<2>(fSlow59) / faustpower<2>(fSlow58)) - 1.0)));
	double 	fSlow62 = (fSlow55 * ((1.0 + fSlow61) - fSlow60));
	double 	fSlow63 = (fSlow60 - fSlow61);
	double 	fSlow64 = exp((fConst35 / fSlow6));
	double 	fSlow65 = ((exp((fConst35 / fSlow8)) / fSlow64) - 1);
	double 	fSlow66 = faustpower<2>(fSlow64);
	double 	fSlow67 = (1.0 - fSlow66);
	double 	fSlow68 = (1.0 - (fSlow12 * fSlow66));
	double 	fSlow69 = (fSlow68 / fSlow67);
	double 	fSlow70 = sqrt(max((double)0, ((faustpower<2>(fSlow68) / faustpower<2>(fSlow67)) - 1.0)));
	double 	fSlow71 = (fSlow64 * ((1.0 + fSlow70) - fSlow69));
	double 	fSlow72 = (fSlow69 - fSlow70);
	double 	fSlow73 = exp((fConst40 / fSlow6));
	double 	fSlow74 = ((exp((fConst40 / fSlow8)) / fSlow73) - 1);
	double 	fSlow75 = faustpower<2>(fSlow73);
	double 	fSlow76 = (1.0 - fSlow75);
	double 	fSlow77 = (1.0 - (fSlow75 * fSlow12));
	double 	fSlow78 = (fSlow77 / fSlow76);
	double 	fSlow79 = sqrt(max((double)0, ((faustpower<2>(fSlow77) / faustpower<2>(fSlow76)) - 1.0)));
	double 	fSlow80 = (fSlow73 * ((1.0 + fSlow79) - fSlow78));
	double 	fSlow81 = (fSlow78 - fSlow79);
	double 	fSlow82 = pow(10,(0.05 * double(fslider7)));
	double 	fSlow83 = double(fslider8);
	double 	fSlow84 = (fConst44 * (fSlow83 / sqrt(fSlow82)));
	double 	fSlow85 = ((1.0 - fSlow84) / (1.0 + fSlow84));
	double 	fSlow86 = ((0 - cos((fConst44 * fSlow83))) * (1 + fSlow85));
	double 	fSlow87 = pow(10,(0.05 * double(fslider9)));
	double 	fSlow88 = double(fslider10);
	double 	fSlow89 = (fConst44 * (fSlow88 / sqrt(fSlow87)));
	double 	fSlow90 = ((1.0 - fSlow89) / (1.0 + fSlow89));
	double 	fSlow91 = ((0 - cos((fConst44 * fSlow88))) * (1 + fSlow90));
	for (int i=0; i<count; i++) {
		fRec0[0] = ((0.999 * fRec0[1]) + fSlow0);
		double fTemp0 = pow(10,(0.05 * fRec0[0]));
		fRec1[0] = ((0.999 * fRec1[1]) + fSlow1);
		double fTemp1 = (1.0 + fRec1[0]);
		double fTemp2 = (1.0 - (0.5 * fTemp1));
		double fTemp3 = (double)input0[i];
		fVec0[IOTA&8191] = fTemp3;
		fRec13[0] = ((fSlow5 * fRec13[1]) + (fSlow4 * (fRec6[1] + fRec6[2])));
		fRec12[0] = ((fSlow17 * fRec12[1]) + (fSlow16 * (fRec6[1] + (fSlow9 * fRec13[0]))));
		fVec1[IOTA&8191] = (1e-20 + (0.35355339059327373 * fRec12[0]));
		double fTemp4 = (0.3 * fVec0[(IOTA-iSlow18)&8191]);
		double fTemp5 = ((fTemp4 + fVec1[(IOTA-iConst6)&8191]) - (0.6 * fRec10[1]));
		fVec2[IOTA&2047] = fTemp5;
		fRec10[0] = fVec2[(IOTA-iConst8)&2047];
		double 	fRec11 = (0.6 * fVec2[IOTA&2047]);
		fRec17[0] = ((fSlow5 * fRec17[1]) + (fSlow4 * (fRec2[1] + fRec2[2])));
		fRec16[0] = ((fSlow27 * fRec16[1]) + (fSlow26 * (fRec2[1] + (fSlow20 * fRec17[0]))));
		fVec3[IOTA&8191] = (1e-20 + (0.35355339059327373 * fRec16[0]));
		double fTemp6 = ((fVec3[(IOTA-iConst12)&8191] + fTemp4) - (0.6 * fRec14[1]));
		fVec4[IOTA&1023] = fTemp6;
		fRec14[0] = fVec4[(IOTA-iConst13)&1023];
		double 	fRec15 = (0.6 * fVec4[IOTA&1023]);
		double fTemp7 = (fRec15 + fRec11);
		fRec21[0] = ((fSlow5 * fRec21[1]) + (fSlow4 * (fRec4[1] + fRec4[2])));
		fRec20[0] = ((fSlow36 * fRec20[1]) + (fSlow35 * (fRec4[1] + (fSlow29 * fRec21[0]))));
		fVec5[IOTA&8191] = (1e-20 + (0.35355339059327373 * fRec20[0]));
		double fTemp8 = (fVec5[(IOTA-iConst17)&8191] - (fTemp4 + (0.6 * fRec18[1])));
		fVec6[IOTA&2047] = fTemp8;
		fRec18[0] = fVec6[(IOTA-iConst18)&2047];
		double 	fRec19 = (0.6 * fVec6[IOTA&2047]);
		fRec25[0] = ((fSlow5 * fRec25[1]) + (fSlow4 * (fRec8[1] + fRec8[2])));
		fRec24[0] = ((fSlow45 * fRec24[1]) + (fSlow44 * (fRec8[1] + (fSlow38 * fRec25[0]))));
		fVec7[IOTA&8191] = (1e-20 + (0.35355339059327373 * fRec24[0]));
		double fTemp9 = (fVec7[(IOTA-iConst22)&8191] - (fTemp4 + (0.6 * fRec22[1])));
		fVec8[IOTA&1023] = fTemp9;
		fRec22[0] = fVec8[(IOTA-iConst23)&1023];
		double 	fRec23 = (0.6 * fVec8[IOTA&1023]);
		double fTemp10 = (fRec23 + (fRec19 + fTemp7));
		fRec29[0] = ((fSlow5 * fRec29[1]) + (fSlow4 * (fRec3[1] + fRec3[2])));
		fRec28[0] = ((fSlow54 * fRec28[1]) + (fSlow53 * (fRec3[1] + (fSlow47 * fRec29[0]))));
		fVec9[IOTA&16383] = (1e-20 + (0.35355339059327373 * fRec28[0]));
		double fTemp11 = (double)input1[i];
		fVec10[IOTA&8191] = fTemp11;
		double fTemp12 = (0.3 * fVec10[(IOTA-iSlow18)&8191]);
		double fTemp13 = (fTemp12 + ((0.6 * fRec26[1]) + fVec9[(IOTA-iConst27)&16383]));
		fVec11[IOTA&2047] = fTemp13;
		fRec26[0] = fVec11[(IOTA-iConst28)&2047];
		double 	fRec27 = (0 - (0.6 * fVec11[IOTA&2047]));
		fRec33[0] = ((fSlow5 * fRec33[1]) + (fSlow4 * (fRec7[1] + fRec7[2])));
		fRec32[0] = ((fSlow63 * fRec32[1]) + (fSlow62 * (fRec7[1] + (fSlow56 * fRec33[0]))));
		fVec12[IOTA&8191] = (1e-20 + (0.35355339059327373 * fRec32[0]));
		double fTemp14 = (fVec12[(IOTA-iConst32)&8191] + (fTemp12 + (0.6 * fRec30[1])));
		fVec13[IOTA&2047] = fTemp14;
		fRec30[0] = fVec13[(IOTA-iConst33)&2047];
		double 	fRec31 = (0 - (0.6 * fVec13[IOTA&2047]));
		fRec37[0] = ((fSlow5 * fRec37[1]) + (fSlow4 * (fRec5[1] + fRec5[2])));
		fRec36[0] = ((fSlow72 * fRec36[1]) + (fSlow71 * (fRec5[1] + (fSlow65 * fRec37[0]))));
		fVec14[IOTA&16383] = (1e-20 + (0.35355339059327373 * fRec36[0]));
		double fTemp15 = (((0.6 * fRec34[1]) + fVec14[(IOTA-iConst37)&16383]) - fTemp12);
		fVec15[IOTA&2047] = fTemp15;
		fRec34[0] = fVec15[(IOTA-iConst38)&2047];
		double 	fRec35 = (0 - (0.6 * fVec15[IOTA&2047]));
		fRec41[0] = ((fSlow5 * fRec41[1]) + (fSlow4 * (fRec9[1] + fRec9[2])));
		fRec40[0] = ((fSlow81 * fRec40[1]) + (fSlow80 * (fRec9[1] + (fSlow74 * fRec41[0]))));
		fVec16[IOTA&16383] = (1e-20 + (0.35355339059327373 * fRec40[0]));
		double fTemp16 = (((0.6 * fRec38[1]) + fVec16[(IOTA-iConst42)&16383]) - fTemp12);
		fVec17[IOTA&1023] = fTemp16;
		fRec38[0] = fVec17[(IOTA-iConst43)&1023];
		double 	fRec39 = (0 - (0.6 * fVec17[IOTA&1023]));
		fRec2[0] = (fRec38[1] + (fRec34[1] + (fRec30[1] + (fRec26[1] + (fRec22[1] + (fRec18[1] + (fRec10[1] + (fRec14[1] + (fRec39 + (fRec35 + (fRec31 + (fRec27 + fTemp10))))))))))));
		fRec3[0] = (0 - ((fRec38[1] + (fRec34[1] + (fRec30[1] + (fRec26[1] + (fRec39 + (fRec35 + (fRec27 + fRec31))))))) - (fRec22[1] + (fRec18[1] + (fRec10[1] + (fRec14[1] + fTemp10))))));
		double fTemp17 = (fRec19 + fRec23);
		fRec4[0] = (0 - ((fRec38[1] + (fRec34[1] + (fRec22[1] + (fRec18[1] + (fRec39 + (fRec35 + fTemp17)))))) - (fRec30[1] + (fRec26[1] + (fRec10[1] + (fRec14[1] + (fRec31 + (fRec27 + fTemp7))))))));
		fRec5[0] = (0 - ((fRec30[1] + (fRec26[1] + (fRec22[1] + (fRec18[1] + (fRec31 + (fRec27 + fTemp17)))))) - (fRec38[1] + (fRec34[1] + (fRec10[1] + (fRec14[1] + (fRec39 + (fRec35 + fTemp7))))))));
		double fTemp18 = (fRec15 + fRec19);
		double fTemp19 = (fRec11 + fRec23);
		fRec6[0] = (0 - ((fRec38[1] + (fRec30[1] + (fRec22[1] + (fRec10[1] + (fRec39 + (fRec31 + fTemp19)))))) - (fRec34[1] + (fRec26[1] + (fRec18[1] + (fRec14[1] + (fRec35 + (fRec27 + fTemp18))))))));
		fRec7[0] = (0 - ((fRec34[1] + (fRec26[1] + (fRec22[1] + (fRec10[1] + (fRec35 + (fRec27 + fTemp19)))))) - (fRec38[1] + (fRec30[1] + (fRec18[1] + (fRec14[1] + (fRec39 + (fRec31 + fTemp18))))))));
		double fTemp20 = (fRec15 + fRec23);
		double fTemp21 = (fRec11 + fRec19);
		fRec8[0] = (0 - ((fRec34[1] + (fRec30[1] + (fRec18[1] + (fRec10[1] + (fRec35 + (fRec31 + fTemp21)))))) - (fRec38[1] + (fRec26[1] + (fRec22[1] + (fRec14[1] + (fRec39 + (fRec27 + fTemp20))))))));
		fRec9[0] = (0 - ((fRec38[1] + (fRec26[1] + (fRec18[1] + (fRec10[1] + (fRec39 + (fRec27 + fTemp21)))))) - (fRec34[1] + (fRec30[1] + (fRec22[1] + (fRec14[1] + (fRec35 + (fRec31 + fTemp20))))))));
		double fTemp22 = (0.37 * (fRec3[0] + fRec4[0]));
		double fTemp23 = (fSlow86 * fRec42[1]);
		fRec42[0] = (0 - ((fTemp23 + (fSlow85 * fRec42[2])) - fTemp22));
		double fTemp24 = (fSlow85 * fRec42[0]);
		double fTemp25 = (0.5 * ((fTemp24 + (fRec42[2] + (fTemp22 + fTemp23))) + (fSlow82 * ((fTemp24 + (fTemp23 + fRec42[2])) - fTemp22))));
		double fTemp26 = (fSlow91 * fRec43[1]);
		fRec43[0] = (0 - ((fTemp26 + (fSlow90 * fRec43[2])) - fTemp25));
		double fTemp27 = (fSlow90 * fRec43[0]);
		output0[i] = (FAUSTFLOAT)(((0.25 * (((fTemp27 + (fRec43[2] + (fTemp25 + fTemp26))) + (fSlow87 * ((fTemp27 + (fTemp26 + fRec43[2])) - fTemp25))) * fTemp1)) + (fVec0[IOTA&8191] * fTemp2)) * fTemp0);
		double fTemp28 = (0.37 * (fRec3[0] - fRec4[0]));
		double fTemp29 = (fSlow86 * fRec44[1]);
		fRec44[0] = (0 - ((fTemp29 + (fSlow85 * fRec44[2])) - fTemp28));
		double fTemp30 = (fSlow85 * fRec44[0]);
		double fTemp31 = (0.5 * ((fTemp30 + (fRec44[2] + (fTemp28 + fTemp29))) + (fSlow82 * ((fTemp30 + (fTemp29 + fRec44[2])) - fTemp28))));
		double fTemp32 = (fSlow91 * fRec45[1]);
		fRec45[0] = (0 - ((fTemp32 + (fSlow90 * fRec45[2])) - fTemp31));
		double fTemp33 = (fSlow90 * fRec45[0]);
		output1[i] = (FAUSTFLOAT)(fTemp0 * ((0.25 * (fTemp1 * ((fTemp33 + (fRec45[2] + (fTemp31 + fTemp32))) + (fSlow87 * ((fTemp33 + (fTemp32 + fRec45[2])) - fTemp31))))) + (fVec10[IOTA&8191] * fTemp2)));
		// post processing
		fRec45[2] = fRec45[1]; fRec45[1] = fRec45[0];
		fRec44[2] = fRec44[1]; fRec44[1] = fRec44[0];
		fRec43[2] = fRec43[1]; fRec43[1] = fRec43[0];
		fRec42[2] = fRec42[1]; fRec42[1] = fRec42[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
		fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec38[1] = fRec38[0];
		fRec40[1] = fRec40[0];
		fRec41[1] = fRec41[0];
		fRec34[1] = fRec34[0];
		fRec36[1] = fRec36[0];
		fRec37[1] = fRec37[0];
		fRec30[1] = fRec30[0];
		fRec32[1] = fRec32[0];
		fRec33[1] = fRec33[0];
		fRec26[1] = fRec26[0];
		fRec28[1] = fRec28[0];
		fRec29[1] = fRec29[0];
		fRec22[1] = fRec22[0];
		fRec24[1] = fRec24[0];
		fRec25[1] = fRec25[0];
		fRec18[1] = fRec18[0];
		fRec20[1] = fRec20[0];
		fRec21[1] = fRec21[0];
		fRec14[1] = fRec14[0];
		fRec16[1] = fRec16[0];
		fRec17[1] = fRec17[0];
		fRec10[1] = fRec10[0];
		fRec12[1] = fRec12[0];
		fRec13[1] = fRec13[0];
		IOTA = IOTA+1;
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
	}
#undef fslider0
#undef fslider1
#undef fslider2
#undef fslider3
#undef fslider4
#undef fslider5
#undef fslider6
#undef fslider7
#undef fslider8
#undef fslider9
#undef fslider10
}
		
void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case HF_DAMPING: 
		fslider5_ = (float*)data; // , 6e+03, 1.5e+03, 2.352e+04, 1.0 
		break;
	case LF_X: 
		fslider2_ = (float*)data; // , 2e+02, 5e+01, 1e+03, 1.0 
		break;
	case LOW_RT60: 
		fslider4_ = (float*)data; // , 3.0, 1.0, 8.0, 0.1 
		break;
	case MID_RT60: 
		fslider3_ = (float*)data; // , 2.0, 1.0, 8.0, 0.1 
		break;
	case EQ1_FREQ: 
		fslider8_ = (float*)data; // , 315.0, 4e+01, 2.5e+03, 1.0 
		break;
	case EQ1_LEVEL: 
		fslider7_ = (float*)data; // , 0.0, -15.0, 15.0, 0.1 
		break;
	case EQ2_FREQ: 
		fslider10_ = (float*)data; // , 1.5e+03, 1.6e+02, 1e+04, 1.0 
		break;
	case EQ2_LEVEL: 
		fslider9_ = (float*)data; // , 0.0, -15.0, 15.0, 0.1 
		break;
	case IN_DELAY: 
		fslider6_ = (float*)data; // , 6e+01, 2e+01, 1e+02, 1.0 
		break;
	case DRY_WET_MIX: 
		fslider1_ = (float*)data; // , 0.0, -1.0, 1.0, 0.01 
		break;
	case LEVEL: 
		fslider0_ = (float*)data; // , 0.0, -7e+01, 4e+01, 0.1 
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
   HF_DAMPING, 
   LF_X, 
   LOW_RT60, 
   MID_RT60, 
   EQ1_FREQ, 
   EQ1_LEVEL, 
   EQ2_FREQ, 
   EQ2_LEVEL, 
   IN_DELAY, 
   DRY_WET_MIX, 
   LEVEL, 
} PortIndex;
*/

} // end namespace gx_zita_rev1
