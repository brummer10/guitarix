// generated from file '../src/plugins/ffreak.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"
#include "trany.h"

namespace pluginlib {
namespace ffreak {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	FAUSTFLOAT 	fslider1;
	double 	fRec8[2];
	double 	fConst9;
	double 	fConst10;
	double 	fConst11;
	double 	fConst12;
	double 	fConst13;
	double 	fConst14;
	double 	fConst15;
	double 	fConst16;
	FAUSTFLOAT 	fslider2;
	double 	fRec9[2];
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
	FAUSTFLOAT 	fslider3;
	double 	fRec10[2];
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
	double 	fConst113;
	double 	fConst114;
	double 	fConst115;
	double 	fConst116;
	double 	fConst117;
	double 	fConst118;
	double 	fRec11[6];
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
	double 	fConst170;
	double 	fConst171;
	double 	fConst172;
	double 	fConst173;
	double 	fConst174;
	FAUSTFLOAT 	fslider4;
	double 	fRec12[2];
	double 	fVec0[2];
	double 	fConst175;
	double 	fConst176;
	double 	fConst177;
	double 	fRec7[2];
	double 	fRec6[3];
	double 	fConst178;
	double 	fConst179;
	double 	fConst180;
	double 	fConst181;
	double 	fRec13[2];
	double 	fRec5[3];
	double 	fConst182;
	double 	fConst183;
	double 	fConst184;
	double 	fConst185;
	double 	fConst186;
	double 	fRec4[2];
	double 	fConst187;
	double 	fRec3[2];
	double 	fRec2[3];
	double 	fRec14[2];
	double 	fRec1[3];
	double 	fRec0[2];
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
	id = "ffreak";
	name = N_("Fat Furry Freak");
	groups = 0;
	description = N_("Extreme Bass Fuzz Monster"); // description (tooltip)
	category = N_("Fuzz");       // category
	shortname = N_("Fat Freak");     // shortname
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
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<6; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<3; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = tan((50265.48245743669 / double(iConst0)));
	fConst2 = (2 * (1 - (1.0 / faustpower<2>(fConst1))));
	fConst3 = (1.0 / fConst1);
	fConst4 = (1 + ((fConst3 - 1.0000000000000004) / fConst1));
	fConst5 = (1.0 / (1 + ((1.0000000000000004 + fConst3) / fConst1)));
	fConst6 = double(iConst0);
	fConst7 = (8.04220615975416e-24 * fConst6);
	fConst8 = (2.93784119708281e-14 + (fConst6 * (2.24958749395832e-14 + (fConst6 * (9.44004344622598e-17 + (fConst6 * (7.95599798455062e-20 + fConst7)))))));
	fConst9 = (7.85412319843039e-24 * fConst6);
	fConst10 = ((fConst6 * ((fConst6 * ((fConst6 * (0 - (7.78792746651557e-20 + fConst9))) - 9.37831383212833e-17)) - 2.23954390036707e-14)) - 6.98094898928731e-15);
	fConst11 = (3.92585764869983e-15 + (fConst6 * (4.00054450346221e-15 + (fConst6 * (7.37353569889028e-17 + (fConst6 * (7.72040670186403e-20 + fConst7)))))));
	fConst12 = (fConst6 * ((fConst6 * ((fConst6 * (0 - (7.55784595381368e-20 + fConst9))) - 7.35486357301907e-17)) - 3.92585764869983e-15));
	fConst13 = (5.58465983797742e-24 * fConst6);
	fConst14 = (fConst6 * (2.62717307381705e-15 + (fConst6 * (3.19454127568418e-17 + (fConst6 * (3.42119219586653e-20 + fConst13))))));
	fConst15 = (5.71839588129828e-24 * fConst6);
	fConst16 = ((fConst6 * ((fConst6 * ((fConst6 * (0 - (3.49001694087957e-20 + fConst15))) - 3.20489931550839e-17)) - 2.65988017960024e-15)) - 2.62717307381705e-15);
	fConst17 = (6.70053233478594e-24 * fConst6);
	fConst18 = ((fConst6 * ((fConst6 * ((fConst6 * (0 - (5.95782688271891e-20 + fConst17))) - 1.90595008624394e-17)) - 1.88638248347695e-16)) - 2.17339588935373e-16);
	fConst19 = (6.5437965336828e-24 * fConst6);
	fConst20 = (5.00381548719698e-17 + (fConst6 * (1.66102929456909e-16 + (fConst6 * (1.85568523263077e-17 + (fConst6 * (5.81782503663661e-20 + fConst19)))))));
	fConst21 = ((fConst6 * ((fConst6 * ((fConst6 * (0 - (5.76153907610498e-20 + fConst17))) - 3.80725717138185e-18)) - 3.24770777204502e-17)) - 2.81398235873666e-17);
	fConst22 = (fConst6 * (2.81398235873666e-17 + (fConst6 * (3.66325429672488e-18 + (fConst6 * (5.62612870500992e-20 + fConst19))))));
	fConst23 = (4.65295447579145e-24 * fConst6);
	fConst24 = (fConst6 * ((fConst6 * ((fConst6 * (0 - (2.3734396603456e-20 + fConst23))) - 2.32762902199934e-18)) - 1.88310920685509e-17));
	fConst25 = (4.76440117855884e-24 * fConst6);
	fConst26 = (1.88310920685509e-17 + (fConst6 * (2.16097599157672e-17 + (fConst6 * (2.40711435730575e-18 + (fConst6 * (2.43075314241076e-20 + fConst25)))))));
	fConst27 = (1.87753470001854e-18 * fConst6);
	fConst28 = (fConst6 * (1.56079959618259e-14 - fConst27));
	fConst29 = (2.70062186191777e-18 * fConst6);
	fConst30 = (1.56079959618259e-14 + (fConst6 * (fConst29 - 2.24522189930045e-14)));
	fConst31 = (2.79019064029245e-21 * fConst6);
	fConst32 = (fConst6 * (fConst31 - 1.39597416617602e-17));
	fConst33 = (4.01337447559171e-21 * fConst6);
	fConst34 = ((fConst6 * (2.00823037773142e-17 - fConst33)) - 1.39597416617602e-17);
	fConst35 = (2.3166360517034e-21 * fConst6);
	fConst36 = (fConst6 * (1.15904771305196e-17 - fConst35));
	fConst37 = (3.33595591445278e-21 * fConst6);
	fConst38 = (1.15904771305196e-17 + (fConst6 * (fConst37 - 1.66926037039994e-17)));
	fConst39 = (1.5588772005669e-18 * fConst6);
	fConst40 = (fConst6 * (fConst39 - 1.29589876827259e-14));
	fConst41 = (2.24478316881626e-18 * fConst6);
	fConst42 = ((fConst6 * (1.86625011403253e-14 - fConst41)) - 1.29589876827259e-14);
	fConst43 = ((fConst6 * (2.24958749395832e-14 + (fConst6 * ((fConst6 * (7.95599798455062e-20 - fConst7)) - 9.44004344622598e-17)))) - 2.93784119708281e-14);
	fConst44 = (6.98094898928731e-15 + (fConst6 * ((fConst6 * (9.37831383212833e-17 + (fConst6 * (fConst9 - 7.78792746651557e-20)))) - 2.23954390036707e-14)));
	fConst45 = ((fConst6 * (4.00054450346221e-15 + (fConst6 * ((fConst6 * (7.72040670186403e-20 - fConst7)) - 7.37353569889028e-17)))) - 3.92585764869983e-15);
	fConst46 = (fConst6 * ((fConst6 * (7.35486357301907e-17 + (fConst6 * (fConst9 - 7.55784595381368e-20)))) - 3.92585764869983e-15));
	fConst47 = (fConst6 * (2.62717307381705e-15 + (fConst6 * ((fConst6 * (3.42119219586653e-20 - fConst13)) - 3.19454127568418e-17))));
	fConst48 = (2.62717307381705e-15 + (fConst6 * ((fConst6 * (3.20489931550839e-17 + (fConst6 * (fConst15 - 3.49001694087957e-20)))) - 2.65988017960024e-15)));
	fConst49 = (2.17339588935373e-16 + (fConst6 * ((fConst6 * (1.90595008624394e-17 + (fConst6 * (fConst17 - 5.95782688271891e-20)))) - 1.88638248347695e-16)));
	fConst50 = ((fConst6 * (1.66102929456909e-16 + (fConst6 * ((fConst6 * (5.81782503663661e-20 - fConst19)) - 1.85568523263077e-17)))) - 5.00381548719698e-17);
	fConst51 = (2.81398235873666e-17 + (fConst6 * ((fConst6 * (3.80725717138185e-18 + (fConst6 * (fConst17 - 5.76153907610498e-20)))) - 3.24770777204502e-17)));
	fConst52 = (fConst6 * (2.81398235873666e-17 + (fConst6 * ((fConst6 * (5.62612870500992e-20 - fConst19)) - 3.66325429672488e-18))));
	fConst53 = (fConst6 * ((fConst6 * (2.32762902199934e-18 + (fConst6 * (fConst23 - 2.3734396603456e-20)))) - 1.88310920685509e-17));
	fConst54 = ((fConst6 * (2.16097599157672e-17 + (fConst6 * ((fConst6 * (2.43075314241076e-20 - fConst25)) - 2.40711435730575e-18)))) - 1.88310920685509e-17);
	fConst55 = (4.02110307987708e-23 * fConst6);
	fConst56 = ((fConst6 * (2.24958749395832e-14 + (fConst6 * (9.44004344622598e-17 + (fConst6 * (fConst55 - 2.38679939536519e-19)))))) - 8.81352359124845e-14);
	fConst57 = (3.92706159921519e-23 * fConst6);
	fConst58 = (2.09428469678619e-14 + (fConst6 * ((fConst6 * ((fConst6 * (2.33637823995467e-19 - fConst57)) - 9.37831383212833e-17)) - 2.23954390036707e-14)));
	fConst59 = ((fConst6 * (4.00054450346221e-15 + (fConst6 * (7.37353569889028e-17 + (fConst6 * (fConst55 - 2.31612201055921e-19)))))) - 1.17775729460995e-14);
	fConst60 = (fConst6 * ((fConst6 * ((fConst6 * (2.2673537861441e-19 - fConst57)) - 7.35486357301907e-17)) - 3.92585764869983e-15));
	fConst61 = (2.79232991898871e-23 * fConst6);
	fConst62 = (fConst6 * (2.62717307381705e-15 + (fConst6 * (3.19454127568418e-17 + (fConst6 * (fConst61 - 1.02635765875996e-19))))));
	fConst63 = (2.85919794064914e-23 * fConst6);
	fConst64 = (7.88151922145115e-15 + (fConst6 * ((fConst6 * ((fConst6 * (1.04700508226387e-19 - fConst63)) - 3.20489931550839e-17)) - 2.65988017960024e-15)));
	fConst65 = (3.35026616739297e-23 * fConst6);
	fConst66 = (6.5201876680612e-16 + (fConst6 * ((fConst6 * ((fConst6 * (1.78734806481567e-19 - fConst65)) - 1.90595008624394e-17)) - 1.88638248347695e-16)));
	fConst67 = (3.2718982668414e-23 * fConst6);
	fConst68 = ((fConst6 * (1.66102929456909e-16 + (fConst6 * (1.85568523263077e-17 + (fConst6 * (fConst67 - 1.74534751099098e-19)))))) - 1.50114464615909e-16);
	fConst69 = (8.44194707620996e-17 + (fConst6 * ((fConst6 * ((fConst6 * (1.72846172283149e-19 - fConst65)) - 3.80725717138185e-18)) - 3.24770777204502e-17)));
	fConst70 = (fConst6 * (2.81398235873666e-17 + (fConst6 * (3.66325429672488e-18 + (fConst6 * (fConst67 - 1.68783861150298e-19))))));
	fConst71 = (2.32647723789573e-23 * fConst6);
	fConst72 = (fConst6 * ((fConst6 * ((fConst6 * (7.12031898103681e-20 - fConst71)) - 2.32762902199934e-18)) - 1.88310920685509e-17));
	fConst73 = (2.38220058927942e-23 * fConst6);
	fConst74 = ((fConst6 * (2.16097599157672e-17 + (fConst6 * (2.40711435730575e-18 + (fConst6 * (fConst73 - 7.29225942723227e-20)))))) - 5.64932762056526e-17);
	fConst75 = (8.04220615975416e-23 * fConst6);
	fConst76 = ((fConst6 * ((fConst6 * (1.8880086892452e-16 + (fConst6 * (1.59119959691012e-19 - fConst75)))) - 4.49917498791663e-14)) - 5.87568239416563e-14);
	fConst77 = (7.85412319843039e-23 * fConst6);
	fConst78 = (1.39618979785746e-14 + (fConst6 * (4.47908780073414e-14 + (fConst6 * ((fConst6 * (fConst77 - 1.55758549330311e-19)) - 1.87566276642567e-16)))));
	fConst79 = ((fConst6 * ((fConst6 * (1.47470713977806e-16 + (fConst6 * (1.54408134037281e-19 - fConst75)))) - 8.00108900692442e-15)) - 7.85171529739967e-15);
	fConst80 = (fConst6 * (7.85171529739967e-15 + (fConst6 * ((fConst6 * (fConst77 - 1.51156919076274e-19)) - 1.47097271460381e-16))));
	fConst81 = (5.58465983797742e-23 * fConst6);
	fConst82 = (fConst6 * ((fConst6 * (6.38908255136836e-17 + (fConst6 * (6.84238439173305e-20 - fConst81)))) - 5.2543461476341e-15));
	fConst83 = (5.71839588129828e-23 * fConst6);
	fConst84 = (5.2543461476341e-15 + (fConst6 * (5.31976035920048e-15 + (fConst6 * ((fConst6 * (fConst83 - 6.98003388175914e-20)) - 6.40979863101677e-17)))));
	fConst85 = (6.70053233478594e-23 * fConst6);
	fConst86 = (4.34679177870747e-16 + (fConst6 * (3.77276496695391e-16 + (fConst6 * ((fConst6 * (fConst85 - 1.19156537654378e-19)) - 3.81190017248789e-17)))));
	fConst87 = (6.5437965336828e-23 * fConst6);
	fConst88 = ((fConst6 * ((fConst6 * (3.71137046526154e-17 + (fConst6 * (1.16356500732732e-19 - fConst87)))) - 3.32205858913818e-16)) - 1.0007630974394e-16);
	fConst89 = (5.62796471747331e-17 + (fConst6 * (6.49541554409003e-17 + (fConst6 * ((fConst6 * (fConst85 - 1.152307815221e-19)) - 7.61451434276371e-18)))));
	fConst90 = (fConst6 * ((fConst6 * (7.32650859344976e-18 + (fConst6 * (1.12522574100198e-19 - fConst87)))) - 5.62796471747331e-17));
	fConst91 = (4.65295447579145e-23 * fConst6);
	fConst92 = (fConst6 * (3.76621841371018e-17 + (fConst6 * ((fConst6 * (fConst91 - 4.74687932069121e-20)) - 4.65525804399867e-18))));
	fConst93 = (4.76440117855884e-23 * fConst6);
	fConst94 = ((fConst6 * ((fConst6 * (4.81422871461151e-18 + (fConst6 * (4.86150628482152e-20 - fConst93)))) - 4.32195198315344e-17)) - 3.76621841371018e-17);
	fConst95 = (5.87568239416563e-14 + (fConst6 * ((fConst6 * ((fConst6 * (1.59119959691012e-19 + fConst75)) - 1.8880086892452e-16)) - 4.49917498791663e-14)));
	fConst96 = ((fConst6 * (4.47908780073414e-14 + (fConst6 * (1.87566276642567e-16 + (fConst6 * (0 - (1.55758549330311e-19 + fConst77))))))) - 1.39618979785746e-14);
	fConst97 = (7.85171529739967e-15 + (fConst6 * ((fConst6 * ((fConst6 * (1.54408134037281e-19 + fConst75)) - 1.47470713977806e-16)) - 8.00108900692442e-15)));
	fConst98 = (fConst6 * (7.85171529739967e-15 + (fConst6 * (1.47097271460381e-16 + (fConst6 * (0 - (1.51156919076274e-19 + fConst77)))))));
	fConst99 = (fConst6 * ((fConst6 * ((fConst6 * (6.84238439173305e-20 + fConst81)) - 6.38908255136836e-17)) - 5.2543461476341e-15));
	fConst100 = ((fConst6 * (5.31976035920048e-15 + (fConst6 * (6.40979863101677e-17 + (fConst6 * (0 - (6.98003388175914e-20 + fConst83))))))) - 5.2543461476341e-15);
	fConst101 = ((fConst6 * (3.77276496695391e-16 + (fConst6 * (3.81190017248789e-17 + (fConst6 * (0 - (1.19156537654378e-19 + fConst85))))))) - 4.34679177870747e-16);
	fConst102 = (1.0007630974394e-16 + (fConst6 * ((fConst6 * ((fConst6 * (1.16356500732732e-19 + fConst87)) - 3.71137046526154e-17)) - 3.32205858913818e-16)));
	fConst103 = ((fConst6 * (6.49541554409003e-17 + (fConst6 * (7.61451434276371e-18 + (fConst6 * (0 - (1.152307815221e-19 + fConst85))))))) - 5.62796471747331e-17);
	fConst104 = (fConst6 * ((fConst6 * ((fConst6 * (1.12522574100198e-19 + fConst87)) - 7.32650859344976e-18)) - 5.62796471747331e-17));
	fConst105 = (fConst6 * (3.76621841371018e-17 + (fConst6 * (4.65525804399867e-18 + (fConst6 * (0 - (4.74687932069121e-20 + fConst91)))))));
	fConst106 = (3.76621841371018e-17 + (fConst6 * ((fConst6 * ((fConst6 * (4.86150628482152e-20 + fConst93)) - 4.81422871461151e-18)) - 4.32195198315344e-17)));
	fConst107 = (8.81352359124845e-14 + (fConst6 * (2.24958749395832e-14 + (fConst6 * ((fConst6 * (0 - (2.38679939536519e-19 + fConst55))) - 9.44004344622598e-17)))));
	fConst108 = ((fConst6 * ((fConst6 * (9.37831383212833e-17 + (fConst6 * (2.33637823995467e-19 + fConst57)))) - 2.23954390036707e-14)) - 2.09428469678619e-14);
	fConst109 = (1.17775729460995e-14 + (fConst6 * (4.00054450346221e-15 + (fConst6 * ((fConst6 * (0 - (2.31612201055921e-19 + fConst55))) - 7.37353569889028e-17)))));
	fConst110 = (fConst6 * ((fConst6 * (7.35486357301907e-17 + (fConst6 * (2.2673537861441e-19 + fConst57)))) - 3.92585764869983e-15));
	fConst111 = (fConst6 * (2.62717307381705e-15 + (fConst6 * ((fConst6 * (0 - (1.02635765875996e-19 + fConst61))) - 3.19454127568418e-17))));
	fConst112 = ((fConst6 * ((fConst6 * (3.20489931550839e-17 + (fConst6 * (1.04700508226387e-19 + fConst63)))) - 2.65988017960024e-15)) - 7.88151922145115e-15);
	fConst113 = ((fConst6 * ((fConst6 * (1.90595008624394e-17 + (fConst6 * (1.78734806481567e-19 + fConst65)))) - 1.88638248347695e-16)) - 6.5201876680612e-16);
	fConst114 = (1.50114464615909e-16 + (fConst6 * (1.66102929456909e-16 + (fConst6 * ((fConst6 * (0 - (1.74534751099098e-19 + fConst67))) - 1.85568523263077e-17)))));
	fConst115 = ((fConst6 * ((fConst6 * (3.80725717138185e-18 + (fConst6 * (1.72846172283149e-19 + fConst65)))) - 3.24770777204502e-17)) - 8.44194707620996e-17);
	fConst116 = (fConst6 * (2.81398235873666e-17 + (fConst6 * ((fConst6 * (0 - (1.68783861150298e-19 + fConst67))) - 3.66325429672488e-18))));
	fConst117 = (fConst6 * ((fConst6 * (2.32762902199934e-18 + (fConst6 * (7.12031898103681e-20 + fConst71)))) - 1.88310920685509e-17));
	fConst118 = (5.64932762056526e-17 + (fConst6 * (2.16097599157672e-17 + (fConst6 * ((fConst6 * (0 - (7.29225942723227e-20 + fConst73))) - 2.40711435730575e-18)))));
	fConst119 = (5.63260410005562e-18 * fConst6);
	fConst120 = (fConst6 * (fConst119 - 1.56079959618259e-14));
	fConst121 = (8.10186558575332e-18 * fConst6);
	fConst122 = (1.56079959618259e-14 + (fConst6 * (2.24522189930045e-14 - fConst121)));
	fConst123 = (1.39509532014623e-20 * fConst6);
	fConst124 = (fConst6 * (4.18792249852806e-17 - fConst123));
	fConst125 = (2.00668723779585e-20 * fConst6);
	fConst126 = (1.39597416617602e-17 + (fConst6 * (fConst125 - 6.02469113319426e-17)));
	fConst127 = (1.1583180258517e-20 * fConst6);
	fConst128 = (fConst6 * (fConst127 - 3.47714313915589e-17));
	fConst129 = (1.66797795722639e-20 * fConst6);
	fConst130 = ((fConst6 * (5.00778111119983e-17 - fConst129)) - 1.15904771305196e-17);
	fConst131 = (4.67663160170071e-18 * fConst6);
	fConst132 = (fConst6 * (1.29589876827259e-14 - fConst131));
	fConst133 = (6.73434950644879e-18 * fConst6);
	fConst134 = ((fConst6 * (fConst133 - 1.86625011403253e-14)) - 1.29589876827259e-14);
	fConst135 = (3.75506940003708e-18 * fConst6);
	fConst136 = (fConst6 * (0 - (3.12159919236519e-14 + fConst135)));
	fConst137 = (5.40124372383555e-18 * fConst6);
	fConst138 = ((fConst6 * (4.4904437986009e-14 + fConst137)) - 3.12159919236519e-14);
	fConst139 = (2.79019064029245e-20 * fConst6);
	fConst140 = (fConst6 * (fConst139 - 2.79194833235204e-17));
	fConst141 = (4.01337447559171e-20 * fConst6);
	fConst142 = (2.79194833235204e-17 + (fConst6 * (4.01646075546284e-17 - fConst141)));
	fConst143 = (2.3166360517034e-20 * fConst6);
	fConst144 = (fConst6 * (2.31809542610393e-17 - fConst143));
	fConst145 = (3.33595591445278e-20 * fConst6);
	fConst146 = ((fConst6 * (fConst145 - 3.33852074079988e-17)) - 2.31809542610393e-17);
	fConst147 = (3.1177544011338e-18 * fConst6);
	fConst148 = (fConst6 * (2.59179753654518e-14 + fConst147));
	fConst149 = (4.48956633763253e-18 * fConst6);
	fConst150 = (2.59179753654518e-14 + (fConst6 * (0 - (3.73250022806505e-14 + fConst149))));
	fConst151 = (fConst6 * (3.12159919236519e-14 - fConst135));
	fConst152 = ((fConst6 * (fConst137 - 4.4904437986009e-14)) - 3.12159919236519e-14);
	fConst153 = (fConst6 * (0 - (2.79194833235204e-17 + fConst139)));
	fConst154 = ((fConst6 * (4.01646075546284e-17 + fConst141)) - 2.79194833235204e-17);
	fConst155 = (fConst6 * (2.31809542610393e-17 + fConst143));
	fConst156 = (2.31809542610393e-17 + (fConst6 * (0 - (3.33852074079988e-17 + fConst145))));
	fConst157 = (fConst6 * (fConst147 - 2.59179753654518e-14));
	fConst158 = (2.59179753654518e-14 + (fConst6 * (3.73250022806505e-14 - fConst149)));
	fConst159 = (fConst6 * (1.56079959618259e-14 + fConst119));
	fConst160 = (1.56079959618259e-14 + (fConst6 * (0 - (2.24522189930045e-14 + fConst121))));
	fConst161 = (fConst6 * (4.18792249852806e-17 + fConst123));
	fConst162 = ((fConst6 * (0 - (6.02469113319426e-17 + fConst125))) - 1.39597416617602e-17);
	fConst163 = (fConst6 * (0 - (3.47714313915589e-17 + fConst127)));
	fConst164 = (1.15904771305196e-17 + (fConst6 * (5.00778111119983e-17 + fConst129)));
	fConst165 = (fConst6 * (0 - (1.29589876827259e-14 + fConst131)));
	fConst166 = ((fConst6 * (1.86625011403253e-14 + fConst133)) - 1.29589876827259e-14);
	fConst167 = (fConst6 * (0 - (1.56079959618259e-14 + fConst27)));
	fConst168 = (1.56079959618259e-14 + (fConst6 * (2.24522189930045e-14 + fConst29)));
	fConst169 = (fConst6 * (0 - (1.39597416617602e-17 + fConst31)));
	fConst170 = (1.39597416617602e-17 + (fConst6 * (2.00823037773142e-17 + fConst33)));
	fConst171 = (fConst6 * (1.15904771305196e-17 + fConst35));
	fConst172 = ((fConst6 * (0 - (1.66926037039994e-17 + fConst37))) - 1.15904771305196e-17);
	fConst173 = (fConst6 * (1.29589876827259e-14 + fConst39));
	fConst174 = ((fConst6 * (0 - (1.86625011403253e-14 + fConst41))) - 1.29589876827259e-14);
	fConst175 = (1 + fConst3);
	fConst176 = (faustpower<2>(fConst6) / fConst175);
	fConst177 = (0 - ((1 - fConst3) / fConst175));
	fConst178 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst179 = (1 + fConst178);
	fConst180 = (0.027 / fConst179);
	fConst181 = (0 - ((1 - fConst178) / fConst179));
	fConst182 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst183 = (0 - fConst182);
	fConst184 = (1 + fConst182);
	fConst185 = (0.025 / fConst184);
	fConst186 = (0 - ((1 - fConst182) / fConst184));
	fConst187 = (1.0 / fConst175);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlow0 = (0.01 * double(fslider0));
	double 	fSlow1 = (1 - fSlow0);
	double 	fSlow2 = (0.007000000000000006 * double(fslider1));
	double 	fSlow3 = (0.007000000000000006 * double(fslider2));
	double 	fSlow4 = (0.007000000000000006 * double(fslider3));
	double 	fSlow5 = (0.007000000000000006 * double(fslider4));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fRec8[0] = ((0.993 * fRec8[1]) + fSlow2);
		fRec9[0] = ((0.993 * fRec9[1]) + fSlow3);
		fRec10[0] = ((0.993 * fRec10[1]) + fSlow4);
		double fTemp1 = (6.98094898928731e-15 + ((fRec10[0] * ((fConst6 * (((fRec9[0] * (((fRec9[0] * (fConst26 + (fConst24 * fRec8[0]))) + (fConst22 * fRec8[0])) + fConst21)) + (fConst20 * fRec8[0])) + fConst18)) - 5.00381548719698e-17)) + (fConst6 * (((fRec9[0] * (((fRec9[0] * (fConst16 + (fConst14 * fRec8[0]))) + (fConst12 * fRec8[0])) + fConst11)) + (fConst10 * fRec8[0])) + fConst8))));
		fRec11[0] = ((fSlow0 * fTemp0) - ((((((fRec11[1] * (3.49047449464365e-14 + ((fRec10[0] * ((fConst6 * (((fRec9[0] * (((fRec9[0] * (fConst118 + (fConst117 * fRec8[0]))) + (fConst116 * fRec8[0])) + fConst115)) + (fConst114 * fRec8[0])) + fConst113)) - 2.50190774359849e-16)) + (fConst6 * (((fRec9[0] * (((fRec9[0] * (fConst112 + (fConst111 * fRec8[0]))) + (fConst110 * fRec8[0])) + fConst109)) + (fConst108 * fRec8[0])) + fConst107))))) + (fRec11[2] * (6.98094898928731e-14 + ((fRec10[0] * ((fConst6 * (((fRec9[0] * (((fRec9[0] * (fConst106 + (fConst105 * fRec8[0]))) + (fConst104 * fRec8[0])) + fConst103)) + (fConst102 * fRec8[0])) + fConst101)) - 5.00381548719698e-16)) + (fConst6 * (((fRec9[0] * (((fRec9[0] * (fConst100 + (fConst99 * fRec8[0]))) + (fConst98 * fRec8[0])) + fConst97)) + (fConst96 * fRec8[0])) + fConst95)))))) + (fRec11[3] * (6.98094898928731e-14 + ((fRec10[0] * ((fConst6 * (((fRec9[0] * (((fRec9[0] * (fConst94 + (fConst92 * fRec8[0]))) + (fConst90 * fRec8[0])) + fConst89)) + (fConst88 * fRec8[0])) + fConst86)) - 5.00381548719698e-16)) + (fConst6 * (((fRec9[0] * (((fRec9[0] * (fConst84 + (fConst82 * fRec8[0]))) + (fConst80 * fRec8[0])) + fConst79)) + (fConst78 * fRec8[0])) + fConst76)))))) + (fRec11[4] * (3.49047449464365e-14 + ((fRec10[0] * ((fConst6 * (((fRec9[0] * (((fRec9[0] * (fConst74 + (fConst72 * fRec8[0]))) + (fConst70 * fRec8[0])) + fConst69)) + (fConst68 * fRec8[0])) + fConst66)) - 2.50190774359849e-16)) + (fConst6 * (((fRec9[0] * (((fRec9[0] * (fConst64 + (fConst62 * fRec8[0]))) + (fConst60 * fRec8[0])) + fConst59)) + (fConst58 * fRec8[0])) + fConst56)))))) + (fRec11[5] * (6.98094898928731e-15 + ((fRec10[0] * ((fConst6 * (((fRec9[0] * (((fRec9[0] * (fConst54 + (fConst53 * fRec8[0]))) + (fConst52 * fRec8[0])) + fConst51)) + (fConst50 * fRec8[0])) + fConst49)) - 5.00381548719698e-17)) + (fConst6 * (((fRec9[0] * (((fRec9[0] * (fConst48 + (fConst47 * fRec8[0]))) + (fConst46 * fRec8[0])) + fConst45)) + (fConst44 * fRec8[0])) + fConst43)))))) / fTemp1));
		fRec12[0] = ((0.993 * fRec12[1]) + fSlow5);
		double fTemp2 = ((fRec12[0] * ((((((fRec11[0] * (((fRec10[0] * ((fConst174 + (fConst173 * fRec8[0])) + (fConst6 * (fRec9[0] * (fConst172 + (fConst171 * fRec8[0])))))) + (fConst6 * (fRec9[0] * (fConst170 + (fConst169 * fRec8[0]))))) + (fConst168 + (fConst167 * fRec8[0])))) + (fRec11[1] * (((fRec10[0] * ((fConst166 + (fConst165 * fRec8[0])) + (fConst6 * (fRec9[0] * (fConst164 + (fConst163 * fRec8[0])))))) + (fConst6 * (fRec9[0] * (fConst162 + (fConst161 * fRec8[0]))))) + (fConst160 + (fConst159 * fRec8[0]))))) + (fRec11[2] * (((fRec10[0] * ((fConst158 + (fConst157 * fRec8[0])) + (fConst6 * (fRec9[0] * (fConst156 + (fConst155 * fRec8[0])))))) + (fConst6 * (fRec9[0] * (fConst154 + (fConst153 * fRec8[0]))))) + (fConst152 + (fConst151 * fRec8[0]))))) + (fRec11[3] * (((fRec10[0] * ((fConst150 + (fConst148 * fRec8[0])) + (fConst6 * (fRec9[0] * (fConst146 + (fConst144 * fRec8[0])))))) + (fConst6 * (fRec9[0] * (fConst142 + (fConst140 * fRec8[0]))))) + (fConst138 + (fConst136 * fRec8[0]))))) + (fRec11[4] * (((fRec10[0] * ((fConst134 + (fConst132 * fRec8[0])) + (fConst6 * (fRec9[0] * (fConst130 + (fConst128 * fRec8[0])))))) + (fConst6 * (fRec9[0] * (fConst126 + (fConst124 * fRec8[0]))))) + (fConst122 + (fConst120 * fRec8[0]))))) + (fRec11[5] * (((fRec10[0] * ((fConst42 + (fConst40 * fRec8[0])) + (fConst6 * (fRec9[0] * (fConst38 + (fConst36 * fRec8[0])))))) + (fConst6 * (fRec9[0] * (fConst34 + (fConst32 * fRec8[0]))))) + (fConst30 + (fConst28 * fRec8[0])))))) / fTemp1);
		fVec0[0] = fTemp2;
		fRec7[0] = ((fConst177 * fRec7[1]) + (fConst176 * (fVec0[0] + fVec0[1])));
		fRec6[0] = (fRec7[0] - (fConst5 * ((fConst4 * fRec6[2]) + (fConst2 * fRec6[1]))));
		fRec13[0] = ((fConst181 * fRec13[1]) + (fConst180 * (fRec5[1] + fRec5[2])));
		fRec5[0] = (Ftrany(TRANY_TABLE_SVEL34_250k, ((fRec13[0] + (fConst5 * (fRec6[2] + (fRec6[0] + (2 * fRec6[1]))))) - 3.571981)) - 117.70440740740739);
		fRec4[0] = ((fConst186 * fRec4[1]) + (fConst185 * ((fConst182 * fRec5[0]) + (fConst183 * fRec5[1]))));
		fRec3[0] = ((fConst177 * fRec3[1]) + (fConst187 * (fRec4[0] + fRec4[1])));
		fRec2[0] = (fRec3[0] - (fConst5 * ((fConst4 * fRec2[2]) + (fConst2 * fRec2[1]))));
		fRec14[0] = ((fConst181 * fRec14[1]) + (fConst180 * (fRec1[1] + fRec1[2])));
		fRec1[0] = (Ftrany(TRANY_TABLE_KT88_68k, ((fRec14[0] + (fConst5 * (fRec2[2] + (fRec2[0] + (2 * fRec2[1]))))) - 5.562895)) - 43.96685185185183);
		fRec0[0] = ((fConst186 * fRec0[1]) + (fConst185 * ((fConst182 * fRec1[0]) + (fConst183 * fRec1[1]))));
		output0[i] = (FAUSTFLOAT)(fRec0[0] + (fSlow1 * fTemp0));
		// post processing
		fRec0[1] = fRec0[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec14[1] = fRec14[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec13[1] = fRec13[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec7[1] = fRec7[0];
		fVec0[1] = fVec0[0];
		fRec12[1] = fRec12[0];
		for (int i=5; i>0; i--) fRec11[i] = fRec11[i-1];
		fRec10[1] = fRec10[0];
		fRec9[1] = fRec9[0];
		fRec8[1] = fRec8[0];
	}

}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("ffreak.Fuzz",N_("Fuzz"),"S","",&fslider1, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("ffreak.Gate",N_("Gate"),"S","",&fslider3, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("ffreak.Level",N_("Level"),"S","",&fslider4, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("ffreak.Tone",N_("Tone"),"S","",&fslider2, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("ffreak.wet_dry",N_("wet/dry"),"S",N_("percentage of processed signal in output signal"),&fslider0, 1e+02, 0.0, 1e+02, 1.0);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
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
