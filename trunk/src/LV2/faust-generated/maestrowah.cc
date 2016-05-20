// generated from file '../src/LV2/faust/maestrowah.dsp' by dsp2cc:
// Code generated with Faust 0.9.73 (http://faust.grame.fr)


namespace maestrowah {

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
	double 	fRec4[2];
	double 	fConst7;
	double 	fConst8;
	double 	fRec3[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec5[2];
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
	double 	fRec7[2];
	double 	fRec6[5];
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
	id = "maestrowah";
	name = N_("Maestro Wah");
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
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<5; i++) fRec6[i] = 0;
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
	fConst2 = (2.95651915836617e-20 * fConst1);
	fConst3 = (7.65730526965241e-11 + (fConst1 * (5.39738799500148e-13 + (fConst1 * (3.70386813965067e-17 + fConst2)))));
	fConst4 = (0.10471975511965977 / double(iConst0));
	fConst5 = exp((0 - (1e+01 / double(iConst0))));
	fConst6 = (1.0 - fConst5);
	fConst7 = exp((0 - (1e+02 / double(iConst0))));
	fConst8 = (1.0 - fConst7);
	fConst9 = (4.53925105453318e-22 * fConst1);
	fConst10 = (fConst1 * ((fConst1 * (0 - (2.20007271917577e-18 + fConst9))) - 1.9840085993285e-14));
	fConst11 = (3.15399184914731e-19 * fConst1);
	fConst12 = (3.968017198657e-12 + (fConst1 * (2.81635784152467e-14 + (fConst1 * (2.2050952353796e-17 + fConst11)))));
	fConst13 = (2.72075590065939e-21 * fConst1);
	fConst14 = (8.86819759919558e-14 + (fConst1 * (fConst13 - 2.47828940556324e-17)));
	fConst15 = (2.71455853073723e-21 * fConst1);
	fConst16 = ((fConst1 * (2.47794028705763e-17 - fConst15)) - 8.86817888313842e-14);
	fConst17 = (3.51316538913314e-20 * fConst1);
	fConst18 = (1.98647626221981e-11 + (fConst1 * ((fConst1 * (4.11229500551683e-16 - fConst17)) - 1.76902751745081e-12)));
	fConst19 = ((fConst1 * (5.39738799500148e-13 + (fConst1 * (fConst2 - 3.70386813965067e-17)))) - 7.65730526965241e-11);
	fConst20 = (fConst1 * ((fConst1 * (2.20007271917577e-18 - fConst9)) - 1.9840085993285e-14));
	fConst21 = ((fConst1 * (2.81635784152467e-14 + (fConst1 * (fConst11 - 2.2050952353796e-17)))) - 3.968017198657e-12);
	fConst22 = (1.18260766334647e-19 * fConst1);
	fConst23 = faustpower<2>(fConst1);
	fConst24 = ((fConst23 * (7.40773627930135e-17 - fConst22)) - 1.53146105393048e-10);
	fConst25 = (1.81570042181327e-21 * fConst1);
	fConst26 = (fConst23 * (fConst25 - 4.40014543835154e-18));
	fConst27 = (1.26159673965892e-18 * fConst1);
	fConst28 = ((fConst23 * (4.4101904707592e-17 - fConst27)) - 7.93603439731401e-12);
	fConst29 = (3.968017198657e-14 - (2.72355063271991e-21 * fConst23));
	fConst30 = ((1.89239510948839e-18 * fConst23) - 5.63271568304933e-14);
	fConst31 = ((1.7739114950197e-19 * fConst23) - 1.0794775990003e-12);
	fConst32 = (1.53146105393048e-10 + (fConst23 * (0 - (7.40773627930135e-17 + fConst22))));
	fConst33 = (fConst23 * (4.40014543835154e-18 + fConst25));
	fConst34 = (7.93603439731401e-12 + (fConst23 * (0 - (4.4101904707592e-17 + fConst27))));
	fConst35 = (203.47539521535035 / double(iConst0));
	fConst36 = (1 + fConst35);
	fConst37 = (0.01 / fConst36);
	fConst38 = (1 - fConst35);
	fConst39 = (1.0 / fConst36);
	fConst40 = (1.08830236026375e-20 * fConst1);
	fConst41 = (4.95657881112649e-17 - fConst40);
	fConst42 = (1.08582341229489e-20 * fConst1);
	fConst43 = (fConst42 - 4.95588057411526e-17);
	fConst44 = (1.40526615565326e-19 * fConst1);
	fConst45 = (3.97295252443962e-11 + (fConst23 * (fConst44 - 8.22459001103366e-16)));
	fConst46 = (3.53805503490162e-12 - (2.10789923347988e-19 * fConst23));
	fConst47 = ((1.63245354039563e-20 * fConst23) - 1.77363951983912e-13);
	fConst48 = (1.77363577662768e-13 - (1.62873511844234e-20 * fConst23));
	fConst49 = (0 - (4.95657881112649e-17 + fConst40));
	fConst50 = (4.95588057411526e-17 + fConst42);
	fConst51 = ((fConst23 * (8.22459001103366e-16 + fConst44)) - 3.97295252443962e-11);
	fConst52 = (8.86819759919558e-14 + (fConst1 * (2.47828940556324e-17 + fConst13)));
	fConst53 = ((fConst1 * (0 - (2.47794028705763e-17 + fConst15))) - 8.86817888313842e-14);
	fConst54 = ((fConst1 * ((fConst1 * (0 - (4.11229500551683e-16 + fConst17))) - 1.76902751745081e-12)) - 1.98647626221981e-11);
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
	double 	fSlow1 = (0.004073836948085289 * (exp((1 - double(fslider1))) - 1));
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
		fRec4[0] = max(fTemp1, ((fConst5 * fRec4[1]) + (fConst6 * fTemp1)));
		fRec3[0] = ((fConst7 * fRec3[1]) + (fConst8 * fRec4[0]));
		fRec5[0] = ((0.993 * fRec5[1]) + fSlow1);
		double fTemp2 = ((iSlow2==0)? fRec5[0] : ((iSlow2==1)?max(0.09, min(0.75, fRec3[0])):(1 - max(0.25, min(0.91, (0.5 * (1 + fRec0[0])))))) );
		double fTemp3 = (7.93603439731401e-10 + (fConst1 * ((fTemp2 * (fConst12 + (fConst10 * fTemp2))) + fConst3)));
		fVec1[0] = (fSlow4 * fTemp0);
		fRec7[0] = ((fConst39 * ((fSlow5 * fTemp0) + (fConst38 * fRec7[1]))) - fVec1[1]);
		fRec6[0] = (fRec7[0] - (((((fRec6[1] * (3.1744137589256e-09 + (fConst1 * ((fTemp2 * (fConst34 + (fConst33 * fTemp2))) + fConst32)))) + (fRec6[2] * (4.76162063838841e-09 + (fConst23 * (fConst31 + (fTemp2 * (fConst30 + (fConst29 * fTemp2)))))))) + (fRec6[3] * (3.1744137589256e-09 + (fConst1 * ((fTemp2 * (fConst28 + (fConst26 * fTemp2))) + fConst24))))) + (fRec6[4] * (7.93603439731401e-10 + (fConst1 * ((fTemp2 * (fConst21 + (fConst20 * fTemp2))) + fConst19))))) / fTemp3));
		output0[i] = (FAUSTFLOAT)((fSlow6 * fTemp0) + (fConst1 * ((((((fRec6[0] * (fConst54 + (fConst1 * (fTemp2 * (fConst53 + (fConst52 * fTemp2)))))) + (fRec6[1] * (fConst51 + (fConst23 * (fTemp2 * (fConst50 + (fConst49 * fTemp2))))))) + (fConst1 * (fRec6[2] * ((fTemp2 * (fConst48 + (fConst47 * fTemp2))) + fConst46)))) + (fRec6[3] * (fConst45 + (fConst23 * (fTemp2 * (fConst43 + (fConst41 * fTemp2))))))) + (fRec6[4] * (fConst18 + (fConst1 * (fTemp2 * (fConst16 + (fConst14 * fTemp2))))))) / fTemp3)));
		// post processing
		for (int i=4; i>0; i--) fRec6[i] = fRec6[i-1];
		fRec7[1] = fRec7[0];
		fVec1[1] = fVec1[0];
		fRec5[1] = fRec5[0];
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
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

} // end namespace maestrowah
