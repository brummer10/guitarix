// generated from file './faust/mbreverb.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)


namespace mbreverb {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	int 	iConst0;
	double 	fConst1;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fConst2;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fVec0[2];
	double 	fRec11[2];
	double 	fRec10[3];
	double 	fVec1[2];
	double 	fRec9[2];
	double 	fRec8[3];
	double 	fVec2[2];
	double 	fRec7[2];
	double 	fRec6[3];
	double 	fVec3[2];
	double 	fRec5[2];
	double 	fRec4[3];
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT	*fslider4_;
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT	*fslider5_;
	double 	fRec21[2];
	FAUSTFLOAT 	fslider6;
	FAUSTFLOAT	*fslider6_;
	int 	IOTA;
	double 	fVec4[2048];
	double 	fRec20[2];
	double 	fRec23[2];
	double 	fVec5[2048];
	double 	fRec22[2];
	double 	fRec25[2];
	double 	fVec6[2048];
	double 	fRec24[2];
	double 	fRec27[2];
	double 	fVec7[2048];
	double 	fRec26[2];
	double 	fRec29[2];
	double 	fVec8[2048];
	double 	fRec28[2];
	double 	fRec31[2];
	double 	fVec9[2048];
	double 	fRec30[2];
	double 	fRec33[2];
	double 	fVec10[2048];
	double 	fRec32[2];
	double 	fRec35[2];
	double 	fVec11[2048];
	double 	fRec34[2];
	double 	fVec12[1024];
	double 	fRec18[2];
	double 	fVec13[512];
	double 	fRec16[2];
	double 	fVec14[512];
	double 	fRec14[2];
	double 	fVec15[256];
	double 	fRec12[2];
	double 	fRec0[2];
	int 	iRec1[2];
	double 	fRec2[2];
	FAUSTFLOAT 	fbargraph0;
	FAUSTFLOAT	*fbargraph0_;
	double 	fRec41[2];
	double 	fRec40[3];
	FAUSTFLOAT 	fslider7;
	FAUSTFLOAT	*fslider7_;
	FAUSTFLOAT 	fslider8;
	FAUSTFLOAT	*fslider8_;
	double 	fRec51[2];
	FAUSTFLOAT 	fslider9;
	FAUSTFLOAT	*fslider9_;
	double 	fVec16[2048];
	double 	fRec50[2];
	double 	fRec53[2];
	double 	fVec17[2048];
	double 	fRec52[2];
	double 	fRec55[2];
	double 	fVec18[2048];
	double 	fRec54[2];
	double 	fRec57[2];
	double 	fVec19[2048];
	double 	fRec56[2];
	double 	fRec59[2];
	double 	fVec20[2048];
	double 	fRec58[2];
	double 	fRec61[2];
	double 	fVec21[2048];
	double 	fRec60[2];
	double 	fRec63[2];
	double 	fVec22[2048];
	double 	fRec62[2];
	double 	fRec65[2];
	double 	fVec23[2048];
	double 	fRec64[2];
	double 	fVec24[1024];
	double 	fRec48[2];
	double 	fVec25[512];
	double 	fRec46[2];
	double 	fVec26[512];
	double 	fRec44[2];
	double 	fVec27[256];
	double 	fRec42[2];
	double 	fRec36[2];
	int 	iRec37[2];
	double 	fRec38[2];
	FAUSTFLOAT 	fbargraph1;
	FAUSTFLOAT	*fbargraph1_;
	double 	fRec72[2];
	double 	fRec71[3];
	double 	fRec70[3];
	FAUSTFLOAT 	fslider10;
	FAUSTFLOAT	*fslider10_;
	FAUSTFLOAT 	fslider11;
	FAUSTFLOAT	*fslider11_;
	double 	fRec82[2];
	FAUSTFLOAT 	fslider12;
	FAUSTFLOAT	*fslider12_;
	double 	fVec28[2048];
	double 	fRec81[2];
	double 	fRec84[2];
	double 	fVec29[2048];
	double 	fRec83[2];
	double 	fRec86[2];
	double 	fVec30[2048];
	double 	fRec85[2];
	double 	fRec88[2];
	double 	fVec31[2048];
	double 	fRec87[2];
	double 	fRec90[2];
	double 	fVec32[2048];
	double 	fRec89[2];
	double 	fRec92[2];
	double 	fVec33[2048];
	double 	fRec91[2];
	double 	fRec94[2];
	double 	fVec34[2048];
	double 	fRec93[2];
	double 	fRec96[2];
	double 	fVec35[2048];
	double 	fRec95[2];
	double 	fVec36[1024];
	double 	fRec79[2];
	double 	fVec37[512];
	double 	fRec77[2];
	double 	fVec38[512];
	double 	fRec75[2];
	double 	fVec39[256];
	double 	fRec73[2];
	double 	fRec66[2];
	int 	iRec67[2];
	double 	fRec68[2];
	FAUSTFLOAT 	fbargraph2;
	FAUSTFLOAT	*fbargraph2_;
	double 	fRec104[2];
	double 	fRec103[3];
	double 	fRec102[3];
	double 	fRec101[3];
	FAUSTFLOAT 	fslider13;
	FAUSTFLOAT	*fslider13_;
	FAUSTFLOAT 	fslider14;
	FAUSTFLOAT	*fslider14_;
	double 	fRec114[2];
	FAUSTFLOAT 	fslider15;
	FAUSTFLOAT	*fslider15_;
	double 	fVec40[2048];
	double 	fRec113[2];
	double 	fRec116[2];
	double 	fVec41[2048];
	double 	fRec115[2];
	double 	fRec118[2];
	double 	fVec42[2048];
	double 	fRec117[2];
	double 	fRec120[2];
	double 	fVec43[2048];
	double 	fRec119[2];
	double 	fRec122[2];
	double 	fVec44[2048];
	double 	fRec121[2];
	double 	fRec124[2];
	double 	fVec45[2048];
	double 	fRec123[2];
	double 	fRec126[2];
	double 	fVec46[2048];
	double 	fRec125[2];
	double 	fRec128[2];
	double 	fVec47[2048];
	double 	fRec127[2];
	double 	fVec48[1024];
	double 	fRec111[2];
	double 	fVec49[512];
	double 	fRec109[2];
	double 	fVec50[512];
	double 	fRec107[2];
	double 	fVec51[256];
	double 	fRec105[2];
	double 	fRec97[2];
	int 	iRec98[2];
	double 	fRec99[2];
	FAUSTFLOAT 	fbargraph3;
	FAUSTFLOAT	*fbargraph3_;
	double 	fRec137[2];
	double 	fRec136[3];
	double 	fRec135[3];
	double 	fRec134[3];
	double 	fRec133[3];
	FAUSTFLOAT 	fslider16;
	FAUSTFLOAT	*fslider16_;
	FAUSTFLOAT 	fslider17;
	FAUSTFLOAT	*fslider17_;
	double 	fRec147[2];
	FAUSTFLOAT 	fslider18;
	FAUSTFLOAT	*fslider18_;
	double 	fVec52[2048];
	double 	fRec146[2];
	double 	fRec149[2];
	double 	fVec53[2048];
	double 	fRec148[2];
	double 	fRec151[2];
	double 	fVec54[2048];
	double 	fRec150[2];
	double 	fRec153[2];
	double 	fVec55[2048];
	double 	fRec152[2];
	double 	fRec155[2];
	double 	fVec56[2048];
	double 	fRec154[2];
	double 	fRec157[2];
	double 	fVec57[2048];
	double 	fRec156[2];
	double 	fRec159[2];
	double 	fVec58[2048];
	double 	fRec158[2];
	double 	fRec161[2];
	double 	fVec59[2048];
	double 	fRec160[2];
	double 	fVec60[1024];
	double 	fRec144[2];
	double 	fVec61[512];
	double 	fRec142[2];
	double 	fVec62[512];
	double 	fRec140[2];
	double 	fVec63[256];
	double 	fRec138[2];
	double 	fRec129[2];
	int 	iRec130[2];
	double 	fRec131[2];
	FAUSTFLOAT 	fbargraph4;
	FAUSTFLOAT	*fbargraph4_;
	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(uint32_t samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(uint32_t samplingFreq, PluginLV2*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginLV2() {
	version = PLUGINLV2_VERSION;
	id = "mbe";
	name = N_("MultiBand Reverb");
	mono_audio = compute_static;
	stereo_audio = 0;
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
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<3; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<3; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<3; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<2048; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<2048; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fRec25[i] = 0;
	for (int i=0; i<2048; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fRec27[i] = 0;
	for (int i=0; i<2048; i++) fVec7[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<2; i++) fRec29[i] = 0;
	for (int i=0; i<2048; i++) fVec8[i] = 0;
	for (int i=0; i<2; i++) fRec28[i] = 0;
	for (int i=0; i<2; i++) fRec31[i] = 0;
	for (int i=0; i<2048; i++) fVec9[i] = 0;
	for (int i=0; i<2; i++) fRec30[i] = 0;
	for (int i=0; i<2; i++) fRec33[i] = 0;
	for (int i=0; i<2048; i++) fVec10[i] = 0;
	for (int i=0; i<2; i++) fRec32[i] = 0;
	for (int i=0; i<2; i++) fRec35[i] = 0;
	for (int i=0; i<2048; i++) fVec11[i] = 0;
	for (int i=0; i<2; i++) fRec34[i] = 0;
	for (int i=0; i<1024; i++) fVec12[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<512; i++) fVec13[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<512; i++) fVec14[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<256; i++) fVec15[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) iRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec41[i] = 0;
	for (int i=0; i<3; i++) fRec40[i] = 0;
	for (int i=0; i<2; i++) fRec51[i] = 0;
	for (int i=0; i<2048; i++) fVec16[i] = 0;
	for (int i=0; i<2; i++) fRec50[i] = 0;
	for (int i=0; i<2; i++) fRec53[i] = 0;
	for (int i=0; i<2048; i++) fVec17[i] = 0;
	for (int i=0; i<2; i++) fRec52[i] = 0;
	for (int i=0; i<2; i++) fRec55[i] = 0;
	for (int i=0; i<2048; i++) fVec18[i] = 0;
	for (int i=0; i<2; i++) fRec54[i] = 0;
	for (int i=0; i<2; i++) fRec57[i] = 0;
	for (int i=0; i<2048; i++) fVec19[i] = 0;
	for (int i=0; i<2; i++) fRec56[i] = 0;
	for (int i=0; i<2; i++) fRec59[i] = 0;
	for (int i=0; i<2048; i++) fVec20[i] = 0;
	for (int i=0; i<2; i++) fRec58[i] = 0;
	for (int i=0; i<2; i++) fRec61[i] = 0;
	for (int i=0; i<2048; i++) fVec21[i] = 0;
	for (int i=0; i<2; i++) fRec60[i] = 0;
	for (int i=0; i<2; i++) fRec63[i] = 0;
	for (int i=0; i<2048; i++) fVec22[i] = 0;
	for (int i=0; i<2; i++) fRec62[i] = 0;
	for (int i=0; i<2; i++) fRec65[i] = 0;
	for (int i=0; i<2048; i++) fVec23[i] = 0;
	for (int i=0; i<2; i++) fRec64[i] = 0;
	for (int i=0; i<1024; i++) fVec24[i] = 0;
	for (int i=0; i<2; i++) fRec48[i] = 0;
	for (int i=0; i<512; i++) fVec25[i] = 0;
	for (int i=0; i<2; i++) fRec46[i] = 0;
	for (int i=0; i<512; i++) fVec26[i] = 0;
	for (int i=0; i<2; i++) fRec44[i] = 0;
	for (int i=0; i<256; i++) fVec27[i] = 0;
	for (int i=0; i<2; i++) fRec42[i] = 0;
	for (int i=0; i<2; i++) fRec36[i] = 0;
	for (int i=0; i<2; i++) iRec37[i] = 0;
	for (int i=0; i<2; i++) fRec38[i] = 0;
	for (int i=0; i<2; i++) fRec72[i] = 0;
	for (int i=0; i<3; i++) fRec71[i] = 0;
	for (int i=0; i<3; i++) fRec70[i] = 0;
	for (int i=0; i<2; i++) fRec82[i] = 0;
	for (int i=0; i<2048; i++) fVec28[i] = 0;
	for (int i=0; i<2; i++) fRec81[i] = 0;
	for (int i=0; i<2; i++) fRec84[i] = 0;
	for (int i=0; i<2048; i++) fVec29[i] = 0;
	for (int i=0; i<2; i++) fRec83[i] = 0;
	for (int i=0; i<2; i++) fRec86[i] = 0;
	for (int i=0; i<2048; i++) fVec30[i] = 0;
	for (int i=0; i<2; i++) fRec85[i] = 0;
	for (int i=0; i<2; i++) fRec88[i] = 0;
	for (int i=0; i<2048; i++) fVec31[i] = 0;
	for (int i=0; i<2; i++) fRec87[i] = 0;
	for (int i=0; i<2; i++) fRec90[i] = 0;
	for (int i=0; i<2048; i++) fVec32[i] = 0;
	for (int i=0; i<2; i++) fRec89[i] = 0;
	for (int i=0; i<2; i++) fRec92[i] = 0;
	for (int i=0; i<2048; i++) fVec33[i] = 0;
	for (int i=0; i<2; i++) fRec91[i] = 0;
	for (int i=0; i<2; i++) fRec94[i] = 0;
	for (int i=0; i<2048; i++) fVec34[i] = 0;
	for (int i=0; i<2; i++) fRec93[i] = 0;
	for (int i=0; i<2; i++) fRec96[i] = 0;
	for (int i=0; i<2048; i++) fVec35[i] = 0;
	for (int i=0; i<2; i++) fRec95[i] = 0;
	for (int i=0; i<1024; i++) fVec36[i] = 0;
	for (int i=0; i<2; i++) fRec79[i] = 0;
	for (int i=0; i<512; i++) fVec37[i] = 0;
	for (int i=0; i<2; i++) fRec77[i] = 0;
	for (int i=0; i<512; i++) fVec38[i] = 0;
	for (int i=0; i<2; i++) fRec75[i] = 0;
	for (int i=0; i<256; i++) fVec39[i] = 0;
	for (int i=0; i<2; i++) fRec73[i] = 0;
	for (int i=0; i<2; i++) fRec66[i] = 0;
	for (int i=0; i<2; i++) iRec67[i] = 0;
	for (int i=0; i<2; i++) fRec68[i] = 0;
	for (int i=0; i<2; i++) fRec104[i] = 0;
	for (int i=0; i<3; i++) fRec103[i] = 0;
	for (int i=0; i<3; i++) fRec102[i] = 0;
	for (int i=0; i<3; i++) fRec101[i] = 0;
	for (int i=0; i<2; i++) fRec114[i] = 0;
	for (int i=0; i<2048; i++) fVec40[i] = 0;
	for (int i=0; i<2; i++) fRec113[i] = 0;
	for (int i=0; i<2; i++) fRec116[i] = 0;
	for (int i=0; i<2048; i++) fVec41[i] = 0;
	for (int i=0; i<2; i++) fRec115[i] = 0;
	for (int i=0; i<2; i++) fRec118[i] = 0;
	for (int i=0; i<2048; i++) fVec42[i] = 0;
	for (int i=0; i<2; i++) fRec117[i] = 0;
	for (int i=0; i<2; i++) fRec120[i] = 0;
	for (int i=0; i<2048; i++) fVec43[i] = 0;
	for (int i=0; i<2; i++) fRec119[i] = 0;
	for (int i=0; i<2; i++) fRec122[i] = 0;
	for (int i=0; i<2048; i++) fVec44[i] = 0;
	for (int i=0; i<2; i++) fRec121[i] = 0;
	for (int i=0; i<2; i++) fRec124[i] = 0;
	for (int i=0; i<2048; i++) fVec45[i] = 0;
	for (int i=0; i<2; i++) fRec123[i] = 0;
	for (int i=0; i<2; i++) fRec126[i] = 0;
	for (int i=0; i<2048; i++) fVec46[i] = 0;
	for (int i=0; i<2; i++) fRec125[i] = 0;
	for (int i=0; i<2; i++) fRec128[i] = 0;
	for (int i=0; i<2048; i++) fVec47[i] = 0;
	for (int i=0; i<2; i++) fRec127[i] = 0;
	for (int i=0; i<1024; i++) fVec48[i] = 0;
	for (int i=0; i<2; i++) fRec111[i] = 0;
	for (int i=0; i<512; i++) fVec49[i] = 0;
	for (int i=0; i<2; i++) fRec109[i] = 0;
	for (int i=0; i<512; i++) fVec50[i] = 0;
	for (int i=0; i<2; i++) fRec107[i] = 0;
	for (int i=0; i<256; i++) fVec51[i] = 0;
	for (int i=0; i<2; i++) fRec105[i] = 0;
	for (int i=0; i<2; i++) fRec97[i] = 0;
	for (int i=0; i<2; i++) iRec98[i] = 0;
	for (int i=0; i<2; i++) fRec99[i] = 0;
	for (int i=0; i<2; i++) fRec137[i] = 0;
	for (int i=0; i<3; i++) fRec136[i] = 0;
	for (int i=0; i<3; i++) fRec135[i] = 0;
	for (int i=0; i<3; i++) fRec134[i] = 0;
	for (int i=0; i<3; i++) fRec133[i] = 0;
	for (int i=0; i<2; i++) fRec147[i] = 0;
	for (int i=0; i<2048; i++) fVec52[i] = 0;
	for (int i=0; i<2; i++) fRec146[i] = 0;
	for (int i=0; i<2; i++) fRec149[i] = 0;
	for (int i=0; i<2048; i++) fVec53[i] = 0;
	for (int i=0; i<2; i++) fRec148[i] = 0;
	for (int i=0; i<2; i++) fRec151[i] = 0;
	for (int i=0; i<2048; i++) fVec54[i] = 0;
	for (int i=0; i<2; i++) fRec150[i] = 0;
	for (int i=0; i<2; i++) fRec153[i] = 0;
	for (int i=0; i<2048; i++) fVec55[i] = 0;
	for (int i=0; i<2; i++) fRec152[i] = 0;
	for (int i=0; i<2; i++) fRec155[i] = 0;
	for (int i=0; i<2048; i++) fVec56[i] = 0;
	for (int i=0; i<2; i++) fRec154[i] = 0;
	for (int i=0; i<2; i++) fRec157[i] = 0;
	for (int i=0; i<2048; i++) fVec57[i] = 0;
	for (int i=0; i<2; i++) fRec156[i] = 0;
	for (int i=0; i<2; i++) fRec159[i] = 0;
	for (int i=0; i<2048; i++) fVec58[i] = 0;
	for (int i=0; i<2; i++) fRec158[i] = 0;
	for (int i=0; i<2; i++) fRec161[i] = 0;
	for (int i=0; i<2048; i++) fVec59[i] = 0;
	for (int i=0; i<2; i++) fRec160[i] = 0;
	for (int i=0; i<1024; i++) fVec60[i] = 0;
	for (int i=0; i<2; i++) fRec144[i] = 0;
	for (int i=0; i<512; i++) fVec61[i] = 0;
	for (int i=0; i<2; i++) fRec142[i] = 0;
	for (int i=0; i<512; i++) fVec62[i] = 0;
	for (int i=0; i<2; i++) fRec140[i] = 0;
	for (int i=0; i<256; i++) fVec63[i] = 0;
	for (int i=0; i<2; i++) fRec138[i] = 0;
	for (int i=0; i<2; i++) fRec129[i] = 0;
	for (int i=0; i<2; i++) iRec130[i] = 0;
	for (int i=0; i<2; i++) fRec131[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (1.0 / double(iConst0));
	fConst2 = (3.141592653589793 / double(iConst0));
	IOTA = 0;
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
#define fslider2 (*fslider2_)
#define fslider3 (*fslider3_)
#define fslider4 (*fslider4_)
#define fslider5 (*fslider5_)
#define fslider6 (*fslider6_)
#define fbargraph0 (*fbargraph0_)
#define fslider7 (*fslider7_)
#define fslider8 (*fslider8_)
#define fslider9 (*fslider9_)
#define fbargraph1 (*fbargraph1_)
#define fslider10 (*fslider10_)
#define fslider11 (*fslider11_)
#define fslider12 (*fslider12_)
#define fbargraph2 (*fbargraph2_)
#define fslider13 (*fslider13_)
#define fslider14 (*fslider14_)
#define fslider15 (*fslider15_)
#define fbargraph3 (*fbargraph3_)
#define fslider16 (*fslider16_)
#define fslider17 (*fslider17_)
#define fslider18 (*fslider18_)
#define fbargraph4 (*fbargraph4_)
	double 	fSlow0 = tan((fConst2 * double(fslider0)));
	double 	fSlow1 = (1.0 / faustpower<2>(fSlow0));
	double 	fSlow2 = (2 * (1 - fSlow1));
	double 	fSlow3 = (1.0 / fSlow0);
	double 	fSlow4 = (1 + ((fSlow3 - 1.0000000000000004) / fSlow0));
	double 	fSlow5 = (1 + ((fSlow3 + 1.0000000000000004) / fSlow0));
	double 	fSlow6 = (1.0 / fSlow5);
	double 	fSlow7 = tan((fConst2 * double(fslider1)));
	double 	fSlow8 = (1.0 / faustpower<2>(fSlow7));
	double 	fSlow9 = (2 * (1 - fSlow8));
	double 	fSlow10 = (1.0 / fSlow7);
	double 	fSlow11 = (1 + ((fSlow10 - 1.0000000000000004) / fSlow7));
	double 	fSlow12 = (1 + ((fSlow10 + 1.0000000000000004) / fSlow7));
	double 	fSlow13 = (1.0 / fSlow12);
	double 	fSlow14 = tan((fConst2 * double(fslider2)));
	double 	fSlow15 = (1.0 / faustpower<2>(fSlow14));
	double 	fSlow16 = (2 * (1 - fSlow15));
	double 	fSlow17 = (1.0 / fSlow14);
	double 	fSlow18 = (1 + ((fSlow17 - 1.0000000000000004) / fSlow14));
	double 	fSlow19 = (1 + ((fSlow17 + 1.0000000000000004) / fSlow14));
	double 	fSlow20 = (1.0 / fSlow19);
	double 	fSlow21 = tan((fConst2 * double(fslider3)));
	double 	fSlow22 = (1.0 / faustpower<2>(fSlow21));
	double 	fSlow23 = (2 * (1 - fSlow22));
	double 	fSlow24 = (1.0 / fSlow21);
	double 	fSlow25 = (1 + ((fSlow24 - 1.0000000000000004) / fSlow21));
	double 	fSlow26 = (1 + ((1.0000000000000004 + fSlow24) / fSlow21));
	double 	fSlow27 = (1.0 / fSlow26);
	double 	fSlow28 = (1 + fSlow24);
	double 	fSlow29 = (1.0 / fSlow28);
	double 	fSlow30 = (0 - ((1 - fSlow24) / fSlow28));
	double 	fSlow31 = (1 + fSlow17);
	double 	fSlow32 = (1.0 / fSlow31);
	double 	fSlow33 = (0 - ((1 - fSlow17) / fSlow31));
	double 	fSlow34 = (1 + fSlow10);
	double 	fSlow35 = (1.0 / fSlow34);
	double 	fSlow36 = (0 - ((1 - fSlow10) / fSlow34));
	double 	fSlow37 = (1 + fSlow3);
	double 	fSlow38 = (1.0 / fSlow37);
	double 	fSlow39 = (0 - ((1 - fSlow3) / fSlow37));
	double 	fSlow40 = double(fslider4);
	double 	fSlow41 = (1 - (0.01 * fSlow40));
	double 	fSlow42 = ((fSlow41 + (fSlow40 * (0.00015 + (0.01 * fSlow41)))) / fSlow5);
	double 	fSlow43 = double(fslider5);
	double 	fSlow44 = (1 - fSlow43);
	double 	fSlow45 = (0.7 + (0.28 * double(fslider6)));
	double 	fSlow46 = (0.00015 * (fSlow40 / fSlow5));
	double 	fSlow47 = (0 - fSlow3);
	double 	fSlow48 = (1.0 / (fSlow0 * fSlow12));
	double 	fSlow49 = (2 * (0 - fSlow1));
	double 	fSlow50 = double(fslider7);
	double 	fSlow51 = (1 - (0.01 * fSlow50));
	double 	fSlow52 = ((fSlow51 + (fSlow50 * (0.00015 + (0.01 * fSlow51)))) / fSlow5);
	double 	fSlow53 = double(fslider8);
	double 	fSlow54 = (1 - fSlow53);
	double 	fSlow55 = (0.7 + (0.28 * double(fslider9)));
	double 	fSlow56 = (0.00015 * (fSlow50 / fSlow5));
	double 	fSlow57 = (1 + ((fSlow3 - 1.0) / fSlow0));
	double 	fSlow58 = (1.0 / (1 + ((1.0 + fSlow3) / fSlow0)));
	double 	fSlow59 = (0 - fSlow10);
	double 	fSlow60 = (1.0 / (fSlow7 * fSlow19));
	double 	fSlow61 = (2 * (0 - fSlow8));
	double 	fSlow62 = double(fslider10);
	double 	fSlow63 = (1 - (0.01 * fSlow62));
	double 	fSlow64 = (fSlow63 + (fSlow62 * (0.00015 + (0.01 * fSlow63))));
	double 	fSlow65 = double(fslider11);
	double 	fSlow66 = (1 - fSlow65);
	double 	fSlow67 = (0.7 + (0.28 * double(fslider12)));
	double 	fSlow68 = (0.00015 * fSlow62);
	double 	fSlow69 = (1 + ((fSlow10 - 1.0) / fSlow7));
	double 	fSlow70 = (1.0 / (1 + ((1.0 + fSlow10) / fSlow7)));
	double 	fSlow71 = (0 - fSlow17);
	double 	fSlow72 = (1.0 / (fSlow14 * fSlow26));
	double 	fSlow73 = (2 * (0 - fSlow15));
	double 	fSlow74 = double(fslider13);
	double 	fSlow75 = (1 - (0.01 * fSlow74));
	double 	fSlow76 = (fSlow75 + (fSlow74 * (0.00015 + (0.01 * fSlow75))));
	double 	fSlow77 = double(fslider14);
	double 	fSlow78 = (1 - fSlow77);
	double 	fSlow79 = (0.7 + (0.28 * double(fslider15)));
	double 	fSlow80 = (0.00015 * fSlow74);
	double 	fSlow81 = (1 + ((fSlow17 - 1.0) / fSlow14));
	double 	fSlow82 = (1.0 / (1 + ((1.0 + fSlow17) / fSlow14)));
	double 	fSlow83 = (0 - fSlow24);
	double 	fSlow84 = (2 * (0 - fSlow22));
	double 	fSlow85 = double(fslider16);
	double 	fSlow86 = (1 - (0.01 * fSlow85));
	double 	fSlow87 = (fSlow86 + (fSlow85 * (0.00015 + (0.01 * fSlow86))));
	double 	fSlow88 = double(fslider17);
	double 	fSlow89 = (1 - fSlow88);
	double 	fSlow90 = (0.7 + (0.28 * double(fslider18)));
	double 	fSlow91 = (0.00015 * fSlow85);
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fVec0[0] = fTemp0;
		fRec11[0] = ((fSlow30 * fRec11[1]) + (fSlow29 * (fVec0[0] + fVec0[1])));
		fRec10[0] = (fRec11[0] - (fSlow27 * ((fSlow25 * fRec10[2]) + (fSlow23 * fRec10[1]))));
		double fTemp1 = (fRec10[2] + (fRec10[0] + (2 * fRec10[1])));
		double fTemp2 = (fSlow27 * fTemp1);
		fVec1[0] = fTemp2;
		fRec9[0] = ((fSlow33 * fRec9[1]) + (fSlow32 * (fVec1[0] + fVec1[1])));
		fRec8[0] = (fRec9[0] - (fSlow20 * ((fSlow18 * fRec8[2]) + (fSlow16 * fRec8[1]))));
		double fTemp3 = (fRec8[2] + (fRec8[0] + (2 * fRec8[1])));
		double fTemp4 = (fSlow20 * fTemp3);
		fVec2[0] = fTemp4;
		fRec7[0] = ((fSlow36 * fRec7[1]) + (fSlow35 * (fVec2[0] + fVec2[1])));
		fRec6[0] = (fRec7[0] - (fSlow13 * ((fSlow11 * fRec6[2]) + (fSlow9 * fRec6[1]))));
		double fTemp5 = (fRec6[2] + (fRec6[0] + (2 * fRec6[1])));
		double fTemp6 = (fSlow13 * fTemp5);
		fVec3[0] = fTemp6;
		fRec5[0] = ((fSlow39 * fRec5[1]) + (fSlow38 * (fVec3[0] + fVec3[1])));
		fRec4[0] = (fRec5[0] - (fSlow6 * ((fSlow4 * fRec4[2]) + (fSlow2 * fRec4[1]))));
		double fTemp7 = (fRec4[2] + (fRec4[0] + (2 * fRec4[1])));
		fRec21[0] = ((fSlow43 * fRec21[1]) + (fSlow44 * fRec20[1]));
		double fTemp8 = (fSlow46 * fTemp7);
		fVec4[IOTA&2047] = (fTemp8 + (fSlow45 * fRec21[0]));
		fRec20[0] = fVec4[(IOTA-1640)&2047];
		fRec23[0] = ((fSlow43 * fRec23[1]) + (fSlow44 * fRec22[1]));
		fVec5[IOTA&2047] = (fTemp8 + (fSlow45 * fRec23[0]));
		fRec22[0] = fVec5[(IOTA-1580)&2047];
		fRec25[0] = ((fSlow43 * fRec25[1]) + (fSlow44 * fRec24[1]));
		fVec6[IOTA&2047] = (fTemp8 + (fSlow45 * fRec25[0]));
		fRec24[0] = fVec6[(IOTA-1514)&2047];
		fRec27[0] = ((fSlow43 * fRec27[1]) + (fSlow44 * fRec26[1]));
		fVec7[IOTA&2047] = (fTemp8 + (fSlow45 * fRec27[0]));
		fRec26[0] = fVec7[(IOTA-1445)&2047];
		fRec29[0] = ((fSlow43 * fRec29[1]) + (fSlow44 * fRec28[1]));
		fVec8[IOTA&2047] = (fTemp8 + (fSlow45 * fRec29[0]));
		fRec28[0] = fVec8[(IOTA-1379)&2047];
		fRec31[0] = ((fSlow43 * fRec31[1]) + (fSlow44 * fRec30[1]));
		fVec9[IOTA&2047] = (fTemp8 + (fSlow45 * fRec31[0]));
		fRec30[0] = fVec9[(IOTA-1300)&2047];
		fRec33[0] = ((fSlow43 * fRec33[1]) + (fSlow44 * fRec32[1]));
		fVec10[IOTA&2047] = (fTemp8 + (fSlow45 * fRec33[0]));
		fRec32[0] = fVec10[(IOTA-1211)&2047];
		fRec35[0] = ((fSlow43 * fRec35[1]) + (fSlow44 * fRec34[1]));
		fVec11[IOTA&2047] = (fTemp8 + (fSlow45 * fRec35[0]));
		fRec34[0] = fVec11[(IOTA-1139)&2047];
		double fTemp9 = (((((((fRec34[0] + fRec32[0]) + fRec30[0]) + fRec28[0]) + fRec26[0]) + fRec24[0]) + fRec22[0]) + fRec20[0]);
		fVec12[IOTA&1023] = (fTemp9 + (0.5 * fRec18[1]));
		fRec18[0] = fVec12[(IOTA-579)&1023];
		double 	fRec19 = (0 - (fTemp9 - fRec18[1]));
		fVec13[IOTA&511] = (fRec19 + (0.5 * fRec16[1]));
		fRec16[0] = fVec13[(IOTA-464)&511];
		double 	fRec17 = (fRec16[1] - fRec19);
		fVec14[IOTA&511] = (fRec17 + (0.5 * fRec14[1]));
		fRec14[0] = fVec14[(IOTA-364)&511];
		double 	fRec15 = (fRec14[1] - fRec17);
		fVec15[IOTA&255] = (fRec15 + (0.5 * fRec12[1]));
		fRec12[0] = fVec15[(IOTA-248)&255];
		double 	fRec13 = (fRec12[1] - fRec15);
		double fTemp10 = (fRec13 + (fSlow42 * fTemp7));
		double 	fRec3 = max(fConst1, fabs(fTemp10));
		int iTemp11 = int((iRec1[1] < 4096));
		fRec0[0] = ((iTemp11)?max(fRec0[1], fRec3):fRec3);
		iRec1[0] = ((iTemp11)?(1 + iRec1[1]):1);
		fRec2[0] = ((iTemp11)?fRec2[1]:fRec0[1]);
		fbargraph0 = fRec2[0];
		fRec41[0] = ((fSlow39 * fRec41[1]) + (fSlow38 * ((fSlow48 * fTemp5) + (fSlow47 * fVec3[1]))));
		fRec40[0] = (fRec41[0] - (fSlow6 * ((fSlow4 * fRec40[2]) + (fSlow2 * fRec40[1]))));
		double fTemp12 = (((fSlow1 * fRec40[0]) + (fSlow49 * fRec40[1])) + (fSlow1 * fRec40[2]));
		fRec51[0] = ((fSlow53 * fRec51[1]) + (fSlow54 * fRec50[1]));
		double fTemp13 = (fSlow56 * fTemp12);
		fVec16[IOTA&2047] = (fTemp13 + (fSlow55 * fRec51[0]));
		fRec50[0] = fVec16[(IOTA-1640)&2047];
		fRec53[0] = ((fSlow53 * fRec53[1]) + (fSlow54 * fRec52[1]));
		fVec17[IOTA&2047] = (fTemp13 + (fSlow55 * fRec53[0]));
		fRec52[0] = fVec17[(IOTA-1580)&2047];
		fRec55[0] = ((fSlow53 * fRec55[1]) + (fSlow54 * fRec54[1]));
		fVec18[IOTA&2047] = (fTemp13 + (fSlow55 * fRec55[0]));
		fRec54[0] = fVec18[(IOTA-1514)&2047];
		fRec57[0] = ((fSlow53 * fRec57[1]) + (fSlow54 * fRec56[1]));
		fVec19[IOTA&2047] = (fTemp13 + (fSlow55 * fRec57[0]));
		fRec56[0] = fVec19[(IOTA-1445)&2047];
		fRec59[0] = ((fSlow53 * fRec59[1]) + (fSlow54 * fRec58[1]));
		fVec20[IOTA&2047] = (fTemp13 + (fSlow55 * fRec59[0]));
		fRec58[0] = fVec20[(IOTA-1379)&2047];
		fRec61[0] = ((fSlow53 * fRec61[1]) + (fSlow54 * fRec60[1]));
		fVec21[IOTA&2047] = (fTemp13 + (fSlow55 * fRec61[0]));
		fRec60[0] = fVec21[(IOTA-1300)&2047];
		fRec63[0] = ((fSlow53 * fRec63[1]) + (fSlow54 * fRec62[1]));
		fVec22[IOTA&2047] = (fTemp13 + (fSlow55 * fRec63[0]));
		fRec62[0] = fVec22[(IOTA-1211)&2047];
		fRec65[0] = ((fSlow53 * fRec65[1]) + (fSlow54 * fRec64[1]));
		fVec23[IOTA&2047] = (fTemp13 + (fSlow55 * fRec65[0]));
		fRec64[0] = fVec23[(IOTA-1139)&2047];
		double fTemp14 = (((((((fRec64[0] + fRec62[0]) + fRec60[0]) + fRec58[0]) + fRec56[0]) + fRec54[0]) + fRec52[0]) + fRec50[0]);
		fVec24[IOTA&1023] = (fTemp14 + (0.5 * fRec48[1]));
		fRec48[0] = fVec24[(IOTA-579)&1023];
		double 	fRec49 = (0 - (fTemp14 - fRec48[1]));
		fVec25[IOTA&511] = (fRec49 + (0.5 * fRec46[1]));
		fRec46[0] = fVec25[(IOTA-464)&511];
		double 	fRec47 = (fRec46[1] - fRec49);
		fVec26[IOTA&511] = (fRec47 + (0.5 * fRec44[1]));
		fRec44[0] = fVec26[(IOTA-364)&511];
		double 	fRec45 = (fRec44[1] - fRec47);
		fVec27[IOTA&255] = (fRec45 + (0.5 * fRec42[1]));
		fRec42[0] = fVec27[(IOTA-248)&255];
		double 	fRec43 = (fRec42[1] - fRec45);
		double fTemp15 = (fRec43 + (fSlow52 * fTemp12));
		double 	fRec39 = max(fConst1, fabs(fTemp15));
		int iTemp16 = int((iRec37[1] < 4096));
		fRec36[0] = ((iTemp16)?max(fRec36[1], fRec39):fRec39);
		iRec37[0] = ((iTemp16)?(1 + iRec37[1]):1);
		fRec38[0] = ((iTemp16)?fRec38[1]:fRec36[1]);
		fbargraph1 = fRec38[0];
		double fTemp17 = (fSlow2 * fRec70[1]);
		fRec72[0] = ((fSlow36 * fRec72[1]) + (fSlow35 * ((fSlow60 * fTemp3) + (fSlow59 * fVec2[1]))));
		fRec71[0] = (fRec72[0] - (fSlow13 * ((fSlow11 * fRec71[2]) + (fSlow9 * fRec71[1]))));
		fRec70[0] = ((fSlow13 * (((fSlow8 * fRec71[0]) + (fSlow61 * fRec71[1])) + (fSlow8 * fRec71[2]))) - (fSlow58 * ((fSlow57 * fRec70[2]) + fTemp17)));
		double fTemp18 = (fRec70[2] + (fSlow58 * (fTemp17 + (fSlow57 * fRec70[0]))));
		fRec82[0] = ((fSlow65 * fRec82[1]) + (fSlow66 * fRec81[1]));
		double fTemp19 = (fSlow68 * fTemp18);
		fVec28[IOTA&2047] = (fTemp19 + (fSlow67 * fRec82[0]));
		fRec81[0] = fVec28[(IOTA-1640)&2047];
		fRec84[0] = ((fSlow65 * fRec84[1]) + (fSlow66 * fRec83[1]));
		fVec29[IOTA&2047] = (fTemp19 + (fSlow67 * fRec84[0]));
		fRec83[0] = fVec29[(IOTA-1580)&2047];
		fRec86[0] = ((fSlow65 * fRec86[1]) + (fSlow66 * fRec85[1]));
		fVec30[IOTA&2047] = (fTemp19 + (fSlow67 * fRec86[0]));
		fRec85[0] = fVec30[(IOTA-1514)&2047];
		fRec88[0] = ((fSlow65 * fRec88[1]) + (fSlow66 * fRec87[1]));
		fVec31[IOTA&2047] = (fTemp19 + (fSlow67 * fRec88[0]));
		fRec87[0] = fVec31[(IOTA-1445)&2047];
		fRec90[0] = ((fSlow65 * fRec90[1]) + (fSlow66 * fRec89[1]));
		fVec32[IOTA&2047] = (fTemp19 + (fSlow67 * fRec90[0]));
		fRec89[0] = fVec32[(IOTA-1379)&2047];
		fRec92[0] = ((fSlow65 * fRec92[1]) + (fSlow66 * fRec91[1]));
		fVec33[IOTA&2047] = (fTemp19 + (fSlow67 * fRec92[0]));
		fRec91[0] = fVec33[(IOTA-1300)&2047];
		fRec94[0] = ((fSlow65 * fRec94[1]) + (fSlow66 * fRec93[1]));
		fVec34[IOTA&2047] = (fTemp19 + (fSlow67 * fRec94[0]));
		fRec93[0] = fVec34[(IOTA-1211)&2047];
		fRec96[0] = ((fSlow65 * fRec96[1]) + (fSlow66 * fRec95[1]));
		fVec35[IOTA&2047] = (fTemp19 + (fSlow67 * fRec96[0]));
		fRec95[0] = fVec35[(IOTA-1139)&2047];
		double fTemp20 = (((((((fRec95[0] + fRec93[0]) + fRec91[0]) + fRec89[0]) + fRec87[0]) + fRec85[0]) + fRec83[0]) + fRec81[0]);
		fVec36[IOTA&1023] = (fTemp20 + (0.5 * fRec79[1]));
		fRec79[0] = fVec36[(IOTA-579)&1023];
		double 	fRec80 = (0 - (fTemp20 - fRec79[1]));
		fVec37[IOTA&511] = (fRec80 + (0.5 * fRec77[1]));
		fRec77[0] = fVec37[(IOTA-464)&511];
		double 	fRec78 = (fRec77[1] - fRec80);
		fVec38[IOTA&511] = (fRec78 + (0.5 * fRec75[1]));
		fRec75[0] = fVec38[(IOTA-364)&511];
		double 	fRec76 = (fRec75[1] - fRec78);
		fVec39[IOTA&255] = (fRec76 + (0.5 * fRec73[1]));
		fRec73[0] = fVec39[(IOTA-248)&255];
		double 	fRec74 = (fRec73[1] - fRec76);
		double fTemp21 = (fRec74 + (fSlow64 * fTemp18));
		double 	fRec69 = max(fConst1, fabs(fTemp21));
		int iTemp22 = int((iRec67[1] < 4096));
		fRec66[0] = ((iTemp22)?max(fRec66[1], fRec69):fRec69);
		iRec67[0] = ((iTemp22)?(1 + iRec67[1]):1);
		fRec68[0] = ((iTemp22)?fRec68[1]:fRec66[1]);
		fbargraph2 = fRec68[0];
		double fTemp23 = (fSlow2 * fRec101[1]);
		double fTemp24 = (fSlow9 * fRec102[1]);
		fRec104[0] = ((fSlow33 * fRec104[1]) + (fSlow32 * ((fSlow72 * fTemp1) + (fSlow71 * fVec1[1]))));
		fRec103[0] = (fRec104[0] - (fSlow20 * ((fSlow18 * fRec103[2]) + (fSlow16 * fRec103[1]))));
		fRec102[0] = ((fSlow20 * (((fSlow15 * fRec103[0]) + (fSlow73 * fRec103[1])) + (fSlow15 * fRec103[2]))) - (fSlow70 * ((fSlow69 * fRec102[2]) + fTemp24)));
		fRec101[0] = ((fRec102[2] + (fSlow70 * (fTemp24 + (fSlow69 * fRec102[0])))) - (fSlow58 * ((fSlow57 * fRec101[2]) + fTemp23)));
		double fTemp25 = (fRec101[2] + (fSlow58 * (fTemp23 + (fSlow57 * fRec101[0]))));
		fRec114[0] = ((fSlow77 * fRec114[1]) + (fSlow78 * fRec113[1]));
		double fTemp26 = (fSlow80 * fTemp25);
		fVec40[IOTA&2047] = (fTemp26 + (fSlow79 * fRec114[0]));
		fRec113[0] = fVec40[(IOTA-1640)&2047];
		fRec116[0] = ((fSlow77 * fRec116[1]) + (fSlow78 * fRec115[1]));
		fVec41[IOTA&2047] = (fTemp26 + (fSlow79 * fRec116[0]));
		fRec115[0] = fVec41[(IOTA-1580)&2047];
		fRec118[0] = ((fSlow77 * fRec118[1]) + (fSlow78 * fRec117[1]));
		fVec42[IOTA&2047] = (fTemp26 + (fSlow79 * fRec118[0]));
		fRec117[0] = fVec42[(IOTA-1514)&2047];
		fRec120[0] = ((fSlow77 * fRec120[1]) + (fSlow78 * fRec119[1]));
		fVec43[IOTA&2047] = (fTemp26 + (fSlow79 * fRec120[0]));
		fRec119[0] = fVec43[(IOTA-1445)&2047];
		fRec122[0] = ((fSlow77 * fRec122[1]) + (fSlow78 * fRec121[1]));
		fVec44[IOTA&2047] = (fTemp26 + (fSlow79 * fRec122[0]));
		fRec121[0] = fVec44[(IOTA-1379)&2047];
		fRec124[0] = ((fSlow77 * fRec124[1]) + (fSlow78 * fRec123[1]));
		fVec45[IOTA&2047] = (fTemp26 + (fSlow79 * fRec124[0]));
		fRec123[0] = fVec45[(IOTA-1300)&2047];
		fRec126[0] = ((fSlow77 * fRec126[1]) + (fSlow78 * fRec125[1]));
		fVec46[IOTA&2047] = (fTemp26 + (fSlow79 * fRec126[0]));
		fRec125[0] = fVec46[(IOTA-1211)&2047];
		fRec128[0] = ((fSlow77 * fRec128[1]) + (fSlow78 * fRec127[1]));
		fVec47[IOTA&2047] = (fTemp26 + (fSlow79 * fRec128[0]));
		fRec127[0] = fVec47[(IOTA-1139)&2047];
		double fTemp27 = (((((((fRec127[0] + fRec125[0]) + fRec123[0]) + fRec121[0]) + fRec119[0]) + fRec117[0]) + fRec115[0]) + fRec113[0]);
		fVec48[IOTA&1023] = (fTemp27 + (0.5 * fRec111[1]));
		fRec111[0] = fVec48[(IOTA-579)&1023];
		double 	fRec112 = (0 - (fTemp27 - fRec111[1]));
		fVec49[IOTA&511] = (fRec112 + (0.5 * fRec109[1]));
		fRec109[0] = fVec49[(IOTA-464)&511];
		double 	fRec110 = (fRec109[1] - fRec112);
		fVec50[IOTA&511] = (fRec110 + (0.5 * fRec107[1]));
		fRec107[0] = fVec50[(IOTA-364)&511];
		double 	fRec108 = (fRec107[1] - fRec110);
		fVec51[IOTA&255] = (fRec108 + (0.5 * fRec105[1]));
		fRec105[0] = fVec51[(IOTA-248)&255];
		double 	fRec106 = (fRec105[1] - fRec108);
		double fTemp28 = (fRec106 + (fSlow76 * fTemp25));
		double 	fRec100 = max(fConst1, fabs(fTemp28));
		int iTemp29 = int((iRec98[1] < 4096));
		fRec97[0] = ((iTemp29)?max(fRec97[1], fRec100):fRec100);
		iRec98[0] = ((iTemp29)?(1 + iRec98[1]):1);
		fRec99[0] = ((iTemp29)?fRec99[1]:fRec97[1]);
		fbargraph3 = fRec99[0];
		double fTemp30 = (fSlow2 * fRec133[1]);
		double fTemp31 = (fSlow9 * fRec134[1]);
		double fTemp32 = (fSlow16 * fRec135[1]);
		fRec137[0] = ((fSlow30 * fRec137[1]) + (fSlow29 * ((fSlow24 * fVec0[0]) + (fSlow83 * fVec0[1]))));
		fRec136[0] = (fRec137[0] - (fSlow27 * ((fSlow25 * fRec136[2]) + (fSlow23 * fRec136[1]))));
		fRec135[0] = ((fSlow27 * (((fSlow22 * fRec136[0]) + (fSlow84 * fRec136[1])) + (fSlow22 * fRec136[2]))) - (fSlow82 * ((fSlow81 * fRec135[2]) + fTemp32)));
		fRec134[0] = ((fRec135[2] + (fSlow82 * (fTemp32 + (fSlow81 * fRec135[0])))) - (fSlow70 * ((fSlow69 * fRec134[2]) + fTemp31)));
		fRec133[0] = ((fRec134[2] + (fSlow70 * (fTemp31 + (fSlow69 * fRec134[0])))) - (fSlow58 * ((fSlow57 * fRec133[2]) + fTemp30)));
		double fTemp33 = (fRec133[2] + (fSlow58 * (fTemp30 + (fSlow57 * fRec133[0]))));
		fRec147[0] = ((fSlow88 * fRec147[1]) + (fSlow89 * fRec146[1]));
		double fTemp34 = (fSlow91 * fTemp33);
		fVec52[IOTA&2047] = (fTemp34 + (fSlow90 * fRec147[0]));
		fRec146[0] = fVec52[(IOTA-1640)&2047];
		fRec149[0] = ((fSlow88 * fRec149[1]) + (fSlow89 * fRec148[1]));
		fVec53[IOTA&2047] = (fTemp34 + (fSlow90 * fRec149[0]));
		fRec148[0] = fVec53[(IOTA-1580)&2047];
		fRec151[0] = ((fSlow88 * fRec151[1]) + (fSlow89 * fRec150[1]));
		fVec54[IOTA&2047] = (fTemp34 + (fSlow90 * fRec151[0]));
		fRec150[0] = fVec54[(IOTA-1514)&2047];
		fRec153[0] = ((fSlow88 * fRec153[1]) + (fSlow89 * fRec152[1]));
		fVec55[IOTA&2047] = (fTemp34 + (fSlow90 * fRec153[0]));
		fRec152[0] = fVec55[(IOTA-1445)&2047];
		fRec155[0] = ((fSlow88 * fRec155[1]) + (fSlow89 * fRec154[1]));
		fVec56[IOTA&2047] = (fTemp34 + (fSlow90 * fRec155[0]));
		fRec154[0] = fVec56[(IOTA-1379)&2047];
		fRec157[0] = ((fSlow88 * fRec157[1]) + (fSlow89 * fRec156[1]));
		fVec57[IOTA&2047] = (fTemp34 + (fSlow90 * fRec157[0]));
		fRec156[0] = fVec57[(IOTA-1300)&2047];
		fRec159[0] = ((fSlow88 * fRec159[1]) + (fSlow89 * fRec158[1]));
		fVec58[IOTA&2047] = (fTemp34 + (fSlow90 * fRec159[0]));
		fRec158[0] = fVec58[(IOTA-1211)&2047];
		fRec161[0] = ((fSlow88 * fRec161[1]) + (fSlow89 * fRec160[1]));
		fVec59[IOTA&2047] = (fTemp34 + (fSlow90 * fRec161[0]));
		fRec160[0] = fVec59[(IOTA-1139)&2047];
		double fTemp35 = (((((((fRec160[0] + fRec158[0]) + fRec156[0]) + fRec154[0]) + fRec152[0]) + fRec150[0]) + fRec148[0]) + fRec146[0]);
		fVec60[IOTA&1023] = (fTemp35 + (0.5 * fRec144[1]));
		fRec144[0] = fVec60[(IOTA-579)&1023];
		double 	fRec145 = (0 - (fTemp35 - fRec144[1]));
		fVec61[IOTA&511] = (fRec145 + (0.5 * fRec142[1]));
		fRec142[0] = fVec61[(IOTA-464)&511];
		double 	fRec143 = (fRec142[1] - fRec145);
		fVec62[IOTA&511] = (fRec143 + (0.5 * fRec140[1]));
		fRec140[0] = fVec62[(IOTA-364)&511];
		double 	fRec141 = (fRec140[1] - fRec143);
		fVec63[IOTA&255] = (fRec141 + (0.5 * fRec138[1]));
		fRec138[0] = fVec63[(IOTA-248)&255];
		double 	fRec139 = (fRec138[1] - fRec141);
		double fTemp36 = (fRec139 + (fSlow87 * fTemp33));
		double 	fRec132 = max(fConst1, fabs(fTemp36));
		int iTemp37 = int((iRec130[1] < 4096));
		fRec129[0] = ((iTemp37)?max(fRec129[1], fRec132):fRec132);
		iRec130[0] = ((iTemp37)?(1 + iRec130[1]):1);
		fRec131[0] = ((iTemp37)?fRec131[1]:fRec129[1]);
		fbargraph4 = fRec131[0];
		output0[i] = (FAUSTFLOAT)((((fTemp36 + fTemp28) + fTemp21) + fTemp15) + fTemp10);
		// post processing
		fRec131[1] = fRec131[0];
		iRec130[1] = iRec130[0];
		fRec129[1] = fRec129[0];
		fRec138[1] = fRec138[0];
		fRec140[1] = fRec140[0];
		fRec142[1] = fRec142[0];
		fRec144[1] = fRec144[0];
		fRec160[1] = fRec160[0];
		fRec161[1] = fRec161[0];
		fRec158[1] = fRec158[0];
		fRec159[1] = fRec159[0];
		fRec156[1] = fRec156[0];
		fRec157[1] = fRec157[0];
		fRec154[1] = fRec154[0];
		fRec155[1] = fRec155[0];
		fRec152[1] = fRec152[0];
		fRec153[1] = fRec153[0];
		fRec150[1] = fRec150[0];
		fRec151[1] = fRec151[0];
		fRec148[1] = fRec148[0];
		fRec149[1] = fRec149[0];
		fRec146[1] = fRec146[0];
		fRec147[1] = fRec147[0];
		fRec133[2] = fRec133[1]; fRec133[1] = fRec133[0];
		fRec134[2] = fRec134[1]; fRec134[1] = fRec134[0];
		fRec135[2] = fRec135[1]; fRec135[1] = fRec135[0];
		fRec136[2] = fRec136[1]; fRec136[1] = fRec136[0];
		fRec137[1] = fRec137[0];
		fRec99[1] = fRec99[0];
		iRec98[1] = iRec98[0];
		fRec97[1] = fRec97[0];
		fRec105[1] = fRec105[0];
		fRec107[1] = fRec107[0];
		fRec109[1] = fRec109[0];
		fRec111[1] = fRec111[0];
		fRec127[1] = fRec127[0];
		fRec128[1] = fRec128[0];
		fRec125[1] = fRec125[0];
		fRec126[1] = fRec126[0];
		fRec123[1] = fRec123[0];
		fRec124[1] = fRec124[0];
		fRec121[1] = fRec121[0];
		fRec122[1] = fRec122[0];
		fRec119[1] = fRec119[0];
		fRec120[1] = fRec120[0];
		fRec117[1] = fRec117[0];
		fRec118[1] = fRec118[0];
		fRec115[1] = fRec115[0];
		fRec116[1] = fRec116[0];
		fRec113[1] = fRec113[0];
		fRec114[1] = fRec114[0];
		fRec101[2] = fRec101[1]; fRec101[1] = fRec101[0];
		fRec102[2] = fRec102[1]; fRec102[1] = fRec102[0];
		fRec103[2] = fRec103[1]; fRec103[1] = fRec103[0];
		fRec104[1] = fRec104[0];
		fRec68[1] = fRec68[0];
		iRec67[1] = iRec67[0];
		fRec66[1] = fRec66[0];
		fRec73[1] = fRec73[0];
		fRec75[1] = fRec75[0];
		fRec77[1] = fRec77[0];
		fRec79[1] = fRec79[0];
		fRec95[1] = fRec95[0];
		fRec96[1] = fRec96[0];
		fRec93[1] = fRec93[0];
		fRec94[1] = fRec94[0];
		fRec91[1] = fRec91[0];
		fRec92[1] = fRec92[0];
		fRec89[1] = fRec89[0];
		fRec90[1] = fRec90[0];
		fRec87[1] = fRec87[0];
		fRec88[1] = fRec88[0];
		fRec85[1] = fRec85[0];
		fRec86[1] = fRec86[0];
		fRec83[1] = fRec83[0];
		fRec84[1] = fRec84[0];
		fRec81[1] = fRec81[0];
		fRec82[1] = fRec82[0];
		fRec70[2] = fRec70[1]; fRec70[1] = fRec70[0];
		fRec71[2] = fRec71[1]; fRec71[1] = fRec71[0];
		fRec72[1] = fRec72[0];
		fRec38[1] = fRec38[0];
		iRec37[1] = iRec37[0];
		fRec36[1] = fRec36[0];
		fRec42[1] = fRec42[0];
		fRec44[1] = fRec44[0];
		fRec46[1] = fRec46[0];
		fRec48[1] = fRec48[0];
		fRec64[1] = fRec64[0];
		fRec65[1] = fRec65[0];
		fRec62[1] = fRec62[0];
		fRec63[1] = fRec63[0];
		fRec60[1] = fRec60[0];
		fRec61[1] = fRec61[0];
		fRec58[1] = fRec58[0];
		fRec59[1] = fRec59[0];
		fRec56[1] = fRec56[0];
		fRec57[1] = fRec57[0];
		fRec54[1] = fRec54[0];
		fRec55[1] = fRec55[0];
		fRec52[1] = fRec52[0];
		fRec53[1] = fRec53[0];
		fRec50[1] = fRec50[0];
		fRec51[1] = fRec51[0];
		fRec40[2] = fRec40[1]; fRec40[1] = fRec40[0];
		fRec41[1] = fRec41[0];
		fRec2[1] = fRec2[0];
		iRec1[1] = iRec1[0];
		fRec0[1] = fRec0[0];
		fRec12[1] = fRec12[0];
		fRec14[1] = fRec14[0];
		fRec16[1] = fRec16[0];
		fRec18[1] = fRec18[0];
		fRec34[1] = fRec34[0];
		fRec35[1] = fRec35[0];
		fRec32[1] = fRec32[0];
		fRec33[1] = fRec33[0];
		fRec30[1] = fRec30[0];
		fRec31[1] = fRec31[0];
		fRec28[1] = fRec28[0];
		fRec29[1] = fRec29[0];
		fRec26[1] = fRec26[0];
		fRec27[1] = fRec27[0];
		fRec24[1] = fRec24[0];
		fRec25[1] = fRec25[0];
		fRec22[1] = fRec22[0];
		fRec23[1] = fRec23[0];
		fRec20[1] = fRec20[0];
		IOTA = IOTA+1;
		fRec21[1] = fRec21[0];
		fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fVec3[1] = fVec3[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec7[1] = fRec7[0];
		fVec2[1] = fVec2[0];
		fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
		fRec9[1] = fRec9[0];
		fVec1[1] = fVec1[0];
		fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		fVec0[1] = fVec0[0];
	}
#undef fslider0
#undef fslider1
#undef fslider2
#undef fslider3
#undef fslider4
#undef fslider5
#undef fslider6
#undef fbargraph0
#undef fslider7
#undef fslider8
#undef fslider9
#undef fbargraph1
#undef fslider10
#undef fslider11
#undef fslider12
#undef fbargraph2
#undef fslider13
#undef fslider14
#undef fslider15
#undef fbargraph3
#undef fslider16
#undef fslider17
#undef fslider18
#undef fbargraph4
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case ROOMSIZE1: 
		fslider6_ = (float*)data; // , 0.5, 0.0, 1.0, 0.025 
		break;
	case ROOMSIZE2: 
		fslider9_ = (float*)data; // , 0.5, 0.0, 1.0, 0.025 
		break;
	case ROOMSIZE3: 
		fslider12_ = (float*)data; // , 0.5, 0.0, 1.0, 0.025 
		break;
	case ROOMSIZE4: 
		fslider15_ = (float*)data; // , 0.5, 0.0, 1.0, 0.025 
		break;
	case ROOMSIZE5: 
		fslider18_ = (float*)data; // , 0.5, 0.0, 1.0, 0.025 
		break;
	case CROSSOVER_B1_B2: 
		fslider0_ = (float*)data; // , 8e+01, 2e+01, 2e+04, 1.08 
		break;
	case CROSSOVER_B2_B3: 
		fslider1_ = (float*)data; // , 2.1e+02, 2e+01, 2e+04, 1.08 
		break;
	case CROSSOVER_B3_B4: 
		fslider2_ = (float*)data; // , 1.7e+03, 2e+01, 2e+04, 1.08 
		break;
	case CROSSOVER_B4_B5: 
		fslider3_ = (float*)data; // , 5e+03, 2e+01, 2e+04, 1.08 
		break;
	case DAMP1: 
		fslider5_ = (float*)data; // , 0.5, 0.0, 1.0, 0.025 
		break;
	case DAMP2: 
		fslider8_ = (float*)data; // , 0.5, 0.0, 1.0, 0.025 
		break;
	case DAMP3: 
		fslider11_ = (float*)data; // , 0.5, 0.0, 1.0, 0.025 
		break;
	case DAMP4: 
		fslider14_ = (float*)data; // , 0.5, 0.0, 1.0, 0.025 
		break;
	case DAMP5: 
		fslider17_ = (float*)data; // , 0.5, 0.0, 1.0, 0.025 
		break;
	case V1: 
		fbargraph0_ = (float*)data; // , -70.0, -70.0, 4.0, 0.00001 
		break;
	case V2: 
		fbargraph1_ = (float*)data; // , -70.0, -70.0, 4.0, 0.00001 
		break;
	case V3: 
		fbargraph2_ = (float*)data; // , -70.0, -70.0, 4.0, 0.00001 
		break;
	case V4: 
		fbargraph3_ = (float*)data; // , -70.0, -70.0, 4.0, 0.00001 
		break;
	case V5: 
		fbargraph4_ = (float*)data; // , -70.0, -70.0, 4.0, 0.00001 
		break;
	case WET_DRY1: 
		fslider4_ = (float*)data; // , 5e+01, 0.0, 1e+02, 1.0 
		break;
	case WET_DRY2: 
		fslider7_ = (float*)data; // , 5e+01, 0.0, 1e+02, 1.0 
		break;
	case WET_DRY3: 
		fslider10_ = (float*)data; // , 5e+01, 0.0, 1e+02, 1.0 
		break;
	case WET_DRY4: 
		fslider13_ = (float*)data; // , 5e+01, 0.0, 1e+02, 1.0 
		break;
	case WET_DRY5: 
		fslider16_ = (float*)data; // , 5e+01, 0.0, 1e+02, 1.0 
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
   ROOMSIZE1, 
   ROOMSIZE2, 
   ROOMSIZE3, 
   ROOMSIZE4, 
   ROOMSIZE5, 
   CROSSOVER_B1_B2, 
   CROSSOVER_B2_B3, 
   CROSSOVER_B3_B4, 
   CROSSOVER_B4_B5, 
   DAMP1, 
   DAMP2, 
   DAMP3, 
   DAMP4, 
   DAMP5, 
   V1, 
   V2, 
   V3, 
   V4, 
   V5, 
   WET_DRY1, 
   WET_DRY2, 
   WET_DRY3, 
   WET_DRY4, 
   WET_DRY5, 
} PortIndex;
*/

} // end namespace mbreverb
