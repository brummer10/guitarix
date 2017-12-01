// generated from file '../src/plugins/coverd.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

namespace pluginlib {
namespace coverd {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	double 	fRec0[2];
	double 	fConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	FAUSTFLOAT 	fslider1;
	double 	fRec1[2];
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
	FAUSTFLOAT 	fslider2;
	double 	fRec3[2];
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
	FAUSTFLOAT 	fslider3;
	double 	fRec4[6];
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
	fConst0 = double(min(1.92e+05, max(1.0, (double)fSamplingFreq)));
	fConst1 = (1.11390635159433e-24 * fConst0);
	fConst2 = ((fConst0 * ((fConst0 * (3.18702063081927e-22 + fConst1)) - 7.14108820102165e-34)) - 1.80540050182853e-48);
	fConst3 = (7.72208706599171e-24 * fConst0);
	fConst4 = (7.605464376339e-34 + (fConst0 * ((fConst0 * (0 - (6.05969681445433e-22 + fConst3))) - 3.39044747958769e-22)));
	fConst5 = (9.07610804066639e-25 * fConst0);
	fConst6 = ((fConst0 * ((fConst0 * (0 - (3.13971543026984e-22 + fConst5))) - 1.80077239576117e-20)) - 1.69522373979748e-20);
	fConst7 = (5.49427436280305e-24 * fConst0);
	fConst8 = ((fConst0 * (3.39044747960198e-22 + (fConst0 * (fConst7 - 3.14344447184204e-23)))) - 7.60546437633897e-34);
	fConst9 = (1.11582073532266e-24 * fConst0);
	fConst10 = (3.39044747959503e-20 + (fConst0 * (8.5311710434333e-22 + (fConst0 * (3.23543557700559e-22 + fConst9)))));
	fConst11 = (2.23797473617709e-24 * fConst0);
	fConst12 = (6.97469477751319e-35 + (fConst0 * (1.74198245202729e-20 + (fConst0 * (1.74849041434644e-22 - fConst11)))));
	fConst13 = (3.22318393238815e-24 * fConst0);
	fConst14 = (9.66029729825488e-17 + (fConst0 * (5.44196016387214e-19 + (fConst0 * (2.32489770791907e-21 + fConst13)))));
	fConst15 = (6.72581680534004e-24 * fConst0);
	fConst16 = (4.51350125457133e-43 + (fConst0 * (1.78867236680673e-28 + (fConst0 * ((fConst0 * ((fConst0 * (0 - (4.41586600140972e-21 + fConst15))) - 7.47371530788388e-19)) - 9.57970935359556e-17)))));
	fConst17 = (7.09491773348213e-24 * fConst0);
	fConst18 = ((fConst0 * (8.47611869896916e-17 + (fConst0 * (1.677855547693e-16 + (fConst0 * (2.55872993315156e-18 + (fConst0 * (8.1036807179337e-21 + fConst17)))))))) - 1.90136609408475e-28);
	fConst19 = (6.58813040006868e-24 * fConst0);
	fConst20 = (7.07969084128568e-37 + (fConst0 * (fConst19 - 2.80345974471016e-22)));
	fConst21 = (6.88899571441955e-24 * fConst0);
	fConst22 = ((fConst0 * (2.95929420463955e-22 - fConst21)) - 1.1408541599688e-23);
	fConst23 = ((fConst0 * (2.80345974471016e-22 - fConst19)) - 7.07969084128568e-37);
	fConst24 = (1.91438372832372e-27 * fConst0);
	fConst25 = (2.28170831993645e-23 + (fConst0 * (0 - (9.28894735127254e-24 + fConst24))));
	fConst26 = (1.0025039931634e-23 * fConst0);
	fConst27 = (6.08366393926321e-36 + (fConst0 * (fConst26 - 4.24692905313867e-22)));
	fConst28 = (3.8335982187148e-25 * fConst0);
	fConst29 = ((fConst0 * (1.95786469833648e-18 + (fConst0 * (fConst28 - 5.42251622369686e-21)))) - 7.39993880685971e-17);
	fConst30 = (2.08000946656956e-27 * fConst0);
	fConst31 = (3.53984542064284e-34 + (fConst0 * ((fConst0 * (3.29838842203039e-21 + fConst30)) - 1.40184395777108e-19)));
	fConst32 = (3.70058120006252e-25 * fConst0);
	fConst33 = (7.0086493617754e-17 + (fConst0 * ((fConst0 * (3.84955928653808e-22 - fConst32)) - 1.66273197458755e-18)));
	fConst34 = ((fConst0 * (7.14108820102165e-34 + (fConst0 * (3.18702063081927e-22 - fConst1)))) - 1.80540050182853e-48);
	fConst35 = (7.605464376339e-34 + (fConst0 * (3.39044747958769e-22 + (fConst0 * (fConst3 - 6.05969681445433e-22)))));
	fConst36 = ((fConst0 * (1.80077239576117e-20 + (fConst0 * (fConst5 - 3.13971543026984e-22)))) - 1.69522373979748e-20);
	fConst37 = ((fConst0 * ((fConst0 * (0 - (3.14344447184204e-23 + fConst7))) - 3.39044747960198e-22)) - 7.60546437633897e-34);
	fConst38 = (3.39044747959503e-20 + (fConst0 * ((fConst0 * (3.23543557700559e-22 - fConst9)) - 8.5311710434333e-22)));
	fConst39 = (6.97469477751319e-35 + (fConst0 * ((fConst0 * (1.74849041434644e-22 + fConst11)) - 1.74198245202729e-20)));
	fConst40 = (9.66029729825488e-17 + (fConst0 * ((fConst0 * (2.32489770791907e-21 - fConst13)) - 5.44196016387214e-19)));
	fConst41 = (4.51350125457133e-43 + (fConst0 * ((fConst0 * ((fConst0 * (7.47371530788388e-19 + (fConst0 * (fConst15 - 4.41586600140972e-21)))) - 9.57970935359556e-17)) - 1.78867236680673e-28)));
	fConst42 = ((fConst0 * ((fConst0 * (1.677855547693e-16 + (fConst0 * ((fConst0 * (8.1036807179337e-21 - fConst17)) - 2.55872993315156e-18)))) - 8.47611869896916e-17)) - 1.90136609408475e-28);
	fConst43 = (5.56953175797167e-24 * fConst0);
	fConst44 = ((fConst0 * ((fConst0 * (fConst43 - 9.5610618924578e-22)) - 7.14108820102165e-34)) - 1.80540050182853e-48);
	fConst45 = (3.86104353299586e-23 * fConst0);
	fConst46 = (7.605464376339e-34 + (fConst0 * ((fConst0 * (1.8179090443363e-21 - fConst45)) - 3.39044747958769e-22)));
	fConst47 = (4.53805402033319e-24 * fConst0);
	fConst48 = ((fConst0 * ((fConst0 * (9.41914629080951e-22 - fConst47)) - 1.80077239576117e-20)) - 1.69522373979748e-20);
	fConst49 = (2.74713718140152e-23 * fConst0);
	fConst50 = ((fConst0 * (3.39044747960198e-22 + (fConst0 * (9.43033341552612e-23 + fConst49)))) - 7.60546437633897e-34);
	fConst51 = (5.57910367661329e-24 * fConst0);
	fConst52 = (3.39044747959503e-20 + (fConst0 * (8.5311710434333e-22 + (fConst0 * (fConst51 - 9.70630673101678e-22)))));
	fConst53 = (1.11898736808855e-23 * fConst0);
	fConst54 = (6.97469477751319e-35 + (fConst0 * (1.74198245202729e-20 + (fConst0 * (0 - (5.24547124303932e-22 + fConst53))))));
	fConst55 = (1.61159196619408e-23 * fConst0);
	fConst56 = (9.66029729825488e-17 + (fConst0 * (5.44196016387214e-19 + (fConst0 * (fConst55 - 6.9746931237572e-21)))));
	fConst57 = (3.36290840267002e-23 * fConst0);
	fConst58 = (2.25675062728566e-42 + (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (1.32475980042292e-20 - fConst57)) - 7.47371530788388e-19)) - 9.57970935359556e-17)) - 5.3660171004202e-28)));
	fConst59 = (3.54745886674106e-23 * fConst0);
	fConst60 = ((fConst0 * ((fConst0 * (1.677855547693e-16 + (fConst0 * (2.55872993315156e-18 + (fConst0 * (fConst59 - 2.43110421538011e-20)))))) - 2.54283560969075e-16)) - 9.50683047042375e-28);
	fConst61 = (1.11390635159433e-23 * fConst0);
	fConst62 = (3.61080100365706e-48 + (fConst0 * ((fConst0 * (6.37404126163853e-22 - fConst61)) - 1.42821764020433e-33)));
	fConst63 = (7.72208706599171e-23 * fConst0);
	fConst64 = ((fConst0 * ((fConst0 * (fConst63 - 1.21193936289087e-21)) - 6.78089495917539e-22)) - 1.5210928752678e-33);
	fConst65 = (9.07610804066639e-24 * fConst0);
	fConst66 = (3.39044747959497e-20 + (fConst0 * ((fConst0 * (fConst65 - 6.27943086053967e-22)) - 3.60154479152234e-20)));
	fConst67 = (5.49427436280305e-23 * fConst0);
	fConst68 = (1.52109287526779e-33 + (fConst0 * (6.78089495920395e-22 + (fConst0 * (0 - (6.28688894368408e-23 + fConst67))))));
	fConst69 = (1.11582073532266e-23 * fConst0);
	fConst70 = ((fConst0 * (1.70623420868666e-21 + (fConst0 * (6.47087115401119e-22 - fConst69)))) - 6.78089495919005e-20);
	fConst71 = (2.23797473617709e-23 * fConst0);
	fConst72 = ((fConst0 * (3.48396490405458e-20 + (fConst0 * (3.49698082869288e-22 + fConst71)))) - 1.39493895550264e-34);
	fConst73 = (3.22318393238815e-23 * fConst0);
	fConst74 = ((fConst0 * (1.08839203277443e-18 + (fConst0 * (4.64979541583813e-21 - fConst73)))) - 1.93205945965098e-16);
	fConst75 = (6.72581680534004e-23 * fConst0);
	fConst76 = (4.51350125457133e-42 + (fConst0 * ((fConst0 * (1.91594187071911e-16 + (fConst0 * ((fConst0 * (fConst75 - 8.83173200281944e-21)) - 1.49474306157678e-18)))) - 3.57734473361347e-28)));
	fConst77 = (7.09491773348213e-23 * fConst0);
	fConst78 = ((fConst0 * ((fConst0 * ((fConst0 * (5.11745986630311e-18 + (fConst0 * (1.62073614358674e-20 - fConst77)))) - 3.35571109538599e-16)) - 1.69522373979383e-16)) - 1.90136609408475e-27);
	fConst79 = (3.61080100365706e-48 + (fConst0 * (1.42821764020433e-33 + (fConst0 * (6.37404126163853e-22 + fConst61)))));
	fConst80 = ((fConst0 * (6.78089495917539e-22 + (fConst0 * (0 - (1.21193936289087e-21 + fConst63))))) - 1.5210928752678e-33);
	fConst81 = (3.39044747959497e-20 + (fConst0 * (3.60154479152234e-20 + (fConst0 * (0 - (6.27943086053967e-22 + fConst65))))));
	fConst82 = (1.52109287526779e-33 + (fConst0 * ((fConst0 * (fConst67 - 6.28688894368408e-23)) - 6.78089495920395e-22)));
	fConst83 = ((fConst0 * ((fConst0 * (6.47087115401119e-22 + fConst69)) - 1.70623420868666e-21)) - 6.78089495919005e-20);
	fConst84 = ((fConst0 * ((fConst0 * (3.49698082869288e-22 - fConst71)) - 3.48396490405458e-20)) - 1.39493895550264e-34);
	fConst85 = ((fConst0 * ((fConst0 * (4.64979541583813e-21 + fConst73)) - 1.08839203277443e-18)) - 1.93205945965098e-16);
	fConst86 = (4.51350125457133e-42 + (fConst0 * (3.57734473361347e-28 + (fConst0 * (1.91594187071911e-16 + (fConst0 * (1.49474306157678e-18 + (fConst0 * (0 - (8.83173200281944e-21 + fConst75))))))))));
	fConst87 = ((fConst0 * (1.69522373979383e-16 + (fConst0 * ((fConst0 * ((fConst0 * (1.62073614358674e-20 + fConst77)) - 5.11745986630311e-18)) - 3.35571109538599e-16)))) - 1.90136609408475e-27);
	fConst88 = ((fConst0 * (7.14108820102165e-34 + (fConst0 * (0 - (9.5610618924578e-22 + fConst43))))) - 1.80540050182853e-48);
	fConst89 = (7.605464376339e-34 + (fConst0 * (3.39044747958769e-22 + (fConst0 * (1.8179090443363e-21 + fConst45)))));
	fConst90 = ((fConst0 * (1.80077239576117e-20 + (fConst0 * (9.41914629080951e-22 + fConst47)))) - 1.69522373979748e-20);
	fConst91 = ((fConst0 * ((fConst0 * (9.43033341552612e-23 - fConst49)) - 3.39044747960198e-22)) - 7.60546437633897e-34);
	fConst92 = (3.39044747959503e-20 + (fConst0 * ((fConst0 * (0 - (9.70630673101678e-22 + fConst51))) - 8.5311710434333e-22)));
	fConst93 = (6.97469477751319e-35 + (fConst0 * ((fConst0 * (fConst53 - 5.24547124303932e-22)) - 1.74198245202729e-20)));
	fConst94 = (9.66029729825488e-17 + (fConst0 * ((fConst0 * (0 - (6.9746931237572e-21 + fConst55))) - 5.44196016387214e-19)));
	fConst95 = (2.25675062728566e-42 + (fConst0 * (5.3660171004202e-28 + (fConst0 * ((fConst0 * (7.47371530788388e-19 + (fConst0 * (1.32475980042292e-20 + fConst57)))) - 9.57970935359556e-17)))));
	fConst96 = ((fConst0 * (2.54283560969075e-16 + (fConst0 * (1.677855547693e-16 + (fConst0 * ((fConst0 * (0 - (2.43110421538011e-20 + fConst59))) - 2.55872993315156e-18)))))) - 9.50683047042375e-28);
	fConst97 = (2.40788246727257e-24 * fConst0);
	fConst98 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (0 - (1.83337089189981e-19 + fConst97))) - 1.0884037880131e-17)) - 2.17663092851014e-16)) - 5.23377299648722e-16)) - 4.66166061483529e-29);
	fConst99 = (2.78713041660513e-24 * fConst0);
	fConst100 = (1.16306066588601e-15 + (fConst0 * (1.42685467015479e-15 + (fConst0 * (3.13137866048362e-16 + (fConst0 * (1.25272695161612e-17 + (fConst0 * (2.03907877623046e-19 + fConst99)))))))));
	fConst101 = (3.97647190322603e-27 * fConst0);
	fConst102 = (2.63401345836477e-31 + (fConst0 * ((fConst0 * (2.12282875792926e-17 + (fConst0 * (0 - (4.95880631786145e-19 + fConst101))))) - 2.95727845714664e-18)));
	fConst103 = (7.42702058644117e-27 * fConst0);
	fConst104 = ((fConst0 * (5.04598373508118e-17 + (fConst0 * ((fConst0 * (7.89889133199585e-19 + fConst103)) - 3.48875412150739e-17)))) - 6.57172990476634e-18);
	fConst105 = ((fConst0 * (5.23377299648722e-16 + (fConst0 * ((fConst0 * (1.0884037880131e-17 + (fConst0 * (fConst97 - 1.83337089189981e-19)))) - 2.17663092851014e-16)))) - 4.66166061483529e-29);
	fConst106 = (1.16306066588601e-15 + (fConst0 * ((fConst0 * (3.13137866048362e-16 + (fConst0 * ((fConst0 * (2.03907877623046e-19 - fConst99)) - 1.25272695161612e-17)))) - 1.42685467015479e-15)));
	fConst107 = (1.20394123363628e-23 * fConst0);
	fConst108 = ((fConst0 * (1.57013189894617e-15 + (fConst0 * ((fConst0 * ((fConst0 * (5.50011267569942e-19 - fConst107)) - 1.0884037880131e-17)) - 2.17663092851014e-16)))) - 2.33083030741764e-28);
	fConst109 = (1.39356520830257e-23 * fConst0);
	fConst110 = (5.81530332943008e-15 + (fConst0 * ((fConst0 * (3.13137866048362e-16 + (fConst0 * (1.25272695161612e-17 + (fConst0 * (fConst109 - 6.11723632869138e-19)))))) - 4.28056401046438e-15)));
	fConst111 = (2.40788246727257e-23 * fConst0);
	fConst112 = ((fConst0 * (1.04675459929744e-15 + (fConst0 * (4.35326185702027e-16 + (fConst0 * ((fConst0 * (fConst111 - 3.66674178379961e-19)) - 2.17680757602621e-17)))))) - 4.66166061483529e-28);
	fConst113 = (2.78713041660513e-23 * fConst0);
	fConst114 = (1.16306066588602e-14 + (fConst0 * ((fConst0 * ((fConst0 * (2.50545390323223e-17 + (fConst0 * (4.07815755246092e-19 - fConst113)))) - 6.26275732096724e-16)) - 2.85370934030959e-15)));
	fConst115 = ((fConst0 * ((fConst0 * (4.35326185702027e-16 + (fConst0 * (2.17680757602621e-17 + (fConst0 * (0 - (3.66674178379961e-19 + fConst111))))))) - 1.04675459929744e-15)) - 4.66166061483529e-28);
	fConst116 = (1.16306066588602e-14 + (fConst0 * (2.85370934030959e-15 + (fConst0 * ((fConst0 * ((fConst0 * (4.07815755246092e-19 + fConst113)) - 2.50545390323223e-17)) - 6.26275732096724e-16)))));
	fConst117 = ((fConst0 * ((fConst0 * ((fConst0 * (1.0884037880131e-17 + (fConst0 * (5.50011267569942e-19 + fConst107)))) - 2.17663092851014e-16)) - 1.57013189894617e-15)) - 2.33083030741764e-28);
	fConst118 = (5.81530332943008e-15 + (fConst0 * (4.28056401046438e-15 + (fConst0 * (3.13137866048362e-16 + (fConst0 * ((fConst0 * (0 - (6.11723632869138e-19 + fConst109))) - 1.25272695161612e-17)))))));
	fConst119 = (1.98823595161302e-26 * fConst0);
	fConst120 = (7.9020403750943e-31 + (fConst0 * ((fConst0 * ((fConst0 * (1.48764189535843e-18 + fConst119)) - 2.12282875792926e-17)) - 2.95727845714664e-18)));
	fConst121 = (3.71351029322059e-26 * fConst0);
	fConst122 = ((fConst0 * (5.04598373508118e-17 + (fConst0 * (3.48875412150739e-17 + (fConst0 * (0 - (2.36966739959876e-18 + fConst121))))))) - 1.9715189714299e-17);
	fConst123 = (3.97647190322603e-26 * fConst0);
	fConst124 = (5.26802691672954e-31 + (fConst0 * (5.91455691429328e-18 + (fConst0 * ((fConst0 * (0 - (9.91761263572289e-19 + fConst123))) - 4.24565751585853e-17)))));
	fConst125 = (7.42702058644117e-26 * fConst0);
	fConst126 = ((fConst0 * ((fConst0 * (6.97750824301479e-17 + (fConst0 * (1.57977826639917e-18 + fConst125)))) - 1.00919674701624e-16)) - 1.31434598095327e-17);
	fConst127 = ((fConst0 * (5.91455691429328e-18 + (fConst0 * (4.24565751585853e-17 + (fConst0 * (fConst123 - 9.91761263572289e-19)))))) - 5.26802691672954e-31);
	fConst128 = (1.31434598095327e-17 + (fConst0 * ((fConst0 * ((fConst0 * (1.57977826639917e-18 - fConst125)) - 6.97750824301479e-17)) - 1.00919674701624e-16)));
	fConst129 = ((fConst0 * ((fConst0 * (2.12282875792926e-17 + (fConst0 * (1.48764189535843e-18 - fConst119)))) - 2.95727845714664e-18)) - 7.9020403750943e-31);
	fConst130 = (1.9715189714299e-17 + (fConst0 * (5.04598373508118e-17 + (fConst0 * ((fConst0 * (fConst121 - 2.36966739959876e-18)) - 3.48875412150739e-17)))));
	fConst131 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst101 - 4.95880631786145e-19)) - 2.12282875792926e-17)) - 2.95727845714664e-18)) - 2.63401345836477e-31);
	fConst132 = (6.57172990476634e-18 + (fConst0 * (5.04598373508118e-17 + (fConst0 * (3.48875412150739e-17 + (fConst0 * (7.89889133199585e-19 - fConst103)))))));
	fConst133 = faustpower<2>(fConst0);
	fConst134 = (3.29406520003434e-23 * fConst0);
	fConst135 = ((fConst0 * (8.41037923413049e-22 - fConst134)) - 7.07969084128568e-37);
	fConst136 = (3.44449785720978e-23 * fConst0);
	fConst137 = (1.1408541599688e-23 + (fConst0 * (fConst136 - 8.87788261391865e-22)));
	fConst138 = (7.07969084128568e-37 + (fConst0 * (fConst134 - 8.41037923413049e-22)));
	fConst139 = (9.57191864161859e-27 * fConst0);
	fConst140 = ((fConst0 * (2.78668420538176e-23 + fConst139)) - 2.28170831993645e-23);
	fConst141 = (5.012519965817e-23 * fConst0);
	fConst142 = ((fConst0 * (1.2740787159416e-21 - fConst141)) - 6.08366393926321e-36);
	fConst143 = (1.9167991093574e-24 * fConst0);
	fConst144 = ((fConst0 * ((fConst0 * (1.62675486710906e-20 - fConst143)) - 1.95786469833648e-18)) - 7.39993880685971e-17);
	fConst145 = (1.04000473328478e-26 * fConst0);
	fConst146 = (3.53984542064284e-34 + (fConst0 * (1.40184395777108e-19 + (fConst0 * (0 - (9.89516526609117e-21 + fConst145))))));
	fConst147 = (1.85029060003126e-24 * fConst0);
	fConst148 = (7.0086493617754e-17 + (fConst0 * (1.66273197458755e-18 + (fConst0 * (fConst147 - 1.15486778596142e-21)))));
	fConst149 = (6.58813040006868e-23 * fConst0);
	fConst150 = ((fConst0 * (fConst149 - 5.60691948942032e-22)) - 1.41593816825714e-36);
	fConst151 = (6.88899571441955e-23 * fConst0);
	fConst152 = (2.28170831993761e-23 + (fConst0 * (5.9185884092791e-22 - fConst151)));
	fConst153 = (1.41593816825714e-36 + (fConst0 * (5.60691948942032e-22 - fConst149)));
	fConst154 = (1.91438372832372e-26 * fConst0);
	fConst155 = ((fConst0 * (0 - (1.85778947025451e-23 + fConst154))) - 4.56341663987291e-23);
	fConst156 = (1.0025039931634e-22 * fConst0);
	fConst157 = ((fConst0 * (fConst156 - 8.49385810627733e-22)) - 1.21673278785264e-35);
	fConst158 = (3.8335982187148e-24 * fConst0);
	fConst159 = (1.47998776137194e-16 + (fConst0 * ((fConst0 * (fConst158 - 1.08450324473937e-20)) - 3.91572939667295e-18)));
	fConst160 = (2.08000946656956e-26 * fConst0);
	fConst161 = ((fConst0 * (2.80368791554216e-19 + (fConst0 * (6.59677684406078e-21 + fConst160)))) - 7.07969084128568e-34);
	fConst162 = (3.70058120006252e-24 * fConst0);
	fConst163 = ((fConst0 * (3.32546394917509e-18 + (fConst0 * (7.69911857307616e-22 - fConst162)))) - 1.40172987235508e-16);
	fConst164 = (5.60691948942032e-22 + fConst149);
	fConst165 = (1.41593816825714e-36 + (fConst0 * (0 - fConst164)));
	fConst166 = ((fConst0 * (5.9185884092791e-22 + fConst151)) - 2.28170831993761e-23);
	fConst167 = ((fConst0 * fConst164) - 1.41593816825714e-36);
	fConst168 = (4.56341663987291e-23 + (fConst0 * (fConst154 - 1.85778947025451e-23)));
	fConst169 = (1.21673278785264e-35 + (fConst0 * (0 - (8.49385810627733e-22 + fConst156))));
	fConst170 = (1.47998776137194e-16 + (fConst0 * (3.91572939667295e-18 + (fConst0 * (0 - (1.08450324473937e-20 + fConst158))))));
	fConst171 = ((fConst0 * ((fConst0 * (6.59677684406078e-21 - fConst160)) - 2.80368791554216e-19)) - 7.07969084128568e-34);
	fConst172 = ((fConst0 * ((fConst0 * (7.69911857307616e-22 + fConst162)) - 3.32546394917509e-18)) - 1.40172987235508e-16);
	fConst173 = (8.41037923413049e-22 + fConst134);
	fConst174 = (7.07969084128568e-37 + (fConst0 * fConst173));
	fConst175 = ((fConst0 * (0 - (8.87788261391865e-22 + fConst136))) - 1.1408541599688e-23);
	fConst176 = ((fConst0 * (0 - fConst173)) - 7.07969084128568e-37);
	fConst177 = (2.28170831993645e-23 + (fConst0 * (2.78668420538176e-23 - fConst139)));
	fConst178 = (6.08366393926321e-36 + (fConst0 * (1.2740787159416e-21 + fConst141)));
	fConst179 = ((fConst0 * (1.95786469833648e-18 + (fConst0 * (1.62675486710906e-20 + fConst143)))) - 7.39993880685971e-17);
	fConst180 = (3.53984542064284e-34 + (fConst0 * ((fConst0 * (fConst145 - 9.89516526609117e-21)) - 1.40184395777108e-19)));
	fConst181 = (7.0086493617754e-17 + (fConst0 * ((fConst0 * (0 - (1.15486778596142e-21 + fConst147))) - 1.66273197458755e-18)));
	fConst182 = (2.80345974471016e-22 + fConst19);
	fConst183 = ((fConst0 * (0 - fConst182)) - 7.07969084128568e-37);
	fConst184 = (1.1408541599688e-23 + (fConst0 * (2.95929420463955e-22 + fConst21)));
	fConst185 = (7.07969084128568e-37 + (fConst0 * fConst182));
	fConst186 = ((fConst0 * (fConst24 - 9.28894735127254e-24)) - 2.28170831993645e-23);
	fConst187 = ((fConst0 * (0 - (4.24692905313867e-22 + fConst26))) - 6.08366393926321e-36);
	fConst188 = ((fConst0 * ((fConst0 * (0 - (5.42251622369686e-21 + fConst28))) - 1.95786469833648e-18)) - 7.39993880685971e-17);
	fConst189 = (3.53984542064284e-34 + (fConst0 * (1.40184395777108e-19 + (fConst0 * (3.29838842203039e-21 - fConst30)))));
	fConst190 = (7.0086493617754e-17 + (fConst0 * (1.66273197458755e-18 + (fConst0 * (3.84955928653808e-22 + fConst32)))));
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
		fRec0[0] = (fSlow0 + (0.993 * fRec0[1]));
		fRec1[0] = (fSlow1 + (0.993 * fRec1[1]));
		double fTemp0 = (4.23805934949371e-15 + ((fRec0[0] * (fConst18 + (fConst16 * fRec0[0]))) + (fConst0 * (4.5272406798381e-15 + (fConst0 * (fConst14 + (fRec1[0] * (fConst12 + ((fRec0[0] * (fConst10 + (fConst8 * fRec0[0]))) + (fRec1[0] * (fConst6 + (fRec0[0] * (fConst4 + (fConst2 * fRec0[0]))))))))))))));
		fRec3[0] = (fSlow2 + (0.993 * fRec3[1]));
		double fTemp1 = (fConst100 + (fConst98 * fRec3[0]));
		double fTemp2 = (double)input0[i];
		fRec4[0] = ((fSlow3 * fTemp2) - ((((((fRec4[1] * (fConst118 + (fConst117 * fRec3[0]))) + (fRec4[2] * (fConst116 + (fConst115 * fRec3[0])))) + (fRec4[3] * (fConst114 + (fConst112 * fRec3[0])))) + (fRec4[4] * (fConst110 + (fConst108 * fRec3[0])))) + (fRec4[5] * (fConst106 + (fConst105 * fRec3[0])))) / fTemp1));
		double fTemp3 = ((((((fRec4[0] * (fConst132 + (fConst131 * fRec3[0]))) + (fRec4[1] * (fConst130 + (fConst129 * fRec3[0])))) + (fRec4[2] * (fConst128 + (fConst127 * fRec3[0])))) + (fRec4[3] * (fConst126 + (fConst124 * fRec3[0])))) + (fRec4[4] * (fConst122 + (fConst120 * fRec3[0])))) + (fRec4[5] * (fConst104 + (fConst102 * fRec3[0]))));
		double fTemp4 = fabs((fConst0 * (fTemp3 / fTemp1)));
		fRec2[0] = ((fConst0 * (((fRec3[0] * fTemp3) * (0.5 + fTemp4)) / (fTemp1 * ((1 + (fConst133 * (faustpower<2>(fTemp3) / faustpower<2>(fTemp1)))) - (0.5 * fTemp4))))) - ((((((fRec2[1] * (2.11902967474685e-14 + ((fRec0[0] * (fConst96 + (fConst95 * fRec0[0]))) + (fConst0 * (1.35817220395143e-14 + (fConst0 * (fConst94 + (fRec1[0] * (fConst93 + ((fRec0[0] * (fConst92 + (fConst91 * fRec0[0]))) + (fRec1[0] * (fConst90 + (fRec0[0] * (fConst89 + (fConst88 * fRec0[0]))))))))))))))) + (fRec2[2] * (4.23805934949371e-14 + ((fRec0[0] * (fConst87 + (fConst86 * fRec0[0]))) + (fConst0 * (9.05448135967619e-15 + (fConst0 * (fConst85 + (fRec1[0] * (fConst84 + ((fRec0[0] * (fConst83 + (fConst82 * fRec0[0]))) + (fRec1[0] * (fConst81 + (fRec0[0] * (fConst80 + (fConst79 * fRec0[0])))))))))))))))) + (fRec2[3] * (4.23805934949371e-14 + ((fRec0[0] * (fConst78 + (fConst76 * fRec0[0]))) + (fConst0 * ((fConst0 * (fConst74 + (fRec1[0] * (fConst72 + ((fRec0[0] * (fConst70 + (fConst68 * fRec0[0]))) + (fRec1[0] * (fConst66 + (fRec0[0] * (fConst64 + (fConst62 * fRec0[0])))))))))) - 9.05448135967619e-15)))))) + (fRec2[4] * (2.11902967474685e-14 + ((fRec0[0] * (fConst60 + (fConst58 * fRec0[0]))) + (fConst0 * ((fConst0 * (fConst56 + (fRec1[0] * (fConst54 + ((fRec0[0] * (fConst52 + (fConst50 * fRec0[0]))) + (fRec1[0] * (fConst48 + (fRec0[0] * (fConst46 + (fConst44 * fRec0[0])))))))))) - 1.35817220395143e-14)))))) + (fRec2[5] * (4.23805934949371e-15 + ((fRec0[0] * (fConst42 + (fConst41 * fRec0[0]))) + (fConst0 * ((fConst0 * (fConst40 + (fRec1[0] * (fConst39 + ((fRec0[0] * (fConst38 + (fConst37 * fRec0[0]))) + (fRec1[0] * (fConst36 + (fRec0[0] * (fConst35 + (fConst34 * fRec0[0])))))))))) - 4.5272406798381e-15)))))) / fTemp0));
		output0[i] = (FAUSTFLOAT)((fSlow4 * fTemp2) + (fConst0 * (((((((fRec2[0] * (((fRec0[0] * (1.76992271032142e-31 + (fConst0 * (fConst190 + (fConst189 * fRec0[0]))))) + (fConst0 * (fConst188 + (fConst0 * (fRec1[0] * (fConst187 + ((fRec0[0] * (fConst186 + (fConst185 * fRec0[0]))) + (fRec1[0] * (fConst184 + (fConst183 * fRec0[0])))))))))) - 2.85213539992201e-18)) + (fRec2[1] * (((fRec0[0] * (5.30976813096426e-31 + (fConst0 * (fConst181 + (fConst180 * fRec0[0]))))) + (fConst0 * (fConst179 + (fConst0 * (fRec1[0] * (fConst178 + ((fRec0[0] * (fConst177 + (fConst176 * fRec0[0]))) + (fRec1[0] * (fConst175 + (fConst174 * fRec0[0])))))))))) - 8.55640619976602e-18))) + (fRec2[2] * (((fRec0[0] * (3.53984542064284e-31 + (fConst0 * (fConst172 + (fConst171 * fRec0[0]))))) + (fConst0 * (fConst170 + (fConst0 * (fRec1[0] * (fConst169 + ((fRec0[0] * (fConst168 + (fConst167 * fRec0[0]))) + (fRec1[0] * (fConst166 + (fConst165 * fRec0[0])))))))))) - 5.70427079984401e-18))) + (fRec2[3] * (5.70427079984401e-18 + ((fRec0[0] * ((fConst0 * (fConst163 + (fConst161 * fRec0[0]))) - 3.53984542064284e-31)) + (fConst0 * (fConst159 + (fConst0 * (fRec1[0] * (fConst157 + ((fRec0[0] * (fConst155 + (fConst153 * fRec0[0]))) + (fRec1[0] * (fConst152 + (fConst150 * fRec0[0]))))))))))))) + (fRec2[4] * (8.55640619976602e-18 + ((fRec0[0] * ((fConst0 * (fConst148 + (fConst146 * fRec0[0]))) - 5.30976813096426e-31)) + (fConst0 * (fConst144 + (fConst0 * (fRec1[0] * (fConst142 + ((fRec0[0] * (fConst140 + (fConst138 * fRec0[0]))) + (fRec1[0] * (fConst137 + (fConst135 * fRec0[0]))))))))))))) + (fRec2[5] * (2.85213539992201e-18 + ((fRec0[0] * ((fConst0 * (fConst33 + (fConst31 * fRec0[0]))) - 1.76992271032142e-31)) + (fConst0 * (fConst29 + (fConst0 * (fRec1[0] * (fConst27 + ((fRec0[0] * (fConst25 + (fConst23 * fRec0[0]))) + (fRec1[0] * (fConst22 + (fConst20 * fRec0[0]))))))))))))) / fTemp0)));
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
