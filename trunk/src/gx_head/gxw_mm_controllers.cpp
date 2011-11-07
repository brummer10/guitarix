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
#include <gxw/GxControlParameter.h>      // NOLINT

/****************************************************************
 ** fixup_controlparameters()
 ** helper function to initialize widgets which are linked to a
 ** variable name (via ControlParameter interface):
 ** set range, title and initial value from parameter table,
 ** connect uiItem and Midi learn
 */

namespace Glib { namespace Container_Helpers {
template <>
struct TypeTraits<GObject*> {
    typedef GObject *CppType;
    typedef GObject *CType;
    typedef GObject *CTypeNonConst;

    static CType to_c_type(CppType item) { return item; }
    static CppType to_cpp_type(CType item) { return item; }
    static void release_c_type(CType) {}
};
}} // end namespace Glib::Container_Helpers

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
    modifyZone(get_value());
}

void UiRegler::reflectZone() {
    float     v = *fZone;
    fCache = v;
    set_value(v);
}

static bool hasId(string id) {
    if (!parameter_map.hasId(id)) {
	printf("not found: %s\n", id.c_str());
        return false;
    }
    return true;
}

GtkWidget *UiRegler::create(gx_ui::GxUI& ui, Gxw::Regler *regler, string id, bool show_value) {
    if (!hasId(id)) {
        return 0;
    }
    return (new UiRegler(ui, parameter_map[id].getFloat(), regler, show_value))->get_widget();
}

UiRegler::UiRegler(gx_ui::GxUI &ui, FloatParameter &param, Gxw::Regler *regler, bool show_value):
    gx_ui::GxUiItemFloat(&ui, &param.value),
    Gtk::Adjustment(param.std_value, param.lower, param.upper, param.step, 10*param.step, 0),
    m_regler(regler) {
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
    m_regler->show();
    m_regler->get_accessible()->set_description (param.id().c_str());
    m_regler->get_accessible()->set_name (param.id().substr( param.id().find_last_of(".")+1).c_str());
    
    param.value = param.std_value;
    connect_midi_controller(GTK_WIDGET(m_regler->gobj()), &param.value);
}

UiRegler::~UiRegler() {
    delete m_regler;
}

UiSelector::UiSelector() {
    m_selector.show();
}

void UiSelectorFloat::on_value_changed() {
    modifyZone(get_value());
}

void UiSelectorInt::on_value_changed() {
    modifyZone((int)get_value());
}

GtkWidget* UiSelector::create(gx_ui::GxUI& ui, string id, const char *widget_name) {
    Parameter& p = parameter_map[id];
    UiSelector *s;
    if (p.isFloat()) {
        s = new UiSelectorFloat(ui, p.getFloat());
    } else {
        s = new UiSelectorInt(ui, p.getInt());
    }
    if (widget_name) {
	s->m_selector.set_name(widget_name);
    }
    return s->get_widget();
}

void UiSelector::init(Parameter& param) {
    m_selector.cp_set_var(param.id());
    Gtk::TreeModelColumn<Glib::ustring> label;
    Gtk::TreeModelColumnRecord rec;
    rec.add(label);
    Glib::RefPtr<Gtk::ListStore> ls = Gtk::ListStore::create(rec);
    for (const value_pair *p = param.getValueNames(); p->value_id; ++p) {
        ls->append()->set_value(0, Glib::ustring(param.value_label(*p)));
    }
    m_selector.set_model(ls);
}

UiSelectorFloat::UiSelectorFloat(gx_ui::GxUI& ui, FloatParameter &param)
    : gx_ui::GxUiItemFloat(&ui, &param.value),
    Gtk::Adjustment(param.std_value, param.lower, param.upper, param.step, 10*param.step, 0) {
    m_selector.set_adjustment(*this);
    init(param);
    m_selector.get_accessible()->set_description (param.id().c_str());
    m_selector.get_accessible()->set_name (param.id().substr( param.id().find_last_of(".")+1).c_str());
    connect_midi_controller(GTK_WIDGET(m_selector.gobj()), fZone);
}

void UiSelectorFloat::reflectZone() {
    float v = *fZone;
    fCache = v;
    set_value(v);
}

void UiSelectorInt::reflectZone() {
    int v = *fZone;
    fCache = v;
    set_value(v);
}

UiSelectorInt::UiSelectorInt(gx_ui::GxUI& ui, IntParameter &param)
    : gx_ui::GxUiItemInt(&ui, &param.value),
    Gtk::Adjustment(param.std_value, param.lower, param.upper, 1, 5, 0) {
    m_selector.set_adjustment(*this);
    init(param);
    m_selector.get_accessible()->set_description (param.id().c_str());
    m_selector.get_accessible()->set_name (param.id().substr( param.id().find_last_of(".")+1).c_str());
    connect_midi_controller(GTK_WIDGET(m_selector.gobj()), fZone);
}

GtkWidget* UiReglerWithCaption::create(gx_ui::GxUI& ui, Gxw::Regler *regler,
           string id, bool show_value) {
    if (!hasId(id)) {
        return 0;
    }
    return create(ui, regler, id, parameter_map[id].l_name(), show_value);
}

GtkWidget* UiReglerWithCaption::create(gx_ui::GxUI& ui, Gxw::Regler *regler,
           string id, Glib::ustring label, bool show_value) {
    if (!hasId(id)) {
        return 0;
    }
    return (new UiReglerWithCaption(ui, parameter_map[id].getFloat(), regler, label, show_value))->get_widget();
}

GtkWidget* UiRackReglerWithCaption::create(gx_ui::GxUI& ui, Gxw::Regler *regler, string id) {
    if (!hasId(id)) {
        return 0;
    }
    return create(ui, regler, id, parameter_map[id].l_name());
}

GtkWidget* UiRackReglerWithCaption::create(gx_ui::GxUI& ui, Gxw::Regler *regler,
                                           string id, Glib::ustring label) {
    if (!hasId(id)) {
        return 0;
    }
    return (new UiRackReglerWithCaption(ui, parameter_map[id].getFloat(), regler,
            label))->get_widget();
}

GtkWidget* UiRackRegler::create(gx_ui::GxUI& ui, Gxw::Regler *regler, string id) {
    if (!hasId(id)) {
        return 0;
    }
    return create(ui, regler, id, parameter_map[id].l_name());
}

GtkWidget* UiRackRegler::create(gx_ui::GxUI& ui, Gxw::Regler *regler,
                                string id, Glib::ustring label) {
    if (!hasId(id)) {
        return 0;
    }
    return (new UiRackRegler(ui, parameter_map[id].getFloat(), regler, label))->get_widget();
}
UiReglerWithCaption::UiReglerWithCaption(gx_ui::GxUI &ui,
                    FloatParameter &param, Gxw::Regler *regler,
                    Glib::ustring label, bool show_value)
    : UiRegler(ui, param, regler, show_value) {
    m_label.set_text(label);
    m_label.set_name("effekt_label");
    m_box.set_name(param.id());
    m_box.pack_start(m_label, Gtk::PACK_SHRINK);
    m_box.pack_start(*m_regler, Gtk::PACK_SHRINK);
    set_accessible(GTK_WIDGET(m_regler->gobj()),m_label.gobj());
    m_box.show_all();
}

UiRackReglerWithCaption::UiRackReglerWithCaption(gx_ui::GxUI &ui,
                         FloatParameter &param, Gxw::Regler *regler,
                         Glib::ustring label)
    : UiRegler(ui, param, regler, true) {
    m_label.set_text(label);
    m_label.set_name("rack_label");
    m_box.set_name(param.id());
    m_box.pack_start(m_label, Gtk::PACK_SHRINK);
    m_box.pack_start(*m_regler, Gtk::PACK_SHRINK);
    set_accessible(GTK_WIDGET(m_regler->gobj()),m_label.gobj());
    m_box.show_all();
}

UiRackRegler::UiRackRegler(gx_ui::GxUI &ui, FloatParameter &param, Gxw::Regler *regler,
    Glib::ustring label)
    : UiRegler(ui, param, regler, true) {
    m_box.set_name(param.id());
    m_box.pack_start(*m_regler, Gtk::PACK_SHRINK);
    m_regler->set_name("rack_regler");
    m_regler->get_accessible()->set_description (param.id().c_str());
    m_regler->get_accessible()->set_name (param.id().substr(
              param.id().find_last_of(".")+1).c_str());
    m_box.show_all();
}

UiSwitch::UiSwitch(const char *sw_type):
    Switch(sw_type) {
}

UiSwitch *UiSwitch::new_switch(gx_ui::GxUI& ui, const char* sw_type, Parameter& param) {
    if (param.isFloat()) {
        return new UiSwitchFloat(ui, sw_type, param.getFloat());
    } else {
        return new UiSwitchBool(ui, sw_type, param.getBool());
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

UiSwitchFloat::UiSwitchFloat(gx_ui::GxUI& ui, const char *sw_type, FloatParameter &param)
    : UiSwitch(sw_type),
    gx_ui::GxUiItemFloat(&ui, &param.value) {
    param.set_std_value();
    set_active(param.value != 0.0);
    cp_set_var(param.id());
    this->set_tooltip_text(param.id().substr( param.id().find_last_of(".")+1).c_str());
    this->get_accessible()->set_description (param.id().c_str());
    this->get_accessible()->set_name (param.id().substr(
          param.id().find_last_of(".")+1).c_str());
    connect_midi_controller(GTK_WIDGET(gobj()), fZone);
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

UiSwitchBool::UiSwitchBool(gx_ui::GxUI& ui, const char *sw_type, BoolParameter &param)
    : UiSwitch(sw_type),
    gx_ui::GxUiItemBool(&ui, &param.value) {
    param.set_std_value();
    set_active(param.value);
    cp_set_var(param.id());
    char s[64];
    snprintf(s, 63, _("%s on/off"),param.l_group().c_str());
    this->set_tooltip_text(s);
    this->get_accessible()->set_description (param.id().c_str());
    this->get_accessible()->set_name 
          (param.id().substr( param.id().find_last_of(".")+1).c_str());
    connect_midi_controller(GTK_WIDGET(gobj()), fZone);
    show();
}

GtkWidget* UiSwitchWithCaption::create(
    gx_ui::GxUI& ui, const char *sw_type, string id, Gtk::PositionType pos) {
    if (!hasId(id)) {
        return 0;
    }
    return create(ui, sw_type, id, parameter_map[id].l_name(), pos);
}

GtkWidget* UiSwitchWithCaption::create(
                                gx_ui::GxUI& ui, const char *sw_type, string id,
                                Glib::ustring label, Gtk::PositionType pos) {
    if (!hasId(id)) {
        return 0;
    }
    return (new UiSwitchWithCaption(ui, sw_type, parameter_map[id],
                                    label, pos))->get_widget();
}

UiSwitchWithCaption::UiSwitchWithCaption(gx_ui::GxUI &ui,
                                         const char *sw_type, Parameter &param,
                                         Glib::ustring label, Gtk::PositionType pos):
    m_switch(UiSwitch::new_switch(ui, sw_type, param)) {
    m_label.set_text(label);
    m_label.set_name("effekt_label");
    if (pos == Gtk::POS_LEFT || pos == Gtk::POS_RIGHT) {
        m_box = new Gtk::HBox();
    } else {
        m_box = new Gtk::VBox();
    }
    if (pos == Gtk::POS_LEFT || pos == Gtk::POS_TOP) {
        m_box->pack_start(m_label, Gtk::PACK_SHRINK);
        m_box->pack_start(*m_switch, Gtk::PACK_SHRINK);
    } else {
        m_box->pack_start(*m_switch, Gtk::PACK_SHRINK);
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

void PToggleButton::on_clicked() {
    gx_gui::GxMainInterface& gui = gx_gui::GxMainInterface::get_instance();
    gui.mainmenu.preset_submenu[0].popup(2, gtk_get_current_event_time());
}

PToggleButton::PToggleButton(const char* label):
    m_label(label) {
    Pango::FontDescription font = m_label.get_style()->get_font();
    font.set_size(8*Pango::SCALE);
    font.set_weight(Pango::WEIGHT_BOLD);
    m_label.modify_font(font);
    m_label.set_name("beffekt_label");
    m_label.show();
    button.add(m_label);
    button.signal_clicked().connect(
	sigc::mem_fun(*this, &PToggleButton::on_clicked));
}

/****************************************************************
 ** Load glade file
 */

template<class T>
class uiToggle: public gx_ui::GxUiItemV<T> {
protected:
    Glib::RefPtr<Gtk::ToggleButton> button;
    void on_button_toggled();
    virtual void reflectZone();
public:
    uiToggle(gx_ui::GxUI& ui, Glib::RefPtr<Gtk::ToggleButton>& b, T *zone);
};

template<class T>
uiToggle<T>::uiToggle(gx_ui::GxUI& ui, Glib::RefPtr<Gtk::ToggleButton>& b, T *zone)
    : gx_ui::GxUiItemV<T>(&ui, zone), button(b) {
    button->signal_toggled().connect(sigc::mem_fun(*this, &uiToggle<T>::on_button_toggled));
}

template<class T>
void uiToggle<T>::on_button_toggled() {
    gx_ui::GxUiItemV<T>::modifyZone(button->get_active());
}

template<class T>
void uiToggle<T>::reflectZone() {
    T v = *gx_ui::GxUiItemV<T>::fZone;
    gx_ui::GxUiItemV<T>::fCache = v;
    button->set_active(v);
}

static void fixup_controlparameters(Glib::RefPtr<Gtk::Builder> builder, gx_ui::GxUI& ui) {
    Glib::SListHandle<GObject*> objs = Glib::SListHandle<GObject*>(
        gtk_builder_get_objects(builder->gobj()), Glib::OWNERSHIP_DEEP);
    for (Glib::SListHandle<GObject*>::iterator i = objs.begin(); i != objs.end(); ++i) {
	if (g_type_is_a(G_OBJECT_TYPE(*i), GTK_TYPE_WIDGET)) {
	    const char *id = gtk_buildable_get_name(GTK_BUILDABLE(*i));
	    const char *p = g_strstr_len(id, -1, ":");
	    if (p) {
		gtk_widget_set_name(GTK_WIDGET(*i), p+1);
	    }
	}
        if (!g_type_is_a(G_OBJECT_TYPE(*i), GX_TYPE_CONTROL_PARAMETER)) {
            continue;
        }
        Glib::RefPtr<Gxw::ControlParameter> w = Glib::wrap(GX_CONTROL_PARAMETER(*i), true);
        Glib::ustring v = w->cp_get_var();
        if (v.empty()) {
            continue;
        }
        if (!gx_gui::parameter_map.hasId(v)) {
            gx_system::gx_print_warning("load dialog",
                (boost::format("Parameter variable %1% not found") % v).str());
            continue;
        }
        gx_gui::Parameter& p = gx_gui::parameter_map[v];
        if (!p.desc().empty()) {
            Glib::RefPtr<Gtk::Widget>::cast_dynamic(w)->set_tooltip_text(
		gettext(p.desc().c_str()));
        }
        if (p.isFloat()) {
            gx_gui::FloatParameter &fp = p.getFloat();
            w->cp_configure(p.l_group(), p.l_name(), fp.lower, fp.upper, fp.step);
            w->cp_set_value(fp.value);
            Glib::RefPtr<Gtk::Range> r = Glib::RefPtr<Gtk::Range>::cast_dynamic(w);
            if (r) {
                Gtk::Adjustment *adj = r->get_adjustment();
                gx_gui::uiAdjustment* c = new gx_gui::uiAdjustment(&ui, &fp.value, adj->gobj());
                adj->signal_value_changed().connect(
                    sigc::bind<GtkAdjustment*>(
                        sigc::bind<gpointer>(
                            sigc::ptr_fun(gx_gui::uiAdjustment::changed),
                                         (gpointer)c), adj->gobj()));
            } else {
                Glib::RefPtr<Gtk::ToggleButton> t =
                    Glib::RefPtr<Gtk::ToggleButton>::cast_dynamic(w);
                if (t) {
                    new uiToggle<float>(ui, t, &fp.value);
                }
            }
            if (fp.isControllable()) {
                gx_gui::connect_midi_controller(GTK_WIDGET(w->gobj()), &fp.value);
            }
        } else if (p.isBool()) {
            gx_gui::BoolParameter &fp = p.getBool();
            w->cp_configure(p.l_group(), p.l_name(), 0, 0, 0);
            w->cp_set_value(fp.value);
	    Glib::RefPtr<Gtk::ToggleButton> t =
		Glib::RefPtr<Gtk::ToggleButton>::cast_dynamic(w);
	    if (t) {
		new uiToggle<bool>(ui, t, &fp.value);
	    }
            if (fp.isControllable()) {
                gx_gui::connect_midi_controller(GTK_WIDGET(w->gobj()), &fp.value);
            }
        } else {
            gx_system::gx_print_warning("load dialog",
                      (boost::format("Parameter variable %1%: type not handled") % v).str());
        }
    }
}

Glib::RefPtr<Gtk::Builder> load_builder_from_file(Glib::ustring name, gx_ui::GxUI& ui) {
    Glib::RefPtr<Gtk::Builder> bld = Gtk::Builder::create();
    try {
        bld->add_from_file(gx_system::get_options().get_builder_filepath(name));
    } catch(const Glib::FileError& ex) {
        gx_system::gx_print_error("FileError", ex.what());
    } catch(const Gtk::BuilderError& ex) {
        gx_system::gx_print_error("Builder Error", ex.what());
    }
    fixup_controlparameters(bld, ui);
    return bld;
}

Glib::RefPtr<Gtk::Builder> load_builder_from_data(const char *xmldesc, gx_ui::GxUI& ui) {
    Glib::RefPtr<Gtk::Builder> bld = Gtk::Builder::create();
    try {
	bld->add_from_string(xmldesc, -1);
    } catch(const Glib::FileError& ex) {
        gx_system::gx_print_error("FileError", ex.what());
    } catch(const Gtk::BuilderError& ex) {
        gx_system::gx_print_error("Builder Error", ex.what());
    }
    fixup_controlparameters(bld, ui);
    return bld;
}

}/* end of gx_gui namespace */

