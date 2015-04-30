// generated from file '../src/plugins/fuzzdrive.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

namespace pluginlib {
namespace fuzzdrive {

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
	FAUSTFLOAT 	fslider1;
	double 	fRec2[2];
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
	FAUSTFLOAT 	fslider2;
	double 	fRec3[9];
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
	FAUSTFLOAT 	fslider3;
	double 	fRec4[2];
	double 	fRec1[4];
	double 	fConst81;
	double 	fConst82;
	double 	fConst83;
	double 	fConst84;
	double 	fConst85;
	double 	fConst86;
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
	id = "fuzzdrive";
	name = N_("Fuzz Drive");
	groups = 0;
	description = N_("Fuzz Distortion"); // description (tooltip)
	category = N_("Distortion");       // category
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
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<9; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<4; i++) fRec1[i] = 0;
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
	fConst15 = (1.21134747730432e-39 * fConst0);
	fConst16 = (7.12034665177176e-15 + (fConst0 * (4.74767687606168e-17 + (fConst0 * (1.31102852092565e-19 + (fConst0 * (1.73266579347222e-22 + (fConst0 * (1.07298568411666e-25 + (fConst0 * (4.4344097371444e-29 + (fConst0 * (1.63282987404348e-33 + fConst15)))))))))))));
	fConst17 = (1.20954612086615e-39 * fConst0);
	fConst18 = (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (0 - (2.86589792702458e-34 + fConst17))) - 6.29844123704863e-30)) - 6.96590249983833e-27)) - 2.97472992156056e-24)) - 4.85407145719168e-22)) - 2.26821940920998e-20));
	fConst19 = (2.45020046020493e-40 * fConst0);
	fConst20 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst19 - 1.12017008405057e-33)) - 2.68390877243249e-29)) - 2.76343706770825e-26)) - 1.93946085329172e-23)) - 8.29607943811672e-21)) - 1.41480755159492e-18)) - 6.87339214912114e-17);
	fConst21 = (1.29594227235659e-40 * fConst0);
	fConst22 = (fConst0 * (4.36734685990874e-21 + (fConst0 * ((fConst0 * (1.58018238163299e-26 + (fConst0 * ((fConst0 * (8.87073657190112e-34 + fConst21)) - 1.64126469795529e-30)))) - 1.52868099778786e-23))));
	fConst23 = (1.17227175222998e-40 * fConst0);
	fConst24 = ((fConst0 * ((fConst0 * (6.72185939565773e-21 + (fConst0 * ((fConst0 * (3.96129387282593e-28 + (fConst0 * (8.60503380045389e-34 + fConst23)))) - 4.46652612440854e-25)))) - 2.17087377052947e-18)) - 1.32343844239659e-17);
	fConst25 = ((fConst0 * (4.74767687606168e-17 + (fConst0 * ((fConst0 * (1.73266579347222e-22 + (fConst0 * ((fConst0 * (4.4344097371444e-29 + (fConst0 * (fConst15 - 1.63282987404348e-33)))) - 1.07298568411666e-25)))) - 1.31102852092565e-19)))) - 7.12034665177176e-15);
	fConst26 = (fConst0 * ((fConst0 * (4.85407145719168e-22 + (fConst0 * ((fConst0 * (6.96590249983833e-27 + (fConst0 * ((fConst0 * (2.86589792702458e-34 - fConst17)) - 6.29844123704863e-30)))) - 2.97472992156056e-24)))) - 2.26821940920998e-20));
	fConst27 = (6.87339214912114e-17 + (fConst0 * ((fConst0 * (8.29607943811672e-21 + (fConst0 * ((fConst0 * (2.76343706770825e-26 + (fConst0 * ((fConst0 * (1.12017008405057e-33 + fConst19)) - 2.68390877243249e-29)))) - 1.93946085329172e-23)))) - 1.41480755159492e-18)));
	fConst28 = (9.69077981843452e-39 * fConst0);
	fConst29 = faustpower<2>(fConst0);
	fConst30 = ((fConst0 * (1.89907075042467e-16 + (fConst0 * ((fConst29 * (2.14597136823331e-25 + (fConst0 * ((fConst0 * (9.79697924426087e-33 - fConst28)) - 1.77376389485776e-28)))) - 2.62205704185131e-19)))) - 4.27220799106305e-14);
	fConst31 = (9.6763689669292e-39 * fConst0);
	fConst32 = (fConst0 * ((fConst0 * (9.70814291438336e-22 + (fConst29 * ((fConst0 * (2.51937649481945e-29 + (fConst0 * (fConst31 - 1.71953875621475e-33)))) - 1.39318049996767e-26)))) - 9.0728776368399e-20));
	fConst33 = (1.96016036816394e-39 * fConst0);
	fConst34 = (4.12403528947268e-16 + (fConst0 * ((fConst0 * (1.65921588762334e-20 + (fConst29 * ((fConst0 * (1.073563508973e-28 + (fConst0 * (0 - (6.7210205043034e-33 + fConst33))))) - 5.52687413541649e-26)))) - 5.65923020637969e-18)));
	fConst35 = (3.39177293645208e-38 * fConst0);
	fConst36 = ((fConst0 * (1.89907075042467e-16 + (fConst0 * (2.62205704185131e-19 + (fConst0 * ((fConst0 * (2.14597136823331e-25 + (fConst0 * (1.77376389485776e-28 + (fConst0 * (fConst35 - 2.28596182366087e-32)))))) - 6.93066317388889e-22)))))) - 9.96848531248046e-14);
	fConst37 = (3.38672913842522e-38 * fConst0);
	fConst38 = (fConst0 * ((fConst0 * ((fConst0 * (1.18989196862423e-23 + (fConst0 * ((fConst0 * ((fConst0 * (4.01225709783442e-33 - fConst37)) - 2.51937649481945e-29)) - 1.39318049996767e-26)))) - 9.70814291438336e-22)) - 9.0728776368399e-20));
	fConst39 = (6.86056128857379e-39 * fConst0);
	fConst40 = (9.62274900876959e-16 + (fConst0 * ((fConst0 * ((fConst0 * (7.75784341316688e-23 + (fConst0 * ((fConst0 * ((fConst0 * (1.56823811767079e-32 + fConst39)) - 1.073563508973e-28)) - 5.52687413541649e-26)))) - 1.65921588762334e-20)) - 5.65923020637969e-18)));
	fConst41 = (6.78354587290416e-38 * fConst0);
	fConst42 = ((fConst0 * ((fConst0 * (7.86617112555392e-19 + (fConst29 * ((fConst0 * (1.77376389485776e-28 + (fConst0 * (2.28596182366087e-32 - fConst41)))) - 6.43791410469994e-25)))) - 1.89907075042467e-16)) - 9.96848531248046e-14);
	fConst43 = (6.77345827685044e-38 * fConst0);
	fConst44 = (fConst0 * (9.0728776368399e-20 + (fConst0 * ((fConst29 * (4.179541499903e-26 + (fConst0 * ((fConst0 * (fConst43 - 4.01225709783442e-33)) - 2.51937649481945e-29)))) - 2.91244287431501e-21))));
	fConst45 = (1.37211225771476e-38 * fConst0);
	fConst46 = (9.62274900876959e-16 + (fConst0 * (5.65923020637969e-18 + (fConst0 * ((fConst29 * (1.65806224062495e-25 + (fConst0 * ((fConst0 * (0 - (1.56823811767079e-32 + fConst45))) - 1.073563508973e-28)))) - 4.97764766287003e-20)))));
	fConst47 = ((fConst29 * (1.03959947608333e-21 + (fConst29 * ((8.47943234113021e-38 * fConst29) - 4.4344097371444e-28)))) - 4.74767687606168e-16);
	fConst48 = (2.26821940920998e-19 + (fConst29 * ((fConst29 * (6.29844123704863e-29 - (8.46682284606305e-38 * fConst29))) - 1.78483795293634e-23)));
	fConst49 = (1.41480755159492e-17 + (fConst29 * ((fConst29 * (2.68390877243249e-28 + (1.71514032214345e-38 * fConst29))) - 1.16367651197503e-22)));
	fConst50 = (9.96848531248046e-14 + (fConst0 * ((fConst0 * ((fConst29 * (6.43791410469994e-25 + (fConst0 * (1.77376389485776e-28 + (fConst0 * (0 - (2.28596182366087e-32 + fConst41))))))) - 7.86617112555392e-19)) - 1.89907075042467e-16)));
	fConst51 = (fConst0 * (9.0728776368399e-20 + (fConst0 * (2.91244287431501e-21 + (fConst29 * ((fConst0 * ((fConst0 * (4.01225709783442e-33 + fConst43)) - 2.51937649481945e-29)) - 4.179541499903e-26))))));
	fConst52 = ((fConst0 * (5.65923020637969e-18 + (fConst0 * (4.97764766287003e-20 + (fConst29 * ((fConst0 * ((fConst0 * (1.56823811767079e-32 - fConst45)) - 1.073563508973e-28)) - 1.65806224062495e-25)))))) - 9.62274900876959e-16);
	fConst53 = (9.96848531248046e-14 + (fConst0 * (1.89907075042467e-16 + (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (1.77376389485776e-28 + (fConst0 * (2.28596182366087e-32 + fConst35)))) - 2.14597136823331e-25)) - 6.93066317388889e-22)) - 2.62205704185131e-19)))));
	fConst54 = (fConst0 * ((fConst0 * (9.70814291438336e-22 + (fConst0 * (1.18989196862423e-23 + (fConst0 * (1.39318049996767e-26 + (fConst0 * ((fConst0 * (0 - (4.01225709783442e-33 + fConst37))) - 2.51937649481945e-29)))))))) - 9.0728776368399e-20));
	fConst55 = ((fConst0 * ((fConst0 * (1.65921588762334e-20 + (fConst0 * (7.75784341316688e-23 + (fConst0 * (5.52687413541649e-26 + (fConst0 * ((fConst0 * (fConst39 - 1.56823811767079e-32)) - 1.073563508973e-28)))))))) - 5.65923020637969e-18)) - 9.62274900876959e-16);
	fConst56 = (4.27220799106305e-14 + (fConst0 * (1.89907075042467e-16 + (fConst0 * (2.62205704185131e-19 + (fConst29 * ((fConst0 * ((fConst0 * (0 - (9.79697924426087e-33 + fConst28))) - 1.77376389485776e-28)) - 2.14597136823331e-25)))))));
	fConst57 = (fConst0 * ((fConst0 * ((fConst29 * (1.39318049996767e-26 + (fConst0 * (2.51937649481945e-29 + (fConst0 * (1.71953875621475e-33 + fConst31)))))) - 9.70814291438336e-22)) - 9.0728776368399e-20));
	fConst58 = ((fConst0 * ((fConst0 * ((fConst29 * (5.52687413541649e-26 + (fConst0 * (1.073563508973e-28 + (fConst0 * (6.7210205043034e-33 - fConst33)))))) - 1.65921588762334e-20)) - 5.65923020637969e-18)) - 4.12403528947268e-16);
	fConst59 = (1.03675381788527e-39 * fConst0);
	fConst60 = (fConst0 * (8.73469371981747e-21 + (fConst29 * ((fConst0 * (6.56505879182116e-30 + (fConst0 * (0 - (5.32244194314067e-33 + fConst59))))) - 3.16036476326599e-26))));
	fConst61 = (9.37817401783986e-40 * fConst0);
	fConst62 = ((fConst0 * ((fConst29 * (8.93305224881709e-25 + (fConst0 * ((fConst0 * (0 - (5.16302028027233e-33 + fConst61))) - 1.58451754913037e-27)))) - 4.34174754105893e-18)) - 5.29375376958635e-17);
	fConst63 = (3.62863836259845e-39 * fConst0);
	fConst64 = (fConst0 * ((fConst0 * (6.11472399115143e-23 + (fConst0 * ((fConst0 * ((fConst0 * (1.24190312006616e-32 + fConst63)) - 6.56505879182116e-30)) - 3.16036476326599e-26)))) - 8.73469371981747e-21));
	fConst65 = (3.28236090624395e-39 * fConst0);
	fConst66 = ((fConst0 * (4.34174754105893e-18 + (fConst0 * ((fConst0 * (8.93305224881709e-25 + (fConst0 * (1.58451754913037e-27 + (fConst0 * (1.20470473206354e-32 + fConst65)))))) - 2.68874375826309e-20)))) - 5.29375376958635e-17);
	fConst67 = (7.2572767251969e-39 * fConst0);
	fConst68 = (fConst0 * ((fConst29 * (9.48109428979796e-26 + (fConst0 * ((fConst0 * (0 - (1.24190312006616e-32 + fConst67))) - 6.56505879182116e-30)))) - 2.62040811594524e-20));
	fConst69 = (6.5647218124879e-39 * fConst0);
	fConst70 = (5.29375376958635e-17 + (fConst0 * (1.30252426231768e-17 + (fConst29 * ((fConst0 * (1.58451754913037e-27 + (fConst0 * (0 - (1.20470473206354e-32 + fConst69))))) - 2.67991567464513e-24)))));
	fConst71 = (fConst29 * ((fConst29 * (1.64126469795529e-29 + (9.07159590649613e-39 * fConst29))) - 9.17208598672714e-23));
	fConst72 = (1.32343844239659e-16 + (fConst29 * (4.03311563739464e-20 + (fConst29 * ((8.20590226560988e-39 * fConst29) - 3.96129387282593e-27)))));
	fConst73 = (fConst0 * (2.62040811594524e-20 + (fConst29 * ((fConst0 * ((fConst0 * (1.24190312006616e-32 - fConst67)) - 6.56505879182116e-30)) - 9.48109428979796e-26))));
	fConst74 = (5.29375376958635e-17 + (fConst0 * ((fConst29 * (2.67991567464513e-24 + (fConst0 * (1.58451754913037e-27 + (fConst0 * (1.20470473206354e-32 - fConst69)))))) - 1.30252426231768e-17)));
	fConst75 = (fConst0 * (8.73469371981747e-21 + (fConst0 * (6.11472399115143e-23 + (fConst0 * (3.16036476326599e-26 + (fConst0 * ((fConst0 * (fConst63 - 1.24190312006616e-32)) - 6.56505879182116e-30))))))));
	fConst76 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (1.58451754913037e-27 + (fConst0 * (fConst65 - 1.20470473206354e-32)))) - 8.93305224881709e-25)) - 2.68874375826309e-20)) - 4.34174754105893e-18)) - 5.29375376958635e-17);
	fConst77 = (fConst0 * ((fConst29 * (3.16036476326599e-26 + (fConst0 * (6.56505879182116e-30 + (fConst0 * (5.32244194314067e-33 - fConst59)))))) - 8.73469371981747e-21));
	fConst78 = ((fConst0 * (4.34174754105893e-18 + (fConst29 * ((fConst0 * ((fConst0 * (5.16302028027233e-33 - fConst61)) - 1.58451754913037e-27)) - 8.93305224881709e-25)))) - 5.29375376958635e-17);
	fConst79 = (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst21 - 8.87073657190112e-34)) - 1.64126469795529e-30)) - 1.58018238163299e-26)) - 1.52868099778786e-23)) - 4.36734685990874e-21));
	fConst80 = ((fConst0 * (2.17087377052947e-18 + (fConst0 * (6.72185939565773e-21 + (fConst0 * (4.46652612440854e-25 + (fConst0 * (3.96129387282593e-28 + (fConst0 * (fConst23 - 8.60503380045389e-34)))))))))) - 1.32343844239659e-17);
	fConst81 = (1.03607375306884e-12 * fConst0);
	fConst82 = (5.38043573960525e-13 * fConst0);
	fConst83 = (fConst82 - 3.45357917689612e-12);
	fConst84 = (0 - (3.45357917689612e-12 + fConst82));
	fConst85 = (3.45357917689612e-13 * fConst0);
	fConst86 = (3.45357917689612e-12 + fConst5);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlow0 = (0.007000000000000006 * (1 - double(fslider0)));
	double 	fSlow1 = (0.007000000000000006 * (1 - double(fslider1)));
	double 	fSlow2 = (0.01 * double(fslider2));
	double 	fSlow3 = (0.007000000000000006 * double(fslider3));
	double 	fSlow4 = (1 - fSlow2);
	for (int i=0; i<count; i++) {
		fRec0[0] = ((0.993 * fRec0[1]) + fSlow0);
		double fTemp0 = (2.49252253398618e-07 + (fConst0 * (fConst4 + (fConst2 * fRec0[0]))));
		fRec2[0] = ((0.993 * fRec2[1]) + fSlow1);
		double fTemp1 = (3.12426915869143e-13 + (fConst0 * ((fRec2[0] * (fConst20 + (fConst18 * fRec2[0]))) + fConst16)));
		double fTemp2 = (double)input0[i];
		fRec3[0] = ((fSlow2 * fTemp2) - (((((((((fRec3[1] * (2.49941532695314e-12 + (fConst0 * ((fRec2[0] * (fConst58 + (fConst57 * fRec2[0]))) + fConst56)))) + (fRec3[2] * (8.74795364433599e-12 + (fConst0 * ((fRec2[0] * (fConst55 + (fConst54 * fRec2[0]))) + fConst53))))) + (fRec3[3] * (1.7495907288672e-11 + (fConst0 * ((fRec2[0] * (fConst52 + (fConst51 * fRec2[0]))) + fConst50))))) + (fRec3[4] * (2.186988411084e-11 + (fConst29 * ((fRec2[0] * (fConst49 + (fConst48 * fRec2[0]))) + fConst47))))) + (fRec3[5] * (1.7495907288672e-11 + (fConst0 * ((fRec2[0] * (fConst46 + (fConst44 * fRec2[0]))) + fConst42))))) + (fRec3[6] * (8.74795364433599e-12 + (fConst0 * ((fRec2[0] * (fConst40 + (fConst38 * fRec2[0]))) + fConst36))))) + (fRec3[7] * (2.49941532695314e-12 + (fConst0 * ((fRec2[0] * (fConst34 + (fConst32 * fRec2[0]))) + fConst30))))) + (fRec3[8] * (3.12426915869143e-13 + (fConst0 * ((fRec2[0] * (fConst27 + (fConst26 * fRec2[0]))) + fConst25))))) / fTemp1));
		fRec4[0] = ((0.993 * fRec4[1]) + fSlow3);
		fRec1[0] = ((fConst29 * ((fRec4[0] * (((((((((fRec3[0] * (fConst80 + (fConst79 * fRec2[0]))) + (fRec3[1] * (fConst78 + (fConst77 * fRec2[0])))) + (fRec3[2] * (fConst76 + (fConst75 * fRec2[0])))) + (fRec3[3] * (fConst74 + (fConst73 * fRec2[0])))) + (fRec3[4] * (fConst72 + (fConst71 * fRec2[0])))) + (fRec3[5] * (fConst70 + (fConst68 * fRec2[0])))) + (fRec3[6] * (fConst66 + (fConst64 * fRec2[0])))) + (fRec3[7] * (fConst62 + (fConst60 * fRec2[0])))) + (fRec3[8] * (fConst24 + (fConst22 * fRec2[0]))))) / fTemp1)) - ((((fRec1[1] * (7.47756760195853e-07 + (fConst0 * (fConst14 + (fConst13 * fRec0[0]))))) + (fRec1[2] * (7.47756760195853e-07 + (fConst0 * (fConst12 + (fConst10 * fRec0[0])))))) + (fRec1[3] * (2.49252253398618e-07 + (fConst0 * (fConst8 + (fConst7 * fRec0[0])))))) / fTemp0));
		output0[i] = (FAUSTFLOAT)((fSlow4 * fTemp2) + (fConst29 * ((fRec4[0] * ((((fRec1[0] * (fConst86 + (fConst85 * fRec0[0]))) + (fRec1[1] * (fConst84 + (fConst0 * (0 - (1.03607375306884e-12 * fRec0[0])))))) + (fRec1[2] * (fConst83 + (fConst81 * fRec0[0])))) + (fRec1[3] * (fConst6 + (fConst0 * (0 - (3.45357917689612e-13 * fRec0[0]))))))) / fTemp0)));
		// post processing
		for (int i=3; i>0; i--) fRec1[i] = fRec1[i-1];
		fRec4[1] = fRec4[0];
		for (int i=8; i>0; i--) fRec3[i] = fRec3[i-1];
		fRec2[1] = fRec2[0];
		fRec0[1] = fRec0[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("fuzzdrive.Distortion",N_("Drive"),"S","",&fslider0, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("fuzzdrive.Fuzz",N_("Tone"),"S","",&fslider1, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("fuzzdrive.Volume",N_("Volume"),"S","",&fslider3, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("fuzzdrive.wet_dry",N_("wet/dry"),"S",N_("percentage of processed signal in output signal"),&fslider2, 1e+02, 0.0, 1e+02, 1.0);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("fuzzdrive" "." p)

b.openHorizontalhideBox("");
    b.create_master_slider(PARAM("Volume"), "Volume");
b.closeBox();
b.openHorizontalBox("");

    b.create_small_rackknobr(PARAM("Volume"), "Volume");

    b.create_small_rackknobr(PARAM("Fuzz"), "Tone");

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
