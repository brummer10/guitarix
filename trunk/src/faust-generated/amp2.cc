// generated from file '../src/faust/amp2.dsp' by dsp2cc:
#include "valve.h"
namespace amp2 {
static FAUSTFLOAT 	fslider0;
static double 	fRec0[2];
static FAUSTFLOAT 	fcheckbox0;
static FAUSTFLOAT 	fslider1;
static double 	fRec1[2];
static double 	fConst0;
static double 	fConst1;
static double 	fConst2;
static double 	fConst3;
static double 	fConst4;
static double 	fConst5;
static double 	fConst6;
static double 	fRec4[2];
static double 	fRec3[3];
static double 	fConst7;
static double 	fConst8;
static double 	fRec2[2];
static FAUSTFLOAT 	fcheckbox1;
static double 	fVec0[2];
static FAUSTFLOAT 	fslider2;
static double 	fRec5[2];
static double 	fConst9;
static double 	fConst10;
static double 	fConst11;
static double 	fConst12;
static double 	fRec8[2];
static double 	fConst13;
static double 	fConst14;
static double 	fConst15;
static double 	fConst16;
static double 	fRec9[2];
static double 	fRec7[3];
static double 	fRec6[2];
static FAUSTFLOAT 	fcheckbox2;
static int	fSamplingFreq;

static void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	fConst0 = (1.0 / tan((97.38937226128358 / fSamplingFreq)));
	fConst1 = (1 + fConst0);
	fConst2 = (0 - ((1 - fConst0) / fConst1));
	fConst3 = (1.0 / tan((270.1769682087222 / fSamplingFreq)));
	fConst4 = (1 + fConst3);
	fConst5 = (0 - ((1 - fConst3) / fConst4));
	fConst6 = (0.027 / fConst4);
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<3; i++) fRec3[i] = 0;
	fConst7 = (0 - fConst0);
	fConst8 = (0.025 / fConst1);
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	fConst9 = (1.0 / tan((20517.741620594938 / fSamplingFreq)));
	fConst10 = (1 + fConst9);
	fConst11 = (0 - ((1 - fConst9) / fConst10));
	fConst12 = (1.0 / fConst10);
	for (int i=0; i<2; i++) fRec8[i] = 0;
	fConst13 = (1.0 / tan((414.6902302738527 / fSamplingFreq)));
	fConst14 = (1 + fConst13);
	fConst15 = (0 - ((1 - fConst13) / fConst14));
	fConst16 = (0.015 / fConst14);
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<3; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = (0.0010000000000000009 * pow(10,(0.05 * fslider0)));
	int 	iSlow1 = int(fcheckbox0);
	double 	fSlow2 = (0.0010000000000000009 * pow(10,(0.05 * fslider1)));
	int 	iSlow3 = int(fcheckbox1);
	double 	fSlow4 = (0.0010000000000000009 * pow(10,(0.05 * fslider2)));
	int 	iSlow5 = int(fcheckbox2);
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fRec0[0] = (fSlow0 + (0.999 * fRec0[1]));
		double fTemp1 = ((iSlow1)?(fTemp0 * fRec0[0]):fTemp0);
		fRec1[0] = (fSlow2 + (0.999 * fRec1[1]));
		fRec4[0] = ((fConst6 * (fRec3[1] + fRec3[2])) + (fConst5 * fRec4[1]));
		fRec3[0] = (Ftube(TUBE_TABLE_12AX7_68k, ((fTemp1 + fRec4[0]) - 1.581656)) - 191.42014814814814);
		fRec2[0] = ((fConst8 * ((fConst7 * fRec3[1]) + (fConst0 * fRec3[0]))) + (fConst2 * fRec2[1]));
		double fTemp2 = ((iSlow3)?(fRec2[0] * fRec1[0]):fTemp1);
		fVec0[0] = fTemp2;
		fRec5[0] = (fSlow4 + (0.999 * fRec5[1]));
		fRec8[0] = ((fConst12 * (fVec0[0] + fVec0[1])) + (fConst11 * fRec8[1]));
		fRec9[0] = ((fConst16 * (fRec7[1] + fRec7[2])) + (fConst15 * fRec9[1]));
		fRec7[0] = (Ftube(TUBE_TABLE_12AX7_250k, ((fRec9[0] + fRec8[0]) - 1.204285)) - 169.71433333333334);
		fRec6[0] = ((fConst8 * ((fConst7 * fRec7[1]) + (fConst0 * fRec7[0]))) + (fConst2 * fRec6[1]));
		output0[i] = (FAUSTFLOAT)((iSlow5)?(fRec6[0] * fRec5[0]):fVec0[0]);
		// post processing
		fRec6[1] = fRec6[0];
		fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
		fRec9[1] = fRec9[0];
		fRec8[1] = fRec8[0];
		fRec5[1] = fRec5[0];
		fVec0[1] = fVec0[0];
		fRec2[1] = fRec2[0];
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("amp2.stage1.ON","","B","",&fcheckbox1, 0.0, 0.0, 1.0, 1.0);
	registerVar("amp2.preamp.ON","","B","",&fcheckbox0, 0.0, 0.0, 1.0, 1.0);
	registerVar("amp2.stage2.ON","","B","",&fcheckbox2, 0.0, 0.0, 1.0, 1.0);
	registerVar("amp2.stage2.gain2","","S","",&fslider2, 6.0, -1e+01, 2e+01, 0.1);
	registerVar("amp2.stage1.gain1","","S","",&fslider1, 6.0, -1e+01, 2e+01, 0.1);
	registerVar("amp2.preamp.Pregain","","S","",&fslider0, 3e+01, -1e+01, 8e+01, 0.1);
	registerInit("amp2", init);
}

} // end namespace amp2
