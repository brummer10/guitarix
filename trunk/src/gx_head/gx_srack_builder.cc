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
                              openHorizontalBox("");
                              {
                                   create_small_rackknobr("chorus.level","  level  ");
                                   create_small_rackknob("chorus.delay","  delay  ");
                                   create_small_rackknob("chorus.depth","  depth  ");
                                   create_small_rackknob("chorus.freq","  freq  ");
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
                              openHorizontalBox("");
                              {
                                   create_small_rackknobr("flanger.level","  level  ");
                                   create_small_rackknob("flanger.feedback gain"," feedback ");
                                   create_small_rackknob("flanger.depth","  depth  ");
                                   create_small_rackknob("flanger.flange delay","  delay  ");
                                   create_small_rackknob("flanger.flange delay offset"," delay offset");
                                   create_small_rackknob("flanger.LFO freq"," LFO ");

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
                              openHorizontalBox("");
                              {
                                   create_small_rackknobr("phaser.level","  level ");
                                   create_small_rackknob("phaser.feedback gain"," feedback ");
                                   create_small_rackknob("phaser.depth", "depth");
                                   create_small_rackknob("phaser.Notch width", "width");
                                   create_small_rackknob("phaser.NotchFreq", "freq");
                                   create_small_rackknob("phaser.MaxNotch1Freq", "max Hz");
                                   create_small_rackknob("phaser.MinNotch1Freq", "min Hz");
                                   create_small_rackknob("phaser.Speed", "speed");
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
                                   create_selector("phaser.VibratoMode");
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
                              openHorizontalBox("");
                              {
									create_small_rackknob("stereodelay.l_gain","left gain");
									create_small_rackknob("stereodelay.l_delay","left delay");
									openVerticalBox("");
									{
										create_small_rackknobr("stereodelay.LFO freq","LFO");
										openSpaceBox("");
										closeBox();
										create_selector("stereodelay.invert");
										openSpaceBox("");
										closeBox();
									}
									closeBox();	
                                   
									create_small_rackknob("stereodelay.r_gain","right gain");
									create_small_rackknob("stereodelay.r_delay","right delay");

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
                              openHorizontalBox("");
                              {
									create_small_rackknob("stereoecho.percent_l","left %");
									create_small_rackknob("stereoecho.time_l","left time");
									create_small_rackknob("stereoecho.percent_r","right %");
									create_small_rackknob("stereoecho.time_r","right time");

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
                                   create_small_rackknob("moog.Q","            Q            ");

                                   create_small_rackknob("moog.fr","            Hz           ");

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
