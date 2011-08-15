/*
 * Copyright (C) 2009, 2010 Hermann Meyer, James Warden, Andreas Degert
 * Copyright (C) 2011 Pete Shorthose
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
* ---------------------------------------------------------------------------
*
*    This file is a part ofthe gx_head interface builder
*    and build the mono effect rack,
*    it's a part of the class GxMainInterface
*
* ----------------------------------------------------------------------------
*/

#include "guitarix.h"        // NOLINT

#include <glibmm/i18n.h>     // NOLINT

// -------- the gx_head user interface build instruktions

namespace gx_gui {

void GxMainInterface::gx_build_mono_rack() {
    /** This is the fixed box on top of the mono rack, it include fixed effect modules
     * witch can't move (make no sense to move them arround). Right now it is the noisegate,
     * and the noisesharper, witch are fixed at the beginning of the process callback, and the
     * mono level out and the clipper, witch are fixed at the end of the mono callback.
     **/
    openHorizontalTableBox("");
    {
        openVerticalBox("");
        {
            openPaintBox("");
            {
                openVerticalBox(" noise gate      ");
                {
                    openHorizontalBox("");
                    {
                        create_switch_no_caption(sw_switchit, "noise_gate.on_off");
                        openpaintampBox("noise gate");
                        {
                            create_wheel("noise_gate.threshold");
                        }
                        closeBox();
                    }
                    closeBox();
                }
                closeBox();

                openVerticalBox(_("noise shaper       "));
                {
                    openHorizontalBox("");
                    {
                        create_switch_no_caption(sw_switchit, "shaper.on_off");

                        openpaintampBox("shaper");
                        {
                            create_wheel("shaper.sharper");
                        }
                        closeBox();
                    }
                    closeBox();
                }
                closeBox();

                openVerticalBox(_("mono level out       "));
                {
                    openHorizontalBox("");
                    {
                        create_switch_no_caption(sw_switchit, "amp.on_off");

                        openpaintampBox("level");
                        {
                            create_spin_value("amp.out_amp");
                            create_wheel("amp.out_amp");
                        }
                        closeBox();
                    }
                    closeBox();
                }
                closeBox();

                openVerticalBox(_("clip       "));
                {
                    openHorizontalBox("");
                    {
                        create_switch_no_caption(sw_switchit, "amp.clip.on_off");

                        openpaintampBox("level");
                        {
                            create_wheel("amp.fuzz");
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

        /** The moveable mono effects. Main box of a mono effect modul is the HorizontalOrderBox
         * witch present the move buttons. Inside the HorizontalOrderBox we need a DialogBox witch
         * register the effect to a counter and insert a menu entry as well a button to the toolbar
         **/
        // low high pass filter
        openHorizontalOrderBox(_("l/h/filter"), &gx_engine::audio.posit[14]);
        {
            openVerticalBox(_("l/h/filter"));
            {
                openHorizontalBox("");
                {
                    openPaintBox1("");
                    {
                        create_switch_no_caption(sw_switchit, "low_highpass.on_off");
                        create_selector("low_highpass.pp");
                    }
                    closeBox();

                    openDialogBox("low_highpass.dialog", "low_highpass.on_off", "RackBox_expose");
                    {
                        openHorizontalBox("");
                        {

                            openHorizontalBox("");
                            {
                                create_small_rackknob("low_high_pass.lhp.high_freq", _("high-pass "));
                                create_small_rackknob("low_high_pass.lhp.low_freq", _(" low-pass "));
                                create_switch_no_caption(sw_switchit, "low_high_pass.lhp.on_off");
                            }
                            closeBox();
                            openSpaceBox("");
                            closeBox();
                            openHorizontalBox("");
                            {
                                create_small_rackknob("low_high_pass.lhc.low_freq", _("low-cut "));
                                create_small_rackknob("low_high_pass.lhc.high_freq", _("high-cut "));
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
        openHorizontalOrderBox(_("EQ"), &gx_engine::audio.posit[10]);
        {
            openVerticalBox(_("EQ"));
            {
                openHorizontalBox("");
                {
                    openPaintBox1("");
                    {
                        create_switch_no_caption(sw_switchit, "eqs.on_off");
                        create_selector("eqs.pp");
                    }
                    closeBox();

                    openDialogBox("eqs.dialog", "eqs.on_off", "RackBox_expose");
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
                                create_small_rackknob("eqs.Qs31_25", "Q");
                                create_small_rackknob("eqs.Qs62_5", "Q");
                                create_small_rackknob("eqs.Qs125", "Q");
                                create_small_rackknob("eqs.Qs250", "Q");
                                create_small_rackknob("eqs.Qs500", "Q");
                                create_small_rackknob("eqs.Qs1k", "Q");
                                create_small_rackknob("eqs.Qs2k", "Q");
                                create_small_rackknob("eqs.Qs4k", "Q");
                                create_small_rackknob("eqs.Qs8k", "Q");
                                create_small_rackknob("eqs.Qs16k", "Q");
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
        // ----- crybaby
        openHorizontalOrderBox(_("crybaby"), &gx_engine::audio.posit[0]);
        {
            openVerticalBox(_("crybaby"));
            {
                openHorizontalBox("");
                {
                    openPaintBox1("");
                    {
                        create_switch_no_caption(sw_switchit, "crybaby.on_off");
                        create_selector("crybaby.pp");
                    }
                    closeBox();

                    openDialogBox("crybaby.dialog", "crybaby.on_off", "RackBox_expose");
                    {
                        openHorizontalBox("");
                        {
                            openSpaceBox("");
                            closeBox();
                            create_selector("crybaby.autowah");
                            openSpaceBox("");
                            closeBox();
                            openSpaceBox("");
                            closeBox();
                            openHorizontalTableBox("");
                            {
                                create_small_rackknobr("crybaby.wah", _("  wah   "));
                                create_small_rackknob("crybaby.level", _("  level  "));
                                create_small_rackknob("crybaby.wet_dry", _("  dry/wet  "));
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
        // ----- distortion
        openHorizontalOrderBox(_("distortion"), &gx_engine::audio.posit[2]);
        {
            openVerticalBox(_("distortion"));
            {
                openHorizontalBox("");
                {
                    openPaintBox1("");
                    {
                        create_switch_no_caption(sw_switchit, "gx_distortion.on_off");
                        create_selector("gx_distortion.pp");
                    }
                    closeBox();

                    openDialogBox("gx_distortion.dialog", "gx_distortion.on_off", "RackBox_expose");
                    {
                        openHorizontalBox("");
                        {
                            openVerticalBox("");
                            {
                                openVerticalBox("");
                                {
                                    openFlipLabelBox(_("  drive "));
                                    {
                                        openHorizontalBox("");
                                        {
                                            create_small_rackknobr("gx_distortion.drive", _("  drive "));
                                            create_small_rackknobr("gx_distortion.low_drive", _(" low "));
                                            create_small_rackknobr("gx_distortion.middle_l_drive", _(" middle l. "));
                                            create_small_rackknobr("gx_distortion.middle_h_drive", _(" middle h. "));
                                            create_small_rackknobr("gx_distortion.high_drive", _(" high "));
                                        }
                                        closeBox();
                                    }
                                    closeBox();
                                    openFlipLabelBox(_("  gain  "));
                                    {
                                        openHorizontalBox("");
                                        {
                                            create_small_rackknob("gx_distortion.gain", _("  gain  "));
                                            create_small_rackknob("gx_distortion.low_gain", _(" low "));
                                            create_small_rackknob("gx_distortion.middle_l_gain", _(" middle l. "));
                                            create_small_rackknob("gx_distortion.middle_h_gain", _(" middle h. "));
                                            create_small_rackknob("gx_distortion.high_gain", _(" high "));
                                        }
                                        closeBox();
                                    }
                                    closeBox();
                                }
                                closeBox();

                                openHorizontalBox("");
                                {
                                    create_small_rackknob("gx_distortion.wet_dry", _("dry/wet"));
                                    create_small_rackknob("gx_distortion.level", _("  level  "));
                                    openVerticalBox(_("frequency split Hz"));
                                    {
                                        openpaintampBox("");
                                        {
                                            openHorizontalBox("");
                                            {
                                                openSpaceBox("");
                                                closeBox();
                                                create_wheel("gx_distortion.split_low_freq", _("split low freq"));
                                                openSpaceBox("");
                                                closeBox();
                                                create_wheel("gx_distortion.split_middle_freq", _("split m. freq"));
                                                openSpaceBox("");
                                                closeBox();
                                                create_wheel("gx_distortion.split_high_freq", _("split high freq"));
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

                            openVerticalBox(_("resonator"));
                            {
                                create_small_rackknob("gx_distortion.trigger", _("trigger "));
                                create_small_rackknob("gx_distortion.vibrato", _(" vibrato "));
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
        // ----- IR
        openHorizontalOrderBox(_("IR"), &gx_engine::audio.posit[4]);
        {
            openVerticalBox(_("IR"));
            {
                openHorizontalBox("");
                {
                    openPaintBox1("");
                    {
                        create_switch_no_caption(sw_switchit, "IR.on_off");
                        create_selector("IR.pp");
                    }
                    closeBox();

                    openDialogBox("IR.dialog", "IR.on_off", "RackBox_expose");
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
                                    create_small_rackknob("IR.freq", _(" freq "));
                                    create_small_rackknob("IR.peak", _(" peak "));
                                    create_small_rackknob("IR.bandwidth", _(" bandwidth "));
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
        // ----- the compressor
        openHorizontalOrderBox(_("Compr."), &gx_engine::audio.posit[5]);
        {
            openVerticalBox(_("Compr."));
            {
                openHorizontalBox("");
                {
                    openPaintBox1("");
                    {
                        create_switch_no_caption(sw_switchit, "compressor.on_off");
                        create_selector("compressor.pp");
                    }
                    closeBox();

                    openDialogBox("compressor.dialog", "compressor.on_off", "RackBox_expose");
                    {
                        openHorizontalTableBox("");
                        {
                            create_small_rackknob("compressor.knee", _("knee"));
                            create_small_rackknobr("compressor.ratio", _("ratio"));
                            create_small_rackknob("compressor.threshold", _("threshold"));


                            create_small_rackknob("compressor.attack", _("attack"));
                            create_small_rackknob("compressor.release", _("release"));
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
        // -----overdrive
        openHorizontalOrderBox(_("overdrive"), &gx_engine::audio.posit[1]);
        {
            openVerticalBox(_("overdrive"));
            {
                openHorizontalBox("");
                {
                    openPaintBox1("");
                    {
                        create_switch_no_caption(sw_switchit, "overdrive.on_off");
                        create_selector("overdrive.pp");
                    }
                    closeBox();

                    openDialogBox("overdrive.dialog", "overdrive.on_off", "RackBox_expose");
                    {
                        openHorizontalTableBox("");
                        {
                            openSpaceBox("");
                            closeBox();
                            create_small_rackknobr("overdrive.drive", _("  drive "));
                            create_small_rackknob("overdrive.wet_dry", _("dry/wet"));
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
        // ----- echo
        openHorizontalOrderBox(_("echo"), &gx_engine::audio.posit[6]);
        {
            openVerticalBox(_("echo"));
            {
                openHorizontalBox("");
                {
                    openPaintBox1("");
                    {
                        create_switch_no_caption(sw_switchit, "echo.on_off");
                        create_selector("echo.pp");
                    }
                    closeBox();

                    openDialogBox("echo.dialog", "echo.on_off", "RackBox_expose");
                    {
                        openVerticalBox("");
                        {
                            openHorizontalTableBox("");
                            {
                                create_small_rackknobr("echo.time", _("  time  "));

                                create_small_rackknob("echo.percent", _("    %    "));
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
        // -----delay
        openHorizontalOrderBox(_("delay"), &gx_engine::audio.posit[7]);
        {
            openVerticalBox(_("delay"));
            {
                openHorizontalBox("");
                {
                    openPaintBox1("");
                    {
                        create_switch_no_caption(sw_switchit, "delay.on_off");
                        create_selector("delay.pp");
                    }
                    closeBox();

                    openDialogBox("delay.dialog", "delay.on_off", "RackBox_expose");
                    {
                        openVerticalBox("");
                        {
                            openHorizontalTableBox("");
                            {
                                create_small_rackknobr("delay.delay", _(" delay "));

                                create_small_rackknob("delay.gain", _("  gain "));
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
        // ----- freeverb
        openHorizontalOrderBox(_("freeverb"), &gx_engine::audio.posit[3]);
        {
            openVerticalBox(_("freeverb"));
            {
                openHorizontalBox("");
                {
                    openPaintBox1("");
                    {
                        create_switch_no_caption(sw_switchit, "freeverb.on_off");
                        create_selector("freeverb.pp");
                    }
                    closeBox();
                    openDialogBox("freeverb.dialog", "freeverb.on_off", "RackBox_expose");
                    {
                        openFrameBox("");
                        closeBox();
                        openFrameBox("");
                        closeBox();
                        openHorizontalTableBox("");
                        {
                            create_small_rackknobr("freeverb.RoomSize", _("RoomSize"));
                            create_small_rackknob("freeverb.damp", _("damp"));
                            create_small_rackknob("freeverb.wet_dry", _("dry/wet"));
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

        // -----osc
        openHorizontalOrderBox(_("oscilloscope"), &gx_engine::audio.posit[17]);
        {
            openVerticalBox(_("osc"));
            {
                openHorizontalBox("");
                {
                    openPaintBox1("");
                    {
                        create_switch_no_caption(sw_switchit, "oscilloscope.on_off");
                        create_selector("oscilloscope.pp");
                    }
                    closeBox();

                    openDialogBox("oscilloscope.dialog", "oscilloscope.on_off", "RackBox_expose");
                    {
                        openVerticalBox("");
                        {
                            openFrameBox("");
                            closeBox();
                            openHorizontalBox("");
                            {
                                openFrameBox("");
                                closeBox();
                                addLiveWaveDisplay(" ", &gx_engine::audio.viv , &gx_engine::audio.vivi);
                                openFrameBox("");
                                closeBox();
                            }
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
        }
        closeBox();

        openHorizontalOrderBox(_("biquad"), &gx_engine::audio.posit[18]);
        {
            openVerticalBox(_("biquad"));
            {
                openHorizontalBox("");
                {
                    openPaintBox1("");
                    {
                        create_switch_no_caption(sw_switchit, "biquad.on_off");
                        create_selector("biquad.pp");
                    }
                    closeBox();

                    openDialogBox("biquad.dialog", "biquad.on_off", "RackBox_expose");
                    {
                        openVerticalBox("");
                        {
                            openHorizontalBox("");
                            {
                                create_small_rackknobr("biquad.Freq", _("Freq"));
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

        openHorizontalOrderBox(_("tremolo"), &gx_engine::audio.posit[21]);
        {
            openVerticalBox(_("tremolo"));
            {
                openHorizontalBox("");
                {
                    openPaintBox1("");
                    {
                        create_switch_no_caption(sw_switchit, "tremolo.on_off");
                        create_selector("tremolo.pp");
                    }
                    closeBox();

                    openDialogBox("tremolo.dialog", "tremolo.on_off", "RackBox_expose");
                    {
                        openVerticalBox("");
                        {
                            openHorizontalBox("");
                            {
                                openSpaceBox("");
                                closeBox();
                                create_selector("tremolo.SINE");
                                openSpaceBox("");
                                closeBox();
                                openSpaceBox("");
                                closeBox();
                                openHorizontalTableBox("");
                                {
                                    create_small_rackknobr("tremolo.freq", _("Freq"));
                                    openSpaceBox("");
                                    closeBox();
                                    create_small_rackknobr("tremolo.depth", _("Depth"));
                                    openSpaceBox("");
                                    closeBox();
                                    create_small_rackknob("tremolo.wet_dry", _("dry/wet"));
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

        openHorizontalOrderBox(_("phaser"), &gx_engine::audio.posit[22]);
        {
            openVerticalBox(_("phaser"));
            {
                openHorizontalBox("");
                {
                    openPaintBox1("");
                    {
                        create_switch_no_caption(sw_switchit, "phaser_mono.on_off");
                        create_selector("phaser_mono.pp");
                    }
                    closeBox();

                    openDialogBox("phaser_mono.dialog", "phaser_mono.on_off", "RackBox_expose");
                    {
                        openVerticalBox("");
                        {
                            openHorizontalBox("");
                            {
                                create_small_rackknobr("phaser_mono.level", _("level"));
                                create_small_rackknob("phaser_mono.Speed", _("speed"));
                                create_small_rackknob("phaser_mono.wet_dry", _("dry/wet"));
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

        openHorizontalOrderBox(_("chorus"), &gx_engine::audio.posit[23]);
        {
            openVerticalBox(_("chorus"));
            {
                openHorizontalBox("");
                {
                    openPaintBox1("");
                    {
                        create_switch_no_caption(sw_switchit, "chorus_mono.on_off");
                        create_selector("chorus_mono.pp");
                    }
                    closeBox();

                    openDialogBox("chorus_mono.dialog", "chorus_mono.on_off", "RackBox_expose");
                    {
                        openVerticalBox("");
                        {
                            openHorizontalBox("");
                            {
                                create_small_rackknobr("chorus_mono.level", _("level"));
                                create_small_rackknob("chorus_mono.freq", _("speed"));
                                create_small_rackknob("chorus_mono.wet_dry", _("dry/wet"));
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

        openHorizontalOrderBox(_("flanger"), &gx_engine::audio.posit[24]);
        {
            openVerticalBox(_("flanger"));
            {
                openHorizontalBox("");
                {
                    openPaintBox1("");
                    {
                        create_switch_no_caption(sw_switchit, "flanger_mono.on_off");
                        create_selector("flanger_mono.pp");
                    }
                    closeBox();

                    openDialogBox("flanger_mono.dialog", "flanger_mono.on_off", "RackBox_expose");
                    {
                        openVerticalBox("");
                        {
                            openHorizontalBox("");
                            {
                                create_small_rackknobr("flanger_mono.level", _("level"));
                                create_small_rackknob("flanger_mono.freq", _("speed"));
                                create_small_rackknob("flanger_mono.wet_dry", _("dry/wet"));
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

        openHorizontalOrderBox(_("feedback"), &gx_engine::audio.posit[25]);
        {
            openVerticalBox(_("feedback"));
            {
                openHorizontalBox("");
                {
                    openPaintBox1("");
                    {
                        create_switch_no_caption(sw_switchit, "feedback.on_off");
                        create_selector("feedback.pp");
                    }
                    closeBox();

                    openDialogBox("feedback.dialog", "feedback.on_off", "RackBox_expose");
                    {
                        openVerticalBox("");
                        {
                            openHorizontalBox("");
                            {
                                create_small_rackknobr("feedback.feedback",  _("feedback"));
                                create_small_rackknob("feedback.wet_dry",  _("dry/wet"));
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

        openHorizontalOrderBox(_("tonestack"), &gx_engine::audio.posit[26]);
        {
            openVerticalBox(_("tonestack"));
            {
                openHorizontalBox("");
                {
                    openPaintBox1("");
                    {
                        create_switch_no_caption(sw_switchit, "amp.tonestack.on_off");
                        create_selector("amp.tonestack.pp");
                    }
                    closeBox();

                    openDialogBox("amp.tonestack.dialog", "amp.tonestack.on_off", "RackBox_expose");
                    {
                        openVerticalBox("");
                        {
                            openHorizontalBox("");
                            {
                                create_selector("amp.tonestack.select");

                                create_small_rackknob("amp.tonestack.Bass", _("bass"));

                                create_small_rackknob("amp.tonestack.Middle", _("middle"));

                                create_small_rackknob("amp.tonestack.Treble", _("treble"));
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

        openHorizontalOrderBox(_("cabinet"), &gx_engine::audio.posit[27]);
        {
            openVerticalBox(_("cabinet"));
            {
                openHorizontalBox("");
                {
                    openPaintBox1("");
                    {
                        create_switch_no_caption(sw_switchit, "cab.on_off");
                        create_selector("cab.pp");
                    }
                    closeBox();

                    openDialogBox("cab.dialog", "cab.on_off", "RackBox_expose");
                    {
                        openVerticalBox("");
                        {
                            openHorizontalBox("");
                            {
                                create_selector("cab.select");
                                create_small_rackknob("cab.bass", "bass");
                                create_small_rackknob("cab.treble", "treble");
                                create_small_rackknobr("cab.Level", "level");
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

        openVerticalMidiBox(_("  MIDI out  "));
        {
            openHorizontalBox("");
            {
                openVerticalBox(_("  MIDI out  "));
                {
                    create_switch_no_caption(sw_switchit, "midi_out.on_off");
                    openFrameBox("");
                    closeBox();
                    openHorizontalBox("");
                    {
                        openFrameBox("");
                        closeBox();
                        openPaintBox2("gree_box");
                        {
                            create_switch_no_caption(sw_led, "midi_out.midistat");
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
                // ----- create the midi settings dialog
                openVerticalBox("");
                {
                    openTabBox("");
                    {
                        openVerticalBox(_("channel1"));
                        {
                            openpaintampBox("MIDI OUT");
                            {
                                openVerticalBox("");
                                {
                                    openHorizontalBox("");
                                    {
                                        create_small_rackknob("midi_out.channel_1.velocity", _("velocity"));
                                        openVerticalBox("");
                                        {
                                            openPaintBox2("dark_box");
                                            {
                                                create_small_rackknob("midi_out.channel_1.volume", _("volume"));
                                            }
                                            closeBox();
                                            addCheckButton("midi_out.channel_1.autogain", _("autogain"));
                                        }
                                        closeBox();
                                        openVerticalBox("");
                                        {
                                            addNumEntry("midi_out.channel_1.channel", _("channel"));
                                            addNumEntry("midi_out.channel_1.program", _("program"));
                                        }
                                        closeBox();
                                        create_small_rackknob("midi_out.channel_1.oktave", _("oktave"));
                                        create_small_rackknob("midi_out.channel_1.sensity", _("sensity"));
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
                                            openPaintBox2("darker_box");
                                            {
                                                create_switch_no_caption(sw_led, "midi_out.midistat1");
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
                                            addMToggleButton("midi_out.channel_1.auto_pitch", _("auto_pitch"));
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

                        openVerticalBox(_("channel2"));
                        {
                            openpaintampBox("MIDI OUT");
                            {
                                openVerticalBox("");
                                {
                                    openHorizontalBox("");
                                    {
                                        create_small_rackknob("midi_out.channel_2.velocity", _("velocity"));
                                        openVerticalBox("");
                                        {
                                            openPaintBox2("dark_box");
                                            {
                                                create_small_rackknob("midi_out.channel_2.volume", _("volume"));
                                            }
                                            closeBox();
                                            addCheckButton("midi_out.channel_2.autogain", _("autogain"));
                                        }
                                        closeBox();
                                        openVerticalBox("");
                                        {
                                            addNumEntry("midi_out.channel_2.channel", _("channel"));
                                            addNumEntry("midi_out.channel_2.program", _("program"));
                                        }
                                        closeBox();
                                        create_small_rackknob("midi_out.channel_2.oktave", _("oktave"));
                                        create_small_rackknob("midi_out.channel_2.sensity", _("sensity"));
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
                                            openPaintBox2("darker_box");
                                            {
                                                create_switch_no_caption(sw_led, "midi_out.midistat2");
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
                                            addMToggleButton("midi_out.channel_2.auto_pitch", _("auto_pitch"));
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

                        openVerticalBox(_("channel3"));
                        {
                            openpaintampBox("MIDI OUT");
                            {
                                openVerticalBox("");
                                {
                                    openHorizontalBox("");
                                    {
                                        create_small_rackknob("midi_out.channel_3.velocity", _("velocity"));
                                        openVerticalBox("");
                                        {
                                            openPaintBox2("dark_box");
                                            {
                                                create_small_rackknob("midi_out.channel_3.volume", _("volume"));
                                            }
                                            closeBox();
                                            addCheckButton("midi_out.channel_3.autogain", _("autogain"));
                                        }
                                        closeBox();
                                        openVerticalBox("");
                                        {
                                            addNumEntry("midi_out.channel_3.channel", _("channel"));
                                            addNumEntry("midi_out.channel_3.program", _("program"));
                                        }
                                        closeBox();
                                        create_small_rackknob("midi_out.channel_3.oktave", _("oktave"));
                                        create_small_rackknob("midi_out.channel_3.sensity", _("sensity"));
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
                                            openPaintBox2("darker_box");
                                            {
                                                create_switch_no_caption(sw_led, "midi_out.midistat3");
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
                                            addMToggleButton("midi_out.channel_3.auto_pitch", _("auto_pitch"));
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

                        openVerticalBox(_("beat_detector"));
                        {
                            openpaintampBox("MIDI OUT");
                            {
                                openVerticalBox("");
                                {

                                    openHorizontalBox("");
                                    {
                                        create_small_rackknob("beat_detector.stepper", _("stepper"));
                                        create_small_rackknob("beat_detector.note_off", _("note_off"));
                                        create_small_rackknob("beat_detector.atack_gain", _("atack_gain"));
                                        create_small_rackknob("beat_detector.beat_gain", _("beat_gain"));
                                    }
                                    closeBox();
                                    addStatusDisplay("", &gx_engine::audio.midistat);
                                    openHorizontalBox("");
                                    {
                                        openFrameBox("");
                                        closeBox();
                                        openPaintBox2("darker_box");
                                        {
                                            create_switch_no_caption(sw_led, "midi_out.midistat1");
                                        }
                                        closeBox();
                                        openFrameBox("");
                                        closeBox();
                                        openPaintBox2("darker_box");
                                        {
                                            create_switch_no_caption(sw_led, "midi_out.midistat2");
                                        }
                                        closeBox();
                                        openFrameBox("");
                                        closeBox();
                                        openPaintBox2("darker_box");
                                        {
                                            create_switch_no_caption(sw_led, "midi_out.midistat3");
                                        }
                                        closeBox();
                                        openFrameBox("");
                                        closeBox();
                                    }
                                    closeBox();

                                    openVerticalBox(_("Midi gain"));
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
}  // close mono rack
} // end namespace gx_gui

