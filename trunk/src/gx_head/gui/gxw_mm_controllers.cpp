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
 ** UiRegler, UiSwitch
 */

void UiRegler::on_value_changed() {
    if (blocked) {
	return;
    }
    if (log_display) {
	machine.set_parameter_value(param.id(), pow(10.0,get_value()));
    } else {
	machine.set_parameter_value(param.id(), get_value());
    }
}

void UiRegler::set_regler_value(float v) {
    blocked = true;
    if (log_display) {
	Gtk::Adjustment::set_value(log10(v));
    } else {
	Gtk::Adjustment::set_value(v);
    }
    blocked = false;
}

static bool hasId(gx_engine::GxMachineBase& machine, string id) {
    if (!machine.parameter_hasId(id)) {
	printf("not found: %s\n", id.c_str());
        return false;
    }
    return true;
}

Gtk::Widget *UiRegler::create(gx_engine::GxMachineBase& machine, Gxw::Regler *regler, const std::string& id, bool show_value) {
    if (!hasId(machine, id)) {
        return 0;
    }
    return (new UiRegler(machine, machine.get_parameter(id).getFloat(), regler, show_value))->get_widget();
}

UiRegler::UiRegler(gx_engine::GxMachineBase &machine_, gx_engine::FloatParameter &param_, Gxw::Regler *regler, bool show_value):
    Gtk::Adjustment(0, 0, 0),
    machine(machine_),
    param(param_),
    m_regler(regler),
    log_display(param_.is_log_display()),
    blocked(false) {
    if (log_display) {
	double up = log10(param.getUpperAsFloat());
	double step = log10(param.getStepAsFloat());
	configure(log10(machine.get_parameter_value<float>(param.id())), log10(param.getLowerAsFloat()), up, step, 10*step, 0);
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
	m_regler->signal_format_value().connect(
	    sigc::bind(
		sigc::ptr_fun(logarithmic_format_value),
		prec));
	m_regler->signal_input_value().connect(
	    sigc::ptr_fun(logarithmic_input_value));
    } else {
	configure(machine.get_parameter_value<float>(param.id()), param.getLowerAsFloat(), param.getUpperAsFloat(), param.getStepAsFloat(), 10*param.getStepAsFloat(), 0);
    }
    m_regler->set_show_value(show_value);
    m_regler->set_name("regler");
    m_regler->set_has_tooltip();
    string tip = param.desc();
    if (param.desc().empty()) {
	tip = param.id().substr(param.id().find_last_of(".")+1);
    }
    m_regler->set_tooltip_text(tip);
    m_regler->cp_set_var(param.id());
    m_regler->set_adjustment(*this);
    set_regler_value(machine.get_parameter_value<float>(param.id()));
    machine.signal_parameter_value<float>(param.id()).connect(
	sigc::mem_fun(this, &UiRegler::set_regler_value));
    m_regler->show();
    m_regler->get_accessible()->set_description (param.id());
    m_regler->get_accessible()->set_name(param.id().substr(param.id().find_last_of(".")+1));
    connect_midi_controller(m_regler, param.id(), machine);
}

UiRegler::~UiRegler() {
    delete m_regler;
}

UiSelectorBase::UiSelectorBase(gx_engine::GxMachineBase& machine_, const std::string& id_)
    : machine(machine_), id(id_), m_selector() {
    m_selector.show();
    m_selector.cp_set_var(id);
    Gtk::TreeModelColumn<Glib::ustring> label;
    Gtk::TreeModelColumnRecord rec;
    rec.add(label);
    Glib::RefPtr<Gtk::ListStore> ls = Gtk::ListStore::create(rec);
    gx_engine::Parameter& param = machine.get_parameter(id);
    for (const value_pair *p = param.getValueNames(); p->value_id; ++p) {
        ls->append()->set_value(0, Glib::ustring(param.value_label(*p)));
    }
    m_selector.set_model(ls);
    m_selector.set_has_tooltip();
    string tip = param.desc();
    if (param.desc().empty()) {
	tip = id.substr(id.find_last_of(".")+1);
    }
    m_selector.set_tooltip_text(tip);
    m_selector.get_accessible()->set_description(id);
    m_selector.get_accessible()->set_name(id.substr(id.find_last_of(".")+1));
}

template <>
UiSelector<float>::UiSelector(gx_engine::GxMachineBase& machine_, const std::string& id_)
    : UiSelectorBase(machine_, id_),
      Gtk::Adjustment(0,0,0) {
    gx_engine::FloatParameter& param = machine.get_parameter(id).getFloat();
    configure(machine.get_parameter_value<float>(id), param.getLowerAsFloat(), param.getUpperAsFloat(), param.getStepAsFloat(), 10*param.getStepAsFloat(), 0);
    m_selector.set_adjustment(*this);
    machine.signal_parameter_value<float>(id).connect(
	sigc::mem_fun(this, &UiSelector<float>::set_selector_value));
    connect_midi_controller(&m_selector, id, machine);
}

template <>
UiSelector<int>::UiSelector(gx_engine::GxMachineBase& machine, const std::string& id_)
    : UiSelectorBase(machine, id_),
      Gtk::Adjustment(0, 0, 0) {
    gx_engine::IntParameter& param = machine.get_parameter(id).getInt();
    configure(machine.get_parameter_value<int>(id), param.getLowerAsFloat(), param.getUpperAsFloat(), 1, 5, 0);
    m_selector.set_adjustment(*this);
    machine.signal_parameter_value<int>(id).connect(
	sigc::mem_fun(this, &UiSelector<int>::set_selector_value));
    connect_midi_controller(&m_selector, id, machine);
}

template <class T>
void UiSelector<T>::set_selector_value(T v) {
    m_selector.set_value(v);
}

template <class T>
void UiSelector<T>::on_value_changed() {
    machine.set_parameter_value(id, get_value());
}

template <>
void UiSelector<int>::on_value_changed() {
    machine.set_parameter_value(id, static_cast<int>(get_value()));
}

Gtk::Widget* UiReglerWithCaption::create(gx_engine::GxMachineBase& machine, Gxw::Regler *regler,
					 const std::string& id, bool show_value) {
    if (!hasId(machine, id)) {
        return 0;
    }
    return create(machine, regler, id, machine.get_parameter(id).l_name(), show_value);
}

Gtk::Widget* UiReglerWithCaption::create(gx_engine::GxMachineBase& machine, Gxw::Regler *regler,
					 const std::string& id, const Glib::ustring& label, bool show_value) {
    if (!hasId(machine, id)) {
        return 0;
    }
    return (new UiReglerWithCaption(machine, machine.get_parameter(id).getFloat(), regler, label, show_value))->get_widget();
}

Gtk::Widget* UiRackReglerWithCaption::create(gx_engine::GxMachineBase& machine, Gxw::Regler *regler, const std::string& id) {
    if (!hasId(machine, id)) {
        return 0;
    }
    return create(machine, regler, id, machine.get_parameter(id).l_name());
}

Gtk::Widget* UiRackReglerWithCaption::create(gx_engine::GxMachineBase& machine, Gxw::Regler *regler,
					     const std::string& id, const Glib::ustring& label) {
    if (!hasId(machine, id)) {
        return 0;
    }
    return (new UiRackReglerWithCaption(machine, machine.get_parameter(id).getFloat(), regler,
            label))->get_widget();
}

Gtk::Widget* UiRackRegler::create(gx_engine::GxMachineBase& machine, Gxw::Regler *regler, const std::string& id) {
    if (!hasId(machine, id)) {
        return 0;
    }
    return create(machine, regler, id, machine.get_parameter(id).l_name());
}

Gtk::Widget* UiRackRegler::create(gx_engine::GxMachineBase& machine, Gxw::Regler *regler,
				  const std::string& id, const Glib::ustring& label) {
    if (!hasId(machine, id)) {
        return 0;
    }
    return (new UiRackRegler(machine, machine.get_parameter(id).getFloat(), regler, label))->get_widget();
}

Gtk::Widget* UiRackMasterRegler::create(gx_engine::GxMachineBase& machine, Gxw::Regler *regler,
					const std::string& id, const Glib::ustring& label) {
    if (!hasId(machine, id)) {
        return 0;
    }
    return (new UiRackMasterRegler(machine, machine.get_parameter(id).getFloat(), regler, label))->get_widget();
}

Gtk::Widget* UiRackMasterRegler::create(gx_engine::GxMachineBase& machine, Gxw::Regler *regler, const std::string& id) {
    if (!hasId(machine, id)) {
        return 0;
    }
    return create(machine, regler, id, machine.get_parameter(id).l_name());
}

UiReglerWithCaption::UiReglerWithCaption(gx_engine::GxMachineBase& machine,
                    gx_engine::FloatParameter &param, Gxw::Regler *regler,
                    const Glib::ustring& label, bool show_value)
    : UiRegler(machine, param, regler, show_value) {
    m_label.set_text(label);
    m_label.set_name("effekt_label");
    m_box.set_name(param.id());
    m_box.pack_start(m_label, Gtk::PACK_SHRINK);
    m_box.pack_start(*m_regler, Gtk::PACK_SHRINK);
    set_accessible(*m_regler, m_label);
    m_box.show_all();
}

UiRackReglerWithCaption::UiRackReglerWithCaption(gx_engine::GxMachineBase& machine,
                         gx_engine::FloatParameter &param, Gxw::Regler *regler,
                         const Glib::ustring& label)
    : UiRegler(machine, param, regler, true) {
    m_label.set_text(label);
    m_label.set_name("rack_label");
    m_label.set_justify(Gtk::JUSTIFY_CENTER);
    m_box.set_name(param.id());
    m_box.pack_start(m_label, Gtk::PACK_SHRINK);
    if (typeid(*m_regler) == typeid(Gxw::ValueDisplay) || typeid(*m_regler) == typeid(Gxw::SimpleValueDisplay)) { // FIXME
	Gtk::HBox *h = new Gtk::HBox();
	h->pack_start(*m_regler, Gtk::PACK_EXPAND_PADDING);
	m_box.pack_start(*manage(h), Gtk::PACK_EXPAND_PADDING);
    } else {
	m_box.pack_end(*m_regler, Gtk::PACK_SHRINK);
    }
    set_accessible(*m_regler, m_label);
    m_box.show_all();
}

UiRackRegler::UiRackRegler(gx_engine::GxMachineBase& machine, gx_engine::FloatParameter &param, Gxw::Regler *regler,
    const Glib::ustring& label)
    : UiRegler(machine, param, regler, true) {
    m_box.set_name(param.id());
    m_box.pack_start(*m_regler, Gtk::PACK_SHRINK);
    m_regler->set_name("rack_regler");
    m_regler->get_accessible()->set_description (param.id().c_str());
    m_regler->get_accessible()->set_name (param.id().substr(
              param.id().find_last_of(".")+1).c_str());
    m_box.show_all();
}

UiRackMasterRegler::UiRackMasterRegler(gx_engine::GxMachineBase& machine,
                         gx_engine::FloatParameter &param, Gxw::Regler *regler,
                         const Glib::ustring& label)
    : UiRegler(machine, param, regler, false) {
    m_label.set_text(label+" "); //FIXME: font bug, add space to avoid cut off on the right
    m_label.set_name("rack_label");
    m_label.set_size_request(-1,12);
    m_box.set_name(param.id());
    m_box.set_spacing(4);
    m_box.pack_start(*m_regler, Gtk::PACK_SHRINK);
    m_box.pack_start(m_label, Gtk::PACK_SHRINK);
    set_accessible(*m_regler, m_label);
    m_box.show_all();
}

UiSwitch::UiSwitch(const char *sw_type):
    Switch(sw_type) {
}

UiSwitch *UiSwitch::new_switch(gx_engine::GxMachineBase& machine, const char* sw_type, gx_engine::Parameter& param) {
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

Gtk::Widget* UiSwitchWithCaption::create(
    gx_engine::GxMachineBase& machine, const char *sw_type, const std::string& id, Gtk::PositionType pos) {
    if (!hasId(machine, id)) {
        return 0;
    }
    return create(machine, sw_type, id, machine.get_parameter(id).l_name(), pos);
}

Gtk::Widget* UiSwitchWithCaption::create(
    gx_engine::GxMachineBase& machine, const char *sw_type, const std::string& id,
    const Glib::ustring& label, Gtk::PositionType pos) {
    if (!hasId(machine, id)) {
        return 0;
    }
    return (new UiSwitchWithCaption(machine, sw_type, machine.get_parameter(id),
                                    label, pos))->get_widget();
}

UiSwitchWithCaption::UiSwitchWithCaption(gx_engine::GxMachineBase& machine,
                                         const char *sw_type, gx_engine::Parameter &param,
                                         const Glib::ustring& label, Gtk::PositionType pos):
    m_switch(UiSwitch::new_switch(machine, sw_type, param)) {
    m_label.set_text(label);
    m_label.set_name("rack_label");
    if (pos == Gtk::POS_LEFT || pos == Gtk::POS_RIGHT) {
        m_box = new Gtk::HBox();
    } else {
	m_label.set_justify(Gtk::JUSTIFY_CENTER);
        m_box = new Gtk::VBox();
    }
    if (pos == Gtk::POS_LEFT || pos == Gtk::POS_TOP) {
        m_box->pack_start(m_label, Gtk::PACK_SHRINK);
        m_box->pack_start(*m_switch, Gtk::PACK_EXPAND_PADDING);
    } else {
        m_box->pack_start(*m_switch, Gtk::PACK_EXPAND_PADDING);
        m_box->pack_start(m_label, Gtk::PACK_SHRINK);
    }
    m_box->set_name(param.id());
    set_accessible(*m_switch, m_label);
    m_box->show_all();
}

UiSwitchWithCaption::~UiSwitchWithCaption() {
    delete m_switch;
    delete m_box;
}

}/* end of gx_gui namespace */
