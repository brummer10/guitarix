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
//----- the compressor
     openHorizontalOrderBox("", &gx_engine::audio.posit5);
     {
          openVerticalBox("Compressor");
          {
               openHorizontalBox("");
               {
					openPaintBox1("");
					{
						create_switch_no_caption(sw_switchit, "compressor.on_off");
						create_selector("compressor.pp");
                    }
					closeBox();
//----- open a dialogbox(toplevel widget) and put the advanced controlls in it
                    openDialogBox("compressor.dialog", "compressor.on_off");
                    {


                         openFrameBox("");
                         closeBox();
                         openFrameBox("");
                         closeBox();
                         
                              openHorizontalTableBox("");
                              {
                                   create_smallknob("compressor.knee");
                                   create_smallknobr("compressor.ratio");
                                   create_smallknob("compressor.threshold");
                              
                              
                                   create_smallknob("compressor.attack");
                                   create_smallknob("compressor.release");
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


     openHorizontalOrderBox("", &gx_engine::audio.posit0);
     {
//----- crybaby
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
		
                    openDialogBox("crybaby.dialog", "crybaby.on_off");
                    {


                         openVerticalBox("");
                         {
                              openHorizontalTableBox("");
                              {
                                   create_smallknobr("crybaby.wah","  wah   ");
                                   
                                   create_smallknob("crybaby.level","  level  ");
                                  
                                   create_smallknob("crybaby.wet_dry","  dry/wet  ");
                                   

                              }
                              closeBox();
                              openSpaceBox("");
                              closeBox();
                              openHorizontalBox("");
                              {
                                   
                                   create_selector("crybaby.autowah");
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
//----- end advanced settings widget
               closeBox();
          }
          closeBox();
//----- end crybaby
     }
     closeBox();


     openHorizontalOrderBox("", &gx_engine::audio.posit3);
     {
//----- freeverb
          openVerticalBox(" freeverb");
          {

               openHorizontalBox("");
               {
					openPaintBox1("");
					{
						create_switch_no_caption(sw_switchit, "freeverb.on_off");
						create_selector("freeverb.pp");
                    }
                    closeBox();

                    openDialogBox("freeverb.dialog", "freeverb.on_off");
                    {

                         openFrameBox("");
                         closeBox();
                         openFrameBox("");
                         closeBox();
                         openHorizontalTableBox("");
                         {
                              create_smallknobr("freeverb.RoomSize");
                              create_smallknob("freeverb.damp");
                              create_smallknob("freeverb.wet_dry", "dry/wet");
                         }
                         closeBox();
                         openFrameBox("");
                         closeBox();
                         openFrameBox("");
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

     openHorizontalOrderBox("", &gx_engine::audio.posit4);
     {
//----- IR
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
                    
                    openDialogBox("IR.dialog", "IR.on_off");
                    {

                         openVerticalBox1("");
                         {

                              openHorizontalBox("");
                              {
                                   
                                   openHorizontalTableBox("");
                                   {
                                        create_smallknob("IR.freq"," freq ");
                                        create_smallknob("IR.peak"," peak ");
                                        create_smallknob("IR.bandwidth"," bandwidth ");
                                   }
                                   closeBox();

                              }
                              closeBox();
                              openSpaceBox("");
                              closeBox();
                              openHorizontalBox("");
                              {
                                   
                                   create_selector("IR.auto_freq");
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
//----- end advanced settings widget
               closeBox();
          }
          closeBox();
//----- end IR
     }
     closeBox();
     openHorizontalOrderBox("", &gx_engine::audio.posit6);
     {
//----- echo
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
                    
                    openDialogBox("echo.dialog", "echo.on_off");
                    {

                         openVerticalBox("");
                         {
                              openHorizontalTableBox("");
                              {

                                   create_smallknobr("echo.time","  time  ");

                                   create_smallknob("echo.percent","    %    ");

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

                    openDialogBox("delay.dialog", "delay.on_off");
                    {

                         openVerticalBox("");
                         {
                              openHorizontalTableBox("");
                              {

                                   create_smallknobr("delay.delay"," delay ");

                                   create_smallknob("delay.gain","  gain ");

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
                    openDialogBox("overdrive.dialog", "overdrive.on_off");
                    {
//----- overdrive
                         openHorizontalTableBox("");
                         {

                              openSpaceBox("");
                              closeBox();
                              create_smallknobr("overdrive.drive","  drive ");
                              openSpaceBox("");
                              closeBox();

                         }
                         closeBox();
//-----end overdrive
                    }
                    closeBox();
               }
               closeBox();
          }
          closeBox();
     }
     closeBox();

     openHorizontalOrderBox("", &gx_engine::audio.posit2);
     {
          //----- distortion
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

                    openDialogBox("gx_distortion.dialog", "gx_distortion.on_off");
                    {
                         openHorizontalBox("");
                         {
                              openVerticalBox("");
                              {
                                   openHorizontalBox("");
                                   {
                                        openVerticalBox1("");
                                        {
                                             create_smallknobr("gx_distortion.drive","  drive ");
                                             create_smallknob("gx_distortion.level","  level  ");
                                             create_smallknob("gx_distortion.gain","  gain  ");
                                        }
                                        closeBox();
                                        openVerticalBox1("");
                                        {
                                             openHorizontalBox("");
                                             {
                                                  openVerticalBox1("");
                                                  {
                                                       create_smallknobr("gx_distortion.low_drive"," low drive ");
                                                       create_smallknob("gx_distortion.low_gain"," low gain ");
                                                  }
                                                  closeBox();
                                                  openVerticalBox1("");
                                                  {
                                                       create_smallknobr("gx_distortion.middle_l_drive"," middle low drive ");
                                                       create_smallknob("gx_distortion.middle_l_gain"," middle low gain ");
                                                  }
                                                  closeBox();
                                                  openVerticalBox1("");
                                                  {
                                                       create_smallknobr("gx_distortion.middle_h_drive"," middle high drive ");
                                                       create_smallknob("gx_distortion.middle_h_gain"," middle high gain ");
                                                  }
                                                  closeBox();
                                                  openVerticalBox1("");
                                                  {
                                                       create_smallknobr("gx_distortion.high_drive"," high drive ");
                                                       create_smallknob("gx_distortion.high_gain"," high gain ");
                                                  }
                                                  closeBox();
                                             }
                                             closeBox();
                                             openHorizontalBox("");
                                             {
                                                  create_hslider("gx_distortion.split_low_freq", "split low freq");
                                                  create_hslider("gx_distortion.split_middle_freq", "split middle freq");
                                                  create_hslider("gx_distortion.split_high_freq", "split high freq");
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
               
							   openVerticalBox("resonator");
							   {
									create_smallknob("gx_distortion.trigger","trigger ");
									create_smallknob("gx_distortion.vibrato"," vibrato ");
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
          //----- end distortion
     }
     closeBox();

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
					
					openDialogBox("eqs.dialog", "eqs.on_off");
                    {
						openVerticalBox("");
						{
							 openHorizontalTableBox("");
							 {
								  create_spin_value("eqs.freq31_25");
								  create_spin_value("eqs.freq62_5");
								  create_spin_value("eqs.freq125");
								  create_spin_value("eqs.freq250");
								  create_spin_value("eqs.freq500");
								  create_spin_value("eqs.freq1k");
								  create_spin_value("eqs.freq2k");
								  create_spin_value("eqs.freq4k");
								  create_spin_value("eqs.freq8k");
								  create_spin_value("eqs.freq16k");
							 }
							 closeBox();
							 openHorizontalTableBox("");
							 {
								  create_eqslider_no_caption("eqs.fs31_25");
								  create_eqslider_no_caption("eqs.fs62_5");
								  create_eqslider_no_caption("eqs.fs125");
								  create_eqslider_no_caption("eqs.fs250");
								  create_eqslider_no_caption("eqs.fs500");
								  create_eqslider_no_caption("eqs.fs1k");
								  create_eqslider_no_caption("eqs.fs2k");
								  create_eqslider_no_caption("eqs.fs4k");
								  create_eqslider_no_caption("eqs.fs8k");
								  create_eqslider_no_caption("eqs.fs16k");
							 }
							 closeBox();
							 openHorizontalTableBox("");
							 {
								  create_smallknob("eqs.Qs31_25","Q");
								  create_smallknob("eqs.Qs62_5","Q");
								  create_smallknob("eqs.Qs125","Q");
								  create_smallknob("eqs.Qs250","Q");
								  create_smallknob("eqs.Qs500","Q");
								  create_smallknob("eqs.Qs1k","Q");
								  create_smallknob("eqs.Qs2k","Q");
								  create_smallknob("eqs.Qs4k","Q");
								  create_smallknob("eqs.Qs8k","Q");
								  create_smallknob("eqs.Qs16k","Q");
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
     
     openHorizontalOrderBox(" ", &gx_engine::audio.posit14);
     {
		 openVerticalBox("low high pass ");
          {
               openHorizontalBox("");
               {
					openPaintBox1("");
					{
						create_switch_no_caption(sw_switchit, "low_highpass.on_off");
						create_selector("low_high_pass.pp");
                    }
                    closeBox();
				 
                    openDialogBox("low_high_pass.dialog", "low_highpass.on_off");
                    {
						openHorizontalBox("");
                        {
							openVerticalBox("low/highpass");
							{
								openHorizontalBox("");
								{
									create_smallknob("low_high_pass.low_highpass.high_freq","high-pass ");
									create_smallknob("low_high_pass.low_highpass.low_freq"," low-pass ");
									create_switch_no_caption(sw_switchit, "low_high_pass.low_highpass.on_off");
								}
								closeBox();
							}
							closeBox();
							openSpaceBox("");
							closeBox();   
							openVerticalBox("low/highcut");
							{
								openHorizontalBox("");
								{
									create_smallknob("low_high_pass.low_highcutoff.low_freq"," low-cut ");
									create_smallknob("low_high_pass.low_highcutoff.high_freq","high-cut ");
									create_switch_no_caption(sw_switchit, "low_high_pass.low_highcutoff.on_off");
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
