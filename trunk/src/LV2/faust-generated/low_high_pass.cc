// generated from file '../src/LV2/faust/low_high_pass.dsp' by dsp2cc:
// Code generated with Faust 0.9.73 (http://faust.grame.fr)


namespace low_high_pass {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	int 	iVec0[2];
	double 	fRec2[2];
	double 	fVec1[2];
	FAUSTFLOAT 	fentry0;
	FAUSTFLOAT	*fentry0_;
	double 	fConst0;
	double 	fRec1[2];
	FAUSTFLOAT 	fentry1;
	FAUSTFLOAT	*fentry1_;
	double 	fRec0[2];
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT	*fcheckbox0_;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fVec2[2];
	double 	fRec6[2];
	double 	fVec3[2];
	double 	fRec5[2];
	double 	fRec4[3];
	double 	fRec3[3];
	FAUSTFLOAT 	fcheckbox1;
	FAUSTFLOAT	*fcheckbox1_;
	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(uint32_t samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(uint32_t samplingFreq, PluginLV2*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	Dsp();
	~Dsp();
};



static const char* parm_groups[] = {
	".low_high_pass.lhp", N_("low_highpass"),
	".low_high_pass.lhc", N_("low_highcutoff"),
	0
	};

Dsp::Dsp()
	: PluginLV2() {
	version = PLUGINLV2_VERSION;
	id = "low_highpass";
	name = N_("low high pass");
	mono_audio = compute_static;
	stereo_audio = 0;
	set_samplerate = init_static;
	activate_plugin = 0;
	connect_ports = connect_static;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int i=0; i<2; i++) iVec0[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<3; i++) fRec4[i] = 0;
	for (int i=0; i<3; i++) fRec3[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = (3.141592653589793 / double(min(192000, max(1, fSamplingFreq))));
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fentry0 (*fentry0_)
#define fentry1 (*fentry1_)
#define fcheckbox0 (*fcheckbox0_)
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
#define fcheckbox1 (*fcheckbox1_)
	double 	fSlow0 = (1.0 / tan((fConst0 * double(fentry0))));
	double 	fSlow1 = (1 + fSlow0);
	double 	fSlow2 = (1.0 / fSlow1);
	double 	fSlow3 = (0 - ((1 - fSlow0) / fSlow1));
	double 	fSlow4 = (1.0 / tan((fConst0 * double(fentry1))));
	double 	fSlow5 = (0 - fSlow4);
	double 	fSlow6 = (1 + fSlow4);
	double 	fSlow7 = (1.0 / fSlow6);
	double 	fSlow8 = (0 - ((1 - fSlow4) / fSlow6));
	int 	iSlow9 = int(double(fcheckbox0));
	double 	fSlow10 = tan((fConst0 * double(fslider0)));
	double 	fSlow11 = (2 * (1 - (1.0 / faustpower<2>(fSlow10))));
	double 	fSlow12 = (1.0 / fSlow10);
	double 	fSlow13 = (1 + ((fSlow12 - 0.7653668647301795) / fSlow10));
	double 	fSlow14 = (1.0 / (1 + ((0.7653668647301795 + fSlow12) / fSlow10)));
	double 	fSlow15 = (1 + ((fSlow12 - 1.8477590650225735) / fSlow10));
	double 	fSlow16 = (1.0 / (1 + ((1.8477590650225735 + fSlow12) / fSlow10)));
	double 	fSlow17 = (fConst0 * double(fslider1));
	double 	fSlow18 = (1.0 / (1 + fSlow17));
	double 	fSlow19 = (1 - fSlow17);
	int 	iSlow20 = int(double(fcheckbox1));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		iVec0[0] = 1;
		fRec2[0] = ((1e-20 * (1 - iVec0[1])) - fRec2[1]);
		double fTemp1 = (fTemp0 + fRec2[0]);
		fVec1[0] = fTemp1;
		fRec1[0] = ((fSlow3 * fRec1[1]) + (fSlow2 * (fVec1[0] + fVec1[1])));
		fRec0[0] = ((fSlow8 * fRec0[1]) + (fSlow7 * ((fSlow4 * fRec1[0]) + (fSlow5 * fRec1[1]))));
		double fTemp2 = ((iSlow9)?fRec0[0]:fTemp0);
		double fTemp3 = (fRec2[0] + fTemp2);
		fVec2[0] = (fSlow18 * fTemp3);
		fRec6[0] = ((fSlow18 * (fTemp3 + (fSlow19 * fRec6[1]))) - fVec2[1]);
		fVec3[0] = (fSlow18 * fRec6[0]);
		fRec5[0] = ((fSlow18 * (fRec6[0] + (fSlow19 * fRec5[1]))) - fVec3[1]);
		fRec4[0] = (fRec5[0] - (fSlow16 * ((fSlow15 * fRec4[2]) + (fSlow11 * fRec4[1]))));
		fRec3[0] = ((fSlow16 * (fRec4[2] + (fRec4[0] + (2 * fRec4[1])))) - (fSlow14 * ((fSlow13 * fRec3[2]) + (fSlow11 * fRec3[1]))));
		output0[i] = (FAUSTFLOAT)((iSlow20)?(fSlow14 * (fRec3[2] + (fRec3[0] + (2 * fRec3[1])))):fTemp2);
		// post processing
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
		fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fVec3[1] = fVec3[0];
		fRec6[1] = fRec6[0];
		fVec2[1] = fVec2[0];
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fVec1[1] = fVec1[0];
		fRec2[1] = fRec2[0];
		iVec0[1] = iVec0[0];
	}
#undef fentry0
#undef fentry1
#undef fcheckbox0
#undef fslider0
#undef fslider1
#undef fcheckbox1
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case HIGH_FREQ: 
		fslider0_ = (float*)data; // , 5e+03, 1e+03, 1.2e+04, 1e+01 
		break;
	case LOW_FREQ: 
		fslider1_ = (float*)data; // , 1.3e+02, 2e+01, 1e+03, 1e+01 
		break;
	case ON_OFF: 
		fcheckbox1_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case HIGH_FREQ: 
		fentry1_ = (float*)data; // , 1.3e+02, 2e+01, 7.04e+03, 1e+01 
		break;
	case LOW_FREQ: 
		fentry0_ = (float*)data; // , 5e+03, 2e+01, 1.2e+04, 1e+01 
		break;
	case ON_OFF: 
		fcheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
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
   HIGH_FREQ, 
   LOW_FREQ, 
   ON_OFF, 
   HIGH_FREQ, 
   LOW_FREQ, 
   ON_OFF, 
} PortIndex;
*/

} // end namespace low_high_pass
