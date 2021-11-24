// generated from file '../src/LV2/faust/rangem.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace rangem {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fConst1;
	double fConst3;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec1[2];
	double fConst5;
	double fConst7;
	double fConst8;
	double fConst9;
	double fConst10;
	double fConst12;
	double fConst14;
	double fConst16;
	double fConst17;
	double fConst18;
	double fConst19;
	double fRec0[4];
	double fConst21;
	double fConst23;
	double fConst25;
	double fConst27;
	double fConst28;
	double fConst29;
	double fConst30;
	double fConst31;

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
	id = "rangem";
	name = N_("Rangemaster");
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec1[l0] = 0.0;
	for (int l1 = 0; (l1 < 4); l1 = (l1 + 1)) fRec0[l1] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = mydsp_faustpower2_f(fConst0);
	double fConst2 = (1.3112152596533899e-14 * fConst0);
	fConst3 = (fConst0 * ((fConst0 * (-2.23510911173716e-10 - fConst2)) + 1.20972656728663e-08));
	double fConst4 = (1.80914841671183e-16 * fConst0);
	fConst5 = (fConst0 * ((fConst0 * (fConst4 + -1.26333088694976e-11)) + 1.9579195352328598e-11));
	double fConst6 = (2.8831193297149801e-16 * fConst0);
	fConst7 = ((fConst0 * ((fConst0 * (fConst6 + 1.2982868337500301e-11)) + -3.7705539406211702e-11)) + -1.94326933795877e-22);
	fConst8 = (fConst0 * ((fConst0 * (fConst2 + -2.23510911173716e-10)) + -1.20972656728663e-08));
	fConst9 = (fConst0 * ((fConst0 * (-1.26333088694976e-11 - fConst4)) + -1.9579195352328598e-11));
	fConst10 = ((fConst0 * ((fConst0 * (1.2982868337500301e-11 - fConst6)) + 3.7705539406211702e-11)) + -1.94326933795877e-22);
	double fConst11 = (4.3707175321779698e-15 * fConst0);
	fConst12 = (fConst0 * ((fConst0 * (2.23510911173716e-10 - fConst11)) + -1.20972656728663e-08));
	double fConst13 = (6.0304947223727498e-17 * fConst0);
	fConst14 = (fConst0 * ((fConst0 * (fConst13 + 1.26333088694976e-11)) + -1.9579195352328598e-11));
	double fConst15 = (9.6103977657166e-17 * fConst0);
	fConst16 = ((fConst0 * ((fConst0 * (fConst15 + -1.2982868337500301e-11)) + 3.7705539406211702e-11)) + -6.4775644598625805e-23);
	fConst17 = (fConst0 * ((fConst0 * (fConst11 + 2.23510911173716e-10)) + 1.20972656728663e-08));
	fConst18 = (fConst0 * ((fConst0 * (1.26333088694976e-11 - fConst13)) + 1.9579195352328598e-11));
	fConst19 = ((fConst0 * ((fConst0 * (-1.2982868337500301e-11 - fConst15)) + -3.7705539406211702e-11)) + -6.4775644598625805e-23);
	double fConst20 = (8.3285238622566202e-13 * fConst0);
	fConst21 = (-2.2490612274236699e-12 - fConst20);
	double fConst22 = (8.3146660854475396e-13 * fConst0);
	fConst23 = (fConst22 + 2.2453190290419298e-12);
	double fConst24 = (2.4985571586769899e-12 * fConst0);
	fConst25 = (fConst24 + 2.2490612274236699e-12);
	double fConst26 = (2.49439982563426e-12 * fConst0);
	fConst27 = (-2.2453190290419298e-12 - fConst26);
	fConst28 = (2.2490612274236699e-12 - fConst24);
	fConst29 = (fConst26 + -2.2453190290419298e-12);
	fConst30 = (fConst20 + -2.2490612274236699e-12);
	fConst31 = (2.2453190290419298e-12 - fConst22);
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
	double fSlow0 = (0.01 * double(fVslider0));
	double fSlow1 = (1.0 - fSlow0);
	double fSlow2 = (0.0070000000000000062 * (1.0 - double(fVslider1)));
	for (int i0 = 0; (i0 < count); i0 = (i0 + 1)) {
		double fTemp0 = double(input0[i0]);
		fRec1[0] = (fSlow2 + (0.99299999999999999 * fRec1[1]));
		double fTemp1 = (fConst17 + ((fRec1[0] * (fConst18 + ((fConst19 * fRec1[0]) + 3.3635773937765603e-23))) + 4.6631307159519999e-08));
		fRec0[0] = ((fSlow0 * fTemp0) - ((((fRec0[1] * (fConst3 + ((fRec1[0] * (fConst5 + ((fConst7 * fRec1[0]) + 1.00907321813297e-22))) + 1.3989392147856001e-07))) + (fRec0[2] * (fConst8 + ((fRec1[0] * (fConst9 + ((fConst10 * fRec1[0]) + 1.00907321813297e-22))) + 1.3989392147856001e-07)))) + (fRec0[3] * (fConst12 + ((fRec1[0] * (fConst14 + ((fConst16 * fRec1[0]) + 3.3635773937765603e-23))) + 4.6631307159519999e-08)))) / fTemp1));
		output0[i0] = FAUSTFLOAT(((fSlow1 * fTemp0) + (fConst1 * (((((fRec0[0] * (fConst21 + (fConst23 * fRec1[0]))) + (fRec0[1] * (fConst25 + (fConst27 * fRec1[0])))) + (fRec0[2] * (fConst28 + (fConst29 * fRec1[0])))) + (fRec0[3] * (fConst30 + (fConst31 * fRec1[0])))) / fTemp1))));
		fRec1[1] = fRec1[0];
		for (int j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
			fRec0[j0] = fRec0[(j0 - 1)];
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
	case BOOST: 
		fVslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case WET_DRY: 
		fVslider0_ = (float*)data; // , 100.0, 0.0, 100.0, 1.0 
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
   BOOST, 
   WET_DRY, 
} PortIndex;
*/

} // end namespace rangem
