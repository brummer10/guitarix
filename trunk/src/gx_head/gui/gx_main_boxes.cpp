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
 *    This file is part of the gx_head GUI main class
 *
 * ----------------------------------------------------------------------------
 */

#include "guitarix.h"           // NOLINT


#include <gdk/gdkkeysyms.h>     // NOLINT
#include <glibmm/i18n.h>        // NOLINT

#include <iomanip>              // NOLINT
#include <cstring>              // NOLINT
#include <string>               // NOLINT

namespace gx_gui {

/****************************************************************
 ** predefined gtkmm widget classes used in main GUI
 */

void ToggleCheckButton::on_my_toggled() {
    param->set(get_active());
}

gx_engine::SwitchParameter* ToggleCheckButton::get_parameter() {
    return param;
}

void ToggleCheckButton::set_parameter(gx_engine::SwitchParameter *p) {
    param = p;
    p->signal_changed().connect(sigc::mem_fun(*this, &ToggleCheckButton::set_active));
    signal_toggled().connect(
        sigc::mem_fun(*this, &ToggleCheckButton::on_my_toggled));
}

ToggleCheckButton::~ToggleCheckButton() {}

ToggleCheckButton::ToggleCheckButton()
    : param(0) {
    set_name("barbutton");
    Pango::FontDescription font = m_label.get_style()->get_font();
    font.set_size(8*Pango::SCALE);
    font.set_weight(Pango::WEIGHT_BOLD);
    m_label.modify_font(font);
    m_label.set_name("barbuttonlabel");
    add(m_label);
}

///////

void ToggleCheckButtonUiBool::on_my_toggled() {
    modifyZone(get_active());
}

void ToggleCheckButtonUiBool::reflectZone() {
    bool v = *fZone;
    fCache = v;
    set_active(v);
}

ToggleCheckButtonUiBool::~ToggleCheckButtonUiBool() {}

ToggleCheckButtonUiBool::ToggleCheckButtonUiBool(gx_ui::GxUI* ui, bool* zone)
    : Gtk::ToggleButton(),
      gx_ui::GxUiItemBool(ui, zone) {
    set_name("barbutton");
    Pango::FontDescription font = m_label.get_style()->get_font();
    font.set_size(8*Pango::SCALE);
    font.set_weight(Pango::WEIGHT_BOLD);
    m_label.modify_font(font);
    m_label.set_name("barbuttonlabel");
    add(m_label);
    signal_toggled().connect(
        sigc::mem_fun(*this, &ToggleCheckButtonUiBool::on_my_toggled));
}

/****************************************************************/

GxTBox::~GxTBox() {}

GxTBox::GxTBox(const gx_ui::GxUI& ui) {}
/****************************************************************/

GxVBox::~GxVBox() {}

GxVBox::GxVBox(const gx_ui::GxUI& ui) {}
/****************************************************************/

GxHBox::~GxHBox() {}

GxHBox::GxHBox(const gx_ui::GxUI& ui) {}
/****************************************************************/

GxFixedBox::~GxFixedBox() {}

GxFixedBox::GxFixedBox(const gx_ui::GxUI& ui) {
    m_fixed.put(m_box, 0, 0);
}
/****************************************************************/

GxPaintBox::~GxPaintBox() {}

GxPaintBox::GxPaintBox(gx_ui::GxUI& ui, const char *expose_funk)
    : m_box(false, 0) {
    m_paintbox.property_paint_func() = expose_funk;
    m_paintbox.pack_start(m_box);
}
/****************************************************************/

GxEventBox::~GxEventBox() {}

GxEventBox::GxEventBox(const gx_ui::GxUI& ui) {
    m_eventbox.add(m_box);
    m_fixedbox.add(m_eventbox);
    m_hbox.add(m_pbox);
    m_hbox.pack_start(m_fbox, false, false);
    m_fbox.pack_start(m_fixedbox, false, false);
    m_hbox.add(m_tbox);
}
/****************************************************************/

GxMainBox::~GxMainBox() {}

GxMainBox::GxMainBox(gx_ui::GxUI& ui, const char *expose_funk) {
    m_paintbox.add(m_box);
    m_eventbox.add(m_paintbox);
    m_paintbox.property_paint_func() = expose_funk;
    m_fixedbox.put(m_eventbox, 0, 0);
    m_hbox.add(m_pbox);
    m_hbox.pack_start(m_fbox, false, false);
    m_fbox.pack_start(m_fixedbox, false, false);
    m_hbox.add(m_tbox);
}
/****************************************************************/

GxMidiBox::~GxMidiBox() {
    delete unit_on_off;
}

GxMidiBox::GxMidiBox(gx_ui::GxUI& ui, const char *expose_funk)
    : unit_on_off(UiSwitch::new_switch(ui, sw_led, "midi_out.on_off")) {
    m_bbox.pack_start(m_tcb, true, true);
    m_bbox.pack_end(*unit_on_off, false, false);
    m_paintbox.property_paint_func() = expose_funk;
    m_eventbox.add(m_paintbox);
    m_paintbox.pack_start(m_box);
    m_eventbox.set_border_width(0);
    m_eventbox.set_name("black_box");
    m_box.set_homogeneous(false);
    m_box.set_spacing(0);
    m_box.set_border_width(4);
    m_box.pack_end(m_fixedbox, false, false, 0);
    m_fixedbox.set_size_request(25, -1);
}
/****************************************************************/

GxNotebookBox::~GxNotebookBox() {}

GxNotebookBox::GxNotebookBox(const gx_ui::GxUI& ui) {
    m_box.set_name("tab_rack");
}

/****************************************************************/


GxDialogButtonBox::GxDialogButtonBox(gx_ui::GxUI& ui, gx_engine::Parameter& param_dialog)
    : box(false, 0),
    show_dialog(ui, sw_button, param_dialog.getBool()) {
    box.set_border_width(0);
    box.show_all();
}


/****************************************************************/
#if 0
void GxTunerRackBox::on_dialog_menu_activate() {
    gx_show_extended_settings(GTK_WIDGET(menuitem.gobj()), (gpointer)paintbox.gobj());
   // GxMainInterface& gui = GxMainInterface::get_instance();
   // bool tuner_on = menuitem.get_active();
   // gui.engine.tuner.used_for_display(tuner_on);
   // gui.engine.set_rack_changed();
    if (!menuitem.get_active()) {
        string group = group_id;
        group += ".on_off";
        gx_engine::parameter_map[group].stdJSON_value();
        gx_engine::parameter_map[group].setJSON_value();
    }
}

void GxTunerRackBox::on_toggled() {
    //gx_show_extended_settings(GTK_WIDGET(menuitem.gobj()), (gpointer)paintbox.gobj());
    GxMainInterface& gui = GxMainInterface::get_instance();
    bool tuner_on = unit_on_off->get_active();
    gui.engine.tuner.used_for_display(tuner_on);
    gui.engine.set_rack_changed();
    gui.mainmenu.fShowTuner.set_active(tuner_on);
   // menuitem.set_active(tuner_on);
}

void GxTunerRackBox::on_reset_button_pressed() {
    gx_reset_units(gx_engine::parameter_map, group_id);
}

GxTunerRackBox::~GxTunerRackBox() {
    delete unit_on_off;
}

GxTunerRackBox::GxTunerRackBox(gx_ui::GxUI& ui, const char *expose_funk,
                                     gx_engine::Parameter& param_dialog,
                                     gx_engine::Parameter& param_switch,
                                     Gtk::ToggleButton& button, GtkWidget * Caller)
    : box(false, 0),
      unit_on_off(UiSwitch::new_switch(ui, sw_led, param_switch)),
      menuitem(&ui, &param_dialog.getBool().get_value()),
      m_tcb(&ui, &param_dialog.getBool().get_value()),
      m_regler_tooltip_window(Gtk::WINDOW_POPUP)  {
    group_id = param_switch.id().substr(0, param_switch.id().find_last_of("."));
    Glib::ustring title = param_switch.l_group();
    box1.pack_end(*unit_on_off, false, false);
    box.set_border_width(2);
    box4.set_spacing(2);
    box4.set_border_width(2);
    box5.set_border_width(4);
    box6.set_border_width(4);
    paintbox.property_paint_func() = expose_funk;
    paintbox.set_name(title);
    reset_button.set_name("effect_reset");
    reset_button1.set_name("effect_reset");
    box5.add(reset_button);
    box6.add(reset_button1);
    box5.set_size_request(15, -1);
    box6.set_size_request(15, -1);
    reset_button.signal_pressed().connect(
        sigc::mem_fun(*this, &GxTunerRackBox::on_reset_button_pressed));
    reset_button1.signal_pressed().connect(
        sigc::mem_fun(*this, &GxTunerRackBox::on_reset_button_pressed));
    reset_button.set_tooltip_text(_("Reset Button, press to reset settings"));
    reset_button1.set_tooltip_text(_("Reset Button, press to reset settings"));
    box4.pack_start(box6, false, false, 0);
    box4.pack_start(box, true, true, 0);
    box4.pack_end(box5, false, false, 0);
    paintbox.pack_start(box4);
    paintbox.set_tooltip_text(title.c_str());
    m_tcb.m_label.set_text(title.c_str());
    unit_on_off->signal_toggled().connect(
        sigc::mem_fun(*this, &GxTunerRackBox::on_toggled));
    menuitem.signal_activate().connect(
        sigc::mem_fun(*this, &GxTunerRackBox::on_dialog_menu_activate));
}
#endif

/****************************************************************/

bool GxToolBox::on_window_delete_event(GdkEventAny*, gpointer d) {
    gtk_check_menu_item_set_active(
                GTK_CHECK_MENU_ITEM(GTK_WIDGET(d)), FALSE
                );
    return false;
}

GxToolBox::GxToolBox(gx_ui::GxUI& ui,
    const char *pb_2, Glib::ustring titl, GtkWidget * d)
    : rbox(false, 4),
    m_regler_tooltip_window(Gtk::WINDOW_POPUP) {
    Glib::ustring title = titl;
    m_scrolled_window.set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_AUTOMATIC);
    paintbox1.set_border_width(18);
    paintbox.set_border_width(4);
    paintbox1.property_paint_func() = pb_2;
    paintbox.property_paint_func() = pb_rectangle_skin_color_expose;
    window.signal_delete_event().connect(
         sigc::bind<gpointer>(sigc::mem_fun(*this, &GxToolBox::on_window_delete_event), d));
    box.add(rbox);
    paintbox1.pack_start(m_scrolled_window);
    m_scrolled_window.add(paintbox);
    paintbox.pack_start(box);
    window.add(paintbox1);
    paintbox1.show();
    box.show();
    m_scrolled_window.show();
    rbox.show();
}

/****************************************************************/
}

