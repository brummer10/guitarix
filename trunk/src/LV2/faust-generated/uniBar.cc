// generated from file '../src/LV2/faust/uniBar.dsp' by dsp2cc:
// Code generated with Faust 2.15.11 (https://faust.grame.fr)


namespace uniBar {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT	*fCheckbox0_;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT	*fHslider0_;
	double fConst4;
	double fRec6[2];
	double fConst5;
	double fRec8[2];
	double fConst6;
	double fConst7;
	double fConst8;
	double fRec7[2];
	double fConst9;
	int IOTA;
	double fVec0[8192];
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT	*fHslider1_;
	double fConst10;
	double fConst11;
	double fRec5[3];
	double fRec4[2];
	double fRec0[2];
	double fVec1[4096];
	double fConst12;
	double fConst13;
	double fRec10[3];
	double fRec9[2];
	double fRec1[2];
	double fVec2[2048];
	double fConst14;
	double fConst15;
	double fRec12[3];
	double fRec11[2];
	double fRec2[2];
	double fVec3[2048];
	double fConst16;
	double fConst17;
	double fRec14[3];
	double fRec13[2];
	double fRec3[2];

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



Dsp::Dsp()
	: PluginLV2() {
	version = PLUGINLV2_VERSION;
	id = "uniBar";
	name = N_("Nonlinear Banded Waveguide Models");
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec6[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec8[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec7[l2] = 0.0;
	for (int l3 = 0; (l3 < 8192); l3 = (l3 + 1)) fVec0[l3] = 0.0;
	for (int l4 = 0; (l4 < 3); l4 = (l4 + 1)) fRec5[l4] = 0.0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fRec4[l5] = 0.0;
	for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) fRec0[l6] = 0.0;
	for (int l7 = 0; (l7 < 4096); l7 = (l7 + 1)) fVec1[l7] = 0.0;
	for (int l8 = 0; (l8 < 3); l8 = (l8 + 1)) fRec10[l8] = 0.0;
	for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) fRec9[l9] = 0.0;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) fRec1[l10] = 0.0;
	for (int l11 = 0; (l11 < 2048); l11 = (l11 + 1)) fVec2[l11] = 0.0;
	for (int l12 = 0; (l12 < 3); l12 = (l12 + 1)) fRec12[l12] = 0.0;
	for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) fRec11[l13] = 0.0;
	for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) fRec2[l14] = 0.0;
	for (int l15 = 0; (l15 < 2048); l15 = (l15 + 1)) fVec3[l15] = 0.0;
	for (int l16 = 0; (l16 < 3); l16 = (l16 + 1)) fRec14[l16] = 0.0;
	for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) fRec13[l17] = 0.0;
	for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) fRec3[l18] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSamplingFreq)));
	fConst1 = (1.0 - (100.53096491487338 / fConst0));
	fConst2 = mydsp_faustpower2_f(fConst1);
	fConst3 = (0.5 * (1.0 - fConst2));
	fConst4 = std::max<double>(0.001, (0.01 * fConst0));
	fConst5 = (0.025000000000000001 * fConst0);
	fConst6 = (0.02 * fConst0);
	fConst7 = (199.99999999999997 / fConst0);
	fConst8 = (50.0 / fConst0);
	fConst9 = (1.0 / fConst4);
	fConst10 = (0.0 - (2.0 * fConst1));
	fConst11 = (6.2831853071795862 / fConst0);
	fConst12 = (0.36284470246734402 * fConst0);
	fConst13 = (17.316458706586939 / fConst0);
	fConst14 = (0.1850481125092524 * fConst0);
	fConst15 = (33.954333399998482 / fConst0);
	fConst16 = (0.11194447554013209 * fConst0);
	fConst17 = (56.127694349035245 / fConst0);
	fCheckbox0 = FAUSTFLOAT(0.0);
	fHslider0 = FAUSTFLOAT(0.80000000000000004);
	fHslider1 = FAUSTFLOAT(440.0);
			IOTA = 0;
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fCheckbox0 (*fCheckbox0_)
#define fHslider0 (*fHslider0_)
#define fHslider1 (*fHslider1_)
	double fSlow0 = double(fCheckbox0);
	double fSlow1 = double(fHslider0);
	double fSlow2 = (2.5 * (fSlow0 * fSlow1));
	double fSlow3 = (fSlow1 + 0.029999999999999999);
	int iSlow4 = (fSlow0 > 0.0);
	int iSlow5 = (iSlow4 > 0);
	double fSlow6 = double(iSlow4);
	int iSlow7 = ((fSlow0 == 0.0) > 0);
	double fSlow8 = (90.0 * fSlow0);
	double fSlow9 = (fConst7 * (fSlow8 + -1.0));
	double fSlow10 = double(fHslider1);
	int iSlow11 = int(std::min<double>(4096.0, std::max<double>(0.0, (fConst0 / fSlow10))));
	double fSlow12 = (fConst10 * std::cos((fConst11 * fSlow10)));
	int iSlow13 = int(std::min<double>(4096.0, std::max<double>(0.0, (fConst12 / fSlow10))));
	double fSlow14 = (fConst10 * std::cos((fConst13 * fSlow10)));
	int iSlow15 = int(std::min<double>(4096.0, std::max<double>(0.0, (fConst14 / fSlow10))));
	double fSlow16 = (fConst10 * std::cos((fConst15 * fSlow10)));
	int iSlow17 = int(std::min<double>(4096.0, std::max<double>(0.0, (fConst16 / fSlow10))));
	double fSlow18 = (fConst10 * std::cos((fConst17 * fSlow10)));
	for (int i = 0; (i < count); i = (i + 1)) {
		fRec6[0] = (iSlow5?0.0:std::min<double>(fConst4, (fRec6[1] + 1.0)));
		fRec8[0] = (iSlow7?0.0:std::min<double>(fConst5, (fRec8[1] + 1.0)));
		int iTemp0 = (fRec8[0] < fConst6);
		fRec7[0] = (iSlow4?(fSlow6 * (iTemp0?((fRec8[0] < 0.0)?0.0:(iTemp0?(fConst8 * fRec8[0]):1.0)):((fRec8[0] < fConst5)?((fSlow9 * (fRec8[0] - fConst6)) + 1.0):fSlow8))):fRec7[1]);
		double fTemp1 = ((fSlow3 * ((fRec6[0] < 0.0)?fRec7[0]:((fRec6[0] < fConst4)?(fRec7[0] + (fConst9 * (0.0 - (fRec6[0] * fRec7[0])))):0.0))) + (-0.80000000000000004 - (0.99999999999999989 * ((fRec0[1] + fRec2[1]) + (fRec1[1] + fRec3[1])))));
		double fTemp2 = mydsp_faustpower4_f((std::fabs(fTemp1) + 0.75));
		double fTemp3 = (1.0 / fTemp2);
		double fTemp4 = (0.25 * (fTemp1 * (double((fTemp3 > 1.0)) + (double((fTemp3 <= 1.0)) / fTemp2))));
		fVec0[(IOTA & 8191)] = (fSlow2 + (fRec4[1] + fTemp4));
		fRec5[0] = ((0.90000000000000002 * fVec0[((IOTA - iSlow11) & 8191)]) - ((fSlow12 * fRec5[1]) + (fConst2 * fRec5[2])));
		fRec4[0] = (fConst3 * (fRec5[0] - fRec5[2]));
		fRec0[0] = fRec4[0];
		fVec1[(IOTA & 4095)] = (fSlow2 + (fTemp4 + fRec9[1]));
		fRec10[0] = ((0.81000000000000005 * fVec1[((IOTA - iSlow13) & 4095)]) - ((fSlow14 * fRec10[1]) + (fConst2 * fRec10[2])));
		fRec9[0] = (fConst3 * (fRec10[0] - fRec10[2]));
		fRec1[0] = fRec9[0];
		fVec2[(IOTA & 2047)] = (fSlow2 + (fTemp4 + fRec11[1]));
		fRec12[0] = ((0.72900000000000009 * fVec2[((IOTA - iSlow15) & 2047)]) - ((fSlow16 * fRec12[1]) + (fConst2 * fRec12[2])));
		fRec11[0] = (fConst3 * (fRec12[0] - fRec12[2]));
		fRec2[0] = fRec11[0];
		fVec3[(IOTA & 2047)] = (fSlow2 + (fTemp4 + fRec13[1]));
		fRec14[0] = ((0.65610000000000002 * fVec3[((IOTA - iSlow17) & 2047)]) - ((fSlow18 * fRec14[1]) + (fConst2 * fRec14[2])));
		fRec13[0] = (fConst3 * (fRec14[0] - fRec14[2]));
		fRec3[0] = fRec13[0];
		output0[i] = FAUSTFLOAT(((((fRec0[0] + fRec1[0]) + fRec2[0]) + fRec3[0]) + double(input0[i])));
		fRec6[1] = fRec6[0];
		fRec8[1] = fRec8[0];
		fRec7[1] = fRec7[0];
		IOTA = (IOTA + 1);
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		fRec4[1] = fRec4[0];
		fRec0[1] = fRec0[0];
		fRec10[2] = fRec10[1];
		fRec10[1] = fRec10[0];
		fRec9[1] = fRec9[0];
		fRec1[1] = fRec1[0];
		fRec12[2] = fRec12[1];
		fRec12[1] = fRec12[0];
		fRec11[1] = fRec11[0];
		fRec2[1] = fRec2[0];
		fRec14[2] = fRec14[1];
		fRec14[1] = fRec14[0];
		fRec13[1] = fRec13[0];
		fRec3[1] = fRec3[0];
	}
#undef fCheckbox0
#undef fHslider0
#undef fHslider1
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case GAIN: 
		fHslider0_ = (float*)data; // , 0.80000000000000004, 0.0, 10.0, 0.01 
		break;
	case GATE: 
		fCheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case SYNTHFREQ: 
		fHslider1_ = (float*)data; // , 440.0, 20.0, 20000.0, 1.0 
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
   GAIN, 
   GATE, 
   SYNTHFREQ, 
} PortIndex;
*/

} // end namespace uniBar
