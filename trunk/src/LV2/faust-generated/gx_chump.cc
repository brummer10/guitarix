// generated from file '../src/LV2/faust/gx_chump.dsp' by dsp2cc:
// Code generated with Faust 2.15.11 (https://faust.grame.fr)

#include "valve.h"

namespace gx_chump {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	double fConst4;
	double fConst5;
	double fConst6;
	double fConst7;
	double fConst8;
	double fConst9;
	double fConst10;
	double fConst11;
	double fConst12;
	double fConst13;
	double fConst14;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec8[2];
	double fConst15;
	double fConst16;
	double fConst17;
	double fConst18;
	double fConst19;
	double fConst20;
	double fConst21;
	double fConst22;
	double fConst23;
	double fConst24;
	double fConst25;
	double fConst26;
	double fConst27;
	double fConst28;
	double fConst29;
	double fConst30;
	double fRec7[4];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec9[2];
	double fVec0[2];
	double fRec6[2];
	double fVec1[2];
	double fRec5[2];
	double fRec4[3];
	double fConst31;
	double fConst32;
	double fConst33;
	double fVec2[2];
	double fRec10[2];
	double fRec3[2];
	double fConst34;
	double fConst35;
	double fRec2[2];
	double fRec1[2];
	double fConst36;
	double fConst37;
	double fRec0[2];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec11[2];

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
	id = "Redeye Chump";
	name = N_("Redeye Chumo");
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec8[l0] = 0.0;
	for (int l1 = 0; (l1 < 4); l1 = (l1 + 1)) fRec7[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec9[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fVec0[l3] = 0.0;
	for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) fRec6[l4] = 0.0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fVec1[l5] = 0.0;
	for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) fRec5[l6] = 0.0;
	for (int l7 = 0; (l7 < 3); l7 = (l7 + 1)) fRec4[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fVec2[l8] = 0.0;
	for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) fRec10[l9] = 0.0;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) fRec3[l10] = 0.0;
	for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) fRec2[l11] = 0.0;
	for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) fRec1[l12] = 0.0;
	for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) fRec0[l13] = 0.0;
	for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) fRec11[l14] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSamplingFreq)));
	fConst1 = std::tan((251.32741228718345 / fConst0));
	fConst2 = (1.0 / fConst1);
	fConst3 = (fConst2 + 1.0);
	fConst4 = (0.0 - (1.0 / (fConst3 * fConst1)));
	fConst5 = (1.0 / std::tan((20517.741620594938 / fConst0)));
	fConst6 = (1.0 / (fConst5 + 1.0));
	fConst7 = (1.0 - fConst5);
	fConst8 = std::tan((97.389372261283583 / fConst0));
	fConst9 = (1.0 / fConst8);
	fConst10 = (fConst9 + 1.0);
	fConst11 = (1.0 / (fConst10 * fConst8));
	fConst12 = (0.10000000000000001 * mydsp_faustpower2_f(fConst0));
	fConst13 = (1.25065599533842e-14 * fConst0);
	fConst14 = (((-2.51329500908337e-11 - fConst13) * fConst0) + 3.3392126645374901e-09);
	fConst15 = (3.9226747496001702e-14 * fConst0);
	fConst16 = (((-1.57726547438855e-12 - fConst15) * fConst0) + 4.2149168714872797e-11);
	fConst17 = (2.6409582903850001e-14 * fConst0);
	fConst18 = (((fConst17 + 9.77412876487773e-13) * fConst0) + -2.15618481704215e-11);
	fConst19 = (((fConst13 + -2.51329500908337e-11) * fConst0) + -3.3392126645374901e-09);
	fConst20 = (((fConst15 + -1.57726547438855e-12) * fConst0) + -4.2149168714872797e-11);
	fConst21 = (((9.77412876487773e-13 - fConst17) * fConst0) + 2.15618481704215e-11);
	fConst22 = (4.16885331779473e-15 * fConst0);
	fConst23 = (((2.51329500908337e-11 - fConst22) * fConst0) + -3.3392126645374901e-09);
	fConst24 = (1.30755824986672e-14 * fConst0);
	fConst25 = (((1.57726547438855e-12 - fConst24) * fConst0) + -4.2149168714872797e-11);
	fConst26 = (8.8031943012833396e-15 * fConst0);
	fConst27 = (((fConst26 + -9.77412876487773e-13) * fConst0) + 2.15618481704215e-11);
	fConst28 = (((fConst22 + 2.51329500908337e-11) * fConst0) + 3.3392126645374901e-09);
	fConst29 = (((fConst24 + 1.57726547438855e-12) * fConst0) + 4.2149168714872797e-11);
	fConst30 = (((-9.77412876487773e-13 - fConst26) * fConst0) + -2.15618481704215e-11);
	fConst31 = (1.0 / std::tan((376.99111843077515 / fConst0)));
	fConst32 = (1.0 / (fConst31 + 1.0));
	fConst33 = (1.0 - fConst31);
	fConst34 = (0.0 - fConst11);
	fConst35 = ((1.0 - fConst9) / fConst10);
	fConst36 = (1.0 / fConst3);
	fConst37 = (1.0 - fConst2);
	fVslider0 = FAUSTFLOAT(0.5);
	fVslider1 = FAUSTFLOAT(0.5);
	fVslider2 = FAUSTFLOAT(0.5);
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fVslider0 (*fVslider0_)
#define fVslider1 (*fVslider1_)
#define fVslider2 (*fVslider2_)
	double fSlow0 = (0.004073836948085289 * (std::exp(double(fVslider0)) + -1.0));
	double fSlow1 = (0.004073836948085289 * (std::exp(double(fVslider1)) + -1.0));
	double fSlow2 = (0.0010000000000000009 * double(fVslider2));
	for (int i = 0; (i < count); i = (i + 1)) {
		fRec8[0] = (fSlow0 + (0.99299999999999999 * fRec8[1]));
		double fTemp0 = ((fConst0 * (fConst28 + (fRec8[0] * (fConst29 + (fConst30 * fRec8[0]))))) + 1.0800933674345301e-07);
		fRec7[0] = (double(input0[i]) - ((((fRec7[1] * ((fConst0 * (fConst14 + (fRec8[0] * (fConst16 + (fConst18 * fRec8[0]))))) + 3.2402801023035898e-07)) + (fRec7[2] * ((fConst0 * (fConst19 + (fRec8[0] * (fConst20 + (fConst21 * fRec8[0]))))) + 3.2402801023035898e-07))) + (fRec7[3] * ((fConst0 * (fConst23 + (fRec8[0] * (fConst25 + (fConst27 * fRec8[0]))))) + 1.0800933674345301e-07))) / fTemp0));
		fRec9[0] = (fSlow1 + (0.99299999999999999 * fRec9[1]));
		double fTemp1 = (7.3758739549169399e-09 * fRec9[0]);
		double fTemp2 = (0.0 - fTemp1);
		double fTemp3 = (((((fRec7[0] * (fTemp1 + (fConst0 * (fRec8[0] * ((6.82678111605089e-12 * fRec9[0]) + (fRec8[0] * (0.0 - (2.8683954269121398e-12 * fRec9[0])))))))) + (fRec7[1] * (fTemp2 + (fConst0 * ((fRec8[0] * fRec9[0]) * ((8.6051862807364304e-12 * fRec8[0]) + -2.0480343348152702e-11)))))) + (fRec7[2] * (fTemp2 + (fConst0 * (fRec8[0] * ((2.0480343348152702e-11 * fRec9[0]) + (fRec8[0] * (0.0 - (8.6051862807364304e-12 * fRec9[0]))))))))) + ((fRec9[0] * fRec7[3]) * ((fConst0 * (fRec8[0] * ((2.8683954269121398e-12 * fRec8[0]) + -6.82678111605089e-12))) + 7.3758739549169399e-09))) / fTemp0);
		fVec0[0] = fTemp3;
		fRec6[0] = (fConst6 * ((fConst12 * (fTemp3 + fVec0[1])) - (fConst7 * fRec6[1])));
		double fTemp4 = (fRec6[0] + 1.0000000000000001e-15);
		fVec1[0] = fTemp4;
		fRec5[0] = ((0.93028479253239138 * (fTemp4 + fVec1[1])) - (0.86056958506478287 * fRec5[1]));
		fRec4[0] = (fRec5[0] - ((1.8405051250752198 * fRec4[1]) + (0.86129424393186271 * fRec4[2])));
		double fTemp5 = ((0.0082000000000000007 * fRec3[1]) + 1.0000000000000001e-15);
		fVec2[0] = fTemp5;
		fRec10[0] = (0.0 - (fConst32 * ((fConst33 * fRec10[1]) - (fTemp5 + fVec2[1]))));
		fRec3[0] = (double(Ftube(int(TUBE_TABLE_6V6_250k), double((((0.92544984225177063 * (fRec4[0] + fRec4[2])) + (fRec10[0] + (1.8508996845035413 * fRec4[1]))) + -1.1304620000000001)))) + -112.13878048780487);
		fRec2[0] = ((0.025000000000000001 * ((fConst11 * fRec3[0]) + (fConst34 * fRec3[1]))) - (fConst35 * fRec2[1]));
		fRec1[0] = (0.0 - (fConst6 * ((fConst7 * fRec1[1]) - (fRec2[0] + fRec2[1]))));
		fRec0[0] = ((fConst4 * fRec1[1]) - (fConst36 * ((fConst37 * fRec0[1]) - (fConst2 * fRec1[0]))));
		fRec11[0] = (fSlow2 + (0.999 * fRec11[1]));
		output0[i] = FAUSTFLOAT((fRec0[0] * fRec11[0]));
		fRec8[1] = fRec8[0];
		for (int j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
			fRec7[j0] = fRec7[(j0 - 1)];
		}
		fRec9[1] = fRec9[0];
		fVec0[1] = fVec0[0];
		fRec6[1] = fRec6[0];
		fVec1[1] = fVec1[0];
		fRec5[1] = fRec5[0];
		fRec4[2] = fRec4[1];
		fRec4[1] = fRec4[0];
		fVec2[1] = fVec2[0];
		fRec10[1] = fRec10[0];
		fRec3[1] = fRec3[0];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
		fRec11[1] = fRec11[0];
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
	case GAIN: 
		fVslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case TONE: 
		fVslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case VOLUME: 
		fVslider2_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
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
   TONE, 
   VOLUME, 
} PortIndex;
*/

} // end namespace gx_chump
