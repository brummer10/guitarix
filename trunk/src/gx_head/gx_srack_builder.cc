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
*    and build the stereo effect rack,
*    it's a part of the class GxMainInterface
*
* ----------------------------------------------------------------------------
*/


openHorizontalTableBox("");
{

     //----- chorus
     openHorizontalRestetBox("", &gx_engine::audio.posit8);
     {
          openVerticalBox("     chorus     ");
          {

               openHorizontalTableBox("");
               {

                    create_switch_no_caption(sw_switchit, "chorus.on_off");
                    openSpaceBox("");
                    closeBox();
                    openSpaceBox("");
                    closeBox();
                    opensDialogBox("chorus.dialog", "chorus.on_off");
                    {

                         openVerticalBox("");
                         {
                              openHorizontalTableBox("");
                              {
                                   create_bigknob("chorus.level","  level  ");
                                   create_smallknob("chorus.delay","  delay  ");
                                   create_smallknob("chorus.depth","  depth  ");
                                   create_smallknob("chorus.freq","  freq  ");
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

     openHorizontalRestetBox("", &gx_engine::audio.posit9);
     {
          openVerticalBox("flanger");
          {

               openHorizontalTableBox("");
               {

                    create_switch_no_caption(sw_switchit, "flanger.on_off");
                    openSpaceBox("");
                    closeBox();
                    openSpaceBox("");
                    closeBox();
                    opensDialogBox("flanger.dialog", "flanger.on_off");
                    {

                         openVerticalBox("");
                         {
                              openHorizontalTableBox("");
                              {
                                   create_bigknob("flanger.level","  level  ");
                                   create_smallknob("flanger.feedback gain"," feedback gain ");
                                   create_smallknob("flanger.depth","  depth  ");
                                   create_smallknob("flanger.flange delay","  delay  ");
                                   create_smallknob("flanger.flange delay offset"," delay offset");
                                   create_smallknob("flanger.LFO freq"," LFO freq  ");

                              }
                              closeBox();
                              openHorizontalBox("");
                              {
                                   openSpaceBox("");
                                   closeBox();
                                   openSpaceBox("");
                                   closeBox();
                                   openSpaceBox("");
                                   closeBox();
                                   openSpaceBox("");
                                   closeBox();
                                   openSpaceBox("");
                                   closeBox();
                                   openSpaceBox("");
                                   closeBox();
                                   create_selector("flanger.invert");
                                   openSpaceBox("");
                                   closeBox();
                                   openSpaceBox("");
                                   closeBox();
                              }
                              closeBox();
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

     openHorizontalRestetBox("", &gx_engine::audio.posit11);
     {
          openVerticalBox("moog filter");
          {

               openHorizontalTableBox("");
               {
                    create_switch_no_caption(sw_switchit, "moog.on_off");
                    openSpaceBox("");
                    closeBox();
                    openSpaceBox("");
                    closeBox();
                    opensDialogBox("moog.dialog", "moog.on_off");
                    {

                         openVerticalBox("");
                         {
                              openHorizontalTableBox("");
                              {
                                   create_smallknob("moog.Q","            Q            ");

                                   create_smallknob("moog.fr","            Hz           ");

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

     openHorizontalRestetBox("", &gx_engine::audio.posit12);
     {
          openVerticalBox("phaser");
          {

               openHorizontalTableBox("");
               {
                    create_switch_no_caption(sw_switchit, "phaser.on_off");
                    openSpaceBox("");
                    closeBox();
                    openSpaceBox("");
                    closeBox();
                    opensDialogBox("phaser.dialog", "phaser.on_off");
                    {
                         openVerticalBox("");
                         {
                              openHorizontalTableBox("");
                              {
                                   create_bigknob("phaser.level","  level ");
                                   create_smallknob("phaser.feedback gain","feedback gain");
                                   create_smallknob("phaser.depth", "depth");
                                   create_smallknob("phaser.delay", "delay");
                                   create_smallknob("phaser.delay offset", "delay offset");
                                   create_smallknob("phaser.LFO freq", "LFO");
                              }
                              closeBox();
                              openHorizontalBox("");
                              {
								   openSpaceBox("");
                                   closeBox();
                                   openSpaceBox("");
                                   closeBox();
                                   openSpaceBox("");
                                   closeBox();
                                   openSpaceBox("");
                                   closeBox();
                                   create_selector("phaser.invert");
                                   openSpaceBox("");
                                   closeBox();
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
     }
     closeBox();
}
closeBox();
