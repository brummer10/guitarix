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
 *    This is the gx_head GUI main menu class
 *
 * ----------------------------------------------------------------------------
 */

#include "guitarix.h"         // NOLINT


#include <gdk/gdkkeysyms.h>   // NOLINT
#include <glibmm/i18n.h>      // NOLINT

#include <cstring>            // NOLINT
#include <string>             // NOLINT
#include <gtkmm/menushell.h>
#include <gtkmm/separatormenuitem.h>

namespace gx_gui {

//----------------------------- main menu ----------------------------
MainMenu::MainMenu(gx_ui::GxUI& ui, const gx_system::CmdlineOptions& options, gx_engine::ParamMap& pmap)
    : Gtk::HBox(),
      menucont(),
      menupix(),
      tooltips(),

      // menubar images
      engine_on_image(""),
      engineon(options.get_pixmap_filepath("gx_on.png")),
      engine_off_image(""),
      engineoff(options.get_pixmap_filepath("gx_off.png")),
      engine_bypass_image(""),
      engineby(options.get_pixmap_filepath("gx_bypass.png")),
      jackd_on_image(""),
      jackstateon(options.get_pixmap_filepath("jackd_on.png")),
      jackd_off_image(""),
      jackstateoff(options.get_pixmap_filepath("jackd_off.png")),

      // engine menu
      engine_menu_label(_("_Engine"), true),
      engine_menu(),
      engine_start_stop_item(_("Engine _Start / _Stop"), true),
      engine_bypass_item(_("Engine _Bypass"), true),
      //---
      jack_connect_item(_("Jack Server _Connection "), true),
      portmap_item(_("Jack _Ports "), true),
      jack_latency_label(_("_Latency"), true),
      jack_latency_menu(),
      jack_latency_group(),
      //---
      engine_midi_item(_("M_idi Controller"), true),
      //---
      engine_quit_item(_("_Quit"), true),

      // preset menu
      preset_menu_label(_("_Presets"), true),
      preset_menu(),
      preset_load_item(_("_Load Preset..."), true),
      preset_save_item(_("_Save Preset..."), true),
      preset_save_new(_("_New Preset"), true),
      preset_rename_item(_("_Rename Preset..."), true),
      preset_submenu(),
      // factory settings submenu
      preset_factory_settings_label(_("Factory Settings"), true),
      preset_factory_settings_menu(),
      // !factory settings submenu
      //---
      preset_patch_info_item(_("Patch Inf_o"), true),
      //---
      preset_load_file_item(_("Load Preset-_file"), true),
      preset_export_file_item(_("E_xport Preset-file"), true),
      //---
      preset_recall_item(_("Recall Main _Setting"), true),
      preset_save_main_item(_("_Save As Main _Setting"), true),
      //---
      // preset extra submenu
      preset_more_label(_("More Preset Options..."), true),
      preset_more_menu(),
      preset_next(_("Next _Preset"), true),
      preset_previous(_("Previous _Preset"), true),
      //---
      preset_save_active(_("_Save Active Preset"), true),
      preset_rename_active(_("_Rename Active Preset"), true),
      preset_delete_active(_("_Delete Active Preset"), true),
      //---
      preset_delete_all(_("_Delete All Presets"), true),

      // plugin menu
      plugin_menu_label(_("P_lugins"), true),
      plugin_menu(),
      fShowToolBar(_("Show Plugin _Bar"),pmap,"system.show_toolbar"),
      fShowRRack(_("Show _Rack"),pmap,"system.show_rrack"),
      //---
      fShowRack(_("Show _Mono Rack"),pmap,"system.show_rack"),
      plugin_mono_plugins(_("_Mono Plugins"), true),
      plugin_mono_menu(),
      fShowMidiOut(_("MIDI out"),pmap,"ui.midi_out"),

      //---
      fShowSRack(_("Show St_ereo Rack"),pmap,"system.show_Srack"),
      plugin_stereo_plugins(_("_Stereo Plugins"), true),
      //---
      rack_order_group(),
      fOrdervRack(rack_order_group, _("Order Rack Vertically")),
      fOrderhRack(rack_order_group, _("Order Rack Horizontally")),

      // amp menu
      amp_menu_label(_("_Tube "), true),
      amp_menu(),
      amp_radio_menu(&ui, pmap["tube.select"].getUInt()),

      // options menu
      options_menu_label(_("_Options"), true),
      options_menu(),
      options_meterbridge(_("_Meterbridge"), true),
      fShowTuner(_("_Tuner"),pmap,"system.show_tuner"),
      fShowValue(_("Hide _Values"),pmap,"system.show_value"),
      // skin submenu
      skin_menu_label(_("_Skin..."), true),
      skin_menu(),
      skingroup(),
      // !skin submenu
      select_jack_cmd("_Jack Startup Control",true),
      fShowLogger(_("Show _Logging Box"),pmap,"system.show_logger"),
      fShowTooltips(_("Show _Tooltips"),pmap,"system.show_tooltips",true),
      fMidiInPreset(_("Include MIDI in _presets"),pmap,"system.midi_in_preset"),
      options_reset_all(_("Reset _All Parameters"), true),


      // about menu
      about_menu_label(_("_About"), true),
      about_menu(),
      about_about_item(_("_About"), true),
      about_help_item(_("_Help"), true) {
}

void MainMenu::setup(GxMainInterface& intf) {
    amp_radio_menu.setup(amp_menu, intf.fAccelGroup);
    pack_start(menucont);
    pack_end(menupix);
    //menupix.set_pack_direction(Gtk::PACK_DIRECTION_RTL);  // after gtk 2.20
    gtk_menu_bar_set_pack_direction(menupix.gobj(), GTK_PACK_DIRECTION_RTL);

    engine_on_image.set_always_show_image();
    engine_on_image.set_image(engineon);
    menupix.append(engine_on_image);
    tooltips.set_tip(engine_on_image, _("engine is on"), "engine state.");

    engine_off_image.set_always_show_image();
    engine_off_image.set_image(engineoff);
    menupix.append(engine_off_image);
    tooltips.set_tip(engine_off_image, _("engine is off"), "engine state.");

    engine_bypass_image.set_always_show_image();
    engine_bypass_image.set_image(engineby);
    menupix.append(engine_bypass_image);
    tooltips.set_tip(engine_bypass_image, _("engine is in bypass mode"), "engine state.");

    jackd_on_image.set_always_show_image();
    jackd_on_image.set_image(jackstateon);
    menupix.append(jackd_on_image);
    tooltips.set_tip(jackd_on_image, _("jack server is connected"), "jack server state.");

    jackd_off_image.set_always_show_image();
    jackd_off_image.set_image(jackstateoff);
    menupix.append(jackd_off_image);
    tooltips.set_tip(jackd_off_image, _("jack server is unconnected"), "jack server state.");
    addEngineMenu(intf);
    addPresetMenu(intf);
    addPluginMenu(intf);
    addAmpMenu(intf);
    addOptionMenu(intf);
    addAboutMenu(intf);

    /*---------------- add menu to main window box----------------*/
    menupix.show_all();
    jackd_off_image.hide();
    engine_bypass_image.hide();
    engine_off_image.hide();

    menucont.show_all();

    show();
}

void MainMenu::addEngineMenu(GxMainInterface& intf) {
    menucont.append(engine_menu_label);
    engine_menu_label.set_submenu(engine_menu);

    /*-- Create Engine start / stop item  --*/

    engine_start_stop_item.add_accelerator(
	"activate", intf.fAccelGroup, GDK_space, Gdk::ModifierType(0),
	Gtk::ACCEL_VISIBLE);
    engine_menu.append(engine_start_stop_item);
    engine_start_stop_item.set_active();
    engine_start_stop_item.signal_activate().connect(
	sigc::mem_fun(intf, &GxMainInterface::toggle_engine_switch));

    /*-- Create Engine bypass item  --*/
    engine_bypass_item.add_accelerator(
	"activate", intf.fAccelGroup, GDK_b, Gdk::ModifierType(0), Gtk::ACCEL_VISIBLE);
    engine_menu.append(engine_bypass_item);
    engine_bypass_item.signal_activate().connect(
	sigc::mem_fun(intf, &GxMainInterface::toggle_engine_bypass));

    /*-- add a separator line --*/
    engine_menu.append(*manage(new Gtk::SeparatorMenuItem()));

    /*---------------- Create Jack Server menu --------------------*/
    addJackServerMenu(intf);

    /*---------------- End Jack server menu declarations ----------------*/

    /*-- add a separator line --*/
    engine_menu.append(*manage(new Gtk::SeparatorMenuItem()));

    /*-- create Midi Controller Table menu item --*/
    engine_midi_item.add_accelerator(
	"activate", intf.fAccelGroup, GDK_i, Gdk::CONTROL_MASK, Gtk::ACCEL_VISIBLE);
    engine_midi_item.signal_activate().connect(
        sigc::bind(sigc::ptr_fun(gx_main_midi::MidiControllerTable::toggle),
		   sigc::ref(intf.pmap),
		   sigc::ref(engine_midi_item)));
    engine_menu.append(engine_midi_item);

    /*-- add a separator line --*/
    engine_menu.append(*manage(new Gtk::SeparatorMenuItem()));

    /*-- Create Exit menu item under Engine submenu --*/
    engine_quit_item.add_accelerator(
	"activate", intf.fAccelGroup, GDK_q, Gdk::CONTROL_MASK, Gtk::ACCEL_VISIBLE);
    engine_quit_item.signal_activate().connect(
	sigc::mem_fun(intf, &GxMainInterface::save_window_position));
    engine_quit_item.signal_activate().connect(sigc::ptr_fun(Gtk::Main::quit));
    engine_menu.append(engine_quit_item);

    /*---------------- End Engine menu declarations ----------------*/
}

//----------------------------- preset menu ----------------------------
void MainMenu::addPresetMenu(GxMainInterface& intf) {
    menucont.append(preset_menu_label);
    preset_menu_label.set_submenu(preset_menu);

    /*-- Create Presets submenus --*/
    
    preset_menu.append(preset_load_item);
    preset_load_item.set_submenu(preset_submenu[0]);
    preset_load_item.set_accel_path("<gx_head>/Load");
    preset_menu.append(preset_save_item);
    preset_save_item.set_submenu(preset_submenu[1]);
    preset_load_item.set_accel_path("<gx_head>/Save");
    preset_menu.append(preset_rename_item);
    preset_rename_item.set_submenu(preset_submenu[2]);
    preset_load_item.set_accel_path("<gx_head>/Rename");

    preset_menu.append(preset_factory_settings_label);
    preset_factory_settings_label.set_submenu(preset_factory_settings_menu);

    /*-- add New Preset saving under Save Presets menu */
    preset_submenu[1].append(preset_save_new);
    preset_save_new.signal_activate().connect(
	sigc::ptr_fun(gx_preset::gxpreset.gx_save_newpreset_dialog));
    preset_save_new.add_accelerator(
	"activate", intf.fAccelGroup, GDK_n, Gdk::CONTROL_MASK, Gtk::ACCEL_VISIBLE);

    preset_submenu[1].append(*manage(new Gtk::SeparatorMenuItem()));
    /* ------------------- */

    preset_menu.append(*manage(new Gtk::SeparatorMenuItem()));

    preset_menu.append(preset_patch_info_item);
    preset_patch_info_item.add_accelerator(
	"activate", intf.fAccelGroup, GDK_o, Gdk::CONTROL_MASK, Gtk::ACCEL_VISIBLE);
    preset_patch_info_item.signal_activate().connect(
	sigc::ptr_fun(gx_patch));

    preset_menu.append(*manage(new Gtk::SeparatorMenuItem));

    preset_menu.append(preset_load_file_item);
    preset_load_file_item.add_accelerator(
	"activate", intf.fAccelGroup, GDK_f, Gdk::CONTROL_MASK, Gtk::ACCEL_VISIBLE);
    preset_load_file_item.signal_activate().connect(
	sigc::ptr_fun(gx_preset::gxpreset.gx_load_preset_file));

    /*-- Create save as presetfile menu--*/
    preset_menu.append(preset_export_file_item);
    preset_export_file_item.add_accelerator(
	"activate", intf.fAccelGroup, GDK_x, Gdk::CONTROL_MASK, Gtk::ACCEL_VISIBLE);
    preset_export_file_item.signal_activate().connect(
	sigc::ptr_fun(gx_preset::gxpreset.gx_save_preset_file));

    /*-- add a separator line --*/
    preset_menu.append(*manage(new Gtk::SeparatorMenuItem));

    /*-- Create  Main setting submenu --*/
    preset_menu.append(preset_recall_item);
    preset_recall_item.add_accelerator(
	"activate", intf.fAccelGroup, GDK_s,
	(Gdk::ModifierType)0, Gtk::ACCEL_VISIBLE);
    preset_recall_item.signal_activate().connect(
	sigc::mem_fun(gx_preset::gxpreset,
		      &gx_preset::GxPreset::gx_recall_settings_file));

    preset_menu.append(preset_save_main_item);
    preset_save_main_item.add_accelerator(
	"activate", intf.fAccelGroup, GDK_s, Gdk::CONTROL_MASK, Gtk::ACCEL_VISIBLE);
    preset_save_main_item.signal_activate().connect(
	sigc::ptr_fun(gx_preset::gxpreset.gx_save_main_setting));

    /*-- add a separator line --*/
    preset_menu.append(*manage(new Gtk::SeparatorMenuItem));

    /*-- Create sub menu More Preset Action --*/
    preset_menu.append(preset_more_label);
    preset_more_label.set_submenu(preset_more_menu);

    /*--------------- Extra preset menu */
    addExtraPresetMenu(intf);
    intf.gx_settings.signal_presetlist_changed().connect(
	sigc::mem_fun(gx_preset::gxpreset,
		      &gx_preset::GxPreset::gx_refresh_preset_menus));
}

void MainMenu::addExtraPresetMenu(GxMainInterface& intf) {
    /*---------------- Create Presets menu items --------------------*/

    /* forward preset */
    preset_more_menu.append(preset_next);
    preset_next.add_accelerator(
	"activate", intf.fAccelGroup, GDK_Page_Down, (Gdk::ModifierType)0, Gtk::ACCEL_VISIBLE);
    preset_next.signal_activate().connect(
	sigc::ptr_fun(gx_preset::gxpreset.gx_next_preset));

    preset_more_menu.append(preset_previous);
    preset_previous.add_accelerator(
	"activate", intf.fAccelGroup, GDK_Page_Up, (Gdk::ModifierType)0, Gtk::ACCEL_VISIBLE);
    preset_previous.signal_activate().connect(sigc::ptr_fun(gx_preset::gxpreset.gx_previous_preset));

    preset_more_menu.append(*manage(new Gtk::SeparatorMenuItem));

    preset_more_menu.append(preset_save_active);
    preset_save_active.add_accelerator(
	"activate", intf.fAccelGroup, GDK_s, Gdk::MOD1_MASK, Gtk::ACCEL_VISIBLE);
    preset_save_active.signal_activate().connect(
	sigc::ptr_fun(gx_preset::gxpreset.gx_save_active_preset));

    preset_more_menu.append(preset_rename_active);
    preset_rename_active.add_accelerator(
	"activate", intf.fAccelGroup, GDK_r, Gdk::MOD1_MASK, Gtk::ACCEL_VISIBLE);
    preset_rename_active.signal_activate().connect(sigc::ptr_fun(gx_preset::gxpreset.gx_rename_active_preset_dialog));

    preset_more_menu.append(preset_delete_active);
    preset_delete_active.add_accelerator(
	"activate", intf.fAccelGroup, GDK_Delete, (Gdk::ModifierType)0, Gtk::ACCEL_VISIBLE);
    preset_delete_active.signal_activate().connect(sigc::ptr_fun(gx_preset::gxpreset.gx_delete_active_preset_dialog));

    preset_more_menu.append(*manage(new Gtk::SeparatorMenuItem));

    preset_more_menu.append(preset_delete_all);
    preset_delete_all.add_accelerator(
	"activate", intf.fAccelGroup, GDK_d,
	Gdk::ModifierType(Gdk::CONTROL_MASK|Gdk::SHIFT_MASK),
	Gtk::ACCEL_VISIBLE);
    preset_delete_all.signal_activate().connect(sigc::ptr_fun(gx_preset::gxpreset.gx_delete_all_presets_dialog));

}

void MainMenu::addAmpMenu(GxMainInterface& intf) {
    menucont.append(amp_menu_label);
    amp_menu_label.set_submenu(amp_menu);
}

//----------------------------- preset menu ----------------------------
void MainMenu::addPluginMenu(GxMainInterface& intf) {
    menucont.append(plugin_menu_label);
    plugin_menu_label.set_submenu(plugin_menu);

    fShowToolBar.add_accelerator("activate", intf.fAccelGroup,
                               GDK_b, Gdk::CONTROL_MASK, Gtk::ACCEL_VISIBLE);
    fShowToolBar.signal_activate().connect(
        sigc::mem_fun(intf, &GxMainInterface::on_toolbar_activate));
    plugin_menu.append(fShowToolBar);

    /*-- Create mono rack check menu item under Options submenu --*/
    fShowRRack.add_accelerator("activate", intf.fAccelGroup,
                               GDK_r, Gdk::CONTROL_MASK, Gtk::ACCEL_VISIBLE);
    fShowRRack.signal_activate().connect(
        sigc::mem_fun(intf, &GxMainInterface::on_rrack_activate));
    plugin_menu.append(fShowRRack);

    plugin_menu.append(*manage(new Gtk::SeparatorMenuItem));

    /*-- Create mono rack check menu item under Options submenu --*/
    fShowRack.add_accelerator("activate", intf.fAccelGroup,
			      GDK_m, Gdk::CONTROL_MASK, Gtk::ACCEL_VISIBLE);
    fShowRack.signal_activate().connect(
        sigc::mem_fun(intf, &GxMainInterface::on_rack_activate));
    plugin_menu.append(fShowRack);

    /*-- Create mono plugin menu soket item under Options submenu --*/
    plugin_menu.append(plugin_mono_plugins);
    plugin_mono_plugins.set_submenu(plugin_mono_menu);

    plugin_menu.append(*manage(new Gtk::SeparatorMenuItem));

    /*-- create midi out menu  --*/
    fShowMidiOut.add_accelerator("activate", intf.fAccelGroup,
				 GDK_a, Gdk::LOCK_MASK, Gtk::ACCEL_VISIBLE);
    fShowMidiOut.signal_activate().connect(
	sigc::mem_fun(intf, &GxMainInterface::gx_midi_out));
    plugin_mono_menu.append(fShowMidiOut);

    /*-- Create stereo rack check menu item under Options submenu --*/
    fShowSRack.add_accelerator("activate", intf.fAccelGroup,
                               GDK_e, Gdk::CONTROL_MASK, Gtk::ACCEL_VISIBLE);
    fShowSRack.signal_activate().connect(
        sigc::mem_fun(intf, &GxMainInterface::on_srack_activate));
    plugin_menu.append(fShowSRack);

    /*-- Create stereo plugin menu soket item under Options submenu --*/
    plugin_menu.append(plugin_stereo_plugins);
    plugin_stereo_plugins.set_submenu(plugin_stereo_menu);

    plugin_menu.append(*manage(new Gtk::SeparatorMenuItem));
}

static void set_tooltips(bool v) {
    gtk_settings_set_long_property(
        gtk_settings_get_default(), "gtk-enable-tooltips", v,
        "gx_head menu-option");
}

void MainMenu::addOptionMenu(GxMainInterface& intf) {
    menucont.append(options_menu_label);
    options_menu_label.set_submenu(options_menu);

    options_meterbridge.add_accelerator(
	"activate", intf.fAccelGroup, GDK_m, Gdk::MOD1_MASK, Gtk::ACCEL_VISIBLE);
    options_meterbridge.signal_activate().connect(
	sigc::bind(sigc::ptr_fun(gx_child_process::Meterbridge::start_stop),
		   sigc::ref(options_meterbridge)));
    options_menu.append(options_meterbridge);

    /*-- Create skin menu under Options submenu--*/
    addGuiSkinMenu(intf);

    select_jack_cmd.add_accelerator("activate", intf.fAccelGroup,
				    GDK_j, Gdk::CONTROL_MASK, Gtk::ACCEL_VISIBLE);
    select_jack_cmd.signal_activate().connect(
	sigc::mem_fun(intf, &GxMainInterface::on_select_jack_control));
    options_menu.append(select_jack_cmd);

    /*-- Create logbox check menu item under Options submenu --*/
    fShowLogger.add_accelerator("activate", intf.fAccelGroup,
                               GDK_l, Gdk::CONTROL_MASK, Gtk::ACCEL_VISIBLE);
    fShowLogger.signal_activate().connect(
        sigc::mem_fun(intf, &GxMainInterface::on_log_activate));
    options_menu.append(fShowLogger);
    
    /*-- Create logbox check menu item under Options submenu --*/
    fShowValue.add_accelerator("activate", intf.fAccelGroup,
                               GDK_v, Gdk::CONTROL_MASK, Gtk::ACCEL_VISIBLE);
    fShowValue.signal_activate().connect(
        sigc::mem_fun(intf, &GxMainInterface::on_value_activate));
    options_menu.append(fShowValue);

    /*-- Create menu item to control tooltip display --*/
    fShowTooltips.signal_activate().connect(
	sigc::compose(sigc::ptr_fun(set_tooltips),
		      sigc::mem_fun(fShowTooltips, &MenuCheckItem::get_active)));
    options_menu.append(fShowTooltips);

    /*-- create option for saving midi controller settings in presets --*/
    options_menu.append(fMidiInPreset);

    /*-- create option for resetting gx_head settings --*/
    options_reset_all.signal_activate().connect(
	sigc::mem_fun(intf.pmap, &gx_engine::ParamMap::set_init_values));
    options_menu.append(options_reset_all);
}

void MainMenu::addGuiSkinMenu(GxMainInterface& intf) {
    options_menu.append(skin_menu_label);
    skin_menu_label.set_submenu(skin_menu);

    /* Create black skin item under skin submenu --*/
    int idx = 0;
    for (vector<string>::iterator i = intf.options.skin.skin_list.begin();
	 i != intf.options.skin.skin_list.end();
	 ++i) {
	Gtk::RadioMenuItem *menuitem =
	    manage(new Gtk::RadioMenuItem(skingroup, i->c_str()));
	menuitem->set_active(false);
	menuitem->signal_activate().connect(
	    sigc::bind(sigc::ptr_fun(gx_change_skin), sigc::ref(*menuitem), idx++));
        skin_menu.append(*menuitem);
    }

    /*-- End skin menu declarations --*/
}

// ----------------------------- about menu ----------------------------


void MainMenu::addAboutMenu(GxMainInterface& intf) {
    menucont.append(about_menu_label);
    about_menu_label.set_submenu(about_menu);

    about_about_item.add_accelerator(
	"activate", intf.fAccelGroup,
	GDK_a, Gdk::CONTROL_MASK, Gtk::ACCEL_VISIBLE);
    about_about_item.signal_activate().connect(sigc::ptr_fun(gx_show_about));
    about_menu.append(about_about_item);

    //FIXME
    about_help_item.add_accelerator(
	"activate", intf.fAccelGroup,
	GDK_h, Gdk::CONTROL_MASK, Gtk::ACCEL_VISIBLE);
    about_help_item.signal_activate().connect(sigc::ptr_fun(gx_show_help));
    about_menu.append(about_help_item);
}

/*---------------- Jack Server Menu ----------------*/
void MainMenu::addJackServerMenu(GxMainInterface& intf) {
    /*-- Create Jack Connection toggle button --*/
    jack_connect_item.add_accelerator(
	"activate", intf.fAccelGroup,
	GDK_c, Gdk::CONTROL_MASK, Gtk::ACCEL_VISIBLE);
    jack_connect_item.signal_activate().connect(
	sigc::mem_fun(intf, &GxMainInterface::gx_jack_connection));
    engine_menu.append(jack_connect_item);

    /*-- create Jack Ports menu item --*/
    portmap_item.add_accelerator(
	"activate", intf.fAccelGroup, GDK_p, Gdk::CONTROL_MASK, Gtk::ACCEL_VISIBLE);
    portmap_item.signal_activate().connect(
	sigc::mem_fun(intf, &GxMainInterface::on_portmap_activate));
    portmap_item.show();
    engine_menu.append(portmap_item);

    /*-- Create  Latency submenu under Jack Server submenu --*/
    jack_latency_label.set_submenu(jack_latency_menu);
    engine_menu.append(jack_latency_label);

    /*-- Create  menu item under Latency submenu --*/
    gchar buf_size[8];
    const int min_pow = 4;  // 2**4  = 16
    const int max_pow = 13; // 2**13 = 8192

    for (int i = min_pow; i <= max_pow; i++) {
        int jack_buffer_size = static_cast<int>(pow(2., i));
        (void)snprintf(buf_size, sizeof(buf_size), "%d", jack_buffer_size);
	Gtk::RadioMenuItem* item = manage(new Gtk::RadioMenuItem(jack_latency_group, buf_size));
        item->set_active(false);
	item->signal_activate().connect(
	    sigc::bind(sigc::mem_fun(intf, &GxMainInterface::set_jack_buffer_size),
		       jack_buffer_size));

        // display actual buffer size as default
        jack_latency_menu.append(*item);
        intf.fJackLatencyItem[i-min_pow] = item;
    }
}

// ------- retrieve jack latency menu item
Gtk::RadioMenuItem* const GxMainInterface::getJackLatencyItem(jack_nframes_t bufsize) const {
    if (bufsize & (bufsize-1)) {
        return NULL; // not power of 2
    }
    const int minbuf = 4; // 2**4 = 16 // FIXME magic value
    int index = -(minbuf+1);
    while (bufsize) {
        bufsize >>= 1;
        index++;
    }
    if (index >= 0 && index < NJACKLAT) {
        return fJackLatencyItem[index];
    }
    return NULL;
}

/****************************************************************
 ** KeyFinder
 ** finds next unused Key in a GtkAccelGroup
 */

KeyFinder::KeyFinder(Glib::RefPtr<Gtk::AccelGroup> group) {
    next_key = GDK_a;
    gtk_accel_group_find(group->gobj(), add_keys_to_list, static_cast<gpointer>(&l));
}

KeyFinder::~KeyFinder() {
}

gboolean KeyFinder::add_keys_to_list(GtkAccelKey *key, GClosure *cl, gpointer data) {
    accel_list* l = (accel_list*)data;
    if (key->accel_mods == GDK_SHIFT_MASK) {
	l->push_back(*key);
    }
    return false;
}

int KeyFinder::operator()() {
    while (next_key <= GDK_z) {
	bool found = false;
	for (accel_list::iterator i = l.begin(); i != l.end(); ++i) {
	    if (next_key == i->accel_key) {
		found = true;
		break;
	    }
	}
	if (!found) {
	    return next_key++;
	}
	next_key++;
    }
    return -1;
}

/****************************************************************
 ** GxUiRadioMenu
 ** adds the values of an UEnumParameter as Gtk::RadioMenuItem's
 ** to a Gtk::MenuShell
 */

class TubeKeys {
private:
    static unsigned int keysep[];
    unsigned int ks;
public:
    TubeKeys(): ks(0) {};
    int operator()();
};

unsigned int TubeKeys::keysep[] = {
    GDK_a, GDK_b, GDK_c, GDK_d, GDK_e, 0,
    GDK_f, 0,
    GDK_g, GDK_h, GDK_i, GDK_j, 0,
    GDK_k, GDK_l, GDK_m, GDK_n, 0,
    GDK_o, GDK_p, GDK_q, GDK_r
};

inline int TubeKeys::operator()() {
    if (ks < sizeof(keysep)/sizeof(keysep[0])) {
	return keysep[ks++];
    }
    return -1;
}

GxUiRadioMenu::GxUiRadioMenu(gx_ui::GxUI* ui, gx_engine::UIntParameter& param_):
    gx_ui::GxUiItemUInt(ui, &param_.get_value()),
    param(param_) {
}

void GxUiRadioMenu::setup(Gtk::MenuShell& menucont, Glib::RefPtr<Gtk::AccelGroup>& ag) {
    int i, c;
    const value_pair *p;
    TubeKeys next_key;
    //KeyFinder next_key(ag); // uncomment to find out which keys are free...
    items.reserve(param.upper-param.lower+1);
    for (p = param.getValueNames(), i = 0; p->value_id; p++, i++) {
	Gtk::RadioMenuItem *r = new Gtk::RadioMenuItem(group, param.value_label(*p));
	c = next_key();
	if (c == 0) {
	    Gtk::SeparatorMenuItem* sep = new Gtk::SeparatorMenuItem();
	    menucont.append(*sep);
	    sep->show();
	    c = next_key();
	}
	items[i] = r;
	if (c > 0) {
	    r->add_accelerator("activate", ag, c, Gdk::SHIFT_MASK, Gtk::ACCEL_VISIBLE);
	}
	r->signal_activate().connect(
	    sigc::bind<int>(sigc::mem_fun(*this, &GxUiRadioMenu::on_activate), i));
	menucont.append(*r);
	r->show();
    }
}

GxUiRadioMenu::~GxUiRadioMenu() {
    for (vector<Gtk::RadioMenuItem*>::iterator i = items.begin(); i != items.end(); ++i) {
	delete *i;
    }
}

void GxUiRadioMenu::reflectZone() {
    int v = *fZone;
    fCache = v;
    items[v]->set_active(true);
}

void GxUiRadioMenu::on_activate(int i) {
    param.set(i);
}


MenuCheckItemUiBool::MenuCheckItemUiBool(gx_ui::GxUI* ui, bool* zone)
    : Gtk::CheckMenuItem("", true),
      gx_ui::GxUiItemBool(ui, zone) {
    signal_toggled().connect(
        sigc::mem_fun(*this, &MenuCheckItemUiBool::on_my_activate));
}

void MenuCheckItemUiBool::reflectZone() {
    bool v = *fZone;
    fCache = v;
    set_active(v);
}

void MenuCheckItemUiBool::on_my_activate() {
    modifyZone(get_active());
}

/* ----- Menu check item signaled from parameter ------ */

MenuCheckItem::MenuCheckItem(const char *label, gx_engine::ParamMap& pmap, const char *id, bool sv)
  : Gtk::CheckMenuItem(label, true),
    param() {
    set_parameter(pmap.reg_switch(id, false, sv));
}

void MenuCheckItem::on_my_activate() {
    param->set(get_active());
}

gx_engine::SwitchParameter* MenuCheckItem::get_parameter() {
    return param;
}

void MenuCheckItem::set_parameter(gx_engine::SwitchParameter *p) {
    param = p;
    p->signal_changed().connect(sigc::mem_fun(*this, &MenuCheckItem::set_active));
    set_active(p->get());
    signal_activate().connect(
        sigc::mem_fun(*this, &MenuCheckItem::on_my_activate));
}

void MenuCheckItem::add_parameter(gx_engine::SwitchParameter *p) {
    param = p;
    p->signal_changed().connect(sigc::mem_fun(*this, &MenuCheckItem::set_active));
    signal_activate().connect(
        sigc::mem_fun(*this, &MenuCheckItem::on_my_activate));
}

void RadioCheckItem::on_my_toggled() {
    param->set(get_active());
}

gx_engine::SwitchParameter* RadioCheckItem::get_parameter() {
    return param;
}

void RadioCheckItem::set_parameter(gx_engine::SwitchParameter *p) {
    param = p;
    p->signal_changed().connect(sigc::mem_fun(*this, &RadioCheckItem::set_active));
    signal_activate().connect(
        sigc::mem_fun(*this, &RadioCheckItem::on_my_toggled));
}

} /* end of gx_gui namespace */

