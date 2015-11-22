// generated from file '../src/plugins/cstb.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"
#include "trany.h"

namespace pluginlib {
namespace cstb {

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
	double 	fConst17;
	double 	fConst18;
	double 	fConst19;
	double 	fConst20;
	FAUSTFLOAT 	fslider2;
	double 	fRec9[2];
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
	double 	fRec11[6];
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
	double 	fConst191;
	double 	fConst192;
	double 	fConst193;
	double 	fConst194;
	double 	fConst195;
	double 	fVec0[2];
	double 	fConst196;
	double 	fConst197;
	double 	fConst198;
	double 	fRec7[2];
	double 	fRec6[3];
	double 	fConst199;
	double 	fConst200;
	double 	fConst201;
	double 	fConst202;
	double 	fRec12[2];
	double 	fRec5[3];
	double 	fConst203;
	double 	fConst204;
	double 	fConst205;
	double 	fConst206;
	double 	fConst207;
	double 	fRec4[2];
	double 	fConst208;
	double 	fRec3[2];
	double 	fRec2[3];
	double 	fRec13[2];
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
	id = "cstbt1";
	name = N_("Colorsound Tone Blender");
	groups = 0;
	description = N_("Colorsound Tone Blender"); // description (tooltip)
	category = N_("Fuzz");       // category
	shortname = N_("CS Toneblender");     // shortname
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
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
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
	fConst7 = (7.8746133025304e-22 * fConst6);
	fConst8 = (1.19374357533685e-13 + (fConst6 * (5.81722106266131e-15 + (fConst6 * (1.20886112608973e-17 + fConst7)))));
	fConst9 = (7.2677502129384e-24 * fConst6);
	fConst10 = ((fConst6 * ((fConst6 * ((fConst6 * (0 - (1.11622970892275e-19 + fConst9))) - 5.44781387848185e-17)) - 1.11859678983445e-15)) - 2.16342879110166e-15);
	fConst11 = (7.40213650437857e-24 * fConst6);
	fConst12 = (2.17010750008645e-15 + (fConst6 * (1.12211896081664e-15 + (fConst6 * (5.46818779890163e-17 + (fConst6 * (1.13632945852435e-19 + fConst11)))))));
	fConst13 = (1.8420467174625e-21 * fConst6);
	fConst14 = (2.69059416486104e-13 + (fConst6 * (1.22792404260186e-14 + (fConst6 * (2.55273478792579e-17 + fConst13)))));
	fConst15 = (1.72098866161537e-23 * fConst6);
	fConst16 = (2.45620889089652e-16 + (fConst6 * (1.14222007971933e-16 + (fConst6 * (2.43964228204556e-19 + fConst15)))));
	fConst17 = (1.75281106567011e-23 * fConst6);
	fConst18 = ((fConst6 * ((fConst6 * (0 - (2.48347397038037e-19 + fConst17))) - 1.14582451009122e-16)) - 2.46379143969851e-16);
	fConst19 = (1.86469262305331e-21 * fConst6);
	fConst20 = ((fConst6 * ((fConst6 * (0 - (2.64199358551104e-17 + fConst19))) - 1.21896224477789e-14)) - 2.62105472308353e-14);
	fConst21 = (1.70008798003816e-23 * fConst6);
	fConst22 = ((fConst6 * ((fConst6 * ((fConst6 * (0 - (2.35724702889288e-19 + fConst21))) - 1.14989728218871e-16)) - 2.52121869652107e-15)) - 4.91241778179305e-15);
	fConst23 = (1.73152391441475e-23 * fConst6);
	fConst24 = (4.92758287939703e-15 + (fConst6 * (2.52915851496938e-15 + (fConst6 * (1.15424860004575e-16 + (fConst6 * (2.39957070065024e-19 + fConst23)))))));
	fConst25 = (9.67524227740541e-23 * fConst6);
	fConst26 = (1.52102059347953e-20 - fConst25);
	fConst27 = (9.67524227740542e-20 * fConst6);
	fConst28 = (1.52102059347953e-17 - fConst27);
	fConst29 = (9.09472774076109e-22 * fConst6);
	fConst30 = (fConst29 - 1.42975935787076e-19);
	fConst31 = (9.05450478550043e-24 * fConst6);
	fConst32 = (1.42343600786794e-21 - fConst31);
	fConst33 = (9.05450478550042e-27 * fConst6);
	fConst34 = (1.42343600786794e-24 - fConst33);
	fConst35 = (9.09472774076109e-25 * fConst6);
	fConst36 = (fConst35 - 1.42975935787076e-22);
	fConst37 = (8.18152886468203e-23 * fConst6);
	fConst38 = (3.32042567560148e-19 + fConst37);
	fConst39 = (8.18152886468203e-20 * fConst6);
	fConst40 = (3.32042567560148e-16 + fConst39);
	fConst41 = (7.69063713280111e-25 * fConst6);
	fConst42 = (0 - (3.1212001350654e-21 + fConst41));
	fConst43 = (7.69063713280111e-22 * fConst6);
	fConst44 = (0 - (3.12120013506539e-18 + fConst43));
	fConst45 = (7.65662400320161e-24 * fConst6);
	fConst46 = (3.10739610519547e-20 + fConst45);
	fConst47 = (7.65662400320161e-27 * fConst6);
	fConst48 = (3.10739610519547e-23 + fConst47);
	fConst49 = ((fConst6 * (5.81722106266131e-15 + (fConst6 * (fConst7 - 1.20886112608973e-17)))) - 1.19374357533685e-13);
	fConst50 = (2.16342879110166e-15 + (fConst6 * ((fConst6 * (5.44781387848185e-17 + (fConst6 * (fConst9 - 1.11622970892275e-19)))) - 1.11859678983445e-15)));
	fConst51 = ((fConst6 * (1.12211896081664e-15 + (fConst6 * ((fConst6 * (1.13632945852435e-19 - fConst11)) - 5.46818779890163e-17)))) - 2.17010750008645e-15);
	fConst52 = ((fConst6 * (1.22792404260186e-14 + (fConst6 * (fConst13 - 2.55273478792579e-17)))) - 2.69059416486104e-13);
	fConst53 = (2.45620889089652e-16 + (fConst6 * ((fConst6 * (2.43964228204556e-19 - fConst15)) - 1.14222007971933e-16)));
	fConst54 = ((fConst6 * (1.14582451009122e-16 + (fConst6 * (fConst17 - 2.48347397038037e-19)))) - 2.46379143969851e-16);
	fConst55 = (2.62105472308353e-14 + (fConst6 * ((fConst6 * (2.64199358551104e-17 - fConst19)) - 1.21896224477789e-14)));
	fConst56 = (4.91241778179305e-15 + (fConst6 * ((fConst6 * (1.14989728218871e-16 + (fConst6 * (fConst21 - 2.35724702889288e-19)))) - 2.52121869652107e-15)));
	fConst57 = ((fConst6 * (2.52915851496938e-15 + (fConst6 * ((fConst6 * (2.39957070065024e-19 - fConst23)) - 1.15424860004575e-16)))) - 4.92758287939703e-15);
	fConst58 = (2.36238399075912e-21 * fConst6);
	fConst59 = ((fConst6 * (5.81722106266131e-15 + (fConst6 * (1.20886112608973e-17 - fConst58)))) - 3.58123072601056e-13);
	fConst60 = (3.6338751064692e-23 * fConst6);
	fConst61 = (6.49028637330497e-15 + (fConst6 * ((fConst6 * ((fConst6 * (3.34868912676825e-19 - fConst60)) - 5.44781387848185e-17)) - 1.11859678983445e-15)));
	fConst62 = (3.70106825218929e-23 * fConst6);
	fConst63 = ((fConst6 * (1.12211896081664e-15 + (fConst6 * (5.46818779890163e-17 + (fConst6 * (fConst62 - 3.40898837557304e-19)))))) - 6.51032250025936e-15);
	fConst64 = (5.52614015238749e-21 * fConst6);
	fConst65 = ((fConst6 * (1.22792404260186e-14 + (fConst6 * (2.55273478792579e-17 - fConst64)))) - 8.07178249458312e-13);
	fConst66 = (8.60494330807685e-23 * fConst6);
	fConst67 = (2.45620889089652e-16 + (fConst6 * (1.14222007971933e-16 + (fConst6 * (fConst66 - 7.31892684613668e-19)))));
	fConst68 = (8.76405532835057e-23 * fConst6);
	fConst69 = ((fConst6 * ((fConst6 * (7.45042191114112e-19 - fConst68)) - 1.14582451009122e-16)) - 2.46379143969851e-16);
	fConst70 = (5.59407786915994e-21 * fConst6);
	fConst71 = (7.86316416925058e-14 + (fConst6 * ((fConst6 * (fConst70 - 2.64199358551104e-17)) - 1.21896224477789e-14)));
	fConst72 = (8.50043990019081e-23 * fConst6);
	fConst73 = (1.47372533453791e-14 + (fConst6 * ((fConst6 * ((fConst6 * (7.07174108667865e-19 - fConst72)) - 1.14989728218871e-16)) - 2.52121869652107e-15)));
	fConst74 = (8.65761957207373e-23 * fConst6);
	fConst75 = ((fConst6 * (2.52915851496938e-15 + (fConst6 * (1.15424860004575e-16 + (fConst6 * (fConst74 - 7.19871210195072e-19)))))) - 1.47827486381911e-14);
	fConst76 = (1.57492266050608e-21 * fConst6);
	fConst77 = ((fConst6 * ((fConst6 * (2.41772225217946e-17 + fConst76)) - 1.16344421253226e-14)) - 2.3874871506737e-13);
	fConst78 = (7.2677502129384e-23 * fConst6);
	fConst79 = (4.32685758220331e-15 + (fConst6 * (2.2371935796689e-15 + (fConst6 * ((fConst6 * (fConst78 - 2.2324594178455e-19)) - 1.08956277569637e-16)))));
	fConst80 = (7.40213650437857e-23 * fConst6);
	fConst81 = ((fConst6 * ((fConst6 * (1.09363755978033e-16 + (fConst6 * (2.27265891704869e-19 - fConst80)))) - 2.24423792163328e-15)) - 4.3402150001729e-15);
	fConst82 = (3.68409343492499e-21 * fConst6);
	fConst83 = ((fConst6 * ((fConst6 * (5.10546957585158e-17 + fConst82)) - 2.45584808520372e-14)) - 5.38118832972208e-13);
	fConst84 = (1.72098866161537e-22 * fConst6);
	fConst85 = ((fConst6 * (2.28444015943865e-16 + (fConst6 * (4.87928456409112e-19 - fConst84)))) - 4.91241778179304e-16);
	fConst86 = (1.75281106567011e-22 * fConst6);
	fConst87 = (4.92758287939703e-16 + (fConst6 * ((fConst6 * (fConst86 - 4.96694794076075e-19)) - 2.29164902018244e-16)));
	fConst88 = (3.72938524610662e-21 * fConst6);
	fConst89 = (5.24210944616705e-14 + (fConst6 * (2.43792448955579e-14 + (fConst6 * (0 - (5.28398717102207e-17 + fConst88))))));
	fConst90 = (1.70008798003816e-22 * fConst6);
	fConst91 = (9.82483556358609e-15 + (fConst6 * (5.04243739304215e-15 + (fConst6 * ((fConst6 * (fConst90 - 4.71449405778577e-19)) - 2.29979456437742e-16)))));
	fConst92 = (1.73152391441475e-22 * fConst6);
	fConst93 = ((fConst6 * ((fConst6 * (2.3084972000915e-16 + (fConst6 * (4.79914140130048e-19 - fConst92)))) - 5.05831702993876e-15)) - 9.85516575879406e-15);
	fConst94 = (2.3874871506737e-13 + (fConst6 * ((fConst6 * (fConst76 - 2.41772225217946e-17)) - 1.16344421253226e-14)));
	fConst95 = ((fConst6 * (2.2371935796689e-15 + (fConst6 * (1.08956277569637e-16 + (fConst6 * (0 - (2.2324594178455e-19 + fConst78))))))) - 4.32685758220331e-15);
	fConst96 = (4.3402150001729e-15 + (fConst6 * ((fConst6 * ((fConst6 * (2.27265891704869e-19 + fConst80)) - 1.09363755978033e-16)) - 2.24423792163328e-15)));
	fConst97 = (5.38118832972208e-13 + (fConst6 * ((fConst6 * (fConst82 - 5.10546957585158e-17)) - 2.45584808520372e-14)));
	fConst98 = ((fConst6 * ((fConst6 * (4.87928456409112e-19 + fConst84)) - 2.28444015943865e-16)) - 4.91241778179304e-16);
	fConst99 = (4.92758287939703e-16 + (fConst6 * (2.29164902018244e-16 + (fConst6 * (0 - (4.96694794076075e-19 + fConst86))))));
	fConst100 = ((fConst6 * (2.43792448955579e-14 + (fConst6 * (5.28398717102207e-17 - fConst88)))) - 5.24210944616705e-14);
	fConst101 = ((fConst6 * (5.04243739304215e-15 + (fConst6 * (2.29979456437742e-16 + (fConst6 * (0 - (4.71449405778577e-19 + fConst90))))))) - 9.82483556358609e-15);
	fConst102 = (9.85516575879406e-15 + (fConst6 * ((fConst6 * ((fConst6 * (4.79914140130048e-19 + fConst92)) - 2.3084972000915e-16)) - 5.05831702993876e-15)));
	fConst103 = (3.58123072601056e-13 + (fConst6 * (5.81722106266131e-15 + (fConst6 * (0 - (1.20886112608973e-17 + fConst58))))));
	fConst104 = ((fConst6 * ((fConst6 * (5.44781387848185e-17 + (fConst6 * (3.34868912676825e-19 + fConst60)))) - 1.11859678983445e-15)) - 6.49028637330497e-15);
	fConst105 = (6.51032250025936e-15 + (fConst6 * (1.12211896081664e-15 + (fConst6 * ((fConst6 * (0 - (3.40898837557304e-19 + fConst62))) - 5.46818779890163e-17)))));
	fConst106 = (8.07178249458312e-13 + (fConst6 * (1.22792404260186e-14 + (fConst6 * (0 - (2.55273478792579e-17 + fConst64))))));
	fConst107 = (2.45620889089652e-16 + (fConst6 * ((fConst6 * (0 - (7.31892684613668e-19 + fConst66))) - 1.14222007971933e-16)));
	fConst108 = ((fConst6 * (1.14582451009122e-16 + (fConst6 * (7.45042191114112e-19 + fConst68)))) - 2.46379143969851e-16);
	fConst109 = ((fConst6 * ((fConst6 * (2.64199358551104e-17 + fConst70)) - 1.21896224477789e-14)) - 7.86316416925058e-14);
	fConst110 = ((fConst6 * ((fConst6 * (1.14989728218871e-16 + (fConst6 * (7.07174108667865e-19 + fConst72)))) - 2.52121869652107e-15)) - 1.47372533453791e-14);
	fConst111 = (1.47827486381911e-14 + (fConst6 * (2.52915851496938e-15 + (fConst6 * ((fConst6 * (0 - (7.19871210195072e-19 + fConst74))) - 1.15424860004575e-16)))));
	fConst112 = (2.90257268322162e-19 * fConst6);
	fConst113 = (fConst112 - 1.52102059347953e-17);
	fConst114 = (4.54736387038055e-24 * fConst6);
	fConst115 = (4.28927807361227e-22 - fConst114);
	fConst116 = (4.54736387038055e-21 * fConst6);
	fConst117 = (4.28927807361227e-19 - fConst116);
	fConst118 = (4.52725239275021e-23 * fConst6);
	fConst119 = (fConst118 - 4.27030802360382e-21);
	fConst120 = (4.52725239275021e-26 * fConst6);
	fConst121 = (fConst120 - 4.27030802360382e-24);
	fConst122 = (2.45445865940461e-22 * fConst6);
	fConst123 = (0 - (3.32042567560148e-19 + fConst122));
	fConst124 = (2.45445865940461e-19 * fConst6);
	fConst125 = (0 - (3.32042567560148e-16 + fConst124));
	fConst126 = (3.84531856640056e-24 * fConst6);
	fConst127 = (9.36360040519619e-21 + fConst126);
	fConst128 = (3.84531856640056e-21 * fConst6);
	fConst129 = (9.36360040519619e-18 + fConst128);
	fConst130 = (3.82831200160081e-23 * fConst6);
	fConst131 = (0 - (9.3221883155864e-20 + fConst130));
	fConst132 = (3.82831200160081e-26 * fConst6);
	fConst133 = (0 - (9.3221883155864e-23 + fConst132));
	fConst134 = (2.90257268322162e-22 * fConst6);
	fConst135 = (fConst134 - 1.52102059347953e-20);
	fConst136 = (1.93504845548108e-22 * fConst6);
	fConst137 = (0 - (3.04204118695905e-20 + fConst136));
	fConst138 = (1.93504845548108e-19 * fConst6);
	fConst139 = (0 - (3.04204118695905e-17 + fConst138));
	fConst140 = (9.09472774076109e-21 * fConst6);
	fConst141 = (fConst140 - 2.85951871574151e-19);
	fConst142 = (9.05450478550042e-23 * fConst6);
	fConst143 = (2.84687201573588e-21 - fConst142);
	fConst144 = (9.05450478550042e-26 * fConst6);
	fConst145 = (2.84687201573588e-24 - fConst144);
	fConst146 = (9.09472774076109e-24 * fConst6);
	fConst147 = (fConst146 - 2.85951871574151e-22);
	fConst148 = (1.63630577293641e-19 * fConst6);
	fConst149 = (fConst148 - 6.64085135120297e-16);
	fConst150 = (7.69063713280111e-24 * fConst6);
	fConst151 = (0 - (6.24240027013079e-21 + fConst150));
	fConst152 = (7.69063713280111e-21 * fConst6);
	fConst153 = (0 - (6.24240027013079e-18 + fConst152));
	fConst154 = (7.65662400320161e-23 * fConst6);
	fConst155 = (6.21479221039094e-20 + fConst154);
	fConst156 = (7.65662400320161e-26 * fConst6);
	fConst157 = (6.21479221039094e-23 + fConst156);
	fConst158 = (1.63630577293641e-22 * fConst6);
	fConst159 = (fConst158 - 6.64085135120297e-19);
	fConst160 = (3.04204118695905e-20 - fConst136);
	fConst161 = (3.04204118695905e-17 - fConst138);
	fConst162 = (0 - (2.85951871574151e-22 + fConst146));
	fConst163 = (0 - (2.85951871574151e-19 + fConst140));
	fConst164 = (2.84687201573588e-21 + fConst142);
	fConst165 = (2.84687201573588e-24 + fConst144);
	fConst166 = (6.64085135120297e-19 + fConst158);
	fConst167 = (6.64085135120297e-16 + fConst148);
	fConst168 = (fConst152 - 6.24240027013079e-18);
	fConst169 = (6.21479221039094e-20 - fConst154);
	fConst170 = (6.21479221039094e-23 - fConst156);
	fConst171 = (fConst150 - 6.24240027013079e-21);
	fConst172 = (1.52102059347953e-20 + fConst134);
	fConst173 = (1.52102059347953e-17 + fConst112);
	fConst174 = (4.28927807361227e-22 + fConst114);
	fConst175 = (4.28927807361227e-19 + fConst116);
	fConst176 = (0 - (4.27030802360382e-21 + fConst118));
	fConst177 = (0 - (4.27030802360382e-24 + fConst120));
	fConst178 = (3.32042567560148e-19 - fConst122);
	fConst179 = (3.32042567560148e-16 - fConst124);
	fConst180 = (9.36360040519619e-21 - fConst126);
	fConst181 = (9.36360040519619e-18 - fConst128);
	fConst182 = (fConst130 - 9.3221883155864e-20);
	fConst183 = (fConst132 - 9.3221883155864e-23);
	fConst184 = (0 - (1.52102059347953e-20 + fConst25));
	fConst185 = (0 - (1.52102059347953e-17 + fConst27));
	fConst186 = (0 - (1.42975935787076e-22 + fConst35));
	fConst187 = (0 - (1.42975935787076e-19 + fConst29));
	fConst188 = (1.42343600786794e-21 + fConst31);
	fConst189 = (1.42343600786794e-24 + fConst33);
	fConst190 = (fConst39 - 3.32042567560148e-16);
	fConst191 = (fConst43 - 3.12120013506539e-18);
	fConst192 = (3.10739610519547e-20 - fConst45);
	fConst193 = (3.10739610519547e-23 - fConst47);
	fConst194 = (fConst41 - 3.1212001350654e-21);
	fConst195 = (fConst37 - 3.32042567560148e-19);
	fConst196 = (1 + fConst3);
	fConst197 = (faustpower<3>(fConst6) / fConst196);
	fConst198 = (0 - ((1 - fConst3) / fConst196));
	fConst199 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst200 = (1 + fConst199);
	fConst201 = (0.027 / fConst200);
	fConst202 = (0 - ((1 - fConst199) / fConst200));
	fConst203 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst204 = (0 - fConst203);
	fConst205 = (1 + fConst203);
	fConst206 = (0.025 / fConst205);
	fConst207 = (0 - ((1 - fConst203) / fConst205));
	fConst208 = (1.0 / fConst196);
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
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fRec8[0] = ((0.993 * fRec8[1]) + fSlow2);
		fRec9[0] = ((0.993 * fRec9[1]) + fSlow3);
		double fTemp1 = (2.30862500009197e-13 + ((fRec9[0] * (5.24210944616705e-13 + (fConst6 * (((fRec8[0] * (fConst24 + (fConst22 * fRec8[0]))) + (fRec9[0] * (fConst20 + (fConst6 * (fRec8[0] * (fConst18 + (fConst16 * fRec8[0]))))))) + fConst14)))) + (fConst6 * ((fRec8[0] * (fConst12 + (fConst10 * fRec8[0]))) + fConst8))));
		fRec10[0] = ((0.993 * fRec10[1]) + fSlow4);
		fRec11[0] = ((fSlow0 * fTemp0) - ((((((fRec11[1] * (1.15431250004598e-12 + ((fRec9[0] * (2.62105472308353e-12 + (fConst6 * (((fRec8[0] * (fConst111 + (fConst110 * fRec8[0]))) + (fRec9[0] * (fConst109 + (fConst6 * (fRec8[0] * (fConst108 + (fConst107 * fRec8[0]))))))) + fConst106)))) + (fConst6 * ((fRec8[0] * (fConst105 + (fConst104 * fRec8[0]))) + fConst103))))) + (fRec11[2] * (2.30862500009197e-12 + ((fRec9[0] * (5.24210944616705e-12 + (fConst6 * (((fRec8[0] * (fConst102 + (fConst101 * fRec8[0]))) + (fRec9[0] * (fConst100 + (fConst6 * (fRec8[0] * (fConst99 + (fConst98 * fRec8[0]))))))) + fConst97)))) + (fConst6 * ((fRec8[0] * (fConst96 + (fConst95 * fRec8[0]))) + fConst94)))))) + (fRec11[3] * (2.30862500009197e-12 + ((fRec9[0] * (5.24210944616705e-12 + (fConst6 * (((fRec8[0] * (fConst93 + (fConst91 * fRec8[0]))) + (fRec9[0] * (fConst89 + (fConst6 * (fRec8[0] * (fConst87 + (fConst85 * fRec8[0]))))))) + fConst83)))) + (fConst6 * ((fRec8[0] * (fConst81 + (fConst79 * fRec8[0]))) + fConst77)))))) + (fRec11[4] * (1.15431250004598e-12 + ((fRec9[0] * (2.62105472308353e-12 + (fConst6 * (((fRec8[0] * (fConst75 + (fConst73 * fRec8[0]))) + (fRec9[0] * (fConst71 + (fConst6 * (fRec8[0] * (fConst69 + (fConst67 * fRec8[0]))))))) + fConst65)))) + (fConst6 * ((fRec8[0] * (fConst63 + (fConst61 * fRec8[0]))) + fConst59)))))) + (fRec11[5] * (2.30862500009197e-13 + ((fRec9[0] * (5.24210944616705e-13 + (fConst6 * (((fRec8[0] * (fConst57 + (fConst56 * fRec8[0]))) + (fRec9[0] * (fConst55 + (fConst6 * (fRec8[0] * (fConst54 + (fConst53 * fRec8[0]))))))) + fConst52)))) + (fConst6 * ((fRec8[0] * (fConst51 + (fConst50 * fRec8[0]))) + fConst49)))))) / fTemp1));
		double fTemp2 = (((((((fRec11[0] * ((((fRec9[0] * (fConst195 + ((fConst6 * (fRec8[0] * (fConst194 + ((fRec8[0] * (fConst193 + (fConst192 * fRec10[0]))) + (fConst191 * fRec10[0]))))) + (fConst190 * fRec10[0])))) + (fConst6 * (fRec8[0] * (((fRec8[0] * (fConst189 + (fConst188 * fRec10[0]))) + (fConst187 * fRec10[0])) + fConst186)))) + (fConst185 * fRec10[0])) + fConst184)) + (fRec11[1] * ((((fRec9[0] * (((fConst6 * (fRec8[0] * (((fRec8[0] * (fConst183 + (fConst182 * fRec10[0]))) + (fConst181 * fRec10[0])) + fConst180))) + (fConst179 * fRec10[0])) + fConst178)) + (fConst6 * (fRec8[0] * (((fRec8[0] * (fConst177 + (fConst176 * fRec10[0]))) + (fConst175 * fRec10[0])) + fConst174)))) + (fConst173 * fRec10[0])) + fConst172))) + (fRec11[2] * ((((fRec9[0] * (((fConst6 * (fRec8[0] * (fConst171 + ((fRec8[0] * (fConst170 + (fConst169 * fRec10[0]))) + (fConst168 * fRec10[0]))))) + (fConst167 * fRec10[0])) + fConst166)) + (fConst6 * (fRec8[0] * (((fRec8[0] * (fConst165 + (fConst164 * fRec10[0]))) + (fConst163 * fRec10[0])) + fConst162)))) + (fConst161 * fRec10[0])) + fConst160))) + (fRec11[3] * ((((fRec9[0] * (fConst159 + ((fConst6 * (fRec8[0] * (((fRec8[0] * (fConst157 + (fConst155 * fRec10[0]))) + (fConst153 * fRec10[0])) + fConst151))) + (fConst149 * fRec10[0])))) + (fConst6 * (fRec8[0] * (fConst147 + ((fRec8[0] * (fConst145 + (fConst143 * fRec10[0]))) + (fConst141 * fRec10[0])))))) + (fConst139 * fRec10[0])) + fConst137))) + (fRec11[4] * (fConst135 + (((fRec9[0] * (((fConst6 * (fRec8[0] * (((fRec8[0] * (fConst133 + (fConst131 * fRec10[0]))) + (fConst129 * fRec10[0])) + fConst127))) + (fConst125 * fRec10[0])) + fConst123)) + (fConst6 * (fRec8[0] * (((fRec8[0] * (fConst121 + (fConst119 * fRec10[0]))) + (fConst117 * fRec10[0])) + fConst115)))) + (fConst113 * fRec10[0]))))) + (fRec11[5] * ((((fRec9[0] * (((fConst6 * (fRec8[0] * (((fRec8[0] * (fConst48 + (fConst46 * fRec10[0]))) + (fConst44 * fRec10[0])) + fConst42))) + (fConst40 * fRec10[0])) + fConst38)) + (fConst6 * (fRec8[0] * (fConst36 + ((fRec8[0] * (fConst34 + (fConst32 * fRec10[0]))) + (fConst30 * fRec10[0])))))) + (fConst28 * fRec10[0])) + fConst26))) / fTemp1);
		fVec0[0] = fTemp2;
		fRec7[0] = ((fConst198 * fRec7[1]) + (fConst197 * (fVec0[0] + fVec0[1])));
		fRec6[0] = (fRec7[0] - (fConst5 * ((fConst4 * fRec6[2]) + (fConst2 * fRec6[1]))));
		fRec12[0] = ((fConst202 * fRec12[1]) + (fConst201 * (fRec5[1] + fRec5[2])));
		fRec5[0] = (Ftrany(TRANY_TABLE_KT88_68k, ((fRec12[0] + (fConst5 * (fRec6[2] + (fRec6[0] + (2 * fRec6[1]))))) - 5.562895)) - 43.96685185185183);
		fRec4[0] = ((fConst207 * fRec4[1]) + (fConst206 * ((fConst203 * fRec5[0]) + (fConst204 * fRec5[1]))));
		fRec3[0] = ((fConst198 * fRec3[1]) + (fConst208 * (fRec4[0] + fRec4[1])));
		fRec2[0] = (fRec3[0] - (fConst5 * ((fConst4 * fRec2[2]) + (fConst2 * fRec2[1]))));
		fRec13[0] = ((fConst202 * fRec13[1]) + (fConst201 * (fRec1[1] + fRec1[2])));
		fRec1[0] = (Ftrany(TRANY_TABLE_KT88_68k, ((fRec13[0] + (fConst5 * (fRec2[2] + (fRec2[0] + (2 * fRec2[1]))))) - 5.562895)) - 43.96685185185183);
		fRec0[0] = ((fConst207 * fRec0[1]) + (fConst206 * ((fConst203 * fRec1[0]) + (fConst204 * fRec1[1]))));
		output0[i] = (FAUSTFLOAT)(fRec0[0] + (fSlow1 * fTemp0));
		// post processing
		fRec0[1] = fRec0[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec13[1] = fRec13[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec12[1] = fRec12[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec7[1] = fRec7[0];
		fVec0[1] = fVec0[0];
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
	reg.registerVar("cstbt1.Attack",N_("Attack"),"S","",&fslider1, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("cstbt1.Level",N_("Level"),"S","",&fslider3, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("cstbt1.Tone",N_("Tone"),"S","",&fslider2, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("cstbt1.wet_dry",N_("wet/dry"),"S",N_("percentage of processed signal in output signal"),&fslider0, 1e+02, 0.0, 1e+02, 1.0);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("cstbt1" "." p)

b.openHorizontalhideBox("");
    b.create_master_slider(PARAM("Level"), "Level");
b.closeBox();
b.openHorizontalBox("");

    b.create_small_rackknobr(PARAM("Level"), "Level");

    b.create_small_rackknobr(PARAM("Tone"), "Tone");

    b.create_small_rackknobr(PARAM("Attack"), "Attack");
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

} // end namespace cstb
} // end namespace pluginlib
