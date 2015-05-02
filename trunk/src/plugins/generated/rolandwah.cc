// generated from file '../src/plugins/rolandwah.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

namespace pluginlib {
namespace rolandwah {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	int 	iVec0[2];
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	FAUSTFLOAT 	fslider0;
	double 	fConst4;
	double 	fRec2[2];
	double 	fRec1[2];
	double 	fRec0[2];
	FAUSTFLOAT 	fslider1;
	double 	fRec5[2];
	double 	fConst5;
	double 	fConst6;
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
	double 	fConst33;
	double 	fConst34;
	double 	fConst35;
	FAUSTFLOAT 	fslider2;
	double 	fRec6[9];
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
	double 	fRec4[2];
	double 	fConst63;
	double 	fConst64;
	double 	fRec3[2];
	FAUSTFLOAT 	fslider3;
	double 	fRec7[2];
	FAUSTFLOAT 	fcheckbox0;
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
	double 	fConst92;
	double 	fConst93;
	double 	fConst94;
	double 	fConst95;
	double 	fConst96;
	double 	fConst97;
	double 	fConst98;
	double 	fRec8[7];
	double 	fConst99;
	double 	fConst100;
	double 	fConst101;
	double 	fConst102;
	double 	fConst103;
	double 	fConst104;
	double 	fConst105;
	double 	fConst106;
	double 	fConst107;
	double 	fConst108;
	double 	fConst109;
	double 	fConst110;
	double 	fConst111;
	double 	fConst112;
	double 	fConst113;
	double 	fConst114;
	double 	fConst115;
	double 	fConst116;
	double 	fConst117;
	double 	fConst118;
	double 	fConst119;
	double 	fConst120;
	double 	fConst121;
	double 	fConst122;
	void clear_state_f();
	int load_ui_f(const UiBuilder& b, int form);
	void init(unsigned int samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static int load_ui_f_static(const UiBuilder& b, int form);
	static void init_static(unsigned int samplingFreq, PluginDef*);
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
	id = "rolandwah";
	name = N_("Roland Double Beat");
	groups = 0;
	description = N_("Roland Double Beat"); // description (tooltip)
	category = N_("Guitar Effects");       // category
	shortname = N_("Double Beat");     // shortname
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
	for (int i=0; i<2; i++) iVec0[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<9; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<7; i++) fRec8[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = double(iConst0);
	fConst2 = (5.0345082751012e-30 * fConst1);
	fConst3 = (3.09198451037471e-17 + (fConst1 * (3.76182116601294e-18 + (fConst1 * (1.48648313435063e-19 + (fConst1 * (2.55142258602227e-22 + (fConst1 * (1.05561747816346e-26 + fConst2)))))))));
	fConst4 = (0.10471975511965977 / double(iConst0));
	fConst5 = (1.06547675999473e-54 * fConst1);
	fConst6 = ((fConst1 * ((fConst1 * ((fConst1 * ((fConst1 * ((fConst1 * ((fConst1 * (fConst5 - 6.36703541780379e-34)) - 9.00344543865557e-30)) - 2.39397418473651e-26)) - 1.34572992250123e-23)) - 1.91115337400853e-21)) - 4.31167897320117e-20)) - 1.60575474208273e-19);
	fConst7 = (1.1941846910457e-54 * fConst1);
	fConst8 = (2.31715010157959e-18 + (fConst1 * (1.38910427011718e-19 + (fConst1 * (2.60211977798108e-21 + (fConst1 * (1.49502594204983e-23 + (fConst1 * (2.58670896475515e-26 + (fConst1 * (1.15619064166179e-29 + (fConst1 * (1.86853737366137e-33 - fConst7)))))))))))));
	fConst9 = (1.82165381590155e-34 * fConst1);
	fConst10 = (fConst1 * (1.75333971598006e-23 + (fConst1 * ((fConst1 * (1.57206471944022e-27 - fConst9)) - 8.06344317796452e-25))));
	fConst11 = (5.55310765569968e-34 * fConst1);
	fConst12 = (8.76669857990029e-22 + (fConst1 * ((fConst1 * (2.57911836885096e-24 + (fConst1 * (fConst11 - 4.8752347359394e-27)))) - 9.46466696004935e-23)));
	fConst13 = (1.60575474208273e-19 + (fConst1 * ((fConst1 * (1.91115337400853e-21 + (fConst1 * ((fConst1 * (2.39397418473651e-26 + (fConst1 * ((fConst1 * (6.36703541780379e-34 + fConst5)) - 9.00344543865557e-30)))) - 1.34572992250123e-23)))) - 4.31167897320117e-20)));
	fConst14 = ((fConst1 * (1.38910427011718e-19 + (fConst1 * ((fConst1 * (1.49502594204983e-23 + (fConst1 * ((fConst1 * (1.15619064166179e-29 + (fConst1 * (0 - (1.86853737366137e-33 + fConst7))))) - 2.58670896475515e-26)))) - 2.60211977798108e-21)))) - 2.31715010157959e-18);
	fConst15 = (8.52381407995785e-54 * fConst1);
	fConst16 = faustpower<2>(fConst1);
	fConst17 = (9.63452845249636e-19 + (fConst1 * ((fConst1 * (3.82230674801706e-21 + (fConst16 * ((fConst1 * (3.60137817546223e-29 + (fConst1 * (0 - (3.82022125068227e-33 + fConst15))))) - 4.78794836947302e-26)))) - 1.72467158928047e-19)));
	fConst18 = (9.55347752836564e-54 * fConst1);
	fConst19 = ((fConst1 * (5.55641708046871e-19 + (fConst1 * ((fConst16 * (5.17341792951031e-26 + (fConst1 * ((fConst1 * (1.12112242419682e-32 + fConst18)) - 4.62476256664716e-29)))) - 5.20423955596215e-21)))) - 1.39029006094775e-17);
	fConst20 = (2.98333492798525e-53 * fConst1);
	fConst21 = (2.24805663891582e-18 + (fConst1 * ((fConst1 * ((fConst1 * (5.38291969000492e-23 + (fConst1 * ((fConst1 * ((fConst1 * (8.91384958492531e-33 + fConst20)) - 3.60137817546223e-29)) - 4.78794836947302e-26)))) - 3.82230674801706e-21)) - 1.72467158928047e-19)));
	fConst22 = (3.34371713492797e-53 * fConst1);
	fConst23 = ((fConst1 * (5.55641708046871e-19 + (fConst1 * (5.20423955596215e-21 + (fConst1 * ((fConst1 * (5.17341792951031e-26 + (fConst1 * (4.62476256664716e-29 + (fConst1 * (0 - (2.61595232312592e-32 + fConst22))))))) - 5.98010376819931e-23)))))) - 3.24401014221143e-17);
	fConst24 = (5.96666985597049e-53 * fConst1);
	fConst25 = (2.24805663891582e-18 + (fConst1 * (1.72467158928047e-19 + (fConst1 * ((fConst16 * (1.43638451084191e-25 + (fConst1 * ((fConst1 * (0 - (8.91384958492531e-33 + fConst24))) - 3.60137817546223e-29)))) - 1.14669202440512e-20)))));
	fConst26 = (6.68743426985594e-53 * fConst1);
	fConst27 = ((fConst1 * ((fConst1 * (1.56127186678865e-20 + (fConst16 * ((fConst1 * (4.62476256664716e-29 + (fConst1 * (2.61595232312592e-32 + fConst26)))) - 1.55202537885309e-25)))) - 5.55641708046871e-19)) - 3.24401014221143e-17);
	fConst28 = (4.31167897320117e-19 + (fConst16 * ((fConst16 * (9.00344543865557e-29 + (7.45833731996312e-53 * fConst16))) - 8.07437953500738e-23)));
	fConst29 = ((fConst16 * (8.97015565229896e-23 + (fConst16 * (0 - (1.15619064166179e-28 + (8.35929283731993e-53 * fConst16)))))) - 1.38910427011718e-18);
	fConst30 = ((fConst1 * (1.72467158928047e-19 + (fConst1 * (1.14669202440512e-20 + (fConst16 * ((fConst1 * ((fConst1 * (8.91384958492531e-33 - fConst24)) - 3.60137817546223e-29)) - 1.43638451084191e-25)))))) - 2.24805663891582e-18);
	fConst31 = (3.24401014221143e-17 + (fConst1 * ((fConst1 * ((fConst16 * (1.55202537885309e-25 + (fConst1 * (4.62476256664716e-29 + (fConst1 * (fConst26 - 2.61595232312592e-32)))))) - 1.56127186678865e-20)) - 5.55641708046871e-19)));
	fConst32 = ((fConst1 * ((fConst1 * (3.82230674801706e-21 + (fConst1 * (5.38291969000492e-23 + (fConst1 * (4.78794836947302e-26 + (fConst1 * ((fConst1 * (fConst20 - 8.91384958492531e-33)) - 3.60137817546223e-29)))))))) - 1.72467158928047e-19)) - 2.24805663891582e-18);
	fConst33 = (3.24401014221143e-17 + (fConst1 * (5.55641708046871e-19 + (fConst1 * ((fConst1 * ((fConst1 * ((fConst1 * (4.62476256664716e-29 + (fConst1 * (2.61595232312592e-32 - fConst22)))) - 5.17341792951031e-26)) - 5.98010376819931e-23)) - 5.20423955596215e-21)))));
	fConst34 = ((fConst1 * ((fConst1 * ((fConst16 * (4.78794836947302e-26 + (fConst1 * (3.60137817546223e-29 + (fConst1 * (3.82022125068227e-33 - fConst15)))))) - 3.82230674801706e-21)) - 1.72467158928047e-19)) - 9.63452845249636e-19);
	fConst35 = (1.39029006094775e-17 + (fConst1 * (5.55641708046871e-19 + (fConst1 * (5.20423955596215e-21 + (fConst16 * ((fConst1 * ((fConst1 * (fConst18 - 1.12112242419682e-32)) - 4.62476256664716e-29)) - 5.17341792951031e-26)))))));
	fConst36 = (1.09299228954093e-33 * fConst1);
	fConst37 = (fConst16 * (1.6126886355929e-24 + (fConst1 * (fConst36 - 6.28825887776087e-27))));
	fConst38 = (3.3318645934198e-33 * fConst1);
	fConst39 = (1.75333971598006e-21 + (fConst16 * ((fConst1 * (1.95009389437576e-26 - fConst38)) - 5.15823673770192e-24)));
	fConst40 = (2.55031534226217e-33 * fConst1);
	fConst41 = (fConst1 * (6.28825887776087e-27 - fConst40));
	fConst42 = (fConst1 * ((fConst1 * (1.6126886355929e-24 + fConst41)) - 7.01335886392023e-23));
	fConst43 = (7.77435071797955e-33 * fConst1);
	fConst44 = (fConst1 * (fConst43 - 1.95009389437576e-26));
	fConst45 = ((fConst1 * (3.78586678401974e-22 + (fConst1 * (fConst44 - 5.15823673770192e-24)))) - 1.75333971598006e-21);
	fConst46 = (fConst1 * (6.28825887776087e-27 + fConst40));
	fConst47 = (fConst16 * (fConst46 - 4.83806590677871e-24));
	fConst48 = (fConst1 * (0 - (1.95009389437576e-26 + fConst43)));
	fConst49 = ((fConst16 * (1.54747102131058e-23 + fConst48)) - 5.26001914794017e-21);
	fConst50 = (1.05200382958803e-22 - (1.57206471944022e-26 * fConst16));
	fConst51 = ((4.8752347359394e-26 * fConst16) - 5.67880017602961e-22);
	fConst52 = (fConst16 * (4.83806590677871e-24 + fConst41));
	fConst53 = (5.26001914794017e-21 + (fConst16 * (fConst44 - 1.54747102131058e-23)));
	fConst54 = (fConst1 * ((fConst1 * (fConst46 - 1.6126886355929e-24)) - 7.01335886392023e-23));
	fConst55 = (1.75333971598006e-21 + (fConst1 * (3.78586678401974e-22 + (fConst1 * (5.15823673770192e-24 + fConst48)))));
	fConst56 = (fConst16 * ((fConst1 * (0 - (6.28825887776087e-27 + fConst36))) - 1.6126886355929e-24));
	fConst57 = ((fConst16 * (5.15823673770192e-24 + (fConst1 * (1.95009389437576e-26 + fConst38)))) - 1.75333971598006e-21);
	fConst58 = (fConst1 * (1.75333971598006e-23 + (fConst1 * (8.06344317796452e-25 + (fConst1 * (1.57206471944022e-27 + fConst9))))));
	fConst59 = ((fConst1 * ((fConst1 * ((fConst1 * (0 - (4.8752347359394e-27 + fConst11))) - 2.57911836885096e-24)) - 9.46466696004935e-23)) - 8.76669857990029e-22);
	fConst60 = faustpower<3>(fConst1);
	fConst61 = exp((0 - (1e+01 / double(iConst0))));
	fConst62 = (1.0 - fConst61);
	fConst63 = exp((0 - (1e+02 / double(iConst0))));
	fConst64 = (1.0 - fConst63);
	fConst65 = (4.29845675581904e-29 * fConst1);
	fConst66 = (fConst1 * ((fConst1 * ((fConst1 * ((fConst1 * (0 - (3.19373566665743e-26 + fConst65))) - 8.90038927961101e-23)) - 4.87042253786579e-20)) - 3.50713071672392e-19));
	fConst67 = (1.72206886126217e-28 * fConst1);
	fConst68 = (5.31383441927866e-18 + (fConst1 * (1.07969798611464e-18 + (fConst1 * (5.2144154673581e-20 + (fConst1 * (9.7683567600612e-23 + (fConst1 * (1.1453389852842e-25 + fConst67)))))))));
	fConst69 = (9.65744972703433e-31 * fConst1);
	fConst70 = ((fConst1 * (2.88264605310366e-21 + (fConst1 * ((fConst1 * (3.08822188644282e-26 - fConst69)) - 4.82624719521696e-23)))) - 1.49007855810795e-20);
	fConst71 = (7.18082556296232e-31 * fConst1);
	fConst72 = (fConst1 * ((fConst1 * (1.81635217972948e-23 + (fConst1 * (fConst71 - 1.2196809675607e-26)))) - 9.8345184835125e-22));
	fConst73 = (7.16633351212421e-31 * fConst1);
	fConst74 = ((fConst1 * (1.21592229012527e-21 + (fConst1 * ((fConst1 * (1.22012125074374e-26 - fConst73)) - 1.83126711766163e-23)))) - 1.2608516331659e-20);
	fConst75 = ((fConst1 * (3.76182116601294e-18 + (fConst1 * ((fConst1 * (2.55142258602227e-22 + (fConst1 * (fConst2 - 1.05561747816346e-26)))) - 1.48648313435063e-19)))) - 3.09198451037471e-17);
	fConst76 = (fConst1 * ((fConst1 * (4.87042253786579e-20 + (fConst1 * ((fConst1 * (3.19373566665743e-26 - fConst65)) - 8.90038927961101e-23)))) - 3.50713071672392e-19));
	fConst77 = ((fConst1 * (1.07969798611464e-18 + (fConst1 * ((fConst1 * (9.7683567600612e-23 + (fConst1 * (fConst67 - 1.1453389852842e-25)))) - 5.2144154673581e-20)))) - 5.31383441927866e-18);
	fConst78 = (3.02070496506072e-29 * fConst1);
	fConst79 = ((fConst1 * (7.52364233202588e-18 + (fConst16 * ((fConst1 * (4.22246991265385e-26 - fConst78)) - 5.10284517204454e-22)))) - 1.23679380414989e-16);
	fConst80 = (2.57907405349142e-28 * fConst1);
	fConst81 = (fConst1 * ((fConst16 * (1.7800778559222e-22 + (fConst1 * (fConst80 - 1.27749426666297e-25)))) - 7.01426143344783e-19));
	fConst82 = (1.0332413167573e-27 * fConst1);
	fConst83 = ((fConst1 * (2.15939597222928e-18 + (fConst16 * ((fConst1 * (4.5813559411368e-25 - fConst82)) - 1.95367135201224e-22)))) - 2.12553376771146e-17);
	fConst84 = (7.55176241265181e-29 * fConst1);
	fConst85 = ((fConst1 * ((fConst1 * (4.4594494030519e-19 + (fConst1 * ((fConst1 * (fConst84 - 5.27808739081731e-26)) - 2.55142258602227e-22)))) - 3.76182116601294e-18)) - 1.54599225518736e-16);
	fConst86 = (6.44768513372856e-28 * fConst1);
	fConst87 = (fConst1 * (3.50713071672392e-19 + (fConst1 * ((fConst1 * (8.90038927961101e-23 + (fConst1 * (1.59686783332872e-25 - fConst86)))) - 1.46112676135974e-19))));
	fConst88 = (2.58310329189325e-27 * fConst1);
	fConst89 = ((fConst1 * ((fConst1 * (1.56432464020743e-19 + (fConst1 * ((fConst1 * (fConst88 - 5.726694926421e-25)) - 9.7683567600612e-23)))) - 1.07969798611464e-18)) - 2.65691720963933e-17);
	fConst90 = ((fConst16 * (1.02056903440891e-21 - (1.00690165502024e-28 * fConst16))) - 1.50472846640518e-17);
	fConst91 = (1.40285228668957e-18 + (fConst16 * ((8.59691351163808e-28 * fConst16) - 3.5601557118444e-22)));
	fConst92 = ((fConst16 * (3.90734270402448e-22 - (3.44413772252433e-27 * fConst16))) - 4.31879194445857e-18);
	fConst93 = (1.54599225518736e-16 + (fConst1 * ((fConst1 * ((fConst1 * ((fConst1 * (5.27808739081731e-26 + fConst84)) - 2.55142258602227e-22)) - 4.4594494030519e-19)) - 3.76182116601294e-18)));
	fConst94 = (fConst1 * (3.50713071672392e-19 + (fConst1 * (1.46112676135974e-19 + (fConst1 * (8.90038927961101e-23 + (fConst1 * (0 - (1.59686783332872e-25 + fConst86)))))))));
	fConst95 = (2.65691720963933e-17 + (fConst1 * ((fConst1 * ((fConst1 * ((fConst1 * (5.726694926421e-25 + fConst88)) - 9.7683567600612e-23)) - 1.56432464020743e-19)) - 1.07969798611464e-18)));
	fConst96 = (1.23679380414989e-16 + (fConst1 * (7.52364233202588e-18 + (fConst16 * ((fConst1 * (0 - (4.22246991265385e-26 + fConst78))) - 5.10284517204454e-22)))));
	fConst97 = (fConst1 * ((fConst16 * (1.7800778559222e-22 + (fConst1 * (1.27749426666297e-25 + fConst80)))) - 7.01426143344783e-19));
	fConst98 = (2.12553376771146e-17 + (fConst1 * (2.15939597222928e-18 + (fConst16 * ((fConst1 * (0 - (4.5813559411368e-25 + fConst82))) - 1.95367135201224e-22)))));
	fConst99 = (5.7944698362206e-30 * fConst1);
	fConst100 = ((fConst16 * (9.65249439043393e-23 + (fConst1 * (fConst99 - 1.23528875457713e-25)))) - 2.98015711621591e-20);
	fConst101 = (4.30849533777739e-30 * fConst1);
	fConst102 = (fConst16 * ((fConst1 * (4.87872387024281e-26 - fConst101)) - 3.63270435945895e-23));
	fConst103 = (4.29980010727452e-30 * fConst1);
	fConst104 = ((fConst16 * (3.66253423532326e-23 + (fConst1 * (fConst103 - 4.88048500297496e-26)))) - 2.5217032663318e-20);
	fConst105 = (1.44861745905515e-29 * fConst1);
	fConst106 = (1.49007855810795e-20 + (fConst1 * ((fConst1 * (4.82624719521696e-23 + (fConst1 * (1.54411094322141e-25 - fConst105)))) - 8.64793815931099e-21)));
	fConst107 = (1.07712383444435e-29 * fConst1);
	fConst108 = (fConst1 * (2.95035554505375e-21 + (fConst1 * ((fConst1 * (fConst107 - 6.09840483780351e-26)) - 1.81635217972948e-23))));
	fConst109 = (1.07495002681863e-29 * fConst1);
	fConst110 = (1.2608516331659e-20 + (fConst1 * ((fConst1 * (1.83126711766163e-23 + (fConst1 * (6.1006062537187e-26 - fConst109)))) - 3.64776687037582e-21)));
	fConst111 = (5.96031423243182e-20 + (fConst16 * ((1.93148994540687e-29 * fConst16) - 1.93049887808679e-22)));
	fConst112 = (fConst16 * (7.2654087189179e-23 - (1.43616511259246e-29 * fConst16)));
	fConst113 = (5.0434065326636e-20 + (fConst16 * ((1.43326670242484e-29 * fConst16) - 7.32506847064652e-23)));
	fConst114 = (1.49007855810795e-20 + (fConst1 * (8.64793815931099e-21 + (fConst1 * (4.82624719521696e-23 + (fConst1 * (0 - (1.54411094322141e-25 + fConst105))))))));
	fConst115 = (fConst1 * ((fConst1 * ((fConst1 * (6.09840483780351e-26 + fConst107)) - 1.81635217972948e-23)) - 2.95035554505375e-21));
	fConst116 = (1.2608516331659e-20 + (fConst1 * (3.64776687037582e-21 + (fConst1 * (1.83126711766163e-23 + (fConst1 * (0 - (6.1006062537187e-26 + fConst109))))))));
	fConst117 = ((fConst16 * (9.65249439043393e-23 + (fConst1 * (1.23528875457713e-25 + fConst99)))) - 2.98015711621591e-20);
	fConst118 = (fConst16 * ((fConst1 * (0 - (4.87872387024281e-26 + fConst101))) - 3.63270435945895e-23));
	fConst119 = ((fConst16 * (3.66253423532326e-23 + (fConst1 * (4.88048500297496e-26 + fConst103)))) - 2.5217032663318e-20);
	fConst120 = ((fConst1 * ((fConst1 * ((fConst1 * (0 - (3.08822188644282e-26 + fConst69))) - 4.82624719521696e-23)) - 2.88264605310366e-21)) - 1.49007855810795e-20);
	fConst121 = (fConst1 * (9.8345184835125e-22 + (fConst1 * (1.81635217972948e-23 + (fConst1 * (1.2196809675607e-26 + fConst71))))));
	fConst122 = ((fConst1 * ((fConst1 * ((fConst1 * (0 - (1.22012125074374e-26 + fConst73))) - 1.83126711766163e-23)) - 1.21592229012527e-21)) - 1.2608516331659e-20);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlow0 = (fConst4 * double(fslider0));
	double 	fSlow1 = (0.007000000000000006 * double(fslider1));
	double 	fSlow2 = (0.01 * double(fslider2));
	double 	fSlow3 = (0.007000000000000006 * double(fslider3));
	int 	iSlow4 = int(double(fcheckbox0));
	double 	fSlow5 = (1 - fSlow2);
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		fRec2[0] = (fRec2[1] + (fSlow0 * (0 - fRec0[1])));
		fRec1[0] = ((1 + (fRec1[1] + (fSlow0 * fRec2[0]))) - iVec0[1]);
		fRec0[0] = fRec1[0];
		fRec5[0] = ((0.993 * fRec5[1]) + fSlow1);
		double fTemp0 = (8.02877371041363e-18 + (fConst1 * (fConst8 + (fConst6 * fRec5[0]))));
		double fTemp1 = (double)input0[i];
		fRec6[0] = ((fSlow2 * fTemp1) - (((((((((fRec6[1] * (6.42301896833091e-17 + (fConst1 * (fConst35 + (fConst34 * fRec5[0]))))) + (fRec6[2] * (2.24805663891582e-16 + (fConst1 * (fConst33 + (fConst32 * fRec5[0])))))) + (fRec6[3] * (4.49611327783164e-16 + (fConst1 * (fConst31 + (fConst30 * fRec5[0])))))) + (fRec6[4] * (5.62014159728954e-16 + (fConst16 * (fConst29 + (fConst28 * fRec5[0])))))) + (fRec6[5] * (4.49611327783164e-16 + (fConst1 * (fConst27 + (fConst25 * fRec5[0])))))) + (fRec6[6] * (2.24805663891582e-16 + (fConst1 * (fConst23 + (fConst21 * fRec5[0])))))) + (fRec6[7] * (6.42301896833091e-17 + (fConst1 * (fConst19 + (fConst17 * fRec5[0])))))) + (fRec6[8] * (8.02877371041363e-18 + (fConst1 * (fConst14 + (fConst13 * fRec5[0])))))) / fTemp0));
		double fTemp2 = (fConst60 * ((((((((((fRec6[0] * (fConst59 + (fConst58 * fRec5[0]))) + (fRec6[1] * (fConst57 + (fConst56 * fRec5[0])))) + (fRec6[2] * (fConst55 + (fConst54 * fRec5[0])))) + (fRec6[3] * (fConst53 + (fConst52 * fRec5[0])))) + (fConst1 * (fRec6[4] * (fConst51 + (fConst50 * fRec5[0]))))) + (fRec6[5] * (fConst49 + (fConst47 * fRec5[0])))) + (fRec6[6] * (fConst45 + (fConst42 * fRec5[0])))) + (fRec6[7] * (fConst39 + (fConst37 * fRec5[0])))) + (fRec6[8] * (fConst12 + (fConst10 * fRec5[0])))) / fTemp0));
		double fTemp3 = fabs(fTemp2);
		fRec4[0] = ((fConst61 * max(fTemp3, fRec4[1])) + (fConst62 * fTemp3));
		fRec3[0] = ((fConst63 * fRec3[1]) + (fConst64 * fRec4[0]));
		fRec7[0] = ((0.993 * fRec7[1]) + fSlow3);
		double fTemp4 = ((iSlow4==0)? fRec7[0] : ((iSlow4==1)?max(0.09, min(0.9, fRec3[0])):max(0.09, min(0.9, (0.5 * (1 + fRec0[0]))))) );
		double fTemp5 = (8.05126427163433e-17 + (fConst1 * ((fTemp4 * (fConst68 + (fConst66 * fTemp4))) + fConst3)));
		fRec8[0] = (fTemp2 - (((((((fRec8[1] * (4.8307585629806e-16 + (fConst1 * ((fTemp4 * (fConst98 + (fConst97 * fTemp4))) + fConst96)))) + (fRec8[2] * (1.20768964074515e-15 + (fConst1 * ((fTemp4 * (fConst95 + (fConst94 * fTemp4))) + fConst93))))) + (fRec8[3] * (1.61025285432687e-15 + (fConst16 * ((fTemp4 * (fConst92 + (fConst91 * fTemp4))) + fConst90))))) + (fRec8[4] * (1.20768964074515e-15 + (fConst1 * ((fTemp4 * (fConst89 + (fConst87 * fTemp4))) + fConst85))))) + (fRec8[5] * (4.8307585629806e-16 + (fConst1 * ((fTemp4 * (fConst83 + (fConst81 * fTemp4))) + fConst79))))) + (fRec8[6] * (8.05126427163433e-17 + (fConst1 * ((fTemp4 * (fConst77 + (fConst76 * fTemp4))) + fConst75))))) / fTemp5));
		output0[i] = (FAUSTFLOAT)((fSlow5 * fTemp1) + (fConst16 * ((((((((fRec8[0] * ((fTemp4 * (fConst122 + (fConst121 * fTemp4))) + fConst120)) + (fRec8[1] * ((fTemp4 * (fConst119 + (fConst118 * fTemp4))) + fConst117))) + (fRec8[2] * ((fTemp4 * (fConst116 + (fConst115 * fTemp4))) + fConst114))) + (fRec8[3] * ((fTemp4 * (fConst113 + (fConst112 * fTemp4))) + fConst111))) + (fRec8[4] * ((fTemp4 * (fConst110 + (fConst108 * fTemp4))) + fConst106))) + (fRec8[5] * ((fTemp4 * (fConst104 + (fConst102 * fTemp4))) + fConst100))) + (fRec8[6] * ((fTemp4 * (fConst74 + (fConst72 * fTemp4))) + fConst70))) / fTemp5)));
		// post processing
		for (int i=6; i>0; i--) fRec8[i] = fRec8[i-1];
		fRec7[1] = fRec7[0];
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		for (int i=8; i>0; i--) fRec6[i] = fRec6[i-1];
		fRec5[1] = fRec5[0];
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		iVec0[1] = iVec0[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("rolandwah.Fuzz",N_("Fuzz"),"S","",&fslider1, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("rolandwah.Wah",N_("Wah"),"S","",&fslider3, 0.5, 0.02, 1.0, 0.01);
	reg.registerVar("rolandwah.lfobpm",N_("Alien Freq"),"S",N_("LFO in Beats per Minute"),&fslider0, 24.0, 24.0, 3.6e+02, 1.0);
	static const value_pair fcheckbox0_values[] = {{"manual"},{"auto"},{"alien"},{0}};
	reg.registerEnumVar("rolandwah.mode","","B","",fcheckbox0_values,&fcheckbox0, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("rolandwah.wet_dry",N_("wet/dry"),"S",N_("percentage of processed signal in output signal"),&fslider2, 1e+02, 0.0, 1e+02, 1.0);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("rolandwah" "." p)

b.openHorizontalhideBox("");
    b.create_master_slider(PARAM("Wah"), "Wah");
b.closeBox();
b.openHorizontalBox("");

    b.create_selector(PARAM("mode"), "Mode");
    b.create_small_rackknobr(PARAM("lfobpm"), "Alien Freq");
    b.create_small_rackknobr(PARAM("Fuzz"), "Fuzz");
    b.create_small_rackknobr(PARAM("Wah"), "Wah");
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

} // end namespace rolandwah
} // end namespace pluginlib
