// generated from file '../src/LV2/faust/susta.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "trany.h"

namespace susta {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	double fConst4;
	double fConst5;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec13[2];
	double fConst6;
	double fConst7;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec14[2];
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
	double fConst22;
	double fConst23;
	double fConst24;
	double fConst25;
	double fConst26;
	double fConst27;
	double fConst28;
	double fConst29;
	double fConst30;
	double fConst31;
	double fConst32;
	double fConst33;
	double fConst34;
	double fConst35;
	double fConst36;
	double fConst37;
	double fConst38;
	double fConst39;
	double fConst40;
	double fConst41;
	double fConst42;
	double fConst43;
	double fConst44;
	double fConst45;
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
	double fRec12[6];
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
	double fConst71;
	double fConst72;
	double fConst73;
	double fConst74;
	double fConst75;
	double fConst76;
	double fConst77;
	double fConst78;
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
	double fConst92;
	double fConst93;
	double fConst94;
	double fConst95;
	double fVec0[2];
	double fRec11[2];
	double fRec10[3];
	double fConst96;
	double fConst97;
	double fConst98;
	double fRec15[2];
	double fRec9[3];
	double fConst99;
	double fConst100;
	double fRec8[2];
	double fRec7[2];
	double fRec6[3];
	double fRec16[2];
	double fRec5[3];
	double fRec4[2];
	double fRec3[2];
	double fRec2[3];
	double fRec17[2];
	double fRec1[3];
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec13[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec14[l1] = 0.0;
	for (int l2 = 0; (l2 < 6); l2 = (l2 + 1)) fRec12[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fVec0[l3] = 0.0;
	for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) fRec11[l4] = 0.0;
	for (int l5 = 0; (l5 < 3); l5 = (l5 + 1)) fRec10[l5] = 0.0;
	for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) fRec15[l6] = 0.0;
	for (int l7 = 0; (l7 < 3); l7 = (l7 + 1)) fRec9[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fRec8[l8] = 0.0;
	for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) fRec7[l9] = 0.0;
	for (int l10 = 0; (l10 < 3); l10 = (l10 + 1)) fRec6[l10] = 0.0;
	for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) fRec16[l11] = 0.0;
	for (int l12 = 0; (l12 < 3); l12 = (l12 + 1)) fRec5[l12] = 0.0;
	for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) fRec4[l13] = 0.0;
	for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) fRec3[l14] = 0.0;
	for (int l15 = 0; (l15 < 3); l15 = (l15 + 1)) fRec2[l15] = 0.0;
	for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) fRec17[l16] = 0.0;
	for (int l17 = 0; (l17 < 3); l17 = (l17 + 1)) fRec1[l17] = 0.0;
	for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) fRec0[l18] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = std::tan((97.389372261283583 / fConst0));
	fConst2 = (1.0 / fConst1);
	fConst3 = (fConst2 + 1.0);
	fConst4 = (1.0 / (fConst1 * fConst3));
	fConst5 = (0.93028479253239138 * mydsp_faustpower3_f(fConst0));
	fConst6 = (5.1986513420818397e-24 * fConst0);
	fConst7 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst6 + 1.7153563146327399e-19)) + 1.41224926366503e-16)) + -3.7718569868030302e-15)) + -9.9095275604879496e-14);
	fConst8 = (2.5377268129031099e-23 * fConst0);
	fConst9 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst8 + 2.10184078089632e-19)) + 1.4746084952545501e-16)) + -2.8103491919263598e-15)) + -3.8745627763789799e-14);
	fConst10 = (2.5554575353749899e-23 * fConst0);
	fConst11 = (fConst0 * ((fConst0 * ((fConst0 * (-2.0966224746914901e-19 - fConst10)) + -1.4095256819997e-16)) + 1.7564684586251401e-15));
	fConst12 = (7.9444263598425703e-24 * fConst0);
	fConst13 = ((fConst0 * ((fConst0 * ((fConst0 * (-1.8431345115767401e-19 - fConst12)) + -1.4867852143994001e-16)) + 4.14135154627774e-15)) + 1.1408637802285001e-13);
	fConst14 = (4.9224951879988899e-23 * fConst0);
	fConst15 = ((fConst0 * ((fConst0 * ((fConst0 * (-2.8282985219400499e-19 - fConst14)) + -1.7842131276678399e-16)) + 3.3977551244592401e-15)) + 4.6832453671078502e-14);
	fConst16 = (4.9568879349265099e-23 * fConst0);
	fConst17 = (fConst0 * ((fConst0 * ((fConst0 * (fConst16 + 2.80945197437672e-19)) + 1.70486053448624e-16)) + -2.12307123308889e-15));
	fConst18 = (1.03973026841637e-23 * fConst0);
	fConst19 = ((fConst0 * ((fConst0 * ((fConst0 * (-1.1435708764218199e-19 - fConst18)) + 2.8244985273300699e-16)) + 7.5437139736060604e-15)) + -6.6063517069919597e-14);
	fConst20 = (5.0754536258062098e-23 * fConst0);
	fConst21 = ((fConst0 * ((fConst0 * ((fConst0 * (-1.40122718726421e-19 - fConst20)) + 2.94921699050911e-16)) + 5.6206983838527196e-15)) + -2.5830418509193201e-14);
	fConst22 = (5.1109150707499798e-23 * fConst0);
	fConst23 = (fConst0 * ((fConst0 * ((fConst0 * (fConst22 + 1.3977483164610001e-19)) + -2.8190513639994098e-16)) + -3.5129369172502802e-15));
	fConst24 = (1.5888852719685099e-23 * fConst0);
	fConst25 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst24 + 1.22875634105116e-19)) + -2.97357042879881e-16)) + -8.2827030925554799e-15)) + 7.6057585348566401e-14);
	fConst26 = (9.8449903759977797e-23 * fConst0);
	fConst27 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst26 + 1.88553234796003e-19)) + -3.5684262553356798e-16)) + -6.7955102489184699e-15)) + 3.1221635780719003e-14);
	fConst28 = (9.9137758698530105e-23 * fConst0);
	fConst29 = (fConst0 * ((fConst0 * ((fConst0 * (-1.87296798291781e-19 - fConst28)) + 3.40972106897249e-16)) + 4.2461424661777799e-15));
	fConst30 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst18 + -1.1435708764218199e-19)) + -2.8244985273300699e-16)) + 7.5437139736060604e-15)) + 6.6063517069919597e-14);
	fConst31 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst20 + -1.40122718726421e-19)) + -2.94921699050911e-16)) + 5.6206983838527196e-15)) + 2.5830418509193201e-14);
	fConst32 = (fConst0 * ((fConst0 * ((fConst0 * (1.3977483164610001e-19 - fConst22)) + 2.8190513639994098e-16)) + -3.5129369172502802e-15));
	fConst33 = ((fConst0 * ((fConst0 * ((fConst0 * (1.22875634105116e-19 - fConst24)) + 2.97357042879881e-16)) + -8.2827030925554799e-15)) + -7.6057585348566401e-14);
	fConst34 = ((fConst0 * ((fConst0 * ((fConst0 * (1.88553234796003e-19 - fConst26)) + 3.5684262553356798e-16)) + -6.7955102489184699e-15)) + -3.1221635780719003e-14);
	fConst35 = (fConst0 * ((fConst0 * ((fConst0 * (fConst28 + -1.87296798291781e-19)) + -3.40972106897249e-16)) + 4.2461424661777799e-15));
	fConst36 = ((fConst0 * ((fConst0 * ((fConst0 * (1.7153563146327399e-19 - fConst6)) + -1.41224926366503e-16)) + -3.7718569868030302e-15)) + 9.9095275604879496e-14);
	fConst37 = ((fConst0 * ((fConst0 * ((fConst0 * (2.10184078089632e-19 - fConst8)) + -1.4746084952545501e-16)) + -2.8103491919263598e-15)) + 3.8745627763789799e-14);
	fConst38 = (fConst0 * ((fConst0 * ((fConst0 * (fConst10 + -2.0966224746914901e-19)) + 1.4095256819997e-16)) + 1.7564684586251401e-15));
	fConst39 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst12 + -1.8431345115767401e-19)) + 1.4867852143994001e-16)) + 4.14135154627774e-15)) + -1.1408637802285001e-13);
	fConst40 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst14 + -2.8282985219400499e-19)) + 1.7842131276678399e-16)) + 3.3977551244592401e-15)) + -4.6832453671078502e-14);
	fConst41 = (fConst0 * ((fConst0 * ((fConst0 * (2.80945197437672e-19 - fConst16)) + -1.70486053448624e-16)) + -2.12307123308889e-15));
	fConst42 = (1.03973026841637e-24 * fConst0);
	fConst43 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst42 + -5.7178543821091199e-20)) + 1.41224926366503e-16)) + -3.7718569868030302e-15)) + 3.3031758534959798e-14);
	fConst44 = (5.07545362580621e-24 * fConst0);
	fConst45 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst44 + -7.0061359363210703e-20)) + 1.4746084952545501e-16)) + -2.8103491919263598e-15)) + 1.2915209254596601e-14);
	fConst46 = (5.1109150707499797e-24 * fConst0);
	fConst47 = (fConst0 * ((fConst0 * ((fConst0 * (6.9887415823049801e-20 - fConst46)) + -1.4095256819997e-16)) + 1.7564684586251401e-15));
	fConst48 = (1.58888527196851e-24 * fConst0);
	fConst49 = ((fConst0 * ((fConst0 * ((fConst0 * (6.1437817052558098e-20 - fConst48)) + -1.4867852143994001e-16)) + 4.14135154627774e-15)) + -3.80287926742832e-14);
	fConst50 = (9.84499037599778e-24 * fConst0);
	fConst51 = ((fConst0 * ((fConst0 * ((fConst0 * (9.42766173980015e-20 - fConst50)) + -1.7842131276678399e-16)) + 3.3977551244592401e-15)) + -1.5610817890359502e-14);
	fConst52 = (9.9137758698530105e-24 * fConst0);
	fConst53 = (fConst0 * ((fConst0 * ((fConst0 * (fConst52 + -9.3648399145890596e-20)) + 1.70486053448624e-16)) + -2.12307123308889e-15));
	fConst54 = ((fConst0 * ((fConst0 * ((fConst0 * (-5.7178543821091199e-20 - fConst42)) + -1.41224926366503e-16)) + -3.7718569868030302e-15)) + -3.3031758534959798e-14);
	fConst55 = ((fConst0 * ((fConst0 * ((fConst0 * (-7.0061359363210703e-20 - fConst44)) + -1.4746084952545501e-16)) + -2.8103491919263598e-15)) + -1.2915209254596601e-14);
	fConst56 = (fConst0 * ((fConst0 * ((fConst0 * (fConst46 + 6.9887415823049801e-20)) + 1.4095256819997e-16)) + 1.7564684586251401e-15));
	fConst57 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst48 + 6.1437817052558098e-20)) + 1.4867852143994001e-16)) + 4.14135154627774e-15)) + 3.80287926742832e-14);
	fConst58 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst50 + 9.42766173980015e-20)) + 1.7842131276678399e-16)) + 3.3977551244592401e-15)) + 1.5610817890359502e-14);
	fConst59 = (fConst0 * ((fConst0 * ((fConst0 * (-9.3648399145890596e-20 - fConst52)) + -1.70486053448624e-16)) + -2.12307123308889e-15));
	fConst60 = (4.0724943902439398e-29 * fConst0);
	fConst61 = ((fConst0 * (fConst60 + -1.3411884984281801e-22)) + 1.2352517755682401e-17);
	fConst62 = (3.9514408494262001e-29 * fConst0);
	fConst63 = ((fConst0 * (1.2630090717698801e-22 - fConst62)) + 2.6890421358576598e-19);
	fConst64 = (3.9514408494262003e-27 * fConst0);
	fConst65 = ((fConst0 * (1.26300907176988e-20 - fConst64)) + 2.6890421358576598e-17);
	fConst66 = (4.0724943902439399e-27 * fConst0);
	fConst67 = ((fConst0 * (fConst66 + -1.3411884984281799e-20)) + 1.23525177556824e-15);
	fConst68 = (2.0362471951219699e-28 * fConst0);
	fConst69 = ((fConst0 * (4.02356549528453e-22 - fConst68)) + -1.2352517755682401e-17);
	fConst70 = (1.9757204247131001e-28 * fConst0);
	fConst71 = ((fConst0 * (fConst70 + -3.78902721530964e-22)) + -2.6890421358576598e-19);
	fConst72 = (1.9757204247130999e-26 * fConst0);
	fConst73 = ((fConst0 * (fConst72 + -3.7890272153096399e-20)) + -2.6890421358576598e-17);
	fConst74 = (2.03624719512197e-26 * fConst0);
	fConst75 = ((fConst0 * (4.0235654952845302e-20 - fConst74)) + -1.23525177556824e-15);
	fConst76 = (4.0724943902439399e-28 * fConst0);
	fConst77 = ((fConst0 * (fConst76 + -2.6823769968563499e-22)) + -2.47050355113649e-17);
	fConst78 = (3.9514408494262001e-28 * fConst0);
	fConst79 = ((fConst0 * (2.5260181435397602e-22 - fConst78)) + -5.3780842717153195e-19);
	fConst80 = (3.9514408494261998e-26 * fConst0);
	fConst81 = ((fConst0 * (2.5260181435397601e-20 - fConst80)) + -5.3780842717153197e-17);
	fConst82 = (4.07249439024394e-26 * fConst0);
	fConst83 = ((fConst0 * (fConst82 + -2.6823769968563499e-20)) + -2.4705035511364902e-15);
	fConst84 = ((fConst0 * (-2.6823769968563499e-22 - fConst76)) + 2.47050355113649e-17);
	fConst85 = ((fConst0 * (fConst78 + 2.5260181435397602e-22)) + 5.3780842717153195e-19);
	fConst86 = ((fConst0 * (fConst80 + 2.5260181435397601e-20)) + 5.3780842717153197e-17);
	fConst87 = ((fConst0 * (-2.6823769968563499e-20 - fConst82)) + 2.4705035511364902e-15);
	fConst88 = ((fConst0 * (fConst68 + 4.02356549528453e-22)) + 1.2352517755682401e-17);
	fConst89 = ((fConst0 * (-3.78902721530964e-22 - fConst70)) + 2.6890421358576598e-19);
	fConst90 = ((fConst0 * (-3.7890272153096399e-20 - fConst72)) + 2.6890421358576598e-17);
	fConst91 = ((fConst0 * (fConst74 + 4.0235654952845302e-20)) + 1.23525177556824e-15);
	fConst92 = ((fConst0 * (-1.3411884984281801e-22 - fConst60)) + -1.2352517755682401e-17);
	fConst93 = ((fConst0 * (fConst62 + 1.2630090717698801e-22)) + -2.6890421358576598e-19);
	fConst94 = ((fConst0 * (fConst64 + 1.26300907176988e-20)) + -2.6890421358576598e-17);
	fConst95 = ((fConst0 * (-1.3411884984281799e-20 - fConst66)) + -1.23525177556824e-15);
	fConst96 = (1.0 / std::tan((270.1769682087222 / fConst0)));
	fConst97 = (1.0 / (fConst96 + 1.0));
	fConst98 = (1.0 - fConst96);
	fConst99 = (0.0 - fConst4);
	fConst100 = ((1.0 - fConst2) / fConst3);
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
	double fSlow0 = (0.0070000000000000062 * double(fVslider0));
	double fSlow1 = (0.0070000000000000062 * double(fVslider1));
	for (int i = 0; (i < count); i = (i + 1)) {
		fRec13[0] = (fSlow0 + (0.99299999999999999 * fRec13[1]));
		fRec14[0] = (fSlow1 + (0.99299999999999999 * fRec14[1]));
		double fTemp0 = (((fRec13[0] * ((fConst0 * (fConst54 + (fRec14[0] * (fConst55 + (fConst56 * fRec14[0]))))) + -9.4964773930857394e-14)) + (fConst0 * (fConst57 + (fRec14[0] * (fConst58 + (fConst59 * fRec14[0])))))) + 1.1478542566440801e-13);
		fRec12[0] = (double(input0[i]) - ((((((fRec12[1] * (((fRec13[0] * ((fConst0 * (fConst7 + (fRec14[0] * (fConst9 + (fConst11 * fRec14[0]))))) + -4.7482386965428703e-13)) + (fConst0 * (fConst13 + (fRec14[0] * (fConst15 + (fConst17 * fRec14[0])))))) + 5.7392712832203995e-13)) + (fRec12[2] * (((fRec13[0] * ((fConst0 * (fConst19 + (fRec14[0] * (fConst21 + (fConst23 * fRec14[0]))))) + -9.4964773930857407e-13)) + (fConst0 * (fConst25 + (fRec14[0] * (fConst27 + (fConst29 * fRec14[0])))))) + 1.1478542566440799e-12))) + (fRec12[3] * (((fRec13[0] * ((fConst0 * (fConst30 + (fRec14[0] * (fConst31 + (fConst32 * fRec14[0]))))) + -9.4964773930857407e-13)) + (fConst0 * (fConst33 + (fRec14[0] * (fConst34 + (fConst35 * fRec14[0])))))) + 1.1478542566440799e-12))) + (fRec12[4] * (((fRec13[0] * ((fConst0 * (fConst36 + (fRec14[0] * (fConst37 + (fConst38 * fRec14[0]))))) + -4.7482386965428703e-13)) + (fConst0 * (fConst39 + (fRec14[0] * (fConst40 + (fConst41 * fRec14[0])))))) + 5.7392712832203995e-13))) + (fRec12[5] * (((fRec13[0] * ((fConst0 * (fConst43 + (fRec14[0] * (fConst45 + (fConst47 * fRec14[0]))))) + -9.4964773930857394e-14)) + (fConst0 * (fConst49 + (fRec14[0] * (fConst51 + (fConst53 * fRec14[0])))))) + 1.1478542566440801e-13))) / fTemp0));
		double fTemp1 = (((((((fRec12[0] * (fConst61 + ((fRec13[0] * (fConst63 + (fConst65 * fRec14[0]))) + (fConst67 * fRec14[0])))) + (fRec12[1] * (fConst69 + ((fRec13[0] * (fConst71 + (fConst73 * fRec14[0]))) + (fConst75 * fRec14[0]))))) + (fRec12[2] * (fConst77 + ((fRec13[0] * (fConst79 + (fConst81 * fRec14[0]))) + (fConst83 * fRec14[0]))))) + (fRec12[3] * (fConst84 + ((fRec13[0] * (fConst85 + (fConst86 * fRec14[0]))) + (fConst87 * fRec14[0]))))) + (fRec12[4] * (fConst88 + ((fRec13[0] * (fConst89 + (fConst90 * fRec14[0]))) + (fConst91 * fRec14[0]))))) + (fRec12[5] * (fConst92 + ((fRec13[0] * (fConst93 + (fConst94 * fRec14[0]))) + (fConst95 * fRec14[0]))))) / fTemp0);
		fVec0[0] = fTemp1;
		fRec11[0] = ((fConst5 * (fTemp1 + fVec0[1])) - (0.86056958506478287 * fRec11[1]));
		fRec10[0] = (fRec11[0] - ((1.8405051250752198 * fRec10[1]) + (0.86129424393186271 * fRec10[2])));
		fRec15[0] = (fConst97 * ((0.027 * (fRec9[1] + fRec9[2])) - (fConst98 * fRec15[1])));
		fRec9[0] = (double(Ftrany(int(TRANY_TABLE_7199P_68k), double((((0.92544984225177063 * (fRec10[0] + fRec10[2])) + (fRec15[0] + (1.8508996845035413 * fRec10[1]))) + -3.5719810000000001)))) + -117.70440740740739);
		fRec8[0] = ((0.025000000000000001 * ((fConst4 * fRec9[0]) + (fConst99 * fRec9[1]))) - (fConst100 * fRec8[1]));
		fRec7[0] = ((0.93028479253239138 * (fRec8[0] + fRec8[1])) - (0.86056958506478287 * fRec7[1]));
		fRec6[0] = (fRec7[0] - ((1.8405051250752198 * fRec6[1]) + (0.86129424393186271 * fRec6[2])));
		fRec16[0] = (fConst97 * ((0.027 * (fRec5[1] + fRec5[2])) - (fConst98 * fRec16[1])));
		fRec5[0] = (double(Ftrany(int(TRANY_TABLE_7199P_68k), double((((0.92544984225177063 * (fRec6[0] + fRec6[2])) + (fRec16[0] + (1.8508996845035413 * fRec6[1]))) + -3.5719810000000001)))) + -117.70440740740739);
		fRec4[0] = ((0.025000000000000001 * ((fConst4 * fRec5[0]) + (fConst99 * fRec5[1]))) - (fConst100 * fRec4[1]));
		fRec3[0] = ((0.93028479253239138 * (fRec4[0] + fRec4[1])) - (0.86056958506478287 * fRec3[1]));
		fRec2[0] = (fRec3[0] - ((1.8405051250752198 * fRec2[1]) + (0.86129424393186271 * fRec2[2])));
		fRec17[0] = (fConst97 * ((0.027 * (fRec1[1] + fRec1[2])) - (fConst98 * fRec17[1])));
		fRec1[0] = (double(Ftrany(int(TRANY_TABLE_7199P_68k), double((((0.92544984225177063 * (fRec2[0] + fRec2[2])) + (fRec17[0] + (1.8508996845035413 * fRec2[1]))) + -3.5719810000000001)))) + -117.70440740740739);
		fRec0[0] = ((0.025000000000000001 * ((fConst4 * fRec1[0]) + (fConst99 * fRec1[1]))) - (fConst100 * fRec0[1]));
		output0[i] = FAUSTFLOAT(fRec0[0]);
		fRec13[1] = fRec13[0];
		fRec14[1] = fRec14[0];
		for (int j0 = 5; (j0 > 0); j0 = (j0 - 1)) {
			fRec12[j0] = fRec12[(j0 - 1)];
		}
		fVec0[1] = fVec0[0];
		fRec11[1] = fRec11[0];
		fRec10[2] = fRec10[1];
		fRec10[1] = fRec10[0];
		fRec15[1] = fRec15[0];
		fRec9[2] = fRec9[1];
		fRec9[1] = fRec9[0];
		fRec8[1] = fRec8[0];
		fRec7[1] = fRec7[0];
		fRec6[2] = fRec6[1];
		fRec6[1] = fRec6[0];
		fRec16[1] = fRec16[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fRec17[1] = fRec17[0];
		fRec1[2] = fRec1[1];
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
		fVslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case VOLUME: 
		fVslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
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
