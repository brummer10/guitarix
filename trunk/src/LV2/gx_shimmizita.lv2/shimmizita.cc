// generated from file './faust/shimmizita.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)


namespace shimmizita {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	class SIG0 {
	  private:
		int 	fSamplingFreq;
		int 	iRec14[2];
	  public:
		int getNumInputs() 	{ return 0; }
		int getNumOutputs() 	{ return 1; }
		void init(int samplingFreq) {
			fSamplingFreq = samplingFreq;
			for (int i=0; i<2; i++) iRec14[i] = 0;
		}
		void fill (int count, double output[]) {
			for (int i=0; i<count; i++) {
				iRec14[0] = (1 + iRec14[1]);
				output[i] = sin((9.587379924285257e-05 * double((iRec14[0] - 1))));
				// post processing
				iRec14[1] = iRec14[0];
			}
		}
	};
			FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	int 	iConst0;
	double 	fConst1;
	double 	fRec13[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fConst2;
	double 	fConst3;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fConst4;
	double 	fConst5;
	double 	fRec12[2];
	int 	IOTA;
	double 	fVec0[65536];
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT	*fslider4_;
	double 	fConst6;
	double 	fRec11[2];
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT	*fslider5_;
	static double 	ftbl0[65536];
	FAUSTFLOAT 	fslider6;
	FAUSTFLOAT	*fslider6_;
	double 	fConst7;
	double 	fRec15[2];
	FAUSTFLOAT 	fslider7;
	FAUSTFLOAT	*fslider7_;
	FAUSTFLOAT 	fslider8;
	FAUSTFLOAT	*fslider8_;
	FAUSTFLOAT 	fslider9;
	FAUSTFLOAT	*fslider9_;
	double 	fRec10[2];
	FAUSTFLOAT 	fslider10;
	FAUSTFLOAT	*fslider10_;
	double 	fVec1[8192];
	double 	fConst8;
	int 	iConst9;
	double 	fVec2[2048];
	int 	iConst10;
	double 	fRec8[2];
	double 	fRec21[2];
	double 	fConst11;
	double 	fConst12;
	double 	fRec20[2];
	double 	fVec3[65536];
	double 	fRec19[2];
	double 	fRec18[2];
	double 	fVec4[8192];
	double 	fConst13;
	int 	iConst14;
	double 	fVec5[1024];
	int 	iConst15;
	double 	fRec16[2];
	double 	fRec27[2];
	double 	fConst16;
	double 	fConst17;
	double 	fRec26[2];
	double 	fVec6[65536];
	double 	fRec25[2];
	double 	fRec24[2];
	double 	fVec7[8192];
	double 	fConst18;
	int 	iConst19;
	double 	fVec8[2048];
	int 	iConst20;
	double 	fRec22[2];
	double 	fRec33[2];
	double 	fConst21;
	double 	fConst22;
	double 	fRec32[2];
	double 	fVec9[65536];
	double 	fRec31[2];
	double 	fRec30[2];
	double 	fVec10[8192];
	double 	fConst23;
	int 	iConst24;
	double 	fVec11[1024];
	int 	iConst25;
	double 	fRec28[2];
	double 	fRec39[2];
	double 	fConst26;
	double 	fConst27;
	double 	fRec38[2];
	double 	fVec12[65536];
	double 	fRec37[2];
	double 	fRec36[2];
	double 	fVec13[16384];
	double 	fConst28;
	int 	iConst29;
	double 	fVec14[2048];
	int 	iConst30;
	double 	fRec34[2];
	double 	fRec45[2];
	double 	fConst31;
	double 	fConst32;
	double 	fRec44[2];
	double 	fVec15[65536];
	double 	fRec43[2];
	double 	fRec42[2];
	double 	fVec16[8192];
	double 	fConst33;
	int 	iConst34;
	double 	fVec17[2048];
	int 	iConst35;
	double 	fRec40[2];
	double 	fRec51[2];
	double 	fConst36;
	double 	fConst37;
	double 	fRec50[2];
	double 	fVec18[65536];
	double 	fRec49[2];
	double 	fRec48[2];
	double 	fVec19[16384];
	double 	fConst38;
	int 	iConst39;
	double 	fVec20[2048];
	int 	iConst40;
	double 	fRec46[2];
	double 	fRec57[2];
	double 	fConst41;
	double 	fConst42;
	double 	fRec56[2];
	double 	fVec21[65536];
	double 	fRec55[2];
	double 	fRec54[2];
	double 	fVec22[16384];
	double 	fConst43;
	int 	iConst44;
	double 	fVec23[1024];
	int 	iConst45;
	double 	fRec52[2];
	double 	fRec0[3];
	double 	fRec1[3];
	double 	fRec2[3];
	double 	fRec3[3];
	double 	fRec4[3];
	double 	fRec5[3];
	double 	fRec6[3];
	double 	fRec7[3];
	FAUSTFLOAT 	fslider11;
	FAUSTFLOAT	*fslider11_;
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


double Dsp::ftbl0[65536];

Dsp::Dsp()
	: PluginLV2() {
	version = PLUGINLV2_VERSION;
	id = "shimmizita";
	name = "?shimmizita";
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
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<65536; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<8192; i++) fVec1[i] = 0;
	for (int i=0; i<2048; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<65536; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<8192; i++) fVec4[i] = 0;
	for (int i=0; i<1024; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fRec27[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<65536; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec25[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<8192; i++) fVec7[i] = 0;
	for (int i=0; i<2048; i++) fVec8[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fRec33[i] = 0;
	for (int i=0; i<2; i++) fRec32[i] = 0;
	for (int i=0; i<65536; i++) fVec9[i] = 0;
	for (int i=0; i<2; i++) fRec31[i] = 0;
	for (int i=0; i<2; i++) fRec30[i] = 0;
	for (int i=0; i<8192; i++) fVec10[i] = 0;
	for (int i=0; i<1024; i++) fVec11[i] = 0;
	for (int i=0; i<2; i++) fRec28[i] = 0;
	for (int i=0; i<2; i++) fRec39[i] = 0;
	for (int i=0; i<2; i++) fRec38[i] = 0;
	for (int i=0; i<65536; i++) fVec12[i] = 0;
	for (int i=0; i<2; i++) fRec37[i] = 0;
	for (int i=0; i<2; i++) fRec36[i] = 0;
	for (int i=0; i<16384; i++) fVec13[i] = 0;
	for (int i=0; i<2048; i++) fVec14[i] = 0;
	for (int i=0; i<2; i++) fRec34[i] = 0;
	for (int i=0; i<2; i++) fRec45[i] = 0;
	for (int i=0; i<2; i++) fRec44[i] = 0;
	for (int i=0; i<65536; i++) fVec15[i] = 0;
	for (int i=0; i<2; i++) fRec43[i] = 0;
	for (int i=0; i<2; i++) fRec42[i] = 0;
	for (int i=0; i<8192; i++) fVec16[i] = 0;
	for (int i=0; i<2048; i++) fVec17[i] = 0;
	for (int i=0; i<2; i++) fRec40[i] = 0;
	for (int i=0; i<2; i++) fRec51[i] = 0;
	for (int i=0; i<2; i++) fRec50[i] = 0;
	for (int i=0; i<65536; i++) fVec18[i] = 0;
	for (int i=0; i<2; i++) fRec49[i] = 0;
	for (int i=0; i<2; i++) fRec48[i] = 0;
	for (int i=0; i<16384; i++) fVec19[i] = 0;
	for (int i=0; i<2048; i++) fVec20[i] = 0;
	for (int i=0; i<2; i++) fRec46[i] = 0;
	for (int i=0; i<2; i++) fRec57[i] = 0;
	for (int i=0; i<2; i++) fRec56[i] = 0;
	for (int i=0; i<65536; i++) fVec21[i] = 0;
	for (int i=0; i<2; i++) fRec55[i] = 0;
	for (int i=0; i<2; i++) fRec54[i] = 0;
	for (int i=0; i<16384; i++) fVec22[i] = 0;
	for (int i=0; i<1024; i++) fVec23[i] = 0;
	for (int i=0; i<2; i++) fRec52[i] = 0;
	for (int i=0; i<3; i++) fRec0[i] = 0;
	for (int i=0; i<3; i++) fRec1[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<3; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec4[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<3; i++) fRec7[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	SIG0 sig0;
	sig0.init(samplingFreq);
	sig0.fill(65536,ftbl0);
	fSamplingFreq = samplingFreq;
	iConst0 = std::min(192000, std::max(1, (int)fSamplingFreq));
	fConst1 = (3.141592653589793 / double(iConst0));
	fConst2 = floor((0.5 + (0.174713 * iConst0)));
	fConst3 = ((0 - (6.907755278982138 * fConst2)) / double(iConst0));
	fConst4 = double(iConst0);
	fConst5 = (6.283185307179586 / fConst4);
	IOTA = 0;
	fConst6 = (1.0 / double(iConst0));
	fConst7 = (1.0 / fConst4);
	fConst8 = floor((0.5 + (0.022904 * iConst0)));
	iConst9 = int((int((fConst2 - fConst8)) & 8191));
	iConst10 = int((int((fConst8 - 1)) & 2047));
	fConst11 = floor((0.5 + (0.153129 * iConst0)));
	fConst12 = ((0 - (6.907755278982138 * fConst11)) / double(iConst0));
	fConst13 = floor((0.5 + (0.020346 * iConst0)));
	iConst14 = int((int((fConst11 - fConst13)) & 8191));
	iConst15 = int((int((fConst13 - 1)) & 1023));
	fConst16 = floor((0.5 + (0.127837 * iConst0)));
	fConst17 = ((0 - (6.907755278982138 * fConst16)) / double(iConst0));
	fConst18 = floor((0.5 + (0.031604 * iConst0)));
	iConst19 = int((int((fConst16 - fConst18)) & 8191));
	iConst20 = int((int((fConst18 - 1)) & 2047));
	fConst21 = floor((0.5 + (0.125 * iConst0)));
	fConst22 = ((0 - (6.907755278982138 * fConst21)) / double(iConst0));
	fConst23 = floor((0.5 + (0.013458 * iConst0)));
	iConst24 = int((int((fConst21 - fConst23)) & 8191));
	iConst25 = int((int((fConst23 - 1)) & 1023));
	fConst26 = floor((0.5 + (0.210389 * iConst0)));
	fConst27 = ((0 - (6.907755278982138 * fConst26)) / double(iConst0));
	fConst28 = floor((0.5 + (0.024421 * iConst0)));
	iConst29 = int((int((fConst26 - fConst28)) & 16383));
	iConst30 = int((int((fConst28 - 1)) & 2047));
	fConst31 = floor((0.5 + (0.192303 * iConst0)));
	fConst32 = ((0 - (6.907755278982138 * fConst31)) / double(iConst0));
	fConst33 = floor((0.5 + (0.029291 * iConst0)));
	iConst34 = int((int((fConst31 - fConst33)) & 8191));
	iConst35 = int((int((fConst33 - 1)) & 2047));
	fConst36 = floor((0.5 + (0.256891 * iConst0)));
	fConst37 = ((0 - (6.907755278982138 * fConst36)) / double(iConst0));
	fConst38 = floor((0.5 + (0.027333 * iConst0)));
	iConst39 = int((int((fConst36 - fConst38)) & 16383));
	iConst40 = int((int((fConst38 - 1)) & 2047));
	fConst41 = floor((0.5 + (0.219991 * iConst0)));
	fConst42 = ((0 - (6.907755278982138 * fConst41)) / double(iConst0));
	fConst43 = floor((0.5 + (0.019123 * iConst0)));
	iConst44 = int((int((fConst41 - fConst43)) & 16383));
	iConst45 = int((int((fConst43 - 1)) & 1023));
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
#define fslider11 (*fslider11_)
	double 	fSlow0 = (1.0 / tan((fConst1 * double(fslider0))));
	double 	fSlow1 = (1 + fSlow0);
	double 	fSlow2 = (1.0 / fSlow1);
	double 	fSlow3 = (0 - ((1 - fSlow0) / fSlow1));
	double 	fSlow4 = double(fslider1);
	double 	fSlow5 = exp((fConst3 / fSlow4));
	double 	fSlow6 = double(fslider2);
	double 	fSlow7 = ((exp((fConst3 / fSlow6)) / fSlow5) - 1);
	double 	fSlow8 = faustpower<2>(fSlow5);
	double 	fSlow9 = (1.0 - fSlow8);
	double 	fSlow10 = cos((fConst5 * double(fslider3)));
	double 	fSlow11 = (1.0 - (fSlow10 * fSlow8));
	double 	fSlow12 = (fSlow11 / fSlow9);
	double 	fSlow13 = sqrt(std::max((double)0, ((faustpower<2>(fSlow11) / faustpower<2>(fSlow9)) - 1.0)));
	double 	fSlow14 = (fSlow5 * ((1.0 + fSlow13) - fSlow12));
	double 	fSlow15 = (fSlow12 - fSlow13);
	double 	fSlow16 = exp((0 - (fConst6 / double(fslider4))));
	double 	fSlow17 = (1.0 - fSlow16);
	double 	fSlow18 = double(fslider5);
	double 	fSlow19 = (6 * (1 - fSlow18));
	double 	fSlow20 = (fConst7 * double(fslider6));
	double 	fSlow21 = (0.5 * fSlow18);
	double 	fSlow22 = double(fslider7);
	double 	fSlow23 = double(fslider8);
	int 	iSlow24 = (fSlow23 < 0);
	double 	fSlow25 = (0.5 * fSlow23);
	double 	fSlow26 = (1 + fSlow25);
	int 	iSlow27 = (fSlow23 >= 0);
	double 	fSlow28 = (iSlow27 * fSlow26);
	double 	fSlow29 = double(fslider9);
	double 	fSlow30 = (0.08333333333333333 * (fSlow29 * (fSlow28 + (iSlow24 * (1 + (0.16666666666666666 * fSlow23))))));
	double 	fSlow31 = double(fslider10);
	double 	fSlow32 = (1 - fSlow31);
	double 	fSlow33 = exp((fConst12 / fSlow4));
	double 	fSlow34 = ((exp((fConst12 / fSlow6)) / fSlow33) - 1);
	double 	fSlow35 = faustpower<2>(fSlow33);
	double 	fSlow36 = (1.0 - fSlow35);
	double 	fSlow37 = (1.0 - (fSlow10 * fSlow35));
	double 	fSlow38 = (fSlow37 / fSlow36);
	double 	fSlow39 = sqrt(std::max((double)0, ((faustpower<2>(fSlow37) / faustpower<2>(fSlow36)) - 1.0)));
	double 	fSlow40 = (fSlow33 * ((1.0 + fSlow39) - fSlow38));
	double 	fSlow41 = (fSlow38 - fSlow39);
	double 	fSlow42 = (0.08333333333333333 * (fSlow29 * (fSlow28 + (iSlow24 * (1 + (0.2 * fSlow23))))));
	double 	fSlow43 = exp((fConst17 / fSlow4));
	double 	fSlow44 = ((exp((fConst17 / fSlow6)) / fSlow43) - 1);
	double 	fSlow45 = faustpower<2>(fSlow43);
	double 	fSlow46 = (1.0 - fSlow45);
	double 	fSlow47 = (1.0 - (fSlow10 * fSlow45));
	double 	fSlow48 = (fSlow47 / fSlow46);
	double 	fSlow49 = sqrt(std::max((double)0, ((faustpower<2>(fSlow47) / faustpower<2>(fSlow46)) - 1.0)));
	double 	fSlow50 = (fSlow43 * ((1.0 + fSlow49) - fSlow48));
	double 	fSlow51 = (fSlow48 - fSlow49);
	double 	fSlow52 = (0.3333333333333333 * fSlow23);
	double 	fSlow53 = (1 + fSlow52);
	double 	fSlow54 = (0.08333333333333333 * (fSlow29 * (fSlow28 + (iSlow24 * fSlow53))));
	double 	fSlow55 = exp((fConst22 / fSlow4));
	double 	fSlow56 = ((exp((fConst22 / fSlow6)) / fSlow55) - 1);
	double 	fSlow57 = faustpower<2>(fSlow55);
	double 	fSlow58 = (1.0 - fSlow57);
	double 	fSlow59 = (1.0 - (fSlow10 * fSlow57));
	double 	fSlow60 = (fSlow59 / fSlow58);
	double 	fSlow61 = sqrt(std::max((double)0, ((faustpower<2>(fSlow59) / faustpower<2>(fSlow58)) - 1.0)));
	double 	fSlow62 = (fSlow55 * ((1.0 + fSlow61) - fSlow60));
	double 	fSlow63 = (fSlow60 - fSlow61);
	double 	fSlow64 = exp((fConst27 / fSlow4));
	double 	fSlow65 = ((exp((fConst27 / fSlow6)) / fSlow64) - 1);
	double 	fSlow66 = faustpower<2>(fSlow64);
	double 	fSlow67 = (1.0 - fSlow66);
	double 	fSlow68 = (1.0 - (fSlow10 * fSlow66));
	double 	fSlow69 = (fSlow68 / fSlow67);
	double 	fSlow70 = sqrt(std::max((double)0, ((faustpower<2>(fSlow68) / faustpower<2>(fSlow67)) - 1.0)));
	double 	fSlow71 = (fSlow64 * ((1.0 + fSlow70) - fSlow69));
	double 	fSlow72 = (fSlow69 - fSlow70);
	double 	fSlow73 = (iSlow24 * (1 - fSlow25));
	double 	fSlow74 = (iSlow27 * fSlow53);
	double 	fSlow75 = (0.08333333333333333 * (fSlow29 * (fSlow74 + fSlow73)));
	double 	fSlow76 = exp((fConst32 / fSlow4));
	double 	fSlow77 = ((exp((fConst32 / fSlow6)) / fSlow76) - 1);
	double 	fSlow78 = faustpower<2>(fSlow76);
	double 	fSlow79 = (1.0 - fSlow78);
	double 	fSlow80 = (1.0 - (fSlow10 * fSlow78));
	double 	fSlow81 = (fSlow80 / fSlow79);
	double 	fSlow82 = sqrt(std::max((double)0, ((faustpower<2>(fSlow80) / faustpower<2>(fSlow79)) - 1.0)));
	double 	fSlow83 = (fSlow76 * ((1.0 + fSlow82) - fSlow81));
	double 	fSlow84 = (fSlow81 - fSlow82);
	double 	fSlow85 = (0.08333333333333333 * (fSlow29 * ((iSlow27 * (1 + (0.125 * fSlow23))) + (iSlow24 * (1 - fSlow52)))));
	double 	fSlow86 = exp((fConst37 / fSlow4));
	double 	fSlow87 = ((exp((fConst37 / fSlow6)) / fSlow86) - 1);
	double 	fSlow88 = faustpower<2>(fSlow86);
	double 	fSlow89 = (1.0 - fSlow88);
	double 	fSlow90 = (1.0 - (fSlow10 * fSlow88));
	double 	fSlow91 = (fSlow90 / fSlow89);
	double 	fSlow92 = sqrt(std::max((double)0, ((faustpower<2>(fSlow90) / faustpower<2>(fSlow89)) - 1.0)));
	double 	fSlow93 = (fSlow86 * ((1.0 + fSlow92) - fSlow91));
	double 	fSlow94 = (fSlow91 - fSlow92);
	double 	fSlow95 = (0.08333333333333333 * (fSlow29 * ((iSlow27 * (1 + (0.25 * fSlow23))) + fSlow73)));
	double 	fSlow96 = exp((fConst42 / fSlow4));
	double 	fSlow97 = ((exp((fConst42 / fSlow6)) / fSlow96) - 1);
	double 	fSlow98 = faustpower<2>(fSlow96);
	double 	fSlow99 = (1.0 - fSlow98);
	double 	fSlow100 = (1.0 - (fSlow98 * fSlow10));
	double 	fSlow101 = (fSlow100 / fSlow99);
	double 	fSlow102 = sqrt(std::max((double)0, ((faustpower<2>(fSlow100) / faustpower<2>(fSlow99)) - 1.0)));
	double 	fSlow103 = (fSlow96 * ((1.0 + fSlow102) - fSlow101));
	double 	fSlow104 = (fSlow101 - fSlow102);
	double 	fSlow105 = (0.08333333333333333 * (fSlow29 * (fSlow74 + (iSlow24 * fSlow26))));
	double 	fSlow106 = double(fslider11);
	double 	fSlow107 = (1 - fSlow106);
	for (int i=0; i<count; i++) {
		fRec13[0] = ((fSlow3 * fRec13[1]) + (fSlow2 * (fRec4[1] + fRec4[2])));
		fRec12[0] = ((fSlow15 * fRec12[1]) + (fSlow14 * (fRec4[1] + (fSlow7 * fRec13[0]))));
		double fTemp0 = (1e-20 + (0.35355339059327373 * fRec12[0]));
		fVec0[IOTA&65535] = fTemp0;
		double fTemp1 = fabs(fVec0[IOTA&65535]);
		fRec11[0] = ((fSlow16 * std::max(fTemp1, fRec11[1])) + (fSlow17 * fTemp1));
		double fTemp2 = (fRec15[1] + fSlow20);
		fRec15[0] = (fTemp2 - floor(fTemp2));
		double fTemp3 = (fSlow21 * ftbl0[int((65536.0 * fRec15[0]))]);
		fRec10[0] = fmod(((2049 + fRec10[1]) - pow(2,(fSlow30 * (0.5 + (fSlow22 * (fTemp3 + (fSlow19 * fRec11[0]))))))),2048);
		double fTemp4 = std::min((0.0009765625 * fRec10[0]), (double)1);
		double fTemp5 = (2048 + fRec10[0]);
		int iTemp6 = int(fTemp5);
		int iTemp7 = int(fRec10[0]);
		int iTemp8 = (1 + iTemp7);
		fVec1[IOTA&8191] = ((fSlow32 * fVec0[IOTA&65535]) + (fSlow31 * ((((fVec0[(IOTA-int((iTemp7 & 65535)))&65535] * (iTemp8 - fRec10[0])) + ((fRec10[0] - iTemp7) * fVec0[(IOTA-int((int(iTemp8) & 65535)))&65535])) * fTemp4) + (((fVec0[(IOTA-int((iTemp6 & 65535)))&65535] * (iTemp6 - (fRec10[0] + 2047))) + ((fTemp5 - iTemp6) * fVec0[(IOTA-int((int((1 + iTemp6)) & 65535)))&65535])) * (1 - fTemp4)))));
		double fTemp9 = (double)input0[i];
		double fTemp10 = ((fTemp9 + fVec1[(IOTA-iConst9)&8191]) - (0.6 * fRec8[1]));
		fVec2[IOTA&2047] = fTemp10;
		fRec8[0] = fVec2[(IOTA-iConst10)&2047];
		double 	fRec9 = (0.6 * fVec2[IOTA&2047]);
		fRec21[0] = ((fSlow3 * fRec21[1]) + (fSlow2 * (fRec0[1] + fRec0[2])));
		fRec20[0] = ((fSlow41 * fRec20[1]) + (fSlow40 * (fRec0[1] + (fSlow34 * fRec21[0]))));
		double fTemp11 = (1e-20 + (0.35355339059327373 * fRec20[0]));
		fVec3[IOTA&65535] = fTemp11;
		double fTemp12 = fabs(fVec3[IOTA&65535]);
		fRec19[0] = ((fSlow16 * std::max(fTemp12, fRec19[1])) + (fSlow17 * fTemp12));
		fRec18[0] = fmod(((2049 + fRec18[1]) - pow(2,(fSlow42 * (0.5 + (fSlow22 * ((fSlow19 * fRec19[0]) + fTemp3)))))),2048);
		double fTemp13 = std::min((0.0009765625 * fRec18[0]), (double)1);
		double fTemp14 = (2048 + fRec18[0]);
		int iTemp15 = int(fTemp14);
		int iTemp16 = int(fRec18[0]);
		int iTemp17 = (1 + iTemp16);
		fVec4[IOTA&8191] = ((fSlow32 * fVec3[IOTA&65535]) + (fSlow31 * ((((fVec3[(IOTA-int((iTemp16 & 65535)))&65535] * (iTemp17 - fRec18[0])) + ((fRec18[0] - iTemp16) * fVec3[(IOTA-int((int(iTemp17) & 65535)))&65535])) * fTemp13) + (((fVec3[(IOTA-int((iTemp15 & 65535)))&65535] * (iTemp15 - (fRec18[0] + 2047))) + ((fTemp14 - iTemp15) * fVec3[(IOTA-int((int((1 + iTemp15)) & 65535)))&65535])) * (1 - fTemp13)))));
		double fTemp18 = ((fTemp9 + fVec4[(IOTA-iConst14)&8191]) - (0.6 * fRec16[1]));
		fVec5[IOTA&1023] = fTemp18;
		fRec16[0] = fVec5[(IOTA-iConst15)&1023];
		double 	fRec17 = (0.6 * fVec5[IOTA&1023]);
		double fTemp19 = (fRec17 + fRec9);
		fRec27[0] = ((fSlow3 * fRec27[1]) + (fSlow2 * (fRec2[1] + fRec2[2])));
		fRec26[0] = ((fSlow51 * fRec26[1]) + (fSlow50 * (fRec2[1] + (fSlow44 * fRec27[0]))));
		double fTemp20 = (1e-20 + (0.35355339059327373 * fRec26[0]));
		fVec6[IOTA&65535] = fTemp20;
		double fTemp21 = fabs(fVec6[IOTA&65535]);
		fRec25[0] = ((fSlow16 * std::max(fTemp21, fRec25[1])) + (fSlow17 * fTemp21));
		fRec24[0] = fmod(((2049 + fRec24[1]) - pow(2,(fSlow54 * (0.5 + (fSlow22 * (fTemp3 + (fSlow19 * fRec25[0]))))))),2048);
		double fTemp22 = std::min((0.0009765625 * fRec24[0]), (double)1);
		double fTemp23 = (2048 + fRec24[0]);
		int iTemp24 = int(fTemp23);
		int iTemp25 = int(fRec24[0]);
		int iTemp26 = (1 + iTemp25);
		fVec7[IOTA&8191] = ((fSlow32 * fVec6[IOTA&65535]) + (fSlow31 * ((((fVec6[(IOTA-int((iTemp25 & 65535)))&65535] * (iTemp26 - fRec24[0])) + ((fRec24[0] - iTemp25) * fVec6[(IOTA-int((int(iTemp26) & 65535)))&65535])) * fTemp22) + (((fVec6[(IOTA-int((iTemp24 & 65535)))&65535] * (iTemp24 - (fRec24[0] + 2047))) + ((fTemp23 - iTemp24) * fVec6[(IOTA-int((int((1 + iTemp24)) & 65535)))&65535])) * (1 - fTemp22)))));
		double fTemp27 = ((fTemp9 + fVec7[(IOTA-iConst19)&8191]) - (0.6 * fRec22[1]));
		fVec8[IOTA&2047] = fTemp27;
		fRec22[0] = fVec8[(IOTA-iConst20)&2047];
		double 	fRec23 = (0.6 * fVec8[IOTA&2047]);
		fRec33[0] = ((fSlow3 * fRec33[1]) + (fSlow2 * (fRec6[1] + fRec6[2])));
		fRec32[0] = ((fSlow63 * fRec32[1]) + (fSlow62 * (fRec6[1] + (fSlow56 * fRec33[0]))));
		double fTemp28 = (1e-20 + (0.35355339059327373 * fRec32[0]));
		fVec9[IOTA&65535] = fTemp28;
		double fTemp29 = fabs(fVec9[IOTA&65535]);
		fRec31[0] = ((fSlow16 * std::max(fTemp29, fRec31[1])) + (fSlow17 * fTemp29));
		fRec30[0] = fmod(((2049 + fRec30[1]) - pow(2,(fSlow54 * (0.5 + (fSlow22 * (fTemp3 + (fSlow19 * fRec31[0]))))))),2048);
		double fTemp30 = std::min((0.0009765625 * fRec30[0]), (double)1);
		double fTemp31 = (2048 + fRec30[0]);
		int iTemp32 = int(fTemp31);
		int iTemp33 = int(fRec30[0]);
		int iTemp34 = (1 + iTemp33);
		fVec10[IOTA&8191] = ((fSlow32 * fVec9[IOTA&65535]) + (fSlow31 * ((((fVec9[(IOTA-int((iTemp33 & 65535)))&65535] * (iTemp34 - fRec30[0])) + ((fRec30[0] - iTemp33) * fVec9[(IOTA-int((int(iTemp34) & 65535)))&65535])) * fTemp30) + (((fVec9[(IOTA-int((iTemp32 & 65535)))&65535] * (iTemp32 - (fRec30[0] + 2047))) + ((fTemp31 - iTemp32) * fVec9[(IOTA-int((int((1 + iTemp32)) & 65535)))&65535])) * (1 - fTemp30)))));
		double fTemp35 = ((fTemp9 + fVec10[(IOTA-iConst24)&8191]) - (0.6 * fRec28[1]));
		fVec11[IOTA&1023] = fTemp35;
		fRec28[0] = fVec11[(IOTA-iConst25)&1023];
		double 	fRec29 = (0.6 * fVec11[IOTA&1023]);
		double fTemp36 = (fRec29 + (fRec23 + fTemp19));
		double fTemp37 = (double)input1[i];
		fRec39[0] = ((fSlow3 * fRec39[1]) + (fSlow2 * (fRec1[1] + fRec1[2])));
		fRec38[0] = ((fSlow72 * fRec38[1]) + (fSlow71 * (fRec1[1] + (fSlow65 * fRec39[0]))));
		double fTemp38 = (1e-20 + (0.35355339059327373 * fRec38[0]));
		fVec12[IOTA&65535] = fTemp38;
		double fTemp39 = fabs(fVec12[IOTA&65535]);
		fRec37[0] = ((fSlow16 * std::max(fTemp39, fRec37[1])) + (fSlow17 * fTemp39));
		fRec36[0] = fmod(((2049 + fRec36[1]) - pow(2,(fSlow75 * (0.5 + (fSlow22 * (fTemp3 + (fSlow19 * fRec37[0]))))))),2048);
		double fTemp40 = std::min((0.0009765625 * fRec36[0]), (double)1);
		double fTemp41 = (2048 + fRec36[0]);
		int iTemp42 = int(fTemp41);
		int iTemp43 = int(fRec36[0]);
		int iTemp44 = (1 + iTemp43);
		fVec13[IOTA&16383] = ((fSlow32 * fVec12[IOTA&65535]) + (fSlow31 * ((((fVec12[(IOTA-int((iTemp43 & 65535)))&65535] * (iTemp44 - fRec36[0])) + ((fRec36[0] - iTemp43) * fVec12[(IOTA-int((int(iTemp44) & 65535)))&65535])) * fTemp40) + (((fVec12[(IOTA-int((iTemp42 & 65535)))&65535] * (iTemp42 - (fRec36[0] + 2047))) + ((fTemp41 - iTemp42) * fVec12[(IOTA-int((int((1 + iTemp42)) & 65535)))&65535])) * (1 - fTemp40)))));
		double fTemp45 = (fVec13[(IOTA-iConst29)&16383] + (fTemp37 + (0.6 * fRec34[1])));
		fVec14[IOTA&2047] = fTemp45;
		fRec34[0] = fVec14[(IOTA-iConst30)&2047];
		double 	fRec35 = (0 - (0.6 * fVec14[IOTA&2047]));
		fRec45[0] = ((fSlow3 * fRec45[1]) + (fSlow2 * (fRec5[1] + fRec5[2])));
		fRec44[0] = ((fSlow84 * fRec44[1]) + (fSlow83 * (fRec5[1] + (fSlow77 * fRec45[0]))));
		double fTemp46 = (1e-20 + (0.35355339059327373 * fRec44[0]));
		fVec15[IOTA&65535] = fTemp46;
		double fTemp47 = fabs(fVec15[IOTA&65535]);
		fRec43[0] = ((fSlow16 * std::max(fTemp47, fRec43[1])) + (fSlow17 * fTemp47));
		fRec42[0] = fmod(((2049 + fRec42[1]) - pow(2,(fSlow85 * (0.5 + (fSlow22 * (fTemp3 + (fSlow19 * fRec43[0]))))))),2048);
		double fTemp48 = std::min((0.0009765625 * fRec42[0]), (double)1);
		double fTemp49 = (2048 + fRec42[0]);
		int iTemp50 = int(fTemp49);
		int iTemp51 = int(fRec42[0]);
		int iTemp52 = (1 + iTemp51);
		fVec16[IOTA&8191] = ((fSlow32 * fVec15[IOTA&65535]) + (fSlow31 * ((((fVec15[(IOTA-int((iTemp51 & 65535)))&65535] * (iTemp52 - fRec42[0])) + ((fRec42[0] - iTemp51) * fVec15[(IOTA-int((int(iTemp52) & 65535)))&65535])) * fTemp48) + (((fVec15[(IOTA-int((iTemp50 & 65535)))&65535] * (iTemp50 - (fRec42[0] + 2047))) + ((fTemp49 - iTemp50) * fVec15[(IOTA-int((int((1 + iTemp50)) & 65535)))&65535])) * (1 - fTemp48)))));
		double fTemp53 = (fVec16[(IOTA-iConst34)&8191] + (fTemp37 + (0.6 * fRec40[1])));
		fVec17[IOTA&2047] = fTemp53;
		fRec40[0] = fVec17[(IOTA-iConst35)&2047];
		double 	fRec41 = (0 - (0.6 * fVec17[IOTA&2047]));
		fRec51[0] = ((fSlow3 * fRec51[1]) + (fSlow2 * (fRec3[1] + fRec3[2])));
		fRec50[0] = ((fSlow94 * fRec50[1]) + (fSlow93 * (fRec3[1] + (fSlow87 * fRec51[0]))));
		double fTemp54 = (1e-20 + (0.35355339059327373 * fRec50[0]));
		fVec18[IOTA&65535] = fTemp54;
		double fTemp55 = fabs(fVec18[IOTA&65535]);
		fRec49[0] = ((fSlow16 * std::max(fTemp55, fRec49[1])) + (fSlow17 * fTemp55));
		fRec48[0] = fmod(((2049 + fRec48[1]) - pow(2,(fSlow95 * (0.5 + (fSlow22 * (fTemp3 + (fSlow19 * fRec49[0]))))))),2048);
		double fTemp56 = std::min((0.0009765625 * fRec48[0]), (double)1);
		double fTemp57 = (2048 + fRec48[0]);
		int iTemp58 = int(fTemp57);
		int iTemp59 = int(fRec48[0]);
		int iTemp60 = (1 + iTemp59);
		fVec19[IOTA&16383] = ((fSlow32 * fVec18[IOTA&65535]) + (fSlow31 * ((((fVec18[(IOTA-int((iTemp59 & 65535)))&65535] * (iTemp60 - fRec48[0])) + ((fRec48[0] - iTemp59) * fVec18[(IOTA-int((int(iTemp60) & 65535)))&65535])) * fTemp56) + (((fVec18[(IOTA-int((iTemp58 & 65535)))&65535] * (iTemp58 - (fRec48[0] + 2047))) + ((fTemp57 - iTemp58) * fVec18[(IOTA-int((int((1 + iTemp58)) & 65535)))&65535])) * (1 - fTemp56)))));
		double fTemp61 = (fVec19[(IOTA-iConst39)&16383] + (fTemp37 + (0.6 * fRec46[1])));
		fVec20[IOTA&2047] = fTemp61;
		fRec46[0] = fVec20[(IOTA-iConst40)&2047];
		double 	fRec47 = (0 - (0.6 * fVec20[IOTA&2047]));
		fRec57[0] = ((fSlow3 * fRec57[1]) + (fSlow2 * (fRec7[1] + fRec7[2])));
		fRec56[0] = ((fSlow104 * fRec56[1]) + (fSlow103 * (fRec7[1] + (fSlow97 * fRec57[0]))));
		double fTemp62 = (1e-20 + (0.35355339059327373 * fRec56[0]));
		fVec21[IOTA&65535] = fTemp62;
		double fTemp63 = fabs(fVec21[IOTA&65535]);
		fRec55[0] = ((fSlow16 * std::max(fTemp63, fRec55[1])) + (fSlow17 * fTemp63));
		fRec54[0] = fmod(((2049 + fRec54[1]) - pow(2,(fSlow105 * (0.5 + (fSlow22 * (fTemp3 + (fSlow19 * fRec55[0]))))))),2048);
		double fTemp64 = std::min((0.0009765625 * fRec54[0]), (double)1);
		double fTemp65 = (2048 + fRec54[0]);
		int iTemp66 = int(fTemp65);
		int iTemp67 = int(fRec54[0]);
		int iTemp68 = (1 + iTemp67);
		fVec22[IOTA&16383] = ((fSlow32 * fVec21[IOTA&65535]) + (fSlow31 * ((((fVec21[(IOTA-int((iTemp67 & 65535)))&65535] * (iTemp68 - fRec54[0])) + ((fRec54[0] - iTemp67) * fVec21[(IOTA-int((int(iTemp68) & 65535)))&65535])) * fTemp64) + (((fVec21[(IOTA-int((iTemp66 & 65535)))&65535] * (iTemp66 - (fRec54[0] + 2047))) + ((fTemp65 - iTemp66) * fVec21[(IOTA-int((int((1 + iTemp66)) & 65535)))&65535])) * (1 - fTemp64)))));
		double fTemp69 = (fVec22[(IOTA-iConst44)&16383] + (fTemp37 + (0.6 * fRec52[1])));
		fVec23[IOTA&1023] = fTemp69;
		fRec52[0] = fVec23[(IOTA-iConst45)&1023];
		double 	fRec53 = (0 - (0.6 * fVec23[IOTA&1023]));
		fRec0[0] = (fRec52[1] + (fRec46[1] + (fRec40[1] + (fRec34[1] + (fRec28[1] + (fRec22[1] + (fRec8[1] + (fRec16[1] + (fRec53 + (fRec47 + (fRec41 + (fRec35 + fTemp36))))))))))));
		fRec1[0] = (0 - ((fRec52[1] + (fRec46[1] + (fRec40[1] + (fRec34[1] + (fRec53 + (fRec47 + (fRec35 + fRec41))))))) - (fRec28[1] + (fRec22[1] + (fRec8[1] + (fRec16[1] + fTemp36))))));
		double fTemp70 = (fRec23 + fRec29);
		fRec2[0] = (0 - ((fRec52[1] + (fRec46[1] + (fRec28[1] + (fRec22[1] + (fRec53 + (fRec47 + fTemp70)))))) - (fRec40[1] + (fRec34[1] + (fRec8[1] + (fRec16[1] + (fRec41 + (fRec35 + fTemp19))))))));
		fRec3[0] = (0 - ((fRec40[1] + (fRec34[1] + (fRec28[1] + (fRec22[1] + (fRec41 + (fRec35 + fTemp70)))))) - (fRec52[1] + (fRec46[1] + (fRec8[1] + (fRec16[1] + (fRec53 + (fRec47 + fTemp19))))))));
		double fTemp71 = (fRec17 + fRec23);
		double fTemp72 = (fRec9 + fRec29);
		fRec4[0] = (0 - ((fRec52[1] + (fRec40[1] + (fRec28[1] + (fRec8[1] + (fRec53 + (fRec41 + fTemp72)))))) - (fRec46[1] + (fRec34[1] + (fRec22[1] + (fRec16[1] + (fRec47 + (fRec35 + fTemp71))))))));
		fRec5[0] = (0 - ((fRec46[1] + (fRec34[1] + (fRec28[1] + (fRec8[1] + (fRec47 + (fRec35 + fTemp72)))))) - (fRec52[1] + (fRec40[1] + (fRec22[1] + (fRec16[1] + (fRec53 + (fRec41 + fTemp71))))))));
		double fTemp73 = (fRec17 + fRec29);
		double fTemp74 = (fRec9 + fRec23);
		fRec6[0] = (0 - ((fRec46[1] + (fRec40[1] + (fRec22[1] + (fRec8[1] + (fRec47 + (fRec41 + fTemp74)))))) - (fRec52[1] + (fRec34[1] + (fRec28[1] + (fRec16[1] + (fRec53 + (fRec35 + fTemp73))))))));
		fRec7[0] = (0 - ((fRec52[1] + (fRec34[1] + (fRec22[1] + (fRec8[1] + (fRec53 + (fRec35 + fTemp74)))))) - (fRec46[1] + (fRec40[1] + (fRec28[1] + (fRec16[1] + (fRec47 + (fRec41 + fTemp73))))))));
		output0[i] = (FAUSTFLOAT)((fSlow107 * fTemp9) + (fSlow106 * (((fRec0[0] + fRec2[0]) + fRec4[0]) + fRec6[0])));
		output1[i] = (FAUSTFLOAT)((fSlow107 * fTemp37) + (fSlow106 * (((fRec1[0] + fRec3[0]) + fRec5[0]) + fRec7[0])));
		// post processing
		fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		fRec52[1] = fRec52[0];
		fRec54[1] = fRec54[0];
		fRec55[1] = fRec55[0];
		fRec56[1] = fRec56[0];
		fRec57[1] = fRec57[0];
		fRec46[1] = fRec46[0];
		fRec48[1] = fRec48[0];
		fRec49[1] = fRec49[0];
		fRec50[1] = fRec50[0];
		fRec51[1] = fRec51[0];
		fRec40[1] = fRec40[0];
		fRec42[1] = fRec42[0];
		fRec43[1] = fRec43[0];
		fRec44[1] = fRec44[0];
		fRec45[1] = fRec45[0];
		fRec34[1] = fRec34[0];
		fRec36[1] = fRec36[0];
		fRec37[1] = fRec37[0];
		fRec38[1] = fRec38[0];
		fRec39[1] = fRec39[0];
		fRec28[1] = fRec28[0];
		fRec30[1] = fRec30[0];
		fRec31[1] = fRec31[0];
		fRec32[1] = fRec32[0];
		fRec33[1] = fRec33[0];
		fRec22[1] = fRec22[0];
		fRec24[1] = fRec24[0];
		fRec25[1] = fRec25[0];
		fRec26[1] = fRec26[0];
		fRec27[1] = fRec27[0];
		fRec16[1] = fRec16[0];
		fRec18[1] = fRec18[0];
		fRec19[1] = fRec19[0];
		fRec20[1] = fRec20[0];
		fRec21[1] = fRec21[0];
		fRec8[1] = fRec8[0];
		fRec10[1] = fRec10[0];
		fRec15[1] = fRec15[0];
		fRec11[1] = fRec11[0];
		IOTA = IOTA+1;
		fRec12[1] = fRec12[0];
		fRec13[1] = fRec13[0];
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
#undef fslider11
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case CONTROL: 
		fslider5_ = (float*)data; // , 0.5, 0.0, 1.0, 0.05 
		break;
	case DEPTH: 
		fslider7_ = (float*)data; // , 0.0, 0.0, 1.0, 0.05 
		break;
	case DRYWET: 
		fslider11_ = (float*)data; // , 0.5, 0.0, 1.0, 0.05 
		break;
	case ENVELOPE: 
		fslider4_ = (float*)data; // , 1.0, 0.1, 3.0, 0.05 
		break;
	case F1: 
		fslider0_ = (float*)data; // , 2e+02, 5e+01, 1e+03, 1.0 
		break;
	case F2: 
		fslider3_ = (float*)data; // , 6e+03, 1.5e+03, 2.352e+04, 1.0 
		break;
	case MODE: 
		fslider8_ = (float*)data; // , 0.0, -3.0, 3.0, 0.05 
		break;
	case PSDRYWET: 
		fslider10_ = (float*)data; // , 0.5, 0.0, 1.0, 0.05 
		break;
	case SHIFT: 
		fslider9_ = (float*)data; // , 0.0, -6.0, 6.0, 0.1 
		break;
	case SPEED: 
		fslider6_ = (float*)data; // , 0.1, 0.1, 1e+01, 0.05 
		break;
	case T60DS: 
		fslider2_ = (float*)data; // , 3.0, 1.0, 8.0, 0.1 
		break;
	case T60M: 
		fslider1_ = (float*)data; // , 2.0, 1.0, 8.0, 0.1 
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
   CONTROL, 
   DEPTH, 
   DRYWET, 
   ENVELOPE, 
   F1, 
   F2, 
   MODE, 
   PSDRYWET, 
   SHIFT, 
   SPEED, 
   T60DS, 
   T60M, 
} PortIndex;
*/

} // end namespace shimmizita
