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
double 	fVec0[2];
double 	fConst9;
double 	fConst10;
double 	fRec1[2];
double 	fRec0[3];
double 	fConst11;
FAUSTFLOAT 	fslider0;
double 	fConst12;
double 	fConst13;
double 	fConst14;
double 	fConst15;
double 	fConst16;
double 	fConst17;
double 	fConst18;
double 	fConst19;
double 	fConst20;
double 	fRec5[2];
double 	fRec4[3];
double 	fVec1[2];
double 	fConst21;
double 	fConst22;
double 	fRec3[2];
double 	fRec2[3];
double 	fConst23;
double 	fConst24;
double 	fConst25;
double 	fConst26;
double 	fConst27;
double 	fConst28;
double 	fConst29;
double 	fConst30;
double 	fConst31;
double 	fRec9[2];
double 	fRec8[3];
double 	fVec2[2];
double 	fConst32;
double 	fConst33;
double 	fRec7[2];
double 	fRec6[3];
double 	fConst34;
double 	fRec11[2];
double 	fRec10[3];
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = tan((10053.096491487338 / fSamplingFreq));
	fConst1 = (1.0 / faustpower<2>(fConst0));
	fConst2 = (2 * (1 - fConst1));
	fConst3 = (1.0 / fConst0);
	fConst4 = (1 + ((fConst3 - 1.0000000000000004) / fConst0));
	fConst5 = (1 + ((1.0000000000000004 + fConst3) / fConst0));
	fConst6 = (1.0 / fConst5);
	fConst7 = (1 + fConst3);
	fConst8 = (0 - ((1 - fConst3) / fConst7));
	for (int i=0; i<2; i++) fVec0[i] = 0;
	fConst9 = (0 - fConst3);
	fConst10 = (1.0 / fConst7);
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<3; i++) fRec0[i] = 0;
	fConst11 = (2 * (0 - fConst1));
	fConst12 = tan((3769.9111843077517 / fSamplingFreq));
	fConst13 = (1.0 / faustpower<2>(fConst12));
	fConst14 = (2 * (1 - fConst13));
	fConst15 = (1.0 / fConst12);
	fConst16 = (1 + ((fConst15 - 1.0000000000000004) / fConst12));
	fConst17 = (1 + ((1.0000000000000004 + fConst15) / fConst12));
	fConst18 = (1.0 / fConst17);
	fConst19 = (1 + fConst15);
	fConst20 = (0 - ((1 - fConst15) / fConst19));
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<3; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	fConst21 = (0 - fConst15);
	fConst22 = (1.0 / (fConst19 * fConst5));
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	fConst23 = (2 * (0 - fConst13));
	fConst24 = tan((942.4777960769379 / fSamplingFreq));
	fConst25 = (1.0 / faustpower<2>(fConst24));
	fConst26 = (2 * (1 - fConst25));
	fConst27 = (1.0 / fConst24);
	fConst28 = (1 + ((fConst27 - 1.0000000000000004) / fConst24));
	fConst29 = (1.0 / (1 + ((1.0000000000000004 + fConst27) / fConst24)));
	fConst30 = (1 + fConst27);
	fConst31 = (0 - ((1 - fConst27) / fConst30));
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<3; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	fConst32 = (0 - fConst27);
	fConst33 = (1.0 / (fConst30 * fConst17));
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	fConst34 = (2 * (0 - fConst25));
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<3; i++) fRec10[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = fslider0;
	double 	fSlow1 = (fConst6 * pow(1e+01,(0.8 * fSlow0)));
	double 	fSlow2 = (fConst18 * pow(1e+01,(1.2 * fSlow0)));
	double 	fSlow3 = (fConst29 * pow(1e+01,(2 * fSlow0)));
	double 	fSlow4 = (fConst29 * pow(1e+01,(0.9 * fSlow0)));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fVec0[0] = fTemp0;
		fRec1[0] = ((fConst10 * ((fConst9 * fVec0[1]) + (fConst3 * fVec0[0]))) + (fConst8 * fRec1[1]));
		fRec0[0] = (fRec1[0] - (fConst6 * ((fConst4 * fRec0[2]) + (fConst2 * fRec0[1]))));
		double fTemp1 = max(-1, min(1, (fSlow1 * (((fConst1 * fRec0[0]) + (fConst11 * fRec0[1])) + (fConst1 * fRec0[2])))));
		fRec5[0] = ((fConst10 * (fVec0[0] + fVec0[1])) + (fConst8 * fRec5[1]));
		fRec4[0] = (fRec5[0] - (fConst6 * ((fConst4 * fRec4[2]) + (fConst2 * fRec4[1]))));
		double fTemp2 = (fRec4[2] + (fRec4[0] + (2 * fRec4[1])));
		fVec1[0] = fTemp2;
		fRec3[0] = ((fConst22 * ((fConst21 * fVec1[1]) + (fConst15 * fVec1[0]))) + (fConst20 * fRec3[1]));
		fRec2[0] = (fRec3[0] - (fConst18 * ((fConst16 * fRec2[2]) + (fConst14 * fRec2[1]))));
		double fTemp3 = max(-1, min(1, (fSlow2 * (((fConst13 * fRec2[0]) + (fConst23 * fRec2[1])) + (fConst13 * fRec2[2])))));
		fRec9[0] = ((fConst22 * (fVec1[0] + fVec1[1])) + (fConst20 * fRec9[1]));
		fRec8[0] = (fRec9[0] - (fConst18 * ((fConst16 * fRec8[2]) + (fConst14 * fRec8[1]))));
		double fTemp4 = (fRec8[2] + (fRec8[0] + (2 * fRec8[1])));
		fVec2[0] = fTemp4;
		fRec7[0] = ((fConst33 * ((fConst32 * fVec2[1]) + (fConst27 * fVec2[0]))) + (fConst31 * fRec7[1]));
		fRec6[0] = (fRec7[0] - (fConst29 * ((fConst28 * fRec6[2]) + (fConst26 * fRec6[1]))));
		double fTemp5 = max(-1, min(1, (fSlow3 * (((fConst25 * fRec6[0]) + (fConst34 * fRec6[1])) + (fConst25 * fRec6[2])))));
		fRec11[0] = ((fConst33 * (fVec2[0] + fVec2[1])) + (fConst31 * fRec11[1]));
		fRec10[0] = (fRec11[0] - (fConst29 * ((fConst28 * fRec10[2]) + (fConst26 * fRec10[1]))));
		double fTemp6 = max(-1, min(1, (fSlow4 * (fRec10[2] + (fRec10[0] + (2 * fRec10[1]))))));
		output0[i] = (FAUSTFLOAT)(8.0 * ((((fTemp6 * (1 - (0.3333333333333333 * faustpower<2>(fTemp6)))) + (fTemp5 * (1 - (0.3333333333333333 * faustpower<2>(fTemp5))))) + (0.625 * (fTemp3 * (1 - (0.3333333333333333 * faustpower<2>(fTemp3)))))) + (0.5 * (fTemp1 * (1 - (0.3333333333333333 * faustpower<2>(fTemp1)))))));
		// post processing
		fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec7[1] = fRec7[0];
		fVec2[1] = fVec2[0];
		fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
		fRec9[1] = fRec9[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fVec1[1] = fVec1[0];
		fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
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
