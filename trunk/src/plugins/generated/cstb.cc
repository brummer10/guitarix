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
	FAUSTFLOAT 	fslider1;
	double 	fRec8[2];
	double 	fConst4;
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
	FAUSTFLOAT 	fslider2;
	double 	fRec9[2];
	double 	fConst16;
	double 	fConst17;
	double 	fConst18;
	double 	fConst19;
	double 	fConst20;
	double 	fConst21;
	FAUSTFLOAT 	fslider3;
	double 	fRec10[2];
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
	double 	fRec11[6];
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
	double 	fVec0[2];
	double 	fConst191;
	double 	fRec7[2];
	double 	fRec6[3];
	double 	fConst192;
	double 	fConst193;
	double 	fConst194;
	double 	fConst195;
	double 	fRec12[2];
	double 	fRec5[3];
	double 	fConst196;
	double 	fConst197;
	double 	fConst198;
	double 	fConst199;
	double 	fConst200;
	double 	fRec4[2];
	double 	fRec3[2];
	double 	fRec2[3];
	double 	fRec13[2];
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
	id = "cstbt1";
	name = N_("Colorsound Tone Blender");
	groups = 0;
	description = N_("Colorsound Tone Blender"); // description (tooltip)
	category = N_("Fuzz");       // category
	shortname = N_("CS Tone");     // shortname
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
	fConst1 = double(iConst0);
	fConst2 = (7.8746133025304e-22 * fConst1);
	fConst3 = (1.19374357533685e-13 + (fConst1 * (5.81722106266131e-15 + (fConst1 * (1.20886112608973e-17 + fConst2)))));
	fConst4 = (7.2677502129384e-24 * fConst1);
	fConst5 = ((fConst1 * ((fConst1 * ((fConst1 * (0 - (1.11622970892275e-19 + fConst4))) - 5.44781387848185e-17)) - 1.11859678983445e-15)) - 2.16342879110166e-15);
	fConst6 = (7.40213650437857e-24 * fConst1);
	fConst7 = (2.17010750008645e-15 + (fConst1 * (1.12211896081664e-15 + (fConst1 * (5.46818779890163e-17 + (fConst1 * (1.13632945852435e-19 + fConst6)))))));
	fConst8 = (1.8420467174625e-21 * fConst1);
	fConst9 = (2.69059416486104e-13 + (fConst1 * (1.22792404260186e-14 + (fConst1 * (2.55273478792579e-17 + fConst8)))));
	fConst10 = (1.72098866161537e-23 * fConst1);
	fConst11 = (2.45620889089652e-16 + (fConst1 * (1.14222007971933e-16 + (fConst1 * (2.43964228204556e-19 + fConst10)))));
	fConst12 = (1.75281106567011e-23 * fConst1);
	fConst13 = ((fConst1 * ((fConst1 * (0 - (2.48347397038037e-19 + fConst12))) - 1.14582451009122e-16)) - 2.46379143969851e-16);
	fConst14 = (1.86469262305331e-21 * fConst1);
	fConst15 = ((fConst1 * ((fConst1 * (0 - (2.64199358551104e-17 + fConst14))) - 1.21896224477789e-14)) - 2.62105472308353e-14);
	fConst16 = (1.70008798003816e-23 * fConst1);
	fConst17 = ((fConst1 * ((fConst1 * ((fConst1 * (0 - (2.35724702889288e-19 + fConst16))) - 1.14989728218871e-16)) - 2.52121869652107e-15)) - 4.91241778179305e-15);
	fConst18 = (1.73152391441475e-23 * fConst1);
	fConst19 = (4.92758287939703e-15 + (fConst1 * (2.52915851496938e-15 + (fConst1 * (1.15424860004575e-16 + (fConst1 * (2.39957070065024e-19 + fConst18)))))));
	fConst20 = (9.67524227740541e-23 * fConst1);
	fConst21 = (1.52102059347953e-20 - fConst20);
	fConst22 = (9.67524227740542e-20 * fConst1);
	fConst23 = (1.52102059347953e-17 - fConst22);
	fConst24 = (9.09472774076109e-22 * fConst1);
	fConst25 = (fConst24 - 1.42975935787076e-19);
	fConst26 = (9.05450478550043e-24 * fConst1);
	fConst27 = (1.42343600786794e-21 - fConst26);
	fConst28 = (9.05450478550042e-27 * fConst1);
	fConst29 = (1.42343600786794e-24 - fConst28);
	fConst30 = (9.09472774076109e-25 * fConst1);
	fConst31 = (fConst30 - 1.42975935787076e-22);
	fConst32 = (8.18152886468203e-23 * fConst1);
	fConst33 = (3.32042567560148e-19 + fConst32);
	fConst34 = (8.18152886468203e-20 * fConst1);
	fConst35 = (3.32042567560148e-16 + fConst34);
	fConst36 = (7.69063713280111e-25 * fConst1);
	fConst37 = (0 - (3.1212001350654e-21 + fConst36));
	fConst38 = (7.69063713280111e-22 * fConst1);
	fConst39 = (0 - (3.12120013506539e-18 + fConst38));
	fConst40 = (7.65662400320161e-24 * fConst1);
	fConst41 = (3.10739610519547e-20 + fConst40);
	fConst42 = (7.65662400320161e-27 * fConst1);
	fConst43 = (3.10739610519547e-23 + fConst42);
	fConst44 = ((fConst1 * (5.81722106266131e-15 + (fConst1 * (fConst2 - 1.20886112608973e-17)))) - 1.19374357533685e-13);
	fConst45 = (2.16342879110166e-15 + (fConst1 * ((fConst1 * (5.44781387848185e-17 + (fConst1 * (fConst4 - 1.11622970892275e-19)))) - 1.11859678983445e-15)));
	fConst46 = ((fConst1 * (1.12211896081664e-15 + (fConst1 * ((fConst1 * (1.13632945852435e-19 - fConst6)) - 5.46818779890163e-17)))) - 2.17010750008645e-15);
	fConst47 = ((fConst1 * (1.22792404260186e-14 + (fConst1 * (fConst8 - 2.55273478792579e-17)))) - 2.69059416486104e-13);
	fConst48 = (2.45620889089652e-16 + (fConst1 * ((fConst1 * (2.43964228204556e-19 - fConst10)) - 1.14222007971933e-16)));
	fConst49 = ((fConst1 * (1.14582451009122e-16 + (fConst1 * (fConst12 - 2.48347397038037e-19)))) - 2.46379143969851e-16);
	fConst50 = (2.62105472308353e-14 + (fConst1 * ((fConst1 * (2.64199358551104e-17 - fConst14)) - 1.21896224477789e-14)));
	fConst51 = (4.91241778179305e-15 + (fConst1 * ((fConst1 * (1.14989728218871e-16 + (fConst1 * (fConst16 - 2.35724702889288e-19)))) - 2.52121869652107e-15)));
	fConst52 = ((fConst1 * (2.52915851496938e-15 + (fConst1 * ((fConst1 * (2.39957070065024e-19 - fConst18)) - 1.15424860004575e-16)))) - 4.92758287939703e-15);
	fConst53 = (2.36238399075912e-21 * fConst1);
	fConst54 = ((fConst1 * (5.81722106266131e-15 + (fConst1 * (1.20886112608973e-17 - fConst53)))) - 3.58123072601056e-13);
	fConst55 = (3.6338751064692e-23 * fConst1);
	fConst56 = (6.49028637330497e-15 + (fConst1 * ((fConst1 * ((fConst1 * (3.34868912676825e-19 - fConst55)) - 5.44781387848185e-17)) - 1.11859678983445e-15)));
	fConst57 = (3.70106825218929e-23 * fConst1);
	fConst58 = ((fConst1 * (1.12211896081664e-15 + (fConst1 * (5.46818779890163e-17 + (fConst1 * (fConst57 - 3.40898837557304e-19)))))) - 6.51032250025936e-15);
	fConst59 = (5.52614015238749e-21 * fConst1);
	fConst60 = ((fConst1 * (1.22792404260186e-14 + (fConst1 * (2.55273478792579e-17 - fConst59)))) - 8.07178249458312e-13);
	fConst61 = (8.60494330807685e-23 * fConst1);
	fConst62 = (2.45620889089652e-16 + (fConst1 * (1.14222007971933e-16 + (fConst1 * (fConst61 - 7.31892684613668e-19)))));
	fConst63 = (8.76405532835057e-23 * fConst1);
	fConst64 = ((fConst1 * ((fConst1 * (7.45042191114112e-19 - fConst63)) - 1.14582451009122e-16)) - 2.46379143969851e-16);
	fConst65 = (5.59407786915994e-21 * fConst1);
	fConst66 = (7.86316416925058e-14 + (fConst1 * ((fConst1 * (fConst65 - 2.64199358551104e-17)) - 1.21896224477789e-14)));
	fConst67 = (8.50043990019081e-23 * fConst1);
	fConst68 = (1.47372533453791e-14 + (fConst1 * ((fConst1 * ((fConst1 * (7.07174108667865e-19 - fConst67)) - 1.14989728218871e-16)) - 2.52121869652107e-15)));
	fConst69 = (8.65761957207373e-23 * fConst1);
	fConst70 = ((fConst1 * (2.52915851496938e-15 + (fConst1 * (1.15424860004575e-16 + (fConst1 * (fConst69 - 7.19871210195072e-19)))))) - 1.47827486381911e-14);
	fConst71 = (1.57492266050608e-21 * fConst1);
	fConst72 = ((fConst1 * ((fConst1 * (2.41772225217946e-17 + fConst71)) - 1.16344421253226e-14)) - 2.3874871506737e-13);
	fConst73 = (7.2677502129384e-23 * fConst1);
	fConst74 = (4.32685758220331e-15 + (fConst1 * (2.2371935796689e-15 + (fConst1 * ((fConst1 * (fConst73 - 2.2324594178455e-19)) - 1.08956277569637e-16)))));
	fConst75 = (7.40213650437857e-23 * fConst1);
	fConst76 = ((fConst1 * ((fConst1 * (1.09363755978033e-16 + (fConst1 * (2.27265891704869e-19 - fConst75)))) - 2.24423792163328e-15)) - 4.3402150001729e-15);
	fConst77 = (3.68409343492499e-21 * fConst1);
	fConst78 = ((fConst1 * ((fConst1 * (5.10546957585158e-17 + fConst77)) - 2.45584808520372e-14)) - 5.38118832972208e-13);
	fConst79 = (1.72098866161537e-22 * fConst1);
	fConst80 = ((fConst1 * (2.28444015943865e-16 + (fConst1 * (4.87928456409112e-19 - fConst79)))) - 4.91241778179304e-16);
	fConst81 = (1.75281106567011e-22 * fConst1);
	fConst82 = (4.92758287939703e-16 + (fConst1 * ((fConst1 * (fConst81 - 4.96694794076075e-19)) - 2.29164902018244e-16)));
	fConst83 = (3.72938524610662e-21 * fConst1);
	fConst84 = (5.24210944616705e-14 + (fConst1 * (2.43792448955579e-14 + (fConst1 * (0 - (5.28398717102207e-17 + fConst83))))));
	fConst85 = (1.70008798003816e-22 * fConst1);
	fConst86 = (9.82483556358609e-15 + (fConst1 * (5.04243739304215e-15 + (fConst1 * ((fConst1 * (fConst85 - 4.71449405778577e-19)) - 2.29979456437742e-16)))));
	fConst87 = (1.73152391441475e-22 * fConst1);
	fConst88 = ((fConst1 * ((fConst1 * (2.3084972000915e-16 + (fConst1 * (4.79914140130048e-19 - fConst87)))) - 5.05831702993876e-15)) - 9.85516575879406e-15);
	fConst89 = (2.3874871506737e-13 + (fConst1 * ((fConst1 * (fConst71 - 2.41772225217946e-17)) - 1.16344421253226e-14)));
	fConst90 = ((fConst1 * (2.2371935796689e-15 + (fConst1 * (1.08956277569637e-16 + (fConst1 * (0 - (2.2324594178455e-19 + fConst73))))))) - 4.32685758220331e-15);
	fConst91 = (4.3402150001729e-15 + (fConst1 * ((fConst1 * ((fConst1 * (2.27265891704869e-19 + fConst75)) - 1.09363755978033e-16)) - 2.24423792163328e-15)));
	fConst92 = (5.38118832972208e-13 + (fConst1 * ((fConst1 * (fConst77 - 5.10546957585158e-17)) - 2.45584808520372e-14)));
	fConst93 = ((fConst1 * ((fConst1 * (4.87928456409112e-19 + fConst79)) - 2.28444015943865e-16)) - 4.91241778179304e-16);
	fConst94 = (4.92758287939703e-16 + (fConst1 * (2.29164902018244e-16 + (fConst1 * (0 - (4.96694794076075e-19 + fConst81))))));
	fConst95 = ((fConst1 * (2.43792448955579e-14 + (fConst1 * (5.28398717102207e-17 - fConst83)))) - 5.24210944616705e-14);
	fConst96 = ((fConst1 * (5.04243739304215e-15 + (fConst1 * (2.29979456437742e-16 + (fConst1 * (0 - (4.71449405778577e-19 + fConst85))))))) - 9.82483556358609e-15);
	fConst97 = (9.85516575879406e-15 + (fConst1 * ((fConst1 * ((fConst1 * (4.79914140130048e-19 + fConst87)) - 2.3084972000915e-16)) - 5.05831702993876e-15)));
	fConst98 = (3.58123072601056e-13 + (fConst1 * (5.81722106266131e-15 + (fConst1 * (0 - (1.20886112608973e-17 + fConst53))))));
	fConst99 = ((fConst1 * ((fConst1 * (5.44781387848185e-17 + (fConst1 * (3.34868912676825e-19 + fConst55)))) - 1.11859678983445e-15)) - 6.49028637330497e-15);
	fConst100 = (6.51032250025936e-15 + (fConst1 * (1.12211896081664e-15 + (fConst1 * ((fConst1 * (0 - (3.40898837557304e-19 + fConst57))) - 5.46818779890163e-17)))));
	fConst101 = (8.07178249458312e-13 + (fConst1 * (1.22792404260186e-14 + (fConst1 * (0 - (2.55273478792579e-17 + fConst59))))));
	fConst102 = (2.45620889089652e-16 + (fConst1 * ((fConst1 * (0 - (7.31892684613668e-19 + fConst61))) - 1.14222007971933e-16)));
	fConst103 = ((fConst1 * (1.14582451009122e-16 + (fConst1 * (7.45042191114112e-19 + fConst63)))) - 2.46379143969851e-16);
	fConst104 = ((fConst1 * ((fConst1 * (2.64199358551104e-17 + fConst65)) - 1.21896224477789e-14)) - 7.86316416925058e-14);
	fConst105 = ((fConst1 * ((fConst1 * (1.14989728218871e-16 + (fConst1 * (7.07174108667865e-19 + fConst67)))) - 2.52121869652107e-15)) - 1.47372533453791e-14);
	fConst106 = (1.47827486381911e-14 + (fConst1 * (2.52915851496938e-15 + (fConst1 * ((fConst1 * (0 - (7.19871210195072e-19 + fConst69))) - 1.15424860004575e-16)))));
	fConst107 = (2.90257268322162e-19 * fConst1);
	fConst108 = (fConst107 - 1.52102059347953e-17);
	fConst109 = (4.54736387038055e-24 * fConst1);
	fConst110 = (4.28927807361227e-22 - fConst109);
	fConst111 = (4.54736387038055e-21 * fConst1);
	fConst112 = (4.28927807361227e-19 - fConst111);
	fConst113 = (4.52725239275021e-23 * fConst1);
	fConst114 = (fConst113 - 4.27030802360382e-21);
	fConst115 = (4.52725239275021e-26 * fConst1);
	fConst116 = (fConst115 - 4.27030802360382e-24);
	fConst117 = (2.45445865940461e-22 * fConst1);
	fConst118 = (0 - (3.32042567560148e-19 + fConst117));
	fConst119 = (2.45445865940461e-19 * fConst1);
	fConst120 = (0 - (3.32042567560148e-16 + fConst119));
	fConst121 = (3.84531856640056e-24 * fConst1);
	fConst122 = (9.36360040519619e-21 + fConst121);
	fConst123 = (3.84531856640056e-21 * fConst1);
	fConst124 = (9.36360040519619e-18 + fConst123);
	fConst125 = (3.82831200160081e-23 * fConst1);
	fConst126 = (0 - (9.3221883155864e-20 + fConst125));
	fConst127 = (3.82831200160081e-26 * fConst1);
	fConst128 = (0 - (9.3221883155864e-23 + fConst127));
	fConst129 = (2.90257268322162e-22 * fConst1);
	fConst130 = (fConst129 - 1.52102059347953e-20);
	fConst131 = (1.93504845548108e-22 * fConst1);
	fConst132 = (0 - (3.04204118695905e-20 + fConst131));
	fConst133 = (1.93504845548108e-19 * fConst1);
	fConst134 = (0 - (3.04204118695905e-17 + fConst133));
	fConst135 = (9.09472774076109e-21 * fConst1);
	fConst136 = (fConst135 - 2.85951871574151e-19);
	fConst137 = (9.05450478550042e-23 * fConst1);
	fConst138 = (2.84687201573588e-21 - fConst137);
	fConst139 = (9.05450478550042e-26 * fConst1);
	fConst140 = (2.84687201573588e-24 - fConst139);
	fConst141 = (9.09472774076109e-24 * fConst1);
	fConst142 = (fConst141 - 2.85951871574151e-22);
	fConst143 = (1.63630577293641e-19 * fConst1);
	fConst144 = (fConst143 - 6.64085135120297e-16);
	fConst145 = (7.69063713280111e-24 * fConst1);
	fConst146 = (0 - (6.24240027013079e-21 + fConst145));
	fConst147 = (7.69063713280111e-21 * fConst1);
	fConst148 = (0 - (6.24240027013079e-18 + fConst147));
	fConst149 = (7.65662400320161e-23 * fConst1);
	fConst150 = (6.21479221039094e-20 + fConst149);
	fConst151 = (7.65662400320161e-26 * fConst1);
	fConst152 = (6.21479221039094e-23 + fConst151);
	fConst153 = (1.63630577293641e-22 * fConst1);
	fConst154 = (fConst153 - 6.64085135120297e-19);
	fConst155 = (3.04204118695905e-20 - fConst131);
	fConst156 = (3.04204118695905e-17 - fConst133);
	fConst157 = (0 - (2.85951871574151e-22 + fConst141));
	fConst158 = (0 - (2.85951871574151e-19 + fConst135));
	fConst159 = (2.84687201573588e-21 + fConst137);
	fConst160 = (2.84687201573588e-24 + fConst139);
	fConst161 = (6.64085135120297e-19 + fConst153);
	fConst162 = (6.64085135120297e-16 + fConst143);
	fConst163 = (fConst147 - 6.24240027013079e-18);
	fConst164 = (6.21479221039094e-20 - fConst149);
	fConst165 = (6.21479221039094e-23 - fConst151);
	fConst166 = (fConst145 - 6.24240027013079e-21);
	fConst167 = (1.52102059347953e-20 + fConst129);
	fConst168 = (1.52102059347953e-17 + fConst107);
	fConst169 = (4.28927807361227e-22 + fConst109);
	fConst170 = (4.28927807361227e-19 + fConst111);
	fConst171 = (0 - (4.27030802360382e-21 + fConst113));
	fConst172 = (0 - (4.27030802360382e-24 + fConst115));
	fConst173 = (3.32042567560148e-19 - fConst117);
	fConst174 = (3.32042567560148e-16 - fConst119);
	fConst175 = (9.36360040519619e-21 - fConst121);
	fConst176 = (9.36360040519619e-18 - fConst123);
	fConst177 = (fConst125 - 9.3221883155864e-20);
	fConst178 = (fConst127 - 9.3221883155864e-23);
	fConst179 = (0 - (1.52102059347953e-20 + fConst20));
	fConst180 = (0 - (1.52102059347953e-17 + fConst22));
	fConst181 = (0 - (1.42975935787076e-22 + fConst30));
	fConst182 = (0 - (1.42975935787076e-19 + fConst24));
	fConst183 = (1.42343600786794e-21 + fConst26);
	fConst184 = (1.42343600786794e-24 + fConst28);
	fConst185 = (fConst34 - 3.32042567560148e-16);
	fConst186 = (fConst38 - 3.12120013506539e-18);
	fConst187 = (3.10739610519547e-20 - fConst40);
	fConst188 = (3.10739610519547e-23 - fConst42);
	fConst189 = (fConst36 - 3.1212001350654e-21);
	fConst190 = (fConst32 - 3.32042567560148e-19);
	fConst191 = (0.9302847925323914 * faustpower<3>(fConst1));
	fConst192 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst193 = (1 + fConst192);
	fConst194 = (0.027 / fConst193);
	fConst195 = (0 - ((1 - fConst192) / fConst193));
	fConst196 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst197 = (0 - fConst196);
	fConst198 = (1 + fConst196);
	fConst199 = (0.025 / fConst198);
	fConst200 = (0 - ((1 - fConst196) / fConst198));
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
		double fTemp1 = (2.30862500009197e-13 + ((fRec9[0] * (5.24210944616705e-13 + (fConst1 * (((fRec8[0] * (fConst19 + (fConst17 * fRec8[0]))) + (fRec9[0] * (fConst15 + (fConst1 * (fRec8[0] * (fConst13 + (fConst11 * fRec8[0]))))))) + fConst9)))) + (fConst1 * ((fRec8[0] * (fConst7 + (fConst5 * fRec8[0]))) + fConst3))));
		fRec10[0] = ((0.993 * fRec10[1]) + fSlow4);
		fRec11[0] = ((fSlow0 * fTemp0) - ((((((fRec11[1] * (1.15431250004598e-12 + ((fRec9[0] * (2.62105472308353e-12 + (fConst1 * (((fRec8[0] * (fConst106 + (fConst105 * fRec8[0]))) + (fRec9[0] * (fConst104 + (fConst1 * (fRec8[0] * (fConst103 + (fConst102 * fRec8[0]))))))) + fConst101)))) + (fConst1 * ((fRec8[0] * (fConst100 + (fConst99 * fRec8[0]))) + fConst98))))) + (fRec11[2] * (2.30862500009197e-12 + ((fRec9[0] * (5.24210944616705e-12 + (fConst1 * (((fRec8[0] * (fConst97 + (fConst96 * fRec8[0]))) + (fRec9[0] * (fConst95 + (fConst1 * (fRec8[0] * (fConst94 + (fConst93 * fRec8[0]))))))) + fConst92)))) + (fConst1 * ((fRec8[0] * (fConst91 + (fConst90 * fRec8[0]))) + fConst89)))))) + (fRec11[3] * (2.30862500009197e-12 + ((fRec9[0] * (5.24210944616705e-12 + (fConst1 * (((fRec8[0] * (fConst88 + (fConst86 * fRec8[0]))) + (fRec9[0] * (fConst84 + (fConst1 * (fRec8[0] * (fConst82 + (fConst80 * fRec8[0]))))))) + fConst78)))) + (fConst1 * ((fRec8[0] * (fConst76 + (fConst74 * fRec8[0]))) + fConst72)))))) + (fRec11[4] * (1.15431250004598e-12 + ((fRec9[0] * (2.62105472308353e-12 + (fConst1 * (((fRec8[0] * (fConst70 + (fConst68 * fRec8[0]))) + (fRec9[0] * (fConst66 + (fConst1 * (fRec8[0] * (fConst64 + (fConst62 * fRec8[0]))))))) + fConst60)))) + (fConst1 * ((fRec8[0] * (fConst58 + (fConst56 * fRec8[0]))) + fConst54)))))) + (fRec11[5] * (2.30862500009197e-13 + ((fRec9[0] * (5.24210944616705e-13 + (fConst1 * (((fRec8[0] * (fConst52 + (fConst51 * fRec8[0]))) + (fRec9[0] * (fConst50 + (fConst1 * (fRec8[0] * (fConst49 + (fConst48 * fRec8[0]))))))) + fConst47)))) + (fConst1 * ((fRec8[0] * (fConst46 + (fConst45 * fRec8[0]))) + fConst44)))))) / fTemp1));
		double fTemp2 = (((((((fRec11[0] * ((((fRec9[0] * (fConst190 + ((fConst1 * (fRec8[0] * (fConst189 + ((fRec8[0] * (fConst188 + (fConst187 * fRec10[0]))) + (fConst186 * fRec10[0]))))) + (fConst185 * fRec10[0])))) + (fConst1 * (fRec8[0] * (((fRec8[0] * (fConst184 + (fConst183 * fRec10[0]))) + (fConst182 * fRec10[0])) + fConst181)))) + (fConst180 * fRec10[0])) + fConst179)) + (fRec11[1] * ((((fRec9[0] * (((fConst1 * (fRec8[0] * (((fRec8[0] * (fConst178 + (fConst177 * fRec10[0]))) + (fConst176 * fRec10[0])) + fConst175))) + (fConst174 * fRec10[0])) + fConst173)) + (fConst1 * (fRec8[0] * (((fRec8[0] * (fConst172 + (fConst171 * fRec10[0]))) + (fConst170 * fRec10[0])) + fConst169)))) + (fConst168 * fRec10[0])) + fConst167))) + (fRec11[2] * ((((fRec9[0] * (((fConst1 * (fRec8[0] * (fConst166 + ((fRec8[0] * (fConst165 + (fConst164 * fRec10[0]))) + (fConst163 * fRec10[0]))))) + (fConst162 * fRec10[0])) + fConst161)) + (fConst1 * (fRec8[0] * (((fRec8[0] * (fConst160 + (fConst159 * fRec10[0]))) + (fConst158 * fRec10[0])) + fConst157)))) + (fConst156 * fRec10[0])) + fConst155))) + (fRec11[3] * ((((fRec9[0] * (fConst154 + ((fConst1 * (fRec8[0] * (((fRec8[0] * (fConst152 + (fConst150 * fRec10[0]))) + (fConst148 * fRec10[0])) + fConst146))) + (fConst144 * fRec10[0])))) + (fConst1 * (fRec8[0] * (fConst142 + ((fRec8[0] * (fConst140 + (fConst138 * fRec10[0]))) + (fConst136 * fRec10[0])))))) + (fConst134 * fRec10[0])) + fConst132))) + (fRec11[4] * (fConst130 + (((fRec9[0] * (((fConst1 * (fRec8[0] * (((fRec8[0] * (fConst128 + (fConst126 * fRec10[0]))) + (fConst124 * fRec10[0])) + fConst122))) + (fConst120 * fRec10[0])) + fConst118)) + (fConst1 * (fRec8[0] * (((fRec8[0] * (fConst116 + (fConst114 * fRec10[0]))) + (fConst112 * fRec10[0])) + fConst110)))) + (fConst108 * fRec10[0]))))) + (fRec11[5] * ((((fRec9[0] * (((fConst1 * (fRec8[0] * (((fRec8[0] * (fConst43 + (fConst41 * fRec10[0]))) + (fConst39 * fRec10[0])) + fConst37))) + (fConst35 * fRec10[0])) + fConst33)) + (fConst1 * (fRec8[0] * (fConst31 + ((fRec8[0] * (fConst29 + (fConst27 * fRec10[0]))) + (fConst25 * fRec10[0])))))) + (fConst23 * fRec10[0])) + fConst21))) / fTemp1);
		fVec0[0] = fTemp2;
		fRec7[0] = ((fConst191 * (fVec0[0] + fVec0[1])) - (0.8605695850647829 * fRec7[1]));
		fRec6[0] = (fRec7[0] - ((1.8405051250752198 * fRec6[1]) + (0.8612942439318627 * fRec6[2])));
		fRec12[0] = ((fConst195 * fRec12[1]) + (fConst194 * (fRec5[1] + fRec5[2])));
		fRec5[0] = (Ftrany(TRANY_TABLE_KT88_68k, ((fRec12[0] + (0.9254498422517706 * (fRec6[2] + (fRec6[0] + (2.0 * fRec6[1]))))) - 5.562895)) - 43.96685185185183);
		fRec4[0] = ((fConst200 * fRec4[1]) + (fConst199 * ((fConst196 * fRec5[0]) + (fConst197 * fRec5[1]))));
		fRec3[0] = ((0.9302847925323914 * (fRec4[0] + fRec4[1])) - (0.8605695850647829 * fRec3[1]));
		fRec2[0] = (fRec3[0] - ((1.8405051250752198 * fRec2[1]) + (0.8612942439318627 * fRec2[2])));
		fRec13[0] = ((fConst195 * fRec13[1]) + (fConst194 * (fRec1[1] + fRec1[2])));
		fRec1[0] = (Ftrany(TRANY_TABLE_KT88_68k, ((fRec13[0] + (0.9254498422517706 * (fRec2[2] + (fRec2[0] + (2.0 * fRec2[1]))))) - 5.562895)) - 43.96685185185183);
		fRec0[0] = ((fConst200 * fRec0[1]) + (fConst199 * ((fConst196 * fRec1[0]) + (fConst197 * fRec1[1]))));
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
	reg.registerVar("cstbt1.wet_dry",N_("Wet/Dry"),"S",N_("percentage of processed signal in output signal"),&fslider0, 1e+02, 0.0, 1e+02, 1.0);
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
                        <property name=\"var_id\">cstbt1.Attack</property>\n\
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
                        <property name=\"var_id\">cstbt1.Tone</property>\n\
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
                        <property name=\"var_id\">cstbt1.Level</property>\n\
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
                        <property name=\"var_id\">cstbt1.wet_dry</property>\n\
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
                <property name=\"var_id\">cstbt1.Level</property>\n\
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

} // end namespace cstb
} // end namespace pluginlib
