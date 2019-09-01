// generated from file '../src/plugins/fuzzdrive.dsp' by dsp2cc:
// Code generated with Faust 2.15.11 (https://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"
#include "clipping.h"

namespace pluginlib {
namespace fuzzdrive {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT fHslider0;
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
	double fRec2[9];
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
	double fConst39;
	double fConst40;
	double fConst41;
	double fConst42;
	double fConst43;
	double fConst44;
	double fConst45;
	FAUSTFLOAT fVslider1;
	double fRec3[2];
	double fConst46;
	double fConst47;
	double fConst48;
	double fConst49;
	double fConst50;
	double fConst51;
	double fConst52;
	double fConst53;
	double fRec1[4];
	double fConst54;
	double fConst55;
	double fConst56;
	double fConst57;
	double fConst58;
	double fConst59;
	double fConst60;
	double fConst61;

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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec0[l0] = 0.0;
	for (int l1 = 0; (l1 < 9); l1 = (l1 + 1)) fRec2[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec3[l2] = 0.0;
	for (int l3 = 0; (l3 < 4); l3 = (l3 + 1)) fRec1[l3] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSamplingFreq)));
	fConst1 = mydsp_faustpower2_f(fConst0);
	fConst2 = (1.2113474773043201e-39 * fConst0);
	fConst3 = (2.4502004602049298e-40 * fConst0);
	fConst4 = (1.20954612086615e-39 * fConst0);
	fConst5 = ((((((((((((((((fConst2 + 1.63282987404348e-33) * fConst0) + 4.4344097371444002e-29) * fConst0) + 1.0729856841166599e-25) * fConst0) + 1.73266579347222e-22) * fConst0) + 1.3110285209256499e-19) * fConst0) + 4.7476768760616798e-17) * fConst0) + 7.1203466517717607e-15) + (0.5 * ((((((((((((((fConst3 + -1.12017008405057e-33) * fConst0) + -2.6839087724324902e-29) * fConst0) + -2.7634370677082497e-26) * fConst0) + -1.9394608532917201e-23) * fConst0) + -8.2960794381167194e-21) * fConst0) + -1.41480755159492e-18) * fConst0) + -6.8733921491211398e-17) + (0.5 * ((((((((((((-2.8658979270245801e-34 - fConst4) * fConst0) + -6.2984412370486301e-30) * fConst0) + -6.9659024998383304e-27) * fConst0) + -2.9747299215605601e-24) * fConst0) + -4.8540714571916797e-22) * fConst0) + -2.2682194092099799e-20) * fConst0))))) * fConst0) + 3.1242691586914298e-13);
	fConst6 = (fConst1 / fConst5);
	fConst7 = (1.1722717522299801e-40 * fConst0);
	fConst8 = (1.2959422723565901e-40 * fConst0);
	fConst9 = ((((((((((((fConst7 + -8.6050338004538901e-34) * fConst0) + 3.9612938728259302e-28) * fConst0) + 4.46652612440854e-25) * fConst0) + 6.7218593956577298e-21) * fConst0) + 2.1708737705294701e-18) * fConst0) + -1.3234384423965901e-17) + (0.5 * ((((((((((fConst8 + -8.8707365719011199e-34) * fConst0) + -1.6412646979552901e-30) * fConst0) + -1.5801823816329901e-26) * fConst0) + -1.52868099778786e-23) * fConst0) + -4.3673468599087398e-21) * fConst0)));
	fConst10 = (1.0 / fConst5);
	fConst11 = (9.69077981843452e-39 * fConst0);
	fConst12 = (1.96016036816394e-39 * fConst0);
	fConst13 = (9.6763689669291996e-39 * fConst0);
	fConst14 = ((((((((((((((-9.7969792442608704e-33 - fConst11) * fConst0) + -1.7737638948577601e-28) * fConst0) + -2.1459713682333098e-25) * fConst1) + 2.62205704185131e-19) * fConst0) + 1.8990707504246699e-16) * fConst0) + 4.2722079910630501e-14) + (0.5 * ((((((((((((6.7210205043034e-33 - fConst12) * fConst0) + 1.0735635089729999e-28) * fConst0) + 5.5268741354164903e-26) * fConst1) + -1.65921588762334e-20) * fConst0) + -5.6592302063796899e-18) * fConst0) + -4.1240352894726799e-16) + (0.5 * ((((((((((fConst13 + 1.71953875621475e-33) * fConst0) + 2.5193764948194501e-29) * fConst0) + 1.3931804999676701e-26) * fConst1) + -9.7081429143833594e-22) * fConst0) + -9.0728776368399005e-20) * fConst0))))) * fConst0) + 2.4994153269531398e-12);
	fConst15 = (3.39177293645208e-38 * fConst0);
	fConst16 = (6.8605612885737902e-39 * fConst0);
	fConst17 = (3.3867291384252199e-38 * fConst0);
	fConst18 = ((((((((((((((((fConst15 + 2.2859618236608701e-32) * fConst0) + 1.7737638948577601e-28) * fConst0) + -2.1459713682333098e-25) * fConst0) + -6.9306631738888905e-22) * fConst0) + -2.62205704185131e-19) * fConst0) + 1.8990707504246699e-16) * fConst0) + 9.96848531248046e-14) + (0.5 * ((((((((((((((fConst16 + -1.56823811767079e-32) * fConst0) + -1.0735635089729999e-28) * fConst0) + 5.5268741354164903e-26) * fConst0) + 7.7578434131668804e-23) * fConst0) + 1.65921588762334e-20) * fConst0) + -5.6592302063796899e-18) * fConst0) + -9.6227490087695898e-16) + (0.5 * ((((((((((((-4.0122570978344203e-33 - fConst17) * fConst0) + -2.5193764948194501e-29) * fConst0) + 1.3931804999676701e-26) * fConst0) + 1.1898919686242301e-23) * fConst0) + 9.7081429143833594e-22) * fConst0) + -9.0728776368399005e-20) * fConst0))))) * fConst0) + 8.7479536443359908e-12);
	fConst19 = (6.78354587290416e-38 * fConst0);
	fConst20 = (1.3721122577147601e-38 * fConst0);
	fConst21 = (6.7734582768504399e-38 * fConst0);
	fConst22 = ((((((((((((((-2.2859618236608701e-32 - fConst19) * fConst0) + 1.7737638948577601e-28) * fConst0) + 6.4379141046999399e-25) * fConst1) + -7.8661711255539204e-19) * fConst0) + -1.8990707504246699e-16) * fConst0) + 9.96848531248046e-14) + (0.5 * ((((((((((((1.56823811767079e-32 - fConst20) * fConst0) + -1.0735635089729999e-28) * fConst0) + -1.6580622406249499e-25) * fConst1) + 4.9776476628700302e-20) * fConst0) + 5.6592302063796899e-18) * fConst0) + -9.6227490087695898e-16) + (0.5 * ((((((((((fConst21 + 4.0122570978344203e-33) * fConst0) + -2.5193764948194501e-29) * fConst0) + -4.1795414999030003e-26) * fConst1) + 2.9124428743150101e-21) * fConst0) + 9.0728776368399005e-20) * fConst0))))) * fConst0) + 1.7495907288672001e-11);
	fConst23 = (((((((((8.4794323411302099e-38 * fConst1) + -4.4344097371444e-28) * fConst1) + 1.0395994760833299e-21) * fConst1) + -4.74767687606168e-16) + (0.5 * (((((((1.71514032214345e-38 * fConst1) + 2.68390877243249e-28) * fConst1) + -1.1636765119750301e-22) * fConst1) + 1.41480755159492e-17) + (0.5 * (((((6.2984412370486305e-29 - (8.4668228460630496e-38 * fConst1)) * fConst1) + -1.7848379529363399e-23) * fConst1) + 2.2682194092099801e-19))))) * fConst1) + 2.186988411084e-11);
	fConst24 = ((((((((((((((2.2859618236608701e-32 - fConst19) * fConst0) + 1.7737638948577601e-28) * fConst0) + -6.4379141046999399e-25) * fConst1) + 7.8661711255539204e-19) * fConst0) + -1.8990707504246699e-16) * fConst0) + -9.96848531248046e-14) + (0.5 * ((((((((((((-1.56823811767079e-32 - fConst20) * fConst0) + -1.0735635089729999e-28) * fConst0) + 1.6580622406249499e-25) * fConst1) + -4.9776476628700302e-20) * fConst0) + 5.6592302063796899e-18) * fConst0) + 9.6227490087695898e-16) + (0.5 * ((((((((((fConst21 + -4.0122570978344203e-33) * fConst0) + -2.5193764948194501e-29) * fConst0) + 4.1795414999030003e-26) * fConst1) + -2.9124428743150101e-21) * fConst0) + 9.0728776368399005e-20) * fConst0))))) * fConst0) + 1.7495907288672001e-11);
	fConst25 = ((((((((((((((((fConst15 + -2.2859618236608701e-32) * fConst0) + 1.7737638948577601e-28) * fConst0) + 2.1459713682333098e-25) * fConst0) + -6.9306631738888905e-22) * fConst0) + 2.62205704185131e-19) * fConst0) + 1.8990707504246699e-16) * fConst0) + -9.96848531248046e-14) + (0.5 * ((((((((((((((fConst16 + 1.56823811767079e-32) * fConst0) + -1.0735635089729999e-28) * fConst0) + -5.5268741354164903e-26) * fConst0) + 7.7578434131668804e-23) * fConst0) + -1.65921588762334e-20) * fConst0) + -5.6592302063796899e-18) * fConst0) + 9.6227490087695898e-16) + (0.5 * ((((((((((((4.0122570978344203e-33 - fConst17) * fConst0) + -2.5193764948194501e-29) * fConst0) + -1.3931804999676701e-26) * fConst0) + 1.1898919686242301e-23) * fConst0) + -9.7081429143833594e-22) * fConst0) + -9.0728776368399005e-20) * fConst0))))) * fConst0) + 8.7479536443359908e-12);
	fConst26 = ((((((((((((((9.7969792442608704e-33 - fConst11) * fConst0) + -1.7737638948577601e-28) * fConst0) + 2.1459713682333098e-25) * fConst1) + -2.62205704185131e-19) * fConst0) + 1.8990707504246699e-16) * fConst0) + -4.2722079910630501e-14) + (0.5 * ((((((((((((-6.7210205043034e-33 - fConst12) * fConst0) + 1.0735635089729999e-28) * fConst0) + -5.5268741354164903e-26) * fConst1) + 1.65921588762334e-20) * fConst0) + -5.6592302063796899e-18) * fConst0) + 4.1240352894726799e-16) + (0.5 * ((((((((((fConst13 + -1.71953875621475e-33) * fConst0) + 2.5193764948194501e-29) * fConst0) + -1.3931804999676701e-26) * fConst1) + 9.7081429143833594e-22) * fConst0) + -9.0728776368399005e-20) * fConst0))))) * fConst0) + 2.4994153269531398e-12);
	fConst27 = ((((((((((((((((fConst2 + -1.63282987404348e-33) * fConst0) + 4.4344097371444002e-29) * fConst0) + -1.0729856841166599e-25) * fConst0) + 1.73266579347222e-22) * fConst0) + -1.3110285209256499e-19) * fConst0) + 4.7476768760616798e-17) * fConst0) + -7.1203466517717607e-15) + (0.5 * ((((((((((((((fConst3 + 1.12017008405057e-33) * fConst0) + -2.6839087724324902e-29) * fConst0) + 2.7634370677082497e-26) * fConst0) + -1.9394608532917201e-23) * fConst0) + 8.2960794381167194e-21) * fConst0) + -1.41480755159492e-18) * fConst0) + 6.8733921491211398e-17) + (0.5 * ((((((((((((2.8658979270245801e-34 - fConst4) * fConst0) + -6.2984412370486301e-30) * fConst0) + 6.9659024998383304e-27) * fConst0) + -2.9747299215605601e-24) * fConst0) + 4.8540714571916797e-22) * fConst0) + -2.2682194092099799e-20) * fConst0))))) * fConst0) + 3.1242691586914298e-13);
	fConst28 = (9.3781740178398601e-40 * fConst0);
	fConst29 = (1.0367538178852699e-39 * fConst0);
	fConst30 = ((((((((((5.1630202802723303e-33 - fConst28) * fConst0) + -1.5845175491303699e-27) * fConst0) + -8.9330522488170893e-25) * fConst1) + 4.3417475410589302e-18) * fConst0) + -5.2937537695863498e-17) + (0.5 * ((((((((5.3224419431406702e-33 - fConst29) * fConst0) + 6.5650587918211606e-30) * fConst0) + 3.16036476326599e-26) * fConst1) + -8.7346937198174706e-21) * fConst0)));
	fConst31 = (3.2823609062439498e-39 * fConst0);
	fConst32 = (3.62863836259845e-39 * fConst0);
	fConst33 = ((((((((((((fConst31 + -1.20470473206354e-32) * fConst0) + 1.5845175491303699e-27) * fConst0) + -8.9330522488170893e-25) * fConst0) + -2.6887437582630901e-20) * fConst0) + -4.3417475410589302e-18) * fConst0) + -5.2937537695863498e-17) + (0.5 * ((((((((((fConst32 + -1.2419031200661599e-32) * fConst0) + -6.5650587918211606e-30) * fConst0) + 3.16036476326599e-26) * fConst0) + 6.1147239911514295e-23) * fConst0) + 8.7346937198174706e-21) * fConst0)));
	fConst34 = (6.5647218124878997e-39 * fConst0);
	fConst35 = (7.2572767251969e-39 * fConst0);
	fConst36 = ((((((((((1.20470473206354e-32 - fConst34) * fConst0) + 1.5845175491303699e-27) * fConst0) + 2.6799156746451301e-24) * fConst1) + -1.3025242623176801e-17) * fConst0) + 5.2937537695863498e-17) + (0.5 * ((((((((1.2419031200661599e-32 - fConst35) * fConst0) + -6.5650587918211606e-30) * fConst0) + -9.4810942897979596e-26) * fConst1) + 2.62040811594524e-20) * fConst0)));
	fConst37 = (((((((8.2059022656098801e-39 * fConst1) + -3.9612938728259299e-27) * fConst1) + 4.03311563739464e-20) * fConst1) + 1.32343844239659e-16) + (0.5 * (((((9.07159590649613e-39 * fConst1) + 1.6412646979552901e-29) * fConst1) + -9.1720859867271395e-23) * fConst1)));
	fConst38 = ((((((((((-1.20470473206354e-32 - fConst34) * fConst0) + 1.5845175491303699e-27) * fConst0) + -2.6799156746451301e-24) * fConst1) + 1.3025242623176801e-17) * fConst0) + 5.2937537695863498e-17) + (0.5 * ((((((((-1.2419031200661599e-32 - fConst35) * fConst0) + -6.5650587918211606e-30) * fConst0) + 9.4810942897979596e-26) * fConst1) + -2.62040811594524e-20) * fConst0)));
	fConst39 = ((((((((((((fConst31 + 1.20470473206354e-32) * fConst0) + 1.5845175491303699e-27) * fConst0) + 8.9330522488170893e-25) * fConst0) + -2.6887437582630901e-20) * fConst0) + 4.3417475410589302e-18) * fConst0) + -5.2937537695863498e-17) + (0.5 * ((((((((((fConst32 + 1.2419031200661599e-32) * fConst0) + -6.5650587918211606e-30) * fConst0) + -3.16036476326599e-26) * fConst0) + 6.1147239911514295e-23) * fConst0) + -8.7346937198174706e-21) * fConst0)));
	fConst40 = ((((((((((-5.1630202802723303e-33 - fConst28) * fConst0) + -1.5845175491303699e-27) * fConst0) + 8.9330522488170893e-25) * fConst1) + -4.3417475410589302e-18) * fConst0) + -5.2937537695863498e-17) + (0.5 * ((((((((-5.3224419431406702e-33 - fConst29) * fConst0) + 6.5650587918211606e-30) * fConst0) + -3.16036476326599e-26) * fConst1) + 8.7346937198174706e-21) * fConst0)));
	fConst41 = ((((((((((((fConst7 + 8.6050338004538901e-34) * fConst0) + 3.9612938728259302e-28) * fConst0) + -4.46652612440854e-25) * fConst0) + 6.7218593956577298e-21) * fConst0) + -2.1708737705294701e-18) * fConst0) + -1.3234384423965901e-17) + (0.5 * ((((((((((fConst8 + 8.8707365719011199e-34) * fConst0) + -1.6412646979552901e-30) * fConst0) + 1.5801823816329901e-26) * fConst0) + -1.52868099778786e-23) * fConst0) + 4.3673468599087398e-21) * fConst0)));
	fConst42 = (1.0722229453354299e-15 * fConst0);
	fConst43 = (((-2.8173689510973699e-13 - fConst42) * fConst0) + 2.53046873750701e-09);
	fConst44 = (3.6297149828678902e-14 * fConst0);
	fConst45 = (((-2.5180162216562701e-10 - fConst44) * fConst0) + 2.4925225339861801e-08);
	fConst46 = (((fConst42 + -2.8173689510973699e-13) * fConst0) + -2.53046873750701e-09);
	fConst47 = (((fConst44 + -2.5180162216562701e-10) * fConst0) + -2.4925225339861801e-08);
	fConst48 = (3.5740764844514402e-16 * fConst0);
	fConst49 = (((2.8173689510973699e-13 - fConst48) * fConst0) + -2.53046873750701e-09);
	fConst50 = (1.2099049942893e-14 * fConst0);
	fConst51 = (((2.5180162216562701e-10 - fConst50) * fConst0) + -2.4925225339861801e-08);
	fConst52 = (((fConst48 + 2.8173689510973699e-13) * fConst0) + 2.53046873750701e-09);
	fConst53 = (((fConst50 + 2.5180162216562701e-10) * fConst0) + 2.4925225339861801e-08);
	fConst54 = (1.7934785798684201e-13 * fConst0);
	fConst55 = (0.10000000000000001 * (fConst54 + 3.4535791768961199e-12));
	fConst56 = (3.4535791768961205e-14 * fConst0);
	fConst57 = (5.3804357396052502e-13 * fConst0);
	fConst58 = (-3.4535791768961199e-12 - fConst57);
	fConst59 = (0.10000000000000001 * (fConst57 + -3.4535791768961199e-12));
	fConst60 = (1.0360737530688401e-13 * fConst0);
	fConst61 = (3.4535791768961199e-12 - fConst54);
	fVslider0 = FAUSTFLOAT(100.0);
	fHslider0 = FAUSTFLOAT(-2.0);
	fVslider1 = FAUSTFLOAT(0.5);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double fSlow0 = (0.01 * double(fVslider0));
	double fSlow1 = (1.0 - fSlow0);
	double fSlow2 = (0.0070000000000000062 * std::pow(10.0, (0.050000000000000003 * double(fHslider0))));
	double fSlow3 = (0.0070000000000000062 * (1.0 - double(fVslider1)));
	for (int i = 0; (i < count); i = (i + 1)) {
		double fTemp0 = double(input0[i]);
		fRec0[0] = (fSlow2 + (0.99299999999999999 * fRec0[1]));
		double fTemp1 = (fSlow0 * fTemp0);
		fRec2[0] = (fTemp1 - (fConst10 * ((((((((fConst14 * fRec2[1]) + (fConst18 * fRec2[2])) + (fConst22 * fRec2[3])) + (fConst23 * fRec2[4])) + (fConst24 * fRec2[5])) + (fConst25 * fRec2[6])) + (fConst26 * fRec2[7])) + (fConst27 * fRec2[8]))));
		fRec3[0] = (fSlow3 + (0.99299999999999999 * fRec3[1]));
		double fTemp2 = ((fConst0 * (fConst52 + (fConst53 * fRec3[0]))) + 2.49252253398618e-07);
		fRec1[0] = ((fConst6 * (((((((((fConst9 * fRec2[0]) + (fConst30 * fRec2[1])) + (fConst33 * fRec2[2])) + (fConst36 * fRec2[3])) + (fConst37 * fRec2[4])) + (fConst38 * fRec2[5])) + (fConst39 * fRec2[6])) + (fConst40 * fRec2[7])) + (fConst41 * fRec2[8]))) - ((((fRec1[1] * ((fConst0 * (fConst43 + (fConst45 * fRec3[0]))) + 7.4775676019585299e-07)) + (fRec1[2] * ((fConst0 * (fConst46 + (fConst47 * fRec3[0]))) + 7.4775676019585299e-07))) + (fRec1[3] * ((fConst0 * (fConst49 + (fConst51 * fRec3[0]))) + 2.49252253398618e-07))) / fTemp2));
		output0[i] = FAUSTFLOAT(((fSlow1 * fTemp0) + (fRec0[0] * double(asymhardclip2(double((fTemp1 - double(opamp(double(((fConst1 * (((((fRec1[0] * (fConst55 + (fConst56 * fRec3[0]))) + (0.10000000000000001 * (fRec1[1] * (fConst58 + (fConst0 * (0.0 - (1.0360737530688401e-12 * fRec3[0]))))))) + (fRec1[2] * (fConst59 + (fConst60 * fRec3[0])))) + (0.10000000000000001 * (fRec1[3] * (fConst61 + (fConst0 * (0.0 - (3.4535791768961202e-13 * fRec3[0]))))))) / fTemp2)) - fTemp1)))))))))));
		fRec0[1] = fRec0[0];
		for (int j0 = 8; (j0 > 0); j0 = (j0 - 1)) {
			fRec2[j0] = fRec2[(j0 - 1)];
		}
		fRec3[1] = fRec3[0];
		for (int j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
			fRec1[j1] = fRec1[(j1 - 1)];
		}
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("fuzzdrive.Distortion",N_("Drive"),"S","",&fVslider1, 0.5, 0.0, 0.98999999999999999, 0.01);
	reg.registerVar("fuzzdrive.Level",N_("Level"),"S","",&fHslider0, -2.0, -20.0, 12.0, 0.10000000000000001);
	reg.registerVar("fuzzdrive.wet_dry",N_("Wet/Dry"),"S",N_("percentage of processed signal in output signal"),&fVslider0, 100.0, 0.0, 100.0, 1.0);
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
