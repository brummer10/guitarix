// generated from file '../src/plugins/ffreak.dsp' by dsp2cc:
// Code generated with Faust 0.9.73 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

#include "trany.h"
#include <string.h>

namespace pluginlib {
namespace ffreak {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	double 	fConst0;
	double 	fConst1;
	double 	fConst2;
	FAUSTFLOAT 	fslider0;
	double 	fRec0[2];
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	double 	fConst9;
	double 	fConst10;
	FAUSTFLOAT 	fslider1;
	double 	fRec1[2];
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
	FAUSTFLOAT 	fslider2;
	double 	fRec2[2];
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
	double 	fConst92;
	double 	fConst93;
	double 	fConst94;
	double 	fConst95;
	double 	fConst96;
	double 	fConst97;
	double 	fConst98;
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
	double 	fRec3[6];
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
	double 	fConst123;
	double 	fConst124;
	double 	fConst125;
	double 	fConst126;
	double 	fConst127;
	double 	fConst128;
	double 	fConst129;
	double 	fConst130;
	double 	fConst131;
	double 	fConst132;
	double 	fConst133;
	double 	fConst134;
	double 	fConst135;
	double 	fConst136;
	double 	fConst137;
	double 	fConst138;
	double 	fConst139;
	double 	fConst140;
	double 	fConst141;
	double 	fConst142;
	double 	fConst143;
	double 	fConst144;
	double 	fConst145;
	double 	fConst146;
	double 	fConst147;
	double 	fConst148;
	double 	fConst149;
	double 	fConst150;
	double 	fConst151;
	double 	fConst152;
	double 	fConst153;
	double 	fConst154;
	double 	fConst155;
	double 	fConst156;
	double 	fConst157;
	double 	fConst158;
	double 	fConst159;
	double 	fConst160;
	double 	fConst161;
	double 	fConst162;
	double 	fConst163;
	double 	fConst164;
	double 	fConst165;
	double 	fConst166;
	double 	fConst167;
	double 	fConst168;
	double 	fConst169;

	int samplingFreq;
	gx_resample::FixedRateResampler smpCl;
	double 	fVecCl0[2];
	double 	fRecCl7[2];
	double 	fRecCl6[3];
	int 	iConstCl0;
	double 	fConstCl1;
	double 	fConstCl2;
	double 	fConstCl3;
	double 	fConstCl4;
	double 	fRecCl8[2];
	double 	fRecCl5[3];
	double 	fConstCl5;
	double 	fConstCl6;
	double 	fConstCl7;
	double 	fConstCl8;
	double 	fConstCl9;
	double 	fRecCl4[2];
	double 	fRecCl3[2];
	double 	fRecCl2[3];
	double 	fRecCl9[2];
	double 	fRecCl1[3];
	double 	fRecCl0[2];

	FAUSTFLOAT fsliderdw0;
	FAUSTFLOAT 	fsliderV0;
	double 	fRecV0[2];
	void clear_state_f();
	int load_ui_f(const UiBuilder& b, int form);
	static const char *glade_def;
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
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<6; i++) fRec3[i] = 0;

	for (int i=0; i<2; i++) fVecCl0[i] = 0;
	for (int i=0; i<2; i++) fRecCl7[i] = 0;
	for (int i=0; i<3; i++) fRecCl6[i] = 0;
	for (int i=0; i<2; i++) fRecCl8[i] = 0;
	for (int i=0; i<3; i++) fRecCl5[i] = 0;
	for (int i=0; i<2; i++) fRecCl4[i] = 0;
	for (int i=0; i<2; i++) fRecCl3[i] = 0;
	for (int i=0; i<3; i++) fRecCl2[i] = 0;
	for (int i=0; i<2; i++) fRecCl9[i] = 0;
	for (int i=0; i<3; i++) fRecCl1[i] = 0;
	for (int i=0; i<2; i++) fRecCl0[i] = 0;

	for (int i=0; i<2; i++) fRecV0[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = double(min(192000, max(1, fSamplingFreq)));
	fConst1 = (8.04220615975416e-24 * fConst0);
	fConst2 = (2.93784119708281e-14 + (fConst0 * (2.24958749395832e-14 + (fConst0 * (9.44004344622598e-17 + (fConst0 * (7.95599798455062e-20 + fConst1)))))));
	fConst3 = (7.85412319843039e-24 * fConst0);
	fConst4 = ((fConst0 * ((fConst0 * ((fConst0 * (0 - (7.78792746651557e-20 + fConst3))) - 9.37831383212833e-17)) - 2.23954390036707e-14)) - 6.98094898928731e-15);
	fConst5 = (3.92585764869983e-15 + (fConst0 * (4.00054450346221e-15 + (fConst0 * (7.37353569889028e-17 + (fConst0 * (7.72040670186403e-20 + fConst1)))))));
	fConst6 = (fConst0 * ((fConst0 * ((fConst0 * (0 - (7.55784595381368e-20 + fConst3))) - 7.35486357301907e-17)) - 3.92585764869983e-15));
	fConst7 = (5.58465983797742e-24 * fConst0);
	fConst8 = (fConst0 * (2.62717307381705e-15 + (fConst0 * (3.19454127568418e-17 + (fConst0 * (3.42119219586653e-20 + fConst7))))));
	fConst9 = (5.71839588129828e-24 * fConst0);
	fConst10 = ((fConst0 * ((fConst0 * ((fConst0 * (0 - (3.49001694087957e-20 + fConst9))) - 3.20489931550839e-17)) - 2.65988017960024e-15)) - 2.62717307381705e-15);
	fConst11 = (6.70053233478594e-24 * fConst0);
	fConst12 = ((fConst0 * ((fConst0 * ((fConst0 * (0 - (5.95782688271891e-20 + fConst11))) - 1.90595008624394e-17)) - 1.88638248347695e-16)) - 2.17339588935373e-16);
	fConst13 = (6.5437965336828e-24 * fConst0);
	fConst14 = (5.00381548719698e-17 + (fConst0 * (1.66102929456909e-16 + (fConst0 * (1.85568523263077e-17 + (fConst0 * (5.81782503663661e-20 + fConst13)))))));
	fConst15 = ((fConst0 * ((fConst0 * ((fConst0 * (0 - (5.76153907610498e-20 + fConst11))) - 3.80725717138185e-18)) - 3.24770777204502e-17)) - 2.81398235873666e-17);
	fConst16 = (fConst0 * (2.81398235873666e-17 + (fConst0 * (3.66325429672488e-18 + (fConst0 * (5.62612870500992e-20 + fConst13))))));
	fConst17 = (4.65295447579145e-24 * fConst0);
	fConst18 = (fConst0 * ((fConst0 * ((fConst0 * (0 - (2.3734396603456e-20 + fConst17))) - 2.32762902199934e-18)) - 1.88310920685509e-17));
	fConst19 = (4.76440117855884e-24 * fConst0);
	fConst20 = (1.88310920685509e-17 + (fConst0 * (2.16097599157672e-17 + (fConst0 * (2.40711435730575e-18 + (fConst0 * (2.43075314241076e-20 + fConst19)))))));
	fConst21 = (1.87753470001854e-18 * fConst0);
	fConst22 = (fConst0 * (1.56079959618259e-14 - fConst21));
	fConst23 = (2.70062186191777e-18 * fConst0);
	fConst24 = (1.56079959618259e-14 + (fConst0 * (fConst23 - 2.24522189930045e-14)));
	fConst25 = (2.79019064029245e-21 * fConst0);
	fConst26 = (fConst0 * (fConst25 - 1.39597416617602e-17));
	fConst27 = (4.01337447559171e-21 * fConst0);
	fConst28 = ((fConst0 * (2.00823037773142e-17 - fConst27)) - 1.39597416617602e-17);
	fConst29 = (2.3166360517034e-21 * fConst0);
	fConst30 = (fConst0 * (1.15904771305196e-17 - fConst29));
	fConst31 = (3.33595591445278e-21 * fConst0);
	fConst32 = (1.15904771305196e-17 + (fConst0 * (fConst31 - 1.66926037039994e-17)));
	fConst33 = (1.5588772005669e-18 * fConst0);
	fConst34 = (fConst0 * (fConst33 - 1.29589876827259e-14));
	fConst35 = (2.24478316881626e-18 * fConst0);
	fConst36 = ((fConst0 * (1.86625011403253e-14 - fConst35)) - 1.29589876827259e-14);
	fConst37 = ((fConst0 * (2.24958749395832e-14 + (fConst0 * ((fConst0 * (7.95599798455062e-20 - fConst1)) - 9.44004344622598e-17)))) - 2.93784119708281e-14);
	fConst38 = (6.98094898928731e-15 + (fConst0 * ((fConst0 * (9.37831383212833e-17 + (fConst0 * (fConst3 - 7.78792746651557e-20)))) - 2.23954390036707e-14)));
	fConst39 = ((fConst0 * (4.00054450346221e-15 + (fConst0 * ((fConst0 * (7.72040670186403e-20 - fConst1)) - 7.37353569889028e-17)))) - 3.92585764869983e-15);
	fConst40 = (fConst0 * ((fConst0 * (7.35486357301907e-17 + (fConst0 * (fConst3 - 7.55784595381368e-20)))) - 3.92585764869983e-15));
	fConst41 = (fConst0 * (2.62717307381705e-15 + (fConst0 * ((fConst0 * (3.42119219586653e-20 - fConst7)) - 3.19454127568418e-17))));
	fConst42 = (2.62717307381705e-15 + (fConst0 * ((fConst0 * (3.20489931550839e-17 + (fConst0 * (fConst9 - 3.49001694087957e-20)))) - 2.65988017960024e-15)));
	fConst43 = (2.17339588935373e-16 + (fConst0 * ((fConst0 * (1.90595008624394e-17 + (fConst0 * (fConst11 - 5.95782688271891e-20)))) - 1.88638248347695e-16)));
	fConst44 = ((fConst0 * (1.66102929456909e-16 + (fConst0 * ((fConst0 * (5.81782503663661e-20 - fConst13)) - 1.85568523263077e-17)))) - 5.00381548719698e-17);
	fConst45 = (2.81398235873666e-17 + (fConst0 * ((fConst0 * (3.80725717138185e-18 + (fConst0 * (fConst11 - 5.76153907610498e-20)))) - 3.24770777204502e-17)));
	fConst46 = (fConst0 * (2.81398235873666e-17 + (fConst0 * ((fConst0 * (5.62612870500992e-20 - fConst13)) - 3.66325429672488e-18))));
	fConst47 = (fConst0 * ((fConst0 * (2.32762902199934e-18 + (fConst0 * (fConst17 - 2.3734396603456e-20)))) - 1.88310920685509e-17));
	fConst48 = ((fConst0 * (2.16097599157672e-17 + (fConst0 * ((fConst0 * (2.43075314241076e-20 - fConst19)) - 2.40711435730575e-18)))) - 1.88310920685509e-17);
	fConst49 = (4.02110307987708e-23 * fConst0);
	fConst50 = ((fConst0 * (2.24958749395832e-14 + (fConst0 * (9.44004344622598e-17 + (fConst0 * (fConst49 - 2.38679939536519e-19)))))) - 8.81352359124845e-14);
	fConst51 = (3.92706159921519e-23 * fConst0);
	fConst52 = (2.09428469678619e-14 + (fConst0 * ((fConst0 * ((fConst0 * (2.33637823995467e-19 - fConst51)) - 9.37831383212833e-17)) - 2.23954390036707e-14)));
	fConst53 = ((fConst0 * (4.00054450346221e-15 + (fConst0 * (7.37353569889028e-17 + (fConst0 * (fConst49 - 2.31612201055921e-19)))))) - 1.17775729460995e-14);
	fConst54 = (fConst0 * ((fConst0 * ((fConst0 * (2.2673537861441e-19 - fConst51)) - 7.35486357301907e-17)) - 3.92585764869983e-15));
	fConst55 = (2.79232991898871e-23 * fConst0);
	fConst56 = (fConst0 * (2.62717307381705e-15 + (fConst0 * (3.19454127568418e-17 + (fConst0 * (fConst55 - 1.02635765875996e-19))))));
	fConst57 = (2.85919794064914e-23 * fConst0);
	fConst58 = (7.88151922145115e-15 + (fConst0 * ((fConst0 * ((fConst0 * (1.04700508226387e-19 - fConst57)) - 3.20489931550839e-17)) - 2.65988017960024e-15)));
	fConst59 = (3.35026616739297e-23 * fConst0);
	fConst60 = (6.5201876680612e-16 + (fConst0 * ((fConst0 * ((fConst0 * (1.78734806481567e-19 - fConst59)) - 1.90595008624394e-17)) - 1.88638248347695e-16)));
	fConst61 = (3.2718982668414e-23 * fConst0);
	fConst62 = ((fConst0 * (1.66102929456909e-16 + (fConst0 * (1.85568523263077e-17 + (fConst0 * (fConst61 - 1.74534751099098e-19)))))) - 1.50114464615909e-16);
	fConst63 = (8.44194707620996e-17 + (fConst0 * ((fConst0 * ((fConst0 * (1.72846172283149e-19 - fConst59)) - 3.80725717138185e-18)) - 3.24770777204502e-17)));
	fConst64 = (fConst0 * (2.81398235873666e-17 + (fConst0 * (3.66325429672488e-18 + (fConst0 * (fConst61 - 1.68783861150298e-19))))));
	fConst65 = (2.32647723789573e-23 * fConst0);
	fConst66 = (fConst0 * ((fConst0 * ((fConst0 * (7.12031898103681e-20 - fConst65)) - 2.32762902199934e-18)) - 1.88310920685509e-17));
	fConst67 = (2.38220058927942e-23 * fConst0);
	fConst68 = ((fConst0 * (2.16097599157672e-17 + (fConst0 * (2.40711435730575e-18 + (fConst0 * (fConst67 - 7.29225942723227e-20)))))) - 5.64932762056526e-17);
	fConst69 = (8.04220615975416e-23 * fConst0);
	fConst70 = ((fConst0 * ((fConst0 * (1.8880086892452e-16 + (fConst0 * (1.59119959691012e-19 - fConst69)))) - 4.49917498791663e-14)) - 5.87568239416563e-14);
	fConst71 = (7.85412319843039e-23 * fConst0);
	fConst72 = (1.39618979785746e-14 + (fConst0 * (4.47908780073414e-14 + (fConst0 * ((fConst0 * (fConst71 - 1.55758549330311e-19)) - 1.87566276642567e-16)))));
	fConst73 = ((fConst0 * ((fConst0 * (1.47470713977806e-16 + (fConst0 * (1.54408134037281e-19 - fConst69)))) - 8.00108900692442e-15)) - 7.85171529739967e-15);
	fConst74 = (fConst0 * (7.85171529739967e-15 + (fConst0 * ((fConst0 * (fConst71 - 1.51156919076274e-19)) - 1.47097271460381e-16))));
	fConst75 = (5.58465983797742e-23 * fConst0);
	fConst76 = (fConst0 * ((fConst0 * (6.38908255136836e-17 + (fConst0 * (6.84238439173305e-20 - fConst75)))) - 5.2543461476341e-15));
	fConst77 = (5.71839588129828e-23 * fConst0);
	fConst78 = (5.2543461476341e-15 + (fConst0 * (5.31976035920048e-15 + (fConst0 * ((fConst0 * (fConst77 - 6.98003388175914e-20)) - 6.40979863101677e-17)))));
	fConst79 = (6.70053233478594e-23 * fConst0);
	fConst80 = (4.34679177870747e-16 + (fConst0 * (3.77276496695391e-16 + (fConst0 * ((fConst0 * (fConst79 - 1.19156537654378e-19)) - 3.81190017248789e-17)))));
	fConst81 = (6.5437965336828e-23 * fConst0);
	fConst82 = ((fConst0 * ((fConst0 * (3.71137046526154e-17 + (fConst0 * (1.16356500732732e-19 - fConst81)))) - 3.32205858913818e-16)) - 1.0007630974394e-16);
	fConst83 = (5.62796471747331e-17 + (fConst0 * (6.49541554409003e-17 + (fConst0 * ((fConst0 * (fConst79 - 1.152307815221e-19)) - 7.61451434276371e-18)))));
	fConst84 = (fConst0 * ((fConst0 * (7.32650859344976e-18 + (fConst0 * (1.12522574100198e-19 - fConst81)))) - 5.62796471747331e-17));
	fConst85 = (4.65295447579145e-23 * fConst0);
	fConst86 = (fConst0 * (3.76621841371018e-17 + (fConst0 * ((fConst0 * (fConst85 - 4.74687932069121e-20)) - 4.65525804399867e-18))));
	fConst87 = (4.76440117855884e-23 * fConst0);
	fConst88 = ((fConst0 * ((fConst0 * (4.81422871461151e-18 + (fConst0 * (4.86150628482152e-20 - fConst87)))) - 4.32195198315344e-17)) - 3.76621841371018e-17);
	fConst89 = (5.87568239416563e-14 + (fConst0 * ((fConst0 * ((fConst0 * (1.59119959691012e-19 + fConst69)) - 1.8880086892452e-16)) - 4.49917498791663e-14)));
	fConst90 = ((fConst0 * (4.47908780073414e-14 + (fConst0 * (1.87566276642567e-16 + (fConst0 * (0 - (1.55758549330311e-19 + fConst71))))))) - 1.39618979785746e-14);
	fConst91 = (7.85171529739967e-15 + (fConst0 * ((fConst0 * ((fConst0 * (1.54408134037281e-19 + fConst69)) - 1.47470713977806e-16)) - 8.00108900692442e-15)));
	fConst92 = (fConst0 * (7.85171529739967e-15 + (fConst0 * (1.47097271460381e-16 + (fConst0 * (0 - (1.51156919076274e-19 + fConst71)))))));
	fConst93 = (fConst0 * ((fConst0 * ((fConst0 * (6.84238439173305e-20 + fConst75)) - 6.38908255136836e-17)) - 5.2543461476341e-15));
	fConst94 = ((fConst0 * (5.31976035920048e-15 + (fConst0 * (6.40979863101677e-17 + (fConst0 * (0 - (6.98003388175914e-20 + fConst77))))))) - 5.2543461476341e-15);
	fConst95 = ((fConst0 * (3.77276496695391e-16 + (fConst0 * (3.81190017248789e-17 + (fConst0 * (0 - (1.19156537654378e-19 + fConst79))))))) - 4.34679177870747e-16);
	fConst96 = (1.0007630974394e-16 + (fConst0 * ((fConst0 * ((fConst0 * (1.16356500732732e-19 + fConst81)) - 3.71137046526154e-17)) - 3.32205858913818e-16)));
	fConst97 = ((fConst0 * (6.49541554409003e-17 + (fConst0 * (7.61451434276371e-18 + (fConst0 * (0 - (1.152307815221e-19 + fConst79))))))) - 5.62796471747331e-17);
	fConst98 = (fConst0 * ((fConst0 * ((fConst0 * (1.12522574100198e-19 + fConst81)) - 7.32650859344976e-18)) - 5.62796471747331e-17));
	fConst99 = (fConst0 * (3.76621841371018e-17 + (fConst0 * (4.65525804399867e-18 + (fConst0 * (0 - (4.74687932069121e-20 + fConst85)))))));
	fConst100 = (3.76621841371018e-17 + (fConst0 * ((fConst0 * ((fConst0 * (4.86150628482152e-20 + fConst87)) - 4.81422871461151e-18)) - 4.32195198315344e-17)));
	fConst101 = (8.81352359124845e-14 + (fConst0 * (2.24958749395832e-14 + (fConst0 * ((fConst0 * (0 - (2.38679939536519e-19 + fConst49))) - 9.44004344622598e-17)))));
	fConst102 = ((fConst0 * ((fConst0 * (9.37831383212833e-17 + (fConst0 * (2.33637823995467e-19 + fConst51)))) - 2.23954390036707e-14)) - 2.09428469678619e-14);
	fConst103 = (1.17775729460995e-14 + (fConst0 * (4.00054450346221e-15 + (fConst0 * ((fConst0 * (0 - (2.31612201055921e-19 + fConst49))) - 7.37353569889028e-17)))));
	fConst104 = (fConst0 * ((fConst0 * (7.35486357301907e-17 + (fConst0 * (2.2673537861441e-19 + fConst51)))) - 3.92585764869983e-15));
	fConst105 = (fConst0 * (2.62717307381705e-15 + (fConst0 * ((fConst0 * (0 - (1.02635765875996e-19 + fConst55))) - 3.19454127568418e-17))));
	fConst106 = ((fConst0 * ((fConst0 * (3.20489931550839e-17 + (fConst0 * (1.04700508226387e-19 + fConst57)))) - 2.65988017960024e-15)) - 7.88151922145115e-15);
	fConst107 = ((fConst0 * ((fConst0 * (1.90595008624394e-17 + (fConst0 * (1.78734806481567e-19 + fConst59)))) - 1.88638248347695e-16)) - 6.5201876680612e-16);
	fConst108 = (1.50114464615909e-16 + (fConst0 * (1.66102929456909e-16 + (fConst0 * ((fConst0 * (0 - (1.74534751099098e-19 + fConst61))) - 1.85568523263077e-17)))));
	fConst109 = ((fConst0 * ((fConst0 * (3.80725717138185e-18 + (fConst0 * (1.72846172283149e-19 + fConst59)))) - 3.24770777204502e-17)) - 8.44194707620996e-17);
	fConst110 = (fConst0 * (2.81398235873666e-17 + (fConst0 * ((fConst0 * (0 - (1.68783861150298e-19 + fConst61))) - 3.66325429672488e-18))));
	fConst111 = (fConst0 * ((fConst0 * (2.32762902199934e-18 + (fConst0 * (7.12031898103681e-20 + fConst65)))) - 1.88310920685509e-17));
	fConst112 = (5.64932762056526e-17 + (fConst0 * (2.16097599157672e-17 + (fConst0 * ((fConst0 * (0 - (7.29225942723227e-20 + fConst67))) - 2.40711435730575e-18)))));
	fConst113 = (5.63260410005562e-18 * fConst0);
	fConst114 = (fConst0 * (fConst113 - 1.56079959618259e-14));
	fConst115 = (8.10186558575332e-18 * fConst0);
	fConst116 = (1.56079959618259e-14 + (fConst0 * (2.24522189930045e-14 - fConst115)));
	fConst117 = (1.39509532014623e-20 * fConst0);
	fConst118 = (fConst0 * (4.18792249852806e-17 - fConst117));
	fConst119 = (2.00668723779585e-20 * fConst0);
	fConst120 = (1.39597416617602e-17 + (fConst0 * (fConst119 - 6.02469113319426e-17)));
	fConst121 = (1.1583180258517e-20 * fConst0);
	fConst122 = (fConst0 * (fConst121 - 3.47714313915589e-17));
	fConst123 = (1.66797795722639e-20 * fConst0);
	fConst124 = ((fConst0 * (5.00778111119983e-17 - fConst123)) - 1.15904771305196e-17);
	fConst125 = (4.67663160170071e-18 * fConst0);
	fConst126 = (fConst0 * (1.29589876827259e-14 - fConst125));
	fConst127 = (6.73434950644879e-18 * fConst0);
	fConst128 = ((fConst0 * (fConst127 - 1.86625011403253e-14)) - 1.29589876827259e-14);
	fConst129 = (3.75506940003708e-18 * fConst0);
	fConst130 = (fConst0 * (0 - (3.12159919236519e-14 + fConst129)));
	fConst131 = (5.40124372383555e-18 * fConst0);
	fConst132 = ((fConst0 * (4.4904437986009e-14 + fConst131)) - 3.12159919236519e-14);
	fConst133 = (2.79019064029245e-20 * fConst0);
	fConst134 = (fConst0 * (fConst133 - 2.79194833235204e-17));
	fConst135 = (4.01337447559171e-20 * fConst0);
	fConst136 = (2.79194833235204e-17 + (fConst0 * (4.01646075546284e-17 - fConst135)));
	fConst137 = (2.3166360517034e-20 * fConst0);
	fConst138 = (fConst0 * (2.31809542610393e-17 - fConst137));
	fConst139 = (3.33595591445278e-20 * fConst0);
	fConst140 = ((fConst0 * (fConst139 - 3.33852074079988e-17)) - 2.31809542610393e-17);
	fConst141 = (3.1177544011338e-18 * fConst0);
	fConst142 = (fConst0 * (2.59179753654518e-14 + fConst141));
	fConst143 = (4.48956633763253e-18 * fConst0);
	fConst144 = (2.59179753654518e-14 + (fConst0 * (0 - (3.73250022806505e-14 + fConst143))));
	fConst145 = (fConst0 * (3.12159919236519e-14 - fConst129));
	fConst146 = ((fConst0 * (fConst131 - 4.4904437986009e-14)) - 3.12159919236519e-14);
	fConst147 = (fConst0 * (0 - (2.79194833235204e-17 + fConst133)));
	fConst148 = ((fConst0 * (4.01646075546284e-17 + fConst135)) - 2.79194833235204e-17);
	fConst149 = (fConst0 * (2.31809542610393e-17 + fConst137));
	fConst150 = (2.31809542610393e-17 + (fConst0 * (0 - (3.33852074079988e-17 + fConst139))));
	fConst151 = (fConst0 * (fConst141 - 2.59179753654518e-14));
	fConst152 = (2.59179753654518e-14 + (fConst0 * (3.73250022806505e-14 - fConst143)));
	fConst153 = (fConst0 * (1.56079959618259e-14 + fConst113));
	fConst154 = (1.56079959618259e-14 + (fConst0 * (0 - (2.24522189930045e-14 + fConst115))));
	fConst155 = (fConst0 * (4.18792249852806e-17 + fConst117));
	fConst156 = ((fConst0 * (0 - (6.02469113319426e-17 + fConst119))) - 1.39597416617602e-17);
	fConst157 = (fConst0 * (0 - (3.47714313915589e-17 + fConst121)));
	fConst158 = (1.15904771305196e-17 + (fConst0 * (5.00778111119983e-17 + fConst123)));
	fConst159 = (fConst0 * (0 - (1.29589876827259e-14 + fConst125)));
	fConst160 = ((fConst0 * (1.86625011403253e-14 + fConst127)) - 1.29589876827259e-14);
	fConst161 = (fConst0 * (0 - (1.56079959618259e-14 + fConst21)));
	fConst162 = (1.56079959618259e-14 + (fConst0 * (2.24522189930045e-14 + fConst23)));
	fConst163 = (fConst0 * (0 - (1.39597416617602e-17 + fConst25)));
	fConst164 = (1.39597416617602e-17 + (fConst0 * (2.00823037773142e-17 + fConst27)));
	fConst165 = (fConst0 * (1.15904771305196e-17 + fConst29));
	fConst166 = ((fConst0 * (0 - (1.66926037039994e-17 + fConst31))) - 1.15904771305196e-17);
	fConst167 = (fConst0 * (1.29589876827259e-14 + fConst33));
	fConst168 = ((fConst0 * (0 - (1.86625011403253e-14 + fConst35))) - 1.29589876827259e-14);
	fConst169 = faustpower<2>(fConst0);

	samplingFreq = 96000;
	smpCl.setup(fSamplingFreq, samplingFreq);
	fSamplingFreq = samplingFreq;
	iConstCl0 = min(192000, max(1, fSamplingFreq));
	fConstCl1 = (1.0 / tan((270.1769682087222 / double(iConstCl0))));
	fConstCl2 = (1 + fConstCl1);
	fConstCl3 = (0.027 / fConstCl2);
	fConstCl4 = (0 - ((1 - fConstCl1) / fConstCl2));
	fConstCl5 = (1.0 / tan((97.38937226128358 / double(iConstCl0))));
	fConstCl6 = (0 - fConstCl5);
	fConstCl7 = (1 + fConstCl5);
	fConstCl8 = (0.025 / fConstCl7);
	fConstCl9 = (0 - ((1 - fConstCl5) / fConstCl7));

	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlowdw0 = (0.01 * fsliderdw0);
	double 	fSlowdw1 = (1 - fSlowdw0);
	FAUSTFLOAT 	dryinput[count];
	memcpy(&dryinput, input0, count * sizeof(float));

	double 	fSlowV0 = (0.0010000000000000009 * double(fsliderV0));

	double 	fSlow0 = (0.007000000000000006 * double(fslider0));
	double 	fSlow1 = (0.007000000000000006 * double(fslider1));
	double 	fSlow2 = (0.007000000000000006 * double(fslider2));
	for (int i=0; i<count; i++) {
		fRec0[0] = ((0.993 * fRec0[1]) + fSlow0);
		fRec1[0] = ((0.993 * fRec1[1]) + fSlow1);
		fRec2[0] = ((0.993 * fRec2[1]) + fSlow2);
		double fTemp0 = (6.98094898928731e-15 + ((fRec2[0] * ((fConst0 * (((fRec1[0] * (((fRec1[0] * (fConst20 + (fConst18 * fRec0[0]))) + (fConst16 * fRec0[0])) + fConst15)) + (fConst14 * fRec0[0])) + fConst12)) - 5.00381548719698e-17)) + (fConst0 * (((fRec1[0] * (((fRec1[0] * (fConst10 + (fConst8 * fRec0[0]))) + (fConst6 * fRec0[0])) + fConst5)) + (fConst4 * fRec0[0])) + fConst2))));
		fRec3[0] = ((double)input0[i] - ((((((fRec3[1] * (3.49047449464365e-14 + ((fRec2[0] * ((fConst0 * (((fRec1[0] * (((fRec1[0] * (fConst112 + (fConst111 * fRec0[0]))) + (fConst110 * fRec0[0])) + fConst109)) + (fConst108 * fRec0[0])) + fConst107)) - 2.50190774359849e-16)) + (fConst0 * (((fRec1[0] * (((fRec1[0] * (fConst106 + (fConst105 * fRec0[0]))) + (fConst104 * fRec0[0])) + fConst103)) + (fConst102 * fRec0[0])) + fConst101))))) + (fRec3[2] * (6.98094898928731e-14 + ((fRec2[0] * ((fConst0 * (((fRec1[0] * (((fRec1[0] * (fConst100 + (fConst99 * fRec0[0]))) + (fConst98 * fRec0[0])) + fConst97)) + (fConst96 * fRec0[0])) + fConst95)) - 5.00381548719698e-16)) + (fConst0 * (((fRec1[0] * (((fRec1[0] * (fConst94 + (fConst93 * fRec0[0]))) + (fConst92 * fRec0[0])) + fConst91)) + (fConst90 * fRec0[0])) + fConst89)))))) + (fRec3[3] * (6.98094898928731e-14 + ((fRec2[0] * ((fConst0 * (((fRec1[0] * (((fRec1[0] * (fConst88 + (fConst86 * fRec0[0]))) + (fConst84 * fRec0[0])) + fConst83)) + (fConst82 * fRec0[0])) + fConst80)) - 5.00381548719698e-16)) + (fConst0 * (((fRec1[0] * (((fRec1[0] * (fConst78 + (fConst76 * fRec0[0]))) + (fConst74 * fRec0[0])) + fConst73)) + (fConst72 * fRec0[0])) + fConst70)))))) + (fRec3[4] * (3.49047449464365e-14 + ((fRec2[0] * ((fConst0 * (((fRec1[0] * (((fRec1[0] * (fConst68 + (fConst66 * fRec0[0]))) + (fConst64 * fRec0[0])) + fConst63)) + (fConst62 * fRec0[0])) + fConst60)) - 2.50190774359849e-16)) + (fConst0 * (((fRec1[0] * (((fRec1[0] * (fConst58 + (fConst56 * fRec0[0]))) + (fConst54 * fRec0[0])) + fConst53)) + (fConst52 * fRec0[0])) + fConst50)))))) + (fRec3[5] * (6.98094898928731e-15 + ((fRec2[0] * ((fConst0 * (((fRec1[0] * (((fRec1[0] * (fConst48 + (fConst47 * fRec0[0]))) + (fConst46 * fRec0[0])) + fConst45)) + (fConst44 * fRec0[0])) + fConst43)) - 5.00381548719698e-17)) + (fConst0 * (((fRec1[0] * (((fRec1[0] * (fConst42 + (fConst41 * fRec0[0]))) + (fConst40 * fRec0[0])) + fConst39)) + (fConst38 * fRec0[0])) + fConst37)))))) / fTemp0));
		output0[i] = (FAUSTFLOAT)(fConst169 * (((((((fRec3[0] * (((fRec2[0] * ((fConst168 + (fConst167 * fRec0[0])) + (fConst0 * (fRec1[0] * (fConst166 + (fConst165 * fRec0[0])))))) + (fConst0 * (fRec1[0] * (fConst164 + (fConst163 * fRec0[0]))))) + (fConst162 + (fConst161 * fRec0[0])))) + (fRec3[1] * (((fRec2[0] * ((fConst160 + (fConst159 * fRec0[0])) + (fConst0 * (fRec1[0] * (fConst158 + (fConst157 * fRec0[0])))))) + (fConst0 * (fRec1[0] * (fConst156 + (fConst155 * fRec0[0]))))) + (fConst154 + (fConst153 * fRec0[0]))))) + (fRec3[2] * (((fRec2[0] * ((fConst152 + (fConst151 * fRec0[0])) + (fConst0 * (fRec1[0] * (fConst150 + (fConst149 * fRec0[0])))))) + (fConst0 * (fRec1[0] * (fConst148 + (fConst147 * fRec0[0]))))) + (fConst146 + (fConst145 * fRec0[0]))))) + (fRec3[3] * (((fRec2[0] * ((fConst144 + (fConst142 * fRec0[0])) + (fConst0 * (fRec1[0] * (fConst140 + (fConst138 * fRec0[0])))))) + (fConst0 * (fRec1[0] * (fConst136 + (fConst134 * fRec0[0]))))) + (fConst132 + (fConst130 * fRec0[0]))))) + (fRec3[4] * (((fRec2[0] * ((fConst128 + (fConst126 * fRec0[0])) + (fConst0 * (fRec1[0] * (fConst124 + (fConst122 * fRec0[0])))))) + (fConst0 * (fRec1[0] * (fConst120 + (fConst118 * fRec0[0]))))) + (fConst116 + (fConst114 * fRec0[0]))))) + (fRec3[5] * (((fRec2[0] * ((fConst36 + (fConst34 * fRec0[0])) + (fConst0 * (fRec1[0] * (fConst32 + (fConst30 * fRec0[0])))))) + (fConst0 * (fRec1[0] * (fConst28 + (fConst26 * fRec0[0]))))) + (fConst24 + (fConst22 * fRec0[0]))))) / fTemp0));
		// post processing
		for (int i=5; i>0; i--) fRec3[i] = fRec3[i-1];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
	}

	FAUSTFLOAT bufCl[smpCl.max_out_count(count)];
	int ReCount = smpCl.up(count, output0, bufCl);
	for (int i=0; i<ReCount; i++) {
		double fTemp0 = (double)bufCl[i];
		fVecCl0[0] = fTemp0;
		fRecCl7[0] = ((0.9302847925323914 * (fVecCl0[0] + fVecCl0[1])) - (0.8605695850647829 * fRecCl7[1]));
		fRecCl6[0] = (fRecCl7[0] - ((1.8405051250752198 * fRecCl6[1]) + (0.8612942439318627 * fRecCl6[2])));
		fRecCl8[0] = ((fConstCl4 * fRecCl8[1]) + (fConstCl3 * (fRecCl5[1] + fRecCl5[2])));
		fRecCl5[0] = (Ftrany(TRANY_TABLE_KT88_68k, ((fRecCl8[0] + (0.9254498422517706 * (fRecCl6[2] + (fRecCl6[0] + (2.0 * fRecCl6[1]))))) - 5.562895)) - 43.96685185185183);
		fRecCl4[0] = ((fConstCl9 * fRecCl4[1]) + (fConstCl8 * ((fConstCl5 * fRecCl5[0]) + (fConstCl6 * fRecCl5[1]))));
		fRecCl3[0] = ((0.9302847925323914 * (fRecCl4[0] + fRecCl4[1])) - (0.8605695850647829 * fRecCl3[1]));
		fRecCl2[0] = (fRecCl3[0] - ((1.8405051250752198 * fRecCl2[1]) + (0.8612942439318627 * fRecCl2[2])));
		fRecCl9[0] = ((fConstCl4 * fRecCl9[1]) + (fConstCl3 * (fRecCl1[1] + fRecCl1[2])));
		fRecCl1[0] = (Ftrany(TRANY_TABLE_KT88_68k, ((fRecCl9[0] + (0.9254498422517706 * (fRecCl2[2] + (fRecCl2[0] + (2.0 * fRecCl2[1]))))) - 5.562895)) - 43.96685185185183);
		fRecCl0[0] = ((fConstCl9 * fRecCl0[1]) + (fConstCl8 * ((fConstCl5 * fRecCl1[0]) + (fConstCl6 * fRecCl1[1]))));
		bufCl[i] = (FAUSTFLOAT)fRecCl0[0];
		// post processing
		fRecCl0[1] = fRecCl0[0];
		fRecCl1[2] = fRecCl1[1]; fRecCl1[1] = fRecCl1[0];
		fRecCl9[1] = fRecCl9[0];
		fRecCl2[2] = fRecCl2[1]; fRecCl2[1] = fRecCl2[0];
		fRecCl3[1] = fRecCl3[0];
		fRecCl4[1] = fRecCl4[0];
		fRecCl5[2] = fRecCl5[1]; fRecCl5[1] = fRecCl5[0];
		fRecCl8[1] = fRecCl8[0];
		fRecCl6[2] = fRecCl6[1]; fRecCl6[1] = fRecCl6[0];
		fRecCl7[1] = fRecCl7[0];
		fVecCl0[1] = fVecCl0[0];
	}
	smpCl.down(bufCl, output0);

	for (int i=0; i<count; i++) {
		fRecV0[0] = ((0.999 * fRecV0[1]) + fSlowV0);
		output0[i] = (FAUSTFLOAT)((double)output0[i] * fRecV0[0]);
		// post processing
		fRecV0[1] = fRecV0[0];
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
	reg.registerVar("ffreak.wet_dry",N_("Dry/Wet"),"S",N_("percentage of processed signal in output signal"),&fsliderdw0, 1e+02, 0.0, 1e+02, 1.0);
	reg.registerVar("ffreak.Level",N_("Level"),"S","",&fsliderV0, 0.5, 0.0, 1, 0.01);
	reg.registerVar("ffreak.Fuzz",N_("Fuzz"),"S","",&fslider0, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("ffreak.Gate",N_("Gate"),"S","",&fslider2, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("ffreak.Tone",N_("Tone"),"S","",&fslider1, 0.5, 0.0, 1.0, 0.01);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

const char *Dsp::glade_def = "\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<interface>\n\
  <!-- interface-requires gxwidgets 0.0 -->\n\
  <requires lib=\"gtk+\" version=\"2.20\"/>\n\
  <!-- interface-naming-policy project-wide -->\n\
  <object class=\"GtkWindow\" id=\"window1\">\n\
    <property name=\"can_focus\">False</property>\n\
    <child>\n\
      <object class=\"GtkVBox\" id=\"vbox1\">\n\
        <property name=\"visible\">True</property>\n\
        <property name=\"can_focus\">False</property>\n\
        <child>\n\
          <object class=\"GtkHBox\" id=\"rackbox\">\n\
            <property name=\"visible\">True</property>\n\
            <property name=\"can_focus\">False</property>\n\
            <property name=\"spacing\">4</property>\n\
            <child>\n\
              <object class=\"GtkHBox\" id=\"hbox1\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">False</property>\n\
                <property name=\"spacing\">10</property>\n\
                <child>\n\
                  <object class=\"GtkVBox\" id=\"vbox2\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
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
                  <object class=\"GtkVBox\" id=\"vbox3\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
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
                  <object class=\"GtkVBox\" id=\"vbox4\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
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
                  <object class=\"GtkVBox\" id=\"vbox5\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
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
                  <object class=\"GtkVBox\" id=\"vbox6\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
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
          <object class=\"GtkHBox\" id=\"minibox\">\n\
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
                <property name=\"xalign\">0</property>\n\
                <property name=\"label\" translatable=\"yes\">Level</property>\n\
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
