// generated from file '../src/LV2/faust/fuzzface.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "trany.h"

namespace fuzzface {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec12[2];
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec13[2];
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
	double 	fConst28;
	double 	fConst29;
	double 	fConst30;
	double 	fConst31;
	double 	fConst32;
	double 	fConst33;
	double 	fRec14[6];
	double 	fConst34;
	double 	fConst35;
	double 	fConst36;
	double 	fConst37;
	double 	fConst38;
	double 	fConst39;
	double 	fConst40;
	double 	fConst41;
	double 	fConst42;
	double 	fConst43;
	double 	fConst44;
	double 	fConst45;
	double 	fConst46;
	double 	fConst47;
	double 	fConst48;
	double 	fConst49;
	double 	fConst50;
	double 	fConst51;
	double 	fConst52;
	double 	fConst53;
	double 	fConst54;
	double 	fConst55;
	double 	fConst56;
	double 	fConst57;
	double 	fConst58;
	double 	fConst59;
	double 	fConst60;
	double 	fConst61;
	double 	fConst62;
	double 	fConst63;
	double 	fRec11[3];
	double 	fVec0[2];
	double 	fRec10[2];
	double 	fConst64;
	double 	fConst65;
	double 	fConst66;
	double 	fConst67;
	double 	fRec15[2];
	double 	fRec9[3];
	double 	fConst68;
	double 	fConst69;
	double 	fConst70;
	double 	fConst71;
	double 	fConst72;
	double 	fRec8[2];
	double 	fRec7[3];
	double 	fVec1[2];
	double 	fRec6[2];
	double 	fRec16[2];
	double 	fRec5[3];
	double 	fRec4[2];
	double 	fRec3[3];
	double 	fVec2[2];
	double 	fRec2[2];
	double 	fRec17[2];
	double 	fRec1[3];
	double 	fRec0[2];
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
	id = "fuzzface";
	name = N_("Fuzz Face");
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
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<6; i++) fRec14[i] = 0;
	for (int i=0; i<3; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<3; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<3; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<3; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<3; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = double(iConst0);
	fConst2 = (3.98985774247549e-22 * fConst1);
	fConst3 = (5.31230624730483e-11 + (fConst1 * (1.83615604104971e-13 + (fConst1 * (1.99042653510896e-15 + fConst2)))));
	fConst4 = (3.73292075290073e-29 * fConst1);
	fConst5 = ((fConst1 * ((fConst1 * ((fConst1 * (0 - (1.05633134620746e-20 + fConst4))) - 3.11506369039915e-14)) - 2.30719916990074e-11)) - 1.07493164710329e-09);
	fConst6 = (1.07449105454163e-09 + (fConst1 * (2.29636966370042e-11 + (fConst1 * (2.91602352831988e-14 + (fConst1 * (1.01643277726662e-20 + fConst4)))))));
	fConst7 = (4.76991513499346e-20 * fConst1);
	fConst8 = (5.00346713698171e-13 + fConst7);
	fConst9 = (0 - fConst8);
	fConst10 = (fConst7 - 5.38351707988916e-15);
	fConst11 = (5.38351707988916e-15 - fConst7);
	fConst12 = (5.05730339185222e-13 * fConst1);
	fConst13 = (fConst12 - 1.16162215422261e-12);
	fConst14 = (1.16162215422261e-12 - fConst12);
	fConst15 = ((fConst1 * (1.83615604104971e-13 + (fConst1 * (fConst2 - 1.99042653510896e-15)))) - 5.31230624730483e-11);
	fConst16 = (1.07493164710329e-09 + (fConst1 * ((fConst1 * (3.11506369039915e-14 + (fConst1 * (fConst4 - 1.05633134620746e-20)))) - 2.30719916990074e-11)));
	fConst17 = ((fConst1 * (2.29636966370042e-11 + (fConst1 * ((fConst1 * (1.01643277726662e-20 - fConst4)) - 2.91602352831988e-14)))) - 1.07449105454163e-09);
	fConst18 = (1.19695732274265e-21 * fConst1);
	fConst19 = ((fConst1 * (1.83615604104971e-13 + (fConst1 * (1.99042653510896e-15 - fConst18)))) - 1.59369187419145e-10);
	fConst20 = (1.86646037645036e-28 * fConst1);
	fConst21 = (3.22479494130986e-09 + (fConst1 * ((fConst1 * ((fConst1 * (3.16899403862238e-20 - fConst20)) - 3.11506369039915e-14)) - 2.30719916990074e-11)));
	fConst22 = ((fConst1 * (2.29636966370042e-11 + (fConst1 * (2.91602352831988e-14 + (fConst1 * (fConst20 - 3.04929833179984e-20)))))) - 3.22347316362488e-09);
	fConst23 = (7.97971548495099e-22 * fConst1);
	fConst24 = ((fConst1 * ((fConst1 * (3.98085307021793e-15 + fConst23)) - 3.67231208209942e-13)) - 1.06246124946097e-10);
	fConst25 = (3.73292075290073e-28 * fConst1);
	fConst26 = (2.14986329420657e-09 + (fConst1 * (4.61439833980148e-11 + (fConst1 * ((fConst1 * (fConst25 - 2.11266269241492e-20)) - 6.2301273807983e-14)))));
	fConst27 = ((fConst1 * ((fConst1 * (5.83204705663976e-14 + (fConst1 * (2.03286555453323e-20 - fConst25)))) - 4.59273932740084e-11)) - 2.14898210908325e-09);
	fConst28 = (1.06246124946097e-10 + (fConst1 * ((fConst1 * (fConst23 - 3.98085307021793e-15)) - 3.67231208209942e-13)));
	fConst29 = ((fConst1 * (4.61439833980148e-11 + (fConst1 * (6.2301273807983e-14 + (fConst1 * (0 - (2.11266269241492e-20 + fConst25))))))) - 2.14986329420657e-09);
	fConst30 = (2.14898210908325e-09 + (fConst1 * ((fConst1 * ((fConst1 * (2.03286555453323e-20 + fConst25)) - 5.83204705663976e-14)) - 4.59273932740084e-11)));
	fConst31 = (1.59369187419145e-10 + (fConst1 * (1.83615604104971e-13 + (fConst1 * (0 - (1.99042653510896e-15 + fConst18))))));
	fConst32 = ((fConst1 * ((fConst1 * (3.11506369039915e-14 + (fConst1 * (3.16899403862238e-20 + fConst20)))) - 2.30719916990074e-11)) - 3.22479494130986e-09);
	fConst33 = (3.22347316362488e-09 + (fConst1 * (2.29636966370042e-11 + (fConst1 * ((fConst1 * (0 - (3.04929833179984e-20 + fConst20))) - 2.91602352831988e-14)))));
	fConst34 = (1.43097454049804e-19 * fConst1);
	fConst35 = (5.00346713698171e-13 + fConst34);
	fConst36 = (0 - fConst35);
	fConst37 = (5.38351707988916e-15 - fConst34);
	fConst38 = (fConst34 - 5.38351707988916e-15);
	fConst39 = (1.16162215422261e-12 + fConst12);
	fConst40 = (0 - fConst39);
	fConst41 = (1.01146067837044e-12 * fConst1);
	fConst42 = (2.32324430844522e-12 - fConst41);
	fConst43 = (9.53983026998693e-20 * fConst1);
	fConst44 = (1.00069342739634e-12 - fConst43);
	fConst45 = (1.07670341597783e-14 + fConst43);
	fConst46 = (0 - fConst45);
	fConst47 = (fConst43 - 1.00069342739634e-12);
	fConst48 = (fConst41 - 2.32324430844522e-12);
	fConst49 = (2.32324430844522e-12 + fConst41);
	fConst50 = (0 - fConst49);
	fConst51 = (1.00069342739634e-12 + fConst43);
	fConst52 = (0 - fConst51);
	fConst53 = (fConst43 - 1.07670341597783e-14);
	fConst54 = (1.07670341597783e-14 - fConst43);
	fConst55 = (5.00346713698171e-13 - fConst34);
	fConst56 = (fConst34 - 5.00346713698171e-13);
	fConst57 = (5.38351707988916e-15 + fConst34);
	fConst58 = (0 - fConst57);
	fConst59 = (5.00346713698171e-13 - fConst7);
	fConst60 = (5.38351707988916e-15 + fConst7);
	fConst61 = (0 - fConst60);
	fConst62 = (fConst7 - 5.00346713698171e-13);
	fConst63 = faustpower<2>(fConst1);
	fConst64 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst65 = (1 + fConst64);
	fConst66 = (0.027 / fConst65);
	fConst67 = (0 - ((1 - fConst64) / fConst65));
	fConst68 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst69 = (0 - fConst68);
	fConst70 = (1 + fConst68);
	fConst71 = (0.025 / fConst70);
	fConst72 = (0 - ((1 - fConst68) / fConst70));
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
	double 	fSlow0 = (0.007000000000000006 * (1.0 - double(fslider0)));
	double 	fSlow1 = (0.007000000000000006 * (1.0 - double(fslider1)));
	for (int i=0; i<count; i++) {
		double fTemp0 = (2.0 * fRec3[1]);
		double fTemp1 = (2.0 * fRec7[1]);
		double fTemp2 = (2.0 * fRec11[1]);
		fRec12[0] = ((0.993 * fRec12[1]) + fSlow0);
		double fTemp3 = (2.44402781742033e-09 + (fConst1 * ((fRec12[0] * (fConst6 + (fConst5 * fRec12[0]))) + fConst3)));
		fRec13[0] = ((0.993 * fRec13[1]) + fSlow1);
		double fTemp4 = (fConst13 * fRec13[0]);
		fRec14[0] = ((double)input0[i] - ((((((fRec14[1] * (1.22201390871017e-08 + (fConst1 * ((fRec12[0] * (fConst33 + (fConst32 * fRec12[0]))) + fConst31)))) + (fRec14[2] * (2.44402781742033e-08 + (fConst1 * ((fRec12[0] * (fConst30 + (fConst29 * fRec12[0]))) + fConst28))))) + (fRec14[3] * (2.44402781742033e-08 + (fConst1 * ((fRec12[0] * (fConst27 + (fConst26 * fRec12[0]))) + fConst24))))) + (fRec14[4] * (1.22201390871017e-08 + (fConst1 * ((fRec12[0] * (fConst22 + (fConst21 * fRec12[0]))) + fConst19))))) + (fRec14[5] * (2.44402781742033e-09 + (fConst1 * ((fRec12[0] * (fConst17 + (fConst16 * fRec12[0]))) + fConst15))))) / fTemp3));
		double fTemp5 = (fConst40 * fRec13[0]);
		fRec11[0] = ((fConst63 * (((((((fRec14[0] * (fConst39 + ((fConst1 * (fRec12[0] * (fConst62 + ((fRec12[0] * (fConst61 + (fConst60 * fRec13[0]))) + (fConst59 * fRec13[0]))))) + fTemp5))) + (fRec14[1] * (((fConst1 * (fRec12[0] * (((fRec12[0] * (fConst57 + (fConst58 * fRec13[0]))) + (fConst56 * fRec13[0])) + fConst55))) + fTemp4) + fConst14))) + (fRec14[2] * (((fConst1 * (fRec12[0] * (fConst51 + ((fRec12[0] * (fConst54 + (fConst53 * fRec13[0]))) + (fConst52 * fRec13[0]))))) + (fConst49 * fRec13[0])) + fConst50))) + (fRec14[3] * (fConst48 + ((fConst1 * (fRec12[0] * (fConst47 + ((fRec12[0] * (fConst46 + (fConst45 * fRec13[0]))) + (fConst44 * fRec13[0]))))) + (fConst42 * fRec13[0]))))) + (fRec14[4] * (fConst39 + (fTemp5 + (fConst1 * (fRec12[0] * (((fRec12[0] * (fConst38 + (fConst37 * fRec13[0]))) + (fConst35 * fRec13[0])) + fConst36))))))) + (fRec14[5] * (fConst14 + (fTemp4 + (fConst1 * (fRec12[0] * (fConst8 + ((fRec12[0] * (fConst11 + (fConst10 * fRec13[0]))) + (fConst9 * fRec13[0]))))))))) / fTemp3)) - (fTemp2 + fRec11[2]));
		double fTemp6 = (fRec11[2] + (fRec11[0] + fTemp2));
		fVec0[0] = fTemp6;
		fRec10[0] = ((1.0000000000000002 * (fVec0[0] + fVec0[1])) - (0.9999999999999998 * fRec10[1]));
		fRec15[0] = ((fConst67 * fRec15[1]) + (fConst66 * (fRec9[1] + fRec9[2])));
		fRec9[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec15[0] + fRec10[0]) - 3.571981)) - 117.70440740740739);
		fRec8[0] = ((fConst72 * fRec8[1]) + (fConst71 * ((fConst68 * fRec9[0]) + (fConst69 * fRec9[1]))));
		fRec7[0] = (fRec8[0] - (fTemp1 + fRec7[2]));
		double fTemp7 = (fRec7[2] + (fRec7[0] + fTemp1));
		fVec1[0] = fTemp7;
		fRec6[0] = ((1.0000000000000002 * (fVec1[0] + fVec1[1])) - (0.9999999999999998 * fRec6[1]));
		fRec16[0] = ((fConst67 * fRec16[1]) + (fConst66 * (fRec5[1] + fRec5[2])));
		fRec5[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec16[0] + fRec6[0]) - 3.571981)) - 117.70440740740739);
		fRec4[0] = ((fConst72 * fRec4[1]) + (fConst71 * ((fConst68 * fRec5[0]) + (fConst69 * fRec5[1]))));
		fRec3[0] = (fRec4[0] - (fTemp0 + fRec3[2]));
		double fTemp8 = (fRec3[2] + (fRec3[0] + fTemp0));
		fVec2[0] = fTemp8;
		fRec2[0] = ((1.0000000000000002 * (fVec2[0] + fVec2[1])) - (0.9999999999999998 * fRec2[1]));
		fRec17[0] = ((fConst67 * fRec17[1]) + (fConst66 * (fRec1[1] + fRec1[2])));
		fRec1[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec17[0] + fRec2[0]) - 3.571981)) - 117.70440740740739);
		fRec0[0] = ((fConst72 * fRec0[1]) + (fConst71 * ((fConst68 * fRec1[0]) + (fConst69 * fRec1[1]))));
		output0[i] = (FAUSTFLOAT)fRec0[0];
		// post processing
		fRec0[1] = fRec0[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec17[1] = fRec17[0];
		fRec2[1] = fRec2[0];
		fVec2[1] = fVec2[0];
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec16[1] = fRec16[0];
		fRec6[1] = fRec6[0];
		fVec1[1] = fVec1[0];
		fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec15[1] = fRec15[0];
		fRec10[1] = fRec10[0];
		fVec0[1] = fVec0[0];
		fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
		for (int i=5; i>0; i--) fRec14[i] = fRec14[i-1];
		fRec13[1] = fRec13[0];
		fRec12[1] = fRec12[0];
	}
#undef fslider0
#undef fslider1
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case FUZZ: 
		fslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case LEVEL: 
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
   FUZZ, 
   LEVEL, 
} PortIndex;
*/

} // end namespace fuzzface
