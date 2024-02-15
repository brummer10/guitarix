// generated from file '../src/faust/preamp_impulse_former.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace preamp_impulse_former {


Dsp::Dsp() {
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int l0 = 0; l0 < 3; l0 = l0 + 1) fVec0[l0] = 0.0;
	for (int l1 = 0; l1 < 3; l1 = l1 + 1) fRec1[l1] = 0.0;
	for (int l2 = 0; l2 < 3; l2 = l2 + 1) fRec0[l2] = 0.0;
}

inline void Dsp::init(unsigned int sample_rate)
{
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = 1884.9555921538758 / fConst0;
	fConst2 = 1.4142135623730951 * std::sin(fConst1);
	fConst3 = std::cos(fConst1);
	double fConst4 = 15079.644737231007 / fConst0;
	fConst5 = 1.4142135623730951 * std::sin(fConst4);
	fConst6 = std::cos(fConst4);
	clear_state_f();
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fVslider0 (*fVslider0_)
#define fVslider1 (*fVslider1_)
#define fVslider2 (*fVslider2_)
	double fSlow0 = std::pow(1e+01, 0.025 * double(fVslider0));
	double fSlow1 = fConst2 * std::sqrt(fSlow0);
	double fSlow2 = fConst3 * (fSlow0 + -1.0);
	double fSlow3 = fSlow0 + (1.0 - (fSlow2 + fSlow1));
	double fSlow4 = fConst3 * (fSlow0 + 1.0);
	double fSlow5 = 2.0 * (fSlow0 + (-1.0 - fSlow4));
	double fSlow6 = fSlow0 + fSlow1 + (1.0 - fSlow2);
	double fSlow7 = fSlow0 + fSlow2;
	double fSlow8 = fSlow7 + (1.0 - fSlow1);
	double fSlow9 = 2.0 * (fSlow0 + fSlow4 + -1.0);
	double fSlow10 = 1.0 / (fSlow7 + fSlow1 + 1.0);
	double fSlow11 = std::pow(1e+01, 0.025 * double(fVslider1));
	double fSlow12 = fConst5 * std::sqrt(fSlow11);
	double fSlow13 = fConst6 * (fSlow11 + -1.0);
	double fSlow14 = fSlow11 + fSlow13;
	double fSlow15 = fSlow14 + (1.0 - fSlow12);
	double fSlow16 = fConst6 * (fSlow11 + 1.0);
	double fSlow17 = 2.0 * (fSlow11 + fSlow16 + -1.0);
	double fSlow18 = fSlow12 + fSlow14 + 1.0;
	double fSlow19 = 2.0 * (fSlow11 + (-1.0 - fSlow16));
	double fSlow20 = fSlow11 + (1.0 - (fSlow13 + fSlow12));
	double fSlow21 = 1.0 / (fSlow11 + fSlow12 + (1.0 - fSlow13));
	double fSlow22 = double(fVslider2);
	double fSlow23 = fSlow22 * std::pow(1e+01, -0.1 * fSlow22);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		double fTemp0 = double(input0[i0]);
		fVec0[0] = fTemp0;
		fRec1[0] = fSlow10 * (fSlow9 * fRec1[1] - fSlow8 * fRec1[2] + fSlow0 * (fSlow6 * fTemp0 + fSlow5 * fVec0[1] + fSlow3 * fVec0[2]));
		fRec0[0] = -(fSlow21 * (fSlow20 * fRec0[2] + fSlow19 * fRec0[1] - fSlow11 * (fSlow18 * fRec1[0] - fSlow17 * fRec1[1] + fSlow15 * fRec1[2])));
		output0[i0] = FAUSTFLOAT(fSlow23 * fRec0[0]);
		fVec0[2] = fVec0[1];
		fVec0[1] = fVec0[0];
		fRec1[2] = fRec1[1];
		fRec1[1] = fRec1[0];
		fRec0[2] = fRec0[1];
		fRec0[1] = fRec0[0];
	}
#undef fVslider0
#undef fVslider1
#undef fVslider2
}

int Dsp::register_par(const ParamReg& reg)
{
	fVslider2_ = reg.registerFloatVar("pre.Level",N_("Level"),"SA",N_("Level"),&fVslider2, 1.0, 0.1, 2.1, 0.1, 0);
	fVslider0_ = reg.registerFloatVar("pre.bass",N_("Bass"),"SA",N_("Bass"),&fVslider0, 0.0, -1e+01, 1e+01, 0.5, 0);
	fVslider1_ = reg.registerFloatVar("pre.treble",N_("Treble"),"SA",N_("Treble"),&fVslider1, 0.0, -1e+01, 1e+01, 0.5, 0);
	return 0;
}


} // end namespace preamp_impulse_former
