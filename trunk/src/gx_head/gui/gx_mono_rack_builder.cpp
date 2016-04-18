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
*
* ----------------------------------------------------------------------------
*/

#include "guitarix.h"        // NOLINT

#include <glibmm/i18n.h>     // NOLINT

// -------- the gx_head user interface build instruktions

namespace gx_gui {

void StackBoxBuilder::make_rackbox_oscilloscope() {
    // -----osc
    openHorizontalhideBox("");
    closeBox();
    openVerticalBox("");
    {
	openFrameBox("");
	closeBox();
	openHorizontalBox("");
	{
	    openFrameBox("");
	    closeBox();
	    addLiveWaveDisplay(" ");
	    openFrameBox("");
	    closeBox();
	}
	closeBox();
	openFrameBox("");
	closeBox();
    }
    closeBox();
}

void StackBoxBuilder::make_rackbox_jconv_mono() {
    static gx_jconv::IRWindow *irw = gx_jconv::IRWindow::create("jconv_mono", window_icon, machine, accels, 1);
    openHorizontalhideBox("");
        create_master_slider("jconv_mono.wet_dry", _("Dry/Wet"));
        openSpaceBox("");
        closeBox();
        openSpaceBox("");
        closeBox();
        addSmallJConvFavButton(C_("Setup", "S"), irw);
    closeBox();
    openVerticalBox("");
    {
        openSetMonoLabelBox();
        closeBox();
        openSpaceBox("");
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
            create_mid_rackknob("jconv_mono.gain", _("Gain"));
            create_small_rackknobr("jconv_mono.wet_dry", _("Dry/Wet"));
            openVerticalBox("");
                openSpaceBox("");
                closeBox();
                openSpaceBox("");
                closeBox();
                addJConvButton(_("Setup"), irw);
                openSpaceBox("");
                closeBox();
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
            openSpaceBox("");
            closeBox();
        }
        closeBox();
    }
    closeBox();
}

void StackBoxBuilder::make_rackbox_midi_out() {
    openVerticalMidiBox(_("  MIDI out  "));
    {
	openHorizontalhideBox("");
	closeBox();
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

} // end namespace gx_gui
