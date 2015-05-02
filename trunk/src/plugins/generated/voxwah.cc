// generated from file '../src/plugins/voxwah.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

namespace pluginlib {
namespace voxwah {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	int 	iVec0[2];
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	FAUSTFLOAT 	fslider0;
	double 	fConst4;
	double 	fRec2[2];
	double 	fRec1[2];
	double 	fRec0[2];
	FAUSTFLOAT 	fslider1;
	double 	fRec3[2];
	double 	fConst5;
	double 	fConst6;
	double 	fRec5[2];
	double 	fConst7;
	double 	fConst8;
	double 	fRec4[2];
	FAUSTFLOAT 	fslider2;
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
	double 	fConst40;
	double 	fConst41;
	double 	fConst42;
	double 	fConst43;
	FAUSTFLOAT 	fslider3;
	double 	fRec6[7];
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
	for (int i=0; i<2; i++) iVec0[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<7; i++) fRec6[i] = 0;
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
	fConst2 = (2.1399304623982e-29 * fConst1);
	fConst3 = (5.69239039885932e-17 + (fConst1 * (6.14367881980831e-18 + (fConst1 * (2.02121260151633e-19 + (fConst1 * (2.76955826240888e-22 + (fConst1 * (3.04570433260508e-26 + fConst2)))))))));
	fConst4 = (0.10471975511965977 / double(iConst0));
	fConst5 = exp((0 - (1e+01 / double(iConst0))));
	fConst6 = (1.0 - fConst5);
	fConst7 = exp((0 - (1e+02 / double(iConst0))));
	fConst8 = (1.0 - fConst7);
	fConst9 = (1.89633819957818e-29 * fConst1);
	fConst10 = (fConst1 * ((fConst1 * ((fConst1 * ((fConst1 * (0 - (1.67389657230137e-26 + fConst9))) - 3.3280358276443e-23)) - 2.30098055446033e-20)) - 1.88953692908276e-19));
	fConst11 = (1.26707994816449e-28 * fConst1);
	fConst12 = (5.36800263943966e-18 + (fConst1 * (8.35300656600375e-19 + (fConst1 * (2.71579433571679e-20 + (fConst1 * (4.29512485115259e-23 + (fConst1 * (1.03160559927227e-25 + fConst11)))))))));
	fConst13 = (3.23177789600593e-30 * fConst1);
	fConst14 = ((fConst1 * (1.19105605913141e-20 + (fConst1 * ((fConst1 * (1.07008772095285e-25 - fConst13)) - 1.60626322047249e-22)))) - 5.93495580034508e-20);
	fConst15 = (5.3581264088071e-31 * fConst1);
	fConst16 = (fConst1 * ((fConst1 * (2.20774629012815e-23 + (fConst1 * (fConst15 - 1.48874673815095e-26)))) - 1.52372411622765e-21));
	fConst17 = (5.35111910191404e-31 * fConst1);
	fConst18 = ((fConst1 * (2.13084338459394e-21 + (fConst1 * ((fConst1 * (1.48995539050572e-26 - fConst17)) - 2.24831652271913e-23)))) - 4.19202946447508e-20);
	fConst19 = ((fConst1 * (6.14367881980831e-18 + (fConst1 * ((fConst1 * (2.76955826240888e-22 + (fConst1 * (fConst2 - 3.04570433260508e-26)))) - 2.02121260151633e-19)))) - 5.69239039885932e-17);
	fConst20 = (fConst1 * ((fConst1 * (2.30098055446033e-20 + (fConst1 * ((fConst1 * (1.67389657230137e-26 - fConst9)) - 3.3280358276443e-23)))) - 1.88953692908276e-19));
	fConst21 = ((fConst1 * (8.35300656600375e-19 + (fConst1 * ((fConst1 * (4.29512485115259e-23 + (fConst1 * (fConst11 - 1.03160559927227e-25)))) - 2.71579433571679e-20)))) - 5.36800263943966e-18);
	fConst22 = (1.28395827743892e-28 * fConst1);
	fConst23 = faustpower<2>(fConst1);
	fConst24 = ((fConst1 * (1.22873576396166e-17 + (fConst23 * ((fConst1 * (1.21828173304203e-25 - fConst22)) - 5.53911652481776e-22)))) - 2.27695615954373e-16);
	fConst25 = (1.13780291974691e-28 * fConst1);
	fConst26 = (fConst1 * ((fConst23 * (6.6560716552886e-23 + (fConst1 * (fConst25 - 6.69558628920547e-26)))) - 3.77907385816552e-19));
	fConst27 = (7.60247968898691e-28 * fConst1);
	fConst28 = ((fConst1 * (1.67060131320075e-18 + (fConst23 * ((fConst1 * (4.1264223970891e-25 - fConst27)) - 8.59024970230518e-23)))) - 2.14720105577586e-17);
	fConst29 = (3.20989569359729e-28 * fConst1);
	fConst30 = ((fConst1 * ((fConst1 * (6.06363780454899e-19 + (fConst1 * ((fConst1 * (fConst29 - 1.52285216630254e-25)) - 2.76955826240888e-22)))) - 6.14367881980831e-18)) - 2.84619519942966e-16);
	fConst31 = (2.84450729936727e-28 * fConst1);
	fConst32 = (fConst1 * (1.88953692908276e-19 + (fConst1 * ((fConst1 * (3.3280358276443e-23 + (fConst1 * (8.36948286150684e-26 - fConst31)))) - 6.902941663381e-20))));
	fConst33 = (1.90061992224673e-27 * fConst1);
	fConst34 = ((fConst1 * ((fConst1 * (8.14738300715037e-20 + (fConst1 * ((fConst1 * (fConst33 - 5.15802799636137e-25)) - 4.29512485115259e-23)))) - 8.35300656600375e-19)) - 2.68400131971983e-17);
	fConst35 = ((fConst23 * (1.10782330496355e-21 - (4.27986092479639e-28 * fConst23))) - 2.45747152792332e-17);
	fConst36 = (7.55814771633104e-19 + (fConst23 * ((3.79267639915636e-28 * fConst23) - 1.33121433105772e-22)));
	fConst37 = ((fConst23 * (1.71804994046104e-22 - (2.53415989632897e-27 * fConst23))) - 3.3412026264015e-18);
	fConst38 = (2.84619519942966e-16 + (fConst1 * ((fConst1 * ((fConst1 * ((fConst1 * (1.52285216630254e-25 + fConst29)) - 2.76955826240888e-22)) - 6.06363780454899e-19)) - 6.14367881980831e-18)));
	fConst39 = (fConst1 * (1.88953692908276e-19 + (fConst1 * (6.902941663381e-20 + (fConst1 * (3.3280358276443e-23 + (fConst1 * (0 - (8.36948286150684e-26 + fConst31)))))))));
	fConst40 = (2.68400131971983e-17 + (fConst1 * ((fConst1 * ((fConst1 * ((fConst1 * (5.15802799636137e-25 + fConst33)) - 4.29512485115259e-23)) - 8.14738300715037e-20)) - 8.35300656600375e-19)));
	fConst41 = (2.27695615954373e-16 + (fConst1 * (1.22873576396166e-17 + (fConst23 * ((fConst1 * (0 - (1.21828173304203e-25 + fConst22))) - 5.53911652481776e-22)))));
	fConst42 = (fConst1 * ((fConst23 * (6.6560716552886e-23 + (fConst1 * (6.69558628920547e-26 + fConst25)))) - 3.77907385816552e-19));
	fConst43 = (2.14720105577586e-17 + (fConst1 * (1.67060131320075e-18 + (fConst23 * ((fConst1 * (0 - (4.1264223970891e-25 + fConst27))) - 8.59024970230518e-23)))));
	fConst44 = (1.93906673760356e-29 * fConst1);
	fConst45 = ((fConst23 * (3.21252644094498e-22 + (fConst1 * (fConst44 - 4.28035088381142e-25)))) - 1.18699116006902e-19);
	fConst46 = (3.21487584528426e-30 * fConst1);
	fConst47 = (fConst23 * ((fConst1 * (5.95498695260382e-26 - fConst46)) - 4.4154925802563e-23));
	fConst48 = (3.21067146114843e-30 * fConst1);
	fConst49 = ((fConst23 * (4.49663304543827e-23 + (fConst1 * (fConst48 - 5.9598215620229e-26)))) - 8.38405892895015e-20);
	fConst50 = (4.8476668440089e-29 * fConst1);
	fConst51 = (5.93495580034508e-20 + (fConst1 * ((fConst1 * (1.60626322047249e-22 + (fConst1 * (5.35043860476427e-25 - fConst50)))) - 3.57316817739422e-20)));
	fConst52 = (8.03718961321065e-30 * fConst1);
	fConst53 = (fConst1 * (4.57117234868296e-21 + (fConst1 * ((fConst1 * (fConst52 - 7.44373369075477e-26)) - 2.20774629012815e-23))));
	fConst54 = (8.02667865287107e-30 * fConst1);
	fConst55 = (4.19202946447508e-20 + (fConst1 * ((fConst1 * (2.24831652271913e-23 + (fConst1 * (7.44977695252862e-26 - fConst54)))) - 6.39253015378182e-21)));
	fConst56 = (2.37398232013803e-19 + (fConst23 * ((6.46355579201187e-29 * fConst23) - 6.42505288188996e-22)));
	fConst57 = (fConst23 * (8.83098516051261e-23 - (1.07162528176142e-29 * fConst23)));
	fConst58 = (1.67681178579003e-19 + (fConst23 * ((1.07022382038281e-29 * fConst23) - 8.99326609087654e-23)));
	fConst59 = (5.93495580034508e-20 + (fConst1 * (3.57316817739422e-20 + (fConst1 * (1.60626322047249e-22 + (fConst1 * (0 - (5.35043860476427e-25 + fConst50))))))));
	fConst60 = (fConst1 * ((fConst1 * ((fConst1 * (7.44373369075477e-26 + fConst52)) - 2.20774629012815e-23)) - 4.57117234868296e-21));
	fConst61 = (4.19202946447508e-20 + (fConst1 * (6.39253015378182e-21 + (fConst1 * (2.24831652271913e-23 + (fConst1 * (0 - (7.44977695252862e-26 + fConst54))))))));
	fConst62 = ((fConst23 * (3.21252644094498e-22 + (fConst1 * (4.28035088381142e-25 + fConst44)))) - 1.18699116006902e-19);
	fConst63 = (fConst23 * ((fConst1 * (0 - (5.95498695260382e-26 + fConst46))) - 4.4154925802563e-23));
	fConst64 = ((fConst23 * (4.49663304543827e-23 + (fConst1 * (5.9598215620229e-26 + fConst48)))) - 8.38405892895015e-20);
	fConst65 = ((fConst1 * ((fConst1 * ((fConst1 * (0 - (1.07008772095285e-25 + fConst13))) - 1.60626322047249e-22)) - 1.19105605913141e-20)) - 5.93495580034508e-20);
	fConst66 = (fConst1 * (1.52372411622765e-21 + (fConst1 * (2.20774629012815e-23 + (fConst1 * (1.48874673815095e-26 + fConst15))))));
	fConst67 = ((fConst1 * ((fConst1 * ((fConst1 * (0 - (1.48995539050572e-26 + fConst17))) - 2.24831652271913e-23)) - 2.13084338459394e-21)) - 4.19202946447508e-20);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlow0 = (fConst4 * double(fslider0));
	double 	fSlow1 = (0.007000000000000006 * double(fslider1));
	int 	iSlow2 = int(double(fslider2));
	double 	fSlow3 = (0.01 * double(fslider3));
	double 	fSlow4 = (1 - fSlow3);
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		fRec2[0] = (fRec2[1] + (fSlow0 * (0 - fRec0[1])));
		fRec1[0] = ((1 + (fRec1[1] + (fSlow0 * fRec2[0]))) - iVec0[1]);
		fRec0[0] = fRec1[0];
		fRec3[0] = ((0.993 * fRec3[1]) + fSlow1);
		double fTemp0 = (double)input0[i];
		double fTemp1 = fabs(fTemp0);
		fRec5[0] = ((fConst5 * max(fTemp1, fRec5[1])) + (fConst6 * fTemp1));
		fRec4[0] = ((fConst7 * fRec4[1]) + (fConst8 * fRec5[0]));
		double fTemp2 = ((iSlow2==0)? max(0.02, min((double)1, fRec4[0])) : ((iSlow2==1)?fRec3[0]:max(0.02, min((double)1, (0.5 * (1 + fRec0[0]))))) );
		double fTemp3 = (1.52500074984081e-16 + (fConst1 * ((fTemp2 * (fConst12 + (fConst10 * fTemp2))) + fConst3)));
		fRec6[0] = ((fSlow3 * fTemp0) - (((((((fRec6[1] * (9.15000449904488e-16 + (fConst1 * ((fTemp2 * (fConst43 + (fConst42 * fTemp2))) + fConst41)))) + (fRec6[2] * (2.28750112476122e-15 + (fConst1 * ((fTemp2 * (fConst40 + (fConst39 * fTemp2))) + fConst38))))) + (fRec6[3] * (3.05000149968163e-15 + (fConst23 * ((fTemp2 * (fConst37 + (fConst36 * fTemp2))) + fConst35))))) + (fRec6[4] * (2.28750112476122e-15 + (fConst1 * ((fTemp2 * (fConst34 + (fConst32 * fTemp2))) + fConst30))))) + (fRec6[5] * (9.15000449904488e-16 + (fConst1 * ((fTemp2 * (fConst28 + (fConst26 * fTemp2))) + fConst24))))) + (fRec6[6] * (1.52500074984081e-16 + (fConst1 * ((fTemp2 * (fConst21 + (fConst20 * fTemp2))) + fConst19))))) / fTemp3));
		output0[i] = (FAUSTFLOAT)((fSlow4 * fTemp0) + (fConst23 * ((((((((fRec6[0] * ((fTemp2 * (fConst67 + (fConst66 * fTemp2))) + fConst65)) + (fRec6[1] * ((fTemp2 * (fConst64 + (fConst63 * fTemp2))) + fConst62))) + (fRec6[2] * ((fTemp2 * (fConst61 + (fConst60 * fTemp2))) + fConst59))) + (fRec6[3] * ((fTemp2 * (fConst58 + (fConst57 * fTemp2))) + fConst56))) + (fRec6[4] * ((fTemp2 * (fConst55 + (fConst53 * fTemp2))) + fConst51))) + (fRec6[5] * ((fTemp2 * (fConst49 + (fConst47 * fTemp2))) + fConst45))) + (fRec6[6] * ((fTemp2 * (fConst18 + (fConst16 * fTemp2))) + fConst14))) / fTemp3)));
		// post processing
		for (int i=6; i>0; i--) fRec6[i] = fRec6[i-1];
		fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fRec3[1] = fRec3[0];
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		iVec0[1] = iVec0[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("voxwah.Wah",N_("Wah"),"S","",&fslider1, 0.5, 0.02, 1.0, 0.01);
	reg.registerVar("voxwah.lfobpm",N_("Alien Freq"),"S",N_("LFO in Beats per Minute"),&fslider0, 24.0, 24.0, 3.6e+02, 1.0);
	static const value_pair fslider2_values[] = {{"manual"},{"auto"},{"alien"},{0}};
	reg.registerEnumVar("voxwah.mode","","S","",fslider2_values,&fslider2, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("voxwah.wet_dry",N_("wet/dry"),"S",N_("percentage of processed signal in output signal"),&fslider3, 1e+02, 0.0, 1e+02, 1.0);
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

    b.create_selector(PARAM("mode"), "Mode");
    b.create_small_rackknobr(PARAM("lfobpm"), "Alien Freq");
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
