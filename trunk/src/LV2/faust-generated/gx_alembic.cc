// generated from file '../src/LV2/faust/gx_alembic.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace gx_alembic {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	double fConst0;
	double fConst1;
	double fConst2;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec0[2];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec1[2];
	double fConst3;
	double fConst4;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec3[2];
	double fConst5;
	double fConst6;
	double fConst7;
	double fConst8;
	double fConst9;
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fRec4[2];
	double fConst10;
	double fConst11;
	double fConst12;
	double fConst13;
	double fConst14;
	double fConst15;
	double fConst16;
	double fConst17;
	double fConst18;
	double fConst19;
	double fConst20;
	double fConst21;
	double fConst22;
	FAUSTFLOAT fVslider4;
	FAUSTFLOAT	*fVslider4_;
	double fRec5[2];
	double fConst23;
	double fConst24;
	double fConst25;
	double fConst26;
	double fConst27;
	double fConst28;
	double fConst29;
	double fConst30;
	double fConst31;
	double fConst32;
	double fConst33;
	double fConst34;
	double fConst35;
	double fConst36;
	double fConst37;
	double fConst38;
	double fConst39;
	double fConst40;
	double fConst41;
	double fConst42;
	double fConst43;
	double fConst44;
	double fConst45;
	double fConst46;
	double fConst47;
	double fConst48;
	double fConst49;
	double fConst50;
	double fConst51;
	double fConst52;
	double fConst53;
	double fConst54;
	double fConst55;
	double fConst56;
	double fConst57;
	double fConst58;
	double fConst59;
	double fConst60;
	double fConst61;
	double fConst62;
	double fConst63;
	double fConst64;
	double fConst65;
	double fConst66;
	double fConst67;
	double fConst68;
	double fConst69;
	double fConst70;
	double fConst71;
	double fConst72;
	double fConst73;
	double fConst74;
	double fConst75;
	double fConst76;
	double fConst77;
	double fConst78;
	double fConst79;
	double fConst80;
	double fConst81;
	double fConst82;
	double fConst83;
	double fConst84;
	double fConst85;
	double fConst86;
	double fConst87;
	double fConst88;
	double fConst89;
	double fConst90;
	double fConst91;
	double fConst92;
	double fConst93;
	double fConst94;
	double fConst95;
	double fConst96;
	double fConst97;
	double fConst98;
	double fConst99;
	double fConst100;
	double fConst101;
	double fConst102;
	double fConst103;
	double fConst104;
	double fConst105;
	double fConst106;
	double fConst107;
	double fConst108;
	double fConst109;
	double fConst110;
	double fConst111;
	double fConst112;
	double fConst113;
	double fConst114;
	double fConst115;
	double fConst116;
	double fConst117;
	double fConst118;
	double fConst119;
	double fConst120;
	double fConst121;
	double fConst122;
	double fConst123;
	double fConst124;
	double fConst125;
	double fConst126;
	double fConst127;
	double fConst128;
	double fConst129;
	double fConst130;
	double fConst131;
	double fConst132;
	double fConst133;
	double fConst134;
	double fConst135;
	double fConst136;
	double fConst137;
	double fConst138;
	double fConst139;
	double fConst140;
	double fConst141;
	double fConst142;
	double fConst143;
	double fConst144;
	double fConst145;
	double fConst146;
	double fConst147;
	double fConst148;
	double fConst149;
	double fConst150;
	double fConst151;
	double fConst152;
	double fConst153;
	double fConst154;
	double fConst155;
	double fConst156;
	double fConst157;
	double fConst158;
	double fConst159;
	double fConst160;
	double fConst161;
	double fConst162;
	double fConst163;
	double fConst164;
	double fConst165;
	double fConst166;
	double fConst167;
	double fConst168;
	double fConst169;
	double fConst170;
	double fConst171;
	double fConst172;
	double fConst173;
	double fConst174;
	double fConst175;
	double fConst176;
	double fConst177;
	double fConst178;
	double fConst179;
	double fConst180;
	double fConst181;
	double fConst182;
	double fConst183;
	double fConst184;
	double fConst185;
	double fConst186;
	double fConst187;
	double fConst188;
	double fConst189;
	double fConst190;
	double fConst191;
	double fConst192;
	double fConst193;
	double fConst194;
	double fConst195;
	double fConst196;
	double fConst197;
	double fConst198;
	double fConst199;
	double fConst200;
	double fConst201;
	double fConst202;
	double fConst203;
	double fConst204;
	double fConst205;
	double fConst206;
	double fConst207;
	double fConst208;
	double fConst209;
	double fConst210;
	double fConst211;
	double fConst212;
	double fConst213;
	double fConst214;
	double fConst215;
	double fConst216;
	double fConst217;
	double fConst218;
	double fConst219;
	double fConst220;
	double fConst221;
	double fConst222;
	double fConst223;
	double fConst224;
	double fConst225;
	double fConst226;
	double fConst227;
	double fConst228;
	double fConst229;
	double fConst230;
	double fConst231;
	double fConst232;
	double fConst233;
	double fConst234;
	double fConst235;
	double fConst236;
	double fConst237;
	double fConst238;
	double fConst239;
	double fConst240;
	double fConst241;
	double fConst242;
	double fConst243;
	double fConst244;
	double fConst245;
	double fConst246;
	double fConst247;
	double fConst248;
	double fConst249;
	double fConst250;
	double fConst251;
	double fConst252;
	double fConst253;
	double fConst254;
	double fConst255;
	double fConst256;
	double fConst257;
	double fConst258;
	double fConst259;
	double fConst260;
	double fConst261;
	double fConst262;
	double fConst263;
	double fConst264;
	double fConst265;
	double fConst266;
	double fConst267;
	double fConst268;
	double fConst269;
	double fConst270;
	double fConst271;
	double fConst272;
	double fConst273;
	double fConst274;
	double fConst275;
	double fConst276;
	double fConst277;
	double fConst278;
	double fConst279;
	double fConst280;
	double fConst281;
	double fConst282;
	double fConst283;
	double fConst284;
	double fConst285;
	double fConst286;
	double fConst287;
	double fConst288;
	double fConst289;
	double fConst290;
	double fRec2[6];
	double fConst291;
	double fConst292;
	double fConst293;
	double fConst294;
	double fConst295;
	double fConst296;
	double fConst297;
	double fConst298;
	double fConst299;
	double fConst300;
	double fConst301;
	double fConst302;
	double fConst303;
	double fConst304;
	double fConst305;
	double fConst306;
	double fConst307;
	double fConst308;
	double fConst309;
	double fConst310;
	double fConst311;
	double fConst312;
	double fConst313;
	double fConst314;
	double fConst315;
	double fConst316;
	double fConst317;
	double fConst318;
	double fConst319;
	double fConst320;
	double fConst321;
	double fConst322;
	double fConst323;
	double fConst324;
	double fConst325;
	double fConst326;
	double fConst327;
	double fConst328;
	double fConst329;
	double fConst330;
	double fConst331;
	double fConst332;
	double fConst333;
	double fConst334;
	double fConst335;
	double fConst336;
	double fConst337;
	double fConst338;

	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(uint32_t sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(uint32_t sample_rate, PluginLV2*);
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
	id = "alembic";
	name = N_("Alembic Preamp");
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec0[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec1[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec3[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fRec4[l3] = 0.0;
	for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) fRec5[l4] = 0.0;
	for (int l5 = 0; (l5 < 6); l5 = (l5 + 1)) fRec2[l5] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = mydsp_faustpower2_f(fConst0);
	fConst2 = (0.050000000000000003 * fConst1);
	fConst3 = (9.3476168267280999e-22 * fConst0);
	fConst4 = (fConst0 * ((fConst0 * ((fConst0 * (-2.7839098601865799e-18 - fConst3)) + 1.2795763483988699e-16)) + 4.3425020303467898e-15));
	fConst5 = (2.3320020406901101e-23 * fConst0);
	fConst6 = (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (-1.2633231515507101e-19 - fConst5)) + -4.69643971510767e-18)) + 8.52210149990995e-17)) + 1.4128042788285e-15));
	fConst7 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst5 + 1.2633231515507101e-19)) + 4.69643971510767e-18)) + -8.52210149990995e-17)) + -1.4128042788285e-15)) + -3.9909588087242801e-15);
	fConst8 = (2.49057817945703e-23 * fConst0);
	fConst9 = ((fConst0 * ((fConst0 * ((fConst0 * (-1.3492291258561499e-19 - fConst8)) + -5.0157976157349902e-18)) + 9.1016044019038295e-17)) + 1.50887496978884e-15);
	fConst10 = (4.9784602875504403e-24 * fConst0);
	fConst11 = ((fConst0 * ((fConst0 * ((fConst0 * (2.60634218706887e-20 - fConst10)) + 8.8419101327569207e-19)) + -1.30182230144389e-17)) + -1.2755064443094701e-16);
	fConst12 = (4.6614796699910497e-24 * fConst0);
	fConst13 = ((fConst0 * ((fConst0 * ((fConst0 * (2.4403953062442599e-20 - fConst12)) + 8.2789420718697798e-19)) + -1.2189347391796701e-17)) + -1.1942944235107401e-16);
	fConst14 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst12 + -2.4403953062442599e-20)) + -8.2789420718697798e-19)) + 1.2189347391796701e-17)) + 1.1942944235107401e-16);
	fConst15 = (5.53312035914695e-24 * fConst0);
	fConst16 = ((fConst0 * ((fConst0 * (fConst15 + 3.3324433674294899e-22)) + 1.6322909920366499e-21)) + -5.32793000964692e-21);
	fConst17 = (5.1808243063173699e-24 * fConst0);
	fConst18 = ((fConst0 * ((fConst0 * (fConst17 + 3.1202653253085101e-22)) + 1.52836235209424e-21)) + -4.9886985109053503e-21);
	fConst19 = ((fConst0 * ((fConst0 * (-3.1202653253085101e-22 - fConst17)) + -1.52836235209424e-21)) + 4.9886985109053503e-21);
	fConst20 = (8.7524502122922301e-22 * fConst0);
	fConst21 = (fConst0 * ((fConst0 * ((fConst0 * (-2.6066571724593401e-18 - fConst20)) + 1.1981051951300199e-16)) + 4.0660131370288298e-15));
	fConst22 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst20 + 2.6066571724593401e-18)) + -1.1981051951300199e-16)) + -4.0660131370288298e-15)) + -1.99547940436214e-14);
	fConst23 = (8.4329985537621802e-23 * fConst0);
	fConst24 = (fConst0 * ((fConst0 * ((fConst0 * (-2.15807364568921e-19 - fConst23)) + 4.3759098620589198e-18)) + 6.7766674993742604e-17));
	fConst25 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst23 + 2.15807364568921e-19)) + -4.3759098620589198e-18)) + -6.7766674993742604e-17)) + -1.5963835234897099e-16);
	fConst26 = (9.0064424554180099e-23 * fConst0);
	fConst27 = ((fConst0 * ((fConst0 * (-2.3048226535960802e-19 - fConst26)) + 4.6734717326789204e-18)) + 7.2374808893316998e-17);
	fConst28 = (2.3996757109106899e-24 * fConst0);
	fConst29 = ((fConst0 * ((fConst0 * ((fConst0 * (-1.1060317668611701e-20 - fConst28)) + -7.89937124628652e-20)) + 4.60313050181815e-19)) + 2.4039620203526901e-18);
	fConst30 = (2.2468873697665698e-24 * fConst0);
	fConst31 = ((fConst0 * ((fConst0 * ((fConst0 * (-1.0356102685966e-20 - fConst30)) + -7.3964150246128498e-20)) + 4.3100472863465798e-19)) + 2.2509007681204999e-18);
	fConst32 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst30 + 1.0356102685966e-20)) + 7.3964150246128498e-20)) + -4.3100472863465798e-19)) + -2.2509007681204999e-18);
	fConst33 = (5.8050582522179604e-25 * fConst0);
	fConst34 = ((fConst0 * ((fConst0 * (1.9792129164812199e-21 - fConst33)) + 1.1615299421015499e-20)) + -3.9965868588363503e-20);
	fConst35 = (5.4354478017022097e-25 * fConst0);
	fConst36 = ((fConst0 * ((fConst0 * (1.8531956146827899e-21 - fConst35)) + 1.08757485215501e-20)) + -3.7421225270003199e-20);
	fConst37 = ((fConst0 * ((fConst0 * (fConst35 + -1.8531956146827899e-21)) + -1.08757485215501e-20)) + 3.7421225270003199e-20);
	fConst38 = (4.1464701801556802e-25 * fConst0);
	fConst39 = ((fConst0 * (fConst38 + 4.3692898409429397e-24)) + 5.0082542090681003e-24);
	fConst40 = (3.8824627155015799e-25 * fConst0);
	fConst41 = ((fConst0 * (fConst40 + 4.0910953566881399e-24)) + 4.6893766002510301e-24);
	fConst42 = ((fConst0 * (-4.0910953566881399e-24 - fConst40)) + -4.6893766002510301e-24);
	fConst43 = (2.17874952274734e-23 * fConst0);
	fConst44 = ((fConst0 * ((fConst0 * (4.13018666157306e-20 - fConst43)) + -7.2715662086784803e-19)) + -7.5059877975905804e-18);
	fConst45 = (2.0400276430218499e-23 * fConst0);
	fConst46 = ((fConst0 * ((fConst0 * (3.8672159752556701e-20 - fConst45)) + -6.8085825923955804e-19)) + -7.02807846216346e-18);
	fConst47 = ((fConst0 * ((fConst0 * (fConst45 + -3.8672159752556701e-20)) + 6.8085825923955804e-19)) + 7.02807846216346e-18);
	fConst48 = (1.5562496591052401e-23 * fConst0);
	fConst49 = ((fConst0 * (fConst48 + 9.1104341364342094e-23)) + -3.1328228456723898e-22);
	fConst50 = (1.4571626021584601e-23 * fConst0);
	fConst51 = ((fConst0 * (fConst50 + 8.5303690416050705e-23)) + -2.9333547244123502e-22);
	fConst52 = ((fConst0 * (-8.5303690416050705e-23 - fConst50)) + 2.9333547244123502e-22);
	fConst53 = (1.7495425825242999e-22 * fConst0);
	fConst54 = (fConst0 * ((fConst0 * ((fConst0 * (5.1594771788559299e-19 - fConst53)) + -2.3901137548476001e-17)) + -8.1266384796658803e-16));
	fConst55 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst53 + -5.1594771788559299e-19)) + 2.3901137548476001e-17)) + 8.1266384796658803e-16)) + 3.9909588087242801e-15);
	fConst56 = (1.8685114781359499e-22 * fConst0);
	fConst57 = ((fConst0 * ((fConst0 * (5.5103216270181403e-19 - fConst56)) + -2.5526414901772399e-17)) + -8.6792498962831596e-16);
	fConst58 = (2.07668602415643e-22 * fConst0);
	fConst59 = ((fConst0 * ((fConst0 * (fConst58 + 3.19433851972335e-21)) + -3.61733701138641e-20)) + -3.1967580057881502e-19);
	fConst60 = (1.9444625694348601e-22 * fConst0);
	fConst61 = ((fConst0 * ((fConst0 * (fConst60 + 2.9909536701529499e-21)) + -3.3870196735827798e-20)) + -2.9932191065432099e-19);
	fConst62 = ((fConst0 * ((fConst0 * (-2.9909536701529499e-21 - fConst60)) + 3.3870196735827798e-20)) + 2.9932191065432099e-19);
	fConst63 = (6.2317445511520701e-22 * fConst0);
	fConst64 = (fConst0 * ((fConst0 * ((fConst0 * (fConst63 + -5.5678197203731598e-18)) + -2.55915269679773e-16)) + 2.89500135356453e-15));
	fConst65 = (4.6640040813802101e-23 * fConst0);
	fConst66 = (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst65 + 8.4221543436713698e-20)) + -9.3928794302153293e-18)) + -1.70442029998199e-16)) + 9.4186951921900103e-16));
	fConst67 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (-8.4221543436713698e-20 - fConst65)) + 9.3928794302153293e-18)) + 1.70442029998199e-16)) + -9.4186951921900103e-16)) + -7.9819176174485601e-15);
	fConst68 = (4.98115635891407e-23 * fConst0);
	fConst69 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst68 + 8.9948608390410199e-20)) + -1.003159523147e-17)) + -1.8203208803807701e-16)) + 1.0059166465258901e-15);
	fConst70 = (9.9569205751008895e-24 * fConst0);
	fConst71 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst70 + -1.73756145804592e-20)) + 1.7683820265513799e-18)) + 2.6036446028877899e-17)) + -8.5033762953964798e-17);
	fConst72 = (9.3229593399821096e-24 * fConst0);
	fConst73 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst72 + -1.6269302041628401e-20)) + 1.65578841437396e-18)) + 2.43786947835935e-17)) + -7.9619628234049401e-17);
	fConst74 = ((fConst0 * ((fConst0 * ((fConst0 * (1.6269302041628401e-20 - fConst72)) + -1.65578841437396e-18)) + -2.43786947835935e-17)) + 7.9619628234049401e-17);
	fConst75 = (1.10662407182939e-23 * fConst0);
	fConst76 = ((fConst0 * ((fConst0 * (-2.2216289116196598e-22 - fConst75)) + 3.2645819840732901e-21)) + 1.0655860019293799e-20);
	fConst77 = (1.03616486126347e-23 * fConst0);
	fConst78 = ((fConst0 * ((fConst0 * (-2.08017688353901e-22 - fConst77)) + 3.0567247041884799e-21)) + 9.9773970218107095e-21);
	fConst79 = ((fConst0 * ((fConst0 * (fConst77 + 2.08017688353901e-22)) + -3.0567247041884799e-21)) + -9.9773970218107095e-21);
	fConst80 = (5.8349668081948204e-22 * fConst0);
	fConst81 = (fConst0 * ((fConst0 * ((fConst0 * (fConst80 + -5.2133143449186902e-18)) + -2.3962103902600502e-16)) + 2.7106754246858899e-15));
	fConst82 = ((fConst0 * ((fConst0 * ((fConst0 * (5.2133143449186902e-18 - fConst80)) + 2.3962103902600502e-16)) + -2.7106754246858899e-15)) + -3.9909588087242799e-14);
	fConst83 = (5.6219990358414601e-23 * fConst0);
	fConst84 = (fConst0 * ((fConst0 * ((fConst0 * (fConst83 + -4.3161472913784199e-19)) + -8.7518197241178303e-18)) + 4.5177783329161701e-17));
	fConst85 = ((fConst0 * ((fConst0 * ((fConst0 * (4.3161472913784199e-19 - fConst83)) + 8.7518197241178303e-18)) + -4.5177783329161701e-17)) + -3.1927670469794302e-16);
	fConst86 = (6.0042949702786697e-23 * fConst0);
	fConst87 = ((fConst0 * ((fConst0 * (fConst86 + -4.6096453071921498e-19)) + -9.3469434653578408e-18)) + 4.82498725955447e-17);
	fConst88 = (4.7993514218213902e-24 * fConst0);
	fConst89 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst88 + 7.3735451124077803e-21)) + -1.5798742492572999e-19)) + -9.2062610036363e-19)) + 1.60264134690179e-18);
	fConst90 = (4.4937747395331397e-24 * fConst0);
	fConst91 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst90 + 6.9040684573106595e-21)) + -1.47928300492257e-19)) + -8.6200945726931702e-19)) + 1.50060051208033e-18);
	fConst92 = ((fConst0 * ((fConst0 * ((fConst0 * (-6.9040684573106595e-21 - fConst90)) + 1.47928300492257e-19)) + 8.6200945726931702e-19)) + -1.50060051208033e-18);
	fConst93 = (1.1610116504435901e-24 * fConst0);
	fConst94 = ((fConst0 * ((fConst0 * (fConst93 + -1.31947527765415e-21)) + 2.3230598842030999e-20)) + 7.9931737176726898e-20);
	fConst95 = (1.0870895603404399e-24 * fConst0);
	fConst96 = ((fConst0 * ((fConst0 * (fConst95 + -1.2354637431218599e-21)) + 2.1751497043100201e-20)) + 7.4842450540006495e-20);
	fConst97 = ((fConst0 * ((fConst0 * (1.2354637431218599e-21 - fConst95)) + -2.1751497043100201e-20)) + -7.4842450540006495e-20);
	fConst98 = (8.2929403603113697e-25 * fConst0);
	fConst99 = ((fConst0 * (-2.9128598939619601e-24 - fConst98)) + 1.0016508418136201e-23);
	fConst100 = (7.7649254310031597e-25 * fConst0);
	fConst101 = ((fConst0 * (-2.72739690445876e-24 - fConst100)) + 9.3787532005020602e-24);
	fConst102 = ((fConst0 * (fConst100 + 2.72739690445876e-24)) + -9.3787532005020602e-24);
	fConst103 = (1.4524996818315601e-23 * fConst0);
	fConst104 = ((fConst0 * ((fConst0 * (fConst103 + 8.2603733231461104e-20)) + 1.4543132417356999e-18)) + -5.00399186506038e-18);
	fConst105 = (1.36001842868123e-23 * fConst0);
	fConst106 = ((fConst0 * ((fConst0 * (fConst105 + 7.7344319505113402e-20)) + 1.3617165184791199e-18)) + -4.6853856414423103e-18);
	fConst107 = ((fConst0 * ((fConst0 * (-7.7344319505113402e-20 - fConst105)) + -1.3617165184791199e-18)) + 4.6853856414423103e-18);
	fConst108 = (1.03749977273683e-23 * fConst0);
	fConst109 = ((fConst0 * (1.82208682728684e-22 - fConst108)) + 6.2656456913447702e-22);
	fConst110 = (9.7144173477231007e-24 * fConst0);
	fConst111 = ((fConst0 * (1.7060738083210101e-22 - fConst110)) + 5.8667094488246901e-22);
	fConst112 = ((fConst0 * (fConst110 + -1.7060738083210101e-22)) + -5.8667094488246901e-22);
	fConst113 = (1.1663617216828699e-22 * fConst0);
	fConst114 = (fConst0 * ((fConst0 * ((fConst0 * (fConst113 + 1.03189543577119e-18)) + 4.7802275096952002e-17)) + -5.4177589864439198e-16));
	fConst115 = ((fConst0 * ((fConst0 * ((fConst0 * (-1.03189543577119e-18 - fConst113)) + -4.7802275096952002e-17)) + 5.4177589864439198e-16)) + 7.9819176174485601e-15);
	fConst116 = (1.2456743187573e-22 * fConst0);
	fConst117 = ((fConst0 * ((fConst0 * (fConst116 + 1.10206432540363e-18)) + 5.10528298035447e-17)) + -5.7861665975221103e-16);
	fConst118 = (1.3844573494376201e-22 * fConst0);
	fConst119 = ((fConst0 * ((fConst0 * (6.3886770394466902e-21 - fConst118)) + 7.23467402277282e-20)) + -2.13117200385877e-19);
	fConst120 = (1.29630837962324e-22 * fConst0);
	fConst121 = ((fConst0 * ((fConst0 * (5.9819073403058901e-21 - fConst120)) + 6.7740393471655597e-20)) + -1.99547940436214e-19);
	fConst122 = ((fConst0 * ((fConst0 * (fConst120 + -5.9819073403058901e-21)) + -6.7740393471655597e-20)) + 1.99547940436214e-19);
	fConst123 = (fConst0 * ((fConst0 * ((fConst0 * (fConst63 + 5.5678197203731598e-18)) + -2.55915269679773e-16)) + -2.89500135356453e-15));
	fConst124 = (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (8.4221543436713698e-20 - fConst65)) + 9.3928794302153293e-18)) + -1.70442029998199e-16)) + -9.4186951921900103e-16));
	fConst125 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst65 + -8.4221543436713698e-20)) + -9.3928794302153293e-18)) + 1.70442029998199e-16)) + 9.4186951921900103e-16)) + -7.9819176174485601e-15);
	fConst126 = ((fConst0 * ((fConst0 * ((fConst0 * (8.9948608390410199e-20 - fConst68)) + 1.003159523147e-17)) + -1.8203208803807701e-16)) + -1.0059166465258901e-15);
	fConst127 = ((fConst0 * ((fConst0 * ((fConst0 * (-1.73756145804592e-20 - fConst70)) + -1.7683820265513799e-18)) + 2.6036446028877899e-17)) + 8.5033762953964798e-17);
	fConst128 = ((fConst0 * ((fConst0 * ((fConst0 * (-1.6269302041628401e-20 - fConst72)) + -1.65578841437396e-18)) + 2.43786947835935e-17)) + 7.9619628234049401e-17);
	fConst129 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst72 + 1.6269302041628401e-20)) + 1.65578841437396e-18)) + -2.43786947835935e-17)) + -7.9619628234049401e-17);
	fConst130 = ((fConst0 * ((fConst0 * (fConst75 + -2.2216289116196598e-22)) + -3.2645819840732901e-21)) + 1.0655860019293799e-20);
	fConst131 = ((fConst0 * ((fConst0 * (fConst77 + -2.08017688353901e-22)) + -3.0567247041884799e-21)) + 9.9773970218107095e-21);
	fConst132 = ((fConst0 * ((fConst0 * (2.08017688353901e-22 - fConst77)) + 3.0567247041884799e-21)) + -9.9773970218107095e-21);
	fConst133 = (fConst0 * ((fConst0 * ((fConst0 * (fConst80 + 5.2133143449186902e-18)) + -2.3962103902600502e-16)) + -2.7106754246858899e-15));
	fConst134 = ((fConst0 * ((fConst0 * ((fConst0 * (-5.2133143449186902e-18 - fConst80)) + 2.3962103902600502e-16)) + 2.7106754246858899e-15)) + -3.9909588087242799e-14);
	fConst135 = (fConst0 * ((fConst0 * ((fConst0 * (fConst83 + 4.3161472913784199e-19)) + -8.7518197241178303e-18)) + -4.5177783329161701e-17));
	fConst136 = ((fConst0 * ((fConst0 * ((fConst0 * (-4.3161472913784199e-19 - fConst83)) + 8.7518197241178303e-18)) + 4.5177783329161701e-17)) + -3.1927670469794302e-16);
	fConst137 = ((fConst0 * ((fConst0 * (fConst86 + 4.6096453071921498e-19)) + -9.3469434653578408e-18)) + -4.82498725955447e-17);
	fConst138 = ((fConst0 * ((fConst0 * ((fConst0 * (7.3735451124077803e-21 - fConst88)) + 1.5798742492572999e-19)) + -9.2062610036363e-19)) + -1.60264134690179e-18);
	fConst139 = ((fConst0 * ((fConst0 * ((fConst0 * (6.9040684573106595e-21 - fConst90)) + 1.47928300492257e-19)) + -8.6200945726931702e-19)) + -1.50060051208033e-18);
	fConst140 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst90 + -6.9040684573106595e-21)) + -1.47928300492257e-19)) + 8.6200945726931702e-19)) + 1.50060051208033e-18);
	fConst141 = ((fConst0 * ((fConst0 * (-1.31947527765415e-21 - fConst93)) + -2.3230598842030999e-20)) + 7.9931737176726898e-20);
	fConst142 = ((fConst0 * ((fConst0 * (-1.2354637431218599e-21 - fConst95)) + -2.1751497043100201e-20)) + 7.4842450540006495e-20);
	fConst143 = ((fConst0 * ((fConst0 * (fConst95 + 1.2354637431218599e-21)) + 2.1751497043100201e-20)) + -7.4842450540006495e-20);
	fConst144 = ((fConst0 * (fConst98 + -2.9128598939619601e-24)) + -1.0016508418136201e-23);
	fConst145 = ((fConst0 * (fConst100 + -2.72739690445876e-24)) + -9.3787532005020602e-24);
	fConst146 = ((fConst0 * (2.72739690445876e-24 - fConst100)) + 9.3787532005020602e-24);
	fConst147 = ((fConst0 * ((fConst0 * (fConst103 + -8.2603733231461104e-20)) + 1.4543132417356999e-18)) + 5.00399186506038e-18);
	fConst148 = ((fConst0 * ((fConst0 * (fConst105 + -7.7344319505113402e-20)) + 1.3617165184791199e-18)) + 4.6853856414423103e-18);
	fConst149 = ((fConst0 * ((fConst0 * (7.7344319505113402e-20 - fConst105)) + -1.3617165184791199e-18)) + -4.6853856414423103e-18);
	fConst150 = ((fConst0 * (-1.82208682728684e-22 - fConst108)) + 6.2656456913447702e-22);
	fConst151 = ((fConst0 * (-1.7060738083210101e-22 - fConst110)) + 5.8667094488246901e-22);
	fConst152 = ((fConst0 * (fConst110 + 1.7060738083210101e-22)) + -5.8667094488246901e-22);
	fConst153 = (fConst0 * ((fConst0 * ((fConst0 * (fConst113 + -1.03189543577119e-18)) + 4.7802275096952002e-17)) + 5.4177589864439198e-16));
	fConst154 = ((fConst0 * ((fConst0 * ((fConst0 * (1.03189543577119e-18 - fConst113)) + -4.7802275096952002e-17)) + -5.4177589864439198e-16)) + 7.9819176174485601e-15);
	fConst155 = ((fConst0 * ((fConst0 * (fConst116 + -1.10206432540363e-18)) + 5.10528298035447e-17)) + 5.7861665975221103e-16);
	fConst156 = ((fConst0 * ((fConst0 * (-6.3886770394466902e-21 - fConst118)) + 7.23467402277282e-20)) + 2.13117200385877e-19);
	fConst157 = ((fConst0 * ((fConst0 * (-5.9819073403058901e-21 - fConst120)) + 6.7740393471655597e-20)) + 1.99547940436214e-19);
	fConst158 = ((fConst0 * ((fConst0 * (fConst120 + 5.9819073403058901e-21)) + -6.7740393471655597e-20)) + -1.99547940436214e-19);
	fConst159 = (fConst0 * ((fConst0 * ((fConst0 * (2.7839098601865799e-18 - fConst3)) + 1.2795763483988699e-16)) + -4.3425020303467898e-15));
	fConst160 = (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst5 + -1.2633231515507101e-19)) + 4.69643971510767e-18)) + 8.52210149990995e-17)) + -1.4128042788285e-15));
	fConst161 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (1.2633231515507101e-19 - fConst5)) + -4.69643971510767e-18)) + -8.52210149990995e-17)) + 1.4128042788285e-15)) + -3.9909588087242801e-15);
	fConst162 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst8 + -1.3492291258561499e-19)) + 5.0157976157349902e-18)) + 9.1016044019038295e-17)) + -1.50887496978884e-15);
	fConst163 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst10 + 2.60634218706887e-20)) + -8.8419101327569207e-19)) + -1.30182230144389e-17)) + 1.2755064443094701e-16);
	fConst164 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst12 + 2.4403953062442599e-20)) + -8.2789420718697798e-19)) + -1.2189347391796701e-17)) + 1.1942944235107401e-16);
	fConst165 = ((fConst0 * ((fConst0 * ((fConst0 * (-2.4403953062442599e-20 - fConst12)) + 8.2789420718697798e-19)) + 1.2189347391796701e-17)) + -1.1942944235107401e-16);
	fConst166 = ((fConst0 * ((fConst0 * (3.3324433674294899e-22 - fConst15)) + -1.6322909920366499e-21)) + -5.32793000964692e-21);
	fConst167 = ((fConst0 * ((fConst0 * (3.1202653253085101e-22 - fConst17)) + -1.52836235209424e-21)) + -4.9886985109053503e-21);
	fConst168 = ((fConst0 * ((fConst0 * (fConst17 + -3.1202653253085101e-22)) + 1.52836235209424e-21)) + 4.9886985109053503e-21);
	fConst169 = (fConst0 * ((fConst0 * ((fConst0 * (2.6066571724593401e-18 - fConst20)) + 1.1981051951300199e-16)) + -4.0660131370288298e-15));
	fConst170 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst20 + -2.6066571724593401e-18)) + -1.1981051951300199e-16)) + 4.0660131370288298e-15)) + -1.99547940436214e-14);
	fConst171 = (fConst0 * ((fConst0 * ((fConst0 * (2.15807364568921e-19 - fConst23)) + 4.3759098620589198e-18)) + -6.7766674993742604e-17));
	fConst172 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst23 + -2.15807364568921e-19)) + -4.3759098620589198e-18)) + 6.7766674993742604e-17)) + -1.5963835234897099e-16);
	fConst173 = ((fConst0 * ((fConst0 * (2.3048226535960802e-19 - fConst26)) + 4.6734717326789204e-18)) + -7.2374808893316998e-17);
	fConst174 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst28 + -1.1060317668611701e-20)) + 7.89937124628652e-20)) + 4.60313050181815e-19)) + -2.4039620203526901e-18);
	fConst175 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst30 + -1.0356102685966e-20)) + 7.3964150246128498e-20)) + 4.3100472863465798e-19)) + -2.2509007681204999e-18);
	fConst176 = ((fConst0 * ((fConst0 * ((fConst0 * (1.0356102685966e-20 - fConst30)) + -7.3964150246128498e-20)) + -4.3100472863465798e-19)) + 2.2509007681204999e-18);
	fConst177 = ((fConst0 * ((fConst0 * (fConst33 + 1.9792129164812199e-21)) + -1.1615299421015499e-20)) + -3.9965868588363503e-20);
	fConst178 = ((fConst0 * ((fConst0 * (fConst35 + 1.8531956146827899e-21)) + -1.08757485215501e-20)) + -3.7421225270003199e-20);
	fConst179 = ((fConst0 * ((fConst0 * (-1.8531956146827899e-21 - fConst35)) + 1.08757485215501e-20)) + 3.7421225270003199e-20);
	fConst180 = ((fConst0 * (4.3692898409429397e-24 - fConst38)) + -5.0082542090681003e-24);
	fConst181 = ((fConst0 * (4.0910953566881399e-24 - fConst40)) + -4.6893766002510301e-24);
	fConst182 = ((fConst0 * (fConst40 + -4.0910953566881399e-24)) + 4.6893766002510301e-24);
	fConst183 = ((fConst0 * ((fConst0 * (-4.13018666157306e-20 - fConst43)) + -7.2715662086784803e-19)) + 7.5059877975905804e-18);
	fConst184 = ((fConst0 * ((fConst0 * (-3.8672159752556701e-20 - fConst45)) + -6.8085825923955804e-19)) + 7.02807846216346e-18);
	fConst185 = ((fConst0 * ((fConst0 * (fConst45 + 3.8672159752556701e-20)) + 6.8085825923955804e-19)) + -7.02807846216346e-18);
	fConst186 = ((fConst0 * (fConst48 + -9.1104341364342094e-23)) + -3.1328228456723898e-22);
	fConst187 = ((fConst0 * (fConst50 + -8.5303690416050705e-23)) + -2.9333547244123502e-22);
	fConst188 = ((fConst0 * (8.5303690416050705e-23 - fConst50)) + 2.9333547244123502e-22);
	fConst189 = (fConst0 * ((fConst0 * ((fConst0 * (-5.1594771788559299e-19 - fConst53)) + -2.3901137548476001e-17)) + 8.1266384796658803e-16));
	fConst190 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst53 + 5.1594771788559299e-19)) + 2.3901137548476001e-17)) + -8.1266384796658803e-16)) + 3.9909588087242801e-15);
	fConst191 = ((fConst0 * ((fConst0 * (-5.5103216270181403e-19 - fConst56)) + -2.5526414901772399e-17)) + 8.6792498962831596e-16);
	fConst192 = ((fConst0 * ((fConst0 * (fConst58 + -3.19433851972335e-21)) + -3.61733701138641e-20)) + 3.1967580057881502e-19);
	fConst193 = ((fConst0 * ((fConst0 * (fConst60 + -2.9909536701529499e-21)) + -3.3870196735827798e-20)) + 2.9932191065432099e-19);
	fConst194 = ((fConst0 * ((fConst0 * (2.9909536701529499e-21 - fConst60)) + 3.3870196735827798e-20)) + -2.9932191065432099e-19);
	fConst195 = (3.1158722755760299e-22 * fConst0);
	fConst196 = (fConst0 * ((fConst0 * ((fConst0 * (fConst195 + -2.7839098601865799e-18)) + 1.2795763483988699e-16)) + -1.4475006767822601e-15));
	fConst197 = (4.6640040813802103e-24 * fConst0);
	fConst198 = (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (4.2110771718356801e-20 - fConst197)) + -4.69643971510767e-18)) + 8.52210149990995e-17)) + -4.7093475960950101e-16));
	fConst199 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst197 + -4.2110771718356801e-20)) + 4.69643971510767e-18)) + -8.52210149990995e-17)) + 4.7093475960950101e-16)) + -7.9819176174485603e-16);
	fConst200 = (4.9811563589140703e-24 * fConst0);
	fConst201 = ((fConst0 * ((fConst0 * ((fConst0 * (4.4974304195205099e-20 - fConst200)) + -5.0157976157349902e-18)) + 9.1016044019038295e-17)) + -5.0295832326294702e-16);
	fConst202 = (9.9569205751008895e-25 * fConst0);
	fConst203 = ((fConst0 * ((fConst0 * ((fConst0 * (-8.6878072902295803e-21 - fConst202)) + 8.8419101327569207e-19)) + -1.30182230144389e-17)) + 4.2516881476982399e-17);
	fConst204 = (9.3229593399821096e-25 * fConst0);
	fConst205 = ((fConst0 * ((fConst0 * ((fConst0 * (-8.1346510208142203e-21 - fConst204)) + 8.2789420718697798e-19)) + -1.2189347391796701e-17)) + 3.98098141170247e-17);
	fConst206 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst204 + 8.1346510208142203e-21)) + -8.2789420718697798e-19)) + 1.2189347391796701e-17)) + -3.98098141170247e-17);
	fConst207 = (1.10662407182939e-24 * fConst0);
	fConst208 = ((fConst0 * ((fConst0 * (fConst207 + -1.1108144558098299e-22)) + 1.6322909920366499e-21)) + -5.32793000964692e-21);
	fConst209 = (1.0361648612634699e-24 * fConst0);
	fConst210 = ((fConst0 * ((fConst0 * (fConst209 + -1.0400884417694999e-22)) + 1.52836235209424e-21)) + -4.9886985109053503e-21);
	fConst211 = ((fConst0 * ((fConst0 * (1.0400884417694999e-22 - fConst209)) + -1.52836235209424e-21)) + 4.9886985109053503e-21);
	fConst212 = (2.9174834040974102e-22 * fConst0);
	fConst213 = (fConst0 * ((fConst0 * ((fConst0 * (fConst212 + -2.6066571724593401e-18)) + 1.1981051951300199e-16)) + -1.35533771234294e-15));
	fConst214 = ((fConst0 * ((fConst0 * ((fConst0 * (2.6066571724593401e-18 - fConst212)) + -1.1981051951300199e-16)) + 1.35533771234294e-15)) + -3.9909588087242801e-15);
	fConst215 = (2.8109995179207301e-23 * fConst0);
	fConst216 = (fConst0 * ((fConst0 * ((fConst0 * (fConst215 + -2.15807364568921e-19)) + 4.3759098620589198e-18)) + -2.25888916645809e-17));
	fConst217 = ((fConst0 * ((fConst0 * ((fConst0 * (2.15807364568921e-19 - fConst215)) + -4.3759098620589198e-18)) + 2.25888916645809e-17)) + -3.19276704697943e-17);
	fConst218 = (3.0021474851393402e-23 * fConst0);
	fConst219 = ((fConst0 * ((fConst0 * (fConst218 + -2.3048226535960802e-19)) + 4.6734717326789204e-18)) + -2.4124936297772301e-17);
	fConst220 = (4.7993514218213904e-25 * fConst0);
	fConst221 = ((fConst0 * ((fConst0 * ((fConst0 * (3.6867725562038901e-21 - fConst220)) + -7.89937124628652e-20)) + 4.60313050181815e-19)) + -8.0132067345089605e-19);
	fConst222 = (4.49377473953314e-25 * fConst0);
	fConst223 = ((fConst0 * ((fConst0 * ((fConst0 * (3.4520342286553298e-21 - fConst222)) + -7.3964150246128498e-20)) + 4.3100472863465798e-19)) + -7.5030025604016499e-19);
	fConst224 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst222 + -3.4520342286553298e-21)) + 7.3964150246128498e-20)) + -4.3100472863465798e-19)) + 7.5030025604016499e-19);
	fConst225 = (1.1610116504435901e-25 * fConst0);
	fConst226 = ((fConst0 * ((fConst0 * (-6.5973763882707399e-22 - fConst225)) + 1.1615299421015499e-20)) + -3.9965868588363503e-20);
	fConst227 = (1.08708956034044e-25 * fConst0);
	fConst228 = ((fConst0 * ((fConst0 * (-6.1773187156093099e-22 - fConst227)) + 1.08757485215501e-20)) + -3.7421225270003199e-20);
	fConst229 = ((fConst0 * ((fConst0 * (fConst227 + 6.1773187156093099e-22)) + -1.08757485215501e-20)) + 3.7421225270003199e-20);
	fConst230 = (8.2929403603113699e-26 * fConst0);
	fConst231 = ((fConst0 * (fConst230 + -1.4564299469809801e-24)) + 5.0082542090681003e-24);
	fConst232 = (7.7649254310031595e-26 * fConst0);
	fConst233 = ((fConst0 * (fConst232 + -1.36369845222938e-24)) + 4.6893766002510301e-24);
	fConst234 = ((fConst0 * (1.36369845222938e-24 - fConst232)) + -4.6893766002510301e-24);
	fConst235 = (7.2624984091577901e-24 * fConst0);
	fConst236 = ((fConst0 * ((fConst0 * (fConst235 + 4.13018666157306e-20)) + -7.2715662086784803e-19)) + 2.50199593253019e-18);
	fConst237 = (6.8000921434061693e-24 * fConst0);
	fConst238 = ((fConst0 * ((fConst0 * (fConst237 + 3.8672159752556701e-20)) + -6.8085825923955804e-19)) + 2.3426928207211501e-18);
	fConst239 = ((fConst0 * ((fConst0 * (-3.8672159752556701e-20 - fConst237)) + 6.8085825923955804e-19)) + -2.3426928207211501e-18);
	fConst240 = (5.1874988636841301e-24 * fConst0);
	fConst241 = ((fConst0 * (9.1104341364342094e-23 - fConst240)) + -3.1328228456723898e-22);
	fConst242 = (4.8572086738615503e-24 * fConst0);
	fConst243 = ((fConst0 * (8.5303690416050705e-23 - fConst242)) + -2.9333547244123502e-22);
	fConst244 = ((fConst0 * (fConst242 + -8.5303690416050705e-23)) + 2.9333547244123502e-22);
	fConst245 = (5.8318086084143401e-23 * fConst0);
	fConst246 = (fConst0 * ((fConst0 * ((fConst0 * (fConst245 + 5.1594771788559299e-19)) + -2.3901137548476001e-17)) + 2.7088794932219599e-16));
	fConst247 = ((fConst0 * ((fConst0 * ((fConst0 * (-5.1594771788559299e-19 - fConst245)) + 2.3901137548476001e-17)) + -2.7088794932219599e-16)) + 7.9819176174485603e-16);
	fConst248 = (6.2283715937865103e-23 * fConst0);
	fConst249 = ((fConst0 * ((fConst0 * (fConst248 + 5.5103216270181403e-19)) + -2.5526414901772399e-17)) + 2.8930832987610502e-16);
	fConst250 = (6.9222867471881005e-23 * fConst0);
	fConst251 = ((fConst0 * ((fConst0 * (3.19433851972335e-21 - fConst250)) + -3.61733701138641e-20)) + 1.0655860019293799e-19);
	fConst252 = (6.4815418981162002e-23 * fConst0);
	fConst253 = ((fConst0 * ((fConst0 * (2.9909536701529499e-21 - fConst252)) + -3.3870196735827798e-20)) + 9.9773970218107002e-20);
	fConst254 = ((fConst0 * ((fConst0 * (fConst252 + -2.9909536701529499e-21)) + 3.3870196735827798e-20)) + -9.9773970218107002e-20);
	fConst255 = (fConst0 * ((fConst0 * ((fConst0 * (fConst195 + 2.7839098601865799e-18)) + 1.2795763483988699e-16)) + 1.4475006767822601e-15));
	fConst256 = (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst197 + 4.2110771718356801e-20)) + 4.69643971510767e-18)) + 8.52210149990995e-17)) + 4.7093475960950101e-16));
	fConst257 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (-4.2110771718356801e-20 - fConst197)) + -4.69643971510767e-18)) + -8.52210149990995e-17)) + -4.7093475960950101e-16)) + -7.9819176174485603e-16);
	fConst258 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst200 + 4.4974304195205099e-20)) + 5.0157976157349902e-18)) + 9.1016044019038295e-17)) + 5.0295832326294702e-16);
	fConst259 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst202 + -8.6878072902295803e-21)) + -8.8419101327569207e-19)) + -1.30182230144389e-17)) + -4.2516881476982399e-17);
	fConst260 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst204 + -8.1346510208142203e-21)) + -8.2789420718697798e-19)) + -1.2189347391796701e-17)) + -3.98098141170247e-17);
	fConst261 = ((fConst0 * ((fConst0 * ((fConst0 * (8.1346510208142203e-21 - fConst204)) + 8.2789420718697798e-19)) + 1.2189347391796701e-17)) + 3.98098141170247e-17);
	fConst262 = ((fConst0 * ((fConst0 * (-1.1108144558098299e-22 - fConst207)) + -1.6322909920366499e-21)) + -5.32793000964692e-21);
	fConst263 = ((fConst0 * ((fConst0 * (-1.0400884417694999e-22 - fConst209)) + -1.52836235209424e-21)) + -4.9886985109053503e-21);
	fConst264 = ((fConst0 * ((fConst0 * (fConst209 + 1.0400884417694999e-22)) + 1.52836235209424e-21)) + 4.9886985109053503e-21);
	fConst265 = (fConst0 * ((fConst0 * ((fConst0 * (fConst212 + 2.6066571724593401e-18)) + 1.1981051951300199e-16)) + 1.35533771234294e-15));
	fConst266 = ((fConst0 * ((fConst0 * ((fConst0 * (-2.6066571724593401e-18 - fConst212)) + -1.1981051951300199e-16)) + -1.35533771234294e-15)) + -3.9909588087242801e-15);
	fConst267 = (fConst0 * ((fConst0 * ((fConst0 * (fConst215 + 2.15807364568921e-19)) + 4.3759098620589198e-18)) + 2.25888916645809e-17));
	fConst268 = ((fConst0 * ((fConst0 * ((fConst0 * (-2.15807364568921e-19 - fConst215)) + -4.3759098620589198e-18)) + -2.25888916645809e-17)) + -3.19276704697943e-17);
	fConst269 = ((fConst0 * ((fConst0 * (fConst218 + 2.3048226535960802e-19)) + 4.6734717326789204e-18)) + 2.4124936297772301e-17);
	fConst270 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst220 + 3.6867725562038901e-21)) + 7.89937124628652e-20)) + 4.60313050181815e-19)) + 8.0132067345089605e-19);
	fConst271 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst222 + 3.4520342286553298e-21)) + 7.3964150246128498e-20)) + 4.3100472863465798e-19)) + 7.5030025604016499e-19);
	fConst272 = ((fConst0 * ((fConst0 * ((fConst0 * (-3.4520342286553298e-21 - fConst222)) + -7.3964150246128498e-20)) + -4.3100472863465798e-19)) + -7.5030025604016499e-19);
	fConst273 = ((fConst0 * ((fConst0 * (fConst225 + -6.5973763882707399e-22)) + -1.1615299421015499e-20)) + -3.9965868588363503e-20);
	fConst274 = ((fConst0 * ((fConst0 * (fConst227 + -6.1773187156093099e-22)) + -1.08757485215501e-20)) + -3.7421225270003199e-20);
	fConst275 = ((fConst0 * ((fConst0 * (6.1773187156093099e-22 - fConst227)) + 1.08757485215501e-20)) + 3.7421225270003199e-20);
	fConst276 = ((fConst0 * (-1.4564299469809801e-24 - fConst230)) + -5.0082542090681003e-24);
	fConst277 = ((fConst0 * (-1.36369845222938e-24 - fConst232)) + -4.6893766002510301e-24);
	fConst278 = ((fConst0 * (fConst232 + 1.36369845222938e-24)) + 4.6893766002510301e-24);
	fConst279 = ((fConst0 * ((fConst0 * (fConst235 + -4.13018666157306e-20)) + -7.2715662086784803e-19)) + -2.50199593253019e-18);
	fConst280 = ((fConst0 * ((fConst0 * (fConst237 + -3.8672159752556701e-20)) + -6.8085825923955804e-19)) + -2.3426928207211501e-18);
	fConst281 = ((fConst0 * ((fConst0 * (3.8672159752556701e-20 - fConst237)) + 6.8085825923955804e-19)) + 2.3426928207211501e-18);
	fConst282 = ((fConst0 * (-9.1104341364342094e-23 - fConst240)) + -3.1328228456723898e-22);
	fConst283 = ((fConst0 * (-8.5303690416050705e-23 - fConst242)) + -2.9333547244123502e-22);
	fConst284 = ((fConst0 * (fConst242 + 8.5303690416050705e-23)) + 2.9333547244123502e-22);
	fConst285 = (fConst0 * ((fConst0 * ((fConst0 * (fConst245 + -5.1594771788559299e-19)) + -2.3901137548476001e-17)) + -2.7088794932219599e-16));
	fConst286 = ((fConst0 * ((fConst0 * ((fConst0 * (5.1594771788559299e-19 - fConst245)) + 2.3901137548476001e-17)) + 2.7088794932219599e-16)) + 7.9819176174485603e-16);
	fConst287 = ((fConst0 * ((fConst0 * (fConst248 + -5.5103216270181403e-19)) + -2.5526414901772399e-17)) + -2.8930832987610502e-16);
	fConst288 = ((fConst0 * ((fConst0 * (-3.19433851972335e-21 - fConst250)) + -3.61733701138641e-20)) + -1.0655860019293799e-19);
	fConst289 = ((fConst0 * ((fConst0 * (-2.9909536701529499e-21 - fConst252)) + -3.3870196735827798e-20)) + -9.9773970218107002e-20);
	fConst290 = ((fConst0 * ((fConst0 * (fConst252 + 2.9909536701529499e-21)) + 3.3870196735827798e-20)) + 9.9773970218107002e-20);
	fConst291 = (3.5568716158719698e-19 * fConst0);
	fConst292 = ((fConst0 * (fConst291 + 1.44694505189894e-17)) + 8.0654685167165206e-17);
	fConst293 = (5.6861553042851301e-21 * fConst0);
	fConst294 = ((fConst0 * ((fConst0 * (fConst293 + 9.9850500236950203e-19)) + 4.8577832948072403e-15)) + 3.2342528752033202e-14);
	fConst295 = (fConst1 * (-3.7907702028567602e-20 - fConst293));
	fConst296 = ((fConst0 * (-1.44694505189894e-17 - fConst291)) + -8.0654685167165206e-17);
	fConst297 = (4.9796202622207603e-20 * fConst0);
	fConst298 = ((fConst0 * (fConst297 + 2.8536563206490898e-16)) + 1.90022438253841e-15);
	fConst299 = (7.9606174259991803e-22 * fConst0);
	fConst300 = (fConst0 * ((fConst0 * (fConst299 + 4.5656036323206698e-18)) + 3.0401977026911197e-17));
	fConst301 = (1.0670614847615901e-18 * fConst0);
	fConst302 = ((fConst0 * (-1.44694505189894e-17 - fConst301)) + 8.0654685167165206e-17);
	fConst303 = (2.84307765214256e-20 * fConst0);
	fConst304 = ((fConst0 * ((fConst0 * (-2.9955150071085099e-18 - fConst303)) + -4.8577832948072403e-15)) + 3.2342528752033202e-14);
	fConst305 = (fConst1 * (fConst303 + 1.13723106085703e-19));
	fConst306 = ((fConst0 * (fConst301 + 1.44694505189894e-17)) + -8.0654685167165206e-17);
	fConst307 = (1.4938860786662301e-19 * fConst0);
	fConst308 = ((fConst0 * (-2.8536563206490898e-16 - fConst307)) + 1.90022438253841e-15);
	fConst309 = (3.98030871299959e-21 * fConst0);
	fConst310 = (fConst0 * ((fConst0 * (-1.3696810896961999e-17 - fConst309)) + -3.0401977026911197e-17));
	fConst311 = (7.1137432317439502e-19 * fConst0);
	fConst312 = ((fConst0 * (fConst311 + -2.89389010379788e-17)) + -1.6130937033432999e-16);
	fConst313 = (5.6861553042851295e-20 * fConst0);
	fConst314 = ((fConst0 * ((fConst0 * (fConst313 + 1.9970100047389998e-18)) + -9.71556658961449e-15)) + -6.4685057504066505e-14);
	fConst315 = (fConst1 * (-7.5815404057135301e-20 - fConst313));
	fConst316 = ((fConst0 * (2.89389010379788e-17 - fConst311)) + 1.6130937033432999e-16);
	fConst317 = (9.9592405244415302e-20 * fConst0);
	fConst318 = ((fConst0 * (fConst317 + -5.7073126412981796e-16)) + -3.8004487650768199e-15);
	fConst319 = (7.9606174259991801e-21 * fConst0);
	fConst320 = (fConst0 * ((fConst0 * (fConst319 + 9.1312072646413396e-18)) + -6.0803954053822505e-17));
	fConst321 = ((fConst0 * (fConst311 + 2.89389010379788e-17)) + -1.6130937033432999e-16);
	fConst322 = ((fConst0 * ((fConst0 * (1.9970100047389998e-18 - fConst313)) + 9.71556658961449e-15)) + -6.4685057504066505e-14);
	fConst323 = (fConst1 * (fConst313 + -7.5815404057135301e-20));
	fConst324 = ((fConst0 * (-2.89389010379788e-17 - fConst311)) + 1.6130937033432999e-16);
	fConst325 = ((fConst0 * (fConst317 + 5.7073126412981796e-16)) + -3.8004487650768199e-15);
	fConst326 = (fConst0 * ((fConst0 * (9.1312072646413396e-18 - fConst319)) + 6.0803954053822505e-17));
	fConst327 = ((fConst0 * (1.44694505189894e-17 - fConst301)) + 8.0654685167165206e-17);
	fConst328 = ((fConst0 * ((fConst0 * (fConst303 + -2.9955150071085099e-18)) + 4.8577832948072403e-15)) + 3.2342528752033202e-14);
	fConst329 = (fConst1 * (1.13723106085703e-19 - fConst303));
	fConst330 = ((fConst0 * (fConst301 + -1.44694505189894e-17)) + -8.0654685167165206e-17);
	fConst331 = ((fConst0 * (2.8536563206490898e-16 - fConst307)) + 1.90022438253841e-15);
	fConst332 = (fConst0 * ((fConst0 * (fConst309 + -1.3696810896961999e-17)) + 3.0401977026911197e-17));
	fConst333 = ((fConst0 * (fConst291 + -1.44694505189894e-17)) + 8.0654685167165206e-17);
	fConst334 = ((fConst0 * ((fConst0 * (9.9850500236950203e-19 - fConst293)) + -4.8577832948072403e-15)) + 3.2342528752033202e-14);
	fConst335 = (fConst1 * (fConst293 + -3.7907702028567602e-20));
	fConst336 = ((fConst0 * (1.44694505189894e-17 - fConst291)) + -8.0654685167165206e-17);
	fConst337 = ((fConst0 * (fConst297 + -2.8536563206490898e-16)) + 1.90022438253841e-15);
	fConst338 = (fConst0 * ((fConst0 * (4.5656036323206698e-18 - fConst299)) + -3.0401977026911197e-17));
	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fVslider0 (*fVslider0_)
#define fVslider1 (*fVslider1_)
#define fVslider2 (*fVslider2_)
#define fVslider3 (*fVslider3_)
#define fVslider4 (*fVslider4_)
	double fSlow0 = (0.004073836948085289 * (std::exp(double(fVslider0)) + -1.0));
	double fSlow1 = (0.004073836948085289 * (std::exp(double(fVslider1)) + -1.0));
	double fSlow2 = (0.004073836948085289 * (std::exp(double(fVslider2)) + -1.0));
	double fSlow3 = (0.0070000000000000062 * (1.0 - double(fVslider3)));
	double fSlow4 = (0.0070000000000000062 * double(fVslider4));
	for (int i = 0; (i < count); i = (i + 1)) {
		fRec0[0] = (fSlow0 + (0.99299999999999999 * fRec0[1]));
		fRec1[0] = (fSlow1 + (0.99299999999999999 * fRec1[1]));
		fRec3[0] = (fSlow2 + (0.99299999999999999 * fRec3[1]));
		fRec4[0] = (fSlow3 + (0.99299999999999999 * fRec4[1]));
		fRec5[0] = (fSlow4 + (0.99299999999999999 * fRec5[1]));
		double fTemp0 = (fConst255 + (((((fRec3[0] * (((fRec0[0] * (fConst256 + ((fConst257 * fRec0[0]) + 7.9819176174485603e-16))) + (fConst0 * (fConst258 + (fRec4[0] * (fConst259 + ((fRec0[0] * (fConst260 + (fConst261 * fRec0[0]))) + (fConst0 * (fRec4[0] * (fConst262 + (fRec0[0] * (fConst263 + (fConst264 * fRec0[0])))))))))))) + 8.5246880154350698e-16)) + (fRec0[0] * (fConst265 + ((fConst266 * fRec0[0]) + 3.9909588087242801e-15)))) + (fRec5[0] * (((fRec0[0] * (fConst267 + ((fConst268 * fRec0[0]) + 3.19276704697943e-17))) + (fConst0 * (fConst269 + ((fRec3[0] * (fConst270 + ((fRec0[0] * (fConst271 + (fConst272 * fRec0[0]))) + (fConst0 * (fRec4[0] * (fConst273 + ((fRec0[0] * (fConst274 + (fConst275 * fRec0[0]))) + (fConst0 * (fRec4[0] * (fConst276 + (fRec0[0] * (fConst277 + (fConst278 * fRec0[0]))))))))))))) + (fRec4[0] * (fConst279 + ((fRec0[0] * (fConst280 + (fConst281 * fRec0[0]))) + (fConst0 * (fRec4[0] * (fConst282 + (fRec0[0] * (fConst283 + (fConst284 * fRec0[0]))))))))))))) + 3.4098752061740298e-17))) + (fRec4[0] * (((fRec0[0] * (fConst285 + ((fConst286 * fRec0[0]) + -7.9819176174485603e-16))) + (fConst0 * (fConst287 + (fRec4[0] * (fConst288 + (fRec0[0] * (fConst289 + (fConst290 * fRec0[0])))))))) + -8.5246880154350698e-16))) + 4.2623440077175302e-15));
		fRec2[0] = (double(input0[i]) - ((((((fRec2[1] * (fConst4 + (((((fRec3[0] * (((fRec0[0] * (fConst6 + ((fConst7 * fRec0[0]) + 3.9909588087242801e-15))) + (fConst0 * (fConst9 + (fRec4[0] * (fConst11 + ((fRec0[0] * (fConst13 + (fConst14 * fRec0[0]))) + (fConst0 * (fRec4[0] * (fConst16 + (fRec0[0] * (fConst18 + (fConst19 * fRec0[0])))))))))))) + 4.2623440077175302e-15)) + (fRec0[0] * (fConst21 + ((fConst22 * fRec0[0]) + 1.99547940436214e-14)))) + (fRec5[0] * (((fRec0[0] * (fConst24 + ((fConst25 * fRec0[0]) + 1.5963835234897099e-16))) + (fConst0 * (fConst27 + ((fRec3[0] * (fConst29 + ((fRec0[0] * (fConst31 + (fConst32 * fRec0[0]))) + (fConst0 * (fRec4[0] * (fConst34 + ((fRec0[0] * (fConst36 + (fConst37 * fRec0[0]))) + (fConst0 * (fRec4[0] * (fConst39 + (fRec0[0] * (fConst41 + (fConst42 * fRec0[0]))))))))))))) + (fRec4[0] * (fConst44 + ((fRec0[0] * (fConst46 + (fConst47 * fRec0[0]))) + (fConst0 * (fRec4[0] * (fConst49 + (fRec0[0] * (fConst51 + (fConst52 * fRec0[0]))))))))))))) + 1.7049376030870099e-16))) + (fRec4[0] * (((fRec0[0] * (fConst54 + ((fConst55 * fRec0[0]) + -3.9909588087242801e-15))) + (fConst0 * (fConst57 + (fRec4[0] * (fConst59 + (fRec0[0] * (fConst61 + (fConst62 * fRec0[0])))))))) + -4.2623440077175302e-15))) + 2.1311720038587701e-14))) + (fRec2[2] * (fConst64 + (((((fRec3[0] * (((fRec0[0] * (fConst66 + ((fConst67 * fRec0[0]) + 7.9819176174485601e-15))) + (fConst0 * (fConst69 + (fRec4[0] * (fConst71 + ((fRec0[0] * (fConst73 + (fConst74 * fRec0[0]))) + (fConst0 * (fRec4[0] * (fConst76 + (fRec0[0] * (fConst78 + (fConst79 * fRec0[0])))))))))))) + 8.5246880154350698e-15)) + (fRec0[0] * (fConst81 + ((fConst82 * fRec0[0]) + 3.9909588087242799e-14)))) + (fRec5[0] * (((fRec0[0] * (fConst84 + ((fConst85 * fRec0[0]) + 3.1927670469794302e-16))) + (fConst0 * (fConst87 + ((fRec3[0] * (fConst89 + ((fRec0[0] * (fConst91 + (fConst92 * fRec0[0]))) + (fConst0 * (fRec4[0] * (fConst94 + ((fRec0[0] * (fConst96 + (fConst97 * fRec0[0]))) + (fConst0 * (fRec4[0] * (fConst99 + (fRec0[0] * (fConst101 + (fConst102 * fRec0[0]))))))))))))) + (fRec4[0] * (fConst104 + ((fRec0[0] * (fConst106 + (fConst107 * fRec0[0]))) + (fConst0 * (fRec4[0] * (fConst109 + (fRec0[0] * (fConst111 + (fConst112 * fRec0[0]))))))))))))) + 3.4098752061740302e-16))) + (fRec4[0] * (((fRec0[0] * (fConst114 + ((fConst115 * fRec0[0]) + -7.9819176174485601e-15))) + (fConst0 * (fConst117 + (fRec4[0] * (fConst119 + (fRec0[0] * (fConst121 + (fConst122 * fRec0[0])))))))) + -8.5246880154350698e-15))) + 4.2623440077175302e-14)))) + (fRec2[3] * (fConst123 + (((((fRec3[0] * (((fRec0[0] * (fConst124 + ((fConst125 * fRec0[0]) + 7.9819176174485601e-15))) + (fConst0 * (fConst126 + (fRec4[0] * (fConst127 + ((fRec0[0] * (fConst128 + (fConst129 * fRec0[0]))) + (fConst0 * (fRec4[0] * (fConst130 + (fRec0[0] * (fConst131 + (fConst132 * fRec0[0])))))))))))) + 8.5246880154350698e-15)) + (fRec0[0] * (fConst133 + ((fConst134 * fRec0[0]) + 3.9909588087242799e-14)))) + (fRec5[0] * (((fRec0[0] * (fConst135 + ((fConst136 * fRec0[0]) + 3.1927670469794302e-16))) + (fConst0 * (fConst137 + ((fRec3[0] * (fConst138 + ((fRec0[0] * (fConst139 + (fConst140 * fRec0[0]))) + (fConst0 * (fRec4[0] * (fConst141 + ((fRec0[0] * (fConst142 + (fConst143 * fRec0[0]))) + (fConst0 * (fRec4[0] * (fConst144 + (fRec0[0] * (fConst145 + (fConst146 * fRec0[0]))))))))))))) + (fRec4[0] * (fConst147 + ((fRec0[0] * (fConst148 + (fConst149 * fRec0[0]))) + (fConst0 * (fRec4[0] * (fConst150 + (fRec0[0] * (fConst151 + (fConst152 * fRec0[0]))))))))))))) + 3.4098752061740302e-16))) + (fRec4[0] * (((fRec0[0] * (fConst153 + ((fConst154 * fRec0[0]) + -7.9819176174485601e-15))) + (fConst0 * (fConst155 + (fRec4[0] * (fConst156 + (fRec0[0] * (fConst157 + (fConst158 * fRec0[0])))))))) + -8.5246880154350698e-15))) + 4.2623440077175302e-14)))) + (fRec2[4] * (fConst159 + (((((fRec3[0] * (((fRec0[0] * (fConst160 + ((fConst161 * fRec0[0]) + 3.9909588087242801e-15))) + (fConst0 * (fConst162 + (fRec4[0] * (fConst163 + ((fRec0[0] * (fConst164 + (fConst165 * fRec0[0]))) + (fConst0 * (fRec4[0] * (fConst166 + (fRec0[0] * (fConst167 + (fConst168 * fRec0[0])))))))))))) + 4.2623440077175302e-15)) + (fRec0[0] * (fConst169 + ((fConst170 * fRec0[0]) + 1.99547940436214e-14)))) + (fRec5[0] * (((fRec0[0] * (fConst171 + ((fConst172 * fRec0[0]) + 1.5963835234897099e-16))) + (fConst0 * (fConst173 + ((fRec3[0] * (fConst174 + ((fRec0[0] * (fConst175 + (fConst176 * fRec0[0]))) + (fConst0 * (fRec4[0] * (fConst177 + ((fRec0[0] * (fConst178 + (fConst179 * fRec0[0]))) + (fConst0 * (fRec4[0] * (fConst180 + (fRec0[0] * (fConst181 + (fConst182 * fRec0[0]))))))))))))) + (fRec4[0] * (fConst183 + ((fRec0[0] * (fConst184 + (fConst185 * fRec0[0]))) + (fConst0 * (fRec4[0] * (fConst186 + (fRec0[0] * (fConst187 + (fConst188 * fRec0[0]))))))))))))) + 1.7049376030870099e-16))) + (fRec4[0] * (((fRec0[0] * (fConst189 + ((fConst190 * fRec0[0]) + -3.9909588087242801e-15))) + (fConst0 * (fConst191 + (fRec4[0] * (fConst192 + (fRec0[0] * (fConst193 + (fConst194 * fRec0[0])))))))) + -4.2623440077175302e-15))) + 2.1311720038587701e-14)))) + (fRec2[5] * (fConst196 + (((((fRec3[0] * (((fRec0[0] * (fConst198 + ((fConst199 * fRec0[0]) + 7.9819176174485603e-16))) + (fConst0 * (fConst201 + (fRec4[0] * (fConst203 + ((fRec0[0] * (fConst205 + (fConst206 * fRec0[0]))) + (fConst0 * (fRec4[0] * (fConst208 + (fRec0[0] * (fConst210 + (fConst211 * fRec0[0])))))))))))) + 8.5246880154350698e-16)) + (fRec0[0] * (fConst213 + ((fConst214 * fRec0[0]) + 3.9909588087242801e-15)))) + (fRec5[0] * (((fRec0[0] * (fConst216 + ((fConst217 * fRec0[0]) + 3.19276704697943e-17))) + (fConst0 * (fConst219 + ((fRec3[0] * (fConst221 + ((fRec0[0] * (fConst223 + (fConst224 * fRec0[0]))) + (fConst0 * (fRec4[0] * (fConst226 + ((fRec0[0] * (fConst228 + (fConst229 * fRec0[0]))) + (fConst0 * (fRec4[0] * (fConst231 + (fRec0[0] * (fConst233 + (fConst234 * fRec0[0]))))))))))))) + (fRec4[0] * (fConst236 + ((fRec0[0] * (fConst238 + (fConst239 * fRec0[0]))) + (fConst0 * (fRec4[0] * (fConst241 + (fRec0[0] * (fConst243 + (fConst244 * fRec0[0]))))))))))))) + 3.4098752061740298e-17))) + (fRec4[0] * (((fRec0[0] * (fConst246 + ((fConst247 * fRec0[0]) + -7.9819176174485603e-16))) + (fConst0 * (fConst249 + (fRec4[0] * (fConst251 + (fRec0[0] * (fConst253 + (fConst254 * fRec0[0])))))))) + -8.5246880154350698e-16))) + 4.2623440077175302e-15)))) / fTemp0));
		output0[i] = FAUSTFLOAT((fConst2 * (((fRec0[0] * fRec1[0]) * ((((((fRec2[0] * ((fConst292 + ((fRec3[0] * (fConst294 + (fConst295 * fRec4[0]))) + (fConst296 * fRec4[0]))) + (fRec5[0] * (fConst298 + (fConst300 * fRec3[0]))))) + (fRec2[1] * ((fConst302 + ((fRec3[0] * (fConst304 + (fConst305 * fRec4[0]))) + (fConst306 * fRec4[0]))) + (fRec5[0] * (fConst308 + (fConst310 * fRec3[0])))))) + (fRec2[2] * ((fConst312 + ((fRec3[0] * (fConst314 + (fConst315 * fRec4[0]))) + (fConst316 * fRec4[0]))) + (fRec5[0] * (fConst318 + (fConst320 * fRec3[0])))))) + (fRec2[3] * ((fConst321 + ((fRec3[0] * (fConst322 + (fConst323 * fRec4[0]))) + (fConst324 * fRec4[0]))) + (fRec5[0] * (fConst325 + (fConst326 * fRec3[0])))))) + (fRec2[4] * ((fConst327 + ((fRec3[0] * (fConst328 + (fConst329 * fRec4[0]))) + (fConst330 * fRec4[0]))) + (fRec5[0] * (fConst331 + (fConst332 * fRec3[0])))))) + (fRec2[5] * ((fConst333 + ((fRec3[0] * (fConst334 + (fConst335 * fRec4[0]))) + (fConst336 * fRec4[0]))) + (fRec5[0] * (fConst337 + (fConst338 * fRec3[0]))))))) / fTemp0)));
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		for (int j0 = 5; (j0 > 0); j0 = (j0 - 1)) {
			fRec2[j0] = fRec2[(j0 - 1)];
		}
	}
#undef fVslider0
#undef fVslider1
#undef fVslider2
#undef fVslider3
#undef fVslider4
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case BASS: 
		fVslider2_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case INPUT: 
		fVslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case MIDDLE: 
		fVslider4_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case TREBLE: 
		fVslider3_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case VOLUME: 
		fVslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
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
   BASS, 
   INPUT, 
   MIDDLE, 
   TREBLE, 
   VOLUME, 
} PortIndex;
*/

} // end namespace gx_alembic
