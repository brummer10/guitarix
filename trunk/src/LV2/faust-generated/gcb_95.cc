// generated from file '../src/LV2/faust/gcb_95.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace gcb_95 {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec0[2];
	double fConst2;
	double fConst3;
	double fConst5;
	double fConst7;
	double fConst9;
	double fConst11;
	double fConst13;
	double fConst14;
	double fConst15;
	double fConst16;
	double fConst19;
	double fConst21;
	double fConst23;
	double fConst24;
	double fConst25;
	double fConst26;
	double fConst27;
	double fConst28;
	double fConst29;
	double fConst31;
	double fVec0[2];
	double fConst32;
	double fRec2[2];
	double fRec1[5];
	double fConst34;
	double fConst36;
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
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec3[2];

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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec0[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fVec0[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec2[l2] = 0.0;
	for (int l3 = 0; l3 < 5; l3 = l3 + 1) fRec1[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fRec3[l4] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = 6.9672955745145e-20 * fConst0;
	fConst2 = mydsp_faustpower2_f(fConst0);
	fConst3 = fConst2 * (fConst0 * (-9.30061422376548e-18 - fConst1) + -9.53707992555105e-14);
	double fConst4 = 3.8766476861454e-19 * fConst0;
	fConst5 = fConst0 * (fConst0 * (fConst0 * (fConst4 + 2.92076464853813e-17) + 7.68323461702748e-14) + 2.16751816489796e-12);
	double fConst6 = 1.08819023657393e-20 * fConst0;
	fConst7 = fConst0 * (fConst0 * (fConst0 * (fConst6 + 2.80985481683452e-17) + 5.44712113689982e-13) + 1.29191360120173e-11);
	double fConst8 = 1.96834437163512e-21 * fConst0;
	fConst9 = fConst2 * (fConst0 * (fConst8 + -5.48587515516469e-17) + 8.09470493272714e-14);
	double fConst10 = 1.96653248770188e-21 * fConst0;
	fConst11 = fConst0 * (fConst0 * (fConst0 * (5.48942867863191e-17 - fConst10) + -8.21432353321142e-14) + 1.78155704878595e-12);
	double fConst12 = 7.41350388334374e-21 * fConst0;
	fConst13 = fConst0 * (fConst0 * (fConst0 * (2.47418541205506e-16 - fConst12) + -3.69672787496925e-13) + 1.8397056665289e-12);
	fConst14 = fConst2 * (fConst0 * (9.30061422376548e-18 - fConst1) + -9.53707992555105e-14);
	fConst15 = fConst0 * (fConst0 * (fConst0 * (fConst4 + -2.92076464853813e-17) + 7.68323461702748e-14) + -2.16751816489796e-12);
	fConst16 = fConst0 * (fConst0 * (fConst0 * (fConst6 + -2.80985481683452e-17) + 5.44712113689982e-13) + -1.29191360120173e-11);
	double fConst17 = 2.7869182298058e-19 * fConst0;
	double fConst18 = mydsp_faustpower3_f(fConst0);
	fConst19 = fConst18 * (fConst17 + -1.8601228447531e-17);
	double fConst20 = 1.55065907445816e-18 * fConst0;
	fConst21 = fConst0 * (fConst2 * (5.84152929707626e-17 - fConst20) + -4.33503632979593e-12);
	double fConst22 = 4.3527609462957e-20 * fConst0;
	fConst23 = fConst0 * (fConst2 * (5.61970963366905e-17 - fConst22) + -2.58382720240347e-11);
	fConst24 = 1.90741598511021e-13 - 4.1803773447087e-19 * fConst2;
	fConst25 = 2.32598861168724e-18 * fConst2 + -1.5366469234055e-13;
	fConst26 = 6.52914141944355e-20 * fConst2 + -1.08942422737996e-12;
	fConst27 = fConst18 * (fConst17 + 1.8601228447531e-17);
	fConst28 = fConst0 * (fConst2 * (-5.84152929707626e-17 - fConst20) + 4.33503632979593e-12);
	fConst29 = fConst0 * (fConst2 * (-5.61970963366905e-17 - fConst22) + 2.58382720240347e-11);
	double fConst30 = 716.6140154481191 / fConst0;
	fConst31 = 1.0 - fConst30;
	fConst32 = 1.0 / (fConst30 + 1.0);
	double fConst33 = 7.87337748654046e-21 * fConst0;
	fConst34 = fConst18 * (1.09717503103294e-16 - fConst33);
	double fConst35 = 7.86612995080753e-21 * fConst0;
	fConst36 = fConst0 * (fConst2 * (fConst35 + -1.09788573572638e-16) + 3.56311409757189e-12);
	double fConst37 = 2.9654015533375e-20 * fConst0;
	fConst38 = fConst0 * (fConst2 * (fConst37 + -4.94837082411013e-16) + 3.67941133305779e-12);
	fConst39 = 1.18100662298107e-20 * fConst2 + -1.61894098654543e-13;
	fConst40 = 1.64286470664228e-13 - 1.17991949262113e-20 * fConst2;
	fConst41 = 7.39345574993849e-13 - 4.44810233000624e-20 * fConst2;
	fConst42 = fConst18 * (-1.09717503103294e-16 - fConst33);
	fConst43 = fConst0 * (fConst2 * (fConst35 + 1.09788573572638e-16) + -3.56311409757189e-12);
	fConst44 = fConst0 * (fConst2 * (fConst37 + 4.94837082411013e-16) + -3.67941133305779e-12);
	fConst45 = fConst2 * (fConst0 * (fConst8 + 5.48587515516469e-17) + 8.09470493272714e-14);
	fConst46 = fConst0 * (fConst0 * (fConst0 * (-5.48942867863191e-17 - fConst10) + -8.21432353321142e-14) + -1.78155704878595e-12);
	fConst47 = fConst0 * (fConst0 * (fConst0 * (-2.47418541205506e-16 - fConst12) + -3.69672787496925e-13) + -1.8397056665289e-12);
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
	double fSlow0 = 4.748558434412966e-05 * (std::exp(5.0 * (1.0 - double(fVslider0))) + -1.0);
	double fSlow1 = 0.007000000000000006 * std::pow(1e+01, 0.05 * double(fVslider1));
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec0[0] = fSlow0 + 0.993 * fRec0[1];
		double fTemp0 = fConst7 + fRec0[0] * (fConst5 + fConst3 * fRec0[0]) + 4.92617764749537e-11;
		double fTemp1 = double(input0[i0]);
		fVec0[0] = fTemp1;
		fRec2[0] = fConst32 * (fTemp1 - fVec0[1] + fConst31 * fRec2[1]);
		fRec1[0] = fRec2[0] - (fRec1[1] * (fConst29 + fRec0[0] * (fConst28 + fConst27 * fRec0[0]) + 1.97047105899815e-10) + fRec1[2] * (fConst2 * (fConst26 + fRec0[0] * (fConst25 + fConst24 * fRec0[0])) + 2.95570658849723e-10) + fRec1[3] * (fConst23 + fRec0[0] * (fConst21 + fConst19 * fRec0[0]) + 1.97047105899815e-10) + fRec1[4] * (fConst16 + fRec0[0] * (fConst15 + fConst14 * fRec0[0]) + 4.92617764749537e-11)) / fTemp0;
		fRec3[0] = fSlow1 + 0.993 * fRec3[1];
		output0[i0] = FAUSTFLOAT(fRec3[0] * (fRec1[0] * (fConst47 + fRec0[0] * (fConst46 + fConst45 * fRec0[0])) + fRec1[1] * (fConst44 + fRec0[0] * (fConst43 + fConst42 * fRec0[0])) + fConst2 * fRec1[2] * (fConst41 + fRec0[0] * (fConst40 + fConst39 * fRec0[0])) + fRec1[3] * (fConst38 + fRec0[0] * (fConst36 + fConst34 * fRec0[0])) + fRec1[4] * (fConst13 + fRec0[0] * (fConst11 + fConst9 * fRec0[0]))) / fTemp0);
		fRec0[1] = fRec0[0];
		fVec0[1] = fVec0[0];
		fRec2[1] = fRec2[0];
		for (int j0 = 4; j0 > 0; j0 = j0 - 1) {
			fRec1[j0] = fRec1[j0 - 1];
		}
		fRec3[1] = fRec3[0];
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
		fVslider1_ = (float*)data; // , 0.0, -2e+01, 4.0, 0.1 
		break;
	case HOTPOTZ: 
		fVslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
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
