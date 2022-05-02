// generated from file '../src/LV2/faust/bossds1.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "clipping.h"

namespace bossds1 {

class Dsp: public PluginLV2 {
private:
	gx_resample::FixedRateResampler smp;
	uint32_t sample_rate;
	uint32_t fSampleRate;
	double fConst0;
	double fConst2;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT	*fHslider0_;
	double fRec0[2];
	double fConst3;
	double fConst4;
	double fConst7;
	double fConst10;
	double fConst12;
	double fConst14;
	double fConst15;
	double fConst16;
	double fConst19;
	double fConst20;
	double fConst21;
	double fConst22;
	double fRec7[2];
	double fConst23;
	double fConst24;
	double fConst25;
	double fRec6[4];
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT	*fHslider1_;
	double fRec8[2];
	double fConst27;
	double fConst29;
	double fConst30;
	double fConst31;
	double fRec5[3];
	double fConst32;
	double fConst33;
	double fConst34;
	double fConst35;
	double fConst36;
	double fConst37;
	double fRec4[3];
	double fConst38;
	double fConst39;
	double fVec0[2];
	double fRec9[2];
	double fConst40;
	double fConst41;
	double fRec3[3];
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec10[2];
	double fConst42;
	double fConst43;
	double fConst44;
	double fConst46;
	double fConst48;
	double fConst50;
	double fConst51;
	double fConst52;
	double fConst53;
	double fRec2[3];
	double fConst55;
	double fConst56;
	double fConst57;
	double fConst58;
	double fConst59;
	double fConst60;
	double fConst61;
	double fConst62;
	double fRec1[3];
	double fConst63;

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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec0[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec7[l1] = 0.0;
	for (int l2 = 0; l2 < 4; l2 = l2 + 1) fRec6[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec8[l3] = 0.0;
	for (int l4 = 0; l4 < 3; l4 = l4 + 1) fRec5[l4] = 0.0;
	for (int l5 = 0; l5 < 3; l5 = l5 + 1) fRec4[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fVec0[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec9[l7] = 0.0;
	for (int l8 = 0; l8 < 3; l8 = l8 + 1) fRec3[l8] = 0.0;
	for (int l9 = 0; l9 < 2; l9 = l9 + 1) fRec10[l9] = 0.0;
	for (int l10 = 0; l10 < 3; l10 = l10 + 1) fRec2[l10] = 0.0;
	for (int l11 = 0; l11 < 3; l11 = l11 + 1) fRec1[l11] = 0.0;
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
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = 4.3387950886014201e-10 * fConst0;
	fConst2 = 1.0 / (fConst0 * (fConst1 + 7.11639898820675e-09) + 2.4434797982677599e-08);
	fConst3 = mydsp_faustpower2_f(fConst0);
	fConst4 = 0.0 - 8.5603915970520705e-10 * fConst3;
	double fConst5 = std::tan(22619.46710584651 / fConst0);
	double fConst6 = 1.0 / fConst5;
	fConst7 = 1.0 / ((fConst6 + 1.4142135623730949) / fConst5 + 1.0);
	double fConst8 = std::tan(72.256631032565238 / fConst0);
	double fConst9 = 1.0 / fConst8;
	fConst10 = 1.0 / ((fConst9 + 1.4142135623730949) / fConst8 + 1.0);
	double fConst11 = mydsp_faustpower2_f(fConst8);
	fConst12 = 1.0 / fConst11;
	double fConst13 = 3.5398265163483301e-10 * fConst0;
	fConst14 = 1.0 / (fConst0 * (fConst13 + 2.3858234950004601e-07) + 1.94656546234155e-05);
	fConst15 = 5.5104196727749697e-09 * fConst3;
	fConst16 = 0.0 - fConst15;
	double fConst17 = 2.0823214561542701e-05 * fConst0;
	double fConst18 = fConst17 + 0.00048570104595134299;
	fConst19 = 1.0 / fConst18;
	fConst20 = 2.0711071744279299e-05 * fConst0;
	fConst21 = 0.0 - fConst20;
	fConst22 = (0.00048570104595134299 - fConst17) / fConst18;
	fConst23 = fConst0 * (2.3858234950004601e-07 - fConst13) + 5.8396963870246599e-05;
	fConst24 = fConst0 * (-2.3858234950004601e-07 - fConst13) + 5.8396963870246599e-05;
	fConst25 = fConst0 * (fConst13 + -2.3858234950004601e-07) + 1.94656546234155e-05;
	double fConst26 = 1.4950387453943399e-11 * fConst0;
	fConst27 = fConst26 + -1.66555708487018e-05;
	double fConst28 = 3.0314296262996001e-10 * fConst0;
	fConst29 = fConst28 + 3.38397180940322e-09;
	fConst30 = fConst26 + 1.66555708487018e-05;
	fConst31 = fConst28 + -3.38397180940322e-09;
	fConst32 = fConst26 + 7.5090334450657498e-07;
	fConst33 = fConst28 + 1.5901283532385801e-05;
	fConst34 = fConst26 + -7.5090334450657498e-07;
	fConst35 = fConst28 + -1.5901283532385801e-05;
	fConst36 = (fConst9 + -1.4142135623730949) / fConst8 + 1.0;
	fConst37 = 2.0 * (1.0 - fConst12);
	fConst38 = 0.0 - 2.0 / fConst11;
	fConst39 = 9.3999999999999995e-08 * fConst0;
	fConst40 = (fConst6 + -1.4142135623730949) / fConst5 + 1.0;
	fConst41 = 2.0 * (1.0 - 1.0 / mydsp_faustpower2_f(fConst5));
	fConst42 = 5.7928870756649804e-10 * fConst3 + -0.0010756251997298301;
	fConst43 = 5.31143379426527e-10 * fConst3;
	fConst44 = 6.7557936384644e-10 * fConst3;
	double fConst45 = 3.3778968192322e-10 * fConst0;
	fConst46 = fConst0 * (fConst45 + -1.5555982487546801e-06);
	double fConst47 = 2.6557168971326298e-10 * fConst0;
	fConst48 = fConst0 * (fConst47 + -7.5042497934431299e-07);
	double fConst49 = 2.8964435378324902e-10 * fConst0;
	fConst50 = fConst0 * (9.4439892536279197e-07 - fConst49) + -0.00053781259986491602;
	fConst51 = fConst0 * (fConst45 + 1.5555982487546801e-06);
	fConst52 = fConst0 * (fConst47 + 7.5042497934431299e-07);
	fConst53 = fConst0 * (-9.4439892536279197e-07 - fConst49) + -0.00053781259986491602;
	double fConst54 = 2.1884240063623301e-10 * fConst0;
	fConst55 = fConst0 * (fConst54 + 2.3332461832539501e-07);
	fConst56 = fConst0 * (5.2060259666923803e-08 - fConst54) + 0.00053781259986491602;
	fConst57 = 4.3768480127246498e-10 * fConst3;
	fConst58 = fConst57 + 0.0010756251997298301;
	fConst59 = fConst0 * (fConst54 + -2.3332461832539501e-07);
	fConst60 = fConst0 * (-5.2060259666923803e-08 - fConst54) + 0.00053781259986491602;
	fConst61 = 4.8869595965355297e-08 - 8.6775901772028505e-10 * fConst3;
	fConst62 = fConst0 * (fConst1 + -7.11639898820675e-09) + 2.4434797982677599e-08;
	fConst63 = 4.2801957985260301e-10 * fConst3;
	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fHslider0 (*fHslider0_)
#define fHslider1 (*fHslider1_)
#define fVslider0 (*fVslider0_)
	FAUSTFLOAT buf[smp.max_out_count(count)];
	int ReCount = smp.up(count, input0, buf);
	double fSlow0 = 0.0070000000000000062 * std::pow(10.0, 0.050000000000000003 * double(fHslider0));
	double fSlow1 = 0.002198000000000002 * double(fHslider1);
	double fSlow2 = 0.0070000000000000062 * double(fVslider0);
	for (int i0 = 0; i0 < ReCount; i0 = i0 + 1) {
		fRec0[0] = fSlow0 + 0.99299999999999999 * fRec0[1];
		fRec7[0] = double(buf[i0]) - fConst22 * fRec7[1];
		fRec6[0] = fConst19 * (fConst21 * fRec7[1] + fConst20 * fRec7[0]) - fConst14 * (fConst23 * fRec6[1] + fConst24 * fRec6[2] + fConst25 * fRec6[3]);
		fRec8[0] = fSlow1 + 0.99299999999999999 * fRec8[1];
		double fTemp0 = fConst3 * (fRec8[0] * (6.3618670016780696e-10 * fRec8[0] + -6.0628592525992003e-10) + -2.9900774907886902e-11);
		double fTemp1 = fConst0 * (0.0 - 3.18093350083904e-10 * fRec8[0]);
		double fTemp2 = fConst0 * (fConst30 + fRec8[0] * (fConst31 + fTemp1)) + 0.00016919859047016201;
		fRec5[0] = fConst14 * (fConst16 * fRec6[0] + fConst15 * fRec6[1] + fConst15 * fRec6[2] + fConst16 * fRec6[3]) - (fRec5[1] * (fTemp0 + 0.00033839718094032402) + fRec5[2] * (fConst0 * (fConst27 + fRec8[0] * (fConst29 + fTemp1)) + 0.00016919859047016201)) / fTemp2;
		fRec4[0] = double(asymclip3(double((fRec5[0] * (fConst0 * (fConst32 + fRec8[0] * (fConst33 + fTemp1)) + 0.00016919859047016101) + fRec5[1] * (fTemp0 + 0.00033839718094032299) + fRec5[2] * (fConst0 * (fConst34 + fRec8[0] * (fConst35 + fTemp1)) + 0.00016919859047016101)) / fTemp2))) - fConst10 * (fConst36 * fRec4[2] + fConst37 * fRec4[1]);
		double fTemp3 = fConst10 * (fConst12 * fRec4[0] + fConst38 * fRec4[1] + fConst12 * fRec4[2]);
		double fTemp4 = double(opamp(double(fTemp3)));
		double fTemp5 = 1.0 - fRec8[0];
		double fTemp6 = fConst39 * (100000.0 * fTemp5 + 4700.0);
		double fTemp7 = fTemp3 - fTemp4;
		fVec0[0] = fTemp7;
		double fTemp8 = fConst39 * (100000.0 * (fTemp5 + fRec8[0] + 1.0) + 4700.0);
		fRec9[0] = 0.0 - (fRec9[1] * (1.0 - fTemp6) - (fTemp7 * (fTemp8 + 1.0) + fVec0[1] * (1.0 - fTemp8))) / (fTemp6 + 1.0);
		fRec3[0] = fTemp3 - (fTemp4 + double(opamp(double((fRec9[0] + fTemp4) - fTemp3))) + fConst7 * (fConst40 * fRec3[2] + fConst41 * fRec3[1]));
		fRec10[0] = fSlow2 + 0.99299999999999999 * fRec10[1];
		double fTemp9 = fConst51 + fRec10[0] * (fConst52 + fConst53 * fRec10[0] + 0.00053781259986491602) + 0.00114855258827151;
		fRec2[0] = double(asymhardclip2(double(fConst7 * (fRec3[2] + fRec3[0] + 2.0 * fRec3[1])))) - (fRec2[1] * ((fRec10[0] * ((fConst42 * fRec10[0] + 0.0010756251997298301) - fConst43) + 0.00229710517654303) - fConst44) + fRec2[2] * (fConst46 + fRec10[0] * (fConst48 + fConst50 * fRec10[0] + 0.00053781259986491602) + 0.00114855258827151)) / fTemp9;
		fRec1[0] = (fRec2[0] * (fConst55 + fConst56 * fRec10[0] + 0.00018285628395407099) + fRec2[1] * ((fConst58 * fRec10[0] + 0.00036571256790814301) - fConst57) + fRec2[2] * (fConst59 + fConst60 * fRec10[0] + 0.00018285628395407099)) / fTemp9 - fConst2 * (fConst61 * fRec1[1] + fConst62 * fRec1[2]);
		buf[i0] = FAUSTFLOAT(fConst2 * fRec0[0] * (fConst4 * fRec1[1] + fConst63 * fRec1[0] + fConst63 * fRec1[2]));
		fRec0[1] = fRec0[0];
		fRec7[1] = fRec7[0];
		for (int j0 = 3; j0 > 0; j0 = j0 - 1) {
			fRec6[j0] = fRec6[j0 - 1];
		}
		fRec8[1] = fRec8[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		fRec4[2] = fRec4[1];
		fRec4[1] = fRec4[0];
		fVec0[1] = fVec0[0];
		fRec9[1] = fRec9[0];
		fRec3[2] = fRec3[1];
		fRec3[1] = fRec3[0];
		fRec10[1] = fRec10[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fRec1[2] = fRec1[1];
		fRec1[1] = fRec1[0];
	}
	smp.down(buf, output0);
#undef fHslider0
#undef fHslider1
#undef fVslider0
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
		fHslider0_ = (float*)data; // , 3.0, -20.0, 12.0, 0.10000000000000001 
		break;
	case TONE: 
		fVslider0_ = (float*)data; // , 0.69999999999999996, 0.0, 1.0, 0.01 
		break;
	case DRIVE: 
		fHslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
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
