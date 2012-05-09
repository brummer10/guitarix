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

class GxVBox {
 public:
    Gtk::VBox m_box;
    Gtk::Label m_label;
    explicit GxVBox(const gx_ui::GxUI& ui);
    virtual ~GxVBox();
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

class GxNotebookBox {
 public:
    Gtk::Notebook m_box;
    explicit GxNotebookBox(const gx_ui::GxUI& ui);
    virtual ~GxNotebookBox();
};

/****************************************************************/

}/* end of gx_gui namespace */

#endif  // SRC_HEADERS_GX_MAIN_BOXES_H_

