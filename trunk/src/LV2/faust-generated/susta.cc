// generated from file '../src/LV2/faust/susta.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "trany.h"

namespace susta {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec12[2];
	double fConst3;
	double fConst5;
	double fConst7;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec13[2];
	double fConst9;
	double fConst11;
	double fConst13;
	double fConst15;
	double fConst17;
	double fConst19;
	double fConst21;
	double fConst22;
	double fConst23;
	double fConst24;
	double fConst25;
	double fConst26;
	double fConst27;
	double fConst29;
	double fConst31;
	double fConst33;
	double fConst35;
	double fConst37;
	double fConst39;
	double fConst41;
	double fConst43;
	double fConst45;
	double fConst47;
	double fConst49;
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
	double fRec14[6];
	double fConst65;
	double fConst67;
	double fConst69;
	double fConst71;
	double fConst73;
	double fConst75;
	double fConst77;
	double fConst79;
	double fConst80;
	double fConst81;
	double fConst82;
	double fConst83;
	double fConst84;
	double fConst85;
	double fConst86;
	double fConst87;
	double fConst88;
	double fConst89;
	double fConst90;
	double fConst91;
	double fVec0[2];
	double fConst92;
	double fRec11[2];
	double fRec10[3];
	double fRec9[2];
	double fConst94;
	double fConst95;
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
	id = "susta";
	name = N_("Sustainer");
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
	double fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = mydsp_faustpower2_f(fConst0);
	double fConst2 = 5.11091507074998e-24 * fConst0;
	fConst3 = (fConst0 * (fConst0 * (fConst2 + 6.98874158230498e-20) + 1.4095256819997e-16) + 1.75646845862514e-15) * fConst1;
	double fConst4 = 5.07545362580621e-24 * fConst0;
	fConst5 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (-7.00613593632107e-20 - fConst4) + -1.47460849525455e-16) + -2.81034919192636e-15) + -1.29152092545966e-14);
	double fConst6 = 1.03973026841637e-24 * fConst0;
	fConst7 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (-5.71785438210912e-20 - fConst6) + -1.41224926366503e-16) + -3.77185698680303e-15) + -3.30317585349598e-14);
	double fConst8 = 9.91377586985301e-24 * fConst0;
	fConst9 = fConst1 * (fConst0 * (fConst0 * (-9.36483991458906e-20 - fConst8) + -1.70486053448624e-16) + -2.12307123308889e-15);
	double fConst10 = 9.84499037599778e-24 * fConst0;
	fConst11 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst10 + 9.42766173980015e-20) + 1.78421312766784e-16) + 3.39775512445924e-15) + 1.56108178903595e-14);
	double fConst12 = 1.58888527196851e-24 * fConst0;
	fConst13 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst12 + 6.14378170525581e-20) + 1.4867852143994e-16) + 4.14135154627774e-15) + 3.80287926742832e-14);
	double fConst14 = 4.07249439024394e-27 * fConst0;
	fConst15 = fConst0 * (-1.34118849842818e-20 - fConst14) + -1.23525177556824e-15;
	double fConst16 = 3.9514408494262e-27 * fConst0;
	fConst17 = fConst0 * (fConst16 + 1.26300907176988e-20) + -2.68904213585766e-17;
	double fConst18 = 3.9514408494262e-29 * fConst0;
	fConst19 = fConst0 * (fConst18 + 1.26300907176988e-22) + -2.68904213585766e-19;
	double fConst20 = 4.07249439024394e-29 * fConst0;
	fConst21 = fConst0 * (-1.34118849842818e-22 - fConst20) + -1.23525177556824e-17;
	fConst22 = fConst1 * (fConst0 * (fConst0 * (6.98874158230498e-20 - fConst2) + -1.4095256819997e-16) + 1.75646845862514e-15);
	fConst23 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst4 + -7.00613593632107e-20) + 1.47460849525455e-16) + -2.81034919192636e-15) + 1.29152092545966e-14);
	fConst24 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst6 + -5.71785438210912e-20) + 1.41224926366503e-16) + -3.77185698680303e-15) + 3.30317585349598e-14);
	fConst25 = fConst1 * (fConst0 * (fConst0 * (fConst8 + -9.36483991458906e-20) + 1.70486053448624e-16) + -2.12307123308889e-15);
	fConst26 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (9.42766173980015e-20 - fConst10) + -1.78421312766784e-16) + 3.39775512445924e-15) + -1.56108178903595e-14);
	fConst27 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (6.14378170525581e-20 - fConst12) + -1.4867852143994e-16) + 4.14135154627774e-15) + -3.80287926742832e-14);
	double fConst28 = 2.55545753537499e-23 * fConst0;
	fConst29 = fConst1 * (fConst0 * (fConst0 * (fConst28 + -2.09662247469149e-19) + 1.4095256819997e-16) + 1.75646845862514e-15);
	double fConst30 = 2.53772681290311e-23 * fConst0;
	fConst31 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (2.10184078089632e-19 - fConst30) + -1.47460849525455e-16) + -2.81034919192636e-15) + 3.87456277637898e-14);
	double fConst32 = 5.19865134208184e-24 * fConst0;
	fConst33 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (1.71535631463274e-19 - fConst32) + -1.41224926366503e-16) + -3.77185698680303e-15) + 9.90952756048795e-14);
	double fConst34 = 4.95688793492651e-23 * fConst0;
	fConst35 = fConst1 * (fConst0 * (fConst0 * (2.80945197437672e-19 - fConst34) + -1.70486053448624e-16) + -2.12307123308889e-15);
	double fConst36 = 4.92249518799889e-23 * fConst0;
	fConst37 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst36 + -2.82829852194005e-19) + 1.78421312766784e-16) + 3.39775512445924e-15) + -4.68324536710785e-14);
	double fConst38 = 7.94442635984257e-24 * fConst0;
	fConst39 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst38 + -1.84313451157674e-19) + 1.4867852143994e-16) + 4.14135154627774e-15) + -1.1408637802285e-13);
	double fConst40 = 5.11091507074998e-23 * fConst0;
	fConst41 = fConst1 * (fConst0 * (fConst0 * (1.397748316461e-19 - fConst40) + 2.81905136399941e-16) + -3.51293691725028e-15);
	double fConst42 = 5.07545362580621e-23 * fConst0;
	fConst43 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst42 + -1.40122718726421e-19) + -2.94921699050911e-16) + 5.62069838385272e-15) + 2.58304185091932e-14);
	double fConst44 = 1.03973026841637e-23 * fConst0;
	fConst45 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst44 + -1.14357087642182e-19) + -2.82449852733007e-16) + 7.54371397360606e-15) + 6.60635170699196e-14);
	double fConst46 = 9.91377586985301e-23 * fConst0;
	fConst47 = fConst1 * (fConst0 * (fConst0 * (fConst46 + -1.87296798291781e-19) + -3.40972106897249e-16) + 4.24614246617778e-15);
	double fConst48 = 9.84499037599778e-23 * fConst0;
	fConst49 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (1.88553234796003e-19 - fConst48) + 3.56842625533568e-16) + -6.79551024891847e-15) + -3.1221635780719e-14);
	double fConst50 = 1.58888527196851e-23 * fConst0;
	fConst51 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (1.22875634105116e-19 - fConst50) + 2.97357042879881e-16) + -8.28270309255548e-15) + -7.60575853485664e-14);
	fConst52 = fConst1 * (fConst0 * (fConst0 * (fConst40 + 1.397748316461e-19) + -2.81905136399941e-16) + -3.51293691725028e-15);
	fConst53 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (-1.40122718726421e-19 - fConst42) + 2.94921699050911e-16) + 5.62069838385272e-15) + -2.58304185091932e-14);
	fConst54 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (-1.14357087642182e-19 - fConst44) + 2.82449852733007e-16) + 7.54371397360606e-15) + -6.60635170699196e-14);
	fConst55 = fConst1 * (fConst0 * (fConst0 * (-1.87296798291781e-19 - fConst46) + 3.40972106897249e-16) + 4.24614246617778e-15);
	fConst56 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst48 + 1.88553234796003e-19) + -3.56842625533568e-16) + -6.79551024891847e-15) + 3.1221635780719e-14);
	fConst57 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst50 + 1.22875634105116e-19) + -2.97357042879881e-16) + -8.28270309255548e-15) + 7.60575853485664e-14);
	fConst58 = fConst1 * (fConst0 * (fConst0 * (-2.09662247469149e-19 - fConst28) + -1.4095256819997e-16) + 1.75646845862514e-15);
	fConst59 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst30 + 2.10184078089632e-19) + 1.47460849525455e-16) + -2.81034919192636e-15) + -3.87456277637898e-14);
	fConst60 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst32 + 1.71535631463274e-19) + 1.41224926366503e-16) + -3.77185698680303e-15) + -9.90952756048795e-14);
	fConst61 = fConst1 * (fConst0 * (fConst0 * (fConst34 + 2.80945197437672e-19) + 1.70486053448624e-16) + -2.12307123308889e-15);
	fConst62 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (-2.82829852194005e-19 - fConst36) + -1.78421312766784e-16) + 3.39775512445924e-15) + 4.68324536710785e-14);
	fConst63 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (-1.84313451157674e-19 - fConst38) + -1.4867852143994e-16) + 4.14135154627774e-15) + 1.1408637802285e-13);
	double fConst64 = 2.03624719512197e-26 * fConst0;
	fConst65 = fConst0 * (fConst64 + 4.02356549528453e-20) + 1.23525177556824e-15;
	double fConst66 = 1.9757204247131e-26 * fConst0;
	fConst67 = fConst0 * (-3.78902721530964e-20 - fConst66) + 2.68904213585766e-17;
	double fConst68 = 1.9757204247131e-28 * fConst0;
	fConst69 = fConst0 * (-3.78902721530964e-22 - fConst68) + 2.68904213585766e-19;
	double fConst70 = 2.03624719512197e-28 * fConst0;
	fConst71 = fConst0 * (fConst70 + 4.02356549528453e-22) + 1.23525177556824e-17;
	double fConst72 = 4.07249439024394e-26 * fConst0;
	fConst73 = fConst0 * (-2.68237699685635e-20 - fConst72) + 2.47050355113649e-15;
	double fConst74 = 3.9514408494262e-26 * fConst0;
	fConst75 = fConst0 * (fConst74 + 2.52601814353976e-20) + 5.37808427171532e-17;
	double fConst76 = 3.9514408494262e-28 * fConst0;
	fConst77 = fConst0 * (fConst76 + 2.52601814353976e-22) + 5.37808427171532e-19;
	double fConst78 = 4.07249439024394e-28 * fConst0;
	fConst79 = fConst0 * (-2.68237699685635e-22 - fConst78) + 2.47050355113649e-17;
	fConst80 = fConst0 * (fConst72 + -2.68237699685635e-20) + -2.47050355113649e-15;
	fConst81 = fConst0 * (2.52601814353976e-20 - fConst74) + -5.37808427171532e-17;
	fConst82 = fConst0 * (2.52601814353976e-22 - fConst76) + -5.37808427171532e-19;
	fConst83 = fConst0 * (fConst78 + -2.68237699685635e-22) + -2.47050355113649e-17;
	fConst84 = fConst0 * (4.02356549528453e-20 - fConst64) + -1.23525177556824e-15;
	fConst85 = fConst0 * (fConst66 + -3.78902721530964e-20) + -2.68904213585766e-17;
	fConst86 = fConst0 * (fConst68 + -3.78902721530964e-22) + -2.68904213585766e-19;
	fConst87 = fConst0 * (4.02356549528453e-22 - fConst70) + -1.23525177556824e-17;
	fConst88 = fConst0 * (fConst14 + -1.34118849842818e-20) + 1.23525177556824e-15;
	fConst89 = fConst0 * (1.26300907176988e-20 - fConst16) + 2.68904213585766e-17;
	fConst90 = fConst0 * (1.26300907176988e-22 - fConst18) + 2.68904213585766e-19;
	fConst91 = fConst0 * (fConst20 + -1.34118849842818e-22) + 1.23525177556824e-17;
	fConst92 = 0.9302847925323914 * mydsp_faustpower3_f(fConst0);
	double fConst93 = 3.141592653589793 / fConst0;
	fConst94 = 1.0 - fConst93;
	fConst95 = 1.0 / (fConst93 + 1.0);
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
	double fSlow0 = 0.007000000000000006 * double(fVslider0);
	double fSlow1 = 0.007000000000000006 * double(fVslider1);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec12[0] = fSlow0 + 0.993 * fRec12[1];
		fRec13[0] = fSlow1 + 0.993 * fRec13[1];
		double fTemp0 = fConst13 + fRec12[0] * (fConst11 + fConst9 * fRec12[0]) + fRec13[0] * (fConst7 + fRec12[0] * (fConst5 + fConst3 * fRec12[0]) + -9.49647739308574e-14) + 1.14785425664408e-13;
		fRec14[0] = double(input0[i0]) - (fRec14[1] * (fConst63 + fRec12[0] * (fConst62 + fConst61 * fRec12[0]) + fRec13[0] * (fConst60 + fRec12[0] * (fConst59 + fConst58 * fRec12[0]) + -4.74823869654287e-13) + 5.7392712832204e-13) + fRec14[2] * (fConst57 + fRec12[0] * (fConst56 + fConst55 * fRec12[0]) + fRec13[0] * (fConst54 + fRec12[0] * (fConst53 + fConst52 * fRec12[0]) + -9.49647739308574e-13) + 1.14785425664408e-12) + fRec14[3] * (fConst51 + fRec12[0] * (fConst49 + fConst47 * fRec12[0]) + fRec13[0] * (fConst45 + fRec12[0] * (fConst43 + fConst41 * fRec12[0]) + -9.49647739308574e-13) + 1.14785425664408e-12) + fRec14[4] * (fConst39 + fRec12[0] * (fConst37 + fConst35 * fRec12[0]) + fRec13[0] * (fConst33 + fRec12[0] * (fConst31 + fConst29 * fRec12[0]) + -4.74823869654287e-13) + 5.7392712832204e-13) + fRec14[5] * (fConst27 + fRec12[0] * (fConst26 + fConst25 * fRec12[0]) + fRec13[0] * (fConst24 + fRec12[0] * (fConst23 + fConst22 * fRec12[0]) + -9.49647739308574e-14) + 1.14785425664408e-13)) / fTemp0;
		double fTemp1 = (fRec14[0] * (fConst91 + fRec13[0] * (fConst90 + fConst89 * fRec12[0]) + fConst88 * fRec12[0]) + fRec14[1] * (fConst87 + fRec13[0] * (fConst86 + fConst85 * fRec12[0]) + fConst84 * fRec12[0]) + fRec14[2] * (fConst83 + fRec13[0] * (fConst82 + fConst81 * fRec12[0]) + fConst80 * fRec12[0]) + fRec14[3] * (fConst79 + fRec13[0] * (fConst77 + fConst75 * fRec12[0]) + fConst73 * fRec12[0]) + fRec14[4] * (fConst71 + fRec13[0] * (fConst69 + fConst67 * fRec12[0]) + fConst65 * fRec12[0]) + fRec14[5] * (fConst21 + fRec13[0] * (fConst19 + fConst17 * fRec12[0]) + fConst15 * fRec12[0])) / fTemp0;
		fVec0[0] = fTemp1;
		fRec11[0] = fConst92 * (fTemp1 + fVec0[1]) - 0.8605695850647829 * fRec11[1];
		fRec10[0] = fRec11[0] - (1.8405051250752198 * fRec10[1] + 0.8612942439318627 * fRec10[2]);
		double fTemp2 = 1.8508996845035413 * fRec10[1] + 0.9254498422517706 * (fRec10[0] + fRec10[2]);
		double fTemp3 = Ftrany(TRANY_TABLE_7199P_68k, fTemp2 + 2.7e+03 * (fTemp2 / (Rtrany(TRANY_TABLE_7199P_68k, fRec9[1]) + 1e+05)) + -3.571981);
		fRec9[0] = fTemp3 + 0.001322955925925926 * (Rtrany(TRANY_TABLE_7199P_68k, fTemp3) + 1e+05) + -2.5e+02;
		fRec8[0] = fConst95 * (fConst94 * fRec8[1] + 0.025 * (fRec9[0] - fRec9[1]));
		fRec7[0] = 0.9302847925323914 * (fRec8[0] + fRec8[1]) - 0.8605695850647829 * fRec7[1];
		fRec6[0] = fRec7[0] - (1.8405051250752198 * fRec6[1] + 0.8612942439318627 * fRec6[2]);
		double fTemp4 = 1.8508996845035413 * fRec6[1] + 0.9254498422517706 * (fRec6[0] + fRec6[2]);
		double fTemp5 = Ftrany(TRANY_TABLE_7199P_68k, fTemp4 + 2.7e+03 * (fTemp4 / (Rtrany(TRANY_TABLE_7199P_68k, fRec5[1]) + 1e+05)) + -3.571981);
		fRec5[0] = fTemp5 + 0.001322955925925926 * (Rtrany(TRANY_TABLE_7199P_68k, fTemp5) + 1e+05) + -2.5e+02;
		fRec4[0] = fConst95 * (fConst94 * fRec4[1] + 0.025 * (fRec5[0] - fRec5[1]));
		fRec3[0] = 0.9302847925323914 * (fRec4[0] + fRec4[1]) - 0.8605695850647829 * fRec3[1];
		fRec2[0] = fRec3[0] - (1.8405051250752198 * fRec2[1] + 0.8612942439318627 * fRec2[2]);
		double fTemp6 = 1.8508996845035413 * fRec2[1] + 0.9254498422517706 * (fRec2[0] + fRec2[2]);
		double fTemp7 = Ftrany(TRANY_TABLE_7199P_68k, fTemp6 + 2.7e+03 * (fTemp6 / (Rtrany(TRANY_TABLE_7199P_68k, fRec1[1]) + 1e+05)) + -3.571981);
		fRec1[0] = fTemp7 + 0.001322955925925926 * (Rtrany(TRANY_TABLE_7199P_68k, fTemp7) + 1e+05) + -2.5e+02;
		fRec0[0] = fConst95 * (fConst94 * fRec0[1] + 0.025 * (fRec1[0] - fRec1[1]));
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
	case SUSTAIN: 
		fVslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case VOLUME: 
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
   SUSTAIN, 
   VOLUME, 
} PortIndex;
*/

} // end namespace susta
