// generated from file '../src/LV2/faust/bossds1.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)

#include "clipping.h"

namespace bossds1 {

class Dsp: public PluginLV2 {
private:
	double 	fLowVec0[2];
	uint32_t 	iLowConst0;
	double 	fLowConst1;
	double 	fLowConst2;
	double 	fLowConst3;
	double 	fLowConst4;
	double 	fLowRec0[2];
	gx_resample::FixedRateResampler smp;
	uint32_t samplingFreq;
	uint32_t fSamplingFreq;
	double 	fConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec1[2];
	double 	fConst7;
	double 	fConst8;
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
	double 	fConst21;
	double 	fConst22;
	double 	fConst23;
	double 	fConst24;
	double 	fConst25;
	double 	fConst26;
	double 	fConst27;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec5[2];
	double 	fConst28;
	double 	fConst29;
	double 	fConst30;
	double 	fConst31;
	double 	fConst32;
	double 	fConst33;
	double 	fConst34;
	double 	fConst35;
	double 	fConst36;
	double 	fConst37;
	double 	fConst38;
	double 	fConst39;
	double 	fConst40;
	double 	fRec8[2];
	double 	fConst41;
	double 	fConst42;
	double 	fConst43;
	double 	fRec7[4];
	double 	fConst44;
	double 	fConst45;
	double 	fRec6[3];
	double 	fConst46;
	double 	fRec4[3];
	double 	fConst47;
	double 	fConst48;
	double 	fConst49;
	double 	fConst50;
	double 	fConst51;
	double 	fConst52;
	double 	fConst53;
	double 	fVec0[2];
	double 	fConst54;
	double 	fConst55;
	double 	fConst56;
	double 	fRec9[2];
	double 	fRec3[3];
	double 	fRec2[3];
	double 	fConst57;
	double 	fConst58;
	double 	fConst59;
	double 	fConst60;
	double 	fConst61;
	double 	fRec0[3];
	double 	fConst62;
	double 	fConst63;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec10[2];

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
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<4; i++) fRec7[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<3; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<3; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<3; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fLowVec0[i] = 0;
	for (int i=0; i<2; i++) fLowRec0[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t RsamplingFreq)
{
	samplingFreq = 96000;
	smp.setup(RsamplingFreq, samplingFreq);
	iLowConst0 = min(192000, max(1, RsamplingFreq));
	fLowConst1 = (1.0 / tan((1.5707963267948966 * (double(iLowConst0) / double(iLowConst0)))));
	fLowConst2 = (1 + fLowConst1);
	fLowConst3 = (1.0 / fLowConst2);
	fLowConst4 = (0 - ((1 - fLowConst1) / fLowConst2));
	fSamplingFreq = samplingFreq;
	fConst0 = min(1.92e+05, max(1.0, (double)fSamplingFreq));
	fConst1 = double(fConst0);
	fConst2 = (4.33879508860142e-10 * fConst1);
	fConst3 = (2.44347979826776e-08 + (fConst1 * (fConst2 - 7.11639898820675e-09)));
	fConst4 = faustpower<2>(fConst1);
	fConst5 = (4.88695959653553e-08 - (8.67759017720285e-10 * fConst4));
	fConst6 = (1.0 / (2.44347979826776e-08 + (fConst1 * (7.11639898820675e-09 + fConst2))));
	fConst7 = (2.89644353783249e-10 * fConst1);
	fConst8 = ((fConst1 * (0 - (9.44398925362792e-07 + fConst7))) - 0.000537812599864916);
	fConst9 = (2.65571689713263e-10 * fConst1);
	fConst10 = (0.000537812599864916 + (fConst1 * (7.50424979344313e-07 + fConst9)));
	fConst11 = (3.3778968192322e-10 * fConst1);
	fConst12 = (0.00114855258827151 + (fConst1 * (1.55559824875468e-06 + fConst11)));
	fConst13 = (2.18842400636233e-10 * fConst1);
	fConst14 = (0.000537812599864916 + (fConst1 * (0 - (5.20602596669238e-08 + fConst13))));
	fConst15 = (0.000182856283954071 + (fConst1 * (fConst13 - 2.33324618325395e-07)));
	fConst16 = ((fConst1 * (9.44398925362792e-07 - fConst7)) - 0.000537812599864916);
	fConst17 = (0.000537812599864916 + (fConst1 * (fConst9 - 7.50424979344313e-07)));
	fConst18 = (0.00114855258827151 + (fConst1 * (fConst11 - 1.55559824875468e-06)));
	fConst19 = ((5.79288707566498e-10 * fConst4) - 0.00107562519972983);
	fConst20 = (0.00107562519972983 - (5.31143379426527e-10 * fConst4));
	fConst21 = (0.00229710517654303 - (6.7557936384644e-10 * fConst4));
	fConst22 = tan((72.25663103256524 / fConst0));
	fConst23 = (1.0 / faustpower<2>(fConst22));
	fConst24 = (2 * (1 - fConst23));
	fConst25 = (1.0 / fConst22);
	fConst26 = (1 + ((fConst25 - 1.414213562373095) / fConst22));
	fConst27 = (1.0 / (1 + ((1.414213562373095 + fConst25) / fConst22)));
	fConst28 = (1.49503874539434e-11 * fConst1);
	fConst29 = (1.66555708487018e-05 + fConst28);
	fConst30 = (fConst28 - 7.50903344506575e-07);
	fConst31 = (fConst28 - 1.66555708487018e-05);
	fConst32 = (3.53982651634833e-10 * fConst1);
	fConst33 = (1.94656546234155e-05 + (fConst1 * (fConst32 - 2.38582349500046e-07)));
	fConst34 = (2.38582349500046e-07 + fConst32);
	fConst35 = (5.83969638702466e-05 + (fConst1 * (0 - fConst34)));
	fConst36 = (5.83969638702466e-05 + (fConst1 * (2.38582349500046e-07 - fConst32)));
	fConst37 = (1.0 / (1.94656546234155e-05 + (fConst1 * fConst34)));
	fConst38 = (2.08232145615427e-05 * fConst1);
	fConst39 = (0.000485701045951343 + fConst38);
	fConst40 = ((0.000485701045951343 - fConst38) / fConst39);
	fConst41 = (2.07110717442793e-05 * fConst1);
	fConst42 = (0 - fConst41);
	fConst43 = (1.0 / fConst39);
	fConst44 = (5.51041967277497e-09 * fConst4);
	fConst45 = (0 - fConst44);
	fConst46 = (7.50903344506575e-07 + fConst28);
	fConst47 = (2 * (0 - fConst23));
	fConst48 = tan((22619.46710584651 / fConst0));
	fConst49 = (2 * (1 - (1.0 / faustpower<2>(fConst48))));
	fConst50 = (1.0 / fConst48);
	fConst51 = (1 + ((fConst50 - 1.414213562373095) / fConst48));
	fConst52 = (1.0 / (1 + ((1.414213562373095 + fConst50) / fConst48)));
	fConst53 = (9.4e-08 * fConst0);
	fConst54 = (0.0192418 * fConst0);
	fConst55 = (1 - fConst54);
	fConst56 = (1 + fConst54);
	fConst57 = (4.37684801272465e-10 * fConst4);
	fConst58 = (0.00107562519972983 + fConst57);
	fConst59 = (0.000365712567908143 - fConst57);
	fConst60 = (0.000537812599864916 + (fConst1 * (5.20602596669238e-08 - fConst13)));
	fConst61 = (0.000182856283954071 + (fConst1 * (2.33324618325395e-07 + fConst13)));
	fConst62 = (4.28019579852603e-10 * fConst4);
	fConst63 = (0 - (8.56039159705207e-10 * fConst4));
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
	for (int i=0; i<count; i++) {
		double fLowTemp0 = (double)input0[i];
		fLowVec0[0] = fLowTemp0;
		fLowRec0[0] = ((fLowConst4 * fLowRec0[1]) + (fLowConst3 * (fLowVec0[0] + fLowVec0[1])));
		output0[i] = (FAUSTFLOAT)fLowRec0[0];
		// post processing
		fLowRec0[1] = fLowRec0[0];
		fLowVec0[1] = fLowVec0[0];
	}
	FAUSTFLOAT buf[smp.max_out_count(count)];
	int ReCount = smp.up(count, output0, buf);
	double 	fSlow0 = (0.007000000000000006 * double(fslider0));
	double 	fSlow1 = (0.002198000000000002 * double(fslider1));
	double 	fSlow2 = (0.007000000000000006 * pow(10,(0.05 * double(fslider2))));
	for (int i=0; i<ReCount; i++) {
		fRec1[0] = (fSlow0 + (0.993 * fRec1[1]));
		double fTemp0 = (fConst12 + (fRec1[0] * (fConst10 + (fConst8 * fRec1[0]))));
		fRec5[0] = (fSlow1 + (0.993 * fRec5[1]));
		double fTemp1 = (fConst1 * (3.0314296262996e-10 + (0 - (3.18093350083904e-10 * fRec5[0]))));
		double fTemp2 = (0.000169198590470162 + (fConst1 * (fConst29 + (fRec5[0] * (fTemp1 - 3.38397180940322e-09)))));
		double fTemp3 = (fConst4 * ((fRec5[0] * ((6.36186700167807e-10 * fRec5[0]) - 6.0628592525992e-10)) - 2.99007749078869e-11));
		fRec8[0] = ((double)buf[i] - (fConst40 * fRec8[1]));
		fRec7[0] = ((fConst43 * ((fConst42 * fRec8[1]) + (fConst41 * fRec8[0]))) - (fConst37 * (((fConst36 * fRec7[1]) + (fConst35 * fRec7[2])) + (fConst33 * fRec7[3]))));
		fRec6[0] = ((fConst37 * ((fConst44 * (fRec7[1] + fRec7[2])) + (fConst45 * (fRec7[3] + fRec7[0])))) - (((fRec6[1] * (0.000338397180940324 + fTemp3)) + (fRec6[2] * (0.000169198590470162 + (fConst1 * (fConst31 + (fRec5[0] * (3.38397180940322e-09 + fTemp1))))))) / fTemp2));
		fRec4[0] = (asymclip3(((((fRec6[1] * (0.000338397180940323 + fTemp3)) + (fRec6[0] * (0.000169198590470161 + (fConst1 * (fConst46 + (fRec5[0] * (1.59012835323858e-05 + fTemp1))))))) + (fRec6[2] * (0.000169198590470161 + (fConst1 * (fConst30 + (fRec5[0] * (fTemp1 - 1.59012835323858e-05))))))) / fTemp2)) - (fConst27 * ((fConst26 * fRec4[2]) + (fConst24 * fRec4[1]))));
		double fTemp4 = (fConst27 * ((fConst47 * fRec4[1]) + (fConst23 * (fRec4[2] + fRec4[0]))));
		double fTemp5 = opamp(fTemp4);
		double fTemp6 = (fConst53 * (4700 + (100000 * (1.0 - fRec5[0]))));
		double fTemp7 = (1 + fTemp6);
		double fTemp8 = (fTemp4 - fTemp5);
		fVec0[0] = fTemp8;
		fRec9[0] = ((fRec9[1] * (0 - ((1 - fTemp6) / fTemp7))) + (((fConst56 * fVec0[0]) + (fConst55 * fVec0[1])) / fTemp7));
		fRec3[0] = (0 - ((opamp(((fRec9[0] + fTemp5) - fTemp4)) + ((fConst52 * ((fConst51 * fRec3[2]) + (fConst49 * fRec3[1]))) + fTemp5)) - fTemp4));
		fRec2[0] = (asymhardclip2((fConst52 * (fRec3[0] + (fRec3[2] + (2 * fRec3[1]))))) - (((fRec2[1] * (fConst21 + (fRec1[0] * (fConst20 + (fConst19 * fRec1[0]))))) + (fRec2[2] * (fConst18 + (fRec1[0] * (fConst17 + (fConst16 * fRec1[0])))))) / fTemp0));
		fRec0[0] = (((((fRec2[0] * (fConst61 + (fConst60 * fRec1[0]))) + (fRec2[1] * (fConst59 + (fConst58 * fRec1[0])))) + (fRec2[2] * (fConst15 + (fConst14 * fRec1[0])))) / fTemp0) - (fConst6 * ((fConst5 * fRec0[1]) + (fConst3 * fRec0[2]))));
		fRec10[0] = (fSlow2 + (0.993 * fRec10[1]));
		buf[i] = (FAUSTFLOAT)(fConst6 * (fRec10[0] * ((fConst63 * fRec0[1]) + (fConst62 * (fRec0[2] + fRec0[0])))));
		// post processing
		fRec10[1] = fRec10[0];
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
		fRec9[1] = fRec9[0];
		fVec0[1] = fVec0[0];
		fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		for (int i=3; i>0; i--) fRec7[i] = fRec7[i-1];
		fRec8[1] = fRec8[0];
		fRec5[1] = fRec5[0];
		fRec1[1] = fRec1[0];
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
	case LEVEL: 
		fslider2_ = (float*)data; // , 3.0, -2e+01, 12.0, 0.1 
		break;
	case TONE: 
		fslider0_ = (float*)data; // , 0.7, 0.0, 1.0, 0.01 
		break;
	case DRIVE: 
		fslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
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
