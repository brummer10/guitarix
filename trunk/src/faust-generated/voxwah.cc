// generated from file '../src/faust/voxwah.dsp' by dsp2cc:
// Code generated with Faust 2.15.11 (https://faust.grame.fr)


namespace voxwah {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fConst4;
	double fConst5;
	double fYec0_perm[4];
	double fRec1_perm[4];
	double fConst6;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec4_perm[4];
	int iVec0_perm[4];
	double fRec3_perm[4];
	double fRec2_perm[4];
	double fConst7;
	double fConst8;
	double fRec7_perm[4];
	double fConst9;
	double fConst10;
	double fRec6_perm[4];
	double fRec5_perm[4];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec8_perm[4];
	double fConst11;
	double fConst12;
	double fConst13;
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fConst14;
	double fConst15;
	double fConst16;
	double fConst17;
	double fConst18;
	double fConst19;
	double fConst20;
	double fConst21;
	double fConst22;
	double fConst23;
	double fConst24;
	double fConst25;
	double fConst26;
	double fConst27;
	double fConst28;
	double fConst29;
	double fConst30;
	double fConst31;
	double fConst32;
	double fRec0_perm[4];
	double fConst33;
	double fConst34;
	double fConst35;
	double fConst36;
	double fConst37;
	double fConst38;
	double fConst39;
	double fConst40;
	double fConst41;
	double fConst42;
	double fConst43;
	double fConst44;
	double fConst45;
	double fConst46;
	double fConst47;
	double fConst48;
	double fConst49;
	double fConst50;
	double fConst51;
	double fConst52;
	double fConst53;

	void clear_state_f();
	void init(unsigned int samplingFreq);
	void compute(int count, FAUSTFLOAT *inputX0, FAUSTFLOAT *outputX0);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static void init_static(unsigned int samplingFreq, PluginDef*);
	static void compute_static(int count, FAUSTFLOAT *inputX0, FAUSTFLOAT *outputX0, PluginDef*);
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
	id = "voxwah";
	name = N_("Vox Wah V847");
	groups = 0;
	description = N_("Vox Wah V847"); // description (tooltip)
	category = N_("Guitar Effects");       // category
	shortname = N_("Vox Wah");     // shortname
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
	for (int l0 = 0; (l0 < 4); l0 = (l0 + 1)) fYec0_perm[l0] = 0.0;
	for (int l1 = 0; (l1 < 4); l1 = (l1 + 1)) fRec1_perm[l1] = 0.0;
	for (int l2 = 0; (l2 < 4); l2 = (l2 + 1)) fRec4_perm[l2] = 0.0;
	for (int l3 = 0; (l3 < 4); l3 = (l3 + 1)) iVec0_perm[l3] = 0;
	for (int l4 = 0; (l4 < 4); l4 = (l4 + 1)) fRec3_perm[l4] = 0.0;
	for (int l5 = 0; (l5 < 4); l5 = (l5 + 1)) fRec2_perm[l5] = 0.0;
	for (int l6 = 0; (l6 < 4); l6 = (l6 + 1)) fRec7_perm[l6] = 0.0;
	for (int l7 = 0; (l7 < 4); l7 = (l7 + 1)) fRec6_perm[l7] = 0.0;
	for (int l8 = 0; (l8 < 4); l8 = (l8 + 1)) fRec5_perm[l8] = 0.0;
	for (int l9 = 0; (l9 < 4); l9 = (l9 + 1)) fRec8_perm[l9] = 0.0;
	for (int l10 = 0; (l10 < 4); l10 = (l10 + 1)) fRec0_perm[l10] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSamplingFreq)));
	fConst1 = (716.57315087380141 / fConst0);
	fConst2 = (fConst1 + 1.0);
	fConst3 = (1.0 / fConst2);
	fConst4 = (1.0 - fConst1);
	fConst5 = (0.01 / fConst2);
	fConst6 = (0.10471975511965977 / fConst0);
	fConst7 = std::exp((0.0 - (10.0 / fConst0)));
	fConst8 = (1.0 - fConst7);
	fConst9 = std::exp((0.0 - (100.0 / fConst0)));
	fConst10 = (1.0 - fConst9);
	fConst11 = (2.0025718801104299e-19 * fConst0);
	fConst12 = mydsp_faustpower2_f(fConst0);
	fConst13 = (((-6.88510194321502e-17 - fConst11) * fConst12) + 2.9721030168538698e-11);
	fConst14 = (1.18574819071565e-18 * fConst0);
	fConst15 = (((-4.4130909394522001e-17 - fConst14) * fConst12) + 3.9233605261862003e-12);
	fConst16 = (1.77461540007175e-19 * fConst0);
	fConst17 = ((fConst16 + 1.27350423451651e-17) * fConst12);
	fConst18 = ((3.0038578201656399e-19 * fConst12) + -1.24767383443114e-12);
	fConst19 = ((1.7786222860734801e-18 * fConst12) + -1.04524039940345e-13);
	fConst20 = (1.3810229052175401e-13 - (2.66192310010762e-19 * fConst12));
	fConst21 = (((6.88510194321502e-17 - fConst11) * fConst12) + -2.9721030168538698e-11);
	fConst22 = (((4.4130909394522001e-17 - fConst14) * fConst12) + -3.9233605261862003e-12);
	fConst23 = ((fConst16 + -1.27350423451651e-17) * fConst12);
	fConst24 = (5.0064297002760598e-20 * fConst0);
	fConst25 = (((((fConst24 + -3.44255097160751e-17) * fConst0) + 6.2383691721556798e-13) * fConst0) + -1.48605150842693e-11);
	fConst26 = (2.9643704767891302e-19 * fConst0);
	fConst27 = (((((fConst26 + -2.2065454697261e-17) * fConst0) + 5.2262019970172701e-14) * fConst0) + -1.9616802630931001e-12);
	fConst28 = (4.4365385001793701e-20 * fConst0);
	fConst29 = ((((6.36752117258257e-18 - fConst28) * fConst0) + -6.9051145260877105e-14) * fConst0);
	fConst30 = (((((fConst24 + 3.44255097160751e-17) * fConst0) + 6.2383691721556798e-13) * fConst0) + 1.48605150842693e-11);
	fConst31 = (((((fConst26 + 2.2065454697261e-17) * fConst0) + 5.2262019970172701e-14) * fConst0) + 1.9616802630931001e-12);
	fConst32 = ((((-6.36752117258257e-18 - fConst28) * fConst0) + -6.9051145260877105e-14) * fConst0);
	fConst33 = (7.5608386008615503e-21 * fConst0);
	fConst34 = (((((-2.5031607202699102e-16 - fConst33) * fConst0) + -3.73895528534631e-13) * fConst0) + -2.0007925501478499e-12);
	fConst35 = (1.25190991353587e-21 * fConst0);
	fConst36 = (((((-3.4852328346311903e-17 - fConst35) * fConst0) + -5.2316993137229003e-14) * fConst0) + -1.41321715016552e-12);
	fConst37 = (1.2535492934112801e-21 * fConst0);
	fConst38 = ((((fConst37 + 3.4824044172122303e-17) * fConst0) + 5.1367793843580803e-14) * fConst0);
	fConst39 = (3.0243354403446201e-20 * fConst0);
	fConst40 = (((fConst39 + 5.0063214405398096e-16) * fConst12) + -4.0015851002956998e-12);
	fConst41 = (5.0076396541434904e-21 * fConst0);
	fConst42 = (((fConst41 + 6.9704656692623805e-17) * fConst12) + -2.82643430033104e-12);
	fConst43 = (5.01419717364513e-21 * fConst0);
	fConst44 = ((-6.9648088344244704e-17 - fConst43) * fConst12);
	fConst45 = (7.4779105706926201e-13 - (4.5365031605169299e-20 * fConst12));
	fConst46 = (1.0463398627445801e-13 - (7.5114594812152299e-21 * fConst12));
	fConst47 = ((7.5212957604676898e-21 * fConst12) + -1.02735587687162e-13);
	fConst48 = (((fConst39 + -5.0063214405398096e-16) * fConst12) + 4.0015851002956998e-12);
	fConst49 = (((fConst41 + -6.9704656692623805e-17) * fConst12) + 2.82643430033104e-12);
	fConst50 = ((6.9648088344244704e-17 - fConst43) * fConst12);
	fConst51 = (((((2.5031607202699102e-16 - fConst33) * fConst0) + -3.73895528534631e-13) * fConst0) + 2.0007925501478499e-12);
	fConst52 = (((((3.4852328346311903e-17 - fConst35) * fConst0) + -5.2316993137229003e-14) * fConst0) + 1.41321715016552e-12);
	fConst53 = ((((fConst37 + -3.4824044172122303e-17) * fConst0) + 5.1367793843580803e-14) * fConst0);
	fVslider0 = FAUSTFLOAT(100.0);
	fVslider1 = FAUSTFLOAT(24.0);
	fVslider2 = FAUSTFLOAT(0.0);
	fVslider3 = FAUSTFLOAT(0.0);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *inputX0, FAUSTFLOAT *outputX0)
{
#define fVslider0 (*fVslider0_)
#define fVslider1 (*fVslider1_)
#define fVslider2 (*fVslider2_)
#define fVslider3 (*fVslider3_)
	FAUSTFLOAT* input0_ptr = &inputX0[0];
	FAUSTFLOAT* output0_ptr = &outputX0[0];
	double fSlow0 = double(fVslider0);
	double fSlow1 = (0.01 * fSlow0);
	double fSlow2 = (fConst5 * fSlow0);
	double fYec0_tmp[36];
	double* fYec0 = &fYec0_tmp[4];
	double fRec1_tmp[36];
	double* fRec1 = &fRec1_tmp[4];
	double fSlow3 = (fConst6 * double(fVslider1));
	double fRec4_tmp[36];
	double* fRec4 = &fRec4_tmp[4];
	int iVec0_tmp[36];
	int* iVec0 = &iVec0_tmp[4];
	double fRec3_tmp[36];
	double* fRec3 = &fRec3_tmp[4];
	double fRec2_tmp[36];
	double* fRec2 = &fRec2_tmp[4];
	double fZec0[32];
	double fRec7_tmp[36];
	double* fRec7 = &fRec7_tmp[4];
	double fRec6_tmp[36];
	double* fRec6 = &fRec6_tmp[4];
	double fRec5_tmp[36];
	double* fRec5 = &fRec5_tmp[4];
	double fSlow4 = (4.748558434412966e-05 * (std::exp((5.0 * std::max<double>(0.029999999999999999, double(fVslider2)))) + -1.0));
	double fRec8_tmp[36];
	double* fRec8 = &fRec8_tmp[4];
	int iSlow5 = int(double(fVslider3));
	int iSlow6 = (iSlow5 == 0);
	int iSlow7 = (iSlow5 == 1);
	double fZec1[32];
	double fZec2[32];
	double fRec0_tmp[36];
	double* fRec0 = &fRec0_tmp[4];
	double fSlow8 = (1.0 - fSlow1);
	int vindex = 0;
	/* Main loop */
	for (vindex = 0; (vindex <= (count - 32)); vindex = (vindex + 32)) {
		FAUSTFLOAT* input0 = &input0_ptr[vindex];
		FAUSTFLOAT* output0 = &output0_ptr[vindex];
		int vsize = 32;
		/* Vectorizable loop 0 */
		/* Compute code */
		for (int i = 0; (i < vsize); i = (i + 1)) {
			fZec0[i] = std::fabs(double(input0[i]));
		}
		/* Recursive loop 1 */
		/* Pre code */
		for (int j12 = 0; (j12 < 4); j12 = (j12 + 1)) {
			fRec7_tmp[j12] = fRec7_perm[j12];
		}
		/* Compute code */
		for (int i = 0; (i < vsize); i = (i + 1)) {
			fRec7[i] = std::max<double>(fZec0[i], ((fConst7 * fRec7[(i - 1)]) + (fConst8 * fZec0[i])));
		}
		/* Post code */
		for (int j13 = 0; (j13 < 4); j13 = (j13 + 1)) {
			fRec7_perm[j13] = fRec7_tmp[(vsize + j13)];
		}
		/* Vectorizable loop 2 */
		/* Pre code */
		for (int j6 = 0; (j6 < 4); j6 = (j6 + 1)) {
			iVec0_tmp[j6] = iVec0_perm[j6];
		}
		/* Compute code */
		for (int i = 0; (i < vsize); i = (i + 1)) {
			iVec0[i] = 1;
		}
		/* Post code */
		for (int j7 = 0; (j7 < 4); j7 = (j7 + 1)) {
			iVec0_perm[j7] = iVec0_tmp[(vsize + j7)];
		}
		/* Recursive loop 3 */
		/* Pre code */
		for (int j14 = 0; (j14 < 4); j14 = (j14 + 1)) {
			fRec6_tmp[j14] = fRec6_perm[j14];
		}
		/* Compute code */
		for (int i = 0; (i < vsize); i = (i + 1)) {
			fRec6[i] = ((fConst9 * fRec6[(i - 1)]) + (fConst10 * fRec7[i]));
		}
		/* Post code */
		for (int j15 = 0; (j15 < 4); j15 = (j15 + 1)) {
			fRec6_perm[j15] = fRec6_tmp[(vsize + j15)];
		}
		/* Recursive loop 4 */
		/* Pre code */
		for (int j4 = 0; (j4 < 4); j4 = (j4 + 1)) {
			fRec4_tmp[j4] = fRec4_perm[j4];
		}
		for (int j8 = 0; (j8 < 4); j8 = (j8 + 1)) {
			fRec3_tmp[j8] = fRec3_perm[j8];
		}
		for (int j10 = 0; (j10 < 4); j10 = (j10 + 1)) {
			fRec2_tmp[j10] = fRec2_perm[j10];
		}
		/* Compute code */
		for (int i = 0; (i < vsize); i = (i + 1)) {
			fRec4[i] = (fRec4[(i - 1)] + (fSlow3 * (0.0 - fRec2[(i - 1)])));
			fRec3[i] = ((fSlow3 * fRec4[i]) + (double((1 - iVec0[(i - 1)])) + fRec3[(i - 1)]));
			fRec2[i] = fRec3[i];
		}
		/* Post code */
		for (int j5 = 0; (j5 < 4); j5 = (j5 + 1)) {
			fRec4_perm[j5] = fRec4_tmp[(vsize + j5)];
		}
		for (int j9 = 0; (j9 < 4); j9 = (j9 + 1)) {
			fRec3_perm[j9] = fRec3_tmp[(vsize + j9)];
		}
		for (int j11 = 0; (j11 < 4); j11 = (j11 + 1)) {
			fRec2_perm[j11] = fRec2_tmp[(vsize + j11)];
		}
		/* Recursive loop 5 */
		/* Pre code */
		for (int j16 = 0; (j16 < 4); j16 = (j16 + 1)) {
			fRec5_tmp[j16] = fRec5_perm[j16];
		}
		/* Compute code */
		for (int i = 0; (i < vsize); i = (i + 1)) {
			fRec5[i] = ((0.99299999999999999 * fRec5[(i - 1)]) + (0.0070000000000000062 * (1.0 - std::max<double>(0.029999999999999999, std::min<double>(0.97999999999999998, fRec6[i])))));
		}
		/* Post code */
		for (int j17 = 0; (j17 < 4); j17 = (j17 + 1)) {
			fRec5_perm[j17] = fRec5_tmp[(vsize + j17)];
		}
		/* Recursive loop 6 */
		/* Pre code */
		for (int j18 = 0; (j18 < 4); j18 = (j18 + 1)) {
			fRec8_tmp[j18] = fRec8_perm[j18];
		}
		/* Compute code */
		for (int i = 0; (i < vsize); i = (i + 1)) {
			fRec8[i] = (fSlow4 + (0.99299999999999999 * fRec8[(i - 1)]));
		}
		/* Post code */
		for (int j19 = 0; (j19 < 4); j19 = (j19 + 1)) {
			fRec8_perm[j19] = fRec8_tmp[(vsize + j19)];
		}
		/* Vectorizable loop 7 */
		/* Pre code */
		for (int j0 = 0; (j0 < 4); j0 = (j0 + 1)) {
			fYec0_tmp[j0] = fYec0_perm[j0];
		}
		/* Compute code */
		for (int i = 0; (i < vsize); i = (i + 1)) {
			fYec0[i] = (fSlow2 * double(input0[i]));
		}
		/* Post code */
		for (int j1 = 0; (j1 < 4); j1 = (j1 + 1)) {
			fYec0_perm[j1] = fYec0_tmp[(vsize + j1)];
		}
		/* Vectorizable loop 8 */
		/* Compute code */
		for (int i = 0; (i < vsize); i = (i + 1)) {
			fZec1[i] = (iSlow6?fRec8[i]:(iSlow7?fRec5[i]:std::max<double>(0.029999999999999999, std::min<double>(1.0, (0.5 * (fRec2[i] + 1.0))))));
		}
		/* Recursive loop 9 */
		/* Pre code */
		for (int j2 = 0; (j2 < 4); j2 = (j2 + 1)) {
			fRec1_tmp[j2] = fRec1_perm[j2];
		}
		/* Compute code */
		for (int i = 0; (i < vsize); i = (i + 1)) {
			fRec1[i] = ((fConst3 * ((fSlow1 * double(input0[i])) + (fConst4 * fRec1[(i - 1)]))) - fYec0[(i - 1)]);
		}
		/* Post code */
		for (int j3 = 0; (j3 < 4); j3 = (j3 + 1)) {
			fRec1_perm[j3] = fRec1_tmp[(vsize + j3)];
		}
		/* Vectorizable loop 10 */
		/* Compute code */
		for (int i = 0; (i < vsize); i = (i + 1)) {
			fZec2[i] = ((fConst0 * (fConst30 + (fZec1[i] * (fConst31 + (fConst32 * fZec1[i]))))) + 5.5729552928781202e-11);
		}
		/* Recursive loop 11 */
		/* Pre code */
		for (int j20 = 0; (j20 < 4); j20 = (j20 + 1)) {
			fRec0_tmp[j20] = fRec0_perm[j20];
		}
		/* Compute code */
		for (int i = 0; (i < vsize); i = (i + 1)) {
			fRec0[i] = (fRec1[i] - (((((fRec0[(i - 1)] * ((fConst0 * (fConst13 + (fZec1[i] * (fConst15 + (fConst17 * fZec1[i]))))) + 2.2291821171512499e-10)) + (fRec0[(i - 2)] * ((fConst12 * (fConst18 + (fZec1[i] * (fConst19 + (fConst20 * fZec1[i]))))) + 3.3437731757268698e-10))) + (fRec0[(i - 3)] * ((fConst0 * (fConst21 + (fZec1[i] * (fConst22 + (fConst23 * fZec1[i]))))) + 2.2291821171512499e-10))) + (fRec0[(i - 4)] * ((fConst0 * (fConst25 + (fZec1[i] * (fConst27 + (fConst29 * fZec1[i]))))) + 5.5729552928781202e-11))) / fZec2[i]));
		}
		/* Post code */
		for (int j21 = 0; (j21 < 4); j21 = (j21 + 1)) {
			fRec0_perm[j21] = fRec0_tmp[(vsize + j21)];
		}
		/* Vectorizable loop 12 */
		/* Compute code */
		for (int i = 0; (i < vsize); i = (i + 1)) {
			output0[i] = FAUSTFLOAT(((fSlow8 * double(input0[i])) + (fConst0 * ((((((fRec0[i] * (fConst34 + (fZec1[i] * (fConst36 + (fConst38 * fZec1[i]))))) + (fRec0[(i - 1)] * (fConst40 + (fZec1[i] * (fConst42 + (fConst44 * fZec1[i])))))) + (fConst0 * (fRec0[(i - 2)] * (fConst45 + (fZec1[i] * (fConst46 + (fConst47 * fZec1[i]))))))) + (fRec0[(i - 3)] * (fConst48 + (fZec1[i] * (fConst49 + (fConst50 * fZec1[i])))))) + (fRec0[(i - 4)] * (fConst51 + (fZec1[i] * (fConst52 + (fConst53 * fZec1[i])))))) / fZec2[i]))));
		}
	}
	/* Remaining frames */
	if (vindex < count) {
		FAUSTFLOAT* input0 = &input0_ptr[vindex];
		FAUSTFLOAT* output0 = &output0_ptr[vindex];
		int vsize = (count - vindex);
		/* Vectorizable loop 0 */
		/* Compute code */
		for (int i = 0; (i < vsize); i = (i + 1)) {
			fZec0[i] = std::fabs(double(input0[i]));
		}
		/* Recursive loop 1 */
		/* Pre code */
		for (int j12 = 0; (j12 < 4); j12 = (j12 + 1)) {
			fRec7_tmp[j12] = fRec7_perm[j12];
		}
		/* Compute code */
		for (int i = 0; (i < vsize); i = (i + 1)) {
			fRec7[i] = std::max<double>(fZec0[i], ((fConst7 * fRec7[(i - 1)]) + (fConst8 * fZec0[i])));
		}
		/* Post code */
		for (int j13 = 0; (j13 < 4); j13 = (j13 + 1)) {
			fRec7_perm[j13] = fRec7_tmp[(vsize + j13)];
		}
		/* Vectorizable loop 2 */
		/* Pre code */
		for (int j6 = 0; (j6 < 4); j6 = (j6 + 1)) {
			iVec0_tmp[j6] = iVec0_perm[j6];
		}
		/* Compute code */
		for (int i = 0; (i < vsize); i = (i + 1)) {
			iVec0[i] = 1;
		}
		/* Post code */
		for (int j7 = 0; (j7 < 4); j7 = (j7 + 1)) {
			iVec0_perm[j7] = iVec0_tmp[(vsize + j7)];
		}
		/* Recursive loop 3 */
		/* Pre code */
		for (int j14 = 0; (j14 < 4); j14 = (j14 + 1)) {
			fRec6_tmp[j14] = fRec6_perm[j14];
		}
		/* Compute code */
		for (int i = 0; (i < vsize); i = (i + 1)) {
			fRec6[i] = ((fConst9 * fRec6[(i - 1)]) + (fConst10 * fRec7[i]));
		}
		/* Post code */
		for (int j15 = 0; (j15 < 4); j15 = (j15 + 1)) {
			fRec6_perm[j15] = fRec6_tmp[(vsize + j15)];
		}
		/* Recursive loop 4 */
		/* Pre code */
		for (int j4 = 0; (j4 < 4); j4 = (j4 + 1)) {
			fRec4_tmp[j4] = fRec4_perm[j4];
		}
		for (int j8 = 0; (j8 < 4); j8 = (j8 + 1)) {
			fRec3_tmp[j8] = fRec3_perm[j8];
		}
		for (int j10 = 0; (j10 < 4); j10 = (j10 + 1)) {
			fRec2_tmp[j10] = fRec2_perm[j10];
		}
		/* Compute code */
		for (int i = 0; (i < vsize); i = (i + 1)) {
			fRec4[i] = (fRec4[(i - 1)] + (fSlow3 * (0.0 - fRec2[(i - 1)])));
			fRec3[i] = ((fSlow3 * fRec4[i]) + (double((1 - iVec0[(i - 1)])) + fRec3[(i - 1)]));
			fRec2[i] = fRec3[i];
		}
		/* Post code */
		for (int j5 = 0; (j5 < 4); j5 = (j5 + 1)) {
			fRec4_perm[j5] = fRec4_tmp[(vsize + j5)];
		}
		for (int j9 = 0; (j9 < 4); j9 = (j9 + 1)) {
			fRec3_perm[j9] = fRec3_tmp[(vsize + j9)];
		}
		for (int j11 = 0; (j11 < 4); j11 = (j11 + 1)) {
			fRec2_perm[j11] = fRec2_tmp[(vsize + j11)];
		}
		/* Recursive loop 5 */
		/* Pre code */
		for (int j16 = 0; (j16 < 4); j16 = (j16 + 1)) {
			fRec5_tmp[j16] = fRec5_perm[j16];
		}
		/* Compute code */
		for (int i = 0; (i < vsize); i = (i + 1)) {
			fRec5[i] = ((0.99299999999999999 * fRec5[(i - 1)]) + (0.0070000000000000062 * (1.0 - std::max<double>(0.029999999999999999, std::min<double>(0.97999999999999998, fRec6[i])))));
		}
		/* Post code */
		for (int j17 = 0; (j17 < 4); j17 = (j17 + 1)) {
			fRec5_perm[j17] = fRec5_tmp[(vsize + j17)];
		}
		/* Recursive loop 6 */
		/* Pre code */
		for (int j18 = 0; (j18 < 4); j18 = (j18 + 1)) {
			fRec8_tmp[j18] = fRec8_perm[j18];
		}
		/* Compute code */
		for (int i = 0; (i < vsize); i = (i + 1)) {
			fRec8[i] = (fSlow4 + (0.99299999999999999 * fRec8[(i - 1)]));
		}
		/* Post code */
		for (int j19 = 0; (j19 < 4); j19 = (j19 + 1)) {
			fRec8_perm[j19] = fRec8_tmp[(vsize + j19)];
		}
		/* Vectorizable loop 7 */
		/* Pre code */
		for (int j0 = 0; (j0 < 4); j0 = (j0 + 1)) {
			fYec0_tmp[j0] = fYec0_perm[j0];
		}
		/* Compute code */
		for (int i = 0; (i < vsize); i = (i + 1)) {
			fYec0[i] = (fSlow2 * double(input0[i]));
		}
		/* Post code */
		for (int j1 = 0; (j1 < 4); j1 = (j1 + 1)) {
			fYec0_perm[j1] = fYec0_tmp[(vsize + j1)];
		}
		/* Vectorizable loop 8 */
		/* Compute code */
		for (int i = 0; (i < vsize); i = (i + 1)) {
			fZec1[i] = (iSlow6?fRec8[i]:(iSlow7?fRec5[i]:std::max<double>(0.029999999999999999, std::min<double>(1.0, (0.5 * (fRec2[i] + 1.0))))));
		}
		/* Recursive loop 9 */
		/* Pre code */
		for (int j2 = 0; (j2 < 4); j2 = (j2 + 1)) {
			fRec1_tmp[j2] = fRec1_perm[j2];
		}
		/* Compute code */
		for (int i = 0; (i < vsize); i = (i + 1)) {
			fRec1[i] = ((fConst3 * ((fSlow1 * double(input0[i])) + (fConst4 * fRec1[(i - 1)]))) - fYec0[(i - 1)]);
		}
		/* Post code */
		for (int j3 = 0; (j3 < 4); j3 = (j3 + 1)) {
			fRec1_perm[j3] = fRec1_tmp[(vsize + j3)];
		}
		/* Vectorizable loop 10 */
		/* Compute code */
		for (int i = 0; (i < vsize); i = (i + 1)) {
			fZec2[i] = ((fConst0 * (fConst30 + (fZec1[i] * (fConst31 + (fConst32 * fZec1[i]))))) + 5.5729552928781202e-11);
		}
		/* Recursive loop 11 */
		/* Pre code */
		for (int j20 = 0; (j20 < 4); j20 = (j20 + 1)) {
			fRec0_tmp[j20] = fRec0_perm[j20];
		}
		/* Compute code */
		for (int i = 0; (i < vsize); i = (i + 1)) {
			fRec0[i] = (fRec1[i] - (((((fRec0[(i - 1)] * ((fConst0 * (fConst13 + (fZec1[i] * (fConst15 + (fConst17 * fZec1[i]))))) + 2.2291821171512499e-10)) + (fRec0[(i - 2)] * ((fConst12 * (fConst18 + (fZec1[i] * (fConst19 + (fConst20 * fZec1[i]))))) + 3.3437731757268698e-10))) + (fRec0[(i - 3)] * ((fConst0 * (fConst21 + (fZec1[i] * (fConst22 + (fConst23 * fZec1[i]))))) + 2.2291821171512499e-10))) + (fRec0[(i - 4)] * ((fConst0 * (fConst25 + (fZec1[i] * (fConst27 + (fConst29 * fZec1[i]))))) + 5.5729552928781202e-11))) / fZec2[i]));
		}
		/* Post code */
		for (int j21 = 0; (j21 < 4); j21 = (j21 + 1)) {
			fRec0_perm[j21] = fRec0_tmp[(vsize + j21)];
		}
		/* Vectorizable loop 12 */
		/* Compute code */
		for (int i = 0; (i < vsize); i = (i + 1)) {
			output0[i] = FAUSTFLOAT(((fSlow8 * double(input0[i])) + (fConst0 * ((((((fRec0[i] * (fConst34 + (fZec1[i] * (fConst36 + (fConst38 * fZec1[i]))))) + (fRec0[(i - 1)] * (fConst40 + (fZec1[i] * (fConst42 + (fConst44 * fZec1[i])))))) + (fConst0 * (fRec0[(i - 2)] * (fConst45 + (fZec1[i] * (fConst46 + (fConst47 * fZec1[i]))))))) + (fRec0[(i - 3)] * (fConst48 + (fZec1[i] * (fConst49 + (fConst50 * fZec1[i])))))) + (fRec0[(i - 4)] * (fConst51 + (fZec1[i] * (fConst52 + (fConst53 * fZec1[i])))))) / fZec2[i]))));
		}
	}
#undef fVslider0
#undef fVslider1
#undef fVslider2
#undef fVslider3
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *inputX0, FAUSTFLOAT *outputX0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, inputX0, outputX0);
}

int Dsp::register_par(const ParamReg& reg)
{
	fVslider2_ = reg.registerVar("wah.Wah","","SA","",&fVslider2, 0.0, 0.0, 1.0, 0.01);
	fVslider1_ = reg.registerVar("wah.freq",N_("Alien Freq"),"SA",N_("LFO in Beats per Minute"),&fVslider1, 24.0, 24.0, 360.0, 1.0);
	static const value_pair fVslider3_values[] = {{"manual"},{"auto"},{"alien"},{0}};
	fVslider3_ = reg.registerSharedEnumVar("wah.mode","","SA","",fVslider3_values,&fVslider3, 0.0, 0.0, 2.0, 1.0);
	fVslider0_ = reg.registerVar("wah.wet_dry",N_("dry/wet"),"SA","",&fVslider0, 100.0, 0.0, 100.0, 1.0);
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

} // end namespace voxwah
