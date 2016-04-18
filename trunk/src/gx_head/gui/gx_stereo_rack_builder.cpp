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

void StackBoxBuilder::make_rackbox_jconv() {
    static gx_jconv::IRWindow *irw = gx_jconv::IRWindow::create("jconv", window_icon, machine, accels, 2);
    openHorizontalhideBox("");
	create_master_slider("jconv.wet_dry", _("Dry/Wet"));
    openSpaceBox("");
	closeBox();
	openSpaceBox("");
	closeBox();
	addSmallJConvFavButton(C_("Setup", "S"), irw);
    closeBox();
    openVerticalBox("");
    {
	openSetLabelBox();
	{
	}
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
	    create_mid_rackknob("jconv.gain", _("Gain"));
	    create_small_rackknobr("jconv.diff_delay", _("Delta Delay"));
	    create_small_rackknobr("jconv.balance", _("Balance"));
	    create_small_rackknobr("jconv.wet_dry", _("Dry/Wet"));
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
	}
	closeBox();
    }
    closeBox();
}

}  // end namespace gx_gui
