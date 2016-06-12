// generated from file '../src/LV2/faust/bmp.dsp' by dsp2cc:
// Code generated with Faust 0.9.73 (http://faust.grame.fr)

#include "clipping.h"

namespace bmp {

class Dsp: public PluginLV2 {
private:
	gx_resample::FixedRateResampler smp;
	uint32_t samplingFreq;
	uint32_t fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec0[2];
	double 	fConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec2[2];
	double 	fConst9;
	double 	fConst10;
	double 	fConst11;
	double 	fConst12;
	double 	fConst13;
	double 	fConst14;
	double 	fConst15;
	double 	fConst16;
	double 	fConst17;
	double 	fConst18;
	double 	fConst19;
	double 	fConst20;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec5[2];
	double 	fConst21;
	double 	fConst22;
	double 	fConst23;
	double 	fConst24;
	double 	fConst25;
	double 	fConst26;
	double 	fConst27;
	double 	fConst28;
	double 	fConst29;
	double 	fConst30;
	double 	fConst31;
	double 	fConst32;
	double 	fConst33;
	double 	fConst34;
	double 	fRec7[3];
	double 	fConst35;
	double 	fConst36;
	double 	fRec6[3];
	double 	fConst37;
	double 	fConst38;
	double 	fRec4[3];
	double 	fConst39;
	double 	fConst40;
	double 	fConst41;
	double 	fConst42;
	double 	fRec3[3];
	double 	fConst43;
	double 	fConst44;
	double 	fRec1[3];
	double 	fConst45;
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
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<3; i++) fRec7[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<3; i++) fRec4[i] = 0;
	for (int i=0; i<3; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec1[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t RsamplingFreq)
{
	samplingFreq = 96000;
	smp.setup(RsamplingFreq, samplingFreq);
	fSamplingFreq = samplingFreq;
	fConst0 = double(min(192000, max(1, fSamplingFreq)));
	fConst1 = (4.33884681055068e-10 * fConst0);
	fConst2 = (2.65226702159437e-08 + (fConst0 * (fConst1 - 6.86809013445937e-09)));
	fConst3 = faustpower<2>(fConst0);
	fConst4 = (5.30453404318874e-08 - (8.67769362110135e-10 * fConst3));
	fConst5 = (2.65226702159437e-08 + (fConst0 * (6.86809013445937e-09 + fConst1)));
	fConst6 = (1.0 / fConst5);
	fConst7 = (8.67101574539126e-07 * fConst0);
	fConst8 = (0.00401435914138484 - fConst7);
	fConst9 = ((3.68688858465455e-10 * fConst3) - 0.00316091270975185);
	fConst10 = (3.68688858465455e-10 * fConst0);
	fConst11 = (0.00486780557301784 + (fConst0 * (fConst10 - 3.03485551088694e-06)));
	fConst12 = (7.37377716930911e-10 * fConst3);
	fConst13 = (0.00973561114603569 - fConst12);
	fConst14 = (1.0 / (0.00486780557301784 + (fConst0 * (3.03485551088694e-06 + fConst10))));
	fConst15 = (3.920487958595e-10 * fConst0);
	fConst16 = (0.000489785157611555 + (fConst0 * (fConst15 - 2.00478727462711e-06)));
	fConst17 = (0.000979570315223111 - (7.84097591718999e-10 * fConst3));
	fConst18 = (1.0 / (0.000489785157611555 + (fConst0 * (2.00478727462711e-06 + fConst15))));
	fConst19 = (1.2821120020393e-10 * fConst0);
	fConst20 = (6.26521815410076e-07 + fConst19);
	fConst21 = (1.13446519814126e-09 * fConst0);
	fConst22 = (0 - (2.89110812782566e-06 + fConst21));
	fConst23 = (1.12312054615984e-09 * fConst0);
	fConst24 = (2.8621970465474e-06 + fConst23);
	fConst25 = (2.26293387153501e-12 * fConst0);
	fConst26 = (1.17905906929765e-05 + fConst25);
	fConst27 = (2.26293387153501e-14 * fConst0);
	fConst28 = (1.17905906929765e-07 + fConst27);
	fConst29 = (2.89110812782566e-06 - fConst21);
	fConst30 = (fConst23 - 2.8621970465474e-06);
	fConst31 = (fConst19 - 6.26521815410076e-07);
	fConst32 = (2.08287704934496e-05 * fConst0);
	fConst33 = (0.000219016314271736 - fConst32);
	fConst34 = (1.0 / (0.000219016314271736 + fConst32));
	fConst35 = (3.7454979802542e-06 * fConst0);
	fConst36 = (0 - fConst35);
	fConst37 = (fConst25 - 1.17905906929765e-05);
	fConst38 = (fConst27 - 1.17905906929765e-07);
	fConst39 = (7.66731214399861e-12 * fConst0);
	fConst40 = (fConst0 * (3.99490857178962e-05 + fConst39));
	fConst41 = (0 - (1.53346242879972e-11 * fConst3));
	fConst42 = (fConst0 * (fConst39 - 3.99490857178962e-05));
	fConst43 = (0 - (0.00632182541950369 + fConst12));
	fConst44 = (0.00401435914138484 + fConst7);
	fConst45 = (fConst3 / fConst5);
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
#define fslider2 (*fslider2_)
	FAUSTFLOAT buf[smp.max_out_count(count)];
	int ReCount = smp.up(count, input0, buf);
	double 	fSlow0 = (0.007000000000000006 * double(fslider0));
	double 	fSlow1 = (0.007000000000000006 * double(fslider1));
	double 	fSlow2 = (0.007000000000000006 * double(fslider2));
	for (int i=0; i<ReCount; i++) {
		fRec0[0] = ((0.993 * fRec0[1]) + fSlow0);
		double fTemp0 = (0 - (1.74325899023428e-09 * fRec0[0]));
		fRec2[0] = ((0.993 * fRec2[1]) + fSlow1);
		double fTemp1 = (fConst9 * fRec2[0]);
		fRec5[0] = ((0.993 * fRec5[1]) + fSlow2);
		double fTemp2 = (0.000146000960455196 + (fConst0 * ((fRec5[0] * (fConst24 + (fConst22 * fRec5[0]))) + fConst20)));
		fRec7[0] = ((double)buf[i] - (fConst34 * ((fConst33 * fRec7[2]) + (0.000438032628543473 * fRec7[1]))));
		fRec6[0] = ((fConst34 * ((fConst36 * fRec7[2]) + (fConst35 * fRec7[0]))) - (((fRec6[1] * (0.000292001920910392 + (fConst3 * ((fRec5[0] * ((2.26893039628251e-09 * fRec5[0]) - 2.24624109231969e-09)) - 2.5642240040786e-10)))) + (fRec6[2] * (0.000146000960455196 + (fConst0 * (fConst31 + (fRec5[0] * (fConst30 + (fConst29 * fRec5[0])))))))) / fTemp2));
		fRec4[0] = (symclip((fConst0 * ((((fRec6[0] * (fConst38 + (fConst37 * fRec5[0]))) + (fConst0 * (fRec6[1] * ((0 - (4.52586774307001e-12 * fRec5[0])) - 4.52586774307001e-14)))) + (fRec6[2] * (fConst28 + (fConst26 * fRec5[0])))) / fTemp2))) - (fConst18 * ((fConst17 * fRec4[1]) + (fConst16 * fRec4[2]))));
		fRec3[0] = (symclip((fConst18 * (((fConst42 * fRec4[0]) + (fConst41 * fRec4[1])) + (fConst40 * fRec4[2])))) - (fConst14 * ((fConst13 * fRec3[1]) + (fConst11 * fRec3[2]))));
		fRec1[0] = ((fConst14 * (((fRec3[0] * (fTemp1 + fConst44)) + (fRec3[1] * (0.00802871828276969 + (fConst43 * fRec2[0])))) + (fRec3[2] * (fTemp1 + fConst8)))) - (fConst6 * ((fConst4 * fRec1[1]) + (fConst2 * fRec1[2]))));
		buf[i] = (FAUSTFLOAT)(fConst45 * (((fRec1[0] * fTemp0) + (3.48651798046856e-09 * (fRec0[0] * fRec1[1]))) + (fRec1[2] * fTemp0)));
		// post processing
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
		fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
		fRec5[1] = fRec5[0];
		fRec2[1] = fRec2[0];
		fRec0[1] = fRec0[0];
	}
	smp.down(buf, output0);
#undef fslider0
#undef fslider1
#undef fslider2
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
		fslider2_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case TONE: 
		fslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case VOLUME: 
		fslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
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
