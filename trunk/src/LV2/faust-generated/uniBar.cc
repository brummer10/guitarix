// generated from file '../src/LV2/faust/uniBar.dsp' by dsp2cc:
// Code generated with Faust 0.9.46 (http://faust.grame.fr)


namespace uniBar {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT	*fcheckbox0_;
	int 	iRec6_perm[4];
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fRec7_perm[4];
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fYec0[8192];
	int 	fYec0_idx;
	int 	fYec0_idx_save;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fRec5_perm[4];
	double 	fConst8;
	double 	fConst9;
	double 	fConst10;
	double 	fRec4_perm[4];
	double 	fRec0_perm[4];
	double 	fYec1[8192];
	int 	fYec1_idx;
	int 	fYec1_idx_save;
	double 	fConst11;
	double 	fConst12;
	double 	fRec9_perm[4];
	double 	fRec8_perm[4];
	double 	fRec1_perm[4];
	double 	fYec2[4096];
	int 	fYec2_idx;
	int 	fYec2_idx_save;
	double 	fConst13;
	double 	fConst14;
	double 	fRec11_perm[4];
	double 	fRec10_perm[4];
	double 	fRec2_perm[4];
	double 	fYec3[4096];
	int 	fYec3_idx;
	int 	fYec3_idx_save;
	double 	fConst15;
	double 	fConst16;
	double 	fRec13_perm[4];
	double 	fRec12_perm[4];
	double 	fRec3_perm[4];
	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(uint32_t samplingFreq);
	void compute(int fullcount, float *inputX0, float *outputX0);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(uint32_t samplingFreq, PluginLV2*);
	static void compute_static(int fullcount, float *inputX0, float *outputX0, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginLV2() {
	version = PLUGINLV2_VERSION;
	id = "Basic Parameters";
	name = N_("Nonlinear Banded Waveguide Models");
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
	for (int i=0; i<4; i++) iRec6_perm[i]=0;
	for (int i=0; i<4; i++) fRec7_perm[i]=0;
	for (int i=0; i<8192; i++) fYec0[i]=0;
	for (int i=0; i<4; i++) fRec5_perm[i]=0;
	for (int i=0; i<4; i++) fRec4_perm[i]=0;
	for (int i=0; i<4; i++) fRec0_perm[i]=0;
	for (int i=0; i<8192; i++) fYec1[i]=0;
	for (int i=0; i<4; i++) fRec9_perm[i]=0;
	for (int i=0; i<4; i++) fRec8_perm[i]=0;
	for (int i=0; i<4; i++) fRec1_perm[i]=0;
	for (int i=0; i<4096; i++) fYec2[i]=0;
	for (int i=0; i<4; i++) fRec11_perm[i]=0;
	for (int i=0; i<4; i++) fRec10_perm[i]=0;
	for (int i=0; i<4; i++) fRec2_perm[i]=0;
	for (int i=0; i<4096; i++) fYec3[i]=0;
	for (int i=0; i<4; i++) fRec13_perm[i]=0;
	for (int i=0; i<4; i++) fRec12_perm[i]=0;
	for (int i=0; i<4; i++) fRec3_perm[i]=0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (1 - (1.0 / pow(9e+04,(1e+02 / iConst0))));
	fConst2 = (1 - pow(9e+01,(2e+02 / iConst0)));
	fConst3 = (5e+01 / iConst0);
	fYec0_idx = 0;
	fYec0_idx_save = 0;
	fConst4 = (6.283185307179586 / iConst0);
	fConst5 = (1 - (100.53096491487338 / iConst0));
	fConst6 = (0 - (2 * fConst5));
	fConst7 = faustpower<2>(fConst5);
	fConst8 = (0.5 * fConst7);
	fConst9 = (0.5 - fConst8);
	fConst10 = (fConst8 - 0.5);
	fYec1_idx = 0;
	fYec1_idx_save = 0;
	fConst11 = (0.362844702467344 * iConst0);
	fConst12 = (17.31645870658694 / iConst0);
	fYec2_idx = 0;
	fYec2_idx_save = 0;
	fConst13 = (0.1850481125092524 * iConst0);
	fConst14 = (33.95433339999848 / iConst0);
	fYec3_idx = 0;
	fYec3_idx_save = 0;
	fConst15 = (0.1119444755401321 * iConst0);
	fConst16 = (56.127694349035245 / iConst0);
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int fullcount, float *inputX0, float *outputX0)
{
#define fcheckbox0 (*fcheckbox0_)
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
	int 	iRec6_tmp[128+4];
	int 	iZec0[128];
	double 	fRec7_tmp[128+4];
	double 	fZec1[128];
	double 	fZec2[128];
	double 	fZec3[128];
	double 	fZec4[128];
	double 	fRec5_tmp[128+4];
	double 	fRec4_tmp[128+4];
	double 	fRec0_tmp[128+4];
	double 	fRec9_tmp[128+4];
	double 	fRec8_tmp[128+4];
	double 	fRec1_tmp[128+4];
	double 	fRec11_tmp[128+4];
	double 	fRec10_tmp[128+4];
	double 	fRec2_tmp[128+4];
	double 	fRec13_tmp[128+4];
	double 	fRec12_tmp[128+4];
	double 	fRec3_tmp[128+4];
	double 	fSlow0 = fcheckbox0;
	int 	iSlow1 = (fSlow0 > 0);
	int* 	iRec6 = &iRec6_tmp[4];
	int 	iSlow2 = (fSlow0 <= 0);
	double* 	fRec7 = &fRec7_tmp[4];
	double 	fSlow3 = fslider0;
	double 	fSlow4 = (0.03 + fSlow3);
	double 	fSlow5 = (2.5 * (fSlow0 * fSlow3));
	double 	fSlow6 = fslider1;
	int 	iSlow7 = int((int((iConst0 / fSlow6)) & 4095));
	double 	fSlow8 = (fConst6 * cos((fConst4 * fSlow6)));
	double* 	fRec5 = &fRec5_tmp[4];
	double* 	fRec4 = &fRec4_tmp[4];
	double* 	fRec0 = &fRec0_tmp[4];
	int 	iSlow9 = int((int((fConst11 / fSlow6)) & 4095));
	double 	fSlow10 = (fConst6 * cos((fConst12 * fSlow6)));
	double* 	fRec9 = &fRec9_tmp[4];
	double* 	fRec8 = &fRec8_tmp[4];
	double* 	fRec1 = &fRec1_tmp[4];
	int 	iSlow11 = int((int((fConst13 / fSlow6)) & 4095));
	double 	fSlow12 = (fConst6 * cos((fConst14 * fSlow6)));
	double* 	fRec11 = &fRec11_tmp[4];
	double* 	fRec10 = &fRec10_tmp[4];
	double* 	fRec2 = &fRec2_tmp[4];
	int 	iSlow13 = int((int((fConst15 / fSlow6)) & 4095));
	double 	fSlow14 = (fConst6 * cos((fConst16 * fSlow6)));
	double* 	fRec13 = &fRec13_tmp[4];
	double* 	fRec12 = &fRec12_tmp[4];
	double* 	fRec3 = &fRec3_tmp[4];
	int index;
	for (index = 0; index <= fullcount - 128; index += 128) {
		// compute by blocks of 128 samples
		const int count = 128;
		FAUSTFLOAT* input0 = &inputX0[index];
		FAUSTFLOAT* output0 = &outputX0[index];
		// SECTION : 1
		// LOOP 0xa516178
		// pre processing
		for (int i=0; i<4; i++) iRec6_tmp[i]=iRec6_perm[i];
		for (int i=0; i<4; i++) fRec7_tmp[i]=fRec7_perm[i];
		// exec code
		for (int i=0; i<count; i++) {
			iRec6[i] = (iSlow1 & (iRec6[i-1] | (fRec7[i-1] >= 1)));
			iZec0[i] = (iSlow2 & (fRec7[i-1] > 0));
			fRec7[i] = (((iZec0[i] == 0) | (fRec7[i-1] >= 1e-06)) * ((fConst3 * (((iRec6[i-1] == 0) & iSlow1) & (fRec7[i-1] < 1))) + (fRec7[i-1] * ((1 - (fConst2 * (iRec6[i-1] & (fRec7[i-1] > 90)))) - (fConst1 * iZec0[i])))));
		}
		// post processing
		for (int i=0; i<4; i++) fRec7_perm[i]=fRec7_tmp[count+i];
		for (int i=0; i<4; i++) iRec6_perm[i]=iRec6_tmp[count+i];
		
		// SECTION : 2
		// LOOP 0xa515950
		// pre processing
		fYec0_idx = (fYec0_idx+fYec0_idx_save)&8191;
		for (int i=0; i<4; i++) fRec5_tmp[i]=fRec5_perm[i];
		for (int i=0; i<4; i++) fRec4_tmp[i]=fRec4_perm[i];
		for (int i=0; i<4; i++) fRec0_tmp[i]=fRec0_perm[i];
		fYec1_idx = (fYec1_idx+fYec1_idx_save)&8191;
		for (int i=0; i<4; i++) fRec9_tmp[i]=fRec9_perm[i];
		for (int i=0; i<4; i++) fRec8_tmp[i]=fRec8_perm[i];
		for (int i=0; i<4; i++) fRec1_tmp[i]=fRec1_perm[i];
		fYec2_idx = (fYec2_idx+fYec2_idx_save)&4095;
		for (int i=0; i<4; i++) fRec11_tmp[i]=fRec11_perm[i];
		for (int i=0; i<4; i++) fRec10_tmp[i]=fRec10_perm[i];
		for (int i=0; i<4; i++) fRec2_tmp[i]=fRec2_perm[i];
		fYec3_idx = (fYec3_idx+fYec3_idx_save)&4095;
		for (int i=0; i<4; i++) fRec13_tmp[i]=fRec13_perm[i];
		for (int i=0; i<4; i++) fRec12_tmp[i]=fRec12_perm[i];
		for (int i=0; i<4; i++) fRec3_tmp[i]=fRec3_perm[i];
		// exec code
		for (int i=0; i<count; i++) {
			fZec1[i] = ((fSlow4 * fRec7[i]) - (0.9999999999999999 * ((fRec3[i-1] + fRec1[i-1]) + (0.8000000000000002 + (fRec2[i-1] + fRec0[i-1])))));
			fZec2[i] = faustpower<4>((0.75 + fabs(fZec1[i])));
			fZec3[i] = (1.0 / fZec2[i]);
			fZec4[i] = (0.25 * (fZec1[i] * (((fZec3[i] <= 1) / fZec2[i]) + (fZec3[i] > 1))));
			fYec0[(fYec0_idx+i)&8191] = (fSlow5 + (fZec4[i] + fRec4[i-1]));
			fRec5[i] = (0 - (((fConst7 * fRec5[i-2]) + (fSlow8 * fRec5[i-1])) - (0.9 * fYec0[(fYec0_idx+i-iSlow7)&8191])));
			fRec4[i] = ((fConst10 * fRec5[i-2]) + (fConst9 * fRec5[i]));
			fRec0[i] = fRec4[i];
			fYec1[(fYec1_idx+i)&8191] = (fSlow5 + (fZec4[i] + fRec8[i-1]));
			fRec9[i] = (0 - (((fConst7 * fRec9[i-2]) + (fSlow10 * fRec9[i-1])) - (0.81 * fYec1[(fYec1_idx+i-iSlow9)&8191])));
			fRec8[i] = ((fConst10 * fRec9[i-2]) + (fConst9 * fRec9[i]));
			fRec1[i] = fRec8[i];
			fYec2[(fYec2_idx+i)&4095] = (fSlow5 + (fZec4[i] + fRec10[i-1]));
			fRec11[i] = (0 - (((fConst7 * fRec11[i-2]) + (fSlow12 * fRec11[i-1])) - (0.7290000000000001 * fYec2[(fYec2_idx+i-iSlow11)&4095])));
			fRec10[i] = ((fConst10 * fRec11[i-2]) + (fConst9 * fRec11[i]));
			fRec2[i] = fRec10[i];
			fYec3[(fYec3_idx+i)&4095] = (fSlow5 + (fZec4[i] + fRec12[i-1]));
			fRec13[i] = (0 - (((fConst7 * fRec13[i-2]) + (fSlow14 * fRec13[i-1])) - (0.6561 * fYec3[(fYec3_idx+i-iSlow13)&4095])));
			fRec12[i] = ((fConst10 * fRec13[i-2]) + (fConst9 * fRec13[i]));
			fRec3[i] = fRec12[i];
		}
		// post processing
		for (int i=0; i<4; i++) fRec3_perm[i]=fRec3_tmp[count+i];
		for (int i=0; i<4; i++) fRec12_perm[i]=fRec12_tmp[count+i];
		for (int i=0; i<4; i++) fRec13_perm[i]=fRec13_tmp[count+i];
		fYec3_idx_save = count;
		for (int i=0; i<4; i++) fRec2_perm[i]=fRec2_tmp[count+i];
		for (int i=0; i<4; i++) fRec10_perm[i]=fRec10_tmp[count+i];
		for (int i=0; i<4; i++) fRec11_perm[i]=fRec11_tmp[count+i];
		fYec2_idx_save = count;
		for (int i=0; i<4; i++) fRec1_perm[i]=fRec1_tmp[count+i];
		for (int i=0; i<4; i++) fRec8_perm[i]=fRec8_tmp[count+i];
		for (int i=0; i<4; i++) fRec9_perm[i]=fRec9_tmp[count+i];
		fYec1_idx_save = count;
		for (int i=0; i<4; i++) fRec0_perm[i]=fRec0_tmp[count+i];
		for (int i=0; i<4; i++) fRec4_perm[i]=fRec4_tmp[count+i];
		for (int i=0; i<4; i++) fRec5_perm[i]=fRec5_tmp[count+i];
		fYec0_idx_save = count;
		
		// SECTION : 3
		// LOOP 0xa515858
		// exec code
		for (int i=0; i<count; i++) {
			output0[i] = (FAUSTFLOAT)(fRec3[i] + (fRec2[i] + (fRec1[i] + ((double)input0[i] + fRec0[i]))));
		}
		
	}
	if (index < fullcount) {
		// compute the remaining samples if any
		int count = fullcount-index;
		FAUSTFLOAT* input0 = &inputX0[index];
		FAUSTFLOAT* output0 = &outputX0[index];
		// SECTION : 1
		// LOOP 0xa516178
		// pre processing
		for (int i=0; i<4; i++) iRec6_tmp[i]=iRec6_perm[i];
		for (int i=0; i<4; i++) fRec7_tmp[i]=fRec7_perm[i];
		// exec code
		for (int i=0; i<count; i++) {
			iRec6[i] = (iSlow1 & (iRec6[i-1] | (fRec7[i-1] >= 1)));
			iZec0[i] = (iSlow2 & (fRec7[i-1] > 0));
			fRec7[i] = (((iZec0[i] == 0) | (fRec7[i-1] >= 1e-06)) * ((fConst3 * (((iRec6[i-1] == 0) & iSlow1) & (fRec7[i-1] < 1))) + (fRec7[i-1] * ((1 - (fConst2 * (iRec6[i-1] & (fRec7[i-1] > 90)))) - (fConst1 * iZec0[i])))));
		}
		// post processing
		for (int i=0; i<4; i++) fRec7_perm[i]=fRec7_tmp[count+i];
		for (int i=0; i<4; i++) iRec6_perm[i]=iRec6_tmp[count+i];
		
		// SECTION : 2
		// LOOP 0xa515950
		// pre processing
		fYec0_idx = (fYec0_idx+fYec0_idx_save)&8191;
		for (int i=0; i<4; i++) fRec5_tmp[i]=fRec5_perm[i];
		for (int i=0; i<4; i++) fRec4_tmp[i]=fRec4_perm[i];
		for (int i=0; i<4; i++) fRec0_tmp[i]=fRec0_perm[i];
		fYec1_idx = (fYec1_idx+fYec1_idx_save)&8191;
		for (int i=0; i<4; i++) fRec9_tmp[i]=fRec9_perm[i];
		for (int i=0; i<4; i++) fRec8_tmp[i]=fRec8_perm[i];
		for (int i=0; i<4; i++) fRec1_tmp[i]=fRec1_perm[i];
		fYec2_idx = (fYec2_idx+fYec2_idx_save)&4095;
		for (int i=0; i<4; i++) fRec11_tmp[i]=fRec11_perm[i];
		for (int i=0; i<4; i++) fRec10_tmp[i]=fRec10_perm[i];
		for (int i=0; i<4; i++) fRec2_tmp[i]=fRec2_perm[i];
		fYec3_idx = (fYec3_idx+fYec3_idx_save)&4095;
		for (int i=0; i<4; i++) fRec13_tmp[i]=fRec13_perm[i];
		for (int i=0; i<4; i++) fRec12_tmp[i]=fRec12_perm[i];
		for (int i=0; i<4; i++) fRec3_tmp[i]=fRec3_perm[i];
		// exec code
		for (int i=0; i<count; i++) {
			fZec1[i] = ((fSlow4 * fRec7[i]) - (0.9999999999999999 * ((fRec3[i-1] + fRec1[i-1]) + (0.8000000000000002 + (fRec2[i-1] + fRec0[i-1])))));
			fZec2[i] = faustpower<4>((0.75 + fabs(fZec1[i])));
			fZec3[i] = (1.0 / fZec2[i]);
			fZec4[i] = (0.25 * (fZec1[i] * (((fZec3[i] <= 1) / fZec2[i]) + (fZec3[i] > 1))));
			fYec0[(fYec0_idx+i)&8191] = (fSlow5 + (fZec4[i] + fRec4[i-1]));
			fRec5[i] = (0 - (((fConst7 * fRec5[i-2]) + (fSlow8 * fRec5[i-1])) - (0.9 * fYec0[(fYec0_idx+i-iSlow7)&8191])));
			fRec4[i] = ((fConst10 * fRec5[i-2]) + (fConst9 * fRec5[i]));
			fRec0[i] = fRec4[i];
			fYec1[(fYec1_idx+i)&8191] = (fSlow5 + (fZec4[i] + fRec8[i-1]));
			fRec9[i] = (0 - (((fConst7 * fRec9[i-2]) + (fSlow10 * fRec9[i-1])) - (0.81 * fYec1[(fYec1_idx+i-iSlow9)&8191])));
			fRec8[i] = ((fConst10 * fRec9[i-2]) + (fConst9 * fRec9[i]));
			fRec1[i] = fRec8[i];
			fYec2[(fYec2_idx+i)&4095] = (fSlow5 + (fZec4[i] + fRec10[i-1]));
			fRec11[i] = (0 - (((fConst7 * fRec11[i-2]) + (fSlow12 * fRec11[i-1])) - (0.7290000000000001 * fYec2[(fYec2_idx+i-iSlow11)&4095])));
			fRec10[i] = ((fConst10 * fRec11[i-2]) + (fConst9 * fRec11[i]));
			fRec2[i] = fRec10[i];
			fYec3[(fYec3_idx+i)&4095] = (fSlow5 + (fZec4[i] + fRec12[i-1]));
			fRec13[i] = (0 - (((fConst7 * fRec13[i-2]) + (fSlow14 * fRec13[i-1])) - (0.6561 * fYec3[(fYec3_idx+i-iSlow13)&4095])));
			fRec12[i] = ((fConst10 * fRec13[i-2]) + (fConst9 * fRec13[i]));
			fRec3[i] = fRec12[i];
		}
		// post processing
		for (int i=0; i<4; i++) fRec3_perm[i]=fRec3_tmp[count+i];
		for (int i=0; i<4; i++) fRec12_perm[i]=fRec12_tmp[count+i];
		for (int i=0; i<4; i++) fRec13_perm[i]=fRec13_tmp[count+i];
		fYec3_idx_save = count;
		for (int i=0; i<4; i++) fRec2_perm[i]=fRec2_tmp[count+i];
		for (int i=0; i<4; i++) fRec10_perm[i]=fRec10_tmp[count+i];
		for (int i=0; i<4; i++) fRec11_perm[i]=fRec11_tmp[count+i];
		fYec2_idx_save = count;
		for (int i=0; i<4; i++) fRec1_perm[i]=fRec1_tmp[count+i];
		for (int i=0; i<4; i++) fRec8_perm[i]=fRec8_tmp[count+i];
		for (int i=0; i<4; i++) fRec9_perm[i]=fRec9_tmp[count+i];
		fYec1_idx_save = count;
		for (int i=0; i<4; i++) fRec0_perm[i]=fRec0_tmp[count+i];
		for (int i=0; i<4; i++) fRec4_perm[i]=fRec4_tmp[count+i];
		for (int i=0; i<4; i++) fRec5_perm[i]=fRec5_tmp[count+i];
		fYec0_idx_save = count;
		
		// SECTION : 3
		// LOOP 0xa515858
		// exec code
		for (int i=0; i<count; i++) {
			output0[i] = (FAUSTFLOAT)(fRec3[i] + (fRec2[i] + (fRec1[i] + ((double)input0[i] + fRec0[i]))));
		}
		
	}
#undef fcheckbox0
#undef fslider0
#undef fslider1
}

void __rt_func Dsp::compute_static(int fullcount, float *inputX0, float *outputX0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(fullcount, inputX0, outputX0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case GATE: 
		fcheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case SYNTHFREQ: 
		fslider1_ = (float*)data; // , 4.4e+02, 2e+01, 2e+04, 1.0 
		break;
	case GAIN: 
		fslider0_ = (float*)data; // , 0.8, 0.0, 1e+01, 0.01 
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
   GATE, 
   SYNTHFREQ, 
   GAIN, 
} PortIndex;
*/

} // end namespace uniBar
