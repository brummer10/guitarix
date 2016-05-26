// generated from file '../src/LV2/faust/duck_delay_st.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)


namespace duck_delay_st {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	int 	IOTA;
	double 	fVec0[524288];
	double 	fConst9;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fConst10;
	double 	fRec6[2];
	double 	fConst11;
	double 	fRec5[2];
	double 	fRec3[2];
	double 	fVec1[524288];
	double 	fRec7[2];
	double 	fRec4[2];
	double 	fConst12;
	double 	fConst13;
	double 	fConst14;
	double 	fConst15;
	double 	fRec2[2];
	double 	fRec1[3];
	double 	fConst16;
	double 	fRec0[3];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fRec10[2];
	double 	fRec9[3];
	double 	fRec8[3];
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
	double 	fRec13[2];
	double 	fRec12[3];
	double 	fRec11[3];
	double 	fConst28;
	double 	fRec16[2];
	double 	fRec15[3];
	double 	fConst29;
	double 	fRec14[3];
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT	*fslider4_;
	double 	fRec17[2];
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT	*fslider5_;
	double 	fConst30;
	double 	fRec20[2];
	FAUSTFLOAT 	fslider6;
	FAUSTFLOAT	*fslider6_;
	double 	fRec19[2];
	FAUSTFLOAT 	fslider7;
	FAUSTFLOAT	*fslider7_;
	double 	fRec18[2];
	double 	fRec23[2];
	double 	fRec22[3];
	double 	fRec21[3];
	double 	fRec26[2];
	double 	fRec25[3];
	double 	fRec24[3];
	double 	fRec29[2];
	double 	fRec28[3];
	double 	fRec27[3];
	double 	fRec32[2];
	double 	fRec31[3];
	double 	fRec30[3];
	double 	fRec35[2];
	double 	fRec34[2];
	double 	fRec33[2];
	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(uint32_t samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(uint32_t samplingFreq, PluginLV2*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginLV2() {
	version = PLUGINLV2_VERSION;
	id = "duckDelaySt";
	name = N_("Duck Delay St");
	mono_audio = 0;
	stereo_audio = compute_static;
	set_samplerate = init_static;
	activate_plugin = 0;
	connect_ports = connect_static;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int i=0; i<524288; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<524288; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<3; i++) fRec1[i] = 0;
	for (int i=0; i<3; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<3; i++) fRec9[i] = 0;
	for (int i=0; i<3; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<3; i++) fRec12[i] = 0;
	for (int i=0; i<3; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<3; i++) fRec15[i] = 0;
	for (int i=0; i<3; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<3; i++) fRec22[i] = 0;
	for (int i=0; i<3; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<3; i++) fRec25[i] = 0;
	for (int i=0; i<3; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fRec29[i] = 0;
	for (int i=0; i<3; i++) fRec28[i] = 0;
	for (int i=0; i<3; i++) fRec27[i] = 0;
	for (int i=0; i<2; i++) fRec32[i] = 0;
	for (int i=0; i<3; i++) fRec31[i] = 0;
	for (int i=0; i<3; i++) fRec30[i] = 0;
	for (int i=0; i<2; i++) fRec35[i] = 0;
	for (int i=0; i<2; i++) fRec34[i] = 0;
	for (int i=0; i<2; i++) fRec33[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = tan((2764.601535159018 / double(iConst0)));
	fConst2 = (1.0 / faustpower<2>(fConst1));
	fConst3 = (2 * (1 - fConst2));
	fConst4 = (1.0 / fConst1);
	fConst5 = (1 + ((fConst4 - 0.6180339887498947) / fConst1));
	fConst6 = (1.0 / (1 + ((0.6180339887498947 + fConst4) / fConst1)));
	fConst7 = (1 + ((fConst4 - 1.6180339887498947) / fConst1));
	fConst8 = (1.0 / (1 + ((fConst4 + 1.6180339887498947) / fConst1)));
	IOTA = 0;
	fConst9 = exp((0 - (1e+01 / double(iConst0))));
	fConst10 = (1.0 - fConst9);
	fConst11 = (0.001 * iConst0);
	fConst12 = (0 - fConst4);
	fConst13 = (1 + fConst4);
	fConst14 = (1.0 / fConst13);
	fConst15 = (0 - ((1 - fConst4) / fConst13));
	fConst16 = (2 * (0 - fConst2));
	fConst17 = tan((1382.300767579509 / double(iConst0)));
	fConst18 = (1.0 / faustpower<2>(fConst17));
	fConst19 = (2 * (1 - fConst18));
	fConst20 = (1.0 / fConst17);
	fConst21 = (1 + ((fConst20 - 0.6180339887498947) / fConst17));
	fConst22 = (1.0 / (1 + ((0.6180339887498947 + fConst20) / fConst17)));
	fConst23 = (1 + ((fConst20 - 1.6180339887498947) / fConst17));
	fConst24 = (1.0 / (1 + ((1.6180339887498947 + fConst20) / fConst17)));
	fConst25 = (1 + fConst20);
	fConst26 = (1.0 / fConst25);
	fConst27 = (0 - ((1 - fConst20) / fConst25));
	fConst28 = (0 - fConst20);
	fConst29 = (2 * (0 - fConst18));
	fConst30 = (1.0 / double(iConst0));
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
#define fslider2 (*fslider2_)
#define fslider3 (*fslider3_)
#define fslider4 (*fslider4_)
#define fslider5 (*fslider5_)
#define fslider6 (*fslider6_)
#define fslider7 (*fslider7_)
	double 	fSlow0 = double(fslider0);
	double 	fSlow1 = (1 - fSlow0);
	double 	fSlow2 = double(fslider1);
	double 	fSlow3 = (fConst10 * double(fslider2));
	double 	fSlow4 = (1 - (fSlow0 * fSlow2));
	double 	fSlow5 = double(fslider3);
	double 	fSlow6 = pow(10,(0.6 * fSlow5));
	double 	fSlow7 = pow(10,(0.6 * (1 - fSlow5)));
	double 	fSlow8 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider4))));
	double 	fSlow9 = exp((0 - (fConst30 / double(fslider5))));
	double 	fSlow10 = (1.0 - fSlow9);
	double 	fSlow11 = exp((0 - (fConst30 / double(fslider6))));
	double 	fSlow12 = (1.0 - fSlow11);
	double 	fSlow13 = pow(10,(0.05 * double(fslider7)));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		double fTemp1 = (fTemp0 + (fSlow2 * ((fSlow1 * fRec5[1]) + (fSlow0 * fRec4[1]))));
		fVec0[IOTA&524287] = fTemp1;
		fRec6[0] = (fSlow3 + (fConst9 * fRec6[1]));
		double fTemp2 = (fConst11 * fRec6[0]);
		int iTemp3 = int(fTemp2);
		int iTemp4 = (1 + iTemp3);
		int iTemp5 = int((int(iTemp4) & 393215));
		double fTemp6 = (fTemp2 - iTemp3);
		double fTemp7 = (iTemp4 - fTemp2);
		int iTemp8 = int((iTemp3 & 393215));
		fRec5[0] = ((fVec0[(IOTA-iTemp8)&524287] * fTemp7) + (fTemp6 * fVec0[(IOTA-iTemp5)&524287]));
		fRec3[0] = fRec5[0];
		double fTemp9 = (double)input1[i];
		double fTemp10 = ((fSlow4 * fTemp9) + (fSlow2 * ((fSlow1 * fRec7[1]) + (fSlow0 * fRec3[1]))));
		fVec1[IOTA&524287] = fTemp10;
		fRec7[0] = ((fTemp7 * fVec1[(IOTA-iTemp8)&524287]) + (fTemp6 * fVec1[(IOTA-iTemp5)&524287]));
		fRec4[0] = fRec7[0];
		fRec2[0] = ((fConst15 * fRec2[1]) + (fConst14 * ((fConst4 * fRec3[0]) + (fConst12 * fRec3[1]))));
		fRec1[0] = (fRec2[0] - (fConst8 * ((fConst7 * fRec1[2]) + (fConst3 * fRec1[1]))));
		fRec0[0] = ((fConst8 * (((fConst2 * fRec1[0]) + (fConst16 * fRec1[1])) + (fConst2 * fRec1[2]))) - (fConst6 * ((fConst5 * fRec0[2]) + (fConst3 * fRec0[1]))));
		double fTemp11 = (fRec3[0] + fRec3[1]);
		fRec10[0] = ((fConst15 * fRec10[1]) + (fConst14 * fTemp11));
		fRec9[0] = (fRec10[0] - (fConst8 * ((fConst7 * fRec9[2]) + (fConst3 * fRec9[1]))));
		fRec8[0] = ((fConst8 * (fRec9[2] + (fRec9[0] + (2 * fRec9[1])))) - (fConst6 * ((fConst5 * fRec8[2]) + (fConst3 * fRec8[1]))));
		fRec13[0] = ((fConst27 * fRec13[1]) + (fConst26 * fTemp11));
		fRec12[0] = (fRec13[0] - (fConst24 * ((fConst23 * fRec12[2]) + (fConst19 * fRec12[1]))));
		fRec11[0] = ((fConst24 * (fRec12[2] + (fRec12[0] + (2 * fRec12[1])))) - (fConst22 * ((fConst21 * fRec11[2]) + (fConst19 * fRec11[1]))));
		fRec16[0] = ((fConst27 * fRec16[1]) + (fConst26 * ((fConst20 * fRec3[0]) + (fConst28 * fRec3[1]))));
		fRec15[0] = (fRec16[0] - (fConst24 * ((fConst23 * fRec15[2]) + (fConst19 * fRec15[1]))));
		fRec14[0] = ((fConst24 * (((fConst18 * fRec15[0]) + (fConst29 * fRec15[1])) + (fConst18 * fRec15[2]))) - (fConst22 * ((fConst21 * fRec14[2]) + (fConst19 * fRec14[1]))));
		fRec17[0] = ((0.999 * fRec17[1]) + fSlow8);
		double fTemp12 = fabs(fTemp0);
		fRec20[0] = ((fSlow9 * max(fTemp12, fRec20[1])) + (fSlow10 * fTemp12));
		fRec19[0] = ((fSlow11 * fRec19[1]) + (fSlow12 * fRec20[0]));
		fRec18[0] = ((fConst9 * fRec18[1]) + (fConst10 * (1 - ((fSlow13 * fRec19[0]) > 1))));
		output0[i] = (FAUSTFLOAT)(fTemp0 + (0.1778279410038923 * ((fRec18[0] * fRec17[0]) * ((fConst22 * ((((fConst18 * fRec14[0]) + (fConst29 * fRec14[1])) + (fConst18 * fRec14[2])) + (fSlow7 * (fRec11[2] + (fRec11[0] + (2 * fRec11[1])))))) + (fConst6 * ((fRec8[2] + (fRec8[0] + (2 * fRec8[1]))) + (fSlow6 * (((fConst2 * fRec0[0]) + (fConst16 * fRec0[1])) + (fConst2 * fRec0[2])))))))));
		fRec23[0] = ((fConst15 * fRec23[1]) + (fConst14 * ((fConst4 * fRec4[0]) + (fConst12 * fRec4[1]))));
		fRec22[0] = (fRec23[0] - (fConst8 * ((fConst7 * fRec22[2]) + (fConst3 * fRec22[1]))));
		fRec21[0] = ((fConst8 * (((fConst2 * fRec22[0]) + (fConst16 * fRec22[1])) + (fConst2 * fRec22[2]))) - (fConst6 * ((fConst5 * fRec21[2]) + (fConst3 * fRec21[1]))));
		double fTemp13 = (fRec4[0] + fRec4[1]);
		fRec26[0] = ((fConst15 * fRec26[1]) + (fConst14 * fTemp13));
		fRec25[0] = (fRec26[0] - (fConst8 * ((fConst7 * fRec25[2]) + (fConst3 * fRec25[1]))));
		fRec24[0] = ((fConst8 * (fRec25[2] + (fRec25[0] + (2 * fRec25[1])))) - (fConst6 * ((fConst5 * fRec24[2]) + (fConst3 * fRec24[1]))));
		fRec29[0] = ((fConst27 * fRec29[1]) + (fConst26 * fTemp13));
		fRec28[0] = (fRec29[0] - (fConst24 * ((fConst23 * fRec28[2]) + (fConst19 * fRec28[1]))));
		fRec27[0] = ((fConst24 * (fRec28[2] + (fRec28[0] + (2 * fRec28[1])))) - (fConst22 * ((fConst21 * fRec27[2]) + (fConst19 * fRec27[1]))));
		fRec32[0] = ((fConst27 * fRec32[1]) + (fConst26 * ((fConst20 * fRec4[0]) + (fConst28 * fRec4[1]))));
		fRec31[0] = (fRec32[0] - (fConst24 * ((fConst23 * fRec31[2]) + (fConst19 * fRec31[1]))));
		fRec30[0] = ((fConst24 * (((fConst18 * fRec31[0]) + (fConst29 * fRec31[1])) + (fConst18 * fRec31[2]))) - (fConst22 * ((fConst21 * fRec30[2]) + (fConst19 * fRec30[1]))));
		double fTemp14 = fabs(fTemp9);
		fRec35[0] = ((fSlow9 * max(fTemp14, fRec35[1])) + (fSlow10 * fTemp14));
		fRec34[0] = ((fSlow11 * fRec34[1]) + (fSlow12 * fRec35[0]));
		fRec33[0] = ((fConst9 * fRec33[1]) + (fConst10 * (1 - ((fSlow13 * fRec34[0]) > 1))));
		output1[i] = (FAUSTFLOAT)(fTemp9 + (0.1778279410038923 * ((fRec17[0] * fRec33[0]) * ((fConst22 * ((((fConst18 * fRec30[0]) + (fConst29 * fRec30[1])) + (fConst18 * fRec30[2])) + (fSlow7 * (fRec27[2] + (fRec27[0] + (2 * fRec27[1])))))) + (fConst6 * ((fRec24[2] + (fRec24[0] + (2 * fRec24[1]))) + (fSlow6 * (((fConst2 * fRec21[0]) + (fConst16 * fRec21[1])) + (fConst2 * fRec21[2])))))))));
		// post processing
		fRec33[1] = fRec33[0];
		fRec34[1] = fRec34[0];
		fRec35[1] = fRec35[0];
		fRec30[2] = fRec30[1]; fRec30[1] = fRec30[0];
		fRec31[2] = fRec31[1]; fRec31[1] = fRec31[0];
		fRec32[1] = fRec32[0];
		fRec27[2] = fRec27[1]; fRec27[1] = fRec27[0];
		fRec28[2] = fRec28[1]; fRec28[1] = fRec28[0];
		fRec29[1] = fRec29[0];
		fRec24[2] = fRec24[1]; fRec24[1] = fRec24[0];
		fRec25[2] = fRec25[1]; fRec25[1] = fRec25[0];
		fRec26[1] = fRec26[0];
		fRec21[2] = fRec21[1]; fRec21[1] = fRec21[0];
		fRec22[2] = fRec22[1]; fRec22[1] = fRec22[0];
		fRec23[1] = fRec23[0];
		fRec18[1] = fRec18[0];
		fRec19[1] = fRec19[0];
		fRec20[1] = fRec20[0];
		fRec17[1] = fRec17[0];
		fRec14[2] = fRec14[1]; fRec14[1] = fRec14[0];
		fRec15[2] = fRec15[1]; fRec15[1] = fRec15[0];
		fRec16[1] = fRec16[0];
		fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
		fRec12[2] = fRec12[1]; fRec12[1] = fRec12[0];
		fRec13[1] = fRec13[0];
		fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec10[1] = fRec10[0];
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec4[1] = fRec4[0];
		fRec7[1] = fRec7[0];
		fRec3[1] = fRec3[0];
		fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		IOTA = IOTA+1;
	}
#undef fslider0
#undef fslider1
#undef fslider2
#undef fslider3
#undef fslider4
#undef fslider5
#undef fslider6
#undef fslider7
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case AMOUNT: 
		fslider7_ = (float*)data; // , 0.5, 0.0, 56.0, 0.05 
		break;
	case ATTACK: 
		fslider6_ = (float*)data; // , 0.1, 0.05, 0.5, 0.05 
		break;
	case COLORATION: 
		fslider3_ = (float*)data; // , 0.0, -1.0, 1.0, 0.05 
		break;
	case EFFECT: 
		fslider4_ = (float*)data; // , 0.0, -16.0, 4.0, 0.1 
		break;
	case FEEDBACK: 
		fslider1_ = (float*)data; // , 0.0, 0.0, 1.0, 0.05 
		break;
	case PINGPONG: 
		fslider0_ = (float*)data; // , 0.0, 0.0, 1.0, 0.05 
		break;
	case RELEASE: 
		fslider5_ = (float*)data; // , 0.1, 0.05, 2.0, 0.05 
		break;
	case TIME: 
		fslider2_ = (float*)data; // , 5e+02, 1.0, 2e+03, 1.0 
		break;
	default:
		break;
	}
}

void Dsp::connect_static(uint32_t port,void* data, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->connect(port, data);
}


PluginLV2 *plugin() {
	return new Dsp();
}

void Dsp::del_instance(PluginLV2 *p)
{
	delete static_cast<Dsp*>(p);
}

/*
typedef enum
{
   AMOUNT, 
   ATTACK, 
   COLORATION, 
   EFFECT, 
   FEEDBACK, 
   PINGPONG, 
   RELEASE, 
   TIME, 
} PortIndex;
*/

} // end namespace duck_delay_st
