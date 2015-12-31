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
	FAUSTFLOAT 	fslider1;
	double 	fRec12[2];
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	double 	fConst9;
	double 	fConst10;
	double 	fConst11;
	FAUSTFLOAT 	fslider2;
	double 	fRec13[2];
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
	FAUSTFLOAT 	fslider3;
	double 	fRec14[2];
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
	double 	fConst113;
	double 	fRec15[6];
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
	FAUSTFLOAT 	fslider4;
	double 	fRec16[2];
	double 	fVec0[2];
	double 	fConst170;
	double 	fRec11[2];
	double 	fRec10[3];
	double 	fConst171;
	double 	fConst172;
	double 	fConst173;
	double 	fConst174;
	double 	fRec17[2];
	double 	fRec9[3];
	double 	fConst175;
	double 	fConst176;
	double 	fConst177;
	double 	fConst178;
	double 	fConst179;
	double 	fRec8[2];
	double 	fRec7[2];
	double 	fRec6[3];
	double 	fRec18[2];
	double 	fRec5[3];
	double 	fRec4[2];
	double 	fRec3[2];
	double 	fRec2[3];
	double 	fRec19[2];
	double 	fRec1[3];
	double 	fRec0[2];
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
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<6; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<3; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<3; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
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
	fConst1 = double(iConst0);
	fConst2 = (8.04220615975416e-24 * fConst1);
	fConst3 = (2.93784119708281e-14 + (fConst1 * (2.24958749395832e-14 + (fConst1 * (9.44004344622598e-17 + (fConst1 * (7.95599798455062e-20 + fConst2)))))));
	fConst4 = (7.85412319843039e-24 * fConst1);
	fConst5 = ((fConst1 * ((fConst1 * ((fConst1 * (0 - (7.78792746651557e-20 + fConst4))) - 9.37831383212833e-17)) - 2.23954390036707e-14)) - 6.98094898928731e-15);
	fConst6 = (3.92585764869983e-15 + (fConst1 * (4.00054450346221e-15 + (fConst1 * (7.37353569889028e-17 + (fConst1 * (7.72040670186403e-20 + fConst2)))))));
	fConst7 = (fConst1 * ((fConst1 * ((fConst1 * (0 - (7.55784595381368e-20 + fConst4))) - 7.35486357301907e-17)) - 3.92585764869983e-15));
	fConst8 = (5.58465983797742e-24 * fConst1);
	fConst9 = (fConst1 * (2.62717307381705e-15 + (fConst1 * (3.19454127568418e-17 + (fConst1 * (3.42119219586653e-20 + fConst8))))));
	fConst10 = (5.71839588129828e-24 * fConst1);
	fConst11 = ((fConst1 * ((fConst1 * ((fConst1 * (0 - (3.49001694087957e-20 + fConst10))) - 3.20489931550839e-17)) - 2.65988017960024e-15)) - 2.62717307381705e-15);
	fConst12 = (6.70053233478594e-24 * fConst1);
	fConst13 = ((fConst1 * ((fConst1 * ((fConst1 * (0 - (5.95782688271891e-20 + fConst12))) - 1.90595008624394e-17)) - 1.88638248347695e-16)) - 2.17339588935373e-16);
	fConst14 = (6.5437965336828e-24 * fConst1);
	fConst15 = (5.00381548719698e-17 + (fConst1 * (1.66102929456909e-16 + (fConst1 * (1.85568523263077e-17 + (fConst1 * (5.81782503663661e-20 + fConst14)))))));
	fConst16 = ((fConst1 * ((fConst1 * ((fConst1 * (0 - (5.76153907610498e-20 + fConst12))) - 3.80725717138185e-18)) - 3.24770777204502e-17)) - 2.81398235873666e-17);
	fConst17 = (fConst1 * (2.81398235873666e-17 + (fConst1 * (3.66325429672488e-18 + (fConst1 * (5.62612870500992e-20 + fConst14))))));
	fConst18 = (4.65295447579145e-24 * fConst1);
	fConst19 = (fConst1 * ((fConst1 * ((fConst1 * (0 - (2.3734396603456e-20 + fConst18))) - 2.32762902199934e-18)) - 1.88310920685509e-17));
	fConst20 = (4.76440117855884e-24 * fConst1);
	fConst21 = (1.88310920685509e-17 + (fConst1 * (2.16097599157672e-17 + (fConst1 * (2.40711435730575e-18 + (fConst1 * (2.43075314241076e-20 + fConst20)))))));
	fConst22 = (1.87753470001854e-18 * fConst1);
	fConst23 = (fConst1 * (1.56079959618259e-14 - fConst22));
	fConst24 = (2.70062186191777e-18 * fConst1);
	fConst25 = (1.56079959618259e-14 + (fConst1 * (fConst24 - 2.24522189930045e-14)));
	fConst26 = (2.79019064029245e-21 * fConst1);
	fConst27 = (fConst1 * (fConst26 - 1.39597416617602e-17));
	fConst28 = (4.01337447559171e-21 * fConst1);
	fConst29 = ((fConst1 * (2.00823037773142e-17 - fConst28)) - 1.39597416617602e-17);
	fConst30 = (2.3166360517034e-21 * fConst1);
	fConst31 = (fConst1 * (1.15904771305196e-17 - fConst30));
	fConst32 = (3.33595591445278e-21 * fConst1);
	fConst33 = (1.15904771305196e-17 + (fConst1 * (fConst32 - 1.66926037039994e-17)));
	fConst34 = (1.5588772005669e-18 * fConst1);
	fConst35 = (fConst1 * (fConst34 - 1.29589876827259e-14));
	fConst36 = (2.24478316881626e-18 * fConst1);
	fConst37 = ((fConst1 * (1.86625011403253e-14 - fConst36)) - 1.29589876827259e-14);
	fConst38 = ((fConst1 * (2.24958749395832e-14 + (fConst1 * ((fConst1 * (7.95599798455062e-20 - fConst2)) - 9.44004344622598e-17)))) - 2.93784119708281e-14);
	fConst39 = (6.98094898928731e-15 + (fConst1 * ((fConst1 * (9.37831383212833e-17 + (fConst1 * (fConst4 - 7.78792746651557e-20)))) - 2.23954390036707e-14)));
	fConst40 = ((fConst1 * (4.00054450346221e-15 + (fConst1 * ((fConst1 * (7.72040670186403e-20 - fConst2)) - 7.37353569889028e-17)))) - 3.92585764869983e-15);
	fConst41 = (fConst1 * ((fConst1 * (7.35486357301907e-17 + (fConst1 * (fConst4 - 7.55784595381368e-20)))) - 3.92585764869983e-15));
	fConst42 = (fConst1 * (2.62717307381705e-15 + (fConst1 * ((fConst1 * (3.42119219586653e-20 - fConst8)) - 3.19454127568418e-17))));
	fConst43 = (2.62717307381705e-15 + (fConst1 * ((fConst1 * (3.20489931550839e-17 + (fConst1 * (fConst10 - 3.49001694087957e-20)))) - 2.65988017960024e-15)));
	fConst44 = (2.17339588935373e-16 + (fConst1 * ((fConst1 * (1.90595008624394e-17 + (fConst1 * (fConst12 - 5.95782688271891e-20)))) - 1.88638248347695e-16)));
	fConst45 = ((fConst1 * (1.66102929456909e-16 + (fConst1 * ((fConst1 * (5.81782503663661e-20 - fConst14)) - 1.85568523263077e-17)))) - 5.00381548719698e-17);
	fConst46 = (2.81398235873666e-17 + (fConst1 * ((fConst1 * (3.80725717138185e-18 + (fConst1 * (fConst12 - 5.76153907610498e-20)))) - 3.24770777204502e-17)));
	fConst47 = (fConst1 * (2.81398235873666e-17 + (fConst1 * ((fConst1 * (5.62612870500992e-20 - fConst14)) - 3.66325429672488e-18))));
	fConst48 = (fConst1 * ((fConst1 * (2.32762902199934e-18 + (fConst1 * (fConst18 - 2.3734396603456e-20)))) - 1.88310920685509e-17));
	fConst49 = ((fConst1 * (2.16097599157672e-17 + (fConst1 * ((fConst1 * (2.43075314241076e-20 - fConst20)) - 2.40711435730575e-18)))) - 1.88310920685509e-17);
	fConst50 = (4.02110307987708e-23 * fConst1);
	fConst51 = ((fConst1 * (2.24958749395832e-14 + (fConst1 * (9.44004344622598e-17 + (fConst1 * (fConst50 - 2.38679939536519e-19)))))) - 8.81352359124845e-14);
	fConst52 = (3.92706159921519e-23 * fConst1);
	fConst53 = (2.09428469678619e-14 + (fConst1 * ((fConst1 * ((fConst1 * (2.33637823995467e-19 - fConst52)) - 9.37831383212833e-17)) - 2.23954390036707e-14)));
	fConst54 = ((fConst1 * (4.00054450346221e-15 + (fConst1 * (7.37353569889028e-17 + (fConst1 * (fConst50 - 2.31612201055921e-19)))))) - 1.17775729460995e-14);
	fConst55 = (fConst1 * ((fConst1 * ((fConst1 * (2.2673537861441e-19 - fConst52)) - 7.35486357301907e-17)) - 3.92585764869983e-15));
	fConst56 = (2.79232991898871e-23 * fConst1);
	fConst57 = (fConst1 * (2.62717307381705e-15 + (fConst1 * (3.19454127568418e-17 + (fConst1 * (fConst56 - 1.02635765875996e-19))))));
	fConst58 = (2.85919794064914e-23 * fConst1);
	fConst59 = (7.88151922145115e-15 + (fConst1 * ((fConst1 * ((fConst1 * (1.04700508226387e-19 - fConst58)) - 3.20489931550839e-17)) - 2.65988017960024e-15)));
	fConst60 = (3.35026616739297e-23 * fConst1);
	fConst61 = (6.5201876680612e-16 + (fConst1 * ((fConst1 * ((fConst1 * (1.78734806481567e-19 - fConst60)) - 1.90595008624394e-17)) - 1.88638248347695e-16)));
	fConst62 = (3.2718982668414e-23 * fConst1);
	fConst63 = ((fConst1 * (1.66102929456909e-16 + (fConst1 * (1.85568523263077e-17 + (fConst1 * (fConst62 - 1.74534751099098e-19)))))) - 1.50114464615909e-16);
	fConst64 = (8.44194707620996e-17 + (fConst1 * ((fConst1 * ((fConst1 * (1.72846172283149e-19 - fConst60)) - 3.80725717138185e-18)) - 3.24770777204502e-17)));
	fConst65 = (fConst1 * (2.81398235873666e-17 + (fConst1 * (3.66325429672488e-18 + (fConst1 * (fConst62 - 1.68783861150298e-19))))));
	fConst66 = (2.32647723789573e-23 * fConst1);
	fConst67 = (fConst1 * ((fConst1 * ((fConst1 * (7.12031898103681e-20 - fConst66)) - 2.32762902199934e-18)) - 1.88310920685509e-17));
	fConst68 = (2.38220058927942e-23 * fConst1);
	fConst69 = ((fConst1 * (2.16097599157672e-17 + (fConst1 * (2.40711435730575e-18 + (fConst1 * (fConst68 - 7.29225942723227e-20)))))) - 5.64932762056526e-17);
	fConst70 = (8.04220615975416e-23 * fConst1);
	fConst71 = ((fConst1 * ((fConst1 * (1.8880086892452e-16 + (fConst1 * (1.59119959691012e-19 - fConst70)))) - 4.49917498791663e-14)) - 5.87568239416563e-14);
	fConst72 = (7.85412319843039e-23 * fConst1);
	fConst73 = (1.39618979785746e-14 + (fConst1 * (4.47908780073414e-14 + (fConst1 * ((fConst1 * (fConst72 - 1.55758549330311e-19)) - 1.87566276642567e-16)))));
	fConst74 = ((fConst1 * ((fConst1 * (1.47470713977806e-16 + (fConst1 * (1.54408134037281e-19 - fConst70)))) - 8.00108900692442e-15)) - 7.85171529739967e-15);
	fConst75 = (fConst1 * (7.85171529739967e-15 + (fConst1 * ((fConst1 * (fConst72 - 1.51156919076274e-19)) - 1.47097271460381e-16))));
	fConst76 = (5.58465983797742e-23 * fConst1);
	fConst77 = (fConst1 * ((fConst1 * (6.38908255136836e-17 + (fConst1 * (6.84238439173305e-20 - fConst76)))) - 5.2543461476341e-15));
	fConst78 = (5.71839588129828e-23 * fConst1);
	fConst79 = (5.2543461476341e-15 + (fConst1 * (5.31976035920048e-15 + (fConst1 * ((fConst1 * (fConst78 - 6.98003388175914e-20)) - 6.40979863101677e-17)))));
	fConst80 = (6.70053233478594e-23 * fConst1);
	fConst81 = (4.34679177870747e-16 + (fConst1 * (3.77276496695391e-16 + (fConst1 * ((fConst1 * (fConst80 - 1.19156537654378e-19)) - 3.81190017248789e-17)))));
	fConst82 = (6.5437965336828e-23 * fConst1);
	fConst83 = ((fConst1 * ((fConst1 * (3.71137046526154e-17 + (fConst1 * (1.16356500732732e-19 - fConst82)))) - 3.32205858913818e-16)) - 1.0007630974394e-16);
	fConst84 = (5.62796471747331e-17 + (fConst1 * (6.49541554409003e-17 + (fConst1 * ((fConst1 * (fConst80 - 1.152307815221e-19)) - 7.61451434276371e-18)))));
	fConst85 = (fConst1 * ((fConst1 * (7.32650859344976e-18 + (fConst1 * (1.12522574100198e-19 - fConst82)))) - 5.62796471747331e-17));
	fConst86 = (4.65295447579145e-23 * fConst1);
	fConst87 = (fConst1 * (3.76621841371018e-17 + (fConst1 * ((fConst1 * (fConst86 - 4.74687932069121e-20)) - 4.65525804399867e-18))));
	fConst88 = (4.76440117855884e-23 * fConst1);
	fConst89 = ((fConst1 * ((fConst1 * (4.81422871461151e-18 + (fConst1 * (4.86150628482152e-20 - fConst88)))) - 4.32195198315344e-17)) - 3.76621841371018e-17);
	fConst90 = (5.87568239416563e-14 + (fConst1 * ((fConst1 * ((fConst1 * (1.59119959691012e-19 + fConst70)) - 1.8880086892452e-16)) - 4.49917498791663e-14)));
	fConst91 = ((fConst1 * (4.47908780073414e-14 + (fConst1 * (1.87566276642567e-16 + (fConst1 * (0 - (1.55758549330311e-19 + fConst72))))))) - 1.39618979785746e-14);
	fConst92 = (7.85171529739967e-15 + (fConst1 * ((fConst1 * ((fConst1 * (1.54408134037281e-19 + fConst70)) - 1.47470713977806e-16)) - 8.00108900692442e-15)));
	fConst93 = (fConst1 * (7.85171529739967e-15 + (fConst1 * (1.47097271460381e-16 + (fConst1 * (0 - (1.51156919076274e-19 + fConst72)))))));
	fConst94 = (fConst1 * ((fConst1 * ((fConst1 * (6.84238439173305e-20 + fConst76)) - 6.38908255136836e-17)) - 5.2543461476341e-15));
	fConst95 = ((fConst1 * (5.31976035920048e-15 + (fConst1 * (6.40979863101677e-17 + (fConst1 * (0 - (6.98003388175914e-20 + fConst78))))))) - 5.2543461476341e-15);
	fConst96 = ((fConst1 * (3.77276496695391e-16 + (fConst1 * (3.81190017248789e-17 + (fConst1 * (0 - (1.19156537654378e-19 + fConst80))))))) - 4.34679177870747e-16);
	fConst97 = (1.0007630974394e-16 + (fConst1 * ((fConst1 * ((fConst1 * (1.16356500732732e-19 + fConst82)) - 3.71137046526154e-17)) - 3.32205858913818e-16)));
	fConst98 = ((fConst1 * (6.49541554409003e-17 + (fConst1 * (7.61451434276371e-18 + (fConst1 * (0 - (1.152307815221e-19 + fConst80))))))) - 5.62796471747331e-17);
	fConst99 = (fConst1 * ((fConst1 * ((fConst1 * (1.12522574100198e-19 + fConst82)) - 7.32650859344976e-18)) - 5.62796471747331e-17));
	fConst100 = (fConst1 * (3.76621841371018e-17 + (fConst1 * (4.65525804399867e-18 + (fConst1 * (0 - (4.74687932069121e-20 + fConst86)))))));
	fConst101 = (3.76621841371018e-17 + (fConst1 * ((fConst1 * ((fConst1 * (4.86150628482152e-20 + fConst88)) - 4.81422871461151e-18)) - 4.32195198315344e-17)));
	fConst102 = (8.81352359124845e-14 + (fConst1 * (2.24958749395832e-14 + (fConst1 * ((fConst1 * (0 - (2.38679939536519e-19 + fConst50))) - 9.44004344622598e-17)))));
	fConst103 = ((fConst1 * ((fConst1 * (9.37831383212833e-17 + (fConst1 * (2.33637823995467e-19 + fConst52)))) - 2.23954390036707e-14)) - 2.09428469678619e-14);
	fConst104 = (1.17775729460995e-14 + (fConst1 * (4.00054450346221e-15 + (fConst1 * ((fConst1 * (0 - (2.31612201055921e-19 + fConst50))) - 7.37353569889028e-17)))));
	fConst105 = (fConst1 * ((fConst1 * (7.35486357301907e-17 + (fConst1 * (2.2673537861441e-19 + fConst52)))) - 3.92585764869983e-15));
	fConst106 = (fConst1 * (2.62717307381705e-15 + (fConst1 * ((fConst1 * (0 - (1.02635765875996e-19 + fConst56))) - 3.19454127568418e-17))));
	fConst107 = ((fConst1 * ((fConst1 * (3.20489931550839e-17 + (fConst1 * (1.04700508226387e-19 + fConst58)))) - 2.65988017960024e-15)) - 7.88151922145115e-15);
	fConst108 = ((fConst1 * ((fConst1 * (1.90595008624394e-17 + (fConst1 * (1.78734806481567e-19 + fConst60)))) - 1.88638248347695e-16)) - 6.5201876680612e-16);
	fConst109 = (1.50114464615909e-16 + (fConst1 * (1.66102929456909e-16 + (fConst1 * ((fConst1 * (0 - (1.74534751099098e-19 + fConst62))) - 1.85568523263077e-17)))));
	fConst110 = ((fConst1 * ((fConst1 * (3.80725717138185e-18 + (fConst1 * (1.72846172283149e-19 + fConst60)))) - 3.24770777204502e-17)) - 8.44194707620996e-17);
	fConst111 = (fConst1 * (2.81398235873666e-17 + (fConst1 * ((fConst1 * (0 - (1.68783861150298e-19 + fConst62))) - 3.66325429672488e-18))));
	fConst112 = (fConst1 * ((fConst1 * (2.32762902199934e-18 + (fConst1 * (7.12031898103681e-20 + fConst66)))) - 1.88310920685509e-17));
	fConst113 = (5.64932762056526e-17 + (fConst1 * (2.16097599157672e-17 + (fConst1 * ((fConst1 * (0 - (7.29225942723227e-20 + fConst68))) - 2.40711435730575e-18)))));
	fConst114 = (5.63260410005562e-18 * fConst1);
	fConst115 = (fConst1 * (fConst114 - 1.56079959618259e-14));
	fConst116 = (8.10186558575332e-18 * fConst1);
	fConst117 = (1.56079959618259e-14 + (fConst1 * (2.24522189930045e-14 - fConst116)));
	fConst118 = (1.39509532014623e-20 * fConst1);
	fConst119 = (fConst1 * (4.18792249852806e-17 - fConst118));
	fConst120 = (2.00668723779585e-20 * fConst1);
	fConst121 = (1.39597416617602e-17 + (fConst1 * (fConst120 - 6.02469113319426e-17)));
	fConst122 = (1.1583180258517e-20 * fConst1);
	fConst123 = (fConst1 * (fConst122 - 3.47714313915589e-17));
	fConst124 = (1.66797795722639e-20 * fConst1);
	fConst125 = ((fConst1 * (5.00778111119983e-17 - fConst124)) - 1.15904771305196e-17);
	fConst126 = (4.67663160170071e-18 * fConst1);
	fConst127 = (fConst1 * (1.29589876827259e-14 - fConst126));
	fConst128 = (6.73434950644879e-18 * fConst1);
	fConst129 = ((fConst1 * (fConst128 - 1.86625011403253e-14)) - 1.29589876827259e-14);
	fConst130 = (3.75506940003708e-18 * fConst1);
	fConst131 = (fConst1 * (0 - (3.12159919236519e-14 + fConst130)));
	fConst132 = (5.40124372383555e-18 * fConst1);
	fConst133 = ((fConst1 * (4.4904437986009e-14 + fConst132)) - 3.12159919236519e-14);
	fConst134 = (2.79019064029245e-20 * fConst1);
	fConst135 = (fConst1 * (fConst134 - 2.79194833235204e-17));
	fConst136 = (4.01337447559171e-20 * fConst1);
	fConst137 = (2.79194833235204e-17 + (fConst1 * (4.01646075546284e-17 - fConst136)));
	fConst138 = (2.3166360517034e-20 * fConst1);
	fConst139 = (fConst1 * (2.31809542610393e-17 - fConst138));
	fConst140 = (3.33595591445278e-20 * fConst1);
	fConst141 = ((fConst1 * (fConst140 - 3.33852074079988e-17)) - 2.31809542610393e-17);
	fConst142 = (3.1177544011338e-18 * fConst1);
	fConst143 = (fConst1 * (2.59179753654518e-14 + fConst142));
	fConst144 = (4.48956633763253e-18 * fConst1);
	fConst145 = (2.59179753654518e-14 + (fConst1 * (0 - (3.73250022806505e-14 + fConst144))));
	fConst146 = (fConst1 * (3.12159919236519e-14 - fConst130));
	fConst147 = ((fConst1 * (fConst132 - 4.4904437986009e-14)) - 3.12159919236519e-14);
	fConst148 = (fConst1 * (0 - (2.79194833235204e-17 + fConst134)));
	fConst149 = ((fConst1 * (4.01646075546284e-17 + fConst136)) - 2.79194833235204e-17);
	fConst150 = (fConst1 * (2.31809542610393e-17 + fConst138));
	fConst151 = (2.31809542610393e-17 + (fConst1 * (0 - (3.33852074079988e-17 + fConst140))));
	fConst152 = (fConst1 * (fConst142 - 2.59179753654518e-14));
	fConst153 = (2.59179753654518e-14 + (fConst1 * (3.73250022806505e-14 - fConst144)));
	fConst154 = (fConst1 * (1.56079959618259e-14 + fConst114));
	fConst155 = (1.56079959618259e-14 + (fConst1 * (0 - (2.24522189930045e-14 + fConst116))));
	fConst156 = (fConst1 * (4.18792249852806e-17 + fConst118));
	fConst157 = ((fConst1 * (0 - (6.02469113319426e-17 + fConst120))) - 1.39597416617602e-17);
	fConst158 = (fConst1 * (0 - (3.47714313915589e-17 + fConst122)));
	fConst159 = (1.15904771305196e-17 + (fConst1 * (5.00778111119983e-17 + fConst124)));
	fConst160 = (fConst1 * (0 - (1.29589876827259e-14 + fConst126)));
	fConst161 = ((fConst1 * (1.86625011403253e-14 + fConst128)) - 1.29589876827259e-14);
	fConst162 = (fConst1 * (0 - (1.56079959618259e-14 + fConst22)));
	fConst163 = (1.56079959618259e-14 + (fConst1 * (2.24522189930045e-14 + fConst24)));
	fConst164 = (fConst1 * (0 - (1.39597416617602e-17 + fConst26)));
	fConst165 = (1.39597416617602e-17 + (fConst1 * (2.00823037773142e-17 + fConst28)));
	fConst166 = (fConst1 * (1.15904771305196e-17 + fConst30));
	fConst167 = ((fConst1 * (0 - (1.66926037039994e-17 + fConst32))) - 1.15904771305196e-17);
	fConst168 = (fConst1 * (1.29589876827259e-14 + fConst34));
	fConst169 = ((fConst1 * (0 - (1.86625011403253e-14 + fConst36))) - 1.29589876827259e-14);
	fConst170 = (0.9302847925323914 * faustpower<2>(fConst1));
	fConst171 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst172 = (1 + fConst171);
	fConst173 = (0.027 / fConst172);
	fConst174 = (0 - ((1 - fConst171) / fConst172));
	fConst175 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst176 = (0 - fConst175);
	fConst177 = (1 + fConst175);
	fConst178 = (0.025 / fConst177);
	fConst179 = (0 - ((1 - fConst175) / fConst177));
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
		fRec12[0] = ((0.993 * fRec12[1]) + fSlow2);
		fRec13[0] = ((0.993 * fRec13[1]) + fSlow3);
		fRec14[0] = ((0.993 * fRec14[1]) + fSlow4);
		double fTemp1 = (6.98094898928731e-15 + ((fRec14[0] * ((fConst1 * (((fRec13[0] * (((fRec13[0] * (fConst21 + (fConst19 * fRec12[0]))) + (fConst17 * fRec12[0])) + fConst16)) + (fConst15 * fRec12[0])) + fConst13)) - 5.00381548719698e-17)) + (fConst1 * (((fRec13[0] * (((fRec13[0] * (fConst11 + (fConst9 * fRec12[0]))) + (fConst7 * fRec12[0])) + fConst6)) + (fConst5 * fRec12[0])) + fConst3))));
		fRec15[0] = ((fSlow0 * fTemp0) - ((((((fRec15[1] * (3.49047449464365e-14 + ((fRec14[0] * ((fConst1 * (((fRec13[0] * (((fRec13[0] * (fConst113 + (fConst112 * fRec12[0]))) + (fConst111 * fRec12[0])) + fConst110)) + (fConst109 * fRec12[0])) + fConst108)) - 2.50190774359849e-16)) + (fConst1 * (((fRec13[0] * (((fRec13[0] * (fConst107 + (fConst106 * fRec12[0]))) + (fConst105 * fRec12[0])) + fConst104)) + (fConst103 * fRec12[0])) + fConst102))))) + (fRec15[2] * (6.98094898928731e-14 + ((fRec14[0] * ((fConst1 * (((fRec13[0] * (((fRec13[0] * (fConst101 + (fConst100 * fRec12[0]))) + (fConst99 * fRec12[0])) + fConst98)) + (fConst97 * fRec12[0])) + fConst96)) - 5.00381548719698e-16)) + (fConst1 * (((fRec13[0] * (((fRec13[0] * (fConst95 + (fConst94 * fRec12[0]))) + (fConst93 * fRec12[0])) + fConst92)) + (fConst91 * fRec12[0])) + fConst90)))))) + (fRec15[3] * (6.98094898928731e-14 + ((fRec14[0] * ((fConst1 * (((fRec13[0] * (((fRec13[0] * (fConst89 + (fConst87 * fRec12[0]))) + (fConst85 * fRec12[0])) + fConst84)) + (fConst83 * fRec12[0])) + fConst81)) - 5.00381548719698e-16)) + (fConst1 * (((fRec13[0] * (((fRec13[0] * (fConst79 + (fConst77 * fRec12[0]))) + (fConst75 * fRec12[0])) + fConst74)) + (fConst73 * fRec12[0])) + fConst71)))))) + (fRec15[4] * (3.49047449464365e-14 + ((fRec14[0] * ((fConst1 * (((fRec13[0] * (((fRec13[0] * (fConst69 + (fConst67 * fRec12[0]))) + (fConst65 * fRec12[0])) + fConst64)) + (fConst63 * fRec12[0])) + fConst61)) - 2.50190774359849e-16)) + (fConst1 * (((fRec13[0] * (((fRec13[0] * (fConst59 + (fConst57 * fRec12[0]))) + (fConst55 * fRec12[0])) + fConst54)) + (fConst53 * fRec12[0])) + fConst51)))))) + (fRec15[5] * (6.98094898928731e-15 + ((fRec14[0] * ((fConst1 * (((fRec13[0] * (((fRec13[0] * (fConst49 + (fConst48 * fRec12[0]))) + (fConst47 * fRec12[0])) + fConst46)) + (fConst45 * fRec12[0])) + fConst44)) - 5.00381548719698e-17)) + (fConst1 * (((fRec13[0] * (((fRec13[0] * (fConst43 + (fConst42 * fRec12[0]))) + (fConst41 * fRec12[0])) + fConst40)) + (fConst39 * fRec12[0])) + fConst38)))))) / fTemp1));
		fRec16[0] = ((0.993 * fRec16[1]) + fSlow5);
		double fTemp2 = ((fRec16[0] * ((((((fRec15[0] * (((fRec14[0] * ((fConst169 + (fConst168 * fRec12[0])) + (fConst1 * (fRec13[0] * (fConst167 + (fConst166 * fRec12[0])))))) + (fConst1 * (fRec13[0] * (fConst165 + (fConst164 * fRec12[0]))))) + (fConst163 + (fConst162 * fRec12[0])))) + (fRec15[1] * (((fRec14[0] * ((fConst161 + (fConst160 * fRec12[0])) + (fConst1 * (fRec13[0] * (fConst159 + (fConst158 * fRec12[0])))))) + (fConst1 * (fRec13[0] * (fConst157 + (fConst156 * fRec12[0]))))) + (fConst155 + (fConst154 * fRec12[0]))))) + (fRec15[2] * (((fRec14[0] * ((fConst153 + (fConst152 * fRec12[0])) + (fConst1 * (fRec13[0] * (fConst151 + (fConst150 * fRec12[0])))))) + (fConst1 * (fRec13[0] * (fConst149 + (fConst148 * fRec12[0]))))) + (fConst147 + (fConst146 * fRec12[0]))))) + (fRec15[3] * (((fRec14[0] * ((fConst145 + (fConst143 * fRec12[0])) + (fConst1 * (fRec13[0] * (fConst141 + (fConst139 * fRec12[0])))))) + (fConst1 * (fRec13[0] * (fConst137 + (fConst135 * fRec12[0]))))) + (fConst133 + (fConst131 * fRec12[0]))))) + (fRec15[4] * (((fRec14[0] * ((fConst129 + (fConst127 * fRec12[0])) + (fConst1 * (fRec13[0] * (fConst125 + (fConst123 * fRec12[0])))))) + (fConst1 * (fRec13[0] * (fConst121 + (fConst119 * fRec12[0]))))) + (fConst117 + (fConst115 * fRec12[0]))))) + (fRec15[5] * (((fRec14[0] * ((fConst37 + (fConst35 * fRec12[0])) + (fConst1 * (fRec13[0] * (fConst33 + (fConst31 * fRec12[0])))))) + (fConst1 * (fRec13[0] * (fConst29 + (fConst27 * fRec12[0]))))) + (fConst25 + (fConst23 * fRec12[0])))))) / fTemp1);
		fVec0[0] = fTemp2;
		fRec11[0] = ((fConst170 * (fVec0[0] + fVec0[1])) - (0.8605695850647829 * fRec11[1]));
		fRec10[0] = (fRec11[0] - ((1.8405051250752198 * fRec10[1]) + (0.8612942439318627 * fRec10[2])));
		fRec17[0] = ((fConst174 * fRec17[1]) + (fConst173 * (fRec9[1] + fRec9[2])));
		fRec9[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec17[0] + (0.9254498422517706 * (fRec10[2] + (fRec10[0] + (2.0 * fRec10[1]))))) - 3.571981)) - 117.70440740740739);
		fRec8[0] = ((fConst179 * fRec8[1]) + (fConst178 * ((fConst175 * fRec9[0]) + (fConst176 * fRec9[1]))));
		fRec7[0] = ((0.9302847925323914 * (fRec8[0] + fRec8[1])) - (0.8605695850647829 * fRec7[1]));
		fRec6[0] = (fRec7[0] - ((1.8405051250752198 * fRec6[1]) + (0.8612942439318627 * fRec6[2])));
		fRec18[0] = ((fConst174 * fRec18[1]) + (fConst173 * (fRec5[1] + fRec5[2])));
		fRec5[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec18[0] + (0.9254498422517706 * (fRec6[2] + (fRec6[0] + (2.0 * fRec6[1]))))) - 3.571981)) - 117.70440740740739);
		fRec4[0] = ((fConst179 * fRec4[1]) + (fConst178 * ((fConst175 * fRec5[0]) + (fConst176 * fRec5[1]))));
		fRec3[0] = ((0.9302847925323914 * (fRec4[0] + fRec4[1])) - (0.8605695850647829 * fRec3[1]));
		fRec2[0] = (fRec3[0] - ((1.8405051250752198 * fRec2[1]) + (0.8612942439318627 * fRec2[2])));
		fRec19[0] = ((fConst174 * fRec19[1]) + (fConst173 * (fRec1[1] + fRec1[2])));
		fRec1[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec19[0] + (0.9254498422517706 * (fRec2[2] + (fRec2[0] + (2.0 * fRec2[1]))))) - 3.571981)) - 117.70440740740739);
		fRec0[0] = ((fConst179 * fRec0[1]) + (fConst178 * ((fConst175 * fRec1[0]) + (fConst176 * fRec1[1]))));
		output0[i] = (FAUSTFLOAT)(fRec0[0] + (fSlow1 * fTemp0));
		// post processing
		fRec0[1] = fRec0[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec19[1] = fRec19[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec18[1] = fRec18[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec17[1] = fRec17[0];
		fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		fVec0[1] = fVec0[0];
		fRec16[1] = fRec16[0];
		for (int i=5; i>0; i--) fRec15[i] = fRec15[i-1];
		fRec14[1] = fRec14[0];
		fRec13[1] = fRec13[0];
		fRec12[1] = fRec12[0];
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
	reg.registerVar("ffreak.wet_dry",N_("Wet/Dry"),"S",N_("percentage of processed signal in output signal"),&fslider0, 1e+02, 0.0, 1e+02, 1.0);
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
                <property name=\"spacing\">22</property>\n\
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
