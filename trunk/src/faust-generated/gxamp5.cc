// generated from file '../src/faust/gxamp5.dsp' by dsp2cc:
// Code generated with Faust 0.9.30 (http://faust.grame.fr)

#include "valve.h"
namespace gxamp5 {
static double 	fConst0;
static double 	fConst1;
static double 	fConst2;
static double 	fConst3;
static double 	fConst4;
static double 	fConst5;
static double 	fConst6;
static double 	fRec2[2];
FAUSTFLOAT 	fslider0;
FAUSTFLOAT	*fslider0_;
#define fslider0 (*fslider0_)
static double 	fRec3[2];
FAUSTFLOAT 	fslider1;
FAUSTFLOAT	*fslider1_;
#define fslider1 (*fslider1_)
static double 	fRec5[2];
FAUSTFLOAT 	fslider2;
FAUSTFLOAT	*fslider2_;
#define fslider2 (*fslider2_)
static double 	fRec13[2];
static double 	fConst7;
static double 	fConst8;
static double 	fConst9;
static double 	fConst10;
static double 	fRec14[2];
static double 	fRec12[3];
static double 	fConst11;
static double 	fConst12;
static double 	fRec11[2];
static double 	fConst13;
static double 	fRec10[2];
static double 	fConst14;
static double 	fConst15;
static double 	fConst16;
static double 	fConst17;
static double 	fRec15[2];
static double 	fRec9[3];
static double 	fRec8[2];
static double 	fConst18;
static double 	fConst19;
static double 	fConst20;
static double 	fConst21;
static double 	fRec16[2];
static double 	fRec7[3];
static double 	fRec6[2];
FAUSTFLOAT 	fslider3;
FAUSTFLOAT	*fslider3_;
#define fslider3 (*fslider3_)
static double 	fConst22;
static double 	fConst23;
static double 	fConst24;
static double 	fConst25;
static double 	fConst26;
static double 	fConst27;
static double 	fConst28;
static double 	fConst29;
static double 	fConst30;
static double 	fConst31;
static double 	fConst32;
static double 	fConst33;
static double 	fConst34;
static double 	fConst35;
static double 	fConst36;
static double 	fConst37;
static double 	fConst38;
static double 	fConst39;
static double 	fConst40;
static double 	fConst41;
static double 	fConst42;
static double 	fConst43;
static double 	fConst44;
static double 	fConst45;
static double 	fConst46;
static double 	fConst47;
static double 	fConst48;
static double 	fConst49;
static double 	fConst50;
static double 	fConst51;
static double 	fRec24[3];
static double 	fVec0[2];
static double 	fConst52;
static double 	fRec23[2];
static double 	fConst53;
static double 	fRec22[2];
static double 	fRec21[3];
static double 	fVec1[2];
static double 	fConst54;
static double 	fConst55;
static double 	fRec20[2];
static double 	fRec19[3];
static double 	fConst56;
static double 	fRec18[3];
static double 	fConst57;
static double 	fConst58;
static double 	fConst59;
static double 	fConst60;
static double 	fRec28[2];
static double 	fRec27[3];
static double 	fVec2[2];
static double 	fConst61;
static double 	fConst62;
static double 	fRec26[2];
static double 	fRec25[3];
static double 	fConst63;
static double 	fConst64;
static double 	fConst65;
static double 	fConst66;
static double 	fRec32[2];
static double 	fRec31[3];
static double 	fConst67;
static double 	fRec30[3];
static double 	fRec29[3];
static double 	fRec34[2];
static double 	fRec33[3];
static double 	fVec3[2];
static double 	fRec17[2];
static double 	fVec4[2];
static double 	fRec4[2];
static double 	fRec1[3];
static double 	fRec0[2];
static double 	fRec37[2];
static double 	fRec36[3];
static double 	fRec35[2];
static int	fSamplingFreq;

static void clear_state(PluginDef* = 0)
{
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<3; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<3; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<3; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<3; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<3; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<3; i++) fRec19[i] = 0;
	for (int i=0; i<3; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fRec28[i] = 0;
	for (int i=0; i<3; i++) fRec27[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<3; i++) fRec25[i] = 0;
	for (int i=0; i<2; i++) fRec32[i] = 0;
	for (int i=0; i<3; i++) fRec31[i] = 0;
	for (int i=0; i<3; i++) fRec30[i] = 0;
	for (int i=0; i<3; i++) fRec29[i] = 0;
	for (int i=0; i<2; i++) fRec34[i] = 0;
	for (int i=0; i<3; i++) fRec33[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<3; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec37[i] = 0;
	for (int i=0; i<3; i++) fRec36[i] = 0;
	for (int i=0; i<2; i++) fRec35[i] = 0;
}

static void init(int samplingFreq, PluginDef* = 0)
{
	fSamplingFreq = samplingFreq;
	fConst0 = (1.0 / tan((97.38937226128358 / fSamplingFreq)));
	fConst1 = (1 + fConst0);
	fConst2 = (0 - ((1 - fConst0) / fConst1));
	fConst3 = (1.0 / tan((20517.741620594938 / fSamplingFreq)));
	fConst4 = (1 + fConst3);
	fConst5 = (0 - ((1 - fConst3) / fConst4));
	fConst6 = (0.0082 / fConst4);
	fConst7 = (1.0 / tan((270.1769682087222 / fSamplingFreq)));
	fConst8 = (1 + fConst7);
	fConst9 = (0 - ((1 - fConst7) / fConst8));
	fConst10 = (0.027 / fConst8);
	fConst11 = (0 - fConst0);
	fConst12 = (0.025 / fConst1);
	fConst13 = (1.0 / fConst4);
	fConst14 = (1.0 / tan((414.6902302738527 / fSamplingFreq)));
	fConst15 = (1 + fConst14);
	fConst16 = (0 - ((1 - fConst14) / fConst15));
	fConst17 = (0.015 / fConst15);
	fConst18 = (1.0 / tan((609.4689747964198 / fSamplingFreq)));
	fConst19 = (1 + fConst18);
	fConst20 = (0 - ((1 - fConst18) / fConst19));
	fConst21 = (0.0082 / fConst19);
	fConst22 = tan((942.4777960769379 / fSamplingFreq));
	fConst23 = (1.0 / faustpower<2>(fConst22));
	fConst24 = (2 * (1 - fConst23));
	fConst25 = (1.0 / fConst22);
	fConst26 = (1 + ((fConst25 - 1.0) / fConst22));
	fConst27 = (1.0 / (1 + ((1.0 + fConst25) / fConst22)));
	fConst28 = tan((3769.9111843077517 / fSamplingFreq));
	fConst29 = (1.0 / faustpower<2>(fConst28));
	fConst30 = (2 * (1 - fConst29));
	fConst31 = (1.0 / fConst28);
	fConst32 = (1 + ((fConst31 - 1.0000000000000004) / fConst28));
	fConst33 = (1 + ((fConst31 + 1.0000000000000004) / fConst28));
	fConst34 = (1.0 / fConst33);
	fConst35 = (1 + fConst31);
	fConst36 = (0 - ((1 - fConst31) / fConst35));
	fConst37 = tan((10053.096491487338 / fSamplingFreq));
	fConst38 = (1.0 / faustpower<2>(fConst37));
	fConst39 = (2 * (1 - fConst38));
	fConst40 = (1.0 / fConst37);
	fConst41 = (1 + ((fConst40 - 1.0000000000000004) / fConst37));
	fConst42 = (1 + ((1.0000000000000004 + fConst40) / fConst37));
	fConst43 = (1.0 / fConst42);
	fConst44 = (1 + fConst40);
	fConst45 = (0 - ((1 - fConst40) / fConst44));
	fConst46 = tan((47123.8898038469 / fSamplingFreq));
	fConst47 = (2 * (1 - (1.0 / faustpower<2>(fConst46))));
	fConst48 = (1.0 / fConst46);
	fConst49 = (1 + ((fConst48 - 1.414213562373095) / fConst46));
	fConst50 = (1 + ((1.414213562373095 + fConst48) / fConst46));
	fConst51 = (1.0 / fConst50);
	fConst52 = (1.0 / (fConst1 * fConst50));
	fConst53 = (1.0 / fConst44);
	fConst54 = (0 - fConst31);
	fConst55 = (1.0 / (fConst35 * fConst42));
	fConst56 = (2 * (0 - fConst29));
	fConst57 = (1 + ((fConst25 - 1.0000000000000004) / fConst22));
	fConst58 = (1.0 / (1 + ((fConst25 + 1.0000000000000004) / fConst22)));
	fConst59 = (1 + fConst25);
	fConst60 = (0 - ((1 - fConst25) / fConst59));
	fConst61 = (0 - fConst25);
	fConst62 = (1.0 / (fConst59 * fConst33));
	fConst63 = (2 * (0 - fConst23));
	fConst64 = (1 + ((fConst31 - 1.0) / fConst28));
	fConst65 = (1.0 / (1 + ((1.0 + fConst31) / fConst28)));
	fConst66 = (0 - fConst40);
	fConst67 = (2 * (0 - fConst38));
	clear_state();
}

static void compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = (0.0010000000000000009 * pow(10,(0.05 * fslider0)));
	double 	fSlow1 = (1.000000000000001e-05 * fslider1);
	double 	fSlow2 = (0.0010000000000000009 * pow(10,(0.05 * fslider2)));
	double 	fSlow3 = fslider3;
	double 	fSlow4 = (1.25 * fSlow3);
	double 	fSlow5 = (2 * (fSlow3 - 0.5));
	double 	fSlow6 = (1 - max(0, fSlow5));
	double 	fSlow7 = pow(1e+01,(1.2 * fSlow3));
	double 	fSlow8 = (fConst58 * pow(1e+01,(2 * fSlow3)));
	double 	fSlow9 = pow(1e+01,(0.8 * fSlow3));
	double 	fSlow10 = (fConst58 * pow(1e+01,(0.9 * fSlow3)));
	double 	fSlow11 = (1 - max(0, (0 - fSlow5)));
	for (int i=0; i<count; i++) {
		fRec2[0] = ((fConst6 * (fRec1[1] + fRec1[2])) + (fConst5 * fRec2[1]));
		fRec3[0] = (fSlow0 + (0.999 * fRec3[1]));
		fRec5[0] = (fSlow1 + (0.999 * fRec5[1]));
		double fTemp0 = (1 - fRec5[0]);
		fRec13[0] = (fSlow2 + (0.999 * fRec13[1]));
		fRec14[0] = ((fConst10 * (fRec12[1] + fRec12[2])) + (fConst9 * fRec14[1]));
		fRec12[0] = (Ftube(TUBE_TABLE_12AX7_68k, ((fRec14[0] + ((double)input0[i] * fRec13[0])) - 1.581656)) - 191.42014814814814);
		fRec11[0] = ((fConst12 * ((fConst11 * fRec12[1]) + (fConst0 * fRec12[0]))) + (fConst2 * fRec11[1]));
		fRec10[0] = ((fConst13 * (fRec11[0] + fRec11[1])) + (fConst5 * fRec10[1]));
		fRec15[0] = ((fConst17 * (fRec9[1] + fRec9[2])) + (fConst16 * fRec15[1]));
		fRec9[0] = (Ftube(TUBE_TABLE_12AX7_250k, ((fRec15[0] + fRec10[0]) - 1.204285)) - 169.71433333333334);
		fRec8[0] = ((fConst12 * ((fConst11 * fRec9[1]) + (fConst0 * fRec9[0]))) + (fConst2 * fRec8[1]));
		fRec16[0] = ((fConst21 * (fRec7[1] + fRec7[2])) + (fConst20 * fRec16[1]));
		fRec7[0] = (Ftube(TUBE_TABLE_12AX7_250k, ((fRec16[0] + fRec8[0]) - 0.840703)) - 147.47524390243905);
		fRec6[0] = ((fConst12 * ((fConst11 * fRec7[1]) + (fConst0 * fRec7[0]))) + (fConst2 * fRec6[1]));
		double fTemp1 = (fConst24 * fRec18[1]);
		fRec24[0] = ((fRec6[0] * fRec5[0]) - (fConst51 * ((fConst49 * fRec24[2]) + (fConst47 * fRec24[1]))));
		double fTemp2 = (fRec24[2] + (fRec24[0] + (2 * fRec24[1])));
		fVec0[0] = fTemp2;
		fRec23[0] = ((fConst52 * ((fConst11 * fVec0[1]) + (fConst0 * fVec0[0]))) + (fConst2 * fRec23[1]));
		fRec22[0] = ((fConst53 * (fRec23[0] + fRec23[1])) + (fConst45 * fRec22[1]));
		fRec21[0] = (fRec22[0] - (fConst43 * ((fConst41 * fRec21[2]) + (fConst39 * fRec21[1]))));
		double fTemp3 = (fRec21[2] + (fRec21[0] + (2 * fRec21[1])));
		fVec1[0] = fTemp3;
		fRec20[0] = ((fConst55 * ((fConst54 * fVec1[1]) + (fConst31 * fVec1[0]))) + (fConst36 * fRec20[1]));
		fRec19[0] = (fRec20[0] - (fConst34 * ((fConst32 * fRec19[2]) + (fConst30 * fRec19[1]))));
		fRec18[0] = ((fConst34 * (((fConst29 * fRec19[0]) + (fConst56 * fRec19[1])) + (fConst29 * fRec19[2]))) - (fConst27 * ((fConst26 * fRec18[2]) + fTemp1)));
		double fTemp4 = max(-1, min(1, (fSlow7 * (fRec18[2] + (fConst27 * (fTemp1 + (fConst26 * fRec18[0])))))));
		fRec28[0] = ((fConst55 * (fVec1[0] + fVec1[1])) + (fConst36 * fRec28[1]));
		fRec27[0] = (fRec28[0] - (fConst34 * ((fConst32 * fRec27[2]) + (fConst30 * fRec27[1]))));
		double fTemp5 = (fRec27[2] + (fRec27[0] + (2 * fRec27[1])));
		fVec2[0] = fTemp5;
		fRec26[0] = ((fConst62 * ((fConst61 * fVec2[1]) + (fConst25 * fVec2[0]))) + (fConst60 * fRec26[1]));
		fRec25[0] = (fRec26[0] - (fConst58 * ((fConst57 * fRec25[2]) + (fConst24 * fRec25[1]))));
		double fTemp6 = max(-1, min(1, (fSlow8 * (((fConst23 * fRec25[0]) + (fConst63 * fRec25[1])) + (fConst23 * fRec25[2])))));
		double fTemp7 = (fConst24 * fRec29[1]);
		double fTemp8 = (fConst30 * fRec30[1]);
		fRec32[0] = ((fConst53 * ((fConst66 * fRec23[1]) + (fConst40 * fRec23[0]))) + (fConst45 * fRec32[1]));
		fRec31[0] = (fRec32[0] - (fConst43 * ((fConst41 * fRec31[2]) + (fConst39 * fRec31[1]))));
		fRec30[0] = ((fConst43 * (((fConst38 * fRec31[0]) + (fConst67 * fRec31[1])) + (fConst38 * fRec31[2]))) - (fConst65 * ((fConst64 * fRec30[2]) + fTemp8)));
		fRec29[0] = ((fRec30[2] + (fConst65 * (fTemp8 + (fConst64 * fRec30[0])))) - (fConst27 * ((fConst26 * fRec29[2]) + fTemp7)));
		double fTemp9 = max(-1, min(1, (fSlow9 * (fRec29[2] + (fConst27 * (fTemp7 + (fConst26 * fRec29[0])))))));
		fRec34[0] = ((fConst62 * (fVec2[0] + fVec2[1])) + (fConst60 * fRec34[1]));
		fRec33[0] = (fRec34[0] - (fConst58 * ((fConst57 * fRec33[2]) + (fConst24 * fRec33[1]))));
		double fTemp10 = max(-1, min(1, (fSlow10 * (fRec33[2] + (fRec33[0] + (2 * fRec33[1]))))));
		double fTemp11 = ((1.2589412 * (fTemp10 * (1 - (0.3333333333333333 * faustpower<2>(fTemp10))))) + (1.584893192 * ((fTemp9 * (1 - (0.3333333333333333 * faustpower<2>(fTemp9)))) + ((fTemp6 * (1 - (0.3333333333333333 * faustpower<2>(fTemp6)))) + (0.8413951417869425 * (fTemp4 * (1 - (0.3333333333333333 * faustpower<2>(fTemp4)))))))));
		fVec3[0] = fTemp11;
		fRec17[0] = ((fConst13 * (fVec3[0] + fVec3[1])) + (fConst5 * fRec17[1]));
		double fTemp12 = ((fSlow11 * fRec17[0]) + (fRec6[0] * ((fSlow6 * fRec5[0]) + (fTemp0 * (1 + (fSlow4 * ((4 - (4 * fabs((fRec6[0] * fTemp0)))) - 1)))))));
		fVec4[0] = fTemp12;
		fRec4[0] = ((fConst13 * (fVec4[0] + fVec4[1])) + (fConst5 * fRec4[1]));
		double fTemp13 = (fRec4[0] * fRec3[0]);
		fRec1[0] = (Ftube(TUBE_TABLE_6V6_68k, ((fTemp13 + fRec2[0]) - 1.13074)) - 112.10487804878048);
		fRec0[0] = ((fConst12 * ((fConst11 * fRec1[1]) + (fConst0 * fRec1[0]))) + (fConst2 * fRec0[1]));
		fRec37[0] = ((fConst6 * (fRec36[1] + fRec36[2])) + (fConst5 * fRec37[1]));
		fRec36[0] = (Ftube(TUBE_TABLE_6V6_250k, ((fRec37[0] + fTemp13) - 1.130462)) - 112.13878048780487);
		fRec35[0] = ((fConst12 * ((fConst11 * fRec36[1]) + (fConst0 * fRec36[0]))) + (fConst2 * fRec35[1]));
		output0[i] = (FAUSTFLOAT)(fRec35[0] + fRec0[0]);
		// post processing
		fRec35[1] = fRec35[0];
		fRec36[2] = fRec36[1]; fRec36[1] = fRec36[0];
		fRec37[1] = fRec37[0];
		fRec0[1] = fRec0[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec4[1] = fRec4[0];
		fVec4[1] = fVec4[0];
		fRec17[1] = fRec17[0];
		fVec3[1] = fVec3[0];
		fRec33[2] = fRec33[1]; fRec33[1] = fRec33[0];
		fRec34[1] = fRec34[0];
		fRec29[2] = fRec29[1]; fRec29[1] = fRec29[0];
		fRec30[2] = fRec30[1]; fRec30[1] = fRec30[0];
		fRec31[2] = fRec31[1]; fRec31[1] = fRec31[0];
		fRec32[1] = fRec32[0];
		fRec25[2] = fRec25[1]; fRec25[1] = fRec25[0];
		fRec26[1] = fRec26[0];
		fVec2[1] = fVec2[0];
		fRec27[2] = fRec27[1]; fRec27[1] = fRec27[0];
		fRec28[1] = fRec28[0];
		fRec18[2] = fRec18[1]; fRec18[1] = fRec18[0];
		fRec19[2] = fRec19[1]; fRec19[1] = fRec19[0];
		fRec20[1] = fRec20[0];
		fVec1[1] = fVec1[0];
		fRec21[2] = fRec21[1]; fRec21[1] = fRec21[0];
		fRec22[1] = fRec22[0];
		fRec23[1] = fRec23[0];
		fVec0[1] = fVec0[0];
		fRec24[2] = fRec24[1]; fRec24[1] = fRec24[0];
		fRec6[1] = fRec6[0];
		fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
		fRec16[1] = fRec16[0];
		fRec8[1] = fRec8[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec15[1] = fRec15[0];
		fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		fRec12[2] = fRec12[1]; fRec12[1] = fRec12[0];
		fRec14[1] = fRec14[0];
		fRec13[1] = fRec13[0];
		fRec5[1] = fRec5[0];
		fRec3[1] = fRec3[0];
		fRec2[1] = fRec2[0];
	}
}

static int register_params(const ParamReg& reg)
{
#undef fslider3
	fslider3_ = reg.registerVar("gxdistortion.drive","","SA","",&fslider3, 0.35, 0.0, 1.0, 0.01);
#undef fslider2
	fslider2_ = reg.registerVar("amp2.stage1.Pregain","","SA","",&fslider2, -6.0, -2e+01, 2e+01, 0.1);
#undef fslider1
	fslider1_ = reg.registerVar("gxdistortion.wet_dry","","SA","",&fslider1, 1e+02, 0.0, 1e+02, 1.0);
#undef fslider0
	fslider0_ = reg.registerVar("amp2.stage2.gain1","","SA","",&fslider0, -6.0, -2e+01, 2e+01, 0.1);
	return 0;
}

PluginDef plugin = {
    PLUGINDEF_VERSION,
    0,   // flags
    "pre 12ax7/ master 6V6",  // id
    N_("pre 12ax7/ master 6V6"),  // name
    0,  // groups
    compute,  // mono_audio
    0,  // stereo_audio
    init,  // set_samplerate
    0,  // activate plugin
    register_params,
    0,   // load_ui
    clear_state,  // clear_state
};

} // end namespace gxamp5
