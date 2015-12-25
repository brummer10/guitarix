/****************************************************************************
*
* NAME: smbPitchShift.cpp
* VERSION: 1.2
* HOME URL: http://www.dspdimension.com
* KNOWN BUGS: none
* 
*
* COPYRIGHT 1999-2009 Stephan M. Bernsee <smb [AT] dspdimension [DOT] com>
* 
* Modified for guitarix by Hermann Meyer 2014
*
* 						The Wide Open License (WOL)
*
* Permission to use, copy, modify, distribute and sell this software and its
* documentation for any purpose is hereby granted without fee, provided that
* the above copyright notice and this license appear in all source copies. 
* THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT EXPRESS OR IMPLIED WARRANTY OF
* ANY KIND. See http://www.dspguru.com/wol.htm for more information.
*
*****************************************************************************/ 

namespace detune {


#define M_PI 3.14159265358979323846
#define MAX_FRAME_LENGTH 8096

class smbPitchShift : public PluginLV2 {
private:
    gx_resample::SimpleResampler resamp;
	bool            mem_allocated;
	volatile bool ready;
	float gInFIFO[MAX_FRAME_LENGTH];
	float gOutFIFO[MAX_FRAME_LENGTH];
    float *fpb;
    float *expect;
    float *hanning;
    float *hanningd;
    float *resampin;
    float *resampin2;
    float *resampout;
    float *indata2;
	float gLastPhase[MAX_FRAME_LENGTH/2+1];
	float gSumPhase[MAX_FRAME_LENGTH/2+1];
	float gOutputAccum[2*MAX_FRAME_LENGTH];
	float gAnaFreq[MAX_FRAME_LENGTH];
	float gAnaMagn[MAX_FRAME_LENGTH];
	float gSynFreq[MAX_FRAME_LENGTH];
	float gSynMagn[MAX_FRAME_LENGTH];
	float semitones;
	float octave,a,b,c,d,l;
	float wet;
	float dry;
	float latency;
	float *semitones_;
	float *octave_,*a_,*b_,*c_,*d_,*l_;
	float *wet_;
	float *dry_;
	float *latency_;
    float *latencyr_;
    float mpi, mpi1;
	int   osamp, numSampsToProcess, fftFrameSize, sampleRate ;
    int ai;
    int aio;
    int ii;
	long  gRover , gInit ;
	double magn, phase, tmp, window, real, imag;
	double freqPerBin, freqPerBin1, freqPerBin2, expct;
    double fftFrameSize3;
    double fftFrameSize4;
    double osamp1,osamp2;
	long   i,k, qpd, index, inFifoLatency, stepSize, fftFrameSize2;
	
    fftwf_complex fftw_in[MAX_FRAME_LENGTH], fftw_out[MAX_FRAME_LENGTH];
    fftwf_plan ftPlanForward, ftPlanInverse;
    
    void change_latency();
   
    void mem_alloc();
	void mem_free();
	int activate(bool start);
	bool setParameters( int sampleRate);
	void PitchShift(int count, float *indata, float *outdata);
	void connect(uint32_t port,void* data);
    void setbuffersize(unsigned int size) {numSampsToProcess = size; };
    static int  activate_static(bool start, PluginLV2*);
    static void del_instance(PluginLV2 *p);
	static void init(unsigned int sampleRate, PluginLV2 *plugin); 
    static void compute_static(int count, float *input0, float *output0, PluginLV2 *p); 
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);

public:
    static void set_buffersize(PluginLV2 *p, unsigned int size) {
        static_cast<smbPitchShift*>(p)->setbuffersize(size); };
    static void change_latency_static(PluginLV2 *p) {
        static_cast<smbPitchShift*>(p)->change_latency(); };
	smbPitchShift();
	~smbPitchShift();
};


bool smbPitchShift::setParameters(int sampleRate_)
{
   // numSampsToProcess = int(engine.get_buffersize());
   //  fftFrameSize = numSampsToProcess/4;
    sampleRate = int(sampleRate_);
    assert(sampleRate>0);
    osamp = 8;
    osamp1 = 1./osamp;
    osamp2 = 2.*M_PI*osamp1;
    mpi = (1./(2.*M_PI)) * osamp;
    mpi1 = 1./M_PI;
    fpb = 0; 
    expect = 0; 
    hanning = 0; 
    hanningd = 0;
    resampin = 0;
    resampout = 0;
    indata2 = 0;
    resamp.setup(sampleRate,4);
    gRover = false;
    return true;
}

smbPitchShift::smbPitchShift():
  PluginLV2(),
  mem_allocated(false),
  ready(false),
  ftPlanForward(0),
  ftPlanInverse(0) {
    if (gRover == false) gRover = inFifoLatency;
    memset(gInFIFO, 0, MAX_FRAME_LENGTH*sizeof(float));
    memset(gOutFIFO, 0, MAX_FRAME_LENGTH*sizeof(float));
    memset(gLastPhase, 0, (MAX_FRAME_LENGTH/2+1)*sizeof(float));
    memset(gSumPhase, 0, (MAX_FRAME_LENGTH/2+1)*sizeof(float));
    memset(gOutputAccum, 0, 2*MAX_FRAME_LENGTH*sizeof(float));
    memset(gAnaFreq, 0, MAX_FRAME_LENGTH*sizeof(float));
    memset(gAnaMagn, 0, MAX_FRAME_LENGTH*sizeof(float));
    version = PLUGINLV2_VERSION;
    id = "smbPitchShift";
    name = N_("Detune");
    mono_audio = compute_static;
    stereo_audio = 0;
    set_samplerate = init;
    activate_plugin = activate_static;
    connect_ports = connect_static;
    delete_instance = del_instance;
}

void smbPitchShift::init(unsigned int samplingFreq, PluginLV2 *plugin) {
    static_cast<smbPitchShift*>(plugin)->setParameters(samplingFreq);
    
}

void smbPitchShift::mem_alloc()
{
   // numSampsToProcess = int(engine.get_buffersize());
    assert(numSampsToProcess>0);
    assert(sampleRate>0);
    
    switch(int(latency)) {
      case(0):
        if (numSampsToProcess <= 2048) {
          fftFrameSize = 512 ;
          *(latencyr_) = 2048-numSampsToProcess;
        } else {
          fftFrameSize = numSampsToProcess*0.25 ;
          *(latencyr_) = 0;
        }
        break;
      case(1):
        fftFrameSize = numSampsToProcess;
        *(latencyr_) = numSampsToProcess*3;
        break;
      case(2):
        fftFrameSize = numSampsToProcess*0.25;
        *(latencyr_) = 0;
        break;
      default:
        if (numSampsToProcess <= 2048) {
          fftFrameSize = 512 ; 
          *(latencyr_) = 2048-numSampsToProcess;
        } else {
          fftFrameSize = numSampsToProcess*0.25 ;
          *(latencyr_) = 0;
        }
        break;
    }
    fftFrameSize2 = fftFrameSize/2;
    stepSize = fftFrameSize/osamp;
    freqPerBin = (double)(sampleRate/4)/(double)fftFrameSize;
    freqPerBin1 = (1/freqPerBin)*osamp2;
    freqPerBin2 = freqPerBin*mpi;
    expct = 2.*M_PI*(double)stepSize/(double)fftFrameSize;
    inFifoLatency = fftFrameSize-stepSize;
    fftFrameSize3 = 2. * (1./ ((double)(fftFrameSize2)*osamp));
    fftFrameSize4 = 1./(double)fftFrameSize;
    ai = 0;
    aio = 0;
    ii = 0;
    memset(gInFIFO, 0, MAX_FRAME_LENGTH*sizeof(float));
    memset(gOutFIFO, 0, MAX_FRAME_LENGTH*sizeof(float));
    memset(gLastPhase, 0, (MAX_FRAME_LENGTH/2+1)*sizeof(float));
    memset(gSumPhase, 0, (MAX_FRAME_LENGTH/2+1)*sizeof(float));
    memset(gOutputAccum, 0, 2*MAX_FRAME_LENGTH*sizeof(float));
    memset(gAnaFreq, 0, MAX_FRAME_LENGTH*sizeof(float));
    memset(gAnaMagn, 0, MAX_FRAME_LENGTH*sizeof(float));

    try {
        fpb = new float[fftFrameSize2];
        for (k = 0; k < fftFrameSize2;k++) {
            fpb[k] = (double)k*freqPerBin;
        }
        expect = new float[fftFrameSize2];
        for (k = 0; k < fftFrameSize2;k++) {
            expect[k] = (double)k*expct;
        }
        hanning = new float[fftFrameSize];
        for (k = 0; k < fftFrameSize;k++) {
            hanning[k] = 0.5*(1-cos(2.*M_PI*(double)k/((double)fftFrameSize)));
        }
        hanningd = new float[fftFrameSize];
        for (k = 0; k < fftFrameSize;k++) {
            hanningd[k] = 0.5*(1-cos(2.*M_PI*(double)k * fftFrameSize4)) * fftFrameSize3; 
        }
        resampin = new float[fftFrameSize];
        for (k = 0; k < fftFrameSize;k++) {
            resampin[k] = 0.0; 
        }
        resampin2 = new float[fftFrameSize];
        for (k = 0; k < fftFrameSize;k++) {
            resampin2[k] = 0.0; 
        }
        resampout = new float[fftFrameSize*4];
        for (k = 0; k < fftFrameSize*4;k++) {
            resampout[k] = 0.0; 
        }
        indata2 = new float[fftFrameSize*4];
        for (k = 0; k < fftFrameSize*4;k++) {
            indata2[k] = 0.0; 
        }
        //create FFTW plan
        ftPlanForward = fftwf_plan_dft_1d(fftFrameSize, fftw_in, fftw_out, FFTW_FORWARD, FFTW_MEASURE);
        ftPlanInverse = fftwf_plan_dft_1d(fftFrameSize, fftw_in, fftw_out, FFTW_BACKWARD, FFTW_MEASURE);
    } catch(...) {
            
            return;
        }
    
    
    gRover = inFifoLatency;

    mem_allocated = true;
    ready = true;
}

void smbPitchShift::mem_free()
{
    ready = false;
    mem_allocated = false;
    if (fpb) { delete fpb; fpb = 0; }
    if (expect) { delete expect; expect = 0; }
    if (hanning) { delete hanning; hanning = 0; }
    if (hanningd) { delete hanningd; hanningd = 0; }
    if (resampin) { delete resampin; resampin = 0; }
    if (resampin2) { delete resampin2; resampin2 = 0; }
    if (resampout) { delete resampout; resampout = 0; }
    if (indata2) { delete indata2; indata2 = 0; }
    if (ftPlanForward)
        {fftwf_destroy_plan(ftPlanForward);ftPlanForward = 0; }
    if (ftPlanInverse) 
        { fftwf_destroy_plan(ftPlanInverse);ftPlanInverse = 0; }
}


int smbPitchShift::activate(bool start)
{
    if (start) {
        if (!mem_allocated) {
            mem_alloc();
        }
    } else if (mem_allocated) {
        mem_free();
    }
    return 0;
}

void smbPitchShift::change_latency()
{
    if (mem_allocated) {
        mem_free();
        mem_alloc();
    }
}

smbPitchShift::~smbPitchShift()
{
    if (mem_allocated) {
        mem_free();
    }
}

// -----------------------------------------------------------------------------------------------------------------
void __rt_func smbPitchShift::compute_static(int count, float *input0, float *output0, PluginLV2 *p)
{
    static_cast<smbPitchShift*>(p)->PitchShift(count, input0, output0);
}


void always_inline smbPitchShift::PitchShift(int count, float *indata, float *outdata)
{
    if (!ready || count != numSampsToProcess)  {
        memcpy(outdata,indata,count*sizeof(float));
        return;
    }
    resamp.down(count*0.25,indata,resampin);
    double     fSlow0 = (0.01 * wet);
    double     fSlow1 = (0.01 * dry);
    
    float tone =0;
    
	semitones = *semitones_;
	octave = *octave_;
    a = *a_;
    b = *b_;
    c = *c_;
    d = *d_;
    l = *l_;
	wet = *wet_;
	dry = *dry_;
	latency = *latency_;
 
    // collect data for latency compensation
    for (i = 0; i < count; i++){
        indata2[ii] = indata[i];
        ii++;
    }
    // collect data for fft
    for (i = 0; i < count*0.25; i++){
        resampin2[ai] = resampin[i];
        ai++;
    }
    // now we have enough data
    if (ai>=fftFrameSize) {
        ai = 0;
        ii = 0;
        switch(int(octave)) {
          case(0):
            break;
          case(1):
            tone =12;
            break;
          case(2):
            tone =-12;
            break;
          default:
            break;
        }
        float pitchShift = pow(2., (semitones+tone)*0.0833333333);
        /* main processing loop */
        for (i = 0; i < fftFrameSize; i++){

            /* As long as we have not yet collected enough data just read in */
            float fTemp = resampin2[i];
            gInFIFO[gRover] = fTemp;
            resampin2[i] = gOutFIFO[gRover-inFifoLatency];
            gRover++;

            /* now we have enough data for processing */
            if (gRover >= fftFrameSize) {
                gRover = inFifoLatency;

                /* do windowing and re,im interleave */
                for (k = 0; k < fftFrameSize;k++) {
                    fftw_in[k][0] = gInFIFO[k] * hanning[k];
                    fftw_in[k][1] = 0.0;
                }


                /* ***************** ANALYSIS ******************* */
                /* do transform */
                fftwf_execute(ftPlanForward);

                /* this is the analysis step */
                for (k = 0; k <= fftFrameSize2; k++) {

                    /* de-interlace FFT buffer */
                    real = fftw_out[k][0];
                    imag = fftw_out[k][1];

                    /* compute magnitude and phase */
                    magn = 2.*sqrt(real*real + imag*imag);
                    phase = atan2(imag,real);

                    /* compute phase difference */
                    tmp = phase - gLastPhase[k];
                    gLastPhase[k] = phase;

                    /* subtract expected phase difference */
                    tmp -= expect[k];

                    /* map delta phase into +/- Pi interval */
                    qpd = tmp*mpi1;
                    if (qpd >= 0) qpd += qpd&1;
                    else qpd -= qpd&1;
                    tmp -= M_PI*(double)qpd;

                    /* get deviation from bin frequency from the +/- Pi interval */
                    /* compute the k-th partials' true frequency */
                    tmp = fpb[k] + tmp*freqPerBin2;

                    /* store magnitude and true frequency in analysis arrays */
                    gAnaMagn[k] = magn;
                    gAnaFreq[k] = tmp;

                }

                /* ***************** PROCESSING ******************* */
                /* this does the actual pitch shifting */
                memset(gSynMagn, 0, fftFrameSize*sizeof(float));
                memset(gSynFreq, 0, fftFrameSize*sizeof(float));
                for (k = 1; k <= fftFrameSize2-2; k++) { 
                    index = k*pitchShift;
                    if (index <= fftFrameSize2) { 
                        if (index <= fftFrameSize2*0.20)
                            gSynMagn[index] += gAnaMagn[k]*a; 
                        else if (index <= fftFrameSize2*0.45)
                            gSynMagn[index] += gAnaMagn[k]*b; 
                        else if (index <= fftFrameSize2*0.667)
                            gSynMagn[index] += gAnaMagn[k]*c; 
                        else 
                            gSynMagn[index] += gAnaMagn[k]*d; 
                           gSynFreq[index] = gAnaFreq[k] * pitchShift; 
                    } 
                }
                
                /* ***************** SYNTHESIS ******************* */
                /* this is the synthesis step */
                for (k = 0; k <= fftFrameSize2; k++) {

                    /* get magnitude and true frequency from synthesis arrays */
                    magn = gSynMagn[k];
                    //tmp = gSynFreq[k];

                    /* subtract bin mid frequency */
                    /* get bin deviation from freq deviation */
                    /* take osamp into account */
                    /* add the overlap phase advance back in */
                    tmp = ((gSynFreq[k] - fpb[k]) * freqPerBin1) + expect[k];

                    /* accumulate delta phase to get bin phase */
                    gSumPhase[k] += tmp;
                    phase = gSumPhase[k];
                    if (magn == 0.0) continue;

                    /* get real and imag part and re-interleave */                
                    fftw_in[k][0] = magn * cos (phase);
                    fftw_in[k][1] = magn * sin (phase);
                } 

                /* do inverse transform */
                fftwf_execute(ftPlanInverse);
                /* do windowing and add to output accumulator */ 
                for(k=0; k < fftFrameSize; k++) {
                    gOutputAccum[k] += hanningd[k] * fftw_out[ k][0] ;
                }
                for (k = 0; k < stepSize; k++) gOutFIFO[k] = gOutputAccum[k];

                /* shift accumulator */
                memmove(gOutputAccum, gOutputAccum+stepSize, fftFrameSize*sizeof(float));

                /* move input FIFO */
                for (k = 0; k < inFifoLatency; k++) gInFIFO[k] = gInFIFO[k+stepSize];
            }
        }
        resamp.up(fftFrameSize,resampin2,resampout);
        aio = 0;
    }
    if(l) {
        for (i = 0; i < count; i++){
            outdata[i] = ((fSlow0 * resampout[aio]) + (fSlow1 *indata2[aio]));
            aio++;
        }
    } else {
        for (i = 0; i < count; i++){
            outdata[i] = ((fSlow0 * resampout[aio]) + (fSlow1 *indata[i]));
            aio++;
        }
    }
}

void smbPitchShift::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case DETUNE: 
		semitones_ = (float*)data; // , 0.0, -12.0, 12.0, 0.1 
		break;
    // static const value_pair octave_values[] = {{"normal"},{"octave up"},{"octave down"},{0}};
	case OCTAVE: 
		octave_ = (float*)data; // , 0.0f, 0.0f, 2.0f, 1.0f 
		break;
    // static const value_pair latency_values[] = {{"latency "},{"compensate"},{0}};
	case COMPENSATE: 
		l_ = (float*)data; // , 0.0f, 0.0f, 1.0f, 1.0f
		break;
    // static const value_pair latency_set[] = {{"high quality"},{"low quality"},{"realtime"},{0}};
	case LATENCY: 
		latency_ = (float*)data; // , 0.0f, 0.0f, 2.0f, 1.0f 
		break;
	case WET: 
		wet_ = (float*)data; // , 50.0, 0.0, 100.0, 1
		break;
	case DRY: 
		dry_ = (float*)data; // , 50.0, 0.0, 100.0, 1
		break;
	case LOW: 
		a_ = (float*)data; // , 1.0, 0.0, 2.0, 0.01
		break;
	case MIDDLELOW: 
		b_ = (float*)data; // , 1.0, 0.0, 2.0, 0.01
		break;
	case MIDDLETREBLE: 
		c_ = (float*)data; // , 1.0, 0.0, 2.0, 0.01
		break;
	case TREBLE: 
		d_ = (float*)data; // , 1.0, 0.0, 2.0, 0.01 
		break;
	case LATENCYREPORT: 
		latencyr_ = (float*)data; 
		break;
	default:
		break;
	}
}

void smbPitchShift::connect_static(uint32_t port,void* data, PluginLV2 *p)
{
	static_cast<smbPitchShift*>(p)->connect(port, data);
}

int smbPitchShift::activate_static(bool start, PluginLV2 *p)
{
    return static_cast<smbPitchShift*>(p)->activate(start);
}

PluginLV2 *plugin() {
	return new smbPitchShift();
}

void smbPitchShift::del_instance(PluginLV2 *p)
{
    delete static_cast<smbPitchShift*>(p);
}

/*
typedef enum
{
   DETUNE, 
   OCTAVE,
   COMPENSATE,
   LATENCY, 
   WET,
   DRY,
   LOW,
   MIDDLELOW,
   MIDDLETREBLE,
   TREBLE,
} PortIndex;
*/


} // namespace gx_detune
