// generated from file '../src/LV2/faust/gxtilttone.dsp' by dsp2cc:
// Code generated with Faust 0.9.73 (http://faust.grame.fr)


namespace gxtilttone {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	double 	fConst0;
	double 	fConst1;
	double 	fConst2;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec0[2];
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
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec1[2];
	double 	fConst13;
	double 	fConst14;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec2[2];
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
	double 	fRec3[6];
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
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fRec4[2];
	double 	fConst125;
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
	id = "tiltdrive";
	name = N_("Tilt Tone Pro");
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
	for (int i=0; i<6; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = double(min(192000, max(1, fSamplingFreq)));
	fConst1 = (2.28122296333533e-24 * fConst0);
	fConst2 = (8.10365204511649e-14 + (fConst0 * (2.10762961057232e-14 + (fConst0 * (8.74821708374195e-16 + (fConst0 * (7.96263953610201e-18 + (fConst0 * (8.79069607151715e-21 + fConst1)))))))));
	fConst3 = (2.18640566240203e-25 * fConst0);
	fConst4 = ((fConst0 * ((fConst0 * ((fConst0 * (0 - (7.4373965003245e-22 + fConst3))) - 5.10322864018117e-19)) - 1.60195443528707e-17)) - 6.45008484054134e-17);
	fConst5 = (2.28122296333533e-25 * fConst0);
	fConst6 = ((fConst0 * ((fConst0 * (2.91513197131548e-19 + (fConst0 * (6.7333505453927e-22 + fConst5)))) - 4.73548057740805e-17)) - 1.77838894830509e-15);
	fConst7 = (2.62525390732477e-24 * fConst0);
	fConst8 = (1.83241046606283e-15 + (fConst0 * (5.83051240035225e-16 + (fConst0 * (4.65427400362912e-17 + (fConst0 * (1.1019944255992e-18 + (fConst0 * (4.06350352538518e-21 + fConst7)))))))));
	fConst9 = (2.20196238530113e-25 * fConst0);
	fConst10 = (4.29052522779372e-32 + (fConst0 * ((fConst0 * ((fConst0 * (0 - (2.17931503100737e-22 + fConst9))) - 6.97015807574444e-21)) - 2.81458247587152e-20)));
	fConst11 = (2.62525390732477e-25 * fConst0);
	fConst12 = (1.17274269828036e-17 + (fConst0 * (2.92826202944812e-18 + (fConst0 * (9.67716852364725e-20 + (fConst0 * (2.81564132170152e-22 + fConst11)))))));
	fConst13 = (1.04204943391911e-18 * fConst0);
	fConst14 = (8.92471252071873e-14 + (fConst0 * (fConst13 - 5.90609889146098e-15)));
	fConst15 = (5.84747164357487e-22 * fConst0);
	fConst16 = (8.45143231128667e-14 + (fConst0 * ((fConst0 * (fConst15 - 8.85980552056803e-21)) - 5.57794532544917e-15)));
	fConst17 = ((fConst0 * (5.57794532544917e-15 + (fConst0 * (8.85980552056803e-21 - fConst15)))) - 8.45143231128667e-14);
	fConst18 = ((fConst0 * (5.90609889146098e-15 - fConst13)) - 8.92471252071873e-14);
	fConst19 = (4.65200640142461e-18 * fConst0);
	fConst20 = (2.11285807782166e-14 + (fConst0 * (fConst19 - 1.46497127683842e-15)));
	fConst21 = ((fConst0 * (1.46497127683842e-15 - fConst19)) - 2.11285807782166e-14);
	fConst22 = (2.61047841231021e-21 * fConst0);
	fConst23 = ((fConst0 * (3.71038765066618e-30 + (fConst0 * (fConst22 - 3.95527032168216e-20)))) - 5.62179947070636e-29);
	fConst24 = (5.62179947070636e-29 + (fConst0 * ((fConst0 * (3.95527032168216e-20 - fConst22)) - 3.71038765066618e-30)));
	fConst25 = (8.10365204511649e-14 + (fConst0 * ((fConst0 * (8.74821708374195e-16 + (fConst0 * ((fConst0 * (8.79069607151715e-21 - fConst1)) - 7.96263953610201e-18)))) - 2.10762961057232e-14)));
	fConst26 = (6.45008484054134e-17 + (fConst0 * ((fConst0 * (5.10322864018117e-19 + (fConst0 * (fConst3 - 7.4373965003245e-22)))) - 1.60195443528707e-17)));
	fConst27 = (1.77838894830509e-15 + (fConst0 * ((fConst0 * ((fConst0 * (6.7333505453927e-22 - fConst5)) - 2.91513197131548e-19)) - 4.73548057740805e-17)));
	fConst28 = (1.83241046606283e-15 + (fConst0 * ((fConst0 * (4.65427400362912e-17 + (fConst0 * ((fConst0 * (4.06350352538518e-21 - fConst7)) - 1.1019944255992e-18)))) - 5.83051240035225e-16)));
	fConst29 = ((fConst0 * ((fConst0 * (6.97015807574444e-21 + (fConst0 * (fConst9 - 2.17931503100737e-22)))) - 2.81458247587152e-20)) - 4.29052522779372e-32);
	fConst30 = ((fConst0 * (2.92826202944812e-18 + (fConst0 * ((fConst0 * (2.81564132170152e-22 - fConst11)) - 9.67716852364725e-20)))) - 1.17274269828036e-17);
	fConst31 = (1.14061148166766e-23 * fConst0);
	fConst32 = (4.05182602255824e-13 + (fConst0 * ((fConst0 * (8.74821708374195e-16 + (fConst0 * (7.96263953610201e-18 + (fConst0 * (fConst31 - 2.63720882145514e-20)))))) - 6.32288883171697e-14)));
	fConst33 = (1.09320283120102e-24 * fConst0);
	fConst34 = (1.9350254521624e-16 + (fConst0 * ((fConst0 * ((fConst0 * (2.23121895009735e-21 - fConst33)) - 5.10322864018117e-19)) - 1.60195443528707e-17)));
	fConst35 = (1.14061148166766e-24 * fConst0);
	fConst36 = (5.33516684491528e-15 + (fConst0 * ((fConst0 * (2.91513197131548e-19 + (fConst0 * (fConst35 - 2.02000516361781e-21)))) - 4.73548057740805e-17)));
	fConst37 = (1.31262695366239e-23 * fConst0);
	fConst38 = (9.16205233031414e-15 + (fConst0 * ((fConst0 * (4.65427400362912e-17 + (fConst0 * (1.1019944255992e-18 + (fConst0 * (fConst37 - 1.21905105761555e-20)))))) - 1.74915372010567e-15)));
	fConst39 = (1.10098119265056e-24 * fConst0);
	fConst40 = ((fConst0 * ((fConst0 * ((fConst0 * (6.53794509302211e-22 - fConst39)) - 6.97015807574444e-21)) - 2.81458247587152e-20)) - 1.28715756833812e-31);
	fConst41 = (1.31262695366239e-24 * fConst0);
	fConst42 = ((fConst0 * (2.92826202944812e-18 + (fConst0 * (9.67716852364725e-20 + (fConst0 * (fConst41 - 8.44692396510456e-22)))))) - 3.51822809484109e-17);
	fConst43 = (2.28122296333533e-23 * fConst0);
	fConst44 = (8.10365204511649e-13 + (fConst0 * ((fConst0 * ((fConst0 * (1.5925279072204e-17 + (fConst0 * (1.75813921430343e-20 - fConst43)))) - 1.74964341674839e-15)) - 4.21525922114464e-14)));
	fConst45 = (2.18640566240203e-24 * fConst0);
	fConst46 = (1.29001696810827e-16 + (fConst0 * (3.20390887057414e-17 + (fConst0 * ((fConst0 * (fConst45 - 1.4874793000649e-21)) - 1.02064572803623e-18)))));
	fConst47 = (3.55677789661019e-15 + (fConst0 * (9.4709611548161e-17 + (fConst0 * (5.83026394263095e-19 + (fConst0 * (1.34667010907854e-21 - fConst1)))))));
	fConst48 = (2.62525390732477e-23 * fConst0);
	fConst49 = (1.83241046606283e-14 + (fConst0 * ((fConst0 * ((fConst0 * (2.2039888511984e-18 + (fConst0 * (8.12700705077035e-21 - fConst48)))) - 9.30854800725824e-17)) - 1.16610248007045e-15)));
	fConst50 = (2.20196238530113e-24 * fConst0);
	fConst51 = ((fConst0 * (5.62916495174304e-20 + (fConst0 * ((fConst0 * (fConst50 - 4.35863006201474e-22)) - 1.39403161514889e-20)))) - 8.58105045558744e-32);
	fConst52 = ((fConst0 * ((fConst0 * (1.93543370472945e-19 + (fConst0 * (5.63128264340304e-22 - fConst7)))) - 5.85652405889624e-18)) - 2.34548539656073e-17);
	fConst53 = (8.10365204511649e-13 + (fConst0 * (4.21525922114464e-14 + (fConst0 * ((fConst0 * ((fConst0 * (1.75813921430343e-20 + fConst43)) - 1.5925279072204e-17)) - 1.74964341674839e-15)))));
	fConst54 = ((fConst0 * (3.20390887057414e-17 + (fConst0 * (1.02064572803623e-18 + (fConst0 * (0 - (1.4874793000649e-21 + fConst45))))))) - 1.29001696810827e-16);
	fConst55 = ((fConst0 * (9.4709611548161e-17 + (fConst0 * ((fConst0 * (1.34667010907854e-21 + fConst1)) - 5.83026394263095e-19)))) - 3.55677789661019e-15);
	fConst56 = (1.83241046606283e-14 + (fConst0 * (1.16610248007045e-15 + (fConst0 * ((fConst0 * ((fConst0 * (8.12700705077035e-21 + fConst48)) - 2.2039888511984e-18)) - 9.30854800725824e-17)))));
	fConst57 = (8.58105045558744e-32 + (fConst0 * (5.62916495174304e-20 + (fConst0 * (1.39403161514889e-20 + (fConst0 * (0 - (4.35863006201474e-22 + fConst50))))))));
	fConst58 = (2.34548539656073e-17 + (fConst0 * ((fConst0 * ((fConst0 * (5.63128264340304e-22 + fConst7)) - 1.93543370472945e-19)) - 5.85652405889624e-18)));
	fConst59 = (4.05182602255824e-13 + (fConst0 * (6.32288883171697e-14 + (fConst0 * (8.74821708374195e-16 + (fConst0 * ((fConst0 * (0 - (2.63720882145514e-20 + fConst31))) - 7.96263953610201e-18)))))));
	fConst60 = ((fConst0 * ((fConst0 * (5.10322864018117e-19 + (fConst0 * (2.23121895009735e-21 + fConst33)))) - 1.60195443528707e-17)) - 1.9350254521624e-16);
	fConst61 = ((fConst0 * ((fConst0 * ((fConst0 * (0 - (2.02000516361781e-21 + fConst35))) - 2.91513197131548e-19)) - 4.73548057740805e-17)) - 5.33516684491528e-15);
	fConst62 = (9.16205233031414e-15 + (fConst0 * (1.74915372010567e-15 + (fConst0 * (4.65427400362912e-17 + (fConst0 * ((fConst0 * (0 - (1.21905105761555e-20 + fConst37))) - 1.1019944255992e-18)))))));
	fConst63 = (1.28715756833812e-31 + (fConst0 * ((fConst0 * (6.97015807574444e-21 + (fConst0 * (6.53794509302211e-22 + fConst39)))) - 2.81458247587152e-20)));
	fConst64 = (3.51822809484109e-17 + (fConst0 * (2.92826202944812e-18 + (fConst0 * ((fConst0 * (0 - (8.44692396510456e-22 + fConst41))) - 9.67716852364725e-20)))));
	fConst65 = (3.12614830175733e-18 * fConst0);
	fConst66 = (8.92471252071873e-14 + (fConst0 * (5.90609889146098e-15 - fConst65)));
	fConst67 = (2.92373582178743e-21 * fConst0);
	fConst68 = (8.45143231128667e-14 + (fConst0 * (5.57794532544917e-15 + (fConst0 * (2.65794165617041e-20 - fConst67)))));
	fConst69 = ((fConst0 * ((fConst0 * (fConst67 - 2.65794165617041e-20)) - 5.57794532544917e-15)) - 8.45143231128667e-14);
	fConst70 = ((fConst0 * (fConst65 - 5.90609889146098e-15)) - 8.92471252071873e-14);
	fConst71 = (1.39560192042738e-17 * fConst0);
	fConst72 = (2.11285807782166e-14 + (fConst0 * (1.46497127683842e-15 - fConst71)));
	fConst73 = ((fConst0 * (fConst71 - 1.46497127683842e-15)) - 2.11285807782166e-14);
	fConst74 = (1.30523920615511e-20 * fConst0);
	fConst75 = ((fConst0 * ((fConst0 * (1.18658109650465e-19 - fConst74)) - 3.71038765066618e-30)) - 5.62179947070636e-29);
	fConst76 = (5.62179947070636e-29 + (fConst0 * (3.71038765066618e-30 + (fConst0 * (fConst74 - 1.18658109650465e-19)))));
	fConst77 = (2.08409886783822e-18 * fConst0);
	fConst78 = (1.1812197782922e-14 + fConst77);
	fConst79 = ((fConst0 * fConst78) - 1.78494250414375e-13);
	fConst80 = (5.84747164357486e-21 * fConst0);
	fConst81 = ((fConst0 * (1.11558906508983e-14 + (fConst0 * (fConst80 - 1.77196110411361e-20)))) - 1.69028646225733e-13);
	fConst82 = (1.69028646225733e-13 + (fConst0 * ((fConst0 * (1.77196110411361e-20 - fConst80)) - 1.11558906508983e-14)));
	fConst83 = (1.78494250414375e-13 + (fConst0 * (0 - fConst78)));
	fConst84 = (9.30401280284922e-18 * fConst0);
	fConst85 = (2.92994255367684e-15 + fConst84);
	fConst86 = ((fConst0 * fConst85) - 4.22571615564333e-14);
	fConst87 = (4.22571615564333e-14 + (fConst0 * (0 - fConst85)));
	fConst88 = (2.61047841231021e-20 * fConst0);
	fConst89 = (1.12435989414127e-28 + (fConst0 * ((fConst0 * (fConst88 - 7.91054064336433e-20)) - 7.42077530133235e-30)));
	fConst90 = ((fConst0 * (7.42077530133235e-30 + (fConst0 * (7.91054064336433e-20 - fConst88)))) - 1.12435989414127e-28);
	fConst91 = (1.77196110411361e-20 + fConst80);
	fConst92 = ((fConst0 * ((fConst0 * (0 - fConst91)) - 1.11558906508983e-14)) - 1.69028646225733e-13);
	fConst93 = (1.69028646225733e-13 + (fConst0 * (1.11558906508983e-14 + (fConst0 * fConst91))));
	fConst94 = (1.78494250414375e-13 + (fConst0 * (1.1812197782922e-14 - fConst77)));
	fConst95 = (4.22571615564333e-14 + (fConst0 * (2.92994255367684e-15 - fConst84)));
	fConst96 = (7.91054064336433e-20 + fConst88);
	fConst97 = (1.12435989414127e-28 + (fConst0 * (7.42077530133235e-30 + (fConst0 * (0 - fConst96)))));
	fConst98 = ((fConst0 * ((fConst0 * fConst96) - 7.42077530133235e-30)) - 1.12435989414127e-28);
	fConst99 = ((fConst0 * (fConst84 - 2.92994255367684e-15)) - 4.22571615564333e-14);
	fConst100 = ((fConst0 * (fConst77 - 1.1812197782922e-14)) - 1.78494250414375e-13);
	fConst101 = (5.90609889146098e-15 + fConst65);
	fConst102 = (8.92471252071873e-14 + (fConst0 * (0 - fConst101)));
	fConst103 = (2.65794165617041e-20 + fConst67);
	fConst104 = (8.45143231128667e-14 + (fConst0 * ((fConst0 * fConst103) - 5.57794532544917e-15)));
	fConst105 = ((fConst0 * (5.57794532544917e-15 + (fConst0 * (0 - fConst103)))) - 8.45143231128667e-14);
	fConst106 = ((fConst0 * fConst101) - 8.92471252071873e-14);
	fConst107 = (1.46497127683842e-15 + fConst71);
	fConst108 = (2.11285807782166e-14 + (fConst0 * (0 - fConst107)));
	fConst109 = ((fConst0 * fConst107) - 2.11285807782166e-14);
	fConst110 = (1.18658109650465e-19 + fConst74);
	fConst111 = ((fConst0 * (3.71038765066618e-30 + (fConst0 * fConst110))) - 5.62179947070636e-29);
	fConst112 = (5.62179947070636e-29 + (fConst0 * ((fConst0 * (0 - fConst110)) - 3.71038765066618e-30)));
	fConst113 = (5.90609889146098e-15 + fConst13);
	fConst114 = (8.92471252071873e-14 + (fConst0 * fConst113));
	fConst115 = (8.85980552056803e-21 + fConst15);
	fConst116 = (8.45143231128667e-14 + (fConst0 * (5.57794532544917e-15 + (fConst0 * (0 - fConst115)))));
	fConst117 = ((fConst0 * ((fConst0 * fConst115) - 5.57794532544917e-15)) - 8.45143231128667e-14);
	fConst118 = ((fConst0 * (0 - fConst113)) - 8.92471252071873e-14);
	fConst119 = (1.46497127683842e-15 + fConst19);
	fConst120 = (2.11285807782166e-14 + (fConst0 * fConst119));
	fConst121 = ((fConst0 * (0 - fConst119)) - 2.11285807782166e-14);
	fConst122 = (3.95527032168216e-20 + fConst22);
	fConst123 = ((fConst0 * ((fConst0 * (0 - fConst122)) - 3.71038765066618e-30)) - 5.62179947070636e-29);
	fConst124 = (5.62179947070636e-29 + (fConst0 * (3.71038765066618e-30 + (fConst0 * fConst122))));
	fConst125 = (0.1 * faustpower<2>(fConst0));
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
	double 	fSlow0 = (0.004073836948085289 * (exp(double(fslider0)) - 1));
	double 	fSlow1 = (0.007000000000000006 * double(fslider1));
	double 	fSlow2 = (0.004073836948085289 * (exp((1 - double(fslider2))) - 1));
	double 	fSlow3 = (0.004073836948085289 * (exp(double(fslider3)) - 1));
	for (int i=0; i<count; i++) {
		fRec0[0] = ((0.993 * fRec0[1]) + fSlow0);
		fRec1[0] = ((0.993 * fRec1[1]) + fSlow1);
		double fTemp0 = (((fRec1[0] * ((fRec0[0] * (4.87559684976559e-30 + (fConst0 * (fConst12 + (fConst10 * fRec0[0]))))) + fConst8)) + (fRec0[0] * ((fConst0 * (fConst6 + (fConst4 * fRec0[0]))) - 7.32964186425153e-15))) + fConst2);
		fRec2[0] = ((0.993 * fRec2[1]) + fSlow2);
		fRec3[0] = ((double)input0[i] - ((((((fRec3[1] * (((fRec1[0] * ((fRec0[0] * (2.43779842488279e-29 + (fConst0 * (fConst64 + (fConst63 * fRec0[0]))))) + fConst62)) + (fRec0[0] * ((fConst0 * (fConst61 + (fConst60 * fRec0[0]))) - 3.66482093212576e-14))) + fConst59)) + (fRec3[2] * (((fRec1[0] * ((fRec0[0] * (4.87559684976559e-29 + (fConst0 * (fConst58 + (fConst57 * fRec0[0]))))) + fConst56)) + (fRec0[0] * ((fConst0 * (fConst55 + (fConst54 * fRec0[0]))) - 7.32964186425153e-14))) + fConst53))) + (fRec3[3] * (((fRec1[0] * ((fRec0[0] * (4.87559684976559e-29 + (fConst0 * (fConst52 + (fConst51 * fRec0[0]))))) + fConst49)) + (fRec0[0] * ((fConst0 * (fConst47 + (fConst46 * fRec0[0]))) - 7.32964186425153e-14))) + fConst44))) + (fRec3[4] * (((fRec1[0] * ((fRec0[0] * (2.43779842488279e-29 + (fConst0 * (fConst42 + (fConst40 * fRec0[0]))))) + fConst38)) + (fRec0[0] * ((fConst0 * (fConst36 + (fConst34 * fRec0[0]))) - 3.66482093212576e-14))) + fConst32))) + (fRec3[5] * (((fRec1[0] * ((fRec0[0] * (4.87559684976559e-30 + (fConst0 * (fConst30 + (fConst29 * fRec0[0]))))) + fConst28)) + (fRec0[0] * ((fConst0 * (fConst27 + (fConst26 * fRec0[0]))) - 7.32964186425153e-15))) + fConst25))) / fTemp0));
		fRec4[0] = ((0.993 * fRec4[1]) + fSlow3);
		output0[i] = (FAUSTFLOAT)(fConst125 * ((fRec4[0] * ((((((fRec3[0] * ((((fRec1[0] * (((fRec0[0] * (fConst124 + (fConst123 * fRec2[0]))) + (fConst121 * fRec2[0])) + fConst120)) + (fConst118 * fRec2[0])) + (fRec0[0] * (fConst117 + (fConst116 * fRec2[0])))) + fConst114)) + (fRec3[1] * ((((fRec1[0] * (((fRec0[0] * (fConst112 + (fConst111 * fRec2[0]))) + (fConst109 * fRec2[0])) + fConst108)) + (fConst106 * fRec2[0])) + (fRec0[0] * (fConst105 + (fConst104 * fRec2[0])))) + fConst102))) + (fRec3[2] * (fConst100 + (((fRec1[0] * (fConst99 + ((fRec0[0] * (fConst98 + (fConst97 * fRec2[0]))) + (fConst95 * fRec2[0])))) + (fConst94 * fRec2[0])) + (fRec0[0] * (fConst93 + (fConst92 * fRec2[0]))))))) + (fRec3[3] * ((((fRec1[0] * (((fRec0[0] * (fConst90 + (fConst89 * fRec2[0]))) + (fConst87 * fRec2[0])) + fConst86)) + (fConst83 * fRec2[0])) + (fRec0[0] * (fConst82 + (fConst81 * fRec2[0])))) + fConst79))) + (fRec3[4] * ((((fRec1[0] * (((fRec0[0] * (fConst76 + (fConst75 * fRec2[0]))) + (fConst73 * fRec2[0])) + fConst72)) + (fConst70 * fRec2[0])) + (fRec0[0] * (fConst69 + (fConst68 * fRec2[0])))) + fConst66))) + (fRec3[5] * ((((fRec1[0] * (((fRec0[0] * (fConst24 + (fConst23 * fRec2[0]))) + (fConst21 * fRec2[0])) + fConst20)) + (fConst18 * fRec2[0])) + (fRec0[0] * (fConst17 + (fConst16 * fRec2[0])))) + fConst14)))) / fTemp0));
		// post processing
		fRec4[1] = fRec4[0];
		for (int i=5; i>0; i--) fRec3[i] = fRec3[i-1];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
	}
#undef fslider0
#undef fslider1
#undef fslider2
#undef fslider3
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case BODY: 
		fslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case DRIVE: 
		fslider2_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case LEVEL: 
		fslider3_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case TONE: 
		fslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
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
   BODY, 
   DRIVE, 
   LEVEL, 
   TONE, 
} PortIndex;
*/

} // end namespace gxtilttone
