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
*    and build the stereo effect rack,
*    it's a part of the class GxMainInterface
*
* ----------------------------------------------------------------------------
*/


#include "guitarix.h"         // NOLINT

#include <glibmm/i18n.h>      // NOLINT

// -------- the gx_head user interface build instruktions

namespace gx_gui {

void StackBoxBuilder::make_rackbox_chorus() {
    // ----- chorus
    openHorizontalhideBox("");
    create_master_slider("chorus.level", _("level"));
    closeBox();
    openHorizontalBox("");
    {
	create_small_rackknobr("chorus.level", _("  level  "));
	create_small_rackknob("chorus.delay", _("  delay  "));
	create_small_rackknob("chorus.depth", _("  depth  "));
	create_small_rackknob("chorus.freq", _("  freq  "));
    }
    closeBox();
}

void StackBoxBuilder::make_rackbox_flanger() {
    // flanger
    openHorizontalhideBox("");
    create_master_slider("flanger.level", _("level"));
    closeBox();
    openHorizontalBox("");
    {
	openHorizontalBox("");
	{
	    create_small_rackknobr("flanger.level", _("  level  "));
	}
	closeBox();
	openVerticalBox("");
	{
	    openHorizontalBox("");
	    {
		create_small_rackknob("flanger.feedback gain", _(" feedback "));
		create_small_rackknob("flanger.depth", _("  depth  "));
		create_small_rackknob("flanger.flange delay", _("  delay  "));
		create_small_rackknob("flanger.flange delay offset", _(" delay offset"));
		create_small_rackknob("flanger.LFO freq", _(" LFO "));
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
	    openFrameBox("");
	    closeBox();
	}
	closeBox();
    }
    closeBox();
}

void StackBoxBuilder::make_rackbox_phaser() {
    // phaser
    openHorizontalhideBox("");
    create_master_slider("phaser.level", _("level"));
    closeBox();
    openHorizontalBox("");
    {
	openHorizontalBox("");
	{
	    create_small_rackknobr("phaser.level", _("  level "));
	}
	closeBox();
	openVerticalBox("");
	{
	    openHorizontalBox("");
	    {
		create_small_rackknob("phaser.feedback gain", _(" feedback "));
		create_small_rackknob("phaser.depth", _("depth"));
		create_small_rackknob("phaser.Notch width", _("width"));
		create_small_rackknob("phaser.NotchFreq", _("freq"));
		create_small_rackknob("phaser.MaxNotch1Freq", _("max Hz"));
		create_small_rackknob("phaser.MinNotch1Freq", _("min Hz"));
		create_small_rackknob("phaser.Speed", _("speed"));
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
	    openFrameBox("");
	    closeBox();
	}
	closeBox();
    }
    closeBox();
}

void StackBoxBuilder::make_rackbox_stereodelay() {
    // stereo delay
    openHorizontalhideBox("");
    closeBox();
    openHorizontalBox("");
    {
	create_small_rackknob("stereodelay.l_gain", _("left gain"));
	create_small_rackknob("stereodelay.l_delay", _("left delay"));
	openVerticalBox("");
	{
	    create_small_rackknobr("stereodelay.LFO freq", _("LFO"));
	    openSpaceBox("");
	    closeBox();
	    create_selector("stereodelay.invert");
	    openFrameBox("");
	    closeBox();
	}
	closeBox();
	create_small_rackknob("stereodelay.r_gain", _("right gain"));
	create_small_rackknob("stereodelay.r_delay", _("right delay"));
    }
    closeBox();
}

void StackBoxBuilder::make_rackbox_stereoecho() {
    // echo
    openHorizontalhideBox("");
    closeBox();
    openHorizontalBox("");
    {
        openVerticalBox("");
	{
	    create_small_rackknob("stereoecho.percent_l", _("left %"));
	    openSpaceBox("");
	    closeBox();
        }
	closeBox();
        openVerticalBox("");
	{
	    create_small_rackknob("stereoecho.time_l", _("left time"));
	    openSpaceBox("");
	    closeBox();
        }
	closeBox();
        openVerticalBox("");
	{
	    create_small_rackknobr("stereoecho.LFO freq", _("LFO"));
	    openSpaceBox("");
	    closeBox();
	    create_selector("stereoecho.invert");
	    openFrameBox("");
	    closeBox();
	}
	closeBox();
        openVerticalBox("");
	{
	    create_small_rackknob("stereoecho.percent_r", _("right %"));
	    openSpaceBox("");
	    closeBox();
        }
	closeBox();
        openVerticalBox("");
	{
	    create_small_rackknob("stereoecho.time_r", _("right time"));
	    openSpaceBox("");
	    closeBox();
        }
	closeBox();
    }
    closeBox();
}

void StackBoxBuilder::make_rackbox_moog() {
    // moog filter
    openHorizontalhideBox("");
    create_master_slider("moog.Q", _("Q"));
    closeBox();
    openHorizontalTableBox("");
    {
	create_small_rackknob("moog.Q", _("            Q            "));
	create_small_rackknob("moog.fr", _("            Hz           "));
    }
    closeBox();
}

void StackBoxBuilder::make_rackbox_ampmodul() {
    // postamp
    openHorizontalhideBox("");
    create_master_slider("ampmodul.level", _("level"));
    closeBox();
    openHorizontalBox("");
    {
	openSpaceBox("");
	closeBox();
	create_small_rackknobr("ampmodul.feedbac", _("dry/feedback  "));
	create_small_rackknob("ampmodul.wet_dry", _("dry/wet"));
	create_small_rackknob("ampmodul.level", _("level"));
	create_small_rackknob("ampmodul.amp2.stage1.tube1", _("tube1"));
	create_small_rackknob("ampmodul.amp2.stage2.tube2", _("tube2"));
	create_small_rackknobr("ampmodul.feedback", _("  wet/feedback"));
	openSpaceBox("");
	closeBox();
    }
    closeBox();
}

void StackBoxBuilder::make_rackbox_tonemodul() {
    // 3 band eq
    openHorizontalhideBox("");
    closeBox();
    openHorizontalBox("");
    {
	create_small_rackknob("tonemodul.Bass", _("bass"));
	create_small_rackknob("tonemodul.Middle", _("middle"));
	create_small_rackknob("tonemodul.Treble", _("treble"));
	openSpaceBox("");
	closeBox();
	create_switch_no_caption(sw_switchit, "tonemodul.ON");
	create_small_rackknob("tonemodul.sharper", _("sharp"));
    }
    closeBox();
}

void StackBoxBuilder::make_rackbox_jconv() {
    static gx_jconv::IRWindow *irw = gx_jconv::IRWindow::create(ui, engine.stereo_convolver, window_icon, gx_settings, accels, 2);
    openHorizontalhideBox("");
    {
	create_master_slider("jconv.gain", _("gain"));
	openSpaceBox("");
	closeBox();
	openSpaceBox("");
	closeBox();
	addSmallJConvFavButton(_("setup"), irw);
    }
    closeBox();
    openHorizontalBox("");
    {
	openVerticalBox("");
	{
	    openSetLabelBox();
	    {
	    }
	    closeBox();
	    openHorizontalBox("");
	    {
		openSpaceBox("");
		closeBox();
		openSpaceBox("");
		closeBox();
		create_small_rackknobr("jconv.gain", _("gain"));
		openSpaceBox("");
		closeBox();
		create_small_rackknob("jconv.diff_delay", _("delta delay"));
		openSpaceBox("");
		closeBox();
		create_small_rackknob("jconv.balance", _("balance"));
		openSpaceBox("");
		closeBox();
		create_small_rackknobr("jconv.wet_dry", _("dry/wet"));
		openSpaceBox("");
		closeBox();
		addJConvButton(_("setup"), irw);
		openSpaceBox("");
		closeBox();
	    }
	    closeBox();
	}
	closeBox();
    }
    closeBox();
}

void StackBoxBuilder::make_rackbox_stereoverb() {
    //stereoverb
    openHorizontalhideBox("");
    create_master_slider("stereoverb.RoomSize", _("RoomSize"));
    closeBox();
    openHorizontalBox("");
    {
        openVerticalBox("");
	{
	    create_small_rackknobr("stereoverb.RoomSize", _("RoomSize"));
	    openSpaceBox("");
	    closeBox();
        }
        closeBox();
        openVerticalBox("");
	{
	    create_small_rackknob("stereoverb.damp", _("damp"));
	    openSpaceBox("");
	    closeBox();
        }
        closeBox();
        openVerticalBox("");
	{
	    create_small_rackknob("stereoverb.wet_dry", _("dry/wet"));
	    openSpaceBox("");
	    closeBox();
        }
        closeBox();
        openVerticalBox("");
	{
	    create_small_rackknobr("stereoverb.LFO freq", _("LFO"));
	    openSpaceBox("");
	    closeBox();
	    create_selector("stereoverb.invert");
	    openFrameBox("");
	    closeBox();
	}
        closeBox();
    }
    closeBox();
}

}  // end namespace gx_gui
