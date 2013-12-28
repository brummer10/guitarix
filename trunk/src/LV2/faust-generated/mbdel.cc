// generated from file '../src/LV2/faust/mbdel.dsp' by dsp2cc:
// Code generated with Faust 0.9.58 (http://faust.grame.fr)


namespace mbdel {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	int 	iConst0;
	double 	fConst1;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fConst2;
	double 	fVec0[2];
	double 	fRec5[2];
	double 	fRec4[3];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec6[2];
	int 	IOTA;
	double *fVec1;
	double 	fConst3;
	double 	fConst4;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	int 	iConst5;
	double 	fRec7[2];
	double 	fRec8[2];
	double 	fRec9[2];
	double 	fRec10[2];
	double 	fRec0[2];
	int 	iRec1[2];
	double 	fRec2[2];
	FAUSTFLOAT 	fbargraph0;
	FAUSTFLOAT	*fbargraph0_;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fRec18[2];
	double 	fRec17[3];
	double 	fVec2[2];
	double 	fRec16[2];
	double 	fRec15[3];
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT	*fslider4_;
	double 	fRec19[2];
	double *fVec3;
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT	*fslider5_;
	double 	fRec20[2];
	double 	fRec21[2];
	double 	fRec22[2];
	double 	fRec23[2];
	double 	fRec11[2];
	int 	iRec12[2];
	double 	fRec13[2];
	FAUSTFLOAT 	fbargraph1;
	FAUSTFLOAT	*fbargraph1_;
	FAUSTFLOAT 	fslider6;
	FAUSTFLOAT	*fslider6_;
	double 	fRec31[2];
	double 	fRec30[3];
	double 	fVec4[2];
	double 	fRec29[2];
	double 	fRec28[3];
	FAUSTFLOAT 	fslider7;
	FAUSTFLOAT	*fslider7_;
	double 	fRec32[2];
	double *fVec5;
	FAUSTFLOAT 	fslider8;
	FAUSTFLOAT	*fslider8_;
	double 	fRec33[2];
	double 	fRec34[2];
	double 	fRec35[2];
	double 	fRec36[2];
	double 	fRec24[2];
	int 	iRec25[2];
	double 	fRec26[2];
	FAUSTFLOAT 	fbargraph2;
	FAUSTFLOAT	*fbargraph2_;
	FAUSTFLOAT 	fslider9;
	FAUSTFLOAT	*fslider9_;
	double 	fRec44[2];
	double 	fRec43[3];
	double 	fVec6[2];
	double 	fRec42[2];
	double 	fRec41[3];
	FAUSTFLOAT 	fslider10;
	FAUSTFLOAT	*fslider10_;
	double 	fRec45[2];
	double *fVec7;
	FAUSTFLOAT 	fslider11;
	FAUSTFLOAT	*fslider11_;
	double 	fRec46[2];
	double 	fRec47[2];
	double 	fRec48[2];
	double 	fRec49[2];
	double 	fRec37[2];
	int 	iRec38[2];
	double 	fRec39[2];
	FAUSTFLOAT 	fbargraph3;
	FAUSTFLOAT	*fbargraph3_;
	double 	fRec55[2];
	double 	fRec54[3];
	FAUSTFLOAT 	fslider12;
	FAUSTFLOAT	*fslider12_;
	double 	fRec56[2];
	double *fVec8;
	FAUSTFLOAT 	fslider13;
	FAUSTFLOAT	*fslider13_;
	double 	fRec57[2];
	double 	fRec58[2];
	double 	fRec59[2];
	double 	fRec60[2];
	double 	fRec50[2];
	int 	iRec51[2];
	double 	fRec52[2];
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
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<3; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<262144; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) iRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<3; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<3; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<262144; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) iRec12[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec31[i] = 0;
	for (int i=0; i<3; i++) fRec30[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec29[i] = 0;
	for (int i=0; i<3; i++) fRec28[i] = 0;
	for (int i=0; i<2; i++) fRec32[i] = 0;
	for (int i=0; i<262144; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec33[i] = 0;
	for (int i=0; i<2; i++) fRec34[i] = 0;
	for (int i=0; i<2; i++) fRec35[i] = 0;
	for (int i=0; i<2; i++) fRec36[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) iRec25[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<2; i++) fRec44[i] = 0;
	for (int i=0; i<3; i++) fRec43[i] = 0;
	for (int i=0; i<2; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec42[i] = 0;
	for (int i=0; i<3; i++) fRec41[i] = 0;
	for (int i=0; i<2; i++) fRec45[i] = 0;
	for (int i=0; i<262144; i++) fVec7[i] = 0;
	for (int i=0; i<2; i++) fRec46[i] = 0;
	for (int i=0; i<2; i++) fRec47[i] = 0;
	for (int i=0; i<2; i++) fRec48[i] = 0;
	for (int i=0; i<2; i++) fRec49[i] = 0;
	for (int i=0; i<2; i++) fRec37[i] = 0;
	for (int i=0; i<2; i++) iRec38[i] = 0;
	for (int i=0; i<2; i++) fRec39[i] = 0;
	for (int i=0; i<2; i++) fRec55[i] = 0;
	for (int i=0; i<3; i++) fRec54[i] = 0;
	for (int i=0; i<2; i++) fRec56[i] = 0;
	for (int i=0; i<262144; i++) fVec8[i] = 0;
	for (int i=0; i<2; i++) fRec57[i] = 0;
	for (int i=0; i<2; i++) fRec58[i] = 0;
	for (int i=0; i<2; i++) fRec59[i] = 0;
	for (int i=0; i<2; i++) fRec60[i] = 0;
	for (int i=0; i<2; i++) fRec50[i] = 0;
	for (int i=0; i<2; i++) iRec51[i] = 0;
	for (int i=0; i<2; i++) fRec52[i] = 0;
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
#define fbargraph0 (*fbargraph0_)
#define fslider3 (*fslider3_)
#define fslider4 (*fslider4_)
#define fslider5 (*fslider5_)
#define fbargraph1 (*fbargraph1_)
#define fslider6 (*fslider6_)
#define fslider7 (*fslider7_)
#define fslider8 (*fslider8_)
#define fbargraph2 (*fbargraph2_)
#define fslider9 (*fslider9_)
#define fslider10 (*fslider10_)
#define fslider11 (*fslider11_)
#define fbargraph3 (*fbargraph3_)
#define fslider12 (*fslider12_)
#define fslider13 (*fslider13_)
#define fbargraph4 (*fbargraph4_)
	double 	fSlow0 = tan((fConst2 * fslider0));
	double 	fSlow1 = (1.0 / faustpower<2>(fSlow0));
	double 	fSlow2 = (2 * (1 - fSlow1));
	double 	fSlow3 = (1.0 / fSlow0);
	double 	fSlow4 = (1 + ((fSlow3 - 1.0000000000000004) / fSlow0));
	double 	fSlow5 = (1 + ((1.0000000000000004 + fSlow3) / fSlow0));
	double 	fSlow6 = (1.0 / fSlow5);
	double 	fSlow7 = (1 + fSlow3);
	double 	fSlow8 = (0 - ((1 - fSlow3) / fSlow7));
	double 	fSlow9 = (0 - fSlow3);
	double 	fSlow10 = (1.0 / fSlow7);
	double 	fSlow11 = (2 * (0 - fSlow1));
	double 	fSlow12 = (0.0010000000000000009 * pow(10,(0.05 * fslider1)));
	double 	fSlow13 = (double(iConst5) / fslider2);
	double 	fSlow14 = tan((fConst2 * fslider3));
	double 	fSlow15 = (1.0 / faustpower<2>(fSlow14));
	double 	fSlow16 = (2 * (1 - fSlow15));
	double 	fSlow17 = (1.0 / fSlow14);
	double 	fSlow18 = (1 + ((fSlow17 - 1.0000000000000004) / fSlow14));
	double 	fSlow19 = (1 + ((1.0000000000000004 + fSlow17) / fSlow14));
	double 	fSlow20 = (1.0 / fSlow19);
	double 	fSlow21 = (1 + fSlow17);
	double 	fSlow22 = (0 - ((1 - fSlow17) / fSlow21));
	double 	fSlow23 = (1.0 / (fSlow5 * fSlow14));
	double 	fSlow24 = (0 - fSlow17);
	double 	fSlow25 = (1.0 / fSlow21);
	double 	fSlow26 = (2 * (0 - fSlow15));
	double 	fSlow27 = (0.0010000000000000009 * pow(10,(0.05 * fslider4)));
	double 	fSlow28 = (double(iConst5) / fslider5);
	double 	fSlow29 = tan((fConst2 * fslider6));
	double 	fSlow30 = (1.0 / faustpower<2>(fSlow29));
	double 	fSlow31 = (2 * (1 - fSlow30));
	double 	fSlow32 = (1.0 / fSlow29);
	double 	fSlow33 = (1 + ((fSlow32 - 1.0000000000000004) / fSlow29));
	double 	fSlow34 = (1 + ((1.0000000000000004 + fSlow32) / fSlow29));
	double 	fSlow35 = (1.0 / fSlow34);
	double 	fSlow36 = (1 + fSlow32);
	double 	fSlow37 = (0 - ((1 - fSlow32) / fSlow36));
	double 	fSlow38 = (1.0 / (fSlow19 * fSlow29));
	double 	fSlow39 = (0 - fSlow32);
	double 	fSlow40 = (1.0 / fSlow36);
	double 	fSlow41 = (2 * (0 - fSlow30));
	double 	fSlow42 = (0.0010000000000000009 * pow(10,(0.05 * fslider7)));
	double 	fSlow43 = (double(iConst5) / fslider8);
	double 	fSlow44 = tan((fConst2 * fslider9));
	double 	fSlow45 = (1.0 / faustpower<2>(fSlow44));
	double 	fSlow46 = (2 * (1 - fSlow45));
	double 	fSlow47 = (1.0 / fSlow44);
	double 	fSlow48 = (1 + ((fSlow47 - 1.0000000000000004) / fSlow44));
	double 	fSlow49 = (1.0 / (1 + ((1.0000000000000004 + fSlow47) / fSlow44)));
	double 	fSlow50 = (1 + fSlow47);
	double 	fSlow51 = (0 - ((1 - fSlow47) / fSlow50));
	double 	fSlow52 = (1.0 / (fSlow34 * fSlow44));
	double 	fSlow53 = (0 - fSlow47);
	double 	fSlow54 = (1.0 / fSlow50);
	double 	fSlow55 = (2 * (0 - fSlow45));
	double 	fSlow56 = (0.0010000000000000009 * pow(10,(0.05 * fslider10)));
	double 	fSlow57 = (double(iConst5) / fslider11);
	double 	fSlow58 = (0.0010000000000000009 * pow(10,(0.05 * fslider12)));
	double 	fSlow59 = (double(iConst5) / fslider13);
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fVec0[0] = fTemp0;
		fRec5[0] = ((fSlow10 * ((fSlow9 * fVec0[1]) + (fSlow3 * fVec0[0]))) + (fSlow8 * fRec5[1]));
		fRec4[0] = (fRec5[0] - (fSlow6 * ((fSlow4 * fRec4[2]) + (fSlow2 * fRec4[1]))));
		fRec6[0] = (fSlow12 + (0.999 * fRec6[1]));
		double fTemp1 = (fSlow6 * (fRec6[0] * (((fSlow1 * fRec4[0]) + (fSlow11 * fRec4[1])) + (fSlow1 * fRec4[2]))));
		fVec1[IOTA&262143] = fTemp1;
		double fTemp2 = ((int((fRec7[1] != 0.0)))?((int(((fRec8[1] > 0.0) & (fRec8[1] < 1.0))))?fRec7[1]:0):((int(((fRec8[1] == 0.0) & (fSlow13 != fRec9[1]))))?fConst3:((int(((fRec8[1] == 1.0) & (fSlow13 != fRec10[1]))))?fConst4:0)));
		fRec7[0] = fTemp2;
		fRec8[0] = max(0.0, min(1.0, (fRec8[1] + fTemp2)));
		fRec9[0] = ((int(((fRec8[1] >= 1.0) & (fRec10[1] != fSlow13))))?fSlow13:fRec9[1]);
		fRec10[0] = ((int(((fRec8[1] <= 0.0) & (fRec9[1] != fSlow13))))?fSlow13:fRec10[1]);
		double fTemp3 = ((fRec8[0] * fVec1[(IOTA-int((int(fRec10[0]) & 262143)))&262143]) + ((1.0 - fRec8[0]) * fVec1[(IOTA-int((int(fRec9[0]) & 262143)))&262143]));
		double 	fRec3 = max(fConst1, fabs(fTemp3));
		int iTemp4 = int((iRec1[1] < 4096));
		fRec0[0] = ((iTemp4)?max(fRec0[1], fRec3):fRec3);
		iRec1[0] = ((iTemp4)?(1 + iRec1[1]):1);
		fRec2[0] = ((iTemp4)?fRec2[1]:fRec0[1]);
		fbargraph0 = fRec2[0];
		double fTemp5 = (fVec0[0] + fVec0[1]);
		fRec18[0] = ((fSlow10 * fTemp5) + (fSlow8 * fRec18[1]));
		fRec17[0] = (fRec18[0] - (fSlow6 * ((fSlow4 * fRec17[2]) + (fSlow2 * fRec17[1]))));
		double fTemp6 = (fRec17[2] + (fRec17[0] + (2 * fRec17[1])));
		fVec2[0] = (fSlow6 * fTemp6);
		fRec16[0] = ((fSlow25 * ((fSlow24 * fVec2[1]) + (fSlow23 * fTemp6))) + (fSlow22 * fRec16[1]));
		fRec15[0] = (fRec16[0] - (fSlow20 * ((fSlow18 * fRec15[2]) + (fSlow16 * fRec15[1]))));
		fRec19[0] = (fSlow27 + (0.999 * fRec19[1]));
		double fTemp7 = (fSlow20 * (fRec19[0] * (((fSlow15 * fRec15[0]) + (fSlow26 * fRec15[1])) + (fSlow15 * fRec15[2]))));
		fVec3[IOTA&262143] = fTemp7;
		double fTemp8 = ((int((fRec20[1] != 0.0)))?((int(((fRec21[1] > 0.0) & (fRec21[1] < 1.0))))?fRec20[1]:0):((int(((fRec21[1] == 0.0) & (fSlow28 != fRec22[1]))))?fConst3:((int(((fRec21[1] == 1.0) & (fSlow28 != fRec23[1]))))?fConst4:0)));
		fRec20[0] = fTemp8;
		fRec21[0] = max(0.0, min(1.0, (fRec21[1] + fTemp8)));
		fRec22[0] = ((int(((fRec21[1] >= 1.0) & (fRec23[1] != fSlow28))))?fSlow28:fRec22[1]);
		fRec23[0] = ((int(((fRec21[1] <= 0.0) & (fRec22[1] != fSlow28))))?fSlow28:fRec23[1]);
		double fTemp9 = ((fRec21[0] * fVec3[(IOTA-int((int(fRec23[0]) & 262143)))&262143]) + ((1.0 - fRec21[0]) * fVec3[(IOTA-int((int(fRec22[0]) & 262143)))&262143]));
		double 	fRec14 = max(fConst1, fabs(fTemp9));
		int iTemp10 = int((iRec12[1] < 4096));
		fRec11[0] = ((iTemp10)?max(fRec11[1], fRec14):fRec14);
		iRec12[0] = ((iTemp10)?(1 + iRec12[1]):1);
		fRec13[0] = ((iTemp10)?fRec13[1]:fRec11[1]);
		fbargraph1 = fRec13[0];
		fRec31[0] = ((fSlow25 * fTemp5) + (fSlow22 * fRec31[1]));
		fRec30[0] = (fRec31[0] - (fSlow20 * ((fSlow18 * fRec30[2]) + (fSlow16 * fRec30[1]))));
		double fTemp11 = (fRec30[2] + (fRec30[0] + (2 * fRec30[1])));
		fVec4[0] = (fSlow20 * fTemp11);
		fRec29[0] = ((fSlow40 * ((fSlow39 * fVec4[1]) + (fSlow38 * fTemp11))) + (fSlow37 * fRec29[1]));
		fRec28[0] = (fRec29[0] - (fSlow35 * ((fSlow33 * fRec28[2]) + (fSlow31 * fRec28[1]))));
		fRec32[0] = (fSlow42 + (0.999 * fRec32[1]));
		double fTemp12 = (fSlow35 * (fRec32[0] * (((fSlow30 * fRec28[0]) + (fSlow41 * fRec28[1])) + (fSlow30 * fRec28[2]))));
		fVec5[IOTA&262143] = fTemp12;
		double fTemp13 = ((int((fRec33[1] != 0.0)))?((int(((fRec34[1] > 0.0) & (fRec34[1] < 1.0))))?fRec33[1]:0):((int(((fRec34[1] == 0.0) & (fSlow43 != fRec35[1]))))?fConst3:((int(((fRec34[1] == 1.0) & (fSlow43 != fRec36[1]))))?fConst4:0)));
		fRec33[0] = fTemp13;
		fRec34[0] = max(0.0, min(1.0, (fRec34[1] + fTemp13)));
		fRec35[0] = ((int(((fRec34[1] >= 1.0) & (fRec36[1] != fSlow43))))?fSlow43:fRec35[1]);
		fRec36[0] = ((int(((fRec34[1] <= 0.0) & (fRec35[1] != fSlow43))))?fSlow43:fRec36[1]);
		double fTemp14 = ((fRec34[0] * fVec5[(IOTA-int((int(fRec36[0]) & 262143)))&262143]) + ((1.0 - fRec34[0]) * fVec5[(IOTA-int((int(fRec35[0]) & 262143)))&262143]));
		double 	fRec27 = max(fConst1, fabs(fTemp14));
		int iTemp15 = int((iRec25[1] < 4096));
		fRec24[0] = ((iTemp15)?max(fRec24[1], fRec27):fRec27);
		iRec25[0] = ((iTemp15)?(1 + iRec25[1]):1);
		fRec26[0] = ((iTemp15)?fRec26[1]:fRec24[1]);
		fbargraph2 = fRec26[0];
		fRec44[0] = ((fSlow40 * fTemp5) + (fSlow37 * fRec44[1]));
		fRec43[0] = (fRec44[0] - (fSlow35 * ((fSlow33 * fRec43[2]) + (fSlow31 * fRec43[1]))));
		double fTemp16 = (fRec43[2] + (fRec43[0] + (2 * fRec43[1])));
		fVec6[0] = (fSlow35 * fTemp16);
		fRec42[0] = ((fSlow54 * ((fSlow53 * fVec6[1]) + (fSlow52 * fTemp16))) + (fSlow51 * fRec42[1]));
		fRec41[0] = (fRec42[0] - (fSlow49 * ((fSlow48 * fRec41[2]) + (fSlow46 * fRec41[1]))));
		fRec45[0] = (fSlow56 + (0.999 * fRec45[1]));
		double fTemp17 = (fSlow49 * (fRec45[0] * (((fSlow45 * fRec41[0]) + (fSlow55 * fRec41[1])) + (fSlow45 * fRec41[2]))));
		fVec7[IOTA&262143] = fTemp17;
		double fTemp18 = ((int((fRec46[1] != 0.0)))?((int(((fRec47[1] > 0.0) & (fRec47[1] < 1.0))))?fRec46[1]:0):((int(((fRec47[1] == 0.0) & (fSlow57 != fRec48[1]))))?fConst3:((int(((fRec47[1] == 1.0) & (fSlow57 != fRec49[1]))))?fConst4:0)));
		fRec46[0] = fTemp18;
		fRec47[0] = max(0.0, min(1.0, (fRec47[1] + fTemp18)));
		fRec48[0] = ((int(((fRec47[1] >= 1.0) & (fRec49[1] != fSlow57))))?fSlow57:fRec48[1]);
		fRec49[0] = ((int(((fRec47[1] <= 0.0) & (fRec48[1] != fSlow57))))?fSlow57:fRec49[1]);
		double fTemp19 = ((fRec47[0] * fVec7[(IOTA-int((int(fRec49[0]) & 262143)))&262143]) + ((1.0 - fRec47[0]) * fVec7[(IOTA-int((int(fRec48[0]) & 262143)))&262143]));
		double 	fRec40 = max(fConst1, fabs(fTemp19));
		int iTemp20 = int((iRec38[1] < 4096));
		fRec37[0] = ((iTemp20)?max(fRec37[1], fRec40):fRec40);
		iRec38[0] = ((iTemp20)?(1 + iRec38[1]):1);
		fRec39[0] = ((iTemp20)?fRec39[1]:fRec37[1]);
		fbargraph3 = fRec39[0];
		fRec55[0] = ((fSlow54 * fTemp5) + (fSlow51 * fRec55[1]));
		fRec54[0] = (fRec55[0] - (fSlow49 * ((fSlow48 * fRec54[2]) + (fSlow46 * fRec54[1]))));
		fRec56[0] = (fSlow58 + (0.999 * fRec56[1]));
		double fTemp21 = (fSlow49 * (fRec56[0] * (fRec54[2] + (fRec54[0] + (2 * fRec54[1])))));
		fVec8[IOTA&262143] = fTemp21;
		double fTemp22 = ((int((fRec57[1] != 0.0)))?((int(((fRec58[1] > 0.0) & (fRec58[1] < 1.0))))?fRec57[1]:0):((int(((fRec58[1] == 0.0) & (fSlow59 != fRec59[1]))))?fConst3:((int(((fRec58[1] == 1.0) & (fSlow59 != fRec60[1]))))?fConst4:0)));
		fRec57[0] = fTemp22;
		fRec58[0] = max(0.0, min(1.0, (fRec58[1] + fTemp22)));
		fRec59[0] = ((int(((fRec58[1] >= 1.0) & (fRec60[1] != fSlow59))))?fSlow59:fRec59[1]);
		fRec60[0] = ((int(((fRec58[1] <= 0.0) & (fRec59[1] != fSlow59))))?fSlow59:fRec60[1]);
		double fTemp23 = ((fRec58[0] * fVec8[(IOTA-int((int(fRec60[0]) & 262143)))&262143]) + ((1.0 - fRec58[0]) * fVec8[(IOTA-int((int(fRec59[0]) & 262143)))&262143]));
		double 	fRec53 = max(fConst1, fabs(fTemp23));
		int iTemp24 = int((iRec51[1] < 4096));
		fRec50[0] = ((iTemp24)?max(fRec50[1], fRec53):fRec53);
		iRec51[0] = ((iTemp24)?(1 + iRec51[1]):1);
		fRec52[0] = ((iTemp24)?fRec52[1]:fRec50[1]);
		fbargraph4 = fRec52[0];
		output0[i] = (FAUSTFLOAT)(fTemp23 + (fTemp19 + (fTemp14 + (fTemp9 + (fVec0[0] + fTemp3)))));
		// post processing
		fRec52[1] = fRec52[0];
		iRec51[1] = iRec51[0];
		fRec50[1] = fRec50[0];
		fRec60[1] = fRec60[0];
		fRec59[1] = fRec59[0];
		fRec58[1] = fRec58[0];
		fRec57[1] = fRec57[0];
		fRec56[1] = fRec56[0];
		fRec54[2] = fRec54[1]; fRec54[1] = fRec54[0];
		fRec55[1] = fRec55[0];
		fRec39[1] = fRec39[0];
		iRec38[1] = iRec38[0];
		fRec37[1] = fRec37[0];
		fRec49[1] = fRec49[0];
		fRec48[1] = fRec48[0];
		fRec47[1] = fRec47[0];
		fRec46[1] = fRec46[0];
		fRec45[1] = fRec45[0];
		fRec41[2] = fRec41[1]; fRec41[1] = fRec41[0];
		fRec42[1] = fRec42[0];
		fVec6[1] = fVec6[0];
		fRec43[2] = fRec43[1]; fRec43[1] = fRec43[0];
		fRec44[1] = fRec44[0];
		fRec26[1] = fRec26[0];
		iRec25[1] = iRec25[0];
		fRec24[1] = fRec24[0];
		fRec36[1] = fRec36[0];
		fRec35[1] = fRec35[0];
		fRec34[1] = fRec34[0];
		fRec33[1] = fRec33[0];
		fRec32[1] = fRec32[0];
		fRec28[2] = fRec28[1]; fRec28[1] = fRec28[0];
		fRec29[1] = fRec29[0];
		fVec4[1] = fVec4[0];
		fRec30[2] = fRec30[1]; fRec30[1] = fRec30[0];
		fRec31[1] = fRec31[0];
		fRec13[1] = fRec13[0];
		iRec12[1] = iRec12[0];
		fRec11[1] = fRec11[0];
		fRec23[1] = fRec23[0];
		fRec22[1] = fRec22[0];
		fRec21[1] = fRec21[0];
		fRec20[1] = fRec20[0];
		fRec19[1] = fRec19[0];
		fRec15[2] = fRec15[1]; fRec15[1] = fRec15[0];
		fRec16[1] = fRec16[0];
		fVec2[1] = fVec2[0];
		fRec17[2] = fRec17[1]; fRec17[1] = fRec17[0];
		fRec18[1] = fRec18[0];
		fRec2[1] = fRec2[0];
		iRec1[1] = iRec1[0];
		fRec0[1] = fRec0[0];
		fRec10[1] = fRec10[0];
		fRec9[1] = fRec9[0];
		fRec8[1] = fRec8[0];
		fRec7[1] = fRec7[0];
		IOTA = IOTA+1;
		fRec6[1] = fRec6[0];
		fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fVec0[1] = fVec0[0];
	}
#undef fslider0
#undef fslider1
#undef fslider2
#undef fbargraph0
#undef fslider3
#undef fslider4
#undef fslider5
#undef fbargraph1
#undef fslider6
#undef fslider7
#undef fslider8
#undef fbargraph2
#undef fslider9
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
		fslider9_ = (float*)data; // , 8e+01, 2e+01, 2e+04, 1.08 
		break;
	case CROSSOVER_B2_B3: 
		fslider6_ = (float*)data; // , 2.1e+02, 2e+01, 2e+04, 1.08 
		break;
	case CROSSOVER_B3_B4: 
		fslider3_ = (float*)data; // , 1.7e+03, 2e+01, 2e+04, 1.08 
		break;
	case CROSSOVER_B4_B5: 
		fslider0_ = (float*)data; // , 5e+03, 2e+01, 2e+04, 1.08 
		break;
	case DELAY1: 
		fslider13_ = (float*)data; // , 3e+01, 24.0, 3.6e+02, 1.0 
		break;
	case DELAY2: 
		fslider11_ = (float*)data; // , 6e+01, 24.0, 3.6e+02, 1.0 
		break;
	case DELAY3: 
		fslider8_ = (float*)data; // , 9e+01, 24.0, 3.6e+02, 1.0 
		break;
	case DELAY4: 
		fslider5_ = (float*)data; // , 1.2e+02, 24.0, 3.6e+02, 1.0 
		break;
	case DELAY5: 
		fslider2_ = (float*)data; // , 1.5e+02, 24.0, 3.6e+02, 1.0 
		break;
	case GAIN1: 
		fslider12_ = (float*)data; // , -1e+01, -2e+01, 2e+01, 0.1 
		break;
	case GAIN2: 
		fslider10_ = (float*)data; // , -5.0, -2e+01, 2e+01, 0.1 
		break;
	case GAIN3: 
		fslider7_ = (float*)data; // , -2.0, -2e+01, 2e+01, 0.1 
		break;
	case GAIN4: 
		fslider4_ = (float*)data; // , 0.0, -2e+01, 2e+01, 0.1 
		break;
	case GAIN5: 
		fslider1_ = (float*)data; // , -1e+01, -2e+01, 2e+01, 0.1 
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
