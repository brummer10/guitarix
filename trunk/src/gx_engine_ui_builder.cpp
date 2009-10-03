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
 *    This is the Guitarix Engine GUI builder
 *    This file is included in gx_engine.cpp which has been split for
 *    readability.
 *
 * --------------------------------------------------------------------------
 */


void GxEngine::buildUserInterface(gx_ui::GxUI* interface)
{
  //----- the main box, all visible widgets are a child of this box
  interface->openVerticalBox("");

  //----- add the menubar on top
  {
    interface->addMenu();

    //----- this is a dummy widget, only for save settings for the latency warning dialog
    interface->openWarningBox("WARNING", &fwarn);
    interface->setSkinBox("SKIN", &fskin);
    interface->closeBox();

    //----- the upper box,
    interface->openVerticalBox("");
    {
      interface->openEventBox(" ");
      interface->openPaintBox2("");
            {
      interface->openHorizontalBox("");
      {
        //----- the tuner widget
        interface->openFrameBox("");
        {
          interface->addNumDisplay("", &fConsta1);
        }
        interface->closeBox();

        //----- the balance widget
        interface->openVerticalBox("");
        {
          interface->addslider("balance", &fslider25, 0.f, -1.f, 1.f, 1.e-01f);
        }
        interface->closeBox();

        //----- the jconv widget on the main window
        interface->openFrameBox("");
        {
          interface->openExpanderBox(" jconv ", &fexpand2);
          {
            interface->openHandleBox("  ");
            {
              interface->openVerticalBox("");
              {
                interface->addslider("wet/dry", &fslider24,  0.f, -1.f, 1.f, 1.e-01f);
                interface->addJConvButton("jconv settings", &filebutton);
                interface->addJToggleButton("run jconv", &gx_jconv::GxJConvSettings::checkbutton7);
              }
              interface->closeBox();

            }
            interface->closeBox();

          }
          interface->closeBox();

        }
        interface->closeBox();

      }
      interface->closeBox();
     }
    interface->closeBox();
    }
    interface->closeBox();
    //----- end of the upper box

    //----- the middle box,
    interface->openExpanderBox(" CONTROLS ", &fexpand);
    {
      //----- a handle box is a vertical box
      interface->openHandleBox("  ");
      {
        //----- arange all widgets in a horizontal scale
        interface->openHorizontalBox("");
        {
          //----- arange all widgets in a vertical scale
          interface->openVerticalBox("");
          {
           // interface->openPaintBox("");
           // {
              //----- the left widget side, volume, tone, fuzz
              interface->openHorizontalBox("");
              {

                //----- open a box for the volume controllers
                {
                  interface->openVerticalBox("volume");
                  {

                    interface->openVerticalBox("");
                    {
                      interface->addbigregler(" in / level ", &fslider3, 0.f, -40.f, 40.f, 0.1f);
                      interface->addbigregler("out / master", &fslider17, 0.f, -40.f, 40.f, 0.1f);
                    }
                    interface->closeBox();

                  }
                  interface->closeBox();
                  //----- volume controll ready


                  //----- open a box for the tone and the fuzz controllers
                  interface->openVerticalBox("tone");
                  {
                    interface->addregler("bass", &fslider_tone2, 0.f, -20.f, 20.f, 0.1f);
                    interface->addregler("middle", &fslider_tone1, 0.f, -20.f, 20.f, 0.1f);
                    interface->addregler("treble", &fslider_tone0, 0.f, -20.f, 20.f, 0.1f);

                    //----- I have set a framebox to fill space beetween the widgets
                    interface->openFrameBox("");
                    interface->closeBox();
                  }
                  interface->closeBox();

                }
                interface->closeBox();
                //----- end tone and fuzz controll

                //----- the next part in the vertical box,
                interface->openVerticalBox("");
                {
                  interface->openHorizontalBox("");
                  {

                    interface->openVerticalBox("shaper ");
                    {
                      interface->addswitch("", &fng);
                      interface->openFrameBox("");
                      {
                        interface->addHorizontalWheel("sharper",&fsharp0, 1.f, 1.f, 10.f, 1.0f);
                      }
                      interface->closeBox();
                      interface->openFrameBox("");
                      {
                      }
                      interface->closeBox();
                    }
                    interface->closeBox();
                    interface->openVerticalBox("noise gate ");
                    {
                      interface->addswitch("", &fnoise_g);
                      interface->addHorizontalWheel(" threshold ", &fnglevel, 0.017f, 0.01f, 0.21f, 0.001f);
                      interface->openFrameBox("");
                      {
                      }
                      interface->closeBox();
                    }
                    interface->closeBox();

                    interface->openVerticalBox("anti aliase");
                    {
                      interface->addswitch("", &antialis0);
                      interface->addHorizontalWheel(" feedback ", &faas1, 0.3f, 0.3f, 0.9f, 0.01f);
                      interface->openFrameBox("");
                      {
                      }
                      interface->closeBox();
                    }
                    interface->closeBox();
                  }
                  interface->closeBox();

                 // interface->openPaintBox("");
                 // {
                    interface->openVerticalBox("amp  ");
                    {
                      interface->openHorizontalBox("");
                      {
                        interface->openFrameBox("");
                        {
                        }

                        interface->closeBox();
                        interface->addminiswitch(" oversample  ", &fupsample);
                        interface->openFrameBox("");
                        {
                        }

                        interface->closeBox();
                        interface->addminiswitch(" bass booster", &fboost);
                        interface->openFrameBox("");
                        {
                        }
                        interface->closeBox();
                      }
                      interface->closeBox();
                    }
                    interface->closeBox();

                    //-----

                    //----- the second part in the vertical box
                    interface->openHorizontalBox("");
                    {
                      interface->openVerticalBox("");
                      {
                        interface->openVerticalBox("");
                        {
                          interface->addswitch("preamp", &fcheckbox1);
                          interface->addHorizontalWheel("atan",&fatan, 1.f, 1.f, 10.f, 1.0f);
                        }
                        interface->closeBox();
                        interface->openFrameBox("");
                        {
                        }
                        interface->closeBox();
                        interface->openVerticalBox("");
                        {
                          interface->addswitch("drive", &fprdr);
                          interface->addHorizontalWheel("drive", &fpredrive, 1.f, 1.f, 10.f, 1.0f);
                        }
                        interface->closeBox();

                      }
                      interface->closeBox();
                      interface->openFrameBox("");
                      interface->closeBox();

                      interface->openVerticalBox("");
                      {
                        interface->openVerticalBox("");
                        {
                          interface->addswitch("tube", &ftube);
                          interface->addHorizontalWheel("tube",&ffuzzytube, 1.f, -3.f, 10.f, 1.0f);
                        }
                        interface->closeBox();
                        interface->openFrameBox("");
                        {
                        }
                        interface->closeBox();
                        interface->openVerticalBox("");
                        {
                          interface->addswitch("vibrato", &fresoon);
                          interface->addHorizontalWheel("vibrato", &fvibrato, 0.f, 0.f, 2.f, 0.02f);
                        }
                        interface->closeBox();

                      }
                      interface->closeBox();
                      interface->openFrameBox("");
                      interface->closeBox();

                      interface->openVerticalBox("");
                      {
                        interface->openVerticalBox("");
                        {
                          interface->addswitch("tube2", &ftube3);
                          interface->openFrameBox("");
                          {
                            interface->addHorizontalWheel("tube",&fresotube3, 1.f, -3.f, 10.f, 1.0f);
                          }
                          interface->closeBox();

                        }
                        interface->closeBox();

                        interface->openVerticalBox("");
                        {
                          interface->openVerticalBox1("resonanz");
                          {
                            interface->addHorizontalWheel("reso",&fresotube1, 0.5f, 0.f, 0.9f, 0.01f);
                          }
                          interface->closeBox();

                          interface->openVerticalBox1("vibrato");
                          {
                            interface->addHorizontalWheel("vibrato",&fresotube2, 1.f, 0.f, 1.f, 0.01f);
                          }
                          interface->closeBox();

                        }
                        interface->closeBox();

                      }
                      interface->closeBox();

                    }
                    interface->closeBox();
                    interface->openFrameBox("");
                    interface->closeBox();
                    interface->openFrameBox("");
                    interface->closeBox();
                 // }
                 // interface->closeBox();
                }
                interface->closeBox();
              }
              interface->closeBox();

          //  }
          //  interface->closeBox();
            //----- end
            interface->openFrameBox("");
            interface->closeBox();

            //----- this box include all effects and the osccilloscope


            interface->openVerticalBox("");
            {
            //  interface->openScrollBox("  ");
            //  {

                //----- fill empty space
               // interface->openPaintBox("");
               // {
                  interface->openHorizontalBox("");
                  {
                  }
                  interface->closeBox();

                  //----- this box include only the effects

                  interface->openHorizontalBox("");
                  {
                  //  interface->openFrameBox("");
                  //  interface->closeBox();
                    //----- the compressor
                    interface->openVerticalBox("compressor");
                    {
                      interface->addregler("ratio", &fentrycom2, 2.000000f, 1.000000f, 20.000000f, 0.100000f);
                      interface->openHorizontalBox("");
                      {
                        interface->addtoggle("", &fcheckboxcom1);

                        //----- open a dialogbox(toplevel widget) and put the advanced controlls in it
                        interface->openDialogBox("compressor", &fdialogbox8);
                        {
                          interface->openHandleBox("  ");
                          {
                            interface->openVerticalBox("compressor");
                            {
                              interface->openHorizontalBox("");
                              {
                                interface->addregler("knee", &fentrycom1, 3.000000f, 0.000000f, 20.000000f, 0.100000f);
                                interface->addregler("ratio", &fentrycom2, 2.000000f, 1.000000f, 20.000000f, 0.100000f);
                                interface->addregler("threshold", &fentrycom0, -20.000000f, -96.000000f, 10.000000f, 0.100000f);
                              }
                              interface->closeBox();

                              interface->openVerticalBox("envelop");
                              {
                                interface->addslider("attack", &fslidercom0, 2.000000e-03f, 0.000000f, 1.000000f, 1.000000e-03f);
                                interface->addslider("release", &fslidercom1, 0.500000f, 0.000000f, 10.000000f, 1.000000e-02f);
                              }
                              interface->closeBox();

                            }
                            interface->closeBox();

                          }
                          interface->closeBox();

                        }
                        interface->closeBox();

                      }
                      //----- end advanced settings widget
                      interface->closeBox();

                    }
                    interface->closeBox();
                    //----- end compressor


                    //----- overdrive
                    interface->openVerticalBox("overdrive");
                    {
                      interface->addregler("  drive ", &drive, 1.f, 1.f, 20.f, 0.1f);
                      interface->addtoggle("", &foverdrive4);
                    }
                    interface->closeBox();
                    //-----end overdrive


                    //----- distortion
                    interface->openVerticalBox(" distortion");
                    {
                      interface->addregler("  drive ", &fslider9, 0.64f, 0.f, 1.f, 1.e-02f);
                      interface->openHorizontalBox("");
                      {
                        interface->addtoggle("", &fcheckbox4);

                        //----- open a dialogbox(toplevel widget) and put the advanced controlls in it
                        {
                          interface->openDialogBox("distortion", &fdialogbox1);
                          {
                            interface->openHandleBox("  ");
                            {
                              interface->addbigregler("  drive ", &fslider9, 0.64f, 0.f, 1.f, 1.e-02f);
                              interface->addregler("level", &fslider8, 1.000000e-02f, 0.0f, 0.50f, 1.000000e-02f);
                              interface->addregler("gain", &fslider10, 2.0f, -10.0f, 10.0f, 0.1f);

                              interface->openVerticalBox("low/highpass");
                              {
                                interface->openHorizontalBox("");
                                {
                                  interface->addregler("high-freq ", &fentry1, 130.0f, 20.0f, 7040.0f, 10.0f);
                                  interface->addregler(" low-freq ", &fentry0, 5000.0f, 20.0f, 12000.0f, 10.0f);
                                }
                                interface->closeBox();

                                interface->addtoggle("", &fcheckbox2);
                              }
                              interface->closeBox();

                              interface->openVerticalBox("low/highcutoff");
                              {
                                interface->openHorizontalBox("");
                                {
                                  interface->addregler("high-freq ", &fslider6, 5000.0f, 1000.0f, 12000.0f, 10.0f);
                                  interface->addregler(" low-freq ", &fslider7, 130.0f, 20.0f, 1000.0f, 10.0f);
                                }
                                interface->closeBox();

                                interface->addtoggle("", &fcheckbox3);
                              }
                              interface->closeBox();

                              interface->openHorizontalBox("resonanz");
                              {
                                interface->addregler("trigger ", &fslider4, 0.12f, 0.0f, 1.0f, 1.000000e-02f);
                                interface->addregler(" vibrato ", &fslider5, 1.0f, 0.0f, 1.0f, 1.000000e-02f);
                              }
                              interface->closeBox();

                            }
                            interface->closeBox();

                          }
                          interface->closeBox();

                        }
                        //----- end advanced settings widget
                        interface->closeBox();

                      }
                      interface->closeBox();
                      //----- end distortion

                      //----- freeverb
                      interface->openVerticalBox(" freeverb");
                      {
                        interface->addregler("RoomSize", &fslider16, 0.500000f, 0.000000f, 1.000000f, 2.500000e-02f);

                        interface->openHorizontalBox("");
                        {
                          interface->addtoggle("", &fcheckbox6);

                          //----- open a dialogbox(toplevel widget) and put the advanced controlls in it
                          interface->openDialogBox("freeverb", &fdialogbox2);
                          {
                            interface->openHandleBox("  ");
                            {
                              interface->addregler("RoomSize", &fslider16, 0.500000f, 0.000000f, 1.000000f, 2.500000e-02f);
                              interface->addregler("damp", &fslider15, 0.5f, 0.0f, 1.0f, 2.500000e-02f);
                              interface->addregler("wet/dry", &fslider14, 0.0f, -0.5f, 0.5f, 1.e-01f);
                            }
                            interface->closeBox();
                          }
                          interface->closeBox();

                        }
                        //----- end advanced settings widget
                        interface->closeBox();

                      }
                      interface->closeBox();
                      //----- end freeverb

                      //----- IR
                      interface->openVerticalBox("IR");
                      {
                        interface->openHorizontalBox("");
                        {
                          interface->addregler("   freq   ", &fslider21, 440.000000f, 20.000000f, 12000.000000f, 10.000000f);
                          //interface->addregler(" peak ", &fslider22, 1.000000f, 0.000000f, 10.000000f, 0.200000f);
                        }
                        interface->closeBox();

                        interface->openHorizontalBox("");
                        {
                          interface->addtoggle("", &fcheckbox8);

                          //----- open a dialogbox(toplevel widget) and put the advanced controlls in it
                          interface->openDialogBox("ImpulseResponse", &fdialogbox3);
                          {
                            interface->openHandleBox("  ");
                            {
                              interface->addregler("    freq     ", &fslider21, 440.000000f, 20.000000f, 12000.000000f, 10.000000f);
                              interface->addregler("     peak    ", &fslider22, 1.000000f, 0.000000f, 10.000000f, 0.200000f);
                              interface->addregler("    bandwidth    ", &fslider20, 100.0f, 20.0f, 20000.0f, 10.0f);
                            }
                            interface->closeBox();

                          }
                          interface->closeBox();

                        }
                        //----- end advanced settings widget
                        interface->closeBox();

                      }
                      interface->closeBox();
                      //----- end IR

                      interface->openVerticalBox("chorus");
                      {

                        interface->addregler("level", &fslider_CH3, 0.5f, 0.0f, 1.0f, 1.000000e-02f);
                        interface->openHorizontalBox("");
                        {
                          interface->addtoggle("", &fchorus);
                          interface->openDialogBox("chorus", &fchorusbox);
                          {
                            interface->openHandleBox("  ");
                            {
                              interface->openVerticalBox("");
                              {
                                interface->openHorizontalBox("");
                                {
                                  interface->addregler("  delay  ", &fslider_CH2, 2.500000e-02f, 0.0f, 0.2f, 1.000000e-03f);
                                  interface->addregler("  depth  ", &fslider_CH1, 2.000000e-02f, 0.0f, 1.0f, 1.000000e-03f);
                                  interface->addregler("  freq  ", &fslider_CH0, 3.0f, 0.0f, 10.0f, 1.000000e-02f);
                                  interface->addregler("  level  ", &fslider_CH3, 0.5f, 0.0f, 1.0f, 1.000000e-02f);

                                }
                                interface->closeBox();
                              }
                              interface->closeBox();
                            }
                            interface->closeBox();
                          }
                          interface->closeBox();
                        }
                        interface->closeBox();
                      }
                      interface->closeBox();

                      //----- crybaby
                      interface->openVerticalBox("crybaby");
                      {
                        interface->addregler(" wah ", &fslider11, 0.000000f, 0.000000f, 1.000000f, 1.000000e-02f);

                        interface->openHorizontalBox("");
                        {
                          interface->addtoggle("", &fcheckbox5);

                          //----- open a dialogbox(toplevel widget) and put the advanced controlls in it
                          interface->openDialogBox("crybaby", &fdialogbox4);
                          {
                            interface->openHandleBox("  ");
                            {
                              interface->openVerticalBox("");
                              {
                                interface->openHorizontalBox("");
                                {
                                  interface->addregler("  wah   ", &fslider11, 0.0f, 0.0f, 1.0f, 1.000000e-02f);
                                  interface->addregler("  level  ", &fslider12, 0.1f, 0.0f, 1.0f, 1.000000e-02f);
                                  interface->addregler("wet/dry", &fslider13, 0.f, -1.f, 1.f, 1.e-01f);
                                }
                                interface->closeBox();

                                interface->addminiswitch(" autowah", &fautowah);
                              }
                              interface->closeBox();
                            }
                            interface->closeBox();

                          }
                          interface->closeBox();

                        }
                        //----- end advanced settings widget
                        interface->closeBox();

                      }
                      interface->closeBox();
                      //----- end crybaby

                      //----- echo
                      interface->openVerticalBox("echo");
                      {
                        interface->openHorizontalBox("");
                        {
                          interface->addregler("    %    ", &fslider19, 0.000000f, 0.000000f, 100.000000f, 0.100000f);
                          interface->addregler("  time  ", &fslider18, 1.000000f, 1.000000f, 2000.000000f, 1.000000f);
                        }
                        interface->closeBox();

                        interface->addtoggle("", &fcheckbox7);

                      }
                      interface->closeBox();

                    }
                    //----- end echo

                  }
                  interface->closeBox();
               // }
               // interface->closeBox();
                //----- close vertical effect box


                //----- open a box for the oscilloscope
                interface->openVerticalBox("");
                {


                  interface->openHorizontalBox("");
                  {


                    //----- the oscilloscope
                    interface->addLiveWaveDisplay(" ", &viv , &vivi);

                  }
                  interface->closeBox();
                 // interface->openPaintBox("");
                 // {

                    interface->openHorizontalBox("");
                    {

                      interface->openVerticalBox("");
                      {
                        interface->openFrameBox("");
                        interface->closeBox();
                        interface->openFrameBox("");
                        interface->closeBox();
                        interface->addregler("fuzz",&fthreshold, 1.f, 0.f, 1.f, 0.01f);
                        interface->addHorizontalSlider("threshold", &ffuse, 0.f, 0.f, 2.f, 1.f);
                      }
                      interface->closeBox();

                      interface->openFrameBox("");
                      interface->closeBox();

                      interface->openFrameBox("");
                      interface->closeBox();

                      interface->openFrameBox("");
                      interface->closeBox();

                      interface->openFrameBox("");
                      interface->closeBox();

                      interface->openFrameBox("");
                      interface->closeBox();

                      interface->openFrameBox("");
                      interface->closeBox();

                      interface->openFrameBox("");
                      interface->closeBox();

                      interface->openFrameBox("");
                      interface->closeBox();

                      interface->openFrameBox("");
                      interface->closeBox();

                      interface->openFrameBox("");
                      interface->closeBox();

                      interface->openFrameBox("");
                      interface->closeBox();

                      interface->openFrameBox("");
                      interface->closeBox();
                    }
                    interface->closeBox();



                    //----- fill empty space
                    interface->openFrameBox("");
                    interface->closeBox();

                //  }
                //  interface->closeBox();
                //}
                //interface->closeBox();

              }
              //----- close ocsilloscope box
              interface->closeBox();
            }
            interface->closeBox();
          }
          interface->closeBox();

          interface->openFrameBox("");
          interface->closeBox();


        }
        interface->closeBox();


      }
      interface->closeBox();
      //----- close the vertical box for effects and oscilloscope

      //----- open the 3. box on botton of the main widget
      interface->openEventBox(" FEEDBACK ");
      {
        interface->openHorizontalBox("");
        {
          interface->openFrameBox("");
          {
            //----- the midi widget
            interface->openVerticalMidiBox("");
            {
              interface->openHorizontalBox("midi_out");
              {
                //----- create the midi settings dialog
                interface->openDialogBox("midi out", &fdialogbox6);
                {
                  interface->openTabBox("");
                  {
                    interface->openVerticalBox("channel1");
                    {
                      interface->openEventBox(" ");
                      {
                        interface->openHorizontalBox("");
                        {
                          interface->addregler("velocity", &fslider26, 64.f, 0.f, 127.f, 1.f);

                          interface->openVerticalBox("");
                          {
                            interface->addregler("volume", &fslider46, 64.f, 0.f, 127.f, 1.f);
                            interface->addCheckButton("autogain", &fautogain);
                          }
                          interface->closeBox();

                          interface->openVerticalBox("");
                          {
                            interface->addNumEntry("channel 1", &fslider30, 0.f, 0.f, 16.f, 1.f);
                            interface->addNumEntry("program", &fslider31, 0.f, 0.f, 248.f, 1.f);
                          }
                          interface->closeBox();

                          interface->addregler("oktave", &fslider29, 0.f, -2.f, 2.f, 1.f);
                          interface->addregler("sensity", &fslider27, 20.f, 1.f, 500.f, 1.f);
                        }
                        interface->closeBox();

                      }
                      interface->closeBox();

                      interface->openHorizontalBox("");
                      {
                        interface->openHorizontalBox(" ");
                        interface->closeBox();


                        interface->openHorizontalBox(" ");
                        {
                          interface->addPToggleButton("auto pitch", &fpitch);
                        }
                        interface->closeBox();

                      }
                      interface->closeBox();

                    }
                    interface->closeBox();


                    interface->openVerticalBox("channel2");
                    {

                      interface->openEventBox(" ");
                      {

                        interface->openHorizontalBox("");
                        {
                          interface->addregler("velocity", &fslider32, 64.f, 0.f, 127.f, 1.f);

                          interface->openVerticalBox("");
                          {
                            interface->addregler("volume", &fslider47, 64.f, 0.f, 127.f, 1.f);
                            interface->addCheckButton("autogain", &fautogain1);
                          }
                          interface->closeBox();

                          interface->openVerticalBox("");
                          {
                            interface->addNumEntry("channel 2", &fslider35, 0.f, 0.f, 16.f, 1.f);
                            interface->addNumEntry("program", &fslider36, 0.f, 0.f, 248.f, 1.f);
                          }
                          interface->closeBox();

                          interface->addregler("oktave", &fslider34, 0.f, -2.f, 2.f, 1.f);
                          interface->addregler("sensity", &fslider33, 20.f, 1.f, 500.f, 1.f);

                        }
                        interface->closeBox();

                      }
                      interface->closeBox();

                      interface->openHorizontalBox("");
                      {
                        interface->addtoggle("", &fcheckbox10);

                        interface->openHorizontalBox(" ");
                        {
                          interface->addPToggleButton("auto pitch", &fpitch1);
                        }
                        interface->closeBox();

                      }
                      interface->closeBox();

                    }
                    interface->closeBox();

                    interface->openVerticalBox("channel3");
                    {
                      interface->openEventBox(" ");

                      interface->openHorizontalBox("");
                      {
                        interface->addregler("velocity", &fslider40, 64.f, 0.f, 127.f, 1.f);

                        interface->openVerticalBox("");
                        {
                          interface->addregler("volume", &fslider48, 64.f, 0.f, 127.f, 1.f);
                          interface->addCheckButton("autogain", &fautogain2);
                        }
                        interface->closeBox();

                        interface->openVerticalBox("");
                        {
                          interface->addNumEntry("channel 3", &fslider44, 0.f, 0.f, 16.f, 1.f);
                          interface->addNumEntry("program", &fslider43, 0.f, 0.f, 248.f, 1.f);
                        }
                        interface->closeBox();

                        interface->addregler("oktave", &fslider42, 0.f, -2.f, 2.f, 1.f);
                        interface->addregler("sensity", &fslider41, 20.f, 1.f, 500.f, 1.f);

                      }
                      interface->closeBox();

                    }
                    interface->closeBox();

                    interface->openHorizontalBox("");
                    {
                      interface->addtoggle("", &fcheckbox11);

                      interface->openHorizontalBox(" ");
                      {
                        interface->addPToggleButton("auto pitch", &fpitch2);
                      }
                      interface->closeBox();

                    }
                    interface->closeBox();

                  }
                  interface->closeBox();

                  interface->openVerticalBox("beat_detector");
                  {
                    interface->openEventBox(" ");
                    {
                      interface->openHorizontalBox("");
                      {
                        interface->addregler("stepper", &fslider39, 1.f, 1.f, 32.f, 1.f);
                        interface->addregler("note_off", &fslider37, 2.f, 1.f, 127.f, 1.f);
                        interface->addregler("atack_gain", &fslider45, 5.f, 1.f, 127.f, 1.f);
                        interface->addregler("beat_gain", &fslider38, 1.f, 0.0f, 127.f, 1.f);
                      }
                    }
                    interface->closeBox();

                  }
                  interface->closeBox();

                  interface->addStatusDisplay("", &midistat);

                  interface->openVerticalBox("Midi gain");
                  {
                    interface->addHorizontalWheel("midi gain", &midi_gain, 0.f, -20.f, 60.f, 1.f);
                  }
                  interface->closeBox();

                }
                interface->closeBox();

              }
              interface->closeBox();

            }
            interface->closeBox();

          }
          interface->closeBox();

        }
        interface->closeBox();

      }
      interface->closeBox();


      //----- add the controlers for feedback feedforward to the bottob box
      interface->addslider(" feedback", &fslider0, 0.000000f, -1.000000f, 1.000000f, 1.000000e-02f);
      interface->addslider(" feedforward", &fslider23, 0.000000f, -1.000000f, 1.000000f, 1.000000e-02f);

      //----- the toggle button to start/stop jack_capture
      interface->openFrameBox("");
      {
        interface->addToggleButton("record", 0);
      }
      interface->closeBox();
      //----- end jack_capture

    }
    interface->closeBox();
    //----- close botton box

  }

  interface->closeBox();
  //----- close main box

  // add a log message box: out of box stack, no need to closeBox
  interface->openTextLoggingBox("Logging Window");


  interface->closeBox();
}
