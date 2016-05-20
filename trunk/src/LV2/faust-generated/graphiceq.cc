// generated from file '../src/LV2/faust/graphiceq.dsp' by dsp2cc:
// Code generated with Faust 0.9.73 (http://faust.grame.fr)


namespace graphiceq {

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
	double 	fConst68;
	double 	fConst69;
	double 	fConst70;
	double 	fVec0[2];
	double 	fConst71;
	double 	fConst72;
	double 	fConst73;
	double 	fRec23[2];
	double 	fRec22[3];
	double 	fVec1[2];
	double 	fConst74;
	double 	fConst75;
	double 	fConst76;
	double 	fRec21[2];
	double 	fRec20[3];
	double 	fVec2[2];
	double 	fConst77;
	double 	fConst78;
	double 	fConst79;
	double 	fRec19[2];
	double 	fRec18[3];
	double 	fVec3[2];
	double 	fConst80;
	double 	fConst81;
	double 	fConst82;
	double 	fRec17[2];
	double 	fRec16[3];
	double 	fVec4[2];
	double 	fConst83;
	double 	fConst84;
	double 	fConst85;
	double 	fRec15[2];
	double 	fRec14[3];
	double 	fVec5[2];
	double 	fConst86;
	double 	fConst87;
	double 	fConst88;
	double 	fRec13[2];
	double 	fRec12[3];
	double 	fVec6[2];
	double 	fConst89;
	double 	fConst90;
	double 	fConst91;
	double 	fRec11[2];
	double 	fRec10[3];
	double 	fVec7[2];
	double 	fConst92;
	double 	fConst93;
	double 	fConst94;
	double 	fRec9[2];
	double 	fRec8[3];
	double 	fVec8[2];
	double 	fConst95;
	double 	fConst96;
	double 	fConst97;
	double 	fRec7[2];
	double 	fRec6[3];
	double 	fVec9[2];
	double 	fConst98;
	double 	fConst99;
	double 	fConst100;
	double 	fRec5[2];
	double 	fRec4[3];
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec24[2];
	double 	fRec0[2];
	int 	iRec1[2];
	double 	fRec2[2];
	FAUSTFLOAT 	fbargraph0;
	FAUSTFLOAT	*fbargraph0_;
	double 	fConst101;
	double 	fRec30[2];
	double 	fRec29[3];
	double 	fConst102;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec31[2];
	double 	fRec25[2];
	int 	iRec26[2];
	double 	fRec27[2];
	FAUSTFLOAT 	fbargraph1;
	FAUSTFLOAT	*fbargraph1_;
	double 	fConst103;
	double 	fConst104;
	double 	fConst105;
	double 	fRec38[2];
	double 	fRec37[3];
	double 	fConst106;
	double 	fRec36[3];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec39[2];
	double 	fRec32[2];
	int 	iRec33[2];
	double 	fRec34[2];
	FAUSTFLOAT 	fbargraph2;
	FAUSTFLOAT	*fbargraph2_;
	double 	fConst107;
	double 	fConst108;
	double 	fConst109;
	double 	fRec47[2];
	double 	fRec46[3];
	double 	fConst110;
	double 	fRec45[3];
	double 	fRec44[3];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fRec48[2];
	double 	fRec40[2];
	int 	iRec41[2];
	double 	fRec42[2];
	FAUSTFLOAT 	fbargraph3;
	FAUSTFLOAT	*fbargraph3_;
	double 	fConst111;
	double 	fConst112;
	double 	fConst113;
	double 	fRec57[2];
	double 	fRec56[3];
	double 	fConst114;
	double 	fRec55[3];
	double 	fRec54[3];
	double 	fRec53[3];
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT	*fslider4_;
	double 	fRec58[2];
	double 	fRec49[2];
	int 	iRec50[2];
	double 	fRec51[2];
	FAUSTFLOAT 	fbargraph4;
	FAUSTFLOAT	*fbargraph4_;
	double 	fConst115;
	double 	fConst116;
	double 	fConst117;
	double 	fRec68[2];
	double 	fRec67[3];
	double 	fConst118;
	double 	fRec66[3];
	double 	fRec65[3];
	double 	fRec64[3];
	double 	fRec63[3];
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT	*fslider5_;
	double 	fRec69[2];
	double 	fRec59[2];
	int 	iRec60[2];
	double 	fRec61[2];
	FAUSTFLOAT 	fbargraph5;
	FAUSTFLOAT	*fbargraph5_;
	double 	fConst119;
	double 	fConst120;
	double 	fConst121;
	double 	fRec80[2];
	double 	fRec79[3];
	double 	fConst122;
	double 	fRec78[3];
	double 	fRec77[3];
	double 	fRec76[3];
	double 	fRec75[3];
	double 	fRec74[3];
	FAUSTFLOAT 	fslider6;
	FAUSTFLOAT	*fslider6_;
	double 	fRec81[2];
	double 	fRec70[2];
	int 	iRec71[2];
	double 	fRec72[2];
	FAUSTFLOAT 	fbargraph6;
	FAUSTFLOAT	*fbargraph6_;
	double 	fConst123;
	double 	fConst124;
	double 	fConst125;
	double 	fRec93[2];
	double 	fRec92[3];
	double 	fConst126;
	double 	fRec91[3];
	double 	fRec90[3];
	double 	fRec89[3];
	double 	fRec88[3];
	double 	fRec87[3];
	double 	fRec86[3];
	FAUSTFLOAT 	fslider7;
	FAUSTFLOAT	*fslider7_;
	double 	fRec94[2];
	double 	fRec82[2];
	int 	iRec83[2];
	double 	fRec84[2];
	FAUSTFLOAT 	fbargraph7;
	FAUSTFLOAT	*fbargraph7_;
	double 	fConst127;
	double 	fConst128;
	double 	fConst129;
	double 	fRec107[2];
	double 	fRec106[3];
	double 	fConst130;
	double 	fRec105[3];
	double 	fRec104[3];
	double 	fRec103[3];
	double 	fRec102[3];
	double 	fRec101[3];
	double 	fRec100[3];
	double 	fRec99[3];
	FAUSTFLOAT 	fslider8;
	FAUSTFLOAT	*fslider8_;
	double 	fRec108[2];
	double 	fRec95[2];
	int 	iRec96[2];
	double 	fRec97[2];
	FAUSTFLOAT 	fbargraph8;
	FAUSTFLOAT	*fbargraph8_;
	double 	fConst131;
	double 	fConst132;
	double 	fConst133;
	double 	fRec122[2];
	double 	fRec121[3];
	double 	fConst134;
	double 	fRec120[3];
	double 	fRec119[3];
	double 	fRec118[3];
	double 	fRec117[3];
	double 	fRec116[3];
	double 	fRec115[3];
	double 	fRec114[3];
	double 	fRec113[3];
	FAUSTFLOAT 	fslider9;
	FAUSTFLOAT	*fslider9_;
	double 	fRec123[2];
	double 	fRec109[2];
	int 	iRec110[2];
	double 	fRec111[2];
	FAUSTFLOAT 	fbargraph9;
	FAUSTFLOAT	*fbargraph9_;
	double 	fConst135;
	double 	fConst136;
	double 	fConst137;
	double 	fRec138[2];
	double 	fRec137[3];
	double 	fConst138;
	double 	fRec136[3];
	double 	fRec135[3];
	double 	fRec134[3];
	double 	fRec133[3];
	double 	fRec132[3];
	double 	fRec131[3];
	double 	fRec130[3];
	double 	fRec129[3];
	double 	fRec128[3];
	FAUSTFLOAT 	fslider10;
	FAUSTFLOAT	*fslider10_;
	double 	fRec139[2];
	double 	fRec124[2];
	int 	iRec125[2];
	double 	fRec126[2];
	FAUSTFLOAT 	fbargraph10;
	FAUSTFLOAT	*fbargraph10_;
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
	id = "graphiceq";
	name = N_("Graphic EQ");
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
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<3; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<3; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<3; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<3; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<3; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<3; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<3; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fVec7[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<3; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fVec8[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fVec9[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<3; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) iRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec30[i] = 0;
	for (int i=0; i<3; i++) fRec29[i] = 0;
	for (int i=0; i<2; i++) fRec31[i] = 0;
	for (int i=0; i<2; i++) fRec25[i] = 0;
	for (int i=0; i<2; i++) iRec26[i] = 0;
	for (int i=0; i<2; i++) fRec27[i] = 0;
	for (int i=0; i<2; i++) fRec38[i] = 0;
	for (int i=0; i<3; i++) fRec37[i] = 0;
	for (int i=0; i<3; i++) fRec36[i] = 0;
	for (int i=0; i<2; i++) fRec39[i] = 0;
	for (int i=0; i<2; i++) fRec32[i] = 0;
	for (int i=0; i<2; i++) iRec33[i] = 0;
	for (int i=0; i<2; i++) fRec34[i] = 0;
	for (int i=0; i<2; i++) fRec47[i] = 0;
	for (int i=0; i<3; i++) fRec46[i] = 0;
	for (int i=0; i<3; i++) fRec45[i] = 0;
	for (int i=0; i<3; i++) fRec44[i] = 0;
	for (int i=0; i<2; i++) fRec48[i] = 0;
	for (int i=0; i<2; i++) fRec40[i] = 0;
	for (int i=0; i<2; i++) iRec41[i] = 0;
	for (int i=0; i<2; i++) fRec42[i] = 0;
	for (int i=0; i<2; i++) fRec57[i] = 0;
	for (int i=0; i<3; i++) fRec56[i] = 0;
	for (int i=0; i<3; i++) fRec55[i] = 0;
	for (int i=0; i<3; i++) fRec54[i] = 0;
	for (int i=0; i<3; i++) fRec53[i] = 0;
	for (int i=0; i<2; i++) fRec58[i] = 0;
	for (int i=0; i<2; i++) fRec49[i] = 0;
	for (int i=0; i<2; i++) iRec50[i] = 0;
	for (int i=0; i<2; i++) fRec51[i] = 0;
	for (int i=0; i<2; i++) fRec68[i] = 0;
	for (int i=0; i<3; i++) fRec67[i] = 0;
	for (int i=0; i<3; i++) fRec66[i] = 0;
	for (int i=0; i<3; i++) fRec65[i] = 0;
	for (int i=0; i<3; i++) fRec64[i] = 0;
	for (int i=0; i<3; i++) fRec63[i] = 0;
	for (int i=0; i<2; i++) fRec69[i] = 0;
	for (int i=0; i<2; i++) fRec59[i] = 0;
	for (int i=0; i<2; i++) iRec60[i] = 0;
	for (int i=0; i<2; i++) fRec61[i] = 0;
	for (int i=0; i<2; i++) fRec80[i] = 0;
	for (int i=0; i<3; i++) fRec79[i] = 0;
	for (int i=0; i<3; i++) fRec78[i] = 0;
	for (int i=0; i<3; i++) fRec77[i] = 0;
	for (int i=0; i<3; i++) fRec76[i] = 0;
	for (int i=0; i<3; i++) fRec75[i] = 0;
	for (int i=0; i<3; i++) fRec74[i] = 0;
	for (int i=0; i<2; i++) fRec81[i] = 0;
	for (int i=0; i<2; i++) fRec70[i] = 0;
	for (int i=0; i<2; i++) iRec71[i] = 0;
	for (int i=0; i<2; i++) fRec72[i] = 0;
	for (int i=0; i<2; i++) fRec93[i] = 0;
	for (int i=0; i<3; i++) fRec92[i] = 0;
	for (int i=0; i<3; i++) fRec91[i] = 0;
	for (int i=0; i<3; i++) fRec90[i] = 0;
	for (int i=0; i<3; i++) fRec89[i] = 0;
	for (int i=0; i<3; i++) fRec88[i] = 0;
	for (int i=0; i<3; i++) fRec87[i] = 0;
	for (int i=0; i<3; i++) fRec86[i] = 0;
	for (int i=0; i<2; i++) fRec94[i] = 0;
	for (int i=0; i<2; i++) fRec82[i] = 0;
	for (int i=0; i<2; i++) iRec83[i] = 0;
	for (int i=0; i<2; i++) fRec84[i] = 0;
	for (int i=0; i<2; i++) fRec107[i] = 0;
	for (int i=0; i<3; i++) fRec106[i] = 0;
	for (int i=0; i<3; i++) fRec105[i] = 0;
	for (int i=0; i<3; i++) fRec104[i] = 0;
	for (int i=0; i<3; i++) fRec103[i] = 0;
	for (int i=0; i<3; i++) fRec102[i] = 0;
	for (int i=0; i<3; i++) fRec101[i] = 0;
	for (int i=0; i<3; i++) fRec100[i] = 0;
	for (int i=0; i<3; i++) fRec99[i] = 0;
	for (int i=0; i<2; i++) fRec108[i] = 0;
	for (int i=0; i<2; i++) fRec95[i] = 0;
	for (int i=0; i<2; i++) iRec96[i] = 0;
	for (int i=0; i<2; i++) fRec97[i] = 0;
	for (int i=0; i<2; i++) fRec122[i] = 0;
	for (int i=0; i<3; i++) fRec121[i] = 0;
	for (int i=0; i<3; i++) fRec120[i] = 0;
	for (int i=0; i<3; i++) fRec119[i] = 0;
	for (int i=0; i<3; i++) fRec118[i] = 0;
	for (int i=0; i<3; i++) fRec117[i] = 0;
	for (int i=0; i<3; i++) fRec116[i] = 0;
	for (int i=0; i<3; i++) fRec115[i] = 0;
	for (int i=0; i<3; i++) fRec114[i] = 0;
	for (int i=0; i<3; i++) fRec113[i] = 0;
	for (int i=0; i<2; i++) fRec123[i] = 0;
	for (int i=0; i<2; i++) fRec109[i] = 0;
	for (int i=0; i<2; i++) iRec110[i] = 0;
	for (int i=0; i<2; i++) fRec111[i] = 0;
	for (int i=0; i<2; i++) fRec138[i] = 0;
	for (int i=0; i<3; i++) fRec137[i] = 0;
	for (int i=0; i<3; i++) fRec136[i] = 0;
	for (int i=0; i<3; i++) fRec135[i] = 0;
	for (int i=0; i<3; i++) fRec134[i] = 0;
	for (int i=0; i<3; i++) fRec133[i] = 0;
	for (int i=0; i<3; i++) fRec132[i] = 0;
	for (int i=0; i<3; i++) fRec131[i] = 0;
	for (int i=0; i<3; i++) fRec130[i] = 0;
	for (int i=0; i<3; i++) fRec129[i] = 0;
	for (int i=0; i<3; i++) fRec128[i] = 0;
	for (int i=0; i<2; i++) fRec139[i] = 0;
	for (int i=0; i<2; i++) fRec124[i] = 0;
	for (int i=0; i<2; i++) iRec125[i] = 0;
	for (int i=0; i<2; i++) fRec126[i] = 0;
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
	fConst2 = tan((138.23007675795088 / double(iConst0)));
	fConst3 = (1.0 / faustpower<2>(fConst2));
	fConst4 = (2 * (1 - fConst3));
	fConst5 = (1.0 / fConst2);
	fConst6 = (1 + ((fConst5 - 1.0000000000000004) / fConst2));
	fConst7 = (1.0 / (1 + ((fConst5 + 1.0000000000000004) / fConst2)));
	fConst8 = tan((276.46015351590177 / double(iConst0)));
	fConst9 = (1.0 / faustpower<2>(fConst8));
	fConst10 = (2 * (1 - fConst9));
	fConst11 = (1.0 / fConst8);
	fConst12 = (1 + ((fConst11 - 1.0000000000000004) / fConst8));
	fConst13 = (1 + ((fConst11 + 1.0000000000000004) / fConst8));
	fConst14 = (1.0 / fConst13);
	fConst15 = tan((556.0618996853934 / double(iConst0)));
	fConst16 = (1.0 / faustpower<2>(fConst15));
	fConst17 = (2 * (1 - fConst16));
	fConst18 = (1.0 / fConst15);
	fConst19 = (1 + ((fConst18 - 1.0000000000000004) / fConst15));
	fConst20 = (1 + ((fConst18 + 1.0000000000000004) / fConst15));
	fConst21 = (1.0 / fConst20);
	fConst22 = tan((1112.1237993707869 / double(iConst0)));
	fConst23 = (1.0 / faustpower<2>(fConst22));
	fConst24 = (2 * (1 - fConst23));
	fConst25 = (1.0 / fConst22);
	fConst26 = (1 + ((fConst25 - 1.0000000000000004) / fConst22));
	fConst27 = (1 + ((fConst25 + 1.0000000000000004) / fConst22));
	fConst28 = (1.0 / fConst27);
	fConst29 = tan((2221.1060060879836 / double(iConst0)));
	fConst30 = (1.0 / faustpower<2>(fConst29));
	fConst31 = (2 * (1 - fConst30));
	fConst32 = (1.0 / fConst29);
	fConst33 = (1 + ((fConst32 - 1.0000000000000004) / fConst29));
	fConst34 = (1 + ((fConst32 + 1.0000000000000004) / fConst29));
	fConst35 = (1.0 / fConst34);
	fConst36 = tan((4442.212012175967 / double(iConst0)));
	fConst37 = (1.0 / faustpower<2>(fConst36));
	fConst38 = (2 * (1 - fConst37));
	fConst39 = (1.0 / fConst36);
	fConst40 = (1 + ((fConst39 - 1.0000000000000004) / fConst36));
	fConst41 = (1 + ((fConst39 + 1.0000000000000004) / fConst36));
	fConst42 = (1.0 / fConst41);
	fConst43 = tan((8884.424024351934 / double(iConst0)));
	fConst44 = (1.0 / faustpower<2>(fConst43));
	fConst45 = (2 * (1 - fConst44));
	fConst46 = (1.0 / fConst43);
	fConst47 = (1 + ((fConst46 - 1.0000000000000004) / fConst43));
	fConst48 = (1 + ((fConst46 + 1.0000000000000004) / fConst43));
	fConst49 = (1.0 / fConst48);
	fConst50 = tan((17771.98964135746 / double(iConst0)));
	fConst51 = (1.0 / faustpower<2>(fConst50));
	fConst52 = (2 * (1 - fConst51));
	fConst53 = (1.0 / fConst50);
	fConst54 = (1 + ((fConst53 - 1.0000000000000004) / fConst50));
	fConst55 = (1 + ((fConst53 + 1.0000000000000004) / fConst50));
	fConst56 = (1.0 / fConst55);
	fConst57 = tan((35763.890768466204 / double(iConst0)));
	fConst58 = (1.0 / faustpower<2>(fConst57));
	fConst59 = (2 * (1 - fConst58));
	fConst60 = (1.0 / fConst57);
	fConst61 = (1 + ((fConst60 - 1.0000000000000004) / fConst57));
	fConst62 = (1 + ((fConst60 + 1.0000000000000004) / fConst57));
	fConst63 = (1.0 / fConst62);
	fConst64 = tan((56894.24295651115 / double(iConst0)));
	fConst65 = (1.0 / faustpower<2>(fConst64));
	fConst66 = (2 * (1 - fConst65));
	fConst67 = (1.0 / fConst64);
	fConst68 = (1 + ((fConst67 - 1.0000000000000004) / fConst64));
	fConst69 = (1 + ((1.0000000000000004 + fConst67) / fConst64));
	fConst70 = (1.0 / fConst69);
	fConst71 = (1 + fConst67);
	fConst72 = (1.0 / fConst71);
	fConst73 = (0 - ((1 - fConst67) / fConst71));
	fConst74 = (1 + fConst60);
	fConst75 = (1.0 / (fConst74 * fConst69));
	fConst76 = (0 - ((1 - fConst60) / fConst74));
	fConst77 = (1 + fConst53);
	fConst78 = (1.0 / (fConst77 * fConst62));
	fConst79 = (0 - ((1 - fConst53) / fConst77));
	fConst80 = (1 + fConst46);
	fConst81 = (1.0 / (fConst80 * fConst55));
	fConst82 = (0 - ((1 - fConst46) / fConst80));
	fConst83 = (1 + fConst39);
	fConst84 = (1.0 / (fConst83 * fConst48));
	fConst85 = (0 - ((1 - fConst39) / fConst83));
	fConst86 = (1 + fConst32);
	fConst87 = (1.0 / (fConst86 * fConst41));
	fConst88 = (0 - ((1 - fConst32) / fConst86));
	fConst89 = (1 + fConst25);
	fConst90 = (1.0 / (fConst89 * fConst34));
	fConst91 = (0 - ((1 - fConst25) / fConst89));
	fConst92 = (1 + fConst18);
	fConst93 = (1.0 / (fConst92 * fConst27));
	fConst94 = (0 - ((1 - fConst18) / fConst92));
	fConst95 = (1 + fConst11);
	fConst96 = (1.0 / (fConst95 * fConst20));
	fConst97 = (0 - ((1 - fConst11) / fConst95));
	fConst98 = (1 + fConst5);
	fConst99 = (1.0 / (fConst98 * fConst13));
	fConst100 = (0 - ((1 - fConst5) / fConst98));
	fConst101 = (0 - fConst5);
	fConst102 = (2 * (0 - fConst3));
	fConst103 = (1 + ((fConst5 - 1.0) / fConst2));
	fConst104 = (1.0 / (1 + ((1.0 + fConst5) / fConst2)));
	fConst105 = (0 - fConst11);
	fConst106 = (2 * (0 - fConst9));
	fConst107 = (1 + ((fConst11 - 1.0) / fConst8));
	fConst108 = (1.0 / (1 + ((1.0 + fConst11) / fConst8)));
	fConst109 = (0 - fConst18);
	fConst110 = (2 * (0 - fConst16));
	fConst111 = (1 + ((fConst18 - 1.0) / fConst15));
	fConst112 = (1.0 / (1 + ((1.0 + fConst18) / fConst15)));
	fConst113 = (0 - fConst25);
	fConst114 = (2 * (0 - fConst23));
	fConst115 = (1 + ((fConst25 - 1.0) / fConst22));
	fConst116 = (1.0 / (1 + ((1.0 + fConst25) / fConst22)));
	fConst117 = (0 - fConst32);
	fConst118 = (2 * (0 - fConst30));
	fConst119 = (1 + ((fConst32 - 1.0) / fConst29));
	fConst120 = (1.0 / (1 + ((1.0 + fConst32) / fConst29)));
	fConst121 = (0 - fConst39);
	fConst122 = (2 * (0 - fConst37));
	fConst123 = (1 + ((fConst39 - 1.0) / fConst36));
	fConst124 = (1.0 / (1 + ((1.0 + fConst39) / fConst36)));
	fConst125 = (0 - fConst46);
	fConst126 = (2 * (0 - fConst44));
	fConst127 = (1 + ((fConst46 - 1.0) / fConst43));
	fConst128 = (1.0 / (1 + ((1.0 + fConst46) / fConst43)));
	fConst129 = (0 - fConst53);
	fConst130 = (2 * (0 - fConst51));
	fConst131 = (1 + ((fConst53 - 1.0) / fConst50));
	fConst132 = (1.0 / (1 + ((1.0 + fConst53) / fConst50)));
	fConst133 = (0 - fConst60);
	fConst134 = (2 * (0 - fConst58));
	fConst135 = (1 + ((fConst60 - 1.0) / fConst57));
	fConst136 = (1.0 / (1 + ((1.0 + fConst60) / fConst57)));
	fConst137 = (0 - fConst67);
	fConst138 = (2 * (0 - fConst65));
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fslider0 (*fslider0_)
#define fbargraph0 (*fbargraph0_)
#define fslider1 (*fslider1_)
#define fbargraph1 (*fbargraph1_)
#define fslider2 (*fslider2_)
#define fbargraph2 (*fbargraph2_)
#define fslider3 (*fslider3_)
#define fbargraph3 (*fbargraph3_)
#define fslider4 (*fslider4_)
#define fbargraph4 (*fbargraph4_)
#define fslider5 (*fslider5_)
#define fbargraph5 (*fbargraph5_)
#define fslider6 (*fslider6_)
#define fbargraph6 (*fbargraph6_)
#define fslider7 (*fslider7_)
#define fbargraph7 (*fbargraph7_)
#define fslider8 (*fslider8_)
#define fbargraph8 (*fbargraph8_)
#define fslider9 (*fslider9_)
#define fbargraph9 (*fbargraph9_)
#define fslider10 (*fslider10_)
#define fbargraph10 (*fbargraph10_)
	double 	fSlow0 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider0))));
	double 	fSlow1 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider1))));
	double 	fSlow2 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider2))));
	double 	fSlow3 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider3))));
	double 	fSlow4 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider4))));
	double 	fSlow5 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider5))));
	double 	fSlow6 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider6))));
	double 	fSlow7 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider7))));
	double 	fSlow8 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider8))));
	double 	fSlow9 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider9))));
	double 	fSlow10 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider10))));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fVec0[0] = fTemp0;
		fRec23[0] = ((fConst73 * fRec23[1]) + (fConst72 * (fVec0[0] + fVec0[1])));
		fRec22[0] = (fRec23[0] - (fConst70 * ((fConst68 * fRec22[2]) + (fConst66 * fRec22[1]))));
		double fTemp1 = (fRec22[2] + (fRec22[0] + (2 * fRec22[1])));
		fVec1[0] = fTemp1;
		fRec21[0] = ((fConst76 * fRec21[1]) + (fConst75 * (fVec1[0] + fVec1[1])));
		fRec20[0] = (fRec21[0] - (fConst63 * ((fConst61 * fRec20[2]) + (fConst59 * fRec20[1]))));
		double fTemp2 = (fRec20[2] + (fRec20[0] + (2 * fRec20[1])));
		fVec2[0] = fTemp2;
		fRec19[0] = ((fConst79 * fRec19[1]) + (fConst78 * (fVec2[0] + fVec2[1])));
		fRec18[0] = (fRec19[0] - (fConst56 * ((fConst54 * fRec18[2]) + (fConst52 * fRec18[1]))));
		double fTemp3 = (fRec18[2] + (fRec18[0] + (2 * fRec18[1])));
		fVec3[0] = fTemp3;
		fRec17[0] = ((fConst82 * fRec17[1]) + (fConst81 * (fVec3[0] + fVec3[1])));
		fRec16[0] = (fRec17[0] - (fConst49 * ((fConst47 * fRec16[2]) + (fConst45 * fRec16[1]))));
		double fTemp4 = (fRec16[2] + (fRec16[0] + (2 * fRec16[1])));
		fVec4[0] = fTemp4;
		fRec15[0] = ((fConst85 * fRec15[1]) + (fConst84 * (fVec4[0] + fVec4[1])));
		fRec14[0] = (fRec15[0] - (fConst42 * ((fConst40 * fRec14[2]) + (fConst38 * fRec14[1]))));
		double fTemp5 = (fRec14[2] + (fRec14[0] + (2 * fRec14[1])));
		fVec5[0] = fTemp5;
		fRec13[0] = ((fConst88 * fRec13[1]) + (fConst87 * (fVec5[0] + fVec5[1])));
		fRec12[0] = (fRec13[0] - (fConst35 * ((fConst33 * fRec12[2]) + (fConst31 * fRec12[1]))));
		double fTemp6 = (fRec12[2] + (fRec12[0] + (2 * fRec12[1])));
		fVec6[0] = fTemp6;
		fRec11[0] = ((fConst91 * fRec11[1]) + (fConst90 * (fVec6[0] + fVec6[1])));
		fRec10[0] = (fRec11[0] - (fConst28 * ((fConst26 * fRec10[2]) + (fConst24 * fRec10[1]))));
		double fTemp7 = (fRec10[2] + (fRec10[0] + (2 * fRec10[1])));
		fVec7[0] = fTemp7;
		fRec9[0] = ((fConst94 * fRec9[1]) + (fConst93 * (fVec7[0] + fVec7[1])));
		fRec8[0] = (fRec9[0] - (fConst21 * ((fConst19 * fRec8[2]) + (fConst17 * fRec8[1]))));
		double fTemp8 = (fRec8[2] + (fRec8[0] + (2 * fRec8[1])));
		fVec8[0] = fTemp8;
		fRec7[0] = ((fConst97 * fRec7[1]) + (fConst96 * (fVec8[0] + fVec8[1])));
		fRec6[0] = (fRec7[0] - (fConst14 * ((fConst12 * fRec6[2]) + (fConst10 * fRec6[1]))));
		double fTemp9 = (fRec6[2] + (fRec6[0] + (2 * fRec6[1])));
		fVec9[0] = fTemp9;
		fRec5[0] = ((fConst100 * fRec5[1]) + (fConst99 * (fVec9[0] + fVec9[1])));
		fRec4[0] = (fRec5[0] - (fConst7 * ((fConst6 * fRec4[2]) + (fConst4 * fRec4[1]))));
		fRec24[0] = ((0.999 * fRec24[1]) + fSlow0);
		double fTemp10 = (fConst7 * (fRec24[0] * (fRec4[2] + (fRec4[0] + (2 * fRec4[1])))));
		double 	fRec3 = max(fConst1, fabs(fTemp10));
		int iTemp11 = int((iRec1[1] < 4096));
		fRec0[0] = ((iTemp11)?max(fRec0[1], fRec3):fRec3);
		iRec1[0] = ((iTemp11)?(1 + iRec1[1]):1);
		fRec2[0] = ((iTemp11)?fRec2[1]:fRec0[1]);
		fbargraph0 = fRec2[0];
		fRec30[0] = ((fConst100 * fRec30[1]) + (fConst99 * ((fConst5 * fVec9[0]) + (fConst101 * fVec9[1]))));
		fRec29[0] = (fRec30[0] - (fConst7 * ((fConst6 * fRec29[2]) + (fConst4 * fRec29[1]))));
		fRec31[0] = ((0.999 * fRec31[1]) + fSlow1);
		double fTemp12 = (fConst7 * (fRec31[0] * (((fConst3 * fRec29[0]) + (fConst102 * fRec29[1])) + (fConst3 * fRec29[2]))));
		double 	fRec28 = max(fConst1, fabs(fTemp12));
		int iTemp13 = int((iRec26[1] < 4096));
		fRec25[0] = ((iTemp13)?max(fRec25[1], fRec28):fRec28);
		iRec26[0] = ((iTemp13)?(1 + iRec26[1]):1);
		fRec27[0] = ((iTemp13)?fRec27[1]:fRec25[1]);
		fbargraph1 = fRec27[0];
		double fTemp14 = (fConst4 * fRec36[1]);
		fRec38[0] = ((fConst97 * fRec38[1]) + (fConst96 * ((fConst11 * fVec8[0]) + (fConst105 * fVec8[1]))));
		fRec37[0] = (fRec38[0] - (fConst14 * ((fConst12 * fRec37[2]) + (fConst10 * fRec37[1]))));
		fRec36[0] = ((fConst14 * (((fConst9 * fRec37[0]) + (fConst106 * fRec37[1])) + (fConst9 * fRec37[2]))) - (fConst104 * ((fConst103 * fRec36[2]) + fTemp14)));
		fRec39[0] = ((0.999 * fRec39[1]) + fSlow2);
		double fTemp15 = (fRec39[0] * (fRec36[2] + (fConst104 * (fTemp14 + (fConst103 * fRec36[0])))));
		double 	fRec35 = max(fConst1, fabs(fTemp15));
		int iTemp16 = int((iRec33[1] < 4096));
		fRec32[0] = ((iTemp16)?max(fRec32[1], fRec35):fRec35);
		iRec33[0] = ((iTemp16)?(1 + iRec33[1]):1);
		fRec34[0] = ((iTemp16)?fRec34[1]:fRec32[1]);
		fbargraph2 = fRec34[0];
		double fTemp17 = (fConst4 * fRec44[1]);
		double fTemp18 = (fConst10 * fRec45[1]);
		fRec47[0] = ((fConst94 * fRec47[1]) + (fConst93 * ((fConst18 * fVec7[0]) + (fConst109 * fVec7[1]))));
		fRec46[0] = (fRec47[0] - (fConst21 * ((fConst19 * fRec46[2]) + (fConst17 * fRec46[1]))));
		fRec45[0] = ((fConst21 * (((fConst16 * fRec46[0]) + (fConst110 * fRec46[1])) + (fConst16 * fRec46[2]))) - (fConst108 * ((fConst107 * fRec45[2]) + fTemp18)));
		fRec44[0] = ((fRec45[2] + (fConst108 * (fTemp18 + (fConst107 * fRec45[0])))) - (fConst104 * ((fConst103 * fRec44[2]) + fTemp17)));
		fRec48[0] = ((0.999 * fRec48[1]) + fSlow3);
		double fTemp19 = (fRec48[0] * (fRec44[2] + (fConst104 * (fTemp17 + (fConst103 * fRec44[0])))));
		double 	fRec43 = max(fConst1, fabs(fTemp19));
		int iTemp20 = int((iRec41[1] < 4096));
		fRec40[0] = ((iTemp20)?max(fRec40[1], fRec43):fRec43);
		iRec41[0] = ((iTemp20)?(1 + iRec41[1]):1);
		fRec42[0] = ((iTemp20)?fRec42[1]:fRec40[1]);
		fbargraph3 = fRec42[0];
		double fTemp21 = (fConst4 * fRec53[1]);
		double fTemp22 = (fConst10 * fRec54[1]);
		double fTemp23 = (fConst17 * fRec55[1]);
		fRec57[0] = ((fConst91 * fRec57[1]) + (fConst90 * ((fConst25 * fVec6[0]) + (fConst113 * fVec6[1]))));
		fRec56[0] = (fRec57[0] - (fConst28 * ((fConst26 * fRec56[2]) + (fConst24 * fRec56[1]))));
		fRec55[0] = ((fConst28 * (((fConst23 * fRec56[0]) + (fConst114 * fRec56[1])) + (fConst23 * fRec56[2]))) - (fConst112 * ((fConst111 * fRec55[2]) + fTemp23)));
		fRec54[0] = ((fRec55[2] + (fConst112 * (fTemp23 + (fConst111 * fRec55[0])))) - (fConst108 * ((fConst107 * fRec54[2]) + fTemp22)));
		fRec53[0] = ((fRec54[2] + (fConst108 * (fTemp22 + (fConst107 * fRec54[0])))) - (fConst104 * ((fConst103 * fRec53[2]) + fTemp21)));
		fRec58[0] = ((0.999 * fRec58[1]) + fSlow4);
		double fTemp24 = (fRec58[0] * (fRec53[2] + (fConst104 * (fTemp21 + (fConst103 * fRec53[0])))));
		double 	fRec52 = max(fConst1, fabs(fTemp24));
		int iTemp25 = int((iRec50[1] < 4096));
		fRec49[0] = ((iTemp25)?max(fRec49[1], fRec52):fRec52);
		iRec50[0] = ((iTemp25)?(1 + iRec50[1]):1);
		fRec51[0] = ((iTemp25)?fRec51[1]:fRec49[1]);
		fbargraph4 = fRec51[0];
		double fTemp26 = (fConst4 * fRec63[1]);
		double fTemp27 = (fConst10 * fRec64[1]);
		double fTemp28 = (fConst17 * fRec65[1]);
		double fTemp29 = (fConst24 * fRec66[1]);
		fRec68[0] = ((fConst88 * fRec68[1]) + (fConst87 * ((fConst32 * fVec5[0]) + (fConst117 * fVec5[1]))));
		fRec67[0] = (fRec68[0] - (fConst35 * ((fConst33 * fRec67[2]) + (fConst31 * fRec67[1]))));
		fRec66[0] = ((fConst35 * (((fConst30 * fRec67[0]) + (fConst118 * fRec67[1])) + (fConst30 * fRec67[2]))) - (fConst116 * ((fConst115 * fRec66[2]) + fTemp29)));
		fRec65[0] = ((fRec66[2] + (fConst116 * (fTemp29 + (fConst115 * fRec66[0])))) - (fConst112 * ((fConst111 * fRec65[2]) + fTemp28)));
		fRec64[0] = ((fRec65[2] + (fConst112 * (fTemp28 + (fConst111 * fRec65[0])))) - (fConst108 * ((fConst107 * fRec64[2]) + fTemp27)));
		fRec63[0] = ((fRec64[2] + (fConst108 * (fTemp27 + (fConst107 * fRec64[0])))) - (fConst104 * ((fConst103 * fRec63[2]) + fTemp26)));
		fRec69[0] = ((0.999 * fRec69[1]) + fSlow5);
		double fTemp30 = (fRec69[0] * (fRec63[2] + (fConst104 * (fTemp26 + (fConst103 * fRec63[0])))));
		double 	fRec62 = max(fConst1, fabs(fTemp30));
		int iTemp31 = int((iRec60[1] < 4096));
		fRec59[0] = ((iTemp31)?max(fRec59[1], fRec62):fRec62);
		iRec60[0] = ((iTemp31)?(1 + iRec60[1]):1);
		fRec61[0] = ((iTemp31)?fRec61[1]:fRec59[1]);
		fbargraph5 = fRec61[0];
		double fTemp32 = (fConst4 * fRec74[1]);
		double fTemp33 = (fConst10 * fRec75[1]);
		double fTemp34 = (fConst17 * fRec76[1]);
		double fTemp35 = (fConst24 * fRec77[1]);
		double fTemp36 = (fConst31 * fRec78[1]);
		fRec80[0] = ((fConst85 * fRec80[1]) + (fConst84 * ((fConst39 * fVec4[0]) + (fConst121 * fVec4[1]))));
		fRec79[0] = (fRec80[0] - (fConst42 * ((fConst40 * fRec79[2]) + (fConst38 * fRec79[1]))));
		fRec78[0] = ((fConst42 * (((fConst37 * fRec79[0]) + (fConst122 * fRec79[1])) + (fConst37 * fRec79[2]))) - (fConst120 * ((fConst119 * fRec78[2]) + fTemp36)));
		fRec77[0] = ((fRec78[2] + (fConst120 * (fTemp36 + (fConst119 * fRec78[0])))) - (fConst116 * ((fConst115 * fRec77[2]) + fTemp35)));
		fRec76[0] = ((fRec77[2] + (fConst116 * (fTemp35 + (fConst115 * fRec77[0])))) - (fConst112 * ((fConst111 * fRec76[2]) + fTemp34)));
		fRec75[0] = ((fRec76[2] + (fConst112 * (fTemp34 + (fConst111 * fRec76[0])))) - (fConst108 * ((fConst107 * fRec75[2]) + fTemp33)));
		fRec74[0] = ((fRec75[2] + (fConst108 * (fTemp33 + (fConst107 * fRec75[0])))) - (fConst104 * ((fConst103 * fRec74[2]) + fTemp32)));
		fRec81[0] = ((0.999 * fRec81[1]) + fSlow6);
		double fTemp37 = (fRec81[0] * (fRec74[2] + (fConst104 * (fTemp32 + (fConst103 * fRec74[0])))));
		double 	fRec73 = max(fConst1, fabs(fTemp37));
		int iTemp38 = int((iRec71[1] < 4096));
		fRec70[0] = ((iTemp38)?max(fRec70[1], fRec73):fRec73);
		iRec71[0] = ((iTemp38)?(1 + iRec71[1]):1);
		fRec72[0] = ((iTemp38)?fRec72[1]:fRec70[1]);
		fbargraph6 = fRec72[0];
		double fTemp39 = (fConst4 * fRec86[1]);
		double fTemp40 = (fConst10 * fRec87[1]);
		double fTemp41 = (fConst17 * fRec88[1]);
		double fTemp42 = (fConst24 * fRec89[1]);
		double fTemp43 = (fConst31 * fRec90[1]);
		double fTemp44 = (fConst38 * fRec91[1]);
		fRec93[0] = ((fConst82 * fRec93[1]) + (fConst81 * ((fConst46 * fVec3[0]) + (fConst125 * fVec3[1]))));
		fRec92[0] = (fRec93[0] - (fConst49 * ((fConst47 * fRec92[2]) + (fConst45 * fRec92[1]))));
		fRec91[0] = ((fConst49 * (((fConst44 * fRec92[0]) + (fConst126 * fRec92[1])) + (fConst44 * fRec92[2]))) - (fConst124 * ((fConst123 * fRec91[2]) + fTemp44)));
		fRec90[0] = ((fRec91[2] + (fConst124 * (fTemp44 + (fConst123 * fRec91[0])))) - (fConst120 * ((fConst119 * fRec90[2]) + fTemp43)));
		fRec89[0] = ((fRec90[2] + (fConst120 * (fTemp43 + (fConst119 * fRec90[0])))) - (fConst116 * ((fConst115 * fRec89[2]) + fTemp42)));
		fRec88[0] = ((fRec89[2] + (fConst116 * (fTemp42 + (fConst115 * fRec89[0])))) - (fConst112 * ((fConst111 * fRec88[2]) + fTemp41)));
		fRec87[0] = ((fRec88[2] + (fConst112 * (fTemp41 + (fConst111 * fRec88[0])))) - (fConst108 * ((fConst107 * fRec87[2]) + fTemp40)));
		fRec86[0] = ((fRec87[2] + (fConst108 * (fTemp40 + (fConst107 * fRec87[0])))) - (fConst104 * ((fConst103 * fRec86[2]) + fTemp39)));
		fRec94[0] = ((0.999 * fRec94[1]) + fSlow7);
		double fTemp45 = (fRec94[0] * (fRec86[2] + (fConst104 * (fTemp39 + (fConst103 * fRec86[0])))));
		double 	fRec85 = max(fConst1, fabs(fTemp45));
		int iTemp46 = int((iRec83[1] < 4096));
		fRec82[0] = ((iTemp46)?max(fRec82[1], fRec85):fRec85);
		iRec83[0] = ((iTemp46)?(1 + iRec83[1]):1);
		fRec84[0] = ((iTemp46)?fRec84[1]:fRec82[1]);
		fbargraph7 = fRec84[0];
		double fTemp47 = (fConst4 * fRec99[1]);
		double fTemp48 = (fConst10 * fRec100[1]);
		double fTemp49 = (fConst17 * fRec101[1]);
		double fTemp50 = (fConst24 * fRec102[1]);
		double fTemp51 = (fConst31 * fRec103[1]);
		double fTemp52 = (fConst38 * fRec104[1]);
		double fTemp53 = (fConst45 * fRec105[1]);
		fRec107[0] = ((fConst79 * fRec107[1]) + (fConst78 * ((fConst53 * fVec2[0]) + (fConst129 * fVec2[1]))));
		fRec106[0] = (fRec107[0] - (fConst56 * ((fConst54 * fRec106[2]) + (fConst52 * fRec106[1]))));
		fRec105[0] = ((fConst56 * (((fConst51 * fRec106[0]) + (fConst130 * fRec106[1])) + (fConst51 * fRec106[2]))) - (fConst128 * ((fConst127 * fRec105[2]) + fTemp53)));
		fRec104[0] = ((fRec105[2] + (fConst128 * (fTemp53 + (fConst127 * fRec105[0])))) - (fConst124 * ((fConst123 * fRec104[2]) + fTemp52)));
		fRec103[0] = ((fRec104[2] + (fConst124 * (fTemp52 + (fConst123 * fRec104[0])))) - (fConst120 * ((fConst119 * fRec103[2]) + fTemp51)));
		fRec102[0] = ((fRec103[2] + (fConst120 * (fTemp51 + (fConst119 * fRec103[0])))) - (fConst116 * ((fConst115 * fRec102[2]) + fTemp50)));
		fRec101[0] = ((fRec102[2] + (fConst116 * (fTemp50 + (fConst115 * fRec102[0])))) - (fConst112 * ((fConst111 * fRec101[2]) + fTemp49)));
		fRec100[0] = ((fRec101[2] + (fConst112 * (fTemp49 + (fConst111 * fRec101[0])))) - (fConst108 * ((fConst107 * fRec100[2]) + fTemp48)));
		fRec99[0] = ((fRec100[2] + (fConst108 * (fTemp48 + (fConst107 * fRec100[0])))) - (fConst104 * ((fConst103 * fRec99[2]) + fTemp47)));
		fRec108[0] = ((0.999 * fRec108[1]) + fSlow8);
		double fTemp54 = (fRec108[0] * (fRec99[2] + (fConst104 * (fTemp47 + (fConst103 * fRec99[0])))));
		double 	fRec98 = max(fConst1, fabs(fTemp54));
		int iTemp55 = int((iRec96[1] < 4096));
		fRec95[0] = ((iTemp55)?max(fRec95[1], fRec98):fRec98);
		iRec96[0] = ((iTemp55)?(1 + iRec96[1]):1);
		fRec97[0] = ((iTemp55)?fRec97[1]:fRec95[1]);
		fbargraph8 = fRec97[0];
		double fTemp56 = (fConst4 * fRec113[1]);
		double fTemp57 = (fConst10 * fRec114[1]);
		double fTemp58 = (fConst17 * fRec115[1]);
		double fTemp59 = (fConst24 * fRec116[1]);
		double fTemp60 = (fConst31 * fRec117[1]);
		double fTemp61 = (fConst38 * fRec118[1]);
		double fTemp62 = (fConst45 * fRec119[1]);
		double fTemp63 = (fConst52 * fRec120[1]);
		fRec122[0] = ((fConst76 * fRec122[1]) + (fConst75 * ((fConst60 * fVec1[0]) + (fConst133 * fVec1[1]))));
		fRec121[0] = (fRec122[0] - (fConst63 * ((fConst61 * fRec121[2]) + (fConst59 * fRec121[1]))));
		fRec120[0] = ((fConst63 * (((fConst58 * fRec121[0]) + (fConst134 * fRec121[1])) + (fConst58 * fRec121[2]))) - (fConst132 * ((fConst131 * fRec120[2]) + fTemp63)));
		fRec119[0] = ((fRec120[2] + (fConst132 * (fTemp63 + (fConst131 * fRec120[0])))) - (fConst128 * ((fConst127 * fRec119[2]) + fTemp62)));
		fRec118[0] = ((fRec119[2] + (fConst128 * (fTemp62 + (fConst127 * fRec119[0])))) - (fConst124 * ((fConst123 * fRec118[2]) + fTemp61)));
		fRec117[0] = ((fRec118[2] + (fConst124 * (fTemp61 + (fConst123 * fRec118[0])))) - (fConst120 * ((fConst119 * fRec117[2]) + fTemp60)));
		fRec116[0] = ((fRec117[2] + (fConst120 * (fTemp60 + (fConst119 * fRec117[0])))) - (fConst116 * ((fConst115 * fRec116[2]) + fTemp59)));
		fRec115[0] = ((fRec116[2] + (fConst116 * (fTemp59 + (fConst115 * fRec116[0])))) - (fConst112 * ((fConst111 * fRec115[2]) + fTemp58)));
		fRec114[0] = ((fRec115[2] + (fConst112 * (fTemp58 + (fConst111 * fRec115[0])))) - (fConst108 * ((fConst107 * fRec114[2]) + fTemp57)));
		fRec113[0] = ((fRec114[2] + (fConst108 * (fTemp57 + (fConst107 * fRec114[0])))) - (fConst104 * ((fConst103 * fRec113[2]) + fTemp56)));
		fRec123[0] = ((0.999 * fRec123[1]) + fSlow9);
		double fTemp64 = (fRec123[0] * (fRec113[2] + (fConst104 * (fTemp56 + (fConst103 * fRec113[0])))));
		double 	fRec112 = max(fConst1, fabs(fTemp64));
		int iTemp65 = int((iRec110[1] < 4096));
		fRec109[0] = ((iTemp65)?max(fRec109[1], fRec112):fRec112);
		iRec110[0] = ((iTemp65)?(1 + iRec110[1]):1);
		fRec111[0] = ((iTemp65)?fRec111[1]:fRec109[1]);
		fbargraph9 = fRec111[0];
		double fTemp66 = (fConst4 * fRec128[1]);
		double fTemp67 = (fConst10 * fRec129[1]);
		double fTemp68 = (fConst17 * fRec130[1]);
		double fTemp69 = (fConst24 * fRec131[1]);
		double fTemp70 = (fConst31 * fRec132[1]);
		double fTemp71 = (fConst38 * fRec133[1]);
		double fTemp72 = (fConst45 * fRec134[1]);
		double fTemp73 = (fConst52 * fRec135[1]);
		double fTemp74 = (fConst59 * fRec136[1]);
		fRec138[0] = ((fConst73 * fRec138[1]) + (fConst72 * ((fConst67 * fVec0[0]) + (fConst137 * fVec0[1]))));
		fRec137[0] = (fRec138[0] - (fConst70 * ((fConst68 * fRec137[2]) + (fConst66 * fRec137[1]))));
		fRec136[0] = ((fConst70 * (((fConst65 * fRec137[0]) + (fConst138 * fRec137[1])) + (fConst65 * fRec137[2]))) - (fConst136 * ((fConst135 * fRec136[2]) + fTemp74)));
		fRec135[0] = ((fRec136[2] + (fConst136 * (fTemp74 + (fConst135 * fRec136[0])))) - (fConst132 * ((fConst131 * fRec135[2]) + fTemp73)));
		fRec134[0] = ((fRec135[2] + (fConst132 * (fTemp73 + (fConst131 * fRec135[0])))) - (fConst128 * ((fConst127 * fRec134[2]) + fTemp72)));
		fRec133[0] = ((fRec134[2] + (fConst128 * (fTemp72 + (fConst127 * fRec134[0])))) - (fConst124 * ((fConst123 * fRec133[2]) + fTemp71)));
		fRec132[0] = ((fRec133[2] + (fConst124 * (fTemp71 + (fConst123 * fRec133[0])))) - (fConst120 * ((fConst119 * fRec132[2]) + fTemp70)));
		fRec131[0] = ((fRec132[2] + (fConst120 * (fTemp70 + (fConst119 * fRec132[0])))) - (fConst116 * ((fConst115 * fRec131[2]) + fTemp69)));
		fRec130[0] = ((fRec131[2] + (fConst116 * (fTemp69 + (fConst115 * fRec131[0])))) - (fConst112 * ((fConst111 * fRec130[2]) + fTemp68)));
		fRec129[0] = ((fRec130[2] + (fConst112 * (fTemp68 + (fConst111 * fRec130[0])))) - (fConst108 * ((fConst107 * fRec129[2]) + fTemp67)));
		fRec128[0] = ((fRec129[2] + (fConst108 * (fTemp67 + (fConst107 * fRec129[0])))) - (fConst104 * ((fConst103 * fRec128[2]) + fTemp66)));
		fRec139[0] = ((0.999 * fRec139[1]) + fSlow10);
		double fTemp75 = (fRec139[0] * (fRec128[2] + (fConst104 * (fTemp66 + (fConst103 * fRec128[0])))));
		double 	fRec127 = max(fConst1, fabs(fTemp75));
		int iTemp76 = int((iRec125[1] < 4096));
		fRec124[0] = ((iTemp76)?max(fRec124[1], fRec127):fRec127);
		iRec125[0] = ((iTemp76)?(1 + iRec125[1]):1);
		fRec126[0] = ((iTemp76)?fRec126[1]:fRec124[1]);
		fbargraph10 = fRec126[0];
		output0[i] = (FAUSTFLOAT)((((((((((fTemp75 + fTemp64) + fTemp54) + fTemp45) + fTemp37) + fTemp30) + fTemp24) + fTemp19) + fTemp15) + fTemp12) + fTemp10);
		// post processing
		fRec126[1] = fRec126[0];
		iRec125[1] = iRec125[0];
		fRec124[1] = fRec124[0];
		fRec139[1] = fRec139[0];
		fRec128[2] = fRec128[1]; fRec128[1] = fRec128[0];
		fRec129[2] = fRec129[1]; fRec129[1] = fRec129[0];
		fRec130[2] = fRec130[1]; fRec130[1] = fRec130[0];
		fRec131[2] = fRec131[1]; fRec131[1] = fRec131[0];
		fRec132[2] = fRec132[1]; fRec132[1] = fRec132[0];
		fRec133[2] = fRec133[1]; fRec133[1] = fRec133[0];
		fRec134[2] = fRec134[1]; fRec134[1] = fRec134[0];
		fRec135[2] = fRec135[1]; fRec135[1] = fRec135[0];
		fRec136[2] = fRec136[1]; fRec136[1] = fRec136[0];
		fRec137[2] = fRec137[1]; fRec137[1] = fRec137[0];
		fRec138[1] = fRec138[0];
		fRec111[1] = fRec111[0];
		iRec110[1] = iRec110[0];
		fRec109[1] = fRec109[0];
		fRec123[1] = fRec123[0];
		fRec113[2] = fRec113[1]; fRec113[1] = fRec113[0];
		fRec114[2] = fRec114[1]; fRec114[1] = fRec114[0];
		fRec115[2] = fRec115[1]; fRec115[1] = fRec115[0];
		fRec116[2] = fRec116[1]; fRec116[1] = fRec116[0];
		fRec117[2] = fRec117[1]; fRec117[1] = fRec117[0];
		fRec118[2] = fRec118[1]; fRec118[1] = fRec118[0];
		fRec119[2] = fRec119[1]; fRec119[1] = fRec119[0];
		fRec120[2] = fRec120[1]; fRec120[1] = fRec120[0];
		fRec121[2] = fRec121[1]; fRec121[1] = fRec121[0];
		fRec122[1] = fRec122[0];
		fRec97[1] = fRec97[0];
		iRec96[1] = iRec96[0];
		fRec95[1] = fRec95[0];
		fRec108[1] = fRec108[0];
		fRec99[2] = fRec99[1]; fRec99[1] = fRec99[0];
		fRec100[2] = fRec100[1]; fRec100[1] = fRec100[0];
		fRec101[2] = fRec101[1]; fRec101[1] = fRec101[0];
		fRec102[2] = fRec102[1]; fRec102[1] = fRec102[0];
		fRec103[2] = fRec103[1]; fRec103[1] = fRec103[0];
		fRec104[2] = fRec104[1]; fRec104[1] = fRec104[0];
		fRec105[2] = fRec105[1]; fRec105[1] = fRec105[0];
		fRec106[2] = fRec106[1]; fRec106[1] = fRec106[0];
		fRec107[1] = fRec107[0];
		fRec84[1] = fRec84[0];
		iRec83[1] = iRec83[0];
		fRec82[1] = fRec82[0];
		fRec94[1] = fRec94[0];
		fRec86[2] = fRec86[1]; fRec86[1] = fRec86[0];
		fRec87[2] = fRec87[1]; fRec87[1] = fRec87[0];
		fRec88[2] = fRec88[1]; fRec88[1] = fRec88[0];
		fRec89[2] = fRec89[1]; fRec89[1] = fRec89[0];
		fRec90[2] = fRec90[1]; fRec90[1] = fRec90[0];
		fRec91[2] = fRec91[1]; fRec91[1] = fRec91[0];
		fRec92[2] = fRec92[1]; fRec92[1] = fRec92[0];
		fRec93[1] = fRec93[0];
		fRec72[1] = fRec72[0];
		iRec71[1] = iRec71[0];
		fRec70[1] = fRec70[0];
		fRec81[1] = fRec81[0];
		fRec74[2] = fRec74[1]; fRec74[1] = fRec74[0];
		fRec75[2] = fRec75[1]; fRec75[1] = fRec75[0];
		fRec76[2] = fRec76[1]; fRec76[1] = fRec76[0];
		fRec77[2] = fRec77[1]; fRec77[1] = fRec77[0];
		fRec78[2] = fRec78[1]; fRec78[1] = fRec78[0];
		fRec79[2] = fRec79[1]; fRec79[1] = fRec79[0];
		fRec80[1] = fRec80[0];
		fRec61[1] = fRec61[0];
		iRec60[1] = iRec60[0];
		fRec59[1] = fRec59[0];
		fRec69[1] = fRec69[0];
		fRec63[2] = fRec63[1]; fRec63[1] = fRec63[0];
		fRec64[2] = fRec64[1]; fRec64[1] = fRec64[0];
		fRec65[2] = fRec65[1]; fRec65[1] = fRec65[0];
		fRec66[2] = fRec66[1]; fRec66[1] = fRec66[0];
		fRec67[2] = fRec67[1]; fRec67[1] = fRec67[0];
		fRec68[1] = fRec68[0];
		fRec51[1] = fRec51[0];
		iRec50[1] = iRec50[0];
		fRec49[1] = fRec49[0];
		fRec58[1] = fRec58[0];
		fRec53[2] = fRec53[1]; fRec53[1] = fRec53[0];
		fRec54[2] = fRec54[1]; fRec54[1] = fRec54[0];
		fRec55[2] = fRec55[1]; fRec55[1] = fRec55[0];
		fRec56[2] = fRec56[1]; fRec56[1] = fRec56[0];
		fRec57[1] = fRec57[0];
		fRec42[1] = fRec42[0];
		iRec41[1] = iRec41[0];
		fRec40[1] = fRec40[0];
		fRec48[1] = fRec48[0];
		fRec44[2] = fRec44[1]; fRec44[1] = fRec44[0];
		fRec45[2] = fRec45[1]; fRec45[1] = fRec45[0];
		fRec46[2] = fRec46[1]; fRec46[1] = fRec46[0];
		fRec47[1] = fRec47[0];
		fRec34[1] = fRec34[0];
		iRec33[1] = iRec33[0];
		fRec32[1] = fRec32[0];
		fRec39[1] = fRec39[0];
		fRec36[2] = fRec36[1]; fRec36[1] = fRec36[0];
		fRec37[2] = fRec37[1]; fRec37[1] = fRec37[0];
		fRec38[1] = fRec38[0];
		fRec27[1] = fRec27[0];
		iRec26[1] = iRec26[0];
		fRec25[1] = fRec25[0];
		fRec31[1] = fRec31[0];
		fRec29[2] = fRec29[1]; fRec29[1] = fRec29[0];
		fRec30[1] = fRec30[0];
		fRec2[1] = fRec2[0];
		iRec1[1] = iRec1[0];
		fRec0[1] = fRec0[0];
		fRec24[1] = fRec24[0];
		fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fVec9[1] = fVec9[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec7[1] = fRec7[0];
		fVec8[1] = fVec8[0];
		fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
		fRec9[1] = fRec9[0];
		fVec7[1] = fVec7[0];
		fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		fVec6[1] = fVec6[0];
		fRec12[2] = fRec12[1]; fRec12[1] = fRec12[0];
		fRec13[1] = fRec13[0];
		fVec5[1] = fVec5[0];
		fRec14[2] = fRec14[1]; fRec14[1] = fRec14[0];
		fRec15[1] = fRec15[0];
		fVec4[1] = fVec4[0];
		fRec16[2] = fRec16[1]; fRec16[1] = fRec16[0];
		fRec17[1] = fRec17[0];
		fVec3[1] = fVec3[0];
		fRec18[2] = fRec18[1]; fRec18[1] = fRec18[0];
		fRec19[1] = fRec19[0];
		fVec2[1] = fVec2[0];
		fRec20[2] = fRec20[1]; fRec20[1] = fRec20[0];
		fRec21[1] = fRec21[0];
		fVec1[1] = fVec1[0];
		fRec22[2] = fRec22[1]; fRec22[1] = fRec22[0];
		fRec23[1] = fRec23[0];
		fVec0[1] = fVec0[0];
	}
#undef fslider0
#undef fbargraph0
#undef fslider1
#undef fbargraph1
#undef fslider2
#undef fbargraph2
#undef fslider3
#undef fbargraph3
#undef fslider4
#undef fbargraph4
#undef fslider5
#undef fbargraph5
#undef fslider6
#undef fbargraph6
#undef fslider7
#undef fbargraph7
#undef fslider8
#undef fbargraph8
#undef fslider9
#undef fbargraph9
#undef fslider10
#undef fbargraph10
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case G10: 
		fslider9_ = (float*)data; // , 0.0, -3e+01, 5.2, 0.1 
		break;
	case G11: 
		fslider10_ = (float*)data; // , 0.0, -3e+01, 5.2, 0.1 
		break;
	case G1: 
		fslider0_ = (float*)data; // , 0.0, -6e+01, 5.2, 0.1 
		break;
	case G2: 
		fslider1_ = (float*)data; // , 0.0, -3e+01, 5.2, 0.1 
		break;
	case G3: 
		fslider2_ = (float*)data; // , 0.0, -3e+01, 5.2, 0.1 
		break;
	case G4: 
		fslider3_ = (float*)data; // , 0.0, -3e+01, 5.2, 0.1 
		break;
	case G5: 
		fslider4_ = (float*)data; // , 0.0, -3e+01, 5.2, 0.1 
		break;
	case G6: 
		fslider5_ = (float*)data; // , 0.0, -3e+01, 5.2, 0.1 
		break;
	case G7: 
		fslider6_ = (float*)data; // , 0.0, -3e+01, 5.2, 0.1 
		break;
	case G8: 
		fslider7_ = (float*)data; // , 0.0, -3e+01, 5.2, 0.1 
		break;
	case G9: 
		fslider8_ = (float*)data; // , 0.0, -3e+01, 5.2, 0.1 
		break;
	case V10: 
		fbargraph9_ = (float*)data; // , -70.0, -70.0, 4.0, 0.00001 
		break;
	case V11: 
		fbargraph10_ = (float*)data; // , -70.0, -70.0, 4.0, 0.00001 
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
	case V6: 
		fbargraph5_ = (float*)data; // , -70.0, -70.0, 4.0, 0.00001 
		break;
	case V7: 
		fbargraph6_ = (float*)data; // , -70.0, -70.0, 4.0, 0.00001 
		break;
	case V8: 
		fbargraph7_ = (float*)data; // , -70.0, -70.0, 4.0, 0.00001 
		break;
	case V9: 
		fbargraph8_ = (float*)data; // , -70.0, -70.0, 4.0, 0.00001 
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
   G10, 
   G11, 
   G1, 
   G2, 
   G3, 
   G4, 
   G5, 
   G6, 
   G7, 
   G8, 
   G9, 
   V10, 
   V11, 
   V1, 
   V2, 
   V3, 
   V4, 
   V5, 
   V6, 
   V7, 
   V8, 
   V9, 
} PortIndex;
*/

} // end namespace graphiceq
