/*
 * Copyright (C) 2009, 2010 Hermann Meyer, James Warden
 * Copyright (C) 2011 Pete Shorthose
 * Copyright (C) 2012 Andreas Degert
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
 * ----------------------------------------------------------------------------
 */

#include <guitarix.h>

/****************************************************************
 ** class Liveplay
 */

bool Liveplay::do_action(GtkAccelGroup *accel_group, GObject *acceleratable,
			 guint keyval, GdkModifierType modifier,
			 GtkAction* act) {
    gtk_action_activate(act);
    return true;
}

void Liveplay::display_empty(const Glib::ustring& s) {
    liveplay_preset->set_text(s);
    key_timeout = Glib::signal_timeout().connect(
	sigc::bind_return(sigc::mem_fun(*this, &Liveplay::on_selection_changed), false), 400);
}

void Liveplay::process_preset_key(int idx) {
    if (last_bank_key.empty()) {
	if (!gx_settings.setting_is_preset()) {
	    display_empty(Glib::ustring::compose("?? / %1", idx+1));
	    return;
	}
	last_bank_key = gx_settings.get_current_bank();
    }
    gx_system::PresetFile *f = gx_settings.banks.get_file(last_bank_key);
    if (idx >= f->size()) {
	display_empty(Glib::ustring::compose("%1 / %2?", last_bank_key, idx+1));
    } else {
	gx_settings.load_preset(f, f->get_name(idx));
    }
}

void Liveplay::process_bank_key(int idx) {
    last_bank_key = gx_settings.banks.get_name(idx);
    if (last_bank_key.empty()) {
	display_empty("-- / --");
	return;
    }
    liveplay_preset->set_text(Glib::ustring::compose("%1 /", last_bank_key));
    key_timeout = Glib::signal_timeout().connect(
	sigc::bind_return(sigc::mem_fun(*this, &Liveplay::on_selection_changed), false), 2000);
}

bool Liveplay::on_keyboard_preset_select(GtkAccelGroup *accel_group, GObject *acceleratable,
					 guint keyval, GdkModifierType modifier, Liveplay& self) {
    if (self.key_timeout.connected()) {
	self.key_timeout.disconnect();
    }
    int idx = keyval - GDK_KEY_1;
    if (idx >= 0 && idx <= 9) {
	self.process_preset_key(idx);
	return true;
    }
    idx = keyval - GDK_KEY_KP_1;
    if (idx >= 0 && idx <= 9) {
	self.process_preset_key(idx);
	return true;
    }
    idx = keyval - GDK_KEY_a;
    if (idx >= 0 && idx <= (GDK_KEY_z - GDK_KEY_a)) {
	self.process_bank_key(idx);
	return true;
    }
    return false;
}

bool Liveplay::on_keyboard_toggle_mute(GtkAccelGroup *accel_group, GObject *acceleratable,
				       guint keyval, GdkModifierType modifier, Liveplay& self) {
    self.engine.set_state(self.engine.get_state() == gx_engine::kEngineOff ?
		     gx_engine::kEngineOn
		     : gx_engine::kEngineOff);
    return true;
}

bool Liveplay::on_keyboard_arrows(GtkAccelGroup *accel_group, GObject *acceleratable,
				       guint keyval, GdkModifierType modifier, Liveplay& self) {
    if (keyval == GDK_KEY_Left || keyval == GDK_KEY_Right) {
	Gtk::Adjustment *a = self.brightness_slider->get_adjustment();
	double val = a->get_value();
	double step = a->get_step_increment();
	if (keyval == GDK_KEY_Left) {
	    val -= step;
	} else {
	    val += step;
	}
	a->set_value(val);
    } else {
	Gtk::Adjustment *a = self.background_slider->get_adjustment();
	double val = a->get_value();
	double step = a->get_step_increment();
	if (keyval == GDK_KEY_Down) {
	    val -= step;
	} else {
	    val += step;
	}
	a->set_value(val);
    }
    return true;
}

Liveplay::Liveplay(const gx_system::CmdlineOptions& options, gx_engine::GxEngine& engine_, gx_preset::GxSettings& gx_settings_,
		   const std::string& fname, Glib::RefPtr<Gtk::ActionGroup>& actiongroup, Glib::RefPtr<UiBoolToggleAction>& livetuner_action)
    : ui(), bld(), engine(engine_), gx_settings(gx_settings_), use_composite(),
      brightness_adj(1,0.5,1,0.01,0.1), background_adj(0,0,1,0.01,0.1), key_timeout(),
      last_bank_key(), midi_conn(), window() {
    const char *id_list[] = {"LivePlay", 0};
    bld = gx_gui::GxBuilder::create_from_file(fname, &ui, id_list);
    bld->get_toplevel("LivePlay", window);

    bld->find_widget("liveplay_preset", liveplay_preset);
    bld->find_widget("liveplay_bypass_image", bypass_image);
    bld->find_widget("liveplay_mute_image", mute_image);
    bld->find_widget("liveplay_canvas", liveplay_canvas);
    bld->find_widget("brightness_slider", brightness_slider);
    bld->find_widget("brightness_box", brightness_box);
    bld->find_widget("background_slider", background_slider);
    bld->find_widget("liveplay_exit:barbutton", liveplay_exit);
    bld->find_widget("liveplay_tuner", tuner);
    bld->find_widget("liveplay_midictrl_table", midictrl_table);

    Glib::RefPtr<Gdk::Pixbuf> pb = Gdk::Pixbuf::create_from_file(
	options.get_style_filepath("bypass.svg"), 300, 150);
    bypass_image->set(pb);
    pb = Gdk::Pixbuf::create_from_file(
	options.get_style_filepath("mute.svg"), 300, 150);
    mute_image->set(pb);
    use_composite = window->get_display()->supports_composite();
    if (use_composite) {
	brightness_adj.signal_value_changed().connect(sigc::mem_fun(*this, &Liveplay::on_brightness_changed));
	brightness_slider->set_adjustment(brightness_adj);
	liveplay_canvas->signal_realize().connect(sigc::mem_fun(*this, &Liveplay::on_realize));
	window->signal_expose_event().connect(
	    sigc::mem_fun(*this, &Liveplay::window_expose_event), true);
    } else {
	brightness_box->hide();
    }
    background_adj.signal_value_changed().connect(
	sigc::mem_fun(*this, &Liveplay::on_background_changed));
    background_slider->set_adjustment(background_adj);
    Glib::RefPtr<Gdk::Screen> screen = liveplay_canvas->get_screen();
    Glib::RefPtr<Gdk::Colormap> rgba = screen->get_rgba_colormap();
    liveplay_canvas->set_colormap(rgba);
    liveplay_canvas->set_app_paintable(true);
    liveplay_canvas->signal_expose_event().connect(
	sigc::mem_fun(*this, &Liveplay::transparent_expose));
    window->signal_delete_event().connect(
	sigc::mem_fun(*this, &Liveplay::on_delete));

    Glib::RefPtr<Gtk::Action> act = actiongroup->get_action("Liveplay");
    gtk_activatable_set_related_action(
	GTK_ACTIVATABLE(liveplay_exit->gobj()),
	act->gobj());
    Glib::RefPtr<Gtk::AccelGroup> ag = Gtk::AccelGroup::create();
    GClosure *cl = g_cclosure_new(G_CALLBACK(do_action), (gpointer)(act->gobj()), 0);
    gtk_accel_group_connect_by_path(ag->gobj(), act->get_accel_path().c_str(), cl);
    cl = g_cclosure_new(G_CALLBACK(do_action), (gpointer)(act->gobj()), 0);
    gtk_accel_group_connect(ag->gobj(), GDK_KEY_Escape, (GdkModifierType)0, (GtkAccelFlags)0, cl);

    actiongroup->add(
	livetuner_action,
	sigc::compose(
	    sigc::mem_fun(*this, &Liveplay::display_tuner),
	    sigc::mem_fun(livetuner_action.operator->(), &Gtk::ToggleAction::get_active)));
    cl = g_cclosure_new(G_CALLBACK(do_action), (gpointer)(livetuner_action->gobj()), 0);
    gtk_accel_group_connect(ag->gobj(), GDK_KEY_Return, (GdkModifierType)0, (GtkAccelFlags)0, cl);

    act = actiongroup->get_action("Quit");
    cl = g_cclosure_new(G_CALLBACK(do_action), (gpointer)(act->gobj()), 0);
    gtk_accel_group_connect_by_path(ag->gobj(), act->get_accel_path().c_str(), cl);

    cl = g_cclosure_new(G_CALLBACK(on_keyboard_toggle_mute), (gpointer)this, 0);
    gtk_accel_group_connect(ag->gobj(), GDK_KEY_space, (GdkModifierType)0, (GtkAccelFlags)0, cl);

    cl = g_cclosure_new(G_CALLBACK(on_keyboard_arrows), (gpointer)this, 0);
    gtk_accel_group_connect(ag->gobj(), GDK_KEY_Left, GDK_CONTROL_MASK, (GtkAccelFlags)0, cl);
    cl = g_cclosure_new(G_CALLBACK(on_keyboard_arrows), (gpointer)this, 0);
    gtk_accel_group_connect(ag->gobj(), GDK_KEY_Right, GDK_CONTROL_MASK, (GtkAccelFlags)0, cl);
    cl = g_cclosure_new(G_CALLBACK(on_keyboard_arrows), (gpointer)this, 0);
    gtk_accel_group_connect(ag->gobj(), GDK_KEY_Up, GDK_CONTROL_MASK, (GtkAccelFlags)0, cl);
    cl = g_cclosure_new(G_CALLBACK(on_keyboard_arrows), (gpointer)this, 0);
    gtk_accel_group_connect(ag->gobj(), GDK_KEY_Down, GDK_CONTROL_MASK, (GtkAccelFlags)0, cl);

    for (int n = GDK_KEY_1; n <= GDK_KEY_9; ++n) {
	cl = g_cclosure_new(G_CALLBACK(on_keyboard_preset_select), (gpointer)this, 0);
	gtk_accel_group_connect(ag->gobj(), n, (GdkModifierType)0, (GtkAccelFlags)0, cl);
    }
    for (int n = GDK_KEY_KP_1; n <= GDK_KEY_KP_9; ++n) {
	cl = g_cclosure_new(G_CALLBACK(on_keyboard_preset_select), (gpointer)this, 0);
	gtk_accel_group_connect(ag->gobj(), n, (GdkModifierType)0, (GtkAccelFlags)0, cl);
    }
    for (int n = GDK_KEY_A; n <= GDK_KEY_Z; ++n) {
	cl = g_cclosure_new(G_CALLBACK(on_keyboard_preset_select), (gpointer)this, 0);
	gtk_accel_group_connect(ag->gobj(), n, (GdkModifierType)0, (GtkAccelFlags)0, cl);
    }
    
    window->add_accel_group(ag);

    engine.signal_state_change().connect(
	sigc::mem_fun(*this, &Liveplay::on_engine_state_change));
    gx_settings.signal_selection_changed().connect(
	sigc::mem_fun(*this, &Liveplay::on_selection_changed));

    on_engine_state_change(engine.get_state());
    on_selection_changed();
}

Liveplay::~Liveplay() {
    delete window;
}

void Liveplay::on_engine_state_change(gx_engine::GxEngineState state) {
    switch (state) {
    case gx_engine::kEngineOff:    bypass_image->hide(); mute_image->show(); break;
    case gx_engine::kEngineOn:     bypass_image->hide(); mute_image->hide(); break;
    case gx_engine::kEngineBypass: bypass_image->show(); mute_image->hide(); break;
    }
}

void Liveplay::on_selection_changed() {
    last_bank_key.clear();
    Glib::ustring s;
    if (gx_settings.get_current_source() == gx_system::GxSettingsBase::state) {
	s = "----";
    } else {
	s = Glib::ustring::compose(
	    "%1 / %2", gx_settings.get_current_bank(), gx_settings.get_current_name());
    }
    liveplay_preset->set_text(s);
}

void Liveplay::on_live_play(Glib::RefPtr<Gtk::ToggleAction> act) {
    if (act->get_active()) {
	window->fullscreen();
	midi_conn = gx_engine::controller_map.signal_changed().connect(
	    sigc::mem_fun(*this, &Liveplay::add_midi_elements));
	add_midi_elements();
	window->show();
    } else {
	midi_conn.disconnect();
	window->hide();
    }
}

bool Liveplay::window_expose_event(GdkEventExpose *event) {
    Cairo::RefPtr<Cairo::Context> cr = Glib::wrap(event->window, true)->create_cairo_context();
    Gtk::Allocation a = liveplay_canvas->get_allocation();
    gdk_cairo_set_source_window(cr->cobj(), liveplay_canvas->get_window()->gobj(), a.get_x(), a.get_y());
    Gdk::Region region(a);
    region.intersect(Glib::wrap(event->region, true));
    Gdk::Cairo::add_region_to_path(cr, region);
    cr->clip();

    cr->set_operator(Cairo::OPERATOR_OVER);
    cr->paint_with_alpha(pow(brightness_adj.get_value(),2.2));
    return false;
}

bool Liveplay::on_delete(GdkEventAny *ev) {
    liveplay_exit->set_active(false);
    return true;
}

void Liveplay::on_brightness_changed() {
    window->queue_draw();
}

void Liveplay::on_background_changed() {
    window->queue_draw();
}

bool Liveplay::transparent_expose(GdkEventExpose *event) {
    Cairo::RefPtr<Cairo::Context> cr = Glib::wrap(event->window, true)->create_cairo_context();
    gdk_cairo_region(cr->cobj(), event->region);
    cr->set_source_rgba(0.0, 1.0, 0.0, pow(background_adj.get_value(),2.2));
    cr->fill();
    return false;
}

void Liveplay::display_tuner(bool v) {
    tuner->set_sensitive(v);
}

void Liveplay::on_realize() {
    liveplay_canvas->get_window()->set_composited(true);
}

class MidiControllerDisplay: public Gtk::ProgressBar, public gx_ui::GxUiItem {
private:
    gx_ui::GxUI& ui;
    gx_engine::MidiController& controller;
private:
    virtual void reflectZone();
    virtual bool hasChanged();
public:
    MidiControllerDisplay(gx_ui::GxUI& ui, gx_engine::MidiController& ctr, const Glib::ustring& name);
    ~MidiControllerDisplay();
};

MidiControllerDisplay::MidiControllerDisplay(gx_ui::GxUI& ui_, gx_engine::MidiController& ctr, const Glib::ustring& name)
    : Gtk::ProgressBar(), gx_ui::GxUiItem(), ui(ui_), controller(ctr) {
    ui.registerZone(controller.get_zone(), this);
    set_size_request(300, 50);
    set_text(name);
    reflectZone();
}

MidiControllerDisplay::~MidiControllerDisplay() {
    ui.unregisterZone(controller.get_zone(), this);
}

bool MidiControllerDisplay::hasChanged() {
    return get_fraction() != controller.get();
}

void MidiControllerDisplay::reflectZone() {
    set_fraction(controller.get());
}

void Liveplay::add_midi_elements() {
    int left = 0;
    int top = 0;
    int top_max = 6;
    int left_max = 3;
    Gtk::Table::TableList& tl = midictrl_table->children();
    tl.erase(tl.begin(), tl.end());
    for (int i = 0; i < gx_engine::controller_map.size(); i++) {
        gx_engine::midi_controller_list& cl = gx_engine::controller_map[i];
	if (cl.empty()) {
	    continue;
	}
	std::string v = gx_engine::midi_std_ctr[i];
	if (v.empty()) {
	    v = Glib::ustring::compose("controller %1", i);
	}
#if 0
	cout << v << ": " << endl;
        for (gx_engine::midi_controller_list::iterator j = cl.begin(); j != cl.end(); ++j) {
            gx_engine::Parameter& p = j->getParameter();
	    cout << Glib::ustring::compose(" %1/%2", p.l_group(), p.l_name());
	}
	cout << endl;
#endif
	midictrl_table->attach(
	    *manage(new MidiControllerDisplay(ui, *cl.begin(), v)),
	    left, left+1, top, top+1);
	top += 1;
	if (top >= top_max) {
	    top = 0;
	    left += 1;
	}
	if (left >= left_max) {
	    break;
	}
    }
    midictrl_table->show_all();
}
