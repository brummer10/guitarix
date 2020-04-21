// generated from file '../src/LV2/faust/gxtilttone.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace gxtilttone {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	double fConst0;
	double fConst1;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec0[2];
	double fConst2;
	double fConst3;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec2[2];
	double fConst4;
	double fConst5;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec3[2];
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
	double fRec1[6];
	double fConst54;
	double fConst55;
	double fConst56;
	double fConst57;
	double fConst58;
	double fConst59;
	double fConst60;
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fRec4[2];
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec0[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec2[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec3[l2] = 0.0;
	for (int l3 = 0; (l3 < 6); l3 = (l3 + 1)) fRec1[l3] = 0.0;
	for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) fRec4[l4] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = (0.10000000000000001 * mydsp_faustpower2_f(fConst0));
	fConst2 = (1.14069652350792e-23 * fConst0);
	fConst3 = (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (-2.6349560001164101e-20 - fConst2)) + -7.9318087295529299e-18)) + 8.46536337187037e-16)) + 5.4243071328378599e-14));
	fConst4 = (1.3127248206517199e-23 * fConst0);
	fConst5 = (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (-1.21632310037211e-20 - fConst4)) + -1.08757722986638e-18)) + 4.2670683709224401e-17)) + 1.30459807978552e-15));
	fConst6 = (1.3127248206517201e-24 * fConst0);
	fConst7 = ((fConst0 * ((fConst0 * ((fConst0 * (-8.4193652779148502e-22 - fConst6)) + -9.5775592186120102e-20)) + 2.5868723463367701e-18)) + 8.5964486975315597e-18);
	fConst8 = (1.10106327973123e-24 * fConst0);
	fConst9 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst8 + 6.5147891380635098e-22)) + 6.19440233250284e-21)) + -6.8771589580132299e-21)) + 3.1450445234293e-32);
	fConst10 = (1.14069652350792e-24 * fConst0);
	fConst11 = ((fConst0 * ((fConst0 * ((fConst0 * (-2.0177063247387299e-21 - fConst10)) + -2.8912883650403799e-19)) + -4.8390308527555599e-17)) + -4.8124336258501303e-15);
	fConst12 = (1.09328433834173e-24 * fConst0);
	fConst13 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst12 + 2.2290376683106399e-21)) + 5.0770266862060799e-19)) + -1.4206809853686799e-17)) + -4.7280467836405903e-17);
	fConst14 = (2.2813930470158401e-23 * fConst0);
	fConst15 = (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst14 + 1.75663733341094e-20)) + -1.58636174591059e-17)) + -1.6930726743740701e-15)) + 3.6162047552252399e-14));
	fConst16 = (2.6254496413034399e-23 * fConst0);
	fConst17 = (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst16 + 8.1088206691473993e-21)) + -2.17515445973276e-18)) + -8.5341367418448802e-17)) + 8.6973205319034397e-16));
	fConst18 = (2.6254496413034402e-24 * fConst0);
	fConst19 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst18 + 5.6129101852765702e-22)) + -1.9155118437224001e-19)) + -5.1737446926735402e-18)) + 5.73096579835437e-18);
	fConst20 = (2.2021265594624699e-24 * fConst0);
	fConst21 = ((fConst0 * ((fConst0 * ((fConst0 * (-4.343192758709e-22 - fConst20)) + 1.2388804665005699e-20)) + 1.3754317916026499e-20)) + 2.0966963489528699e-32);
	fConst22 = (2.28139304701584e-24 * fConst0);
	fConst23 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst22 + 1.3451375498258201e-21)) + -5.7825767300807598e-19)) + 9.6780617055111296e-17)) + -3.2082890839000799e-15);
	fConst24 = (2.1865686766834699e-24 * fConst0);
	fConst25 = ((fConst0 * ((fConst0 * ((fConst0 * (-1.4860251122071e-21 - fConst24)) + 1.01540533724122e-18)) + 2.8413619707373703e-17)) + -3.1520311890937299e-17);
	fConst26 = (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (1.75663733341094e-20 - fConst14)) + 1.58636174591059e-17)) + -1.6930726743740701e-15)) + -3.6162047552252399e-14));
	fConst27 = (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (8.1088206691473993e-21 - fConst16)) + 2.17515445973276e-18)) + -8.5341367418448802e-17)) + -8.6973205319034397e-16));
	fConst28 = ((fConst0 * ((fConst0 * ((fConst0 * (5.6129101852765702e-22 - fConst18)) + 1.9155118437224001e-19)) + -5.1737446926735402e-18)) + -5.73096579835437e-18);
	fConst29 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst20 + -4.343192758709e-22)) + -1.2388804665005699e-20)) + 1.3754317916026499e-20)) + -2.0966963489528699e-32);
	fConst30 = ((fConst0 * ((fConst0 * ((fConst0 * (1.3451375498258201e-21 - fConst22)) + 5.7825767300807598e-19)) + 9.6780617055111296e-17)) + 3.2082890839000799e-15);
	fConst31 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst24 + -1.4860251122071e-21)) + -1.01540533724122e-18)) + 2.8413619707373703e-17)) + 3.1520311890937299e-17);
	fConst32 = (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst2 + -2.6349560001164101e-20)) + 7.9318087295529299e-18)) + 8.46536337187037e-16)) + -5.4243071328378599e-14));
	fConst33 = (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst4 + -1.21632310037211e-20)) + 1.08757722986638e-18)) + 4.2670683709224401e-17)) + -1.30459807978552e-15));
	fConst34 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst6 + -8.4193652779148502e-22)) + 9.5775592186120102e-20)) + 2.5868723463367701e-18)) + -8.5964486975315597e-18);
	fConst35 = ((fConst0 * ((fConst0 * ((fConst0 * (6.5147891380635098e-22 - fConst8)) + -6.19440233250284e-21)) + -6.8771589580132299e-21)) + -3.1450445234293e-32);
	fConst36 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst10 + -2.0177063247387299e-21)) + 2.8912883650403799e-19)) + -4.8390308527555599e-17)) + 4.8124336258501303e-15);
	fConst37 = ((fConst0 * ((fConst0 * ((fConst0 * (2.2290376683106399e-21 - fConst12)) + -5.0770266862060799e-19)) + -1.4206809853686799e-17)) + 4.7280467836405903e-17);
	fConst38 = (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (8.7831866670547105e-21 - fConst22)) + -7.9318087295529299e-18)) + 8.46536337187037e-16)) + -1.80810237761262e-14));
	fConst39 = (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (4.0544103345736997e-21 - fConst18)) + -1.08757722986638e-18)) + 4.2670683709224401e-17)) + -4.3486602659517199e-16));
	fConst40 = (2.62544964130344e-25 * fConst0);
	fConst41 = ((fConst0 * ((fConst0 * ((fConst0 * (2.8064550926382799e-22 - fConst40)) + -9.5775592186120102e-20)) + 2.5868723463367701e-18)) + -2.86548289917719e-18);
	fConst42 = (2.20212655946247e-25 * fConst0);
	fConst43 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst42 + -2.1715963793545e-22)) + 6.19440233250284e-21)) + -6.8771589580132299e-21)) + -1.04834817447643e-32);
	fConst44 = (2.28139304701584e-25 * fConst0);
	fConst45 = ((fConst0 * ((fConst0 * ((fConst0 * (6.7256877491291098e-22 - fConst44)) + -2.8912883650403799e-19)) + -4.8390308527555599e-17)) + 1.6041445419500399e-15);
	fConst46 = (2.1865686766834702e-25 * fConst0);
	fConst47 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst46 + -7.4301255610354802e-22)) + 5.0770266862060799e-19)) + -1.4206809853686799e-17)) + 1.57601559454686e-17);
	fConst48 = (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst22 + 8.7831866670547105e-21)) + 7.9318087295529299e-18)) + 8.46536337187037e-16)) + 1.80810237761262e-14));
	fConst49 = (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst18 + 4.0544103345736997e-21)) + 1.08757722986638e-18)) + 4.2670683709224401e-17)) + 4.3486602659517199e-16));
	fConst50 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst40 + 2.8064550926382799e-22)) + 9.5775592186120102e-20)) + 2.5868723463367701e-18)) + 2.86548289917719e-18);
	fConst51 = ((fConst0 * ((fConst0 * ((fConst0 * (-2.1715963793545e-22 - fConst42)) + -6.19440233250284e-21)) + -6.8771589580132299e-21)) + 1.04834817447643e-32);
	fConst52 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst44 + 6.7256877491291098e-22)) + 2.8912883650403799e-19)) + -4.8390308527555599e-17)) + -1.6041445419500399e-15);
	fConst53 = ((fConst0 * ((fConst0 * ((fConst0 * (-7.4301255610354802e-22 - fConst46)) + -5.0770266862060799e-19)) + -1.4206809853686799e-17)) + -1.57601559454686e-17);
	fConst54 = (8.9208502675412796e-20 * fConst0);
	fConst55 = ((fConst0 * (fConst54 + 5.0561347821916101e-16)) + 7.6403308218065703e-15);
	fConst56 = (3.9825224408666499e-19 * fConst0);
	fConst57 = ((fConst0 * (fConst56 + 1.25414294001131e-16)) + 1.8087904407686001e-15);
	fConst58 = (2.2347967653784101e-22 * fConst0);
	fConst59 = ((fConst0 * ((fConst0 * (fConst58 + 3.3860557051188198e-21)) + 3.1764148214773299e-31)) + 4.8127497295111301e-30);
	fConst60 = ((fConst0 * ((fConst0 * (-3.3860557051188198e-21 - fConst58)) + -3.1764148214773299e-31)) + -4.8127497295111301e-30);
	fConst61 = ((fConst0 * (-1.25414294001131e-16 - fConst56)) + -1.8087904407686001e-15);
	fConst62 = ((fConst0 * (-5.0561347821916101e-16 - fConst54)) + -7.6403308218065703e-15);
	fConst63 = (5.0059447544476199e-23 * fConst0);
	fConst64 = ((fConst0 * ((fConst0 * (fConst63 + 7.58476477946615e-22)) + -4.7752067636290798e-16)) + -7.2351617630744097e-15);
	fConst65 = ((fConst0 * ((fConst0 * (-7.58476477946615e-22 - fConst63)) + 4.7752067636290798e-16)) + 7.2351617630744097e-15);
	fConst66 = (2.6762550802623798e-19 * fConst0);
	fConst67 = ((fConst0 * (-5.0561347821916101e-16 - fConst66)) + 7.6403308218065703e-15);
	fConst68 = (1.19475673226e-18 * fConst0);
	fConst69 = ((fConst0 * (-1.25414294001131e-16 - fConst68)) + 1.8087904407686001e-15);
	fConst70 = (1.1173983826892e-21 * fConst0);
	fConst71 = ((fConst0 * ((fConst0 * (-1.0158167115356499e-20 - fConst70)) + -3.1764148214773299e-31)) + 4.8127497295111301e-30);
	fConst72 = ((fConst0 * ((fConst0 * (fConst70 + 1.0158167115356499e-20)) + 3.1764148214773299e-31)) + -4.8127497295111301e-30);
	fConst73 = ((fConst0 * (fConst68 + 1.25414294001131e-16)) + -1.8087904407686001e-15);
	fConst74 = ((fConst0 * (fConst66 + 5.0561347821916101e-16)) + -7.6403308218065703e-15);
	fConst75 = (2.5029723772238099e-22 * fConst0);
	fConst76 = ((fConst0 * ((fConst0 * (-2.2754294338398401e-21 - fConst75)) + 4.7752067636290798e-16)) + -7.2351617630744097e-15);
	fConst77 = ((fConst0 * ((fConst0 * (fConst75 + 2.2754294338398401e-21)) + -4.7752067636290798e-16)) + 7.2351617630744097e-15);
	fConst78 = (1.78417005350826e-19 * fConst0);
	fConst79 = ((fConst0 * (fConst78 + -1.0112269564383201e-15)) + -1.5280661643613099e-14);
	fConst80 = (7.9650448817332998e-19 * fConst0);
	fConst81 = ((fConst0 * (fConst80 + -2.5082858800226102e-16)) + -3.6175808815371899e-15);
	fConst82 = (2.2347967653784102e-21 * fConst0);
	fConst83 = ((fConst0 * ((fConst0 * (fConst82 + 6.7721114102376502e-21)) + -6.3528296429546597e-31)) + -9.6254994590222701e-30);
	fConst84 = ((fConst0 * ((fConst0 * (-6.7721114102376502e-21 - fConst82)) + 6.3528296429546597e-31)) + 9.6254994590222701e-30);
	fConst85 = ((fConst0 * (2.5082858800226102e-16 - fConst80)) + 3.6175808815371899e-15);
	fConst86 = ((fConst0 * (1.0112269564383201e-15 - fConst78)) + 1.5280661643613099e-14);
	fConst87 = (5.0059447544476198e-22 * fConst0);
	fConst88 = ((fConst0 * ((fConst0 * (fConst87 + 1.51695295589323e-21)) + 9.5504135272581596e-16)) + 1.4470323526148801e-14);
	fConst89 = ((fConst0 * ((fConst0 * (-1.51695295589323e-21 - fConst87)) + -9.5504135272581596e-16)) + -1.4470323526148801e-14);
	fConst90 = ((fConst0 * (fConst78 + 1.0112269564383201e-15)) + -1.5280661643613099e-14);
	fConst91 = ((fConst0 * (fConst80 + 2.5082858800226102e-16)) + -3.6175808815371899e-15);
	fConst92 = ((fConst0 * ((fConst0 * (6.7721114102376502e-21 - fConst82)) + 6.3528296429546597e-31)) + -9.6254994590222701e-30);
	fConst93 = ((fConst0 * ((fConst0 * (fConst82 + -6.7721114102376502e-21)) + -6.3528296429546597e-31)) + 9.6254994590222701e-30);
	fConst94 = ((fConst0 * (-2.5082858800226102e-16 - fConst80)) + 3.6175808815371899e-15);
	fConst95 = ((fConst0 * (-1.0112269564383201e-15 - fConst78)) + 1.5280661643613099e-14);
	fConst96 = ((fConst0 * ((fConst0 * (1.51695295589323e-21 - fConst87)) + -9.5504135272581596e-16)) + 1.4470323526148801e-14);
	fConst97 = ((fConst0 * ((fConst0 * (fConst87 + -1.51695295589323e-21)) + 9.5504135272581596e-16)) + -1.4470323526148801e-14);
	fConst98 = ((fConst0 * (5.0561347821916101e-16 - fConst66)) + 7.6403308218065703e-15);
	fConst99 = ((fConst0 * (1.25414294001131e-16 - fConst68)) + 1.8087904407686001e-15);
	fConst100 = ((fConst0 * ((fConst0 * (fConst70 + -1.0158167115356499e-20)) + 3.1764148214773299e-31)) + 4.8127497295111301e-30);
	fConst101 = ((fConst0 * ((fConst0 * (1.0158167115356499e-20 - fConst70)) + -3.1764148214773299e-31)) + -4.8127497295111301e-30);
	fConst102 = ((fConst0 * (fConst68 + -1.25414294001131e-16)) + -1.8087904407686001e-15);
	fConst103 = ((fConst0 * (fConst66 + -5.0561347821916101e-16)) + -7.6403308218065703e-15);
	fConst104 = ((fConst0 * ((fConst0 * (fConst75 + -2.2754294338398401e-21)) + -4.7752067636290798e-16)) + -7.2351617630744097e-15);
	fConst105 = ((fConst0 * ((fConst0 * (2.2754294338398401e-21 - fConst75)) + 4.7752067636290798e-16)) + 7.2351617630744097e-15);
	fConst106 = ((fConst0 * (fConst54 + -5.0561347821916101e-16)) + 7.6403308218065703e-15);
	fConst107 = ((fConst0 * (fConst56 + -1.25414294001131e-16)) + 1.8087904407686001e-15);
	fConst108 = ((fConst0 * ((fConst0 * (3.3860557051188198e-21 - fConst58)) + -3.1764148214773299e-31)) + 4.8127497295111301e-30);
	fConst109 = ((fConst0 * ((fConst0 * (fConst58 + -3.3860557051188198e-21)) + 3.1764148214773299e-31)) + -4.8127497295111301e-30);
	fConst110 = ((fConst0 * (1.25414294001131e-16 - fConst56)) + -1.8087904407686001e-15);
	fConst111 = ((fConst0 * (5.0561347821916101e-16 - fConst54)) + -7.6403308218065703e-15);
	fConst112 = ((fConst0 * ((fConst0 * (7.58476477946615e-22 - fConst63)) + 4.7752067636290798e-16)) + -7.2351617630744097e-15);
	fConst113 = ((fConst0 * ((fConst0 * (fConst63 + -7.58476477946615e-22)) + -4.7752067636290798e-16)) + 7.2351617630744097e-15);
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
	double fSlow0 = (0.004073836948085289 * (std::exp(double(fVslider0)) + -1.0));
	double fSlow1 = (0.0070000000000000062 * double(fVslider1));
	double fSlow2 = (0.004073836948085289 * (std::exp(double(fVslider2)) + -1.0));
	double fSlow3 = (0.004073836948085289 * (std::exp((1.0 - double(fVslider3))) + -1.0));
	for (int i = 0; (i < count); i = (i + 1)) {
		fRec0[0] = (fSlow0 + (0.99299999999999999 * fRec0[1]));
		fRec2[0] = (fSlow1 + (0.99299999999999999 * fRec2[1]));
		fRec3[0] = (fSlow2 + (0.99299999999999999 * fRec3[1]));
		double fTemp0 = (fConst48 + (((fRec2[0] * (fConst49 + ((fRec3[0] * ((fConst0 * (fConst50 + (fConst51 * fRec3[0]))) + 1.1913047437232199e-30)) + 4.4773170299625501e-16))) + (fRec3[0] * ((fConst0 * (fConst52 + (fConst53 * fRec3[0]))) + -1.7909268119850701e-15))) + 1.9800486833307e-14));
		fRec1[0] = ((2.0 * double(input0[i])) - ((((((fRec1[1] * (fConst3 + (((fRec2[0] * (fConst5 + ((fRec3[0] * ((fConst0 * (fConst7 + (fConst9 * fRec3[0]))) + 5.9565237186161e-30)) + 2.2386585149812802e-15))) + (fRec3[0] * ((fConst0 * (fConst11 + (fConst13 * fRec3[0]))) + -8.95463405992537e-15))) + 9.9002434166534897e-14))) + (fRec1[2] * (fConst15 + (((fRec2[0] * (fConst17 + ((fRec3[0] * ((fConst0 * (fConst19 + (fConst21 * fRec3[0]))) + 1.19130474372322e-29)) + 4.4773170299625501e-15))) + (fRec3[0] * ((fConst0 * (fConst23 + (fConst25 * fRec3[0]))) + -1.7909268119850699e-14))) + 1.9800486833307e-13)))) + (fRec1[3] * (fConst26 + (((fRec2[0] * (fConst27 + ((fRec3[0] * ((fConst0 * (fConst28 + (fConst29 * fRec3[0]))) + 1.19130474372322e-29)) + 4.4773170299625501e-15))) + (fRec3[0] * ((fConst0 * (fConst30 + (fConst31 * fRec3[0]))) + -1.7909268119850699e-14))) + 1.9800486833307e-13)))) + (fRec1[4] * (fConst32 + (((fRec2[0] * (fConst33 + ((fRec3[0] * ((fConst0 * (fConst34 + (fConst35 * fRec3[0]))) + 5.9565237186161e-30)) + 2.2386585149812802e-15))) + (fRec3[0] * ((fConst0 * (fConst36 + (fConst37 * fRec3[0]))) + -8.95463405992537e-15))) + 9.9002434166534897e-14)))) + (fRec1[5] * (fConst38 + (((fRec2[0] * (fConst39 + ((fRec3[0] * ((fConst0 * (fConst41 + (fConst43 * fRec3[0]))) + 1.1913047437232199e-30)) + 4.4773170299625501e-16))) + (fRec3[0] * ((fConst0 * (fConst45 + (fConst47 * fRec3[0]))) + -1.7909268119850701e-15))) + 1.9800486833307e-14)))) / fTemp0));
		fRec4[0] = (fSlow3 + (0.99299999999999999 * fRec4[1]));
		output0[i] = FAUSTFLOAT((fConst1 * ((fRec0[0] * ((((((fRec1[0] * (fConst55 + (((fRec2[0] * (fConst57 + ((fRec3[0] * (fConst59 + (fConst60 * fRec4[0]))) + (fConst61 * fRec4[0])))) + (fConst62 * fRec4[0])) + (fRec3[0] * (fConst64 + (fConst65 * fRec4[0])))))) + (fRec1[1] * (fConst67 + (((fRec2[0] * (fConst69 + ((fRec3[0] * (fConst71 + (fConst72 * fRec4[0]))) + (fConst73 * fRec4[0])))) + (fConst74 * fRec4[0])) + (fRec3[0] * (fConst76 + (fConst77 * fRec4[0]))))))) + (fRec1[2] * (fConst79 + (((fRec2[0] * (fConst81 + ((fRec3[0] * (fConst83 + (fConst84 * fRec4[0]))) + (fConst85 * fRec4[0])))) + (fConst86 * fRec4[0])) + (fRec3[0] * (fConst88 + (fConst89 * fRec4[0]))))))) + (fRec1[3] * (fConst90 + (((fRec2[0] * (fConst91 + ((fRec3[0] * (fConst92 + (fConst93 * fRec4[0]))) + (fConst94 * fRec4[0])))) + (fConst95 * fRec4[0])) + (fRec3[0] * (fConst96 + (fConst97 * fRec4[0]))))))) + (fRec1[4] * (fConst98 + (((fRec2[0] * (fConst99 + ((fRec3[0] * (fConst100 + (fConst101 * fRec4[0]))) + (fConst102 * fRec4[0])))) + (fConst103 * fRec4[0])) + (fRec3[0] * (fConst104 + (fConst105 * fRec4[0]))))))) + (fRec1[5] * (fConst106 + (((fRec2[0] * (fConst107 + ((fRec3[0] * (fConst108 + (fConst109 * fRec4[0]))) + (fConst110 * fRec4[0])))) + (fConst111 * fRec4[0])) + (fRec3[0] * (fConst112 + (fConst113 * fRec4[0])))))))) / fTemp0)));
		fRec0[1] = fRec0[0];
		fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		for (int j0 = 5; (j0 > 0); j0 = (j0 - 1)) {
			fRec1[j0] = fRec1[(j0 - 1)];
		}
		fRec4[1] = fRec4[0];
	}
#undef fVslider0
#undef fVslider1
#undef fVslider2
#undef fVslider3
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
		fVslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case DRIVE: 
		fVslider3_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case LEVEL: 
		fVslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case TONE: 
		fVslider2_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
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
