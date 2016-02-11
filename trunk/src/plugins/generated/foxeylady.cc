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
	double 	fRec2[7];
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
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<7; i++) fRec2[i] = 0;

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

}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = double(min(192000, max(1, fSamplingFreq)));
	fConst1 = (5.24588897595767e-29 * fConst0);
	fConst2 = (6.94956080958259e-12 + (fConst0 * (1.71281273151154e-13 + (fConst0 * (1.29693461432975e-15 + (fConst0 * (3.61888994332083e-18 + (fConst0 * (2.89396306244108e-21 + (fConst0 * (7.02844574269719e-25 + fConst1)))))))))));
	fConst3 = (4.59387215604116e-29 * fConst0);
	fConst4 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (0 - (4.36933720361044e-25 + fConst3))) - 8.96539812308464e-22)) - 3.5938048928126e-19)) - 4.96738293767392e-17)) - 2.0568206880379e-15);
	fConst5 = (4.57704216569471e-29 * fConst0);
	fConst6 = ((fConst0 * ((fConst0 * ((fConst0 * (2.55877854891379e-22 + (fConst0 * (4.12221097685163e-25 + fConst5)))) - 9.9587457844786e-19)) - 4.94708666311112e-16)) - 7.32065571555064e-14);
	fConst7 = (3.28344197367049e-30 * fConst0);
	fConst8 = ((fConst0 * (4.33524374895714e-19 + (fConst0 * ((fConst0 * (1.8701619702637e-25 - fConst7)) - 2.16157324062859e-21)))) - 5.90848481409701e-18);
	fConst9 = (3.28344197367049e-28 * fConst0);
	fConst10 = ((fConst0 * (4.33524374895714e-17 + (fConst0 * ((fConst0 * (1.8701619702637e-23 - fConst9)) - 2.16157324062859e-19)))) - 5.90848481409701e-16);
	fConst11 = (6.42669378638762e-27 * fConst0);
	fConst12 = (4.84302033942378e-16 + (fConst0 * ((fConst0 * (1.79551930386446e-19 + (fConst0 * (fConst11 - 2.86240593005591e-23)))) - 3.55668379874028e-17)));
	fConst13 = (6.42669378638762e-29 * fConst0);
	fConst14 = (4.84302033942378e-18 + (fConst0 * ((fConst0 * (1.79551930386446e-21 + (fConst0 * (fConst13 - 2.86240593005591e-25)))) - 3.55668379874028e-19)));
	fConst15 = (6.94956080958259e-12 + (fConst0 * ((fConst0 * (1.29693461432975e-15 + (fConst0 * ((fConst0 * (2.89396306244108e-21 + (fConst0 * (fConst1 - 7.02844574269719e-25)))) - 3.61888994332083e-18)))) - 1.71281273151154e-13)));
	fConst16 = (2.0568206880379e-15 + (fConst0 * ((fConst0 * (3.5938048928126e-19 + (fConst0 * ((fConst0 * (4.36933720361044e-25 - fConst3)) - 8.96539812308464e-22)))) - 4.96738293767392e-17)));
	fConst17 = (7.32065571555064e-14 + (fConst0 * ((fConst0 * (9.9587457844786e-19 + (fConst0 * (2.55877854891379e-22 + (fConst0 * (fConst5 - 4.12221097685163e-25)))))) - 4.94708666311112e-16)));
	fConst18 = (3.1475333855746e-28 * fConst0);
	fConst19 = faustpower<2>(fConst0);
	fConst20 = (4.16973648574956e-11 + (fConst0 * ((fConst0 * (2.5938692286595e-15 + (fConst19 * ((fConst0 * (2.81137829707888e-24 - fConst18)) - 5.78792612488216e-21)))) - 6.85125092604618e-13)));
	fConst21 = (2.7563232936247e-28 * fConst0);
	fConst22 = (8.22728275215159e-15 + (fConst0 * ((fConst19 * (1.79307962461693e-21 + (fConst0 * (fConst21 - 1.74773488144418e-24)))) - 9.93476587534785e-17)));
	fConst23 = (2.74622529941683e-28 * fConst0);
	fConst24 = (2.92826228622026e-13 + (fConst0 * ((fConst19 * ((fConst0 * (1.64888439074065e-24 - fConst23)) - 5.11755709782759e-22)) - 9.89417332622223e-16)));
	fConst25 = (7.8688334639365e-28 * fConst0);
	fConst26 = (1.04243412143739e-10 + (fConst0 * ((fConst0 * ((fConst0 * (1.08566698299625e-17 + (fConst0 * ((fConst0 * (fConst25 - 3.51422287134859e-24)) - 2.89396306244108e-21)))) - 1.29693461432975e-15)) - 8.56406365755772e-13)));
	fConst27 = (6.89080823406175e-28 * fConst0);
	fConst28 = (1.02841034401895e-14 + (fConst0 * (4.96738293767392e-17 + (fConst0 * ((fConst0 * (8.96539812308464e-22 + (fConst0 * (2.18466860180522e-24 - fConst27)))) - 1.07814146784378e-18)))));
	fConst29 = (6.86556324854206e-28 * fConst0);
	fConst30 = (3.66032785777532e-13 + (fConst0 * (4.94708666311112e-16 + (fConst0 * ((fConst0 * ((fConst0 * (fConst29 - 2.06110548842582e-24)) - 2.55877854891379e-22)) - 2.98762373534358e-18)))));
	fConst31 = (1.38991216191652e-10 + (fConst19 * ((fConst19 * (1.15758522497643e-20 - (1.04917779519153e-27 * fConst19))) - 5.18773845731899e-15)));
	fConst32 = (1.98695317506957e-16 + (fConst19 * ((9.18774431208233e-28 * fConst19) - 3.58615924923386e-21)));
	fConst33 = (1.97883466524445e-15 + (fConst19 * (1.02351141956552e-21 - (9.15408433138942e-28 * fConst19))));
	fConst34 = (1.04243412143739e-10 + (fConst0 * (8.56406365755772e-13 + (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (3.51422287134859e-24 + fConst25)) - 2.89396306244108e-21)) - 1.08566698299625e-17)) - 1.29693461432975e-15)))));
	fConst35 = ((fConst0 * (4.96738293767392e-17 + (fConst0 * (1.07814146784378e-18 + (fConst0 * (8.96539812308464e-22 + (fConst0 * (0 - (2.18466860180522e-24 + fConst27))))))))) - 1.02841034401895e-14);
	fConst36 = ((fConst0 * (4.94708666311112e-16 + (fConst0 * (2.98762373534358e-18 + (fConst0 * ((fConst0 * (2.06110548842582e-24 + fConst29)) - 2.55877854891379e-22)))))) - 3.66032785777532e-13);
	fConst37 = (4.16973648574956e-11 + (fConst0 * (6.85125092604618e-13 + (fConst0 * (2.5938692286595e-15 + (fConst19 * ((fConst0 * (0 - (2.81137829707888e-24 + fConst18))) - 5.78792612488216e-21)))))));
	fConst38 = ((fConst0 * ((fConst19 * (1.79307962461693e-21 + (fConst0 * (1.74773488144418e-24 + fConst21)))) - 9.93476587534785e-17)) - 8.22728275215159e-15);
	fConst39 = ((fConst0 * ((fConst19 * ((fConst0 * (0 - (1.64888439074065e-24 + fConst23))) - 5.11755709782759e-22)) - 9.89417332622223e-16)) - 2.92826228622026e-13);
	fConst40 = (1.97006518420229e-29 * fConst0);
	fConst41 = ((fConst19 * (4.32314648125718e-21 + (fConst0 * (fConst40 - 7.48064788105479e-25)))) - 1.1816969628194e-17);
	fConst42 = (1.97006518420229e-27 * fConst0);
	fConst43 = ((fConst19 * (4.32314648125718e-19 + (fConst0 * (fConst42 - 7.48064788105479e-23)))) - 1.1816969628194e-15);
	fConst44 = (3.85601627183257e-26 * fConst0);
	fConst45 = (9.68604067884756e-16 + (fConst19 * ((fConst0 * (1.14496237202237e-22 - fConst44)) - 3.59103860772892e-19)));
	fConst46 = (3.85601627183257e-28 * fConst0);
	fConst47 = (9.68604067884756e-18 + (fConst19 * ((fConst0 * (1.14496237202237e-24 - fConst46)) - 3.59103860772892e-21)));
	fConst48 = (4.92516296050573e-29 * fConst0);
	fConst49 = (5.90848481409701e-18 + (fConst0 * ((fConst0 * (2.16157324062859e-21 + (fConst0 * (9.35080985131849e-25 - fConst48)))) - 1.30057312468714e-18)));
	fConst50 = (4.92516296050573e-27 * fConst0);
	fConst51 = (5.90848481409701e-16 + (fConst0 * ((fConst0 * (2.16157324062859e-19 + (fConst0 * (9.35080985131849e-23 - fConst50)))) - 1.30057312468714e-16)));
	fConst52 = (9.64004067958143e-26 * fConst0);
	fConst53 = ((fConst0 * (1.06700513962208e-16 + (fConst0 * ((fConst0 * (fConst52 - 1.43120296502796e-22)) - 1.79551930386446e-19)))) - 4.84302033942378e-16);
	fConst54 = (9.64004067958143e-28 * fConst0);
	fConst55 = ((fConst0 * (1.06700513962208e-18 + (fConst0 * ((fConst0 * (fConst54 - 1.43120296502796e-24)) - 1.79551930386446e-21)))) - 4.84302033942378e-18);
	fConst56 = (2.3633939256388e-17 + (fConst19 * ((6.56688394734098e-29 * fConst19) - 8.64629296251435e-21)));
	fConst57 = (2.3633939256388e-15 + (fConst19 * ((6.56688394734098e-27 * fConst19) - 8.64629296251435e-19)));
	fConst58 = ((fConst19 * (7.18207721545784e-19 - (1.28533875727752e-25 * fConst19))) - 1.93720813576951e-15);
	fConst59 = ((fConst19 * (7.18207721545784e-21 - (1.28533875727752e-27 * fConst19))) - 1.93720813576951e-17);
	fConst60 = (5.90848481409701e-18 + (fConst0 * (1.30057312468714e-18 + (fConst0 * (2.16157324062859e-21 + (fConst0 * (0 - (9.35080985131849e-25 + fConst48))))))));
	fConst61 = (5.90848481409701e-16 + (fConst0 * (1.30057312468714e-16 + (fConst0 * (2.16157324062859e-19 + (fConst0 * (0 - (9.35080985131849e-23 + fConst50))))))));
	fConst62 = ((fConst0 * ((fConst0 * ((fConst0 * (1.43120296502796e-22 + fConst52)) - 1.79551930386446e-19)) - 1.06700513962208e-16)) - 4.84302033942378e-16);
	fConst63 = ((fConst0 * ((fConst0 * ((fConst0 * (1.43120296502796e-24 + fConst54)) - 1.79551930386446e-21)) - 1.06700513962208e-18)) - 4.84302033942378e-18);
	fConst64 = ((fConst19 * (4.32314648125718e-21 + (fConst0 * (7.48064788105479e-25 + fConst40)))) - 1.1816969628194e-17);
	fConst65 = ((fConst19 * (4.32314648125718e-19 + (fConst0 * (7.48064788105479e-23 + fConst42)))) - 1.1816969628194e-15);
	fConst66 = (9.68604067884756e-16 + (fConst19 * ((fConst0 * (0 - (1.14496237202237e-22 + fConst44))) - 3.59103860772892e-19)));
	fConst67 = (9.68604067884756e-18 + (fConst19 * ((fConst0 * (0 - (1.14496237202237e-24 + fConst46))) - 3.59103860772892e-21)));
	fConst68 = ((fConst0 * ((fConst0 * ((fConst0 * (0 - (1.8701619702637e-25 + fConst7))) - 2.16157324062859e-21)) - 4.33524374895714e-19)) - 5.90848481409701e-18);
	fConst69 = ((fConst0 * ((fConst0 * ((fConst0 * (0 - (1.8701619702637e-23 + fConst9))) - 2.16157324062859e-19)) - 4.33524374895714e-17)) - 5.90848481409701e-16);
	fConst70 = (4.84302033942378e-16 + (fConst0 * (3.55668379874028e-17 + (fConst0 * (1.79551930386446e-19 + (fConst0 * (2.86240593005591e-23 + fConst11)))))));
	fConst71 = (4.84302033942378e-18 + (fConst0 * (3.55668379874028e-19 + (fConst0 * (1.79551930386446e-21 + (fConst0 * (2.86240593005591e-25 + fConst13)))))));

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
	double 	fSlow0 = (0.007000000000000006 * (1 - double(fslider0)));
	double 	fSlow1 = (0.007000000000000006 * double(fslider1));
	for (int i=0; i<count; i++) {
		fRec0[0] = ((0.993 * fRec0[1]) + fSlow0);
		double fTemp0 = ((fRec0[0] * ((fConst0 * (fConst6 + (fConst4 * fRec0[0]))) - 3.1163949818756e-12)) + fConst2);
		fRec1[0] = ((0.993 * fRec1[1]) + fSlow1);
		fRec2[0] = ((double)input0[i] - (((((((fRec2[1] * ((fRec0[0] * ((fConst0 * (fConst39 + (fConst38 * fRec0[0]))) - 1.86983698912536e-11)) + fConst37)) + (fRec2[2] * ((fRec0[0] * ((fConst0 * (fConst36 + (fConst35 * fRec0[0]))) - 4.6745924728134e-11)) + fConst34))) + (fRec2[3] * ((fRec0[0] * ((fConst19 * (fConst33 + (fConst32 * fRec0[0]))) - 6.23278996375121e-11)) + fConst31))) + (fRec2[4] * ((fRec0[0] * ((fConst0 * (fConst30 + (fConst28 * fRec0[0]))) - 4.6745924728134e-11)) + fConst26))) + (fRec2[5] * ((fRec0[0] * ((fConst0 * (fConst24 + (fConst22 * fRec0[0]))) - 1.86983698912536e-11)) + fConst20))) + (fRec2[6] * ((fRec0[0] * ((fConst0 * (fConst17 + (fConst16 * fRec0[0]))) - 3.1163949818756e-12)) + fConst15))) / fTemp0));
		output0[i] = (FAUSTFLOAT)(fConst19 * ((((((((fRec2[0] * (((fRec0[0] * (fConst71 + (fConst70 * fRec1[0]))) + (fConst69 * fRec1[0])) + fConst68)) + (fRec2[1] * (((fRec0[0] * (fConst67 + (fConst66 * fRec1[0]))) + (fConst65 * fRec1[0])) + fConst64))) + (fRec2[2] * (((fRec0[0] * (fConst63 + (fConst62 * fRec1[0]))) + (fConst61 * fRec1[0])) + fConst60))) + (fRec2[3] * (((fRec0[0] * (fConst59 + (fConst58 * fRec1[0]))) + (fConst57 * fRec1[0])) + fConst56))) + (fRec2[4] * (((fRec0[0] * (fConst55 + (fConst53 * fRec1[0]))) + (fConst51 * fRec1[0])) + fConst49))) + (fRec2[5] * (((fRec0[0] * (fConst47 + (fConst45 * fRec1[0]))) + (fConst43 * fRec1[0])) + fConst41))) + (fRec2[6] * (((fRec0[0] * (fConst14 + (fConst12 * fRec1[0]))) + (fConst10 * fRec1[0])) + fConst8))) / fTemp0));
		// post processing
		for (int i=6; i>0; i--) fRec2[i] = fRec2[i-1];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
	}

	float bufCl[smpCl.max_out_count(count)];
	int ReCount = smpCl.up(count, output0, bufCl);
	for (int i=0; i<ReCount; i++) {
		double fTemp0 = (double)bufCl[i];
		fVecCl0[0] = fTemp0;
		fRecCl7[0] = ((0.9302847925323914 * (fVecCl0[0] + fVecCl0[1])) - (0.8605695850647829 * fRecCl7[1]));
		fRecCl6[0] = (fRecCl7[0] - ((1.8405051250752198 * fRecCl6[1]) + (0.8612942439318627 * fRecCl6[2])));
		fRecCl8[0] = ((fConstCl4 * fRecCl8[1]) + (fConstCl3 * (fRecCl5[1] + fRecCl5[2])));
		fRecCl5[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRecCl8[0] + (0.9254498422517706 * (fRecCl6[2] + (fRecCl6[0] + (2.0 * fRecCl6[1]))))) - 3.571981)) - 117.70440740740739);
		fRecCl4[0] = ((fConstCl9 * fRecCl4[1]) + (fConstCl8 * ((fConstCl5 * fRecCl5[0]) + (fConstCl6 * fRecCl5[1]))));
		fRecCl3[0] = ((0.9302847925323914 * (fRecCl4[0] + fRecCl4[1])) - (0.8605695850647829 * fRecCl3[1]));
		fRecCl2[0] = (fRecCl3[0] - ((1.8405051250752198 * fRecCl2[1]) + (0.8612942439318627 * fRecCl2[2])));
		fRecCl9[0] = ((fConstCl4 * fRecCl9[1]) + (fConstCl3 * (fRecCl1[1] + fRecCl1[2])));
		fRecCl1[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRecCl9[0] + (0.9254498422517706 * (fRecCl2[2] + (fRecCl2[0] + (2.0 * fRecCl2[1]))))) - 3.571981)) - 117.70440740740739);
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
                        <property name=\"var_id\">foxeylady.Fuzz</property>\n\
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
                      <object class=\"GxMidKnob\" id=\"gxbigknob2\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">foxeylady.Level</property>\n\
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
                <property name=\"var_id\">foxeylady.Fuzz</property>\n\
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
                <property name=\"label\" translatable=\"yes\">Fuzz</property>\n\
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

} // end namespace foxeylady
} // end namespace pluginlib
