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
	double fConst15;
	double fConst16;
	double fConst17;
	double fConst18;
	double fConst19;
	double fConst20;
	double fConst21;
	double fRec5[3];
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec6[2];
	double fConst22;
	double fConst23;
	double fConst24;
	double fConst25;
	double fConst26;
	double fConst27;
	double fConst28;
	double fConst29;
	double fConst30;
	double fRec4[3];
	double fConst31;
	double fConst32;
	double fConst33;
	double fConst34;
	double fConst35;
	double fConst36;
	double fConst37;
	double fConst38;
	double fRec3[3];
	double fConst39;
	double fConst40;
	double fConst41;
	double fConst42;
	double fConst43;
	double fRec2[3];
	double fConst44;
	double fConst45;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec7[2];
	double fConst46;
	double fConst47;
	double fConst48;
	double fConst49;
	double fRec1[3];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec8[2];
	double fConst50;
	double fRec0[3];
	double fConst51;
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
	for (int l0 = 0; (l0 < 3); l0 = (l0 + 1)) fRec5[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec6[l1] = 0.0;
	for (int l2 = 0; (l2 < 3); l2 = (l2 + 1)) fRec4[l2] = 0.0;
	for (int l3 = 0; (l3 < 3); l3 = (l3 + 1)) fRec3[l3] = 0.0;
	for (int l4 = 0; (l4 < 3); l4 = (l4 + 1)) fRec2[l4] = 0.0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fRec7[l5] = 0.0;
	for (int l6 = 0; (l6 < 3); l6 = (l6 + 1)) fRec1[l6] = 0.0;
	for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) fRec8[l7] = 0.0;
	for (int l8 = 0; (l8 < 3); l8 = (l8 + 1)) fRec0[l8] = 0.0;
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
	fConst1 = std::tan((37699.111843077517 / fConst0));
	fConst2 = (1.0 / fConst1);
	fConst3 = (fConst0 * std::sin((75398.223686155034 / fConst0)));
	fConst4 = (11800.82018976876 / fConst3);
	fConst5 = (1.0 / (((fConst2 + fConst4) / fConst1) + 1.0));
	fConst6 = (2.0 * (1.0 - (1.0 / mydsp_faustpower2_f(fConst1))));
	fConst7 = mydsp_faustpower2_f(fConst0);
	fConst8 = (4.3388468105506801e-10 * fConst0);
	fConst9 = ((fConst0 * (fConst8 + 6.8680901344593704e-09)) + 2.6522670215943701e-08);
	fConst10 = (fConst7 / fConst9);
	fConst11 = (3.6868885846545499e-10 * fConst0);
	fConst12 = (1.0 / ((fConst0 * (fConst11 + 3.0348555108869402e-06)) + 0.00486780557301784));
	fConst13 = (3.9204879585950002e-10 * fConst0);
	fConst14 = (1.0 / ((fConst0 * (fConst13 + 2.0047872746271098e-06)) + 0.00048978515761155495));
	fConst15 = (7.6673121439986096e-12 * fConst0);
	fConst16 = (fConst0 * (fConst15 + -3.9949085717896201e-05));
	fConst17 = (2.0828770493449602e-05 * fConst0);
	fConst18 = (1.0 / (fConst17 + 0.00021901631427173599));
	fConst19 = (3.7454979802541999e-06 * fConst0);
	fConst20 = (0.0 - fConst19);
	fConst21 = (0.00021901631427173599 - fConst17);
	fConst22 = (1.2821120020392999e-10 * fConst0);
	fConst23 = (fConst22 + -6.2652181541007596e-07);
	fConst24 = (1.12312054615984e-09 * fConst0);
	fConst25 = (fConst24 + -2.8621970465474001e-06);
	fConst26 = (1.1344651981412601e-09 * fConst0);
	fConst27 = (2.8911081278256599e-06 - fConst26);
	fConst28 = (fConst22 + 6.2652181541007596e-07);
	fConst29 = (fConst24 + 2.8621970465474001e-06);
	fConst30 = (-2.8911081278256599e-06 - fConst26);
	fConst31 = (2.26293387153501e-14 * fConst0);
	fConst32 = (fConst31 + -1.17905906929765e-07);
	fConst33 = (2.26293387153501e-12 * fConst0);
	fConst34 = (fConst33 + -1.17905906929765e-05);
	fConst35 = (fConst31 + 1.17905906929765e-07);
	fConst36 = (fConst33 + 1.17905906929765e-05);
	fConst37 = (0.00097957031522311099 - (7.8409759171899901e-10 * fConst7));
	fConst38 = ((fConst0 * (fConst13 + -2.0047872746271098e-06)) + 0.00048978515761155495);
	fConst39 = (0.0 - (1.53346242879972e-11 * fConst7));
	fConst40 = (fConst0 * (fConst15 + 3.9949085717896201e-05));
	fConst41 = (7.3737771693091102e-10 * fConst7);
	fConst42 = (0.0097356111460356904 - fConst41);
	fConst43 = ((fConst0 * (fConst11 + -3.0348555108869402e-06)) + 0.00486780557301784);
	fConst44 = (8.6710157453912601e-07 * fConst0);
	fConst45 = ((3.6868885846545499e-10 * fConst7) + -0.0031609127097518498);
	fConst46 = (-0.0063218254195036901 - fConst41);
	fConst47 = (1.0 / fConst9);
	fConst48 = (5.3045340431887401e-08 - (8.6776936211013499e-10 * fConst7));
	fConst49 = ((fConst0 * (fConst8 + -6.8680901344593704e-09)) + 2.6522670215943701e-08);
	fConst50 = (((fConst2 - fConst4) / fConst1) + 1.0);
	fConst51 = (4435.1896285973553 / fConst3);
	fConst52 = (((fConst2 + fConst51) / fConst1) + 1.0);
	fConst53 = (((fConst2 - fConst51) / fConst1) + 1.0);
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
	double fSlow0 = (0.0070000000000000062 * double(fVslider0));
	double fSlow1 = (0.0070000000000000062 * double(fVslider1));
	double fSlow2 = (0.0070000000000000062 * double(fVslider2));
	for (int i = 0; (i < ReCount); i = (i + 1)) {
		fRec5[0] = (double(buf[i]) - (fConst18 * ((fConst21 * fRec5[2]) + (0.000438032628543473 * fRec5[1]))));
		fRec6[0] = (fSlow0 + (0.99299999999999999 * fRec6[1]));
		double fTemp0 = ((fConst0 * (fConst28 + (fRec6[0] * (fConst29 + (fConst30 * fRec6[0]))))) + 0.000146000960455196);
		fRec4[0] = ((fConst18 * ((fConst20 * fRec5[2]) + (fConst19 * fRec5[0]))) - (((fRec4[1] * ((fConst7 * ((fRec6[0] * ((2.2689303962825102e-09 * fRec6[0]) + -2.2462410923196899e-09)) + -2.5642240040785998e-10)) + 0.00029200192091039201)) + (fRec4[2] * ((fConst0 * (fConst23 + (fRec6[0] * (fConst25 + (fConst27 * fRec6[0]))))) + 0.000146000960455196))) / fTemp0));
		fRec3[0] = (double(symclip(double((fConst0 * ((((fRec4[0] * (fConst32 + (fConst34 * fRec6[0]))) + (fConst0 * (fRec4[1] * ((0.0 - (4.5258677430700104e-12 * fRec6[0])) + -4.5258677430700099e-14)))) + (fRec4[2] * (fConst35 + (fConst36 * fRec6[0])))) / fTemp0))))) - (fConst14 * ((fConst37 * fRec3[1]) + (fConst38 * fRec3[2]))));
		fRec2[0] = (double(symclip(double((fConst14 * (((fConst16 * fRec3[0]) + (fConst39 * fRec3[1])) + (fConst40 * fRec3[2])))))) - (fConst12 * ((fConst42 * fRec2[1]) + (fConst43 * fRec2[2]))));
		fRec7[0] = (fSlow1 + (0.99299999999999999 * fRec7[1]));
		double fTemp1 = ((fConst45 * fRec7[0]) + 0.0040143591413848399);
		fRec1[0] = ((fConst12 * (((fRec2[0] * (fConst44 + fTemp1)) + (fRec2[1] * ((fConst46 * fRec7[0]) + 0.0080287182827696903))) + (fRec2[2] * (fTemp1 - fConst44)))) - (fConst47 * ((fConst48 * fRec1[1]) + (fConst49 * fRec1[2]))));
		fRec8[0] = (fSlow2 + (0.99299999999999999 * fRec8[1]));
		double fTemp2 = (0.0 - (1.74325899023428e-09 * fRec8[0]));
		double fTemp3 = (fConst6 * fRec0[1]);
		fRec0[0] = ((fConst10 * (((fRec1[0] * fTemp2) + (3.4865179804685599e-09 * (fRec8[0] * fRec1[1]))) + (fRec1[2] * fTemp2))) - (fConst5 * ((fConst50 * fRec0[2]) + fTemp3)));
		buf[i] = FAUSTFLOAT((fConst5 * ((fTemp3 + (fConst52 * fRec0[0])) + (fConst53 * fRec0[2]))));
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		fRec4[2] = fRec4[1];
		fRec4[1] = fRec4[0];
		fRec3[2] = fRec3[1];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fRec7[1] = fRec7[0];
		fRec1[2] = fRec1[1];
		fRec1[1] = fRec1[0];
		fRec8[1] = fRec8[0];
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
		fVslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case TONE: 
		fVslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
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
   SUSTAIN, 
   TONE, 
   VOLUME, 
} PortIndex;
*/

} // end namespace bmp
