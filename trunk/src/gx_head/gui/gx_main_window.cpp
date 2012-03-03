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

#include <guitarix.h>
#include <gxw/GxLevelSlider.h>

/****************************************************************
 ** class TextLoggingBox
 */

// color depending on msg type
TextLoggingBox::tab_table TextLoggingBox::tagdefs[] = {
    {"colinfo", "#0000ff"},
    {"colwarn", "#ff8800"},
    {"colerr", "#ff0000"},
};

TextLoggingBox::TextLoggingBox()
    : box(),
      scrollbox(),
      tbox(),
      highest_unseen_msg_level(-1),
      msg_level_changed() {

    set_default_size(600, 200);
    set_decorated(true);
    set_resizable(true);
    set_gravity(Gdk::GRAVITY_SOUTH);
    set_keep_below(false);
    set_title(_("Logging Window"));
    set_type_hint(Gdk::WINDOW_TYPE_HINT_UTILITY);

    box.set_border_width(0);
    scrollbox.set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_AUTOMATIC);

    add(box);

    tbox.set_wrap_mode(Gtk::WRAP_WORD_CHAR);
    tbox.set_border_width(0);
    tbox.set_editable(false);
    tbox.set_cursor_visible(false);
    tbox.set_pixels_above_lines(0);
    tbox.set_pixels_below_lines(2);
    tbox.set_justification(Gtk::JUSTIFY_LEFT);
    tbox.set_left_margin(5);
    tbox.set_indent(0);

    Glib::RefPtr<Gtk::TextBuffer> buffer = tbox.get_buffer();
    for (int i = 0; i < gx_system::kMessageTypeCount; i++) {
	tags[i] = buffer->create_tag(tagdefs[i].tagname);
	tags[i]->property_foreground() = tagdefs[i].tag_color;
    }

    box.add(scrollbox);
    scrollbox.add(tbox);
    tbox.show();
    scrollbox.show();
    tbox.set_size_request(-1, 50);
    box.show();
    gx_system::Logger::get_logger().signal_message().connect(
	sigc::mem_fun(*this, &TextLoggingBox::show_msg));
    gx_system::Logger::get_logger().unplug_queue();
}

TextLoggingBox::~TextLoggingBox() {
}

void TextLoggingBox::on_show() {
    highest_unseen_msg_level = gx_system::kMessageTypeCount;
    Gtk::Window::on_show();
}

void TextLoggingBox::on_hide() {
    highest_unseen_msg_level = -1;
    Gtk::Window::on_hide();
}

void TextLoggingBox::show_msg(string msgbuf, gx_system::GxMsgType msgtype, bool plugged) {
    assert(0 <= msgtype && msgtype < gx_system::kMessageTypeCount);

    // retrieve gtk text buffer
    Glib::RefPtr<Gtk::TextBuffer> buffer = tbox.get_buffer();

    // how many lines to keep
    const int nlines = 50;

    // delete first line when window filled up
    int linecount = buffer->get_line_count(); // empty buffer == 1 line
    if (linecount >= nlines) {
	Gtk::TextIter iter1 = buffer->get_iter_at_line(0);
	Gtk::TextIter iter2 = buffer->get_iter_at_line(1);
        buffer->erase(iter1, iter2);
    }

    Gtk::TextIter iter = buffer->end();
    if (buffer->get_char_count() > 0) {
        iter = buffer->insert(iter, "\n");
    }

    buffer->insert_with_tag(iter, msgbuf, tags[msgtype]);
    scrollbox.get_vadjustment()->set_value(10000);
    // scroll to end (big value, gets clamped to max)

    // modify expander bg color is closed
    if (msgtype > highest_unseen_msg_level) {
        highest_unseen_msg_level = msgtype;
	msg_level_changed();
    }
}

/****************************************************************
 ** KeyFinder
 ** finds next unused Key in a GtkAccelGroup
 */

class KeyFinder {
private:
    typedef list<GtkAccelKey> accel_list;
    unsigned int next_key;
    accel_list l;
    static gboolean add_keys_to_list(GtkAccelKey *key, GClosure *cl, gpointer data);
public:
    KeyFinder(Glib::RefPtr<Gtk::AccelGroup> group);
    ~KeyFinder();
    int operator()();
};

/****************************************************************
 ** KeyFinder
 ** finds next unused Key in a GtkAccelGroup
 */

KeyFinder::KeyFinder(Glib::RefPtr<Gtk::AccelGroup> group) {
    next_key = GDK_a;
    gtk_accel_group_find(group->gobj(), add_keys_to_list, static_cast<gpointer>(&l));
}

KeyFinder::~KeyFinder() {
}

gboolean KeyFinder::add_keys_to_list(GtkAccelKey *key, GClosure *cl, gpointer data) {
    accel_list* l = (accel_list*)data;
    if (key->accel_mods == GDK_SHIFT_MASK) {
	l->push_back(*key);
    }
    return false;
}

int KeyFinder::operator()() {
    while (next_key <= GDK_z) {
	bool found = false;
	for (accel_list::iterator i = l.begin(); i != l.end(); ++i) {
	    if (next_key == i->accel_key) {
		found = true;
		break;
	    }
	}
	if (!found) {
	    return next_key++;
	}
	next_key++;
    }
    return -1;
}

/****************************************************************
 ** GxUiRadioMenu
 ** adds the values of an UEnumParameter as Gtk::RadioMenuItem's
 ** to a Gtk::MenuShell
 */

class TubeKeys {
private:
    static unsigned int keysep[];
    unsigned int ks;
public:
    TubeKeys(): ks(0) {};
    int operator()();
};

unsigned int TubeKeys::keysep[] = {
    GDK_a, GDK_b, GDK_c, GDK_d, GDK_e, 0,
    GDK_f, 0,
    GDK_g, GDK_h, GDK_i, GDK_j, 0,
    GDK_k, GDK_l, GDK_m, GDK_n, 0,
    GDK_o, GDK_p, GDK_q, GDK_r
};

inline int TubeKeys::operator()() {
    if (ks < sizeof(keysep)/sizeof(keysep[0])) {
	return keysep[ks++];
    }
    return -1;
}

GxUiRadioMenu::GxUiRadioMenu(gx_ui::GxUI* ui, gx_engine::UIntParameter& param_):
    gx_ui::GxUiItemUInt(ui, &param_.get_value()),
    param(param_) {
}

void GxUiRadioMenu::setup(const Glib::ustring& prefix, const Glib::ustring& postfix,
			  Glib::RefPtr<Gtk::UIManager>& uimanager, Glib::RefPtr<Gtk::ActionGroup>& actiongroup) {
    int i, c;
    const value_pair *p;
    TubeKeys next_key;
    //KeyFinder next_key(ag); // uncomment to find out which keys are free...
    Glib::ustring s = prefix;
    Gtk::RadioButtonGroup group;
    for (p = param.getValueNames(), i = 0; p->value_id; p++, i++) {
	c = next_key();
	if (c == 0) {
	    s += "<separator/>";
	    c = next_key();
	}
	Glib::ustring actname = Glib::ustring::compose("Enum_%1.%2", param.id(), p->value_id);
	s += Glib::ustring::compose("<menuitem action=\"%1\"/>", actname);
	Glib::RefPtr<Gtk::RadioAction> act = Gtk::RadioAction::create(group, actname, param.value_label(*p));
	act->property_value().set_value(param.lower+i);
	if (c > 0) {
	    actiongroup->add(act, Gtk::AccelKey(Glib::ustring::compose("<shift>%1", (char)c)));
	} else {
	    actiongroup->add(act);
	}
	if (i == 0) {
	    act->signal_changed().connect(
		sigc::mem_fun(*this, &GxUiRadioMenu::on_changed));
	    action = act;
	}
    }
    s.append(postfix);
    uimanager->add_ui_from_string(s);
}

void GxUiRadioMenu::reflectZone() {
    int v = *fZone;
    fCache = v;
    action->set_current_value(v);
}

void GxUiRadioMenu::on_changed(Glib::RefPtr<Gtk::RadioAction> act) {
    param.set(act->get_current_value());
}


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


/****************************************************************
 ** class PluginUI
 */

PluginUI::PluginUI(MainWindow& main_, const gx_engine::PluginList& pl, const char *name,
		   const Glib::ustring& fname_, const Glib::ustring& tooltip_)
    : GxUiItem(), merge_id(0), action(), plugin(pl.lookup_plugin(name)), fname(fname_),
      tooltip(tooltip_), shortname(), icon(), group(), toolitem(), main(main_), rackbox(),
      hidden(false), compressed(false) {
}

bool PluginUI::hasChanged() {
    if ((plugin->box_visible || plugin->on_off) != is_displayed()) {
	if (plugin->on_off) {
	    // when loading from old preset files make sure plugins
	    // are visible if they are switched on
	    plugin->box_visible = true;
	}
	return true;
    }
    if (!plugin->box_visible) {
	return false;
    }
    if (plugin->plug_visible != rackbox->get_plug_visible()) {
	return true;
    }
    if (main.is_loading()) {
	return false;
    }
    return rackbox->hasOrderDiff();
}

void PluginUI::reflectZone() {
    if (!hasChanged()) {
	return;
    }
    if (plugin->box_visible != is_displayed()) {
	action->set_active(plugin->box_visible);
	display(plugin->box_visible, false);
    }
    if (plugin->box_visible) {
	if (plugin->plug_visible != rackbox->get_plug_visible()) {
	    rackbox->swtch(plugin->plug_visible);
	}
	if (!main.is_loading() && rackbox->hasOrderDiff()) {
	    rackbox->get_parent()->check_order();
	}
    }
}

void PluginUI::set_action(Glib::RefPtr<Gtk::ToggleAction>& act)
{
    action = act;
    action->signal_toggled().connect(sigc::mem_fun(*this, &PluginUI::on_action_toggled));
}

void PluginUI::on_action_toggled() {
    if (plugin->box_visible != is_displayed()) {
	return; // call triggered by reflectZone
    }
    if (action->get_active()) {
	display_new();
    } else {
	display(false, true);
    }
}

void PluginUI::display(bool v, bool animate) {
    // this function hides the rackbox. It could also destroy it (or
    // some other function could do it, e.g. when unloading a module),
    // but currently there are too man memory leaks in the stackbased
    // builder.
    plugin->box_visible = v;
    if (v) {
	if (!rackbox) {
	    rackbox = main.add_rackbox(*this, false, -1, animate);
	} else {
	    rackbox->display(true, animate);
	}
	if (compressed) {
	    rackbox->swtch(true);
	}
	if (hidden) {
	    rackbox->hide();
	}
	main.hide_effect(get_id());
    } else {
	if (rackbox) {
	    rackbox->display(false, animate);
	    main.add_icon(get_id());
	}
    }
}

void PluginUI::display_new(bool unordered) {
    display(true, true);
    if (!unordered) {
	rackbox->get_parent()->reorder(get_id(), -1);
    }
    rackbox->swtch(false);
}

/****************************************************************
 ** class DragIcon
 */

inline guint8 convert_color_channel (guint8 src, guint8 alpha) {
    return alpha ? ((guint (src) << 8) - src) / alpha : 0;
}

void convert_bgra_to_rgba (guint8 const* src, guint8* dst, int width, int height) {
    guint8 const* src_pixel = src;
    guint8*       dst_pixel = dst;

    for (int i = 0; i < height*width; ++i) {
        dst_pixel[0] = convert_color_channel(src_pixel[2], src_pixel[3]);
        dst_pixel[1] = convert_color_channel(src_pixel[1], src_pixel[3]);
        dst_pixel[2] = convert_color_channel(src_pixel[0], src_pixel[3]);
        dst_pixel[3] = src_pixel[3];

        dst_pixel += 4;
        src_pixel += 4;
    }
}

DragIcon::DragIcon(const PluginUI& plugin, Glib::RefPtr<Gdk::DragContext> context, gx_system::CmdlineOptions& options, int xoff)
    : window(), drag_icon_pixbuf() {
    Glib::RefPtr<Gdk::Screen> screen = context->get_source_window()->get_screen();
    Glib::RefPtr<Gdk::Colormap> rgba = screen->get_rgba_colormap();
    if (screen->is_composited()) {
	window = new Gtk::Window(Gtk::WINDOW_POPUP);
	if (rgba) { // else will look ugly..
	    window->set_colormap(rgba);
	}
    }
    create_drag_icon_pixbuf(plugin, rgba, options);
    int w = drag_icon_pixbuf->get_width();
    int h = drag_icon_pixbuf->get_height();
    int h2 = (h/2)-2;
    int w2 = std::min(std::max(0, xoff), w-gradient_length/2) - 4;
    if (window) {
	window->set_size_request(w, h);
	window->signal_expose_event().connect(sigc::mem_fun(*this, &DragIcon::icon_expose_event));
	//context->set_icon_widget(window, w2, h2);
	gtk_drag_set_icon_widget(context->gobj(), GTK_WIDGET(window->gobj()), w2, h2);
    } else {
	context->set_icon(drag_icon_pixbuf, w2, h2);
    }
}

DragIcon::~DragIcon() {
    delete window;
}

bool DragIcon::icon_expose_event(GdkEventExpose *ev) {
    Cairo::RefPtr<Cairo::Context> cr = Glib::wrap(ev->window, true)->create_cairo_context();
    gdk_cairo_region(cr->cobj(), ev->region);
    cr->set_operator(Cairo::OPERATOR_SOURCE);
    cr->clip();
    Gdk::Cairo::set_source_pixbuf(cr, drag_icon_pixbuf, 0, 0);
    cr->paint();
    return true;
}

void DragIcon::create_drag_icon_pixbuf(const PluginUI& plugin, Glib::RefPtr<Gdk::Colormap> rgba, gx_system::CmdlineOptions& options) {
    Gtk::OffscreenWindow w;
    w.signal_expose_event().connect(sigc::bind(sigc::mem_fun(*this, &DragIcon::window_expose_event), sigc::ref(w)));
    if (rgba) {
	w.set_colormap(rgba);
    }
    Gtk::Widget *r = RackBox::create_drag_widget(plugin, options);
    w.add(*r);
    w.show_all();
    w.get_window()->process_updates(true);
}

static void destroy_data(const guint8 *data) {
    delete[] data;
}

bool DragIcon::window_expose_event(GdkEventExpose *event, Gtk::OffscreenWindow& widget) {
    Cairo::RefPtr<Cairo::Context> cr = widget.get_window()->create_cairo_context();
    cr->set_operator(Cairo::OPERATOR_SOURCE);
    cr->set_source_rgba(0,0,0,0);
    cr->paint();
    Gtk::Widget *child = widget.get_child();
    if (child) {
	widget.propagate_expose(*child, event);
    }
    Cairo::RefPtr<Cairo::Surface> x_surf = cr->get_target();
    int w = gdk_window_get_width(event->window);
    int h = gdk_window_get_height(event->window);
    Cairo::RefPtr<Cairo::LinearGradient> grad = Cairo::LinearGradient::create(w, 0, w-gradient_length, 0);
    grad->add_color_stop_rgba(0, 1, 1, 1, 1);
    grad->add_color_stop_rgba(1, 1, 1, 1, 0);
    cr->rectangle(w-gradient_length, 0, gradient_length, h);
    cr->mask(grad);
    Cairo::RefPtr<Cairo::ImageSurface> i_surf = Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32, w, h);
    Cairo::RefPtr<Cairo::Context> crt = Cairo::Context::create(i_surf);
    crt->set_operator(Cairo::OPERATOR_SOURCE);
    crt->set_source(x_surf, 0, 0);
    crt->paint();
    guint8 *data = new guint8[w*h*4];
    convert_bgra_to_rgba(i_surf->get_data(), data, w, h);
    drag_icon_pixbuf = Gdk::Pixbuf::create_from_data(data, Gdk::COLORSPACE_RGB, true, 8, w, h, i_surf->get_stride(), sigc::ptr_fun(destroy_data));
    return true;
}


/****************************************************************
 ** class MiniRackBox
 */

Glib::RefPtr<Gtk::SizeGroup> MiniRackBox::szg_label;

Gtk::Widget *MiniRackBox::make_delete_button(RackBox& rb) {
    Gtk::Widget *w;
    if (rb.has_delete()) {
	Gtk::Label *l = new Gtk::Label("\u2a2f");
	l->show();
	Gtk::Button *b = new Gtk::Button();
	b->set_focus_on_click(false);
	b->add(*manage(l));
	b->signal_clicked().connect(sigc::bind(sigc::mem_fun(rb.plugin, &PluginUI::display), false, true));
	w = b;
    } else {
	w = new Gtk::Alignment();
    }
    w->set_size_request(20, 15);
    return w;
}

MiniRackBox::MiniRackBox(RackBox& rb, gx_system::CmdlineOptions& options)
    : Gtk::HBox(),
      evbox(),
      mconbox(false, 4),
      mb_expand_button(),
      mb_delete_button(),
      preset_button(),
      on_off_switch("minitoggle"),
      toggle_on_off(rb.main.get_ui(), &on_off_switch, &rb.plugin.plugin->on_off) {
    if (strcmp(rb.plugin.get_id(), "ampstack") != 0) { // FIXME
	gx_gui::connect_midi_controller(GTK_WIDGET(on_off_switch.gobj()), &rb.plugin.plugin->on_off);
    }
    if (!szg_label) {
	szg_label = Gtk::SizeGroup::create(Gtk::SIZE_GROUP_HORIZONTAL);
    }
    evbox.set_visible_window(false);
    add(evbox);
    Gtk::HBox *box = new Gtk::HBox();
    evbox.add(*manage(box));
    Gtk::Alignment *al = new Gtk::Alignment(0.5, 0.5, 0.0, 0.0);
    al->add(on_off_switch);
#ifdef USE_SZG
    RackBox::szg->add_widget(*al);
#else
    al->set_size_request(35, -1);
#endif
    box->pack_start(*manage(al), Gtk::PACK_SHRINK);
    Gtk::Widget *effect_label = RackBox::make_label(rb.plugin, options);
    szg_label->add_widget(*manage(effect_label));
    al = new Gtk::Alignment(0.0, 0.0, 0.0, 0.0);
    al->add(*manage(rb.wrap_bar()));
    box->pack_start(*manage(al), Gtk::PACK_SHRINK);
    box->pack_start(*manage(effect_label), Gtk::PACK_SHRINK);
    box->pack_start(mconbox, Gtk::PACK_EXPAND_WIDGET, 15);
    al = new Gtk::Alignment(0.0, 0.0, 0.0, 0.0);
    Gtk::HBox *hb = new Gtk::HBox();
    al->add(*manage(hb));
    mb_expand_button = rb.make_expand_button(true);
    hb->pack_start(*manage(mb_expand_button), Gtk::PACK_SHRINK);
    mb_delete_button = make_delete_button(rb);
    mb_delete_button->set_no_show_all(true);
    hb->pack_start(*manage(mb_delete_button), Gtk::PACK_SHRINK);
    al->set_padding(1, 0, 4, 4);
    pack_end(*manage(al), Gtk::PACK_SHRINK);
    box->pack_end(*manage(rb.wrap_bar(8)), Gtk::PACK_SHRINK);
    preset_button = rb.make_preset_button();
    box->pack_end(*manage(preset_button), Gtk::PACK_SHRINK);
    show_all();
}

void MiniRackBox::pack(Gtk::Widget *w) {
    if (w) {
	mconbox.pack_start(*manage(w), Gtk::PACK_SHRINK, 4);
    }
}

void MiniRackBox::set_config_mode(bool mode) {
    evbox.set_above_child(mode);
    if (mode) {
	mconbox.hide();
	preset_button->hide();
	mb_expand_button->hide();
	if (mb_delete_button) {
	    mb_delete_button->show();
	}
    } else {
	mconbox.show();
	preset_button->show();
	mb_expand_button->show();
	if (mb_delete_button) {
	    mb_delete_button->hide();
	}
    }
}

/****************************************************************
 ** class RackBox
 */

/*
** InputWindow
*/

class InputWindow: public Gtk::Window {
private:
    Glib::ustring name;
    void on_cancel();
    void on_ok(Gtk::Entry *e);
    static InputWindow* create_from_builder(BaseObjectType* cobject, Glib::RefPtr<gx_gui::GxBuilder> bld);
    InputWindow(BaseObjectType* cobject, Glib::RefPtr<gx_gui::GxBuilder> bld);
public:
    ~InputWindow();
    static InputWindow *create(const gx_system::CmdlineOptions& options);
    void run();
    Glib::ustring& get_name() { return name; }
};

InputWindow *InputWindow::create_from_builder(BaseObjectType* cobject, Glib::RefPtr<gx_gui::GxBuilder> bld) {
    return new InputWindow(cobject, bld);
}

InputWindow::~InputWindow() {
}

InputWindow *InputWindow::create(const gx_system::CmdlineOptions& options) {
    Glib::RefPtr<gx_gui::GxBuilder> bld = gx_gui::GxBuilder::create_from_file(options.get_builder_filepath("pluginpreset_inputwindow.glade"));
    InputWindow *w;
    bld->get_toplevel_derived(
	"PluginPresetInputWindow", w,
	sigc::bind(sigc::ptr_fun(InputWindow::create_from_builder),bld));
    return w;
}

void InputWindow::on_ok(Gtk::Entry *e) {
    name = e->get_text();
    hide();
}

InputWindow::InputWindow(BaseObjectType* cobject, Glib::RefPtr<gx_gui::GxBuilder> bld)
    : Gtk::Window(cobject), name() {
    Gtk::Button *b;
    bld->find_widget("cancelbutton", b);
    b->signal_clicked().connect(
	sigc::mem_fun(*this, &InputWindow::hide));
    bld->find_widget("okbutton", b);
    Gtk::Entry *e;
    bld->find_widget("entry", e);
    b->signal_clicked().connect(
	sigc::bind(sigc::mem_fun(*this, &InputWindow::on_ok), e));
}

void InputWindow::run() {
    Gtk::Main::run(*this);
}

/*
** PluginPresetListWindow
*/

class TextListStore: public Gtk::ListStore {
public:
    class TextListColumns : public Gtk::TreeModel::ColumnRecord {
    public:
	Gtk::TreeModelColumn<Glib::ustring> name;
	TextListColumns() { add(name); }
    } col;
private:
    TextListStore(): Gtk::ListStore(TextListColumns()) {}
public:
    static Glib::RefPtr<TextListStore> create() { return Glib::RefPtr<TextListStore>(new TextListStore); }
};

class PluginPresetListWindow: public Gtk::Window {
private:
    Glib::RefPtr<TextListStore> textliststore;
    Glib::RefPtr<gx_preset::PluginPresetList> presetlist;
    //
    Gtk::TreeView *treeview;
    Gtk::Button *removebutton;
    void on_remove();
    void on_selection_changed();
    static PluginPresetListWindow* create_from_builder(BaseObjectType* cobject, Glib::RefPtr<gx_gui::GxBuilder> bld, Glib::RefPtr<gx_preset::PluginPresetList> l);
    PluginPresetListWindow(BaseObjectType* cobject, Glib::RefPtr<gx_gui::GxBuilder> bld, Glib::RefPtr<gx_preset::PluginPresetList> l);
public:
    ~PluginPresetListWindow();
    static PluginPresetListWindow *create(const gx_system::CmdlineOptions& options, Glib::RefPtr<gx_preset::PluginPresetList> l);
    void run();
};

PluginPresetListWindow *PluginPresetListWindow::create_from_builder(BaseObjectType* cobject, Glib::RefPtr<gx_gui::GxBuilder> bld, Glib::RefPtr<gx_preset::PluginPresetList> l) {
    return new PluginPresetListWindow(cobject, bld, l);
}

PluginPresetListWindow::~PluginPresetListWindow() {
}

PluginPresetListWindow *PluginPresetListWindow::create(const gx_system::CmdlineOptions& options, Glib::RefPtr<gx_preset::PluginPresetList> l) {
    Glib::RefPtr<gx_gui::GxBuilder> bld = gx_gui::GxBuilder::create_from_file(options.get_builder_filepath("pluginpreset_listwindow.glade"));
    PluginPresetListWindow *w;
    bld->get_toplevel_derived(
	"PluginPresetListWindow", w,
	sigc::bind(sigc::ptr_fun(PluginPresetListWindow::create_from_builder), bld, l));
    return w;
}

void PluginPresetListWindow::on_remove() {
    Gtk::TreeIter it = treeview->get_selection()->get_selected();
    if (it) {
	presetlist->remove(it->get_value(textliststore->col.name));
	textliststore->erase(it);
    }
}

PluginPresetListWindow::PluginPresetListWindow(BaseObjectType* cobject, Glib::RefPtr<gx_gui::GxBuilder> bld, Glib::RefPtr<gx_preset::PluginPresetList> l)
    : Gtk::Window(cobject), textliststore(TextListStore::create()), presetlist(l) {
    Gtk::Button *b;
    bld->find_widget("closebutton", b);
    b->signal_clicked().connect(
	sigc::mem_fun(*this, &PluginPresetListWindow::hide));
    bld->find_widget("removebutton", removebutton);
    removebutton->signal_clicked().connect(
	sigc::mem_fun(*this, &PluginPresetListWindow::on_remove));
    bld->find_widget("treeview", treeview);
    if (l->start()) {
	Glib::ustring name;
	while (l->next(name)) {
	    textliststore->append()->set_value(textliststore->col.name, name);
	}
    }
    treeview->set_model(textliststore);
    Glib::RefPtr<Gtk::TreeSelection> sel = treeview->get_selection();
    sel->select(textliststore->children().begin());
    sel->signal_changed().connect(
	sigc::mem_fun(*this, &PluginPresetListWindow::on_selection_changed));
}

void PluginPresetListWindow::on_selection_changed() {
    removebutton->set_sensitive(treeview->get_selection()->get_selected());
}

void PluginPresetListWindow::run() {
    Gtk::Main::run(*this);
}


/*
** RackBox
*/

#ifdef USE_SZG
Glib::RefPtr<Gtk::SizeGroup> RackBox::szg;
#endif

void RackBox::set_paintbox(Gxw::PaintBox& pb, PluginType tp) {
    pb.set_name("rackbox");
    pb.property_paint_func().set_value("rectangle_skin_color_expose");
    pb.set_border_width(4);
}

Gtk::Widget *RackBox::make_label(const PluginUI& plugin, gx_system::CmdlineOptions& options, bool useshort) {
    const char *effect_name;
    if (useshort) {
	effect_name = plugin.shortname;
	if (!effect_name) {
	    effect_name = plugin.get_name();
	}
    } else {
	effect_name = plugin.get_name();
    }
    Gtk::Label *effect_label = new Gtk::Label(effect_name);
    effect_label->set_alignment(0, 0.5);
    effect_label->set_name("rack_effect_label");
    Pango::FontDescription font_desc = effect_label->get_style()->get_font();
    font_desc.set_size(int(7.5*Pango::SCALE));
    font_desc.set_weight(Pango::WEIGHT_BOLD);
    effect_label->modify_font(font_desc);
    if (plugin.get_type() == PLUGIN_TYPE_STEREO) {
	Gtk::HBox *hbox = new Gtk::HBox(false, 4);
	Gtk::Image *e = new Gtk::Image(options.get_style_filepath("stereo.png"));
	hbox->pack_start(*manage(e), Gtk::PACK_SHRINK);
	hbox->pack_start(*manage(effect_label));
	hbox->show_all();
	return hbox;
    } else {
	return effect_label;
    }
}

Gtk::Widget *RackBox::make_bar(int left, int right, bool sens) {
    Gtk::Alignment *al = new Gtk::Alignment(0, 0, 1.0, 1.0);
    al->set_padding(4, 4, left, right);
    Gtk::Button *button = new Gtk::Button();
    button->set_size_request(6,-1);
    button->set_name("effect_reset");
    button->set_sensitive(sens);
    al->add(*manage(button));
    return al;
}

Gtk::Widget *RackBox::wrap_bar(int left, int right, bool sens) {
    Gtk::EventBox *ev = new Gtk::EventBox;
    ev->set_visible_window(false);
    ev->set_above_child(true);
    ev->add(*manage(make_bar(left, right, sens)));
    ev->signal_drag_begin().connect(sigc::mem_fun(*this, &RackBox::on_my_drag_begin));
    ev->signal_drag_end().connect(sigc::mem_fun(*this, &RackBox::on_my_drag_end));
    ev->signal_drag_data_get().connect(sigc::mem_fun(*this, &RackBox::on_my_drag_data_get));
    std::vector<Gtk::TargetEntry> listTargets;
    listTargets.push_back(Gtk::TargetEntry(target, Gtk::TARGET_SAME_APP, 0));
    ev->drag_source_set(listTargets, Gdk::BUTTON1_MASK, Gdk::ACTION_MOVE);
    return ev;
}

Gtk::Widget *RackBox::create_icon_widget(const PluginUI& plugin, gx_system::CmdlineOptions& options) {
    Gxw::PaintBox *pb = new Gxw::PaintBox(Gtk::ORIENTATION_HORIZONTAL);
    RackBox::set_paintbox(*pb, plugin.get_type());
    Gtk::Widget *effect_label = RackBox::make_label(plugin, options);
    Gtk::Alignment *al = new Gtk::Alignment(0.0, 0.0, 1.0, 1.0);
    al->set_padding(0,2,2,0);
    al->add(*manage(effect_label));
    pb->pack_start(*manage(al), Gtk::PACK_SHRINK);
    pb->show_all();
    return pb;
}

Gtk::Widget *RackBox::create_drag_widget(const PluginUI& plugin, gx_system::CmdlineOptions& options) {
    Gxw::PaintBox *pb = new Gxw::PaintBox(Gtk::ORIENTATION_HORIZONTAL);
    RackBox::set_paintbox(*pb, plugin.get_type());
    if (strcmp(plugin.get_id(), "ampstack") == 0) { // FIXME
	pb->property_paint_func().set_value("zac_expose");
    }
    Gxw::Switch *swtch = new Gxw::Switch("minitoggle");
    swtch->set_active(plugin.plugin->on_off);
#ifdef USE_SZG
    RackBox::szg->add_widget(*swtch);
#else
    swtch->set_size_request(35, -1);
#endif
    pb->pack_start(*manage(swtch), Gtk::PACK_SHRINK);
    Gtk::Widget *effect_label = RackBox::make_label(plugin, options);
    Gtk::Alignment *al = new Gtk::Alignment(0.0, 0.0, 0.0, 0.0);
    al->set_padding(0,0,4,20);
    al->add(*manage(RackBox::make_bar(4, 4, true))); // FIXME: fix style and remove sens parameter
    pb->pack_start(*manage(al), Gtk::PACK_SHRINK);
    pb->pack_start(*manage(effect_label), Gtk::PACK_SHRINK);
    al = new Gtk::Alignment(0.0, 0.0, 0.0, 0.0);
    al->set_size_request(50,-1);
    pb->pack_start(*manage(al), Gtk::PACK_SHRINK);
    pb->show_all();
    return pb;
}

void RackBox::display(bool v, bool animate) {
    box_visible = v;
    if (v) {
	if (animate) {
	    animate_insert();
	} else {
	    show();
	}
	get_parent()->increment();
    } else {
	plugin.plugin->on_off = false;
	if (animate) {
	    animate_remove();
	} else {
	    hide();
	}
	get_parent()->decrement();
    }
}

RackBox::RackBox(PluginUI& plugin_, MainWindow& tl, Gtk::Widget* bare)
    : Gtk::VBox(), plugin(plugin_), main(tl), vis(true), config_mode(false), anim_tag(),
      compress(true), delete_button(true), mbox(Gtk::ORIENTATION_HORIZONTAL), minibox(0),
      fbox(0), target(), anim_height(0), anim_step(), drag_icon(), target_height(0),
      box(Gtk::ORIENTATION_HORIZONTAL, 2), box_visible(true), position(), effect_post_pre(), on_off_switch("switchit"),
      toggle_on_off(tl.get_ui(), &on_off_switch, &plugin.plugin->on_off) {
    if (strcmp(plugin.get_id(), "ampstack") != 0) { // FIXME
	gx_gui::connect_midi_controller(GTK_WIDGET(on_off_switch.gobj()), &plugin.plugin->on_off);
    }
#ifdef USE_SZG
    if (!szg) {
	szg = Gtk::SizeGroup::create(Gtk::SIZE_GROUP_HORIZONTAL);
    }
#endif
    if (bare) {
	compress = false;
	delete_button = false;
    }
    set_paintbox(mbox, plugin.get_type());
    init_dnd();
    minibox = new MiniRackBox(*this, tl.get_options());
    mbox.pack_start(*manage(minibox));
    pack_start(mbox, Gtk::PACK_SHRINK);
    if (bare) {
	add(*manage(bare));
	fbox = bare;
	mbox.property_paint_func().set_value("zac_expose");
    } else {
	Gxw::PaintBox *pb = new Gxw::PaintBox(Gtk::ORIENTATION_HORIZONTAL);
	pb->show();
	set_paintbox(*pb, plugin.get_type());
	pb->pack_start(*manage(make_full_box(tl.get_options())));
	pack_start(*manage(pb), Gtk::PACK_SHRINK);
	fbox = pb;
    }
    show();
}

void RackBox::init_dnd() {
    target = "application/x-guitarix-";
    if (plugin.get_type() == PLUGIN_TYPE_MONO) {
	target += "mono";
    } else {
	target += "stereo";
    }
    if (!delete_button) {
	target += "-s";
    }
    mbox.signal_drag_begin().connect(sigc::mem_fun(*this, &RackBox::on_my_drag_begin));
    mbox.signal_drag_end().connect(sigc::mem_fun(*this, &RackBox::on_my_drag_end));
    mbox.signal_drag_data_get().connect(sigc::mem_fun(*this, &RackBox::on_my_drag_data_get));
}

void RackBox::enable_drag(bool v) {
    if (v) {
	std::vector<Gtk::TargetEntry> listTargets;
	listTargets.push_back(Gtk::TargetEntry(target, Gtk::TARGET_SAME_APP, 0));
	mbox.drag_source_set(listTargets, Gdk::BUTTON1_MASK, Gdk::ACTION_MOVE);
    } else {
	mbox.drag_source_unset();
    }
}

bool RackBox::animate_vanish() {
    anim_height -= anim_step;
    if (anim_height <= 0) {
	hide();
	set_size_request(-1,-1);
	//anim_tag.disconnect(); //FIXME
	return false;
    } else {
	set_size_request(-1, anim_height);
	return true;
    }
}

void RackBox::animate_remove() {
    if (!get_parent()->check_if_animate(*this)) {
	hide();
    } else {
	if (anim_tag.connected()) {
	    //Glib::source_remove(anim_tag);
	    anim_tag.disconnect();
	    set_size_request(-1,-1);
	    show();
	}
	anim_height = size_request().height;
	anim_step = anim_height / 5;
	anim_tag = Glib::signal_timeout().connect(sigc::mem_fun(*this, &RackBox::animate_vanish), 20);
    }
}

RackContainer *RackBox::get_parent() {
    return dynamic_cast<RackContainer*>(Gtk::VBox::get_parent());
}

void RackBox::on_my_drag_begin(const Glib::RefPtr<Gdk::DragContext>& context) {
    int x, y;
    get_pointer(x, y);
    drag_icon = new DragIcon(plugin, context, main.get_options(), x);
    animate_remove();
}

bool RackBox::animate_create() {
    bool ret = true;
    anim_height += anim_step;
    if (anim_height >= target_height) {
	set_size_request(-1,-1);
	//anim_tag.disconnect(); //FIXME
	ret = false;
    } else {
	set_size_request(-1, anim_height);
    }
    get_parent()->ensure_visible(*this);
    return ret;
}

void RackBox::animate_insert() {
    if (!get_parent()->check_if_animate(*this)) {
	show();
	get_parent()->ensure_visible(*this);
    } else {
	if (anim_tag.connected()) {
	    hide();
	    anim_tag.disconnect();
	    set_size_request(-1,-1);
	}
	target_height = size_request().height;
	set_size_request(-1,0);
	show();
	anim_height = 0;
	anim_step = target_height / 5;
	anim_tag = Glib::signal_timeout().connect(mem_fun(*this, &RackBox::animate_create), 20);
    }
}

void RackBox::on_my_drag_end(const Glib::RefPtr<Gdk::DragContext>& context) {
    if (drag_icon) {
	delete drag_icon;
	drag_icon = 0;
    }
    if (box_visible) {
	animate_insert();
    }
}

void RackBox::on_my_drag_data_get(const Glib::RefPtr<Gdk::DragContext>& context, Gtk::SelectionData& selection, int info, int timestamp) {
    selection.set(target, plugin.get_id());
}

void RackBox::vis_switch(Gtk::Widget& a, Gtk::Widget& b) {
    a.hide();
    b.show();
}

void RackBox::swtch(bool mini) {
    plugin.plugin->plug_visible = mini;
    if (config_mode) {
	vis = !mini;
    } else {
	if (mini) {
	    vis_switch(*fbox, mbox);
	} else {
	    vis_switch(mbox, *fbox);
	}
    }
}

void RackBox::set_config_mode(bool mode) {
    minibox->set_config_mode(mode);
    if (mode) {
	vis = fbox->get_visible();
	if (vis) {
	    swtch(true);
	}
	config_mode = true;
    } else {
	config_mode = false;
	if (vis) {
	    swtch(false);
	}
    }
    enable_drag(mode);
}

Gtk::Button *RackBox::make_expand_button(bool expand) {
    Glib::ustring t;
    if (expand) {
	t = "▶";
    } else {
	t = "▼"; // ▲
    }
    Gtk::Label *l = new Gtk::Label(t);
    l->set_name("rack_slider");
    Gtk::Button *b = new Gtk::Button();
    b->set_focus_on_click(false);
    b->add(*manage(l));
    b->set_size_request(20, 15);
    b->set_name("effect_reset");
    b->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &RackBox::swtch), !expand));
    return b;
}

void RackBox::on_preset_popup_destroy(Gtk::Menu *w) {
    delete w;
}

void RackBox::set_plugin_preset(Glib::RefPtr<gx_preset::PluginPresetList> l, Glib::ustring name) {
    l->set(name);
}

void RackBox::set_plugin_std_preset() {
    gx_gui::gx_reset_units(main.get_parametermap(), plugin.get_id());
}

void RackBox::save_plugin_preset(Glib::RefPtr<gx_preset::PluginPresetList> l) {
    InputWindow *w = InputWindow::create(main.get_options());
    w->run();
    if (!w->get_name().empty()) {
	l->save(w->get_name(), plugin.get_id());
    }
    delete w;
}

void RackBox::remove_plugin_preset(Glib::RefPtr<gx_preset::PluginPresetList> l) {
    PluginPresetListWindow *w = PluginPresetListWindow::create(main.get_options(), l);
    w->run();
    delete w;
}

void RackBox::preset_popup() {
    Gtk::Menu *m = new Gtk::Menu();
    Glib::RefPtr<gx_preset::PluginPresetList> l = main.load_plugin_preset_list(plugin.get_id());
    bool found_presets = false;
    if (l->start()) {
	Glib::ustring name;
	bool is_set;
	while (l->next(name, &is_set)) {
	    found_presets = true;
	    Gtk::CheckMenuItem *c = new Gtk::CheckMenuItem(name);
	    if (is_set) {
		c->set_active(true);
	    }
	    c->signal_activate().connect(
		sigc::bind(sigc::mem_fun(*this, &RackBox::set_plugin_preset), l, name));
	    m->append(*manage(c));
	}
    }
    Gtk::CheckMenuItem *c = new Gtk::CheckMenuItem(_("standard"));
    std::string s = std::string(plugin.get_id()) + ".";
    string on_off = s + "on_off";
    string pp = s + "pp";
    bool is_std = true;
    gx_engine::ParamMap& pmap = main.get_parametermap();
    for (gx_engine::ParamMap::iterator i = pmap.begin(); i != pmap.end(); ++i) {
	if (i->first.compare(0, s.size(), s) == 0) {
	    if (i->second->isControllable()) {
		if (i->first != on_off && i->first != pp) {
		    i->second->stdJSON_value();
		    if (!i->second->compareJSON_value()) {
			is_std = false;
			break;
		    }
		}
	    }
	}
    }
    if (is_std) {
	c->set_active(true);
    }
    c->signal_activate().connect(
	sigc::mem_fun(*this, &RackBox::set_plugin_std_preset));
    m->append(*manage(c));
    m->append(*manage(new Gtk::SeparatorMenuItem()));
    Gtk::MenuItem *mi = new Gtk::MenuItem(_("save..."));
    m->append(*manage(mi));
    mi->signal_activate().connect(
	sigc::bind(sigc::mem_fun(*this, &RackBox::save_plugin_preset),l));
    if (found_presets) {
	mi = new Gtk::MenuItem(_("remove..."));
	m->append(*manage(mi));
	mi->signal_activate().connect(
	    sigc::bind(sigc::mem_fun(*this, &RackBox::remove_plugin_preset),l));
    }
    m->signal_selection_done().connect(sigc::bind(sigc::mem_fun(*this, &RackBox::on_preset_popup_destroy), m));
    m->show_all();
    m->popup(1, gtk_get_current_event_time());
}

Gtk::Button *RackBox::make_preset_button() {
    Gtk::Button *p = new Gtk::Button("p");
    p->set_can_default(false);
    p->set_can_focus(false);
    p->set_size_request(18,18);
    p->signal_clicked().connect(mem_fun(*this, &RackBox::preset_popup));
    return p;
}

void RackBox::pack(Gtk::Widget *main, Gtk::Widget *mini) {
    if (!main) {
	return;
    }
    box.pack_start(*manage(main));
    minibox->pack(mini);
}

Gtk::HBox *RackBox::make_full_box(gx_system::CmdlineOptions& options) {
    Gtk::HBox *bx = new Gtk::HBox();
    bx->pack_start(*manage(switcher_vbox(options)), Gtk::PACK_SHRINK);
    box.set_name(plugin.get_id());
    box.set_border_width(4);
    box.property_paint_func().set_value("RackBox_expose");
    bx->pack_start(box);
    Gtk::VBox *vbox = new Gtk::VBox();
    vbox->pack_start(*manage(make_expand_button(false)), Gtk::PACK_SHRINK);
    vbox->pack_start(*manage(make_preset_button()), Gtk::PACK_EXPAND_PADDING);
    Gtk::Alignment *al = new Gtk::Alignment(0.0, 0.0, 0.0, 0.7);
    al->add(*manage(vbox));
    al->set_padding(1, 0, 0, 4);
    bx->pack_end(*manage(al), Gtk::PACK_SHRINK);
    bx->pack_end(*manage(wrap_bar(4, 8)), Gtk::PACK_SHRINK);
    bx->show_all();
    return bx;
}

Gtk::VBox *RackBox::switcher_vbox(gx_system::CmdlineOptions& options) {
    Gtk::VBox *vbox = new Gtk::VBox();
    Gtk::Widget *effect_label = make_label(plugin, options, true);
    vbox->pack_start(*manage(effect_label), Gtk::PACK_SHRINK);
    Gtk::HBox *hbox = new Gtk::HBox();
    vbox->pack_start(*manage(hbox));
    Gtk::HBox *hbox2 = new Gtk::HBox();
    hbox->pack_start(*manage(hbox2), Gtk::PACK_SHRINK);
    Gtk::VBox *vbox2 = new Gtk::VBox();
    hbox2->pack_start(*manage(vbox2));
    hbox2->pack_start(*manage(wrap_bar()), Gtk::PACK_SHRINK);
#ifdef USE_SZG
    szg->add_widget(&on_off_switch);
#endif
    Gtk::Alignment *al = new Gtk::Alignment(0.5, 0.5, 0.0, 0.0);
    al->add(on_off_switch);
    vbox2->pack_start(*manage(al));
    return vbox;
}


/****************************************************************
 ** class RackContainer
 */

static const int min_containersize = 40;

RackContainer::RackContainer(PluginType tp_, MainWindow& main_)
    : Gtk::VBox(),
      tp(tp_),
      main(main_),
      config_mode(false),
      in_drag(-2),
      child_count(0),
      switch_level(1),
      targets(),
      othertargets(),
      highlight_connection(),
      autoscroll_connection() {
    std::vector<std::string> *pm, *ps;
    if (tp == PLUGIN_TYPE_MONO) {
	pm = &targets;
	ps = &othertargets;
    } else {
	ps = &targets;
	pm = &othertargets;
    }
    pm->push_back("application/x-guitarix-mono");
    pm->push_back("application/x-guitarix-mono-s");
    pm->push_back("application/x-gtk-tool-palette-item-mono");
    ps->push_back("application/x-guitarix-stereo");
    ps->push_back("application/x-guitarix-stereo-s");
    ps->push_back("application/x-gtk-tool-palette-item-stereo");
    std::vector<Gtk::TargetEntry> listTargets;
    listTargets.push_back(Gtk::TargetEntry("application/x-guitarix-mono", Gtk::TARGET_SAME_APP, 0));
    listTargets.push_back(Gtk::TargetEntry("application/x-guitarix-mono-s", Gtk::TARGET_SAME_APP, 1));
    listTargets.push_back(Gtk::TargetEntry("application/x-gtk-tool-palette-item-mono", Gtk::TARGET_SAME_APP, 2));
    listTargets.push_back(Gtk::TargetEntry("application/x-guitarix-stereo", Gtk::TARGET_SAME_APP, 3));
    listTargets.push_back(Gtk::TargetEntry("application/x-guitarix-stereo-s", Gtk::TARGET_SAME_APP, 4));
    listTargets.push_back(Gtk::TargetEntry("application/x-gtk-tool-palette-item-stereo", Gtk::TARGET_SAME_APP, 5));
    drag_dest_set(listTargets, Gtk::DEST_DEFAULT_DROP, Gdk::ACTION_MOVE);
    signal_remove().connect(sigc::mem_fun(*this, &RackContainer::on_my_remove));
    set_size_request(-1, min_containersize);
    show_all();
}

bool RackContainer::drag_highlight_expose(GdkEventExpose *event, int y0) {
    if (!is_drawable()) {
	return false;
    }
    Cairo::RefPtr<Cairo::Context> cr = Glib::wrap(event->window, true)->create_cairo_context();
    cr->set_source_rgb(1.0, 1.0, 1.0);
    int x, y, width, height;
    if (!get_has_window()) {
	Gtk::Allocation a = get_allocation();
	x = a.get_x();
	y = a.get_y();
	width = a.get_width();
	height = a.get_height();
    } else {
        int depth;
        get_window()->get_geometry(x, y, width, height, depth);
	x = 0;
	y = 0;
    }
    if (y0 < 0) {
	get_style()->paint_shadow(
	    get_window(), Gtk::STATE_NORMAL, Gtk::SHADOW_OUT,
	    Glib::wrap(&event->area), *this, "dnd", x, y, width, height);
	cr->set_line_width(1.0);
	cr->rectangle(x + 0.5, y + 0.5, width - 1, height - 1);
    } else {
	y0 -= 1;
	y0 = std::max(y0, y);
	cr->set_line_width(1.0);
	cr->move_to(x+0.5, y0+0.5);
	cr->rel_line_to(width - 1, 0);
    }
    cr->stroke();
    return false;
}

struct childpos {
    int y0, y1, pos;
    childpos(int y0_, int y1_, int pos_): y0(y0_), y1(y1_), pos(pos_) {}
    bool operator<(const childpos& p) { return y0 < p.y0; }
};

void RackContainer::find_index(int x, int y, int* len, int *ypos) {
    std::list<childpos> l;
    std::vector<RackBox*> children = get_children();
    int mpos = -1;
    for (std::vector<RackBox*>::iterator ch = children.begin(); ch != children.end(); ++ch) {
	++mpos;
	if (!(*ch)->get_visible()) {
	    continue;
	}
	Gtk::Allocation a = (*ch)->get_allocation();
	l.push_back(childpos(a.get_y(), a.get_y()+a.get_height(), mpos));
    }
    if (l.empty()) {
	*len = -1;
	*ypos = -1;
	return;
    }
    Gtk::Allocation a0 = get_allocation();
    y += a0.get_y();
    int sy = l.begin()->y0;
    for (std::list<childpos>::iterator cp = l.begin(); cp != l.end(); ++cp) {
	if (y < (cp->y0 + cp->y1) / 2) {
	    *len = cp->pos;
	    *ypos = (cp->y0+sy)/2;
	    return;
	}
	sy = cp->y1;
    }
    *len = mpos+1;
    *ypos = sy;
}

void RackContainer::on_my_remove(Gtk::Widget *ch) {
    decrement();
    if (!main.is_loading()) {
	renumber();
    }
}

bool RackContainer::check_targets(const std::vector<std::string>& tgts1, const std::vector<std::string>& tgts2) {
    for (std::vector<std::string>::const_iterator t1 = tgts1.begin(); t1 != tgts1.end(); ++t1) {
	for (std::vector<std::string>::const_iterator t2 = tgts2.begin(); t2 != tgts2.end(); ++t2) {
	    if (*t1 == *t2) {
		return true;
	    }
	}
    }
    return false;
}

bool RackContainer::on_drag_motion(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, guint timestamp) {
    const std::vector<std::string>& tg = context->get_targets();
    if (!check_targets(tg, targets)) {
	if (check_targets(tg, othertargets)) {
	    if (!autoscroll_connection.connected()) {
		autoscroll_connection = Glib::signal_timeout().connect(
		    sigc::mem_fun(*this, &RackContainer::scrollother_timeout), 50);
	    }
	    context->drag_status(Gdk::DragAction(0), timestamp);
	    return true;
	}
	return false;
    }
    context->drag_status(Gdk::ACTION_MOVE, timestamp);
    int i, ind;
    find_index(x, y, &i, &ind);
    if (in_drag == ind) {
	return true;
    }
    if (in_drag > -2) {
	highlight_connection.disconnect();
    }
    highlight_connection = signal_expose_event().connect(sigc::bind(sigc::mem_fun(*this, &RackContainer::drag_highlight_expose), ind), true);
    queue_draw();
    in_drag = ind;
    if (!autoscroll_connection.connected()) {
	autoscroll_connection = Glib::signal_timeout().connect(sigc::mem_fun(*this, &RackContainer::scroll_timeout), 50);
    }
    return true;
}

void RackContainer::ensure_visible(RackBox& child) {
    Gtk::Allocation alloc = child.get_allocation();
    Gtk::Viewport *p = dynamic_cast<Gtk::Viewport*>(get_ancestor(GTK_TYPE_VIEWPORT));
    p->get_vadjustment()->clamp_page(alloc.get_y(), alloc.get_y()+alloc.get_height());
}

static const double scroll_edge_size = 60.0;
static const int step_size = 20;

bool RackContainer::scrollother_timeout() {
    Gtk::Viewport *p = dynamic_cast<Gtk::Viewport*>(get_ancestor(GTK_TYPE_VIEWPORT));
    Gtk::Adjustment *a = p->get_vadjustment();
    double off = a->get_value();
    Gtk::Allocation alloc = get_allocation();
    int x, y;
    get_pointer(x, y);
    y -= alloc.get_height();
    double step;
    if (y < -scroll_edge_size) {
	step = step_size;
    } else {
	step = step_size * exp(-(y+scroll_edge_size)/(1.0*scroll_edge_size));
	if (step < 1.5) {
	    return false;
	}
    }
    if (tp == PLUGIN_TYPE_MONO) {
	off = main.stop_at_stereo_bottom(off, step_size, a->get_page_size());
    } else {
	printf("%g ", off);
	off = main.stop_at_mono_top(off, step_size);
	printf("%g\n", off);
    }
    if (off < a->get_lower()) {
	off = a->get_lower();
    }
    if (off > a->get_upper() - a->get_page_size()) {
	off = a->get_upper() - a->get_page_size();
    }
    a->set_value(off);
    return true;
}

bool RackContainer::scroll_timeout() {
    Gtk::Viewport *p = dynamic_cast<Gtk::Viewport*>(get_ancestor(GTK_TYPE_VIEWPORT));
    Gtk::Adjustment *a = p->get_vadjustment();
    double off = a->get_value();
    Gtk::Allocation alloc = get_allocation();
    int x, y;
    get_pointer(x, y);
    double sez = scroll_edge_size;
    if (sez > a->get_page_size() / 3) {
	sez = a->get_page_size() / 3;
    }
    double yw = y + alloc.get_y() - off;
    double step;
    if (yw <= sez) {
	step = step_size * (sez-yw) / sez;
	off = max(double(alloc.get_y()), off-step);
    } else {
	yw = a->get_page_size() - yw;
	if (yw <= sez) {
	    step = step_size * (sez-yw) / sez;
	    off = min(alloc.get_y()+alloc.get_height()-a->get_page_size(), off+step);
	} else {
	    return true;
	}
    }
    if (off < a->get_lower()) {
	off = a->get_lower();
    }
    if (off > a->get_upper() - a->get_page_size()) {
	off = a->get_upper() - a->get_page_size();
    }
    a->set_value(off);
    return true;
}

void RackContainer::on_drag_leave(const Glib::RefPtr<Gdk::DragContext>& context, guint timestamp) {
    if (in_drag > -2) {
	highlight_connection.disconnect();
	queue_draw();
	in_drag = -2;
    }
    autoscroll_connection.disconnect();
}

void RackContainer::on_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, const Gtk::SelectionData& data, guint info, guint timestamp) {
    int i, ind;
    find_index(x, y, &i, &ind);
    std::string dtype = data.get_data_type();
    if (dtype == "application/x-gtk-tool-palette-item-mono" || dtype == "application/x-gtk-tool-palette-item-stereo") {
	main.get_plugin(data.get_data_as_string())->display_new(true);
    }
    reorder(data.get_data_as_string(), i);
}

void RackContainer::show_entries() {
    for (PluginDict::iterator i = main.plugins_begin(); i != main.plugins_end(); ++i) {
	i->second->hidden = false;
	RackBox *r = i->second->rackbox;
	if (r) {
	    r->show();
	}
    }
}

void RackContainer::hide_entries() {
    for (PluginDict::iterator i = main.plugins_begin(); i != main.plugins_end(); ++i) {
	i->second->hidden = true;
	RackBox *r = i->second->rackbox;
	if (r) {
	    if (r->can_compress()) {
		r->hide();
	    }
	}
    }
}

void RackContainer::reorder(const std::string& name, int pos) {
    std::vector<RackBox*> l = get_children();
    int i = 0;
    RackBox *r = 0;
    for (std::vector<RackBox*>::iterator v = l.begin(); v != l.end(); ++v) {
	if ((*v)->get_id() == name) {
	    if (pos > i) {
		pos -= 1;
	    }
	    r = *v;
	    break;
	}
	++i;
    }
    assert(r);
    if (!r) {
	return;
    }
    reorder_child(*r, pos);
    renumber();
}

void RackContainer::on_add(Widget *ch) {
    add(*dynamic_cast<RackBox*>(ch));
}

void RackContainer::add(RackBox& r, int pos) {
    pack_start(r, Gtk::PACK_SHRINK);
    increment();
    if (main.is_loading()) {
	return;
    }
    reorder_child(r, pos);
    if (config_mode) {
	r.set_config_mode(true);
    }
    renumber();
}

void RackContainer::increment() {
    ++child_count;
    if (child_count == 1) {
	set_size_request(-1, -1);
    }
}

void RackContainer::decrement() {
    --child_count;
    assert(child_count >= 0);
    if (child_count == 0) {
	set_size_request(-1, min_containersize);
    }
}

void RackContainer::set_config_mode(bool mode) {
    config_mode = mode;
    std::vector<RackBox*> l = get_children();
    for (std::vector<RackBox*>::iterator c = l.begin(); c != l.end(); ++c) {
	(*c)->set_config_mode(mode);
    }
}

bool RackContainer::check_if_animate(const RackBox& rackbox) {
    if (!main.use_animations()) {
	return false;
    }
    std::vector<RackBox*> l = get_children();
    if (l.empty()) {
	return true;
    }
    if (l[l.size()-1] != &rackbox) {
	return true;
    }
    // is last child
    return main.check_if_rack_container_size_animate(*this);
}

void RackContainer::compress_all() {
    for (PluginDict::iterator i = main.plugins_begin(); i != main.plugins_end(); ++i) {
	i->second->compressed = true;
	RackBox *r = i->second->rackbox;
	if (r) {
	    if (r->can_compress()) {
		r->swtch(true);
	    }
	}
    }
}

void RackContainer::expand_all() {
    for (PluginDict::iterator i = main.plugins_begin(); i != main.plugins_end(); ++i) {
	i->second->compressed = false;
	RackBox *r = i->second->rackbox;
	if (r) {
	    if (r->can_compress()) {
		r->swtch(false);
	    }
	}
    }
}

bool rackboxes_less(RackBox *a, RackBox *b) {
    return a->position_weight() < b->position_weight();
}

void RackContainer::check_order() {
    int last_weight = -1;
    bool in_order = true;
    rackbox_list l = get_children();
    for (rackbox_list::iterator c = l.begin(); c != l.end(); ++c) {
	if (in_order) {
	    int w = (*c)->position_weight();
	    if (w < last_weight) {
		in_order = false;
	    }
	    last_weight = w;
	}
	(*c)->storeOrder();
    }
    if (!in_order) {
	std::vector<RackBox*> ol = get_children();
	std::sort(ol.begin(), ol.end(), rackboxes_less);
	int n = 0;
	for (std::vector<RackBox*>::iterator i = ol.begin(); i != ol.end(); ++i) {
	    reorder_child(**i, n++);
	}
    }
}

void RackContainer::renumber() {
    rackbox_list l = get_children();
    int pos = 0;
    unsigned int post_pre = 1;
    for (rackbox_list::iterator c = l.begin(); c != l.end(); ++c, ++pos) {
	if (strcmp((*c)->get_id(), "ampstack") == 0) { // FIXME
	    pos = 0;
	    post_pre = 0;
	    continue;
	}
	(*c)->setOrder(pos, post_pre);
    }
}

/****************************************************************
 ** class StackBoxBuilderNew
 */

StackBoxBuilderNew::StackBoxBuilderNew(
    gx_engine::GxEngine& engine_, gx_engine::ParamMap& pmap_,
    Gxw::WaveView &fWaveView_, Gtk::Label &convolver_filename_label_, gx_ui::GxUI& ui_,
    Glib::RefPtr<Gdk::Pixbuf> window_icon)
    : StackBoxBuilder(fTop, fBox, engine_, pmap_, fMode, fWaveView_, convolver_filename_label_, ui_, window_icon),
      engine(engine_), pmap(pmap_), fWaveView(fWaveView_),
      convolver_filename_label(convolver_filename_label_), widget() {
}

void StackBoxBuilderNew::openMonoRackBox(const char* label, int* posit, const char *id_on_off, const char *id_pre_post, const char *id_dialog) {
}

void StackBoxBuilderNew::closeMonoRackBox() {
}

void StackBoxBuilderNew::openStereoRackBox(const char* label, int* posit, const char *id_on_off, const char *id_dialog) {
}

void StackBoxBuilderNew::closeStereoRackBox() {
}

void StackBoxBuilderNew::openVerticalMidiBox(const char* label) {
    openVerticalBox(label);
}

void StackBoxBuilderNew::prepare() {
    fTop = 0;
    widget = new Gtk::VBox();
    widget->show();
    fBox[fTop] = GTK_WIDGET(widget->gobj());
    fMode[fTop] = kBoxMode;
}

#ifndef NDEBUG
void wnotify(gpointer data, GObject *where_the_object_was) {
    printf("WN %p %p\n", where_the_object_was, data);
}

// check if object will be finalized
void trace_finalize(Glib::Object *o, int n) {
    g_object_weak_ref(o->gobj(), wnotify, (gpointer)n);
}
#endif

void StackBoxBuilderNew::fetch(Gtk::Widget*& mainbox, Gtk::Widget*& minibox) {
    assert(fTop == 0);
    mainbox = widget;
    Glib::ListHandle<Gtk::Widget*> l = widget->get_children();
    if (l.size() == 2) {
	Glib::ListHandle<Gtk::Widget*>::iterator i = l.begin();
	minibox = new Gtk::VBox();
	minibox->show();
	(*i)->show();
	(*i)->reference(); //FIXME can't unmanage widget, reparent unrefs
	(*i)->reparent(*minibox);
    } else {
	minibox = 0;
    }
}

void StackBoxBuilderNew::get_box(const std::string& name, Gtk::Widget*& mainbox, Gtk::Widget*& minibox) {
    struct {
	const char *name;
	void (StackBoxBuilder::*func)();
    } mapping[] = {
	// mono
	//{ "ampdetail", &StackBoxBuilder::make_rackbox_ampdetail },
	{ "overdrive", &StackBoxBuilder::make_rackbox_overdrive },
	{ "echo", &StackBoxBuilder::make_rackbox_echo },
	{ "delay", &StackBoxBuilder::make_rackbox_delay },
	{ "freeverb", &StackBoxBuilder::make_rackbox_freeverb },
	{ "oscilloscope", &StackBoxBuilder::make_rackbox_oscilloscope },
	{ "low_highpass", &StackBoxBuilder::make_rackbox_low_highpass },
	{ "eqs", &StackBoxBuilder::make_rackbox_eqs },
	//{ "crybaby", &StackBoxBuilder::make_rackbox_crybaby },
	{ "gx_distortion", &StackBoxBuilder::make_rackbox_gx_distortion },
	{ "IR", &StackBoxBuilder::make_rackbox_IR },
	{ "compressor", &StackBoxBuilder::make_rackbox_compressor },
	{ "biquad", &StackBoxBuilder::make_rackbox_biquad },
	//{ "tremolo", &StackBoxBuilder::make_rackbox_tremolo },
	{ "phaser_mono", &StackBoxBuilder::make_rackbox_phaser_mono },
	{ "chorus_mono", &StackBoxBuilder::make_rackbox_chorus_mono },
	{ "flanger_mono", &StackBoxBuilder::make_rackbox_flanger_mono },
	{ "feedback", &StackBoxBuilder::make_rackbox_feedback },
	//{ "amp.tonestack", &StackBoxBuilder::make_rackbox_amp_tonestack },
	{ "cab", &StackBoxBuilder::make_rackbox_cab },
	{ "midi_out", &StackBoxBuilder::make_rackbox_midi_out },
	// stereo
	{ "chorus", &StackBoxBuilder::make_rackbox_chorus },
	{ "flanger", &StackBoxBuilder::make_rackbox_flanger },
	{ "phaser", &StackBoxBuilder::make_rackbox_phaser },
	{ "stereodelay", &StackBoxBuilder::make_rackbox_stereodelay },
	{ "stereoecho", &StackBoxBuilder::make_rackbox_stereoecho },
	{ "moog", &StackBoxBuilder::make_rackbox_moog },
	{ "ampmodul", &StackBoxBuilder::make_rackbox_ampmodul },
	{ "tonemodul", &StackBoxBuilder::make_rackbox_tonemodul },
	{ "jconv", &StackBoxBuilder::make_rackbox_jconv },
	{ "stereoverb", &StackBoxBuilder::make_rackbox_stereoverb }
    };
    mainbox = minibox = 0;
    for (unsigned int i = 0; i < sizeof(mapping) / sizeof(mapping[0]); ++i) {
	if (name == mapping[i].name) {
	    prepare();
	    (this->*mapping[i].func)();
	    fetch(mainbox, minibox);
	}
    }
}

/****************************************************************
 ** class Freezer
 */

Freezer::Freezer()
    : window(0), tag(), size_x(-1), size_y(-1) {
}

Freezer::~Freezer() {
    thaw();
}

void Freezer::freeze(Gtk::Window *w, int width, int height) {
    if (window) {
	thaw();
    }
    size_x = width;
    size_y = height;
    window = w;
    Glib::RefPtr<Gdk::Window> win = window->get_window();
    if (win) {
	win->freeze_updates();
	tag = Glib::signal_timeout().connect(sigc::mem_fun(*this, &Freezer::thaw_timeout), 500);
    }
}

void Freezer::freeze_and_size_request(Gtk::Window *w, int width, int height) {
    int wd, ht;
    w->get_size(wd, ht);
    if (wd >= width && ht == height) {
	return;
    }
    freeze(w, width, height);
    w->set_size_request(width, height);
}

bool Freezer::thaw_timeout() {
#ifndef NDEBUG
    gx_system::gx_print_error("freezer", "timeout");
#else
    gx_system::gx_print_warning("freezer", "timeout");
#endif
    if (size_y != -1) {
	window->set_size_request(-1,-1);
    }
    size_x = size_y = -1;
    Glib::RefPtr<Gdk::Window> win = window->get_window();
    window = 0;
    if (!win) {
	return false;
    }
    win->thaw_updates();
    return false;
}

void Freezer::thaw() {
    if (!tag.connected()) {
	return;
    }
    tag.disconnect();
    size_x = size_y = -1;
    Glib::RefPtr<Gdk::Window> win = window->get_window();
    window = 0;
    if (!win) {
	return;
    }
    win->thaw_updates();
}

bool Freezer::check_thaw(int width, int height) {
    if (size_x == -1) {
	return true;
    }
    Glib::RefPtr<Gdk::Window> win = window->get_window();
    if (!win) {
	return false;
    }
    if (win->get_state()) {
	thaw();
	return true;
    }
    if (size_y == -1) {
	if (size_x == width) {
	    window->set_size_request(-1,-1);
	    thaw();
	    return true;
	}
    }
    if (size_x <= width && size_y == height) {
	window->set_size_request(-1,-1);
	thaw();
	return true;
    }
    return false;
}


/****************************************************************
 ** class MainWindow
 */

template <class Param>
UiToggleAction<Param>::UiToggleAction(
    gx_ui::GxUI& ui_, Param& para, const Glib::ustring& name, const Glib::ustring& icon_name,
    const Glib::ustring& label, const Glib::ustring& tooltip,
    bool is_active)
    : Gtk::ToggleAction(name, icon_name, label, tooltip, is_active),
      gx_ui::GxUiItem(),
      param(para),
      ui(ui_) {
    ui.registerZone(param.zone(), this);
      }

template <class Param>
UiToggleAction<Param>::~UiToggleAction() {
    ui.unregisterZone(param.zone(), this);
}

template <>
bool UiToggleAction<gx_engine::SwitchParameter>::hasChanged() {
    return param.get() != get_active();
}

template <>
void UiToggleAction<gx_engine::SwitchParameter>::reflectZone() {
    set_active(param.get());
}

template <class Param>
void UiToggleAction<Param>::on_toggled() {
    param.set(get_active());
}

template <class Param>
bool UiToggleAction<Param>::hasChanged() {
    return param.get_value() != get_active();
}

template <class Param>
void UiToggleAction<Param>::reflectZone() {
    set_active(param.get_value());
}

template <class Param>
UiRadioAction<Param>::UiRadioAction(
    gx_ui::GxUI& ui_, Param& para, Gtk::RadioButtonGroup& group, const Glib::ustring& name, const Glib::ustring& icon_name,
    const Glib::ustring& label, const Glib::ustring& tooltip)
    : Gtk::RadioAction(group, name, icon_name, label, tooltip),
      gx_ui::GxUiItem(),
      param(para),
      ui(ui_) {
    ui.registerZone(param.zone(), this);
      }

template <class Param>
UiRadioAction<Param>::~UiRadioAction() {
    ui.unregisterZone(param.zone(), this);
}

template <>
bool UiRadioAction<gx_engine::SwitchParameter>::hasChanged() {
    return param.get() != get_current_value();
}

template <>
void UiRadioAction<gx_engine::SwitchParameter>::reflectZone() {
    set_current_value(param.get());
}

template <class Param>
void UiRadioAction<Param>::on_changed(const Glib::RefPtr<Gtk::RadioAction>& act) {
    param.set(get_current_value());
}

int GuiParameter::mainwin_x = -1;
int GuiParameter::mainwin_y = -1;
int GuiParameter::mainwin_width = -1;
int GuiParameter::mainwin_height = -1;

const value_pair GuiParameter::streaming_labels[] = {{"scale"}, {"stream"}, {0}};
const value_pair GuiParameter::tuning_labels[] = {{"(Chromatic)"},{"Standard"}, {"Standard/Es"}, {"Open E"}, {0}};

GuiParameter::GuiParameter(gx_engine::ParamMap& pmap) {
    gx_engine::get_group_table().insert("racktuner", "Rack Tuner");
    ui_racktuner = pmap.reg_par("ui.racktuner", "Tuner", 0, true);
    racktuner_streaming = pmap.reg_enum_par("racktuner.streaming", "Streaming Mode", streaming_labels, (int*)0, 1);
    racktuner_tuning = pmap.reg_enum_par("racktuner.tuning", "Tuning", tuning_labels, (int*)0, 0);
    racktuner_scale_lim = pmap.reg_par("racktuner.scale_lim", "Limit", 0, 3.0, 1.0, 10.0, 1.0);
    ui_tuner_reference_pitch = pmap.reg_par_non_preset("ui.tuner_reference_pitch", "?Tuner Reference Pitch",
						       0, 440, 427, 453, 0.1);

    show_plugin_bar = pmap.reg_switch("system.show_toolbar", false, false);
    presets = pmap.reg_switch("system.show_presets", false, false);
    show_rack = pmap.reg_switch("system.show_rack", false, true);
    order_rack_v = pmap.reg_switch("system.order_rack_v", false, true);
    tuner = pmap.reg_non_midi_par("system.show_tuner", (bool*)0, false);
    show_values = pmap.reg_switch("system.show_value", false, true);
    show_tooltips = pmap.reg_switch("system.show_tooltips", false, true);
    midi_in_presets = pmap.reg_switch("system.midi_in_preset", false, false);
    mainwin_x_param = pmap.reg_non_midi_par("system.mainwin_x", &mainwin_x, false, -1, -1, 99999);
    mainwin_y_param = pmap.reg_non_midi_par("system.mainwin_y", &mainwin_y, false, -1, -1, 99999);
    mainwin_width_param = pmap.reg_non_midi_par("system.mainwin_width", &mainwin_width, false, -1, -1, 99999);
    mainwin_height_param = pmap.reg_non_midi_par("system.mainwin_height", &mainwin_height, false, -1, -1, 99999);
}

void update_scrolled_window(Gtk::ScrolledWindow& w) {
    Gtk::PolicyType hp, vp;
    w.get_policy(hp, vp);
    w.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    w.set_policy(hp, vp);
}

/*
** moving / hiding / showing parts of the UI
*/

int MainWindow::skin = -1;
bool MainWindow::no_warn_latency;

void MainWindow::maybe_shrink_horizontally() {
    Glib::RefPtr<Gdk::Window> w = window->get_window();
    if (!w) {
	return;
    }
    int state = w->get_state();
    if (state & (Gdk::WINDOW_STATE_MAXIMIZED | Gdk::WINDOW_STATE_FULLSCREEN)) {
	return;
    }
    Gtk::Requisition req;
    window->size_request(req);
    int x, y;
    window->get_position(x, y);
    Gdk::Geometry geom;
    geom.min_width = req.width;
    geom.min_height = req.height;
    w->set_geometry_hints(geom, Gdk::HINT_MIN_SIZE);
    w->move_resize(x, y, req.width, std::max(req.height, window_height));
    if (!state) {
	freezer.freeze_until_width_update(window, req.width);
    }
}

void MainWindow::on_show_tuner() {
    bool v = tuner_action->get_active();
    if (v) {
	tunerbox->show();
    } else {
	tunerbox->hide();
    }
    update_scrolled_window(*vrack_scrolledbox);
}

void MainWindow::load_widget_pointers() {
    bld->get_toplevel("MainWindow", window);
    bld->find_widget("tunerbox", tunerbox);
    bld->find_widget("vrack_scrolledbox", vrack_scrolledbox);
    bld->find_widget("stereorackcontainerH", stereorackcontainerH);
    bld->find_widget("stereorackcontainerV", stereorackcontainerV);
    bld->find_widget("rackcontainer", rackcontainer);
    bld->find_widget("stereorackbox", stereorackbox);
    bld->find_widget("monorackcontainer", monocontainer);
    bld->find_widget("monoampcontainer:ampdetails", monoampcontainer);
    bld->find_widget("main_vpaned", main_vpaned);
    bld->find_widget("amp_toplevel_box", amp_toplevel_box);
    bld->find_widget("monobox", monobox);
    bld->find_widget("upper_rackbox", upper_rackbox);
    bld->find_widget("preset_scrolledbox", preset_scrolledbox);
    bld->find_widget("effects_frame_paintbox", effects_frame_paintbox);
    bld->find_widget("status_image", status_image);
    bld->find_widget("jackd_image", jackd_image);
    bld->find_widget("logstate_image", logstate_image);
    bld->find_widget("menubox", menubox);
    bld->find_widget("show_rack:barbutton", show_rack_button);
    bld->find_widget("config_mode:barbutton", config_mode_button);
    bld->find_widget("liveplay:barbutton", liveplay_button);
    bld->find_widget("tuner:barbutton", tuner_button);
    bld->find_widget("effects:barbutton", effects_button);
    bld->find_widget("presets:barbutton", presets_button);
    bld->find_widget("compress:barbutton", compress_button);
    bld->find_widget("expand:barbutton", expand_button);
    bld->find_widget("effects_toolpalette", effects_toolpalette);
    bld->find_widget("amp_background:ampbox", amp_background);
    bld->find_widget("tuner_on_off", tuner_on_off);
    bld->find_widget("tuner_mode", tuner_mode);
    bld->find_widget("tuner_reference_pitch", tuner_reference_pitch);
    bld->find_widget("tuner_tuning", tuner_tuning);
    bld->find_widget("racktuner", racktuner);
    bld->find_widget("ampdetail_compress:effect_reset", ampdetail_compress);
    bld->find_widget("ampdetail_expand:effect_reset", ampdetail_expand);
    bld->find_widget("ampdetail_mini", ampdetail_mini);
    bld->find_widget("ampdetail_normal", ampdetail_normal);
    bld->find_widget("fastmeterL", fastmeter[0]);
    bld->find_widget("fastmeterR", fastmeter[1]);
    bld->find_widget("preset_status", preset_status);
}

void MainWindow::on_select_preset(const Glib::RefPtr<Gtk::RadioAction>& act) {
    gx_system::PresetFile *pf = gx_settings.get_current_bank_file();
    gx_settings.load_preset(pf, pf->get_name(act->get_current_value()));
}

void MainWindow::show_selected_preset() {
    Glib::ustring t;
    if (gx_settings.get_current_source() != gx_system::GxSettingsBase::state) {
	t = gx_settings.get_current_bank() + " / " + gx_settings.get_current_name();
    }
    preset_status->set_text(t);
    if (!preset_list_menu_bank.empty()) {
	if (gx_settings.setting_is_preset() && preset_list_menu_bank == gx_settings.get_current_bank()) {
	    select_preset_action->set_current_value(
		gx_settings.get_current_bank_file()->get_index(
		    gx_settings.get_current_name()));
	    return;
	}
	if (preset_list_merge_id) {
	    uimanager->remove_ui(preset_list_merge_id);
	    uimanager->remove_action_group(preset_list_actiongroup);
	}
    }
    if (!gx_settings.setting_is_preset()) {
	preset_list_menu_bank.clear();
	preset_list_merge_id = 0;
	preset_list_actiongroup.reset();
	return;
    }
    preset_list_actiongroup = Gtk::ActionGroup::create("PresetList");
    preset_list_menu_bank = gx_settings.get_current_bank();
    Glib::ustring s = "<menubar><menu action=\"PresetsMenu\"><menu action=\"PresetListMenu\">";
    gx_system::PresetFile *pf = gx_settings.get_current_bank_file();
    Gtk::RadioButtonGroup pg;
    int idx = 0;
    char c = '1';
    for (gx_system::PresetFile::iterator i = pf->begin(); i != pf->end(); ++i) {
	Glib::ustring actname = "PresetList_" + i->name;
	Glib::RefPtr<Gtk::RadioAction> action = Gtk::RadioAction::create(pg, actname, i->name);
	if (c <= '9') {
	    preset_list_actiongroup->add(action, Gtk::AccelKey(Glib::ustring::compose("%1", (char)c++)));
	} else {
	    preset_list_actiongroup->add(action);
	}
	if (idx == 0) {
	    select_preset_action = action;
	}
	s += Glib::ustring::compose("<menuitem action=\"%1\"/>", actname);
	action->property_value().set_value(idx++);
    }
    s += "</menu></menu></menubar>";
    uimanager->insert_action_group(preset_list_actiongroup);
    preset_list_merge_id = uimanager->add_ui_from_string(s);
    select_preset_action->set_current_value(
	pf->get_index(gx_settings.get_current_name()));
    select_preset_action->signal_changed().connect(
	sigc::mem_fun(*this, &MainWindow::on_select_preset));
    dynamic_cast<Gtk::MenuItem*>(uimanager->get_widget("/menubar/PresetsMenu/PresetListMenu"))->set_label(_("_Bank: ")+preset_list_menu_bank);
}

bool MainWindow::is_variable_size() {
    return presets_action->get_active() || show_rack_action->get_active();
}

void MainWindow::maybe_change_resizable() {
    Glib::RefPtr<Gdk::Window> w = window->get_window();
    if (w && w->get_state() != 0) {
	return;
    }
    if (!is_variable_size() && window->get_resizable()) {
	window->set_resizable(false);
    } else if (!window->get_resizable()) {
	window->set_resizable(true);
    }
}

void MainWindow::on_show_rack() {
    Gtk::Widget *w;
    if (rackbox_stacked_vertical()) {
	w = stereorackcontainerV;
    } else {
	w = stereorackbox;
    }
    bool v = show_rack_action->get_active();
    rackv_action->set_sensitive(v);
    rackh_action->set_sensitive(v);
    rackcontainer->set_border_width(v ? 18 : 0); //FIXME (just experimental)
    if (v) {
	window_height = max(window_height, window->size_request().height);
	//main_vpaned->child_set_property(amp_toplevel_box, "resize", true);
	child_set_property(*main_vpaned, *amp_toplevel_box, "resize", true);
	main_vpaned->set_position(oldpos);
	w->show();
	monoampcontainer->show();
	monorackcontainer.show_entries();
	vrack_scrolledbox->set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_AUTOMATIC);
	vrack_scrolledbox->set_size_request(scrl_size_x, scrl_size_y);
	Glib::RefPtr<Gdk::Window> win = window->get_window();
	if (!win || win->get_state() == 0) {
	    Gtk::Requisition req;
	    window->size_request(req);
	    req.height = max(req.height, window_height);
	    freezer.freeze_and_size_request(window, req.width, req.height);
	}
    } else {
	oldpos = main_vpaned->get_position();
	child_set_property(*main_vpaned, *amp_toplevel_box, "resize", false);
	main_vpaned->set_position(0);
	int wd;
	window->get_size(wd, window_height);
	w->hide();
	monoampcontainer->hide();
	monorackcontainer.hide_entries();
	vrack_scrolledbox->set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_NEVER);
	vrack_scrolledbox->get_size_request(scrl_size_x, scrl_size_y);
	vrack_scrolledbox->set_size_request(-1,-1);
	maybe_shrink_horizontally();
    }
    maybe_change_resizable();
}

void MainWindow::on_compress_all() {
    monorackcontainer.compress_all();
    stereorackcontainer.compress_all();
    on_ampdetail_switch(true);
}

void MainWindow::on_expand_all() {
    monorackcontainer.expand_all();
    stereorackcontainer.expand_all();
    on_ampdetail_switch(false);
}

void MainWindow::on_rack_configuration() {
    bool v = rack_config_action->get_active();
    show_plugin_bar_action->set_sensitive(!v);
    show_rack_action->set_sensitive(!v);
    tuner_action->set_sensitive(!v);
    presets_action->set_sensitive(!v);
    compress_action->set_sensitive(!v);
    expand_action->set_sensitive(!v);
    Gtk::Requisition req;
    monobox->size_request(req);
    stereorackcontainer.set_config_mode(v);
    monorackcontainer.set_config_mode(v);
    bool plugin_bar = show_plugin_bar_action->get_active();
    if (v) {
	pre_act = presets_action->get_active();
	if (pre_act) {
	    preset_scrolledbox->hide();
	    presets_action->set_active(false);
	}
	show_rack_action->set_active(true);
	effects_frame_paintbox->show();
	upper_rackbox->hide();
	Gtk::Requisition req2;
	effects_frame_paintbox->size_request(req2);
	int width = req.width;
	if (!plugin_bar) {
	    if (rackbox_stacked_vertical()) {
		width -= req2.width;
	    } else {
		width -= req2.width/2;
	    }
	}
	monobox->set_size_request(width,-1);
    } else {
	if (pre_act) {
	    presets_action->set_active(true);
	}
	if (!plugin_bar) {
	    effects_frame_paintbox->hide();
	}
	upper_rackbox->show();
	monobox->set_size_request(-1,-1);
    }
    if (!plugin_bar) {
	update_scrolled_window(*vrack_scrolledbox);
	update_scrolled_window(*stereorackbox);
	maybe_shrink_horizontally();
    }
}

void MainWindow::on_show_plugin_bar() {
    bool v = show_plugin_bar_action->get_active();
    show_rack_action->set_sensitive(!v);
    if (v) {
	show_rack_action->set_active(true);
    }
    effects_frame_paintbox->set_visible(v);
    update_scrolled_window(*vrack_scrolledbox);
    update_scrolled_window(*stereorackbox);
    maybe_shrink_horizontally();
}

void MainWindow::move_widget(Gtk::Widget& w, Gtk::Box& b1, Gtk::Box& b2) {
    // reparent does not always work when child is hidden
    // (sometimes wrong position when shown later),
    // use remove / add
    b1.remove(w);
    b1.hide();
    b2.pack_start(w);
    b2.show();
}

int MainWindow::rackbox_stacked_vertical() const {
    return rackv_action->get_current_value() == 0;
}

void MainWindow::change_expand(Gtk::Widget& w, bool value) {
    Gtk::Box *p = dynamic_cast<Gtk::Box*>(w.get_parent());
    int expand, fill;
    unsigned int padding;
    GtkPackType pack_type;
    gtk_box_query_child_packing(p->gobj(), w.gobj(), &expand, &fill, &padding, &pack_type);
    gtk_box_set_child_packing(p->gobj(), w.gobj(), value, fill, padding, pack_type);
}

double MainWindow::stop_at_stereo_bottom(double off, double step_size, double pagesize) {
    Gtk::Allocation alloc = stereorackcontainer.get_allocation();
    double lim = alloc.get_y() + alloc.get_height() - pagesize;
    if (off >= lim) {
	return off;
    }
    return min(off+step_size, lim);
}

double MainWindow::stop_at_mono_top(double off, double step_size) {
    Gtk::Allocation alloc = monorackcontainer.get_allocation();
    printf(" [%d] ", alloc.get_y());
    if (off < alloc.get_y()) {
	return off;
    }
    return max(off-step_size, double(alloc.get_y()));
}

void MainWindow::on_dir_changed(Glib::RefPtr<Gtk::RadioAction> act) {
    if (act->get_current_value()) {
	// horizontally
	move_widget(stereorackcontainer, *stereorackcontainerV, *stereorackcontainerH);
	stereorackbox->show();
    } else {
	move_widget(stereorackcontainer, *stereorackcontainerH, *stereorackcontainerV);
	stereorackbox->hide();
	maybe_shrink_horizontally();
    }
}

void MainWindow::on_configure_event(GdkEventConfigure *ev) {
    if (freezer.check_thaw(ev->width, ev->height)) {
	if (is_variable_size()) {
	    window_height = ev->height;
	}
    }
}

RackBox *MainWindow::add_rackbox_internal(PluginUI& plugin, Gtk::Widget *mainwidget, Gtk::Widget *miniwidget,
					  bool mini, int pos, bool animate, Gtk::Widget *bare) {
    RackBox *r = new RackBox(plugin, *this, bare);
    if (mini) {
	r->swtch(true);
    }
    r->pack(mainwidget, miniwidget);
    if (plugin.get_type() == PLUGIN_TYPE_MONO) {
	monorackcontainer.add(*manage(r), pos);
    } else {
	stereorackcontainer.add(*manage(r), pos);
    }
    if (animate) {
	r->animate_insert();
    }
    return r;
}

class UiBuilderImplNew: public gx_gui::UiBuilderImpl {
private:
    MainWindow& main;
    std::vector<PluginUI*> *pluginlist;
public:
    virtual bool load(gx_engine::Plugin *p);
    bool load_unit(PluginUI &pl);
    UiBuilderImplNew(MainWindow *i, gx_gui::StackBoxBuilder *b, std::vector<PluginUI*> *pl=0);
};

UiBuilderImplNew::UiBuilderImplNew(MainWindow *i, gx_gui::StackBoxBuilder *b, std::vector<PluginUI*> *pl)
    : gx_gui::UiBuilderImpl(b), main(*i), pluginlist(pl) {
}

bool UiBuilderImplNew::load(gx_engine::Plugin *p) {
    PluginDef *pd = p->pdef;
    if (!pd->load_ui) {
	return false;
    }
    main.add_plugin(pluginlist, pd->id, "", "");
    return true;
}

bool UiBuilderImplNew::load_unit(PluginUI &pl) {
    gx_engine::Plugin *p = pl.plugin;
    PluginDef *pd = p->pdef;
    if (!pd->load_ui) {
	return false;
    }
    plugin = pd;
    dynamic_cast<StackBoxBuilderNew*>(intf)->prepare();
    if (pd->flags & PGN_STEREO) {
	pd->load_ui(*this);
    } else {
	pd->load_ui(*this);
    }
    return true;
}

void load_rack_ui(const std::string& fname, gx_ui::GxUI& ui, Gtk::Widget*& mainwidget, Gtk::Widget*& miniwidget) {
    const char *id_list[] = {"rackbox", "minibox", 0};
    Glib::RefPtr<gx_gui::GxBuilder> bld = gx_gui::GxBuilder::create_from_file(fname, &ui, id_list);
    bld->get_toplevel("rackbox", mainwidget);
    miniwidget = 0;
    if (bld->has_object("minibox")) {
	bld->get_toplevel("minibox", miniwidget);
    }
}

PluginDict::~PluginDict() {
    for (std::map<std::string, PluginUI*>::iterator i = begin(); i != end(); ++i) {
	ui.unregisterZone(&i->second->plugin->box_visible, i->second);
	ui.unregisterZone(&i->second->plugin->position, i->second);
	ui.unregisterZone(&i->second->plugin->effect_post_pre, i->second);
	delete i->second;
    }
}

RackBox *MainWindow::add_rackbox(PluginUI& pl, bool mini, int pos, bool animate) {
    Gtk::Widget *mainwidget = 0;
    Gtk::Widget *miniwidget = 0;
    if (!mainwidget && !pl.fname.empty()) {
	load_rack_ui(pl.fname, ui, mainwidget, miniwidget);
    }
    if (!mainwidget) {
	boxbuilder.get_box(pl.get_id(), mainwidget, miniwidget);
    }
    if (!mainwidget) {
	UiBuilderImplNew builder(this, &boxbuilder);
	if (builder.load_unit(pl)) {
	    boxbuilder.fetch(mainwidget, miniwidget);
	}
    }
    if (!mainwidget) {
	std::string gladefile = options.get_builder_filepath(
	    std::string(pl.get_id())+"_ui.glade");
	if (access(gladefile.c_str(), R_OK) == 0) {
	    load_rack_ui(gladefile, ui, mainwidget, miniwidget);
	}
    }
    return add_rackbox_internal(pl, mainwidget, miniwidget, mini, pos, animate);
}

bool MainWindow::check_if_rack_container_size_animate(const RackContainer& rackcontainer) const {
    return true; // FIXME
    if (&rackcontainer == &monorackcontainer && rackbox_stacked_vertical() && !stereorackcontainer.empty()) {
	// non-empty stereo box below
	return true;
    }
    return false;
}

void MainWindow::add_icon(const std::string& name) {
    PluginUI *p = plugin_dict[name];
    p->toolitem->show();
}

void MainWindow::on_show_values() {
    std::string s =
	"style \"ShowValue\" {\n"
	"  GxRegler::show-value = " + gx_system::to_string(show_values_action->get_active()) + "\n"
	"}\n"
	"class \"*GxRegler*\" style:highest \"ShowValue\"\n";
    gtk_rc_parse_string(s.c_str());
    gtk_rc_reset_styles(gtk_settings_get_default());
}

void MainWindow::on_preset_action() {
    maybe_change_resizable();
    bool v = presets_action->get_active();
    preset_window->on_preset_select(v);
    if (v && !show_rack_action->get_active()) {
	Gtk::Requisition req;
	window->size_request(req);
	int x, y;
	window->get_position(x, y);
	while (Gtk::Main::events_pending()) {
	    Gtk::Main::iteration();
	}
	if (window->get_mapped()) {
	    window->get_window()->move_resize(x, y, req.width, max(req.height, window_height));
	} else {
	    window->resize(req.width, max(req.height, window_height));
	    window->move(x, y);
	}
    }
}

/*
** UI initialization
*/

void MainWindow::add_toolitem(PluginUI& pl, Gtk::ToolItemGroup *gw) {
    Gtk::ToolItem *tb = new Gtk::ToolItem();
    tb->set_use_drag_window(true);
    tb->signal_drag_begin().connect(sigc::bind(sigc::mem_fun(*this, &MainWindow::on_ti_drag_begin), sigc::ref(pl)));
    tb->signal_drag_end().connect(sigc::mem_fun(*this, &MainWindow::on_ti_drag_end));
    tb->signal_drag_data_delete().connect(sigc::bind(sigc::mem_fun(*this, &MainWindow::on_ti_drag_data_delete), pl.get_id()));
    tb->signal_button_press_event().connect(sigc::bind(sigc::mem_fun(*this, &MainWindow::on_ti_button_press), pl.get_id()));
    std::vector<Gtk::TargetEntry> listTargets;
    if (pl.get_type() == PLUGIN_TYPE_MONO) {
	listTargets.push_back(Gtk::TargetEntry("application/x-gtk-tool-palette-item-mono", Gtk::TARGET_SAME_APP, 0));
    } else {
	listTargets.push_back(Gtk::TargetEntry("application/x-gtk-tool-palette-item-stereo", Gtk::TARGET_SAME_APP, 0));
    }
    tb->drag_source_set(listTargets, Gdk::BUTTON1_MASK, Gdk::ACTION_MOVE);
    tb->signal_drag_data_get().connect(sigc::bind(sigc::mem_fun(*this, &MainWindow::on_ti_drag_data_get), pl.get_id()));
    Gtk::Image *img = new Gtk::Image(pl.icon);
    if (!pl.tooltip.empty()) {
	img->set_tooltip_text(pl.tooltip);
    }
    tb->add(*manage(img));
    pl.toolitem = tb;
    gw->add(*manage(tb));
    pl.group = gw;
}

bool MainWindow::on_visibility_notify(GdkEventVisibility *ev) {
    bool v = ev->state != GDK_VISIBILITY_FULLY_OBSCURED;
    if (v == is_visible) {
	return false;
    }
    is_visible = v;
    return false;
}

void MainWindow::on_live_play() {
    live_play->on_live_play(live_play_action);
}

void MainWindow::on_ti_drag_begin(const Glib::RefPtr<Gdk::DragContext>& context, const PluginUI& plugin) {
    drag_icon = new DragIcon(plugin, context, options);
}

void MainWindow::on_ti_drag_end(const Glib::RefPtr<Gdk::DragContext>& context) {
    if (drag_icon) {
	delete drag_icon;
	drag_icon = 0;
    }
}

void MainWindow::on_ti_drag_data_get(const Glib::RefPtr<Gdk::DragContext>& context, Gtk::SelectionData& selection, int info, int timestamp, const char *effect_id) {
    selection.set(*context->get_targets().begin(), effect_id);
}

void MainWindow::hide_effect(const std::string& name) {
    plugin_dict[name]->toolitem->hide();
}

void MainWindow::on_ti_drag_data_delete(const Glib::RefPtr<Gdk::DragContext>& context, const char *effect_id) {
    hide_effect(effect_id);
}

bool MainWindow::on_ti_button_press(GdkEventButton *ev, const char *effect_id) {
    if (ev->type == GDK_2BUTTON_PRESS) {
	get_plugin(effect_id)->display_new();
	return true;
    }
    return false;
}

void MainWindow::on_tp_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, const Gtk::SelectionData& data, int info, int timestamp) {
    Glib::ustring id = data.get_data_as_string();
    PluginUI *p = get_plugin(id);
    p->display(false, false);
    add_icon(id);
    p->group->set_collapsed(false);
}

void MainWindow::jack_connection() {
    bool v = jackserverconnection_action->get_active();
    if (!connect_jack(v)) {
	jackserverconnection_action->set_active(!v);
    }
}

void MainWindow::on_portmap_response(int) {
    jackports_action->set_active(false);
}

void MainWindow::on_portmap_activate() {
    if (jackports_action->get_active()) {
	if (portmap_window) {
	    return;
	}
	portmap_window = gx_portmap::PortMapWindow::create(jack, ui, accel_group);
	portmap_window->signal_response().connect(
	    sigc::mem_fun(*this, &MainWindow::on_portmap_response));
    } else {
	if (!portmap_window) {
	    return;
	}
	delete portmap_window;
	portmap_window = 0;
    }
}

void MainWindow::on_miditable_toggle() {
    gx_main_midi::MidiControllerTable::toggle(pmap, midicontroller_action);
}

void MainWindow::change_skin(Glib::RefPtr<Gtk::RadioAction> action) {
    unsigned int n = action->get_current_value();
    skin_changed.modifyZone(n);
    set_new_skin(n);
}

void MainWindow::set_new_skin(unsigned int idx) {
    assert(idx < options.skin.skin_list.size());
    string rcfile = options.get_style_filepath(
	"gx_head_" + options.skin.skin_list[idx] + ".rc");
    gtk_rc_parse(rcfile.c_str());
    gtk_rc_reset_styles(gtk_settings_get_default());
    make_icons();
}

void MainWindow::add_skin_menu() {
    Glib::ustring s = "<menubar><menu action=\"OptionsMenu\"><menu action=\"SkinMenu\">";
    int idx = 0;
    Gtk::RadioButtonGroup sg;
    value_pair *skin_labels = new value_pair[options.skin.skin_list.size()+1];
    for (vector<string>::iterator i = options.skin.skin_list.begin();
	 i != options.skin.skin_list.end();
	 ++i) {
	Glib::ustring name = *i;
	Glib::ustring actname = Glib::ustring::compose("ChangeSkin_%1", name);
	s += Glib::ustring::compose("<menuitem action=\"%1\"/>", actname);
	Glib::RefPtr<Gtk::RadioAction> action = Gtk::RadioAction::create(sg, actname, name);
	actiongroup->add(action);
	if (idx == 0) {
	    action->signal_changed().connect(
		sigc::mem_fun(*this, &MainWindow::change_skin));
	    skin_action = action;
	}
	skin_labels[idx].value_id = strdup(name.c_str()); // will not be freed
	skin_labels[idx].value_label = 0;
	action->property_value().set_value(idx++);
    }
    s.append("</menu></menu></menubar>");
    uimanager->add_ui_from_string(s);
    skin_labels[idx].value_id = 0;
    skin_labels[idx].value_label = 0;
    pmap.reg_non_midi_enum_par("ui.skin_name", "?ui.skin_name", skin_labels, &skin, false, 6);
}

enum GxJackLatencyChange {
    kChangeLatency = 1,
    kKeepLatency   = 2
};

// check user's decision to turn off latency change warning
void MainWindow::user_disable_latency_warn(Gtk::CheckButton* disable_warn) {
    no_warn_latency = disable_warn->get_active();
}

int MainWindow::gx_wait_latency_warn() {
    Gtk::Dialog warn_dialog;
    // no set_destroy_with_parent() ??
    warn_dialog.property_destroy_with_parent().set_value(true);

    Gtk::VBox box(0, 4);
    Gtk::Label labelt(_("\nWARNING\n"));
    Gtk::Label labelt1(
	_("CHANGING THE JACK_BUFFER_SIZE ON THE FLY \n"
	  "MAY CAUSE UNPREDICTABLE EFFECTS \n"
	  "TO OTHER RUNNING JACK APPLICATIONS. \n"
	  "DO YOU WANT TO PROCEED ?"));
    Gdk::Color colorGreen("#969292");
    labelt1.modify_fg(Gtk::STATE_NORMAL, colorGreen);
    Pango::FontDescription font = labelt1.get_style()->get_font();
    font.set_size(10*Pango::SCALE);
    font.set_weight(Pango::WEIGHT_BOLD);
    labelt1.modify_font(font);

    Gdk::Color colorWhite("#ffffff");
    labelt.modify_fg(Gtk::STATE_NORMAL, colorWhite);
    font = labelt.get_style()->get_font();
    font.set_size(14*Pango::SCALE);
    font.set_weight(Pango::WEIGHT_BOLD);
    labelt.modify_font(font);

    warn_dialog.add_button(_("Yes"), kChangeLatency);
    warn_dialog.add_button(_("No"),  kKeepLatency);

    Gtk::HBox box1(0, 4);
    Gtk::HBox box2(0, 4);

    Gtk::CheckButton disable_warn;
    disable_warn.signal_clicked().connect(
	sigc::bind(
	    sigc::mem_fun(*this, &MainWindow::user_disable_latency_warn),
	    &disable_warn));

    Gtk::Label labelt2(
	_("Don't bother me again with such a question, "
	  "I know what I am doing"));

    box.add(labelt);
    box.add(labelt1);
    box.add(box2);
    box.add(box1);
    box1.add(disable_warn);
    box1.add(labelt2);
    warn_dialog.get_vbox()->add(box);

    labelt2.modify_fg(Gtk::STATE_NORMAL, colorWhite);

    font = labelt2.get_style()->get_font();
    font.set_size(8*Pango::SCALE);
    font.set_weight(Pango::WEIGHT_NORMAL);
    labelt2.modify_font(font);

    box.show_all();

    return warn_dialog.run();
}

void MainWindow::change_latency(Glib::RefPtr<Gtk::RadioAction> action) {
    // are we a proper jack gxjack.client ?
    if (!jack.client) {
        gx_system::gx_print_error(
            _("Jack Buffer Size setting"),
            _("we are not a jack gxjack.client, server may be down")
            );
        return;
    }
    jack_nframes_t buf_size = action->get_current_value();
    if (buf_size == jack.get_jack_bs()) {
        return;
    }
    if (!no_warn_latency && gx_wait_latency_warn() != kChangeLatency) {
	Glib::signal_idle().connect_once(
	    sigc::bind(
		sigc::mem_fun(action.operator->(), &Gtk::RadioAction::set_current_value), jack.get_jack_bs()));
    } else {
        if (jack_set_buffer_size(jack.client, buf_size) != 0)
            gx_system::gx_print_warning(_("Setting Jack Buffer Size"),
					_("Could not change latency"));
    }	
    gx_system::gx_print_info(
	_("Jack Buffer Size"),
	boost::format(_("latency is %1%")) % jack_get_buffer_size(jack.client));
}

void MainWindow::add_latency_menu() {
    Glib::ustring s = "<menubar><menu action=\"EngineMenu\"><menu action=\"JackLatency\">";
    Gtk::RadioButtonGroup group;
    const int min_pow = 4;  // 2**4  = 16
    const int max_pow = 13; // 2**13 = 8192
    int jack_buffer_size = 16;
    for (int i = 0; i <= max_pow-min_pow; ++i) {
	Glib::ustring name = gx_system::to_string(jack_buffer_size);
	Glib::ustring actname = Glib::ustring::compose("Latency_%1", name);
	s += Glib::ustring::compose("<menuitem action=\"%1\"/>", actname);
	Glib::RefPtr<Gtk::RadioAction> action = Gtk::RadioAction::create(group, actname, name);
	actiongroup->add(action);
	if (i == 0) {
	    action->signal_changed().connect(
		sigc::mem_fun(*this, &MainWindow::change_latency));
	    latency_action = action;
	}
	action->property_value().set_value(jack_buffer_size);
	jack_buffer_size *= 2;
    }
    s.append("</menu></menu></menubar>");
    uimanager->add_ui_from_string(s);
    pmap.reg_non_midi_par("ui.latency_nowarn", &no_warn_latency, false, false);
}

void MainWindow::set_latency() {
    jack_nframes_t n = jack.get_jack_bs();
    if (n > 0) {
	latency_action->set_current_value(n);
    }
}

void gx_show_help() {
    GError *error = NULL;
    gtk_show_uri(gdk_screen_get_default(), "http://sourceforge.net/apps/mediawiki/guitarix/index.php?title=Main_Page",
    gtk_get_current_event_time(), &error);
    if (error)
    {
        gx_system::gx_print_error("guitarix help",
				  _("failed to load online help   "));
        g_error_free(error);
    } 

}

// ---- popup warning
int gx_message_popup(const char* msg) {
    // check msg validity
    if (!msg) {
        gx_system::gx_print_warning("Message Popup",
                         string(_("warning message does not exist")));
        return -1;
    }

    // build popup window
    GtkWidget *about;
    GtkWidget *label;
    GtkWidget *ok_button;

    about = gtk_dialog_new();
    ok_button  = gtk_button_new_from_stock(GTK_STOCK_OK);

    label = gtk_label_new(msg);

    GtkStyle *style = gtk_widget_get_style(label);

    pango_font_description_set_size(style->font_desc, 10*PANGO_SCALE);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);

    gtk_widget_modify_font(label, style->font_desc);

    gtk_label_set_selectable(GTK_LABEL(label), TRUE);

    gtk_container_add(GTK_CONTAINER(GTK_DIALOG(about)->vbox), label);

    GTK_BOX(GTK_DIALOG(about)->action_area)->spacing = 3;
    gtk_container_add(GTK_CONTAINER(GTK_DIALOG(about)->action_area), ok_button);

    g_signal_connect_swapped(ok_button, "clicked",
                              G_CALLBACK(gtk_widget_destroy), about);

    g_signal_connect(GTK_DIALOG(about)->vbox, "expose-event", G_CALLBACK(gx_cairo::start_box_expose), NULL);
    gtk_widget_set_redraw_on_allocate(GTK_WIDGET(GTK_DIALOG(about)->vbox),true);
    gtk_widget_show(ok_button);
    gtk_widget_show(label);
    return gtk_dialog_run (GTK_DIALOG(about));
}

// ----menu funktion about
void gx_show_about() {
    static string about;
    if (about.empty()) {
        about +=
            _("\n\n  This Aplication is to a large extent provided"
            "\n  with the marvelous faust compiler.Yann Orlary"
            "\n  http://faust.grame.fr/"
            "\n  A large part is based on the work of Julius Orion Smith"
            "\n  http://ccrma.stanford.edu/realsimple/faust/"
            "\n  and Albert Graef\n  http://q-lang.sourceforge.net/examples.html#Faust"
            "\n\n\n  gx_head ");

        about += GX_VERSION;

        about +=
            _("\n  for impulse response it use zita-convolver "
            "\n  byFons Adriaensen "
            "\n  http://www.kokkinizita.net/linuxaudio/index.html "
            "\n\n  authors: Hermann Meyer <brummer-@web.de>"
            "\n  authors: James Warden <warjamy@yahoo.com>"
            "\n  authors: Andreas Degert <andreas.degert@googlemail.com>    "
            "\n  authors: Pete Shorthose <pshorthose@gmail.com>    "
            "\n  home: http://guitarix.sourceforge.net/\n");
    }

    gx_message_popup(about.c_str());
}

static void set_tooltips(bool v) {
    gtk_settings_set_long_property(
        gtk_settings_get_default(), "gtk-enable-tooltips", v,
        "gx_head menu-option");
}

void MainWindow::on_select_jack_control() {
    if (select_jack_control) {
	select_jack_control->present();
    } else {
	select_jack_control = gx_gui::SelectJackControlPgm::create(&ui, options, pmap);
	select_jack_control->signal_close().connect(
	    sigc::mem_fun(*this, &MainWindow::delete_select_jack_control));
	select_jack_control->set_transient_for(*window);
	select_jack_control->show();
    }
}

void MainWindow::delete_select_jack_control() {
    delete select_jack_control;
    select_jack_control = 0;
}

// show loggingbox
void MainWindow::on_log_activate() {
    if (loggingbox_action->get_active()) {
        gint rxorg, ryorg;
        window->get_position(rxorg, ryorg);
        fLoggingWindow.move(rxorg+5, ryorg+272);
        fLoggingWindow.show_all();
	on_msg_level_changed();
    } else {
        fLoggingWindow.hide();
    }
}

void MainWindow::on_engine_toggled() {
    gx_engine::GxEngineState s;
    if (engine_mute_action->get_active()) {
	s = gx_engine::kEngineOff;
    } else if (engine_bypass_action->get_active()) {
	s = gx_engine::kEngineBypass;
    } else {
	s = gx_engine::kEngineOn;
    }
    engine.set_state(s);
}

void MainWindow::create_menu(Glib::RefPtr<Gtk::ActionGroup>& actiongroup, const GuiParameter& para) {
    uimanager = Gtk::UIManager::create();

    /*
    ** Menu actions
    */
    actiongroup->add(Gtk::Action::create("EngineMenu","_Engine"));
    jack_latency_menu_action = Gtk::Action::create("JackLatency","_Latency");
    actiongroup->add(jack_latency_menu_action);
    actiongroup->add(Gtk::Action::create("PresetsMenu","_Presets"));
    actiongroup->add(Gtk::Action::create("PresetListMenu","--"));
    actiongroup->add(Gtk::Action::create("PluginsMenu","P_lugins"));
    actiongroup->add(Gtk::Action::create("MonoPlugins","_Mono Plugins"));
    actiongroup->add(Gtk::Action::create("StereoPlugins","_Stereo Plugins"));
    actiongroup->add(Gtk::Action::create("TubeMenu","_Tube"));
    actiongroup->add(Gtk::Action::create("OptionsMenu","_Options"));
    actiongroup->add(Gtk::Action::create("SkinMenu", _("_Skin...")));
    actiongroup->add(Gtk::Action::create("AboutMenu","_About"));

    /*
    ** engine actions
    */
    jackserverconnection_action = Gtk::ToggleAction::create("JackServerConnection", "Jack Server _Connection");
    actiongroup->add(
	jackserverconnection_action, Gtk::AccelKey("<control>c"),
	sigc::mem_fun(*this, &MainWindow::jack_connection));

    jackports_action = Gtk::ToggleAction::create("JackPorts", "Jack _Ports");
    actiongroup->add(
	jackports_action, Gtk::AccelKey("<control>p"),
	sigc::mem_fun(*this, &MainWindow::on_portmap_activate));

    midicontroller_action = Gtk::ToggleAction::create("MidiController", "M_idi Controller");
    actiongroup->add(
	midicontroller_action, Gtk::AccelKey("<control>i"),
        sigc::mem_fun(*this, &MainWindow::on_miditable_toggle));

    engine_mute_action = Gtk::ToggleAction::create("EngineMute", "Engine _Mute");
    actiongroup->add(
	engine_mute_action, Gtk::AccelKey("space"),
	sigc::mem_fun(*this, &MainWindow::on_engine_toggled));

    engine_bypass_action = Gtk::ToggleAction::create("EngineBypass", "Engine _Bypass");
    actiongroup->add(
	engine_bypass_action, Gtk::AccelKey("b"),
	sigc::mem_fun(*this, &MainWindow::on_engine_toggled));

    actiongroup->add(Gtk::Action::create("Quit","_Quit"),Gtk::AccelKey("<Control>q"),sigc::ptr_fun(Gtk::Main::quit));

    /*
    ** actions to open other (sub)windows
    */
    presets_action = UiSwitchToggleAction::create(ui, *para.presets, "Presets","_Preset Selection");
    actiongroup->add(presets_action, Gtk::AccelKey("<control>p"), sigc::mem_fun(*this, &MainWindow::on_preset_action));

    show_plugin_bar_action = UiSwitchToggleAction::create(ui, *para.show_plugin_bar, "ShowPluginBar","Show _Plugin Bar","",true);
    actiongroup->add(show_plugin_bar_action, Gtk::AccelKey("<Control>b"), sigc::mem_fun(*this, &MainWindow::on_show_plugin_bar));

    show_rack_action = UiSwitchToggleAction::create(ui, *para.show_rack, "ShowRack","Show _Rack","",true);
    actiongroup->add(show_rack_action, Gtk::AccelKey("<Control>r"),sigc::mem_fun(*this, &MainWindow::on_show_rack));

    loggingbox_action = Gtk::ToggleAction::create("LoggingBox", _("Show _Logging Box"));
    actiongroup->add(
	loggingbox_action, Gtk::AccelKey("<control>l"),
        sigc::mem_fun(*this, &MainWindow::on_log_activate));

    live_play_action = Gtk::ToggleAction::create("Liveplay","_Live Display");
    actiongroup->add(live_play_action, Gtk::AccelKey("<Control>l"),sigc::mem_fun(*this, &MainWindow::on_live_play));

    meterbridge_action = Gtk::ToggleAction::create("Meterbridge", _("_Meterbridge"));
    actiongroup->add(
	meterbridge_action, Gtk::AccelKey("<alt>m"),
	sigc::bind(sigc::ptr_fun(gx_child_process::Meterbridge::start_stop),
		   sigc::ref(meterbridge_action), sigc::ref(jack)));

    /*
    ** rack actions
    */
    tuner_action = UiBoolToggleAction::create(ui, *para.tuner, "Tuner","_Tuner","",true);
    actiongroup->add(tuner_action,Gtk::AccelKey("<Control>t"),sigc::mem_fun(*this, &MainWindow::on_show_tuner));

    rack_config_action = Gtk::ToggleAction::create("RackConfig", "R_ack Configuration");
    actiongroup->add(rack_config_action, Gtk::AccelKey("<control>a"), sigc::mem_fun(*this, &MainWindow::on_rack_configuration));

    compress_action = Gtk::Action::create("Compress","_Compress all");
    actiongroup->add(compress_action,Gtk::AccelKey("<control>c"),sigc::mem_fun(*this, &MainWindow::on_compress_all));

    expand_action = Gtk::Action::create("Expand","E_xpand all");
    actiongroup->add(expand_action, Gtk::AccelKey("<control>e"),sigc::mem_fun(*this, &MainWindow::on_expand_all));

    // rack order radio buttons
    Gtk::RadioButtonGroup dg;
    rackv_action = UiSwitchRadioAction::create(
	ui, *para.order_rack_v, dg, "RackV", "Order Rack Vertically");
    rackv_action->property_value().set_value(0);
    actiongroup->add(rackv_action, Gtk::AccelKey("<Control>v"));
    // horizontal
    rackh_action = Gtk::RadioAction::create(dg, "RackH", "Order Rack Horizontally");
    rackh_action->property_value().set_value(1);
    actiongroup->add(rackh_action, Gtk::AccelKey("<Control>h"));
    // vertical
    rackh_action->set_active(true);
    rackv_action->signal_changed().connect(sigc::mem_fun(*this, &MainWindow::on_dir_changed));

    /*
    ** option actions
    */
    show_values_action = UiSwitchToggleAction::create(ui, *para.show_values, "ShowValues","_Show Values");
    actiongroup->add(show_values_action, Gtk::AccelKey("<Control>s"), sigc::mem_fun(*this, &MainWindow::on_show_values));

    tooltips_action = UiSwitchToggleAction::create(ui, *para.show_tooltips, "ShowTooltips", _("Show _Tooltips"));
    actiongroup->add(
	tooltips_action,
	sigc::compose(sigc::ptr_fun(set_tooltips),
		      sigc::mem_fun(tooltips_action.operator->(), &UiSwitchToggleAction::get_active)));

    midi_in_presets_action = UiSwitchToggleAction::create(ui, *para.midi_in_presets, "MidiInPresets", _("Include MIDI in _presets"));
    actiongroup->add(midi_in_presets_action);

    jackstartup_action = Gtk::ToggleAction::create("JackStartup", _("_Jack Startup Control"));
    actiongroup->add(
	jackstartup_action, Gtk::AccelKey("<control>j"),
	sigc::mem_fun(*this, &MainWindow::on_select_jack_control));

    actiongroup->add(Gtk::ToggleAction::create("ResetAll", _("Reset _All Parameters")),
		     sigc::mem_fun(pmap, &gx_engine::ParamMap::set_init_values));

    animations_action = Gtk::ToggleAction::create("Animations", _("Use Animations"),"",true);
    actiongroup->add(animations_action);

    /*
    ** Help and About
    */
    actiongroup->add(Gtk::Action::create("Help", _("_Help")),
		     Gtk::AccelKey("<control>h"),
		     sigc::ptr_fun(gx_show_help));
    actiongroup->add(Gtk::Action::create("About", _("_About")),
		     Gtk::AccelKey("<control>a"),
		     sigc::ptr_fun(gx_show_about));

    //
    // Add the actiongroup to the uimanager
    //
    uimanager->insert_action_group(actiongroup);
    uimanager->add_ui_from_file(options.get_builder_filepath("menudef.xml"));

    // add dynamic submenues
    add_skin_menu();
    add_latency_menu();
    amp_radio_menu.setup("<menubar><menu action=\"TubeMenu\">","</menu></menubar>",uimanager,actiongroup);
}

int get_current_workarea_height_from_desktop(GdkWindow *root) {
    // use "xprop -root" to view desktop properties
    GdkAtom actual_type, atom_cardinal;
    gint actual_format;
    gint num_items;
    int *ret_data_ptr;
    int idx;
    atom_cardinal = gdk_atom_intern("CARDINAL", false);
    if (!gdk_property_get(
	    root, gdk_atom_intern("_NET_CURRENT_DESKTOP", false), atom_cardinal,
	    0, 1, false, &actual_type, &actual_format, &num_items,
	    (guchar**)&ret_data_ptr)) {
	return -1;
    }
    idx = *ret_data_ptr * 4 + 3; // [x, y, width, height] * desktop_count
    g_free(ret_data_ptr);
    if (!gdk_property_get(
	    root, gdk_atom_intern("_NET_WORKAREA", false), atom_cardinal,
	    idx, 1, false, &actual_type, &actual_format, &num_items,
	    (guchar**)&ret_data_ptr)) {
	return -1;
    }
    if (idx >= num_items) {
	//??
	return -1;
    }
    int height = *ret_data_ptr;
    g_free(ret_data_ptr);
    return height;
}

int get_current_workarea_height() {
    // Helper fetching the current workarea (i.e. usable space) size
    GdkWindow *root = gdk_get_default_root_window();
    int height = get_current_workarea_height_from_desktop(root);
    if (height > 0) {
	return height;
    }
    int x, y, width, depth;
    gdk_window_get_geometry(root, &x, &y, &width, &height, &depth);
    return height;
}

void MainWindow::clear_box(Gtk::Container& box) {
    std::vector<Gtk::Widget*> l = box.get_children();
    for (std::vector<Gtk::Widget*>::iterator p = l.begin(); p != l.end(); ++p) {
	box.remove(**p);
    }
}

void MainWindow::make_icons() {
    Gtk::OffscreenWindow w;
    Glib::RefPtr<Gdk::Screen> screen = w.get_screen();
    Glib::RefPtr<Gdk::Colormap> rgba = screen->get_rgba_colormap();
    if (rgba) {
        w.set_colormap(rgba);
    }
    Gtk::VBox vb;
    w.add(vb);
    Glib::RefPtr<Gtk::SizeGroup> sz = Gtk::SizeGroup::create(Gtk::SIZE_GROUP_BOTH);
    std::vector<std::pair<PluginUI*,Gtk::Widget*> > l;
    for (std::map<std::string, PluginUI*>::iterator i = plugin_dict.begin(); i != plugin_dict.end(); ++i) {
        Gtk::Widget *r = RackBox::create_icon_widget(*i->second, options);
        r->hide();
        r->set_no_show_all(true);
        vb.add(*manage(r));
        sz->add_widget(*r);
	l.push_back(std::pair<PluginUI*,Gtk::Widget*>(i->second, r));
    }
    for (std::vector<std::pair<PluginUI*,Gtk::Widget*> >::iterator i = l.begin(); i != l.end(); ++i) {
        i->second->show();
        w.show_all();
	while (Gtk::Main::events_pending()) {
	    Gtk::Main::iteration();
	}
        //w.get_window()->process_updates(true);
	i->first->icon = w.get_pixbuf();
	if (i->first->toolitem) {
	    dynamic_cast<Gtk::Image*>(i->first->toolitem->get_child())->set(i->first->icon);
	}
        i->second->hide();
    }
}

void MainWindow::add_plugin(std::vector<PluginUI*> *p, const char *id, const Glib::ustring& fname, const Glib::ustring& tooltip) {
    gx_engine::Plugin *pl = engine.pluginlist.lookup_plugin(id);
    if (pl->pdef->flags & gx_engine::PGNI_UI_REG) {
	return;
    }
    pl->pdef->flags |= gx_engine::PGNI_UI_REG;
    PluginUI *pui = new PluginUI(*this, engine.pluginlist, id, fname, tooltip);
    ui.registerZone(&pui->plugin->box_visible, pui);
    ui.registerZone(&pui->plugin->position, pui);
    ui.registerZone(&pui->plugin->effect_post_pre, pui);
    p->push_back(pui);
}

void MainWindow::fill_pluginlist() {
    std::vector<PluginDesc*> l;
    std::vector<PluginUI*> *p;

    p = new std::vector<PluginUI*>;
    add_plugin(p, "low_highpass");
    add_plugin(p, "eqs");
    add_plugin(p, "IR");
    add_plugin(p, "biquad");
    add_plugin(p, "feedback");
    add_plugin(p, "amp.tonestack");
    add_plugin(p, "cab");
    add_plugin(p, "moog");
    add_plugin(p, "tonemodul");
    l.push_back(new PluginDesc("Tone control", p));

    p = new std::vector<PluginUI*>;
    add_plugin(p, "gx_distortion");
    add_plugin(p, "overdrive");
    add_plugin(p, "ampmodul");
    l.push_back(new PluginDesc("Distortion", p));

    p = new std::vector<PluginUI*>;
    add_plugin(p, "freeverb");
    add_plugin(p, "jconv");
    add_plugin(p, "stereoverb");
    add_plugin(p, "zita_rev1", "", "High Quality Reverb");
    l.push_back(new PluginDesc("Reverb", p));

    p = new std::vector<PluginUI*>;
    add_plugin(p, "echo");
    add_plugin(p, "delay");
    add_plugin(p, "stereodelay");
    add_plugin(p, "stereoecho");
    l.push_back(new PluginDesc("Echo / Delay", p));

    p = new std::vector<PluginUI*>;
    add_plugin(p, "tremolo");
    add_plugin(p, "phaser_mono");
    add_plugin(p, "chorus_mono");
    add_plugin(p, "flanger_mono");
    add_plugin(p, "chorus");
    add_plugin(p, "flanger");
    add_plugin(p, "phaser");
    //add_plugin(p_TYPE_STEREO, "univibe");
    l.push_back(new PluginDesc("Modulation", p));

    p = new std::vector<PluginUI*>;
    add_plugin(p, "crybaby");
    //add_plugin(p, PLUGIN_TYPE_MONO, "crybaby2");
    add_plugin(p, "compressor");
    l.push_back(new PluginDesc("Guitar Effects", p));

    p = new std::vector<PluginUI*>;
    add_plugin(p, "oscilloscope");
    add_plugin(p, "midi_out");
    l.push_back(new PluginDesc("Misc", p));

    p = new std::vector<PluginUI*>;
    UiBuilderImplNew builder(this, &boxbuilder, p);
    engine.pluginlist.append_rack(builder);
    if (p->size()) {
	l.push_back(new PluginDesc("External", p));
    }

    Glib::ustring ui_template =
	"<menubar><menu action=\"PluginsMenu\"><menu action=\"%1Plugins\"><menu action=\"%2\">"
	"<menuitem action=\"%3\"/>"
	"</menu></menu></menu></menubar>";
    int key = GDK_a;
    for (std::vector<PluginDesc*>::iterator i = l.begin(); i != l.end(); ++i) {
	int idx = 0;
	for (std::vector<PluginUI*>::iterator v = (*i)->plugins->begin(); v != (*i)->plugins->end(); ++v) {
	    PluginUI *pui = *v;
	    plugin_dict[pui->get_id()] = pui;
	    const char *tp = (pui->get_type() == PLUGIN_TYPE_MONO ? "Mono" : "Stereo");
	    Glib::ustring groupname = Glib::ustring::compose("PluginCategory_%1", (*i)->group);
	    Glib::ustring actionname = Glib::ustring::compose("Plugin_%1", pui->get_id());
	    pui->set_ui_merge_id(uimanager->add_ui_from_string(Glib::ustring::compose(ui_template, tp, groupname, actionname)));
	    if (idx++ == 0) {
		actiongroup->add(Gtk::Action::create(groupname, (*i)->group));
	    }
	    Glib::RefPtr<Gtk::ToggleAction> act = Gtk::ToggleAction::create(actionname, pui->get_name());
	    if (key <= GDK_z) {
		actiongroup->add(act, Gtk::AccelKey(gx_system::to_string((char)key)));
		++key;
	    } else {
		actiongroup->add(act);
	    }
	    pui->set_action(act);
	}
    }
    bool collapse = false;
    for (std::vector<PluginDesc*>::iterator i = l.begin(); i != l.end(); ++i) {
	Gtk::ToolItemGroup *gw = new Gtk::ToolItemGroup((*i)->group);
	gw->set_collapsed(collapse);
	collapse = true;
	for (std::vector<PluginUI*>::iterator v = (*i)->plugins->begin(); v != (*i)->plugins->end(); ++v) {
	    add_toolitem(**v, gw);
	}
	effects_toolpalette->add(*manage(gw));
	effects_toolpalette->set_exclusive(*gw, true);
	effects_toolpalette->set_expand(*gw, true);
	delete (*i)->plugins;
	delete *i;
    }
}

/* Update all user items reflecting zone z */
bool MainWindow::update_all_gui() {
    // the general Gui update handler
    gx_ui::GxUI::updateAllGuis();
    engine.check_module_lists();
    return true;
}

// start_jack() returns:
// 1:  success
// 0:  fail
// -1: no start command configured
int MainWindow::start_jack() {
    gx_engine::EnumParameter& jack_starter = pmap["ui.jack_starter_idx"].getEnum();
    string v_id = jack_starter.get_pair().value_id;
    if (v_id == "autostart") {
	return jack.gx_jack_connection(true, true) ? 1 : 0;
    }
    string cmd;
    if (v_id == "other") {
	cmd = pmap["ui.jack_starter"].getString().get_value();
	if (cmd.empty()) {
	    return -1;
	}
    } else if (v_id == "qjackctl") {
	cmd = "qjackctl --start";
    } else {
	assert(false);
    }
    gx_system::gx_system_call(cmd, true, true);
    for (int i = 0; i < 10; i++) {
	if (jack.gx_jack_connection(true,false)) {
	    return 1;
	}
	usleep(500000);
    }
    gx_system::gx_print_error(
	_("main"),
	string(_("I really tried to get jack up and running, sorry ... ")));
    return 0;
}

bool MainWindow::connect_jack(bool v) {
    if (jack.gx_jack_connection(v, false)) {
	return true;
    }
    if (!v) {
	gx_system::gx_print_error(_("main"), _("can't disconnect jack"));
	return false;
    }
    bool ask = pmap["ui.ask_for_jack_starter"].getSwitch().get();
    if (!ask) {
	switch (start_jack()) {
	case 1: return true;   // connected
	case -1: return false; // no starter, do nothing
	default: break;        // failed, ask user
	}
    }
    if (!gx_gui::gx_start_jack_dialog(gx_head_icon)) {
	gx_system::gx_print_warning(_("main"), string(_("Ignoring jackd ...")));
	return false;
    }
    return start_jack() == 1;
}

void MainWindow::on_jack_client_changed() {
    if (!window) {
	return;
    }

    bool v = (jack.client != 0);
    if (!v) {
        gx_child_process::Meterbridge::stop(); //FIXME
    }
    jackserverconnection_action->set_active(v);
    Glib::ustring s = "Guitarix: ";
    if (v) {
	s += jack.get_instancename();
    } else {
	s += "("+jack.get_instancename()+")";
    }
    window->set_title(s);
    jack_latency_menu_action->set_sensitive(v);
    engine_mute_action->set_sensitive(v);
    engine_bypass_action->set_sensitive(v);
    status_image->set_sensitive(v);
    if (!v) {
	jackd_image->set(pixbuf_jack_disconnected);
    } else {
	jackd_image->set(pixbuf_jack_connected);
    }
}

void MainWindow::on_engine_state_change(gx_engine::GxEngineState state) {
    switch (state) {
    case gx_engine::kEngineOff:
	engine_mute_action->set_active(true);
	status_image->set(pixbuf_off);
	break;
    case gx_engine::kEngineOn:
	engine_mute_action->set_active(false);
	engine_bypass_action->set_active(false);
	status_image->set(pixbuf_on);
	break;
    case gx_engine::kEngineBypass:
	engine_mute_action->set_active(false);
	engine_bypass_action->set_active(true);
	status_image->set(pixbuf_bypass);
	break;
    }
}

void MainWindow::do_program_change(int pgm) {
    Glib::ustring bank = gx_settings.get_current_bank();
    bool in_preset = !bank.empty();
    gx_system::PresetFile *f;
    if (in_preset) {
	f = gx_settings.banks.get_file(bank);
	in_preset = pgm < f->size();
    }
    if (in_preset) {
	gx_settings.load_preset(f, f->get_name(pgm));
	if (engine.get_state() == gx_engine::kEngineBypass) {
	    engine.set_state(gx_engine::kEngineOn);
	}
    } else if (engine.get_state() == gx_engine::kEngineOn) {
	engine.set_state(gx_engine::kEngineBypass);
    }
}

void MainWindow::set_tuning(Gxw::RackTuner& tuner) {
    static struct TuningTab {
	const char *name;
	const char* key;
	bool flat;
	int notes[6];
    } tuning_tab[] = {
	{ "Standard",    "E",  false, {40, 45, 50, 55, 59, 64}},
	{ "Standard/Es", "Es", true,  {39, 44, 49, 54, 58, 63}},
	{ "Open E",      "E",  false, {40, 47, 52, 56, 59, 64}},
    };
    int mode = tuner_tuning->get_value();
    tuner.clear_notes();
    if (mode > 0) {
	tuner.set_display_flat(tuning_tab[mode-1].flat);
	for (int i = 0; i < 6; ++i) {
	    tuner.push_note(tuning_tab[mode-1].notes[i]);
	}
    } else {
	tuner.set_display_flat(false);
    }
}

void MainWindow::setup_tuner(Gxw::RackTuner& tuner) {
    tuner.signal_frequency_poll().connect(
	sigc::compose(
	    sigc::mem_fun(tuner, &Gxw::RackTuner::set_freq),
	    sigc::mem_fun(engine.tuner, &gx_engine::TunerAdapter::get_freq)));
    tuner_mode->signal_value_changed().connect(
	sigc::compose(
	    sigc::mem_fun(tuner, &Gxw::RackTuner::set_streaming),
	    sigc::mem_fun(*tuner_mode, &Gxw::Selector::get_value)));
    tuner_reference_pitch->signal_value_changed().connect(
	sigc::compose(
	    sigc::mem_fun(tuner, &Gxw::RackTuner::set_reference_pitch),
	    sigc::mem_fun(*tuner_reference_pitch, &Gxw::Wheel::get_value)));
    tuner_tuning->signal_value_changed().connect(
	sigc::bind(sigc::mem_fun(*this, &MainWindow::set_tuning), sigc::ref(tuner)));
}

bool MainWindow::on_toggle_mute(GdkEventButton* ev) {
    if (ev->type == GDK_BUTTON_PRESS && ev->button == 1) {
	if (engine.get_state() == gx_engine::kEngineOff) {
	    engine.set_state(gx_engine::kEngineOn);
	} else {
	    engine.set_state(gx_engine::kEngineOff);
	}
    }
    return true;
}

void MainWindow::on_msg_level_changed() {
    //FIXME use better icons...
    switch (fLoggingWindow.get_unseen_msg_level()) {
    case gx_system::kWarning: logstate_image->set(pixbuf_log_yellow); break;
    case gx_system::kError:   logstate_image->set(pixbuf_log_red); break;
    default:                  logstate_image->set(pixbuf_log_grey); break;
    }
}

static void toggle_action(Glib::RefPtr<Gtk::ToggleAction> act) {
    act->set_active(!act->get_active());
}

void MainWindow::on_ampdetail_switch(bool compress) {
    if (compress) {
	ampdetail_normal->hide();
	ampdetail_mini->show();
    } else {
	ampdetail_mini->hide();
	ampdetail_normal->show();
    }
    pmap["ui.mp_s_h"].getBool().set(compress);
}

/****************************************************************
 ** oscilloscope handling
 */

void MainWindow::on_show_oscilloscope(bool v) {
    if (v) {
	// FIXME G_PRIORITY_DEFAULT_IDLE??
	Glib::signal_timeout().connect(
	    sigc::mem_fun(*this, &MainWindow::on_refresh_oscilloscope), 60); 
    }
}

void MainWindow::set_waveview_buffer(unsigned int size) {
    fWaveView.set_frame(engine.oscilloscope.get_buffer(), size);
}

void MainWindow::on_oscilloscope_post_pre(int post_pre) {
    if (post_pre) {
        fWaveView.set_multiplicator(150.,250.);
    } else {
        fWaveView.set_multiplicator(20.,60.);
    }
}

int MainWindow::on_oscilloscope_activate(bool start) {
    if (!start) {
	engine.oscilloscope.clear_buffer();
	fWaveView.queue_draw();
    }
    return 0;
}

bool MainWindow::on_refresh_oscilloscope() {
    static struct  {
        int load, frames;
        jack_nframes_t bsize;
        bool rt;
    } oc;
    int load = static_cast<int>(round(jack.get_jcpu_load()));
    if (!oc.bsize || oc.load != load) {
        oc.load = load;
        fWaveView.set_text(
            (boost::format(_("dsp load  %1% %%")) % oc.load).str().c_str(),
            Gtk::CORNER_TOP_LEFT);
    }
    int frames = jack.get_time_is()/100000;
    if (!oc.bsize || oc.frames != frames) {
        oc.frames = frames;
        fWaveView.set_text(
            (boost::format(_("ht frames %1%")) % oc.frames).str().c_str(),
            Gtk::CORNER_BOTTOM_LEFT);
    }
    bool is_rt = jack.get_is_rt();
    if (!oc.bsize || oc.rt != is_rt) {
        oc.rt = is_rt;
        fWaveView.set_text(
            oc.rt ? _("RT mode  yes ") : _("RT mode  <span color=\"#cc1a1a\">NO</span>"),
            Gtk::CORNER_BOTTOM_RIGHT);
    }
    if (!oc.bsize || oc.bsize != jack.get_jack_bs()) {
        oc.bsize = jack.get_jack_bs();
        fWaveView.set_text(
            (boost::format(_("latency    %1%")) % oc.bsize).str().c_str(),
            Gtk::CORNER_TOP_RIGHT);
    }
    fWaveView.queue_draw();
    return engine.oscilloscope.plugin.box_visible;
}

bool MainWindow::refresh_meter_level() {
    if (!jack.client) {
	return true;
    }
    const float falloff = gx_gui::guivar.meter_falloff *
	gx_gui::guivar.meter_display_timeout * 0.001;

    // Note: removed RMS calculation, we will only focus on max peaks
    static float old_peak_db[sizeof(fastmeter)/sizeof(fastmeter[0])] = {-INFINITY, -INFINITY};

    // fill up from engine buffers
    gx_engine::MaxLevel& m = engine.maxlevel;
    for (unsigned int c = 0; c < sizeof(fastmeter)/sizeof(fastmeter[0]); c++) {
	// update meters (consider falloff as well)
	// calculate peak dB and translate into meter
	float peak_db = -INFINITY;
	if (m.get(c) > 0) {
	    peak_db = gx_threads::power2db(m.get(c));
	}
	// retrieve old meter value and consider falloff
	if (peak_db < old_peak_db[c]) {
	    peak_db = max(peak_db, old_peak_db[c] - falloff);
	}
	fastmeter[c]->set(log_meter(peak_db));
	old_peak_db[c] = peak_db;
    }
    m.reset();
    return true;
}

void MainWindow::cab_conv_restart() {
    if (!cab_conv_conn.connected()) {
	cab_conv_conn = Glib::signal_timeout().connect(
	    sigc::bind_return(
		sigc::bind(
		    sigc::mem_fun(engine.cabinet, &gx_engine::CabinetConvolver::start),
		    false),
		false),
	    0, Glib::PRIORITY_HIGH_IDLE + 10);
    } else {
        gx_system::gx_print_warning(_("Cabinet Loading"), string(_(" cab thread is bussy")));
    }
}

void MainWindow::contrast_conv_restart() {
    if (!contrast_conv_conn.connected()) {
	contrast_conv_conn = Glib::signal_timeout().connect(
	    sigc::bind_return(
		sigc::bind(
		    sigc::mem_fun(engine.contrast, &gx_engine::ContrastConvolver::start),
		    false),
		false),
	    0, Glib::PRIORITY_HIGH_IDLE + 10);
    } else {
        gx_system::gx_print_warning(_("Presence Loading"), string(_(" presence thread is bussy")));
    }
}

bool MainWindow::check_cab_state() {
    if (engine.cabinet.plugin.on_off) {
	if (engine.cabinet.cabinet_changed()) {
            engine.cabinet.conv_stop();
            cab_conv_restart();
	} else if (engine.cabinet.sum_changed()) {
	    engine.cabinet.conv_update();
        }
    }
    if (engine.contrast.plugin.on_off) {
        if (engine.contrast.sum_changed()) {
            engine.contrast.conv_stop();
            contrast_conv_restart();
        }
    }
    return true;
}

bool MainWindow::survive_jack_shutdown() {
    // return if jack is not down
    if (gx_system::gx_system_call("pgrep jackd", true) == SYSTEM_OK) {
        if (jack.is_jack_down()) {
        sleep(2);
	    jack.set_jack_down(false);
	}
	// let's make sure we get out of here
	gx_system::gx_print_warning("Jack Shutdown",
				    _("jack has bumped us out!!   "));
	jackserverconnection_action->set_active(true);
	// run only one time whem jackd is running
	return false;
    } else if (!jack.is_jack_down()) {
        // refresh some stuff. Note that it can be executed
        // more than once, no harm here
        jackserverconnection_action->set_active(false);
        jack.set_jack_down(true);
	gx_system::gx_print_error("Jack Shutdown",
				  _("jack has bumped us out!!   "));
    }
    // run as long jackd is down
    return true;
}

void MainWindow::gx_jack_is_down() {
    jackserverconnection_action->set_active(false);
    Glib::signal_timeout().connect(
	sigc::mem_fun(*this, &MainWindow::survive_jack_shutdown),
	200, Glib::PRIORITY_LOW);
}

#ifdef HAVE_JACK_SESSION
void MainWindow::jack_session_event() {
    const char *statefile = "gx_head.state";
    jack_session_event_t *event = jack.get_last_session_event();
    set_in_session();
    gx_settings.set_statefilename(string(event->session_dir) + statefile);
    gx_settings.save_to_state();

#ifndef NDEBUG
    string cmd(options.get_path_to_program());
#else
    string cmd("guitarix");
#endif
    cmd += " -U ";
    cmd += event->client_uuid;
    cmd += " -A ";
    cmd += jack.get_uuid_insert();
    cmd += " -f ${SESSION_DIR}";
    cmd += statefile; // no space after SESSION_DIR
    event->command_line = strdup(cmd.c_str());

    JackSessionEventType tp = event->type;
    if (jack.return_last_session_event() == 0) {
	if (tp == JackSessionSaveAndQuit) {
	    gx_system::GxExit::get_instance().exit_program("** session exit **");
	}
    }
}

void MainWindow::jack_session_event_ins() {
    jack_session_event_t *event = jack.get_last_session_event_ins();
    set_in_session();
    event->command_line = strdup("true ${SESSION_DIR}");
    JackSessionEventType tp = event->type;
    if (jack.return_last_session_event_ins() == 0) {
	if (tp == JackSessionSaveAndQuit) {
	    gx_system::GxExit::get_instance().exit_program("** session exit **");
	}
    }
}
#endif

void MainWindow::set_in_session() {
    if (!in_session) {
	in_session = true;
	// it seems in a session we generally don't know
	// where to save and from where to recall data
	// it's all controlled by the session manager
	gx_settings.disable_autosave(true);
    }
}

void MainWindow::systray_menu(guint button, guint32 activate_time) {
    Gtk::Menu *menu = dynamic_cast<Gtk::MenuItem*>(uimanager->get_widget("/menubar/EngineMenu"))->get_submenu();
    menu->popup(2, gtk_get_current_event_time());
}

void MainWindow::overload_status_changed() {
    switch (engine.midiaudiobuffer.jack_load_status()) {
    case gx_engine::MidiAudioBuffer::load_off:
	status_icon->set(gx_head_icon);
	break;
    case gx_engine::MidiAudioBuffer::load_normal:
	if (engine.midiaudiobuffer.get_midistat()) {
	    status_icon->set(gx_head_midi);
	} else {
	    status_icon->set(gx_head_icon);
	}
	break;
    case gx_engine::MidiAudioBuffer::load_over:
	status_icon->set(gx_head_warn);
	break;
    default:
	assert(false);
    }
}

bool MainWindow::on_window_state_changed(GdkEventWindowState* event) {
    if (event->changed_mask & event->new_window_state & (Gdk::WINDOW_STATE_ICONIFIED|Gdk::WINDOW_STATE_WITHDRAWN)) {
	window->get_window()->get_root_origin(GuiParameter::mainwin_x, GuiParameter::mainwin_y);
    }
    return false;
}

void MainWindow::hide_extended_settings() {
    if (!is_visible ||
	(window->get_window()->get_state()
	 & (Gdk::WINDOW_STATE_ICONIFIED|Gdk::WINDOW_STATE_WITHDRAWN))) {
        window->move(GuiParameter::mainwin_x, GuiParameter::mainwin_y);
        window->present();
    } else {
        window->hide();
        //window->iconify();
    }
}

void MainWindow::run() {
    window->show();
    Gtk::Main::run();
}

bool MainWindow::on_meter_button_release(GdkEventButton* ev) {
    if (ev->button == 1) {
        for (unsigned int i = 0; i < sizeof(fastmeter)/sizeof(fastmeter[0]); i++) {
            fastmeter[i]->clear();
        }
        return true;
    }
    return false;
}

MainWindow::MainWindow(gx_engine::GxEngine& engine_, gx_system::CmdlineOptions& options_, gx_engine::ParamMap& pmap_)
    : sigc::trackable(),
      ui(),
      bld(),
      window_height(0),
      freezer(),
      plugin_dict(ui),
      oldpos(0),
      scrl_size_x(-1),
      scrl_size_y(-1),
      monorackcontainer(PLUGIN_TYPE_MONO, *this),
      stereorackcontainer(PLUGIN_TYPE_STEREO, *this),
      pre_act(false),
      is_visible(false),
      drag_icon(0),
      actiongroup(),
      preset_list_menu_bank(),
      preset_list_merge_id(0),
      preset_list_actiongroup(),
      select_preset_action(),
      uimanager(),
      options(options_),
      pmap(pmap_),
      engine(engine_),
      jack(engine),
      gx_settings(options, jack, engine.convolver, gx_engine::midi_std_ctr, gx_engine::controller_map, engine, pmap_),
      live_play(),
      preset_window(),
      fWaveView(),
      convolver_filename_label(),
      gx_head_icon(Gdk::Pixbuf::create_from_file(options.get_pixmap_filepath("gx_head.png"))),
      boxbuilder(engine_, pmap_, fWaveView, convolver_filename_label, ui, gx_head_icon),
      portmap_window(0),
      accel_group(),
      skin_changed(&ui, &skin),
      select_jack_control(0),
      fLoggingWindow(),
      amp_radio_menu(&ui, pmap["tube.select"].getUInt()),
      pixbuf_on(Gdk::Pixbuf::create_from_file(options.get_pixmap_filepath("gx_on.png"))),
      pixbuf_off(Gdk::Pixbuf::create_from_file(options.get_pixmap_filepath("gx_off.png"))),
      pixbuf_bypass(Gdk::Pixbuf::create_from_file(options.get_pixmap_filepath("gx_bypass.png"))),
      pixbuf_jack_connected(Gdk::Pixbuf::create_from_file(options.get_pixmap_filepath("jackd_on.png"))),
      pixbuf_jack_disconnected(Gdk::Pixbuf::create_from_file(options.get_pixmap_filepath("jackd_off.png"))),
      pixbuf_log_grey(Gdk::Pixbuf::create_from_file(options.get_pixmap_filepath("gx_log_grey.png"))),
      pixbuf_log_yellow(Gdk::Pixbuf::create_from_file(options.get_pixmap_filepath("gx_log_yellow.png"))),
      pixbuf_log_red(Gdk::Pixbuf::create_from_file(options.get_pixmap_filepath("gx_log_red.png"))),
      mute_changed(&ui, &pmap.reg_par("engine.mute", "Mute", 0, false)->get_value()),
      ampdetail_sh(&ui, &pmap.reg_non_midi_par("ui.mp_s_h", (bool*)0, false)->get_value()),
      contrast_conv_conn(),
      cab_conv_conn(),
      report_xrun(jack),
      in_session(false),
      status_icon(Gtk::StatusIcon::create(gx_head_icon)),
      gx_head_midi(Gdk::Pixbuf::create_from_file(options.get_pixmap_filepath("gx_head-midi.png"))),
      gx_head_warn(Gdk::Pixbuf::create_from_file(options.get_pixmap_filepath("gx_head-warn.png"))) {
    engine.set_jack(&jack);
    jack.xrun.connect(sigc::mem_fun(report_xrun, &gx_gui::ReportXrun::run));
#ifdef HAVE_JACK_SESSION
    jack.session.connect(sigc::mem_fun(*this, &MainWindow::jack_session_event));
    jack.session_ins.connect(sigc::mem_fun(*this, &MainWindow::jack_session_event_ins));
    if (!options.get_jack_uuid().empty()) {
	set_in_session();
    }
#endif
    jack.shutdown.connect(sigc::mem_fun(*this, &MainWindow::gx_jack_is_down));

    /*
    ** max window size is work area reduce by arbitrary amount to
    ** make it visually more appealing and to account for the unknown
    ** frame size (difficult to find out, would have to query the
    ** window mananger)
    */
    //window_height = std::min(600, get_current_workarea_height()-50);
    window_height = get_current_workarea_height() - 80;

    //self.pmap = ParamMap(param_fname)
    //gtk_rc_parse(options.get_style_filepath(style_fname));
    //gtk.rc_parse_string(styledef % style_dir);


    GuiParameter para(pmap);
    const char *id_list[] = { "MainWindow", "amp_background:ampbox", "bank_liststore", "target_liststore", "bank_combo_liststore", 0 };
    bld = gx_gui::GxBuilder::create_from_file(options_.get_builder_filepath("mainpanel.glade"), &ui, id_list);

    load_widget_pointers();
    int width, height;
    window->get_default_size(width, height);
    window->set_default_size(width, window_height);
    rackcontainer->set_homogeneous(true); // setting it in glade is awkward to use with glade tool

    window->signal_window_state_event().connect(
	sigc::mem_fun(*this, &MainWindow::on_window_state_changed));
    window->signal_delete_event().connect(
	sigc::bind_return(
	    sigc::hide(
		sigc::ptr_fun(Gtk::Main::quit)),
	    true));

    for (unsigned int i = 0; i < sizeof(fastmeter)/sizeof(fastmeter[0]); ++i) {
        fastmeter[i]->signal_button_release_event().connect(
            sigc::mem_fun(*this, &MainWindow::on_meter_button_release));
        fastmeter[i]->set_tooltip_text(_("gx_head output"));
    }

    // remove child labels from boxes used for demo:
    clear_box(*monocontainer);
    clear_box(*stereorackcontainerH);
    clear_box(*stereorackcontainerV);

    // create menu
    actiongroup = Gtk::ActionGroup::create("Main");
    preset_window = new PresetWindow(pmap, bld, gx_settings, options, actiongroup);
    create_menu(actiongroup, para);
    Gtk::Widget *menubar = uimanager->get_widget("/menubar");
    accel_group = uimanager->get_accel_group(); //window->get_accel_group(); //FIXME
    preset_window->set_accel_group(accel_group);
    menubox->pack_start(*menubar);
    window->add_accel_group(uimanager->get_accel_group());

    status_image->set(pixbuf_on);
    gx_engine::BoolParameter& par = pmap["engine.mute"].getBool();
    par.setSavable(false);
    gx_gui::connect_midi_controller(GTK_WIDGET(status_image->get_parent()->gobj()), &par.get_value());
    status_image->get_parent()->signal_button_press_event().connect(
	sigc::mem_fun(*this, &MainWindow::on_toggle_mute));

    jackd_image->set(pixbuf_jack_disconnected);
    jackd_image->get_parent()->signal_button_press_event().connect(
	sigc::bind_return(
	    sigc::group(
		sigc::ptr_fun(toggle_action),
		jackserverconnection_action),
	    true));

    fLoggingWindow.set_transient_for(*window);
    fLoggingWindow.set_icon(gx_head_icon);
    fLoggingWindow.signal_msg_level_changed().connect(
	sigc::mem_fun(*this, &MainWindow::on_msg_level_changed));
    fLoggingWindow.signal_hide().connect(
	sigc::bind(
	    sigc::mem_fun(loggingbox_action.operator->(), &Gtk::ToggleAction::set_active),
	    false));
    on_msg_level_changed();
    logstate_image->get_parent()->signal_button_press_event().connect(
	sigc::bind_return(
	    sigc::group(
		sigc::ptr_fun(toggle_action),
		loggingbox_action),
	    true));

    ampdetail_compress->signal_clicked().connect(
	sigc::bind(sigc::mem_fun(*this, &MainWindow::on_ampdetail_switch), true));
    ampdetail_expand->signal_clicked().connect(
	sigc::bind(sigc::mem_fun(*this, &MainWindow::on_ampdetail_switch), false));
    ampdetail_sh.changed.connect(
	sigc::mem_fun(*this, &MainWindow::on_ampdetail_switch));

    engine.oscilloscope.post_pre_signal.changed.connect(
	sigc::mem_fun(*this, &MainWindow::on_oscilloscope_post_pre));
    engine.oscilloscope.visible.changed.connect(
	sigc::mem_fun(*this, &MainWindow::on_show_oscilloscope));
    engine.oscilloscope.activation.connect(
	sigc::mem_fun(*this, &MainWindow::on_oscilloscope_activate));
    engine.oscilloscope.size_change.connect(
	sigc::mem_fun(*this, &MainWindow::set_waveview_buffer));

    Glib::signal_timeout().connect(
	sigc::mem_fun(*this, &MainWindow::refresh_meter_level), gx_gui::guivar.meter_display_timeout);
    Glib::signal_timeout().connect(
	sigc::mem_fun(*this, &MainWindow::check_cab_state), 200);
	
    gx_settings.signal_selection_changed().connect(
	sigc::mem_fun(*this, &MainWindow::show_selected_preset));

    // create rack
    stereorackcontainerH->pack_start(stereorackcontainer, Gtk::PACK_EXPAND_WIDGET);
    monocontainer->pack_start(monorackcontainer, Gtk::PACK_EXPAND_WIDGET);

    // connect signal
    window->signal_configure_event().connect_notify(sigc::mem_fun(*this, &MainWindow::on_configure_event));
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(show_rack_button->gobj()), GTK_ACTION(show_rack_action->gobj()));
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(config_mode_button->gobj()), GTK_ACTION(rack_config_action->gobj()));
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(liveplay_button->gobj()),GTK_ACTION(live_play_action->gobj()));
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(tuner_button->gobj()),GTK_ACTION(tuner_action->gobj()));
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(effects_button->gobj()), GTK_ACTION(show_plugin_bar_action->gobj()));
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(presets_button->gobj()), GTK_ACTION(presets_action->gobj()));
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(compress_button->gobj()), GTK_ACTION(compress_action->gobj()));
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(expand_button->gobj()), GTK_ACTION(expand_action->gobj()));

    setup_tuner(*racktuner);
    tuner_on_off->signal_toggled().connect(
	sigc::compose(
	    sigc::mem_fun(*racktuner, &Gxw::RackTuner::set_sensitive),
	    sigc::mem_fun(*tuner_on_off, &Gxw::Switch::get_active)));
    racktuner->signal_poll_status_changed().connect(
	sigc::mem_fun(engine.tuner, &gx_engine::TunerAdapter::used_for_display));

    livetuner_action = UiBoolToggleAction::create(ui, *para.ui_racktuner, "LiveTuner", "??", "", false);
    live_play = new Liveplay(options, engine, gx_settings, options.get_builder_filepath("mainpanel.glade"), actiongroup, livetuner_action);
    setup_tuner(live_play->get_tuner());
    live_play->get_tuner().signal_poll_status_changed().connect(
	sigc::mem_fun(engine.tuner, &gx_engine::TunerAdapter::used_for_livedisplay));

    tuner_action->set_active(false);
    show_plugin_bar_action->set_active(false);
    if (rackv_action->get_current_value()) {
	// horizontally
	stereorackcontainerV->hide();
    } else {
	stereorackcontainerH->hide();
    }
    std::vector<Gtk::TargetEntry> listTargets;
    listTargets.push_back(Gtk::TargetEntry("application/x-guitarix-mono", Gtk::TARGET_SAME_APP, 1));
    listTargets.push_back(Gtk::TargetEntry("application/x-guitarix-stereo", Gtk::TARGET_SAME_APP, 2));
    effects_toolpalette->drag_dest_set(listTargets, Gtk::DEST_DEFAULT_ALL, Gdk::ACTION_MOVE);
    effects_toolpalette->signal_drag_data_received().connect(sigc::mem_fun(*this, &MainWindow::on_tp_drag_data_received));

    /*---------------- status icon ----------------*/
    window->set_icon(gx_head_icon);
    status_icon->signal_activate().connect(
	sigc::mem_fun(*this, &MainWindow::hide_extended_settings));
    status_icon->signal_popup_menu().connect(
	sigc::mem_fun(*this, &MainWindow::systray_menu));
    engine.midiaudiobuffer.signal_jack_load_change().connect(
	sigc::mem_fun(*this, &MainWindow::overload_status_changed));

    window->signal_visibility_notify_event().connect(
	sigc::mem_fun(*this, &MainWindow::on_visibility_notify));
    jack.signal_buffersize_change().connect(
	sigc::mem_fun(*this, &MainWindow::set_latency));
    engine.signal_state_change().connect(
	sigc::mem_fun(*this, &MainWindow::on_engine_state_change));
    jack.signal_client_change().connect(
	sigc::mem_fun(*this, &MainWindow::on_jack_client_changed));
    gx_engine::controller_map.signal_new_program().connect(
	sigc::mem_fun(*this, &MainWindow::do_program_change));
    gx_settings.signal_selection_changed().connect(
	sigc::mem_fun(monorackcontainer, &RackContainer::check_order));
    gx_settings.signal_selection_changed().connect(
	sigc::mem_fun(stereorackcontainer, &RackContainer::check_order));

    fill_pluginlist();
    plugin_dict["gx_distortion"]->shortname = _("Distortion");
    PluginUI *mainamp_plugin = new PluginUI(*this, engine.pluginlist, "ampstack");
    plugin_dict["ampstack"] = mainamp_plugin;
    add_rackbox_internal(*mainamp_plugin, 0, 0, false, -1, false, amp_background);
    effects_toolpalette->show_all();

    pmap.set_init_values();
    gx_ui::GxUI::updateAllGuis(true);

    // state must be loaded before starting jack because connect_jack() uses
    // some settings. If the jack client name changes (from the predefined value)
    // on connect the jack client-change signal will trigger the load of another
    // state file, which means that the jack starter options are read from the
    // standard state file (gx_head_rc or similar if -n is used)
    gx_settings.loadstate();
    if (!connect_jack(true)) {
	jack.signal_client_change()();
    }
	
    if (!jack.is_jack_exit()) {
	engine.clear_stateflag(gx_engine::ModuleSequencer::SF_INITIALIZING);
    }
    set_latency();

    // we set the skin at this late point to avoid calling make_icons more
    // than once
    if (skin_action->get_current_value() != skin) {
	skin_action->set_current_value(skin); // will call set_new_skin()
    } else {
	set_new_skin(skin);
    }
    skin_changed.changed.connect(
	sigc::mem_fun(skin_action.operator->(), &Gtk::RadioAction::set_current_value));

    // set window position (make this optional??)
    if (para.mainwin_height > 0) {
	window->set_default_size(-1, para.mainwin_height);
    }
    if (para.mainwin_x > 0) {
	window->move(para.mainwin_x, para.mainwin_y);
    }

    window->show();

    Glib::signal_timeout().connect(
	sigc::mem_fun(*this, &MainWindow::update_all_gui), 40);
}

MainWindow::~MainWindow() {
    engine.start_ramp_down();

    window->get_size(GuiParameter::mainwin_width, GuiParameter::mainwin_height);
    window->get_window()->get_root_origin(GuiParameter::mainwin_x, GuiParameter::mainwin_y);
    delete live_play;
    delete preset_window;
    delete window;
    window = 0;

    engine.wait_ramp_down_finished();
    engine.set_stateflag(gx_engine::ModuleSequencer::SF_INITIALIZING);
    engine.set_jack(0);
}
