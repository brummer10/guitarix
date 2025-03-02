// generated from file '../src/faust/low_high_cut.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace low_high_cut {


Dsp::Dsp() {
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) iVec0[l0] = 0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec4[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fVec1[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec3[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fRec2[l4] = 0.0;
	for (int l5 = 0; l5 < 3; l5 = l5 + 1) fRec1[l5] = 0.0;
	for (int l6 = 0; l6 < 3; l6 = l6 + 1) fRec0[l6] = 0.0;
}

inline void Dsp::init(unsigned int sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = std::tan(3138.4510609362032 / fConst0);
	fConst2 = 2.0 * (1.0 - 1.0 / mydsp_faustpower2_f(fConst1));
	fConst3 = 1.0 / fConst1;
	fConst4 = (fConst3 + -0.7653668647301795) / fConst1 + 1.0;
	fConst5 = 1.0 / ((fConst3 + 0.7653668647301795) / fConst1 + 1.0);
	fConst6 = (fConst3 + -1.8477590650225735) / fConst1 + 1.0;
	fConst7 = 1.0 / ((fConst3 + 1.8477590650225735) / fConst1 + 1.0);
	fConst8 = 72.25663103256524 / fConst0;
	fConst9 = 1.0 - fConst8;
	fConst10 = 1.0 / (fConst8 + 1.0);
	clear_state_f();
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		iVec0[0] = 1;
		fRec4[0] = 1e-20 * double(1 - iVec0[1]) - fRec4[1];
		double fTemp0 = double(input0[i0]) + fRec4[0];
		fVec1[0] = fTemp0;
		fRec3[0] = fConst10 * (fTemp0 - fVec1[1] + fConst9 * fRec3[1]);
		fRec2[0] = fConst10 * (fRec3[0] - fRec3[1] + fConst9 * fRec2[1]);
		fRec1[0] = fRec2[0] - fConst7 * (fConst6 * fRec1[2] + fConst2 * fRec1[1]);
		fRec0[0] = fConst7 * (fRec1[2] + fRec1[0] + 2.0 * fRec1[1]) - fConst5 * (fConst4 * fRec0[2] + fConst2 * fRec0[1]);
		output0[i0] = FAUSTFLOAT(fConst5 * (fRec0[2] + fRec0[0] + 2.0 * fRec0[1]));
		iVec0[1] = iVec0[0];
		fRec4[1] = fRec4[0];
		fVec1[1] = fVec1[0];
		fRec3[1] = fRec3[0];
		fRec2[1] = fRec2[0];
		fRec1[2] = fRec1[1];
		fRec1[1] = fRec1[0];
		fRec0[2] = fRec0[1];
		fRec0[1] = fRec0[0];
	}
}

int Dsp::register_par(const ParamReg& reg)
{
	return 0;
}


} // end namespace low_high_cut
