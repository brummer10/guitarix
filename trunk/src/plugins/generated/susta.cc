// generated from file '../src/plugins/susta.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

#include "trany.h"

namespace pluginlib {
namespace susta {

class Dsp: public PluginDef {
private:
	int fSampleRate;
	double fConst0;
	double fConst1;
	double fConst3;
	FAUSTFLOAT fVslider0;
	double fRec1[2];
	double fConst5;
	double fConst7;
	double fConst9;
	double fConst11;
	double fConst13;
	double fConst15;
	double fConst17;
	double fConst19;
	double fConst21;
	double fConst23;
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
	double fConst39;
	double fConst41;
	double fConst43;
	double fConst45;
	double fConst47;
	double fConst49;
	double fConst50;
	double fConst51;
	double fConst52;
	double fConst53;
	double fConst54;
	double fConst55;
	double fRec0[6];
	double fConst57;
	double fConst59;
	double fConst61;
	double fConst63;
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
	double 	fRecV0[2];
	void clear_state_f();
	int load_ui_f(const UiBuilder& b, int form);
	static const char *glade_def;
	void init(unsigned int sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static int load_ui_f_static(const UiBuilder& b, int form);
	static void init_static(unsigned int sample_rate, PluginDef*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef*);
	static int register_params_static(const ParamReg& reg);
	static void del_instance(PluginDef *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginDef() {
	version = PLUGINDEF_VERSION;
	flags = 0;
	id = "susta";
	name = N_("Sustainer");
	groups = 0;
	description = N_("Sustainer"); // description (tooltip)
	category = N_("Fuzz");       // category
	shortname = N_("Sustainer");     // shortname
	mono_audio = compute_static;
	stereo_audio = 0;
	set_samplerate = init_static;
	activate_plugin = 0;
	register_params = register_params_static;
	load_ui = load_ui_f_static;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec1[l0] = 0.0;
	for (int l1 = 0; (l1 < 6); l1 = (l1 + 1)) fRec0[l1] = 0.0;

	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fVecCl0[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRecCl7[l1] = 0.0;
	for (int l2 = 0; (l2 < 3); l2 = (l2 + 1)) fRecCl6[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fRecCl8[l3] = 0.0;
	for (int l4 = 0; (l4 < 3); l4 = (l4 + 1)) fRecCl5[l4] = 0.0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fRecCl4[l5] = 0.0;
	for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) fRecCl3[l6] = 0.0;
	for (int l7 = 0; (l7 < 3); l7 = (l7 + 1)) fRecCl2[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fRecCl9[l8] = 0.0;
	for (int l9 = 0; (l9 < 3); l9 = (l9 + 1)) fRecCl1[l9] = 0.0;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) fRecCl0[l10] = 0.0;

	for (int i=0; i<2; i++) fRecV0[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = mydsp_faustpower3_f(fConst0);
	double fConst2 = (7.9444263598425703e-24 * fConst0);
	fConst3 = ((fConst0 * ((fConst0 * ((fConst0 * (-1.8431345115767401e-19 - fConst2)) + -1.4867852143994001e-16)) + 4.14135154627774e-15)) + 1.1408637802285001e-13);
	double fConst4 = (4.9224951879988899e-23 * fConst0);
	fConst5 = ((fConst0 * ((fConst0 * ((fConst0 * (-2.8282985219400499e-19 - fConst4)) + -1.7842131276678399e-16)) + 3.3977551244592401e-15)) + 4.6832453671078502e-14);
	double fConst6 = (4.9568879349265099e-23 * fConst0);
	fConst7 = (fConst0 * ((fConst0 * ((fConst0 * (fConst6 + 2.80945197437672e-19)) + 1.70486053448624e-16)) + -2.12307123308889e-15));
	double fConst8 = (5.1986513420818397e-24 * fConst0);
	fConst9 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst8 + 1.7153563146327399e-19)) + 1.41224926366503e-16)) + -3.7718569868030302e-15)) + -9.9095275604879496e-14);
	double fConst10 = (2.5377268129031099e-23 * fConst0);
	fConst11 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst10 + 2.10184078089632e-19)) + 1.4746084952545501e-16)) + -2.8103491919263598e-15)) + -3.8745627763789799e-14);
	double fConst12 = (2.5554575353749899e-23 * fConst0);
	fConst13 = (fConst0 * ((fConst0 * ((fConst0 * (-2.0966224746914901e-19 - fConst12)) + -1.4095256819997e-16)) + 1.7564684586251401e-15));
	double fConst14 = (1.5888852719685099e-23 * fConst0);
	fConst15 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst14 + 1.22875634105116e-19)) + -2.97357042879881e-16)) + -8.2827030925554799e-15)) + 7.6057585348566401e-14);
	double fConst16 = (9.8449903759977797e-23 * fConst0);
	fConst17 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst16 + 1.88553234796003e-19)) + -3.5684262553356798e-16)) + -6.7955102489184699e-15)) + 3.1221635780719003e-14);
	double fConst18 = (9.9137758698530105e-23 * fConst0);
	fConst19 = (fConst0 * ((fConst0 * ((fConst0 * (-1.87296798291781e-19 - fConst18)) + 3.40972106897249e-16)) + 4.2461424661777799e-15));
	double fConst20 = (1.03973026841637e-23 * fConst0);
	fConst21 = ((fConst0 * ((fConst0 * ((fConst0 * (-1.1435708764218199e-19 - fConst20)) + 2.8244985273300699e-16)) + 7.5437139736060604e-15)) + -6.6063517069919597e-14);
	double fConst22 = (5.0754536258062098e-23 * fConst0);
	fConst23 = ((fConst0 * ((fConst0 * ((fConst0 * (-1.40122718726421e-19 - fConst22)) + 2.94921699050911e-16)) + 5.6206983838527196e-15)) + -2.5830418509193201e-14);
	double fConst24 = (5.1109150707499798e-23 * fConst0);
	fConst25 = (fConst0 * ((fConst0 * ((fConst0 * (fConst24 + 1.3977483164610001e-19)) + -2.8190513639994098e-16)) + -3.5129369172502802e-15));
	fConst26 = ((fConst0 * ((fConst0 * ((fConst0 * (1.22875634105116e-19 - fConst14)) + 2.97357042879881e-16)) + -8.2827030925554799e-15)) + -7.6057585348566401e-14);
	fConst27 = ((fConst0 * ((fConst0 * ((fConst0 * (1.88553234796003e-19 - fConst16)) + 3.5684262553356798e-16)) + -6.7955102489184699e-15)) + -3.1221635780719003e-14);
	fConst28 = (fConst0 * ((fConst0 * ((fConst0 * (fConst18 + -1.87296798291781e-19)) + -3.40972106897249e-16)) + 4.2461424661777799e-15));
	fConst29 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst20 + -1.1435708764218199e-19)) + -2.8244985273300699e-16)) + 7.5437139736060604e-15)) + 6.6063517069919597e-14);
	fConst30 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst22 + -1.40122718726421e-19)) + -2.94921699050911e-16)) + 5.6206983838527196e-15)) + 2.5830418509193201e-14);
	fConst31 = (fConst0 * ((fConst0 * ((fConst0 * (1.3977483164610001e-19 - fConst24)) + 2.8190513639994098e-16)) + -3.5129369172502802e-15));
	fConst32 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst2 + -1.8431345115767401e-19)) + 1.4867852143994001e-16)) + 4.14135154627774e-15)) + -1.1408637802285001e-13);
	fConst33 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst4 + -2.8282985219400499e-19)) + 1.7842131276678399e-16)) + 3.3977551244592401e-15)) + -4.6832453671078502e-14);
	fConst34 = (fConst0 * ((fConst0 * ((fConst0 * (2.80945197437672e-19 - fConst6)) + -1.70486053448624e-16)) + -2.12307123308889e-15));
	fConst35 = ((fConst0 * ((fConst0 * ((fConst0 * (1.7153563146327399e-19 - fConst8)) + -1.41224926366503e-16)) + -3.7718569868030302e-15)) + 9.9095275604879496e-14);
	fConst36 = ((fConst0 * ((fConst0 * ((fConst0 * (2.10184078089632e-19 - fConst10)) + -1.4746084952545501e-16)) + -2.8103491919263598e-15)) + 3.8745627763789799e-14);
	fConst37 = (fConst0 * ((fConst0 * ((fConst0 * (fConst12 + -2.0966224746914901e-19)) + 1.4095256819997e-16)) + 1.7564684586251401e-15));
	double fConst38 = (1.58888527196851e-24 * fConst0);
	fConst39 = ((fConst0 * ((fConst0 * ((fConst0 * (6.1437817052558098e-20 - fConst38)) + -1.4867852143994001e-16)) + 4.14135154627774e-15)) + -3.80287926742832e-14);
	double fConst40 = (9.84499037599778e-24 * fConst0);
	fConst41 = ((fConst0 * ((fConst0 * ((fConst0 * (9.42766173980015e-20 - fConst40)) + -1.7842131276678399e-16)) + 3.3977551244592401e-15)) + -1.5610817890359502e-14);
	double fConst42 = (9.9137758698530105e-24 * fConst0);
	fConst43 = (fConst0 * ((fConst0 * ((fConst0 * (fConst42 + -9.3648399145890596e-20)) + 1.70486053448624e-16)) + -2.12307123308889e-15));
	double fConst44 = (1.03973026841637e-24 * fConst0);
	fConst45 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst44 + -5.7178543821091199e-20)) + 1.41224926366503e-16)) + -3.7718569868030302e-15)) + 3.3031758534959798e-14);
	double fConst46 = (5.07545362580621e-24 * fConst0);
	fConst47 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst46 + -7.0061359363210703e-20)) + 1.4746084952545501e-16)) + -2.8103491919263598e-15)) + 1.2915209254596601e-14);
	double fConst48 = (5.1109150707499797e-24 * fConst0);
	fConst49 = (fConst0 * ((fConst0 * ((fConst0 * (6.9887415823049801e-20 - fConst48)) + -1.4095256819997e-16)) + 1.7564684586251401e-15));
	fConst50 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst38 + 6.1437817052558098e-20)) + 1.4867852143994001e-16)) + 4.14135154627774e-15)) + 3.80287926742832e-14);
	fConst51 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst40 + 9.42766173980015e-20)) + 1.7842131276678399e-16)) + 3.3977551244592401e-15)) + 1.5610817890359502e-14);
	fConst52 = (fConst0 * ((fConst0 * ((fConst0 * (-9.3648399145890596e-20 - fConst42)) + -1.70486053448624e-16)) + -2.12307123308889e-15));
	fConst53 = ((fConst0 * ((fConst0 * ((fConst0 * (-5.7178543821091199e-20 - fConst44)) + -1.41224926366503e-16)) + -3.7718569868030302e-15)) + -3.3031758534959798e-14);
	fConst54 = ((fConst0 * ((fConst0 * ((fConst0 * (-7.0061359363210703e-20 - fConst46)) + -1.4746084952545501e-16)) + -2.8103491919263598e-15)) + -1.2915209254596601e-14);
	fConst55 = (fConst0 * ((fConst0 * ((fConst0 * (fConst48 + 6.9887415823049801e-20)) + 1.4095256819997e-16)) + 1.7564684586251401e-15));
	double fConst56 = (4.0724943902439398e-29 * fConst0);
	fConst57 = ((fConst0 * (fConst56 + -1.3411884984281801e-22)) + 1.2352517755682401e-17);
	double fConst58 = (3.9514408494262001e-29 * fConst0);
	fConst59 = ((fConst0 * (1.2630090717698801e-22 - fConst58)) + 2.6890421358576598e-19);
	double fConst60 = (3.9514408494262003e-27 * fConst0);
	fConst61 = ((fConst0 * (1.26300907176988e-20 - fConst60)) + 2.6890421358576598e-17);
	double fConst62 = (4.0724943902439399e-27 * fConst0);
	fConst63 = ((fConst0 * (fConst62 + -1.3411884984281799e-20)) + 1.23525177556824e-15);
	double fConst64 = (2.0362471951219699e-28 * fConst0);
	fConst65 = ((fConst0 * (4.02356549528453e-22 - fConst64)) + -1.2352517755682401e-17);
	double fConst66 = (1.9757204247131001e-28 * fConst0);
	fConst67 = ((fConst0 * (fConst66 + -3.78902721530964e-22)) + -2.6890421358576598e-19);
	double fConst68 = (1.9757204247130999e-26 * fConst0);
	fConst69 = ((fConst0 * (fConst68 + -3.7890272153096399e-20)) + -2.6890421358576598e-17);
	double fConst70 = (2.03624719512197e-26 * fConst0);
	fConst71 = ((fConst0 * (4.0235654952845302e-20 - fConst70)) + -1.23525177556824e-15);
	double fConst72 = (4.0724943902439399e-28 * fConst0);
	fConst73 = ((fConst0 * (fConst72 + -2.6823769968563499e-22)) + -2.47050355113649e-17);
	double fConst74 = (3.9514408494262001e-28 * fConst0);
	fConst75 = ((fConst0 * (2.5260181435397602e-22 - fConst74)) + -5.3780842717153195e-19);
	double fConst76 = (3.9514408494261998e-26 * fConst0);
	fConst77 = ((fConst0 * (2.5260181435397601e-20 - fConst76)) + -5.3780842717153197e-17);
	double fConst78 = (4.07249439024394e-26 * fConst0);
	fConst79 = ((fConst0 * (fConst78 + -2.6823769968563499e-20)) + -2.4705035511364902e-15);
	fConst80 = ((fConst0 * (-2.6823769968563499e-22 - fConst72)) + 2.47050355113649e-17);
	fConst81 = ((fConst0 * (fConst74 + 2.5260181435397602e-22)) + 5.3780842717153195e-19);
	fConst82 = ((fConst0 * (fConst76 + 2.5260181435397601e-20)) + 5.3780842717153197e-17);
	fConst83 = ((fConst0 * (-2.6823769968563499e-20 - fConst78)) + 2.4705035511364902e-15);
	fConst84 = ((fConst0 * (fConst64 + 4.02356549528453e-22)) + 1.2352517755682401e-17);
	fConst85 = ((fConst0 * (-3.78902721530964e-22 - fConst66)) + 2.6890421358576598e-19);
	fConst86 = ((fConst0 * (-3.7890272153096399e-20 - fConst68)) + 2.6890421358576598e-17);
	fConst87 = ((fConst0 * (fConst70 + 4.0235654952845302e-20)) + 1.23525177556824e-15);
	fConst88 = ((fConst0 * (-1.3411884984281801e-22 - fConst56)) + -1.2352517755682401e-17);
	fConst89 = ((fConst0 * (fConst58 + 1.2630090717698801e-22)) + -2.6890421358576598e-19);
	fConst90 = ((fConst0 * (fConst60 + 1.26300907176988e-20)) + -2.6890421358576598e-17);
	fConst91 = ((fConst0 * (-1.3411884984281799e-20 - fConst62)) + -1.23525177556824e-15);

	sample_rate = 96000;
	smpCl.setup(fSampleRate, sample_rate);
	fSampleRate = sample_rate;
	double fConstCl0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	double fConstCl1 = std::tan((97.389372261283583 / fConstCl0));
	double fConstCl2 = (1.0 / fConstCl1);
	double fConstCl3 = (fConstCl2 + 1.0);
	fConstCl4 = (1.0 / (fConstCl1 * fConstCl3));
	double fConstCl5 = (1.0 / std::tan((270.1769682087222 / fConstCl0)));
	fConstCl6 = (1.0 / (fConstCl5 + 1.0));
	fConstCl7 = (1.0 - fConstCl5);
	fConstCl8 = (0.0 - fConstCl4);
	fConstCl9 = ((1.0 - fConstCl2) / fConstCl3);

	clear_state_f();
}

void Dsp::init_static(unsigned int sample_rate, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlowV0 = (0.0010000000000000009 * double(fsliderV0));

	double fSlow0 = (0.0070000000000000062 * double(fVslider0));
	for (int i0 = 0; (i0 < count); i0 = (i0 + 1)) {
		fRec1[0] = (fSlow0 + (0.99299999999999999 * fRec1[1]));
		double fTemp0 = ((fConst0 * (fConst50 + ((fRec1[0] * (fConst51 + (fConst52 * fRec1[0]))) + (fConst53 + (fRec1[0] * (fConst54 + (fConst55 * fRec1[0]))))))) + 1.9820651733550611e-14);
		fRec0[0] = (double(input0[i0]) - ((((((fRec0[1] * ((fConst0 * (fConst3 + ((fRec1[0] * (fConst5 + (fConst7 * fRec1[0]))) + (fConst9 + (fRec1[0] * (fConst11 + (fConst13 * fRec1[0]))))))) + 9.9103258667752918e-14)) + (fRec0[2] * ((fConst0 * (fConst15 + ((fRec1[0] * (fConst17 + (fConst19 * fRec1[0]))) + (fConst21 + (fRec1[0] * (fConst23 + (fConst25 * fRec1[0]))))))) + 1.9820651733550584e-13))) + (fRec0[3] * ((fConst0 * (fConst26 + ((fRec1[0] * (fConst27 + (fConst28 * fRec1[0]))) + (fConst29 + (fRec1[0] * (fConst30 + (fConst31 * fRec1[0]))))))) + 1.9820651733550584e-13))) + (fRec0[4] * ((fConst0 * (fConst32 + ((fRec1[0] * (fConst33 + (fConst34 * fRec1[0]))) + (fConst35 + (fRec1[0] * (fConst36 + (fConst37 * fRec1[0]))))))) + 9.9103258667752918e-14))) + (fRec0[5] * ((fConst0 * (fConst39 + ((fRec1[0] * (fConst41 + (fConst43 * fRec1[0]))) + (fConst45 + (fRec1[0] * (fConst47 + (fConst49 * fRec1[0]))))))) + 1.9820651733550611e-14))) / fTemp0));
		output0[i0] = FAUSTFLOAT((fConst1 * (((((((fRec0[0] * (fConst57 + ((fConst59 + (fConst61 * fRec1[0])) + (fConst63 * fRec1[0])))) + (fRec0[1] * (fConst65 + ((fConst67 + (fConst69 * fRec1[0])) + (fConst71 * fRec1[0]))))) + (fRec0[2] * (fConst73 + ((fConst75 + (fConst77 * fRec1[0])) + (fConst79 * fRec1[0]))))) + (fRec0[3] * (fConst80 + ((fConst81 + (fConst82 * fRec1[0])) + (fConst83 * fRec1[0]))))) + (fRec0[4] * (fConst84 + ((fConst85 + (fConst86 * fRec1[0])) + (fConst87 * fRec1[0]))))) + (fRec0[5] * (fConst88 + ((fConst89 + (fConst90 * fRec1[0])) + (fConst91 * fRec1[0]))))) / fTemp0)));
		fRec1[1] = fRec1[0];
		for (int j0 = 5; (j0 > 0); j0 = (j0 - 1)) {
			fRec0[j0] = fRec0[(j0 - 1)];
		}
	}

	FAUSTFLOAT bufCl[smpCl.max_out_count(count)];
	int ReCount = smpCl.up(count, output0, bufCl);
	for (int i0 = 0; (i0 < ReCount); i0 = (i0 + 1)) {
		double fTemp0 = double(bufCl[i0]);
		fVecCl0[0] = fTemp0;
		fRecCl7[0] = ((0.93028479253239138 * (fTemp0 + fVecCl0[1])) - (0.86056958506478287 * fRecCl7[1]));
		fRecCl6[0] = (fRecCl7[0] - ((1.8405051250752198 * fRecCl6[1]) + (0.86129424393186271 * fRecCl6[2])));
		fRecCl8[0] = (fConstCl6 * ((0.027 * (fRecCl5[1] + fRecCl5[2])) - (fConstCl7 * fRecCl8[1])));
		fRecCl5[0] = (double(Ftrany(int(TRANY_TABLE_7199P_68k), double((((0.92544984225177063 * (fRecCl6[0] + fRecCl6[2])) + (fRecCl8[0] + (1.8508996845035413 * fRecCl6[1]))) + -3.5719810000000001)))) + -117.70440740740739);
		fRecCl4[0] = ((0.025000000000000001 * ((fConstCl4 * fRecCl5[0]) + (fConstCl8 * fRecCl5[1]))) - (fConstCl9 * fRecCl4[1]));
		fRecCl3[0] = ((0.93028479253239138 * (fRecCl4[0] + fRecCl4[1])) - (0.86056958506478287 * fRecCl3[1]));
		fRecCl2[0] = (fRecCl3[0] - ((1.8405051250752198 * fRecCl2[1]) + (0.86129424393186271 * fRecCl2[2])));
		fRecCl9[0] = (fConstCl6 * ((0.027 * (fRecCl1[1] + fRecCl1[2])) - (fConstCl7 * fRecCl9[1])));
		fRecCl1[0] = (double(Ftrany(int(TRANY_TABLE_7199P_68k), double((((0.92544984225177063 * (fRecCl2[0] + fRecCl2[2])) + (fRecCl9[0] + (1.8508996845035413 * fRecCl2[1]))) + -3.5719810000000001)))) + -117.70440740740739);
		fRecCl0[0] = ((0.025000000000000001 * ((fConstCl4 * fRecCl1[0]) + (fConstCl8 * fRecCl1[1]))) - (fConstCl9 * fRecCl0[1]));
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

}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerFloatVar("susta.Volume",N_("Volume"),"S","",&fsliderV0, 0.5, 0.0, 1, 0.01, 0);
	reg.registerFloatVar("susta.Sustain",N_("Sustain"),"S","",&fVslider0, 0.5, 0.0, 1.0, 0.01, 0);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

const char *Dsp::glade_def = "\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<!-- Generated with glade 3.22.1 -->\n\
<interface>\n\
  <requires lib=\"gtk+\" version=\"3.20\"/>\n\
  <requires lib=\"gxwidgets\" version=\"0.0\"/>\n\
  <object class=\"GtkWindow\" id=\"window1\">\n\
    <property name=\"can_focus\">False</property>\n\
    <child>\n\
      <placeholder/>\n\
    </child>\n\
    <child>\n\
      <object class=\"GtkBox\" id=\"vbox1\">\n\
        <property name=\"visible\">True</property>\n\
        <property name=\"can_focus\">False</property>\n\
        <property name=\"orientation\">vertical</property>\n\
        <child>\n\
          <object class=\"GtkBox\" id=\"rackbox\">\n\
            <property name=\"visible\">True</property>\n\
            <property name=\"can_focus\">False</property>\n\
            <property name=\"spacing\">4</property>\n\
            <child>\n\
              <object class=\"GtkBox\" id=\"hbox1\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">False</property>\n\
                <property name=\"spacing\">10</property>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox2\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label1:rack_label\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSmallKnobR\" id=\"gxbigknob1\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">susta.Sustain</property>\n\
                        <property name=\"label_ref\">label1:rack_label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">False</property>\n\
                    <property name=\"fill\">False</property>\n\
                    <property name=\"position\">0</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox3\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label2:rack_label\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxMidKnob\" id=\"gxbigknob2\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">susta.Volume</property>\n\
                        <property name=\"label_ref\">label2:rack_label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">False</property>\n\
                    <property name=\"fill\">False</property>\n\
                    <property name=\"position\">1</property>\n\
                  </packing>\n\
                </child>\n\
              </object>\n\
              <packing>\n\
                <property name=\"expand\">True</property>\n\
                <property name=\"fill\">False</property>\n\
                <property name=\"pack_type\">end</property>\n\
                <property name=\"position\">0</property>\n\
              </packing>\n\
            </child>\n\
          </object>\n\
          <packing>\n\
            <property name=\"expand\">True</property>\n\
            <property name=\"fill\">False</property>\n\
            <property name=\"position\">0</property>\n\
          </packing>\n\
        </child>\n\
        <child>\n\
          <object class=\"GtkBox\" id=\"minibox\">\n\
            <property name=\"visible\">True</property>\n\
            <property name=\"can_focus\">False</property>\n\
            <property name=\"spacing\">4</property>\n\
            <child>\n\
              <object class=\"GxHSlider\" id=\"gxhslider1\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">True</property>\n\
                <property name=\"receives_default\">True</property>\n\
                <property name=\"round_digits\">0</property>\n\
                <property name=\"var_id\">susta.Sustain</property>\n\
                <property name=\"show_value\">False</property>\n\
                <property name=\"value_position\">right</property>\n\
                <property name=\"value_xalign\">0.52000000000000002</property>\n\
                <property name=\"label_ref\">label0:rack_label</property>\n\
              </object>\n\
              <packing>\n\
                <property name=\"expand\">False</property>\n\
                <property name=\"fill\">False</property>\n\
                <property name=\"position\">0</property>\n\
              </packing>\n\
            </child>\n\
            <child>\n\
              <object class=\"GtkLabel\" id=\"label0:rack_label\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">False</property>\n\
                <property name=\"label\" translatable=\"yes\">Sustain</property>\n\
                <property name=\"xalign\">0</property>\n\
              </object>\n\
              <packing>\n\
                <property name=\"expand\">False</property>\n\
                <property name=\"fill\">False</property>\n\
                <property name=\"position\">1</property>\n\
              </packing>\n\
            </child>\n\
          </object>\n\
          <packing>\n\
            <property name=\"expand\">True</property>\n\
            <property name=\"fill\">True</property>\n\
            <property name=\"position\">1</property>\n\
          </packing>\n\
        </child>\n\
      </object>\n\
    </child>\n\
  </object>\n\
</interface>\n\
";

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_GLADE) {
        b.load_glade(glade_def);
        return 0;
    }
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("susta" "." p)

b.openHorizontalhideBox("");
    b.create_master_slider(PARAM("Sustain"), N_("Sustain"));
b.closeBox();
b.openHorizontalBox("");

    b.create_small_rackknobr(PARAM("Sustain"), N_("Sustain"));

    b.create_small_rackknobr(PARAM("Volume"), N_("Volume"));
b.closeBox();

#undef PARAM
        return 0;
    }
	return -1;
}

int Dsp::load_ui_f_static(const UiBuilder& b, int form)
{
	return static_cast<Dsp*>(b.plugin)->load_ui_f(b, form);
}
PluginDef *plugin() {
	return new Dsp();
}

void Dsp::del_instance(PluginDef *p)
{
	delete static_cast<Dsp*>(p);
}

} // end namespace susta
} // end namespace pluginlib
