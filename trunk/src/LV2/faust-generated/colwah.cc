// generated from file '../src/LV2/faust/colwah.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)


namespace colwah {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	int 	iVec0[2];
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fConst0;
	double 	fConst1;
	double 	fRec2[2];
	double 	fRec1[2];
	double 	fRec0[2];
	double 	fConst2;
	double 	fConst3;
	double 	fRec5[2];
	double 	fConst4;
	double 	fConst5;
	double 	fRec4[2];
	double 	fRec3[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec6[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
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
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fConst35;
	double 	fConst36;
	double 	fConst37;
	double 	fVec1[2];
	double 	fConst38;
	double 	fConst39;
	double 	fRec8[2];
	double 	fRec7[5];
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
	id = "colwah";
	name = N_("ColorSound Wah");
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
	for (int i=0; i<2; i++) iVec0[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<5; i++) fRec7[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = min(1.92e+05, max(1.0, (double)fSamplingFreq));
	fConst1 = (0.10471975511965977 / fConst0);
	fConst2 = exp((0 - (1e+01 / fConst0)));
	fConst3 = (1.0 - fConst2);
	fConst4 = exp((0 - (1e+02 / fConst0)));
	fConst5 = (1.0 - fConst4);
	fConst6 = double(fConst0);
	fConst7 = (6.9713352578405e-20 * fConst6);
	fConst8 = ((fConst6 * ((fConst6 * (0 - (5.83030654431973e-18 + fConst7))) - 2.29684974478901e-14)) - 2.35672055328543e-13);
	fConst9 = (3.97687174092932e-19 * fConst6);
	fConst10 = (7.09396691797023e-13 + (fConst6 * (1.90255378851155e-14 + (fConst6 * (2.70551577331849e-17 + fConst9)))));
	fConst11 = (6.54938497087849e-21 * fConst6);
	fConst12 = (3.94769224069978e-12 + (fConst6 * (1.2663530557943e-13 + (fConst6 * (5.15430968663743e-18 + fConst11)))));
	fConst13 = (8.31249052050881e-22 * fConst6);
	fConst14 = (2.9122542229415e-14 + (fConst6 * (fConst13 - 1.912505767204e-17)));
	fConst15 = (8.22579827731233e-22 * fConst6);
	fConst16 = ((fConst6 * (1.89445663105706e-17 - fConst15)) - 2.92311751105741e-14);
	fConst17 = (2.66926675132622e-21 * fConst6);
	fConst18 = (6.81633101368958e-13 + (fConst6 * ((fConst6 * (8.43534115306834e-17 - fConst17)) - 1.31405791553819e-13)));
	fConst19 = (2.35672055328543e-13 + (fConst6 * ((fConst6 * (5.83030654431973e-18 - fConst7)) - 2.29684974478901e-14)));
	fConst20 = ((fConst6 * (1.90255378851155e-14 + (fConst6 * (fConst9 - 2.70551577331849e-17)))) - 7.09396691797023e-13);
	fConst21 = ((fConst6 * (1.2663530557943e-13 + (fConst6 * (fConst11 - 5.15430968663743e-18)))) - 3.94769224069978e-12);
	fConst22 = (2.7885341031362e-19 * fConst6);
	fConst23 = faustpower<2>(fConst6);
	fConst24 = (4.71344110657085e-13 + (fConst23 * (fConst22 - 1.16606130886395e-17)));
	fConst25 = (1.59074869637173e-18 * fConst6);
	fConst26 = ((fConst23 * (5.41103154663699e-17 - fConst25)) - 1.41879338359405e-12);
	fConst27 = (2.6197539883514e-20 * fConst6);
	fConst28 = ((fConst23 * (1.03086193732749e-17 - fConst27)) - 7.89538448139956e-12);
	fConst29 = ((fConst23 * (1.16606130886395e-17 + fConst22)) - 4.71344110657085e-13);
	fConst30 = (1.41879338359405e-12 + (fConst23 * (0 - (5.41103154663699e-17 + fConst25))));
	fConst31 = (7.89538448139956e-12 + (fConst23 * (0 - (1.03086193732749e-17 + fConst27))));
	fConst32 = (4.59369948957802e-14 - (4.1828011547043e-19 * fConst23));
	fConst33 = ((2.38612304455759e-18 * fConst23) - 3.8051075770231e-14);
	fConst34 = ((3.9296309825271e-20 * fConst23) - 2.5327061115886e-13);
	fConst35 = (491.77839701345533 / fConst0);
	fConst36 = (1 + fConst35);
	fConst37 = (0.01 / fConst36);
	fConst38 = (1 - fConst35);
	fConst39 = (1.0 / fConst36);
	fConst40 = (3.32499620820352e-21 * fConst6);
	fConst41 = (3.825011534408e-17 - fConst40);
	fConst42 = (3.29031931092493e-21 * fConst6);
	fConst43 = (fConst42 - 3.78891326211413e-17);
	fConst44 = (1.06770670053049e-20 * fConst6);
	fConst45 = (1.36326620273792e-12 + (fConst23 * (fConst44 - 1.68706823061367e-16)));
	fConst46 = ((4.98749431230529e-21 * fConst23) - 5.824508445883e-14);
	fConst47 = (5.84623502211483e-14 - (4.9354789663874e-21 * fConst23));
	fConst48 = (2.62811583107638e-13 - (1.60156005079573e-20 * fConst23));
	fConst49 = (0 - (3.825011534408e-17 + fConst40));
	fConst50 = (3.78891326211413e-17 + fConst42);
	fConst51 = ((fConst23 * (1.68706823061367e-16 + fConst44)) - 1.36326620273792e-12);
	fConst52 = (2.9122542229415e-14 + (fConst6 * (1.912505767204e-17 + fConst13)));
	fConst53 = ((fConst6 * (0 - (1.89445663105706e-17 + fConst15))) - 2.92311751105741e-14);
	fConst54 = ((fConst6 * ((fConst6 * (0 - (8.43534115306834e-17 + fConst17))) - 1.31405791553819e-13)) - 6.81633101368958e-13);
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
	double 	fSlow0 = (fConst1 * double(fslider0));
	double 	fSlow1 = (4.748558434412966e-05 * (exp((5 * (1 - max(0.01, double(fslider1))))) - 1));
	int 	iSlow2 = int(double(fslider2));
	double 	fSlow3 = double(fslider3);
	double 	fSlow4 = (fConst37 * fSlow3);
	double 	fSlow5 = (0.01 * fSlow3);
	double 	fSlow6 = (1 - fSlow5);
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		fRec2[0] = ((fSlow0 * (0 - fRec0[1])) + fRec2[1]);
		fRec1[0] = ((1 + (fRec1[1] + (fSlow0 * fRec2[0]))) - iVec0[1]);
		fRec0[0] = fRec1[0];
		double fTemp0 = (double)input0[i];
		double fTemp1 = fabs(fTemp0);
		fRec5[0] = max(fTemp1, ((fConst3 * fTemp1) + (fConst2 * fRec5[1])));
		fRec4[0] = ((fConst4 * fRec4[1]) + (fConst5 * fRec5[0]));
		fRec3[0] = ((0.993 * fRec3[1]) + (0.007000000000000006 * max(0.02, min((double)1, fRec4[0]))));
		fRec6[0] = (fSlow1 + (0.993 * fRec6[1]));
		double fTemp2 = ((iSlow2==0)? fRec6[0] : ((iSlow2==1)?fRec3[0]:(1 - max(0.02, min(0.98, (0.5 * (1 + fRec0[0])))))) );
		double fTemp3 = (1.63948058636323e-11 + (fConst6 * (fConst12 + (fTemp2 * (fConst10 + (fConst8 * fTemp2))))));
		fVec1[0] = (fSlow4 * fTemp0);
		fRec8[0] = ((fConst39 * ((fSlow5 * fTemp0) + (fConst38 * fRec8[1]))) - fVec1[1]);
		fRec7[0] = (fRec8[0] - (((((fRec7[2] * (9.83688351817936e-11 + (fConst23 * (fConst34 + (fTemp2 * (fConst33 + (fConst32 * fTemp2))))))) + (fRec7[1] * (6.55792234545291e-11 + (fConst6 * (fConst31 + (fTemp2 * (fConst30 + (fConst29 * fTemp2)))))))) + (fRec7[3] * (6.55792234545291e-11 + (fConst6 * (fConst28 + (fTemp2 * (fConst26 + (fConst24 * fTemp2)))))))) + (fRec7[4] * (1.63948058636323e-11 + (fConst6 * (fConst21 + (fTemp2 * (fConst20 + (fConst19 * fTemp2)))))))) / fTemp3));
		output0[i] = (FAUSTFLOAT)((fSlow6 * fTemp0) + (fConst6 * ((((((fRec7[0] * (fConst54 + (fTemp2 * ((fConst6 * (fConst53 + (fConst52 * fTemp2))) - 6.25519484069141e-13)))) + (fRec7[1] * (fConst51 + (fTemp2 * ((fConst23 * (fConst50 + (fConst49 * fTemp2))) - 1.25103896813828e-12))))) + (fConst6 * (fRec7[2] * (fConst48 + (fTemp2 * (fConst47 + (fConst46 * fTemp2))))))) + (fRec7[3] * (fConst45 + (fTemp2 * (1.25103896813828e-12 + (fConst23 * (fConst43 + (fConst41 * fTemp2)))))))) + (fRec7[4] * (fConst18 + (fTemp2 * (6.25519484069141e-13 + (fConst6 * (fConst16 + (fConst14 * fTemp2)))))))) / fTemp3)));
		// post processing
		for (int i=4; i>0; i--) fRec7[i] = fRec7[i-1];
		fRec8[1] = fRec8[0];
		fVec1[1] = fVec1[0];
		fRec6[1] = fRec6[0];
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		iVec0[1] = iVec0[0];
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
	case WAH: 
		fslider1_ = (float*)data; // , 0.0, 0.0, 1.0, 0.01 
		break;
	case FREQ: 
		fslider0_ = (float*)data; // , 24.0, 24.0, 3.6e+02, 1.0 
		break;
	// static const value_pair fslider2_values[] = {{"manual"},{"auto"},{"alien"},{0}};
	case MODE: 
		fslider2_ = (float*)data; // , 0.0, 0.0, 2.0, 1.0 
		break;
	case WET_DRY: 
		fslider3_ = (float*)data; // , 1e+02, 0.0, 1e+02, 1.0 
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

} // end namespace colwah
