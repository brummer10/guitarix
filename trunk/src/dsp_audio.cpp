/******************************************************************************
*******************************************************************************

   							FAUST DSP
   dsp_audio.cpp
   the dsp audio processing for guitarix
*******************************************************************************
*******************************************************************************/

// denormal prevention is needed in the distortion unit for the low/high/cut part.
inline void add_dc (float &val)
{
    static const float anti_denormal = 1e-20;
    val += anti_denormal;
}

inline float clip (float x, float a)
{
float x1,x2;
float b = -a;
x1 = fabs (x-a);
x2 = fabs (x-b);
x = x1 + (a+b);
x -= x2;
x *= 0.5;
return (x);
}

// the fuzz unit run on sample base
inline float fuzz(float in, float threshold)
{
    if ( in > threshold)
    {
        in = threshold;
    }
    else if ( in < -threshold)
    {
        in = -threshold;
    }
    return in;
}

// foldback distortion, run on sample base
inline float foldback(float in, float threshold)
{
    if (threshold == 0) threshold = 0.01f;
    if (in>threshold || in<-threshold)
    {
        in= fabs(fabs(fmod(in - threshold, threshold*4)) - threshold*2) - threshold;
    }
    return in;
}

// tube unit to run on sample base, it's unused for now, dont know if we need it any more
inline float valve(float in, float out)
{
    float a = 2.000 ;
    float b = 1.000 ;

    if ( in >= 0.0 )
    {
        out = a * in - b * in * in;
    }
    else
    {
        out = a * in + b * in * in;
    }
    return out;
}

// oversample the input signal 2*, give a nice antialised effect
inline void over_sample(float **input,float **output, int sf)
{
    float * in = input[0];
    float * out = output[0];
    float x = in[0];
    float y = 0;
    for (int i=0; i<sf; i++)
    {
        x = in[i];
        *out++ = x;
        y = in[i+1];
        *out++ = (y+ x)*0.5;
    }
}

// downsample the processed signal to the jack_buffer size
inline void down_sample(float **input,float **output, int sf)
{
    float * in = input[0];
    float * out = output[0];
    float x = in[0];
    float y = 0;
    for (int i=0; i<sf; i++)
    {

        y = *in++;
        out[i] = x*0.75 + y*0.5;
        x = *in++;
    }
}

// anti aliasing the sine wav, this unit can nicly run oversampeled
inline void AntiAlias (int sf, float** input, float** output)
{
    float* in = input[0];
    float* out = output[0];
    float alias[frag] ;
    int state = 0;
    for (int i=0; i<sf; i++)
    {
        float x = *in++;
        float a = alias[state];
        alias[state++] = x + a * faas1;
        if (state > 1.5)
            state = 0;
        *out++ = a ;
    }
}

// the resonace tube unit on frame base
inline void reso_tube (int fuzzy, int sf,float reso, float vibra, float** input, float** output)
{
    float* in = input[0];
    float* out = output[0];
    float ot = 0;
    float x = in[0];
    float a = 2.000 ;
    float b = 1.000 ;
    float 	fSlowRESO0 = reso;
    // float 	fSlowRESO1 = vibra;

    double c = 0.5;
    //----- resonator
    int 	iSlowRESO2 = int((int((vibra - 1)) & 4095));
    int 	iSlowRESO3 = int((int(vibra) & 4095));

    for (int i=0; i<sf; i++)
    {
        x = in[i];
        if ( x >= 0.0 )
        {
            ot = ((a * x - b * x * x) -x)*c;
        }
        else
        {
            ot =  ((a * x + b * x * x) -x)*c;
        }

        float fTempRESO0 = (ot + (fSlowRESO0 * fRecRESO0[1]));
        fVecRESO0[IOTARESO&4095] = fTempRESO0;
        fRecRESO0[0] = (0.5f * (fVecRESO0[(IOTARESO-iSlowRESO3)&4095] + fVecRESO0[(IOTARESO-iSlowRESO2)&4095]));
        ot = fRecRESO0[0];

        *out++ = fuzz(x + ot*fuzzy*0.5,0.7);
        // post processing
        fRecRESO0[1] = fRecRESO0[0];
        IOTARESO = IOTARESO+1;

    }
}


// the oscilate tube unit on frame base
inline void osc_tube (int fuzzy, int sf,float reso, float vibra, float** input, float** output)
{
    float* in = input[0];
    float* out = output[0];
    float ot = 0;
    float x = in[0];
    float a = 2.000 ;
    float b = 1.000 ;
    float 	fSlowRESO0 = reso;
    // float 	fSlowRESO1 = vibra;
    //----- oscillator


    double c = 0.5;
    //----- resonator
    int 	iSlowRESO2 = int((int((vibra - 1)) & 4095));
    int 	iSlowRESO3 = int((int(vibra) & 4095));



    for (int i=0; i<sf; i++)
    {
        x = in[i];
        if ( x >= 0.0 )
        {
            ot = ((a * x - b * x * x) -x)*c;
        }
        else
        {
            ot =  ((a * x + b * x * x) -x)*c;
        }

				iVecoscb0[0] = 1;
				fRecoscb0[0] = (0 - (((fRecoscb0[2] + (fConstoscb0 * fRecoscb0[1])) + iVecoscb0[1]) - 1));
				float oscb = fRecoscb0[0];

        float fTempRESO0 = (ot + (fSlowRESO0 * fRecRESO0[1]));
        fVecRESO0[IOTARESO&4095] = fTempRESO0;
        fRecRESO0[0] = (0.5f * (fVecRESO0[(IOTARESO-iSlowRESO3)&4095] + fVecRESO0[(IOTARESO-iSlowRESO2)&4095]));
        ot = fRecRESO0[0] * (3+oscb)*0.25f;

                float sp0 = ot;
				fVecsp0[0] = sp0;
				fRecsp3[0] = (fConstsp9 * ((fVecsp0[0] - fVecsp0[1]) + (fConstsp8 * fRecsp3[1])));
				fRecsp2[0] = (fConstsp9 * ((fRecsp3[0] - fRecsp3[1]) + (fConstsp8 * fRecsp2[1])));
				fRecsp1[0] = (fRecsp2[0] - (fConstsp6 * ((fConstsp5 * fRecsp1[2]) + (fConstsp1 * fRecsp1[1]))));
				fRecsp0[0] = ((fConstsp6 * (fRecsp1[2] + (fRecsp1[0] + (2 * fRecsp1[1])))) - (fConstsp4 * ((fConstsp3 * fRecsp0[2]) + (fConstsp1 * fRecsp0[1]))));
				ot = (fConstsp4 * (fRecsp0[2] + (fRecsp0[0] + (2 * fRecsp0[1]))));


        *out++ = clip(x + ot*fuzzy*0.5,0.7);
        // post processing
        fRecRESO0[1] = fRecRESO0[0];
        IOTARESO = IOTARESO+1;

				fRecoscb0[2] = fRecoscb0[1]; fRecoscb0[1] = fRecoscb0[0];
				iVecoscb0[1] = iVecoscb0[0];

                fRecsp0[2] = fRecsp0[1]; fRecsp0[1] = fRecsp0[0];
				fRecsp1[2] = fRecsp1[1]; fRecsp1[1] = fRecsp1[0];
				fRecsp2[1] = fRecsp2[0];
				fRecsp3[1] = fRecsp3[0];
				fVecsp0[1] = fVecsp0[0];
    }
}

// the tube unit on frame base, it's also the drive unit just with other variables
inline void fuzzy_tube (int fuzzy,int mode, int sf, float** input, float** output)
{
    float* in = input[0];
    float* out = output[0];
    float ot = 0;
    float x = in[0];
    float a = 2.000 ;
    float b = 1.000 ;
    double c = 0.5;

    if (mode == 1)
    {
        a = 4.000 ;
        b = 4.000 ;
        c = 0.125;
    }

    for (int i=0; i<sf; i++)
    {
        x = in[i];
        if ( x >= 0.0 )
        {
            ot = ((a * x - b * x * x) -x)*c;
        }
        else
        {
            ot =  ((a * x + b * x * x) -x)*c;
        }
        *out++ = fuzz(x + ot*fuzzy*0.5,0.7);
    }
}

// it isn't normalize, it's more a waveshaper funktion
inline float normalize(float in, float atan_shape, float shape)
{
    float out = atan_shape * atan(in*shape);
    return out;
}

// the preamp on frame base, it's a gloubi-boulga followed by a third-degree polynomial
// and then the "normalize", output will smoth down by 0.75
inline void preamp(int sf, float** input, float** output,float atan_shape,float f_atan)
{
    float* in = input[0];
    float* out = output[0];

    for (int i=0; i<sf; i++)
    {
        float  x = in[i] ;
        float  fTemp0in = (x-0.15*(x*x))-(0.15*(x*x*x));
        x = 1.5f * fTemp0in - 0.5f * fTemp0in *fTemp0in * fTemp0in;
        fTemp0in = normalize(x,atan_shape,f_atan);
        out[i] = fTemp0in*0.75;

    }

}

// this is the process callback called from jack
virtual void compute (int count, float** input, float** output)
{
    if ((checky != 0) && (NO_CONNECTION == 0 ) )      // play
    {
        // precalculate values with need update peer frame
        // compressor
        float   fSlowcom0 = fentrycom0;
        float   fSlowcom1 = expf((0 - (fConstcom2 / max(fConstcom2, fslidercom0))));
        float   fSlowcom2 = expf((0 - (fConstcom2 / max(fConstcom2, fslidercom1))));
        float   fSlowcom3 = fentrycom1;
        float   fSlowcom4 = (1.000000f / (1.000000e-03f + fSlowcom3));
        float   fSlowcom5 = fentrycom2;
        // compressor end
        float 	fSlow0 = fslider0;
        float 	fSlow1 = powf(10, (2.500000e-02f * fslider1));
        float 	fSlow2 = (1 + fSlow1);
        float 	fSlow3 = (fConst1 * fSlow2);
        float 	fSlow4 = (2 * (0 - ((1 + fSlow3) - fSlow1)));
        float 	fSlow5 = (fConst1 * (fSlow1 - 1));
        float 	fSlow6 = (fConst2 * sqrtf(fSlow1));
        float 	fSlow7 = (fSlow2 - (fSlow6 + fSlow5));
        float 	fSlow8 = powf(10, (2.500000e-02f * fslider2));
        float 	fSlow9 = (1 + fSlow8);
        float 	fSlow10 = (fConst4 * fSlow9);
        float 	fSlow11 = (0 - (2 * ((fSlow8 + fSlow10) - 1)));
        float 	fSlow12 = (fConst5 * sqrtf(fSlow8));
        float 	fSlow13 = (fConst4 * (fSlow8 - 1));
        float 	fSlow14 = ((1 + (fSlow8 + fSlow13)) - fSlow12);
        float 	fSlow15 = checky;
        float 	fSlow16 = (7.118644f * fSlow15);
        float 	fSlow18 = (9.999871e-04f * powf(10, (5.000000e-02f * fslider3)));
        float 	fSlow19 = (1.0f - fslider4);
        float 	fSlow20 = fslider5;
        float 	fSlow23 = (1.0f / tanf((fConst6 * fentry0)));
        float 	fSlow24 = (fSlow23 - 1);
        float 	fSlow25 = (1.0f / (1 + fSlow23));
        float 	fSlow26 = (1.0f / tanf((fConst8 * (fConst7 - (6.283185f * fentry1)))));
        float 	fSlow27 = (1 + fSlow26);
        float 	fSlow28 = (1.0f / fSlow27);
        float 	fSlow29 = (0 - ((fSlow26 - 1) / fSlow27));
        float 	fSlow31 = tanf((fConst6 * fslider6));
        float 	fSlow32 = (2 * (1 - (1.0f / (fSlow31 * fSlow31))));
        float 	fSlow33 = (1.0f / fSlow31);
        float 	fSlow34 = (1 + ((fSlow33 - 0.765367f) / fSlow31));
        float 	fSlow35 = (1.0f / (1 + ((0.765367f + fSlow33) / fSlow31)));
        float 	fSlow36 = (1 + ((fSlow33 - 1.847759f) / fSlow31));
        float 	fSlow37 = (1.0f / (1 + ((1.847759f + fSlow33) / fSlow31)));
        float 	fSlow38 = (fConst6 * fslider7);
        float 	fSlow39 = (1.0f / (1 + fSlow38));
        float 	fSlow40 = (1 - fSlow38);
        float 	fSlow42 = fslider8;
        float 	fSlow43 = powf(10.0f, (2 * fslider9));
        float 	fSlow44 = (9.999871e-04f * powf(10, (5.000000e-02f * (fslider10 - 10))));
        float 	fSlow46 = (fSlow9 - (fSlow12 + fSlow13));
        float 	fSlow47 = (2 * (0 - ((1 + fSlow10) - fSlow8)));
        float 	fSlow48 = (fSlow8 + fSlow12);
        float 	fSlow49 = ((1 + fSlow48) - fSlow13);
        float 	fSlow50 = (1.0f / (1 + (fSlow13 + fSlow48)));
        float 	fSlow51 = (fSlow1 * ((1 + (fSlow1 + fSlow5)) - fSlow6));
        float 	fSlow52 = (fSlow1 + fSlow6);
        float 	fSlow53 = (fSlow1 * (1 + (fSlow5 + fSlow52)));
        float 	fSlow54 = (((fSlow1 + fSlow3) - 1) * (0 - (2 * fSlow1)));
        float 	fSlow55 = (1.0f / ((1 + fSlow52) - fSlow5));
        float 	fSlow56 = fslider11;
        float 	fSlow57 = (9.999872e-05f * powf(4.0f, fSlow56));
        float 	fSlow58 = fslider13;
        float 	fSlow59 = ((1 - max(0, (0 - fSlow58))) * fslider12);
        float 	fSlow60 = powf(2.0f, (2.3f * fSlow56));
        float 	fSlow61 = (1 - (fConst10 * (fSlow60 / powf(2.0f, (1.0f + (2.0f * (1.0f - fSlow56)))))));
        float 	fSlow62 = (9.999871e-04f * (0 - (2.0f * (fSlow61 * cosf((fConst9 * fSlow60))))));
        float 	fSlow63 = (9.999871e-04f * (fSlow61 * fSlow61));
        float 	fSlow64 = (1 - max(0, fSlow58));
        float 	fSlow66 = (0.5 + fslider14);
        float 	fSlow67 = (2 * (1 - fSlow66));
        float 	fSlow68 = fslider15;
        float 	fSlow69 = (1 - fSlow68);
        float 	fSlow70 = (0.7f + (0.28f * fslider16));
        float 	fSlow72 = (9.999871e-04f * powf(10, (5.000000e-02f * fslider17)));
        float 	fSlow74 = (1.000000e-02f * fslider19);
        float 	fSlow76 = expf((0 - (fConst6 * fslider20)));
        float 	fSlow77 = (2 * cosf((fConst12 * fslider21)));
        float 	fSlow78 = (0.5f * (fslider22 * (1 - (fSlow76 * fSlow76))));
        float 	fSlow80 = fslider23;
        float 	fSlow81 = fslider24;
        float 	fSlow82 = (1 - max(0, (0 - fSlow81)));
        float 	fSlow83 = fslider25;
        float 	fSlow84 = (1 - max(0, fSlow83));
        float 	fSlow85 = (fSlow84 * fSlow82);
        float 	fSlow86 = (1 - max(0, fSlow81));
        float 	fSlow87 = (fSlow84 * fSlow86);
        float 	fSlow89 = (1 - max(0, (0 - fSlow83)));
        float 	fSlow90 = (fSlow89 * fSlow82);
        float 	fSlow91 = (fSlow89 * fSlow86);
        float   drivem1 = drive - 1.0f;
        float   fSlowover0 = (9.999871e-04f * powf(10, (5.000000e-02f * (drive*-0.5))));
        float   fSlowvib0 = fvibrato;
        float   sumt = 0;
        float   atan_shape = 1.0/atan(fatan);
        float   f_atan = fatan;
        float   threshold = fthreshold;
        float   fTemps39 = 10;//fslider39;
        float	f_resotube1 = fresotube1;

        float 	f_resotube2 = fresotube2;


        int 	ifuzzytube = int(ffuzzytube);
        int 	itube = int(ftube);

        int 	iresotube3 = int(fresotube3);
        int 	itube3 = int(ftube3);
        int 	ipredrive = int(fpredrive);
        int 	iprdr = int(fprdr);
        int     iupsample = int(fupsample);
        // the extra port register can only run clean on frame base, therfor the
        // variable runjc must check on frame base, not in the inner loop.
        int     irunjc = runjc;
        int 	iSlow21 = int((int((fSlow20 - 1)) & 4095));
        int 	iSlow22 = int((int(fSlow20) & 4095));
        int 	iSlow30 = int(fcheckbox2);
        int 	iSlow41 = int(fcheckbox3);
        int 	iSlow45 = int(fcheckbox4);
        int 	iSlow65 = int(fcheckbox5);
        int 	iSlow71 = int(fcheckbox6);
        int 	iSlow73 = int((1 + int((int((int((fConst11 * fslider18)) - 1)) & 131071))));
        int 	iSlow75 = int(fcheckbox7);
        int 	iSlow79 = int(fcheckbox8);
        int 	iSlow88 = int(checkbox7);
        int     icheckboxcom1 = int(fcheckboxcom1);
        int     icheckbox1 = int(fcheckbox1);
        int     ioverdrive4 = int(foverdrive4);
        int     cts = 0;
        int     ifuse = ffuse;
        int     iTemps39 = 10;//int(fslider39);
        // pointer to the jack_buffer
        float*  input0 = input[0];
        // copy clean audio input for the tuner and midi_process
        if ((shownote == 1) || (playmidi == 1))
        {
            for (int i=0; i<count; i++)  checkfreq [i] = input0[i];
        }
        // run pre_funktions on frame base
        // 2*oversample
        if (iupsample == 1)
        {
            over_sample(input,&oversample,count);
          //  if (icheckbox1 == 1)  preamp(count*2,&oversample,&oversample,atan_shape,f_atan);
            if (itube == 1)    fuzzy_tube(ifuzzytube, 0,count*2,&oversample,&oversample);
            if (itube3 == 1)   reso_tube(iresotube3,count*2,f_resotube1, f_resotube2, &oversample,&oversample);
            if (iprdr == 1)    fuzzy_tube(ipredrive, 1,count*2,&oversample,&oversample);
            if (antialis0 == 1)  AntiAlias(count*2,&oversample,&oversample);
            down_sample(&oversample,input,count);
        }
        // or plain sample
        else
        {
         //   if (icheckbox1 == 1)  preamp(count,input,input,atan_shape,f_atan);
            if (itube == 1)    fuzzy_tube(ifuzzytube, 0,count,input,input);
            if (itube3 == 1)   osc_tube(iresotube3,count,f_resotube1, f_resotube2,input,input);
            if (iprdr == 1)    fuzzy_tube(ipredrive, 1,count,input,input);
            if (antialis0 == 1)  AntiAlias(count,input,input);
        }
        // pointers to the jack_output_buffers
        float* output0 = output[2];
        float* output1 = output[0];
        float* output2 = output[3];
        float* output3 = output[1];
        // start the inner loop count = jack_frame
        for (int i=0; i<count; i++)
        {
            float 	S0[2];
            float 	S1[2];
            float 	S2[2];
            float 	S3[2];
            float 	S4[2];
            float 	S5[2];
            // when the ocilloscope draw wav by sample (mode 3) get the input value
            if (showwave == 1) vivi = input0[i];

            if ((shownote == 1) || (playmidi == 1)) // enable tuner when show note or play midi
            {
                float fTemphp0 = checkfreq [i]*2;
                // low and highpass filter
                tunerstage1=tunerstage1+(tunerfilter*(fTemphp0-tunerstage1));
                tunerstage2=tunerstage2+(tunerfilter*(tunerstage1-tunerstage2));
                tunerstageh1=tunerstageh1+(tunerfilterh*(tunerstage2-tunerstageh1));
                tunerstageh2=tunerstageh2+(tunerfilterh*(tunerstageh1-tunerstageh2));
                fTemphp0 = tunerstage2-tunerstageh2;
                // waveshaper
                float fTemphps0 = (1.5f * fTemphp0 - 0.5f * fTemphp0 *fTemphp0 * fTemphp0);
                // now run a fft
                fVechp0[0] = fTemphps0;
                fRechp0[0] = ((fConsthp3 * (fVechp0[0] - fVechp0[1])) + (fConsthp2 * fRechp0[1]));
                float fTemphp1  = fRechp0[0];
                int iTempt0 = (1 + iRect2[1]);
                float fTempt1 = (1.0f / tanf((fConstan0 * max(100, fRect0[1]))));
                float fTempt2 = (1 + fTempt1);
                fVect0[0] = fTemphp1;
                fRect5[0] = (fConstan3 * ((fVect0[0] - fVect0[1]) + (fConstan2 * fRect5[1])));
                fVect1[0] = (fRect5[0] / fTempt2);
                fRect4[0] = (fVect1[1] + ((fRect5[0] + ((fTempt1 - 1) * fRect4[1])) / fTempt2));
                int iTempt4 = ((fRect4[1] < 0) & (fRect4[0] >= 0));
                iRect3[0] = (iTempt4 + (iRect3[1] % iTemps39));
                iRect2[0] = ((1 - (iTempt4 & (iRect3[0] ==  fTemps39))) * iTempt0);
                int iTempt5 = (iRect2[0] == 0);
                iRect1[0] = ((iTempt5 * iTempt0) + ((1 - iTempt5) * iRect1[1]));
                fRect0[0] = (fSamplingFreq * ((fTemps39 / max(iRect1[0], 1)) - (fTemps39 * (iRect1[0] == 0))));
                // get the frequence here
                float fConsta4s = fRect0[0];
                // smoth tuner output by rms the value peer frame
                cts += 1;
                sumt += sqrf(fConsta4s);
                fConsta4 = sqrtf(sumt/cts);
            }
            else if (shownote == 0)
            {
                fConsta1 = 1000.0f;
                shownote = 2;
            }

            if (icheckboxcom1 == 1)     // compressor
            {
                add_dc(input0[i]);
                float fTempcom0 = input0[i];
                fReccom1[0] = ((fConstcom1 * fabsf(fTempcom0)) + (fConstcom0 * fReccom1[1]));
                float fTempcom2 = max(fReccom1[0], fReccom1[0]);
                float fTempcom3 = ((fSlowcom2 * (fReccom0[1] >= fTempcom2)) + (fSlowcom1 * (fReccom0[1] < fTempcom2)));
                fReccom0[0] = ((fTempcom2 * (1 - fTempcom3)) + (fReccom0[1] * fTempcom3));
                float fTempcom4 = max(0, ((fSlowcom3 + (20 * log10f(fReccom0[0]))) - fSlowcom0));
                float fTempcom5 = min(1, max(0, (fSlowcom4 * fTempcom4)));
                float fTempcom6 = (fSlowcom5 * fTempcom5);
                float fTempcom7 = ((fTempcom4 / ((1 + fTempcom6) - fTempcom5)) * (fTempcom5 - fTempcom6));
                float fTempcom8 = powf(10, (5.000000e-02f * fTempcom7));
                fVec0[0]= (fTempcom0 * fTempcom8);
            }
            else
            {
                add_dc(input0[i]);
                fVec0[0] = input0[i]; // compressor end
            }

            S5[0] = (fSlow15 * fVec0[1]);
            S5[1] = (fSlow16 * fVec0[1]);
            fRec4[0] = ((0.999f * fRec4[1]) + fSlow18);
            float fTemp0 = (fRec4[0] * S5[0]);

            // I have move the preamp to the frame based section, leef it here for . . .
              if (icheckbox1 == 1)     // preamp
              {
                  float  in = fTemp0 ;
                  float  fTemp0in = (in-0.15*(in*in))-(0.15*(in*in*in));
                  in = 1.5f * fTemp0in - 0.5f * fTemp0in *fTemp0in * fTemp0in;
                  fTemp0in = normalize(in,atan_shape,f_atan);
                  fTemp0 = valve(fTemp0in,fTemp0in)*0.75;
                  fTemp0 = fuzz(fTemp0in,0.7);
              }  //preamp ende 


            fRec3[0] = fTemp0;
            // vibrato
            if (fresoon == 1.0) fRec3[0] = fuzz (0.5f * ((2.0 * fTemp0) + ( fSlowvib0* fRec3[1])),0.7);  //resonanz 1.76f
            S4[0] = fRec3[0];

            if (ioverdrive4 == 1)     // overdrive
            {
                float fTempdr0 = (fTemp0 + S4[0]) * 0.5;
                float fTempdr1 = fabs(fTempdr0);
                fRecover0[0] = (fSlowover0 + (0.999000f * fRecover0[1]));
                S4[0] = (fTempdr0*(fTempdr1 + drive)/(fTempdr0*fTempdr0 + drivem1*fTempdr1 + 1.0f)) * fRecover0[0];
                fTemp0 = S4[0];
            }

            if (iSlow45 == 1)     // distortion
            {
                float 	S6[2];
                float 	S7[2];
                float 	S8[2];
                float fTemp1 = (fTemp0 + (fSlow19 * fRec6[1]));
                fVec1[IOTA&4095] = fTemp1;
                fRec6[0] = (0.5f * (fVec1[(IOTA-iSlow22)&4095] + fVec1[(IOTA-iSlow21)&4095]));
                S8[0] = fRec6[0];
                fVec2[0] = (fSlow25 * fRec6[0]);
                fRec8[0] = (fVec2[1] + (fSlow25 * (fRec6[0] + (fSlow24 * fRec8[1]))));
                float fTemp2 = (fSlow28 * fRec8[0]);
                fVec3[0] = fTemp2;
                fRec7[0] = ((fVec3[0] + (fSlow29 * fRec7[1])) - fVec3[1]);
                S8[1] = fRec7[0];
                float fTemp3 = S8[iSlow30];
                S7[0] = fTemp3;
                add_dc(S7[0]);
                fVec4[0] = (fSlow39 * fTemp3);
                fRec12[0] = ((fSlow39 * (fTemp3 + (fSlow40 * fRec12[1]))) - fVec4[1]);
                fVec5[0] = (fSlow39 * fRec12[0]);
                fRec11[0] = ((fSlow39 * (fRec12[0] + (fSlow40 * fRec11[1]))) - fVec5[1]);
                fRec10[0] = (fRec11[0] - (fSlow37 * ((fSlow36 * fRec10[2]) + (fSlow32 * fRec10[1]))));
                fRec9[0] = ((fSlow37 * (fRec10[2] + (fRec10[0] + (2 * fRec10[1])))) - (fSlow35 * ((fSlow34 * fRec9[2]) + (fSlow32 * fRec9[1]))));
                S7[1] = (fSlow35 * (fRec9[2] + (fRec9[0] + (2 * fRec9[1]))));
                add_dc(S7[1]);
                float fTemp4 = max(-1, min(1, (fSlow43 * (fSlow42 + S7[iSlow41]))));
                add_dc(fTemp4);
                float fTemp5 = (fTemp4 * (1 - (0.333333f * (fTemp4 * fTemp4))));
                fVec6[0] = fTemp5;
                fRec5[0] = ((fVec6[0] + (0.995f * fRec5[1])) - fVec6[1]);
                fRec13[0] = (fSlow44 + (0.999f * fRec13[1]));
                float fTemp6 = (fRec13[0] * fRec5[0]);
                S6[0] = fTemp6;
                fVec7[0] = (fSlow39 * fTemp6);
                fRec17[0] = ((fSlow39 * (fTemp6 + (fSlow40 * fRec17[1]))) - fVec7[1]);
                fVec8[0] = (fSlow39 * fRec17[0]);
                fRec16[0] = ((fSlow39 * (fRec17[0] + (fSlow40 * fRec16[1]))) - fVec8[1]);
                fRec15[0] = (fRec16[0] - (fSlow37 * ((fSlow36 * fRec15[2]) + (fSlow32 * fRec15[1]))));
                fRec14[0] = ((fSlow37 * (fRec15[2] + (fRec15[0] + (2 * fRec15[1])))) - (fSlow35 * ((fSlow34 * fRec14[2]) + (fSlow32 * fRec14[1]))));
                S6[1] = (fSlow35 * (fRec14[2] + (fRec14[0] + (2 * fRec14[1]))));
                S4[1] = S6[iSlow41];
                float fTemp7 = S4[iSlow45];
                fVec9[0] = fTemp7;
            }
            else  fVec9[0] = S4[0];   		// distortion end

            fRec2[0] = (fSlow50 * ((fSlow8 * (((fSlow49 * fVec9[0]) + (fSlow47 * fVec9[1])) + (fSlow46 * fVec9[2]))) - ((fSlow14 * fRec2[2]) + (fSlow11 * fRec2[1]))));
            fRec1[0] = (fSlow55 * ((((fSlow54 * fRec2[1]) + (fSlow53 * fRec2[0])) + (fSlow51 * fRec2[2])) + (0 - ((fSlow7 * fRec1[2]) + (fSlow4 * fRec1[1])))));

            float fTemp8 = fRec1[0];
            if (iSlow65 == 1)    //crybaby
            {
                S3[0] = fRec1[0];
                fRec19[0] = (fSlow57 + (0.999f * fRec19[1]));
                fRec20[0] = (fSlow62 + (0.999f * fRec20[1]));
                fRec21[0] = (fSlow63 + (0.999f * fRec21[1]));
                fRec18[0] = (0 - (((fRec21[0] * fRec18[2]) + (fRec20[0] * fRec18[1])) - (fSlow59 * (fRec1[0] * fRec19[0]))));
                S3[1] = ((fRec18[0] + (fSlow64 * fRec1[0])) - fRec18[1]);
                fTemp8 = S3[iSlow65];
            }                                     //crybaby ende

            S2[0] = fTemp8;

            if (iSlow71 == 1)     //freeverb
            {
                float fTemp9 = (1.500000e-02f * fTemp8);
                fRec31[0] = ((fSlow69 * fRec30[1]) + (fSlow68 * fRec31[1]));
                fVec10[IOTA&2047] = (fTemp9 + (fSlow70 * fRec31[0]));
                fRec30[0] = fVec10[(IOTA-1640)&2047];
                fRec33[0] = ((fSlow69 * fRec32[1]) + (fSlow68 * fRec33[1]));
                fVec11[IOTA&2047] = (fTemp9 + (fSlow70 * fRec33[0]));
                fRec32[0] = fVec11[(IOTA-1580)&2047];
                fRec35[0] = ((fSlow69 * fRec34[1]) + (fSlow68 * fRec35[1]));
                fVec12[IOTA&2047] = (fTemp9 + (fSlow70 * fRec35[0]));
                fRec34[0] = fVec12[(IOTA-1514)&2047];
                fRec37[0] = ((fSlow69 * fRec36[1]) + (fSlow68 * fRec37[1]));
                fVec13[IOTA&2047] = (fTemp9 + (fSlow70 * fRec37[0]));
                fRec36[0] = fVec13[(IOTA-1445)&2047];
                fRec39[0] = ((fSlow69 * fRec38[1]) + (fSlow68 * fRec39[1]));
                fVec14[IOTA&2047] = (fTemp9 + (fSlow70 * fRec39[0]));
                fRec38[0] = fVec14[(IOTA-1379)&2047];
                fRec41[0] = ((fSlow69 * fRec40[1]) + (fSlow68 * fRec41[1]));
                fVec15[IOTA&2047] = (fTemp9 + (fSlow70 * fRec41[0]));
                fRec40[0] = fVec15[(IOTA-1300)&2047];
                fRec43[0] = ((fSlow69 * fRec42[1]) + (fSlow68 * fRec43[1]));
                fVec16[IOTA&2047] = (fTemp9 + (fSlow70 * fRec43[0]));
                fRec42[0] = fVec16[(IOTA-1211)&2047];
                fRec45[0] = ((fSlow69 * fRec44[1]) + (fSlow68 * fRec45[1]));
                fVec17[IOTA&2047] = (fTemp9 + (fSlow70 * fRec45[0]));
                fRec44[0] = fVec17[(IOTA-1139)&2047];
                float fTemp10 = (((((((fRec44[0] + fRec42[0]) + fRec40[0]) + fRec38[0]) + fRec36[0]) + fRec34[0]) + fRec32[0]) + fRec30[0]);
                fVec18[IOTA&1023] = (fTemp10 + (0.5f * fRec28[1]));
                fRec28[0] = fVec18[(IOTA-579)&1023];
                float 	fRec29 = (0 - (fTemp10 - fRec28[1]));
                fVec19[IOTA&511] = (fRec29 + (0.5f * fRec26[1]));
                fRec26[0] = fVec19[(IOTA-464)&511];
                float 	fRec27 = (fRec26[1] - fRec29);
                fVec20[IOTA&511] = (fRec27 + (0.5f * fRec24[1]));
                fRec24[0] = fVec20[(IOTA-364)&511];
                float 	fRec25 = (fRec24[1] - fRec27);
                fVec21[IOTA&255] = (fRec25 + (0.5f * fRec22[1]));
                fRec22[0] = fVec21[(IOTA-248)&255];
                float 	fRec23 = (fRec22[1] - fRec25);
                S2[1] = ((fSlow66 * (fRec23 + fTemp9)) + (fSlow67 * fTemp8));
            }
            else  S2[1] = fTemp8;	//freeverb end

            fRec46[0] = (fSlow72 + (0.999f * fRec46[1]));
            float fTemp12 = (fRec46[0] * S2[iSlow71]);

            if (iSlow75 == 1)    //echo
            {
                S1[0] = fTemp12;
                fRec47[IOTA&262143] = (fTemp12 + (fSlow74 * fRec47[(IOTA-iSlow73)&262143]));
                S1[1] = fRec47[(IOTA-0)&262143];
                fTemp12 = S1[iSlow75];
            }                                     //echo ende

            if (iSlow79 == 1)     //impulseResponse
            {
                fVec22[0] = fTemp12;
                S0[0] = fVec22[0];
                fRec48[0] = ((fSlow78 * (fVec22[0] - fVec22[2])) + (fSlow76 * ((fSlow77 * fRec48[1]) - (fSlow76 * fRec48[2]))));
                S0[1] = (fRec48[0] + fVec22[0]);
                float fTemp13 = S0[iSlow79];
                fVec23[0] = fTemp13;
            }
            else  fVec23[0] = fTemp12;   //impulseResponse ende

            // this is the output value from the mono process
            fRec0[0] = ((fVec23[0] + (fSlow80 * fVec23[3])) - (fSlow0 * fRec0[5]));
            // switch betwee fuzz or foldback distortion, or plain output
            switch (ifuse)
            {
            case 0:
                break;
            case 1:
                fRec0[0] = fuzz(fRec0[0],threshold);
                break;
            case 2:
                fRec0[0] = foldback(fRec0[0],threshold);
                break;
            }
            // trigger the oscilloscope to update peer sample. I know that some samples dont will show, but it will
            // update fast as  posible this way (mode 3)
            if ((showwave == 1) &&(view_mode == 3)) viv = fRec0[0];
            // this is the left "extra" port to run jconv in bybass mode
            if (irunjc == 1) output0[i] = (fSlow85 * fRec0[0]);
            float 	S9[2];
            // copy the output for the frame based mode of the oscilloscope
            if ((showwave == 1) &&((view_mode == 1) || (view_mode == 2) )) get_frame[i] = fRec0[0];
            S9[0] = (fSlow87 * fRec0[0]);
            S9[1] = (fSlow84 * fRec0[0]);
            // the left output port
            output1[i] = S9[iSlow88];
            // this is the right "extra" port to run jconv in bybass mode
            if (irunjc == 1) output2[i] = (fSlow90 * fRec0[0]);
            float 	S10[2];
            S10[0] = (fSlow91 * fRec0[0]);
            S10[1] = (fSlow89 * fRec0[0]);
            // the right output port
            output3[i] = S10[iSlow88];
            // post processing
            for (int i=5; i>0; i--) fRec0[i] = fRec0[i-1];
            for (int i=3; i>0; i--) fVec23[i] = fVec23[i-1];
            fRec48[2] = fRec48[1];
            fRec48[1] = fRec48[0];
            fVec22[2] = fVec22[1];
            fVec22[1] = fVec22[0];
            fRec46[1] = fRec46[0];
            fRec22[1] = fRec22[0];
            fRec24[1] = fRec24[0];
            fRec26[1] = fRec26[0];
            fRec28[1] = fRec28[0];
            fRec44[1] = fRec44[0];
            fRec45[1] = fRec45[0];
            fRec42[1] = fRec42[0];
            fRec43[1] = fRec43[0];
            fRec40[1] = fRec40[0];
            fRec41[1] = fRec41[0];
            fRec38[1] = fRec38[0];
            fRec39[1] = fRec39[0];
            fRec36[1] = fRec36[0];
            fRec37[1] = fRec37[0];
            fRec34[1] = fRec34[0];
            fRec35[1] = fRec35[0];
            fRec32[1] = fRec32[0];
            fRec33[1] = fRec33[0];
            fRec30[1] = fRec30[0];
            fRec31[1] = fRec31[0];
            fRec18[2] = fRec18[1];
            fRec18[1] = fRec18[0];
            fRec21[1] = fRec21[0];
            fRec20[1] = fRec20[0];
            fRec19[1] = fRec19[0];
            fRec1[2] = fRec1[1];
            fRec1[1] = fRec1[0];
            fRec2[2] = fRec2[1];
            fRec2[1] = fRec2[0];
            fVec9[2] = fVec9[1];
            fVec9[1] = fVec9[0];
            fRec14[2] = fRec14[1];
            fRec14[1] = fRec14[0];
            fRec15[2] = fRec15[1];
            fRec15[1] = fRec15[0];
            fRec16[1] = fRec16[0];
            fVec8[1] = fVec8[0];
            fRec17[1] = fRec17[0];
            fVec7[1] = fVec7[0];
            fRec13[1] = fRec13[0];
            fRec5[1] = fRec5[0];
            fVec6[1] = fVec6[0];
            fRec9[2] = fRec9[1];
            fRec9[1] = fRec9[0];
            fRec10[2] = fRec10[1];
            fRec10[1] = fRec10[0];
            fRec11[1] = fRec11[0];
            fVec5[1] = fVec5[0];
            fRec12[1] = fRec12[0];
            fVec4[1] = fVec4[0];
            fRec7[1] = fRec7[0];
            fVec3[1] = fVec3[0];
            fRec8[1] = fRec8[0];
            fVec2[1] = fVec2[0];
            fRec6[1] = fRec6[0];
            IOTA = IOTA+1;
            fRec3[1] = fRec3[0];
            fRec4[1] = fRec4[0];
            fReccom0[1] = fReccom0[0];
            fReccom1[1] = fReccom1[0];
            fVec0[1] = fVec0[0];
            fRecover0[1] = fRecover0[0];
            // post processing tuner
            fRect0[1] = fRect0[0];
            iRect1[1] = iRect1[0];
            iRect2[1] = iRect2[0];
            iRect3[1] = iRect3[0];
            fRect4[1] = fRect4[0];
            fVect1[1] = fVect1[0];
            fRect5[1] = fRect5[0];
            fVect0[1] = fVect0[0];
            fRechp0[1] = fRechp0[0];
            fVechp0[1] = fVechp0[0];

        }
        // triger the oscilloscope to update on frame base (mode 1 and 2)
        if ((showwave == 1) &&((view_mode == 1)|| (view_mode == 2))) viv = fRec0[0];
    }
    else  // when the dsp prozess is disable, send zeros the the portbuffer
    {
        // the extra port register can only run clean on frame base, therfor the
        // variable runjc must check on frame base, not in the inner loop.
        int     irunjc = runjc;
        // pointer to the output buffers
        float* output0 = output[0];
        float* output1 = output[1];
        float* output2 = output[2];
        float* output3 = output[3];
        for (int i=0; i<count; i++)
        {
            float fTemp0 = 0.0f;
            output0[i] = fTemp0;
            output1[i] = fTemp0;
            // only when jconv is runing
            if (irunjc == 1)output2[i] = fTemp0;
            if (irunjc == 1)output3[i] = fTemp0;
        }
    }
}


