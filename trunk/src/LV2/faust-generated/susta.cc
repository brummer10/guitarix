// generated from file '../src/LV2/faust/susta.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "trany.h"

namespace susta {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	double fConst0;
	double fConst2;
	double fConst3;
	double fConst4;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec13[2];
	double fConst6;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec14[2];
	double fConst8;
	double fConst10;
	double fConst12;
	double fConst14;
	double fConst16;
	double fConst18;
	double fConst20;
	double fConst22;
	double fConst24;
	double fConst26;
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
	double fConst42;
	double fConst44;
	double fConst46;
	double fConst48;
	double fConst50;
	double fConst52;
	double fConst53;
	double fConst54;
	double fConst55;
	double fConst56;
	double fConst57;
	double fConst58;
	double fRec12[6];
	double fConst60;
	double fConst62;
	double fConst64;
	double fConst66;
	double fConst68;
	double fConst70;
	double fConst72;
	double fConst74;
	double fConst76;
	double fConst78;
	double fConst80;
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
	double fVec0[2];
	double fRec11[2];
	double fRec10[3];
	double fRec9[2];
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec13[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec14[l1] = 0.0;
	for (int l2 = 0; (l2 < 6); l2 = (l2 + 1)) fRec12[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fVec0[l3] = 0.0;
	for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) fRec11[l4] = 0.0;
	for (int l5 = 0; (l5 < 3); l5 = (l5 + 1)) fRec10[l5] = 0.0;
	for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) fRec9[l6] = 0.0;
	for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) fRec8[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fRec7[l8] = 0.0;
	for (int l9 = 0; (l9 < 3); l9 = (l9 + 1)) fRec6[l9] = 0.0;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) fRec5[l10] = 0.0;
	for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) fRec4[l11] = 0.0;
	for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) fRec3[l12] = 0.0;
	for (int l13 = 0; (l13 < 3); l13 = (l13 + 1)) fRec2[l13] = 0.0;
	for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) fRec1[l14] = 0.0;
	for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) fRec0[l15] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = (3.1415926535897931 / fConst0);
	fConst2 = (1.0 / (fConst1 + 1.0));
	fConst3 = (1.0 - fConst1);
	fConst4 = (0.93028479253239138 * mydsp_faustpower3_f(fConst0));
	double fConst5 = (5.1986513420818397e-24 * fConst0);
	fConst6 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst5 + 1.7153563146327399e-19)) + 1.41224926366503e-16)) + -3.7718569868030302e-15)) + -9.9095275604879496e-14);
	double fConst7 = (2.5377268129031099e-23 * fConst0);
	fConst8 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst7 + 2.10184078089632e-19)) + 1.4746084952545501e-16)) + -2.8103491919263598e-15)) + -3.8745627763789799e-14);
	double fConst9 = (2.5554575353749899e-23 * fConst0);
	fConst10 = (fConst0 * ((fConst0 * ((fConst0 * (-2.0966224746914901e-19 - fConst9)) + -1.4095256819997e-16)) + 1.7564684586251401e-15));
	double fConst11 = (7.9444263598425703e-24 * fConst0);
	fConst12 = ((fConst0 * ((fConst0 * ((fConst0 * (-1.8431345115767401e-19 - fConst11)) + -1.4867852143994001e-16)) + 4.14135154627774e-15)) + 1.1408637802285001e-13);
	double fConst13 = (4.9224951879988899e-23 * fConst0);
	fConst14 = ((fConst0 * ((fConst0 * ((fConst0 * (-2.8282985219400499e-19 - fConst13)) + -1.7842131276678399e-16)) + 3.3977551244592401e-15)) + 4.6832453671078502e-14);
	double fConst15 = (4.9568879349265099e-23 * fConst0);
	fConst16 = (fConst0 * ((fConst0 * ((fConst0 * (fConst15 + 2.80945197437672e-19)) + 1.70486053448624e-16)) + -2.12307123308889e-15));
	double fConst17 = (1.03973026841637e-23 * fConst0);
	fConst18 = ((fConst0 * ((fConst0 * ((fConst0 * (-1.1435708764218199e-19 - fConst17)) + 2.8244985273300699e-16)) + 7.5437139736060604e-15)) + -6.6063517069919597e-14);
	double fConst19 = (5.0754536258062098e-23 * fConst0);
	fConst20 = ((fConst0 * ((fConst0 * ((fConst0 * (-1.40122718726421e-19 - fConst19)) + 2.94921699050911e-16)) + 5.6206983838527196e-15)) + -2.5830418509193201e-14);
	double fConst21 = (5.1109150707499798e-23 * fConst0);
	fConst22 = (fConst0 * ((fConst0 * ((fConst0 * (fConst21 + 1.3977483164610001e-19)) + -2.8190513639994098e-16)) + -3.5129369172502802e-15));
	double fConst23 = (1.5888852719685099e-23 * fConst0);
	fConst24 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst23 + 1.22875634105116e-19)) + -2.97357042879881e-16)) + -8.2827030925554799e-15)) + 7.6057585348566401e-14);
	double fConst25 = (9.8449903759977797e-23 * fConst0);
	fConst26 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst25 + 1.88553234796003e-19)) + -3.5684262553356798e-16)) + -6.7955102489184699e-15)) + 3.1221635780719003e-14);
	double fConst27 = (9.9137758698530105e-23 * fConst0);
	fConst28 = (fConst0 * ((fConst0 * ((fConst0 * (-1.87296798291781e-19 - fConst27)) + 3.40972106897249e-16)) + 4.2461424661777799e-15));
	fConst29 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst17 + -1.1435708764218199e-19)) + -2.8244985273300699e-16)) + 7.5437139736060604e-15)) + 6.6063517069919597e-14);
	fConst30 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst19 + -1.40122718726421e-19)) + -2.94921699050911e-16)) + 5.6206983838527196e-15)) + 2.5830418509193201e-14);
	fConst31 = (fConst0 * ((fConst0 * ((fConst0 * (1.3977483164610001e-19 - fConst21)) + 2.8190513639994098e-16)) + -3.5129369172502802e-15));
	fConst32 = ((fConst0 * ((fConst0 * ((fConst0 * (1.22875634105116e-19 - fConst23)) + 2.97357042879881e-16)) + -8.2827030925554799e-15)) + -7.6057585348566401e-14);
	fConst33 = ((fConst0 * ((fConst0 * ((fConst0 * (1.88553234796003e-19 - fConst25)) + 3.5684262553356798e-16)) + -6.7955102489184699e-15)) + -3.1221635780719003e-14);
	fConst34 = (fConst0 * ((fConst0 * ((fConst0 * (fConst27 + -1.87296798291781e-19)) + -3.40972106897249e-16)) + 4.2461424661777799e-15));
	fConst35 = ((fConst0 * ((fConst0 * ((fConst0 * (1.7153563146327399e-19 - fConst5)) + -1.41224926366503e-16)) + -3.7718569868030302e-15)) + 9.9095275604879496e-14);
	fConst36 = ((fConst0 * ((fConst0 * ((fConst0 * (2.10184078089632e-19 - fConst7)) + -1.4746084952545501e-16)) + -2.8103491919263598e-15)) + 3.8745627763789799e-14);
	fConst37 = (fConst0 * ((fConst0 * ((fConst0 * (fConst9 + -2.0966224746914901e-19)) + 1.4095256819997e-16)) + 1.7564684586251401e-15));
	fConst38 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst11 + -1.8431345115767401e-19)) + 1.4867852143994001e-16)) + 4.14135154627774e-15)) + -1.1408637802285001e-13);
	fConst39 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst13 + -2.8282985219400499e-19)) + 1.7842131276678399e-16)) + 3.3977551244592401e-15)) + -4.6832453671078502e-14);
	fConst40 = (fConst0 * ((fConst0 * ((fConst0 * (2.80945197437672e-19 - fConst15)) + -1.70486053448624e-16)) + -2.12307123308889e-15));
	double fConst41 = (1.03973026841637e-24 * fConst0);
	fConst42 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst41 + -5.7178543821091199e-20)) + 1.41224926366503e-16)) + -3.7718569868030302e-15)) + 3.3031758534959798e-14);
	double fConst43 = (5.07545362580621e-24 * fConst0);
	fConst44 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst43 + -7.0061359363210703e-20)) + 1.4746084952545501e-16)) + -2.8103491919263598e-15)) + 1.2915209254596601e-14);
	double fConst45 = (5.1109150707499797e-24 * fConst0);
	fConst46 = (fConst0 * ((fConst0 * ((fConst0 * (6.9887415823049801e-20 - fConst45)) + -1.4095256819997e-16)) + 1.7564684586251401e-15));
	double fConst47 = (1.58888527196851e-24 * fConst0);
	fConst48 = ((fConst0 * ((fConst0 * ((fConst0 * (6.1437817052558098e-20 - fConst47)) + -1.4867852143994001e-16)) + 4.14135154627774e-15)) + -3.80287926742832e-14);
	double fConst49 = (9.84499037599778e-24 * fConst0);
	fConst50 = ((fConst0 * ((fConst0 * ((fConst0 * (9.42766173980015e-20 - fConst49)) + -1.7842131276678399e-16)) + 3.3977551244592401e-15)) + -1.5610817890359502e-14);
	double fConst51 = (9.9137758698530105e-24 * fConst0);
	fConst52 = (fConst0 * ((fConst0 * ((fConst0 * (fConst51 + -9.3648399145890596e-20)) + 1.70486053448624e-16)) + -2.12307123308889e-15));
	fConst53 = ((fConst0 * ((fConst0 * ((fConst0 * (-5.7178543821091199e-20 - fConst41)) + -1.41224926366503e-16)) + -3.7718569868030302e-15)) + -3.3031758534959798e-14);
	fConst54 = ((fConst0 * ((fConst0 * ((fConst0 * (-7.0061359363210703e-20 - fConst43)) + -1.4746084952545501e-16)) + -2.8103491919263598e-15)) + -1.2915209254596601e-14);
	fConst55 = (fConst0 * ((fConst0 * ((fConst0 * (fConst45 + 6.9887415823049801e-20)) + 1.4095256819997e-16)) + 1.7564684586251401e-15));
	fConst56 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst47 + 6.1437817052558098e-20)) + 1.4867852143994001e-16)) + 4.14135154627774e-15)) + 3.80287926742832e-14);
	fConst57 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst49 + 9.42766173980015e-20)) + 1.7842131276678399e-16)) + 3.3977551244592401e-15)) + 1.5610817890359502e-14);
	fConst58 = (fConst0 * ((fConst0 * ((fConst0 * (-9.3648399145890596e-20 - fConst51)) + -1.70486053448624e-16)) + -2.12307123308889e-15));
	double fConst59 = (4.0724943902439398e-29 * fConst0);
	fConst60 = ((fConst0 * (fConst59 + -1.3411884984281801e-22)) + 1.2352517755682401e-17);
	double fConst61 = (3.9514408494262001e-29 * fConst0);
	fConst62 = ((fConst0 * (1.2630090717698801e-22 - fConst61)) + 2.6890421358576598e-19);
	double fConst63 = (3.9514408494262003e-27 * fConst0);
	fConst64 = ((fConst0 * (1.26300907176988e-20 - fConst63)) + 2.6890421358576598e-17);
	double fConst65 = (4.0724943902439399e-27 * fConst0);
	fConst66 = ((fConst0 * (fConst65 + -1.3411884984281799e-20)) + 1.23525177556824e-15);
	double fConst67 = (2.0362471951219699e-28 * fConst0);
	fConst68 = ((fConst0 * (4.02356549528453e-22 - fConst67)) + -1.2352517755682401e-17);
	double fConst69 = (1.9757204247131001e-28 * fConst0);
	fConst70 = ((fConst0 * (fConst69 + -3.78902721530964e-22)) + -2.6890421358576598e-19);
	double fConst71 = (1.9757204247130999e-26 * fConst0);
	fConst72 = ((fConst0 * (fConst71 + -3.7890272153096399e-20)) + -2.6890421358576598e-17);
	double fConst73 = (2.03624719512197e-26 * fConst0);
	fConst74 = ((fConst0 * (4.0235654952845302e-20 - fConst73)) + -1.23525177556824e-15);
	double fConst75 = (4.0724943902439399e-28 * fConst0);
	fConst76 = ((fConst0 * (fConst75 + -2.6823769968563499e-22)) + -2.47050355113649e-17);
	double fConst77 = (3.9514408494262001e-28 * fConst0);
	fConst78 = ((fConst0 * (2.5260181435397602e-22 - fConst77)) + -5.3780842717153195e-19);
	double fConst79 = (3.9514408494261998e-26 * fConst0);
	fConst80 = ((fConst0 * (2.5260181435397601e-20 - fConst79)) + -5.3780842717153197e-17);
	double fConst81 = (4.07249439024394e-26 * fConst0);
	fConst82 = ((fConst0 * (fConst81 + -2.6823769968563499e-20)) + -2.4705035511364902e-15);
	fConst83 = ((fConst0 * (-2.6823769968563499e-22 - fConst75)) + 2.47050355113649e-17);
	fConst84 = ((fConst0 * (fConst77 + 2.5260181435397602e-22)) + 5.3780842717153195e-19);
	fConst85 = ((fConst0 * (fConst79 + 2.5260181435397601e-20)) + 5.3780842717153197e-17);
	fConst86 = ((fConst0 * (-2.6823769968563499e-20 - fConst81)) + 2.4705035511364902e-15);
	fConst87 = ((fConst0 * (fConst67 + 4.02356549528453e-22)) + 1.2352517755682401e-17);
	fConst88 = ((fConst0 * (-3.78902721530964e-22 - fConst69)) + 2.6890421358576598e-19);
	fConst89 = ((fConst0 * (-3.7890272153096399e-20 - fConst71)) + 2.6890421358576598e-17);
	fConst90 = ((fConst0 * (fConst73 + 4.0235654952845302e-20)) + 1.23525177556824e-15);
	fConst91 = ((fConst0 * (-1.3411884984281801e-22 - fConst59)) + -1.2352517755682401e-17);
	fConst92 = ((fConst0 * (fConst61 + 1.2630090717698801e-22)) + -2.6890421358576598e-19);
	fConst93 = ((fConst0 * (fConst63 + 1.26300907176988e-20)) + -2.6890421358576598e-17);
	fConst94 = ((fConst0 * (-1.3411884984281799e-20 - fConst65)) + -1.23525177556824e-15);
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
	for (int i0 = 0; (i0 < count); i0 = (i0 + 1)) {
		fRec13[0] = (fSlow0 + (0.99299999999999999 * fRec13[1]));
		fRec14[0] = (fSlow1 + (0.99299999999999999 * fRec14[1]));
		double fTemp0 = (((fRec13[0] * ((fConst0 * (fConst53 + (fRec14[0] * (fConst54 + (fConst55 * fRec14[0]))))) + -9.4964773930857394e-14)) + (fConst0 * (fConst56 + (fRec14[0] * (fConst57 + (fConst58 * fRec14[0])))))) + 1.1478542566440801e-13);
		fRec12[0] = (double(input0[i0]) - ((((((fRec12[1] * (((fRec13[0] * ((fConst0 * (fConst6 + (fRec14[0] * (fConst8 + (fConst10 * fRec14[0]))))) + -4.7482386965428703e-13)) + (fConst0 * (fConst12 + (fRec14[0] * (fConst14 + (fConst16 * fRec14[0])))))) + 5.7392712832203995e-13)) + (fRec12[2] * (((fRec13[0] * ((fConst0 * (fConst18 + (fRec14[0] * (fConst20 + (fConst22 * fRec14[0]))))) + -9.4964773930857407e-13)) + (fConst0 * (fConst24 + (fRec14[0] * (fConst26 + (fConst28 * fRec14[0])))))) + 1.1478542566440799e-12))) + (fRec12[3] * (((fRec13[0] * ((fConst0 * (fConst29 + (fRec14[0] * (fConst30 + (fConst31 * fRec14[0]))))) + -9.4964773930857407e-13)) + (fConst0 * (fConst32 + (fRec14[0] * (fConst33 + (fConst34 * fRec14[0])))))) + 1.1478542566440799e-12))) + (fRec12[4] * (((fRec13[0] * ((fConst0 * (fConst35 + (fRec14[0] * (fConst36 + (fConst37 * fRec14[0]))))) + -4.7482386965428703e-13)) + (fConst0 * (fConst38 + (fRec14[0] * (fConst39 + (fConst40 * fRec14[0])))))) + 5.7392712832203995e-13))) + (fRec12[5] * (((fRec13[0] * ((fConst0 * (fConst42 + (fRec14[0] * (fConst44 + (fConst46 * fRec14[0]))))) + -9.4964773930857394e-14)) + (fConst0 * (fConst48 + (fRec14[0] * (fConst50 + (fConst52 * fRec14[0])))))) + 1.1478542566440801e-13))) / fTemp0));
		double fTemp1 = (((((((fRec12[0] * (fConst60 + ((fRec13[0] * (fConst62 + (fConst64 * fRec14[0]))) + (fConst66 * fRec14[0])))) + (fRec12[1] * (fConst68 + ((fRec13[0] * (fConst70 + (fConst72 * fRec14[0]))) + (fConst74 * fRec14[0]))))) + (fRec12[2] * (fConst76 + ((fRec13[0] * (fConst78 + (fConst80 * fRec14[0]))) + (fConst82 * fRec14[0]))))) + (fRec12[3] * (fConst83 + ((fRec13[0] * (fConst84 + (fConst85 * fRec14[0]))) + (fConst86 * fRec14[0]))))) + (fRec12[4] * (fConst87 + ((fRec13[0] * (fConst88 + (fConst89 * fRec14[0]))) + (fConst90 * fRec14[0]))))) + (fRec12[5] * (fConst91 + ((fRec13[0] * (fConst92 + (fConst93 * fRec14[0]))) + (fConst94 * fRec14[0]))))) / fTemp0);
		fVec0[0] = fTemp1;
		fRec11[0] = ((fConst4 * (fTemp1 + fVec0[1])) - (0.86056958506478287 * fRec11[1]));
		fRec10[0] = (fRec11[0] - ((1.8405051250752198 * fRec10[1]) + (0.86129424393186271 * fRec10[2])));
		double fTemp2 = ((1.8508996845035413 * fRec10[1]) + (0.92544984225177063 * (fRec10[0] + fRec10[2])));
		double fTemp3 = double(Ftrany(int(TRANY_TABLE_7199P_68k), double(((fTemp2 + (2700.0 * (fTemp2 / (double(Rtrany(int(TRANY_TABLE_7199P_68k), double(fRec9[1]))) + 100000.0)))) + -3.5719810000000001))));
		fRec9[0] = ((fTemp3 + (0.001322955925925926 * (double(Rtrany(int(TRANY_TABLE_7199P_68k), double(fTemp3))) + 100000.0))) + -250.0);
		fRec8[0] = (fConst2 * ((fConst3 * fRec8[1]) + (0.025000000000000001 * (fRec9[0] - fRec9[1]))));
		fRec7[0] = ((0.93028479253239138 * (fRec8[0] + fRec8[1])) - (0.86056958506478287 * fRec7[1]));
		fRec6[0] = (fRec7[0] - ((1.8405051250752198 * fRec6[1]) + (0.86129424393186271 * fRec6[2])));
		double fTemp4 = ((1.8508996845035413 * fRec6[1]) + (0.92544984225177063 * (fRec6[0] + fRec6[2])));
		double fTemp5 = double(Ftrany(int(TRANY_TABLE_7199P_68k), double(((fTemp4 + (2700.0 * (fTemp4 / (double(Rtrany(int(TRANY_TABLE_7199P_68k), double(fRec5[1]))) + 100000.0)))) + -3.5719810000000001))));
		fRec5[0] = ((fTemp5 + (0.001322955925925926 * (double(Rtrany(int(TRANY_TABLE_7199P_68k), double(fTemp5))) + 100000.0))) + -250.0);
		fRec4[0] = (fConst2 * ((fConst3 * fRec4[1]) + (0.025000000000000001 * (fRec5[0] - fRec5[1]))));
		fRec3[0] = ((0.93028479253239138 * (fRec4[0] + fRec4[1])) - (0.86056958506478287 * fRec3[1]));
		fRec2[0] = (fRec3[0] - ((1.8405051250752198 * fRec2[1]) + (0.86129424393186271 * fRec2[2])));
		double fTemp6 = ((1.8508996845035413 * fRec2[1]) + (0.92544984225177063 * (fRec2[0] + fRec2[2])));
		double fTemp7 = double(Ftrany(int(TRANY_TABLE_7199P_68k), double(((fTemp6 + (2700.0 * (fTemp6 / (double(Rtrany(int(TRANY_TABLE_7199P_68k), double(fRec1[1]))) + 100000.0)))) + -3.5719810000000001))));
		fRec1[0] = ((fTemp7 + (0.001322955925925926 * (double(Rtrany(int(TRANY_TABLE_7199P_68k), double(fTemp7))) + 100000.0))) + -250.0);
		fRec0[0] = (fConst2 * ((fConst3 * fRec0[1]) + (0.025000000000000001 * (fRec1[0] - fRec1[1]))));
		output0[i0] = FAUSTFLOAT(fRec0[0]);
		fRec13[1] = fRec13[0];
		fRec14[1] = fRec14[0];
		for (int j0 = 5; (j0 > 0); j0 = (j0 - 1)) {
			fRec12[j0] = fRec12[(j0 - 1)];
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
