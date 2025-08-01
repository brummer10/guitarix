// generated from file '../src/plugins/fuzzfacerm.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

#include "trany.h"

namespace pluginlib {
namespace fuzzfacerm {

class Dsp: public PluginDef {
private:
	int fSampleRate;
	FAUSTFLOAT fVslider0;
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
	FAUSTFLOAT fVslider1;
	double fRec1[2];
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
	double fConst56;
	double fConst57;
	double fConst58;
	double fConst59;
	double fConst60;
	double fRec2[4];
	double fConst61;
	double fConst62;
	double fConst63;
	double fConst64;
	double fConst65;
	double fConst66;
	double fConst67;
	double fConst68;


	gx_resample::FixedRateResampler smpCl;
	double fConstCl0;
	double fConstCl1;
	double fConstCl2;
	double fConstCl3;
	double fVecCl0[2];
	double fRecCl7[2];
	double fRecCl6[3];
	double fConstCl4;
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
	id = "fuzzfacerm";
	name = N_("Fuzz Face Mayer");
	groups = 0;
	description = N_("Roger Mayer Fuzz Face simulation"); // description (tooltip)
	category = N_("Fuzz");       // category
	shortname = N_("FF Mayer");     // shortname
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
	for (int l2 = 0; l2 < 4; l2 = l2 + 1) fRec2[l2] = 0.0;

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
	fConst1 = 5.85504578964162e-29 * fConst0;
	fConst2 = fConst0 * (fConst1 + 4.00083755606776e-26) + 2.83746860731297e-29;
	fConst3 = 1.19490650740761e-31 * fConst0;
	fConst4 = fConst0 * (fConst3 + 2.08767320417856e-28) + 8.68612838978577e-26;
	fConst5 = 6.18674104772942e-29 * fConst0;
	fConst6 = fConst0 * (-4.00204457374009e-26 - fConst5) + -2.83832448080453e-29;
	fConst7 = 1.26259937209307e-31 * fConst0;
	fConst8 = fConst0 * (-2.15993317197785e-28 - fConst7) + -8.68874841067831e-26;
	fConst9 = 3.22405119745267e-14 * fConst0;
	fConst10 = fConst0 * (-2.08898268350887e-11 - fConst9) + -2.21793415696022e-11;
	fConst11 = 3.05119726906337e-14 * fConst0;
	fConst12 = fConst0 * (fConst11 + 2.08816997599123e-11) + 2.21726535708769e-11;
	fConst13 = 1.72853928389298e-15 * fConst0;
	fConst14 = fConst0 * (fConst13 + 4.32740215906676e-13) + 2.6123111187704e-10;
	fConst15 = 3.31695258087803e-30 * fConst0;
	fConst16 = fConst0 * (fConst0 * (fConst15 + 8.26874714950455e-28) + 5.00406457485288e-25) + 3.54897544287011e-28;
	fConst17 = 6.76928646854567e-33 * fConst0;
	fConst18 = fConst0 * (fConst0 * (fConst17 + 8.88886207590151e-30) + 2.81644163364677e-27);
	fConst19 = 2.23179427996828e-12 * fConst0;
	fConst20 = fConst19 + -2.84573463334658e-11;
	fConst21 = 2.27734110200845e-12 * fConst0;
	fConst22 = 2.90381085035365e-11 - fConst21;
	fConst23 = mydsp_faustpower2_f(fConst0);
	fConst24 = mydsp_faustpower3_f(fConst0);
	fConst25 = fConst0 * (4.00083755606776e-26 - fConst1) + -2.83746860731297e-29;
	fConst26 = fConst0 * (2.08767320417856e-28 - fConst3) + -8.68612838978577e-26;
	fConst27 = fConst0 * (fConst5 + -4.00204457374009e-26) + 2.83832448080453e-29;
	fConst28 = fConst0 * (fConst7 + -2.15993317197785e-28) + 8.68874841067831e-26;
	fConst29 = fConst0 * (fConst9 + -2.08898268350887e-11) + 2.21793415696022e-11;
	fConst30 = fConst0 * (2.08816997599123e-11 - fConst11) + -2.21726535708769e-11;
	fConst31 = fConst0 * (4.32740215906676e-13 - fConst13) + -2.6123111187704e-10;
	fConst32 = fConst0 * (fConst0 * (8.26874714950455e-28 - fConst15) + -5.00406457485288e-25) + 3.54897544287011e-28;
	fConst33 = fConst0 * (fConst0 * (8.88886207590151e-30 - fConst17) + -2.81644163364677e-27);
	fConst34 = 1.75651373689249e-28 * fConst0;
	fConst35 = fConst0 * (fConst34 + -4.00083755606776e-26) + -2.83746860731297e-29;
	fConst36 = 3.58471952222284e-31 * fConst0;
	fConst37 = fConst0 * (fConst36 + -2.08767320417856e-28) + -8.68612838978577e-26;
	fConst38 = 1.85602231431883e-28 * fConst0;
	fConst39 = fConst0 * (4.00204457374009e-26 - fConst38) + 2.83832448080453e-29;
	fConst40 = 3.78779811627921e-31 * fConst0;
	fConst41 = fConst0 * (2.15993317197785e-28 - fConst40) + 8.68874841067831e-26;
	fConst42 = 9.67215359235801e-14 * fConst0;
	fConst43 = fConst0 * (2.08898268350887e-11 - fConst42) + 2.21793415696022e-11;
	fConst44 = 9.15359180719011e-14 * fConst0;
	fConst45 = fConst0 * (fConst44 + -2.08816997599123e-11) + -2.21726535708769e-11;
	fConst46 = 5.18561785167894e-15 * fConst0;
	fConst47 = fConst0 * (fConst46 + -4.32740215906676e-13) + -2.6123111187704e-10;
	fConst48 = 9.95085774263408e-30 * fConst0;
	fConst49 = fConst0 * (fConst0 * (fConst48 + -8.26874714950455e-28) + -5.00406457485288e-25) + 1.06469263286103e-27;
	fConst50 = 2.0307859405637e-32 * fConst0;
	fConst51 = fConst0 * (fConst0 * (fConst50 + -8.88886207590151e-30) + -2.81644163364677e-27);
	fConst52 = fConst0 * (-4.00083755606776e-26 - fConst34) + 2.83746860731297e-29;
	fConst53 = fConst0 * (-2.08767320417856e-28 - fConst36) + 8.68612838978577e-26;
	fConst54 = fConst0 * (fConst38 + 4.00204457374009e-26) + -2.83832448080453e-29;
	fConst55 = fConst0 * (fConst40 + 2.15993317197785e-28) + -8.68874841067831e-26;
	fConst56 = fConst0 * (fConst42 + 2.08898268350887e-11) + -2.21793415696022e-11;
	fConst57 = fConst0 * (-2.08816997599123e-11 - fConst44) + 2.21726535708769e-11;
	fConst58 = fConst0 * (-4.32740215906676e-13 - fConst46) + 2.6123111187704e-10;
	fConst59 = fConst0 * (fConst0 * (-8.26874714950455e-28 - fConst48) + 5.00406457485288e-25) + 1.06469263286103e-27;
	fConst60 = fConst0 * (fConst0 * (-8.88886207590151e-30 - fConst50) + 2.81644163364677e-27);
	fConst61 = 6.69538283990485e-12 * fConst0;
	fConst62 = 2.84573463334658e-11 - fConst61;
	fConst63 = 6.83202330602535e-12 * fConst0;
	fConst64 = fConst63 + -2.90381085035365e-11;
	fConst65 = fConst61 + 2.84573463334658e-11;
	fConst66 = -2.90381085035365e-11 - fConst63;
	fConst67 = -2.84573463334658e-11 - fConst19;
	fConst68 = fConst21 + 2.90381085035365e-11;

	sample_rate = 96000;
	smpCl.setup(fSampleRate, sample_rate);
	fSampleRate = sample_rate;
	fConstCl0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	fConstCl1 = std::tan(97.38937226128358 / fConstCl0);
	fConstCl2 = 1.0 / fConstCl1;
	fConstCl3 = 1.0 - fConstCl2;
	fConstCl4 = 1.0 / std::tan(270.1769682087222 / fConstCl0);
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
	double fSlow0 = 0.007000000000000006 * (1.0 - 0.05239569649125595 * (std::exp(3.0 * double(fVslider0)) + -1.0));
	double fSlow1 = 0.007000000000000006 * (1.0 - double(fVslider1));
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec0[0] = fSlow0 + 0.993 * fRec0[1];
		fRec1[0] = fSlow1 + 0.993 * fRec1[1];
		double fTemp0 = fRec0[0] * (fConst18 + fConst16 * fRec0[0] + 1.08642105394636e-24) + fConst0 * (fConst14 + fRec1[0] * (fConst12 + fRec1[0] * (fConst10 + fRec0[0] * (fConst8 + fConst6 * fRec0[0])) + fRec0[0] * (fConst4 + fConst2 * fRec0[0]))) + 2.77325369604093e-10;
		double fTemp1 = 2.1870008532593e-12 * fRec0[0];
		double fTemp2 = 4.47934267089816e-14 * fRec0[0];
		fRec2[0] = double(input0[i0]) - (fRec2[1] * (fRec0[0] * (fConst60 + fConst59 * fRec0[0] + 3.25926316183907e-24) + fConst0 * (fConst58 + fRec1[0] * (fConst57 + fRec1[0] * (fConst56 + fRec0[0] * (fConst55 + fConst54 * fRec0[0])) + fRec0[0] * (fConst53 + fConst52 * fRec0[0]))) + 8.3197610881228e-10) + fRec2[2] * (fRec0[0] * (fConst51 + fConst49 * fRec0[0] + 3.25926316183907e-24) + fConst0 * (fConst47 + fRec1[0] * (fConst45 + fRec1[0] * (fConst43 + fRec0[0] * (fConst41 + fConst39 * fRec0[0])) + fRec0[0] * (fConst37 + fConst35 * fRec0[0]))) + 8.3197610881228e-10) + fRec2[3] * (fRec0[0] * (fConst33 + fConst32 * fRec0[0] + 1.08642105394636e-24) + fConst0 * (fConst31 + fRec1[0] * (fConst30 + fRec1[0] * (fConst29 + fRec0[0] * (fConst28 + fConst27 * fRec0[0])) + fRec0[0] * (fConst26 + fConst25 * fRec0[0]))) + 2.77325369604093e-10)) / fTemp0;
		double fTemp3 = 1.34380280126945e-13 * fRec0[0];
		double fTemp4 = 6.5610025597779e-12 * fRec0[0];
		output0[i0] = FAUSTFLOAT((fRec2[0] * (fConst24 * fRec1[0] * (fTemp1 + fRec1[0] * (fTemp2 + -4.57075782744711e-14) + -2.23163352373398e-12) + fConst23 * (fConst68 + fConst67 * fRec0[0])) + fRec2[1] * (fConst24 * fRec1[0] * (fRec1[0] * (1.37122734823413e-13 - fTemp3) - fTemp4 + 6.69490057120194e-12) + fConst23 * (fConst66 + fConst65 * fRec0[0])) + fRec2[2] * (fConst24 * fRec1[0] * (fTemp4 + fRec1[0] * (fTemp3 + -1.37122734823413e-13) + -6.69490057120194e-12) + fConst23 * (fConst64 + fConst62 * fRec0[0])) + fRec2[3] * (fConst24 * fRec1[0] * (fRec1[0] * (4.57075782744711e-14 - fTemp2) - fTemp1 + 2.23163352373398e-12) + fConst23 * (fConst22 + fConst20 * fRec0[0]))) / fTemp0);
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		for (int j0 = 3; j0 > 0; j0 = j0 - 1) {
			fRec2[j0] = fRec2[j0 - 1];
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
		fRecCl5[0] = Ftrany(TRANY_TABLE_KT88_68k, 0.9254498422517706 * (fRecCl6[0] + fRecCl6[2]) + fRecCl8[0] + 1.8508996845035413 * fRecCl6[1] + -5.562895) + -43.96685185185183;
		fRecCl4[0] = fConstCl8 * (fConstCl7 * (fRecCl5[0] - fRecCl5[1]) - fConstCl3 * fRecCl4[1]);
		fRecCl3[0] = 0.9302847925323914 * (fRecCl4[0] + fRecCl4[1]) - 0.8605695850647829 * fRecCl3[1];
		fRecCl2[0] = fRecCl3[0] - (1.8405051250752198 * fRecCl2[1] + 0.8612942439318627 * fRecCl2[2]);
		fRecCl9[0] = fConstCl6 * (0.027 * (fRecCl1[1] + fRecCl1[2]) - fConstCl5 * fRecCl9[1]);
		fRecCl1[0] = Ftrany(TRANY_TABLE_KT88_68k, 0.9254498422517706 * (fRecCl2[0] + fRecCl2[2]) + fRecCl9[0] + 1.8508996845035413 * fRecCl2[1] + -5.562895) + -43.96685185185183;
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

}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerFloatVar("fuzzfacerm.Fuzz",N_("Fuzz"),"S","",&fVslider1, 0.5, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("fuzzfacerm.Level",N_("Level"),"S","",&fVslider0, 0.5, 0.0, 1.0, 0.01, 0);
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
                        <property name=\"var_id\">fuzzfacerm.Fuzz</property>\n\
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
                        <property name=\"var_id\">fuzzfacerm.Level</property>\n\
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
                <property name=\"var_id\">fuzzfacerm.Level</property>\n\
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
#define PARAM(p) ("fuzzfacerm" "." p)

b.openHorizontalhideBox("");
    b.create_master_slider(PARAM("Fuzz"), N_("Fuzz"));
b.closeBox();
b.openHorizontalBox("");

    b.create_small_rackknobr(PARAM("Fuzz"), N_("Fuzz"));

    b.create_small_rackknobr(PARAM("Level"), N_("Level"));
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

} // end namespace fuzzfacerm
} // end namespace pluginlib
