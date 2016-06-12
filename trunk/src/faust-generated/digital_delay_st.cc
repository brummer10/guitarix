// generated from file '../src/faust/digital_delay_st.dsp' by dsp2cc:
// Code generated with Faust 0.9.73 (http://faust.grame.fr)

#include "beat.h"

namespace digital_delay_st {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT 	fslider1;
	int 	iConst0;
	float 	fConst1;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT 	fslider3;
	float 	fRec2[3];
	float 	fRec1[3];
	float 	fVec0[2];
	float 	fConst2;
	float 	fConst3;
	float 	fConst4;
	float 	fConst5;
	float 	fConst6;
	float 	fConst7;
	float 	fConst8;
	float 	fConst9;
	float 	fConst10;
	float 	fConst11;
	float 	fConst12;
	float 	fConst13;
	float 	fConst14;
	float 	fConst15;
	float 	fConst16;
	float 	fConst17;
	float 	fConst18;
	float 	fConst19;
	float 	fConst20;
	float 	fConst21;
	float 	fConst22;
	float 	fConst23;
	float 	fConst24;
	float 	fConst25;
	float 	fConst26;
	float 	fConst27;
	float 	fConst28;
	float 	fConst29;
	float 	fConst30;
	float 	fConst31;
	float 	fConst32;
	float 	fConst33;
	float 	fConst34;
	float 	fConst35;
	float 	fConst36;
	float 	fConst37;
	float 	fConst38;
	float 	fConst39;
	float 	fConst40;
	float 	fConst41;
	float 	fConst42;
	float 	fConst43;
	float 	fConst44;
	float 	fConst45;
	float 	fConst46;
	float 	fConst47;
	float 	fConst48;
	float 	fConst49;
	float 	fConst50;
	float 	fConst51;
	float 	fConst52;
	float 	fConst53;
	float 	fConst54;
	float 	fRec11[2];
	float 	fRec10[3];
	float 	fConst55;
	float 	fRec9[3];
	float 	fConst56;
	float 	fConst57;
	float 	fConst58;
	float 	fRec8[3];
	float 	fConst59;
	float 	fConst60;
	float 	fConst61;
	float 	fRec7[3];
	float 	fConst62;
	float 	fConst63;
	float 	fConst64;
	float 	fRec6[3];
	float 	fConst65;
	float 	fConst66;
	float 	fConst67;
	float 	fRec5[3];
	float 	fConst68;
	float 	fConst69;
	float 	fConst70;
	float 	fVec1[2];
	float 	fConst71;
	float 	fConst72;
	float 	fConst73;
	float 	fRec4[2];
	float 	fRec3[3];
	float 	fConst74;
	FAUSTFLOAT 	fslider4;
	float 	fRec18[2];
	float 	fRec16[2];
	float 	fRec14[2];
	float 	fRec12[2];
	float 	fRec26[2];
	float 	fRec24[2];
	float 	fRec22[2];
	float 	fRec20[2];
	int 	IOTA;
	float *fVec2;
	float 	fConst75;
	float 	fConst76;
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT 	fslider6;
	int 	iConst77;
	float 	fRec28[2];
	float 	fRec29[2];
	float 	fRec30[2];
	float 	fRec31[2];
	FAUSTFLOAT 	fslider7;
	float 	fRec0[2];
	FAUSTFLOAT 	fslider8;
	float 	fRec34[3];
	float 	fRec33[3];
	float 	fVec3[2];
	float 	fRec43[2];
	float 	fRec42[3];
	float 	fRec41[3];
	float 	fRec40[3];
	float 	fRec39[3];
	float 	fRec38[3];
	float 	fRec37[3];
	float 	fVec4[2];
	float 	fRec36[2];
	float 	fRec35[3];
	float 	fRec50[2];
	float 	fRec48[2];
	float 	fRec46[2];
	float 	fRec44[2];
	float 	fRec58[2];
	float 	fRec56[2];
	float 	fRec54[2];
	float 	fRec52[2];
	float *fVec5;
	float 	fRec32[2];
	bool mem_allocated;
	void mem_alloc();
	void mem_free();
	void clear_state_f();
	int activate(bool start);
	int load_ui_f(const UiBuilder& b, int form);
	static const char *glade_def;
	void init(unsigned int samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static int activate_static(bool start, PluginDef*);
	static int load_ui_f_static(const UiBuilder& b, int form);
	static void init_static(unsigned int samplingFreq, PluginDef*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginDef*);
	static int register_params_static(const ParamReg& reg);
	static void del_instance(PluginDef *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginDef(),
	  fVec2(0),
	  fVec5(0),
	  mem_allocated(false) {
	version = PLUGINDEF_VERSION;
	flags = 0;
	id = "didest";
	name = N_("Digital Stereo Delay");
	groups = 0;
	description = N_("Digital Delay Stereo Version"); // description (tooltip)
	category = N_("Echo / Delay");       // category
	shortname = N_("Digi Delay S");     // shortname
	mono_audio = 0;
	stereo_audio = compute_static;
	set_samplerate = init_static;
	activate_plugin = activate_static;
	register_params = register_params_static;
	load_ui = load_ui_f_static;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<3; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<3; i++) fRec10[i] = 0;
	for (int i=0; i<3; i++) fRec9[i] = 0;
	for (int i=0; i<3; i++) fRec8[i] = 0;
	for (int i=0; i<3; i++) fRec7[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<3; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<524288; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec28[i] = 0;
	for (int i=0; i<2; i++) fRec29[i] = 0;
	for (int i=0; i<2; i++) fRec30[i] = 0;
	for (int i=0; i<2; i++) fRec31[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<3; i++) fRec34[i] = 0;
	for (int i=0; i<3; i++) fRec33[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec43[i] = 0;
	for (int i=0; i<3; i++) fRec42[i] = 0;
	for (int i=0; i<3; i++) fRec41[i] = 0;
	for (int i=0; i<3; i++) fRec40[i] = 0;
	for (int i=0; i<3; i++) fRec39[i] = 0;
	for (int i=0; i<3; i++) fRec38[i] = 0;
	for (int i=0; i<3; i++) fRec37[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec36[i] = 0;
	for (int i=0; i<3; i++) fRec35[i] = 0;
	for (int i=0; i<2; i++) fRec50[i] = 0;
	for (int i=0; i<2; i++) fRec48[i] = 0;
	for (int i=0; i<2; i++) fRec46[i] = 0;
	for (int i=0; i<2; i++) fRec44[i] = 0;
	for (int i=0; i<2; i++) fRec58[i] = 0;
	for (int i=0; i<2; i++) fRec56[i] = 0;
	for (int i=0; i<2; i++) fRec54[i] = 0;
	for (int i=0; i<2; i++) fRec52[i] = 0;
	for (int i=0; i<524288; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec32[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (3.141592653589793f / float(iConst0));
	fConst2 = tanf((37699.11184307752f / float(iConst0)));
	fConst3 = (2 * (1 - (1.0f / faustpower<2>(fConst2))));
	fConst4 = (1.0f / fConst2);
	fConst5 = (1 + ((fConst4 - 1.0000000000000004f) / fConst2));
	fConst6 = (1 + ((1.0000000000000004f + fConst4) / fConst2));
	fConst7 = (1.0f / fConst6);
	fConst8 = tanf((25132.741228718343f / float(iConst0)));
	fConst9 = (2 * (1 - (1.0f / faustpower<2>(fConst8))));
	fConst10 = float((1.0f / float(iConst0)));
	fConst11 = (fConst10 / sinf((50265.48245743669f * fConst10)));
	fConst12 = (3141.592653589793f * fConst11);
	fConst13 = (1.0f / fConst8);
	fConst14 = (1 + ((fConst13 - fConst12) / fConst8));
	fConst15 = (1 + ((fConst12 + fConst13) / fConst8));
	fConst16 = (1.0f / fConst15);
	fConst17 = tanf((12566.370614359172f / float(iConst0)));
	fConst18 = (2 * (1 - (1.0f / faustpower<2>(fConst17))));
	fConst19 = (fConst10 / sinf((25132.741228718343f * fConst10)));
	fConst20 = (6268.301430690795f * fConst19);
	fConst21 = (1.0f / fConst17);
	fConst22 = (1 + ((fConst21 - fConst20) / fConst17));
	fConst23 = (1.0f / (1 + ((fConst20 + fConst21) / fConst17)));
	fConst24 = tanf((6283.185307179586f / float(iConst0)));
	fConst25 = (2 * (1 - (1.0f / faustpower<2>(fConst24))));
	fConst26 = (fConst10 / sinf((12566.370614359172f * fConst10)));
	fConst27 = (1570.7963267948965f * fConst26);
	fConst28 = (1.0f / fConst24);
	fConst29 = (1 + ((fConst28 - fConst27) / fConst24));
	fConst30 = (1.0f / (1 + ((fConst27 + fConst28) / fConst24)));
	fConst31 = tanf((1178.0972450961724f / float(iConst0)));
	fConst32 = (2 * (1 - (1.0f / faustpower<2>(fConst31))));
	fConst33 = (fConst10 / sinf((2356.194490192345f * fConst10)));
	fConst34 = (392.6990816987241f * fConst33);
	fConst35 = (1.0f / fConst31);
	fConst36 = (1 + ((fConst35 - fConst34) / fConst31));
	fConst37 = (1.0f / (1 + ((fConst34 + fConst35) / fConst31)));
	fConst38 = tanf((628.3185307179587f / float(iConst0)));
	fConst39 = (2 * (1 - (1.0f / faustpower<2>(fConst38))));
	fConst40 = (fConst10 / sinf((1256.6370614359173f * fConst10)));
	fConst41 = (221.8808786553305f * fConst40);
	fConst42 = (1.0f / fConst38);
	fConst43 = (1 + ((fConst42 - fConst41) / fConst38));
	fConst44 = (1.0f / (1 + ((fConst41 + fConst42) / fConst38)));
	fConst45 = tanf((251.32741228718345f / float(iConst0)));
	fConst46 = (1.0f / faustpower<2>(fConst45));
	fConst47 = (2 * (1 - fConst46));
	fConst48 = (1.0f / fConst45);
	fConst49 = (1 + ((fConst48 - 1.0000000000000004f) / fConst45));
	fConst50 = (1.0f / (1 + ((1.0000000000000004f + fConst48) / fConst45)));
	fConst51 = (0 - fConst48);
	fConst52 = (1 + fConst48);
	fConst53 = (1.0f / fConst52);
	fConst54 = (0 - ((1 - fConst48) / fConst52));
	fConst55 = (2 * (0 - fConst46));
	fConst56 = (157.07963267948966f * fConst40);
	fConst57 = (1 + ((fConst42 - fConst56) / fConst38));
	fConst58 = (1 + ((fConst56 + fConst42) / fConst38));
	fConst59 = (466.72373331140534f * fConst33);
	fConst60 = (1 + ((fConst35 - fConst59) / fConst31));
	fConst61 = (1 + ((fConst59 + fConst35) / fConst31));
	fConst62 = (2218.808786553305f * fConst26);
	fConst63 = (1 + ((fConst28 - fConst62) / fConst24));
	fConst64 = (1 + ((fConst62 + fConst28) / fConst24));
	fConst65 = (3141.592653589793f * fConst19);
	fConst66 = (1 + ((fConst21 - fConst65) / fConst17));
	fConst67 = (1 + ((fConst65 + fConst21) / fConst17));
	fConst68 = (3955.030825110061f * fConst11);
	fConst69 = (1 + ((fConst13 - fConst68) / fConst8));
	fConst70 = (1 + ((fConst68 + fConst13) / fConst8));
	fConst71 = (1 + fConst4);
	fConst72 = (1.0f / (fConst71 * fConst15));
	fConst73 = (0 - ((1 - fConst4) / fConst71));
	fConst74 = (0.8f / fConst6);
	IOTA = 0;
	fConst75 = (1e+01f / float(iConst0));
	fConst76 = (0 - fConst75);
	iConst77 = (60 * iConst0);
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void Dsp::mem_alloc()
{
	if (!fVec2) fVec2 = new float[524288];
	if (!fVec5) fVec5 = new float[524288];
	mem_allocated = true;
}

void Dsp::mem_free()
{
	mem_allocated = false;
	if (fVec2) { delete fVec2; fVec2 = 0; }
	if (fVec5) { delete fVec5; fVec5 = 0; }
}

int Dsp::activate(bool start)
{
	if (start) {
		if (!mem_allocated) {
			mem_alloc();
			clear_state_f();
		}
	} else if (mem_allocated) {
		mem_free();
	}
	return 0;
}

int Dsp::activate_static(bool start, PluginDef *p)
{
	return static_cast<Dsp*>(p)->activate(start);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
	float 	fSlow0 = float(fslider0);
	float 	fSlow1 = (1.0f - fSlow0);
	float 	fSlow2 = tanf((fConst1 * float(fslider1)));
	float 	fSlow3 = (2 * (1 - (1.0f / faustpower<2>(fSlow2))));
	float 	fSlow4 = (1.0f / fSlow2);
	float 	fSlow5 = (1 + ((fSlow4 - 1.414213562373095f) / fSlow2));
	float 	fSlow6 = (1 + ((1.414213562373095f + fSlow4) / fSlow2));
	float 	fSlow7 = (1.0f / fSlow6);
	float 	fSlow8 = tanf((fConst1 * float(fslider2)));
	float 	fSlow9 = (1.0f / faustpower<2>(fSlow8));
	float 	fSlow10 = (2 * (1 - fSlow9));
	float 	fSlow11 = (1.0f / fSlow8);
	float 	fSlow12 = (1 + ((fSlow11 - 1.414213562373095f) / fSlow8));
	float 	fSlow13 = (1.0f / (1 + ((1.414213562373095f + fSlow11) / fSlow8)));
	float 	fSlow14 = (0.01f * float(fslider3));
	float 	fSlow15 = (2 * (0 - fSlow9));
	float 	fSlow16 = (fConst48 / fSlow6);
	float 	fSlow17 = float(fslider4);
	int 	iSlow18 = int(min((float)2, max((float)0, fSlow17)));
	int 	iSlow19 = int(min((float)2, max((float)0, (fSlow17 - 1))));
	int 	iSlow20 = int(min((float)2, max((float)0, (fSlow17 - 2))));
	int 	iSlow21 = int(fSlow0);
	float 	fSlow22 = min(524288.0f, B2N(float(fslider5), (float(iConst77) / float(fslider6))));
	float 	fSlow23 = (0.01f * float(fslider7));
	float 	fSlow24 = (0.01f * float(fslider8));
	for (int i=0; i<count; i++) {
		float fTemp0 = (float)input0[i];
		fRec2[0] = ((fSlow14 * fRec0[1]) - (fSlow13 * ((fSlow12 * fRec2[2]) + (fSlow10 * fRec2[1]))));
		fRec1[0] = ((fSlow13 * (((fSlow9 * fRec2[0]) + (fSlow15 * fRec2[1])) + (fSlow9 * fRec2[2]))) - (fSlow7 * ((fSlow5 * fRec1[2]) + (fSlow3 * fRec1[1]))));
		float fTemp1 = (fRec1[2] + (fRec1[0] + (2 * fRec1[1])));
		float fTemp2 = (fSlow7 * fTemp1);
		fVec0[0] = fTemp2;
		float fTemp3 = (fConst9 * fRec5[1]);
		float fTemp4 = (fConst18 * fRec6[1]);
		float fTemp5 = (fConst25 * fRec7[1]);
		float fTemp6 = (fConst32 * fRec8[1]);
		float fTemp7 = (fConst39 * fRec9[1]);
		fRec11[0] = ((fConst54 * fRec11[1]) + (fConst53 * ((fSlow16 * fTemp1) + (fConst51 * fVec0[1]))));
		fRec10[0] = (fRec11[0] - (fConst50 * ((fConst49 * fRec10[2]) + (fConst47 * fRec10[1]))));
		fRec9[0] = ((fConst50 * (((fConst46 * fRec10[0]) + (fConst55 * fRec10[1])) + (fConst46 * fRec10[2]))) - (fConst44 * ((fConst43 * fRec9[2]) + fTemp7)));
		fRec8[0] = ((fConst44 * ((fTemp7 + (fConst58 * fRec9[0])) + (fConst57 * fRec9[2]))) - (fConst37 * ((fConst36 * fRec8[2]) + fTemp6)));
		fRec7[0] = ((fConst37 * ((fTemp6 + (fConst61 * fRec8[0])) + (fConst60 * fRec8[2]))) - (fConst30 * ((fConst29 * fRec7[2]) + fTemp5)));
		fRec6[0] = ((fConst30 * ((fTemp5 + (fConst64 * fRec7[0])) + (fConst63 * fRec7[2]))) - (fConst23 * ((fConst22 * fRec6[2]) + fTemp4)));
		fRec5[0] = ((fConst23 * ((fTemp4 + (fConst67 * fRec6[0])) + (fConst66 * fRec6[2]))) - (fConst16 * ((fConst14 * fRec5[2]) + fTemp3)));
		float fTemp8 = ((fTemp3 + (fConst70 * fRec5[0])) + (fConst69 * fRec5[2]));
		fVec1[0] = fTemp8;
		fRec4[0] = ((fConst73 * fRec4[1]) + (fConst72 * (fVec1[0] + fVec1[1])));
		fRec3[0] = (fRec4[0] - (fConst7 * ((fConst5 * fRec3[2]) + (fConst3 * fRec3[1]))));
		float fTemp9 = ((iSlow18==0)? fVec0[0] : ((iSlow18==1)?(fConst74 * (fRec3[2] + (fRec3[0] + (2 * fRec3[1])))):fVec0[0]) );
		float fTemp10 = (0.1f * fRec12[1]);
		float fTemp11 = ((0.4f * fRec16[1]) + fTemp10);
		float fTemp12 = (0.2f * fRec14[1]);
		float fTemp13 = ((fTemp12 + (fTemp9 + (0.6f * fRec18[1]))) - fTemp11);
		fRec18[0] = fTemp13;
		float 	fRec19 = (0 - (0.6f * fTemp13));
		fRec16[0] = (fRec19 + fRec18[1]);
		float fTemp14 = (fTemp9 + fTemp12);
		float 	fRec17 = (0.4f * (fTemp14 - fTemp11));
		fRec14[0] = (fRec17 + fRec16[1]);
		float 	fRec15 = (0 - (0.2f * (fTemp14 - fTemp10)));
		fRec12[0] = (fRec15 + fRec14[1]);
		float 	fRec13 = (0.1f * (fTemp9 - fTemp10));
		float fTemp15 = ((iSlow19==0)? fTemp9 : ((iSlow19==1)?(fRec13 + fRec12[1]):fTemp9) );
		float fTemp16 = (0.5f * fRec20[1]);
		float fTemp17 = ((0.4f * fRec22[1]) + fTemp16);
		float fTemp18 = (0.3f * fRec24[1]);
		float fTemp19 = ((fTemp18 + (fTemp15 + (0.2f * fRec26[1]))) - fTemp17);
		fRec26[0] = fTemp19;
		float 	fRec27 = (0 - (0.2f * fTemp19));
		fRec24[0] = (fRec27 + fRec26[1]);
		float 	fRec25 = (0 - (0.3f * ((fTemp15 + fTemp18) - fTemp17)));
		fRec22[0] = (fRec25 + fRec24[1]);
		float 	fRec23 = (0.4f * (fTemp15 - fTemp17));
		fRec20[0] = (fRec23 + fRec22[1]);
		float 	fRec21 = (0.5f * (fTemp15 - fTemp16));
		float fTemp20 = (((iSlow21)?fRec0[1]:((iSlow20==0)? fTemp15 : ((iSlow20==1)?(fRec21 + fRec20[1]):fTemp15) )) + (fSlow1 * fTemp0));
		fVec2[IOTA&524287] = fTemp20;
		float fTemp21 = ((int((fRec28[1] != 0.0f)))?((int(((fRec29[1] > 0.0f) & (fRec29[1] < 1.0f))))?fRec28[1]:0):((int(((fRec29[1] == 0.0f) & (fSlow22 != fRec30[1]))))?fConst75:((int(((fRec29[1] == 1.0f) & (fSlow22 != fRec31[1]))))?fConst76:0)));
		fRec28[0] = fTemp21;
		fRec29[0] = max(0.0f, min(1.0f, (fRec29[1] + fTemp21)));
		fRec30[0] = ((int(((fRec29[1] >= 1.0f) & (fRec31[1] != fSlow22))))?fSlow22:fRec30[1]);
		fRec31[0] = ((int(((fRec29[1] <= 0.0f) & (fRec30[1] != fSlow22))))?fSlow22:fRec31[1]);
		int iTemp22 = int((int(fRec31[0]) & 524287));
		int iTemp23 = int((int(fRec30[0]) & 524287));
		float fTemp24 = (1.0f - fRec29[0]);
		float fTemp25 = ((fTemp24 * fVec2[(IOTA-iTemp23)&524287]) + (fRec29[0] * fVec2[(IOTA-iTemp22)&524287]));
		fRec0[0] = ((iSlow21)?fTemp25:(fSlow23 * fTemp25));
		output0[i] = (FAUSTFLOAT)(fTemp0 + (fSlow24 * fRec0[0]));
		float fTemp26 = (float)input1[i];
		fRec34[0] = ((fSlow14 * fRec32[1]) - (fSlow13 * ((fSlow12 * fRec34[2]) + (fSlow10 * fRec34[1]))));
		fRec33[0] = ((fSlow13 * (((fSlow9 * fRec34[0]) + (fSlow15 * fRec34[1])) + (fSlow9 * fRec34[2]))) - (fSlow7 * ((fSlow5 * fRec33[2]) + (fSlow3 * fRec33[1]))));
		float fTemp27 = (fRec33[2] + (fRec33[0] + (2 * fRec33[1])));
		float fTemp28 = (fSlow7 * fTemp27);
		fVec3[0] = fTemp28;
		float fTemp29 = (fConst9 * fRec37[1]);
		float fTemp30 = (fConst18 * fRec38[1]);
		float fTemp31 = (fConst25 * fRec39[1]);
		float fTemp32 = (fConst32 * fRec40[1]);
		float fTemp33 = (fConst39 * fRec41[1]);
		fRec43[0] = ((fConst54 * fRec43[1]) + (fConst53 * ((fSlow16 * fTemp27) + (fConst51 * fVec3[1]))));
		fRec42[0] = (fRec43[0] - (fConst50 * ((fConst49 * fRec42[2]) + (fConst47 * fRec42[1]))));
		fRec41[0] = ((fConst50 * (((fConst46 * fRec42[0]) + (fConst55 * fRec42[1])) + (fConst46 * fRec42[2]))) - (fConst44 * ((fConst43 * fRec41[2]) + fTemp33)));
		fRec40[0] = ((fConst44 * ((fTemp33 + (fConst58 * fRec41[0])) + (fConst57 * fRec41[2]))) - (fConst37 * ((fConst36 * fRec40[2]) + fTemp32)));
		fRec39[0] = ((fConst37 * ((fTemp32 + (fConst61 * fRec40[0])) + (fConst60 * fRec40[2]))) - (fConst30 * ((fConst29 * fRec39[2]) + fTemp31)));
		fRec38[0] = ((fConst30 * ((fTemp31 + (fConst64 * fRec39[0])) + (fConst63 * fRec39[2]))) - (fConst23 * ((fConst22 * fRec38[2]) + fTemp30)));
		fRec37[0] = ((fConst23 * ((fTemp30 + (fConst67 * fRec38[0])) + (fConst66 * fRec38[2]))) - (fConst16 * ((fConst14 * fRec37[2]) + fTemp29)));
		float fTemp34 = ((fTemp29 + (fConst70 * fRec37[0])) + (fConst69 * fRec37[2]));
		fVec4[0] = fTemp34;
		fRec36[0] = ((fConst73 * fRec36[1]) + (fConst72 * (fVec4[0] + fVec4[1])));
		fRec35[0] = (fRec36[0] - (fConst7 * ((fConst5 * fRec35[2]) + (fConst3 * fRec35[1]))));
		float fTemp35 = ((iSlow18==0)? fVec3[0] : ((iSlow18==1)?(fConst74 * (fRec35[2] + (fRec35[0] + (2 * fRec35[1])))):fVec3[0]) );
		float fTemp36 = (0.1f * fRec44[1]);
		float fTemp37 = ((0.4f * fRec48[1]) + fTemp36);
		float fTemp38 = (0.2f * fRec46[1]);
		float fTemp39 = ((fTemp38 + (fTemp35 + (0.6f * fRec50[1]))) - fTemp37);
		fRec50[0] = fTemp39;
		float 	fRec51 = (0 - (0.6f * fTemp39));
		fRec48[0] = (fRec51 + fRec50[1]);
		float fTemp40 = (fTemp35 + fTemp38);
		float 	fRec49 = (0.4f * (fTemp40 - fTemp37));
		fRec46[0] = (fRec49 + fRec48[1]);
		float 	fRec47 = (0 - (0.2f * (fTemp40 - fTemp36)));
		fRec44[0] = (fRec47 + fRec46[1]);
		float 	fRec45 = (0.1f * (fTemp35 - fTemp36));
		float fTemp41 = ((iSlow19==0)? fTemp35 : ((iSlow19==1)?(fRec45 + fRec44[1]):fTemp35) );
		float fTemp42 = (0.5f * fRec52[1]);
		float fTemp43 = ((0.4f * fRec54[1]) + fTemp42);
		float fTemp44 = (0.3f * fRec56[1]);
		float fTemp45 = ((fTemp44 + (fTemp41 + (0.2f * fRec58[1]))) - fTemp43);
		fRec58[0] = fTemp45;
		float 	fRec59 = (0 - (0.2f * fTemp45));
		fRec56[0] = (fRec59 + fRec58[1]);
		float 	fRec57 = (0 - (0.3f * ((fTemp41 + fTemp44) - fTemp43)));
		fRec54[0] = (fRec57 + fRec56[1]);
		float 	fRec55 = (0.4f * (fTemp41 - fTemp43));
		fRec52[0] = (fRec55 + fRec54[1]);
		float 	fRec53 = (0.5f * (fTemp41 - fTemp42));
		float fTemp46 = (((iSlow21)?fRec32[1]:((iSlow20==0)? fTemp41 : ((iSlow20==1)?(fRec53 + fRec52[1]):fTemp41) )) + (fSlow1 * fTemp26));
		fVec5[IOTA&524287] = fTemp46;
		float fTemp47 = ((fTemp24 * fVec5[(IOTA-iTemp23)&524287]) + (fRec29[0] * fVec5[(IOTA-iTemp22)&524287]));
		fRec32[0] = ((iSlow21)?fTemp47:(fSlow23 * fTemp47));
		output1[i] = (FAUSTFLOAT)(fTemp26 + (fSlow24 * fRec32[0]));
		// post processing
		fRec32[1] = fRec32[0];
		fRec52[1] = fRec52[0];
		fRec54[1] = fRec54[0];
		fRec56[1] = fRec56[0];
		fRec58[1] = fRec58[0];
		fRec44[1] = fRec44[0];
		fRec46[1] = fRec46[0];
		fRec48[1] = fRec48[0];
		fRec50[1] = fRec50[0];
		fRec35[2] = fRec35[1]; fRec35[1] = fRec35[0];
		fRec36[1] = fRec36[0];
		fVec4[1] = fVec4[0];
		fRec37[2] = fRec37[1]; fRec37[1] = fRec37[0];
		fRec38[2] = fRec38[1]; fRec38[1] = fRec38[0];
		fRec39[2] = fRec39[1]; fRec39[1] = fRec39[0];
		fRec40[2] = fRec40[1]; fRec40[1] = fRec40[0];
		fRec41[2] = fRec41[1]; fRec41[1] = fRec41[0];
		fRec42[2] = fRec42[1]; fRec42[1] = fRec42[0];
		fRec43[1] = fRec43[0];
		fVec3[1] = fVec3[0];
		fRec33[2] = fRec33[1]; fRec33[1] = fRec33[0];
		fRec34[2] = fRec34[1]; fRec34[1] = fRec34[0];
		fRec0[1] = fRec0[0];
		fRec31[1] = fRec31[0];
		fRec30[1] = fRec30[0];
		fRec29[1] = fRec29[0];
		fRec28[1] = fRec28[0];
		IOTA = IOTA+1;
		fRec20[1] = fRec20[0];
		fRec22[1] = fRec22[0];
		fRec24[1] = fRec24[0];
		fRec26[1] = fRec26[0];
		fRec12[1] = fRec12[0];
		fRec14[1] = fRec14[0];
		fRec16[1] = fRec16[0];
		fRec18[1] = fRec18[0];
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fVec1[1] = fVec1[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
		fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		fVec0[1] = fVec0[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("didest.Freeze","","S",N_("Freeze the current delay"),&fslider0, 0.0f, 0.0f, 1.0f, 1.0f);
	reg.registerVar("didest.bpm",N_("BPM"),"S",N_("Delay in Beats per Minute"),&fslider6, 1.2e+02f, 24.0f, 3.6e+02f, 1.0f);
	reg.registerVar("didest.feedback",N_("Feedback"),"S",N_("Percentage of the feedback level in the delay loop"),&fslider3, 5e+01f, 1.0f, 1e+02f, 1.0f);
	reg.registerVar("didest.gain",N_("Gain"),"S",N_("Overall gain of the delay line in percent"),&fslider8, 1e+02f, 0.0f, 1.2e+02f, 1.0f);
	reg.registerVar("didest.highpass",N_("Hipass"),"S",N_("Highpass filter frequency in the feddback loop"),&fslider2, 1.2e+02f, 2e+01f, 2e+04f, 1.0f);
	reg.registerVar("didest.howpass",N_("Lopass"),"S",N_("Lowpass filter frequency in the feddback loop"),&fslider1, 1.2e+04f, 2e+01f, 2e+04f, 1.0f);
	reg.registerVar("didest.level",N_("Level"),"S",N_("Percentage of the delay gain level"),&fslider7, 5e+01f, 1.0f, 1e+02f, 1.0f);
	static const value_pair fslider4_values[] = {{"plain"},{"presence"},{"tape"},{"tape2"},{0}};
	reg.registerEnumVar("didest.mode",N_("Mode"),"S","",fslider4_values,&fslider4, 0.0f, 0.0f, 3.0f, 1.0f);
	static const value_pair fslider5_values[] = {{"Dotted 1/2 note"},{"1/2 note"},{"1/2 note triplets"},{" Dotted 1/4 note"},{"1/4 note"},{"1/4 note triplets"},{"Dotted 1/8 note"},{"1/8 note"},{"1/8 note triplets"},{" Dotted 1/16 note"},{"1/16 note"},{"1/16 note triplets"},{"Dotted 1/32 note"},{"1/32 note"},{"1/32 note triplets"},{" Dotted 1/64 note"},{"1/64 note"},{"1/64 note triplets"},{0}};
	reg.registerEnumVar("didest.notes",N_("Notes"),"S",N_("Note setting for bpm"),fslider5_values,&fslider5, 4.0f, 0.0f, 17.0f, 1.0f);
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
            <child>\n\
              <object class=\"GtkVBox\" id=\"vbox2\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">False</property>\n\
                <child>\n\
                  <object class=\"GtkLabel\" id=\"label1\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">False</property>\n\
                    <property name=\"fill\">False</property>\n\
                    <property name=\"position\">0</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkLabel\" id=\"label1:rack_label\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"label\" translatable=\"yes\">label</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">False</property>\n\
                    <property name=\"fill\">False</property>\n\
                    <property name=\"position\">1</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxMidKnob\" id=\"GxMidKnob1\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"var_id\">didest.bpm</property>\n\
                    <property name=\"label_ref\">label1:rack_label</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">True</property>\n\
                    <property name=\"fill\">True</property>\n\
                    <property name=\"position\">2</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkLabel\" id=\"label2\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">False</property>\n\
                    <property name=\"fill\">False</property>\n\
                    <property name=\"position\">3</property>\n\
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
              <object class=\"GtkVBox\" id=\"vbox8\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">False</property>\n\
                <property name=\"spacing\">10</property>\n\
                <child>\n\
                  <object class=\"GtkHBox\" id=\"hbox1\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
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
                          <object class=\"GxSmallKnobR\" id=\"GxMidKnob2\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">True</property>\n\
                            <property name=\"receives_default\">True</property>\n\
                            <property name=\"var_id\">didest.feedback</property>\n\
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
                        <property name=\"expand\">True</property>\n\
                        <property name=\"fill\">True</property>\n\
                        <property name=\"position\">0</property>\n\
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
                          <object class=\"GxSmallKnobR\" id=\"GxMidKnob3\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">True</property>\n\
                            <property name=\"receives_default\">True</property>\n\
                            <property name=\"var_id\">didest.level</property>\n\
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
                        <property name=\"expand\">True</property>\n\
                        <property name=\"fill\">True</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GtkVBox\" id=\"vbox5\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <child>\n\
                          <object class=\"GtkLabel\" id=\"label4:rack_label\">\n\
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
                          <object class=\"GxSmallKnobR\" id=\"GxMidKnob4\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">True</property>\n\
                            <property name=\"receives_default\">True</property>\n\
                            <property name=\"var_id\">didest.highpass</property>\n\
                            <property name=\"label_ref\">label4:rack_label</property>\n\
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
                        <property name=\"position\">2</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GtkVBox\" id=\"vbox6\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <child>\n\
                          <object class=\"GtkLabel\" id=\"label5:rack_label\">\n\
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
                          <object class=\"GxSmallKnobR\" id=\"GxMidKnob5\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">True</property>\n\
                            <property name=\"receives_default\">True</property>\n\
                            <property name=\"var_id\">didest.howpass</property>\n\
                            <property name=\"label_ref\">label5:rack_label</property>\n\
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
                        <property name=\"position\">3</property>\n\
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
                  <object class=\"GtkTable\" id=\"table1\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"n_rows\">2</property>\n\
                    <property name=\"n_columns\">4</property>\n\
                    <property name=\"column_spacing\">6</property>\n\
                    <property name=\"row_spacing\">3</property>\n\
                    <child>\n\
                      <object class=\"GxSelector\" id=\"gxselector2\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">didest.mode</property>\n\
                        <property name=\"label_ref\">label21:rack_label_inverse</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"left_attach\">1</property>\n\
                        <property name=\"right_attach\">2</property>\n\
                        <property name=\"top_attach\">1</property>\n\
                        <property name=\"bottom_attach\">2</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label11:rack_label_inverse\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"xalign\">1</property>\n\
                        <property name=\"label\" translatable=\"yes\">label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"x_options\">GTK_FILL</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label21:rack_label_inverse\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"xalign\">1</property>\n\
                        <property name=\"label\" translatable=\"yes\">label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"top_attach\">1</property>\n\
                        <property name=\"bottom_attach\">2</property>\n\
                        <property name=\"x_options\">GTK_FILL</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSelector\" id=\"gxselector1\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">didest.notes</property>\n\
                        <property name=\"label_ref\">label11:rack_label_inverse</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"left_attach\">1</property>\n\
                        <property name=\"right_attach\">4</property>\n\
                        <property name=\"x_options\">GTK_FILL</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label31:rack_label_inverse\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"xalign\">1</property>\n\
                        <property name=\"label\" translatable=\"yes\">label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"left_attach\">2</property>\n\
                        <property name=\"right_attach\">3</property>\n\
                        <property name=\"top_attach\">1</property>\n\
                        <property name=\"bottom_attach\">2</property>\n\
                        <property name=\"x_options\">GTK_FILL</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSwitch\" id=\"gxswitch1\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"use_action_appearance\">False</property>\n\
                        <property name=\"use_stock\">True</property>\n\
                        <property name=\"var_id\">didest.Freeze</property>\n\
                        <property name=\"label_ref\">label31:rack_label_inverse</property>\n\
                        <property name=\"base_name\">frbutton</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"left_attach\">3</property>\n\
                        <property name=\"right_attach\">4</property>\n\
                        <property name=\"top_attach\">1</property>\n\
                        <property name=\"bottom_attach\">2</property>\n\
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
                <property name=\"fill\">True</property>\n\
                <property name=\"position\">1</property>\n\
              </packing>\n\
            </child>\n\
            <child>\n\
              <object class=\"GtkVBox\" id=\"vbox7\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">False</property>\n\
                <child>\n\
                  <object class=\"GtkLabel\" id=\"label6:rack_label1\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">False</property>\n\
                    <property name=\"fill\">False</property>\n\
                    <property name=\"position\">0</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkLabel\" id=\"label6:rack_label\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"label\" translatable=\"yes\">label</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">False</property>\n\
                    <property name=\"fill\">False</property>\n\
                    <property name=\"position\">1</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxMidKnob\" id=\"GxMidKnob6\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"var_id\">didest.gain</property>\n\
                    <property name=\"label_ref\">label6:rack_label</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">True</property>\n\
                    <property name=\"fill\">True</property>\n\
                    <property name=\"position\">2</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkLabel\" id=\"label6:rack_label2\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">False</property>\n\
                    <property name=\"fill\">False</property>\n\
                    <property name=\"position\">3</property>\n\
                  </packing>\n\
                </child>\n\
              </object>\n\
              <packing>\n\
                <property name=\"expand\">True</property>\n\
                <property name=\"fill\">True</property>\n\
                <property name=\"position\">2</property>\n\
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
                <property name=\"var_id\">didest.gain</property>\n\
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
                <property name=\"label\" translatable=\"yes\">Amount</property>\n\
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
#define PARAM(p) ("didest" "." p)
// -----delay
b.openHorizontalhideBox("");
b.create_master_slider(PARAM("bpm"), _(" delay (bpm)"));
b.closeBox();
b.openVerticalBox("");
{
    b.openHorizontalBox("");
    {
	b.openVerticalBox("");
        {
            b.create_selector(PARAM("notes"), "tact");
            b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_TOP);
            b.create_small_rackknob(PARAM("bpm"), _(" delay (bpm)"));
        }
        b.closeBox();
	b.openVerticalBox("");
        {
            b.openHorizontalBox("");
            b.openFrameBox("");
            b.closeBox();
            b.create_selector(PARAM("mode"), "mode");
            b.closeBox();
            b.openHorizontalBox("");
            {
                b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_TOP);
                b.create_small_rackknob(PARAM("highpass"), _("highpass (hz)"));
                b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_TOP);
                b.create_small_rackknob(PARAM("howpass"), _("lowpass (hz)"));
            }
            b.closeBox();
        }
        b.closeBox();
        b.openVerticalBox("");
        {
            b.create_small_rackknob(PARAM("level"), _("level"));
            b.create_small_rackknob(PARAM("feedback"), _("feedback"));
        }
        b.closeBox();
        b.openVerticalBox("");
        {
            b.create_small_rackknobr(PARAM("gain"), _("amount"));
            b.openFrameBox("");
            b.closeBox();
            b.create_switch(sw_rbutton,PARAM("Freeze"), _("freeze"));
        }
        b.closeBox();
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

} // end namespace digital_delay_st
