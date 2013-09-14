// generated from file '../src/LV2/faust/mbe.dsp' by dsp2cc:
// Code generated with Faust 0.9.58 (http://faust.grame.fr)


namespace mbe {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	int 	iConst4;
	double 	fRec2[2];
	double 	fRec3[2];
	double 	fRec4[2];
	double 	fRec5[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec6[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fConst5;
	double 	fVec0[2];
	double 	fRec8[2];
	double 	fRec7[3];
	int 	IOTA;
	double *fRec1;
	FAUSTFLOAT 	fbargraph0;
	FAUSTFLOAT	*fbargraph0_;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fRec11[2];
	double 	fRec12[2];
	double 	fRec13[2];
	double 	fRec14[2];
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT	*fslider4_;
	double 	fRec15[2];
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT	*fslider5_;
	double 	fRec19[2];
	double 	fRec18[3];
	double 	fVec1[2];
	double 	fRec17[2];
	double 	fRec16[3];
	double *fRec10;
	FAUSTFLOAT 	fbargraph1;
	FAUSTFLOAT	*fbargraph1_;
	FAUSTFLOAT 	fslider6;
	FAUSTFLOAT	*fslider6_;
	double 	fRec22[2];
	double 	fRec23[2];
	double 	fRec24[2];
	double 	fRec25[2];
	FAUSTFLOAT 	fslider7;
	FAUSTFLOAT	*fslider7_;
	double 	fRec26[2];
	FAUSTFLOAT 	fslider8;
	FAUSTFLOAT	*fslider8_;
	double 	fRec30[2];
	double 	fRec29[3];
	double 	fVec2[2];
	double 	fRec28[2];
	double 	fRec27[3];
	double *fRec21;
	FAUSTFLOAT 	fbargraph2;
	FAUSTFLOAT	*fbargraph2_;
	FAUSTFLOAT 	fslider9;
	FAUSTFLOAT	*fslider9_;
	double 	fRec33[2];
	double 	fRec34[2];
	double 	fRec35[2];
	double 	fRec36[2];
	FAUSTFLOAT 	fslider10;
	FAUSTFLOAT	*fslider10_;
	double 	fRec37[2];
	FAUSTFLOAT 	fslider11;
	FAUSTFLOAT	*fslider11_;
	double 	fRec41[2];
	double 	fRec40[3];
	double 	fVec3[2];
	double 	fRec39[2];
	double 	fRec38[3];
	double *fRec32;
	FAUSTFLOAT 	fbargraph3;
	FAUSTFLOAT	*fbargraph3_;
	FAUSTFLOAT 	fslider12;
	FAUSTFLOAT	*fslider12_;
	double 	fRec44[2];
	double 	fRec45[2];
	double 	fRec46[2];
	double 	fRec47[2];
	FAUSTFLOAT 	fslider13;
	FAUSTFLOAT	*fslider13_;
	double 	fRec48[2];
	double 	fRec50[2];
	double 	fRec49[3];
	double *fRec43;
	FAUSTFLOAT 	fbargraph4;
	FAUSTFLOAT	*fbargraph4_;
	bool mem_allocated;
	void mem_alloc();
	void mem_free();
	void connect(uint32_t port,void* data);
	void clear_state_f();
	int activate(bool start);
	void init(uint32_t samplingFreq);
	void compute(int count, float *input0, float *output0);

	static void clear_state_f_static(PluginLV2*);
	static int activate_static(bool start, PluginLV2*);
	static void init_static(uint32_t samplingFreq, PluginLV2*);
	static void compute_static(int count, float *input0, float *output0, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginLV2(),
	  fRec1(0),
	  fRec10(0),
	  fRec21(0),
	  fRec32(0),
	  fRec43(0),
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
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<3; i++) fRec7[i] = 0;
	for (int i=0; i<524288; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<3; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<3; i++) fRec16[i] = 0;
	for (int i=0; i<524288; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fRec25[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<2; i++) fRec30[i] = 0;
	for (int i=0; i<3; i++) fRec29[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec28[i] = 0;
	for (int i=0; i<3; i++) fRec27[i] = 0;
	for (int i=0; i<524288; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fRec33[i] = 0;
	for (int i=0; i<2; i++) fRec34[i] = 0;
	for (int i=0; i<2; i++) fRec35[i] = 0;
	for (int i=0; i<2; i++) fRec36[i] = 0;
	for (int i=0; i<2; i++) fRec37[i] = 0;
	for (int i=0; i<2; i++) fRec41[i] = 0;
	for (int i=0; i<3; i++) fRec40[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec39[i] = 0;
	for (int i=0; i<3; i++) fRec38[i] = 0;
	for (int i=0; i<524288; i++) fRec32[i] = 0;
	for (int i=0; i<2; i++) fRec44[i] = 0;
	for (int i=0; i<2; i++) fRec45[i] = 0;
	for (int i=0; i<2; i++) fRec46[i] = 0;
	for (int i=0; i<2; i++) fRec47[i] = 0;
	for (int i=0; i<2; i++) fRec48[i] = 0;
	for (int i=0; i<2; i++) fRec50[i] = 0;
	for (int i=0; i<3; i++) fRec49[i] = 0;
	for (int i=0; i<524288; i++) fRec43[i] = 0;
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
	fConst2 = (1e+01 / double(iConst0));
	fConst3 = (0 - fConst2);
	iConst4 = (60 * iConst0);
	fConst5 = (3.141592653589793 / double(iConst0));
	IOTA = 0;
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void Dsp::mem_alloc()
{
	if (!fRec1) fRec1 = new double[524288];
	if (!fRec10) fRec10 = new double[524288];
	if (!fRec21) fRec21 = new double[524288];
	if (!fRec32) fRec32 = new double[524288];
	if (!fRec43) fRec43 = new double[524288];
	mem_allocated = true;
}

void Dsp::mem_free()
{
	mem_allocated = false;
	if (fRec1) { delete fRec1; fRec1 = 0; }
	if (fRec10) { delete fRec10; fRec10 = 0; }
	if (fRec21) { delete fRec21; fRec21 = 0; }
	if (fRec32) { delete fRec32; fRec32 = 0; }
	if (fRec43) { delete fRec43; fRec43 = 0; }
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

void always_inline Dsp::compute(int count, float *input0, float *output0)
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
	double 	fSlow0 = (double(iConst4) / fslider0);
	double 	fSlow1 = (1.000000000000001e-05 * fslider1);
	double 	fSlow2 = tan((fConst5 * fslider2));
	double 	fSlow3 = (1.0 / faustpower<2>(fSlow2));
	double 	fSlow4 = (2 * (1 - fSlow3));
	double 	fSlow5 = (1.0 / fSlow2);
	double 	fSlow6 = (1 + ((fSlow5 - 1.0000000000000004) / fSlow2));
	double 	fSlow7 = (1 + ((1.0000000000000004 + fSlow5) / fSlow2));
	double 	fSlow8 = (1.0 / fSlow7);
	double 	fSlow9 = (1 + fSlow5);
	double 	fSlow10 = (0 - ((1 - fSlow5) / fSlow9));
	double 	fSlow11 = (0 - fSlow5);
	double 	fSlow12 = (1.0 / fSlow9);
	double 	fSlow13 = (2 * (0 - fSlow3));
	double 	fSlow14 = (double(iConst4) / fslider3);
	double 	fSlow15 = (1.000000000000001e-05 * fslider4);
	double 	fSlow16 = tan((fConst5 * fslider5));
	double 	fSlow17 = (1.0 / faustpower<2>(fSlow16));
	double 	fSlow18 = (2 * (1 - fSlow17));
	double 	fSlow19 = (1.0 / fSlow16);
	double 	fSlow20 = (1 + ((fSlow19 - 1.0000000000000004) / fSlow16));
	double 	fSlow21 = (1 + ((1.0000000000000004 + fSlow19) / fSlow16));
	double 	fSlow22 = (1.0 / fSlow21);
	double 	fSlow23 = (1 + fSlow19);
	double 	fSlow24 = (0 - ((1 - fSlow19) / fSlow23));
	double 	fSlow25 = (1.0 / (fSlow7 * fSlow16));
	double 	fSlow26 = (0 - fSlow19);
	double 	fSlow27 = (1.0 / fSlow23);
	double 	fSlow28 = (2 * (0 - fSlow17));
	double 	fSlow29 = (double(iConst4) / fslider6);
	double 	fSlow30 = (1.000000000000001e-05 * fslider7);
	double 	fSlow31 = tan((fConst5 * fslider8));
	double 	fSlow32 = (1.0 / faustpower<2>(fSlow31));
	double 	fSlow33 = (2 * (1 - fSlow32));
	double 	fSlow34 = (1.0 / fSlow31);
	double 	fSlow35 = (1 + ((fSlow34 - 1.0000000000000004) / fSlow31));
	double 	fSlow36 = (1 + ((1.0000000000000004 + fSlow34) / fSlow31));
	double 	fSlow37 = (1.0 / fSlow36);
	double 	fSlow38 = (1 + fSlow34);
	double 	fSlow39 = (0 - ((1 - fSlow34) / fSlow38));
	double 	fSlow40 = (1.0 / (fSlow21 * fSlow31));
	double 	fSlow41 = (0 - fSlow34);
	double 	fSlow42 = (1.0 / fSlow38);
	double 	fSlow43 = (2 * (0 - fSlow32));
	double 	fSlow44 = (double(iConst4) / fslider9);
	double 	fSlow45 = (1.000000000000001e-05 * fslider10);
	double 	fSlow46 = tan((fConst5 * fslider11));
	double 	fSlow47 = (1.0 / faustpower<2>(fSlow46));
	double 	fSlow48 = (2 * (1 - fSlow47));
	double 	fSlow49 = (1.0 / fSlow46);
	double 	fSlow50 = (1 + ((fSlow49 - 1.0000000000000004) / fSlow46));
	double 	fSlow51 = (1.0 / (1 + ((1.0000000000000004 + fSlow49) / fSlow46)));
	double 	fSlow52 = (1 + fSlow49);
	double 	fSlow53 = (0 - ((1 - fSlow49) / fSlow52));
	double 	fSlow54 = (1.0 / (fSlow36 * fSlow46));
	double 	fSlow55 = (0 - fSlow49);
	double 	fSlow56 = (1.0 / fSlow52);
	double 	fSlow57 = (2 * (0 - fSlow47));
	double 	fSlow58 = (double(iConst4) / fslider12);
	double 	fSlow59 = (1.000000000000001e-05 * fslider13);
	for (int i=0; i<count; i++) {
		double fTemp0 = ((int((fRec2[1] != 0.0)))?((int(((fRec3[1] > 0.0) & (fRec3[1] < 1.0))))?fRec2[1]:0):((int(((fRec3[1] == 0.0) & (fSlow0 != fRec4[1]))))?fConst2:((int(((fRec3[1] == 1.0) & (fSlow0 != fRec5[1]))))?fConst3:0)));
		fRec2[0] = fTemp0;
		fRec3[0] = max(0.0, min(1.0, (fRec3[1] + fTemp0)));
		fRec4[0] = ((int(((fRec3[1] >= 1.0) & (fRec5[1] != fSlow0))))?fSlow0:fRec4[1]);
		fRec5[0] = ((int(((fRec3[1] <= 0.0) & (fRec4[1] != fSlow0))))?fSlow0:fRec5[1]);
		fRec6[0] = (fSlow1 + (0.999 * fRec6[1]));
		double fTemp1 = (double)input0[i];
		fVec0[0] = fTemp1;
		fRec8[0] = ((fSlow12 * ((fSlow11 * fVec0[1]) + (fSlow5 * fVec0[0]))) + (fSlow10 * fRec8[1]));
		fRec7[0] = (fRec8[0] - (fSlow8 * ((fSlow6 * fRec7[2]) + (fSlow4 * fRec7[1]))));
		fRec1[IOTA&524287] = ((fSlow8 * (((fSlow3 * fRec7[0]) + (fSlow13 * fRec7[1])) + (fSlow3 * fRec7[2]))) + (fRec6[0] * ((fRec3[0] * fRec1[(IOTA-int((1 + int((int(fRec5[0]) & 262143)))))&524287]) + ((1.0 - fRec3[0]) * fRec1[(IOTA-int((1 + int((int(fRec4[0]) & 262143)))))&524287]))));
		double fTemp2 = fRec1[(IOTA-0)&524287];
		double 	fRec0 = max(fConst1, fabs(fTemp2));
		fbargraph0 = fRec0;
		double fTemp3 = ((int((fRec11[1] != 0.0)))?((int(((fRec12[1] > 0.0) & (fRec12[1] < 1.0))))?fRec11[1]:0):((int(((fRec12[1] == 0.0) & (fSlow14 != fRec13[1]))))?fConst2:((int(((fRec12[1] == 1.0) & (fSlow14 != fRec14[1]))))?fConst3:0)));
		fRec11[0] = fTemp3;
		fRec12[0] = max(0.0, min(1.0, (fRec12[1] + fTemp3)));
		fRec13[0] = ((int(((fRec12[1] >= 1.0) & (fRec14[1] != fSlow14))))?fSlow14:fRec13[1]);
		fRec14[0] = ((int(((fRec12[1] <= 0.0) & (fRec13[1] != fSlow14))))?fSlow14:fRec14[1]);
		fRec15[0] = (fSlow15 + (0.999 * fRec15[1]));
		double fTemp4 = (fVec0[0] + fVec0[1]);
		fRec19[0] = ((fSlow12 * fTemp4) + (fSlow10 * fRec19[1]));
		fRec18[0] = (fRec19[0] - (fSlow8 * ((fSlow6 * fRec18[2]) + (fSlow4 * fRec18[1]))));
		double fTemp5 = (fRec18[2] + (fRec18[0] + (2 * fRec18[1])));
		fVec1[0] = (fSlow8 * fTemp5);
		fRec17[0] = ((fSlow27 * ((fSlow26 * fVec1[1]) + (fSlow25 * fTemp5))) + (fSlow24 * fRec17[1]));
		fRec16[0] = (fRec17[0] - (fSlow22 * ((fSlow20 * fRec16[2]) + (fSlow18 * fRec16[1]))));
		fRec10[IOTA&524287] = ((fSlow22 * (((fSlow17 * fRec16[0]) + (fSlow28 * fRec16[1])) + (fSlow17 * fRec16[2]))) + (fRec15[0] * ((fRec12[0] * fRec10[(IOTA-int((1 + int((int(fRec14[0]) & 262143)))))&524287]) + ((1.0 - fRec12[0]) * fRec10[(IOTA-int((1 + int((int(fRec13[0]) & 262143)))))&524287]))));
		double fTemp6 = fRec10[(IOTA-0)&524287];
		double 	fRec9 = max(fConst1, fabs(fTemp6));
		fbargraph1 = fRec9;
		double fTemp7 = ((int((fRec22[1] != 0.0)))?((int(((fRec23[1] > 0.0) & (fRec23[1] < 1.0))))?fRec22[1]:0):((int(((fRec23[1] == 0.0) & (fSlow29 != fRec24[1]))))?fConst2:((int(((fRec23[1] == 1.0) & (fSlow29 != fRec25[1]))))?fConst3:0)));
		fRec22[0] = fTemp7;
		fRec23[0] = max(0.0, min(1.0, (fRec23[1] + fTemp7)));
		fRec24[0] = ((int(((fRec23[1] >= 1.0) & (fRec25[1] != fSlow29))))?fSlow29:fRec24[1]);
		fRec25[0] = ((int(((fRec23[1] <= 0.0) & (fRec24[1] != fSlow29))))?fSlow29:fRec25[1]);
		fRec26[0] = (fSlow30 + (0.999 * fRec26[1]));
		fRec30[0] = ((fSlow27 * fTemp4) + (fSlow24 * fRec30[1]));
		fRec29[0] = (fRec30[0] - (fSlow22 * ((fSlow20 * fRec29[2]) + (fSlow18 * fRec29[1]))));
		double fTemp8 = (fRec29[2] + (fRec29[0] + (2 * fRec29[1])));
		fVec2[0] = (fSlow22 * fTemp8);
		fRec28[0] = ((fSlow42 * ((fSlow41 * fVec2[1]) + (fSlow40 * fTemp8))) + (fSlow39 * fRec28[1]));
		fRec27[0] = (fRec28[0] - (fSlow37 * ((fSlow35 * fRec27[2]) + (fSlow33 * fRec27[1]))));
		fRec21[IOTA&524287] = ((fSlow37 * (((fSlow32 * fRec27[0]) + (fSlow43 * fRec27[1])) + (fSlow32 * fRec27[2]))) + (fRec26[0] * ((fRec23[0] * fRec21[(IOTA-int((1 + int((int(fRec25[0]) & 262143)))))&524287]) + ((1.0 - fRec23[0]) * fRec21[(IOTA-int((1 + int((int(fRec24[0]) & 262143)))))&524287]))));
		double fTemp9 = fRec21[(IOTA-0)&524287];
		double 	fRec20 = max(fConst1, fabs(fTemp9));
		fbargraph2 = fRec20;
		double fTemp10 = ((int((fRec33[1] != 0.0)))?((int(((fRec34[1] > 0.0) & (fRec34[1] < 1.0))))?fRec33[1]:0):((int(((fRec34[1] == 0.0) & (fSlow44 != fRec35[1]))))?fConst2:((int(((fRec34[1] == 1.0) & (fSlow44 != fRec36[1]))))?fConst3:0)));
		fRec33[0] = fTemp10;
		fRec34[0] = max(0.0, min(1.0, (fRec34[1] + fTemp10)));
		fRec35[0] = ((int(((fRec34[1] >= 1.0) & (fRec36[1] != fSlow44))))?fSlow44:fRec35[1]);
		fRec36[0] = ((int(((fRec34[1] <= 0.0) & (fRec35[1] != fSlow44))))?fSlow44:fRec36[1]);
		fRec37[0] = (fSlow45 + (0.999 * fRec37[1]));
		fRec41[0] = ((fSlow42 * fTemp4) + (fSlow39 * fRec41[1]));
		fRec40[0] = (fRec41[0] - (fSlow37 * ((fSlow35 * fRec40[2]) + (fSlow33 * fRec40[1]))));
		double fTemp11 = (fRec40[2] + (fRec40[0] + (2 * fRec40[1])));
		fVec3[0] = (fSlow37 * fTemp11);
		fRec39[0] = ((fSlow56 * ((fSlow55 * fVec3[1]) + (fSlow54 * fTemp11))) + (fSlow53 * fRec39[1]));
		fRec38[0] = (fRec39[0] - (fSlow51 * ((fSlow50 * fRec38[2]) + (fSlow48 * fRec38[1]))));
		fRec32[IOTA&524287] = ((fSlow51 * (((fSlow47 * fRec38[0]) + (fSlow57 * fRec38[1])) + (fSlow47 * fRec38[2]))) + (fRec37[0] * ((fRec34[0] * fRec32[(IOTA-int((1 + int((int(fRec36[0]) & 262143)))))&524287]) + ((1.0 - fRec34[0]) * fRec32[(IOTA-int((1 + int((int(fRec35[0]) & 262143)))))&524287]))));
		double fTemp12 = fRec32[(IOTA-0)&524287];
		double 	fRec31 = max(fConst1, fabs(fTemp12));
		fbargraph3 = fRec31;
		double fTemp13 = ((int((fRec44[1] != 0.0)))?((int(((fRec45[1] > 0.0) & (fRec45[1] < 1.0))))?fRec44[1]:0):((int(((fRec45[1] == 0.0) & (fSlow58 != fRec46[1]))))?fConst2:((int(((fRec45[1] == 1.0) & (fSlow58 != fRec47[1]))))?fConst3:0)));
		fRec44[0] = fTemp13;
		fRec45[0] = max(0.0, min(1.0, (fRec45[1] + fTemp13)));
		fRec46[0] = ((int(((fRec45[1] >= 1.0) & (fRec47[1] != fSlow58))))?fSlow58:fRec46[1]);
		fRec47[0] = ((int(((fRec45[1] <= 0.0) & (fRec46[1] != fSlow58))))?fSlow58:fRec47[1]);
		fRec48[0] = (fSlow59 + (0.999 * fRec48[1]));
		fRec50[0] = ((fSlow56 * fTemp4) + (fSlow53 * fRec50[1]));
		fRec49[0] = (fRec50[0] - (fSlow51 * ((fSlow50 * fRec49[2]) + (fSlow48 * fRec49[1]))));
		fRec43[IOTA&524287] = ((fSlow51 * (fRec49[2] + (fRec49[0] + (2 * fRec49[1])))) + (fRec48[0] * ((fRec45[0] * fRec43[(IOTA-int((1 + int((int(fRec47[0]) & 262143)))))&524287]) + ((1.0 - fRec45[0]) * fRec43[(IOTA-int((1 + int((int(fRec46[0]) & 262143)))))&524287]))));
		double fTemp14 = fRec43[(IOTA-0)&524287];
		double 	fRec42 = max(fConst1, fabs(fTemp14));
		fbargraph4 = fRec42;
		output0[i] = (FAUSTFLOAT)((((fTemp14 + fTemp12) + fTemp9) + fTemp6) + fTemp2);
		// post processing
		fRec49[2] = fRec49[1]; fRec49[1] = fRec49[0];
		fRec50[1] = fRec50[0];
		fRec48[1] = fRec48[0];
		fRec47[1] = fRec47[0];
		fRec46[1] = fRec46[0];
		fRec45[1] = fRec45[0];
		fRec44[1] = fRec44[0];
		fRec38[2] = fRec38[1]; fRec38[1] = fRec38[0];
		fRec39[1] = fRec39[0];
		fVec3[1] = fVec3[0];
		fRec40[2] = fRec40[1]; fRec40[1] = fRec40[0];
		fRec41[1] = fRec41[0];
		fRec37[1] = fRec37[0];
		fRec36[1] = fRec36[0];
		fRec35[1] = fRec35[0];
		fRec34[1] = fRec34[0];
		fRec33[1] = fRec33[0];
		fRec27[2] = fRec27[1]; fRec27[1] = fRec27[0];
		fRec28[1] = fRec28[0];
		fVec2[1] = fVec2[0];
		fRec29[2] = fRec29[1]; fRec29[1] = fRec29[0];
		fRec30[1] = fRec30[0];
		fRec26[1] = fRec26[0];
		fRec25[1] = fRec25[0];
		fRec24[1] = fRec24[0];
		fRec23[1] = fRec23[0];
		fRec22[1] = fRec22[0];
		fRec16[2] = fRec16[1]; fRec16[1] = fRec16[0];
		fRec17[1] = fRec17[0];
		fVec1[1] = fVec1[0];
		fRec18[2] = fRec18[1]; fRec18[1] = fRec18[0];
		fRec19[1] = fRec19[0];
		fRec15[1] = fRec15[0];
		fRec14[1] = fRec14[0];
		fRec13[1] = fRec13[0];
		fRec12[1] = fRec12[0];
		fRec11[1] = fRec11[0];
		IOTA = IOTA+1;
		fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
		fVec0[1] = fVec0[0];
		fRec6[1] = fRec6[0];
		fRec5[1] = fRec5[0];
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		fRec2[1] = fRec2[0];
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

void __rt_func Dsp::compute_static(int count, float *input0, float *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case CROSSOVER_B1_B2: 
		fslider11_ = (float*)data; // , 8e+01, 2e+01, 2e+04, 1.08 
		break;
	case CROSSOVER_B2_B3: 
		fslider8_ = (float*)data; // , 2.1e+02, 2e+01, 2e+04, 1.08 
		break;
	case CROSSOVER_B3_B4: 
		fslider5_ = (float*)data; // , 1.7e+03, 2e+01, 2e+04, 1.08 
		break;
	case CROSSOVER_B4_B5: 
		fslider2_ = (float*)data; // , 5e+03, 2e+01, 2e+04, 1.08 
		break;
	case PERCENT1: 
		fslider13_ = (float*)data; // , 1e+01, 0.0, 1e+02, 0.1 
		break;
	case PERCENT2: 
		fslider10_ = (float*)data; // , 3e+01, 0.0, 1e+02, 0.1 
		break;
	case PERCENT3: 
		fslider7_ = (float*)data; // , 45.0, 0.0, 1e+02, 0.1 
		break;
	case PERCENT4: 
		fslider4_ = (float*)data; // , 2e+01, 0.0, 1e+02, 0.1 
		break;
	case PERCENT5: 
		fslider1_ = (float*)data; // , 0.0, 0.0, 1e+02, 0.1 
		break;
	case TIME1: 
		fslider12_ = (float*)data; // , 3e+01, 24.0, 3.6e+02, 1.0 
		break;
	case TIME2: 
		fslider9_ = (float*)data; // , 6e+01, 24.0, 3.6e+02, 1.0 
		break;
	case TIME3: 
		fslider6_ = (float*)data; // , 1.2e+02, 24.0, 3.6e+02, 1.0 
		break;
	case TIME4: 
		fslider3_ = (float*)data; // , 1.5e+02, 24.0, 3.6e+02, 1.0 
		break;
	case TIME5: 
		fslider0_ = (float*)data; // , 2.4e+02, 24.0, 3.6e+02, 1.0 
		break;
	case V1: 
		fbargraph4_ = (float*)data; // , -70.0, -70.0, 4.0, 1.0 
		break;
	case V2: 
		fbargraph3_ = (float*)data; // , -70.0, -70.0, 4.0, 1.0 
		break;
	case V3: 
		fbargraph2_ = (float*)data; // , -70.0, -70.0, 4.0, 1.0 
		break;
	case V4: 
		fbargraph1_ = (float*)data; // , -70.0, -70.0, 4.0, 1.0 
		break;
	case V5: 
		fbargraph0_ = (float*)data; // , -70.0, -70.0, 4.0, 1.0 
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
