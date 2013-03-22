// generated from file '../src/LV2/faust/stereodelay.dsp' by dsp2cc:
// Code generated with Faust 0.9.46 (http://faust.grame.fr)


namespace stereodelay {

class Dsp: public PluginLV2 {
private:
	int fSamplingFreq;
	int 	IOTA;
	float *fVec0;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	int 	iVec1[2];
	int 	iConst0;
	float 	fConst1;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	float 	fConst2;
	float 	fRec0[2];
	float 	fRec1[2];
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT	*fcheckbox0_;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	float 	fRec2[2];
	float *fVec2;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT	*fslider4_;
	float 	fRec3[2];
	bool mem_allocated;
	void mem_alloc();
	void mem_free();
	void connect(uint32_t port,void* data);
	void clear_state_f();
	int activate(bool start);
	void init(unsigned int samplingFreq);
	void compute(int count, float *input0, float *input1, float *output0, float *output1);

	static void clear_state_f_static(PluginLV2*);
	static int activate_static(bool start, PluginLV2*);
	static void init_static(unsigned int samplingFreq, PluginLV2*);
	static void compute_static(int count, float *input0, float *input1, float *output0, float *output1, PluginLV2*);
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
	for (int i=0; i<262144; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	IOTA = 0;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (0.001f * iConst0);
	fConst2 = (6.283185307179586f / iConst0);
}

void Dsp::init_static(unsigned int samplingFreq, PluginLV2 *p)
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
	float 	fSlow0 = (fConst1 * fslider0);
	int 	iSlow1 = int(fSlow0);
	int 	iSlow2 = int((iSlow1 & 262143));
	int 	iSlow3 = (1 + iSlow1);
	float 	fSlow4 = (iSlow3 - fSlow0);
	int 	iSlow5 = int((int(iSlow3) & 262143));
	float 	fSlow6 = (fSlow0 - iSlow1);
	float 	fSlow7 = (fConst2 * fslider1);
	float 	fSlow8 = sinf(fSlow7);
	float 	fSlow9 = cosf(fSlow7);
	float 	fSlow10 = (0 - fSlow8);
	float 	fSlow11 = fcheckbox0;
	float 	fSlow12 = (0.0010000000000000009f * powf(10,(0.05f * fslider2)));
	float 	fSlow13 = (fConst1 * fslider3);
	int 	iSlow14 = int(fSlow13);
	int 	iSlow15 = int((iSlow14 & 262143));
	int 	iSlow16 = (1 + iSlow14);
	float 	fSlow17 = (iSlow16 - fSlow13);
	int 	iSlow18 = int((int(iSlow16) & 262143));
	float 	fSlow19 = (fSlow13 - iSlow14);
	float 	fSlow20 = (0.0010000000000000009f * powf(10,(0.05f * fslider4)));
	for (int i=0; i<count; i++) {
		float fTemp0 = (float)input0[i];
		fVec0[IOTA&262143] = fTemp0;
		iVec1[0] = 1;
		fRec0[0] = ((fSlow9 * fRec0[1]) + (fSlow8 * fRec1[1]));
		fRec1[0] = ((1 + ((fSlow10 * fRec0[1]) + (fSlow9 * fRec1[1]))) - iVec1[1]);
		float fTemp1 = (fSlow11 * fRec0[0]);
		fRec2[0] = (fSlow12 + (0.999f * fRec2[1]));
		output0[i] = (FAUSTFLOAT)(fVec0[IOTA&262143] + ((fRec2[0] * (1 + fTemp1)) * ((fSlow6 * fVec0[(IOTA-iSlow5)&262143]) + (fSlow4 * fVec0[(IOTA-iSlow2)&262143]))));
		float fTemp2 = (float)input1[i];
		fVec2[IOTA&262143] = fTemp2;
		fRec3[0] = (fSlow20 + (0.999f * fRec3[1]));
		output1[i] = (FAUSTFLOAT)(fVec2[IOTA&262143] + ((fRec3[0] * (1 - fTemp1)) * ((fSlow19 * fVec2[(IOTA-iSlow18)&262143]) + (fSlow17 * fVec2[(IOTA-iSlow15)&262143]))));
		// post processing
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
	case LFOFREQ: 
		fslider1_ = (float*)data; // , 0.2f, 0.0f, 5.0f, 0.01f 
		break;
	case L_DELAY: 
		fslider0_ = (float*)data; // , 0.0f, 0.0f, 5e+03f, 1e+01f 
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
