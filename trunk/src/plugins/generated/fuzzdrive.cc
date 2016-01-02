// generated from file '../src/plugins/fuzzdrive.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"
#include "clipping.h"

namespace pluginlib {
namespace fuzzdrive {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT 	fslider1;
	double 	fRec0[2];
	double 	fConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
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
	double 	fRec2[9];
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
	double 	fRec1[4];
	double 	fConst56;
	double 	fConst57;
	double 	fConst58;
	double 	fConst59;
	double 	fConst60;
	double 	fConst61;
	FAUSTFLOAT 	fslider2;
	double 	fRec3[2];
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
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<9; i++) fRec2[i] = 0;
	for (int i=0; i<4; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = double(min(192000, max(1, fSamplingFreq)));
	fConst1 = (1.2099049942893e-14 * fConst0);
	fConst2 = (2.49252253398618e-08 + (fConst0 * (2.51801622165627e-10 + fConst1)));
	fConst3 = (3.57407648445144e-16 * fConst0);
	fConst4 = (2.53046873750701e-09 + (fConst0 * (2.81736895109737e-13 + fConst3)));
	fConst5 = (1.79347857986842e-13 * fConst0);
	fConst6 = (3.45357917689612e-12 - fConst5);
	fConst7 = ((fConst0 * (2.51801622165627e-10 - fConst1)) - 2.49252253398618e-08);
	fConst8 = ((fConst0 * (2.81736895109737e-13 - fConst3)) - 2.53046873750701e-09);
	fConst9 = (3.62971498286789e-14 * fConst0);
	fConst10 = ((fConst0 * (fConst9 - 2.51801622165627e-10)) - 2.49252253398618e-08);
	fConst11 = (1.07222294533543e-15 * fConst0);
	fConst12 = ((fConst0 * (fConst11 - 2.81736895109737e-13)) - 2.53046873750701e-09);
	fConst13 = (2.49252253398618e-08 + (fConst0 * (0 - (2.51801622165627e-10 + fConst9))));
	fConst14 = (2.53046873750701e-09 + (fConst0 * (0 - (2.81736895109737e-13 + fConst11))));
	fConst15 = (1.20954612086615e-39 * fConst0);
	fConst16 = (2.45020046020493e-40 * fConst0);
	fConst17 = (1.21134747730432e-39 * fConst0);
	fConst18 = (3.12426915869143e-13 + (fConst0 * (((fConst0 * (4.74767687606168e-17 + (fConst0 * ((fConst0 * (1.73266579347222e-22 + (fConst0 * ((fConst0 * (4.4344097371444e-29 + (fConst0 * (fConst17 - 1.63282987404348e-33)))) - 1.07298568411666e-25)))) - 1.31102852092565e-19)))) - 7.12034665177176e-15) + (0.5 * ((6.87339214912114e-17 + (fConst0 * ((fConst0 * (8.29607943811672e-21 + (fConst0 * ((fConst0 * (2.76343706770825e-26 + (fConst0 * ((fConst0 * (1.12017008405057e-33 + fConst16)) - 2.68390877243249e-29)))) - 1.93946085329172e-23)))) - 1.41480755159492e-18))) + (0.5 * (fConst0 * ((fConst0 * (4.85407145719168e-22 + (fConst0 * ((fConst0 * (6.96590249983833e-27 + (fConst0 * ((fConst0 * (2.86589792702458e-34 - fConst15)) - 6.29844123704863e-30)))) - 2.97472992156056e-24)))) - 2.26821940920998e-20))))))));
	fConst19 = (9.6763689669292e-39 * fConst0);
	fConst20 = faustpower<2>(fConst0);
	fConst21 = (1.96016036816394e-39 * fConst0);
	fConst22 = (9.69077981843452e-39 * fConst0);
	fConst23 = (2.49941532695314e-12 + (fConst0 * (((fConst0 * (1.89907075042467e-16 + (fConst0 * ((fConst20 * (2.14597136823331e-25 + (fConst0 * ((fConst0 * (9.79697924426087e-33 - fConst22)) - 1.77376389485776e-28)))) - 2.62205704185131e-19)))) - 4.27220799106305e-14) + (0.5 * ((4.12403528947268e-16 + (fConst0 * ((fConst0 * (1.65921588762334e-20 + (fConst20 * ((fConst0 * (1.073563508973e-28 + (fConst0 * (0 - (6.7210205043034e-33 + fConst21))))) - 5.52687413541649e-26)))) - 5.65923020637969e-18))) + (0.5 * (fConst0 * ((fConst0 * (9.70814291438336e-22 + (fConst20 * ((fConst0 * (2.51937649481945e-29 + (fConst0 * (fConst19 - 1.71953875621475e-33)))) - 1.39318049996767e-26)))) - 9.0728776368399e-20))))))));
	fConst24 = (3.38672913842522e-38 * fConst0);
	fConst25 = (6.86056128857379e-39 * fConst0);
	fConst26 = (3.39177293645208e-38 * fConst0);
	fConst27 = (8.74795364433599e-12 + (fConst0 * (((fConst0 * (1.89907075042467e-16 + (fConst0 * (2.62205704185131e-19 + (fConst0 * ((fConst0 * (2.14597136823331e-25 + (fConst0 * (1.77376389485776e-28 + (fConst0 * (fConst26 - 2.28596182366087e-32)))))) - 6.93066317388889e-22)))))) - 9.96848531248046e-14) + (0.5 * ((9.62274900876959e-16 + (fConst0 * ((fConst0 * ((fConst0 * (7.75784341316688e-23 + (fConst0 * ((fConst0 * ((fConst0 * (1.56823811767079e-32 + fConst25)) - 1.073563508973e-28)) - 5.52687413541649e-26)))) - 1.65921588762334e-20)) - 5.65923020637969e-18))) + (0.5 * (fConst0 * ((fConst0 * ((fConst0 * (1.18989196862423e-23 + (fConst0 * ((fConst0 * ((fConst0 * (4.01225709783442e-33 - fConst24)) - 2.51937649481945e-29)) - 1.39318049996767e-26)))) - 9.70814291438336e-22)) - 9.0728776368399e-20))))))));
	fConst28 = (6.77345827685044e-38 * fConst0);
	fConst29 = (1.37211225771476e-38 * fConst0);
	fConst30 = (6.78354587290416e-38 * fConst0);
	fConst31 = (1.7495907288672e-11 + (fConst0 * (((fConst0 * ((fConst0 * (7.86617112555392e-19 + (fConst20 * ((fConst0 * (1.77376389485776e-28 + (fConst0 * (2.28596182366087e-32 - fConst30)))) - 6.43791410469994e-25)))) - 1.89907075042467e-16)) - 9.96848531248046e-14) + (0.5 * ((9.62274900876959e-16 + (fConst0 * (5.65923020637969e-18 + (fConst0 * ((fConst20 * (1.65806224062495e-25 + (fConst0 * ((fConst0 * (0 - (1.56823811767079e-32 + fConst29))) - 1.073563508973e-28)))) - 4.97764766287003e-20))))) + (0.5 * (fConst0 * (9.0728776368399e-20 + (fConst0 * ((fConst20 * (4.179541499903e-26 + (fConst0 * ((fConst0 * (fConst28 - 4.01225709783442e-33)) - 2.51937649481945e-29)))) - 2.91244287431501e-21))))))))));
	fConst32 = (2.186988411084e-11 + (fConst20 * (((fConst20 * (1.03959947608333e-21 + (fConst20 * ((8.47943234113021e-38 * fConst20) - 4.4344097371444e-28)))) - 4.74767687606168e-16) + (0.5 * ((1.41480755159492e-17 + (fConst20 * ((fConst20 * (2.68390877243249e-28 + (1.71514032214345e-38 * fConst20))) - 1.16367651197503e-22))) + (0.5 * (2.26821940920998e-19 + (fConst20 * ((fConst20 * (6.29844123704863e-29 - (8.46682284606305e-38 * fConst20))) - 1.78483795293634e-23)))))))));
	fConst33 = (1.7495907288672e-11 + (fConst0 * ((9.96848531248046e-14 + (fConst0 * ((fConst0 * ((fConst20 * (6.43791410469994e-25 + (fConst0 * (1.77376389485776e-28 + (fConst0 * (0 - (2.28596182366087e-32 + fConst30))))))) - 7.86617112555392e-19)) - 1.89907075042467e-16))) + (0.5 * (((fConst0 * (5.65923020637969e-18 + (fConst0 * (4.97764766287003e-20 + (fConst20 * ((fConst0 * ((fConst0 * (1.56823811767079e-32 - fConst29)) - 1.073563508973e-28)) - 1.65806224062495e-25)))))) - 9.62274900876959e-16) + (0.5 * (fConst0 * (9.0728776368399e-20 + (fConst0 * (2.91244287431501e-21 + (fConst20 * ((fConst0 * ((fConst0 * (4.01225709783442e-33 + fConst28)) - 2.51937649481945e-29)) - 4.179541499903e-26))))))))))));
	fConst34 = (8.74795364433599e-12 + (fConst0 * ((9.96848531248046e-14 + (fConst0 * (1.89907075042467e-16 + (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (1.77376389485776e-28 + (fConst0 * (2.28596182366087e-32 + fConst26)))) - 2.14597136823331e-25)) - 6.93066317388889e-22)) - 2.62205704185131e-19))))) + (0.5 * (((fConst0 * ((fConst0 * (1.65921588762334e-20 + (fConst0 * (7.75784341316688e-23 + (fConst0 * (5.52687413541649e-26 + (fConst0 * ((fConst0 * (fConst25 - 1.56823811767079e-32)) - 1.073563508973e-28)))))))) - 5.65923020637969e-18)) - 9.62274900876959e-16) + (0.5 * (fConst0 * ((fConst0 * (9.70814291438336e-22 + (fConst0 * (1.18989196862423e-23 + (fConst0 * (1.39318049996767e-26 + (fConst0 * ((fConst0 * (0 - (4.01225709783442e-33 + fConst24))) - 2.51937649481945e-29)))))))) - 9.0728776368399e-20))))))));
	fConst35 = (2.49941532695314e-12 + (fConst0 * ((4.27220799106305e-14 + (fConst0 * (1.89907075042467e-16 + (fConst0 * (2.62205704185131e-19 + (fConst20 * ((fConst0 * ((fConst0 * (0 - (9.79697924426087e-33 + fConst22))) - 1.77376389485776e-28)) - 2.14597136823331e-25))))))) + (0.5 * (((fConst0 * ((fConst0 * ((fConst20 * (5.52687413541649e-26 + (fConst0 * (1.073563508973e-28 + (fConst0 * (6.7210205043034e-33 - fConst21)))))) - 1.65921588762334e-20)) - 5.65923020637969e-18)) - 4.12403528947268e-16) + (0.5 * (fConst0 * ((fConst0 * ((fConst20 * (1.39318049996767e-26 + (fConst0 * (2.51937649481945e-29 + (fConst0 * (1.71953875621475e-33 + fConst19)))))) - 9.70814291438336e-22)) - 9.0728776368399e-20))))))));
	fConst36 = (3.12426915869143e-13 + (fConst0 * ((7.12034665177176e-15 + (fConst0 * (4.74767687606168e-17 + (fConst0 * (1.31102852092565e-19 + (fConst0 * (1.73266579347222e-22 + (fConst0 * (1.07298568411666e-25 + (fConst0 * (4.4344097371444e-29 + (fConst0 * (1.63282987404348e-33 + fConst17))))))))))))) + (0.5 * (((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst16 - 1.12017008405057e-33)) - 2.68390877243249e-29)) - 2.76343706770825e-26)) - 1.93946085329172e-23)) - 8.29607943811672e-21)) - 1.41480755159492e-18)) - 6.87339214912114e-17) + (0.5 * (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (0 - (2.86589792702458e-34 + fConst15))) - 6.29844123704863e-30)) - 6.96590249983833e-27)) - 2.97472992156056e-24)) - 4.85407145719168e-22)) - 2.26821940920998e-20))))))));
	fConst37 = (1.0 / fConst36);
	fConst38 = (1.29594227235659e-40 * fConst0);
	fConst39 = (1.17227175222998e-40 * fConst0);
	fConst40 = (((fConst0 * ((fConst0 * (6.72185939565773e-21 + (fConst0 * ((fConst0 * (3.96129387282593e-28 + (fConst0 * (8.60503380045389e-34 + fConst39)))) - 4.46652612440854e-25)))) - 2.17087377052947e-18)) - 1.32343844239659e-17) + (0.5 * (fConst0 * (4.36734685990874e-21 + (fConst0 * ((fConst0 * (1.58018238163299e-26 + (fConst0 * ((fConst0 * (8.87073657190112e-34 + fConst38)) - 1.64126469795529e-30)))) - 1.52868099778786e-23))))));
	fConst41 = (1.03675381788527e-39 * fConst0);
	fConst42 = (9.37817401783986e-40 * fConst0);
	fConst43 = (((fConst0 * ((fConst20 * (8.93305224881709e-25 + (fConst0 * ((fConst0 * (0 - (5.16302028027233e-33 + fConst42))) - 1.58451754913037e-27)))) - 4.34174754105893e-18)) - 5.29375376958635e-17) + (0.5 * (fConst0 * (8.73469371981747e-21 + (fConst20 * ((fConst0 * (6.56505879182116e-30 + (fConst0 * (0 - (5.32244194314067e-33 + fConst41))))) - 3.16036476326599e-26))))));
	fConst44 = (3.62863836259845e-39 * fConst0);
	fConst45 = (3.28236090624395e-39 * fConst0);
	fConst46 = (((fConst0 * (4.34174754105893e-18 + (fConst0 * ((fConst0 * (8.93305224881709e-25 + (fConst0 * (1.58451754913037e-27 + (fConst0 * (1.20470473206354e-32 + fConst45)))))) - 2.68874375826309e-20)))) - 5.29375376958635e-17) + (0.5 * (fConst0 * ((fConst0 * (6.11472399115143e-23 + (fConst0 * ((fConst0 * ((fConst0 * (1.24190312006616e-32 + fConst44)) - 6.56505879182116e-30)) - 3.16036476326599e-26)))) - 8.73469371981747e-21))));
	fConst47 = (7.2572767251969e-39 * fConst0);
	fConst48 = (6.5647218124879e-39 * fConst0);
	fConst49 = ((5.29375376958635e-17 + (fConst0 * (1.30252426231768e-17 + (fConst20 * ((fConst0 * (1.58451754913037e-27 + (fConst0 * (0 - (1.20470473206354e-32 + fConst48))))) - 2.67991567464513e-24))))) + (0.5 * (fConst0 * ((fConst20 * (9.48109428979796e-26 + (fConst0 * ((fConst0 * (0 - (1.24190312006616e-32 + fConst47))) - 6.56505879182116e-30)))) - 2.62040811594524e-20))));
	fConst50 = ((1.32343844239659e-16 + (fConst20 * (4.03311563739464e-20 + (fConst20 * ((8.20590226560988e-39 * fConst20) - 3.96129387282593e-27))))) + (0.5 * (fConst20 * ((fConst20 * (1.64126469795529e-29 + (9.07159590649613e-39 * fConst20))) - 9.17208598672714e-23))));
	fConst51 = ((5.29375376958635e-17 + (fConst0 * ((fConst20 * (2.67991567464513e-24 + (fConst0 * (1.58451754913037e-27 + (fConst0 * (1.20470473206354e-32 - fConst48)))))) - 1.30252426231768e-17))) + (0.5 * (fConst0 * (2.62040811594524e-20 + (fConst20 * ((fConst0 * ((fConst0 * (1.24190312006616e-32 - fConst47)) - 6.56505879182116e-30)) - 9.48109428979796e-26))))));
	fConst52 = (((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (1.58451754913037e-27 + (fConst0 * (fConst45 - 1.20470473206354e-32)))) - 8.93305224881709e-25)) - 2.68874375826309e-20)) - 4.34174754105893e-18)) - 5.29375376958635e-17) + (0.5 * (fConst0 * (8.73469371981747e-21 + (fConst0 * (6.11472399115143e-23 + (fConst0 * (3.16036476326599e-26 + (fConst0 * ((fConst0 * (fConst44 - 1.24190312006616e-32)) - 6.56505879182116e-30))))))))));
	fConst53 = (((fConst0 * (4.34174754105893e-18 + (fConst20 * ((fConst0 * ((fConst0 * (5.16302028027233e-33 - fConst42)) - 1.58451754913037e-27)) - 8.93305224881709e-25)))) - 5.29375376958635e-17) + (0.5 * (fConst0 * ((fConst20 * (3.16036476326599e-26 + (fConst0 * (6.56505879182116e-30 + (fConst0 * (5.32244194314067e-33 - fConst41)))))) - 8.73469371981747e-21))));
	fConst54 = (((fConst0 * (2.17087377052947e-18 + (fConst0 * (6.72185939565773e-21 + (fConst0 * (4.46652612440854e-25 + (fConst0 * (3.96129387282593e-28 + (fConst0 * (fConst39 - 8.60503380045389e-34)))))))))) - 1.32343844239659e-17) + (0.5 * (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst38 - 8.87073657190112e-34)) - 1.64126469795529e-30)) - 1.58018238163299e-26)) - 1.52868099778786e-23)) - 4.36734685990874e-21))));
	fConst55 = (fConst20 / fConst36);
	fConst56 = (1.0360737530688401e-13 * fConst0);
	fConst57 = (5.38043573960525e-13 * fConst0);
	fConst58 = (0.1 * (fConst57 - 3.45357917689612e-12));
	fConst59 = (0 - (3.45357917689612e-12 + fConst57));
	fConst60 = (0.1 * (3.45357917689612e-12 + fConst5));
	fConst61 = (3.4535791768961205e-14 * fConst0);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlow0 = (0.01 * double(fslider0));
	double 	fSlow1 = (0.007000000000000006 * (1 - double(fslider1)));
	double 	fSlow2 = (0.007000000000000006 * pow(10,(0.05 * double(fslider2))));
	double 	fSlow3 = (1 - fSlow0);
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		double fTemp1 = (fSlow0 * fTemp0);
		fRec0[0] = ((0.993 * fRec0[1]) + fSlow1);
		double fTemp2 = (2.49252253398618e-07 + (fConst0 * (fConst4 + (fConst2 * fRec0[0]))));
		fRec2[0] = (fTemp1 - (fConst37 * ((((((((fConst35 * fRec2[1]) + (fConst34 * fRec2[2])) + (fConst33 * fRec2[3])) + (fConst32 * fRec2[4])) + (fConst31 * fRec2[5])) + (fConst27 * fRec2[6])) + (fConst23 * fRec2[7])) + (fConst18 * fRec2[8]))));
		fRec1[0] = ((fConst55 * (((((((((fConst54 * fRec2[0]) + (fConst53 * fRec2[1])) + (fConst52 * fRec2[2])) + (fConst51 * fRec2[3])) + (fConst50 * fRec2[4])) + (fConst49 * fRec2[5])) + (fConst46 * fRec2[6])) + (fConst43 * fRec2[7])) + (fConst40 * fRec2[8]))) - ((((fRec1[1] * (7.47756760195853e-07 + (fConst0 * (fConst14 + (fConst13 * fRec0[0]))))) + (fRec1[2] * (7.47756760195853e-07 + (fConst0 * (fConst12 + (fConst10 * fRec0[0])))))) + (fRec1[3] * (2.49252253398618e-07 + (fConst0 * (fConst8 + (fConst7 * fRec0[0])))))) / fTemp2));
		fRec3[0] = ((0.993 * fRec3[1]) + fSlow2);
		output0[i] = (FAUSTFLOAT)((fSlow3 * fTemp0) + (fRec3[0] * asymhardclip2((fTemp1 - opamp(((fConst20 * (((((fRec1[0] * ((fConst61 * fRec0[0]) + fConst60)) + (0.1 * (fRec1[1] * (fConst59 + (fConst0 * (0 - (1.03607375306884e-12 * fRec0[0]))))))) + (fRec1[2] * (fConst58 + (fConst56 * fRec0[0])))) + (0.1 * (fRec1[3] * (fConst6 + (fConst0 * (0 - (3.45357917689612e-13 * fRec0[0]))))))) / fTemp2)) - fTemp1))))));
		// post processing
		fRec3[1] = fRec3[0];
		for (int i=3; i>0; i--) fRec1[i] = fRec1[i-1];
		for (int i=8; i>0; i--) fRec2[i] = fRec2[i-1];
		fRec0[1] = fRec0[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("fuzzdrive.Distortion",N_("Drive"),"S","",&fslider1, 0.5, 0.0, 0.99, 0.01);
	reg.registerVar("fuzzdrive.Level",N_("Level"),"S","",&fslider2, -2.0, -2e+01, 12.0, 0.1);
	reg.registerVar("fuzzdrive.wet_dry",N_("Wet/Dry"),"S",N_("percentage of processed signal in output signal"),&fslider0, 1e+02, 0.0, 1e+02, 1.0);
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

} // end namespace fuzzdrive
} // end namespace pluginlib
