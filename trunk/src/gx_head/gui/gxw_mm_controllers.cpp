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

#include <string>

#include "guitarix.h"
#include <gtkmm/menu.h>

namespace gx_gui
{
// -------------------------- gxwmm library controlers -----------------------------------

void set_accessible(GtkWidget *widget,GtkLabel *label) {
    AtkObject *atk_widget, *atk_label;
    AtkRelationSet *relation_set;
    AtkRelation *relation;
    AtkObject *targets[1];

    atk_widget = gtk_widget_get_accessible (widget);
    atk_label = gtk_widget_get_accessible (GTK_WIDGET(label));

    relation_set = atk_object_ref_relation_set (atk_label);
    targets[0] = atk_widget;

    relation = atk_relation_new(targets,1, ATK_RELATION_LABEL_FOR);
    atk_relation_set_add(relation_set,relation);
    g_object_unref(G_OBJECT(relation));

    relation_set = atk_object_ref_relation_set (atk_widget);
    targets[0] = atk_label;

    relation = atk_relation_new (targets, 1, ATK_RELATION_LABELLED_BY);
    atk_relation_set_add (relation_set, relation);
    g_object_unref (G_OBJECT (relation));
}


/****************************************************************
 ** UiRegler, UiSwitch
 */

void UiRegler::on_value_changed() {
    if (log_display) {
	modifyZone(pow(10.0,get_value()));
    } else {
	modifyZone(get_value());
    }
}

void UiRegler::reflectZone() {
    float     v = *fZone;
    fCache = v;
    if (log_display) {
	set_value(log10(v));
    } else {
	set_value(v);
    }
}

static bool hasId(gx_engine::GxMachineBase& machine, string id) {
    if (!machine.parameter_hasId(id)) {
	printf("not found: %s\n", id.c_str());
        return false;
    }
    return true;
}

GtkWidget *UiRegler::create(gx_engine::GxMachineBase& machine, Gxw::Regler *regler, string id, bool show_value) {
    if (!hasId(machine, id)) {
        return 0;
    }
    return (new UiRegler(machine, machine.get_parameter(id).getFloat(), regler, show_value))->get_widget();
}

UiRegler::UiRegler(gx_engine::GxMachineBase &machine, gx_engine::FloatParameter &param, Gxw::Regler *regler, bool show_value):
    gx_ui::GxUiItemFloat(&machine.get_ui(), &param.get_value()),
    Gtk::Adjustment(param.get_value(), param.lower, param.upper, param.step, 10*param.step, 0),
    m_regler(regler),
    log_display(param.is_log_display()) {
    if (log_display) {
	double up = log10(param.upper);
	double step = log10(param.step);
	configure(log10(param.get_value()), log10(param.lower), up, step, 10*step, 0);
	int prec = 0;
	float d = log10((param.step-1)*param.upper);
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
    if (log_display) {
	set_value(log10(param.get_value()));
    } else {
	set_value(param.get_value());
    }
    m_regler->show();
    m_regler->get_accessible()->set_description (param.id().c_str());
    m_regler->get_accessible()->set_name (param.id().substr( param.id().find_last_of(".")+1).c_str());
    connect_midi_controller(m_regler, param.id().c_str(), machine);
}

UiRegler::~UiRegler() {
    delete m_regler;
}

UiSelectorBase::UiSelectorBase(gx_engine::Parameter& param)
    : m_selector() {
    m_selector.show();
    m_selector.cp_set_var(param.id());
    Gtk::TreeModelColumn<Glib::ustring> label;
    Gtk::TreeModelColumnRecord rec;
    rec.add(label);
    Glib::RefPtr<Gtk::ListStore> ls = Gtk::ListStore::create(rec);
    for (const value_pair *p = param.getValueNames(); p->value_id; ++p) {
        ls->append()->set_value(0, Glib::ustring(param.value_label(*p)));
    }
    m_selector.set_model(ls);
    m_selector.set_has_tooltip();
    string tip = param.desc();
    if (param.desc().empty()) {
	tip = param.id().substr(param.id().find_last_of(".")+1);
    }
    m_selector.set_tooltip_text(tip);
    m_selector.get_accessible()->set_description (param.id().c_str());
    m_selector.get_accessible()->set_name (param.id().substr( param.id().find_last_of(".")+1).c_str());
}

template <>
UiSelector<float>::UiSelector(gx_engine::GxMachineBase& machine, gx_engine::ParameterV<float> &param)
    : UiSelectorBase(param),
      gx_ui::GxUiItemV<float>(&machine.get_ui(), &param.get_value()),
      Gtk::Adjustment(param.std_value, param.lower, param.upper, param.step, 10*param.step, 0) {
    m_selector.set_adjustment(*this);
    set_value(param.get_value());
    connect_midi_controller(&m_selector, param.id().c_str(), machine);
}

template <>
UiSelector<int>::UiSelector(gx_engine::GxMachineBase& machine, gx_engine::ParameterV<int> &param)
    : UiSelectorBase(param),
      gx_ui::GxUiItemV<int>(&machine.get_ui(), &param.get_value()),
      Gtk::Adjustment(param.std_value, param.lower, param.upper, 1, 5, 0) {
    m_selector.set_adjustment(*this);
    set_value(param.get_value());
    connect_midi_controller(&m_selector, param.id().c_str(), machine);
}

template <>
UiSelector<unsigned int>::UiSelector(gx_engine::GxMachineBase& machine, gx_engine::ParameterV<unsigned int> &param)
    : UiSelectorBase(param),
      gx_ui::GxUiItemV<unsigned int>(&machine.get_ui(), &param.get_value()),
      Gtk::Adjustment(param.std_value, param.lower, param.upper, 1, 5, 0) {
    m_selector.set_adjustment(*this);
    set_value(param.get_value());
    connect_midi_controller(&m_selector, param.id().c_str(), machine);
}

template <class T>
void UiSelector<T>::on_value_changed() {
    this->modifyZone(get_value());
}

template <class T>
void UiSelector<T>::reflectZone() {
    T v = *gx_ui::GxUiItemV<T>::fZone;
    gx_ui::GxUiItemV<T>::fCache = v;
    set_value(v);
}

GtkWidget* UiReglerWithCaption::create(gx_engine::GxMachineBase& machine, Gxw::Regler *regler,
           string id, bool show_value) {
    if (!hasId(machine, id)) {
        return 0;
    }
    return create(machine, regler, id, machine.get_parameter(id).l_name(), show_value);
}

GtkWidget* UiReglerWithCaption::create(gx_engine::GxMachineBase& machine, Gxw::Regler *regler,
           string id, Glib::ustring label, bool show_value) {
    if (!hasId(machine, id)) {
        return 0;
    }
    return (new UiReglerWithCaption(machine, machine.get_parameter(id).getFloat(), regler, label, show_value))->get_widget();
}

GtkWidget* UiRackReglerWithCaption::create(gx_engine::GxMachineBase& machine, Gxw::Regler *regler, string id) {
    if (!hasId(machine, id)) {
        return 0;
    }
    return create(machine, regler, id, machine.get_parameter(id).l_name());
}

GtkWidget* UiRackReglerWithCaption::create(gx_engine::GxMachineBase& machine, Gxw::Regler *regler,
                                           string id, Glib::ustring label) {
    if (!hasId(machine, id)) {
        return 0;
    }
    return (new UiRackReglerWithCaption(machine, machine.get_parameter(id).getFloat(), regler,
            label))->get_widget();
}

GtkWidget* UiRackRegler::create(gx_engine::GxMachineBase& machine, Gxw::Regler *regler, string id) {
    if (!hasId(machine, id)) {
        return 0;
    }
    return create(machine, regler, id, machine.get_parameter(id).l_name());
}

GtkWidget* UiRackRegler::create(gx_engine::GxMachineBase& machine, Gxw::Regler *regler,
                                string id, Glib::ustring label) {
    if (!hasId(machine, id)) {
        return 0;
    }
    return (new UiRackRegler(machine, machine.get_parameter(id).getFloat(), regler, label))->get_widget();
}

GtkWidget* UiRackMasterRegler::create(gx_engine::GxMachineBase& machine, Gxw::Regler *regler,
                                string id, Glib::ustring label) {
    if (!hasId(machine, id)) {
        return 0;
    }
    return (new UiRackMasterRegler(machine, machine.get_parameter(id).getFloat(), regler, label))->get_widget();
}

GtkWidget* UiRackMasterRegler::create(gx_engine::GxMachineBase& machine, Gxw::Regler *regler, string id) {
    if (!hasId(machine, id)) {
        return 0;
    }
    return create(machine, regler, id, machine.get_parameter(id).l_name());
}

UiReglerWithCaption::UiReglerWithCaption(gx_engine::GxMachineBase& machine,
                    gx_engine::FloatParameter &param, Gxw::Regler *regler,
                    Glib::ustring label, bool show_value)
    : UiRegler(machine, param, regler, show_value) {
    m_label.set_text(label);
    m_label.set_name("effekt_label");
    m_box.set_name(param.id());
    m_box.pack_start(m_label, Gtk::PACK_SHRINK);
    m_box.pack_start(*m_regler, Gtk::PACK_SHRINK);
    set_accessible(GTK_WIDGET(m_regler->gobj()),m_label.gobj());
    m_box.show_all();
}

UiRackReglerWithCaption::UiRackReglerWithCaption(gx_engine::GxMachineBase& machine,
                         gx_engine::FloatParameter &param, Gxw::Regler *regler,
                         Glib::ustring label)
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
    set_accessible(GTK_WIDGET(m_regler->gobj()),m_label.gobj());
    m_box.show_all();
}

UiRackRegler::UiRackRegler(gx_engine::GxMachineBase& machine, gx_engine::FloatParameter &param, Gxw::Regler *regler,
    Glib::ustring label)
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
                         Glib::ustring label)
    : UiRegler(machine, param, regler, false) {
    m_label.set_text(label+" "); //FIXME: font bug, add space to avoid cut off on the right
    m_label.set_name("rack_label");
    m_label.set_size_request(-1,12);
    m_box.set_name(param.id());
    m_box.set_spacing(4);
    m_box.pack_start(*m_regler, Gtk::PACK_SHRINK);
    m_box.pack_start(m_label, Gtk::PACK_SHRINK);
    set_accessible(GTK_WIDGET(m_regler->gobj()),m_label.gobj());
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
    modifyZone(get_active());
}

void UiSwitchFloat::reflectZone() {
    float v = *fZone;
    fCache = v;
    set_active(v != 0.0);
}

UiSwitchFloat::UiSwitchFloat(gx_engine::GxMachineBase& machine, const char *sw_type, gx_engine::FloatParameter &param)
    : UiSwitch(sw_type),
      gx_ui::GxUiItemFloat(&machine.get_ui(), &param.get_value()) {
    set_active(param.get_value() != 0.0);
    cp_set_var(param.id());
    this->set_has_tooltip();
    string tip = param.desc();
    if (param.desc().empty()) {
	tip = param.id().substr(param.id().find_last_of(".")+1);
    }
    this->set_tooltip_text(tip);
    this->get_accessible()->set_description (param.id().c_str());
    this->get_accessible()->set_name (param.id().substr(
          param.id().find_last_of(".")+1).c_str());
    connect_midi_controller(this, param.id().c_str(), machine);
    show();
}

void UiSwitchBool::on_toggled() {
    modifyZone(get_active());
}

void UiSwitchBool::reflectZone() {
    bool v = *fZone;
    fCache = v;
    set_active(v);
}

UiSwitchBool::UiSwitchBool(gx_engine::GxMachineBase& machine, const char *sw_type, gx_engine::BoolParameter &param)
    : UiSwitch(sw_type),
      gx_ui::GxUiItemBool(&machine.get_ui(), &param.get_value()) {
    set_active(param.get_value());
    cp_set_var(param.id());
    this->set_has_tooltip();
    string tip = param.desc();
    if (param.desc().empty()) {
	tip = param.id().substr(param.id().find_last_of(".")+1);
    }
    this->set_tooltip_text(tip);
    this->get_accessible()->set_description (param.id().c_str());
    this->get_accessible()->set_name 
          (param.id().substr( param.id().find_last_of(".")+1).c_str());
    connect_midi_controller(this, param.id().c_str(), machine);
    show();
}

GtkWidget* UiSwitchWithCaption::create(
    gx_engine::GxMachineBase& machine, const char *sw_type, string id, Gtk::PositionType pos) {
    if (!hasId(machine, id)) {
        return 0;
    }
    return create(machine, sw_type, id, machine.get_parameter(id).l_name(), pos);
}

GtkWidget* UiSwitchWithCaption::create(
                                gx_engine::GxMachineBase& machine, const char *sw_type, string id,
                                Glib::ustring label, Gtk::PositionType pos) {
    if (!hasId(machine, id)) {
        return 0;
    }
    return (new UiSwitchWithCaption(machine, sw_type, machine.get_parameter(id),
                                    label, pos))->get_widget();
}

UiSwitchWithCaption::UiSwitchWithCaption(gx_engine::GxMachineBase& machine,
                                         const char *sw_type, gx_engine::Parameter &param,
                                         Glib::ustring label, Gtk::PositionType pos):
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
    set_accessible(GTK_WIDGET(m_switch->gobj()),m_label.gobj());
    m_box->show_all();
}

UiSwitchWithCaption::~UiSwitchWithCaption() {
    delete m_switch;
    delete m_box;
}

}/* end of gx_gui namespace */
