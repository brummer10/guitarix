// generated from file '../src/faust/jenwah.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)


namespace jenwah {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	int 	iVec0[2];
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fConst4;
	double 	fRec2[2];
	double 	fRec1[2];
	double 	fRec0[2];
	double 	fConst5;
	double 	fConst6;
	double 	fRec5[2];
	double 	fConst7;
	double 	fConst8;
	double 	fRec4[2];
	double 	fRec3[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec6[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
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
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fConst44;
	double 	fConst45;
	double 	fConst46;
	double 	fVec1[2];
	double 	fConst47;
	double 	fConst48;
	double 	fRec8[2];
	double 	fRec7[7];
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
	void clear_state_f();
	void init(unsigned int samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static void init_static(unsigned int samplingFreq, PluginDef*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef*);
	static int register_params_static(const ParamReg& reg);
	static void del_instance(PluginDef *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginDef() {
	version = PLUGINDEF_VERSION;
	flags = 0;
	id = "jenwah";
	name = N_("Jen Wah");
	groups = 0;
	description = N_("Jen Wah"); // description (tooltip)
	category = N_("Guitar Effects");       // category
	shortname = N_("Jen Wah");     // shortname
	mono_audio = compute_static;
	stereo_audio = 0;
	set_samplerate = init_static;
	activate_plugin = 0;
	register_params = register_params_static;
	load_ui = 0;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int i=0; i<2; i++) iVec0[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<7; i++) fRec7[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = double(iConst0);
	fConst2 = (5.06729438510915e-30 * fConst1);
	fConst3 = (3.83962880191652e-17 + (fConst1 * (5.19747968243949e-18 + (fConst1 * (1.86059812765692e-19 + (fConst1 * (2.55792255245646e-22 + (fConst1 * (1.75902134761561e-26 + fConst2)))))))));
	fConst4 = (0.10471975511965977 / double(iConst0));
	fConst5 = exp((0 - (1e+01 / double(iConst0))));
	fConst6 = (1.0 - fConst5);
	fConst7 = exp((0 - (1e+02 / double(iConst0))));
	fConst8 = (1.0 - fConst7);
	fConst9 = (2.99058068344367e-29 * fConst1);
	fConst10 = (fConst1 * ((fConst1 * ((fConst1 * ((fConst1 * (0 - (2.80670790745131e-26 + fConst9))) - 5.93685085752414e-23)) - 4.06379935456973e-20)) - 4.33319933521253e-19));
	fConst11 = (1.64867026615177e-28 * fConst1);
	fConst12 = (9.8481803073012e-18 + (fConst1 * (1.34455763292065e-18 + (fConst1 * (4.91860288753505e-20 + (fConst1 * (7.41293891074537e-23 + (fConst1 * (1.33928172058214e-25 + fConst11)))))))));
	fConst13 = (3.18327632166844e-30 * fConst1);
	fConst14 = ((fConst1 * (1.24894038761244e-20 + (fConst1 * ((fConst1 * (1.0511872826981e-25 - fConst13)) - 1.52009426668339e-22)))) - 7.39230423647202e-22);
	fConst15 = (1.82217902614682e-30 * fConst1);
	fConst16 = (fConst1 * ((fConst1 * (3.97330096911255e-23 + (fConst1 * (fConst15 - 2.88343830435939e-26)))) - 3.25261386404769e-21));
	fConst17 = (1.81642997288596e-30 * fConst1);
	fConst18 = ((fConst1 * (3.98756637137511e-21 + (fConst1 * ((fConst1 * (2.88488738607105e-26 - fConst17)) - 4.02405861356002e-23)))) - 6.03499692778005e-20);
	fConst19 = ((fConst1 * (5.19747968243949e-18 + (fConst1 * ((fConst1 * (2.55792255245646e-22 + (fConst1 * (fConst2 - 1.75902134761561e-26)))) - 1.86059812765692e-19)))) - 3.83962880191652e-17);
	fConst20 = (fConst1 * ((fConst1 * (4.06379935456973e-20 + (fConst1 * ((fConst1 * (2.80670790745131e-26 - fConst9)) - 5.93685085752414e-23)))) - 4.33319933521253e-19));
	fConst21 = ((fConst1 * (1.34455763292065e-18 + (fConst1 * ((fConst1 * (7.41293891074537e-23 + (fConst1 * (fConst11 - 1.33928172058214e-25)))) - 4.91860288753505e-20)))) - 9.8481803073012e-18);
	fConst22 = (3.04037663106549e-29 * fConst1);
	fConst23 = faustpower<2>(fConst1);
	fConst24 = ((fConst1 * (1.0394959364879e-17 + (fConst23 * ((fConst1 * (7.03608539046245e-26 - fConst22)) - 5.11584510491292e-22)))) - 1.53585152076661e-16);
	fConst25 = (1.7943484100662e-28 * fConst1);
	fConst26 = (fConst1 * ((fConst23 * (1.18737017150483e-22 + (fConst1 * (fConst25 - 1.12268316298052e-25)))) - 8.66639867042506e-19));
	fConst27 = (9.89202159691062e-28 * fConst1);
	fConst28 = ((fConst1 * (2.68911526584129e-18 + (fConst23 * ((fConst1 * (5.35712688232857e-25 - fConst27)) - 1.48258778214907e-22)))) - 3.93927212292048e-17);
	fConst29 = (7.60094157766373e-29 * fConst1);
	fConst30 = ((fConst1 * ((fConst1 * (5.58179438297077e-19 + (fConst1 * ((fConst1 * (fConst29 - 8.79510673807807e-26)) - 2.55792255245646e-22)))) - 5.19747968243949e-18)) - 1.91981440095826e-16);
	fConst31 = (4.48587102516551e-28 * fConst1);
	fConst32 = (fConst1 * (4.33319933521253e-19 + (fConst1 * ((fConst1 * (5.93685085752414e-23 + (fConst1 * (1.40335395372566e-25 - fConst31)))) - 1.21913980637092e-19))));
	fConst33 = (2.47300539922766e-27 * fConst1);
	fConst34 = ((fConst1 * ((fConst1 * (1.47558086626052e-19 + (fConst1 * ((fConst1 * (fConst33 - 6.69640860291072e-25)) - 7.41293891074537e-23)))) - 1.34455763292065e-18)) - 4.9240901536506e-17);
	fConst35 = ((fConst23 * (1.02316902098258e-21 - (1.01345887702183e-28 * fConst23))) - 2.0789918729758e-17);
	fConst36 = (1.73327973408501e-18 + (fConst23 * ((5.98116136688735e-28 * fConst23) - 2.37474034300966e-22)));
	fConst37 = ((fConst23 * (2.96517556429815e-22 - (3.29734053230354e-27 * fConst23))) - 5.37823053168259e-18);
	fConst38 = (1.91981440095826e-16 + (fConst1 * ((fConst1 * ((fConst1 * ((fConst1 * (8.79510673807807e-26 + fConst29)) - 2.55792255245646e-22)) - 5.58179438297077e-19)) - 5.19747968243949e-18)));
	fConst39 = (fConst1 * (4.33319933521253e-19 + (fConst1 * (1.21913980637092e-19 + (fConst1 * (5.93685085752414e-23 + (fConst1 * (0 - (1.40335395372566e-25 + fConst31)))))))));
	fConst40 = (4.9240901536506e-17 + (fConst1 * ((fConst1 * ((fConst1 * ((fConst1 * (6.69640860291072e-25 + fConst33)) - 7.41293891074537e-23)) - 1.47558086626052e-19)) - 1.34455763292065e-18)));
	fConst41 = (1.53585152076661e-16 + (fConst1 * (1.0394959364879e-17 + (fConst23 * ((fConst1 * (0 - (7.03608539046245e-26 + fConst22))) - 5.11584510491292e-22)))));
	fConst42 = (fConst1 * ((fConst23 * (1.18737017150483e-22 + (fConst1 * (1.12268316298052e-25 + fConst25)))) - 8.66639867042506e-19));
	fConst43 = (3.93927212292048e-17 + (fConst1 * (2.68911526584129e-18 + (fConst23 * ((fConst1 * (0 - (5.35712688232857e-25 + fConst27))) - 1.48258778214907e-22)))));
	fConst44 = (716.6140154481191 / double(iConst0));
	fConst45 = (1 + fConst44);
	fConst46 = (0.01 / fConst45);
	fConst47 = (1 - fConst44);
	fConst48 = (1.0 / fConst45);
	fConst49 = (1.90996579300106e-29 * fConst1);
	fConst50 = ((fConst23 * (3.04018853336678e-22 + (fConst1 * (fConst49 - 4.20474913079239e-25)))) - 1.4784608472944e-21);
	fConst51 = (1.09330741568809e-29 * fConst1);
	fConst52 = (fConst23 * ((fConst1 * (1.15337532174376e-25 - fConst51)) - 7.94660193822509e-23));
	fConst53 = (1.08985798373158e-29 * fConst1);
	fConst54 = ((fConst23 * (8.04811722712005e-23 + (fConst1 * (fConst53 - 1.15395495442842e-25)))) - 1.20699938555601e-19);
	fConst55 = (4.77491448250266e-29 * fConst1);
	fConst56 = (7.39230423647202e-22 + (fConst1 * ((fConst1 * (1.52009426668339e-22 + (fConst1 * (5.25593641349048e-25 - fConst55)))) - 3.74682116283731e-20)));
	fConst57 = (2.73326853922023e-29 * fConst1);
	fConst58 = (fConst1 * (9.75784159214306e-21 + (fConst1 * ((fConst1 * (fConst57 - 1.4417191521797e-25)) - 3.97330096911255e-23))));
	fConst59 = (2.72464495932894e-29 * fConst1);
	fConst60 = (6.03499692778005e-20 + (fConst1 * ((fConst1 * (4.02405861356002e-23 + (fConst1 * (1.44244369303552e-25 - fConst59)))) - 1.19626991141253e-20)));
	fConst61 = (2.95692169458881e-21 + (fConst23 * ((6.36655264333688e-29 * fConst23) - 6.08037706673355e-22)));
	fConst62 = (fConst23 * (1.58932038764502e-22 - (3.64435805229364e-29 * fConst23)));
	fConst63 = (2.41399877111202e-19 + (fConst23 * ((3.63285994577192e-29 * fConst23) - 1.60962344542401e-22)));
	fConst64 = (7.39230423647202e-22 + (fConst1 * (3.74682116283731e-20 + (fConst1 * (1.52009426668339e-22 + (fConst1 * (0 - (5.25593641349048e-25 + fConst55))))))));
	fConst65 = (fConst1 * ((fConst1 * ((fConst1 * (1.4417191521797e-25 + fConst57)) - 3.97330096911255e-23)) - 9.75784159214306e-21));
	fConst66 = (6.03499692778005e-20 + (fConst1 * (1.19626991141253e-20 + (fConst1 * (4.02405861356002e-23 + (fConst1 * (0 - (1.44244369303552e-25 + fConst59))))))));
	fConst67 = ((fConst23 * (3.04018853336678e-22 + (fConst1 * (4.20474913079239e-25 + fConst49)))) - 1.4784608472944e-21);
	fConst68 = (fConst23 * ((fConst1 * (0 - (1.15337532174376e-25 + fConst51))) - 7.94660193822509e-23));
	fConst69 = ((fConst23 * (8.04811722712005e-23 + (fConst1 * (1.15395495442842e-25 + fConst53)))) - 1.20699938555601e-19);
	fConst70 = ((fConst1 * ((fConst1 * ((fConst1 * (0 - (1.0511872826981e-25 + fConst13))) - 1.52009426668339e-22)) - 1.24894038761244e-20)) - 7.39230423647202e-22);
	fConst71 = (fConst1 * (3.25261386404769e-21 + (fConst1 * (3.97330096911255e-23 + (fConst1 * (2.88343830435939e-26 + fConst15))))));
	fConst72 = ((fConst1 * ((fConst1 * ((fConst1 * (0 - (2.88488738607105e-26 + fConst17))) - 4.02405861356002e-23)) - 3.98756637137511e-21)) - 6.03499692778005e-20);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
#define fslider2 (*fslider2_)
#define fslider3 (*fslider3_)
	double 	fSlow0 = (fConst4 * double(fslider0));
	double 	fSlow1 = (0.007000000000000006 * (1 - double(fslider1)));
	int 	iSlow2 = int(double(fslider2));
	double 	fSlow3 = double(fslider3);
	double 	fSlow4 = (fConst46 * fSlow3);
	double 	fSlow5 = (0.01 * fSlow3);
	double 	fSlow6 = (1 - fSlow5);
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		fRec2[0] = (fRec2[1] + (fSlow0 * (0 - fRec0[1])));
		fRec1[0] = ((1 + (fRec1[1] + (fSlow0 * fRec2[0]))) - iVec0[1]);
		fRec0[0] = fRec1[0];
		double fTemp0 = (double)input0[i];
		double fTemp1 = fabs(fTemp0);
		fRec5[0] = ((fConst5 * max(fTemp1, fRec5[1])) + (fConst6 * fTemp1));
		fRec4[0] = ((fConst7 * fRec4[1]) + (fConst8 * fRec5[0]));
		fRec3[0] = ((0.993 * fRec3[1]) + (0.007000000000000006 * max(0.1, min(0.99, fRec4[0]))));
		fRec6[0] = ((0.993 * fRec6[1]) + fSlow1);
		double fTemp2 = ((iSlow2==0)? fRec6[0] : ((iSlow2==1)?fRec3[0]:(1 - max(0.01, min(0.98, (0.5 * (1 + fRec0[0])))))) );
		double fTemp3 = (2.23822279711391e-18 + (fConst1 * ((fTemp2 * (fConst12 + (fConst10 * fTemp2))) + fConst3)));
		fVec1[0] = (fSlow4 * fTemp0);
		fRec8[0] = ((fConst48 * ((fSlow5 * fTemp0) + (fConst47 * fRec8[1]))) - fVec1[1]);
		fRec7[0] = (fRec8[0] - (((((((fRec7[1] * (1.34293367826835e-17 + (fConst1 * ((fTemp2 * (fConst43 + (fConst42 * fTemp2))) + fConst41)))) + (fRec7[2] * (3.35733419567086e-17 + (fConst1 * ((fTemp2 * (fConst40 + (fConst39 * fTemp2))) + fConst38))))) + (fRec7[3] * (4.47644559422782e-17 + (fConst23 * ((fTemp2 * (fConst37 + (fConst36 * fTemp2))) + fConst35))))) + (fRec7[4] * (3.35733419567086e-17 + (fConst1 * ((fTemp2 * (fConst34 + (fConst32 * fTemp2))) + fConst30))))) + (fRec7[5] * (1.34293367826835e-17 + (fConst1 * ((fTemp2 * (fConst28 + (fConst26 * fTemp2))) + fConst24))))) + (fRec7[6] * (2.23822279711391e-18 + (fConst1 * ((fTemp2 * (fConst21 + (fConst20 * fTemp2))) + fConst19))))) / fTemp3));
		output0[i] = (FAUSTFLOAT)((fSlow6 * fTemp0) + (fConst23 * ((((((((fRec7[0] * ((fTemp2 * (fConst72 + (fConst71 * fTemp2))) + fConst70)) + (fRec7[1] * ((fTemp2 * (fConst69 + (fConst68 * fTemp2))) + fConst67))) + (fRec7[2] * ((fTemp2 * (fConst66 + (fConst65 * fTemp2))) + fConst64))) + (fRec7[3] * ((fTemp2 * (fConst63 + (fConst62 * fTemp2))) + fConst61))) + (fRec7[4] * ((fTemp2 * (fConst60 + (fConst58 * fTemp2))) + fConst56))) + (fRec7[5] * ((fTemp2 * (fConst54 + (fConst52 * fTemp2))) + fConst50))) + (fRec7[6] * ((fTemp2 * (fConst18 + (fConst16 * fTemp2))) + fConst14))) / fTemp3)));
		// post processing
		for (int i=6; i>0; i--) fRec7[i] = fRec7[i-1];
		fRec8[1] = fRec8[0];
		fVec1[1] = fVec1[0];
		fRec6[1] = fRec6[0];
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		iVec0[1] = iVec0[0];
	}
#undef fslider0
#undef fslider1
#undef fslider2
#undef fslider3
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	fslider1_ = reg.registerVar("wah.Wah","","SA","",&fslider1, 0.0, 0.0, 1.0, 0.01);
	fslider0_ = reg.registerVar("wah.freq",N_("Alien Freq"),"SA",N_("LFO in Beats per Minute"),&fslider0, 24.0, 24.0, 3.6e+02, 1.0);
	static const value_pair fslider2_values[] = {{"manual"},{"auto"},{"alien"},{0}};
	fslider2_ = reg.registerSharedEnumVar("wah.mode","","SA","",fslider2_values,&fslider2, 0.0, 0.0, 2.0, 1.0);
	fslider3_ = reg.registerVar("wah.wet_dry",N_("dry/wet"),"SA","",&fslider3, 1e+02, 0.0, 1e+02, 1.0);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

PluginDef *plugin() {
	return new Dsp();
}

void Dsp::del_instance(PluginDef *p)
{
	delete static_cast<Dsp*>(p);
}

} // end namespace jenwah
