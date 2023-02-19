// generated from file '../src/LV2/faust/rangem.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace rangem {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec0[2];
	double fConst2;
	double fConst4;
	double fConst6;
	double fConst8;
	double fConst10;
	double fConst11;
	double fConst12;
	double fConst13;
	double fConst15;
	double fConst17;
	double fConst19;
	double fConst20;
	double fConst21;
	double fConst22;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec1[4];
	double fConst24;
	double fConst26;
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec0[l0] = 0.0;
	for (int l1 = 0; l1 < 4; l1 = l1 + 1) fRec1[l1] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = 9.6103977657166e-17 * fConst0;
	fConst2 = fConst0 * (fConst0 * (-1.29828683375003e-11 - fConst1) + -3.77055394062117e-11) + -6.47756445986258e-23;
	double fConst3 = 6.03049472237275e-17 * fConst0;
	fConst4 = fConst0 * (fConst0 * (1.26333088694976e-11 - fConst3) + 1.95791953523286e-11);
	double fConst5 = 4.37071753217797e-15 * fConst0;
	fConst6 = fConst0 * (fConst0 * (fConst5 + 2.23510911173716e-10) + 1.20972656728663e-08);
	double fConst7 = 8.31466608544754e-13 * fConst0;
	fConst8 = 2.24531902904193e-12 - fConst7;
	double fConst9 = 8.32852386225662e-13 * fConst0;
	fConst10 = fConst9 + -2.24906122742367e-12;
	fConst11 = fConst0 * (fConst0 * (fConst1 + -1.29828683375003e-11) + 3.77055394062117e-11) + -6.47756445986258e-23;
	fConst12 = fConst0 * (fConst0 * (fConst3 + 1.26333088694976e-11) + -1.95791953523286e-11);
	fConst13 = fConst0 * (fConst0 * (2.23510911173716e-10 - fConst5) + -1.20972656728663e-08);
	double fConst14 = 2.88311932971498e-16 * fConst0;
	fConst15 = fConst0 * (fConst0 * (1.29828683375003e-11 - fConst14) + 3.77055394062117e-11) + -1.94326933795877e-22;
	double fConst16 = 1.80914841671183e-16 * fConst0;
	fConst17 = fConst0 * (fConst0 * (-1.26333088694976e-11 - fConst16) + -1.95791953523286e-11);
	double fConst18 = 1.31121525965339e-14 * fConst0;
	fConst19 = fConst0 * (fConst0 * (fConst18 + -2.23510911173716e-10) + -1.20972656728663e-08);
	fConst20 = fConst0 * (fConst0 * (fConst14 + 1.29828683375003e-11) + -3.77055394062117e-11) + -1.94326933795877e-22;
	fConst21 = fConst0 * (fConst0 * (fConst16 + -1.26333088694976e-11) + 1.95791953523286e-11);
	fConst22 = fConst0 * (fConst0 * (-2.23510911173716e-10 - fConst18) + 1.20972656728663e-08);
	double fConst23 = 2.49439982563426e-12 * fConst0;
	fConst24 = fConst23 + -2.24531902904193e-12;
	double fConst25 = 2.49855715867699e-12 * fConst0;
	fConst26 = 2.24906122742367e-12 - fConst25;
	fConst27 = -2.24531902904193e-12 - fConst23;
	fConst28 = fConst25 + 2.24906122742367e-12;
	fConst29 = fConst7 + 2.24531902904193e-12;
	fConst30 = -2.24906122742367e-12 - fConst9;
	fConst31 = mydsp_faustpower2_f(fConst0);
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
	double fSlow0 = 0.007000000000000006 * (1.0 - double(fVslider0));
	double fSlow1 = 0.01 * double(fVslider1);
	double fSlow2 = 1.0 - fSlow1;
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec0[0] = fSlow0 + 0.993 * fRec0[1];
		double fTemp0 = fConst6 + fRec0[0] * (fConst4 + fConst2 * fRec0[0] + 3.36357739377656e-23) + 4.663130715952e-08;
		double fTemp1 = double(input0[i0]);
		fRec1[0] = fSlow1 * fTemp1 - (fRec1[1] * (fConst22 + fRec0[0] * (fConst21 + fConst20 * fRec0[0] + 1.00907321813297e-22) + 1.3989392147856e-07) + fRec1[2] * (fConst19 + fRec0[0] * (fConst17 + fConst15 * fRec0[0] + 1.00907321813297e-22) + 1.3989392147856e-07) + fRec1[3] * (fConst13 + fRec0[0] * (fConst12 + fConst11 * fRec0[0] + 3.36357739377656e-23) + 4.663130715952e-08)) / fTemp0;
		output0[i0] = FAUSTFLOAT(fSlow2 * fTemp1 + fConst31 * ((fRec1[0] * (fConst30 + fConst29 * fRec0[0]) + fRec1[1] * (fConst28 + fConst27 * fRec0[0]) + fRec1[2] * (fConst26 + fConst24 * fRec0[0]) + fRec1[3] * (fConst10 + fConst8 * fRec0[0])) / fTemp0));
		fRec0[1] = fRec0[0];
		for (int j0 = 3; j0 > 0; j0 = j0 - 1) {
			fRec1[j0] = fRec1[j0 - 1];
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
		fVslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case WET_DRY: 
		fVslider1_ = (float*)data; // , 1e+02, 0.0, 1e+02, 1.0 
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
