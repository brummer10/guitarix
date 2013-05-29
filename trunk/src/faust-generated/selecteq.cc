// generated from file '../src/faust/selecteq.dsp' by dsp2cc:
// Code generated with Faust 0.9.46 (http://faust.grame.fr)


namespace selecteq {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	double 	fConst0;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT 	fslider2;
	double 	fRec9_perm[4];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT 	fslider5;
	double 	fRec8_perm[4];
	FAUSTFLOAT 	fslider6;
	FAUSTFLOAT 	fslider7;
	FAUSTFLOAT 	fslider8;
	double 	fRec7_perm[4];
	FAUSTFLOAT 	fslider9;
	FAUSTFLOAT 	fslider10;
	FAUSTFLOAT 	fslider11;
	double 	fRec6_perm[4];
	FAUSTFLOAT 	fslider12;
	FAUSTFLOAT 	fslider13;
	FAUSTFLOAT 	fslider14;
	double 	fRec5_perm[4];
	FAUSTFLOAT 	fslider15;
	FAUSTFLOAT 	fslider16;
	FAUSTFLOAT 	fslider17;
	double 	fRec4_perm[4];
	FAUSTFLOAT 	fslider18;
	FAUSTFLOAT 	fslider19;
	FAUSTFLOAT 	fslider20;
	double 	fRec3_perm[4];
	FAUSTFLOAT 	fslider21;
	FAUSTFLOAT 	fslider22;
	FAUSTFLOAT 	fslider23;
	double 	fRec2_perm[4];
	FAUSTFLOAT 	fslider24;
	FAUSTFLOAT 	fslider25;
	FAUSTFLOAT 	fslider26;
	double 	fRec1_perm[4];
	FAUSTFLOAT 	fslider27;
	FAUSTFLOAT 	fslider28;
	FAUSTFLOAT 	fslider29;
	double 	fRec0_perm[4];
	void clear_state_f();
	void init(unsigned int samplingFreq);
	void compute(int fullcount, float *inputX0, float *outputX0);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static void init_static(unsigned int samplingFreq, PluginDef*);
	static void compute_static(int fullcount, float *inputX0, float *outputX0, PluginDef*);
	static int register_params_static(const ParamReg& reg);
	static void del_instance(PluginDef *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginDef() {
	version = PLUGINDEF_VERSION;
	flags = 0;
	id = "eqs";
	name = N_("Scaleable EQ");
	groups = 0;
	description = ""; // description (tooltip)
	category = N_("Tone control");       // category
	shortname = "";     // shortname
	mono_audio = compute_static;
	stereo_audio = 0;
	set_samplerate = init_static;
	activate_plugin = 0;
	register_params = register_params_static;
	load_ui = 0;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int i=0; i<4; i++) fRec9_perm[i]=0;
	for (int i=0; i<4; i++) fRec8_perm[i]=0;
	for (int i=0; i<4; i++) fRec7_perm[i]=0;
	for (int i=0; i<4; i++) fRec6_perm[i]=0;
	for (int i=0; i<4; i++) fRec5_perm[i]=0;
	for (int i=0; i<4; i++) fRec4_perm[i]=0;
	for (int i=0; i<4; i++) fRec3_perm[i]=0;
	for (int i=0; i<4; i++) fRec2_perm[i]=0;
	for (int i=0; i<4; i++) fRec1_perm[i]=0;
	for (int i=0; i<4; i++) fRec0_perm[i]=0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = (3.141592653589793 / min(192000, max(1, fSamplingFreq)));
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int fullcount, float *inputX0, float *outputX0)
{
	double 	fZec0[128];
	double 	fRec9_tmp[128+4];
	double 	fZec1[128];
	double 	fRec8_tmp[128+4];
	double 	fZec2[128];
	double 	fRec7_tmp[128+4];
	double 	fZec3[128];
	double 	fRec6_tmp[128+4];
	double 	fZec4[128];
	double 	fRec5_tmp[128+4];
	double 	fZec5[128];
	double 	fRec4_tmp[128+4];
	double 	fZec6[128];
	double 	fRec3_tmp[128+4];
	double 	fZec7[128];
	double 	fRec2_tmp[128+4];
	double 	fZec8[128];
	double 	fRec1_tmp[128+4];
	double 	fZec9[128];
	double 	fRec0_tmp[128+4];
	double 	fSlow0 = tan((fConst0 * fslider0));
	double 	fSlow1 = (2 * (faustpower<2>(fSlow0) - 1));
	double 	fSlow2 = fslider1;
	double 	fSlow3 = (pow(10,(0.05 * (0 - fslider2))) / fSlow2);
	double 	fSlow4 = (1 + (fSlow0 * (fSlow0 - fSlow3)));
	double 	fSlow5 = (1.0 / (1 + (fSlow0 * (fSlow0 + fSlow3))));
	double* 	fRec9 = &fRec9_tmp[4];
	double 	fSlow6 = tan((fConst0 * fslider3));
	double 	fSlow7 = (2 * (faustpower<2>(fSlow6) - 1));
	double 	fSlow8 = fslider4;
	double 	fSlow9 = (pow(10,(0.05 * (0 - fslider5))) / fSlow8);
	double 	fSlow10 = (1 + (fSlow6 * (fSlow6 - fSlow9)));
	double 	fSlow11 = (1.0 / (1 + (fSlow6 * (fSlow6 + fSlow9))));
	double 	fSlow12 = (1.0 / fSlow2);
	double 	fSlow13 = (1 + (fSlow0 * (fSlow0 - fSlow12)));
	double 	fSlow14 = (1 + (fSlow0 * (fSlow0 + fSlow12)));
	double* 	fRec8 = &fRec8_tmp[4];
	double 	fSlow15 = tan((fConst0 * fslider6));
	double 	fSlow16 = (2 * (faustpower<2>(fSlow15) - 1));
	double 	fSlow17 = fslider7;
	double 	fSlow18 = (pow(10,(0.05 * (0 - fslider8))) / fSlow17);
	double 	fSlow19 = (1 + (fSlow15 * (fSlow15 - fSlow18)));
	double 	fSlow20 = (1.0 / (1 + (fSlow15 * (fSlow15 + fSlow18))));
	double 	fSlow21 = (1.0 / fSlow8);
	double 	fSlow22 = (1 + (fSlow6 * (fSlow6 - fSlow21)));
	double 	fSlow23 = (1 + (fSlow6 * (fSlow6 + fSlow21)));
	double* 	fRec7 = &fRec7_tmp[4];
	double 	fSlow24 = tan((fConst0 * fslider9));
	double 	fSlow25 = (2 * (faustpower<2>(fSlow24) - 1));
	double 	fSlow26 = fslider10;
	double 	fSlow27 = (pow(10,(0.05 * (0 - fslider11))) / fSlow26);
	double 	fSlow28 = (1 + (fSlow24 * (fSlow24 - fSlow27)));
	double 	fSlow29 = (1.0 / (1 + (fSlow24 * (fSlow24 + fSlow27))));
	double 	fSlow30 = (1.0 / fSlow17);
	double 	fSlow31 = (1 + (fSlow15 * (fSlow15 - fSlow30)));
	double 	fSlow32 = (1 + (fSlow15 * (fSlow15 + fSlow30)));
	double* 	fRec6 = &fRec6_tmp[4];
	double 	fSlow33 = tan((fConst0 * fslider12));
	double 	fSlow34 = (2 * (faustpower<2>(fSlow33) - 1));
	double 	fSlow35 = fslider13;
	double 	fSlow36 = (pow(10,(0.05 * (0 - fslider14))) / fSlow35);
	double 	fSlow37 = (1 + (fSlow33 * (fSlow33 - fSlow36)));
	double 	fSlow38 = (1.0 / (1 + (fSlow33 * (fSlow33 + fSlow36))));
	double 	fSlow39 = (1.0 / fSlow26);
	double 	fSlow40 = (1 + (fSlow24 * (fSlow24 - fSlow39)));
	double 	fSlow41 = (1 + (fSlow24 * (fSlow24 + fSlow39)));
	double* 	fRec5 = &fRec5_tmp[4];
	double 	fSlow42 = tan((fConst0 * fslider15));
	double 	fSlow43 = (2 * (faustpower<2>(fSlow42) - 1));
	double 	fSlow44 = fslider16;
	double 	fSlow45 = (pow(10,(0.05 * (0 - fslider17))) / fSlow44);
	double 	fSlow46 = (1 + (fSlow42 * (fSlow42 - fSlow45)));
	double 	fSlow47 = (1.0 / (1 + (fSlow42 * (fSlow42 + fSlow45))));
	double 	fSlow48 = (1.0 / fSlow35);
	double 	fSlow49 = (1 + (fSlow33 * (fSlow33 - fSlow48)));
	double 	fSlow50 = (1 + (fSlow33 * (fSlow33 + fSlow48)));
	double* 	fRec4 = &fRec4_tmp[4];
	double 	fSlow51 = tan((fConst0 * fslider18));
	double 	fSlow52 = (2 * (faustpower<2>(fSlow51) - 1));
	double 	fSlow53 = fslider19;
	double 	fSlow54 = (pow(10,(0.05 * (0 - fslider20))) / fSlow53);
	double 	fSlow55 = (1 + (fSlow51 * (fSlow51 - fSlow54)));
	double 	fSlow56 = (1.0 / (1 + (fSlow51 * (fSlow51 + fSlow54))));
	double 	fSlow57 = (1.0 / fSlow44);
	double 	fSlow58 = (1 + (fSlow42 * (fSlow42 - fSlow57)));
	double 	fSlow59 = (1 + (fSlow42 * (fSlow42 + fSlow57)));
	double* 	fRec3 = &fRec3_tmp[4];
	double 	fSlow60 = tan((fConst0 * fslider21));
	double 	fSlow61 = (2 * (faustpower<2>(fSlow60) - 1));
	double 	fSlow62 = fslider22;
	double 	fSlow63 = (pow(10,(0.05 * (0 - fslider23))) / fSlow62);
	double 	fSlow64 = (1 + (fSlow60 * (fSlow60 - fSlow63)));
	double 	fSlow65 = (1.0 / (1 + (fSlow60 * (fSlow60 + fSlow63))));
	double 	fSlow66 = (1.0 / fSlow53);
	double 	fSlow67 = (1 + (fSlow51 * (fSlow51 - fSlow66)));
	double 	fSlow68 = (1 + (fSlow51 * (fSlow51 + fSlow66)));
	double* 	fRec2 = &fRec2_tmp[4];
	double 	fSlow69 = tan((fConst0 * fslider24));
	double 	fSlow70 = (2 * (faustpower<2>(fSlow69) - 1));
	double 	fSlow71 = fslider25;
	double 	fSlow72 = (pow(10,(0.05 * (0 - fslider26))) / fSlow71);
	double 	fSlow73 = (1 + (fSlow69 * (fSlow69 - fSlow72)));
	double 	fSlow74 = (1.0 / (1 + (fSlow69 * (fSlow69 + fSlow72))));
	double 	fSlow75 = (1.0 / fSlow62);
	double 	fSlow76 = (1 + (fSlow60 * (fSlow60 - fSlow75)));
	double 	fSlow77 = (1 + (fSlow60 * (fSlow60 + fSlow75)));
	double* 	fRec1 = &fRec1_tmp[4];
	double 	fSlow78 = tan((fConst0 * fslider27));
	double 	fSlow79 = (2 * (faustpower<2>(fSlow78) - 1));
	double 	fSlow80 = fslider28;
	double 	fSlow81 = (pow(10,(0.05 * (0 - fslider29))) / fSlow80);
	double 	fSlow82 = (1 + (fSlow78 * (fSlow78 - fSlow81)));
	double 	fSlow83 = (1.0 / (1 + (fSlow78 * (fSlow78 + fSlow81))));
	double 	fSlow84 = (1.0 / fSlow71);
	double 	fSlow85 = (1 + (fSlow69 * (fSlow69 - fSlow84)));
	double 	fSlow86 = (1 + (fSlow69 * (fSlow69 + fSlow84)));
	double* 	fRec0 = &fRec0_tmp[4];
	double 	fSlow87 = (1.0 / fSlow80);
	double 	fSlow88 = (1 + (fSlow78 * (fSlow78 - fSlow87)));
	double 	fSlow89 = (1 + (fSlow78 * (fSlow78 + fSlow87)));
	int index;
	for (index = 0; index <= fullcount - 128; index += 128) {
		// compute by blocks of 128 samples
		const int count = 128;
		FAUSTFLOAT* input0 = &inputX0[index];
		FAUSTFLOAT* output0 = &outputX0[index];
		// SECTION : 1
		// LOOP 0x91cbf58
		// pre processing
		for (int i=0; i<4; i++) fRec9_tmp[i]=fRec9_perm[i];
		// exec code
		for (int i=0; i<count; i++) {
			fZec0[i] = (fSlow1 * fRec9[i-1]);
			fRec9[i] = ((double)input0[i] - (fSlow5 * ((fSlow4 * fRec9[i-2]) + fZec0[i])));
		}
		// post processing
		for (int i=0; i<4; i++) fRec9_perm[i]=fRec9_tmp[count+i];
		
		// SECTION : 2
		// LOOP 0x91cbcd0
		// pre processing
		for (int i=0; i<4; i++) fRec8_tmp[i]=fRec8_perm[i];
		// exec code
		for (int i=0; i<count; i++) {
			fZec1[i] = (fSlow7 * fRec8[i-1]);
			fRec8[i] = ((fSlow5 * ((fZec0[i] + (fSlow14 * fRec9[i])) + (fSlow13 * fRec9[i-2]))) - (fSlow11 * ((fSlow10 * fRec8[i-2]) + fZec1[i])));
		}
		// post processing
		for (int i=0; i<4; i++) fRec8_perm[i]=fRec8_tmp[count+i];
		
		// SECTION : 3
		// LOOP 0x91cba48
		// pre processing
		for (int i=0; i<4; i++) fRec7_tmp[i]=fRec7_perm[i];
		// exec code
		for (int i=0; i<count; i++) {
			fZec2[i] = (fSlow16 * fRec7[i-1]);
			fRec7[i] = ((fSlow11 * ((fZec1[i] + (fSlow23 * fRec8[i])) + (fSlow22 * fRec8[i-2]))) - (fSlow20 * ((fSlow19 * fRec7[i-2]) + fZec2[i])));
		}
		// post processing
		for (int i=0; i<4; i++) fRec7_perm[i]=fRec7_tmp[count+i];
		
		// SECTION : 4
		// LOOP 0x91cb7c0
		// pre processing
		for (int i=0; i<4; i++) fRec6_tmp[i]=fRec6_perm[i];
		// exec code
		for (int i=0; i<count; i++) {
			fZec3[i] = (fSlow25 * fRec6[i-1]);
			fRec6[i] = ((fSlow20 * ((fZec2[i] + (fSlow32 * fRec7[i])) + (fSlow31 * fRec7[i-2]))) - (fSlow29 * ((fSlow28 * fRec6[i-2]) + fZec3[i])));
		}
		// post processing
		for (int i=0; i<4; i++) fRec6_perm[i]=fRec6_tmp[count+i];
		
		// SECTION : 5
		// LOOP 0x91cb578
		// pre processing
		for (int i=0; i<4; i++) fRec5_tmp[i]=fRec5_perm[i];
		// exec code
		for (int i=0; i<count; i++) {
			fZec4[i] = (fSlow34 * fRec5[i-1]);
			fRec5[i] = ((fSlow29 * ((fZec3[i] + (fSlow41 * fRec6[i])) + (fSlow40 * fRec6[i-2]))) - (fSlow38 * ((fSlow37 * fRec5[i-2]) + fZec4[i])));
		}
		// post processing
		for (int i=0; i<4; i++) fRec5_perm[i]=fRec5_tmp[count+i];
		
		// SECTION : 6
		// LOOP 0x91cb3c0
		// pre processing
		for (int i=0; i<4; i++) fRec4_tmp[i]=fRec4_perm[i];
		// exec code
		for (int i=0; i<count; i++) {
			fZec5[i] = (fSlow43 * fRec4[i-1]);
			fRec4[i] = ((fSlow38 * ((fZec4[i] + (fSlow50 * fRec5[i])) + (fSlow49 * fRec5[i-2]))) - (fSlow47 * ((fSlow46 * fRec4[i-2]) + fZec5[i])));
		}
		// post processing
		for (int i=0; i<4; i++) fRec4_perm[i]=fRec4_tmp[count+i];
		
		// SECTION : 7
		// LOOP 0x91cb208
		// pre processing
		for (int i=0; i<4; i++) fRec3_tmp[i]=fRec3_perm[i];
		// exec code
		for (int i=0; i<count; i++) {
			fZec6[i] = (fSlow52 * fRec3[i-1]);
			fRec3[i] = ((fSlow47 * ((fZec5[i] + (fSlow59 * fRec4[i])) + (fSlow58 * fRec4[i-2]))) - (fSlow56 * ((fSlow55 * fRec3[i-2]) + fZec6[i])));
		}
		// post processing
		for (int i=0; i<4; i++) fRec3_perm[i]=fRec3_tmp[count+i];
		
		// SECTION : 8
		// LOOP 0x91cb050
		// pre processing
		for (int i=0; i<4; i++) fRec2_tmp[i]=fRec2_perm[i];
		// exec code
		for (int i=0; i<count; i++) {
			fZec7[i] = (fSlow61 * fRec2[i-1]);
			fRec2[i] = ((fSlow56 * ((fZec6[i] + (fSlow68 * fRec3[i])) + (fSlow67 * fRec3[i-2]))) - (fSlow65 * ((fSlow64 * fRec2[i-2]) + fZec7[i])));
		}
		// post processing
		for (int i=0; i<4; i++) fRec2_perm[i]=fRec2_tmp[count+i];
		
		// SECTION : 9
		// LOOP 0x91cae80
		// pre processing
		for (int i=0; i<4; i++) fRec1_tmp[i]=fRec1_perm[i];
		// exec code
		for (int i=0; i<count; i++) {
			fZec8[i] = (fSlow70 * fRec1[i-1]);
			fRec1[i] = ((fSlow65 * ((fZec7[i] + (fSlow77 * fRec2[i])) + (fSlow76 * fRec2[i-2]))) - (fSlow74 * ((fSlow73 * fRec1[i-2]) + fZec8[i])));
		}
		// post processing
		for (int i=0; i<4; i++) fRec1_perm[i]=fRec1_tmp[count+i];
		
		// SECTION : 10
		// LOOP 0x91cac78
		// pre processing
		for (int i=0; i<4; i++) fRec0_tmp[i]=fRec0_perm[i];
		// exec code
		for (int i=0; i<count; i++) {
			fZec9[i] = (fSlow79 * fRec0[i-1]);
			fRec0[i] = ((fSlow74 * ((fZec8[i] + (fSlow86 * fRec1[i])) + (fSlow85 * fRec1[i-2]))) - (fSlow83 * ((fSlow82 * fRec0[i-2]) + fZec9[i])));
		}
		// post processing
		for (int i=0; i<4; i++) fRec0_perm[i]=fRec0_tmp[count+i];
		
		// SECTION : 11
		// LOOP 0x91cab98
		// exec code
		for (int i=0; i<count; i++) {
			output0[i] = (FAUSTFLOAT)(fSlow83 * ((fZec9[i] + (fSlow89 * fRec0[i])) + (fSlow88 * fRec0[i-2])));
		}
		
	}
	if (index < fullcount) {
		// compute the remaining samples if any
		int count = fullcount-index;
		FAUSTFLOAT* input0 = &inputX0[index];
		FAUSTFLOAT* output0 = &outputX0[index];
		// SECTION : 1
		// LOOP 0x91cbf58
		// pre processing
		for (int i=0; i<4; i++) fRec9_tmp[i]=fRec9_perm[i];
		// exec code
		for (int i=0; i<count; i++) {
			fZec0[i] = (fSlow1 * fRec9[i-1]);
			fRec9[i] = ((double)input0[i] - (fSlow5 * ((fSlow4 * fRec9[i-2]) + fZec0[i])));
		}
		// post processing
		for (int i=0; i<4; i++) fRec9_perm[i]=fRec9_tmp[count+i];
		
		// SECTION : 2
		// LOOP 0x91cbcd0
		// pre processing
		for (int i=0; i<4; i++) fRec8_tmp[i]=fRec8_perm[i];
		// exec code
		for (int i=0; i<count; i++) {
			fZec1[i] = (fSlow7 * fRec8[i-1]);
			fRec8[i] = ((fSlow5 * ((fZec0[i] + (fSlow14 * fRec9[i])) + (fSlow13 * fRec9[i-2]))) - (fSlow11 * ((fSlow10 * fRec8[i-2]) + fZec1[i])));
		}
		// post processing
		for (int i=0; i<4; i++) fRec8_perm[i]=fRec8_tmp[count+i];
		
		// SECTION : 3
		// LOOP 0x91cba48
		// pre processing
		for (int i=0; i<4; i++) fRec7_tmp[i]=fRec7_perm[i];
		// exec code
		for (int i=0; i<count; i++) {
			fZec2[i] = (fSlow16 * fRec7[i-1]);
			fRec7[i] = ((fSlow11 * ((fZec1[i] + (fSlow23 * fRec8[i])) + (fSlow22 * fRec8[i-2]))) - (fSlow20 * ((fSlow19 * fRec7[i-2]) + fZec2[i])));
		}
		// post processing
		for (int i=0; i<4; i++) fRec7_perm[i]=fRec7_tmp[count+i];
		
		// SECTION : 4
		// LOOP 0x91cb7c0
		// pre processing
		for (int i=0; i<4; i++) fRec6_tmp[i]=fRec6_perm[i];
		// exec code
		for (int i=0; i<count; i++) {
			fZec3[i] = (fSlow25 * fRec6[i-1]);
			fRec6[i] = ((fSlow20 * ((fZec2[i] + (fSlow32 * fRec7[i])) + (fSlow31 * fRec7[i-2]))) - (fSlow29 * ((fSlow28 * fRec6[i-2]) + fZec3[i])));
		}
		// post processing
		for (int i=0; i<4; i++) fRec6_perm[i]=fRec6_tmp[count+i];
		
		// SECTION : 5
		// LOOP 0x91cb578
		// pre processing
		for (int i=0; i<4; i++) fRec5_tmp[i]=fRec5_perm[i];
		// exec code
		for (int i=0; i<count; i++) {
			fZec4[i] = (fSlow34 * fRec5[i-1]);
			fRec5[i] = ((fSlow29 * ((fZec3[i] + (fSlow41 * fRec6[i])) + (fSlow40 * fRec6[i-2]))) - (fSlow38 * ((fSlow37 * fRec5[i-2]) + fZec4[i])));
		}
		// post processing
		for (int i=0; i<4; i++) fRec5_perm[i]=fRec5_tmp[count+i];
		
		// SECTION : 6
		// LOOP 0x91cb3c0
		// pre processing
		for (int i=0; i<4; i++) fRec4_tmp[i]=fRec4_perm[i];
		// exec code
		for (int i=0; i<count; i++) {
			fZec5[i] = (fSlow43 * fRec4[i-1]);
			fRec4[i] = ((fSlow38 * ((fZec4[i] + (fSlow50 * fRec5[i])) + (fSlow49 * fRec5[i-2]))) - (fSlow47 * ((fSlow46 * fRec4[i-2]) + fZec5[i])));
		}
		// post processing
		for (int i=0; i<4; i++) fRec4_perm[i]=fRec4_tmp[count+i];
		
		// SECTION : 7
		// LOOP 0x91cb208
		// pre processing
		for (int i=0; i<4; i++) fRec3_tmp[i]=fRec3_perm[i];
		// exec code
		for (int i=0; i<count; i++) {
			fZec6[i] = (fSlow52 * fRec3[i-1]);
			fRec3[i] = ((fSlow47 * ((fZec5[i] + (fSlow59 * fRec4[i])) + (fSlow58 * fRec4[i-2]))) - (fSlow56 * ((fSlow55 * fRec3[i-2]) + fZec6[i])));
		}
		// post processing
		for (int i=0; i<4; i++) fRec3_perm[i]=fRec3_tmp[count+i];
		
		// SECTION : 8
		// LOOP 0x91cb050
		// pre processing
		for (int i=0; i<4; i++) fRec2_tmp[i]=fRec2_perm[i];
		// exec code
		for (int i=0; i<count; i++) {
			fZec7[i] = (fSlow61 * fRec2[i-1]);
			fRec2[i] = ((fSlow56 * ((fZec6[i] + (fSlow68 * fRec3[i])) + (fSlow67 * fRec3[i-2]))) - (fSlow65 * ((fSlow64 * fRec2[i-2]) + fZec7[i])));
		}
		// post processing
		for (int i=0; i<4; i++) fRec2_perm[i]=fRec2_tmp[count+i];
		
		// SECTION : 9
		// LOOP 0x91cae80
		// pre processing
		for (int i=0; i<4; i++) fRec1_tmp[i]=fRec1_perm[i];
		// exec code
		for (int i=0; i<count; i++) {
			fZec8[i] = (fSlow70 * fRec1[i-1]);
			fRec1[i] = ((fSlow65 * ((fZec7[i] + (fSlow77 * fRec2[i])) + (fSlow76 * fRec2[i-2]))) - (fSlow74 * ((fSlow73 * fRec1[i-2]) + fZec8[i])));
		}
		// post processing
		for (int i=0; i<4; i++) fRec1_perm[i]=fRec1_tmp[count+i];
		
		// SECTION : 10
		// LOOP 0x91cac78
		// pre processing
		for (int i=0; i<4; i++) fRec0_tmp[i]=fRec0_perm[i];
		// exec code
		for (int i=0; i<count; i++) {
			fZec9[i] = (fSlow79 * fRec0[i-1]);
			fRec0[i] = ((fSlow74 * ((fZec8[i] + (fSlow86 * fRec1[i])) + (fSlow85 * fRec1[i-2]))) - (fSlow83 * ((fSlow82 * fRec0[i-2]) + fZec9[i])));
		}
		// post processing
		for (int i=0; i<4; i++) fRec0_perm[i]=fRec0_tmp[count+i];
		
		// SECTION : 11
		// LOOP 0x91cab98
		// exec code
		for (int i=0; i<count; i++) {
			output0[i] = (FAUSTFLOAT)(fSlow83 * ((fZec9[i] + (fSlow89 * fRec0[i])) + (fSlow88 * fRec0[i-2])));
		}
		
	}
}

void __rt_func Dsp::compute_static(int fullcount, float *inputX0, float *outputX0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(fullcount, inputX0, outputX0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("eqs.Qs16k","","S","",&fslider28, 5e+01, 1.0, 1e+02, 1.0);
	reg.registerVar("eqs.fs16k","","S",N_("gain (dB) at 16 kHz"),&fslider29, 0.0, -4e+01, 3e+01, 0.1);
	reg.registerVar("eqs.fs8k","","S",N_("gain (dB) at 8 kHz"),&fslider26, 0.0, -4e+01, 3e+01, 0.1);
	reg.registerVar("eqs.freq16k","","S",N_("Hz"),&fslider27, 1.6e+04, 2e+01, 2e+04, 1.0);
	reg.registerVar("eqs.freq8k","","S",N_("Hz"),&fslider24, 8e+03, 2e+01, 2e+04, 1.0);
	reg.registerVar("eqs.Qs8k","","S","",&fslider25, 5e+01, 1.0, 1e+02, 1.0);
	reg.registerVar("eqs.Qs4k","","S","",&fslider22, 5e+01, 1.0, 1e+02, 1.0);
	reg.registerVar("eqs.fs4k","","S",N_("gain (dB) at 4 kHz"),&fslider23, 0.0, -4e+01, 3e+01, 0.1);
	reg.registerVar("eqs.fs2k","","S",N_("gain (dB) at 2 kHz"),&fslider20, 0.0, -4e+01, 3e+01, 0.1);
	reg.registerVar("eqs.freq4k","","S",N_("Hz"),&fslider21, 4e+03, 2e+01, 2e+04, 1.0);
	reg.registerVar("eqs.Qs500","","S","",&fslider13, 5e+01, 1.0, 1e+02, 1.0);
	reg.registerVar("eqs.freq500","","S",N_("Hz"),&fslider12, 5e+02, 2e+01, 2e+04, 1.0);
	reg.registerVar("eqs.fs250","","S",N_("gain (dB) at 250 Hz"),&fslider11, 0.0, -4e+01, 3e+01, 0.1);
	reg.registerVar("eqs.Qs250","","S","",&fslider10, 5e+01, 1.0, 1e+02, 1.0);
	reg.registerVar("eqs.fs1k","","S",N_("gain (dB) at 1 kHz"),&fslider17, 0.0, -4e+01, 3e+01, 0.1);
	reg.registerVar("eqs.Qs1k","","S","",&fslider16, 5e+01, 1.0, 1e+02, 1.0);
	reg.registerVar("eqs.freq1k","","S",N_("Hz"),&fslider15, 1e+03, 2e+01, 2e+04, 1.0);
	reg.registerVar("eqs.fs500","","S",N_("gain (dB) at 500 Hz"),&fslider14, 0.0, -4e+01, 3e+01, 0.1);
	reg.registerVar("eqs.Qs2k","","S","",&fslider19, 5e+01, 1.0, 1e+02, 1.0);
	reg.registerVar("eqs.freq2k","","S",N_("Hz"),&fslider18, 2e+03, 2e+01, 2e+04, 1.0);
	reg.registerVar("eqs.Qs125","","S","",&fslider7, 5e+01, 1.0, 1e+02, 1.0);
	reg.registerVar("eqs.freq125","","S",N_("Hz"),&fslider6, 125.0, 2e+01, 2e+04, 1.0);
	reg.registerVar("eqs.fs62_5","","S",N_("gain (dB) at 62.5 Hz"),&fslider5, 0.0, -4e+01, 3e+01, 0.1);
	reg.registerVar("eqs.Qs62_5","","S","",&fslider4, 5e+01, 1.0, 1e+02, 1.0);
	reg.registerVar("eqs.freq62_5","","S",N_("Hz"),&fslider3, 62.0, 2e+01, 2e+04, 1.0);
	reg.registerVar("eqs.fs31_25","","S",N_("gain (dB) at 31.25 Hz"),&fslider2, 0.0, -4e+01, 3e+01, 0.1);
	reg.registerVar("eqs.Qs31_25","","S","",&fslider1, 5e+01, 1.0, 1e+02, 1.0);
	reg.registerVar("eqs.freq31_25","","S",N_("Hz"),&fslider0, 31.0, 2e+01, 2e+04, 1.0);
	reg.registerVar("eqs.freq250","","S",N_("Hz"),&fslider9, 2.5e+02, 2e+01, 2e+04, 1.0);
	reg.registerVar("eqs.fs125","","S",N_("gain (dB) at 125 Hz"),&fslider8, 0.0, -4e+01, 3e+01, 0.1);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

PluginDef *plugin() {
	return new Dsp();
}

void Dsp::del_instance(PluginDef *p)
{
	delete static_cast<Dsp*>(p);
}

} // end namespace selecteq
