// generated from file '../src/LV2/faust/low_high_pass.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace low_high_pass {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT	*fCheckbox0_;
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT	*fCheckbox1_;
	int iVec0[2];
	double fRec2[2];
	double fVec1[2];
	FAUSTFLOAT fEntry0;
	FAUSTFLOAT	*fEntry0_;
	double fConst0;
	double fRec1[2];
	FAUSTFLOAT fEntry1;
	FAUSTFLOAT	*fEntry1_;
	double fRec0[2];
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fVec2[2];
	double fRec6[2];
	double fVec3[2];
	double fRec5[2];
	double fRec4[3];
	double fRec3[3];

	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(uint32_t sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(uint32_t sample_rate, PluginLV2*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	Dsp();
	~Dsp();
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) iVec0[l0] = 0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec2[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fVec1[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec1[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fRec0[l4] = 0.0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fVec2[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fRec6[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fVec3[l7] = 0.0;
	for (int l8 = 0; l8 < 2; l8 = l8 + 1) fRec5[l8] = 0.0;
	for (int l9 = 0; l9 < 3; l9 = l9 + 1) fRec4[l9] = 0.0;
	for (int l10 = 0; l10 < 3; l10 = l10 + 1) fRec3[l10] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = 3.141592653589793 / std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fCheckbox0 (*fCheckbox0_)
#define fCheckbox1 (*fCheckbox1_)
#define fEntry0 (*fEntry0_)
#define fEntry1 (*fEntry1_)
#define fVslider0 (*fVslider0_)
#define fVslider1 (*fVslider1_)
	int iSlow0 = int(double(fCheckbox0));
	int iSlow1 = int(double(fCheckbox1));
	double fSlow2 = 1.0 / std::tan(fConst0 * double(fEntry0));
	double fSlow3 = 1.0 - fSlow2;
	double fSlow4 = 1.0 / (fSlow2 + 1.0);
	double fSlow5 = std::tan(fConst0 * double(fEntry1));
	double fSlow6 = 1.0 / fSlow5;
	double fSlow7 = 1.0 - fSlow6;
	double fSlow8 = fSlow6 + 1.0;
	double fSlow9 = 1.0 / fSlow8;
	double fSlow10 = 0.0 - 1.0 / (fSlow5 * fSlow8);
	double fSlow11 = std::tan(fConst0 * double(fVslider0));
	double fSlow12 = 2.0 * (1.0 - 1.0 / mydsp_faustpower2_f(fSlow11));
	double fSlow13 = 1.0 / fSlow11;
	double fSlow14 = (fSlow13 + -0.7653668647301795) / fSlow11 + 1.0;
	double fSlow15 = 1.0 / ((fSlow13 + 0.7653668647301795) / fSlow11 + 1.0);
	double fSlow16 = (fSlow13 + -1.8477590650225735) / fSlow11 + 1.0;
	double fSlow17 = 1.0 / ((fSlow13 + 1.8477590650225735) / fSlow11 + 1.0);
	double fSlow18 = fConst0 * double(fVslider1);
	double fSlow19 = 1.0 / (fSlow18 + 1.0);
	double fSlow20 = 1.0 - fSlow18;
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		double fTemp0 = double(input0[i0]);
		iVec0[0] = 1;
		fRec2[0] = 1e-20 * double(1 - iVec0[1]) - fRec2[1];
		double fTemp1 = fTemp0 + fRec2[0];
		fVec1[0] = fTemp1;
		fRec1[0] = 0.0 - fSlow4 * (fSlow3 * fRec1[1] - (fTemp1 + fVec1[1]));
		fRec0[0] = fSlow10 * fRec1[1] - fSlow9 * (fSlow7 * fRec0[1] - fSlow6 * fRec1[0]);
		double fTemp2 = ((iSlow1) ? fRec0[0] : fTemp0);
		double fTemp3 = fRec2[0] + fTemp2;
		fVec2[0] = fSlow19 * fTemp3;
		fRec6[0] = fSlow19 * (fTemp3 + fSlow20 * fRec6[1]) - fVec2[1];
		fVec3[0] = fSlow19 * fRec6[0];
		fRec5[0] = fSlow19 * (fRec6[0] + fSlow20 * fRec5[1]) - fVec3[1];
		fRec4[0] = fRec5[0] - fSlow17 * (fSlow16 * fRec4[2] + fSlow12 * fRec4[1]);
		fRec3[0] = fSlow17 * (fRec4[2] + fRec4[0] + 2.0 * fRec4[1]) - fSlow15 * (fSlow14 * fRec3[2] + fSlow12 * fRec3[1]);
		output0[i0] = FAUSTFLOAT(((iSlow0) ? fSlow15 * (fRec3[2] + fRec3[0] + 2.0 * fRec3[1]) : fTemp2));
		iVec0[1] = iVec0[0];
		fRec2[1] = fRec2[0];
		fVec1[1] = fVec1[0];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
		fVec2[1] = fVec2[0];
		fRec6[1] = fRec6[0];
		fVec3[1] = fVec3[0];
		fRec5[1] = fRec5[0];
		fRec4[2] = fRec4[1];
		fRec4[1] = fRec4[0];
		fRec3[2] = fRec3[1];
		fRec3[1] = fRec3[0];
	}
#undef fCheckbox0
#undef fCheckbox1
#undef fEntry0
#undef fEntry1
#undef fVslider0
#undef fVslider1
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case ONOFF: 
		fCheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case ON_OFF: 
		fCheckbox1_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case HIGHFREQ: 
		fVslider0_ = (float*)data; // , 5e+03, 1e+03, 1.2e+04, 1e+01 
		break;
	case LOWFREQ: 
		fVslider1_ = (float*)data; // , 1.3e+02, 2e+01, 1e+03, 1e+01 
		break;
	case HIGH_FREQ: 
		fEntry1_ = (float*)data; // , 1.3e+02, 2e+01, 7.04e+03, 1e+01 
		break;
	case LOW_FREQ: 
		fEntry0_ = (float*)data; // , 5e+03, 2e+01, 1.2e+04, 1e+01 
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
   HIGHFREQ, 
   LOWFREQ, 
   ONOFF, 
   HIGH_FREQ, 
   LOW_FREQ, 
   ON_OFF, 
} PortIndex;
*/

} // end namespace low_high_pass
