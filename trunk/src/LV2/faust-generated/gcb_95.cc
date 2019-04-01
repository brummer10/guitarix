// generated from file '../src/LV2/faust/gcb_95.dsp' by dsp2cc:
// Code generated with Faust 2.15.11 (https://faust.grame.fr)


namespace gcb_95 {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	double fConst0;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec0[2];
	double fConst1;
	double fConst2;
	double fVec0[2];
	double fConst3;
	double fRec2[2];
	double fConst4;
	double fConst5;
	double fConst6;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec3[2];
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
	double fRec1[5];
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
	id = "GCB_95";
	name = N_("GCB 95");
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
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fVec0[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec2[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fRec3[l3] = 0.0;
	for (int l4 = 0; (l4 < 5); l4 = (l4 + 1)) fRec1[l4] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSamplingFreq)));
	fConst1 = (716.61401544811906 / fConst0);
	fConst2 = (1.0 / (fConst1 + 1.0));
	fConst3 = (1.0 - fConst1);
	fConst4 = (4.3527609462957e-20 * fConst0);
	fConst5 = mydsp_faustpower2_f(fConst0);
	fConst6 = (((-5.61970963366905e-17 - fConst4) * fConst5) + 2.5838272024034701e-11);
	fConst7 = (1.5506590744581601e-18 * fConst0);
	fConst8 = (((-5.8415292970762599e-17 - fConst7) * fConst5) + 4.3350363297959298e-12);
	fConst9 = (2.7869182298057999e-19 * fConst0);
	fConst10 = ((fConst9 + 1.8601228447531002e-17) * fConst5);
	fConst11 = ((6.5291414194435498e-20 * fConst5) + -1.08942422737996e-12);
	fConst12 = ((2.3259886116872401e-18 * fConst5) + -1.5366469234055e-13);
	fConst13 = (1.90741598511021e-13 - (4.1803773447087001e-19 * fConst5));
	fConst14 = (((5.61970963366905e-17 - fConst4) * fConst5) + -2.5838272024034701e-11);
	fConst15 = (((5.8415292970762599e-17 - fConst7) * fConst5) + -4.3350363297959298e-12);
	fConst16 = ((fConst9 + -1.8601228447531002e-17) * fConst5);
	fConst17 = (1.08819023657393e-20 * fConst0);
	fConst18 = (((((fConst17 + -2.8098548168345201e-17) * fConst0) + 5.4471211368998203e-13) * fConst0) + -1.29191360120173e-11);
	fConst19 = (3.8766476861454002e-19 * fConst0);
	fConst20 = (((((fConst19 + -2.9207646485381299e-17) * fConst0) + 7.6832346170274799e-14) * fConst0) + -2.16751816489796e-12);
	fConst21 = (6.9672955745144997e-20 * fConst0);
	fConst22 = ((((9.3006142237654807e-18 - fConst21) * fConst0) + -9.5370799255510498e-14) * fConst0);
	fConst23 = (((((fConst17 + 2.8098548168345201e-17) * fConst0) + 5.4471211368998203e-13) * fConst0) + 1.29191360120173e-11);
	fConst24 = (((((fConst19 + 2.9207646485381299e-17) * fConst0) + 7.6832346170274799e-14) * fConst0) + 2.16751816489796e-12);
	fConst25 = ((((-9.3006142237654807e-18 - fConst21) * fConst0) + -9.5370799255510498e-14) * fConst0);
	fConst26 = (7.4135038833437398e-21 * fConst0);
	fConst27 = (((((-2.4741854120550598e-16 - fConst26) * fConst0) + -3.6967278749692501e-13) * fConst0) + -1.8397056665288999e-12);
	fConst28 = (1.9665324877018799e-21 * fConst0);
	fConst29 = (((((-5.48942867863191e-17 - fConst28) * fConst0) + -8.2143235332114198e-14) * fConst0) + -1.7815570487859499e-12);
	fConst30 = (1.9683443716351199e-21 * fConst0);
	fConst31 = ((((fConst30 + 5.4858751551646897e-17) * fConst0) + 8.0947049327271397e-14) * fConst0);
	fConst32 = (2.9654015533375001e-20 * fConst0);
	fConst33 = (((fConst32 + 4.9483708241101304e-16) * fConst5) + -3.67941133305779e-12);
	fConst34 = (7.86612995080753e-21 * fConst0);
	fConst35 = (((fConst34 + 1.09788573572638e-16) * fConst5) + -3.5631140975718902e-12);
	fConst36 = (7.8733774865404599e-21 * fConst0);
	fConst37 = ((-1.09717503103294e-16 - fConst36) * fConst5);
	fConst38 = (7.39345574993849e-13 - (4.44810233000624e-20 * fConst5));
	fConst39 = (1.6428647066422799e-13 - (1.17991949262113e-20 * fConst5));
	fConst40 = ((1.18100662298107e-20 * fConst5) + -1.61894098654543e-13);
	fConst41 = (((fConst32 + -4.9483708241101304e-16) * fConst5) + 3.67941133305779e-12);
	fConst42 = (((fConst34 + -1.09788573572638e-16) * fConst5) + 3.5631140975718902e-12);
	fConst43 = ((1.09717503103294e-16 - fConst36) * fConst5);
	fConst44 = (((((2.4741854120550598e-16 - fConst26) * fConst0) + -3.6967278749692501e-13) * fConst0) + 1.8397056665288999e-12);
	fConst45 = (((((5.48942867863191e-17 - fConst28) * fConst0) + -8.2143235332114198e-14) * fConst0) + 1.7815570487859499e-12);
	fConst46 = ((((fConst30 + -5.4858751551646897e-17) * fConst0) + 8.0947049327271397e-14) * fConst0);
	fVslider0 = FAUSTFLOAT(0.0);
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
	double fSlow0 = (0.0070000000000000062 * std::pow(10.0, (0.050000000000000003 * double(fVslider0))));
	double fSlow1 = (4.748558434412966e-05 * (std::exp((5.0 * (1.0 - double(fVslider1)))) + -1.0));
	for (int i = 0; (i < count); i = (i + 1)) {
		fRec0[0] = (fSlow0 + (0.99299999999999999 * fRec0[1]));
		double fTemp0 = double(input0[i]);
		fVec0[0] = fTemp0;
		fRec2[0] = (fConst2 * ((fTemp0 - fVec0[1]) + (fConst3 * fRec2[1])));
		fRec3[0] = (fSlow1 + (0.99299999999999999 * fRec3[1]));
		double fTemp1 = ((fConst0 * (fConst23 + (fRec3[0] * (fConst24 + (fConst25 * fRec3[0]))))) + 4.9261776474953702e-11);
		fRec1[0] = (fRec2[0] - (((((fRec1[1] * ((fConst0 * (fConst6 + (fRec3[0] * (fConst8 + (fConst10 * fRec3[0]))))) + 1.9704710589981499e-10)) + (fRec1[2] * ((fConst5 * (fConst11 + (fRec3[0] * (fConst12 + (fConst13 * fRec3[0]))))) + 2.9557065884972299e-10))) + (fRec1[3] * ((fConst0 * (fConst14 + (fRec3[0] * (fConst15 + (fConst16 * fRec3[0]))))) + 1.9704710589981499e-10))) + (fRec1[4] * ((fConst0 * (fConst18 + (fRec3[0] * (fConst20 + (fConst22 * fRec3[0]))))) + 4.9261776474953702e-11))) / fTemp1));
		output0[i] = FAUSTFLOAT((fConst0 * ((fRec0[0] * (((((fRec1[0] * (fConst27 + (fRec3[0] * (fConst29 + (fConst31 * fRec3[0]))))) + (fRec1[1] * (fConst33 + (fRec3[0] * (fConst35 + (fConst37 * fRec3[0])))))) + (fConst0 * (fRec1[2] * (fConst38 + (fRec3[0] * (fConst39 + (fConst40 * fRec3[0]))))))) + (fRec1[3] * (fConst41 + (fRec3[0] * (fConst42 + (fConst43 * fRec3[0])))))) + (fRec1[4] * (fConst44 + (fRec3[0] * (fConst45 + (fConst46 * fRec3[0]))))))) / fTemp1)));
		fRec0[1] = fRec0[0];
		fVec0[1] = fVec0[0];
		fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		for (int j0 = 4; (j0 > 0); j0 = (j0 - 1)) {
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
	case VOLUME: 
		fVslider0_ = (float*)data; // , 0.0, -20.0, 4.0, 0.10000000000000001 
		break;
	case HOTPOTZ: 
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
   VOLUME, 
   HOTPOTZ, 
} PortIndex;
*/

} // end namespace gcb_95
