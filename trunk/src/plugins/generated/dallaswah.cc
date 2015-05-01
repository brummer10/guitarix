// generated from file '../src/plugins/dallaswah.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

namespace pluginlib {
namespace dallaswah {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	FAUSTFLOAT 	fslider0;
	double 	fRec0[2];
	double 	fConst4;
	double 	fConst5;
	double 	fRec2[2];
	double 	fConst6;
	double 	fConst7;
	double 	fRec1[2];
	FAUSTFLOAT 	fslider1;
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
	double 	fConst39;
	double 	fConst40;
	double 	fConst41;
	double 	fConst42;
	FAUSTFLOAT 	fslider2;
	double 	fRec3[7];
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
	id = "dallaswah";
	name = N_("Dallas Wah");
	groups = 0;
	description = N_("Dallas Arbiter Wah"); // description (tooltip)
	category = N_("Guitar Effects");       // category
	shortname = N_("Dallas  Wah");     // shortname
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
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<7; i++) fRec3[i] = 0;
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
	fConst2 = (2.51617848419225e-29 * fConst1);
	fConst3 = (1.13711463931101e-15 + (fConst1 * (3.6815416628337e-16 + (fConst1 * (3.59986998986588e-17 + (fConst1 * (1.09351207812161e-18 + (fConst1 * (6.29629967279172e-22 + (fConst1 * (8.09025818356709e-26 + fConst2)))))))))));
	fConst4 = exp((0 - (1e+01 / double(iConst0))));
	fConst5 = (1.0 - fConst4);
	fConst6 = exp((0 - (1e+02 / double(iConst0))));
	fConst7 = (1.0 - fConst6);
	fConst8 = (1.86565797488138e-29 * fConst1);
	fConst9 = (1.52896089528608e-31 + (fConst1 * ((fConst1 * ((fConst1 * ((fConst1 * (0 - (4.23676337082129e-26 + fConst8))) - 1.00468221585939e-22)) - 1.65639280522528e-19)) - 1.59055047288262e-18)));
	fConst10 = (1.14266706841096e-28 * fConst1);
	fConst11 = (4.25280875102305e-17 + (fConst1 * (5.68607004495272e-18 + (fConst1 * (1.35174012417023e-19 + (fConst1 * (9.3225622428148e-23 + (fConst1 * (2.27871736066328e-25 + fConst10)))))))));
	fConst12 = (2.95334143650199e-30 * fConst1);
	fConst13 = ((fConst1 * (2.71762597345689e-20 + (fConst1 * ((fConst1 * (2.39932288230564e-25 - fConst12)) - 3.60669905407753e-22)))) - 1.62378538408517e-19);
	fConst14 = (1.20894405825314e-30 * fConst1);
	fConst15 = ((fConst1 * ((fConst1 * (6.67221502794578e-23 + (fConst1 * (fConst14 - 4.55223559536905e-26)))) - 4.60832615818034e-21)) - 4.42988173510265e-34);
	fConst16 = (9.90901628275927e-31 * fConst1);
	fConst17 = ((fConst1 * (5.22251274319268e-21 + (fConst1 * ((fConst1 * (3.74994304179366e-26 - fConst16)) - 5.59001169449057e-23)))) - 9.86965379369583e-20);
	fConst18 = (1.13711463931101e-15 + (fConst1 * ((fConst1 * (3.59986998986588e-17 + (fConst1 * ((fConst1 * (6.29629967279172e-22 + (fConst1 * (fConst2 - 8.09025818356709e-26)))) - 1.09351207812161e-18)))) - 3.6815416628337e-16)));
	fConst19 = ((fConst1 * ((fConst1 * (1.65639280522528e-19 + (fConst1 * ((fConst1 * (4.23676337082129e-26 - fConst8)) - 1.00468221585939e-22)))) - 1.59055047288262e-18)) - 1.52896089528608e-31);
	fConst20 = ((fConst1 * (5.68607004495272e-18 + (fConst1 * ((fConst1 * (9.3225622428148e-23 + (fConst1 * (fConst10 - 2.27871736066328e-25)))) - 1.35174012417023e-19)))) - 4.25280875102305e-17);
	fConst21 = (1.50970709051535e-28 * fConst1);
	fConst22 = faustpower<2>(fConst1);
	fConst23 = (6.82268783586605e-15 + (fConst1 * ((fConst1 * (7.19973997973176e-17 + (fConst22 * ((fConst1 * (3.23610327342684e-25 - fConst21)) - 1.25925993455834e-21)))) - 1.47261666513348e-15)));
	fConst24 = (1.11939478492883e-28 * fConst1);
	fConst25 = ((fConst1 * ((fConst22 * (2.00936443171878e-22 + (fConst1 * (fConst24 - 1.69470534832851e-25)))) - 3.18110094576525e-18)) - 6.11584358114433e-31);
	fConst26 = (6.85600241046577e-28 * fConst1);
	fConst27 = ((fConst1 * (1.13721400899054e-17 + (fConst22 * ((fConst1 * (9.1148694426531e-25 - fConst26)) - 1.86451244856296e-22)))) - 1.70112350040922e-16);
	fConst28 = (3.77426772628837e-28 * fConst1);
	fConst29 = (1.70567195896651e-14 + (fConst1 * ((fConst1 * ((fConst1 * (3.28053623436483e-18 + (fConst1 * ((fConst1 * (fConst28 - 4.04512909178355e-25)) - 6.29629967279172e-22)))) - 3.59986998986588e-17)) - 1.84077083141685e-15)));
	fConst30 = (2.79848696232207e-28 * fConst1);
	fConst31 = ((fConst1 * (1.59055047288262e-18 + (fConst1 * ((fConst1 * (1.00468221585939e-22 + (fConst1 * (2.11838168541064e-25 - fConst30)))) - 4.96917841567585e-19)))) - 7.64480447643042e-31);
	fConst32 = (1.71400060261644e-27 * fConst1);
	fConst33 = ((fConst1 * ((fConst1 * (4.05522037251071e-19 + (fConst1 * ((fConst1 * (fConst32 - 1.13935868033164e-24)) - 9.3225622428148e-23)))) - 5.68607004495272e-18)) - 2.12640437551152e-16);
	fConst34 = (2.27422927862202e-14 + (fConst22 * ((fConst22 * (2.51851986911669e-21 - (5.03235696838449e-28 * fConst22))) - 1.43994799594635e-16)));
	fConst35 = (6.3622018915305e-18 + (fConst22 * ((3.73131594976276e-28 * fConst22) - 4.01872886343757e-22)));
	fConst36 = ((fConst22 * (3.72902489712592e-22 - (2.28533413682192e-27 * fConst22))) - 2.27442801798109e-17);
	fConst37 = (1.70567195896651e-14 + (fConst1 * (1.84077083141685e-15 + (fConst1 * ((fConst1 * ((fConst1 * ((fConst1 * (4.04512909178355e-25 + fConst28)) - 6.29629967279172e-22)) - 3.28053623436483e-18)) - 3.59986998986588e-17)))));
	fConst38 = (7.64480447643042e-31 + (fConst1 * (1.59055047288262e-18 + (fConst1 * (4.96917841567585e-19 + (fConst1 * (1.00468221585939e-22 + (fConst1 * (0 - (2.11838168541064e-25 + fConst30))))))))));
	fConst39 = (2.12640437551152e-16 + (fConst1 * ((fConst1 * ((fConst1 * ((fConst1 * (1.13935868033164e-24 + fConst32)) - 9.3225622428148e-23)) - 4.05522037251071e-19)) - 5.68607004495272e-18)));
	fConst40 = (6.82268783586605e-15 + (fConst1 * (1.47261666513348e-15 + (fConst1 * (7.19973997973176e-17 + (fConst22 * ((fConst1 * (0 - (3.23610327342684e-25 + fConst21))) - 1.25925993455834e-21)))))));
	fConst41 = (6.11584358114433e-31 + (fConst1 * ((fConst22 * (2.00936443171878e-22 + (fConst1 * (1.69470534832851e-25 + fConst24)))) - 3.18110094576525e-18)));
	fConst42 = (1.70112350040922e-16 + (fConst1 * (1.13721400899054e-17 + (fConst22 * ((fConst1 * (0 - (9.1148694426531e-25 + fConst26))) - 1.86451244856296e-22)))));
	fConst43 = (1.77200486190119e-29 * fConst1);
	fConst44 = ((fConst22 * (7.21339810815506e-22 + (fConst1 * (fConst43 - 9.59729152922254e-25)))) - 3.24757076817034e-19);
	fConst45 = (7.25366434951886e-30 * fConst1);
	fConst46 = ((fConst22 * ((fConst1 * (1.82089423814762e-25 - fConst45)) - 1.33444300558916e-22)) - 8.85976347020531e-34);
	fConst47 = (5.94540976965556e-30 * fConst1);
	fConst48 = ((fConst22 * (1.11800233889811e-22 + (fConst1 * (fConst47 - 1.49997721671747e-25)))) - 1.97393075873917e-19);
	fConst49 = (4.43001215475298e-29 * fConst1);
	fConst50 = (1.62378538408517e-19 + (fConst1 * ((fConst1 * (3.60669905407753e-22 + (fConst1 * (1.19966144115282e-24 - fConst49)))) - 8.15287792037067e-20)));
	fConst51 = (1.81341608737971e-29 * fConst1);
	fConst52 = (4.42988173510265e-34 + (fConst1 * (1.3824978474541e-20 + (fConst1 * ((fConst1 * (fConst51 - 2.27611779768452e-25)) - 6.67221502794578e-23)))));
	fConst53 = (1.48635244241389e-29 * fConst1);
	fConst54 = (9.86965379369583e-20 + (fConst1 * ((fConst1 * (5.59001169449057e-23 + (fConst1 * (1.87497152089683e-25 - fConst53)))) - 1.5667538229578e-20)));
	fConst55 = (6.49514153634068e-19 + (fConst22 * ((5.90668287300397e-29 * fConst22) - 1.44267962163101e-21)));
	fConst56 = (1.77195269404106e-33 + (fConst22 * (2.66888601117831e-22 - (2.41788811650629e-29 * fConst22))));
	fConst57 = (3.94786151747833e-19 + (fConst22 * ((1.98180325655185e-29 * fConst22) - 2.23600467779623e-22)));
	fConst58 = (1.62378538408517e-19 + (fConst1 * (8.15287792037067e-20 + (fConst1 * (3.60669905407753e-22 + (fConst1 * (0 - (1.19966144115282e-24 + fConst49))))))));
	fConst59 = (4.42988173510265e-34 + (fConst1 * ((fConst1 * ((fConst1 * (2.27611779768452e-25 + fConst51)) - 6.67221502794578e-23)) - 1.3824978474541e-20)));
	fConst60 = (9.86965379369583e-20 + (fConst1 * (1.5667538229578e-20 + (fConst1 * (5.59001169449057e-23 + (fConst1 * (0 - (1.87497152089683e-25 + fConst53))))))));
	fConst61 = ((fConst22 * (7.21339810815506e-22 + (fConst1 * (9.59729152922254e-25 + fConst43)))) - 3.24757076817034e-19);
	fConst62 = ((fConst22 * ((fConst1 * (0 - (1.82089423814762e-25 + fConst45))) - 1.33444300558916e-22)) - 8.85976347020531e-34);
	fConst63 = ((fConst22 * (1.11800233889811e-22 + (fConst1 * (1.49997721671747e-25 + fConst47)))) - 1.97393075873917e-19);
	fConst64 = ((fConst1 * ((fConst1 * ((fConst1 * (0 - (2.39932288230564e-25 + fConst12))) - 3.60669905407753e-22)) - 2.71762597345689e-20)) - 1.62378538408517e-19);
	fConst65 = ((fConst1 * (4.60832615818034e-21 + (fConst1 * (6.67221502794578e-23 + (fConst1 * (4.55223559536905e-26 + fConst14)))))) - 4.42988173510265e-34);
	fConst66 = ((fConst1 * ((fConst1 * ((fConst1 * (0 - (3.74994304179366e-26 + fConst16))) - 5.59001169449057e-23)) - 5.22251274319268e-21)) - 9.86965379369583e-20);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlow0 = (0.007000000000000006 * double(fslider0));
	int 	iSlow1 = int((double(fslider1) > 0));
	double 	fSlow2 = (0.01 * double(fslider2));
	double 	fSlow3 = (1 - fSlow2);
	for (int i=0; i<count; i++) {
		fRec0[0] = ((0.993 * fRec0[1]) + fSlow0);
		double fTemp0 = (double)input0[i];
		double fTemp1 = fabs(fTemp0);
		fRec2[0] = ((fConst4 * max(fTemp1, fRec2[1])) + (fConst5 * fTemp1));
		fRec1[0] = ((fConst6 * fRec1[1]) + (fConst7 * fRec2[0]));
		double fTemp2 = ((iSlow1)?max(0.02, min((double)1, fRec1[0])):fRec0[0]);
		double fTemp3 = ((fTemp2 * ((fConst1 * (fConst11 + (fConst9 * fTemp2))) - 4.08813073605905e-30)) + fConst3);
		fRec3[0] = ((fSlow2 * fTemp0) - (((((((fRec3[1] * ((fTemp2 * ((fConst1 * (fConst42 + (fConst41 * fTemp2))) - 2.45287844163543e-29)) + fConst40)) + (fRec3[2] * ((fTemp2 * ((fConst1 * (fConst39 + (fConst38 * fTemp2))) - 6.13219610408857e-29)) + fConst37))) + (fRec3[3] * ((fTemp2 * ((fConst22 * (fConst36 + (fConst35 * fTemp2))) - 8.17626147211809e-29)) + fConst34))) + (fRec3[4] * ((fTemp2 * ((fConst1 * (fConst33 + (fConst31 * fTemp2))) - 6.13219610408857e-29)) + fConst29))) + (fRec3[5] * ((fTemp2 * ((fConst1 * (fConst27 + (fConst25 * fTemp2))) - 2.45287844163543e-29)) + fConst23))) + (fRec3[6] * ((fTemp2 * ((fConst1 * (fConst20 + (fConst19 * fTemp2))) - 4.08813073605905e-30)) + fConst18))) / fTemp3));
		output0[i] = (FAUSTFLOAT)((fSlow3 * fTemp0) + (fConst22 * ((((((((fRec3[0] * ((fTemp2 * (fConst66 + (fConst65 * fTemp2))) + fConst64)) + (fRec3[1] * ((fTemp2 * (fConst63 + (fConst62 * fTemp2))) + fConst61))) + (fRec3[2] * ((fTemp2 * (fConst60 + (fConst59 * fTemp2))) + fConst58))) + (fRec3[3] * ((fTemp2 * (fConst57 + (fConst56 * fTemp2))) + fConst55))) + (fRec3[4] * ((fTemp2 * (fConst54 + (fConst52 * fTemp2))) + fConst50))) + (fRec3[5] * ((fTemp2 * (fConst48 + (fConst46 * fTemp2))) + fConst44))) + (fRec3[6] * ((fTemp2 * (fConst17 + (fConst15 * fTemp2))) + fConst13))) / fTemp3)));
		// post processing
		for (int i=6; i>0; i--) fRec3[i] = fRec3[i-1];
		fRec1[1] = fRec1[0];
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
	reg.registerVar("dallaswah.Wah",N_("Wah"),"S","",&fslider0, 0.5, 0.0, 1.0, 0.01);
	static const value_pair fslider1_values[] = {{"manual"},{"auto"},{0}};
	reg.registerEnumVar("dallaswah.mode","","S","",fslider1_values,&fslider1, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("dallaswah.wet_dry",N_("wet/dry"),"S",N_("percentage of processed signal in output signal"),&fslider2, 1e+02, 0.0, 1e+02, 1.0);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("dallaswah" "." p)

b.openHorizontalhideBox("");
    b.create_master_slider(PARAM("Wah"), "Wah");
b.closeBox();
b.openHorizontalBox("");

    b.create_selector(PARAM("mode"), "Mode");
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

} // end namespace dallaswah
} // end namespace pluginlib
