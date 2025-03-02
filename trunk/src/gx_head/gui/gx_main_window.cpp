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
#include <gtkmm/accelmap.h>
#include "jsonrpc.h"
#include <boost/algorithm/string/replace.hpp>

/****************************************************************
 * class UIManager
 */
UIManager::UIManager(const std::string& file, Gtk::MenuBar *bar):
    menu(),
    accelgroup(Gtk::AccelGroup::create()),
    actiongroup(Gio::SimpleActionGroup::create()),
    menubar(bar) {
    auto b = Gtk::Builder::create_from_file(file);
    menu = Glib::RefPtr<Gio::Menu>::cast_dynamic(b->get_object("menubar"));
    menubar->bind_model(menu, "app", true);
}

struct action_target {
    Glib::RefPtr<Gio::Action> action;
    Glib::VariantBase target;
    action_target(Glib::RefPtr<Gio::Action>& action_, Glib::VariantBase& target_)
        : action(action_), target(target_) {}
};

static bool do_action(GtkAccelGroup *accel_group, GObject *acceleratable,
                             guint keyval, GdkModifierType modifier,
                             action_target* data) {
    g_action_activate(data->action->gobj(), data->target.gobj());
    return true;
}

static void destroy_action_target(void *p, GClosure *closure) {
    delete static_cast<action_target*>(p);
}

//static
void UIManager::add_accelerator(Glib::RefPtr<Gtk::AccelGroup>& group,
                                Glib::RefPtr<Gio::Action> action,
                                const Glib::ustring& accelerator,
                                Glib::VariantBase& target) {
    GClosure *cl = g_cclosure_new(
        G_CALLBACK(do_action),
        new action_target(action, target),
        destroy_action_target);
    guint accelerator_key;
    GdkModifierType accelerator_mods;
    gtk_accelerator_parse(accelerator.c_str(), &accelerator_key, &accelerator_mods);
    gtk_accel_group_connect (
        group->gobj(), accelerator_key, accelerator_mods, GTK_ACCEL_VISIBLE, cl);
    g_closure_unref(cl);
}

void UIManager::add_accelerator(Glib::RefPtr<Gio::Action> action,
                                Glib::VariantBase& target,
                                const Glib::ustring& accelerator) {
    add_accelerator(accelgroup, action, accelerator, target);
}

void UIManager::set_accelerators_from_menu(Glib::RefPtr<Gio::Menu>& menu) {
    int n = menu->get_n_items();
    auto stringtype = Glib::VARIANT_TYPE_STRING;
    for (int i = 0; i < n; i++) {
        auto it = menu->iterate_item_attributes(i);
        Glib::ustring action;
        Glib::ustring accel;
        Glib::VariantBase target;
        while (it->next()) {
            Glib::ustring key = it->get_name();
            if (key == "action") {
                Glib::VariantBase value = it->get_value();
                if (value.is_of_type(stringtype)) {
                    action = static_cast<Glib::Variant<Glib::ustring>*>(&value)->get();
                }
            } else if (key == "accel") {
                Glib::VariantBase value = it->get_value();
                if (value.is_of_type(stringtype)) {
                    accel = static_cast<Glib::Variant<Glib::ustring>*>(&value)->get();
                }
            } else if (key == "target") {
                target = it->get_value();
            }
        }
        if (!accel.empty()) {
            Glib::RefPtr<Gio::Action> a = actiongroup->lookup(action);
            assert(a);
            add_accelerator(a, target, accel);
        }
        auto itl = menu->iterate_item_links(i);
        while (itl->next()) {
            auto m = Glib::RefPtr<Gio::Menu>::cast_dynamic(itl->get_value());
            set_accelerators_from_menu(m);
        }
    }
}

Glib::RefPtr<Gio::SimpleAction> UIManager::add_action(const Glib::ustring& action) {
    auto a = Gio::SimpleAction::create(action);
    actiongroup->add_action(a);
    return a;
}

Glib::RefPtr<Gio::SimpleAction> UIManager::add_action(const Glib::ustring& action,
                                                      sigc::slot<void()> slot) {
    auto a = add_action(action);
    a->signal_activate().connect(sigc::hide(slot));
    return a;
}

Glib::RefPtr<ToggleAction> UIManager::add_toggle_action(const Glib::ustring& action, bool state) {
    auto a = ToggleAction::create(action, state);
    actiongroup->add_action(a);
    return a;
}

Glib::RefPtr<RadioAction> UIManager::add_radio_action(const Glib::ustring& action) {
    auto a = RadioAction::create(action);
    actiongroup->add_action(a);
    return a;
}

Glib::RefPtr<UiBoolToggleAction> UIManager::add_ui_bool_action(
    gx_engine::GxMachineBase& machine, const std::string& id, const Glib::ustring& name,
    bool is_active) {
    auto a = UiBoolToggleAction::create(machine, id, name, is_active);
    actiongroup->add_action(a);
    return a;
}

bool UIManager::foreach_menu_(
    Glib::RefPtr<Gio::Menu>& menu, search_func& func, int& startpos) {
    int n = menu->get_n_items();
    for (int i = 0; i < n; i++) {
        Glib::VariantBase v = menu->get_item_attribute(
            i, Gio::MENU_ATTRIBUTE_ACTION, Glib::VARIANT_TYPE_STRING);
        if (v) {
            Glib::ustring action = static_cast<Glib::Variant<Glib::ustring>*>(&v)->get();
            if (func(action, menu, i, startpos)) {
                return true;
            }
        }
        auto it = menu->iterate_item_links(i);
        while (it->next()) {
            auto m = Glib::RefPtr<Gio::Menu>::cast_dynamic(it->get_value());
            Glib::ustring tp = it->get_name();
            bool is_section = tp == "section";
            int j = 0;
            if (func(tp, m, -1, 0) || foreach_menu_(m, func, (is_section ? startpos : j))) {
                return true;
            }
            func(tp, m, -2, 0);
            if (is_section) {
                // adjust for SeparatorMenuItem between sections
                startpos += 1;
            }
        }
    }
    startpos += n;
    return false;
}

Glib::RefPtr<Gio::Menu> UIManager::get_linked_menu(const Glib::ustring& action) {
    Glib::RefPtr<Gio::Menu> found;
    foreach_menu(
        [&action, &found](const Glib::ustring& a, Glib::RefPtr<Gio::Menu>& m, int i, int pos) -> bool {
            if (i == -2) {
                return false;
            }
            if (a != action) {
                return false;
            }
            if (i < 0) {
                found = m;
                return true;
            }
            auto it = m->iterate_item_links(i);
            if (!it->next()) {
                return false;
            }
            found = Glib::RefPtr<Gio::Menu>::cast_dynamic(it->get_value());
            return true;
        });
    return found;
}

Gtk::MenuItem *UIManager::find_item(const Glib::ustring& action) {
    std::vector<int> l;
    l.push_back(-1);
    if (!foreach_menu(
            [&action, &l](const Glib::ustring& a, Glib::RefPtr<Gio::Menu>& m,
                          int i, int startpos) -> bool {
                if (i == -1) {
                    l.push_back(-1);
                    return false;
                }
                if (i == -2) {
                    l.pop_back();
                    return false;
                }
                l.back() = startpos + i;
                if (a != action) {
                    return false;
                }
                return true;
            })) {
        return nullptr;
    }
    Gtk::MenuItem *item = nullptr;
    for (std::vector<int>::iterator i = l.begin(); i != l.end(); ++i) {
        if (*i != -1) {
            Gtk::MenuShell *m;
            if (item) {
                m = item->get_submenu();
                if (!m) {
                    assert(false);
                }
            } else {
                m = menubar;
            }
            item = dynamic_cast<Gtk::MenuItem*>(m->get_children()[*i]);
        }
    }
    return item;
}

bool UIManager::remove_item(const Glib::ustring& action) {
    return foreach_menu(
        [&action](const Glib::ustring& a, Glib::RefPtr<Gio::Menu>& m,
                  int i, int pos) -> bool {
            if (a == action && i >= 0) {
                m->remove(i);
                return true;
            }
            return false;
        });
}

void ToggleAction::set_active(bool v)
{
    change_state(v);
}

RadioAction::RadioAction(const Glib::ustring& name)

    : Gio::SimpleAction(
        name, Glib::VARIANT_TYPE_INT32, Glib::Variant<gint32>::create(0)) {
}

//static
void UIManager::set_widget_action(Gtk::Widget *w, const Glib::ustring& action) {
    Glib::ustring name = "app." + action;
    gtk_actionable_set_action_name(GTK_ACTIONABLE(w->gobj()), name.c_str());
}

//static
void UIManager::set_widget_action(Gtk::Widget *w, const Glib::RefPtr<Gio::Action>& action) {
    Glib::ustring name = action->get_name();
    set_widget_action(w, name);
}


/****************************************************************
 ** class TextLoggingBox
 */

// color depending on msg type
TextLoggingBox::tab_table TextLoggingBox::tagdefs[] = {
    {"colinfo", "#cccccc"},
    {"colwarn", "#77994f"},
    {"colerr", "#ff8800"},
};

TextLoggingBox::TextLoggingBox()
    : box(),
      ok_button(Gtk::Stock::OK),
      buttonbox(),
      scrollbox(),
      tbox(),
      highest_unseen_msg_level(-1),
      msg_level_changed() {

    set_default_size(640, 320);
    set_decorated(true);
    set_resizable(true);
    set_gravity(Gdk::GRAVITY_SOUTH);
    set_keep_below(false);
    set_title(_("Logging Window"));
    set_type_hint(Gdk::WINDOW_TYPE_HINT_UTILITY);
    set_border_width(4);

    box.set_border_width(0);
    scrollbox.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

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

void TextLoggingBox::reset_msg_level() {
    highest_unseen_msg_level = GxLogger::kMessageTypeCount;
    msg_level_changed();
    highest_unseen_msg_level = -1;
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

/****************************************************************
 ** SelectMidiChannel
 ** select a midi channel to use exclusive only
 */


SelectMidiChannel::SelectMidiChannel(BaseObjectType* cobject, Glib::RefPtr<gx_gui::GxBuilder> bld, gx_engine::GxMachineBase& m)
    : Gtk::Window(cobject),
      description(),
      channelcombo(),
      machine(m),
      close() {
    signal_delete_event().connect(sigc::mem_fun(*this, &SelectMidiChannel::on_delete_event));
    bld->find_widget("description", description);
    bld->find_widget("channelcombo", channelcombo);
    const char *v_id = machine.get_parameter("system.midi_channel").getValueNames()[machine.get_parameter_value<int>("system.midi_channel")].value_id;
    int n = 0;
    Glib::RefPtr<Gtk::TreeModel> model = channelcombo->get_model();
    for (Gtk::TreeIter i = model->children().begin(); i; ++i, ++n) {
        Glib::ustring s;
        i->get_value(1, s);
        if (s == v_id) {
            channelcombo->set_active(n);
        }
    }
    Gtk::Button *button;
    bld->find_widget("ok_button", button);
    button->signal_clicked().connect(
        sigc::mem_fun(*this, &SelectMidiChannel::on_ok_button));
    bld->find_widget("cancel_button", button);
    button->signal_clicked().connect(
        sigc::mem_fun(*this, &SelectMidiChannel::on_cancel_button));
}

SelectMidiChannel::~SelectMidiChannel() {
}

//static
SelectMidiChannel* SelectMidiChannel::create(gx_system::CmdlineOptions& opt, gx_engine::GxMachineBase& m) {
    Glib::RefPtr<gx_gui::GxBuilder> bld = gx_gui::GxBuilder::create_from_file(opt.get_builder_filepath("midi_channel.glade"), &m);
    SelectMidiChannel *w;
    bld->get_toplevel_derived("selectmidichannel", w,
        sigc::bind(sigc::ptr_fun(SelectMidiChannel::create_from_builder), bld, sigc::ref(m)));
    return w;
}

bool SelectMidiChannel::on_key_press_event(GdkEventKey *event) {
    if (event->keyval == GDK_KEY_Escape && (event->state & Gtk::AccelGroup::get_default_mod_mask()) == 0) {
        close();
        return true;
    }
    return Gtk::Window::on_key_press_event(event);
}

bool SelectMidiChannel::on_delete_event(GdkEventAny* event) {
    close();
    return true;
}

void SelectMidiChannel::on_ok_button() {
    Glib::ustring s;
    channelcombo->get_active()->get_value(1, s);
    int n = machine.get_parameter("system.midi_channel").getInt().idx_from_id(s);
    if (n >= 0) {
        machine.set_parameter_value("system.midi_channel", n);
    } else {
        gx_print_error("SelectMidiChannel", "Midi Channel out of range");
    }
    close();
}

void SelectMidiChannel::on_cancel_button() {
    close();
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
 ** adds the values of an EnumParameter as Gio::MenuItem's
 ** to a Gio::Menu
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
    GDK_KEY_a, GDK_KEY_b, GDK_KEY_c, GDK_KEY_d, GDK_KEY_e, 0,
    GDK_KEY_f, 0,
    GDK_KEY_g, GDK_KEY_h, GDK_KEY_i, GDK_KEY_j, 0,
    GDK_KEY_k, GDK_KEY_l, GDK_KEY_m, GDK_KEY_n, 0,
    GDK_KEY_o, GDK_KEY_p, GDK_KEY_q, GDK_KEY_r
};

inline int TubeKeys::operator()() {
    if (ks < sizeof(keysep)/sizeof(keysep[0])) {
        return keysep[ks++];
    }
    return -1;
}

GxUiRadioMenu::GxUiRadioMenu(gx_engine::GxMachineBase& machine_, const std::string& id_)
    : machine(machine_),
      id(id_),
      action() {
    machine.signal_parameter_value<int>(id).connect(
	sigc::mem_fun(this, &GxUiRadioMenu::set_value));
}

void GxUiRadioMenu::setup(UIManager& uimanager) {
    int i, c;
    const value_pair *p;
    TubeKeys next_key;
    gx_engine::IntParameter& param = machine.get_parameter(id).getInt();
    Glib::ustring actname = Glib::ustring::compose("Enum_%1", param.id());
    action = uimanager.add_radio_action(actname);
    action->signal_activate().connect(
        sigc::mem_fun(*this, &GxUiRadioMenu::on_changed));
    Glib::RefPtr<Gio::Menu> menu = uimanager.get_linked_menu("TubeMenu");
    auto section = Gio::Menu::create();
    for (p = param.getValueNames(), i = 0; p->value_id; p++, i++) {
        c = next_key();
        if (c == 0) {
            menu->append_section(section);
            section = Gio::Menu::create();
            c = next_key();
        }
        auto a = Gio::MenuItem::create(param.value_label(*p), actname);
        auto target = Glib::Variant<int>::create(i);
        a->set_action_and_target(actname, target);
        if (c > 0) {
            auto accelstr = Glib::ustring::compose("<shift>%1", (char)c);
            auto accel = Glib::Variant<Glib::ustring>::create(accelstr);
            a->set_attribute("accel", accel);
            uimanager.add_accelerator(action, target, accelstr);
        }
        section->append_item(a);
    }
    menu->append_section("", section);
}

void GxUiRadioMenu::set_value(int v) {
    action->change_state(v);
}

void GxUiRadioMenu::on_changed(const Glib::VariantBase& value) {
    gint32 v;
    action->get_state(v);
    machine.set_parameter_value(
        id, static_cast<const Glib::Variant<gint32>&>(value).get());
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
 ** class MainWindowBuilder
 */

MainWindowBuilder::MainWindowBuilder(const gx_system::CmdlineOptions& options, gx_engine::GxMachineBase&  machine)
    : Glib::RefPtr<gx_gui::GxBuilder>(gx_gui::GxBuilder::create())
    /* widget points left uninitialized */
{
    const char *id_list[] = { "MainWindow", "bank_liststore", "target_liststore",
			      "bank_combo_liststore", "rack_vadjustment", "left_column" };
    get()->add_from_file(options.get_builder_filepath("mainpanel.glade"),
			 vector<Glib::ustring>(begin(id_list),end(id_list)));
    const char *id_list1[] = { "amp_background:ampbox" };
    get()->add_from_file(options.get_builder_filepath("ampbox.glade"),
			 vector<Glib::ustring>(begin(id_list1),end(id_list1)));
    get()->fixup_controlparameters(machine, nullptr);
    load_widget_pointers();
}

MainWindowBuilder::~MainWindowBuilder() {
    delete window;
}

/****************************************************************
 ** class MainWindow
 */

template <class T>
UiToggleAction<T>::UiToggleAction(
    gx_engine::GxMachineBase& machine_, const std::string& id_, const Glib::ustring& name,
    bool is_active)
    : ToggleAction(name, is_active),
      machine(machine_),
      id(id_) {
    set_active(machine.get_parameter_value<T>(id));
    machine.signal_parameter_value<T>(id).connect(
        sigc::mem_fun(this, &UiToggleAction::set_active));
    signal_toggled().connect(sigc::mem_fun(this, &UiToggleAction::on_toggled));
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
    Glib::RefPtr<Gdk::Window> w = bld.window->get_window();
    if (!w) {
	return;
    }
    int state = w->get_state();
    if (state & (Gdk::WINDOW_STATE_MAXIMIZED | Gdk::WINDOW_STATE_FULLSCREEN)) {
	return;
    }
    gint req_min_w, req_min_h;
    gint req_w, req_h;
    bld.window->get_preferred_width(req_min_w, req_w);
    bld.window->get_preferred_height(req_min_h, req_h);
    int x, y;
    bld.window->get_position(x, y);
    Gdk::Geometry geom;
    geom.min_width = req_min_w;
    geom.min_height = req_min_h;
    w->set_geometry_hints(geom, Gdk::HINT_MIN_SIZE);
    if (preset_no_rack) {
	int min_height, natural_height;
	bld.preset_scrolledbox->get_preferred_height(min_height, natural_height);
	req_h += options.preset_window_height - min_height;
    } else {
	req_h = std::max(req_h, options.window_height);
    }
    w->move_resize(x, y, req_w, req_h);
    if (!state) {
	freezer.freeze_until_width_update(bld.window, req_w);
    }
}

void MainWindow::on_midiout_tuner() {
    bool v = actions.tunermidiout->get_active();
    if (v) machine.tuner_used_by_midi(true);
    else machine.tuner_used_by_midi(false);
}

void MainWindow::on_move_tuner() {
    bool v = actions.tuner->get_active();
    if(bld.tunerbox->get_parent() == bld.upper_rackbox) {
        bld.tunerbox->set_visible(false);
        bld.upper_rackbox->remove(*bld.tunerbox);
        bld.tuner_box_no_rack->pack_start(*bld.tunerbox,false,false);
    } else if(bld.tunerbox->get_parent() == bld.tuner_box_no_rack) {
        bld.tunerbox->set_visible(false);
        bld.tuner_box_no_rack->remove(*bld.tunerbox);
        bld.upper_rackbox->add(*bld.tunerbox);
    }
    on_livetuner_toggled();
    bld.tunerbox->set_visible(v);
    update_scrolled_window(*bld.vrack_scrolledbox);
}

void MainWindow::on_show_tuner() {
    bool v = actions.tuner->get_active();
    on_livetuner_toggled();
    bld.tunerbox->set_visible(v);
    if (!v && !is_variable_size()) {
        bld.window->set_size_request(-1, 1);
    }
}

void MainWindowBuilder::load_widget_pointers() {
    get()->get_toplevel("MainWindow", window);
    get()->find_widget("tunerbox", tunerbox);
    get()->find_widget("tuner_box_no_rack", tuner_box_no_rack);
    get()->find_widget("vrack_scrolledbox", vrack_scrolledbox);
    get()->find_widget("monorackscroller", monorackscroller);
    get()->find_widget("stereorackcontainerH", stereorackcontainerH);
    get()->find_widget("stereorackcontainerV", stereorackcontainerV);
    get()->find_widget("rackcontainer", rackcontainer);
    get()->find_widget("stereorackbox", stereorackbox);
    get()->find_widget("monorackcontainer", monocontainer);
    get()->find_widget("monoampcontainer:ampdetails", monoampcontainer);
    get()->find_widget("main_vpaned", main_vpaned);
    get()->find_widget("monobox", monobox);
    get()->find_widget("upper_rackbox", upper_rackbox);
    get()->find_widget("preset_scrolledbox", preset_scrolledbox);
    get()->find_widget("preset_box_no_rack", preset_box_no_rack);
    get()->find_widget("effects_frame_paintbox", effects_frame_paintbox);
    get()->find_widget("insert_image", insert_image);
    get()->find_widget("status_image", status_image);
    get()->find_widget("jackd_image", jackd_image);
    get()->find_widget("logstate_image", logstate_image);
    get()->find_widget("show_rack:barbutton", show_rack_button);
    get()->find_widget("rack_order_h:barbutton", rack_order_h_button);
    get()->find_widget("config_mode:barbutton", config_mode_button);
    get()->find_widget("liveplay:barbutton", liveplay_button);
    get()->find_widget("tuner:barbutton", tuner_button);
    get()->find_widget("effects:barbutton", effects_button);
    get()->find_widget("presets:barbutton", presets_button);
    get()->find_widget("compress:barbutton", compress_button);
    get()->find_widget("expand:barbutton", expand_button);
    get()->find_widget("effects_toolpalette", effects_toolpalette);
    get()->find_widget("amp_background:ampbox", amp_background);
    get()->find_widget("tuner_on_off", tuner_on_off);
    get()->find_widget("tuner_mode", tuner_mode);
    get()->find_widget("tuner_reference_pitch", tuner_reference_pitch);
    get()->find_widget("tuner_tuning", tuner_tuning);
    get()->find_widget("tuner_temperament", tuner_temperament);
    get()->find_widget("racktuner", racktuner);
    get()->find_widget("ampdetail_compress:effect_reset", ampdetail_compress);
    get()->find_widget("ampdetail_expand:effect_reset", ampdetail_expand);
    get()->find_widget("ampdetail_mini", ampdetail_mini);
    get()->find_widget("ampdetail_normal", ampdetail_normal);
    get()->find_widget("fastmeterL", fastmeter[0]);
    get()->find_widget("fastmeterR", fastmeter[1]);
    get()->find_widget("preset_status", preset_status);
    get()->find_widget("menubar", menubar);
}


void MainWindow::set_next_preset_controller() {
    if (!machine.midi_get_config_mode()) {
	new gx_main_midi::MidiConnect(0, machine.get_parameter("engine.next_preset"), machine);
    }
}

void MainWindow::set_previus_preset_controller() {
    if (!machine.midi_get_config_mode()) {
	new gx_main_midi::MidiConnect(0, machine.get_parameter("engine.previus_preset"), machine);
    }
}

void MainWindow::on_select_preset(const Glib::VariantBase& value) {
    int idx = static_cast<const Glib::Variant<gint32>*>(&value)->get();
    keyswitch.process_preset_key(idx);
}

void MainWindow::on_next_preset() {
    if (machine.setting_is_preset()) {
        machine.next_preset_switch();
    }
}

void MainWindow::on_previus_preset() {
    if (machine.setting_is_preset()) {
        machine.previus_preset_switch();
    }
}

void MainWindow::add_preset_key_accelerators() {
    for (int idx = KeySwitcher::next_idx(); idx >= 0; idx = KeySwitcher::next_idx(idx)) {
        auto accelstr = Glib::ustring::compose("%1", KeySwitcher::idx_to_char(idx));
        auto target = Glib::Variant<gint32>::create(idx);
        uimanager.add_accelerator(
            actions.preset_list_menu, target, accelstr);
    }
}

void MainWindow::rebuild_preset_menu() {
    Glib::ustring actname = "PresetListMenu";
    Glib::RefPtr<Gio::Menu> menu = uimanager.get_linked_menu(actname);
    if (menu->get_n_items()) {
        menu->remove_all();
        preset_list_menu_bank.clear();
    }
    Gtk::MenuItem *menuitem = uimanager.find_item("PresetListMenu");
    if (!machine.setting_is_preset()) {
        menuitem->hide();
        return;
    }
    gx_system::PresetFileGui *pf = machine.get_current_bank_file();
    if (!pf) {
        menuitem->hide();
        return;
    }
    preset_list_menu_bank = machine.get_current_bank();
    Glib::ustring current_preset = machine.get_current_name();
    int idx = 0;
    for (gx_system::PresetFile::iterator i = pf->begin();
         i != pf->end();
         ++i, ++idx) {
        auto a = Gio::MenuItem::create(
            i->name, Glib::ustring::compose("%1(%2)", actname, idx));
        char c = KeySwitcher::idx_to_char(idx);
        if (c) {
            auto accelstr = Glib::ustring::compose("%1", (char)c);
            auto accel = Glib::Variant<Glib::ustring>::create(accelstr);
            a->set_attribute("accel", accel);
            auto target = Glib::Variant<gint32>::create(idx);
        }
        menu->append_item(a);
        if (pf->get_name(idx) == current_preset) {
            actions.preset_list_menu->set_current_value(idx);
        }
    }
    menuitem->set_label(_("_Bank: ")+preset_list_menu_bank);
    menuitem->show();
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
    bld.preset_status->set_text(t);
}

bool MainWindow::is_variable_size() {
    return actions.presets->get_active() || actions.show_rack->get_active();
}

void MainWindow::maybe_change_resizable() {
    Glib::RefPtr<Gdk::Window> w = bld.window->get_window();
    if (w && w->get_state() & (Gdk::WINDOW_STATE_MAXIMIZED|Gdk::WINDOW_STATE_FULLSCREEN|Gdk::WINDOW_STATE_TILED)) {
	return;
    }
    if (!is_variable_size() && bld.window->get_resizable()) {
        bld.window->set_size_request(-1, 1);
	bld.window->set_resizable(false);
    } else if (!bld.window->get_resizable()) {
	bld.window->set_resizable(true);
    }
}

void MainWindow::set_vpaned_handle() {
    int h = bld.main_vpaned->get_handle_window()->get_height();
    int pos = bld.main_vpaned->get_allocation().get_height() - options.preset_window_height - h;
    bld.main_vpaned->set_position(pos);
}

void MainWindow::on_show_rack() {
    Gtk::Widget *stereobox;
    if (rackbox_stacked_vertical()) {
	stereobox = bld.stereorackcontainerV;
    } else {
	stereobox = bld.stereorackbox;
    }
    bool v = options.system_show_rack = actions.show_rack->get_active();
    actions.rackh->set_enabled(v);
    plugin_dict.get_stereorackcontainer().set_visible(v);
    bld.rack_order_h_button->set_visible(v);
    if (v) {
        bool c = machine.get_parameter_value<bool>("ui.all_s_h");
        bld.compress_button->set_visible(!c);
        bld.expand_button->set_visible(c);
    } else {
        bld.compress_button->set_visible(false);
        bld.expand_button->set_visible(false);
    }
    if (actions.presets->get_active() && bld.preset_scrolledbox->get_mapped()) {
	options.preset_window_height = bld.preset_scrolledbox->get_allocation().get_height();
    }
    if (v) {
	// show rack
	if (pool_act) {
	    actions.show_plugin_bar->set_active(true);
	}
	int min_height, natural_height;
	bld.window->get_preferred_height(min_height, natural_height);
	options.window_height = max(options.window_height, min_height);
	bld.main_vpaned->set_position(oldpos);
	stereobox->show();
	bld.monoampcontainer->show();
	plugin_dict.show_entries();
	bld.vrack_scrolledbox->set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_EXTERNAL);
	bld.vrack_scrolledbox->set_size_request(scrl_size_x, scrl_size_y);
	bld.monorackscroller->show();
	if (bld.preset_scrolledbox->get_parent() != bld.main_vpaned) {
	    bld.preset_box_no_rack->remove(*bld.preset_scrolledbox);
	    bld.main_vpaned->add(*bld.preset_scrolledbox);
	    change_expand(*bld.preset_box_no_rack, false);
	    change_expand(*bld.main_vpaned, true);
	    gx_gui::child_set_property(*bld.main_vpaned, *bld.preset_scrolledbox, "shrink", false);
	}
	Glib::RefPtr<Gdk::Window> win = bld.window->get_window();
	if (!win || win->get_state() == 0) {
	    int min_width, natural_width;
	    int min_height, natural_height;
	    bld.window->get_preferred_width(min_width, natural_width);
	    bld.window->get_preferred_height(min_height, natural_height);
	    min_height = max(min_height, options.window_height);
	    freezer.freeze_and_size_request(bld.window, min_width, min_height);
	    if (win && actions.presets->get_active()) {
		freezer.set_slot(sigc::mem_fun(this, &MainWindow::set_vpaned_handle));
	    }
	}
        bld.window->resize(1, options.window_height);
    } else {
	// show only amp (and maybe presets), hide rack
	pool_act = actions.show_plugin_bar->get_active();
	if (pool_act) {
	    actions.show_plugin_bar->set_active(false);
	}
	oldpos = bld.main_vpaned->get_position();
	stereobox->hide();
	bld.monoampcontainer->hide();
	plugin_dict.hide_entries();
	if (bld.preset_scrolledbox->get_parent() == bld.main_vpaned) {
	    bld.main_vpaned->remove(*bld.preset_scrolledbox);
	    bld.preset_box_no_rack->add(*bld.preset_scrolledbox);
	    change_expand(*bld.main_vpaned, false);
	    change_expand(*bld.preset_box_no_rack, true);
	}
	bld.preset_box_no_rack->set_visible(actions.presets->get_active());
	bld.vrack_scrolledbox->set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_NEVER);
	bld.monorackscroller->hide();
	bld.vrack_scrolledbox->get_size_request(scrl_size_x, scrl_size_y);
	bld.vrack_scrolledbox->set_size_request(-1,-1);
	if (actions.presets->get_active()) {
	    maybe_shrink_horizontally(true);
	} else {
            bld.window->set_default_size(1, 1);
	    maybe_shrink_horizontally();
	}
    }
    maybe_change_resizable();
}

void MainWindow::on_compress_all() {
    plugin_dict.compress(true);
    on_ampdetail_switch(true, true);
    machine.set_parameter_value("ui.all_s_h", true);
    bld.compress_button->set_visible(false);
    bld.expand_button->set_visible(true);
}

void MainWindow::on_expand_all() {
    plugin_dict.compress(false);
    on_ampdetail_switch(false, true);
    machine.set_parameter_value("ui.all_s_h", false);
    bld.compress_button->set_visible(true);
    bld.expand_button->set_visible(false);
}

void MainWindow::on_rack_configuration() {
    bool v = actions.rack_config->get_active();
    actions.show_plugin_bar->set_enabled(!v);
    actions.show_rack->set_enabled(!v);
    actions.tuner->set_enabled(!v);
    actions.compress->set_enabled(!v);
    actions.expand->set_enabled(!v);
    actions.live_play->set_enabled(!v);
    int min_width, natural_width;
    bld.monobox->get_preferred_width(min_width, natural_width);;
    plugin_dict.set_config_mode(v);
    bool plugin_bar = actions.show_plugin_bar->get_active();
    if (v) {
	pre_act = actions.presets->get_active();
	if (pre_act) {
	    actions.presets->set_active(false);
	}
	actions.show_rack->set_active(true);
	bld.tunerbox->hide();
	bld.effects_frame_paintbox->show();
	bld.upper_rackbox->hide();
	int min_width2, natural_width2;
	bld.effects_frame_paintbox->get_preferred_width(min_width2, natural_width2);
	int width = min_width;
	if (!plugin_bar) {
	    if (rackbox_stacked_vertical()) {
		width -= min_width2;
	    } else {
		if (min_width2 & 1) {
		    min_width2 += 1;
		}
		width -= min_width2 / 2;
	    }
	}
	bld.effects_frame_paintbox->set_size_request(min_width2, -1);
	bld.monobox->set_size_request(width,-1);
    } else {
	bld.tunerbox->set_visible(actions.tuner->get_active());
	if (!plugin_bar) {
	    bld.effects_frame_paintbox->hide();
	}
	bld.upper_rackbox->show();
 	bld.effects_frame_paintbox->set_size_request(-1,-1);
	bld.monobox->set_size_request(-1,-1);
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
    bld.effects_frame_paintbox->set_visible(v);
    if (!v) {
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
    w.set_vexpand(value);
    dynamic_cast<Gtk::Box*>(w.get_parent())->child_property_expand(w) = value;
}

void MainWindow::on_dir_changed() {
    bool v = options.system_order_rack_h = actions.rackh->get_active();
    if (v) {
	// horizontally
	move_widget(plugin_dict.get_stereorackcontainer(), *bld.stereorackcontainerV, *bld.stereorackcontainerH);
	change_expand(*bld.monobox, true);
	bld.stereorackbox->show();
    } else {
	move_widget(plugin_dict.get_stereorackcontainer(), *bld.stereorackcontainerH, *bld.stereorackcontainerV);
	change_expand(*bld.monobox, false);
	bld.stereorackbox->hide();
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

void MainWindow::update_width() {
    update_scrolled_window(*bld.vrack_scrolledbox);
    update_scrolled_window(*bld.stereorackbox);
}

void MainWindow::on_show_values() {
    options.system_show_value = actions.show_values->get_active();
    gx_gui::WaitCursor wait(bld.window);
    actions.show_values->set_enabled(false);
    theme.update_show_values();
    actions.show_values->set_enabled(true);
}

void MainWindow::on_preset_action() {
    bool v = options.system_show_presets = actions.presets->get_active();
    if (!v && bld.preset_scrolledbox->get_mapped()) {
	options.preset_window_height = bld.preset_scrolledbox->get_allocation().get_height();
    }
    maybe_change_resizable();
    if (v && !actions.show_rack->get_active()) {
	Glib::RefPtr<Gdk::Window> win = bld.window->get_window();
        int min_width, natural_width;
        int min_height, natural_height;
        bld.window->get_preferred_width(min_width, natural_width);
        bld.window->get_preferred_height(min_height, natural_height);
	if (!win || win->get_state() == 0) {
	    freezer.freeze_and_size_request(bld.window, min_width, min_height+options.preset_window_height);
	} else {
            bld.window->resize(min_width, min_height+options.preset_window_height);
        }
    }
    bld.preset_box_no_rack->set_visible(v);
    preset_window->on_preset_select(v, use_animations() && actions.show_rack->get_active(), options.preset_window_height);
}

/*
** UI initialization
*/

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
	portmap_window = gx_portmap::PortMapWindow::create(machine, uimanager.get_accel_group());
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

void MainWindow::change_skin(const Glib::VariantBase& value) {
    gx_gui::WaitCursor wait(bld.window);
    int idx = static_cast<const Glib::Variant<gint32>*>(&value)->get();
    theme.set_new_skin(options.skin[idx]);
    actions.skin->change_state(idx);
}

void MainWindow::add_skin_menu() {
    Glib::ustring actname = "ChangeSkin";
    actions.skin = uimanager.add_radio_action(actname);
    actions.skin->signal_activate().connect(
        sigc::mem_fun(*this, &MainWindow::change_skin));
    Glib::RefPtr<Gio::Menu> menu = uimanager.get_linked_menu("ChangeSkin");
    int idx = 0;
    for (vector<Glib::ustring>::iterator i = options.skin.skin_list.begin();
         i != options.skin.skin_list.end();
         ++i, ++idx) {
        Glib::ustring name = *i;
        std::string display = name;
        boost::replace_all(display, "_", " ");
        auto a = Gio::MenuItem::create(display, actname);
        auto target = Glib::Variant<gint32>::create(idx);
        a->set_action_and_target(actname, target);
        if (name == options.skin.name) {
            actions.skin->change_state(idx);
        }
        menu->append_item(a);
    }
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
    Gdk::RGBA colorGreen("#969292");
    labelt1.override_color(colorGreen, Gtk::STATE_FLAG_NORMAL);
    Pango::FontDescription font = labelt1.get_style_context()->get_font();
    font.set_size(10*Pango::SCALE);
    font.set_weight(Pango::WEIGHT_BOLD);
    labelt1.override_font(font);

    Gdk::RGBA colorWhite("#ffffff");
    labelt.override_color(colorWhite, Gtk::STATE_FLAG_NORMAL);
    font = labelt.get_style_context()->get_font();
    font.set_size(14*Pango::SCALE);
    font.set_weight(Pango::WEIGHT_BOLD);
    labelt.override_font(font);

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

    labelt2.override_color(colorWhite, Gtk::STATE_FLAG_NORMAL);

    font = labelt2.get_style_context()->get_font();
    font.set_size(8*Pango::SCALE);
    font.set_weight(Pango::WEIGHT_NORMAL);
    labelt2.override_font(font);

    box.show_all();

    return warn_dialog.run();
}

void MainWindow::change_latency(const Glib::VariantBase& value) {
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
    jack_nframes_t buf_size = static_cast<const Glib::Variant<gint32>*>(&value)->get();
    if (buf_size == jack->get_jack_bs()) {
        return;
    }
    actions.latency->set_current_value(buf_size);
    if (!options.no_warn_latency && gx_wait_latency_warn() != kChangeLatency) {
        Glib::signal_idle().connect_once(
            sigc::bind(
                sigc::mem_fun(*actions.latency.get(), &RadioAction::set_current_value),
                jack->get_jack_bs()));
    } else {
        if (jack_set_buffer_size(jack->client, buf_size) != 0) {
            gx_print_warning(_("Setting Jack Buffer Size"),
                             _("Could not change latency"));
            actions.latency->set_current_value(jack->get_jack_bs());
        }
    }
    gx_print_info(
        _("Jack Buffer Size"),
        boost::format(_("latency is %1%")) % jack_get_buffer_size(jack->client));
}

void MainWindow::add_latency_menu() {
    const int min_pow = 4;  // 2**4  = 16
    const int max_pow = 13; // 2**13 = 8192
    int jack_buffer_size = 16;
    Glib::ustring actname = "JackLatency";
    actions.latency = uimanager.add_radio_action(actname);
    actions.latency->signal_activate().connect(
        sigc::mem_fun(*this, &MainWindow::change_latency));
    Glib::RefPtr<Gio::Menu> menu = uimanager.get_linked_menu(actname);
    for (int i = 0; i <= max_pow-min_pow; ++i) {
        Glib::ustring name = gx_system::to_string(jack_buffer_size);
        auto a = Gio::MenuItem::create(name, actname);
        auto target = Glib::Variant<gint32>::create(jack_buffer_size);
        a->set_action_and_target(actname, target);
        menu->append_item(a);
        jack_buffer_size *= 2;
    }
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
    actions.osc_buffer_size->set_enabled(n < 1024);
}

void MainWindow::show_forum_help() {
#if GTK_MINOR_VERSION >= 24
    try {
	bld.window->show_uri(
	    "https://www.reddit.com/r/Guitarix/",
	    gtk_get_current_event_time());
    } catch (Glib::Error& e) { // seems to never happen, all errors silently ignored
	gx_print_info("guitarix help", Glib::ustring::compose(_("Uri launch error: %s"), e.what()));
	gx_print_error("guitarix help", _("failed to load online help   "));
    }
#else
    try {
        gtk_show_uri_on_window(NULL, "https://www.reddit.com/r/Guitarix/",
            gtk_get_current_event_time(), NULL);
    } catch (Glib::Error& e) { // seems to never happen, all errors silently ignored
	gx_print_info("guitarix help", Glib::ustring::compose(_("Uri launch error: %s"), e.what()));
	gx_print_error("guitarix help", _("failed to load online help   "));
    }
#endif
}

void MainWindow::gx_show_help() {
    Glib::signal_idle().connect_once(sigc::mem_fun(this, &MainWindow::show_forum_help));
}

void MainWindow::show_tonehunt() {
#if GTK_MINOR_VERSION >= 24
    try {
	bld.window->show_uri(
	    "https://tonehunt.org/models?tags%5B0%5D=nam",
	    gtk_get_current_event_time());
    } catch (Glib::Error& e) { // seems to never happen, all errors silently ignored
	gx_print_info("tonehunt", Glib::ustring::compose(_("Uri launch error: %s"), e.what()));
	gx_print_error("tonehunt", _("failed to tonehunt side   "));
    }
#else
    try {
        gtk_show_uri_on_window(NULL, "https://tonehunt.org/models?tags%5B0%5D=nam",
            gtk_get_current_event_time(), NULL);
    } catch (Glib::Error& e) { // seems to never happen, all errors silently ignored
	gx_print_info("tonehunt", Glib::ustring::compose(_("Uri launch error: %s"), e.what()));
	gx_print_error("tonehunt", _("failed to load tonehunt side   "));
    }
#endif
}

void MainWindow::gx_show_tonehunt() {
    Glib::signal_idle().connect_once(sigc::mem_fun(this, &MainWindow::show_tonehunt));
}

void MainWindow::show_rtneural() {
#if GTK_MINOR_VERSION >= 24
    try {
	bld.window->show_uri(
	    "https://tonehunt.org/models?tags%5B0%5D=aida-x",
	    gtk_get_current_event_time());
    } catch (Glib::Error& e) { // seems to never happen, all errors silently ignored
	gx_print_info("RTNeural", Glib::ustring::compose(_("Uri launch error: %s"), e.what()));
	gx_print_error("RTNeural", _("failed to aidax side   "));
    }
#else
    try {
        gtk_show_uri_on_window(NULL, "https://tonehunt.org/models?tags%5B0%5D=aida-x",
            gtk_get_current_event_time(), NULL);
    } catch (Glib::Error& e) { // seems to never happen, all errors silently ignored
	gx_print_info("RTNeural", Glib::ustring::compose(_("Uri launch error: %s"), e.what()));
	gx_print_error("RTNeural", _("failed to load aidax side   "));
    }
#endif
}

void MainWindow::gx_show_rtneural() {
    Glib::signal_idle().connect_once(sigc::mem_fun(this, &MainWindow::show_rtneural));
}

// ----menu function about
void gx_show_about() {
    static string about;
    if (about.empty()) {
        about +=_("<b>Guitarix:gx_head</b> (");
        about += GX_VERSION;
        about +=
            _(")\n\nThis Application is to a large extent provided"
            "\nwith the marvelous faust compiler.Yann Orlary"
            "\n(http://faust.grame.fr/)"
            "\n\nA large part is based on the work of Julius Orion Smith"
            "\n(http://ccrma.stanford.edu/realsimple/faust/)"
            "\nand Albert Graef\n(http://q-lang.sourceforge.net/examples.html#Faust)"
            "\n\n");

        about +=
            _("for Neural Amp Modelling it use Neural Amp Modeler Core "
            "\nby Steven Atkinson"
            "\n(https://github.com/sdatkinson/NeuralAmpModelerCore)"
            "\nthe RTNeural Network Engine used in the RTNeural Plugs"
            "\nwas developed by Jatin Chowdhury"
            "\n(https://github.com/jatinchowdhury18/RTNeural)");

        about +=
            _("\n\nfor impulse response it use zita-convolver"
            "\nby Fons Adriaensen"
            "\n(http://www.kokkinizita.net/linuxaudio/index.html)"
            "\n\nThe included IR-files are contributed by"
            "\nDavid Fau Casquel (BESTPLUGINS)"
            "\nhome: http://www.youtube.com/bestplugins"
            "\n\nauthors: Hermann Meyer &lt;brummer-@web.de&gt;"
            "\nauthors: James Warden &lt;warjamy@yahoo.com&gt;"
            "\nauthors: Andreas Degert &lt;andreas.degert@googlemail.com&gt;"
            "\nauthors: Pete Shorthose &lt;pshorthose@gmail.com&gt;"
            "\nauthors: Markus Schmidt &lt;schmidt@boomshop.net&gt;"
            "\n\nwebsite: http://guitarix.org/\n");
    }

    gx_gui::gx_message_popup(about.c_str());
}

void MainWindow::set_tooltips() {
    options.system_show_tooltips = actions.tooltips->get_active();
    gx_gui::GxBuilder::set_show_tooltips(options.system_show_tooltips);
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
	select_jack_control->set_transient_for(*bld.window);
	select_jack_control->show();
    }
}

void MainWindow::delete_select_jack_control() {
    delete select_jack_control;
    select_jack_control = 0;
}

void MainWindow::on_select_midi_channel() {
    if (select_midi_channel) {
	select_midi_channel->present();
    } else {
	select_midi_channel = SelectMidiChannel::create(options, machine);
	select_midi_channel->signal_close().connect(
	    sigc::mem_fun(*this, &MainWindow::delete_select_midi_channel));
	select_midi_channel->set_transient_for(*bld.window);
	select_midi_channel->show();
    }
}

void MainWindow::delete_select_midi_channel() {
    delete select_midi_channel;
    select_midi_channel = 0;
}

void MainWindow::set_midiout() {
    machine.set_midi_feedback(actions.midiout->get_active());
}

// show loggingbox
void MainWindow::on_log_activate() {
    if (actions.loggingbox->get_active()) {
        gint rxorg, ryorg;
        bld.window->get_position(rxorg, ryorg);
        fLoggingWindow.move(rxorg+5, ryorg+272);
        fLoggingWindow.show_all();
	on_msg_level_changed();
    } else {
        fLoggingWindow.hide();
    }
}
// show loggingbox
bool MainWindow::on_log_activated(GdkEventButton* ev) {
    if (ev->type == GDK_BUTTON_PRESS && ev->button == 1) {
    if (!actions.loggingbox->get_active()) {
		actions.loggingbox->set_active(true);
        gint rxorg, ryorg;
        bld.window->get_position(rxorg, ryorg);
        fLoggingWindow.move(rxorg+5, ryorg+272);
        fLoggingWindow.show_all();
        on_msg_level_changed();
    } else {
        fLoggingWindow.hide();
        actions.loggingbox->set_active(false);
    }
	}else if (ev->type == GDK_BUTTON_PRESS && ev->button == 2) {
        fLoggingWindow.reset_msg_level();
	}
    return true;
}

bool MainWindow::on_log_scrolled(GdkEventScroll* ev) {
    if (!actions.loggingbox->get_active()) {
		actions.loggingbox->set_active(true);
        gint rxorg, ryorg;
        bld.window->get_position(rxorg, ryorg);
        fLoggingWindow.move(rxorg+5, ryorg+272);
        fLoggingWindow.show_all();
        on_msg_level_changed();
    } else {
        fLoggingWindow.hide();
        actions.loggingbox->set_active(false);
    }
    return true;
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

void MainWindow::set_bypass_controller() {
    if (!machine.midi_get_config_mode()) {
	new gx_main_midi::MidiConnect(0, machine.get_parameter("engine.bypass"), machine);
    }
}

void MainWindow::on_livetuner_toggled() {
    if (actions.livetuner->get_active()) {
	if (actions.live_play->get_active()) {
	    live_play->display_tuner(true);
	    bld.racktuner->set_sensitive(false);
	    machine.tuner_used_for_display(true);
	} else {
	    live_play->display_tuner(false);
	    if (actions.tuner->get_active()) {
		bld.racktuner->set_sensitive(true);
		machine.tuner_used_for_display(true);
 	    } else {
		machine.tuner_used_for_display(false);
	    }
	}
    } else {
	live_play->display_tuner(false);
	bld.racktuner->set_sensitive(false);
	machine.tuner_used_for_display(false);
    }
}

void MainWindow::create_actions() {
    /*
    ** Menu actions
    */
    uimanager.add_action("EngineMenu");

    uimanager.add_action("PresetsMenu");
    uimanager.add_action("NextPreset", sigc::mem_fun(*this, &MainWindow::on_next_preset));
    uimanager.add_action("PreviusPreset", sigc::mem_fun(*this, &MainWindow::on_previus_preset));

    uimanager.add_action("SetNextPresetSwitcher",
                              sigc::mem_fun(this, &MainWindow::set_next_preset_controller));

    uimanager.add_action("SetPreviusPresetSwitcher",
                              sigc::mem_fun(this, &MainWindow::set_previus_preset_controller));

    actions.preset_list_menu = uimanager.add_radio_action("PresetListMenu");
    actions.preset_list_menu->signal_activate().connect(
        sigc::mem_fun(*this, &MainWindow::on_select_preset));

    uimanager.add_action("PluginsMenu");
    uimanager.add_action("MonoPlugins");
    uimanager.add_action("StereoPlugins");
    uimanager.add_action("TubeMenu");
    uimanager.add_action("OptionsMenu");
    uimanager.add_action("AboutMenu");

    /*
    ** engine actions
    */
    actions.jackserverconnection = uimanager.add_toggle_action("JackServerConnection");
    actions.jackserverconnection->signal_toggled().connect(
        sigc::mem_fun(*this, &MainWindow::jack_connection));

    actions.jackports = uimanager.add_toggle_action("JackPorts");
	actions.jackports->signal_toggled().connect(
        sigc::mem_fun(*this, &MainWindow::on_portmap_activate));

    actions.midicontroller = uimanager.add_toggle_action("MidiController");
    actions.midicontroller->signal_toggled().connect(
        sigc::mem_fun(*this, &MainWindow::on_miditable_toggle));

    actions.engine_mute = uimanager.add_toggle_action("EngineMute");
    actions.engine_mute_conn = actions.engine_mute->signal_toggled().connect(
        sigc::mem_fun(*this, &MainWindow::on_engine_toggled));

    actions.engine_bypass = uimanager.add_toggle_action("EngineBypass");
    actions.engine_bypass_conn = actions.engine_bypass->signal_toggled().connect(
        sigc::mem_fun(*this, &MainWindow::on_engine_toggled));

    actions.quit = uimanager.add_action(
        "Quit", sigc::hide_return(sigc::mem_fun(this, &MainWindow::on_quit)));

    /*
    ** actions to open other (sub)windows
    */
    actions.presets = uimanager.add_toggle_action("Presets");
    actions.presets->signal_toggled().connect(
        sigc::mem_fun(*this, &MainWindow::on_preset_action));

    actions.show_plugin_bar = uimanager.add_toggle_action("ShowPluginBar");
    actions.show_plugin_bar->signal_toggled().connect(
        sigc::mem_fun(*this, &MainWindow::on_show_plugin_bar));

    actions.show_rack = uimanager.add_toggle_action("ShowRack", true);
    actions.show_rack->signal_toggled().connect(
        sigc::mem_fun(*this, &MainWindow::on_show_rack));

    actions.loggingbox = uimanager.add_toggle_action("LoggingBox");
    actions.loggingbox->signal_toggled().connect(
        sigc::mem_fun(*this, &MainWindow::on_log_activate));

    actions.live_play = uimanager.add_toggle_action("Liveplay");
    actions.live_play->signal_toggled().connect(
        sigc::mem_fun(*this, &MainWindow::on_live_play));

    actions.meterbridge = uimanager.add_toggle_action("Meterbridge");
    gx_jack::GxJack *jack = machine.get_jack();
    if (jack) {
        actions.meterbridge->signal_toggled().connect(
            sigc::bind(sigc::ptr_fun(gx_child_process::Meterbridge::start_stop),
                       sigc::ref(actions.meterbridge), sigc::ref(*jack)));
    }

    actions.livetuner = uimanager.add_ui_bool_action(machine, "ui.racktuner", "LiveTuner");
    actions.livetuner->signal_toggled().connect(
        sigc::mem_fun(this, &MainWindow::on_livetuner_toggled));

    /*
    ** rack actions
    */
    actions.tuner = uimanager.add_ui_bool_action(machine, "system.show_tuner", "Tuner");
    actions.tuner->signal_toggled().connect(
        sigc::mem_fun(*this, &MainWindow::on_show_tuner));
    actions.tunermove = uimanager.add_ui_bool_action(machine, "system.stick_tuner", "Tunermove");
    actions.tunermove->signal_toggled().connect(
        sigc::mem_fun(*this, &MainWindow::on_move_tuner));
    actions.tunermidiout = uimanager.add_ui_bool_action(machine, "system.midiout_tuner", "Tunermidiout");
    actions.tunermidiout->signal_toggled().connect(
        sigc::mem_fun(*this, &MainWindow::on_midiout_tuner));

    actions.rack_config = uimanager.add_toggle_action("RackConfig");
    actions.rack_config->signal_toggled().connect(
        sigc::mem_fun(*this, &MainWindow::on_rack_configuration));

    actions.compress = uimanager.add_action(
        "Compress", sigc::mem_fun(*this, &MainWindow::on_compress_all));

    actions.expand = uimanager.add_action(
        "Expand", sigc::mem_fun(*this, &MainWindow::on_expand_all));

    actions.rackh = uimanager.add_toggle_action("RackH");
    actions.rackh->signal_toggled().connect(
        sigc::mem_fun(*this, &MainWindow::on_dir_changed));

    /*
    ** option actions
    */
    actions.show_values = uimanager.add_toggle_action("ShowValues", true);
    actions.show_values->signal_toggled().connect(
        sigc::mem_fun(*this, &MainWindow::on_show_values));

    actions.tooltips = uimanager.add_toggle_action("ShowTooltips", true);
    actions.tooltips->signal_toggled().connect(
        sigc::mem_fun(this, &MainWindow::set_tooltips));

    actions.midi_in_presets = uimanager.add_ui_bool_action(
        machine, "system.midi_in_preset", "MidiInPresets", _("Include MIDI in _presets"));

    actions.jackstartup = uimanager.add_action(
        "JackStartup", sigc::mem_fun(*this, &MainWindow::on_select_jack_control));

    actions.loadladspa = uimanager.add_action(
        "LoadLADSPA", sigc::mem_fun(this, &MainWindow::on_load_ladspa));

    uimanager.add_action(
        "ResetAll", sigc::mem_fun(machine, &gx_engine::GxMachineBase::set_init_values));

    actions.animations = uimanager.add_toggle_action("Animations", true);
    actions.animations->signal_toggled().connect(
        sigc::mem_fun(this, &MainWindow::set_animations));

    uimanager.add_action(
        "SetPresetSwitcher", sigc::mem_fun(this, &MainWindow::set_switcher_controller));

    uimanager.add_action(
        "SetBypassSwitcher", sigc::mem_fun(this, &MainWindow::set_bypass_controller));

    uimanager.add_action(
        "SetMidiChannel", sigc::mem_fun(this, &MainWindow::on_select_midi_channel));

    actions.midiout = uimanager.add_toggle_action("MidiFeedback", true);
    actions.midiout->signal_toggled().connect(
        sigc::mem_fun(this, &MainWindow::set_midiout));

    /*
    ** Help and About
    */
    uimanager.add_action("Help", sigc::mem_fun(this, &MainWindow::gx_show_help));
    uimanager.add_action("GetNAMModels", sigc::mem_fun(this, &MainWindow::gx_show_tonehunt));
    uimanager.add_action("GetRTNeuralModels", sigc::mem_fun(this, &MainWindow::gx_show_rtneural));
    uimanager.add_action("About", sigc::ptr_fun(gx_show_about));
}

void MainWindow::clear_box(Gtk::Container& box) {
    std::vector<Gtk::Widget*> l = box.get_children();
    for (std::vector<Gtk::Widget*>::iterator p = l.begin(); p != l.end(); ++p) {
        delete *p;
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
    if (!bld.window) {
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
    bld.window->set_title(s);
    actions.latency->set_enabled(v);
    actions.engine_mute->set_enabled(v);
    actions.engine_bypass->set_enabled(v);
    bld.status_image->set_sensitive(v);
    if (!v) {
        bld.jackd_image->set(pixbuf_jack_disconnected);
    } else {
        bld.jackd_image->set(pixbuf_jack_connected);
    }
}

void MainWindow::on_engine_state_change(gx_engine::GxEngineState state) {
    switch (state) {
    case gx_engine::kEngineOff:
	actions.engine_mute_conn.block();
	actions.engine_mute->set_active(true);
	actions.engine_mute_conn.unblock();
	bld.status_image->set(pixbuf_off);
	machine.msend_midi_cc(0xB0,120,127,3);
	break;
    case gx_engine::kEngineOn:
	actions.engine_mute_conn.block();
	actions.engine_bypass_conn.block();
	actions.engine_mute->set_active(false);
	actions.engine_bypass->set_active(false);
	actions.engine_mute_conn.unblock();
	actions.engine_bypass_conn.unblock();
	bld.status_image->set(pixbuf_on);
	machine.msend_midi_cc(0xB0,120,0,3);
	break;
    case gx_engine::kEngineBypass:
	actions.engine_mute_conn.block();
	actions.engine_bypass_conn.block();
	actions.engine_mute->set_active(false);
	actions.engine_bypass->set_active(true);
	actions.engine_mute_conn.unblock();
	actions.engine_bypass_conn.unblock();
	bld.status_image->set(pixbuf_bypass);
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
    int mode = bld.tuner_tuning->get_value();
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

void MainWindow::set_tuner_tet(Gxw::RackTuner& tuner) {
    Glib::ustring tet = options.get_tuner_tet();
    int t = 0;
    if (tet.find("12") !=Glib::ustring::npos) t=0;
    else if (tet.find("19") !=Glib::ustring::npos) t=1;
    else if (tet.find("24") !=Glib::ustring::npos) t=2;
    else if (tet.find("31") !=Glib::ustring::npos) t=3;
    else if (tet.find("41") !=Glib::ustring::npos) t=4;
    else if (tet.find("53") !=Glib::ustring::npos) t=5;
    else t = bld.tuner_temperament->get_value();
    machine.set_parameter_value("racktuner.temperament", t);
    tuner.set_temperament(bld.tuner_temperament->get_value());
    set_tuning(tuner);
}

void MainWindow::set_tuner_ref(Gxw::RackTuner& tuner) {
    Glib::ustring ref = options.get_tuner_ref();
    float t = atof(ref.c_str());
    machine.set_parameter_value("ui.bld.tuner_reference_pitch", t);
    tuner.set_reference_pitch(bld.tuner_reference_pitch->get_value());
    set_tuning(tuner);
}

void MainWindow::setup_tuner_temperament(Gxw::RackTuner& tuner) {
    tuner.set_temperament(bld.tuner_temperament->get_value());
    set_tuning(tuner);
}

void MainWindow::setup_tuner(Gxw::RackTuner& tuner) {
    tuner.signal_frequency_poll().connect(
	sigc::compose(
	    sigc::mem_fun(tuner, &Gxw::RackTuner::set_freq),
	    sigc::mem_fun(machine, &gx_engine::GxMachineBase::get_tuner_freq)));
    bld.tuner_mode->signal_value_changed().connect(
	sigc::compose(
	    sigc::mem_fun(tuner, &Gxw::RackTuner::set_streaming),
	    sigc::mem_fun(*bld.tuner_mode, &Gxw::Selector::get_value)));
    bld.tuner_reference_pitch->signal_value_changed().connect(
	sigc::compose(
	    sigc::mem_fun(tuner, &Gxw::RackTuner::set_reference_pitch),
	    sigc::mem_fun(*bld.tuner_reference_pitch, &Gxw::ValueDisplay::get_value)));
    bld.tuner_tuning->signal_value_changed().connect(
	sigc::bind(sigc::mem_fun(*this, &MainWindow::set_tuning), sigc::ref(tuner)));
    bld.tuner_temperament->signal_value_changed().connect(
        sigc::bind(sigc::mem_fun(*this, &MainWindow::setup_tuner_temperament), sigc::ref(tuner)));
	tuner.set_temperament(bld.tuner_temperament->get_value());
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

bool MainWindow::on_scroll_toggle(GdkEventScroll* ev) {
    if (ev->direction == GDK_SCROLL_UP) {
	if (machine.get_state() == gx_engine::kEngineOff) {
	    machine.set_state(gx_engine::kEngineOn);
	} else if (machine.get_state() == gx_engine::kEngineOn) {
	    machine.set_state(gx_engine::kEngineBypass);
	} else {
	    machine.set_state(gx_engine::kEngineOff);
	}
    } else if (ev->direction == GDK_SCROLL_DOWN) {
	if (machine.get_state() == gx_engine::kEngineOff) {
	    machine.set_state(gx_engine::kEngineBypass);
	} else if (machine.get_state() == gx_engine::kEngineBypass) {
	    machine.set_state(gx_engine::kEngineOn);
	} else {
	    machine.set_state(gx_engine::kEngineOff);
	}
    }

    return true;
}

bool MainWindow::on_toggle_insert(GdkEventButton* ev) {
    if (ev->type == GDK_BUTTON_PRESS && ev->button == 1) {
	if (machine.get_parameter_value<bool>("engine.insert")) {
		machine.set_parameter_value("engine.insert",false);
	} else {
		machine.set_parameter_value("engine.insert",true);
	}
	}
    return true;
}

bool MainWindow::on_scroll_toggle_insert(GdkEventScroll* ev) {
	if (machine.get_parameter_value<bool>("engine.insert")) {
		machine.set_parameter_value("engine.insert",false);
	} else {
		machine.set_parameter_value("engine.insert",true);
	}
    return true;
}

void MainWindow::on_insert_jack_changed(bool s) {
    if (s) {
	bld.insert_image->set(pixbuf_insert_off);
    } else {
	bld.insert_image->set(pixbuf_insert_on);
    }
}

bool MainWindow::on_jackserverconnection(GdkEventButton* ev) {
    if (ev->type == GDK_BUTTON_PRESS && ev->button == 1) {
    bool v = actions.jackserverconnection->get_active();
    actions.jackserverconnection->set_active(!v);
    }
    return true;
}

bool MainWindow::on_jackserverconnection_scroll(GdkEventScroll* ev) {
    bool v = actions.jackserverconnection->get_active();
    actions.jackserverconnection->set_active(!v);
    return true;
}

void MainWindow::on_msg_level_changed() {
    switch (fLoggingWindow.get_unseen_msg_level()) {
    case GxLogger::kWarning: bld.logstate_image->set(pixbuf_log_yellow); break;
    case GxLogger::kError:   bld.logstate_image->set(pixbuf_log_red); break;
    default:                 bld.logstate_image->set(pixbuf_log_grey); break;
    }
}

void MainWindow::on_ampdetail_switch(bool compress, bool setparam) {
    if (compress) {
	bld.ampdetail_normal->hide();
	bld.ampdetail_mini->show();
    } else {
	bld.ampdetail_mini->hide();
	bld.ampdetail_normal->show();
    }
    if (setparam) {
	machine.set_parameter_value("ui.mp_s_h", compress);
    }
}

/****************************************************************
 ** oscilloscope handling
 */

void MainWindow::set_osc_size() {
    if (options.mul_buffer > 0) {
        actions.osc_buffer_size->set_current_value(options.mul_buffer);
    }
}

void MainWindow::change_osc_buffer(const Glib::VariantBase& value) {
    gx_jack::GxJack *jack = machine.get_jack();
    options.mul_buffer = static_cast<const Glib::Variant<gint32>*>(&value)->get();
    if (!jack || jack->client) {
        machine.set_oscilloscope_mul_buffer(options.mul_buffer);
    }
    set_osc_size();
}

void MainWindow::add_osc_size_menu() {
    Glib::ustring actname = "OscBufferSize";
    actions.osc_buffer_size = uimanager.add_radio_action(actname);
    actions.osc_buffer_size->signal_activate().connect(
        sigc::mem_fun(*this, &MainWindow::change_osc_buffer), true);
    Glib::RefPtr<Gio::Menu> menu = uimanager.get_linked_menu(actname);
    for (int osc_buffer_size = 1; osc_buffer_size <= 6; osc_buffer_size++) {
        Glib::ustring name = "*" + gx_system::to_string(osc_buffer_size);
        auto a = Gio::MenuItem::create(name, actname);
        auto target = Glib::Variant<gint32>::create(osc_buffer_size);
        a->set_action_and_target(actname, target);
        menu->append_item(a);
    }
    actions.osc_buffer_size->change_state(options.mul_buffer);
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
	// run only one time when jackd is running
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
    if (!bld.window->get_window()) {
        return;
    }
    Gtk::MenuItem *item = uimanager.find_item("EngineMenu");
    if (item) {
        Gtk::Menu *m = item->get_submenu();
        if (m) {
            m->popup(2, gtk_get_current_event_time());
            return;
        }
    }
    assert(false);
}

void MainWindow::on_nsm_save() {
    if (!bld.window->get_window()) {
        return;
    }
    bld.window->get_window()->get_root_origin(options.mainwin_x, options.mainwin_y);
    int mainwin_width;
    bld.window->get_size(mainwin_width, options.mainwin_height);
    options.write_ui_vars();
}

bool MainWindow::on_window_state_changed(GdkEventWindowState* event) {
    if (event->changed_mask & event->new_window_state & (Gdk::WINDOW_STATE_ICONIFIED|Gdk::WINDOW_STATE_WITHDRAWN)) {
        bld.window->get_window()->get_root_origin(options.mainwin_x, options.mainwin_y);
    }
    return false;
}

void MainWindow::hide_extended_settings() {
    if (!is_visible || (bld.window->get_window()->get_state()
        & (Gdk::WINDOW_STATE_ICONIFIED|Gdk::WINDOW_STATE_WITHDRAWN))) {
        bld.window->move(options.mainwin_x, options.mainwin_y);
        bld.window->present();
        if (nsmsig.nsm_session_control) {
            nsmsig.trigger_nsm_gui_is_shown();
            options.mainwin_visible = 1;
        }
       // bld.window->deiconify();
    } else {
        bld.window->hide();
        if (nsmsig.nsm_session_control) {
            nsmsig.trigger_nsm_gui_is_hidden();
            options.mainwin_visible = 0;
        }
       // bld.window->iconify();
    }
}

void MainWindow::run() {
    int port = options.get_rpcport();
    if (machine.get_jack() && port != RPCPORT_DEFAULT && port != RPCPORT_NONE) {
        machine.start_socket(sigc::ptr_fun(Gtk::Main::quit), options.get_rpcaddress(), port);
        bld.window->show();
    if (options.get_liveplaygui()) bld.liveplay_button->set_active();
        Gtk::Main::run();
    } else {
        if (!nsmsig.nsm_session_control || options.mainwin_visible) {
            bld.window->show();
            if (nsmsig.nsm_session_control) nsmsig.trigger_nsm_gui_is_shown();
        } else {
            if (nsmsig.nsm_session_control) nsmsig.trigger_nsm_gui_is_hidden();
        }
    if (nsmsig.nsm_session_control) machine.disable_save_on_exit(true);
    if (options.get_liveplaygui()) bld.liveplay_button->set_active();
    Gtk::Main::run();
    }
}

bool MainWindow::on_meter_button_release(GdkEventButton* ev) {
    if (ev->button == 1) {
        for (unsigned int i = 0; i < sizeof(bld.fastmeter)/sizeof(bld.fastmeter[0]); i++) {
            bld.fastmeter[i]->clear();
        }
        return true;
    }
    return false;
}

void MainWindow::display_preset_msg(const Glib::ustring& bank, const Glib::ustring& preset) {
    bld.preset_status->set_text(bank + " / " + preset);
}

bool MainWindow::on_key_press_event(GdkEventKey *event) {
    if ((event->state & Gtk::AccelGroup::get_default_mod_mask()) != 0) {
	return false;
    }
    if (event->keyval >= GDK_KEY_0 && event->keyval <= GDK_KEY_9) {
	keyswitch.process_preset_key(event->keyval - GDK_KEY_0);
	return true;
    }
    if (event->keyval >= GDK_KEY_KP_0 && event->keyval <= GDK_KEY_KP_9) {
	keyswitch.process_preset_key(event->keyval - GDK_KEY_KP_0);
	return true;
    }
    if (event->keyval >= GDK_KEY_a && event->keyval <= GDK_KEY_z) {
	keyswitch.process_bank_key(event->keyval - GDK_KEY_a);
	return true;
    }
    return false;
}

void MainWindow::on_nsm_quit() {
    options.set_hideonquit(false);
    delete_ladspalist_window();
    machine.stop_socket();
    Gtk::Main::quit();
}

bool MainWindow::on_quit() {
    if (options.get_hideonquit()) {
        machine.save_to_state();
        //hide_extended_settings();
        usleep(100000);
        hide_extended_settings();
        return true;
    }
    if (ladspalist_window && !ladspalist_window->check_exit()) {
	return true;
    }
    machine.stop_socket();
    Gtk::Main::quit();
    return false;
}

void MainWindow::amp_controls_visible(Gtk::Range *rr) {
    //FIXME
    bool v = std::abs(rr->get_value() - machine.get_parameter("tube.select").getUpperAsFloat()) < 0.5;
    const char *knobs1[] = {"gxmediumknobpregain","gxmediumknobdrive","gxmediumknobdist","gxmediumknobgain", "labelpregain:effekt_label", "labeldrive:effekt_label", "labeldist:effekt_label", "labelgain:effekt_label"};
    const char *knobs2[] = {"gxbigknobgain", "labelgain2:effekt_label"};
    for (unsigned int i = 0; i < sizeof(knobs1)/sizeof(knobs1[1]); ++i) {
        Gtk::Widget *w;
        bld->find_widget(knobs1[i], w);
        w->set_visible(!v);
    }
    for (unsigned int i = 0; i < sizeof(knobs2)/sizeof(knobs2[1]); ++i) {
        Gtk::Widget *w;
        bld->find_widget(knobs2[i], w);
        w->set_visible(v);
    }
}

MainWindow::MainWindow(gx_engine::GxMachineBase& machine_, gx_system::CmdlineOptions& options_,
		       NsmSignals& nsmsig_ ,GxTheme& theme_, Gtk::Window *splash, const Glib::ustring& title)
    : sigc::trackable(),
      options(options_),
      machine(machine_),
      nsmsig(nsmsig_),
      theme(theme_),
      bld(options_, machine_),
      freezer(),
      gx_head_icon(Gdk::Pixbuf::create_from_file(options.get_pixmap_filepath("gx_head.png"))),
      boxbuilder(machine_, gx_head_icon),
      uimanager(UIManager(options.get_builder_filepath("menu.ui"), bld.menubar)),
      actions(),
      plugin_dict(machine_, options_, *bld.effects_toolpalette, boxbuilder, uimanager),
      oldpos(0),
      scrl_size_x(-1),
      scrl_size_y(-1),
      pre_act(false),
      is_visible(false),
      preset_list_menu_bank(),
      live_play(),
      preset_window(),
      portmap_window(0),
      select_jack_control(0),
      select_midi_channel(0),
      fLoggingWindow(),
      amp_radio_menu(machine_, "tube.select"),
      pixbuf_insert_on(Gdk::Pixbuf::create_from_file(options.get_pixmap_filepath("insert_on.png"))),
      pixbuf_insert_off(Gdk::Pixbuf::create_from_file(options.get_pixmap_filepath("insert_off.png"))),
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
      keyswitch(machine, sigc::mem_fun(this, &MainWindow::display_preset_msg)),
      ladspalist_window() {

    nsmsig.signal_trigger_nsm_show_gui().connect(
        sigc::mem_fun(this, &MainWindow::hide_extended_settings));

    nsmsig.signal_trigger_nsm_hide_gui().connect(
        sigc::mem_fun(this, &MainWindow::hide_extended_settings));

    nsmsig.signal_trigger_nsm_save_gui().connect(
        sigc::mem_fun(this, &MainWindow::on_nsm_save));

    /*
    ** create actions and some parameters
    */
    create_actions();
    bld.window->insert_action_group("app", uimanager.get_action_group());

    /*
    ** load key accelerator table and glade window definition
    **
    ** at this point all parameters that are used in the main window glade file must be defined
    */
    //Gtk::AccelMap::load(options.get_builder_filepath("accels_rc"));

#ifndef NDEBUG
    theme.set_window(bld.window);
#endif
    bld.rackcontainer->set_homogeneous(true); // setting it in glade is awkward to use with glade tool

    // remove marker labels from boxes (used in glade to make display clearer)
    clear_box(*bld.monocontainer);
    clear_box(*bld.stereorackcontainerH);
    clear_box(*bld.stereorackcontainerV);
    clear_box(*bld.preset_box_no_rack);

    // preset window also creates some actions
    preset_window = new PresetWindow(bld, machine, options, actions, uimanager);

    uimanager.set_accelerators_from_menu();
    if (!machine.get_jack()) {
        uimanager.find_item("JackLatency")->set_visible(false);
        uimanager.find_item("JackServerConnection")->set_visible(false);
        uimanager.find_item("JackPorts")->set_visible(false);
        uimanager.find_item("Meterbridge")->set_visible(false);
        //actions.latency->set_visible(false);
        //actions.jackserverconnection->set_visible(false);
        //actions.jackports->set_visible(false);
        //actions.meterbridge->set_visible(false);
    }

    // add dynamic submenus
    if (!options.get_clear_rc()) {
        add_skin_menu();
    }
    add_latency_menu();
    add_osc_size_menu();
    amp_radio_menu.setup(uimanager);
    add_preset_key_accelerators();

    // add menubar, accelgroup and icon to main window
    bld.window->add_accel_group(uimanager.get_accel_group());
    bld.window->set_icon(gx_head_icon);
    boxbuilder.set_accelgroup(uimanager.get_accel_group());

    // replace menuitem label when needed
    Gtk::MenuItem *item = uimanager.find_item("Quit");
    if(options.get_hideonquit()) {
        item->set_label("Hide");
    }

    /*
    ** connect main window signals
    */
    bld.window->signal_window_state_event().connect(
	sigc::mem_fun(*this, &MainWindow::on_window_state_changed));
    bld.window->signal_delete_event().connect(
	sigc::hide(sigc::mem_fun(this, &MainWindow::on_quit)));
    bld.window->signal_configure_event().connect_notify(
	sigc::mem_fun(*this, &MainWindow::on_configure_event));
    bld.window->signal_visibility_notify_event().connect(
	sigc::mem_fun(*this, &MainWindow::on_visibility_notify));
    bld.window->signal_key_press_event().connect(
	sigc::mem_fun(*this, &MainWindow::on_key_press_event));

    /*
    ** status icon signal connections
    */
    if (!options.get_hideonquit()) {
        status_icon->signal_popup_menu().connect(
        sigc::mem_fun(*this, &MainWindow::systray_menu));
    }
    status_icon->signal_activate().connect(
    sigc::mem_fun(*this, &MainWindow::hide_extended_settings));

    // add rack container
    bld.stereorackcontainerV->pack_start(plugin_dict.get_stereorackcontainer(), Gtk::PACK_EXPAND_WIDGET);
    bld.monocontainer->pack_start(plugin_dict.get_monorackcontainer(), Gtk::PACK_EXPAND_WIDGET);

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

    /*
    ** GxSettings signal connections
    */
    machine.signal_presetlist_changed().connect(
	sigc::mem_fun(*this, &MainWindow::rebuild_preset_menu));
    machine.signal_selection_changed().connect(
	sigc::mem_fun(*this, &MainWindow::show_selected_preset));

    /*
    ** DnD setup for effects toolpalette
    */
    std::vector<Gtk::TargetEntry> listTargets;
    listTargets.push_back(Gtk::TargetEntry("application/x-guitarix-mono", Gtk::TARGET_SAME_APP, 1));
    listTargets.push_back(Gtk::TargetEntry("application/x-guitarix-stereo", Gtk::TARGET_SAME_APP, 2));

    /*
    ** init jack connection image widget
    */
    if (jack) {
	bld.jackd_image->set(pixbuf_jack_disconnected);
    bld.jackd_image->get_parent()->add_events(Gdk::SCROLL_MASK);
    bld.jackd_image->get_parent()->signal_button_press_event().connect(
	sigc::mem_fun(*this, &MainWindow::on_jackserverconnection));
    bld.jackd_image->get_parent()->signal_scroll_event().connect(
	sigc::mem_fun(*this, &MainWindow::on_jackserverconnection_scroll));
	//bld.jackd_image->get_parent()->signal_button_press_event().connect(
	//    sigc::bind_return(
	//	sigc::group(
	//	    sigc::ptr_fun(toggle_action),
	//	    actions.jackserverconnection),
	//	true));
    } else {
	bld.jackd_image->hide();
    }

    /*
    ** setup racktuner parameter and signals
    */
    setup_tuner(*bld.racktuner);
    bld.tuner_on_off->set_name("effect_on_off");
    bld.tuner_on_off->signal_toggled().connect(
	sigc::compose(
	    sigc::mem_fun(*bld.racktuner, &Gxw::RackTuner::set_sensitive),
	    sigc::mem_fun(*bld.tuner_on_off, &Gxw::Switch::get_active)));
    bld.racktuner->signal_poll_status_changed().connect(
	sigc::mem_fun(machine, &gx_engine::GxMachineBase::tuner_used_for_display));

    /*
    ** fastmeter initialization and signal connections
    */
    for (unsigned int i = 0; i < sizeof(bld.fastmeter)/sizeof(bld.fastmeter[0]); ++i) {
        bld.fastmeter[i]->signal_button_release_event().connect(
            sigc::mem_fun(*this, &MainWindow::on_meter_button_release));
    }

    /*
    ** amp top box signal connections
    */
    bld.ampdetail_compress->signal_clicked().connect(
	sigc::bind(sigc::mem_fun(*this, &MainWindow::on_ampdetail_switch), true, true));
    bld.ampdetail_expand->signal_clicked().connect(
	sigc::bind(sigc::mem_fun(*this, &MainWindow::on_ampdetail_switch), false, true));
    machine.signal_parameter_value<bool>("ui.mp_s_h").connect(
	sigc::bind(sigc::mem_fun(*this, &MainWindow::on_ampdetail_switch), false));

    /*
    ** init status image widget
    */
    bld.status_image->set(pixbuf_on);
    bld.status_image->get_parent()->add_events(Gdk::SCROLL_MASK);
    gx_gui::connect_midi_controller(bld.status_image->get_parent(), "engine.mute", machine);
    bld.status_image->get_parent()->signal_button_press_event().connect(
	sigc::mem_fun(*this, &MainWindow::on_toggle_mute));
    bld.status_image->get_parent()->signal_scroll_event().connect(
	sigc::mem_fun(*this, &MainWindow::on_scroll_toggle));
    on_engine_state_change(machine.get_state());

    /*
    ** init insert image widget
    */
    bld.insert_image->set(pixbuf_insert_on);
    bld.insert_image->get_parent()->add_events(Gdk::SCROLL_MASK);
    gx_gui::connect_midi_controller(bld.insert_image->get_parent(), "engine.insert", machine);
    bld.insert_image->get_parent()->signal_button_press_event().connect(
	sigc::mem_fun(*this, &MainWindow::on_toggle_insert));
    bld.insert_image->get_parent()->signal_scroll_event().connect(
	sigc::mem_fun(*this, &MainWindow::on_scroll_toggle_insert));
    gx_engine::BoolParameter& ip = machine.get_parameter("engine.insert").getBool();
    ip.signal_changed().connect(sigc::mem_fun(*this, &MainWindow::on_insert_jack_changed));

    /*
    ** connect buttons with actions
    */
    UIManager::set_widget_action(bld.show_rack_button, actions.show_rack);
    UIManager::set_widget_action(bld.rack_order_h_button, actions.rackh);
    UIManager::set_widget_action(bld.config_mode_button, actions.rack_config);
    UIManager::set_widget_action(bld.liveplay_button, actions.live_play);
    UIManager::set_widget_action(bld.tuner_button, actions.tuner);
    UIManager::set_widget_action(bld.effects_button, actions.show_plugin_bar);
    UIManager::set_widget_action(bld.presets_button, actions.presets);
    UIManager::set_widget_action(bld.compress_button, actions.compress);
    UIManager::set_widget_action(bld.expand_button, actions.expand);

    /*
    ** setup window initial configuration
    */
    bld.tunerbox->set_visible(machine.get_parameter_value<bool>("system.show_tuner"));
    bld.racktuner->set_sensitive(machine.get_parameter_value<bool>("ui.racktuner"));
    actions.show_plugin_bar->set_active(false);

    /*
    ** create liveplay and setup liveplay racktuner
    */
    live_play = new Liveplay(options, machine, options.get_builder_filepath("liveplay.glade"),
                             actions, uimanager.get_action_group());
    setup_tuner(live_play->get_tuner());
    live_play->get_tuner().signal_poll_status_changed().connect(
	sigc::mem_fun1(machine, &gx_engine::GxMachineBase::tuner_used_for_display));

    /*
    ** init logging window and logstate image widget
    */
    fLoggingWindow.set_transient_for(*bld.window);
    fLoggingWindow.set_icon(gx_head_icon);
    fLoggingWindow.signal_msg_level_changed().connect(
	sigc::mem_fun(*this, &MainWindow::on_msg_level_changed));
    fLoggingWindow.signal_hide().connect(
        sigc::bind(
            sigc::mem_fun(*actions.loggingbox.get(), &ToggleAction::set_active),
            false));
    on_msg_level_changed();
    bld.logstate_image->get_parent()->add_events(Gdk::SCROLL_MASK);
    bld.logstate_image->get_parent()->signal_button_press_event().connect(
    sigc::mem_fun(*this, &MainWindow::on_log_activated));
    bld.logstate_image->get_parent()->signal_scroll_event().connect(
    sigc::mem_fun(*this, &MainWindow::on_log_scrolled));

    /*
    ** load plugin definitions into plugin_dict, add to effects_toolpalette
    **
    ** icons will be added after state loading when we know the skin
    ** UI definitions will be loaded on demand
    */
    plugin_dict.add_bare("ampstack", bld.amp_background);
    //bld.effects_toolpalette->show();

    // call some action functions to sync state
    // with settings defined in create_actions()
    actions.rackh->set_active(options.system_order_rack_h);
    actions.presets->set_active(options.system_show_presets);
    actions.show_plugin_bar->set_active(options.system_show_toolbar);
    actions.show_rack->set_active(options.system_show_rack);
    actions.show_values->set_active(options.system_show_value);
    actions.tooltips->set_active(options.system_show_tooltips);
    actions.animations->set_active(options.system_animations);
    actions.midiout->set_active(machine.get_midi_feedback());

    if (!title.empty()) {
	bld.window->set_title(title);
    }

    /*
    ** Jack client connection and subsequent initializations
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
	bld.window->set_default_size(-1, min(options.window_height, options.mainwin_height));
    }

    // set window position (make this optional??)
    if (options.mainwin_x > 0) {
	bld.window->move(options.mainwin_x, options.mainwin_y);
    }

    Gtk::Range *rr;
    bld->find_widget("gxselector1:amp_selector", rr);
    rr->signal_value_changed().connect(
	sigc::bind(
	    sigc::mem_fun(this, &MainWindow::amp_controls_visible),
	    rr));
    amp_controls_visible(rr);

    // set insert_image state
	if (machine.get_parameter_value<bool>("engine.insert")) {
		bld.insert_image->set(pixbuf_insert_off);
		machine.set_jack_insert(true);
	} else {
		bld.insert_image->set(pixbuf_insert_on);
		machine.set_jack_insert(false);
	}
    bool c = machine.get_parameter_value<bool>("ui.all_s_h");
    bld.compress_button->set_visible(!c);
    bld.expand_button->set_visible(c);
    if (!options.get_tuner_tet().empty()) set_tuner_tet(*bld.racktuner);
    if (!machine.get_jack()) on_move_tuner();

    machine.set_update_parameter(this, "maxlevel.left", true);
    machine.set_update_parameter(this, "maxlevel.right", true);
    machine.set_update_parameter(this, "hardlim.vleft", true);
    machine.set_update_parameter(this, "hardlim.vright", true);
 }

MainWindow::~MainWindow() {
    machine.set_update_parameter(this, "maxlevel.left", false);
    machine.set_update_parameter(this, "maxlevel.right", false);
    machine.set_update_parameter(this, "hardlim.vleft", false);
    machine.set_update_parameter(this, "hardlim.vright", false);
#if false   // set true to generate a new keyboard accel file
    gtk_accel_map_add_filter("<Actions>/Main/ChangeSkin_*");
    gtk_accel_map_add_filter("<Actions>/Main/Enum_tube.select.*");
    gtk_accel_map_add_filter("<Actions>/Main/Latency_*");
    gtk_accel_map_add_filter("<Actions>/Main/Plugin_*");
    gtk_accel_map_add_filter("<Actions>/PresetList/PresetList_*");
    Gtk::AccelMap::save(options.get_user_filepath("accels_rc"));
#endif
#ifndef NDEBUG
    theme.set_window(nullptr);
#endif
    int mainwin_width;
    bld.window->get_size(mainwin_width, options.mainwin_height);
    Glib::RefPtr<Gdk::Window> win = bld.window->get_window();
    if (win) {
	win->get_root_origin(options.mainwin_x, options.mainwin_y);
    }
    if (actions.presets->get_active()) {
	options.preset_window_height = bld.preset_scrolledbox->get_allocation().get_height();
    }
    delete live_play;
    delete preset_window;
    //if (ladspalist_window) {
	//delete ladspalist_window;
	//ladspalist_window = 0;
    //}
}
