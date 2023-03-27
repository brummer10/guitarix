// generated from file '../src/LV2/faust/fuzzface.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "trany.h"

namespace fuzzface {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec12[2];
	double fConst0;
	double fConst2;
	double fConst3;
	double fConst5;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec13[2];
	double fConst7;
	double fConst8;
	double fConst9;
	double fConst10;
	double fConst11;
	double fConst13;
	double fConst14;
	double fConst15;
	double fConst16;
	double fConst17;
	double fConst18;
	double fConst20;
	double fConst21;
	double fConst23;
	double fConst25;
	double fConst26;
	double fConst28;
	double fConst29;
	double fConst30;
	double fConst31;
	double fConst32;
	double fConst33;
	double fConst34;
	double fRec14[6];
	double fConst36;
	double fConst37;
	double fConst38;
	double fConst39;
	double fConst40;
	double fConst41;
	double fConst43;
	double fConst44;
	double fConst46;
	double fConst47;
	double fConst48;
	double fConst49;
	double fConst50;
	double fConst51;
	double fConst52;
	double fConst53;
	double fConst54;
	double fConst55;
	double fConst56;
	double fConst57;
	double fConst58;
	double fConst59;
	double fConst60;
	double fConst61;
	double fConst62;
	double fConst63;
	double fVec0[2];
	double fRec11[2];
	double fRec10[3];
	double fRec9[2];
	double fConst65;
	double fConst66;
	double fRec8[2];
	double fRec7[2];
	double fRec6[3];
	double fRec5[2];
	double fRec4[2];
	double fRec3[2];
	double fRec2[3];
	double fRec1[2];
	double fRec0[2];

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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec12[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec13[l1] = 0.0;
	for (int l2 = 0; l2 < 6; l2 = l2 + 1) fRec14[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fVec0[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fRec11[l4] = 0.0;
	for (int l5 = 0; l5 < 3; l5 = l5 + 1) fRec10[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fRec9[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec8[l7] = 0.0;
	for (int l8 = 0; l8 < 2; l8 = l8 + 1) fRec7[l8] = 0.0;
	for (int l9 = 0; l9 < 3; l9 = l9 + 1) fRec6[l9] = 0.0;
	for (int l10 = 0; l10 < 2; l10 = l10 + 1) fRec5[l10] = 0.0;
	for (int l11 = 0; l11 < 2; l11 = l11 + 1) fRec4[l11] = 0.0;
	for (int l12 = 0; l12 < 2; l12 = l12 + 1) fRec3[l12] = 0.0;
	for (int l13 = 0; l13 < 3; l13 = l13 + 1) fRec2[l13] = 0.0;
	for (int l14 = 0; l14 < 2; l14 = l14 + 1) fRec1[l14] = 0.0;
	for (int l15 = 0; l15 < 2; l15 = l15 + 1) fRec0[l15] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = 3.73292075290073e-29 * fConst0;
	fConst2 = fConst0 * (fConst0 * (fConst0 * (-1.05633134620746e-20 - fConst1) + -3.11506369039915e-14) + -2.30719916990074e-11) + -1.07493164710329e-09;
	fConst3 = fConst0 * (fConst0 * (fConst0 * (fConst1 + 1.01643277726662e-20) + 2.91602352831988e-14) + 2.29636966370042e-11) + 1.07449105454163e-09;
	double fConst4 = 3.98985774247549e-22 * fConst0;
	fConst5 = fConst0 * (fConst0 * (fConst4 + 1.99042653510896e-15) + 1.83615604104971e-13) + 5.31230624730483e-11;
	double fConst6 = 4.76991513499346e-20 * fConst0;
	fConst7 = -5.00346713698171e-13 - fConst6;
	fConst8 = fConst6 + -5.38351707988916e-15;
	fConst9 = 5.38351707988916e-15 - fConst6;
	fConst10 = fConst6 + 5.00346713698171e-13;
	fConst11 = mydsp_faustpower3_f(fConst0);
	double fConst12 = 5.05730339185222e-13 * fConst0;
	fConst13 = fConst12 + -1.16162215422261e-12;
	fConst14 = 1.16162215422261e-12 - fConst12;
	fConst15 = mydsp_faustpower2_f(fConst0);
	fConst16 = fConst0 * (fConst0 * (fConst0 * (fConst1 + -1.05633134620746e-20) + 3.11506369039915e-14) + -2.30719916990074e-11) + 1.07493164710329e-09;
	fConst17 = fConst0 * (fConst0 * (fConst0 * (1.01643277726662e-20 - fConst1) + -2.91602352831988e-14) + 2.29636966370042e-11) + -1.07449105454163e-09;
	fConst18 = fConst0 * (fConst0 * (fConst4 + -1.99042653510896e-15) + 1.83615604104971e-13) + -5.31230624730483e-11;
	double fConst19 = 1.86646037645036e-28 * fConst0;
	fConst20 = fConst0 * (fConst0 * (fConst0 * (3.16899403862238e-20 - fConst19) + -3.11506369039915e-14) + -2.30719916990074e-11) + 3.22479494130986e-09;
	fConst21 = fConst0 * (fConst0 * (fConst0 * (fConst19 + -3.04929833179984e-20) + 2.91602352831988e-14) + 2.29636966370042e-11) + -3.22347316362488e-09;
	double fConst22 = 1.19695732274265e-21 * fConst0;
	fConst23 = fConst0 * (fConst0 * (1.99042653510896e-15 - fConst22) + 1.83615604104971e-13) + -1.59369187419145e-10;
	double fConst24 = 3.73292075290073e-28 * fConst0;
	fConst25 = fConst0 * (fConst0 * (fConst0 * (fConst24 + -2.11266269241492e-20) + -6.2301273807983e-14) + 4.61439833980148e-11) + 2.14986329420657e-09;
	fConst26 = fConst0 * (fConst0 * (fConst0 * (2.03286555453323e-20 - fConst24) + 5.83204705663976e-14) + -4.59273932740084e-11) + -2.14898210908325e-09;
	double fConst27 = 7.97971548495099e-22 * fConst0;
	fConst28 = fConst0 * (fConst0 * (fConst27 + 3.98085307021793e-15) + -3.67231208209942e-13) + -1.06246124946097e-10;
	fConst29 = fConst0 * (fConst0 * (fConst0 * (-2.11266269241492e-20 - fConst24) + 6.2301273807983e-14) + 4.61439833980148e-11) + -2.14986329420657e-09;
	fConst30 = fConst0 * (fConst0 * (fConst0 * (fConst24 + 2.03286555453323e-20) + -5.83204705663976e-14) + -4.59273932740084e-11) + 2.14898210908325e-09;
	fConst31 = fConst0 * (fConst0 * (fConst27 + -3.98085307021793e-15) + -3.67231208209942e-13) + 1.06246124946097e-10;
	fConst32 = fConst0 * (fConst0 * (fConst0 * (fConst19 + 3.16899403862238e-20) + 3.11506369039915e-14) + -2.30719916990074e-11) + -3.22479494130986e-09;
	fConst33 = fConst0 * (fConst0 * (fConst0 * (-3.04929833179984e-20 - fConst19) + -2.91602352831988e-14) + 2.29636966370042e-11) + 3.22347316362488e-09;
	fConst34 = fConst0 * (fConst0 * (-1.99042653510896e-15 - fConst22) + 1.83615604104971e-13) + 1.59369187419145e-10;
	double fConst35 = 1.43097454049804e-19 * fConst0;
	fConst36 = fConst35 + 5.00346713698171e-13;
	fConst37 = 5.38351707988916e-15 - fConst35;
	fConst38 = fConst35 + -5.38351707988916e-15;
	fConst39 = -5.00346713698171e-13 - fConst35;
	fConst40 = -1.16162215422261e-12 - fConst12;
	fConst41 = fConst12 + 1.16162215422261e-12;
	double fConst42 = 1.01146067837044e-12 * fConst0;
	fConst43 = 2.32324430844522e-12 - fConst42;
	fConst44 = fConst42 + -2.32324430844522e-12;
	double fConst45 = 9.53983026998693e-20 * fConst0;
	fConst46 = 1.00069342739634e-12 - fConst45;
	fConst47 = fConst45 + 1.07670341597783e-14;
	fConst48 = -1.07670341597783e-14 - fConst45;
	fConst49 = fConst45 + -1.00069342739634e-12;
	fConst50 = fConst42 + 2.32324430844522e-12;
	fConst51 = -2.32324430844522e-12 - fConst42;
	fConst52 = -1.00069342739634e-12 - fConst45;
	fConst53 = fConst45 + -1.07670341597783e-14;
	fConst54 = 1.07670341597783e-14 - fConst45;
	fConst55 = fConst45 + 1.00069342739634e-12;
	fConst56 = fConst35 + -5.00346713698171e-13;
	fConst57 = -5.38351707988916e-15 - fConst35;
	fConst58 = fConst35 + 5.38351707988916e-15;
	fConst59 = 5.00346713698171e-13 - fConst35;
	fConst60 = 5.00346713698171e-13 - fConst6;
	fConst61 = fConst6 + 5.38351707988916e-15;
	fConst62 = -5.38351707988916e-15 - fConst6;
	fConst63 = fConst6 + -5.00346713698171e-13;
	double fConst64 = 3.141592653589793 / fConst0;
	fConst65 = 1.0 - fConst64;
	fConst66 = 1.0 / (fConst64 + 1.0);
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
	double fSlow0 = 0.007000000000000006 * (1.0 - double(fVslider0));
	double fSlow1 = 0.007000000000000006 * (1.0 - double(fVslider1));
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec12[0] = fSlow0 + 0.993 * fRec12[1];
		double fTemp0 = fConst0 * (fConst5 + fRec12[0] * (fConst3 + fConst2 * fRec12[0])) + 2.44402781742033e-09;
		fRec13[0] = fSlow1 + 0.993 * fRec13[1];
		double fTemp1 = fConst15 * (fConst14 + fConst13 * fRec13[0]);
		fRec14[0] = double(input0[i0]) - (fRec14[1] * (fConst0 * (fConst34 + fRec12[0] * (fConst33 + fConst32 * fRec12[0])) + 1.22201390871017e-08) + fRec14[2] * (fConst0 * (fConst31 + fRec12[0] * (fConst30 + fConst29 * fRec12[0])) + 2.44402781742033e-08) + fRec14[3] * (fConst0 * (fConst28 + fRec12[0] * (fConst26 + fConst25 * fRec12[0])) + 2.44402781742033e-08) + fRec14[4] * (fConst0 * (fConst23 + fRec12[0] * (fConst21 + fConst20 * fRec12[0])) + 1.22201390871017e-08) + fRec14[5] * (fConst0 * (fConst18 + fRec12[0] * (fConst17 + fConst16 * fRec12[0])) + 2.44402781742033e-09)) / fTemp0;
		double fTemp2 = fConst15 * (fConst41 + fConst40 * fRec13[0]);
		double fTemp3 = (fRec14[0] * (fConst11 * fRec12[0] * (fConst63 + fRec12[0] * (fConst62 + fConst61 * fRec13[0]) + fConst60 * fRec13[0]) + fTemp2) + fRec14[1] * (fConst11 * fRec12[0] * (fConst59 + fRec12[0] * (fConst58 + fConst57 * fRec13[0]) + fConst56 * fRec13[0]) + fTemp1) + fRec14[2] * (fConst11 * fRec12[0] * (fConst55 + fRec12[0] * (fConst54 + fConst53 * fRec13[0]) + fConst52 * fRec13[0]) + fConst15 * (fConst51 + fConst50 * fRec13[0])) + fRec14[3] * (fConst11 * fRec12[0] * (fConst49 + fRec12[0] * (fConst48 + fConst47 * fRec13[0]) + fConst46 * fRec13[0]) + fConst15 * (fConst44 + fConst43 * fRec13[0])) + fRec14[4] * (fTemp2 + fConst11 * fRec12[0] * (fConst39 + fRec12[0] * (fConst38 + fConst37 * fRec13[0]) + fConst36 * fRec13[0])) + fRec14[5] * (fTemp1 + fConst11 * fRec12[0] * (fConst10 + fRec12[0] * (fConst9 + fConst8 * fRec13[0]) + fConst7 * fRec13[0]))) / fTemp0;
		fVec0[0] = fTemp3;
		fRec11[0] = 0.9302847925323914 * (fTemp3 + fVec0[1]) - 0.8605695850647829 * fRec11[1];
		fRec10[0] = fRec11[0] - (1.8405051250752198 * fRec10[1] + 0.8612942439318627 * fRec10[2]);
		double fTemp4 = 1.8508996845035413 * fRec10[1] + 0.9254498422517706 * (fRec10[0] + fRec10[2]);
		double fTemp5 = Ftrany(TRANY_TABLE_7199P_68k, fTemp4 + 2.7e+03 * (fTemp4 / (Rtrany(TRANY_TABLE_7199P_68k, fRec9[1]) + 1e+05)) + -3.571981);
		fRec9[0] = fTemp5 + 0.001322955925925926 * (Rtrany(TRANY_TABLE_7199P_68k, fTemp5) + 1e+05) + -2.5e+02;
		fRec8[0] = fConst66 * (fConst65 * fRec8[1] + 0.025 * (fRec9[0] - fRec9[1]));
		fRec7[0] = 0.9302847925323914 * (fRec8[0] + fRec8[1]) - 0.8605695850647829 * fRec7[1];
		fRec6[0] = fRec7[0] - (1.8405051250752198 * fRec6[1] + 0.8612942439318627 * fRec6[2]);
		double fTemp6 = 1.8508996845035413 * fRec6[1] + 0.9254498422517706 * (fRec6[0] + fRec6[2]);
		double fTemp7 = Ftrany(TRANY_TABLE_7199P_68k, fTemp6 + 2.7e+03 * (fTemp6 / (Rtrany(TRANY_TABLE_7199P_68k, fRec5[1]) + 1e+05)) + -3.571981);
		fRec5[0] = fTemp7 + 0.001322955925925926 * (Rtrany(TRANY_TABLE_7199P_68k, fTemp7) + 1e+05) + -2.5e+02;
		fRec4[0] = fConst66 * (fConst65 * fRec4[1] + 0.025 * (fRec5[0] - fRec5[1]));
		fRec3[0] = 0.9302847925323914 * (fRec4[0] + fRec4[1]) - 0.8605695850647829 * fRec3[1];
		fRec2[0] = fRec3[0] - (1.8405051250752198 * fRec2[1] + 0.8612942439318627 * fRec2[2]);
		double fTemp8 = 1.8508996845035413 * fRec2[1] + 0.9254498422517706 * (fRec2[0] + fRec2[2]);
		double fTemp9 = Ftrany(TRANY_TABLE_7199P_68k, fTemp8 + 2.7e+03 * (fTemp8 / (Rtrany(TRANY_TABLE_7199P_68k, fRec1[1]) + 1e+05)) + -3.571981);
		fRec1[0] = fTemp9 + 0.001322955925925926 * (Rtrany(TRANY_TABLE_7199P_68k, fTemp9) + 1e+05) + -2.5e+02;
		fRec0[0] = fConst66 * (fConst65 * fRec0[1] + 0.025 * (fRec1[0] - fRec1[1]));
		output0[i0] = FAUSTFLOAT(fRec0[0]);
		fRec12[1] = fRec12[0];
		fRec13[1] = fRec13[0];
		for (int j0 = 5; j0 > 0; j0 = j0 - 1) {
			fRec14[j0] = fRec14[j0 - 1];
		}
		fVec0[1] = fVec0[0];
		fRec11[1] = fRec11[0];
		fRec10[2] = fRec10[1];
		fRec10[1] = fRec10[0];
		fRec9[1] = fRec9[0];
		fRec8[1] = fRec8[0];
		fRec7[1] = fRec7[0];
		fRec6[2] = fRec6[1];
		fRec6[1] = fRec6[0];
		fRec5[1] = fRec5[0];
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
	}
#undef fVslider0
#undef fVslider1
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
		fVslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case LEVEL: 
		fVslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
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
