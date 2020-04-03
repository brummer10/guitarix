// generated from file '../src/LV2/faust/gx_vibrochump.dsp' by dsp2cc:
// Code generated with Faust 2.15.11 (https://faust.grame.fr)

#include "valve.h"

namespace gx_vibrochump {

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
	int iVec0[2];
	double fConst8;
	double fConst9;
	double fConst10;
	double fConst11;
	double fConst12;
	double fConst13;
	double fConst14;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec7[2];
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
	double fRec6[4];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec8[2];
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT	*fCheckbox0_;
	double fConst31;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT	*fCheckbox1_;
	double fConst32;
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	int iRec11[2];
	int iRec10[2];
	double fConst33;
	double fRec14[2];
	double fRec13[2];
	double fRec12[2];
	double fRec9[2];
	double fVec1[2];
	double fRec5[2];
	double fRec4[3];
	double fConst34;
	double fConst35;
	double fVec2[2];
	double fRec15[2];
	double fRec3[2];
	double fConst36;
	double fConst37;
	double fRec2[2];
	double fRec1[2];
	double fRec0[2];
	FAUSTFLOAT fVslider4;
	FAUSTFLOAT	*fVslider4_;
	double fRec16[2];

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
	id = "Redeye Vibro Chump";
	name = N_("Redeye Vibro Chumo");
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) iVec0[l0] = 0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec7[l1] = 0.0;
	for (int l2 = 0; (l2 < 4); l2 = (l2 + 1)) fRec6[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fRec8[l3] = 0.0;
	for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) iRec11[l4] = 0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) iRec10[l5] = 0;
	for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) fRec14[l6] = 0.0;
	for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) fRec13[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fRec12[l8] = 0.0;
	for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) fRec9[l9] = 0.0;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) fVec1[l10] = 0.0;
	for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) fRec5[l11] = 0.0;
	for (int l12 = 0; (l12 < 3); l12 = (l12 + 1)) fRec4[l12] = 0.0;
	for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) fVec2[l13] = 0.0;
	for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) fRec15[l14] = 0.0;
	for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) fRec3[l15] = 0.0;
	for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) fRec2[l16] = 0.0;
	for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) fRec1[l17] = 0.0;
	for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) fRec0[l18] = 0.0;
	for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) fRec16[l19] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSamplingFreq)));
	fConst1 = std::tan((376.99111843077515 / fConst0));
	fConst2 = (1.0 / fConst1);
	fConst3 = (fConst2 + 1.0);
	fConst4 = (0.0 - (1.0 / (fConst3 * fConst1)));
	fConst5 = (1.0 / std::tan((17278.75959474386 / fConst0)));
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
	fConst31 = (1.0 / fConst0);
	fConst32 = (0.5 * fConst0);
	fConst33 = (6.2831853071795862 / fConst0);
	fConst34 = (1.0 / fConst3);
	fConst35 = (1.0 - fConst2);
	fConst36 = (0.0 - fConst11);
	fConst37 = ((1.0 - fConst9) / fConst10);
	fVslider0 = FAUSTFLOAT(0.5);
	fVslider1 = FAUSTFLOAT(0.5);
	fCheckbox0 = FAUSTFLOAT(0.0);
	fVslider2 = FAUSTFLOAT(5.0);
	fCheckbox1 = FAUSTFLOAT(0.0);
	fVslider3 = FAUSTFLOAT(5.0);
	fVslider4 = FAUSTFLOAT(0.5);
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
#define fCheckbox0 (*fCheckbox0_)
#define fVslider2 (*fVslider2_)
#define fCheckbox1 (*fCheckbox1_)
#define fVslider3 (*fVslider3_)
#define fVslider4 (*fVslider4_)
	double fSlow0 = (0.004073836948085289 * (std::exp(double(fVslider0)) + -1.0));
	double fSlow1 = (0.004073836948085289 * (std::exp(double(fVslider1)) + -1.0));
	int iSlow2 = int(double(fCheckbox0));
	double fSlow3 = (0.098039215686274522 * double(fVslider2));
	int iSlow4 = int(double(fCheckbox1));
	double fSlow5 = double(fVslider3);
	int iSlow6 = int((fConst32 / fSlow5));
	double fSlow7 = (1.0 / double(iSlow6));
	double fSlow8 = (fConst33 * fSlow5);
	double fSlow9 = (0.0010000000000000009 * double(fVslider4));
	for (int i = 0; (i < count); i = (i + 1)) {
		iVec0[0] = 1;
		fRec7[0] = (fSlow0 + (0.99299999999999999 * fRec7[1]));
		double fTemp0 = ((fConst0 * (fConst28 + (fRec7[0] * (fConst29 + (fConst30 * fRec7[0]))))) + 1.0800933674345301e-07);
		fRec6[0] = (double(input0[i]) - ((((fRec6[1] * ((fConst0 * (fConst14 + (fRec7[0] * (fConst16 + (fConst18 * fRec7[0]))))) + 3.2402801023035898e-07)) + (fRec6[2] * ((fConst0 * (fConst19 + (fRec7[0] * (fConst20 + (fConst21 * fRec7[0]))))) + 3.2402801023035898e-07))) + (fRec6[3] * ((fConst0 * (fConst23 + (fRec7[0] * (fConst25 + (fConst27 * fRec7[0]))))) + 1.0800933674345301e-07))) / fTemp0));
		fRec8[0] = (fSlow1 + (0.99299999999999999 * fRec8[1]));
		double fTemp1 = (7.3758739549169399e-09 * fRec8[0]);
		double fTemp2 = (0.0 - fTemp1);
		double fTemp3 = (fRec9[1] * (1.0 - (fConst31 / (fConst31 + (0.059999999999999998 * std::exp((0.0 - (2.4849066497880004 * fRec9[1]))))))));
		iRec11[0] = ((iRec11[1] > 0)?((2 * (iRec10[1] < iSlow6)) + -1):(1 - (2 * (iRec10[1] > 0))));
		iRec10[0] = (iRec11[0] + iRec10[1]);
		fRec14[0] = (fRec14[1] + (fSlow8 * (0.0 - fRec12[1])));
		fRec13[0] = ((fSlow8 * fRec14[0]) + (double((1 - iVec0[1])) + fRec13[1]));
		fRec12[0] = fRec13[0];
		fRec9[0] = (fTemp3 + (fConst31 * (std::pow(((fSlow3 * ((iSlow4?std::max<double>(0.0, (0.5 * (fRec12[0] + 1.0))):(fSlow7 * double(iRec10[0]))) + -1.0)) + 1.0), 1.8999999999999999) / (fConst31 + (0.059999999999999998 * std::exp((0.0 - (2.4849066497880004 * fTemp3))))))));
		double fTemp4 = ((fConst12 * ((((((fRec6[0] * (fTemp1 + (fConst0 * (fRec7[0] * ((6.82678111605089e-12 * fRec8[0]) + (fRec7[0] * (0.0 - (2.8683954269121398e-12 * fRec8[0])))))))) + (fRec6[1] * (fTemp2 + (fConst0 * ((fRec7[0] * fRec8[0]) * ((8.6051862807364304e-12 * fRec7[0]) + -2.0480343348152702e-11)))))) + (fRec6[2] * (fTemp2 + (fConst0 * (fRec7[0] * ((2.0480343348152702e-11 * fRec8[0]) + (fRec7[0] * (0.0 - (8.6051862807364304e-12 * fRec8[0]))))))))) + ((fRec8[0] * fRec6[3]) * ((fConst0 * (fRec7[0] * ((2.8683954269121398e-12 * fRec7[0]) + -6.82678111605089e-12))) + 7.3758739549169399e-09))) * (iSlow2?(2700.0 / (std::exp((13.815510557964274 / std::log(((8.5519675079294171 * fRec9[0]) + 2.7182818284590451)))) + 2700.0)):1.0)) / fTemp0)) + 1.0000000000000001e-15);
		fVec1[0] = fTemp4;
		fRec5[0] = ((0.93028479253239138 * (fTemp4 + fVec1[1])) - (0.86056958506478287 * fRec5[1]));
		fRec4[0] = (fRec5[0] - ((1.8405051250752198 * fRec4[1]) + (0.86129424393186271 * fRec4[2])));
		double fTemp5 = ((0.0082000000000000007 * fRec3[1]) + 1.0000000000000001e-15);
		fVec2[0] = fTemp5;
		fRec15[0] = (0.0 - (fConst34 * ((fConst35 * fRec15[1]) - (fTemp5 + fVec2[1]))));
		fRec3[0] = (double(Ftube(int(TUBE_TABLE_6V6_250k), double((((0.92544984225177063 * (fRec4[0] + fRec4[2])) + (fRec15[0] + (1.8508996845035413 * fRec4[1]))) + -1.1304620000000001)))) + -112.13878048780487);
		fRec2[0] = ((0.025000000000000001 * ((fConst11 * fRec3[0]) + (fConst36 * fRec3[1]))) - (fConst37 * fRec2[1]));
		fRec1[0] = (0.0 - (fConst6 * ((fConst7 * fRec1[1]) - (fRec2[0] + fRec2[1]))));
		fRec0[0] = ((fConst4 * fRec1[1]) - (fConst34 * ((fConst35 * fRec0[1]) - (fConst2 * fRec1[0]))));
		fRec16[0] = (fSlow9 + (0.999 * fRec16[1]));
		output0[i] = FAUSTFLOAT((0.5 * (fRec0[0] * fRec16[0])));
		iVec0[1] = iVec0[0];
		fRec7[1] = fRec7[0];
		for (int j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
			fRec6[j0] = fRec6[(j0 - 1)];
		}
		fRec8[1] = fRec8[0];
		iRec11[1] = iRec11[0];
		iRec10[1] = iRec10[0];
		fRec14[1] = fRec14[0];
		fRec13[1] = fRec13[0];
		fRec12[1] = fRec12[0];
		fRec9[1] = fRec9[0];
		fVec1[1] = fVec1[0];
		fRec5[1] = fRec5[0];
		fRec4[2] = fRec4[1];
		fRec4[1] = fRec4[0];
		fVec2[1] = fVec2[0];
		fRec15[1] = fRec15[0];
		fRec3[1] = fRec3[0];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
		fRec16[1] = fRec16[0];
	}
#undef fVslider0
#undef fVslider1
#undef fCheckbox0
#undef fVslider2
#undef fCheckbox1
#undef fVslider3
#undef fVslider4
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
		fVslider4_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	// static const value_pair fCheckbox1_values[] = {{"os.triangle"},{"sine"},{0}};
	case SINEWAVE: 
		fCheckbox1_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case INTENSITY: 
		fVslider2_ = (float*)data; // , 5.0, 0.0, 10.0, 0.10000000000000001 
		break;
	case SPEED: 
		fVslider3_ = (float*)data; // , 5.0, 0.10000000000000001, 10.0, 0.10000000000000001 
		break;
	// static const value_pair fCheckbox0_values[] = {{"Off"},{"On"},{0}};
	case VIBE: 
		fCheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
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
   SINEWAVE, 
   INTENSITY, 
   SPEED, 
   VIBE, 
} PortIndex;
*/

} // end namespace gx_vibrochump
