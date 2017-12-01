// generated from file '../src/LV2/faust/gx_alembic.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)


namespace gx_alembic {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec0[2];
	double 	fConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec1[2];
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
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec2[2];
	double 	fConst40;
	double 	fConst41;
	double 	fConst42;
	double 	fConst43;
	double 	fConst44;
	double 	fConst45;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fRec3[2];
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
	double 	fConst71;
	double 	fConst72;
	double 	fConst73;
	double 	fConst74;
	double 	fConst75;
	double 	fConst76;
	double 	fConst77;
	double 	fConst78;
	double 	fConst79;
	double 	fConst80;
	double 	fConst81;
	double 	fConst82;
	double 	fConst83;
	double 	fConst84;
	double 	fConst85;
	double 	fConst86;
	double 	fConst87;
	double 	fConst88;
	double 	fConst89;
	double 	fConst90;
	double 	fConst91;
	double 	fConst92;
	double 	fConst93;
	double 	fConst94;
	double 	fConst95;
	double 	fConst96;
	double 	fConst97;
	double 	fConst98;
	double 	fConst99;
	double 	fConst100;
	double 	fConst101;
	double 	fConst102;
	double 	fConst103;
	double 	fConst104;
	double 	fConst105;
	double 	fConst106;
	double 	fConst107;
	double 	fConst108;
	double 	fConst109;
	double 	fConst110;
	double 	fConst111;
	double 	fConst112;
	double 	fConst113;
	double 	fConst114;
	double 	fConst115;
	double 	fConst116;
	double 	fConst117;
	double 	fConst118;
	double 	fConst119;
	double 	fConst120;
	double 	fConst121;
	double 	fConst122;
	double 	fConst123;
	double 	fConst124;
	double 	fConst125;
	double 	fConst126;
	double 	fConst127;
	double 	fConst128;
	double 	fConst129;
	double 	fConst130;
	double 	fConst131;
	double 	fConst132;
	double 	fConst133;
	double 	fConst134;
	double 	fConst135;
	double 	fConst136;
	double 	fConst137;
	double 	fConst138;
	double 	fConst139;
	double 	fConst140;
	double 	fConst141;
	double 	fConst142;
	double 	fConst143;
	double 	fConst144;
	double 	fConst145;
	double 	fConst146;
	double 	fConst147;
	double 	fConst148;
	double 	fConst149;
	double 	fConst150;
	double 	fConst151;
	double 	fConst152;
	double 	fConst153;
	double 	fConst154;
	double 	fConst155;
	double 	fConst156;
	double 	fConst157;
	double 	fConst158;
	double 	fConst159;
	double 	fConst160;
	double 	fConst161;
	double 	fConst162;
	double 	fConst163;
	double 	fConst164;
	double 	fConst165;
	double 	fConst166;
	double 	fConst167;
	double 	fConst168;
	double 	fConst169;
	double 	fConst170;
	double 	fConst171;
	double 	fConst172;
	double 	fConst173;
	double 	fConst174;
	double 	fConst175;
	double 	fConst176;
	double 	fConst177;
	double 	fConst178;
	double 	fConst179;
	double 	fConst180;
	double 	fConst181;
	double 	fConst182;
	double 	fConst183;
	double 	fConst184;
	double 	fConst185;
	double 	fConst186;
	double 	fConst187;
	double 	fConst188;
	double 	fConst189;
	double 	fConst190;
	double 	fConst191;
	double 	fConst192;
	double 	fConst193;
	double 	fConst194;
	double 	fConst195;
	double 	fConst196;
	double 	fConst197;
	double 	fConst198;
	double 	fConst199;
	double 	fConst200;
	double 	fConst201;
	double 	fConst202;
	double 	fConst203;
	double 	fConst204;
	double 	fConst205;
	double 	fConst206;
	double 	fConst207;
	double 	fConst208;
	double 	fConst209;
	double 	fConst210;
	double 	fConst211;
	double 	fConst212;
	double 	fConst213;
	double 	fConst214;
	double 	fConst215;
	double 	fConst216;
	double 	fConst217;
	double 	fConst218;
	double 	fConst219;
	double 	fConst220;
	double 	fConst221;
	double 	fConst222;
	double 	fConst223;
	double 	fConst224;
	double 	fConst225;
	double 	fConst226;
	double 	fConst227;
	double 	fConst228;
	double 	fConst229;
	double 	fConst230;
	double 	fConst231;
	double 	fConst232;
	double 	fConst233;
	double 	fConst234;
	double 	fConst235;
	double 	fConst236;
	double 	fConst237;
	double 	fConst238;
	double 	fConst239;
	double 	fConst240;
	double 	fConst241;
	double 	fConst242;
	double 	fConst243;
	double 	fConst244;
	double 	fConst245;
	double 	fConst246;
	double 	fConst247;
	double 	fConst248;
	double 	fConst249;
	double 	fConst250;
	double 	fConst251;
	double 	fConst252;
	double 	fConst253;
	double 	fConst254;
	double 	fConst255;
	double 	fConst256;
	double 	fConst257;
	double 	fConst258;
	double 	fConst259;
	double 	fConst260;
	double 	fConst261;
	double 	fConst262;
	double 	fConst263;
	double 	fConst264;
	double 	fConst265;
	double 	fConst266;
	double 	fConst267;
	double 	fConst268;
	double 	fConst269;
	double 	fConst270;
	double 	fConst271;
	double 	fConst272;
	double 	fConst273;
	double 	fConst274;
	double 	fConst275;
	double 	fConst276;
	double 	fConst277;
	double 	fConst278;
	double 	fConst279;
	double 	fConst280;
	double 	fConst281;
	double 	fConst282;
	double 	fConst283;
	double 	fConst284;
	double 	fConst285;
	double 	fConst286;
	double 	fConst287;
	double 	fConst288;
	double 	fConst289;
	double 	fConst290;
	double 	fConst291;
	double 	fConst292;
	double 	fConst293;
	double 	fConst294;
	double 	fConst295;
	double 	fConst296;
	double 	fConst297;
	double 	fConst298;
	double 	fConst299;
	double 	fConst300;
	double 	fConst301;
	double 	fConst302;
	double 	fConst303;
	double 	fConst304;
	double 	fConst305;
	double 	fConst306;
	double 	fConst307;
	double 	fConst308;
	double 	fConst309;
	double 	fConst310;
	double 	fConst311;
	double 	fConst312;
	double 	fConst313;
	double 	fConst314;
	double 	fConst315;
	double 	fConst316;
	double 	fConst317;
	double 	fConst318;
	double 	fConst319;
	double 	fConst320;
	double 	fConst321;
	double 	fConst322;
	double 	fConst323;
	double 	fConst324;
	double 	fConst325;
	double 	fConst326;
	double 	fConst327;
	double 	fConst328;
	double 	fConst329;
	double 	fConst330;
	double 	fConst331;
	double 	fConst332;
	double 	fConst333;
	double 	fConst334;
	double 	fRec4[6];
	double 	fConst335;
	double 	fConst336;
	double 	fConst337;
	double 	fConst338;
	double 	fConst339;
	double 	fConst340;
	double 	fConst341;
	double 	fConst342;
	double 	fConst343;
	double 	fConst344;
	double 	fConst345;
	double 	fConst346;
	double 	fConst347;
	double 	fConst348;
	double 	fConst349;
	double 	fConst350;
	double 	fConst351;
	double 	fConst352;
	double 	fConst353;
	double 	fConst354;
	double 	fConst355;
	double 	fConst356;
	double 	fConst357;
	double 	fConst358;
	double 	fConst359;
	double 	fConst360;
	double 	fConst361;
	double 	fConst362;
	double 	fConst363;
	double 	fConst364;
	double 	fConst365;
	double 	fConst366;
	double 	fConst367;
	double 	fConst368;
	double 	fConst369;
	double 	fConst370;
	double 	fConst371;
	double 	fConst372;
	double 	fConst373;
	double 	fConst374;
	double 	fConst375;
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT	*fslider4_;
	double 	fRec5[2];
	double 	fConst376;

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
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<6; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = double(min(1.92e+05, max(1.0, (double)fSamplingFreq)));
	fConst1 = (6.4815418981162e-23 * fConst0);
	fConst2 = (2.99095367015295e-21 + fConst1);
	fConst3 = (9.9773970218107e-20 + (fConst0 * (3.38701967358278e-20 + (fConst0 * fConst2))));
	fConst4 = ((fConst0 * ((fConst0 * (0 - fConst2)) - 3.38701967358278e-20)) - 9.9773970218107e-20);
	fConst5 = (6.9222867471881e-23 * fConst0);
	fConst6 = ((fConst0 * ((fConst0 * (0 - (3.19433851972335e-21 + fConst5))) - 3.61733701138641e-20)) - 1.06558600192938e-19);
	fConst7 = (6.22837159378651e-23 * fConst0);
	fConst8 = ((fConst0 * ((fConst0 * (fConst7 - 5.51032162701814e-19)) - 2.55264149017724e-17)) - 2.89308329876105e-16);
	fConst9 = (5.83180860841434e-23 * fConst0);
	fConst10 = (7.98191761744856e-16 + (fConst0 * (2.70887949322196e-16 + (fConst0 * (2.3901137548476e-17 + (fConst0 * (5.15947717885593e-19 - fConst9)))))));
	fConst11 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst9 - 5.15947717885593e-19)) - 2.3901137548476e-17)) - 2.70887949322196e-16)) - 7.98191761744856e-16);
	fConst12 = (4.85720867386155e-24 * fConst0);
	fConst13 = (8.53036904160507e-23 + fConst12);
	fConst14 = (2.93335472441235e-22 + (fConst0 * fConst13));
	fConst15 = ((fConst0 * (0 - fConst13)) - 2.93335472441235e-22);
	fConst16 = (5.18749886368413e-24 * fConst0);
	fConst17 = ((fConst0 * (0 - (9.11043413643421e-23 + fConst16))) - 3.13282284567239e-22);
	fConst18 = (7.26249840915779e-24 * fConst0);
	fConst19 = ((fConst0 * (fConst18 - 4.13018666157306e-20)) - 7.27156620867848e-19);
	fConst20 = (6.80009214340617e-24 * fConst0);
	fConst21 = (2.34269282072115e-18 + (fConst0 * (6.80858259239558e-19 + (fConst0 * (3.86721597525567e-20 - fConst20)))));
	fConst22 = ((fConst0 * ((fConst0 * (fConst20 - 3.86721597525567e-20)) - 6.80858259239558e-19)) - 2.34269282072115e-18);
	fConst23 = (7.76492543100316e-26 * fConst0);
	fConst24 = (1.36369845222938e-24 + fConst23);
	fConst25 = (4.68937660025103e-24 + (fConst0 * fConst24));
	fConst26 = ((fConst0 * (0 - fConst24)) - 4.68937660025103e-24);
	fConst27 = (8.29294036031137e-26 * fConst0);
	fConst28 = ((fConst0 * (0 - (1.45642994698098e-24 + fConst27))) - 5.0082542090681e-24);
	fConst29 = (1.16101165044359e-25 * fConst0);
	fConst30 = ((fConst0 * (fConst29 - 6.59737638827074e-22)) - 1.16152994210155e-20);
	fConst31 = (1.08708956034044e-25 * fConst0);
	fConst32 = (3.74212252700032e-20 + (fConst0 * (1.08757485215501e-20 + (fConst0 * (6.17731871560931e-22 - fConst31)))));
	fConst33 = ((fConst0 * ((fConst0 * (fConst31 - 6.17731871560931e-22)) - 1.08757485215501e-20)) - 3.74212252700032e-20);
	fConst34 = (4.79935142182139e-25 * fConst0);
	fConst35 = (4.60313050181815e-19 + (fConst0 * (7.89937124628652e-20 + (fConst0 * (3.68677255620389e-21 + fConst34)))));
	fConst36 = (4.49377473953314e-25 * fConst0);
	fConst37 = (3.45203422865533e-21 + fConst36);
	fConst38 = ((fConst0 * ((fConst0 * ((fConst0 * (0 - fConst37)) - 7.39641502461285e-20)) - 4.31004728634658e-19)) - 7.50300256040165e-19);
	fConst39 = (7.50300256040165e-19 + (fConst0 * (4.31004728634658e-19 + (fConst0 * (7.39641502461285e-20 + (fConst0 * fConst37))))));
	fConst40 = (3.00214748513934e-23 * fConst0);
	fConst41 = (2.41249362977723e-17 + (fConst0 * (4.67347173267892e-18 + (fConst0 * (2.30482265359608e-19 + fConst40)))));
	fConst42 = (2.81099951792073e-23 * fConst0);
	fConst43 = (2.15807364568921e-19 + fConst42);
	fConst44 = ((fConst0 * ((fConst0 * ((fConst0 * (0 - fConst43)) - 4.37590986205892e-18)) - 2.25888916645809e-17)) - 3.19276704697943e-17);
	fConst45 = (3.19276704697943e-17 + (fConst0 * (2.25888916645809e-17 + (fConst0 * (4.37590986205892e-18 + (fConst0 * fConst43))))));
	fConst46 = (2.91748340409741e-22 * fConst0);
	fConst47 = (2.60665717245934e-18 + fConst46);
	fConst48 = ((fConst0 * ((fConst0 * ((fConst0 * (0 - fConst47)) - 1.19810519513002e-16)) - 1.35533771234294e-15)) - 3.99095880872428e-15);
	fConst49 = (3.99095880872428e-15 + (fConst0 * (1.35533771234294e-15 + (fConst0 * (1.19810519513002e-16 + (fConst0 * fConst47))))));
	fConst50 = (1.03616486126347e-24 * fConst0);
	fConst51 = (1.0400884417695e-22 + fConst50);
	fConst52 = (4.98869851090535e-21 + (fConst0 * (1.52836235209424e-21 + (fConst0 * fConst51))));
	fConst53 = ((fConst0 * ((fConst0 * (0 - fConst51)) - 1.52836235209424e-21)) - 4.98869851090535e-21);
	fConst54 = (1.10662407182939e-24 * fConst0);
	fConst55 = ((fConst0 * ((fConst0 * (0 - (1.11081445580983e-22 + fConst54))) - 1.63229099203665e-21)) - 5.32793000964692e-21);
	fConst56 = (9.95692057510089e-25 * fConst0);
	fConst57 = ((fConst0 * ((fConst0 * (fConst56 - 8.68780729022958e-21)) - 8.84191013275692e-19)) - 1.30182230144389e-17);
	fConst58 = (9.32295933998211e-25 * fConst0);
	fConst59 = (3.98098141170247e-17 + (fConst0 * (1.21893473917967e-17 + (fConst0 * (8.27894207186978e-19 + (fConst0 * (8.13465102081422e-21 - fConst58)))))));
	fConst60 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst58 - 8.13465102081422e-21)) - 8.27894207186978e-19)) - 1.21893473917967e-17)) - 3.98098141170247e-17);
	fConst61 = (4.98115635891407e-24 * fConst0);
	fConst62 = (5.02958323262947e-16 + (fConst0 * (9.10160440190383e-17 + (fConst0 * (5.01579761573499e-18 + (fConst0 * (4.49743041952051e-20 + fConst61)))))));
	fConst63 = (4.66400408138021e-24 * fConst0);
	fConst64 = (4.21107717183568e-20 + fConst63);
	fConst65 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (0 - fConst64)) - 4.69643971510767e-18)) - 8.52210149990995e-17)) - 4.70934759609501e-16)) - 7.98191761744856e-16);
	fConst66 = (7.98191761744856e-16 + (fConst0 * (4.70934759609501e-16 + (fConst0 * (8.52210149990995e-17 + (fConst0 * (4.69643971510767e-18 + (fConst0 * fConst64))))))));
	fConst67 = (3.11587227557603e-22 * fConst0);
	fConst68 = (4.26234400771753e-15 + (fConst0 * (1.44750067678226e-15 + (fConst0 * (1.27957634839887e-16 + (fConst0 * (2.78390986018658e-18 + fConst67)))))));
	fConst69 = (7.96061742599918e-22 * fConst0);
	fConst70 = ((fConst0 * (4.56560363232067e-18 - fConst69)) - 3.04019770269112e-17);
	fConst71 = (4.97962026222076e-20 * fConst0);
	fConst72 = (fConst71 - 2.85365632064909e-16);
	fConst73 = (5.68615530428513e-21 * fConst0);
	fConst74 = (fConst0 * (fConst73 - 3.79077020285676e-20));
	fConst75 = ((fConst0 * (9.98505002369502e-19 - fConst73)) - 4.85778329480724e-15);
	fConst76 = (3.55687161587197e-19 * fConst0);
	fConst77 = ((fConst0 * (1.44694505189894e-17 - fConst76)) - 8.06546851671652e-17);
	fConst78 = (8.06546851671652e-17 + (fConst0 * (fConst76 - 1.44694505189894e-17)));
	fConst79 = ((fConst0 * (3.38701967358278e-20 + (fConst0 * (fConst1 - 2.99095367015295e-21)))) - 9.9773970218107e-20);
	fConst80 = (9.9773970218107e-20 + (fConst0 * ((fConst0 * (2.99095367015295e-21 - fConst1)) - 3.38701967358278e-20)));
	fConst81 = (1.06558600192938e-19 + (fConst0 * ((fConst0 * (3.19433851972335e-21 - fConst5)) - 3.61733701138641e-20)));
	fConst82 = (2.89308329876105e-16 + (fConst0 * ((fConst0 * (5.51032162701814e-19 + fConst7)) - 2.55264149017724e-17)));
	fConst83 = (5.15947717885593e-19 + fConst9);
	fConst84 = (7.98191761744856e-16 + (fConst0 * ((fConst0 * (2.3901137548476e-17 + (fConst0 * (0 - fConst83)))) - 2.70887949322196e-16)));
	fConst85 = ((fConst0 * (2.70887949322196e-16 + (fConst0 * ((fConst0 * fConst83) - 2.3901137548476e-17)))) - 7.98191761744856e-16);
	fConst86 = (2.93335472441235e-22 + (fConst0 * (fConst12 - 8.53036904160507e-23)));
	fConst87 = ((fConst0 * (8.53036904160507e-23 - fConst12)) - 2.93335472441235e-22);
	fConst88 = ((fConst0 * (9.11043413643421e-23 - fConst16)) - 3.13282284567239e-22);
	fConst89 = ((fConst0 * (4.13018666157306e-20 + fConst18)) - 7.27156620867848e-19);
	fConst90 = (3.86721597525567e-20 + fConst20);
	fConst91 = ((fConst0 * (6.80858259239558e-19 + (fConst0 * (0 - fConst90)))) - 2.34269282072115e-18);
	fConst92 = (2.34269282072115e-18 + (fConst0 * ((fConst0 * fConst90) - 6.80858259239558e-19)));
	fConst93 = ((fConst0 * (1.36369845222938e-24 - fConst23)) - 4.68937660025103e-24);
	fConst94 = (4.68937660025103e-24 + (fConst0 * (fConst23 - 1.36369845222938e-24)));
	fConst95 = (5.0082542090681e-24 + (fConst0 * (fConst27 - 1.45642994698098e-24)));
	fConst96 = (1.16152994210155e-20 + (fConst0 * (0 - (6.59737638827074e-22 + fConst29))));
	fConst97 = (6.17731871560931e-22 + fConst31);
	fConst98 = (3.74212252700032e-20 + (fConst0 * ((fConst0 * fConst97) - 1.08757485215501e-20)));
	fConst99 = ((fConst0 * (1.08757485215501e-20 + (fConst0 * (0 - fConst97)))) - 3.74212252700032e-20);
	fConst100 = (4.60313050181815e-19 + (fConst0 * ((fConst0 * (3.68677255620389e-21 - fConst34)) - 7.89937124628652e-20)));
	fConst101 = (7.50300256040165e-19 + (fConst0 * ((fConst0 * (7.39641502461285e-20 + (fConst0 * (fConst36 - 3.45203422865533e-21)))) - 4.31004728634658e-19)));
	fConst102 = ((fConst0 * (4.31004728634658e-19 + (fConst0 * ((fConst0 * (3.45203422865533e-21 - fConst36)) - 7.39641502461285e-20)))) - 7.50300256040165e-19);
	fConst103 = ((fConst0 * (4.67347173267892e-18 + (fConst0 * (fConst40 - 2.30482265359608e-19)))) - 2.41249362977723e-17);
	fConst104 = ((fConst0 * (2.25888916645809e-17 + (fConst0 * ((fConst0 * (2.15807364568921e-19 - fConst42)) - 4.37590986205892e-18)))) - 3.19276704697943e-17);
	fConst105 = (3.19276704697943e-17 + (fConst0 * ((fConst0 * (4.37590986205892e-18 + (fConst0 * (fConst42 - 2.15807364568921e-19)))) - 2.25888916645809e-17)));
	fConst106 = ((fConst0 * (1.35533771234294e-15 + (fConst0 * ((fConst0 * (2.60665717245934e-18 - fConst46)) - 1.19810519513002e-16)))) - 3.99095880872428e-15);
	fConst107 = (3.99095880872428e-15 + (fConst0 * ((fConst0 * (1.19810519513002e-16 + (fConst0 * (fConst46 - 2.60665717245934e-18)))) - 1.35533771234294e-15)));
	fConst108 = (4.98869851090535e-21 + (fConst0 * ((fConst0 * (1.0400884417695e-22 - fConst50)) - 1.52836235209424e-21)));
	fConst109 = ((fConst0 * (1.52836235209424e-21 + (fConst0 * (fConst50 - 1.0400884417695e-22)))) - 4.98869851090535e-21);
	fConst110 = ((fConst0 * (1.63229099203665e-21 + (fConst0 * (fConst54 - 1.11081445580983e-22)))) - 5.32793000964692e-21);
	fConst111 = ((fConst0 * (8.84191013275692e-19 + (fConst0 * (0 - (8.68780729022958e-21 + fConst56))))) - 1.30182230144389e-17);
	fConst112 = (8.13465102081422e-21 + fConst58);
	fConst113 = ((fConst0 * (1.21893473917967e-17 + (fConst0 * ((fConst0 * fConst112) - 8.27894207186978e-19)))) - 3.98098141170247e-17);
	fConst114 = (3.98098141170247e-17 + (fConst0 * ((fConst0 * (8.27894207186978e-19 + (fConst0 * (0 - fConst112)))) - 1.21893473917967e-17)));
	fConst115 = ((fConst0 * (9.10160440190383e-17 + (fConst0 * ((fConst0 * (4.49743041952051e-20 - fConst61)) - 5.01579761573499e-18)))) - 5.02958323262947e-16);
	fConst116 = ((fConst0 * (4.70934759609501e-16 + (fConst0 * ((fConst0 * (4.69643971510767e-18 + (fConst0 * (fConst63 - 4.21107717183568e-20)))) - 8.52210149990995e-17)))) - 7.98191761744856e-16);
	fConst117 = (7.98191761744856e-16 + (fConst0 * ((fConst0 * (8.52210149990995e-17 + (fConst0 * ((fConst0 * (4.21107717183568e-20 - fConst63)) - 4.69643971510767e-18)))) - 4.70934759609501e-16)));
	fConst118 = (4.26234400771753e-15 + (fConst0 * ((fConst0 * (1.27957634839887e-16 + (fConst0 * (fConst67 - 2.78390986018658e-18)))) - 1.44750067678226e-15)));
	fConst119 = (1.94446256943486e-22 * fConst0);
	fConst120 = ((fConst0 * (3.38701967358278e-20 + (fConst0 * (2.99095367015295e-21 - fConst119)))) - 2.99321910654321e-19);
	fConst121 = (2.99321910654321e-19 + (fConst0 * ((fConst0 * (fConst119 - 2.99095367015295e-21)) - 3.38701967358278e-20)));
	fConst122 = (2.07668602415643e-22 * fConst0);
	fConst123 = (3.19675800578815e-19 + (fConst0 * ((fConst0 * (fConst122 - 3.19433851972335e-21)) - 3.61733701138641e-20)));
	fConst124 = (1.86851147813595e-22 * fConst0);
	fConst125 = (8.67924989628316e-16 + (fConst0 * ((fConst0 * (0 - (5.51032162701814e-19 + fConst124))) - 2.55264149017724e-17)));
	fConst126 = (1.7495425825243e-22 * fConst0);
	fConst127 = (5.15947717885593e-19 + fConst126);
	fConst128 = (3.99095880872428e-15 + (fConst0 * ((fConst0 * (2.3901137548476e-17 + (fConst0 * fConst127))) - 8.12663847966588e-16)));
	fConst129 = ((fConst0 * (8.12663847966588e-16 + (fConst0 * ((fConst0 * (0 - fConst127)) - 2.3901137548476e-17)))) - 3.99095880872428e-15);
	fConst130 = (1.45716260215846e-23 * fConst0);
	fConst131 = (2.93335472441235e-22 + (fConst0 * (8.53036904160507e-23 - fConst130)));
	fConst132 = ((fConst0 * (fConst130 - 8.53036904160507e-23)) - 2.93335472441235e-22);
	fConst133 = (1.55624965910524e-23 * fConst0);
	fConst134 = ((fConst0 * (fConst133 - 9.11043413643421e-23)) - 3.13282284567239e-22);
	fConst135 = (2.17874952274734e-23 * fConst0);
	fConst136 = ((fConst0 * (0 - (4.13018666157306e-20 + fConst135))) - 7.27156620867848e-19);
	fConst137 = (2.04002764302185e-23 * fConst0);
	fConst138 = (3.86721597525567e-20 + fConst137);
	fConst139 = ((fConst0 * (6.80858259239558e-19 + (fConst0 * fConst138))) - 7.02807846216346e-18);
	fConst140 = (7.02807846216346e-18 + (fConst0 * ((fConst0 * (0 - fConst138)) - 6.80858259239558e-19)));
	fConst141 = (3.88246271550158e-25 * fConst0);
	fConst142 = (4.68937660025103e-24 + (fConst0 * (fConst141 - 4.09109535668814e-24)));
	fConst143 = ((fConst0 * (4.09109535668814e-24 - fConst141)) - 4.68937660025103e-24);
	fConst144 = (4.14647018015568e-25 * fConst0);
	fConst145 = ((fConst0 * (4.36928984094294e-24 - fConst144)) - 5.0082542090681e-24);
	fConst146 = (5.80505825221796e-25 * fConst0);
	fConst147 = ((fConst0 * (1.97921291648122e-21 + fConst146)) - 1.16152994210155e-20);
	fConst148 = (5.43544780170221e-25 * fConst0);
	fConst149 = (1.85319561468279e-21 + fConst148);
	fConst150 = (3.74212252700032e-20 + (fConst0 * (1.08757485215501e-20 + (fConst0 * (0 - fConst149)))));
	fConst151 = ((fConst0 * ((fConst0 * fConst149) - 1.08757485215501e-20)) - 3.74212252700032e-20);
	fConst152 = (2.39967571091069e-24 * fConst0);
	fConst153 = (4.60313050181815e-19 + (fConst0 * (7.89937124628652e-20 + (fConst0 * (fConst152 - 1.10603176686117e-20)))));
	fConst154 = (2.24688736976657e-24 * fConst0);
	fConst155 = (2.2509007681205e-18 + (fConst0 * ((fConst0 * ((fConst0 * (1.0356102685966e-20 - fConst154)) - 7.39641502461285e-20)) - 4.31004728634658e-19)));
	fConst156 = ((fConst0 * (4.31004728634658e-19 + (fConst0 * (7.39641502461285e-20 + (fConst0 * (fConst154 - 1.0356102685966e-20)))))) - 2.2509007681205e-18);
	fConst157 = (9.00644245541801e-23 * fConst0);
	fConst158 = ((fConst0 * (4.67347173267892e-18 + (fConst0 * (2.30482265359608e-19 - fConst157)))) - 7.2374808893317e-17);
	fConst159 = (8.43299855376218e-23 * fConst0);
	fConst160 = ((fConst0 * (6.77666749937426e-17 + (fConst0 * ((fConst0 * (fConst159 - 2.15807364568921e-19)) - 4.37590986205892e-18)))) - 1.59638352348971e-16);
	fConst161 = (1.59638352348971e-16 + (fConst0 * ((fConst0 * (4.37590986205892e-18 + (fConst0 * (2.15807364568921e-19 - fConst159)))) - 6.77666749937426e-17)));
	fConst162 = (8.75245021229223e-22 * fConst0);
	fConst163 = ((fConst0 * (4.06601313702883e-15 + (fConst0 * ((fConst0 * (fConst162 - 2.60665717245934e-18)) - 1.19810519513002e-16)))) - 1.99547940436214e-14);
	fConst164 = (1.99547940436214e-14 + (fConst0 * ((fConst0 * (1.19810519513002e-16 + (fConst0 * (2.60665717245934e-18 - fConst162)))) - 4.06601313702883e-15)));
	fConst165 = (5.18082430631737e-24 * fConst0);
	fConst166 = (4.98869851090535e-21 + (fConst0 * (1.52836235209424e-21 + (fConst0 * (fConst165 - 3.12026532530851e-22)))));
	fConst167 = ((fConst0 * ((fConst0 * (3.12026532530851e-22 - fConst165)) - 1.52836235209424e-21)) - 4.98869851090535e-21);
	fConst168 = (5.53312035914695e-24 * fConst0);
	fConst169 = ((fConst0 * ((fConst0 * (3.33244336742949e-22 - fConst168)) - 1.63229099203665e-21)) - 5.32793000964692e-21);
	fConst170 = (4.97846028755044e-24 * fConst0);
	fConst171 = ((fConst0 * ((fConst0 * (2.60634218706887e-20 + fConst170)) - 8.84191013275692e-19)) - 1.30182230144389e-17);
	fConst172 = (4.66147966999105e-24 * fConst0);
	fConst173 = (2.44039530624426e-20 + fConst172);
	fConst174 = ((fConst0 * (1.21893473917967e-17 + (fConst0 * (8.27894207186978e-19 + (fConst0 * (0 - fConst173)))))) - 1.19429442351074e-16);
	fConst175 = (1.19429442351074e-16 + (fConst0 * ((fConst0 * ((fConst0 * fConst173) - 8.27894207186978e-19)) - 1.21893473917967e-17)));
	fConst176 = (2.49057817945703e-23 * fConst0);
	fConst177 = ((fConst0 * (9.10160440190383e-17 + (fConst0 * (5.01579761573499e-18 + (fConst0 * (fConst176 - 1.34922912585615e-19)))))) - 1.50887496978884e-15);
	fConst178 = (2.33200204069011e-23 * fConst0);
	fConst179 = ((fConst0 * (1.4128042788285e-15 + (fConst0 * ((fConst0 * ((fConst0 * (1.26332315155071e-19 - fConst178)) - 4.69643971510767e-18)) - 8.52210149990995e-17)))) - 3.99095880872428e-15);
	fConst180 = (3.99095880872428e-15 + (fConst0 * ((fConst0 * (8.52210149990995e-17 + (fConst0 * (4.69643971510767e-18 + (fConst0 * (fConst178 - 1.26332315155071e-19)))))) - 1.4128042788285e-15)));
	fConst181 = (9.3476168267281e-22 * fConst0);
	fConst182 = (2.13117200385877e-14 + (fConst0 * ((fConst0 * (1.27957634839887e-16 + (fConst0 * (2.78390986018658e-18 - fConst181)))) - 4.34250203034679e-15)));
	fConst183 = (1.29630837962324e-22 * fConst0);
	fConst184 = (5.98190734030589e-21 + fConst183);
	fConst185 = ((fConst0 * ((fConst0 * fConst184) - 6.77403934716556e-20)) - 1.99547940436214e-19);
	fConst186 = (1.99547940436214e-19 + (fConst0 * (6.77403934716556e-20 + (fConst0 * (0 - fConst184)))));
	fConst187 = (1.38445734943762e-22 * fConst0);
	fConst188 = (2.13117200385877e-19 + (fConst0 * (7.23467402277282e-20 + (fConst0 * (0 - (6.38867703944669e-21 + fConst187))))));
	fConst189 = (1.2456743187573e-22 * fConst0);
	fConst190 = (5.78616659752211e-16 + (fConst0 * (5.10528298035447e-17 + (fConst0 * (fConst189 - 1.10206432540363e-18)))));
	fConst191 = (1.16636172168287e-22 * fConst0);
	fConst192 = (7.98191761744856e-15 + (fConst0 * ((fConst0 * ((fConst0 * (1.03189543577119e-18 - fConst191)) - 4.7802275096952e-17)) - 5.41775898644392e-16)));
	fConst193 = ((fConst0 * (5.41775898644392e-16 + (fConst0 * (4.7802275096952e-17 + (fConst0 * (fConst191 - 1.03189543577119e-18)))))) - 7.98191761744856e-15);
	fConst194 = (9.7144173477231e-24 * fConst0);
	fConst195 = (1.70607380832101e-22 + fConst194);
	fConst196 = ((fConst0 * fConst195) - 5.86670944882469e-22);
	fConst197 = (5.86670944882469e-22 + (fConst0 * (0 - fConst195)));
	fConst198 = (1.03749977273683e-23 * fConst0);
	fConst199 = (6.26564569134477e-22 + (fConst0 * (0 - (1.82208682728684e-22 + fConst198))));
	fConst200 = (1.45249968183156e-23 * fConst0);
	fConst201 = (1.4543132417357e-18 + (fConst0 * (fConst200 - 8.26037332314611e-20)));
	fConst202 = (1.36001842868123e-23 * fConst0);
	fConst203 = ((fConst0 * ((fConst0 * (7.73443195051134e-20 - fConst202)) - 1.36171651847912e-18)) - 4.68538564144231e-18);
	fConst204 = (4.68538564144231e-18 + (fConst0 * (1.36171651847912e-18 + (fConst0 * (fConst202 - 7.73443195051134e-20)))));
	fConst205 = (7.76492543100316e-25 * fConst0);
	fConst206 = (9.37875320050206e-24 + (fConst0 * (2.72739690445876e-24 - fConst205)));
	fConst207 = ((fConst0 * (fConst205 - 2.72739690445876e-24)) - 9.37875320050206e-24);
	fConst208 = (8.29294036031137e-25 * fConst0);
	fConst209 = ((fConst0 * (fConst208 - 2.91285989396196e-24)) - 1.00165084181362e-23);
	fConst210 = (1.16101165044359e-24 * fConst0);
	fConst211 = ((fConst0 * (0 - (1.31947527765415e-21 + fConst210))) - 2.3230598842031e-20);
	fConst212 = (1.08708956034044e-24 * fConst0);
	fConst213 = (1.23546374312186e-21 + fConst212);
	fConst214 = ((fConst0 * (2.17514970431002e-20 + (fConst0 * fConst213))) - 7.48424505400065e-20);
	fConst215 = (7.48424505400065e-20 + (fConst0 * ((fConst0 * (0 - fConst213)) - 2.17514970431002e-20)));
	fConst216 = (4.79935142182139e-24 * fConst0);
	fConst217 = ((fConst0 * (1.5798742492573e-19 + (fConst0 * (7.37354511240778e-21 - fConst216)))) - 9.2062610036363e-19);
	fConst218 = (4.49377473953314e-24 * fConst0);
	fConst219 = (1.50060051208033e-18 + (fConst0 * (8.62009457269317e-19 + (fConst0 * ((fConst0 * (fConst218 - 6.90406845731066e-21)) - 1.47928300492257e-19)))));
	fConst220 = ((fConst0 * ((fConst0 * (1.47928300492257e-19 + (fConst0 * (6.90406845731066e-21 - fConst218)))) - 8.62009457269317e-19)) - 1.50060051208033e-18);
	fConst221 = (6.00429497027867e-23 * fConst0);
	fConst222 = ((fConst0 * ((fConst0 * (4.60964530719215e-19 + fConst221)) - 9.34694346535784e-18)) - 4.82498725955447e-17);
	fConst223 = (5.62199903584146e-23 * fConst0);
	fConst224 = (4.31614729137842e-19 + fConst223);
	fConst225 = ((fConst0 * (4.51777833291617e-17 + (fConst0 * (8.75181972411783e-18 + (fConst0 * (0 - fConst224)))))) - 3.19276704697943e-16);
	fConst226 = (3.19276704697943e-16 + (fConst0 * ((fConst0 * ((fConst0 * fConst224) - 8.75181972411783e-18)) - 4.51777833291617e-17)));
	fConst227 = (5.83496680819482e-22 * fConst0);
	fConst228 = (5.21331434491869e-18 + fConst227);
	fConst229 = ((fConst0 * (2.71067542468589e-15 + (fConst0 * (2.39621039026005e-16 + (fConst0 * (0 - fConst228)))))) - 3.99095880872428e-14);
	fConst230 = (3.99095880872428e-14 + (fConst0 * ((fConst0 * ((fConst0 * fConst228) - 2.39621039026005e-16)) - 2.71067542468589e-15)));
	fConst231 = (1.03616486126347e-23 * fConst0);
	fConst232 = ((fConst0 * (3.05672470418848e-21 + (fConst0 * (2.08017688353901e-22 - fConst231)))) - 9.97739702181071e-21);
	fConst233 = (9.97739702181071e-21 + (fConst0 * ((fConst0 * (fConst231 - 2.08017688353901e-22)) - 3.05672470418848e-21)));
	fConst234 = (1.10662407182939e-23 * fConst0);
	fConst235 = (1.06558600192938e-20 + (fConst0 * ((fConst0 * (fConst234 - 2.22162891161966e-22)) - 3.26458198407329e-21)));
	fConst236 = (9.95692057510089e-24 * fConst0);
	fConst237 = (2.60364460288779e-17 + (fConst0 * ((fConst0 * (0 - (1.73756145804592e-20 + fConst236))) - 1.76838202655138e-18)));
	fConst238 = (9.32295933998211e-24 * fConst0);
	fConst239 = (1.62693020416284e-20 + fConst238);
	fConst240 = ((fConst0 * ((fConst0 * (1.65578841437396e-18 + (fConst0 * fConst239))) - 2.43786947835935e-17)) - 7.96196282340494e-17);
	fConst241 = (7.96196282340494e-17 + (fConst0 * (2.43786947835935e-17 + (fConst0 * ((fConst0 * (0 - fConst239)) - 1.65578841437396e-18)))));
	fConst242 = (4.98115635891407e-23 * fConst0);
	fConst243 = ((fConst0 * ((fConst0 * (1.003159523147e-17 + (fConst0 * (8.99486083904102e-20 - fConst242)))) - 1.82032088038077e-16)) - 1.00591664652589e-15);
	fConst244 = (4.66400408138021e-23 * fConst0);
	fConst245 = ((fConst0 * (9.41869519219001e-16 + (fConst0 * (1.70442029998199e-16 + (fConst0 * ((fConst0 * (fConst244 - 8.42215434367137e-20)) - 9.39287943021533e-18)))))) - 7.98191761744856e-15);
	fConst246 = (7.98191761744856e-15 + (fConst0 * ((fConst0 * ((fConst0 * (9.39287943021533e-18 + (fConst0 * (8.42215434367137e-20 - fConst244)))) - 1.70442029998199e-16)) - 9.41869519219001e-16)));
	fConst247 = (6.23174455115207e-22 * fConst0);
	fConst248 = (4.26234400771753e-14 + (fConst0 * ((fConst0 * ((fConst0 * (5.56781972037316e-18 + fConst247)) - 2.55915269679773e-16)) - 2.89500135356453e-15)));
	fConst249 = (1.99547940436214e-19 + (fConst0 * ((fConst0 * (fConst183 - 5.98190734030589e-21)) - 6.77403934716556e-20)));
	fConst250 = ((fConst0 * (6.77403934716556e-20 + (fConst0 * (5.98190734030589e-21 - fConst183)))) - 1.99547940436214e-19);
	fConst251 = ((fConst0 * (7.23467402277282e-20 + (fConst0 * (6.38867703944669e-21 - fConst187)))) - 2.13117200385877e-19);
	fConst252 = ((fConst0 * (5.10528298035447e-17 + (fConst0 * (1.10206432540363e-18 + fConst189)))) - 5.78616659752211e-16);
	fConst253 = (1.03189543577119e-18 + fConst191);
	fConst254 = (7.98191761744856e-15 + (fConst0 * (5.41775898644392e-16 + (fConst0 * ((fConst0 * (0 - fConst253)) - 4.7802275096952e-17)))));
	fConst255 = ((fConst0 * ((fConst0 * (4.7802275096952e-17 + (fConst0 * fConst253))) - 5.41775898644392e-16)) - 7.98191761744856e-15);
	fConst256 = ((fConst0 * (fConst194 - 1.70607380832101e-22)) - 5.86670944882469e-22);
	fConst257 = (5.86670944882469e-22 + (fConst0 * (1.70607380832101e-22 - fConst194)));
	fConst258 = (6.26564569134477e-22 + (fConst0 * (1.82208682728684e-22 - fConst198)));
	fConst259 = (1.4543132417357e-18 + (fConst0 * (8.26037332314611e-20 + fConst200)));
	fConst260 = (7.73443195051134e-20 + fConst202);
	fConst261 = (4.68538564144231e-18 + (fConst0 * ((fConst0 * (0 - fConst260)) - 1.36171651847912e-18)));
	fConst262 = ((fConst0 * (1.36171651847912e-18 + (fConst0 * fConst260))) - 4.68538564144231e-18);
	fConst263 = (2.72739690445876e-24 + fConst205);
	fConst264 = ((fConst0 * fConst263) - 9.37875320050206e-24);
	fConst265 = (9.37875320050206e-24 + (fConst0 * (0 - fConst263)));
	fConst266 = (1.00165084181362e-23 + (fConst0 * (0 - (2.91285989396196e-24 + fConst208))));
	fConst267 = (2.3230598842031e-20 + (fConst0 * (fConst210 - 1.31947527765415e-21)));
	fConst268 = ((fConst0 * ((fConst0 * (1.23546374312186e-21 - fConst212)) - 2.17514970431002e-20)) - 7.48424505400065e-20);
	fConst269 = (7.48424505400065e-20 + (fConst0 * (2.17514970431002e-20 + (fConst0 * (fConst212 - 1.23546374312186e-21)))));
	fConst270 = ((fConst0 * ((fConst0 * (7.37354511240778e-21 + fConst216)) - 1.5798742492573e-19)) - 9.2062610036363e-19);
	fConst271 = (6.90406845731066e-21 + fConst218);
	fConst272 = ((fConst0 * (8.62009457269317e-19 + (fConst0 * (1.47928300492257e-19 + (fConst0 * (0 - fConst271)))))) - 1.50060051208033e-18);
	fConst273 = (1.50060051208033e-18 + (fConst0 * ((fConst0 * ((fConst0 * fConst271) - 1.47928300492257e-19)) - 8.62009457269317e-19)));
	fConst274 = (4.82498725955447e-17 + (fConst0 * ((fConst0 * (fConst221 - 4.60964530719215e-19)) - 9.34694346535784e-18)));
	fConst275 = ((fConst0 * ((fConst0 * (8.75181972411783e-18 + (fConst0 * (4.31614729137842e-19 - fConst223)))) - 4.51777833291617e-17)) - 3.19276704697943e-16);
	fConst276 = (3.19276704697943e-16 + (fConst0 * (4.51777833291617e-17 + (fConst0 * ((fConst0 * (fConst223 - 4.31614729137842e-19)) - 8.75181972411783e-18)))));
	fConst277 = ((fConst0 * ((fConst0 * (2.39621039026005e-16 + (fConst0 * (5.21331434491869e-18 - fConst227)))) - 2.71067542468589e-15)) - 3.99095880872428e-14);
	fConst278 = (3.99095880872428e-14 + (fConst0 * (2.71067542468589e-15 + (fConst0 * ((fConst0 * (fConst227 - 5.21331434491869e-18)) - 2.39621039026005e-16)))));
	fConst279 = (2.08017688353901e-22 + fConst231);
	fConst280 = ((fConst0 * ((fConst0 * fConst279) - 3.05672470418848e-21)) - 9.97739702181071e-21);
	fConst281 = (9.97739702181071e-21 + (fConst0 * (3.05672470418848e-21 + (fConst0 * (0 - fConst279)))));
	fConst282 = (1.06558600192938e-20 + (fConst0 * (3.26458198407329e-21 + (fConst0 * (0 - (2.22162891161966e-22 + fConst234))))));
	fConst283 = (2.60364460288779e-17 + (fConst0 * (1.76838202655138e-18 + (fConst0 * (fConst236 - 1.73756145804592e-20)))));
	fConst284 = (7.96196282340494e-17 + (fConst0 * ((fConst0 * ((fConst0 * (1.62693020416284e-20 - fConst238)) - 1.65578841437396e-18)) - 2.43786947835935e-17)));
	fConst285 = ((fConst0 * (2.43786947835935e-17 + (fConst0 * (1.65578841437396e-18 + (fConst0 * (fConst238 - 1.62693020416284e-20)))))) - 7.96196282340494e-17);
	fConst286 = (1.00591664652589e-15 + (fConst0 * ((fConst0 * ((fConst0 * (8.99486083904102e-20 + fConst242)) - 1.003159523147e-17)) - 1.82032088038077e-16)));
	fConst287 = (8.42215434367137e-20 + fConst244);
	fConst288 = ((fConst0 * ((fConst0 * (1.70442029998199e-16 + (fConst0 * (9.39287943021533e-18 + (fConst0 * (0 - fConst287)))))) - 9.41869519219001e-16)) - 7.98191761744856e-15);
	fConst289 = (7.98191761744856e-15 + (fConst0 * (9.41869519219001e-16 + (fConst0 * ((fConst0 * ((fConst0 * fConst287) - 9.39287943021533e-18)) - 1.70442029998199e-16)))));
	fConst290 = (4.26234400771753e-14 + (fConst0 * (2.89500135356453e-15 + (fConst0 * ((fConst0 * (fConst247 - 5.56781972037316e-18)) - 2.55915269679773e-16)))));
	fConst291 = (2.99095367015295e-21 + fConst119);
	fConst292 = (2.99321910654321e-19 + (fConst0 * (3.38701967358278e-20 + (fConst0 * (0 - fConst291)))));
	fConst293 = ((fConst0 * ((fConst0 * fConst291) - 3.38701967358278e-20)) - 2.99321910654321e-19);
	fConst294 = ((fConst0 * ((fConst0 * (3.19433851972335e-21 + fConst122)) - 3.61733701138641e-20)) - 3.19675800578815e-19);
	fConst295 = ((fConst0 * ((fConst0 * (5.51032162701814e-19 - fConst124)) - 2.55264149017724e-17)) - 8.67924989628316e-16);
	fConst296 = (3.99095880872428e-15 + (fConst0 * (8.12663847966588e-16 + (fConst0 * (2.3901137548476e-17 + (fConst0 * (fConst126 - 5.15947717885593e-19)))))));
	fConst297 = ((fConst0 * ((fConst0 * ((fConst0 * (5.15947717885593e-19 - fConst126)) - 2.3901137548476e-17)) - 8.12663847966588e-16)) - 3.99095880872428e-15);
	fConst298 = (8.53036904160507e-23 + fConst130);
	fConst299 = (2.93335472441235e-22 + (fConst0 * (0 - fConst298)));
	fConst300 = ((fConst0 * fConst298) - 2.93335472441235e-22);
	fConst301 = ((fConst0 * (9.11043413643421e-23 + fConst133)) - 3.13282284567239e-22);
	fConst302 = ((fConst0 * (4.13018666157306e-20 - fConst135)) - 7.27156620867848e-19);
	fConst303 = (7.02807846216346e-18 + (fConst0 * (6.80858259239558e-19 + (fConst0 * (fConst137 - 3.86721597525567e-20)))));
	fConst304 = ((fConst0 * ((fConst0 * (3.86721597525567e-20 - fConst137)) - 6.80858259239558e-19)) - 7.02807846216346e-18);
	fConst305 = (4.09109535668814e-24 + fConst141);
	fConst306 = ((fConst0 * (0 - fConst305)) - 4.68937660025103e-24);
	fConst307 = (4.68937660025103e-24 + (fConst0 * fConst305));
	fConst308 = (5.0082542090681e-24 + (fConst0 * (4.36928984094294e-24 + fConst144)));
	fConst309 = (1.16152994210155e-20 + (fConst0 * (1.97921291648122e-21 - fConst146)));
	fConst310 = (3.74212252700032e-20 + (fConst0 * ((fConst0 * (fConst148 - 1.85319561468279e-21)) - 1.08757485215501e-20)));
	fConst311 = ((fConst0 * (1.08757485215501e-20 + (fConst0 * (1.85319561468279e-21 - fConst148)))) - 3.74212252700032e-20);
	fConst312 = (4.60313050181815e-19 + (fConst0 * ((fConst0 * (0 - (1.10603176686117e-20 + fConst152))) - 7.89937124628652e-20)));
	fConst313 = (1.0356102685966e-20 + fConst154);
	fConst314 = ((fConst0 * ((fConst0 * (7.39641502461285e-20 + (fConst0 * fConst313))) - 4.31004728634658e-19)) - 2.2509007681205e-18);
	fConst315 = (2.2509007681205e-18 + (fConst0 * (4.31004728634658e-19 + (fConst0 * ((fConst0 * (0 - fConst313)) - 7.39641502461285e-20)))));
	fConst316 = (7.2374808893317e-17 + (fConst0 * (4.67347173267892e-18 + (fConst0 * (0 - (2.30482265359608e-19 + fConst157))))));
	fConst317 = (2.15807364568921e-19 + fConst159);
	fConst318 = ((fConst0 * ((fConst0 * ((fConst0 * fConst317) - 4.37590986205892e-18)) - 6.77666749937426e-17)) - 1.59638352348971e-16);
	fConst319 = (1.59638352348971e-16 + (fConst0 * (6.77666749937426e-17 + (fConst0 * (4.37590986205892e-18 + (fConst0 * (0 - fConst317)))))));
	fConst320 = (2.60665717245934e-18 + fConst162);
	fConst321 = ((fConst0 * ((fConst0 * ((fConst0 * fConst320) - 1.19810519513002e-16)) - 4.06601313702883e-15)) - 1.99547940436214e-14);
	fConst322 = (1.99547940436214e-14 + (fConst0 * (4.06601313702883e-15 + (fConst0 * (1.19810519513002e-16 + (fConst0 * (0 - fConst320)))))));
	fConst323 = (3.12026532530851e-22 + fConst165);
	fConst324 = (4.98869851090535e-21 + (fConst0 * ((fConst0 * (0 - fConst323)) - 1.52836235209424e-21)));
	fConst325 = ((fConst0 * (1.52836235209424e-21 + (fConst0 * fConst323))) - 4.98869851090535e-21);
	fConst326 = ((fConst0 * (1.63229099203665e-21 + (fConst0 * (3.33244336742949e-22 + fConst168)))) - 5.32793000964692e-21);
	fConst327 = ((fConst0 * (8.84191013275692e-19 + (fConst0 * (2.60634218706887e-20 - fConst170)))) - 1.30182230144389e-17);
	fConst328 = (1.19429442351074e-16 + (fConst0 * (1.21893473917967e-17 + (fConst0 * ((fConst0 * (fConst172 - 2.44039530624426e-20)) - 8.27894207186978e-19)))));
	fConst329 = ((fConst0 * ((fConst0 * (8.27894207186978e-19 + (fConst0 * (2.44039530624426e-20 - fConst172)))) - 1.21893473917967e-17)) - 1.19429442351074e-16);
	fConst330 = (1.50887496978884e-15 + (fConst0 * (9.10160440190383e-17 + (fConst0 * ((fConst0 * (0 - (1.34922912585615e-19 + fConst176))) - 5.01579761573499e-18)))));
	fConst331 = (1.26332315155071e-19 + fConst178);
	fConst332 = ((fConst0 * ((fConst0 * ((fConst0 * (4.69643971510767e-18 + (fConst0 * fConst331))) - 8.52210149990995e-17)) - 1.4128042788285e-15)) - 3.99095880872428e-15);
	fConst333 = (3.99095880872428e-15 + (fConst0 * (1.4128042788285e-15 + (fConst0 * (8.52210149990995e-17 + (fConst0 * ((fConst0 * (0 - fConst331)) - 4.69643971510767e-18)))))));
	fConst334 = (2.13117200385877e-14 + (fConst0 * (4.34250203034679e-15 + (fConst0 * (1.27957634839887e-16 + (fConst0 * (0 - (2.78390986018658e-18 + fConst181))))))));
	fConst335 = (3.98030871299959e-21 * fConst0);
	fConst336 = (3.04019770269112e-17 + (fConst0 * (fConst335 - 1.3696810896962e-17)));
	fConst337 = (1.49388607866623e-19 * fConst0);
	fConst338 = (2.85365632064909e-16 - fConst337);
	fConst339 = (2.84307765214256e-20 * fConst0);
	fConst340 = (fConst0 * (1.13723106085703e-19 - fConst339));
	fConst341 = (4.85778329480724e-15 + (fConst0 * (fConst339 - 2.99551500710851e-18)));
	fConst342 = (1.06706148476159e-18 * fConst0);
	fConst343 = ((fConst0 * (fConst342 - 1.44694505189894e-17)) - 8.06546851671652e-17);
	fConst344 = (8.06546851671652e-17 + (fConst0 * (1.44694505189894e-17 - fConst342)));
	fConst345 = (7.96061742599918e-21 * fConst0);
	fConst346 = (6.08039540538225e-17 + (fConst0 * (9.13120726464134e-18 - fConst345)));
	fConst347 = (9.95924052444153e-20 * fConst0);
	fConst348 = (5.70731264129818e-16 + fConst347);
	fConst349 = (5.68615530428513e-20 * fConst0);
	fConst350 = (fConst0 * (fConst349 - 7.58154040571353e-20));
	fConst351 = (9.71556658961449e-15 + (fConst0 * (1.997010004739e-18 - fConst349)));
	fConst352 = (7.11374323174395e-19 * fConst0);
	fConst353 = (2.89389010379788e-17 + fConst352);
	fConst354 = (1.6130937033433e-16 + (fConst0 * (0 - fConst353)));
	fConst355 = ((fConst0 * fConst353) - 1.6130937033433e-16);
	fConst356 = ((fConst0 * (9.13120726464134e-18 + fConst345)) - 6.08039540538225e-17);
	fConst357 = (fConst347 - 5.70731264129818e-16);
	fConst358 = (fConst0 * (0 - (7.58154040571353e-20 + fConst349)));
	fConst359 = ((fConst0 * (1.997010004739e-18 + fConst349)) - 9.71556658961449e-15);
	fConst360 = (1.6130937033433e-16 + (fConst0 * (2.89389010379788e-17 - fConst352)));
	fConst361 = ((fConst0 * (fConst352 - 2.89389010379788e-17)) - 1.6130937033433e-16);
	fConst362 = ((fConst0 * (0 - (1.3696810896962e-17 + fConst335))) - 3.04019770269112e-17);
	fConst363 = (0 - (2.85365632064909e-16 + fConst337));
	fConst364 = (fConst0 * (1.13723106085703e-19 + fConst339));
	fConst365 = ((fConst0 * (0 - (2.99551500710851e-18 + fConst339))) - 4.85778329480724e-15);
	fConst366 = (1.44694505189894e-17 + fConst342);
	fConst367 = ((fConst0 * fConst366) - 8.06546851671652e-17);
	fConst368 = (8.06546851671652e-17 + (fConst0 * (0 - fConst366)));
	fConst369 = (3.04019770269112e-17 + (fConst0 * (4.56560363232067e-18 + fConst69)));
	fConst370 = (2.85365632064909e-16 + fConst71);
	fConst371 = (fConst0 * (0 - (3.79077020285676e-20 + fConst73)));
	fConst372 = (4.85778329480724e-15 + (fConst0 * (9.98505002369502e-19 + fConst73)));
	fConst373 = (1.44694505189894e-17 + fConst76);
	fConst374 = ((fConst0 * (0 - fConst373)) - 8.06546851671652e-17);
	fConst375 = (8.06546851671652e-17 + (fConst0 * fConst373));
	fConst376 = (0.1 * faustpower<2>(fConst0));
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
	double 	fSlow0 = (0.004073836948085289 * (exp(double(fslider0)) - 1));
	double 	fSlow1 = (0.007000000000000006 * (1 - double(fslider1)));
	double 	fSlow2 = (0.004073836948085289 * (exp(double(fslider2)) - 1));
	double 	fSlow3 = (0.007000000000000006 * double(fslider3));
	double 	fSlow4 = (0.004073836948085289 * (exp(double(fslider4)) - 1));
	for (int i=0; i<count; i++) {
		fRec0[0] = (fSlow0 + (0.993 * fRec0[1]));
		fRec1[0] = (fSlow1 + (0.993 * fRec1[1]));
		fRec2[0] = (fSlow2 + (0.993 * fRec2[1]));
		fRec3[0] = (fSlow3 + (0.993 * fRec3[1]));
		double fTemp0 = (fConst68 + ((((fRec2[0] * (8.52468801543507e-16 + ((fRec0[0] * (fConst66 + (fConst65 * fRec0[0]))) + (fConst0 * (fConst62 + (fRec1[0] * (((fRec0[0] * (fConst60 + (fConst59 * fRec0[0]))) + (fConst0 * (fConst57 + (fRec1[0] * (fConst55 + (fRec0[0] * (fConst53 + (fConst52 * fRec0[0])))))))) - 4.25168814769824e-17))))))) + (fRec0[0] * (fConst49 + (fConst48 * fRec0[0])))) + (fRec3[0] * (3.40987520617403e-17 + ((fRec0[0] * (fConst45 + (fConst44 * fRec0[0]))) + (fConst0 * (fConst41 + ((fRec2[0] * (8.01320673450896e-19 + ((fRec0[0] * (fConst39 + (fConst38 * fRec0[0]))) + (fConst0 * (fConst35 + (fRec1[0] * (((fRec0[0] * (fConst33 + (fConst32 * fRec0[0]))) + (fConst0 * (fConst30 + (fRec1[0] * (fConst28 + (fRec0[0] * (fConst26 + (fConst25 * fRec0[0])))))))) - 3.99658685883635e-20))))))) + (fRec1[0] * (((fRec0[0] * (fConst22 + (fConst21 * fRec0[0]))) + (fConst0 * (fConst19 + (fRec1[0] * (fConst17 + (fRec0[0] * (fConst15 + (fConst14 * fRec0[0])))))))) - 2.50199593253019e-18))))))))) + (fRec1[0] * (((fRec0[0] * (fConst11 + (fConst10 * fRec0[0]))) + (fConst0 * (fConst8 + (fRec1[0] * (fConst6 + (fRec0[0] * (fConst4 + (fConst3 * fRec0[0])))))))) - 8.52468801543507e-16))));
		fRec4[0] = ((double)input0[i] - ((((((fRec4[1] * (fConst334 + ((((fRec2[0] * (4.26234400771753e-15 + ((fRec0[0] * (fConst333 + (fConst332 * fRec0[0]))) + (fConst0 * (fConst330 + (fRec1[0] * (((fRec0[0] * (fConst329 + (fConst328 * fRec0[0]))) + (fConst0 * (fConst327 + (fRec1[0] * (fConst326 + (fRec0[0] * (fConst325 + (fConst324 * fRec0[0])))))))) - 1.27550644430947e-16))))))) + (fRec0[0] * (fConst322 + (fConst321 * fRec0[0])))) + (fRec3[0] * (1.70493760308701e-16 + ((fRec0[0] * (fConst319 + (fConst318 * fRec0[0]))) + (fConst0 * (fConst316 + ((fRec2[0] * (2.40396202035269e-18 + ((fRec0[0] * (fConst315 + (fConst314 * fRec0[0]))) + (fConst0 * (fConst312 + (fRec1[0] * (((fRec0[0] * (fConst311 + (fConst310 * fRec0[0]))) + (fConst0 * (fConst309 + (fRec1[0] * (fConst308 + (fRec0[0] * (fConst307 + (fConst306 * fRec0[0])))))))) - 3.99658685883635e-20))))))) + (fRec1[0] * (((fRec0[0] * (fConst304 + (fConst303 * fRec0[0]))) + (fConst0 * (fConst302 + (fRec1[0] * (fConst301 + (fRec0[0] * (fConst300 + (fConst299 * fRec0[0])))))))) - 7.50598779759058e-18))))))))) + (fRec1[0] * (((fRec0[0] * (fConst297 + (fConst296 * fRec0[0]))) + (fConst0 * (fConst295 + (fRec1[0] * (fConst294 + (fRec0[0] * (fConst293 + (fConst292 * fRec0[0])))))))) - 4.26234400771753e-15))))) + (fRec4[2] * (fConst290 + ((((fRec2[0] * (8.52468801543507e-15 + ((fRec0[0] * (fConst289 + (fConst288 * fRec0[0]))) + (fConst0 * (fConst286 + (fRec1[0] * (((fRec0[0] * (fConst285 + (fConst284 * fRec0[0]))) + (fConst0 * (fConst283 + (fRec1[0] * (fConst282 + (fRec0[0] * (fConst281 + (fConst280 * fRec0[0])))))))) - 8.50337629539648e-17))))))) + (fRec0[0] * (fConst278 + (fConst277 * fRec0[0])))) + (fRec3[0] * (3.40987520617403e-16 + ((fRec0[0] * (fConst276 + (fConst275 * fRec0[0]))) + (fConst0 * (fConst274 + ((fRec2[0] * (1.60264134690179e-18 + ((fRec0[0] * (fConst273 + (fConst272 * fRec0[0]))) + (fConst0 * (fConst270 + (fRec1[0] * (7.99317371767269e-20 + ((fRec0[0] * (fConst269 + (fConst268 * fRec0[0]))) + (fConst0 * (fConst267 + (fRec1[0] * (fConst266 + (fRec0[0] * (fConst265 + (fConst264 * fRec0[0]))))))))))))))) + (fRec1[0] * (((fRec0[0] * (fConst262 + (fConst261 * fRec0[0]))) + (fConst0 * (fConst259 + (fRec1[0] * (fConst258 + (fRec0[0] * (fConst257 + (fConst256 * fRec0[0])))))))) - 5.00399186506038e-18))))))))) + (fRec1[0] * (((fRec0[0] * (fConst255 + (fConst254 * fRec0[0]))) + (fConst0 * (fConst252 + (fRec1[0] * (fConst251 + (fRec0[0] * (fConst250 + (fConst249 * fRec0[0])))))))) - 8.52468801543507e-15)))))) + (fRec4[3] * (fConst248 + ((((fRec2[0] * (8.52468801543507e-15 + ((fRec0[0] * (fConst246 + (fConst245 * fRec0[0]))) + (fConst0 * (fConst243 + (fRec1[0] * (8.50337629539648e-17 + ((fRec0[0] * (fConst241 + (fConst240 * fRec0[0]))) + (fConst0 * (fConst237 + (fRec1[0] * (fConst235 + (fRec0[0] * (fConst233 + (fConst232 * fRec0[0]))))))))))))))) + (fRec0[0] * (fConst230 + (fConst229 * fRec0[0])))) + (fRec3[0] * (3.40987520617403e-16 + ((fRec0[0] * (fConst226 + (fConst225 * fRec0[0]))) + (fConst0 * (fConst222 + ((fRec2[0] * (((fRec0[0] * (fConst220 + (fConst219 * fRec0[0]))) + (fConst0 * (fConst217 + (fRec1[0] * (7.99317371767269e-20 + ((fRec0[0] * (fConst215 + (fConst214 * fRec0[0]))) + (fConst0 * (fConst211 + (fRec1[0] * (fConst209 + (fRec0[0] * (fConst207 + (fConst206 * fRec0[0]))))))))))))) - 1.60264134690179e-18)) + (fRec1[0] * (5.00399186506038e-18 + ((fRec0[0] * (fConst204 + (fConst203 * fRec0[0]))) + (fConst0 * (fConst201 + (fRec1[0] * (fConst199 + (fRec0[0] * (fConst197 + (fConst196 * fRec0[0]))))))))))))))))) + (fRec1[0] * (((fRec0[0] * (fConst193 + (fConst192 * fRec0[0]))) + (fConst0 * (fConst190 + (fRec1[0] * (fConst188 + (fRec0[0] * (fConst186 + (fConst185 * fRec0[0])))))))) - 8.52468801543507e-15)))))) + (fRec4[4] * (fConst182 + ((((fRec2[0] * (4.26234400771753e-15 + ((fRec0[0] * (fConst180 + (fConst179 * fRec0[0]))) + (fConst0 * (fConst177 + (fRec1[0] * (1.27550644430947e-16 + ((fRec0[0] * (fConst175 + (fConst174 * fRec0[0]))) + (fConst0 * (fConst171 + (fRec1[0] * (fConst169 + (fRec0[0] * (fConst167 + (fConst166 * fRec0[0]))))))))))))))) + (fRec0[0] * (fConst164 + (fConst163 * fRec0[0])))) + (fRec3[0] * (1.70493760308701e-16 + ((fRec0[0] * (fConst161 + (fConst160 * fRec0[0]))) + (fConst0 * (fConst158 + ((fRec2[0] * (((fRec0[0] * (fConst156 + (fConst155 * fRec0[0]))) + (fConst0 * (fConst153 + (fRec1[0] * (((fRec0[0] * (fConst151 + (fConst150 * fRec0[0]))) + (fConst0 * (fConst147 + (fRec1[0] * (fConst145 + (fRec0[0] * (fConst143 + (fConst142 * fRec0[0])))))))) - 3.99658685883635e-20))))) - 2.40396202035269e-18)) + (fRec1[0] * (7.50598779759058e-18 + ((fRec0[0] * (fConst140 + (fConst139 * fRec0[0]))) + (fConst0 * (fConst136 + (fRec1[0] * (fConst134 + (fRec0[0] * (fConst132 + (fConst131 * fRec0[0]))))))))))))))))) + (fRec1[0] * (((fRec0[0] * (fConst129 + (fConst128 * fRec0[0]))) + (fConst0 * (fConst125 + (fRec1[0] * (fConst123 + (fRec0[0] * (fConst121 + (fConst120 * fRec0[0])))))))) - 4.26234400771753e-15)))))) + (fRec4[5] * (fConst118 + ((((fRec2[0] * (8.52468801543507e-16 + ((fRec0[0] * (fConst117 + (fConst116 * fRec0[0]))) + (fConst0 * (fConst115 + (fRec1[0] * (4.25168814769824e-17 + ((fRec0[0] * (fConst114 + (fConst113 * fRec0[0]))) + (fConst0 * (fConst111 + (fRec1[0] * (fConst110 + (fRec0[0] * (fConst109 + (fConst108 * fRec0[0]))))))))))))))) + (fRec0[0] * (fConst107 + (fConst106 * fRec0[0])))) + (fRec3[0] * (3.40987520617403e-17 + ((fRec0[0] * (fConst105 + (fConst104 * fRec0[0]))) + (fConst0 * (fConst103 + ((fRec2[0] * (((fRec0[0] * (fConst102 + (fConst101 * fRec0[0]))) + (fConst0 * (fConst100 + (fRec1[0] * (((fRec0[0] * (fConst99 + (fConst98 * fRec0[0]))) + (fConst0 * (fConst96 + (fRec1[0] * (fConst95 + (fRec0[0] * (fConst94 + (fConst93 * fRec0[0])))))))) - 3.99658685883635e-20))))) - 8.01320673450896e-19)) + (fRec1[0] * (2.50199593253019e-18 + ((fRec0[0] * (fConst92 + (fConst91 * fRec0[0]))) + (fConst0 * (fConst89 + (fRec1[0] * (fConst88 + (fRec0[0] * (fConst87 + (fConst86 * fRec0[0]))))))))))))))))) + (fRec1[0] * (((fRec0[0] * (fConst85 + (fConst84 * fRec0[0]))) + (fConst0 * (fConst82 + (fRec1[0] * (fConst81 + (fRec0[0] * (fConst80 + (fConst79 * fRec0[0])))))))) - 8.52468801543507e-16)))))) / fTemp0));
		fRec5[0] = (fSlow4 + (0.993 * fRec5[1]));
		output0[i] = (FAUSTFLOAT)(fConst376 * (((fRec0[0] * fRec5[0]) * ((((((fRec4[0] * (fConst375 + (((fConst374 * fRec1[0]) + (fRec2[0] * (3.23425287520332e-14 + (fConst0 * (fConst372 + (fConst371 * fRec1[0])))))) + (fRec3[0] * (1.90022438253841e-15 + (fConst0 * (fConst370 + (fConst369 * fRec2[0])))))))) + (fRec4[1] * (fConst368 + (((fConst367 * fRec1[0]) + (fRec2[0] * (3.23425287520332e-14 + (fConst0 * (fConst365 + (fConst364 * fRec1[0])))))) + (fRec3[0] * (1.90022438253841e-15 + (fConst0 * (fConst363 + (fConst362 * fRec2[0]))))))))) + (fRec4[2] * (fConst361 + (((fConst360 * fRec1[0]) + (fRec2[0] * ((fConst0 * (fConst359 + (fConst358 * fRec1[0]))) - 6.46850575040665e-14))) + (fRec3[0] * ((fConst0 * (fConst357 + (fConst356 * fRec2[0]))) - 3.80044876507682e-15)))))) + (fRec4[3] * (fConst355 + (((fConst354 * fRec1[0]) + (fRec2[0] * ((fConst0 * (fConst351 + (fConst350 * fRec1[0]))) - 6.46850575040665e-14))) + (fRec3[0] * ((fConst0 * (fConst348 + (fConst346 * fRec2[0]))) - 3.80044876507682e-15)))))) + (fRec4[4] * (fConst344 + (((fConst343 * fRec1[0]) + (fRec2[0] * (3.23425287520332e-14 + (fConst0 * (fConst341 + (fConst340 * fRec1[0])))))) + (fRec3[0] * (1.90022438253841e-15 + (fConst0 * (fConst338 + (fConst336 * fRec2[0]))))))))) + (fRec4[5] * (fConst78 + (((fConst77 * fRec1[0]) + (fRec2[0] * (3.23425287520332e-14 + (fConst0 * (fConst75 + (fConst74 * fRec1[0])))))) + (fRec3[0] * (1.90022438253841e-15 + (fConst0 * (fConst72 + (fConst70 * fRec2[0])))))))))) / fTemp0));
		// post processing
		fRec5[1] = fRec5[0];
		for (int i=5; i>0; i--) fRec4[i] = fRec4[i-1];
		fRec3[1] = fRec3[0];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
	}
#undef fslider0
#undef fslider1
#undef fslider2
#undef fslider3
#undef fslider4
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
		fslider2_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case INPUT: 
		fslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case MIDDLE: 
		fslider3_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case TREBLE: 
		fslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case VOLUME: 
		fslider4_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
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
