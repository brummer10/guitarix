// generated from file '../src/LV2/faust/dallaswah.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace dallaswah {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	int iVec0[2];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fConst0;
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
	double fConst9;
	double fConst11;
	double fConst13;
	double fConst15;
	double fConst17;
	double fConst18;
	double fConst19;
	double fConst20;
	double fConst22;
	double fConst23;
	double fConst25;
	double fConst27;
	double fConst28;
	double fConst29;
	double fConst30;
	double fConst31;
	double fConst32;
	double fConst33;
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fConst36;
	double fVec1[2];
	double fConst37;
	double fConst38;
	double fRec8[2];
	double fRec7[5];
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
	id = "dallaswah";
	name = N_("Dallas Wah");
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
	fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = 0.10471975511965977 / fConst0;
	fConst2 = std::exp(0.0 - 1e+02 / fConst0);
	fConst3 = std::exp(0.0 - 1e+01 / fConst0);
	fConst4 = 1.0 - fConst3;
	fConst5 = 1.0 - fConst2;
	double fConst6 = 4.47972527031659e-20 * fConst0;
	fConst7 = fConst0 * (fConst0 * (-1.0922674147551e-17 - fConst6) + -2.09610231217262e-13) + 2.01493666656321e-26;
	double fConst8 = 2.74906060407121e-19 * fConst0;
	fConst9 = fConst0 * (fConst0 * (fConst8 + 2.45407810123387e-17) + 1.4198849343527e-13) + 5.60455163682517e-12;
	double fConst10 = 6.05097478328861e-20 * fConst0;
	fConst11 = fConst0 * (fConst0 * (fConst0 * (fConst10 + 3.86741226880994e-17) + 1.39111781189056e-12) + 3.46679367777423e-11);
	double fConst12 = 2.83510090714092e-21 * fConst0;
	fConst13 = fConst0 * (fConst0 * (fConst12 + -1.04896968320146e-16) + 1.59534818623044e-13) + 1.53357283072645e-26;
	double fConst14 = 2.32347860461171e-21 * fConst0;
	fConst15 = fConst0 * (fConst0 * (8.64108311643329e-17 - fConst14) + -1.33575525905195e-13) + 3.41675778537176e-12;
	double fConst16 = 7.07917432005204e-21 * fConst0;
	fConst17 = fConst0 * (fConst0 * (5.52389028989215e-16 - fConst16) + -8.63117119019868e-13) + 5.62135356398181e-12;
	fConst18 = fConst0 * (fConst0 * (1.0922674147551e-17 - fConst6) + -2.09610231217262e-13) + -2.01493666656321e-26;
	fConst19 = fConst0 * (fConst0 * (fConst8 + -2.45407810123387e-17) + 1.4198849343527e-13) + -5.60455163682517e-12;
	fConst20 = fConst0 * (fConst0 * (fConst0 * (fConst10 + -3.86741226880994e-17) + 1.39111781189056e-12) + -3.46679367777423e-11);
	double fConst21 = 1.79189010812664e-19 * fConst0;
	fConst22 = mydsp_faustpower2_f(fConst0);
	fConst23 = fConst22 * (fConst21 + -2.18453482951021e-17) + -4.02987333312642e-26;
	double fConst24 = 1.09962424162848e-18 * fConst0;
	fConst25 = fConst22 * (4.90815620246775e-17 - fConst24) + -1.12091032736503e-11;
	double fConst26 = 2.42038991331544e-19 * fConst0;
	fConst27 = fConst0 * (fConst22 * (7.73482453761989e-17 - fConst26) + -6.93358735554846e-11);
	fConst28 = 4.19220462434524e-13 - 2.68783516218996e-19 * fConst22;
	fConst29 = 1.64943636244273e-18 * fConst22 + -2.8397698687054e-13;
	fConst30 = fConst22 * (3.63058486997317e-19 * fConst22 + -2.78223562378113e-12);
	fConst31 = fConst22 * (fConst21 + 2.18453482951021e-17) + 4.02987333312642e-26;
	fConst32 = fConst22 * (-4.90815620246775e-17 - fConst24) + 1.12091032736503e-11;
	fConst33 = fConst0 * (fConst22 * (-7.73482453761989e-17 - fConst26) + 6.93358735554846e-11);
	double fConst34 = 1833.7929316777988 / fConst0;
	double fConst35 = fConst34 + 1.0;
	fConst36 = 0.01 / fConst35;
	fConst37 = 1.0 - fConst34;
	fConst38 = 1.0 / fConst35;
	double fConst39 = 1.13404036285637e-20 * fConst0;
	fConst40 = fConst22 * (2.09793936640293e-16 - fConst39) + 3.06714566145289e-26;
	double fConst41 = 9.29391441844685e-21 * fConst0;
	fConst42 = fConst22 * (fConst41 + -1.72821662328666e-16) + 6.83351557074351e-12;
	double fConst43 = 2.83166972802082e-20 * fConst0;
	fConst44 = fConst22 * (fConst43 + -1.10477805797843e-15) + 1.12427071279636e-11;
	fConst45 = 1.70106054428455e-20 * fConst22 + -3.19069637246088e-13;
	fConst46 = 2.6715105181039e-13 - 1.39408716276703e-20 * fConst22;
	fConst47 = 1.72623423803974e-12 - 4.24750459203123e-20 * fConst22;
	fConst48 = fConst22 * (-2.09793936640293e-16 - fConst39) + -3.06714566145289e-26;
	fConst49 = fConst22 * (fConst41 + 1.72821662328666e-16) + -6.83351557074351e-12;
	fConst50 = fConst22 * (fConst43 + 1.10477805797843e-15) + -1.12427071279636e-11;
	fConst51 = fConst0 * (fConst0 * (fConst12 + 1.04896968320146e-16) + 1.59534818623044e-13) + -1.53357283072645e-26;
	fConst52 = fConst0 * (fConst0 * (-8.64108311643329e-17 - fConst14) + -1.33575525905195e-13) + -3.41675778537176e-12;
	fConst53 = fConst0 * (fConst0 * (-5.52389028989215e-16 - fConst16) + -8.63117119019868e-13) + -5.62135356398181e-12;
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
	double fSlow4 = 4.748558434412966e-05 * (std::exp(5.0 * (1.0 - std::max<double>(0.01, double(fVslider2)))) + -1.0);
	double fSlow5 = double(fVslider3);
	double fSlow6 = fConst36 * fSlow5;
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
		fRec3[0] = 0.007000000000000006 * std::max<double>(0.02, std::min<double>(1.0, fRec4[0])) + 0.993 * fRec3[1];
		fRec6[0] = fSlow4 + 0.993 * fRec6[1];
		double fTemp2 = ((iSlow1) ? fRec6[0] : ((iSlow2) ? fRec3[0] : 1.0 - std::max<double>(0.02, std::min<double>(0.98, 0.5 * (fRec0[0] + 1.0)))));
		double fTemp3 = fConst11 + fTemp2 * (fConst0 * (fConst9 + fConst7 * fTemp2) + -5.38753119401928e-25) + 1.49854321840248e-10;
		fVec1[0] = fSlow6 * fTemp0;
		fRec8[0] = fConst38 * (fSlow7 * fTemp0 + fConst37 * fRec8[1]) - fVec1[1];
		fRec7[0] = fRec8[0] - (fRec7[1] * (fConst33 + fTemp2 * (fConst0 * (fConst32 + fConst31 * fTemp2) + -2.15501247760771e-24) + 5.99417287360993e-10) + fRec7[2] * (fConst30 + fTemp2 * (fConst22 * (fConst29 + fConst28 * fTemp2) + -3.23251871641157e-24) + 8.99125931041489e-10) + fRec7[3] * (fConst27 + fTemp2 * (fConst0 * (fConst25 + fConst23 * fTemp2) + -2.15501247760771e-24) + 5.99417287360993e-10) + fRec7[4] * (fConst20 + fTemp2 * (fConst0 * (fConst19 + fConst18 * fTemp2) + -5.38753119401928e-25) + 1.49854321840248e-10)) / fTemp3;
		output0[i0] = FAUSTFLOAT(fSlow8 * fTemp0 + (fConst0 * (fRec7[0] * (fConst53 + fTemp2 * (fConst52 + fConst51 * fTemp2)) + fRec7[1] * (fConst50 + fTemp2 * (fConst49 + fConst48 * fTemp2))) + fConst22 * fRec7[2] * (fConst47 + fTemp2 * (fConst46 + fConst45 * fTemp2)) + fConst0 * fRec7[3] * (fConst44 + fTemp2 * (fConst42 + fConst40 * fTemp2)) + fConst0 * fRec7[4] * (fConst17 + fTemp2 * (fConst15 + fConst13 * fTemp2))) / fTemp3);
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

} // end namespace dallaswah
