namespace tube3 {
// generated from file '../src/faust/tube3.dsp'

FAUSTFLOAT 	fslider0;
FAUSTFLOAT 	fslider1;
FAUSTFLOAT 	fslider2;
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
}

void compute(int count, float *input0, float *input1, float *output0, float *output1)
{
	float 	fSlow0 = faustpower<3>((0 - fslider0));
	float 	fSlow1 = (0 - fSlow0);
	float 	fSlow2 = powf(10,fslider1);
	float 	fSlow3 = (fSlow2 * fSlow1);
	float 	fSlow4 = max(-600, fSlow3);
	float 	fSlow5 = (0 - fSlow4);
	float 	fSlow6 = expf(fSlow5);
	float 	fSlow7 = (1 - fSlow6);
	float 	fSlow8 = (expf(fSlow4) * fSlow5);
	int 	iSlow9 = int((fSlow4 < -50));
	int 	iSlow10 = int((fabsf(fSlow3) > 0.0001f));
	float 	fSlow11 = ((iSlow10)?((iSlow9)?fSlow8:(fSlow4 / fSlow7)):(1 + (fSlow3 * (0.5f + (0.08333333333333333f * fSlow3)))));
	float 	fSlow12 = ((iSlow10)?((iSlow9)?fSlow8:((1.0f - ((fSlow4 * fSlow6) / fSlow7)) / fSlow7)):(0.5f + (fSlow3 * (0.16666666666666666f - (0.005555555555555556f * (faustpower<2>(fSlow2) * faustpower<2>(fSlow1)))))));
	float 	fSlow13 = (0.08333333333333333f * fSlow2);
	float 	fSlow14 = (1.0f / fSlow2);
	float 	fSlow15 = (fSlow2 * fSlow0);
	float 	fSlow16 = expf(fSlow15);
	float 	fSlow17 = (1.0f / fSlow15);
	float 	fSlow18 = (0 - fSlow14);
	int 	iSlow19 = int((fSlow15 > 50));
	float 	fSlow20 = fslider2;
	for (int i=0; i<count; i++) {
		float fTemp0 = (float)input0[i];
		float fTemp1 = (fTemp0 - fSlow0);
		float fTemp2 = (fSlow2 * fTemp1);
		float fTemp3 = max(-600, fTemp2);
		float fTemp4 = (0 - fTemp3);
		float fTemp5 = (fSlow2 * fTemp0);
		float fTemp6 = (0 - (fSlow0 + (fSlow20 * ((iSlow19)?((int((fTemp5 > 50)))?1e+10f:((int((fTemp5 < -50)))?fSlow18:(fSlow17 * ((fSlow16 * (fTemp1 / (1 - expf((0 - fTemp2))))) - fSlow0)))):(fSlow14 * ((((int((fabsf(fTemp2) > 0.0001f)))?((int((fTemp3 < -50)))?(expf(fTemp3) * fTemp4):(fTemp3 / (1 - expf(fTemp4)))):(1 + (fSlow2 * (fTemp1 * (0.5f + (fSlow13 * fTemp1)))))) - fSlow11) / fSlow12))))));
		float fTemp7 = (fSlow2 * fTemp6);
		float fTemp8 = max(-600, fTemp7);
		float fTemp9 = (0 - fTemp8);
		float fTemp10 = ((fSlow14 * (((int((fabsf(fTemp7) > 0.0001f)))?((int((fTemp8 < -50)))?(expf(fTemp8) * fTemp9):(fTemp8 / (1 - expf(fTemp9)))):(1 + (fSlow2 * (fTemp6 * (0.5f + (fSlow13 * fTemp6)))))) - fSlow11)) - fSlow0);
		float fTemp11 = (fSlow2 * fTemp10);
		float fTemp12 = max(-600, fTemp11);
		float fTemp13 = (0 - fTemp12);
		output0[i] = (FAUSTFLOAT)(0 - (fSlow14 * (((int((fabsf(fTemp11) > 0.0001f)))?((int((fTemp12 < -50)))?(expf(fTemp12) * fTemp13):(fTemp12 / (1 - expf(fTemp13)))):(1 + (fSlow2 * (fTemp10 * (0.5f + (fSlow13 * fTemp10)))))) - fSlow11)));
		float fTemp14 = (float)input1[i];
		float fTemp15 = (fTemp14 - fSlow0);
		float fTemp16 = (fSlow2 * fTemp15);
		float fTemp17 = max(-600, fTemp16);
		float fTemp18 = (0 - fTemp17);
		float fTemp19 = (fSlow2 * fTemp14);
		float fTemp20 = (0 - (fSlow0 + (fSlow20 * ((iSlow19)?((int((fTemp19 > 50)))?1e+10f:((int((fTemp19 < -50)))?fSlow18:(fSlow17 * ((fSlow16 * (fTemp15 / (1 - expf((0 - fTemp16))))) - fSlow0)))):(fSlow14 * ((((int((fabsf(fTemp16) > 0.0001f)))?((int((fTemp17 < -50)))?(expf(fTemp17) * fTemp18):(fTemp17 / (1 - expf(fTemp18)))):(1 + (fSlow2 * (fTemp15 * (0.5f + (fSlow13 * fTemp15)))))) - fSlow11) / fSlow12))))));
		float fTemp21 = (fSlow2 * fTemp20);
		float fTemp22 = max(-600, fTemp21);
		float fTemp23 = (0 - fTemp22);
		float fTemp24 = ((fSlow14 * (((int((fabsf(fTemp21) > 0.0001f)))?((int((fTemp22 < -50)))?(expf(fTemp22) * fTemp23):(fTemp22 / (1 - expf(fTemp23)))):(1 + (fSlow2 * (fTemp20 * (0.5f + (fSlow13 * fTemp20)))))) - fSlow11)) - fSlow0);
		float fTemp25 = (fSlow2 * fTemp24);
		float fTemp26 = max(-600, fTemp25);
		float fTemp27 = (0 - fTemp26);
		output1[i] = (FAUSTFLOAT)(0 - (fSlow14 * (((int((fabsf(fTemp25) > 0.0001f)))?((int((fTemp26 < -50)))?(expf(fTemp26) * fTemp27):(fTemp26 / (1 - expf(fTemp27)))):(1 + (fSlow2 * (fTemp24 * (0.5f + (fSlow13 * fTemp24)))))) - fSlow11)));
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("tube3.g","","S","",&fslider2, 1.0f, 0.5f, 2.0f, 0.1f);
	registerVar("tube3.dist","","S","",&fslider1, 0.0f, 0.0f, 1.7f, 0.01f);
	registerVar("tube3.q","","S","",&fslider0, 0.0f, 0.4f, 1.0f, 0.001f);
	registerInit(init);
}

} // end namespace tube3
