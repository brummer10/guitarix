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

#include <glibmm/i18n.h>
#include <atkmm/relationset.h>
#include <string>

#include "guitarix.h"
#include <gtkmm/menu.h>

namespace gx_gui
{
// -------------------------- gxwmm library controlers -----------------------------------

void set_accessible(Gtk::Widget& widget,Gtk::Label& label) {
    Glib::RefPtr<Atk::Object> atk_widget, atk_label;
    Glib::RefPtr<Atk::RelationSet> relation_set;
    Glib::RefPtr<Atk::Relation> relation;
    std::vector<Glib::RefPtr<Atk::Object> > targets(1);

    atk_widget = widget.get_accessible();
    atk_label = label.get_accessible();

    relation_set = atk_label->get_relation_set();
    targets[0] = atk_widget;

    relation = Atk::Relation::create(targets, Atk::RELATION_LABEL_FOR);
    relation_set->set_add(relation);

    relation_set = atk_widget->get_relation_set();
    targets[0] = atk_label;

    relation = Atk::Relation::create(targets, Atk::RELATION_LABELLED_BY);
    relation_set->set_add(relation);
}


/****************************************************************
 ** class CpBaseXX
 */

void CpBase::on_cp_value_changed(Gxw::ControlParameter& c) {
    if (blocked) {
	return;
    }
    if (log_display) {
	machine.set_parameter_value(id, pow(10.0,c.cp_get_value()));
    } else {
	machine.set_parameter_value(id, c.cp_get_value());
    }
}

void CpBase::set_cp_value(float v, Gxw::ControlParameter& c) {
    blocked = true;
    if (log_display) {
	c.cp_set_value(log10(v));
    } else {
	c.cp_set_value(v);
    }
    blocked = false;
}

CpBase::CpBase(gx_engine::GxMachineBase& machine_, const std::string& id_)
    : machine(machine_),
      id(id_),
      log_display(),
      blocked(false) {
}

void CpBase::init(Gxw::Regler& regler, bool show_value) {
    regler.set_show_value(show_value);
    regler.set_name("regler");
    regler.cp_set_var(id);
    if (!machine.parameter_hasId(id)) {
	printf("not found: %s\n", id.c_str());
	regler.set_sensitive(false);
        return;
    }
    gx_engine::FloatParameter& param = machine.get_parameter(id).getFloat();
    log_display = param.is_log_display();
    if (log_display) {
	double up = log10(param.getUpperAsFloat());
	double step = log10(param.getStepAsFloat());
	regler.cp_configure(param.group(), param.name(), log10(param.getLowerAsFloat()), up, step);
	int prec = 0;
	float d = log10((param.getStepAsFloat()-1)*param.getUpperAsFloat());
	if (up > 0) {
	    prec = up;
	    if (d < 0) {
		prec -= floor(d);
	    }
	} else if (d < 0) {
	    prec = -floor(d);
	}
	regler.signal_format_value().connect(
	    sigc::bind(
		sigc::ptr_fun(logarithmic_format_value),
		prec));
	regler.signal_input_value().connect(
	    sigc::ptr_fun(logarithmic_input_value));
    } else {
	regler.cp_configure(param.group(), param.name(), param.getLowerAsFloat(), param.getUpperAsFloat(), param.getStepAsFloat());
    }
    regler.set_has_tooltip();
    string tip = param.desc();
    if (param.desc().empty()) {
	tip = id.substr(id.find_last_of(".")+1);
    }
    regler.set_tooltip_text(tip);
    set_cp_value(machine.get_parameter_value<float>(id), regler);
    machine.signal_parameter_value<float>(id).connect(
	sigc::bind(sigc::mem_fun(this, &CpBase::set_cp_value), sigc::ref(regler)));
    regler.get_adjustment()->signal_value_changed().connect(
	sigc::bind(sigc::mem_fun(this, &CpBase::on_cp_value_changed), sigc::ref(regler)));
    regler.show();
    regler.get_accessible()->set_description (id);
    regler.get_accessible()->set_name(id.substr(id.find_last_of(".")+1));
    connect_midi_controller(&regler, id, machine);
}

CpBase::~CpBase() {
}

CpBaseCaption::CpBaseCaption(
    gx_engine::GxMachineBase& machine_, const std::string& id_)
    : Gtk::VBox(),
      base( machine_, id_),
      m_label() {
}

CpBaseCaption::~CpBaseCaption() {
}

void CpBaseCaption::init(Gxw::Regler& regler, bool show_value) {
    regler.set_label_ref(&m_label);
    base.init(regler, show_value);
    set_name(base.id);
    pack_start(m_label, Gtk::PACK_SHRINK);
    pack_start(regler, Gtk::PACK_EXPAND_WIDGET);
    set_accessible(regler, m_label);
    show_all();
}

void CpBaseCaption::set_effect_label(const char *label) {
    if (label) {
	m_label.set_text(label);
    }
    m_label.set_name("effekt_label");
}

void CpBaseCaption::set_rack_label(const char *label) {
    if (label) {
	m_label.set_text(label);
    }
    m_label.set_name("rack_label");
    m_label.set_justify(Gtk::JUSTIFY_CENTER);
}

CpMasterCaption::CpMasterCaption(
    gx_engine::GxMachineBase& machine_, const std::string& id_)
    : Gtk::HBox(),
      base(machine_, id_),
      m_label() {
}

CpMasterCaption::~CpMasterCaption() {
}

void CpMasterCaption::init(Gxw::Regler& regler) {
    regler.set_label_ref(&m_label);
    base.init(regler, false);
    m_label.set_name("rack_label");
    m_label.set_size_request(-1,12);
    set_spacing(4);
    set_name(base.id);
    set_spacing(4);
    pack_start(regler, Gtk::PACK_SHRINK);
    pack_start(m_label, Gtk::PACK_SHRINK);
    set_accessible(regler, m_label);
    show_all();
}

void CpMasterCaption::set_label(const char *label) {
    if (label) {
	Glib::ustring s = label;
	m_label.set_text(s+" "); //FIXME: font bug, add space to avoid cut off on the right
    }
}

CpBaseCaptionBoxed::CpBaseCaptionBoxed(
    gx_engine::GxMachineBase& machine_, const std::string& id_)
    : Gtk::VBox(),
      base(machine_, id_),
      h_box(),
      m_label() {
}

CpBaseCaptionBoxed::~CpBaseCaptionBoxed() {
}

void CpBaseCaptionBoxed::init(Gxw::Regler& regler, bool show_value) {
    regler.set_label_ref(&m_label);
    base.init(regler, show_value);
    m_label.set_name("rack_label");
    m_label.set_justify(Gtk::JUSTIFY_CENTER);
    set_name(base.id);
    pack_start(m_label, Gtk::PACK_SHRINK);
    h_box.pack_start(regler, Gtk::PACK_EXPAND_PADDING);
    pack_start(h_box, Gtk::PACK_EXPAND_PADDING);
    set_accessible(regler, m_label);
    show_all();
}

void CpBaseCaptionBoxed::set_rack_label(const char *label) {
    if (label) {
	m_label.set_text(label);
    }
}


/****************************************************************
 ** class UiSelectorXX
 */

CpSelectorBase::CpSelectorBase(Gxw::Selector& selector, gx_engine::GxMachineBase& machine_, const std::string& id_)
    : machine(machine_), id(id_) {
    selector.show();
    selector.cp_set_var(id);
    Gtk::TreeModelColumn<Glib::ustring> label;
    Gtk::TreeModelColumnRecord rec;
    rec.add(label);
    Glib::RefPtr<Gtk::ListStore> ls = Gtk::ListStore::create(rec);
    gx_engine::Parameter& param = machine.get_parameter(id);
    for (const value_pair *p = param.getValueNames(); p->value_id; ++p) {
        ls->append()->set_value(0, Glib::ustring(param.value_label(*p)));
    }
    selector.set_model(ls);
    selector.set_has_tooltip();
    string tip = param.desc();
    if (param.desc().empty()) {
	tip = id.substr(id.find_last_of(".")+1);
    }
    selector.set_tooltip_text(tip);
    selector.get_accessible()->set_description(id);
    selector.get_accessible()->set_name(id.substr(id.find_last_of(".")+1));
}

template <>
UiSelector<float>::UiSelector(gx_engine::GxMachineBase& machine_, const std::string& id_)
    : Gxw::Selector(),
      base(*this, machine_, id_) {
    gx_engine::FloatParameter& param = base.machine.get_parameter(base.id).getFloat();
    cp_configure(param.group(), param.name(), param.getLowerAsFloat(), param.getUpperAsFloat(), param.getStepAsFloat());
    cp_set_value(base.machine.get_parameter_value<float>(base.id));
    base.machine.signal_parameter_value<float>(base.id).connect(
	sigc::mem_fun(this, &UiSelector<float>::cp_set_value));
    connect_midi_controller(this, base.id, base.machine);
}

template <class T>
void UiSelector<T>::set_selector_value(T v) {
    cp_set_value(v);
}

template <class T>
void UiSelector<T>::on_value_changed() {
    base.machine.set_parameter_value(base.id, get_value());
}

template <>
void UiSelector<int>::on_value_changed() {
    base.machine.set_parameter_value(base.id, static_cast<int>(get_value()));
}

template <>
UiSelector<int>::UiSelector(gx_engine::GxMachineBase& machine, const std::string& id_)
    : Gxw::Selector(),
      base(*this, machine, id_) {
    gx_engine::IntParameter& param = machine.get_parameter(base.id).getInt();
    cp_configure(param.group(), param.name(), param.getLowerAsFloat(), param.getUpperAsFloat(), 1);
    cp_set_value(machine.get_parameter_value<int>(base.id));
    get_adjustment()->signal_value_changed().connect(
	sigc::mem_fun(this, &UiSelector::on_value_changed));
    base.machine.signal_parameter_value<int>(base.id).connect(
	sigc::mem_fun(this, &UiSelector<int>::set_selector_value));
    connect_midi_controller(this, base.id, base.machine);
}


/****************************************************************
 ** class UiSwitchXX
 */

UiSwitch::UiSwitch(const char *sw_type):
    Switch(sw_type) {
}

UiSwitch *UiSwitch::create(gx_engine::GxMachineBase& machine, const char* sw_type, gx_engine::Parameter& param) {
    if (param.isFloat()) {
        return new UiSwitchFloat(machine, sw_type, param.getFloat());
    } else {
        return new UiSwitchBool(machine, sw_type, param.getBool());
    }
}

void UiSwitchFloat::on_toggled() {
    machine.set_parameter_value(param.id(), static_cast<float>(get_active()));
}

void UiSwitchFloat::set_value(float v) {
  set_active(v != 0.0);
}

UiSwitchFloat::UiSwitchFloat(gx_engine::GxMachineBase& machine_, const char *sw_type, gx_engine::FloatParameter &param_)
    : UiSwitch(sw_type),
      machine(machine_),
      param(param_) {
    set_value(machine.get_parameter_value<float>(param.id()));
    cp_set_var(param.id());
    machine.signal_parameter_value<float>(param.id()).connect(
	sigc::mem_fun(this, &UiSwitchFloat::set_value));
    set_has_tooltip();
    string tip = param.desc();
    if (param.desc().empty()) {
	tip = param.id().substr(param.id().find_last_of(".")+1);
    }
    set_tooltip_text(tip);
    get_accessible()->set_description (param.id());
    get_accessible()->set_name (param.id().substr(
          param.id().find_last_of(".")+1));
    connect_midi_controller(this, param.id(), machine);
    show();
}

void UiSwitchBool::on_toggled() {
    machine.set_parameter_value(param.id(), get_active());
}

void UiSwitchBool::set_value(bool v) {
    set_active(v);
}

UiSwitchBool::UiSwitchBool(gx_engine::GxMachineBase& machine_, const char *sw_type, gx_engine::BoolParameter &param_)
    : UiSwitch(sw_type),
      machine(machine_),
      param(param_) {
    set_active(machine.get_parameter_value<bool>(param.id()));
    cp_set_var(param.id());
    machine.signal_parameter_value<bool>(param.id()).connect(
	sigc::mem_fun(this, &UiSwitchBool::set_value));
    set_has_tooltip();
    string tip = param.desc();
    if (param.desc().empty()) {
	tip = param.id().substr(param.id().find_last_of(".")+1);
    }
    set_tooltip_text(tip);
    get_accessible()->set_description (param.id());
    get_accessible()->set_name 
          (param.id().substr( param.id().find_last_of(".")+1));
    connect_midi_controller(this, param.id(), machine);
    show();
}

static bool hasId(gx_engine::GxMachineBase& machine, string id) {
    if (!machine.parameter_hasId(id)) {
        printf("not found: %s\n", id.c_str());
        return false;
    }
    return true;
}

Gtk::Widget* UiHSwitchWithCaption::create(
    gx_engine::GxMachineBase& machine, const char *sw_type, const std::string& id,
    const char *label) {
    if (!hasId(machine, id)) {
        return 0;
    }
    return new UiHSwitchWithCaption(machine, sw_type, machine.get_parameter(id), label);
}

UiHSwitchWithCaption::UiHSwitchWithCaption(
    gx_engine::GxMachineBase& machine, const char *sw_type,
    gx_engine::Parameter &param, const char *label)
    : Gtk::HBox(),
      m_label(label ? label : param.l_name()),
      m_switch(UiSwitch::create(machine, sw_type, param)) {
    m_label.set_name("rack_label");
    pack_start(m_label, Gtk::PACK_SHRINK);
    pack_start(*m_switch, Gtk::PACK_EXPAND_PADDING);
    set_name(param.id());
    set_accessible(*m_switch, m_label);
    show_all();
}

Gtk::Widget* UiVSwitchWithCaption::create(
    gx_engine::GxMachineBase& machine, const char *sw_type, const std::string& id,
    const char *label) {
    if (!hasId(machine, id)) {
        return 0;
    }
    return new UiVSwitchWithCaption(machine, sw_type, machine.get_parameter(id), label);
}

UiVSwitchWithCaption::UiVSwitchWithCaption(
    gx_engine::GxMachineBase& machine, const char *sw_type,
    gx_engine::Parameter &param, const char *label)
    : Gtk::VBox(),
      m_label(label ? label : param.l_name()),
      m_switch(UiSwitch::create(machine, sw_type, param)) {
    m_label.set_name("rack_label");
    m_label.set_justify(Gtk::JUSTIFY_CENTER);
    pack_start(*m_switch, Gtk::PACK_EXPAND_PADDING);
    pack_start(m_label, Gtk::PACK_SHRINK);
    set_name(param.id());
    set_accessible(*m_switch, m_label);
    show_all();
}

UiHSwitchWithCaption::~UiHSwitchWithCaption() {
    delete m_switch;
}

UiVSwitchWithCaption::~UiVSwitchWithCaption() {
    delete m_switch;
}

}/* end of gx_gui namespace */
