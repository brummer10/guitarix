// generated from file '../src/LV2/faust/maestrowah.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace maestrowah {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fConst0;
	double fConst3;
	double fConst4;
	int iVec0[2];
	double fConst5;
	double fVec1[2];
	double fRec1[2];
	double fConst6;
	double fConst8;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fConst9;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec4[2];
	double fRec3[2];
	double fRec2[2];
	double fConst10;
	double fConst11;
	double fConst12;
	double fConst13;
	double fRec6[2];
	double fRec5[2];
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fRec7[2];
	double fConst15;
	double fConst17;
	double fConst18;
	double fConst19;
	double fConst20;
	double fConst21;
	double fConst22;
	double fConst23;
	double fConst25;
	double fConst27;
	double fConst29;
	double fConst30;
	double fConst31;
	double fConst32;
	double fRec0[5];
	double fConst34;
	double fConst36;
	double fConst38;
	double fConst40;
	double fConst42;
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
	id = "maestrowah";
	name = N_("Maestro Wah");
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) iVec0[l0] = 0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fVec1[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec1[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fRec4[l3] = 0.0;
	for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) fRec3[l4] = 0.0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fRec2[l5] = 0.0;
	for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) fRec6[l6] = 0.0;
	for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) fRec5[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fRec7[l8] = 0.0;
	for (int l9 = 0; (l9 < 5); l9 = (l9 + 1)) fRec0[l9] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = (203.47539521535035 / fConst0);
	double fConst2 = (fConst1 + 1.0);
	fConst3 = (1.0 / fConst2);
	fConst4 = (1.0 - fConst1);
	fConst5 = (0.01 / fConst2);
	fConst6 = mydsp_faustpower2_f(fConst0);
	double fConst7 = (1.1826076633464699e-19 * fConst0);
	fConst8 = ((fConst6 * (-7.4077362793013503e-17 - fConst7)) + 1.53146105393048e-10);
	fConst9 = (0.10471975511965977 / fConst0);
	fConst10 = std::exp((0.0 - (100.0 / fConst0)));
	fConst11 = (1.0 - fConst10);
	fConst12 = std::exp((0.0 - (10.0 / fConst0)));
	fConst13 = (1.0 - fConst12);
	double fConst14 = (1.26159673965892e-18 * fConst0);
	fConst15 = ((fConst6 * (-4.4101904707591998e-17 - fConst14)) + 7.9360343973140094e-12);
	double fConst16 = (1.8157004218132698e-21 * fConst0);
	fConst17 = (fConst6 * (fConst16 + 4.4001454383515398e-18));
	fConst18 = ((1.7739114950196999e-19 * fConst6) + -1.0794775990002999e-12);
	fConst19 = ((1.8923951094883899e-18 * fConst6) + -5.6327156830493297e-14);
	fConst20 = (3.9680171986569998e-14 - (2.72355063271991e-21 * fConst6));
	fConst21 = ((fConst6 * (7.4077362793013503e-17 - fConst7)) + -1.53146105393048e-10);
	fConst22 = ((fConst6 * (4.4101904707591998e-17 - fConst14)) + -7.9360343973140094e-12);
	fConst23 = (fConst6 * (fConst16 + -4.4001454383515398e-18));
	double fConst24 = (2.95651915836617e-20 * fConst0);
	fConst25 = ((fConst0 * ((fConst0 * (fConst24 + -3.7038681396506702e-17)) + 5.3973879950014804e-13)) + -7.6573052696524105e-11);
	double fConst26 = (3.1539918491473101e-19 * fConst0);
	fConst27 = ((fConst0 * ((fConst0 * (fConst26 + -2.2050952353795999e-17)) + 2.8163578415246699e-14)) + -3.9680171986569999e-12);
	double fConst28 = (4.5392510545331802e-22 * fConst0);
	fConst29 = (fConst0 * ((fConst0 * (2.2000727191757699e-18 - fConst28)) + -1.9840085993284999e-14));
	fConst30 = ((fConst0 * ((fConst0 * (fConst24 + 3.7038681396506702e-17)) + 5.3973879950014804e-13)) + 7.6573052696524105e-11);
	fConst31 = ((fConst0 * ((fConst0 * (fConst26 + 2.2050952353795999e-17)) + 2.8163578415246699e-14)) + 3.9680171986569999e-12);
	fConst32 = (fConst0 * ((fConst0 * (-2.2000727191757699e-18 - fConst28)) + -1.9840085993284999e-14));
	double fConst33 = (3.5131653891331399e-20 * fConst0);
	fConst34 = ((fConst0 * ((fConst0 * (-4.1122950055168299e-16 - fConst33)) + -1.76902751745081e-12)) + -1.9864762622198099e-11);
	double fConst35 = (2.7145585307372299e-21 * fConst0);
	fConst36 = ((fConst0 * (-2.4779402870576299e-17 - fConst35)) + -8.8681788831384194e-14);
	double fConst37 = (2.7207559006593899e-21 * fConst0);
	fConst38 = ((fConst0 * (fConst37 + 2.4782894055632401e-17)) + 8.8681975991955794e-14);
	double fConst39 = (1.40526615565326e-19 * fConst0);
	fConst40 = ((fConst6 * (fConst39 + 8.2245900110336598e-16)) + -3.9729525244396197e-11);
	double fConst41 = (1.08582341229489e-20 * fConst0);
	fConst42 = (fConst41 + 4.9558805741152598e-17);
	double fConst43 = (1.0883023602637499e-20 * fConst0);
	fConst44 = (-4.95657881112649e-17 - fConst43);
	fConst45 = (3.53805503490162e-12 - (2.1078992334798801e-19 * fConst6));
	fConst46 = (1.7736357766276801e-13 - (1.62873511844234e-20 * fConst6));
	fConst47 = ((1.6324535403956301e-20 * fConst6) + -1.7736395198391199e-13);
	fConst48 = ((fConst6 * (fConst39 + -8.2245900110336598e-16)) + 3.9729525244396197e-11);
	fConst49 = (fConst41 + -4.9558805741152598e-17);
	fConst50 = (4.95657881112649e-17 - fConst43);
	fConst51 = ((fConst0 * ((fConst0 * (4.1122950055168299e-16 - fConst33)) + -1.76902751745081e-12)) + 1.9864762622198099e-11);
	fConst52 = ((fConst0 * (2.4779402870576299e-17 - fConst35)) + -8.8681788831384194e-14);
	fConst53 = ((fConst0 * (fConst37 + -2.4782894055632401e-17)) + 8.8681975991955794e-14);
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
	double fSlow0 = double(fVslider0);
	double fSlow1 = (0.01 * fSlow0);
	double fSlow2 = (1.0 - fSlow1);
	double fSlow3 = (fConst5 * fSlow0);
	int iSlow4 = int(double(fVslider1));
	int iSlow5 = (iSlow4 == 0);
	int iSlow6 = (iSlow4 == 1);
	double fSlow7 = (fConst9 * double(fVslider2));
	double fSlow8 = (0.004073836948085289 * (std::exp((1.0 - double(fVslider3))) + -1.0));
	for (int i0 = 0; (i0 < count); i0 = (i0 + 1)) {
		double fTemp0 = double(input0[i0]);
		iVec0[0] = 1;
		fVec1[0] = (fSlow3 * fTemp0);
		fRec1[0] = ((fConst3 * ((fSlow1 * fTemp0) + (fConst4 * fRec1[1]))) - fVec1[1]);
		fRec4[0] = (fRec4[1] + (fSlow7 * (0.0 - fRec2[1])));
		fRec3[0] = ((fSlow7 * fRec4[0]) + (double((1 - iVec0[1])) + fRec3[1]));
		fRec2[0] = fRec3[0];
		double fTemp1 = std::fabs(fTemp0);
		fRec6[0] = std::max<double>(fTemp1, ((fConst12 * fRec6[1]) + (fConst13 * fTemp1)));
		fRec5[0] = ((fConst10 * fRec5[1]) + (fConst11 * fRec6[0]));
		double fThen0 = (1.0 - std::max<double>(0.25, std::min<double>(0.91000000000000003, (0.5 * (fRec2[0] + 1.0)))));
		double fElse0 = std::max<double>(0.089999999999999997, std::min<double>(0.75, fRec5[0]));
		fRec7[0] = (fSlow8 + (0.99299999999999999 * fRec7[1]));
		double fThen1 = (iSlow6 ? fElse0 : fThen0);
		double fTemp2 = (iSlow5 ? fRec7[0] : fThen1);
		double fTemp3 = ((fConst0 * (fConst30 + (fTemp2 * (fConst31 + (fConst32 * fTemp2))))) + 7.9360343973140096e-10);
		fRec0[0] = (fRec1[0] - (((((fRec0[1] * ((fConst0 * (fConst8 + (fTemp2 * (fConst15 + (fConst17 * fTemp2))))) + 3.1744137589256001e-09)) + (fRec0[2] * ((fConst6 * (fConst18 + (fTemp2 * (fConst19 + (fConst20 * fTemp2))))) + 4.7616206383884097e-09))) + (fRec0[3] * ((fConst0 * (fConst21 + (fTemp2 * (fConst22 + (fConst23 * fTemp2))))) + 3.1744137589256001e-09))) + (fRec0[4] * ((fConst0 * (fConst25 + (fTemp2 * (fConst27 + (fConst29 * fTemp2))))) + 7.9360343973140096e-10))) / fTemp3));
		output0[i0] = FAUSTFLOAT(((fSlow2 * fTemp0) + (fConst0 * ((((((fRec0[0] * (fConst34 + (fConst0 * (fTemp2 * (fConst36 + (fConst38 * fTemp2)))))) + (fRec0[1] * (fConst40 + (fConst6 * (fTemp2 * (fConst42 + (fConst44 * fTemp2))))))) + (fConst0 * (fRec0[2] * (fConst45 + (fTemp2 * (fConst46 + (fConst47 * fTemp2))))))) + (fRec0[3] * (fConst48 + (fConst6 * (fTemp2 * (fConst49 + (fConst50 * fTemp2))))))) + (fRec0[4] * (fConst51 + (fConst0 * (fTemp2 * (fConst52 + (fConst53 * fTemp2))))))) / fTemp3))));
		iVec0[1] = iVec0[0];
		fVec1[1] = fVec1[0];
		fRec1[1] = fRec1[0];
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		fRec2[1] = fRec2[0];
		fRec6[1] = fRec6[0];
		fRec5[1] = fRec5[0];
		fRec7[1] = fRec7[0];
		for (int j0 = 4; (j0 > 0); j0 = (j0 - 1)) {
			fRec0[j0] = fRec0[(j0 - 1)];
		}
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
	case WAH: 
		fVslider3_ = (float*)data; // , 0.0, 0.0, 1.0, 0.01 
		break;
	case FREQ: 
		fVslider2_ = (float*)data; // , 24.0, 24.0, 360.0, 1.0 
	// static const value_pair fVslider1_values[] = {{"manual"},{"auto"},{"alien"},{0}};
	case MODE: 
		fVslider1_ = (float*)data; // , 0.0, 0.0, 2.0, 1.0 
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
   WAH, 
   FREQ, 
   MODE, 
   WET_DRY, 
} PortIndex;
*/

} // end namespace maestrowah
