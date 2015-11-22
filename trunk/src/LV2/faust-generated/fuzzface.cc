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
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec12[2];
	double 	fConst9;
	double 	fConst10;
	double 	fConst11;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec13[2];
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
	double 	fConst34;
	double 	fConst35;
	double 	fConst36;
	double 	fConst37;
	double 	fConst38;
	double 	fRec14[6];
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
	double 	fConst64;
	double 	fConst65;
	double 	fConst66;
	double 	fConst67;
	double 	fVec0[2];
	double 	fConst68;
	double 	fConst69;
	double 	fConst70;
	double 	fRec11[2];
	double 	fRec10[3];
	double 	fConst71;
	double 	fConst72;
	double 	fConst73;
	double 	fConst74;
	double 	fRec15[2];
	double 	fRec9[3];
	double 	fConst75;
	double 	fConst76;
	double 	fConst77;
	double 	fConst78;
	double 	fConst79;
	double 	fRec8[2];
	double 	fConst80;
	double 	fRec7[2];
	double 	fRec6[3];
	double 	fRec16[2];
	double 	fRec5[3];
	double 	fRec4[2];
	double 	fRec3[2];
	double 	fRec2[3];
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
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<3; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<3; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
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
	fConst1 = tan((50265.48245743669 / double(iConst0)));
	fConst2 = (2 * (1 - (1.0 / faustpower<2>(fConst1))));
	fConst3 = (1.0 / fConst1);
	fConst4 = (1 + ((fConst3 - 1.0000000000000004) / fConst1));
	fConst5 = (1.0 / (1 + ((1.0000000000000004 + fConst3) / fConst1)));
	fConst6 = double(iConst0);
	fConst7 = (3.98985774247549e-22 * fConst6);
	fConst8 = (5.31230624730483e-11 + (fConst6 * (1.83615604104971e-13 + (fConst6 * (1.99042653510896e-15 + fConst7)))));
	fConst9 = (3.73292075290073e-29 * fConst6);
	fConst10 = ((fConst6 * ((fConst6 * ((fConst6 * (0 - (1.05633134620746e-20 + fConst9))) - 3.11506369039915e-14)) - 2.30719916990074e-11)) - 1.07493164710329e-09);
	fConst11 = (1.07449105454163e-09 + (fConst6 * (2.29636966370042e-11 + (fConst6 * (2.91602352831988e-14 + (fConst6 * (1.01643277726662e-20 + fConst9)))))));
	fConst12 = (4.76991513499346e-20 * fConst6);
	fConst13 = (5.00346713698171e-13 + fConst12);
	fConst14 = (0 - fConst13);
	fConst15 = (fConst12 - 5.38351707988916e-15);
	fConst16 = (5.38351707988916e-15 - fConst12);
	fConst17 = (5.05730339185222e-13 * fConst6);
	fConst18 = (fConst17 - 1.16162215422261e-12);
	fConst19 = (1.16162215422261e-12 - fConst17);
	fConst20 = ((fConst6 * (1.83615604104971e-13 + (fConst6 * (fConst7 - 1.99042653510896e-15)))) - 5.31230624730483e-11);
	fConst21 = (1.07493164710329e-09 + (fConst6 * ((fConst6 * (3.11506369039915e-14 + (fConst6 * (fConst9 - 1.05633134620746e-20)))) - 2.30719916990074e-11)));
	fConst22 = ((fConst6 * (2.29636966370042e-11 + (fConst6 * ((fConst6 * (1.01643277726662e-20 - fConst9)) - 2.91602352831988e-14)))) - 1.07449105454163e-09);
	fConst23 = (1.19695732274265e-21 * fConst6);
	fConst24 = ((fConst6 * (1.83615604104971e-13 + (fConst6 * (1.99042653510896e-15 - fConst23)))) - 1.59369187419145e-10);
	fConst25 = (1.86646037645036e-28 * fConst6);
	fConst26 = (3.22479494130986e-09 + (fConst6 * ((fConst6 * ((fConst6 * (3.16899403862238e-20 - fConst25)) - 3.11506369039915e-14)) - 2.30719916990074e-11)));
	fConst27 = ((fConst6 * (2.29636966370042e-11 + (fConst6 * (2.91602352831988e-14 + (fConst6 * (fConst25 - 3.04929833179984e-20)))))) - 3.22347316362488e-09);
	fConst28 = (7.97971548495099e-22 * fConst6);
	fConst29 = ((fConst6 * ((fConst6 * (3.98085307021793e-15 + fConst28)) - 3.67231208209942e-13)) - 1.06246124946097e-10);
	fConst30 = (3.73292075290073e-28 * fConst6);
	fConst31 = (2.14986329420657e-09 + (fConst6 * (4.61439833980148e-11 + (fConst6 * ((fConst6 * (fConst30 - 2.11266269241492e-20)) - 6.2301273807983e-14)))));
	fConst32 = ((fConst6 * ((fConst6 * (5.83204705663976e-14 + (fConst6 * (2.03286555453323e-20 - fConst30)))) - 4.59273932740084e-11)) - 2.14898210908325e-09);
	fConst33 = (1.06246124946097e-10 + (fConst6 * ((fConst6 * (fConst28 - 3.98085307021793e-15)) - 3.67231208209942e-13)));
	fConst34 = ((fConst6 * (4.61439833980148e-11 + (fConst6 * (6.2301273807983e-14 + (fConst6 * (0 - (2.11266269241492e-20 + fConst30))))))) - 2.14986329420657e-09);
	fConst35 = (2.14898210908325e-09 + (fConst6 * ((fConst6 * ((fConst6 * (2.03286555453323e-20 + fConst30)) - 5.83204705663976e-14)) - 4.59273932740084e-11)));
	fConst36 = (1.59369187419145e-10 + (fConst6 * (1.83615604104971e-13 + (fConst6 * (0 - (1.99042653510896e-15 + fConst23))))));
	fConst37 = ((fConst6 * ((fConst6 * (3.11506369039915e-14 + (fConst6 * (3.16899403862238e-20 + fConst25)))) - 2.30719916990074e-11)) - 3.22479494130986e-09);
	fConst38 = (3.22347316362488e-09 + (fConst6 * (2.29636966370042e-11 + (fConst6 * ((fConst6 * (0 - (3.04929833179984e-20 + fConst25))) - 2.91602352831988e-14)))));
	fConst39 = (1.43097454049804e-19 * fConst6);
	fConst40 = (5.00346713698171e-13 + fConst39);
	fConst41 = (0 - fConst40);
	fConst42 = (5.38351707988916e-15 - fConst39);
	fConst43 = (fConst39 - 5.38351707988916e-15);
	fConst44 = (1.16162215422261e-12 + fConst17);
	fConst45 = (0 - fConst44);
	fConst46 = (1.01146067837044e-12 * fConst6);
	fConst47 = (2.32324430844522e-12 - fConst46);
	fConst48 = (9.53983026998693e-20 * fConst6);
	fConst49 = (1.00069342739634e-12 - fConst48);
	fConst50 = (1.07670341597783e-14 + fConst48);
	fConst51 = (0 - fConst50);
	fConst52 = (fConst48 - 1.00069342739634e-12);
	fConst53 = (fConst46 - 2.32324430844522e-12);
	fConst54 = (2.32324430844522e-12 + fConst46);
	fConst55 = (0 - fConst54);
	fConst56 = (1.00069342739634e-12 + fConst48);
	fConst57 = (0 - fConst56);
	fConst58 = (fConst48 - 1.07670341597783e-14);
	fConst59 = (1.07670341597783e-14 - fConst48);
	fConst60 = (5.00346713698171e-13 - fConst39);
	fConst61 = (fConst39 - 5.00346713698171e-13);
	fConst62 = (5.38351707988916e-15 + fConst39);
	fConst63 = (0 - fConst62);
	fConst64 = (5.00346713698171e-13 - fConst12);
	fConst65 = (5.38351707988916e-15 + fConst12);
	fConst66 = (0 - fConst65);
	fConst67 = (fConst12 - 5.00346713698171e-13);
	fConst68 = (1 + fConst3);
	fConst69 = (faustpower<2>(fConst6) / fConst68);
	fConst70 = (0 - ((1 - fConst3) / fConst68));
	fConst71 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst72 = (1 + fConst71);
	fConst73 = (0.027 / fConst72);
	fConst74 = (0 - ((1 - fConst71) / fConst72));
	fConst75 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst76 = (0 - fConst75);
	fConst77 = (1 + fConst75);
	fConst78 = (0.025 / fConst77);
	fConst79 = (0 - ((1 - fConst75) / fConst77));
	fConst80 = (1.0 / fConst68);
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
		fRec12[0] = ((0.993 * fRec12[1]) + fSlow0);
		double fTemp0 = (2.44402781742033e-09 + (fConst6 * ((fRec12[0] * (fConst11 + (fConst10 * fRec12[0]))) + fConst8)));
		fRec13[0] = ((0.993 * fRec13[1]) + fSlow1);
		double fTemp1 = (fConst18 * fRec13[0]);
		fRec14[0] = ((double)input0[i] - ((((((fRec14[1] * (1.22201390871017e-08 + (fConst6 * ((fRec12[0] * (fConst38 + (fConst37 * fRec12[0]))) + fConst36)))) + (fRec14[2] * (2.44402781742033e-08 + (fConst6 * ((fRec12[0] * (fConst35 + (fConst34 * fRec12[0]))) + fConst33))))) + (fRec14[3] * (2.44402781742033e-08 + (fConst6 * ((fRec12[0] * (fConst32 + (fConst31 * fRec12[0]))) + fConst29))))) + (fRec14[4] * (1.22201390871017e-08 + (fConst6 * ((fRec12[0] * (fConst27 + (fConst26 * fRec12[0]))) + fConst24))))) + (fRec14[5] * (2.44402781742033e-09 + (fConst6 * ((fRec12[0] * (fConst22 + (fConst21 * fRec12[0]))) + fConst20))))) / fTemp0));
		double fTemp2 = (fConst45 * fRec13[0]);
		double fTemp3 = (((((((fRec14[0] * (fConst44 + ((fConst6 * (fRec12[0] * (fConst67 + ((fRec12[0] * (fConst66 + (fConst65 * fRec13[0]))) + (fConst64 * fRec13[0]))))) + fTemp2))) + (fRec14[1] * (((fConst6 * (fRec12[0] * (((fRec12[0] * (fConst62 + (fConst63 * fRec13[0]))) + (fConst61 * fRec13[0])) + fConst60))) + fTemp1) + fConst19))) + (fRec14[2] * (((fConst6 * (fRec12[0] * (fConst56 + ((fRec12[0] * (fConst59 + (fConst58 * fRec13[0]))) + (fConst57 * fRec13[0]))))) + (fConst54 * fRec13[0])) + fConst55))) + (fRec14[3] * (fConst53 + ((fConst6 * (fRec12[0] * (fConst52 + ((fRec12[0] * (fConst51 + (fConst50 * fRec13[0]))) + (fConst49 * fRec13[0]))))) + (fConst47 * fRec13[0]))))) + (fRec14[4] * (fConst44 + (fTemp2 + (fConst6 * (fRec12[0] * (((fRec12[0] * (fConst43 + (fConst42 * fRec13[0]))) + (fConst40 * fRec13[0])) + fConst41))))))) + (fRec14[5] * (fConst19 + (fTemp1 + (fConst6 * (fRec12[0] * (fConst13 + ((fRec12[0] * (fConst16 + (fConst15 * fRec13[0]))) + (fConst14 * fRec13[0]))))))))) / fTemp0);
		fVec0[0] = fTemp3;
		fRec11[0] = ((fConst70 * fRec11[1]) + (fConst69 * (fVec0[0] + fVec0[1])));
		fRec10[0] = (fRec11[0] - (fConst5 * ((fConst4 * fRec10[2]) + (fConst2 * fRec10[1]))));
		fRec15[0] = ((fConst74 * fRec15[1]) + (fConst73 * (fRec9[1] + fRec9[2])));
		fRec9[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec15[0] + (fConst5 * (fRec10[2] + (fRec10[0] + (2 * fRec10[1]))))) - 3.571981)) - 117.70440740740739);
		fRec8[0] = ((fConst79 * fRec8[1]) + (fConst78 * ((fConst75 * fRec9[0]) + (fConst76 * fRec9[1]))));
		fRec7[0] = ((fConst70 * fRec7[1]) + (fConst80 * (fRec8[0] + fRec8[1])));
		fRec6[0] = (fRec7[0] - (fConst5 * ((fConst4 * fRec6[2]) + (fConst2 * fRec6[1]))));
		fRec16[0] = ((fConst74 * fRec16[1]) + (fConst73 * (fRec5[1] + fRec5[2])));
		fRec5[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec16[0] + (fConst5 * (fRec6[2] + (fRec6[0] + (2 * fRec6[1]))))) - 3.571981)) - 117.70440740740739);
		fRec4[0] = ((fConst79 * fRec4[1]) + (fConst78 * ((fConst75 * fRec5[0]) + (fConst76 * fRec5[1]))));
		fRec3[0] = ((fConst70 * fRec3[1]) + (fConst80 * (fRec4[0] + fRec4[1])));
		fRec2[0] = (fRec3[0] - (fConst5 * ((fConst4 * fRec2[2]) + (fConst2 * fRec2[1]))));
		fRec17[0] = ((fConst74 * fRec17[1]) + (fConst73 * (fRec1[1] + fRec1[2])));
		fRec1[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec17[0] + (fConst5 * (fRec2[2] + (fRec2[0] + (2 * fRec2[1]))))) - 3.571981)) - 117.70440740740739);
		fRec0[0] = ((fConst79 * fRec0[1]) + (fConst78 * ((fConst75 * fRec1[0]) + (fConst76 * fRec1[1]))));
		output0[i] = (FAUSTFLOAT)fRec0[0];
		// post processing
		fRec0[1] = fRec0[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec17[1] = fRec17[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec16[1] = fRec16[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec15[1] = fRec15[0];
		fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		fVec0[1] = fVec0[0];
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
