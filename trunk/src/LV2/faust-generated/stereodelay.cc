// generated from file '../src/LV2/faust/stereodelay.dsp' by dsp2cc:
// Code generated with Faust 0.9.46 (http://faust.grame.fr)


namespace stereodelay {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	int 	iVec0[2];
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	int 	iConst0;
	float 	fConst1;
	float 	fRec0[2];
	float 	fRec1[2];
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT	*fcheckbox0_;
	int 	IOTA;
	float *fVec1;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	float 	fConst2;
	float 	fRec2[2];
	float 	fRec3[2];
	float 	fRec4[2];
	float 	fRec5[2];
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
	void compute(int count, float *input0, float *input1, float *output0, float *output1);

	static void clear_state_f_static(PluginLV2*);
	static int activate_static(bool start, PluginLV2*);
	static void init_static(uint32_t samplingFreq, PluginLV2*);
	static void compute_static(int count, float *input0, float *input1, float *output0, float *output1, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginLV2(),
	  fVec1(0),
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
	for (int i=0; i<2; i++) iVec0[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<262144; i++) fVec1[i] = 0;
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
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (6.283185307179586f / iConst0);
	IOTA = 0;
	fConst2 = (0.001f * iConst0);
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void Dsp::mem_alloc()
{
	if (!fVec1) fVec1 = new float[262144];
	if (!fVec2) fVec2 = new float[262144];
	mem_allocated = true;
}

void Dsp::mem_free()
{
	mem_allocated = false;
	if (fVec1) { delete fVec1; fVec1 = 0; }
	if (fVec2) { delete fVec2; fVec2 = 0; }
}

int Dsp::activate(bool start)
{
	if (start) {
		if (!mem_allocated) {
			mem_alloc();
			clear_state_f();
		}
	} else if (!mem_allocated) {
		mem_free();
	}
	return 0;
}

int Dsp::activate_static(bool start, PluginLV2 *p)
{
	return static_cast<Dsp*>(p)->activate(start);
}

inline void Dsp::compute(int count, float *input0, float *input1, float *output0, float *output1)
{
#define fslider0 (*fslider0_)
#define fcheckbox0 (*fcheckbox0_)
#define fslider1 (*fslider1_)
#define fslider2 (*fslider2_)
#define fslider3 (*fslider3_)
#define fslider4 (*fslider4_)
	float 	fSlow0 = (fConst1 * fslider0);
	float 	fSlow1 = sinf(fSlow0);
	float 	fSlow2 = cosf(fSlow0);
	float 	fSlow3 = (0 - fSlow1);
	float 	fSlow4 = fcheckbox0;
	float 	fSlow5 = (fConst2 * fslider1);
	float 	fSlow6 = (0.0010000000000000009f * powf(10,(0.05f * fslider2)));
	float 	fSlow7 = (fConst2 * fslider3);
	float 	fSlow8 = (0.0010000000000000009f * powf(10,(0.05f * fslider4)));
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		fRec0[0] = ((fSlow2 * fRec0[1]) + (fSlow1 * fRec1[1]));
		fRec1[0] = ((1 + ((fSlow3 * fRec0[1]) + (fSlow2 * fRec1[1]))) - iVec0[1]);
		float fTemp0 = (float)input0[i];
		fVec1[IOTA&262143] = fTemp0;
		float fTemp1 = ((int((fRec2[1] != 0.0f)))?((int(((fRec3[1] > 0.0f) & (fRec3[1] < 1.0f))))?fRec2[1]:0):((int(((fRec3[1] == 0.0f) & (fSlow5 != fRec4[1]))))?0.0009765625f:((int(((fRec3[1] == 1.0f) & (fSlow5 != fRec5[1]))))?-0.0009765625f:0)));
		fRec2[0] = fTemp1;
		fRec3[0] = max(0.0f, min(1.0f, (fRec3[1] + fTemp1)));
		fRec4[0] = ((int(((fRec3[1] >= 1.0f) & (fRec5[1] != fSlow5))))?fSlow5:fRec4[1]);
		fRec5[0] = ((int(((fRec3[1] <= 0.0f) & (fRec4[1] != fSlow5))))?fSlow5:fRec5[1]);
		fRec6[0] = (fSlow6 + (0.999f * fRec6[1]));
		output0[i] = (FAUSTFLOAT)(fVec1[IOTA&262143] + ((fRec6[0] * ((fRec3[0] * fVec1[(IOTA-int((int(fRec5[0]) & 262143)))&262143]) + ((1.0f - fRec3[0]) * fVec1[(IOTA-int((int(fRec4[0]) & 262143)))&262143]))) * (1 - (fSlow4 * fRec0[0]))));
		float fTemp2 = (float)input1[i];
		fVec2[IOTA&262143] = fTemp2;
		float fTemp3 = ((int((fRec7[1] != 0.0f)))?((int(((fRec8[1] > 0.0f) & (fRec8[1] < 1.0f))))?fRec7[1]:0):((int(((fRec8[1] == 0.0f) & (fSlow7 != fRec9[1]))))?0.0009765625f:((int(((fRec8[1] == 1.0f) & (fSlow7 != fRec10[1]))))?-0.0009765625f:0)));
		fRec7[0] = fTemp3;
		fRec8[0] = max(0.0f, min(1.0f, (fRec8[1] + fTemp3)));
		fRec9[0] = ((int(((fRec8[1] >= 1.0f) & (fRec10[1] != fSlow7))))?fSlow7:fRec9[1]);
		fRec10[0] = ((int(((fRec8[1] <= 0.0f) & (fRec9[1] != fSlow7))))?fSlow7:fRec10[1]);
		fRec11[0] = (fSlow8 + (0.999f * fRec11[1]));
		output1[i] = (FAUSTFLOAT)(fVec2[IOTA&262143] + ((fRec11[0] * ((fRec8[0] * fVec2[(IOTA-int((int(fRec10[0]) & 262143)))&262143]) + ((1.0f - fRec8[0]) * fVec2[(IOTA-int((int(fRec9[0]) & 262143)))&262143]))) * (1 - (fSlow4 * (0 - fRec0[0])))));
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
		IOTA = IOTA+1;
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
		iVec0[1] = iVec0[0];
	}
#undef fslider0
#undef fcheckbox0
#undef fslider1
#undef fslider2
#undef fslider3
#undef fslider4
}

void Dsp::compute_static(int count, float *input0, float *input1, float *output0, float *output1, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	// static const value_pair fcheckbox0_values[] = {{"linear"},{"pingpong"},{0}};
	case INVERT: 
		fcheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case R_GAIN: 
		fslider4_ = (float*)data; // , 0.0f, -2e+01f, 2e+01f, 0.1f 
		break;
	case R_DELAY: 
		fslider3_ = (float*)data; // , 0.0f, 0.0f, 5e+03f, 1e+01f 
		break;
	case L_GAIN: 
		fslider2_ = (float*)data; // , 0.0f, -2e+01f, 2e+01f, 0.1f 
		break;
	case L_DELAY: 
		fslider1_ = (float*)data; // , 0.0f, 0.0f, 5e+03f, 1e+01f 
		break;
	case LFOFREQ: 
		fslider0_ = (float*)data; // , 0.2f, 0.0f, 5.0f, 0.01f 
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

} // end namespace stereodelay
