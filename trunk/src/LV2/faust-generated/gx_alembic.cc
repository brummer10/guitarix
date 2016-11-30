// generated from file '../src/LV2/faust/gx_alembic.dsp' by dsp2cc:
// Code generated with Faust 0.9.73 (http://faust.grame.fr)


namespace gx_alembic {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	double 	fConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec0[2];
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec1[2];
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
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec2[2];
	double 	fConst44;
	double 	fConst45;
	double 	fConst46;
	double 	fConst47;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fRec3[2];
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
	double 	fConst335;
	double 	fRec4[6];
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
	double 	fConst376;
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT	*fslider4_;
	double 	fRec5[2];
	double 	fConst377;
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
	fConst0 = double(min(192000, max(1, fSamplingFreq)));
	fConst1 = (3.11587227557603e-22 * fConst0);
	fConst2 = (4.26234400771753e-15 + (fConst0 * (1.44750067678226e-15 + (fConst0 * (1.27957634839887e-16 + (fConst0 * (2.78390986018658e-18 + fConst1)))))));
	fConst3 = (6.9222867471881e-23 * fConst0);
	fConst4 = ((fConst0 * ((fConst0 * (0 - (3.19433851972335e-21 + fConst3))) - 3.61733701138641e-20)) - 1.06558600192938e-19);
	fConst5 = (6.4815418981162e-23 * fConst0);
	fConst6 = (2.99095367015295e-21 + fConst5);
	fConst7 = (9.9773970218107e-20 + (fConst0 * (3.38701967358278e-20 + (fConst0 * fConst6))));
	fConst8 = ((fConst0 * ((fConst0 * (0 - fConst6)) - 3.38701967358278e-20)) - 9.9773970218107e-20);
	fConst9 = (6.22837159378651e-23 * fConst0);
	fConst10 = ((fConst0 * ((fConst0 * (fConst9 - 5.51032162701814e-19)) - 2.55264149017724e-17)) - 2.89308329876105e-16);
	fConst11 = (5.83180860841434e-23 * fConst0);
	fConst12 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst11 - 5.15947717885593e-19)) - 2.3901137548476e-17)) - 2.70887949322196e-16)) - 7.98191761744856e-16);
	fConst13 = (7.98191761744856e-16 + (fConst0 * (2.70887949322196e-16 + (fConst0 * (2.3901137548476e-17 + (fConst0 * (5.15947717885593e-19 - fConst11)))))));
	fConst14 = (3.00214748513934e-23 * fConst0);
	fConst15 = (2.41249362977723e-17 + (fConst0 * (4.67347173267892e-18 + (fConst0 * (2.30482265359608e-19 + fConst14)))));
	fConst16 = (5.18749886368413e-24 * fConst0);
	fConst17 = ((fConst0 * (0 - (9.11043413643421e-23 + fConst16))) - 3.13282284567239e-22);
	fConst18 = (4.85720867386155e-24 * fConst0);
	fConst19 = (8.53036904160507e-23 + fConst18);
	fConst20 = (2.93335472441235e-22 + (fConst0 * fConst19));
	fConst21 = ((fConst0 * (0 - fConst19)) - 2.93335472441235e-22);
	fConst22 = (6.80009214340617e-24 * fConst0);
	fConst23 = (2.34269282072115e-18 + (fConst0 * (6.80858259239558e-19 + (fConst0 * (3.86721597525567e-20 - fConst22)))));
	fConst24 = ((fConst0 * ((fConst0 * (fConst22 - 3.86721597525567e-20)) - 6.80858259239558e-19)) - 2.34269282072115e-18);
	fConst25 = (7.26249840915779e-24 * fConst0);
	fConst26 = ((fConst0 * ((fConst0 * (fConst25 - 4.13018666157306e-20)) - 7.27156620867848e-19)) - 2.50199593253019e-18);
	fConst27 = (4.79935142182139e-25 * fConst0);
	fConst28 = (8.01320673450896e-19 + (fConst0 * (4.60313050181815e-19 + (fConst0 * (7.89937124628652e-20 + (fConst0 * (3.68677255620389e-21 + fConst27)))))));
	fConst29 = (8.29294036031137e-26 * fConst0);
	fConst30 = ((fConst0 * (0 - (1.45642994698098e-24 + fConst29))) - 5.0082542090681e-24);
	fConst31 = (7.76492543100316e-26 * fConst0);
	fConst32 = (1.36369845222938e-24 + fConst31);
	fConst33 = (4.68937660025103e-24 + (fConst0 * fConst32));
	fConst34 = ((fConst0 * (0 - fConst32)) - 4.68937660025103e-24);
	fConst35 = (1.08708956034044e-25 * fConst0);
	fConst36 = (3.74212252700032e-20 + (fConst0 * (1.08757485215501e-20 + (fConst0 * (6.17731871560931e-22 - fConst35)))));
	fConst37 = ((fConst0 * ((fConst0 * (fConst35 - 6.17731871560931e-22)) - 1.08757485215501e-20)) - 3.74212252700032e-20);
	fConst38 = (1.16101165044359e-25 * fConst0);
	fConst39 = ((fConst0 * ((fConst0 * (fConst38 - 6.59737638827074e-22)) - 1.16152994210155e-20)) - 3.99658685883635e-20);
	fConst40 = (4.49377473953314e-25 * fConst0);
	fConst41 = (3.45203422865533e-21 + fConst40);
	fConst42 = ((fConst0 * ((fConst0 * ((fConst0 * (0 - fConst41)) - 7.39641502461285e-20)) - 4.31004728634658e-19)) - 7.50300256040165e-19);
	fConst43 = (7.50300256040165e-19 + (fConst0 * (4.31004728634658e-19 + (fConst0 * (7.39641502461285e-20 + (fConst0 * fConst41))))));
	fConst44 = (2.81099951792073e-23 * fConst0);
	fConst45 = (2.15807364568921e-19 + fConst44);
	fConst46 = (3.19276704697943e-17 + (fConst0 * (2.25888916645809e-17 + (fConst0 * (4.37590986205892e-18 + (fConst0 * fConst45))))));
	fConst47 = ((fConst0 * ((fConst0 * ((fConst0 * (0 - fConst45)) - 4.37590986205892e-18)) - 2.25888916645809e-17)) - 3.19276704697943e-17);
	fConst48 = (2.91748340409741e-22 * fConst0);
	fConst49 = (2.60665717245934e-18 + fConst48);
	fConst50 = (3.99095880872428e-15 + (fConst0 * (1.35533771234294e-15 + (fConst0 * (1.19810519513002e-16 + (fConst0 * fConst49))))));
	fConst51 = ((fConst0 * ((fConst0 * ((fConst0 * (0 - fConst49)) - 1.19810519513002e-16)) - 1.35533771234294e-15)) - 3.99095880872428e-15);
	fConst52 = (4.98115635891407e-24 * fConst0);
	fConst53 = (5.02958323262947e-16 + (fConst0 * (9.10160440190383e-17 + (fConst0 * (5.01579761573499e-18 + (fConst0 * (4.49743041952051e-20 + fConst52)))))));
	fConst54 = (1.10662407182939e-24 * fConst0);
	fConst55 = ((fConst0 * ((fConst0 * (0 - (1.11081445580983e-22 + fConst54))) - 1.63229099203665e-21)) - 5.32793000964692e-21);
	fConst56 = (1.03616486126347e-24 * fConst0);
	fConst57 = (1.0400884417695e-22 + fConst56);
	fConst58 = (4.98869851090535e-21 + (fConst0 * (1.52836235209424e-21 + (fConst0 * fConst57))));
	fConst59 = ((fConst0 * ((fConst0 * (0 - fConst57)) - 1.52836235209424e-21)) - 4.98869851090535e-21);
	fConst60 = (9.32295933998211e-25 * fConst0);
	fConst61 = (3.98098141170247e-17 + (fConst0 * (1.21893473917967e-17 + (fConst0 * (8.27894207186978e-19 + (fConst0 * (8.13465102081422e-21 - fConst60)))))));
	fConst62 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst60 - 8.13465102081422e-21)) - 8.27894207186978e-19)) - 1.21893473917967e-17)) - 3.98098141170247e-17);
	fConst63 = (9.95692057510089e-25 * fConst0);
	fConst64 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst63 - 8.68780729022958e-21)) - 8.84191013275692e-19)) - 1.30182230144389e-17)) - 4.25168814769824e-17);
	fConst65 = (4.66400408138021e-24 * fConst0);
	fConst66 = (4.21107717183568e-20 + fConst65);
	fConst67 = (7.98191761744856e-16 + (fConst0 * (4.70934759609501e-16 + (fConst0 * (8.52210149990995e-17 + (fConst0 * (4.69643971510767e-18 + (fConst0 * fConst66))))))));
	fConst68 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (0 - fConst66)) - 4.69643971510767e-18)) - 8.52210149990995e-17)) - 4.70934759609501e-16)) - 7.98191761744856e-16);
	fConst69 = (7.96061742599918e-22 * fConst0);
	fConst70 = (fConst0 * ((fConst0 * (4.56560363232067e-18 - fConst69)) - 3.04019770269112e-17));
	fConst71 = (4.97962026222076e-20 * fConst0);
	fConst72 = (1.90022438253841e-15 + (fConst0 * (fConst71 - 2.85365632064909e-16)));
	fConst73 = (3.55687161587197e-19 * fConst0);
	fConst74 = (8.06546851671652e-17 + (fConst0 * (fConst73 - 1.44694505189894e-17)));
	fConst75 = ((fConst0 * (1.44694505189894e-17 - fConst73)) - 8.06546851671652e-17);
	fConst76 = (5.68615530428513e-21 * fConst0);
	fConst77 = faustpower<2>(fConst0);
	fConst78 = (fConst77 * (fConst76 - 3.79077020285676e-20));
	fConst79 = (3.23425287520332e-14 + (fConst0 * ((fConst0 * (9.98505002369502e-19 - fConst76)) - 4.85778329480724e-15)));
	fConst80 = (4.26234400771753e-15 + (fConst0 * ((fConst0 * (1.27957634839887e-16 + (fConst0 * (fConst1 - 2.78390986018658e-18)))) - 1.44750067678226e-15)));
	fConst81 = (2.89308329876105e-16 + (fConst0 * ((fConst0 * (5.51032162701814e-19 + fConst9)) - 2.55264149017724e-17)));
	fConst82 = (1.06558600192938e-19 + (fConst0 * ((fConst0 * (3.19433851972335e-21 - fConst3)) - 3.61733701138641e-20)));
	fConst83 = ((fConst0 * (3.38701967358278e-20 + (fConst0 * (fConst5 - 2.99095367015295e-21)))) - 9.9773970218107e-20);
	fConst84 = (9.9773970218107e-20 + (fConst0 * ((fConst0 * (2.99095367015295e-21 - fConst5)) - 3.38701967358278e-20)));
	fConst85 = (5.15947717885593e-19 + fConst11);
	fConst86 = ((fConst0 * (2.70887949322196e-16 + (fConst0 * ((fConst0 * fConst85) - 2.3901137548476e-17)))) - 7.98191761744856e-16);
	fConst87 = (7.98191761744856e-16 + (fConst0 * ((fConst0 * (2.3901137548476e-17 + (fConst0 * (0 - fConst85)))) - 2.70887949322196e-16)));
	fConst88 = ((fConst0 * (4.67347173267892e-18 + (fConst0 * (fConst14 - 2.30482265359608e-19)))) - 2.41249362977723e-17);
	fConst89 = (2.50199593253019e-18 + (fConst0 * ((fConst0 * (4.13018666157306e-20 + fConst25)) - 7.27156620867848e-19)));
	fConst90 = ((fConst0 * (9.11043413643421e-23 - fConst16)) - 3.13282284567239e-22);
	fConst91 = (2.93335472441235e-22 + (fConst0 * (fConst18 - 8.53036904160507e-23)));
	fConst92 = ((fConst0 * (8.53036904160507e-23 - fConst18)) - 2.93335472441235e-22);
	fConst93 = (3.86721597525567e-20 + fConst22);
	fConst94 = ((fConst0 * (6.80858259239558e-19 + (fConst0 * (0 - fConst93)))) - 2.34269282072115e-18);
	fConst95 = (2.34269282072115e-18 + (fConst0 * ((fConst0 * fConst93) - 6.80858259239558e-19)));
	fConst96 = ((fConst0 * (4.60313050181815e-19 + (fConst0 * ((fConst0 * (3.68677255620389e-21 - fConst27)) - 7.89937124628652e-20)))) - 8.01320673450896e-19);
	fConst97 = ((fConst0 * (1.16152994210155e-20 + (fConst0 * (0 - (6.59737638827074e-22 + fConst38))))) - 3.99658685883635e-20);
	fConst98 = (5.0082542090681e-24 + (fConst0 * (fConst29 - 1.45642994698098e-24)));
	fConst99 = ((fConst0 * (1.36369845222938e-24 - fConst31)) - 4.68937660025103e-24);
	fConst100 = (4.68937660025103e-24 + (fConst0 * (fConst31 - 1.36369845222938e-24)));
	fConst101 = (6.17731871560931e-22 + fConst35);
	fConst102 = (3.74212252700032e-20 + (fConst0 * ((fConst0 * fConst101) - 1.08757485215501e-20)));
	fConst103 = ((fConst0 * (1.08757485215501e-20 + (fConst0 * (0 - fConst101)))) - 3.74212252700032e-20);
	fConst104 = (7.50300256040165e-19 + (fConst0 * ((fConst0 * (7.39641502461285e-20 + (fConst0 * (fConst40 - 3.45203422865533e-21)))) - 4.31004728634658e-19)));
	fConst105 = ((fConst0 * (4.31004728634658e-19 + (fConst0 * ((fConst0 * (3.45203422865533e-21 - fConst40)) - 7.39641502461285e-20)))) - 7.50300256040165e-19);
	fConst106 = (3.19276704697943e-17 + (fConst0 * ((fConst0 * (4.37590986205892e-18 + (fConst0 * (fConst44 - 2.15807364568921e-19)))) - 2.25888916645809e-17)));
	fConst107 = ((fConst0 * (2.25888916645809e-17 + (fConst0 * ((fConst0 * (2.15807364568921e-19 - fConst44)) - 4.37590986205892e-18)))) - 3.19276704697943e-17);
	fConst108 = (3.99095880872428e-15 + (fConst0 * ((fConst0 * (1.19810519513002e-16 + (fConst0 * (fConst48 - 2.60665717245934e-18)))) - 1.35533771234294e-15)));
	fConst109 = ((fConst0 * (1.35533771234294e-15 + (fConst0 * ((fConst0 * (2.60665717245934e-18 - fConst48)) - 1.19810519513002e-16)))) - 3.99095880872428e-15);
	fConst110 = ((fConst0 * (9.10160440190383e-17 + (fConst0 * ((fConst0 * (4.49743041952051e-20 - fConst52)) - 5.01579761573499e-18)))) - 5.02958323262947e-16);
	fConst111 = (4.25168814769824e-17 + (fConst0 * ((fConst0 * (8.84191013275692e-19 + (fConst0 * (0 - (8.68780729022958e-21 + fConst63))))) - 1.30182230144389e-17)));
	fConst112 = ((fConst0 * (1.63229099203665e-21 + (fConst0 * (fConst54 - 1.11081445580983e-22)))) - 5.32793000964692e-21);
	fConst113 = (4.98869851090535e-21 + (fConst0 * ((fConst0 * (1.0400884417695e-22 - fConst56)) - 1.52836235209424e-21)));
	fConst114 = ((fConst0 * (1.52836235209424e-21 + (fConst0 * (fConst56 - 1.0400884417695e-22)))) - 4.98869851090535e-21);
	fConst115 = (8.13465102081422e-21 + fConst60);
	fConst116 = ((fConst0 * (1.21893473917967e-17 + (fConst0 * ((fConst0 * fConst115) - 8.27894207186978e-19)))) - 3.98098141170247e-17);
	fConst117 = (3.98098141170247e-17 + (fConst0 * ((fConst0 * (8.27894207186978e-19 + (fConst0 * (0 - fConst115)))) - 1.21893473917967e-17)));
	fConst118 = (7.98191761744856e-16 + (fConst0 * ((fConst0 * (8.52210149990995e-17 + (fConst0 * ((fConst0 * (4.21107717183568e-20 - fConst65)) - 4.69643971510767e-18)))) - 4.70934759609501e-16)));
	fConst119 = ((fConst0 * (4.70934759609501e-16 + (fConst0 * ((fConst0 * (4.69643971510767e-18 + (fConst0 * (fConst65 - 4.21107717183568e-20)))) - 8.52210149990995e-17)))) - 7.98191761744856e-16);
	fConst120 = (9.3476168267281e-22 * fConst0);
	fConst121 = (2.13117200385877e-14 + (fConst0 * ((fConst0 * (1.27957634839887e-16 + (fConst0 * (2.78390986018658e-18 - fConst120)))) - 4.34250203034679e-15)));
	fConst122 = (1.86851147813595e-22 * fConst0);
	fConst123 = (8.67924989628316e-16 + (fConst0 * ((fConst0 * (0 - (5.51032162701814e-19 + fConst122))) - 2.55264149017724e-17)));
	fConst124 = (2.07668602415643e-22 * fConst0);
	fConst125 = (3.19675800578815e-19 + (fConst0 * ((fConst0 * (fConst124 - 3.19433851972335e-21)) - 3.61733701138641e-20)));
	fConst126 = (1.94446256943486e-22 * fConst0);
	fConst127 = ((fConst0 * (3.38701967358278e-20 + (fConst0 * (2.99095367015295e-21 - fConst126)))) - 2.99321910654321e-19);
	fConst128 = (2.99321910654321e-19 + (fConst0 * ((fConst0 * (fConst126 - 2.99095367015295e-21)) - 3.38701967358278e-20)));
	fConst129 = (1.7495425825243e-22 * fConst0);
	fConst130 = (5.15947717885593e-19 + fConst129);
	fConst131 = ((fConst0 * (8.12663847966588e-16 + (fConst0 * ((fConst0 * (0 - fConst130)) - 2.3901137548476e-17)))) - 3.99095880872428e-15);
	fConst132 = (3.99095880872428e-15 + (fConst0 * ((fConst0 * (2.3901137548476e-17 + (fConst0 * fConst130))) - 8.12663847966588e-16)));
	fConst133 = (9.00644245541801e-23 * fConst0);
	fConst134 = ((fConst0 * (4.67347173267892e-18 + (fConst0 * (2.30482265359608e-19 - fConst133)))) - 7.2374808893317e-17);
	fConst135 = (2.17874952274734e-23 * fConst0);
	fConst136 = (7.50598779759058e-18 + (fConst0 * ((fConst0 * (0 - (4.13018666157306e-20 + fConst135))) - 7.27156620867848e-19)));
	fConst137 = (1.45716260215846e-23 * fConst0);
	fConst138 = (2.93335472441235e-22 + (fConst0 * (8.53036904160507e-23 - fConst137)));
	fConst139 = ((fConst0 * (fConst137 - 8.53036904160507e-23)) - 2.93335472441235e-22);
	fConst140 = (1.55624965910524e-23 * fConst0);
	fConst141 = ((fConst0 * (fConst140 - 9.11043413643421e-23)) - 3.13282284567239e-22);
	fConst142 = (2.04002764302185e-23 * fConst0);
	fConst143 = (3.86721597525567e-20 + fConst142);
	fConst144 = ((fConst0 * (6.80858259239558e-19 + (fConst0 * fConst143))) - 7.02807846216346e-18);
	fConst145 = (7.02807846216346e-18 + (fConst0 * ((fConst0 * (0 - fConst143)) - 6.80858259239558e-19)));
	fConst146 = (2.39967571091069e-24 * fConst0);
	fConst147 = ((fConst0 * (4.60313050181815e-19 + (fConst0 * (7.89937124628652e-20 + (fConst0 * (fConst146 - 1.10603176686117e-20)))))) - 2.40396202035269e-18);
	fConst148 = (5.80505825221796e-25 * fConst0);
	fConst149 = ((fConst0 * ((fConst0 * (1.97921291648122e-21 + fConst148)) - 1.16152994210155e-20)) - 3.99658685883635e-20);
	fConst150 = (4.14647018015568e-25 * fConst0);
	fConst151 = ((fConst0 * (4.36928984094294e-24 - fConst150)) - 5.0082542090681e-24);
	fConst152 = (3.88246271550158e-25 * fConst0);
	fConst153 = (4.68937660025103e-24 + (fConst0 * (fConst152 - 4.09109535668814e-24)));
	fConst154 = ((fConst0 * (4.09109535668814e-24 - fConst152)) - 4.68937660025103e-24);
	fConst155 = (5.43544780170221e-25 * fConst0);
	fConst156 = (1.85319561468279e-21 + fConst155);
	fConst157 = (3.74212252700032e-20 + (fConst0 * (1.08757485215501e-20 + (fConst0 * (0 - fConst156)))));
	fConst158 = ((fConst0 * ((fConst0 * fConst156) - 1.08757485215501e-20)) - 3.74212252700032e-20);
	fConst159 = (2.24688736976657e-24 * fConst0);
	fConst160 = (2.2509007681205e-18 + (fConst0 * ((fConst0 * ((fConst0 * (1.0356102685966e-20 - fConst159)) - 7.39641502461285e-20)) - 4.31004728634658e-19)));
	fConst161 = ((fConst0 * (4.31004728634658e-19 + (fConst0 * (7.39641502461285e-20 + (fConst0 * (fConst159 - 1.0356102685966e-20)))))) - 2.2509007681205e-18);
	fConst162 = (8.43299855376218e-23 * fConst0);
	fConst163 = (1.59638352348971e-16 + (fConst0 * ((fConst0 * (4.37590986205892e-18 + (fConst0 * (2.15807364568921e-19 - fConst162)))) - 6.77666749937426e-17)));
	fConst164 = ((fConst0 * (6.77666749937426e-17 + (fConst0 * ((fConst0 * (fConst162 - 2.15807364568921e-19)) - 4.37590986205892e-18)))) - 1.59638352348971e-16);
	fConst165 = (8.75245021229223e-22 * fConst0);
	fConst166 = (1.99547940436214e-14 + (fConst0 * ((fConst0 * (1.19810519513002e-16 + (fConst0 * (2.60665717245934e-18 - fConst165)))) - 4.06601313702883e-15)));
	fConst167 = ((fConst0 * (4.06601313702883e-15 + (fConst0 * ((fConst0 * (fConst165 - 2.60665717245934e-18)) - 1.19810519513002e-16)))) - 1.99547940436214e-14);
	fConst168 = (2.49057817945703e-23 * fConst0);
	fConst169 = ((fConst0 * (9.10160440190383e-17 + (fConst0 * (5.01579761573499e-18 + (fConst0 * (fConst168 - 1.34922912585615e-19)))))) - 1.50887496978884e-15);
	fConst170 = (4.97846028755044e-24 * fConst0);
	fConst171 = (1.27550644430947e-16 + (fConst0 * ((fConst0 * ((fConst0 * (2.60634218706887e-20 + fConst170)) - 8.84191013275692e-19)) - 1.30182230144389e-17)));
	fConst172 = (5.53312035914695e-24 * fConst0);
	fConst173 = ((fConst0 * ((fConst0 * (3.33244336742949e-22 - fConst172)) - 1.63229099203665e-21)) - 5.32793000964692e-21);
	fConst174 = (5.18082430631737e-24 * fConst0);
	fConst175 = (4.98869851090535e-21 + (fConst0 * (1.52836235209424e-21 + (fConst0 * (fConst174 - 3.12026532530851e-22)))));
	fConst176 = ((fConst0 * ((fConst0 * (3.12026532530851e-22 - fConst174)) - 1.52836235209424e-21)) - 4.98869851090535e-21);
	fConst177 = (4.66147966999105e-24 * fConst0);
	fConst178 = (2.44039530624426e-20 + fConst177);
	fConst179 = ((fConst0 * (1.21893473917967e-17 + (fConst0 * (8.27894207186978e-19 + (fConst0 * (0 - fConst178)))))) - 1.19429442351074e-16);
	fConst180 = (1.19429442351074e-16 + (fConst0 * ((fConst0 * ((fConst0 * fConst178) - 8.27894207186978e-19)) - 1.21893473917967e-17)));
	fConst181 = (2.33200204069011e-23 * fConst0);
	fConst182 = (3.99095880872428e-15 + (fConst0 * ((fConst0 * (8.52210149990995e-17 + (fConst0 * (4.69643971510767e-18 + (fConst0 * (fConst181 - 1.26332315155071e-19)))))) - 1.4128042788285e-15)));
	fConst183 = ((fConst0 * (1.4128042788285e-15 + (fConst0 * ((fConst0 * ((fConst0 * (1.26332315155071e-19 - fConst181)) - 4.69643971510767e-18)) - 8.52210149990995e-17)))) - 3.99095880872428e-15);
	fConst184 = (6.23174455115207e-22 * fConst0);
	fConst185 = (4.26234400771753e-14 + (fConst0 * ((fConst0 * ((fConst0 * (5.56781972037316e-18 + fConst184)) - 2.55915269679773e-16)) - 2.89500135356453e-15)));
	fConst186 = (1.2456743187573e-22 * fConst0);
	fConst187 = (5.78616659752211e-16 + (fConst0 * (5.10528298035447e-17 + (fConst0 * (fConst186 - 1.10206432540363e-18)))));
	fConst188 = (1.38445734943762e-22 * fConst0);
	fConst189 = (2.13117200385877e-19 + (fConst0 * (7.23467402277282e-20 + (fConst0 * (0 - (6.38867703944669e-21 + fConst188))))));
	fConst190 = (1.29630837962324e-22 * fConst0);
	fConst191 = (5.98190734030589e-21 + fConst190);
	fConst192 = ((fConst0 * ((fConst0 * fConst191) - 6.77403934716556e-20)) - 1.99547940436214e-19);
	fConst193 = (1.99547940436214e-19 + (fConst0 * (6.77403934716556e-20 + (fConst0 * (0 - fConst191)))));
	fConst194 = (1.16636172168287e-22 * fConst0);
	fConst195 = ((fConst0 * (5.41775898644392e-16 + (fConst0 * (4.7802275096952e-17 + (fConst0 * (fConst194 - 1.03189543577119e-18)))))) - 7.98191761744856e-15);
	fConst196 = (7.98191761744856e-15 + (fConst0 * ((fConst0 * ((fConst0 * (1.03189543577119e-18 - fConst194)) - 4.7802275096952e-17)) - 5.41775898644392e-16)));
	fConst197 = (6.00429497027867e-23 * fConst0);
	fConst198 = ((fConst0 * ((fConst0 * (4.60964530719215e-19 + fConst197)) - 9.34694346535784e-18)) - 4.82498725955447e-17);
	fConst199 = (1.45249968183156e-23 * fConst0);
	fConst200 = (5.00399186506038e-18 + (fConst0 * (1.4543132417357e-18 + (fConst0 * (fConst199 - 8.26037332314611e-20)))));
	fConst201 = (1.03749977273683e-23 * fConst0);
	fConst202 = (6.26564569134477e-22 + (fConst0 * (0 - (1.82208682728684e-22 + fConst201))));
	fConst203 = (9.7144173477231e-24 * fConst0);
	fConst204 = (1.70607380832101e-22 + fConst203);
	fConst205 = ((fConst0 * fConst204) - 5.86670944882469e-22);
	fConst206 = (5.86670944882469e-22 + (fConst0 * (0 - fConst204)));
	fConst207 = (1.36001842868123e-23 * fConst0);
	fConst208 = ((fConst0 * ((fConst0 * (7.73443195051134e-20 - fConst207)) - 1.36171651847912e-18)) - 4.68538564144231e-18);
	fConst209 = (4.68538564144231e-18 + (fConst0 * (1.36171651847912e-18 + (fConst0 * (fConst207 - 7.73443195051134e-20)))));
	fConst210 = (4.79935142182139e-24 * fConst0);
	fConst211 = ((fConst0 * ((fConst0 * (1.5798742492573e-19 + (fConst0 * (7.37354511240778e-21 - fConst210)))) - 9.2062610036363e-19)) - 1.60264134690179e-18);
	fConst212 = (1.16101165044359e-24 * fConst0);
	fConst213 = (7.99317371767269e-20 + (fConst0 * ((fConst0 * (0 - (1.31947527765415e-21 + fConst212))) - 2.3230598842031e-20)));
	fConst214 = (7.76492543100316e-25 * fConst0);
	fConst215 = (9.37875320050206e-24 + (fConst0 * (2.72739690445876e-24 - fConst214)));
	fConst216 = ((fConst0 * (fConst214 - 2.72739690445876e-24)) - 9.37875320050206e-24);
	fConst217 = (8.29294036031137e-25 * fConst0);
	fConst218 = ((fConst0 * (fConst217 - 2.91285989396196e-24)) - 1.00165084181362e-23);
	fConst219 = (1.08708956034044e-24 * fConst0);
	fConst220 = (1.23546374312186e-21 + fConst219);
	fConst221 = ((fConst0 * (2.17514970431002e-20 + (fConst0 * fConst220))) - 7.48424505400065e-20);
	fConst222 = (7.48424505400065e-20 + (fConst0 * ((fConst0 * (0 - fConst220)) - 2.17514970431002e-20)));
	fConst223 = (4.49377473953314e-24 * fConst0);
	fConst224 = (1.50060051208033e-18 + (fConst0 * (8.62009457269317e-19 + (fConst0 * ((fConst0 * (fConst223 - 6.90406845731066e-21)) - 1.47928300492257e-19)))));
	fConst225 = ((fConst0 * ((fConst0 * (1.47928300492257e-19 + (fConst0 * (6.90406845731066e-21 - fConst223)))) - 8.62009457269317e-19)) - 1.50060051208033e-18);
	fConst226 = (5.62199903584146e-23 * fConst0);
	fConst227 = (4.31614729137842e-19 + fConst226);
	fConst228 = (3.19276704697943e-16 + (fConst0 * ((fConst0 * ((fConst0 * fConst227) - 8.75181972411783e-18)) - 4.51777833291617e-17)));
	fConst229 = ((fConst0 * (4.51777833291617e-17 + (fConst0 * (8.75181972411783e-18 + (fConst0 * (0 - fConst227)))))) - 3.19276704697943e-16);
	fConst230 = (5.83496680819482e-22 * fConst0);
	fConst231 = (5.21331434491869e-18 + fConst230);
	fConst232 = (3.99095880872428e-14 + (fConst0 * ((fConst0 * ((fConst0 * fConst231) - 2.39621039026005e-16)) - 2.71067542468589e-15)));
	fConst233 = ((fConst0 * (2.71067542468589e-15 + (fConst0 * (2.39621039026005e-16 + (fConst0 * (0 - fConst231)))))) - 3.99095880872428e-14);
	fConst234 = (4.98115635891407e-23 * fConst0);
	fConst235 = ((fConst0 * ((fConst0 * (1.003159523147e-17 + (fConst0 * (8.99486083904102e-20 - fConst234)))) - 1.82032088038077e-16)) - 1.00591664652589e-15);
	fConst236 = (9.95692057510089e-24 * fConst0);
	fConst237 = (8.50337629539648e-17 + (fConst0 * (2.60364460288779e-17 + (fConst0 * ((fConst0 * (0 - (1.73756145804592e-20 + fConst236))) - 1.76838202655138e-18)))));
	fConst238 = (1.10662407182939e-23 * fConst0);
	fConst239 = (1.06558600192938e-20 + (fConst0 * ((fConst0 * (fConst238 - 2.22162891161966e-22)) - 3.26458198407329e-21)));
	fConst240 = (1.03616486126347e-23 * fConst0);
	fConst241 = ((fConst0 * (3.05672470418848e-21 + (fConst0 * (2.08017688353901e-22 - fConst240)))) - 9.97739702181071e-21);
	fConst242 = (9.97739702181071e-21 + (fConst0 * ((fConst0 * (fConst240 - 2.08017688353901e-22)) - 3.05672470418848e-21)));
	fConst243 = (9.32295933998211e-24 * fConst0);
	fConst244 = (1.62693020416284e-20 + fConst243);
	fConst245 = ((fConst0 * ((fConst0 * (1.65578841437396e-18 + (fConst0 * fConst244))) - 2.43786947835935e-17)) - 7.96196282340494e-17);
	fConst246 = (7.96196282340494e-17 + (fConst0 * (2.43786947835935e-17 + (fConst0 * ((fConst0 * (0 - fConst244)) - 1.65578841437396e-18)))));
	fConst247 = (4.66400408138021e-23 * fConst0);
	fConst248 = (7.98191761744856e-15 + (fConst0 * ((fConst0 * ((fConst0 * (9.39287943021533e-18 + (fConst0 * (8.42215434367137e-20 - fConst247)))) - 1.70442029998199e-16)) - 9.41869519219001e-16)));
	fConst249 = ((fConst0 * (9.41869519219001e-16 + (fConst0 * (1.70442029998199e-16 + (fConst0 * ((fConst0 * (fConst247 - 8.42215434367137e-20)) - 9.39287943021533e-18)))))) - 7.98191761744856e-15);
	fConst250 = (4.26234400771753e-14 + (fConst0 * (2.89500135356453e-15 + (fConst0 * ((fConst0 * (fConst184 - 5.56781972037316e-18)) - 2.55915269679773e-16)))));
	fConst251 = ((fConst0 * (5.10528298035447e-17 + (fConst0 * (1.10206432540363e-18 + fConst186)))) - 5.78616659752211e-16);
	fConst252 = ((fConst0 * (7.23467402277282e-20 + (fConst0 * (6.38867703944669e-21 - fConst188)))) - 2.13117200385877e-19);
	fConst253 = (1.99547940436214e-19 + (fConst0 * ((fConst0 * (fConst190 - 5.98190734030589e-21)) - 6.77403934716556e-20)));
	fConst254 = ((fConst0 * (6.77403934716556e-20 + (fConst0 * (5.98190734030589e-21 - fConst190)))) - 1.99547940436214e-19);
	fConst255 = (1.03189543577119e-18 + fConst194);
	fConst256 = ((fConst0 * ((fConst0 * (4.7802275096952e-17 + (fConst0 * fConst255))) - 5.41775898644392e-16)) - 7.98191761744856e-15);
	fConst257 = (7.98191761744856e-15 + (fConst0 * (5.41775898644392e-16 + (fConst0 * ((fConst0 * (0 - fConst255)) - 4.7802275096952e-17)))));
	fConst258 = (4.82498725955447e-17 + (fConst0 * ((fConst0 * (fConst197 - 4.60964530719215e-19)) - 9.34694346535784e-18)));
	fConst259 = ((fConst0 * (1.4543132417357e-18 + (fConst0 * (8.26037332314611e-20 + fConst199)))) - 5.00399186506038e-18);
	fConst260 = (6.26564569134477e-22 + (fConst0 * (1.82208682728684e-22 - fConst201)));
	fConst261 = ((fConst0 * (fConst203 - 1.70607380832101e-22)) - 5.86670944882469e-22);
	fConst262 = (5.86670944882469e-22 + (fConst0 * (1.70607380832101e-22 - fConst203)));
	fConst263 = (7.73443195051134e-20 + fConst207);
	fConst264 = (4.68538564144231e-18 + (fConst0 * ((fConst0 * (0 - fConst263)) - 1.36171651847912e-18)));
	fConst265 = ((fConst0 * (1.36171651847912e-18 + (fConst0 * fConst263))) - 4.68538564144231e-18);
	fConst266 = (1.60264134690179e-18 + (fConst0 * ((fConst0 * ((fConst0 * (7.37354511240778e-21 + fConst210)) - 1.5798742492573e-19)) - 9.2062610036363e-19)));
	fConst267 = (7.99317371767269e-20 + (fConst0 * (2.3230598842031e-20 + (fConst0 * (fConst212 - 1.31947527765415e-21)))));
	fConst268 = (1.00165084181362e-23 + (fConst0 * (0 - (2.91285989396196e-24 + fConst217))));
	fConst269 = (2.72739690445876e-24 + fConst214);
	fConst270 = ((fConst0 * fConst269) - 9.37875320050206e-24);
	fConst271 = (9.37875320050206e-24 + (fConst0 * (0 - fConst269)));
	fConst272 = ((fConst0 * ((fConst0 * (1.23546374312186e-21 - fConst219)) - 2.17514970431002e-20)) - 7.48424505400065e-20);
	fConst273 = (7.48424505400065e-20 + (fConst0 * (2.17514970431002e-20 + (fConst0 * (fConst219 - 1.23546374312186e-21)))));
	fConst274 = (6.90406845731066e-21 + fConst223);
	fConst275 = ((fConst0 * (8.62009457269317e-19 + (fConst0 * (1.47928300492257e-19 + (fConst0 * (0 - fConst274)))))) - 1.50060051208033e-18);
	fConst276 = (1.50060051208033e-18 + (fConst0 * ((fConst0 * ((fConst0 * fConst274) - 1.47928300492257e-19)) - 8.62009457269317e-19)));
	fConst277 = (3.19276704697943e-16 + (fConst0 * (4.51777833291617e-17 + (fConst0 * ((fConst0 * (fConst226 - 4.31614729137842e-19)) - 8.75181972411783e-18)))));
	fConst278 = ((fConst0 * ((fConst0 * (8.75181972411783e-18 + (fConst0 * (4.31614729137842e-19 - fConst226)))) - 4.51777833291617e-17)) - 3.19276704697943e-16);
	fConst279 = (3.99095880872428e-14 + (fConst0 * (2.71067542468589e-15 + (fConst0 * ((fConst0 * (fConst230 - 5.21331434491869e-18)) - 2.39621039026005e-16)))));
	fConst280 = ((fConst0 * ((fConst0 * (2.39621039026005e-16 + (fConst0 * (5.21331434491869e-18 - fConst230)))) - 2.71067542468589e-15)) - 3.99095880872428e-14);
	fConst281 = (1.00591664652589e-15 + (fConst0 * ((fConst0 * ((fConst0 * (8.99486083904102e-20 + fConst234)) - 1.003159523147e-17)) - 1.82032088038077e-16)));
	fConst282 = ((fConst0 * (2.60364460288779e-17 + (fConst0 * (1.76838202655138e-18 + (fConst0 * (fConst236 - 1.73756145804592e-20)))))) - 8.50337629539648e-17);
	fConst283 = (1.06558600192938e-20 + (fConst0 * (3.26458198407329e-21 + (fConst0 * (0 - (2.22162891161966e-22 + fConst238))))));
	fConst284 = (2.08017688353901e-22 + fConst240);
	fConst285 = ((fConst0 * ((fConst0 * fConst284) - 3.05672470418848e-21)) - 9.97739702181071e-21);
	fConst286 = (9.97739702181071e-21 + (fConst0 * (3.05672470418848e-21 + (fConst0 * (0 - fConst284)))));
	fConst287 = (7.96196282340494e-17 + (fConst0 * ((fConst0 * ((fConst0 * (1.62693020416284e-20 - fConst243)) - 1.65578841437396e-18)) - 2.43786947835935e-17)));
	fConst288 = ((fConst0 * (2.43786947835935e-17 + (fConst0 * (1.65578841437396e-18 + (fConst0 * (fConst243 - 1.62693020416284e-20)))))) - 7.96196282340494e-17);
	fConst289 = (8.42215434367137e-20 + fConst247);
	fConst290 = (7.98191761744856e-15 + (fConst0 * (9.41869519219001e-16 + (fConst0 * ((fConst0 * ((fConst0 * fConst289) - 9.39287943021533e-18)) - 1.70442029998199e-16)))));
	fConst291 = ((fConst0 * ((fConst0 * (1.70442029998199e-16 + (fConst0 * (9.39287943021533e-18 + (fConst0 * (0 - fConst289)))))) - 9.41869519219001e-16)) - 7.98191761744856e-15);
	fConst292 = (2.13117200385877e-14 + (fConst0 * (4.34250203034679e-15 + (fConst0 * (1.27957634839887e-16 + (fConst0 * (0 - (2.78390986018658e-18 + fConst120))))))));
	fConst293 = ((fConst0 * ((fConst0 * (5.51032162701814e-19 - fConst122)) - 2.55264149017724e-17)) - 8.67924989628316e-16);
	fConst294 = ((fConst0 * ((fConst0 * (3.19433851972335e-21 + fConst124)) - 3.61733701138641e-20)) - 3.19675800578815e-19);
	fConst295 = (2.99095367015295e-21 + fConst126);
	fConst296 = (2.99321910654321e-19 + (fConst0 * (3.38701967358278e-20 + (fConst0 * (0 - fConst295)))));
	fConst297 = ((fConst0 * ((fConst0 * fConst295) - 3.38701967358278e-20)) - 2.99321910654321e-19);
	fConst298 = ((fConst0 * ((fConst0 * ((fConst0 * (5.15947717885593e-19 - fConst129)) - 2.3901137548476e-17)) - 8.12663847966588e-16)) - 3.99095880872428e-15);
	fConst299 = (3.99095880872428e-15 + (fConst0 * (8.12663847966588e-16 + (fConst0 * (2.3901137548476e-17 + (fConst0 * (fConst129 - 5.15947717885593e-19)))))));
	fConst300 = (7.2374808893317e-17 + (fConst0 * (4.67347173267892e-18 + (fConst0 * (0 - (2.30482265359608e-19 + fConst133))))));
	fConst301 = ((fConst0 * ((fConst0 * (4.13018666157306e-20 - fConst135)) - 7.27156620867848e-19)) - 7.50598779759058e-18);
	fConst302 = ((fConst0 * (9.11043413643421e-23 + fConst140)) - 3.13282284567239e-22);
	fConst303 = (8.53036904160507e-23 + fConst137);
	fConst304 = (2.93335472441235e-22 + (fConst0 * (0 - fConst303)));
	fConst305 = ((fConst0 * fConst303) - 2.93335472441235e-22);
	fConst306 = (7.02807846216346e-18 + (fConst0 * (6.80858259239558e-19 + (fConst0 * (fConst142 - 3.86721597525567e-20)))));
	fConst307 = ((fConst0 * ((fConst0 * (3.86721597525567e-20 - fConst142)) - 6.80858259239558e-19)) - 7.02807846216346e-18);
	fConst308 = (2.40396202035269e-18 + (fConst0 * (4.60313050181815e-19 + (fConst0 * ((fConst0 * (0 - (1.10603176686117e-20 + fConst146))) - 7.89937124628652e-20)))));
	fConst309 = ((fConst0 * (1.16152994210155e-20 + (fConst0 * (1.97921291648122e-21 - fConst148)))) - 3.99658685883635e-20);
	fConst310 = (5.0082542090681e-24 + (fConst0 * (4.36928984094294e-24 + fConst150)));
	fConst311 = (4.09109535668814e-24 + fConst152);
	fConst312 = ((fConst0 * (0 - fConst311)) - 4.68937660025103e-24);
	fConst313 = (4.68937660025103e-24 + (fConst0 * fConst311));
	fConst314 = (3.74212252700032e-20 + (fConst0 * ((fConst0 * (fConst155 - 1.85319561468279e-21)) - 1.08757485215501e-20)));
	fConst315 = ((fConst0 * (1.08757485215501e-20 + (fConst0 * (1.85319561468279e-21 - fConst155)))) - 3.74212252700032e-20);
	fConst316 = (1.0356102685966e-20 + fConst159);
	fConst317 = ((fConst0 * ((fConst0 * (7.39641502461285e-20 + (fConst0 * fConst316))) - 4.31004728634658e-19)) - 2.2509007681205e-18);
	fConst318 = (2.2509007681205e-18 + (fConst0 * (4.31004728634658e-19 + (fConst0 * ((fConst0 * (0 - fConst316)) - 7.39641502461285e-20)))));
	fConst319 = (2.15807364568921e-19 + fConst162);
	fConst320 = (1.59638352348971e-16 + (fConst0 * (6.77666749937426e-17 + (fConst0 * (4.37590986205892e-18 + (fConst0 * (0 - fConst319)))))));
	fConst321 = ((fConst0 * ((fConst0 * ((fConst0 * fConst319) - 4.37590986205892e-18)) - 6.77666749937426e-17)) - 1.59638352348971e-16);
	fConst322 = (2.60665717245934e-18 + fConst165);
	fConst323 = (1.99547940436214e-14 + (fConst0 * (4.06601313702883e-15 + (fConst0 * (1.19810519513002e-16 + (fConst0 * (0 - fConst322)))))));
	fConst324 = ((fConst0 * ((fConst0 * ((fConst0 * fConst322) - 1.19810519513002e-16)) - 4.06601313702883e-15)) - 1.99547940436214e-14);
	fConst325 = (1.50887496978884e-15 + (fConst0 * (9.10160440190383e-17 + (fConst0 * ((fConst0 * (0 - (1.34922912585615e-19 + fConst168))) - 5.01579761573499e-18)))));
	fConst326 = ((fConst0 * ((fConst0 * (8.84191013275692e-19 + (fConst0 * (2.60634218706887e-20 - fConst170)))) - 1.30182230144389e-17)) - 1.27550644430947e-16);
	fConst327 = ((fConst0 * (1.63229099203665e-21 + (fConst0 * (3.33244336742949e-22 + fConst172)))) - 5.32793000964692e-21);
	fConst328 = (3.12026532530851e-22 + fConst174);
	fConst329 = (4.98869851090535e-21 + (fConst0 * ((fConst0 * (0 - fConst328)) - 1.52836235209424e-21)));
	fConst330 = ((fConst0 * (1.52836235209424e-21 + (fConst0 * fConst328))) - 4.98869851090535e-21);
	fConst331 = (1.19429442351074e-16 + (fConst0 * (1.21893473917967e-17 + (fConst0 * ((fConst0 * (fConst177 - 2.44039530624426e-20)) - 8.27894207186978e-19)))));
	fConst332 = ((fConst0 * ((fConst0 * (8.27894207186978e-19 + (fConst0 * (2.44039530624426e-20 - fConst177)))) - 1.21893473917967e-17)) - 1.19429442351074e-16);
	fConst333 = (1.26332315155071e-19 + fConst181);
	fConst334 = (3.99095880872428e-15 + (fConst0 * (1.4128042788285e-15 + (fConst0 * (8.52210149990995e-17 + (fConst0 * ((fConst0 * (0 - fConst333)) - 4.69643971510767e-18)))))));
	fConst335 = ((fConst0 * ((fConst0 * ((fConst0 * (4.69643971510767e-18 + (fConst0 * fConst333))) - 8.52210149990995e-17)) - 1.4128042788285e-15)) - 3.99095880872428e-15);
	fConst336 = (3.98030871299959e-21 * fConst0);
	fConst337 = (fConst0 * (3.04019770269112e-17 + (fConst0 * (fConst336 - 1.3696810896962e-17))));
	fConst338 = (1.49388607866623e-19 * fConst0);
	fConst339 = (1.90022438253841e-15 + (fConst0 * (2.85365632064909e-16 - fConst338)));
	fConst340 = (1.06706148476159e-18 * fConst0);
	fConst341 = (8.06546851671652e-17 + (fConst0 * (1.44694505189894e-17 - fConst340)));
	fConst342 = ((fConst0 * (fConst340 - 1.44694505189894e-17)) - 8.06546851671652e-17);
	fConst343 = (2.84307765214256e-20 * fConst0);
	fConst344 = (fConst77 * (1.13723106085703e-19 - fConst343));
	fConst345 = (3.23425287520332e-14 + (fConst0 * (4.85778329480724e-15 + (fConst0 * (fConst343 - 2.99551500710851e-18)))));
	fConst346 = (7.96061742599918e-21 * fConst0);
	fConst347 = (fConst0 * (6.08039540538225e-17 + (fConst0 * (9.13120726464134e-18 - fConst346))));
	fConst348 = (9.95924052444153e-20 * fConst0);
	fConst349 = ((fConst0 * (5.70731264129818e-16 + fConst348)) - 3.80044876507682e-15);
	fConst350 = (7.11374323174395e-19 * fConst0);
	fConst351 = (2.89389010379788e-17 + fConst350);
	fConst352 = ((fConst0 * fConst351) - 1.6130937033433e-16);
	fConst353 = (1.6130937033433e-16 + (fConst0 * (0 - fConst351)));
	fConst354 = (5.68615530428513e-20 * fConst0);
	fConst355 = (fConst77 * (fConst354 - 7.58154040571353e-20));
	fConst356 = ((fConst0 * (9.71556658961449e-15 + (fConst0 * (1.997010004739e-18 - fConst354)))) - 6.46850575040665e-14);
	fConst357 = (fConst0 * ((fConst0 * (9.13120726464134e-18 + fConst346)) - 6.08039540538225e-17));
	fConst358 = ((fConst0 * (fConst348 - 5.70731264129818e-16)) - 3.80044876507682e-15);
	fConst359 = (1.6130937033433e-16 + (fConst0 * (2.89389010379788e-17 - fConst350)));
	fConst360 = (fConst77 * (0 - (7.58154040571353e-20 + fConst354)));
	fConst361 = ((fConst0 * ((fConst0 * (1.997010004739e-18 + fConst354)) - 9.71556658961449e-15)) - 6.46850575040665e-14);
	fConst362 = ((fConst0 * (fConst350 - 2.89389010379788e-17)) - 1.6130937033433e-16);
	fConst363 = (fConst0 * ((fConst0 * (0 - (1.3696810896962e-17 + fConst336))) - 3.04019770269112e-17));
	fConst364 = (1.90022438253841e-15 + (fConst0 * (0 - (2.85365632064909e-16 + fConst338))));
	fConst365 = (1.44694505189894e-17 + fConst340);
	fConst366 = (8.06546851671652e-17 + (fConst0 * (0 - fConst365)));
	fConst367 = ((fConst0 * fConst365) - 8.06546851671652e-17);
	fConst368 = (fConst77 * (1.13723106085703e-19 + fConst343));
	fConst369 = (3.23425287520332e-14 + (fConst0 * ((fConst0 * (0 - (2.99551500710851e-18 + fConst343))) - 4.85778329480724e-15)));
	fConst370 = (fConst0 * (3.04019770269112e-17 + (fConst0 * (4.56560363232067e-18 + fConst69))));
	fConst371 = (1.90022438253841e-15 + (fConst0 * (2.85365632064909e-16 + fConst71)));
	fConst372 = (1.44694505189894e-17 + fConst73);
	fConst373 = (8.06546851671652e-17 + (fConst0 * fConst372));
	fConst374 = ((fConst0 * (0 - fConst372)) - 8.06546851671652e-17);
	fConst375 = (fConst77 * (0 - (3.79077020285676e-20 + fConst76)));
	fConst376 = (3.23425287520332e-14 + (fConst0 * (4.85778329480724e-15 + (fConst0 * (9.98505002369502e-19 + fConst76)))));
	fConst377 = (0.1 * fConst77);
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
		fRec0[0] = ((0.993 * fRec0[1]) + fSlow0);
		fRec1[0] = ((0.993 * fRec1[1]) + fSlow1);
		fRec2[0] = ((0.993 * fRec2[1]) + fSlow2);
		fRec3[0] = ((0.993 * fRec3[1]) + fSlow3);
		double fTemp0 = (((((fRec2[0] * (8.52468801543507e-16 + ((fRec0[0] * ((fConst68 * fRec0[0]) + fConst67)) + (fConst0 * ((fRec1[0] * (fConst64 + ((fRec0[0] * (fConst62 + (fConst61 * fRec0[0]))) + (fConst0 * (fRec1[0] * ((fRec0[0] * (fConst59 + (fConst58 * fRec0[0]))) + fConst55)))))) + fConst53))))) + (fRec0[0] * ((fConst51 * fRec0[0]) + fConst50))) + (fRec3[0] * (3.40987520617403e-17 + ((fRec0[0] * ((fConst47 * fRec0[0]) + fConst46)) + (fConst0 * (((fRec2[0] * (((fRec0[0] * (fConst43 + (fConst42 * fRec0[0]))) + (fConst0 * (fRec1[0] * (fConst39 + ((fRec0[0] * (fConst37 + (fConst36 * fRec0[0]))) + (fConst0 * (fRec1[0] * ((fRec0[0] * (fConst34 + (fConst33 * fRec0[0]))) + fConst30)))))))) + fConst28)) + (fRec1[0] * (fConst26 + ((fRec0[0] * (fConst24 + (fConst23 * fRec0[0]))) + (fConst0 * (fRec1[0] * ((fRec0[0] * (fConst21 + (fConst20 * fRec0[0]))) + fConst17))))))) + fConst15)))))) + (fRec1[0] * (((fRec0[0] * ((fConst13 * fRec0[0]) + fConst12)) + (fConst0 * (fConst10 + (fRec1[0] * ((fRec0[0] * (fConst8 + (fConst7 * fRec0[0]))) + fConst4))))) - 8.52468801543507e-16))) + fConst2);
		fRec4[0] = ((double)input0[i] - ((((((fRec4[1] * (((((fRec2[0] * (4.26234400771753e-15 + ((fRec0[0] * ((fConst335 * fRec0[0]) + fConst334)) + (fConst0 * ((fRec1[0] * (((fRec0[0] * (fConst332 + (fConst331 * fRec0[0]))) + (fConst0 * (fRec1[0] * ((fRec0[0] * (fConst330 + (fConst329 * fRec0[0]))) + fConst327)))) + fConst326)) + fConst325))))) + (fRec0[0] * ((fConst324 * fRec0[0]) + fConst323))) + (fRec3[0] * (1.70493760308701e-16 + ((fRec0[0] * ((fConst321 * fRec0[0]) + fConst320)) + (fConst0 * (((fRec2[0] * (((fRec0[0] * (fConst318 + (fConst317 * fRec0[0]))) + (fConst0 * (fRec1[0] * (((fRec0[0] * (fConst315 + (fConst314 * fRec0[0]))) + (fConst0 * (fRec1[0] * ((fRec0[0] * (fConst313 + (fConst312 * fRec0[0]))) + fConst310)))) + fConst309)))) + fConst308)) + (fRec1[0] * (((fRec0[0] * (fConst307 + (fConst306 * fRec0[0]))) + (fConst0 * (fRec1[0] * ((fRec0[0] * (fConst305 + (fConst304 * fRec0[0]))) + fConst302)))) + fConst301))) + fConst300)))))) + (fRec1[0] * (((fRec0[0] * ((fConst299 * fRec0[0]) + fConst298)) + (fConst0 * ((fRec1[0] * ((fRec0[0] * (fConst297 + (fConst296 * fRec0[0]))) + fConst294)) + fConst293))) - 4.26234400771753e-15))) + fConst292)) + (fRec4[2] * (((((fRec2[0] * (8.52468801543507e-15 + ((fRec0[0] * ((fConst291 * fRec0[0]) + fConst290)) + (fConst0 * ((fRec1[0] * (((fRec0[0] * (fConst288 + (fConst287 * fRec0[0]))) + (fConst0 * (fRec1[0] * ((fRec0[0] * (fConst286 + (fConst285 * fRec0[0]))) + fConst283)))) + fConst282)) + fConst281))))) + (fRec0[0] * ((fConst280 * fRec0[0]) + fConst279))) + (fRec3[0] * (3.40987520617403e-16 + ((fRec0[0] * ((fConst278 * fRec0[0]) + fConst277)) + (fConst0 * (((fRec2[0] * (((fRec0[0] * (fConst276 + (fConst275 * fRec0[0]))) + (fConst0 * (fRec1[0] * (((fRec0[0] * (fConst273 + (fConst272 * fRec0[0]))) + (fConst0 * (fRec1[0] * ((fRec0[0] * (fConst271 + (fConst270 * fRec0[0]))) + fConst268)))) + fConst267)))) + fConst266)) + (fRec1[0] * (((fRec0[0] * (fConst265 + (fConst264 * fRec0[0]))) + (fConst0 * (fRec1[0] * ((fRec0[0] * (fConst262 + (fConst261 * fRec0[0]))) + fConst260)))) + fConst259))) + fConst258)))))) + (fRec1[0] * (((fRec0[0] * ((fConst257 * fRec0[0]) + fConst256)) + (fConst0 * ((fRec1[0] * ((fRec0[0] * (fConst254 + (fConst253 * fRec0[0]))) + fConst252)) + fConst251))) - 8.52468801543507e-15))) + fConst250))) + (fRec4[3] * (((((fRec2[0] * (8.52468801543507e-15 + ((fRec0[0] * ((fConst249 * fRec0[0]) + fConst248)) + (fConst0 * ((fRec1[0] * (((fRec0[0] * (fConst246 + (fConst245 * fRec0[0]))) + (fConst0 * (fRec1[0] * ((fRec0[0] * (fConst242 + (fConst241 * fRec0[0]))) + fConst239)))) + fConst237)) + fConst235))))) + (fRec0[0] * ((fConst233 * fRec0[0]) + fConst232))) + (fRec3[0] * (3.40987520617403e-16 + ((fRec0[0] * ((fConst229 * fRec0[0]) + fConst228)) + (fConst0 * (((fRec2[0] * (((fRec0[0] * (fConst225 + (fConst224 * fRec0[0]))) + (fConst0 * (fRec1[0] * (((fRec0[0] * (fConst222 + (fConst221 * fRec0[0]))) + (fConst0 * (fRec1[0] * (fConst218 + (fRec0[0] * (fConst216 + (fConst215 * fRec0[0]))))))) + fConst213)))) + fConst211)) + (fRec1[0] * (((fRec0[0] * (fConst209 + (fConst208 * fRec0[0]))) + (fConst0 * (fRec1[0] * ((fRec0[0] * (fConst206 + (fConst205 * fRec0[0]))) + fConst202)))) + fConst200))) + fConst198)))))) + (fRec1[0] * (((fRec0[0] * ((fConst196 * fRec0[0]) + fConst195)) + (fConst0 * ((fRec1[0] * ((fRec0[0] * (fConst193 + (fConst192 * fRec0[0]))) + fConst189)) + fConst187))) - 8.52468801543507e-15))) + fConst185))) + (fRec4[4] * (((((fRec2[0] * (4.26234400771753e-15 + ((fRec0[0] * ((fConst183 * fRec0[0]) + fConst182)) + (fConst0 * ((fRec1[0] * (((fRec0[0] * (fConst180 + (fConst179 * fRec0[0]))) + (fConst0 * (fRec1[0] * ((fRec0[0] * (fConst176 + (fConst175 * fRec0[0]))) + fConst173)))) + fConst171)) + fConst169))))) + (fRec0[0] * ((fConst167 * fRec0[0]) + fConst166))) + (fRec3[0] * (1.70493760308701e-16 + ((fRec0[0] * ((fConst164 * fRec0[0]) + fConst163)) + (fConst0 * (((fRec2[0] * (((fRec0[0] * (fConst161 + (fConst160 * fRec0[0]))) + (fConst0 * (fRec1[0] * (((fRec0[0] * (fConst158 + (fConst157 * fRec0[0]))) + (fConst0 * (fRec1[0] * ((fRec0[0] * (fConst154 + (fConst153 * fRec0[0]))) + fConst151)))) + fConst149)))) + fConst147)) + (fRec1[0] * (((fRec0[0] * (fConst145 + (fConst144 * fRec0[0]))) + (fConst0 * (fRec1[0] * (fConst141 + (fRec0[0] * (fConst139 + (fConst138 * fRec0[0]))))))) + fConst136))) + fConst134)))))) + (fRec1[0] * (((fRec0[0] * ((fConst132 * fRec0[0]) + fConst131)) + (fConst0 * ((fRec1[0] * ((fRec0[0] * (fConst128 + (fConst127 * fRec0[0]))) + fConst125)) + fConst123))) - 4.26234400771753e-15))) + fConst121))) + (fRec4[5] * (((((fRec2[0] * (8.52468801543507e-16 + ((fRec0[0] * ((fConst119 * fRec0[0]) + fConst118)) + (fConst0 * ((fRec1[0] * (((fRec0[0] * (fConst117 + (fConst116 * fRec0[0]))) + (fConst0 * (fRec1[0] * ((fRec0[0] * (fConst114 + (fConst113 * fRec0[0]))) + fConst112)))) + fConst111)) + fConst110))))) + (fRec0[0] * ((fConst109 * fRec0[0]) + fConst108))) + (fRec3[0] * (3.40987520617403e-17 + ((fRec0[0] * ((fConst107 * fRec0[0]) + fConst106)) + (fConst0 * (((fRec2[0] * (((fRec0[0] * (fConst105 + (fConst104 * fRec0[0]))) + (fConst0 * (fRec1[0] * (((fRec0[0] * (fConst103 + (fConst102 * fRec0[0]))) + (fConst0 * (fRec1[0] * ((fRec0[0] * (fConst100 + (fConst99 * fRec0[0]))) + fConst98)))) + fConst97)))) + fConst96)) + (fRec1[0] * (((fRec0[0] * (fConst95 + (fConst94 * fRec0[0]))) + (fConst0 * (fRec1[0] * ((fRec0[0] * (fConst92 + (fConst91 * fRec0[0]))) + fConst90)))) + fConst89))) + fConst88)))))) + (fRec1[0] * (((fRec0[0] * ((fConst87 * fRec0[0]) + fConst86)) + (fConst0 * ((fRec1[0] * ((fRec0[0] * (fConst84 + (fConst83 * fRec0[0]))) + fConst82)) + fConst81))) - 8.52468801543507e-16))) + fConst80))) / fTemp0));
		fRec5[0] = ((0.993 * fRec5[1]) + fSlow4);
		output0[i] = (FAUSTFLOAT)(fConst377 * (((fRec0[0] * fRec5[0]) * ((((((fRec4[0] * ((((fRec2[0] * (fConst376 + (fConst375 * fRec1[0]))) + (fConst374 * fRec1[0])) + fConst373) + (fRec3[0] * (fConst371 + (fConst370 * fRec2[0]))))) + (fRec4[1] * ((((fRec2[0] * (fConst369 + (fConst368 * fRec1[0]))) + (fConst367 * fRec1[0])) + fConst366) + (fRec3[0] * (fConst364 + (fConst363 * fRec2[0])))))) + (fRec4[2] * ((fConst362 + ((fRec2[0] * (fConst361 + (fConst360 * fRec1[0]))) + (fConst359 * fRec1[0]))) + (fRec3[0] * (fConst358 + (fConst357 * fRec2[0])))))) + (fRec4[3] * ((((fRec2[0] * (fConst356 + (fConst355 * fRec1[0]))) + (fConst353 * fRec1[0])) + fConst352) + (fRec3[0] * (fConst349 + (fConst347 * fRec2[0])))))) + (fRec4[4] * ((((fRec2[0] * (fConst345 + (fConst344 * fRec1[0]))) + (fConst342 * fRec1[0])) + fConst341) + (fRec3[0] * (fConst339 + (fConst337 * fRec2[0])))))) + (fRec4[5] * ((((fRec2[0] * (fConst79 + (fConst78 * fRec1[0]))) + (fConst75 * fRec1[0])) + fConst74) + (fRec3[0] * (fConst72 + (fConst70 * fRec2[0]))))))) / fTemp0));
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
