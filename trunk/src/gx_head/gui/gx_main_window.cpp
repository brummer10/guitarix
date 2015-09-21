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
#include <gtkmm/accelmap.h>
#include "jsonrpc.h"

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
      ok_button(Gtk::Stock::OK),
      buttonbox(),
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
    set_border_width(4);

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
    for (int i = 0; i < GxLogger::kMessageTypeCount; i++) {
	tags[i] = buffer->create_tag(tagdefs[i].tagname);
	tags[i]->property_foreground() = tagdefs[i].tag_color;
    }

    box.add(scrollbox);
    box.pack_end(buttonbox, Gtk::PACK_SHRINK);
    buttonbox.set_layout(Gtk::BUTTONBOX_END);
    buttonbox.add(ok_button);
    buttonbox.set_border_width(4);
    ok_button.set_can_default();
    ok_button.grab_default();
    ok_button.signal_clicked().connect(sigc::mem_fun(this, &TextLoggingBox::hide));
    //signal_activate().connect(sigc::mem_fun(this, &TextLoggingBox::hide));
    scrollbox.add(tbox);
    tbox.set_size_request(-1, 50);
    box.show_all();
    GxLogger::get_logger().signal_message().connect(
	sigc::mem_fun(*this, &TextLoggingBox::show_msg));
    GxLogger::get_logger().unplug_queue();
}

TextLoggingBox::~TextLoggingBox() {
}

bool TextLoggingBox::on_key_press_event(GdkEventKey *event) {
    if (event->keyval == GDK_KEY_Escape && (event->state & Gtk::AccelGroup::get_default_mod_mask()) == 0) {
	hide();
	return true;
    }
    return Gtk::Window::on_key_press_event(event);
}

void TextLoggingBox::on_show() {
    highest_unseen_msg_level = GxLogger::kMessageTypeCount;
    Gtk::Window::on_show();
}

void TextLoggingBox::on_hide() {
    highest_unseen_msg_level = -1;
    Gtk::Window::on_hide();
}

void TextLoggingBox::show_msg(string msgbuf, GxLogger::MsgType msgtype, bool plugged) {
    assert(0 <= msgtype && msgtype < GxLogger::kMessageTypeCount);

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

#if false // unused
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
#endif

/****************************************************************
 ** GxUiRadioMenu
 ** adds the values of an EnumParameter as Gtk::RadioMenuItem's
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

GxUiRadioMenu::GxUiRadioMenu(gx_engine::GxMachineBase& machine_, const std::string& id_)
    : machine(machine_),
      id(id_) {
    machine.signal_parameter_value<int>(id).connect(
	sigc::mem_fun(this, &GxUiRadioMenu::set_value));
}

void GxUiRadioMenu::setup(const Glib::ustring& prefix, const Glib::ustring& postfix,
			  Glib::RefPtr<Gtk::UIManager>& uimanager, Glib::RefPtr<Gtk::ActionGroup>& actiongroup) {
    int i, c;
    const value_pair *p;
    TubeKeys next_key;
    Glib::ustring s = prefix;
    Gtk::RadioButtonGroup group;
    gx_engine::IntParameter& param = machine.get_parameter(id).getInt();
    for (p = param.getValueNames(), i = 0; p->value_id; p++, i++) {
	c = next_key();
	if (c == 0) {
	    s += "<separator/>";
	    c = next_key();
	}
	Glib::ustring actname = Glib::ustring::compose("Enum_%1.%2", param.id(), p->value_id);
	s += Glib::ustring::compose("<menuitem action=\"%1\"/>", actname);
	Glib::RefPtr<Gtk::RadioAction> act = Gtk::RadioAction::create(group, actname, param.value_label(*p));
	act->property_value().set_value(static_cast<int>(param.getLowerAsFloat())+i);
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
    //fprintf(stderr, "%s  \n", p->value_id);
    }
    s.append(postfix);
    uimanager->add_ui_from_string(s);
}

void GxUiRadioMenu::set_value(unsigned int v) {
    action->set_current_value(v);
}

void GxUiRadioMenu::on_changed(Glib::RefPtr<Gtk::RadioAction> act) {
    machine.set_parameter_value(id, act->get_current_value());
}


/****************************************************************
 ** class Freezer
 */

Freezer::Freezer()
    : window(0), tag(), need_thaw(false), size_x(-1), size_y(-1) {
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
	need_thaw = true;
	win->freeze_updates();
    }
}

void Freezer::set_slot(sigc::slot<void> w) {
    if (size_x == -1) {
	w();
    } else {
	work = w;
    }
}

void Freezer::freeze_until_width_update(Gtk::Window *w, int width) {
    int wd, ht;
    w->get_size(wd, ht);
    if (wd == width) {
	return;
    }
    freeze(w, width, -1);
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
    gx_print_error("freezer", "timeout");
#else
    gx_print_warning("freezer", "timeout");
#endif
    if (size_y != -1) {
	window->set_size_request(-1,-1);
    }
    do_thaw();
    return false;
}

void Freezer::do_thaw() {
    size_x = size_y = -1;
    Glib::RefPtr<Gdk::Window> win = window->get_window();
    window = 0;
    if (!win) {
	return;
    }
    if (!work.empty()) {
	Glib::signal_idle().connect_once(work);
	work.disconnect();
    }
    if (need_thaw) {
	win->thaw_updates();
    }
}

void Freezer::thaw() {
    if (size_x != -1) {
	tag.disconnect();
	do_thaw();
    }
}

bool Freezer::check_thaw(int width, int height) {
    if (size_x == -1) {
	return true;
    }
    Glib::RefPtr<Gdk::Window> win = window->get_window();
    if (win && win->get_state()) {
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
    if (!tag.connected()) {
	tag = Glib::signal_timeout().connect(sigc::mem_fun(*this, &Freezer::thaw_timeout), 500);
    }
    return false;
}


/****************************************************************
 ** class MainWindow
 */

template <class T>
UiToggleAction<T>::UiToggleAction(
    gx_engine::GxMachineBase& machine_, const std::string& id_, const Glib::ustring& name, const Glib::ustring& icon_name,
    const Glib::ustring& label, const Glib::ustring& tooltip,
    bool is_active)
    : Gtk::ToggleAction(name, icon_name, label, tooltip, is_active),
      machine(machine_),
      id(id_) {
    set_active(machine.get_parameter_value<T>(id));
    machine.signal_parameter_value<T>(id).connect(
	sigc::mem_fun(this, &UiToggleAction::set_active));
}

template <class T>
UiToggleAction<T>::~UiToggleAction() {
}

template <class T>
void UiToggleAction<T>::on_toggled() {
    machine.set_parameter_value(id, get_active());
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

void MainWindow::maybe_shrink_horizontally(bool preset_no_rack) {
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
    if (preset_no_rack) {
	req.height += options.preset_window_height - preset_scrolledbox->size_request().height;
    } else {
	req.height = std::max(req.height, options.window_height);
    }
    w->move_resize(x, y, req.width, req.height);
    if (!state) {
	freezer.freeze_until_width_update(window, req.width);
    }
}

void MainWindow::on_show_tuner() {
    bool v = actions.tuner->get_active();
    on_livetuner_toggled();
    tunerbox->set_visible(v);
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
    bld->find_widget("preset_box_no_rack", preset_box_no_rack);
    bld->find_widget("effects_frame_paintbox", effects_frame_paintbox);
    bld->find_widget("status_image", status_image);
    bld->find_widget("jackd_image", jackd_image);
    bld->find_widget("logstate_image", logstate_image);
    bld->find_widget("menubox", menubox);
    bld->find_widget("show_rack:barbutton", show_rack_button);
    bld->find_widget("rack_order_h:barbutton", rack_order_h_button);
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
    bld->find_widget("tuner_temperament", tuner_temperament);
    bld->find_widget("racktuner", racktuner);
    bld->find_widget("ampdetail_compress:effect_reset", ampdetail_compress);
    bld->find_widget("ampdetail_expand:effect_reset", ampdetail_expand);
    bld->find_widget("ampdetail_mini", ampdetail_mini);
    bld->find_widget("ampdetail_normal", ampdetail_normal);
    bld->find_widget("fastmeterL", fastmeter[0]);
    bld->find_widget("fastmeterR", fastmeter[1]);
    bld->find_widget("preset_status", preset_status);
    bld->find_widget("midi_out_box", midi_out_box);
    bld->find_widget("midi_out_normal", midi_out_normal);
    bld->find_widget("midi_out_mini", midi_out_mini);
    bld->find_widget("midi_out_compress:effect_reset", midi_out_compress);
    bld->find_widget("midi_out_expand:effect_reset", midi_out_expand);
    bld->find_widget("midi_out_presets_mini", midi_out_presets_mini);
    bld->find_widget("midi_out_presets_normal", midi_out_presets_normal);
    bld->find_widget("channel1_button", channel1_button);
    bld->find_widget("channel1_box", channel1_box);
    bld->find_widget("channel2_button", channel2_button);
    bld->find_widget("channel2_box", channel2_box);
    bld->find_widget("channel3_button", channel3_button);
    bld->find_widget("channel3_box", channel3_box);
}

void MainWindow::on_select_preset(int idx) {
    keyswitch.process_preset_key(idx);
}

void MainWindow::rebuild_preset_menu() {
    if (preset_list_merge_id) {
	uimanager->remove_ui(preset_list_merge_id);
	uimanager->remove_action_group(preset_list_actiongroup);
	preset_list_menu_bank.clear();
	preset_list_merge_id = 0;
	preset_list_actiongroup.reset();
	uimanager->ensure_update();
    }
    if (!machine.setting_is_preset()) {
	return;
    }
    gx_system::PresetFileGui *pf = machine.get_current_bank_file();
    if (!pf) {
	return;
    }
    preset_list_actiongroup = Gtk::ActionGroup::create("PresetList");
    preset_list_menu_bank = machine.get_current_bank();
    Glib::ustring s = "<menubar><menu action=\"PresetsMenu\"><menu action=\"PresetListMenu\">";
    int idx = 0;
    for (gx_system::PresetFile::iterator i = pf->begin(); i != pf->end(); ++i, ++idx) {
	Glib::ustring actname = "PresetList_" + i->name;
	Glib::RefPtr<Gtk::Action> action = Gtk::Action::create(actname, i->name);
	preset_list_actiongroup->add(
	    action, sigc::bind(sigc::mem_fun(*this, &MainWindow::on_select_preset), idx));
	if (idx <= 9) {
	    char c = (idx == 9 ? '0' : '1'+idx);
	    Gtk::AccelMap::change_entry(action->get_accel_path(), c, Gdk::ModifierType(0), true);
	}
	s += Glib::ustring::compose("<menuitem action=\"%1\"/>", actname);
    }
    s += "</menu></menu></menubar>";
    uimanager->insert_action_group(preset_list_actiongroup);
    preset_list_merge_id = uimanager->add_ui_from_string(s);
    dynamic_cast<Gtk::MenuItem*>(uimanager->get_widget("/menubar/PresetsMenu/PresetListMenu"))->set_label(_("_Bank: ")+preset_list_menu_bank);
}

void MainWindow::show_selected_preset() {
    keyswitch.deactivate();
    Glib::ustring t;
    if (machine.setting_is_preset()) {
	t = machine.get_current_bank() + " / " + machine.get_current_name();
	if (preset_list_menu_bank != machine.get_current_bank()) {
	    rebuild_preset_menu();
	}
    }
    preset_status->set_text(t);
}

bool MainWindow::is_variable_size() {
    return actions.presets->get_active() || actions.show_rack->get_active();
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

void MainWindow::set_vpaned_handle() {
    int w, h;
    main_vpaned->get_handle_window()->get_size(w, h);
    int pos = main_vpaned->get_allocation().get_height() - options.preset_window_height - h;
    main_vpaned->set_position(pos);
}

void MainWindow::on_show_rack() {
    Gtk::Widget *w;
    if (rackbox_stacked_vertical()) {
	w = stereorackcontainerV;
    } else {
	w = stereorackbox;
    }
    bool v = options.system_show_rack = actions.show_rack->get_active();
    actions.rackh->set_sensitive(v);
    rackcontainer->set_border_width(v ? 18 : 0); //FIXME (just experimental)
    stereorackcontainer.set_visible(v);
    rack_order_h_button->set_visible(v);
    compress_button->set_visible(v);
    expand_button->set_visible(v);
    if (actions.presets->get_active() && preset_scrolledbox->get_mapped()) {
	options.preset_window_height = preset_scrolledbox->get_allocation().get_height();
    }
    if (v) {
	midi_out_box->set_visible(actions.midi_out->get_active());
	options.window_height = max(options.window_height, window->size_request().height);
	main_vpaned->set_position(oldpos);
	w->show();
	monoampcontainer->show();
	monorackcontainer.show_entries();
	vrack_scrolledbox->set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_ALWAYS);
	vrack_scrolledbox->set_size_request(scrl_size_x, scrl_size_y);
	if (preset_scrolledbox->get_parent() != main_vpaned) {
	    preset_box_no_rack->remove(*preset_scrolledbox);
	    main_vpaned->add(*preset_scrolledbox);
	    change_expand(*preset_box_no_rack, false);
	    change_expand(*main_vpaned, true);
	}
	Glib::RefPtr<Gdk::Window> win = window->get_window();
	if (!win || win->get_state() == 0) {
	    Gtk::Requisition req;
	    window->size_request(req);
	    req.height = max(req.height, options.window_height);
	    freezer.freeze_and_size_request(window, req.width, req.height);
	    if (win && actions.presets->get_active()) {
		freezer.set_slot(sigc::mem_fun(this, &MainWindow::set_vpaned_handle));
	    }
	}
    } else {
	if (actions.midi_out->get_active()) {
	    midi_out_box->set_visible(false);
	}
	actions.show_plugin_bar->set_active(false);
	oldpos = main_vpaned->get_position();
	w->hide();
	monoampcontainer->hide();
	monorackcontainer.hide_entries();
	if (preset_scrolledbox->get_parent() == main_vpaned) {
	    main_vpaned->remove(*preset_scrolledbox);
	    preset_box_no_rack->add(*preset_scrolledbox);
	    change_expand(*main_vpaned, false);
	    change_expand(*preset_box_no_rack, true);
	}
	preset_box_no_rack->set_visible(actions.presets->get_active());
	vrack_scrolledbox->set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_NEVER);
	vrack_scrolledbox->get_size_request(scrl_size_x, scrl_size_y);
	vrack_scrolledbox->set_size_request(-1,-1);
	if (actions.presets->get_active()) {
	    maybe_shrink_horizontally(true);
	} else {
	    maybe_shrink_horizontally();
	}
    }
    maybe_change_resizable();
}

void MainWindow::on_compress_all() {
    plugin_dict.compress(true);
    on_ampdetail_switch(true, true);
    actions.midi_out_plug->set_active(true);
}

void MainWindow::on_expand_all() {
    plugin_dict.compress(false);
    on_ampdetail_switch(false, true);
    actions.midi_out_plug->set_active(false);
}

void MainWindow::on_rack_configuration() {
    bool v = actions.rack_config->get_active();
    actions.show_plugin_bar->set_sensitive(!v);
    actions.show_rack->set_sensitive(!v);
    actions.tuner->set_sensitive(!v);
    actions.compress->set_sensitive(!v);
    actions.expand->set_sensitive(!v);
    actions.live_play->set_sensitive(!v);
    Gtk::Requisition req;
    monobox->size_request(req);
    stereorackcontainer.set_config_mode(v);
    monorackcontainer.set_config_mode(v);
    szg_rack_units->set_ignore_hidden(v);
    bool plugin_bar = actions.show_plugin_bar->get_active();
    if (v) {
	pre_act = actions.presets->get_active();
	if (pre_act) {
	    actions.presets->set_active(false);
	}
    actions.show_rack->set_active(true);
	effects_frame_paintbox->show();
	upper_rackbox->hide();
	Gtk::Requisition req2;
	effects_frame_paintbox->size_request(req2);
	int width = req.width;
	if (!plugin_bar) {
	    if (rackbox_stacked_vertical()) {
		width -= req2.width;
	    } else {
		if (req2.width & 1) {
		    req2.width += 1;
		}
		width -= req2.width/2;
	    }
	}
	effects_frame_paintbox->set_size_request(req2.width, -1);
	monobox->set_size_request(width,-1);
    } else {
	if (!plugin_bar) {
	    effects_frame_paintbox->hide();
	}
	upper_rackbox->show();
 	effects_frame_paintbox->set_size_request(-1,-1);
	monobox->set_size_request(-1,-1);
	if (pre_act) {
	    actions.presets->set_active(true);
	}
    }
    if (!plugin_bar) {
	update_width();
	maybe_shrink_horizontally();
    }
}

void MainWindow::on_show_plugin_bar() {
    bool v = options.system_show_toolbar = actions.show_plugin_bar->get_active();
    if (v) {
	actions.show_rack->set_active(true);
    }
    effects_frame_paintbox->set_visible(v);
    if (!v) {
	//update_scrolled_window(*vrack_scrolledbox);
	//update_scrolled_window(*stereorackbox);
	maybe_shrink_horizontally();
    }
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
    return !actions.rackh->get_active();
}

void MainWindow::change_expand(Gtk::Widget& w, bool value) {
    Gtk::Box *p = dynamic_cast<Gtk::Box*>(w.get_parent());
    int expand, fill;
    unsigned int padding;
    GtkPackType pack_type;
    gtk_box_query_child_packing(p->gobj(), w.gobj(), &expand, &fill, &padding, &pack_type);
    gtk_box_set_child_packing(p->gobj(), w.gobj(), value, value, padding, pack_type);
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
    if (off < alloc.get_y()) {
	return off;
    }
    return max(off-step_size, double(alloc.get_y()));
}

void MainWindow::on_dir_changed() {
    bool v = options.system_order_rack_h = actions.rackh->get_active();
    if (v) {
	// horizontally
	move_widget(stereorackcontainer, *stereorackcontainerV, *stereorackcontainerH);
	change_expand(*monobox, true);
	stereorackbox->show();
    } else {
	move_widget(stereorackcontainer, *stereorackcontainerH, *stereorackcontainerV);
	change_expand(*monobox, false);
	stereorackbox->hide();
	maybe_shrink_horizontally();
    }
}

void MainWindow::on_configure_event(GdkEventConfigure *ev) {
    if (freezer.check_thaw(ev->width, ev->height)) {
	if (actions.show_rack->get_active()) {
	    options.window_height = ev->height;
	}
    }
}

void MainWindow::resize_finished(RackContainer *ch)
{
    if (ch == &monorackcontainer && !actions.rackh->get_active()) {
	stereorackcontainer.queue_draw();
    }
}

void MainWindow::update_width() {
    update_scrolled_window(*vrack_scrolledbox);
    update_scrolled_window(*stereorackbox);
}

RackBox *MainWindow::add_rackbox_internal(PluginUI& plugin, Gtk::Widget *mainwidget, Gtk::Widget *miniwidget,
					  bool mini, int pos, bool animate, Gtk::Widget *bare) {
    RackBox *r = new RackBox(plugin, *this, bare);
    if (mini) {
	r->swtch(true);
    }
    r->pack(mainwidget, miniwidget, szg_rack_units);
    update_width();
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

RackBox *MainWindow::add_rackbox(PluginUI& pl, bool mini, int pos, bool animate) {
    Gtk::Widget *mainwidget = 0;
    Gtk::Widget *miniwidget = 0;
    boxbuilder.get_box(pl.get_id(), mainwidget, miniwidget);
    if (!mainwidget) {
	gx_gui::UiBuilderImpl builder(this, &boxbuilder);
	
	if (machine.load_unit(builder, pl.plugin->get_pdef())) {
	    boxbuilder.fetch(mainwidget, miniwidget);
	}
    }
    return add_rackbox_internal(pl, mainwidget, miniwidget, mini, pos, animate);
}

void MainWindow::add_icon(const std::string& name) {
    PluginUI *p = plugin_dict[name];
    p->toolitem->show();
}

void MainWindow::on_show_values() {
    options.system_show_value = actions.show_values->get_active();
    std::string s =
	"style \"ShowValue\" {\n"
	"  GxRegler::show-value = " + gx_system::to_string(options.system_show_value) + "\n"
	"}\n"
	"class \"*GxRegler*\" style:highest \"ShowValue\"\n";
    gtk_rc_parse_string(s.c_str());
    gtk_rc_reset_styles(gtk_settings_get_default());
}

void MainWindow::on_preset_action() {
    bool v = options.system_show_presets = actions.presets->get_active();
    if (!v && preset_scrolledbox->get_mapped()) {
	options.preset_window_height = preset_scrolledbox->get_allocation().get_height();
    }
    maybe_change_resizable();
    if (v && !actions.show_rack->get_active()) {
	Glib::RefPtr<Gdk::Window> win = window->get_window();
	if (!win || win->get_state() == 0) {
	    Gtk::Requisition req;
	    window->size_request(req);
	    freezer.freeze_and_size_request(window, req.width, req.height+options.preset_window_height);
	}
    }
    preset_box_no_rack->set_visible(v);
    preset_window->on_preset_select(v, use_animations() && actions.show_rack->get_active(), options.preset_window_height);
}

/*
** UI initialization
*/

bool MainWindow::on_my_leave_out(GdkEventCrossing *focus) {
    Glib::RefPtr<Gdk::Window> wind = window->get_window();
    wind->set_cursor();
    return true;
}

bool MainWindow::on_my_enter_in(GdkEventCrossing *focus) {
    Glib::RefPtr<Gdk::Window> wind = window->get_window();
    Gdk::Cursor cursor(Gdk::HAND1);
    wind->set_cursor(cursor);
    return true;
}

void MainWindow::add_toolitem(PluginUI& pl, Gtk::ToolItemGroup *gw) {
    Gtk::ToolItem *tb = new Gtk::ToolItem();
    tb->set_use_drag_window(true);
    tb->signal_drag_begin().connect(sigc::bind(sigc::mem_fun(*this, &MainWindow::on_ti_drag_begin), sigc::ref(pl)));
    tb->signal_drag_end().connect(sigc::mem_fun(*this, &MainWindow::on_ti_drag_end));
    tb->signal_drag_data_delete().connect(sigc::bind(sigc::mem_fun(*this, &MainWindow::on_ti_drag_data_delete), pl.get_id()));
    tb->signal_button_press_event().connect(sigc::bind(sigc::mem_fun(*this, &MainWindow::on_ti_button_press), pl.get_id()));
    tb->add_events(Gdk::ENTER_NOTIFY_MASK|Gdk::LEAVE_NOTIFY_MASK);
    tb->signal_leave_notify_event().connect(sigc::mem_fun(*this, &MainWindow::on_my_leave_out));
    tb->signal_enter_notify_event().connect(sigc::mem_fun(*this, &MainWindow::on_my_enter_in));
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
    tb->show_all();
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
    live_play->on_live_play(actions.live_play);
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
    Gtk::ToolItem *toolitem = plugin_dict[name]->toolitem;
    if (toolitem) {
	toolitem->hide();
    }
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
    bool v = actions.jackserverconnection->get_active();
    if (!connect_jack(v)) {
	actions.jackserverconnection->set_active(!v);
    }
}

void MainWindow::on_portmap_response(int) {
    actions.jackports->set_active(false);
}

void MainWindow::on_portmap_activate() {
    gx_jack::GxJack *jack = machine.get_jack();
    if (!jack) {
	return;
    }
    if (actions.jackports->get_active()) {
	if (portmap_window) {
	    return;
	}
	portmap_window = gx_portmap::PortMapWindow::create(machine, actions.accels);
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
    gx_main_midi::MidiControllerTable::toggle(machine, actions.midicontroller);
}

void MainWindow::change_skin(Glib::RefPtr<Gtk::RadioAction> action) {
    set_new_skin(options.skin[action->get_current_value()]);
}

void MainWindow::set_new_skin(const Glib::ustring& skin_name) {
    if (!skin_name.empty()) {
	options.skin_name = skin_name;
	string rcfile = options.get_style_filepath(
	    "gx_head_" + skin_name + ".rc");
	gtk_rc_parse(rcfile.c_str());
	gtk_rc_reset_styles(gtk_settings_get_default());
	make_icons();
    }
}

void MainWindow::add_skin_menu() {
    Glib::ustring s = "<menubar><menu action=\"OptionsMenu\"><menu action=\"SkinMenu\">";
    int idx = 0;
    Gtk::RadioButtonGroup sg;
    for (vector<Glib::ustring>::iterator i = options.skin.skin_list.begin();
	 i != options.skin.skin_list.end();
	 ++i) {
	Glib::ustring name = *i;
	Glib::ustring actname = Glib::ustring::compose("ChangeSkin_%1", name);
	s += Glib::ustring::compose("<menuitem action=\"%1\"/>", actname);
	Glib::RefPtr<Gtk::RadioAction> action = Gtk::RadioAction::create(sg, actname, name);
	if (name == options.skin_name) {
	    action->set_active(true);
	}
	actions.group->add(action);
	if (idx == 0) {
	    actions.skin = action;
	}
	action->property_value().set_value(idx++);
    }
    actions.skin->signal_changed().connect(
	sigc::mem_fun(*this, &MainWindow::change_skin));
    s.append("</menu></menu></menubar>");
    uimanager->add_ui_from_string(s);
}

enum GxJackLatencyChange {
    kChangeLatency = 1,
    kKeepLatency   = 2
};

// check user's decision to turn off latency change warning
void MainWindow::user_disable_latency_warn(Gtk::CheckButton* disable_warn) {
    options.no_warn_latency = disable_warn->get_active();
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
    gx_jack::GxJack *jack = machine.get_jack();
    if (!jack) {
	return;
    }
    if (!jack->client) {
        gx_print_error(
            _("Jack Buffer Size setting"),
            _("we are not a jack gxjack.client, server may be down")
            );
        return;
    }
    jack_nframes_t buf_size = action->get_current_value();
    if (buf_size == jack->get_jack_bs()) {
        return;
    }
    if (!options.no_warn_latency && gx_wait_latency_warn() != kChangeLatency) {
	Glib::signal_idle().connect_once(
	    sigc::bind(
		sigc::mem_fun(action.operator->(), &Gtk::RadioAction::set_current_value), jack->get_jack_bs()));
    } else {
        if (jack_set_buffer_size(jack->client, buf_size) != 0)
            gx_print_warning(_("Setting Jack Buffer Size"),
					_("Could not change latency"));
    }
    gx_print_info(
	_("Jack Buffer Size"),
	boost::format(_("latency is %1%")) % jack_get_buffer_size(jack->client));
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
	actions.group->add(action);
	if (i == 0) {
	    action->signal_changed().connect(
		sigc::mem_fun(*this, &MainWindow::change_latency));
	    actions.latency = action;
	}
	action->property_value().set_value(jack_buffer_size);
	jack_buffer_size *= 2;
    }
    s.append("</menu></menu></menubar>");
    uimanager->add_ui_from_string(s);
}

void MainWindow::set_latency() {
    gx_jack::GxJack *jack = machine.get_jack();
    if (!jack) {
	return;
    }
    jack_nframes_t n = jack->get_jack_bs();
    if (n > 0) {
	actions.latency->set_current_value(n);
    }
    if (n > 1023) actions.osc_buffer_menu->set_sensitive(false);
    else actions.osc_buffer_menu->set_sensitive(true);
}

void show_forum_help() {
    GError *error = NULL;
    gtk_show_uri(gdk_screen_get_default(), "http://guitarix.sourceforge.net/forum/",
    gtk_get_current_event_time(), &error);
    if (error)
    {
        gx_print_error("guitarix help",
				  _("failed to load online help   "));
        g_error_free(error);
    }
}

void gx_show_help() {
    Glib::signal_idle().connect_once(sigc::ptr_fun( show_forum_help));
}

// ----menu funktion about
void gx_show_about() {
    static string about;
    if (about.empty()) {
        about +=_("\n Guitarix:gx_head ");
        about += GX_VERSION;
        about +=
            _("\n\n  This Aplication is to a large extent provided"
            "\n  with the marvelous faust compiler.Yann Orlary"
            "\n  http://faust.grame.fr/"
            "\n  A large part is based on the work of Julius Orion Smith"
            "\n  http://ccrma.stanford.edu/realsimple/faust/"
            "\n  and Albert Graef\n  http://q-lang.sourceforge.net/examples.html#Faust"
            "\n\n ");


        about +=
            _("\n  for impulse response it use zita-convolver "
            "\n  byFons Adriaensen "
            "\n  http://www.kokkinizita.net/linuxaudio/index.html "
            "\n\n  The included IR-files are contributed by "
            "\n  David Fau Casquel (BESTPLUGINS) "
            "\n  home: http://www.youtube.com/bestplugins"
            "\n\n  authors: Hermann Meyer <brummer-@web.de>"
            "\n  authors: James Warden <warjamy@yahoo.com>"
            "\n  authors: Andreas Degert <andreas.degert@googlemail.com>    "
            "\n  authors: Pete Shorthose <pshorthose@gmail.com>    "
            "\n  home: http://guitarix.sourceforge.net/\n");
    }

    gx_gui::gx_message_popup(about.c_str());
}

void MainWindow::set_tooltips() {
    options.system_show_tooltips = actions.tooltips->get_active();
    gtk_settings_set_long_property(
        gtk_settings_get_default(), "gtk-enable-tooltips", options.system_show_tooltips,
        "gx_head menu-option");
}

void MainWindow::set_animations() {
    options.system_animations = actions.animations->get_active();
}

void MainWindow::on_select_jack_control() {
    if (select_jack_control) {
	select_jack_control->present();
    } else {
	select_jack_control = gx_gui::SelectJackControlPgm::create(options, machine);
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
    if (actions.loggingbox->get_active()) {
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
    if (actions.engine_mute->get_active()) {
	s = gx_engine::kEngineOff;
    } else if (actions.engine_bypass->get_active()) {
	s = gx_engine::kEngineBypass;
    } else {
	s = gx_engine::kEngineOn;
    }
    machine.set_state(s);
}

void MainWindow::set_switcher_controller() {
    if (!machine.midi_get_config_mode()) {
	new gx_main_midi::MidiConnect(0, machine.get_parameter("ui.live_play_switcher"), machine);
    }
}

void MainWindow::on_show_midi_out() {
#ifdef USE_MIDI_OUT
    if (actions.midi_out->get_active()) {
	actions.show_rack->set_active(true);
	midi_out_box->set_visible(true);
    } else {
	midi_out_box->set_visible(false);
	machine.pluginlist_lookup_plugin("midi_out")->set_on_off(false);
    }
#endif
}

void MainWindow::on_show_midi_out_plug() {
    if (actions.midi_out_plug->get_active()) {
	midi_out_normal->hide();
	midi_out_mini->show();
    } else {
	midi_out_mini->hide();
	midi_out_normal->show();
    }
}

void MainWindow::on_midi_out_channel_toggled(Gtk::RadioButton *rb, Gtk::Container *c) {
    c->set_visible(rb->get_active());
}

void MainWindow::on_livetuner_toggled() {
    if (actions.livetuner->get_active()) {
	if (actions.live_play->get_active()) {
	    live_play->display_tuner(true);
	    racktuner->set_sensitive(false);
	    machine.tuner_used_for_display(true);
	} else {
	    live_play->display_tuner(false);
	    if (actions.tuner->get_active()) {
		racktuner->set_sensitive(true);
		machine.tuner_used_for_display(true);
 	    } else {
		machine.tuner_used_for_display(false);
	    }
	}
    } else {
	live_play->display_tuner(false);
	racktuner->set_sensitive(false);
	machine.tuner_used_for_display(false);
    }
}

void MainWindow::create_actions() {
    gx_jack::GxJack *jack = machine.get_jack();
    actions.group = Gtk::ActionGroup::create("Main");
    /*
    ** Menu actions
    */
    actions.group->add(Gtk::Action::create("EngineMenu",_("_Engine")));
    actions.jack_latency_menu = Gtk::Action::create("JackLatency",_("_Latency"));
    actions.group->add(actions.jack_latency_menu);
    actions.osc_buffer_menu = Gtk::Action::create("OscBuffer",_("Osc. Buffer-size"));
    actions.group->add(actions.osc_buffer_menu);

    actions.group->add(Gtk::Action::create("PresetsMenu",_("_Presets")));
    actions.group->add(Gtk::Action::create("PresetListMenu","--"));
    actions.group->add(Gtk::Action::create("PluginsMenu",_("P_lugins")));
    actions.group->add(Gtk::Action::create("MonoPlugins",_("_Mono Plugins")));
    actions.group->add(Gtk::Action::create("StereoPlugins",_("_Stereo Plugins")));
    actions.group->add(Gtk::Action::create("TubeMenu",_("_Tube")));
    actions.group->add(Gtk::Action::create("OptionsMenu",_("_Options")));
    actions.group->add(Gtk::Action::create("SkinMenu", _("_Skin...")));
    actions.group->add(Gtk::Action::create("AboutMenu",_("_About")));

    /*
    ** engine actions
    */
    actions.jackserverconnection = Gtk::ToggleAction::create("JackServerConnection", _("Jack Server _Connection"));
    actions.group->add(
	actions.jackserverconnection,
	sigc::mem_fun(*this, &MainWindow::jack_connection));

    actions.jackports = Gtk::ToggleAction::create("JackPorts", _("Jack _Ports"));
    actions.group->add(
	actions.jackports,
	sigc::mem_fun(*this, &MainWindow::on_portmap_activate));

    actions.midicontroller = Gtk::ToggleAction::create("MidiController", _("M_idi Controller"));
    actions.group->add(
	actions.midicontroller,
        sigc::mem_fun(*this, &MainWindow::on_miditable_toggle));

    actions.engine_mute = Gtk::ToggleAction::create("EngineMute", _("Engine _Mute"));
    actions.group->add(actions.engine_mute);
    actions.engine_mute_conn = actions.engine_mute->signal_toggled().connect(
	sigc::mem_fun(*this, &MainWindow::on_engine_toggled));

    actions.engine_bypass = Gtk::ToggleAction::create("EngineBypass", _("Engine _Bypass"));
    actions.group->add(actions.engine_bypass);
    actions.engine_bypass_conn = actions.engine_bypass->signal_toggled().connect(
	sigc::mem_fun(*this, &MainWindow::on_engine_toggled));

    actions.quit = Gtk::Action::create("Quit",_("_Quit"));
    actions.group->add(
	actions.quit,
	sigc::hide_return(sigc::mem_fun(this, &MainWindow::on_quit)));

    /*
    ** actions to open other (sub)windows
    */
    actions.presets = Gtk::ToggleAction::create(
	"Presets",_("_Preset Selection"));
    actions.group->add(actions.presets,
		       sigc::mem_fun(*this, &MainWindow::on_preset_action));

    actions.show_plugin_bar = Gtk::ToggleAction::create(
	"ShowPluginBar",_("Show Plugin _Bar"));
    actions.group->add(actions.show_plugin_bar,
		       sigc::mem_fun(*this, &MainWindow::on_show_plugin_bar));

    actions.show_rack = Gtk::ToggleAction::create(
	"ShowRack",_("Show _Rack"), "", true);
    actions.group->add(actions.show_rack,
		       sigc::mem_fun(*this, &MainWindow::on_show_rack));

    actions.loggingbox = Gtk::ToggleAction::create("LoggingBox", _("Show _Logging Box"));
    actions.group->add(
	actions.loggingbox,
        sigc::mem_fun(*this, &MainWindow::on_log_activate));

    actions.live_play = Gtk::ToggleAction::create("Liveplay",_("Live _Display"));
    actions.group->add(actions.live_play,
		     sigc::mem_fun(*this, &MainWindow::on_live_play));

    actions.meterbridge = Gtk::ToggleAction::create("Meterbridge", _("_Meterbridge"));
    if (jack) {
	actions.group->add(
	    actions.meterbridge,
	    sigc::bind(sigc::ptr_fun(gx_child_process::Meterbridge::start_stop),
		       sigc::ref(actions.meterbridge), sigc::ref(*jack)));
    } else {
	actions.group->add(actions.meterbridge);
    }

    actions.livetuner = UiBoolToggleAction::create(
	machine, "ui.racktuner", "LiveTuner", "??");
    actions.group->add(actions.livetuner);
    actions.livetuner->signal_toggled().connect(
	sigc::mem_fun(this, &MainWindow::on_livetuner_toggled));

    actions.midi_out = UiBoolToggleAction::create(
	machine, "ui.midi_out", "MidiOut", _("M_idi Out"));
    actions.group->add(
	actions.midi_out,
	sigc::mem_fun(this, &MainWindow::on_show_midi_out));

    actions.midi_out_plug = UiBoolToggleAction::create(
	machine, "midi_out.s_h", "MidiOutSH", "??");
    actions.group->add(
	actions.midi_out_plug,
	sigc::mem_fun(this, &MainWindow::on_show_midi_out_plug));

    /*
    ** rack actions
    */
    actions.tuner = UiBoolToggleAction::create(
	machine, "system.show_tuner", "Tuner",_("_Tuner"));
    actions.group->add(actions.tuner,
		     sigc::mem_fun(*this, &MainWindow::on_show_tuner));

    actions.rack_config = Gtk::ToggleAction::create("RackConfig", _("R_ack Configuration"));
    actions.group->add(actions.rack_config,
		     sigc::mem_fun(*this, &MainWindow::on_rack_configuration));

    actions.compress = Gtk::Action::create("Compress",_("C_ompress all"));
    actions.group->add(actions.compress,
		     sigc::mem_fun(*this, &MainWindow::on_compress_all));

    actions.expand = Gtk::Action::create("Expand",_("E_xpand all"));
    actions.group->add(actions.expand,
		     sigc::mem_fun(*this, &MainWindow::on_expand_all));

    actions.rackh = Gtk::ToggleAction::create(
	"RackH", _("Order Rack _Horizontally"));
    actions.group->add(actions.rackh,
		     sigc::mem_fun(*this, &MainWindow::on_dir_changed));

    /*
    ** option actions
    */
    actions.show_values = Gtk::ToggleAction::create(
	"ShowValues",_("_Show _Values"), "", true);
    actions.group->add(actions.show_values,
		       sigc::mem_fun(*this, &MainWindow::on_show_values));

    actions.tooltips = Gtk::ToggleAction::create(
	"ShowTooltips", _("Show _Tooltips"), "", true);
    actions.group->add(
	actions.tooltips,
	sigc::mem_fun(this, &MainWindow::set_tooltips));

    actions.midi_in_presets = UiSwitchToggleAction::create(
	machine, "system.midi_in_preset", "MidiInPresets", _("Include MIDI in _presets"));
    actions.group->add(actions.midi_in_presets);

    actions.jackstartup = Gtk::Action::create("JackStartup", _("_Jack Startup Control"));
    actions.group->add(
	actions.jackstartup,
	sigc::mem_fun(*this, &MainWindow::on_select_jack_control));

    actions.loadladspa = Gtk::Action::create("LoadLADSPA", _("LADSPA/LV2 Pl_ugins"));
    actions.group->add(
	actions.loadladspa,
	sigc::mem_fun(this, &MainWindow::on_load_ladspa));

    actions.group->add(Gtk::Action::create("ResetAll", _("Reset _All Parameters")),
		       sigc::mem_fun(machine, &gx_engine::GxMachineBase::set_init_values));

    actions.animations = Gtk::ToggleAction::create(
	"Animations", _("_Use Animations"),"",true);
    actions.group->add(actions.animations,
		       sigc::mem_fun(this, &MainWindow::set_animations));

    actions.group->add(Gtk::Action::create("SetPresetSwitcher", _("L_iveplay Midi Switch")),
		     sigc::mem_fun(this, &MainWindow::set_switcher_controller));

    /*
    ** Help and About
    */
    actions.group->add(Gtk::Action::create("Help", _("_Help")),
		     sigc::ptr_fun(gx_show_help));
    actions.group->add(Gtk::Action::create("About", _("_About")),
		     sigc::ptr_fun(gx_show_about));

    if (!jack) {
	actions.jack_latency_menu->set_visible(false);
	actions.jackserverconnection->set_visible(false);
	actions.jackports->set_visible(false);
	actions.meterbridge->set_visible(false);
    }
}

#if false // unused
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
#endif

void MainWindow::plugin_preset_popup(const PluginDef *pdef) {
    new PluginPresetPopup(pdef, machine);
}

void MainWindow::plugin_preset_popup(const PluginDef *pdef, const Glib::ustring& name) {
    new PluginPresetPopup(pdef, machine, name);
}

void MainWindow::clear_box(Gtk::Container& box) {
    std::vector<Gtk::Widget*> l = box.get_children();
    for (std::vector<Gtk::Widget*>::iterator p = l.begin(); p != l.end(); ++p) {
	box.remove(**p);
    }
}

void MainWindow::make_icons(bool force) {
    Gtk::OffscreenWindow w;
    w.set_type_hint(Gdk::WINDOW_TYPE_HINT_DOCK); // circumvent canberra-gtk-module bug on AV Linux
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
	if (!force && i->second->icon) {
	    continue;
	}
        Gtk::Widget *r = RackBox::create_icon_widget(*i->second, options);
        r->hide();
        r->set_no_show_all(true);
        vb.add(*manage(r));
        sz->add_widget(*r);
	l.push_back(std::pair<PluginUI*,Gtk::Widget*>(i->second, r));
    }
    //FIXME hack to set a minimum size
    l.begin()->second->show();
    if (vb.size_request().width < 110) {
	vb.set_size_request(110, -1);
    }
    w.show_all();
    for (std::vector<std::pair<PluginUI*,Gtk::Widget*> >::iterator i = l.begin(); i != l.end(); ++i) {
        i->second->show();
	w.show();
        w.get_window()->process_updates(true);
	i->first->icon = w.get_pixbuf();
	if (i->first->toolitem) {
	    dynamic_cast<Gtk::Image*>(i->first->toolitem->get_child())->set(i->first->icon);
	}
	w.hide();
        i->second->hide();
    }
}

class JConvPluginUI: public PluginUI {
private:
    virtual void on_plugin_preset_popup();
public:
    JConvPluginUI(MainWindow& main, const char* id,
		  const Glib::ustring& tooltip="")
	: PluginUI(main, id, tooltip) {
    }
};

void JConvPluginUI::on_plugin_preset_popup() {
    gx_engine::JConvParameter *jcp = dynamic_cast<gx_engine::JConvParameter*>(
	&main.get_machine().get_parameter(std::string(get_id())+".convolver"));
    assert(jcp);
    Glib::ustring name = jcp->get_value().getIRFile();
    Glib::ustring::size_type n = name.find_last_of('.');
    if (n != Glib::ustring::npos) {
	name.erase(n);
    }
    main.plugin_preset_popup(plugin->get_pdef(), name);
}

void MainWindow::on_plugin_changed(gx_engine::Plugin *pl, gx_engine::PluginChange::pc c) {
    if (!pl) { // end of update sequence
	make_icons(true); // re-create all icons, width might have changed
    } else if (c == gx_engine::PluginChange::add) {
	register_plugin(new PluginUI(*this, pl->get_pdef()->id, ""));
    } else {
	PluginUI *pui = plugin_dict[pl->get_pdef()->id];
	if (c == gx_engine::PluginChange::remove) {
	    plugin_dict.remove(pui);
	    pui->unset_ui_merge_id(uimanager);
	    uimanager->ensure_update();
	    actions.group->remove(pui->get_action());
	    machine.remove_rack_unit(pui->get_id(), pui->get_type());
	    std::string group_id = pui->get_category();
	    delete pui;
	    Gtk::ToolItemGroup * group = groupmap[group_id];
	    if (group->get_n_items() == 0) {
		Glib::ustring groupname = Glib::ustring::compose("PluginCategory_%1", group_id);
		Glib::RefPtr<Gtk::Action> act = actions.group->get_action(groupname);
		actions.group->remove(actions.group->get_action(groupname));
		groupmap.erase(group_id);
		delete group;
	    }
	} else {
	    assert(c == gx_engine::PluginChange::update || c == gx_engine::PluginChange::update_category);
        //if (!pui->plugin->get_box_visible())
        bool state =  pui->plugin->get_on_off();
	    pui->update_rackbox();
        pui->plugin->set_on_off(state);
	    if (c == gx_engine::PluginChange::update_category) {
		pui->unset_ui_merge_id(uimanager);
		pui->group = add_plugin_category(pui->get_category());
		pui->toolitem->reparent(*pui->group);
		add_plugin_menu_entry(pui);
	    }
	}
    }
}

void MainWindow::on_ladspa_finished(bool reload, bool quit) {
    if (reload) {
	machine.commit_ladspa_changes();
    }
    if (quit) {
	Glib::signal_idle().connect(sigc::mem_fun(this, &MainWindow::delete_ladspalist_window));
    }
}

bool MainWindow::delete_ladspalist_window() {
    if (ladspalist_window) {
    //ladspalist_window->hide();
	delete ladspalist_window;
	ladspalist_window = 0;
    }
    return false;
}

void MainWindow::on_load_ladspa() {
    if (ladspalist_window) {
	ladspalist_window->present();
    } else {
	ladspalist_window = new ladspa::PluginDisplay(machine, gx_head_icon, sigc::mem_fun(this, &MainWindow::on_ladspa_finished));
    }
}

void MainWindow::add_plugin(std::vector<PluginUI*>& p, const char *id, const Glib::ustring& tooltip) {
    if (PluginUI::is_registered(machine, id)) {
	return;
    }
    p.push_back(new PluginUI(*this, id, tooltip));
}

#ifdef accel_keys_for_plugins
struct accel_search {
    unsigned int key;
    bool res;
};

static void accel_search_callback(gpointer data, const gchar *accel_path, guint accel_key, GdkModifierType accel_mods, gboolean changed) {
    accel_search *s = static_cast<accel_search*>(data);
    if (accel_key == s->key && accel_mods == 0) {
	s->res = true;
    }
}

static bool accel_map_has_key(unsigned int accel_key) {
    accel_search s;
    s.key = accel_key;
    s.res = false;
    gtk_accel_map_foreach_unfiltered(gpointer(&s), accel_search_callback);
    return s.res;
}

static bool accel_map_next_key(unsigned int *accel_key) {
    while (*accel_key <= GDK_z) {
	if (!accel_map_has_key(*accel_key)) {
	    return true;
	}
	*accel_key += 1;
    }
    return false;
}
#endif

struct PluginDesc {
    Glib::ustring group;
    std::vector<PluginUI*> *plugins;
    PluginDesc(const Glib::ustring& g, std::vector<PluginUI*> *p)
	: group(g), plugins(p) {}
};

Gtk::ToolItemGroup *MainWindow::add_plugin_category(const char *group, bool collapse) {
    std::map<Glib::ustring, Gtk::ToolItemGroup*>::iterator it = groupmap.find(group);
    if (it != groupmap.end()) {
	return it->second;
    }
    Glib::ustring ui_template =
	"<menubar><menu action=\"PluginsMenu\"><menu action=\"%1Plugins\"><menu action=\"%2\">"
	"</menu></menu></menu></menubar>";
    Glib::ustring groupname = Glib::ustring::compose("PluginCategory_%1", group);
    uimanager->add_ui_from_string(Glib::ustring::compose(ui_template, "Mono", groupname));
    uimanager->add_ui_from_string(Glib::ustring::compose(ui_template, "Stereo", groupname));
    actions.group->add(Gtk::Action::create(groupname, gettext(group)));
    Gtk::ToolItemGroup *gw = new Gtk::ToolItemGroup(gettext(group));
    groupmap[group] = gw;
    gw->set_collapsed(collapse);
    effects_toolpalette->add(*manage(gw));
    effects_toolpalette->set_exclusive(*gw, true);
    effects_toolpalette->set_expand(*gw, true);
    return gw;
}

Glib::ustring MainWindow::add_plugin_menu_entry(PluginUI *pui) {
    Glib::ustring ui_template =
	"<menubar><menu action=\"PluginsMenu\"><menu action=\"%1Plugins\"><menu action=\"%2\">"
	"<menuitem action=\"%3\"/>"
	"</menu></menu></menu></menubar>";
    const char *group = pui->get_category();
    Glib::ustring groupname = Glib::ustring::compose("PluginCategory_%1", group);
    Glib::ustring actionname = Glib::ustring::compose("Plugin_%1", pui->get_id());
    const char *tp = (pui->get_type() == PLUGIN_TYPE_MONO ? "Mono" : "Stereo");
    pui->set_ui_merge_id(uimanager->add_ui_from_string(Glib::ustring::compose(ui_template, tp, groupname, actionname)));
    //fprintf(stderr, "%s : %s : %s \n", tp, group, pui->get_name());
    return actionname;
}

void MainWindow::register_plugin(PluginUI *pui) {
    plugin_dict.add(pui);
    Gtk::ToolItemGroup *gw = add_plugin_category(pui->get_category());
    Glib::ustring actionname = add_plugin_menu_entry(pui);
    add_toolitem(*pui, gw);
    Glib::RefPtr<Gtk::ToggleAction> act = Gtk::ToggleAction::create(actionname, pui->get_name());
    actions.group->add(act);
#ifdef accel_keys_for_plugins
    unsigned int key = GDK_a;
    if (accel_map_next_key(&key)) {
	Gtk::AccelMap::add_entry(act->get_accel_path(), key, Gdk::ModifierType(0));
	++key;
    }
#endif
    if (pui->rackbox && pui->rackbox->get_box_visible()) {
	act->set_active(true);
    }
    pui->set_action(act);
}

void MainWindow::fill_pluginlist() {
    // define order of categories by registering
    // them first
    add_plugin_category(N_("Tone control"), false);
    add_plugin_category(N_("Distortion"));
    add_plugin_category(N_("Fuzz"));
    add_plugin_category(N_("Reverb"));
    add_plugin_category(N_("Echo / Delay"));
    add_plugin_category(N_("Modulation"));
    add_plugin_category(N_("Guitar Effects"));
    add_plugin_category(N_("Misc"));

    std::vector<PluginUI*> p;
    p.push_back(new JConvPluginUI(*this, "jconv"));
    p.push_back(new JConvPluginUI(*this, "jconv_mono"));

    gx_gui::UiBuilderImpl builder(this, &boxbuilder, &p);
    machine.pluginlist_append_rack(builder);

    std::sort(p.begin(), p.end(), plugins_by_name_less);
    for (std::vector<PluginUI*>::iterator v = p.begin(); v != p.end(); ++v) {
	register_plugin(*v);
    }
}

// start_jack() returns:
// 1:  success
// 0:  fail
// -1: no start command configured
int MainWindow::start_jack() {
    gx_jack::GxJack *jack = machine.get_jack();
    if (!jack) {
	return -1;
    }
    int wait_after_connect = 0;
    gx_engine::EnumParameter& jack_starter = machine.get_parameter("ui.jack_starter_idx").getEnum();
    string v_id = jack_starter.get_pair().value_id;
    if (v_id == "autostart") {
	return jack->gx_jack_connection(true, true, wait_after_connect, options) ? 1 : 0;
    }
    string cmd;
    if (v_id == "other") {
	cmd = machine.get_parameter("ui.jack_starter").getString().get_value();
	if (cmd.empty()) {
	    return -1;
	}
    } else if (v_id == "qjackctl") {
	wait_after_connect = 500000;
	cmd = "qjackctl --start";
    } else {
	assert(false);
    }
    gx_system::gx_system_call(cmd, true, true);
    for (int i = 0; i < 10; i++) {
	if (jack->gx_jack_connection(true,false,wait_after_connect, options)) {
	    return 1;
	}
	usleep(500000);
    }
    gx_print_error(
	_("main"),
	string(_("I really tried to get jack up and running, sorry ... ")));
    return 0;
}

bool MainWindow::connect_jack(bool v, Gtk::Window *splash) {
    gx_jack::GxJack *jack = machine.get_jack();
    if (!jack) {
	return false;
    }
    if (jack->gx_jack_connection(v, false, 0, options)) {
	return true;
    }
    if (!v) {
	gx_print_error(_("main"), _("can't disconnect jack"));
	return false;
    }
    bool ask = machine.get_parameter_value<bool>("ui.ask_for_jack_starter");
    if (!ask) {
	switch (start_jack()) {
	case 1: return true;   // connected
	case -1: return false; // no starter, do nothing
	default: break;        // failed, ask user
	}
    }
    if (splash) {
	splash->hide();
    }
    if (!gx_gui::gx_start_jack_dialog(gx_head_icon)) {
	gx_print_warning(_("main"), string(_("Ignoring jackd ...")));
	return false;
    }
    return start_jack() == 1;
}

void MainWindow::on_jack_client_changed() {
    if (!window) {
	return;
    }
    gx_jack::GxJack *jack = machine.get_jack();
    if (!jack) {
	return;
    }
    bool v = (jack->client != 0);
    if (!v) {
        gx_child_process::Meterbridge::stop(); //FIXME
    }
    actions.jackserverconnection->set_active(v);
    Glib::ustring s = "Guitarix: ";
    if (v) {
	s += jack->get_instancename();
    } else {
	s += "("+jack->get_instancename()+")";
    }
    window->set_title(s);
    actions.jack_latency_menu->set_sensitive(v);
    actions.engine_mute->set_sensitive(v);
    actions.engine_bypass->set_sensitive(v);
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
	actions.engine_mute_conn.block();
	actions.engine_mute->set_active(true);
	actions.engine_mute_conn.unblock();
	status_image->set(pixbuf_off);
	machine.msend_midi_cc(0xB0,120,127,3);
	break;
    case gx_engine::kEngineOn:
	actions.engine_mute_conn.block();
	actions.engine_bypass_conn.block();
	actions.engine_mute->set_active(false);
	actions.engine_bypass->set_active(false);
	actions.engine_mute_conn.unblock();
	actions.engine_bypass_conn.unblock();
	status_image->set(pixbuf_on);
	machine.msend_midi_cc(0xB0,120,0,3);
	break;
    case gx_engine::kEngineBypass:
	actions.engine_mute_conn.block();
	actions.engine_bypass_conn.block();
	actions.engine_mute->set_active(false);
	actions.engine_bypass->set_active(true);
	actions.engine_mute_conn.unblock();
	actions.engine_bypass_conn.unblock();
	status_image->set(pixbuf_bypass);
	break;
    }
}

void MainWindow::set_tuning(Gxw::RackTuner& tuner) {
    static struct TuningTab {
	const char *name;
	const char* key;
	bool flat;
	int notes[6];
    } tuning_tab[] = {
	{ "Standard",             "E",  false, {40, 45, 50, 55, 59, 64}},
	{ "Standard/Es",          "Es", true,  {39, 44, 49, 54, 58, 63}},
	{ "Open E",               "E",  false, {40, 47, 52, 56, 59, 64}},
    { "Drop D",               "D",  false, {38, 45, 50, 55, 59, 64}},
    { "Half Step Down",       "E",  false, {39, 44, 49, 54, 58, 63}},
    { "Full Step Down",       "D",  false, {38, 43, 48, 53, 57, 62}},
    { "1 and 1/2 Steps Down", "E",  false, {37, 42, 47, 52, 56, 61}},
    { "Double Drop D",        "D",  false, {38, 45, 50, 55, 59, 62}},
    { "Drop C",               "C",  false, {36, 43, 48, 53, 57, 62}},
    { "Drop C#",              "C#", false, {37, 44, 49, 54, 58, 63}},
    { "Drop B",               "B",  false, {35, 42, 47, 52, 56, 61}},
    { "Drop A#",              "A#", false, {34, 41, 46, 51, 55, 60}},
    { "Drop A",               "A",  false, {33, 40, 45, 50, 54, 59}},
    { "Open D",               "D",  false, {38, 45, 50, 54, 57, 62}},
    { "Open D Minor",         "D",  false, {38, 45, 50, 53, 57, 62}},
    { "Open G",               "G",  false, {38, 43, 50, 55, 59, 62}},
    { "Open G Minor",         "G",  false, {38, 43, 50, 55, 58, 62}},
    { "Open C",               "C",  false, {36, 43, 48, 55, 60, 64}},
    { "Open C#",              "C#", false, {37, 42, 59, 52, 56, 61}},
    { "Open C Minor",         "C",  false, {36, 43, 48, 55, 60, 63}},
    { "Open E7",              "E7", false, {40, 44, 50, 52, 59, 64}},
    { "Open E Minor7",        "E",  false, {40, 47, 50, 55, 59, 64}},
    { "Open G Major7",        "G",  false, {38, 43, 50, 54, 59, 62}},
    { "Open A Minor",         "A",  false, {40, 45, 52, 57, 60, 64}},
    { "Open A Minor7",        "A",  false, {40, 45, 52, 55, 60, 64}},
    { "Open A",               "A",  false, {40, 45, 49, 52, 57, 64}},
    { "C Tuning",             "C",  false, {36, 41, 46, 51, 55, 60}},
    { "C# Tuning",            "C#", false, {37, 42, 47, 52, 56, 61}},
    { "Bb Tuning",            "Bb", false, {34, 39, 44, 49, 53, 58}},
    { "A to A (Baritone)",    "A",  false, {33, 38, 43, 48, 52, 57}},
    { "Open Dsus2",           "D",  false, {38, 45, 50, 55, 57, 62}},
    { "Open Gsus2",           "G",  false, {38, 43, 50, 55, 60, 62}},
    { "G6",                   "G6", false, {38, 43, 50, 55, 59, 64}},
    { "Modal G",              "G",  false, {38, 43, 50, 55, 60, 62}},
    { "Overtone",             "E",  false, {48, 52, 55, 58, 60, 62}},
    { "Pentatonic",           "E",  false, {45, 48, 50, 52, 55, 69}},
    { "Minor Third",          "E",  false, {48, 51, 54, 57, 60, 63}},
    { "Major Third",          "E",  false, {48, 52, 56, 60, 64, 68}},
    { "All Fourths",          "E",  false, {40, 45, 50, 55, 60, 65}},
    { "Augmented Fourths",    "E",  false, {36, 42, 48, 54, 60, 66}},
    { "Slow Motion",          "E",  false, {38, 43, 50, 53, 60, 62}},
    { "Admiral",              "E",  false, {36, 43, 50, 55, 59, 60}},
    { "Buzzard",              "E",  false, {36, 41, 48, 55, 58, 65}},
    { "Face",                 "E",  false, {36, 43, 50, 55, 57, 62}},
    { "Four and Twenty",      "E",  false, {38, 45, 50, 50, 57, 62}},
    { "Ostrich",              "E",  false, {38, 50, 50, 50, 62, 62}},
    { "Capo 200",             "E",  false, {36, 43, 50, 51, 62, 63}},
    { "Balalaika",            "E",  false, {40, 45, 50, 52, 52, 57}},
    { "Cittern One",          "E",  false, {36, 41, 48, 55, 60, 62}},
    { "Cittern Two",          "E",  false, {36, 43, 48, 55, 60, 67}},
    { "Dobro",                "E",  false, {43, 47, 50, 55, 59, 62}},
    { "Lefty",                "E",  false, {64, 59, 55, 50, 45, 40}},
    { "Mandoguitar",          "E",  false, {36, 43, 50, 57, 64, 71}},
    { "Rusty Cage",           "E",  false, {35, 45, 50, 55, 59, 64}},
    { "Hardcore",             "C",  false, {36, 43, 48, 53, 57, 58}},
    };
    int mode = tuner_tuning->get_value();
    tuner.clear_notes();
    if (mode > 0) {
	tuner.set_display_flat(tuning_tab[mode-1].flat);
	for (int i = 0; i < 6; ++i) {
	    tuner.push_note(tuning_tab[mode-1].notes[i], 69, 12);
	}
    } else {
	tuner.set_display_flat(false);
    }
}

void MainWindow::setup_tuner_temperament(Gxw::RackTuner& tuner) {
    tuner.set_temperament(tuner_temperament->get_value());
    set_tuning(tuner);

}

void MainWindow::setup_tuner(Gxw::RackTuner& tuner) {
    tuner.signal_frequency_poll().connect(
	sigc::compose(
	    sigc::mem_fun(tuner, &Gxw::RackTuner::set_freq),
	    sigc::mem_fun(machine, &gx_engine::GxMachineBase::get_tuner_freq)));
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
    tuner_temperament->signal_value_changed().connect(
        sigc::bind(sigc::mem_fun(*this, &MainWindow::setup_tuner_temperament), sigc::ref(tuner)));
	
}

bool MainWindow::on_toggle_mute(GdkEventButton* ev) {
    if (ev->type == GDK_BUTTON_PRESS && ev->button == 1) {
	if (machine.get_state() == gx_engine::kEngineOff) {
	    machine.set_state(gx_engine::kEngineOn);
	} else {
	    machine.set_state(gx_engine::kEngineOff);
	}
    }
    return true;
}

void MainWindow::on_msg_level_changed() {
    switch (fLoggingWindow.get_unseen_msg_level()) {
    case GxLogger::kWarning: logstate_image->set(pixbuf_log_yellow); break;
    case GxLogger::kError:   logstate_image->set(pixbuf_log_red); break;
    default:                 logstate_image->set(pixbuf_log_grey); break;
    }
}

static void toggle_action(Glib::RefPtr<Gtk::ToggleAction> act) {
    act->set_active(!act->get_active());
}

void MainWindow::on_ampdetail_switch(bool compress, bool setparam) {
    if (compress) {
	ampdetail_normal->hide();
	ampdetail_mini->show();
    } else {
	ampdetail_mini->hide();
	ampdetail_normal->show();
    }
    if (setparam) {
	machine.set_parameter_value("ui.mp_s_h", compress);
    }
}

/****************************************************************
 ** oscilloscope handling
 */

void MainWindow::set_osc_size() {
    //int osc_size = engine.oscilloscope.get_mul_buffer();
    if (options.mul_buffer > 0) {
        actions.osc_buffer_size->set_current_value(options.mul_buffer);
    }
}

void MainWindow::change_osc_buffer(Glib::RefPtr<Gtk::RadioAction> action) {
    gx_jack::GxJack *jack = machine.get_jack();
    if (!jack || jack->client) {
	options.mul_buffer = action->get_current_value();
	on_oscilloscope_activate(false);
	machine.set_oscilloscope_mul_buffer(options.mul_buffer);
	on_oscilloscope_activate(true);
    } else {
	set_osc_size();
    }
}

void MainWindow::add_osc_size_menu() {
    Glib::ustring s = "<menubar><menu action=\"OptionsMenu\"><menu action=\"OscBuffer\">";
    Gtk::RadioButtonGroup group;
    int osc_buffer_size = 1;
    for (int i = 1; i <= 6; ++i) {
	Glib::ustring name = "*" + gx_system::to_string(osc_buffer_size);
	Glib::ustring actname = Glib::ustring::compose("buffer size %1", name);
	s += Glib::ustring::compose("<menuitem action=\"%1\"/>", actname);
	Glib::RefPtr<Gtk::RadioAction> action = Gtk::RadioAction::create(group, actname, name);
	actions.group->add(action);
	if (i == 1) {
	    action->signal_changed().connect(
		sigc::mem_fun(*this, &MainWindow::change_osc_buffer));
	    actions.osc_buffer_size = action;
	}
	action->property_value().set_value(osc_buffer_size);
    osc_buffer_size++;
    }
    s.append("</menu></menu></menubar>");
    uimanager->add_ui_from_string(s);
}

void MainWindow::on_show_oscilloscope(bool v) {
    if (v) {
	// FIXME G_PRIORITY_DEFAULT_IDLE??
	Glib::signal_timeout().connect(
	    sigc::mem_fun(*this, &MainWindow::on_refresh_oscilloscope), 60);
    }
}

void MainWindow::set_waveview_buffer(unsigned int size) {
    fWaveView.set_frame(machine.get_oscilloscope_buffer(), size);
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
	machine.clear_oscilloscope_buffer();
	fWaveView.queue_draw();
    }
    return 0;
}

bool MainWindow::on_refresh_oscilloscope() {
    int load, frames;
    bool is_rt;
    jack_nframes_t bsize;
    machine.get_oscilloscope_info(load, frames, is_rt, bsize);
    static struct  {
        int load, frames;
        jack_nframes_t bsize;
        bool rt;
    } oc;
    if (!oc.bsize || oc.load != load) {
        oc.load = load;
        fWaveView.set_text(
            (boost::format(_("dsp load  %1% %%")) % oc.load).str().c_str(),
            Gtk::CORNER_TOP_LEFT);
    }
    if (!oc.bsize || oc.frames != frames) {
        oc.frames = frames;
        fWaveView.set_text(
            (boost::format(_("ht frames %1%")) % oc.frames).str().c_str(),
            Gtk::CORNER_BOTTOM_LEFT);
    }
    if (!oc.bsize || oc.rt != is_rt) {
        oc.rt = is_rt;
        fWaveView.set_text(
            oc.rt ? _("RT mode  yes ") : _("RT mode  <span color=\"#cc1a1a\">NO</span>"),
            Gtk::CORNER_BOTTOM_RIGHT);
    }
    if (!oc.bsize || oc.bsize != bsize) {
	oc.bsize = bsize;
        fWaveView.set_text(
            (boost::format(_("latency    %1%")) % oc.bsize).str().c_str(),
            Gtk::CORNER_TOP_RIGHT);
    }
    fWaveView.queue_draw();
    return machine.oscilloscope_plugin_box_visible();
}

/* --------- calculate power (percent) to decibel -------- */
// Note: could use fast_log10 (see ardour code) to make it faster
inline float power2db(float power) {
    return  20.*log10(power);
}

bool MainWindow::refresh_meter_level(float falloff) {
    const unsigned int channels = sizeof(fastmeter)/sizeof(fastmeter[0]);
    gx_jack::GxJack *jack = machine.get_jack();
    if (jack && !jack->client) {
	return true;
    }

    // Note: removed RMS calculation, we will only focus on max peaks
    static float old_peak_db[channels] = {-INFINITY, -INFINITY};

    // fill up from engine buffers
    float level[channels];
    machine.maxlevel_get(channels, level);
    for (unsigned int c = 0; c < channels; c++) {
	// update meters (consider falloff as well)
	// calculate peak dB and translate into meter
	float peak_db = -INFINITY;
	if (level[c] > 0) {
	    peak_db = power2db(level[c]);
	}
	// retrieve old meter value and consider falloff
	if (peak_db < old_peak_db[c]) {
	    peak_db = max(peak_db, old_peak_db[c] - falloff);
	}
	fastmeter[c]->set(log_meter(peak_db));
	old_peak_db[c] = peak_db;
    }
    return true;
}

bool MainWindow::survive_jack_shutdown() {
    gx_jack::GxJack *jack = machine.get_jack();
    if (!jack) {
	return false;
    }
    // return if jack is not down
    if (gx_system::gx_system_call("pgrep jackd", true) == SYSTEM_OK) {
        if (jack->is_jack_down()) {
        sleep(2);
	    jack->set_jack_down(false);
	}
	// let's make sure we get out of here
	gx_print_warning("Jack Shutdown",
				    _("jack has bumped us out!!   "));
	actions.jackserverconnection->set_active(true);
	// run only one time whem jackd is running
	return false;
    } else if (!jack->is_jack_down()) {
        // refresh some stuff. Note that it can be executed
        // more than once, no harm here
        actions.jackserverconnection->set_active(false);
        jack->set_jack_down(true);
	gx_print_error("Jack Shutdown",
				  _("jack has bumped us out!!   "));
    }
    // run as long jackd is down
    return true;
}

void MainWindow::gx_jack_is_down() {
    actions.jackserverconnection->set_active(false);
    Glib::signal_timeout().connect(
	sigc::mem_fun(*this, &MainWindow::survive_jack_shutdown),
	200, Glib::PRIORITY_LOW);
}

#ifdef HAVE_JACK_SESSION
void MainWindow::jack_session_event() {
    gx_jack::GxJack *jack = machine.get_jack();
    if (!jack) {
	return;
    }
    const char *statefile = "gx_head.state";
    jack_session_event_t *event = jack->get_last_session_event();
    set_in_session();
    machine.set_statefilename(string(event->session_dir) + statefile);
    machine.save_to_state();

#ifndef NDEBUG
    string cmd(options.get_path_to_program());
#else
    string cmd("guitarix");
#endif
    cmd += " -U ";
    cmd += event->client_uuid;
    cmd += " -A ";
    cmd += jack->get_uuid_insert();
    cmd += " -f ${SESSION_DIR}";
    cmd += statefile; // no space after SESSION_DIR
    event->command_line = strdup(cmd.c_str());

    JackSessionEventType tp = event->type;
    if (jack->return_last_session_event() == 0) {
	if (tp == JackSessionSaveAndQuit) {
	    GxExit::get_instance().exit_program("** session exit **");
	}
    }
}

void MainWindow::jack_session_event_ins() {
    gx_jack::GxJack *jack = machine.get_jack();
    if (!jack) {
	return;
    }
    jack_session_event_t *event = jack->get_last_session_event_ins();
    set_in_session();
    event->command_line = strdup("true ${SESSION_DIR}");
    JackSessionEventType tp = event->type;
    if (jack->return_last_session_event_ins() == 0) {
	if (tp == JackSessionSaveAndQuit) {
	    GxExit::get_instance().exit_program("** session exit **");
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
	machine.disable_autosave(true);
    }
}

void MainWindow::systray_menu(guint button, guint32 activate_time) {
    Gtk::Menu *menu = dynamic_cast<Gtk::MenuItem*>(uimanager->get_widget("/menubar/EngineMenu"))->get_submenu();
    menu->popup(2, gtk_get_current_event_time());
}

void MainWindow::overload_status_changed(gx_engine::MidiAudioBuffer::Load l) {
    switch (l) {
    case gx_engine::MidiAudioBuffer::load_low:
	status_icon->set(gx_head_midi);
	break;
    case gx_engine::MidiAudioBuffer::load_off:
    case gx_engine::MidiAudioBuffer::load_high:
	status_icon->set(gx_head_icon);
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
	window->get_window()->get_root_origin(options.mainwin_x, options.mainwin_y);
    }
    return false;
}

void MainWindow::hide_extended_settings() {
    if (!is_visible ||
	(window->get_window()->get_state()
	 & (Gdk::WINDOW_STATE_ICONIFIED|Gdk::WINDOW_STATE_WITHDRAWN))) {
        window->move(options.mainwin_x, options.mainwin_y);
        window->present();
        //window->deiconify();
    } else {
        window->hide();
        //window->iconify();
    }
}

//bool MainWindow::ui_sleep() {
//    usleep(1900);
    //cout<<"timeout"<<endl;
//    return true;
//}

void MainWindow::run() {
    int port = options.get_rpcport();
    if (machine.get_jack() && port != RPCPORT_DEFAULT && port != RPCPORT_NONE) {
	machine.start_socket(sigc::ptr_fun(Gtk::Main::quit), options.get_rpcaddress(), port);
	window->show();
    if (options.get_liveplaygui()) liveplay_button->set_active();
	Gtk::Main::run();
    } else {
	window->show();
    if (options.get_liveplaygui()) liveplay_button->set_active();
   // Glib::signal_timeout().connect (mem_fun (*this, &MainWindow::ui_sleep), 2);
	Gtk::Main::run();
    }
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

void MainWindow::display_preset_msg(const Glib::ustring& bank, const Glib::ustring& preset) {
    preset_status->set_text(bank + " / " + preset);
}

bool MainWindow::on_key_press_event(GdkEventKey *event) {
    if ((event->state & Gtk::AccelGroup::get_default_mod_mask()) != 0) {
	return false;
    }
    if (event->keyval >= GDK_KEY_0 && event->keyval <= GDK_KEY_9) {
	keyswitch.process_preset_key(event->keyval == GDK_KEY_0 ? 9 : event->keyval - GDK_KEY_1);
	return true;
    }
    if (event->keyval >= GDK_KEY_KP_0 && event->keyval <= GDK_KEY_KP_9) {
	keyswitch.process_preset_key(event->keyval == GDK_KEY_KP_0 ? 9 : event->keyval - GDK_KEY_KP_1);
	return true;
    }
    if (event->keyval >= GDK_KEY_a && event->keyval <= GDK_KEY_z) {
	keyswitch.process_bank_key(event->keyval - GDK_KEY_a);
	return true;
    }
    return false;
}

bool MainWindow::on_quit() {
    if (ladspalist_window && !ladspalist_window->check_exit()) {
	return true;
    }
    machine.stop_socket();
    Gtk::Main::quit();
    return false;
}

void MainWindow::amp_controls_visible(Gtk::Range *rr) {
    //FIXME
    bool v = abs(rr->get_value() - machine.get_parameter("tube.select").getUpperAsFloat()) < 0.5;
    const char *knobs[] = {"gxbigknob1","gxbigknob2","gxbigknob3"};
    for (unsigned int i = 0; i < sizeof(knobs)/sizeof(knobs[0]); ++i) {
	Gtk::Widget *w;
	bld->find_widget(knobs[i], w);
	w->set_visible(!v);
    }
}

MainWindow::MainWindow(gx_engine::GxMachineBase& machine_, gx_system::CmdlineOptions& options_,
		       Gtk::Window *splash, const Glib::ustring& title)
    : sigc::trackable(),
      options(options_),
      machine(machine_),
      bld(),
      freezer(),
      plugin_dict(),
      oldpos(0),
      scrl_size_x(-1),
      scrl_size_y(-1),
      monorackcontainer(PLUGIN_TYPE_MONO, *this),
      stereorackcontainer(PLUGIN_TYPE_STEREO, *this),
      pre_act(false),
      is_visible(false),
      drag_icon(0),
      preset_list_menu_bank(),
      preset_list_merge_id(0),
      preset_list_actiongroup(),
      uimanager(),
      live_play(),
      preset_window(),
      fWaveView(),
      convolver_filename_label(),
      convolver_mono_filename_label(),
      gx_head_icon(Gdk::Pixbuf::create_from_file(options.get_pixmap_filepath("gx_head.png"))),
      boxbuilder(machine_, fWaveView, convolver_filename_label, convolver_mono_filename_label, gx_head_icon),
      portmap_window(0),
      select_jack_control(0),
      fLoggingWindow(),
      amp_radio_menu(machine_, "tube.select"),
      pixbuf_on(Gdk::Pixbuf::create_from_file(options.get_pixmap_filepath("gx_on.png"))),
      pixbuf_off(Gdk::Pixbuf::create_from_file(options.get_pixmap_filepath("gx_off.png"))),
      pixbuf_bypass(Gdk::Pixbuf::create_from_file(options.get_pixmap_filepath("gx_bypass.png"))),
      pixbuf_jack_connected(Gdk::Pixbuf::create_from_file(options.get_pixmap_filepath("jackd_on.png"))),
      pixbuf_jack_disconnected(Gdk::Pixbuf::create_from_file(options.get_pixmap_filepath("jackd_off.png"))),
      pixbuf_log_grey(Gdk::Pixbuf::create_from_file(options.get_pixmap_filepath("gx_log_grey.png"))),
      pixbuf_log_yellow(Gdk::Pixbuf::create_from_file(options.get_pixmap_filepath("gx_log_yellow.png"))),
      pixbuf_log_red(Gdk::Pixbuf::create_from_file(options.get_pixmap_filepath("gx_log_red.png"))),
      in_session(false),
      status_icon(Gtk::StatusIcon::create(gx_head_icon)),
      gx_head_midi(Gdk::Pixbuf::create_from_file(options.get_pixmap_filepath("gx_head-midi.png"))),
      gx_head_warn(Gdk::Pixbuf::create_from_file(options.get_pixmap_filepath("gx_head-warn.png"))),
      actions(),
      keyswitch(machine, sigc::mem_fun(this, &MainWindow::display_preset_msg)),
      groupmap(),
      ladspalist_window(),
      szg_rack_units(Gtk::SizeGroup::create(Gtk::SIZE_GROUP_HORIZONTAL)) {

    convolver_filename_label.set_ellipsize(Pango::ELLIPSIZE_END);
    convolver_mono_filename_label.set_ellipsize(Pango::ELLIPSIZE_END);

    /*
    ** create actions and some parameters
    */
    create_actions();

    /*
    ** load key accelerator table and glade window definition
    **
    ** at this point all parameters that are used in the main window glade file must be defined
    */
    Gtk::AccelMap::load(options.get_builder_filepath("accels_rc"));

    const char *id_list[] = { "MainWindow", "amp_background:ampbox", "bank_liststore", "target_liststore",
			      "bank_combo_liststore", 0 };
    bld = gx_gui::GxBuilder::create_from_file(options_.get_builder_filepath("mainpanel.glade"), &machine, id_list);
    load_widget_pointers();
    rackcontainer->set_homogeneous(true); // setting it in glade is awkward to use with glade tool
    szg_rack_units->add_widget(*ampdetail_mini);
    szg_rack_units->add_widget(*ampdetail_normal);

    // remove marker labels from boxes (used in glade to make display clearer)
    clear_box(*monocontainer);
    clear_box(*stereorackcontainerH);
    clear_box(*stereorackcontainerV);
    clear_box(*preset_box_no_rack);

    // preset window also creates some actions
    preset_window = new PresetWindow(bld, machine, options, actions);

    // create uimanager and load menu
    uimanager = Gtk::UIManager::create();
    uimanager->insert_action_group(actions.group);
    uimanager->add_ui_from_file(options.get_builder_filepath("menudef.xml"));

    // add dynamic submenus
    if (!options.get_clear_rc()) {
        add_skin_menu();
    }
    add_latency_menu();
    add_osc_size_menu();
    amp_radio_menu.setup("<menubar><menu action=\"TubeMenu\">","</menu></menubar>",uimanager,actions.group);

    // add menubar, accelgroup and icon to main window
    Gtk::Widget *menubar = uimanager->get_widget("/menubar");
    actions.accels = uimanager->get_accel_group();
    menubox->pack_start(*menubar);
    window->add_accel_group(actions.accels);
    window->set_icon(gx_head_icon);
    boxbuilder.set_accelgroup(actions.accels);

    /*
    ** connect main window signals
    */
    window->signal_window_state_event().connect(
	sigc::mem_fun(*this, &MainWindow::on_window_state_changed));
    window->signal_delete_event().connect(
	sigc::hide(sigc::mem_fun(this, &MainWindow::on_quit)));
    window->signal_configure_event().connect_notify(
	sigc::mem_fun(*this, &MainWindow::on_configure_event));
    window->signal_visibility_notify_event().connect(
	sigc::mem_fun(*this, &MainWindow::on_visibility_notify));
    window->signal_key_press_event().connect(
	sigc::mem_fun(*this, &MainWindow::on_key_press_event));

    /*
    ** status icon signal connections
    */
    status_icon->signal_activate().connect(
	sigc::mem_fun(*this, &MainWindow::hide_extended_settings));
    status_icon->signal_popup_menu().connect(
	sigc::mem_fun(*this, &MainWindow::systray_menu));

    // add rack container
    stereorackcontainerV->pack_start(stereorackcontainer, Gtk::PACK_EXPAND_WIDGET);
    monocontainer->pack_start(monorackcontainer, Gtk::PACK_EXPAND_WIDGET);

    /*
    ** jack, engine, and controller_map signal connections and related settings
    */
    gx_jack::GxJack::rt_watchdog_set_limit(options.get_idle_thread_timeout());
    gx_jack::GxJack *jack = machine.get_jack();
    if (jack) {
	jack->shutdown.connect(sigc::mem_fun(*this, &MainWindow::gx_jack_is_down));
	jack->signal_buffersize_change().connect(
	    sigc::mem_fun(*this, &MainWindow::set_latency));
	jack->signal_client_change().connect(
	    sigc::mem_fun(*this, &MainWindow::on_jack_client_changed));
#ifdef HAVE_JACK_SESSION
	jack->session.connect(sigc::mem_fun(*this, &MainWindow::jack_session_event));
	jack->session_ins.connect(sigc::mem_fun(*this, &MainWindow::jack_session_event_ins));
	if (!options.get_jack_uuid().empty()) {
	    set_in_session();
	}
#endif
    }

    machine.signal_state_change().connect(
	sigc::mem_fun(*this, &MainWindow::on_engine_state_change));
    machine.signal_jack_load_change().connect(
	sigc::mem_fun(*this, &MainWindow::overload_status_changed));
    machine.signal_plugin_changed().connect(
	sigc::mem_fun(this, &MainWindow::on_plugin_changed));
    /*
    ** GxSettings signal connections
    */
    machine.signal_presetlist_changed().connect(
	sigc::mem_fun(*this, &MainWindow::rebuild_preset_menu));
    machine.signal_selection_changed().connect(
	sigc::mem_fun(*this, &MainWindow::show_selected_preset));
    machine.signal_selection_changed().connect(
	sigc::mem_fun(monorackcontainer, &RackContainer::check_order));
    machine.signal_selection_changed().connect(
	sigc::mem_fun(stereorackcontainer, &RackContainer::check_order));

    /*
    ** DnD setup for effects toolpalette
    */
    std::vector<Gtk::TargetEntry> listTargets;
    listTargets.push_back(Gtk::TargetEntry("application/x-guitarix-mono", Gtk::TARGET_SAME_APP, 1));
    listTargets.push_back(Gtk::TargetEntry("application/x-guitarix-stereo", Gtk::TARGET_SAME_APP, 2));
    effects_toolpalette->drag_dest_set(listTargets, Gtk::DEST_DEFAULT_ALL, Gdk::ACTION_MOVE);
    effects_toolpalette->signal_drag_data_received().connect(sigc::mem_fun(*this, &MainWindow::on_tp_drag_data_received));

    /*
    ** init jack connection image widget
    */
    if (jack) {
	jackd_image->set(pixbuf_jack_disconnected);
	jackd_image->get_parent()->signal_button_press_event().connect(
	    sigc::bind_return(
		sigc::group(
		    sigc::ptr_fun(toggle_action),
		    actions.jackserverconnection),
		true));
    } else {
	jackd_image->hide();
    }

    /*
    ** setup racktuner parameter and signals
    */
    setup_tuner(*racktuner);
    tuner_on_off->signal_toggled().connect(
	sigc::compose(
	    sigc::mem_fun(*racktuner, &Gxw::RackTuner::set_sensitive),
	    sigc::mem_fun(*tuner_on_off, &Gxw::Switch::get_active)));
    racktuner->signal_poll_status_changed().connect(
	sigc::mem_fun(machine, &gx_engine::GxMachineBase::tuner_used_for_display));

    /*
    ** oscilloscope signal connections
    */
    machine.signal_oscilloscope_post_pre().connect(
	sigc::mem_fun(*this, &MainWindow::on_oscilloscope_post_pre));
    machine.signal_oscilloscope_visible().connect(
	sigc::mem_fun(*this, &MainWindow::on_show_oscilloscope));
    machine.signal_oscilloscope_activation().connect(
	sigc::mem_fun(*this, &MainWindow::on_oscilloscope_activate));
    machine.signal_oscilloscope_size_change().connect(
	sigc::mem_fun(*this, &MainWindow::set_waveview_buffer));

    /*
    ** fastmeter initialization and signal connections
    */
    for (unsigned int i = 0; i < sizeof(fastmeter)/sizeof(fastmeter[0]); ++i) {
        fastmeter[i]->signal_button_release_event().connect(
            sigc::mem_fun(*this, &MainWindow::on_meter_button_release));
        fastmeter[i]->set_tooltip_text(_("gx_head output"));
    }
    const float meter_falloff = 27; // in dB/sec.
    const float meter_display_timeout = 60; // in millisec
    const float falloff = meter_falloff * meter_display_timeout * 0.001;
    Glib::signal_timeout().connect(
	sigc::bind(sigc::mem_fun(this, &MainWindow::refresh_meter_level), falloff),
	meter_display_timeout);

    /*
    ** amp top box signal connections
    */
    ampdetail_compress->signal_clicked().connect(
	sigc::bind(sigc::mem_fun(*this, &MainWindow::on_ampdetail_switch), true, true));
    ampdetail_expand->signal_clicked().connect(
	sigc::bind(sigc::mem_fun(*this, &MainWindow::on_ampdetail_switch), false, true));
    machine.signal_parameter_value<bool>("ui.mp_s_h").connect(
	sigc::bind(sigc::mem_fun(*this, &MainWindow::on_ampdetail_switch), false));

    /*
    ** midi out signal connections
    */
    midi_out_compress->signal_clicked().connect(
	sigc::bind(
	    sigc::mem_fun(actions.midi_out_plug.operator->(), &Gtk::ToggleAction::set_active),
	    true));
    midi_out_expand->signal_clicked().connect(
	sigc::bind(
	    sigc::mem_fun(actions.midi_out_plug.operator->(), &Gtk::ToggleAction::set_active),
	    false));
    midi_out_presets_mini->signal_clicked().connect(
	sigc::bind(
	    sigc::mem_fun1(this, &MainWindow::plugin_preset_popup),
	    machine.pluginlist_lookup_plugin("midi_out")->get_pdef()));
    midi_out_presets_normal->signal_clicked().connect(
	sigc::bind(
	    sigc::mem_fun1(this, &MainWindow::plugin_preset_popup),
	    machine.pluginlist_lookup_plugin("midi_out")->get_pdef()));
    channel1_button->signal_toggled().connect(
	sigc::bind(
	    sigc::mem_fun(this, &MainWindow::on_midi_out_channel_toggled),
	    channel1_button, channel1_box));
    channel2_button->signal_toggled().connect(
	sigc::bind(
	    sigc::mem_fun(this, &MainWindow::on_midi_out_channel_toggled),
	    channel2_button, channel2_box));
    channel3_button->signal_toggled().connect(
	sigc::bind(
	    sigc::mem_fun(this, &MainWindow::on_midi_out_channel_toggled),
	    channel3_button, channel3_box));

    /*
    ** init status image widget
    */
    status_image->set(pixbuf_on);
    gx_gui::connect_midi_controller(status_image->get_parent(), "engine.mute", machine);
    status_image->get_parent()->signal_button_press_event().connect(
	sigc::mem_fun(*this, &MainWindow::on_toggle_mute));
    on_engine_state_change(machine.get_state());

    /*
    ** connect buttons with actions
    */
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(show_rack_button->gobj()), GTK_ACTION(actions.show_rack->gobj()));
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(rack_order_h_button->gobj()), GTK_ACTION(actions.rackh->gobj()));
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(config_mode_button->gobj()), GTK_ACTION(actions.rack_config->gobj()));
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(liveplay_button->gobj()),GTK_ACTION(actions.live_play->gobj()));
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(tuner_button->gobj()),GTK_ACTION(actions.tuner->gobj()));
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(effects_button->gobj()), GTK_ACTION(actions.show_plugin_bar->gobj()));
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(presets_button->gobj()), GTK_ACTION(actions.presets->gobj()));
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(compress_button->gobj()), GTK_ACTION(actions.compress->gobj()));
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(expand_button->gobj()), GTK_ACTION(actions.expand->gobj()));

    /*
    ** setup window initial configuration
    */
    tunerbox->set_visible(machine.get_parameter_value<bool>("system.show_tuner"));
    racktuner->set_sensitive(machine.get_parameter_value<bool>("ui.racktuner"));
    actions.show_plugin_bar->set_active(false);

    /*
    ** create liveplay and setup liveplay racktuner
    */
    live_play = new Liveplay(options, machine, options.get_builder_filepath("mainpanel.glade"), actions);
    setup_tuner(live_play->get_tuner());
    live_play->get_tuner().signal_poll_status_changed().connect(
	sigc::mem_fun1(machine, &gx_engine::GxMachineBase::tuner_used_for_display));

    /*
    ** init logging window and logstate image widget
    */
    fLoggingWindow.set_transient_for(*window);
    fLoggingWindow.set_icon(gx_head_icon);
    fLoggingWindow.signal_msg_level_changed().connect(
	sigc::mem_fun(*this, &MainWindow::on_msg_level_changed));
    fLoggingWindow.signal_hide().connect(
	sigc::bind(
	    sigc::mem_fun(actions.loggingbox.operator->(), &Gtk::ToggleAction::set_active),
	    false));
    on_msg_level_changed();
    logstate_image->get_parent()->signal_button_press_event().connect(
	sigc::bind_return(
	    sigc::group(
		sigc::ptr_fun(toggle_action),
		actions.loggingbox),
	    true));

    /*
    ** load plugin definitions into plugin_dict, add to effects_toolpalette
    **
    ** icons will be added after state loading when we know the skin
    ** UI definitions will be loaded on demand
    */
    fill_pluginlist();
    PluginUI *mainamp_plugin = new PluginUI(*this, "ampstack");
    plugin_dict.add(mainamp_plugin);
    mainamp_plugin->rackbox = add_rackbox_internal(*mainamp_plugin, 0, 0, false, -1, false, amp_background);
    effects_toolpalette->show();
    if (!options.get_clear_rc()) {
		  //g_object_set (gtk_settings_get_default (),"gtk-theme-name",NULL, NULL);
          set_new_skin(options.skin_name);
    } else {
      gtk_rc_parse(
          (options.get_style_filepath("clear.rc")).c_str());
      make_icons();
    }

    // call some action functions to sync state
    // with settings defined in create_actions()
    actions.rackh->set_active(options.system_order_rack_h);
    actions.presets->set_active(options.system_show_presets);
    actions.show_plugin_bar->set_active(options.system_show_toolbar);
    actions.show_rack->set_active(options.system_show_rack);
    actions.show_values->set_active(options.system_show_value);
    actions.tooltips->set_active(options.system_show_tooltips);
    actions.animations->set_active(options.system_animations);

    if (!title.empty()) {
	window->set_title(title);
    }

    /*
    ** Jack client connection and subsequent initalizations
    */

    // state must be loaded before starting jack because connect_jack() uses
    // some settings. If the jack client name changes (from the predefined value)
    // on connect the jack client-change signal will trigger the load of another
    // state file, which means that the jack starter options are read from the
    // standard state file (gx_head_rc or similar if -n is used)
    machine.loadstate();
    if (!in_session) {
	machine.disable_autosave(options.get_opt_save_on_exit());
    }
    if (!connect_jack(true, splash)) {
	// not connected, must synthesize signal for initialization
	if (jack) {
	    jack->signal_client_change()();
	}
    }
    set_latency(); // make sure latency menu is updated
    set_osc_size();

    if (options.mainwin_height > 0) {  // initially use the default set in mainpanel.glade
	window->set_default_size(-1, min(options.window_height, options.mainwin_height));
    }

    // set window position (make this optional??)
    if (options.mainwin_x > 0) {
	window->move(options.mainwin_x, options.mainwin_y);
    }

    Gtk::Range *rr;
    bld->find_widget("gxselector1:amp_selector", rr);
    rr->signal_value_changed().connect(
	sigc::bind(
	    sigc::mem_fun(this, &MainWindow::amp_controls_visible),
	    rr));
    amp_controls_visible(rr);
}

MainWindow::~MainWindow() {
#if false   // set true to generate a new keyboard accel file
    gtk_accel_map_add_filter("<Actions>/Main/ChangeSkin_*");
    gtk_accel_map_add_filter("<Actions>/Main/Enum_tube.select.*");
    gtk_accel_map_add_filter("<Actions>/Main/Latency_*");
    gtk_accel_map_add_filter("<Actions>/Main/Plugin_*");
    gtk_accel_map_add_filter("<Actions>/PresetList/PresetList_*");
    Gtk::AccelMap::save(options.get_user_filepath("accels_rc"));
#endif

    int mainwin_width;
    window->get_size(mainwin_width, options.mainwin_height);
    Glib::RefPtr<Gdk::Window> win = window->get_window();
    if (win) {
	win->get_root_origin(options.mainwin_x, options.mainwin_y);
    }
    if (actions.presets->get_active()) {
	options.preset_window_height = preset_scrolledbox->get_allocation().get_height();
    }
    plugin_dict.cleanup();
    delete live_play;
    delete preset_window;
    delete window;
    window = 0;
    //if (ladspalist_window) {
	//delete ladspalist_window;
	//ladspalist_window = 0;
    //}
}
