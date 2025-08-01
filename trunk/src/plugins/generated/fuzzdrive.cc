// generated from file '../src/plugins/fuzzdrive.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"
#include "clipping.h"

namespace pluginlib {
namespace fuzzdrive {

class Dsp: public PluginDef {
private:
	int fSampleRate;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT fVslider1;
	double fRec0[2];
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	double fConst4;
	double fConst5;
	double fConst6;
	double fConst7;
	double fConst8;
	double fConst9;
	double fConst10;
	double fConst11;
	double fConst12;
	double fConst13;
	double fConst14;
	double fConst15;
	double fConst16;
	double fConst17;
	double fConst18;
	double fConst19;
	double fConst20;
	double fConst21;
	double fConst22;
	double fConst23;
	double fConst24;
	double fConst25;
	double fConst26;
	double fConst27;
	double fConst28;
	double fConst29;
	double fConst30;
	double fConst31;
	double fConst32;
	double fConst33;
	double fConst34;
	double fConst35;
	double fConst36;
	double fConst37;
	double fConst38;
	double fRec2[9];
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
	double fConst54;
	double fConst55;
	double fRec1[4];
	double fConst56;
	double fConst57;
	double fConst58;
	double fConst59;
	double fConst60;
	FAUSTFLOAT fHslider0;
	double fRec3[2];

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
	id = "fuzzdrive";
	name = N_("Fuzz Drive");
	groups = 0;
	description = N_("Fuzz Distortion"); // description (tooltip)
	category = N_("Fuzz");       // category
	shortname = N_("Fuzz Drive");     // shortname
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
	for (int l1 = 0; l1 < 9; l1 = l1 + 1) fRec2[l1] = 0.0;
	for (int l2 = 0; l2 < 4; l2 = l2 + 1) fRec1[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec3[l3] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = 1.2099049942893e-14 * fConst0;
	fConst2 = fConst0 * (fConst1 + 2.51801622165627e-10) + 2.49252253398618e-08;
	fConst3 = 3.57407648445144e-16 * fConst0;
	fConst4 = fConst0 * (fConst3 + 2.81736895109737e-13) + 2.53046873750701e-09;
	fConst5 = mydsp_faustpower3_f(fConst0);
	fConst6 = 3.4535791768961205e-14 * fConst5;
	fConst7 = 1.79347857986842e-13 * fConst0;
	fConst8 = mydsp_faustpower2_f(fConst0);
	fConst9 = 0.1 * fConst8 * (3.45357917689612e-12 - fConst7);
	fConst10 = fConst0 * (2.51801622165627e-10 - fConst1) + -2.49252253398618e-08;
	fConst11 = fConst0 * (2.81736895109737e-13 - fConst3) + -2.53046873750701e-09;
	fConst12 = 3.62971498286789e-14 * fConst0;
	fConst13 = fConst0 * (fConst12 + -2.51801622165627e-10) + -2.49252253398618e-08;
	fConst14 = 1.07222294533543e-15 * fConst0;
	fConst15 = fConst0 * (fConst14 + -2.81736895109737e-13) + -2.53046873750701e-09;
	fConst16 = fConst0 * (-2.51801622165627e-10 - fConst12) + 2.49252253398618e-08;
	fConst17 = fConst0 * (-2.81736895109737e-13 - fConst14) + 2.53046873750701e-09;
	fConst18 = 1.21134747730432e-39 * fConst0;
	fConst19 = 2.45020046020493e-40 * fConst0;
	fConst20 = 1.20954612086615e-39 * fConst0;
	fConst21 = 0.5 * (0.5 * fConst8 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (2.86589792702458e-34 - fConst20) + -6.29844123704863e-30) + 6.96590249983833e-27) + -2.97472992156056e-24) + 4.85407145719168e-22) + -2.26821940920998e-20) + fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst19 + 1.12017008405057e-33) + -2.68390877243249e-29) + 2.76343706770825e-26) + -1.93946085329172e-23) + 8.29607943811672e-21) + -1.41480755159492e-18) + 6.87339214912114e-17)) + fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst18 + -1.63282987404348e-33) + 4.4344097371444e-29) + -1.07298568411666e-25) + 1.73266579347222e-22) + -1.31102852092565e-19) + 4.74767687606168e-17) + -7.12034665177176e-15) + 3.12426915869143e-13;
	fConst22 = 9.69077981843452e-39 * fConst0;
	fConst23 = 1.96016036816394e-39 * fConst0;
	fConst24 = 9.6763689669292e-39 * fConst0;
	fConst25 = 0.5 * (0.5 * fConst8 * (fConst0 * (fConst8 * (fConst0 * (fConst0 * (fConst24 + -1.71953875621475e-33) + 2.51937649481945e-29) + -1.39318049996767e-26) + 9.70814291438336e-22) + -9.0728776368399e-20) + fConst0 * (fConst0 * (fConst0 * (fConst8 * (fConst0 * (fConst0 * (-6.7210205043034e-33 - fConst23) + 1.073563508973e-28) + -5.52687413541649e-26) + 1.65921588762334e-20) + -5.65923020637969e-18) + 4.12403528947268e-16)) + fConst0 * (fConst0 * (fConst0 * (fConst8 * (fConst0 * (fConst0 * (9.79697924426087e-33 - fConst22) + -1.77376389485776e-28) + 2.14597136823331e-25) + -2.62205704185131e-19) + 1.89907075042467e-16) + -4.27220799106305e-14) + 2.49941532695314e-12;
	fConst26 = 3.39177293645208e-38 * fConst0;
	fConst27 = 6.86056128857379e-39 * fConst0;
	fConst28 = 3.38672913842522e-38 * fConst0;
	fConst29 = 0.5 * (0.5 * fConst8 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (4.01225709783442e-33 - fConst28) + -2.51937649481945e-29) + -1.39318049996767e-26) + 1.18989196862423e-23) + -9.70814291438336e-22) + -9.0728776368399e-20) + fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst27 + 1.56823811767079e-32) + -1.073563508973e-28) + -5.52687413541649e-26) + 7.75784341316688e-23) + -1.65921588762334e-20) + -5.65923020637969e-18) + 9.62274900876959e-16)) + fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst26 + -2.28596182366087e-32) + 1.77376389485776e-28) + 2.14597136823331e-25) + -6.93066317388889e-22) + 2.62205704185131e-19) + 1.89907075042467e-16) + -9.96848531248046e-14) + 8.74795364433599e-12;
	fConst30 = 6.78354587290416e-38 * fConst0;
	fConst31 = 1.37211225771476e-38 * fConst0;
	fConst32 = 6.77345827685044e-38 * fConst0;
	fConst33 = 0.5 * (0.5 * fConst8 * (fConst0 * (fConst8 * (fConst0 * (fConst0 * (fConst32 + -4.01225709783442e-33) + -2.51937649481945e-29) + 4.179541499903e-26) + -2.91244287431501e-21) + 9.0728776368399e-20) + fConst0 * (fConst0 * (fConst0 * (fConst8 * (fConst0 * (fConst0 * (-1.56823811767079e-32 - fConst31) + -1.073563508973e-28) + 1.65806224062495e-25) + -4.97764766287003e-20) + 5.65923020637969e-18) + 9.62274900876959e-16)) + fConst0 * (fConst0 * (fConst0 * (fConst8 * (fConst0 * (fConst0 * (2.28596182366087e-32 - fConst30) + 1.77376389485776e-28) + -6.43791410469994e-25) + 7.86617112555392e-19) + -1.89907075042467e-16) + -9.96848531248046e-14) + 1.7495907288672e-11;
	fConst34 = fConst8 * (fConst8 * (fConst8 * (8.47943234113021e-38 * fConst8 + -4.4344097371444e-28) + 1.03959947608333e-21) + -4.74767687606168e-16 + 0.5 * (fConst8 * (fConst8 * (1.71514032214345e-38 * fConst8 + 2.68390877243249e-28) + -1.16367651197503e-22) + 1.41480755159492e-17 + 0.5 * (fConst8 * (fConst8 * (6.29844123704863e-29 - 8.46682284606305e-38 * fConst8) + -1.78483795293634e-23) + 2.26821940920998e-19))) + 2.186988411084e-11;
	fConst35 = 0.5 * (0.5 * fConst8 * (fConst0 * (fConst8 * (fConst0 * (fConst0 * (fConst32 + 4.01225709783442e-33) + -2.51937649481945e-29) + -4.179541499903e-26) + 2.91244287431501e-21) + 9.0728776368399e-20) + fConst0 * (fConst0 * (fConst0 * (fConst8 * (fConst0 * (fConst0 * (1.56823811767079e-32 - fConst31) + -1.073563508973e-28) + -1.65806224062495e-25) + 4.97764766287003e-20) + 5.65923020637969e-18) + -9.62274900876959e-16)) + fConst0 * (fConst0 * (fConst0 * (fConst8 * (fConst0 * (fConst0 * (-2.28596182366087e-32 - fConst30) + 1.77376389485776e-28) + 6.43791410469994e-25) + -7.86617112555392e-19) + -1.89907075042467e-16) + 9.96848531248046e-14) + 1.7495907288672e-11;
	fConst36 = 0.5 * (0.5 * fConst8 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (-4.01225709783442e-33 - fConst28) + -2.51937649481945e-29) + 1.39318049996767e-26) + 1.18989196862423e-23) + 9.70814291438336e-22) + -9.0728776368399e-20) + fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst27 + -1.56823811767079e-32) + -1.073563508973e-28) + 5.52687413541649e-26) + 7.75784341316688e-23) + 1.65921588762334e-20) + -5.65923020637969e-18) + -9.62274900876959e-16)) + fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst26 + 2.28596182366087e-32) + 1.77376389485776e-28) + -2.14597136823331e-25) + -6.93066317388889e-22) + -2.62205704185131e-19) + 1.89907075042467e-16) + 9.96848531248046e-14) + 8.74795364433599e-12;
	fConst37 = 0.5 * (0.5 * fConst8 * (fConst0 * (fConst8 * (fConst0 * (fConst0 * (fConst24 + 1.71953875621475e-33) + 2.51937649481945e-29) + 1.39318049996767e-26) + -9.70814291438336e-22) + -9.0728776368399e-20) + fConst0 * (fConst0 * (fConst0 * (fConst8 * (fConst0 * (fConst0 * (6.7210205043034e-33 - fConst23) + 1.073563508973e-28) + 5.52687413541649e-26) + -1.65921588762334e-20) + -5.65923020637969e-18) + -4.12403528947268e-16)) + fConst0 * (fConst0 * (fConst0 * (fConst8 * (fConst0 * (fConst0 * (-9.79697924426087e-33 - fConst22) + -1.77376389485776e-28) + -2.14597136823331e-25) + 2.62205704185131e-19) + 1.89907075042467e-16) + 4.27220799106305e-14) + 2.49941532695314e-12;
	fConst38 = 1.0 / (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst18 + 1.63282987404348e-33) + 4.4344097371444e-29) + 1.07298568411666e-25) + 1.73266579347222e-22) + 1.31102852092565e-19) + 4.74767687606168e-17) + 7.12034665177176e-15) + 0.5 * (0.5 * fConst8 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (-2.86589792702458e-34 - fConst20) + -6.29844123704863e-30) + -6.96590249983833e-27) + -2.97472992156056e-24) + -4.85407145719168e-22) + -2.26821940920998e-20) + fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst19 + -1.12017008405057e-33) + -2.68390877243249e-29) + -2.76343706770825e-26) + -1.93946085329172e-23) + -8.29607943811672e-21) + -1.41480755159492e-18) + -6.87339214912114e-17)) + 3.12426915869143e-13);
	fConst39 = 1.17227175222998e-40 * fConst0;
	fConst40 = 1.29594227235659e-40 * fConst0;
	fConst41 = 0.5 * fConst5 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst40 + 8.87073657190112e-34) + -1.64126469795529e-30) + 1.58018238163299e-26) + -1.52868099778786e-23) + 4.36734685990874e-21) + fConst8 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst39 + 8.60503380045389e-34) + 3.96129387282593e-28) + -4.46652612440854e-25) + 6.72185939565773e-21) + -2.17087377052947e-18) + -1.32343844239659e-17);
	fConst42 = 9.37817401783986e-40 * fConst0;
	fConst43 = 1.03675381788527e-39 * fConst0;
	fConst44 = 0.5 * fConst5 * (fConst8 * (fConst0 * (fConst0 * (-5.32244194314067e-33 - fConst43) + 6.56505879182116e-30) + -3.16036476326599e-26) + 8.73469371981747e-21) + fConst8 * (fConst0 * (fConst8 * (fConst0 * (fConst0 * (-5.16302028027233e-33 - fConst42) + -1.58451754913037e-27) + 8.93305224881709e-25) + -4.34174754105893e-18) + -5.29375376958635e-17);
	fConst45 = 3.28236090624395e-39 * fConst0;
	fConst46 = 3.62863836259845e-39 * fConst0;
	fConst47 = 0.5 * fConst5 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst46 + 1.24190312006616e-32) + -6.56505879182116e-30) + -3.16036476326599e-26) + 6.11472399115143e-23) + -8.73469371981747e-21) + fConst8 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst45 + 1.20470473206354e-32) + 1.58451754913037e-27) + 8.93305224881709e-25) + -2.68874375826309e-20) + 4.34174754105893e-18) + -5.29375376958635e-17);
	fConst48 = 6.5647218124879e-39 * fConst0;
	fConst49 = 7.2572767251969e-39 * fConst0;
	fConst50 = 0.5 * fConst5 * (fConst8 * (fConst0 * (fConst0 * (-1.24190312006616e-32 - fConst49) + -6.56505879182116e-30) + 9.48109428979796e-26) + -2.62040811594524e-20) + fConst8 * (fConst0 * (fConst8 * (fConst0 * (fConst0 * (-1.20470473206354e-32 - fConst48) + 1.58451754913037e-27) + -2.67991567464513e-24) + 1.30252426231768e-17) + 5.29375376958635e-17);
	fConst51 = 0.5 * mydsp_faustpower4_f(fConst0) * (fConst8 * (9.07159590649613e-39 * fConst8 + 1.64126469795529e-29) + -9.17208598672714e-23) + fConst8 * (fConst8 * (fConst8 * (8.20590226560988e-39 * fConst8 + -3.96129387282593e-27) + 4.03311563739464e-20) + 1.32343844239659e-16);
	fConst52 = 0.5 * fConst5 * (fConst8 * (fConst0 * (fConst0 * (1.24190312006616e-32 - fConst49) + -6.56505879182116e-30) + -9.48109428979796e-26) + 2.62040811594524e-20) + fConst8 * (fConst0 * (fConst8 * (fConst0 * (fConst0 * (1.20470473206354e-32 - fConst48) + 1.58451754913037e-27) + 2.67991567464513e-24) + -1.30252426231768e-17) + 5.29375376958635e-17);
	fConst53 = 0.5 * fConst5 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst46 + -1.24190312006616e-32) + -6.56505879182116e-30) + 3.16036476326599e-26) + 6.11472399115143e-23) + 8.73469371981747e-21) + fConst8 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst45 + -1.20470473206354e-32) + 1.58451754913037e-27) + -8.93305224881709e-25) + -2.68874375826309e-20) + -4.34174754105893e-18) + -5.29375376958635e-17);
	fConst54 = 0.5 * fConst5 * (fConst8 * (fConst0 * (fConst0 * (5.32244194314067e-33 - fConst43) + 6.56505879182116e-30) + 3.16036476326599e-26) + -8.73469371981747e-21) + fConst8 * (fConst0 * (fConst8 * (fConst0 * (fConst0 * (5.16302028027233e-33 - fConst42) + -1.58451754913037e-27) + -8.93305224881709e-25) + 4.34174754105893e-18) + -5.29375376958635e-17);
	fConst55 = 0.5 * fConst5 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst40 + -8.87073657190112e-34) + -1.64126469795529e-30) + -1.58018238163299e-26) + -1.52868099778786e-23) + -4.36734685990874e-21) + fConst8 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst39 + -8.60503380045389e-34) + 3.96129387282593e-28) + 4.46652612440854e-25) + 6.72185939565773e-21) + 2.17087377052947e-18) + -1.32343844239659e-17);
	fConst56 = 1.0360737530688401e-13 * fConst5;
	fConst57 = 5.38043573960525e-13 * fConst0;
	fConst58 = 0.1 * fConst8 * (fConst57 + -3.45357917689612e-12);
	fConst59 = 0.1 * fConst8 * (-3.45357917689612e-12 - fConst57);
	fConst60 = 0.1 * fConst8 * (fConst7 + 3.45357917689612e-12);
	clear_state_f();
}

void Dsp::init_static(unsigned int sample_rate, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double fSlow0 = 0.01 * double(fVslider0);
	double fSlow1 = 0.007000000000000006 * (1.0 - double(fVslider1));
	double fSlow2 = 0.007000000000000006 * std::pow(1e+01, 0.05 * double(fHslider0));
	double fSlow3 = 1.0 - fSlow0;
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		double fTemp0 = double(input0[i0]);
		double fTemp1 = fSlow0 * fTemp0;
		fRec0[0] = fSlow1 + 0.993 * fRec0[1];
		double fTemp2 = fConst0 * (fConst4 + fConst2 * fRec0[0]) + 2.49252253398618e-07;
		double fTemp3 = fConst6 * fRec0[0];
		fRec2[0] = fTemp1 - fConst38 * (fConst37 * fRec2[1] + fConst36 * fRec2[2] + fConst35 * fRec2[3] + fConst34 * fRec2[4] + fConst33 * fRec2[5] + fConst29 * fRec2[6] + fConst25 * fRec2[7] + fConst21 * fRec2[8]);
		fRec1[0] = fConst38 * (fConst55 * fRec2[0] + fConst54 * fRec2[1] + fConst53 * fRec2[2] + fConst52 * fRec2[3] + fConst51 * fRec2[4] + fConst50 * fRec2[5] + fConst47 * fRec2[6] + fConst44 * fRec2[7] + fConst41 * fRec2[8]) - (fRec1[1] * (fConst0 * (fConst17 + fConst16 * fRec0[0]) + 7.47756760195853e-07) + fRec1[2] * (fConst0 * (fConst15 + fConst13 * fRec0[0]) + 7.47756760195853e-07) + fRec1[3] * (fConst0 * (fConst11 + fConst10 * fRec0[0]) + 2.49252253398618e-07)) / fTemp2;
		double fTemp4 = fConst56 * fRec0[0];
		fRec3[0] = fSlow2 + 0.993 * fRec3[1];
		output0[i0] = FAUSTFLOAT(fSlow3 * fTemp0 + fRec3[0] * asymhardclip2(fTemp1 - opamp((fRec1[0] * (fConst60 + fTemp3) + fRec1[1] * (fConst59 - fTemp4) + fRec1[2] * (fConst58 + fTemp4) + fRec1[3] * (fConst9 - fTemp3)) / fTemp2 - fTemp1)));
		fRec0[1] = fRec0[0];
		for (int j0 = 8; j0 > 0; j0 = j0 - 1) {
			fRec2[j0] = fRec2[j0 - 1];
		}
		for (int j1 = 3; j1 > 0; j1 = j1 - 1) {
			fRec1[j1] = fRec1[j1 - 1];
		}
		fRec3[1] = fRec3[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerFloatVar("fuzzdrive.Distortion",N_("Drive"),"S","",&fVslider1, 0.5, 0.0, 0.99, 0.01, 0);
	reg.registerFloatVar("fuzzdrive.Level",N_("Level"),"S","",&fHslider0, -2.0, -2e+01, 12.0, 0.1, 0);
	reg.registerFloatVar("fuzzdrive.wet_dry",N_("Wet/Dry"),"S",N_("percentage of processed signal in output signal"),&fVslider0, 1e+02, 0.0, 1e+02, 1.0, 0);
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
                        <property name=\"var_id\">fuzzdrive.Distortion</property>\n\
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
                      <object class=\"GxMidKnob\" id=\"gxbigknob2\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">fuzzdrive.Level</property>\n\
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
                      <object class=\"GxSmallKnobR\" id=\"gxbigknob3\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">fuzzdrive.wet_dry</property>\n\
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
                <property name=\"var_id\">fuzzdrive.Level</property>\n\
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
#define PARAM(p) ("fuzzdrive" "." p)

b.openHorizontalhideBox("");
    b.create_master_slider(PARAM("Level"), "Level");
b.closeBox();
b.openHorizontalBox("");

    b.create_small_rackknobr(PARAM("Level"), "Level");

    b.create_small_rackknobr(PARAM("Distortion"), "Drive");

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

} // end namespace fuzzdrive
} // end namespace pluginlib
