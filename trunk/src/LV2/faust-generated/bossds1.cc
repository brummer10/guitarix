// generated from file '../src/LV2/faust/bossds1.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "clipping.h"

namespace bossds1 {

class Dsp: public PluginLV2 {
private:
	gx_resample::FixedRateResampler smp;
	uint32_t sample_rate;
	uint32_t fSampleRate;
	double fConst2;
	double fConst3;
	double fConst4;
	double fConst5;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec1[2];
	double fConst7;
	double fConst9;
	double fConst11;
	double fConst13;
	double fConst14;
	double fConst15;
	double fConst16;
	double fConst17;
	double fConst18;
	double fConst19;
	double fConst20;
	double fConst22;
	double fConst24;
	double fConst25;
	double fConst28;
	double fConst29;
	double fConst31;
	double fConst32;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT	*fHslider0_;
	double fRec5[2];
	double fConst34;
	double fConst36;
	double fConst37;
	double fConst38;
	double fConst39;
	double fConst40;
	double fConst42;
	double fConst43;
	double fConst44;
	double fConst45;
	double fConst48;
	double fRec8[2];
	double fConst49;
	double fConst50;
	double fConst51;
	double fRec7[4];
	double fConst52;
	double fConst53;
	double fRec6[3];
	double fConst54;
	double fConst55;
	double fRec4[3];
	double fConst56;
	double fConst57;
	double fVec0[2];
	double fRec9[2];
	double fRec3[3];
	double fRec2[3];
	double fConst58;
	double fConst59;
	double fConst60;
	double fConst61;
	double fRec0[3];
	double fConst62;
	double fConst63;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT	*fHslider1_;
	double fRec10[2];

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
	id = "bossds1";
	name = N_("Boss DS1");
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec1[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec5[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec8[l2] = 0.0;
	for (int l3 = 0; l3 < 4; l3 = l3 + 1) fRec7[l3] = 0.0;
	for (int l4 = 0; l4 < 3; l4 = l4 + 1) fRec6[l4] = 0.0;
	for (int l5 = 0; l5 < 3; l5 = l5 + 1) fRec4[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fVec0[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec9[l7] = 0.0;
	for (int l8 = 0; l8 < 3; l8 = l8 + 1) fRec3[l8] = 0.0;
	for (int l9 = 0; l9 < 3; l9 = l9 + 1) fRec2[l9] = 0.0;
	for (int l10 = 0; l10 < 3; l10 = l10 + 1) fRec0[l10] = 0.0;
	for (int l11 = 0; l11 < 2; l11 = l11 + 1) fRec10[l11] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t RsamplingFreq)
{
	sample_rate = 96000;
	smp.setup(RsamplingFreq, sample_rate);
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = 4.33879508860142e-10 * fConst0;
	fConst2 = fConst0 * (fConst1 + -7.11639898820675e-09) + 2.44347979826776e-08;
	fConst3 = mydsp_faustpower2_f(fConst0);
	fConst4 = 4.88695959653553e-08 - 8.67759017720285e-10 * fConst3;
	fConst5 = 1.0 / (fConst0 * (fConst1 + 7.11639898820675e-09) + 2.44347979826776e-08);
	double fConst6 = 2.89644353783249e-10 * fConst0;
	fConst7 = fConst0 * (-9.44398925362792e-07 - fConst6) + -0.000537812599864916;
	double fConst8 = 2.65571689713263e-10 * fConst0;
	fConst9 = fConst0 * (fConst8 + 7.50424979344313e-07);
	double fConst10 = 3.3778968192322e-10 * fConst0;
	fConst11 = fConst0 * (fConst10 + 1.55559824875468e-06);
	double fConst12 = 2.18842400636233e-10 * fConst0;
	fConst13 = fConst0 * (-5.20602596669238e-08 - fConst12) + 0.000537812599864916;
	fConst14 = fConst0 * (fConst12 + -2.33324618325395e-07);
	fConst15 = fConst0 * (9.44398925362792e-07 - fConst6) + -0.000537812599864916;
	fConst16 = fConst0 * (fConst8 + -7.50424979344313e-07);
	fConst17 = fConst0 * (fConst10 + -1.55559824875468e-06);
	fConst18 = 6.7557936384644e-10 * fConst3;
	fConst19 = 5.31143379426527e-10 * fConst3;
	fConst20 = 5.79288707566498e-10 * fConst3 + -0.00107562519972983;
	double fConst21 = std::tan(22619.46710584651 / fConst0);
	fConst22 = 2.0 * (1.0 - 1.0 / mydsp_faustpower2_f(fConst21));
	double fConst23 = 1.0 / fConst21;
	fConst24 = (fConst23 + -1.414213562373095) / fConst21 + 1.0;
	fConst25 = 1.0 / ((fConst23 + 1.414213562373095) / fConst21 + 1.0);
	double fConst26 = std::tan(72.25663103256524 / fConst0);
	double fConst27 = mydsp_faustpower2_f(fConst26);
	fConst28 = 1.0 / fConst27;
	fConst29 = 2.0 * (1.0 - fConst28);
	double fConst30 = 1.0 / fConst26;
	fConst31 = (fConst30 + -1.414213562373095) / fConst26 + 1.0;
	fConst32 = 1.0 / ((fConst30 + 1.414213562373095) / fConst26 + 1.0);
	double fConst33 = 3.0314296262996e-10 * fConst0;
	fConst34 = fConst0 * (fConst33 + -3.38397180940322e-09);
	double fConst35 = 1.49503874539434e-11 * fConst0;
	fConst36 = fConst0 * (fConst35 + 1.66555708487018e-05);
	fConst37 = fConst0 * (fConst33 + -1.59012835323858e-05);
	fConst38 = fConst0 * (fConst35 + -7.50903344506575e-07);
	fConst39 = fConst0 * (fConst33 + 3.38397180940322e-09);
	fConst40 = fConst0 * (fConst35 + -1.66555708487018e-05);
	double fConst41 = 3.53982651634833e-10 * fConst0;
	fConst42 = fConst0 * (fConst41 + -2.38582349500046e-07) + 1.94656546234155e-05;
	fConst43 = fConst0 * (-2.38582349500046e-07 - fConst41) + 5.83969638702466e-05;
	fConst44 = fConst0 * (2.38582349500046e-07 - fConst41) + 5.83969638702466e-05;
	fConst45 = 1.0 / (fConst0 * (fConst41 + 2.38582349500046e-07) + 1.94656546234155e-05);
	double fConst46 = 2.08232145615427e-05 * fConst0;
	double fConst47 = fConst46 + 0.000485701045951343;
	fConst48 = (0.000485701045951343 - fConst46) / fConst47;
	fConst49 = 2.07110717442793e-05 * fConst0;
	fConst50 = 0.0 - fConst49;
	fConst51 = 1.0 / fConst47;
	fConst52 = 5.51041967277497e-09 * fConst3;
	fConst53 = 0.0 - fConst52;
	fConst54 = fConst0 * (fConst33 + 1.59012835323858e-05);
	fConst55 = fConst0 * (fConst35 + 7.50903344506575e-07);
	fConst56 = 0.0 - 2.0 / fConst27;
	fConst57 = 9.4e-08 * fConst0;
	fConst58 = 4.37684801272465e-10 * fConst3;
	fConst59 = fConst58 + 0.00107562519972983;
	fConst60 = fConst0 * (5.20602596669238e-08 - fConst12) + 0.000537812599864916;
	fConst61 = fConst0 * (fConst12 + 2.33324618325395e-07);
	fConst62 = 4.28019579852603e-10 * fConst3;
	fConst63 = 0.0 - 8.56039159705207e-10 * fConst3;
	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fVslider0 (*fVslider0_)
#define fHslider0 (*fHslider0_)
#define fHslider1 (*fHslider1_)
	FAUSTFLOAT buf[smp.max_out_count(count)];
	int ReCount = smp.up(count, input0, buf);
	double fSlow0 = 0.007000000000000006 * double(fVslider0);
	double fSlow1 = 0.002198000000000002 * double(fHslider0);
	double fSlow2 = 0.007000000000000006 * std::pow(1e+01, 0.05 * double(fHslider1));
	for (int i0 = 0; i0 < ReCount; i0 = i0 + 1) {
		fRec1[0] = fSlow0 + 0.993 * fRec1[1];
		double fTemp0 = fConst11 + fRec1[0] * (fConst9 + fConst7 * fRec1[0] + 0.000537812599864916) + 0.00114855258827151;
		fRec5[0] = fSlow1 + 0.993 * fRec5[1];
		double fTemp1 = fConst3 * (0.0 - 3.18093350083904e-10 * fRec5[0]);
		double fTemp2 = fConst36 + fRec5[0] * (fConst34 + fTemp1) + 0.000169198590470162;
		double fTemp3 = fConst3 * (fRec5[0] * (6.36186700167807e-10 * fRec5[0] + -6.0628592525992e-10) + -2.99007749078869e-11);
		fRec8[0] = double(buf[i0]) - fConst48 * fRec8[1];
		fRec7[0] = fConst51 * (fConst50 * fRec8[1] + fConst49 * fRec8[0]) - fConst45 * (fConst44 * fRec7[1] + fConst43 * fRec7[2] + fConst42 * fRec7[3]);
		fRec6[0] = fConst45 * (fConst53 * fRec7[0] + fConst52 * fRec7[1] + fConst52 * fRec7[2] + fConst53 * fRec7[3]) - (fRec6[1] * (fTemp3 + 0.000338397180940324) + fRec6[2] * (fConst40 + fRec5[0] * (fConst39 + fTemp1) + 0.000169198590470162)) / fTemp2;
		fRec4[0] = asymclip3((fRec6[0] * (fConst55 + fRec5[0] * (fConst54 + fTemp1) + 0.000169198590470161) + fRec6[1] * (fTemp3 + 0.000338397180940323) + fRec6[2] * (fConst38 + fRec5[0] * (fConst37 + fTemp1) + 0.000169198590470161)) / fTemp2) - fConst32 * (fConst31 * fRec4[2] + fConst29 * fRec4[1]);
		double fTemp4 = fConst32 * (fConst28 * fRec4[0] + fConst56 * fRec4[1] + fConst28 * fRec4[2]);
		double fTemp5 = opamp(fTemp4);
		double fTemp6 = 1.0 - fRec5[0];
		double fTemp7 = fConst57 * (1e+05 * fTemp6 + 4.7e+03);
		double fTemp8 = fConst57 * (1e+05 * (fTemp6 + fRec5[0] + 1.0) + 4.7e+03);
		double fTemp9 = fTemp4 - fTemp5;
		fVec0[0] = fTemp9;
		fRec9[0] = 0.0 - (fRec9[1] * (1.0 - fTemp7) - (fTemp9 * (fTemp8 + 1.0) + fVec0[1] * (1.0 - fTemp8))) / (fTemp7 + 1.0);
		fRec3[0] = fTemp4 - (fTemp5 + opamp(fRec9[0] + fTemp5 - fTemp4) + fConst25 * (fConst24 * fRec3[2] + fConst22 * fRec3[1]));
		fRec2[0] = asymhardclip2(fConst25 * (fRec3[2] + fRec3[0] + 2.0 * fRec3[1])) - (fRec2[1] * (fRec1[0] * (fConst20 * fRec1[0] + 0.00107562519972983 - fConst19) + 0.00229710517654303 - fConst18) + fRec2[2] * (fConst17 + fRec1[0] * (fConst16 + fConst15 * fRec1[0] + 0.000537812599864916) + 0.00114855258827151)) / fTemp0;
		fRec0[0] = (fRec2[0] * (fConst61 + fConst60 * fRec1[0] + 0.000182856283954071) + fRec2[1] * (fConst59 * fRec1[0] + 0.000365712567908143 - fConst58) + fRec2[2] * (fConst14 + fConst13 * fRec1[0] + 0.000182856283954071)) / fTemp0 - fConst5 * (fConst4 * fRec0[1] + fConst2 * fRec0[2]);
		fRec10[0] = fSlow2 + 0.993 * fRec10[1];
		buf[i0] = FAUSTFLOAT(fConst5 * fRec10[0] * (fConst63 * fRec0[1] + fConst62 * fRec0[0] + fConst62 * fRec0[2]));
		fRec1[1] = fRec1[0];
		fRec5[1] = fRec5[0];
		fRec8[1] = fRec8[0];
		for (int j0 = 3; j0 > 0; j0 = j0 - 1) {
			fRec7[j0] = fRec7[j0 - 1];
		}
		fRec6[2] = fRec6[1];
		fRec6[1] = fRec6[0];
		fRec4[2] = fRec4[1];
		fRec4[1] = fRec4[0];
		fVec0[1] = fVec0[0];
		fRec9[1] = fRec9[0];
		fRec3[2] = fRec3[1];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fRec0[2] = fRec0[1];
		fRec0[1] = fRec0[0];
		fRec10[1] = fRec10[0];
	}
	smp.down(buf, output0);
#undef fVslider0
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
	case LEVEL: 
		fHslider1_ = (float*)data; // , 3.0, -2e+01, 12.0, 0.1 
		break;
	case TONE: 
		fVslider0_ = (float*)data; // , 0.7, 0.0, 1.0, 0.01 
		break;
	case DRIVE: 
		fHslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
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
   TONE, 
   DRIVE, 
} PortIndex;
*/

} // end namespace bossds1
