// generated from file '../src/LV2/faust/stereodelay.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)


namespace stereodelay {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	int 	IOTA;
	float *fVec0;
	int 	iVec1[2];
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	int 	iConst0;
	float 	fConst1;
	float 	fRec0[2];
	float 	fRec1[2];
	float 	fRec2[2];
	float 	fRec3[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	float 	fConst2;
	float 	fRec4[2];
	float 	fRec5[2];
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT	*fcheckbox0_;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	float 	fRec6[2];
	float *fVec2;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	float 	fRec7[2];
	float 	fRec8[2];
	float 	fRec9[2];
	float 	fRec10[2];
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT	*fslider4_;
	float 	fRec11[2];
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
	  fVec0(0),
	  fVec2(0),
	  mem_allocated(false) {
	version = PLUGINLV2_VERSION;
	id = "stereodelay";
	name = N_("Stereo Delay");
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
	for (int i=0; i<262144; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) iVec1[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<262144; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
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
	fConst1 = (0.001f * iConst0);
	fConst2 = (6.283185307179586f / float(iConst0));
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void Dsp::mem_alloc()
{
	if (!fVec0) fVec0 = new float[262144];
	if (!fVec2) fVec2 = new float[262144];
	mem_allocated = true;
}

void Dsp::mem_free()
{
	mem_allocated = false;
	if (fVec0) { delete fVec0; fVec0 = 0; }
	if (fVec2) { delete fVec2; fVec2 = 0; }
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
#define fslider1 (*fslider1_)
#define fcheckbox0 (*fcheckbox0_)
#define fslider2 (*fslider2_)
#define fslider3 (*fslider3_)
#define fslider4 (*fslider4_)
	float 	fSlow0 = (fConst1 * float(fslider0));
	float 	fSlow1 = (fConst2 * float(fslider1));
	float 	fSlow2 = cosf(fSlow1);
	float 	fSlow3 = sinf(fSlow1);
	float 	fSlow4 = (0 - fSlow3);
	float 	fSlow5 = float(fcheckbox0);
	float 	fSlow6 = (0.0010000000000000009f * powf(10,(0.05f * float(fslider2))));
	float 	fSlow7 = (fConst1 * float(fslider3));
	float 	fSlow8 = (0.0010000000000000009f * powf(10,(0.05f * float(fslider4))));
	for (int i=0; i<count; i++) {
		float fTemp0 = (float)input0[i];
		fVec0[IOTA&262143] = fTemp0;
		iVec1[0] = 1;
		float fTemp1 = ((int((fRec0[1] != 0.0f)))?((int(((fRec1[1] > 0.0f) & (fRec1[1] < 1.0f))))?fRec0[1]:0):((int(((fRec1[1] == 0.0f) & (fSlow0 != fRec2[1]))))?0.0009765625f:((int(((fRec1[1] == 1.0f) & (fSlow0 != fRec3[1]))))?-0.0009765625f:0)));
		fRec0[0] = fTemp1;
		fRec1[0] = max(0.0f, min(1.0f, (fRec1[1] + fTemp1)));
		fRec2[0] = ((int(((fRec1[1] >= 1.0f) & (fRec3[1] != fSlow0))))?fSlow0:fRec2[1]);
		fRec3[0] = ((int(((fRec1[1] <= 0.0f) & (fRec2[1] != fSlow0))))?fSlow0:fRec3[1]);
		fRec4[0] = ((fSlow3 * fRec5[1]) + (fSlow2 * fRec4[1]));
		fRec5[0] = ((1 + ((fSlow2 * fRec5[1]) + (fSlow4 * fRec4[1]))) - iVec1[1]);
		fRec6[0] = ((0.999f * fRec6[1]) + fSlow6);
		output0[i] = (FAUSTFLOAT)(fVec0[IOTA&262143] + ((fRec6[0] * (1 - (fSlow5 * fRec4[0]))) * (((1.0f - fRec1[0]) * fVec0[(IOTA-int((int(fRec2[0]) & 262143)))&262143]) + (fRec1[0] * fVec0[(IOTA-int((int(fRec3[0]) & 262143)))&262143]))));
		float fTemp2 = (float)input1[i];
		fVec2[IOTA&262143] = fTemp2;
		float fTemp3 = ((int((fRec7[1] != 0.0f)))?((int(((fRec8[1] > 0.0f) & (fRec8[1] < 1.0f))))?fRec7[1]:0):((int(((fRec8[1] == 0.0f) & (fSlow7 != fRec9[1]))))?0.0009765625f:((int(((fRec8[1] == 1.0f) & (fSlow7 != fRec10[1]))))?-0.0009765625f:0)));
		fRec7[0] = fTemp3;
		fRec8[0] = max(0.0f, min(1.0f, (fRec8[1] + fTemp3)));
		fRec9[0] = ((int(((fRec8[1] >= 1.0f) & (fRec10[1] != fSlow7))))?fSlow7:fRec9[1]);
		fRec10[0] = ((int(((fRec8[1] <= 0.0f) & (fRec9[1] != fSlow7))))?fSlow7:fRec10[1]);
		fRec11[0] = ((0.999f * fRec11[1]) + fSlow8);
		output1[i] = (FAUSTFLOAT)(fVec2[IOTA&262143] + ((fRec11[0] * (1 - (fSlow5 * (0 - fRec4[0])))) * (((1.0f - fRec8[0]) * fVec2[(IOTA-int((int(fRec9[0]) & 262143)))&262143]) + (fRec8[0] * fVec2[(IOTA-int((int(fRec10[0]) & 262143)))&262143]))));
		// post processing
		fRec11[1] = fRec11[0];
		fRec10[1] = fRec10[0];
		fRec9[1] = fRec9[0];
		fRec8[1] = fRec8[0];
		fRec7[1] = fRec7[0];
		fRec6[1] = fRec6[0];
		fRec5[1] = fRec5[0];
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
		iVec1[1] = iVec1[0];
		IOTA = IOTA+1;
	}
#undef fslider0
#undef fslider1
#undef fcheckbox0
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
		fslider1_ = (float*)data; // , 0.2f, 0.0f, 5.0f, 0.01f 
		break;
	// static const value_pair fcheckbox0_values[] = {{"linear"},{"pingpong"},{0}};
	case INVERT: 
		fcheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case L_DELAY: 
		fslider0_ = (float*)data; // , 0.0f, 0.0f, 5e+03f, 1e+01f 
		break;
	case L_GAIN: 
		fslider2_ = (float*)data; // , 0.0f, -2e+01f, 2e+01f, 0.1f 
		break;
	case R_DELAY: 
		fslider3_ = (float*)data; // , 0.0f, 0.0f, 5e+03f, 1e+01f 
		break;
	case R_GAIN: 
		fslider4_ = (float*)data; // , 0.0f, -2e+01f, 2e+01f, 0.1f 
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
   L_DELAY, 
   L_GAIN, 
   R_DELAY, 
   R_GAIN, 
} PortIndex;
*/

} // end namespace stereodelay
