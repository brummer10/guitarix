// generated from file '../src/LV2/faust/stereoecho.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)


namespace stereoecho {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	int 	iVec0[2];
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	float 	fConst0;
	float 	fConst1;
	float 	fRec1[2];
	float 	fRec2[2];
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT	*fcheckbox0_;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	float 	fConst2;
	float 	fRec3[2];
	float 	fRec4[2];
	int 	iRec5[2];
	int 	iRec6[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	int 	IOTA;
	float *fRec0;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	float 	fRec8[2];
	float 	fRec9[2];
	int 	iRec10[2];
	int 	iRec11[2];
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT	*fslider4_;
	float *fRec7;

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
	  fRec0(0),
	  fRec7(0),
	  mem_allocated(false) {
	version = PLUGINLV2_VERSION;
	id = "stereoecho";
	name = N_("Stereo Echo");
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
	for (int i=0; i<2; i++) iVec0[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) iRec5[i] = 0;
	for (int i=0; i<2; i++) iRec6[i] = 0;
	for (int i=0; i<262144; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) iRec10[i] = 0;
	for (int i=0; i<2; i++) iRec11[i] = 0;
	for (int i=0; i<262144; i++) fRec7[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = min(1.92e+05f, max(1.0f, (float)fSamplingFreq));
	fConst1 = (6.2831855f / fConst0);
	fConst2 = (0.001f * fConst0);
	IOTA = 0;
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void Dsp::mem_alloc()
{
	if (!fRec0) fRec0 = new float[262144];
	if (!fRec7) fRec7 = new float[262144];
	mem_allocated = true;
}

void Dsp::mem_free()
{
	mem_allocated = false;
	if (fRec0) { delete fRec0; fRec0 = 0; }
	if (fRec7) { delete fRec7; fRec7 = 0; }
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
#define fslider0 (*fslider0_)
#define fcheckbox0 (*fcheckbox0_)
#define fslider1 (*fslider1_)
#define fslider2 (*fslider2_)
#define fslider3 (*fslider3_)
#define fslider4 (*fslider4_)
	float 	fSlow0 = (fConst1 * float(fslider0));
	float 	fSlow1 = cosf(fSlow0);
	float 	fSlow2 = sinf(fSlow0);
	float 	fSlow3 = (0 - fSlow2);
	float 	fSlow4 = float(fcheckbox0);
	int 	iSlow5 = (int((fConst2 * float(fslider1))) - 1);
	float 	fSlow6 = (0.01f * float(fslider2));
	int 	iSlow7 = (int((fConst2 * float(fslider3))) - 1);
	float 	fSlow8 = (0.01f * float(fslider4));
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		fRec1[0] = ((fSlow2 * fRec2[1]) + (fSlow1 * fRec1[1]));
		fRec2[0] = ((1 + ((fSlow1 * fRec2[1]) + (fSlow3 * fRec1[1]))) - iVec0[1]);
		float fTemp0 = ((int((fRec3[1] != 0.0f)))?((int(((fRec4[1] > 0.0f) & (fRec4[1] < 1.0f))))?fRec3[1]:0):((int(((fRec4[1] == 0.0f) & (iSlow5 != iRec5[1]))))?0.0009765625f:((int(((fRec4[1] == 1.0f) & (iSlow5 != iRec6[1]))))?-0.0009765625f:0)));
		fRec3[0] = fTemp0;
		fRec4[0] = max(0.0f, min(1.0f, (fRec4[1] + fTemp0)));
		iRec5[0] = ((int(((fRec4[1] >= 1.0f) & (iRec6[1] != iSlow5))))?iSlow5:iRec5[1]);
		iRec6[0] = ((int(((fRec4[1] <= 0.0f) & (iRec5[1] != iSlow5))))?iSlow5:iRec6[1]);
		fRec0[IOTA&262143] = ((float)input0[i] + (fSlow6 * (((fRec0[(IOTA-int((1 + int((int(iRec5[0]) & 131071)))))&262143] * (1.0f - fRec4[0])) + (fRec4[0] * fRec0[(IOTA-int((1 + int((int(iRec6[0]) & 131071)))))&262143])) * (1 - (fSlow4 * fRec1[0])))));
		output0[i] = (FAUSTFLOAT)fRec0[(IOTA-0)&262143];
		float fTemp1 = ((int((fRec8[1] != 0.0f)))?((int(((fRec9[1] > 0.0f) & (fRec9[1] < 1.0f))))?fRec8[1]:0):((int(((fRec9[1] == 0.0f) & (iSlow7 != iRec10[1]))))?0.0009765625f:((int(((fRec9[1] == 1.0f) & (iSlow7 != iRec11[1]))))?-0.0009765625f:0)));
		fRec8[0] = fTemp1;
		fRec9[0] = max(0.0f, min(1.0f, (fRec9[1] + fTemp1)));
		iRec10[0] = ((int(((fRec9[1] >= 1.0f) & (iRec11[1] != iSlow7))))?iSlow7:iRec10[1]);
		iRec11[0] = ((int(((fRec9[1] <= 0.0f) & (iRec10[1] != iSlow7))))?iSlow7:iRec11[1]);
		fRec7[IOTA&262143] = ((float)input1[i] + (fSlow8 * (((fRec7[(IOTA-int((1 + int((int(iRec10[0]) & 131071)))))&262143] * (1.0f - fRec9[0])) + (fRec9[0] * fRec7[(IOTA-int((1 + int((int(iRec11[0]) & 131071)))))&262143])) * (1 - (fSlow4 * (0 - fRec1[0]))))));
		output1[i] = (FAUSTFLOAT)fRec7[(IOTA-0)&262143];
		// post processing
		iRec11[1] = iRec11[0];
		iRec10[1] = iRec10[0];
		fRec9[1] = fRec9[0];
		fRec8[1] = fRec8[0];
		IOTA = IOTA+1;
		iRec6[1] = iRec6[0];
		iRec5[1] = iRec5[0];
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
		iVec0[1] = iVec0[0];
	}
#undef fslider0
#undef fcheckbox0
#undef fslider1
#undef fslider2
#undef fslider3
#undef fslider4
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case LFOFREQ: 
		fslider0_ = (float*)data; // , 0.2f, 0.0f, 5.0f, 0.01f 
		break;
	// static const value_pair fcheckbox0_values[] = {{"linear"},{"pingpong"},{0}};
	case INVERT: 
		fcheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case PERCENT_L: 
		fslider2_ = (float*)data; // , 0.0f, 0.0f, 1e+02f, 0.1f 
		break;
	case PERCENT_R: 
		fslider4_ = (float*)data; // , 0.0f, 0.0f, 1e+02f, 0.1f 
		break;
	case TIME_L: 
		fslider1_ = (float*)data; // , 1.0f, 1.0f, 2e+03f, 1.0f 
		break;
	case TIME_R: 
		fslider3_ = (float*)data; // , 1.0f, 1.0f, 2e+03f, 1.0f 
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
   LFOFREQ, 
   INVERT, 
   PERCENT_L, 
   PERCENT_R, 
   TIME_L, 
   TIME_R, 
} PortIndex;
*/

} // end namespace stereoecho
