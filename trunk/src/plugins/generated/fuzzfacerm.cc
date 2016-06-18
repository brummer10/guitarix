// generated from file '../src/plugins/fuzzfacerm.dsp' by dsp2cc:
// Code generated with Faust 0.9.73 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

#include "trany.h"

namespace pluginlib {
namespace fuzzfacerm {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	double 	fConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	FAUSTFLOAT 	fslider0;
	double 	fRec0[2];
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
	FAUSTFLOAT 	fslider1;
	double 	fRec1[2];
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
	double 	fRec2[4];
	double 	fConst59;
	double 	fConst60;
	double 	fConst61;
	double 	fConst62;
	double 	fConst63;
	double 	fConst64;
	double 	fConst65;
	double 	fConst66;
	double 	fConst67;

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
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<4; i++) fRec2[i] = 0;

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
	fConst1 = (1.72853928389298e-15 * fConst0);
	fConst2 = (2.6123111187704e-10 + (fConst0 * (4.32740215906676e-13 + fConst1)));
	fConst3 = (3.05119726906337e-14 * fConst0);
	fConst4 = (2.21726535708769e-11 + (fConst0 * (2.08816997599123e-11 + fConst3)));
	fConst5 = (5.85504578964162e-29 * fConst0);
	fConst6 = (2.83746860731297e-29 + (fConst0 * (4.00083755606776e-26 + fConst5)));
	fConst7 = (1.19490650740761e-31 * fConst0);
	fConst8 = (8.68612838978577e-26 + (fConst0 * (2.08767320417856e-28 + fConst7)));
	fConst9 = (3.22405119745267e-14 * fConst0);
	fConst10 = ((fConst0 * (0 - (2.08898268350887e-11 + fConst9))) - 2.21793415696022e-11);
	fConst11 = (6.18674104772942e-29 * fConst0);
	fConst12 = ((fConst0 * (0 - (4.00204457374009e-26 + fConst11))) - 2.83832448080453e-29);
	fConst13 = (1.26259937209307e-31 * fConst0);
	fConst14 = ((fConst0 * (0 - (2.15993317197785e-28 + fConst13))) - 8.68874841067831e-26);
	fConst15 = (6.76928646854567e-33 * fConst0);
	fConst16 = (1.08642105394636e-24 + (fConst0 * (2.81644163364677e-27 + (fConst0 * (8.88886207590151e-30 + fConst15)))));
	fConst17 = (3.31695258087803e-30 * fConst0);
	fConst18 = (3.54897544287011e-28 + (fConst0 * (5.00406457485288e-25 + (fConst0 * (8.26874714950455e-28 + fConst17)))));
	fConst19 = (2.27734110200845e-12 * fConst0);
	fConst20 = (2.90381085035365e-11 - fConst19);
	fConst21 = (2.23179427996828e-12 * fConst0);
	fConst22 = (fConst21 - 2.84573463334658e-11);
	fConst23 = ((fConst0 * (4.32740215906676e-13 - fConst1)) - 2.6123111187704e-10);
	fConst24 = ((fConst0 * (2.08816997599123e-11 - fConst3)) - 2.21726535708769e-11);
	fConst25 = ((fConst0 * (4.00083755606776e-26 - fConst5)) - 2.83746860731297e-29);
	fConst26 = ((fConst0 * (2.08767320417856e-28 - fConst7)) - 8.68612838978577e-26);
	fConst27 = (2.21793415696022e-11 + (fConst0 * (fConst9 - 2.08898268350887e-11)));
	fConst28 = (2.83832448080453e-29 + (fConst0 * (fConst11 - 4.00204457374009e-26)));
	fConst29 = (8.68874841067831e-26 + (fConst0 * (fConst13 - 2.15993317197785e-28)));
	fConst30 = (1.08642105394636e-24 + (fConst0 * ((fConst0 * (8.88886207590151e-30 - fConst15)) - 2.81644163364677e-27)));
	fConst31 = (3.54897544287011e-28 + (fConst0 * ((fConst0 * (8.26874714950455e-28 - fConst17)) - 5.00406457485288e-25)));
	fConst32 = (1.75651373689249e-28 * fConst0);
	fConst33 = ((fConst0 * (fConst32 - 4.00083755606776e-26)) - 2.83746860731297e-29);
	fConst34 = (3.58471952222284e-31 * fConst0);
	fConst35 = ((fConst0 * (fConst34 - 2.08767320417856e-28)) - 8.68612838978577e-26);
	fConst36 = (9.67215359235801e-14 * fConst0);
	fConst37 = (2.21793415696022e-11 + (fConst0 * (2.08898268350887e-11 - fConst36)));
	fConst38 = (1.85602231431883e-28 * fConst0);
	fConst39 = (2.83832448080453e-29 + (fConst0 * (4.00204457374009e-26 - fConst38)));
	fConst40 = (3.78779811627921e-31 * fConst0);
	fConst41 = (8.68874841067831e-26 + (fConst0 * (2.15993317197785e-28 - fConst40)));
	fConst42 = (9.15359180719011e-14 * fConst0);
	fConst43 = ((fConst0 * (fConst42 - 2.08816997599123e-11)) - 2.21726535708769e-11);
	fConst44 = (5.18561785167894e-15 * fConst0);
	fConst45 = ((fConst0 * (fConst44 - 4.32740215906676e-13)) - 2.6123111187704e-10);
	fConst46 = (2.0307859405637e-32 * fConst0);
	fConst47 = (3.25926316183907e-24 + (fConst0 * ((fConst0 * (fConst46 - 8.88886207590151e-30)) - 2.81644163364677e-27)));
	fConst48 = (9.95085774263408e-30 * fConst0);
	fConst49 = (1.06469263286103e-27 + (fConst0 * ((fConst0 * (fConst48 - 8.26874714950455e-28)) - 5.00406457485288e-25)));
	fConst50 = (2.6123111187704e-10 + (fConst0 * (0 - (4.32740215906676e-13 + fConst44))));
	fConst51 = (2.21726535708769e-11 + (fConst0 * (0 - (2.08816997599123e-11 + fConst42))));
	fConst52 = (2.83746860731297e-29 + (fConst0 * (0 - (4.00083755606776e-26 + fConst32))));
	fConst53 = (8.68612838978577e-26 + (fConst0 * (0 - (2.08767320417856e-28 + fConst34))));
	fConst54 = ((fConst0 * (2.08898268350887e-11 + fConst36)) - 2.21793415696022e-11);
	fConst55 = ((fConst0 * (4.00204457374009e-26 + fConst38)) - 2.83832448080453e-29);
	fConst56 = ((fConst0 * (2.15993317197785e-28 + fConst40)) - 8.68874841067831e-26);
	fConst57 = (3.25926316183907e-24 + (fConst0 * (2.81644163364677e-27 + (fConst0 * (0 - (8.88886207590151e-30 + fConst46))))));
	fConst58 = (1.06469263286103e-27 + (fConst0 * (5.00406457485288e-25 + (fConst0 * (0 - (8.26874714950455e-28 + fConst48))))));
	fConst59 = (6.69538283990485e-12 * fConst0);
	fConst60 = (2.84573463334658e-11 - fConst59);
	fConst61 = (6.83202330602535e-12 * fConst0);
	fConst62 = (fConst61 - 2.90381085035365e-11);
	fConst63 = (0 - (2.90381085035365e-11 + fConst61));
	fConst64 = (2.84573463334658e-11 + fConst59);
	fConst65 = (2.90381085035365e-11 + fConst19);
	fConst66 = (0 - (2.84573463334658e-11 + fConst21));
	fConst67 = faustpower<2>(fConst0);

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
	double 	fSlow1 = (0.007000000000000006 * (1 - double(fslider1)));
	for (int i=0; i<count; i++) {
		fRec0[0] = ((0.993 * fRec0[1]) + fSlow0);
		fRec1[0] = ((0.993 * fRec1[1]) + fSlow1);
		double fTemp0 = (2.77325369604093e-10 + ((fRec0[0] * ((fConst18 * fRec0[0]) + fConst16)) + (fConst0 * ((fRec1[0] * (((fRec1[0] * ((fRec0[0] * (fConst14 + (fConst12 * fRec0[0]))) + fConst10)) + (fRec0[0] * (fConst8 + (fConst6 * fRec0[0])))) + fConst4)) + fConst2))));
		double fTemp1 = (2.1870008532593e-12 * fRec0[0]);
		double fTemp2 = (4.47934267089816e-14 * fRec0[0]);
		fRec2[0] = ((double)input0[i] - ((((fRec2[1] * (8.3197610881228e-10 + ((fRec0[0] * ((fConst58 * fRec0[0]) + fConst57)) + (fConst0 * ((fRec1[0] * (((fRec1[0] * ((fRec0[0] * (fConst56 + (fConst55 * fRec0[0]))) + fConst54)) + (fRec0[0] * (fConst53 + (fConst52 * fRec0[0])))) + fConst51)) + fConst50))))) + (fRec2[2] * (8.3197610881228e-10 + ((fRec0[0] * ((fConst49 * fRec0[0]) + fConst47)) + (fConst0 * (fConst45 + (fRec1[0] * (fConst43 + ((fRec1[0] * ((fRec0[0] * (fConst41 + (fConst39 * fRec0[0]))) + fConst37)) + (fRec0[0] * (fConst35 + (fConst33 * fRec0[0])))))))))))) + (fRec2[3] * (2.77325369604093e-10 + ((fRec0[0] * ((fConst31 * fRec0[0]) + fConst30)) + (fConst0 * ((fRec1[0] * (((fRec1[0] * ((fRec0[0] * (fConst29 + (fConst28 * fRec0[0]))) + fConst27)) + (fRec0[0] * (fConst26 + (fConst25 * fRec0[0])))) + fConst24)) + fConst23)))))) / fTemp0));
		double fTemp3 = (1.34380280126945e-13 * fRec0[0]);
		double fTemp4 = (6.5610025597779e-12 * fRec0[0]);
		output0[i] = (FAUSTFLOAT)(fConst67 * (((((fRec2[0] * (((fConst0 * (fRec1[0] * ((fTemp1 + (fRec1[0] * (fTemp2 - 4.57075782744711e-14))) - 2.23163352373398e-12))) + (fConst66 * fRec0[0])) + fConst65)) + (fRec2[1] * (((fConst0 * (fRec1[0] * (6.69490057120194e-12 + ((fRec1[0] * (1.37122734823413e-13 + (0 - fTemp3))) - fTemp4)))) + (fConst64 * fRec0[0])) + fConst63))) + (fRec2[2] * (fConst62 + ((fConst0 * (fRec1[0] * ((fTemp4 + (fRec1[0] * (fTemp3 - 1.37122734823413e-13))) - 6.69490057120194e-12))) + (fConst60 * fRec0[0]))))) + (fRec2[3] * (((fConst0 * (fRec1[0] * (2.23163352373398e-12 + ((fRec1[0] * (4.57075782744711e-14 + (0 - fTemp2))) - fTemp1)))) + (fConst22 * fRec0[0])) + fConst20))) / fTemp0));
		// post processing
		for (int i=3; i>0; i--) fRec2[i] = fRec2[i-1];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
	}

	FAUSTFLOAT bufCl[smpCl.max_out_count(count)];
	int ReCount = smpCl.up(count, output0, bufCl);
	for (int i=0; i<ReCount; i++) {
		double fTemp0 = (double)bufCl[i];
		fVecCl0[0] = fTemp0;
		fRecCl7[0] = ((0.9302847925323914 * (fVecCl0[0] + fVecCl0[1])) - (0.8605695850647829 * fRecCl7[1]));
		fRecCl6[0] = (fRecCl7[0] - ((1.8405051250752198 * fRecCl6[1]) + (0.8612942439318627 * fRecCl6[2])));
		fRecCl8[0] = ((fConstCl4 * fRecCl8[1]) + (fConstCl3 * (fRecCl5[1] + fRecCl5[2])));
		fRecCl5[0] = (Ftrany(TRANY_TABLE_KT88_68k, ((fRecCl8[0] + (0.9254498422517706 * (fRecCl6[2] + (fRecCl6[0] + (2.0 * fRecCl6[1]))))) - 5.562895)) - 43.96685185185183);
		fRecCl4[0] = ((fConstCl9 * fRecCl4[1]) + (fConstCl8 * ((fConstCl5 * fRecCl5[0]) + (fConstCl6 * fRecCl5[1]))));
		fRecCl3[0] = ((0.9302847925323914 * (fRecCl4[0] + fRecCl4[1])) - (0.8605695850647829 * fRecCl3[1]));
		fRecCl2[0] = (fRecCl3[0] - ((1.8405051250752198 * fRecCl2[1]) + (0.8612942439318627 * fRecCl2[2])));
		fRecCl9[0] = ((fConstCl4 * fRecCl9[1]) + (fConstCl3 * (fRecCl1[1] + fRecCl1[2])));
		fRecCl1[0] = (Ftrany(TRANY_TABLE_KT88_68k, ((fRecCl9[0] + (0.9254498422517706 * (fRecCl2[2] + (fRecCl2[0] + (2.0 * fRecCl2[1]))))) - 5.562895)) - 43.96685185185183);
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
	reg.registerVar("fuzzfacerm.Fuzz",N_("Fuzz"),"S","",&fslider1, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("fuzzfacerm.Level",N_("Level"),"S","",&fslider0, 0.5, 0.0, 1.0, 0.01);
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
