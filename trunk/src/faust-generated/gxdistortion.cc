namespace gxdistortion {
// generated from file '../src/faust/gxdistortion.dsp'

double 	fVec0[2];
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
double 	fConst18;
double 	fConst19;
double 	fConst20;
double 	fConst21;
double 	fConst22;
double 	fRec3[2];
double 	fRec2[3];
double 	fConst23;
double 	fRec1[3];
double 	fRec0[3];
FAUSTFLOAT 	fslider0;
double 	fConst24;
double 	fConst25;
double 	fConst26;
double 	fConst27;
double 	fConst28;
double 	fRec8[2];
double 	fRec7[3];
double 	fVec1[2];
double 	fConst29;
double 	fConst30;
double 	fRec6[2];
double 	fRec5[3];
double 	fConst31;
double 	fRec4[3];
double 	fConst32;
double 	fConst33;
double 	fConst34;
double 	fConst35;
double 	fRec12[2];
double 	fRec11[3];
double 	fVec2[2];
double 	fConst36;
double 	fConst37;
double 	fRec10[2];
double 	fRec9[3];
double 	fConst38;
double 	fRec14[2];
double 	fRec13[3];
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	fConst0 = tan((942.4777960769379 / fSamplingFreq));
	fConst1 = (1.0 / faustpower<2>(fConst0));
	fConst2 = (2 * (1 - fConst1));
	fConst3 = (1.0 / fConst0);
	fConst4 = (1 + ((fConst3 - 1.0) / fConst0));
	fConst5 = (1.0 / (1 + ((1.0 + fConst3) / fConst0)));
	fConst6 = tan((3769.9111843077517 / fSamplingFreq));
	fConst7 = (1.0 / faustpower<2>(fConst6));
	fConst8 = (2 * (1 - fConst7));
	fConst9 = (1.0 / fConst6);
	fConst10 = (1 + ((fConst9 - 1.0) / fConst6));
	fConst11 = (1.0 / (1 + ((1.0 + fConst9) / fConst6)));
	fConst12 = tan((10053.096491487338 / fSamplingFreq));
	fConst13 = (1.0 / faustpower<2>(fConst12));
	fConst14 = (2 * (1 - fConst13));
	fConst15 = (1.0 / fConst12);
	fConst16 = (1 + ((fConst15 - 1.0000000000000004) / fConst12));
	fConst17 = (1 + ((1.0000000000000004 + fConst15) / fConst12));
	fConst18 = (1.0 / fConst17);
	fConst19 = (1 + fConst15);
	fConst20 = (0 - ((1 - fConst15) / fConst19));
	fConst21 = (0 - fConst15);
	fConst22 = (1.0 / fConst19);
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	fConst23 = (2 * (0 - fConst13));
	for (int i=0; i<3; i++) fRec1[i] = 0;
	for (int i=0; i<3; i++) fRec0[i] = 0;
	fConst24 = (1 + ((fConst9 - 1.0000000000000004) / fConst6));
	fConst25 = (1 + ((fConst9 + 1.0000000000000004) / fConst6));
	fConst26 = (1.0 / fConst25);
	fConst27 = (1 + fConst9);
	fConst28 = (0 - ((1 - fConst9) / fConst27));
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<3; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	fConst29 = (0 - fConst9);
	fConst30 = (1.0 / (fConst27 * fConst17));
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	fConst31 = (2 * (0 - fConst7));
	for (int i=0; i<3; i++) fRec4[i] = 0;
	fConst32 = (1 + ((fConst3 - 1.0000000000000004) / fConst0));
	fConst33 = (1.0 / (1 + ((fConst3 + 1.0000000000000004) / fConst0)));
	fConst34 = (1 + fConst3);
	fConst35 = (0 - ((1 - fConst3) / fConst34));
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<3; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	fConst36 = (0 - fConst3);
	fConst37 = (1.0 / (fConst34 * fConst25));
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<3; i++) fRec9[i] = 0;
	fConst38 = (2 * (0 - fConst1));
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<3; i++) fRec13[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = fslider0;
	double 	fSlow1 = pow(1e+01,(0.8 * fSlow0));
	double 	fSlow2 = pow(1e+01,(1.2 * fSlow0));
	double 	fSlow3 = (fConst33 * pow(1e+01,(2 * fSlow0)));
	double 	fSlow4 = (fConst33 * pow(1e+01,(0.9 * fSlow0)));
	int 	iSlow5 = int(min(1, (100 * fSlow0)));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fVec0[0] = fTemp0;
		double fTemp1 = (fConst2 * fRec0[1]);
		double fTemp2 = (fConst8 * fRec1[1]);
		fRec3[0] = ((fConst22 * ((fConst21 * fVec0[1]) + (fConst15 * fVec0[0]))) + (fConst20 * fRec3[1]));
		fRec2[0] = (fRec3[0] - (fConst18 * ((fConst16 * fRec2[2]) + (fConst14 * fRec2[1]))));
		fRec1[0] = ((fConst18 * (((fConst13 * fRec2[0]) + (fConst23 * fRec2[1])) + (fConst13 * fRec2[2]))) - (fConst11 * ((fConst10 * fRec1[2]) + fTemp2)));
		fRec0[0] = ((fRec1[2] + (fConst11 * (fTemp2 + (fConst10 * fRec1[0])))) - (fConst5 * ((fConst4 * fRec0[2]) + fTemp1)));
		double fTemp3 = max(-1, min(1, (fSlow1 * (fRec0[2] + (fConst5 * (fTemp1 + (fConst4 * fRec0[0])))))));
		double fTemp4 = (fConst2 * fRec4[1]);
		fRec8[0] = ((fConst22 * (fVec0[0] + fVec0[1])) + (fConst20 * fRec8[1]));
		fRec7[0] = (fRec8[0] - (fConst18 * ((fConst16 * fRec7[2]) + (fConst14 * fRec7[1]))));
		double fTemp5 = (fRec7[2] + (fRec7[0] + (2 * fRec7[1])));
		fVec1[0] = fTemp5;
		fRec6[0] = ((fConst30 * ((fConst29 * fVec1[1]) + (fConst9 * fVec1[0]))) + (fConst28 * fRec6[1]));
		fRec5[0] = (fRec6[0] - (fConst26 * ((fConst24 * fRec5[2]) + (fConst8 * fRec5[1]))));
		fRec4[0] = ((fConst26 * (((fConst7 * fRec5[0]) + (fConst31 * fRec5[1])) + (fConst7 * fRec5[2]))) - (fConst5 * ((fConst4 * fRec4[2]) + fTemp4)));
		double fTemp6 = max(-1, min(1, (fSlow2 * (fRec4[2] + (fConst5 * (fTemp4 + (fConst4 * fRec4[0])))))));
		fRec12[0] = ((fConst30 * (fVec1[0] + fVec1[1])) + (fConst28 * fRec12[1]));
		fRec11[0] = (fRec12[0] - (fConst26 * ((fConst24 * fRec11[2]) + (fConst8 * fRec11[1]))));
		double fTemp7 = (fRec11[2] + (fRec11[0] + (2 * fRec11[1])));
		fVec2[0] = fTemp7;
		fRec10[0] = ((fConst37 * ((fConst36 * fVec2[1]) + (fConst3 * fVec2[0]))) + (fConst35 * fRec10[1]));
		fRec9[0] = (fRec10[0] - (fConst33 * ((fConst32 * fRec9[2]) + (fConst2 * fRec9[1]))));
		double fTemp8 = max(-1, min(1, (fSlow3 * (((fConst1 * fRec9[0]) + (fConst38 * fRec9[1])) + (fConst1 * fRec9[2])))));
		fRec14[0] = ((fConst37 * (fVec2[0] + fVec2[1])) + (fConst35 * fRec14[1]));
		fRec13[0] = (fRec14[0] - (fConst33 * ((fConst32 * fRec13[2]) + (fConst2 * fRec13[1]))));
		double fTemp9 = max(-1, min(1, (fSlow4 * (fRec13[2] + (fRec13[0] + (2 * fRec13[1]))))));
		output0[i] = (FAUSTFLOAT)((iSlow5)?(8.0 * ((((fTemp9 * (1 - (0.3333333333333333 * faustpower<2>(fTemp9)))) + (fTemp8 * (1 - (0.3333333333333333 * faustpower<2>(fTemp8))))) + (0.625 * (fTemp6 * (1 - (0.3333333333333333 * faustpower<2>(fTemp6)))))) + (0.5 * (fTemp3 * (1 - (0.3333333333333333 * faustpower<2>(fTemp3))))))):fVec0[0]);
		// post processing
		fRec13[2] = fRec13[1]; fRec13[1] = fRec13[0];
		fRec14[1] = fRec14[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec10[1] = fRec10[0];
		fVec2[1] = fVec2[0];
		fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
		fRec12[1] = fRec12[0];
		fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		fVec1[1] = fVec1[0];
		fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fVec0[1] = fVec0[0];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("gxdistortion.drive","","S","",&fslider0, 0.35, 0.0, 1.0, 0.01);
	registerInit("gxdistortion", init);
}

} // end namespace gxdistortion
