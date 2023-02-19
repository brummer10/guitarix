// generated from file '../src/LV2/faust/selwah.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace selwah {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	int iVec0[2];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fConst1;
	double fRec2[2];
	double fRec1[2];
	double fRec0[2];
	double fConst2;
	double fConst3;
	double fConst4;
	double fRec5[2];
	double fConst5;
	double fRec4[2];
	double fRec3[2];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec6[2];
	double fConst7;
	double fConst8;
	double fConst10;
	double fConst12;
	double fConst14;
	double fConst16;
	double fConst18;
	double fConst19;
	double fConst20;
	double fConst21;
	double fConst24;
	double fConst26;
	double fConst28;
	double fConst29;
	double fConst30;
	double fConst31;
	double fConst32;
	double fConst33;
	double fConst34;
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fConst37;
	double fVec1[2];
	double fConst38;
	double fConst39;
	double fRec8[2];
	double fRec7[5];
	double fConst41;
	double fConst43;
	double fConst45;
	double fConst46;
	double fConst47;
	double fConst48;
	double fConst49;
	double fConst50;
	double fConst51;
	double fConst52;
	double fConst53;
	double fConst54;

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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) iVec0[l0] = 0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec2[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec1[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec0[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fRec5[l4] = 0.0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fRec4[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fRec3[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec6[l7] = 0.0;
	for (int l8 = 0; l8 < 2; l8 = l8 + 1) fVec1[l8] = 0.0;
	for (int l9 = 0; l9 < 2; l9 = l9 + 1) fRec8[l9] = 0.0;
	for (int l10 = 0; l10 < 5; l10 = l10 + 1) fRec7[l10] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = 0.10471975511965977 / fConst0;
	fConst2 = std::exp(0.0 - 1e+02 / fConst0);
	fConst3 = std::exp(0.0 - 1e+01 / fConst0);
	fConst4 = 1.0 - fConst3;
	fConst5 = 1.0 - fConst2;
	double fConst6 = 6.9507309070366e-20 * fConst0;
	fConst7 = mydsp_faustpower2_f(fConst0);
	fConst8 = fConst7 * (fConst0 * (-1.01737279942973e-17 - fConst6) + -8.91391550989893e-14);
	double fConst9 = 2.47965348716056e-19 * fConst0;
	fConst10 = fConst0 * (fConst0 * (fConst0 * (-9.25643357134141e-18 - fConst9) + 1.10300249541729e-13) + -2.02588988861339e-12);
	double fConst11 = 3.2847328592148e-19 * fConst0;
	fConst12 = fConst0 * (fConst0 * (fConst0 * (fConst11 + 5.6599406495133e-17) + 5.11880447644045e-13) + 1.73599395967319e-11);
	double fConst13 = 9.34067018664482e-21 * fConst0;
	fConst14 = fConst7 * (fConst0 * (fConst13 + -1.87102855759734e-16) + 2.81828342103572e-13);
	double fConst15 = 9.34656187780755e-21 * fConst0;
	fConst16 = fConst0 * (fConst0 * (fConst0 * (1.86919114730712e-16 - fConst15) + -2.77734086106026e-13) + -6.21752156007224e-12);
	double fConst17 = 3.81791996652528e-20 * fConst0;
	fConst18 = fConst0 * (fConst0 * (fConst0 * (8.47349775377979e-16 - fConst17) + -1.29923285740847e-12) + 2.03089386652508e-11);
	fConst19 = fConst7 * (fConst0 * (1.01737279942973e-17 - fConst6) + -8.91391550989893e-14);
	fConst20 = fConst0 * (fConst0 * (fConst0 * (9.25643357134141e-18 - fConst9) + 1.10300249541729e-13) + 2.02588988861339e-12);
	fConst21 = fConst0 * (fConst0 * (fConst0 * (fConst11 + -5.6599406495133e-17) + 5.11880447644045e-13) + -1.73599395967319e-11);
	double fConst22 = 2.78029236281464e-19 * fConst0;
	double fConst23 = mydsp_faustpower3_f(fConst0);
	fConst24 = fConst23 * (fConst22 + -2.03474559885945e-17);
	double fConst25 = 9.91861394864224e-19 * fConst0;
	fConst26 = fConst0 * (fConst7 * (fConst25 + -1.85128671426828e-17) + 4.05177977722679e-12);
	double fConst27 = 1.31389314368592e-18 * fConst0;
	fConst28 = fConst0 * (fConst7 * (1.13198812990266e-16 - fConst27) + -3.47198791934638e-11);
	fConst29 = 1.78278310197979e-13 - 4.17043854422196e-19 * fConst7;
	fConst30 = -2.20600499083458e-13 - 1.48779209229634e-18 * fConst7;
	fConst31 = 1.97083971552888e-18 * fConst7 + -1.02376089528809e-12;
	fConst32 = fConst23 * (fConst22 + 2.03474559885945e-17);
	fConst33 = fConst0 * (fConst7 * (fConst25 + 1.85128671426828e-17) + -4.05177977722679e-12);
	fConst34 = fConst0 * (fConst7 * (-1.13198812990266e-16 - fConst27) + 3.47198791934638e-11);
	double fConst35 = 2189.236692273638 / fConst0;
	double fConst36 = fConst35 + 1.0;
	fConst37 = 0.01 / fConst36;
	fConst38 = 1.0 - fConst35;
	fConst39 = 1.0 / fConst36;
	double fConst40 = 3.73626807465793e-20 * fConst0;
	fConst41 = fConst23 * (3.74205711519468e-16 - fConst40);
	double fConst42 = 3.73862475112302e-20 * fConst0;
	fConst43 = fConst0 * (fConst7 * (fConst42 + -3.73838229461424e-16) + -1.24350431201445e-11);
	double fConst44 = 1.52716798661011e-19 * fConst0;
	fConst45 = fConst0 * (fConst7 * (fConst44 + -1.69469955075596e-15) + 4.06178773305017e-11);
	fConst46 = 5.60440211198689e-20 * fConst7 + -5.63656684207144e-13;
	fConst47 = 5.55468172212051e-13 - 5.60793712668453e-20 * fConst7;
	fConst48 = 2.59846571481694e-12 - 2.29075197991517e-19 * fConst7;
	fConst49 = fConst23 * (-3.74205711519468e-16 - fConst40);
	fConst50 = fConst0 * (fConst7 * (fConst42 + 3.73838229461424e-16) + 1.24350431201445e-11);
	fConst51 = fConst0 * (fConst7 * (fConst44 + 1.69469955075596e-15) + -4.06178773305017e-11);
	fConst52 = fConst7 * (fConst0 * (fConst13 + 1.87102855759734e-16) + 2.81828342103572e-13);
	fConst53 = fConst0 * (fConst0 * (fConst0 * (-1.86919114730712e-16 - fConst15) + -2.77734086106026e-13) + 6.21752156007224e-12);
	fConst54 = fConst0 * (fConst0 * (fConst0 * (-8.47349775377979e-16 - fConst17) + -1.29923285740847e-12) + -2.03089386652508e-11);
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
	int iSlow1 = fSlow0 == 0.0;
	int iSlow2 = fSlow0 == 1.0;
	double fSlow3 = fConst1 * double(fVslider1);
	double fSlow4 = 0.007000000000000006 * double(fVslider2);
	double fSlow5 = double(fVslider3);
	double fSlow6 = fConst37 * fSlow5;
	double fSlow7 = 0.01 * fSlow5;
	double fSlow8 = 1.0 - fSlow7;
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		iVec0[0] = 1;
		fRec2[0] = fRec2[1] + fSlow3 * (0.0 - fRec0[1]);
		fRec1[0] = fSlow3 * fRec2[0] + double(1 - iVec0[1]) + fRec1[1];
		fRec0[0] = fRec1[0];
		double fTemp0 = double(input0[i0]);
		double fTemp1 = std::fabs(fTemp0);
		fRec5[0] = std::max<double>(fTemp1, fConst3 * fRec5[1] + fConst4 * fTemp1);
		fRec4[0] = fConst5 * fRec5[0] + fConst2 * fRec4[1];
		fRec3[0] = 0.007000000000000006 * (1.0 - std::max<double>(0.1, std::min<double>(0.99, fRec4[0]))) + 0.993 * fRec3[1];
		fRec6[0] = fSlow4 + 0.993 * fRec6[1];
		double fTemp2 = ((iSlow1) ? fRec6[0] : ((iSlow2) ? fRec3[0] : std::max<double>(0.01, std::min<double>(0.9, 0.5 * (fRec0[0] + 1.0)))));
		double fTemp3 = fConst12 + fTemp2 * (fConst10 + fConst8 * fTemp2) + 1.0129449443067e-10;
		fVec1[0] = fSlow6 * fTemp0;
		fRec8[0] = fConst39 * (fSlow7 * fTemp0 + fConst38 * fRec8[1]) - fVec1[1];
		fRec7[0] = fRec8[0] - (fRec7[1] * (fConst34 + fTemp2 * (fConst33 + fConst32 * fTemp2) + 4.05177977722679e-10) + fRec7[2] * (fConst7 * (fConst31 + fTemp2 * (fConst30 + fConst29 * fTemp2)) + 6.07766966584018e-10) + fRec7[3] * (fConst28 + fTemp2 * (fConst26 + fConst24 * fTemp2) + 4.05177977722679e-10) + fRec7[4] * (fConst21 + fTemp2 * (fConst20 + fConst19 * fTemp2) + 1.0129449443067e-10)) / fTemp3;
		output0[i0] = FAUSTFLOAT(fSlow8 * fTemp0 + (fRec7[0] * (fConst54 + fTemp2 * (fConst53 + fConst52 * fTemp2)) + fRec7[1] * (fConst51 + fTemp2 * (fConst50 + fConst49 * fTemp2)) + fConst7 * fRec7[2] * (fConst48 + fTemp2 * (fConst47 + fConst46 * fTemp2)) + fRec7[3] * (fConst45 + fTemp2 * (fConst43 + fConst41 * fTemp2)) + fRec7[4] * (fConst18 + fTemp2 * (fConst16 + fConst14 * fTemp2))) / fTemp3);
		iVec0[1] = iVec0[0];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
		fRec5[1] = fRec5[0];
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		fRec6[1] = fRec6[0];
		fVec1[1] = fVec1[0];
		fRec8[1] = fRec8[0];
		for (int j0 = 4; j0 > 0; j0 = j0 - 1) {
			fRec7[j0] = fRec7[j0 - 1];
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
		fVslider2_ = (float*)data; // , 0.0, 0.0, 1.0, 0.01 
		break;
	case FREQ: 
		fVslider1_ = (float*)data; // , 24.0, 24.0, 3.6e+02, 1.0 
	// static const value_pair fVslider0_values[] = {{"manual"},{"auto"},{"alien"},{0}};
	case MODE: 
		fVslider0_ = (float*)data; // , 0.0, 0.0, 2.0, 1.0 
		break;
	case WET_DRY: 
		fVslider3_ = (float*)data; // , 1e+02, 0.0, 1e+02, 1.0 
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
