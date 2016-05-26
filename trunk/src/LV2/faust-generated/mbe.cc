// generated from file '../src/LV2/faust/mbe.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)


namespace mbe {

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
	double 	fRec12[2];
	double 	fRec11[3];
	double 	fVec1[2];
	double 	fRec10[2];
	double 	fRec9[3];
	double 	fVec2[2];
	double 	fRec8[2];
	double 	fRec7[3];
	double 	fVec3[2];
	double 	fRec6[2];
	double 	fRec5[3];
	double 	fConst3;
	double 	fConst4;
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT	*fslider4_;
	int 	iConst5;
	double 	fRec13[2];
	double 	fRec14[2];
	double 	fRec15[2];
	double 	fRec16[2];
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT	*fslider5_;
	double 	fRec17[2];
	int 	IOTA;
	double *fRec4;
	double 	fRec0[2];
	int 	iRec1[2];
	double 	fRec2[2];
	FAUSTFLOAT 	fbargraph0;
	FAUSTFLOAT	*fbargraph0_;
	double 	fRec24[2];
	double 	fRec23[3];
	FAUSTFLOAT 	fslider6;
	FAUSTFLOAT	*fslider6_;
	double 	fRec25[2];
	double 	fRec26[2];
	double 	fRec27[2];
	double 	fRec28[2];
	FAUSTFLOAT 	fslider7;
	FAUSTFLOAT	*fslider7_;
	double 	fRec29[2];
	double *fRec22;
	double 	fRec18[2];
	int 	iRec19[2];
	double 	fRec20[2];
	FAUSTFLOAT 	fbargraph1;
	FAUSTFLOAT	*fbargraph1_;
	double 	fRec37[2];
	double 	fRec36[3];
	double 	fRec35[3];
	FAUSTFLOAT 	fslider8;
	FAUSTFLOAT	*fslider8_;
	double 	fRec38[2];
	double 	fRec39[2];
	double 	fRec40[2];
	double 	fRec41[2];
	FAUSTFLOAT 	fslider9;
	FAUSTFLOAT	*fslider9_;
	double 	fRec42[2];
	double *fRec34;
	double 	fRec30[2];
	int 	iRec31[2];
	double 	fRec32[2];
	FAUSTFLOAT 	fbargraph2;
	FAUSTFLOAT	*fbargraph2_;
	double 	fRec51[2];
	double 	fRec50[3];
	double 	fRec49[3];
	double 	fRec48[3];
	FAUSTFLOAT 	fslider10;
	FAUSTFLOAT	*fslider10_;
	double 	fRec52[2];
	double 	fRec53[2];
	double 	fRec54[2];
	double 	fRec55[2];
	FAUSTFLOAT 	fslider11;
	FAUSTFLOAT	*fslider11_;
	double 	fRec56[2];
	double *fRec47;
	double 	fRec43[2];
	int 	iRec44[2];
	double 	fRec45[2];
	FAUSTFLOAT 	fbargraph3;
	FAUSTFLOAT	*fbargraph3_;
	double 	fRec66[2];
	double 	fRec65[3];
	double 	fRec64[3];
	double 	fRec63[3];
	double 	fRec62[3];
	FAUSTFLOAT 	fslider12;
	FAUSTFLOAT	*fslider12_;
	double 	fRec67[2];
	double 	fRec68[2];
	double 	fRec69[2];
	double 	fRec70[2];
	FAUSTFLOAT 	fslider13;
	FAUSTFLOAT	*fslider13_;
	double 	fRec71[2];
	double *fRec61;
	double 	fRec57[2];
	int 	iRec58[2];
	double 	fRec59[2];
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
	  fRec4(0),
	  fRec22(0),
	  fRec34(0),
	  fRec47(0),
	  fRec61(0),
	  mem_allocated(false) {
	version = PLUGINLV2_VERSION;
	id = "mbe";
	name = N_("MultiBand Echo");
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
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<3; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<3; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<3; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<524288; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) iRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<3; i++) fRec23[i] = 0;
	for (int i=0; i<2; i++) fRec25[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<2; i++) fRec27[i] = 0;
	for (int i=0; i<2; i++) fRec28[i] = 0;
	for (int i=0; i<2; i++) fRec29[i] = 0;
	for (int i=0; i<524288; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) iRec19[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec37[i] = 0;
	for (int i=0; i<3; i++) fRec36[i] = 0;
	for (int i=0; i<3; i++) fRec35[i] = 0;
	for (int i=0; i<2; i++) fRec38[i] = 0;
	for (int i=0; i<2; i++) fRec39[i] = 0;
	for (int i=0; i<2; i++) fRec40[i] = 0;
	for (int i=0; i<2; i++) fRec41[i] = 0;
	for (int i=0; i<2; i++) fRec42[i] = 0;
	for (int i=0; i<524288; i++) fRec34[i] = 0;
	for (int i=0; i<2; i++) fRec30[i] = 0;
	for (int i=0; i<2; i++) iRec31[i] = 0;
	for (int i=0; i<2; i++) fRec32[i] = 0;
	for (int i=0; i<2; i++) fRec51[i] = 0;
	for (int i=0; i<3; i++) fRec50[i] = 0;
	for (int i=0; i<3; i++) fRec49[i] = 0;
	for (int i=0; i<3; i++) fRec48[i] = 0;
	for (int i=0; i<2; i++) fRec52[i] = 0;
	for (int i=0; i<2; i++) fRec53[i] = 0;
	for (int i=0; i<2; i++) fRec54[i] = 0;
	for (int i=0; i<2; i++) fRec55[i] = 0;
	for (int i=0; i<2; i++) fRec56[i] = 0;
	for (int i=0; i<524288; i++) fRec47[i] = 0;
	for (int i=0; i<2; i++) fRec43[i] = 0;
	for (int i=0; i<2; i++) iRec44[i] = 0;
	for (int i=0; i<2; i++) fRec45[i] = 0;
	for (int i=0; i<2; i++) fRec66[i] = 0;
	for (int i=0; i<3; i++) fRec65[i] = 0;
	for (int i=0; i<3; i++) fRec64[i] = 0;
	for (int i=0; i<3; i++) fRec63[i] = 0;
	for (int i=0; i<3; i++) fRec62[i] = 0;
	for (int i=0; i<2; i++) fRec67[i] = 0;
	for (int i=0; i<2; i++) fRec68[i] = 0;
	for (int i=0; i<2; i++) fRec69[i] = 0;
	for (int i=0; i<2; i++) fRec70[i] = 0;
	for (int i=0; i<2; i++) fRec71[i] = 0;
	for (int i=0; i<524288; i++) fRec61[i] = 0;
	for (int i=0; i<2; i++) fRec57[i] = 0;
	for (int i=0; i<2; i++) iRec58[i] = 0;
	for (int i=0; i<2; i++) fRec59[i] = 0;
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
	fConst3 = (1e+01 / double(iConst0));
	fConst4 = (0 - fConst3);
	iConst5 = (60 * iConst0);
	IOTA = 0;
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void Dsp::mem_alloc()
{
	if (!fRec4) fRec4 = new double[524288];
	if (!fRec22) fRec22 = new double[524288];
	if (!fRec34) fRec34 = new double[524288];
	if (!fRec47) fRec47 = new double[524288];
	if (!fRec61) fRec61 = new double[524288];
	mem_allocated = true;
}

void Dsp::mem_free()
{
	mem_allocated = false;
	if (fRec4) { delete fRec4; fRec4 = 0; }
	if (fRec22) { delete fRec22; fRec22 = 0; }
	if (fRec34) { delete fRec34; fRec34 = 0; }
	if (fRec47) { delete fRec47; fRec47 = 0; }
	if (fRec61) { delete fRec61; fRec61 = 0; }
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
#define fbargraph0 (*fbargraph0_)
#define fslider6 (*fslider6_)
#define fslider7 (*fslider7_)
#define fbargraph1 (*fbargraph1_)
#define fslider8 (*fslider8_)
#define fslider9 (*fslider9_)
#define fbargraph2 (*fbargraph2_)
#define fslider10 (*fslider10_)
#define fslider11 (*fslider11_)
#define fbargraph3 (*fbargraph3_)
#define fslider12 (*fslider12_)
#define fslider13 (*fslider13_)
#define fbargraph4 (*fbargraph4_)
	double 	fSlow0 = tan((fConst2 * double(fslider0)));
	double 	fSlow1 = (1.0 / faustpower<2>(fSlow0));
	double 	fSlow2 = (2 * (1 - fSlow1));
	double 	fSlow3 = (1.0 / fSlow0);
	double 	fSlow4 = (1 + ((fSlow3 - 1.0000000000000004) / fSlow0));
	double 	fSlow5 = (1.0 / (1 + ((fSlow3 + 1.0000000000000004) / fSlow0)));
	double 	fSlow6 = tan((fConst2 * double(fslider1)));
	double 	fSlow7 = (1.0 / faustpower<2>(fSlow6));
	double 	fSlow8 = (2 * (1 - fSlow7));
	double 	fSlow9 = (1.0 / fSlow6);
	double 	fSlow10 = (1 + ((fSlow9 - 1.0000000000000004) / fSlow6));
	double 	fSlow11 = (1 + ((fSlow9 + 1.0000000000000004) / fSlow6));
	double 	fSlow12 = (1.0 / fSlow11);
	double 	fSlow13 = tan((fConst2 * double(fslider2)));
	double 	fSlow14 = (1.0 / faustpower<2>(fSlow13));
	double 	fSlow15 = (2 * (1 - fSlow14));
	double 	fSlow16 = (1.0 / fSlow13);
	double 	fSlow17 = (1 + ((fSlow16 - 1.0000000000000004) / fSlow13));
	double 	fSlow18 = (1 + ((fSlow16 + 1.0000000000000004) / fSlow13));
	double 	fSlow19 = (1.0 / fSlow18);
	double 	fSlow20 = tan((fConst2 * double(fslider3)));
	double 	fSlow21 = (1.0 / faustpower<2>(fSlow20));
	double 	fSlow22 = (2 * (1 - fSlow21));
	double 	fSlow23 = (1.0 / fSlow20);
	double 	fSlow24 = (1 + ((fSlow23 - 1.0000000000000004) / fSlow20));
	double 	fSlow25 = (1 + ((1.0000000000000004 + fSlow23) / fSlow20));
	double 	fSlow26 = (1.0 / fSlow25);
	double 	fSlow27 = (1 + fSlow23);
	double 	fSlow28 = (1.0 / fSlow27);
	double 	fSlow29 = (0 - ((1 - fSlow23) / fSlow27));
	double 	fSlow30 = (1 + fSlow16);
	double 	fSlow31 = (1.0 / fSlow30);
	double 	fSlow32 = (0 - ((1 - fSlow16) / fSlow30));
	double 	fSlow33 = (1 + fSlow9);
	double 	fSlow34 = (1.0 / fSlow33);
	double 	fSlow35 = (0 - ((1 - fSlow9) / fSlow33));
	double 	fSlow36 = (1 + fSlow3);
	double 	fSlow37 = (1.0 / fSlow36);
	double 	fSlow38 = (0 - ((1 - fSlow3) / fSlow36));
	double 	fSlow39 = (double(iConst5) / double(fslider4));
	double 	fSlow40 = (1.000000000000001e-05 * double(fslider5));
	double 	fSlow41 = (0 - fSlow3);
	double 	fSlow42 = (1.0 / (fSlow0 * fSlow11));
	double 	fSlow43 = (2 * (0 - fSlow1));
	double 	fSlow44 = (double(iConst5) / double(fslider6));
	double 	fSlow45 = (1.000000000000001e-05 * double(fslider7));
	double 	fSlow46 = (1 + ((fSlow3 - 1.0) / fSlow0));
	double 	fSlow47 = (1.0 / (1 + ((1.0 + fSlow3) / fSlow0)));
	double 	fSlow48 = (0 - fSlow9);
	double 	fSlow49 = (1.0 / (fSlow6 * fSlow18));
	double 	fSlow50 = (2 * (0 - fSlow7));
	double 	fSlow51 = (double(iConst5) / double(fslider8));
	double 	fSlow52 = (1.000000000000001e-05 * double(fslider9));
	double 	fSlow53 = (1 + ((fSlow9 - 1.0) / fSlow6));
	double 	fSlow54 = (1.0 / (1 + ((1.0 + fSlow9) / fSlow6)));
	double 	fSlow55 = (0 - fSlow16);
	double 	fSlow56 = (1.0 / (fSlow13 * fSlow25));
	double 	fSlow57 = (2 * (0 - fSlow14));
	double 	fSlow58 = (double(iConst5) / double(fslider10));
	double 	fSlow59 = (1.000000000000001e-05 * double(fslider11));
	double 	fSlow60 = (1 + ((fSlow16 - 1.0) / fSlow13));
	double 	fSlow61 = (1.0 / (1 + ((1.0 + fSlow16) / fSlow13)));
	double 	fSlow62 = (0 - fSlow23);
	double 	fSlow63 = (2 * (0 - fSlow21));
	double 	fSlow64 = (double(iConst5) / double(fslider12));
	double 	fSlow65 = (1.000000000000001e-05 * double(fslider13));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fVec0[0] = fTemp0;
		fRec12[0] = ((fSlow29 * fRec12[1]) + (fSlow28 * (fVec0[0] + fVec0[1])));
		fRec11[0] = (fRec12[0] - (fSlow26 * ((fSlow24 * fRec11[2]) + (fSlow22 * fRec11[1]))));
		double fTemp1 = (fRec11[2] + (fRec11[0] + (2 * fRec11[1])));
		double fTemp2 = (fSlow26 * fTemp1);
		fVec1[0] = fTemp2;
		fRec10[0] = ((fSlow32 * fRec10[1]) + (fSlow31 * (fVec1[0] + fVec1[1])));
		fRec9[0] = (fRec10[0] - (fSlow19 * ((fSlow17 * fRec9[2]) + (fSlow15 * fRec9[1]))));
		double fTemp3 = (fRec9[2] + (fRec9[0] + (2 * fRec9[1])));
		double fTemp4 = (fSlow19 * fTemp3);
		fVec2[0] = fTemp4;
		fRec8[0] = ((fSlow35 * fRec8[1]) + (fSlow34 * (fVec2[0] + fVec2[1])));
		fRec7[0] = (fRec8[0] - (fSlow12 * ((fSlow10 * fRec7[2]) + (fSlow8 * fRec7[1]))));
		double fTemp5 = (fRec7[2] + (fRec7[0] + (2 * fRec7[1])));
		double fTemp6 = (fSlow12 * fTemp5);
		fVec3[0] = fTemp6;
		fRec6[0] = ((fSlow38 * fRec6[1]) + (fSlow37 * (fVec3[0] + fVec3[1])));
		fRec5[0] = (fRec6[0] - (fSlow5 * ((fSlow4 * fRec5[2]) + (fSlow2 * fRec5[1]))));
		double fTemp7 = ((int((fRec13[1] != 0.0)))?((int(((fRec14[1] > 0.0) & (fRec14[1] < 1.0))))?fRec13[1]:0):((int(((fRec14[1] == 0.0) & (fSlow39 != fRec15[1]))))?fConst3:((int(((fRec14[1] == 1.0) & (fSlow39 != fRec16[1]))))?fConst4:0)));
		fRec13[0] = fTemp7;
		fRec14[0] = max(0.0, min(1.0, (fRec14[1] + fTemp7)));
		fRec15[0] = ((int(((fRec14[1] >= 1.0) & (fRec16[1] != fSlow39))))?fSlow39:fRec15[1]);
		fRec16[0] = ((int(((fRec14[1] <= 0.0) & (fRec15[1] != fSlow39))))?fSlow39:fRec16[1]);
		fRec17[0] = (fSlow40 + (0.999 * fRec17[1]));
		fRec4[IOTA&524287] = ((fRec17[0] * (((1.0 - fRec14[0]) * fRec4[(IOTA-int((1 + int((int(fRec15[0]) & 262143)))))&524287]) + (fRec14[0] * fRec4[(IOTA-int((1 + int((int(fRec16[0]) & 262143)))))&524287]))) + (fSlow5 * (fRec5[2] + (fRec5[0] + (2 * fRec5[1])))));
		double fTemp8 = fRec4[(IOTA-0)&524287];
		double 	fRec3 = max(fConst1, fabs(fTemp8));
		int iTemp9 = int((iRec1[1] < 4096));
		fRec0[0] = ((iTemp9)?max(fRec0[1], fRec3):fRec3);
		iRec1[0] = ((iTemp9)?(1 + iRec1[1]):1);
		fRec2[0] = ((iTemp9)?fRec2[1]:fRec0[1]);
		fbargraph0 = fRec2[0];
		fRec24[0] = ((fSlow38 * fRec24[1]) + (fSlow37 * ((fSlow42 * fTemp5) + (fSlow41 * fVec3[1]))));
		fRec23[0] = (fRec24[0] - (fSlow5 * ((fSlow4 * fRec23[2]) + (fSlow2 * fRec23[1]))));
		double fTemp10 = ((int((fRec25[1] != 0.0)))?((int(((fRec26[1] > 0.0) & (fRec26[1] < 1.0))))?fRec25[1]:0):((int(((fRec26[1] == 0.0) & (fSlow44 != fRec27[1]))))?fConst3:((int(((fRec26[1] == 1.0) & (fSlow44 != fRec28[1]))))?fConst4:0)));
		fRec25[0] = fTemp10;
		fRec26[0] = max(0.0, min(1.0, (fRec26[1] + fTemp10)));
		fRec27[0] = ((int(((fRec26[1] >= 1.0) & (fRec28[1] != fSlow44))))?fSlow44:fRec27[1]);
		fRec28[0] = ((int(((fRec26[1] <= 0.0) & (fRec27[1] != fSlow44))))?fSlow44:fRec28[1]);
		fRec29[0] = (fSlow45 + (0.999 * fRec29[1]));
		fRec22[IOTA&524287] = ((fRec29[0] * (((1.0 - fRec26[0]) * fRec22[(IOTA-int((1 + int((int(fRec27[0]) & 262143)))))&524287]) + (fRec26[0] * fRec22[(IOTA-int((1 + int((int(fRec28[0]) & 262143)))))&524287]))) + (fSlow5 * (((fSlow1 * fRec23[0]) + (fSlow43 * fRec23[1])) + (fSlow1 * fRec23[2]))));
		double fTemp11 = fRec22[(IOTA-0)&524287];
		double 	fRec21 = max(fConst1, fabs(fTemp11));
		int iTemp12 = int((iRec19[1] < 4096));
		fRec18[0] = ((iTemp12)?max(fRec18[1], fRec21):fRec21);
		iRec19[0] = ((iTemp12)?(1 + iRec19[1]):1);
		fRec20[0] = ((iTemp12)?fRec20[1]:fRec18[1]);
		fbargraph1 = fRec20[0];
		double fTemp13 = (fSlow2 * fRec35[1]);
		fRec37[0] = ((fSlow35 * fRec37[1]) + (fSlow34 * ((fSlow49 * fTemp3) + (fSlow48 * fVec2[1]))));
		fRec36[0] = (fRec37[0] - (fSlow12 * ((fSlow10 * fRec36[2]) + (fSlow8 * fRec36[1]))));
		fRec35[0] = ((fSlow12 * (((fSlow7 * fRec36[0]) + (fSlow50 * fRec36[1])) + (fSlow7 * fRec36[2]))) - (fSlow47 * ((fSlow46 * fRec35[2]) + fTemp13)));
		double fTemp14 = ((int((fRec38[1] != 0.0)))?((int(((fRec39[1] > 0.0) & (fRec39[1] < 1.0))))?fRec38[1]:0):((int(((fRec39[1] == 0.0) & (fSlow51 != fRec40[1]))))?fConst3:((int(((fRec39[1] == 1.0) & (fSlow51 != fRec41[1]))))?fConst4:0)));
		fRec38[0] = fTemp14;
		fRec39[0] = max(0.0, min(1.0, (fRec39[1] + fTemp14)));
		fRec40[0] = ((int(((fRec39[1] >= 1.0) & (fRec41[1] != fSlow51))))?fSlow51:fRec40[1]);
		fRec41[0] = ((int(((fRec39[1] <= 0.0) & (fRec40[1] != fSlow51))))?fSlow51:fRec41[1]);
		fRec42[0] = (fSlow52 + (0.999 * fRec42[1]));
		fRec34[IOTA&524287] = ((fSlow47 * (fTemp13 + (fSlow46 * fRec35[0]))) + ((fRec42[0] * (((1.0 - fRec39[0]) * fRec34[(IOTA-int((1 + int((int(fRec40[0]) & 262143)))))&524287]) + (fRec39[0] * fRec34[(IOTA-int((1 + int((int(fRec41[0]) & 262143)))))&524287]))) + fRec35[2]));
		double fTemp15 = fRec34[(IOTA-0)&524287];
		double 	fRec33 = max(fConst1, fabs(fTemp15));
		int iTemp16 = int((iRec31[1] < 4096));
		fRec30[0] = ((iTemp16)?max(fRec30[1], fRec33):fRec33);
		iRec31[0] = ((iTemp16)?(1 + iRec31[1]):1);
		fRec32[0] = ((iTemp16)?fRec32[1]:fRec30[1]);
		fbargraph2 = fRec32[0];
		double fTemp17 = (fSlow2 * fRec48[1]);
		double fTemp18 = (fSlow8 * fRec49[1]);
		fRec51[0] = ((fSlow32 * fRec51[1]) + (fSlow31 * ((fSlow56 * fTemp1) + (fSlow55 * fVec1[1]))));
		fRec50[0] = (fRec51[0] - (fSlow19 * ((fSlow17 * fRec50[2]) + (fSlow15 * fRec50[1]))));
		fRec49[0] = ((fSlow19 * (((fSlow14 * fRec50[0]) + (fSlow57 * fRec50[1])) + (fSlow14 * fRec50[2]))) - (fSlow54 * ((fSlow53 * fRec49[2]) + fTemp18)));
		fRec48[0] = ((fRec49[2] + (fSlow54 * (fTemp18 + (fSlow53 * fRec49[0])))) - (fSlow47 * ((fSlow46 * fRec48[2]) + fTemp17)));
		double fTemp19 = ((int((fRec52[1] != 0.0)))?((int(((fRec53[1] > 0.0) & (fRec53[1] < 1.0))))?fRec52[1]:0):((int(((fRec53[1] == 0.0) & (fSlow58 != fRec54[1]))))?fConst3:((int(((fRec53[1] == 1.0) & (fSlow58 != fRec55[1]))))?fConst4:0)));
		fRec52[0] = fTemp19;
		fRec53[0] = max(0.0, min(1.0, (fRec53[1] + fTemp19)));
		fRec54[0] = ((int(((fRec53[1] >= 1.0) & (fRec55[1] != fSlow58))))?fSlow58:fRec54[1]);
		fRec55[0] = ((int(((fRec53[1] <= 0.0) & (fRec54[1] != fSlow58))))?fSlow58:fRec55[1]);
		fRec56[0] = (fSlow59 + (0.999 * fRec56[1]));
		fRec47[IOTA&524287] = ((fSlow47 * (fTemp17 + (fSlow46 * fRec48[0]))) + ((fRec56[0] * (((1.0 - fRec53[0]) * fRec47[(IOTA-int((1 + int((int(fRec54[0]) & 262143)))))&524287]) + (fRec53[0] * fRec47[(IOTA-int((1 + int((int(fRec55[0]) & 262143)))))&524287]))) + fRec48[2]));
		double fTemp20 = fRec47[(IOTA-0)&524287];
		double 	fRec46 = max(fConst1, fabs(fTemp20));
		int iTemp21 = int((iRec44[1] < 4096));
		fRec43[0] = ((iTemp21)?max(fRec43[1], fRec46):fRec46);
		iRec44[0] = ((iTemp21)?(1 + iRec44[1]):1);
		fRec45[0] = ((iTemp21)?fRec45[1]:fRec43[1]);
		fbargraph3 = fRec45[0];
		double fTemp22 = (fSlow2 * fRec62[1]);
		double fTemp23 = (fSlow8 * fRec63[1]);
		double fTemp24 = (fSlow15 * fRec64[1]);
		fRec66[0] = ((fSlow29 * fRec66[1]) + (fSlow28 * ((fSlow23 * fVec0[0]) + (fSlow62 * fVec0[1]))));
		fRec65[0] = (fRec66[0] - (fSlow26 * ((fSlow24 * fRec65[2]) + (fSlow22 * fRec65[1]))));
		fRec64[0] = ((fSlow26 * (((fSlow21 * fRec65[0]) + (fSlow63 * fRec65[1])) + (fSlow21 * fRec65[2]))) - (fSlow61 * ((fSlow60 * fRec64[2]) + fTemp24)));
		fRec63[0] = ((fRec64[2] + (fSlow61 * (fTemp24 + (fSlow60 * fRec64[0])))) - (fSlow54 * ((fSlow53 * fRec63[2]) + fTemp23)));
		fRec62[0] = ((fRec63[2] + (fSlow54 * (fTemp23 + (fSlow53 * fRec63[0])))) - (fSlow47 * ((fSlow46 * fRec62[2]) + fTemp22)));
		double fTemp25 = ((int((fRec67[1] != 0.0)))?((int(((fRec68[1] > 0.0) & (fRec68[1] < 1.0))))?fRec67[1]:0):((int(((fRec68[1] == 0.0) & (fSlow64 != fRec69[1]))))?fConst3:((int(((fRec68[1] == 1.0) & (fSlow64 != fRec70[1]))))?fConst4:0)));
		fRec67[0] = fTemp25;
		fRec68[0] = max(0.0, min(1.0, (fRec68[1] + fTemp25)));
		fRec69[0] = ((int(((fRec68[1] >= 1.0) & (fRec70[1] != fSlow64))))?fSlow64:fRec69[1]);
		fRec70[0] = ((int(((fRec68[1] <= 0.0) & (fRec69[1] != fSlow64))))?fSlow64:fRec70[1]);
		fRec71[0] = (fSlow65 + (0.999 * fRec71[1]));
		fRec61[IOTA&524287] = ((fSlow47 * (fTemp22 + (fSlow46 * fRec62[0]))) + ((fRec71[0] * (((1.0 - fRec68[0]) * fRec61[(IOTA-int((1 + int((int(fRec69[0]) & 262143)))))&524287]) + (fRec68[0] * fRec61[(IOTA-int((1 + int((int(fRec70[0]) & 262143)))))&524287]))) + fRec62[2]));
		double fTemp26 = fRec61[(IOTA-0)&524287];
		double 	fRec60 = max(fConst1, fabs(fTemp26));
		int iTemp27 = int((iRec58[1] < 4096));
		fRec57[0] = ((iTemp27)?max(fRec57[1], fRec60):fRec60);
		iRec58[0] = ((iTemp27)?(1 + iRec58[1]):1);
		fRec59[0] = ((iTemp27)?fRec59[1]:fRec57[1]);
		fbargraph4 = fRec59[0];
		output0[i] = (FAUSTFLOAT)((((fTemp26 + fTemp20) + fTemp15) + fTemp11) + fTemp8);
		// post processing
		fRec59[1] = fRec59[0];
		iRec58[1] = iRec58[0];
		fRec57[1] = fRec57[0];
		fRec71[1] = fRec71[0];
		fRec70[1] = fRec70[0];
		fRec69[1] = fRec69[0];
		fRec68[1] = fRec68[0];
		fRec67[1] = fRec67[0];
		fRec62[2] = fRec62[1]; fRec62[1] = fRec62[0];
		fRec63[2] = fRec63[1]; fRec63[1] = fRec63[0];
		fRec64[2] = fRec64[1]; fRec64[1] = fRec64[0];
		fRec65[2] = fRec65[1]; fRec65[1] = fRec65[0];
		fRec66[1] = fRec66[0];
		fRec45[1] = fRec45[0];
		iRec44[1] = iRec44[0];
		fRec43[1] = fRec43[0];
		fRec56[1] = fRec56[0];
		fRec55[1] = fRec55[0];
		fRec54[1] = fRec54[0];
		fRec53[1] = fRec53[0];
		fRec52[1] = fRec52[0];
		fRec48[2] = fRec48[1]; fRec48[1] = fRec48[0];
		fRec49[2] = fRec49[1]; fRec49[1] = fRec49[0];
		fRec50[2] = fRec50[1]; fRec50[1] = fRec50[0];
		fRec51[1] = fRec51[0];
		fRec32[1] = fRec32[0];
		iRec31[1] = iRec31[0];
		fRec30[1] = fRec30[0];
		fRec42[1] = fRec42[0];
		fRec41[1] = fRec41[0];
		fRec40[1] = fRec40[0];
		fRec39[1] = fRec39[0];
		fRec38[1] = fRec38[0];
		fRec35[2] = fRec35[1]; fRec35[1] = fRec35[0];
		fRec36[2] = fRec36[1]; fRec36[1] = fRec36[0];
		fRec37[1] = fRec37[0];
		fRec20[1] = fRec20[0];
		iRec19[1] = iRec19[0];
		fRec18[1] = fRec18[0];
		fRec29[1] = fRec29[0];
		fRec28[1] = fRec28[0];
		fRec27[1] = fRec27[0];
		fRec26[1] = fRec26[0];
		fRec25[1] = fRec25[0];
		fRec23[2] = fRec23[1]; fRec23[1] = fRec23[0];
		fRec24[1] = fRec24[0];
		fRec2[1] = fRec2[0];
		iRec1[1] = iRec1[0];
		fRec0[1] = fRec0[0];
		IOTA = IOTA+1;
		fRec17[1] = fRec17[0];
		fRec16[1] = fRec16[0];
		fRec15[1] = fRec15[0];
		fRec14[1] = fRec14[0];
		fRec13[1] = fRec13[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		fVec3[1] = fVec3[0];
		fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
		fVec2[1] = fVec2[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec10[1] = fRec10[0];
		fVec1[1] = fVec1[0];
		fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
		fRec12[1] = fRec12[0];
		fVec0[1] = fVec0[0];
	}
#undef fslider0
#undef fslider1
#undef fslider2
#undef fslider3
#undef fslider4
#undef fslider5
#undef fbargraph0
#undef fslider6
#undef fslider7
#undef fbargraph1
#undef fslider8
#undef fslider9
#undef fbargraph2
#undef fslider10
#undef fslider11
#undef fbargraph3
#undef fslider12
#undef fslider13
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
	case PERCENT1: 
		fslider5_ = (float*)data; // , 1e+01, 0.0, 1e+02, 0.1 
		break;
	case PERCENT2: 
		fslider7_ = (float*)data; // , 3e+01, 0.0, 1e+02, 0.1 
		break;
	case PERCENT3: 
		fslider9_ = (float*)data; // , 45.0, 0.0, 1e+02, 0.1 
		break;
	case PERCENT4: 
		fslider11_ = (float*)data; // , 2e+01, 0.0, 1e+02, 0.1 
		break;
	case PERCENT5: 
		fslider13_ = (float*)data; // , 0.0, 0.0, 1e+02, 0.1 
		break;
	case TIME1: 
		fslider4_ = (float*)data; // , 3e+01, 24.0, 3.6e+02, 1.0 
		break;
	case TIME2: 
		fslider6_ = (float*)data; // , 6e+01, 24.0, 3.6e+02, 1.0 
		break;
	case TIME3: 
		fslider8_ = (float*)data; // , 1.2e+02, 24.0, 3.6e+02, 1.0 
		break;
	case TIME4: 
		fslider10_ = (float*)data; // , 1.5e+02, 24.0, 3.6e+02, 1.0 
		break;
	case TIME5: 
		fslider12_ = (float*)data; // , 2.4e+02, 24.0, 3.6e+02, 1.0 
		break;
	case V1: 
		fbargraph0_ = (float*)data; // , -70.0, -70.0, 4.0, 0.00001 
		break;
	case V2: 
		fbargraph1_ = (float*)data; // , -70.0, -70.0, 4.0, 0.00001 
		break;
	case V3: 
		fbargraph2_ = (float*)data; // , -70.0, -70.0, 4.0, 0.00001 
		break;
	case V4: 
		fbargraph3_ = (float*)data; // , -70.0, -70.0, 4.0, 0.00001 
		break;
	case V5: 
		fbargraph4_ = (float*)data; // , -70.0, -70.0, 4.0, 0.00001 
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
   PERCENT1, 
   PERCENT2, 
   PERCENT3, 
   PERCENT4, 
   PERCENT5, 
   TIME1, 
   TIME2, 
   TIME3, 
   TIME4, 
   TIME5, 
   V1, 
   V2, 
   V3, 
   V4, 
   V5, 
} PortIndex;
*/

} // end namespace mbe
