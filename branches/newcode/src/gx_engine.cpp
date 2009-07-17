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
 *
 *
 *	This is the guitarix engine definitions
 *
 *
 * --------------------------------------------------------------------------
 */

#include <string>
#include <list>
#include <map>
#include <vector>
#include <iostream>

using namespace std;

#include <cmath>
#include <gtk/gtk.h>
#include <jack/jack.h>
#include <jack/midiport.h>
#include <sndfile.h>

#include "guitarix.h"

using namespace gx_system;

namespace gx_engine 
{
  // static member
  GxMidiState dsp::midistate = kMidiOff;

  // instanciation
  inline GxEngine* GxEngine::instance() 
  {
    static GxEngine engine; 
    return &engine;
  }

  void GxEngine::metadata(Meta* m)
  {
    m->declare("name", "guitarix");
    m->declare("version", "0.01");
    m->declare("author", "brummer");
    m->declare("contributor", "Julius O. Smith (jos at ccrma.stanford.edu)");
    m->declare("license", "BSD");
    m->declare("copyright", "(c)brummer 2008");
    m->declare("reference", "http://ccrma.stanford.edu/realsimple/faust_strings/");
  }

  void GxEngine::initEngine(int samplingFreq)
  {
    // initialize all variables for audio, midi and interface
    fSamplingFreq = samplingFreq;

    // --- compressor
    fentrycom0 = -20.000000f;

    fConstcom0 = expf((0 - (10.000000f / fSamplingFreq)));
    fConstcom1 = (1 - fConstcom0);

    zeroize(fReccom1, 2);
    zeroize(fReccom2, 2);

    fConstcom2 = (1.000000f / fSamplingFreq);
    fslidercom0 = 2.000000e-03f;
    fslidercom1 = 0.500000f;

    zeroize(fReccom0, 2);

    fentrycom1 = 3.000000f;
    fentrycom2 = 2.000000f;
    // --- compressor end


    fConstan0 = (3.141593f / fSamplingFreq);
    fConstan1 = (251.327423f / fSamplingFreq);
    fConstan2 = (1 - fConstan1);

    zeroize(fVect0, 2);

    fConstan3 = (1.0f / (1 + fConstan1));

    zeroize(fRect5, 2);
    zeroize(fVect1, 2);
    zeroize(fRect4, 2);
    zeroize(iRect3, 2);
    zeroize(iRect2, 2);
    zeroize(iRect1, 2);
    zeroize(fRect0, 2);

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

    zeroize(fVec_tone0, 3);
    zeroize(fRec_tone3, 3);
    zeroize(fRec_tone2, 3);
    zeroize(fRec_tone1, 3);
    zeroize(fRec_tone0, 3);
    // tone end

    zeroize(fVec0, 3);

    // engine state
    checky = (float)kEngineOn;

    fcheckbox1 = 0.0;
    fslider3 = 0.0f;

    zeroize(fRec4, 2); 
    zeroize(fRec3, 2);

    fslider4 = 0.12f;

    IOTA = 0;

    zeroize(fVec1, 4096);
    fslider5 = 0.5f;

    zeroize(fRec6, 2);

    fentry0 = 723.0f;
    fConst6 = (3.141593f / fSamplingFreq);

    zeroize(fVec2, 2);
    zeroize(fRec8, 2);

    fentry1 = 720.0f;
    fConst7 = (3.141593f * fSamplingFreq);
    fConst8 = (0.5f / fSamplingFreq);

    zeroize(fVec3, 2);
    zeroize(fRec7, 2);

    fcheckbox2 = 1.0;
    fslider6 = 5000.0f;
    fslider7 = 130.0f;

    zeroize(fVec4 , 2);
    zeroize(fRec12, 2);
    zeroize(fVec5 , 2);
    zeroize(fRec11, 2);

    zeroize(fRec10, 3);
    zeroize(fRec9 , 3);

    fcheckbox3 = 1.0;
    fslider8 = 1.000000e-02f;
    fslider9 = 0.64f;

    zeroize(fVec6, 2);
    zeroize(fRec5, 2);

    fslider10 = 2.0f;

    zeroize(fRec13, 2);
    zeroize(fVec7 , 2);
    zeroize(fRec17, 2);
    zeroize(fVec8 , 2);
    zeroize(fRec16, 2);

    zeroize(fRec15, 3);
    zeroize(fRec14, 3);

    fcheckbox4 = 1.0;
    fslider11 = 0.0f;

    zeroize(fRec19, 2);

    fslider12 = 0.1f;
    fslider13 = 0.0f;
    fConst9 = (2827.43335f / fSamplingFreq);
    fConst10 = (1413.716675f / fSamplingFreq);

    zeroize(fRec20, 2);
    zeroize(fRec21, 2);
    zeroize(fRec18, 3);

    fcheckbox5 = 0.0;
    fslider14 = 0.3333f;
    fslider15 = 0.5f;

    for (int i=0; i<2; i++) fRec31[i] = 0;

    fslider16 = 0.5f;

    zeroize(fVec10, 2048);
    zeroize(fRec30, 2);
    zeroize(fRec33, 2);
    zeroize(fVec11, 2048);
    zeroize(fRec32, 2);
    zeroize(fRec35, 2);
    zeroize(fVec12, 2048);
    zeroize(fRec34, 2);
    zeroize(fRec37, 2);
    zeroize(fVec13, 2048);
    zeroize(fRec36, 2);
    zeroize(fRec39, 2);
    zeroize(fVec14, 2048);
    zeroize(fRec38, 2);
    zeroize(fRec41, 2);
    zeroize(fVec15, 2048);
    zeroize(fRec40, 2);
    zeroize(fRec43, 2);
    zeroize(fVec16, 2048);
    zeroize(fRec42, 2);
    zeroize(fRec45, 2);
    zeroize(fVec17, 2048);
    zeroize(fRec44, 2);
    zeroize(fVec18, 1024);
    zeroize(fRec28, 2);
    zeroize(fVec19, 512);
    zeroize(fRec26, 2);
    zeroize(fVec20, 512);
    zeroize(fRec24, 2);
    zeroize(fVec21, 256);
    zeroize(fRec22, 2);

    fcheckbox6 = 0.0;
    fslider17 = 0.0f;

    zeroize(fRec46, 2);

    fslider18 = 0.0f;
    fConst11 = (1.000000e-03f * fSamplingFreq);
    fslider19 = 0.0f;

    zeroize(fRec47, 262144);

    fcheckbox7 = 0.0;

    zeroize(fVec22, 3);

    fslider20 = 100.0f;
    fslider21 = 440.0f;
    fConst12 = (6.283185f / fSamplingFreq);
    fslider22 = 1.0f;

    zeroize(fRec48, 3);

    fcheckbox8 = 0.0;

    zeroize(fVec23, 4);

    fslider23 = 0.0f;

    zeroize(fRec0, 6);

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

    midistat  = 0.0f;

    fslider46 = 64;
    fslider47 = 64;
    fslider48 = 64;

    fConsthp0 = (1.0f / tanf((0.5f * (((3.141593f * fSamplingFreq) - 2764.601562f) / fSamplingFreq))));
    fConsthp1 = (1 + fConsthp0);
    fConsthp2 = (0 - ((fConsthp0 - 1) / fConsthp1));

    zeroize(fVechp0, 2);

    fConsthp3 = (1.0f / fConsthp1);

    zeroize(fRechp0, 2);

    send = 0;
    send1 = 0;
    send2 = 0;

    fTemprec1 = 0;
    drive = 1.5;
    foverdrive4 = 0.0;

    zeroize(fRecover0, 2);

    viv = 0.;
    vivi = 0.;

    dsp::turnOffMidi();
    gx_gui::shownote = 0;

    antialis0  = 0;
    faas1      = 0;
    ffuzzytube = 1;
    ftube      = 0;
    fpredrive  = 1;
    fprdr      = 0;
    fautogain  = 0;
    fautogain1 = 0;
    fautogain2 = 0;
    fresoon    = 0;
    fvibrato   = 0;
    fConstun0  = (0.001*300*fSamplingFreq)*36;

    tunerfilter  = 1.0/(fSamplingFreq* (1.0f/(2.0f*M_PI*150.0f)));
    tunerstage1  = tunerstage2 = 0.0;
    tunerfilterh = 1.0/(fSamplingFreq* (1.0f/(2.0f*M_PI*12000.0f)));
    tunerstageh1 = tunerstageh2 = 0.0;

    fConstlog  = log(1.055)*0.5;
    fConstlog2 = 6/log(2)*-1;

    fatan = 1;
    fwarn = 0;

    fwarn_swap = fwarn;

    fupsample  = 0;
    ffuse      = 0;
    fthreshold = 1;

    //ftubemode = 0;
    ftube3 = 0;
    fresotube1 = 0.12f;
    fresotube2 = 0.5f;
    fresotube3 = 0;

    //----- resonator
    IOTARESO = 0;
    zeroize(fVecRESO0, 4096);
    zeroize(fRecRESO0, 2);

    //----- oscillator
    zeroize(iVecoscb0, 2);
    fConstoscb0 = (0 - (2 * cosf((75398.226562f / fSamplingFreq))));
    zeroize(fRecoscb0, 3);

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

    zeroize(fVecsp0, 2);

    fConstsp9 = (1.0f / (1 + fConstsp7));

    zeroize(fRecsp3, 2);
    zeroize(fRecsp2, 2);
    zeroize(fRecsp1, 3);
    zeroize(fRecsp0, 3);

    // lets init the variables for the tonesettings
    fSlow_mid_tone = (fslider_tone1*0.5);

    fSlow_tone0  = powf(10, (2.500000e-02f * (fslider_tone0- fSlow_mid_tone)));
    fSlow_tone1  = (1 + fSlow_tone0);
    fSlow_tone2  = (fConst_tone1 * fSlow_tone1);
    fSlow_tone3  = (2 * (0 - ((1 + fSlow_tone2) - fSlow_tone0)));
    fSlow_tone4  = (fConst_tone1 * (fSlow_tone0 - 1));
    fSlow_tone5  = (fConst_tone2 * sqrtf(fSlow_tone0));
    fSlow_tone6  = (fSlow_tone1 - (fSlow_tone5 + fSlow_tone4));
    fSlow_tone7  = powf(10, (2.500000e-02f * fSlow_mid_tone));
    fSlow_tone8  = (1 + fSlow_tone7);
    fSlow_tone9  = (fConst_tone4 * fSlow_tone8);
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
    // end engine init
  }

  /* --- adding rest of engine class by file inclusion for readability --- */

  /* engine GUI */
#include "gx_engine_ui_builder.cpp"

  /* MIDI engine */
#ifdef USE_RINGBUFFER
#include "gx_engine_midi_ringbuf.cpp"
#else
#include "gx_engine_midi.cpp"
#endif

  /* audio engine */
#include "gx_engine_audio.cpp"


  /* --- forward definition of useful namespace functions --- */
  void gx_engine_init(int& argc, char**& argv)
  {
    GxEngine* engine = GxEngine::instance();
    gNumInChans  = engine->getNumInputs();
    gNumOutChans = engine->getNumOutputs();
    
    
    //----- lock the buffer for the oscilloscope
    const int frag = (const int)gx_jack::jack_bs;

    get_frame  = new float[frag];
    checkfreq  = new float[frag];
    oversample = new float[frag*2];

    (void)memset(get_frame,  0, frag*sizeof(float));
    (void)memset(checkfreq,  0, frag*sizeof(float));
    (void)memset(oversample, 0, frag*2*sizeof(float));

    //----- build the GUI interface virtual
    const char* jname = jack_get_client_name(gx_jack::client);

    gx_gui::GxMainInterface* interface = 
      gx_gui::GxMainInterface::instance(jname, &argc, &argv);

    engine->initEngine((int)gx_jack::jack_sr);
    engine->buildUserInterface(interface);

    // turn on logging window by default
    //    gx_gui::gx_log_window(NULL, NULL);

    string previous_state = gx_user_dir + string(jname) + "rc";
    interface->recallState(previous_state.c_str());

    //----- save the state for the latency change warning widget
    engine->set_latency_warning_change();
  }

  //----menu function play stop
  void gx_engine_switch (GtkWidget* widget, gpointer arg)
  {
    GxEngineState estate = (GxEngineState)checky;

    switch (estate) {
    case kEngineOn:
      estate = kEngineOff;
      if (arg) {  
	// need to activate item
	gtk_check_menu_item_set_active(
	    GTK_CHECK_MENU_ITEM(gx_gui::gx_engine_item), TRUE);
	estate = kEngineBypass;
      }

      break;

    case kEngineOff:
      if (!arg)
	estate = kEngineOn;
      break;
    
    default:
      estate = kEngineOn;
      gtk_check_menu_item_set_active(
	  GTK_CHECK_MENU_ITEM(gx_gui::gx_engine_item), TRUE);
    }

    checky = (float)estate;
    gx_refresh_engine_status_display();
  }

  //----refresh status display
  void gx_refresh_engine_status_display()
  {
    GxEngineState estate = (GxEngineState)checky;
    string state;

    switch (estate) {

    case kEngineOff:
      gtk_widget_show(gx_gui::gx_engine_off_image);
      gtk_widget_hide(gx_gui::gx_engine_on_image);
      gtk_widget_hide(gx_gui::gx_engine_bypass_image);

      gtk_check_menu_item_set_active(
	  GTK_CHECK_MENU_ITEM(gx_gui::gx_engine_item), FALSE);
      state = "OFF";
      break;

    case kEngineBypass:
      gtk_widget_show(gx_gui::gx_engine_bypass_image);
      gtk_widget_hide(gx_gui::gx_engine_off_image);
      gtk_widget_hide(gx_gui::gx_engine_on_image);

      gtk_check_menu_item_set_active(
          GTK_CHECK_MENU_ITEM(gx_gui::gx_engine_item), TRUE);
      state = "BYPASSED";
      break;

    case kEngineOn:
    default: // ON
      gtk_widget_show(gx_gui::gx_engine_on_image);
      gtk_widget_hide(gx_gui::gx_engine_off_image);
      gtk_widget_hide(gx_gui::gx_engine_bypass_image);

      gtk_check_menu_item_set_active(
          GTK_CHECK_MENU_ITEM(gx_gui::gx_engine_item), TRUE);
      state = "ON";
    }

    gx_print_info("Engine State: ", state);
  }

} /* end of gx_engine namespace */
