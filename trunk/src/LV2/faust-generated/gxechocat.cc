// generated from file '../src/LV2/faust/gxechocat.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)


namespace gxechocat {

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
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec2[2];
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fRec3[2];
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
	double 	fRec10[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fConst22;
	double 	fConst23;
	double 	fVec0[2];
	double 	fConst24;
	double 	fConst25;
	double 	fConst26;
	double 	fConst27;
	double 	fConst28;
	double 	fRec9[2];
	double 	fRec8[3];
	double 	fConst29;
	double 	fRec7[3];
	int 	IOTA;
	double *fVec1;
	double 	fConst30;
	double 	fConst31;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fConst32;
	double 	fRec11[2];
	double 	fRec12[2];
	double 	fRec13[2];
	double 	fRec14[2];
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT	*fcheckbox0_;
	double 	fConst33;
	double 	fRec15[2];
	double 	fRec16[2];
	double 	fRec17[2];
	double 	fRec18[2];
	FAUSTFLOAT 	fcheckbox1;
	FAUSTFLOAT	*fcheckbox1_;
	double 	fConst34;
	double 	fRec19[2];
	double 	fRec20[2];
	double 	fRec21[2];
	double 	fRec22[2];
	FAUSTFLOAT 	fcheckbox2;
	FAUSTFLOAT	*fcheckbox2_;
	double 	fVec2[2];
	double 	fConst35;
	double 	fConst36;
	double 	fConst37;
	double 	fConst38;
	double 	fRec6[2];
	double 	fRec5[2];
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT	*fslider4_;
	double 	fRec4[3];
	double 	fRec1[2];
	double 	fConst39;

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
	id = "gxechocat";
	name = N_("Tape Delay");
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
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<3; i++) fRec8[i] = 0;
	for (int i=0; i<3; i++) fRec7[i] = 0;
	for (int i=0; i<524288; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<3; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = min(1.92e+05, max(1.0, (double)fSamplingFreq));
	fConst1 = double(fConst0);
	fConst2 = (2.08237464507809e-05 * fConst1);
	fConst3 = (0.000460170362516827 + fConst2);
	fConst4 = ((0.000460170362516827 - fConst2) / fConst3);
	fConst5 = (2.08237299868718e-05 * fConst1);
	fConst6 = (0.000460960630154374 + fConst5);
	fConst7 = ((0.000460960630154374 - fConst5) / fConst6);
	fConst8 = (fConst1 / fConst6);
	fConst9 = tan((125.66370614359172 / fConst0));
	fConst10 = (1.0 / fConst9);
	fConst11 = (1 + ((fConst10 - 0.7653668647301795) / fConst9));
	fConst12 = (1.0 / faustpower<2>(fConst9));
	fConst13 = (2 * (1 - fConst12));
	fConst14 = (1 + ((0.7653668647301795 + fConst10) / fConst9));
	fConst15 = (1.0 / fConst14);
	fConst16 = (1 + ((fConst10 - 1.8477590650225735) / fConst9));
	fConst17 = (1.0 / (1 + ((fConst10 + 1.8477590650225735) / fConst9)));
	fConst18 = (1.0 / tan((23561.94490192345 / fConst0)));
	fConst19 = (1 + fConst18);
	fConst20 = (0 - ((1 - fConst18) / fConst19));
	fConst21 = (1.0 / fConst19);
	fConst22 = tan((392.6990816987241 / fConst0));
	fConst23 = (0.5 / fConst22);
	fConst24 = (1.0 / fConst22);
	fConst25 = (0 - fConst24);
	fConst26 = (1 + fConst24);
	fConst27 = (1.0 / fConst26);
	fConst28 = (0 - ((1 - fConst24) / fConst26));
	fConst29 = (2 * (0 - fConst12));
	fConst30 = (1e+01 / fConst0);
	fConst31 = (0 - fConst30);
	fConst32 = (180 * fConst0);
	fConst33 = (120 * fConst0);
	fConst34 = (60 * fConst0);
	fConst35 = (1.0 / tan((20420.352248333656 / fConst0)));
	fConst36 = (1 + fConst35);
	fConst37 = (1.0 / (fConst36 * fConst14));
	fConst38 = (0 - ((1 - fConst35) / fConst36));
	fConst39 = (0.1 * (fConst1 / fConst3));
	IOTA = 0;
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void Dsp::mem_alloc()
{
	if (!fVec1) fVec1 = new double[524288];
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
#define fslider3 (*fslider3_)
#define fcheckbox0 (*fcheckbox0_)
#define fcheckbox1 (*fcheckbox1_)
#define fcheckbox2 (*fcheckbox2_)
#define fslider4 (*fslider4_)
	double 	fSlow0 = (0.004073836948085289 * (exp((1 - double(fslider0))) - 1));
	double 	fSlow1 = (0.004073836948085289 * (exp(double(fslider1)) - 1));
	double 	fSlow2 = double(fslider2);
	double 	fSlow3 = (fConst23 * fSlow2);
	double 	fSlow4 = (0.5 * fSlow2);
	double 	fSlow5 = double(fslider3);
	double 	fSlow6 = (fConst32 / fSlow5);
	double 	fSlow7 = double(fcheckbox0);
	double 	fSlow8 = (fConst33 / fSlow5);
	double 	fSlow9 = double(fcheckbox1);
	double 	fSlow10 = (fConst34 / fSlow5);
	double 	fSlow11 = double(fcheckbox2);
	double 	fSlow12 = double(fslider4);
	for (int i=0; i<count; i++) {
		fRec0[0] = (fSlow0 + (0.993 * fRec0[1]));
		double fTemp0 = (0.000257077328090757 * fRec0[0]);
		fRec2[0] = (fSlow1 + (0.993 * fRec2[1]));
		fRec3[0] = ((double)input0[i] - (fConst7 * fRec3[1]));
		double fTemp1 = (fConst8 * ((fRec3[0] * (0 - (0.000275923691873229 * fRec2[0]))) + (0.000275923691873229 * (fRec3[1] * fRec2[0]))));
		fRec10[0] = ((fConst21 * (fRec4[1] + fRec4[2])) + (fConst20 * fRec10[1]));
		fVec0[0] = (fSlow4 * fRec10[0]);
		fRec9[0] = ((fConst28 * fRec9[1]) + (fConst27 * ((fConst25 * fVec0[1]) + (fSlow3 * fRec10[0]))));
		fRec8[0] = ((fRec9[0] + fTemp1) - (fConst17 * ((fConst16 * fRec8[2]) + (fConst13 * fRec8[1]))));
		fRec7[0] = ((fConst17 * ((fConst29 * fRec8[1]) + (fConst12 * (fRec8[2] + fRec8[0])))) - (fConst15 * ((fConst13 * fRec7[1]) + (fConst11 * fRec7[2]))));
		double fTemp2 = ((fConst29 * fRec7[1]) + (fConst12 * (fRec7[2] + fRec7[0])));
		fVec1[IOTA&524287] = fTemp2;
		double fTemp3 = ((int((fRec11[1] != 0.0)))?((int(((fRec12[1] > 0.0) & (fRec12[1] < 1.0))))?fRec11[1]:0):((int(((fRec12[1] == 0.0) & (fSlow6 != fRec13[1]))))?fConst30:((int(((fRec12[1] == 1.0) & (fSlow6 != fRec14[1]))))?fConst31:0)));
		fRec11[0] = fTemp3;
		fRec12[0] = max(0.0, min(1.0, (fRec12[1] + fTemp3)));
		fRec13[0] = ((int(((fRec12[1] >= 1.0) & (fRec14[1] != fSlow6))))?fSlow6:fRec13[1]);
		fRec14[0] = ((int(((fRec12[1] <= 0.0) & (fRec13[1] != fSlow6))))?fSlow6:fRec14[1]);
		double fTemp4 = ((int((fRec15[1] != 0.0)))?((int(((fRec16[1] > 0.0) & (fRec16[1] < 1.0))))?fRec15[1]:0):((int(((fRec16[1] == 0.0) & (fSlow8 != fRec17[1]))))?fConst30:((int(((fRec16[1] == 1.0) & (fSlow8 != fRec18[1]))))?fConst31:0)));
		fRec15[0] = fTemp4;
		fRec16[0] = max(0.0, min(1.0, (fRec16[1] + fTemp4)));
		fRec17[0] = ((int(((fRec16[1] >= 1.0) & (fRec18[1] != fSlow8))))?fSlow8:fRec17[1]);
		fRec18[0] = ((int(((fRec16[1] <= 0.0) & (fRec17[1] != fSlow8))))?fSlow8:fRec18[1]);
		double fTemp5 = ((int((fRec19[1] != 0.0)))?((int(((fRec20[1] > 0.0) & (fRec20[1] < 1.0))))?fRec19[1]:0):((int(((fRec20[1] == 0.0) & (fSlow10 != fRec21[1]))))?fConst30:((int(((fRec20[1] == 1.0) & (fSlow10 != fRec22[1]))))?fConst31:0)));
		fRec19[0] = fTemp5;
		fRec20[0] = max(0.0, min(1.0, (fRec20[1] + fTemp5)));
		fRec21[0] = ((int(((fRec20[1] >= 1.0) & (fRec22[1] != fSlow10))))?fSlow10:fRec21[1]);
		fRec22[0] = ((int(((fRec20[1] <= 0.0) & (fRec21[1] != fSlow10))))?fSlow10:fRec22[1]);
		double fTemp6 = (((fSlow11 * (((1.0 - fRec20[0]) * fVec1[(IOTA-int((int(fRec21[0]) & 524287)))&524287]) + (fRec20[0] * fVec1[(IOTA-int((int(fRec22[0]) & 524287)))&524287]))) + (fSlow9 * (((1.0 - fRec16[0]) * fVec1[(IOTA-int((int(fRec17[0]) & 524287)))&524287]) + (fRec16[0] * fVec1[(IOTA-int((int(fRec18[0]) & 524287)))&524287])))) + (fSlow7 * (((1.0 - fRec12[0]) * fVec1[(IOTA-int((int(fRec13[0]) & 524287)))&524287]) + (fRec12[0] * fVec1[(IOTA-int((int(fRec14[0]) & 524287)))&524287]))));
		fVec2[0] = fTemp6;
		fRec6[0] = ((fConst38 * fRec6[1]) + (fConst37 * (fVec2[0] + fVec2[1])));
		fRec5[0] = (((0.995 * fRec5[1]) + fRec6[0]) - fRec6[1]);
		fRec4[0] = (fSlow12 * fRec5[0]);
		fRec1[0] = ((fRec4[0] + fTemp1) - (fConst4 * fRec1[1]));
		output0[i] = (FAUSTFLOAT)(fConst39 * ((fRec1[0] * (fTemp0 - 0.000257077328090757)) + (fRec1[1] * (0.000257077328090757 - fTemp0))));
		// post processing
		fRec1[1] = fRec1[0];
		fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		fVec2[1] = fVec2[0];
		fRec22[1] = fRec22[0];
		fRec21[1] = fRec21[0];
		fRec20[1] = fRec20[0];
		fRec19[1] = fRec19[0];
		fRec18[1] = fRec18[0];
		fRec17[1] = fRec17[0];
		fRec16[1] = fRec16[0];
		fRec15[1] = fRec15[0];
		fRec14[1] = fRec14[0];
		fRec13[1] = fRec13[0];
		fRec12[1] = fRec12[0];
		fRec11[1] = fRec11[0];
		IOTA = IOTA+1;
		fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
		fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
		fRec9[1] = fRec9[0];
		fVec0[1] = fVec0[0];
		fRec10[1] = fRec10[0];
		fRec3[1] = fRec3[0];
		fRec2[1] = fRec2[0];
		fRec0[1] = fRec0[0];
	}
#undef fslider0
#undef fslider1
#undef fslider2
#undef fslider3
#undef fcheckbox0
#undef fcheckbox1
#undef fcheckbox2
#undef fslider4
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
	case SUSTAIN: 
		fslider2_ = (float*)data; // , 0.0, 0.0, 0.95, 0.01 
		break;
	case GAIN: 
		fslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case BPM: 
		fslider3_ = (float*)data; // , 1.2e+02, 24.0, 3.6e+02, 0.1 
		break;
	case SWELL: 
		fslider4_ = (float*)data; // , 0.0, 0.0, 1.0, 0.01 
		break;
	case HEAD1: 
		fcheckbox2_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case HEAD2: 
		fcheckbox1_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case HEAD3: 
		fcheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
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
   SUSTAIN, 
   GAIN, 
   BPM, 
   SWELL, 
   HEAD1, 
   HEAD2, 
   HEAD3, 
} PortIndex;
*/

} // end namespace gxechocat
