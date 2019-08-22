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
    if (!machine.setting_is_preset()) {
	display("----","");
    } else {
	display(machine.get_current_bank(), machine.get_current_name());
    }
    return false;
}

bool KeySwitcher::process_preset_key(int idx) {
    key_timeout.disconnect();
    Glib::ustring bank = last_bank_key;
    if (bank.empty()) {
	if (!machine.setting_is_preset()) {
	    display_empty("??", gx_system::to_string(idx+1));
	    return false;
	}
	bank = machine.get_current_bank();
    }
    gx_system::PresetFileGui *f = machine.get_bank_file(bank);
    if (idx >= f->size()) {
	display_empty(bank, gx_system::to_string(idx+1)+"?");
	return false;
    } else {
	machine.load_preset(f, f->get_name(idx));
	return true;
    }
}

bool KeySwitcher::process_bank_key(int idx) {
    key_timeout.disconnect();
    Glib::ustring bank = machine.get_bank_name(machine.bank_size() - idx - 1);
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
    if (keyval >= GDK_KEY_0 && keyval <= GDK_KEY_9) {
	self.keyswitch.process_preset_key(keyval - GDK_KEY_0);
	return true;
    }
    if (keyval >= GDK_KEY_KP_0 && keyval <= GDK_KEY_KP_9) {
	self.keyswitch.process_preset_key(keyval - GDK_KEY_KP_0);
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
    self.machine.set_state(self.machine.get_state() == gx_engine::kEngineOff ?
		     gx_engine::kEngineOn
		     : gx_engine::kEngineOff);
    return true;
}

bool Liveplay::on_keyboard_toggle_bypass(GtkAccelGroup *accel_group, GObject *acceleratable,
				       guint keyval, GdkModifierType modifier, Liveplay& self) {
    self.machine.set_state(self.machine.get_state() == gx_engine::kEngineBypass ?
		     gx_engine::kEngineOn
		     : gx_engine::kEngineBypass);
    return true;
}

bool Liveplay::on_keyboard_mode_switch(GtkAccelGroup *accel_group, GObject *acceleratable,
				       guint keyval, GdkModifierType modifier, Liveplay& self) {
    self.machine.tuner_switcher_toggle(self.actions.livetuner->get_active());
    return true;
}

void Liveplay::set_display_state(TunerSwitcher::SwitcherState newstate) {
    bool sens = true;
    Gtk::StateType st = Gtk::STATE_NORMAL;
    switch (newstate) {
    case TunerSwitcher::normal_mode:
	break;
    case TunerSwitcher::wait_start:
	sens = false;
	st = Gtk::STATE_SELECTED;
	break;
    case TunerSwitcher::listening:
	st = Gtk::STATE_SELECTED;
	break;
    case TunerSwitcher::wait_stop:
	st = Gtk::STATE_PRELIGHT;
	break;
    default:
	assert(false);
	break;
    }
    liveplay_bank->set_sensitive(sens);
    liveplay_bank->set_state(st);
    liveplay_preset->set_sensitive(sens);
    liveplay_preset->set_state(st);
}

bool Liveplay::on_keyboard_arrows(GtkAccelGroup *accel_group, GObject *acceleratable,
				       guint keyval, GdkModifierType modifier, Liveplay& self) {
    if (keyval == GDK_KEY_Left || keyval == GDK_KEY_Right) {
	Glib::RefPtr<Gtk::Adjustment> a = self.brightness_slider->get_adjustment();
	double val = a->get_value();
	double step = a->get_step_increment();
	if (keyval == GDK_KEY_Left) {
	    val -= step;
	} else {
	    val += step;
	}
	a->set_value(val);
    } else {
	Glib::RefPtr<Gtk::Adjustment> a = self.background_slider->get_adjustment();
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
    Glib::RefPtr<Gtk::Adjustment> background_adj;
    MyPaintBox(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Adjustment> &background_adj_)
	: Gxw::PaintBox(cobject), background_adj(background_adj_) {}
public:
    static MyPaintBox *create_from_builder(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Adjustment>& background_adj) {
	return new MyPaintBox(cobject, background_adj); }
    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr);
};

bool MyPaintBox::on_draw(const Cairo::RefPtr<Cairo::Context> &cr) {
    call_paint_func(cr->cobj());
    cr->set_source_rgba(0.0, 0.0, 0.0, 1-background_adj->get_value());
    cr->paint();
    foreach(sigc::bind(sigc::mem_fun(this, &MyPaintBox::propagate_draw), cr));
    return true;
}


Liveplay::Liveplay(
    const gx_system::CmdlineOptions& options, gx_engine::GxMachineBase& machine_,
    const std::string& fname, const GxActions& actions_)
    : bld(),
      machine(machine_),
      actions(actions_),
      use_composite(),
      brightness_adj(),
      background_adj(),
      keyswitch(machine_, sigc::mem_fun(this, &Liveplay::display)),
      midi_conn(),
      window(),
      mouse_hide_conn() {
    const char *id_list[] = {"LivePlay", 0};
    bld = gx_gui::GxBuilder::create_from_file(fname, &machine, id_list);
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
    Glib::RefPtr<Gdk::Pixbuf> pb;
    try {
      pb = Gdk::Pixbuf::create_from_file(
	  options.get_style_filepath("live_bypass.png"));
      bypass_image->set(pb);
    } catch (const Glib::FileError& ex) {
        gx_print_error("liveplay", ex.what());
    } catch (const Gdk::PixbufError& ex) {
        gx_print_error("liveplay", ex.what());
    } catch(...) {
        gx_print_error("liveplay", "failed to load pixmap live_bypass.png");
    }
    try {
      pb = Gdk::Pixbuf::create_from_file(
	  options.get_style_filepath("live_mute.png"));
      mute_image->set(pb);
    } catch (const Glib::FileError& ex) {
        gx_print_error("liveplay", ex.what());
    } catch (const Gdk::PixbufError& ex) {
        gx_print_error("liveplay", ex.what());
    } catch(...) {
        gx_print_error("liveplay", "failed to load pixmap live_mute.png");
    }   
    use_composite = window->get_display()->supports_composite();
    if (use_composite) {
	brightness_adj->signal_value_changed().connect(sigc::mem_fun(this, &Liveplay::on_brightness_changed));
	liveplay_canvas->signal_realize().connect(sigc::mem_fun(this, &Liveplay::on_realize));
	window->signal_draw().connect(
	    sigc::mem_fun(this, &Liveplay::window_draw), true);
    } else {
	brightness_box->hide();
    }
    background_adj->signal_value_changed().connect(
	sigc::mem_fun(this, &Liveplay::on_background_changed));
    Glib::RefPtr<Gdk::Screen> screen = liveplay_canvas->get_screen();
    Glib::RefPtr<Gdk::Visual> rgba = screen->get_rgba_visual();
    gtk_widget_set_visual(liveplay_canvas->gobj(), rgba->gobj());
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
    machine.tuner_switcher_signal_display().connect(
	sigc::mem_fun(this, &Liveplay::display));
    machine.tuner_switcher_signal_set_state().connect(
	sigc::mem_fun(this, &Liveplay::set_display_state));
    machine.tuner_switcher_signal_selection_done().connect(
	sigc::mem_fun(this, &Liveplay::on_selection_done));

    window->add_accel_group(ag);

    machine.signal_state_change().connect(
	sigc::mem_fun(this, &Liveplay::on_engine_state_change));
    machine.signal_selection_changed().connect(
	sigc::mem_fun(this, &Liveplay::on_selection_changed));

    on_engine_state_change(machine.get_state());
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
    Glib::RefPtr<Gdk::Display> disp = window->get_display();
    mouse_hide_conn = Glib::signal_timeout().connect_seconds(
	sigc::bind_return(
	    sigc::bind(
		sigc::mem_fun1(window->get_window().operator->(), &Gdk::Window::set_cursor),
		Gdk::Cursor::create(disp, Gdk::BLANK_CURSOR)),
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

void Liveplay::on_selection_done(bool v) {
    keyswitch.deactivate();
    if (!machine.setting_is_preset()) {
	display("----","");
    } else {
	display(machine.get_current_bank(), machine.get_current_name());
    }
    actions.livetuner->set_active(v);
}

void Liveplay::on_selection_changed() {
    keyswitch.deactivate();
    if (!machine.setting_is_preset()) {
	display("----","");
    } else {
	display(machine.get_current_bank(), machine.get_current_name());
    }
}

void Liveplay::on_live_play(Glib::RefPtr<Gtk::ToggleAction> act) {
    if (act->get_active()) {
	window->fullscreen();
	midi_conn = machine.signal_midi_changed().connect(
	    sigc::mem_fun(this, &Liveplay::add_midi_elements));
	add_midi_elements();
	window->show();
    } else {
	midi_conn.disconnect();
	keyswitch.deactivate();
	machine.tuner_switcher_deactivate();
	window->hide();
    }
    actions.livetuner->toggled();
}

bool Liveplay::window_draw(const Cairo::RefPtr<Cairo::Context> &cr) {
    cr->set_operator(Cairo::OPERATOR_SOURCE);
    cr->set_source_rgb(0,0,0);
    cr->paint();
    gdk_cairo_set_source_window(cr->cobj(), liveplay_canvas->get_window()->gobj(), 0, 0);
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
    tuner->set_visible(v);
}

void Liveplay::on_realize() {
    liveplay_canvas->get_window()->set_composited(true);
}

class MidiControllerDisplay: public Gtk::ProgressBar {
private:
    int ctr;
private:
    void midi_value_changed(int ctr, int val);
public:
    MidiControllerDisplay(gx_engine::GxMachineBase& machine, unsigned int n, const gx_engine::midi_controller_list& ctrl, const Glib::ustring& name);
    ~MidiControllerDisplay();
};

MidiControllerDisplay::MidiControllerDisplay(gx_engine::GxMachineBase& machine, unsigned int n, const gx_engine::midi_controller_list& ctrl, const Glib::ustring& name)
    : Gtk::ProgressBar(), ctr(n) {
    machine.signal_midi_value_changed().connect(
	sigc::mem_fun(this, &MidiControllerDisplay::midi_value_changed));
    set_size_request(400, 50);
    set_text(name);
    machine.request_midi_value_update();
}

MidiControllerDisplay::~MidiControllerDisplay() {
}

void MidiControllerDisplay::midi_value_changed(int c, int v) {
    if (c != ctr) {
	return;
    }
    if (v >= 0) {
	set_sensitive(true);
	set_fraction(v / 127.0);
    } else {
	set_sensitive(false);
    }
}

void Liveplay::add_midi_elements() {
    int left = 0;
    int top = 0;
    int top_max = 4;
    int left_max = 3;
    auto tl = midictrl_table->get_children();
    for (auto iter = tl.begin(); iter != tl.end(); iter++) {
        if (*iter) {
            midictrl_table->remove(**iter);
        }
    }
    tl.erase(tl.begin(), tl.end());
    for (int i = 0; i < machine.midi_size(); i++) {
        gx_engine::midi_controller_list& cl = machine.midi_get(i);
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
	    *manage(new MidiControllerDisplay(machine, i, cl, v)),
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
