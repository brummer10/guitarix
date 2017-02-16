// generated from file '../src/LV2/faust/gxtubevibrato.dsp' by dsp2cc:
// Code generated with Faust 0.9.73 (http://faust.grame.fr)


namespace gxtubevibrato {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	int 	iVec0[2];
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec0[2];
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fRec2[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec3[2];
	int 	IOTA;
	double *fVec1;
	double 	fConst8;
	double 	fConst9;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fConst10;
	int 	iRec9[2];
	int 	iRec8[2];
	double 	fConst11;
	double 	fRec12[2];
	double 	fRec11[2];
	double 	fRec10[2];
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT	*fcheckbox0_;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fConst12;
	double 	fRec4[2];
	double 	fRec5[2];
	double 	fRec6[2];
	double 	fRec7[2];
	double 	fConst13;
	double 	fRec1[2];
	double 	fConst14;
	bool mem_allocated;
	void mem_alloc();
	void mem_free();
	void connect(uint32_t port,void* data);
	void clear_state_f();
	int activate(bool start);
	void init(uint32_t samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);

	static void clear_state_f_static(PluginLV2*);
	static int activate_static(bool start, PluginLV2*);
	static void init_static(uint32_t samplingFreq, PluginLV2*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginLV2(),
	  fVec1(0),
	  mem_allocated(false) {
	version = PLUGINLV2_VERSION;
	id = "gxtubevibrato";
	name = "?gxtubevibrato";
	mono_audio = compute_static;
	stereo_audio = 0;
	set_samplerate = init_static;
	activate_plugin = activate_static;
	connect_ports = connect_static;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int i=0; i<2; i++) iVec0[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<65536; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) iRec9[i] = 0;
	for (int i=0; i<2; i++) iRec8[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
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
	fConst2 = (2.08237464507809e-05 * fConst1);
	fConst3 = (0.000460170362516827 + fConst2);
	fConst4 = ((0.000460170362516827 - fConst2) / fConst3);
	fConst5 = (2.08237299868718e-05 * fConst1);
	fConst6 = (0.000460960630154374 + fConst5);
	fConst7 = ((0.000460960630154374 - fConst5) / fConst6);
	IOTA = 0;
	fConst8 = (1e+01 / double(iConst0));
	fConst9 = (0 - fConst8);
	fConst10 = (0.5 * iConst0);
	fConst11 = (6.283185307179586 / double(iConst0));
	fConst12 = (0.005 * iConst0);
	fConst13 = (0.1 * (fConst1 / fConst6));
	fConst14 = (fConst1 / fConst3);
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void Dsp::mem_alloc()
{
	if (!fVec1) fVec1 = new double[65536];
	mem_allocated = true;
}

void Dsp::mem_free()
{
	mem_allocated = false;
	if (fVec1) { delete fVec1; fVec1 = 0; }
}

int Dsp::activate(bool start)
{
	if (start) {
		if (!mem_allocated) {
			mem_alloc();
			clear_state_f();
		}
	} else if (mem_allocated) {
		mem_free();
	}
	return 0;
}

int Dsp::activate_static(bool start, PluginLV2 *p)
{
	return static_cast<Dsp*>(p)->activate(start);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
#define fslider2 (*fslider2_)
#define fcheckbox0 (*fcheckbox0_)
#define fslider3 (*fslider3_)
	double 	fSlow0 = (0.004073836948085289 * (exp((1 - double(fslider0))) - 1));
	double 	fSlow1 = (0.004073836948085289 * (exp(double(fslider1)) - 1));
	double 	fSlow2 = double(fslider2);
	int 	iSlow3 = int((fConst10 / double(fSlow2)));
	double 	fSlow4 = (1.0 / double(iSlow3));
	double 	fSlow5 = (fConst11 * fSlow2);
	int 	iSlow6 = int(double(fcheckbox0));
	double 	fSlow7 = (fConst12 * double(fslider3));
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		fRec0[0] = ((0.993 * fRec0[1]) + fSlow0);
		double fTemp0 = (0.000257077328090757 * fRec0[0]);
		fRec2[0] = ((double)input0[i] - (fConst7 * fRec2[1]));
		fRec3[0] = ((0.993 * fRec3[1]) + fSlow1);
		double fTemp1 = ((fRec2[0] * (0 - (0.000275923691873229 * fRec3[0]))) + (0.000275923691873229 * (fRec3[0] * fRec2[1])));
		fVec1[IOTA&65535] = fTemp1;
		iRec9[0] = ((int((iRec9[1] > 0)))?((2 * (iRec8[1] < iSlow3)) - 1):(1 - (2 * (iRec8[1] > 0))));
		iRec8[0] = (iRec9[0] + iRec8[1]);
		fRec12[0] = (fRec12[1] + (fSlow5 * (0 - fRec10[1])));
		fRec11[0] = ((1 + (fRec11[1] + (fSlow5 * fRec12[0]))) - iVec0[1]);
		fRec10[0] = fRec11[0];
		double fTemp2 = (fSlow7 * (1 + (1 + ((iSlow6)?max((double)0, (0.5 * (1 + fRec10[0]))):(fSlow4 * iRec8[0])))));
		double fTemp3 = ((int((fRec4[1] != 0.0)))?((int(((fRec5[1] > 0.0) & (fRec5[1] < 1.0))))?fRec4[1]:0):((int(((fRec5[1] == 0.0) & (fTemp2 != fRec6[1]))))?fConst8:((int(((fRec5[1] == 1.0) & (fTemp2 != fRec7[1]))))?fConst9:0)));
		fRec4[0] = fTemp3;
		fRec5[0] = max(0.0, min(1.0, (fRec5[1] + fTemp3)));
		fRec6[0] = ((int(((fRec5[1] >= 1.0) & (fRec7[1] != fTemp2))))?fTemp2:fRec6[1]);
		fRec7[0] = ((int(((fRec5[1] <= 0.0) & (fRec6[1] != fTemp2))))?fTemp2:fRec7[1]);
		fRec1[0] = ((fConst13 * (((1.0 - fRec5[0]) * fVec1[(IOTA-int((int(fRec6[0]) & 65535)))&65535]) + (fRec5[0] * fVec1[(IOTA-int((int(fRec7[0]) & 65535)))&65535]))) - (fConst4 * fRec1[1]));
		output0[i] = (FAUSTFLOAT)(fConst14 * ((fRec1[0] * (fTemp0 - 0.000257077328090757)) + (fRec1[1] * (0.000257077328090757 + (0 - fTemp0)))));
		// post processing
		fRec1[1] = fRec1[0];
		fRec7[1] = fRec7[0];
		fRec6[1] = fRec6[0];
		fRec5[1] = fRec5[0];
		fRec4[1] = fRec4[0];
		fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		fRec12[1] = fRec12[0];
		iRec8[1] = iRec8[0];
		iRec9[1] = iRec9[0];
		IOTA = IOTA+1;
		fRec3[1] = fRec3[0];
		fRec2[1] = fRec2[0];
		fRec0[1] = fRec0[0];
		iVec0[1] = iVec0[0];
	}
#undef fslider0
#undef fslider1
#undef fslider2
#undef fcheckbox0
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
	case GAIN: 
		fslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	// static const value_pair fcheckbox0_values[] = {{"triangle"},{"sine"},{0}};
	case SINEWAVE: 
		fcheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case DEPTH: 
		fslider3_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case SPEED: 
		fslider2_ = (float*)data; // , 5.0, 0.0, 14.0, 0.1 
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
   GAIN, 
   SINEWAVE, 
   DEPTH, 
   SPEED, 
} PortIndex;
*/

} // end namespace gxtubevibrato
