// generated from file '../src/LV2/faust/gx_alembic.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace gx_alembic {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec0[2];
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	double fConst4;
	double fConst5;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec1[2];
	double fConst6;
	double fConst7;
	double fConst8;
	double fConst9;
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
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec2[2];
	double fConst38;
	double fConst39;
	double fConst40;
	double fConst41;
	double fConst42;
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fRec3[2];
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
	double fRec4[6];
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
	double fConst339;
	double fConst340;
	double fConst341;
	double fConst342;
	double fConst343;
	double fConst344;
	double fConst345;
	double fConst346;
	double fConst347;
	double fConst348;
	double fConst349;
	double fConst350;
	double fConst351;
	double fConst352;
	double fConst353;
	double fConst354;
	double fConst355;
	double fConst356;
	FAUSTFLOAT fVslider4;
	FAUSTFLOAT	*fVslider4_;
	double fRec5[2];

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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec0[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec1[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec2[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec3[l3] = 0.0;
	for (int l4 = 0; l4 < 6; l4 = l4 + 1) fRec4[l4] = 0.0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fRec5[l5] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = 6.4815418981162e-23 * fConst0;
	fConst2 = fConst0 * (fConst0 * (fConst1 + 2.99095367015295e-21) + 3.38701967358278e-20) + 9.9773970218107e-20;
	fConst3 = fConst0 * (fConst0 * (-2.99095367015295e-21 - fConst1) + -3.38701967358278e-20);
	fConst4 = 6.9222867471881e-23 * fConst0;
	fConst5 = fConst0 * (fConst0 * (-3.19433851972335e-21 - fConst4) + -3.61733701138641e-20);
	fConst6 = 6.22837159378651e-23 * fConst0;
	fConst7 = fConst0 * (fConst0 * (fConst6 + -5.51032162701814e-19) + -2.55264149017724e-17);
	fConst8 = 5.83180860841434e-23 * fConst0;
	fConst9 = fConst0 * (fConst0 * (fConst0 * (5.15947717885593e-19 - fConst8) + 2.3901137548476e-17) + 2.70887949322196e-16) + 7.98191761744856e-16;
	fConst10 = fConst0 * (fConst0 * (fConst0 * (fConst8 + -5.15947717885593e-19) + -2.3901137548476e-17) + -2.70887949322196e-16);
	fConst11 = 6.80009214340617e-24 * fConst0;
	fConst12 = fConst0 * (fConst0 * (3.86721597525567e-20 - fConst11) + 6.80858259239558e-19) + 2.34269282072115e-18;
	fConst13 = fConst0 * (fConst0 * (fConst11 + -3.86721597525567e-20) + -6.80858259239558e-19);
	fConst14 = 7.26249840915779e-24 * fConst0;
	fConst15 = fConst0 * (fConst0 * (fConst14 + -4.13018666157306e-20) + -7.27156620867848e-19);
	fConst16 = 4.85720867386155e-24 * fConst0;
	fConst17 = fConst0 * (fConst16 + 8.53036904160507e-23) + 2.93335472441235e-22;
	fConst18 = fConst0 * (-8.53036904160507e-23 - fConst16);
	fConst19 = 5.18749886368413e-24 * fConst0;
	fConst20 = fConst0 * (-9.11043413643421e-23 - fConst19);
	fConst21 = mydsp_faustpower2_f(fConst0);
	fConst22 = 4.49377473953314e-25 * fConst0;
	fConst23 = fConst0 * (fConst0 * (fConst0 * (-3.45203422865533e-21 - fConst22) + -7.39641502461285e-20) + -4.31004728634658e-19) + -7.50300256040165e-19;
	fConst24 = fConst0 * (fConst0 * (fConst0 * (fConst22 + 3.45203422865533e-21) + 7.39641502461285e-20) + 4.31004728634658e-19);
	fConst25 = 4.79935142182139e-25 * fConst0;
	fConst26 = fConst0 * (fConst0 * (fConst0 * (fConst25 + 3.68677255620389e-21) + 7.89937124628652e-20) + 4.60313050181815e-19);
	fConst27 = 1.08708956034044e-25 * fConst0;
	fConst28 = fConst0 * (fConst0 * (6.17731871560931e-22 - fConst27) + 1.08757485215501e-20) + 3.74212252700032e-20;
	fConst29 = fConst0 * (fConst0 * (fConst27 + -6.17731871560931e-22) + -1.08757485215501e-20);
	fConst30 = 1.16101165044359e-25 * fConst0;
	fConst31 = fConst0 * (fConst0 * (fConst30 + -6.59737638827074e-22) + -1.16152994210155e-20);
	fConst32 = 7.76492543100316e-26 * fConst0;
	fConst33 = fConst0 * (fConst32 + 1.36369845222938e-24) + 4.68937660025103e-24;
	fConst34 = fConst0 * (-1.36369845222938e-24 - fConst32);
	fConst35 = 8.29294036031137e-26 * fConst0;
	fConst36 = fConst0 * (-1.45642994698098e-24 - fConst35);
	fConst37 = mydsp_faustpower3_f(fConst0);
	fConst38 = 2.81099951792073e-23 * fConst0;
	fConst39 = fConst0 * (fConst0 * (fConst0 * (-2.15807364568921e-19 - fConst38) + -4.37590986205892e-18) + -2.25888916645809e-17) + -3.19276704697943e-17;
	fConst40 = fConst0 * (fConst0 * (fConst0 * (fConst38 + 2.15807364568921e-19) + 4.37590986205892e-18) + 2.25888916645809e-17);
	fConst41 = 3.00214748513934e-23 * fConst0;
	fConst42 = fConst0 * (fConst0 * (fConst0 * (fConst41 + 2.30482265359608e-19) + 4.67347173267892e-18) + 2.41249362977723e-17);
	fConst43 = 9.32295933998211e-25 * fConst0;
	fConst44 = fConst0 * (fConst0 * (fConst0 * (8.13465102081422e-21 - fConst43) + 8.27894207186978e-19) + 1.21893473917967e-17) + 3.98098141170247e-17;
	fConst45 = fConst0 * (fConst0 * (fConst0 * (fConst43 + -8.13465102081422e-21) + -8.27894207186978e-19) + -1.21893473917967e-17);
	fConst46 = 9.95692057510089e-25 * fConst0;
	fConst47 = fConst0 * (fConst0 * (fConst0 * (fConst46 + -8.68780729022958e-21) + -8.84191013275692e-19) + -1.30182230144389e-17);
	fConst48 = 1.03616486126347e-24 * fConst0;
	fConst49 = fConst0 * (fConst0 * (fConst48 + 1.0400884417695e-22) + 1.52836235209424e-21) + 4.98869851090535e-21;
	fConst50 = fConst0 * (fConst0 * (-1.0400884417695e-22 - fConst48) + -1.52836235209424e-21);
	fConst51 = 1.10662407182939e-24 * fConst0;
	fConst52 = fConst0 * (fConst0 * (-1.11081445580983e-22 - fConst51) + -1.63229099203665e-21);
	fConst53 = 4.66400408138021e-24 * fConst0;
	fConst54 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (-4.21107717183568e-20 - fConst53) + -4.69643971510767e-18) + -8.52210149990995e-17) + -4.70934759609501e-16) + -7.98191761744856e-16;
	fConst55 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst53 + 4.21107717183568e-20) + 4.69643971510767e-18) + 8.52210149990995e-17) + 4.70934759609501e-16);
	fConst56 = 4.98115635891407e-24 * fConst0;
	fConst57 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst56 + 4.49743041952051e-20) + 5.01579761573499e-18) + 9.10160440190383e-17) + 5.02958323262947e-16);
	fConst58 = 2.91748340409741e-22 * fConst0;
	fConst59 = fConst0 * (fConst0 * (fConst0 * (-2.60665717245934e-18 - fConst58) + -1.19810519513002e-16) + -1.35533771234294e-15) + -3.99095880872428e-15;
	fConst60 = fConst0 * (fConst0 * (fConst0 * (fConst58 + 2.60665717245934e-18) + 1.19810519513002e-16) + 1.35533771234294e-15);
	fConst61 = 3.11587227557603e-22 * fConst0;
	fConst62 = fConst0 * (fConst0 * (fConst0 * (fConst61 + 2.78390986018658e-18) + 1.27957634839887e-16) + 1.44750067678226e-15);
	fConst63 = 7.96061742599918e-22 * fConst0;
	fConst64 = fConst37 * (fConst0 * (4.56560363232067e-18 - fConst63) + -3.04019770269112e-17);
	fConst65 = 4.97962026222076e-20 * fConst0;
	fConst66 = fConst21 * (fConst0 * (fConst65 + -2.85365632064909e-16) + 1.90022438253841e-15);
	fConst67 = 5.68615530428513e-21 * fConst0;
	fConst68 = mydsp_faustpower4_f(fConst0);
	fConst69 = fConst68 * (fConst67 + -3.79077020285676e-20);
	fConst70 = fConst21 * (fConst0 * (fConst0 * (9.98505002369502e-19 - fConst67) + -4.85778329480724e-15) + 3.23425287520332e-14);
	fConst71 = 3.55687161587197e-19 * fConst0;
	fConst72 = fConst0 * (1.44694505189894e-17 - fConst71) + -8.06546851671652e-17;
	fConst73 = fConst0 * (fConst71 + -1.44694505189894e-17) + 8.06546851671652e-17;
	fConst74 = fConst3 + -9.9773970218107e-20;
	fConst75 = fConst5 + -1.06558600192938e-19;
	fConst76 = fConst7 + -2.89308329876105e-16;
	fConst77 = fConst13 + -2.34269282072115e-18;
	fConst78 = fConst15 + -2.50199593253019e-18;
	fConst79 = fConst18 + -2.93335472441235e-22;
	fConst80 = fConst20 + -3.13282284567239e-22;
	fConst81 = fConst24 + 7.50300256040165e-19;
	fConst82 = fConst26 + 8.01320673450896e-19;
	fConst83 = fConst29 + -3.74212252700032e-20;
	fConst84 = fConst31 + -3.99658685883635e-20;
	fConst85 = fConst34 + -4.68937660025103e-24;
	fConst86 = fConst36 + -5.0082542090681e-24;
	fConst87 = fConst45 + -3.98098141170247e-17;
	fConst88 = fConst47 + -4.25168814769824e-17;
	fConst89 = fConst50 + -4.98869851090535e-21;
	fConst90 = fConst52 + -5.32793000964692e-21;
	fConst91 = fConst0 * (fConst0 * (fConst1 + -2.99095367015295e-21) + 3.38701967358278e-20) + -9.9773970218107e-20;
	fConst92 = fConst0 * (fConst0 * (2.99095367015295e-21 - fConst1) + -3.38701967358278e-20) + 9.9773970218107e-20;
	fConst93 = fConst0 * (fConst0 * (3.19433851972335e-21 - fConst4) + -3.61733701138641e-20) + 1.06558600192938e-19;
	fConst94 = fConst0 * (fConst0 * (fConst6 + 5.51032162701814e-19) + -2.55264149017724e-17) + 2.89308329876105e-16;
	fConst95 = fConst0 * (fConst0 * (fConst0 * (-5.15947717885593e-19 - fConst8) + 2.3901137548476e-17) + -2.70887949322196e-16) + 7.98191761744856e-16;
	fConst96 = fConst0 * (fConst0 * (fConst0 * (fConst8 + 5.15947717885593e-19) + -2.3901137548476e-17) + 2.70887949322196e-16);
	fConst97 = fConst0 * (fConst0 * (-3.86721597525567e-20 - fConst11) + 6.80858259239558e-19) + -2.34269282072115e-18;
	fConst98 = fConst0 * (fConst0 * (fConst11 + 3.86721597525567e-20) + -6.80858259239558e-19) + 2.34269282072115e-18;
	fConst99 = fConst0 * (fConst0 * (fConst14 + 4.13018666157306e-20) + -7.27156620867848e-19) + 2.50199593253019e-18;
	fConst100 = fConst0 * (fConst16 + -8.53036904160507e-23) + 2.93335472441235e-22;
	fConst101 = fConst0 * (8.53036904160507e-23 - fConst16) + -2.93335472441235e-22;
	fConst102 = fConst0 * (9.11043413643421e-23 - fConst19) + -3.13282284567239e-22;
	fConst103 = fConst0 * (fConst0 * (fConst0 * (2.15807364568921e-19 - fConst38) + -4.37590986205892e-18) + 2.25888916645809e-17) + -3.19276704697943e-17;
	fConst104 = fConst0 * (fConst0 * (fConst0 * (fConst38 + -2.15807364568921e-19) + 4.37590986205892e-18) + -2.25888916645809e-17);
	fConst105 = fConst0 * (fConst0 * (fConst0 * (fConst22 + -3.45203422865533e-21) + 7.39641502461285e-20) + -4.31004728634658e-19) + 7.50300256040165e-19;
	fConst106 = fConst0 * (fConst0 * (fConst0 * (3.45203422865533e-21 - fConst22) + -7.39641502461285e-20) + 4.31004728634658e-19) + -7.50300256040165e-19;
	fConst107 = fConst0 * (fConst0 * (fConst0 * (3.68677255620389e-21 - fConst25) + -7.89937124628652e-20) + 4.60313050181815e-19) + -8.01320673450896e-19;
	fConst108 = fConst0 * (fConst0 * (fConst27 + 6.17731871560931e-22) + -1.08757485215501e-20) + 3.74212252700032e-20;
	fConst109 = fConst0 * (fConst0 * (-6.17731871560931e-22 - fConst27) + 1.08757485215501e-20) + -3.74212252700032e-20;
	fConst110 = fConst0 * (fConst0 * (-6.59737638827074e-22 - fConst30) + 1.16152994210155e-20) + -3.99658685883635e-20;
	fConst111 = fConst0 * (1.36369845222938e-24 - fConst32) + -4.68937660025103e-24;
	fConst112 = fConst0 * (fConst32 + -1.36369845222938e-24) + 4.68937660025103e-24;
	fConst113 = fConst0 * (fConst35 + -1.45642994698098e-24) + 5.0082542090681e-24;
	fConst114 = fConst0 * (fConst0 * (fConst0 * (fConst41 + -2.30482265359608e-19) + 4.67347173267892e-18) + -2.41249362977723e-17);
	fConst115 = fConst0 * (fConst0 * (fConst0 * (2.60665717245934e-18 - fConst58) + -1.19810519513002e-16) + 1.35533771234294e-15) + -3.99095880872428e-15;
	fConst116 = fConst0 * (fConst0 * (fConst0 * (fConst58 + -2.60665717245934e-18) + 1.19810519513002e-16) + -1.35533771234294e-15);
	fConst117 = fConst0 * (fConst0 * (fConst0 * (fConst43 + 8.13465102081422e-21) + -8.27894207186978e-19) + 1.21893473917967e-17) + -3.98098141170247e-17;
	fConst118 = fConst0 * (fConst0 * (fConst0 * (-8.13465102081422e-21 - fConst43) + 8.27894207186978e-19) + -1.21893473917967e-17) + 3.98098141170247e-17;
	fConst119 = fConst0 * (fConst0 * (fConst0 * (-8.68780729022958e-21 - fConst46) + 8.84191013275692e-19) + -1.30182230144389e-17) + 4.25168814769824e-17;
	fConst120 = fConst0 * (fConst0 * (1.0400884417695e-22 - fConst48) + -1.52836235209424e-21) + 4.98869851090535e-21;
	fConst121 = fConst0 * (fConst0 * (fConst48 + -1.0400884417695e-22) + 1.52836235209424e-21) + -4.98869851090535e-21;
	fConst122 = fConst0 * (fConst0 * (fConst51 + -1.11081445580983e-22) + 1.63229099203665e-21) + -5.32793000964692e-21;
	fConst123 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst53 + -4.21107717183568e-20) + 4.69643971510767e-18) + -8.52210149990995e-17) + 4.70934759609501e-16) + -7.98191761744856e-16;
	fConst124 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (4.21107717183568e-20 - fConst53) + -4.69643971510767e-18) + 8.52210149990995e-17) + -4.70934759609501e-16);
	fConst125 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (4.49743041952051e-20 - fConst56) + -5.01579761573499e-18) + 9.10160440190383e-17) + -5.02958323262947e-16);
	fConst126 = fConst0 * (fConst0 * (fConst0 * (fConst61 + -2.78390986018658e-18) + 1.27957634839887e-16) + -1.44750067678226e-15);
	fConst127 = 1.94446256943486e-22 * fConst0;
	fConst128 = fConst0 * (fConst0 * (2.99095367015295e-21 - fConst127) + 3.38701967358278e-20) + -2.99321910654321e-19;
	fConst129 = fConst0 * (fConst0 * (fConst127 + -2.99095367015295e-21) + -3.38701967358278e-20) + 2.99321910654321e-19;
	fConst130 = 2.07668602415643e-22 * fConst0;
	fConst131 = fConst0 * (fConst0 * (fConst130 + -3.19433851972335e-21) + -3.61733701138641e-20) + 3.19675800578815e-19;
	fConst132 = 1.86851147813595e-22 * fConst0;
	fConst133 = fConst0 * (fConst0 * (-5.51032162701814e-19 - fConst132) + -2.55264149017724e-17) + 8.67924989628316e-16;
	fConst134 = 1.7495425825243e-22 * fConst0;
	fConst135 = fConst0 * (fConst0 * (fConst0 * (fConst134 + 5.15947717885593e-19) + 2.3901137548476e-17) + -8.12663847966588e-16) + 3.99095880872428e-15;
	fConst136 = fConst0 * (fConst0 * (fConst0 * (-5.15947717885593e-19 - fConst134) + -2.3901137548476e-17) + 8.12663847966588e-16);
	fConst137 = 2.04002764302185e-23 * fConst0;
	fConst138 = fConst0 * (fConst0 * (fConst137 + 3.86721597525567e-20) + 6.80858259239558e-19) + -7.02807846216346e-18;
	fConst139 = fConst0 * (fConst0 * (-3.86721597525567e-20 - fConst137) + -6.80858259239558e-19) + 7.02807846216346e-18;
	fConst140 = 2.17874952274734e-23 * fConst0;
	fConst141 = fConst0 * (fConst0 * (-4.13018666157306e-20 - fConst140) + -7.27156620867848e-19) + 7.50598779759058e-18;
	fConst142 = 1.45716260215846e-23 * fConst0;
	fConst143 = fConst0 * (8.53036904160507e-23 - fConst142) + 2.93335472441235e-22;
	fConst144 = fConst0 * (fConst142 + -8.53036904160507e-23) + -2.93335472441235e-22;
	fConst145 = 1.55624965910524e-23 * fConst0;
	fConst146 = fConst0 * (fConst145 + -9.11043413643421e-23) + -3.13282284567239e-22;
	fConst147 = 8.43299855376218e-23 * fConst0;
	fConst148 = fConst0 * (fConst0 * (fConst0 * (fConst147 + -2.15807364568921e-19) + -4.37590986205892e-18) + 6.77666749937426e-17) + -1.59638352348971e-16;
	fConst149 = fConst0 * (fConst0 * (fConst0 * (2.15807364568921e-19 - fConst147) + 4.37590986205892e-18) + -6.77666749937426e-17);
	fConst150 = 2.24688736976657e-24 * fConst0;
	fConst151 = fConst0 * (fConst0 * (fConst0 * (1.0356102685966e-20 - fConst150) + -7.39641502461285e-20) + -4.31004728634658e-19) + 2.2509007681205e-18;
	fConst152 = fConst0 * (fConst0 * (fConst0 * (fConst150 + -1.0356102685966e-20) + 7.39641502461285e-20) + 4.31004728634658e-19) + -2.2509007681205e-18;
	fConst153 = 2.39967571091069e-24 * fConst0;
	fConst154 = fConst0 * (fConst0 * (fConst0 * (fConst153 + -1.10603176686117e-20) + 7.89937124628652e-20) + 4.60313050181815e-19) + -2.40396202035269e-18;
	fConst155 = 5.43544780170221e-25 * fConst0;
	fConst156 = fConst0 * (fConst0 * (-1.85319561468279e-21 - fConst155) + 1.08757485215501e-20) + 3.74212252700032e-20;
	fConst157 = fConst0 * (fConst0 * (fConst155 + 1.85319561468279e-21) + -1.08757485215501e-20) + -3.74212252700032e-20;
	fConst158 = 5.80505825221796e-25 * fConst0;
	fConst159 = fConst0 * (fConst0 * (fConst158 + 1.97921291648122e-21) + -1.16152994210155e-20) + -3.99658685883635e-20;
	fConst160 = 3.88246271550158e-25 * fConst0;
	fConst161 = fConst0 * (fConst160 + -4.09109535668814e-24) + 4.68937660025103e-24;
	fConst162 = fConst0 * (4.09109535668814e-24 - fConst160) + -4.68937660025103e-24;
	fConst163 = 4.14647018015568e-25 * fConst0;
	fConst164 = fConst0 * (4.36928984094294e-24 - fConst163) + -5.0082542090681e-24;
	fConst165 = 9.00644245541801e-23 * fConst0;
	fConst166 = fConst0 * (fConst0 * (fConst0 * (2.30482265359608e-19 - fConst165) + 4.67347173267892e-18) + -7.2374808893317e-17);
	fConst167 = 8.75245021229223e-22 * fConst0;
	fConst168 = fConst0 * (fConst0 * (fConst0 * (fConst167 + -2.60665717245934e-18) + -1.19810519513002e-16) + 4.06601313702883e-15) + -1.99547940436214e-14;
	fConst169 = fConst0 * (fConst0 * (fConst0 * (2.60665717245934e-18 - fConst167) + 1.19810519513002e-16) + -4.06601313702883e-15);
	fConst170 = 4.66147966999105e-24 * fConst0;
	fConst171 = fConst0 * (fConst0 * (fConst0 * (-2.44039530624426e-20 - fConst170) + 8.27894207186978e-19) + 1.21893473917967e-17) + -1.19429442351074e-16;
	fConst172 = fConst0 * (fConst0 * (fConst0 * (fConst170 + 2.44039530624426e-20) + -8.27894207186978e-19) + -1.21893473917967e-17) + 1.19429442351074e-16;
	fConst173 = 4.97846028755044e-24 * fConst0;
	fConst174 = fConst0 * (fConst0 * (fConst0 * (fConst173 + 2.60634218706887e-20) + -8.84191013275692e-19) + -1.30182230144389e-17) + 1.27550644430947e-16;
	fConst175 = 5.18082430631737e-24 * fConst0;
	fConst176 = fConst0 * (fConst0 * (fConst175 + -3.12026532530851e-22) + 1.52836235209424e-21) + 4.98869851090535e-21;
	fConst177 = fConst0 * (fConst0 * (3.12026532530851e-22 - fConst175) + -1.52836235209424e-21) + -4.98869851090535e-21;
	fConst178 = 5.53312035914695e-24 * fConst0;
	fConst179 = fConst0 * (fConst0 * (3.33244336742949e-22 - fConst178) + -1.63229099203665e-21) + -5.32793000964692e-21;
	fConst180 = 2.33200204069011e-23 * fConst0;
	fConst181 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (1.26332315155071e-19 - fConst180) + -4.69643971510767e-18) + -8.52210149990995e-17) + 1.4128042788285e-15) + -3.99095880872428e-15;
	fConst182 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst180 + -1.26332315155071e-19) + 4.69643971510767e-18) + 8.52210149990995e-17) + -1.4128042788285e-15);
	fConst183 = 2.49057817945703e-23 * fConst0;
	fConst184 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst183 + -1.34922912585615e-19) + 5.01579761573499e-18) + 9.10160440190383e-17) + -1.50887496978884e-15);
	fConst185 = 9.3476168267281e-22 * fConst0;
	fConst186 = fConst0 * (fConst0 * (fConst0 * (2.78390986018658e-18 - fConst185) + 1.27957634839887e-16) + -4.34250203034679e-15);
	fConst187 = 1.29630837962324e-22 * fConst0;
	fConst188 = fConst0 * (fConst0 * (fConst187 + 5.98190734030589e-21) + -6.77403934716556e-20) + -1.99547940436214e-19;
	fConst189 = fConst0 * (fConst0 * (-5.98190734030589e-21 - fConst187) + 6.77403934716556e-20) + 1.99547940436214e-19;
	fConst190 = 1.38445734943762e-22 * fConst0;
	fConst191 = fConst0 * (fConst0 * (-6.38867703944669e-21 - fConst190) + 7.23467402277282e-20) + 2.13117200385877e-19;
	fConst192 = 1.2456743187573e-22 * fConst0;
	fConst193 = fConst0 * (fConst0 * (fConst192 + -1.10206432540363e-18) + 5.10528298035447e-17) + 5.78616659752211e-16;
	fConst194 = 1.16636172168287e-22 * fConst0;
	fConst195 = fConst0 * (fConst0 * (fConst0 * (1.03189543577119e-18 - fConst194) + -4.7802275096952e-17) + -5.41775898644392e-16) + 7.98191761744856e-15;
	fConst196 = fConst0 * (fConst0 * (fConst0 * (fConst194 + -1.03189543577119e-18) + 4.7802275096952e-17) + 5.41775898644392e-16);
	fConst197 = 1.36001842868123e-23 * fConst0;
	fConst198 = fConst0 * (fConst0 * (7.73443195051134e-20 - fConst197) + -1.36171651847912e-18) + -4.68538564144231e-18;
	fConst199 = fConst0 * (fConst0 * (fConst197 + -7.73443195051134e-20) + 1.36171651847912e-18) + 4.68538564144231e-18;
	fConst200 = 1.45249968183156e-23 * fConst0;
	fConst201 = fConst0 * (fConst0 * (fConst200 + -8.26037332314611e-20) + 1.4543132417357e-18) + 5.00399186506038e-18;
	fConst202 = 9.7144173477231e-24 * fConst0;
	fConst203 = fConst0 * (fConst202 + 1.70607380832101e-22) + -5.86670944882469e-22;
	fConst204 = fConst0 * (-1.70607380832101e-22 - fConst202) + 5.86670944882469e-22;
	fConst205 = 1.03749977273683e-23 * fConst0;
	fConst206 = fConst0 * (-1.82208682728684e-22 - fConst205) + 6.26564569134477e-22;
	fConst207 = 5.62199903584146e-23 * fConst0;
	fConst208 = fConst0 * (fConst0 * (fConst0 * (-4.31614729137842e-19 - fConst207) + 8.75181972411783e-18) + 4.51777833291617e-17) + -3.19276704697943e-16;
	fConst209 = fConst0 * (fConst0 * (fConst0 * (fConst207 + 4.31614729137842e-19) + -8.75181972411783e-18) + -4.51777833291617e-17);
	fConst210 = 4.49377473953314e-24 * fConst0;
	fConst211 = fConst0 * (fConst0 * (fConst0 * (fConst210 + -6.90406845731066e-21) + -1.47928300492257e-19) + 8.62009457269317e-19) + 1.50060051208033e-18;
	fConst212 = fConst0 * (fConst0 * (fConst0 * (6.90406845731066e-21 - fConst210) + 1.47928300492257e-19) + -8.62009457269317e-19) + -1.50060051208033e-18;
	fConst213 = 4.79935142182139e-24 * fConst0;
	fConst214 = fConst0 * (fConst0 * (fConst0 * (7.37354511240778e-21 - fConst213) + 1.5798742492573e-19) + -9.2062610036363e-19) + -1.60264134690179e-18;
	fConst215 = 1.08708956034044e-24 * fConst0;
	fConst216 = fConst0 * (fConst0 * (fConst215 + 1.23546374312186e-21) + 2.17514970431002e-20) + -7.48424505400065e-20;
	fConst217 = fConst0 * (fConst0 * (-1.23546374312186e-21 - fConst215) + -2.17514970431002e-20) + 7.48424505400065e-20;
	fConst218 = 1.16101165044359e-24 * fConst0;
	fConst219 = fConst0 * (fConst0 * (-1.31947527765415e-21 - fConst218) + -2.3230598842031e-20) + 7.99317371767269e-20;
	fConst220 = 7.76492543100316e-25 * fConst0;
	fConst221 = fConst0 * (2.72739690445876e-24 - fConst220) + 9.37875320050206e-24;
	fConst222 = fConst0 * (fConst220 + -2.72739690445876e-24) + -9.37875320050206e-24;
	fConst223 = 8.29294036031137e-25 * fConst0;
	fConst224 = fConst0 * (fConst223 + -2.91285989396196e-24) + -1.00165084181362e-23;
	fConst225 = 6.00429497027867e-23 * fConst0;
	fConst226 = fConst0 * (fConst0 * (fConst0 * (fConst225 + 4.60964530719215e-19) + -9.34694346535784e-18) + -4.82498725955447e-17);
	fConst227 = 5.83496680819482e-22 * fConst0;
	fConst228 = fConst0 * (fConst0 * (fConst0 * (-5.21331434491869e-18 - fConst227) + 2.39621039026005e-16) + 2.71067542468589e-15) + -3.99095880872428e-14;
	fConst229 = fConst0 * (fConst0 * (fConst0 * (fConst227 + 5.21331434491869e-18) + -2.39621039026005e-16) + -2.71067542468589e-15);
	fConst230 = 9.32295933998211e-24 * fConst0;
	fConst231 = fConst0 * (fConst0 * (fConst0 * (fConst230 + 1.62693020416284e-20) + 1.65578841437396e-18) + -2.43786947835935e-17) + -7.96196282340494e-17;
	fConst232 = fConst0 * (fConst0 * (fConst0 * (-1.62693020416284e-20 - fConst230) + -1.65578841437396e-18) + 2.43786947835935e-17) + 7.96196282340494e-17;
	fConst233 = 9.95692057510089e-24 * fConst0;
	fConst234 = fConst0 * (fConst0 * (fConst0 * (-1.73756145804592e-20 - fConst233) + -1.76838202655138e-18) + 2.60364460288779e-17) + 8.50337629539648e-17;
	fConst235 = 1.03616486126347e-23 * fConst0;
	fConst236 = fConst0 * (fConst0 * (2.08017688353901e-22 - fConst235) + 3.05672470418848e-21) + -9.97739702181071e-21;
	fConst237 = fConst0 * (fConst0 * (fConst235 + -2.08017688353901e-22) + -3.05672470418848e-21) + 9.97739702181071e-21;
	fConst238 = 1.10662407182939e-23 * fConst0;
	fConst239 = fConst0 * (fConst0 * (fConst238 + -2.22162891161966e-22) + -3.26458198407329e-21) + 1.06558600192938e-20;
	fConst240 = 4.66400408138021e-23 * fConst0;
	fConst241 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst240 + -8.42215434367137e-20) + -9.39287943021533e-18) + 1.70442029998199e-16) + 9.41869519219001e-16) + -7.98191761744856e-15;
	fConst242 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (8.42215434367137e-20 - fConst240) + 9.39287943021533e-18) + -1.70442029998199e-16) + -9.41869519219001e-16);
	fConst243 = 4.98115635891407e-23 * fConst0;
	fConst244 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (8.99486083904102e-20 - fConst243) + 1.003159523147e-17) + -1.82032088038077e-16) + -1.00591664652589e-15);
	fConst245 = 6.23174455115207e-22 * fConst0;
	fConst246 = fConst0 * (fConst0 * (fConst0 * (fConst245 + 5.56781972037316e-18) + -2.55915269679773e-16) + -2.89500135356453e-15);
	fConst247 = fConst0 * (fConst0 * (fConst187 + -5.98190734030589e-21) + -6.77403934716556e-20) + 1.99547940436214e-19;
	fConst248 = fConst0 * (fConst0 * (5.98190734030589e-21 - fConst187) + 6.77403934716556e-20) + -1.99547940436214e-19;
	fConst249 = fConst0 * (fConst0 * (6.38867703944669e-21 - fConst190) + 7.23467402277282e-20) + -2.13117200385877e-19;
	fConst250 = fConst0 * (fConst0 * (fConst192 + 1.10206432540363e-18) + 5.10528298035447e-17) + -5.78616659752211e-16;
	fConst251 = fConst0 * (fConst0 * (fConst0 * (-1.03189543577119e-18 - fConst194) + -4.7802275096952e-17) + 5.41775898644392e-16) + 7.98191761744856e-15;
	fConst252 = fConst0 * (fConst0 * (fConst0 * (fConst194 + 1.03189543577119e-18) + 4.7802275096952e-17) + -5.41775898644392e-16);
	fConst253 = fConst0 * (fConst0 * (-7.73443195051134e-20 - fConst197) + -1.36171651847912e-18) + 4.68538564144231e-18;
	fConst254 = fConst0 * (fConst0 * (fConst197 + 7.73443195051134e-20) + 1.36171651847912e-18) + -4.68538564144231e-18;
	fConst255 = fConst0 * (fConst0 * (fConst200 + 8.26037332314611e-20) + 1.4543132417357e-18) + -5.00399186506038e-18;
	fConst256 = fConst0 * (fConst202 + -1.70607380832101e-22) + -5.86670944882469e-22;
	fConst257 = fConst0 * (1.70607380832101e-22 - fConst202) + 5.86670944882469e-22;
	fConst258 = fConst0 * (1.82208682728684e-22 - fConst205) + 6.26564569134477e-22;
	fConst259 = fConst0 * (fConst0 * (fConst0 * (4.31614729137842e-19 - fConst207) + 8.75181972411783e-18) + -4.51777833291617e-17) + -3.19276704697943e-16;
	fConst260 = fConst0 * (fConst0 * (fConst0 * (fConst207 + -4.31614729137842e-19) + -8.75181972411783e-18) + 4.51777833291617e-17);
	fConst261 = fConst0 * (fConst0 * (fConst0 * (-6.90406845731066e-21 - fConst210) + 1.47928300492257e-19) + 8.62009457269317e-19) + -1.50060051208033e-18;
	fConst262 = fConst0 * (fConst0 * (fConst0 * (fConst210 + 6.90406845731066e-21) + -1.47928300492257e-19) + -8.62009457269317e-19) + 1.50060051208033e-18;
	fConst263 = fConst0 * (fConst0 * (fConst0 * (fConst213 + 7.37354511240778e-21) + -1.5798742492573e-19) + -9.2062610036363e-19) + 1.60264134690179e-18;
	fConst264 = fConst0 * (fConst0 * (1.23546374312186e-21 - fConst215) + -2.17514970431002e-20) + -7.48424505400065e-20;
	fConst265 = fConst0 * (fConst0 * (fConst215 + -1.23546374312186e-21) + 2.17514970431002e-20) + 7.48424505400065e-20;
	fConst266 = fConst0 * (fConst0 * (fConst218 + -1.31947527765415e-21) + 2.3230598842031e-20) + 7.99317371767269e-20;
	fConst267 = fConst0 * (fConst220 + 2.72739690445876e-24) + -9.37875320050206e-24;
	fConst268 = fConst0 * (-2.72739690445876e-24 - fConst220) + 9.37875320050206e-24;
	fConst269 = fConst0 * (-2.91285989396196e-24 - fConst223) + 1.00165084181362e-23;
	fConst270 = fConst0 * (fConst0 * (fConst0 * (fConst225 + -4.60964530719215e-19) + -9.34694346535784e-18) + 4.82498725955447e-17);
	fConst271 = fConst0 * (fConst0 * (fConst0 * (5.21331434491869e-18 - fConst227) + 2.39621039026005e-16) + -2.71067542468589e-15) + -3.99095880872428e-14;
	fConst272 = fConst0 * (fConst0 * (fConst0 * (fConst227 + -5.21331434491869e-18) + -2.39621039026005e-16) + 2.71067542468589e-15);
	fConst273 = fConst0 * (fConst0 * (fConst0 * (1.62693020416284e-20 - fConst230) + -1.65578841437396e-18) + -2.43786947835935e-17) + 7.96196282340494e-17;
	fConst274 = fConst0 * (fConst0 * (fConst0 * (fConst230 + -1.62693020416284e-20) + 1.65578841437396e-18) + 2.43786947835935e-17) + -7.96196282340494e-17;
	fConst275 = fConst0 * (fConst0 * (fConst0 * (fConst233 + -1.73756145804592e-20) + 1.76838202655138e-18) + 2.60364460288779e-17) + -8.50337629539648e-17;
	fConst276 = fConst0 * (fConst0 * (fConst235 + 2.08017688353901e-22) + -3.05672470418848e-21) + -9.97739702181071e-21;
	fConst277 = fConst0 * (fConst0 * (-2.08017688353901e-22 - fConst235) + 3.05672470418848e-21) + 9.97739702181071e-21;
	fConst278 = fConst0 * (fConst0 * (-2.22162891161966e-22 - fConst238) + 3.26458198407329e-21) + 1.06558600192938e-20;
	fConst279 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (-8.42215434367137e-20 - fConst240) + 9.39287943021533e-18) + 1.70442029998199e-16) + -9.41869519219001e-16) + -7.98191761744856e-15;
	fConst280 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst240 + 8.42215434367137e-20) + -9.39287943021533e-18) + -1.70442029998199e-16) + 9.41869519219001e-16);
	fConst281 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst243 + 8.99486083904102e-20) + -1.003159523147e-17) + -1.82032088038077e-16) + 1.00591664652589e-15);
	fConst282 = fConst0 * (fConst0 * (fConst0 * (fConst245 + -5.56781972037316e-18) + -2.55915269679773e-16) + 2.89500135356453e-15);
	fConst283 = fConst0 * (fConst0 * (-2.99095367015295e-21 - fConst127) + 3.38701967358278e-20) + 2.99321910654321e-19;
	fConst284 = fConst0 * (fConst0 * (fConst127 + 2.99095367015295e-21) + -3.38701967358278e-20) + -2.99321910654321e-19;
	fConst285 = fConst0 * (fConst0 * (fConst130 + 3.19433851972335e-21) + -3.61733701138641e-20) + -3.19675800578815e-19;
	fConst286 = fConst0 * (fConst0 * (5.51032162701814e-19 - fConst132) + -2.55264149017724e-17) + -8.67924989628316e-16;
	fConst287 = fConst0 * (fConst0 * (fConst0 * (fConst134 + -5.15947717885593e-19) + 2.3901137548476e-17) + 8.12663847966588e-16) + 3.99095880872428e-15;
	fConst288 = fConst0 * (fConst0 * (fConst0 * (5.15947717885593e-19 - fConst134) + -2.3901137548476e-17) + -8.12663847966588e-16);
	fConst289 = fConst0 * (fConst0 * (fConst137 + -3.86721597525567e-20) + 6.80858259239558e-19) + 7.02807846216346e-18;
	fConst290 = fConst0 * (fConst0 * (3.86721597525567e-20 - fConst137) + -6.80858259239558e-19) + -7.02807846216346e-18;
	fConst291 = fConst0 * (fConst0 * (4.13018666157306e-20 - fConst140) + -7.27156620867848e-19) + -7.50598779759058e-18;
	fConst292 = fConst0 * (-8.53036904160507e-23 - fConst142) + 2.93335472441235e-22;
	fConst293 = fConst0 * (fConst142 + 8.53036904160507e-23) + -2.93335472441235e-22;
	fConst294 = fConst0 * (fConst145 + 9.11043413643421e-23) + -3.13282284567239e-22;
	fConst295 = fConst0 * (fConst0 * (fConst0 * (fConst147 + 2.15807364568921e-19) + -4.37590986205892e-18) + -6.77666749937426e-17) + -1.59638352348971e-16;
	fConst296 = fConst0 * (fConst0 * (fConst0 * (-2.15807364568921e-19 - fConst147) + 4.37590986205892e-18) + 6.77666749937426e-17);
	fConst297 = fConst0 * (fConst0 * (fConst0 * (fConst150 + 1.0356102685966e-20) + 7.39641502461285e-20) + -4.31004728634658e-19) + -2.2509007681205e-18;
	fConst298 = fConst0 * (fConst0 * (fConst0 * (-1.0356102685966e-20 - fConst150) + -7.39641502461285e-20) + 4.31004728634658e-19) + 2.2509007681205e-18;
	fConst299 = fConst0 * (fConst0 * (fConst0 * (-1.10603176686117e-20 - fConst153) + -7.89937124628652e-20) + 4.60313050181815e-19) + 2.40396202035269e-18;
	fConst300 = fConst0 * (fConst0 * (fConst155 + -1.85319561468279e-21) + -1.08757485215501e-20) + 3.74212252700032e-20;
	fConst301 = fConst0 * (fConst0 * (1.85319561468279e-21 - fConst155) + 1.08757485215501e-20) + -3.74212252700032e-20;
	fConst302 = fConst0 * (fConst0 * (1.97921291648122e-21 - fConst158) + 1.16152994210155e-20) + -3.99658685883635e-20;
	fConst303 = fConst0 * (-4.09109535668814e-24 - fConst160) + -4.68937660025103e-24;
	fConst304 = fConst0 * (fConst160 + 4.09109535668814e-24) + 4.68937660025103e-24;
	fConst305 = fConst0 * (fConst163 + 4.36928984094294e-24) + 5.0082542090681e-24;
	fConst306 = fConst0 * (fConst0 * (fConst0 * (-2.30482265359608e-19 - fConst165) + 4.67347173267892e-18) + 7.2374808893317e-17);
	fConst307 = fConst0 * (fConst0 * (fConst0 * (fConst167 + 2.60665717245934e-18) + -1.19810519513002e-16) + -4.06601313702883e-15) + -1.99547940436214e-14;
	fConst308 = fConst0 * (fConst0 * (fConst0 * (-2.60665717245934e-18 - fConst167) + 1.19810519513002e-16) + 4.06601313702883e-15);
	fConst309 = fConst0 * (fConst0 * (fConst0 * (fConst170 + -2.44039530624426e-20) + -8.27894207186978e-19) + 1.21893473917967e-17) + 1.19429442351074e-16;
	fConst310 = fConst0 * (fConst0 * (fConst0 * (2.44039530624426e-20 - fConst170) + 8.27894207186978e-19) + -1.21893473917967e-17) + -1.19429442351074e-16;
	fConst311 = fConst0 * (fConst0 * (fConst0 * (2.60634218706887e-20 - fConst173) + 8.84191013275692e-19) + -1.30182230144389e-17) + -1.27550644430947e-16;
	fConst312 = fConst0 * (fConst0 * (-3.12026532530851e-22 - fConst175) + -1.52836235209424e-21) + 4.98869851090535e-21;
	fConst313 = fConst0 * (fConst0 * (fConst175 + 3.12026532530851e-22) + 1.52836235209424e-21) + -4.98869851090535e-21;
	fConst314 = fConst0 * (fConst0 * (fConst178 + 3.33244336742949e-22) + 1.63229099203665e-21) + -5.32793000964692e-21;
	fConst315 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst180 + 1.26332315155071e-19) + 4.69643971510767e-18) + -8.52210149990995e-17) + -1.4128042788285e-15) + -3.99095880872428e-15;
	fConst316 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (-1.26332315155071e-19 - fConst180) + -4.69643971510767e-18) + 8.52210149990995e-17) + 1.4128042788285e-15);
	fConst317 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (-1.34922912585615e-19 - fConst183) + -5.01579761573499e-18) + 9.10160440190383e-17) + 1.50887496978884e-15);
	fConst318 = fConst0 * (fConst0 * (fConst0 * (-2.78390986018658e-18 - fConst185) + 1.27957634839887e-16) + 4.34250203034679e-15);
	fConst319 = 3.98030871299959e-21 * fConst0;
	fConst320 = fConst37 * (fConst0 * (fConst319 + -1.3696810896962e-17) + 3.04019770269112e-17);
	fConst321 = 1.49388607866623e-19 * fConst0;
	fConst322 = fConst21 * (fConst0 * (2.85365632064909e-16 - fConst321) + 1.90022438253841e-15);
	fConst323 = 2.84307765214256e-20 * fConst0;
	fConst324 = fConst68 * (1.13723106085703e-19 - fConst323);
	fConst325 = fConst21 * (fConst0 * (fConst0 * (fConst323 + -2.99551500710851e-18) + 4.85778329480724e-15) + 3.23425287520332e-14);
	fConst326 = 1.06706148476159e-18 * fConst0;
	fConst327 = fConst0 * (fConst326 + -1.44694505189894e-17) + -8.06546851671652e-17;
	fConst328 = fConst0 * (1.44694505189894e-17 - fConst326) + 8.06546851671652e-17;
	fConst329 = 7.96061742599918e-21 * fConst0;
	fConst330 = fConst37 * (fConst0 * (9.13120726464134e-18 - fConst329) + 6.08039540538225e-17);
	fConst331 = 9.95924052444153e-20 * fConst0;
	fConst332 = fConst21 * (fConst0 * (fConst331 + 5.70731264129818e-16) + -3.80044876507682e-15);
	fConst333 = 5.68615530428513e-20 * fConst0;
	fConst334 = fConst68 * (fConst333 + -7.58154040571353e-20);
	fConst335 = fConst21 * (fConst0 * (fConst0 * (1.997010004739e-18 - fConst333) + 9.71556658961449e-15) + -6.46850575040665e-14);
	fConst336 = 7.11374323174395e-19 * fConst0;
	fConst337 = fConst0 * (-2.89389010379788e-17 - fConst336) + 1.6130937033433e-16;
	fConst338 = fConst0 * (fConst336 + 2.89389010379788e-17) + -1.6130937033433e-16;
	fConst339 = fConst37 * (fConst0 * (fConst329 + 9.13120726464134e-18) + -6.08039540538225e-17);
	fConst340 = fConst21 * (fConst0 * (fConst331 + -5.70731264129818e-16) + -3.80044876507682e-15);
	fConst341 = fConst68 * (-7.58154040571353e-20 - fConst333);
	fConst342 = fConst21 * (fConst0 * (fConst0 * (fConst333 + 1.997010004739e-18) + -9.71556658961449e-15) + -6.46850575040665e-14);
	fConst343 = fConst0 * (2.89389010379788e-17 - fConst336) + 1.6130937033433e-16;
	fConst344 = fConst0 * (fConst336 + -2.89389010379788e-17) + -1.6130937033433e-16;
	fConst345 = fConst37 * (fConst0 * (-1.3696810896962e-17 - fConst319) + -3.04019770269112e-17);
	fConst346 = fConst21 * (fConst0 * (-2.85365632064909e-16 - fConst321) + 1.90022438253841e-15);
	fConst347 = fConst68 * (fConst323 + 1.13723106085703e-19);
	fConst348 = fConst21 * (fConst0 * (fConst0 * (-2.99551500710851e-18 - fConst323) + -4.85778329480724e-15) + 3.23425287520332e-14);
	fConst349 = fConst0 * (fConst326 + 1.44694505189894e-17) + -8.06546851671652e-17;
	fConst350 = fConst0 * (-1.44694505189894e-17 - fConst326) + 8.06546851671652e-17;
	fConst351 = fConst37 * (fConst0 * (fConst63 + 4.56560363232067e-18) + 3.04019770269112e-17);
	fConst352 = fConst21 * (fConst0 * (fConst65 + 2.85365632064909e-16) + 1.90022438253841e-15);
	fConst353 = fConst68 * (-3.79077020285676e-20 - fConst67);
	fConst354 = fConst21 * (fConst0 * (fConst0 * (fConst67 + 9.98505002369502e-19) + 4.85778329480724e-15) + 3.23425287520332e-14);
	fConst355 = fConst0 * (-1.44694505189894e-17 - fConst71) + -8.06546851671652e-17;
	fConst356 = fConst0 * (fConst71 + 1.44694505189894e-17) + 8.06546851671652e-17;
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
	double fSlow0 = 0.004073836948085289 * (std::exp(double(fVslider0)) + -1.0);
	double fSlow1 = 0.007000000000000006 * (1.0 - double(fVslider1));
	double fSlow2 = 0.004073836948085289 * (std::exp(double(fVslider2)) + -1.0);
	double fSlow3 = 0.007000000000000006 * double(fVslider3);
	double fSlow4 = 0.004073836948085289 * (std::exp(double(fVslider4)) + -1.0);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec0[0] = fSlow0 + 0.993 * fRec0[1];
		double fTemp0 = fConst2 * fRec0[0];
		fRec1[0] = fSlow1 + 0.993 * fRec1[1];
		double fTemp1 = fRec0[0] * (fConst10 + fConst9 * fRec0[0] + -7.98191761744856e-16);
		double fTemp2 = fConst12 * fRec0[0];
		double fTemp3 = fConst17 * fRec0[0];
		double fTemp4 = fConst23 * fRec0[0];
		double fTemp5 = fConst28 * fRec0[0];
		double fTemp6 = fConst33 * fRec0[0];
		fRec2[0] = fSlow2 + 0.993 * fRec2[1];
		double fTemp7 = fRec0[0] * (fConst40 + fConst39 * fRec0[0] + 3.19276704697943e-17);
		fRec3[0] = fSlow3 + 0.993 * fRec3[1];
		double fTemp8 = fConst44 * fRec0[0];
		double fTemp9 = fConst49 * fRec0[0];
		double fTemp10 = fRec0[0] * (fConst55 + fConst54 * fRec0[0] + 7.98191761744856e-16);
		double fTemp11 = fRec0[0] * (fConst60 + fConst59 * fRec0[0] + 3.99095880872428e-15);
		fRec4[0] = double(input0[i0]) - (fRec4[1] * (fConst318 + fRec2[0] * (fConst317 + fRec0[0] * (fConst316 + fConst315 * fRec0[0] + 3.99095880872428e-15) + fRec1[0] * (fConst21 * fRec1[0] * (fConst314 + fRec0[0] * (fConst313 + fConst312 * fRec0[0])) + fConst0 * (fConst311 + fRec0[0] * (fConst310 + fConst309 * fRec0[0]))) + 4.26234400771753e-15) + fRec0[0] * (fConst308 + fConst307 * fRec0[0] + 1.99547940436214e-14) + fRec3[0] * (fConst306 + fRec2[0] * (fRec1[0] * (fConst37 * fRec1[0] * (fConst305 + fRec0[0] * (fConst304 + fConst303 * fRec0[0])) + fConst21 * (fConst302 + fRec0[0] * (fConst301 + fConst300 * fRec0[0]))) + fConst0 * (fConst299 + fRec0[0] * (fConst298 + fConst297 * fRec0[0]))) + fRec0[0] * (fConst296 + fConst295 * fRec0[0] + 1.59638352348971e-16) + fRec1[0] * (fConst21 * fRec1[0] * (fConst294 + fRec0[0] * (fConst293 + fConst292 * fRec0[0])) + fConst0 * (fConst291 + fRec0[0] * (fConst290 + fConst289 * fRec0[0]))) + 1.70493760308701e-16) + fRec1[0] * (fRec0[0] * (fConst288 + fConst287 * fRec0[0] + -3.99095880872428e-15) + fConst0 * (fConst286 + fRec1[0] * (fConst285 + fRec0[0] * (fConst284 + fConst283 * fRec0[0]))) + -4.26234400771753e-15) + 2.13117200385877e-14) + fRec4[2] * (fConst282 + fRec2[0] * (fConst281 + fRec0[0] * (fConst280 + fConst279 * fRec0[0] + 7.98191761744856e-15) + fRec1[0] * (fConst21 * fRec1[0] * (fConst278 + fRec0[0] * (fConst277 + fConst276 * fRec0[0])) + fConst0 * (fConst275 + fRec0[0] * (fConst274 + fConst273 * fRec0[0]))) + 8.52468801543507e-15) + fRec0[0] * (fConst272 + fConst271 * fRec0[0] + 3.99095880872428e-14) + fRec3[0] * (fConst270 + fRec2[0] * (fRec1[0] * (fConst37 * fRec1[0] * (fConst269 + fRec0[0] * (fConst268 + fConst267 * fRec0[0])) + fConst21 * (fConst266 + fRec0[0] * (fConst265 + fConst264 * fRec0[0]))) + fConst0 * (fConst263 + fRec0[0] * (fConst262 + fConst261 * fRec0[0]))) + fRec0[0] * (fConst260 + fConst259 * fRec0[0] + 3.19276704697943e-16) + fRec1[0] * (fConst21 * fRec1[0] * (fConst258 + fRec0[0] * (fConst257 + fConst256 * fRec0[0])) + fConst0 * (fConst255 + fRec0[0] * (fConst254 + fConst253 * fRec0[0]))) + 3.40987520617403e-16) + fRec1[0] * (fRec0[0] * (fConst252 + fConst251 * fRec0[0] + -7.98191761744856e-15) + fConst0 * (fConst250 + fRec1[0] * (fConst249 + fRec0[0] * (fConst248 + fConst247 * fRec0[0]))) + -8.52468801543507e-15) + 4.26234400771753e-14) + fRec4[3] * (fConst246 + fRec2[0] * (fConst244 + fRec0[0] * (fConst242 + fConst241 * fRec0[0] + 7.98191761744856e-15) + fRec1[0] * (fConst21 * fRec1[0] * (fConst239 + fRec0[0] * (fConst237 + fConst236 * fRec0[0])) + fConst0 * (fConst234 + fRec0[0] * (fConst232 + fConst231 * fRec0[0]))) + 8.52468801543507e-15) + fRec0[0] * (fConst229 + fConst228 * fRec0[0] + 3.99095880872428e-14) + fRec3[0] * (fConst226 + fRec2[0] * (fRec1[0] * (fConst37 * fRec1[0] * (fConst224 + fRec0[0] * (fConst222 + fConst221 * fRec0[0])) + fConst21 * (fConst219 + fRec0[0] * (fConst217 + fConst216 * fRec0[0]))) + fConst0 * (fConst214 + fRec0[0] * (fConst212 + fConst211 * fRec0[0]))) + fRec0[0] * (fConst209 + fConst208 * fRec0[0] + 3.19276704697943e-16) + fRec1[0] * (fConst21 * fRec1[0] * (fConst206 + fRec0[0] * (fConst204 + fConst203 * fRec0[0])) + fConst0 * (fConst201 + fRec0[0] * (fConst199 + fConst198 * fRec0[0]))) + 3.40987520617403e-16) + fRec1[0] * (fRec0[0] * (fConst196 + fConst195 * fRec0[0] + -7.98191761744856e-15) + fConst0 * (fConst193 + fRec1[0] * (fConst191 + fRec0[0] * (fConst189 + fConst188 * fRec0[0]))) + -8.52468801543507e-15) + 4.26234400771753e-14) + fRec4[4] * (fConst186 + fRec2[0] * (fConst184 + fRec0[0] * (fConst182 + fConst181 * fRec0[0] + 3.99095880872428e-15) + fRec1[0] * (fConst21 * fRec1[0] * (fConst179 + fRec0[0] * (fConst177 + fConst176 * fRec0[0])) + fConst0 * (fConst174 + fRec0[0] * (fConst172 + fConst171 * fRec0[0]))) + 4.26234400771753e-15) + fRec0[0] * (fConst169 + fConst168 * fRec0[0] + 1.99547940436214e-14) + fRec3[0] * (fConst166 + fRec2[0] * (fRec1[0] * (fConst37 * fRec1[0] * (fConst164 + fRec0[0] * (fConst162 + fConst161 * fRec0[0])) + fConst21 * (fConst159 + fRec0[0] * (fConst157 + fConst156 * fRec0[0]))) + fConst0 * (fConst154 + fRec0[0] * (fConst152 + fConst151 * fRec0[0]))) + fRec0[0] * (fConst149 + fConst148 * fRec0[0] + 1.59638352348971e-16) + fRec1[0] * (fConst21 * fRec1[0] * (fConst146 + fRec0[0] * (fConst144 + fConst143 * fRec0[0])) + fConst0 * (fConst141 + fRec0[0] * (fConst139 + fConst138 * fRec0[0]))) + 1.70493760308701e-16) + fRec1[0] * (fRec0[0] * (fConst136 + fConst135 * fRec0[0] + -3.99095880872428e-15) + fConst0 * (fConst133 + fRec1[0] * (fConst131 + fRec0[0] * (fConst129 + fConst128 * fRec0[0]))) + -4.26234400771753e-15) + 2.13117200385877e-14) + fRec4[5] * (fConst126 + fRec2[0] * (fConst125 + fRec0[0] * (fConst124 + fConst123 * fRec0[0] + 7.98191761744856e-16) + fRec1[0] * (fConst21 * fRec1[0] * (fConst122 + fRec0[0] * (fConst121 + fConst120 * fRec0[0])) + fConst0 * (fConst119 + fRec0[0] * (fConst118 + fConst117 * fRec0[0]))) + 8.52468801543507e-16) + fRec0[0] * (fConst116 + fConst115 * fRec0[0] + 3.99095880872428e-15) + fRec3[0] * (fConst114 + fRec2[0] * (fRec1[0] * (fConst37 * fRec1[0] * (fConst113 + fRec0[0] * (fConst112 + fConst111 * fRec0[0])) + fConst21 * (fConst110 + fRec0[0] * (fConst109 + fConst108 * fRec0[0]))) + fConst0 * (fConst107 + fRec0[0] * (fConst106 + fConst105 * fRec0[0]))) + fRec0[0] * (fConst104 + fConst103 * fRec0[0] + 3.19276704697943e-17) + fRec1[0] * (fConst21 * fRec1[0] * (fConst102 + fRec0[0] * (fConst101 + fConst100 * fRec0[0])) + fConst0 * (fConst99 + fRec0[0] * (fConst98 + fConst97 * fRec0[0]))) + 3.40987520617403e-17) + fRec1[0] * (fRec0[0] * (fConst96 + fConst95 * fRec0[0] + -7.98191761744856e-16) + fConst0 * (fConst94 + fRec1[0] * (fConst93 + fRec0[0] * (fConst92 + fConst91 * fRec0[0]))) + -8.52468801543507e-16) + 4.26234400771753e-15)) / (fConst62 + fRec2[0] * (fConst57 + fTemp10 + fRec1[0] * (fConst21 * fRec1[0] * (fConst90 + fRec0[0] * (fConst89 + fTemp9)) + fConst0 * (fConst88 + fRec0[0] * (fConst87 + fTemp8))) + 8.52468801543507e-16) + fTemp11 + fRec3[0] * (fConst42 + fRec2[0] * (fRec1[0] * (fConst37 * fRec1[0] * (fConst86 + fRec0[0] * (fConst85 + fTemp6)) + fConst21 * (fConst84 + fRec0[0] * (fConst83 + fTemp5))) + fConst0 * (fConst82 + fRec0[0] * (fConst81 + fTemp4))) + fTemp7 + fRec1[0] * (fConst21 * fRec1[0] * (fConst80 + fRec0[0] * (fConst79 + fTemp3)) + fConst0 * (fConst78 + fRec0[0] * (fConst77 + fTemp2))) + 3.40987520617403e-17) + fRec1[0] * (fTemp1 + fConst0 * (fConst76 + fRec1[0] * (fConst75 + fRec0[0] * (fConst74 + fTemp0))) + -8.52468801543507e-16) + 4.26234400771753e-15);
		fRec5[0] = fSlow4 + 0.993 * fRec5[1];
		output0[i0] = FAUSTFLOAT(0.05 * (fRec0[0] * fRec5[0] * (fRec4[0] * (fConst21 * (fConst356 + fConst355 * fRec1[0]) + fRec2[0] * (fConst354 + fConst353 * fRec1[0]) + fRec3[0] * (fConst352 + fConst351 * fRec2[0])) + fRec4[1] * (fConst21 * (fConst350 + fConst349 * fRec1[0]) + fRec2[0] * (fConst348 + fConst347 * fRec1[0]) + fRec3[0] * (fConst346 + fConst345 * fRec2[0])) + fRec4[2] * (fConst21 * (fConst344 + fConst343 * fRec1[0]) + fRec2[0] * (fConst342 + fConst341 * fRec1[0]) + fRec3[0] * (fConst340 + fConst339 * fRec2[0])) + fRec4[3] * (fConst21 * (fConst338 + fConst337 * fRec1[0]) + fRec2[0] * (fConst335 + fConst334 * fRec1[0]) + fRec3[0] * (fConst332 + fConst330 * fRec2[0])) + fRec4[4] * (fConst21 * (fConst328 + fConst327 * fRec1[0]) + fRec2[0] * (fConst325 + fConst324 * fRec1[0]) + fRec3[0] * (fConst322 + fConst320 * fRec2[0])) + fRec4[5] * (fConst21 * (fConst73 + fConst72 * fRec1[0]) + fRec2[0] * (fConst70 + fConst69 * fRec1[0]) + fRec3[0] * (fConst66 + fConst64 * fRec2[0]))) / (fConst62 + fTemp11 + fRec2[0] * (fConst57 + fTemp10 + fRec1[0] * (fConst21 * fRec1[0] * (fConst52 + fRec0[0] * (fConst50 + fTemp9 + -4.98869851090535e-21) + -5.32793000964692e-21) + fConst0 * (fConst47 + fRec0[0] * (fConst45 + fTemp8 + -3.98098141170247e-17) + -4.25168814769824e-17)) + 8.52468801543507e-16) + fRec3[0] * (fConst42 + fTemp7 + fRec2[0] * (fRec1[0] * (fConst37 * fRec1[0] * (fConst36 + fRec0[0] * (fConst34 + fTemp6 + -4.68937660025103e-24) + -5.0082542090681e-24) + fConst21 * (fConst31 + fRec0[0] * (fConst29 + fTemp5 + -3.74212252700032e-20) + -3.99658685883635e-20)) + fConst0 * (fConst26 + fRec0[0] * (fConst24 + fTemp4 + 7.50300256040165e-19) + 8.01320673450896e-19)) + fRec1[0] * (fConst21 * fRec1[0] * (fConst20 + fRec0[0] * (fConst18 + fTemp3 + -2.93335472441235e-22) + -3.13282284567239e-22) + fConst0 * (fConst15 + fRec0[0] * (fConst13 + fTemp2 + -2.34269282072115e-18) + -2.50199593253019e-18)) + 3.40987520617403e-17) + fRec1[0] * (fTemp1 + fConst0 * (fConst7 + fRec1[0] * (fConst5 + fRec0[0] * (fConst3 + fTemp0 + -9.9773970218107e-20) + -1.06558600192938e-19) + -2.89308329876105e-16) + -8.52468801543507e-16) + 4.26234400771753e-15)));
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		for (int j0 = 5; j0 > 0; j0 = j0 - 1) {
			fRec4[j0] = fRec4[j0 - 1];
		}
		fRec5[1] = fRec5[0];
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
	case AUDIO_IN: 
		fVslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case BASS: 
		fVslider2_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case MIDDLE: 
		fVslider3_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case TREBLE: 
		fVslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case VOLUME: 
		fVslider4_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
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
   AUDIO_IN, 
   BASS, 
   MIDDLE, 
   TREBLE, 
   VOLUME, 
} PortIndex;
*/

} // end namespace gx_alembic
