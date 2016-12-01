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
	fConst1 = (2.28139304701584e-24 * fConst0);
	fConst2 = (1.9800486833307e-14 + (fConst0 * (1.80810237761262e-14 + (fConst0 * (8.46536337187037e-16 + (fConst0 * (7.93180872955293e-18 + (fConst0 * (8.78318666705471e-21 + fConst1)))))))));
	fConst3 = (2.18656867668347e-25 * fConst0);
	fConst4 = ((fConst0 * ((fConst0 * ((fConst0 * (0 - (7.43012556103548e-22 + fConst3))) - 5.07702668620608e-19)) - 1.42068098536868e-17)) - 1.57601559454686e-17);
	fConst5 = (2.28139304701584e-25 * fConst0);
	fConst6 = ((fConst0 * ((fConst0 * (2.89128836504038e-19 + (fConst0 * (6.72568774912911e-22 + fConst5)))) - 4.83903085275556e-17)) - 1.60414454195004e-15);
	fConst7 = (2.62544964130344e-24 * fConst0);
	fConst8 = (4.47731702996255e-16 + (fConst0 * (4.34866026595172e-16 + (fConst0 * (4.26706837092244e-17 + (fConst0 * (1.08757722986638e-18 + (fConst0 * (4.0544103345737e-21 + fConst7)))))))));
	fConst9 = (2.20212655946247e-25 * fConst0);
	fConst10 = (1.04834817447643e-32 + (fConst0 * ((fConst0 * ((fConst0 * (0 - (2.1715963793545e-22 + fConst9))) - 6.19440233250284e-21)) - 6.87715895801323e-21)));
	fConst11 = (2.62544964130344e-25 * fConst0);
	fConst12 = (2.86548289917719e-18 + (fConst0 * (2.58687234633677e-18 + (fConst0 * (9.57755921861201e-20 + (fConst0 * (2.80645509263828e-22 + fConst11)))))));
	fConst13 = (8.92085026754128e-20 * fConst0);
	fConst14 = (7.64033082180657e-15 + (fConst0 * (fConst13 - 5.05613478219161e-16)));
	fConst15 = (5.00594475444762e-23 * fConst0);
	fConst16 = (7.23516176307441e-15 + (fConst0 * ((fConst0 * (fConst15 - 7.58476477946615e-22)) - 4.77520676362908e-16)));
	fConst17 = ((fConst0 * (4.77520676362908e-16 + (fConst0 * (7.58476477946615e-22 - fConst15)))) - 7.23516176307441e-15);
	fConst18 = ((fConst0 * (5.05613478219161e-16 - fConst13)) - 7.64033082180657e-15);
	fConst19 = (3.98252244086665e-19 * fConst0);
	fConst20 = (1.8087904407686e-15 + (fConst0 * (fConst19 - 1.25414294001131e-16)));
	fConst21 = ((fConst0 * (1.25414294001131e-16 - fConst19)) - 1.8087904407686e-15);
	fConst22 = (2.23479676537841e-22 * fConst0);
	fConst23 = ((fConst0 * (3.17641482147733e-31 + (fConst0 * (fConst22 - 3.38605570511882e-21)))) - 4.81274972951113e-30);
	fConst24 = (4.81274972951113e-30 + (fConst0 * ((fConst0 * (3.38605570511882e-21 - fConst22)) - 3.17641482147733e-31)));
	fConst25 = (1.9800486833307e-14 + (fConst0 * ((fConst0 * (8.46536337187037e-16 + (fConst0 * ((fConst0 * (8.78318666705471e-21 - fConst1)) - 7.93180872955293e-18)))) - 1.80810237761262e-14)));
	fConst26 = (1.57601559454686e-17 + (fConst0 * ((fConst0 * (5.07702668620608e-19 + (fConst0 * (fConst3 - 7.43012556103548e-22)))) - 1.42068098536868e-17)));
	fConst27 = (1.60414454195004e-15 + (fConst0 * ((fConst0 * ((fConst0 * (6.72568774912911e-22 - fConst5)) - 2.89128836504038e-19)) - 4.83903085275556e-17)));
	fConst28 = (4.47731702996255e-16 + (fConst0 * ((fConst0 * (4.26706837092244e-17 + (fConst0 * ((fConst0 * (4.0544103345737e-21 - fConst7)) - 1.08757722986638e-18)))) - 4.34866026595172e-16)));
	fConst29 = ((fConst0 * ((fConst0 * (6.19440233250284e-21 + (fConst0 * (fConst9 - 2.1715963793545e-22)))) - 6.87715895801323e-21)) - 1.04834817447643e-32);
	fConst30 = ((fConst0 * (2.58687234633677e-18 + (fConst0 * ((fConst0 * (2.80645509263828e-22 - fConst11)) - 9.57755921861201e-20)))) - 2.86548289917719e-18);
	fConst31 = (1.14069652350792e-23 * fConst0);
	fConst32 = (9.90024341665349e-14 + (fConst0 * ((fConst0 * (8.46536337187037e-16 + (fConst0 * (7.93180872955293e-18 + (fConst0 * (fConst31 - 2.63495600011641e-20)))))) - 5.42430713283786e-14)));
	fConst33 = (1.09328433834173e-24 * fConst0);
	fConst34 = (4.72804678364059e-17 + (fConst0 * ((fConst0 * ((fConst0 * (2.22903766831064e-21 - fConst33)) - 5.07702668620608e-19)) - 1.42068098536868e-17)));
	fConst35 = (1.14069652350792e-24 * fConst0);
	fConst36 = (4.81243362585013e-15 + (fConst0 * ((fConst0 * (2.89128836504038e-19 + (fConst0 * (fConst35 - 2.01770632473873e-21)))) - 4.83903085275556e-17)));
	fConst37 = (1.31272482065172e-23 * fConst0);
	fConst38 = (2.23865851498128e-15 + (fConst0 * ((fConst0 * (4.26706837092244e-17 + (fConst0 * (1.08757722986638e-18 + (fConst0 * (fConst37 - 1.21632310037211e-20)))))) - 1.30459807978552e-15)));
	fConst39 = (1.10106327973123e-24 * fConst0);
	fConst40 = ((fConst0 * ((fConst0 * ((fConst0 * (6.51478913806351e-22 - fConst39)) - 6.19440233250284e-21)) - 6.87715895801323e-21)) - 3.1450445234293e-32);
	fConst41 = (1.31272482065172e-24 * fConst0);
	fConst42 = ((fConst0 * (2.58687234633677e-18 + (fConst0 * (9.57755921861201e-20 + (fConst0 * (fConst41 - 8.41936527791485e-22)))))) - 8.59644869753156e-18);
	fConst43 = (2.28139304701584e-23 * fConst0);
	fConst44 = (1.9800486833307e-13 + (fConst0 * ((fConst0 * ((fConst0 * (1.58636174591059e-17 + (fConst0 * (1.75663733341094e-20 - fConst43)))) - 1.69307267437407e-15)) - 3.61620475522524e-14)));
	fConst45 = (2.18656867668347e-24 * fConst0);
	fConst46 = (3.15203118909373e-17 + (fConst0 * (2.84136197073737e-17 + (fConst0 * ((fConst0 * (fConst45 - 1.4860251122071e-21)) - 1.01540533724122e-18)))));
	fConst47 = (3.20828908390008e-15 + (fConst0 * (9.67806170551113e-17 + (fConst0 * (5.78257673008076e-19 + (fConst0 * (1.34513754982582e-21 - fConst1)))))));
	fConst48 = (2.62544964130344e-23 * fConst0);
	fConst49 = (4.47731702996255e-15 + (fConst0 * ((fConst0 * ((fConst0 * (2.17515445973276e-18 + (fConst0 * (8.1088206691474e-21 - fConst48)))) - 8.53413674184488e-17)) - 8.69732053190344e-16)));
	fConst50 = (2.20212655946247e-24 * fConst0);
	fConst51 = ((fConst0 * (1.37543179160265e-20 + (fConst0 * ((fConst0 * (fConst50 - 4.343192758709e-22)) - 1.23888046650057e-20)))) - 2.09669634895287e-32);
	fConst52 = ((fConst0 * ((fConst0 * (1.9155118437224e-19 + (fConst0 * (5.61291018527657e-22 - fConst7)))) - 5.17374469267354e-18)) - 5.73096579835437e-18);
	fConst53 = (1.9800486833307e-13 + (fConst0 * (3.61620475522524e-14 + (fConst0 * ((fConst0 * ((fConst0 * (1.75663733341094e-20 + fConst43)) - 1.58636174591059e-17)) - 1.69307267437407e-15)))));
	fConst54 = ((fConst0 * (2.84136197073737e-17 + (fConst0 * (1.01540533724122e-18 + (fConst0 * (0 - (1.4860251122071e-21 + fConst45))))))) - 3.15203118909373e-17);
	fConst55 = ((fConst0 * (9.67806170551113e-17 + (fConst0 * ((fConst0 * (1.34513754982582e-21 + fConst1)) - 5.78257673008076e-19)))) - 3.20828908390008e-15);
	fConst56 = (4.47731702996255e-15 + (fConst0 * (8.69732053190344e-16 + (fConst0 * ((fConst0 * ((fConst0 * (8.1088206691474e-21 + fConst48)) - 2.17515445973276e-18)) - 8.53413674184488e-17)))));
	fConst57 = (2.09669634895287e-32 + (fConst0 * (1.37543179160265e-20 + (fConst0 * (1.23888046650057e-20 + (fConst0 * (0 - (4.343192758709e-22 + fConst50))))))));
	fConst58 = (5.73096579835437e-18 + (fConst0 * ((fConst0 * ((fConst0 * (5.61291018527657e-22 + fConst7)) - 1.9155118437224e-19)) - 5.17374469267354e-18)));
	fConst59 = (9.90024341665349e-14 + (fConst0 * (5.42430713283786e-14 + (fConst0 * (8.46536337187037e-16 + (fConst0 * ((fConst0 * (0 - (2.63495600011641e-20 + fConst31))) - 7.93180872955293e-18)))))));
	fConst60 = ((fConst0 * ((fConst0 * (5.07702668620608e-19 + (fConst0 * (2.22903766831064e-21 + fConst33)))) - 1.42068098536868e-17)) - 4.72804678364059e-17);
	fConst61 = ((fConst0 * ((fConst0 * ((fConst0 * (0 - (2.01770632473873e-21 + fConst35))) - 2.89128836504038e-19)) - 4.83903085275556e-17)) - 4.81243362585013e-15);
	fConst62 = (2.23865851498128e-15 + (fConst0 * (1.30459807978552e-15 + (fConst0 * (4.26706837092244e-17 + (fConst0 * ((fConst0 * (0 - (1.21632310037211e-20 + fConst37))) - 1.08757722986638e-18)))))));
	fConst63 = (3.1450445234293e-32 + (fConst0 * ((fConst0 * (6.19440233250284e-21 + (fConst0 * (6.51478913806351e-22 + fConst39)))) - 6.87715895801323e-21)));
	fConst64 = (8.59644869753156e-18 + (fConst0 * (2.58687234633677e-18 + (fConst0 * ((fConst0 * (0 - (8.41936527791485e-22 + fConst41))) - 9.57755921861201e-20)))));
	fConst65 = (2.67625508026238e-19 * fConst0);
	fConst66 = (7.64033082180657e-15 + (fConst0 * (5.05613478219161e-16 - fConst65)));
	fConst67 = (2.50297237722381e-22 * fConst0);
	fConst68 = (7.23516176307441e-15 + (fConst0 * (4.77520676362908e-16 + (fConst0 * (2.27542943383984e-21 - fConst67)))));
	fConst69 = ((fConst0 * ((fConst0 * (fConst67 - 2.27542943383984e-21)) - 4.77520676362908e-16)) - 7.23516176307441e-15);
	fConst70 = ((fConst0 * (fConst65 - 5.05613478219161e-16)) - 7.64033082180657e-15);
	fConst71 = (1.19475673226e-18 * fConst0);
	fConst72 = (1.8087904407686e-15 + (fConst0 * (1.25414294001131e-16 - fConst71)));
	fConst73 = ((fConst0 * (fConst71 - 1.25414294001131e-16)) - 1.8087904407686e-15);
	fConst74 = (1.1173983826892e-21 * fConst0);
	fConst75 = ((fConst0 * ((fConst0 * (1.01581671153565e-20 - fConst74)) - 3.17641482147733e-31)) - 4.81274972951113e-30);
	fConst76 = (4.81274972951113e-30 + (fConst0 * (3.17641482147733e-31 + (fConst0 * (fConst74 - 1.01581671153565e-20)))));
	fConst77 = (1.78417005350826e-19 * fConst0);
	fConst78 = (1.01122695643832e-15 + fConst77);
	fConst79 = ((fConst0 * fConst78) - 1.52806616436131e-14);
	fConst80 = (5.00594475444762e-22 * fConst0);
	fConst81 = ((fConst0 * (9.55041352725816e-16 + (fConst0 * (fConst80 - 1.51695295589323e-21)))) - 1.44703235261488e-14);
	fConst82 = (1.44703235261488e-14 + (fConst0 * ((fConst0 * (1.51695295589323e-21 - fConst80)) - 9.55041352725816e-16)));
	fConst83 = (1.52806616436131e-14 + (fConst0 * (0 - fConst78)));
	fConst84 = (7.9650448817333e-19 * fConst0);
	fConst85 = (2.50828588002261e-16 + fConst84);
	fConst86 = (3.61758088153719e-15 + (fConst0 * (0 - fConst85)));
	fConst87 = (2.23479676537841e-21 * fConst0);
	fConst88 = (9.62549945902227e-30 + (fConst0 * ((fConst0 * (fConst87 - 6.77211141023765e-21)) - 6.35282964295466e-31)));
	fConst89 = ((fConst0 * (6.35282964295466e-31 + (fConst0 * (6.77211141023765e-21 - fConst87)))) - 9.62549945902227e-30);
	fConst90 = ((fConst0 * fConst85) - 3.61758088153719e-15);
	fConst91 = (1.51695295589323e-21 + fConst80);
	fConst92 = ((fConst0 * ((fConst0 * (0 - fConst91)) - 9.55041352725816e-16)) - 1.44703235261488e-14);
	fConst93 = (1.44703235261488e-14 + (fConst0 * (9.55041352725816e-16 + (fConst0 * fConst91))));
	fConst94 = (1.52806616436131e-14 + (fConst0 * (1.01122695643832e-15 - fConst77)));
	fConst95 = (3.61758088153719e-15 + (fConst0 * (2.50828588002261e-16 - fConst84)));
	fConst96 = (6.77211141023765e-21 + fConst87);
	fConst97 = (9.62549945902227e-30 + (fConst0 * (6.35282964295466e-31 + (fConst0 * (0 - fConst96)))));
	fConst98 = ((fConst0 * ((fConst0 * fConst96) - 6.35282964295466e-31)) - 9.62549945902227e-30);
	fConst99 = ((fConst0 * (fConst84 - 2.50828588002261e-16)) - 3.61758088153719e-15);
	fConst100 = ((fConst0 * (fConst77 - 1.01122695643832e-15)) - 1.52806616436131e-14);
	fConst101 = (5.05613478219161e-16 + fConst65);
	fConst102 = (7.64033082180657e-15 + (fConst0 * (0 - fConst101)));
	fConst103 = (2.27542943383984e-21 + fConst67);
	fConst104 = (7.23516176307441e-15 + (fConst0 * ((fConst0 * fConst103) - 4.77520676362908e-16)));
	fConst105 = ((fConst0 * (4.77520676362908e-16 + (fConst0 * (0 - fConst103)))) - 7.23516176307441e-15);
	fConst106 = ((fConst0 * fConst101) - 7.64033082180657e-15);
	fConst107 = (1.25414294001131e-16 + fConst71);
	fConst108 = (1.8087904407686e-15 + (fConst0 * (0 - fConst107)));
	fConst109 = ((fConst0 * fConst107) - 1.8087904407686e-15);
	fConst110 = (1.01581671153565e-20 + fConst74);
	fConst111 = ((fConst0 * (3.17641482147733e-31 + (fConst0 * fConst110))) - 4.81274972951113e-30);
	fConst112 = (4.81274972951113e-30 + (fConst0 * ((fConst0 * (0 - fConst110)) - 3.17641482147733e-31)));
	fConst113 = (5.05613478219161e-16 + fConst13);
	fConst114 = (7.64033082180657e-15 + (fConst0 * fConst113));
	fConst115 = (7.58476477946615e-22 + fConst15);
	fConst116 = (7.23516176307441e-15 + (fConst0 * (4.77520676362908e-16 + (fConst0 * (0 - fConst115)))));
	fConst117 = ((fConst0 * ((fConst0 * fConst115) - 4.77520676362908e-16)) - 7.23516176307441e-15);
	fConst118 = ((fConst0 * (0 - fConst113)) - 7.64033082180657e-15);
	fConst119 = (1.25414294001131e-16 + fConst19);
	fConst120 = (1.8087904407686e-15 + (fConst0 * fConst119));
	fConst121 = ((fConst0 * (0 - fConst119)) - 1.8087904407686e-15);
	fConst122 = (3.38605570511882e-21 + fConst22);
	fConst123 = ((fConst0 * ((fConst0 * (0 - fConst122)) - 3.17641482147733e-31)) - 4.81274972951113e-30);
	fConst124 = (4.81274972951113e-30 + (fConst0 * (3.17641482147733e-31 + (fConst0 * fConst122))));
	fConst125 = faustpower<2>(fConst0);
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
		double fTemp0 = (((fRec1[0] * ((fRec0[0] * (1.19130474372322e-30 + (fConst0 * (fConst12 + (fConst10 * fRec0[0]))))) + fConst8)) + (fRec0[0] * ((fConst0 * (fConst6 + (fConst4 * fRec0[0]))) - 1.79092681198507e-15))) + fConst2);
		fRec2[0] = ((0.993 * fRec2[1]) + fSlow2);
		fRec3[0] = ((double)input0[i] - ((((((fRec3[1] * (((fRec1[0] * ((fRec0[0] * (5.9565237186161e-30 + (fConst0 * (fConst64 + (fConst63 * fRec0[0]))))) + fConst62)) + (fRec0[0] * ((fConst0 * (fConst61 + (fConst60 * fRec0[0]))) - 8.95463405992537e-15))) + fConst59)) + (fRec3[2] * (((fRec1[0] * ((fRec0[0] * (1.19130474372322e-29 + (fConst0 * (fConst58 + (fConst57 * fRec0[0]))))) + fConst56)) + (fRec0[0] * ((fConst0 * (fConst55 + (fConst54 * fRec0[0]))) - 1.79092681198507e-14))) + fConst53))) + (fRec3[3] * (((fRec1[0] * ((fRec0[0] * (1.19130474372322e-29 + (fConst0 * (fConst52 + (fConst51 * fRec0[0]))))) + fConst49)) + (fRec0[0] * ((fConst0 * (fConst47 + (fConst46 * fRec0[0]))) - 1.79092681198507e-14))) + fConst44))) + (fRec3[4] * (((fRec1[0] * ((fRec0[0] * (5.9565237186161e-30 + (fConst0 * (fConst42 + (fConst40 * fRec0[0]))))) + fConst38)) + (fRec0[0] * ((fConst0 * (fConst36 + (fConst34 * fRec0[0]))) - 8.95463405992537e-15))) + fConst32))) + (fRec3[5] * (((fRec1[0] * ((fRec0[0] * (1.19130474372322e-30 + (fConst0 * (fConst30 + (fConst29 * fRec0[0]))))) + fConst28)) + (fRec0[0] * ((fConst0 * (fConst27 + (fConst26 * fRec0[0]))) - 1.79092681198507e-15))) + fConst25))) / fTemp0));
		fRec4[0] = ((0.993 * fRec4[1]) + fSlow3);
		output0[i] = (FAUSTFLOAT)(fConst125 * ((fRec4[0] * ((((((fRec3[0] * ((((fRec1[0] * (((fRec0[0] * (fConst124 + (fConst123 * fRec2[0]))) + (fConst121 * fRec2[0])) + fConst120)) + (fConst118 * fRec2[0])) + (fRec0[0] * (fConst117 + (fConst116 * fRec2[0])))) + fConst114)) + (fRec3[1] * ((((fRec1[0] * (((fRec0[0] * (fConst112 + (fConst111 * fRec2[0]))) + (fConst109 * fRec2[0])) + fConst108)) + (fConst106 * fRec2[0])) + (fRec0[0] * (fConst105 + (fConst104 * fRec2[0])))) + fConst102))) + (fRec3[2] * (fConst100 + (((fRec1[0] * (fConst99 + ((fRec0[0] * (fConst98 + (fConst97 * fRec2[0]))) + (fConst95 * fRec2[0])))) + (fConst94 * fRec2[0])) + (fRec0[0] * (fConst93 + (fConst92 * fRec2[0]))))))) + (fRec3[3] * ((((fRec1[0] * (fConst90 + ((fRec0[0] * (fConst89 + (fConst88 * fRec2[0]))) + (fConst86 * fRec2[0])))) + (fConst83 * fRec2[0])) + (fRec0[0] * (fConst82 + (fConst81 * fRec2[0])))) + fConst79))) + (fRec3[4] * ((((fRec1[0] * (((fRec0[0] * (fConst76 + (fConst75 * fRec2[0]))) + (fConst73 * fRec2[0])) + fConst72)) + (fConst70 * fRec2[0])) + (fRec0[0] * (fConst69 + (fConst68 * fRec2[0])))) + fConst66))) + (fRec3[5] * ((((fRec1[0] * (((fRec0[0] * (fConst24 + (fConst23 * fRec2[0]))) + (fConst21 * fRec2[0])) + fConst20)) + (fConst18 * fRec2[0])) + (fRec0[0] * (fConst17 + (fConst16 * fRec2[0])))) + fConst14)))) / fTemp0));
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
