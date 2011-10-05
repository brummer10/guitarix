// generated from file '../src/faust/gxamp10.dsp' by dsp2cc:
// Code generated with Faust 0.9.30 (http://faust.grame.fr)

#include "valve.h"
namespace gxamp10 {
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
static double 	fConst6;
static double 	fRec3[2];
static double 	fConst7;
static double 	fConst8;
static double 	fConst9;
FAUSTFLOAT 	fslider1;
FAUSTFLOAT	*fslider1_;
#define fslider1 (*fslider1_)
static double 	fRec8[2];
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
static double 	fConst36;
static double 	fConst37;
static double 	fConst38;
static double 	fConst39;
FAUSTFLOAT 	fslider2;
FAUSTFLOAT	*fslider2_;
#define fslider2 (*fslider2_)
static double 	fRec19[2];
static double 	fRec18[3];
static double 	fVec0[2];
static double 	fConst40;
static double 	fConst41;
static double 	fRec17[2];
static double 	fConst42;
static double 	fRec16[2];
static double 	fRec15[3];
static double 	fVec1[2];
static double 	fConst43;
static double 	fConst44;
static double 	fRec14[2];
static double 	fRec13[3];
static double 	fConst45;
static double 	fRec12[3];
FAUSTFLOAT 	fslider3;
FAUSTFLOAT	*fslider3_;
#define fslider3 (*fslider3_)
static double 	fConst46;
static double 	fConst47;
static double 	fConst48;
static double 	fConst49;
static double 	fRec23[2];
static double 	fRec22[3];
static double 	fVec2[2];
static double 	fConst50;
static double 	fConst51;
static double 	fRec21[2];
static double 	fRec20[3];
static double 	fConst52;
static double 	fConst53;
static double 	fConst54;
static double 	fConst55;
static double 	fRec27[2];
static double 	fRec26[3];
static double 	fConst56;
static double 	fRec25[3];
static double 	fRec24[3];
static double 	fRec29[2];
static double 	fRec28[3];
static double 	fVec3[2];
static double 	fConst57;
static double 	fRec11[2];
static double 	fConst58;
static double 	fConst59;
static double 	fConst60;
static double 	fConst61;
static double 	fRec30[2];
static double 	fRec10[3];
static double 	fConst62;
static double 	fRec9[2];
static double 	fVec4[2];
static double 	fRec7[2];
static double 	fConst63;
static double 	fConst64;
static double 	fConst65;
static double 	fConst66;
static double 	fRec31[2];
static double 	fRec6[3];
static double 	fRec5[2];
static double 	fVec5[2];
static double 	fRec4[2];
static double 	fRec2[3];
static double 	fRec1[2];
static double 	fRec34[2];
static double 	fRec33[3];
static double 	fRec32[2];
static int	fSamplingFreq;

static void clear_state(PluginDef* = 0)
{
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<3; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<3; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<3; i++) fRec13[i] = 0;
	for (int i=0; i<3; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<3; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<3; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec27[i] = 0;
	for (int i=0; i<3; i++) fRec26[i] = 0;
	for (int i=0; i<3; i++) fRec25[i] = 0;
	for (int i=0; i<3; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fRec29[i] = 0;
	for (int i=0; i<3; i++) fRec28[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec30[i] = 0;
	for (int i=0; i<3; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec31[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec34[i] = 0;
	for (int i=0; i<3; i++) fRec33[i] = 0;
	for (int i=0; i<2; i++) fRec32[i] = 0;
}

static void init(int samplingFreq, PluginDef* = 0)
{
	fSamplingFreq = samplingFreq;
	fConst0 = (1.0 / tan((97.38937226128358 / fSamplingFreq)));
	fConst1 = (1 + fConst0);
	fConst2 = (0 - ((1 - fConst0) / fConst1));
	fConst3 = (1.0 / tan((609.4689747964198 / fSamplingFreq)));
	fConst4 = (1 + fConst3);
	fConst5 = (0 - ((1 - fConst3) / fConst4));
	fConst6 = (0.0082 / fConst4);
	fConst7 = (1.0 / tan((20517.741620594938 / fSamplingFreq)));
	fConst8 = (1 + fConst7);
	fConst9 = (0 - ((1 - fConst7) / fConst8));
	fConst10 = tan((942.4777960769379 / fSamplingFreq));
	fConst11 = (1.0 / faustpower<2>(fConst10));
	fConst12 = (2 * (1 - fConst11));
	fConst13 = (1.0 / fConst10);
	fConst14 = (1 + ((fConst13 - 1.0) / fConst10));
	fConst15 = (1.0 / (1 + ((1.0 + fConst13) / fConst10)));
	fConst16 = tan((3769.9111843077517 / fSamplingFreq));
	fConst17 = (1.0 / faustpower<2>(fConst16));
	fConst18 = (2 * (1 - fConst17));
	fConst19 = (1.0 / fConst16);
	fConst20 = (1 + ((fConst19 - 1.0000000000000004) / fConst16));
	fConst21 = (1 + ((fConst19 + 1.0000000000000004) / fConst16));
	fConst22 = (1.0 / fConst21);
	fConst23 = (1 + fConst19);
	fConst24 = (0 - ((1 - fConst19) / fConst23));
	fConst25 = tan((10053.096491487338 / fSamplingFreq));
	fConst26 = (1.0 / faustpower<2>(fConst25));
	fConst27 = (2 * (1 - fConst26));
	fConst28 = (1.0 / fConst25);
	fConst29 = (1 + ((fConst28 - 1.0000000000000004) / fConst25));
	fConst30 = (1 + ((1.0000000000000004 + fConst28) / fConst25));
	fConst31 = (1.0 / fConst30);
	fConst32 = (1 + fConst28);
	fConst33 = (0 - ((1 - fConst28) / fConst32));
	fConst34 = tan((47123.8898038469 / fSamplingFreq));
	fConst35 = (2 * (1 - (1.0 / faustpower<2>(fConst34))));
	fConst36 = (1.0 / fConst34);
	fConst37 = (1 + ((fConst36 - 1.414213562373095) / fConst34));
	fConst38 = (1 + ((1.414213562373095 + fConst36) / fConst34));
	fConst39 = (1.0 / fConst38);
	fConst40 = (0 - fConst0);
	fConst41 = (1.0 / (fConst1 * fConst38));
	fConst42 = (1.0 / fConst32);
	fConst43 = (0 - fConst19);
	fConst44 = (1.0 / (fConst23 * fConst30));
	fConst45 = (2 * (0 - fConst17));
	fConst46 = (1 + ((fConst13 - 1.0000000000000004) / fConst10));
	fConst47 = (1.0 / (1 + ((fConst13 + 1.0000000000000004) / fConst10)));
	fConst48 = (1 + fConst13);
	fConst49 = (0 - ((1 - fConst13) / fConst48));
	fConst50 = (0 - fConst13);
	fConst51 = (1.0 / (fConst48 * fConst21));
	fConst52 = (2 * (0 - fConst11));
	fConst53 = (1 + ((fConst19 - 1.0) / fConst16));
	fConst54 = (1.0 / (1 + ((1.0 + fConst19) / fConst16)));
	fConst55 = (0 - fConst28);
	fConst56 = (2 * (0 - fConst26));
	fConst57 = (1.0 / fConst8);
	fConst58 = (1.0 / tan((270.1769682087222 / fSamplingFreq)));
	fConst59 = (1 + fConst58);
	fConst60 = (0 - ((1 - fConst58) / fConst59));
	fConst61 = (0.027 / fConst59);
	fConst62 = (0.05 / fConst1);
	fConst63 = (1.0 / tan((414.6902302738527 / fSamplingFreq)));
	fConst64 = (1 + fConst63);
	fConst65 = (0 - ((1 - fConst63) / fConst64));
	fConst66 = (0.015 / fConst64);
	clear_state();
}

static void compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = (0.0010000000000000009 * pow(10,(0.05 * fslider0)));
	double 	fSlow1 = (0.0010000000000000009 * pow(10,(0.05 * fslider1)));
	double 	fSlow2 = (1.000000000000001e-05 * fslider2);
	double 	fSlow3 = fslider3;
	double 	fSlow4 = pow(1e+01,(1.2 * fSlow3));
	double 	fSlow5 = (fConst47 * pow(1e+01,(2 * fSlow3)));
	double 	fSlow6 = pow(1e+01,(0.8 * fSlow3));
	double 	fSlow7 = (fConst47 * pow(1e+01,(0.9 * fSlow3)));
	double 	fSlow8 = (2 * (fSlow3 - 0.5));
	double 	fSlow9 = (1 - max(0, (0 - fSlow8)));
	double 	fSlow10 = (1.25 * fSlow3);
	double 	fSlow11 = (1 - max(0, fSlow8));
	for (int i=0; i<count; i++) {
		fRec0[0] = (fSlow0 + (0.999 * fRec0[1]));
		fRec3[0] = ((fConst6 * (fRec2[1] + fRec2[2])) + (fConst5 * fRec3[1]));
		fRec8[0] = (fSlow1 + (0.999 * fRec8[1]));
		double fTemp0 = (fConst12 * fRec12[1]);
		fRec19[0] = (fSlow2 + (0.999 * fRec19[1]));
		double fTemp1 = (double)input0[i];
		fRec18[0] = ((fTemp1 * fRec19[0]) - (fConst39 * ((fConst37 * fRec18[2]) + (fConst35 * fRec18[1]))));
		double fTemp2 = (fRec18[2] + (fRec18[0] + (2 * fRec18[1])));
		fVec0[0] = fTemp2;
		fRec17[0] = ((fConst41 * ((fConst40 * fVec0[1]) + (fConst0 * fVec0[0]))) + (fConst2 * fRec17[1]));
		fRec16[0] = ((fConst42 * (fRec17[0] + fRec17[1])) + (fConst33 * fRec16[1]));
		fRec15[0] = (fRec16[0] - (fConst31 * ((fConst29 * fRec15[2]) + (fConst27 * fRec15[1]))));
		double fTemp3 = (fRec15[2] + (fRec15[0] + (2 * fRec15[1])));
		fVec1[0] = fTemp3;
		fRec14[0] = ((fConst44 * ((fConst43 * fVec1[1]) + (fConst19 * fVec1[0]))) + (fConst24 * fRec14[1]));
		fRec13[0] = (fRec14[0] - (fConst22 * ((fConst20 * fRec13[2]) + (fConst18 * fRec13[1]))));
		fRec12[0] = ((fConst22 * (((fConst17 * fRec13[0]) + (fConst45 * fRec13[1])) + (fConst17 * fRec13[2]))) - (fConst15 * ((fConst14 * fRec12[2]) + fTemp0)));
		double fTemp4 = max(-1, min(1, (fSlow4 * (fRec12[2] + (fConst15 * (fTemp0 + (fConst14 * fRec12[0])))))));
		fRec23[0] = ((fConst44 * (fVec1[0] + fVec1[1])) + (fConst24 * fRec23[1]));
		fRec22[0] = (fRec23[0] - (fConst22 * ((fConst20 * fRec22[2]) + (fConst18 * fRec22[1]))));
		double fTemp5 = (fRec22[2] + (fRec22[0] + (2 * fRec22[1])));
		fVec2[0] = fTemp5;
		fRec21[0] = ((fConst51 * ((fConst50 * fVec2[1]) + (fConst13 * fVec2[0]))) + (fConst49 * fRec21[1]));
		fRec20[0] = (fRec21[0] - (fConst47 * ((fConst46 * fRec20[2]) + (fConst12 * fRec20[1]))));
		double fTemp6 = max(-1, min(1, (fSlow5 * (((fConst11 * fRec20[0]) + (fConst52 * fRec20[1])) + (fConst11 * fRec20[2])))));
		double fTemp7 = (fConst12 * fRec24[1]);
		double fTemp8 = (fConst18 * fRec25[1]);
		fRec27[0] = ((fConst42 * ((fConst55 * fRec17[1]) + (fConst28 * fRec17[0]))) + (fConst33 * fRec27[1]));
		fRec26[0] = (fRec27[0] - (fConst31 * ((fConst29 * fRec26[2]) + (fConst27 * fRec26[1]))));
		fRec25[0] = ((fConst31 * (((fConst26 * fRec26[0]) + (fConst56 * fRec26[1])) + (fConst26 * fRec26[2]))) - (fConst54 * ((fConst53 * fRec25[2]) + fTemp8)));
		fRec24[0] = ((fRec25[2] + (fConst54 * (fTemp8 + (fConst53 * fRec25[0])))) - (fConst15 * ((fConst14 * fRec24[2]) + fTemp7)));
		double fTemp9 = max(-1, min(1, (fSlow6 * (fRec24[2] + (fConst15 * (fTemp7 + (fConst14 * fRec24[0])))))));
		fRec29[0] = ((fConst51 * (fVec2[0] + fVec2[1])) + (fConst49 * fRec29[1]));
		fRec28[0] = (fRec29[0] - (fConst47 * ((fConst46 * fRec28[2]) + (fConst12 * fRec28[1]))));
		double fTemp10 = max(-1, min(1, (fSlow7 * (fRec28[2] + (fRec28[0] + (2 * fRec28[1]))))));
		double fTemp11 = ((1.2589412 * (fTemp10 * (1 - (0.3333333333333333 * faustpower<2>(fTemp10))))) + (1.584893192 * ((fTemp9 * (1 - (0.3333333333333333 * faustpower<2>(fTemp9)))) + ((fTemp6 * (1 - (0.3333333333333333 * faustpower<2>(fTemp6)))) + (0.8413951417869425 * (fTemp4 * (1 - (0.3333333333333333 * faustpower<2>(fTemp4)))))))));
		fVec3[0] = fTemp11;
		fRec11[0] = ((fConst57 * (fVec3[0] + fVec3[1])) + (fConst9 * fRec11[1]));
		fRec30[0] = ((fConst61 * (fRec10[1] + fRec10[2])) + (fConst60 * fRec30[1]));
		double fTemp12 = (1 - fRec19[0]);
		fRec10[0] = (Ftube(TUBE_TABLE_6DJ8_68k, (((fTemp1 * ((fSlow11 * fRec19[0]) + (fTemp12 * (1 + (fSlow10 * ((4 - (4 * fabs((fTemp1 * fTemp12)))) - 1)))))) + (fRec30[0] + (fSlow9 * fRec11[0]))) - 1.863946)) - 60.96496296296296);
		fRec9[0] = ((fConst62 * ((fConst40 * fRec10[1]) + (fConst0 * fRec10[0]))) + (fConst2 * fRec9[1]));
		double fTemp13 = (fRec9[0] * fRec8[0]);
		fVec4[0] = fTemp13;
		fRec7[0] = ((fConst57 * (fVec4[0] + fVec4[1])) + (fConst9 * fRec7[1]));
		fRec31[0] = ((fConst66 * (fRec6[1] + fRec6[2])) + (fConst65 * fRec31[1]));
		fRec6[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec31[0] + fRec7[0]) - 1.271609)) - 45.22606666666667);
		fRec5[0] = ((fConst62 * ((fConst40 * fRec6[1]) + (fConst0 * fRec6[0]))) + (fConst2 * fRec5[1]));
		double fTemp14 = (fRec8[0] * fRec5[0]);
		fVec5[0] = fTemp14;
		fRec4[0] = ((fConst57 * (fVec5[0] + fVec5[1])) + (fConst9 * fRec4[1]));
		fRec2[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec4[0] + fRec3[0]) - 0.797043)) - 32.799634146341475);
		fRec1[0] = ((fConst62 * ((fConst40 * fRec2[1]) + (fConst0 * fRec2[0]))) + (fConst2 * fRec1[1]));
		fRec34[0] = ((fConst6 * (fRec33[1] + fRec33[2])) + (fConst5 * fRec34[1]));
		fRec33[0] = (Ftube(TUBE_TABLE_6DJ8_68k, ((fRec34[0] + fRec4[0]) - 0.799031)) - 32.55719512195121);
		fRec32[0] = ((fConst62 * ((fConst40 * fRec33[1]) + (fConst0 * fRec33[0]))) + (fConst2 * fRec32[1]));
		output0[i] = (FAUSTFLOAT)((fRec32[0] + fRec1[0]) * fRec0[0]);
		// post processing
		fRec32[1] = fRec32[0];
		fRec33[2] = fRec33[1]; fRec33[1] = fRec33[0];
		fRec34[1] = fRec34[0];
		fRec1[1] = fRec1[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec4[1] = fRec4[0];
		fVec5[1] = fVec5[0];
		fRec5[1] = fRec5[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec31[1] = fRec31[0];
		fRec7[1] = fRec7[0];
		fVec4[1] = fVec4[0];
		fRec9[1] = fRec9[0];
		fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
		fRec30[1] = fRec30[0];
		fRec11[1] = fRec11[0];
		fVec3[1] = fVec3[0];
		fRec28[2] = fRec28[1]; fRec28[1] = fRec28[0];
		fRec29[1] = fRec29[0];
		fRec24[2] = fRec24[1]; fRec24[1] = fRec24[0];
		fRec25[2] = fRec25[1]; fRec25[1] = fRec25[0];
		fRec26[2] = fRec26[1]; fRec26[1] = fRec26[0];
		fRec27[1] = fRec27[0];
		fRec20[2] = fRec20[1]; fRec20[1] = fRec20[0];
		fRec21[1] = fRec21[0];
		fVec2[1] = fVec2[0];
		fRec22[2] = fRec22[1]; fRec22[1] = fRec22[0];
		fRec23[1] = fRec23[0];
		fRec12[2] = fRec12[1]; fRec12[1] = fRec12[0];
		fRec13[2] = fRec13[1]; fRec13[1] = fRec13[0];
		fRec14[1] = fRec14[0];
		fVec1[1] = fVec1[0];
		fRec15[2] = fRec15[1]; fRec15[1] = fRec15[0];
		fRec16[1] = fRec16[0];
		fRec17[1] = fRec17[0];
		fVec0[1] = fVec0[0];
		fRec18[2] = fRec18[1]; fRec18[1] = fRec18[0];
		fRec19[1] = fRec19[0];
		fRec8[1] = fRec8[0];
		fRec3[1] = fRec3[0];
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
    "6DJ8",  // id
    N_("6DJ8"),  // name
    0,  // groups
    compute,  // mono_audio
    0,  // stereo_audio
    init,  // set_samplerate
    0,  // activate plugin
    register_params,
    0,   // load_ui
    clear_state,  // clear_state
};

} // end namespace gxamp10
