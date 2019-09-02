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
 ** class PluginUI
 **
 ** This class represents a rack unit. It refers to an engine
 ** plugin. The user interface in the rack is loaded on demand.
 **
 ** It is responsible for reflecting any changes done to display
 ** parameter variables (box_visible, flat/expanded format, ordering).
 **
 ** Registering with an GxUI is done in PluginDict.
 **
 ** When a preset load is in progress re-ordering is blocked.
 ** MainWindow connects RackContainer::check_order() to
 ** GxSettings::signal_selection_changed so that ordering will be done
 ** when the load is finished.
 **
 */

PluginUI::PluginUI(MainWindow& main_, const char *name,
		   const Glib::ustring& tooltip_)
    : merge_id(0),
      action(),
      plugin(main_.get_machine().pluginlist_lookup_plugin(name)),
      tooltip(tooltip_),
      shortname(),
      icon(),
      group(),
      toolitem(),
      main(main_),
      rackbox(),
      hidden(false),
      hidden_by_move(false) {
    if (plugin->get_pdef()->description && tooltip.empty()) {
	tooltip = plugin->get_pdef()->description;
    }
    plugin->get_pdef()->flags |= gx_engine::PGNI_UI_REG;
}

PluginUI::~PluginUI() {
    delete rackbox;
    if (toolitem) {
	if (group) {
	    group->remove(*toolitem);
	}
	delete toolitem;
    }
    plugin->get_pdef()->flags &= ~gx_engine::PGNI_UI_REG;
}

void PluginUI::unset_ui_merge_id(Glib::RefPtr<Gtk::UIManager> uimanager) {
    if (merge_id) {
	uimanager->remove_ui(merge_id);
	merge_id = 0;
    }
}

void PluginUI::on_plugin_preset_popup() {
    main.plugin_preset_popup(plugin->get_pdef());
}

bool PluginUI::is_registered(gx_engine::GxMachineBase& m, const char *name) {
    return m.pluginlist_lookup_plugin(name)->get_pdef()->flags & gx_engine::PGNI_UI_REG;
}

void PluginUI::compress(bool state) {
    plugin->set_plug_visible(state);
    if (rackbox) {
	if (rackbox->can_compress()) {
	    rackbox->swtch(state);
	}
    }
}

void PluginUI::set_action(Glib::RefPtr<Gtk::ToggleAction>& act)
{
    action = act;
    action->signal_toggled().connect(sigc::mem_fun(*this, &PluginUI::on_action_toggled));
}

void PluginUI::on_action_toggled() {
    if (rackbox && action->get_active() == rackbox->get_box_visible()) {
	return;
    }
    if (action->get_active()) {
	display_new();
    } else {
	display(false, true);
    }
}

void PluginUI::hide(bool animate) {
    plugin->set_on_off(false);
    if (rackbox) {
	rackbox->display(false, animate);
	main.add_icon(get_id());
    }
}

void PluginUI::show(bool animate) {
    if (!rackbox) {
	rackbox = main.add_rackbox(*this, plugin->get_plug_visible(), -1, animate);
	set_active(true);
    } else {
	rackbox->display(true, animate);
    }
    if (hidden) {
	rackbox->hide();
    }
    main.hide_effect(get_id());
}

void PluginUI::display(bool v, bool animate) {
    // this function hides the rackbox. It could also destroy it (or
    // some other function could do it, e.g. when unloading a module),
    // but currently there are too many memory leaks in the stack based
    // builder.
    plugin->set_box_visible(v);
    if (v) {
	main.get_machine().insert_rack_unit(get_id(), "", get_type());
	hidden = false;
	show(animate);
    } else {
	main.get_machine().remove_rack_unit(get_id(), get_type());
	hide(animate);
    }
}

void PluginUI::display_new(bool unordered) {
    plugin->set_plug_visible(false);
    if (rackbox) {
	rackbox->swtch(false);
    }
    display(true, true);
    if (!unordered) {
	rackbox->get_parent()->reorder(get_id(), -1);
    }
}

void PluginUI::update_rackbox() {
    if (!rackbox) {
	return;
    }
    if (plugin->get_box_visible()) {
	RackContainer::rackbox_list l = rackbox->get_parent()->get_children();
	int n = 0;
	for (RackContainer::rackbox_list::iterator i = l.begin(); i != l.end(); ++i, ++n)
	    if (*i == rackbox) {
		break;
	    }
    display(false,false);
	delete rackbox;
    rackbox = 0;
    display(true,false);
    rackbox->get_parent()->reorder(get_id(), n);
	//rackbox = main.add_rackbox(*this, plugin->get_plug_visible(), n, false);
    } else {
	delete rackbox;
	rackbox = 0;
    }
}

bool plugins_by_name_less(PluginUI *a, PluginUI *b) {
    int res = a->get_type() - b->get_type();
    if (res == 0) {
	gchar *an = g_utf8_casefold(a->get_shortname(), 1);
	gchar *bn = g_utf8_casefold(b->get_shortname(), 1);
	res = g_utf8_collate(an, bn);
	g_free(an);
	g_free(bn);
    }
    return res < 0;
}


/****************************************************************
 ** class PluginDict
 */

void PluginDict::add(PluginUI *p) {
    insert(pair<std::string, PluginUI*>(p->get_id(), p));
}

void PluginDict::remove(PluginUI *p) {
    std::map<std::string, PluginUI*>::iterator i = find(p->get_id());
    assert(i != end());
    erase(i);
}

void PluginDict::cleanup() {
    for (std::map<std::string, PluginUI*>::iterator i = begin(); i != end(); ++i) {
	delete i->second;
    }
    clear();
}

PluginDict::~PluginDict() {
    cleanup();
}

void PluginDict::compress(bool state) {
    for (std::map<std::string, PluginUI*>::iterator i = begin(); i != end(); ++i) {
       i->second->compress(state);
   }
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
    Glib::RefPtr<Gdk::Visual> rgba = screen->get_rgba_visual();
    if (screen->is_composited()) {
	window = new Gtk::Window(Gtk::WINDOW_POPUP);
	if (rgba) { // else will look ugly..
	    gtk_widget_set_visual(GTK_WIDGET(window->gobj()), rgba->gobj());
	}
    }
    create_drag_icon_pixbuf(plugin, rgba, options);
    int w = drag_icon_pixbuf->get_width();
    int h = drag_icon_pixbuf->get_height();
    int h2 = (h/2)-2;
    int w2 = std::min(std::max(0, xoff), w-gradient_length/2) - 4;
    if (window) {
	window->set_size_request(w, h);
	window->signal_draw().connect(sigc::mem_fun(*this, &DragIcon::icon_draw));
	//context->set_icon_widget(window, w2, h2);
	gtk_drag_set_icon_widget(context->gobj(), GTK_WIDGET(window->gobj()), w2, h2);
    } else {
	context->set_icon(drag_icon_pixbuf, w2, h2);
    }
}

DragIcon::~DragIcon() {
    delete window;
}

bool DragIcon::icon_draw(const Cairo::RefPtr<Cairo::Context> &cr) {
    Gdk::Cairo::set_source_pixbuf(cr, drag_icon_pixbuf, 0, 0);
    cr->paint();
    return true;
}

void DragIcon::create_drag_icon_pixbuf(const PluginUI& plugin, Glib::RefPtr<Gdk::Visual> rgba, gx_system::CmdlineOptions& options) {
    Gtk::OffscreenWindow w;
    w.signal_draw().connect(sigc::bind(sigc::mem_fun(*this, &DragIcon::window_draw), sigc::ref(w)));
    if (rgba) {
        gtk_widget_set_visual(GTK_WIDGET(w.gobj()), rgba->gobj());
    }
    Gtk::Widget *r = RackBox::create_drag_widget(plugin, options);
    w.add(*r);
    w.show_all();
    w.get_window()->process_updates(true);
}

static void destroy_data(const guint8 *data) {
    delete[] data;
}

bool DragIcon::window_draw(const Cairo::RefPtr<Cairo::Context> &cr, Gtk::OffscreenWindow& widget) {
    cr->set_operator(Cairo::OPERATOR_SOURCE);
    cr->set_source_rgba(0,0,0,0);
    cr->paint();
    Gtk::Widget *child = widget.get_child();
    if (child) {
	widget.propagate_draw(*child, cr);
    }
    Cairo::RefPtr<Cairo::Surface> x_surf = cr->get_target();
    int w = widget.get_window()->get_width();
    int h = widget.get_window()->get_height();
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

bool MiniRackBox::on_my_leave_out(GdkEventCrossing *focus) {
    if (!mconbox.get_visible()) {
        Glib::RefPtr<Gdk::Window> window = this->get_window();
        window->set_cursor();
    }
    return true;
}

bool MiniRackBox::on_my_enter_in(GdkEventCrossing *focus) {
    if (!mconbox.get_visible()) {
        Glib::RefPtr<Gdk::Window> window = this->get_window();
        Glib::RefPtr<Gdk::Display> disp = this->get_display();
        Glib::RefPtr<Gdk::Cursor> cursor(Gdk::Cursor::create(disp, Gdk::HAND1));
        window->set_cursor(cursor);
    }
    return true;
}

MiniRackBox::MiniRackBox(RackBox& rb, gx_system::CmdlineOptions& options)
    : Gtk::HBox(),
      evbox(),
      mconbox(false, 4),
      mb_expand_button(),
      mb_delete_button(),
      preset_button(),
      on_off_switch("switchit"),
      toggle_on_off(rb.main.get_machine(), &on_off_switch, rb.plugin.plugin->id_on_off()) {
    if (strcmp(rb.plugin.get_id(), "ampstack") != 0) { // FIXME
        gx_gui::connect_midi_controller(&on_off_switch, rb.plugin.plugin->id_on_off().c_str(), rb.main.get_machine());

        if (!szg_label) {
            szg_label = Gtk::SizeGroup::create(Gtk::SIZE_GROUP_HORIZONTAL);
        }
        evbox.set_visible_window(false);
        evbox.signal_leave_notify_event().connect(sigc::mem_fun(*this, &MiniRackBox::on_my_leave_out));
        evbox.signal_enter_notify_event().connect(sigc::mem_fun(*this, &MiniRackBox::on_my_enter_in));
        add(evbox);
    
        Gtk::Alignment *al = new Gtk::Alignment();
        al->set_padding(0, 4, 0, 0);
        al->set_border_width(0);
    
        evbox.add(*manage(al));
    
        Gtk::HBox *box = new Gtk::HBox();
        Gtk::HBox *top = new Gtk::HBox();
        al->add(*manage(box));
    
        this->set_spacing(0);
        this->set_border_width(0);
    
        box->set_spacing(0);
        box->set_border_width(0);
    
        top->set_spacing(4);
        top->set_border_width(0);
        top->set_name("rack_unit_title_bar");
    
        box->pack_start(*manage(rb.wrap_bar()), Gtk::PACK_SHRINK);
        box->pack_start(*manage(top));
        box->pack_start(*manage(rb.wrap_bar()), Gtk::PACK_SHRINK);
    
        top->pack_start(on_off_switch, Gtk::PACK_SHRINK);
        on_off_switch.set_name("effect_on_off");
        Gtk::Widget *effect_label = RackBox::make_label(rb.plugin, options);
        szg_label->add_widget(*manage(effect_label));
        top->pack_start(*manage(effect_label), Gtk::PACK_SHRINK);
    
        top->pack_start(mconbox, Gtk::PACK_EXPAND_WIDGET);
    
        mb_expand_button = rb.make_expand_button(true);
        top->pack_end(*manage(mb_expand_button), Gtk::PACK_SHRINK);
        if (!(rb.plugin.plugin->get_pdef()->flags & PGN_NO_PRESETS)) {
            preset_button = rb.make_preset_button();
            top->pack_end(*manage(preset_button), Gtk::PACK_SHRINK);
        }
        mb_delete_button = make_delete_button(rb);
        mb_delete_button->set_no_show_all(true);
        top->pack_end(*manage(mb_delete_button), Gtk::PACK_SHRINK);
#ifdef USE_SZG
        RackBox::szg->add_widget(*al);
#else
        al->set_size_request(32, -1);
#endif
    } else { // special minibox for main amp in config mode
        if (!szg_label) {
            szg_label = Gtk::SizeGroup::create(Gtk::SIZE_GROUP_HORIZONTAL);
        }
        evbox.set_visible_window(false);
        evbox.signal_leave_notify_event().connect(sigc::mem_fun(*this, &MiniRackBox::on_my_leave_out));
        evbox.signal_enter_notify_event().connect(sigc::mem_fun(*this, &MiniRackBox::on_my_enter_in));
        add(evbox);

        Gtk::Alignment *al = new Gtk::Alignment();
        al->set_padding(0, 4, 0, 0);
        al->set_border_width(0);

        Gtk::HBox *box = new Gtk::HBox();
        Gtk::HBox *top = new Gtk::HBox();
        evbox.add(*manage(box));

        top->set_name("rack_unit_title_bar");
        Gtk::Widget *effect_label = RackBox::make_label(rb.plugin, options);
        szg_label->add_widget(*manage(effect_label));
        top->pack_start(*manage(effect_label), Gtk::PACK_SHRINK);
        top->pack_start(mconbox, Gtk::PACK_EXPAND_WIDGET);
        box->pack_start(*manage(al), Gtk::PACK_SHRINK);
        box->pack_start(*manage(top));
#ifdef USE_SZG
        RackBox::szg->add_widget(*al);
#else
        al->set_size_request(64, 32);
#endif
    }
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
	if (preset_button) {
	    preset_button->hide();
	}
	if (mb_expand_button) {
	    mb_expand_button->hide();
	}
	if (mb_delete_button) {
	    mb_delete_button->show();
	}
    } else {
	mconbox.show();
	if (preset_button) {
	    preset_button->show();
	}
	if (mb_expand_button) {
	    mb_expand_button->show();
	}
	if (mb_delete_button) {
	    mb_delete_button->hide();
	}
    }
}


/****************************************************************
 ** class PluginPresetPopup
 */

/*
** InputWindow
*/

class InputWindow: public Gtk::Window {
private:
    Glib::ustring name;
    void on_cancel();
    void on_ok(Gtk::Entry *e);
    virtual bool on_key_press_event(GdkEventKey *event);
    static InputWindow* create_from_builder(
	BaseObjectType* cobject, Glib::RefPtr<gx_gui::GxBuilder> bld, const Glib::ustring& save_name_default);
    InputWindow(BaseObjectType* cobject, Glib::RefPtr<gx_gui::GxBuilder> bld, const Glib::ustring& save_name_default);
public:
    ~InputWindow();
    static InputWindow *create(const gx_system::CmdlineOptions& options, const Glib::ustring& save_name_default);
    void run();
    Glib::ustring& get_name() { return name; }
};

InputWindow *InputWindow::create_from_builder(BaseObjectType* cobject, Glib::RefPtr<gx_gui::GxBuilder> bld,
					      const Glib::ustring& save_name_default) {
    return new InputWindow(cobject, bld, save_name_default);
}

InputWindow::~InputWindow() {
}

InputWindow *InputWindow::create(const gx_system::CmdlineOptions& options, const Glib::ustring& save_name_default) {
    Glib::RefPtr<gx_gui::GxBuilder> bld = gx_gui::GxBuilder::create_from_file(options.get_builder_filepath("pluginpreset_inputwindow.glade"));
    InputWindow *w;
    bld->get_toplevel_derived(
	"PluginPresetInputWindow", w,
	sigc::bind(sigc::ptr_fun(InputWindow::create_from_builder), bld, save_name_default));
    return w;
}

bool InputWindow::on_key_press_event(GdkEventKey *event) {
    if (event->keyval == GDK_KEY_Escape && (event->state & Gtk::AccelGroup::get_default_mod_mask()) == 0) {
	hide();
	return true;
    }
    return Gtk::Window::on_key_press_event(event);
}

void InputWindow::on_ok(Gtk::Entry *e) {
    name = e->get_text();
    hide();
}

InputWindow::InputWindow(BaseObjectType* cobject, Glib::RefPtr<gx_gui::GxBuilder> bld,
			 const Glib::ustring& save_name_default)
    : Gtk::Window(cobject), name() {
    Gtk::Button *b;
    bld->find_widget("cancelbutton", b);
    b->signal_clicked().connect(
	sigc::mem_fun(*this, &InputWindow::hide));
    bld->find_widget("okbutton", b);
    Gtk::Entry *e;
    bld->find_widget("entry", e);
    e->set_text(save_name_default);
    e->select_region(0, -1);
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
    TextListStore(): Gtk::ListStore(), col() {
	set_column_types(col);
    }
public:
    static Glib::RefPtr<TextListStore> create() { return Glib::RefPtr<TextListStore>(new TextListStore); }
};

class PluginPresetListWindow: public Gtk::Window {
private:
    Glib::RefPtr<TextListStore> textliststore;
    PluginPresetPopup& presetlist;
    //
    Gtk::TreeView *treeview;
    Gtk::Button *removebutton;
    using Gtk::Window::on_remove;
    void on_remove();
    void on_selection_changed();
    virtual bool on_key_press_event(GdkEventKey *event);
    static PluginPresetListWindow* create_from_builder(
	BaseObjectType* cobject, Glib::RefPtr<gx_gui::GxBuilder> bld, PluginPresetPopup& p);
    PluginPresetListWindow(BaseObjectType* cobject, Glib::RefPtr<gx_gui::GxBuilder> bld, PluginPresetPopup& p);
public:
    ~PluginPresetListWindow();
    static PluginPresetListWindow *create(const gx_system::CmdlineOptions& options, PluginPresetPopup& p);
    void run();
};

PluginPresetListWindow *PluginPresetListWindow::create_from_builder(
    BaseObjectType* cobject, Glib::RefPtr<gx_gui::GxBuilder> bld, PluginPresetPopup& p) {
    return new PluginPresetListWindow(cobject, bld, p);
}

PluginPresetListWindow::~PluginPresetListWindow() {
}

PluginPresetListWindow *PluginPresetListWindow::create(
    const gx_system::CmdlineOptions& options, PluginPresetPopup& p) {
    Glib::RefPtr<gx_gui::GxBuilder> bld = gx_gui::GxBuilder::create_from_file(
	options.get_builder_filepath("pluginpreset_listwindow.glade"));
    PluginPresetListWindow *w;
    bld->get_toplevel_derived(
	"PluginPresetListWindow", w,
	sigc::bind(sigc::ptr_fun(PluginPresetListWindow::create_from_builder), bld, sigc::ref(p)));
    return w;
}

bool PluginPresetListWindow::on_key_press_event(GdkEventKey *event) {
    if (event->keyval == GDK_KEY_Escape && (event->state & Gtk::AccelGroup::get_default_mod_mask()) == 0) {
	hide();
	return true;
    }
    return Gtk::Window::on_key_press_event(event);
}

void PluginPresetListWindow::on_remove() {
    Gtk::TreeIter it = treeview->get_selection()->get_selected();
    if (it) {
	presetlist.get_machine().plugin_preset_list_remove(
	    presetlist.get_pdef(), it->get_value(textliststore->col.name));
	textliststore->erase(it);
    }
}

PluginPresetListWindow::PluginPresetListWindow(
    BaseObjectType* cobject, Glib::RefPtr<gx_gui::GxBuilder> bld, PluginPresetPopup& p)
    : Gtk::Window(cobject),
      textliststore(TextListStore::create()),
      presetlist(p) {
    Gtk::Button *b;
    bld->find_widget("closebutton", b);
    b->signal_clicked().connect(
	sigc::mem_fun(*this, &PluginPresetListWindow::hide));
    bld->find_widget("removebutton", removebutton);
    removebutton->signal_clicked().connect(
	sigc::mem_fun0(*this, &PluginPresetListWindow::on_remove));
    bld->find_widget("treeview", treeview);
    for (gx_preset::UnitPresetList::const_iterator i = presetlist.begin(); i != presetlist.end(); ++i) {
	if (i->name.empty()) {
	    break;
	}
	textliststore->append()->set_value(textliststore->col.name, i->name);
    }
    treeview->set_model(textliststore);
    removebutton->set_sensitive(false);
    Glib::RefPtr<Gtk::TreeSelection> sel = treeview->get_selection();
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
** PluginPresetPopup
*/

void PluginPresetPopup::set_plugin_preset(bool factory, const Glib::ustring& name) {
    if(strcmp(pdef->id,"seq")==0) {
        machine.plugin_preset_list_sync_set(pdef, factory, name);
    } else {
        machine.plugin_preset_list_set(pdef, factory, name);
    }
}

void PluginPresetPopup::set_plugin_std_preset() {
    machine.reset_unit(pdef);
}

void PluginPresetPopup::save_plugin_preset() {
    InputWindow *w = InputWindow::create(machine.get_options(), save_name_default);
    w->run();
    if (!w->get_name().empty()) {
        // save loop file to plugin preset name
	    if(strcmp(pdef->id,"dubber")==0) {
            Glib::ustring name = "";
            machine.set_parameter_value("dubber.filename", name);
            machine.set_parameter_value("dubber.savefile", true);
            machine.set_parameter_value("dubber.filename", w->get_name());
        }
        machine.plugin_preset_list_save(pdef, w->get_name());
        if(strcmp(pdef->id,"seq")==0) {
            Glib::ustring id = "seq." + w->get_name();
            if (!machine.parameter_hasId(id)) {
                machine.insert_param("seq", w->get_name());
            }
        }
    }
    delete w;
}

void PluginPresetPopup::remove_plugin_preset() {
    PluginPresetListWindow *w = PluginPresetListWindow::create(machine.get_options(), *this);
    w->run();
    delete w;
}

bool PluginPresetPopup::add_plugin_preset_list(bool *found) {
    *found = false;
    bool found_presets = false;
    bool factory = false;
    for (gx_preset::UnitPresetList::iterator i = presetnames.begin(); i != presetnames.end(); ++i) {
	if (i->name.empty()) {
	    factory = true;
	    if (found_presets) {
		append(*manage(new Gtk::SeparatorMenuItem()));
		*found = true;
		found_presets = false;
	    }
	    continue;
	} else {
	    found_presets = true;
	}
	Gtk::CheckMenuItem *c = new Gtk::CheckMenuItem(i->name);
	if (i->is_set) {
	    c->set_active(true);
	}
	c->signal_activate().connect(
	    sigc::bind(sigc::mem_fun(this, &PluginPresetPopup::set_plugin_preset), factory, i->name));
	append(*manage(c));
    }
    return found_presets;
}

static bool delete_plugin_preset_popup(PluginPresetPopup *p) {
    delete p;
    return false;
}

void PluginPresetPopup::on_selection_done() {
    Glib::signal_idle().connect(
	sigc::bind(
	    sigc::ptr_fun(delete_plugin_preset_popup),
	    this));
}

PluginPresetPopup::PluginPresetPopup(const PluginDef *pdef_, gx_engine::GxMachineBase& machine_,
				     const Glib::ustring& save_name_default_)
  : Gtk::Menu(),
    pdef(pdef_),
    machine(machine_),
    save_name_default(save_name_default_),
    presetnames() {
    machine.plugin_preset_list_load(pdef, presetnames);
    bool found_presets;
    if (!add_plugin_preset_list(&found_presets)) {
	Gtk::CheckMenuItem *c = new Gtk::CheckMenuItem(_("standard"));
	if (machine.parameter_unit_has_std_values(pdef)) {
	    c->set_active(true);
	}
	c->signal_activate().connect(
	    sigc::mem_fun(this, &PluginPresetPopup::set_plugin_std_preset));
	append(*manage(c));
    }
    append(*manage(new Gtk::SeparatorMenuItem()));
    Gtk::MenuItem *mi = new Gtk::MenuItem(_("save..."));
    append(*manage(mi));
    mi->signal_activate().connect(
	sigc::mem_fun(this, &PluginPresetPopup::save_plugin_preset));
    if (found_presets) {
	mi = new Gtk::MenuItem(_("remove..."));
	append(*manage(mi));
	mi->signal_activate().connect(
	    sigc::mem_fun(this, &PluginPresetPopup::remove_plugin_preset));
    }
    show_all();
    popup_at_pointer(nullptr);
}


/****************************************************************
 ** class RackBox
 */

#ifdef USE_SZG
Glib::RefPtr<Gtk::SizeGroup> RackBox::szg;
#endif

void RackBox::set_paintbox_unit_shrink(Gxw::PaintBox& pb, PluginType tp) {
    pb.set_name("rackbox");
    pb.property_paint_func().set_value("gx_rack_unit_shrink_expose");
    pb.set_border_width(4);
}

void RackBox::set_paintbox_unit(Gxw::PaintBox& pb, const PluginUI& plugin) {
    pb.set_name("rackbox");
    pb.property_paint_func().set_value("gx_rack_unit_expose");
    pb.set_border_width(4);
    // FIXME set special background for LV2 plugins
    // if (plugin.plugin->get_pdef()->flags & gx_engine::PGNI_IS_LV2)
    //   fprintf(stderr,"LV2 Plugin Load for %s %i\n",plugin.plugin->get_pdef()->name, plugin.plugin->get_pdef()->flags & gx_engine::PGNI_IS_LV2);
    // else if (plugin.plugin->get_pdef()->flags & gx_engine::PGNI_IS_LADSPA)
    //   fprintf(stderr,"LADSPA Plugin Load for %s %i\n",plugin.plugin->get_pdef()->name, plugin.plugin->get_pdef()->flags & gx_engine::PGNI_IS_LV2);

}

void RackBox::set_paintbox(Gxw::PaintBox& pb, PluginType tp) {
    pb.set_name("rackbox");
   // pb.property_paint_func().set_value("rectangle_skin_color_expose");
    pb.set_border_width(4);
}

Gtk::Widget *RackBox::make_label(const PluginUI& plugin, gx_system::CmdlineOptions& options, bool useshort) {
    const char *effect_name = useshort ? plugin.get_shortname() : plugin.get_name();
    Gtk::Label *effect_label = new Gtk::Label(effect_name);
    effect_label->set_alignment(0.0, 0.5);
    effect_label->set_name("effect_title");
    if (plugin.get_type() == PLUGIN_TYPE_STEREO) {
        effect_label->set_markup("◗◖ " + effect_label->get_label()); //♾⚮⦅◗◖⦆⚭ ⧓ Ꝏꝏ ⦅◉⦆● ▷◁ ▶◀
    }
    return effect_label;
}

Gtk::Widget *RackBox::make_bar(int left, int right, bool sens) {
    Gtk::Alignment *al = new Gtk::Alignment(0, 0, 1.0, 1.0);
    //al->set_padding(4, 4, left, right);
    Gtk::Button *button = new Gtk::Button();
    button->set_size_request(32,-1);
    //button->set_name("effect_reset");
    button->set_tooltip_text(_("Drag'n' Drop Handle"));
    button->set_relief(Gtk::RELIEF_NONE);
    button->set_sensitive(sens);
    al->add(*manage(button));
    return al;
}

bool RackBox::on_my_leave_out(GdkEventCrossing *focus) {
    Glib::RefPtr<Gdk::Window> window = this->get_window();
    window->set_cursor(); 
    return true;
}

bool RackBox::on_my_enter_in(GdkEventCrossing *focus) {
    Glib::RefPtr<Gdk::Window> window = this->get_window();
    Glib::RefPtr<Gdk::Display> disp = this->get_display();
    Glib::RefPtr<Gdk::Cursor> cursor(Gdk::Cursor::create(disp, Gdk::HAND1));
    window->set_cursor(cursor);
    return true;
}

bool RackBox::on_my_button_press(GdkEventButton* ev) {
    if (ev->type == GDK_2BUTTON_PRESS && ev->button == 1) {
        plugin.display(false, true);
    }
    return true;
}


Gtk::Widget *RackBox::wrap_bar(int left, int right, bool sens) {
    Gtk::EventBox *ev = new Gtk::EventBox;
    ev->set_visible_window(false);
    ev->set_above_child(true);
    ev->add(*manage(make_bar(left, right, sens)));
    ev->signal_leave_notify_event().connect(sigc::mem_fun(*this, &RackBox::on_my_leave_out));
    ev->signal_enter_notify_event().connect(sigc::mem_fun(*this, &RackBox::on_my_enter_in));
    ev->signal_button_press_event().connect(sigc::mem_fun(*this, &RackBox::on_my_button_press));
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
    RackBox::set_paintbox_unit_shrink(*pb, plugin.get_type());
    pb->set_name("drag_widget");
    if (strcmp(plugin.get_id(), "ampstack") == 0) { // FIXME
	pb->property_paint_func().set_value("gx_rack_amp_expose");
    }
    //Gxw::Switch *swtch = new Gxw::Switch("switchit");
    //swtch->set_active(plugin.plugin->get_on_off());
#ifdef USE_SZG
    //RackBox::szg->add_widget(*swtch);
#else
    //swtch->set_size_request(35, -1);
#endif
    Gtk::Widget *effect_label = RackBox::make_label(plugin, options);
    Gtk::Alignment *al = new Gtk::Alignment(0.0, 0.0, 0.0, 0.0);
    al->set_padding(0,0,4,20);
    al->add(*manage(RackBox::make_bar(4, 4, true))); // FIXME: fix style and remove sens parameter
    pb->pack_start(*manage(al), Gtk::PACK_SHRINK);
    //pb->pack_start(*manage(swtch), Gtk::PACK_SHRINK);
    pb->pack_start(*manage(effect_label), Gtk::PACK_SHRINK);
    al = new Gtk::Alignment(0.0, 0.0, 0.0, 0.0);
    al->set_size_request(70,30);
    pb->pack_start(*manage(al), Gtk::PACK_SHRINK);
    pb->show_all();
    return pb;
}

void RackBox::display(bool v, bool animate) {
    assert(box_visible != v);
    box_visible = v;
    plugin.set_active(v);
    if (v) {
	if (animate) {
	    animate_insert();
	} else {
	    show();
	}
	get_parent()->increment();
	plugin.hidden_by_move = false;
	plugin.toolitem->hide();
    } else {
	if (animate) {
	    animate_remove();
	} else {
	    hide();
	}
	get_parent()->decrement();
	plugin.hidden_by_move = true;
    }
}

RackBox::RackBox(PluginUI& plugin_, MainWindow& tl, Gtk::Widget* bare)
    : Gtk::VBox(), plugin(plugin_), main(tl), config_mode(false), anim_tag(),
      compress(true), delete_button(true), mbox(Gtk::ORIENTATION_HORIZONTAL), minibox(0),
      fbox(0), target(), anim_height(0), anim_step(), drag_icon(), target_height(0),
      box(Gtk::ORIENTATION_HORIZONTAL, 2), box_visible(true), on_off_switch("switchit"),
      toggle_on_off(tl.get_machine(), &on_off_switch, plugin.plugin->id_on_off()) {
    if (strcmp(plugin.get_id(), "ampstack") != 0) { // FIXME
	gx_gui::connect_midi_controller(&on_off_switch, plugin.plugin->id_on_off().c_str(), main.get_machine());
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
    set_paintbox_unit_shrink(mbox, plugin.get_type());
    init_dnd();
    minibox = new MiniRackBox(*this, tl.get_options());
    mbox.pack_start(*manage(minibox));
    pack_start(mbox, Gtk::PACK_SHRINK);
    if (bare) {
	add(*manage(bare));
	fbox = bare;
	mbox.property_paint_func().set_value("gx_rack_amp_expose");
    } else {
	Gxw::PaintBox *pb = new Gxw::PaintBox(Gtk::ORIENTATION_HORIZONTAL);
	pb->show();
	set_paintbox_unit(*pb, plugin);
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
	set_visibility(true);
	set_size_request(-1,-1);
	get_parent()->resize_finished();
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
	gint min_height, natural_height;
	get_preferred_height(min_height, natural_height);
	anim_height = min_height;
	set_size_request(-1, anim_height);
	set_visibility(false);
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
	set_visibility(true);
	set_size_request(-1,-1);
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
	gint min_height, natural_height;
	get_preferred_height(min_height, natural_height);
	target_height = min_height;
	set_size_request(-1,0);
	set_visibility(false);
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
    if (plugin.plugin->get_box_visible()) {
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

void RackBox::set_visibility(bool v) {
    if (config_mode || get_plug_visible()) {
	minibox->set_config_mode(false);
	mbox.set_visible(v);
	minibox->set_config_mode(config_mode);
    } else {
	fbox->set_visible(v);
    }
}

void RackBox::swtch(bool mini) {
    plugin.plugin->set_plug_visible(mini);
    if (!config_mode) {
	if (mini) {
	    vis_switch(*fbox, mbox);
	} else {
	    vis_switch(mbox, *fbox);
	}
    }
}

void RackBox::set_config_mode(bool mode) {
    config_mode = mode;
    if (!can_compress() || !get_plug_visible()) {
	if (mode) {
	    vis_switch(*fbox, mbox);
        if (strcmp(plugin.get_id(), "ampstack") == 0) { // FIXME
	        return;
        }
	} else {
	    vis_switch(mbox, *fbox);
	}
    }
    minibox->set_config_mode(mode);
    enable_drag(mode);
}

void RackBox::setOrder(int pos, int post_pre) {
    plugin.plugin->set_position(pos);
    if (plugin.get_type() == PLUGIN_TYPE_MONO) {
	plugin.plugin->set_effect_post_pre(post_pre);
    }
}

void RackBox::do_expand() {
    swtch(false);
    Glib::signal_idle().connect_once(
	sigc::bind(
	    sigc::mem_fun(get_parent(), &RackContainer::ensure_visible),
	    sigc::ref(*this)));
}

Gtk::Button *RackBox::make_expand_button(bool expand) {
    const gchar *t;
    Gtk::Button *b = new Gtk::Button();
    //b->set_relief(Gtk::RELIEF_NONE);
    if (expand) {
	t = "rack_expand";
	b->set_tooltip_text(_("expand effect unit"));
    } else {
	t = "rack_shrink";
	b->set_tooltip_text(_("shrink effect unit"));
    }
    Gtk::Image *l = new Gtk::Image(t, Gtk::ICON_SIZE_BUTTON);
    b->set_focus_on_click(false);
    b->add(*manage(l));
    b->set_name("effect_on_off");
    if (expand) {
	b->signal_clicked().connect(
	    sigc::mem_fun(*this, &RackBox::do_expand));
    } else {
	b->signal_clicked().connect(
	    sigc::bind(sigc::mem_fun(*this, &RackBox::swtch), true));
    }
    return b;
}

Gtk::Button *RackBox::make_preset_button() {
    Gtk::Button *p = new Gtk::Button();
    //p->set_relief(Gtk::RELIEF_NONE);
    Gtk::Image *l = new Gtk::Image("rack_preset", Gtk::ICON_SIZE_BUTTON);
    p->add(*manage(l));
    p->set_can_default(false);
    p->set_can_focus(false);
	p->set_tooltip_text(_("manage effect unit presets"));
	p->set_name("effect_on_off");
    p->signal_clicked().connect(
	sigc::mem_fun(plugin, &PluginUI::on_plugin_preset_popup));
    return p;
}

void RackBox::pack(Gtk::Widget *main, Gtk::Widget *mini, const Glib::RefPtr<Gtk::SizeGroup>& szg) {
    if (!main) {
	return;
    }
    box.pack_start(*manage(main));
    minibox->pack(mini);
    szg->add_widget(*fbox);
    szg->add_widget(mbox);
}

Gtk::HBox *RackBox::make_full_box(gx_system::CmdlineOptions& options) {
    Gtk::HBox *bx = new Gtk::HBox();
    Gtk::Widget *effect_label = make_label(plugin, options, false);
    
    // overall hbox: drag-button - center vbox - drag button
    Gtk::HBox *main   = new Gtk::HBox();
    // center vbox containing title bar and widgets
    Gtk::VBox *center = new Gtk::VBox();
    // title vbox on top
    Gtk::HBox *top    = new Gtk::HBox();
    
    // spacing for bottom shadow
    Gtk::Alignment *al = new Gtk::Alignment();
    al->set_padding(0, 4, 0, 0);
    al->add(*manage(main));
    
    main->set_spacing(0);
    
    center->set_name("rack_unit_center");
    center->set_border_width(0);
    center->set_spacing(4);
    center->pack_start(*manage(top), Gtk::PACK_SHRINK);
    center->pack_start(box, Gtk::PACK_EXPAND_WIDGET);
    
    top->set_spacing(4);
    top->set_name("rack_unit_title_bar");
    
    top->pack_start(on_off_switch, Gtk::PACK_SHRINK);
    on_off_switch.set_name("effect_on_off");
    top->pack_start(*manage(effect_label), Gtk::PACK_SHRINK);
    top->pack_end(*manage(make_expand_button(false)), Gtk::PACK_SHRINK);
    if (!(plugin.plugin->get_pdef()->flags & PGN_NO_PRESETS))
        top->pack_end(*manage(make_preset_button()), Gtk::PACK_SHRINK);
    
    main->pack_start(*manage(wrap_bar()), Gtk::PACK_SHRINK);
    main->pack_start(*manage(center), Gtk::PACK_EXPAND_WIDGET);
    main->pack_end(*manage(wrap_bar()), Gtk::PACK_SHRINK);
    
    main->set_name(plugin.get_id());
    bx->pack_start(*manage(al), Gtk::PACK_EXPAND_WIDGET);
    //al->show_all();
    bx->show_all();
    return bx;
}

Gtk::VBox *RackBox::switcher_vbox(gx_system::CmdlineOptions& options) {
    Gtk::VBox *vbox = new Gtk::VBox();
    
    Gtk::HBox *hbox = new Gtk::HBox();
    vbox->pack_start(*manage(hbox));
    Gtk::HBox *hbox2 = new Gtk::HBox();
    hbox->pack_start(*manage(hbox2), Gtk::PACK_SHRINK);
    Gtk::VBox *vbox2 = new Gtk::VBox();
    hbox2->pack_start(*manage(vbox2));
    hbox2->pack_start(*manage(wrap_bar(4,4)), Gtk::PACK_SHRINK);
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
    main.get_machine().signal_rack_unit_order_changed().connect(
	sigc::mem_fun(this, &RackContainer::unit_order_changed));
    signal_remove().connect(sigc::mem_fun(*this, &RackContainer::on_my_remove));
    set_size_request(-1, min_containersize);
    show_all();
}

void RackContainer::unit_order_changed(bool stereo) {
    if (stereo == (tp == PLUGIN_TYPE_STEREO)) {
	check_order();
    }
}

bool RackContainer::drag_highlight_draw(const Cairo::RefPtr<Cairo::Context> &cr, int y0) {
    if (!get_is_drawable()) {
	return false;
    }
    int x, y, width, height;
    if (!get_has_window()) {
        Gtk::Allocation a = get_allocation();
        x      = 0;
        y      = 0;
        width  = a.get_width();
        height = a.get_height();
    } else {
        get_window()->get_geometry(x, y, width, height);
        x = 0;
        y = 0;
    }
    Glib::RefPtr<Gdk::Pixbuf> pb_ = render_icon_pixbuf(Gtk::StockID("insert"), Gtk::IconSize(-1));
    if (pb_) {
        Gdk::Cairo::set_source_pixbuf(cr, pb_, x, y);
        cr->get_source()->set_extend(Cairo::EXTEND_REPEAT);
        if (y0 < 0) {
            cr->set_line_width(4.0);
            cr->rectangle(x, max(0, y), width, height);
            cr->stroke();
        } else {
            cr->rectangle(x, max(y, y0 - 3), width, 2);
            cr->fill();
        }
    }
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
    if (ch->get_visible()) {
        decrement();
    }
    renumber();
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
    const std::vector<std::string>& tg = context->list_targets();
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
    highlight_connection = signal_draw().connect(sigc::bind(sigc::mem_fun(*this, &RackContainer::drag_highlight_draw), ind), true);
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
    Glib::RefPtr<Gtk::Adjustment> a = p->get_vadjustment();
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
	off = main.stop_at_mono_top(off, step_size);
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
    Glib::RefPtr<Gtk::Adjustment> a = p->get_vadjustment();
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
    if (!i->second->hidden_by_move) {
	RackBox *r = i->second->rackbox;
	if (r) {
	    r->show();
	}
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

void RackContainer::reorder(const std::string& name, unsigned int pos) {
    std::vector<RackBox*> l = get_children();
    main.get_machine().insert_rack_unit(name, ((pos >= l.size()) ? "" : l[pos]->get_id()), tp);
    check_order();
}

void RackContainer::on_add(Widget *ch) {
    add(*dynamic_cast<RackBox*>(ch));
}

void RackContainer::add(RackBox& r, int pos) {
    pack_start(r, Gtk::PACK_SHRINK);
    increment();
    if (config_mode) {
	r.set_config_mode(true);
    }
    reorder_child(r, pos);
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

void RackContainer::check_order() {
    const std::vector<std::string>& ol = main.get_machine().get_rack_unit_order(tp);
    bool in_order = true;
    std::set<std::string> unit_set(ol.begin(), ol.end());
    rackbox_list l = get_children();
    std::vector<std::string>::const_iterator oi = ol.begin();
    for (rackbox_list::iterator c = l.begin(); c != l.end(); ++c) {
	if (!(*c)->get_box_visible()) {
	    continue;
	}
	if (unit_set.find((*c)->get_id()) == unit_set.end()) {
	    main.get_plugin((*c)->get_id())->hide(false);
	    continue;
	}
	if (!in_order) {
	    continue;
	}
	if (oi == ol.end()) {
	    in_order = false;
	    continue;
	}
	if (*oi != (*c)->get_id()) {
	    in_order = false;
	}
	++oi;
    }
    if (oi != ol.end()) {
	in_order = false;
    }
    if (in_order) {
	return;
    }
    int n = 0;
    for (std::vector<std::string>::const_iterator oi = ol.begin(); oi != ol.end(); ++oi) {
	PluginUI *p = main.get_plugin(*oi);
	if (!p->rackbox) {
	    p->show(false);
	} else {
	    if (!p->rackbox->get_box_visible()) {
		p->rackbox->display(true, false);
		if (p->hidden) {
		    p->rackbox->hide();
		}
	    }
	}
	reorder_child(*p->rackbox, n++);
    }
    renumber();
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
