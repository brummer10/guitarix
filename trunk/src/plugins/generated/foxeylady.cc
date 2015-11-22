// generated from file '../src/plugins/foxeylady.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"
#include "trany.h"

namespace pluginlib {
namespace foxeylady {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	FAUSTFLOAT 	fslider0;
	double 	fRec12[2];
	double 	fConst9;
	double 	fConst10;
	double 	fConst11;
	double 	fConst12;
	double 	fConst13;
	double 	fConst14;
	FAUSTFLOAT 	fslider1;
	double 	fRec13[2];
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
	double 	fRec14[7];
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
	double 	fVec0[2];
	double 	fConst78;
	double 	fConst79;
	double 	fConst80;
	double 	fRec11[2];
	double 	fRec10[3];
	double 	fConst81;
	double 	fConst82;
	double 	fConst83;
	double 	fConst84;
	double 	fRec15[2];
	double 	fRec9[3];
	double 	fConst85;
	double 	fConst86;
	double 	fConst87;
	double 	fConst88;
	double 	fConst89;
	double 	fRec8[2];
	double 	fConst90;
	double 	fRec7[2];
	double 	fRec6[3];
	double 	fRec16[2];
	double 	fRec5[3];
	double 	fRec4[2];
	double 	fRec3[2];
	double 	fRec2[3];
	double 	fRec17[2];
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
	id = "foxeylady";
	name = N_("Foxey Lady");
	groups = 0;
	description = N_("Foxey Lady fuzz pedal"); // description (tooltip)
	category = N_("Fuzz");       // category
	shortname = N_("Foxey Lady");     // shortname
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
	for (int i=0; i<7; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<3; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<3; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
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
	fConst7 = (5.24588897595767e-29 * fConst6);
	fConst8 = (6.94956080958259e-12 + (fConst6 * (1.71281273151154e-13 + (fConst6 * (1.29693461432975e-15 + (fConst6 * (3.61888994332083e-18 + (fConst6 * (2.89396306244108e-21 + (fConst6 * (7.02844574269719e-25 + fConst7)))))))))));
	fConst9 = (4.59387215604116e-29 * fConst6);
	fConst10 = ((fConst6 * ((fConst6 * ((fConst6 * ((fConst6 * (0 - (4.36933720361044e-25 + fConst9))) - 8.96539812308464e-22)) - 3.5938048928126e-19)) - 4.96738293767392e-17)) - 2.0568206880379e-15);
	fConst11 = (4.57704216569471e-29 * fConst6);
	fConst12 = ((fConst6 * ((fConst6 * ((fConst6 * (2.55877854891379e-22 + (fConst6 * (4.12221097685163e-25 + fConst11)))) - 9.9587457844786e-19)) - 4.94708666311112e-16)) - 7.32065571555064e-14);
	fConst13 = (3.28344197367049e-30 * fConst6);
	fConst14 = ((fConst6 * (4.33524374895714e-19 + (fConst6 * ((fConst6 * (1.8701619702637e-25 - fConst13)) - 2.16157324062859e-21)))) - 5.90848481409701e-18);
	fConst15 = (3.28344197367049e-28 * fConst6);
	fConst16 = ((fConst6 * (4.33524374895714e-17 + (fConst6 * ((fConst6 * (1.8701619702637e-23 - fConst15)) - 2.16157324062859e-19)))) - 5.90848481409701e-16);
	fConst17 = (6.42669378638762e-27 * fConst6);
	fConst18 = (4.84302033942378e-16 + (fConst6 * ((fConst6 * (1.79551930386446e-19 + (fConst6 * (fConst17 - 2.86240593005591e-23)))) - 3.55668379874028e-17)));
	fConst19 = (6.42669378638762e-29 * fConst6);
	fConst20 = (4.84302033942378e-18 + (fConst6 * ((fConst6 * (1.79551930386446e-21 + (fConst6 * (fConst19 - 2.86240593005591e-25)))) - 3.55668379874028e-19)));
	fConst21 = (6.94956080958259e-12 + (fConst6 * ((fConst6 * (1.29693461432975e-15 + (fConst6 * ((fConst6 * (2.89396306244108e-21 + (fConst6 * (fConst7 - 7.02844574269719e-25)))) - 3.61888994332083e-18)))) - 1.71281273151154e-13)));
	fConst22 = (2.0568206880379e-15 + (fConst6 * ((fConst6 * (3.5938048928126e-19 + (fConst6 * ((fConst6 * (4.36933720361044e-25 - fConst9)) - 8.96539812308464e-22)))) - 4.96738293767392e-17)));
	fConst23 = (7.32065571555064e-14 + (fConst6 * ((fConst6 * (9.9587457844786e-19 + (fConst6 * (2.55877854891379e-22 + (fConst6 * (fConst11 - 4.12221097685163e-25)))))) - 4.94708666311112e-16)));
	fConst24 = (3.1475333855746e-28 * fConst6);
	fConst25 = faustpower<2>(fConst6);
	fConst26 = (4.16973648574956e-11 + (fConst6 * ((fConst6 * (2.5938692286595e-15 + (fConst25 * ((fConst6 * (2.81137829707888e-24 - fConst24)) - 5.78792612488216e-21)))) - 6.85125092604618e-13)));
	fConst27 = (2.7563232936247e-28 * fConst6);
	fConst28 = (8.22728275215159e-15 + (fConst6 * ((fConst25 * (1.79307962461693e-21 + (fConst6 * (fConst27 - 1.74773488144418e-24)))) - 9.93476587534785e-17)));
	fConst29 = (2.74622529941683e-28 * fConst6);
	fConst30 = (2.92826228622026e-13 + (fConst6 * ((fConst25 * ((fConst6 * (1.64888439074065e-24 - fConst29)) - 5.11755709782759e-22)) - 9.89417332622223e-16)));
	fConst31 = (7.8688334639365e-28 * fConst6);
	fConst32 = (1.04243412143739e-10 + (fConst6 * ((fConst6 * ((fConst6 * (1.08566698299625e-17 + (fConst6 * ((fConst6 * (fConst31 - 3.51422287134859e-24)) - 2.89396306244108e-21)))) - 1.29693461432975e-15)) - 8.56406365755772e-13)));
	fConst33 = (6.89080823406175e-28 * fConst6);
	fConst34 = (1.02841034401895e-14 + (fConst6 * (4.96738293767392e-17 + (fConst6 * ((fConst6 * (8.96539812308464e-22 + (fConst6 * (2.18466860180522e-24 - fConst33)))) - 1.07814146784378e-18)))));
	fConst35 = (6.86556324854206e-28 * fConst6);
	fConst36 = (3.66032785777532e-13 + (fConst6 * (4.94708666311112e-16 + (fConst6 * ((fConst6 * ((fConst6 * (fConst35 - 2.06110548842582e-24)) - 2.55877854891379e-22)) - 2.98762373534358e-18)))));
	fConst37 = (1.38991216191652e-10 + (fConst25 * ((fConst25 * (1.15758522497643e-20 - (1.04917779519153e-27 * fConst25))) - 5.18773845731899e-15)));
	fConst38 = (1.98695317506957e-16 + (fConst25 * ((9.18774431208233e-28 * fConst25) - 3.58615924923386e-21)));
	fConst39 = (1.97883466524445e-15 + (fConst25 * (1.02351141956552e-21 - (9.15408433138942e-28 * fConst25))));
	fConst40 = (1.04243412143739e-10 + (fConst6 * (8.56406365755772e-13 + (fConst6 * ((fConst6 * ((fConst6 * ((fConst6 * (3.51422287134859e-24 + fConst31)) - 2.89396306244108e-21)) - 1.08566698299625e-17)) - 1.29693461432975e-15)))));
	fConst41 = ((fConst6 * (4.96738293767392e-17 + (fConst6 * (1.07814146784378e-18 + (fConst6 * (8.96539812308464e-22 + (fConst6 * (0 - (2.18466860180522e-24 + fConst33))))))))) - 1.02841034401895e-14);
	fConst42 = ((fConst6 * (4.94708666311112e-16 + (fConst6 * (2.98762373534358e-18 + (fConst6 * ((fConst6 * (2.06110548842582e-24 + fConst35)) - 2.55877854891379e-22)))))) - 3.66032785777532e-13);
	fConst43 = (4.16973648574956e-11 + (fConst6 * (6.85125092604618e-13 + (fConst6 * (2.5938692286595e-15 + (fConst25 * ((fConst6 * (0 - (2.81137829707888e-24 + fConst24))) - 5.78792612488216e-21)))))));
	fConst44 = ((fConst6 * ((fConst25 * (1.79307962461693e-21 + (fConst6 * (1.74773488144418e-24 + fConst27)))) - 9.93476587534785e-17)) - 8.22728275215159e-15);
	fConst45 = ((fConst6 * ((fConst25 * ((fConst6 * (0 - (1.64888439074065e-24 + fConst29))) - 5.11755709782759e-22)) - 9.89417332622223e-16)) - 2.92826228622026e-13);
	fConst46 = (1.97006518420229e-29 * fConst6);
	fConst47 = ((fConst25 * (4.32314648125718e-21 + (fConst6 * (fConst46 - 7.48064788105479e-25)))) - 1.1816969628194e-17);
	fConst48 = (1.97006518420229e-27 * fConst6);
	fConst49 = ((fConst25 * (4.32314648125718e-19 + (fConst6 * (fConst48 - 7.48064788105479e-23)))) - 1.1816969628194e-15);
	fConst50 = (3.85601627183257e-26 * fConst6);
	fConst51 = (9.68604067884756e-16 + (fConst25 * ((fConst6 * (1.14496237202237e-22 - fConst50)) - 3.59103860772892e-19)));
	fConst52 = (3.85601627183257e-28 * fConst6);
	fConst53 = (9.68604067884756e-18 + (fConst25 * ((fConst6 * (1.14496237202237e-24 - fConst52)) - 3.59103860772892e-21)));
	fConst54 = (4.92516296050573e-29 * fConst6);
	fConst55 = (5.90848481409701e-18 + (fConst6 * ((fConst6 * (2.16157324062859e-21 + (fConst6 * (9.35080985131849e-25 - fConst54)))) - 1.30057312468714e-18)));
	fConst56 = (4.92516296050573e-27 * fConst6);
	fConst57 = (5.90848481409701e-16 + (fConst6 * ((fConst6 * (2.16157324062859e-19 + (fConst6 * (9.35080985131849e-23 - fConst56)))) - 1.30057312468714e-16)));
	fConst58 = (9.64004067958143e-26 * fConst6);
	fConst59 = ((fConst6 * (1.06700513962208e-16 + (fConst6 * ((fConst6 * (fConst58 - 1.43120296502796e-22)) - 1.79551930386446e-19)))) - 4.84302033942378e-16);
	fConst60 = (9.64004067958143e-28 * fConst6);
	fConst61 = ((fConst6 * (1.06700513962208e-18 + (fConst6 * ((fConst6 * (fConst60 - 1.43120296502796e-24)) - 1.79551930386446e-21)))) - 4.84302033942378e-18);
	fConst62 = (2.3633939256388e-17 + (fConst25 * ((6.56688394734098e-29 * fConst25) - 8.64629296251435e-21)));
	fConst63 = (2.3633939256388e-15 + (fConst25 * ((6.56688394734098e-27 * fConst25) - 8.64629296251435e-19)));
	fConst64 = ((fConst25 * (7.18207721545784e-19 - (1.28533875727752e-25 * fConst25))) - 1.93720813576951e-15);
	fConst65 = ((fConst25 * (7.18207721545784e-21 - (1.28533875727752e-27 * fConst25))) - 1.93720813576951e-17);
	fConst66 = (5.90848481409701e-18 + (fConst6 * (1.30057312468714e-18 + (fConst6 * (2.16157324062859e-21 + (fConst6 * (0 - (9.35080985131849e-25 + fConst54))))))));
	fConst67 = (5.90848481409701e-16 + (fConst6 * (1.30057312468714e-16 + (fConst6 * (2.16157324062859e-19 + (fConst6 * (0 - (9.35080985131849e-23 + fConst56))))))));
	fConst68 = ((fConst6 * ((fConst6 * ((fConst6 * (1.43120296502796e-22 + fConst58)) - 1.79551930386446e-19)) - 1.06700513962208e-16)) - 4.84302033942378e-16);
	fConst69 = ((fConst6 * ((fConst6 * ((fConst6 * (1.43120296502796e-24 + fConst60)) - 1.79551930386446e-21)) - 1.06700513962208e-18)) - 4.84302033942378e-18);
	fConst70 = ((fConst25 * (4.32314648125718e-21 + (fConst6 * (7.48064788105479e-25 + fConst46)))) - 1.1816969628194e-17);
	fConst71 = ((fConst25 * (4.32314648125718e-19 + (fConst6 * (7.48064788105479e-23 + fConst48)))) - 1.1816969628194e-15);
	fConst72 = (9.68604067884756e-16 + (fConst25 * ((fConst6 * (0 - (1.14496237202237e-22 + fConst50))) - 3.59103860772892e-19)));
	fConst73 = (9.68604067884756e-18 + (fConst25 * ((fConst6 * (0 - (1.14496237202237e-24 + fConst52))) - 3.59103860772892e-21)));
	fConst74 = ((fConst6 * ((fConst6 * ((fConst6 * (0 - (1.8701619702637e-25 + fConst13))) - 2.16157324062859e-21)) - 4.33524374895714e-19)) - 5.90848481409701e-18);
	fConst75 = ((fConst6 * ((fConst6 * ((fConst6 * (0 - (1.8701619702637e-23 + fConst15))) - 2.16157324062859e-19)) - 4.33524374895714e-17)) - 5.90848481409701e-16);
	fConst76 = (4.84302033942378e-16 + (fConst6 * (3.55668379874028e-17 + (fConst6 * (1.79551930386446e-19 + (fConst6 * (2.86240593005591e-23 + fConst17)))))));
	fConst77 = (4.84302033942378e-18 + (fConst6 * (3.55668379874028e-19 + (fConst6 * (1.79551930386446e-21 + (fConst6 * (2.86240593005591e-25 + fConst19)))))));
	fConst78 = (1 + fConst3);
	fConst79 = (fConst25 / fConst78);
	fConst80 = (0 - ((1 - fConst3) / fConst78));
	fConst81 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst82 = (1 + fConst81);
	fConst83 = (0.027 / fConst82);
	fConst84 = (0 - ((1 - fConst81) / fConst82));
	fConst85 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst86 = (0 - fConst85);
	fConst87 = (1 + fConst85);
	fConst88 = (0.025 / fConst87);
	fConst89 = (0 - ((1 - fConst85) / fConst87));
	fConst90 = (1.0 / fConst78);
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
	for (int i=0; i<count; i++) {
		fRec12[0] = ((0.993 * fRec12[1]) + fSlow0);
		double fTemp0 = ((fRec12[0] * ((fConst6 * (fConst12 + (fConst10 * fRec12[0]))) - 3.1163949818756e-12)) + fConst8);
		fRec13[0] = ((0.993 * fRec13[1]) + fSlow1);
		fRec14[0] = ((double)input0[i] - (((((((fRec14[1] * ((fRec12[0] * ((fConst6 * (fConst45 + (fConst44 * fRec12[0]))) - 1.86983698912536e-11)) + fConst43)) + (fRec14[2] * ((fRec12[0] * ((fConst6 * (fConst42 + (fConst41 * fRec12[0]))) - 4.6745924728134e-11)) + fConst40))) + (fRec14[3] * ((fRec12[0] * ((fConst25 * (fConst39 + (fConst38 * fRec12[0]))) - 6.23278996375121e-11)) + fConst37))) + (fRec14[4] * ((fRec12[0] * ((fConst6 * (fConst36 + (fConst34 * fRec12[0]))) - 4.6745924728134e-11)) + fConst32))) + (fRec14[5] * ((fRec12[0] * ((fConst6 * (fConst30 + (fConst28 * fRec12[0]))) - 1.86983698912536e-11)) + fConst26))) + (fRec14[6] * ((fRec12[0] * ((fConst6 * (fConst23 + (fConst22 * fRec12[0]))) - 3.1163949818756e-12)) + fConst21))) / fTemp0));
		double fTemp1 = ((((((((fRec14[0] * (((fRec12[0] * (fConst77 + (fConst76 * fRec13[0]))) + (fConst75 * fRec13[0])) + fConst74)) + (fRec14[1] * (((fRec12[0] * (fConst73 + (fConst72 * fRec13[0]))) + (fConst71 * fRec13[0])) + fConst70))) + (fRec14[2] * (((fRec12[0] * (fConst69 + (fConst68 * fRec13[0]))) + (fConst67 * fRec13[0])) + fConst66))) + (fRec14[3] * (((fRec12[0] * (fConst65 + (fConst64 * fRec13[0]))) + (fConst63 * fRec13[0])) + fConst62))) + (fRec14[4] * (((fRec12[0] * (fConst61 + (fConst59 * fRec13[0]))) + (fConst57 * fRec13[0])) + fConst55))) + (fRec14[5] * (((fRec12[0] * (fConst53 + (fConst51 * fRec13[0]))) + (fConst49 * fRec13[0])) + fConst47))) + (fRec14[6] * (((fRec12[0] * (fConst20 + (fConst18 * fRec13[0]))) + (fConst16 * fRec13[0])) + fConst14))) / fTemp0);
		fVec0[0] = fTemp1;
		fRec11[0] = ((fConst80 * fRec11[1]) + (fConst79 * (fVec0[0] + fVec0[1])));
		fRec10[0] = (fRec11[0] - (fConst5 * ((fConst4 * fRec10[2]) + (fConst2 * fRec10[1]))));
		fRec15[0] = ((fConst84 * fRec15[1]) + (fConst83 * (fRec9[1] + fRec9[2])));
		fRec9[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec15[0] + (fConst5 * (fRec10[2] + (fRec10[0] + (2 * fRec10[1]))))) - 3.571981)) - 117.70440740740739);
		fRec8[0] = ((fConst89 * fRec8[1]) + (fConst88 * ((fConst85 * fRec9[0]) + (fConst86 * fRec9[1]))));
		fRec7[0] = ((fConst80 * fRec7[1]) + (fConst90 * (fRec8[0] + fRec8[1])));
		fRec6[0] = (fRec7[0] - (fConst5 * ((fConst4 * fRec6[2]) + (fConst2 * fRec6[1]))));
		fRec16[0] = ((fConst84 * fRec16[1]) + (fConst83 * (fRec5[1] + fRec5[2])));
		fRec5[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec16[0] + (fConst5 * (fRec6[2] + (fRec6[0] + (2 * fRec6[1]))))) - 3.571981)) - 117.70440740740739);
		fRec4[0] = ((fConst89 * fRec4[1]) + (fConst88 * ((fConst85 * fRec5[0]) + (fConst86 * fRec5[1]))));
		fRec3[0] = ((fConst80 * fRec3[1]) + (fConst90 * (fRec4[0] + fRec4[1])));
		fRec2[0] = (fRec3[0] - (fConst5 * ((fConst4 * fRec2[2]) + (fConst2 * fRec2[1]))));
		fRec17[0] = ((fConst84 * fRec17[1]) + (fConst83 * (fRec1[1] + fRec1[2])));
		fRec1[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec17[0] + (fConst5 * (fRec2[2] + (fRec2[0] + (2 * fRec2[1]))))) - 3.571981)) - 117.70440740740739);
		fRec0[0] = ((fConst89 * fRec0[1]) + (fConst88 * ((fConst85 * fRec1[0]) + (fConst86 * fRec1[1]))));
		output0[i] = (FAUSTFLOAT)fRec0[0];
		// post processing
		fRec0[1] = fRec0[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec17[1] = fRec17[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec16[1] = fRec16[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec15[1] = fRec15[0];
		fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		fVec0[1] = fVec0[0];
		for (int i=6; i>0; i--) fRec14[i] = fRec14[i-1];
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
	reg.registerVar("foxeylady.Fuzz",N_("Fuzz"),"S","",&fslider0, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("foxeylady.Level",N_("Level"),"S","",&fslider1, 0.5, 0.0, 1.0, 0.01);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("foxeylady" "." p)

b.openHorizontalhideBox("");
    b.create_master_slider(PARAM("Fuzz"), "Fuzz");
b.closeBox();
b.openHorizontalBox("");

    b.create_small_rackknobr(PARAM("Level"), "Level");

    b.create_small_rackknobr(PARAM("Fuzz"), "Fuzz");
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

} // end namespace foxeylady
} // end namespace pluginlib
