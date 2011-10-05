// generated from file '../src/faust/gxamp17.dsp' by dsp2cc:
// Code generated with Faust 0.9.30 (http://faust.grame.fr)

#include "valve.h"
namespace gxamp17 {
FAUSTFLOAT 	fslider0;
FAUSTFLOAT	*fslider0_;
#define fslider0 (*fslider0_)
static double 	fRec0[2];
static double 	fConst0;
static double 	fConst1;
static double 	fConst2;
static double 	fConst3;
static double 	fConst4;
static double 	fConst5;
FAUSTFLOAT 	fslider1;
FAUSTFLOAT	*fslider1_;
#define fslider1 (*fslider1_)
static double 	fRec8[2];
static double 	fConst6;
static double 	fConst7;
static double 	fConst8;
static double 	fConst9;
static double 	fConst10;
static double 	fConst11;
static double 	fConst12;
static double 	fConst13;
static double 	fConst14;
static double 	fConst15;
static double 	fConst16;
static double 	fConst17;
static double 	fConst18;
static double 	fConst19;
static double 	fConst20;
static double 	fConst21;
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
static double 	fRec22[2];
static int 	IOTA;
static double 	fVec0[65536];
static int 	iConst36;
static double 	fRec21[2];
static double 	fConst37;
static double 	fRec20[2];
FAUSTFLOAT 	fslider2;
FAUSTFLOAT	*fslider2_;
#define fslider2 (*fslider2_)
static double 	fRec23[2];
static double 	fRec19[3];
static double 	fVec1[2];
static double 	fConst38;
static double 	fConst39;
static double 	fRec18[2];
static double 	fConst40;
static double 	fRec17[2];
static double 	fRec16[3];
static double 	fVec2[2];
static double 	fConst41;
static double 	fConst42;
static double 	fRec15[2];
static double 	fRec14[3];
static double 	fConst43;
static double 	fRec13[3];
FAUSTFLOAT 	fslider3;
FAUSTFLOAT	*fslider3_;
#define fslider3 (*fslider3_)
static double 	fConst44;
static double 	fConst45;
static double 	fConst46;
static double 	fConst47;
static double 	fRec27[2];
static double 	fRec26[3];
static double 	fVec3[2];
static double 	fConst48;
static double 	fConst49;
static double 	fRec25[2];
static double 	fRec24[3];
static double 	fConst50;
static double 	fConst51;
static double 	fConst52;
static double 	fConst53;
static double 	fRec31[2];
static double 	fRec30[3];
static double 	fConst54;
static double 	fRec29[3];
static double 	fRec28[3];
static double 	fRec33[2];
static double 	fRec32[3];
static double 	fVec4[2];
static double 	fConst55;
static double 	fRec12[2];
static double 	fConst56;
static double 	fConst57;
static double 	fConst58;
static double 	fConst59;
static double 	fRec34[2];
static double 	fRec11[3];
static double 	fConst60;
static double 	fRec10[2];
static double 	fConst61;
static double 	fConst62;
static double 	fConst63;
static double 	fConst64;
static double 	fRec37[2];
static double 	fRec36[3];
static double 	fRec35[2];
static double 	fRec9[2];
static double 	fVec5[2];
static double 	fRec7[2];
static double 	fRec38[2];
static double 	fRec6[3];
static double 	fRec5[2];
static double 	fConst65;
static double 	fConst66;
static double 	fConst67;
static double 	fConst68;
static double 	fRec41[2];
static double 	fRec40[3];
static double 	fRec39[2];
static double 	fRec4[2];
static double 	fRec3[2];
static double 	fRec42[2];
static double 	fRec2[3];
static double 	fRec1[2];
static int	fSamplingFreq;

static void clear_state(PluginDef* = 0)
{
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<65536; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<3; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<3; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<3; i++) fRec14[i] = 0;
	for (int i=0; i<3; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec27[i] = 0;
	for (int i=0; i<3; i++) fRec26[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec25[i] = 0;
	for (int i=0; i<3; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fRec31[i] = 0;
	for (int i=0; i<3; i++) fRec30[i] = 0;
	for (int i=0; i<3; i++) fRec29[i] = 0;
	for (int i=0; i<3; i++) fRec28[i] = 0;
	for (int i=0; i<2; i++) fRec33[i] = 0;
	for (int i=0; i<3; i++) fRec32[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec34[i] = 0;
	for (int i=0; i<3; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec37[i] = 0;
	for (int i=0; i<3; i++) fRec36[i] = 0;
	for (int i=0; i<2; i++) fRec35[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec38[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec41[i] = 0;
	for (int i=0; i<3; i++) fRec40[i] = 0;
	for (int i=0; i<2; i++) fRec39[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec42[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
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
	fConst6 = tan((942.4777960769379 / fSamplingFreq));
	fConst7 = (1.0 / faustpower<2>(fConst6));
	fConst8 = (2 * (1 - fConst7));
	fConst9 = (1.0 / fConst6);
	fConst10 = (1 + ((fConst9 - 1.0) / fConst6));
	fConst11 = (1.0 / (1 + ((1.0 + fConst9) / fConst6)));
	fConst12 = tan((3769.9111843077517 / fSamplingFreq));
	fConst13 = (1.0 / faustpower<2>(fConst12));
	fConst14 = (2 * (1 - fConst13));
	fConst15 = (1.0 / fConst12);
	fConst16 = (1 + ((fConst15 - 1.0000000000000004) / fConst12));
	fConst17 = (1 + ((fConst15 + 1.0000000000000004) / fConst12));
	fConst18 = (1.0 / fConst17);
	fConst19 = (1 + fConst15);
	fConst20 = (0 - ((1 - fConst15) / fConst19));
	fConst21 = tan((10053.096491487338 / fSamplingFreq));
	fConst22 = (1.0 / faustpower<2>(fConst21));
	fConst23 = (2 * (1 - fConst22));
	fConst24 = (1.0 / fConst21);
	fConst25 = (1 + ((fConst24 - 1.0000000000000004) / fConst21));
	fConst26 = (1 + ((1.0000000000000004 + fConst24) / fConst21));
	fConst27 = (1.0 / fConst26);
	fConst28 = (1 + fConst24);
	fConst29 = (0 - ((1 - fConst24) / fConst28));
	fConst30 = tan((47123.8898038469 / fSamplingFreq));
	fConst31 = (2 * (1 - (1.0 / faustpower<2>(fConst30))));
	fConst32 = (1.0 / fConst30);
	fConst33 = (1 + ((fConst32 - 1.414213562373095) / fConst30));
	fConst34 = (1 + ((1.414213562373095 + fConst32) / fConst30));
	fConst35 = (1.0 / fConst34);
	IOTA = 0;
	iConst36 = int((int((0.1111111111111111 * fSamplingFreq)) & 65535));
	fConst37 = (0.009000000000000008 / fSamplingFreq);
	fConst38 = (0 - fConst0);
	fConst39 = (1.0 / (fConst1 * fConst34));
	fConst40 = (1.0 / fConst28);
	fConst41 = (0 - fConst15);
	fConst42 = (1.0 / (fConst19 * fConst26));
	fConst43 = (2 * (0 - fConst13));
	fConst44 = (1 + ((fConst9 - 1.0000000000000004) / fConst6));
	fConst45 = (1.0 / (1 + ((fConst9 + 1.0000000000000004) / fConst6)));
	fConst46 = (1 + fConst9);
	fConst47 = (0 - ((1 - fConst9) / fConst46));
	fConst48 = (0 - fConst9);
	fConst49 = (1.0 / (fConst46 * fConst17));
	fConst50 = (2 * (0 - fConst7));
	fConst51 = (1 + ((fConst15 - 1.0) / fConst12));
	fConst52 = (1.0 / (1 + ((1.0 + fConst15) / fConst12)));
	fConst53 = (0 - fConst24);
	fConst54 = (2 * (0 - fConst22));
	fConst55 = (1.0 / fConst4);
	fConst56 = (1.0 / tan((270.1769682087222 / fSamplingFreq)));
	fConst57 = (1 + fConst56);
	fConst58 = (0 - ((1 - fConst56) / fConst57));
	fConst59 = (0.027 / fConst57);
	fConst60 = (0.025 / fConst1);
	fConst61 = (1.0 / tan((414.6902302738527 / fSamplingFreq)));
	fConst62 = (1 + fConst61);
	fConst63 = (0 - ((1 - fConst61) / fConst62));
	fConst64 = (0.015 / fConst62);
	fConst65 = (1.0 / tan((609.4689747964198 / fSamplingFreq)));
	fConst66 = (1 + fConst65);
	fConst67 = (0 - ((1 - fConst65) / fConst66));
	fConst68 = (0.0082 / fConst66);
	clear_state();
}

static void compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = (0.0010000000000000009 * pow(10,(0.05 * fslider0)));
	double 	fSlow1 = (0.0010000000000000009 * pow(10,(0.05 * fslider1)));
	double 	fSlow2 = (1.000000000000001e-05 * fslider2);
	double 	fSlow3 = fslider3;
	double 	fSlow4 = pow(1e+01,(1.2 * fSlow3));
	double 	fSlow5 = pow(1e+01,(2 * fSlow3));
	double 	fSlow6 = (fConst45 * fSlow5);
	double 	fSlow7 = pow(1e+01,(0.8 * fSlow3));
	double 	fSlow8 = (fConst45 * pow(1e+01,(0.9 * fSlow3)));
	double 	fSlow9 = (2 * (fSlow3 - 0.5));
	double 	fSlow10 = (1 - max(0, (0 - fSlow9)));
	double 	fSlow11 = (0.024937655860349125 * (1 - max(0, fSlow9)));
	double 	fSlow12 = (1.25 * fSlow3);
	for (int i=0; i<count; i++) {
		fRec0[0] = (fSlow0 + (0.999 * fRec0[1]));
		fRec8[0] = (fSlow1 + (0.999 * fRec8[1]));
		double fTemp0 = (fConst8 * fRec13[1]);
		double fTemp1 = (double)input0[i];
		double fTemp2 = fabs(fTemp1);
		fRec22[0] = ((9.999999999998899e-05 * fTemp2) + (0.9999 * fRec22[1]));
		double fTemp3 = max(fRec22[0], fTemp2);
		fVec0[IOTA&65535] = fTemp3;
		fRec21[0] = ((fVec0[IOTA&65535] + fRec21[1]) - fVec0[(IOTA-iConst36)&65535]);
		fRec20[0] = ((fConst37 * fRec21[0]) + (0.999 * fRec20[1]));
		double fTemp4 = max(-1, min(-0.01, (fVec0[IOTA&65535] - (1.0 + (1.02 * fRec20[0])))));
		double fTemp5 = (0 - fTemp4);
		double fTemp6 = (40.1 * fTemp5);
		double fTemp7 = max(-600, fTemp6);
		double fTemp8 = (0 - fTemp7);
		double fTemp9 = (fTemp1 - fTemp4);
		double fTemp10 = (40.1 * fTemp9);
		double fTemp11 = max(-600, fTemp10);
		double fTemp12 = (0 - fTemp11);
		double fTemp13 = (((int((fabs(fTemp10) > 0.0001)))?((int((fTemp11 < -50)))?(exp(fTemp11) * fTemp12):(fTemp11 / (1 - exp(fTemp12)))):(1 + (fTemp9 * (20.05 + (134.00083333333336 * fTemp9))))) - ((int((fabs(fTemp6) > 0.0001)))?((int((fTemp7 < -50)))?(exp(fTemp7) * fTemp8):(fTemp7 / (1 - exp(fTemp8)))):(1 + (fTemp5 * (20.05 + (134.00083333333336 * fTemp5))))));
		fRec23[0] = (fSlow2 + (0.999 * fRec23[1]));
		double fTemp14 = (0.024937655860349125 * (fRec23[0] * fTemp13));
		fRec19[0] = (fTemp14 - (fConst35 * ((fConst33 * fRec19[2]) + (fConst31 * fRec19[1]))));
		double fTemp15 = (fRec19[2] + (fRec19[0] + (2 * fRec19[1])));
		fVec1[0] = fTemp15;
		fRec18[0] = ((fConst39 * ((fConst38 * fVec1[1]) + (fConst0 * fVec1[0]))) + (fConst2 * fRec18[1]));
		fRec17[0] = ((fConst40 * (fRec18[0] + fRec18[1])) + (fConst29 * fRec17[1]));
		fRec16[0] = (fRec17[0] - (fConst27 * ((fConst25 * fRec16[2]) + (fConst23 * fRec16[1]))));
		double fTemp16 = (fRec16[2] + (fRec16[0] + (2 * fRec16[1])));
		fVec2[0] = fTemp16;
		fRec15[0] = ((fConst42 * ((fConst41 * fVec2[1]) + (fConst15 * fVec2[0]))) + (fConst20 * fRec15[1]));
		fRec14[0] = (fRec15[0] - (fConst18 * ((fConst16 * fRec14[2]) + (fConst14 * fRec14[1]))));
		fRec13[0] = ((fConst18 * (((fConst13 * fRec14[0]) + (fConst43 * fRec14[1])) + (fConst13 * fRec14[2]))) - (fConst11 * ((fConst10 * fRec13[2]) + fTemp0)));
		double fTemp17 = max(-1, min(1, (fSlow4 * (fRec13[2] + (fConst11 * (fTemp0 + (fConst10 * fRec13[0])))))));
		fRec27[0] = ((fConst42 * (fVec2[0] + fVec2[1])) + (fConst20 * fRec27[1]));
		fRec26[0] = (fRec27[0] - (fConst18 * ((fConst16 * fRec26[2]) + (fConst14 * fRec26[1]))));
		double fTemp18 = (fRec26[2] + (fRec26[0] + (2 * fRec26[1])));
		fVec3[0] = fTemp18;
		fRec25[0] = ((fConst49 * ((fConst48 * fVec3[1]) + (fConst9 * fVec3[0]))) + (fConst47 * fRec25[1]));
		fRec24[0] = (fRec25[0] - (fConst45 * ((fConst44 * fRec24[2]) + (fConst8 * fRec24[1]))));
		double fTemp19 = max(-1, min(1, (fSlow6 * (((fConst7 * fRec24[0]) + (fConst50 * fRec24[1])) + (fConst7 * fRec24[2])))));
		double fTemp20 = (fConst8 * fRec28[1]);
		double fTemp21 = (fConst14 * fRec29[1]);
		fRec31[0] = ((fConst40 * ((fConst53 * fRec18[1]) + (fConst24 * fRec18[0]))) + (fConst29 * fRec31[1]));
		fRec30[0] = (fRec31[0] - (fConst27 * ((fConst25 * fRec30[2]) + (fConst23 * fRec30[1]))));
		fRec29[0] = ((fConst27 * (((fConst22 * fRec30[0]) + (fConst54 * fRec30[1])) + (fConst22 * fRec30[2]))) - (fConst52 * ((fConst51 * fRec29[2]) + fTemp21)));
		fRec28[0] = ((fRec29[2] + (fConst52 * (fTemp21 + (fConst51 * fRec29[0])))) - (fConst11 * ((fConst10 * fRec28[2]) + fTemp20)));
		double fTemp22 = max(-1, min(1, (fSlow7 * (fRec28[2] + (fConst11 * (fTemp20 + (fConst10 * fRec28[0])))))));
		fRec33[0] = ((fConst49 * (fVec3[0] + fVec3[1])) + (fConst47 * fRec33[1]));
		fRec32[0] = (fRec33[0] - (fConst45 * ((fConst44 * fRec32[2]) + (fConst8 * fRec32[1]))));
		double fTemp23 = max(-1, min(1, (fSlow8 * (fRec32[2] + (fRec32[0] + (2 * fRec32[1]))))));
		double fTemp24 = ((1.2589412 * (fTemp23 * (1 - (0.3333333333333333 * faustpower<2>(fTemp23))))) + (1.584893192 * ((fTemp22 * (1 - (0.3333333333333333 * faustpower<2>(fTemp22)))) + ((fTemp19 * (1 - (0.3333333333333333 * faustpower<2>(fTemp19)))) + (0.8413951417869425 * (fTemp17 * (1 - (0.3333333333333333 * faustpower<2>(fTemp17)))))))));
		fVec4[0] = fTemp24;
		fRec12[0] = ((fConst55 * (fVec4[0] + fVec4[1])) + (fConst5 * fRec12[1]));
		fRec34[0] = ((fConst59 * (fRec11[1] + fRec11[2])) + (fConst58 * fRec34[1]));
		double fTemp25 = max(-1, min(1, (fSlow5 * max(-0.7, min(0.7, fTemp14)))));
		double fTemp26 = (1 - fRec23[0]);
		fRec11[0] = (Ftube(TUBE_TABLE_12AT7_68k, (((fTemp13 * ((fTemp26 * (0.024937655860349125 + (fSlow12 * ((0.0997506234413965 - (0.0997506234413965 * fabs((0.024937655860349125 * (fTemp26 * fTemp13))))) - 0.024937655860349125)))) + (fSlow11 * fRec23[0]))) + ((0.5 * (fTemp25 * (1 - (0.3333333333333333 * faustpower<2>(fTemp25))))) + (fRec34[0] + (fSlow10 * fRec12[0])))) - 2.617753)) - 153.04618518518518);
		fRec10[0] = ((fConst60 * ((fConst38 * fRec11[1]) + (fConst0 * fRec11[0]))) + (fConst2 * fRec10[1]));
		fRec37[0] = ((fConst64 * (fRec36[1] + fRec36[2])) + (fConst63 * fRec37[1]));
		fRec36[0] = (Ftube(TUBE_TABLE_12AT7_250k, ((fRec37[0] + fRec9[1]) - 1.887332)) - 124.17786666666666);
		fRec35[0] = ((fConst60 * ((fConst38 * fRec36[1]) + (fConst0 * fRec36[0]))) + (fConst2 * fRec35[1]));
		fRec9[0] = ((0.6 * fRec35[0]) - fRec10[0]);
		double fTemp27 = (fRec9[0] * fRec8[0]);
		fVec5[0] = fTemp27;
		fRec7[0] = ((fConst55 * (fVec5[0] + fVec5[1])) + (fConst5 * fRec7[1]));
		fRec38[0] = ((fConst64 * (fRec6[1] + fRec6[2])) + (fConst63 * fRec38[1]));
		fRec6[0] = (Ftube(TUBE_TABLE_12AT7_250k, ((fRec38[0] + fRec7[0]) - 1.887332)) - 124.17786666666666);
		fRec5[0] = ((fConst60 * ((fConst38 * fRec6[1]) + (fConst0 * fRec6[0]))) + (fConst2 * fRec5[1]));
		fRec41[0] = ((fConst68 * (fRec40[1] + fRec40[2])) + (fConst67 * fRec41[1]));
		fRec40[0] = (Ftube(TUBE_TABLE_12AT7_250k, ((fRec41[0] + fRec4[1]) - 1.256962)) - 96.7119512195122);
		fRec39[0] = ((fConst60 * ((fConst38 * fRec40[1]) + (fConst0 * fRec40[0]))) + (fConst2 * fRec39[1]));
		fRec4[0] = ((0.6 * fRec39[0]) + fRec5[0]);
		fRec3[0] = ((fConst55 * (fRec4[0] + fRec4[1])) + (fConst5 * fRec3[1]));
		fRec42[0] = ((fConst68 * (fRec2[1] + fRec2[2])) + (fConst67 * fRec42[1]));
		fRec2[0] = (Ftube(TUBE_TABLE_12AT7_250k, ((fRec42[0] + fRec3[0]) - 1.256962)) - 96.7119512195122);
		fRec1[0] = ((fConst60 * ((fConst38 * fRec2[1]) + (fConst0 * fRec2[0]))) + (fConst2 * fRec1[1]));
		output0[i] = (FAUSTFLOAT)(fRec1[0] * fRec0[0]);
		// post processing
		fRec1[1] = fRec1[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec42[1] = fRec42[0];
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fRec39[1] = fRec39[0];
		fRec40[2] = fRec40[1]; fRec40[1] = fRec40[0];
		fRec41[1] = fRec41[0];
		fRec5[1] = fRec5[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec38[1] = fRec38[0];
		fRec7[1] = fRec7[0];
		fVec5[1] = fVec5[0];
		fRec9[1] = fRec9[0];
		fRec35[1] = fRec35[0];
		fRec36[2] = fRec36[1]; fRec36[1] = fRec36[0];
		fRec37[1] = fRec37[0];
		fRec10[1] = fRec10[0];
		fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
		fRec34[1] = fRec34[0];
		fRec12[1] = fRec12[0];
		fVec4[1] = fVec4[0];
		fRec32[2] = fRec32[1]; fRec32[1] = fRec32[0];
		fRec33[1] = fRec33[0];
		fRec28[2] = fRec28[1]; fRec28[1] = fRec28[0];
		fRec29[2] = fRec29[1]; fRec29[1] = fRec29[0];
		fRec30[2] = fRec30[1]; fRec30[1] = fRec30[0];
		fRec31[1] = fRec31[0];
		fRec24[2] = fRec24[1]; fRec24[1] = fRec24[0];
		fRec25[1] = fRec25[0];
		fVec3[1] = fVec3[0];
		fRec26[2] = fRec26[1]; fRec26[1] = fRec26[0];
		fRec27[1] = fRec27[0];
		fRec13[2] = fRec13[1]; fRec13[1] = fRec13[0];
		fRec14[2] = fRec14[1]; fRec14[1] = fRec14[0];
		fRec15[1] = fRec15[0];
		fVec2[1] = fVec2[0];
		fRec16[2] = fRec16[1]; fRec16[1] = fRec16[0];
		fRec17[1] = fRec17[0];
		fRec18[1] = fRec18[0];
		fVec1[1] = fVec1[0];
		fRec19[2] = fRec19[1]; fRec19[1] = fRec19[0];
		fRec23[1] = fRec23[0];
		fRec20[1] = fRec20[0];
		fRec21[1] = fRec21[0];
		IOTA = IOTA+1;
		fRec22[1] = fRec22[0];
		fRec8[1] = fRec8[0];
		fRec0[1] = fRec0[0];
	}
}

static int register_params(const ParamReg& reg)
{
#undef fslider3
	fslider3_ = reg.registerVar("gxdistortion.drive","","SA","",&fslider3, 0.35, 0.0, 1.0, 0.01);
#undef fslider2
	fslider2_ = reg.registerVar("gxdistortion.wet_dry","","SA","",&fslider2, 1e+02, 0.0, 1e+02, 1.0);
#undef fslider1
	fslider1_ = reg.registerVar("amp2.stage1.Pregain","","SA","",&fslider1, -6.0, -2e+01, 2e+01, 0.1);
#undef fslider0
	fslider0_ = reg.registerVar("amp2.stage2.gain1","","SA","",&fslider0, -6.0, -2e+01, 2e+01, 0.1);
	return 0;
}

PluginDef plugin = {
    PLUGINDEF_VERSION,
    0,   // flags
    "12AT7 feedback",  // id
    N_("12AT7 feedback"),  // name
    0,  // groups
    compute,  // mono_audio
    0,  // stereo_audio
    init,  // set_samplerate
    0,  // activate plugin
    register_params,
    0,   // load_ui
    clear_state,  // clear_state
};

} // end namespace gxamp17
