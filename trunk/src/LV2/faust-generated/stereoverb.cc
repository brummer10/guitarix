// generated from file '../src/LV2/faust/stereoverb.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)


namespace stereoverb {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	int 	iVec0[2];
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec9[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	int 	IOTA;
	double 	fVec1[2048];
	double 	fRec8[2];
	double 	fRec11[2];
	double 	fVec2[2048];
	double 	fRec10[2];
	double 	fRec13[2];
	double 	fVec3[2048];
	double 	fRec12[2];
	double 	fRec15[2];
	double 	fVec4[2048];
	double 	fRec14[2];
	double 	fRec17[2];
	double 	fVec5[2048];
	double 	fRec16[2];
	double 	fRec19[2];
	double 	fVec6[2048];
	double 	fRec18[2];
	double 	fRec21[2];
	double 	fVec7[2048];
	double 	fRec20[2];
	double 	fRec23[2];
	double 	fVec8[2048];
	double 	fRec22[2];
	double 	fVec9[1024];
	double 	fRec6[2];
	double 	fVec10[512];
	double 	fRec4[2];
	double 	fVec11[512];
	double 	fRec2[2];
	double 	fVec12[256];
	double 	fRec0[2];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fConst0;
	double 	fRec24[2];
	double 	fRec25[2];
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT	*fcheckbox0_;
	double 	fRec35[2];
	double 	fVec13[2048];
	double 	fRec34[2];
	double 	fRec37[2];
	double 	fVec14[2048];
	double 	fRec36[2];
	double 	fRec39[2];
	double 	fVec15[2048];
	double 	fRec38[2];
	double 	fRec41[2];
	double 	fVec16[2048];
	double 	fRec40[2];
	double 	fRec43[2];
	double 	fVec17[2048];
	double 	fRec42[2];
	double 	fRec45[2];
	double 	fVec18[2048];
	double 	fRec44[2];
	double 	fRec47[2];
	double 	fVec19[2048];
	double 	fRec46[2];
	double 	fRec49[2];
	double 	fVec20[2048];
	double 	fRec48[2];
	double 	fVec21[1024];
	double 	fRec32[2];
	double 	fVec22[512];
	double 	fRec30[2];
	double 	fVec23[512];
	double 	fRec28[2];
	double 	fVec24[256];
	double 	fRec26[2];

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
	id = "stereoverb";
	name = N_("Stereo Verb");
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
	for (int i=0; i<2; i++) iVec0[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2048; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2048; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2048; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2048; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<2048; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<2048; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<2048; i++) fVec7[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<2048; i++) fVec8[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<1024; i++) fVec9[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<512; i++) fVec10[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<512; i++) fVec11[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<256; i++) fVec12[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fRec25[i] = 0;
	for (int i=0; i<2; i++) fRec35[i] = 0;
	for (int i=0; i<2048; i++) fVec13[i] = 0;
	for (int i=0; i<2; i++) fRec34[i] = 0;
	for (int i=0; i<2; i++) fRec37[i] = 0;
	for (int i=0; i<2048; i++) fVec14[i] = 0;
	for (int i=0; i<2; i++) fRec36[i] = 0;
	for (int i=0; i<2; i++) fRec39[i] = 0;
	for (int i=0; i<2048; i++) fVec15[i] = 0;
	for (int i=0; i<2; i++) fRec38[i] = 0;
	for (int i=0; i<2; i++) fRec41[i] = 0;
	for (int i=0; i<2048; i++) fVec16[i] = 0;
	for (int i=0; i<2; i++) fRec40[i] = 0;
	for (int i=0; i<2; i++) fRec43[i] = 0;
	for (int i=0; i<2048; i++) fVec17[i] = 0;
	for (int i=0; i<2; i++) fRec42[i] = 0;
	for (int i=0; i<2; i++) fRec45[i] = 0;
	for (int i=0; i<2048; i++) fVec18[i] = 0;
	for (int i=0; i<2; i++) fRec44[i] = 0;
	for (int i=0; i<2; i++) fRec47[i] = 0;
	for (int i=0; i<2048; i++) fVec19[i] = 0;
	for (int i=0; i<2; i++) fRec46[i] = 0;
	for (int i=0; i<2; i++) fRec49[i] = 0;
	for (int i=0; i<2048; i++) fVec20[i] = 0;
	for (int i=0; i<2; i++) fRec48[i] = 0;
	for (int i=0; i<1024; i++) fVec21[i] = 0;
	for (int i=0; i<2; i++) fRec32[i] = 0;
	for (int i=0; i<512; i++) fVec22[i] = 0;
	for (int i=0; i<2; i++) fRec30[i] = 0;
	for (int i=0; i<512; i++) fVec23[i] = 0;
	for (int i=0; i<2; i++) fRec28[i] = 0;
	for (int i=0; i<256; i++) fVec24[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = (6.283185307179586 / min(1.92e+05, max(1.0, (double)fSamplingFreq)));
	IOTA = 0;
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
#define fcheckbox0 (*fcheckbox0_)
	double 	fSlow0 = double(fslider0);
	double 	fSlow1 = (1 - fSlow0);
	double 	fSlow2 = (0.7 + (0.28 * double(fslider1)));
	double 	fSlow3 = double(fslider2);
	double 	fSlow4 = (0.00015 * fSlow3);
	double 	fSlow5 = (1 - (0.01 * fSlow3));
	double 	fSlow6 = (fSlow3 * (0.00015 + (0.01 * fSlow5)));
	double 	fSlow7 = (fConst0 * double(fslider3));
	double 	fSlow8 = cos(fSlow7);
	double 	fSlow9 = sin(fSlow7);
	double 	fSlow10 = (0 - fSlow9);
	double 	fSlow11 = double(fcheckbox0);
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		fRec9[0] = ((fSlow1 * fRec8[1]) + (fSlow0 * fRec9[1]));
		double fTemp0 = (double)input0[i];
		double fTemp1 = (fSlow4 * fTemp0);
		fVec1[IOTA&2047] = (fTemp1 + (fSlow2 * fRec9[0]));
		fRec8[0] = fVec1[(IOTA-1640)&2047];
		fRec11[0] = ((fSlow1 * fRec10[1]) + (fSlow0 * fRec11[1]));
		fVec2[IOTA&2047] = (fTemp1 + (fSlow2 * fRec11[0]));
		fRec10[0] = fVec2[(IOTA-1580)&2047];
		fRec13[0] = ((fSlow1 * fRec12[1]) + (fSlow0 * fRec13[1]));
		fVec3[IOTA&2047] = (fTemp1 + (fSlow2 * fRec13[0]));
		fRec12[0] = fVec3[(IOTA-1514)&2047];
		fRec15[0] = ((fSlow1 * fRec14[1]) + (fSlow0 * fRec15[1]));
		fVec4[IOTA&2047] = (fTemp1 + (fSlow2 * fRec15[0]));
		fRec14[0] = fVec4[(IOTA-1445)&2047];
		fRec17[0] = ((fSlow1 * fRec16[1]) + (fSlow0 * fRec17[1]));
		fVec5[IOTA&2047] = (fTemp1 + (fSlow2 * fRec17[0]));
		fRec16[0] = fVec5[(IOTA-1379)&2047];
		fRec19[0] = ((fSlow1 * fRec18[1]) + (fSlow0 * fRec19[1]));
		fVec6[IOTA&2047] = (fTemp1 + (fSlow2 * fRec19[0]));
		fRec18[0] = fVec6[(IOTA-1300)&2047];
		fRec21[0] = ((fSlow1 * fRec20[1]) + (fSlow0 * fRec21[1]));
		fVec7[IOTA&2047] = (fTemp1 + (fSlow2 * fRec21[0]));
		fRec20[0] = fVec7[(IOTA-1211)&2047];
		fRec23[0] = ((fSlow1 * fRec22[1]) + (fSlow0 * fRec23[1]));
		fVec8[IOTA&2047] = (fTemp1 + (fSlow2 * fRec23[0]));
		fRec22[0] = fVec8[(IOTA-1139)&2047];
		fVec9[IOTA&1023] = (fRec22[0] + (fRec20[0] + (fRec18[0] + (fRec16[0] + (fRec14[0] + (fRec12[0] + (fRec10[0] + ((0.5 * fRec6[1]) + fRec8[0]))))))));
		fRec6[0] = fVec9[(IOTA-579)&1023];
		double 	fRec7 = (0 - ((fRec22[0] + (fRec20[0] + (fRec18[0] + (fRec16[0] + (fRec14[0] + (fRec12[0] + (fRec8[0] + fRec10[0]))))))) - fRec6[1]));
		fVec10[IOTA&511] = ((0.5 * fRec4[1]) + fRec7);
		fRec4[0] = fVec10[(IOTA-464)&511];
		double 	fRec5 = (fRec4[1] - fRec7);
		fVec11[IOTA&511] = ((0.5 * fRec2[1]) + fRec5);
		fRec2[0] = fVec11[(IOTA-364)&511];
		double 	fRec3 = (fRec2[1] - fRec5);
		fVec12[IOTA&255] = ((0.5 * fRec0[1]) + fRec3);
		fRec0[0] = fVec12[(IOTA-248)&255];
		double 	fRec1 = (fRec0[1] - fRec3);
		fRec24[0] = ((fSlow9 * fRec25[1]) + (fSlow8 * fRec24[1]));
		fRec25[0] = ((1 + ((fSlow8 * fRec25[1]) + (fSlow10 * fRec24[1]))) - iVec0[1]);
		output0[i] = (FAUSTFLOAT)((fSlow5 * fTemp0) + ((1 - (fSlow11 * fRec24[0])) * ((fSlow6 * fTemp0) + fRec1)));
		fRec35[0] = ((fSlow1 * fRec34[1]) + (fSlow0 * fRec35[1]));
		double fTemp2 = (double)input1[i];
		double fTemp3 = (fSlow4 * fTemp2);
		fVec13[IOTA&2047] = (fTemp3 + (fSlow2 * fRec35[0]));
		fRec34[0] = fVec13[(IOTA-1640)&2047];
		fRec37[0] = ((fSlow1 * fRec36[1]) + (fSlow0 * fRec37[1]));
		fVec14[IOTA&2047] = (fTemp3 + (fSlow2 * fRec37[0]));
		fRec36[0] = fVec14[(IOTA-1580)&2047];
		fRec39[0] = ((fSlow1 * fRec38[1]) + (fSlow0 * fRec39[1]));
		fVec15[IOTA&2047] = (fTemp3 + (fSlow2 * fRec39[0]));
		fRec38[0] = fVec15[(IOTA-1514)&2047];
		fRec41[0] = ((fSlow1 * fRec40[1]) + (fSlow0 * fRec41[1]));
		fVec16[IOTA&2047] = (fTemp3 + (fSlow2 * fRec41[0]));
		fRec40[0] = fVec16[(IOTA-1445)&2047];
		fRec43[0] = ((fSlow1 * fRec42[1]) + (fSlow0 * fRec43[1]));
		fVec17[IOTA&2047] = (fTemp3 + (fSlow2 * fRec43[0]));
		fRec42[0] = fVec17[(IOTA-1379)&2047];
		fRec45[0] = ((fSlow1 * fRec44[1]) + (fSlow0 * fRec45[1]));
		fVec18[IOTA&2047] = (fTemp3 + (fSlow2 * fRec45[0]));
		fRec44[0] = fVec18[(IOTA-1300)&2047];
		fRec47[0] = ((fSlow1 * fRec46[1]) + (fSlow0 * fRec47[1]));
		fVec19[IOTA&2047] = (fTemp3 + (fSlow2 * fRec47[0]));
		fRec46[0] = fVec19[(IOTA-1211)&2047];
		fRec49[0] = ((fSlow1 * fRec48[1]) + (fSlow0 * fRec49[1]));
		fVec20[IOTA&2047] = (fTemp3 + (fSlow2 * fRec49[0]));
		fRec48[0] = fVec20[(IOTA-1139)&2047];
		fVec21[IOTA&1023] = (fRec48[0] + (fRec46[0] + (fRec44[0] + (fRec42[0] + (fRec40[0] + (fRec38[0] + (fRec36[0] + ((0.5 * fRec32[1]) + fRec34[0]))))))));
		fRec32[0] = fVec21[(IOTA-579)&1023];
		double 	fRec33 = (0 - ((fRec48[0] + (fRec46[0] + (fRec44[0] + (fRec42[0] + (fRec40[0] + (fRec38[0] + (fRec34[0] + fRec36[0]))))))) - fRec32[1]));
		fVec22[IOTA&511] = ((0.5 * fRec30[1]) + fRec33);
		fRec30[0] = fVec22[(IOTA-464)&511];
		double 	fRec31 = (fRec30[1] - fRec33);
		fVec23[IOTA&511] = ((0.5 * fRec28[1]) + fRec31);
		fRec28[0] = fVec23[(IOTA-364)&511];
		double 	fRec29 = (fRec28[1] - fRec31);
		fVec24[IOTA&255] = ((0.5 * fRec26[1]) + fRec29);
		fRec26[0] = fVec24[(IOTA-248)&255];
		double 	fRec27 = (fRec26[1] - fRec29);
		output1[i] = (FAUSTFLOAT)((fSlow5 * fTemp2) + ((1 - (fSlow11 * (0 - fRec24[0]))) * ((fSlow6 * fTemp2) + fRec27)));
		// post processing
		fRec26[1] = fRec26[0];
		fRec28[1] = fRec28[0];
		fRec30[1] = fRec30[0];
		fRec32[1] = fRec32[0];
		fRec48[1] = fRec48[0];
		fRec49[1] = fRec49[0];
		fRec46[1] = fRec46[0];
		fRec47[1] = fRec47[0];
		fRec44[1] = fRec44[0];
		fRec45[1] = fRec45[0];
		fRec42[1] = fRec42[0];
		fRec43[1] = fRec43[0];
		fRec40[1] = fRec40[0];
		fRec41[1] = fRec41[0];
		fRec38[1] = fRec38[0];
		fRec39[1] = fRec39[0];
		fRec36[1] = fRec36[0];
		fRec37[1] = fRec37[0];
		fRec34[1] = fRec34[0];
		fRec35[1] = fRec35[0];
		fRec25[1] = fRec25[0];
		fRec24[1] = fRec24[0];
		fRec0[1] = fRec0[0];
		fRec2[1] = fRec2[0];
		fRec4[1] = fRec4[0];
		fRec6[1] = fRec6[0];
		fRec22[1] = fRec22[0];
		fRec23[1] = fRec23[0];
		fRec20[1] = fRec20[0];
		fRec21[1] = fRec21[0];
		fRec18[1] = fRec18[0];
		fRec19[1] = fRec19[0];
		fRec16[1] = fRec16[0];
		fRec17[1] = fRec17[0];
		fRec14[1] = fRec14[0];
		fRec15[1] = fRec15[0];
		fRec12[1] = fRec12[0];
		fRec13[1] = fRec13[0];
		fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		fRec8[1] = fRec8[0];
		IOTA = IOTA+1;
		fRec9[1] = fRec9[0];
		iVec0[1] = iVec0[0];
	}
#undef fslider0
#undef fslider1
#undef fslider2
#undef fslider3
#undef fcheckbox0
}
		
void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case LFOFREQ: 
		fslider3_ = (float*)data; // , 0.2, 0.0, 5.0, 0.01 
		break;
	case ROOMSIZE: 
		fslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.025 
		break;
	case DAMP: 
		fslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.025 
		break;
	// static const value_pair fcheckbox0_values[] = {{"linear"},{"pingpong"},{0}};
	case INVERT: 
		fcheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case WET_DRY: 
		fslider2_ = (float*)data; // , 5e+01, 0.0, 1e+02, 1.0 
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
   LFOFREQ, 
   ROOMSIZE, 
   DAMP, 
   INVERT, 
   WET_DRY, 
} PortIndex;
*/

} // end namespace stereoverb
