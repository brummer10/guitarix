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
 *    This is the guitarix interface builder,
 *    it's a part of the class GxMainInterface
 *
 * ----------------------------------------------------------------------------
 */

#include "guitarix.h"

//-------- the guitarix user interface build instruktions

namespace gx_gui
{

#ifndef NDEBUG
// debug_check
inline void all_midi_params_assigned()
{
	for (ParamMap::iterator i = parameter_map.begin(); i != parameter_map.end(); i++) {
		if (i->second->isControllable() && ! i->second->isUsed() && ! i->second->isExperimental())
			gx_system::gx_print_error("Debug Check",
			                          "midi-parameter not assigned in ui: " + i->first);
	}
}
#endif

/* -------- user interface builder ---------- */
void GxMainInterface::setup()
{
	//----- the main box, all visible widgets are a child of this box
	openVerticalBox("");

	//----- add the menubar on top
	{
		addMainMenu();

		//----- this is a dummy widget, only for save settings for the latency warning dialog
		openWarningBox("WARNING", &gx_engine::audio.fwarn);
		setSkinBox("SKIN", &gx_engine::audio.fskin);
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
						addNumDisplay();
					}
					closeBox();

					//----- the balance widget
					openVerticalBox("");
					{
						create_hslider("amp.balance", "balance");
					}
					closeBox();

					//----- the jconv widget on the main window
					openFrameBox("");
					{
						openExpanderBox(" convolver ", &gx_engine::audio.fexpand2);
						{
							openHandleBox("  ");
							{
								openVerticalBox("");
								{
									openHorizontalBox("");
									{
#if 0 //FIXME (delete)
										openDialogBox("jconv.dialog", "jconv.on_off");
										{
										    openPlugBox("");
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
	                                                        create_bigknob("jconv.left_gain","     left gain     ");
                                                            create_smallknob("jconv.left_delay"," left delay ");
                                                            create_bigknob("jconv.right_gain"," right gain ");
                                                            create_smallknob("jconv.right_delay"," right delay ");
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
										closeBox();
#endif
										create_hslider("jconv.wet_dry");
									}
									closeBox();

									openVerticalBox("");
									{
										addJConvButton("convolver settings", &gx_engine::audio.filebutton);
										addJToggleButton("run convolver", &gx_jconv::GxJConvSettings::checkbutton7);
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
		openExpanderBox(" CONTROLS ", &gx_engine::audio.fexpand);
		{
			//----- a handle box is a vertical box
			openHandleBox("  ");
			{
				//----- arange all widgets in a horizontal scale
				openHorizontalBox("");
				{
					openFrameBox("");
					closeBox();
					openFrameBox("");
					closeBox();
					openFrameBox("");
					closeBox();
					//----- arange all widgets in a vertical scale
					openPaintBox1("");
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
                                openHorizontalBox("");
                                {
                                    openFrameBox("");
                                    closeBox();
                                    // add a meter level box: out of box stack, no need to closeBox
                                    openLevelMeterBox("Signal Level");
                                    openFrameBox("");
                                    closeBox();
                                }
                                closeBox();
                                openVerticalBox("");
                                {
                                    openSpaceBox("");
                                    closeBox();
                                    create_selector("eqt.onetwo");
                                    openHorizontalBox("");
                                    {
                                        openSpaceBox("");
                                        closeBox();
                                        create_switch(sw_minitoggle, "eq.on_off", "EQ", Gtk::POS_RIGHT);
                                        openVerticalSwitchBox(" ",0, 1, &gx_engine::audio.witcheq);
                                        {

                                            openDialogBox("eq.dialog", "eq.on_off");
                                            {
                                                openPlugBox("");
                                                {
                                                    openVerticalBox("");
                                                    {
                                                        openHorizontalTableBox("");
                                                        {
                                                            create_eqslider("eq.f31_25","31,25");
                                                            create_eqslider("eq.f62_5"," 62,5");
                                                            create_eqslider("eq.f125"," 125 ");
                                                            create_eqslider("eq.f250"," 250 ");
                                                            create_eqslider("eq.f500"," 500 ");
                                                            create_eqslider("eq.f1k","  1k  ");
                                                            create_eqslider("eq.f2k","  2k  ");
                                                            create_eqslider("eq.f4k","  4k  ");
                                                            create_eqslider("eq.f8k","  8k  ");
                                                            create_eqslider("eq.f16k"," 16k ");
                                                        }
                                                        closeBox();
                                                        openHorizontalTableBox("");
                                                        {
                                                            create_smallknob("eq.Q31_25","    Q    ");
                                                            create_smallknob("eq.Q62_5","Q");
                                                            create_smallknob("eq.Q125","Q");
                                                            create_smallknob("eq.Q250","Q");
                                                            create_smallknob("eq.Q500","Q");
                                                            create_smallknob("eq.Q1k","Q");
                                                            create_smallknob("eq.Q2k","Q");
                                                            create_smallknob("eq.Q4k","Q");
                                                            create_smallknob("eq.Q8k","Q");
                                                            create_smallknob("eq.Q16k","Q");
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

                                        openVerticalSwitchBox(" ",1, 1, &gx_engine::audio.witcheq);
                                        {
                                            openDialogBox("eqs.dialog",  "eq.on_off");
                                            {
                                                openPlugBox("");
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
                            }
                            closeBox();
                            openFrameBox("");
                            closeBox();

							openVerticalBox("");
							{

                                openFlipLabelBox("volume");
                                {
                                    openHorizontalBox("");
                                    {
                                        openSpaceBox("");
                                        closeBox();
                                        create_bigknob("amp.in_level");
                                        openSpaceBox("");
                                        closeBox();
                                        create_bigknob("amp.out_master");
                                        openSpaceBox("");
                                        closeBox();
                                    }
                                    closeBox();
                                    openSpaceBox("");
                                        closeBox();
                                }
                                closeBox();
                                //----- volume controll ready

                                //----- open a box for the tone and the fuzz controllers
                                openFlipLabelBox("tone");
                                {
                                    openHorizontalBox("");
                                    {
                                        openSpaceBox("");
                                        closeBox();
                                        create_smallknob("amp.tonestack.Bass");
                                        openSpaceBox("");
                                        closeBox();
                                        create_smallknob("amp.tonestack.Middle");
                                        openSpaceBox("");
                                        closeBox();
                                        create_smallknob("amp.tonestack.Treble");
                                        openSpaceBox("");
                                        closeBox();
                                    }
                                    closeBox();
                                    openHorizontalBox("");
                                    {
	                                    openVerticalBox1("");
                                        closeBox();
                                        create_switch(sw_minitoggle, "amp.bass_boost.on_off", " bass boost  ", Gtk::POS_RIGHT);
                                        openSpaceBox("");
                                        closeBox();
                                        openSpaceBox("");
                                        closeBox();
                                    }
                                    closeBox();
                                    openHorizontalBox("");
                                    {
                                        create_selector("amp.tonestack.select");
                                        openVerticalBox1("");
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
						//----- end tone and fuzz controll

						openHorizontalBox("");
							{
								openVerticalBox("shaper ");
								{
									create_switch_no_caption(sw_switch, "shaper.on_off");
									openFrameBox("");
									{
										create_wheel("shaper.sharper");
									}
									closeBox();
								}
								closeBox();
								openVerticalBox("     noise gate      ");
								{
									create_switch_no_caption(sw_switch, "noise_gate.on_off");
									openFrameBox("");
									{
										create_wheel("noise_gate.threshold");
									}
									closeBox();
								}
								closeBox();
								openVerticalBox("anti aliase");
								{
									create_switch_no_caption(sw_switch, "anti_aliase.on_off");
									openFrameBox("");
									{
										create_wheel("anti_aliase.feedback");
									}
									closeBox();
								}
								closeBox();
							}
							closeBox();

						//----- the next part in the vertical box,
						openExpanderBox(" amplifier", &gx_engine::audio.fampexpand);
                        {
						openAmpBox("");
						{
							openAmpBox("  ");
							{
								openHorizontalBox("");
								{
                                    //openSpaceBox("");
                                    //closeBox();
                                    openVerticalBox1("model    ");
									{
                                        openVerticalBox1("");
                                        closeBox();
                                        create_selector("amp.model");
									}
									closeBox();

									openVerticalBox1("");
									{
										create_switch(sw_minitoggle, "amp.oversample.on_off", "oversample  ", Gtk::POS_RIGHT);
									    create_selector("amp.select");
									}
									closeBox();

									/*openVerticalBox1("");
									{
                                        create_switch(sw_minitoggle, "amp.bass_boost.on_off", "bass boost  ");
                                        openSpaceBox("");
                                        closeBox();
                                        openVerticalBox1("");
                                        closeBox();
									}
									closeBox();*/

									openVerticalBox1("");
									{
                                        create_switch(sw_minitoggle, "convolve.on_off", "amp tune    ", Gtk::POS_RIGHT);
                                        create_selector("convolve.select");

									}
									closeBox();
								}
								closeBox();
							}
							closeBox();
							//----- the second part in the vertical box
							openAmpBox("  ");
							{
							    openVerticalSwitchBox(" ",0, 2, &gx_engine::audio.witchamp);
                                {
                                openHorizontalBox("");
                                {
                                    openVerticalBox("");
                                    {
                                        openVerticalBox("");
                                        {
                                            create_switch(sw_switch, "preamp.on_off", "preamp");
                                            create_wheel("preamp.atan");
                                        }
                                        closeBox();
                                        openFrameBox("");
                                        {
                                        }
                                        closeBox();
                                        openVerticalBox("");
                                        {
                                            create_switch(sw_switch, "drive.on_off", "drive");
                                            create_wheel("drive.value");
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
                                            create_switch(sw_switch, "tube.on_off", "tube");
                                            create_wheel("tube.fuzzy");
                                        }
                                        closeBox();
                                        openFrameBox("");
                                        {
                                        }
                                        closeBox();
                                        openVerticalBox("");
                                        {
                                            create_switch(sw_switch, "tube.vibrato.on_off", "vibrato");
                                            create_wheel("tube.vibrato");
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
                                            create_switch(sw_switch, "tube2.on_off", "tube2");
                                            openFrameBox("");
                                            {
                                                create_wheel("tube2.fuzzy");
                                            }
                                            closeBox();
                                        }
                                        closeBox();
                                        openVerticalBox("");
                                        {
                                            openVerticalBox1("resonanz");
                                            {
                                                create_wheel("tube2.resonanz");
                                            }
                                            closeBox();
                                            openVerticalBox1("vibrato");
                                            {
                                                create_wheel("tube2.vibrato");
                                            }
                                            closeBox();
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
                                            create_switch(sw_switch, "tube3.on_off", "tube3");
                                            openFrameBox("");
                                            {
                                                create_wheel("tube3.g");
                                            }
                                            closeBox();

                                        }
                                        closeBox();
                                        openVerticalBox("");
                                        {
                                            openVerticalBox1("dist");
                                            {
                                                create_wheel("tube3.dist");
                                            }
                                            closeBox();
                                            openVerticalBox1("level");
                                            {
                                                create_wheel("tube3.q");
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

								openVerticalSwitchBox(" ",1, 2, &gx_engine::audio.witchamp);
                                {
                                    openHorizontalBox("");
                                {
                                    openVerticalBox("");
                                    {
                                        openVerticalBox("");
                                        {
                                            create_switch(sw_switch, "amp2.preamp.ON", "preamp");
                                            openSpaceBox("");
                                            closeBox();
                                            create_smallknob_no_caption("amp2.preamp.Pregain");
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
                                            create_switch(sw_switch, "amp2.stage1.ON", "tube");
                                            openSpaceBox("");
                                            closeBox();
                                            create_smallknob_no_caption("amp2.stage1.gain1");
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
                                            create_switch(sw_switch, "amp2.stage2.ON", "tube2");
                                            openSpaceBox("");
                                            closeBox();
                                            create_smallknob_no_caption("amp2.stage2.gain2");
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
                                            create_switch(sw_switch, "stage3.ON", "tube3");
                                            openSpaceBox("");
                                            closeBox();
                                            create_smallknob_no_caption("stage3.gain3");
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
						//openpaintampBox("");
                        //closeBox();
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
										openHorizontalOrderBox("", &gx_engine::audio.posit5);
										{
											openVerticalBox("compressor");
											{
											    create_selector("compressor.pp");
											    openSpaceBox("");
											    closeBox();
												create_smallknob("compressor.ratio");
												openHorizontalBox("");
												{
													create_switch_no_caption(sw_switchit, "compressor.on_off");
													//----- open a dialogbox(toplevel widget) and put the advanced controlls in it
													openDialogBox("compressor.dialog", "compressor.on_off");
													{
													    openPlugBox("");
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
													closeBox();
												}
												//----- end advanced settings widget
												closeBox();
											}
											closeBox();
											//----- end compressor
										}
										closeBox();
										openHorizontalOrderBox("", &gx_engine::audio.posit1);
										{
											//----- overdrive
											openVerticalBox("overdrive");
											{
											    create_selector("overdrive.pp");
											    openSpaceBox("");
                                                closeBox();
												create_smallknob("overdrive.drive","  drive ");
												create_switch_no_caption(sw_switchit, "overdrive.on_off");
											}
											closeBox();
											//-----end overdrive
										}
										closeBox();

										openHorizontalOrderBox("", &gx_engine::audio.posit2);
										{
											//----- distortion
											openVerticalBox("distortion");
											{
											    create_selector("distortion.pp");
                                                create_selector("distortiont.onetwo");
											    //create_switch(sw_switch, "distortion.onetwo", "");
											    openVerticalSwitchBox(" ",0, 0, &gx_engine::audio.witchdistortion);
											    {
                                                    create_smallknob("distortion.drive","  drive ");
                                                    openHorizontalBox("");
                                                    {
                                                        create_switch_no_caption(sw_switchit, "distortion.on_off");

													//----- open a dialogbox(toplevel widget) and put the advanced controlls in it

                                                            openDialogBox("distortion.dialog", "distortion.on_off");
                                                            {
                                                                openPlugBox("");
                                                                {
	                                                                openHandleBox("  ");
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

                                                        //----- end advanced settings widget
                                                        closeBox();
                                                    }
                                                    closeBox();
                                                    //----- end distortion
                                                }
                                                closeBox();//end switchbox

                                                openVerticalSwitchBox(" ",1, 0, &gx_engine::audio.witchdistortion);
                                                {
                                                    create_smallknob("distortion1.drive","  drive ");
                                                    openHorizontalBox("");
                                                    {
                                                        create_switch_no_caption(sw_switchit, "distortion.on_off");
                                                        openDialogBox("distortion1.dialog", "distortion.on_off");
                                                        {
                                                            openPlugBox("");
                                                            {
                                                                openHandleBox("  ");
                                                                {
	                                                                openHorizontalBox("");
	                                                                {
		                                                                openHorizontalTableBox("");
		                                                                {
			                                                                create_bigknob("distortion1.drive","  drive ");
                                                                            create_smallknob("distortion1.level","\n\n level");
                                                                            create_smallknob("distortion1.gain","\n\n gain");
                                                                        }
                                                                        closeBox();
                                                                        openHorizontalTableBox("");
                                                                        {
                                                                            openVerticalBox("low/highpass");
                                                                            {
                                                                                openHorizontalBox("");
                                                                                {
                                                                                    create_smallknob("distortion1.low_highpass.high_freq","high-freq ");
                                                                                    create_smallknob("distortion1.low_highpass.low_freq"," low-freq ");
                                                                                }
                                                                                closeBox();
                                                                                create_switch_no_caption(sw_switchit, "distortion1.low_highpass.on_off");
                                                                            }
                                                                            closeBox();
                                                                            openVerticalBox("low/highcutoff");
                                                                            {
                                                                                openHorizontalBox("");
                                                                                {
                                                                                    create_smallknob("distortion1.low_highcutoff.high_freq","high-freq ");
                                                                                    create_smallknob("distortion1.low_highcutoff.low_freq"," low-freq ");
                                                                                }
                                                                                closeBox();

                                                                                create_switch_no_caption(sw_switchit, "distortion1.low_highcutoff.on_off");
                                                                            }
                                                                            closeBox();
                                                                            openVerticalBox("resonanz");
                                                                            {
                                                                                openHorizontalBox("");
                                                                                {
                                                                                    create_smallknob("distortion1.trigger","trigger ");
                                                                                    create_smallknob("distortion1.vibrato"," vibrato ");
                                                                                }
                                                                                closeBox();
                                                                                create_switch_no_caption(sw_switchit, "distortion1.resonator.on_off");
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

											openHorizontalOrderBox("", &gx_engine::audio.posit3);
											{
												//----- freeverb
												openVerticalBox(" freeverb");
												{
												    create_selector("freeverb.pp");
												    openSpaceBox("");
                                                    closeBox();
													create_smallknob("freeverb.RoomSize");
													openHorizontalBox("");
													{
														create_switch_no_caption(sw_switchit, "freeverb.on_off");
														//----- open a dialogbox(toplevel widget) and put the advanced controlls in it
														openDialogBox("freeverb.dialog", "freeverb.on_off");
														{
														    openPlugBox("");
															{
                                                                openHandleBox("  ");
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
												    create_selector("IR.pp");
                                                    create_selector("IR.auto_freq");
													openHorizontalBox("");
													{
														create_smallknob("IR.freq","   freq   ");
														//create_smallknob("IR.peak"," peak ");
													}
													closeBox();
													openHorizontalBox("");
													{
														create_switch_no_caption(sw_switchit, "IR.on_off");
														//----- open a dialogbox(toplevel widget) and put the advanced controlls in it
														openDialogBox("IR.dialog", "IR.on_off");
														{
														    openPlugBox("");
															{
                                                                openHandleBox("  ");
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

											openHorizontalOrderBox("", &gx_engine::audio.posit0);
											{
												//----- crybaby
												openVerticalBox("crybaby");
												{
												    create_selector("crybaby.pp");
                                                    create_selector("crybaby.autowah");
												    //create_switch(sw_minitoggle, "crybaby.autowah"," autowah");
													create_smallknob("crybaby.wah"," wah ");
													openHorizontalBox("");
													{
														create_switch_no_caption(sw_switchit, "crybaby.on_off");
														//----- open a dialogbox(toplevel widget) and put the advanced controlls in it
														openDialogBox("crybaby.dialog", "crybaby.on_off");
														{
														    openPlugBox("");
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
		                                                                    create_bigknob("crybaby.wah","  wah   ");
                                                                            create_smallknob("crybaby.level","  level  ");
                                                                            create_smallknob("crybaby.wet_dry","wet/dry");
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
													//----- end advanced settings widget
													closeBox();
												}
												closeBox();
												//----- end crybaby
											}
											closeBox();

											openHorizontalOrderBox("", &gx_engine::audio.posit6);
											{
												//----- echo
												openVerticalBox("echo");
												{
												    create_selector("echo.pp");
												    openSpaceBox("");
                                                    closeBox();
													openHorizontalBox("");
													{

														create_smallknob("echo.time","  time  ");
													}
													closeBox();
													openHorizontalBox("");
                                                    {
                                                        create_switch_no_caption(sw_switchit, "echo.on_off");
                                                        openDialogBox("echo.dialog", "echo.on_off");
                                                        {
                                                            openPlugBox("");
															{
                                                                openHandleBox("  ");
                                                                {
                                                                    openVerticalBox("");
                                                                    {
                                                                        openHorizontalBox("");
                                                                        {
                                                                            create_smallknob("echo.time","  time  ");
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
												}
												closeBox();
											}
											closeBox();
										}
										//----- end echo
										openHorizontalOrderBox("", &gx_engine::audio.posit7);
										{
											openVerticalBox("delay");
											{
											    create_selector("delay.pp");
											    openSpaceBox("");
                                                closeBox();
												openHorizontalBox("");
												{
													create_smallknob("delay.delay"," delay ");

												}
												closeBox();
												openHorizontalBox("");
												{
                                                    create_switch_no_caption(sw_switchit, "delay.on_off");

                                                    openDialogBox("delay.dialog", "delay.on_off");
                                                    {
                                                        openPlugBox("");
                                                        {
                                                            openHandleBox("  ");
                                                            {
                                                                openVerticalBox("");
                                                                {
                                                                    openHorizontalBox("");
                                                                    {
                                                                        create_smallknob("delay.delay"," delay ");
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
											}
											closeBox();
										}
										closeBox();
									}
									closeBox();
									//----- chorus
									openHorizontalRestetBox("", &gx_engine::audio.posit8);
									{
										openVerticalBox("chorus");
										{
										    openSpaceBox("");
                                            closeBox();
											create_smallknob("chorus.level");
											openHorizontalBox("");
											{
												create_switch_no_caption(sw_switchit, "chorus.on_off");
												openDialogBox("chorus.dialog", "chorus.on_off");
												{
												    openPlugBox("");
                                                    {
                                                        openHandleBox("  ");
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
										}
										closeBox();
									}
									closeBox();
									//end chorus

									openHorizontalRestetBox("", &gx_engine::audio.posit9);
									{
										openVerticalBox("flanger");
										{
                                            create_selector("flanger.invert");
											create_smallknob("flanger.level");
											openHorizontalBox("");
											{
												create_switch_no_caption(sw_switchit, "flanger.on_off");
												openDialogBox("flanger.dialog", "flanger.on_off");
												{
												    openPlugBox("");
                                                    {
                                                        openHandleBox("  ");
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
										}
										closeBox();
									}
									closeBox();

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
											addLiveWaveDisplay(" ", &gx_engine::audio.viv , &gx_engine::audio.vivi);
										}
										closeBox();
										openVerticalBox1("");
										{
											openHorizontalBox("");
											{
											    openSlooperBox("slooper");
                                                {
                                                    openVerticalBox1("");
                                                    {


                                                        create_smallknob("SampleLooper.gain"," gain ");

                                                        openHorizontalBox("");
                                                        {
                                                            openSpaceBox("");
                                                            closeBox();
                                                            create_switch_no_caption(sw_minitoggle, "SampleLooper.on_off");

                                                            create_switch_no_caption(sw_rbutton, "SampleLooper.Capture");
                                                            create_switch_no_caption(sw_pbutton, "SampleLooper.Play");
                                                            openSpaceBox("");
                                                            closeBox();
                                                        }
                                                        closeBox();
                                                    }
                                                    closeBox();
                                                    //create_switch_no_caption(sw_switchit, "SampleLooper.on_off");
                                                }
                                                closeBox();
                                                openPaintBox("", "filter_box");
												{
												    openHorizontalBox("");
                                                    {
	                                                    create_switch(sw_minitoggle, "biquad.on_off","   BiQuad Filter     ", Gtk::POS_RIGHT);
                                                        openDialogBox("biquad.dialog", "biquad.on_off");
                                                        {
                                                            openPlugBox("");
															{
                                                                openHandleBox("  ");
                                                                {
                                                                    openVerticalBox("");
                                                                    {
                                                                        openHorizontalBox("");
                                                                        {
                                                                            create_smallknob("biquad.Freq","                                 Hz                                    ");

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
												    openHorizontalBox("");
                                                    {
	                                                    create_switch(sw_minitoggle, "MultiBandFilter.on_off","   MultiBandFilter  ", Gtk::POS_RIGHT);
                                                        openDialogBox("MultiBandFilter.dialog", "MultiBandFilter.on_off");
                                                        {
                                                            openPlugBox("");
															{
                                                                openVerticalBox("");
                                                                {
                                                                    openHorizontalTableBox("");
                                                                    {
                                                                        create_eqslider("MultiBandFilter.f31_25","31,25");
                                                                        create_eqslider("MultiBandFilter.f62_5"," 62,5");
                                                                        create_eqslider("MultiBandFilter.f125"," 125 ");
                                                                        create_eqslider("MultiBandFilter.f250"," 250 ");
                                                                        create_eqslider("MultiBandFilter.f500"," 500 ");
                                                                        create_eqslider("MultiBandFilter.f1k","  1k  ");
                                                                        create_eqslider("MultiBandFilter.f2k","  2k  ");
                                                                        create_eqslider("MultiBandFilter.f4k","  4k  ");
                                                                        create_eqslider("MultiBandFilter.f8k","  8k  ");
                                                                        create_eqslider("MultiBandFilter.f16k"," 16k ");
                                                                    }
                                                                    closeBox();
                                                                    openHorizontalTableBox("");
                                                                    {
                                                                        create_smallknob("MultiBandFilter.Q31_25","    Q    ");
                                                                        create_smallknob("MultiBandFilter.Q62_5","Q");
                                                                        create_smallknob("MultiBandFilter.Q125","Q");
                                                                        create_smallknob("MultiBandFilter.Q250","Q");
                                                                        create_smallknob("MultiBandFilter.Q500","Q");
                                                                        create_smallknob("MultiBandFilter.Q1k","Q");
                                                                        create_smallknob("MultiBandFilter.Q2k","Q");
                                                                        create_smallknob("MultiBandFilter.Q4k","Q");
                                                                        create_smallknob("MultiBandFilter.Q8k","Q");
                                                                        create_smallknob("MultiBandFilter.Q16k","Q");
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
													openHorizontalBox("");
                                                    {
	                                                    create_switch(sw_minitoggle, "moog.on_off","   Moog Filter        ", Gtk::POS_RIGHT);
                                                        openDialogBox("moog.dialog", "moog.on_off");
                                                        {
                                                            openPlugBox("");
															{
                                                                openHandleBox("  ");
                                                                {
                                                                    openVerticalBox("");
                                                                    {
                                                                        openHorizontalBox("");
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
                                                    create_cab_switch("cab.on_off","   Cab-ImpResp              ");
												}
												closeBox();
												openSlooperBox("limiter");
												{
													create_smallknob("amp.fuzz");
													openSpaceBox("");
													closeBox();
													create_selector("amp.threshold");
													openSpaceBox("");
													closeBox();
												}
												closeBox();
											}
											closeBox();
										}
										closeBox();
										openVerticalBox1("");
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
								openHorizontalBox("");
								closeBox();
								openHorizontalBox("");
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
							openDialogBox("midi_out.dialog", "system.midistat");
							{
                                openPlugBox("");
                                {
                                    openTabBox("");
                                    {
                                        openVerticalBox("channel1");
                                        {
                                            openEventBox(" ");
                                            {
                                                openHorizontalBox("");
                                                {
                                                    create_smallknob("midi_out.channel_1.velocity");
                                                    openVerticalBox("");
                                                    {
                                                        create_smallknob("midi_out.channel_1.volume");
                                                        addCheckButton("midi_out.channel_1.autogain");
                                                    }
                                                    closeBox();
                                                    openVerticalBox("");
                                                    {
                                                        addNumEntry("midi_out.channel_1.channel");
                                                        addNumEntry("midi_out.channel_1.program");
                                                    }
                                                    closeBox();
                                                    create_smallknob("midi_out.channel_1.oktave");
                                                    create_smallknob("midi_out.channel_1.sensity");
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
                                                    addPToggleButton("midi_out.channel_1.auto_pitch");
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
                                                    create_smallknob("midi_out.channel_2.velocity");
                                                    openVerticalBox("");
                                                    {
                                                        create_smallknob("midi_out.channel_2.volume");
                                                        addCheckButton("midi_out.channel_2.autogain");
                                                    }
                                                    closeBox();
                                                    openVerticalBox("");
                                                    {
                                                        addNumEntry("midi_out.channel_2.channel");
                                                        addNumEntry("midi_out.channel_2.program");
                                                    }
                                                    closeBox();
                                                    create_smallknob("midi_out.channel_2.oktave");
                                                    create_smallknob("midi_out.channel_2.sensity");
                                                }
                                                closeBox();
                                            }
                                            closeBox();
                                            openHorizontalBox("");
                                            {
                                                create_switch_no_caption(sw_switchit, "midi_out.channel_2.on_off");
                                                openHorizontalBox(" ");
                                                {
                                                    addPToggleButton("midi_out.channel_2.auto_pitch");
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
                                                create_smallknob("midi_out.channel_3.velocity");
                                                openVerticalBox("");
                                                {
                                                    create_smallknob("midi_out.channel_3.volume");
                                                    addCheckButton("midi_out.channel_3.autogain");
                                                }
                                                closeBox();
                                                openVerticalBox("");
                                                {
                                                    addNumEntry("midi_out.channel_3.channel");
                                                    addNumEntry("midi_out.channel_3.program");
                                                }
                                                closeBox();
                                                create_smallknob("midi_out.channel_3.oktave");
                                                create_smallknob("midi_out.channel_3.sensity");
                                            }
                                            closeBox();
                                        }
                                        closeBox();
                                        openHorizontalBox("");
                                        {
                                            create_switch_no_caption(sw_switchit, "midi_out.channel_3.on_off");
                                            openHorizontalBox(" ");
                                            {
                                                addPToggleButton("midi_out.channel_3.auto_pitch");
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
                                                create_smallknob("beat_detector.stepper");
                                                create_smallknob("beat_detector.note_off");
                                                create_smallknob("beat_detector.atack_gain");
                                                create_smallknob("beat_detector.beat_gain");
                                            }
                                            closeBox();
                                        }
                                        closeBox();
                                        addStatusDisplay("", &gx_engine::audio.midistat);
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
			openVerticalBox("");
            {
			//----- add the controlers for feedback feedforward to the bottob box
                create_hslider("amp.feedback"," feedback");
            }
			closeBox();
            openVerticalBox("");
            {
                create_hslider("amp.feedforward"," feedforward");
			}
			closeBox();
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
	// add a Patch Info widget
	openPatchInfoBox(&gx_gui::show_patch_info);

	//debug_check(all_midi_params_assigned);
}

}
