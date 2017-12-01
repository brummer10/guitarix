// generated from file '../src/plugins/zita_rev1.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

namespace pluginlib {
namespace zita_rev1 {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	int 	IOTA;
	double 	fVec0[8192];
	FAUSTFLOAT 	fslider0;
	double 	fConst0;
	double 	fConst1;
	FAUSTFLOAT 	fslider1;
	double 	fConst2;
	double 	fRec11[2];
	FAUSTFLOAT 	fslider2;
	double 	fConst3;
	double 	fConst4;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT 	fslider4;
	double 	fConst5;
	double 	fRec10[2];
	double 	fVec1[16384];
	double 	fConst6;
	int 	iConst7;
	double 	fVec2[1024];
	int 	iConst8;
	double 	fRec8[2];
	double 	fRec15[2];
	double 	fConst9;
	double 	fConst10;
	double 	fRec14[2];
	double 	fVec3[16384];
	double 	fConst11;
	int 	iConst12;
	double 	fVec4[2048];
	int 	iConst13;
	double 	fRec12[2];
	double 	fRec19[2];
	double 	fConst14;
	double 	fConst15;
	double 	fRec18[2];
	double 	fVec5[8192];
	double 	fConst16;
	int 	iConst17;
	double 	fVec6[2048];
	int 	iConst18;
	double 	fRec16[2];
	double 	fRec23[2];
	double 	fConst19;
	double 	fConst20;
	double 	fRec22[2];
	double 	fVec7[16384];
	double 	fConst21;
	int 	iConst22;
	double 	fVec8[2048];
	int 	iConst23;
	double 	fRec20[2];
	double 	fVec9[8192];
	double 	fRec27[2];
	double 	fConst24;
	double 	fConst25;
	double 	fRec26[2];
	double 	fVec10[8192];
	double 	fConst26;
	int 	iConst27;
	double 	fVec11[1024];
	int 	iConst28;
	double 	fRec24[2];
	double 	fRec31[2];
	double 	fConst29;
	double 	fConst30;
	double 	fRec30[2];
	double 	fVec12[8192];
	double 	fConst31;
	int 	iConst32;
	double 	fVec13[2048];
	int 	iConst33;
	double 	fRec28[2];
	double 	fRec35[2];
	double 	fConst34;
	double 	fConst35;
	double 	fRec34[2];
	double 	fVec14[8192];
	double 	fConst36;
	int 	iConst37;
	double 	fVec15[2048];
	int 	iConst38;
	double 	fRec32[2];
	double 	fRec39[2];
	double 	fConst39;
	double 	fConst40;
	double 	fRec38[2];
	double 	fVec16[8192];
	double 	fConst41;
	int 	iConst42;
	double 	fVec17[1024];
	int 	iConst43;
	double 	fRec36[2];
	double 	fRec0[3];
	double 	fRec1[3];
	double 	fRec2[3];
	double 	fRec3[3];
	double 	fRec4[3];
	double 	fRec5[3];
	double 	fRec6[3];
	double 	fRec7[3];
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT 	fslider6;
	double 	fConst44;
	double 	fRec40[3];
	FAUSTFLOAT 	fslider7;
	FAUSTFLOAT 	fslider8;
	double 	fRec41[3];
	FAUSTFLOAT 	fslider9;
	double 	fRec42[2];
	FAUSTFLOAT 	fslider10;
	double 	fRec43[2];
	double 	fRec44[3];
	double 	fRec45[3];

	void clear_state_f();
	int load_ui_f(const UiBuilder& b, int form);
	static const char *glade_def;
	void init(unsigned int samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static int load_ui_f_static(const UiBuilder& b, int form);
	static void init_static(unsigned int samplingFreq, PluginDef*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginDef*);
	static int register_params_static(const ParamReg& reg);
	static void del_instance(PluginDef *p);
public:
	Dsp();
	~Dsp();
};



static const char* parm_groups[] = {
	"decay_times", N_("Decay Times in Bands"),
	"equalizer1", N_("RM Peaking Equalizer 1"),
	"equalizer2", N_("RM Peaking Equalizer 2"),
	"input", N_("Input"),
	"output", N_("Output"),
	0
	};

Dsp::Dsp()
	: PluginDef() {
	version = PLUGINDEF_VERSION;
	flags = 0;
	id = "zita_rev1";
	name = N_("Zita Rev1");
	groups = parm_groups;
	description = ""; // description (tooltip)
	category = N_("Reverb");       // category
	shortname = "";     // shortname
	mono_audio = 0;
	stereo_audio = compute_static;
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
	for (int i=0; i<8192; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<16384; i++) fVec1[i] = 0;
	for (int i=0; i<1024; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<16384; i++) fVec3[i] = 0;
	for (int i=0; i<2048; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<8192; i++) fVec5[i] = 0;
	for (int i=0; i<2048; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<16384; i++) fVec7[i] = 0;
	for (int i=0; i<2048; i++) fVec8[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<8192; i++) fVec9[i] = 0;
	for (int i=0; i<2; i++) fRec27[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<8192; i++) fVec10[i] = 0;
	for (int i=0; i<1024; i++) fVec11[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fRec31[i] = 0;
	for (int i=0; i<2; i++) fRec30[i] = 0;
	for (int i=0; i<8192; i++) fVec12[i] = 0;
	for (int i=0; i<2048; i++) fVec13[i] = 0;
	for (int i=0; i<2; i++) fRec28[i] = 0;
	for (int i=0; i<2; i++) fRec35[i] = 0;
	for (int i=0; i<2; i++) fRec34[i] = 0;
	for (int i=0; i<8192; i++) fVec14[i] = 0;
	for (int i=0; i<2048; i++) fVec15[i] = 0;
	for (int i=0; i<2; i++) fRec32[i] = 0;
	for (int i=0; i<2; i++) fRec39[i] = 0;
	for (int i=0; i<2; i++) fRec38[i] = 0;
	for (int i=0; i<8192; i++) fVec16[i] = 0;
	for (int i=0; i<1024; i++) fVec17[i] = 0;
	for (int i=0; i<2; i++) fRec36[i] = 0;
	for (int i=0; i<3; i++) fRec0[i] = 0;
	for (int i=0; i<3; i++) fRec1[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<3; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec4[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<3; i++) fRec7[i] = 0;
	for (int i=0; i<3; i++) fRec40[i] = 0;
	for (int i=0; i<3; i++) fRec41[i] = 0;
	for (int i=0; i<2; i++) fRec42[i] = 0;
	for (int i=0; i<2; i++) fRec43[i] = 0;
	for (int i=0; i<3; i++) fRec44[i] = 0;
	for (int i=0; i<3; i++) fRec45[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = min(1.92e+05, max(1.0, (double)fSamplingFreq));
	fConst1 = (0.001 * fConst0);
	fConst2 = (3.141592653589793 / fConst0);
	fConst3 = floor((0.5 + (0.219991 * fConst0)));
	fConst4 = ((0 - (6.907755278982138 * fConst3)) / fConst0);
	fConst5 = (6.283185307179586 / double(fConst0));
	fConst6 = floor((0.5 + (0.019123 * fConst0)));
	iConst7 = int((int((fConst3 - fConst6)) & 16383));
	iConst8 = int((int((fConst6 - 1)) & 1023));
	fConst9 = floor((0.5 + (0.256891 * fConst0)));
	fConst10 = ((0 - (6.907755278982138 * fConst9)) / fConst0);
	fConst11 = floor((0.5 + (0.027333 * fConst0)));
	iConst12 = int((int((fConst9 - fConst11)) & 16383));
	iConst13 = int((int((fConst11 - 1)) & 2047));
	fConst14 = floor((0.5 + (0.192303 * fConst0)));
	fConst15 = ((0 - (6.907755278982138 * fConst14)) / fConst0);
	fConst16 = floor((0.5 + (0.029291 * fConst0)));
	iConst17 = int((int((fConst14 - fConst16)) & 8191));
	iConst18 = int((int((fConst16 - 1)) & 2047));
	fConst19 = floor((0.5 + (0.210389 * fConst0)));
	fConst20 = ((0 - (6.907755278982138 * fConst19)) / fConst0);
	fConst21 = floor((0.5 + (0.024421 * fConst0)));
	iConst22 = int((int((fConst19 - fConst21)) & 16383));
	iConst23 = int((int((fConst21 - 1)) & 2047));
	fConst24 = floor((0.5 + (0.125 * fConst0)));
	fConst25 = ((0 - (6.907755278982138 * fConst24)) / fConst0);
	fConst26 = floor((0.5 + (0.013458 * fConst0)));
	iConst27 = int((int((fConst24 - fConst26)) & 8191));
	iConst28 = int((int((fConst26 - 1)) & 1023));
	fConst29 = floor((0.5 + (0.127837 * fConst0)));
	fConst30 = ((0 - (6.907755278982138 * fConst29)) / fConst0);
	fConst31 = floor((0.5 + (0.031604 * fConst0)));
	iConst32 = int((int((fConst29 - fConst31)) & 8191));
	iConst33 = int((int((fConst31 - 1)) & 2047));
	fConst34 = floor((0.5 + (0.174713 * fConst0)));
	fConst35 = ((0 - (6.907755278982138 * fConst34)) / fConst0);
	fConst36 = floor((0.5 + (0.022904 * fConst0)));
	iConst37 = int((int((fConst34 - fConst36)) & 8191));
	iConst38 = int((int((fConst36 - 1)) & 2047));
	fConst39 = floor((0.5 + (0.153129 * fConst0)));
	fConst40 = ((0 - (6.907755278982138 * fConst39)) / fConst0);
	fConst41 = floor((0.5 + (0.020346 * fConst0)));
	iConst42 = int((int((fConst39 - fConst41)) & 8191));
	iConst43 = int((int((fConst41 - 1)) & 1023));
	fConst44 = (6.283185307179586 / fConst0);
	IOTA = 0;
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
	int 	iSlow0 = int((int((fConst1 * double(fslider0))) & 8191));
	double 	fSlow1 = (1.0 / tan((fConst2 * double(fslider1))));
	double 	fSlow2 = (1 + fSlow1);
	double 	fSlow3 = (0 - ((1 - fSlow1) / fSlow2));
	double 	fSlow4 = (1.0 / fSlow2);
	double 	fSlow5 = double(fslider2);
	double 	fSlow6 = exp((fConst4 / fSlow5));
	double 	fSlow7 = double(fslider3);
	double 	fSlow8 = ((exp((fConst4 / fSlow7)) / fSlow6) - 1);
	double 	fSlow9 = faustpower<2>(fSlow6);
	double 	fSlow10 = (1.0 - fSlow9);
	double 	fSlow11 = cos((fConst5 * double(fslider4)));
	double 	fSlow12 = (1.0 - (fSlow9 * fSlow11));
	double 	fSlow13 = (fSlow12 / fSlow10);
	double 	fSlow14 = sqrt(max((double)0, ((faustpower<2>(fSlow12) / faustpower<2>(fSlow10)) - 1.0)));
	double 	fSlow15 = (fSlow6 * ((1.0 + fSlow14) - fSlow13));
	double 	fSlow16 = (fSlow13 - fSlow14);
	double 	fSlow17 = exp((fConst10 / fSlow5));
	double 	fSlow18 = ((exp((fConst10 / fSlow7)) / fSlow17) - 1);
	double 	fSlow19 = faustpower<2>(fSlow17);
	double 	fSlow20 = (1.0 - fSlow19);
	double 	fSlow21 = (1.0 - (fSlow11 * fSlow19));
	double 	fSlow22 = (fSlow21 / fSlow20);
	double 	fSlow23 = sqrt(max((double)0, ((faustpower<2>(fSlow21) / faustpower<2>(fSlow20)) - 1.0)));
	double 	fSlow24 = (fSlow17 * ((1.0 + fSlow23) - fSlow22));
	double 	fSlow25 = (fSlow22 - fSlow23);
	double 	fSlow26 = exp((fConst15 / fSlow5));
	double 	fSlow27 = ((exp((fConst15 / fSlow7)) / fSlow26) - 1);
	double 	fSlow28 = faustpower<2>(fSlow26);
	double 	fSlow29 = (1.0 - fSlow28);
	double 	fSlow30 = (1.0 - (fSlow11 * fSlow28));
	double 	fSlow31 = (fSlow30 / fSlow29);
	double 	fSlow32 = sqrt(max((double)0, ((faustpower<2>(fSlow30) / faustpower<2>(fSlow29)) - 1.0)));
	double 	fSlow33 = (fSlow26 * ((1.0 + fSlow32) - fSlow31));
	double 	fSlow34 = (fSlow31 - fSlow32);
	double 	fSlow35 = exp((fConst20 / fSlow5));
	double 	fSlow36 = ((exp((fConst20 / fSlow7)) / fSlow35) - 1);
	double 	fSlow37 = faustpower<2>(fSlow35);
	double 	fSlow38 = (1.0 - fSlow37);
	double 	fSlow39 = (1.0 - (fSlow11 * fSlow37));
	double 	fSlow40 = (fSlow39 / fSlow38);
	double 	fSlow41 = sqrt(max((double)0, ((faustpower<2>(fSlow39) / faustpower<2>(fSlow38)) - 1.0)));
	double 	fSlow42 = (fSlow35 * ((1.0 + fSlow41) - fSlow40));
	double 	fSlow43 = (fSlow40 - fSlow41);
	double 	fSlow44 = exp((fConst25 / fSlow5));
	double 	fSlow45 = ((exp((fConst25 / fSlow7)) / fSlow44) - 1);
	double 	fSlow46 = faustpower<2>(fSlow44);
	double 	fSlow47 = (1.0 - fSlow46);
	double 	fSlow48 = (1.0 - (fSlow11 * fSlow46));
	double 	fSlow49 = (fSlow48 / fSlow47);
	double 	fSlow50 = sqrt(max((double)0, ((faustpower<2>(fSlow48) / faustpower<2>(fSlow47)) - 1.0)));
	double 	fSlow51 = (fSlow44 * ((1.0 + fSlow50) - fSlow49));
	double 	fSlow52 = (fSlow49 - fSlow50);
	double 	fSlow53 = exp((fConst30 / fSlow5));
	double 	fSlow54 = ((exp((fConst30 / fSlow7)) / fSlow53) - 1);
	double 	fSlow55 = faustpower<2>(fSlow53);
	double 	fSlow56 = (1.0 - fSlow55);
	double 	fSlow57 = (1.0 - (fSlow11 * fSlow55));
	double 	fSlow58 = (fSlow57 / fSlow56);
	double 	fSlow59 = sqrt(max((double)0, ((faustpower<2>(fSlow57) / faustpower<2>(fSlow56)) - 1.0)));
	double 	fSlow60 = (fSlow53 * ((1.0 + fSlow59) - fSlow58));
	double 	fSlow61 = (fSlow58 - fSlow59);
	double 	fSlow62 = exp((fConst35 / fSlow5));
	double 	fSlow63 = ((exp((fConst35 / fSlow7)) / fSlow62) - 1);
	double 	fSlow64 = faustpower<2>(fSlow62);
	double 	fSlow65 = (1.0 - fSlow64);
	double 	fSlow66 = (1.0 - (fSlow11 * fSlow64));
	double 	fSlow67 = (fSlow66 / fSlow65);
	double 	fSlow68 = sqrt(max((double)0, ((faustpower<2>(fSlow66) / faustpower<2>(fSlow65)) - 1.0)));
	double 	fSlow69 = (fSlow62 * ((1.0 + fSlow68) - fSlow67));
	double 	fSlow70 = (fSlow67 - fSlow68);
	double 	fSlow71 = exp((fConst40 / fSlow5));
	double 	fSlow72 = ((exp((fConst40 / fSlow7)) / fSlow71) - 1);
	double 	fSlow73 = faustpower<2>(fSlow71);
	double 	fSlow74 = (1.0 - fSlow73);
	double 	fSlow75 = (1.0 - (fSlow11 * fSlow73));
	double 	fSlow76 = (fSlow75 / fSlow74);
	double 	fSlow77 = sqrt(max((double)0, ((faustpower<2>(fSlow75) / faustpower<2>(fSlow74)) - 1.0)));
	double 	fSlow78 = (fSlow71 * ((1.0 + fSlow77) - fSlow76));
	double 	fSlow79 = (fSlow76 - fSlow77);
	double 	fSlow80 = pow(10,(0.05 * double(fslider5)));
	double 	fSlow81 = double(fslider6);
	double 	fSlow82 = (fConst44 * (fSlow81 / sqrt(fSlow80)));
	double 	fSlow83 = ((1.0 - fSlow82) / (1.0 + fSlow82));
	double 	fSlow84 = ((0 - cos((fConst44 * fSlow81))) * (1 + fSlow83));
	double 	fSlow85 = pow(10,(0.05 * double(fslider7)));
	double 	fSlow86 = double(fslider8);
	double 	fSlow87 = (fConst44 * (fSlow86 / sqrt(fSlow85)));
	double 	fSlow88 = ((1.0 - fSlow87) / (1.0 + fSlow87));
	double 	fSlow89 = ((0 - cos((fConst44 * fSlow86))) * (1 + fSlow88));
	double 	fSlow90 = (0.0010000000000000009 * double(fslider9));
	double 	fSlow91 = (0.0010000000000000009 * double(fslider10));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input1[i];
		fVec0[IOTA&8191] = fTemp0;
		double fTemp1 = (0.3 * fVec0[(IOTA-iSlow0)&8191]);
		fRec11[0] = ((fSlow4 * (fRec7[1] + fRec7[2])) + (fSlow3 * fRec11[1]));
		fRec10[0] = ((fSlow16 * fRec10[1]) + (fSlow15 * (fRec7[1] + (fSlow8 * fRec11[0]))));
		fVec1[IOTA&16383] = (1e-20 + (0.35355339059327373 * fRec10[0]));
		double fTemp2 = (((0.6 * fRec8[1]) + fVec1[(IOTA-iConst7)&16383]) - fTemp1);
		fVec2[IOTA&1023] = fTemp2;
		fRec8[0] = fVec2[(IOTA-iConst8)&1023];
		double 	fRec9 = (0 - (0.6 * fVec2[IOTA&1023]));
		double fTemp3 = (fRec8[1] + fRec9);
		fRec15[0] = ((fSlow4 * (fRec3[1] + fRec3[2])) + (fSlow3 * fRec15[1]));
		fRec14[0] = ((fSlow25 * fRec14[1]) + (fSlow24 * (fRec3[1] + (fSlow18 * fRec15[0]))));
		fVec3[IOTA&16383] = (1e-20 + (0.35355339059327373 * fRec14[0]));
		double fTemp4 = (((0.6 * fRec12[1]) + fVec3[(IOTA-iConst12)&16383]) - fTemp1);
		fVec4[IOTA&2047] = fTemp4;
		fRec12[0] = fVec4[(IOTA-iConst13)&2047];
		double 	fRec13 = (0 - (0.6 * fVec4[IOTA&2047]));
		double fTemp5 = (fRec13 + (fRec12[1] + fTemp3));
		fRec19[0] = ((fSlow4 * (fRec5[1] + fRec5[2])) + (fSlow3 * fRec19[1]));
		fRec18[0] = ((fSlow34 * fRec18[1]) + (fSlow33 * (fRec5[1] + (fSlow27 * fRec19[0]))));
		fVec5[IOTA&8191] = (1e-20 + (0.35355339059327373 * fRec18[0]));
		double fTemp6 = (fVec5[(IOTA-iConst17)&8191] + (fTemp1 + (0.6 * fRec16[1])));
		fVec6[IOTA&2047] = fTemp6;
		fRec16[0] = fVec6[(IOTA-iConst18)&2047];
		double 	fRec17 = (0 - (0.6 * fVec6[IOTA&2047]));
		fRec23[0] = ((fSlow4 * (fRec1[1] + fRec1[2])) + (fSlow3 * fRec23[1]));
		fRec22[0] = ((fSlow43 * fRec22[1]) + (fSlow42 * (fRec1[1] + (fSlow36 * fRec23[0]))));
		fVec7[IOTA&16383] = (1e-20 + (0.35355339059327373 * fRec22[0]));
		double fTemp7 = (fVec7[(IOTA-iConst22)&16383] + (fTemp1 + (0.6 * fRec20[1])));
		fVec8[IOTA&2047] = fTemp7;
		fRec20[0] = fVec8[(IOTA-iConst23)&2047];
		double 	fRec21 = (0 - (0.6 * fVec8[IOTA&2047]));
		double fTemp8 = (fRec21 + (fRec20[1] + (fRec17 + (fRec16[1] + fTemp5))));
		double fTemp9 = (double)input0[i];
		fVec9[IOTA&8191] = fTemp9;
		double fTemp10 = (0.3 * fVec9[(IOTA-iSlow0)&8191]);
		fRec27[0] = ((fSlow4 * (fRec6[1] + fRec6[2])) + (fSlow3 * fRec27[1]));
		fRec26[0] = ((fSlow52 * fRec26[1]) + (fSlow51 * (fRec6[1] + (fSlow45 * fRec27[0]))));
		fVec10[IOTA&8191] = (1e-20 + (0.35355339059327373 * fRec26[0]));
		double fTemp11 = (fVec10[(IOTA-iConst27)&8191] - (fTemp10 + (0.6 * fRec24[1])));
		fVec11[IOTA&1023] = fTemp11;
		fRec24[0] = fVec11[(IOTA-iConst28)&1023];
		double 	fRec25 = (0.6 * fVec11[IOTA&1023]);
		fRec31[0] = ((fSlow4 * (fRec2[1] + fRec2[2])) + (fSlow3 * fRec31[1]));
		fRec30[0] = ((fSlow61 * fRec30[1]) + (fSlow60 * (fRec2[1] + (fSlow54 * fRec31[0]))));
		fVec12[IOTA&8191] = (1e-20 + (0.35355339059327373 * fRec30[0]));
		double fTemp12 = (fVec12[(IOTA-iConst32)&8191] - (fTemp10 + (0.6 * fRec28[1])));
		fVec13[IOTA&2047] = fTemp12;
		fRec28[0] = fVec13[(IOTA-iConst33)&2047];
		double 	fRec29 = (0.6 * fVec13[IOTA&2047]);
		fRec35[0] = ((fSlow4 * (fRec4[1] + fRec4[2])) + (fSlow3 * fRec35[1]));
		fRec34[0] = ((fSlow70 * fRec34[1]) + (fSlow69 * (fRec4[1] + (fSlow63 * fRec35[0]))));
		fVec14[IOTA&8191] = (1e-20 + (0.35355339059327373 * fRec34[0]));
		double fTemp13 = ((fTemp10 + fVec14[(IOTA-iConst37)&8191]) - (0.6 * fRec32[1]));
		fVec15[IOTA&2047] = fTemp13;
		fRec32[0] = fVec15[(IOTA-iConst38)&2047];
		double 	fRec33 = (0.6 * fVec15[IOTA&2047]);
		fRec39[0] = ((fSlow4 * (fRec0[1] + fRec0[2])) + (fSlow3 * fRec39[1]));
		fRec38[0] = ((fSlow79 * fRec38[1]) + (fSlow78 * (fRec0[1] + (fSlow72 * fRec39[0]))));
		fVec16[IOTA&8191] = (1e-20 + (0.35355339059327373 * fRec38[0]));
		double fTemp14 = ((fTemp10 + fVec16[(IOTA-iConst42)&8191]) - (0.6 * fRec36[1]));
		fVec17[IOTA&1023] = fTemp14;
		fRec36[0] = fVec17[(IOTA-iConst43)&1023];
		double 	fRec37 = (0.6 * fVec17[IOTA&1023]);
		fRec0[0] = (fRec37 + (fRec36[1] + (fRec33 + (fRec32[1] + (fRec29 + (fRec28[1] + (fRec25 + (fRec24[1] + fTemp8))))))));
		fRec1[0] = (0 - (fTemp8 - (fRec37 + (fRec36[1] + (fRec33 + (fRec32[1] + (fRec29 + (fRec28[1] + (fRec24[1] + fRec25)))))))));
		double fTemp15 = (fRec21 + (fRec20[1] + (fRec16[1] + fRec17)));
		fRec2[0] = (0 - ((fRec29 + (fRec28[1] + (fRec25 + (fRec24[1] + fTemp5)))) - (fRec37 + (fRec36[1] + (fRec33 + (fRec32[1] + fTemp15))))));
		fRec3[0] = (0 - ((fRec29 + (fRec28[1] + (fRec25 + (fRec24[1] + fTemp15)))) - (fRec37 + (fRec36[1] + (fRec33 + (fRec32[1] + fTemp5))))));
		double fTemp16 = (fRec12[1] + fRec13);
		double fTemp17 = (fRec21 + (fRec20[1] + fTemp16));
		double fTemp18 = (fRec17 + (fRec16[1] + fTemp3));
		fRec4[0] = (0 - ((fRec33 + (fRec32[1] + (fRec25 + (fRec24[1] + fTemp18)))) - (fRec37 + (fRec36[1] + (fRec29 + (fRec28[1] + fTemp17))))));
		fRec5[0] = (0 - ((fRec33 + (fRec32[1] + (fRec25 + (fRec24[1] + fTemp17)))) - (fRec37 + (fRec36[1] + (fRec29 + (fRec28[1] + fTemp18))))));
		double fTemp19 = (fRec21 + (fRec20[1] + fTemp3));
		double fTemp20 = (fRec17 + (fRec16[1] + fTemp16));
		fRec6[0] = (0 - ((fRec33 + (fRec32[1] + (fRec29 + (fRec28[1] + fTemp20)))) - (fRec37 + (fRec36[1] + (fRec25 + (fRec24[1] + fTemp19))))));
		fRec7[0] = (0 - ((fRec33 + (fRec32[1] + (fRec29 + (fRec28[1] + fTemp19)))) - (fRec37 + (fRec36[1] + (fRec25 + (fRec24[1] + fTemp20))))));
		double fTemp21 = (0.37 * (fRec1[0] + fRec2[0]));
		double fTemp22 = (fSlow84 * fRec40[1]);
		fRec40[0] = (0 - ((fTemp22 + (fSlow83 * fRec40[2])) - fTemp21));
		double fTemp23 = (fTemp22 + fRec40[2]);
		double fTemp24 = (fSlow83 * fRec40[0]);
		double fTemp25 = (0.5 * ((fTemp24 + (fTemp21 + fTemp23)) + (fSlow80 * ((fTemp24 + fTemp23) - fTemp21))));
		double fTemp26 = (fSlow89 * fRec41[1]);
		fRec41[0] = (0 - ((fTemp26 + (fSlow88 * fRec41[2])) - fTemp25));
		double fTemp27 = ((fSlow88 * fRec41[0]) + (fTemp26 + fRec41[2]));
		fRec42[0] = (fSlow90 + (0.999 * fRec42[1]));
		double fTemp28 = (1.0 + fRec42[0]);
		double fTemp29 = (1.0 - (0.5 * fTemp28));
		fRec43[0] = (fSlow91 + (0.999 * fRec43[1]));
		double fTemp30 = pow(10,(0.05 * fRec43[0]));
		output0[i] = (FAUSTFLOAT)(fTemp30 * ((fVec9[IOTA&8191] * fTemp29) + (0.25 * (fTemp28 * ((fTemp25 + fTemp27) + (fSlow85 * (fTemp27 - fTemp25)))))));
		double fTemp31 = (0.37 * (fRec1[0] - fRec2[0]));
		double fTemp32 = (fSlow84 * fRec44[1]);
		fRec44[0] = (0 - ((fTemp32 + (fSlow83 * fRec44[2])) - fTemp31));
		double fTemp33 = (fTemp32 + fRec44[2]);
		double fTemp34 = (fSlow83 * fRec44[0]);
		double fTemp35 = (0.5 * ((fTemp34 + (fTemp31 + fTemp33)) + (fSlow80 * ((fTemp34 + fTemp33) - fTemp31))));
		double fTemp36 = (fSlow89 * fRec45[1]);
		fRec45[0] = (0 - ((fTemp36 + (fSlow88 * fRec45[2])) - fTemp35));
		double fTemp37 = ((fSlow88 * fRec45[0]) + (fTemp36 + fRec45[2]));
		output1[i] = (FAUSTFLOAT)(fTemp30 * ((fVec0[IOTA&8191] * fTemp29) + (0.25 * (fTemp28 * ((fTemp35 + fTemp37) + (fSlow85 * (fTemp37 - fTemp35)))))));
		// post processing
		fRec45[2] = fRec45[1]; fRec45[1] = fRec45[0];
		fRec44[2] = fRec44[1]; fRec44[1] = fRec44[0];
		fRec43[1] = fRec43[0];
		fRec42[1] = fRec42[0];
		fRec41[2] = fRec41[1]; fRec41[1] = fRec41[0];
		fRec40[2] = fRec40[1]; fRec40[1] = fRec40[0];
		fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		fRec36[1] = fRec36[0];
		fRec38[1] = fRec38[0];
		fRec39[1] = fRec39[0];
		fRec32[1] = fRec32[0];
		fRec34[1] = fRec34[0];
		fRec35[1] = fRec35[0];
		fRec28[1] = fRec28[0];
		fRec30[1] = fRec30[0];
		fRec31[1] = fRec31[0];
		fRec24[1] = fRec24[0];
		fRec26[1] = fRec26[0];
		fRec27[1] = fRec27[0];
		fRec20[1] = fRec20[0];
		fRec22[1] = fRec22[0];
		fRec23[1] = fRec23[0];
		fRec16[1] = fRec16[0];
		fRec18[1] = fRec18[0];
		fRec19[1] = fRec19[0];
		fRec12[1] = fRec12[0];
		fRec14[1] = fRec14[0];
		fRec15[1] = fRec15[0];
		fRec8[1] = fRec8[0];
		fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		IOTA = IOTA+1;
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("zita_rev1.decay_times.hf_damping",N_("HF Damp"),"SL",N_("Frequency (Hz) at which the high-frequency T60 is half the middle-band's T60"),&fslider4, 6e+03, 1.5e+03, 2.352e+04, 1.08);
	reg.registerVar("zita_rev1.decay_times.lf_x",N_("Freq X"),"SL",N_("Crossover frequency (Hz) separating low and middle frequencies"),&fslider1, 2e+02, 5e+01, 1e+03, 1.08);
	reg.registerVar("zita_rev1.decay_times.low_rt60",N_("Low"),"SL",N_("T60 = time (in seconds) to decay 60dB in low-frequency band"),&fslider3, 3.0, 1.0, 8.0, 1.08);
	reg.registerVar("zita_rev1.decay_times.mid_rt60",N_("Mid"),"SL",N_("T60 = time (in seconds) to decay 60dB in middle band"),&fslider2, 2.0, 1.0, 8.0, 1.08);
	reg.registerVar("zita_rev1.equalizer1.eq1_freq",N_("Freq"),"SL",N_("Center-frequency of second-order Regalia-Mitra peaking equalizer section 1"),&fslider6, 315.0, 4e+01, 2.5e+03, 1.08);
	reg.registerVar("zita_rev1.equalizer1.eq1_level",N_("Level"),"S",N_("Peak level in dB of second-order Regalia-Mitra peaking equalizer section 1"),&fslider5, 0.0, -15.0, 15.0, 0.1);
	reg.registerVar("zita_rev1.equalizer2.eq2_freq",N_("Freq"),"SL",N_("Center-frequency of second-order Regalia-Mitra peaking equalizer section 2"),&fslider8, 1.5e+03, 1.6e+02, 1e+04, 1.08);
	reg.registerVar("zita_rev1.equalizer2.eq2_level",N_("Level"),"S",N_("Peak level in dB of second-order Regalia-Mitra peaking equalizer section 2"),&fslider7, 0.0, -15.0, 15.0, 0.1);
	reg.registerVar("zita_rev1.input.in_delay",N_("Pre Delay"),"S",N_("Delay in ms before reverberation begins"),&fslider0, 6e+01, 2e+01, 1e+02, 1.0);
	reg.registerVar("zita_rev1.output.dry_wet_mix",N_("Dry/Wet"),"S",N_("-1 = dry, 1 = wet"),&fslider9, 0.0, -1.0, 1.0, 0.01);
	reg.registerVar("zita_rev1.output.level",N_("Level"),"S",N_("Output scale factor"),&fslider10, 0.0, -7e+01, 4e+01, 0.1);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

const char *Dsp::glade_def = "\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<interface>\n\
  <requires lib=\"gtk+\" version=\"2.20\"/>\n\
  <!-- interface-requires gxwidgets 0.0 -->\n\
  <!-- interface-naming-policy project-wide -->\n\
  <object class=\"GtkWindow\" id=\"window1\">\n\
    <property name=\"can_focus\">False</property>\n\
    <property name=\"resizable\">False</property>\n\
    <property name=\"default_width\">0</property>\n\
    <property name=\"default_height\">0</property>\n\
    <child>\n\
      <object class=\"GtkVBox\" id=\"vbox12\">\n\
        <property name=\"visible\">True</property>\n\
        <property name=\"can_focus\">False</property>\n\
        <property name=\"spacing\">10</property>\n\
        <child>\n\
          <object class=\"GtkHBox\" id=\"minibox\">\n\
            <property name=\"visible\">True</property>\n\
            <property name=\"can_focus\">False</property>\n\
            <property name=\"spacing\">5</property>\n\
            <child>\n\
              <object class=\"GxHSlider\" id=\"gxhslider1\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">True</property>\n\
                <property name=\"receives_default\">True</property>\n\
                <property name=\"round_digits\">0</property>\n\
                <property name=\"var_id\">zita_rev1.output.dry_wet_mix</property>\n\
                <property name=\"show_value\">False</property>\n\
                <property name=\"value_position\">right</property>\n\
                <property name=\"value_xalign\">0.52000000000000002</property>\n\
                <property name=\"label_ref\">label12:rack_label</property>\n\
              </object>\n\
              <packing>\n\
                <property name=\"expand\">False</property>\n\
                <property name=\"fill\">False</property>\n\
                <property name=\"position\">0</property>\n\
              </packing>\n\
            </child>\n\
            <child>\n\
              <object class=\"GtkLabel\" id=\"label12:rack_label\">\n\
                <property name=\"height_request\">12</property>\n\
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
            <property name=\"position\">0</property>\n\
          </packing>\n\
        </child>\n\
        <child>\n\
          <object class=\"GtkHBox\" id=\"rackbox\">\n\
            <property name=\"visible\">True</property>\n\
            <property name=\"can_focus\">False</property>\n\
            <child>\n\
              <object class=\"GtkVBox\" id=\"vbox\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">False</property>\n\
                <property name=\"spacing\">16</property>\n\
                <child>\n\
                  <object class=\"GtkHBox\" id=\"hbox2\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"spacing\">5</property>\n\
                    <child>\n\
                      <object class=\"GtkFrame\" id=\"frame4\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label_xalign\">0.5</property>\n\
                        <child>\n\
                          <object class=\"GtkAlignment\" id=\"alignment4\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"top_padding\">2</property>\n\
                            <property name=\"bottom_padding\">2</property>\n\
                            <property name=\"left_padding\">2</property>\n\
                            <property name=\"right_padding\">2</property>\n\
                            <child>\n\
                              <object class=\"GtkHBox\" id=\"hbox6\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <child>\n\
                                  <object class=\"GtkVBox\" id=\"vbox7\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <child>\n\
                                      <object class=\"GtkLabel\" id=\"label1:rack_label\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"label\">label</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">False</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">0</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GxSmallKnobR\" id=\"gxsmallknob1\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">True</property>\n\
                                        <property name=\"receives_default\">True</property>\n\
                                        <property name=\"round_digits\">0</property>\n\
                                        <property name=\"var_id\">zita_rev1.input.in_delay</property>\n\
                                        <property name=\"label_ref\">label1:rack_label</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">False</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">1</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">True</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"position\">0</property>\n\
                                  </packing>\n\
                                </child>\n\
                                <child>\n\
                                  <object class=\"GtkVBox\" id=\"vbox9\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <child>\n\
                                      <object class=\"GtkLabel\" id=\"label3:rack_label\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"label\">label</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">0</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GxSmallKnobR\" id=\"gxsmallknob3\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">True</property>\n\
                                        <property name=\"receives_default\">True</property>\n\
                                        <property name=\"round_digits\">0</property>\n\
                                        <property name=\"var_id\">zita_rev1.decay_times.low_rt60</property>\n\
                                        <property name=\"label_ref\">label3:rack_label</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
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
                                <child>\n\
                                  <object class=\"GtkVBox\" id=\"vbox8\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <child>\n\
                                      <object class=\"GtkLabel\" id=\"label2:rack_label\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"label\">label</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">False</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">0</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GxSmallKnob\" id=\"gxminislider1\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">True</property>\n\
                                        <property name=\"receives_default\">True</property>\n\
                                        <property name=\"round_digits\">0</property>\n\
                                        <property name=\"var_id\">zita_rev1.decay_times.lf_x</property>\n\
                                        <property name=\"show_value\">False</property>\n\
                                        <property name=\"label_ref\">label2:rack_label</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">1</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GtkAlignment\" id=\"alignment6\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"xscale\">0</property>\n\
                                        <property name=\"yscale\">0</property>\n\
                                        <child>\n\
                                          <object class=\"GxValueDisplay\" id=\"gxvaluedisplay1\">\n\
                                            <property name=\"visible\">True</property>\n\
                                            <property name=\"can_focus\">True</property>\n\
                                            <property name=\"receives_default\">True</property>\n\
                                            <property name=\"round_digits\">0</property>\n\
                                            <property name=\"var_id\">zita_rev1.decay_times.lf_x</property>\n\
                                          </object>\n\
                                        </child>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">False</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">2</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">True</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"position\">2</property>\n\
                                  </packing>\n\
                                </child>\n\
                                <child>\n\
                                  <object class=\"GtkVBox\" id=\"vbox10\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <child>\n\
                                      <object class=\"GtkLabel\" id=\"label4:rack_label\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"label\">label</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">0</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GxSmallKnobR\" id=\"gxsmallknob4\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">True</property>\n\
                                        <property name=\"receives_default\">True</property>\n\
                                        <property name=\"round_digits\">0</property>\n\
                                        <property name=\"var_id\">zita_rev1.decay_times.mid_rt60</property>\n\
                                        <property name=\"label_ref\">label4:rack_label</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">1</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">True</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"position\">3</property>\n\
                                  </packing>\n\
                                </child>\n\
                                <child>\n\
                                  <object class=\"GtkVBox\" id=\"vbox11\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <child>\n\
                                      <object class=\"GtkLabel\" id=\"label5:rack_label\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"label\">label</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">0</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GxSmallKnobR\" id=\"gxsmallknob5\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">True</property>\n\
                                        <property name=\"receives_default\">True</property>\n\
                                        <property name=\"round_digits\">0</property>\n\
                                        <property name=\"var_id\">zita_rev1.decay_times.hf_damping</property>\n\
                                        <property name=\"label_ref\">label5:rack_label</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">1</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">True</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"position\">4</property>\n\
                                  </packing>\n\
                                </child>\n\
                              </object>\n\
                            </child>\n\
                          </object>\n\
                        </child>\n\
                        <child type=\"label\">\n\
                          <object class=\"GtkLabel\" id=\"label121:rack_label\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"label\" translatable=\"yes\">Reverb</property>\n\
                            <property name=\"use_markup\">True</property>\n\
                          </object>\n\
                        </child>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">True</property>\n\
                        <property name=\"fill\">True</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">False</property>\n\
                    <property name=\"fill\">True</property>\n\
                    <property name=\"position\">0</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkHBox\" id=\"hbox3\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"spacing\">4</property>\n\
                    <child>\n\
                      <object class=\"GtkFrame\" id=\"frame1:frame_inversed\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label_xalign\">0.5</property>\n\
                        <child>\n\
                          <object class=\"GtkAlignment\" id=\"alignment1\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"top_padding\">5</property>\n\
                            <property name=\"bottom_padding\">5</property>\n\
                            <property name=\"left_padding\">5</property>\n\
                            <property name=\"right_padding\">5</property>\n\
                            <child>\n\
                              <object class=\"GtkHBox\" id=\"hbox4\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <child>\n\
                                  <object class=\"GtkHBox\" id=\"vbox1\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <child>\n\
                                      <object class=\"GtkLabel\" id=\"label6:rack_label_inverse\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"label\">label</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">0</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GxSmallKnob\" id=\"gxsmallknob6\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">True</property>\n\
                                        <property name=\"receives_default\">True</property>\n\
                                        <property name=\"round_digits\">0</property>\n\
                                        <property name=\"var_id\">zita_rev1.equalizer1.eq1_freq</property>\n\
                                        <property name=\"label_ref\">label6:rack_label_inverse</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">1</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">True</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"padding\">2</property>\n\
                                    <property name=\"position\">0</property>\n\
                                  </packing>\n\
                                </child>\n\
                                <child>\n\
                                  <object class=\"GtkHBox\" id=\"vbox2\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <child>\n\
                                      <object class=\"GtkLabel\" id=\"label7:rack_label_inverse\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"label\">label</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">0</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GxSmallKnob\" id=\"gxsmallknob7\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">True</property>\n\
                                        <property name=\"receives_default\">True</property>\n\
                                        <property name=\"round_digits\">0</property>\n\
                                        <property name=\"var_id\">zita_rev1.equalizer1.eq1_level</property>\n\
                                        <property name=\"label_ref\">label7:rack_label_inverse</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">1</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">True</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"padding\">2</property>\n\
                                    <property name=\"position\">1</property>\n\
                                  </packing>\n\
                                </child>\n\
                              </object>\n\
                            </child>\n\
                          </object>\n\
                        </child>\n\
                        <child type=\"label\">\n\
                          <object class=\"GtkLabel\" id=\"label15:rack_label_inverse\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"label\" translatable=\"yes\">Filter 1</property>\n\
                            <property name=\"use_markup\">True</property>\n\
                          </object>\n\
                        </child>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">True</property>\n\
                        <property name=\"fill\">True</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GtkFrame\" id=\"frame2:frame_inversed\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label_xalign\">0.5</property>\n\
                        <child>\n\
                          <object class=\"GtkAlignment\" id=\"alignment2\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"top_padding\">5</property>\n\
                            <property name=\"bottom_padding\">5</property>\n\
                            <property name=\"left_padding\">5</property>\n\
                            <property name=\"right_padding\">5</property>\n\
                            <child>\n\
                              <object class=\"GtkHBox\" id=\"hbox7\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <child>\n\
                                  <object class=\"GtkHBox\" id=\"vbox3\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <child>\n\
                                      <object class=\"GtkLabel\" id=\"label8:rack_label_inverse\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"label\">label</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">0</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GxSmallKnob\" id=\"gxsmallknob8\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">True</property>\n\
                                        <property name=\"receives_default\">True</property>\n\
                                        <property name=\"round_digits\">0</property>\n\
                                        <property name=\"var_id\">zita_rev1.equalizer2.eq2_freq</property>\n\
                                        <property name=\"label_ref\">label8:rack_label_inverse</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">1</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">True</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"padding\">2</property>\n\
                                    <property name=\"position\">0</property>\n\
                                  </packing>\n\
                                </child>\n\
                                <child>\n\
                                  <object class=\"GtkHBox\" id=\"vbox4\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <child>\n\
                                      <object class=\"GtkLabel\" id=\"label9:rack_label_inverse\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"label\">label</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">0</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GxSmallKnob\" id=\"gxsmallknob9\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">True</property>\n\
                                        <property name=\"receives_default\">True</property>\n\
                                        <property name=\"round_digits\">0</property>\n\
                                        <property name=\"var_id\">zita_rev1.equalizer2.eq2_level</property>\n\
                                        <property name=\"label_ref\">label9:rack_label_inverse</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">1</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">True</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"padding\">2</property>\n\
                                    <property name=\"position\">1</property>\n\
                                  </packing>\n\
                                </child>\n\
                              </object>\n\
                            </child>\n\
                          </object>\n\
                        </child>\n\
                        <child type=\"label\">\n\
                          <object class=\"GtkLabel\" id=\"label14:rack_label_inverse\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"label\" translatable=\"yes\">Filter 2</property>\n\
                            <property name=\"use_markup\">True</property>\n\
                          </object>\n\
                        </child>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">True</property>\n\
                        <property name=\"fill\">True</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">False</property>\n\
                    <property name=\"fill\">True</property>\n\
                    <property name=\"position\">1</property>\n\
                  </packing>\n\
                </child>\n\
              </object>\n\
              <packing>\n\
                <property name=\"expand\">True</property>\n\
                <property name=\"fill\">True</property>\n\
                <property name=\"position\">0</property>\n\
              </packing>\n\
            </child>\n\
            <child>\n\
              <object class=\"GtkVBox\" id=\"vbox13\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">False</property>\n\
                <property name=\"spacing\">20</property>\n\
                <child>\n\
                  <object class=\"GtkAlignment\" id=\"alignment3\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"top_padding\">18</property>\n\
                    <child>\n\
                      <object class=\"GtkVBox\" id=\"vbox5\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <child>\n\
                          <object class=\"GtkLabel\" id=\"label10:rack_label\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"label\">label</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">0</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GxSmallKnobR\" id=\"gxsmallknob10\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">True</property>\n\
                            <property name=\"receives_default\">True</property>\n\
                            <property name=\"round_digits\">0</property>\n\
                            <property name=\"var_id\">zita_rev1.output.dry_wet_mix</property>\n\
                            <property name=\"label_ref\">label10:rack_label</property>\n\
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
                  <packing>\n\
                    <property name=\"expand\">True</property>\n\
                    <property name=\"fill\">True</property>\n\
                    <property name=\"position\">0</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkVBox\" id=\"vbox6\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label11:rack_label_inverse\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\">label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">True</property>\n\
                        <property name=\"fill\">True</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSmallKnobR\" id=\"gxsmallknob11\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"round_digits\">0</property>\n\
                        <property name=\"var_id\">zita_rev1.output.level</property>\n\
                        <property name=\"label_ref\">label11:rack_label_inverse</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">True</property>\n\
                        <property name=\"fill\">True</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">True</property>\n\
                    <property name=\"fill\">True</property>\n\
                    <property name=\"padding\">2</property>\n\
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
#define PARAM(p) ("zita_rev1" "." p)
b.openHorizontalhideBox("");
{
    b.create_master_slider(PARAM("output.level"), "Level");
}
b.closeBox();
b.openVerticalBox("");
{
    b.create_small_rackknob(PARAM("input.in_delay"), "In Delay");
    b.create_small_rackknob(PARAM("output.dry_wet_mix"), "Dry/Wet");
    b.create_small_rackknob(PARAM("output.level"), "Level");

    b.openHorizontalBox("Reverb Time T60");
    {
	b.create_small_rackknob(PARAM("decay_times.lf_x"), "Freq X");
	b.create_small_rackknob(PARAM("decay_times.low_rt60"), "Low");
	b.create_small_rackknob(PARAM("decay_times.mid_rt60"), "Mid");
	b.create_small_rackknob(PARAM("decay_times.hf_damping"), "HF Damping");
    }
    b.closeBox();

    b.openHorizontalBox("Eq1");
    {
	b.create_small_rackknob(PARAM("equalizer1.eq1_freq"), "Freq");
	b.create_small_rackknob(PARAM("equalizer1.eq1_level"), "Level");
    }
    b.closeBox();

    b.openHorizontalBox("Eq2");
    {
	b.create_small_rackknob(PARAM("equalizer2.eq2_freq"), "Freq");
	b.create_small_rackknob(PARAM("equalizer2.eq2_level"), "Level");
    }
    b.closeBox();
}
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

} // end namespace zita_rev1
} // end namespace pluginlib
