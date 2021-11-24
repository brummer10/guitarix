// generated from file '../src/faust/cabinet_impulse_former.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace cabinet_impulse_former {


Dsp::Dsp() {
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int l0 = 0; (l0 < 3); l0 = (l0 + 1)) fVec0[l0] = 0.0;
	for (int l1 = 0; (l1 < 3); l1 = (l1 + 1)) fRec1[l1] = 0.0;
	for (int l2 = 0; (l2 < 3); l2 = (l2 + 1)) fRec0[l2] = 0.0;
}

inline void Dsp::init(unsigned int sample_rate)
{
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = (15079.644737231007 / fConst0);
	fConst2 = (1.4142135623730951 * std::sin(fConst1));
	fConst3 = std::cos(fConst1);
	double fConst4 = (1884.9555921538758 / fConst0);
	fConst5 = (1.4142135623730951 * std::sin(fConst4));
	fConst6 = std::cos(fConst4);
	clear_state_f();
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fVslider0 (*fVslider0_)
#define fVslider1 (*fVslider1_)
#define fVslider2 (*fVslider2_)
	double fSlow0 = double(fVslider0);
	double fSlow1 = (fSlow0 * std::pow(10.0, (0.0 - (0.10000000000000001 * fSlow0))));
	double fSlow2 = std::pow(10.0, (0.025000000000000001 * double(fVslider1)));
	double fSlow3 = (fConst2 * std::sqrt(fSlow2));
	double fSlow4 = (fConst3 * (fSlow2 + -1.0));
	double fSlow5 = (1.0 / ((fSlow2 + fSlow3) + (1.0 - fSlow4)));
	double fSlow6 = (fSlow2 + (1.0 - (fSlow3 + fSlow4)));
	double fSlow7 = (fConst3 * (fSlow2 + 1.0));
	double fSlow8 = (2.0 * (fSlow2 + (-1.0 - fSlow7)));
	double fSlow9 = (fSlow2 + fSlow4);
	double fSlow10 = (fSlow2 * ((fSlow3 + fSlow9) + 1.0));
	double fSlow11 = std::pow(10.0, (0.025000000000000001 * double(fVslider2)));
	double fSlow12 = (fConst5 * std::sqrt(fSlow11));
	double fSlow13 = (fConst6 * (fSlow11 + -1.0));
	double fSlow14 = (fSlow11 + fSlow13);
	double fSlow15 = (1.0 / ((fSlow12 + fSlow14) + 1.0));
	double fSlow16 = (fConst6 * (fSlow11 + 1.0));
	double fSlow17 = (0.0 - (2.0 * ((fSlow11 + fSlow16) + -1.0)));
	double fSlow18 = (fSlow14 + (1.0 - fSlow12));
	double fSlow19 = ((fSlow11 + fSlow12) + (1.0 - fSlow13));
	double fSlow20 = (2.0 * (fSlow11 + (-1.0 - fSlow16)));
	double fSlow21 = (fSlow11 + (1.0 - (fSlow12 + fSlow13)));
	double fSlow22 = ((0.0 - (2.0 * fSlow2)) * ((fSlow2 + fSlow7) + -1.0));
	double fSlow23 = (fSlow2 * (fSlow9 + (1.0 - fSlow3)));
	for (int i0 = 0; (i0 < count); i0 = (i0 + 1)) {
		double fTemp0 = double(input0[i0]);
		fVec0[0] = fTemp0;
		fRec1[0] = (0.0 - (fSlow15 * (((fSlow17 * fRec1[1]) + (fSlow18 * fRec1[2])) - (fSlow11 * (((fSlow19 * fTemp0) + (fSlow20 * fVec0[1])) + (fSlow21 * fVec0[2]))))));
		fRec0[0] = (fSlow5 * ((0.0 - ((fSlow6 * fRec0[2]) + (fSlow8 * fRec0[1]))) + (((fSlow10 * fRec1[0]) + (fSlow22 * fRec1[1])) + (fSlow23 * fRec1[2]))));
		output0[i0] = FAUSTFLOAT((fSlow1 * fRec0[0]));
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
	fVslider0_ = reg.registerFloatVar("cab.Level",N_("Level"),"SA",N_("Level"),&fVslider0, 1.0, 0.5, 5.0, 0.5, 0);
	fVslider2_ = reg.registerFloatVar("cab.bass",N_("Bass"),"SA",N_("Bass"),&fVslider2, 0.0, -10.0, 10.0, 0.5, 0);
	fVslider1_ = reg.registerFloatVar("cab.treble",N_("Treble"),"SA",N_("Treble"),&fVslider1, 0.0, -10.0, 10.0, 0.5, 0);
	return 0;
}


} // end namespace cabinet_impulse_former
