// generated from file '../src/LV2/faust/freeverb.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace freeverb {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec9[2];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	int IOTA0;
	double fVec0[2048];
	double fRec8[2];
	double fRec11[2];
	double fVec1[2048];
	double fRec10[2];
	double fRec13[2];
	double fVec2[2048];
	double fRec12[2];
	double fRec15[2];
	double fVec3[2048];
	double fRec14[2];
	double fRec17[2];
	double fVec4[2048];
	double fRec16[2];
	double fRec19[2];
	double fVec5[2048];
	double fRec18[2];
	double fRec21[2];
	double fVec6[2048];
	double fRec20[2];
	double fRec23[2];
	double fVec7[2048];
	double fRec22[2];
	double fVec8[1024];
	double fRec6[2];
	double fVec9[512];
	double fRec4[2];
	double fVec10[512];
	double fRec2[2];
	double fVec11[256];
	double fRec0[2];

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
	id = "freeverb";
	name = N_("Freeverb");
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec9[l0] = 0.0;
	for (int l1 = 0; l1 < 2048; l1 = l1 + 1) fVec0[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec8[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec11[l3] = 0.0;
	for (int l4 = 0; l4 < 2048; l4 = l4 + 1) fVec1[l4] = 0.0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fRec10[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fRec13[l6] = 0.0;
	for (int l7 = 0; l7 < 2048; l7 = l7 + 1) fVec2[l7] = 0.0;
	for (int l8 = 0; l8 < 2; l8 = l8 + 1) fRec12[l8] = 0.0;
	for (int l9 = 0; l9 < 2; l9 = l9 + 1) fRec15[l9] = 0.0;
	for (int l10 = 0; l10 < 2048; l10 = l10 + 1) fVec3[l10] = 0.0;
	for (int l11 = 0; l11 < 2; l11 = l11 + 1) fRec14[l11] = 0.0;
	for (int l12 = 0; l12 < 2; l12 = l12 + 1) fRec17[l12] = 0.0;
	for (int l13 = 0; l13 < 2048; l13 = l13 + 1) fVec4[l13] = 0.0;
	for (int l14 = 0; l14 < 2; l14 = l14 + 1) fRec16[l14] = 0.0;
	for (int l15 = 0; l15 < 2; l15 = l15 + 1) fRec19[l15] = 0.0;
	for (int l16 = 0; l16 < 2048; l16 = l16 + 1) fVec5[l16] = 0.0;
	for (int l17 = 0; l17 < 2; l17 = l17 + 1) fRec18[l17] = 0.0;
	for (int l18 = 0; l18 < 2; l18 = l18 + 1) fRec21[l18] = 0.0;
	for (int l19 = 0; l19 < 2048; l19 = l19 + 1) fVec6[l19] = 0.0;
	for (int l20 = 0; l20 < 2; l20 = l20 + 1) fRec20[l20] = 0.0;
	for (int l21 = 0; l21 < 2; l21 = l21 + 1) fRec23[l21] = 0.0;
	for (int l22 = 0; l22 < 2048; l22 = l22 + 1) fVec7[l22] = 0.0;
	for (int l23 = 0; l23 < 2; l23 = l23 + 1) fRec22[l23] = 0.0;
	for (int l24 = 0; l24 < 1024; l24 = l24 + 1) fVec8[l24] = 0.0;
	for (int l25 = 0; l25 < 2; l25 = l25 + 1) fRec6[l25] = 0.0;
	for (int l26 = 0; l26 < 512; l26 = l26 + 1) fVec9[l26] = 0.0;
	for (int l27 = 0; l27 < 2; l27 = l27 + 1) fRec4[l27] = 0.0;
	for (int l28 = 0; l28 < 512; l28 = l28 + 1) fVec10[l28] = 0.0;
	for (int l29 = 0; l29 < 2; l29 = l29 + 1) fRec2[l29] = 0.0;
	for (int l30 = 0; l30 < 256; l30 = l30 + 1) fVec11[l30] = 0.0;
	for (int l31 = 0; l31 < 2; l31 = l31 + 1) fRec0[l31] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	IOTA0 = 0;
	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fVslider0 (*fVslider0_)
#define fVslider1 (*fVslider1_)
#define fVslider2 (*fVslider2_)
	double fSlow0 = double(fVslider0);
	double fSlow1 = 1.0 - 0.01 * fSlow0;
	double fSlow2 = fSlow1 + fSlow0 * (0.01 * fSlow1 + 0.00015);
	double fSlow3 = double(fVslider1);
	double fSlow4 = 1.0 - fSlow3;
	double fSlow5 = 0.28 * double(fVslider2) + 0.7;
	double fSlow6 = 0.00015 * fSlow0;
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		double fTemp0 = double(input0[i0]);
		fRec9[0] = fSlow3 * fRec9[1] + fSlow4 * fRec8[1];
		double fTemp1 = fSlow6 * fTemp0;
		fVec0[IOTA0 & 2047] = fTemp1 + fSlow5 * fRec9[0];
		fRec8[0] = fVec0[(IOTA0 - 1640) & 2047];
		fRec11[0] = fSlow3 * fRec11[1] + fSlow4 * fRec10[1];
		fVec1[IOTA0 & 2047] = fTemp1 + fSlow5 * fRec11[0];
		fRec10[0] = fVec1[(IOTA0 - 1580) & 2047];
		fRec13[0] = fSlow3 * fRec13[1] + fSlow4 * fRec12[1];
		fVec2[IOTA0 & 2047] = fTemp1 + fSlow5 * fRec13[0];
		fRec12[0] = fVec2[(IOTA0 - 1514) & 2047];
		fRec15[0] = fSlow3 * fRec15[1] + fSlow4 * fRec14[1];
		fVec3[IOTA0 & 2047] = fTemp1 + fSlow5 * fRec15[0];
		fRec14[0] = fVec3[(IOTA0 - 1445) & 2047];
		fRec17[0] = fSlow3 * fRec17[1] + fSlow4 * fRec16[1];
		fVec4[IOTA0 & 2047] = fTemp1 + fSlow5 * fRec17[0];
		fRec16[0] = fVec4[(IOTA0 - 1379) & 2047];
		fRec19[0] = fSlow3 * fRec19[1] + fSlow4 * fRec18[1];
		fVec5[IOTA0 & 2047] = fTemp1 + fSlow5 * fRec19[0];
		fRec18[0] = fVec5[(IOTA0 - 1300) & 2047];
		fRec21[0] = fSlow3 * fRec21[1] + fSlow4 * fRec20[1];
		fVec6[IOTA0 & 2047] = fTemp1 + fSlow5 * fRec21[0];
		fRec20[0] = fVec6[(IOTA0 - 1211) & 2047];
		fRec23[0] = fSlow3 * fRec23[1] + fSlow4 * fRec22[1];
		fVec7[IOTA0 & 2047] = fTemp1 + fSlow5 * fRec23[0];
		fRec22[0] = fVec7[(IOTA0 - 1139) & 2047];
		double fTemp2 = fRec22[0] + fRec20[0] + fRec18[0] + fRec16[0] + fRec14[0] + fRec12[0] + fRec10[0] + fRec8[0];
		fVec8[IOTA0 & 1023] = fTemp2 + 0.5 * fRec6[1];
		fRec6[0] = fVec8[(IOTA0 - 579) & 1023];
		double fRec7 = fRec6[1] - fTemp2;
		fVec9[IOTA0 & 511] = fRec7 + 0.5 * fRec4[1];
		fRec4[0] = fVec9[(IOTA0 - 464) & 511];
		double fRec5 = fRec4[1] - fRec7;
		fVec10[IOTA0 & 511] = fRec5 + 0.5 * fRec2[1];
		fRec2[0] = fVec10[(IOTA0 - 364) & 511];
		double fRec3 = fRec2[1] - fRec5;
		fVec11[IOTA0 & 255] = fRec3 + 0.5 * fRec0[1];
		fRec0[0] = fVec11[(IOTA0 - 248) & 255];
		double fRec1 = fRec0[1] - fRec3;
		output0[i0] = FAUSTFLOAT(fRec1 + fSlow2 * fTemp0);
		fRec9[1] = fRec9[0];
		IOTA0 = IOTA0 + 1;
		fRec8[1] = fRec8[0];
		fRec11[1] = fRec11[0];
		fRec10[1] = fRec10[0];
		fRec13[1] = fRec13[0];
		fRec12[1] = fRec12[0];
		fRec15[1] = fRec15[0];
		fRec14[1] = fRec14[0];
		fRec17[1] = fRec17[0];
		fRec16[1] = fRec16[0];
		fRec19[1] = fRec19[0];
		fRec18[1] = fRec18[0];
		fRec21[1] = fRec21[0];
		fRec20[1] = fRec20[0];
		fRec23[1] = fRec23[0];
		fRec22[1] = fRec22[0];
		fRec6[1] = fRec6[0];
		fRec4[1] = fRec4[0];
		fRec2[1] = fRec2[0];
		fRec0[1] = fRec0[0];
	}
#undef fVslider0
#undef fVslider1
#undef fVslider2
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case ROOMSIZE: 
		fVslider2_ = (float*)data; // , 0.5, 0.0, 1.0, 0.025 
		break;
	case DAMP: 
		fVslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.025 
		break;
	case WET_DRY: 
		fVslider0_ = (float*)data; // , 5e+01, 0.0, 1e+02, 1.0 
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
   ROOMSIZE, 
   DAMP, 
   WET_DRY, 
} PortIndex;
*/

} // end namespace freeverb
