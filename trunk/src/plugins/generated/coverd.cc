// generated from file '../src/plugins/coverd.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

namespace pluginlib {
namespace coverd {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	double 	fConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	FAUSTFLOAT 	fslider0;
	double 	fRec0[2];
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	FAUSTFLOAT 	fslider1;
	double 	fRec1[2];
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
	FAUSTFLOAT 	fslider2;
	double 	fRec3[2];
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
	FAUSTFLOAT 	fslider3;
	double 	fRec4[6];
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
	double 	fRec2[6];
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
	double 	fConst175;
	double 	fConst176;
	double 	fConst177;
	double 	fConst178;
	double 	fConst179;
	double 	fConst180;
	double 	fConst181;
	double 	fConst182;
	double 	fConst183;
	double 	fConst184;
	double 	fConst185;
	double 	fConst186;
	double 	fConst187;
	double 	fConst188;
	double 	fConst189;
	double 	fConst190;
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
	id = "coverd";
	name = N_("C Overdrive");
	groups = 0;
	description = N_("Colorsound Overdrive"); // description (tooltip)
	category = N_("Distortion");       // category
	shortname = N_("C Overdrive");     // shortname
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
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<6; i++) fRec4[i] = 0;
	for (int i=0; i<6; i++) fRec2[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = double(min(192000, max(1, fSamplingFreq)));
	fConst1 = (2.23797473617709e-24 * fConst0);
	fConst2 = (6.97469477751319e-35 + (fConst0 * (1.74198245202729e-20 + (fConst0 * (1.74849041434644e-22 - fConst1)))));
	fConst3 = (9.07610804066639e-25 * fConst0);
	fConst4 = ((fConst0 * ((fConst0 * (0 - (3.13971543026984e-22 + fConst3))) - 1.80077239576117e-20)) - 1.69522373979748e-20);
	fConst5 = (1.11390635159433e-24 * fConst0);
	fConst6 = ((fConst0 * ((fConst0 * (3.18702063081927e-22 + fConst5)) - 7.14108820102165e-34)) - 1.80540050182853e-48);
	fConst7 = (7.72208706599171e-24 * fConst0);
	fConst8 = (7.605464376339e-34 + (fConst0 * ((fConst0 * (0 - (6.05969681445433e-22 + fConst7))) - 3.39044747958769e-22)));
	fConst9 = (5.49427436280305e-24 * fConst0);
	fConst10 = ((fConst0 * (3.39044747960198e-22 + (fConst0 * (fConst9 - 3.14344447184204e-23)))) - 7.60546437633897e-34);
	fConst11 = (1.11582073532266e-24 * fConst0);
	fConst12 = (3.39044747959503e-20 + (fConst0 * (8.5311710434333e-22 + (fConst0 * (3.23543557700559e-22 + fConst11)))));
	fConst13 = (3.22318393238815e-24 * fConst0);
	fConst14 = (4.5272406798381e-15 + (fConst0 * (9.66029729825488e-17 + (fConst0 * (5.44196016387214e-19 + (fConst0 * (2.32489770791907e-21 + fConst13)))))));
	fConst15 = (7.09491773348213e-24 * fConst0);
	fConst16 = ((fConst0 * (8.47611869896916e-17 + (fConst0 * (1.677855547693e-16 + (fConst0 * (2.55872993315156e-18 + (fConst0 * (8.1036807179337e-21 + fConst15)))))))) - 1.90136609408475e-28);
	fConst17 = (6.72581680534004e-24 * fConst0);
	fConst18 = (4.51350125457133e-43 + (fConst0 * (1.78867236680673e-28 + (fConst0 * ((fConst0 * ((fConst0 * (0 - (4.41586600140972e-21 + fConst17))) - 7.47371530788388e-19)) - 9.57970935359556e-17)))));
	fConst19 = (3.8335982187148e-25 * fConst0);
	fConst20 = (2.85213539992201e-18 + (fConst0 * ((fConst0 * (1.95786469833648e-18 + (fConst0 * (fConst19 - 5.42251622369686e-21)))) - 7.39993880685971e-17)));
	fConst21 = (1.0025039931634e-23 * fConst0);
	fConst22 = (6.08366393926321e-36 + (fConst0 * (fConst21 - 4.24692905313867e-22)));
	fConst23 = (6.58813040006868e-24 * fConst0);
	fConst24 = (7.07969084128568e-37 + (fConst0 * (fConst23 - 2.80345974471016e-22)));
	fConst25 = (6.88899571441955e-24 * fConst0);
	fConst26 = ((fConst0 * (2.95929420463955e-22 - fConst25)) - 1.1408541599688e-23);
	fConst27 = ((fConst0 * (2.80345974471016e-22 - fConst23)) - 7.07969084128568e-37);
	fConst28 = (1.91438372832372e-27 * fConst0);
	fConst29 = (2.28170831993645e-23 + (fConst0 * (0 - (9.28894735127254e-24 + fConst28))));
	fConst30 = faustpower<2>(fConst0);
	fConst31 = (2.08000946656956e-27 * fConst0);
	fConst32 = (fConst0 * (3.53984542064284e-34 + (fConst0 * ((fConst0 * (3.29838842203039e-21 + fConst31)) - 1.40184395777108e-19))));
	fConst33 = (3.70058120006252e-25 * fConst0);
	fConst34 = ((fConst0 * (7.0086493617754e-17 + (fConst0 * ((fConst0 * (3.84955928653808e-22 - fConst33)) - 1.66273197458755e-18)))) - 1.76992271032142e-31);
	fConst35 = (6.97469477751319e-35 + (fConst0 * ((fConst0 * (1.74849041434644e-22 + fConst1)) - 1.74198245202729e-20)));
	fConst36 = ((fConst0 * (1.80077239576117e-20 + (fConst0 * (fConst3 - 3.13971543026984e-22)))) - 1.69522373979748e-20);
	fConst37 = ((fConst0 * (7.14108820102165e-34 + (fConst0 * (3.18702063081927e-22 - fConst5)))) - 1.80540050182853e-48);
	fConst38 = (7.605464376339e-34 + (fConst0 * (3.39044747958769e-22 + (fConst0 * (fConst7 - 6.05969681445433e-22)))));
	fConst39 = ((fConst0 * ((fConst0 * (0 - (3.14344447184204e-23 + fConst9))) - 3.39044747960198e-22)) - 7.60546437633897e-34);
	fConst40 = (3.39044747959503e-20 + (fConst0 * ((fConst0 * (3.23543557700559e-22 - fConst11)) - 8.5311710434333e-22)));
	fConst41 = ((fConst0 * (9.66029729825488e-17 + (fConst0 * ((fConst0 * (2.32489770791907e-21 - fConst13)) - 5.44196016387214e-19)))) - 4.5272406798381e-15);
	fConst42 = ((fConst0 * ((fConst0 * (1.677855547693e-16 + (fConst0 * ((fConst0 * (8.1036807179337e-21 - fConst15)) - 2.55872993315156e-18)))) - 8.47611869896916e-17)) - 1.90136609408475e-28);
	fConst43 = (4.51350125457133e-43 + (fConst0 * ((fConst0 * ((fConst0 * (7.47371530788388e-19 + (fConst0 * (fConst17 - 4.41586600140972e-21)))) - 9.57970935359556e-17)) - 1.78867236680673e-28)));
	fConst44 = (1.11898736808855e-23 * fConst0);
	fConst45 = (6.97469477751319e-35 + (fConst0 * (1.74198245202729e-20 + (fConst0 * (0 - (5.24547124303932e-22 + fConst44))))));
	fConst46 = (4.53805402033319e-24 * fConst0);
	fConst47 = ((fConst0 * ((fConst0 * (9.41914629080951e-22 - fConst46)) - 1.80077239576117e-20)) - 1.69522373979748e-20);
	fConst48 = (5.56953175797167e-24 * fConst0);
	fConst49 = ((fConst0 * ((fConst0 * (fConst48 - 9.5610618924578e-22)) - 7.14108820102165e-34)) - 1.80540050182853e-48);
	fConst50 = (3.86104353299586e-23 * fConst0);
	fConst51 = (7.605464376339e-34 + (fConst0 * ((fConst0 * (1.8179090443363e-21 - fConst50)) - 3.39044747958769e-22)));
	fConst52 = (2.74713718140152e-23 * fConst0);
	fConst53 = ((fConst0 * (3.39044747960198e-22 + (fConst0 * (9.43033341552612e-23 + fConst52)))) - 7.60546437633897e-34);
	fConst54 = (5.57910367661329e-24 * fConst0);
	fConst55 = (3.39044747959503e-20 + (fConst0 * (8.5311710434333e-22 + (fConst0 * (fConst54 - 9.70630673101678e-22)))));
	fConst56 = (1.61159196619408e-23 * fConst0);
	fConst57 = ((fConst0 * (9.66029729825488e-17 + (fConst0 * (5.44196016387214e-19 + (fConst0 * (fConst56 - 6.9746931237572e-21)))))) - 1.35817220395143e-14);
	fConst58 = (3.54745886674106e-23 * fConst0);
	fConst59 = ((fConst0 * ((fConst0 * (1.677855547693e-16 + (fConst0 * (2.55872993315156e-18 + (fConst0 * (fConst58 - 2.43110421538011e-20)))))) - 2.54283560969075e-16)) - 9.50683047042375e-28);
	fConst60 = (3.36290840267002e-23 * fConst0);
	fConst61 = (2.25675062728566e-42 + (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (1.32475980042292e-20 - fConst60)) - 7.47371530788388e-19)) - 9.57970935359556e-17)) - 5.3660171004202e-28)));
	fConst62 = (2.23797473617709e-23 * fConst0);
	fConst63 = ((fConst0 * (3.48396490405458e-20 + (fConst0 * (3.49698082869288e-22 + fConst62)))) - 1.39493895550264e-34);
	fConst64 = (9.07610804066639e-24 * fConst0);
	fConst65 = (3.39044747959497e-20 + (fConst0 * ((fConst0 * (fConst64 - 6.27943086053967e-22)) - 3.60154479152234e-20)));
	fConst66 = (1.11390635159433e-23 * fConst0);
	fConst67 = (3.61080100365706e-48 + (fConst0 * ((fConst0 * (6.37404126163853e-22 - fConst66)) - 1.42821764020433e-33)));
	fConst68 = (7.72208706599171e-23 * fConst0);
	fConst69 = ((fConst0 * ((fConst0 * (fConst68 - 1.21193936289087e-21)) - 6.78089495917539e-22)) - 1.5210928752678e-33);
	fConst70 = (5.49427436280305e-23 * fConst0);
	fConst71 = (1.52109287526779e-33 + (fConst0 * (6.78089495920395e-22 + (fConst0 * (0 - (6.28688894368408e-23 + fConst70))))));
	fConst72 = (1.11582073532266e-23 * fConst0);
	fConst73 = ((fConst0 * (1.70623420868666e-21 + (fConst0 * (6.47087115401119e-22 - fConst72)))) - 6.78089495919005e-20);
	fConst74 = (3.22318393238815e-23 * fConst0);
	fConst75 = ((fConst0 * ((fConst0 * (1.08839203277443e-18 + (fConst0 * (4.64979541583813e-21 - fConst74)))) - 1.93205945965098e-16)) - 9.05448135967619e-15);
	fConst76 = (7.09491773348213e-23 * fConst0);
	fConst77 = ((fConst0 * ((fConst0 * ((fConst0 * (5.11745986630311e-18 + (fConst0 * (1.62073614358674e-20 - fConst76)))) - 3.35571109538599e-16)) - 1.69522373979383e-16)) - 1.90136609408475e-27);
	fConst78 = (6.72581680534004e-23 * fConst0);
	fConst79 = (4.51350125457133e-42 + (fConst0 * ((fConst0 * (1.91594187071911e-16 + (fConst0 * ((fConst0 * (fConst78 - 8.83173200281944e-21)) - 1.49474306157678e-18)))) - 3.57734473361347e-28)));
	fConst80 = ((fConst0 * ((fConst0 * (3.49698082869288e-22 - fConst62)) - 3.48396490405458e-20)) - 1.39493895550264e-34);
	fConst81 = (3.39044747959497e-20 + (fConst0 * (3.60154479152234e-20 + (fConst0 * (0 - (6.27943086053967e-22 + fConst64))))));
	fConst82 = (3.61080100365706e-48 + (fConst0 * (1.42821764020433e-33 + (fConst0 * (6.37404126163853e-22 + fConst66)))));
	fConst83 = ((fConst0 * (6.78089495917539e-22 + (fConst0 * (0 - (1.21193936289087e-21 + fConst68))))) - 1.5210928752678e-33);
	fConst84 = (1.52109287526779e-33 + (fConst0 * ((fConst0 * (fConst70 - 6.28688894368408e-23)) - 6.78089495920395e-22)));
	fConst85 = ((fConst0 * ((fConst0 * (6.47087115401119e-22 + fConst72)) - 1.70623420868666e-21)) - 6.78089495919005e-20);
	fConst86 = (9.05448135967619e-15 + (fConst0 * ((fConst0 * ((fConst0 * (4.64979541583813e-21 + fConst74)) - 1.08839203277443e-18)) - 1.93205945965098e-16)));
	fConst87 = ((fConst0 * (1.69522373979383e-16 + (fConst0 * ((fConst0 * ((fConst0 * (1.62073614358674e-20 + fConst76)) - 5.11745986630311e-18)) - 3.35571109538599e-16)))) - 1.90136609408475e-27);
	fConst88 = (4.51350125457133e-42 + (fConst0 * (3.57734473361347e-28 + (fConst0 * (1.91594187071911e-16 + (fConst0 * (1.49474306157678e-18 + (fConst0 * (0 - (8.83173200281944e-21 + fConst78))))))))));
	fConst89 = (6.97469477751319e-35 + (fConst0 * ((fConst0 * (fConst44 - 5.24547124303932e-22)) - 1.74198245202729e-20)));
	fConst90 = ((fConst0 * (1.80077239576117e-20 + (fConst0 * (9.41914629080951e-22 + fConst46)))) - 1.69522373979748e-20);
	fConst91 = ((fConst0 * (7.14108820102165e-34 + (fConst0 * (0 - (9.5610618924578e-22 + fConst48))))) - 1.80540050182853e-48);
	fConst92 = (7.605464376339e-34 + (fConst0 * (3.39044747958769e-22 + (fConst0 * (1.8179090443363e-21 + fConst50)))));
	fConst93 = ((fConst0 * ((fConst0 * (9.43033341552612e-23 - fConst52)) - 3.39044747960198e-22)) - 7.60546437633897e-34);
	fConst94 = (3.39044747959503e-20 + (fConst0 * ((fConst0 * (0 - (9.70630673101678e-22 + fConst54))) - 8.5311710434333e-22)));
	fConst95 = (1.35817220395143e-14 + (fConst0 * (9.66029729825488e-17 + (fConst0 * ((fConst0 * (0 - (6.9746931237572e-21 + fConst56))) - 5.44196016387214e-19)))));
	fConst96 = ((fConst0 * (2.54283560969075e-16 + (fConst0 * (1.677855547693e-16 + (fConst0 * ((fConst0 * (0 - (2.43110421538011e-20 + fConst58))) - 2.55872993315156e-18)))))) - 9.50683047042375e-28);
	fConst97 = (2.25675062728566e-42 + (fConst0 * (5.3660171004202e-28 + (fConst0 * ((fConst0 * (7.47371530788388e-19 + (fConst0 * (1.32475980042292e-20 + fConst60)))) - 9.57970935359556e-17)))));
	fConst98 = (2.78713041660513e-24 * fConst0);
	fConst99 = (1.16306066588601e-15 + (fConst0 * (1.42685467015479e-15 + (fConst0 * (3.13137866048362e-16 + (fConst0 * (1.25272695161612e-17 + (fConst0 * (2.03907877623046e-19 + fConst98)))))))));
	fConst100 = (2.40788246727257e-24 * fConst0);
	fConst101 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (0 - (1.83337089189981e-19 + fConst100))) - 1.0884037880131e-17)) - 2.17663092851014e-16)) - 5.23377299648722e-16)) - 4.66166061483529e-29);
	fConst102 = (3.97647190322603e-27 * fConst0);
	fConst103 = (2.63401345836477e-31 + (fConst0 * ((fConst0 * (2.12282875792926e-17 + (fConst0 * (0 - (4.95880631786145e-19 + fConst102))))) - 2.95727845714664e-18)));
	fConst104 = (7.42702058644117e-27 * fConst0);
	fConst105 = ((fConst0 * (5.04598373508118e-17 + (fConst0 * ((fConst0 * (7.89889133199585e-19 + fConst104)) - 3.48875412150739e-17)))) - 6.57172990476634e-18);
	fConst106 = (1.16306066588601e-15 + (fConst0 * ((fConst0 * (3.13137866048362e-16 + (fConst0 * ((fConst0 * (2.03907877623046e-19 - fConst98)) - 1.25272695161612e-17)))) - 1.42685467015479e-15)));
	fConst107 = ((fConst0 * (5.23377299648722e-16 + (fConst0 * ((fConst0 * (1.0884037880131e-17 + (fConst0 * (fConst100 - 1.83337089189981e-19)))) - 2.17663092851014e-16)))) - 4.66166061483529e-29);
	fConst108 = (1.39356520830257e-23 * fConst0);
	fConst109 = (5.81530332943008e-15 + (fConst0 * ((fConst0 * (3.13137866048362e-16 + (fConst0 * (1.25272695161612e-17 + (fConst0 * (fConst108 - 6.11723632869138e-19)))))) - 4.28056401046438e-15)));
	fConst110 = (1.20394123363628e-23 * fConst0);
	fConst111 = ((fConst0 * (1.57013189894617e-15 + (fConst0 * ((fConst0 * ((fConst0 * (5.50011267569942e-19 - fConst110)) - 1.0884037880131e-17)) - 2.17663092851014e-16)))) - 2.33083030741764e-28);
	fConst112 = (2.78713041660513e-23 * fConst0);
	fConst113 = (1.16306066588602e-14 + (fConst0 * ((fConst0 * ((fConst0 * (2.50545390323223e-17 + (fConst0 * (4.07815755246092e-19 - fConst112)))) - 6.26275732096724e-16)) - 2.85370934030959e-15)));
	fConst114 = (2.40788246727257e-23 * fConst0);
	fConst115 = ((fConst0 * (1.04675459929744e-15 + (fConst0 * (4.35326185702027e-16 + (fConst0 * ((fConst0 * (fConst114 - 3.66674178379961e-19)) - 2.17680757602621e-17)))))) - 4.66166061483529e-28);
	fConst116 = (1.16306066588602e-14 + (fConst0 * (2.85370934030959e-15 + (fConst0 * ((fConst0 * ((fConst0 * (4.07815755246092e-19 + fConst112)) - 2.50545390323223e-17)) - 6.26275732096724e-16)))));
	fConst117 = ((fConst0 * ((fConst0 * (4.35326185702027e-16 + (fConst0 * (2.17680757602621e-17 + (fConst0 * (0 - (3.66674178379961e-19 + fConst114))))))) - 1.04675459929744e-15)) - 4.66166061483529e-28);
	fConst118 = (5.81530332943008e-15 + (fConst0 * (4.28056401046438e-15 + (fConst0 * (3.13137866048362e-16 + (fConst0 * ((fConst0 * (0 - (6.11723632869138e-19 + fConst108))) - 1.25272695161612e-17)))))));
	fConst119 = ((fConst0 * ((fConst0 * ((fConst0 * (1.0884037880131e-17 + (fConst0 * (5.50011267569942e-19 + fConst110)))) - 2.17663092851014e-16)) - 1.57013189894617e-15)) - 2.33083030741764e-28);
	fConst120 = (1.98823595161302e-26 * fConst0);
	fConst121 = (7.9020403750943e-31 + (fConst0 * ((fConst0 * ((fConst0 * (1.48764189535843e-18 + fConst120)) - 2.12282875792926e-17)) - 2.95727845714664e-18)));
	fConst122 = (3.71351029322059e-26 * fConst0);
	fConst123 = ((fConst0 * (5.04598373508118e-17 + (fConst0 * (3.48875412150739e-17 + (fConst0 * (0 - (2.36966739959876e-18 + fConst122))))))) - 1.9715189714299e-17);
	fConst124 = (3.97647190322603e-26 * fConst0);
	fConst125 = (5.26802691672954e-31 + (fConst0 * (5.91455691429328e-18 + (fConst0 * ((fConst0 * (0 - (9.91761263572289e-19 + fConst124))) - 4.24565751585853e-17)))));
	fConst126 = (7.42702058644117e-26 * fConst0);
	fConst127 = ((fConst0 * ((fConst0 * (6.97750824301479e-17 + (fConst0 * (1.57977826639917e-18 + fConst126)))) - 1.00919674701624e-16)) - 1.31434598095327e-17);
	fConst128 = ((fConst0 * (5.91455691429328e-18 + (fConst0 * (4.24565751585853e-17 + (fConst0 * (fConst124 - 9.91761263572289e-19)))))) - 5.26802691672954e-31);
	fConst129 = (1.31434598095327e-17 + (fConst0 * ((fConst0 * ((fConst0 * (1.57977826639917e-18 - fConst126)) - 6.97750824301479e-17)) - 1.00919674701624e-16)));
	fConst130 = ((fConst0 * ((fConst0 * (2.12282875792926e-17 + (fConst0 * (1.48764189535843e-18 - fConst120)))) - 2.95727845714664e-18)) - 7.9020403750943e-31);
	fConst131 = (1.9715189714299e-17 + (fConst0 * (5.04598373508118e-17 + (fConst0 * ((fConst0 * (fConst122 - 2.36966739959876e-18)) - 3.48875412150739e-17)))));
	fConst132 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst102 - 4.95880631786145e-19)) - 2.12282875792926e-17)) - 2.95727845714664e-18)) - 2.63401345836477e-31);
	fConst133 = (6.57172990476634e-18 + (fConst0 * (5.04598373508118e-17 + (fConst0 * (3.48875412150739e-17 + (fConst0 * (7.89889133199585e-19 - fConst104)))))));
	fConst134 = (1.9167991093574e-24 * fConst0);
	fConst135 = (8.55640619976602e-18 + (fConst0 * ((fConst0 * ((fConst0 * (1.62675486710906e-20 - fConst134)) - 1.95786469833648e-18)) - 7.39993880685971e-17)));
	fConst136 = (5.012519965817e-23 * fConst0);
	fConst137 = ((fConst0 * (1.2740787159416e-21 - fConst136)) - 6.08366393926321e-36);
	fConst138 = (3.29406520003434e-23 * fConst0);
	fConst139 = ((fConst0 * (8.41037923413049e-22 - fConst138)) - 7.07969084128568e-37);
	fConst140 = (3.44449785720978e-23 * fConst0);
	fConst141 = (1.1408541599688e-23 + (fConst0 * (fConst140 - 8.87788261391865e-22)));
	fConst142 = (7.07969084128568e-37 + (fConst0 * (fConst138 - 8.41037923413049e-22)));
	fConst143 = (9.57191864161859e-27 * fConst0);
	fConst144 = ((fConst0 * (2.78668420538176e-23 + fConst143)) - 2.28170831993645e-23);
	fConst145 = (1.04000473328478e-26 * fConst0);
	fConst146 = (fConst0 * (3.53984542064284e-34 + (fConst0 * (1.40184395777108e-19 + (fConst0 * (0 - (9.89516526609117e-21 + fConst145)))))));
	fConst147 = (1.85029060003126e-24 * fConst0);
	fConst148 = ((fConst0 * (7.0086493617754e-17 + (fConst0 * (1.66273197458755e-18 + (fConst0 * (fConst147 - 1.15486778596142e-21)))))) - 5.30976813096426e-31);
	fConst149 = (3.8335982187148e-24 * fConst0);
	fConst150 = (5.70427079984401e-18 + (fConst0 * (1.47998776137194e-16 + (fConst0 * ((fConst0 * (fConst149 - 1.08450324473937e-20)) - 3.91572939667295e-18)))));
	fConst151 = (6.58813040006868e-23 * fConst0);
	fConst152 = ((fConst0 * (fConst151 - 5.60691948942032e-22)) - 1.41593816825714e-36);
	fConst153 = (6.88899571441955e-23 * fConst0);
	fConst154 = (2.28170831993761e-23 + (fConst0 * (5.9185884092791e-22 - fConst153)));
	fConst155 = (1.41593816825714e-36 + (fConst0 * (5.60691948942032e-22 - fConst151)));
	fConst156 = (1.91438372832372e-26 * fConst0);
	fConst157 = ((fConst0 * (0 - (1.85778947025451e-23 + fConst156))) - 4.56341663987291e-23);
	fConst158 = (1.0025039931634e-22 * fConst0);
	fConst159 = ((fConst0 * (fConst158 - 8.49385810627733e-22)) - 1.21673278785264e-35);
	fConst160 = (2.08000946656956e-26 * fConst0);
	fConst161 = (fConst0 * ((fConst0 * (2.80368791554216e-19 + (fConst0 * (6.59677684406078e-21 + fConst160)))) - 7.07969084128568e-34));
	fConst162 = (3.70058120006252e-24 * fConst0);
	fConst163 = ((fConst0 * ((fConst0 * (3.32546394917509e-18 + (fConst0 * (7.69911857307616e-22 - fConst162)))) - 1.40172987235508e-16)) - 3.53984542064284e-31);
	fConst164 = ((fConst0 * (1.47998776137194e-16 + (fConst0 * (3.91572939667295e-18 + (fConst0 * (0 - (1.08450324473937e-20 + fConst149))))))) - 5.70427079984401e-18);
	fConst165 = (1.21673278785264e-35 + (fConst0 * (0 - (8.49385810627733e-22 + fConst158))));
	fConst166 = (5.60691948942032e-22 + fConst151);
	fConst167 = (1.41593816825714e-36 + (fConst0 * (0 - fConst166)));
	fConst168 = ((fConst0 * (5.9185884092791e-22 + fConst153)) - 2.28170831993761e-23);
	fConst169 = ((fConst0 * fConst166) - 1.41593816825714e-36);
	fConst170 = (4.56341663987291e-23 + (fConst0 * (fConst156 - 1.85778947025451e-23)));
	fConst171 = (fConst0 * ((fConst0 * ((fConst0 * (6.59677684406078e-21 - fConst160)) - 2.80368791554216e-19)) - 7.07969084128568e-34));
	fConst172 = (3.53984542064284e-31 + (fConst0 * ((fConst0 * ((fConst0 * (7.69911857307616e-22 + fConst162)) - 3.32546394917509e-18)) - 1.40172987235508e-16)));
	fConst173 = ((fConst0 * ((fConst0 * (1.95786469833648e-18 + (fConst0 * (1.62675486710906e-20 + fConst134)))) - 7.39993880685971e-17)) - 8.55640619976602e-18);
	fConst174 = (6.08366393926321e-36 + (fConst0 * (1.2740787159416e-21 + fConst136)));
	fConst175 = (8.41037923413049e-22 + fConst138);
	fConst176 = (7.07969084128568e-37 + (fConst0 * fConst175));
	fConst177 = ((fConst0 * (0 - (8.87788261391865e-22 + fConst140))) - 1.1408541599688e-23);
	fConst178 = ((fConst0 * (0 - fConst175)) - 7.07969084128568e-37);
	fConst179 = (2.28170831993645e-23 + (fConst0 * (2.78668420538176e-23 - fConst143)));
	fConst180 = (fConst0 * (3.53984542064284e-34 + (fConst0 * ((fConst0 * (fConst145 - 9.89516526609117e-21)) - 1.40184395777108e-19))));
	fConst181 = (5.30976813096426e-31 + (fConst0 * (7.0086493617754e-17 + (fConst0 * ((fConst0 * (0 - (1.15486778596142e-21 + fConst147))) - 1.66273197458755e-18)))));
	fConst182 = ((fConst0 * ((fConst0 * ((fConst0 * (0 - (5.42251622369686e-21 + fConst19))) - 1.95786469833648e-18)) - 7.39993880685971e-17)) - 2.85213539992201e-18);
	fConst183 = ((fConst0 * (0 - (4.24692905313867e-22 + fConst21))) - 6.08366393926321e-36);
	fConst184 = (2.80345974471016e-22 + fConst23);
	fConst185 = ((fConst0 * (0 - fConst184)) - 7.07969084128568e-37);
	fConst186 = (1.1408541599688e-23 + (fConst0 * (2.95929420463955e-22 + fConst25)));
	fConst187 = (7.07969084128568e-37 + (fConst0 * fConst184));
	fConst188 = ((fConst0 * (fConst28 - 9.28894735127254e-24)) - 2.28170831993645e-23);
	fConst189 = (fConst0 * (3.53984542064284e-34 + (fConst0 * (1.40184395777108e-19 + (fConst0 * (3.29838842203039e-21 - fConst31))))));
	fConst190 = (1.76992271032142e-31 + (fConst0 * (7.0086493617754e-17 + (fConst0 * (1.66273197458755e-18 + (fConst0 * (3.84955928653808e-22 + fConst33)))))));
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlow0 = (0.007000000000000006 * (1 - double(fslider0)));
	double 	fSlow1 = (0.007000000000000006 * double(fslider1));
	double 	fSlow2 = (0.004073836948085289 * (exp(double(fslider2)) - 1));
	double 	fSlow3 = (0.01 * double(fslider3));
	double 	fSlow4 = (1 - fSlow3);
	for (int i=0; i<count; i++) {
		fRec0[0] = ((0.993 * fRec0[1]) + fSlow0);
		fRec1[0] = ((0.993 * fRec1[1]) + fSlow1);
		double fTemp0 = (4.23805934949371e-15 + ((fRec0[0] * ((fConst18 * fRec0[0]) + fConst16)) + (fConst0 * (fConst14 + (fConst0 * (fRec1[0] * (((fRec0[0] * (fConst12 + (fConst10 * fRec0[0]))) + (fRec1[0] * ((fRec0[0] * (fConst8 + (fConst6 * fRec0[0]))) + fConst4))) + fConst2)))))));
		fRec3[0] = ((0.993 * fRec3[1]) + fSlow2);
		double fTemp1 = ((fConst101 * fRec3[0]) + fConst99);
		double fTemp2 = (double)input0[i];
		fRec4[0] = ((fSlow3 * fTemp2) - ((((((fRec4[1] * ((fConst119 * fRec3[0]) + fConst118)) + (fRec4[2] * ((fConst117 * fRec3[0]) + fConst116))) + (fRec4[3] * ((fConst115 * fRec3[0]) + fConst113))) + (fRec4[4] * ((fConst111 * fRec3[0]) + fConst109))) + (fRec4[5] * ((fConst107 * fRec3[0]) + fConst106))) / fTemp1));
		double fTemp3 = ((((((fRec4[0] * (fConst133 + (fConst132 * fRec3[0]))) + (fRec4[1] * (fConst131 + (fConst130 * fRec3[0])))) + (fRec4[2] * (fConst129 + (fConst128 * fRec3[0])))) + (fRec4[3] * (fConst127 + (fConst125 * fRec3[0])))) + (fRec4[4] * (fConst123 + (fConst121 * fRec3[0])))) + (fRec4[5] * (fConst105 + (fConst103 * fRec3[0]))));
		double fTemp4 = fabs((fConst0 * (fTemp3 / fTemp1)));
		fRec2[0] = ((fConst0 * (((fRec3[0] * fTemp3) * (0.5 + fTemp4)) / (fTemp1 * ((1 + (fConst30 * (faustpower<2>(fTemp3) / faustpower<2>(fTemp1)))) - (0.5 * fTemp4))))) - ((((((fRec2[1] * (2.11902967474685e-14 + ((fRec0[0] * ((fConst97 * fRec0[0]) + fConst96)) + (fConst0 * (fConst95 + (fConst0 * (fRec1[0] * (((fRec0[0] * (fConst94 + (fConst93 * fRec0[0]))) + (fRec1[0] * ((fRec0[0] * (fConst92 + (fConst91 * fRec0[0]))) + fConst90))) + fConst89)))))))) + (fRec2[2] * (4.23805934949371e-14 + ((fRec0[0] * ((fConst88 * fRec0[0]) + fConst87)) + (fConst0 * (fConst86 + (fConst0 * (fRec1[0] * (((fRec0[0] * (fConst85 + (fConst84 * fRec0[0]))) + (fRec1[0] * ((fRec0[0] * (fConst83 + (fConst82 * fRec0[0]))) + fConst81))) + fConst80))))))))) + (fRec2[3] * (4.23805934949371e-14 + ((fRec0[0] * ((fConst79 * fRec0[0]) + fConst77)) + (fConst0 * (fConst75 + (fConst0 * (fRec1[0] * (((fRec0[0] * (fConst73 + (fConst71 * fRec0[0]))) + (fRec1[0] * ((fRec0[0] * (fConst69 + (fConst67 * fRec0[0]))) + fConst65))) + fConst63))))))))) + (fRec2[4] * (2.11902967474685e-14 + ((fRec0[0] * ((fConst61 * fRec0[0]) + fConst59)) + (fConst0 * (fConst57 + (fConst0 * (fRec1[0] * (((fRec0[0] * (fConst55 + (fConst53 * fRec0[0]))) + (fRec1[0] * ((fRec0[0] * (fConst51 + (fConst49 * fRec0[0]))) + fConst47))) + fConst45))))))))) + (fRec2[5] * (4.23805934949371e-15 + ((fRec0[0] * ((fConst43 * fRec0[0]) + fConst42)) + (fConst0 * (fConst41 + (fConst0 * (fRec1[0] * (((fRec0[0] * (fConst40 + (fConst39 * fRec0[0]))) + (fRec1[0] * ((fRec0[0] * (fConst38 + (fConst37 * fRec0[0]))) + fConst36))) + fConst35))))))))) / fTemp0));
		output0[i] = (FAUSTFLOAT)((fSlow4 * fTemp2) + (fConst0 * (((((((fRec2[0] * (((fRec0[0] * (fConst190 + (fConst189 * fRec0[0]))) + (fConst30 * (fRec1[0] * (((fRec0[0] * (fConst188 + (fConst187 * fRec0[0]))) + (fRec1[0] * (fConst186 + (fConst185 * fRec0[0])))) + fConst183)))) + fConst182)) + (fRec2[1] * (((fRec0[0] * (fConst181 + (fConst180 * fRec0[0]))) + (fConst30 * (fRec1[0] * (((fRec0[0] * (fConst179 + (fConst178 * fRec0[0]))) + (fRec1[0] * (fConst177 + (fConst176 * fRec0[0])))) + fConst174)))) + fConst173))) + (fRec2[2] * (((fRec0[0] * (fConst172 + (fConst171 * fRec0[0]))) + (fConst30 * (fRec1[0] * (((fRec0[0] * (fConst170 + (fConst169 * fRec0[0]))) + (fRec1[0] * (fConst168 + (fConst167 * fRec0[0])))) + fConst165)))) + fConst164))) + (fRec2[3] * (((fRec0[0] * (fConst163 + (fConst161 * fRec0[0]))) + (fConst30 * (fRec1[0] * (fConst159 + ((fRec0[0] * (fConst157 + (fConst155 * fRec0[0]))) + (fRec1[0] * (fConst154 + (fConst152 * fRec0[0])))))))) + fConst150))) + (fRec2[4] * (((fRec0[0] * (fConst148 + (fConst146 * fRec0[0]))) + (fConst30 * (fRec1[0] * (((fRec0[0] * (fConst144 + (fConst142 * fRec0[0]))) + (fRec1[0] * (fConst141 + (fConst139 * fRec0[0])))) + fConst137)))) + fConst135))) + (fRec2[5] * (((fRec0[0] * (fConst34 + (fConst32 * fRec0[0]))) + (fConst30 * (fRec1[0] * (((fRec0[0] * (fConst29 + (fConst27 * fRec0[0]))) + (fRec1[0] * (fConst26 + (fConst24 * fRec0[0])))) + fConst22)))) + fConst20))) / fTemp0)));
		// post processing
		for (int i=5; i>0; i--) fRec2[i] = fRec2[i-1];
		for (int i=5; i>0; i--) fRec4[i] = fRec4[i-1];
		fRec3[1] = fRec3[0];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("coverd.Bass",N_("Bass"),"S","",&fslider0, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("coverd.Treble",N_("Treble"),"S","",&fslider1, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("coverd.Volume",N_("Volume"),"S","",&fslider2, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("coverd.wet_dry",N_("Wet/Dry"),"S",N_("percentage of processed signal in output signal"),&fslider3, 1e+02, 0.0, 1e+02, 1.0);
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
                        <property name=\"var_id\">coverd.Bass</property>\n\
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
                        <property name=\"var_id\">coverd.Treble</property>\n\
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
                      <object class=\"GxMidKnob\" id=\"gxbigknob3\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">coverd.Volume</property>\n\
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
                      <object class=\"GxSmallKnobR\" id=\"gxbigknob4\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">coverd.wet_dry</property>\n\
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
                <property name=\"var_id\">coverd.Volume</property>\n\
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
                <property name=\"label\" translatable=\"yes\">Volume</property>\n\
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
#define PARAM(p) ("coverd" "." p)

b.openHorizontalhideBox("");
    b.create_master_slider(PARAM("Volume"), "Volume");
b.closeBox();
b.openHorizontalBox("");

    b.create_small_rackknobr(PARAM("Volume"), "Volume");
    b.create_small_rackknobr(PARAM("Bass"), "Bass");
    b.create_small_rackknobr(PARAM("Treble"), "Treble");
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

} // end namespace coverd
} // end namespace pluginlib
