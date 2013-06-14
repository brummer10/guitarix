// generated from file '../src/LV2/faust/chorus.dsp' by dsp2cc:
// Code generated with Faust 0.9.58 (http://faust.grame.fr)


namespace chorus {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	class SIG0 {
	  private:
		int 	fSamplingFreq;
		int 	iRec1[2];
	  public:
		int getNumInputs() 	{ return 0; }
		int getNumOutputs() 	{ return 1; }
		void init(int samplingFreq) {
			fSamplingFreq = samplingFreq;
			for (int i=0; i<2; i++) iRec1[i] = 0;
		}
		void fill (int count, float output[]) {
			for (int i=0; i<count; i++) {
				iRec1[0] = (1 + iRec1[1]);
				output[i] = sinf((9.587379924285257e-05f * (iRec1[0] - 1)));
				// post processing
				iRec1[1] = iRec1[0];
			}
		}
	};
			int 	IOTA;
	float *fVec0;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	int 	iConst0;
	float 	fConst1;
	float 	fRec0[2];
	static float 	ftbl0[65536];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	float 	fConst2;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	float *fVec1;
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


float Dsp::ftbl0[65536];

Dsp::Dsp()
	: PluginLV2(),
	  fVec0(0),
	  fVec1(0),
	  mem_allocated(false) {
	version = PLUGINLV2_VERSION;
	id = "chorus";
	name = N_("Chorus");
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
	for (int i=0; i<65536; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<65536; i++) fVec1[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	SIG0 sig0;
	sig0.init(samplingFreq);
	sig0.fill(65536,ftbl0);
	fSamplingFreq = samplingFreq;
	IOTA = 0;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (1.0f / float(iConst0));
	fConst2 = (0.5f * iConst0);
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void Dsp::mem_alloc()
{
	if (!fVec0) fVec0 = new float[65536];
	if (!fVec1) fVec1 = new float[65536];
	mem_allocated = true;
}

void Dsp::mem_free()
{
	mem_allocated = false;
	if (fVec0) { delete fVec0; fVec0 = 0; }
	if (fVec1) { delete fVec1; fVec1 = 0; }
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

void always_inline Dsp::compute(int count, float *input0, float *input1, float *output0, float *output1)
{
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
#define fslider2 (*fslider2_)
#define fslider3 (*fslider3_)
	float 	fSlow0 = (fConst1 * fslider0);
	float 	fSlow1 = fslider1;
	float 	fSlow2 = (fConst2 * fslider2);
	float 	fSlow3 = fslider3;
	for (int i=0; i<count; i++) {
		float fTemp0 = (float)input0[i];
		fVec0[IOTA&65535] = fTemp0;
		float fTemp1 = (fSlow0 + fRec0[1]);
		fRec0[0] = (fTemp1 - floorf(fTemp1));
		float fTemp2 = (65536 * (fRec0[0] - floorf(fRec0[0])));
		float fTemp3 = floorf(fTemp2);
		int iTemp4 = int(fTemp3);
		float fTemp5 = (fSlow2 * (1 + (fSlow1 * ((ftbl0[((1 + iTemp4) & 65535)] * (fTemp2 - fTemp3)) + (ftbl0[(iTemp4 & 65535)] * ((1 + fTemp3) - fTemp2))))));
		int iTemp6 = int(fTemp5);
		int iTemp7 = (1 + iTemp6);
		output0[i] = (FAUSTFLOAT)(fVec0[IOTA&65535] + (fSlow3 * (((fTemp5 - iTemp6) * fVec0[(IOTA-int((int(iTemp7) & 65535)))&65535]) + ((iTemp7 - fTemp5) * fVec0[(IOTA-int((iTemp6 & 65535)))&65535]))));
		float fTemp8 = (float)input1[i];
		fVec1[IOTA&65535] = fTemp8;
		float fTemp9 = (0.25f + fRec0[0]);
		float fTemp10 = (65536 * (fTemp9 - floorf(fTemp9)));
		float fTemp11 = floorf(fTemp10);
		int iTemp12 = int(fTemp11);
		float fTemp13 = (fSlow2 * (1 + (fSlow1 * ((ftbl0[((1 + iTemp12) & 65535)] * (fTemp10 - fTemp11)) + (ftbl0[(iTemp12 & 65535)] * ((1 + fTemp11) - fTemp10))))));
		int iTemp14 = int(fTemp13);
		int iTemp15 = (1 + iTemp14);
		output1[i] = (FAUSTFLOAT)(fVec1[IOTA&65535] + (fSlow3 * (((fTemp13 - iTemp14) * fVec1[(IOTA-int((int(iTemp15) & 65535)))&65535]) + ((iTemp15 - fTemp13) * fVec1[(IOTA-int((iTemp14 & 65535)))&65535]))));
		// post processing
		fRec0[1] = fRec0[0];
		IOTA = IOTA+1;
	}
#undef fslider0
#undef fslider1
#undef fslider2
#undef fslider3
}

void __rt_func Dsp::compute_static(int count, float *input0, float *input1, float *output0, float *output1, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case LEVEL: 
		fslider3_ = (float*)data; // , 0.5f, 0.0f, 1.0f, 0.01f 
		break;
	case DELAY: 
		fslider2_ = (float*)data; // , 0.02f, 0.0f, 0.2f, 0.01f 
		break;
	case DEPTH: 
		fslider1_ = (float*)data; // , 0.02f, 0.0f, 1.0f, 0.01f 
		break;
	case FREQ: 
		fslider0_ = (float*)data; // , 3.0f, 0.0f, 1e+01f, 0.01f 
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
   LEVEL, 
   DELAY, 
   DEPTH, 
   FREQ, 
} PortIndex;
*/

} // end namespace chorus
