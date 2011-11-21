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
 *    This is the gx_head interface builder,
 *    it's a part of the class GxMainInterface
 *
 * ----------------------------------------------------------------------------
 */

#include "guitarix.h"      // NOLINT

#include <glibmm/i18n.h>   // NOLINT
#include <gtkmm/menu.h>

// -------- the gx_head user interface build instruktions

namespace gx_gui {

#ifndef NDEBUG
// debug_check
inline void all_midi_params_assigned() {
    for (gx_engine::ParamMap::iterator i = gx_engine::parameter_map.begin(); i != gx_engine::parameter_map.end(); ++i) {
        if (i->second->isControllable() && !i->second->isUsed())
            gx_system::gx_print_error("Debug Check",
                                      "midi-parameter not assigned in ui: " + i->first);
    }
}
#endif

/* -------- user interface builder ---------- */
void GxMainInterface::setup() {

    // ----- the main box, all visible widgets are a child of this box
    openVerticalBox("");

    // ----- add the menubar on top
    {
        openHorizontalBox("");
        {
            openVerticalBox("");
            {

                openToolBar(_("Plugins"));
                {
		    create_ptoggle_button("presets");
                }
                closeBox();
                addNumDisplay();
            }
            closeBox();

            openVerticalBox("");
            {
                openEventBox(" "); // main widget start openMainBox(" ", "main_expose");
                {
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

                        openFlipLabelBox("gx-2    ");
                        {
                            openHorizontalBox("");
                            {
                                openSpaceBox("");
                                closeBox();
                                openSpaceBox("");
                                closeBox();
                                openVerticalBox("");
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
                                    openFrameBox("");
                                    closeBox();
                                    
                                    openHorizontalBox("");
                                    {
                                        create_selector("tube.select", "amp_selector");
                                        openFrameBox("");
                                        closeBox();
                                        openFrameBox("");
                                        closeBox();
                                    }
                                    closeBox();
                                    openHorizontalBox("");
                                    {
                                        openVerticalBox("");
                                        {
                                            create_bigknob("amp2.stage1.Pregain", _("Pre gain"));
                                            openSpaceBox("");
                                            closeBox();
                                            openSpaceBox("");
                                            closeBox();
                                        }
                                        closeBox();
                                        openSpaceBox("");
                                        closeBox();
                                        openVerticalBox("");
                                        {
                                            create_bigknob("gxdistortion.drive", _("  Drive "));
                                            openSpaceBox("");
                                            closeBox();
                                            openSpaceBox("");
                                            closeBox();
                                        }
                                        closeBox();
                                        openSpaceBox("");
                                        closeBox();
                                        openVerticalBox("");
                                        {
                                            create_bigknob("gxdistortion.wet_dry", _(" Clean/Dist "));
                                            openSpaceBox("");
                                            closeBox();
                                            openSpaceBox("");
                                            closeBox();
                                        }
                                        closeBox();
                                        openSpaceBox("");
                                        closeBox();
                                        openVerticalBox("");
                                        {
                                            create_bigknob("amp2.stage2.gain1", _("Master gain"));
                                            openSpaceBox("");
                                            closeBox();
                                            openSpaceBox("");
                                            closeBox();
                                        }
                                        closeBox();
                                    }
                                    closeBox();
                                }
                                closeBox();
                                openSpaceBox("");
                                closeBox();
                                openSpaceBox("");
                                closeBox();
                                

                                openVerticalBox("");
                                {
                                    openSpaceBox("");
                                    closeBox();
                                    openSpaceBox("");
                                    closeBox();
                                    openSpaceBox("");
                                    closeBox();
                                    openFrameBox("");
                                    closeBox();
                                    create_switch(sw_minitoggle, "amp.bass_boost.on_off",
                                                  _(" Bass boost  "), Gtk::POS_RIGHT);
                                    create_wheel("bassbooster.Level");
                                    create_switch(sw_minitoggle, "con.on_off", _(" Presence "),
						  Gtk::POS_RIGHT);
                                    create_wheel("con.Level");
                                    create_switch(sw_minitoggle, "amp.feed_on_off", _(" Reverb  "),
                                                  Gtk::POS_RIGHT);
                                    create_wheel("amp.wet_dry");
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
                                openSpaceBox("");
                                closeBox();
                                openSpaceBox("");
                                closeBox();

                                openSpaceBox("");
                                closeBox();
                                openSpaceBox("");
                                closeBox();
                                openVerticalBox("");
                                {
                                    openSpaceBox("");
                                    closeBox();
                                    openFrameBox("");
                                    closeBox();
                                    openFrameBox("");
                                    closeBox();
                                    openSpaceBox("");
                                    closeBox();
                                    openHorizontalBox("");
                                    {
                                        openFrameBox("");
                                        closeBox();
                                        // add a meter level box: out of box stack,
                                        // no need to closeBox
                                        openLevelMeterBox("Signal Level");
                                        openFrameBox("");
                                        closeBox();
                                        
                                    }
                                    closeBox();
                                    openFrameBox("");
                                    closeBox();
                                    openSpaceBox("");
                                    closeBox();
                                    openFrameBox("");
                                    closeBox();
                                }
                                closeBox();
                                openSpaceBox("");
                                closeBox();
                                openSpaceBox("");
                                closeBox();
                            }
                            closeBox();
                            openSpaceBox("");
                            closeBox();
                            openSpaceBox("");
                            closeBox();
                            openSpaceBox("");
                            closeBox();
                            openFrameBox("");
                            closeBox();
                        }
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
                closeBox(); // main widget end
                // add racks
                openScrollBox("");
                {
                    openPlugBox(_("Mono Rack"));
                    {
                        gx_build_mono_rack();
                    }
                    closeBox();

                    openAmpBox(_("Stereo Rack"));
                    {
                        gx_build_stereo_rack();
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
    // add a Patch Info widget
    openPatchInfoBox(&gx_gui::guivar.show_patch_info);

    UiBuilder builder(this);
    engine.pluginlist.append_rack(builder);

    debug_check(all_midi_params_assigned);
    if (!connect_jack(true)) {
	gx_settings.load(gx_system::GxSettingsBase::state);
    }
    vector<string> l;
    gx_settings.fill_factory_names(l);
    for (vector<string>::iterator i = l.begin(); i != l.end(); ++i) {
	Gtk::MenuItem *mi = new Gtk::MenuItem(*i);
	Gtk::Menu *menu = new Gtk::Menu();
	gx_preset::gxpreset.gx_append_factory_file(*i, *menu);
	mi->set_submenu(*manage(menu));
	mainmenu.preset_factory_settings_menu.append(*manage(mi));
    }
    if (l.empty()) {
	mainmenu.preset_factory_settings_label.set_sensitive(false);
    } else {
	mainmenu.preset_factory_settings_menu.show_all();
    }
    gx_preset::gxpreset.gx_refresh_preset_menus();
    gx_jconv::gx_load_jcgui();
}

} // !namespace gx_gui
