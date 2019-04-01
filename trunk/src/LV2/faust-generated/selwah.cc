// generated from file '../src/LV2/faust/selwah.dsp' by dsp2cc:
// Code generated with Faust 2.15.11 (https://faust.grame.fr)


namespace selwah {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	double fConst4;
	int iVec0[2];
	double fConst5;
	double fVec1[2];
	double fRec1[2];
	double fConst6;
	double fConst7;
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
	double fRec7[2];
	double fRec6[2];
	double fRec5[2];
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fRec8[2];
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
	double fRec0[5];
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
	id = "selwah";
	name = N_("Selmer Wah");
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
	for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) fRec7[l6] = 0.0;
	for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) fRec6[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fRec5[l8] = 0.0;
	for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) fRec8[l9] = 0.0;
	for (int l10 = 0; (l10 < 5); l10 = (l10 + 1)) fRec0[l10] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSamplingFreq)));
	fConst1 = (2189.2366922736378 / fConst0);
	fConst2 = (fConst1 + 1.0);
	fConst3 = (1.0 / fConst2);
	fConst4 = (1.0 - fConst1);
	fConst5 = (0.01 / fConst2);
	fConst6 = (1.3138931436859199e-18 * fConst0);
	fConst7 = mydsp_faustpower2_f(fConst0);
	fConst8 = (((-1.13198812990266e-16 - fConst6) * fConst7) + 3.4719879193463799e-11);
	fConst9 = (0.10471975511965977 / fConst0);
	fConst10 = std::exp((0.0 - (100.0 / fConst0)));
	fConst11 = (1.0 - fConst10);
	fConst12 = std::exp((0.0 - (10.0 / fConst0)));
	fConst13 = (1.0 - fConst12);
	fConst14 = (9.9186139486422391e-19 * fConst0);
	fConst15 = (((fConst14 + 1.8512867142682799e-17) * fConst7) + -4.0517797772267902e-12);
	fConst16 = (2.7802923628146398e-19 * fConst0);
	fConst17 = ((fConst16 + 2.0347455988594498e-17) * fConst7);
	fConst18 = ((1.9708397155288798e-18 * fConst7) + -1.02376089528809e-12);
	fConst19 = (-2.2060049908345801e-13 - (1.4877920922963401e-18 * fConst7));
	fConst20 = (1.7827831019797901e-13 - (4.17043854422196e-19 * fConst7));
	fConst21 = (((1.13198812990266e-16 - fConst6) * fConst7) + -3.4719879193463799e-11);
	fConst22 = (((fConst14 + -1.8512867142682799e-17) * fConst7) + 4.0517797772267902e-12);
	fConst23 = ((fConst16 + -2.0347455988594498e-17) * fConst7);
	fConst24 = (3.2847328592147999e-19 * fConst0);
	fConst25 = (((((fConst24 + -5.6599406495132998e-17) * fConst0) + 5.1188044764404501e-13) * fConst0) + -1.7359939596731899e-11);
	fConst26 = (2.4796534871605598e-19 * fConst0);
	fConst27 = (((((9.2564335713414103e-18 - fConst26) * fConst0) + 1.10300249541729e-13) * fConst0) + 2.0258898886133898e-12);
	fConst28 = (6.9507309070365995e-20 * fConst0);
	fConst29 = ((((1.01737279942973e-17 - fConst28) * fConst0) + -8.9139155098989302e-14) * fConst0);
	fConst30 = (((((fConst24 + 5.6599406495132998e-17) * fConst0) + 5.1188044764404501e-13) * fConst0) + 1.7359939596731899e-11);
	fConst31 = (((((-9.2564335713414103e-18 - fConst26) * fConst0) + 1.10300249541729e-13) * fConst0) + -2.0258898886133898e-12);
	fConst32 = ((((-1.01737279942973e-17 - fConst28) * fConst0) + -8.9139155098989302e-14) * fConst0);
	fConst33 = (3.8179199665252801e-20 * fConst0);
	fConst34 = (((((-8.4734977537797905e-16 - fConst33) * fConst0) + -1.29923285740847e-12) * fConst0) + -2.0308938665250799e-11);
	fConst35 = (9.3465618778075504e-21 * fConst0);
	fConst36 = (((((-1.86919114730712e-16 - fConst35) * fConst0) + -2.7773408610602599e-13) * fConst0) + 6.2175215600722403e-12);
	fConst37 = (9.3406701866448199e-21 * fConst0);
	fConst38 = ((((fConst37 + 1.8710285575973399e-16) * fConst0) + 2.8182834210357199e-13) * fConst0);
	fConst39 = (1.5271679866101099e-19 * fConst0);
	fConst40 = (((fConst39 + 1.6946995507559601e-15) * fConst7) + -4.06178773305017e-11);
	fConst41 = (3.7386247511230202e-20 * fConst0);
	fConst42 = (((fConst41 + 3.73838229461424e-16) * fConst7) + 1.24350431201445e-11);
	fConst43 = (3.7362680746579298e-20 * fConst0);
	fConst44 = ((-3.7420571151946799e-16 - fConst43) * fConst7);
	fConst45 = (2.59846571481694e-12 - (2.2907519799151698e-19 * fConst7));
	fConst46 = (5.5546817221205097e-13 - (5.6079371266845299e-20 * fConst7));
	fConst47 = ((5.6044021119868898e-20 * fConst7) + -5.6365668420714398e-13);
	fConst48 = (((fConst39 + -1.6946995507559601e-15) * fConst7) + 4.06178773305017e-11);
	fConst49 = (((fConst41 + -3.73838229461424e-16) * fConst7) + -1.24350431201445e-11);
	fConst50 = ((3.7420571151946799e-16 - fConst43) * fConst7);
	fConst51 = (((((8.4734977537797905e-16 - fConst33) * fConst0) + -1.29923285740847e-12) * fConst0) + 2.0308938665250799e-11);
	fConst52 = (((((1.86919114730712e-16 - fConst35) * fConst0) + -2.7773408610602599e-13) * fConst0) + -6.2175215600722403e-12);
	fConst53 = ((((fConst37 + -1.8710285575973399e-16) * fConst0) + 2.8182834210357199e-13) * fConst0);
	fVslider0 = FAUSTFLOAT(100.0);
	fVslider1 = FAUSTFLOAT(0.0);
	fVslider2 = FAUSTFLOAT(24.0);
	fVslider3 = FAUSTFLOAT(0.0);
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
	double fSlow8 = (0.0070000000000000062 * double(fVslider3));
	for (int i = 0; (i < count); i = (i + 1)) {
		double fTemp0 = double(input0[i]);
		iVec0[0] = 1;
		fVec1[0] = (fSlow3 * fTemp0);
		fRec1[0] = ((fConst3 * ((fSlow1 * fTemp0) + (fConst4 * fRec1[1]))) - fVec1[1]);
		fRec4[0] = (fRec4[1] + (fSlow7 * (0.0 - fRec2[1])));
		fRec3[0] = ((fSlow7 * fRec4[0]) + (double((1 - iVec0[1])) + fRec3[1]));
		fRec2[0] = fRec3[0];
		double fTemp1 = std::fabs(fTemp0);
		fRec7[0] = std::max<double>(fTemp1, ((fConst12 * fRec7[1]) + (fConst13 * fTemp1)));
		fRec6[0] = ((fConst10 * fRec6[1]) + (fConst11 * fRec7[0]));
		fRec5[0] = ((0.99299999999999999 * fRec5[1]) + (0.0070000000000000062 * (1.0 - std::max<double>(0.10000000000000001, std::min<double>(0.98999999999999999, fRec6[0])))));
		fRec8[0] = (fSlow8 + (0.99299999999999999 * fRec8[1]));
		double fTemp2 = (iSlow5?fRec8[0]:(iSlow6?fRec5[0]:std::max<double>(0.01, std::min<double>(0.90000000000000002, (0.5 * (fRec2[0] + 1.0))))));
		double fTemp3 = ((fConst0 * (fConst30 + (fTemp2 * (fConst31 + (fConst32 * fTemp2))))) + 1.0129449443067e-10);
		fRec0[0] = (fRec1[0] - (((((fRec0[1] * ((fConst0 * (fConst8 + (fTemp2 * (fConst15 + (fConst17 * fTemp2))))) + 4.0517797772267901e-10)) + (fRec0[2] * ((fConst7 * (fConst18 + (fTemp2 * (fConst19 + (fConst20 * fTemp2))))) + 6.0776696658401798e-10))) + (fRec0[3] * ((fConst0 * (fConst21 + (fTemp2 * (fConst22 + (fConst23 * fTemp2))))) + 4.0517797772267901e-10))) + (fRec0[4] * ((fConst0 * (fConst25 + (fTemp2 * (fConst27 + (fConst29 * fTemp2))))) + 1.0129449443067e-10))) / fTemp3));
		output0[i] = FAUSTFLOAT(((fSlow2 * fTemp0) + (fConst0 * ((((((fRec0[0] * (fConst34 + (fTemp2 * (fConst36 + (fConst38 * fTemp2))))) + (fRec0[1] * (fConst40 + (fTemp2 * (fConst42 + (fConst44 * fTemp2)))))) + (fConst0 * (fRec0[2] * (fConst45 + (fTemp2 * (fConst46 + (fConst47 * fTemp2))))))) + (fRec0[3] * (fConst48 + (fTemp2 * (fConst49 + (fConst50 * fTemp2)))))) + (fRec0[4] * (fConst51 + (fTemp2 * (fConst52 + (fConst53 * fTemp2)))))) / fTemp3))));
		iVec0[1] = iVec0[0];
		fVec1[1] = fVec1[0];
		fRec1[1] = fRec1[0];
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		fRec2[1] = fRec2[0];
		fRec7[1] = fRec7[0];
		fRec6[1] = fRec6[0];
		fRec5[1] = fRec5[0];
		fRec8[1] = fRec8[0];
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
		break;
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

} // end namespace selwah
