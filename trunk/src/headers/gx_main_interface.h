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

class UiRegler: gx_ui::GxUiItemFloat, protected Gtk::Adjustment {
 protected:
    Gxw::Regler *m_regler;
    bool log_display;
    void on_value_changed();
    virtual void reflectZone();
 public:
    static GtkWidget* create(gx_ui::GxUI& ui, Gxw::Regler *regler, string id, bool show_value);
    UiRegler(gx_ui::GxUI &ui, gx_engine::FloatParameter &param, Gxw::Regler *regler, bool show_value);
    virtual ~UiRegler();
    GtkWidget *get_widget() { return GTK_WIDGET(m_regler->gobj()); }
};

/****************************************************************/

class UiSelectorBase {
protected:
    Gxw::Selector m_selector;
public:
    UiSelectorBase(gx_engine::Parameter& param);
    void set_name(Glib::ustring n) { m_selector.set_name(n); }
    virtual GtkWidget *get_widget() { return GTK_WIDGET(m_selector.gobj()); }
};

template <class T>
class UiSelector: public UiSelectorBase, private gx_ui::GxUiItemV<T>, protected Gtk::Adjustment {
private:
    virtual void reflectZone();
    void on_value_changed();
public:
    UiSelector(gx_ui::GxUI& ui, gx_engine::ParameterV<T> &param);
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
    static GtkWidget* create(gx_ui::GxUI& ui, string id, const char *label);
    UiSelectorWithCaption(gx_ui::GxUI& ui, gx_engine::ParameterV<T> &param, const char *label);
    ~UiSelectorWithCaption();
    virtual GtkWidget *get_widget() { return GTK_WIDGET(m_box.gobj()); }
};

template <class T>
UiSelectorWithCaption<T>::UiSelectorWithCaption(gx_ui::GxUI& ui, gx_engine::ParameterV<T> &param, const char *label)
    : UiSelector<T>(ui, param) {
    if (label) {
	m_label.set_text(label);
    } else {
	m_label.set_text(param.l_name());
    }
    m_label.set_name("rack_label");
    m_box.set_name(param.id());
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
    static GtkWidget* create(gx_ui::GxUI& ui, Gxw::Regler *regler, string id, bool show_value);
    static GtkWidget* create(gx_ui::GxUI& ui, Gxw::Regler *regler, string id,
                             Glib::ustring label, bool show_value);
    UiReglerWithCaption(gx_ui::GxUI &ui, gx_engine::FloatParameter &param, Gxw::Regler *regler,
                        Glib::ustring label, bool show_value);
    GtkWidget *get_widget() { return GTK_WIDGET(m_box.gobj());}
};

/****************************************************************/

class UiRackReglerWithCaption: public UiRegler {
 private:
    Gtk::Label m_label;
    Gtk::VBox m_box;
 public:
    static GtkWidget* create(gx_ui::GxUI& ui, Gxw::Regler *regler, string id);
    static GtkWidget* create(gx_ui::GxUI& ui, Gxw::Regler *regler, string id,
                             Glib::ustring label);
    UiRackReglerWithCaption(gx_ui::GxUI &ui, gx_engine::FloatParameter &param, Gxw::Regler *regler,
                            Glib::ustring label);
    GtkWidget *get_widget() { return GTK_WIDGET(m_box.gobj());}
};
/****************************************************************/

class UiRackMasterRegler: public UiRegler {
 private:
    Gtk::Label m_label;
    Gtk::HBox m_box;
 public:
    static GtkWidget* create(gx_ui::GxUI& ui, Gxw::Regler *regler, string id);
    static GtkWidget* create(gx_ui::GxUI& ui, Gxw::Regler *regler, string id,
                             Glib::ustring label);
    UiRackMasterRegler(gx_ui::GxUI &ui, gx_engine::FloatParameter &param, Gxw::Regler *regler,
                            Glib::ustring label);
    GtkWidget *get_widget() { return GTK_WIDGET(m_box.gobj());}
};

/****************************************************************/

class UiRackRegler: public UiRegler {
 private:
    Gtk::Label m_label;
    Gtk::VBox m_box;
 public:
    static GtkWidget* create(gx_ui::GxUI& ui, Gxw::Regler *regler, string id);
    static GtkWidget* create(gx_ui::GxUI& ui, Gxw::Regler *regler, string id,
                             Glib::ustring label);
    UiRackRegler(gx_ui::GxUI &ui, gx_engine::FloatParameter &param, Gxw::Regler *regler,
                 Glib::ustring label);
    GtkWidget *get_widget() { return GTK_WIDGET(m_box.gobj());}
};

/****************************************************************/

struct uiCheckButton : public gx_ui::GxUiItemBool {
    GtkToggleButton* fButton;
    uiCheckButton(gx_ui::GxUI* ui, bool* zone, GtkToggleButton* b)
                   : gx_ui::GxUiItemBool(ui, zone), fButton(b) {
            gtk_toggle_button_set_active(fButton, *zone);
    }
    static void toggled(GtkWidget *widget, gpointer data) {
            ((gx_ui::GxUiItemBool*)data)->modifyZone(GTK_TOGGLE_BUTTON(widget)->active);
        }

    virtual void reflectZone() {
            bool v = *fZone;
            fCache = v;
            gtk_toggle_button_set_active(fButton, v);
        }
};

/****************************************************************/

class ReportXrun {
private:
    gx_jack::GxJack& jack;
    bool blocked;
    void clear();
public:
    ReportXrun(gx_jack::GxJack& jack_)
	: jack(jack_), blocked(false) {}
    void run();
};

/****************************************************************/

struct uiAdjustment : public gx_ui::GxUiItemFloat {
    GtkAdjustment* fAdj;
    uiAdjustment(gx_ui::GxUI* ui, float* zone, GtkAdjustment* adj) :
                 gx_ui::GxUiItemFloat(ui, zone), fAdj(adj) {
	gtk_adjustment_set_value(fAdj, *zone);
}
    static void changed(GtkAdjustment *adj, gpointer data) {
            float    v = adj->value;
            ((gx_ui::GxUiItemFloat*)data)->modifyZone(v);
        }

    virtual void reflectZone() {
            float     v = *fZone;
            fCache = v;
            gtk_adjustment_set_value(fAdj, v);
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

gboolean button_press_cb(GtkWidget *widget, GdkEventButton *event, gpointer data);
int precision(double n);
string fformat(float value, float step);

/****************************************************************/

#ifndef NDEBUG
// debug_check
inline void check_zone(GtkWidget *w, void *zone) {
    if (!gx_engine::parameter_map.hasZone(zone)) {
        gchar *p;
        gtk_widget_path(w, NULL, &p, NULL);
        cerr << "zone not found in definition of widget: "
             << p << endl;
        g_free(p);
        assert(false);
    }
    gx_engine::parameter_map[zone].setUsed();
}
#endif

/****************************************************************/

inline void connect_midi_controller(GtkWidget *w, void *zone) {
    debug_check(check_zone, w, zone);
    g_signal_connect(w, "button_press_event", G_CALLBACK(button_press_cb),
                    (gpointer)&gx_engine::parameter_map[zone]);
}

/****************************************************************/

/* -------------------------------------------------------------------------- */
} /* end of gx_gui namespace */

#endif  // SRC_HEADERS_GX_MAIN_INTERFACE_H_

