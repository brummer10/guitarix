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
#include <errno.h>

#include <assert.h>
#include <cstring>
#include <list>
#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <cstdio>

#include <array>
#include <zita-convolver.h>
#include <fftw3.h>
#include <zita-resampler.h>

#include <cassert>
#include <sigc++/sigc++.h>
#include <semaphore.h>

using namespace std;

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <jack/jack.h>
#include <sndfile.h>

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
						addNumDisplay("", &gx_engine::audio.fConsta1t);
					}
					closeBox();

					//----- the balance widget
					openVerticalBox("");
					{
						addslider("amp.balance", "balance");
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
										openDialogBox("jconv", &gx_engine::audio.fdialogboxj,(int*)&gx_jconv::GxJConvSettings::checkbutton7);
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
                                                            addbigregler("jconv.left_gain","     left gain     ");
                                                            addregler("jconv.left_delay"," left delay ");
                                                            addbigregler("jconv.right_gain"," right gain ");
                                                            addregler("jconv.right_delay"," right delay ");
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
										addslider("jconv.wet_dry");
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
                                    const char* labels[2]  ={"fixed","scale"};
                                    addselector("eqt.onetwo",2,labels,"");
                                    openHorizontalBox("");
                                    {
                                        openSpaceBox("");
                                        closeBox();
                                        addminiswitch("eq.on_off", "EQ");
                                        openVerticalSwitchBox(" ",0, 1, &gx_engine::audio.witcheq);
                                        {

                                            openDialogBox("eq", &gx_engine::audio.fdialogbox_eq,  &gx_engine::audio.feq);
                                            {
                                                openPlugBox("");
                                                {
                                                    openVerticalBox("");
                                                    {
                                                        openHorizontalTableBox("");
                                                        {
                                                            addVerticalSlider("eq.f31_25","31,25");
                                                            addVerticalSlider("eq.f62_5"," 62,5");
                                                            addVerticalSlider("eq.f125"," 125 ");
                                                            addVerticalSlider("eq.f250"," 250 ");
                                                            addVerticalSlider("eq.f500"," 500 ");
                                                            addVerticalSlider("eq.f1k","  1k  ");
                                                            addVerticalSlider("eq.f2k","  2k  ");
                                                            addVerticalSlider("eq.f4k","  4k  ");
                                                            addVerticalSlider("eq.f8k","  8k  ");
                                                            addVerticalSlider("eq.f16k"," 16k ");
                                                        }
                                                        closeBox();
                                                        openHorizontalTableBox("");
                                                        {
                                                            addregler("eq.Q31_25","    Q    ");
                                                            addregler("eq.Q62_5","Q");
                                                            addregler("eq.Q125","Q");
                                                            addregler("eq.Q250","Q");
                                                            addregler("eq.Q500","Q");
                                                            addregler("eq.Q1k","Q");
                                                            addregler("eq.Q2k","Q");
                                                            addregler("eq.Q4k","Q");
                                                            addregler("eq.Q8k","Q");
                                                            addregler("eq.Q16k","Q");
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
                                            openDialogBox("eqs", &gx_engine::audio.fdialogbox_eqs,  &gx_engine::audio.feq);
                                            {
                                                openPlugBox("");
                                                {
                                                    openVerticalBox("");
                                                    {
                                                        openHorizontalTableBox("");
                                                        {
                                                            addSpinValueBox("eqs.freq31_25" ,"");
                                                            addSpinValueBox("eqs.freq62_5" ,"");
                                                            addSpinValueBox("eqs.freq125" ,"");
                                                            addSpinValueBox("eqs.freq250" ,"");
                                                            addSpinValueBox("eqs.freq500" ,"");
                                                            addSpinValueBox("eqs.freq1k" ,"");
                                                            addSpinValueBox("eqs.freq2k" ,"");
                                                            addSpinValueBox("eqs.freq4k" ,"");
                                                            addSpinValueBox("eqs.freq8k" ,"");
                                                            addSpinValueBox("eqs.freq16k" ,"");

                                                         }
                                                        closeBox();
                                                        openHorizontalTableBox("");
                                                        {
                                                            addVerticalSlider("eqs.fs31_25","");
                                                            addVerticalSlider("eqs.fs62_5","");
                                                            addVerticalSlider("eqs.fs125","");
                                                            addVerticalSlider("eqs.fs250","");
                                                            addVerticalSlider("eqs.fs500","");
                                                            addVerticalSlider("eqs.fs1k","");
                                                            addVerticalSlider("eqs.fs2k","");
                                                            addVerticalSlider("eqs.fs4k","");
                                                            addVerticalSlider("eqs.fs8k","");
                                                            addVerticalSlider("eqs.fs16k","");
                                                        }
                                                        closeBox();
                                                        openHorizontalTableBox("");
                                                        {
                                                            addregler("eqs.Qs31_25","    Q    ");
                                                            addregler("eqs.Qs62_5","Q");
                                                            addregler("eqs.Qs125","Q");
                                                            addregler("eqs.Qs250","Q");
                                                            addregler("eqs.Qs500","Q");
                                                            addregler("eqs.Qs1k","Q");
                                                            addregler("eqs.Qs2k","Q");
                                                            addregler("eqs.Qs4k","Q");
                                                            addregler("eqs.Qs8k","Q");
                                                            addregler("eqs.Qs16k","Q");
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
                                        addbigregler("amp.in_level");
                                        openSpaceBox("");
                                        closeBox();
                                        addbigregler("amp.out_master");
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
                                        addregler("amp.tonestack.Bass");
                                        openSpaceBox("");
                                        closeBox();
                                        addregler("amp.tonestack.Middle");
                                        openSpaceBox("");
                                        closeBox();
                                        addregler("amp.tonestack.Treble");
                                        openSpaceBox("");
                                        closeBox();
                                    }
                                    closeBox();
                                    openHorizontalBox("");
                                    {
                                    addminiswitch("amp.bass_boost.on_off", "bass boost  ");
                                    openSpaceBox("");
                                    closeBox();
                                    }
                                    closeBox();
                                    openHorizontalBox("");
                                    {
                                        const char* labels[10]  ={"default","Bassman", "Twin Reverb","Princeton","JCM-800",
                                                                 "JCM-2000", "M-Lead", "M2199", "AC-30", "Off"};
                                        addselector("amp.tonestack.select",10,labels,"");
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
									addswitch("shaper.on_off", "");
									openFrameBox("");
									{
										addHorizontalWheel("shaper.sharper");
									}
									closeBox();
								}
								closeBox();
								openVerticalBox("     noise gate      ");
								{
									addswitch("noise_gate.on_off", "");
									openFrameBox("");
									{
										addHorizontalWheel("noise_gate.threshold"," threshold ");
									}
									closeBox();
								}
								closeBox();
								openVerticalBox("anti aliase");
								{
									addswitch("anti_aliase.on_off", "");
									openFrameBox("");
									{
										addHorizontalWheel("anti_aliase.feedback", " feedback ");
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
                                        const char* labels[2]  ={"amp 1","amp 2"};
                                        addselector("amp.model",2,labels,"");
									}
									closeBox();

									openVerticalBox1("");
									{
									    addminiswitch("amp.oversample.on_off", "oversample  ");
									    const char* labels[8]  ={"  1x","  2x", "  3x","  4x","  5x", "  6x", "  7x", "  8x"};
										addselector("amp.select",8,labels,"");
									}
									closeBox();

									/*openVerticalBox1("");
									{
                                        addminiswitch("amp.bass_boost.on_off", "bass boost  ");
                                        openSpaceBox("");
                                        closeBox();
                                        openVerticalBox1("");
                                        closeBox();
									}
									closeBox();*/

									openVerticalBox1("");
									{
                                        addminiswitch("convolve.on_off", "amp tune    ");
                                        const char* labels[7]  ={"amp 1","amp 2", "amp 3","amp 4","amp 5", "amp 6", "amp 7"};
                                        addselector("convolve.select",7,labels,"");

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
                                            addswitch("preamp.on_off", "preamp");
                                            addHorizontalWheel("preamp.atan");
                                        }
                                        closeBox();
                                        openFrameBox("");
                                        {
                                        }
                                        closeBox();
                                        openVerticalBox("");
                                        {
                                            addswitch("drive.on_off", "drive");
                                            addHorizontalWheel("drive.value", "drive");
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
                                            addswitch("tube.on_off", "tube");
                                            addHorizontalWheel("tube.fuzzy");
                                        }
                                        closeBox();
                                        openFrameBox("");
                                        {
                                        }
                                        closeBox();
                                        openVerticalBox("");
                                        {
                                            addswitch("tube.vibrato.on_off", "vibrato");
                                            addHorizontalWheel("tube.vibrato", "vibrato");
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
                                            addswitch("tube2.on_off", "tube2");
                                            openFrameBox("");
                                            {
                                                addHorizontalWheel("tube2.fuzzy");
                                            }
                                            closeBox();
                                        }
                                        closeBox();
                                        openVerticalBox("");
                                        {
                                            openVerticalBox1("resonanz");
                                            {
                                                addHorizontalWheel("tube2.resonanz", "reso");
                                            }
                                            closeBox();
                                            openVerticalBox1("vibrato");
                                            {
                                                addHorizontalWheel("tube2.vibrato");
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
                                            addswitch("tube3.on_off", "tube3");
                                            openFrameBox("");
                                            {
                                                addHorizontalWheel("tube3.g");
                                            }
                                            closeBox();

                                        }
                                        closeBox();
                                        openVerticalBox("");
                                        {
                                            openVerticalBox1("dist");
                                            {
                                                addHorizontalWheel("tube3.dist", "dist");
                                            }
                                            closeBox();
                                            openVerticalBox1("level");
                                            {
                                                addHorizontalWheel("tube3.q", "level");
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
                                            addswitch("amp2.preamp.ON", "preamp");
                                            openSpaceBox("");
                                            closeBox();
                                            addregler("amp2.preamp.Pregain","");
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
                                            addswitch("amp2.stage1.ON", "tube");
                                            openSpaceBox("");
                                            closeBox();
                                            addregler("amp2.stage1.gain1","");
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
                                            addswitch("amp2.stage2.ON", "tube2");
                                            openSpaceBox("");
                                            closeBox();
                                            addregler("amp2.stage2.gain2","");
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
                                            addswitch("stage3.ON", "tube3");
                                            openSpaceBox("");
                                            closeBox();
                                            addregler("stage3.gain3","");
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
											    openSpaceBox("");
                                                closeBox();
												addregler("compressor.ratio");
												openHorizontalBox("");
												{
													addtoggle("compressor.on_off", "");
													//----- open a dialogbox(toplevel widget) and put the advanced controlls in it
													openDialogBox("compressor", &gx_engine::audio.fdialogbox8, &gx_engine::audio.fcheckboxcom1);
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
                                                                        addregler("compressor.knee");
                                                                        addregler("compressor.ratio");
                                                                        addregler("compressor.threshold");
                                                                    }
                                                                    closeBox();
                                                                    openVerticalBox("envelop");
                                                                    {
                                                                        addslider("compressor.attack");
                                                                        addslider("compressor.release");
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
											    openSpaceBox("");
                                                closeBox();
												addregler("overdrive.drive","  drive ");
												addtoggle("overdrive.on_off", "");
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
											    const char* labels[2]  ={"multi","single"};
                                                addselector("distortiont.onetwo",2,labels,"");
											    //addswitch("distortion.onetwo", "");
											    openVerticalSwitchBox(" ",0, 0, &gx_engine::audio.witchdistortion);
											    {
                                                    addregler("distortion.drive","  drive ");
                                                    openHorizontalBox("");
                                                    {
                                                        addtoggle("distortion.on_off", "");

													//----- open a dialogbox(toplevel widget) and put the advanced controlls in it

                                                            openDialogBox("distortion", &gx_engine::audio.fdialogbox1, &gx_engine::audio.fcheckbox4);
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
                                                                                        addbigregler("distortion.drive","  drive ");
                                                                                        addregler("distortion.level","  level  ");
                                                                                        addregler("distortion.gain","  gain  ");
                                                                                    }
                                                                                    closeBox();
                                                                                    openVerticalBox1("");
                                                                                    {
                                                                                        openHorizontalBox("");
                                                                                        {
                                                                                            openVerticalBox1("");
                                                                                            {
                                                                                                addregler("distortion.low_drive"," low drive ");
                                                                                                addregler("distortion.low_gain"," low gain ");
                                                                                            }
                                                                                            closeBox();
                                                                                            openVerticalBox1("");
                                                                                            {
                                                                                                addregler("distortion.middle_drive"," middle drive ");
                                                                                                addregler("distortion.middle_gain"," middle gain ");
                                                                                            }
                                                                                            closeBox();
                                                                                            openVerticalBox1("");
                                                                                            {
                                                                                                addregler("distortion.high_drive"," high drive ");
                                                                                                addregler("distortion.high_gain"," high gain ");
                                                                                            }
                                                                                            closeBox();
                                                                                        }
                                                                                        closeBox();
                                                                                        openHorizontalBox("");
                                                                                        {
                                                                                            addslider("distortion.split_low_freq", "split low freq");
                                                                                            addslider("distortion.split_high_freq", "split high freq");
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
                                                                                    addregler("distortion.low_highpass.high_freq","high-pass ");
                                                                                    addregler("distortion.low_highpass.low_freq"," low-pass ");
                                                                                    addtoggle("distortion.low_highpass.on_off", "");
                                                                                }
                                                                                closeBox();
                                                                                openVerticalBox("low/highcut");
                                                                                {
                                                                                    addregler("distortion.low_highcutoff.low_freq"," low-cut ");
                                                                                    addregler("distortion.low_highcutoff.high_freq","high-cut ");
                                                                                    addtoggle("distortion.low_highcutoff.on_off","");
                                                                                }
                                                                                closeBox();
                                                                                openVerticalBox("resonator");
                                                                                {
                                                                                    addregler("distortion.trigger","trigger ");
                                                                                    addregler("distortion.vibrato"," vibrato ");
                                                                                    addtoggle("distortion.resonator.on_off","");
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
                                                    addregler("distortion1.drive","  drive ");
                                                    openHorizontalBox("");
                                                    {
                                                        addtoggle("distortion.on_off", "");
                                                        openDialogBox("distortion1", &gx_engine::audio.fdis1, &gx_engine::audio.fcheckbox4);
                                                        {
                                                            openPlugBox("");
                                                            {
                                                                openHandleBox("  ");
                                                                {
                                                                    openHorizontalBox("");
                                                                    {
                                                                        openHorizontalTableBox("");
                                                                        {
                                                                            addbigregler("distortion1.drive","  drive ");
                                                                            addregler("distortion1.level","\n\n level");
                                                                            addregler("distortion1.gain","\n\n gain");
                                                                        }
                                                                        closeBox();
                                                                        openHorizontalTableBox("");
                                                                        {
                                                                            openVerticalBox("low/highpass");
                                                                            {
                                                                                openHorizontalBox("");
                                                                                {
                                                                                    addregler("distortion1.low_highpass.high_freq","high-freq ");
                                                                                    addregler("distortion1.low_highpass.low_freq"," low-freq ");
                                                                                }
                                                                                closeBox();
                                                                                addtoggle("distortion1.low_highpass.on_off", "");
                                                                            }
                                                                            closeBox();
                                                                            openVerticalBox("low/highcutoff");
                                                                            {
                                                                                openHorizontalBox("");
                                                                                {
                                                                                    addregler("distortion1.low_highcutoff.high_freq","high-freq ");
                                                                                    addregler("distortion1.low_highcutoff.low_freq"," low-freq ");
                                                                                }
                                                                                closeBox();

                                                                                addtoggle("distortion1.low_highcutoff.on_off","");
                                                                            }
                                                                            closeBox();
                                                                            openVerticalBox("resonanz");
                                                                            {
                                                                                openHorizontalBox("");
                                                                                {
                                                                                    addregler("distortion1.trigger","trigger ");
                                                                                    addregler("distortion1.vibrato"," vibrato ");
                                                                                }
                                                                                closeBox();
                                                                                addtoggle("distortion1.resonator.on_off","");
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
												    openSpaceBox("");
                                                    closeBox();
													addregler("freeverb.RoomSize");
													openHorizontalBox("");
													{
														addtoggle("freeverb.on_off","");
														//----- open a dialogbox(toplevel widget) and put the advanced controlls in it
														openDialogBox("freeverb", &gx_engine::audio.fdialogbox2, &gx_engine::audio.fcheckbox6);
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
                                                                        addbigregler("freeverb.RoomSize");
                                                                        addregler("freeverb.damp");
                                                                        addregler("freeverb.wet_dry");
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
												    const char* labels[2]  ={"manual","auto"};
                                                    addselector("IR.auto_freq",2,labels,"");
													openHorizontalBox("");
													{
														addregler("IR.freq","   freq   ");
														//addregler("IR.peak"," peak ");
													}
													closeBox();
													openHorizontalBox("");
													{
														addtoggle("", &gx_engine::audio.fcheckbox8);
														//----- open a dialogbox(toplevel widget) and put the advanced controlls in it
														openDialogBox("IR", &gx_engine::audio.fdialogbox3, &gx_engine::audio.fcheckbox8);
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
                                                                                addbigregler("IR.freq","    freq     ");
                                                                                addregler("IR.peak","     peak    ");
                                                                                addregler("IR.bandwidth","    bandwidth    ");
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
                                                                            addselector("IR.auto_freq",2,labels,"");
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
												    const char* labels[2]  ={"manual","auto"};
                                                    addselector("crybaby.autowah",2,labels,"");
												    //addminiswitch("crybaby.autowah"," autowah");
													addregler("crybaby.wah"," wah ");
													openHorizontalBox("");
													{
														addtoggle("", &gx_engine::audio.fcheckbox5);
														//----- open a dialogbox(toplevel widget) and put the advanced controlls in it
														openDialogBox("crybaby", &gx_engine::audio.fdialogbox4, &gx_engine::audio.fcheckbox5);
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
                                                                            addbigregler("crybaby.wah","  wah   ");
                                                                            addregler("crybaby.level","  level  ");
                                                                            addregler("crybaby.wet_dry","wet/dry");
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
                                                                            addselector("crybaby.autowah",2,labels,"");
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
												    openSpaceBox("");
                                                    closeBox();
													openHorizontalBox("");
													{

														addregler("echo.time","  time  ");
													}
													closeBox();
													openHorizontalBox("");
                                                    {
                                                        addtoggle("echo.on_off","");
                                                        openDialogBox("echo", &gx_engine::audio.fdialogbox_echo, (int*)&gx_engine::audio.fcheckbox7);
                                                        {
                                                            openPlugBox("");
															{
                                                                openHandleBox("  ");
                                                                {
                                                                    openVerticalBox("");
                                                                    {
                                                                        openHorizontalBox("");
                                                                        {
                                                                            addregler("echo.time","  time  ");
                                                                            addregler("echo.percent","    %    ");
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
											    openSpaceBox("");
                                                closeBox();
												openHorizontalBox("");
												{
													addregler("delay.delay"," delay ");

												}
												closeBox();
												openHorizontalBox("");
												{
                                                    addtoggle("delay.on_off","");

                                                    openDialogBox("delay", &gx_engine::audio.fdialogbox_delay, (int*)&gx_engine::audio.fdelay);
                                                    {
                                                        openPlugBox("");
                                                        {
                                                            openHandleBox("  ");
                                                            {
                                                                openVerticalBox("");
                                                                {
                                                                    openHorizontalBox("");
                                                                    {
                                                                        addregler("delay.delay"," delay ");
                                                                        addregler("delay.gain","  gain ");
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
											addregler("chorus.level");
											openHorizontalBox("");
											{
												addtoggle("chorus.on_off","");
												openDialogBox("chorus", &gx_engine::audio.fchorusbox, &gx_engine::audio.fchorus);
												{
												    openPlugBox("");
                                                    {
                                                        openHandleBox("  ");
                                                        {
                                                            openVerticalBox("");
                                                            {
                                                                openHorizontalTableBox("");
                                                                {
                                                                    addbigregler("chorus.level","  level  ");
                                                                    addregler("chorus.delay","  delay  ");
                                                                    addregler("chorus.depth","  depth  ");
                                                                    addregler("chorus.freq","  freq  ");
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
										    const char* labels[2]  ={"linear","invert"};
                                            addselector("flanger.invert",2,labels,"");
											addregler("flanger.level");
											openHorizontalBox("");
											{
												addtoggle("flanger.on_off","");
												openDialogBox("flanger", &gx_engine::audio.fflangerbox, &gx_engine::audio.fflanger);
												{
												    openPlugBox("");
                                                    {
                                                        openHandleBox("  ");
                                                        {
                                                            openVerticalBox("");
                                                            {
                                                                openHorizontalTableBox("");
                                                                {
                                                                    addbigregler("flanger.level","  level  ");
                                                                    addregler("flanger.feedback gain"," feedback gain ");
                                                                    addregler("flanger.depth","  depth  ");
                                                                    addregler("flanger.flange delay","  delay  ");
                                                                    addregler("flanger.flange delay offset"," delay offset");
                                                                    addregler("flanger.LFO freq"," LFO freq  ");

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
                                                                    addselector("flanger.invert",2,labels,"");
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


                                                        addregler("SampleLooper.gain"," gain ");

                                                        openHorizontalBox("");
                                                        {
                                                            openSpaceBox("");
                                                            closeBox();
                                                            addminiswitch("SampleLooper.on_off","");

                                                            addRecButton("SampleLooper.Capture","capture ");
                                                            addPlayButton("SampleLooper.Play"," play       ");
                                                            openSpaceBox("");
                                                            closeBox();
                                                        }
                                                        closeBox();
                                                    }
                                                    closeBox();
                                                    //addtoggle("SampleLooper.on_off","");
                                                }
                                                closeBox();
												openPaintBox("");
												{
												    openHorizontalBox("");
                                                    {
                                                        addminieqswitch("biquad.on_off","  BiQuad Filter    ");
                                                        openDialogBox("biquad", &gx_engine::audio.fbiquadbox, (int*)&gx_engine::audio.fbiquad);
                                                        {
                                                            openPlugBox("");
															{
                                                                openHandleBox("  ");
                                                                {
                                                                    openVerticalBox("");
                                                                    {
                                                                        openHorizontalBox("");
                                                                        {
                                                                            addregler("biquad.Freq","                                 Hz                                    ");

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
                                                        addminieqswitch("MultiBandFilter.on_off","  MultiBandFilter");
                                                        openDialogBox("MultiBandFilter", &gx_engine::audio.fdialogbox_mbf, &gx_engine::audio.fmultifilter);
                                                        {
                                                            openPlugBox("");
															{
                                                                openVerticalBox("");
                                                                {
                                                                    openHorizontalTableBox("");
                                                                    {
                                                                        addVerticalSlider("MultiBandFilter.f31_25","31,25");
                                                                        addVerticalSlider("MultiBandFilter.f62_5"," 62,5");
                                                                        addVerticalSlider("MultiBandFilter.f125"," 125 ");
                                                                        addVerticalSlider("MultiBandFilter.f250"," 250 ");
                                                                        addVerticalSlider("MultiBandFilter.f500"," 500 ");
                                                                        addVerticalSlider("MultiBandFilter.f1k","  1k  ");
                                                                        addVerticalSlider("MultiBandFilter.f2k","  2k  ");
                                                                        addVerticalSlider("MultiBandFilter.f4k","  4k  ");
                                                                        addVerticalSlider("MultiBandFilter.f8k","  8k  ");
                                                                        addVerticalSlider("MultiBandFilter.f16k"," 16k ");
                                                                    }
                                                                    closeBox();
                                                                    openHorizontalTableBox("");
                                                                    {
                                                                        addregler("MultiBandFilter.Q31_25","    Q    ");
                                                                        addregler("MultiBandFilter.Q62_5","Q");
                                                                        addregler("MultiBandFilter.Q125","Q");
                                                                        addregler("MultiBandFilter.Q250","Q");
                                                                        addregler("MultiBandFilter.Q500","Q");
                                                                        addregler("MultiBandFilter.Q1k","Q");
                                                                        addregler("MultiBandFilter.Q2k","Q");
                                                                        addregler("MultiBandFilter.Q4k","Q");
                                                                        addregler("MultiBandFilter.Q8k","Q");
                                                                        addregler("MultiBandFilter.Q16k","Q");
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
                                                        addminieqswitch("moog.on_off","  Moog Filter       ");
                                                        openDialogBox("moog", &gx_engine::audio.fdialogbox_moo, (int*)&gx_engine::audio.fmoog);
                                                        {
                                                            openPlugBox("");
															{
                                                                openHandleBox("  ");
                                                                {
                                                                    openVerticalBox("");
                                                                    {
                                                                        openHorizontalBox("");
                                                                        {
                                                                            addregler("moog.Q","            Q            ");
                                                                            addregler("moog.fr","            Hz           ");

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
                                                    addminicabswitch("cab.on_off","  Cab-ImpResp                ");
												}
												closeBox();
												openSlooperBox("limiter");
												{


													addregler("amp.fuzz");

													const char* lab[3] = {"    off","    clip","foldback"};
													addselector("amp.threshold",3,lab);
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
							openDialogBox("midi_out", &gx_engine::audio.fdialogbox6, (int*)&gx_engine::audio.midistat);
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
                                                    addregler("midi_out.channel_1.velocity");
                                                    openVerticalBox("");
                                                    {
                                                        addregler("midi_out.channel_1.volume");
                                                        addCheckButton("midi_out.channel_1.autogain");
                                                    }
                                                    closeBox();
                                                    openVerticalBox("");
                                                    {
                                                        addNumEntry("midi_out.channel_1.channel");
                                                        addNumEntry("midi_out.channel_1.program");
                                                    }
                                                    closeBox();
                                                    addregler("midi_out.channel_1.oktave");
                                                    addregler("midi_out.channel_1.sensity");
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
                                                    addregler("midi_out.channel_2.velocity");
                                                    openVerticalBox("");
                                                    {
                                                        addregler("midi_out.channel_2.volume");
                                                        addCheckButton("midi_out.channel_2.autogain");
                                                    }
                                                    closeBox();
                                                    openVerticalBox("");
                                                    {
                                                        addNumEntry("midi_out.channel_2.channel");
                                                        addNumEntry("midi_out.channel_2.program");
                                                    }
                                                    closeBox();
                                                    addregler("midi_out.channel_2.oktave");
                                                    addregler("midi_out.channel_2.sensity");
                                                }
                                                closeBox();
                                            }
                                            closeBox();
                                            openHorizontalBox("");
                                            {
                                                addtoggle("midi_out.channel_2.on_off", "");
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
                                                addregler("midi_out.channel_3.velocity");
                                                openVerticalBox("");
                                                {
                                                    addregler("midi_out.channel_3.volume");
                                                    addCheckButton("midi_out.channel_3.autogain");
                                                }
                                                closeBox();
                                                openVerticalBox("");
                                                {
                                                    addNumEntry("midi_out.channel_3.channel");
                                                    addNumEntry("midi_out.channel_3.program");
                                                }
                                                closeBox();
                                                addregler("midi_out.channel_3.oktave");
                                                addregler("midi_out.channel_3.sensity");
                                            }
                                            closeBox();
                                        }
                                        closeBox();
                                        openHorizontalBox("");
                                        {
                                            addtoggle("midi_out.channel_3.on_off", "");
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
                                                addregler("beat_detector.stepper");
                                                addregler("beat_detector.note_off");
                                                addregler("beat_detector.atack_gain");
                                                addregler("beat_detector.beat_gain");
                                            }
                                            closeBox();
                                        }
                                        closeBox();
                                        addStatusDisplay("", &gx_engine::audio.midistat);
                                        openVerticalBox("Midi gain");
                                        {
                                            addHorizontalWheel("beat_detector.midi_gain");
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
                addslider("amp.feedback"," feedback");
            }
			closeBox();
            openVerticalBox("");
            {
                addslider("amp.feedforward"," feedforward");
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

	debug_check(all_midi_params_assigned);
}

}
