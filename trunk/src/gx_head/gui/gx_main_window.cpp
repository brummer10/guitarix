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
    if (!work.empty()) {
	Glib::signal_idle().connect_once(work);
	work.disconnect();
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
    gx_engine::get_group_table().insert("racktuner", N_("Rack Tuner"));
    ui_racktuner = pmap.reg_par("ui.racktuner", N_("Tuner on/off"), (bool*)0, true, false);
    racktuner_streaming = pmap.reg_non_midi_enum_par("racktuner.streaming", "Streaming Mode", streaming_labels, (int*)0, false, 1);
    racktuner_tuning = pmap.reg_non_midi_enum_par("racktuner.tuning", "Tuning", tuning_labels, (int*)0, false, 0);
    racktuner_scale_lim = pmap.reg_par_non_preset("racktuner.scale_lim", "Limit", 0, 3.0, 1.0, 10.0, 1.0);
    ui_tuner_reference_pitch = pmap.reg_par_non_preset("ui.tuner_reference_pitch", "?Tuner Reference Pitch",
						       0, 440, 427, 453, 0.1);
    //pmap.reg_par("racktuner.scale_lim", "Limit", &scale_lim, 3.0, 1.0, 10.0, 1.0); FIXME add in detail view?

    show_plugin_bar = pmap.reg_switch("system.show_toolbar", false, false);
    presets = pmap.reg_switch("system.show_presets", false, true);
    show_rack = pmap.reg_switch("system.show_rack", false, false);
    order_rack_v = pmap.reg_switch("system.order_rack_h", false, false);
    tuner = pmap.reg_non_midi_par("system.show_tuner", (bool*)0, false);
    animations = pmap.reg_non_midi_par("system.animations", (bool*)0, false, true);
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
}

void MainWindow::on_select_preset(const Glib::RefPtr<Gtk::RadioAction>& act) {
    gx_system::PresetFile *pf = gx_settings.get_current_bank_file();
    gx_settings.load_preset(pf, pf->get_name(act->get_current_value()));
}

void MainWindow::rebuild_preset_menu() {
    if (preset_list_merge_id) {
	uimanager->remove_ui(preset_list_merge_id);
	uimanager->remove_action_group(preset_list_actiongroup);
	preset_list_menu_bank.clear();
	preset_list_merge_id = 0;
	select_preset_action.reset();
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
    Gtk::RadioButtonGroup pg;
    int idx = 0;
    char c = '1';
    select_preset_action.reset();
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
    int i = pf->get_index(gx_settings.get_current_name());
    if (select_preset_action) {
	if (i >= 0) {
	    select_preset_action->set_current_value(i);
	}
	select_preset_action->signal_changed().connect(
	    sigc::mem_fun(*this, &MainWindow::on_select_preset));
    }
    dynamic_cast<Gtk::MenuItem*>(uimanager->get_widget("/menubar/PresetsMenu/PresetListMenu"))->set_label(_("_Bank: ")+preset_list_menu_bank);
}

void MainWindow::show_selected_preset() {
    Glib::ustring t;
    if (gx_settings.setting_is_preset()) {
	t = gx_settings.get_current_bank() + " / " + gx_settings.get_current_name();
	if (preset_list_menu_bank != gx_settings.get_current_bank()) {
	    rebuild_preset_menu();
	}	    
	gx_system::PresetFile *pf = gx_settings.get_current_bank_file();
	if (pf) {
	    int i = pf->get_index(gx_settings.get_current_name());
	    if (i >= 0 && select_preset_action) {
		select_preset_action->set_current_value(i);
	    }
	}
    }
    preset_status->set_text(t);
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

void MainWindow::set_vpaned_handle() {
    int pos = main_vpaned->get_allocation().get_height() - preset_window_height - main_vpaned->get_handle_window()->get_height();
    main_vpaned->set_position(pos);
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
    stereorackcontainer.set_visible(v);
    rack_order_h_button->set_visible(v);
    compress_button->set_visible(v);
    expand_button->set_visible(v);
    if (presets_action->get_active()) {
	preset_window_height = preset_scrolledbox->get_allocation().get_height();
    }
    if (v) {
	window_height = max(window_height, window->size_request().height);
	//main_vpaned->child_set_property(amp_toplevel_box, "resize", true);
	//child_set_property(*main_vpaned, *amp_toplevel_box, "resize", true);
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
	child_set_property(*main_vpaned, *preset_scrolledbox, "shrink", false);
	Glib::RefPtr<Gdk::Window> win = window->get_window();
	if (!win || win->get_state() == 0) {
	    Gtk::Requisition req;
	    window->size_request(req);
	    req.height = max(req.height, window_height);
	    freezer.freeze_and_size_request(window, req.width, req.height);
	    if (win && presets_action->get_active()) {
		freezer.set_slot(sigc::mem_fun(this, &MainWindow::set_vpaned_handle));
	    }
	}
    } else {
	show_plugin_bar_action->set_active(false);
	oldpos = main_vpaned->get_position();
	//child_set_property(*main_vpaned, *amp_toplevel_box, "resize", false);
	//main_vpaned->set_position(-1);
	w->hide();
	monoampcontainer->hide();
	monorackcontainer.hide_entries();
	if (preset_scrolledbox->get_parent() == main_vpaned) {
	    main_vpaned->remove(*preset_scrolledbox);
	    preset_box_no_rack->add(*preset_scrolledbox);
	    change_expand(*main_vpaned, false);
	    change_expand(*preset_box_no_rack, true);
	}
	preset_box_no_rack->set_visible(presets_action->get_active());
	vrack_scrolledbox->set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_NEVER);
	vrack_scrolledbox->get_size_request(scrl_size_x, scrl_size_y);
	vrack_scrolledbox->set_size_request(-1,-1);
	if (presets_action->get_active()) {
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
    compress_action->set_sensitive(!v);
    expand_action->set_sensitive(!v);
    live_play_action->set_sensitive(!v);
    Gtk::Requisition req;
    monobox->size_request(req);
    stereorackcontainer.set_config_mode(v);
    monorackcontainer.set_config_mode(v);
    bool plugin_bar = show_plugin_bar_action->get_active();
    if (v) {
	pre_act = presets_action->get_active();
	if (pre_act) {
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
	if (!plugin_bar) {
	    effects_frame_paintbox->hide();
	}
	upper_rackbox->show();
	monobox->set_size_request(-1,-1);
	if (pre_act) {
	    presets_action->set_active(true);
	}
    }
    if (!plugin_bar) {
	update_scrolled_window(*vrack_scrolledbox);
	update_scrolled_window(*stereorackbox);
	maybe_shrink_horizontally();
    }
}

void MainWindow::on_show_plugin_bar() {
    bool v = show_plugin_bar_action->get_active();
    if (v) {
	show_rack_action->set_active(true);
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
    return rackv_action->get_current_value() == 0;
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

void MainWindow::on_dir_changed(Glib::RefPtr<Gtk::RadioAction> act) {
    if (act->get_current_value()) {
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
	if (show_rack_action->get_active()) {
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
    PluginDef *pd = pl.plugin->pdef;
    if (!pd->load_ui) {
	return false;
    }
    dynamic_cast<StackBoxBuilderNew*>(intf)->prepare();
    pd->load_ui(*this);
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
    bool v = presets_action->get_active();
    if (!v && preset_scrolledbox->get_mapped()) {
	preset_window_height = preset_scrolledbox->get_allocation().get_height();
    }
    maybe_change_resizable();
    if (v && !show_rack_action->get_active()) {
	Glib::RefPtr<Gdk::Window> win = window->get_window();
	if (!win || win->get_state() == 0) {
	    Gtk::Requisition req;
	    window->size_request(req);
	    freezer.freeze_and_size_request(window, req.width, req.height+preset_window_height);
	}
    }
    preset_box_no_rack->set_visible(v);
    preset_window->on_preset_select(v, use_animations() && show_rack_action->get_active(), preset_window_height);
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

void MainWindow::set_switcher_controller() {
    if (!gx_engine::controller_map.get_config_mode()) {
	new gx_main_midi::MidiConnect(0, pmap["ui.live_play_switcher"]);
    }
}

void MainWindow::create_menu(Glib::RefPtr<Gtk::ActionGroup>& actiongroup, const GuiParameter& para) {
    uimanager = Gtk::UIManager::create();

    /*
    ** Menu actions
    */
    actiongroup->add(Gtk::Action::create("EngineMenu",_("_Engine")));
    jack_latency_menu_action = Gtk::Action::create("JackLatency",_("_Latency"));
    actiongroup->add(jack_latency_menu_action);
    actiongroup->add(Gtk::Action::create("PresetsMenu",_("_Presets")));
    actiongroup->add(Gtk::Action::create("PresetListMenu","--"));
    actiongroup->add(Gtk::Action::create("PluginsMenu",_("P_lugins")));
    actiongroup->add(Gtk::Action::create("MonoPlugins",_("_Mono Plugins")));
    actiongroup->add(Gtk::Action::create("StereoPlugins",_("_Stereo Plugins")));
    actiongroup->add(Gtk::Action::create("TubeMenu",_("_Tube")));
    actiongroup->add(Gtk::Action::create("OptionsMenu",_("_Options")));
    actiongroup->add(Gtk::Action::create("SkinMenu", _("_Skin...")));
    actiongroup->add(Gtk::Action::create("AboutMenu",_("_About")));

    /*
    ** engine actions
    */
    jackserverconnection_action = Gtk::ToggleAction::create("JackServerConnection", _("Jack Server _Connection"));
    actiongroup->add(
	jackserverconnection_action,
	sigc::mem_fun(*this, &MainWindow::jack_connection));

    jackports_action = Gtk::ToggleAction::create("JackPorts", _("Jack _Ports"));
    actiongroup->add(
	jackports_action,
	sigc::mem_fun(*this, &MainWindow::on_portmap_activate));

    midicontroller_action = Gtk::ToggleAction::create("MidiController", _("M_idi Controller"));
    actiongroup->add(
	midicontroller_action,
        sigc::mem_fun(*this, &MainWindow::on_miditable_toggle));

    engine_mute_action = Gtk::ToggleAction::create("EngineMute", _("Engine _Mute"));
    actiongroup->add(
	engine_mute_action,
	sigc::mem_fun(*this, &MainWindow::on_engine_toggled));

    engine_bypass_action = Gtk::ToggleAction::create("EngineBypass", _("Engine _Bypass"));
    actiongroup->add(
	engine_bypass_action,
	sigc::mem_fun(*this, &MainWindow::on_engine_toggled));

    actiongroup->add(Gtk::Action::create("Quit",_("_Quit")),
		     sigc::ptr_fun(Gtk::Main::quit));

    /*
    ** actions to open other (sub)windows
    */
    presets_action = UiSwitchToggleAction::create(ui, *para.presets, "Presets",_("_Preset Selection"));
    actiongroup->add(presets_action, 
		     sigc::mem_fun(*this, &MainWindow::on_preset_action));

    show_plugin_bar_action = UiSwitchToggleAction::create(ui, *para.show_plugin_bar, "ShowPluginBar",_("Show Plugin _Bar"),"",true);
    actiongroup->add(show_plugin_bar_action,
		     sigc::mem_fun(*this, &MainWindow::on_show_plugin_bar));

    show_rack_action = UiSwitchToggleAction::create(ui, *para.show_rack, "ShowRack",_("Show _Rack"),"",true);
    actiongroup->add(show_rack_action,
		     sigc::mem_fun(*this, &MainWindow::on_show_rack));

    loggingbox_action = Gtk::ToggleAction::create("LoggingBox", _("Show _Logging Box"));
    actiongroup->add(
	loggingbox_action,
        sigc::mem_fun(*this, &MainWindow::on_log_activate));

    live_play_action = Gtk::ToggleAction::create("Liveplay",_("Live _Display"));
    actiongroup->add(live_play_action,
		     sigc::mem_fun(*this, &MainWindow::on_live_play));

    meterbridge_action = Gtk::ToggleAction::create("Meterbridge", _("_Meterbridge"));
    actiongroup->add(
	meterbridge_action,
	sigc::bind(sigc::ptr_fun(gx_child_process::Meterbridge::start_stop),
		   sigc::ref(meterbridge_action), sigc::ref(jack)));

    /*
    ** rack actions
    */
    tuner_action = UiBoolToggleAction::create(ui, *para.tuner, "Tuner",_("_Tuner"),"",true);
    actiongroup->add(tuner_action,
		     sigc::mem_fun(*this, &MainWindow::on_show_tuner));

    rack_config_action = Gtk::ToggleAction::create("RackConfig", _("R_ack Configuration"));
    actiongroup->add(rack_config_action,
		     sigc::mem_fun(*this, &MainWindow::on_rack_configuration));

    compress_action = Gtk::Action::create("Compress",_("C_ompress all"));
    actiongroup->add(compress_action,
		     sigc::mem_fun(*this, &MainWindow::on_compress_all));

    expand_action = Gtk::Action::create("Expand",_("E_xpand all"));
    actiongroup->add(expand_action,
		     sigc::mem_fun(*this, &MainWindow::on_expand_all));

    // rack order radio buttons
    Gtk::RadioButtonGroup dg;
    rackv_action = UiSwitchRadioAction::create(
	ui, *para.order_rack_v, dg, "RackV", _("Order Rack Vertically"));
    rackv_action->property_value().set_value(0);
    actiongroup->add(rackv_action);
    // horizontal
    rackh_action = Gtk::RadioAction::create(dg, "RackH", _("Order Rack Horizontally"));
    rackh_action->property_value().set_value(1);
    actiongroup->add(rackh_action);
    // vertical
    rackh_action->set_active(true);
    rackv_action->signal_changed().connect(sigc::mem_fun(*this, &MainWindow::on_dir_changed));

    /*
    ** option actions
    */
    show_values_action = UiSwitchToggleAction::create(ui, *para.show_values, "ShowValues",_("_Show Values"));
    actiongroup->add(show_values_action,
		     sigc::mem_fun(*this, &MainWindow::on_show_values));

    tooltips_action = UiSwitchToggleAction::create(ui, *para.show_tooltips, "ShowTooltips", _("Show _Tooltips"));
    actiongroup->add(
	tooltips_action,
	sigc::compose(sigc::ptr_fun(set_tooltips),
		      sigc::mem_fun(tooltips_action.operator->(), &UiSwitchToggleAction::get_active)));

    midi_in_presets_action = UiSwitchToggleAction::create(ui, *para.midi_in_presets, "MidiInPresets", _("Include MIDI in _presets"));
    actiongroup->add(midi_in_presets_action);

    jackstartup_action = Gtk::ToggleAction::create("JackStartup", _("_Jack Startup Control"));
    actiongroup->add(
	jackstartup_action,
	sigc::mem_fun(*this, &MainWindow::on_select_jack_control));

    actiongroup->add(Gtk::ToggleAction::create("ResetAll", _("Reset _All Parameters")),
		     sigc::mem_fun(pmap, &gx_engine::ParamMap::set_init_values));

    animations_action = UiBoolToggleAction::create(ui, *para.animations, "Animations", _("Use Animations"),"",true);
    actiongroup->add(animations_action);

    pmap.reg_par("ui.live_play_switcher", "Liveplay preset mode" , (bool*)0, false, false)->setSavable(false);
    actiongroup->add(Gtk::Action::create("SetPresetSwitcher", _("Liveplay Midi Switch")),
		     sigc::mem_fun(this, &MainWindow::set_switcher_controller));

    /*
    ** Help and About
    */
    actiongroup->add(Gtk::Action::create("Help", _("_Help")),
		     sigc::ptr_fun(gx_show_help));
    actiongroup->add(Gtk::Action::create("About", _("_About")),
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
    unsigned int key = GDK_a;
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
	    actiongroup->add(act);
	    if (accel_map_next_key(&key)) {
		Gtk::AccelMap::add_entry(act->get_accel_path(), key, Gdk::ModifierType(0));
		++key;
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

int MainWindow::window_height = 0;
int MainWindow::preset_window_height = 0;

MainWindow::MainWindow(gx_engine::GxEngine& engine_, gx_system::CmdlineOptions& options_, gx_engine::ParamMap& pmap_)
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

    Gtk::AccelMap::load(options.get_builder_filepath("accels_rc"));

    GuiParameter para(pmap);
    pmap.reg_non_midi_par("system.mainwin_rack_height", &window_height, false, 500, 1, 99999);
    pmap.reg_non_midi_par("system.preset_window_height", &preset_window_height, false, 200, 0, 99999);

    const char *id_list[] = { "MainWindow", "amp_background:ampbox", "bank_liststore", "target_liststore", "bank_combo_liststore", 0 };
    bld = gx_gui::GxBuilder::create_from_file(options_.get_builder_filepath("mainpanel.glade"), &ui, id_list);
    load_widget_pointers();
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
    clear_box(*preset_box_no_rack);

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
    gx_settings.signal_presetlist_changed().connect(
	sigc::mem_fun(*this, &MainWindow::rebuild_preset_menu));

    // create rack
    stereorackcontainerH->pack_start(stereorackcontainer, Gtk::PACK_EXPAND_WIDGET);
    monocontainer->pack_start(monorackcontainer, Gtk::PACK_EXPAND_WIDGET);

    // connect signal
    window->signal_configure_event().connect_notify(sigc::mem_fun(*this, &MainWindow::on_configure_event));
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(show_rack_button->gobj()), GTK_ACTION(show_rack_action->gobj()));
    rack_order_h_button->signal_toggled().connect(
	sigc::compose(
	    sigc::mem_fun(rackh_action.operator->(), &Gtk::RadioAction::set_current_value),
	    sigc::mem_fun(rack_order_h_button, &Gtk::ToggleButton::get_active)));
    rackh_action->signal_changed().connect(
	sigc::hide(
	    sigc::compose(
		sigc::mem_fun(rack_order_h_button, &Gtk::ToggleButton::set_active),
		sigc::mem_fun(rackh_action.operator->(), &Gtk::RadioAction::get_current_value))));
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

    int width, height;
    window->get_default_size(width, height);
    window->set_default_size(width, window_height);

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
#if false   // set true to generate a new keyboard accel file
    gtk_accel_map_add_filter("<Actions>/Main/ChangeSkin_*");
    gtk_accel_map_add_filter("<Actions>/Main/Enum_tube.select.*");
    gtk_accel_map_add_filter("<Actions>/Main/Latency_*");
    gtk_accel_map_add_filter("<Actions>/Main/Plugin_*");
    gtk_accel_map_add_filter("<Actions>/PresetList/PresetList_*");
    Gtk::AccelMap::save(options.get_user_filepath("accels_rc"));
#endif

    engine.start_ramp_down();

    window->get_size(GuiParameter::mainwin_width, GuiParameter::mainwin_height);
    window->get_window()->get_root_origin(GuiParameter::mainwin_x, GuiParameter::mainwin_y);
    if (presets_action->get_active()) {
	preset_window_height = preset_scrolledbox->get_allocation().get_height();
    }

    delete live_play;
    delete preset_window;
    delete window;
    window = 0;

    engine.wait_ramp_down_finished();
    engine.set_stateflag(gx_engine::ModuleSequencer::SF_INITIALIZING);
    engine.set_jack(0);
}
