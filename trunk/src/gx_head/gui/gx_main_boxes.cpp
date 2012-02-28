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
#if 0
GxVHideBox::~GxVHideBox() {}

void GxVHideBox::on_hide_button_pressed() {
    GList*   child_list =  gtk_container_get_children(GTK_CONTAINER(m_box.gobj()));
    GtkWidget* child = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 0));
    g_list_free(child_list);
    
    GxMainInterface& gui = GxMainInterface::get_instance();
    GtkAllocation alloc;
    gtk_widget_get_allocation (GTK_WIDGET(gui.RBox), &alloc);
    GtkWidget *plug = gtk_widget_get_parent(GTK_WIDGET(m_box.gobj()));
    GtkWidget *vbox = gtk_widget_get_parent(GTK_WIDGET(plug));
    GtkWidget *box1 = gtk_widget_get_parent(GTK_WIDGET(vbox));
    vbox = gtk_widget_get_parent(GTK_WIDGET(box1));
    box1 = gtk_widget_get_parent(GTK_WIDGET(vbox));
    vbox = gtk_widget_get_parent(GTK_WIDGET(box1));
    
    if(m_tcb.get_active()) {
        gtk_widget_hide(GTK_WIDGET(child));
    } else {
        gtk_widget_show(GTK_WIDGET(child));
    }

    gtk_widget_hide(GTK_WIDGET(vbox));
    if (gui.fWindow.get_resizable())
        gui.fWindow.set_resizable(false);
    gtk_widget_show(GTK_WIDGET(vbox));

    if (GDK_IS_WINDOW (gui.RBox->window)) {
        gtk_widget_set_size_request(GTK_WIDGET(gui.RBox), -1, alloc.height);
    } else {
        gtk_widget_set_size_request(GTK_WIDGET(gui.RBox), -1, 460);
    }
    if (guivar.g_threads[7] == 0 || g_main_context_find_source_by_id
                            (NULL, guivar.g_threads[7]) == NULL)
        guivar.g_threads[7] = g_timeout_add_full(
            G_PRIORITY_HIGH_IDLE + 10, 40, gx_set_resizeable,
            gpointer(gui.fWindow.gobj()), NULL);
    if (guivar.g_threads[6] == 0 || g_main_context_find_source_by_id
                            (NULL, guivar.g_threads[6]) == NULL)
        guivar.g_threads[6] = g_timeout_add_full(G_PRIORITY_HIGH_IDLE + 10, 50,
                       gx_set_default, gpointer(gui.RBox), NULL);
}

GxVHideBox::GxVHideBox(gx_ui::GxUI& ui, gx_engine::Parameter& param_switch) 
    : m_tcb(&ui, &param_switch.getBool().get_value()) {
    m_box.property_paint_func() = "rectangle_skin_color_expose";
    m_fixed.set_size_request(25, 25);
    m_fixed.put(m_tcb, 2, 4);
    m_tcb.m_label.set_text("¤");
    m_tcb.set_size_request(20, 15);
    m_box.pack_end(m_fixed, false, false, 0);
    
    m_tcb.signal_toggled().connect(
        sigc::mem_fun(*this, &GxVHideBox::on_hide_button_pressed));
}
#endif

/****************************************************************/
#if 0
GxMoveBox::~GxMoveBox() {
}

void GxMoveBox::on_hide_button_pressed() {
    GList*   child_list =  gtk_container_get_children(GTK_CONTAINER(m_paintbox.gobj()));
    GtkWidget* child2 = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 0));
    GtkWidget* parent = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 1));
    GtkWidget* parent1 = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 2));
    g_list_free(child_list);
    child_list =  gtk_container_get_children(GTK_CONTAINER(parent));
    GtkWidget* childname = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 0));
    GtkWidget* child = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 1));
    g_list_free(child_list);
    child_list =  gtk_container_get_children(GTK_CONTAINER(parent1));
    GtkWidget* child1 = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 0));
    g_list_free(child_list);
    child_list =  gtk_container_get_children(GTK_CONTAINER(child1));
    GtkWidget* child4 = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 0));
    child1 = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 1));
    GtkWidget* child5 = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 2));
    
    g_list_free(child_list);
    child_list =  gtk_container_get_children(GTK_CONTAINER(child1));
    GtkWidget* child3 = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 0));
    child1 = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 1));
    g_list_free(child_list);
    
    if(!GTK_IS_WIDGET(child1)) {
        child_list =  gtk_container_get_children(GTK_CONTAINER(child3));
        child3 = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 0));
        child1 = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 1));
        g_list_free(child_list);
    }
    
    GxMainInterface& gui = GxMainInterface::get_instance();
    GtkAllocation alloc;
    gtk_widget_get_allocation (GTK_WIDGET(gui.RBox), &alloc);
    GtkWidget *plug = gtk_widget_get_parent(GTK_WIDGET(m_paintbox.gobj()));
    GtkWidget *vbox = gtk_widget_get_parent(GTK_WIDGET(plug));
    GtkWidget *box1 = gtk_widget_get_parent(GTK_WIDGET(vbox));
    vbox = gtk_widget_get_parent(GTK_WIDGET(box1));
    box1 = gtk_widget_get_parent(GTK_WIDGET(vbox));
    vbox = gtk_widget_get_parent(GTK_WIDGET(box1));

    if(m_button2.get_active()) {
        gtk_widget_hide(GTK_WIDGET(child));  // switch
        gtk_widget_show(GTK_WIDGET(child2)); // sw_minitoggle
        gtk_widget_show(GTK_WIDGET(child3)); // master controller
        gtk_widget_hide(GTK_WIDGET(child1)); // paintbox
        gtk_widget_hide(GTK_WIDGET(child4)); // resetbutton
        gtk_widget_hide(GTK_WIDGET(child5)); // resetbutton
        gtk_widget_set_size_request(GTK_WIDGET(childname), 80, -1);
        m_fixed.set_size_request(65, 25);
        gtk_fixed_move(GTK_FIXED(m_fixed.gobj()),GTK_WIDGET(m_button1.gobj()),2, 4);
        gtk_fixed_move(GTK_FIXED(m_fixed.gobj()),GTK_WIDGET(m_button2.gobj()),22, 4);
        gtk_fixed_move(GTK_FIXED(m_fixed.gobj()),GTK_WIDGET(m_button.gobj()),42, 4);
    } else {
        gtk_widget_show(GTK_WIDGET(child));
        gtk_widget_hide(GTK_WIDGET(child2));
        gtk_widget_hide(GTK_WIDGET(child3));
        gtk_widget_show(GTK_WIDGET(child1));
        gtk_widget_show(GTK_WIDGET(child4));
        gtk_widget_show(GTK_WIDGET(child5));
        gtk_widget_set_size_request(GTK_WIDGET(childname), -1, -1);
        m_fixed.set_size_request(25, -1);
        gtk_fixed_move(GTK_FIXED(m_fixed.gobj()),GTK_WIDGET(m_button1.gobj()),2, 5);
        gtk_fixed_move(GTK_FIXED(m_fixed.gobj()),GTK_WIDGET(m_button2.gobj()),2, 20);
        gtk_fixed_move(GTK_FIXED(m_fixed.gobj()),GTK_WIDGET(m_button.gobj()),2, 35);
    }
    gtk_widget_hide(GTK_WIDGET(vbox));
    if (gui.fWindow.get_resizable())
        gui.fWindow.set_resizable(false);
    gtk_widget_show(GTK_WIDGET(vbox));

    if (GDK_IS_WINDOW (gui.RBox->window)) {
        gtk_widget_set_size_request(GTK_WIDGET(gui.RBox), -1, alloc.height);
    } else {
        gtk_widget_set_size_request(GTK_WIDGET(gui.RBox), -1, 460);
    }
    if (guivar.g_threads[7] == 0 || g_main_context_find_source_by_id
                            (NULL, guivar.g_threads[7]) == NULL)
        guivar.g_threads[7] = g_timeout_add_full(
            G_PRIORITY_HIGH_IDLE + 10, 40, gx_set_resizeable,
            gpointer(gui.fWindow.gobj()), NULL);
    if (guivar.g_threads[6] == 0 || g_main_context_find_source_by_id
                            (NULL, guivar.g_threads[6]) == NULL)
        guivar.g_threads[6] = g_timeout_add_full(G_PRIORITY_HIGH_IDLE + 10, 50,
                       gx_set_default, gpointer(gui.RBox), NULL);
}

GxMoveBox::GxMoveBox(gx_ui::GxUI& ui, gx_engine::Parameter& param_switch)
    :m_button2(&ui, &param_switch.getBool().get_value()) {
    m_paintbox.property_paint_func() = "rectangle_skin_color_expose";
    m_label.set_text("▼");
    m_label.set_name("rack_slider");
    m_label1.set_text("▲");
    m_label1.set_name("rack_slider");
    m_button.add(m_label);
    m_button.set_size_request(20, 15);
    m_button.set_name("effect_reset");
    m_button1.add(m_label1);
    m_button1.set_size_request(20, 15);
    m_button1.set_name("effect_reset");
    m_button2.m_label.set_text("¤");
    m_button2.set_size_request(20, 15);
    //m_button2.set_name("effect_reset");
    GtkStyle *style = gtk_widget_get_style(GTK_WIDGET(m_label.gobj()));
    pango_font_description_set_size(style->font_desc, 6*PANGO_SCALE);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
    gtk_widget_modify_font(GTK_WIDGET(m_label.gobj()), style->font_desc);
    gtk_widget_modify_font(GTK_WIDGET(m_label1.gobj()), style->font_desc);
    m_fixed.set_size_request(25, -1);
    m_fixed.put(m_button1, 2, 5);
    m_fixed.put(m_button, 2, 35);
    m_fixed.put(m_button2, 2, 20);
    m_paintbox.pack_end(m_fixed, false, false, 0 );
    m_fixed.show_all();
    m_paintbox.set_border_width(4);
    m_paintbox.property_spacing() = 0;
    m_paintbox.property_homogeneous() = false;
    m_button2.signal_toggled().connect(
        sigc::mem_fun(*this, &GxMoveBox::on_hide_button_pressed));
}
#endif
/****************************************************************/


GxDialogButtonBox::GxDialogButtonBox(gx_ui::GxUI& ui, gx_engine::Parameter& param_dialog)
    : box(false, 0),
    show_dialog(ui, sw_button, param_dialog.getBool()) {
    box.set_border_width(0);
    box.show_all();
}


/****************************************************************/
#if 0
void GxDialogWindowBox::on_dialog_menu_activate() {
    gx_show_extended_settings(GTK_WIDGET(menuitem.gobj()), (gpointer)paintbox.gobj());

    if (!menuitem.get_active()) {
        string group = group_id;
        group += ".on_off";
        gx_engine::parameter_map[group].stdJSON_value();
        gx_engine::parameter_map[group].setJSON_value();
    }
}

void GxDialogWindowBox::on_reset_button_pressed() {
    gx_reset_units(gx_engine::parameter_map, group_id);
}

GxDialogWindowBox::~GxDialogWindowBox() {
    delete unit_on_off;
}

GxDialogWindowBox::GxDialogWindowBox(gx_ui::GxUI& ui, const char *expose_funk,
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
        sigc::mem_fun(*this, &GxDialogWindowBox::on_reset_button_pressed));
    reset_button1.signal_pressed().connect(
        sigc::mem_fun(*this, &GxDialogWindowBox::on_reset_button_pressed));
    reset_button.set_tooltip_text(_("Reset Button, press to reset settings"));
    reset_button1.set_tooltip_text(_("Reset Button, press to reset settings"));
    box4.pack_start(box6, false, false, 0);
    box4.pack_start(box, true, true, 0);
    box4.pack_end(box5, false, false, 0);
    paintbox.pack_start(box4);
    paintbox.set_tooltip_text(title.c_str());
    m_tcb.m_label.set_text(title.c_str());
    menuitem.signal_activate().connect(
        sigc::mem_fun(*this, &GxDialogWindowBox::on_dialog_menu_activate));
}
#endif

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

#if 0
bool GxWindowBox::on_window_delete_event(GdkEventAny*, gpointer d) {
    gtk_check_menu_item_set_active(
                GTK_CHECK_MENU_ITEM(GTK_WIDGET(d)), FALSE
                );
    return false;
}

bool GxWindowBox::on_button_pressed(GdkEventButton* event) {
    gx_gui::GxMainInterface& gui = gx_gui::GxMainInterface::get_instance();
    if ((event->type == GDK_BUTTON_PRESS) && (event->button == 3)) {
        const gchar * title = gtk_widget_get_name(GTK_WIDGET(window.gobj()));
        if (strcmp(title, "MonoRack") == 0) {
            gui.mainmenu.plugin_mono_menu.popup(2, gtk_get_current_event_time());
        return true;
        } else if (strcmp(title, "StereoRack") == 0) {
            gui.mainmenu.plugin_stereo_menu.popup(2, gtk_get_current_event_time());
        return true;
        }
    }

    return false;
}

GxWindowBox::GxWindowBox(gx_ui::GxUI& ui,
    Glib::ustring titl, GtkWidget * d)
    : window(Gtk::WINDOW_TOPLEVEL),
    rbox(false, 0),
    m_regler_tooltip_window(Gtk::WINDOW_POPUP) {
    Glib::ustring title = titl;
    window.add_events(Gdk::BUTTON_PRESS_MASK);
    window.signal_delete_event().connect(
         sigc::bind<gpointer>(sigc::mem_fun(*this, &GxWindowBox::on_window_delete_event), d));
    window.add(box);
    window.signal_button_press_event().connect(
        sigc::mem_fun(*this, &GxWindowBox::on_button_pressed));
    box.show();
    rbox.show();
}
#endif

/****************************************************************/
#if 0
bool GxScrollBox::on_window_delete_event(GdkEventAny*, gpointer d) {
    gtk_check_menu_item_set_active(
                GTK_CHECK_MENU_ITEM(GTK_WIDGET(d)), FALSE
                );
    return false;
}

bool GxScrollBox::on_button_pressed(GdkEventButton* event) {
    gx_gui::GxMainInterface& gui = gx_gui::GxMainInterface::get_instance();
    if ((event->type == GDK_BUTTON_PRESS) && (event->button == 3)) {
        gui.mainmenu.plugin_mono_menu.popup(2, gtk_get_current_event_time());
        return true;
    }
    return false;
}

void GxScrollBox::on_rack_reorder_horizontal() {
    if (fOrderhRack.get_active()) { // horizontal

        if (gx_gui::gw.srack_widget) {
            paintbox1.hide();
            gx_gui::GxMainInterface& gui = gx_gui::GxMainInterface::get_instance();
            if (gui.fWindow.get_resizable())
                gui.fWindow.set_resizable(false);
            gtk_widget_ref(gx_gui::gw.srack_widget);
            GtkWidget *parent = gtk_widget_get_parent(GTK_WIDGET(gx_gui::gw.srack_widget));
            gtk_container_remove(GTK_CONTAINER(parent), gx_gui::gw.srack_widget);
            gtk_box_pack_start(GTK_BOX(box1.gobj()), gx_gui::gw.srack_widget, false, true, 0);
            gtk_widget_unref(gx_gui::gw.srack_widget);
            if (gui.mainmenu.fShowSRack.get_active()) m_scrolled_window2.show();
            paintbox1.show();
            parent = gtk_widget_get_parent(GTK_WIDGET(gx_gui::gw.rack_tool_bar));

            if (strcmp(gtk_widget_get_name(parent), "gtkmm__GtkVBox") == 0) {
                gtk_widget_ref(gx_gui::gw.rack_tool_bar);
                gtk_container_remove(GTK_CONTAINER(parent), gx_gui::gw.rack_tool_bar);
                parent = gtk_widget_get_parent(GTK_WIDGET(parent));
                GList*   child_list =  gtk_container_get_children(GTK_CONTAINER(parent));
                parent = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 1));
                child_list =  gtk_container_get_children(GTK_CONTAINER(parent));
                parent = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 0));
                child_list =  gtk_container_get_children(GTK_CONTAINER(parent));
                parent = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 2));
                parent = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 0));
                gtk_container_add(GTK_CONTAINER(parent), gx_gui::gw.rack_tool_bar);
                gtk_widget_unref(gx_gui::gw.rack_tool_bar);
                g_list_free(child_list);
            }

            gtk_widget_set_size_request(GTK_WIDGET(gui.RBox), -1,  460 );
            if (guivar.g_threads[7] == 0 || g_main_context_find_source_by_id(NULL, guivar.g_threads[7]) == NULL)
                guivar.g_threads[7] = g_timeout_add_full(
		    G_PRIORITY_HIGH_IDLE + 10, 40, gx_gui::gx_set_resizeable,
		    gpointer(gui.fWindow.gobj()), NULL);
            if (guivar.g_threads[6] == 0 || g_main_context_find_source_by_id(NULL, guivar.g_threads[6]) == NULL)
                guivar.g_threads[6] = g_timeout_add_full(G_PRIORITY_HIGH_IDLE + 10, 50,
                               gx_gui::gx_set_default, gpointer(gui.RBox), NULL);
        }
    }
}

void GxScrollBox::on_rack_reorder_vertical() {
    if (fOrdervRack.get_active()) { // vertical

        if (gx_gui::gw.srack_widget) {
            paintbox1.hide();
            gx_gui::GxMainInterface& gui = gx_gui::GxMainInterface::get_instance();
            if (gui.fWindow.get_resizable())
                gui.fWindow.set_resizable(false);
            gtk_widget_ref(gx_gui::gw.srack_widget);
            GtkWidget *parent = gtk_widget_get_parent(GTK_WIDGET(gx_gui::gw.srack_widget));
            gtk_container_remove(GTK_CONTAINER(parent), gx_gui::gw.srack_widget);
            gtk_box_pack_start(GTK_BOX(rbox.gobj()), gx_gui::gw.srack_widget, false, true, 0);
            gtk_widget_unref(gx_gui::gw.srack_widget);
            m_scrolled_window2.hide();
            paintbox1.show();
            parent = gtk_widget_get_parent(GTK_WIDGET(gx_gui::gw.rack_tool_bar));

            if (strcmp(gtk_widget_get_name(parent), "gtkmm__GtkHBox") == 0) {
                gtk_widget_ref(gx_gui::gw.rack_tool_bar);
                gtk_container_remove(GTK_CONTAINER(parent), gx_gui::gw.rack_tool_bar);
                parent = gtk_widget_get_parent(GTK_WIDGET(parent));
                parent = gtk_widget_get_parent(GTK_WIDGET(parent));
                parent = gtk_widget_get_parent(GTK_WIDGET(parent));
                GList*   child_list =  gtk_container_get_children(GTK_CONTAINER(parent));
                parent = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 0));
                gtk_container_add(GTK_CONTAINER(parent), gx_gui::gw.rack_tool_bar);
                gtk_widget_unref(gx_gui::gw.rack_tool_bar);
                g_list_free(child_list);
            }

            gtk_widget_set_size_request(GTK_WIDGET(gui.RBox), -1, 460 );
            if (guivar.g_threads[7] == 0 || g_main_context_find_source_by_id(NULL, guivar.g_threads[7]) == NULL)
                guivar.g_threads[7] = g_timeout_add_full(
		    G_PRIORITY_HIGH_IDLE + 10, 40, gx_gui::gx_set_resizeable,
		    gpointer(gui.fWindow.gobj()), NULL);
            if (guivar.g_threads[6] == 0 || g_main_context_find_source_by_id(NULL, guivar.g_threads[6]) == NULL)
                guivar.g_threads[6] = g_timeout_add_full(G_PRIORITY_HIGH_IDLE + 10, 50,
                               gx_gui::gx_set_default, gpointer(gui.RBox), NULL);
        }
    }
}

GxScrollBox::GxScrollBox(gx_ui::GxUI& ui, const char *pb_2, Glib::ustring titl, gx_engine::ParamMap& pmap,
			 GtkWidget *d, RadioCheckItem& fOrdervRack_, RadioCheckItem& fOrderhRack_)
    : window(Gtk::WINDOW_TOPLEVEL),
      rbox(false, 4),
      fOrdervRack(fOrdervRack_),
      fOrderhRack(fOrderhRack_) {
    Glib::ustring title = titl;
    window.add_events(Gdk::BUTTON_PRESS_MASK);
    m_scrolled_window.set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_ALWAYS);
    m_scrolled_window.set_shadow_type(Gtk::SHADOW_NONE);
    m_scrolled_window2.set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_ALWAYS);
    m_scrolled_window2.set_shadow_type(Gtk::SHADOW_NONE);
    m_scrolled_window2.set_name("HorizontalStereoBox");
    rbox.set_name("MonoBox");
    box1.set_name("SereoBox");
    paintbox1.set_border_width(18);
    paintbox1.property_paint_func() = pb_2;
    window.signal_delete_event().connect(
         sigc::bind<gpointer>(sigc::mem_fun(*this, &GxScrollBox::on_window_delete_event), d));
    paintbox1.pack_start(m_scrolled_window);
    paintbox1.pack_start(m_scrolled_window2);
    m_scrolled_window.add(box);
    m_scrolled_window2.add(vbox);
    window.add(paintbox1);
    window.signal_button_press_event().connect(
        sigc::mem_fun(*this, &GxScrollBox::on_button_pressed));
    fOrderhRack.signal_activate().connect(
        sigc::mem_fun(*this, &GxScrollBox::on_rack_reorder_horizontal));
    fOrdervRack.signal_activate().connect(
        sigc::mem_fun(*this, &GxScrollBox::on_rack_reorder_vertical));

    const gchar * mtitle = _("Order Rack Vertically");
    fOrdervRack.set_label(mtitle);
    gx_gui::GxMainInterface& gui = gx_gui::GxMainInterface::get_instance();
    gui.mainmenu.plugin_menu.append(fOrdervRack);
    fOrdervRack.set_parameter(pmap.reg_switch("system.order_rack_v", false, false));
    fOrdervRack.show();

    mtitle = _("Order Rack Horizontally");
    fOrderhRack.set_label(mtitle);
    gui.mainmenu.plugin_menu.append(fOrderhRack);
    fOrderhRack.set_active(false);
    fOrderhRack.set_parameter(pmap.reg_switch("system.order_rack_h", false, false));
    fOrderhRack.show();

    paintbox1.show();
    box.show();
    m_scrolled_window.show();
    // m_scrolled_window2.show();
    rbox.show();
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

