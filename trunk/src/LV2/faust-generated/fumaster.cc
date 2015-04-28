// generated from file '../src/LV2/faust/fumaster.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)


namespace fumaster {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	double 	fConst0;
	double 	fConst1;
	double 	fConst2;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec0[2];
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec1[2];
	double 	fConst9;
	double 	fConst10;
	double 	fConst11;
	double 	fConst12;
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
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec2[7];
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
	double 	fConst56;
	double 	fConst57;
	double 	fConst58;
	double 	fConst59;
	double 	fConst60;
	double 	fConst61;
	double 	fConst62;
	double 	fConst63;
	double 	fConst64;
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
	id = "fumaster";
	name = N_("Fuzz Master");
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
	for (int i=0; i<7; i++) fRec2[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = double(min(192000, max(1, fSamplingFreq)));
	fConst1 = (1.00949675143598e-28 * fConst0);
	fConst2 = (3.94912717206244e-15 + (fConst0 * (7.52873102578757e-17 + (fConst0 * (3.72110810064138e-19 + (fConst0 * (5.95381363906935e-22 + (fConst0 * (3.20513868924941e-25 + fConst1)))))))));
	fConst3 = (1.00799506674223e-28 * fConst0);
	fConst4 = (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (0 - (2.59175366383786e-25 + fConst3))) - 4.35259230096405e-22)) - 1.02583553103419e-19)) - 2.16974948431515e-18));
	fConst5 = (1.5016846937505e-31 * fConst0);
	fConst6 = (1.08487474215758e-15 + (fConst0 * (5.11414335446406e-17 + (fConst0 * (2.16655787499057e-19 + (fConst0 * (1.27917670111645e-22 + (fConst0 * (4.96235474586462e-26 - fConst5)))))))));
	fConst7 = (1.41775270516311e-29 * fConst0);
	fConst8 = ((fConst0 * (4.70999825737972e-24 + fConst7)) - 2.59478774349197e-21);
	fConst9 = (1.41775270516311e-27 * fConst0);
	fConst10 = ((fConst0 * (4.70999825737972e-22 + fConst9)) - 2.59478774349197e-19);
	fConst11 = (0 - (4.71779589725812e-22 + fConst9));
	fConst12 = (0 - (4.71779589725812e-24 + fConst7));
	fConst13 = ((fConst0 * (7.52873102578757e-17 + (fConst0 * ((fConst0 * (5.95381363906935e-22 + (fConst0 * (fConst1 - 3.20513868924941e-25)))) - 3.72110810064138e-19)))) - 3.94912717206244e-15);
	fConst14 = (fConst0 * ((fConst0 * (1.02583553103419e-19 + (fConst0 * ((fConst0 * (2.59175366383786e-25 - fConst3)) - 4.35259230096405e-22)))) - 2.16974948431515e-18));
	fConst15 = ((fConst0 * (5.11414335446406e-17 + (fConst0 * ((fConst0 * (1.27917670111645e-22 + (fConst0 * (0 - (4.96235474586462e-26 + fConst5))))) - 2.16655787499057e-19)))) - 1.08487474215758e-15);
	fConst16 = (6.0569805086159e-28 * fConst0);
	fConst17 = faustpower<2>(fConst0);
	fConst18 = ((fConst0 * (1.50574620515751e-16 + (fConst17 * ((fConst0 * (1.28205547569977e-24 - fConst16)) - 1.19076272781387e-21)))) - 1.57965086882498e-14);
	fConst19 = (6.0479704004534e-28 * fConst0);
	fConst20 = (fConst0 * ((fConst17 * (8.70518460192809e-22 + (fConst0 * (fConst19 - 1.03670146553514e-24)))) - 4.3394989686303e-18));
	fConst21 = (9.01010816250298e-31 * fConst0);
	fConst22 = ((fConst0 * (1.02282867089281e-16 + (fConst17 * ((fConst0 * (1.98494189834585e-25 + fConst21)) - 2.5583534022329e-22)))) - 4.3394989686303e-15);
	fConst23 = (1.51424512715397e-27 * fConst0);
	fConst24 = ((fConst0 * ((fConst0 * (1.11633243019242e-18 + (fConst0 * ((fConst0 * (fConst23 - 1.60256934462471e-24)) - 5.95381363906935e-22)))) - 7.52873102578757e-17)) - 1.97456358603122e-14);
	fConst25 = (1.51199260011335e-27 * fConst0);
	fConst26 = (fConst0 * (2.16974948431515e-18 + (fConst0 * ((fConst0 * (4.35259230096405e-22 + (fConst0 * (1.29587683191893e-24 - fConst25)))) - 3.07750659310257e-19))));
	fConst27 = (2.25252704062574e-30 * fConst0);
	fConst28 = ((fConst0 * ((fConst0 * (6.4996736249717e-19 + (fConst0 * ((fConst0 * (0 - (2.48117737293231e-25 + fConst27))) - 1.27917670111645e-22)))) - 5.11414335446406e-17)) - 5.42437371078788e-15);
	fConst29 = ((fConst17 * (2.38152545562774e-21 - (2.01899350287197e-27 * fConst17))) - 3.01149241031503e-16);
	fConst30 = (8.6789979372606e-18 + (fConst17 * ((2.01599013348447e-27 * fConst17) - 1.74103692038562e-21)));
	fConst31 = ((fConst17 * (5.11670680446579e-22 + (3.00336938750099e-30 * fConst17))) - 2.04565734178562e-16);
	fConst32 = (1.97456358603122e-14 + (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (1.60256934462471e-24 + fConst23)) - 5.95381363906935e-22)) - 1.11633243019242e-18)) - 7.52873102578757e-17)));
	fConst33 = (fConst0 * (2.16974948431515e-18 + (fConst0 * (3.07750659310257e-19 + (fConst0 * (4.35259230096405e-22 + (fConst0 * (0 - (1.29587683191893e-24 + fConst25)))))))));
	fConst34 = (5.42437371078788e-15 + (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (2.48117737293231e-25 - fConst27)) - 1.27917670111645e-22)) - 6.4996736249717e-19)) - 5.11414335446406e-17)));
	fConst35 = (1.57965086882498e-14 + (fConst0 * (1.50574620515751e-16 + (fConst17 * ((fConst0 * (0 - (1.28205547569977e-24 + fConst16))) - 1.19076272781387e-21)))));
	fConst36 = (fConst0 * ((fConst17 * (8.70518460192809e-22 + (fConst0 * (1.03670146553514e-24 + fConst19)))) - 4.3394989686303e-18));
	fConst37 = (4.3394989686303e-15 + (fConst0 * (1.02282867089281e-16 + (fConst17 * ((fConst0 * (fConst21 - 1.98494189834585e-25)) - 2.5583534022329e-22)))));
	fConst38 = (8.50651623097868e-29 * fConst0);
	fConst39 = (5.18957548698393e-21 + (fConst0 * (0 - (1.88399930295189e-23 + fConst38))));
	fConst40 = (8.50651623097868e-27 * fConst0);
	fConst41 = (5.18957548698393e-19 + (fConst0 * (0 - (1.88399930295189e-21 + fConst40))));
	fConst42 = (1.88711835890325e-21 + fConst40);
	fConst43 = (1.88711835890325e-23 + fConst38);
	fConst44 = (2.12662905774467e-28 * fConst0);
	fConst45 = (2.59478774349197e-21 + (fConst0 * (2.35499912868986e-23 + fConst44)));
	fConst46 = (2.12662905774467e-26 * fConst0);
	fConst47 = (2.59478774349197e-19 + (fConst0 * (2.35499912868986e-21 + fConst46)));
	fConst48 = (0 - (2.35889794862906e-21 + fConst46));
	fConst49 = (0 - (2.35889794862906e-23 + fConst44));
	fConst50 = (0 - (1.03791509739679e-20 + (2.83550541032623e-28 * fConst17)));
	fConst51 = (0 - (1.03791509739679e-18 + (2.83550541032623e-26 * fConst17)));
	fConst52 = (2.59478774349197e-21 + (fConst0 * (fConst44 - 2.35499912868986e-23)));
	fConst53 = (2.59478774349197e-19 + (fConst0 * (fConst46 - 2.35499912868986e-21)));
	fConst54 = (2.35889794862906e-21 - fConst46);
	fConst55 = (2.35889794862906e-23 - fConst44);
	fConst56 = (5.18957548698393e-21 + (fConst0 * (1.88399930295189e-23 - fConst38)));
	fConst57 = (5.18957548698393e-19 + (fConst0 * (1.88399930295189e-21 - fConst40)));
	fConst58 = (fConst40 - 1.88711835890325e-21);
	fConst59 = (fConst38 - 1.88711835890325e-23);
	fConst60 = ((fConst0 * (fConst9 - 4.70999825737972e-22)) - 2.59478774349197e-19);
	fConst61 = (4.71779589725812e-22 - fConst9);
	fConst62 = (4.71779589725812e-24 - fConst7);
	fConst63 = ((fConst0 * (fConst7 - 4.70999825737972e-24)) - 2.59478774349197e-21);
	fConst64 = faustpower<4>(fConst0);
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
	double 	fSlow2 = (0.01 * double(fslider2));
	double 	fSlow3 = (1 - fSlow2);
	for (int i=0; i<count; i++) {
		fRec0[0] = ((0.993 * fRec0[1]) + fSlow0);
		double fTemp0 = (5.42437371078787e-14 + (fConst0 * ((fRec0[0] * (fConst6 + (fConst4 * fRec0[0]))) + fConst2)));
		fRec1[0] = ((0.993 * fRec1[1]) + fSlow1);
		double fTemp1 = (double)input0[i];
		fRec2[0] = ((fSlow2 * fTemp1) - (((((((fRec2[1] * (3.25462422647273e-13 + (fConst0 * ((fRec0[0] * (fConst37 + (fConst36 * fRec0[0]))) + fConst35)))) + (fRec2[2] * (8.13656056618181e-13 + (fConst0 * ((fRec0[0] * (fConst34 + (fConst33 * fRec0[0]))) + fConst32))))) + (fRec2[3] * (1.08487474215758e-12 + (fConst17 * ((fRec0[0] * (fConst31 + (fConst30 * fRec0[0]))) + fConst29))))) + (fRec2[4] * (8.13656056618181e-13 + (fConst0 * ((fRec0[0] * (fConst28 + (fConst26 * fRec0[0]))) + fConst24))))) + (fRec2[5] * (3.25462422647273e-13 + (fConst0 * ((fRec0[0] * (fConst22 + (fConst20 * fRec0[0]))) + fConst18))))) + (fRec2[6] * (5.42437371078787e-14 + (fConst0 * ((fRec0[0] * (fConst15 + (fConst14 * fRec0[0]))) + fConst13))))) / fTemp0));
		output0[i] = (FAUSTFLOAT)((fSlow3 * fTemp1) + (fConst64 * ((((((((fRec2[0] * (fConst63 + ((fConst0 * (fRec0[0] * (fConst62 + (fConst61 * fRec1[0])))) + (fConst60 * fRec1[0])))) + (fRec2[1] * (((fConst0 * (fRec0[0] * (fConst59 + (fConst58 * fRec1[0])))) + (fConst57 * fRec1[0])) + fConst56))) + (fRec2[2] * (((fConst0 * (fRec0[0] * (fConst55 + (fConst54 * fRec1[0])))) + (fConst53 * fRec1[0])) + fConst52))) + (fRec2[3] * (((fConst17 * (fRec0[0] * (2.83550541032623e-28 + (2.83550541032623e-26 * fRec1[0])))) + (fConst51 * fRec1[0])) + fConst50))) + (fRec2[4] * (((fConst0 * (fRec0[0] * (fConst49 + (fConst48 * fRec1[0])))) + (fConst47 * fRec1[0])) + fConst45))) + (fRec2[5] * (((fConst0 * (fRec0[0] * (fConst43 + (fConst42 * fRec1[0])))) + (fConst41 * fRec1[0])) + fConst39))) + (fRec2[6] * (((fConst0 * (fRec0[0] * (fConst12 + (fConst11 * fRec1[0])))) + (fConst10 * fRec1[0])) + fConst8))) / fTemp0)));
		// post processing
		for (int i=6; i>0; i--) fRec2[i] = fRec2[i-1];
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
	case TONE: 
		fslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case VOLUME: 
		fslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case WET_DRY: 
		fslider2_ = (float*)data; // , 1e+02, 0.0, 1e+02, 1.0 
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
   TONE, 
   VOLUME, 
   WET_DRY, 
} PortIndex;
*/

} // end namespace fumaster
