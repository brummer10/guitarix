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
 * --------------------------------------------------------------------------
 *
 *    This file is part of the guitarix GUI main class
 *    Note: this header file depends on gx_ui.h and
 *    gx_main_interface.h
 * 
 * ----------------------------------------------------------------------------
 */

/* ------- This is part of the GUI namespace ------- */


#pragma once

#ifndef SRC_HEADERS_GX_MAIN_BOXES_H_
#define SRC_HEADERS_GX_MAIN_BOXES_H_

#include <gtkmm/liststore.h>
#include <gtkmm/window.h>
#include <gtkmm/frame.h>
#include <gtkmm/accelgroup.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/fixed.h>
#include <gtkmm/eventbox.h>
#include <gtkmm/notebook.h>
#include <gxwmm/paintbox.h>
#include <gtkmm/radiomenuitem.h>
#include <gtkmm/paned.h>
#include <gxwmm/switch.h>

namespace gx_gui {

/****************************************************************/

/* ---- linking menu items and parameter ---- */
class MenuCheckItem: public Gtk::CheckMenuItem {
 private:
    gx_engine::SwitchParameter* param;
    void on_my_activate();
 public:
    // FIXME not gtk-2.12: MenuCheckItem() { set_use_underline(); }
    MenuCheckItem(): Gtk::CheckMenuItem("", true), param() {}
    MenuCheckItem(const char *label): Gtk::CheckMenuItem(label, true), param() {}
    MenuCheckItem(const char *label, gx_engine::ParamMap& pmap, const char *id, bool sv = false);
    void set_parameter(gx_engine::SwitchParameter *p);
    void add_parameter(gx_engine::SwitchParameter *p);
    gx_engine::SwitchParameter * get_parameter();
};

class MenuCheckItemUiBool: public Gtk::CheckMenuItem, gx_ui::GxUiItemBool {
 private:
    virtual void reflectZone();
    void on_my_activate();
 public:
    // FIXME not gtk-2.12: MenuCheckItem() { set_use_underline(); }
    MenuCheckItemUiBool(gx_ui::GxUI* ui, bool* zone);
};

/****************************************************************/

/* ---- linking menu items and parameter ---- */
class RadioCheckItem: public Gtk::RadioMenuItem {
 private:
    gx_engine::SwitchParameter* param;
    void on_my_toggled();
 public:
    // FIXME not gtk-2.12: MenuCheckItem() { set_use_underline(); }
    RadioCheckItem(Gtk::RadioMenuItem::Group& group, const char *label=""):
	Gtk::RadioMenuItem(group, label, true), param() {}
    void set_parameter(gx_engine::SwitchParameter *p);
    gx_engine::SwitchParameter * get_parameter();
};

/****************************************************************/

class UiSwitch: public Gxw::Switch {
 public:
    explicit UiSwitch(const char *sw_type);
    GtkWidget *get_widget() { return GTK_WIDGET(gobj());}
    static UiSwitch *new_switch(gx_ui::GxUI& ui, const char *sw_type, gx_engine::Parameter &param);
    static UiSwitch *new_switch(gx_ui::GxUI& ui, const char *sw_type, string id) {
        if (!gx_engine::parameter_map.hasId(id)) return 0;
        return new_switch(ui, sw_type, gx_engine::parameter_map[id]);
    }
    static GtkWidget *create(gx_ui::GxUI& ui, const char *sw_type, string id) {
        return new_switch(ui, sw_type, id)->get_widget();}
};

/****************************************************************/

class UiSwitchFloat: public UiSwitch, gx_ui::GxUiItemFloat {
 protected:
    void on_toggled();
    virtual void reflectZone();
 public:
    UiSwitchFloat(gx_ui::GxUI& ui, const char *sw_type, gx_engine::FloatParameter &param);
};

/****************************************************************/

class UiSwitchBool: public UiSwitch, gx_ui::GxUiItemBool {
 protected:
    void on_toggled();
    virtual void reflectZone();
 public:
    UiSwitchBool(gx_ui::GxUI& ui, const char *sw_type, gx_engine::BoolParameter &param);
};

/****************************************************************/

class UiSwitchWithCaption {
 private:
    Gtk::Label m_label;
    Gtk::Box *m_box;
 protected:
    UiSwitch *m_switch;
 public:
    static GtkWidget* create(gx_ui::GxUI& ui, const char *sw_type, string id,
                             Gtk::PositionType pos);
    static GtkWidget* create(gx_ui::GxUI& ui, const char *sw_type, string id,
                             Glib::ustring label, Gtk::PositionType pos);
    UiSwitchWithCaption(gx_ui::GxUI &ui, const char *sw_type, gx_engine::Parameter &param,
                        Glib::ustring label, Gtk::PositionType pos);
    ~UiSwitchWithCaption();
    GtkWidget *get_widget() { return GTK_WIDGET(m_box->gobj()); }
};

/****************************************************************/

class UiCabSwitch: public UiSwitchWithCaption {
 private:
    void on_switch_toggled();
 public:
    static GtkWidget* create(gx_ui::GxUI& ui, string id, Glib::ustring label);
    UiCabSwitch(gx_ui::GxUI &ui, gx_engine::Parameter &param, Glib::ustring label);
};

/****************************************************************/

class UiContrastSwitch: public UiSwitchWithCaption {
 private:
    void on_switch_toggled();
 public:
    static GtkWidget* create(gx_ui::GxUI& ui, string id, Glib::ustring label);
    UiContrastSwitch(gx_ui::GxUI &ui, gx_engine::Parameter &param, Glib::ustring label);
};

/****************************************************************/

class ToggleCheckButton: public Gtk::ToggleButton {
 private:
    gx_engine::SwitchParameter* param;
    void on_my_toggled();
 public:
    Gtk::Label m_label;
    void set_parameter(gx_engine::SwitchParameter *p);
    gx_engine::SwitchParameter * get_parameter();
    ToggleCheckButton();
    ~ToggleCheckButton();
};

class ToggleCheckButtonUiBool: public Gtk::ToggleButton, gx_ui::GxUiItemBool {
 private:
    virtual void reflectZone();
    void on_my_toggled();
 public:
    Gtk::Label m_label;
    ToggleCheckButtonUiBool(gx_ui::GxUI* ui, bool* zone);
    ~ToggleCheckButtonUiBool();
};

/****************************************************************/

class GxTBox {
 public:
    Gtk::VBox m_box;
    ToggleCheckButton m_tcb;
    explicit GxTBox(const gx_ui::GxUI& ui);
    virtual ~GxTBox();
};

/****************************************************************/

class GxVBox {
 public:
    Gtk::VBox m_box;
    Gtk::Label m_label;
    explicit GxVBox(const gx_ui::GxUI& ui);
    virtual ~GxVBox();
};

/****************************************************************/

class GxVHideBox {
 public:
    Gxw::PaintBox m_box;
    Gtk::Fixed m_fixed;
    ToggleCheckButtonUiBool m_tcb;
    void on_hide_button_pressed();
    GxVHideBox(gx_ui::GxUI& ui, gx_engine::Parameter& param_switch);
    virtual ~GxVHideBox();
};

/****************************************************************/

class GxHBox {
 public:
    Gtk::HBox m_box;
    Gtk::Label m_label;
    Gtk::Frame m_frame;
    explicit GxHBox(const gx_ui::GxUI& ui);
    virtual ~GxHBox();
};

/****************************************************************/

class GxFixedBox {
 public:
    Gtk::Fixed m_fixed;
    Gtk::VBox m_box;
    explicit GxFixedBox(const gx_ui::GxUI& ui);
    virtual ~GxFixedBox();
};

/****************************************************************/

class GxPaintBox {
 public:
    Gtk::HBox m_box;
    Gxw::PaintBox m_paintbox;
    GxPaintBox(gx_ui::GxUI& ui, const char *expose_funk);
    ~GxPaintBox();
};

/****************************************************************/

class GxEventBox {
 public:
    Gtk::HBox m_box;
    Gtk::HBox m_hbox;
    Gtk::HBox m_pbox;
    Gtk::HBox m_tbox;
    Gtk::EventBox m_eventbox;
    Gtk::HBox m_fbox;
    Gtk::HBox m_fixedbox;
    Gtk::Label m_label;
    explicit GxEventBox(const gx_ui::GxUI& ui);
    virtual ~GxEventBox();
};

/****************************************************************/

class GxMainBox {
 public:
    Gtk::HBox m_box;
    Gtk::HBox m_hbox;
    Gtk::HBox m_pbox;
    Gtk::HBox m_tbox;
    Gtk::HBox m_fbox;
    Gtk::EventBox m_eventbox;
    Gtk::Fixed m_fixedbox;
    Gtk::Label m_label;
    Gxw::PaintBox m_paintbox;
    GxMainBox(gx_ui::GxUI& ui, const char *expose_funk);
    virtual ~GxMainBox();
};

/****************************************************************/

class GxMidiBox {
 public:
    Gtk::HBox m_box;
    Gtk::EventBox m_eventbox;
    Gxw::PaintBox m_paintbox;
    ToggleCheckButton m_tcb;
    UiSwitch* unit_on_off;
    Gtk::HBox m_bbox;
    Gtk::Fixed m_fixedbox;
    GxMidiBox(gx_ui::GxUI& ui, const char *expose_funk);
    virtual ~GxMidiBox();
};

/****************************************************************/

class GxNotebookBox {
 public:
    Gtk::Notebook m_box;
    explicit GxNotebookBox(const gx_ui::GxUI& ui);
    virtual ~GxNotebookBox();
};

/****************************************************************/

class GxMoveBox {
 public:
    Gtk::Label m_label;
    Gtk::Label m_label1;
    Gtk::Fixed m_fixed;
    Gxw::PaintBox m_paintbox;
    Gtk::Button m_button;
    Gtk::Button m_button1;
    ToggleCheckButtonUiBool m_button2;
    void on_hide_button_pressed();
    GxMoveBox(gx_ui::GxUI& ui, gx_engine::Parameter& param_switch);
    virtual ~GxMoveBox();
};

/****************************************************************/

class GxDialogButtonBox {
 public:
    Gtk::HBox box;
    UiSwitchBool show_dialog;
    GxDialogButtonBox(gx_ui::GxUI& ui, gx_engine::Parameter& param_dialog);
};

/****************************************************************/

class GxDialogWindowBox {
 private:
    void on_dialog_button_toggled();
    void on_reset_button_pressed();
    void on_dialog_menu_activate();
    bool on_window_delete_event(GdkEventAny* event);
    string group_id;
 public:
    Gtk::HBox box;
    Gtk::HBox box1;
    Gxw::PaintBox paintbox;
    Gtk::HBox box4;
    Gtk::HBox box5;
    Gtk::HBox box6;
    UiSwitch* unit_on_off;
    MenuCheckItemUiBool menuitem;
    Gtk::Button reset_button;
    Gtk::Button reset_button1;
    ToggleCheckButtonUiBool m_tcb;
    Gtk::Window m_regler_tooltip_window;
    GxDialogWindowBox(gx_ui::GxUI& ui,
        const char *expose_funk, gx_engine::Parameter& param_dialog,
        gx_engine::Parameter& param_switch, Gtk::ToggleButton& button,
        GtkWidget * Caller);
    ~GxDialogWindowBox();
};

/****************************************************************/

class GxWindowBox {
 private:
    bool on_window_delete_event(GdkEventAny* event, gpointer d);
    bool on_button_pressed(GdkEventButton* event);

 public:
    Gtk::HBox window;
    Gtk::HBox box;
    Gtk::HBox box1;
    Gtk::VBox rbox;
    Gtk::Window m_regler_tooltip_window;
    ToggleCheckButton m_tmono_rack;
    ToggleCheckButton m_tstereo_rack;
    GxWindowBox(gx_ui::GxUI& ui,
        Glib::ustring titl, GtkWidget * d);
    ~GxWindowBox();
};

/****************************************************************/

class GxScrollBox {
 private:
    bool on_window_delete_event(GdkEventAny* event, gpointer d);
    bool on_button_pressed(GdkEventButton* event);
    void on_rack_reorder_vertical();
    void on_rack_reorder_horizontal();
 public:
    Gtk::HBox window;
    Gtk::ScrolledWindow m_scrolled_window;
    Gtk::ScrolledWindow m_scrolled_window2;
    Gtk::HBox box;
    Gtk::HBox box1;
    Gxw::PaintBox paintbox1;
    Gtk::VBox rbox;
    Gtk::VBox vbox;
    RadioCheckItem& fOrdervRack;
    RadioCheckItem& fOrderhRack;
    GxScrollBox(gx_ui::GxUI& ui, const char *pb_2, Glib::ustring titl, gx_engine::ParamMap& pmap,
		GtkWidget *d, RadioCheckItem& fOrdervRack, RadioCheckItem& fOrderhRack);
    ~GxScrollBox();
};

/****************************************************************/

class GxToolBox {
 private:
    bool on_window_delete_event(GdkEventAny* event, gpointer d );
    bool on_button_pressed(GdkEventButton* event);
 public:
    Gtk::VBox window;
    Gtk::ScrolledWindow    m_scrolled_window;
    Gtk::HBox box;
    Gtk::HBox box1;
    Gxw::PaintBox paintbox;
    Gxw::PaintBox paintbox1;
    Gtk::VBox rbox;
    Gtk::Window m_regler_tooltip_window;
    ToggleCheckButton m_tmono_rack;
    ToggleCheckButton m_tstereo_rack;
    GxToolBox(gx_ui::GxUI& ui,
        const char *pb_2, Glib::ustring titl, GtkWidget * d);
    ~GxToolBox();
};

/****************************************************************/

class GxTunerBox {
 private:
    bool on_window_delete_event(GdkEventAny* event, gpointer d );
 public:
    Gtk::VBox window;
    Gtk::VBox    m_scrolled_window;
    Gtk::HBox box;
    Gtk::HBox box1;
    Gxw::PaintBox paintbox;
    Gxw::PaintBox paintbox1;
    Gtk::VBox rbox;
    Gtk::Window m_regler_tunertip_window;
    GxTunerBox(gx_ui::GxUI& ui,
        const char *pb_2, Glib::ustring titl, GtkWidget * d);
    ~GxTunerBox();
};

/****************************************************************/
}/* end of gx_gui namespace */

#endif  // SRC_HEADERS_GX_MAIN_BOXES_H_

