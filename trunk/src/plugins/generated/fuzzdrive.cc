// generated from file '../src/plugins/fuzzdrive.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"
#include "trany.h"

namespace pluginlib {
namespace fuzzdrive {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT 	fslider1;
	double 	fRec6[2];
	int 	iConst0;
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
	double 	fConst38;
	double 	fRec14[9];
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
	FAUSTFLOAT 	fslider2;
	double 	fRec15[2];
	double 	fConst56;
	double 	fConst57;
	double 	fConst58;
	double 	fConst59;
	double 	fConst60;
	double 	fRec16[2];
	double 	fRec13[3];
	double 	fConst61;
	double 	fConst62;
	double 	fConst63;
	double 	fConst64;
	double 	fConst65;
	double 	fRec12[2];
	double 	fRec17[2];
	double 	fRec11[3];
	double 	fRec10[2];
	double 	fRec18[2];
	double 	fRec9[3];
	double 	fRec8[2];
	double 	fRec7[4];
	double 	fConst66;
	double 	fConst67;
	double 	fConst68;
	double 	fConst69;
	double 	fConst70;
	double 	fConst71;
	double 	fRec19[2];
	double 	fRec5[3];
	double 	fRec4[2];
	double 	fRec20[2];
	double 	fRec3[3];
	double 	fRec2[2];
	double 	fRec21[2];
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
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<9; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<3; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<3; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<3; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<4; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<3; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
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
	fConst2 = (1.2099049942893e-14 * fConst1);
	fConst3 = (2.49252253398618e-08 + (fConst1 * (2.51801622165627e-10 + fConst2)));
	fConst4 = (3.57407648445144e-16 * fConst1);
	fConst5 = (2.53046873750701e-09 + (fConst1 * (2.81736895109737e-13 + fConst4)));
	fConst6 = (1.79347857986842e-13 * fConst1);
	fConst7 = (3.45357917689612e-12 - fConst6);
	fConst8 = ((fConst1 * (2.51801622165627e-10 - fConst2)) - 2.49252253398618e-08);
	fConst9 = ((fConst1 * (2.81736895109737e-13 - fConst4)) - 2.53046873750701e-09);
	fConst10 = (3.62971498286789e-14 * fConst1);
	fConst11 = ((fConst1 * (fConst10 - 2.51801622165627e-10)) - 2.49252253398618e-08);
	fConst12 = (1.07222294533543e-15 * fConst1);
	fConst13 = ((fConst1 * (fConst12 - 2.81736895109737e-13)) - 2.53046873750701e-09);
	fConst14 = (2.49252253398618e-08 + (fConst1 * (0 - (2.51801622165627e-10 + fConst10))));
	fConst15 = (2.53046873750701e-09 + (fConst1 * (0 - (2.81736895109737e-13 + fConst12))));
	fConst16 = (1.20954612086615e-39 * fConst1);
	fConst17 = (2.45020046020493e-40 * fConst1);
	fConst18 = (1.21134747730432e-39 * fConst1);
	fConst19 = (3.12426915869143e-13 + (fConst1 * (((fConst1 * (4.74767687606168e-17 + (fConst1 * ((fConst1 * (1.73266579347222e-22 + (fConst1 * ((fConst1 * (4.4344097371444e-29 + (fConst1 * (fConst18 - 1.63282987404348e-33)))) - 1.07298568411666e-25)))) - 1.31102852092565e-19)))) - 7.12034665177176e-15) + (0.5 * ((6.87339214912114e-17 + (fConst1 * ((fConst1 * (8.29607943811672e-21 + (fConst1 * ((fConst1 * (2.76343706770825e-26 + (fConst1 * ((fConst1 * (1.12017008405057e-33 + fConst17)) - 2.68390877243249e-29)))) - 1.93946085329172e-23)))) - 1.41480755159492e-18))) + (0.5 * (fConst1 * ((fConst1 * (4.85407145719168e-22 + (fConst1 * ((fConst1 * (6.96590249983833e-27 + (fConst1 * ((fConst1 * (2.86589792702458e-34 - fConst16)) - 6.29844123704863e-30)))) - 2.97472992156056e-24)))) - 2.26821940920998e-20))))))));
	fConst20 = (9.6763689669292e-39 * fConst1);
	fConst21 = faustpower<2>(fConst1);
	fConst22 = (1.96016036816394e-39 * fConst1);
	fConst23 = (9.69077981843452e-39 * fConst1);
	fConst24 = (2.49941532695314e-12 + (fConst1 * (((fConst1 * (1.89907075042467e-16 + (fConst1 * ((fConst21 * (2.14597136823331e-25 + (fConst1 * ((fConst1 * (9.79697924426087e-33 - fConst23)) - 1.77376389485776e-28)))) - 2.62205704185131e-19)))) - 4.27220799106305e-14) + (0.5 * ((4.12403528947268e-16 + (fConst1 * ((fConst1 * (1.65921588762334e-20 + (fConst21 * ((fConst1 * (1.073563508973e-28 + (fConst1 * (0 - (6.7210205043034e-33 + fConst22))))) - 5.52687413541649e-26)))) - 5.65923020637969e-18))) + (0.5 * (fConst1 * ((fConst1 * (9.70814291438336e-22 + (fConst21 * ((fConst1 * (2.51937649481945e-29 + (fConst1 * (fConst20 - 1.71953875621475e-33)))) - 1.39318049996767e-26)))) - 9.0728776368399e-20))))))));
	fConst25 = (3.38672913842522e-38 * fConst1);
	fConst26 = (6.86056128857379e-39 * fConst1);
	fConst27 = (3.39177293645208e-38 * fConst1);
	fConst28 = (8.74795364433599e-12 + (fConst1 * (((fConst1 * (1.89907075042467e-16 + (fConst1 * (2.62205704185131e-19 + (fConst1 * ((fConst1 * (2.14597136823331e-25 + (fConst1 * (1.77376389485776e-28 + (fConst1 * (fConst27 - 2.28596182366087e-32)))))) - 6.93066317388889e-22)))))) - 9.96848531248046e-14) + (0.5 * ((9.62274900876959e-16 + (fConst1 * ((fConst1 * ((fConst1 * (7.75784341316688e-23 + (fConst1 * ((fConst1 * ((fConst1 * (1.56823811767079e-32 + fConst26)) - 1.073563508973e-28)) - 5.52687413541649e-26)))) - 1.65921588762334e-20)) - 5.65923020637969e-18))) + (0.5 * (fConst1 * ((fConst1 * ((fConst1 * (1.18989196862423e-23 + (fConst1 * ((fConst1 * ((fConst1 * (4.01225709783442e-33 - fConst25)) - 2.51937649481945e-29)) - 1.39318049996767e-26)))) - 9.70814291438336e-22)) - 9.0728776368399e-20))))))));
	fConst29 = (6.77345827685044e-38 * fConst1);
	fConst30 = (1.37211225771476e-38 * fConst1);
	fConst31 = (6.78354587290416e-38 * fConst1);
	fConst32 = (1.7495907288672e-11 + (fConst1 * (((fConst1 * ((fConst1 * (7.86617112555392e-19 + (fConst21 * ((fConst1 * (1.77376389485776e-28 + (fConst1 * (2.28596182366087e-32 - fConst31)))) - 6.43791410469994e-25)))) - 1.89907075042467e-16)) - 9.96848531248046e-14) + (0.5 * ((9.62274900876959e-16 + (fConst1 * (5.65923020637969e-18 + (fConst1 * ((fConst21 * (1.65806224062495e-25 + (fConst1 * ((fConst1 * (0 - (1.56823811767079e-32 + fConst30))) - 1.073563508973e-28)))) - 4.97764766287003e-20))))) + (0.5 * (fConst1 * (9.0728776368399e-20 + (fConst1 * ((fConst21 * (4.179541499903e-26 + (fConst1 * ((fConst1 * (fConst29 - 4.01225709783442e-33)) - 2.51937649481945e-29)))) - 2.91244287431501e-21))))))))));
	fConst33 = (2.186988411084e-11 + (fConst21 * (((fConst21 * (1.03959947608333e-21 + (fConst21 * ((8.47943234113021e-38 * fConst21) - 4.4344097371444e-28)))) - 4.74767687606168e-16) + (0.5 * ((1.41480755159492e-17 + (fConst21 * ((fConst21 * (2.68390877243249e-28 + (1.71514032214345e-38 * fConst21))) - 1.16367651197503e-22))) + (0.5 * (2.26821940920998e-19 + (fConst21 * ((fConst21 * (6.29844123704863e-29 - (8.46682284606305e-38 * fConst21))) - 1.78483795293634e-23)))))))));
	fConst34 = (1.7495907288672e-11 + (fConst1 * ((9.96848531248046e-14 + (fConst1 * ((fConst1 * ((fConst21 * (6.43791410469994e-25 + (fConst1 * (1.77376389485776e-28 + (fConst1 * (0 - (2.28596182366087e-32 + fConst31))))))) - 7.86617112555392e-19)) - 1.89907075042467e-16))) + (0.5 * (((fConst1 * (5.65923020637969e-18 + (fConst1 * (4.97764766287003e-20 + (fConst21 * ((fConst1 * ((fConst1 * (1.56823811767079e-32 - fConst30)) - 1.073563508973e-28)) - 1.65806224062495e-25)))))) - 9.62274900876959e-16) + (0.5 * (fConst1 * (9.0728776368399e-20 + (fConst1 * (2.91244287431501e-21 + (fConst21 * ((fConst1 * ((fConst1 * (4.01225709783442e-33 + fConst29)) - 2.51937649481945e-29)) - 4.179541499903e-26))))))))))));
	fConst35 = (8.74795364433599e-12 + (fConst1 * ((9.96848531248046e-14 + (fConst1 * (1.89907075042467e-16 + (fConst1 * ((fConst1 * ((fConst1 * ((fConst1 * (1.77376389485776e-28 + (fConst1 * (2.28596182366087e-32 + fConst27)))) - 2.14597136823331e-25)) - 6.93066317388889e-22)) - 2.62205704185131e-19))))) + (0.5 * (((fConst1 * ((fConst1 * (1.65921588762334e-20 + (fConst1 * (7.75784341316688e-23 + (fConst1 * (5.52687413541649e-26 + (fConst1 * ((fConst1 * (fConst26 - 1.56823811767079e-32)) - 1.073563508973e-28)))))))) - 5.65923020637969e-18)) - 9.62274900876959e-16) + (0.5 * (fConst1 * ((fConst1 * (9.70814291438336e-22 + (fConst1 * (1.18989196862423e-23 + (fConst1 * (1.39318049996767e-26 + (fConst1 * ((fConst1 * (0 - (4.01225709783442e-33 + fConst25))) - 2.51937649481945e-29)))))))) - 9.0728776368399e-20))))))));
	fConst36 = (2.49941532695314e-12 + (fConst1 * ((4.27220799106305e-14 + (fConst1 * (1.89907075042467e-16 + (fConst1 * (2.62205704185131e-19 + (fConst21 * ((fConst1 * ((fConst1 * (0 - (9.79697924426087e-33 + fConst23))) - 1.77376389485776e-28)) - 2.14597136823331e-25))))))) + (0.5 * (((fConst1 * ((fConst1 * ((fConst21 * (5.52687413541649e-26 + (fConst1 * (1.073563508973e-28 + (fConst1 * (6.7210205043034e-33 - fConst22)))))) - 1.65921588762334e-20)) - 5.65923020637969e-18)) - 4.12403528947268e-16) + (0.5 * (fConst1 * ((fConst1 * ((fConst21 * (1.39318049996767e-26 + (fConst1 * (2.51937649481945e-29 + (fConst1 * (1.71953875621475e-33 + fConst20)))))) - 9.70814291438336e-22)) - 9.0728776368399e-20))))))));
	fConst37 = (3.12426915869143e-13 + (fConst1 * ((7.12034665177176e-15 + (fConst1 * (4.74767687606168e-17 + (fConst1 * (1.31102852092565e-19 + (fConst1 * (1.73266579347222e-22 + (fConst1 * (1.07298568411666e-25 + (fConst1 * (4.4344097371444e-29 + (fConst1 * (1.63282987404348e-33 + fConst18))))))))))))) + (0.5 * (((fConst1 * ((fConst1 * ((fConst1 * ((fConst1 * ((fConst1 * ((fConst1 * (fConst17 - 1.12017008405057e-33)) - 2.68390877243249e-29)) - 2.76343706770825e-26)) - 1.93946085329172e-23)) - 8.29607943811672e-21)) - 1.41480755159492e-18)) - 6.87339214912114e-17) + (0.5 * (fConst1 * ((fConst1 * ((fConst1 * ((fConst1 * ((fConst1 * ((fConst1 * (0 - (2.86589792702458e-34 + fConst16))) - 6.29844123704863e-30)) - 6.96590249983833e-27)) - 2.97472992156056e-24)) - 4.85407145719168e-22)) - 2.26821940920998e-20))))))));
	fConst38 = (1.0 / fConst37);
	fConst39 = (1.29594227235659e-40 * fConst1);
	fConst40 = (1.17227175222998e-40 * fConst1);
	fConst41 = (((fConst1 * ((fConst1 * (6.72185939565773e-21 + (fConst1 * ((fConst1 * (3.96129387282593e-28 + (fConst1 * (8.60503380045389e-34 + fConst40)))) - 4.46652612440854e-25)))) - 2.17087377052947e-18)) - 1.32343844239659e-17) + (0.5 * (fConst1 * (4.36734685990874e-21 + (fConst1 * ((fConst1 * (1.58018238163299e-26 + (fConst1 * ((fConst1 * (8.87073657190112e-34 + fConst39)) - 1.64126469795529e-30)))) - 1.52868099778786e-23))))));
	fConst42 = (1.03675381788527e-39 * fConst1);
	fConst43 = (9.37817401783986e-40 * fConst1);
	fConst44 = (((fConst1 * ((fConst21 * (8.93305224881709e-25 + (fConst1 * ((fConst1 * (0 - (5.16302028027233e-33 + fConst43))) - 1.58451754913037e-27)))) - 4.34174754105893e-18)) - 5.29375376958635e-17) + (0.5 * (fConst1 * (8.73469371981747e-21 + (fConst21 * ((fConst1 * (6.56505879182116e-30 + (fConst1 * (0 - (5.32244194314067e-33 + fConst42))))) - 3.16036476326599e-26))))));
	fConst45 = (3.62863836259845e-39 * fConst1);
	fConst46 = (3.28236090624395e-39 * fConst1);
	fConst47 = (((fConst1 * (4.34174754105893e-18 + (fConst1 * ((fConst1 * (8.93305224881709e-25 + (fConst1 * (1.58451754913037e-27 + (fConst1 * (1.20470473206354e-32 + fConst46)))))) - 2.68874375826309e-20)))) - 5.29375376958635e-17) + (0.5 * (fConst1 * ((fConst1 * (6.11472399115143e-23 + (fConst1 * ((fConst1 * ((fConst1 * (1.24190312006616e-32 + fConst45)) - 6.56505879182116e-30)) - 3.16036476326599e-26)))) - 8.73469371981747e-21))));
	fConst48 = (7.2572767251969e-39 * fConst1);
	fConst49 = (6.5647218124879e-39 * fConst1);
	fConst50 = ((5.29375376958635e-17 + (fConst1 * (1.30252426231768e-17 + (fConst21 * ((fConst1 * (1.58451754913037e-27 + (fConst1 * (0 - (1.20470473206354e-32 + fConst49))))) - 2.67991567464513e-24))))) + (0.5 * (fConst1 * ((fConst21 * (9.48109428979796e-26 + (fConst1 * ((fConst1 * (0 - (1.24190312006616e-32 + fConst48))) - 6.56505879182116e-30)))) - 2.62040811594524e-20))));
	fConst51 = ((1.32343844239659e-16 + (fConst21 * (4.03311563739464e-20 + (fConst21 * ((8.20590226560988e-39 * fConst21) - 3.96129387282593e-27))))) + (0.5 * (fConst21 * ((fConst21 * (1.64126469795529e-29 + (9.07159590649613e-39 * fConst21))) - 9.17208598672714e-23))));
	fConst52 = ((5.29375376958635e-17 + (fConst1 * ((fConst21 * (2.67991567464513e-24 + (fConst1 * (1.58451754913037e-27 + (fConst1 * (1.20470473206354e-32 - fConst49)))))) - 1.30252426231768e-17))) + (0.5 * (fConst1 * (2.62040811594524e-20 + (fConst21 * ((fConst1 * ((fConst1 * (1.24190312006616e-32 - fConst48)) - 6.56505879182116e-30)) - 9.48109428979796e-26))))));
	fConst53 = (((fConst1 * ((fConst1 * ((fConst1 * ((fConst1 * (1.58451754913037e-27 + (fConst1 * (fConst46 - 1.20470473206354e-32)))) - 8.93305224881709e-25)) - 2.68874375826309e-20)) - 4.34174754105893e-18)) - 5.29375376958635e-17) + (0.5 * (fConst1 * (8.73469371981747e-21 + (fConst1 * (6.11472399115143e-23 + (fConst1 * (3.16036476326599e-26 + (fConst1 * ((fConst1 * (fConst45 - 1.24190312006616e-32)) - 6.56505879182116e-30))))))))));
	fConst54 = (((fConst1 * (4.34174754105893e-18 + (fConst21 * ((fConst1 * ((fConst1 * (5.16302028027233e-33 - fConst43)) - 1.58451754913037e-27)) - 8.93305224881709e-25)))) - 5.29375376958635e-17) + (0.5 * (fConst1 * ((fConst21 * (3.16036476326599e-26 + (fConst1 * (6.56505879182116e-30 + (fConst1 * (5.32244194314067e-33 - fConst42)))))) - 8.73469371981747e-21))));
	fConst55 = (((fConst1 * (2.17087377052947e-18 + (fConst1 * (6.72185939565773e-21 + (fConst1 * (4.46652612440854e-25 + (fConst1 * (3.96129387282593e-28 + (fConst1 * (fConst40 - 8.60503380045389e-34)))))))))) - 1.32343844239659e-17) + (0.5 * (fConst1 * ((fConst1 * ((fConst1 * ((fConst1 * ((fConst1 * (fConst39 - 8.87073657190112e-34)) - 1.64126469795529e-30)) - 1.58018238163299e-26)) - 1.52868099778786e-23)) - 4.36734685990874e-21))));
	fConst56 = (fConst21 / fConst37);
	fConst57 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst58 = (1 + fConst57);
	fConst59 = (0.027 / fConst58);
	fConst60 = (0 - ((1 - fConst57) / fConst58));
	fConst61 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst62 = (0 - fConst61);
	fConst63 = (1 + fConst61);
	fConst64 = (0.025 / fConst63);
	fConst65 = (0 - ((1 - fConst61) / fConst63));
	fConst66 = (1.0360737530688401e-13 * fConst1);
	fConst67 = (5.38043573960525e-13 * fConst1);
	fConst68 = (0.1 * (fConst67 - 3.45357917689612e-12));
	fConst69 = (0 - (3.45357917689612e-12 + fConst67));
	fConst70 = (0.1 * (3.45357917689612e-12 + fConst6));
	fConst71 = (3.4535791768961205e-14 * fConst1);
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
	double 	fSlow2 = (0.007000000000000006 * (1 - double(fslider1)));
	double 	fSlow3 = (0.007000000000000006 * double(fslider2));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fRec6[0] = ((0.993 * fRec6[1]) + fSlow2);
		double fTemp1 = (2.49252253398618e-07 + (fConst1 * (fConst5 + (fConst3 * fRec6[0]))));
		fRec14[0] = ((fSlow0 * fTemp0) - (fConst38 * ((((((((fConst36 * fRec14[1]) + (fConst35 * fRec14[2])) + (fConst34 * fRec14[3])) + (fConst33 * fRec14[4])) + (fConst32 * fRec14[5])) + (fConst28 * fRec14[6])) + (fConst24 * fRec14[7])) + (fConst19 * fRec14[8]))));
		fRec15[0] = ((0.993 * fRec15[1]) + fSlow3);
		fRec16[0] = ((fConst60 * fRec16[1]) + (fConst59 * (fRec13[1] + fRec13[2])));
		fRec13[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec16[0] + (fConst56 * (fRec15[0] * (((((((((fConst55 * fRec14[0]) + (fConst54 * fRec14[1])) + (fConst53 * fRec14[2])) + (fConst52 * fRec14[3])) + (fConst51 * fRec14[4])) + (fConst50 * fRec14[5])) + (fConst47 * fRec14[6])) + (fConst44 * fRec14[7])) + (fConst41 * fRec14[8]))))) - 3.571981)) - 117.70440740740739);
		fRec12[0] = ((fConst65 * fRec12[1]) + (fConst64 * ((fConst61 * fRec13[0]) + (fConst62 * fRec13[1]))));
		fRec17[0] = ((fConst60 * fRec17[1]) + (fConst59 * (fRec11[1] + fRec11[2])));
		fRec11[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec17[0] + fRec12[0]) - 3.571981)) - 117.70440740740739);
		fRec10[0] = ((fConst65 * fRec10[1]) + (fConst64 * ((fConst61 * fRec11[0]) + (fConst62 * fRec11[1]))));
		fRec18[0] = ((fConst60 * fRec18[1]) + (fConst59 * (fRec9[1] + fRec9[2])));
		fRec9[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec18[0] + fRec10[0]) - 3.571981)) - 117.70440740740739);
		fRec8[0] = ((fConst65 * fRec8[1]) + (fConst64 * ((fConst61 * fRec9[0]) + (fConst62 * fRec9[1]))));
		fRec7[0] = (fRec8[0] - ((((fRec7[1] * (7.47756760195853e-07 + (fConst1 * (fConst15 + (fConst14 * fRec6[0]))))) + (fRec7[2] * (7.47756760195853e-07 + (fConst1 * (fConst13 + (fConst11 * fRec6[0])))))) + (fRec7[3] * (2.49252253398618e-07 + (fConst1 * (fConst9 + (fConst8 * fRec6[0])))))) / fTemp1));
		fRec19[0] = ((fConst60 * fRec19[1]) + (fConst59 * (fRec5[1] + fRec5[2])));
		fRec5[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec19[0] + (fConst21 * ((fRec15[0] * ((((fRec7[0] * ((fConst71 * fRec6[0]) + fConst70)) + (0.1 * (fRec7[1] * (fConst69 + (fConst1 * (0 - (1.03607375306884e-12 * fRec6[0]))))))) + (fRec7[2] * (fConst68 + (fConst66 * fRec6[0])))) + (0.1 * (fRec7[3] * (fConst7 + (fConst1 * (0 - (3.45357917689612e-13 * fRec6[0])))))))) / fTemp1))) - 3.571981)) - 117.70440740740739);
		fRec4[0] = ((fConst65 * fRec4[1]) + (fConst64 * ((fConst61 * fRec5[0]) + (fConst62 * fRec5[1]))));
		fRec20[0] = ((fConst60 * fRec20[1]) + (fConst59 * (fRec3[1] + fRec3[2])));
		fRec3[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec20[0] + fRec4[0]) - 3.571981)) - 117.70440740740739);
		fRec2[0] = ((fConst65 * fRec2[1]) + (fConst64 * ((fConst61 * fRec3[0]) + (fConst62 * fRec3[1]))));
		fRec21[0] = ((fConst60 * fRec21[1]) + (fConst59 * (fRec1[1] + fRec1[2])));
		fRec1[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec21[0] + fRec2[0]) - 3.571981)) - 117.70440740740739);
		fRec0[0] = ((fConst65 * fRec0[1]) + (fConst64 * ((fConst61 * fRec1[0]) + (fConst62 * fRec1[1]))));
		output0[i] = (FAUSTFLOAT)(fRec0[0] + (fSlow1 * fTemp0));
		// post processing
		fRec0[1] = fRec0[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec21[1] = fRec21[0];
		fRec2[1] = fRec2[0];
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
		fRec20[1] = fRec20[0];
		fRec4[1] = fRec4[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec19[1] = fRec19[0];
		for (int i=3; i>0; i--) fRec7[i] = fRec7[i-1];
		fRec8[1] = fRec8[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec18[1] = fRec18[0];
		fRec10[1] = fRec10[0];
		fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
		fRec17[1] = fRec17[0];
		fRec12[1] = fRec12[0];
		fRec13[2] = fRec13[1]; fRec13[1] = fRec13[0];
		fRec16[1] = fRec16[0];
		fRec15[1] = fRec15[0];
		for (int i=8; i>0; i--) fRec14[i] = fRec14[i-1];
		fRec6[1] = fRec6[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("fuzzdrive.Distortion",N_("Drive"),"S","",&fslider1, 0.5, 0.0, 0.99, 0.01);
	reg.registerVar("fuzzdrive.Level",N_("Level"),"S","",&fslider2, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("fuzzdrive.wet_dry",N_("wet/dry"),"S",N_("percentage of processed signal in output signal"),&fslider0, 1e+02, 0.0, 1e+02, 1.0);
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
