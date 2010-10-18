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
                    create_switch_no_caption(sw_switchit, "compressor.on_off");
                    create_selector("compressor.pp");
//----- open a dialogbox(toplevel widget) and put the advanced controlls in it
                    openDialogBox("compressor.dialog", "compressor.on_off");
                    {


                         openFrameBox("");
                         closeBox();
                         openFrameBox("");
                         closeBox();
                         openVerticalBox("compressor");
                         {
                              openHorizontalTableBox("");
                              {
                                   create_smallknob("compressor.knee");
                                   create_smallknob("compressor.ratio");
                                   create_smallknob("compressor.threshold");
                              }
                              closeBox();
                              openVerticalBox("envelop");
                              {
                                   create_hslider("compressor.attack");
                                   create_hslider("compressor.release");
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


     openHorizontalOrderBox("", &gx_engine::audio.posit0);
     {
//----- crybaby
          openVerticalBox("crybaby");
          {

               openHorizontalBox("");
               {
                    create_switch_no_caption(sw_switchit, "crybaby.on_off");
                    create_selector("crybaby.pp");
//----- open a dialogbox(toplevel widget) and put the advanced controlls in it
                    openDialogBox("crybaby.dialog", "crybaby.on_off");
                    {


                         openVerticalBox("");
                         {
                              openHorizontalTableBox("");
                              {
                                   create_bigknob("crybaby.wah","  wah   ");
                                   openVerticalBox("");
                                   {
                                        openSpaceBox("");
                                        closeBox();
                                        create_smallknob("crybaby.level","  level  ");
                                   }
                                   closeBox();
                                   openVerticalBox("");
                                   {
                                        openSpaceBox("");
                                        closeBox();
                                        create_smallknob("crybaby.wet_dry","wet/dry");
                                   }
                                   closeBox();

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
                                   create_selector("crybaby.autowah");
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
                    create_switch_no_caption(sw_switchit, "freeverb.on_off");
                    create_selector("freeverb.pp");
//----- open a dialogbox(toplevel widget) and put the advanced controlls in it
                    openDialogBox("freeverb.dialog", "freeverb.on_off");
                    {

                         openFrameBox("");
                         closeBox();
                         openFrameBox("");
                         closeBox();
                         openHorizontalTableBox("");
                         {
                              create_bigknob("freeverb.RoomSize");
                              create_smallknob("freeverb.damp");
                              create_smallknob("freeverb.wet_dry");
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
                    create_switch_no_caption(sw_switchit, "IR.on_off");
                    create_selector("IR.pp");
//----- open a dialogbox(toplevel widget) and put the advanced controlls in it
                    openDialogBox("IR.dialog", "IR.on_off");
                    {

                         openVerticalBox1("");
                         {

                              openHorizontalBox("");
                              {
                                   openFrameBox("");
                                   closeBox();
                                   openFrameBox("");
                                   closeBox();
                                   openHorizontalTableBox("");
                                   {
                                        create_bigknob("IR.freq","    freq     ");
                                        create_smallknob("IR.peak","     peak    ");
                                        create_smallknob("IR.bandwidth","    bandwidth    ");
                                   }
                                   closeBox();
                                   openFrameBox("");
                                   closeBox();
                                   openFrameBox("");
                                   closeBox();

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
                                   create_selector("IR.auto_freq");
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
                    create_switch_no_caption(sw_switchit, "echo.on_off");
                    create_selector("echo.pp");
                    openDialogBox("echo.dialog", "echo.on_off");
                    {

                         openVerticalBox("");
                         {
                              openHorizontalTableBox("");
                              {

                                   create_bigknob("echo.time","  time  ");

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
                    create_switch_no_caption(sw_switchit, "delay.on_off");
                    create_selector("delay.pp");

                    openDialogBox("delay.dialog", "delay.on_off");
                    {

                         openVerticalBox("");
                         {
                              openHorizontalTableBox("");
                              {

                                   create_bigknob("delay.delay"," delay ");

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
                    create_switch_no_caption(sw_switchit, "overdrive.on_off");
                    create_selector("overdrive.pp");
                    openDialogBox("overdrive.dialog", "overdrive.on_off");
                    {
//----- overdrive
                         openHorizontalTableBox("");
                         {

                              openSpaceBox("");
                              closeBox();
                              create_bigknob("overdrive.drive","  drive ");
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
                    create_switch_no_caption(sw_switchit, "distortion.on_off");
                    create_selector("distortion.pp");
                    //----- open a dialogbox(toplevel widget) and put the advanced controlls in it

                    openDialogBox("distortion.dialog", "distortion.on_off");
                    {
                         openHorizontalBox("");
                         {
                              openVerticalBox("");
                              {
                                   openHorizontalBox("");
                                   {
                                        openVerticalBox1("");
                                        {
                                             create_bigknob("distortion.drive","  drive ");
                                             create_smallknob("distortion.level","  level  ");
                                             create_smallknob("distortion.gain","  gain  ");
                                        }
                                        closeBox();
                                        openVerticalBox1("");
                                        {
                                             openHorizontalBox("");
                                             {
                                                  openVerticalBox1("");
                                                  {
                                                       create_smallknob("distortion.low_drive"," low drive ");
                                                       create_smallknob("distortion.low_gain"," low gain ");
                                                  }
                                                  closeBox();
                                                  openVerticalBox1("");
                                                  {
                                                       create_smallknob("distortion.middle_l_drive"," middle low drive ");
                                                       create_smallknob("distortion.middle_l_gain"," middle low gain ");
                                                  }
                                                  closeBox();
                                                  openVerticalBox1("");
                                                  {
                                                       create_smallknob("distortion.middle_h_drive"," middle high drive ");
                                                       create_smallknob("distortion.middle_h_gain"," middle high gain ");
                                                  }
                                                  closeBox();
                                                  openVerticalBox1("");
                                                  {
                                                       create_smallknob("distortion.high_drive"," high drive ");
                                                       create_smallknob("distortion.high_gain"," high gain ");
                                                  }
                                                  closeBox();
                                             }
                                             closeBox();
                                             openHorizontalBox("");
                                             {
                                                  create_hslider("distortion.split_low_freq", "split low freq");
                                                  create_hslider("distortion.split_middle_freq", "split middle freq");
                                                  create_hslider("distortion.split_high_freq", "split high freq");
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
                              openHorizontalTableBox("");
                              {
                                   openVerticalBox("low/highpass");
                                   {
                                        create_smallknob("distortion.low_highpass.high_freq","high-pass ");
                                        create_smallknob("distortion.low_highpass.low_freq"," low-pass ");
                                        create_switch_no_caption(sw_switchit, "distortion.low_highpass.on_off");
                                   }
                                   closeBox();
                                   openVerticalBox("low/highcut");
                                   {
                                        create_smallknob("distortion.low_highcutoff.low_freq"," low-cut ");
                                        create_smallknob("distortion.low_highcutoff.high_freq","high-cut ");
                                        create_switch_no_caption(sw_switchit, "distortion.low_highcutoff.on_off");
                                   }
                                   closeBox();
                                   openVerticalBox("resonator");
                                   {
                                        create_smallknob("distortion.trigger","trigger ");
                                        create_smallknob("distortion.vibrato"," vibrato ");
                                        create_switch_no_caption(sw_switchit, "distortion.resonator.on_off");
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
          //----- end distortion
     }
     closeBox();

     openHorizontalOrderBox(" ", &gx_engine::audio.posit10);
     {
          openVerticalBox("EQ");
          {
               openHorizontalBox("");
               {
                    create_switch_no_caption(sw_switchit, "eqs.on_off");
                    create_selector("eqs.pp");
					//----- open a dialogbox(toplevel widget) and put the advanced controlls in it
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
}
closeBox();
