// generated from file '../src/LV2/faust/hornet.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace hornet {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	double fConst0;
	double fConst1;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec0[2];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec2[2];
	double fConst2;
	double fConst3;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec3[2];
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
	double fRec1[5];
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
	double fConst54;
	double fConst55;
	double fConst56;
	double fConst57;
	double fConst58;
	double fConst59;
	double fConst60;
	double fConst61;
	double fConst62;
	double fConst63;
	double fConst64;
	double fConst65;
	double fConst66;
	double fConst67;
	double fConst68;
	double fConst69;
	double fConst70;
	double fConst71;
	double fConst72;
	double fConst73;
	double fConst74;
	double fConst75;
	double fConst76;
	double fConst77;
	double fConst78;
	double fConst79;
	double fConst80;
	double fConst81;

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
	id = "hornet";
	name = N_("Hornet");
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
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec3[l2] = 0.0;
	for (int l3 = 0; (l3 < 5); l3 = (l3 + 1)) fRec1[l3] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = mydsp_faustpower2_f(fConst0);
	fConst2 = (8.0344113490136796e-19 * fConst0);
	fConst3 = ((fConst1 * (-2.1327709047497402e-15 - fConst2)) + 4.6082764112797202e-12);
	fConst4 = (1.0533847926209301e-18 * fConst0);
	fConst5 = ((fConst1 * (-2.7912118642523799e-15 - fConst4)) + 2.1911443811562198e-12);
	fConst6 = (8.9092734281538994e-20 * fConst0);
	fConst7 = ((fConst1 * (fConst6 + 2.3136174511326298e-16)) + -1.7723782402438701e-13);
	fConst8 = (7.3938345895294102e-21 * fConst0);
	fConst9 = ((fConst1 * (-4.97629551390976e-16 - fConst8)) + 8.6188432028757995e-11);
	fConst10 = (2.8896627533487999e-21 * fConst0);
	fConst11 = ((fConst1 * (-2.3141629669080201e-16 - fConst10)) + 1.16303563314026e-11);
	fConst12 = (1.02834973428782e-20 * fConst0);
	fConst13 = ((fConst1 * (fConst12 + 6.4056516005839696e-16)) + -3.1853156396660198e-11);
	fConst14 = ((1.20516170235205e-18 * fConst1) + -2.2146088225976801e-13);
	fConst15 = ((1.5800771889314001e-18 * fConst1) + -2.4710764349103501e-13);
	fConst16 = (2.04220452060922e-14 - (1.3363910142230799e-19 * fConst1));
	fConst17 = ((1.10907518842941e-20 * fConst1) + -2.5054803935412798e-12);
	fConst18 = ((4.33449413002321e-21 * fConst1) + -1.16746083607033e-12);
	fConst19 = (3.1991095902122601e-12 - (1.5425246014317301e-20 * fConst1));
	fConst20 = ((fConst1 * (2.1327709047497402e-15 - fConst2)) + -4.6082764112797202e-12);
	fConst21 = ((fConst1 * (2.7912118642523799e-15 - fConst4)) + -2.1911443811562198e-12);
	fConst22 = ((fConst1 * (fConst6 + -2.3136174511326298e-16)) + 1.7723782402438701e-13);
	fConst23 = ((fConst1 * (4.97629551390976e-16 - fConst8)) + -8.6188432028757995e-11);
	fConst24 = ((fConst1 * (2.3141629669080201e-16 - fConst10)) + -1.16303563314026e-11);
	fConst25 = ((fConst1 * (fConst12 + -6.4056516005839696e-16)) + 3.1853156396660198e-11);
	fConst26 = (2.0086028372534199e-19 * fConst0);
	fConst27 = ((fConst0 * ((fConst0 * (fConst26 + -1.0663854523748701e-15)) + 1.1073044112988401e-13)) + -2.3041382056398601e-12);
	fConst28 = (2.6334619815523401e-19 * fConst0);
	fConst29 = ((fConst0 * ((fConst0 * (fConst28 + -1.3956059321261899e-15)) + 1.2355382174551801e-13)) + -1.0955721905781099e-12);
	fConst30 = (2.22731835703847e-20 * fConst0);
	fConst31 = ((fConst0 * ((fConst0 * (1.15680872556631e-16 - fConst30)) + -1.02110226030461e-14)) + 8.8618912012193706e-14);
	fConst32 = (1.8484586473823499e-21 * fConst0);
	fConst33 = ((fConst0 * ((fConst0 * (fConst32 + -2.48814775695488e-16)) + 1.2527401967706399e-12)) + -4.3094216014378998e-11);
	fConst34 = (7.2241568833720101e-22 * fConst0);
	fConst35 = ((fConst0 * ((fConst0 * (fConst34 + -1.1570814834540101e-16)) + 5.8373041803516501e-13)) + -5.8151781657012799e-12);
	fConst36 = (2.5708743357195501e-21 * fConst0);
	fConst37 = ((fConst0 * ((fConst0 * (3.2028258002919799e-16 - fConst36)) + -1.59955479510613e-12)) + 1.5926578198330099e-11);
	fConst38 = ((fConst0 * ((fConst0 * (fConst26 + 1.0663854523748701e-15)) + 1.1073044112988401e-13)) + 2.3041382056398601e-12);
	fConst39 = ((fConst0 * ((fConst0 * (fConst28 + 1.3956059321261899e-15)) + 1.2355382174551801e-13)) + 1.0955721905781099e-12);
	fConst40 = ((fConst0 * ((fConst0 * (-1.15680872556631e-16 - fConst30)) + -1.02110226030461e-14)) + -8.8618912012193706e-14);
	fConst41 = ((fConst0 * ((fConst0 * (fConst32 + 2.48814775695488e-16)) + 1.2527401967706399e-12)) + 4.3094216014378998e-11);
	fConst42 = ((fConst0 * ((fConst0 * (fConst34 + 1.1570814834540101e-16)) + 5.8373041803516501e-13)) + 5.8151781657012799e-12);
	fConst43 = ((fConst0 * ((fConst0 * (-3.2028258002919799e-16 - fConst36)) + -1.59955479510613e-12)) + -1.5926578198330099e-11);
	fConst44 = (2.4218162356217001e-20 * fConst0);
	fConst45 = ((fConst0 * (fConst44 + 1.2685958335763499e-16)) + 3.2109130517186899e-15);
	fConst46 = (9.4649563589667005e-21 * fConst0);
	fConst47 = (fConst46 + 4.9338602296741301e-17);
	fConst48 = (3.3683118715183703e-20 * fConst0);
	fConst49 = (-1.75582214579149e-16 - fConst48);
	fConst50 = (1.45891323583538e-19 * fConst0);
	fConst51 = ((fConst0 * (fConst50 + 7.4048946315080199e-16)) + -1.04296301457845e-13);
	fConst52 = (2.2865563315343902e-18 * fConst0);
	fConst53 = (fConst52 + 1.19192830048069e-14);
	fConst54 = (2.8979800773940299e-18 * fConst0);
	fConst55 = (fConst54 + 1.5106491892798699e-14);
	fConst56 = (9.6872649424868004e-20 * fConst0);
	fConst57 = (-2.5371916671527101e-16 - fConst56);
	fConst58 = (3.7859825435866802e-20 * fConst0);
	fConst59 = (-9.8677204593482602e-17 - fConst58);
	fConst60 = (1.34732474860735e-19 * fConst0);
	fConst61 = (fConst60 + 3.51164429158298e-16);
	fConst62 = (5.83565294334152e-19 * fConst0);
	fConst63 = (-1.4809789263016e-15 - fConst62);
	fConst64 = (9.1462253261375608e-18 * fConst0);
	fConst65 = (-2.38385660096139e-14 - fConst64);
	fConst66 = (1.15919203095761e-17 * fConst0);
	fConst67 = (-3.0212983785597297e-14 - fConst66);
	fConst68 = ((1.4530897413730201e-19 * fConst1) + -6.4218261034373797e-15);
	fConst69 = ((8.7534794150122796e-19 * fConst1) + 2.08592602915691e-13);
	fConst70 = (2.5371916671527101e-16 - fConst56);
	fConst71 = (9.8677204593482602e-17 - fConst58);
	fConst72 = (fConst60 + -3.51164429158298e-16);
	fConst73 = (1.4809789263016e-15 - fConst62);
	fConst74 = (2.38385660096139e-14 - fConst64);
	fConst75 = (3.0212983785597297e-14 - fConst66);
	fConst76 = ((fConst0 * (fConst44 + -1.2685958335763499e-16)) + 3.2109130517186899e-15);
	fConst77 = (fConst46 + -4.9338602296741301e-17);
	fConst78 = (1.75582214579149e-16 - fConst48);
	fConst79 = ((fConst0 * (fConst50 + -7.4048946315080199e-16)) + -1.04296301457845e-13);
	fConst80 = (fConst52 + -1.19192830048069e-14);
	fConst81 = (fConst54 + -1.5106491892798699e-14);
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
	double fSlow0 = (0.0070000000000000062 * double(fVslider0));
	double fSlow1 = (0.0070000000000000062 * double(fVslider1));
	double fSlow2 = (0.0070000000000000062 * double(fVslider2));
	for (int i = 0; (i < count); i = (i + 1)) {
		fRec0[0] = (fSlow0 + (0.99299999999999999 * fRec0[1]));
		fRec2[0] = (fSlow1 + (0.99299999999999999 * fRec2[1]));
		fRec3[0] = (fSlow2 + (0.99299999999999999 * fRec3[1]));
		double fTemp0 = (((fRec2[0] * ((fConst0 * (fConst38 + (fRec3[0] * (fConst39 + (fConst40 * fRec3[0]))))) + 1.30107041069324e-11)) + (fConst0 * (fConst41 + (fRec3[0] * (fConst42 + (fConst43 * fRec3[0])))))) + 3.05506357605318e-10);
		fRec1[0] = (double(input0[i]) - (((((fRec1[1] * (((fRec2[0] * ((fConst0 * (fConst3 + (fRec3[0] * (fConst5 + (fConst7 * fRec3[0]))))) + 5.2042816427729497e-11)) + (fConst0 * (fConst9 + (fRec3[0] * (fConst11 + (fConst13 * fRec3[0])))))) + 1.2220254304212699e-09)) + (fRec1[2] * (((fRec2[0] * ((fConst1 * (fConst14 + (fRec3[0] * (fConst15 + (fConst16 * fRec3[0]))))) + 7.8064224641594301e-11)) + (fConst1 * (fConst17 + (fRec3[0] * (fConst18 + (fConst19 * fRec3[0])))))) + 1.83303814563191e-09))) + (fRec1[3] * (((fRec2[0] * ((fConst0 * (fConst20 + (fRec3[0] * (fConst21 + (fConst22 * fRec3[0]))))) + 5.2042816427729497e-11)) + (fConst0 * (fConst23 + (fRec3[0] * (fConst24 + (fConst25 * fRec3[0])))))) + 1.2220254304212699e-09))) + (fRec1[4] * (((fRec2[0] * ((fConst0 * (fConst27 + (fRec3[0] * (fConst29 + (fConst31 * fRec3[0]))))) + 1.30107041069324e-11)) + (fConst0 * (fConst33 + (fRec3[0] * (fConst35 + (fConst37 * fRec3[0])))))) + 3.05506357605318e-10))) / fTemp0));
		output0[i] = FAUSTFLOAT((0.40000000000000002 * std::min<double>(0.75139999999999996, std::max<double>(-0.45140000000000002, (fConst1 * ((fRec0[0] * (((((fRec1[0] * (fConst45 + ((fConst0 * (fRec3[0] * (fConst47 + (fConst49 * fRec3[0])))) + (fRec2[0] * (fConst51 + (fConst0 * (fRec3[0] * (fConst53 + (fConst55 * fRec3[0]))))))))) + (fConst0 * (fRec1[1] * (fConst57 + ((fRec3[0] * (fConst59 + (fConst61 * fRec3[0]))) + (fRec2[0] * (fConst63 + (fRec3[0] * (fConst65 + (fConst67 * fRec3[0])))))))))) + (fRec1[2] * (fConst68 + ((fConst1 * (fRec3[0] * ((0.0 - (2.02098712291102e-19 * fRec3[0])) + 5.6789738153800206e-20))) + (fRec2[0] * (fConst69 + (fConst1 * (fRec3[0] * ((1.7387880464364199e-17 * fRec3[0]) + 1.37193379892063e-17))))))))) + (fConst0 * (fRec1[3] * (fConst70 + ((fRec3[0] * (fConst71 + (fConst72 * fRec3[0]))) + (fRec2[0] * (fConst73 + (fRec3[0] * (fConst74 + (fConst75 * fRec3[0])))))))))) + (fRec1[4] * (fConst76 + ((fConst0 * (fRec3[0] * (fConst77 + (fConst78 * fRec3[0])))) + (fRec2[0] * (fConst79 + (fConst0 * (fRec3[0] * (fConst80 + (fConst81 * fRec3[0]))))))))))) / fTemp0))))));
		fRec0[1] = fRec0[0];
		fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		for (int j0 = 4; (j0 > 0); j0 = (j0 - 1)) {
			fRec1[j0] = fRec1[(j0 - 1)];
		}
	}
#undef fVslider0
#undef fVslider1
#undef fVslider2
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case FUZZ: 
		fVslider2_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case SUSTAIN: 
		fVslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case VOLUME: 
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
   FUZZ, 
   SUSTAIN, 
   VOLUME, 
} PortIndex;
*/

} // end namespace hornet
