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
 *    This is the gx_head GUI main class
 *
 * ----------------------------------------------------------------------------
 */

#include "guitarix.h"         // NOLINT

#include <iomanip>            // NOLINT
#include <cstring>            // NOLINT
#include <string>             // NOLINT
#include <boost/algorithm/string/replace.hpp>
#include <gxw/GxControlParameter.h>

namespace gx_gui {

/* ----- load a top level window from gtk builder file ------ */

GtkWidget *load_toplevel(GtkBuilder *builder, const char* filename, const char* windowname) {
    string fname = gx_system::get_options().get_builder_filepath(filename);
    GError *err = NULL;
    if (!gtk_builder_add_from_file(builder, fname.c_str(), &err)) {
        g_object_unref(G_OBJECT(builder));
        gx_print_fatal(_("gtk builder"), err->message);
        g_error_free(err);
        return NULL;
    }
    GtkWidget *w = GTK_WIDGET(gtk_builder_get_object(builder, windowname));
    if (!w) {
        g_object_unref(G_OBJECT(builder));
        gx_print_fatal(_("gtk builder"), string(windowname)+_(" not found in ")+fname);
        return NULL;
    }
    gtk_builder_connect_signals(builder, 0);
    return w;
}

/****************************************************************
 ** UiBuilder implementation
 */

StackBoxBuilder *UiBuilderImpl::intf = 0;

UiBuilderImpl::UiBuilderImpl(PluginDict *i, StackBoxBuilder *b, std::vector<PluginUI*> *pl, PluginUI *pluginui)
      : UiBuilderBase(), plugin_dict(*i), pluginlist(pl) {
    intf = b;
    intf->set_current_plugin(pluginui);
    openTabBox = openTabBox_;
    openVerticalBox = openVerticalBox_;
    openVerticalBox1 = openVerticalBox1_;
    openVerticalBox2 = openVerticalBox2_;
    openHorizontalBox = openHorizontalBox_;
    openHorizontalhideBox = openHorizontalhideBox_;
    openHorizontalTableBox = openHorizontalTableBox_;
    openFrameBox = openFrameBox_;
    openFlipLabelBox = openFlipLabelBox_;
    openpaintampBox = openpaintampBox_;
    closeBox = closeBox_;
    load_glade = load_glade_;
    load_glade_file = load_glade_file_;
    create_master_slider = create_master_slider_;
    create_feedback_slider = create_feedback_slider_;
    create_mid_rackknob = create_mid_rackknob_;
    create_small_rackknob = create_small_rackknob_;
    create_small_rackknobr = create_small_rackknobr_;
    create_big_rackknob = create_big_rackknob_;
    create_spin_value = create_spin_value_;
    create_switch = create_switch_;
    create_switch_no_caption = create_switch_no_caption_;
    create_feedback_switch = create_feedback_switch_;
    create_fload_switch = create_fload_switch_;
    create_wheel = create_wheel_;
    create_selector = create_selector_;
    create_simple_meter = create_simple_meter_;
    create_simple_c_meter = create_simple_c_meter_;
    create_selector_no_caption = create_selector_no_caption_;
    create_port_display = create_port_display_;
    create_p_display = create_p_display_;
    create_simple_spin_value = create_simple_spin_value_;
    create_eq_rackslider_no_caption = create_eq_rackslider_no_caption_;
    set_next_flags = set_next_flags_;
    insertSpacer = insertSpacer_;
};

UiBuilderImpl::~UiBuilderImpl() {
    intf->set_current_plugin(nullptr);
}

bool UiBuilderImpl::load_unit(PluginDef *pd) {
    if (!pd->load_ui) {
	return false;
    }
    intf->prepare();
    plugin = pd;
    int form = UI_FORM_GLADE|UI_FORM_STACK;
#ifndef NDEBUG
    if (getenv("GUITARIX_FORM_STACK")) {
        form = UI_FORM_STACK;
    }
#endif
    pd->load_ui(*this, form);
    return true;
}

void UiBuilderImpl::openTabBox_(const char* label) {
    intf->openTabBox(label);
}

void UiBuilderImpl::openVerticalBox_(const char* label) {
    intf->openVerticalBox(label);
}

void UiBuilderImpl::openVerticalBox1_(const char* label) {
    intf->openVerticalBox1(label);
}

void UiBuilderImpl::openVerticalBox2_(const char* label) {
    intf->openVerticalBox2(label);
}

void UiBuilderImpl::openHorizontalhideBox_(const char* label) {
    intf->openHorizontalhideBox(label);
}

void UiBuilderImpl::openHorizontalTableBox_(const char* label) {
    intf->openHorizontalTableBox(label);
}

void UiBuilderImpl::openHorizontalBox_(const char* label) {
    intf->openHorizontalBox(label);
}

void UiBuilderImpl::openFrameBox_(const char* label) {
    intf->openFrameBox(label);
}

void UiBuilderImpl::openFlipLabelBox_(const char* label) {
    intf->openFlipLabelBox(label);
}

void UiBuilderImpl::openpaintampBox_(const char* label) {
    intf->openpaintampBox(label);
}

void UiBuilderImpl::insertSpacer_() {
    intf->insertSpacer();
}

void UiBuilderImpl::set_next_flags_(int flags) {
    intf->set_next_flags(flags);
}

void UiBuilderImpl::create_mid_rackknob_(const char *id, const char *label) {
    intf->create_mid_rackknob(id, label);
}

void UiBuilderImpl::create_small_rackknob_(const char *id, const char *label) {
    intf->create_small_rackknob(id, label);
}

void UiBuilderImpl::create_small_rackknobr_(const char *id, const char *label) {
    intf->create_small_rackknobr(id, label);
}

void UiBuilderImpl::create_big_rackknob_(const char *id, const char *label) {
    intf->create_big_rackknob(id, label);
}

void UiBuilderImpl::create_master_slider_(const char *id, const char *label) {
    intf->create_master_slider(id, label);
}

void UiBuilderImpl::create_feedback_slider_(const char *id, const char *label) {
    intf->create_feedback_slider(id, label);
}

void UiBuilderImpl::create_selector_no_caption_(const char *id) {
    intf->create_selector(id, "");
}

void UiBuilderImpl::create_selector_(const char *id, const char *label) {
    intf->create_selector_with_caption(id, label);
}

void UiBuilderImpl::create_simple_meter_(const char *id) {
    intf->create_simple_meter(id);
}

void UiBuilderImpl::create_simple_c_meter_(const char *id, const char *idl, const char *label) {
    intf->create_simple_c_meter(id, idl, label);
}

void UiBuilderImpl::create_spin_value_(const char *id, const char *label) {
    intf->create_spin_value(id, label);
}

void UiBuilderImpl::create_switch_no_caption_(const char *sw_type, const char * id) {
    intf->create_switch_no_caption(sw_type, id);
}

void UiBuilderImpl::create_feedback_switch_(const char *sw_type, const char * id) {
    intf->create_feedback_switch(sw_type, id);
}

void UiBuilderImpl::create_fload_switch_(const char *sw_type, const char * id, const char * idf) {
    intf->create_fload_switch(sw_type, id, idf);
}

void UiBuilderImpl::create_switch_(const char *sw_type, const char * id, const char *label) {
    intf->create_v_switch(sw_type, id, label);
}

void UiBuilderImpl::create_wheel_(const char * id, const char *label) {
    intf->create_wheel(id, label);
}

void UiBuilderImpl::create_port_display_(const char *id, const char *label) {
    intf->create_port_display(id, label);
}

void UiBuilderImpl::create_p_display_(const char *id, const char *idl, const char *idh) {
    intf->create_p_display(id, idl, idh);
}

void UiBuilderImpl::create_simple_spin_value_(const char *id) {
    intf->create_simple_spin_value(id);
}

void UiBuilderImpl::create_eq_rackslider_no_caption_(const char *id) {
    intf->create_eq_rackslider_no_caption(id);
}

void UiBuilderImpl::closeBox_() {
    intf->closeBox();
}

void UiBuilderImpl::load_glade_(const char *data) {
    intf->loadRackFromGladeData(data);
}

void UiBuilderImpl::load_glade_file_(const char *fname) {
    intf->loadRackFromGladeFile(fname);
}

bool UiBuilderImpl::load(gx_engine::Plugin *p) {
    PluginDef *pd = p->get_pdef();
    if (!(pd->flags & PGN_GUI) || !(pd->flags & gx_engine::PGNI_DYN_POSITION)) {
	return false;
    }
    plugin_dict.add_plugin(*pluginlist, pd->id, "");
    return true;
}

} /* end of gx_gui namespace */

/****************************************************************
 ** class GxBuilder
 */

// GList(GObject*) helper class must be defined in other namespace
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
}}

namespace gx_gui {

bool GxBuilder::show_tooltips = true;

//static
Glib::RefPtr<GxBuilder> GxBuilder::create_from_file(
    const std::string& filename, gx_engine::GxMachineBase* pmach, const char* object_id, sigc::signal<void(bool)> *out_ctr) {
    Glib::RefPtr<GxBuilder> builder = GxBuilder::create();
    try {
	if (object_id) {
	    builder->add_from_file(filename, object_id);
	} else {
	    builder->add_from_file(filename);
	}
    } catch(const Glib::FileError& ex) {
        gx_print_fatal("FileError", ex.what());
    } catch(const Gtk::BuilderError& ex) {
        gx_print_fatal("Builder Error", ex.what());
    }
    if (pmach) {
	builder->fixup_controlparameters(*pmach, out_ctr);
    }
    return builder;
}

//static
Glib::RefPtr<GxBuilder> GxBuilder::create_from_file(
    const std::string& filename, gx_engine::GxMachineBase* pmach, const Glib::StringArrayHandle& object_ids, sigc::signal<void(bool)> *out_ctr) {
    Glib::RefPtr<GxBuilder> builder = GxBuilder::create();
    try {
	builder->add_from_file(filename, object_ids);
    } catch(const Glib::FileError& ex) {
        gx_print_fatal("FileError", ex.what());
    } catch(const Gtk::BuilderError& ex) {
        gx_print_fatal("Builder Error", ex.what());
    }
    if (pmach) {
	builder->fixup_controlparameters(*pmach, out_ctr);
    }
    return builder;
}

//static
Glib::RefPtr<GxBuilder> GxBuilder::create_from_string(
    const Glib::ustring& buffer, gx_engine::GxMachineBase* pmach, const char* object_id, sigc::signal<void(bool)> *out_ctr) {
    Glib::RefPtr<GxBuilder> builder = GxBuilder::create();
    try {
	if (object_id) {
	    builder->add_from_string(buffer, object_id);
	} else {
	    builder->add_from_string(buffer);
	}
    } catch(const Gtk::BuilderError& ex) {
        gx_print_fatal("Builder Error", ex.what());
    }
    if (pmach) {
	builder->fixup_controlparameters(*pmach, out_ctr);
    }
    return builder;
}

//static
Glib::RefPtr<GxBuilder> GxBuilder::create_from_string(
    const Glib::ustring& buffer, gx_engine::GxMachineBase* pmach, const Glib::StringArrayHandle& object_ids, sigc::signal<void(bool)> *out_ctr) {
    Glib::RefPtr<GxBuilder> builder = GxBuilder::create();
    try {
	builder->add_from_string(buffer, object_ids);
    } catch(const Gtk::BuilderError& ex) {
        gx_print_fatal("Builder Error", ex.what());
    }
    if (pmach) {
	builder->fixup_controlparameters(*pmach, out_ctr);
    }
    return builder;
}

Gtk::Window *GxBuilder::get_first_window() {
    Glib::SListHandle<GObject*> objs = Glib::SListHandle<GObject*>(
	gtk_builder_get_objects(gobj()), Glib::OWNERSHIP_DEEP);
    for (Glib::SListHandle<GObject*>::iterator i = objs.begin(); i != objs.end(); ++i) {
	if (g_type_is_a(G_OBJECT_TYPE(*i), GTK_TYPE_WINDOW)) {
	    return Glib::wrap(GTK_WINDOW(*i), false);
	}
    }
    assert(false);
    return 0;
}

GObject* GxBuilder::get_cobject(const Glib::ustring& name)
{
    GObject *cobject = gtk_builder_get_object (gobj(), name.c_str());
    if(!cobject) {
	g_critical("gtkmm: object `%s' not found in GtkBuilder file.", name.c_str());
	return 0;
    }
    return cobject;
}

/*
 ** GxBuilder::fixup_controlparameters + helper classes
 */

gx_engine::Parameter *check_get_parameter(
    gx_engine::GxMachineBase& machine, const std::string& id, Gtk::Widget *w) {
    if (!machine.parameter_hasId(id)) {
        if (w) {
            w->set_sensitive(0);
            w->set_tooltip_text(id); // always shown
        }
        gx_print_warning(
            "load dialog",
            (boost::format("Parameter variable %1% not found") % id).str());
        return nullptr;
    }
    return &machine.get_parameter(id);
}

gx_engine::FloatParameter *check_get_float_parameter(
    gx_engine::GxMachineBase& machine, const std::string& id, Gtk::Widget *w) {
    gx_engine::Parameter *p = check_get_parameter(machine, id, w);
    if (p) {
        if (p->isFloat()) {
            return &machine.get_parameter(id).getFloat();
        }
        gx_print_error(
            "load dialog",
            Glib::ustring::compose(
                "Continuous Parameter variable %1: type not handled", id));
    }
    return nullptr;
}

/**
 * uiElement: base class for adding signal connections to
 * sigc::trackable derived objects
 *
 * uiElement derived class instances must be allocated with new() and
 * will be deleted when the destructor of the sigc::trackable object
 * is called. This removes all signal connections to member functions
 * of the derived class instance (by uiElement itself being a
 * sigc::trackable).
 */
class uiElement: public sigc::trackable {
private:
    static void *destroy(void *p);
protected:
    uiElement(sigc::trackable *obj) { obj->add_destroy_notify_callback(this, destroy); }
    virtual ~uiElement() {}
};

//static
void *uiElement::destroy(void *p) {
    delete static_cast<uiElement*>(p);
    return nullptr;
}

/**
 * uiConnector: abstract base class
 *
 * does midi controller connection and output variable activation
 *
 * derived classes do signal connections to parameter variables
 */
class uiConnector: public uiElement {
protected:
    gx_engine::GxMachineBase& machine;
    const std::string id;
    void activate_output(bool state, Gtk::Widget *w);
    void activate_enable_output(bool state, Gtk::Widget *w);
    uiConnector(gx_engine::GxMachineBase& machine_, const gx_engine::Parameter& p,
                Gtk::Widget *w, sigc::signal<void(bool)> *out_ctr, bool disable);
};

uiConnector::uiConnector(gx_engine::GxMachineBase& machine_, const gx_engine::Parameter& p,
                         Gtk::Widget *w, sigc::signal<void(bool)> *out_ctr, bool disable)
    : uiElement(w), machine(machine_), id(p.id()) {
    if (p.isControllable()) {
        connect_midi_controller(w, id, machine);
    }
    if (p.isOutput()) {
        if (out_ctr) {
            if (disable) {
                out_ctr->connect(
                    sigc::bind(
                        sigc::mem_fun(this, &uiConnector::activate_enable_output),
                        w));
            } else {
                out_ctr->connect(
                    sigc::bind(
                        sigc::mem_fun(this, &uiConnector::activate_output),
                        w));
            }
        }
    }
}

void uiConnector::activate_output(bool state, Gtk::Widget *w) {
    machine.set_update_parameter(w, id, state);
}

void uiConnector::activate_enable_output(bool state, Gtk::Widget *w) {
    machine.set_update_parameter(w, id, state);
    w->set_sensitive(state);
}

/**
 * uiSelector: signal connections for Gxw::Selector widgets
 */
template <class T>
class uiSelector: public uiConnector {
protected:
    Gtk::Range *rng;
    void on_value_changed();
    void set_value(T v);
    uiSelector(gx_engine::GxMachineBase& machine, Gtk::Range *rng, const gx_engine::Parameter& p,
               sigc::signal<void(bool)> *out_ctr, bool disable);
public:
    static uiSelector *create(
        gx_engine::GxMachineBase& machine, Gtk::Range *rng, const gx_engine::Parameter& p,
        sigc::signal<void(bool)> *out_ctr, bool disable) {
        return new uiSelector(machine, rng, p, out_ctr, disable);
    }
    static uiSelector *create(
        gx_engine::GxMachineBase& machine, Gtk::Range *rng, const std::string& id,
        sigc::signal<void(bool)> *out_ctr, bool disable);
};

template <class T>
uiSelector<T>::uiSelector(gx_engine::GxMachineBase& machine_, Gtk::Range *rng_,
                          const gx_engine::Parameter& p, sigc::signal<void(bool)> *out_ctr,
                          bool disable)
    : uiConnector(machine_, p, rng_, out_ctr, disable), rng(rng_) {
    set_value(machine.get_parameter_value<T>(id));
    rng->signal_value_changed().connect(
	sigc::mem_fun(*this, &uiSelector::on_value_changed));
    machine.signal_parameter_value<T>(id).connect(
	sigc::mem_fun(this, &uiSelector::set_value));
}

//static
template <class T>
uiSelector<T> *uiSelector<T>::create(
    gx_engine::GxMachineBase& machine_, Gtk::Range *rng_, const std::string& id_,
    sigc::signal<void(bool)> *out_ctr, bool disable) {
    auto p = check_get_parameter(machine_, id_, rng_);
    if (!p) {
        return nullptr;
    }
    return new uiSelector<T>(machine_, rng_, p, out_ctr, disable);
}

template <class T>
void uiSelector<T>::set_value(T v) {
    rng->set_value(v);
}

template<class T>
void uiSelector<T>::on_value_changed() {
    machine.set_parameter_value(id, static_cast<T>(rng->get_value()));
}

/**
 * uiToggle: signal connections for Gxw::Switch and Gtk::ToggleButton widgets
 */
template<class T>
class uiToggle: public uiConnector {
protected:
    Gtk::ToggleButton* button;
    void on_button_toggled();
    void on_parameter_changed(T v);
    uiToggle(gx_engine::GxMachineBase& machine, Gtk::ToggleButton *b,
             const gx_engine::Parameter& p, sigc::signal<void(bool)> *out_ctr, bool disable);
public:
    static uiToggle *create(gx_engine::GxMachineBase& machine, Gtk::ToggleButton *b,
                            const gx_engine::Parameter& p, sigc::signal<void(bool)> *out_ctr,
                            bool disable) {
        return new uiToggle(machine, b, p, out_ctr, disable);
    }
    static uiToggle *create(gx_engine::GxMachineBase& machine, Gtk::ToggleButton *b,
                            const string& id, sigc::signal<void(bool)> *out_ctr, bool disable);
};

template<class T>
uiToggle<T>::uiToggle(gx_engine::GxMachineBase& machine_, Gtk::ToggleButton *b,
                      const gx_engine::Parameter& p, sigc::signal<void(bool)> *out_ctr, bool disable)
    : uiConnector(machine_, p, b, out_ctr, disable), button(b) {
    button->set_active(machine.get_parameter_value<T>(id));
    button->signal_toggled().connect(sigc::mem_fun(this, &uiToggle<T>::on_button_toggled));
    machine.signal_parameter_value<T>(id).connect(
        sigc::mem_fun(this, &uiToggle<T>::on_parameter_changed));
}

//static
template<class T>
uiToggle<T> *create(gx_engine::GxMachineBase& machine_, Gtk::ToggleButton *b,
                    const string& id_, sigc::signal<void(bool)> *out_ctr, bool disable) {
    auto p = check_get_parameter(machine_, id_, b);
    if (!p) {
        return nullptr;
    }
    return new uiToggle<T>(machine_, b, p, out_ctr, disable);
}

template<>
inline void uiToggle<float>::on_button_toggled() {
    machine.set_parameter_value(id, static_cast<float>(button->get_active()));
}

template<>
inline void uiToggle<bool>::on_button_toggled() {
    machine.set_parameter_value(id, button->get_active());
}

template<>
inline void uiToggle<float>::on_parameter_changed(float v) {
    button->set_active(v != 0.0);
}

template<>
inline void uiToggle<bool>::on_parameter_changed(bool v) {
    button->set_active(v);
}

/**
 * uiController: signal connections for output widgets (Gxw::Fastmeter, Gxw::PortDisplay)
 */
class uiController: public uiConnector {
protected:
    Gxw::ControlParameter *elem;
    uiController(gx_engine::GxMachineBase& machine, const gx_engine::FloatParameter& p,
                 Gtk::Widget *w, sigc::signal<void(bool)> *out_ctr, bool disable);
public:
    static uiController *create(
        gx_engine::GxMachineBase& machine, const gx_engine::FloatParameter& p,
        Gtk::Widget *w, sigc::signal<void(bool)> *out_ctr, bool disable) {
        return new uiController(machine, p, w, out_ctr, disable);
    }
    static uiController *create(
        gx_engine::GxMachineBase& machine, const std::string& id,
        Gtk::Widget *w, sigc::signal<void(bool)> *out_ctr, bool disable);
};

uiController::uiController(gx_engine::GxMachineBase& machine_, const gx_engine::FloatParameter& p,
                           Gtk::Widget *w, sigc::signal<void(bool)> *out_ctr, bool disable)
    : uiConnector(machine_, p, w, out_ctr, disable),
      elem(dynamic_cast<Gxw::ControlParameter*>(w)) {
    elem->cp_configure(p.l_group(), p.l_name(), p.getLowerAsFloat(),
                       p.getUpperAsFloat(), p.is_log_display());
    elem->cp_set_value(machine.get_parameter_value<float>(id));
    machine.signal_parameter_value<float>(id).connect(
	sigc::mem_fun(elem, &Gxw::ControlParameter::cp_set_value));
}

//static
uiController *uiController::create(
    gx_engine::GxMachineBase& machine_, const std::string& id_,
    Gtk::Widget *w, sigc::signal<void(bool)> *out_ctr, bool disable) {
    gx_engine::FloatParameter *p = check_get_float_parameter(machine_, id_, w);
    if (!p) {
        return nullptr;
    }
    return new uiController(machine_, *p, w, out_ctr, disable);
}

/**
 * uiAdjustment: signal connections to Gxw::Regler derived widgets
 */
class uiAdjustment: public uiConnector {
private:
    Gtk::Adjustment *adj;
    bool log;
    bool blocked;
private:
    void changed();
    void on_parameter_changed(float v);
protected:
    uiAdjustment(gx_engine::GxMachineBase& machine_, const gx_engine::FloatParameter& p,
                 Gxw::Regler *regler, sigc::signal<void(bool)> *out_ctr, bool disable);
public:
    static uiAdjustment *create(
        gx_engine::GxMachineBase& machine_, const gx_engine::FloatParameter& p,
        Gxw::Regler *regler, sigc::signal<void(bool)> *out_ctr, bool disable) {
        return new uiAdjustment(machine_, p, regler, out_ctr, disable);
    }
    static uiAdjustment *create(
        gx_engine::GxMachineBase& machine_, const std::string& id,
        Gxw::Regler *regler, sigc::signal<void(bool)> *out_ctr, bool disable);
};

void uiAdjustment::changed() {
    if (!blocked) {
        float v = adj->get_value();
        if (log) {
            v = pow(10.0, v);
        }
        machine.set_parameter_value(id, v);
    }
}

void uiAdjustment::on_parameter_changed(float v) {
    blocked = true;
    if (log) {
        v = log10(v);
    }
    adj->set_value(v);
    blocked = false;
}

uiAdjustment::uiAdjustment(gx_engine::GxMachineBase& machine_, const gx_engine::FloatParameter& p,
                           Gxw::Regler *regler, sigc::signal<void(bool)> *out_ctr,
                           bool disable)
    : uiConnector(machine_, p, regler, out_ctr, disable), adj(regler->get_adjustment().get()),
      log(false), blocked(false) {
    log = p.is_log_display();
    float v = machine.get_parameter_value<float>(id);
    if (log) {
        v = log10(v);
	double up = log10(p.getUpperAsFloat());
	double step = log10(p.getStepAsFloat());
	regler->cp_configure(p.l_group(), p.l_name(), log10(p.getLowerAsFloat()), up, step);
	int prec = 0;
	float d = log10((p.getStepAsFloat()-1)*p.getUpperAsFloat());
	if (up > 0) {
	    prec = up;
	    if (d < 0) {
		prec -= floor(d);
	    }
	} else if (d < 0) {
	    prec = -floor(d);
	}
	regler->signal_format_value().connect(
	    sigc::bind(
		sigc::ptr_fun(logarithmic_format_value),
		prec));
	regler->signal_input_value().connect(
	    sigc::ptr_fun(logarithmic_input_value));
	regler->cp_set_value(log10(machine.get_parameter_value<float>(id)));
    } else {
	regler->cp_configure(p.l_group(), p.l_name(), p.getLowerAsFloat(),
                          p.getUpperAsFloat(), p.getStepAsFloat());
	regler->cp_set_value(machine.get_parameter_value<float>(id));
    }
    adj->set_value(v);
    machine.signal_parameter_value<float>(id).connect(
        sigc::mem_fun(this, &uiAdjustment::on_parameter_changed));
    adj->signal_value_changed().connect(
        sigc::mem_fun(this, &uiAdjustment::changed));
}

//static
uiAdjustment *uiAdjustment::create(
    gx_engine::GxMachineBase& machine_, const std::string& id_, Gxw::Regler *regler,
    sigc::signal<void(bool)> *out_ctr, bool disable) {
    gx_engine::FloatParameter *p = check_get_float_parameter(machine_, id_, regler);
    if (!p) {
        return nullptr;
    }
    return new uiAdjustment(machine_, *p, regler, out_ctr, disable);
}

void ui_connect_switch(
    gx_engine::GxMachineBase& machine, Gtk::ToggleButton *b,
    const gx_engine::Parameter& p, sigc::signal<void(bool)> *out_ctr, bool disable) {
    auto cp = dynamic_cast<Gxw::ControlParameter*>(b);
    if (cp) {
        cp->cp_configure(p.l_group(), p.l_name(), 0, 0, 0);
    }
    if (p.isFloat()) {
	b->set_active(machine.get_parameter_value<float>(p.id()));
        uiToggle<float>::create(machine, b, p, out_ctr, false);
    } else if (p.isBool()) {
	b->set_active(machine.get_parameter_value<bool>(p.id()));
        uiToggle<bool>::create(machine, b, p, out_ctr, false);
    } else {
	gx_print_error(
	    "load dialog",
	    Glib::ustring::compose("Switch Parameter variable %1: type not handled", p.id()));
    }
}

/**
 * parameter signal connections for Gxw::Switch and Gtk::ToggleButton
 */
bool ui_connect_switch(
    gx_engine::GxMachineBase& machine, Gtk::ToggleButton *b,
    const std::string& id, sigc::signal<void(bool)> *out_ctr, bool disable) {
    gx_engine::Parameter *p = check_get_parameter(machine, id, b);
    if (!p) {
        return false;
    }
    ui_connect_switch(machine, b, *p, out_ctr, disable);
    return true;
}

static void make_switch_controller(gx_engine::GxMachineBase& machine,
                                   Gtk::Widget *w,
                                   const gx_engine::Parameter& p,
                                   sigc::signal<void(bool)> *out_ctr) {
    Gtk::ToggleButton *t = dynamic_cast<Gtk::ToggleButton*>(w);
    if (!t) {
	gx_print_error(
	    "load dialog",
	    Glib::ustring::compose(
                "Switch Parameter variable %1: Widget must be ToggleButton based", p.id()));
        return;
    }
    ui_connect_switch(machine, t, p, out_ctr, false);
}

static void make_continuous_controller(gx_engine::GxMachineBase& machine,
                                       Gtk::Widget* w,
                                       gx_engine::Parameter& p,
                                       sigc::signal<void(bool)> *out_ctr) {
    std::string var_id = p.id();
    if (!p.isFloat()) {
        // show error message
        check_get_float_parameter(machine, var_id, w);
	return;
    }
    gx_engine::FloatParameter &fp = p.getFloat();
    if (dynamic_cast<Gxw::FastMeter*>(w) || dynamic_cast<Gxw::PortDisplay*>(w)) {
        if (!p.isOutput()) {
            gx_print_error(
                "load dialog",
                Glib::ustring::compose(
                    "Parameter variable %1: no output (register with o or O)", var_id));
            return;
        }
        uiController::create(machine, fp, w, out_ctr, true);
        return;
    }
    Gxw::Regler* r = dynamic_cast<Gxw::Regler*>(w);
    if (!r) {
	gx_print_error(
	    "load dialog",
	    Glib::ustring::compose(
                "Continuous Parameter variable %1: Widget must be Regler based", var_id));
	return;
    }
    uiAdjustment::create(machine, fp, r, out_ctr, false);
}

static void make_enum_controller(gx_engine::GxMachineBase& machine,
                                 Gtk::Widget *w,
                                 gx_engine::Parameter& p,
                                 sigc::signal<void(bool)> *out_ctr) {
    Gxw::Selector *t = dynamic_cast<Gxw::Selector*>(w);
    if (!t) {
	gx_print_warning(
	    "load dialog",
	    Glib::ustring::compose("Enum Parameter variable %1: no Selector widget", p.id()));
	make_continuous_controller(machine, w, p, out_ctr);
	return;
    }
    Gtk::TreeModelColumn<Glib::ustring> label;
    Gtk::TreeModelColumnRecord rec;
    rec.add(label);
    Glib::RefPtr<Gtk::ListStore> ls = Gtk::ListStore::create(rec);
    for (const value_pair *vp = p.getValueNames(); vp->value_id; ++vp) {
	ls->append()->set_value(0, Glib::ustring(p.value_label(*vp)));
    }
    t->set_model(ls);
    t->cp_configure(p.l_group(), p.l_name(), p.getLowerAsFloat(), p.getUpperAsFloat(), 1.0);
    if (p.isInt()) {
	uiSelector<int>::create(machine, t, p, out_ctr, false);
    } else if (p.isFloat()) {
	uiSelector<float>::create(machine, t, p, out_ctr, false);
    } else {
	gx_print_error(
	    "load dialog",
	    Glib::ustring::compose("Enum Parameter variable %1: type not handled", p.id()));
    }
}

static gboolean gx_query_tooltip(GtkWidget *widget, gint x, gint y, gboolean keyboard_mode,
				 GtkTooltip *tooltip, gpointer user_data) {
    if (!*static_cast<bool*>(user_data)) {
	g_signal_stop_emission_by_name(widget, "query-tooltip");
	return FALSE;
    }
    return FALSE;
}

void GxBuilder::connect_gx_tooltip_handler(GtkWidget *widget) {
    g_signal_connect(widget, "query-tooltip", G_CALLBACK(gx_query_tooltip), &show_tooltips);
}

void GxBuilder::set_tooltip_text_connect_handler(GtkWidget *widget, const char *text) {
    gtk_widget_set_tooltip_text(widget, text);
    connect_gx_tooltip_handler(widget);
}

/**
 * connect a widget w to the parameter id.
 */
bool ui_connect(gx_engine::GxMachineBase& machine, Gtk::Widget *w, const std::string& id,
                sigc::signal<void(bool)> *out_ctr) {
    auto wname = w->get_name();
    if (wname.empty() || wname.substr(0,7) == "gtkmm__") {
        string id_css = id;
        boost::replace_all(id_css, ".", "-");
        w->set_name(id_css);
    }
    gx_engine::Parameter *p = check_get_parameter(machine, id, w);
    if (!p) {
        return false;
    }
    if (!p->desc().empty()) {
        GxBuilder::set_tooltip_text_connect_handler(*w, p->l_desc());
    }
    auto acc = w->get_accessible();
    if (acc->get_description().empty()) {
        acc->set_description(id);
    }
    if (acc->get_name().empty()) {
        Glib::ustring nm = p->l_name();
        if (nm.empty()) {
            nm = id.substr(id.find_last_of(".")+1);
        }
        acc->set_name(nm);
    }
    switch (p->getControlType()) {
    case gx_engine::Parameter::Continuous:
        make_continuous_controller(machine, w, *p, out_ctr);
        break;
    case gx_engine::Parameter::Switch:
        make_switch_controller(machine, w, *p, out_ctr);
        break;
    case gx_engine::Parameter::Enum:
        make_enum_controller(machine, w, *p, out_ctr);
        break;
    default:
	gx_print_error(
	    "load dialog",
	    Glib::ustring::compose("Parameter variable %1: type not handled", p->id()));
        break;
    }
    return true;
}

void GxBuilder::fixup_controlparameters(gx_engine::GxMachineBase& machine,
                                        sigc::signal<void(bool)> *out_ctr) {
    Glib::SListHandle<GObject*> objs = Glib::SListHandle<GObject*>(
        gtk_builder_get_objects(gobj()), Glib::OWNERSHIP_DEEP);
    for (Glib::SListHandle<GObject*>::iterator i = objs.begin(); i != objs.end(); ++i) {
	const char *wname = nullptr;
	GtkWidget *widget = nullptr;
	if (g_type_is_a(G_OBJECT_TYPE(*i), GTK_TYPE_WIDGET)) {
	    const char *id = gtk_buildable_get_name(GTK_BUILDABLE(*i));
	    widget = GTK_WIDGET(*i);
	    wname = g_strstr_len(id, -1, ":");
	    if (wname) {
		gtk_widget_set_name(widget, wname+1);
	    }
	    if (gtk_widget_get_has_tooltip(widget)) {
		connect_gx_tooltip_handler(widget);
	    }
	}
        if (!g_type_is_a(G_OBJECT_TYPE(*i), GX_TYPE_CONTROL_PARAMETER)) {
            continue;
        }
        assert(widget);
        auto w = Glib::wrap(widget);
        std::string v = dynamic_cast<Gxw::ControlParameter*>(w)->cp_get_var();
        if (v.empty()) {
            continue;
        }
        ui_connect(machine, w, v, out_ctr);
    }
}

} /* end of gx_gui namespace */
