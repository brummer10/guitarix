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

void set_accessible(GtkWidget *widget,GtkLabel *label);

/****************************************************************/

class UiSwitch: public Gxw::Switch {
 public:
    explicit UiSwitch(const char *sw_type);
    Gtk::Widget *get_widget() { return this;}
    static UiSwitch *new_switch(gx_engine::GxMachineBase& machine, const char *sw_type, gx_engine::Parameter &param);
    static UiSwitch *new_switch(gx_engine::GxMachineBase& machine, const char *sw_type, const std::string& id) {
        if (!machine.parameter_hasId(id)) return 0;
        return new_switch(machine, sw_type, machine.get_parameter(id));
    }
    static Gtk::Widget *create(gx_engine::GxMachineBase& machine, const char *sw_type, const std::string& id) {
        return new_switch(machine, sw_type, id)->get_widget();}
};

/****************************************************************/

class UiSwitchFloat: public UiSwitch {
 protected:
    gx_engine::GxMachineBase& machine;
    gx_engine::FloatParameter& param;
    void on_toggled();
    void set_value(float v);
 public:
    UiSwitchFloat(gx_engine::GxMachineBase& machine, const char *sw_type, gx_engine::FloatParameter &param);
};

/****************************************************************/

class UiSwitchBool: public UiSwitch {
 protected:
    gx_engine::GxMachineBase& machine;
    gx_engine::BoolParameter& param;
    void on_toggled();
    void set_value(bool v);
 public:
    UiSwitchBool(gx_engine::GxMachineBase& machine, const char *sw_type, gx_engine::BoolParameter &param);
};

/****************************************************************/

class UiSwitchWithCaption {
 private:
    Gtk::Label m_label;
    Gtk::Box *m_box;
 protected:
    UiSwitch *m_switch;
 public:
    static Gtk::Widget* create(gx_engine::GxMachineBase& machine, const char *sw_type, const std::string& id,
                             Gtk::PositionType pos);
    static Gtk::Widget* create(gx_engine::GxMachineBase& machine, const char *sw_type, const std::string& id,
			       const Glib::ustring& label, Gtk::PositionType pos);
    UiSwitchWithCaption(gx_engine::GxMachineBase& machine, const char *sw_type, gx_engine::Parameter &param,
                        const Glib::ustring& label, Gtk::PositionType pos);
    ~UiSwitchWithCaption();
    Gtk::Widget *get_widget() { return m_box; }
};

/****************************************************************/

class GxVBox: public Gtk::VBox {
 public:
    Gtk::Label m_label;
    GxVBox();
    ~GxVBox();
};

/****************************************************************/

class GxHBox: public Gtk::HBox {
 public:
    Gtk::Label m_label;
    Gtk::Frame m_frame;
    GxHBox();
    ~GxHBox();
};

/****************************************************************/

class GxPaintBox: public Gtk::HBox {
 public:
    Gxw::PaintBox m_paintbox;
    GxPaintBox(const char *expose_funk);
    ~GxPaintBox();
};

/****************************************************************/

class GxEventBox: public Gtk::HBox {
 public:
    Gtk::HBox m_hbox;
    Gtk::HBox m_pbox;
    Gtk::HBox m_tbox;
    Gtk::EventBox m_eventbox;
    Gtk::HBox m_fbox;
    Gtk::HBox m_fixedbox;
    Gtk::Label m_label;
    GxEventBox();
    ~GxEventBox();
};

/****************************************************************/

class GxMainBox: public Gtk::HBox {
 public:
    Gtk::HBox m_hbox;
    Gtk::HBox m_pbox;
    Gtk::HBox m_tbox;
    Gtk::HBox m_fbox;
    Gtk::EventBox m_eventbox;
    Gtk::Fixed m_fixedbox;
    Gtk::Label m_label;
    Gxw::PaintBox m_paintbox;
    GxMainBox(const char *expose_funk);
    ~GxMainBox();
};

/****************************************************************/

class GxNotebookBox: public Gtk::Notebook {
 public:
    GxNotebookBox();
};

/****************************************************************/

}/* end of gx_gui namespace */

#endif  // SRC_HEADERS_GX_MAIN_BOXES_H_

