/*
* Copyright (C) 2009, 2010 Hermann Meyer, James Warden, Andreas Degert
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
*    This file is a part ofthe gx_head interface builder
*    and build the mono effect rack,
*    it's a part of the class GxMainInterface
*
* ----------------------------------------------------------------------------
*/

openHorizontalTableBox("");
{
     openPaintBox("");
     {
          openVerticalBox("noise shaper       ");
          {
               openHorizontalBox("");
               {
                    create_switch_no_caption(sw_switchit, "shaper.on_off");
                    openSpaceBox("");
                    closeBox();
                    openSpaceBox("");
                    closeBox();
                    openpaintampBox("");
                    {
                         create_wheel("shaper.sharper");
                    }
                    closeBox();
               }
               closeBox();
          }
          closeBox();
     }
     closeBox();
     //low high pass filter
     openHorizontalOrderBox(" ", &gx_engine::audio.posit14);
     {
          openVerticalBox("l/h/filter");
          {
               openHorizontalBox("");
               {
                    openPaintBox1("");
                    {
                         create_switch_no_caption(sw_switchit, "low_highpass.on_off");
                         create_selector("low_highpass.pp");
                    }
                    closeBox();

                    openDialogBox("low_highpass.dialog", "low_highpass.on_off","RackBox_expose");
                    {
                         openHorizontalBox("");
                         {

                              openHorizontalBox("");
                              {
                                   create_small_rackknob("low_high_pass.lhp.high_freq","high-pass ");
                                   create_small_rackknob("low_high_pass.lhp.low_freq"," low-pass ");
                                   create_switch_no_caption(sw_switchit, "low_high_pass.lhp.on_off");
                              }
                              closeBox();

                              openSpaceBox("");
                              closeBox();

                              openHorizontalBox("");
                              {
                                   create_small_rackknob("low_high_pass.lhc.low_freq"," low-cut ");
                                   create_small_rackknob("low_high_pass.lhc.high_freq","high-cut ");
                                   create_switch_no_caption(sw_switchit, "low_high_pass.lhc.on_off");
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
     // EQ
     openHorizontalOrderBox(" ", &gx_engine::audio.posit10);
     {
          openVerticalBox("EQ");
          {
               openHorizontalBox("");
               {
                    openPaintBox1("");
                    {
                         create_switch_no_caption(sw_switchit, "eqs.on_off");
                         create_selector("eqs.pp");
                    }
                    closeBox();

                    openDialogBox("eqs.dialog", "eqs.on_off","RackBox_expose");
                    {
                         openVerticalBox("");
                         {
                              openHorizontalTableBox("");
                              {
                                   create_simple_spin_value("eqs.freq31_25");
                                   create_simple_spin_value("eqs.freq62_5");
                                   create_simple_spin_value("eqs.freq125");
                                   create_simple_spin_value("eqs.freq250");
                                   create_simple_spin_value("eqs.freq500");
                                   create_simple_spin_value("eqs.freq1k");
                                   create_simple_spin_value("eqs.freq2k");
                                   create_simple_spin_value("eqs.freq4k");
                                   create_simple_spin_value("eqs.freq8k");
                                   create_simple_spin_value("eqs.freq16k");
                              }
                              closeBox();
                              openHorizontalTableBox("");
                              {
                                   create_eq_rackslider_no_caption("eqs.fs31_25");
                                   create_eq_rackslider_no_caption("eqs.fs62_5");
                                   create_eq_rackslider_no_caption("eqs.fs125");
                                   create_eq_rackslider_no_caption("eqs.fs250");
                                   create_eq_rackslider_no_caption("eqs.fs500");
                                   create_eq_rackslider_no_caption("eqs.fs1k");
                                   create_eq_rackslider_no_caption("eqs.fs2k");
                                   create_eq_rackslider_no_caption("eqs.fs4k");
                                   create_eq_rackslider_no_caption("eqs.fs8k");
                                   create_eq_rackslider_no_caption("eqs.fs16k");
                              }
                              closeBox();
                              openHorizontalTableBox("");
                              {
                                   create_small_rackknob("eqs.Qs31_25","Q");
                                   create_small_rackknob("eqs.Qs62_5","Q");
                                   create_small_rackknob("eqs.Qs125","Q");
                                   create_small_rackknob("eqs.Qs250","Q");
                                   create_small_rackknob("eqs.Qs500","Q");
                                   create_small_rackknob("eqs.Qs1k","Q");
                                   create_small_rackknob("eqs.Qs2k","Q");
                                   create_small_rackknob("eqs.Qs4k","Q");
                                   create_small_rackknob("eqs.Qs8k","Q");
                                   create_small_rackknob("eqs.Qs16k","Q");
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
//----- crybaby
     openHorizontalOrderBox("", &gx_engine::audio.posit0);
     {
          openVerticalBox("crybaby");
          {

               openHorizontalBox("");
               {
                    openPaintBox1("");
                    {
                         create_switch_no_caption(sw_switchit, "crybaby.on_off");
                         create_selector("crybaby.pp");
                    }
                    closeBox();

                    openDialogBox("crybaby.dialog", "crybaby.on_off","RackBox_expose");
                    {
                         openHorizontalBox("");
                         {

                              openSpaceBox("");
                              closeBox();
                              create_selector("crybaby.autowah");
                              openSpaceBox("");
                              closeBox();
                              openHorizontalTableBox("");
                              {
                                   create_small_rackknobr("crybaby.wah","  wah   ");
                                   create_small_rackknob("crybaby.level","  level  ");
                                   create_small_rackknob("crybaby.wet_dry","  dry/wet  ");
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
//----- distortion
     openHorizontalOrderBox("", &gx_engine::audio.posit2);
     {
          openVerticalBox("distortion");
          {

               openHorizontalBox("");
               {
                    openPaintBox1("");
                    {
                         create_switch_no_caption(sw_switchit, "gx_distortion.on_off");
                         create_selector("gx_distortion.pp");
                    }
                    closeBox();

                    openDialogBox("gx_distortion.dialog", "gx_distortion.on_off","RackBox_expose");
                    {
                         openHorizontalBox("");
                         {
                              openVerticalBox("");
                              {
                                   openHorizontalBox("");
                                   {
                                        openVerticalBox1("");
                                        {
                                             create_small_rackknobr("gx_distortion.drive","  drive ");
                                             create_small_rackknob("gx_distortion.level","  level  ");
                                             create_small_rackknob("gx_distortion.gain","  gain  ");
                                        }
                                        closeBox();
                                        openVerticalBox1("");
                                        {
                                             openHorizontalBox("");
                                             {
                                                  openVerticalBox1("");
                                                  {
                                                       create_small_rackknobr("gx_distortion.low_drive"," low drive ");
                                                       create_small_rackknob("gx_distortion.low_gain"," low gain ");
                                                  }
                                                  closeBox();
                                                  openVerticalBox1("");
                                                  {
                                                       create_small_rackknobr("gx_distortion.middle_l_drive"," m. l. drive ");
                                                       create_small_rackknob("gx_distortion.middle_l_gain"," m. l. gain ");
                                                  }
                                                  closeBox();
                                                  openVerticalBox1("");
                                                  {
                                                       create_small_rackknobr("gx_distortion.middle_h_drive"," m. h. drive ");
                                                       create_small_rackknob("gx_distortion.middle_h_gain"," m. h. gain ");
                                                  }
                                                  closeBox();
                                                  openVerticalBox1("");
                                                  {
                                                       create_small_rackknobr("gx_distortion.high_drive"," high drive ");
                                                       create_small_rackknob("gx_distortion.high_gain"," high gain ");
                                                  }
                                                  closeBox();
                                             }
                                             closeBox();
                                             openVerticalBox("frequency split Hz");
                                             {
                                                  openHorizontalBox("");
                                                  {
                                                       create_wheel("gx_distortion.split_low_freq", "split low freq");
                                                       create_wheel("gx_distortion.split_middle_freq", "split m. freq");
                                                       create_wheel("gx_distortion.split_high_freq", "split high freq");

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

                              openVerticalBox("resonator");
                              {
                                   create_small_rackknob("gx_distortion.trigger","trigger ");
                                   create_small_rackknob("gx_distortion.vibrato"," vibrato ");
                                   create_switch_no_caption(sw_switchit, "gx_distortion.resonator.on_off");
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
//----- IR
     openHorizontalOrderBox("", &gx_engine::audio.posit4);
     {
          openVerticalBox("IR");
          {
               openHorizontalBox("");
               {
                    openPaintBox1("");
                    {
                         create_switch_no_caption(sw_switchit, "IR.on_off");
                         create_selector("IR.pp");
                    }
                    closeBox();

                    openDialogBox("IR.dialog", "IR.on_off","RackBox_expose");
                    {
                         openVerticalBox1("");
                         {
                              openHorizontalBox("");
                              {
                                   openSpaceBox("");
                                   closeBox();
                                   create_selector("IR.auto_freq");
                                   openSpaceBox("");
                                   closeBox();

                                   openHorizontalTableBox("");
                                   {
                                        create_small_rackknob("IR.freq"," freq ");
                                        create_small_rackknob("IR.peak"," peak ");
                                        create_small_rackknob("IR.bandwidth"," bandwidth ");
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
//----- the compressor
     openHorizontalOrderBox("", &gx_engine::audio.posit5);
     {
          openVerticalBox("Compr.");
          {
               openHorizontalBox("");
               {
                    openPaintBox1("");
                    {
                         create_switch_no_caption(sw_switchit, "compressor.on_off");
                         create_selector("compressor.pp");
                    }
                    closeBox();
                    openDialogBox("compressor.dialog", "compressor.on_off","RackBox_expose");
                    {

                         openHorizontalTableBox("");
                         {
                              create_small_rackknob("compressor.knee");
                              create_small_rackknobr("compressor.ratio");
                              create_small_rackknob("compressor.threshold");


                              create_small_rackknob("compressor.attack");
                              create_small_rackknob("compressor.release");
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
//-----overdrive
     openHorizontalOrderBox("", &gx_engine::audio.posit1);
     {
          openVerticalBox("overdrive");
          {
               openHorizontalBox("");
               {
                    openPaintBox1("");
                    {
                         create_switch_no_caption(sw_switchit, "overdrive.on_off");
                         create_selector("overdrive.pp");
                    }
                    closeBox();
                    openDialogBox("overdrive.dialog", "overdrive.on_off","RackBox_expose");
                    {
                         openHorizontalTableBox("");
                         {

                              openSpaceBox("");
                              closeBox();
                              create_small_rackknobr("overdrive.drive","  drive ");
                              openSpaceBox("");
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
//----- echo
     openHorizontalOrderBox("", &gx_engine::audio.posit6);
     {
          openVerticalBox("echo");
          {
               openHorizontalBox("");
               {
                    openPaintBox1("");
                    {
                         create_switch_no_caption(sw_switchit, "echo.on_off");
                         create_selector("echo.pp");
                    }
                    closeBox();

                    openDialogBox("echo.dialog", "echo.on_off","RackBox_expose");
                    {
                         openVerticalBox("");
                         {
                              openHorizontalTableBox("");
                              {

                                   create_small_rackknobr("echo.time","  time  ");

                                   create_small_rackknob("echo.percent","    %    ");
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
//-----delay
     openHorizontalOrderBox("", &gx_engine::audio.posit7);
     {
          openVerticalBox("delay");
          {
               openHorizontalBox("");
               {
                    openPaintBox1("");
                    {
                         create_switch_no_caption(sw_switchit, "delay.on_off");
                         create_selector("delay.pp");
                    }
                    closeBox();

                    openDialogBox("delay.dialog", "delay.on_off","RackBox_expose");
                    {
                         openVerticalBox("");
                         {
                              openHorizontalTableBox("");
                              {

                                   create_small_rackknobr("delay.delay"," delay ");

                                   create_small_rackknob("delay.gain","  gain ");
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
//----- freeverb
     openHorizontalOrderBox("", &gx_engine::audio.posit3);
     {
          openVerticalBox("freeverb");
          {
               openHorizontalBox("");
               {
                    openPaintBox1("");
                    {
                         create_switch_no_caption(sw_switchit, "freeverb.on_off");
                         create_selector("freeverb.pp");
                    }
                    closeBox();
                    openDialogBox("freeverb.dialog", "freeverb.on_off","RackBox_expose");
                    {

                         openFrameBox("");
                         closeBox();
                         openFrameBox("");
                         closeBox();
                         openHorizontalTableBox("");
                         {
                              create_small_rackknobr("freeverb.RoomSize");
                              create_small_rackknob("freeverb.damp");
                              create_small_rackknob("freeverb.wet_dry", "dry/wet");
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
          closeBox();
     }
     closeBox();

     openVerticalMidiBox("  MIDI out  ");
     {
          openHorizontalBox("");
          {
               openVerticalBox("  MIDI out  ");
               {
                    create_switch_no_caption(sw_switchit, "midi_out.on_off");
                    openFrameBox("");
                    closeBox();
                    openHorizontalBox("");
                    {
                         openFrameBox("");
                         closeBox();
                         openPaintBox2("");
                         {
                              create_switch_no_caption(sw_led,"system.midistat");
                         }
                         closeBox();
                         openFrameBox("");
                         closeBox();
                    }
                    closeBox();
                    openFrameBox("");
                    closeBox();

               }
               closeBox();
//----- create the midi settings dialog
               openVerticalBox("");
               {
                    openTabBox("");
                    {

                         openVerticalBox("channel1");
                         {
                              openpaintampBox(" ");
                              {
                                   openVerticalBox("");
                                   {
                                        openHorizontalBox("");
                                        {
                                             create_small_rackknob("midi_out.channel_1.velocity");
                                             openVerticalBox("");
                                             {
                                                  create_small_rackknob("midi_out.channel_1.volume");
                                                  addCheckButton("midi_out.channel_1.autogain");
                                             }
                                             closeBox();
                                             openVerticalBox("");
                                             {
                                                  addNumEntry("midi_out.channel_1.channel");
                                                  addNumEntry("midi_out.channel_1.program");
                                             }
                                             closeBox();
                                             create_small_rackknob("midi_out.channel_1.oktave");
                                             create_small_rackknob("midi_out.channel_1.sensity");
                                        }
                                        closeBox();
                                        openHorizontalBox("");
                                        {
                                             openHorizontalBox(" ");
                                             closeBox();
                                             openFrameBox("");
                                             closeBox();
                                             openVerticalBox("");
                                             {
                                                  openFrameBox("");
                                                  closeBox();
                                                  openPaintBox2("");
                                                  {
                                                       create_switch_no_caption(sw_led,"system.midistat1");
                                                  }
                                                  closeBox();
                                                  openFrameBox("");
                                                  closeBox();
                                             }
                                             closeBox();
                                             openFrameBox("");
                                             closeBox();
                                             openHorizontalBox(" ");
                                             {
                                                  addPToggleButton("midi_out.channel_1.auto_pitch");
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

                         openVerticalBox("channel2");
                         {
                              openpaintampBox(" ");
                              {
                                   openVerticalBox("");
                                   {
                                        openHorizontalBox("");
                                        {
                                             create_small_rackknob("midi_out.channel_2.velocity");
                                             openVerticalBox("");
                                             {
                                                  create_small_rackknob("midi_out.channel_2.volume");
                                                  addCheckButton("midi_out.channel_2.autogain");
                                             }
                                             closeBox();
                                             openVerticalBox("");
                                             {
                                                  addNumEntry("midi_out.channel_2.channel");
                                                  addNumEntry("midi_out.channel_2.program");
                                             }
                                             closeBox();
                                             create_small_rackknob("midi_out.channel_2.oktave");
                                             create_small_rackknob("midi_out.channel_2.sensity");
                                        }
                                        closeBox();
                                        openHorizontalBox("");
                                        {
                                             create_switch_no_caption(sw_switchit, "midi_out.channel_2.on_off");
                                             openFrameBox("");
                                             closeBox();
                                             openVerticalBox("");
                                             {
                                                  openFrameBox("");
                                                  closeBox();
                                                  openPaintBox2("");
                                                  {
                                                       create_switch_no_caption(sw_led,"system.midistat2");
                                                  }
                                                  closeBox();
                                                  openFrameBox("");
                                                  closeBox();
                                             }
                                             closeBox();
                                             openFrameBox("");
                                             closeBox();

                                             openHorizontalBox(" ");
                                             {
                                                  addPToggleButton("midi_out.channel_2.auto_pitch");
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

                         openVerticalBox("channel3");
                         {
                              openpaintampBox(" ");
                              {
                                   openVerticalBox("");
                                   {
                                        openHorizontalBox("");
                                        {
                                             create_small_rackknob("midi_out.channel_3.velocity");
                                             openVerticalBox("");
                                             {
                                                  create_small_rackknob("midi_out.channel_3.volume");
                                                  addCheckButton("midi_out.channel_3.autogain");
                                             }
                                             closeBox();
                                             openVerticalBox("");
                                             {
                                                  addNumEntry("midi_out.channel_3.channel");
                                                  addNumEntry("midi_out.channel_3.program");
                                             }
                                             closeBox();
                                             create_small_rackknob("midi_out.channel_3.oktave");
                                             create_small_rackknob("midi_out.channel_3.sensity");
                                        }
                                        closeBox();
                                        openHorizontalBox("");
                                        {
                                             create_switch_no_caption(sw_switchit, "midi_out.channel_3.on_off");
                                             openFrameBox("");
                                             closeBox();
                                             openVerticalBox("");
                                             {
                                                  openFrameBox("");
                                                  closeBox();
                                                  openPaintBox2("");
                                                  {
                                                       create_switch_no_caption(sw_led,"system.midistat3");
                                                  }
                                                  closeBox();
                                                  openFrameBox("");
                                                  closeBox();
                                             }
                                             closeBox();

                                             openFrameBox("");
                                             closeBox();
                                             openHorizontalBox(" ");
                                             {
                                                  addPToggleButton("midi_out.channel_3.auto_pitch");
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

                         openVerticalBox("beat_detector");
                         {
                              openpaintampBox(" ");
                              {
                                   openVerticalBox("");
                                   {

                                        openHorizontalBox("");
                                        {
                                             create_small_rackknob("beat_detector.stepper");
                                             create_small_rackknob("beat_detector.note_off");
                                             create_small_rackknob("beat_detector.atack_gain");
                                             create_small_rackknob("beat_detector.beat_gain");
                                        }
                                        closeBox();
                                        addStatusDisplay("", &gx_engine::audio.midistat);
                                        openHorizontalBox("");
                                        {
                                             openFrameBox("");
                                             closeBox();
                                             openPaintBox2("");
                                             {
                                                  create_switch_no_caption(sw_led,"system.midistat1");
                                             }
                                             closeBox();
                                             openFrameBox("");
                                             closeBox();
                                             openPaintBox2("");
                                             {
                                                  create_switch_no_caption(sw_led,"system.midistat2");
                                             }
                                             closeBox();
                                             openFrameBox("");
                                             closeBox();
                                             openPaintBox2("");
                                             {
                                                  create_switch_no_caption(sw_led,"system.midistat3");
                                             }
                                             closeBox();
                                             openFrameBox("");
                                             closeBox();
                                        }
                                        closeBox();

                                        openVerticalBox("Midi gain");
                                        {
                                             create_wheel("beat_detector.midi_gain");
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


}
closeBox();
