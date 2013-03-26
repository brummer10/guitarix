// generated from file '../src/LV2/faust/stereoecho.dsp' by dsp2cc:
// Code generated with Faust 0.9.46 (http://faust.grame.fr)


namespace stereoecho {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	int 	iVec0[2];
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	int 	iConst0;
	float 	fConst1;
	float 	fRec1[2];
	float 	fRec2[2];
	int 	iRec3[2];
	int 	iRec4[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	float 	fConst2;
	float 	fRec5[2];
	float 	fRec6[2];
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT	*fcheckbox0_;
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
	for (int i=0; i<2; i++) iRec3[i] = 0;
	for (int i=0; i<2; i++) iRec4[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
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
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (0.001f * iConst0);
	fConst2 = (6.283185307179586f / iConst0);
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
#define fslider1 (*fslider1_)
#define fcheckbox0 (*fcheckbox0_)
#define fslider2 (*fslider2_)
#define fslider3 (*fslider3_)
#define fslider4 (*fslider4_)
	int 	iSlow0 = (int((fConst1 * fslider0)) - 1);
	float 	fSlow1 = (fConst2 * fslider1);
	float 	fSlow2 = sinf(fSlow1);
	float 	fSlow3 = cosf(fSlow1);
	float 	fSlow4 = (0 - fSlow2);
	float 	fSlow5 = fcheckbox0;
	float 	fSlow6 = (0.01f * fslider2);
	int 	iSlow7 = (int((fConst1 * fslider3)) - 1);
	float 	fSlow8 = (0.01f * fslider4);
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		float fTemp0 = ((int((fRec1[1] != 0.0f)))?((int(((fRec2[1] > 0.0f) & (fRec2[1] < 1.0f))))?fRec1[1]:0):((int(((fRec2[1] == 0.0f) & (iSlow0 != iRec3[1]))))?0.0009765625f:((int(((fRec2[1] == 1.0f) & (iSlow0 != iRec4[1]))))?-0.0009765625f:0)));
		fRec1[0] = fTemp0;
		fRec2[0] = max(0.0f, min(1.0f, (fRec2[1] + fTemp0)));
		iRec3[0] = ((int(((fRec2[1] >= 1.0f) & (iRec4[1] != iSlow0))))?iSlow0:iRec3[1]);
		iRec4[0] = ((int(((fRec2[1] <= 0.0f) & (iRec3[1] != iSlow0))))?iSlow0:iRec4[1]);
		fRec5[0] = ((fSlow3 * fRec5[1]) + (fSlow2 * fRec6[1]));
		fRec6[0] = ((1 + ((fSlow4 * fRec5[1]) + (fSlow3 * fRec6[1]))) - iVec0[1]);
		fRec0[IOTA&262143] = ((float)input0[i] + (fSlow6 * ((1 - (fSlow5 * fRec5[0])) * ((fRec2[0] * fRec0[(IOTA-int((1 + int((int(iRec4[0]) & 131071)))))&262143]) + ((1.0f - fRec2[0]) * fRec0[(IOTA-int((1 + int((int(iRec3[0]) & 131071)))))&262143])))));
		output0[i] = (FAUSTFLOAT)fRec0[(IOTA-0)&262143];
		float fTemp1 = ((int((fRec8[1] != 0.0f)))?((int(((fRec9[1] > 0.0f) & (fRec9[1] < 1.0f))))?fRec8[1]:0):((int(((fRec9[1] == 0.0f) & (iSlow7 != iRec10[1]))))?0.0009765625f:((int(((fRec9[1] == 1.0f) & (iSlow7 != iRec11[1]))))?-0.0009765625f:0)));
		fRec8[0] = fTemp1;
		fRec9[0] = max(0.0f, min(1.0f, (fRec9[1] + fTemp1)));
		iRec10[0] = ((int(((fRec9[1] >= 1.0f) & (iRec11[1] != iSlow7))))?iSlow7:iRec10[1]);
		iRec11[0] = ((int(((fRec9[1] <= 0.0f) & (iRec10[1] != iSlow7))))?iSlow7:iRec11[1]);
		fRec7[IOTA&262143] = ((float)input1[i] + (fSlow8 * ((1 - (fSlow5 * (0 - fRec5[0]))) * ((fRec9[0] * fRec7[(IOTA-int((1 + int((int(iRec11[0]) & 131071)))))&262143]) + ((1.0f - fRec9[0]) * fRec7[(IOTA-int((1 + int((int(iRec10[0]) & 131071)))))&262143])))));
		output1[i] = (FAUSTFLOAT)fRec7[(IOTA-0)&262143];
		// post processing
		iRec11[1] = iRec11[0];
		iRec10[1] = iRec10[0];
		fRec9[1] = fRec9[0];
		fRec8[1] = fRec8[0];
		IOTA = IOTA+1;
		fRec6[1] = fRec6[0];
		fRec5[1] = fRec5[0];
		iRec4[1] = iRec4[0];
		iRec3[1] = iRec3[0];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
		iVec0[1] = iVec0[0];
	}
#undef fslider0
#undef fslider1
#undef fcheckbox0
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
	case PERCENT_R: 
		fslider4_ = (float*)data; // , 0.0f, 0.0f, 1e+02f, 0.1f 
		break;
	case TIME_R: 
		fslider3_ = (float*)data; // , 1.0f, 1.0f, 2e+03f, 1.0f 
		break;
	case PERCENT_L: 
		fslider2_ = (float*)data; // , 0.0f, 0.0f, 1e+02f, 0.1f 
		break;
	case LFOFREQ: 
		fslider1_ = (float*)data; // , 0.2f, 0.0f, 5.0f, 0.01f 
		break;
	case TIME_L: 
		fslider0_ = (float*)data; // , 1.0f, 1.0f, 2e+03f, 1.0f 
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

} // end namespace stereoecho
