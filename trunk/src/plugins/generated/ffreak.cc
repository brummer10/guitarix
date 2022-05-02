// generated from file '../src/plugins/ffreak.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"
#include <string.h>

namespace pluginlib {
namespace ffreak {

class Dsp: public PluginDef {
private:
	int fSampleRate;
	double fConst0;
	double fConst1;
	FAUSTFLOAT fVslider0;
	double fRec0[2];
	FAUSTFLOAT fVslider1;
	double fRec2[2];
	double fConst3;
	FAUSTFLOAT fVslider2;
	double fRec3[2];
	double fConst4;
	double fConst6;
	double fConst8;
	FAUSTFLOAT fVslider3;
	double fRec4[2];
	double fConst10;
	double fConst11;
	double fConst13;
	double fConst14;
	double fConst16;
	double fConst18;
	double fConst20;
	double fConst21;
	double fConst23;
	double fConst24;
	double fConst26;
	double fConst28;
	double fConst30;
	double fConst31;
	double fConst33;
	double fConst34;
	double fConst36;
	double fConst38;
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
	double fConst60;
	double fConst61;
	double fConst62;
	double fConst63;
	double fConst64;
	double fConst65;
	double fConst67;
	double fConst68;
	double fConst70;
	double fConst72;
	double fConst74;
	double fConst75;
	double fConst77;
	double fConst78;
	double fConst80;
	double fConst82;
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
	double fConst96;
	double fConst97;
	double fRec1[6];
	double fConst99;
	double fConst101;
	double fConst103;
	double fConst105;
	double fConst107;
	double fConst109;
	double fConst111;
	double fConst113;
	double fConst115;
	double fConst117;
	double fConst119;
	double fConst121;
	double fConst123;
	double fConst125;
	double fConst127;
	double fConst129;
	double fConst131;
	double fConst133;
	double fConst135;
	double fConst137;
	double fConst139;
	double fConst141;
	double fConst143;
	double fConst145;
	double fConst146;
	double fConst147;
	double fConst148;
	double fConst149;
	double fConst150;
	double fConst151;
	double fConst152;
	double fConst153;
	double fConst154;
	double fConst155;
	double fConst156;
	double fConst157;
	double fConst158;
	double fConst159;
	double fConst160;
	double fConst161;
	double fConst162;
	double fConst163;
	double fConst164;
	double fConst165;
	double fConst166;
	double fConst167;
	double fConst168;
	double fConst169;

	FAUSTFLOAT fsliderdw0;
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
	id = "ffreak";
	name = N_("Fat Furry Freak");
	groups = 0;
	description = N_("Extreme Bass Fuzz Monster"); // description (tooltip)
	category = N_("Fuzz");       // category
	shortname = N_("Fat FFreak");     // shortname
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec0[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec2[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec3[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec4[l3] = 0.0;
	for (int l4 = 0; l4 < 6; l4 = l4 + 1) fRec1[l4] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = mydsp_faustpower2_f(fConst0);
	double fConst2 = 3.3502661673929698e-23 * fConst0;
	fConst3 = fConst0 * (fConst0 * (fConst0 * (fConst2 + 1.7873480648156699e-19) + 1.90595008624394e-17) + -1.88638248347695e-16) + -6.5201876680611895e-16;
	fConst4 = fConst0 * (fConst0 * (fConst0 * (fConst2 + 1.72846172283149e-19) + 3.8072571713818497e-18) + -3.2477077720450097e-17) + -8.4419470762099498e-17;
	double fConst5 = 2.3822005892794199e-23 * fConst0;
	fConst6 = fConst0 * (fConst0 * (fConst0 * (-7.2922594272322706e-20 - fConst5) + -2.4071143573057499e-18) + 2.16097599157672e-17) + 5.6493276205652504e-17;
	double fConst7 = 2.3264772378957199e-23 * fConst0;
	fConst8 = fConst0 * (fConst0 * (fConst0 * (fConst7 + 7.1203189810367999e-20) + 2.3276290219993299e-18) + -1.8831092068550801e-17);
	double fConst9 = 3.2718982668413897e-23 * fConst0;
	fConst10 = fConst0 * (fConst0 * (fConst0 * (-1.6878386115029699e-19 - fConst9) + -3.66325429672487e-18) + 2.8139823587366501e-17);
	fConst11 = fConst0 * (fConst0 * (fConst0 * (-1.74534751099098e-19 - fConst9) + -1.8556852326307699e-17) + 1.66102929456909e-16) + 1.50114464615909e-16;
	double fConst12 = 4.0211030798770698e-23 * fConst0;
	fConst13 = fConst0 * (fConst0 * (fConst0 * (-2.3867993953651901e-19 - fConst12) + -9.4400434462260698e-17) + 2.24958749395835e-14) + 8.8135235912485604e-14;
	fConst14 = fConst0 * (fConst0 * (fConst0 * (-2.31612201055921e-19 - fConst12) + -7.3735356988903701e-17) + 4.0005445034622704e-15) + 1.1777572946099699e-14;
	double fConst15 = 2.8591979406491397e-23 * fConst0;
	fConst16 = fConst0 * (fConst0 * (fConst0 * (fConst15 + 1.0470050822638701e-19) + 3.2048993155084302e-17) + -2.6598801796002799e-15) + -7.8815192214512497e-15;
	double fConst17 = 2.7923299189887e-23 * fConst0;
	fConst18 = fConst0 * (fConst0 * (fConst0 * (-1.0263576587599599e-19 - fConst17) + -3.1945412756842203e-17) + 2.6271730738170801e-15);
	double fConst19 = 3.9270615992151898e-23 * fConst0;
	fConst20 = fConst0 * (fConst0 * (fConst0 * (fConst19 + 2.2673537861440999e-19) + 7.3548635730191699e-17) + -3.9258576486998901e-15);
	fConst21 = fConst0 * (fConst0 * (fConst0 * (fConst19 + 2.33637823995467e-19) + 9.3783138321284205e-17) + -2.2395439003671001e-14) + -2.09428469678622e-14;
	double fConst22 = 6.7005323347859302e-23 * fConst0;
	fConst23 = fConst0 * (fConst0 * (fConst0 * (-1.1915653765437799e-19 - fConst22) + 3.8119001724878801e-17) + 3.7727649669539001e-16) + -4.3467917787074598e-16;
	fConst24 = fConst0 * (fConst0 * (fConst0 * (-1.1523078152209901e-19 - fConst22) + 7.6145143427636994e-18) + 6.4954155440900194e-17) + -5.6279647174733002e-17;
	double fConst25 = 4.7644011785588299e-23 * fConst0;
	fConst26 = fConst0 * (fConst0 * (fConst0 * (fConst25 + 4.8615062848215099e-20) + -4.8142287146114999e-18) + -4.3219519831534399e-17) + 3.76621841371017e-17;
	double fConst27 = 4.6529544757914398e-23 * fConst0;
	fConst28 = fConst0 * (fConst0 * (fConst0 * (-4.7468793206911998e-20 - fConst27) + 4.6552580439986699e-18) + 3.76621841371017e-17);
	double fConst29 = 6.54379653368279e-23 * fConst0;
	fConst30 = fConst0 * (fConst0 * (fConst0 * (fConst29 + 1.1252257410019799e-19) + -7.3265085934497401e-18) + -5.6279647174733002e-17);
	fConst31 = fConst0 * (fConst0 * (fConst0 * (fConst29 + 1.16356500732732e-19) + -3.71137046526153e-17) + -3.32205858913818e-16) + 1.0007630974393899e-16;
	double fConst32 = 8.0422061597541502e-23 * fConst0;
	fConst33 = fConst0 * (fConst0 * (fConst0 * (fConst32 + 1.59119959691012e-19) + -1.88800868924521e-16) + -4.49917498791669e-14) + 5.8756823941657095e-14;
	fConst34 = fConst0 * (fConst0 * (fConst0 * (fConst32 + 1.54408134037281e-19) + -1.4747071397780701e-16) + -8.0010890069245297e-15) + 7.8517152973997801e-15;
	double fConst35 = 5.7183958812982795e-23 * fConst0;
	fConst36 = fConst0 * (fConst0 * (fConst0 * (-6.9800338817591501e-20 - fConst35) + 6.4097986310168506e-17) + 5.3197603592005599e-15) + -5.2543461476341696e-15;
	double fConst37 = 5.5846598379774001e-23 * fConst0;
	fConst38 = fConst0 * (fConst0 * (fConst0 * (fConst37 + 6.8423843917330603e-20) + -6.3890825513684405e-17) + -5.2543461476341696e-15);
	double fConst39 = 7.8541231984303702e-23 * fConst0;
	fConst40 = fConst0 * (fConst0 * (fConst0 * (-1.51156919076274e-19 - fConst39) + 1.47097271460383e-16) + 7.8517152973997801e-15);
	fConst41 = fConst0 * (fConst0 * (fConst0 * (-1.5575854933031099e-19 - fConst39) + 1.8756627664256799e-16) + 4.4790878007342002e-14) + -1.39618979785748e-14;
	fConst42 = fConst0 * (fConst0 * (fConst0 * (fConst22 + -1.1915653765437799e-19) + -3.8119001724878801e-17) + 3.7727649669539001e-16) + 4.3467917787074598e-16;
	fConst43 = fConst0 * (fConst0 * (fConst0 * (fConst22 + -1.1523078152209901e-19) + -7.6145143427636994e-18) + 6.4954155440900194e-17) + 5.6279647174733002e-17;
	fConst44 = fConst0 * (fConst0 * (fConst0 * (4.8615062848215099e-20 - fConst25) + 4.8142287146114999e-18) + -4.3219519831534399e-17) + -3.76621841371017e-17;
	fConst45 = fConst0 * (fConst0 * (fConst0 * (fConst27 + -4.7468793206911998e-20) + -4.6552580439986699e-18) + 3.76621841371017e-17);
	fConst46 = fConst0 * (fConst0 * (fConst0 * (1.1252257410019799e-19 - fConst29) + 7.3265085934497401e-18) + -5.6279647174733002e-17);
	fConst47 = fConst0 * (fConst0 * (fConst0 * (1.16356500732732e-19 - fConst29) + 3.71137046526153e-17) + -3.32205858913818e-16) + -1.0007630974393899e-16;
	fConst48 = fConst0 * (fConst0 * (fConst0 * (1.59119959691012e-19 - fConst32) + 1.88800868924521e-16) + -4.49917498791669e-14) + -5.8756823941657095e-14;
	fConst49 = fConst0 * (fConst0 * (fConst0 * (1.54408134037281e-19 - fConst32) + 1.4747071397780701e-16) + -8.0010890069245297e-15) + -7.8517152973997801e-15;
	fConst50 = fConst0 * (fConst0 * (fConst0 * (fConst35 + -6.9800338817591501e-20) + -6.4097986310168506e-17) + 5.3197603592005599e-15) + 5.2543461476341696e-15;
	fConst51 = fConst0 * (fConst0 * (fConst0 * (6.8423843917330603e-20 - fConst37) + 6.3890825513684405e-17) + -5.2543461476341696e-15);
	fConst52 = fConst0 * (fConst0 * (fConst0 * (fConst39 + -1.51156919076274e-19) + -1.47097271460383e-16) + 7.8517152973997801e-15);
	fConst53 = fConst0 * (fConst0 * (fConst0 * (fConst39 + -1.5575854933031099e-19) + -1.8756627664256799e-16) + 4.4790878007342002e-14) + 1.39618979785748e-14;
	fConst54 = fConst0 * (fConst0 * (fConst0 * (1.7873480648156699e-19 - fConst2) + -1.90595008624394e-17) + -1.88638248347695e-16) + 6.5201876680611895e-16;
	fConst55 = fConst0 * (fConst0 * (fConst0 * (1.72846172283149e-19 - fConst2) + -3.8072571713818497e-18) + -3.2477077720450097e-17) + 8.4419470762099498e-17;
	fConst56 = fConst0 * (fConst0 * (fConst0 * (fConst5 + -7.2922594272322706e-20) + 2.4071143573057499e-18) + 2.16097599157672e-17) + -5.6493276205652504e-17;
	fConst57 = fConst0 * (fConst0 * (fConst0 * (7.1203189810367999e-20 - fConst7) + -2.3276290219993299e-18) + -1.8831092068550801e-17);
	fConst58 = fConst0 * (fConst0 * (fConst0 * (fConst9 + -1.6878386115029699e-19) + 3.66325429672487e-18) + 2.8139823587366501e-17);
	fConst59 = fConst0 * (fConst0 * (fConst0 * (fConst9 + -1.74534751099098e-19) + 1.8556852326307699e-17) + 1.66102929456909e-16) + -1.50114464615909e-16;
	fConst60 = fConst0 * (fConst0 * (fConst0 * (fConst12 + -2.3867993953651901e-19) + 9.4400434462260698e-17) + 2.24958749395835e-14) + -8.8135235912485604e-14;
	fConst61 = fConst0 * (fConst0 * (fConst0 * (fConst12 + -2.31612201055921e-19) + 7.3735356988903701e-17) + 4.0005445034622704e-15) + -1.1777572946099699e-14;
	fConst62 = fConst0 * (fConst0 * (fConst0 * (1.0470050822638701e-19 - fConst15) + -3.2048993155084302e-17) + -2.6598801796002799e-15) + 7.8815192214512497e-15;
	fConst63 = fConst0 * (fConst0 * (fConst0 * (fConst17 + -1.0263576587599599e-19) + 3.1945412756842203e-17) + 2.6271730738170801e-15);
	fConst64 = fConst0 * (fConst0 * (fConst0 * (2.2673537861440999e-19 - fConst19) + -7.3548635730191699e-17) + -3.9258576486998901e-15);
	fConst65 = fConst0 * (fConst0 * (fConst0 * (2.33637823995467e-19 - fConst19) + -9.3783138321284205e-17) + -2.2395439003671001e-14) + 2.09428469678622e-14;
	double fConst66 = 6.7005323347859305e-24 * fConst0;
	fConst67 = fConst0 * (fConst0 * (fConst0 * (fConst66 + -5.9578268827189105e-20) + 1.90595008624394e-17) + -1.88638248347695e-16) + 2.1733958893537299e-16;
	fConst68 = fConst0 * (fConst0 * (fConst0 * (fConst66 + -5.7615390761049697e-20) + 3.8072571713818497e-18) + -3.2477077720450097e-17) + 2.8139823587366501e-17;
	double fConst69 = 4.7644011785588302e-24 * fConst0;
	fConst70 = fConst0 * (fConst0 * (fConst0 * (2.4307531424107601e-20 - fConst69) + -2.4071143573057499e-18) + 2.16097599157672e-17) + -1.8831092068550801e-17;
	double fConst71 = 4.6529544757914402e-24 * fConst0;
	fConst72 = fConst0 * (fConst0 * (fConst0 * (fConst71 + -2.3734396603455999e-20) + 2.3276290219993299e-18) + -1.8831092068550801e-17);
	double fConst73 = 6.5437965336827903e-24 * fConst0;
	fConst74 = fConst0 * (fConst0 * (fConst0 * (5.6261287050099103e-20 - fConst73) + -3.66325429672487e-18) + 2.8139823587366501e-17);
	fConst75 = fConst0 * (fConst0 * (fConst0 * (5.8178250366366002e-20 - fConst73) + -1.8556852326307699e-17) + 1.66102929456909e-16) + -5.0038154871969701e-17;
	double fConst76 = 8.0422061597541496e-24 * fConst0;
	fConst77 = fConst0 * (fConst0 * (fConst0 * (7.9559979845506204e-20 - fConst76) + -9.4400434462260698e-17) + 2.24958749395835e-14) + -2.9378411970828497e-14;
	fConst78 = fConst0 * (fConst0 * (fConst0 * (7.7204067018640298e-20 - fConst76) + -7.3735356988903701e-17) + 4.0005445034622704e-15) + -3.9258576486998901e-15;
	double fConst79 = 5.7183958812982797e-24 * fConst0;
	fConst80 = fConst0 * (fConst0 * (fConst0 * (fConst79 + -3.4900169408795799e-20) + 3.2048993155084302e-17) + -2.6598801796002799e-15) + 2.6271730738170801e-15;
	double fConst81 = 5.5846598379774004e-24 * fConst0;
	fConst82 = fConst0 * (fConst0 * (fConst0 * (3.4211921958665301e-20 - fConst81) + -3.1945412756842203e-17) + 2.6271730738170801e-15);
	double fConst83 = 7.8541231984303702e-24 * fConst0;
	fConst84 = fConst0 * (fConst0 * (fConst0 * (fConst83 + -7.5578459538136805e-20) + 7.3548635730191699e-17) + -3.9258576486998901e-15);
	fConst85 = fConst0 * (fConst0 * (fConst0 * (fConst83 + -7.7879274665155701e-20) + 9.3783138321284205e-17) + -2.2395439003671001e-14) + 6.9809489892874e-15;
	fConst86 = fConst0 * (fConst0 * (fConst0 * (-5.9578268827189105e-20 - fConst66) + -1.90595008624394e-17) + -1.88638248347695e-16) + -2.1733958893537299e-16;
	fConst87 = fConst0 * (fConst0 * (fConst0 * (-5.7615390761049697e-20 - fConst66) + -3.8072571713818497e-18) + -3.2477077720450097e-17) + -2.8139823587366501e-17;
	fConst88 = fConst0 * (fConst0 * (fConst0 * (fConst69 + 2.4307531424107601e-20) + 2.4071143573057499e-18) + 2.16097599157672e-17) + 1.8831092068550801e-17;
	fConst89 = fConst0 * (fConst0 * (fConst0 * (-2.3734396603455999e-20 - fConst71) + -2.3276290219993299e-18) + -1.8831092068550801e-17);
	fConst90 = fConst0 * (fConst0 * (fConst0 * (fConst73 + 5.6261287050099103e-20) + 3.66325429672487e-18) + 2.8139823587366501e-17);
	fConst91 = fConst0 * (fConst0 * (fConst0 * (fConst73 + 5.8178250366366002e-20) + 1.8556852326307699e-17) + 1.66102929456909e-16) + 5.0038154871969701e-17;
	fConst92 = fConst0 * (fConst0 * (fConst0 * (fConst76 + 7.9559979845506204e-20) + 9.4400434462260698e-17) + 2.24958749395835e-14) + 2.9378411970828497e-14;
	fConst93 = fConst0 * (fConst0 * (fConst0 * (fConst76 + 7.7204067018640298e-20) + 7.3735356988903701e-17) + 4.0005445034622704e-15) + 3.9258576486998901e-15;
	fConst94 = fConst0 * (fConst0 * (fConst0 * (-3.4900169408795799e-20 - fConst79) + -3.2048993155084302e-17) + -2.6598801796002799e-15) + -2.6271730738170801e-15;
	fConst95 = fConst0 * (fConst0 * (fConst0 * (fConst81 + 3.4211921958665301e-20) + 3.1945412756842203e-17) + 2.6271730738170801e-15);
	fConst96 = fConst0 * (fConst0 * (fConst0 * (-7.5578459538136805e-20 - fConst83) + -7.3548635730191699e-17) + -3.9258576486998901e-15);
	fConst97 = fConst0 * (fConst0 * (fConst0 * (-7.7879274665155701e-20 - fConst83) + -9.3783138321284205e-17) + -2.2395439003671001e-14) + -6.9809489892874e-15;
	double fConst98 = 2.24478316881583e-18 * fConst0;
	fConst99 = fConst0 * (-1.8662501140321701e-14 - fConst98) + -1.2958987682722301e-14;
	double fConst100 = 1.5588772005664601e-18 * fConst0;
	fConst101 = fConst0 * (fConst100 + 1.2958987682722301e-14);
	double fConst102 = 3.3359559144521401e-21 * fConst0;
	fConst103 = fConst0 * (-1.6692603703996201e-17 - fConst102) + -1.1590477130516399e-17;
	double fConst104 = 2.3166360517027401e-21 * fConst0;
	fConst105 = fConst0 * (fConst104 + 1.1590477130516399e-17);
	double fConst106 = 4.01337447559094e-21 * fConst0;
	fConst107 = fConst0 * (fConst106 + 2.0082303777310401e-17) + 1.39597416617563e-17;
	double fConst108 = 2.7901906402916699e-21 * fConst0;
	fConst109 = fConst0 * (-1.39597416617563e-17 - fConst108);
	double fConst110 = 2.70062186191725e-18 * fConst0;
	fConst111 = fConst0 * (fConst110 + 2.24522189930002e-14) + 1.5607995961821499e-14;
	double fConst112 = 1.8775347000180101e-18 * fConst0;
	fConst113 = fConst0 * (-1.5607995961821499e-14 - fConst112);
	double fConst114 = 6.7343495064474998e-18 * fConst0;
	fConst115 = fConst0 * (fConst114 + 1.8662501140321701e-14) + -1.2958987682722301e-14;
	double fConst116 = 4.6766316016993804e-18 * fConst0;
	fConst117 = fConst0 * (-1.2958987682722301e-14 - fConst116);
	double fConst118 = 1.66797795722607e-20 * fConst0;
	fConst119 = fConst0 * (fConst118 + 5.0077811111988598e-17) + 1.1590477130516399e-17;
	double fConst120 = 1.1583180258513701e-20 * fConst0;
	fConst121 = fConst0 * (-3.47714313915491e-17 - fConst120);
	double fConst122 = 2.0066872377954701e-20 * fConst0;
	fConst123 = fConst0 * (-6.02469113319311e-17 - fConst122) + -1.39597416617563e-17;
	double fConst124 = 1.39509532014583e-20 * fConst0;
	fConst125 = fConst0 * (fConst124 + 4.1879224985268799e-17);
	double fConst126 = 8.1018655857517603e-18 * fConst0;
	fConst127 = fConst0 * (-2.24522189930002e-14 - fConst126) + 1.5607995961821499e-14;
	double fConst128 = 5.6326041000540296e-18 * fConst0;
	fConst129 = fConst0 * (fConst128 + 1.5607995961821499e-14);
	double fConst130 = 4.4895663376316601e-18 * fConst0;
	fConst131 = fConst0 * (3.7325002280643301e-14 - fConst130) + 2.59179753654445e-14;
	double fConst132 = 3.1177544011329201e-18 * fConst0;
	fConst133 = fConst0 * (fConst132 + -2.59179753654445e-14);
	double fConst134 = 3.3359559144521401e-20 * fConst0;
	fConst135 = fConst0 * (-3.3385207407992403e-17 - fConst134) + 2.31809542610327e-17;
	double fConst136 = 2.3166360517027401e-20 * fConst0;
	fConst137 = fConst0 * (fConst136 + 2.31809542610327e-17);
	double fConst138 = 4.0133744755909402e-20 * fConst0;
	fConst139 = fConst0 * (fConst138 + 4.0164607554620703e-17) + -2.79194833235126e-17;
	double fConst140 = 2.7901906402916703e-20 * fConst0;
	fConst141 = fConst0 * (-2.79194833235126e-17 - fConst140);
	double fConst142 = 5.4012437238345099e-18 * fConst0;
	fConst143 = fConst0 * (fConst142 + -4.49044379860004e-14) + -3.1215991923643099e-14;
	double fConst144 = 3.7550694000360203e-18 * fConst0;
	fConst145 = fConst0 * (3.1215991923643099e-14 - fConst144);
	fConst146 = fConst0 * (-3.7325002280643301e-14 - fConst130) + 2.59179753654445e-14;
	fConst147 = fConst0 * (fConst132 + 2.59179753654445e-14);
	fConst148 = fConst0 * (fConst134 + -3.3385207407992403e-17) + -2.31809542610327e-17;
	fConst149 = fConst0 * (2.31809542610327e-17 - fConst136);
	fConst150 = fConst0 * (4.0164607554620703e-17 - fConst138) + 2.79194833235126e-17;
	fConst151 = fConst0 * (fConst140 + -2.79194833235126e-17);
	fConst152 = fConst0 * (fConst142 + 4.49044379860004e-14) + -3.1215991923643099e-14;
	fConst153 = fConst0 * (-3.1215991923643099e-14 - fConst144);
	fConst154 = fConst0 * (fConst114 + -1.8662501140321701e-14) + -1.2958987682722301e-14;
	fConst155 = fConst0 * (1.2958987682722301e-14 - fConst116);
	fConst156 = fConst0 * (5.0077811111988598e-17 - fConst118) + -1.1590477130516399e-17;
	fConst157 = fConst0 * (fConst120 + -3.47714313915491e-17);
	fConst158 = fConst0 * (fConst122 + -6.02469113319311e-17) + 1.39597416617563e-17;
	fConst159 = fConst0 * (4.1879224985268799e-17 - fConst124);
	fConst160 = fConst0 * (2.24522189930002e-14 - fConst126) + 1.5607995961821499e-14;
	fConst161 = fConst0 * (fConst128 + -1.5607995961821499e-14);
	fConst162 = fConst0 * (1.8662501140321701e-14 - fConst98) + -1.2958987682722301e-14;
	fConst163 = fConst0 * (fConst100 + -1.2958987682722301e-14);
	fConst164 = fConst0 * (fConst102 + -1.6692603703996201e-17) + 1.1590477130516399e-17;
	fConst165 = fConst0 * (1.1590477130516399e-17 - fConst104);
	fConst166 = fConst0 * (2.0082303777310401e-17 - fConst106) + -1.39597416617563e-17;
	fConst167 = fConst0 * (fConst108 + -1.39597416617563e-17);
	fConst168 = fConst0 * (fConst110 + -2.24522189930002e-14) + 1.5607995961821499e-14;
	fConst169 = fConst0 * (1.5607995961821499e-14 - fConst112);
	clear_state_f();
}

void Dsp::init_static(unsigned int sample_rate, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlowdw0 = (0.01 * fsliderdw0);
	double 	fSlowdw1 = (1 - fSlowdw0);
	FAUSTFLOAT 	dryinput[count];
	memcpy(&dryinput, input0, count * sizeof(float));

	double fSlow0 = 0.00035000000000000032 * (double(fVslider0) + 0.01);
	double fSlow1 = 0.0070000000000000062 * double(fVslider1);
	double fSlow2 = 0.0070000000000000062 * double(fVslider2);
	double fSlow3 = 0.0070000000000000062 * double(fVslider3);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec0[0] = fSlow0 + 0.99299999999999999 * fRec0[1];
		fRec2[0] = fSlow1 + 0.99299999999999999 * fRec2[1];
		fRec3[0] = fSlow2 + 0.99299999999999999 * fRec3[1];
		fRec4[0] = fSlow3 + 0.99299999999999999 * fRec4[1];
		double fTemp0 = fRec2[0] * (fConst0 * (fConst86 + fRec3[0] * (fConst87 + fRec3[0] * (fConst88 + fConst89 * fRec4[0]) + fConst90 * fRec4[0]) + fConst91 * fRec4[0]) + -5.0038154871969701e-17) + fConst0 * (fConst92 + fRec3[0] * (fConst93 + fRec3[0] * (fConst94 + fConst95 * fRec4[0]) + fConst96 * fRec4[0]) + fConst97 * fRec4[0]) + 6.9809489892874e-15;
		fRec1[0] = double(input0[i0]) - (fRec1[1] * (fRec2[0] * (fConst0 * (fConst3 + fRec3[0] * (fConst4 + fRec3[0] * (fConst6 + fConst8 * fRec4[0]) + fConst10 * fRec4[0]) + fConst11 * fRec4[0]) + -2.5019077435984898e-16) + fConst0 * (fConst13 + fRec3[0] * (fConst14 + fRec3[0] * (fConst16 + fConst18 * fRec4[0]) + fConst20 * fRec4[0]) + fConst21 * fRec4[0]) + 3.4904744946437e-14) + fRec1[2] * (fRec2[0] * (fConst0 * (fConst23 + fRec3[0] * (fConst24 + fRec3[0] * (fConst26 + fConst28 * fRec4[0]) + fConst30 * fRec4[0]) + fConst31 * fRec4[0]) + -5.0038154871969697e-16) + fConst0 * (fConst33 + fRec3[0] * (fConst34 + fRec3[0] * (fConst36 + fConst38 * fRec4[0]) + fConst40 * fRec4[0]) + fConst41 * fRec4[0]) + 6.9809489892874e-14) + fRec1[3] * (fRec2[0] * (fConst0 * (fConst42 + fRec3[0] * (fConst43 + fRec3[0] * (fConst44 + fConst45 * fRec4[0]) + fConst46 * fRec4[0]) + fConst47 * fRec4[0]) + -5.0038154871969697e-16) + fConst0 * (fConst48 + fRec3[0] * (fConst49 + fRec3[0] * (fConst50 + fConst51 * fRec4[0]) + fConst52 * fRec4[0]) + fConst53 * fRec4[0]) + 6.9809489892874e-14) + fRec1[4] * (fRec2[0] * (fConst0 * (fConst54 + fRec3[0] * (fConst55 + fRec3[0] * (fConst56 + fConst57 * fRec4[0]) + fConst58 * fRec4[0]) + fConst59 * fRec4[0]) + -2.5019077435984898e-16) + fConst0 * (fConst60 + fRec3[0] * (fConst61 + fRec3[0] * (fConst62 + fConst63 * fRec4[0]) + fConst64 * fRec4[0]) + fConst65 * fRec4[0]) + 3.4904744946437e-14) + fRec1[5] * (fRec2[0] * (fConst0 * (fConst67 + fRec3[0] * (fConst68 + fRec3[0] * (fConst70 + fConst72 * fRec4[0]) + fConst74 * fRec4[0]) + fConst75 * fRec4[0]) + -5.0038154871969701e-17) + fConst0 * (fConst77 + fRec3[0] * (fConst78 + fRec3[0] * (fConst80 + fConst82 * fRec4[0]) + fConst84 * fRec4[0]) + fConst85 * fRec4[0]) + 6.9809489892874e-15)) / fTemp0;
		output0[i0] = FAUSTFLOAT(0.31830988618379069 * std::atan(fConst1 * (fRec0[0] * (fRec1[0] * (fRec2[0] * (fConst99 + fConst101 * fRec4[0] + fConst0 * fRec3[0] * (fConst103 + fConst105 * fRec4[0])) + fConst0 * fRec3[0] * (fConst107 + fConst109 * fRec4[0]) + fConst111 + fConst113 * fRec4[0]) + fRec1[1] * (fRec2[0] * (fConst115 + fConst117 * fRec4[0] + fConst0 * fRec3[0] * (fConst119 + fConst121 * fRec4[0])) + fConst0 * fRec3[0] * (fConst123 + fConst125 * fRec4[0]) + fConst127 + fConst129 * fRec4[0]) + fRec1[2] * (fRec2[0] * (fConst131 + fConst133 * fRec4[0] + fConst0 * fRec3[0] * (fConst135 + fConst137 * fRec4[0])) + fConst0 * fRec3[0] * (fConst139 + fConst141 * fRec4[0]) + fConst143 + fConst145 * fRec4[0]) + fRec1[3] * (fRec2[0] * (fConst146 + fConst147 * fRec4[0] + fConst0 * fRec3[0] * (fConst148 + fConst149 * fRec4[0])) + fConst0 * fRec3[0] * (fConst150 + fConst151 * fRec4[0]) + fConst152 + fConst153 * fRec4[0]) + fRec1[4] * (fRec2[0] * (fConst154 + fConst155 * fRec4[0] + fConst0 * fRec3[0] * (fConst156 + fConst157 * fRec4[0])) + fConst0 * fRec3[0] * (fConst158 + fConst159 * fRec4[0]) + fConst160 + fConst161 * fRec4[0]) + fRec1[5] * (fRec2[0] * (fConst162 + fConst163 * fRec4[0] + fConst0 * fRec3[0] * (fConst164 + fConst165 * fRec4[0])) + fConst0 * fRec3[0] * (fConst166 + fConst167 * fRec4[0]) + fConst168 + fConst169 * fRec4[0]))) / fTemp0));
		fRec0[1] = fRec0[0];
		fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		for (int j0 = 5; j0 > 0; j0 = j0 - 1) {
			fRec1[j0] = fRec1[j0 - 1];
		}
	}
	for (int i=0; i<count; i++) {
		output0[i] = ((fSlowdw1 * (double)dryinput[i]) + (fSlowdw0 * (double)output0[i]));
	}

}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerFloatVar("ffreak.wet_dry",N_("Dry/Wet"),"S",N_("percentage of processed signal in output signal"),&fsliderdw0, 1e+02, 0.0, 1e+02, 1.0, 0);
	reg.registerFloatVar("ffreak.Fuzz",N_("Fuzz"),"S","",&fVslider3, 0.5, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("ffreak.Gate",N_("Gate"),"S","",&fVslider1, 0.5, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("ffreak.Level",N_("Level"),"S","",&fVslider0, 0.5, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("ffreak.Tone",N_("Tone"),"S","",&fVslider2, 0.5, 0.0, 1.0, 0.01, 0);
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
                        <property name=\"var_id\">ffreak.Gate</property>\n\
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
                      <object class=\"GxSmallKnobR\" id=\"gxbigknob2\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">ffreak.Fuzz</property>\n\
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
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox4\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label3:rack_label\">\n\
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
                      <object class=\"GxSmallKnobR\" id=\"gxbigknob3\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">ffreak.Tone</property>\n\
                        <property name=\"label_ref\">label3:rack_label</property>\n\
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
                    <property name=\"position\">2</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox5\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label4:rack_label\">\n\
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
                      <object class=\"GxMidKnob\" id=\"gxbigknob4\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">ffreak.Level</property>\n\
                        <property name=\"label_ref\">label4:rack_label</property>\n\
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
                    <property name=\"position\">3</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox6\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label5:rack_label\">\n\
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
                      <object class=\"GxSmallKnobR\" id=\"gxbigknob5\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">ffreak.wet_dry</property>\n\
                        <property name=\"label_ref\">label5:rack_label</property>\n\
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
                    <property name=\"position\">4</property>\n\
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
                <property name=\"var_id\">ffreak.Level</property>\n\
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
                <property name=\"label\" translatable=\"yes\">Level</property>\n\
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
#define PARAM(p) ("ffreak" "." p)

b.openHorizontalhideBox("");
    b.create_master_slider(PARAM("Fuzz"), "Fuzz");
b.closeBox();
b.openHorizontalBox("");

    b.create_small_rackknobr(PARAM("Fuzz"), "Fuzz");

    b.create_small_rackknobr(PARAM("Tone"), "Tone");

    b.create_small_rackknobr(PARAM("Gate"), "Gate");

    b.create_small_rackknobr(PARAM("Level"), "Level");
    b.create_small_rackknobr(PARAM("wet_dry"), "dry/wet");
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

} // end namespace ffreak
} // end namespace pluginlib
