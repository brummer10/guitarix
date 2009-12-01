/*
 * Copyright (C) 2009 Hermann Meyer and James Warden
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 * --------------------------------------------------------------------------
 */

/* ------- This is the guitarix Engine namespace ------- */

#pragma once

// --- defines the processing type
#define ZEROIZE_BUFFERS  (0)
#define JUSTCOPY_BUFFERS (1)
#define PROCESS_BUFFERS  (2)

// --- engine interface defines
#define stackSize 256
#define kSingleMode 0
#define kBoxMode 1
#define kTabMode 2

#define max(x,y) (((x)>(y)) ? (x) : (y))
#define min(x,y) (((x)<(y)) ? (x) : (y))

class GxMainInterface;

namespace gx_engine
{
  /* --------------- function declarations --------------- */

  /* inline functions */
  inline void* aligned_calloc(size_t nmemb, size_t size)
  {
    return (void*)(((size_t)(calloc((nmemb*size)+15,
				    sizeof(char)))+15) & (~15));
  }

  /* right bit-shifting by n */
  inline int lsr (int x, int n)
  {
    return int(((unsigned int)x) >> n);
  }

  /* closest power of 2 to a given int */
  inline int int2pow2 (int x)
  {
    int r=0;
    while ((1<<r)<x) r++;
    return r;
  }

  /* square function */
  inline double sqrf(float x)
  {
    return x * x;
  }

  /* function declarations  */
  void gx_engine_init();
  void gx_engine_reset();

  /* ------------- Engine Processing Classes ------------- */
  // metadata
  struct Meta : map<const char*, const char*>
  {
    void declare (const char* key, const char* value)
    {
      (*this)[key] = value;
    }
  };

  /* base engine class definition, not to be used directly */
  class dsp
  {
  protected:
    // Note: an instance of a dsp class with a sample rate = 0 is NOT initialized

    // sample rate given by jack.
    int fSamplingFreq;

    // midi engine state
    static GxMidiState midistate;

  public:
    dsp() {}

    virtual ~dsp() {}

    virtual void compute(int len, float** inputs, float** outputs) = 0;
    virtual void compute_midi( int len) = 0;

    bool isInitialized()
    {
      return fSamplingFreq != 0;
    }

    static void turnOnMidi ()
    {
      midistate = kMidiOn;
    }
    static void turnOffMidi()
    {
      midistate = kMidiOff;
    }
    static bool isMidiOn   ()
    {
      return (midistate == kMidiOn ? true : false);
    }

  private:
    virtual void process_buffers(const int len, float** inputs, float** outputs) = 0;
    virtual void process_midi(const int len) = 0;
  };


  /* -- guitarix main engine class -- */
  class GxEngine : public dsp
  {
  public:

    // register all variables
    float fslider0;

    //----- tone
    float fslider_tone0; // tone treble controller
    float fConst_tone0;
    float fConst_tone1;
    float fConst_tone2;
    float fslider_tone1; // tone middle controller
    float fConst_tone3;
    float fConst_tone4;
    float fConst_tone5;
    float fVec_tone0[3];
    float fRec_tone3[3];
    float fRec_tone2[3];
    float fRec_tone1[3];
    float fRec_tone0[3];
    // tone end

    //float fVec0[2];
    float fcheckbox1;
    float fslider3;
    float fRec4[2];
    float fRec3[2];
    float fslider4;
    int   IOTA;
    float fVec1[4096];
    float fslider5;
    float fRec6[2];
    float fentry0;
    float fConst6;
    float fVec2[2];
    float fRec8[2];
    float fentry1;
    float fConst7;
    float fConst8;
    float fVec3[2];
    float fRec7[2];
    float fcheckbox2;
    float fslider6;
    float fslider7;
    float fVec4[2];
    float fRec12[2];
    float fVec5[2];
    float fRec11[2];
    float fRec10[3];
    float fRec9[3];
    float fcheckbox3;
    float fslider8;
    float fslider9;
    float fVec6[2];
    float fRec5[2];
    float fslider10;
    float fRec13[2];
    float fVec7[2];
    float fRec17[2];
    float fVec8[2];
    float fRec16[2];
    float fRec15[3];
    float fRec14[3];
    float fcheckbox4;
    float fslider11;
    float fRec19[2];
    float fslider12;
    float fslider13;
    float fConst9;
    float fConst10;
    float fRec20[2];
    float fRec21[2];
    float fRec18[3];
    float fcheckbox5;
    float fslider14;
    float fslider15;
    float fRec31[2];
    float fslider16;
    float fVec10[2048];
    float fRec30[2];
    float fRec33[2];
    float fVec11[2048];
    float fRec32[2];
    float fRec35[2];
    float fVec12[2048];
    float fRec34[2];
    float fRec37[2];
    float fVec13[2048];
    float fRec36[2];
    float fRec39[2];
    float fVec14[2048];
    float fRec38[2];
    float fRec41[2];
    float fVec15[2048];
    float fRec40[2];
    float fRec43[2];
    float fVec16[2048];
    float fRec42[2];
    float fRec45[2];
    float fVec17[2048];
    float fRec44[2];
    float fVec18[1024];
    float fRec28[2];
    float fVec19[512];
    float fRec26[2];
    float fVec20[512];
    float fRec24[2];
    float fVec21[256];
    float fRec22[2];
    float fcheckbox6;
    float fslider17;
    float fRec46[2];
    float fslider18;
    float fConst11;
    float fslider19;
    float fRec47[262144];
    float fcheckbox7;
    float fVec22[3];
    float fslider20;
    float fslider21;
    float fConst12;
    float fslider22;
    float fRec48[3];
    float fcheckbox8;
    float fVec23[4];
    float fslider23;
    float fRec0[6];
    float fslider24;
    float fslider25;
    float fConstan0;
    float fConstan1;
    float fConstan2;
    float fVect0[2];
    float fConstan3;
    float fRect5[2];
    float fVect1[2];
    float fRect4[2];
    int   iRect3[2];
    int   iRect2[2];
    int   iRect1[2];
    float fRect0[2];
    int   weg;
    float fexpand;
    float fexpand2;

    float filebutton;
    float fdialogbox1;
    float fdialogbox2;
    float fdialogbox3;
    float fdialogbox4;
    float fdialogbox5;
    float fdialogbox6;
    float fConsta1;
    float fslider26;
    float fslider27;
    float fslider29;
    float fslider30;
    float fslider31;
    int   program;

    unsigned char* midi_send;
    unsigned char* midi_send1;
    unsigned char* midi_send2;

    int   send;
    int   noten;
    float fslider32;
    float fslider33;
    float fslider34;
    float fslider35;
    float fslider36;
    float fcheckbox10;
    int   program1;
    int   send1;
    int   noten1;
    float fslider37;
    float fslider38;
    float fslider39;
    int   send2;
    int   noten2;
    float fslider40;
    float fslider41;
    float fslider42;
    float fslider43;
    float fslider44;
    float fcheckbox11;
    int   program2;
    float fslider45;
    float midistat;
    float fslider46;
    float fslider47;
    float fslider48;
    int   volume;
    int   volume1;
    int   volume2;
    float fpitch;
    float fpitch1;
    float fpitch2;
    float fConsthp0;
    float fConsthp1;
    float fConsthp2;
    float fVechp0[2];
    float fConsthp3;
    float fRechp0[2];

    // compressor
    float fentrycom0;
    float fConstcom0;
    float fConstcom1;
    float fReccom1[2];
    float fReccom2[2];
    float fConstcom2;
    float fslidercom0;
    float fslidercom1;
    float fReccom0[2];
    float fentrycom1;
    float fentrycom2;
    float fdialogbox8;
    float fcheckboxcom1;
    // compressor end

    float drive;
    float foverdrive4;
    float fTemprec1;
    float fRecover0[2];
    float viv;
    float vivi;
    float fConsta4;

    // float rms;
    float beat0;
    float antialis0;
    float faas1;
    float ffuzzytube;
    float ftube;
    float fpredrive;
    float fprdr;
    float fautogain;
    float fautogain1;
    float fautogain2;
    float fresoon;
    float fvibrato;
    float fConstun0;
    float tunerfilter;
    float tunerstage1;
    float tunerstage2;

    float tunerfilterh;
    float tunerstageh1;
    float tunerstageh2;
    float fConstlog;
    float fConstlog2;
    float fatan;
    float fwarn;
    float fupsample;
    float ffuse;
    float fthreshold;
    //float ftubemode;

    float ftube3;
    float fresotube1;
    float fresotube2;
    float fresotube3;

    //----- resonator
    int 	IOTARESO;
    float fVecRESO0[4096];
    float fRecRESO0[2];

    //----- oscillator
    int 	iVecoscb0[2];
    float fConstoscb0;
    float fRecoscb0[3];

    //--- low/highpass for tube
    float fConstsp0;
    float fConstsp1;
    float fConstsp2;
    float fConstsp3;
    float fConstsp4;
    float fConstsp5;
    float fConstsp6;
    float fConstsp7;
    float fConstsp8;
    float fVecsp0[2];
    float fConstsp9;
    float fRecsp3[2];
    float fRecsp2[2];
    float fRecsp1[3];
    float fRecsp0[3];

    //--- tone bass
    float fslider_tone2; // tone bass controller

    // lets init the variable for the tone settings
    float fSlow_mid_tone ;
    float fSlow_tone0;
    float fSlow_tone1 ;
    float fSlow_tone2 ;
    float fSlow_tone3 ;
    float fSlow_tone4 ;
    float fSlow_tone5 ;
    float fSlow_tone6 ;
    float fSlow_tone7 ;
    float fSlow_tone8 ;
    float fSlow_tone9 ;
    float fSlow_tone10 ;
    float fSlow_tone11 ;
    float fSlow_tone12 ;
    float fSlow_tone13 ;
    float fSlow_tone14 ;
    float fSlow_tone15 ;
    float fSlow_tone16 ;
    float fSlow_tone17 ;
    float fSlow_tone18 ;
    float fSlow_tone19 ;
    float fSlow_tone20 ;
    float fSlow_tone21 ;
    float fSlow_tone22 ;
    float fSlow_tone23 ;
    float fSlow_tone24 ;
    float fSlow_tone25 ;
    float fSlow_tone26 ;
    float fSlow_tone27 ;
    float fSlow_tone28 ;
    float fSlow_tone29 ;
    float fSlow_tone30 ;
    float fSlow_tone31 ;
    float fSlow_tone32 ;
    float fSlow_tone33 ;
    float fSlow_tone34 ;
    float fSlow_tone35 ;
    float fSlow_tone36 ;
    float fSlow_tone37 ;
    float fSlow_tone38 ;
    float fSlow_tone39 ;
    float fSlow_tone40 ;
    float fSlow_tone41 ;
    float fSlow_tone42 ;
    float fSlow_tone43 ;
    float fSlow_tone44 ;
    float fSlow_tone45 ;
    float fSlow_tone46 ;
    float fSlow_tone47 ;
    int   fslider_tone_check;
    int   fslider_tone_check1;
    // tone end
    // float  fbargraph0;

    float 	fRecgate0[2];
    float 	fSlowgate2;
    float 	fSlowgate3;
    float 	fSlowgate4;
    float fng;
    float fsharp0;

    // bass booster
    float 	fConst_boost0;
    float 	fConst_boost1;
    float 	fConst_boost2;
    float 	fConst_boost3;
    float 	fConst_boost4;
    float 	fRec_boost0[3];
    float 	fConst_boost5;
    float 	fConst_boost6;
    float 	fConst_boost7;
    float 	fConst_boost8;
    float   fboost;
    // bass booster end
    float ngate;
    float fnoise_g;
    float fnglevel;

    // autowah
    float fautowah;
    float iVecwah0[1024];
    float iRecwah2[2];
    int IOTAWAH;

    float midi_gain;

    float log_2;
    float log_4;

    //chorus
    class SIG0
    {
    private:
      int 	fSamplingFreq;
      int 	iRec1[2];
    public:
      int getNumInputs()
      {
	return 0;
      }
      int getNumOutputs()
      {
	return 1;
      }
      void init(int samplingFreq)
      {
	fSamplingFreq = samplingFreq;
	for (int i=0; i<2; i++) iRec1[i] = 0;
      }
      void fill (int count, float output[])
      {
	for (int i=0; i<count; i++)
	  {
	    iRec1[0] = (1 + iRec1[1]);
	    output[i] = sinf((9.587380e-05f * (iRec1[0] - 1)));
	    // post processing
	    iRec1[1] = iRec1[0];
	  }
      }
    };

    int 	IOTA_CH;
    float 	fVec_CH0[65536];
    float 	fslider_CH0;
    float 	fConst_CH0;
    float 	fRec_CH0[2];
    static float 	ftbl0[65536];
    float 	fslider_CH1;
    float 	fslider_CH2;
    float 	fConst_CH1;
    float 	fslider_CH3;
    float fchorus;
    float fchorusbox;
    //chorus end
    int Beat_is;
    float cache_note;


    float fjc_ingain;
    float fRecinjc[2];
    float old_freq;

    int 	IOTAdel;
	float 	fVecdel0[262144];
	float 	fsliderdel0;
	float 	fConstdel0;

    // private constructor
    GxEngine() {}

    // private audio processing
    void process_buffers(int count, float** input, float** output);
    void process_midi(int count);

    friend class GxMainInterface;

  public:
    float fskin;
    // unique instance : use this instead of constructor
    static GxEngine* instance();

    static void metadata(Meta* m);

    static int getNumInputs()
    {
      return 1;
    }
    static int getNumOutputs()
    {
      return 2;
    }

    static void classInit(int samplingFreq)
    {
      SIG0 sig0;
      sig0.init(samplingFreq);
      sig0.fill(65536,ftbl0);
    }

    void initEngine(int samplingFreq);

    // wrap the state of the latency change warning (dis/enable) to
    // the interface settings to load and save it
    void set_latency_warning_change()
    {
      fwarn_swap = fwarn;
    }
    void get_latency_warning_change()
    {
      fwarn = fwarn_swap;
    }

    // zeroize an array of float using memset
    static void zeroize(int array[], int array_size)
    {
      (void)memset(array, 0, sizeof(array[0])*array_size);
    }

    static void zeroize(float array[], int array_size)
    {
      (void)memset(array, 0, sizeof(array[0])*array_size);
    }

    // ---- audio engine methods
    static void  add_dc     (float& val);
    float my2powf    ( float y);
    float my4powf    (float y);
    static float clip       (float x,  float a);
    static float hard_cut   (float in, float threshold);
    static float foldback   (float in, float threshold);
    static float valve      (float in, float out);
    static void  over_sample(float** input, float** output, int sf);
    static void  down_sample(float** input, float** output, int sf);
    static void  fuzzy_tube (int fuzzy, int mode, int sf,
			     float** input, float** output);
    static float normalize  (float in, float atan_shape, float shape);
    static float saturate(float x, float t);
    static float sigmoid(float x);

    // non static methods (modifying object's non static private members)
    void  moving_filter(float** input, float** output, int sf);
    void  noise_gate  (int sf, float** input);
    void  noise_shaper  (int sf, float** input, float** output);
    void  AntiAlias  (int sf, float** input, float** output);
    void  reso_tube  (int fuzzy, int sf, float reso, float vibra,
		      float** input, float** output);
    void  osc_tube   (int fuzzy, int sf, float reso, float vibra,
		      float** input, float** output);
    void  preamp     (int sf, float** input, float** output,
		      float atan_shape, float f_atan);
    void  get_jconv_output(float **input,float **output,int sf);
    // main audio processing
    void compute (int count, float** input, float** output);

    // ---- MIDI engine methods
    void compute_midi(int len);
#ifdef USE_RINGBUFFER
    void queue_message(struct MidiMessage *ev);
#endif

  };

  /* ------------------------------------------------------------------- */
} /* end of gx_engine namespace */
