// generated from file '../src/LV2/faust/hornet.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)


namespace hornet {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec0[2];
	double 	fConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	double 	fConst9;
	double 	fConst10;
	double 	fConst11;
	double 	fConst12;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec1[2];
	double 	fConst13;
	double 	fConst14;
	double 	fConst15;
	double 	fConst16;
	double 	fConst17;
	double 	fConst18;
	double 	fConst19;
	double 	fConst20;
	double 	fConst21;
	double 	fConst22;
	double 	fConst23;
	double 	fConst24;
	double 	fConst25;
	double 	fConst26;
	double 	fConst27;
	double 	fConst28;
	double 	fConst29;
	double 	fConst30;
	double 	fConst31;
	double 	fConst32;
	double 	fConst33;
	double 	fConst34;
	double 	fConst35;
	double 	fConst36;
	double 	fConst37;
	double 	fConst38;
	double 	fConst39;
	double 	fConst40;
	double 	fConst41;
	double 	fConst42;
	double 	fConst43;
	double 	fConst44;
	double 	fConst45;
	double 	fConst46;
	double 	fConst47;
	double 	fConst48;
	double 	fConst49;
	double 	fConst50;
	double 	fConst51;
	double 	fConst52;
	double 	fConst53;
	double 	fConst54;
	double 	fConst55;
	double 	fRec2[5];
	double 	fConst56;
	double 	fConst57;
	double 	fConst58;
	double 	fConst59;
	double 	fConst60;
	double 	fConst61;
	double 	fConst62;
	double 	fConst63;
	double 	fConst64;
	double 	fConst65;
	double 	fConst66;
	double 	fConst67;
	double 	fConst68;
	double 	fConst69;
	double 	fConst70;
	double 	fConst71;
	double 	fConst72;
	double 	fConst73;
	double 	fConst74;
	double 	fConst75;
	double 	fConst76;
	double 	fConst77;
	double 	fConst78;
	double 	fConst79;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec3[2];

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
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<5; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = double(min(1.92e+05, max(1.0, (double)fSamplingFreq)));
	fConst1 = (2.57087433571955e-21 * fConst0);
	fConst2 = ((fConst0 * ((fConst0 * (0 - (3.20282580029198e-16 + fConst1))) - 1.59955479510613e-12)) - 1.59265781983301e-11);
	fConst3 = (7.22415688337201e-22 * fConst0);
	fConst4 = (5.81517816570128e-12 + (fConst0 * (5.83730418035165e-13 + (fConst0 * (1.15708148345401e-16 + fConst3)))));
	fConst5 = (1.84845864738235e-21 * fConst0);
	fConst6 = (4.3094216014379e-11 + (fConst0 * (1.25274019677064e-12 + (fConst0 * (2.48814775695488e-16 + fConst5)))));
	fConst7 = (2.22731835703847e-20 * fConst0);
	fConst8 = ((fConst0 * ((fConst0 * (0 - (1.15680872556631e-16 + fConst7))) - 1.02110226030461e-14)) - 8.86189120121937e-14);
	fConst9 = (2.63346198155234e-19 * fConst0);
	fConst10 = (1.09557219057811e-12 + (fConst0 * (1.23553821745518e-13 + (fConst0 * (1.39560593212619e-15 + fConst9)))));
	fConst11 = (2.00860283725342e-19 * fConst0);
	fConst12 = (2.30413820563986e-12 + (fConst0 * (1.10730441129884e-13 + (fConst0 * (1.06638545237487e-15 + fConst11)))));
	fConst13 = (3.36831187151837e-20 * fConst0);
	fConst14 = (1.75582214579149e-16 - fConst13);
	fConst15 = (9.4649563589667e-21 * fConst0);
	fConst16 = (fConst15 - 4.93386022967413e-17);
	fConst17 = (2.4218162356217e-20 * fConst0);
	fConst18 = (fConst17 - 1.26859583357635e-16);
	fConst19 = (2.89798007739403e-18 * fConst0);
	fConst20 = (fConst19 - 1.51064918927987e-14);
	fConst21 = (2.28655633153439e-18 * fConst0);
	fConst22 = (fConst21 - 1.19192830048069e-14);
	fConst23 = (1.45891323583538e-19 * fConst0);
	fConst24 = (fConst23 - 7.40489463150802e-16);
	fConst25 = (1.59265781983301e-11 + (fConst0 * ((fConst0 * (3.20282580029198e-16 - fConst1)) - 1.59955479510613e-12)));
	fConst26 = ((fConst0 * (5.83730418035165e-13 + (fConst0 * (fConst3 - 1.15708148345401e-16)))) - 5.81517816570128e-12);
	fConst27 = ((fConst0 * (1.25274019677064e-12 + (fConst0 * (fConst5 - 2.48814775695488e-16)))) - 4.3094216014379e-11);
	fConst28 = (8.86189120121937e-14 + (fConst0 * ((fConst0 * (1.15680872556631e-16 - fConst7)) - 1.02110226030461e-14)));
	fConst29 = ((fConst0 * (1.23553821745518e-13 + (fConst0 * (fConst9 - 1.39560593212619e-15)))) - 1.09557219057811e-12);
	fConst30 = ((fConst0 * (1.10730441129884e-13 + (fConst0 * (fConst11 - 1.06638545237487e-15)))) - 2.30413820563986e-12);
	fConst31 = (1.02834973428782e-20 * fConst0);
	fConst32 = faustpower<2>(fConst0);
	fConst33 = (3.18531563966602e-11 + (fConst32 * (fConst31 - 6.40565160058397e-16)));
	fConst34 = (2.8896627533488e-21 * fConst0);
	fConst35 = ((fConst32 * (2.31416296690802e-16 - fConst34)) - 1.16303563314026e-11);
	fConst36 = (7.39383458952941e-21 * fConst0);
	fConst37 = ((fConst32 * (4.97629551390976e-16 - fConst36)) - 8.6188432028758e-11);
	fConst38 = (8.9092734281539e-20 * fConst0);
	fConst39 = (1.77237824024387e-13 + (fConst32 * (fConst38 - 2.31361745113263e-16)));
	fConst40 = (1.05338479262093e-18 * fConst0);
	fConst41 = ((fConst32 * (2.79121186425238e-15 - fConst40)) - 2.19114438115622e-12);
	fConst42 = (8.03441134901368e-19 * fConst0);
	fConst43 = ((fConst32 * (2.13277090474974e-15 - fConst42)) - 4.60827641127972e-12);
	fConst44 = ((fConst32 * (6.40565160058397e-16 + fConst31)) - 3.18531563966602e-11);
	fConst45 = (1.16303563314026e-11 + (fConst32 * (0 - (2.31416296690802e-16 + fConst34))));
	fConst46 = (8.6188432028758e-11 + (fConst32 * (0 - (4.97629551390976e-16 + fConst36))));
	fConst47 = ((fConst32 * (2.31361745113263e-16 + fConst38)) - 1.77237824024387e-13);
	fConst48 = (2.19114438115622e-12 + (fConst32 * (0 - (2.79121186425238e-15 + fConst40))));
	fConst49 = (4.60827641127972e-12 + (fConst32 * (0 - (2.13277090474974e-15 + fConst42))));
	fConst50 = (3.19910959021226e-12 - (1.54252460143173e-20 * fConst32));
	fConst51 = ((4.33449413002321e-21 * fConst32) - 1.16746083607033e-12);
	fConst52 = ((1.10907518842941e-20 * fConst32) - 2.50548039354128e-12);
	fConst53 = (2.04220452060922e-14 - (1.33639101422308e-19 * fConst32));
	fConst54 = ((1.5800771889314e-18 * fConst32) - 2.47107643491035e-13);
	fConst55 = ((1.20516170235205e-18 * fConst32) - 2.21460882259768e-13);
	fConst56 = (0 - (1.75582214579149e-16 + fConst13));
	fConst57 = (4.93386022967413e-17 + fConst15);
	fConst58 = (1.26859583357635e-16 + fConst17);
	fConst59 = (1.51064918927987e-14 + fConst19);
	fConst60 = (1.19192830048069e-14 + fConst21);
	fConst61 = (7.40489463150802e-16 + fConst23);
	fConst62 = (1.15919203095761e-17 * fConst0);
	fConst63 = (3.02129837855973e-14 - fConst62);
	fConst64 = (9.14622532613756e-18 * fConst0);
	fConst65 = (2.38385660096139e-14 - fConst64);
	fConst66 = (5.83565294334152e-19 * fConst0);
	fConst67 = (1.4809789263016e-15 - fConst66);
	fConst68 = (1.34732474860735e-19 * fConst0);
	fConst69 = (fConst68 - 3.51164429158298e-16);
	fConst70 = (3.78598254358668e-20 * fConst0);
	fConst71 = (9.86772045934826e-17 - fConst70);
	fConst72 = (9.6872649424868e-20 * fConst0);
	fConst73 = (2.53719166715271e-16 - fConst72);
	fConst74 = (2.53719166715271e-16 + fConst72);
	fConst75 = (1.4809789263016e-15 + fConst66);
	fConst76 = (2.38385660096139e-14 + fConst64);
	fConst77 = (0 - (3.02129837855973e-14 + fConst62));
	fConst78 = (9.86772045934826e-17 + fConst70);
	fConst79 = (3.51164429158298e-16 + fConst68);
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
#define fslider2 (*fslider2_)
	double 	fSlow0 = (0.007000000000000006 * double(fslider0));
	double 	fSlow1 = (0.007000000000000006 * double(fslider1));
	double 	fSlow2 = (0.007000000000000006 * double(fslider2));
	for (int i=0; i<count; i++) {
		fRec0[0] = (fSlow0 + (0.993 * fRec0[1]));
		fRec1[0] = (fSlow1 + (0.993 * fRec1[1]));
		double fTemp0 = (3.05506357605318e-10 + ((fRec1[0] * (1.30107041069324e-11 + (fConst0 * (fConst12 + (fRec0[0] * (fConst10 + (fConst8 * fRec0[0]))))))) + (fConst0 * (fConst6 + (fRec0[0] * (fConst4 + (fConst2 * fRec0[0])))))));
		fRec2[0] = ((double)input0[i] - (((((fRec2[2] * (1.83303814563191e-09 + ((fRec1[0] * (7.80642246415943e-11 + (fConst32 * (fConst55 + (fRec0[0] * (fConst54 + (fConst53 * fRec0[0]))))))) + (fConst32 * (fConst52 + (fRec0[0] * (fConst51 + (fConst50 * fRec0[0])))))))) + (fRec2[1] * (1.22202543042127e-09 + ((fRec1[0] * (5.20428164277295e-11 + (fConst0 * (fConst49 + (fRec0[0] * (fConst48 + (fConst47 * fRec0[0]))))))) + (fConst0 * (fConst46 + (fRec0[0] * (fConst45 + (fConst44 * fRec0[0]))))))))) + (fRec2[3] * (1.22202543042127e-09 + ((fRec1[0] * (5.20428164277295e-11 + (fConst0 * (fConst43 + (fRec0[0] * (fConst41 + (fConst39 * fRec0[0]))))))) + (fConst0 * (fConst37 + (fRec0[0] * (fConst35 + (fConst33 * fRec0[0]))))))))) + (fRec2[4] * (3.05506357605318e-10 + ((fRec1[0] * (1.30107041069324e-11 + (fConst0 * (fConst30 + (fRec0[0] * (fConst29 + (fConst28 * fRec0[0]))))))) + (fConst0 * (fConst27 + (fRec0[0] * (fConst26 + (fConst25 * fRec0[0]))))))))) / fTemp0));
		fRec3[0] = (fSlow2 + (0.993 * fRec3[1]));
		output0[i] = (FAUSTFLOAT)(0.4 * min(0.7514, max(-0.4514, (fConst32 * ((fRec3[0] * (((fConst0 * ((fRec2[1] * (((fRec0[0] * ((fConst79 * fRec0[0]) - fConst78)) + (fRec1[0] * ((fRec0[0] * ((fConst77 * fRec0[0]) - fConst76)) - fConst75))) - fConst74)) + (fRec2[3] * (fConst73 + ((fRec0[0] * (fConst71 + (fConst69 * fRec0[0]))) + (fRec1[0] * (fConst67 + (fRec0[0] * (fConst65 + (fConst63 * fRec0[0])))))))))) + ((fRec2[0] * (3.21091305171869e-15 + ((fRec1[0] * ((fConst0 * (fConst61 + (fRec0[0] * (fConst60 + (fConst59 * fRec0[0]))))) - 1.04296301457845e-13)) + (fConst0 * (fConst58 + (fRec0[0] * (fConst57 + (fConst56 * fRec0[0])))))))) + (fRec2[2] * (((fRec1[0] * (2.08592602915691e-13 + (fConst32 * (8.75347941501228e-19 + (fRec0[0] * (1.37193379892063e-17 + (1.73878804643642e-17 * fRec0[0]))))))) + (fConst32 * (1.45308974137302e-19 + (fRec0[0] * (5.67897381538002e-20 - (2.02098712291102e-19 * fRec0[0])))))) - 6.42182610343738e-15)))) + (fRec2[4] * (3.21091305171869e-15 + ((fRec1[0] * ((fConst0 * (fConst24 + (fRec0[0] * (fConst22 + (fConst20 * fRec0[0]))))) - 1.04296301457845e-13)) + (fConst0 * (fConst18 + (fRec0[0] * (fConst16 + (fConst14 * fRec0[0])))))))))) / fTemp0)))));
		// post processing
		fRec3[1] = fRec3[0];
		for (int i=4; i>0; i--) fRec2[i] = fRec2[i-1];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
	}
#undef fslider0
#undef fslider1
#undef fslider2
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
		fslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case SUSTAIN: 
		fslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case VOLUME: 
		fslider2_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
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
