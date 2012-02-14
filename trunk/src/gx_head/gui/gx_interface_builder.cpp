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
inline void all_midi_params_assigned(gx_engine::ParamMap& pmap) {
    for (gx_engine::ParamMap::iterator i = pmap.begin(); i != pmap.end(); ++i) {
        if (i->second->isControllable() && !i->second->isUsed())
            gx_system::gx_print_error("Debug Check",
                                      "midi-parameter not assigned in ui: " + i->first);
    }
}
#endif

/* -------- user interface builder ---------- */
void GxMainInterface::setup() {
    static StackBoxBuilderOld bb(
	fTop, fBox, engine, pmap, fMonoRackContainer, fStereoRackContainer, rBox,
	sBox, tBox, fMode, mainmenu, fWaveView, fAccelGroup, convolver_filename_label);

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
                        gx_build_mono_rack(bb);
                    }
                    closeBox();

                    openAmpBox(_("Stereo Rack"));
                    {
                        gx_build_stereo_rack(bb);
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

    UiBuilderImpl builder(&bb);
    engine.pluginlist.append_rack(builder);

#ifndef NDEBUG
    debug_check(all_midi_params_assigned, pmap);
    const char *dbgfmt = getenv("GUITARIX_DEBUG_PARAMETER");
    if (dbgfmt) {
	pmap.set_init_values();
	pmap.dump(dbgfmt);
    }
#endif

    gx_settings.loadstate();
    if (!options.get_rcset().empty()) {
	gx_gui::gx_actualize_skin_index(options.skin, options.get_rcset());
    }
    gx_gui::gx_update_skin_menu_item(gx_engine::audio.fskin);
    gx_gui::gx_update_skin(gx_engine::audio.fskin, "");
    connect_jack(true);
    vector<Glib::ustring> l;
    gx_settings.fill_factory_names(l);
    for (vector<Glib::ustring>::iterator i = l.begin(); i != l.end(); ++i) {
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
