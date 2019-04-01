// generated from file '../src/LV2/faust/gx_w20.dsp' by dsp2cc:
// Code generated with Faust 2.15.11 (https://faust.grame.fr)


namespace gx_w20 {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
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
	double fRec1[6];
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
	id = "w20";
	name = N_("Westbury W-20");
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
	for (int l2 = 0; (l2 < 6); l2 = (l2 + 1)) fRec1[l2] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSamplingFreq)));
	fConst1 = (0.10000000000000001 * fConst0);
	fConst2 = (1.7560959935176299e-24 * fConst0);
	fConst3 = ((((((((-1.7500688529175899e-19 - fConst2) * fConst0) + -3.0491222395848099e-17) * fConst0) + 2.1817595880032998e-15) * fConst0) + 1.17289385123824e-13) * fConst0);
	fConst4 = (4.9645263801017403e-23 * fConst0);
	fConst5 = (((((((1.30248953220977e-20 - fConst4) * fConst0) + 4.0201625720155398e-19) * fConst0) + -7.8192912500269797e-18) * fConst0) + -7.79694556880737e-22);
	fConst6 = (5.1401359794534997e-23 * fConst0);
	fConst7 = (((((((fConst6 + 2.5096226055034102e-21) * fConst0) + 1.56385834712324e-20) * fConst0) + -5.1979559242204503e-25) * fConst0) + 4.06793321469724e-35);
	fConst8 = (3.5121919870352503e-24 * fConst0);
	fConst9 = ((((((((fConst8 + 1.16671256861173e-19) * fConst0) + -6.0982444791696099e-17) * fConst0) + -4.3635191760065902e-15) * fConst0) + 7.8192923415882398e-14) * fConst0);
	fConst10 = (9.9290527602034806e-23 * fConst0);
	fConst11 = (((((((fConst10 + -8.6832635480650997e-21) * fConst0) + 8.0403251440310796e-19) * fConst0) + 1.5638582500053999e-17) * fConst0) + -5.1979637125382397e-22);
	fConst12 = (1.0280271958906999e-22 * fConst0);
	fConst13 = (((((((-1.6730817370022699e-21 - fConst12) * fConst0) + 3.1277166942464801e-20) * fConst0) + 1.0395911848440901e-24) * fConst0) + 2.7119554764648299e-35);
	fConst14 = ((((((((1.16671256861173e-19 - fConst8) * fConst0) + 6.0982444791696099e-17) * fConst0) + -4.3635191760065902e-15) * fConst0) + -7.8192923415882398e-14) * fConst0);
	fConst15 = (((((((-8.6832635480650997e-21 - fConst10) * fConst0) + -8.0403251440310796e-19) * fConst0) + 1.5638582500053999e-17) * fConst0) + 5.1979637125382397e-22);
	fConst16 = (((((((fConst12 + -1.6730817370022699e-21) * fConst0) + -3.1277166942464801e-20) * fConst0) + 1.0395911848440901e-24) * fConst0) + -2.7119554764648299e-35);
	fConst17 = ((((((((fConst2 + -1.7500688529175899e-19) * fConst0) + 3.0491222395848099e-17) * fConst0) + 2.1817595880032998e-15) * fConst0) + -1.17289385123824e-13) * fConst0);
	fConst18 = (((((((fConst4 + 1.30248953220977e-20) * fConst0) + -4.0201625720155398e-19) * fConst0) + -7.8192912500269797e-18) * fConst0) + 7.79694556880737e-22);
	fConst19 = (((((((2.5096226055034102e-21 - fConst6) * fConst0) + -1.56385834712324e-20) * fConst0) + -5.1979559242204503e-25) * fConst0) + -4.06793321469724e-35);
	fConst20 = (3.5121919870352501e-25 * fConst0);
	fConst21 = ((((((((5.8335628430586305e-20 - fConst20) * fConst0) + -3.0491222395848099e-17) * fConst0) + 2.1817595880032998e-15) * fConst0) + -3.9096461707941199e-14) * fConst0);
	fConst22 = (9.9290527602034803e-24 * fConst0);
	fConst23 = (((((((-4.3416317740325499e-21 - fConst22) * fConst0) + 4.0201625720155398e-19) * fConst0) + -7.8192912500269797e-18) * fConst0) + 2.5989818562691199e-22);
	fConst24 = (1.0280271958907e-23 * fConst0);
	fConst25 = (((((((fConst24 + -8.3654086850113601e-22) * fConst0) + 1.56385834712324e-20) * fConst0) + -5.1979559242204503e-25) * fConst0) + -1.3559777382324101e-35);
	fConst26 = ((((((((fConst20 + 5.8335628430586305e-20) * fConst0) + 3.0491222395848099e-17) * fConst0) + 2.1817595880032998e-15) * fConst0) + 3.9096461707941199e-14) * fConst0);
	fConst27 = (((((((fConst22 + -4.3416317740325499e-21) * fConst0) + -4.0201625720155398e-19) * fConst0) + -7.8192912500269797e-18) * fConst0) + -2.5989818562691199e-22);
	fConst28 = (((((((-8.3654086850113601e-22 - fConst24) * fConst0) + -1.56385834712324e-20) * fConst0) + -5.1979559242204503e-25) * fConst0) + 1.3559777382324101e-35);
	fConst29 = (1.33767398764352e-28 * fConst0);
	fConst30 = (((((fConst29 + 8.4883795584658001e-24) * fConst0) + 3.1080196209938997e-20) * fConst0) + 1.15566670466208e-17);
	fConst31 = (4.25008767113306e-21 * fConst0);
	fConst32 = (((((((fConst31 + 2.1314833830678999e-17) * fConst0) + 3.2197737468686698e-16) * fConst0) + 8.4212352539407002e-21) * fConst0) + -5.4813752919431001e-32);
	fConst33 = ((((((-6.43954751474457e-20 - fConst31) * fConst0) + -6.7691805513013103e-24) * fConst0) + 1.2059025642274799e-34) * fConst0);
	fConst34 = (4.0130219629305702e-28 * fConst0);
	fConst35 = (((((-8.4883795584658001e-24 - fConst34) * fConst0) + 3.1080196209938997e-20) * fConst0) + 3.4670001139862498e-17);
	fConst36 = (2.1250438355665299e-20 * fConst0);
	fConst37 = (((((((-6.3944501492036898e-17 - fConst36) * fConst0) + -3.2197737468686698e-16) * fConst0) + 8.4212352539407002e-21) * fConst0) + -1.64441258758293e-31);
	fConst38 = ((((((fConst36 + 1.93186425442337e-19) * fConst0) + 6.7691805513013103e-24) * fConst0) + 1.2059025642274799e-34) * fConst0);
	fConst39 = (2.6753479752870399e-28 * fConst0);
	fConst40 = (((((fConst39 + -1.69767591169316e-23) * fConst0) + -6.2160392419877995e-20) * fConst0) + 2.3113334093241699e-17);
	fConst41 = (4.2500876711330597e-20 * fConst0);
	fConst42 = (((((((fConst41 + 4.2629667661357899e-17) * fConst0) + -6.4395474937373297e-16) * fConst0) + -1.68424705078814e-20) * fConst0) + -1.09627505838862e-31);
	fConst43 = ((((((-1.2879095029489099e-19 - fConst41) * fConst0) + 1.35383611026026e-23) * fConst0) + -2.4118051284549701e-34) * fConst0);
	fConst44 = (((((fConst39 + 1.69767591169316e-23) * fConst0) + -6.2160392419877995e-20) * fConst0) + -2.3113334093241699e-17);
	fConst45 = (((((((4.2629667661357899e-17 - fConst41) * fConst0) + 6.4395474937373297e-16) * fConst0) + -1.68424705078814e-20) * fConst0) + 1.09627505838862e-31);
	fConst46 = ((((((fConst41 + -1.2879095029489099e-19) * fConst0) + -1.35383611026026e-23) * fConst0) + -2.4118051284549701e-34) * fConst0);
	fConst47 = (((((8.4883795584658001e-24 - fConst34) * fConst0) + 3.1080196209938997e-20) * fConst0) + -3.4670001139862498e-17);
	fConst48 = (((((((fConst36 + -6.3944501492036898e-17) * fConst0) + 3.2197737468686698e-16) * fConst0) + 8.4212352539407002e-21) * fConst0) + 1.64441258758293e-31);
	fConst49 = ((((((1.93186425442337e-19 - fConst36) * fConst0) + -6.7691805513013103e-24) * fConst0) + 1.2059025642274799e-34) * fConst0);
	fConst50 = (((((fConst29 + -8.4883795584658001e-24) * fConst0) + 3.1080196209938997e-20) * fConst0) + -1.15566670466208e-17);
	fConst51 = (((((((2.1314833830678999e-17 - fConst31) * fConst0) + -3.2197737468686698e-16) * fConst0) + 8.4212352539407002e-21) * fConst0) + 5.4813752919431001e-32);
	fConst52 = ((((((fConst31 + -6.43954751474457e-20) * fConst0) + 6.7691805513013103e-24) * fConst0) + 1.2059025642274799e-34) * fConst0);
	fVslider0 = FAUSTFLOAT(0.5);
	fVslider1 = FAUSTFLOAT(0.5);
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fVslider0 (*fVslider0_)
#define fVslider1 (*fVslider1_)
	double fSlow0 = (0.004073836948085289 * (std::exp(double(fVslider0)) + -1.0));
	double fSlow1 = (0.004073836948085289 * (std::exp(double(fVslider1)) + -1.0));
	for (int i = 0; (i < count); i = (i + 1)) {
		fRec0[0] = (fSlow0 + (0.99299999999999999 * fRec0[1]));
		fRec2[0] = (fSlow1 + (0.99299999999999999 * fRec2[1]));
		double fTemp0 = (fConst26 + ((fRec2[0] * ((fConst0 * (fConst27 + (fConst28 * fRec2[0]))) + -6.1635351737836994e-33)) + 1.2994900009538301e-18));
		fRec1[0] = (double(input0[i]) - ((((((fRec1[1] * (fConst3 + ((fRec2[0] * ((fConst0 * (fConst5 + (fConst7 * fRec2[0]))) + -3.0817675868918503e-32)) + 6.4974500047691703e-18))) + (fRec1[2] * (fConst9 + ((fRec2[0] * ((fConst0 * (fConst11 + (fConst13 * fRec2[0]))) + -6.1635351737837005e-32)) + 1.2994900009538301e-17)))) + (fRec1[3] * (fConst14 + ((fRec2[0] * ((fConst0 * (fConst15 + (fConst16 * fRec2[0]))) + -6.1635351737837005e-32)) + 1.2994900009538301e-17)))) + (fRec1[4] * (fConst17 + ((fRec2[0] * ((fConst0 * (fConst18 + (fConst19 * fRec2[0]))) + -3.0817675868918503e-32)) + 6.4974500047691703e-18)))) + (fRec1[5] * (fConst21 + ((fRec2[0] * ((fConst0 * (fConst23 + (fConst25 * fRec2[0]))) + -6.1635351737836994e-33)) + 1.2994900009538301e-18)))) / fTemp0));
		output0[i] = FAUSTFLOAT((fConst1 * ((fRec0[0] * ((((((fRec1[0] * (fConst30 + (fRec2[0] * (fConst32 + (fConst33 * fRec2[0]))))) + (fRec1[1] * (fConst35 + (fRec2[0] * (fConst37 + (fConst38 * fRec2[0])))))) + (fRec1[2] * (fConst40 + (fRec2[0] * (fConst42 + (fConst43 * fRec2[0])))))) + (fRec1[3] * (fConst44 + (fRec2[0] * (fConst45 + (fConst46 * fRec2[0])))))) + (fRec1[4] * (fConst47 + (fRec2[0] * (fConst48 + (fConst49 * fRec2[0])))))) + (fRec1[5] * (fConst50 + (fRec2[0] * (fConst51 + (fConst52 * fRec2[0]))))))) / fTemp0)));
		fRec0[1] = fRec0[0];
		fRec2[1] = fRec2[0];
		for (int j0 = 5; (j0 > 0); j0 = (j0 - 1)) {
			fRec1[j0] = fRec1[(j0 - 1)];
		}
	}
#undef fVslider0
#undef fVslider1
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case GAIN: 
		fVslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case LEVEL: 
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
   GAIN, 
   LEVEL, 
} PortIndex;
*/

} // end namespace gx_w20
