// generated from file '../src/LV2/faust/fuzzfacefm.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)


namespace fuzzfacefm {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	double 	fConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec0[2];
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	double 	fConst9;
	double 	fConst10;
	double 	fConst11;
	double 	fConst12;
	double 	fConst13;
	double 	fConst14;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec1[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec2[2];
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
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fRec3[2];
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
	double 	fConst80;
	double 	fRec4[4];
	double 	fConst81;
	double 	fConst82;
	double 	fConst83;
	double 	fConst84;
	double 	fConst85;
	double 	fConst86;
	double 	fConst87;
	double 	fConst88;
	double 	fConst89;
	double 	fConst90;
	double 	fConst91;
	double 	fConst92;
	double 	fConst93;
	double 	fConst94;
	double 	fConst95;
	double 	fConst96;
	double 	fConst97;
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
	id = "fuzzfacefm";
	name = N_("Fuzz Face Fuller");
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
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<4; i++) fRec4[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = double(min(192000, max(1, fSamplingFreq)));
	fConst1 = (5.60496524842164e-17 * fConst0);
	fConst2 = (1.69410806769336e-10 + (fConst0 * (1.63110208134281e-12 + fConst1)));
	fConst3 = (2.51786247207522e-17 * fConst0);
	fConst4 = ((fConst0 * (0 - (1.61641996632585e-12 + fConst3))) - 1.6091784998802e-10);
	fConst5 = (7.09868387007524e-14 * fConst0);
	fConst6 = (7.07787491781686e-12 + fConst5);
	fConst7 = (7.09616600760317e-14 * fConst0);
	fConst8 = (0 - (7.07536443616085e-12 + fConst7));
	fConst9 = (1.41557498356337e-16 * fConst0);
	fConst10 = (7.17715343346006e-56 - fConst9);
	fConst11 = (1.41507288723217e-16 * fConst0);
	fConst12 = (fConst11 - 7.60754167271764e-56);
	fConst13 = (5.02096331201311e-20 * fConst0);
	fConst14 = ((fConst0 * (3.21835699976039e-15 + fConst13)) - 1.53335572595511e-54);
	fConst15 = (7.14615106636066e-14 * fConst0);
	fConst16 = ((fConst0 * (0 - (7.44787041826973e-12 + fConst15))) - 3.21721587173494e-11);
	fConst17 = (7.14054610111223e-14 * fConst0);
	fConst18 = (3.21607474370948e-11 + (fConst0 * (7.44216743501989e-12 + fConst17)));
	fConst19 = (1.1177069911304e-19 * fConst0);
	fConst20 = ((fConst0 * (0 - (3.24149709132582e-15 + fConst19))) - 1.46288954534563e-14);
	fConst21 = (1.42504059392599e-16 * fConst0);
	fConst22 = ((fConst0 * (6.43443174346988e-16 + fConst21)) - 3.26234246975457e-55);
	fConst23 = (1.42392288693486e-16 * fConst0);
	fConst24 = (3.45797348759893e-55 + (fConst0 * (0 - (6.43214948741896e-16 + fConst23))));
	fConst25 = (2.0681037922594e-13 * fConst0);
	fConst26 = (4.74739615579661e-12 - fConst25);
	fConst27 = (1.65448303380752e-13 * fConst0);
	fConst28 = (fConst27 - 3.79791692463729e-12);
	fConst29 = (1.12549866245409e-13 * fConst0);
	fConst30 = (2.58361695553557e-12 - fConst29);
	fConst31 = (1.40687332806762e-13 * fConst0);
	fConst32 = (fConst31 - 3.22952119441946e-12);
	fConst33 = ((fConst0 * (1.63110208134281e-12 - fConst1)) - 1.69410806769336e-10);
	fConst34 = (1.6091784998802e-10 + (fConst0 * (fConst3 - 1.61641996632585e-12)));
	fConst35 = (7.07787491781686e-12 - fConst5);
	fConst36 = (fConst7 - 7.07536443616085e-12);
	fConst37 = (7.17715343346006e-56 + fConst9);
	fConst38 = (0 - (7.60754167271764e-56 + fConst11));
	fConst39 = (1.53335572595511e-54 + (fConst0 * (3.21835699976039e-15 - fConst13)));
	fConst40 = (3.21721587173494e-11 + (fConst0 * (fConst15 - 7.44787041826973e-12)));
	fConst41 = ((fConst0 * (7.44216743501989e-12 - fConst17)) - 3.21607474370948e-11);
	fConst42 = (1.46288954534563e-14 + (fConst0 * (fConst19 - 3.24149709132582e-15)));
	fConst43 = (3.26234246975457e-55 + (fConst0 * (6.43443174346988e-16 - fConst21)));
	fConst44 = ((fConst0 * (fConst23 - 6.43214948741896e-16)) - 3.45797348759893e-55);
	fConst45 = (7.55358741622564e-17 * fConst0);
	fConst46 = (1.6091784998802e-10 + (fConst0 * (1.61641996632585e-12 - fConst45)));
	fConst47 = (2.12960516102257e-13 * fConst0);
	fConst48 = (fConst47 - 7.07787491781686e-12);
	fConst49 = (2.12884980228095e-13 * fConst0);
	fConst50 = (7.07536443616085e-12 - fConst49);
	fConst51 = (4.24672495069012e-16 * fConst0);
	fConst52 = (0 - (7.17715343346006e-56 + fConst51));
	fConst53 = (4.24521866169651e-16 * fConst0);
	fConst54 = (7.60754167271764e-56 + fConst53);
	fConst55 = (1.50628899360393e-19 * fConst0);
	fConst56 = (1.53335572595511e-54 + (fConst0 * (fConst55 - 3.21835699976039e-15)));
	fConst57 = (2.1438453199082e-13 * fConst0);
	fConst58 = (3.21721587173494e-11 + (fConst0 * (7.44787041826973e-12 - fConst57)));
	fConst59 = (2.14216383033367e-13 * fConst0);
	fConst60 = ((fConst0 * (fConst59 - 7.44216743501989e-12)) - 3.21607474370948e-11);
	fConst61 = (1.68148957452649e-16 * fConst0);
	fConst62 = ((fConst0 * (fConst61 - 1.63110208134281e-12)) - 1.69410806769336e-10);
	fConst63 = (3.35312097339121e-19 * fConst0);
	fConst64 = (1.46288954534563e-14 + (fConst0 * (3.24149709132582e-15 - fConst63)));
	fConst65 = (4.27512178177797e-16 * fConst0);
	fConst66 = (3.26234246975457e-55 + (fConst0 * (fConst65 - 6.43443174346988e-16)));
	fConst67 = (4.27176866080457e-16 * fConst0);
	fConst68 = ((fConst0 * (6.43214948741896e-16 - fConst67)) - 3.45797348759893e-55);
	fConst69 = (1.69410806769336e-10 + (fConst0 * (0 - (1.63110208134281e-12 + fConst61))));
	fConst70 = ((fConst0 * (1.61641996632585e-12 + fConst45)) - 1.6091784998802e-10);
	fConst71 = (0 - (7.07787491781686e-12 + fConst47));
	fConst72 = (7.07536443616085e-12 + fConst49);
	fConst73 = (fConst51 - 7.17715343346006e-56);
	fConst74 = (7.60754167271764e-56 - fConst53);
	fConst75 = ((fConst0 * (0 - (3.21835699976039e-15 + fConst55))) - 1.53335572595511e-54);
	fConst76 = ((fConst0 * (7.44787041826973e-12 + fConst57)) - 3.21721587173494e-11);
	fConst77 = (3.21607474370948e-11 + (fConst0 * (0 - (7.44216743501989e-12 + fConst59))));
	fConst78 = ((fConst0 * (3.24149709132582e-15 + fConst63)) - 1.46288954534563e-14);
	fConst79 = ((fConst0 * (0 - (6.43443174346988e-16 + fConst65))) - 3.26234246975457e-55);
	fConst80 = (3.45797348759893e-55 + (fConst0 * (6.43214948741896e-16 + fConst67)));
	fConst81 = (4.96344910142255e-13 * fConst0);
	fConst82 = (3.79791692463729e-12 - fConst81);
	fConst83 = (4.22061998420285e-13 * fConst0);
	fConst84 = (3.22952119441946e-12 - fConst83);
	fConst85 = (3.37649598736228e-13 * fConst0);
	fConst86 = (fConst85 - 2.58361695553557e-12);
	fConst87 = (6.20431137677819e-13 * fConst0);
	fConst88 = (fConst87 - 4.74739615579661e-12);
	fConst89 = (0 - (4.74739615579661e-12 + fConst87));
	fConst90 = (3.79791692463729e-12 + fConst81);
	fConst91 = (3.22952119441946e-12 + fConst83);
	fConst92 = (0 - (2.58361695553557e-12 + fConst85));
	fConst93 = (4.74739615579661e-12 + fConst25);
	fConst94 = (0 - (3.79791692463729e-12 + fConst27));
	fConst95 = (0 - (3.22952119441946e-12 + fConst31));
	fConst96 = (2.58361695553557e-12 + fConst29);
	fConst97 = faustpower<2>(fConst0);
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
#define fslider3 (*fslider3_)
	double 	fSlow0 = (0.007000000000000006 * (1 - double(fslider0)));
	double 	fSlow1 = (0.007000000000000006 * (1 - double(fslider1)));
	double 	fSlow2 = (0.007000000000000006 * double(fslider2));
	double 	fSlow3 = (0.007000000000000006 * (1 - double(fslider3)));
	for (int i=0; i<count; i++) {
		fRec0[0] = ((0.993 * fRec0[1]) + fSlow0);
		fRec1[0] = ((0.993 * fRec1[1]) + fSlow1);
		fRec2[0] = ((0.993 * fRec2[1]) + fSlow2);
		double fTemp0 = (7.31444772672817e-10 + ((fRec1[0] * (6.96979875434139e-54 + (fConst0 * ((fRec0[0] * (fConst24 + (fConst22 * fRec0[0]))) + fConst20)))) + (fConst0 * (((fRec0[0] * (fConst18 + (fConst16 * fRec0[0]))) + (fRec2[0] * (((fRec1[0] * (fConst14 + (fConst0 * (fRec0[0] * (fConst12 + (fConst10 * fRec0[0])))))) + (fConst0 * (fRec0[0] * (fConst8 + (fConst6 * fRec0[0]))))) + fConst4))) + fConst2))));
		fRec3[0] = ((0.993 * fRec3[1]) + fSlow3);
		double fTemp1 = (1.63788262077463e-13 * fRec3[0]);
		double fTemp2 = (1.66004130328897e-15 * fRec3[0]);
		double fTemp3 = (1.12927979815576e-15 * fRec3[0]);
		double fTemp4 = (1.11420586447254e-13 * fRec3[0]);
		fRec4[0] = ((double)input0[i] - ((((fRec4[1] * (2.19433431801845e-09 + ((fRec1[0] * (2.09093962630242e-53 + (fConst0 * ((fRec0[0] * (fConst80 + (fConst79 * fRec0[0]))) + fConst78)))) + (fConst0 * (((fRec0[0] * (fConst77 + (fConst76 * fRec0[0]))) + (fRec2[0] * (((fRec1[0] * (fConst75 + (fConst0 * (fRec0[0] * (fConst74 + (fConst73 * fRec0[0])))))) + (fConst0 * (fRec0[0] * (fConst72 + (fConst71 * fRec0[0]))))) + fConst70))) + fConst69))))) + (fRec4[2] * (2.19433431801845e-09 + ((fRec1[0] * (2.09093962630242e-53 + (fConst0 * ((fRec0[0] * (fConst68 + (fConst66 * fRec0[0]))) + fConst64)))) + (fConst0 * (fConst62 + ((fRec0[0] * (fConst60 + (fConst58 * fRec0[0]))) + (fRec2[0] * (((fRec1[0] * (fConst56 + (fConst0 * (fRec0[0] * (fConst54 + (fConst52 * fRec0[0])))))) + (fConst0 * (fRec0[0] * (fConst50 + (fConst48 * fRec0[0]))))) + fConst46))))))))) + (fRec4[3] * (7.31444772672817e-10 + ((fRec1[0] * (6.96979875434139e-54 + (fConst0 * ((fRec0[0] * (fConst44 + (fConst43 * fRec0[0]))) + fConst42)))) + (fConst0 * (((fRec0[0] * (fConst41 + (fConst40 * fRec0[0]))) + (fRec2[0] * (((fRec1[0] * (fConst39 + (fConst0 * (fRec0[0] * (fConst38 + (fConst37 * fRec0[0])))))) + (fConst0 * (fRec0[0] * (fConst36 + (fConst35 * fRec0[0]))))) + fConst34))) + fConst33)))))) / fTemp0));
		double fTemp5 = (4.98012390986691e-15 * fRec3[0]);
		double fTemp6 = (4.91364786232388e-13 * fRec3[0]);
		double fTemp7 = (3.34261759341761e-13 * fRec3[0]);
		double fTemp8 = (3.38783939446729e-15 * fRec3[0]);
		output0[i] = (FAUSTFLOAT)(fConst97 * (((((fRec4[0] * ((((fRec1[0] * (((fConst0 * (fRec0[0] * (1.39275733059067e-13 + ((fRec0[0] * (1.4115997476947e-15 + (0 - fTemp3))) - fTemp4)))) + (fConst96 * fRec3[0])) + fConst95)) + (fConst0 * (fRec0[0] * ((fTemp1 + (fRec0[0] * (fTemp2 - 2.07505162911121e-15))) - 2.04735327596828e-13)))) + (fConst94 * fRec3[0])) + fConst93)) + (fRec4[1] * ((((fRec1[0] * (((fConst0 * (fRec0[0] * ((fTemp7 + (fRec0[0] * (fTemp8 - 4.23479924308411e-15))) - 4.17827199177201e-13))) + (fConst92 * fRec3[0])) + fConst91)) + (fConst0 * (fRec0[0] * (6.14205982790485e-13 + ((fRec0[0] * (6.22515488733364e-15 + (0 - fTemp5))) - fTemp6))))) + (fConst90 * fRec3[0])) + fConst89))) + (fRec4[2] * (fConst88 + (((fRec1[0] * (((fConst0 * (fRec0[0] * (4.17827199177201e-13 + ((fRec0[0] * (4.23479924308411e-15 + (0 - fTemp8))) - fTemp7)))) + (fConst86 * fRec3[0])) + fConst84)) + (fConst0 * (fRec0[0] * ((fTemp6 + (fRec0[0] * (fTemp5 - 6.22515488733364e-15))) - 6.14205982790485e-13)))) + (fConst82 * fRec3[0]))))) + (fRec4[3] * ((((fRec1[0] * (fConst32 + ((fConst0 * (fRec0[0] * ((fTemp4 + (fRec0[0] * (fTemp3 - 1.4115997476947e-15))) - 1.39275733059067e-13))) + (fConst30 * fRec3[0])))) + (fConst0 * (fRec0[0] * (2.04735327596828e-13 + ((fRec0[0] * (2.07505162911121e-15 + (0 - fTemp2))) - fTemp1))))) + (fConst28 * fRec3[0])) + fConst26))) / fTemp0));
		// post processing
		for (int i=3; i>0; i--) fRec4[i] = fRec4[i-1];
		fRec3[1] = fRec3[0];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
	}
#undef fslider0
#undef fslider1
#undef fslider2
#undef fslider3
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case DRIVE: 
		fslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case FUZZ: 
		fslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case INPUT: 
		fslider2_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case VOLUME: 
		fslider3_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
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
   DRIVE, 
   FUZZ, 
   INPUT, 
   VOLUME, 
} PortIndex;
*/

} // end namespace fuzzfacefm
