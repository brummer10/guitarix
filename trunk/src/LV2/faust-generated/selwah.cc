// generated from file '../src/LV2/faust/selwah.dsp' by dsp2cc:
// Code generated with Faust 0.9.73 (http://faust.grame.fr)


namespace selwah {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	int 	iVec0[2];
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fConst4;
	double 	fRec2[2];
	double 	fRec1[2];
	double 	fRec0[2];
	double 	fConst5;
	double 	fConst6;
	double 	fRec5[2];
	double 	fConst7;
	double 	fConst8;
	double 	fRec4[2];
	double 	fRec3[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec6[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
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
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = double(iConst0);
	fConst2 = (3.2847328592148e-19 * fConst1);
	fConst3 = (1.73599395967319e-11 + (fConst1 * (5.11880447644045e-13 + (fConst1 * (5.6599406495133e-17 + fConst2)))));
	fConst4 = (0.10471975511965977 / double(iConst0));
	fConst5 = exp((0 - (1e+01 / double(iConst0))));
	fConst6 = (1.0 - fConst5);
	fConst7 = exp((0 - (1e+02 / double(iConst0))));
	fConst8 = (1.0 - fConst7);
	fConst9 = (6.9507309070366e-20 * fConst1);
	fConst10 = (fConst1 * ((fConst1 * (0 - (1.01737279942973e-17 + fConst9))) - 8.91391550989893e-14));
	fConst11 = (2.47965348716056e-19 * fConst1);
	fConst12 = ((fConst1 * (1.10300249541729e-13 + (fConst1 * (0 - (9.25643357134141e-18 + fConst11))))) - 2.02588988861339e-12);
	fConst13 = (3.81791996652528e-20 * fConst1);
	fConst14 = (2.03089386652508e-11 + (fConst1 * ((fConst1 * (8.47349775377979e-16 - fConst13)) - 1.29923285740847e-12)));
	fConst15 = (9.34067018664482e-21 * fConst1);
	fConst16 = (fConst1 * (2.81828342103572e-13 + (fConst1 * (fConst15 - 1.87102855759734e-16))));
	fConst17 = (9.34656187780755e-21 * fConst1);
	fConst18 = ((fConst1 * ((fConst1 * (1.86919114730712e-16 - fConst17)) - 2.77734086106026e-13)) - 6.21752156007224e-12);
	fConst19 = ((fConst1 * (5.11880447644045e-13 + (fConst1 * (fConst2 - 5.6599406495133e-17)))) - 1.73599395967319e-11);
	fConst20 = (fConst1 * ((fConst1 * (1.01737279942973e-17 - fConst9)) - 8.91391550989893e-14));
	fConst21 = (2.02588988861339e-12 + (fConst1 * (1.10300249541729e-13 + (fConst1 * (9.25643357134141e-18 - fConst11)))));
	fConst22 = (1.31389314368592e-18 * fConst1);
	fConst23 = faustpower<2>(fConst1);
	fConst24 = ((fConst23 * (1.13198812990266e-16 - fConst22)) - 3.47198791934638e-11);
	fConst25 = (2.78029236281464e-19 * fConst1);
	fConst26 = (fConst23 * (fConst25 - 2.03474559885945e-17));
	fConst27 = (9.91861394864224e-19 * fConst1);
	fConst28 = (4.05177977722679e-12 + (fConst23 * (fConst27 - 1.85128671426828e-17)));
	fConst29 = (1.78278310197979e-13 - (4.17043854422196e-19 * fConst23));
	fConst30 = (0 - (2.20600499083458e-13 + (1.48779209229634e-18 * fConst23)));
	fConst31 = ((1.97083971552888e-18 * fConst23) - 1.02376089528809e-12);
	fConst32 = (3.47198791934638e-11 + (fConst23 * (0 - (1.13198812990266e-16 + fConst22))));
	fConst33 = (fConst23 * (2.03474559885945e-17 + fConst25));
	fConst34 = ((fConst23 * (1.85128671426828e-17 + fConst27)) - 4.05177977722679e-12);
	fConst35 = (2189.236692273638 / double(iConst0));
	fConst36 = (1 + fConst35);
	fConst37 = (0.01 / fConst36);
	fConst38 = (1 - fConst35);
	fConst39 = (1.0 / fConst36);
	fConst40 = (1.52716798661011e-19 * fConst1);
	fConst41 = (4.06178773305017e-11 + (fConst23 * (fConst40 - 1.69469955075596e-15)));
	fConst42 = (3.73626807465793e-20 * fConst1);
	fConst43 = (fConst23 * (3.74205711519468e-16 - fConst42));
	fConst44 = (3.73862475112302e-20 * fConst1);
	fConst45 = ((fConst23 * (fConst44 - 3.73838229461424e-16)) - 1.24350431201445e-11);
	fConst46 = (2.59846571481694e-12 - (2.29075197991517e-19 * fConst23));
	fConst47 = ((5.60440211198689e-20 * fConst23) - 5.63656684207144e-13);
	fConst48 = (5.55468172212051e-13 - (5.60793712668453e-20 * fConst23));
	fConst49 = ((fConst23 * (1.69469955075596e-15 + fConst40)) - 4.06178773305017e-11);
	fConst50 = (fConst23 * (0 - (3.74205711519468e-16 + fConst42)));
	fConst51 = (1.24350431201445e-11 + (fConst23 * (3.73838229461424e-16 + fConst44)));
	fConst52 = ((fConst1 * ((fConst1 * (0 - (8.47349775377979e-16 + fConst13))) - 1.29923285740847e-12)) - 2.03089386652508e-11);
	fConst53 = (fConst1 * (2.81828342103572e-13 + (fConst1 * (1.87102855759734e-16 + fConst15))));
	fConst54 = (6.21752156007224e-12 + (fConst1 * ((fConst1 * (0 - (1.86919114730712e-16 + fConst17))) - 2.77734086106026e-13)));
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
	double 	fSlow0 = (fConst4 * double(fslider0));
	double 	fSlow1 = (0.007000000000000006 * double(fslider1));
	int 	iSlow2 = int(double(fslider2));
	double 	fSlow3 = double(fslider3);
	double 	fSlow4 = (fConst37 * fSlow3);
	double 	fSlow5 = (0.01 * fSlow3);
	double 	fSlow6 = (1 - fSlow5);
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		fRec2[0] = (fRec2[1] + (fSlow0 * (0 - fRec0[1])));
		fRec1[0] = ((1 + (fRec1[1] + (fSlow0 * fRec2[0]))) - iVec0[1]);
		fRec0[0] = fRec1[0];
		double fTemp0 = (double)input0[i];
		double fTemp1 = fabs(fTemp0);
		fRec5[0] = max(fTemp1, ((fConst5 * fRec5[1]) + (fConst6 * fTemp1)));
		fRec4[0] = ((fConst7 * fRec4[1]) + (fConst8 * fRec5[0]));
		fRec3[0] = ((0.993 * fRec3[1]) + (0.007000000000000006 * (1 - max(0.1, min(0.99, fRec4[0])))));
		fRec6[0] = ((0.993 * fRec6[1]) + fSlow1);
		double fTemp2 = ((iSlow2==0)? fRec6[0] : ((iSlow2==1)?fRec3[0]:max(0.01, min(0.9, (0.5 * (1 + fRec0[0]))))) );
		double fTemp3 = (1.0129449443067e-10 + (fConst1 * ((fTemp2 * (fConst12 + (fConst10 * fTemp2))) + fConst3)));
		fVec1[0] = (fSlow4 * fTemp0);
		fRec8[0] = ((fConst39 * ((fSlow5 * fTemp0) + (fConst38 * fRec8[1]))) - fVec1[1]);
		fRec7[0] = (fRec8[0] - (((((fRec7[1] * (4.05177977722679e-10 + (fConst1 * ((fTemp2 * (fConst34 + (fConst33 * fTemp2))) + fConst32)))) + (fRec7[2] * (6.07766966584018e-10 + (fConst23 * (fConst31 + (fTemp2 * (fConst30 + (fConst29 * fTemp2)))))))) + (fRec7[3] * (4.05177977722679e-10 + (fConst1 * ((fTemp2 * (fConst28 + (fConst26 * fTemp2))) + fConst24))))) + (fRec7[4] * (1.0129449443067e-10 + (fConst1 * ((fTemp2 * (fConst21 + (fConst20 * fTemp2))) + fConst19))))) / fTemp3));
		output0[i] = (FAUSTFLOAT)((fSlow6 * fTemp0) + (fConst1 * ((((((fRec7[0] * ((fTemp2 * (fConst54 + (fConst53 * fTemp2))) + fConst52)) + (fRec7[1] * ((fTemp2 * (fConst51 + (fConst50 * fTemp2))) + fConst49))) + (fConst1 * (fRec7[2] * ((fTemp2 * (fConst48 + (fConst47 * fTemp2))) + fConst46)))) + (fRec7[3] * ((fTemp2 * (fConst45 + (fConst43 * fTemp2))) + fConst41))) + (fRec7[4] * ((fTemp2 * (fConst18 + (fConst16 * fTemp2))) + fConst14))) / fTemp3)));
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

} // end namespace selwah
