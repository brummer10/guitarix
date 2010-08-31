namespace gxdistortion {
// generated from file '../src/faust/gxdistortion.dsp'

double 	fConst0;
double 	fConst1;
double 	fConst2;
double 	fConst3;
double 	fConst4;
double 	fConst5;
double 	fConst6;
double 	fConst7;
double 	fConst8;
double 	fConst9;
double 	fConst10;
double 	fConst11;
double 	fConst12;
double 	fConst13;
double 	fConst14;
double 	fConst15;
double 	fConst16;
double 	fConst17;
double 	fVec0[2];
double 	fConst18;
double 	fRec4[2];
double 	fRec3[3];
double 	fVec1[2];
double 	fConst19;
double 	fConst20;
double 	fRec2[2];
double 	fRec1[3];
double 	fConst21;
FAUSTFLOAT 	fslider0;
double 	fVec2[2];
double 	fRec0[2];
double 	fConst22;
double 	fRec7[2];
double 	fRec6[3];
double 	fConst23;
double 	fVec3[2];
double 	fRec5[2];
double 	fConst24;
double 	fConst25;
double 	fConst26;
double 	fConst27;
double 	fConst28;
double 	fConst29;
double 	fConst30;
double 	fConst31;
double 	fRec12[2];
double 	fRec11[3];
double 	fVec4[2];
double 	fConst32;
double 	fConst33;
double 	fRec10[2];
double 	fRec9[3];
double 	fConst34;
double 	fVec5[2];
double 	fRec8[2];
double 	fRec15[2];
double 	fRec14[3];
double 	fVec6[2];
double 	fRec13[2];
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = tan((3769.9111843077517 / fSamplingFreq));
	fConst1 = (1.0 / faustpower<2>(fConst0));
	fConst2 = (2 * (1 - fConst1));
	fConst3 = (1.0 / fConst0);
	fConst4 = (1 + ((fConst3 - 1.0000000000000004) / fConst0));
	fConst5 = (1 + ((1.0000000000000004 + fConst3) / fConst0));
	fConst6 = (1.0 / fConst5);
	fConst7 = (1 + fConst3);
	fConst8 = (0 - ((1 - fConst3) / fConst7));
	fConst9 = tan((10053.096491487338 / fSamplingFreq));
	fConst10 = (1.0 / faustpower<2>(fConst9));
	fConst11 = (2 * (1 - fConst10));
	fConst12 = (1.0 / fConst9);
	fConst13 = (1 + ((fConst12 - 1.0000000000000004) / fConst9));
	fConst14 = (1 + ((1.0000000000000004 + fConst12) / fConst9));
	fConst15 = (1.0 / fConst14);
	fConst16 = (1 + fConst12);
	fConst17 = (0 - ((1 - fConst12) / fConst16));
	for (int i=0; i<2; i++) fVec0[i] = 0;
	fConst18 = (1.0 / fConst16);
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<3; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	fConst19 = (0 - fConst3);
	fConst20 = (1.0 / (fConst7 * fConst14));
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<3; i++) fRec1[i] = 0;
	fConst21 = (2 * (0 - fConst1));
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	fConst22 = (0 - fConst12);
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	fConst23 = (2 * (0 - fConst10));
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	fConst24 = tan((942.4777960769379 / fSamplingFreq));
	fConst25 = (1.0 / faustpower<2>(fConst24));
	fConst26 = (2 * (1 - fConst25));
	fConst27 = (1.0 / fConst24);
	fConst28 = (1 + ((fConst27 - 1.0000000000000004) / fConst24));
	fConst29 = (1.0 / (1 + ((1.0000000000000004 + fConst27) / fConst24)));
	fConst30 = (1 + fConst27);
	fConst31 = (0 - ((1 - fConst27) / fConst30));
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<3; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	fConst32 = (0 - fConst27);
	fConst33 = (1.0 / (fConst30 * fConst5));
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<3; i++) fRec9[i] = 0;
	fConst34 = (2 * (0 - fConst25));
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<3; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = fslider0;
	double 	fSlow1 = (fConst6 * pow(1e+01,(1.2 * fSlow0)));
	double 	fSlow2 = (fConst15 * pow(1e+01,(0.8 * fSlow0)));
	double 	fSlow3 = (fConst29 * pow(1e+01,(2 * fSlow0)));
	double 	fSlow4 = (fConst29 * pow(1e+01,(0.9 * fSlow0)));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fVec0[0] = fTemp0;
		fRec4[0] = ((fConst18 * (fVec0[0] + fVec0[1])) + (fConst17 * fRec4[1]));
		fRec3[0] = (fRec4[0] - (fConst15 * ((fConst13 * fRec3[2]) + (fConst11 * fRec3[1]))));
		double fTemp1 = (fRec3[2] + (fRec3[0] + (2 * fRec3[1])));
		fVec1[0] = fTemp1;
		fRec2[0] = ((fConst20 * ((fConst19 * fVec1[1]) + (fConst3 * fVec1[0]))) + (fConst8 * fRec2[1]));
		fRec1[0] = (fRec2[0] - (fConst6 * ((fConst4 * fRec1[2]) + (fConst2 * fRec1[1]))));
		double fTemp2 = max(-1, min(1, (fSlow1 * (((fConst1 * fRec1[0]) + (fConst21 * fRec1[1])) + (fConst1 * fRec1[2])))));
		double fTemp3 = (fTemp2 * (1 - (0.3333333333333333 * faustpower<2>(fTemp2))));
		fVec2[0] = fTemp3;
		fRec0[0] = ((fVec2[0] + (0.995 * fRec0[1])) - fVec2[1]);
		fRec7[0] = ((fConst18 * ((fConst22 * fVec0[1]) + (fConst12 * fVec0[0]))) + (fConst17 * fRec7[1]));
		fRec6[0] = (fRec7[0] - (fConst15 * ((fConst13 * fRec6[2]) + (fConst11 * fRec6[1]))));
		double fTemp4 = max(-1, min(1, (fSlow2 * (((fConst10 * fRec6[0]) + (fConst23 * fRec6[1])) + (fConst10 * fRec6[2])))));
		double fTemp5 = (fTemp4 * (1 - (0.3333333333333333 * faustpower<2>(fTemp4))));
		fVec3[0] = fTemp5;
		fRec5[0] = ((fVec3[0] + (0.995 * fRec5[1])) - fVec3[1]);
		fRec12[0] = ((fConst20 * (fVec1[0] + fVec1[1])) + (fConst8 * fRec12[1]));
		fRec11[0] = (fRec12[0] - (fConst6 * ((fConst4 * fRec11[2]) + (fConst2 * fRec11[1]))));
		double fTemp6 = (fRec11[2] + (fRec11[0] + (2 * fRec11[1])));
		fVec4[0] = fTemp6;
		fRec10[0] = ((fConst33 * ((fConst32 * fVec4[1]) + (fConst27 * fVec4[0]))) + (fConst31 * fRec10[1]));
		fRec9[0] = (fRec10[0] - (fConst29 * ((fConst28 * fRec9[2]) + (fConst26 * fRec9[1]))));
		double fTemp7 = max(-1, min(1, (fSlow3 * (((fConst25 * fRec9[0]) + (fConst34 * fRec9[1])) + (fConst25 * fRec9[2])))));
		double fTemp8 = (fTemp7 * (1 - (0.3333333333333333 * faustpower<2>(fTemp7))));
		fVec5[0] = fTemp8;
		fRec8[0] = ((fVec5[0] + (0.995 * fRec8[1])) - fVec5[1]);
		fRec15[0] = ((fConst33 * (fVec4[0] + fVec4[1])) + (fConst31 * fRec15[1]));
		fRec14[0] = (fRec15[0] - (fConst29 * ((fConst28 * fRec14[2]) + (fConst26 * fRec14[1]))));
		double fTemp9 = max(-1, min(1, (fSlow4 * (fRec14[2] + (fRec14[0] + (2 * fRec14[1]))))));
		double fTemp10 = (fTemp9 * (1 - (0.3333333333333333 * faustpower<2>(fTemp9))));
		fVec6[0] = fTemp10;
		fRec13[0] = ((fVec6[0] + (0.995 * fRec13[1])) - fVec6[1]);
		output0[i] = (FAUSTFLOAT)(8.0 * (fRec13[0] + (fRec8[0] + ((0.5 * fRec5[0]) + (0.625 * fRec0[0])))));
		// post processing
		fRec13[1] = fRec13[0];
		fVec6[1] = fVec6[0];
		fRec14[2] = fRec14[1]; fRec14[1] = fRec14[0];
		fRec15[1] = fRec15[0];
		fRec8[1] = fRec8[0];
		fVec5[1] = fVec5[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec10[1] = fRec10[0];
		fVec4[1] = fVec4[0];
		fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
		fRec12[1] = fRec12[0];
		fRec5[1] = fRec5[0];
		fVec3[1] = fVec3[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec7[1] = fRec7[0];
		fRec0[1] = fRec0[0];
		fVec2[1] = fVec2[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fVec1[1] = fVec1[0];
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fVec0[1] = fVec0[0];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("distortion.drive","","S","",&fslider0, 0.64, 0.0, 1.0, 0.01);
	registerInit("distortion", init);
}

} // end namespace gxdistortion
