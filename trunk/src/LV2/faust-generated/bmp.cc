// generated from file '../src/LV2/faust/bmp.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "clipping.h"

namespace bmp {

class Dsp: public PluginLV2 {
private:
	gx_resample::FixedRateResampler smp;
	uint32_t sample_rate;
	uint32_t fSampleRate;
	double fConst0;
	double fConst2;
	double fConst6;
	double fConst7;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec1[2];
	double fConst9;
	double fConst10;
	double fConst11;
	double fConst13;
	double fConst14;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec3[2];
	double fConst15;
	double fConst17;
	double fConst19;
	double fConst20;
	double fConst22;
	double fConst23;
	double fConst24;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec6[2];
	double fConst26;
	double fConst28;
	double fConst30;
	double fConst32;
	double fConst34;
	double fConst35;
	double fConst36;
	double fConst37;
	double fConst39;
	double fConst40;
	double fRec8[3];
	double fConst41;
	double fConst42;
	double fRec7[3];
	double fConst43;
	double fConst44;
	double fRec5[3];
	double fConst46;
	double fConst47;
	double fConst48;
	double fRec4[3];
	double fConst49;
	double fRec2[3];
	double fConst50;
	double fRec0[3];
	double fConst52;
	double fConst53;

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
	id = "bmp";
	name = N_("BigMuffPi");
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
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec3[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec6[l2] = 0.0;
	for (int l3 = 0; l3 < 3; l3 = l3 + 1) fRec8[l3] = 0.0;
	for (int l4 = 0; l4 < 3; l4 = l4 + 1) fRec7[l4] = 0.0;
	for (int l5 = 0; l5 < 3; l5 = l5 + 1) fRec5[l5] = 0.0;
	for (int l6 = 0; l6 < 3; l6 = l6 + 1) fRec4[l6] = 0.0;
	for (int l7 = 0; l7 < 3; l7 = l7 + 1) fRec2[l7] = 0.0;
	for (int l8 = 0; l8 < 3; l8 = l8 + 1) fRec0[l8] = 0.0;
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
	fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = std::tan(37699.11184307752 / fConst0);
	fConst2 = 2.0 * (1.0 - 1.0 / mydsp_faustpower2_f(fConst1));
	double fConst3 = fConst0 * std::sin(75398.22368615503 / fConst0);
	double fConst4 = 11800.82018976876 / fConst3;
	double fConst5 = 1.0 / fConst1;
	fConst6 = (fConst5 - fConst4) / fConst1 + 1.0;
	fConst7 = 1.0 / ((fConst5 + fConst4) / fConst1 + 1.0);
	double fConst8 = 4.33884681055068e-10 * fConst0;
	fConst9 = fConst0 * (fConst8 + -6.86809013445937e-09) + 2.65226702159437e-08;
	fConst10 = mydsp_faustpower2_f(fConst0);
	fConst11 = 5.30453404318874e-08 - 8.67769362110135e-10 * fConst10;
	double fConst12 = fConst0 * (fConst8 + 6.86809013445937e-09) + 2.65226702159437e-08;
	fConst13 = 1.0 / fConst12;
	fConst14 = 8.67101574539126e-07 * fConst0;
	fConst15 = 3.68688858465455e-10 * fConst10 + -0.00316091270975185;
	double fConst16 = 3.68688858465455e-10 * fConst0;
	fConst17 = fConst0 * (fConst16 + -3.03485551088694e-06) + 0.00486780557301784;
	double fConst18 = 7.37377716930911e-10 * fConst10;
	fConst19 = 0.00973561114603569 - fConst18;
	fConst20 = 1.0 / (fConst0 * (fConst16 + 3.03485551088694e-06) + 0.00486780557301784);
	double fConst21 = 3.920487958595e-10 * fConst0;
	fConst22 = fConst0 * (fConst21 + -2.00478727462711e-06) + 0.000489785157611555;
	fConst23 = 0.000979570315223111 - 7.84097591718999e-10 * fConst10;
	fConst24 = 1.0 / (fConst0 * (fConst21 + 2.00478727462711e-06) + 0.000489785157611555);
	double fConst25 = 1.13446519814126e-09 * fConst0;
	fConst26 = -2.89110812782566e-06 - fConst25;
	double fConst27 = 1.12312054615984e-09 * fConst0;
	fConst28 = fConst27 + 2.8621970465474e-06;
	double fConst29 = 1.2821120020393e-10 * fConst0;
	fConst30 = fConst29 + 6.26521815410076e-07;
	double fConst31 = 2.26293387153501e-12 * fConst0;
	fConst32 = fConst31 + 1.17905906929765e-05;
	double fConst33 = 2.26293387153501e-14 * fConst0;
	fConst34 = fConst33 + 1.17905906929765e-07;
	fConst35 = 2.89110812782566e-06 - fConst25;
	fConst36 = fConst27 + -2.8621970465474e-06;
	fConst37 = fConst29 + -6.26521815410076e-07;
	double fConst38 = 2.08287704934496e-05 * fConst0;
	fConst39 = 0.000219016314271736 - fConst38;
	fConst40 = 1.0 / (fConst38 + 0.000219016314271736);
	fConst41 = 3.7454979802542e-06 * fConst0;
	fConst42 = 0.0 - fConst41;
	fConst43 = fConst31 + -1.17905906929765e-05;
	fConst44 = fConst33 + -1.17905906929765e-07;
	double fConst45 = 7.66731214399861e-12 * fConst0;
	fConst46 = fConst0 * (fConst45 + 3.99490857178962e-05);
	fConst47 = 0.0 - 1.53346242879972e-11 * fConst10;
	fConst48 = fConst0 * (fConst45 + -3.99490857178962e-05);
	fConst49 = -0.00632182541950369 - fConst18;
	fConst50 = fConst10 / fConst12;
	double fConst51 = 4435.189628597355 / fConst3;
	fConst52 = (fConst5 - fConst51) / fConst1 + 1.0;
	fConst53 = (fConst5 + fConst51) / fConst1 + 1.0;
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
	FAUSTFLOAT buf[smp.max_out_count(count)];
	int ReCount = smp.up(count, input0, buf);
	double fSlow0 = 0.007000000000000006 * double(fVslider0);
	double fSlow1 = 0.007000000000000006 * double(fVslider1);
	double fSlow2 = 0.007000000000000006 * double(fVslider2);
	for (int i0 = 0; i0 < ReCount; i0 = i0 + 1) {
		double fTemp0 = fConst2 * fRec0[1];
		fRec1[0] = fSlow0 + 0.993 * fRec1[1];
		double fTemp1 = 0.0 - 1.74325899023428e-09 * fRec1[0];
		fRec3[0] = fSlow1 + 0.993 * fRec3[1];
		double fTemp2 = fConst15 * fRec3[0] + 0.00401435914138484;
		fRec6[0] = fSlow2 + 0.993 * fRec6[1];
		double fTemp3 = fConst0 * (fConst30 + fRec6[0] * (fConst28 + fConst26 * fRec6[0])) + 0.000146000960455196;
		fRec8[0] = double(buf[i0]) - fConst40 * (fConst39 * fRec8[2] + 0.000438032628543473 * fRec8[1]);
		fRec7[0] = fConst40 * (fConst42 * fRec8[2] + fConst41 * fRec8[0]) - (fRec7[1] * (fConst10 * (fRec6[0] * (2.26893039628251e-09 * fRec6[0] + -2.24624109231969e-09) + -2.5642240040786e-10) + 0.000292001920910392) + fRec7[2] * (fConst0 * (fConst37 + fRec6[0] * (fConst36 + fConst35 * fRec6[0])) + 0.000146000960455196)) / fTemp3;
		fRec5[0] = symclip((fConst0 * fRec7[0] * (fConst44 + fConst43 * fRec6[0]) + fConst10 * fRec7[1] * (0.0 - 4.52586774307001e-12 * fRec6[0] + -4.52586774307001e-14) + fConst0 * fRec7[2] * (fConst34 + fConst32 * fRec6[0])) / fTemp3) - fConst24 * (fConst23 * fRec5[1] + fConst22 * fRec5[2]);
		fRec4[0] = symclip(fConst24 * (fConst48 * fRec5[0] + fConst47 * fRec5[1] + fConst46 * fRec5[2])) - fConst20 * (fConst19 * fRec4[1] + fConst17 * fRec4[2]);
		fRec2[0] = fConst20 * (fRec4[0] * (fConst14 + fTemp2) + fRec4[1] * (fConst49 * fRec3[0] + 0.00802871828276969) + fRec4[2] * (fTemp2 - fConst14)) - fConst13 * (fConst11 * fRec2[1] + fConst9 * fRec2[2]);
		fRec0[0] = fConst50 * (fRec2[0] * fTemp1 + 3.48651798046856e-09 * fRec1[0] * fRec2[1] + fRec2[2] * fTemp1) - fConst7 * (fConst6 * fRec0[2] + fTemp0);
		buf[i0] = FAUSTFLOAT(fConst7 * (fTemp0 + fConst53 * fRec0[0] + fConst52 * fRec0[2]));
		fRec1[1] = fRec1[0];
		fRec3[1] = fRec3[0];
		fRec6[1] = fRec6[0];
		fRec8[2] = fRec8[1];
		fRec8[1] = fRec8[0];
		fRec7[2] = fRec7[1];
		fRec7[1] = fRec7[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		fRec4[2] = fRec4[1];
		fRec4[1] = fRec4[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fRec0[2] = fRec0[1];
		fRec0[1] = fRec0[0];
	}
	smp.down(buf, output0);
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
	case SUSTAIN: 
		fVslider2_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case TONE: 
		fVslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case VOLUME: 
		fVslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
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
   SUSTAIN, 
   TONE, 
   VOLUME, 
} PortIndex;
*/

} // end namespace bmp
