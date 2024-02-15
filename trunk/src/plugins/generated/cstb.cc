// generated from file '../src/plugins/cstb.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

#include "trany.h"
#include <string.h>

namespace pluginlib {
namespace cstb {

class Dsp: public PluginDef {
private:
	int fSampleRate;
	FAUSTFLOAT fVslider0;
	double fRec0[2];
	double fConst0;
	double fConst2;
	double fConst4;
	double fConst6;
	double fConst8;
	double fConst10;
	double fConst12;
	double fConst14;
	double fConst16;
	double fConst17;
	double fConst19;
	FAUSTFLOAT fVslider1;
	double fRec1[2];
	double fConst20;
	FAUSTFLOAT fVslider2;
	double fRec2[2];
	double fConst22;
	double fConst23;
	double fConst25;
	double fConst26;
	double fConst27;
	double fConst29;
	double fConst30;
	double fConst32;
	double fConst33;
	double fConst34;
	double fConst36;
	double fConst38;
	double fConst39;
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
	double fConst55;
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
	double fConst81;
	double fConst83;
	double fConst85;
	double fConst87;
	double fConst89;
	double fConst90;
	double fConst91;
	double fConst92;
	double fConst93;
	double fConst94;
	double fConst95;
	double fConst96;
	double fConst97;
	double fConst98;
	double fConst99;
	double fConst100;
	double fConst101;
	double fConst102;
	double fConst103;
	double fConst104;
	double fConst105;
	double fConst106;
	double fConst107;
	double fRec3[6];
	double fConst109;
	double fConst110;
	double fConst111;
	double fConst113;
	double fConst114;
	double fConst116;
	double fConst118;
	double fConst119;
	double fConst120;
	double fConst122;
	double fConst123;
	double fConst125;
	double fConst126;
	double fConst128;
	double fConst130;
	double fConst131;
	double fConst132;
	double fConst134;
	double fConst135;
	double fConst137;
	double fConst138;
	double fConst140;
	double fConst142;
	double fConst143;
	double fConst144;
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


	gx_resample::FixedRateResampler smpCl;
	double fConstCl3;
	double fVecCl0[2];
	double fRecCl7[2];
	double fRecCl6[3];
	double fConstCl5;
	double fConstCl6;
	double fRecCl8[2];
	double fRecCl5[3];
	double fConstCl7;
	double fConstCl8;
	double fRecCl4[2];
	double fRecCl3[2];
	double fRecCl2[3];
	double fRecCl9[2];
	double fRecCl1[3];
	double fRecCl0[2];

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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec0[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec1[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec2[l2] = 0.0;
	for (int l3 = 0; l3 < 6; l3 = l3 + 1) fRec3[l3] = 0.0;

	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fVecCl0[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRecCl7[l1] = 0.0;
	for (int l2 = 0; l2 < 3; l2 = l2 + 1) fRecCl6[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRecCl8[l3] = 0.0;
	for (int l4 = 0; l4 < 3; l4 = l4 + 1) fRecCl5[l4] = 0.0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fRecCl4[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fRecCl3[l6] = 0.0;
	for (int l7 = 0; l7 < 3; l7 = l7 + 1) fRecCl2[l7] = 0.0;
	for (int l8 = 0; l8 < 2; l8 = l8 + 1) fRecCl9[l8] = 0.0;
	for (int l9 = 0; l9 < 3; l9 = l9 + 1) fRecCl1[l9] = 0.0;
	for (int l10 = 0; l10 < 2; l10 = l10 + 1) fRecCl0[l10] = 0.0;

}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = 7.2677502129384e-24 * fConst0;
	fConst2 = fConst0 * (fConst0 * (fConst0 * (-1.11622970892275e-19 - fConst1) + -5.44781387848185e-17) + -1.11859678983445e-15) + -2.16342879110166e-15;
	double fConst3 = 7.40213650437857e-24 * fConst0;
	fConst4 = fConst0 * (fConst0 * (fConst0 * (fConst3 + 1.13632945852435e-19) + 5.46818779890163e-17) + 1.12211896081664e-15);
	double fConst5 = 7.8746133025304e-22 * fConst0;
	fConst6 = fConst0 * (fConst0 * (fConst5 + 1.20886112608973e-17) + 5.81722106266131e-15);
	double fConst7 = 1.70008798003816e-23 * fConst0;
	fConst8 = fConst0 * (fConst0 * (fConst0 * (-2.35724702889288e-19 - fConst7) + -1.14989728218871e-16) + -2.52121869652107e-15) + -4.91241778179305e-15;
	double fConst9 = 1.73152391441475e-23 * fConst0;
	fConst10 = fConst0 * (fConst0 * (fConst0 * (fConst9 + 2.39957070065024e-19) + 1.15424860004575e-16) + 2.52915851496938e-15);
	double fConst11 = 1.8420467174625e-21 * fConst0;
	fConst12 = fConst0 * (fConst0 * (fConst11 + 2.55273478792579e-17) + 1.22792404260186e-14);
	double fConst13 = 1.72098866161537e-23 * fConst0;
	fConst14 = fConst0 * (fConst0 * (fConst13 + 2.43964228204556e-19) + 1.14222007971933e-16) + 2.45620889089652e-16;
	double fConst15 = 1.75281106567011e-23 * fConst0;
	fConst16 = fConst0 * (fConst0 * (-2.48347397038037e-19 - fConst15) + -1.14582451009122e-16);
	fConst17 = mydsp_faustpower2_f(fConst0);
	double fConst18 = 1.86469262305331e-21 * fConst0;
	fConst19 = fConst0 * (fConst0 * (fConst0 * (-2.64199358551104e-17 - fConst18) + -1.21896224477789e-14) + -2.62105472308353e-14);
	fConst20 = 9.67524227740541e-23 * fConst0;
	double fConst21 = 9.67524227740542e-20 * fConst0;
	fConst22 = 1.52102059347953e-17 - fConst21;
	fConst23 = mydsp_faustpower3_f(fConst0);
	double fConst24 = 8.18152886468203e-20 * fConst0;
	fConst25 = fConst24 + 3.32042567560148e-16;
	fConst26 = 8.18152886468203e-23 * fConst0;
	fConst27 = 7.69063713280111e-25 * fConst0;
	double fConst28 = 7.65662400320161e-24 * fConst0;
	fConst29 = fConst28 + 3.10739610519547e-20;
	fConst30 = 7.65662400320161e-27 * fConst0;
	double fConst31 = 7.69063713280111e-22 * fConst0;
	fConst32 = -3.12120013506539e-18 - fConst31;
	fConst33 = mydsp_faustpower4_f(fConst0);
	fConst34 = 9.05450478550042e-27 * fConst0;
	double fConst35 = 9.05450478550043e-24 * fConst0;
	fConst36 = 1.42343600786794e-21 - fConst35;
	double fConst37 = 9.09472774076109e-22 * fConst0;
	fConst38 = fConst37 + -1.42975935787076e-19;
	fConst39 = 9.09472774076109e-25 * fConst0;
	fConst40 = fConst4 + 2.17010750008645e-15;
	fConst41 = fConst6 + 1.19374357533685e-13;
	fConst42 = fConst10 + 4.92758287939703e-15;
	fConst43 = fConst12 + 2.69059416486104e-13;
	fConst44 = fConst16 + -2.46379143969851e-16;
	fConst45 = fConst0 * (fConst0 * (fConst0 * (fConst1 + -1.11622970892275e-19) + 5.44781387848185e-17) + -1.11859678983445e-15) + 2.16342879110166e-15;
	fConst46 = fConst0 * (fConst0 * (fConst0 * (1.13632945852435e-19 - fConst3) + -5.46818779890163e-17) + 1.12211896081664e-15) + -2.17010750008645e-15;
	fConst47 = fConst0 * (fConst0 * (fConst5 + -1.20886112608973e-17) + 5.81722106266131e-15) + -1.19374357533685e-13;
	fConst48 = fConst0 * (fConst0 * (fConst0 * (fConst7 + -2.35724702889288e-19) + 1.14989728218871e-16) + -2.52121869652107e-15) + 4.91241778179305e-15;
	fConst49 = fConst0 * (fConst0 * (fConst0 * (2.39957070065024e-19 - fConst9) + -1.15424860004575e-16) + 2.52915851496938e-15) + -4.92758287939703e-15;
	fConst50 = fConst0 * (fConst0 * (fConst11 + -2.55273478792579e-17) + 1.22792404260186e-14) + -2.69059416486104e-13;
	fConst51 = fConst0 * (fConst0 * (2.43964228204556e-19 - fConst13) + -1.14222007971933e-16) + 2.45620889089652e-16;
	fConst52 = fConst0 * (fConst0 * (fConst15 + -2.48347397038037e-19) + 1.14582451009122e-16) + -2.46379143969851e-16;
	fConst53 = fConst0 * (fConst0 * (fConst0 * (2.64199358551104e-17 - fConst18) + -1.21896224477789e-14) + 2.62105472308353e-14);
	double fConst54 = 3.6338751064692e-23 * fConst0;
	fConst55 = fConst0 * (fConst0 * (fConst0 * (3.34868912676825e-19 - fConst54) + -5.44781387848185e-17) + -1.11859678983445e-15) + 6.49028637330497e-15;
	double fConst56 = 3.70106825218929e-23 * fConst0;
	fConst57 = fConst0 * (fConst0 * (fConst0 * (fConst56 + -3.40898837557304e-19) + 5.46818779890163e-17) + 1.12211896081664e-15) + -6.51032250025936e-15;
	double fConst58 = 2.36238399075912e-21 * fConst0;
	fConst59 = fConst0 * (fConst0 * (1.20886112608973e-17 - fConst58) + 5.81722106266131e-15) + -3.58123072601056e-13;
	double fConst60 = 8.50043990019081e-23 * fConst0;
	fConst61 = fConst0 * (fConst0 * (fConst0 * (7.07174108667865e-19 - fConst60) + -1.14989728218871e-16) + -2.52121869652107e-15) + 1.47372533453791e-14;
	double fConst62 = 8.65761957207373e-23 * fConst0;
	fConst63 = fConst0 * (fConst0 * (fConst0 * (fConst62 + -7.19871210195072e-19) + 1.15424860004575e-16) + 2.52915851496938e-15) + -1.47827486381911e-14;
	double fConst64 = 5.52614015238749e-21 * fConst0;
	fConst65 = fConst0 * (fConst0 * (2.55273478792579e-17 - fConst64) + 1.22792404260186e-14) + -8.07178249458312e-13;
	double fConst66 = 8.60494330807685e-23 * fConst0;
	fConst67 = fConst0 * (fConst0 * (fConst66 + -7.31892684613668e-19) + 1.14222007971933e-16) + 2.45620889089652e-16;
	double fConst68 = 8.76405532835057e-23 * fConst0;
	fConst69 = fConst0 * (fConst0 * (7.45042191114112e-19 - fConst68) + -1.14582451009122e-16) + -2.46379143969851e-16;
	double fConst70 = 5.59407786915994e-21 * fConst0;
	fConst71 = fConst0 * (fConst0 * (fConst0 * (fConst70 + -2.64199358551104e-17) + -1.21896224477789e-14) + 7.86316416925058e-14);
	double fConst72 = 7.2677502129384e-23 * fConst0;
	fConst73 = fConst0 * (fConst0 * (fConst0 * (fConst72 + -2.2324594178455e-19) + -1.08956277569637e-16) + 2.2371935796689e-15) + 4.32685758220331e-15;
	double fConst74 = 7.40213650437857e-23 * fConst0;
	fConst75 = fConst0 * (fConst0 * (fConst0 * (2.27265891704869e-19 - fConst74) + 1.09363755978033e-16) + -2.24423792163328e-15) + -4.3402150001729e-15;
	double fConst76 = 1.57492266050608e-21 * fConst0;
	fConst77 = fConst0 * (fConst0 * (fConst76 + 2.41772225217946e-17) + -1.16344421253226e-14) + -2.3874871506737e-13;
	double fConst78 = 1.70008798003816e-22 * fConst0;
	fConst79 = fConst0 * (fConst0 * (fConst0 * (fConst78 + -4.71449405778577e-19) + -2.29979456437742e-16) + 5.04243739304215e-15) + 9.82483556358609e-15;
	double fConst80 = 1.73152391441475e-22 * fConst0;
	fConst81 = fConst0 * (fConst0 * (fConst0 * (4.79914140130048e-19 - fConst80) + 2.3084972000915e-16) + -5.05831702993876e-15) + -9.85516575879406e-15;
	double fConst82 = 3.68409343492499e-21 * fConst0;
	fConst83 = fConst0 * (fConst0 * (fConst82 + 5.10546957585158e-17) + -2.45584808520372e-14) + -5.38118832972208e-13;
	double fConst84 = 1.72098866161537e-22 * fConst0;
	fConst85 = fConst0 * (fConst0 * (4.87928456409112e-19 - fConst84) + 2.28444015943865e-16) + -4.91241778179304e-16;
	double fConst86 = 1.75281106567011e-22 * fConst0;
	fConst87 = fConst0 * (fConst0 * (fConst86 + -4.96694794076075e-19) + -2.29164902018244e-16) + 4.92758287939703e-16;
	double fConst88 = 3.72938524610662e-21 * fConst0;
	fConst89 = fConst0 * (fConst0 * (fConst0 * (-5.28398717102207e-17 - fConst88) + 2.43792448955579e-14) + 5.24210944616705e-14);
	fConst90 = fConst0 * (fConst0 * (fConst0 * (-2.2324594178455e-19 - fConst72) + 1.08956277569637e-16) + 2.2371935796689e-15) + -4.32685758220331e-15;
	fConst91 = fConst0 * (fConst0 * (fConst0 * (fConst74 + 2.27265891704869e-19) + -1.09363755978033e-16) + -2.24423792163328e-15) + 4.3402150001729e-15;
	fConst92 = fConst0 * (fConst0 * (fConst76 + -2.41772225217946e-17) + -1.16344421253226e-14) + 2.3874871506737e-13;
	fConst93 = fConst0 * (fConst0 * (fConst0 * (-4.71449405778577e-19 - fConst78) + 2.29979456437742e-16) + 5.04243739304215e-15) + -9.82483556358609e-15;
	fConst94 = fConst0 * (fConst0 * (fConst0 * (fConst80 + 4.79914140130048e-19) + -2.3084972000915e-16) + -5.05831702993876e-15) + 9.85516575879406e-15;
	fConst95 = fConst0 * (fConst0 * (fConst82 + -5.10546957585158e-17) + -2.45584808520372e-14) + 5.38118832972208e-13;
	fConst96 = fConst0 * (fConst0 * (fConst84 + 4.87928456409112e-19) + -2.28444015943865e-16) + -4.91241778179304e-16;
	fConst97 = fConst0 * (fConst0 * (-4.96694794076075e-19 - fConst86) + 2.29164902018244e-16) + 4.92758287939703e-16;
	fConst98 = fConst0 * (fConst0 * (fConst0 * (5.28398717102207e-17 - fConst88) + 2.43792448955579e-14) + -5.24210944616705e-14);
	fConst99 = fConst0 * (fConst0 * (fConst0 * (fConst54 + 3.34868912676825e-19) + 5.44781387848185e-17) + -1.11859678983445e-15) + -6.49028637330497e-15;
	fConst100 = fConst0 * (fConst0 * (fConst0 * (-3.40898837557304e-19 - fConst56) + -5.46818779890163e-17) + 1.12211896081664e-15) + 6.51032250025936e-15;
	fConst101 = fConst0 * (fConst0 * (-1.20886112608973e-17 - fConst58) + 5.81722106266131e-15) + 3.58123072601056e-13;
	fConst102 = fConst0 * (fConst0 * (fConst0 * (fConst60 + 7.07174108667865e-19) + 1.14989728218871e-16) + -2.52121869652107e-15) + -1.47372533453791e-14;
	fConst103 = fConst0 * (fConst0 * (fConst0 * (-7.19871210195072e-19 - fConst62) + -1.15424860004575e-16) + 2.52915851496938e-15) + 1.47827486381911e-14;
	fConst104 = fConst0 * (fConst0 * (-2.55273478792579e-17 - fConst64) + 1.22792404260186e-14) + 8.07178249458312e-13;
	fConst105 = fConst0 * (fConst0 * (-7.31892684613668e-19 - fConst66) + -1.14222007971933e-16) + 2.45620889089652e-16;
	fConst106 = fConst0 * (fConst0 * (fConst68 + 7.45042191114112e-19) + 1.14582451009122e-16) + -2.46379143969851e-16;
	fConst107 = fConst0 * (fConst0 * (fConst0 * (fConst70 + 2.64199358551104e-17) + -1.21896224477789e-14) + -7.86316416925058e-14);
	double fConst108 = 2.90257268322162e-19 * fConst0;
	fConst109 = fConst108 + -1.52102059347953e-17;
	fConst110 = 2.90257268322162e-22 * fConst0;
	fConst111 = 2.45445865940461e-22 * fConst0;
	double fConst112 = 2.45445865940461e-19 * fConst0;
	fConst113 = -3.32042567560148e-16 - fConst112;
	fConst114 = 3.82831200160081e-26 * fConst0;
	double fConst115 = 3.82831200160081e-23 * fConst0;
	fConst116 = -9.3221883155864e-20 - fConst115;
	double fConst117 = 3.84531856640056e-21 * fConst0;
	fConst118 = fConst117 + 9.36360040519619e-18;
	fConst119 = 3.84531856640056e-24 * fConst0;
	fConst120 = 4.54736387038055e-24 * fConst0;
	double fConst121 = 4.52725239275021e-23 * fConst0;
	fConst122 = fConst121 + -4.27030802360382e-21;
	fConst123 = 4.52725239275021e-26 * fConst0;
	double fConst124 = 4.54736387038055e-21 * fConst0;
	fConst125 = 4.28927807361227e-19 - fConst124;
	fConst126 = 1.93504845548108e-22 * fConst0;
	double fConst127 = 1.93504845548108e-19 * fConst0;
	fConst128 = -3.04204118695905e-17 - fConst127;
	double fConst129 = 1.63630577293641e-19 * fConst0;
	fConst130 = fConst129 + -6.64085135120297e-16;
	fConst131 = 1.63630577293641e-22 * fConst0;
	fConst132 = 7.69063713280111e-24 * fConst0;
	double fConst133 = 7.65662400320161e-23 * fConst0;
	fConst134 = fConst133 + 6.21479221039094e-20;
	fConst135 = 7.65662400320161e-26 * fConst0;
	double fConst136 = 7.69063713280111e-21 * fConst0;
	fConst137 = -6.24240027013079e-18 - fConst136;
	fConst138 = 9.05450478550042e-26 * fConst0;
	double fConst139 = 9.05450478550042e-23 * fConst0;
	fConst140 = 2.84687201573588e-21 - fConst139;
	double fConst141 = 9.09472774076109e-21 * fConst0;
	fConst142 = fConst141 + -2.85951871574151e-19;
	fConst143 = 9.09472774076109e-24 * fConst0;
	fConst144 = 3.04204118695905e-17 - fConst127;
	fConst145 = fConst129 + 6.64085135120297e-16;
	fConst146 = 6.21479221039094e-20 - fConst133;
	fConst147 = fConst136 + -6.24240027013079e-18;
	fConst148 = fConst139 + 2.84687201573588e-21;
	fConst149 = -2.85951871574151e-19 - fConst141;
	fConst150 = fConst108 + 1.52102059347953e-17;
	fConst151 = 3.32042567560148e-16 - fConst112;
	fConst152 = fConst115 + -9.3221883155864e-20;
	fConst153 = 9.36360040519619e-18 - fConst117;
	fConst154 = -4.27030802360382e-21 - fConst121;
	fConst155 = fConst124 + 4.28927807361227e-19;
	fConst156 = -1.52102059347953e-17 - fConst21;
	fConst157 = fConst24 + -3.32042567560148e-16;
	fConst158 = 3.10739610519547e-20 - fConst28;
	fConst159 = fConst31 + -3.12120013506539e-18;
	fConst160 = fConst35 + 1.42343600786794e-21;
	fConst161 = -1.42975935787076e-19 - fConst37;

	sample_rate = 96000;
	smpCl.setup(fSampleRate, sample_rate);
	fSampleRate = sample_rate;
	double fConstCl0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	double fConstCl1 = std::tan(97.38937226128358 / fConstCl0);
	double fConstCl2 = 1.0 / fConstCl1;
	fConstCl3 = 1.0 - fConstCl2;
	double fConstCl4 = 1.0 / std::tan(270.1769682087222 / fConstCl0);
	fConstCl5 = 1.0 - fConstCl4;
	fConstCl6 = 1.0 / (fConstCl4 + 1.0);
	fConstCl7 = 0.025 / fConstCl1;
	fConstCl8 = 1.0 / (fConstCl2 + 1.0);

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

	double fSlow0 = 0.007000000000000006 * double(fVslider0);
	double fSlow1 = 0.007000000000000006 * double(fVslider1);
	double fSlow2 = 0.007000000000000006 * double(fVslider2);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec0[0] = fSlow0 + 0.993 * fRec0[1];
		double fTemp0 = fConst2 * fRec0[0];
		double fTemp1 = fConst8 * fRec0[0];
		double fTemp2 = fConst14 * fRec0[0];
		fRec1[0] = fSlow1 + 0.993 * fRec1[1];
		fRec2[0] = fSlow2 + 0.993 * fRec2[1];
		fRec3[0] = double(input0[i0]) - (fRec3[1] * (fRec1[0] * (fRec1[0] * (fConst107 + fConst17 * fRec0[0] * (fConst106 + fConst105 * fRec0[0])) + fConst0 * (fConst104 + fRec0[0] * (fConst103 + fConst102 * fRec0[0])) + 2.62105472308353e-12) + fConst0 * (fConst101 + fRec0[0] * (fConst100 + fConst99 * fRec0[0])) + 1.15431250004598e-12) + fRec3[2] * (fRec1[0] * (fRec1[0] * (fConst98 + fConst17 * fRec0[0] * (fConst97 + fConst96 * fRec0[0])) + fConst0 * (fConst95 + fRec0[0] * (fConst94 + fConst93 * fRec0[0])) + 5.24210944616705e-12) + fConst0 * (fConst92 + fRec0[0] * (fConst91 + fConst90 * fRec0[0])) + 2.30862500009197e-12) + fRec3[3] * (fRec1[0] * (fRec1[0] * (fConst89 + fConst17 * fRec0[0] * (fConst87 + fConst85 * fRec0[0])) + fConst0 * (fConst83 + fRec0[0] * (fConst81 + fConst79 * fRec0[0])) + 5.24210944616705e-12) + fConst0 * (fConst77 + fRec0[0] * (fConst75 + fConst73 * fRec0[0])) + 2.30862500009197e-12) + fRec3[4] * (fRec1[0] * (fRec1[0] * (fConst71 + fConst17 * fRec0[0] * (fConst69 + fConst67 * fRec0[0])) + fConst0 * (fConst65 + fRec0[0] * (fConst63 + fConst61 * fRec0[0])) + 2.62105472308353e-12) + fConst0 * (fConst59 + fRec0[0] * (fConst57 + fConst55 * fRec0[0])) + 1.15431250004598e-12) + fRec3[5] * (fRec1[0] * (fRec1[0] * (fConst53 + fConst17 * fRec0[0] * (fConst52 + fConst51 * fRec0[0])) + fConst0 * (fConst50 + fRec0[0] * (fConst49 + fConst48 * fRec0[0])) + 5.24210944616705e-13) + fConst0 * (fConst47 + fRec0[0] * (fConst46 + fConst45 * fRec0[0])) + 2.30862500009197e-13)) / (fRec1[0] * (fRec1[0] * (fConst19 + fConst17 * fRec0[0] * (fConst44 + fTemp2)) + fConst0 * (fConst43 + fRec0[0] * (fConst42 + fTemp1)) + 5.24210944616705e-13) + fConst0 * (fConst41 + fRec0[0] * (fConst40 + fTemp0)) + 2.30862500009197e-13);
		output0[i0] = FAUSTFLOAT((fRec3[0] * (fConst33 * fRec0[0] * (fConst161 * fRec2[0] + fRec0[0] * (fConst34 + fConst160 * fRec2[0] + 1.42343600786794e-24) + -1.42975935787076e-22 - fConst39) + fRec1[0] * (fConst33 * fRec0[0] * (fConst27 + fConst159 * fRec2[0] + fRec0[0] * (fConst158 * fRec2[0] + 3.10739610519547e-23 - fConst30) + -3.1212001350654e-21) + fConst23 * (fConst26 + fConst157 * fRec2[0] + -3.32042567560148e-19)) + fConst23 * (fConst156 * fRec2[0] + -1.52102059347953e-20 - fConst20)) + fRec3[1] * (fConst33 * fRec0[0] * (fConst120 + fConst155 * fRec2[0] + fRec0[0] * (fConst154 * fRec2[0] + -4.27030802360382e-24 - fConst123) + 4.28927807361227e-22) + fRec1[0] * (fConst33 * fRec0[0] * (fConst153 * fRec2[0] + fRec0[0] * (fConst114 + fConst152 * fRec2[0] + -9.3221883155864e-23) + 9.36360040519619e-21 - fConst119) + fConst23 * (fConst151 * fRec2[0] + 3.32042567560148e-19 - fConst111)) + fConst23 * (fConst110 + fConst150 * fRec2[0] + 1.52102059347953e-20)) + fRec3[2] * (fConst33 * fRec0[0] * (fConst149 * fRec2[0] + fRec0[0] * (fConst138 + fConst148 * fRec2[0] + 2.84687201573588e-24) + -2.85951871574151e-22 - fConst143) + fRec1[0] * (fConst33 * fRec0[0] * (fConst132 + fConst147 * fRec2[0] + fRec0[0] * (fConst146 * fRec2[0] + 6.21479221039094e-23 - fConst135) + -6.24240027013079e-21) + fConst23 * (fConst131 + fConst145 * fRec2[0] + 6.64085135120297e-19)) + fConst23 * (fConst144 * fRec2[0] + 3.04204118695905e-20 - fConst126)) + fRec3[3] * (fConst33 * fRec0[0] * (fConst143 + fConst142 * fRec2[0] + fRec0[0] * (fConst140 * fRec2[0] + 2.84687201573588e-24 - fConst138) + -2.85951871574151e-22) + fRec1[0] * (fConst33 * fRec0[0] * (fConst137 * fRec2[0] + fRec0[0] * (fConst135 + fConst134 * fRec2[0] + 6.21479221039094e-23) + -6.24240027013079e-21 - fConst132) + fConst23 * (fConst131 + fConst130 * fRec2[0] + -6.64085135120297e-19)) + fConst23 * (fConst128 * fRec2[0] + -3.04204118695905e-20 - fConst126)) + fRec3[4] * (fConst33 * fRec0[0] * (fConst125 * fRec2[0] + fRec0[0] * (fConst123 + fConst122 * fRec2[0] + -4.27030802360382e-24) + 4.28927807361227e-22 - fConst120) + fRec1[0] * (fConst33 * fRec0[0] * (fConst119 + fConst118 * fRec2[0] + fRec0[0] * (fConst116 * fRec2[0] + -9.3221883155864e-23 - fConst114) + 9.36360040519619e-21) + fConst23 * (fConst113 * fRec2[0] + -3.32042567560148e-19 - fConst111)) + fConst23 * (fConst110 + fConst109 * fRec2[0] + -1.52102059347953e-20)) + fRec3[5] * (fConst33 * fRec0[0] * (fConst39 + fConst38 * fRec2[0] + fRec0[0] * (fConst36 * fRec2[0] + 1.42343600786794e-24 - fConst34) + -1.42975935787076e-22) + fRec1[0] * (fConst33 * fRec0[0] * (fConst32 * fRec2[0] + fRec0[0] * (fConst30 + fConst29 * fRec2[0] + 3.10739610519547e-23) + -3.1212001350654e-21 - fConst27) + fConst23 * (fConst26 + fConst25 * fRec2[0] + 3.32042567560148e-19)) + fConst23 * (fConst22 * fRec2[0] + 1.52102059347953e-20 - fConst20))) / (fRec1[0] * (fRec1[0] * (fConst19 + fConst17 * fRec0[0] * (fConst16 + fTemp2 + -2.46379143969851e-16)) + fConst0 * (fConst12 + fRec0[0] * (fConst10 + fTemp1 + 4.92758287939703e-15) + 2.69059416486104e-13) + 5.24210944616705e-13) + fConst0 * (fConst6 + fRec0[0] * (fConst4 + fTemp0 + 2.17010750008645e-15) + 1.19374357533685e-13) + 2.30862500009197e-13));
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		for (int j0 = 5; j0 > 0; j0 = j0 - 1) {
			fRec3[j0] = fRec3[j0 - 1];
		}
	}

	FAUSTFLOAT bufCl[smpCl.max_out_count(count)];
	int ReCount = smpCl.up(count, output0, bufCl);
	for (int i0 = 0; i0 < ReCount; i0 = i0 + 1) {
		double fTemp0 = double(bufCl[i0]);
		fVecCl0[0] = fTemp0;
		fRecCl7[0] = 0.9302847925323914 * (fTemp0 + fVecCl0[1]) - 0.8605695850647829 * fRecCl7[1];
		fRecCl6[0] = fRecCl7[0] - (1.8405051250752198 * fRecCl6[1] + 0.8612942439318627 * fRecCl6[2]);
		fRecCl8[0] = fConstCl6 * (0.027 * (fRecCl5[1] + fRecCl5[2]) - fConstCl5 * fRecCl8[1]);
		fRecCl5[0] = Ftrany(TRANY_TABLE_7199P_68k, 0.9254498422517706 * (fRecCl6[0] + fRecCl6[2]) + fRecCl8[0] + 1.8508996845035413 * fRecCl6[1] + -3.571981) + -117.70440740740739;
		fRecCl4[0] = fConstCl8 * (fConstCl7 * (fRecCl5[0] - fRecCl5[1]) - fConstCl3 * fRecCl4[1]);
		fRecCl3[0] = 0.9302847925323914 * (fRecCl4[0] + fRecCl4[1]) - 0.8605695850647829 * fRecCl3[1];
		fRecCl2[0] = fRecCl3[0] - (1.8405051250752198 * fRecCl2[1] + 0.8612942439318627 * fRecCl2[2]);
		fRecCl9[0] = fConstCl6 * (0.027 * (fRecCl1[1] + fRecCl1[2]) - fConstCl5 * fRecCl9[1]);
		fRecCl1[0] = Ftrany(TRANY_TABLE_7199P_68k, 0.9254498422517706 * (fRecCl2[0] + fRecCl2[2]) + fRecCl9[0] + 1.8508996845035413 * fRecCl2[1] + -3.571981) + -117.70440740740739;
		fRecCl0[0] = fConstCl8 * (fConstCl7 * (fRecCl1[0] - fRecCl1[1]) - fConstCl3 * fRecCl0[1]);
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
		output0[i] = ((fSlowdw1 * (double)dryinput[i]) + (fSlowdw0 * (double)output0[i]));
	}

}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerFloatVar("cstbt1.wet_dry",N_("Dry/Wet"),"S",N_("percentage of processed signal in output signal"),&fsliderdw0, 1e+02, 0.0, 1e+02, 1.0, 0);
	reg.registerFloatVar("cstbt1.Attack",N_("Attack"),"S","",&fVslider0, 0.5, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("cstbt1.Level",N_("Level"),"S","",&fVslider2, 0.5, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("cstbt1.Tone",N_("Tone"),"S","",&fVslider1, 0.5, 0.0, 1.0, 0.01, 0);
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
