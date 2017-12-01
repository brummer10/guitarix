// generated from file '../src/LV2/faust/gxtilttone.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)


namespace gxtilttone {

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
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec2[2];
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
	fConst0 = double(min(1.92e+05, max(1.0, (double)fSamplingFreq)));
	fConst1 = (2.20212655946247e-25 * fConst0);
	fConst2 = (1.04834817447643e-32 + (fConst0 * ((fConst0 * ((fConst0 * (0 - (2.1715963793545e-22 + fConst1))) - 6.19440233250284e-21)) - 6.87715895801323e-21)));
	fConst3 = (2.62544964130344e-25 * fConst0);
	fConst4 = (2.86548289917719e-18 + (fConst0 * (2.58687234633677e-18 + (fConst0 * (9.57755921861201e-20 + (fConst0 * (2.80645509263828e-22 + fConst3)))))));
	fConst5 = (2.62544964130344e-24 * fConst0);
	fConst6 = (4.47731702996255e-16 + (fConst0 * (4.34866026595172e-16 + (fConst0 * (4.26706837092244e-17 + (fConst0 * (1.08757722986638e-18 + (fConst0 * (4.0544103345737e-21 + fConst5)))))))));
	fConst7 = (2.18656867668347e-25 * fConst0);
	fConst8 = ((fConst0 * ((fConst0 * ((fConst0 * (0 - (7.43012556103548e-22 + fConst7))) - 5.07702668620608e-19)) - 1.42068098536868e-17)) - 1.57601559454686e-17);
	fConst9 = (2.28139304701584e-25 * fConst0);
	fConst10 = ((fConst0 * ((fConst0 * (2.89128836504038e-19 + (fConst0 * (6.72568774912911e-22 + fConst9)))) - 4.83903085275556e-17)) - 1.60414454195004e-15);
	fConst11 = (2.28139304701584e-24 * fConst0);
	fConst12 = (1.9800486833307e-14 + (fConst0 * (1.80810237761262e-14 + (fConst0 * (8.46536337187037e-16 + (fConst0 * (7.93180872955293e-18 + (fConst0 * (8.78318666705471e-21 + fConst11)))))))));
	fConst13 = (5.00594475444762e-23 * fConst0);
	fConst14 = (7.23516176307441e-15 + (fConst0 * ((fConst0 * (fConst13 - 7.58476477946615e-22)) - 4.77520676362908e-16)));
	fConst15 = ((fConst0 * (4.77520676362908e-16 + (fConst0 * (7.58476477946615e-22 - fConst13)))) - 7.23516176307441e-15);
	fConst16 = (8.92085026754128e-20 * fConst0);
	fConst17 = ((fConst0 * (5.05613478219161e-16 - fConst16)) - 7.64033082180657e-15);
	fConst18 = (3.98252244086665e-19 * fConst0);
	fConst19 = ((fConst0 * (1.25414294001131e-16 - fConst18)) - 1.8087904407686e-15);
	fConst20 = (2.23479676537841e-22 * fConst0);
	fConst21 = ((fConst0 * (3.17641482147733e-31 + (fConst0 * (fConst20 - 3.38605570511882e-21)))) - 4.81274972951113e-30);
	fConst22 = (4.81274972951113e-30 + (fConst0 * ((fConst0 * (3.38605570511882e-21 - fConst20)) - 3.17641482147733e-31)));
	fConst23 = (1.8087904407686e-15 + (fConst0 * (fConst18 - 1.25414294001131e-16)));
	fConst24 = (7.64033082180657e-15 + (fConst0 * (fConst16 - 5.05613478219161e-16)));
	fConst25 = ((fConst0 * ((fConst0 * (6.19440233250284e-21 + (fConst0 * (fConst1 - 2.1715963793545e-22)))) - 6.87715895801323e-21)) - 1.04834817447643e-32);
	fConst26 = ((fConst0 * (2.58687234633677e-18 + (fConst0 * ((fConst0 * (2.80645509263828e-22 - fConst3)) - 9.57755921861201e-20)))) - 2.86548289917719e-18);
	fConst27 = (4.47731702996255e-16 + (fConst0 * ((fConst0 * (4.26706837092244e-17 + (fConst0 * ((fConst0 * (4.0544103345737e-21 - fConst5)) - 1.08757722986638e-18)))) - 4.34866026595172e-16)));
	fConst28 = (1.57601559454686e-17 + (fConst0 * ((fConst0 * (5.07702668620608e-19 + (fConst0 * (fConst7 - 7.43012556103548e-22)))) - 1.42068098536868e-17)));
	fConst29 = (1.60414454195004e-15 + (fConst0 * ((fConst0 * ((fConst0 * (6.72568774912911e-22 - fConst9)) - 2.89128836504038e-19)) - 4.83903085275556e-17)));
	fConst30 = (1.9800486833307e-14 + (fConst0 * ((fConst0 * (8.46536337187037e-16 + (fConst0 * ((fConst0 * (8.78318666705471e-21 - fConst11)) - 7.93180872955293e-18)))) - 1.80810237761262e-14)));
	fConst31 = (1.10106327973123e-24 * fConst0);
	fConst32 = ((fConst0 * ((fConst0 * ((fConst0 * (6.51478913806351e-22 - fConst31)) - 6.19440233250284e-21)) - 6.87715895801323e-21)) - 3.1450445234293e-32);
	fConst33 = (1.31272482065172e-24 * fConst0);
	fConst34 = ((fConst0 * (2.58687234633677e-18 + (fConst0 * (9.57755921861201e-20 + (fConst0 * (fConst33 - 8.41936527791485e-22)))))) - 8.59644869753156e-18);
	fConst35 = (1.31272482065172e-23 * fConst0);
	fConst36 = (2.23865851498128e-15 + (fConst0 * ((fConst0 * (4.26706837092244e-17 + (fConst0 * (1.08757722986638e-18 + (fConst0 * (fConst35 - 1.21632310037211e-20)))))) - 1.30459807978552e-15)));
	fConst37 = (1.09328433834173e-24 * fConst0);
	fConst38 = (4.72804678364059e-17 + (fConst0 * ((fConst0 * ((fConst0 * (2.22903766831064e-21 - fConst37)) - 5.07702668620608e-19)) - 1.42068098536868e-17)));
	fConst39 = (1.14069652350792e-24 * fConst0);
	fConst40 = (4.81243362585013e-15 + (fConst0 * ((fConst0 * (2.89128836504038e-19 + (fConst0 * (fConst39 - 2.01770632473873e-21)))) - 4.83903085275556e-17)));
	fConst41 = (1.14069652350792e-23 * fConst0);
	fConst42 = (9.90024341665349e-14 + (fConst0 * ((fConst0 * (8.46536337187037e-16 + (fConst0 * (7.93180872955293e-18 + (fConst0 * (fConst41 - 2.63495600011641e-20)))))) - 5.42430713283786e-14)));
	fConst43 = (2.20212655946247e-24 * fConst0);
	fConst44 = ((fConst0 * (1.37543179160265e-20 + (fConst0 * ((fConst0 * (fConst43 - 4.343192758709e-22)) - 1.23888046650057e-20)))) - 2.09669634895287e-32);
	fConst45 = ((fConst0 * ((fConst0 * (1.9155118437224e-19 + (fConst0 * (5.61291018527657e-22 - fConst5)))) - 5.17374469267354e-18)) - 5.73096579835437e-18);
	fConst46 = (2.62544964130344e-23 * fConst0);
	fConst47 = (4.47731702996255e-15 + (fConst0 * ((fConst0 * ((fConst0 * (2.17515445973276e-18 + (fConst0 * (8.1088206691474e-21 - fConst46)))) - 8.53413674184488e-17)) - 8.69732053190344e-16)));
	fConst48 = (2.18656867668347e-24 * fConst0);
	fConst49 = (3.15203118909373e-17 + (fConst0 * (2.84136197073737e-17 + (fConst0 * ((fConst0 * (fConst48 - 1.4860251122071e-21)) - 1.01540533724122e-18)))));
	fConst50 = (3.20828908390008e-15 + (fConst0 * (9.67806170551113e-17 + (fConst0 * (5.78257673008076e-19 + (fConst0 * (1.34513754982582e-21 - fConst11)))))));
	fConst51 = (2.28139304701584e-23 * fConst0);
	fConst52 = (1.9800486833307e-13 + (fConst0 * ((fConst0 * ((fConst0 * (1.58636174591059e-17 + (fConst0 * (1.75663733341094e-20 - fConst51)))) - 1.69307267437407e-15)) - 3.61620475522524e-14)));
	fConst53 = (2.09669634895287e-32 + (fConst0 * (1.37543179160265e-20 + (fConst0 * (1.23888046650057e-20 + (fConst0 * (0 - (4.343192758709e-22 + fConst43))))))));
	fConst54 = (5.73096579835437e-18 + (fConst0 * ((fConst0 * ((fConst0 * (5.61291018527657e-22 + fConst5)) - 1.9155118437224e-19)) - 5.17374469267354e-18)));
	fConst55 = (4.47731702996255e-15 + (fConst0 * (8.69732053190344e-16 + (fConst0 * ((fConst0 * ((fConst0 * (8.1088206691474e-21 + fConst46)) - 2.17515445973276e-18)) - 8.53413674184488e-17)))));
	fConst56 = ((fConst0 * (2.84136197073737e-17 + (fConst0 * (1.01540533724122e-18 + (fConst0 * (0 - (1.4860251122071e-21 + fConst48))))))) - 3.15203118909373e-17);
	fConst57 = ((fConst0 * (9.67806170551113e-17 + (fConst0 * ((fConst0 * (1.34513754982582e-21 + fConst11)) - 5.78257673008076e-19)))) - 3.20828908390008e-15);
	fConst58 = (1.9800486833307e-13 + (fConst0 * (3.61620475522524e-14 + (fConst0 * ((fConst0 * ((fConst0 * (1.75663733341094e-20 + fConst51)) - 1.58636174591059e-17)) - 1.69307267437407e-15)))));
	fConst59 = (3.1450445234293e-32 + (fConst0 * ((fConst0 * (6.19440233250284e-21 + (fConst0 * (6.51478913806351e-22 + fConst31)))) - 6.87715895801323e-21)));
	fConst60 = (8.59644869753156e-18 + (fConst0 * (2.58687234633677e-18 + (fConst0 * ((fConst0 * (0 - (8.41936527791485e-22 + fConst33))) - 9.57755921861201e-20)))));
	fConst61 = (2.23865851498128e-15 + (fConst0 * (1.30459807978552e-15 + (fConst0 * (4.26706837092244e-17 + (fConst0 * ((fConst0 * (0 - (1.21632310037211e-20 + fConst35))) - 1.08757722986638e-18)))))));
	fConst62 = ((fConst0 * ((fConst0 * (5.07702668620608e-19 + (fConst0 * (2.22903766831064e-21 + fConst37)))) - 1.42068098536868e-17)) - 4.72804678364059e-17);
	fConst63 = ((fConst0 * ((fConst0 * ((fConst0 * (0 - (2.01770632473873e-21 + fConst39))) - 2.89128836504038e-19)) - 4.83903085275556e-17)) - 4.81243362585013e-15);
	fConst64 = (9.90024341665349e-14 + (fConst0 * (5.42430713283786e-14 + (fConst0 * (8.46536337187037e-16 + (fConst0 * ((fConst0 * (0 - (2.63495600011641e-20 + fConst41))) - 7.93180872955293e-18)))))));
	fConst65 = (2.50297237722381e-22 * fConst0);
	fConst66 = (7.23516176307441e-15 + (fConst0 * (4.77520676362908e-16 + (fConst0 * (2.27542943383984e-21 - fConst65)))));
	fConst67 = ((fConst0 * ((fConst0 * (fConst65 - 2.27542943383984e-21)) - 4.77520676362908e-16)) - 7.23516176307441e-15);
	fConst68 = (2.67625508026238e-19 * fConst0);
	fConst69 = ((fConst0 * (fConst68 - 5.05613478219161e-16)) - 7.64033082180657e-15);
	fConst70 = (1.19475673226e-18 * fConst0);
	fConst71 = ((fConst0 * (fConst70 - 1.25414294001131e-16)) - 1.8087904407686e-15);
	fConst72 = (1.1173983826892e-21 * fConst0);
	fConst73 = ((fConst0 * ((fConst0 * (1.01581671153565e-20 - fConst72)) - 3.17641482147733e-31)) - 4.81274972951113e-30);
	fConst74 = (4.81274972951113e-30 + (fConst0 * (3.17641482147733e-31 + (fConst0 * (fConst72 - 1.01581671153565e-20)))));
	fConst75 = (1.8087904407686e-15 + (fConst0 * (1.25414294001131e-16 - fConst70)));
	fConst76 = (7.64033082180657e-15 + (fConst0 * (5.05613478219161e-16 - fConst68)));
	fConst77 = (5.00594475444762e-22 * fConst0);
	fConst78 = ((fConst0 * (9.55041352725816e-16 + (fConst0 * (fConst77 - 1.51695295589323e-21)))) - 1.44703235261488e-14);
	fConst79 = (1.44703235261488e-14 + (fConst0 * ((fConst0 * (1.51695295589323e-21 - fConst77)) - 9.55041352725816e-16)));
	fConst80 = (1.78417005350826e-19 * fConst0);
	fConst81 = (1.01122695643832e-15 + fConst80);
	fConst82 = (1.52806616436131e-14 + (fConst0 * (0 - fConst81)));
	fConst83 = (7.9650448817333e-19 * fConst0);
	fConst84 = (2.50828588002261e-16 + fConst83);
	fConst85 = (3.61758088153719e-15 + (fConst0 * (0 - fConst84)));
	fConst86 = (2.23479676537841e-21 * fConst0);
	fConst87 = (9.62549945902227e-30 + (fConst0 * ((fConst0 * (fConst86 - 6.77211141023765e-21)) - 6.35282964295466e-31)));
	fConst88 = ((fConst0 * (6.35282964295466e-31 + (fConst0 * (6.77211141023765e-21 - fConst86)))) - 9.62549945902227e-30);
	fConst89 = ((fConst0 * fConst84) - 3.61758088153719e-15);
	fConst90 = ((fConst0 * fConst81) - 1.52806616436131e-14);
	fConst91 = (7.58476477946615e-22 + fConst13);
	fConst92 = (7.23516176307441e-15 + (fConst0 * (4.77520676362908e-16 + (fConst0 * (0 - fConst91)))));
	fConst93 = ((fConst0 * ((fConst0 * fConst91) - 4.77520676362908e-16)) - 7.23516176307441e-15);
	fConst94 = (5.05613478219161e-16 + fConst16);
	fConst95 = ((fConst0 * (0 - fConst94)) - 7.64033082180657e-15);
	fConst96 = (1.25414294001131e-16 + fConst18);
	fConst97 = ((fConst0 * (0 - fConst96)) - 1.8087904407686e-15);
	fConst98 = (3.38605570511882e-21 + fConst20);
	fConst99 = ((fConst0 * ((fConst0 * (0 - fConst98)) - 3.17641482147733e-31)) - 4.81274972951113e-30);
	fConst100 = (4.81274972951113e-30 + (fConst0 * (3.17641482147733e-31 + (fConst0 * fConst98))));
	fConst101 = (1.8087904407686e-15 + (fConst0 * fConst96));
	fConst102 = (7.64033082180657e-15 + (fConst0 * fConst94));
	fConst103 = (1.51695295589323e-21 + fConst77);
	fConst104 = ((fConst0 * ((fConst0 * (0 - fConst103)) - 9.55041352725816e-16)) - 1.44703235261488e-14);
	fConst105 = (1.44703235261488e-14 + (fConst0 * (9.55041352725816e-16 + (fConst0 * fConst103))));
	fConst106 = (1.52806616436131e-14 + (fConst0 * (1.01122695643832e-15 - fConst80)));
	fConst107 = (3.61758088153719e-15 + (fConst0 * (2.50828588002261e-16 - fConst83)));
	fConst108 = (6.77211141023765e-21 + fConst86);
	fConst109 = (9.62549945902227e-30 + (fConst0 * (6.35282964295466e-31 + (fConst0 * (0 - fConst108)))));
	fConst110 = ((fConst0 * ((fConst0 * fConst108) - 6.35282964295466e-31)) - 9.62549945902227e-30);
	fConst111 = ((fConst0 * (fConst83 - 2.50828588002261e-16)) - 3.61758088153719e-15);
	fConst112 = ((fConst0 * (fConst80 - 1.01122695643832e-15)) - 1.52806616436131e-14);
	fConst113 = (2.27542943383984e-21 + fConst65);
	fConst114 = (7.23516176307441e-15 + (fConst0 * ((fConst0 * fConst113) - 4.77520676362908e-16)));
	fConst115 = ((fConst0 * (4.77520676362908e-16 + (fConst0 * (0 - fConst113)))) - 7.23516176307441e-15);
	fConst116 = (5.05613478219161e-16 + fConst68);
	fConst117 = ((fConst0 * fConst116) - 7.64033082180657e-15);
	fConst118 = (1.25414294001131e-16 + fConst70);
	fConst119 = ((fConst0 * fConst118) - 1.8087904407686e-15);
	fConst120 = (1.01581671153565e-20 + fConst72);
	fConst121 = ((fConst0 * (3.17641482147733e-31 + (fConst0 * fConst120))) - 4.81274972951113e-30);
	fConst122 = (4.81274972951113e-30 + (fConst0 * ((fConst0 * (0 - fConst120)) - 3.17641482147733e-31)));
	fConst123 = (1.8087904407686e-15 + (fConst0 * (0 - fConst118)));
	fConst124 = (7.64033082180657e-15 + (fConst0 * (0 - fConst116)));
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
		fRec0[0] = (fSlow0 + (0.993 * fRec0[1]));
		fRec1[0] = (fSlow1 + (0.993 * fRec1[1]));
		double fTemp0 = (fConst12 + ((fRec0[0] * ((fConst0 * (fConst10 + (fConst8 * fRec0[0]))) - 1.79092681198507e-15)) + (fRec1[0] * (fConst6 + (fRec0[0] * (1.19130474372322e-30 + (fConst0 * (fConst4 + (fConst2 * fRec0[0])))))))));
		fRec2[0] = (fSlow2 + (0.993 * fRec2[1]));
		fRec3[0] = ((double)input0[i] - ((((((fRec3[1] * (fConst64 + ((fRec0[0] * ((fConst0 * (fConst63 + (fConst62 * fRec0[0]))) - 8.95463405992537e-15)) + (fRec1[0] * (fConst61 + (fRec0[0] * (5.9565237186161e-30 + (fConst0 * (fConst60 + (fConst59 * fRec0[0])))))))))) + (fRec3[2] * (fConst58 + ((fRec0[0] * ((fConst0 * (fConst57 + (fConst56 * fRec0[0]))) - 1.79092681198507e-14)) + (fRec1[0] * (fConst55 + (fRec0[0] * (1.19130474372322e-29 + (fConst0 * (fConst54 + (fConst53 * fRec0[0]))))))))))) + (fRec3[3] * (fConst52 + ((fRec0[0] * ((fConst0 * (fConst50 + (fConst49 * fRec0[0]))) - 1.79092681198507e-14)) + (fRec1[0] * (fConst47 + (fRec0[0] * (1.19130474372322e-29 + (fConst0 * (fConst45 + (fConst44 * fRec0[0]))))))))))) + (fRec3[4] * (fConst42 + ((fRec0[0] * ((fConst0 * (fConst40 + (fConst38 * fRec0[0]))) - 8.95463405992537e-15)) + (fRec1[0] * (fConst36 + (fRec0[0] * (5.9565237186161e-30 + (fConst0 * (fConst34 + (fConst32 * fRec0[0]))))))))))) + (fRec3[5] * (fConst30 + ((fRec0[0] * ((fConst0 * (fConst29 + (fConst28 * fRec0[0]))) - 1.79092681198507e-15)) + (fRec1[0] * (fConst27 + (fRec0[0] * (1.19130474372322e-30 + (fConst0 * (fConst26 + (fConst25 * fRec0[0]))))))))))) / fTemp0));
		fRec4[0] = (fSlow3 + (0.993 * fRec4[1]));
		output0[i] = (FAUSTFLOAT)(fConst125 * ((fRec4[0] * (((((fRec3[1] * (fConst124 + ((fRec1[0] * (fConst123 + ((fRec0[0] * (fConst122 + (fConst121 * fRec2[0]))) + (fConst119 * fRec2[0])))) + ((fConst117 * fRec2[0]) + (fRec0[0] * (fConst115 + (fConst114 * fRec2[0]))))))) + ((fRec3[2] * (fConst112 + (((fRec1[0] * (fConst111 + ((fRec0[0] * (fConst110 + (fConst109 * fRec2[0]))) + (fConst107 * fRec2[0])))) + (fConst106 * fRec2[0])) + (fRec0[0] * (fConst105 + (fConst104 * fRec2[0])))))) + (fRec3[0] * (fConst102 + ((fRec1[0] * (fConst101 + ((fRec0[0] * (fConst100 + (fConst99 * fRec2[0]))) + (fConst97 * fRec2[0])))) + ((fConst95 * fRec2[0]) + (fRec0[0] * (fConst93 + (fConst92 * fRec2[0]))))))))) + (fRec3[3] * (fConst90 + ((fRec1[0] * (fConst89 + ((fRec0[0] * (fConst88 + (fConst87 * fRec2[0]))) + (fConst85 * fRec2[0])))) + ((fConst82 * fRec2[0]) + (fRec0[0] * (fConst79 + (fConst78 * fRec2[0])))))))) + (fRec3[4] * (fConst76 + ((fRec1[0] * (fConst75 + ((fRec0[0] * (fConst74 + (fConst73 * fRec2[0]))) + (fConst71 * fRec2[0])))) + ((fConst69 * fRec2[0]) + (fRec0[0] * (fConst67 + (fConst66 * fRec2[0])))))))) + (fRec3[5] * (fConst24 + ((fRec1[0] * (fConst23 + ((fRec0[0] * (fConst22 + (fConst21 * fRec2[0]))) + (fConst19 * fRec2[0])))) + ((fConst17 * fRec2[0]) + (fRec0[0] * (fConst15 + (fConst14 * fRec2[0]))))))))) / fTemp0));
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
