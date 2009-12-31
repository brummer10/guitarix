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
* ---------------------------------------------------------------------------
*
*    This is the guitarix GUI builder
*
* ----------------------------------------------------------------------------
*/

/* -------- user interface builder ---------- */
void GxMainInterface::setup()
{
  //----- notebook window with tabs representing jack clients and portmaps
  // Note: out of box stack scheme.
  createPortMapWindow("Jack Port Maps");

  gx_engine::GxEngine* engine = gx_engine::GxEngine::instance();

  //----- the main box, all visible widgets are a child of this box
  openVerticalBox("");

  //----- add the menubar on top
  {
    addMainMenu();

    //----- this is a dummy widget, only for save settings for the latency warning dialog
    openWarningBox("WARNING", &engine->fwarn);
    setSkinBox("SKIN", &engine->fskin);
    closeBox();

    //----- the upper box,
    openVerticalBox("");
    {
      openEventBox(" ");
      openPaintBox2("");
      {
        openHorizontalBox("");
        {

          //----- the tuner widget
          openVerticalBox("");
          {
            addNumDisplay("", &engine->fConsta1);
          }
          closeBox();

          //----- the balance widget
          openVerticalBox("");
          {
            addslider("balance", &engine->fslider25, 0.f, -1.f, 1.f, 1.e-01f);
          }
          closeBox();

          //----- the jconv widget on the main window
          openFrameBox("");
          {
            openExpanderBox(" jconv ", &engine->fexpand2);
            {
              openHandleBox("  ");
              {
                openVerticalBox("");
                {
                  openHorizontalBox("");
                  {
                    openDialogBox("jconv", &engine->fdialogboxj);
                    {
                      openHandleBox("  ");
                      {
                        openFrameBox("");
                        closeBox();
                        openFrameBox("");
                        closeBox();
                        openVerticalBox("");
                        {
                          openHorizontalTableBox("");
                          {
                            addregler(" left delay ", &engine->fsliderdel0,  0.f, 0.f, 5000.0f, 10.f);
                            addregler(" right delay ", &engine->fsliderdel1,  0.f, 0.f, 5000.0f, 10.f);

                            addregler(" left gain ", &engine->fjc_ingain,  0.f, -20.f, 20.f, 0.1f);
                            addregler(" right gain ", &engine->fjc_ingain1,  0.f, -20.f, 20.f, 0.1f);
                          }
                          closeBox();
                        }
                        closeBox();
                        openFrameBox("");
                        closeBox();
                        openFrameBox("");
                        closeBox();
                      }
                      closeBox();
                    }
                    closeBox();
                    addslider("wet/dry", &engine->fslider24,  0.f, -1.f, 1.f, 1.e-01f);
                  }
                  closeBox();

                  openVerticalBox("");
                  {
                    addJConvButton("jconv settings", &engine->filebutton);
                    addJToggleButton("run jconv", &gx_jconv::GxJConvSettings::checkbutton7);
                  }
                  closeBox();
                }
                closeBox();
              }
              closeBox();
            }
            closeBox();
          }
          closeBox();
        }
        closeBox();
      }
      closeBox();
    }
    closeBox();
    //----- end of the upper box

    //----- the middle box,
    openExpanderBox(" CONTROLS ", &engine->fexpand);
    {
      //----- a handle box is a vertical box
      openHandleBox("  ");
      {
        //----- arange all widgets in a horizontal scale
        openHorizontalBox("");
        {
          //----- arange all widgets in a vertical scale
          openVerticalBox("");
          {
            //----- the left widget side, volume, tone, fuzz
            openHorizontalBox("");
            {
              //----- open a box for the volume controllers
              openFrameBox("");
              closeBox();
              openVerticalBox("");
              {
                openFrameBox("");
                closeBox();
                // add a meter level box: out of box stack, no need to closeBox
                openLevelMeterBox("Signal Level");
                openFrameBox("");
                closeBox();
              }
              closeBox();
              openFrameBox("");
              closeBox();

              openVerticalBox("volume");
              {
                openVerticalBox("");
                {
                  addbigregler(" in / level ", &engine->fslider3, 0.f, -40.f, 40.f, 0.1f);
                  addbigregler("out / master", &engine->fslider17, 0.f, -40.f, 40.f, 0.1f);
                }
                closeBox();
              }
              closeBox();
              //----- volume controll ready

              //----- open a box for the tone and the fuzz controllers
              openVerticalBox("tone");
              {
                addregler("bass",   &engine->fslider_tone2, 0.f, -20.f, 20.f, 0.1f);
                addregler("middle", &engine->fslider_tone1, 0.f, -20.f, 20.f, 0.1f);
                addregler("treble", &engine->fslider_tone0, 0.f, -20.f, 20.f, 0.1f);
                openVerticalBox1("");
                closeBox();
              }
              closeBox();
            }
            closeBox();
            //----- end tone and fuzz controll

            //----- the next part in the vertical box,
            openVerticalBox("");
            {
              openHorizontalBox("");
              {
                openVerticalBox("shaper ");
                {
                  addswitch("", &engine->fng);
                  openFrameBox("");
                  {
                    addHorizontalWheel("sharper",&engine->fsharp0, 1.f, 1.f, 10.f, 1.0f);
                  }
                  closeBox();
                }
                closeBox();
                openVerticalBox("     noise gate      ");
                {
                  addswitch("", &engine->fnoise_g);
                  openFrameBox("");
                  {
                    addHorizontalWheel(" threshold ", &engine->fnglevel, 0.017f, 0.01f, 0.21f, 0.001f);
                  }
                  closeBox();
                }
                closeBox();
                openVerticalBox("anti aliase");
                {
                  addswitch("", &engine->antialis0);
                  openFrameBox("");
                  {
                    addHorizontalWheel(" feedback ", &engine->faas1, 0.3f, 0.3f, 0.9f, 0.01f);
                  }
                  closeBox();
                }
                closeBox();
              }
              closeBox();

              openVerticalBox("amp  ");
              {
                openHorizontalBox("");
                {
                  openFrameBox("");
                  {
                  }
                  closeBox();
                  addminiswitch(" oversample       ", &engine->fupsample);
                  openVerticalBox1("");
                  {
                  }
                  closeBox();
                  addminiswitch(" bass booster      ", &engine->fboost);
                  openVerticalBox1("");
                  {
                  }
                  closeBox();
                }
                closeBox();
              }
              closeBox();
              //----- the second part in the vertical box
              openHorizontalBox("");
              {
                openVerticalBox("");
                {
                  openVerticalBox("");
                  {
                    addswitch("preamp", &engine->fcheckbox1);
                    addHorizontalWheel("atan",&engine->fatan, 1.f, 1.f, 10.f, 1.0f);
                  }
                  closeBox();
                  openFrameBox("");
                  {
                  }
                  closeBox();
                  openVerticalBox("");
                  {
                    addswitch("drive", &engine->fprdr);
                    addHorizontalWheel("drive", &engine->fpredrive, 1.f, 1.f, 10.f, 1.0f);
                  }
                  closeBox();
                }
                closeBox();
                openFrameBox("");
                closeBox();
                openVerticalBox("");
                {
                  openVerticalBox("");
                  {
                    addswitch("tube", &engine->ftube);
                    addHorizontalWheel("tube",&engine->ffuzzytube, 1.f, -3.f, 10.f, 1.0f);
                  }
                  closeBox();
                  openFrameBox("");
                  {
                  }
                  closeBox();
                  openVerticalBox("");
                  {
                    addswitch("vibrato", &engine->fresoon);
                    addHorizontalWheel("vibrato", &engine->fvibrato, 0.f, 0.f, 2.f, 0.02f);
                  }
                  closeBox();

                }
                closeBox();
                openFrameBox("");
                closeBox();
                openVerticalBox("");
                {
                  openVerticalBox("");
                  {
                    addswitch("tube2", &engine->ftube3);
                    openFrameBox("");
                    {
                      addHorizontalWheel("tube", &engine->fresotube3, 1.f, -3.f, 10.f, 1.0f);
                    }
                    closeBox();
                  }
                  closeBox();
                  openVerticalBox("");
                  {
                    openVerticalBox1("resonanz");
                    {
                      addHorizontalWheel("reso", &engine->fresotube1, 0.5f, 0.f, 0.9f, 0.01f);
                    }
                    closeBox();
                    openVerticalBox1("vibrato");
                    {
                      addHorizontalWheel("vibrato", &engine->fresotube2, 1.f, 0.f, 1.f, 0.01f);
                    }
                    closeBox();
                  }
                  closeBox();
                }
                closeBox();
              }
              closeBox();
              openFrameBox("");
              closeBox();
              openFrameBox("");
              closeBox();
            }
            closeBox();
          }
          closeBox();
          //----- end
          openFrameBox("");
          closeBox();
          //----- this box include all effects and the osccilloscope
          openHorizontalBox("");
          {
            openFrameBox("");
            closeBox();
            openFrameBox("");
            closeBox();
            openFrameBox("");
            closeBox();
            openVerticalBox1("");
            {
              openHorizontalBox("");
              {
              }
              closeBox();

              //----- this box include only the effects
              openScrollBox("");
              {
                openHorizontalBox("");
                {
                  openHorizontalTableBox("");
                  {
                    //----- the compressor
                    openHorizontalOrderBox("", &engine->posit5);
                    {
                      openVerticalBox("compressor");
                      {
                        addregler("ratio", &engine->fentrycom2, 2.000000f, 1.000000f, 20.000000f, 0.100000f);
                        openHorizontalBox("");
                        {
                          addtoggle("", &engine->fcheckboxcom1);
                          //----- open a dialogbox(toplevel widget) and put the advanced controlls in it
                          openDialogBox("compressor", &engine->fdialogbox8);
                          {
                            openHandleBox("  ");
                            {
                              openFrameBox("");
                              closeBox();
                              openFrameBox("");
                              closeBox();
                              openVerticalBox("compressor");
                              {
                                openHorizontalBox("");
                                {
                                  addregler("knee",      &engine->fentrycom1, 3.000000f, 0.000000f, 20.000000f, 0.100000f);
                                  addregler("ratio",     &engine->fentrycom2, 2.000000f, 1.000000f, 20.000000f, 0.100000f);
                                  addregler("threshold", &engine->fentrycom0, -20.000000f, -96.000000f, 10.000000f, 0.100000f);
                                }
                                closeBox();
                                openVerticalBox("envelop");
                                {
                                  addslider("attack",  &engine->fslidercom0, 2.000000e-03f, 0.000000f, 1.000000f, 1.000000e-03f);
                                  addslider("release", &engine->fslidercom1, 0.500000f, 0.000000f, 10.000000f, 1.000000e-02f);
                                }
                                closeBox();
                              }
                              closeBox();
                              openFrameBox("");
                              closeBox();
                              openFrameBox("");
                              closeBox();
                            }
                            closeBox();
                          }
                          closeBox();
                        }
                        //----- end advanced settings widget
                        closeBox();
                      }
                      closeBox();
                      //----- end compressor
                    }
                    closeBox();
                    openHorizontalOrderBox("", &engine->posit1);
                    {
                      //----- overdrive
                      openVerticalBox("overdrive");
                      {
                        addregler("  drive ", &engine->drive, 1.f, 1.f, 20.f, 0.1f);
                        addtoggle("", &engine->foverdrive4);
                      }
                      closeBox();
                      //-----end overdrive
                    }
                    closeBox();
                    openHorizontalOrderBox("", &engine->posit2);
                    {
                      //----- distortion
                      openVerticalBox(" distortion");
                      {
                        addregler("  drive ", &engine->fslider9, 0.64f, 0.f, 1.f, 1.e-02f);
                        openHorizontalBox("");
                        {
                          addtoggle("", &engine->fcheckbox4);

                          //----- open a dialogbox(toplevel widget) and put the advanced controlls in it
                          {
                            openDialogBox("distortion", &engine->fdialogbox1);
                            {
                              openHandleBox("  ");
                              {
                                addbigregler("  drive ", &engine->fslider9, 0.64f, 0.f, 1.f, 1.e-02f);
                                addregler("level", &engine->fslider8, 1.000000e-02f, 0.0f, 0.50f, 1.000000e-02f);
                                addregler("gain",  &engine->fslider10, 2.0f, -10.0f, 10.0f, 0.1f);

                                openVerticalBox("low/highpass");
                                {
                                  openHorizontalBox("");
                                  {
                                    addregler("high-freq ", &engine->fentry1, 130.0f, 20.0f, 7040.0f, 10.0f);
                                    addregler(" low-freq ", &engine->fentry0, 5000.0f, 20.0f, 12000.0f, 10.0f);
                                  }
                                  closeBox();

                                  addtoggle("", &engine->fcheckbox2);
                                }
                                closeBox();

                                openVerticalBox("low/highcutoff");
                                {
                                  openHorizontalBox("");
                                  {
                                    addregler("high-freq ", &engine->fslider6, 5000.0f, 1000.0f, 12000.0f, 10.0f);
                                    addregler(" low-freq ", &engine->fslider7, 130.0f, 20.0f, 1000.0f, 10.0f);
                                  }
                                  closeBox();

                                  addtoggle("", &engine->fcheckbox3);
                                }
                                closeBox();

                                openHorizontalBox("resonanz");
                                {
                                  addregler("trigger ",  &engine->fslider4, 0.12f, 0.0f, 1.0f, 1.000000e-02f);
                                  addregler(" vibrato ", &engine->fslider5, 1.0f, 0.0f, 1.0f, 1.000000e-02f);
                                }
                                closeBox();
                              }
                              closeBox();
                            }
                            closeBox();
                          }
                          //----- end advanced settings widget
                          closeBox();
                        }
                        closeBox();
                        //----- end distortion
                      }
                      closeBox();

                      openHorizontalOrderBox("", &engine->posit3);
                      {
                        //----- freeverb
                        openVerticalBox(" freeverb");
                        {
                          addregler("RoomSize", &engine->fslider16, 0.500000f, 0.000000f, 1.000000f, 2.500000e-02f);
                          openHorizontalBox("");
                          {
                            addtoggle("", &engine->fcheckbox6);
                            //----- open a dialogbox(toplevel widget) and put the advanced controlls in it
                            openDialogBox("freeverb", &engine->fdialogbox2);
                            {
                              openHandleBox("  ");
                              {
                                openFrameBox("");
                                closeBox();
                                openFrameBox("");
                                closeBox();
                                addregler("RoomSize", &engine->fslider16, 0.500000f, 0.000000f, 1.000000f, 2.500000e-02f);
                                addregler("damp", &engine->fslider15, 0.5f, 0.0f, 1.0f, 2.500000e-02f);
                                addregler("wet/dry", &engine->fslider14, 0.0f, -0.5f, 0.5f, 1.e-01f);
                                openFrameBox("");
                                closeBox();
                                openFrameBox("");
                                closeBox();
                              }
                              closeBox();
                            }
                            closeBox();
                          }
                          //----- end advanced settings widget
                          closeBox();
                        }
                        closeBox();
                        //----- end freeverb
                      }
                      closeBox();

                      openHorizontalOrderBox("", &engine->posit4);
                      {
                        //----- IR
                        openVerticalBox("IR");
                        {
                          openHorizontalBox("");
                          {
                            addregler("   freq   ", &engine->fslider21, 440.000000f, 20.000000f, 12000.000000f, 10.000000f);
                            //addregler(" peak ", &engine->fslider22, 1.000000f, 0.000000f, 10.000000f, 0.200000f);
                          }
                          closeBox();
                          openHorizontalBox("");
                          {
                            addtoggle("", &engine->fcheckbox8);
                            //----- open a dialogbox(toplevel widget) and put the advanced controlls in it
                            openDialogBox("ImpulseResponse", &engine->fdialogbox3);
                            {
                              openHandleBox("  ");
                              {
                                openFrameBox("");
                                closeBox();
                                openFrameBox("");
                                closeBox();
                                addregler("    freq     ", &engine->fslider21, 440.000000f, 20.000000f, 12000.000000f, 10.000000f);
                                addregler("     peak    ", &engine->fslider22, 1.000000f, 0.000000f, 10.000000f, 0.200000f);
                                addregler("    bandwidth    ", &engine->fslider20, 100.0f, 20.0f, 20000.0f, 10.0f);
                                openFrameBox("");
                                closeBox();
                                openFrameBox("");
                                closeBox();
                              }
                              closeBox();
                            }
                            closeBox();
                          }
                          //----- end advanced settings widget
                          closeBox();
                        }
                        closeBox();
                        //----- end IR
                      }
                      closeBox();

                      openHorizontalOrderBox("", &engine->posit0);
                      {
                        //----- crybaby
                        openVerticalBox("crybaby");
                        {
                          addregler(" wah ", &engine->fslider11, 0.000000f, 0.000000f, 1.000000f, 1.000000e-02f);
                          openHorizontalBox("");
                          {
                            addtoggle("", &engine->fcheckbox5);
                            //----- open a dialogbox(toplevel widget) and put the advanced controlls in it
                            openDialogBox("crybaby", &engine->fdialogbox4);
                            {
                              openHandleBox("  ");
                              {
                                openFrameBox("");
                                closeBox();
                                openFrameBox("");
                                closeBox();
                                openVerticalBox("");
                                {
                                  openHorizontalTableBox("");
                                  {
                                    addregler("  wah   ", &engine->fslider11, 0.0f, 0.0f, 1.0f, 1.000000e-02f);
                                    addregler("  level  ", &engine->fslider12, 0.1f, 0.0f, 1.0f, 1.000000e-02f);
                                    addregler("wet/dry", &engine->fslider13, 0.f, -1.f, 1.f, 1.e-01f);
                                  }
                                  closeBox();
                                  addminiswitch(" autowah", &engine->fautowah);
                                }
                                closeBox();
                                openFrameBox("");
                                closeBox();
                                openFrameBox("");
                                closeBox();
                              }
                              closeBox();
                            }
                            closeBox();
                          }
                          //----- end advanced settings widget
                          closeBox();
                        }
                        closeBox();
                        //----- end crybaby
                      }
                      closeBox();

                      openHorizontalOrderBox("", &engine->posit6);
                      {
                        //----- echo
                        openVerticalBox("echo");
                        {
                          openHorizontalBox("");
                          {
                            addregler("    %    ", &engine->fslider19, 0.000000f, 0.000000f, 100.000000f, 0.100000f);
                            addregler("  time  ", &engine->fslider18, 1.000000f, 1.000000f, 2000.000000f, 1.000000f);
                          }
                          closeBox();
                          addtoggle("", &engine->fcheckbox7);
                        }
                        closeBox();
                      }
                      closeBox();
                    }
                    //----- end echo
                    openHorizontalOrderBox("", &engine->posit7);
                    {
                      openVerticalBox("delay");
                      {
                        openHorizontalBox("");
                        {
                          addregler(" delay ", &engine->fsliderdel2,  0.f, 0.f, 5000.0f, 10.f);
                          addregler("  gain ", &engine->fdel_gain1, 0.0f, -20.0f, 20.0f, 0.1f);
                        }
                        closeBox();
                        addtoggle("", &engine->fdelay);

                      }
                      closeBox();
                    }
                    closeBox();

                  }
                  closeBox();
                  //----- chorus
                  openHorizontalRestetBox("", &engine->posit8);
                  {
                    openVerticalBox("chorus");
                    {
                      addregler("level", &engine->fslider_CH3, 0.5f, 0.0f, 1.0f, 1.000000e-02f);
                      openHorizontalBox("");
                      {
                        addtoggle("", &engine->fchorus);
                        openDialogBox("chorus", &engine->fchorusbox);
                        {
                          openHandleBox("  ");
                          {
                            openVerticalBox("");
                            {
                              openHorizontalTableBox("");
                              {
                                addregler("  level  ", &engine->fslider_CH3, 0.5f, 0.0f, 1.0f, 1.000000e-02f);
                                addregler("  delay  ", &engine->fslider_CH2, 2.500000e-02f, 0.0f, 0.2f, 1.000000e-03f);
                                addregler("  depth  ", &engine->fslider_CH1, 2.000000e-02f, 0.0f, 1.0f, 1.000000e-03f);
                                addregler("  freq  ", &engine->fslider_CH0, 3.0f, 0.0f, 10.0f, 1.000000e-02f);
                              }
                              closeBox();
                            }
                            closeBox();
                          }
                          closeBox();
                        }
                        closeBox();
                      }
                      closeBox();
                    }
                    closeBox();
                  }
                  closeBox();
                  //end chorus
                }
                closeBox();
              }
              closeBox();
              //----- close vertical effect box

              //----- open a box for the oscilloscope
              openVerticalBox1("");
              {
                openHorizontalBox("");
                {
                  openFrameBox("");
                  closeBox();
                  openFrameBox("");
                  closeBox();
                  openFrameBox("");
                  closeBox();
                  openVerticalBox1("");
                  {
                    openHorizontalBox("");
                    {
                      //----- the oscilloscope
                      addLiveWaveDisplay(" ", &engine->viv , &engine->vivi);
                    }
                    closeBox();
                    openHorizontalBox("");
                    {
                      openVerticalBox("");
                      {
                        openVerticalBox1("");
                        closeBox();
                        openVerticalBox1("");
                        closeBox();
                        addregler("fuzz",&engine->fthreshold, 1.f, 0.f, 1.f, 0.01f);
                        addHorizontalSlider("threshold", &engine->ffuse, 0.f, 0.f, 2.f, 1.f);
                      }
                      closeBox();
                      openFrameBox("");
                      closeBox();
                      openFrameBox("");
                      closeBox();
                      openFrameBox("");
                      closeBox();
                      openFrameBox("");
                      closeBox();
                      openFrameBox("");
                      closeBox();
                    }
                    closeBox();
                  }
                  closeBox();
                  //----- fill empty space
                  openFrameBox("");
                  closeBox();
                  openFrameBox("");
                  closeBox();
                  openFrameBox("");
                  closeBox();
                }
                //----- close ocsilloscope box
                closeBox();
                openFrameBox("");
                closeBox();
                openFrameBox("");
                closeBox();
              }
              closeBox();
            }
            closeBox();
          }
          closeBox();
          openFrameBox("");
          closeBox();
          openFrameBox("");
          closeBox();
          openFrameBox("");
          closeBox();
          openFrameBox("");
          closeBox();
          openFrameBox("");
          closeBox();
          openFrameBox("");
          closeBox();
          openFrameBox("");
          closeBox();
        }
        closeBox();
      }
      closeBox();
    }
    closeBox();
    //----- close the vertical box for effects and oscilloscope

    //----- open the 3. box on botton of the main widget
    openEventBox(" FEEDBACK ");
    {
      openHorizontalBox("");
      {
        openVerticalBox("");
        {
          //----- the midi widget
          openVerticalMidiBox("");
          {
            openHorizontalBox("midi_out");
            {
              //----- create the midi settings dialog
              openDialogBox("midi out", &engine->fdialogbox6);
              {
                openTabBox("");
                {
                  openVerticalBox("channel1");
                  {
                    openEventBox(" ");
                    {
                      openHorizontalBox("");
                      {
                        addregler("velocity", &engine->fslider26, 64.f, 0.f, 127.f, 1.f);
                        openVerticalBox("");
                        {
                          addregler("volume", &engine->fslider46, 64.f, 0.f, 127.f, 1.f);
                          addCheckButton("autogain", &engine->fautogain);
                        }
                        closeBox();
                        openVerticalBox("");
                        {
                          addNumEntry("channel 1", &engine->fslider30, 0.f, 0.f, 16.f, 1.f);
                          addNumEntry("program", &engine->fslider31, 0.f, 0.f, 248.f, 1.f);
                        }
                        closeBox();
                        addregler("oktave", &engine->fslider29, 0.f, -2.f, 2.f, 1.f);
                        addregler("sensity", &engine->fslider27, 20.f, 1.f, 500.f, 1.f);
                      }
                      closeBox();
                    }
                    closeBox();
                    openHorizontalBox("");
                    {
                      openHorizontalBox(" ");
                      closeBox();
                      openHorizontalBox(" ");
                      {
                        addPToggleButton("auto pitch", &engine->fpitch);
                      }
                      closeBox();
                    }
                    closeBox();
                  }
                  closeBox();
                  openVerticalBox("channel2");
                  {
                    openEventBox(" ");
                    {
                      openHorizontalBox("");
                      {
                        addregler("velocity", &engine->fslider32, 64.f, 0.f, 127.f, 1.f);
                        openVerticalBox("");
                        {
                          addregler("volume", &engine->fslider47, 64.f, 0.f, 127.f, 1.f);
                          addCheckButton("autogain", &engine->fautogain1);
                        }
                        closeBox();
                        openVerticalBox("");
                        {
                          addNumEntry("channel 2", &engine->fslider35, 0.f, 0.f, 16.f, 1.f);
                          addNumEntry("program", &engine->fslider36, 0.f, 0.f, 248.f, 1.f);
                        }
                        closeBox();
                        addregler("oktave", &engine->fslider34, 0.f, -2.f, 2.f, 1.f);
                        addregler("sensity", &engine->fslider33, 20.f, 1.f, 500.f, 1.f);
                      }
                      closeBox();
                    }
                    closeBox();
                    openHorizontalBox("");
                    {
                      addtoggle("", &engine->fcheckbox10);
                      openHorizontalBox(" ");
                      {
                        addPToggleButton("auto pitch", &engine->fpitch1);
                      }
                      closeBox();
                    }
                    closeBox();
                  }
                  closeBox();
                  openVerticalBox("channel3");
                  {
                    openEventBox(" ");
                    openHorizontalBox("");
                    {
                      addregler("velocity", &engine->fslider40, 64.f, 0.f, 127.f, 1.f);
                      openVerticalBox("");
                      {
                        addregler("volume", &engine->fslider48, 64.f, 0.f, 127.f, 1.f);
                        addCheckButton("autogain", &engine->fautogain2);
                      }
                      closeBox();
                      openVerticalBox("");
                      {
                        addNumEntry("channel 3", &engine->fslider44, 0.f, 0.f, 16.f, 1.f);
                        addNumEntry("program", &engine->fslider43, 0.f, 0.f, 248.f, 1.f);
                      }
                      closeBox();
                      addregler("oktave", &engine->fslider42, 0.f, -2.f, 2.f, 1.f);
                      addregler("sensity", &engine->fslider41, 20.f, 1.f, 500.f, 1.f);
                    }
                    closeBox();
                  }
                  closeBox();
                  openHorizontalBox("");
                  {
                    addtoggle("", &engine->fcheckbox11);
                    openHorizontalBox(" ");
                    {
                      addPToggleButton("auto pitch", &engine->fpitch2);
                    }
                    closeBox();
                  }
                  closeBox();
                }
                closeBox();
                openVerticalBox("beat_detector");
                {
                  openEventBox(" ");
                  {
                    openHorizontalBox("");
                    {
                      addregler("stepper", &engine->fslider39, 1.f, 1.f, 32.f, 1.f);
                      addregler("note_off", &engine->fslider37, 2.f, 1.f, 127.f, 1.f);
                      addregler("atack_gain", &engine->fslider45, 5.f, 1.f, 127.f, 1.f);
                      addregler("beat_gain", &engine->fslider38, 1.f, 0.0f, 127.f, 1.f);
                    }
                    closeBox();
                  }
                  closeBox();
                  addStatusDisplay("", &engine->midistat);
                  openVerticalBox("Midi gain");
                  {
                    addHorizontalWheel("midi gain", &engine->midi_gain, 0.f, -20.f, 60.f, 1.f);
                  }
                  closeBox();
                }
                closeBox();
              }
              closeBox();
            }
            closeBox();
          }
          closeBox();
        }
        closeBox();
      }
      closeBox();
      //----- add the controlers for feedback feedforward to the bottob box
      addslider(" feedback", &engine->fslider0, 0.000000f, -1.000000f, 1.000000f, 1.000000e-02f);
      addslider(" feedforward", &engine->fslider23, 0.000000f, -1.000000f, 1.000000f, 1.000000e-02f);
      //----- the toggle button to start/stop jack_capture
      openFrameBox("");
      {
        addToggleButton("record", 0);
      }
      closeBox();
      //----- end jack_capture
    }
    closeBox();
    //----- close botton box
  }
  closeBox();
  //----- close main box
  // add a log message box: out of box stack, no need to closeBox
  openTextLoggingBox("Logging Window");
  closeBox();
}

