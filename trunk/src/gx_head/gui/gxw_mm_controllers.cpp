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
// -------------------------- gxwmm library controllers -----------------------------------

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

CpBase::CpBase() {}

void CpBase::init(Gxw::Regler& regler, bool show_value) {
    regler.set_show_value(show_value);
    regler.set_name("regler");
    regler.show();
}

CpBase::~CpBase() {
}

CpBaseCaption::CpBaseCaption()
    : Gtk::VBox(),
      base(),
      m_label() {
}

CpBaseCaption::~CpBaseCaption() {
}

void CpBaseCaption::init(Gxw::Regler& regler, bool show_value) {
    regler.set_label_ref(&m_label);
    base.init(regler, show_value);
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

void CpBaseCaption::set_rack_label_inverse(const char *label) {
    if (label) {
	m_label.set_text(label);
    }
    m_label.set_name("rack_label_inverse");
    m_label.set_justify(Gtk::JUSTIFY_CENTER);
}

CpMasterCaption::CpMasterCaption()
    : Gtk::HBox(),
      base(),
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

CpBaseCaptionBoxed::CpBaseCaptionBoxed()
    : Gtk::VBox(),
      base(),
      h_box(),
      m_label() {
}

CpBaseCaptionBoxed::~CpBaseCaptionBoxed() {
}

void CpBaseCaptionBoxed::init(Gxw::Regler& regler, bool show_value) {
    regler.set_label_ref(&m_label);
    base.init(regler, show_value);
    m_label.set_justify(Gtk::JUSTIFY_CENTER);
    pack_start(m_label, Gtk::PACK_SHRINK);
    h_box.pack_start(regler, Gtk::PACK_EXPAND_PADDING);
    pack_start(h_box, Gtk::PACK_EXPAND_PADDING);
    set_accessible(regler, m_label);
    show_all();
}

void CpBaseCaptionBoxed::set_rack_label(const char *label) {
    if (label) {
    m_label.set_name("rack_label");
	m_label.set_text(label);
    }
}

void CpBaseCaptionBoxed::set_rack_label_inverse(const char *label) {
    if (label) {
    m_label.set_name("rack_label_inverse");
	m_label.set_text(label);
    }
}


/****************************************************************
 ** class UiSwitchXX
 */

UiVSwitchWithCaption::UiVSwitchWithCaption(
    const char *sw_type, gx_engine::Parameter &param, const char *label)
    : Gtk::VBox(),
      m_hbox(),
      m_hbox1(),
      m_hbox2(),
      m_label(label ? label : param.l_name()),
      m_switch(sw_type) {
    m_label.set_name("rack_label");
    m_label.set_justify(Gtk::JUSTIFY_CENTER);
    pack_start(m_label, Gtk::PACK_SHRINK);
    pack_start(m_hbox, Gtk::PACK_EXPAND_PADDING);
    m_hbox.pack_start(m_hbox1, Gtk::PACK_EXPAND_PADDING);
    m_hbox.pack_start(m_switch, Gtk::PACK_SHRINK);
    m_hbox.pack_start(m_hbox2, Gtk::PACK_EXPAND_PADDING);
    //set_name(param.id()); //FIXME
    set_accessible(m_switch, m_label);
    show_all();
}

UiSelectorWithCaption::UiSelectorWithCaption(const char *label)
    : Gtk::VBox(), m_selector(), m_label() {
    if (label) { //FIXME
	m_label.set_text(label);
    }
    m_label.set_name("rack_label");
    m_label.set_justify(Gtk::JUSTIFY_CENTER);
    //Gtk::VBox::set_name(id); FIXME
    pack_start(m_label, Gtk::PACK_SHRINK);
    pack_start(m_selector, Gtk::PACK_EXPAND_PADDING);
    set_accessible(m_selector, m_label);
    show_all();
}

}/* end of gx_gui namespace */
