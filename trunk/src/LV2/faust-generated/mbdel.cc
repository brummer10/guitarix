// generated from file '../src/LV2/faust/mbdel.dsp' by dsp2cc:
// Code generated with Faust 0.9.73 (http://faust.grame.fr)


namespace mbdel {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	int 	iConst0;
	double 	fConst1;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fConst2;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fVec0[2];
	double 	fRec9[2];
	double 	fRec8[3];
	double 	fRec7[3];
	double 	fRec6[3];
	double 	fRec5[3];
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT	*fslider4_;
	double 	fRec10[2];
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT	*fslider5_;
	int 	IOTA;
	double *fVec1;
	double 	fConst3;
	double 	fConst4;
	FAUSTFLOAT 	fslider6;
	FAUSTFLOAT	*fslider6_;
	int 	iConst5;
	double 	fRec11[2];
	double 	fRec12[2];
	double 	fRec13[2];
	double 	fRec14[2];
	double 	fRec4[2];
	double 	fRec0[2];
	int 	iRec1[2];
	double 	fRec2[2];
	FAUSTFLOAT 	fbargraph0;
	FAUSTFLOAT	*fbargraph0_;
	double 	fRec25[2];
	double 	fRec24[3];
	double 	fVec2[2];
	double 	fRec23[2];
	double 	fRec22[3];
	double 	fRec21[3];
	double 	fRec20[3];
	FAUSTFLOAT 	fslider7;
	FAUSTFLOAT	*fslider7_;
	double 	fRec26[2];
	FAUSTFLOAT 	fslider8;
	FAUSTFLOAT	*fslider8_;
	double *fVec3;
	FAUSTFLOAT 	fslider9;
	FAUSTFLOAT	*fslider9_;
	double 	fRec27[2];
	double 	fRec28[2];
	double 	fRec29[2];
	double 	fRec30[2];
	double 	fRec19[2];
	double 	fRec15[2];
	int 	iRec16[2];
	double 	fRec17[2];
	FAUSTFLOAT 	fbargraph1;
	FAUSTFLOAT	*fbargraph1_;
	double 	fRec40[2];
	double 	fRec39[3];
	double 	fVec4[2];
	double 	fRec38[2];
	double 	fRec37[3];
	double 	fRec36[3];
	FAUSTFLOAT 	fslider10;
	FAUSTFLOAT	*fslider10_;
	double 	fRec41[2];
	FAUSTFLOAT 	fslider11;
	FAUSTFLOAT	*fslider11_;
	double *fVec5;
	FAUSTFLOAT 	fslider12;
	FAUSTFLOAT	*fslider12_;
	double 	fRec42[2];
	double 	fRec43[2];
	double 	fRec44[2];
	double 	fRec45[2];
	double 	fRec35[2];
	double 	fRec31[2];
	int 	iRec32[2];
	double 	fRec33[2];
	FAUSTFLOAT 	fbargraph2;
	FAUSTFLOAT	*fbargraph2_;
	double 	fRec54[2];
	double 	fRec53[3];
	double 	fVec6[2];
	double 	fRec52[2];
	double 	fRec51[3];
	FAUSTFLOAT 	fslider13;
	FAUSTFLOAT	*fslider13_;
	double 	fRec55[2];
	FAUSTFLOAT 	fslider14;
	FAUSTFLOAT	*fslider14_;
	double *fVec7;
	FAUSTFLOAT 	fslider15;
	FAUSTFLOAT	*fslider15_;
	double 	fRec56[2];
	double 	fRec57[2];
	double 	fRec58[2];
	double 	fRec59[2];
	double 	fRec50[2];
	double 	fRec46[2];
	int 	iRec47[2];
	double 	fRec48[2];
	FAUSTFLOAT 	fbargraph3;
	FAUSTFLOAT	*fbargraph3_;
	double 	fRec66[2];
	double 	fRec65[3];
	FAUSTFLOAT 	fslider16;
	FAUSTFLOAT	*fslider16_;
	double 	fRec67[2];
	FAUSTFLOAT 	fslider17;
	FAUSTFLOAT	*fslider17_;
	double *fVec8;
	FAUSTFLOAT 	fslider18;
	FAUSTFLOAT	*fslider18_;
	double 	fRec68[2];
	double 	fRec69[2];
	double 	fRec70[2];
	double 	fRec71[2];
	double 	fRec64[2];
	double 	fRec60[2];
	int 	iRec61[2];
	double 	fRec62[2];
	FAUSTFLOAT 	fbargraph4;
	FAUSTFLOAT	*fbargraph4_;
	bool mem_allocated;
	void mem_alloc();
	void mem_free();
	void connect(uint32_t port,void* data);
	void clear_state_f();
	int activate(bool start);
	void init(uint32_t samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);

	static void clear_state_f_static(PluginLV2*);
	static int activate_static(bool start, PluginLV2*);
	static void init_static(uint32_t samplingFreq, PluginLV2*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginLV2(),
	  fVec1(0),
	  fVec3(0),
	  fVec5(0),
	  fVec7(0),
	  fVec8(0),
	  mem_allocated(false) {
	version = PLUGINLV2_VERSION;
	id = "mbdel";
	name = N_("MultiBand Delay");
	mono_audio = compute_static;
	stereo_audio = 0;
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
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<3; i++) fRec8[i] = 0;
	for (int i=0; i<3; i++) fRec7[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<262144; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) iRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec25[i] = 0;
	for (int i=0; i<3; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<3; i++) fRec22[i] = 0;
	for (int i=0; i<3; i++) fRec21[i] = 0;
	for (int i=0; i<3; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<262144; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec27[i] = 0;
	for (int i=0; i<2; i++) fRec28[i] = 0;
	for (int i=0; i<2; i++) fRec29[i] = 0;
	for (int i=0; i<2; i++) fRec30[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) iRec16[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) fRec40[i] = 0;
	for (int i=0; i<3; i++) fRec39[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec38[i] = 0;
	for (int i=0; i<3; i++) fRec37[i] = 0;
	for (int i=0; i<3; i++) fRec36[i] = 0;
	for (int i=0; i<2; i++) fRec41[i] = 0;
	for (int i=0; i<262144; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec42[i] = 0;
	for (int i=0; i<2; i++) fRec43[i] = 0;
	for (int i=0; i<2; i++) fRec44[i] = 0;
	for (int i=0; i<2; i++) fRec45[i] = 0;
	for (int i=0; i<2; i++) fRec35[i] = 0;
	for (int i=0; i<2; i++) fRec31[i] = 0;
	for (int i=0; i<2; i++) iRec32[i] = 0;
	for (int i=0; i<2; i++) fRec33[i] = 0;
	for (int i=0; i<2; i++) fRec54[i] = 0;
	for (int i=0; i<3; i++) fRec53[i] = 0;
	for (int i=0; i<2; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec52[i] = 0;
	for (int i=0; i<3; i++) fRec51[i] = 0;
	for (int i=0; i<2; i++) fRec55[i] = 0;
	for (int i=0; i<262144; i++) fVec7[i] = 0;
	for (int i=0; i<2; i++) fRec56[i] = 0;
	for (int i=0; i<2; i++) fRec57[i] = 0;
	for (int i=0; i<2; i++) fRec58[i] = 0;
	for (int i=0; i<2; i++) fRec59[i] = 0;
	for (int i=0; i<2; i++) fRec50[i] = 0;
	for (int i=0; i<2; i++) fRec46[i] = 0;
	for (int i=0; i<2; i++) iRec47[i] = 0;
	for (int i=0; i<2; i++) fRec48[i] = 0;
	for (int i=0; i<2; i++) fRec66[i] = 0;
	for (int i=0; i<3; i++) fRec65[i] = 0;
	for (int i=0; i<2; i++) fRec67[i] = 0;
	for (int i=0; i<262144; i++) fVec8[i] = 0;
	for (int i=0; i<2; i++) fRec68[i] = 0;
	for (int i=0; i<2; i++) fRec69[i] = 0;
	for (int i=0; i<2; i++) fRec70[i] = 0;
	for (int i=0; i<2; i++) fRec71[i] = 0;
	for (int i=0; i<2; i++) fRec64[i] = 0;
	for (int i=0; i<2; i++) fRec60[i] = 0;
	for (int i=0; i<2; i++) iRec61[i] = 0;
	for (int i=0; i<2; i++) fRec62[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (1.0 / double(iConst0));
	fConst2 = (3.141592653589793 / double(iConst0));
	IOTA = 0;
	fConst3 = (1e+01 / double(iConst0));
	fConst4 = (0 - fConst3);
	iConst5 = (60 * iConst0);
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void Dsp::mem_alloc()
{
	if (!fVec1) fVec1 = new double[262144];
	if (!fVec3) fVec3 = new double[262144];
	if (!fVec5) fVec5 = new double[262144];
	if (!fVec7) fVec7 = new double[262144];
	if (!fVec8) fVec8 = new double[262144];
	mem_allocated = true;
}

void Dsp::mem_free()
{
	mem_allocated = false;
	if (fVec1) { delete fVec1; fVec1 = 0; }
	if (fVec3) { delete fVec3; fVec3 = 0; }
	if (fVec5) { delete fVec5; fVec5 = 0; }
	if (fVec7) { delete fVec7; fVec7 = 0; }
	if (fVec8) { delete fVec8; fVec8 = 0; }
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

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
#define fslider2 (*fslider2_)
#define fslider3 (*fslider3_)
#define fslider4 (*fslider4_)
#define fslider5 (*fslider5_)
#define fslider6 (*fslider6_)
#define fbargraph0 (*fbargraph0_)
#define fslider7 (*fslider7_)
#define fslider8 (*fslider8_)
#define fslider9 (*fslider9_)
#define fbargraph1 (*fbargraph1_)
#define fslider10 (*fslider10_)
#define fslider11 (*fslider11_)
#define fslider12 (*fslider12_)
#define fbargraph2 (*fbargraph2_)
#define fslider13 (*fslider13_)
#define fslider14 (*fslider14_)
#define fslider15 (*fslider15_)
#define fbargraph3 (*fbargraph3_)
#define fslider16 (*fslider16_)
#define fslider17 (*fslider17_)
#define fslider18 (*fslider18_)
#define fbargraph4 (*fbargraph4_)
	double 	fSlow0 = tan((fConst2 * double(fslider0)));
	double 	fSlow1 = (1.0 / faustpower<2>(fSlow0));
	double 	fSlow2 = (2 * (1 - fSlow1));
	double 	fSlow3 = (1.0 / fSlow0);
	double 	fSlow4 = (1 + ((fSlow3 - 1.0) / fSlow0));
	double 	fSlow5 = (1.0 / (1 + ((1.0 + fSlow3) / fSlow0)));
	double 	fSlow6 = tan((fConst2 * double(fslider1)));
	double 	fSlow7 = (1.0 / faustpower<2>(fSlow6));
	double 	fSlow8 = (2 * (1 - fSlow7));
	double 	fSlow9 = (1.0 / fSlow6);
	double 	fSlow10 = (1 + ((fSlow9 - 1.0) / fSlow6));
	double 	fSlow11 = (1.0 / (1 + ((1.0 + fSlow9) / fSlow6)));
	double 	fSlow12 = tan((fConst2 * double(fslider2)));
	double 	fSlow13 = (1.0 / faustpower<2>(fSlow12));
	double 	fSlow14 = (2 * (1 - fSlow13));
	double 	fSlow15 = (1.0 / fSlow12);
	double 	fSlow16 = (1 + ((fSlow15 - 1.0) / fSlow12));
	double 	fSlow17 = (1.0 / (1 + ((1.0 + fSlow15) / fSlow12)));
	double 	fSlow18 = tan((fConst2 * double(fslider3)));
	double 	fSlow19 = (1.0 / faustpower<2>(fSlow18));
	double 	fSlow20 = (2 * (1 - fSlow19));
	double 	fSlow21 = (1.0 / fSlow18);
	double 	fSlow22 = (1 + ((fSlow21 - 1.0000000000000004) / fSlow18));
	double 	fSlow23 = (1 + ((1.0000000000000004 + fSlow21) / fSlow18));
	double 	fSlow24 = (1.0 / fSlow23);
	double 	fSlow25 = (0 - fSlow21);
	double 	fSlow26 = (1 + fSlow21);
	double 	fSlow27 = (1.0 / fSlow26);
	double 	fSlow28 = (0 - ((1 - fSlow21) / fSlow26));
	double 	fSlow29 = (2 * (0 - fSlow19));
	double 	fSlow30 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider4))));
	double 	fSlow31 = (0.01 * double(fslider5));
	double 	fSlow32 = (double(iConst5) / double(fslider6));
	double 	fSlow33 = (1 + ((fSlow15 - 1.0000000000000004) / fSlow12));
	double 	fSlow34 = (1 + ((fSlow15 + 1.0000000000000004) / fSlow12));
	double 	fSlow35 = (1.0 / fSlow34);
	double 	fSlow36 = (0 - fSlow15);
	double 	fSlow37 = (1.0 / (fSlow12 * fSlow23));
	double 	fSlow38 = (1 + fSlow15);
	double 	fSlow39 = (1.0 / fSlow38);
	double 	fSlow40 = (0 - ((1 - fSlow15) / fSlow38));
	double 	fSlow41 = (2 * (0 - fSlow13));
	double 	fSlow42 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider7))));
	double 	fSlow43 = (0.01 * double(fslider8));
	double 	fSlow44 = (double(iConst5) / double(fslider9));
	double 	fSlow45 = (1 + ((fSlow9 - 1.0000000000000004) / fSlow6));
	double 	fSlow46 = (1 + ((fSlow9 + 1.0000000000000004) / fSlow6));
	double 	fSlow47 = (1.0 / fSlow46);
	double 	fSlow48 = (0 - fSlow9);
	double 	fSlow49 = (1.0 / (fSlow6 * fSlow34));
	double 	fSlow50 = (1 + fSlow9);
	double 	fSlow51 = (1.0 / fSlow50);
	double 	fSlow52 = (0 - ((1 - fSlow9) / fSlow50));
	double 	fSlow53 = (2 * (0 - fSlow7));
	double 	fSlow54 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider10))));
	double 	fSlow55 = (0.01 * double(fslider11));
	double 	fSlow56 = (double(iConst5) / double(fslider12));
	double 	fSlow57 = (1 + ((fSlow3 - 1.0000000000000004) / fSlow0));
	double 	fSlow58 = (1.0 / (1 + ((fSlow3 + 1.0000000000000004) / fSlow0)));
	double 	fSlow59 = (0 - fSlow3);
	double 	fSlow60 = (1.0 / (fSlow0 * fSlow46));
	double 	fSlow61 = (1 + fSlow3);
	double 	fSlow62 = (1.0 / fSlow61);
	double 	fSlow63 = (0 - ((1 - fSlow3) / fSlow61));
	double 	fSlow64 = (2 * (0 - fSlow1));
	double 	fSlow65 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider13))));
	double 	fSlow66 = (0.01 * double(fslider14));
	double 	fSlow67 = (double(iConst5) / double(fslider15));
	double 	fSlow68 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider16))));
	double 	fSlow69 = (0.01 * double(fslider17));
	double 	fSlow70 = (double(iConst5) / double(fslider18));
	for (int i=0; i<count; i++) {
		double fTemp0 = (fSlow2 * fRec5[1]);
		double fTemp1 = (fSlow8 * fRec6[1]);
		double fTemp2 = (fSlow14 * fRec7[1]);
		double fTemp3 = (double)input0[i];
		fVec0[0] = fTemp3;
		fRec9[0] = ((fSlow28 * fRec9[1]) + (fSlow27 * ((fSlow21 * fVec0[0]) + (fSlow25 * fVec0[1]))));
		fRec8[0] = (fRec9[0] - (fSlow24 * ((fSlow22 * fRec8[2]) + (fSlow20 * fRec8[1]))));
		fRec7[0] = ((fSlow24 * (((fSlow19 * fRec8[0]) + (fSlow29 * fRec8[1])) + (fSlow19 * fRec8[2]))) - (fSlow17 * ((fSlow16 * fRec7[2]) + fTemp2)));
		fRec6[0] = ((fRec7[2] + (fSlow17 * (fTemp2 + (fSlow16 * fRec7[0])))) - (fSlow11 * ((fSlow10 * fRec6[2]) + fTemp1)));
		fRec5[0] = ((fRec6[2] + (fSlow11 * (fTemp1 + (fSlow10 * fRec6[0])))) - (fSlow5 * ((fSlow4 * fRec5[2]) + fTemp0)));
		fRec10[0] = (fSlow30 + (0.999 * fRec10[1]));
		double fTemp4 = ((fSlow31 * fRec4[1]) + (fRec10[0] * (fRec5[2] + (fSlow5 * (fTemp0 + (fSlow4 * fRec5[0]))))));
		fVec1[IOTA&262143] = fTemp4;
		double fTemp5 = ((int((fRec11[1] != 0.0)))?((int(((fRec12[1] > 0.0) & (fRec12[1] < 1.0))))?fRec11[1]:0):((int(((fRec12[1] == 0.0) & (fSlow32 != fRec13[1]))))?fConst3:((int(((fRec12[1] == 1.0) & (fSlow32 != fRec14[1]))))?fConst4:0)));
		fRec11[0] = fTemp5;
		fRec12[0] = max(0.0, min(1.0, (fRec12[1] + fTemp5)));
		fRec13[0] = ((int(((fRec12[1] >= 1.0) & (fRec14[1] != fSlow32))))?fSlow32:fRec13[1]);
		fRec14[0] = ((int(((fRec12[1] <= 0.0) & (fRec13[1] != fSlow32))))?fSlow32:fRec14[1]);
		fRec4[0] = (((1.0 - fRec12[0]) * fVec1[(IOTA-int((int(fRec13[0]) & 262143)))&262143]) + (fRec12[0] * fVec1[(IOTA-int((int(fRec14[0]) & 262143)))&262143]));
		double 	fRec3 = max(fConst1, fabs(fRec4[0]));
		int iTemp6 = int((iRec1[1] < 4096));
		fRec0[0] = ((iTemp6)?max(fRec0[1], fRec3):fRec3);
		iRec1[0] = ((iTemp6)?(1 + iRec1[1]):1);
		fRec2[0] = ((iTemp6)?fRec2[1]:fRec0[1]);
		fbargraph0 = fRec2[0];
		double fTemp7 = (fSlow2 * fRec20[1]);
		double fTemp8 = (fSlow8 * fRec21[1]);
		fRec25[0] = ((fSlow28 * fRec25[1]) + (fSlow27 * (fVec0[0] + fVec0[1])));
		fRec24[0] = (fRec25[0] - (fSlow24 * ((fSlow22 * fRec24[2]) + (fSlow20 * fRec24[1]))));
		double fTemp9 = (fRec24[2] + (fRec24[0] + (2 * fRec24[1])));
		double fTemp10 = (fSlow24 * fTemp9);
		fVec2[0] = fTemp10;
		fRec23[0] = ((fSlow40 * fRec23[1]) + (fSlow39 * ((fSlow37 * fTemp9) + (fSlow36 * fVec2[1]))));
		fRec22[0] = (fRec23[0] - (fSlow35 * ((fSlow33 * fRec22[2]) + (fSlow14 * fRec22[1]))));
		fRec21[0] = ((fSlow35 * (((fSlow13 * fRec22[0]) + (fSlow41 * fRec22[1])) + (fSlow13 * fRec22[2]))) - (fSlow11 * ((fSlow10 * fRec21[2]) + fTemp8)));
		fRec20[0] = ((fRec21[2] + (fSlow11 * (fTemp8 + (fSlow10 * fRec21[0])))) - (fSlow5 * ((fSlow4 * fRec20[2]) + fTemp7)));
		fRec26[0] = (fSlow42 + (0.999 * fRec26[1]));
		double fTemp11 = ((fSlow43 * fRec19[1]) + (fRec26[0] * (fRec20[2] + (fSlow5 * (fTemp7 + (fSlow4 * fRec20[0]))))));
		fVec3[IOTA&262143] = fTemp11;
		double fTemp12 = ((int((fRec27[1] != 0.0)))?((int(((fRec28[1] > 0.0) & (fRec28[1] < 1.0))))?fRec27[1]:0):((int(((fRec28[1] == 0.0) & (fSlow44 != fRec29[1]))))?fConst3:((int(((fRec28[1] == 1.0) & (fSlow44 != fRec30[1]))))?fConst4:0)));
		fRec27[0] = fTemp12;
		fRec28[0] = max(0.0, min(1.0, (fRec28[1] + fTemp12)));
		fRec29[0] = ((int(((fRec28[1] >= 1.0) & (fRec30[1] != fSlow44))))?fSlow44:fRec29[1]);
		fRec30[0] = ((int(((fRec28[1] <= 0.0) & (fRec29[1] != fSlow44))))?fSlow44:fRec30[1]);
		fRec19[0] = (((1.0 - fRec28[0]) * fVec3[(IOTA-int((int(fRec29[0]) & 262143)))&262143]) + (fRec28[0] * fVec3[(IOTA-int((int(fRec30[0]) & 262143)))&262143]));
		double 	fRec18 = max(fConst1, fabs(fRec19[0]));
		int iTemp13 = int((iRec16[1] < 4096));
		fRec15[0] = ((iTemp13)?max(fRec15[1], fRec18):fRec18);
		iRec16[0] = ((iTemp13)?(1 + iRec16[1]):1);
		fRec17[0] = ((iTemp13)?fRec17[1]:fRec15[1]);
		fbargraph1 = fRec17[0];
		double fTemp14 = (fSlow2 * fRec36[1]);
		fRec40[0] = ((fSlow40 * fRec40[1]) + (fSlow39 * (fVec2[0] + fVec2[1])));
		fRec39[0] = (fRec40[0] - (fSlow35 * ((fSlow33 * fRec39[2]) + (fSlow14 * fRec39[1]))));
		double fTemp15 = (fRec39[2] + (fRec39[0] + (2 * fRec39[1])));
		double fTemp16 = (fSlow35 * fTemp15);
		fVec4[0] = fTemp16;
		fRec38[0] = ((fSlow52 * fRec38[1]) + (fSlow51 * ((fSlow49 * fTemp15) + (fSlow48 * fVec4[1]))));
		fRec37[0] = (fRec38[0] - (fSlow47 * ((fSlow45 * fRec37[2]) + (fSlow8 * fRec37[1]))));
		fRec36[0] = ((fSlow47 * (((fSlow7 * fRec37[0]) + (fSlow53 * fRec37[1])) + (fSlow7 * fRec37[2]))) - (fSlow5 * ((fSlow4 * fRec36[2]) + fTemp14)));
		fRec41[0] = (fSlow54 + (0.999 * fRec41[1]));
		double fTemp17 = ((fSlow55 * fRec35[1]) + (fRec41[0] * (fRec36[2] + (fSlow5 * (fTemp14 + (fSlow4 * fRec36[0]))))));
		fVec5[IOTA&262143] = fTemp17;
		double fTemp18 = ((int((fRec42[1] != 0.0)))?((int(((fRec43[1] > 0.0) & (fRec43[1] < 1.0))))?fRec42[1]:0):((int(((fRec43[1] == 0.0) & (fSlow56 != fRec44[1]))))?fConst3:((int(((fRec43[1] == 1.0) & (fSlow56 != fRec45[1]))))?fConst4:0)));
		fRec42[0] = fTemp18;
		fRec43[0] = max(0.0, min(1.0, (fRec43[1] + fTemp18)));
		fRec44[0] = ((int(((fRec43[1] >= 1.0) & (fRec45[1] != fSlow56))))?fSlow56:fRec44[1]);
		fRec45[0] = ((int(((fRec43[1] <= 0.0) & (fRec44[1] != fSlow56))))?fSlow56:fRec45[1]);
		fRec35[0] = (((1.0 - fRec43[0]) * fVec5[(IOTA-int((int(fRec44[0]) & 262143)))&262143]) + (fRec43[0] * fVec5[(IOTA-int((int(fRec45[0]) & 262143)))&262143]));
		double 	fRec34 = max(fConst1, fabs(fRec35[0]));
		int iTemp19 = int((iRec32[1] < 4096));
		fRec31[0] = ((iTemp19)?max(fRec31[1], fRec34):fRec34);
		iRec32[0] = ((iTemp19)?(1 + iRec32[1]):1);
		fRec33[0] = ((iTemp19)?fRec33[1]:fRec31[1]);
		fbargraph2 = fRec33[0];
		fRec54[0] = ((fSlow52 * fRec54[1]) + (fSlow51 * (fVec4[0] + fVec4[1])));
		fRec53[0] = (fRec54[0] - (fSlow47 * ((fSlow45 * fRec53[2]) + (fSlow8 * fRec53[1]))));
		double fTemp20 = (fRec53[2] + (fRec53[0] + (2 * fRec53[1])));
		double fTemp21 = (fSlow47 * fTemp20);
		fVec6[0] = fTemp21;
		fRec52[0] = ((fSlow63 * fRec52[1]) + (fSlow62 * ((fSlow60 * fTemp20) + (fSlow59 * fVec6[1]))));
		fRec51[0] = (fRec52[0] - (fSlow58 * ((fSlow57 * fRec51[2]) + (fSlow2 * fRec51[1]))));
		fRec55[0] = (fSlow65 + (0.999 * fRec55[1]));
		double fTemp22 = ((fSlow66 * fRec50[1]) + (fSlow58 * (fRec55[0] * (((fSlow1 * fRec51[0]) + (fSlow64 * fRec51[1])) + (fSlow1 * fRec51[2])))));
		fVec7[IOTA&262143] = fTemp22;
		double fTemp23 = ((int((fRec56[1] != 0.0)))?((int(((fRec57[1] > 0.0) & (fRec57[1] < 1.0))))?fRec56[1]:0):((int(((fRec57[1] == 0.0) & (fSlow67 != fRec58[1]))))?fConst3:((int(((fRec57[1] == 1.0) & (fSlow67 != fRec59[1]))))?fConst4:0)));
		fRec56[0] = fTemp23;
		fRec57[0] = max(0.0, min(1.0, (fRec57[1] + fTemp23)));
		fRec58[0] = ((int(((fRec57[1] >= 1.0) & (fRec59[1] != fSlow67))))?fSlow67:fRec58[1]);
		fRec59[0] = ((int(((fRec57[1] <= 0.0) & (fRec58[1] != fSlow67))))?fSlow67:fRec59[1]);
		fRec50[0] = (((1.0 - fRec57[0]) * fVec7[(IOTA-int((int(fRec58[0]) & 262143)))&262143]) + (fRec57[0] * fVec7[(IOTA-int((int(fRec59[0]) & 262143)))&262143]));
		double 	fRec49 = max(fConst1, fabs(fRec50[0]));
		int iTemp24 = int((iRec47[1] < 4096));
		fRec46[0] = ((iTemp24)?max(fRec46[1], fRec49):fRec49);
		iRec47[0] = ((iTemp24)?(1 + iRec47[1]):1);
		fRec48[0] = ((iTemp24)?fRec48[1]:fRec46[1]);
		fbargraph3 = fRec48[0];
		fRec66[0] = ((fSlow63 * fRec66[1]) + (fSlow62 * (fVec6[0] + fVec6[1])));
		fRec65[0] = (fRec66[0] - (fSlow58 * ((fSlow57 * fRec65[2]) + (fSlow2 * fRec65[1]))));
		fRec67[0] = (fSlow68 + (0.999 * fRec67[1]));
		double fTemp25 = ((fSlow69 * fRec64[1]) + (fSlow58 * (fRec67[0] * (fRec65[2] + (fRec65[0] + (2 * fRec65[1]))))));
		fVec8[IOTA&262143] = fTemp25;
		double fTemp26 = ((int((fRec68[1] != 0.0)))?((int(((fRec69[1] > 0.0) & (fRec69[1] < 1.0))))?fRec68[1]:0):((int(((fRec69[1] == 0.0) & (fSlow70 != fRec70[1]))))?fConst3:((int(((fRec69[1] == 1.0) & (fSlow70 != fRec71[1]))))?fConst4:0)));
		fRec68[0] = fTemp26;
		fRec69[0] = max(0.0, min(1.0, (fRec69[1] + fTemp26)));
		fRec70[0] = ((int(((fRec69[1] >= 1.0) & (fRec71[1] != fSlow70))))?fSlow70:fRec70[1]);
		fRec71[0] = ((int(((fRec69[1] <= 0.0) & (fRec70[1] != fSlow70))))?fSlow70:fRec71[1]);
		fRec64[0] = (((1.0 - fRec69[0]) * fVec8[(IOTA-int((int(fRec70[0]) & 262143)))&262143]) + (fRec69[0] * fVec8[(IOTA-int((int(fRec71[0]) & 262143)))&262143]));
		double 	fRec63 = max(fConst1, fabs(fRec64[0]));
		int iTemp27 = int((iRec61[1] < 4096));
		fRec60[0] = ((iTemp27)?max(fRec60[1], fRec63):fRec63);
		iRec61[0] = ((iTemp27)?(1 + iRec61[1]):1);
		fRec62[0] = ((iTemp27)?fRec62[1]:fRec60[1]);
		fbargraph4 = fRec62[0];
		output0[i] = (FAUSTFLOAT)(fRec64[0] + (fRec50[0] + (fRec35[0] + (fRec19[0] + (fVec0[0] + fRec4[0])))));
		// post processing
		fRec62[1] = fRec62[0];
		iRec61[1] = iRec61[0];
		fRec60[1] = fRec60[0];
		fRec64[1] = fRec64[0];
		fRec71[1] = fRec71[0];
		fRec70[1] = fRec70[0];
		fRec69[1] = fRec69[0];
		fRec68[1] = fRec68[0];
		fRec67[1] = fRec67[0];
		fRec65[2] = fRec65[1]; fRec65[1] = fRec65[0];
		fRec66[1] = fRec66[0];
		fRec48[1] = fRec48[0];
		iRec47[1] = iRec47[0];
		fRec46[1] = fRec46[0];
		fRec50[1] = fRec50[0];
		fRec59[1] = fRec59[0];
		fRec58[1] = fRec58[0];
		fRec57[1] = fRec57[0];
		fRec56[1] = fRec56[0];
		fRec55[1] = fRec55[0];
		fRec51[2] = fRec51[1]; fRec51[1] = fRec51[0];
		fRec52[1] = fRec52[0];
		fVec6[1] = fVec6[0];
		fRec53[2] = fRec53[1]; fRec53[1] = fRec53[0];
		fRec54[1] = fRec54[0];
		fRec33[1] = fRec33[0];
		iRec32[1] = iRec32[0];
		fRec31[1] = fRec31[0];
		fRec35[1] = fRec35[0];
		fRec45[1] = fRec45[0];
		fRec44[1] = fRec44[0];
		fRec43[1] = fRec43[0];
		fRec42[1] = fRec42[0];
		fRec41[1] = fRec41[0];
		fRec36[2] = fRec36[1]; fRec36[1] = fRec36[0];
		fRec37[2] = fRec37[1]; fRec37[1] = fRec37[0];
		fRec38[1] = fRec38[0];
		fVec4[1] = fVec4[0];
		fRec39[2] = fRec39[1]; fRec39[1] = fRec39[0];
		fRec40[1] = fRec40[0];
		fRec17[1] = fRec17[0];
		iRec16[1] = iRec16[0];
		fRec15[1] = fRec15[0];
		fRec19[1] = fRec19[0];
		fRec30[1] = fRec30[0];
		fRec29[1] = fRec29[0];
		fRec28[1] = fRec28[0];
		fRec27[1] = fRec27[0];
		fRec26[1] = fRec26[0];
		fRec20[2] = fRec20[1]; fRec20[1] = fRec20[0];
		fRec21[2] = fRec21[1]; fRec21[1] = fRec21[0];
		fRec22[2] = fRec22[1]; fRec22[1] = fRec22[0];
		fRec23[1] = fRec23[0];
		fVec2[1] = fVec2[0];
		fRec24[2] = fRec24[1]; fRec24[1] = fRec24[0];
		fRec25[1] = fRec25[0];
		fRec2[1] = fRec2[0];
		iRec1[1] = iRec1[0];
		fRec0[1] = fRec0[0];
		fRec4[1] = fRec4[0];
		fRec14[1] = fRec14[0];
		fRec13[1] = fRec13[0];
		fRec12[1] = fRec12[0];
		fRec11[1] = fRec11[0];
		IOTA = IOTA+1;
		fRec10[1] = fRec10[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
		fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
		fRec9[1] = fRec9[0];
		fVec0[1] = fVec0[0];
	}
#undef fslider0
#undef fslider1
#undef fslider2
#undef fslider3
#undef fslider4
#undef fslider5
#undef fslider6
#undef fbargraph0
#undef fslider7
#undef fslider8
#undef fslider9
#undef fbargraph1
#undef fslider10
#undef fslider11
#undef fslider12
#undef fbargraph2
#undef fslider13
#undef fslider14
#undef fslider15
#undef fbargraph3
#undef fslider16
#undef fslider17
#undef fslider18
#undef fbargraph4
}
		
void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case CROSSOVER_B1_B2: 
		fslider0_ = (float*)data; // , 8e+01, 2e+01, 2e+04, 1.08 
		break;
	case CROSSOVER_B2_B3: 
		fslider1_ = (float*)data; // , 2.1e+02, 2e+01, 2e+04, 1.08 
		break;
	case CROSSOVER_B3_B4: 
		fslider2_ = (float*)data; // , 1.7e+03, 2e+01, 2e+04, 1.08 
		break;
	case CROSSOVER_B4_B5: 
		fslider3_ = (float*)data; // , 5e+03, 2e+01, 2e+04, 1.08 
		break;
	case DELAY1: 
		fslider18_ = (float*)data; // , 3e+01, 24.0, 3.6e+02, 1.0 
		break;
	case DELAY2: 
		fslider15_ = (float*)data; // , 6e+01, 24.0, 3.6e+02, 1.0 
		break;
	case DELAY3: 
		fslider12_ = (float*)data; // , 9e+01, 24.0, 3.6e+02, 1.0 
		break;
	case DELAY4: 
		fslider9_ = (float*)data; // , 1.2e+02, 24.0, 3.6e+02, 1.0 
		break;
	case DELAY5: 
		fslider6_ = (float*)data; // , 1.5e+02, 24.0, 3.6e+02, 1.0 
		break;
	case FEEDBACK1: 
		fslider17_ = (float*)data; // , 5e+01, 1.0, 1e+02, 1.0 
		break;
	case FEEDBACK2: 
		fslider14_ = (float*)data; // , 5e+01, 1.0, 1e+02, 1.0 
		break;
	case FEEDBACK3: 
		fslider11_ = (float*)data; // , 5e+01, 1.0, 1e+02, 1.0 
		break;
	case FEEDBACK4: 
		fslider8_ = (float*)data; // , 5e+01, 1.0, 1e+02, 1.0 
		break;
	case FEEDBACK5: 
		fslider5_ = (float*)data; // , 5e+01, 1.0, 1e+02, 1.0 
		break;
	case GAIN1: 
		fslider16_ = (float*)data; // , -1e+01, -2e+01, 2e+01, 0.1 
		break;
	case GAIN2: 
		fslider13_ = (float*)data; // , -5.0, -2e+01, 2e+01, 0.1 
		break;
	case GAIN3: 
		fslider10_ = (float*)data; // , -2.0, -2e+01, 2e+01, 0.1 
		break;
	case GAIN4: 
		fslider7_ = (float*)data; // , 0.0, -2e+01, 2e+01, 0.1 
		break;
	case GAIN5: 
		fslider4_ = (float*)data; // , -1e+01, -2e+01, 2e+01, 0.1 
		break;
	case V1: 
		fbargraph4_ = (float*)data; // , -70.0, -70.0, 4.0, 0.00001 
		break;
	case V2: 
		fbargraph3_ = (float*)data; // , -70.0, -70.0, 4.0, 0.00001 
		break;
	case V3: 
		fbargraph2_ = (float*)data; // , -70.0, -70.0, 4.0, 0.00001 
		break;
	case V4: 
		fbargraph1_ = (float*)data; // , -70.0, -70.0, 4.0, 0.00001 
		break;
	case V5: 
		fbargraph0_ = (float*)data; // , -70.0, -70.0, 4.0, 0.00001 
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
   CROSSOVER_B1_B2, 
   CROSSOVER_B2_B3, 
   CROSSOVER_B3_B4, 
   CROSSOVER_B4_B5, 
   DELAY1, 
   DELAY2, 
   DELAY3, 
   DELAY4, 
   DELAY5, 
   FEEDBACK1, 
   FEEDBACK2, 
   FEEDBACK3, 
   FEEDBACK4, 
   FEEDBACK5, 
   GAIN1, 
   GAIN2, 
   GAIN3, 
   GAIN4, 
   GAIN5, 
   V1, 
   V2, 
   V3, 
   V4, 
   V5, 
} PortIndex;
*/

} // end namespace mbdel
