// generated from file '../src/plugins/voxwah.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

namespace pluginlib {
namespace voxwah {

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
	FAUSTFLOAT 	fslider1;
	double 	fRec1[7];
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
	double 	fConst59;
	double 	fConst60;
	double 	fConst61;
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
	id = "voxwah";
	name = N_("Vox Wah V847");
	groups = 0;
	description = N_("Vox Wah V847"); // description (tooltip)
	category = N_("Guitar Effects");       // category
	shortname = N_("Vox Wah");     // shortname
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
	for (int i=0; i<7; i++) fRec1[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = double(min(192000, max(1, fSamplingFreq)));
	fConst1 = (2.1399304623982e-29 * fConst0);
	fConst2 = (5.69239039885932e-17 + (fConst0 * (6.14367881980831e-18 + (fConst0 * (2.02121260151633e-19 + (fConst0 * (2.76955826240888e-22 + (fConst0 * (3.04570433260508e-26 + fConst1)))))))));
	fConst3 = (1.89633819957818e-29 * fConst0);
	fConst4 = (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (0 - (1.67389657230137e-26 + fConst3))) - 3.3280358276443e-23)) - 2.30098055446033e-20)) - 1.88953692908276e-19));
	fConst5 = (1.26707994816449e-28 * fConst0);
	fConst6 = (5.36800263943966e-18 + (fConst0 * (8.35300656600375e-19 + (fConst0 * (2.71579433571679e-20 + (fConst0 * (4.29512485115259e-23 + (fConst0 * (1.03160559927227e-25 + fConst5)))))))));
	fConst7 = (3.23177789600593e-30 * fConst0);
	fConst8 = ((fConst0 * (1.19105605913141e-20 + (fConst0 * ((fConst0 * (1.07008772095285e-25 - fConst7)) - 1.60626322047249e-22)))) - 5.93495580034508e-20);
	fConst9 = (5.3581264088071e-31 * fConst0);
	fConst10 = (fConst0 * ((fConst0 * (2.20774629012815e-23 + (fConst0 * (fConst9 - 1.48874673815095e-26)))) - 1.52372411622765e-21));
	fConst11 = (5.35111910191404e-31 * fConst0);
	fConst12 = ((fConst0 * (2.13084338459394e-21 + (fConst0 * ((fConst0 * (1.48995539050572e-26 - fConst11)) - 2.24831652271913e-23)))) - 4.19202946447508e-20);
	fConst13 = ((fConst0 * (6.14367881980831e-18 + (fConst0 * ((fConst0 * (2.76955826240888e-22 + (fConst0 * (fConst1 - 3.04570433260508e-26)))) - 2.02121260151633e-19)))) - 5.69239039885932e-17);
	fConst14 = (fConst0 * ((fConst0 * (2.30098055446033e-20 + (fConst0 * ((fConst0 * (1.67389657230137e-26 - fConst3)) - 3.3280358276443e-23)))) - 1.88953692908276e-19));
	fConst15 = ((fConst0 * (8.35300656600375e-19 + (fConst0 * ((fConst0 * (4.29512485115259e-23 + (fConst0 * (fConst5 - 1.03160559927227e-25)))) - 2.71579433571679e-20)))) - 5.36800263943966e-18);
	fConst16 = (1.28395827743892e-28 * fConst0);
	fConst17 = faustpower<2>(fConst0);
	fConst18 = ((fConst0 * (1.22873576396166e-17 + (fConst17 * ((fConst0 * (1.21828173304203e-25 - fConst16)) - 5.53911652481776e-22)))) - 2.27695615954373e-16);
	fConst19 = (1.13780291974691e-28 * fConst0);
	fConst20 = (fConst0 * ((fConst17 * (6.6560716552886e-23 + (fConst0 * (fConst19 - 6.69558628920547e-26)))) - 3.77907385816552e-19));
	fConst21 = (7.60247968898691e-28 * fConst0);
	fConst22 = ((fConst0 * (1.67060131320075e-18 + (fConst17 * ((fConst0 * (4.1264223970891e-25 - fConst21)) - 8.59024970230518e-23)))) - 2.14720105577586e-17);
	fConst23 = (3.20989569359729e-28 * fConst0);
	fConst24 = ((fConst0 * ((fConst0 * (6.06363780454899e-19 + (fConst0 * ((fConst0 * (fConst23 - 1.52285216630254e-25)) - 2.76955826240888e-22)))) - 6.14367881980831e-18)) - 2.84619519942966e-16);
	fConst25 = (2.84450729936727e-28 * fConst0);
	fConst26 = (fConst0 * (1.88953692908276e-19 + (fConst0 * ((fConst0 * (3.3280358276443e-23 + (fConst0 * (8.36948286150684e-26 - fConst25)))) - 6.902941663381e-20))));
	fConst27 = (1.90061992224673e-27 * fConst0);
	fConst28 = ((fConst0 * ((fConst0 * (8.14738300715037e-20 + (fConst0 * ((fConst0 * (fConst27 - 5.15802799636137e-25)) - 4.29512485115259e-23)))) - 8.35300656600375e-19)) - 2.68400131971983e-17);
	fConst29 = ((fConst17 * (1.10782330496355e-21 - (4.27986092479639e-28 * fConst17))) - 2.45747152792332e-17);
	fConst30 = (7.55814771633104e-19 + (fConst17 * ((3.79267639915636e-28 * fConst17) - 1.33121433105772e-22)));
	fConst31 = ((fConst17 * (1.71804994046104e-22 - (2.53415989632897e-27 * fConst17))) - 3.3412026264015e-18);
	fConst32 = (2.84619519942966e-16 + (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (1.52285216630254e-25 + fConst23)) - 2.76955826240888e-22)) - 6.06363780454899e-19)) - 6.14367881980831e-18)));
	fConst33 = (fConst0 * (1.88953692908276e-19 + (fConst0 * (6.902941663381e-20 + (fConst0 * (3.3280358276443e-23 + (fConst0 * (0 - (8.36948286150684e-26 + fConst25)))))))));
	fConst34 = (2.68400131971983e-17 + (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (5.15802799636137e-25 + fConst27)) - 4.29512485115259e-23)) - 8.14738300715037e-20)) - 8.35300656600375e-19)));
	fConst35 = (2.27695615954373e-16 + (fConst0 * (1.22873576396166e-17 + (fConst17 * ((fConst0 * (0 - (1.21828173304203e-25 + fConst16))) - 5.53911652481776e-22)))));
	fConst36 = (fConst0 * ((fConst17 * (6.6560716552886e-23 + (fConst0 * (6.69558628920547e-26 + fConst19)))) - 3.77907385816552e-19));
	fConst37 = (2.14720105577586e-17 + (fConst0 * (1.67060131320075e-18 + (fConst17 * ((fConst0 * (0 - (4.1264223970891e-25 + fConst21))) - 8.59024970230518e-23)))));
	fConst38 = (1.93906673760356e-29 * fConst0);
	fConst39 = ((fConst17 * (3.21252644094498e-22 + (fConst0 * (fConst38 - 4.28035088381142e-25)))) - 1.18699116006902e-19);
	fConst40 = (3.21487584528426e-30 * fConst0);
	fConst41 = (fConst17 * ((fConst0 * (5.95498695260382e-26 - fConst40)) - 4.4154925802563e-23));
	fConst42 = (3.21067146114843e-30 * fConst0);
	fConst43 = ((fConst17 * (4.49663304543827e-23 + (fConst0 * (fConst42 - 5.9598215620229e-26)))) - 8.38405892895015e-20);
	fConst44 = (4.8476668440089e-29 * fConst0);
	fConst45 = (5.93495580034508e-20 + (fConst0 * ((fConst0 * (1.60626322047249e-22 + (fConst0 * (5.35043860476427e-25 - fConst44)))) - 3.57316817739422e-20)));
	fConst46 = (8.03718961321065e-30 * fConst0);
	fConst47 = (fConst0 * (4.57117234868296e-21 + (fConst0 * ((fConst0 * (fConst46 - 7.44373369075477e-26)) - 2.20774629012815e-23))));
	fConst48 = (8.02667865287107e-30 * fConst0);
	fConst49 = (4.19202946447508e-20 + (fConst0 * ((fConst0 * (2.24831652271913e-23 + (fConst0 * (7.44977695252862e-26 - fConst48)))) - 6.39253015378182e-21)));
	fConst50 = (2.37398232013803e-19 + (fConst17 * ((6.46355579201187e-29 * fConst17) - 6.42505288188996e-22)));
	fConst51 = (fConst17 * (8.83098516051261e-23 - (1.07162528176142e-29 * fConst17)));
	fConst52 = (1.67681178579003e-19 + (fConst17 * ((1.07022382038281e-29 * fConst17) - 8.99326609087654e-23)));
	fConst53 = (5.93495580034508e-20 + (fConst0 * (3.57316817739422e-20 + (fConst0 * (1.60626322047249e-22 + (fConst0 * (0 - (5.35043860476427e-25 + fConst44))))))));
	fConst54 = (fConst0 * ((fConst0 * ((fConst0 * (7.44373369075477e-26 + fConst46)) - 2.20774629012815e-23)) - 4.57117234868296e-21));
	fConst55 = (4.19202946447508e-20 + (fConst0 * (6.39253015378182e-21 + (fConst0 * (2.24831652271913e-23 + (fConst0 * (0 - (7.44977695252862e-26 + fConst48))))))));
	fConst56 = ((fConst17 * (3.21252644094498e-22 + (fConst0 * (4.28035088381142e-25 + fConst38)))) - 1.18699116006902e-19);
	fConst57 = (fConst17 * ((fConst0 * (0 - (5.95498695260382e-26 + fConst40))) - 4.4154925802563e-23));
	fConst58 = ((fConst17 * (4.49663304543827e-23 + (fConst0 * (5.9598215620229e-26 + fConst42)))) - 8.38405892895015e-20);
	fConst59 = ((fConst0 * ((fConst0 * ((fConst0 * (0 - (1.07008772095285e-25 + fConst7))) - 1.60626322047249e-22)) - 1.19105605913141e-20)) - 5.93495580034508e-20);
	fConst60 = (fConst0 * (1.52372411622765e-21 + (fConst0 * (2.20774629012815e-23 + (fConst0 * (1.48874673815095e-26 + fConst9))))));
	fConst61 = ((fConst0 * ((fConst0 * ((fConst0 * (0 - (1.48995539050572e-26 + fConst11))) - 2.24831652271913e-23)) - 2.13084338459394e-21)) - 4.19202946447508e-20);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlow0 = (0.007000000000000006 * double(fslider0));
	double 	fSlow1 = (0.01 * double(fslider1));
	double 	fSlow2 = (1 - fSlow1);
	for (int i=0; i<count; i++) {
		fRec0[0] = ((0.993 * fRec0[1]) + fSlow0);
		double fTemp0 = (1.52500074984081e-16 + (fConst0 * ((fRec0[0] * (fConst6 + (fConst4 * fRec0[0]))) + fConst2)));
		double fTemp1 = (double)input0[i];
		fRec1[0] = ((fSlow1 * fTemp1) - (((((((fRec1[1] * (9.15000449904488e-16 + (fConst0 * ((fRec0[0] * (fConst37 + (fConst36 * fRec0[0]))) + fConst35)))) + (fRec1[2] * (2.28750112476122e-15 + (fConst0 * ((fRec0[0] * (fConst34 + (fConst33 * fRec0[0]))) + fConst32))))) + (fRec1[3] * (3.05000149968163e-15 + (fConst17 * ((fRec0[0] * (fConst31 + (fConst30 * fRec0[0]))) + fConst29))))) + (fRec1[4] * (2.28750112476122e-15 + (fConst0 * ((fRec0[0] * (fConst28 + (fConst26 * fRec0[0]))) + fConst24))))) + (fRec1[5] * (9.15000449904488e-16 + (fConst0 * ((fRec0[0] * (fConst22 + (fConst20 * fRec0[0]))) + fConst18))))) + (fRec1[6] * (1.52500074984081e-16 + (fConst0 * ((fRec0[0] * (fConst15 + (fConst14 * fRec0[0]))) + fConst13))))) / fTemp0));
		output0[i] = (FAUSTFLOAT)((fSlow2 * fTemp1) + (fConst17 * ((((((((fRec1[0] * ((fRec0[0] * (fConst61 + (fConst60 * fRec0[0]))) + fConst59)) + (fRec1[1] * ((fRec0[0] * (fConst58 + (fConst57 * fRec0[0]))) + fConst56))) + (fRec1[2] * ((fRec0[0] * (fConst55 + (fConst54 * fRec0[0]))) + fConst53))) + (fRec1[3] * ((fRec0[0] * (fConst52 + (fConst51 * fRec0[0]))) + fConst50))) + (fRec1[4] * ((fRec0[0] * (fConst49 + (fConst47 * fRec0[0]))) + fConst45))) + (fRec1[5] * ((fRec0[0] * (fConst43 + (fConst41 * fRec0[0]))) + fConst39))) + (fRec1[6] * ((fRec0[0] * (fConst12 + (fConst10 * fRec0[0]))) + fConst8))) / fTemp0)));
		// post processing
		for (int i=6; i>0; i--) fRec1[i] = fRec1[i-1];
		fRec0[1] = fRec0[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("voxwah.Wah",N_("Wah"),"S","",&fslider0, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("voxwah.wet_dry",N_("wet/dry"),"S",N_("percentage of processed signal in output signal"),&fslider1, 1e+02, 0.0, 1e+02, 1.0);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("voxwah" "." p)

b.openHorizontalhideBox("");
    b.create_master_slider(PARAM("Wah"), "Wah");
b.closeBox();
b.openHorizontalBox("");

    b.create_small_rackknobr(PARAM("Wah"), "Wah");
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

} // end namespace voxwah
} // end namespace pluginlib
