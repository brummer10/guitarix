// generated from file '../src/faust/cabinet_impulse_former.dsp' by dsp2cc:
// Code generated with Faust 0.9.58 (http://faust.grame.fr)


namespace cabinet_impulse_former {


Dsp::Dsp() {
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int i=0; i<3; i++) fVec0[i] = 0;
	for (int i=0; i<3; i++) fRec1[i] = 0;
	for (int i=0; i<3; i++) fRec0[i] = 0;
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (15079.644737231007 / double(iConst0));
	fConst2 = cos(fConst1);
	fConst3 = (1.4142135623730951 * sin(fConst1));
	fConst4 = (1884.9555921538758 / double(iConst0));
	fConst5 = cos(fConst4);
	fConst6 = (1.4142135623730951 * sin(fConst4));
	clear_state_f();
}

void always_inline Dsp::compute(int count, float *input0, float *output0)
{
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
#define fslider2 (*fslider2_)
	double 	fSlow0 = pow(10,(0.025 * fslider0));
	double 	fSlow1 = (1 + fSlow0);
	double 	fSlow2 = (fConst2 * fSlow1);
	double 	fSlow3 = (2 * (0 - ((1 + fSlow2) - fSlow0)));
	double 	fSlow4 = (fConst2 * (fSlow0 - 1));
	double 	fSlow5 = (fConst3 * sqrt(fSlow0));
	double 	fSlow6 = (fSlow1 - (fSlow5 + fSlow4));
	double 	fSlow7 = pow(10,(0.025 * fslider1));
	double 	fSlow8 = (1 + fSlow7);
	double 	fSlow9 = (fConst5 * fSlow8);
	double 	fSlow10 = (0 - (2 * ((fSlow7 + fSlow9) - 1)));
	double 	fSlow11 = (fConst6 * sqrt(fSlow7));
	double 	fSlow12 = (fConst5 * (fSlow7 - 1));
	double 	fSlow13 = ((1 + (fSlow7 + fSlow12)) - fSlow11);
	double 	fSlow14 = (fSlow8 - (fSlow11 + fSlow12));
	double 	fSlow15 = (2 * (0 - ((1 + fSlow9) - fSlow7)));
	double 	fSlow16 = (fSlow7 + fSlow11);
	double 	fSlow17 = ((1 + fSlow16) - fSlow12);
	double 	fSlow18 = (1.0 / (1 + (fSlow12 + fSlow16)));
	double 	fSlow19 = (fSlow0 * ((1 + (fSlow0 + fSlow4)) - fSlow5));
	double 	fSlow20 = (fSlow0 + fSlow5);
	double 	fSlow21 = (fSlow0 * (1 + (fSlow4 + fSlow20)));
	double 	fSlow22 = (((fSlow0 + fSlow2) - 1) * (0 - (2 * fSlow0)));
	double 	fSlow23 = (1.0 / ((1 + fSlow20) - fSlow4));
	double 	fSlow24 = fslider2;
	double 	fSlow25 = (fSlow24 * pow(10,(0 - (0.1 * fSlow24))));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fVec0[0] = fTemp0;
		fRec1[0] = (fSlow18 * ((fSlow7 * (((fSlow17 * fVec0[0]) + (fSlow15 * fVec0[1])) + (fSlow14 * fVec0[2]))) - ((fSlow13 * fRec1[2]) + (fSlow10 * fRec1[1]))));
		fRec0[0] = (fSlow23 * ((((fSlow22 * fRec1[1]) + (fSlow21 * fRec1[0])) + (fSlow19 * fRec1[2])) + (0 - ((fSlow6 * fRec0[2]) + (fSlow3 * fRec0[1])))));
		output0[i] = (FAUSTFLOAT)(fSlow25 * fRec0[0]);
		// post processing
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fVec0[2] = fVec0[1]; fVec0[1] = fVec0[0];
	}
#undef fslider0
#undef fslider1
#undef fslider2
}

int Dsp::register_par(const ParamReg& reg)
{
	fslider2_ = reg.registerVar("cab.Level","","SA","",&fslider2, 1.0, 0.5, 5.0, 0.5);
	fslider1_ = reg.registerVar("cab.bass",N_("bass"),"SA","",&fslider1, 0.0, -1e+01, 1e+01, 0.5);
	fslider0_ = reg.registerVar("cab.treble",N_("treble"),"SA","",&fslider0, 0.0, -1e+01, 1e+01, 0.5);
	return 0;
}


} // end namespace cabinet_impulse_former
