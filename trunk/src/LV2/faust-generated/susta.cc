// generated from file '../src/LV2/faust/susta.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)

#include "trany.h"

namespace susta {

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
	double 	fConst7;
	double 	fConst8;
	double 	fConst9;
	double 	fConst10;
	double 	fConst11;
	double 	fConst12;
	double 	fConst13;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec13[2];
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
	double 	fRec14[6];
	double 	fConst64;
	double 	fConst65;
	double 	fConst66;
	double 	fConst67;
	double 	fConst68;
	double 	fConst69;
	double 	fConst70;
	double 	fConst71;
	double 	fConst72;
	double 	fConst73;
	double 	fConst74;
	double 	fConst75;
	double 	fConst76;
	double 	fConst77;
	double 	fConst78;
	double 	fConst79;
	double 	fConst80;
	double 	fConst81;
	double 	fConst82;
	double 	fConst83;
	double 	fConst84;
	double 	fConst85;
	double 	fConst86;
	double 	fConst87;
	double 	fConst88;
	double 	fConst89;
	double 	fConst90;
	double 	fConst91;
	double 	fVec0[2];
	double 	fConst92;
	double 	fRec11[2];
	double 	fRec10[3];
	double 	fConst93;
	double 	fConst94;
	double 	fConst95;
	double 	fConst96;
	double 	fRec15[2];
	double 	fRec9[3];
	double 	fConst97;
	double 	fConst98;
	double 	fConst99;
	double 	fConst100;
	double 	fConst101;
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
	fConst2 = (9.91377586985301e-24 * fConst1);
	fConst3 = ((fConst1 * ((fConst1 * (0 - (9.36483991458906e-20 + fConst2))) - 1.70486053448624e-16)) - 2.12307123308889e-15);
	fConst4 = (9.84499037599778e-24 * fConst1);
	fConst5 = (3.39775512445924e-15 + (fConst1 * (1.78421312766784e-16 + (fConst1 * (9.42766173980015e-20 + fConst4)))));
	fConst6 = (1.58888527196851e-24 * fConst1);
	fConst7 = (3.80287926742832e-14 + (fConst1 * (4.14135154627774e-15 + (fConst1 * (1.4867852143994e-16 + (fConst1 * (6.14378170525581e-20 + fConst6)))))));
	fConst8 = (5.11091507074998e-24 * fConst1);
	fConst9 = (1.75646845862514e-15 + (fConst1 * (1.4095256819997e-16 + (fConst1 * (6.98874158230498e-20 + fConst8)))));
	fConst10 = (5.07545362580621e-24 * fConst1);
	fConst11 = ((fConst1 * ((fConst1 * (0 - (7.00613593632107e-20 + fConst10))) - 1.47460849525455e-16)) - 2.81034919192636e-15);
	fConst12 = (1.03973026841637e-24 * fConst1);
	fConst13 = ((fConst1 * ((fConst1 * ((fConst1 * (0 - (5.71785438210912e-20 + fConst12))) - 1.41224926366503e-16)) - 3.77185698680303e-15)) - 3.30317585349598e-14);
	fConst14 = (4.07249439024394e-27 * fConst1);
	fConst15 = ((fConst1 * (0 - (1.34118849842818e-20 + fConst14))) - 1.23525177556824e-15);
	fConst16 = (3.9514408494262e-27 * fConst1);
	fConst17 = ((fConst1 * (1.26300907176988e-20 + fConst16)) - 2.68904213585766e-17);
	fConst18 = (3.9514408494262e-29 * fConst1);
	fConst19 = ((fConst1 * (1.26300907176988e-22 + fConst18)) - 2.68904213585766e-19);
	fConst20 = (4.07249439024394e-29 * fConst1);
	fConst21 = ((fConst1 * (0 - (1.34118849842818e-22 + fConst20))) - 1.23525177556824e-17);
	fConst22 = ((fConst1 * (1.70486053448624e-16 + (fConst1 * (fConst2 - 9.36483991458906e-20)))) - 2.12307123308889e-15);
	fConst23 = (3.39775512445924e-15 + (fConst1 * ((fConst1 * (9.42766173980015e-20 - fConst4)) - 1.78421312766784e-16)));
	fConst24 = ((fConst1 * (4.14135154627774e-15 + (fConst1 * ((fConst1 * (6.14378170525581e-20 - fConst6)) - 1.4867852143994e-16)))) - 3.80287926742832e-14);
	fConst25 = (1.75646845862514e-15 + (fConst1 * ((fConst1 * (6.98874158230498e-20 - fConst8)) - 1.4095256819997e-16)));
	fConst26 = ((fConst1 * (1.47460849525455e-16 + (fConst1 * (fConst10 - 7.00613593632107e-20)))) - 2.81034919192636e-15);
	fConst27 = (3.30317585349598e-14 + (fConst1 * ((fConst1 * (1.41224926366503e-16 + (fConst1 * (fConst12 - 5.71785438210912e-20)))) - 3.77185698680303e-15)));
	fConst28 = (4.95688793492651e-23 * fConst1);
	fConst29 = ((fConst1 * ((fConst1 * (2.80945197437672e-19 - fConst28)) - 1.70486053448624e-16)) - 2.12307123308889e-15);
	fConst30 = (4.92249518799889e-23 * fConst1);
	fConst31 = (3.39775512445924e-15 + (fConst1 * (1.78421312766784e-16 + (fConst1 * (fConst30 - 2.82829852194005e-19)))));
	fConst32 = (7.94442635984257e-24 * fConst1);
	fConst33 = ((fConst1 * (4.14135154627774e-15 + (fConst1 * (1.4867852143994e-16 + (fConst1 * (fConst32 - 1.84313451157674e-19)))))) - 1.1408637802285e-13);
	fConst34 = (2.55545753537499e-23 * fConst1);
	fConst35 = (1.75646845862514e-15 + (fConst1 * (1.4095256819997e-16 + (fConst1 * (fConst34 - 2.09662247469149e-19)))));
	fConst36 = (2.53772681290311e-23 * fConst1);
	fConst37 = ((fConst1 * ((fConst1 * (2.10184078089632e-19 - fConst36)) - 1.47460849525455e-16)) - 2.81034919192636e-15);
	fConst38 = (5.19865134208184e-24 * fConst1);
	fConst39 = (9.90952756048795e-14 + (fConst1 * ((fConst1 * ((fConst1 * (1.71535631463274e-19 - fConst38)) - 1.41224926366503e-16)) - 3.77185698680303e-15)));
	fConst40 = (9.91377586985301e-23 * fConst1);
	fConst41 = (4.24614246617778e-15 + (fConst1 * ((fConst1 * (fConst40 - 1.87296798291781e-19)) - 3.40972106897249e-16)));
	fConst42 = (9.84499037599778e-23 * fConst1);
	fConst43 = ((fConst1 * (3.56842625533568e-16 + (fConst1 * (1.88553234796003e-19 - fConst42)))) - 6.79551024891847e-15);
	fConst44 = (1.58888527196851e-23 * fConst1);
	fConst45 = ((fConst1 * ((fConst1 * (2.97357042879881e-16 + (fConst1 * (1.22875634105116e-19 - fConst44)))) - 8.28270309255548e-15)) - 7.60575853485664e-14);
	fConst46 = (5.11091507074998e-23 * fConst1);
	fConst47 = ((fConst1 * (2.81905136399941e-16 + (fConst1 * (1.397748316461e-19 - fConst46)))) - 3.51293691725028e-15);
	fConst48 = (5.07545362580621e-23 * fConst1);
	fConst49 = (5.62069838385272e-15 + (fConst1 * ((fConst1 * (fConst48 - 1.40122718726421e-19)) - 2.94921699050911e-16)));
	fConst50 = (1.03973026841637e-23 * fConst1);
	fConst51 = (6.60635170699196e-14 + (fConst1 * (7.54371397360606e-15 + (fConst1 * ((fConst1 * (fConst50 - 1.14357087642182e-19)) - 2.82449852733007e-16)))));
	fConst52 = (4.24614246617778e-15 + (fConst1 * (3.40972106897249e-16 + (fConst1 * (0 - (1.87296798291781e-19 + fConst40))))));
	fConst53 = ((fConst1 * ((fConst1 * (1.88553234796003e-19 + fConst42)) - 3.56842625533568e-16)) - 6.79551024891847e-15);
	fConst54 = (7.60575853485664e-14 + (fConst1 * ((fConst1 * ((fConst1 * (1.22875634105116e-19 + fConst44)) - 2.97357042879881e-16)) - 8.28270309255548e-15)));
	fConst55 = ((fConst1 * ((fConst1 * (1.397748316461e-19 + fConst46)) - 2.81905136399941e-16)) - 3.51293691725028e-15);
	fConst56 = (5.62069838385272e-15 + (fConst1 * (2.94921699050911e-16 + (fConst1 * (0 - (1.40122718726421e-19 + fConst48))))));
	fConst57 = ((fConst1 * (7.54371397360606e-15 + (fConst1 * (2.82449852733007e-16 + (fConst1 * (0 - (1.14357087642182e-19 + fConst50))))))) - 6.60635170699196e-14);
	fConst58 = ((fConst1 * (1.70486053448624e-16 + (fConst1 * (2.80945197437672e-19 + fConst28)))) - 2.12307123308889e-15);
	fConst59 = (3.39775512445924e-15 + (fConst1 * ((fConst1 * (0 - (2.82829852194005e-19 + fConst30))) - 1.78421312766784e-16)));
	fConst60 = (1.1408637802285e-13 + (fConst1 * (4.14135154627774e-15 + (fConst1 * ((fConst1 * (0 - (1.84313451157674e-19 + fConst32))) - 1.4867852143994e-16)))));
	fConst61 = (1.75646845862514e-15 + (fConst1 * ((fConst1 * (0 - (2.09662247469149e-19 + fConst34))) - 1.4095256819997e-16)));
	fConst62 = ((fConst1 * (1.47460849525455e-16 + (fConst1 * (2.10184078089632e-19 + fConst36)))) - 2.81034919192636e-15);
	fConst63 = ((fConst1 * ((fConst1 * (1.41224926366503e-16 + (fConst1 * (1.71535631463274e-19 + fConst38)))) - 3.77185698680303e-15)) - 9.90952756048795e-14);
	fConst64 = (2.03624719512197e-26 * fConst1);
	fConst65 = (1.23525177556824e-15 + (fConst1 * (4.02356549528453e-20 + fConst64)));
	fConst66 = (1.9757204247131e-26 * fConst1);
	fConst67 = (2.68904213585766e-17 + (fConst1 * (0 - (3.78902721530964e-20 + fConst66))));
	fConst68 = (1.9757204247131e-28 * fConst1);
	fConst69 = (2.68904213585766e-19 + (fConst1 * (0 - (3.78902721530964e-22 + fConst68))));
	fConst70 = (2.03624719512197e-28 * fConst1);
	fConst71 = (1.23525177556824e-17 + (fConst1 * (4.02356549528453e-22 + fConst70)));
	fConst72 = (4.07249439024394e-26 * fConst1);
	fConst73 = (2.47050355113649e-15 + (fConst1 * (0 - (2.68237699685635e-20 + fConst72))));
	fConst74 = (3.9514408494262e-26 * fConst1);
	fConst75 = (5.37808427171532e-17 + (fConst1 * (2.52601814353976e-20 + fConst74)));
	fConst76 = (3.9514408494262e-28 * fConst1);
	fConst77 = (5.37808427171532e-19 + (fConst1 * (2.52601814353976e-22 + fConst76)));
	fConst78 = (4.07249439024394e-28 * fConst1);
	fConst79 = (2.47050355113649e-17 + (fConst1 * (0 - (2.68237699685635e-22 + fConst78))));
	fConst80 = (1.23525177556824e-15 + (fConst1 * (fConst14 - 1.34118849842818e-20)));
	fConst81 = (2.68904213585766e-17 + (fConst1 * (1.26300907176988e-20 - fConst16)));
	fConst82 = (2.68904213585766e-19 + (fConst1 * (1.26300907176988e-22 - fConst18)));
	fConst83 = (1.23525177556824e-17 + (fConst1 * (fConst20 - 1.34118849842818e-22)));
	fConst84 = ((fConst1 * (fConst72 - 2.68237699685635e-20)) - 2.47050355113649e-15);
	fConst85 = ((fConst1 * (2.52601814353976e-20 - fConst74)) - 5.37808427171532e-17);
	fConst86 = ((fConst1 * (2.52601814353976e-22 - fConst76)) - 5.37808427171532e-19);
	fConst87 = ((fConst1 * (fConst78 - 2.68237699685635e-22)) - 2.47050355113649e-17);
	fConst88 = ((fConst1 * (4.02356549528453e-20 - fConst64)) - 1.23525177556824e-15);
	fConst89 = ((fConst1 * (fConst66 - 3.78902721530964e-20)) - 2.68904213585766e-17);
	fConst90 = ((fConst1 * (fConst68 - 3.78902721530964e-22)) - 2.68904213585766e-19);
	fConst91 = ((fConst1 * (4.02356549528453e-22 - fConst70)) - 1.23525177556824e-17);
	fConst92 = (0.9302847925323914 * faustpower<3>(fConst1));
	fConst93 = (1.0 / tan((270.1769682087222 / fConst0)));
	fConst94 = (1 + fConst93);
	fConst95 = (0 - ((1 - fConst93) / fConst94));
	fConst96 = (0.027 / fConst94);
	fConst97 = (1.0 / tan((97.38937226128358 / fConst0)));
	fConst98 = (0 - fConst97);
	fConst99 = (1 + fConst97);
	fConst100 = (0.025 / fConst99);
	fConst101 = (0 - ((1 - fConst97) / fConst99));
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
	double 	fSlow0 = (0.007000000000000006 * double(fslider0));
	double 	fSlow1 = (0.007000000000000006 * double(fslider1));
	for (int i=0; i<count; i++) {
		fRec12[0] = (fSlow0 + (0.993 * fRec12[1]));
		fRec13[0] = (fSlow1 + (0.993 * fRec13[1]));
		double fTemp0 = (1.14785425664408e-13 + ((fRec13[0] * ((fConst1 * (fConst13 + (fRec12[0] * ((fConst1 * (fConst11 + (fConst9 * fRec12[0]))) - 1.29152092545966e-14)))) - 9.49647739308574e-14)) + (fConst1 * (fConst7 + (fRec12[0] * (1.56108178903595e-14 + (fConst1 * (fConst5 + (fConst3 * fRec12[0])))))))));
		fRec14[0] = ((double)input0[i] - ((((((fRec14[1] * (5.7392712832204e-13 + ((fRec13[0] * ((fConst1 * (fConst63 + (fRec12[0] * ((fConst1 * (fConst62 + (fConst61 * fRec12[0]))) - 3.87456277637898e-14)))) - 4.74823869654287e-13)) + (fConst1 * (fConst60 + (fRec12[0] * (4.68324536710785e-14 + (fConst1 * (fConst59 + (fConst58 * fRec12[0])))))))))) + (fRec14[2] * (1.14785425664408e-12 + ((fRec13[0] * ((fConst1 * (fConst57 + (fRec12[0] * ((fConst1 * (fConst56 + (fConst55 * fRec12[0]))) - 2.58304185091932e-14)))) - 9.49647739308574e-13)) + (fConst1 * (fConst54 + (fRec12[0] * (3.1221635780719e-14 + (fConst1 * (fConst53 + (fConst52 * fRec12[0]))))))))))) + (fRec14[3] * (1.14785425664408e-12 + ((fRec13[0] * ((fConst1 * (fConst51 + (fRec12[0] * (2.58304185091932e-14 + (fConst1 * (fConst49 + (fConst47 * fRec12[0]))))))) - 9.49647739308574e-13)) + (fConst1 * (fConst45 + (fRec12[0] * ((fConst1 * (fConst43 + (fConst41 * fRec12[0]))) - 3.1221635780719e-14)))))))) + (fRec14[4] * (5.7392712832204e-13 + ((fRec13[0] * ((fConst1 * (fConst39 + (fRec12[0] * (3.87456277637898e-14 + (fConst1 * (fConst37 + (fConst35 * fRec12[0]))))))) - 4.74823869654287e-13)) + (fConst1 * (fConst33 + (fRec12[0] * ((fConst1 * (fConst31 + (fConst29 * fRec12[0]))) - 4.68324536710785e-14)))))))) + (fRec14[5] * (1.14785425664408e-13 + ((fRec13[0] * ((fConst1 * (fConst27 + (fRec12[0] * (1.29152092545966e-14 + (fConst1 * (fConst26 + (fConst25 * fRec12[0]))))))) - 9.49647739308574e-14)) + (fConst1 * (fConst24 + (fRec12[0] * ((fConst1 * (fConst23 + (fConst22 * fRec12[0]))) - 1.56108178903595e-14)))))))) / fTemp0));
		double fTemp1 = ((((((fRec14[1] * (fConst91 + ((fRec13[0] * (fConst90 + (fConst89 * fRec12[0]))) + (fConst88 * fRec12[0])))) + ((fRec14[2] * (fConst87 + ((fRec13[0] * (fConst86 + (fConst85 * fRec12[0]))) + (fConst84 * fRec12[0])))) + (fRec14[0] * (fConst83 + ((fRec13[0] * (fConst82 + (fConst81 * fRec12[0]))) + (fConst80 * fRec12[0])))))) + (fRec14[3] * (fConst79 + ((fRec13[0] * (fConst77 + (fConst75 * fRec12[0]))) + (fConst73 * fRec12[0]))))) + (fRec14[4] * (fConst71 + ((fRec13[0] * (fConst69 + (fConst67 * fRec12[0]))) + (fConst65 * fRec12[0]))))) + (fRec14[5] * (fConst21 + ((fRec13[0] * (fConst19 + (fConst17 * fRec12[0]))) + (fConst15 * fRec12[0]))))) / fTemp0);
		fVec0[0] = fTemp1;
		fRec11[0] = ((fConst92 * (fVec0[0] + fVec0[1])) - (0.8605695850647829 * fRec11[1]));
		fRec10[0] = (fRec11[0] - ((1.8405051250752198 * fRec10[1]) + (0.8612942439318627 * fRec10[2])));
		fRec15[0] = ((fConst96 * (fRec9[1] + fRec9[2])) + (fConst95 * fRec15[1]));
		fRec9[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec15[0] + (0.9254498422517706 * (fRec10[0] + (fRec10[2] + (2.0 * fRec10[1]))))) - 3.571981)) - 117.70440740740739);
		fRec8[0] = ((fConst101 * fRec8[1]) + (fConst100 * ((fConst97 * fRec9[0]) + (fConst98 * fRec9[1]))));
		fRec7[0] = ((0.9302847925323914 * (fRec8[1] + fRec8[0])) - (0.8605695850647829 * fRec7[1]));
		fRec6[0] = (fRec7[0] - ((1.8405051250752198 * fRec6[1]) + (0.8612942439318627 * fRec6[2])));
		fRec16[0] = ((fConst96 * (fRec5[1] + fRec5[2])) + (fConst95 * fRec16[1]));
		fRec5[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec16[0] + (0.9254498422517706 * (fRec6[0] + (fRec6[2] + (2.0 * fRec6[1]))))) - 3.571981)) - 117.70440740740739);
		fRec4[0] = ((fConst101 * fRec4[1]) + (fConst100 * ((fConst97 * fRec5[0]) + (fConst98 * fRec5[1]))));
		fRec3[0] = ((0.9302847925323914 * (fRec4[1] + fRec4[0])) - (0.8605695850647829 * fRec3[1]));
		fRec2[0] = (fRec3[0] - ((1.8405051250752198 * fRec2[1]) + (0.8612942439318627 * fRec2[2])));
		fRec17[0] = ((fConst96 * (fRec1[1] + fRec1[2])) + (fConst95 * fRec17[1]));
		fRec1[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec17[0] + (0.9254498422517706 * (fRec2[0] + (fRec2[2] + (2.0 * fRec2[1]))))) - 3.571981)) - 117.70440740740739);
		fRec0[0] = ((fConst101 * fRec0[1]) + (fConst100 * ((fConst97 * fRec1[0]) + (fConst98 * fRec1[1]))));
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
	case SUSTAIN: 
		fslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case VOLUME: 
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
   SUSTAIN, 
   VOLUME, 
} PortIndex;
*/

} // end namespace susta
