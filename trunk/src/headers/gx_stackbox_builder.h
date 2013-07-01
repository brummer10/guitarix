/*
 * Copyright (C) 2011, 2012 Andreas Degert, Hermann Meyer
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
 */

#include "guitarix.h"        // NOLINT

#include <glibmm/i18n.h>     // NOLINT

namespace gx_gui {

class uiToggleButton {
private:
    gx_engine::GxMachineBase& machine;
    const std::string id;
    Gtk::ToggleButton* fButton;
public:
    uiToggleButton(gx_engine::GxMachineBase& machine_, Gtk::ToggleButton* b, const std::string& id_);
    void toggled();
    void set_value(bool v);
};

/****************************************************************/

class WidgetStack {
private:
    std::vector<Gtk::Widget*> stack;
    Gtk::Widget *top() { return stack.back(); }
public:
    WidgetStack(): stack() {}
    ~WidgetStack() {}
    bool empty() { return stack.empty(); }
    void push(Gtk::Widget& w) { stack.push_back(&w); }
    void pop() { return stack.pop_back(); }
    void container_add(Gtk::Widget& w);
    void box_pack_start(Gtk::Widget& w, bool expand=true, bool fill=true, int padding=0);
    void notebook_append_page(Gtk::Widget& w, Gtk::Widget& label);
    bool top_is_notebook() { return dynamic_cast<Gtk::Notebook*>(top()) != 0; }
    void add(Gtk::Widget& w, const char *label=0);
};

class StackBoxBuilder {
private:
    WidgetStack          fBox;
    gx_engine::GxMachineBase& machine;
    Gxw::WaveView&       fWaveView;
    Gtk::Label&          convolver_filename_label;
    Gtk::Label&          convolver_mono_filename_label;
    Gtk::HBox           *widget;
    Glib::RefPtr<Gtk::AccelGroup> accels;
    Glib::RefPtr<Gdk::Pixbuf> window_icon;
    int next_flags;

    static const          gboolean homogene = false;
    void loadRackFromGladeData(const char *xmldesc);
    void set_convolver_filename(const gx_engine::GxJConvSettings *jcs);
    void set_convolver_mono_filename(const gx_engine::GxJConvSettings *jcs);
private:
    void openVerticalMidiBox(const char* label = "");
    // functions used in interfaces
    void create_master_slider(string id) {
	addwidget(UiRackMasterRegler::create(machine, new Gxw::HSlider(), id));
    }
    void create_master_slider(string id, Glib::ustring(label)) {
	addwidget(UiRackMasterRegler::create(machine, new Gxw::HSlider(), id, label));
    }

    void closeBox();
    void openSpaceBox(const char* label = "");

    void check_set_flags(Gxw::Regler *r);
    void create_small_rackknob(string id);
    void create_small_rackknob(string id, Glib::ustring label);
    void create_small_rackknobr(string id);
    void create_small_rackknobr(string id, Glib::ustring label);

    void openVerticalBox(const char* label = "");
    void openFrameBox(const char* label);
    void openHorizontalBox(const char* label = "");
    void addLiveWaveDisplay(const char* label);
    void openVerticalHideBox(const char* label = "");
    void openHorizontalhideBox(const char* label = "");
    void openHorizontalTableBox(const char* label);
    void create_switch_no_caption(const char *sw_type, const string& id) {
	addwidget(UiSwitch::create(machine, sw_type, id));
    }
    void create_switch(const char *sw_type, const string& id, const char *label, Gtk::PositionType pos) {
	if (label) {
	    addwidget(UiSwitchWithCaption::create(machine, sw_type, id, label, pos));
	} else {
	    addwidget(UiSwitchWithCaption::create(machine, sw_type, id, pos));
	}
    }
    void openpaintampBox(const char* label = "");
    void create_wheel(string id, bool show_value = false) {
	addwidget(UiRegler::create(machine, new Gxw::Wheel(), id, show_value));
    }
    void create_spin_value(const std::string& id, const char *label) {
	Gtk::Widget *w;
	Gxw::ValueDisplay *v = new Gxw::ValueDisplay();
	if (label) {
	    w = UiRackReglerWithCaption::create(machine, v, id, label);
	} else {
	    w = UiRackReglerWithCaption::create(machine, v, id);
	}
	v->set_name("show_always");
	addwidget(w);
    }
    void create_simple_spin_value(const std::string& id, const char *label = 0) {
	Gtk::Widget *w;
	Gxw::SimpleValueDisplay *v = new Gxw::SimpleValueDisplay();
	if (label) {
	    w = UiRackReglerWithCaption::create(machine, v, id, label);
	} else {
	    w = UiRackRegler::create(machine, v, id);
	}
	v->set_name("show_always");
	addwidget(w);
    }
    void create_eq_rackslider_no_caption(string id) {
	addwidget(UiRackRegler::create(machine, new Gxw::EqSlider(), id));
    }
    void create_port_display(string id, const char *label) {
	if (label) {
	    if (*label) {
		addwidget(UiRackReglerWithCaption::create(machine, new Gxw::PortDisplay(), id, label));
	    } else {
		addwidget(UiRackRegler::create(machine, new Gxw::PortDisplay(), id));
	    }
	} else {
	    addwidget(UiRackReglerWithCaption::create(machine, new Gxw::PortDisplay(), id));
	}
    }
    void create_selector(string id, const char *widget_name=0);
    void create_selector_with_caption(string id, const char *label);
    void openFlipLabelBox(const char* = 0);
    void openVerticalBox1(const char* label = 0);
    void openVerticalBox2(const char* label = 0);
    void openPaintBox2(const char* label = 0);
    void openTabBox(const char* label = 0);
    void addCheckButton(string id, const char* label = 0);
    void addNumEntry(string id, const char* label = 0);
    void addMToggleButton(const std::string& id, const char* label = 0);
    void addSmallJConvFavButton(const char* label, gx_jconv::IRWindow *irw);
    void openSetLabelBox();
    void openSetMonoLabelBox();
    void addJConvFavButton(const char* label, gx_jconv::IRWindow *irw);
    void addJConvButton(const char* label, gx_jconv::IRWindow *irw);
    void set_next_flags(int flags);
private:
    // functions used indirectly
    Gtk::Widget*  addWidget(const char* label, Gtk::Widget* w);
    void addwidget(Gtk::Widget *widget);
    void addCheckButton(const char* label, const char* id);
    void addNumEntry(const char* label, const char* id, float init, float min, float max, float step);
    friend class UiBuilderImpl;
public:
    StackBoxBuilder(
	gx_engine::GxMachineBase& machine_, Gxw::WaveView &fWaveView_, Gtk::Label &convolver_filename_label_,
	Gtk::Label& convolver_mono_filename_label_, Glib::RefPtr<Gdk::Pixbuf> window_icon);
    ~StackBoxBuilder();
    void set_accelgroup(Glib::RefPtr<Gtk::AccelGroup> accels_) { accels = accels_; }
    void get_box(const std::string& name, Gtk::Widget*& mainbox, Gtk::Widget*& minibox);
    void prepare();
    void fetch(Gtk::Widget*& mainbox, Gtk::Widget*& minibox);
    // mono
    void make_rackbox_ampdetail();
    void make_rackbox_overdrive();
    void make_rackbox_echo();
    void make_rackbox_delay();
    void make_rackbox_freeverb();
    void make_rackbox_oscilloscope();
    void make_rackbox_low_highpass();
    void make_rackbox_eqs();
    void make_rackbox_peak_eq();
    void make_rackbox_digital_delay();
    void make_rackbox_digital_delay_st();
    void make_rackbox_crybaby();
    void make_rackbox_gx_distortion();
    void make_rackbox_IR();
    void make_rackbox_compressor();
    void make_rackbox_expander();
    void make_rackbox_biquad();
    void make_rackbox_tremolo();
    void make_rackbox_phaser_mono();
    void make_rackbox_chorus_mono();
    void make_rackbox_flanger_mono();
    void make_rackbox_feedback();
    void make_rackbox_amp_tonestack();
    void make_rackbox_cab();
    void make_rackbox_pre();
    void make_rackbox_jconv_mono();
    void make_rackbox_highbooster();
    void make_rackbox_midi_out();
    // stereo
    void make_rackbox_chorus();
    void make_rackbox_flanger();
    void make_rackbox_phaser();
    void make_rackbox_stereodelay();
    void make_rackbox_stereoecho();
    void make_rackbox_moog();
    void make_rackbox_ampmodul();
    void make_rackbox_tonemodul();
    void make_rackbox_jconv();
    void make_rackbox_stereoverb();
};

} // end namespace gx_gui
