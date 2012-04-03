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
 ** class TunerSwitcher
 */

static const int no_note = 1000;
static const int bad_note = 1002;

inline bool is_no_note(float n) {
    return abs(n - no_note) < 1;
}

TunerSwitcher::TunerSwitcher(Liveplay &lp_)
    : lp(lp_),
      switcher_conn(),
      timeout_conn(),
      current_note(),
      state(normal_mode),
      old_engine_state(),
      new_engine_state(),
      old_tuner_active(),
      new_tuner_active(),
      last_bank_idx(),
      last_preset_idx() {
}

bool TunerSwitcher::display_bank_key(int idx) {
    last_bank_idx = lp.gx_settings.banks.size() - idx - 1;
    Glib::ustring bank = lp.gx_settings.banks.get_name(last_bank_idx);
    if (bank.empty()) {
	lp.display("--", "--");
	return false;
    }
    lp.display(bank, "");
    return true;
}

bool TunerSwitcher::display_preset_key(int idx) {
    last_preset_idx = idx;
    Glib::ustring bank = lp.gx_settings.banks.get_name(last_bank_idx);
    if (bank.empty()) {
	lp.display("??", gx_system::to_string(idx+1));
	return false;
    }
    gx_system::PresetFile *f = lp.gx_settings.banks.get_file(bank);
    if (idx >= f->size()) {
	lp.display(bank, gx_system::to_string(idx+1));
	return false;
    }
    lp.display(bank, f->get_name(idx));
    return true;
}

void TunerSwitcher::try_load_preset() {
    if (state == wait_stop) {
	switch (last_bank_idx) {
	case mute_on:    new_engine_state = gx_engine::kEngineOff;    break;
	case mute_off:   new_engine_state = gx_engine::kEngineOn;     break;
	case bypass_on:  new_engine_state = gx_engine::kEngineBypass; break;
	case bypass_off: new_engine_state = gx_engine::kEngineOn;     break;
	case tuner_on:   new_tuner_active = true;  break;
	case tuner_off:  new_tuner_active = false; break;
	default:
	    Glib::ustring bank = lp.gx_settings.banks.get_name(last_bank_idx);
	    if (!bank.empty()) {
		gx_system::PresetFile *f = lp.gx_settings.banks.get_file(bank);
		if (last_preset_idx < f->size()) {
		    Glib::ustring preset = f->get_name(last_preset_idx);
		    if (preset != lp.gx_settings.get_current_name() || bank != lp.gx_settings.get_current_bank()) {
			lp.gx_settings.load_preset(f, preset);
			return;
		    }
		}
	    }
	    break;
	}
    }
    lp.on_selection_changed();
}

void TunerSwitcher::set_state(SwitcherState newstate) {
    if (state == newstate) {
	return;
    }
    state = newstate;
    bool sens = true;
    Gtk::StateType st = Gtk::STATE_NORMAL;
    switch (state) {
    case normal_mode:
	break;
    case wait_start:
	sens = false;
	st = Gtk::STATE_SELECTED;
	break;
    case listening:
	st = Gtk::STATE_SELECTED;
	break;
    case wait_stop:
	st = Gtk::STATE_PRELIGHT;
	break;
    default:
	assert(false);
	break;
    }
    lp.liveplay_bank->set_sensitive(sens);
    lp.liveplay_bank->set_state(st);
    lp.liveplay_preset->set_sensitive(sens);
    lp.liveplay_preset->set_state(st);
}

bool TunerSwitcher::on_note_timeout() {
    if (-24 <= current_note && current_note < -10) {
	set_state(listening);
	display_bank_key(current_note - (-24));
    } else if (current_note >= -10 && current_note <= 7) {
	if (display_preset_key(current_note - (-10))) {
	    set_state(wait_stop);
	} else {
	    set_state(listening);
	}
    } else if (current_note == -25) {
	if (old_engine_state != gx_engine::kEngineOff) {
	    lp.display("", _("MUTE"));
	    last_bank_idx = mute_on;
	} else {
	    lp.display("", _("UNMUTE"));
	    last_bank_idx = mute_off;
	}
	set_state(wait_stop);
    } else if (current_note == -26) {
	if (old_engine_state != gx_engine::kEngineBypass) {
	    lp.display("", _("BYPASS"));
	    last_bank_idx = bypass_on;
	} else {
	    lp.display("", _("BYPASS OFF"));
	    last_bank_idx = bypass_off;
	}
	set_state(wait_stop);
    } else if (current_note < 26) {
	if (!old_tuner_active) {
	    lp.display("", _("TUNER ON"));
	    last_bank_idx = tuner_on;
	} else {
	    lp.display("", _("TUNER OFF"));
	    last_bank_idx = tuner_off;
	}
	set_state(wait_stop);
    }
    return false;
}

bool TunerSwitcher::on_state_timeout() {
    if (state == wait_start) {
	set_state(listening);
	current_note = no_note;
	if (lp.gx_settings.setting_is_preset()) {
	    last_bank_idx = lp.gx_settings.banks.get_index(lp.gx_settings.get_current_bank());
	    last_preset_idx = lp.gx_settings.get_current_bank_file()->get_index(lp.gx_settings.get_current_name());
	} else {
	    last_bank_idx = last_preset_idx = 0; //FIXME
	}
    } else {
	assert(state == wait_stop);
	try_load_preset();
	set_active(false);
    }
    return false;
}

void TunerSwitcher::on_tuner_freq_changed() {
    const float precision = 0.3;
    float note = lp.engine.tuner.get_note();
    if (state == wait_start) {
	if (is_no_note(note)) {
	    if (!timeout_conn.connected()) {
		current_note = no_note;
		timeout_conn = Glib::signal_timeout().connect(
		    sigc::mem_fun(this, &TunerSwitcher::on_state_timeout),
		    40);
	    }
	} else {
	    timeout_conn.disconnect();
	}
	return;
    }
    if (abs(current_note - note) < precision) {
	return;
    }
    if (state == wait_stop) {
	if (is_no_note(note)) {
	    if (!is_no_note(current_note)) {
		timeout_conn.disconnect();
	    }
	    if (!timeout_conn.connected()) {
		current_note = no_note;
		timeout_conn = Glib::signal_timeout().connect(
		    sigc::mem_fun(this, &TunerSwitcher::on_state_timeout),
		    40);
	    }
	    return;
	}
    }
    timeout_conn.disconnect();
    float n = round(note);
    if (abs(note - n) < precision) {
	current_note = n;
	if (!is_no_note(current_note)) {
	    timeout_conn = Glib::signal_timeout().connect(
		sigc::mem_fun(this, &TunerSwitcher::on_note_timeout),
		40);
	}
    } else {
	current_note = bad_note;
    }
}

void TunerSwitcher::set_active(bool v) {
    if (get_active() == v) {
	return;
    }
    if (v) {
	bool running = lp.engine.tuner.plugin.on_off;
	lp.engine.tuner.used_for_switching(true);
	state = wait_start;
	new_engine_state = old_engine_state = lp.engine.get_state();
	lp.engine.set_state(gx_engine::kEngineOff);
	new_tuner_active = old_tuner_active = lp.actions.livetuner->get_active();
	lp.actions.livetuner->set_active(false);
	lp.liveplay_preset->set_sensitive(false);
	switcher_conn = lp.engine.tuner.signal_freq_changed().connect(
	    sigc::mem_fun(this, &TunerSwitcher::on_tuner_freq_changed));
	if (running) {
	    on_tuner_freq_changed();
	}
    } else {
	switcher_conn.disconnect();
	timeout_conn.disconnect();
	lp.engine.tuner.used_for_switching(false);
	set_state(normal_mode);
	lp.engine.set_state(new_engine_state);
	lp.actions.livetuner->set_active(new_tuner_active);
	lp.on_selection_changed();
    }
}


/****************************************************************
 ** class KeySwitcher
 */

void KeySwitcher::deactivate() {
    last_bank_key.clear();
    if (key_timeout.connected()) {
	key_timeout.disconnect();
	display_current();
    }
}

void KeySwitcher::display_key_error() {
    display_empty("??", "??");
}

void KeySwitcher::display_empty(const Glib::ustring& bank, const Glib::ustring& preset) {
    display(bank, preset);
    key_timeout.disconnect();
    if (last_bank_key.empty()) {
	key_timeout = Glib::signal_timeout().connect(
	    sigc::mem_fun(this, &KeySwitcher::display_current), 400);
    } else {
	key_timeout = Glib::signal_timeout().connect(
	    sigc::mem_fun(this, &KeySwitcher::display_selected_bank), 400);
    }
}

bool KeySwitcher::display_selected_bank() {
    display(last_bank_key, "");
    key_timeout = Glib::signal_timeout().connect(
	sigc::mem_fun(this, &KeySwitcher::display_current), 2000);
    return false;
}

bool KeySwitcher::display_current() {
    last_bank_key.clear();
    if (!gx_settings.setting_is_preset()) {
	display("----","");
    } else {
	display(gx_settings.get_current_bank(), gx_settings.get_current_name());
    }
    return false;
}

bool KeySwitcher::process_preset_key(int idx) {
    key_timeout.disconnect();
    Glib::ustring bank = last_bank_key;
    if (bank.empty()) {
	if (!gx_settings.setting_is_preset()) {
	    display_empty("??", gx_system::to_string(idx+1));
	    return false;
	}
	bank = gx_settings.get_current_bank();
    }
    gx_system::PresetFile *f = gx_settings.banks.get_file(bank);
    if (idx >= f->size()) {
	display_empty(bank, gx_system::to_string(idx+1)+"?");
	return false;
    } else {
	gx_settings.load_preset(f, f->get_name(idx));
	return true;
    }
}

bool KeySwitcher::process_bank_key(int idx) {
    key_timeout.disconnect();
    Glib::ustring bank = gx_settings.banks.get_name(gx_settings.banks.size() - idx - 1);
    if (bank.empty()) {
	display_empty("--", "--");
	return false;
    }
    last_bank_key = bank;
    display_selected_bank();
    return true;
}


/****************************************************************
 ** class Liveplay
 */

void Liveplay::display(const Glib::ustring& bank, const Glib::ustring& preset) {
    liveplay_bank->set_text(bank);
    liveplay_preset->set_text(preset);
}

bool Liveplay::do_action(GtkAccelGroup *accel_group, GObject *acceleratable,
			 guint keyval, GdkModifierType modifier,
			 GtkAction* act) {
    gtk_action_activate(act);
    return true;
}

bool Liveplay::on_keyboard_preset_select(GtkAccelGroup *accel_group, GObject *acceleratable,
					 guint keyval, GdkModifierType modifier, Liveplay& self) {
    if (keyval == GDK_KEY_0 || keyval == GDK_KEY_KP_0) {
	self.keyswitch.process_preset_key(9);
	return true;
    }
    if (keyval >= GDK_KEY_1 && keyval <= GDK_KEY_9) {
	self.keyswitch.process_preset_key(keyval - GDK_KEY_1);
	return true;
    }
    if (keyval >= GDK_KEY_KP_1 && keyval <= GDK_KEY_KP_9) {
	self.keyswitch.process_preset_key(keyval - GDK_KEY_KP_1);
	return true;
    }
    if (keyval >= GDK_KEY_a && keyval <= GDK_KEY_z) {
	self.keyswitch.process_bank_key(keyval - GDK_KEY_a);
	return true;
    }
    self.keyswitch.display_key_error();
    return true;
}

bool Liveplay::on_keyboard_toggle_mute(GtkAccelGroup *accel_group, GObject *acceleratable,
				       guint keyval, GdkModifierType modifier, Liveplay& self) {
    self.engine.set_state(self.engine.get_state() == gx_engine::kEngineOff ?
		     gx_engine::kEngineOn
		     : gx_engine::kEngineOff);
    return true;
}

bool Liveplay::on_keyboard_toggle_bypass(GtkAccelGroup *accel_group, GObject *acceleratable,
				       guint keyval, GdkModifierType modifier, Liveplay& self) {
    self.engine.set_state(self.engine.get_state() == gx_engine::kEngineBypass ?
		     gx_engine::kEngineOn
		     : gx_engine::kEngineBypass);
    return true;
}

bool Liveplay::on_keyboard_mode_switch(GtkAccelGroup *accel_group, GObject *acceleratable,
				       guint keyval, GdkModifierType modifier, Liveplay& self) {
    self.tuner_switcher.toggle();
    return true;
}

void Liveplay::on_switcher_toggled(bool v) {
    if (false) {
	tuner_switcher.set_active(v);
    } else {
	if (v) {
	    tuner_switcher.toggle();
	}
    }
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

class MyPaintBox: public Gxw::PaintBox {
private:
    Gtk::Adjustment *background_adj;
    MyPaintBox(BaseObjectType* cobject, Gtk::Adjustment *background_adj_)
	: Gxw::PaintBox(cobject), background_adj(background_adj_) {}
public:
    static MyPaintBox *create_from_builder(BaseObjectType* cobject, Gtk::Adjustment *background_adj) {
	return new MyPaintBox(cobject, background_adj); }
    virtual bool on_expose_event(GdkEventExpose *event);
};

bool MyPaintBox::on_expose_event(GdkEventExpose *event) {
    call_paint_func(event);
    Cairo::RefPtr<Cairo::Context> cr = Glib::wrap(event->window, true)->create_cairo_context();
    gdk_cairo_region(cr->cobj(), event->region);
    cr->clip();
    cr->set_source_rgba(0.0, 0.0, 0.0, 1-background_adj->get_value());
    cr->paint();
    foreach(sigc::bind(sigc::mem_fun(this, &MyPaintBox::propagate_expose), event));
    return true;
}


Liveplay::Liveplay(
    const gx_system::CmdlineOptions& options, gx_engine::GxEngine& engine_, gx_preset::GxSettings& gx_settings_,
    const std::string& fname, const GxActions& actions_)
    : ui(),
      bld(),
      engine(engine_),
      gx_settings(gx_settings_),
      actions(actions_),
      use_composite(),
      brightness_adj(),
      background_adj(),
      keyswitch(gx_settings_, sigc::mem_fun(this, &Liveplay::display)),
      midi_conn(),
      window(),
      tuner_switcher(*this),
      switcher_signal(&ui, &gx_engine::parameter_map["ui.live_play_switcher"].getBool().get_value()), //FIXME
      mouse_hide_conn() {
    const char *id_list[] = {"LivePlay", 0};
    bld = gx_gui::GxBuilder::create_from_file(fname, &ui, id_list);
    bld->get_toplevel("LivePlay", window);

    bld->find_widget("liveplay_bank", liveplay_bank);
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
    brightness_adj = brightness_slider->get_adjustment();
    background_adj = background_slider->get_adjustment();
    MyPaintBox *liveplay_paintbox;
    bld->find_widget_derived(
	"liveplay_paintbox", liveplay_paintbox,
	sigc::bind(
	    sigc::ptr_fun(MyPaintBox::create_from_builder),
	    background_adj));

    Glib::RefPtr<Gdk::Pixbuf> pb = Gdk::Pixbuf::create_from_file(
	options.get_style_filepath("bypass.svg"), 300, 150);
    bypass_image->set(pb);
    pb = Gdk::Pixbuf::create_from_file(
	options.get_style_filepath("mute.svg"), 300, 150);
    mute_image->set(pb);
    use_composite = window->get_display()->supports_composite();
    if (use_composite) {
	brightness_adj->signal_value_changed().connect(sigc::mem_fun(this, &Liveplay::on_brightness_changed));
	liveplay_canvas->signal_realize().connect(sigc::mem_fun(this, &Liveplay::on_realize));
	window->signal_expose_event().connect(
	    sigc::mem_fun(this, &Liveplay::window_expose_event), true);
    } else {
	brightness_box->hide();
    }
    background_adj->signal_value_changed().connect(
	sigc::mem_fun(this, &Liveplay::on_background_changed));
    Glib::RefPtr<Gdk::Screen> screen = liveplay_canvas->get_screen();
    Glib::RefPtr<Gdk::Colormap> rgba = screen->get_rgba_colormap();
    liveplay_canvas->set_colormap(rgba);
    liveplay_canvas->set_app_paintable(true);
    window->signal_delete_event().connect(
	sigc::mem_fun(this, &Liveplay::on_delete));
    window->add_events(Gdk::POINTER_MOTION_HINT_MASK|Gdk::POINTER_MOTION_MASK);
    window->signal_motion_notify_event().connect(
	sigc::mem_fun(*this, &Liveplay::pointer_motion));

    gtk_activatable_set_related_action(
	GTK_ACTIVATABLE(liveplay_exit->gobj()), GTK_ACTION(actions.live_play->gobj()));
    Glib::RefPtr<Gtk::AccelGroup> ag = Gtk::AccelGroup::create();
    GClosure *cl = g_cclosure_new(G_CALLBACK(do_action), (gpointer)(actions.live_play->gobj()), 0);
    gtk_accel_group_connect_by_path(ag->gobj(), actions.live_play->get_accel_path().c_str(), cl);
    cl = g_cclosure_new(G_CALLBACK(do_action), (gpointer)(actions.live_play->gobj()), 0);
    gtk_accel_group_connect(ag->gobj(), GDK_KEY_Escape, (GdkModifierType)0, (GtkAccelFlags)0, cl);

    actions.group->add(
	actions.livetuner,
	sigc::compose(
	    sigc::mem_fun(this, &Liveplay::display_tuner),
	    sigc::mem_fun(actions.livetuner.operator->(), &Gtk::ToggleAction::get_active)));
    cl = g_cclosure_new(G_CALLBACK(do_action), (gpointer)(actions.livetuner->gobj()), 0);
    gtk_accel_group_connect(ag->gobj(), GDK_KEY_Return, (GdkModifierType)0, (GtkAccelFlags)0, cl);

    cl = g_cclosure_new(G_CALLBACK(do_action), (gpointer)(actions.quit->gobj()), 0);
    gtk_accel_group_connect_by_path(ag->gobj(), actions.quit->get_accel_path().c_str(), cl);

    cl = g_cclosure_new(G_CALLBACK(on_keyboard_toggle_mute), (gpointer)this, 0);
    gtk_accel_group_connect(ag->gobj(), GDK_KEY_M, GDK_CONTROL_MASK, (GtkAccelFlags)0, cl);

    cl = g_cclosure_new(G_CALLBACK(on_keyboard_toggle_bypass), (gpointer)this, 0);
    gtk_accel_group_connect(ag->gobj(), GDK_KEY_B, GDK_CONTROL_MASK, (GtkAccelFlags)0, cl);

    cl = g_cclosure_new(G_CALLBACK(on_keyboard_arrows), (gpointer)this, 0);
    gtk_accel_group_connect(ag->gobj(), GDK_KEY_Left, GDK_CONTROL_MASK, (GtkAccelFlags)0, cl);
    cl = g_cclosure_new(G_CALLBACK(on_keyboard_arrows), (gpointer)this, 0);
    gtk_accel_group_connect(ag->gobj(), GDK_KEY_Right, GDK_CONTROL_MASK, (GtkAccelFlags)0, cl);
    cl = g_cclosure_new(G_CALLBACK(on_keyboard_arrows), (gpointer)this, 0);
    gtk_accel_group_connect(ag->gobj(), GDK_KEY_Up, GDK_CONTROL_MASK, (GtkAccelFlags)0, cl);
    cl = g_cclosure_new(G_CALLBACK(on_keyboard_arrows), (gpointer)this, 0);
    gtk_accel_group_connect(ag->gobj(), GDK_KEY_Down, GDK_CONTROL_MASK, (GtkAccelFlags)0, cl);

    for (int n = GDK_KEY_0; n <= GDK_KEY_9; ++n) {
	cl = g_cclosure_new(G_CALLBACK(on_keyboard_preset_select), (gpointer)this, 0);
	gtk_accel_group_connect(ag->gobj(), n, (GdkModifierType)0, (GtkAccelFlags)0, cl);
    }
    for (int n = GDK_KEY_KP_0; n <= GDK_KEY_KP_9; ++n) {
	cl = g_cclosure_new(G_CALLBACK(on_keyboard_preset_select), (gpointer)this, 0);
	gtk_accel_group_connect(ag->gobj(), n, (GdkModifierType)0, (GtkAccelFlags)0, cl);
    }
    for (int n = GDK_KEY_A; n <= GDK_KEY_Z; ++n) {
	cl = g_cclosure_new(G_CALLBACK(on_keyboard_preset_select), (gpointer)this, 0);
	gtk_accel_group_connect(ag->gobj(), n, (GdkModifierType)0, (GtkAccelFlags)0, cl);
    }

    cl = g_cclosure_new(G_CALLBACK(on_keyboard_mode_switch), (gpointer)this, 0);
    gtk_accel_group_connect(ag->gobj(), GDK_KEY_space, (GdkModifierType)0, (GtkAccelFlags)0, cl);
    switcher_signal.changed.connect(sigc::mem_fun(this, &Liveplay::on_switcher_toggled));
    
    window->add_accel_group(ag);

    engine.signal_state_change().connect(
	sigc::mem_fun(this, &Liveplay::on_engine_state_change));
    gx_settings.signal_selection_changed().connect(
	sigc::mem_fun(this, &Liveplay::on_selection_changed));

    on_engine_state_change(engine.get_state());
    on_selection_changed();
}

Liveplay::~Liveplay() {
    delete window;
}

bool Liveplay::pointer_motion(GdkEventMotion* event) {
    if (event) {
	gdk_event_request_motions(event);
    }
    if (mouse_hide_conn.connected()) {
	mouse_hide_conn.disconnect();
    } else {
	window->get_window()->set_cursor();
    }
    mouse_hide_conn = Glib::signal_timeout().connect_seconds(
	sigc::bind_return(
	    sigc::bind(
		sigc::mem_fun1(window->get_window().operator->(), &Gdk::Window::set_cursor),
		Gdk::Cursor(Gdk::BLANK_CURSOR)),
	    false),
	5);
    return false;
}

void Liveplay::on_engine_state_change(gx_engine::GxEngineState state) {
    switch (state) {
    case gx_engine::kEngineOff:    bypass_image->hide(); mute_image->show(); break;
    case gx_engine::kEngineOn:     bypass_image->hide(); mute_image->hide(); break;
    case gx_engine::kEngineBypass: bypass_image->show(); mute_image->hide(); break;
    }
}

void Liveplay::on_selection_changed() {
    keyswitch.deactivate();
    if (!gx_settings.setting_is_preset()) {
	display("----","");
    } else {
	display(gx_settings.get_current_bank(), gx_settings.get_current_name());
    }
}

void Liveplay::on_live_play(Glib::RefPtr<Gtk::ToggleAction> act) {
    if (act->get_active()) {
	window->fullscreen();
	midi_conn = gx_engine::controller_map.signal_changed().connect(
	    sigc::mem_fun(this, &Liveplay::add_midi_elements));
	add_midi_elements();
	window->show();
    } else {
	midi_conn.disconnect();
	keyswitch.deactivate();
	tuner_switcher.set_active(false);
	window->hide();
    }
}

bool Liveplay::window_expose_event(GdkEventExpose *event) {
    Cairo::RefPtr<Cairo::Context> cr = Glib::wrap(event->window, true)->create_cairo_context();
    Gtk::Allocation a = liveplay_canvas->get_allocation();
    Gdk::Region region(a);
    region.intersect(Glib::wrap(event->region, true));
    Gdk::Cairo::add_region_to_path(cr, region);
    cr->clip();
    cr->set_operator(Cairo::OPERATOR_SOURCE);
    cr->set_source_rgb(0,0,0);
    cr->paint();
    //gdk_cairo_set_source_window(cr->cobj(), liveplay_canvas->get_window()->gobj(), a.get_x(), a.get_y()); gtk 2.24
    gdk_cairo_set_source_pixmap(cr->cobj(), liveplay_canvas->get_window()->gobj(), a.get_x(), a.get_y());
    cr->paint_with_alpha(pow(brightness_adj->get_value(),2.2));
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

void Liveplay::display_tuner(bool v) {
    tuner->set_sensitive(v);
}

void Liveplay::on_realize() {
    liveplay_canvas->get_window()->set_composited(true);
}

class MidiControllerDisplay: public Gtk::ProgressBar, public gx_ui::GxUiItem {
private:
    gx_ui::GxUI& ui;
    unsigned int ctr;
    const gx_engine::midi_controller_list& controller;
private:
    virtual void reflectZone();
    virtual bool hasChanged();
public:
    MidiControllerDisplay(gx_ui::GxUI& ui, unsigned int n, const gx_engine::midi_controller_list& ctrl, const Glib::ustring& name);
    ~MidiControllerDisplay();
};

MidiControllerDisplay::MidiControllerDisplay(gx_ui::GxUI& ui_, unsigned int n, const gx_engine::midi_controller_list& ctrl, const Glib::ustring& name)
    : Gtk::ProgressBar(), gx_ui::GxUiItem(), ui(ui_), ctr(n), controller(ctrl) {
    ui.registerZone(gx_engine::MidiControllerList::get_midi_control_zone(ctr), this);
    set_size_request(300, 50);
    set_text(name);
    reflectZone();
}

MidiControllerDisplay::~MidiControllerDisplay() {
    ui.unregisterZone(gx_engine::MidiControllerList::get_midi_control_zone(ctr), this);
}

bool MidiControllerDisplay::hasChanged() {
    int v = gx_engine::MidiControllerList::get_last_midi_control_value(ctr);
    if (v >= 0) {
	return get_fraction() != v / 127.0;
    }
    if (get_sensitive()) {
	set_sensitive(false);
    }
    return false;
}

void MidiControllerDisplay::reflectZone() {
    int v = gx_engine::MidiControllerList::get_last_midi_control_value(ctr);
    if (v >= 0) {
	set_fraction(v / 127.0);
    }
}

void Liveplay::add_midi_elements() {
    int left = 0;
    int top = 0;
    int top_max = 3;
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
	    v = Glib::ustring::compose("%1: ", i);
	}
        for (gx_engine::midi_controller_list::iterator j = cl.begin(); j != cl.end(); ++j) {
            gx_engine::Parameter& p = j->getParameter();
	    v += Glib::ustring::compose(" %1/%2", p.l_group(), p.l_name());
	}
	midictrl_table->attach(
	    *manage(new MidiControllerDisplay(ui, i, cl, v)),
	    left, left+1, top, top+1, Gtk::AttachOptions(0));
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
