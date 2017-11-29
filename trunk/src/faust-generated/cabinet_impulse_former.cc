// generated from file '../src/faust/cabinet_impulse_former.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)


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
	fConst0 = min(1.92e+05, max(1.0, (double)fSamplingFreq));
	fConst1 = (15079.644737231007 / fConst0);
	fConst2 = cos(fConst1);
	fConst3 = (1.4142135623730951 * sin(fConst1));
	fConst4 = (1884.9555921538758 / fConst0);
	fConst5 = (1.4142135623730951 * sin(fConst4));
	fConst6 = cos(fConst4);
	clear_state_f();
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
#define fslider2 (*fslider2_)
	double 	fSlow0 = pow(10,(0.025 * double(fslider0)));
	double 	fSlow1 = (1 + fSlow0);
	double 	fSlow2 = (fConst2 * fSlow1);
	double 	fSlow3 = (2 * (0 - ((1 + fSlow2) - fSlow0)));
	double 	fSlow4 = (fConst3 * sqrt(fSlow0));
	double 	fSlow5 = (fConst2 * (fSlow0 - 1));
	double 	fSlow6 = (fSlow1 - (fSlow5 + fSlow4));
	double 	fSlow7 = pow(10,(0.025 * double(fslider1)));
	double 	fSlow8 = (fConst5 * sqrt(fSlow7));
	double 	fSlow9 = (fConst6 * (fSlow7 - 1));
	double 	fSlow10 = (1 + fSlow7);
	double 	fSlow11 = (fSlow10 - (fSlow9 + fSlow8));
	double 	fSlow12 = (fConst6 * fSlow10);
	double 	fSlow13 = (2 * (0 - ((1 + fSlow12) - fSlow7)));
	double 	fSlow14 = ((1 + (fSlow7 + fSlow8)) - fSlow9);
	double 	fSlow15 = (fSlow7 + fSlow9);
	double 	fSlow16 = ((1 + fSlow15) - fSlow8);
	double 	fSlow17 = (0 - (2 * ((fSlow7 + fSlow12) - 1)));
	double 	fSlow18 = (1.0 / (1 + (fSlow8 + fSlow15)));
	double 	fSlow19 = (fSlow0 + fSlow5);
	double 	fSlow20 = ((1 + fSlow19) - fSlow4);
	double 	fSlow21 = (1 + (fSlow19 + fSlow4));
	double 	fSlow22 = ((0 - (2 * fSlow0)) * ((fSlow0 + fSlow2) - 1));
	double 	fSlow23 = (1.0 / ((1 + (fSlow0 + fSlow4)) - fSlow5));
	double 	fSlow24 = double(fslider2);
	double 	fSlow25 = (fSlow24 * pow(10,(0 - (0.1 * fSlow24))));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fVec0[0] = fTemp0;
		fRec1[0] = (fSlow18 * (0 - (((fSlow17 * fRec1[1]) + (fSlow16 * fRec1[2])) - (fSlow7 * (((fSlow14 * fVec0[0]) + (fSlow13 * fVec0[1])) + (fSlow11 * fVec0[2]))))));
		fRec0[0] = (fSlow23 * (((fSlow22 * fRec1[1]) + (fSlow0 * ((fSlow21 * fRec1[0]) + (fSlow20 * fRec1[2])))) - ((fSlow6 * fRec0[2]) + (fSlow3 * fRec0[1]))));
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
	fslider2_ = reg.registerVar("cab.Level",N_("Level"),"SA",N_("Level"),&fslider2, 1.0, 0.5, 5.0, 0.5);
	fslider1_ = reg.registerVar("cab.bass",N_("Bass"),"SA",N_("Bass"),&fslider1, 0.0, -1e+01, 1e+01, 0.5);
	fslider0_ = reg.registerVar("cab.treble",N_("Treble"),"SA",N_("Treble"),&fslider0, 0.0, -1e+01, 1e+01, 0.5);
	return 0;
}


} // end namespace cabinet_impulse_former
