// generated from file '../src/faust/digital_delay.dsp' by dsp2cc:
// Code generated with Faust 0.9.58 (http://faust.grame.fr)

#include "beat.h"

namespace digital_delay {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	int 	iConst0;
	float 	fConst1;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT 	fslider2;
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
	float 	fConst55;
	float 	fConst56;
	float 	fRec11[2];
	float 	fRec10[3];
	float 	fConst57;
	float 	fRec9[3];
	float 	fConst58;
	float 	fConst59;
	float 	fConst60;
	float 	fRec8[3];
	float 	fConst61;
	float 	fConst62;
	float 	fConst63;
	float 	fRec7[3];
	float 	fConst64;
	float 	fConst65;
	float 	fConst66;
	float 	fRec6[3];
	float 	fConst67;
	float 	fConst68;
	float 	fConst69;
	float 	fRec5[3];
	float 	fConst70;
	float 	fConst71;
	float 	fConst72;
	float 	fVec1[2];
	float 	fConst73;
	float 	fRec4[2];
	float 	fRec3[3];
	float 	fConst74;
	FAUSTFLOAT 	fslider3;
	float 	fRec18[2];
	float 	fRec16[2];
	float 	fRec14[2];
	float 	fRec12[2];
	float 	fRec26[2];
	float 	fRec24[2];
	float 	fRec22[2];
	float 	fRec20[2];
	FAUSTFLOAT 	fslider4;
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
	bool mem_allocated;
	void mem_alloc();
	void mem_free();
	void clear_state_f();
	int activate(bool start);
	int load_ui_f(const UiBuilder& b, int form);
	void init(unsigned int samplingFreq);
	void compute(int count, float *input0, float *output0);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static int activate_static(bool start, PluginDef*);
	static int load_ui_f_static(const UiBuilder& b, int form);
	static void init_static(unsigned int samplingFreq, PluginDef*);
	static void compute_static(int count, float *input0, float *output0, PluginDef*);
	static int register_params_static(const ParamReg& reg);
	static void del_instance(PluginDef *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginDef(),
	  fVec2(0),
	  mem_allocated(false) {
	version = PLUGINDEF_VERSION;
	flags = 0;
	id = "dide";
	name = N_("Digital Delay");
	groups = 0;
	description = N_("Digital Delay"); // description (tooltip)
	category = N_("Echo / Delay");       // category
	shortname = "";     // shortname
	mono_audio = compute_static;
	stereo_audio = 0;
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
	fConst8 = (1 + fConst4);
	fConst9 = (0 - ((1 - fConst4) / fConst8));
	fConst10 = tanf((25132.741228718343f / float(iConst0)));
	fConst11 = (2 * (1 - (1.0f / faustpower<2>(fConst10))));
	fConst12 = float((1.0f / float(iConst0)));
	fConst13 = (fConst12 / sinf((50265.48245743669f * fConst12)));
	fConst14 = (3141.592653589793f * fConst13);
	fConst15 = (1.0f / fConst10);
	fConst16 = (1 + ((fConst15 - fConst14) / fConst10));
	fConst17 = (1 + ((fConst14 + fConst15) / fConst10));
	fConst18 = (1.0f / fConst17);
	fConst19 = tanf((12566.370614359172f / float(iConst0)));
	fConst20 = (2 * (1 - (1.0f / faustpower<2>(fConst19))));
	fConst21 = (fConst12 / sinf((25132.741228718343f * fConst12)));
	fConst22 = (6268.301430690795f * fConst21);
	fConst23 = (1.0f / fConst19);
	fConst24 = (1 + ((fConst23 - fConst22) / fConst19));
	fConst25 = (1.0f / (1 + ((fConst22 + fConst23) / fConst19)));
	fConst26 = tanf((6283.185307179586f / float(iConst0)));
	fConst27 = (2 * (1 - (1.0f / faustpower<2>(fConst26))));
	fConst28 = (fConst12 / sinf((12566.370614359172f * fConst12)));
	fConst29 = (1570.7963267948965f * fConst28);
	fConst30 = (1.0f / fConst26);
	fConst31 = (1 + ((fConst30 - fConst29) / fConst26));
	fConst32 = (1.0f / (1 + ((fConst29 + fConst30) / fConst26)));
	fConst33 = tanf((1178.0972450961724f / float(iConst0)));
	fConst34 = (2 * (1 - (1.0f / faustpower<2>(fConst33))));
	fConst35 = (fConst12 / sinf((2356.194490192345f * fConst12)));
	fConst36 = (392.6990816987241f * fConst35);
	fConst37 = (1.0f / fConst33);
	fConst38 = (1 + ((fConst37 - fConst36) / fConst33));
	fConst39 = (1.0f / (1 + ((fConst36 + fConst37) / fConst33)));
	fConst40 = tanf((628.3185307179587f / float(iConst0)));
	fConst41 = (2 * (1 - (1.0f / faustpower<2>(fConst40))));
	fConst42 = (fConst12 / sinf((1256.6370614359173f * fConst12)));
	fConst43 = (221.8808786553305f * fConst42);
	fConst44 = (1.0f / fConst40);
	fConst45 = (1 + ((fConst44 - fConst43) / fConst40));
	fConst46 = (1.0f / (1 + ((fConst43 + fConst44) / fConst40)));
	fConst47 = tanf((251.32741228718345f / float(iConst0)));
	fConst48 = (1.0f / faustpower<2>(fConst47));
	fConst49 = (2 * (1 - fConst48));
	fConst50 = (1.0f / fConst47);
	fConst51 = (1 + ((fConst50 - 1.0000000000000004f) / fConst47));
	fConst52 = (1.0f / (1 + ((1.0000000000000004f + fConst50) / fConst47)));
	fConst53 = (1 + fConst50);
	fConst54 = (0 - ((1 - fConst50) / fConst53));
	fConst55 = (0 - fConst50);
	fConst56 = (1.0f / fConst53);
	fConst57 = (2 * (0 - fConst48));
	fConst58 = (157.07963267948966f * fConst42);
	fConst59 = (1 + ((fConst44 - fConst58) / fConst40));
	fConst60 = (1 + ((fConst58 + fConst44) / fConst40));
	fConst61 = (466.72373331140534f * fConst35);
	fConst62 = (1 + ((fConst37 - fConst61) / fConst33));
	fConst63 = (1 + ((fConst61 + fConst37) / fConst33));
	fConst64 = (2218.808786553305f * fConst28);
	fConst65 = (1 + ((fConst30 - fConst64) / fConst26));
	fConst66 = (1 + ((fConst64 + fConst30) / fConst26));
	fConst67 = (3141.592653589793f * fConst21);
	fConst68 = (1 + ((fConst23 - fConst67) / fConst19));
	fConst69 = (1 + ((fConst67 + fConst23) / fConst19));
	fConst70 = (3955.030825110061f * fConst13);
	fConst71 = (1 + ((fConst15 - fConst70) / fConst10));
	fConst72 = (1 + ((fConst70 + fConst15) / fConst10));
	fConst73 = (1.0f / (fConst8 * fConst17));
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
	mem_allocated = true;
}

void Dsp::mem_free()
{
	mem_allocated = false;
	if (fVec2) { delete fVec2; fVec2 = 0; }
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

void always_inline Dsp::compute(int count, float *input0, float *output0)
{
	float 	fSlow0 = tanf((fConst1 * fslider0));
	float 	fSlow1 = (2 * (1 - (1.0f / faustpower<2>(fSlow0))));
	float 	fSlow2 = (1.0f / fSlow0);
	float 	fSlow3 = (1 + ((fSlow2 - 1.414213562373095f) / fSlow0));
	float 	fSlow4 = (1 + ((1.414213562373095f + fSlow2) / fSlow0));
	float 	fSlow5 = (1.0f / fSlow4);
	float 	fSlow6 = tanf((fConst1 * fslider1));
	float 	fSlow7 = (1.0f / faustpower<2>(fSlow6));
	float 	fSlow8 = (2 * (1 - fSlow7));
	float 	fSlow9 = (1.0f / fSlow6);
	float 	fSlow10 = (1 + ((fSlow9 - 1.414213562373095f) / fSlow6));
	float 	fSlow11 = (1.0f / (1 + ((1.414213562373095f + fSlow9) / fSlow6)));
	float 	fSlow12 = (0.01f * fslider2);
	float 	fSlow13 = (2 * (0 - fSlow7));
	float 	fSlow14 = (fConst50 / fSlow4);
	float 	fSlow15 = fslider3;
	int 	iSlow16 = int(min((float)2, max((float)0, fSlow15)));
	int 	iSlow17 = int(min((float)2, max((float)0, (fSlow15 - 1))));
	int 	iSlow18 = int(min((float)2, max((float)0, (fSlow15 - 2))));
	float 	fSlow19 = (0.01f * fslider4);
	float 	fSlow20 = min(524288.0f, B2N(fslider5, (float(iConst77) / fslider6)));
	float 	fSlow21 = (0.01f * fslider7);
	for (int i=0; i<count; i++) {
		fRec2[0] = ((fSlow12 * fRec0[1]) - (fSlow11 * ((fSlow10 * fRec2[2]) + (fSlow8 * fRec2[1]))));
		fRec1[0] = ((fSlow11 * (((fSlow7 * fRec2[0]) + (fSlow13 * fRec2[1])) + (fSlow7 * fRec2[2]))) - (fSlow5 * ((fSlow3 * fRec1[2]) + (fSlow1 * fRec1[1]))));
		float fTemp0 = (fRec1[2] + (fRec1[0] + (2 * fRec1[1])));
		float fTemp1 = (fSlow5 * fTemp0);
		fVec0[0] = fTemp1;
		float fTemp2 = (fConst11 * fRec5[1]);
		float fTemp3 = (fConst20 * fRec6[1]);
		float fTemp4 = (fConst27 * fRec7[1]);
		float fTemp5 = (fConst34 * fRec8[1]);
		float fTemp6 = (fConst41 * fRec9[1]);
		fRec11[0] = ((fConst56 * ((fConst55 * fVec0[1]) + (fSlow14 * fTemp0))) + (fConst54 * fRec11[1]));
		fRec10[0] = (fRec11[0] - (fConst52 * ((fConst51 * fRec10[2]) + (fConst49 * fRec10[1]))));
		fRec9[0] = ((fConst52 * (((fConst48 * fRec10[0]) + (fConst57 * fRec10[1])) + (fConst48 * fRec10[2]))) - (fConst46 * ((fConst45 * fRec9[2]) + fTemp6)));
		fRec8[0] = ((fConst46 * ((fTemp6 + (fConst60 * fRec9[0])) + (fConst59 * fRec9[2]))) - (fConst39 * ((fConst38 * fRec8[2]) + fTemp5)));
		fRec7[0] = ((fConst39 * ((fTemp5 + (fConst63 * fRec8[0])) + (fConst62 * fRec8[2]))) - (fConst32 * ((fConst31 * fRec7[2]) + fTemp4)));
		fRec6[0] = ((fConst32 * ((fTemp4 + (fConst66 * fRec7[0])) + (fConst65 * fRec7[2]))) - (fConst25 * ((fConst24 * fRec6[2]) + fTemp3)));
		fRec5[0] = ((fConst25 * ((fTemp3 + (fConst69 * fRec6[0])) + (fConst68 * fRec6[2]))) - (fConst18 * ((fConst16 * fRec5[2]) + fTemp2)));
		float fTemp7 = ((fTemp2 + (fConst72 * fRec5[0])) + (fConst71 * fRec5[2]));
		fVec1[0] = fTemp7;
		fRec4[0] = ((fConst73 * (fVec1[0] + fVec1[1])) + (fConst9 * fRec4[1]));
		fRec3[0] = (fRec4[0] - (fConst7 * ((fConst5 * fRec3[2]) + (fConst3 * fRec3[1]))));
		float fTemp8 = ((iSlow16==0)? fVec0[0] : ((iSlow16==1)?(fConst74 * (fRec3[2] + (fRec3[0] + (2 * fRec3[1])))):fVec0[0]) );
		float fTemp9 = (0.1f * fRec12[1]);
		float fTemp10 = (fTemp9 + (0.4f * fRec16[1]));
		float fTemp11 = (fTemp8 + (0.2f * fRec14[1]));
		float fTemp12 = ((fTemp11 + (0.6f * fRec18[1])) - fTemp10);
		fRec18[0] = fTemp12;
		float 	fRec19 = (0 - (0.6f * fTemp12));
		fRec16[0] = (fRec19 + fRec18[1]);
		float 	fRec17 = (0.4f * (fTemp11 - fTemp10));
		fRec14[0] = (fRec17 + fRec16[1]);
		float 	fRec15 = (0 - (0.2f * (fTemp11 - fTemp9)));
		fRec12[0] = (fRec15 + fRec14[1]);
		float 	fRec13 = (0.1f * (fTemp8 - fTemp9));
		float fTemp13 = ((iSlow17==0)? fTemp8 : ((iSlow17==1)?(fRec13 + fRec12[1]):fTemp8) );
		float fTemp14 = (0.5f * fRec20[1]);
		float fTemp15 = (fTemp14 + (0.4f * fRec22[1]));
		float fTemp16 = (fTemp13 + (0.3f * fRec24[1]));
		float fTemp17 = ((fTemp16 + (0.2f * fRec26[1])) - fTemp15);
		fRec26[0] = fTemp17;
		float 	fRec27 = (0 - (0.2f * fTemp17));
		fRec24[0] = (fRec27 + fRec26[1]);
		float 	fRec25 = (0 - (0.3f * (fTemp16 - fTemp15)));
		fRec22[0] = (fRec25 + fRec24[1]);
		float 	fRec23 = (0.4f * (fTemp13 - fTemp15));
		fRec20[0] = (fRec23 + fRec22[1]);
		float 	fRec21 = (0.5f * (fTemp13 - fTemp14));
		float fTemp18 = (float)input0[i];
		float fTemp19 = ((fSlow19 * fTemp18) + ((iSlow18==0)? fTemp13 : ((iSlow18==1)?(fRec21 + fRec20[1]):fTemp13) ));
		fVec2[IOTA&524287] = fTemp19;
		float fTemp20 = ((int((fRec28[1] != 0.0f)))?((int(((fRec29[1] > 0.0f) & (fRec29[1] < 1.0f))))?fRec28[1]:0):((int(((fRec29[1] == 0.0f) & (fSlow20 != fRec30[1]))))?fConst75:((int(((fRec29[1] == 1.0f) & (fSlow20 != fRec31[1]))))?fConst76:0)));
		fRec28[0] = fTemp20;
		fRec29[0] = max(0.0f, min(1.0f, (fRec29[1] + fTemp20)));
		fRec30[0] = ((int(((fRec29[1] >= 1.0f) & (fRec31[1] != fSlow20))))?fSlow20:fRec30[1]);
		fRec31[0] = ((int(((fRec29[1] <= 0.0f) & (fRec30[1] != fSlow20))))?fSlow20:fRec31[1]);
		fRec0[0] = (fSlow21 * ((fRec29[0] * fVec2[(IOTA-int((int(fRec31[0]) & 524287)))&524287]) + ((1.0f - fRec29[0]) * fVec2[(IOTA-int((int(fRec30[0]) & 524287)))&524287])));
		output0[i] = (FAUSTFLOAT)(fTemp18 + fRec0[0]);
		// post processing
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

void __rt_func Dsp::compute_static(int count, float *input0, float *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("dide.bpm",N_("delay (bpm)"),"S",N_("Delay in Beats per Minute"),&fslider6, 1.2e+02f, 24.0f, 3.6e+02f, 1.0f);
	reg.registerVar("dide.feedback","","S",N_("percentage of the feedback level in the delay loop"),&fslider2, 5e+01f, 0.0f, 1e+02f, 1.0f);
	reg.registerVar("dide.gain","","S",N_("overall gain of the delay line in percent"),&fslider4, 1e+02f, 0.0f, 1.2e+02f, 1.0f);
	reg.registerVar("dide.highpass",N_("highpass (hz)"),"S",N_("highpass filter frequency in the feddback loop"),&fslider1, 1.2e+02f, 2e+01f, 2e+04f, 1.0f);
	reg.registerVar("dide.howpass",N_("lowpass (hz)"),"S",N_("lowpass filter frequency in the feddback loop"),&fslider0, 1.2e+04f, 2e+01f, 2e+04f, 1.0f);
	reg.registerVar("dide.level","","S",N_("percentage of the delay gain level"),&fslider7, 5e+01f, 0.0f, 1e+02f, 1.0f);
	static const value_pair fslider3_values[] = {{"plain"},{"presence"},{"tape"},{"tape2"},{0}};
	reg.registerEnumVar("dide.mode","","S","",fslider3_values,&fslider3, 0.0f, 0.0f, 3.0f, 1.0f);
	static const value_pair fslider5_values[] = {{"Dotted 1/2 note"},{"1/2 note"},{"1/2 note triplets"},{" Dotted 1/4 note"},{"1/4 note"},{"1/4 note triplets"},{"Dotted 1/8 note"},{"1/8 note"},{"1/8 note triplets"},{" Dotted 1/16 note"},{"1/16 note"},{"1/16 note triplets"},{"Dotted 1/32 note"},{"1/32 note"},{"1/32 note triplets"},{" Dotted 1/64 note"},{"1/64 note"},{"1/64 note triplets"},{0}};
	reg.registerEnumVar("dide.notes",N_("tact"),"S",N_("note setting for bpm"),fslider5_values,&fslider5, 5.0f, 1.0f, 18.0f, 1.0f);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("dide" "." p)
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
            b.create_selector(PARAM("notes"), 0);
            b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_TOP);
            b.create_small_rackknob(PARAM("bpm"), _(" delay (bpm)"));
        }
        b.closeBox();
        b.openVerticalBox("");
        {
            b.openHorizontalBox("");
            b.openFrameBox("");
            b.closeBox();
            b.create_selector(PARAM("mode"), 0);
            b.closeBox();
            b.openHorizontalBox("");
            {
                b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_TOP);
                b.create_small_rackknob(PARAM("highpass"), _("highpass(hz)"));
                b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_TOP);
                b.create_small_rackknob(PARAM("howpass"), _("lowpass(hz)"));
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

} // end namespace digital_delay
