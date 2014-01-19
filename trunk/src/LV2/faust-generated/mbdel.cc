// generated from file '../src/LV2/faust/mbdel.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)


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
	double 	fRec8[2];
	double 	fRec7[3];
	double 	fRec6[3];
	double 	fRec5[3];
	double 	fRec4[3];
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT	*fslider4_;
	double 	fRec9[2];
	int 	IOTA;
	double *fVec1;
	double 	fConst3;
	double 	fConst4;
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT	*fslider5_;
	int 	iConst5;
	double 	fRec10[2];
	double 	fRec11[2];
	double 	fRec12[2];
	double 	fRec13[2];
	double 	fRec0[2];
	int 	iRec1[2];
	double 	fRec2[2];
	FAUSTFLOAT 	fbargraph0;
	FAUSTFLOAT	*fbargraph0_;
	double 	fRec23[2];
	double 	fRec22[3];
	double 	fVec2[2];
	double 	fRec21[2];
	double 	fRec20[3];
	double 	fRec19[3];
	double 	fRec18[3];
	FAUSTFLOAT 	fslider6;
	FAUSTFLOAT	*fslider6_;
	double 	fRec24[2];
	double *fVec3;
	FAUSTFLOAT 	fslider7;
	FAUSTFLOAT	*fslider7_;
	double 	fRec25[2];
	double 	fRec26[2];
	double 	fRec27[2];
	double 	fRec28[2];
	double 	fRec14[2];
	int 	iRec15[2];
	double 	fRec16[2];
	FAUSTFLOAT 	fbargraph1;
	FAUSTFLOAT	*fbargraph1_;
	double 	fRec37[2];
	double 	fRec36[3];
	double 	fVec4[2];
	double 	fRec35[2];
	double 	fRec34[3];
	double 	fRec33[3];
	FAUSTFLOAT 	fslider8;
	FAUSTFLOAT	*fslider8_;
	double 	fRec38[2];
	double *fVec5;
	FAUSTFLOAT 	fslider9;
	FAUSTFLOAT	*fslider9_;
	double 	fRec39[2];
	double 	fRec40[2];
	double 	fRec41[2];
	double 	fRec42[2];
	double 	fRec29[2];
	int 	iRec30[2];
	double 	fRec31[2];
	FAUSTFLOAT 	fbargraph2;
	FAUSTFLOAT	*fbargraph2_;
	double 	fRec50[2];
	double 	fRec49[3];
	double 	fVec6[2];
	double 	fRec48[2];
	double 	fRec47[3];
	FAUSTFLOAT 	fslider10;
	FAUSTFLOAT	*fslider10_;
	double 	fRec51[2];
	double *fVec7;
	FAUSTFLOAT 	fslider11;
	FAUSTFLOAT	*fslider11_;
	double 	fRec52[2];
	double 	fRec53[2];
	double 	fRec54[2];
	double 	fRec55[2];
	double 	fRec43[2];
	int 	iRec44[2];
	double 	fRec45[2];
	FAUSTFLOAT 	fbargraph3;
	FAUSTFLOAT	*fbargraph3_;
	double 	fRec61[2];
	double 	fRec60[3];
	FAUSTFLOAT 	fslider12;
	FAUSTFLOAT	*fslider12_;
	double 	fRec62[2];
	double *fVec8;
	FAUSTFLOAT 	fslider13;
	FAUSTFLOAT	*fslider13_;
	double 	fRec63[2];
	double 	fRec64[2];
	double 	fRec65[2];
	double 	fRec66[2];
	double 	fRec56[2];
	int 	iRec57[2];
	double 	fRec58[2];
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
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<3; i++) fRec7[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<3; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<262144; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) iRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<3; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<3; i++) fRec20[i] = 0;
	for (int i=0; i<3; i++) fRec19[i] = 0;
	for (int i=0; i<3; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<262144; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec25[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<2; i++) fRec27[i] = 0;
	for (int i=0; i<2; i++) fRec28[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) iRec15[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fRec37[i] = 0;
	for (int i=0; i<3; i++) fRec36[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec35[i] = 0;
	for (int i=0; i<3; i++) fRec34[i] = 0;
	for (int i=0; i<3; i++) fRec33[i] = 0;
	for (int i=0; i<2; i++) fRec38[i] = 0;
	for (int i=0; i<262144; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec39[i] = 0;
	for (int i=0; i<2; i++) fRec40[i] = 0;
	for (int i=0; i<2; i++) fRec41[i] = 0;
	for (int i=0; i<2; i++) fRec42[i] = 0;
	for (int i=0; i<2; i++) fRec29[i] = 0;
	for (int i=0; i<2; i++) iRec30[i] = 0;
	for (int i=0; i<2; i++) fRec31[i] = 0;
	for (int i=0; i<2; i++) fRec50[i] = 0;
	for (int i=0; i<3; i++) fRec49[i] = 0;
	for (int i=0; i<2; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec48[i] = 0;
	for (int i=0; i<3; i++) fRec47[i] = 0;
	for (int i=0; i<2; i++) fRec51[i] = 0;
	for (int i=0; i<262144; i++) fVec7[i] = 0;
	for (int i=0; i<2; i++) fRec52[i] = 0;
	for (int i=0; i<2; i++) fRec53[i] = 0;
	for (int i=0; i<2; i++) fRec54[i] = 0;
	for (int i=0; i<2; i++) fRec55[i] = 0;
	for (int i=0; i<2; i++) fRec43[i] = 0;
	for (int i=0; i<2; i++) iRec44[i] = 0;
	for (int i=0; i<2; i++) fRec45[i] = 0;
	for (int i=0; i<2; i++) fRec61[i] = 0;
	for (int i=0; i<3; i++) fRec60[i] = 0;
	for (int i=0; i<2; i++) fRec62[i] = 0;
	for (int i=0; i<262144; i++) fVec8[i] = 0;
	for (int i=0; i<2; i++) fRec63[i] = 0;
	for (int i=0; i<2; i++) fRec64[i] = 0;
	for (int i=0; i<2; i++) fRec65[i] = 0;
	for (int i=0; i<2; i++) fRec66[i] = 0;
	for (int i=0; i<2; i++) fRec56[i] = 0;
	for (int i=0; i<2; i++) iRec57[i] = 0;
	for (int i=0; i<2; i++) fRec58[i] = 0;
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
	double 	fSlow31 = (double(iConst5) / double(fslider5));
	double 	fSlow32 = (1 + ((fSlow15 - 1.0000000000000004) / fSlow12));
	double 	fSlow33 = (1 + ((fSlow15 + 1.0000000000000004) / fSlow12));
	double 	fSlow34 = (1.0 / fSlow33);
	double 	fSlow35 = (0 - fSlow15);
	double 	fSlow36 = (1.0 / (fSlow12 * fSlow23));
	double 	fSlow37 = (1 + fSlow15);
	double 	fSlow38 = (1.0 / fSlow37);
	double 	fSlow39 = (0 - ((1 - fSlow15) / fSlow37));
	double 	fSlow40 = (2 * (0 - fSlow13));
	double 	fSlow41 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider6))));
	double 	fSlow42 = (double(iConst5) / double(fslider7));
	double 	fSlow43 = (1 + ((fSlow9 - 1.0000000000000004) / fSlow6));
	double 	fSlow44 = (1 + ((fSlow9 + 1.0000000000000004) / fSlow6));
	double 	fSlow45 = (1.0 / fSlow44);
	double 	fSlow46 = (0 - fSlow9);
	double 	fSlow47 = (1.0 / (fSlow6 * fSlow33));
	double 	fSlow48 = (1 + fSlow9);
	double 	fSlow49 = (1.0 / fSlow48);
	double 	fSlow50 = (0 - ((1 - fSlow9) / fSlow48));
	double 	fSlow51 = (2 * (0 - fSlow7));
	double 	fSlow52 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider8))));
	double 	fSlow53 = (double(iConst5) / double(fslider9));
	double 	fSlow54 = (1 + ((fSlow3 - 1.0000000000000004) / fSlow0));
	double 	fSlow55 = (1.0 / (1 + ((fSlow3 + 1.0000000000000004) / fSlow0)));
	double 	fSlow56 = (0 - fSlow3);
	double 	fSlow57 = (1.0 / (fSlow0 * fSlow44));
	double 	fSlow58 = (1 + fSlow3);
	double 	fSlow59 = (1.0 / fSlow58);
	double 	fSlow60 = (0 - ((1 - fSlow3) / fSlow58));
	double 	fSlow61 = (2 * (0 - fSlow1));
	double 	fSlow62 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider10))));
	double 	fSlow63 = (double(iConst5) / double(fslider11));
	double 	fSlow64 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider12))));
	double 	fSlow65 = (double(iConst5) / double(fslider13));
	for (int i=0; i<count; i++) {
		double fTemp0 = (fSlow2 * fRec4[1]);
		double fTemp1 = (fSlow8 * fRec5[1]);
		double fTemp2 = (fSlow14 * fRec6[1]);
		double fTemp3 = (double)input0[i];
		fVec0[0] = fTemp3;
		fRec8[0] = ((fSlow28 * fRec8[1]) + (fSlow27 * ((fSlow21 * fVec0[0]) + (fSlow25 * fVec0[1]))));
		fRec7[0] = (fRec8[0] - (fSlow24 * ((fSlow22 * fRec7[2]) + (fSlow20 * fRec7[1]))));
		fRec6[0] = ((fSlow24 * (((fSlow19 * fRec7[0]) + (fSlow29 * fRec7[1])) + (fSlow19 * fRec7[2]))) - (fSlow17 * ((fSlow16 * fRec6[2]) + fTemp2)));
		fRec5[0] = ((fRec6[2] + (fSlow17 * (fTemp2 + (fSlow16 * fRec6[0])))) - (fSlow11 * ((fSlow10 * fRec5[2]) + fTemp1)));
		fRec4[0] = ((fRec5[2] + (fSlow11 * (fTemp1 + (fSlow10 * fRec5[0])))) - (fSlow5 * ((fSlow4 * fRec4[2]) + fTemp0)));
		fRec9[0] = (fSlow30 + (0.999 * fRec9[1]));
		double fTemp4 = (fRec9[0] * (fRec4[2] + (fSlow5 * (fTemp0 + (fSlow4 * fRec4[0])))));
		fVec1[IOTA&262143] = fTemp4;
		double fTemp5 = ((int((fRec10[1] != 0.0)))?((int(((fRec11[1] > 0.0) & (fRec11[1] < 1.0))))?fRec10[1]:0):((int(((fRec11[1] == 0.0) & (fSlow31 != fRec12[1]))))?fConst3:((int(((fRec11[1] == 1.0) & (fSlow31 != fRec13[1]))))?fConst4:0)));
		fRec10[0] = fTemp5;
		fRec11[0] = max(0.0, min(1.0, (fRec11[1] + fTemp5)));
		fRec12[0] = ((int(((fRec11[1] >= 1.0) & (fRec13[1] != fSlow31))))?fSlow31:fRec12[1]);
		fRec13[0] = ((int(((fRec11[1] <= 0.0) & (fRec12[1] != fSlow31))))?fSlow31:fRec13[1]);
		double fTemp6 = (((1.0 - fRec11[0]) * fVec1[(IOTA-int((int(fRec12[0]) & 262143)))&262143]) + (fRec11[0] * fVec1[(IOTA-int((int(fRec13[0]) & 262143)))&262143]));
		double 	fRec3 = max(fConst1, fabs(fTemp6));
		int iTemp7 = int((iRec1[1] < 4096));
		fRec0[0] = ((iTemp7)?max(fRec0[1], fRec3):fRec3);
		iRec1[0] = ((iTemp7)?(1 + iRec1[1]):1);
		fRec2[0] = ((iTemp7)?fRec2[1]:fRec0[1]);
		fbargraph0 = fRec2[0];
		double fTemp8 = (fSlow2 * fRec18[1]);
		double fTemp9 = (fSlow8 * fRec19[1]);
		fRec23[0] = ((fSlow28 * fRec23[1]) + (fSlow27 * (fVec0[0] + fVec0[1])));
		fRec22[0] = (fRec23[0] - (fSlow24 * ((fSlow22 * fRec22[2]) + (fSlow20 * fRec22[1]))));
		double fTemp10 = (fRec22[2] + (fRec22[0] + (2 * fRec22[1])));
		double fTemp11 = (fSlow24 * fTemp10);
		fVec2[0] = fTemp11;
		fRec21[0] = ((fSlow39 * fRec21[1]) + (fSlow38 * ((fSlow36 * fTemp10) + (fSlow35 * fVec2[1]))));
		fRec20[0] = (fRec21[0] - (fSlow34 * ((fSlow32 * fRec20[2]) + (fSlow14 * fRec20[1]))));
		fRec19[0] = ((fSlow34 * (((fSlow13 * fRec20[0]) + (fSlow40 * fRec20[1])) + (fSlow13 * fRec20[2]))) - (fSlow11 * ((fSlow10 * fRec19[2]) + fTemp9)));
		fRec18[0] = ((fRec19[2] + (fSlow11 * (fTemp9 + (fSlow10 * fRec19[0])))) - (fSlow5 * ((fSlow4 * fRec18[2]) + fTemp8)));
		fRec24[0] = (fSlow41 + (0.999 * fRec24[1]));
		double fTemp12 = (fRec24[0] * (fRec18[2] + (fSlow5 * (fTemp8 + (fSlow4 * fRec18[0])))));
		fVec3[IOTA&262143] = fTemp12;
		double fTemp13 = ((int((fRec25[1] != 0.0)))?((int(((fRec26[1] > 0.0) & (fRec26[1] < 1.0))))?fRec25[1]:0):((int(((fRec26[1] == 0.0) & (fSlow42 != fRec27[1]))))?fConst3:((int(((fRec26[1] == 1.0) & (fSlow42 != fRec28[1]))))?fConst4:0)));
		fRec25[0] = fTemp13;
		fRec26[0] = max(0.0, min(1.0, (fRec26[1] + fTemp13)));
		fRec27[0] = ((int(((fRec26[1] >= 1.0) & (fRec28[1] != fSlow42))))?fSlow42:fRec27[1]);
		fRec28[0] = ((int(((fRec26[1] <= 0.0) & (fRec27[1] != fSlow42))))?fSlow42:fRec28[1]);
		double fTemp14 = (((1.0 - fRec26[0]) * fVec3[(IOTA-int((int(fRec27[0]) & 262143)))&262143]) + (fRec26[0] * fVec3[(IOTA-int((int(fRec28[0]) & 262143)))&262143]));
		double 	fRec17 = max(fConst1, fabs(fTemp14));
		int iTemp15 = int((iRec15[1] < 4096));
		fRec14[0] = ((iTemp15)?max(fRec14[1], fRec17):fRec17);
		iRec15[0] = ((iTemp15)?(1 + iRec15[1]):1);
		fRec16[0] = ((iTemp15)?fRec16[1]:fRec14[1]);
		fbargraph1 = fRec16[0];
		double fTemp16 = (fSlow2 * fRec33[1]);
		fRec37[0] = ((fSlow39 * fRec37[1]) + (fSlow38 * (fVec2[0] + fVec2[1])));
		fRec36[0] = (fRec37[0] - (fSlow34 * ((fSlow32 * fRec36[2]) + (fSlow14 * fRec36[1]))));
		double fTemp17 = (fRec36[2] + (fRec36[0] + (2 * fRec36[1])));
		double fTemp18 = (fSlow34 * fTemp17);
		fVec4[0] = fTemp18;
		fRec35[0] = ((fSlow50 * fRec35[1]) + (fSlow49 * ((fSlow47 * fTemp17) + (fSlow46 * fVec4[1]))));
		fRec34[0] = (fRec35[0] - (fSlow45 * ((fSlow43 * fRec34[2]) + (fSlow8 * fRec34[1]))));
		fRec33[0] = ((fSlow45 * (((fSlow7 * fRec34[0]) + (fSlow51 * fRec34[1])) + (fSlow7 * fRec34[2]))) - (fSlow5 * ((fSlow4 * fRec33[2]) + fTemp16)));
		fRec38[0] = (fSlow52 + (0.999 * fRec38[1]));
		double fTemp19 = (fRec38[0] * (fRec33[2] + (fSlow5 * (fTemp16 + (fSlow4 * fRec33[0])))));
		fVec5[IOTA&262143] = fTemp19;
		double fTemp20 = ((int((fRec39[1] != 0.0)))?((int(((fRec40[1] > 0.0) & (fRec40[1] < 1.0))))?fRec39[1]:0):((int(((fRec40[1] == 0.0) & (fSlow53 != fRec41[1]))))?fConst3:((int(((fRec40[1] == 1.0) & (fSlow53 != fRec42[1]))))?fConst4:0)));
		fRec39[0] = fTemp20;
		fRec40[0] = max(0.0, min(1.0, (fRec40[1] + fTemp20)));
		fRec41[0] = ((int(((fRec40[1] >= 1.0) & (fRec42[1] != fSlow53))))?fSlow53:fRec41[1]);
		fRec42[0] = ((int(((fRec40[1] <= 0.0) & (fRec41[1] != fSlow53))))?fSlow53:fRec42[1]);
		double fTemp21 = (((1.0 - fRec40[0]) * fVec5[(IOTA-int((int(fRec41[0]) & 262143)))&262143]) + (fRec40[0] * fVec5[(IOTA-int((int(fRec42[0]) & 262143)))&262143]));
		double 	fRec32 = max(fConst1, fabs(fTemp21));
		int iTemp22 = int((iRec30[1] < 4096));
		fRec29[0] = ((iTemp22)?max(fRec29[1], fRec32):fRec32);
		iRec30[0] = ((iTemp22)?(1 + iRec30[1]):1);
		fRec31[0] = ((iTemp22)?fRec31[1]:fRec29[1]);
		fbargraph2 = fRec31[0];
		fRec50[0] = ((fSlow50 * fRec50[1]) + (fSlow49 * (fVec4[0] + fVec4[1])));
		fRec49[0] = (fRec50[0] - (fSlow45 * ((fSlow43 * fRec49[2]) + (fSlow8 * fRec49[1]))));
		double fTemp23 = (fRec49[2] + (fRec49[0] + (2 * fRec49[1])));
		double fTemp24 = (fSlow45 * fTemp23);
		fVec6[0] = fTemp24;
		fRec48[0] = ((fSlow60 * fRec48[1]) + (fSlow59 * ((fSlow57 * fTemp23) + (fSlow56 * fVec6[1]))));
		fRec47[0] = (fRec48[0] - (fSlow55 * ((fSlow54 * fRec47[2]) + (fSlow2 * fRec47[1]))));
		fRec51[0] = (fSlow62 + (0.999 * fRec51[1]));
		double fTemp25 = (fSlow55 * (fRec51[0] * (((fSlow1 * fRec47[0]) + (fSlow61 * fRec47[1])) + (fSlow1 * fRec47[2]))));
		fVec7[IOTA&262143] = fTemp25;
		double fTemp26 = ((int((fRec52[1] != 0.0)))?((int(((fRec53[1] > 0.0) & (fRec53[1] < 1.0))))?fRec52[1]:0):((int(((fRec53[1] == 0.0) & (fSlow63 != fRec54[1]))))?fConst3:((int(((fRec53[1] == 1.0) & (fSlow63 != fRec55[1]))))?fConst4:0)));
		fRec52[0] = fTemp26;
		fRec53[0] = max(0.0, min(1.0, (fRec53[1] + fTemp26)));
		fRec54[0] = ((int(((fRec53[1] >= 1.0) & (fRec55[1] != fSlow63))))?fSlow63:fRec54[1]);
		fRec55[0] = ((int(((fRec53[1] <= 0.0) & (fRec54[1] != fSlow63))))?fSlow63:fRec55[1]);
		double fTemp27 = (((1.0 - fRec53[0]) * fVec7[(IOTA-int((int(fRec54[0]) & 262143)))&262143]) + (fRec53[0] * fVec7[(IOTA-int((int(fRec55[0]) & 262143)))&262143]));
		double 	fRec46 = max(fConst1, fabs(fTemp27));
		int iTemp28 = int((iRec44[1] < 4096));
		fRec43[0] = ((iTemp28)?max(fRec43[1], fRec46):fRec46);
		iRec44[0] = ((iTemp28)?(1 + iRec44[1]):1);
		fRec45[0] = ((iTemp28)?fRec45[1]:fRec43[1]);
		fbargraph3 = fRec45[0];
		fRec61[0] = ((fSlow60 * fRec61[1]) + (fSlow59 * (fVec6[0] + fVec6[1])));
		fRec60[0] = (fRec61[0] - (fSlow55 * ((fSlow54 * fRec60[2]) + (fSlow2 * fRec60[1]))));
		fRec62[0] = (fSlow64 + (0.999 * fRec62[1]));
		double fTemp29 = (fSlow55 * (fRec62[0] * (fRec60[2] + (fRec60[0] + (2 * fRec60[1])))));
		fVec8[IOTA&262143] = fTemp29;
		double fTemp30 = ((int((fRec63[1] != 0.0)))?((int(((fRec64[1] > 0.0) & (fRec64[1] < 1.0))))?fRec63[1]:0):((int(((fRec64[1] == 0.0) & (fSlow65 != fRec65[1]))))?fConst3:((int(((fRec64[1] == 1.0) & (fSlow65 != fRec66[1]))))?fConst4:0)));
		fRec63[0] = fTemp30;
		fRec64[0] = max(0.0, min(1.0, (fRec64[1] + fTemp30)));
		fRec65[0] = ((int(((fRec64[1] >= 1.0) & (fRec66[1] != fSlow65))))?fSlow65:fRec65[1]);
		fRec66[0] = ((int(((fRec64[1] <= 0.0) & (fRec65[1] != fSlow65))))?fSlow65:fRec66[1]);
		double fTemp31 = (((1.0 - fRec64[0]) * fVec8[(IOTA-int((int(fRec65[0]) & 262143)))&262143]) + (fRec64[0] * fVec8[(IOTA-int((int(fRec66[0]) & 262143)))&262143]));
		double 	fRec59 = max(fConst1, fabs(fTemp31));
		int iTemp32 = int((iRec57[1] < 4096));
		fRec56[0] = ((iTemp32)?max(fRec56[1], fRec59):fRec59);
		iRec57[0] = ((iTemp32)?(1 + iRec57[1]):1);
		fRec58[0] = ((iTemp32)?fRec58[1]:fRec56[1]);
		fbargraph4 = fRec58[0];
		output0[i] = (FAUSTFLOAT)(fTemp31 + (fTemp27 + (fTemp21 + (fTemp14 + (fVec0[0] + fTemp6)))));
		// post processing
		fRec58[1] = fRec58[0];
		iRec57[1] = iRec57[0];
		fRec56[1] = fRec56[0];
		fRec66[1] = fRec66[0];
		fRec65[1] = fRec65[0];
		fRec64[1] = fRec64[0];
		fRec63[1] = fRec63[0];
		fRec62[1] = fRec62[0];
		fRec60[2] = fRec60[1]; fRec60[1] = fRec60[0];
		fRec61[1] = fRec61[0];
		fRec45[1] = fRec45[0];
		iRec44[1] = iRec44[0];
		fRec43[1] = fRec43[0];
		fRec55[1] = fRec55[0];
		fRec54[1] = fRec54[0];
		fRec53[1] = fRec53[0];
		fRec52[1] = fRec52[0];
		fRec51[1] = fRec51[0];
		fRec47[2] = fRec47[1]; fRec47[1] = fRec47[0];
		fRec48[1] = fRec48[0];
		fVec6[1] = fVec6[0];
		fRec49[2] = fRec49[1]; fRec49[1] = fRec49[0];
		fRec50[1] = fRec50[0];
		fRec31[1] = fRec31[0];
		iRec30[1] = iRec30[0];
		fRec29[1] = fRec29[0];
		fRec42[1] = fRec42[0];
		fRec41[1] = fRec41[0];
		fRec40[1] = fRec40[0];
		fRec39[1] = fRec39[0];
		fRec38[1] = fRec38[0];
		fRec33[2] = fRec33[1]; fRec33[1] = fRec33[0];
		fRec34[2] = fRec34[1]; fRec34[1] = fRec34[0];
		fRec35[1] = fRec35[0];
		fVec4[1] = fVec4[0];
		fRec36[2] = fRec36[1]; fRec36[1] = fRec36[0];
		fRec37[1] = fRec37[0];
		fRec16[1] = fRec16[0];
		iRec15[1] = iRec15[0];
		fRec14[1] = fRec14[0];
		fRec28[1] = fRec28[0];
		fRec27[1] = fRec27[0];
		fRec26[1] = fRec26[0];
		fRec25[1] = fRec25[0];
		fRec24[1] = fRec24[0];
		fRec18[2] = fRec18[1]; fRec18[1] = fRec18[0];
		fRec19[2] = fRec19[1]; fRec19[1] = fRec19[0];
		fRec20[2] = fRec20[1]; fRec20[1] = fRec20[0];
		fRec21[1] = fRec21[0];
		fVec2[1] = fVec2[0];
		fRec22[2] = fRec22[1]; fRec22[1] = fRec22[0];
		fRec23[1] = fRec23[0];
		fRec2[1] = fRec2[0];
		iRec1[1] = iRec1[0];
		fRec0[1] = fRec0[0];
		fRec13[1] = fRec13[0];
		fRec12[1] = fRec12[0];
		fRec11[1] = fRec11[0];
		fRec10[1] = fRec10[0];
		IOTA = IOTA+1;
		fRec9[1] = fRec9[0];
		fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
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
	case DELAY1: 
		fslider13_ = (float*)data; // , 3e+01, 24.0, 3.6e+02, 1.0 
		break;
	case DELAY2: 
		fslider11_ = (float*)data; // , 6e+01, 24.0, 3.6e+02, 1.0 
		break;
	case DELAY3: 
		fslider9_ = (float*)data; // , 9e+01, 24.0, 3.6e+02, 1.0 
		break;
	case DELAY4: 
		fslider7_ = (float*)data; // , 1.2e+02, 24.0, 3.6e+02, 1.0 
		break;
	case DELAY5: 
		fslider5_ = (float*)data; // , 1.5e+02, 24.0, 3.6e+02, 1.0 
		break;
	case GAIN1: 
		fslider12_ = (float*)data; // , -1e+01, -2e+01, 2e+01, 0.1 
		break;
	case GAIN2: 
		fslider10_ = (float*)data; // , -5.0, -2e+01, 2e+01, 0.1 
		break;
	case GAIN3: 
		fslider8_ = (float*)data; // , -2.0, -2e+01, 2e+01, 0.1 
		break;
	case GAIN4: 
		fslider6_ = (float*)data; // , 0.0, -2e+01, 2e+01, 0.1 
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
