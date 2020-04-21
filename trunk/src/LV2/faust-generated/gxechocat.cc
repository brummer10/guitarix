// generated from file '../src/LV2/faust/gxechocat.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace gxechocat {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fConst4;
	double fConst5;
	double fConst6;
	double fConst7;
	double fConst8;
	double fConst9;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT	*fCheckbox0_;
	double fConst10;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fConst11;
	double fConst12;
	double fRec4[2];
	double fRec5[2];
	double fRec6[2];
	double fRec7[2];
	double fConst13;
	double fConst14;
	double fConst15;
	double fConst16;
	double fConst17;
	double fConst18;
	double fConst19;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fConst20;
	double fConst21;
	double fConst22;
	double fRec11[2];
	double fVec0[2];
	double fConst23;
	double fConst24;
	double fConst25;
	double fRec10[2];
	double fConst26;
	double fConst27;
	double fConst28;
	double fConst29;
	double fRec12[2];
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fRec13[2];
	double fConst30;
	double fConst31;
	double fRec9[3];
	double fConst32;
	double fConst33;
	double fRec8[3];
	int IOTA;
	double *fVec1;
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT	*fCheckbox1_;
	double fConst34;
	double fRec14[2];
	double fRec15[2];
	double fRec16[2];
	double fRec17[2];
	FAUSTFLOAT fCheckbox2;
	FAUSTFLOAT	*fCheckbox2_;
	double fConst35;
	double fRec18[2];
	double fRec19[2];
	double fRec20[2];
	double fRec21[2];
	double fVec2[2];
	double fRec3[2];
	double fRec2[2];
	double fRec1[3];
	double fConst36;
	double fRec0[2];
	FAUSTFLOAT fVslider4;
	FAUSTFLOAT	*fVslider4_;
	double fRec22[2];

	bool mem_allocated;
	void mem_alloc();
	void mem_free();
	void connect(uint32_t port,void* data);
	void clear_state_f();
	int activate(bool start);
	void init(uint32_t sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);

	static void clear_state_f_static(PluginLV2*);
	static int activate_static(bool start, PluginLV2*);
	static void init_static(uint32_t sample_rate, PluginLV2*);
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec4[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec5[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec6[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fRec7[l3] = 0.0;
	for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) fRec11[l4] = 0.0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fVec0[l5] = 0.0;
	for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) fRec10[l6] = 0.0;
	for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) fRec12[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fRec13[l8] = 0.0;
	for (int l9 = 0; (l9 < 3); l9 = (l9 + 1)) fRec9[l9] = 0.0;
	for (int l10 = 0; (l10 < 3); l10 = (l10 + 1)) fRec8[l10] = 0.0;
	for (int l11 = 0; (l11 < 1048576); l11 = (l11 + 1)) fVec1[l11] = 0.0;
	for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) fRec14[l12] = 0.0;
	for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) fRec15[l13] = 0.0;
	for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) fRec16[l14] = 0.0;
	for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) fRec17[l15] = 0.0;
	for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) fRec18[l16] = 0.0;
	for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) fRec19[l17] = 0.0;
	for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) fRec20[l18] = 0.0;
	for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) fRec21[l19] = 0.0;
	for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) fVec2[l20] = 0.0;
	for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) fRec3[l21] = 0.0;
	for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) fRec2[l22] = 0.0;
	for (int l23 = 0; (l23 < 3); l23 = (l23 + 1)) fRec1[l23] = 0.0;
	for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) fRec0[l24] = 0.0;
	for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) fRec22[l25] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = (2.08237464507809e-05 * fConst0);
	fConst2 = (fConst1 + 0.00046017036251682698);
	fConst3 = (0.10000000000000001 * (fConst0 / fConst2));
	fConst4 = (1.0 / std::tan((20420.352248333656 / fConst0)));
	fConst5 = (1.0 / (fConst4 + 1.0));
	fConst6 = (1.0 - fConst4);
	fConst7 = std::tan((125.66370614359172 / fConst0));
	fConst8 = (1.0 / fConst7);
	fConst9 = (1.0 / (((fConst8 + 0.76536686473017945) / fConst7) + 1.0));
	fConst10 = (60.0 * fConst0);
	fConst11 = (10.0 / fConst0);
	fConst12 = (0.0 - fConst11);
	fConst13 = mydsp_faustpower2_f(fConst7);
	fConst14 = (1.0 / fConst13);
	fConst15 = (1.0 / (((fConst8 + 1.8477590650225735) / fConst7) + 1.0));
	fConst16 = std::tan((392.69908169872411 / fConst0));
	fConst17 = (1.0 / fConst16);
	fConst18 = (fConst17 + 1.0);
	fConst19 = (0.0 - (1.0 / (fConst16 * fConst18)));
	fConst20 = (1.0 / std::tan((23561.944901923449 / fConst0)));
	fConst21 = (1.0 / (fConst20 + 1.0));
	fConst22 = (1.0 - fConst20);
	fConst23 = (1.0 / fConst18);
	fConst24 = (0.5 / fConst16);
	fConst25 = (1.0 - fConst17);
	fConst26 = (2.08237299868718e-05 * fConst0);
	fConst27 = (fConst26 + 0.000460960630154374);
	fConst28 = (fConst0 / fConst27);
	fConst29 = ((0.000460960630154374 - fConst26) / fConst27);
	fConst30 = (((fConst8 + -1.8477590650225735) / fConst7) + 1.0);
	fConst31 = (2.0 * (1.0 - fConst14));
	fConst32 = (0.0 - (2.0 / fConst13));
	fConst33 = (((fConst8 + -0.76536686473017945) / fConst7) + 1.0);
	fConst34 = (120.0 * fConst0);
	fConst35 = (180.0 * fConst0);
	fConst36 = ((0.00046017036251682698 - fConst1) / fConst2);
	IOTA = 0;
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void Dsp::mem_alloc()
{
	if (!fVec1) fVec1 = new double[1048576];
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
#define fVslider0 (*fVslider0_)
#define fCheckbox0 (*fCheckbox0_)
#define fVslider1 (*fVslider1_)
#define fVslider2 (*fVslider2_)
#define fVslider3 (*fVslider3_)
#define fCheckbox1 (*fCheckbox1_)
#define fCheckbox2 (*fCheckbox2_)
#define fVslider4 (*fVslider4_)
	double fSlow0 = double(fVslider0);
	double fSlow1 = double(fCheckbox0);
	double fSlow2 = double(fVslider1);
	double fSlow3 = (fConst10 / fSlow2);
	double fSlow4 = double(fVslider2);
	double fSlow5 = (0.5 * fSlow4);
	double fSlow6 = (fConst24 * fSlow4);
	double fSlow7 = (0.004073836948085289 * (std::exp(double(fVslider3)) + -1.0));
	double fSlow8 = double(fCheckbox1);
	double fSlow9 = (fConst34 / fSlow2);
	double fSlow10 = double(fCheckbox2);
	double fSlow11 = (fConst35 / fSlow2);
	double fSlow12 = (0.004073836948085289 * (std::exp((1.0 - double(fVslider4))) + -1.0));
	for (int i = 0; (i < count); i = (i + 1)) {
		double fTemp0 = ((fRec4[1] != 0.0) ? (((fRec5[1] > 0.0) & (fRec5[1] < 1.0)) ? fRec4[1] : 0.0) : (((fRec5[1] == 0.0) & (fSlow3 != fRec6[1])) ? fConst11 : (((fRec5[1] == 1.0) & (fSlow3 != fRec7[1])) ? fConst12 : 0.0)));
		fRec4[0] = fTemp0;
		fRec5[0] = std::max<double>(0.0, std::min<double>(1.0, (fRec5[1] + fTemp0)));
		fRec6[0] = (((fRec5[1] >= 1.0) & (fRec7[1] != fSlow3)) ? fSlow3 : fRec6[1]);
		fRec7[0] = (((fRec5[1] <= 0.0) & (fRec6[1] != fSlow3)) ? fSlow3 : fRec7[1]);
		fRec11[0] = (0.0 - (fConst21 * ((fConst22 * fRec11[1]) - (fRec1[1] + fRec1[2]))));
		fVec0[0] = (fSlow5 * fRec11[0]);
		fRec10[0] = ((fConst19 * fVec0[1]) + (fConst23 * ((fSlow6 * fRec11[0]) - (fConst25 * fRec10[1]))));
		fRec12[0] = (double(input0[i]) - (fConst29 * fRec12[1]));
		fRec13[0] = (fSlow7 + (0.99299999999999999 * fRec13[1]));
		double fTemp1 = (fConst28 * ((fRec12[0] * (0.0 - (0.00027592369187322898 * fRec13[0]))) + (0.00027592369187322898 * (fRec13[0] * fRec12[1]))));
		fRec9[0] = ((fRec10[0] + fTemp1) - (fConst15 * ((fConst30 * fRec9[2]) + (fConst31 * fRec9[1]))));
		fRec8[0] = ((fConst15 * (((fConst14 * fRec9[0]) + (fConst32 * fRec9[1])) + (fConst14 * fRec9[2]))) - (fConst9 * ((fConst33 * fRec8[2]) + (fConst31 * fRec8[1]))));
		double fTemp2 = (((fConst14 * fRec8[0]) + (fConst32 * fRec8[1])) + (fConst14 * fRec8[2]));
		fVec1[(IOTA & 1048575)] = fTemp2;
		double fTemp3 = ((fRec14[1] != 0.0) ? (((fRec15[1] > 0.0) & (fRec15[1] < 1.0)) ? fRec14[1] : 0.0) : (((fRec15[1] == 0.0) & (fSlow9 != fRec16[1])) ? fConst11 : (((fRec15[1] == 1.0) & (fSlow9 != fRec17[1])) ? fConst12 : 0.0)));
		fRec14[0] = fTemp3;
		fRec15[0] = std::max<double>(0.0, std::min<double>(1.0, (fRec15[1] + fTemp3)));
		fRec16[0] = (((fRec15[1] >= 1.0) & (fRec17[1] != fSlow9)) ? fSlow9 : fRec16[1]);
		fRec17[0] = (((fRec15[1] <= 0.0) & (fRec16[1] != fSlow9)) ? fSlow9 : fRec17[1]);
		double fTemp4 = ((fRec18[1] != 0.0) ? (((fRec19[1] > 0.0) & (fRec19[1] < 1.0)) ? fRec18[1] : 0.0) : (((fRec19[1] == 0.0) & (fSlow11 != fRec20[1])) ? fConst11 : (((fRec19[1] == 1.0) & (fSlow11 != fRec21[1])) ? fConst12 : 0.0)));
		fRec18[0] = fTemp4;
		fRec19[0] = std::max<double>(0.0, std::min<double>(1.0, (fRec19[1] + fTemp4)));
		fRec20[0] = (((fRec19[1] >= 1.0) & (fRec21[1] != fSlow11)) ? fSlow11 : fRec20[1]);
		fRec21[0] = (((fRec19[1] <= 0.0) & (fRec20[1] != fSlow11)) ? fSlow11 : fRec21[1]);
		double fTemp5 = (((fSlow1 * (((1.0 - fRec5[0]) * fVec1[((IOTA - int(std::min<double>(524288.0, std::max<double>(0.0, fRec6[0])))) & 1048575)]) + (fRec5[0] * fVec1[((IOTA - int(std::min<double>(524288.0, std::max<double>(0.0, fRec7[0])))) & 1048575)]))) + (fSlow8 * (((1.0 - fRec15[0]) * fVec1[((IOTA - int(std::min<double>(524288.0, std::max<double>(0.0, fRec16[0])))) & 1048575)]) + (fRec15[0] * fVec1[((IOTA - int(std::min<double>(524288.0, std::max<double>(0.0, fRec17[0])))) & 1048575)])))) + (fSlow10 * (((1.0 - fRec19[0]) * fVec1[((IOTA - int(std::min<double>(524288.0, std::max<double>(0.0, fRec20[0])))) & 1048575)]) + (fRec19[0] * fVec1[((IOTA - int(std::min<double>(524288.0, std::max<double>(0.0, fRec21[0])))) & 1048575)]))));
		fVec2[0] = fTemp5;
		fRec3[0] = (0.0 - (fConst5 * ((fConst6 * fRec3[1]) - (fConst9 * (fTemp5 + fVec2[1])))));
		fRec2[0] = ((fRec3[0] + (0.995 * fRec2[1])) - fRec3[1]);
		fRec1[0] = (fSlow0 * fRec2[0]);
		fRec0[0] = ((fRec1[0] + fTemp1) - (fConst36 * fRec0[1]));
		fRec22[0] = (fSlow12 + (0.99299999999999999 * fRec22[1]));
		output0[i] = FAUSTFLOAT((fConst3 * ((fRec0[1] * ((0.0 - (0.00025707732809075701 * fRec22[0])) + 0.00025707732809075701)) + (0.00025707732809075701 * (fRec0[0] * (fRec22[0] + -1.0))))));
		fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		fRec7[1] = fRec7[0];
		fRec11[1] = fRec11[0];
		fVec0[1] = fVec0[0];
		fRec10[1] = fRec10[0];
		fRec12[1] = fRec12[0];
		fRec13[1] = fRec13[0];
		fRec9[2] = fRec9[1];
		fRec9[1] = fRec9[0];
		fRec8[2] = fRec8[1];
		fRec8[1] = fRec8[0];
		IOTA = (IOTA + 1);
		fRec14[1] = fRec14[0];
		fRec15[1] = fRec15[0];
		fRec16[1] = fRec16[0];
		fRec17[1] = fRec17[0];
		fRec18[1] = fRec18[0];
		fRec19[1] = fRec19[0];
		fRec20[1] = fRec20[0];
		fRec21[1] = fRec21[0];
		fVec2[1] = fVec2[0];
		fRec3[1] = fRec3[0];
		fRec2[1] = fRec2[0];
		fRec1[2] = fRec1[1];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
		fRec22[1] = fRec22[0];
	}
#undef fVslider0
#undef fCheckbox0
#undef fVslider1
#undef fVslider2
#undef fVslider3
#undef fCheckbox1
#undef fCheckbox2
#undef fVslider4
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
		fVslider3_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case SUSTAIN: 
		fVslider2_ = (float*)data; // , 0.0, 0.0, 0.94999999999999996, 0.01 
		break;
	case GAIN: 
		fVslider4_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case BPM: 
		fVslider1_ = (float*)data; // , 120.0, 24.0, 360.0, 0.10000000000000001 
		break;
	case SWELL: 
		fVslider0_ = (float*)data; // , 0.0, 0.0, 1.0, 0.01 
		break;
	case HEAD1: 
		fCheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case HEAD2: 
		fCheckbox1_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case HEAD3: 
		fCheckbox2_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
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
