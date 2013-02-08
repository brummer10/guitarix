// generated from file '../src/faust/gxamp17.dsp' by dsp2cc:
// Code generated with Faust 0.9.46 (http://faust.grame.fr)



inline void GxAmpFeedBack::clear_state_f()
{
	for (int32_t i=0; i<2; i++) fRec0[i] = 0;
	for (int32_t i=0; i<2; i++) fRec8[i] = 0;
	for (int32_t i=0; i<2; i++) fRec20[i] = 0;
	for (int32_t i=0; i<3; i++) fRec19[i] = 0;
	for (int32_t i=0; i<2; i++) fVec0[i] = 0;
	for (int32_t i=0; i<2; i++) fRec18[i] = 0;
	for (int32_t i=0; i<2; i++) fRec17[i] = 0;
	for (int32_t i=0; i<3; i++) fRec16[i] = 0;
	for (int32_t i=0; i<2; i++) fVec1[i] = 0;
	for (int32_t i=0; i<2; i++) fRec15[i] = 0;
	for (int32_t i=0; i<3; i++) fRec14[i] = 0;
	for (int32_t i=0; i<3; i++) fRec13[i] = 0;
	for (int32_t i=0; i<2; i++) fRec24[i] = 0;
	for (int32_t i=0; i<3; i++) fRec23[i] = 0;
	for (int32_t i=0; i<2; i++) fVec2[i] = 0;
	for (int32_t i=0; i<2; i++) fRec22[i] = 0;
	for (int32_t i=0; i<3; i++) fRec21[i] = 0;
	for (int32_t i=0; i<2; i++) fRec28[i] = 0;
	for (int32_t i=0; i<3; i++) fRec27[i] = 0;
	for (int32_t i=0; i<3; i++) fRec26[i] = 0;
	for (int32_t i=0; i<3; i++) fRec25[i] = 0;
	for (int32_t i=0; i<2; i++) fRec30[i] = 0;
	for (int32_t i=0; i<3; i++) fRec29[i] = 0;
	for (int32_t i=0; i<2; i++) fVec3[i] = 0;
	for (int32_t i=0; i<2; i++) fRec12[i] = 0;
	for (int32_t i=0; i<2; i++) fRec31[i] = 0;
	for (int32_t i=0; i<3; i++) fRec11[i] = 0;
	for (int32_t i=0; i<2; i++) fRec10[i] = 0;
	for (int32_t i=0; i<2; i++) fRec34[i] = 0;
	for (int32_t i=0; i<3; i++) fRec33[i] = 0;
	for (int32_t i=0; i<2; i++) fRec32[i] = 0;
	for (int32_t i=0; i<2; i++) fRec35[i] = 0;
	for (int32_t i=0; i<2; i++) fRec9[i] = 0;
	for (int32_t i=0; i<2; i++) fVec4[i] = 0;
	for (int32_t i=0; i<2; i++) fRec7[i] = 0;
	for (int32_t i=0; i<2; i++) fRec36[i] = 0;
	for (int32_t i=0; i<3; i++) fRec6[i] = 0;
	for (int32_t i=0; i<2; i++) fRec5[i] = 0;
	for (int32_t i=0; i<2; i++) fRec39[i] = 0;
	for (int32_t i=0; i<3; i++) fRec38[i] = 0;
	for (int32_t i=0; i<2; i++) fRec37[i] = 0;
	for (int32_t i=0; i<2; i++) fRec4[i] = 0;
	for (int32_t i=0; i<2; i++) fRec3[i] = 0;
	for (int32_t i=0; i<2; i++) fRec40[i] = 0;
	for (int32_t i=0; i<3; i++) fRec2[i] = 0;
	for (int32_t i=0; i<2; i++) fRec1[i] = 0;
}

void GxAmpFeedBack::clear_state_f_static(GxAmpFeedBack *p)
{
	p->clear_state_f();
}

inline void GxAmpFeedBack::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (1.0 / tan((97.38937226128358 / iConst0)));
	fConst2 = (1 + fConst1);
	fConst3 = (0 - ((1 - fConst1) / fConst2));
	fConst4 = (1.0 / tan((20517.741620594938 / iConst0)));
	fConst5 = (1 + fConst4);
	fConst6 = (0 - ((1 - fConst4) / fConst5));
	fConst7 = tan((942.4777960769379 / iConst0));
	fConst8 = (1.0 / faustpower<2>(fConst7));
	fConst9 = (2 * (1 - fConst8));
	fConst10 = (1.0 / fConst7);
	fConst11 = (1 + ((fConst10 - 1.0) / fConst7));
	fConst12 = (1.0 / (1 + ((1.0 + fConst10) / fConst7)));
	fConst13 = tan((3769.9111843077517 / iConst0));
	fConst14 = (1.0 / faustpower<2>(fConst13));
	fConst15 = (2 * (1 - fConst14));
	fConst16 = (1.0 / fConst13);
	fConst17 = (1 + ((fConst16 - 1.0000000000000004) / fConst13));
	fConst18 = (1 + ((fConst16 + 1.0000000000000004) / fConst13));
	fConst19 = (1.0 / fConst18);
	fConst20 = (1 + fConst16);
	fConst21 = (0 - ((1 - fConst16) / fConst20));
	fConst22 = tan((10053.096491487338 / iConst0));
	fConst23 = (1.0 / faustpower<2>(fConst22));
	fConst24 = (2 * (1 - fConst23));
	fConst25 = (1.0 / fConst22);
	fConst26 = (1 + ((fConst25 - 1.0000000000000004) / fConst22));
	fConst27 = (1 + ((1.0000000000000004 + fConst25) / fConst22));
	fConst28 = (1.0 / fConst27);
	fConst29 = (1 + fConst25);
	fConst30 = (0 - ((1 - fConst25) / fConst29));
	fConst31 = tan((47123.8898038469 / iConst0));
	fConst32 = (2 * (1 - (1.0 / faustpower<2>(fConst31))));
	fConst33 = (1.0 / fConst31);
	fConst34 = (1 + ((fConst33 - 1.414213562373095) / fConst31));
	fConst35 = (1 + ((1.414213562373095 + fConst33) / fConst31));
	fConst36 = (1.0 / fConst35);
	fConst37 = (0 - fConst1);
	fConst38 = (1.0 / (fConst2 * fConst35));
	fConst39 = (1.0 / fConst29);
	fConst40 = (0 - fConst16);
	fConst41 = (1.0 / (fConst20 * fConst27));
	fConst42 = (2 * (0 - fConst14));
	fConst43 = (1 + ((fConst10 - 1.0000000000000004) / fConst7));
	fConst44 = (1.0 / (1 + ((fConst10 + 1.0000000000000004) / fConst7)));
	fConst45 = (1 + fConst10);
	fConst46 = (0 - ((1 - fConst10) / fConst45));
	fConst47 = (0 - fConst10);
	fConst48 = (1.0 / (fConst45 * fConst18));
	fConst49 = (2 * (0 - fConst8));
	fConst50 = (1 + ((fConst16 - 1.0) / fConst13));
	fConst51 = (1.0 / (1 + ((1.0 + fConst16) / fConst13)));
	fConst52 = (0 - fConst25);
	fConst53 = (2 * (0 - fConst23));
	fConst54 = (1.0 / fConst5);
	fConst55 = (1.0 / tan((270.1769682087222 / iConst0)));
	fConst56 = (1 + fConst55);
	fConst57 = (0 - ((1 - fConst55) / fConst56));
	fConst58 = (0.027 / fConst56);
	fConst59 = (0.025 / fConst2);
	fConst60 = (1.0 / tan((414.6902302738527 / iConst0)));
	fConst61 = (1 + fConst60);
	fConst62 = (0 - ((1 - fConst60) / fConst61));
	fConst63 = (0.015 / fConst61);
	fConst64 = (1.0 / tan((609.4689747964198 / iConst0)));
	fConst65 = (1 + fConst64);
	fConst66 = (0 - ((1 - fConst64) / fConst65));
	fConst67 = (0.0082 / fConst65);
	clear_state_f();
}

inline void GxAmpFeedBack::run_12ax7_f(uint32_t count, float *input0, float *output0) //12ax7-feedback
{
    fslider0 = (*fslider0_);
    fslider1 = (*fslider1_);
    fslider2 = (*fslider2_);
    fslider3 = (*fslider3_);
    fslider4 = (*fslider4_);
	double 	fSlow0 = (0.0010000000000000009 * pow(10,(0.05 * fslider0)));
	double 	fSlow1 = (0.0010000000000000009 * pow(10,(0.05 * fslider1)));
	double 	fSlow2 = (1.000000000000001e-05 * fslider2);
	double 	fSlow3 = fslider3;
	double 	fSlow4 = pow(1e+01,(1.2 * fSlow3));
	double 	fSlow5 = pow(1e+01,(2 * fSlow3));
	double 	fSlow6 = (fConst44 * fSlow5);
	double 	fSlow7 = pow(1e+01,(0.8 * fSlow3));
	double 	fSlow8 = (fConst44 * pow(1e+01,(0.9 * fSlow3)));
	double 	fSlow9 = (2 * (fSlow3 - 0.5));
	double 	fSlow10 = (1 - max(0, (0 - fSlow9)));
	double 	fSlow11 = (1.25 * fSlow3);
	double 	fSlow12 = (1 - max(0, fSlow9));
	double 	fSlow13 = (0.0010000000000000009 * (-fslider4));
	for (uint32_t i=0; i<count; i++) {
		fRec0[0] = (fSlow0 + (0.999 * fRec0[1]));
		fRec8[0] = (fSlow1 + (0.999 * fRec8[1]));
		double fTemp0 = (fConst9 * fRec13[1]);
		fRec20[0] = (fSlow2 + (0.999 * fRec20[1]));
		double fTemp1 = (double)input0[i];
		double fTemp2 = (fTemp1 * fRec20[0]);
		fRec19[0] = (fTemp2 - (fConst36 * ((fConst34 * fRec19[2]) + (fConst32 * fRec19[1]))));
		double fTemp3 = (fRec19[2] + (fRec19[0] + (2 * fRec19[1])));
		fVec0[0] = fTemp3;
		fRec18[0] = ((fConst38 * ((fConst37 * fVec0[1]) + (fConst1 * fVec0[0]))) + (fConst3 * fRec18[1]));
		fRec17[0] = ((fConst39 * (fRec18[0] + fRec18[1])) + (fConst30 * fRec17[1]));
		fRec16[0] = (fRec17[0] - (fConst28 * ((fConst26 * fRec16[2]) + (fConst24 * fRec16[1]))));
		double fTemp4 = (fRec16[2] + (fRec16[0] + (2 * fRec16[1])));
		fVec1[0] = fTemp4;
		fRec15[0] = ((fConst41 * ((fConst40 * fVec1[1]) + (fConst16 * fVec1[0]))) + (fConst21 * fRec15[1]));
		fRec14[0] = (fRec15[0] - (fConst19 * ((fConst17 * fRec14[2]) + (fConst15 * fRec14[1]))));
		fRec13[0] = ((fConst19 * (((fConst14 * fRec14[0]) + (fConst42 * fRec14[1])) + (fConst14 * fRec14[2]))) - (fConst12 * ((fConst11 * fRec13[2]) + fTemp0)));
		double fTemp5 = max(-1, min(1, (fSlow4 * (fRec13[2] + (fConst12 * (fTemp0 + (fConst11 * fRec13[0])))))));
		fRec24[0] = ((fConst41 * (fVec1[0] + fVec1[1])) + (fConst21 * fRec24[1]));
		fRec23[0] = (fRec24[0] - (fConst19 * ((fConst17 * fRec23[2]) + (fConst15 * fRec23[1]))));
		double fTemp6 = (fRec23[2] + (fRec23[0] + (2 * fRec23[1])));
		fVec2[0] = fTemp6;
		fRec22[0] = ((fConst48 * ((fConst47 * fVec2[1]) + (fConst10 * fVec2[0]))) + (fConst46 * fRec22[1]));
		fRec21[0] = (fRec22[0] - (fConst44 * ((fConst43 * fRec21[2]) + (fConst9 * fRec21[1]))));
		double fTemp7 = max(-1, min(1, (fSlow6 * (((fConst8 * fRec21[0]) + (fConst49 * fRec21[1])) + (fConst8 * fRec21[2])))));
		double fTemp8 = (fConst9 * fRec25[1]);
		double fTemp9 = (fConst15 * fRec26[1]);
		fRec28[0] = ((fConst39 * ((fConst52 * fRec18[1]) + (fConst25 * fRec18[0]))) + (fConst30 * fRec28[1]));
		fRec27[0] = (fRec28[0] - (fConst28 * ((fConst26 * fRec27[2]) + (fConst24 * fRec27[1]))));
		fRec26[0] = ((fConst28 * (((fConst23 * fRec27[0]) + (fConst53 * fRec27[1])) + (fConst23 * fRec27[2]))) - (fConst51 * ((fConst50 * fRec26[2]) + fTemp9)));
		fRec25[0] = ((fRec26[2] + (fConst51 * (fTemp9 + (fConst50 * fRec26[0])))) - (fConst12 * ((fConst11 * fRec25[2]) + fTemp8)));
		double fTemp10 = max(-1, min(1, (fSlow7 * (fRec25[2] + (fConst12 * (fTemp8 + (fConst11 * fRec25[0])))))));
		fRec30[0] = ((fConst48 * (fVec2[0] + fVec2[1])) + (fConst46 * fRec30[1]));
		fRec29[0] = (fRec30[0] - (fConst44 * ((fConst43 * fRec29[2]) + (fConst9 * fRec29[1]))));
		double fTemp11 = max(-1, min(1, (fSlow8 * (fRec29[2] + (fRec29[0] + (2 * fRec29[1]))))));
		double fTemp12 = ((1.2589412 * (fTemp11 * (1 - (0.3333333333333333 * faustpower<2>(fTemp11))))) + (1.584893192 * ((fTemp10 * (1 - (0.3333333333333333 * faustpower<2>(fTemp10)))) + ((fTemp7 * (1 - (0.3333333333333333 * faustpower<2>(fTemp7)))) + (0.8413951417869425 * (fTemp5 * (1 - (0.3333333333333333 * faustpower<2>(fTemp5)))))))));
		fVec3[0] = fTemp12;
		fRec12[0] = ((fConst54 * (fVec3[0] + fVec3[1])) + (fConst6 * fRec12[1]));
		fRec31[0] = ((fConst58 * (fRec11[1] + fRec11[2])) + (fConst57 * fRec31[1]));
		double fTemp13 = max(-1, min(1, (fSlow5 * max(-0.7, min(0.7, fTemp2)))));
		double fTemp14 = (1 - fRec20[0]);
		fRec11[0] = (Ftube(TUBE_TABLE_12AX7_68k, (((fTemp1 * ((fSlow12 * fRec20[0]) + (fTemp14 * (1 + (fSlow11 * ((4 - (4 * fabs((fTemp1 * fTemp14)))) - 1)))))) + ((0.5 * (fTemp13 * (1 - (0.3333333333333333 * faustpower<2>(fTemp13))))) + (fRec31[0] + (fSlow10 * fRec12[0])))) - 1.581656)) - 191.42014814814814);
		fRec10[0] = ((fConst59 * ((fConst37 * fRec11[1]) + (fConst1 * fRec11[0]))) + (fConst3 * fRec10[1]));
		fRec34[0] = ((fConst63 * (fRec33[1] + fRec33[2])) + (fConst62 * fRec34[1]));
		fRec33[0] = (Ftube(TUBE_TABLE_12AX7_250k, ((fRec34[0] + fRec9[1]) - 1.204285)) - 169.71433333333334);
		fRec32[0] = ((fConst59 * ((fConst37 * fRec33[1]) + (fConst1 * fRec33[0]))) + (fConst3 * fRec32[1]));
		fRec35[0] = (fSlow13 + (0.999 * fRec35[1]));
		fRec9[0] = ((fRec35[0] * fRec32[0]) - fRec10[0]);
		double fTemp15 = (fRec9[0] * fRec8[0]);
		fVec4[0] = fTemp15;
		fRec7[0] = ((fConst54 * (fVec4[0] + fVec4[1])) + (fConst6 * fRec7[1]));
		fRec36[0] = ((fConst63 * (fRec6[1] + fRec6[2])) + (fConst62 * fRec36[1]));
		fRec6[0] = (Ftube(TUBE_TABLE_12AX7_250k, ((fRec36[0] + fRec7[0]) - 1.204285)) - 169.71433333333334);
		fRec5[0] = ((fConst59 * ((fConst37 * fRec6[1]) + (fConst1 * fRec6[0]))) + (fConst3 * fRec5[1]));
		fRec39[0] = ((fConst67 * (fRec38[1] + fRec38[2])) + (fConst66 * fRec39[1]));
		fRec38[0] = (Ftube(TUBE_TABLE_12AX7_250k, ((fRec39[0] + fRec4[1]) - 0.840702)) - 147.47536585365856);
		fRec37[0] = ((fConst59 * ((fConst37 * fRec38[1]) + (fConst1 * fRec38[0]))) + (fConst3 * fRec37[1]));
		fRec4[0] = ((fRec35[0] * fRec37[0]) + fRec5[0]);
		fRec3[0] = ((fConst54 * (fRec4[0] + fRec4[1])) + (fConst6 * fRec3[1]));
		fRec40[0] = ((fConst67 * (fRec2[1] + fRec2[2])) + (fConst66 * fRec40[1]));
		fRec2[0] = (Ftube(TUBE_TABLE_12AX7_250k, ((fRec40[0] + fRec3[0]) - 0.840702)) - 147.47536585365856);
		fRec1[0] = ((fConst59 * ((fConst37 * fRec2[1]) + (fConst1 * fRec2[0]))) + (fConst3 * fRec1[1]));
		output0[i] = (float)(fRec1[0] * fRec0[0]);
		// post processing
		fRec1[1] = fRec1[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec40[1] = fRec40[0];
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fRec37[1] = fRec37[0];
		fRec38[2] = fRec38[1]; fRec38[1] = fRec38[0];
		fRec39[1] = fRec39[0];
		fRec5[1] = fRec5[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec36[1] = fRec36[0];
		fRec7[1] = fRec7[0];
		fVec4[1] = fVec4[0];
		fRec9[1] = fRec9[0];
		fRec35[1] = fRec35[0];
		fRec32[1] = fRec32[0];
		fRec33[2] = fRec33[1]; fRec33[1] = fRec33[0];
		fRec34[1] = fRec34[0];
		fRec10[1] = fRec10[0];
		fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
		fRec31[1] = fRec31[0];
		fRec12[1] = fRec12[0];
		fVec3[1] = fVec3[0];
		fRec29[2] = fRec29[1]; fRec29[1] = fRec29[0];
		fRec30[1] = fRec30[0];
		fRec25[2] = fRec25[1]; fRec25[1] = fRec25[0];
		fRec26[2] = fRec26[1]; fRec26[1] = fRec26[0];
		fRec27[2] = fRec27[1]; fRec27[1] = fRec27[0];
		fRec28[1] = fRec28[0];
		fRec21[2] = fRec21[1]; fRec21[1] = fRec21[0];
		fRec22[1] = fRec22[0];
		fVec2[1] = fVec2[0];
		fRec23[2] = fRec23[1]; fRec23[1] = fRec23[0];
		fRec24[1] = fRec24[0];
		fRec13[2] = fRec13[1]; fRec13[1] = fRec13[0];
		fRec14[2] = fRec14[1]; fRec14[1] = fRec14[0];
		fRec15[1] = fRec15[0];
		fVec1[1] = fVec1[0];
		fRec16[2] = fRec16[1]; fRec16[1] = fRec16[0];
		fRec17[1] = fRec17[0];
		fRec18[1] = fRec18[0];
		fVec0[1] = fVec0[0];
		fRec19[2] = fRec19[1]; fRec19[1] = fRec19[0];
		fRec20[1] = fRec20[0];
		fRec8[1] = fRec8[0];
		fRec0[1] = fRec0[0];
	}
}

inline void GxAmpFeedBack::run_12AT7_f(uint32_t count, float *input0, float *output0) //12AT7-feedback
{
    fslider0 = (*fslider0_);
    fslider1 = (*fslider1_);
    fslider2 = (*fslider2_);
    fslider3 = (*fslider3_);
    fslider4 = (*fslider4_);
	double 	fSlow0 = (0.0010000000000000009 * pow(10,(0.05 * fslider0)));
	double 	fSlow1 = (0.0010000000000000009 * pow(10,(0.05 * fslider1)));
	double 	fSlow2 = (1.000000000000001e-05 * fslider2);
	double 	fSlow3 = fslider3;
	double 	fSlow4 = pow(1e+01,(1.2 * fSlow3));
	double 	fSlow5 = pow(1e+01,(2 * fSlow3));
	double 	fSlow6 = (fConst44 * fSlow5);
	double 	fSlow7 = pow(1e+01,(0.8 * fSlow3));
	double 	fSlow8 = (fConst44 * pow(1e+01,(0.9 * fSlow3)));
	double 	fSlow9 = (2 * (fSlow3 - 0.5));
	double 	fSlow10 = (1 - max(0, (0 - fSlow9)));
	double 	fSlow11 = (1.25 * fSlow3);
	double 	fSlow12 = (1 - max(0, fSlow9));
	double 	fSlow13 = (0.0010000000000000009 * (-fslider4));
	for (uint32_t i=0; i<count; i++) {
		fRec0[0] = (fSlow0 + (0.999 * fRec0[1]));
		fRec8[0] = (fSlow1 + (0.999 * fRec8[1]));
		double fTemp0 = (fConst9 * fRec13[1]);
		fRec20[0] = (fSlow2 + (0.999 * fRec20[1]));
		double fTemp1 = (double)input0[i];
		double fTemp2 = (fTemp1 * fRec20[0]);
		fRec19[0] = (fTemp2 - (fConst36 * ((fConst34 * fRec19[2]) + (fConst32 * fRec19[1]))));
		double fTemp3 = (fRec19[2] + (fRec19[0] + (2 * fRec19[1])));
		fVec0[0] = fTemp3;
		fRec18[0] = ((fConst38 * ((fConst37 * fVec0[1]) + (fConst1 * fVec0[0]))) + (fConst3 * fRec18[1]));
		fRec17[0] = ((fConst39 * (fRec18[0] + fRec18[1])) + (fConst30 * fRec17[1]));
		fRec16[0] = (fRec17[0] - (fConst28 * ((fConst26 * fRec16[2]) + (fConst24 * fRec16[1]))));
		double fTemp4 = (fRec16[2] + (fRec16[0] + (2 * fRec16[1])));
		fVec1[0] = fTemp4;
		fRec15[0] = ((fConst41 * ((fConst40 * fVec1[1]) + (fConst16 * fVec1[0]))) + (fConst21 * fRec15[1]));
		fRec14[0] = (fRec15[0] - (fConst19 * ((fConst17 * fRec14[2]) + (fConst15 * fRec14[1]))));
		fRec13[0] = ((fConst19 * (((fConst14 * fRec14[0]) + (fConst42 * fRec14[1])) + (fConst14 * fRec14[2]))) - (fConst12 * ((fConst11 * fRec13[2]) + fTemp0)));
		double fTemp5 = max(-1, min(1, (fSlow4 * (fRec13[2] + (fConst12 * (fTemp0 + (fConst11 * fRec13[0])))))));
		fRec24[0] = ((fConst41 * (fVec1[0] + fVec1[1])) + (fConst21 * fRec24[1]));
		fRec23[0] = (fRec24[0] - (fConst19 * ((fConst17 * fRec23[2]) + (fConst15 * fRec23[1]))));
		double fTemp6 = (fRec23[2] + (fRec23[0] + (2 * fRec23[1])));
		fVec2[0] = fTemp6;
		fRec22[0] = ((fConst48 * ((fConst47 * fVec2[1]) + (fConst10 * fVec2[0]))) + (fConst46 * fRec22[1]));
		fRec21[0] = (fRec22[0] - (fConst44 * ((fConst43 * fRec21[2]) + (fConst9 * fRec21[1]))));
		double fTemp7 = max(-1, min(1, (fSlow6 * (((fConst8 * fRec21[0]) + (fConst49 * fRec21[1])) + (fConst8 * fRec21[2])))));
		double fTemp8 = (fConst9 * fRec25[1]);
		double fTemp9 = (fConst15 * fRec26[1]);
		fRec28[0] = ((fConst39 * ((fConst52 * fRec18[1]) + (fConst25 * fRec18[0]))) + (fConst30 * fRec28[1]));
		fRec27[0] = (fRec28[0] - (fConst28 * ((fConst26 * fRec27[2]) + (fConst24 * fRec27[1]))));
		fRec26[0] = ((fConst28 * (((fConst23 * fRec27[0]) + (fConst53 * fRec27[1])) + (fConst23 * fRec27[2]))) - (fConst51 * ((fConst50 * fRec26[2]) + fTemp9)));
		fRec25[0] = ((fRec26[2] + (fConst51 * (fTemp9 + (fConst50 * fRec26[0])))) - (fConst12 * ((fConst11 * fRec25[2]) + fTemp8)));
		double fTemp10 = max(-1, min(1, (fSlow7 * (fRec25[2] + (fConst12 * (fTemp8 + (fConst11 * fRec25[0])))))));
		fRec30[0] = ((fConst48 * (fVec2[0] + fVec2[1])) + (fConst46 * fRec30[1]));
		fRec29[0] = (fRec30[0] - (fConst44 * ((fConst43 * fRec29[2]) + (fConst9 * fRec29[1]))));
		double fTemp11 = max(-1, min(1, (fSlow8 * (fRec29[2] + (fRec29[0] + (2 * fRec29[1]))))));
		double fTemp12 = ((1.2589412 * (fTemp11 * (1 - (0.3333333333333333 * faustpower<2>(fTemp11))))) + (1.584893192 * ((fTemp10 * (1 - (0.3333333333333333 * faustpower<2>(fTemp10)))) + ((fTemp7 * (1 - (0.3333333333333333 * faustpower<2>(fTemp7)))) + (0.8413951417869425 * (fTemp5 * (1 - (0.3333333333333333 * faustpower<2>(fTemp5)))))))));
		fVec3[0] = fTemp12;
		fRec12[0] = ((fConst54 * (fVec3[0] + fVec3[1])) + (fConst6 * fRec12[1]));
		fRec31[0] = ((fConst58 * (fRec11[1] + fRec11[2])) + (fConst57 * fRec31[1]));
		double fTemp13 = max(-1, min(1, (fSlow5 * max(-0.7, min(0.7, fTemp2)))));
		double fTemp14 = (1 - fRec20[0]);
		fRec11[0] = (Ftube(TUBE_TABLE_12AT7_68k, (((fTemp1 * ((fSlow12 * fRec20[0]) + (fTemp14 * (1 + (fSlow11 * ((4 - (4 * fabs((fTemp1 * fTemp14)))) - 1)))))) + ((0.5 * (fTemp13 * (1 - (0.3333333333333333 * faustpower<2>(fTemp13))))) + (fRec31[0] + (fSlow10 * fRec12[0])))) - 2.617753)) - 153.04618518518518);
		fRec10[0] = ((fConst59 * ((fConst37 * fRec11[1]) + (fConst1 * fRec11[0]))) + (fConst3 * fRec10[1]));
		fRec34[0] = ((fConst63 * (fRec33[1] + fRec33[2])) + (fConst62 * fRec34[1]));
		fRec33[0] = (Ftube(TUBE_TABLE_12AT7_250k, ((fRec34[0] + fRec9[1]) - 1.887332)) - 124.17786666666666);
		fRec32[0] = ((fConst59 * ((fConst37 * fRec33[1]) + (fConst1 * fRec33[0]))) + (fConst3 * fRec32[1]));
		fRec35[0] = (fSlow13 + (0.999 * fRec35[1]));
		fRec9[0] = ((fRec35[0] * fRec32[0]) - fRec10[0]);
		double fTemp15 = (fRec9[0] * fRec8[0]);
		fVec4[0] = fTemp15;
		fRec7[0] = ((fConst54 * (fVec4[0] + fVec4[1])) + (fConst6 * fRec7[1]));
		fRec36[0] = ((fConst63 * (fRec6[1] + fRec6[2])) + (fConst62 * fRec36[1]));
		fRec6[0] = (Ftube(TUBE_TABLE_12AT7_250k, ((fRec36[0] + fRec7[0]) - 1.887332)) - 124.17786666666666);
		fRec5[0] = ((fConst59 * ((fConst37 * fRec6[1]) + (fConst1 * fRec6[0]))) + (fConst3 * fRec5[1]));
		fRec39[0] = ((fConst67 * (fRec38[1] + fRec38[2])) + (fConst66 * fRec39[1]));
		fRec38[0] = (Ftube(TUBE_TABLE_12AT7_250k, ((fRec39[0] + fRec4[1]) - 1.256962)) - 96.7119512195122);
		fRec37[0] = ((fConst59 * ((fConst37 * fRec38[1]) + (fConst1 * fRec38[0]))) + (fConst3 * fRec37[1]));
		fRec4[0] = ((fRec35[0] * fRec37[0]) + fRec5[0]);
		fRec3[0] = ((fConst54 * (fRec4[0] + fRec4[1])) + (fConst6 * fRec3[1]));
		fRec40[0] = ((fConst67 * (fRec2[1] + fRec2[2])) + (fConst66 * fRec40[1]));
		fRec2[0] = (Ftube(TUBE_TABLE_12AT7_250k, ((fRec40[0] + fRec3[0]) - 1.256962)) - 96.7119512195122);
		fRec1[0] = ((fConst59 * ((fConst37 * fRec2[1]) + (fConst1 * fRec2[0]))) + (fConst3 * fRec1[1]));
		output0[i] = (float)(fRec1[0] * fRec0[0]);
		// post processing
		fRec1[1] = fRec1[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec40[1] = fRec40[0];
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fRec37[1] = fRec37[0];
		fRec38[2] = fRec38[1]; fRec38[1] = fRec38[0];
		fRec39[1] = fRec39[0];
		fRec5[1] = fRec5[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec36[1] = fRec36[0];
		fRec7[1] = fRec7[0];
		fVec4[1] = fVec4[0];
		fRec9[1] = fRec9[0];
		fRec35[1] = fRec35[0];
		fRec32[1] = fRec32[0];
		fRec33[2] = fRec33[1]; fRec33[1] = fRec33[0];
		fRec34[1] = fRec34[0];
		fRec10[1] = fRec10[0];
		fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
		fRec31[1] = fRec31[0];
		fRec12[1] = fRec12[0];
		fVec3[1] = fVec3[0];
		fRec29[2] = fRec29[1]; fRec29[1] = fRec29[0];
		fRec30[1] = fRec30[0];
		fRec25[2] = fRec25[1]; fRec25[1] = fRec25[0];
		fRec26[2] = fRec26[1]; fRec26[1] = fRec26[0];
		fRec27[2] = fRec27[1]; fRec27[1] = fRec27[0];
		fRec28[1] = fRec28[0];
		fRec21[2] = fRec21[1]; fRec21[1] = fRec21[0];
		fRec22[1] = fRec22[0];
		fVec2[1] = fVec2[0];
		fRec23[2] = fRec23[1]; fRec23[1] = fRec23[0];
		fRec24[1] = fRec24[0];
		fRec13[2] = fRec13[1]; fRec13[1] = fRec13[0];
		fRec14[2] = fRec14[1]; fRec14[1] = fRec14[0];
		fRec15[1] = fRec15[0];
		fVec1[1] = fVec1[0];
		fRec16[2] = fRec16[1]; fRec16[1] = fRec16[0];
		fRec17[1] = fRec17[0];
		fRec18[1] = fRec18[0];
		fVec0[1] = fVec0[0];
		fRec19[2] = fRec19[1]; fRec19[1] = fRec19[0];
		fRec20[1] = fRec20[0];
		fRec8[1] = fRec8[0];
		fRec0[1] = fRec0[0];
	}
}

inline void GxAmpFeedBack::run_6DJ8_f(uint32_t count, float *input0, float *output0) //6DJ8-feedback
{
    fslider0 = (*fslider0_);
    fslider1 = (*fslider1_);
    fslider2 = (*fslider2_);
    fslider3 = (*fslider3_);
    fslider4 = (*fslider4_);
	double 	fSlow0 = (0.0010000000000000009 * pow(10,(0.05 * fslider0)));
	double 	fSlow1 = (0.0010000000000000009 * pow(10,(0.05 * fslider1)));
	double 	fSlow2 = (1.000000000000001e-05 * fslider2);
	double 	fSlow3 = fslider3;
	double 	fSlow4 = pow(1e+01,(1.2 * fSlow3));
	double 	fSlow5 = pow(1e+01,(2 * fSlow3));
	double 	fSlow6 = (fConst44 * fSlow5);
	double 	fSlow7 = pow(1e+01,(0.8 * fSlow3));
	double 	fSlow8 = (fConst44 * pow(1e+01,(0.9 * fSlow3)));
	double 	fSlow9 = (2 * (fSlow3 - 0.5));
	double 	fSlow10 = (1 - max(0, (0 - fSlow9)));
	double 	fSlow11 = (1.25 * fSlow3);
	double 	fSlow12 = (1 - max(0, fSlow9));
	double 	fSlow13 = (0.0010000000000000009 * (-fslider4));
	for (uint32_t i=0; i<count; i++) {
		fRec0[0] = (fSlow0 + (0.999 * fRec0[1]));
		fRec8[0] = (fSlow1 + (0.999 * fRec8[1]));
		double fTemp0 = (fConst9 * fRec13[1]);
		fRec20[0] = (fSlow2 + (0.999 * fRec20[1]));
		double fTemp1 = (double)input0[i];
		double fTemp2 = (fTemp1 * fRec20[0]);
		fRec19[0] = (fTemp2 - (fConst36 * ((fConst34 * fRec19[2]) + (fConst32 * fRec19[1]))));
		double fTemp3 = (fRec19[2] + (fRec19[0] + (2 * fRec19[1])));
		fVec0[0] = fTemp3;
		fRec18[0] = ((fConst38 * ((fConst37 * fVec0[1]) + (fConst1 * fVec0[0]))) + (fConst3 * fRec18[1]));
		fRec17[0] = ((fConst39 * (fRec18[0] + fRec18[1])) + (fConst30 * fRec17[1]));
		fRec16[0] = (fRec17[0] - (fConst28 * ((fConst26 * fRec16[2]) + (fConst24 * fRec16[1]))));
		double fTemp4 = (fRec16[2] + (fRec16[0] + (2 * fRec16[1])));
		fVec1[0] = fTemp4;
		fRec15[0] = ((fConst41 * ((fConst40 * fVec1[1]) + (fConst16 * fVec1[0]))) + (fConst21 * fRec15[1]));
		fRec14[0] = (fRec15[0] - (fConst19 * ((fConst17 * fRec14[2]) + (fConst15 * fRec14[1]))));
		fRec13[0] = ((fConst19 * (((fConst14 * fRec14[0]) + (fConst42 * fRec14[1])) + (fConst14 * fRec14[2]))) - (fConst12 * ((fConst11 * fRec13[2]) + fTemp0)));
		double fTemp5 = max(-1, min(1, (fSlow4 * (fRec13[2] + (fConst12 * (fTemp0 + (fConst11 * fRec13[0])))))));
		fRec24[0] = ((fConst41 * (fVec1[0] + fVec1[1])) + (fConst21 * fRec24[1]));
		fRec23[0] = (fRec24[0] - (fConst19 * ((fConst17 * fRec23[2]) + (fConst15 * fRec23[1]))));
		double fTemp6 = (fRec23[2] + (fRec23[0] + (2 * fRec23[1])));
		fVec2[0] = fTemp6;
		fRec22[0] = ((fConst48 * ((fConst47 * fVec2[1]) + (fConst10 * fVec2[0]))) + (fConst46 * fRec22[1]));
		fRec21[0] = (fRec22[0] - (fConst44 * ((fConst43 * fRec21[2]) + (fConst9 * fRec21[1]))));
		double fTemp7 = max(-1, min(1, (fSlow6 * (((fConst8 * fRec21[0]) + (fConst49 * fRec21[1])) + (fConst8 * fRec21[2])))));
		double fTemp8 = (fConst9 * fRec25[1]);
		double fTemp9 = (fConst15 * fRec26[1]);
		fRec28[0] = ((fConst39 * ((fConst52 * fRec18[1]) + (fConst25 * fRec18[0]))) + (fConst30 * fRec28[1]));
		fRec27[0] = (fRec28[0] - (fConst28 * ((fConst26 * fRec27[2]) + (fConst24 * fRec27[1]))));
		fRec26[0] = ((fConst28 * (((fConst23 * fRec27[0]) + (fConst53 * fRec27[1])) + (fConst23 * fRec27[2]))) - (fConst51 * ((fConst50 * fRec26[2]) + fTemp9)));
		fRec25[0] = ((fRec26[2] + (fConst51 * (fTemp9 + (fConst50 * fRec26[0])))) - (fConst12 * ((fConst11 * fRec25[2]) + fTemp8)));
		double fTemp10 = max(-1, min(1, (fSlow7 * (fRec25[2] + (fConst12 * (fTemp8 + (fConst11 * fRec25[0])))))));
		fRec30[0] = ((fConst48 * (fVec2[0] + fVec2[1])) + (fConst46 * fRec30[1]));
		fRec29[0] = (fRec30[0] - (fConst44 * ((fConst43 * fRec29[2]) + (fConst9 * fRec29[1]))));
		double fTemp11 = max(-1, min(1, (fSlow8 * (fRec29[2] + (fRec29[0] + (2 * fRec29[1]))))));
		double fTemp12 = ((1.2589412 * (fTemp11 * (1 - (0.3333333333333333 * faustpower<2>(fTemp11))))) + (1.584893192 * ((fTemp10 * (1 - (0.3333333333333333 * faustpower<2>(fTemp10)))) + ((fTemp7 * (1 - (0.3333333333333333 * faustpower<2>(fTemp7)))) + (0.8413951417869425 * (fTemp5 * (1 - (0.3333333333333333 * faustpower<2>(fTemp5)))))))));
		fVec3[0] = fTemp12;
		fRec12[0] = ((fConst54 * (fVec3[0] + fVec3[1])) + (fConst6 * fRec12[1]));
		fRec31[0] = ((fConst58 * (fRec11[1] + fRec11[2])) + (fConst57 * fRec31[1]));
		double fTemp13 = max(-1, min(1, (fSlow5 * max(-0.7, min(0.7, fTemp2)))));
		double fTemp14 = (1 - fRec20[0]);
		fRec11[0] = (Ftube(TUBE_TABLE_6DJ8_68k, (((fTemp1 * ((fSlow12 * fRec20[0]) + (fTemp14 * (1 + (fSlow11 * ((4 - (4 * fabs((fTemp1 * fTemp14)))) - 1)))))) + ((0.5 * (fTemp13 * (1 - (0.3333333333333333 * faustpower<2>(fTemp13))))) + (fRec31[0] + (fSlow10 * fRec12[0])))) - 1.863946)) - 60.96496296296296);
		fRec10[0] = ((fConst59 * ((fConst37 * fRec11[1]) + (fConst1 * fRec11[0]))) + (fConst3 * fRec10[1]));
		fRec34[0] = ((fConst63 * (fRec33[1] + fRec33[2])) + (fConst62 * fRec34[1]));
		fRec33[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec34[0] + fRec9[1]) - 1.271609)) - 45.22606666666667);
		fRec32[0] = ((fConst59 * ((fConst37 * fRec33[1]) + (fConst1 * fRec33[0]))) + (fConst3 * fRec32[1]));
		fRec35[0] = (fSlow13 + (0.999 * fRec35[1]));
		fRec9[0] = ((fRec35[0] * fRec32[0]) - fRec10[0]);
		double fTemp15 = (fRec9[0] * fRec8[0]);
		fVec4[0] = fTemp15;
		fRec7[0] = ((fConst54 * (fVec4[0] + fVec4[1])) + (fConst6 * fRec7[1]));
		fRec36[0] = ((fConst63 * (fRec6[1] + fRec6[2])) + (fConst62 * fRec36[1]));
		fRec6[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec36[0] + fRec7[0]) - 1.271609)) - 45.22606666666667);
		fRec5[0] = ((fConst59 * ((fConst37 * fRec6[1]) + (fConst1 * fRec6[0]))) + (fConst3 * fRec5[1]));
		fRec39[0] = ((fConst67 * (fRec38[1] + fRec38[2])) + (fConst66 * fRec39[1]));
		fRec38[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec39[0] + fRec4[1]) - 0.797043)) - 32.799634146341475);
		fRec37[0] = ((fConst59 * ((fConst37 * fRec38[1]) + (fConst1 * fRec38[0]))) + (fConst3 * fRec37[1]));
		fRec4[0] = ((fRec35[0] * fRec37[0]) + fRec5[0]);
		fRec3[0] = ((fConst54 * (fRec4[0] + fRec4[1])) + (fConst6 * fRec3[1]));
		fRec40[0] = ((fConst67 * (fRec2[1] + fRec2[2])) + (fConst66 * fRec40[1]));
		fRec2[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec40[0] + fRec3[0]) - 0.797043)) - 32.799634146341475);
		fRec1[0] = ((fConst59 * ((fConst37 * fRec2[1]) + (fConst1 * fRec2[0]))) + (fConst3 * fRec1[1]));
		output0[i] = (float)(fRec1[0] * fRec0[0]);
		// post processing
		fRec1[1] = fRec1[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec40[1] = fRec40[0];
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fRec37[1] = fRec37[0];
		fRec38[2] = fRec38[1]; fRec38[1] = fRec38[0];
		fRec39[1] = fRec39[0];
		fRec5[1] = fRec5[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec36[1] = fRec36[0];
		fRec7[1] = fRec7[0];
		fVec4[1] = fVec4[0];
		fRec9[1] = fRec9[0];
		fRec35[1] = fRec35[0];
		fRec32[1] = fRec32[0];
		fRec33[2] = fRec33[1]; fRec33[1] = fRec33[0];
		fRec34[1] = fRec34[0];
		fRec10[1] = fRec10[0];
		fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
		fRec31[1] = fRec31[0];
		fRec12[1] = fRec12[0];
		fVec3[1] = fVec3[0];
		fRec29[2] = fRec29[1]; fRec29[1] = fRec29[0];
		fRec30[1] = fRec30[0];
		fRec25[2] = fRec25[1]; fRec25[1] = fRec25[0];
		fRec26[2] = fRec26[1]; fRec26[1] = fRec26[0];
		fRec27[2] = fRec27[1]; fRec27[1] = fRec27[0];
		fRec28[1] = fRec28[0];
		fRec21[2] = fRec21[1]; fRec21[1] = fRec21[0];
		fRec22[1] = fRec22[0];
		fVec2[1] = fVec2[0];
		fRec23[2] = fRec23[1]; fRec23[1] = fRec23[0];
		fRec24[1] = fRec24[0];
		fRec13[2] = fRec13[1]; fRec13[1] = fRec13[0];
		fRec14[2] = fRec14[1]; fRec14[1] = fRec14[0];
		fRec15[1] = fRec15[0];
		fVec1[1] = fVec1[0];
		fRec16[2] = fRec16[1]; fRec16[1] = fRec16[0];
		fRec17[1] = fRec17[0];
		fRec18[1] = fRec18[0];
		fVec0[1] = fVec0[0];
		fRec19[2] = fRec19[1]; fRec19[1] = fRec19[0];
		fRec20[1] = fRec20[0];
		fRec8[1] = fRec8[0];
		fRec0[1] = fRec0[0];
	}
}

void GxAmpFeedBack::connect(uint32_t port,void* data)
{
  switch ((PortIndex)port)
    {
    case AMP_MASTERGAIN:
      fslider0_ = (float*)data;
      break;
    case AMP_PREGAIN:
      fslider1_ = (float*)data;
      break;
    case AMP_WET_DRY:
      fslider2_ = (float*)data;
      break;
    case AMP_DRIVE:
      fslider3_ = (float*)data;
      break;
    case AMP_FEEDBACK:
      fslider4_ = (float*)data;
      break;
    default:
      break;
    }
}


void GxAmpFeedBack::init_static(uint32_t samplingFreq, GxAmpFeedBack *p)
{
	p->init(samplingFreq);
}

void GxAmpFeedBack::connect_static(uint32_t port,void* data, GxAmpFeedBack *p)
{
  p->connect(port, data);
}

/*
int32_t GxAmpFeedBack::register_par(const ParamReg& reg)
{
	fslider4_ = reg.registerVar("amp2.stage1.feedback","","SA","",&fslider4, 0.2, -0.6, 0.6, 0.01);
	fslider3_ = reg.registerVar("gxdistortion.drive","","SA","",&fslider3, 0.35, 0.0, 1.0, 0.01);
	fslider2_ = reg.registerVar("gxdistortion.wet_dry","","SA","",&fslider2, 1e+02, 0.0, 1e+02, 1.0);
	fslider1_ = reg.registerVar("amp2.stage1.Pregain","","SA","",&fslider1, -6.0, -2e+01, 2e+01, 0.1);
	fslider0_ = reg.registerVar("amp2.stage2.gain1","","SA","",&fslider0, -6.0, -2e+01, 2e+01, 0.1);
	return 0;
}
*/

