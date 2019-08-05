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
 *    Note: this header file is the base for gx_main_boxes.h
 * 
 * ----------------------------------------------------------------------------
 */

/* ------- This is the GUI namespace ------- */

#pragma once

#ifndef SRC_HEADERS_GX_MAIN_INTERFACE_H_
#define SRC_HEADERS_GX_MAIN_INTERFACE_H_

#include <gxwmm/bigknob.h>
#include <gxwmm/midknob.h>
#include <gxwmm/smallknob.h>
#include <gxwmm/smallknobr.h>
#include <gxwmm/wheel.h>
#include <gxwmm/hslider.h>
#include <gxwmm/eqslider.h>
#include <gxwmm/levelslider.h>
#include <gxwmm/minislider.h>
#include <gxwmm/switch.h>
#include <gxwmm/selector.h>
#include <gxwmm/valuedisplay.h>
#include <gxwmm/simplevaluedisplay.h>
#include <gxwmm/fastmeter.h>
#include <gxwmm/tuner.h>
#include <gxwmm/racktuner.h>
#include <gxwmm/waveview.h>
#include <gxwmm/portdisplay.h>
#include <gxwmm/playhead.h>
#include <gtkmm/box.h>
#include <gtkmm/alignment.h>
#include <gtkmm/checkmenuitem.h>
#include <gtkmm/radiomenuitem.h>
#include <gtkmm/builder.h>
#include <gtkmm/widgetpath.h>

#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace gx_gui {

/****************************************************************
 **
 */

class CpBase {
public:
    gx_engine::GxMachineBase& machine;
    std::string id;
    bool log_display;
    bool blocked;
    void on_cp_value_changed(Gxw::ControlParameter& c);
    void set_cp_value(float v, Gxw::ControlParameter& c);
public:
    CpBase(gx_engine::GxMachineBase& machine, const std::string& id);
    ~CpBase();
    void init(Gxw::Regler& regler, bool show_value);
};

class CpBaseCaption: public Gtk::VBox {
protected:
    CpBase base;
    Gtk::Label m_label;
public:
    CpBaseCaption(gx_engine::GxMachineBase& machine, const std::string& id);
    ~CpBaseCaption();
    void init(Gxw::Regler& regler, bool show_value);
    void set_effect_label(const char *label);
    void set_rack_label(const char *label);
    void set_rack_label_inverse(const char *label);
};

class CpMasterCaption: public Gtk::HBox {
protected:
    CpBase base;
    Gtk::Label m_label;
public:
    CpMasterCaption(gx_engine::GxMachineBase& machine, const std::string& id);
    ~CpMasterCaption();
    void init(Gxw::Regler& regler);
    void set_label(const char *label);
};

class CpBaseCaptionBoxed: public Gtk::VBox {
protected:
    CpBase base;
    Gtk::HBox h_box;
    Gtk::Label m_label;
public:
    CpBaseCaptionBoxed(gx_engine::GxMachineBase& machine, const std::string& id);
    ~CpBaseCaptionBoxed();
    void init(Gxw::Regler& regler, bool show_value);
    void set_rack_label(const char *label);
    void set_rack_label_inverse(const char *label);
};

template <class T>
class UiRegler: public T {
protected:
    CpBase base;
public:
    UiRegler(gx_engine::GxMachineBase& machine, const std::string& id, bool show_value = true)
	: T(), base(machine, id) { base.init(*this, show_value); }
};

template <class T>
class UiReglerWithCaption: public CpBaseCaption {
protected:
    T regler;
public:
    UiReglerWithCaption(gx_engine::GxMachineBase& machine, const std::string& id)
	: CpBaseCaption(machine, id), regler() { init(regler, true); }
    void set_label(const Glib::ustring& label);
    T *get_regler() { return &regler; }
};

template <class T>
class UiMasterReglerWithCaption: public CpMasterCaption {
protected:
    T regler;
public:
    UiMasterReglerWithCaption(gx_engine::GxMachineBase& machine, const std::string& id)
	: CpMasterCaption(machine, id), regler() { init(regler); }
    T *get_regler() { return &regler; }
};

template<class T>
class UiDisplayWithCaption: public CpBaseCaptionBoxed {
protected:
    T regler;
public:
    UiDisplayWithCaption(gx_engine::GxMachineBase& machine, const std::string& id)
	: CpBaseCaptionBoxed(machine, id), regler() { init(regler, true); }
    T *get_regler() { return &regler; }
};


/****************************************************************/

class CpSelectorBase {
public:
    gx_engine::GxMachineBase& machine;
    const std::string id;
public:
    CpSelectorBase(Gxw::Selector& selector, gx_engine::GxMachineBase& machine, const std::string& id);
};

template <class T>
class UiSelector: public Gxw::Selector {
private:
    CpSelectorBase base;
    void set_selector_value(T v);
    void on_value_changed();
public:
    UiSelector(gx_engine::GxMachineBase& machine, const std::string& id);
    ~UiSelector();
    void set_name(const Glib::ustring& n) { set_name(n); }
};

template <class T>
UiSelector<T>::~UiSelector() {
}

template <class T>
class UiSelectorWithCaption: public Gtk::VBox {
private:
    UiSelector<T> m_selector;
    Gtk::Label m_label;
public:
    UiSelectorWithCaption(gx_engine::GxMachineBase& machine, const std::string& id, const char *label);
    ~UiSelectorWithCaption();
    void set_name(const Glib::ustring& n) { m_selector.set_name(n); }
    void set_rack_label_inverse() {m_label.set_name("rack_label_inverse"); }
};

template <class T>
UiSelectorWithCaption<T>::UiSelectorWithCaption(gx_engine::GxMachineBase& machine, const std::string& id, const char *label)
    : Gtk::VBox(), m_selector(machine, id), m_label() {
    if (label) {
	m_label.set_text(label);
    } else {
	m_label.set_text(machine.get_parameter(id).l_name());
    }
    m_label.set_name("rack_label");
    m_label.set_justify(Gtk::JUSTIFY_CENTER);
    Gtk::VBox::set_name(id);
    pack_start(m_label, Gtk::PACK_SHRINK);
    pack_start(m_selector, Gtk::PACK_EXPAND_PADDING);
    set_accessible(m_selector, m_label);
    show_all();
}

template <class T>
UiSelectorWithCaption<T>::~UiSelectorWithCaption() {
}

/****************************************************************/

struct uiAdjustment: public uiElement {
    gx_engine::GxMachineBase& machine;
    const std::string id;
    Glib::RefPtr<Gtk::Adjustment> fAdj;
    bool blocked;
    uiAdjustment(gx_engine::GxMachineBase& machine_, const std::string& id_, const Glib::RefPtr<Gtk::Adjustment>& adj)
	: uiElement(), machine(machine_), id(id_), fAdj(adj), blocked(false) {
	fAdj->set_value(machine.get_parameter_value<float>(id));
	machine.signal_parameter_value<float>(id).connect(sigc::mem_fun(this, &uiAdjustment::on_parameter_changed));
    }
    void changed() {
	if (!blocked) {
	    machine.set_parameter_value(id, fAdj->get_value());
	}
    }
    void on_parameter_changed(float v) {
	blocked = true;
	fAdj->set_value(v);
	blocked = false;
    }
};

/****************************************************************/

extern const char *pb_gx_rack_amp_expose;
extern const char *pb_rectangle_skin_color_expose;
extern const char *pb_zac_expose;
extern const char *pb_gxhead_expose;
extern const char *pb_RackBox_expose;
extern const char *pb_gxrack_expose;
extern const char *pb_level_meter_expose;

bool button_press_cb(GdkEventButton *event, gx_engine::GxMachineBase& machine, const std::string& id);
int precision(double n);
std::string fformat(float value, float step);

/****************************************************************/

#ifndef NDEBUG
// debug_check
inline void check_id(Gtk::Widget *w, const std::string& id, gx_engine::GxMachineBase& machine) {
    if (!machine.parameter_hasId(id)) {
        Gtk::WidgetPath pt = w->get_path();
        cerr << "id '" << id << "' not found in definition of widget: "
             << pt.to_string() << endl;
        assert(false);
    }
    //gx_engine::parameter_map[zone].setUsed();
}
#endif

/****************************************************************/

inline void connect_midi_controller(Gtk::Widget *w, const std::string& id, gx_engine::GxMachineBase& machine) {
    debug_check(check_id, w, id, machine);
    w->signal_button_press_event().connect(
	sigc::bind(sigc::ptr_fun(button_press_cb), sigc::ref(machine), id), false);
}

/****************************************************************/

/* -------------------------------------------------------------------------- */
} /* end of gx_gui namespace */

#endif  // SRC_HEADERS_GX_MAIN_INTERFACE_H_

