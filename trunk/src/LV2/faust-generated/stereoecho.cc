// generated from file '../src/LV2/faust/stereoecho.dsp' by dsp2cc:
// Code generated with Faust 0.9.46 (http://faust.grame.fr)


namespace stereoecho {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	int 	iVec0[2];
	int 	iConst0;
	float 	fConst1;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	float 	fConst2;
	float 	fRec1[2];
	float 	fRec2[2];
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT	*fcheckbox0_;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	int 	IOTA;
	float *fRec0;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT	*fslider4_;
	float *fRec3;
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
	  fRec3(0),
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
	for (int i=0; i<262144; i++) fRec0[i] = 0;
	for (int i=0; i<262144; i++) fRec3[i] = 0;
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
	if (!fRec3) fRec3 = new float[262144];
	mem_allocated = true;
}

void Dsp::mem_free()
{
	mem_allocated = false;
	if (fRec0) { delete fRec0; fRec0 = 0; }
	if (fRec3) { delete fRec3; fRec3 = 0; }
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
	int 	iSlow0 = int((fConst1 * fslider0));
	int 	iSlow1 = int((iSlow0 - 1.49999f));
	int 	iSlow2 = int((1 + int((iSlow1 & 131071))));
	float 	fSlow3 = (2.0f + iSlow1);
	float 	fSlow4 = (0.5f * (fSlow3 - iSlow0));
	int 	iSlow5 = int((1 + int((int((1 + iSlow1)) & 131071))));
	float 	fSlow6 = (iSlow0 - (1.0f + iSlow1));
	float 	fSlow7 = ((iSlow1 + 3.0f) - iSlow0);
	int 	iSlow8 = int((1 + int((int((2 + iSlow1)) & 131071))));
	float 	fSlow9 = (0.5f * (fSlow6 * (iSlow0 - fSlow3)));
	float 	fSlow10 = (fConst2 * fslider1);
	float 	fSlow11 = sinf(fSlow10);
	float 	fSlow12 = cosf(fSlow10);
	float 	fSlow13 = (0 - fSlow11);
	float 	fSlow14 = fcheckbox0;
	float 	fSlow15 = (0.01f * fslider2);
	int 	iSlow16 = int((fConst1 * fslider3));
	int 	iSlow17 = int((iSlow16 - 1.49999f));
	int 	iSlow18 = int((1 + int((iSlow17 & 131071))));
	float 	fSlow19 = (2.0f + iSlow17);
	float 	fSlow20 = (0.5f * (fSlow19 - iSlow16));
	int 	iSlow21 = int((1 + int((int((1 + iSlow17)) & 131071))));
	float 	fSlow22 = (iSlow16 - (1.0f + iSlow17));
	float 	fSlow23 = ((iSlow17 + 3.0f) - iSlow16);
	int 	iSlow24 = int((1 + int((int((2 + iSlow17)) & 131071))));
	float 	fSlow25 = (0.5f * (fSlow22 * (iSlow16 - fSlow19)));
	float 	fSlow26 = (0.01f * fslider4);
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		fRec1[0] = ((fSlow12 * fRec1[1]) + (fSlow11 * fRec2[1]));
		fRec2[0] = ((1 + ((fSlow13 * fRec1[1]) + (fSlow12 * fRec2[1]))) - iVec0[1]);
		float fTemp0 = (fSlow14 * fRec1[0]);
		fRec0[IOTA&262143] = ((float)input0[i] + (fSlow15 * ((1 + fTemp0) * ((fSlow9 * fRec0[(IOTA-iSlow8)&262143]) + (fSlow7 * ((fSlow6 * fRec0[(IOTA-iSlow5)&262143]) + (fSlow4 * fRec0[(IOTA-iSlow2)&262143])))))));
		output0[i] = (FAUSTFLOAT)fRec0[(IOTA-0)&262143];
		fRec3[IOTA&262143] = ((float)input1[i] + (fSlow26 * ((1 - fTemp0) * ((fSlow25 * fRec3[(IOTA-iSlow24)&262143]) + (fSlow23 * ((fSlow22 * fRec3[(IOTA-iSlow21)&262143]) + (fSlow20 * fRec3[(IOTA-iSlow18)&262143])))))));
		output1[i] = (FAUSTFLOAT)fRec3[(IOTA-0)&262143];
		// post processing
		IOTA = IOTA+1;
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
