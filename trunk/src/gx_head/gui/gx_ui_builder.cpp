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

UiBuilderImpl::UiBuilderImpl(MainWindow *i, StackBoxBuilder *b, std::vector<PluginUI*> *pl)
    : UiBuilderBase(), main(*i), pluginlist(pl) {
    intf = b;
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

bool UiBuilderImpl::load_unit(PluginDef *pd) {
    if (!pd->load_ui) {
	return false;
    }
    intf->prepare();
    plugin = pd;
    pd->load_ui(*this, UI_FORM_GLADE|UI_FORM_STACK);
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
    intf->openSpaceBox("");
    intf->closeBox();
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
    main.add_plugin(*pluginlist, pd->id, "");
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

//static
Glib::RefPtr<GxBuilder> GxBuilder::create_from_file(
    const std::string& filename, gx_engine::GxMachineBase* pmach, const char* object_id) {
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
	builder->fixup_controlparameters(*pmach);
    }
    return builder;
}

//static
Glib::RefPtr<GxBuilder> GxBuilder::create_from_file(
    const std::string& filename, gx_engine::GxMachineBase* pmach, const Glib::StringArrayHandle& object_ids) {
    Glib::RefPtr<GxBuilder> builder = GxBuilder::create();
    try {
	builder->add_from_file(filename, object_ids);
    } catch(const Glib::FileError& ex) {
        gx_print_fatal("FileError", ex.what());
    } catch(const Gtk::BuilderError& ex) {
        gx_print_fatal("Builder Error", ex.what());
    }
    if (pmach) {
	builder->fixup_controlparameters(*pmach);
    }
    return builder;
}

//static
Glib::RefPtr<GxBuilder> GxBuilder::create_from_string(
    const Glib::ustring& buffer, gx_engine::GxMachineBase* pmach, const char* object_id) {
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
	builder->fixup_controlparameters(*pmach);
    }
    return builder;
}

//static
Glib::RefPtr<GxBuilder> GxBuilder::create_from_string(
    const Glib::ustring& buffer, gx_engine::GxMachineBase* pmach, const Glib::StringArrayHandle& object_ids) {
    Glib::RefPtr<GxBuilder> builder = GxBuilder::create();
    try {
	builder->add_from_string(buffer, object_ids);
    } catch(const Gtk::BuilderError& ex) {
        gx_print_fatal("Builder Error", ex.what());
    }
    if (pmach) {
	builder->fixup_controlparameters(*pmach);
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

#if 0
    if (!GTK_IS_WIDGET(cobject))  {
	g_critical("gtkmm: object `%s' (type=`%s') (in GtkBuilder file) is not a widget type.",
		   name.c_str(), G_OBJECT_TYPE_NAME(cobject));
	/* TODO: Unref/sink it? */
	return 0;
    }
#endif

  return cobject;
}

/*
 ** GxBuilder::fixup_controlparameters + helper classes
 */

template <class T>
class uiSelector: public uiElement {
protected:
    gx_engine::GxMachineBase& machine;
    const std::string id;
    Gtk::Range *rng;
    void on_value_changed();
    void set_value(T v);
public:
    uiSelector(gx_engine::GxMachineBase& machine, Gtk::Range *rng, const std::string& id);
};

template <class T>
uiSelector<T>::uiSelector(gx_engine::GxMachineBase& machine_, Gtk::Range *rng_, const std::string& id_)
    : uiElement(), machine(machine_), id(id_), rng(rng_) {
    set_value(machine.get_parameter_value<T>(id));
    rng->signal_value_changed().connect(
	sigc::mem_fun(*this, &uiSelector::on_value_changed));
    machine.signal_parameter_value<T>(id).connect(
	sigc::mem_fun(this, &uiSelector::set_value));
}

template <class T>
void uiSelector<T>::set_value(T v) {
    rng->set_value(v);
}

template<class T>
void uiSelector<T>::on_value_changed() {
    machine.set_parameter_value(id, static_cast<T>(rng->get_value()));
}

static void widget_destroyed(gpointer data) {
    delete static_cast<uiElement*>(data);
}

static void destroy_with_widget(Glib::Object *t, uiElement *p) {
    t->set_data("uiElement", p, widget_destroyed);
}

static void make_switch_controller(gx_engine::GxMachineBase& machine, Glib::RefPtr<Gxw::ControlParameter>& w, gx_engine::Parameter& p) {
    w->cp_configure(p.l_group(), p.l_name(), 0, 0, 0);
    Gtk::ToggleButton *t = dynamic_cast<Gtk::ToggleButton*>(w.operator->());
    if (p.isFloat()) {
	w->cp_set_value(machine.get_parameter_value<float>(p.id()));
	if (t) {
	    destroy_with_widget(t, new uiToggle<float>(machine, t, p.id()));
	}
    } else if (p.isBool()) {
	w->cp_set_value(machine.get_parameter_value<bool>(p.id()));
	if (t) {
	    destroy_with_widget(t, new uiToggle<bool>(machine, t, p.id()));
	}
    } else {
	gx_print_warning(
	    "load dialog",
	    Glib::ustring::compose("Switch Parameter variable %1: type not handled", p.id()));
    }
}

struct uiAdjustmentLog: public uiElement {
    gx_engine::GxMachineBase& machine;
    const std::string id;
    Glib::RefPtr<Gtk::Adjustment> fAdj;
    uiAdjustmentLog(gx_engine::GxMachineBase& machine_, const std::string& id_, Glib::RefPtr<Gtk::Adjustment> adj) :
	uiElement(), machine(machine_), id(id_), fAdj(adj) {
	fAdj->set_value(log10(machine.get_parameter_value<float>(id)));
	machine.signal_parameter_value<float>(id).connect(sigc::mem_fun(this, &uiAdjustmentLog::on_parameter_changed));
    }
    void changed() {
	machine.set_parameter_value(id, pow(10.0,fAdj->get_value()));
    }
    void on_parameter_changed(float v) {
	fAdj->set_value(log10(v));
    }
};

static void make_continuous_controller(gx_engine::GxMachineBase& machine, Glib::RefPtr<Gxw::ControlParameter>& w, gx_engine::Parameter& p) {
    Glib::RefPtr<Gxw::Regler> r = Glib::RefPtr<Gxw::Regler>::cast_dynamic(w);
    if (!r) {
	make_switch_controller(machine, w, p);
	return;
    }
    if (!p.isFloat()) {
	gx_print_warning(
	    "load dialog",
	    Glib::ustring::compose("Continuous Parameter variable %1: type not handled", p.id()));
	return;
    }
    Glib::RefPtr<Gtk::Adjustment> adj = r->get_adjustment();
    gx_engine::FloatParameter &fp = p.getFloat();
    if (fp.is_log_display()) {
	double up = log10(fp.getUpperAsFloat());
	double step = log10(fp.getStepAsFloat());
	w->cp_configure(fp.l_group(), fp.l_name(), log10(fp.getLowerAsFloat()), up, step);
	int prec = 0;
	float d = log10((fp.getStepAsFloat()-1)*fp.getUpperAsFloat());
	if (up > 0) {
	    prec = up;
	    if (d < 0) {
		prec -= floor(d);
	    }
	} else if (d < 0) {
	    prec = -floor(d);
	}
	r->signal_format_value().connect(
	    sigc::bind(
		sigc::ptr_fun(logarithmic_format_value),
		prec));
	r->signal_input_value().connect(
	    sigc::ptr_fun(logarithmic_input_value));
	w->cp_set_value(log10(machine.get_parameter_value<float>(p.id())));
	uiAdjustmentLog* c = new uiAdjustmentLog(machine, p.id(), adj);
	adj->signal_value_changed().connect(sigc::mem_fun(c, &uiAdjustmentLog::changed));
	destroy_with_widget(r.operator->(), c);
    } else {
	w->cp_configure(p.l_group(), p.l_name(), fp.getLowerAsFloat(), fp.getUpperAsFloat(), fp.getStepAsFloat());
	w->cp_set_value(machine.get_parameter_value<float>(p.id()));
	uiAdjustment* c = new uiAdjustment(machine, p.id(), adj);
	adj->signal_value_changed().connect(
	    sigc::mem_fun(c, &uiAdjustment::changed));
	destroy_with_widget(r.operator->(), c);
    }
}

static void make_enum_controller(gx_engine::GxMachineBase& machine, Glib::RefPtr<Gxw::ControlParameter>& w, gx_engine::Parameter& p) {
    Gxw::Selector *t = dynamic_cast<Gxw::Selector*>(w.operator->());
    if (!t) {
	make_continuous_controller(machine, w, p);
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
    w->cp_configure(p.l_group(), p.l_name(), p.getLowerAsFloat(), p.getUpperAsFloat(), 1.0);
    if (p.isInt()) {
	destroy_with_widget(t, new uiSelector<int>(machine, t, p.id()));
	t->cp_set_value(machine.get_parameter_value<int>(p.id()));
    } else if (p.isFloat()) {
	destroy_with_widget(t, new uiSelector<float>(machine, t, p.id()));
	t->cp_set_value(machine.get_parameter_value<float>(p.id()));
    } else {
	gx_print_warning(
	    "load dialog",
	    Glib::ustring::compose("Enum Parameter variable %1: type not handled", p.id()));
    }
}

void GxBuilder::fixup_controlparameters(gx_engine::GxMachineBase& machine) {
    Glib::SListHandle<GObject*> objs = Glib::SListHandle<GObject*>(
        gtk_builder_get_objects(gobj()), Glib::OWNERSHIP_DEEP);
    for (Glib::SListHandle<GObject*>::iterator i = objs.begin(); i != objs.end(); ++i) {
	const char *wname = 0;
	if (g_type_is_a(G_OBJECT_TYPE(*i), GTK_TYPE_WIDGET)) {
	    const char *id = gtk_buildable_get_name(GTK_BUILDABLE(*i));
	    wname = g_strstr_len(id, -1, ":");
	    if (wname) {
		gtk_widget_set_name(GTK_WIDGET(*i), wname+1);
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
	if (!wname) {
	    Glib::RefPtr<Gtk::Widget>::cast_dynamic(w)->set_name(v);
	}
        if (!machine.parameter_hasId(v)) {
	    Glib::RefPtr<Gtk::Widget> wd = Glib::RefPtr<Gtk::Widget>::cast_dynamic(w);
	    wd->set_sensitive(0);
            wd->set_tooltip_text(v);
            gx_print_warning(
		"load dialog",
		(boost::format("Parameter variable %1% not found") % v).str());
            continue;
        }
        gx_engine::Parameter& p = machine.get_parameter(v);
        if (!p.desc().empty()) {
            Glib::RefPtr<Gtk::Widget>::cast_dynamic(w)->set_tooltip_text(
		gettext(p.desc().c_str()));
        }
	switch (p.getControlType()) {
	case gx_engine::Parameter::None:       assert(false); break;
	case gx_engine::Parameter::Continuous: make_continuous_controller(machine, w, p); break;
	case gx_engine::Parameter::Switch:     make_switch_controller(machine, w, p); break;
	case gx_engine::Parameter::Enum:       make_enum_controller(machine, w, p); break;
	default:         assert(false); break;
        }
	if (p.isControllable()) {
	    connect_midi_controller(Glib::RefPtr<Gtk::Widget>::cast_dynamic(w).operator->(), v.c_str(), machine);
	}
    }
}

} /* end of gx_gui namespace */
