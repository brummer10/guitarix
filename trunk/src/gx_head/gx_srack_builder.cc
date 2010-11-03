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
          openVerticalBox("chorus");
          {

               openHorizontalTableBox("");
               {
				    openPaintBox1("");
					{
						create_switch_no_caption(sw_switchit, "chorus.on_off");
                    }
                    closeBox();
                    
                    opensDialogBox("chorus.dialog", "chorus.on_off","RackBox_expose");
                    {

                         openVerticalBox("");
                         {
                              openHorizontalTableBox("");
                              {
                                   create_smallknobr("chorus.level","  level  ");
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
					openPaintBox1("");
					{
						create_switch_no_caption(sw_switchit, "flanger.on_off");
                    }
					closeBox();
                    opensDialogBox("flanger.dialog", "flanger.on_off","RackBox_expose");
                    {

                         openVerticalBox("");
                         {
                              openHorizontalTableBox("");
                              {
                                   create_smallknobr("flanger.level","  level  ");
                                   create_smallknob("flanger.feedback gain"," feedback ");
                                   create_smallknob("flanger.depth","  depth  ");
                                   create_smallknob("flanger.flange delay","  delay  ");
                                   create_smallknob("flanger.flange delay offset"," delay offset");
                                   create_smallknob("flanger.LFO freq"," LFO ");

                              }
                              closeBox();
                              openSpaceBox("");
                              closeBox();
                              openHorizontalBox("");
                              {
                                   openSpaceBox("");
                                   closeBox();
                                   create_selector("flanger.invert");
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
          openVerticalBox("moog");
          {

               openHorizontalTableBox("");
               {
					openPaintBox1("");
					{
						create_switch_no_caption(sw_switchit, "moog.on_off");
                    }
					closeBox();
                    opensDialogBox("moog.dialog", "moog.on_off","RackBox_expose");
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
     
	openHorizontalRestetBox("", &gx_engine::audio.posit15);
     {
          openVerticalBox("delay");
          {

               openHorizontalTableBox("");
               {
					openPaintBox1("");
					{
						create_switch_no_caption(sw_switchit, "stereodelay.on_off");
                    }
					closeBox();
                    opensDialogBox("stereodelay.dialog", "stereodelay.on_off","RackBox_expose");
                    {

                         openVerticalBox("");
                         {
                              openHorizontalTableBox("");
                              {
									create_smallknob("stereodelay.l_gain","left gain");
									create_smallknob("stereodelay.l_delay","left delay");
									openVerticalBox("");
									{
										create_smallknobr("stereodelay.LFO freq","LFO");
										openSpaceBox("");
										closeBox();
										create_selector("stereodelay.invert");
										openSpaceBox("");
										closeBox();
									}
									closeBox();	
                                   
									create_smallknob("stereodelay.r_gain","right gain");
									create_smallknob("stereodelay.r_delay","right delay");

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
     
	openHorizontalRestetBox("", &gx_engine::audio.posit16);
     {
          openVerticalBox("echo");
          {

               openHorizontalTableBox("");
               {
					openPaintBox1("");
					{
						create_switch_no_caption(sw_switchit, "stereoecho.on_off");
                    }
					closeBox();
                    opensDialogBox("stereoecho.dialog", "stereoecho.on_off","RackBox_expose");
                    {

                         openVerticalBox("");
                         {
                              openHorizontalTableBox("");
                              {
									create_smallknob("stereoecho.percent_l","left %");
									create_smallknob("stereoecho.time_l","left time");
									create_smallknob("stereoecho.percent_r","right %");
									create_smallknob("stereoecho.time_r","right time");

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
				    openPaintBox1("");
					{
						create_switch_no_caption(sw_switchit, "phaser.on_off");
                    }
                    closeBox();
                    opensDialogBox("phaser.dialog", "phaser.on_off","RackBox_expose");
                    {
                         openVerticalBox("");
                         {
                              openHorizontalTableBox("");
                              {
                                   create_smallknobr("phaser.level","  level ");
                                   create_smallknob("phaser.feedback gain"," feedback ");
                                   create_smallknob("phaser.depth", "depth");
                                   create_smallknob("phaser.Notch width", "Width");
                                   create_smallknob("phaser.NotchFreq", "Freq");
                                   create_smallknob("phaser.MaxNotch1Freq", "Max Freq");
                                   create_smallknob("phaser.MinNotch1Freq", "Min Freq");
                                   create_smallknob("phaser.Speed", "speed");
                              }
                              closeBox();
                              openSpaceBox("");
                              closeBox();
                              openHorizontalBox("");
                              {
                                   openSpaceBox("");
                                   closeBox();
                                   create_selector("phaser.invert");
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
}
closeBox();
