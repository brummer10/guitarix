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
*/

/******************************************************************************
*******************************************************************************

								FAUST DSP
	dsp.cpp
	init the dsp processing for guitarix
*******************************************************************************
*******************************************************************************/


//----------------------------------------------------------------
//  définition du processeur de signal
//----------------------------------------------------------------

class dsp
{
protected:
  // sample rate given by jack. 
  // Note: an instance of a dsp class with a sample rate = 0 is NOT initialized 
    int fSamplingFreq;
public:
    dsp() : fSamplingFreq(0) {}
    virtual ~dsp() {}
    virtual int getNumInputs() 	= 0;
    virtual int getNumOutputs() 	= 0;
    virtual void buildUserInterface(UI* interface) 	= 0;
    virtual void init(int samplingRate) 	= 0;
    virtual void compute(int len, float** inputs, float** outputs) 	= 0;
    virtual void compute_midi( int len)  = 0;
    virtual void setNumOutputs() = 0;
    virtual void set_state()= 0;
    virtual void get_state()= 0;
    virtual bool isInitialized() { return fSamplingFreq != 0; }

private:
    virtual void process_buffers(const int len, float** inputs, float** outputs) = 0;
};


//----------------------------------------------------------------------------
// 	FAUST generated code
//----------------------------------------------------------------------------

class mydsp : public dsp
{
private:
  // register all variables needed by dsp_audio.cpp dsp_midi.cpp and dsp_interface.cpp

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
  float fVec0[2];
  float fcheckbox1;
  float fslider3;
  float fRec4[2]; 
  float fRec3[2];
  float fslider4;
  int 	IOTA;
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
  int 	iRect3[2];
  int 	iRect2[2];
  int 	iRect1[2];
  float fRect0[2];
  int   weg;
  float fexpand;
  float fexpand2;
  float fexpand3;
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
public:

  static void metadata(Meta* m)
  {
    m->declare("name", "guitarix");
    m->declare("version", "0.01");
    m->declare("author", "brummer");
    m->declare("contributor", "Julius O. Smith (jos at ccrma.stanford.edu)");
    m->declare("license", "BSD");
    m->declare("copyright", "(c)brummer 2008");
    m->declare("reference", "http://ccrma.stanford.edu/realsimple/faust_strings/");
  }

  virtual int getNumInputs()
  {
    return 1;
  }

  virtual int getNumOutputs()
  {
    return 2;
  }

// this funktion isn't needed any more, we can savely remove it
  virtual void setNumOutputs()
  {
    sleep(1);

    if (jack_port_is_mine (client,output_ports[3]))
    {
      jack_port_unregister(client, output_ports[3]);
      gNumOutChans -= 1;
    }
       
    if (jack_port_is_mine (client,output_ports[2]))
    {
      jack_port_unregister(client, output_ports[2]);
      gNumOutChans -= 1;
    }
  }

  static void classInit(int samplingFreq)
  {
  }

  virtual void instanceInit(int samplingFreq)
  {
    // initialisise all variables for dsp_audio dsp_midi and dsp_interface
    fSamplingFreq = samplingFreq;
    // compressor
    fentrycom0 = -20.000000f;
    fConstcom0 = expf((0 - (10.000000f / fSamplingFreq)));
    fConstcom1 = (1 - fConstcom0);
    for (int i=0; i<2; i++) fReccom1[i] = 0;
    for (int i=0; i<2; i++) fReccom2[i] = 0;
    fConstcom2 = (1.000000f / fSamplingFreq);
    fslidercom0 = 2.000000e-03f;
    fslidercom1 = 0.500000f;
    for (int i=0; i<2; i++) fReccom0[i] = 0;
    fentrycom1 = 3.000000f;
    fentrycom2 = 2.000000f;
    // compressor end
    fConstan0 = (3.141593f / fSamplingFreq);
    fConstan1 = (251.327423f / fSamplingFreq);
    fConstan2 = (1 - fConstan1);
    for (int i=0; i<2; i++) fVect0[i] = 0;
    fConstan3 = (1.0f / (1 + fConstan1));
    for (int i=0; i<2; i++) fRect5[i] = 0;
    for (int i=0; i<2; i++) fVect1[i] = 0;
    for (int i=0; i<2; i++) fRect4[i] = 0;
    for (int i=0; i<2; i++) iRect3[i] = 0;
    for (int i=0; i<2; i++) iRect2[i] = 0;
    for (int i=0; i<2; i++) iRect1[i] = 0;
    for (int i=0; i<2; i++) fRect0[i] = 0;

    fslider0 = 0.0f;  // gain in
    //----- tone
    fslider_tone0 = 0.0f;
    fConst_tone0 = (15079.645508f / fSamplingFreq);
    fConst_tone1 = cosf(fConst_tone0);
    fConst_tone2 = (1.414214f * sinf(fConst_tone0));
    fslider_tone1 = 0.0f;
    fConst_tone3 = (3769.911377f / fSamplingFreq);
    fConst_tone4 = cosf(fConst_tone3);
    fConst_tone5 = (1.414214f * sinf(fConst_tone3));
    fslider_tone2 = 0.0f;
    for (int i=0; i<3; i++) fVec_tone0[i] = 0;
    for (int i=0; i<3; i++) fRec_tone3[i] = 0;
    for (int i=0; i<3; i++) fRec_tone2[i] = 0;
    for (int i=0; i<3; i++) fRec_tone1[i] = 0;
    for (int i=0; i<3; i++) fRec_tone0[i] = 0;
    // tone end
    for (int i=0; i<2; i++) fVec0[i] = 0;
    checky = 1.0;
    fcheckbox1 = 0.0;
    fslider3 = 0.0f;
    for (int i=0; i<2; i++) fRec4[i] = 0; 
    for (int i=0; i<2; i++) fRec3[i] = 0;
    fslider4 = 0.12f;
    IOTA = 0;
    for (int i=0; i<4096; i++) fVec1[i] = 0;
    fslider5 = 0.5f;
    for (int i=0; i<2; i++) fRec6[i] = 0;
    fentry0 = 723.0f;
    fConst6 = (3.141593f / fSamplingFreq);
    for (int i=0; i<2; i++) fVec2[i] = 0;
    for (int i=0; i<2; i++) fRec8[i] = 0;
    fentry1 = 720.0f;
    fConst7 = (3.141593f * fSamplingFreq);
    fConst8 = (0.5f / fSamplingFreq);
    for (int i=0; i<2; i++) fVec3[i] = 0;
    for (int i=0; i<2; i++) fRec7[i] = 0;
    fcheckbox2 = 1.0;
    fslider6 = 5000.0f;
    fslider7 = 130.0f;
    for (int i=0; i<2; i++) fVec4[i] = 0;
    for (int i=0; i<2; i++) fRec12[i] = 0;
    for (int i=0; i<2; i++) fVec5[i] = 0;
    for (int i=0; i<2; i++) fRec11[i] = 0;
    for (int i=0; i<3; i++) fRec10[i] = 0;
    for (int i=0; i<3; i++) fRec9[i] = 0;
    fcheckbox3 = 1.0;
    fslider8 = 1.000000e-02f;
    fslider9 = 0.64f;
    for (int i=0; i<2; i++) fVec6[i] = 0;
    for (int i=0; i<2; i++) fRec5[i] = 0;
    fslider10 = 2.0f;
    for (int i=0; i<2; i++) fRec13[i] = 0;
    for (int i=0; i<2; i++) fVec7[i] = 0;
    for (int i=0; i<2; i++) fRec17[i] = 0;
    for (int i=0; i<2; i++) fVec8[i] = 0;
    for (int i=0; i<2; i++) fRec16[i] = 0;
    for (int i=0; i<3; i++) fRec15[i] = 0;
    for (int i=0; i<3; i++) fRec14[i] = 0;
    fcheckbox4 = 1.0;
    fslider11 = 0.0f;
    for (int i=0; i<2; i++) fRec19[i] = 0;
    fslider12 = 0.1f;
    fslider13 = 0.0f;
    fConst9 = (2827.43335f / fSamplingFreq);
    fConst10 = (1413.716675f / fSamplingFreq);
    for (int i=0; i<2; i++) fRec20[i] = 0;
    for (int i=0; i<2; i++) fRec21[i] = 0;
    for (int i=0; i<3; i++) fRec18[i] = 0;
    fcheckbox5 = 0.0;
    fslider14 = 0.3333f;
    fslider15 = 0.5f;
    for (int i=0; i<2; i++) fRec31[i] = 0;
    fslider16 = 0.5f;
    for (int i=0; i<2048; i++) fVec10[i] = 0;
    for (int i=0; i<2; i++) fRec30[i] = 0;
    for (int i=0; i<2; i++) fRec33[i] = 0;
    for (int i=0; i<2048; i++) fVec11[i] = 0;
    for (int i=0; i<2; i++) fRec32[i] = 0;
    for (int i=0; i<2; i++) fRec35[i] = 0;
    for (int i=0; i<2048; i++) fVec12[i] = 0;
    for (int i=0; i<2; i++) fRec34[i] = 0;
    for (int i=0; i<2; i++) fRec37[i] = 0;
    for (int i=0; i<2048; i++) fVec13[i] = 0;
    for (int i=0; i<2; i++) fRec36[i] = 0;
    for (int i=0; i<2; i++) fRec39[i] = 0;
    for (int i=0; i<2048; i++) fVec14[i] = 0;
    for (int i=0; i<2; i++) fRec38[i] = 0;
    for (int i=0; i<2; i++) fRec41[i] = 0;
    for (int i=0; i<2048; i++) fVec15[i] = 0;
    for (int i=0; i<2; i++) fRec40[i] = 0;
    for (int i=0; i<2; i++) fRec43[i] = 0;
    for (int i=0; i<2048; i++) fVec16[i] = 0;
    for (int i=0; i<2; i++) fRec42[i] = 0;
    for (int i=0; i<2; i++) fRec45[i] = 0;
    for (int i=0; i<2048; i++) fVec17[i] = 0;
    for (int i=0; i<2; i++) fRec44[i] = 0;
    for (int i=0; i<1024; i++) fVec18[i] = 0;
    for (int i=0; i<2; i++) fRec28[i] = 0;
    for (int i=0; i<512; i++) fVec19[i] = 0;
    for (int i=0; i<2; i++) fRec26[i] = 0;
    for (int i=0; i<512; i++) fVec20[i] = 0;
    for (int i=0; i<2; i++) fRec24[i] = 0;
    for (int i=0; i<256; i++) fVec21[i] = 0;
    for (int i=0; i<2; i++) fRec22[i] = 0;
    fcheckbox6 = 0.0;
    fslider17 = 0.0f;
    for (int i=0; i<2; i++) fRec46[i] = 0;
    fslider18 = 0.0f;
    fConst11 = (1.000000e-03f * fSamplingFreq);
    fslider19 = 0.0f;
    for (int i=0; i<262144; i++) fRec47[i] = 0;
    fcheckbox7 = 0.0;
    for (int i=0; i<3; i++) fVec22[i] = 0;
    fslider20 = 100.0f;
    fslider21 = 440.0f;
    fConst12 = (6.283185f / fSamplingFreq);
    fslider22 = 1.0f;
    for (int i=0; i<3; i++) fRec48[i] = 0;
    fcheckbox8 = 0.0;
    for (int i=0; i<4; i++) fVec23[i] = 0;
    fslider23 = 0.0f;
    for (int i=0; i<6; i++) fRec0[i] = 0;
    fslider24 = 0.0f;
    fslider25 = 0.0f;
    fslider26 = 64.0f;
    fslider27 = 20.0f;
    fslider29 = 0.0f;
    fslider30 = 0.0f;
    fslider31 = 0.0f;
    fslider32 = 64.0f;
    fslider33 = 20.0f;
    fslider34 = 0.0f;
    fslider35 = 0.0f;
    fslider36 = 0.0f;
    fslider37 = 2.0f;
    fslider38 = 1.0f;
    fslider39 = 20.0f;
    fslider40 = 64.0f;
    fslider41 = 20.0f;
    fslider42 = 0.0f;
    fslider43 = 0.0f;
    fslider44 = 0.0f;
    fslider45 = 5.0f;
    midistat = 0.0f;
    fslider46 = 64;
    fslider47 = 64;
    fslider48 = 64;
    fConsthp0 = (1.0f / tanf((0.5f * (((3.141593f * fSamplingFreq) - 2764.601562f) / fSamplingFreq))));
    fConsthp1 = (1 + fConsthp0);
    fConsthp2 = (0 - ((fConsthp0 - 1) / fConsthp1));
    for (int i=0; i<2; i++) fVechp0[i] = 0;
    fConsthp3 = (1.0f / fConsthp1);
    for (int i=0; i<2; i++) fRechp0[i] = 0;
    send = 0;
    send1 = 0;
    send2 = 0;
    fTemprec1 = 0;
    drive = 1.5;
    foverdrive4 = 0.0;
    for (int i=0; i<2; i++) fRecover0[i] = 0;
    viv = 0.;
    vivi = 0.;
    playmidi = 0;
    shownote = 0;
    antialis0 = 0;
    faas1 = 0;
    ffuzzytube = 1;
    ftube = 0;
    fpredrive = 1;
    fprdr = 0;
    fautogain = 0;
    fautogain1 = 0;
    fautogain2 = 0;
    fresoon = 0;
    fvibrato = 0;
    fConstun0 = (0.001*300*fSamplingFreq)*36;
    tunerfilter = 1.0/(fSamplingFreq* (1.0f/(2.0f*M_PI*150.0f)));
    tunerstage1 = tunerstage2 = 0.0;
    tunerfilterh = 1.0/(fSamplingFreq* (1.0f/(2.0f*M_PI*12000.0f)));
    tunerstageh1 = tunerstageh2 = 0.0;
    fConstlog = log(1.055)*0.5;
    fConstlog2 = 6/log(2)*-1;
    fatan = 1;
    fwarn = 0;
    fwarn_swap = fwarn;
    fupsample = 0;
    ffuse = 0;
    fthreshold = 1;
    //ftubemode = 0;
    ftube3 = 0;
    fresotube1 = 0.12f;
    fresotube2 = 0.5f;
    fresotube3 = 0;
    //----- resonator
    IOTARESO = 0;
    for (int i=0; i<4096; i++) fVecRESO0[i] = 0;
    for (int i=0; i<2; i++) fRecRESO0[i] = 0;
    //----- oscillator
    for (int i=0; i<2; i++) iVecoscb0[i] = 0;
    fConstoscb0 = (0 - (2 * cosf((75398.226562f / fSamplingFreq))));
    for (int i=0; i<3; i++) fRecoscb0[i] = 0;
    //----- low/highpass for tube
    fConstsp0 = tanf((15707.963867f / fSamplingFreq));
    fConstsp1 = (2 * (1 - (1.0f / (fConstsp0 * fConstsp0))));
    fConstsp2 = (1.0f / fConstsp0);
    fConstsp3 = (1 + ((fConstsp2 - 0.765367f) / fConstsp0));
    fConstsp4 = (1.0f / (1 + ((0.765367f + fConstsp2) / fConstsp0)));
    fConstsp5 = (1 + ((fConstsp2 - 1.847759f) / fConstsp0));
    fConstsp6 = (1.0f / (1 + ((1.847759f + fConstsp2) / fConstsp0)));
    fConstsp7 = (408.407043f / fSamplingFreq);
    fConstsp8 = (1 - fConstsp7);
    for (int i=0; i<2; i++) fVecsp0[i] = 0;
    fConstsp9 = (1.0f / (1 + fConstsp7));
    for (int i=0; i<2; i++) fRecsp3[i] = 0;
    for (int i=0; i<2; i++) fRecsp2[i] = 0;
    for (int i=0; i<3; i++) fRecsp1[i] = 0;
    for (int i=0; i<3; i++) fRecsp0[i] = 0;

    // lets init the variables for the tonesettings
    fSlow_mid_tone = (fslider_tone1*0.5);
    fSlow_tone0 = powf(10, (2.500000e-02f * (fslider_tone0- fSlow_mid_tone)));
    fSlow_tone1 = (1 + fSlow_tone0);
    fSlow_tone2 = (fConst_tone1 * fSlow_tone1);
    fSlow_tone3 = (2 * (0 - ((1 + fSlow_tone2) - fSlow_tone0)));
    fSlow_tone4 = (fConst_tone1 * (fSlow_tone0 - 1));
    fSlow_tone5 = (fConst_tone2 * sqrtf(fSlow_tone0));
    fSlow_tone6 = (fSlow_tone1 - (fSlow_tone5 + fSlow_tone4));
    fSlow_tone7 = powf(10, (2.500000e-02f * fSlow_mid_tone));
    fSlow_tone8 = (1 + fSlow_tone7);
    fSlow_tone9 = (fConst_tone4 * fSlow_tone8);
    fSlow_tone10 = (2 * (0 - ((1 + fSlow_tone9) - fSlow_tone7)));
    fSlow_tone11 = (fSlow_tone7 - 1);
    fSlow_tone12 = (fConst_tone4 * fSlow_tone11);
    fSlow_tone13 = sqrtf(fSlow_tone7);
    fSlow_tone14 = (fConst_tone5 * fSlow_tone13);
    fSlow_tone15 = (fSlow_tone8 - (fSlow_tone14 + fSlow_tone12));
    fSlow_tone16 = (fConst_tone1 * fSlow_tone8);
    fSlow_tone17 = (0 - (2 * ((fSlow_tone7 + fSlow_tone16) - 1)));
    fSlow_tone18 = (fConst_tone2 * fSlow_tone13);
    fSlow_tone19 = (fConst_tone1 * fSlow_tone11);
    fSlow_tone20 = ((1 + (fSlow_tone7 + fSlow_tone19)) - fSlow_tone18);
    fSlow_tone21 = powf(10, (2.500000e-02f * (fslider_tone2-fSlow_mid_tone)));
    fSlow_tone22 = (1 + fSlow_tone21);
    fSlow_tone23 = (fConst_tone4 * fSlow_tone22);
    fSlow_tone24 = (0 - (2 * ((fSlow_tone21 + fSlow_tone23) - 1)));
    fSlow_tone25 = (fConst_tone5 * sqrtf(fSlow_tone21));
    fSlow_tone26 = (fConst_tone4 * (fSlow_tone21 - 1));
    fSlow_tone27 = ((1 + (fSlow_tone21 + fSlow_tone26)) - fSlow_tone25);
    fSlow_tone28 = (2 * (0 - ((1 + fSlow_tone23) - fSlow_tone21)));
    fSlow_tone29 = (fSlow_tone21 + fSlow_tone25);
    fSlow_tone30 = ((1 + fSlow_tone29) - fSlow_tone26);
    fSlow_tone31 = (fSlow_tone22 - (fSlow_tone25 + fSlow_tone26));
    fSlow_tone32 = (1.0f / (1 + (fSlow_tone26 + fSlow_tone29)));
    fSlow_tone33 = (fSlow_tone8 - (fSlow_tone18 + fSlow_tone19));
    fSlow_tone34 = (2 * (0 - ((1 + fSlow_tone16) - fSlow_tone7)));
    fSlow_tone35 = (fSlow_tone7 + fSlow_tone18);
    fSlow_tone36 = ((1 + fSlow_tone35) - fSlow_tone19);
    fSlow_tone37 = (1.0f / (1 + (fSlow_tone19 + fSlow_tone35)));
    fSlow_tone38 = (fSlow_tone7 * ((1 + (fSlow_tone7 + fSlow_tone12)) - fSlow_tone14));
    fSlow_tone39 = (fSlow_tone7 + fSlow_tone14);
    fSlow_tone40 = (fSlow_tone7 * (1 + (fSlow_tone12 + fSlow_tone39)));
    fSlow_tone41 = (((fSlow_tone7 + fSlow_tone9) - 1) * (0 - (2 * fSlow_tone7)));
    fSlow_tone42 = (1.0f / ((1 + fSlow_tone39) - fSlow_tone12));
    fSlow_tone43 = (fSlow_tone0 * ((1 + (fSlow_tone0 + fSlow_tone4)) - fSlow_tone5));
    fSlow_tone44 = (fSlow_tone0 + fSlow_tone5);
    fSlow_tone45 = (fSlow_tone0 * (1 + (fSlow_tone4 + fSlow_tone44)));
    fSlow_tone46 = (((fSlow_tone0 + fSlow_tone2) - 1) * (0 - (2 * fSlow_tone0)));
    fSlow_tone47 = (1.0f / ((1 + fSlow_tone44) - fSlow_tone4));
    fslider_tone_check = (fslider_tone1+fslider_tone0+fslider_tone2)*100;
    fslider_tone_check1 = 0;
    // end

  }

  virtual void init(int samplingFreq)
  {
    classInit(samplingFreq);
    instanceInit(samplingFreq);
  }

  // wrap the state off the latency cange warning (dis/enable) to the interface settings
  // to load and save it
  virtual void set_state()
  {
    fwarn_swap = fwarn;
  }

  virtual void get_state()
  {
    fwarn = fwarn_swap;
  }

  // this files are part off the dsp class, I have split it for a better overview
#include"dsp_interface.cpp"
  // I can`t realy remove the midi_ringbuffer part, we dont need it, maybe later
  // when we add a sequencer part the ringbuffer may be usefull.
#ifdef USE_RINGBUFFER
#include"dsp_midi.cpp"
#else
#include"dsp_midi_noringbuffer.cpp"
#endif
#include"dsp_audio.cpp"
};

