// generated from file '../src/LV2/faust/fuzzface.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)

#include "trany.h"

namespace fuzzface {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec12[2];
	double 	fConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
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
	double 	fRec14[6];
	double 	fConst33;
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
	double 	fVec0[2];
	double 	fConst56;
	double 	fRec11[2];
	double 	fRec10[3];
	double 	fConst57;
	double 	fConst58;
	double 	fConst59;
	double 	fConst60;
	double 	fRec15[2];
	double 	fRec9[3];
	double 	fConst61;
	double 	fConst62;
	double 	fConst63;
	double 	fConst64;
	double 	fConst65;
	double 	fRec8[2];
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
	fConst0 = min(1.92e+05, max(1.0, (double)fSamplingFreq));
	fConst1 = double(fConst0);
	fConst2 = (3.73292075290073e-29 * fConst1);
	fConst3 = ((fConst1 * ((fConst1 * ((fConst1 * (0 - (1.05633134620746e-20 + fConst2))) - 3.11506369039915e-14)) - 2.30719916990074e-11)) - 1.07493164710329e-09);
	fConst4 = (1.07449105454163e-09 + (fConst1 * (2.29636966370042e-11 + (fConst1 * (2.91602352831988e-14 + (fConst1 * (1.01643277726662e-20 + fConst2)))))));
	fConst5 = (3.98985774247549e-22 * fConst1);
	fConst6 = (5.31230624730483e-11 + (fConst1 * (1.83615604104971e-13 + (fConst1 * (1.99042653510896e-15 + fConst5)))));
	fConst7 = (4.76991513499346e-20 * fConst1);
	fConst8 = (5.00346713698171e-13 + fConst7);
	fConst9 = (0 - fConst8);
	fConst10 = (fConst7 - 5.38351707988916e-15);
	fConst11 = (5.38351707988916e-15 - fConst7);
	fConst12 = (5.05730339185222e-13 * fConst1);
	fConst13 = (fConst12 - 1.16162215422261e-12);
	fConst14 = (1.07493164710329e-09 + (fConst1 * ((fConst1 * (3.11506369039915e-14 + (fConst1 * (fConst2 - 1.05633134620746e-20)))) - 2.30719916990074e-11)));
	fConst15 = ((fConst1 * (2.29636966370042e-11 + (fConst1 * ((fConst1 * (1.01643277726662e-20 - fConst2)) - 2.91602352831988e-14)))) - 1.07449105454163e-09);
	fConst16 = ((fConst1 * (1.83615604104971e-13 + (fConst1 * (fConst5 - 1.99042653510896e-15)))) - 5.31230624730483e-11);
	fConst17 = (1.86646037645036e-28 * fConst1);
	fConst18 = (3.22479494130986e-09 + (fConst1 * ((fConst1 * ((fConst1 * (3.16899403862238e-20 - fConst17)) - 3.11506369039915e-14)) - 2.30719916990074e-11)));
	fConst19 = ((fConst1 * (2.29636966370042e-11 + (fConst1 * (2.91602352831988e-14 + (fConst1 * (fConst17 - 3.04929833179984e-20)))))) - 3.22347316362488e-09);
	fConst20 = (1.19695732274265e-21 * fConst1);
	fConst21 = ((fConst1 * (1.83615604104971e-13 + (fConst1 * (1.99042653510896e-15 - fConst20)))) - 1.59369187419145e-10);
	fConst22 = (3.73292075290073e-28 * fConst1);
	fConst23 = (2.14986329420657e-09 + (fConst1 * (4.61439833980148e-11 + (fConst1 * ((fConst1 * (fConst22 - 2.11266269241492e-20)) - 6.2301273807983e-14)))));
	fConst24 = ((fConst1 * ((fConst1 * (5.83204705663976e-14 + (fConst1 * (2.03286555453323e-20 - fConst22)))) - 4.59273932740084e-11)) - 2.14898210908325e-09);
	fConst25 = (7.97971548495099e-22 * fConst1);
	fConst26 = ((fConst1 * ((fConst1 * (3.98085307021793e-15 + fConst25)) - 3.67231208209942e-13)) - 1.06246124946097e-10);
	fConst27 = ((fConst1 * (4.61439833980148e-11 + (fConst1 * (6.2301273807983e-14 + (fConst1 * (0 - (2.11266269241492e-20 + fConst22))))))) - 2.14986329420657e-09);
	fConst28 = (2.14898210908325e-09 + (fConst1 * ((fConst1 * ((fConst1 * (2.03286555453323e-20 + fConst22)) - 5.83204705663976e-14)) - 4.59273932740084e-11)));
	fConst29 = (1.06246124946097e-10 + (fConst1 * ((fConst1 * (fConst25 - 3.98085307021793e-15)) - 3.67231208209942e-13)));
	fConst30 = ((fConst1 * ((fConst1 * (3.11506369039915e-14 + (fConst1 * (3.16899403862238e-20 + fConst17)))) - 2.30719916990074e-11)) - 3.22479494130986e-09);
	fConst31 = (3.22347316362488e-09 + (fConst1 * (2.29636966370042e-11 + (fConst1 * ((fConst1 * (0 - (3.04929833179984e-20 + fConst17))) - 2.91602352831988e-14)))));
	fConst32 = (1.59369187419145e-10 + (fConst1 * (1.83615604104971e-13 + (fConst1 * (0 - (1.99042653510896e-15 + fConst20))))));
	fConst33 = (1.43097454049804e-19 * fConst1);
	fConst34 = (5.00346713698171e-13 + fConst33);
	fConst35 = (5.38351707988916e-15 - fConst33);
	fConst36 = (fConst33 - 5.38351707988916e-15);
	fConst37 = (0 - (1.16162215422261e-12 + fConst12));
	fConst38 = (9.53983026998693e-20 * fConst1);
	fConst39 = (1.07670341597783e-14 + fConst38);
	fConst40 = (1.00069342739634e-12 - fConst38);
	fConst41 = (fConst38 - 1.00069342739634e-12);
	fConst42 = (1.01146067837044e-12 * fConst1);
	fConst43 = (2.32324430844522e-12 - fConst42);
	fConst44 = (1.00069342739634e-12 + fConst38);
	fConst45 = (0 - fConst44);
	fConst46 = (fConst38 - 1.07670341597783e-14);
	fConst47 = (1.07670341597783e-14 - fConst38);
	fConst48 = (2.32324430844522e-12 + fConst42);
	fConst49 = (fConst33 - 5.00346713698171e-13);
	fConst50 = (5.38351707988916e-15 + fConst33);
	fConst51 = (0 - fConst50);
	fConst52 = (5.00346713698171e-13 - fConst33);
	fConst53 = (5.38351707988916e-15 + fConst7);
	fConst54 = (5.00346713698171e-13 - fConst7);
	fConst55 = (fConst7 - 5.00346713698171e-13);
	fConst56 = (0.9302847925323914 * faustpower<2>(fConst1));
	fConst57 = (1.0 / tan((270.1769682087222 / fConst0)));
	fConst58 = (1 + fConst57);
	fConst59 = (0 - ((1 - fConst57) / fConst58));
	fConst60 = (0.027 / fConst58);
	fConst61 = (1.0 / tan((97.38937226128358 / fConst0)));
	fConst62 = (0 - fConst61);
	fConst63 = (1 + fConst61);
	fConst64 = (0.025 / fConst63);
	fConst65 = (0 - ((1 - fConst61) / fConst63));
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
		fRec12[0] = (fSlow0 + (0.993 * fRec12[1]));
		double fTemp0 = (2.44402781742033e-09 + (fConst1 * (fConst6 + (fRec12[0] * (fConst4 + (fConst3 * fRec12[0]))))));
		fRec13[0] = (fSlow1 + (0.993 * fRec13[1]));
		double fTemp1 = (fConst13 * fRec13[0]);
		fRec14[0] = ((double)input0[i] - ((((((fRec14[1] * (1.22201390871017e-08 + (fConst1 * (fConst32 + (fRec12[0] * (fConst31 + (fConst30 * fRec12[0]))))))) + (fRec14[2] * (2.44402781742033e-08 + (fConst1 * (fConst29 + (fRec12[0] * (fConst28 + (fConst27 * fRec12[0])))))))) + (fRec14[3] * (2.44402781742033e-08 + (fConst1 * (fConst26 + (fRec12[0] * (fConst24 + (fConst23 * fRec12[0])))))))) + (fRec14[4] * (1.22201390871017e-08 + (fConst1 * (fConst21 + (fRec12[0] * (fConst19 + (fConst18 * fRec12[0])))))))) + (fRec14[5] * (2.44402781742033e-09 + (fConst1 * (fConst16 + (fRec12[0] * (fConst15 + (fConst14 * fRec12[0])))))))) / fTemp0));
		double fTemp2 = (fConst37 * fRec13[0]);
		double fTemp3 = (((((((fRec14[0] * (1.16162215422261e-12 + (fTemp2 + (fConst1 * (5.05730339185222e-13 + (fRec12[0] * (fConst55 + ((fConst54 * fRec13[0]) + (fRec12[0] * ((fConst53 * fRec13[0]) - fConst53)))))))))) + (fRec14[1] * (1.16162215422261e-12 + (fTemp1 + (fConst1 * ((fRec12[0] * (fConst52 + ((fRec12[0] * (fConst50 + (fConst51 * fRec13[0]))) + (fConst49 * fRec13[0])))) - 5.05730339185222e-13)))))) + (fRec14[2] * (((fConst48 * fRec13[0]) + (fConst1 * ((fRec12[0] * (fConst44 + ((fRec12[0] * (fConst47 + (fConst46 * fRec13[0]))) + (fConst45 * fRec13[0])))) - 1.01146067837044e-12))) - 2.32324430844522e-12))) + (fRec14[3] * (((fConst43 * fRec13[0]) + (fConst1 * (1.01146067837044e-12 + (fRec12[0] * (fConst41 + ((fConst40 * fRec13[0]) + (fRec12[0] * ((fConst39 * fRec13[0]) - fConst39)))))))) - 2.32324430844522e-12))) + (fRec14[4] * (1.16162215422261e-12 + (fTemp2 + (fConst1 * (5.05730339185222e-13 + (fRec12[0] * (((fRec12[0] * (fConst36 + (fConst35 * fRec13[0]))) + (fConst34 * fRec13[0])) - fConst34)))))))) + (fRec14[5] * (1.16162215422261e-12 + (fTemp1 + (fConst1 * ((fRec12[0] * (fConst8 + ((fRec12[0] * (fConst11 + (fConst10 * fRec13[0]))) + (fConst9 * fRec13[0])))) - 5.05730339185222e-13)))))) / fTemp0);
		fVec0[0] = fTemp3;
		fRec11[0] = ((fConst56 * (fVec0[0] + fVec0[1])) - (0.8605695850647829 * fRec11[1]));
		fRec10[0] = (fRec11[0] - ((1.8405051250752198 * fRec10[1]) + (0.8612942439318627 * fRec10[2])));
		fRec15[0] = ((fConst60 * (fRec9[1] + fRec9[2])) + (fConst59 * fRec15[1]));
		fRec9[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec15[0] + (0.9254498422517706 * (fRec10[0] + (fRec10[2] + (2.0 * fRec10[1]))))) - 3.571981)) - 117.70440740740739);
		fRec8[0] = ((fConst65 * fRec8[1]) + (fConst64 * ((fConst61 * fRec9[0]) + (fConst62 * fRec9[1]))));
		fRec7[0] = ((0.9302847925323914 * (fRec8[1] + fRec8[0])) - (0.8605695850647829 * fRec7[1]));
		fRec6[0] = (fRec7[0] - ((1.8405051250752198 * fRec6[1]) + (0.8612942439318627 * fRec6[2])));
		fRec16[0] = ((fConst60 * (fRec5[1] + fRec5[2])) + (fConst59 * fRec16[1]));
		fRec5[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec16[0] + (0.9254498422517706 * (fRec6[0] + (fRec6[2] + (2.0 * fRec6[1]))))) - 3.571981)) - 117.70440740740739);
		fRec4[0] = ((fConst65 * fRec4[1]) + (fConst64 * ((fConst61 * fRec5[0]) + (fConst62 * fRec5[1]))));
		fRec3[0] = ((0.9302847925323914 * (fRec4[1] + fRec4[0])) - (0.8605695850647829 * fRec3[1]));
		fRec2[0] = (fRec3[0] - ((1.8405051250752198 * fRec2[1]) + (0.8612942439318627 * fRec2[2])));
		fRec17[0] = ((fConst60 * (fRec1[1] + fRec1[2])) + (fConst59 * fRec17[1]));
		fRec1[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec17[0] + (0.9254498422517706 * (fRec2[0] + (fRec2[2] + (2.0 * fRec2[1]))))) - 3.571981)) - 117.70440740740739);
		fRec0[0] = ((fConst65 * fRec0[1]) + (fConst64 * ((fConst61 * fRec1[0]) + (fConst62 * fRec1[1]))));
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
