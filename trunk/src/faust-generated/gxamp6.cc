// generated from file '../src/faust/gxamp6.dsp' by dsp2cc:
#include "valve.h"
namespace gxamp6 {
static double 	fConst0;
static double 	fConst1;
static double 	fConst2;
static double 	fConst3;
static double 	fConst4;
static double 	fConst5;
static double 	fConst6;
static double 	fConst7;
static double 	fConst8;
static double 	fConst9;
static double 	fConst10;
static double 	fConst11;
static double 	fConst12;
static double 	fConst13;
static double 	fConst14;
static double 	fVec0[2];
static double 	fConst15;
static double 	fRec12[2];
static double 	fRec11[2];
static double 	fRec10[3];
static double 	fRec9[3];
static FAUSTFLOAT&	fslider0 = get_alias("amp2.stage1.Pregain");
static double 	fRec13[2];
static double 	fConst16;
static double 	fConst17;
static double 	fConst18;
static double 	fConst19;
static double 	fRec14[2];
static double 	fRec8[3];
static double 	fConst20;
static double 	fConst21;
static double 	fRec7[2];
static double 	fConst22;
static double 	fConst23;
static double 	fConst24;
static double 	fConst25;
static double 	fRec17[2];
static double 	fRec16[3];
static double 	fRec15[2];
static double 	fRec6[2];
static double 	fConst26;
static double 	fRec5[2];
static double 	fRec18[2];
static double 	fRec4[3];
static double 	fRec3[2];
static double 	fConst27;
static double 	fConst28;
static double 	fConst29;
static double 	fConst30;
static double 	fRec21[2];
static double 	fRec20[3];
static double 	fRec19[2];
static double 	fRec2[2];
static double 	fRec22[2];
static double 	fRec1[3];
static double 	fRec0[2];
static int	fSamplingFreq;

static void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = (1.0 / tan((97.38937226128358 / fSamplingFreq)));
	fConst1 = (1 + fConst0);
	fConst2 = (0 - ((1 - fConst0) / fConst1));
	fConst3 = (1.0 / tan((20517.741620594938 / fSamplingFreq)));
	fConst4 = (1 + fConst3);
	fConst5 = (0 - ((1 - fConst3) / fConst4));
	fConst6 = tan((37699.11184307752 / fSamplingFreq));
	fConst7 = (2 * (1 - (1.0 / faustpower<2>(fConst6))));
	fConst8 = (1.0 / fConst6);
	fConst9 = (1 + ((fConst8 - 0.7653668647301795) / fConst6));
	fConst10 = (1.0 / (1 + ((0.7653668647301795 + fConst8) / fConst6)));
	fConst11 = (1 + ((fConst8 - 1.8477590650225735) / fConst6));
	fConst12 = (1.0 / (1 + ((fConst8 + 1.8477590650225735) / fConst6)));
	fConst13 = (973.8937226128359 / fSamplingFreq);
	fConst14 = (1 - fConst13);
	for (int i=0; i<2; i++) fVec0[i] = 0;
	fConst15 = (1.0 / (1 + fConst13));
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<3; i++) fRec10[i] = 0;
	for (int i=0; i<3; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	fConst16 = (1.0 / tan((270.1769682087222 / fSamplingFreq)));
	fConst17 = (1 + fConst16);
	fConst18 = (0 - ((1 - fConst16) / fConst17));
	fConst19 = (0.027 / fConst17);
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<3; i++) fRec8[i] = 0;
	fConst20 = (0 - fConst0);
	fConst21 = (0.05 / fConst1);
	for (int i=0; i<2; i++) fRec7[i] = 0;
	fConst22 = (1.0 / tan((414.6902302738527 / fSamplingFreq)));
	fConst23 = (1 + fConst22);
	fConst24 = (0 - ((1 - fConst22) / fConst23));
	fConst25 = (0.015 / fConst23);
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<3; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	fConst26 = (1.0 / fConst4);
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<3; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	fConst27 = (1.0 / tan((609.4689747964198 / fSamplingFreq)));
	fConst28 = (1 + fConst27);
	fConst29 = (0 - ((1 - fConst27) / fConst28));
	fConst30 = (0.0082 / fConst28);
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<3; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<3; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = (0.0010000000000000009 * pow(10,(0.05 * fslider0)));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fVec0[0] = fTemp0;
		fRec12[0] = (fConst15 * ((fVec0[0] - fVec0[1]) + (fConst14 * fRec12[1])));
		fRec11[0] = (fConst15 * ((fRec12[0] - fRec12[1]) + (fConst14 * fRec11[1])));
		fRec10[0] = (fRec11[0] - (fConst12 * ((fConst11 * fRec10[2]) + (fConst7 * fRec10[1]))));
		fRec9[0] = ((fConst12 * (fRec10[2] + (fRec10[0] + (2 * fRec10[1])))) - (fConst10 * ((fConst9 * fRec9[2]) + (fConst7 * fRec9[1]))));
		fRec13[0] = (fSlow0 + (0.999 * fRec13[1]));
		fRec14[0] = ((fConst19 * (fRec8[1] + fRec8[2])) + (fConst18 * fRec14[1]));
		fRec8[0] = (Ftube(TUBE_TABLE_6DJ8_68k, ((fRec14[0] + (fConst10 * (fRec13[0] * (fRec9[2] + (fRec9[0] + (2 * fRec9[1])))))) - 1.863946)) - 60.96496296296296);
		fRec7[0] = ((fConst21 * ((fConst20 * fRec8[1]) + (fConst0 * fRec8[0]))) + (fConst2 * fRec7[1]));
		fRec17[0] = ((fConst25 * (fRec16[1] + fRec16[2])) + (fConst24 * fRec17[1]));
		fRec16[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec17[0] + fRec6[1]) - 1.271609)) - 45.22606666666667);
		fRec15[0] = ((fConst21 * ((fConst20 * fRec16[1]) + (fConst0 * fRec16[0]))) + (fConst2 * fRec15[1]));
		fRec6[0] = ((0.6 * fRec15[0]) + fRec7[0]);
		fRec5[0] = ((fConst26 * (fRec6[0] + fRec6[1])) + (fConst5 * fRec5[1]));
		fRec18[0] = ((fConst25 * (fRec4[1] + fRec4[2])) + (fConst24 * fRec18[1]));
		fRec4[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec18[0] + fRec5[0]) - 1.271609)) - 45.22606666666667);
		fRec3[0] = ((fConst21 * ((fConst20 * fRec4[1]) + (fConst0 * fRec4[0]))) + (fConst2 * fRec3[1]));
		fRec21[0] = ((fConst30 * (fRec20[1] + fRec20[2])) + (fConst29 * fRec21[1]));
		fRec20[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec21[0] + fRec2[1]) - 0.797043)) - 32.799634146341475);
		fRec19[0] = ((fConst21 * ((fConst20 * fRec20[1]) + (fConst0 * fRec20[0]))) + (fConst2 * fRec19[1]));
		fRec2[0] = ((0.6 * fRec19[0]) + fRec3[0]);
		fRec22[0] = ((fConst30 * (fRec1[1] + fRec1[2])) + (fConst29 * fRec22[1]));
		fRec1[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec22[0] + fRec2[0]) - 0.797043)) - 32.799634146341475);
		fRec0[0] = ((fConst21 * ((fConst20 * fRec1[1]) + (fConst0 * fRec1[0]))) + (fConst2 * fRec0[1]));
		output0[i] = (FAUSTFLOAT)fRec0[0];
		// post processing
		fRec0[1] = fRec0[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec22[1] = fRec22[0];
		fRec2[1] = fRec2[0];
		fRec19[1] = fRec19[0];
		fRec20[2] = fRec20[1]; fRec20[1] = fRec20[0];
		fRec21[1] = fRec21[0];
		fRec3[1] = fRec3[0];
		fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
		fRec18[1] = fRec18[0];
		fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		fRec15[1] = fRec15[0];
		fRec16[2] = fRec16[1]; fRec16[1] = fRec16[0];
		fRec17[1] = fRec17[0];
		fRec7[1] = fRec7[0];
		fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
		fRec14[1] = fRec14[0];
		fRec13[1] = fRec13[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		fRec12[1] = fRec12[0];
		fVec0[1] = fVec0[0];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerInit("amp2", init);
}

} // end namespace gxamp6
