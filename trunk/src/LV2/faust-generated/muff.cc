// generated from file '../src/LV2/faust/muff.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


#include "trany.h"

namespace muff {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst4;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec1[2];
	double fConst6;
	double fConst8;
	double fConst10;
	double fConst12;
	double fConst14;
	double fConst15;
	double fConst16;
	double fConst17;
	double fConst18;
	double fConst19;
	double fConst20;
	double fConst21;
	double fConst22;
	double fConst23;
	double fConst25;
	double fConst27;
	double fConst29;
	double fConst30;
	double fConst31;
	double fConst32;
	double fRec0[7];
	double fConst34;
	double fConst36;
	double fConst38;
	double fConst40;
	double fConst42;
	double fConst44;
	double fConst46;
	double fConst48;
	double fConst50;
	double fConst52;
	double fConst54;
	double fConst56;
	double fConst57;
	double fConst58;
	double fConst59;
	double fConst60;
	double fConst61;
	double fConst62;
	double fConst63;
	double fConst64;
	double fConst65;
	double fConst66;
	double fConst67;
	double fConst68;
	double fConst69;
	double fConst70;


	gx_resample::FixedRateResampler smpCl;
	double fConstCl4;
	double fVecCl0[2];
	double fRecCl7[2];
	double fRecCl6[3];
	double fConstCl6;
	double fConstCl7;
	double fRecCl8[2];
	double fRecCl5[3];
	double fConstCl8;
	double fConstCl9;
	double fRecCl4[2];
	double fRecCl3[2];
	double fRecCl2[3];
	double fRecCl9[2];
	double fRecCl1[3];
	double fRecCl0[2];

	FAUSTFLOAT 	fsliderV0;
	FAUSTFLOAT 	*fsliderV0_;
	double 	fRecV0[2];
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
	id = "muff";
	name = N_("Muff");
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
	for (int l1 = 0; l1 < 7; l1 = l1 + 1) fRec0[l1] = 0.0;

	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fVecCl0[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRecCl7[l1] = 0.0;
	for (int l2 = 0; l2 < 3; l2 = l2 + 1) fRecCl6[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRecCl8[l3] = 0.0;
	for (int l4 = 0; l4 < 3; l4 = l4 + 1) fRecCl5[l4] = 0.0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fRecCl4[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fRecCl3[l6] = 0.0;
	for (int l7 = 0; l7 < 3; l7 = l7 + 1) fRecCl2[l7] = 0.0;
	for (int l8 = 0; l8 < 2; l8 = l8 + 1) fRecCl9[l8] = 0.0;
	for (int l9 = 0; l9 < 3; l9 = l9 + 1) fRecCl1[l9] = 0.0;
	for (int l10 = 0; l10 < 2; l10 = l10 + 1) fRecCl0[l10] = 0.0;

	for (int i=0; i<2; i++) fRecV0[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = mydsp_faustpower3_f(fConst0);
	fConst2 = mydsp_faustpower2_f(fConst0);
	double fConst3 = 2.7851760796571602e-28 * fConst0;
	fConst4 = fConst0 * (fConst2 * (fConst0 * (-2.8456362099361602e-24 - fConst3) + -5.7449031067776799e-21) + 1.7873506178573599e-15) + 4.6689455809719503e-14;
	double fConst5 = 3.4639059102254199e-28 * fConst0;
	fConst6 = fConst0 * (fConst2 * (fConst0 * (-3.16596879216081e-24 - fConst5) + -5.1546194630173903e-21) + 1.04341801802983e-15) + 1.33311386991013e-14;
	double fConst7 = 3.45271544966819e-28 * fConst0;
	fConst8 = fConst0 * (fConst2 * (fConst0 * (fConst7 + 2.9098764967631799e-24) + 4.7352385930117798e-21) + -1.0677842484623401e-15) + -1.36274545645413e-14;
	double fConst9 = 6.9629401991428898e-28 * fConst0;
	fConst10 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst9 + 3.5570452624201997e-24) + -2.8724515533888399e-21) + -1.0816319464054301e-17) + -8.9367530892868194e-16) + 5.8361819762149404e-14;
	double fConst11 = 8.65976477556356e-28 * fConst0;
	fConst12 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst11 + 3.9574609902010099e-24) + -2.5773097315087e-21) + -6.0715727703843699e-18) + -5.2170900901491599e-16) + 1.66639233738767e-14;
	double fConst13 = 8.6317886241704708e-28 * fConst0;
	fConst14 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (-3.6373456209539698e-24 - fConst13) + 2.3676192965058899e-21) + 6.46996146702087e-18) + 5.3389212423117004e-16) + -1.7034318205676599e-14;
	fConst15 = fConst2 * (1.14898062135554e-20 - 9.2839202655238596e-28 * fConst2) + -3.5747012357147301e-15;
	fConst16 = fConst2 * (1.03092389260348e-20 - 1.1546353034084701e-27 * fConst2) + -2.0868360360596699e-15;
	fConst17 = fConst2 * (1.1509051498894e-27 * fConst2 + -9.4704771860235596e-21) + 2.1355684969246802e-15;
	fConst18 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst9 + -3.5570452624201997e-24) + -2.8724515533888399e-21) + 1.0816319464054301e-17) + -8.9367530892868194e-16) + -5.8361819762149404e-14;
	fConst19 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst11 + -3.9574609902010099e-24) + -2.5773097315087e-21) + 6.0715727703843699e-18) + -5.2170900901491599e-16) + -1.66639233738767e-14;
	fConst20 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (3.6373456209539698e-24 - fConst13) + 2.3676192965058899e-21) + -6.46996146702087e-18) + 5.3389212423117004e-16) + 1.7034318205676599e-14;
	fConst21 = fConst0 * (fConst2 * (fConst0 * (2.8456362099361602e-24 - fConst3) + -5.7449031067776799e-21) + 1.7873506178573599e-15) + -4.6689455809719503e-14;
	fConst22 = fConst0 * (fConst2 * (fConst0 * (3.16596879216081e-24 - fConst5) + -5.1546194630173903e-21) + 1.04341801802983e-15) + -1.33311386991013e-14;
	fConst23 = fConst0 * (fConst2 * (fConst0 * (fConst7 + -2.9098764967631799e-24) + 4.7352385930117798e-21) + -1.0677842484623401e-15) + 1.36274545645413e-14;
	double fConst24 = 4.6419601327619301e-29 * fConst0;
	fConst25 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst24 + -7.1140905248404004e-25) + 2.8724515533888399e-21) + -3.60543982135142e-18) + 8.9367530892868194e-16) + -1.1672363952429899e-14;
	double fConst26 = 5.7731765170423698e-29 * fConst0;
	fConst27 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst26 + -7.9149219804020196e-25) + 2.5773097315087e-21) + -2.02385759012812e-18) + 5.2170900901491599e-16) + -3.3327846747753399e-15;
	double fConst28 = 5.75452574944698e-29 * fConst0;
	fConst29 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (7.2746912419079497e-25 - fConst28) + -2.3676192965058899e-21) + 2.15665382234029e-18) + -5.3389212423117004e-16) + 3.4068636411353101e-15;
	fConst30 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst24 + 7.1140905248404004e-25) + 2.8724515533888399e-21) + 3.60543982135142e-18) + 8.9367530892868194e-16) + 1.1672363952429899e-14;
	fConst31 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst26 + 7.9149219804020196e-25) + 2.5773097315087e-21) + 2.02385759012812e-18) + 5.2170900901491599e-16) + 3.3327846747753399e-15;
	fConst32 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (-7.2746912419079497e-25 - fConst28) + -2.3676192965058899e-21) + -2.15665382234029e-18) + -5.3389212423117004e-16) + -3.4068636411353101e-15;
	double fConst33 = 3.0563518352926499e-28 * fConst0;
	fConst34 = fConst0 * (8.7623352804900498e-22 - fConst33) + 4.0631875266228199e-18;
	double fConst35 = 1.3892508342239301e-26 * fConst0;
	fConst36 = fConst0 * (3.9828796729500198e-20 - fConst35) + 1.84690342119219e-16;
	double fConst37 = 5.9070507911883799e-30 * fConst0;
	fConst38 = fConst0 * (fConst0 * (1.6962426381721e-23 - fConst37) + 5.0643439567801602e-23) + -1.4542546623560601e-16;
	double fConst39 = 1.29955117406144e-31 * fConst0;
	fConst40 = fConst0 * (fConst0 * (3.73173380397863e-25 - fConst39) + 1.11415567049164e-24) + -3.1993602571833199e-18;
	double fConst41 = 1.22254073411706e-27 * fConst0;
	fConst42 = fConst41 + -1.75246705609801e-21;
	double fConst43 = 5.5570033368957295e-26 * fConst0;
	fConst44 = fConst43 + -7.9657593459000504e-20;
	double fConst45 = 3.5442304747130299e-29 * fConst0;
	fConst46 = fConst0 * (fConst45 + -6.7849705526884201e-23) + -1.01286879135603e-22;
	double fConst47 = 7.79730704436866e-31 * fConst0;
	fConst48 = fConst0 * (fConst47 + -1.49269352159145e-24) + -2.22831134098327e-24;
	double fConst49 = 1.5281759176463301e-27 * fConst0;
	fConst50 = fConst0 * (-8.7623352804900498e-22 - fConst49) + -1.21895625798685e-17;
	double fConst51 = 6.9462541711196704e-26 * fConst0;
	fConst52 = fConst0 * (-3.9828796729500198e-20 - fConst51) + -5.5407102635765798e-16;
	double fConst53 = 8.86057618678257e-29 * fConst0;
	fConst54 = fConst0 * (fConst0 * (8.4812131908605201e-23 - fConst53) + -5.0643439567801602e-23) + 4.3627639870681698e-16;
	double fConst55 = 1.9493267610921598e-30 * fConst0;
	fConst56 = fConst0 * (fConst0 * (1.86586690198932e-24 - fConst55) + -1.11415567049164e-24) + 9.5980807715499693e-18;
	fConst57 = 1.18141015823768e-28 * fConst2 + 2.0257375827120601e-22;
	fConst58 = 2.5991023481228902e-30 * fConst2 + 4.45662268196654e-24;
	fConst59 = fConst0 * (fConst49 + -8.7623352804900498e-22) + 1.21895625798685e-17;
	fConst60 = fConst0 * (fConst51 + -3.9828796729500198e-20) + 5.5407102635765798e-16;
	fConst61 = fConst0 * (fConst0 * (-8.4812131908605201e-23 - fConst53) + -5.0643439567801602e-23) + -4.3627639870681698e-16;
	fConst62 = fConst0 * (fConst0 * (-1.86586690198932e-24 - fConst55) + -1.11415567049164e-24) + -9.5980807715499693e-18;
	fConst63 = -1.75246705609801e-21 - fConst41;
	fConst64 = -7.9657593459000504e-20 - fConst43;
	fConst65 = fConst0 * (fConst45 + 6.7849705526884201e-23) + -1.01286879135603e-22;
	fConst66 = fConst0 * (fConst47 + 1.49269352159145e-24) + -2.22831134098327e-24;
	fConst67 = fConst0 * (fConst33 + 8.7623352804900498e-22) + -4.0631875266228199e-18;
	fConst68 = fConst0 * (fConst35 + 3.9828796729500198e-20) + -1.84690342119219e-16;
	fConst69 = fConst0 * (fConst0 * (-1.6962426381721e-23 - fConst37) + 5.0643439567801602e-23) + 1.4542546623560601e-16;
	fConst70 = fConst0 * (fConst0 * (-3.73173380397863e-25 - fConst39) + 1.11415567049164e-24) + 3.1993602571833199e-18;

	sample_rate = 96000;
	smpCl.setup(fSampleRate, sample_rate);
	fSampleRate = sample_rate;
	double fConstCl0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	double fConstCl1 = std::tan(97.389372261283583 / fConstCl0);
	double fConstCl2 = 1.0 / fConstCl1;
	double fConstCl3 = fConstCl2 + 1.0;
	fConstCl4 = 1.0 / (fConstCl1 * fConstCl3);
	double fConstCl5 = 1.0 / std::tan(270.1769682087222 / fConstCl0);
	fConstCl6 = 1.0 / (fConstCl5 + 1.0);
	fConstCl7 = 1.0 - fConstCl5;
	fConstCl8 = 0.0 - fConstCl4;
	fConstCl9 = (1.0 - fConstCl2) / fConstCl3;

	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fVslider0 (*fVslider0_)
#define fsliderV0 (*fsliderV0_)
	double 	fSlowV0 = (0.0010000000000000009 * double(fsliderV0));

	double fSlow0 = 0.0070000000000000062 * double(fVslider0);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec1[0] = fSlow0 + 0.99299999999999999 * fRec1[1];
		double fTemp0 = fConst0 * (fConst30 + fRec1[0] * (fConst31 + fConst32 * fRec1[0])) + 3.9122418924326203e-14;
		fRec0[0] = double(input0[i0]) - (fRec0[1] * (fConst0 * (fConst4 + fRec1[0] * (fConst6 + fConst8 * fRec1[0])) + 2.3473451354595699e-13) + fRec0[2] * (fConst0 * (fConst10 + fRec1[0] * (fConst12 + fConst14 * fRec1[0])) + 5.8683628386489202e-13) + fRec0[3] * (fConst2 * (fConst15 + fRec1[0] * (fConst16 + fConst17 * fRec1[0])) + 7.82448378486523e-13) + fRec0[4] * (fConst0 * (fConst18 + fRec1[0] * (fConst19 + fConst20 * fRec1[0])) + 5.8683628386489202e-13) + fRec0[5] * (fConst0 * (fConst21 + fRec1[0] * (fConst22 + fConst23 * fRec1[0])) + 2.3473451354595699e-13) + fRec0[6] * (fConst0 * (fConst25 + fRec1[0] * (fConst27 + fConst29 * fRec1[0])) + 3.9122418924326203e-14)) / fTemp0;
		output0[i0] = FAUSTFLOAT(fConst1 * (fRec0[0] * (fConst34 + fConst36 + fConst38 * fRec1[0] + fConst40 * fRec1[0]) + fConst0 * fRec0[1] * (fConst42 + fConst44 + fConst46 * fRec1[0] + fConst48 * fRec1[0]) + fRec0[2] * (fConst50 + fConst52 + fConst54 * fRec1[0] + fConst56 * fRec1[0]) + fConst0 * fRec0[3] * (fConst57 * fRec1[0] + 1.5931518691800101e-19 + fConst58 * fRec1[0] + 3.5049341121960199e-21) + fRec0[4] * (fConst59 + fConst60 + fConst61 * fRec1[0] + fConst62 * fRec1[0]) + fConst0 * fRec0[5] * (fConst63 + fConst64 + fConst65 * fRec1[0] + fConst66 * fRec1[0]) + fRec0[6] * (fConst67 + fConst68 + fConst69 * fRec1[0] + fConst70 * fRec1[0])) / fTemp0);
		fRec1[1] = fRec1[0];
		for (int j0 = 6; j0 > 0; j0 = j0 - 1) {
			fRec0[j0] = fRec0[j0 - 1];
		}
	}

	FAUSTFLOAT bufCl[smpCl.max_out_count(count)];
	int ReCount = smpCl.up(count, output0, bufCl);
	for (int i0 = 0; i0 < ReCount; i0 = i0 + 1) {
		double fTemp0 = double(bufCl[i0]);
		fVecCl0[0] = fTemp0;
		fRecCl7[0] = 0.93028479253239138 * (fTemp0 + fVecCl0[1]) - 0.86056958506478287 * fRecCl7[1];
		fRecCl6[0] = fRecCl7[0] - (1.8405051250752198 * fRecCl6[1] + 0.86129424393186271 * fRecCl6[2]);
		fRecCl8[0] = fConstCl6 * (0.027 * (fRecCl5[1] + fRecCl5[2]) - fConstCl7 * fRecCl8[1]);
		fRecCl5[0] = double(Ftrany(int(TRANY_TABLE_7199P_68k), double(0.92544984225177063 * (fRecCl6[0] + fRecCl6[2]) + fRecCl8[0] + 1.8508996845035413 * fRecCl6[1] + -3.5719810000000001))) + -117.70440740740739;
		fRecCl4[0] = 0.025000000000000001 * (fConstCl4 * fRecCl5[0] + fConstCl8 * fRecCl5[1]) - fConstCl9 * fRecCl4[1];
		fRecCl3[0] = 0.93028479253239138 * (fRecCl4[0] + fRecCl4[1]) - 0.86056958506478287 * fRecCl3[1];
		fRecCl2[0] = fRecCl3[0] - (1.8405051250752198 * fRecCl2[1] + 0.86129424393186271 * fRecCl2[2]);
		fRecCl9[0] = fConstCl6 * (0.027 * (fRecCl1[1] + fRecCl1[2]) - fConstCl7 * fRecCl9[1]);
		fRecCl1[0] = double(Ftrany(int(TRANY_TABLE_7199P_68k), double(0.92544984225177063 * (fRecCl2[0] + fRecCl2[2]) + fRecCl9[0] + 1.8508996845035413 * fRecCl2[1] + -3.5719810000000001))) + -117.70440740740739;
		fRecCl0[0] = 0.025000000000000001 * (fConstCl4 * fRecCl1[0] + fConstCl8 * fRecCl1[1]) - fConstCl9 * fRecCl0[1];
		bufCl[i0] = FAUSTFLOAT(fRecCl0[0]);
		fVecCl0[1] = fVecCl0[0];
		fRecCl7[1] = fRecCl7[0];
		fRecCl6[2] = fRecCl6[1];
		fRecCl6[1] = fRecCl6[0];
		fRecCl8[1] = fRecCl8[0];
		fRecCl5[2] = fRecCl5[1];
		fRecCl5[1] = fRecCl5[0];
		fRecCl4[1] = fRecCl4[0];
		fRecCl3[1] = fRecCl3[0];
		fRecCl2[2] = fRecCl2[1];
		fRecCl2[1] = fRecCl2[0];
		fRecCl9[1] = fRecCl9[0];
		fRecCl1[2] = fRecCl1[1];
		fRecCl1[1] = fRecCl1[0];
		fRecCl0[1] = fRecCl0[0];
	}
	smpCl.down(bufCl, output0);

	for (int i=0; i<count; i++) {
		fRecV0[0] = ((0.999 * fRecV0[1]) + fSlowV0);
		output0[i] = (FAUSTFLOAT)((double)output0[i] * fRecV0[0]);
		// post processing
		fRecV0[1] = fRecV0[0];
	}

#undef fsliderV0 
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
	case TONE: 
		fVslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case VOLUME: 
		fsliderV0_ = (float*)data; // , 0.5, 0.0, 1, 0.01 
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
   TONE, 
   VOLUME,
} PortIndex;
*/

} // end namespace muff
