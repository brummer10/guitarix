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
 *    Note: this header file depends on gx_ui.h 
 *    and is the base for gx_main_boxes.h
 * 
 * ----------------------------------------------------------------------------
 */

/* ------- This is the GUI namespace ------- */

#pragma once

#ifndef SRC_HEADERS_GX_MAIN_INTERFACE_H_
#define SRC_HEADERS_GX_MAIN_INTERFACE_H_

#include <gxwmm/bigknob.h>
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
#include <gtkmm/box.h>
#include <gtkmm/alignment.h>
#include <gtkmm/checkmenuitem.h>
#include <gtkmm/radiomenuitem.h>
#include <gtkmm/builder.h>

#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace gx_gui {

/****************************************************************
 **
 ** ---------------- the main GUI class ----------------
 **
 */
class GuiVariables {
 public:
    /* for level display */
    int                 meter_display_timeout; // in millisec
    int                 meter_falloff ; // in dB/sec.
    void register_gui_parameter(gx_engine::ParamMap& pmap);
};

extern GuiVariables guivar;

/****************************************************************/

class UiRegler: public Gtk::Adjustment {
private:
    using Gtk::Adjustment::set_value;
protected:
    gx_engine::GxMachineBase& machine;
    gx_engine::FloatParameter& param;
    Gxw::Regler *m_regler;
    bool log_display;
    void on_value_changed();
    void set_regler_value(float v);
 public:
    static Gtk::Widget* create(gx_engine::GxMachineBase& machine, Gxw::Regler *regler, const std::string& id, bool show_value);
    UiRegler(gx_engine::GxMachineBase& machine, gx_engine::FloatParameter& param, Gxw::Regler *regler, bool show_value);
    virtual ~UiRegler();
    Gtk::Widget *get_widget() { return m_regler; }
};

/****************************************************************/

class UiSelectorBase {
protected:
    gx_engine::GxMachineBase& machine;
    const std::string id;
    Gxw::Selector m_selector;
public:
    UiSelectorBase(gx_engine::GxMachineBase& machine, const std::string& id);
    void set_name(const Glib::ustring& n) { m_selector.set_name(n); }
    virtual Gtk::Widget *get_widget() { return &m_selector; }
};

template <class T>
class UiSelector: public UiSelectorBase, public Gtk::Adjustment {
private:
    using Gtk::Adjustment::set_value;
    void set_selector_value(T v);
    void on_value_changed();
public:
    UiSelector(gx_engine::GxMachineBase& machine, const std::string& id);
    ~UiSelector();
};

template <class T>
UiSelector<T>::~UiSelector() {
}

template <class T>
class UiSelectorWithCaption: public UiSelector<T> {
private:
    Gtk::Label m_label;
    Gtk::VBox m_box;
public:
    static Gtk::Widget* create(gx_engine::GxMachineBase& machine, const std::string& id, const char *label);
    UiSelectorWithCaption(gx_engine::GxMachineBase& machine, const std::string& id, const char *label);
    ~UiSelectorWithCaption();
    virtual Gtk::Widget *get_widget() { return &m_box; }
};

template <class T>
UiSelectorWithCaption<T>::UiSelectorWithCaption(gx_engine::GxMachineBase& machine, const std::string& id, const char *label)
    : UiSelector<T>(machine, id) {
    if (label) {
	m_label.set_text(label);
    } else {
	m_label.set_text(machine.get_parameter(id).l_name());
    }
    m_label.set_name("rack_label");
    m_label.set_justify(Gtk::JUSTIFY_CENTER);
    m_box.set_name(id);
    m_box.pack_start(m_label, Gtk::PACK_SHRINK);
    m_box.pack_start(UiSelectorBase::m_selector, Gtk::PACK_EXPAND_PADDING);
    set_accessible(GTK_WIDGET(UiSelectorBase::m_selector.gobj()),m_label.gobj());
    m_box.show_all();
}

template <class T>
UiSelectorWithCaption<T>::~UiSelectorWithCaption() {
}

/****************************************************************/

class UiReglerWithCaption: public UiRegler {
 private:
    Gtk::Label m_label;
    Gtk::VBox m_box;
 public:
    static Gtk::Widget* create(gx_engine::GxMachineBase& machine, Gxw::Regler *regler, const std::string& id, bool show_value);
    static Gtk::Widget* create(gx_engine::GxMachineBase& machine, Gxw::Regler *regler, const std::string& id,
			       const Glib::ustring& label, bool show_value);
    UiReglerWithCaption(gx_engine::GxMachineBase& machine, gx_engine::FloatParameter &param, Gxw::Regler *regler,
                        const Glib::ustring& label, bool show_value);
    Gtk::Widget *get_widget() { return &m_box;}
};

/****************************************************************/

class UiRackReglerWithCaption: public UiRegler {
 private:
    Gtk::Label m_label;
    Gtk::VBox m_box;
 public:
    static Gtk::Widget* create(gx_engine::GxMachineBase& machine, Gxw::Regler *regler, const std::string& id);
    static Gtk::Widget* create(gx_engine::GxMachineBase& machine, Gxw::Regler *regler, const std::string& id,
                             const Glib::ustring& label);
    UiRackReglerWithCaption(gx_engine::GxMachineBase& machine, gx_engine::FloatParameter &param, Gxw::Regler *regler,
                            const Glib::ustring& label);
    Gtk::Widget *get_widget() { return &m_box;}
};
/****************************************************************/

class UiRackMasterRegler: public UiRegler {
 private:
    Gtk::Label m_label;
    Gtk::HBox m_box;
 public:
    static Gtk::Widget* create(gx_engine::GxMachineBase& machine, Gxw::Regler *regler, const std::string& id);
    static Gtk::Widget* create(gx_engine::GxMachineBase& machine, Gxw::Regler *regler, const std::string& id,
			       const Glib::ustring& label);
    UiRackMasterRegler(gx_engine::GxMachineBase& machine, gx_engine::FloatParameter &param, Gxw::Regler *regler,
		       const Glib::ustring& label);
    Gtk::Widget *get_widget() { return &m_box;}
};

/****************************************************************/

class UiRackRegler: public UiRegler {
 private:
    Gtk::Label m_label;
    Gtk::VBox m_box;
 public:
    static Gtk::Widget* create(gx_engine::GxMachineBase& machine, Gxw::Regler *regler, const std::string& id);
    static Gtk::Widget* create(gx_engine::GxMachineBase& machine, Gxw::Regler *regler, const std::string& id,
                             const Glib::ustring& label);
    UiRackRegler(gx_engine::GxMachineBase& machine, gx_engine::FloatParameter &param, Gxw::Regler *regler,
                 const Glib::ustring& label);
    Gtk::Widget *get_widget() { return &m_box;}
};

/****************************************************************/

class uiCheckButton {
private:
    gx_engine::GxMachineBase& machine;
    const std::string& id;
    Gtk::ToggleButton* fButton;
public:
    uiCheckButton(gx_engine::GxMachineBase& machine_, const std::string& id_, Gtk::ToggleButton* b)
	: machine(machine_), id(id_), fButton(b) {
	fButton->set_active(machine.get_parameter_value<bool>(id));
	machine.signal_parameter_value<bool>(id).connect(sigc::mem_fun(this, &uiCheckButton::set_value));
    }
    void toggled() {
	machine.set_parameter_value(id, fButton->get_active());
    }
    void set_value(bool v) {
	fButton->set_active(v);
    }
};

/****************************************************************/

class ReportXrun {
private:
    gx_engine::GxMachineBase& machine;
    bool blocked;
    void clear();
public:
    ReportXrun(gx_engine::GxMachineBase& machine_)
	: machine(machine_), blocked(false) {}
    void run();
};

/****************************************************************/

struct uiAdjustment: public uiElement {
    gx_engine::GxMachineBase& machine;
    const std::string id;
    Gtk::Adjustment* fAdj;
    uiAdjustment(gx_engine::GxMachineBase& machine_, const std::string& id_, Gtk::Adjustment* adj)
	: uiElement(), machine(machine_), id(id_), fAdj(adj) {
	fAdj->set_value(machine.get_parameter_value<float>(id));
	machine.signal_parameter_value<float>(id).connect(sigc::mem_fun(this, &uiAdjustment::on_parameter_changed));
    }
    void changed() {
	machine.set_parameter_value(id, fAdj->get_value());
    }
    void on_parameter_changed(float v) {
	fAdj->set_value(v);
    }
};

/****************************************************************/

extern const char *sw_led;
extern const char *sw_switch;
extern const char *sw_switchit;
extern const char *sw_minitoggle;
extern const char *sw_button;
extern const char *sw_pbutton;
extern const char *sw_rbutton;

extern const char *pb_amp_expose;
extern const char *pb_conv_widget_expose;
extern const char *pb_upper_widget_expose;
extern const char *pb_rectangle_expose;
extern const char *pb_rectangle_skin_color_expose;
extern const char *pb_convolver_icon_expose;
extern const char *pb_AmpBox_expose;
extern const char *pb_tribal_box_expose;
extern const char *pb_vbox_expose;
extern const char *pb_filter_box_expose;
extern const char *pb_plug_box_expose;
extern const char *pb_info_box_expose_on;
extern const char *pb_info_box_expose_off;
extern const char *pb_slooper_expose;
extern const char *pb_zac_expose;
extern const char *pb_gxhead_expose;
extern const char *pb_RackBox_expose;
extern const char *pb_gxrack_expose;
extern const char *pb_eq_expose;
extern const char *pb_main_expose;
extern const char *pb_level_meter_expose;

bool button_press_cb(GdkEventButton *event, gx_engine::GxMachineBase& machine, const std::string& id);
int precision(double n);
std::string fformat(float value, float step);

/****************************************************************/

#ifndef NDEBUG
// debug_check
inline void check_id(Gtk::Widget *w, const std::string& id, gx_engine::GxMachineBase& machine) {
    if (!machine.parameter_hasId(id)) {
	Glib::ustring pt, ptr;
	w->path(pt, ptr);
        cerr << "id '" << id << "' not found in definition of widget: "
             << pt << endl;
        assert(false);
    }
    //gx_engine::parameter_map[zone].setUsed();
}
#endif

/****************************************************************/

inline void connect_midi_controller(Gtk::Widget *w, const std::string& id, gx_engine::GxMachineBase& machine) {
    debug_check(check_id, w, id, machine);
    w->signal_button_press_event().connect(
	sigc::bind(sigc::ptr_fun(button_press_cb), sigc::ref(machine), id));
}

/****************************************************************/

/* -------------------------------------------------------------------------- */
} /* end of gx_gui namespace */

#endif  // SRC_HEADERS_GX_MAIN_INTERFACE_H_

