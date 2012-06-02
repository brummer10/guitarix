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
    for (int i = 0; i < gx_system::kMessageTypeCount; i++) {
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
    gx_system::Logger::get_logger().signal_message().connect(
	sigc::mem_fun(*this, &TextLoggingBox::show_msg));
    gx_system::Logger::get_logger().unplug_queue();
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
    gx_system::gx_print_error("freezer", "timeout");
#else
    gx_system::gx_print_warning("freezer", "timeout");
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

template <class Param>
UiToggleAction<Param>::UiToggleAction(
    gx_ui::GxUI& ui_, Param& para, const Glib::ustring& name, const Glib::ustring& icon_name,
    const Glib::ustring& label, const Glib::ustring& tooltip,
    bool is_active)
    : Gtk::ToggleAction(name, icon_name, label, tooltip, is_active),
      gx_ui::GxUiItem(),
      param(para),
      ui(ui_)
{
    ui.registerZone(param.zone(), this);
    reflectZone();
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
      ui(ui_)
{
    ui.registerZone(param.zone(), this);
    reflectZone();
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
	req.height += preset_window_height - preset_scrolledbox->size_request().height;
    } else {
	req.height = std::max(req.height, window_height);
    }
    w->move_resize(x, y, req.width, req.height);
    if (!state) {
	freezer.freeze_until_width_update(window, req.width);
    }
}

void MainWindow::on_show_tuner() {
    bool v = actions.tuner->get_active();
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
    }
    if (!gx_settings.setting_is_preset()) {
	return;
    }
    gx_system::PresetFile *pf = gx_settings.get_current_bank_file();
    if (!pf) {
	return;
    }
    preset_list_actiongroup = Gtk::ActionGroup::create("PresetList");
    preset_list_menu_bank = gx_settings.get_current_bank();
    Glib::ustring s = "<menubar><menu action=\"PresetsMenu\"><menu action=\"PresetListMenu\">";
    int idx = 0;
    for (gx_system::PresetFile::iterator i = pf->begin(); i != pf->end(); ++i, ++idx) {
	Glib::ustring actname = "PresetList_" + i->name;
	Glib::RefPtr<Gtk::Action> action = Gtk::Action::create(actname, i->name);
	if (idx <= 9) {
	    char c = (idx == 9 ? '0' : '1'+idx);
	    preset_list_actiongroup->add(
		action, Gtk::AccelKey(Glib::ustring::compose("%1", c)),
		sigc::bind(sigc::mem_fun(*this, &MainWindow::on_select_preset), idx));
	} else {
	    preset_list_actiongroup->add(
		action, sigc::bind(sigc::mem_fun(*this, &MainWindow::on_select_preset), idx));
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
    if (gx_settings.setting_is_preset()) {
	t = gx_settings.get_current_bank() + " / " + gx_settings.get_current_name();
	if (preset_list_menu_bank != gx_settings.get_current_bank()) {
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
    int pos = main_vpaned->get_allocation().get_height() - preset_window_height - h;
    main_vpaned->set_position(pos);
}

void MainWindow::on_show_rack() {
    Gtk::Widget *w;
    if (rackbox_stacked_vertical()) {
	w = stereorackcontainerV;
    } else {
	w = stereorackbox;
    }
    bool v = actions.show_rack->get_active();
    actions.rackh->set_sensitive(v);
    rackcontainer->set_border_width(v ? 18 : 0); //FIXME (just experimental)
    stereorackcontainer.set_visible(v);
    rack_order_h_button->set_visible(v);
    compress_button->set_visible(v);
    expand_button->set_visible(v);
    if (actions.presets->get_active() && preset_scrolledbox->get_mapped()) {
	preset_window_height = preset_scrolledbox->get_allocation().get_height();
    }
    if (v) {
	midi_out_box->set_visible(actions.midi_out->get_active());
	window_height = max(window_height, window->size_request().height);
	main_vpaned->set_position(oldpos);
	w->show();
	monoampcontainer->show();
	monorackcontainer.show_entries();
	vrack_scrolledbox->set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_AUTOMATIC);
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
	    req.height = max(req.height, window_height);
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
    monorackcontainer.compress_all();
    stereorackcontainer.compress_all();
    on_ampdetail_switch(true);
    actions.midi_out_plug->set_active(true);
}

void MainWindow::on_expand_all() {
    monorackcontainer.expand_all();
    stereorackcontainer.expand_all();
    on_ampdetail_switch(false);
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
		width -= req2.width/2;
	    }
	}
	monobox->set_size_request(width,-1);
    } else {
	if (!plugin_bar) {
	    effects_frame_paintbox->hide();
	}
	upper_rackbox->show();
	monobox->set_size_request(-1,-1);
	if (pre_act) {
	    actions.presets->set_active(true);
	}
    }
    if (!plugin_bar) {
	update_scrolled_window(*vrack_scrolledbox);
	update_scrolled_window(*stereorackbox);
	maybe_shrink_horizontally();
    }
}

void MainWindow::on_show_plugin_bar() {
    bool v = actions.show_plugin_bar->get_active();
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
    if (actions.rackh->get_active()) {
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
	    window_height = ev->height;
	}
    }
}

void MainWindow::resize_finished(RackContainer *ch)
{
    if (ch == &monorackcontainer && !actions.rackh->get_active()) {
	stereorackcontainer.queue_draw();
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

void load_rack_ui(const std::string& fname, gx_ui::GxUI& ui, Gtk::Widget*& mainwidget, Gtk::Widget*& miniwidget) {
    const char *id_list[] = {"rackbox", "minibox", 0};
    Glib::RefPtr<gx_gui::GxBuilder> bld = gx_gui::GxBuilder::create_from_file(fname, &ui, id_list);
    bld->get_toplevel("rackbox", mainwidget);
    miniwidget = 0;
    if (bld->has_object("minibox")) {
	bld->get_toplevel("minibox", miniwidget);
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
	std::string gladefile = options.get_builder_filepath(
	    std::string(pl.get_id())+"_ui.glade");
	if (access(gladefile.c_str(), R_OK) == 0) {
	    load_rack_ui(gladefile, ui, mainwidget, miniwidget);
	}
    }
    if (!mainwidget) {
	gx_gui::UiBuilderImpl builder(this, &boxbuilder);
	if (builder.load_unit(pl)) {
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
    std::string s =
	"style \"ShowValue\" {\n"
	"  GxRegler::show-value = " + gx_system::to_string(actions.show_values->get_active()) + "\n"
	"}\n"
	"class \"*GxRegler*\" style:highest \"ShowValue\"\n";
    gtk_rc_parse_string(s.c_str());
    gtk_rc_reset_styles(gtk_settings_get_default());
}

void MainWindow::on_preset_action() {
    bool v = actions.presets->get_active();
    if (!v && preset_scrolledbox->get_mapped()) {
	preset_window_height = preset_scrolledbox->get_allocation().get_height();
    }
    maybe_change_resizable();
    if (v && !actions.show_rack->get_active()) {
	Glib::RefPtr<Gdk::Window> win = window->get_window();
	if (!win || win->get_state() == 0) {
	    Gtk::Requisition req;
	    window->size_request(req);
	    freezer.freeze_and_size_request(window, req.width, req.height+preset_window_height);
	}
    }
    preset_box_no_rack->set_visible(v);
    preset_window->on_preset_select(v, use_animations() && actions.show_rack->get_active(), preset_window_height);
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
    if (actions.jackports->get_active()) {
	if (portmap_window) {
	    return;
	}
	portmap_window = gx_portmap::PortMapWindow::create(jack, ui, actions.accels);
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
    gx_main_midi::MidiControllerTable::toggle(pmap, actions.midicontroller);
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
	actions.group->add(action);
	if (idx == 0) {
	    action->signal_changed().connect(
		sigc::mem_fun(*this, &MainWindow::change_skin));
	    actions.skin = action;
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
    pmap.reg_non_midi_par("ui.latency_nowarn", &no_warn_latency, false, false);
}

void MainWindow::set_latency() {
    jack_nframes_t n = jack.get_jack_bs();
    if (n > 0) {
	actions.latency->set_current_value(n);
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

    gx_gui::gx_message_popup(about.c_str());
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
    engine.set_state(s);
}

void MainWindow::set_switcher_controller() {
    if (!gx_engine::controller_map.get_config_mode()) {
	new gx_main_midi::MidiConnect(0, pmap["ui.live_play_switcher"]);
    }
}

void MainWindow::on_show_midi_out() {
#ifdef USE_MIDI_OUT
    if (actions.midi_out->get_active()) {
	actions.show_rack->set_active(true);
	midi_out_box->set_visible(true);
    } else {
	midi_out_box->set_visible(false);
	engine.midiaudiobuffer.plugin.on_off = false;
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

void MainWindow::create_actions() {
    actions.group = Gtk::ActionGroup::create("Main");
    /*
    ** Menu actions
    */
    actions.group->add(Gtk::Action::create("EngineMenu",_("_Engine")));
    actions.jack_latency_menu = Gtk::Action::create("JackLatency",_("_Latency"));
    actions.group->add(actions.jack_latency_menu);
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
    actions.group->add(
	actions.engine_mute,
	sigc::mem_fun(*this, &MainWindow::on_engine_toggled));

    actions.engine_bypass = Gtk::ToggleAction::create("EngineBypass", _("Engine _Bypass"));
    actions.group->add(
	actions.engine_bypass,
	sigc::mem_fun(*this, &MainWindow::on_engine_toggled));

    actions.quit = Gtk::Action::create("Quit",_("_Quit"));
    actions.group->add(
	actions.quit,
	sigc::hide_return(sigc::mem_fun(this, &MainWindow::on_quit)));

    /*
    ** actions to open other (sub)windows
    */
    actions.presets = UiSwitchToggleAction::create(
	ui, *pmap.reg_switch("system.show_presets", false, false), "Presets",_("_Preset Selection"));
    actions.group->add(actions.presets, 
		     sigc::mem_fun(*this, &MainWindow::on_preset_action));

    actions.show_plugin_bar = UiSwitchToggleAction::create(
	ui, *pmap.reg_switch("system.show_toolbar", false, false), "ShowPluginBar",_("Show Plugin _Bar"));
    actions.group->add(actions.show_plugin_bar,
		     sigc::mem_fun(*this, &MainWindow::on_show_plugin_bar));

    actions.show_rack = UiSwitchToggleAction::create(
	ui, *pmap.reg_switch("system.show_rack", false, false), "ShowRack",_("Show _Rack"));
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
    actions.group->add(
	actions.meterbridge,
	sigc::bind(sigc::ptr_fun(gx_child_process::Meterbridge::start_stop),
		   sigc::ref(actions.meterbridge), sigc::ref(jack)));

    actions.livetuner = UiBoolToggleAction::create(
	ui, *pmap.reg_par("ui.racktuner", N_("Tuner on/off"), (bool*)0, true, false), "LiveTuner", "??");

    actions.midi_out = UiBoolToggleAction::create(
	ui, gx_engine::parameter_map["ui.midi_out"].getBool(), "MidiOut", _("M_idi Out"));
    actions.group->add(
	actions.midi_out,
	sigc::mem_fun(this, &MainWindow::on_show_midi_out));

    actions.midi_out_plug = UiBoolToggleAction::create(
	ui, gx_engine::parameter_map["midi_out.s_h"].getBool(), "MidiOutSH", "??");
    actions.group->add(
	actions.midi_out_plug,
	sigc::mem_fun(this, &MainWindow::on_show_midi_out_plug));

    /*
    ** rack actions
    */
    actions.tuner = UiBoolToggleAction::create(
	ui, *pmap.reg_non_midi_par("system.show_tuner", (bool*)0, false), "Tuner",_("_Tuner"));
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

    actions.rackh = UiSwitchToggleAction::create(
	ui, *pmap.reg_switch("system.order_rack_h", false, false), "RackH", _("Order Rack _Horizontally"));
    actions.group->add(actions.rackh,
		     sigc::mem_fun(*this, &MainWindow::on_dir_changed));

    /*
    ** option actions
    */
    actions.show_values = UiSwitchToggleAction::create(
	ui, *pmap.reg_switch("system.show_value", false, false), "ShowValues",_("_Show _Values"));
    actions.group->add(actions.show_values,
		     sigc::mem_fun(*this, &MainWindow::on_show_values));

    actions.tooltips = UiSwitchToggleAction::create(
	ui, *pmap.reg_switch("system.show_tooltips", false, true), "ShowTooltips", _("Show _Tooltips"), "", true);
    actions.group->add(
	actions.tooltips,
	sigc::compose(sigc::ptr_fun(set_tooltips),
		      sigc::mem_fun(actions.tooltips.operator->(), &UiSwitchToggleAction::get_active)));

    actions.midi_in_presets = UiSwitchToggleAction::create(
	ui, *pmap.reg_switch("system.midi_in_preset", false, false), "MidiInPresets", _("Include MIDI in _presets"));
    actions.group->add(actions.midi_in_presets);

    actions.jackstartup = Gtk::Action::create("JackStartup", _("_Jack Startup Control"));
    actions.group->add(
	actions.jackstartup,
	sigc::mem_fun(*this, &MainWindow::on_select_jack_control));

    actions.loadladspa = Gtk::Action::create("LoadLADSPA", _("LADSPA Pl_ugins"));
    actions.group->add(
	actions.loadladspa,
	sigc::mem_fun(this, &MainWindow::on_load_ladspa));

    actions.group->add(Gtk::Action::create("ResetAll", _("Reset _All Parameters")),
		       sigc::mem_fun(pmap, &gx_engine::ParamMap::set_init_values));

    actions.animations = UiBoolToggleAction::create(
	ui, *pmap.reg_non_midi_par("system.animations", (bool*)0, false, true), "Animations", _("_Use Animations"),"",true);
    actions.group->add(actions.animations);

    pmap.reg_par("ui.live_play_switcher", "Liveplay preset mode" , (bool*)0, false, false)->setSavable(false);
    actions.group->add(Gtk::Action::create("SetPresetSwitcher", _("L_iveplay Midi Switch")),
		     sigc::mem_fun(this, &MainWindow::set_switcher_controller));
    pmap.reg_par_non_preset("ui.liveplay_brightness", "?liveplay_brightness", 0, 1.0, 0.5, 1.0, 0.01);
    pmap.reg_par_non_preset("ui.liveplay_background", "?liveplay_background", 0, 0.8, 0.0, 1.0, 0.01);

    /*
    ** Help and About
    */
    actions.group->add(Gtk::Action::create("Help", _("_Help")),
		     sigc::ptr_fun(gx_show_help));
    actions.group->add(Gtk::Action::create("About", _("_About")),
		     sigc::ptr_fun(gx_show_about));
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

void MainWindow::plugin_preset_popup(const std::string& id) {
    new PluginPresetPopup(id, gx_settings);
}

void MainWindow::plugin_preset_popup(const std::string& id, const Glib::ustring& name) {
    new PluginPresetPopup(id, gx_settings, name);
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
    gx_engine::ConvolverAdapter& conv;
    virtual void on_plugin_preset_popup();
public:
    JConvPluginUI(MainWindow& main, const gx_engine::PluginList& pl, const char* id,
		  gx_engine::ConvolverAdapter& conv_, const Glib::ustring& fname="",
		  const Glib::ustring& tooltip="")
	: PluginUI(main, pl, id, fname, tooltip), conv(conv_) {
    }
};

void JConvPluginUI::on_plugin_preset_popup() {
    Glib::ustring name = Glib::path_get_basename(conv.getIRFile());
    Glib::ustring::size_type n = name.find_last_of('.');
    if (n != Glib::ustring::npos) {
	name.erase(n);
    }
    main.plugin_preset_popup(get_id(), name);
}

static gx_engine::LadspaLoader::pluginarray::iterator find_plugin(gx_engine::LadspaLoader::pluginarray& ml, gx_engine::plugdesc *pl) {
    for (gx_engine::LadspaLoader::pluginarray::iterator i = ml.begin(); i != ml.end(); ++i) {
	if ((*i)->UniqueID == pl->UniqueID) {
	    return i;
	}
    }
    return ml.end();
}

void MainWindow::on_ladspa_finished(bool reload, bool quit) {
    if (reload) {
	typedef gx_engine::LadspaLoader::pluginarray pluginarray;
	pluginarray ml;
	// load plugindesc list
	engine.ladspaloader.load(options, ml);
	// look for removed and changed plugins
	std::vector<gx_engine::Plugin*> to_remove;
	for (pluginarray::iterator i = engine.ladspaloader.begin(); i != engine.ladspaloader.end(); ++i) {
	    PluginUI *pui = plugin_dict[(*i)->id_str];
	    pluginarray::iterator j = find_plugin(ml, *i);
	    if (j == ml.end()) {
		plugin_dict.remove(pui);
		pui->unset_ui_merge_id(uimanager);
		actions.group->remove(pui->get_action());
		delete pui;
		pui->plugin->on_off = false;
		to_remove.push_back(pui->plugin);
	    } else {
		engine.ladspaloader.update_instance(pui->plugin->pdef, *j);
		PluginDef *pd = pui->plugin->pdef;
		if (pd->register_params) {
		    pmap.set_replace_mode(true);
		    gx_engine::ParamRegImpl preg(&pmap);
		    preg.plugin = pd;
		    pd->register_params(preg);
		    pmap.set_replace_mode(false);
		}
		pui->update_rackbox();
		if ((*j)->category != (*i)->category) {
		    pui->unset_ui_merge_id(uimanager);
		    pui->group = add_plugin_category(pui->get_category());
		    pui->toolitem->reparent(*pui->group);
		    add_plugin_menu_entry(pui);
		}
	    }
	}
	// update engine for plugins to be removed
	engine.update_module_lists();
	engine.mono_chain.release();
	engine.stereo_chain.release();
	// remove plugins
	for (std::vector<gx_engine::Plugin*>::iterator i = to_remove.begin(); i != to_remove.end(); ++i) {
	    engine.pluginlist.delete_module(*i, pmap, gx_engine::get_group_table());
	}
	// add new plugins (engine)
	std::vector<PluginDef *> pv;
	for (pluginarray::iterator i = ml.begin(); i != ml.end(); ++i) {
	    if (engine.ladspaloader.find((*i)->UniqueID) == engine.ladspaloader.end()) {
		PluginDef *plugin = engine.ladspaloader.create(*i);
		if (plugin) {
		    engine.pluginlist.add(plugin);
		    pv.push_back(plugin);
		}
	    }
	}
	// update ladspaloader with new list
	engine.ladspaloader.set_plugins(ml);
	// add new plugins (UI)
	std::vector<PluginUI*> p;
	gx_gui::UiBuilderImpl builder(this, &boxbuilder, &p);
	engine.pluginlist.append_rack(builder);
	std::sort(p.begin(), p.end(), plugins_by_name_less);
	for (std::vector<PluginUI*>::iterator v = p.begin(); v != p.end(); ++v) {
	    register_plugin(*v);
	    engine.pluginlist.registerPlugin((*v)->plugin, pmap, gx_engine::get_group_table());
	}
	for (std::vector<PluginDef*>::iterator i = pv.begin(); i != pv.end(); ++i) {
	    (*i)->set_samplerate(engine.get_samplerate(), *i);
	}
	make_icons(true); // re-create all icons, width might have changed
    }
    if (quit) {
	Glib::signal_idle().connect(sigc::mem_fun(this, &MainWindow::delete_ladspalist_window));
    }
}

bool MainWindow::delete_ladspalist_window() {
    delete ladspalist_window;
    ladspalist_window = 0;
    return false;
}

void MainWindow::on_load_ladspa() {
    if (ladspalist_window) {
	ladspalist_window->present();
    } else {
	ladspalist_window = new ladspa::PluginDisplay(options, sigc::mem_fun(this, &MainWindow::on_ladspa_finished));
    }
}

void MainWindow::add_plugin(std::vector<PluginUI*>& p, const char *id, const Glib::ustring& fname, const Glib::ustring& tooltip) {
    if (PluginUI::is_registered(engine.pluginlist, id)) {
	return;
    }
    p.push_back(new PluginUI(*this, engine.pluginlist, id, fname, tooltip));
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
    actions.group->add(Gtk::Action::create(groupname, group));
    Gtk::ToolItemGroup *gw = new Gtk::ToolItemGroup(group);
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
    pui->set_action(act);
}

void MainWindow::fill_pluginlist() {
    // define order of categories by registering
    // them first
    add_plugin_category("Tone control", false);
    add_plugin_category("Distortion");
    add_plugin_category("Reverb");
    add_plugin_category("Echo / Delay");
    add_plugin_category("Modulation");
    add_plugin_category("Guitar Effects");
    add_plugin_category("Misc");

    std::vector<PluginUI*> p;
    p.push_back(new JConvPluginUI(*this, engine.pluginlist, "jconv", engine.stereo_convolver));
    p.push_back(new JConvPluginUI(*this, engine.pluginlist, "jconv_mono", engine.mono_convolver));

    gx_gui::UiBuilderImpl builder(this, &boxbuilder, &p);
    engine.pluginlist.append_rack(builder);

    std::sort(p.begin(), p.end(), plugins_by_name_less);
    for (std::vector<PluginUI*>::iterator v = p.begin(); v != p.end(); ++v) {
	register_plugin(*v);
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
    int wait_after_connect = 0;
    gx_engine::EnumParameter& jack_starter = pmap["ui.jack_starter_idx"].getEnum();
    string v_id = jack_starter.get_pair().value_id;
    if (v_id == "autostart") {
	return jack.gx_jack_connection(true, true, wait_after_connect) ? 1 : 0;
    }
    string cmd;
    if (v_id == "other") {
	cmd = pmap["ui.jack_starter"].getString().get_value();
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
	if (jack.gx_jack_connection(true,false,wait_after_connect)) {
	    return 1;
	}
	usleep(500000);
    }
    gx_system::gx_print_error(
	_("main"),
	string(_("I really tried to get jack up and running, sorry ... ")));
    return 0;
}

bool MainWindow::connect_jack(bool v, Gtk::Window *splash) {
    if (jack.gx_jack_connection(v, false, 0)) {
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
    if (splash) {
	splash->hide();
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
    actions.jackserverconnection->set_active(v);
    Glib::ustring s = "Guitarix: ";
    if (v) {
	s += jack.get_instancename();
    } else {
	s += "("+jack.get_instancename()+")";
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
	actions.engine_mute->set_active(true);
	status_image->set(pixbuf_off);
	break;
    case gx_engine::kEngineOn:
	actions.engine_mute->set_active(false);
	actions.engine_bypass->set_active(false);
	status_image->set(pixbuf_on);
	break;
    case gx_engine::kEngineBypass:
	actions.engine_mute->set_active(false);
	actions.engine_bypass->set_active(true);
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

/* --------- calculate power (percent) to decibel -------- */
// Note: could use fast_log10 (see ardour code) to make it faster
inline float power2db(float power) {
    return  20.*log10(power);
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
	    peak_db = power2db(m.get(c));
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
	actions.jackserverconnection->set_active(true);
	// run only one time whem jackd is running
	return false;
    } else if (!jack.is_jack_down()) {
        // refresh some stuff. Note that it can be executed
        // more than once, no harm here
        actions.jackserverconnection->set_active(false);
        jack.set_jack_down(true);
	gx_system::gx_print_error("Jack Shutdown",
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
	window->get_window()->get_root_origin(mainwin_x, mainwin_y);
    }
    return false;
}

void MainWindow::hide_extended_settings() {
    if (!is_visible ||
	(window->get_window()->get_state()
	 & (Gdk::WINDOW_STATE_ICONIFIED|Gdk::WINDOW_STATE_WITHDRAWN))) {
        //window->move(mainwin_x, mainwin_y);
        window->present();
        //window->deiconify();
    } else {
        //window->hide();
        window->iconify();
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
    Gtk::Main::quit();
    return false;
}

void MainWindow::amp_controls_visible(Gtk::Range *rr) {
    //FIXME
    bool v = abs(rr->get_value() - pmap["tube.select"].getUpperAsFloat()) < 0.5;
    const char *knobs[] = {"gxbigknob1","gxbigknob2","gxbigknob3"};
    for (unsigned int i = 0; i < sizeof(knobs)/sizeof(knobs[0]); ++i) {
	Gtk::Widget *w;
	bld->find_widget(knobs[i], w);
	w->set_visible(!v);
    }
}

int MainWindow::skin = -1;
bool MainWindow::no_warn_latency = false;
int MainWindow::mainwin_x = -1;
int MainWindow::mainwin_y = -1;
int MainWindow::mainwin_height = -1;
int MainWindow::window_height = 0;
int MainWindow::preset_window_height = 0;

MainWindow::MainWindow(gx_engine::GxEngine& engine_, gx_system::CmdlineOptions& options_,
		       gx_engine::ParamMap& pmap_, Gtk::Window *splash)
    : sigc::trackable(),
      ui(),
      bld(),
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
      preset_list_menu_bank(),
      preset_list_merge_id(0),
      preset_list_actiongroup(),
      uimanager(),
      options(options_),
      pmap(pmap_),
      engine(engine_),
      jack(engine),
      gx_settings(options, jack, engine.stereo_convolver, gx_engine::midi_std_ctr, gx_engine::controller_map, engine, pmap_),
      live_play(),
      preset_window(),
      fWaveView(),
      convolver_filename_label(),
      convolver_mono_filename_label(),
      gx_head_icon(Gdk::Pixbuf::create_from_file(options.get_pixmap_filepath("gx_head.png"))),
      boxbuilder(engine_, gx_settings, fWaveView, convolver_filename_label, convolver_mono_filename_label, ui, gx_head_icon),
      portmap_window(0),
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
      report_xrun(jack),
      in_session(false),
      status_icon(Gtk::StatusIcon::create(gx_head_icon)),
      gx_head_midi(Gdk::Pixbuf::create_from_file(options.get_pixmap_filepath("gx_head-midi.png"))),
      gx_head_warn(Gdk::Pixbuf::create_from_file(options.get_pixmap_filepath("gx_head-warn.png"))),
      actions(),
      keyswitch(gx_settings, sigc::mem_fun(this, &MainWindow::display_preset_msg)),
      groupmap(),
      ladspalist_window() {

    convolver_filename_label.set_ellipsize(Pango::ELLIPSIZE_END);
    convolver_mono_filename_label.set_ellipsize(Pango::ELLIPSIZE_END);

    /*
    ** setup parameters
    */

    // window geometry parameter definitions
    pmap.reg_non_midi_par("system.mainwin_x", &mainwin_x, false, -1, -1, 99999);
    pmap.reg_non_midi_par("system.mainwin_y", &mainwin_y, false, -1, -1, 99999);
    pmap.reg_non_midi_par("system.mainwin_height", &mainwin_height, false, -1, -1, 99999);
    pmap.reg_non_midi_par("system.mainwin_rack_height", &window_height, false, 600, 1, 99999);
    pmap.reg_non_midi_par("system.preset_window_height", &preset_window_height, false, 150, 0, 99999);

    // rack tuner
    gx_engine::get_group_table().insert("racktuner", N_("Rack Tuner"));
    static const value_pair streaming_labels[] = {{"scale"}, {"stream"}, {0}};
    pmap.reg_non_midi_enum_par("racktuner.streaming", "Streaming Mode", streaming_labels, (int*)0, false, 1);
    static const value_pair tuning_labels[] = {{"(Chromatic)"},{"Standard"}, {"Standard/Es"}, {"Open E"}, {0}};
    pmap.reg_non_midi_enum_par("racktuner.tuning", "Tuning", tuning_labels, (int*)0, false, 0);
    pmap.reg_par_non_preset("racktuner.scale_lim", "Limit", 0, 3.0, 1.0, 10.0, 1.0);
    pmap.reg_par_non_preset("ui.tuner_reference_pitch", "?Tuner Reference Pitch", 0, 440, 427, 453, 0.1);
    //pmap.reg_par("racktuner.scale_lim", "Limit", &scale_lim, 3.0, 1.0, 10.0, 1.0); FIXME add in detail view?

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
			      "bank_combo_liststore", "ampdetail_sizegroup", 0 };
    bld = gx_gui::GxBuilder::create_from_file(options_.get_builder_filepath("mainpanel.glade"), &ui, id_list);
    load_widget_pointers();
    rackcontainer->set_homogeneous(true); // setting it in glade is awkward to use with glade tool

    // remove marker labels from boxes (used in glade to make display clearer)
    clear_box(*monocontainer);
    clear_box(*stereorackcontainerH);
    clear_box(*stereorackcontainerV);
    clear_box(*preset_box_no_rack);

    // preset window also creates some actions
    preset_window = new PresetWindow(bld, gx_settings, options, actions);

    // create uimanager and load menu
    uimanager = Gtk::UIManager::create();
    uimanager->insert_action_group(actions.group);
    uimanager->add_ui_from_file(options.get_builder_filepath("menudef.xml"));

    // add dynamic submenus
    add_skin_menu();
    add_latency_menu();
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
    engine.set_jack(&jack);
    jack.xrun.connect(sigc::mem_fun(report_xrun, &gx_gui::ReportXrun::run));
    jack.shutdown.connect(sigc::mem_fun(*this, &MainWindow::gx_jack_is_down));
    jack.signal_buffersize_change().connect(
	sigc::mem_fun(*this, &MainWindow::set_latency));
    jack.signal_client_change().connect(
	sigc::mem_fun(*this, &MainWindow::on_jack_client_changed));
#ifdef HAVE_JACK_SESSION
    jack.session.connect(sigc::mem_fun(*this, &MainWindow::jack_session_event));
    jack.session_ins.connect(sigc::mem_fun(*this, &MainWindow::jack_session_event_ins));
    if (!options.get_jack_uuid().empty()) {
	set_in_session();
    }
#endif

    engine.signal_state_change().connect(
	sigc::mem_fun(*this, &MainWindow::on_engine_state_change));
    engine.midiaudiobuffer.signal_jack_load_change().connect(
	sigc::mem_fun(*this, &MainWindow::overload_status_changed));

    gx_engine::controller_map.signal_new_program().connect(
	sigc::mem_fun(*this, &MainWindow::do_program_change));

    /*
    ** GxSettings signal connections
    */
    gx_settings.signal_presetlist_changed().connect(
	sigc::mem_fun(*this, &MainWindow::rebuild_preset_menu));
    gx_settings.signal_selection_changed().connect(
	sigc::mem_fun(*this, &MainWindow::show_selected_preset));
    gx_settings.signal_selection_changed().connect(
	sigc::mem_fun(monorackcontainer, &RackContainer::check_order));
    gx_settings.signal_selection_changed().connect(
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
    jackd_image->set(pixbuf_jack_disconnected);
    jackd_image->get_parent()->signal_button_press_event().connect(
	sigc::bind_return(
	    sigc::group(
		sigc::ptr_fun(toggle_action),
		actions.jackserverconnection),
	    true));

    /*
    ** setup racktuner parameter and signals
    */
    setup_tuner(*racktuner);
    tuner_on_off->signal_toggled().connect(
	sigc::compose(
	    sigc::mem_fun(*racktuner, &Gxw::RackTuner::set_sensitive),
	    sigc::mem_fun(*tuner_on_off, &Gxw::Switch::get_active)));
    racktuner->signal_poll_status_changed().connect(
	sigc::mem_fun(engine.tuner, &gx_engine::TunerAdapter::used_for_display));

    /*
    ** oscilloscope signal connections
    */
    engine.oscilloscope.post_pre_signal.changed.connect(
	sigc::mem_fun(*this, &MainWindow::on_oscilloscope_post_pre));
    engine.oscilloscope.visible.changed.connect(
	sigc::mem_fun(*this, &MainWindow::on_show_oscilloscope));
    engine.oscilloscope.activation.connect(
	sigc::mem_fun(*this, &MainWindow::on_oscilloscope_activate));
    engine.oscilloscope.size_change.connect(
	sigc::mem_fun(*this, &MainWindow::set_waveview_buffer));

    /*
    ** fastmeter initialization and signal connections
    */
    for (unsigned int i = 0; i < sizeof(fastmeter)/sizeof(fastmeter[0]); ++i) {
        fastmeter[i]->signal_button_release_event().connect(
            sigc::mem_fun(*this, &MainWindow::on_meter_button_release));
        fastmeter[i]->set_tooltip_text(_("gx_head output"));
    }
    Glib::signal_timeout().connect(
	sigc::mem_fun(*this, &MainWindow::refresh_meter_level), gx_gui::guivar.meter_display_timeout);

    /*
    ** amp top box signal connections
    */
    ampdetail_compress->signal_clicked().connect(
	sigc::bind(sigc::mem_fun(*this, &MainWindow::on_ampdetail_switch), true));
    ampdetail_expand->signal_clicked().connect(
	sigc::bind(sigc::mem_fun(*this, &MainWindow::on_ampdetail_switch), false));
    ampdetail_sh.changed.connect(
	sigc::mem_fun(*this, &MainWindow::on_ampdetail_switch));

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
	    "midi_out"));
    midi_out_presets_normal->signal_clicked().connect(
	sigc::bind(
	    sigc::mem_fun1(this, &MainWindow::plugin_preset_popup),
	    "midi_out"));
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
    gx_engine::BoolParameter& par = pmap["engine.mute"].getBool();
    par.setSavable(false);
    gx_gui::connect_midi_controller(GTK_WIDGET(status_image->get_parent()->gobj()), &par.get_value());
    status_image->get_parent()->signal_button_press_event().connect(
	sigc::mem_fun(*this, &MainWindow::on_toggle_mute));

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
    actions.tuner->set_active(false);
    actions.show_plugin_bar->set_active(false);

    /*
    ** create liveplay and setup liveplay racktuner
    */
    live_play = new Liveplay(options, engine, gx_settings, options.get_builder_filepath("mainpanel.glade"), actions);
    setup_tuner(live_play->get_tuner());
    live_play->get_tuner().signal_poll_status_changed().connect(
	sigc::mem_fun(engine.tuner, &gx_engine::TunerAdapter::used_for_livedisplay));

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
    PluginUI *mainamp_plugin = new PluginUI(*this, engine.pluginlist, "ampstack");
    plugin_dict.add(mainamp_plugin);
    mainamp_plugin->rackbox = add_rackbox_internal(*mainamp_plugin, 0, 0, false, -1, false, amp_background);
    effects_toolpalette->show();

    // call some action functions to sync state
    // with settings defined in create_actions()
    on_show_rack();
    on_show_values();
    // somehow need to load a style or window might open too wide
    gtk_rc_parse(
	(options.get_style_filepath(
	    "gx_head_" + options.skin.skin_list[0] + ".rc")).c_str());

    /*
    ** Jack client connection and subsequent initalizations
    */

    // state must be loaded before starting jack because connect_jack() uses
    // some settings. If the jack client name changes (from the predefined value)
    // on connect the jack client-change signal will trigger the load of another
    // state file, which means that the jack starter options are read from the
    // standard state file (gx_head_rc or similar if -n is used)
    gx_settings.loadstate();
    if (!connect_jack(true, splash)) {
	// not connected, must synthesize signal for initialization
	jack.signal_client_change()();
    }
    set_latency(); // make sure latency menu is updated
	
    // we set the skin at this late point to avoid calling make_icons more
    // than once
    if (actions.skin->get_current_value() != skin) {
	actions.skin->set_current_value(skin); // will call set_new_skin()
    } else {
	set_new_skin(skin);
    }
    skin_changed.changed.connect(
	sigc::mem_fun(actions.skin.operator->(), &Gtk::RadioAction::set_current_value));

    if (mainwin_height > 0) {  // initially use the default set in mainpanel.glade
	window->set_default_size(-1, min(window_height, mainwin_height));
    }

    // set window position (make this optional??)
    if (mainwin_x > 0) {
	window->move(mainwin_x, mainwin_y);
    }

    Glib::signal_timeout().connect(
	sigc::mem_fun(*this, &MainWindow::update_all_gui), 40);

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

    engine.start_ramp_down();

    int mainwin_width;
    window->get_size(mainwin_width, mainwin_height);
    Glib::RefPtr<Gdk::Window> win = window->get_window();
    if (win) {
	win->get_root_origin(mainwin_x, mainwin_y);
    }
    if (actions.presets->get_active()) {
	preset_window_height = preset_scrolledbox->get_allocation().get_height();
    }
    plugin_dict.cleanup();
    delete live_play;
    delete preset_window;
    delete window;
    window = 0;

    engine.wait_ramp_down_finished();
    engine.set_stateflag(gx_engine::ModuleSequencer::SF_INITIALIZING);
    engine.set_jack(0);
}
