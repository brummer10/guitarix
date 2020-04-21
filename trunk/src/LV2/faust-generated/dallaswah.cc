// generated from file '../src/LV2/faust/dallaswah.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace dallaswah {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
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

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = (1833.7929316777988 / fConst0);
	fConst2 = (fConst1 + 1.0);
	fConst3 = (1.0 / fConst2);
	fConst4 = (1.0 - fConst1);
	fConst5 = (0.01 / fConst2);
	fConst6 = mydsp_faustpower2_f(fConst0);
	fConst7 = (2.4203899133154399e-19 * fConst0);
	fConst8 = (fConst0 * ((fConst6 * (-7.7348245376198901e-17 - fConst7)) + 6.9335873555484602e-11));
	fConst9 = (0.10471975511965977 / fConst0);
	fConst10 = std::exp((0.0 - (100.0 / fConst0)));
	fConst11 = (1.0 - fConst10);
	fConst12 = std::exp((0.0 - (10.0 / fConst0)));
	fConst13 = (1.0 - fConst12);
	fConst14 = (1.09962424162848e-18 * fConst0);
	fConst15 = ((fConst6 * (-4.9081562024677497e-17 - fConst14)) + 1.1209103273650301e-11);
	fConst16 = (1.7918901081266399e-19 * fConst0);
	fConst17 = ((fConst6 * (fConst16 + 2.1845348295102101e-17)) + 4.0298733331264199e-26);
	fConst18 = (fConst6 * ((3.6305848699731698e-19 * fConst6) + -2.7822356237811299e-12));
	fConst19 = ((1.6494363624427299e-18 * fConst6) + -2.8397698687053998e-13);
	fConst20 = (4.1922046243452401e-13 - (2.6878351621899599e-19 * fConst6));
	fConst21 = (fConst0 * ((fConst6 * (7.7348245376198901e-17 - fConst7)) + -6.9335873555484602e-11));
	fConst22 = ((fConst6 * (4.9081562024677497e-17 - fConst14)) + -1.1209103273650301e-11);
	fConst23 = ((fConst6 * (fConst16 + -2.1845348295102101e-17)) + -4.0298733331264199e-26);
	fConst24 = (6.0509747832886095e-20 * fConst0);
	fConst25 = (fConst0 * ((fConst0 * ((fConst0 * (fConst24 + -3.8674122688099401e-17)) + 1.3911178118905599e-12)) + -3.4667936777742301e-11));
	fConst26 = (2.7490606040712101e-19 * fConst0);
	fConst27 = ((fConst0 * ((fConst0 * (fConst26 + -2.4540781012338699e-17)) + 1.4198849343526999e-13)) + -5.6045516368251698e-12);
	fConst28 = (4.4797252703165901e-20 * fConst0);
	fConst29 = ((fConst0 * ((fConst0 * (1.0922674147551e-17 - fConst28)) + -2.09610231217262e-13)) + -2.0149366665632099e-26);
	fConst30 = (fConst0 * ((fConst0 * ((fConst0 * (fConst24 + 3.8674122688099401e-17)) + 1.3911178118905599e-12)) + 3.4667936777742301e-11));
	fConst31 = ((fConst0 * ((fConst0 * (fConst26 + 2.4540781012338699e-17)) + 1.4198849343526999e-13)) + 5.6045516368251698e-12);
	fConst32 = ((fConst0 * ((fConst0 * (-1.0922674147551e-17 - fConst28)) + -2.09610231217262e-13)) + 2.0149366665632099e-26);
	fConst33 = (7.0791743200520402e-21 * fConst0);
	fConst34 = ((fConst0 * ((fConst0 * (-5.5238902898921503e-16 - fConst33)) + -8.6311711901986799e-13)) + -5.6213535639818098e-12);
	fConst35 = (2.3234786046117102e-21 * fConst0);
	fConst36 = ((fConst0 * ((fConst0 * (-8.6410831164332904e-17 - fConst35)) + -1.3357552590519501e-13)) + -3.41675778537176e-12);
	fConst37 = (2.83510090714092e-21 * fConst0);
	fConst38 = ((fConst0 * ((fConst0 * (fConst37 + 1.04896968320146e-16)) + 1.5953481862304399e-13)) + -1.5335728307264501e-26);
	fConst39 = (2.8316697280208203e-20 * fConst0);
	fConst40 = ((fConst6 * (fConst39 + 1.1047780579784301e-15)) + -1.12427071279636e-11);
	fConst41 = (9.2939144184468497e-21 * fConst0);
	fConst42 = ((fConst6 * (fConst41 + 1.7282166232866601e-16)) + -6.8335155707435103e-12);
	fConst43 = (1.13404036285637e-20 * fConst0);
	fConst44 = ((fConst6 * (-2.0979393664029301e-16 - fConst43)) + -3.0671456614528898e-26);
	fConst45 = (1.72623423803974e-12 - (4.2475045920312298e-20 * fConst6));
	fConst46 = (2.6715105181039001e-13 - (1.3940871627670301e-20 * fConst6));
	fConst47 = ((1.7010605442845499e-20 * fConst6) + -3.1906963724608798e-13);
	fConst48 = ((fConst6 * (fConst39 + -1.1047780579784301e-15)) + 1.12427071279636e-11);
	fConst49 = ((fConst6 * (fConst41 + -1.7282166232866601e-16)) + 6.8335155707435103e-12);
	fConst50 = ((fConst6 * (2.0979393664029301e-16 - fConst43)) + 3.0671456614528898e-26);
	fConst51 = ((fConst0 * ((fConst0 * (5.5238902898921503e-16 - fConst33)) + -8.6311711901986799e-13)) + 5.6213535639818098e-12);
	fConst52 = ((fConst0 * ((fConst0 * (8.6410831164332904e-17 - fConst35)) + -1.3357552590519501e-13)) + 3.41675778537176e-12);
	fConst53 = ((fConst0 * ((fConst0 * (fConst37 + -1.04896968320146e-16)) + 1.5953481862304399e-13)) + 1.5335728307264501e-26);
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
	double fSlow8 = (4.748558434412966e-05 * (std::exp((5.0 * (1.0 - std::max<double>(0.01, double(fVslider3))))) + -1.0));
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
		fRec5[0] = ((0.99299999999999999 * fRec5[1]) + (0.0070000000000000062 * std::max<double>(0.02, std::min<double>(1.0, fRec6[0]))));
		fRec8[0] = (fSlow8 + (0.99299999999999999 * fRec8[1]));
		double fTemp2 = (iSlow5 ? fRec8[0] : (iSlow6 ? fRec5[0] : (1.0 - std::max<double>(0.02, std::min<double>(0.97999999999999998, (0.5 * (fRec2[0] + 1.0)))))));
		double fTemp3 = (fConst30 + ((fTemp2 * ((fConst0 * (fConst31 + (fConst32 * fTemp2))) + -5.3875311940192799e-25)) + 1.4985432184024801e-10));
		fRec0[0] = (fRec1[0] - (((((fRec0[1] * (fConst8 + ((fTemp2 * ((fConst0 * (fConst15 + (fConst17 * fTemp2))) + -2.1550124776077101e-24)) + 5.9941728736099297e-10))) + (fRec0[2] * (fConst18 + ((fTemp2 * ((fConst6 * (fConst19 + (fConst20 * fTemp2))) + -3.23251871641157e-24)) + 8.9912593104148899e-10)))) + (fRec0[3] * (fConst21 + ((fTemp2 * ((fConst0 * (fConst22 + (fConst23 * fTemp2))) + -2.1550124776077101e-24)) + 5.9941728736099297e-10)))) + (fRec0[4] * (fConst25 + ((fTemp2 * ((fConst0 * (fConst27 + (fConst29 * fTemp2))) + -5.3875311940192799e-25)) + 1.4985432184024801e-10)))) / fTemp3));
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

} // end namespace dallaswah
