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

#include <gtkmm.h>
#include <gxwmm.h>
using namespace std;
#include <engine.h>
#include <gx_ui.h>
#include <gx_ui_builder.h>

/****************************************************************
 ** class DragIcon
 */

enum PluginType {
    PLUGIN_TYPE_MONO,
    PLUGIN_TYPE_STEREO,
};

class DragIcon {
private:
    Gtk::Window *window;
    Glib::RefPtr<Gdk::Pixbuf> drag_icon_pixbuf;
private:
    bool icon_expose_event(GdkEventExpose *ev);
    void create_drag_icon_pixbuf(const Glib::ustring& text, PluginType tp, Glib::RefPtr<Gdk::Colormap> rgba, gx_system::CmdlineOptions& options);
    bool window_expose_event(GdkEventExpose *event, Gtk::OffscreenWindow& w);
public:
    DragIcon(const Glib::ustring& text, PluginType tp, Glib::RefPtr<Gdk::DragContext> context, gx_system::CmdlineOptions& options, int xoff=0);
    ~DragIcon();
    void destroy();
};

/****************************************************************
 ** class RackBox, class MiniRackBox
 */

class MainWindow;
class MiniRackBox;

class RackBox: public Gtk::VBox {
private:
    static Glib::RefPtr<Gtk::SizeGroup> szg;
    std::string effect_id;
    PluginType tp;
    MainWindow& main;
    bool vis;
    bool config_mode;
    sigc::connection anim_tag;
    bool compress;
    bool delete_button;
    Gxw::PaintBox mbox;
    Glib::RefPtr<Gtk::ToggleAction> on_off_action;
    MiniRackBox* minibox;
    Gtk::Widget *fbox;
    std::string target;
    int anim_height;
    DragIcon *drag_icon;
    int target_height;
    int preset_index;
    std::vector<Glib::ustring> presets;
    Gxw::PaintBox box;
private:
    static void set_paintbox(Gxw::PaintBox& pb, PluginType tp);
    static Gtk::Widget *make_label(const Glib::ustring& name, PluginType tp, gx_system::CmdlineOptions& options);
    static Gtk::Widget *make_bar(int left=4, int right=4, bool sens=false);
    void init_dnd();
    void enable_drag(bool v);
    bool animate_vanish();
    void on_my_drag_begin(const Glib::RefPtr<Gdk::DragContext>& context);
    bool animate_create();
    void on_my_drag_end(const Glib::RefPtr<Gdk::DragContext>& context);
    void on_my_drag_data_get(const Glib::RefPtr<Gdk::DragContext>& context, Gtk::SelectionData& selection, int info, int timestamp);
    void on_my_drag_data_delete(const Glib::RefPtr<Gdk::DragContext>& context);
    void vis_switch(Gtk::Widget& a, Gtk::Widget& b);
    void on_expand(bool mini);
    Gtk::Button *make_expand_button(bool expand);
    void on_preset_popup_destroy(Gtk::Menu *w);
    void preset_popup();
    Gtk::Button *make_preset_button();
    Gtk::HBox *make_full_box(gx_system::CmdlineOptions& options);
    Gtk::VBox *switcher_vbox(gx_system::CmdlineOptions& options);
    bool has_delete() const { return delete_button; }
    void on_kill();
public:
    RackBox(const Glib::ustring& effect_id, PluginType tp, MainWindow& main, Gtk::Widget* bare=0);
    static Gtk::Widget *create_drag_widget(const Glib::ustring& name, PluginType tp, gx_system::CmdlineOptions& options);
    bool can_compress() { return compress; }
    friend class MiniRackBox;
    const std::string& get_id() const { return effect_id; }
    void set_config_mode(bool mode);
    void swtch(bool mini);
    void pack(Gtk::Widget& child);
    void animate_insert();
    static Gtk::Widget *create_icon_widget(const Glib::ustring& name, PluginType tp, gx_system::CmdlineOptions& options);
};

class MiniRackBox: public Gtk::HBox {
private:
    static Glib::RefPtr<Gtk::SizeGroup> szg_label;
    Gtk::EventBox evbox;
    Gtk::HBox mconbox;
    Gtk::Button *mb_expand_button;
    Gtk::Widget *mb_delete_button;
    Gtk::Button *preset_button;
private:
    Gtk::Widget *make_delete_button(RackBox& rb);
public:
    MiniRackBox(RackBox& rb, const Glib::RefPtr<Gtk::Action>& action, gx_system::CmdlineOptions& options);
    void set_config_mode(bool mode);
};


/****************************************************************
 ** class RackContainer
 */

class RackContainer: public Gtk::VBox {
private:
    PluginType tp;
    MainWindow& main;
    bool config_mode;
    int in_drag;
    int child_count;
    int switch_level;
    std::vector<std::string> targets;
    sigc::connection hightlight_connection;
private:
    bool drag_highlight_expose(GdkEventExpose *event, int y0);
    void find_index(int x, int y, int* len, int *ypos);
    void on_my_remove(Gtk::Widget*);
    bool check_targets(const std::vector<std::string>& targets);
    virtual bool on_drag_motion(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, guint timestamp);
    virtual void on_drag_leave(const Glib::RefPtr<Gdk::DragContext>& context, guint timestamp);
    virtual void on_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, const Gtk::SelectionData& data, guint info, guint timestamp);
    virtual void on_add(Widget* ch);
    void reorder(const std::string& name, int pos);
public:
    RackContainer(PluginType tp, MainWindow& main);
    Glib::ListHandle<RackBox*> get_children() {
	Glib::ListHandle<Widget*> l = Gtk::VBox::get_children();
	void *p = &l;
	return *reinterpret_cast<Glib::ListHandle<RackBox*>*>(p);
    }
    Glib::ListHandle<const RackBox*> get_children() const {
	Glib::ListHandle<const Widget*> l = Gtk::VBox::get_children();
	void *p = &l;
	return *reinterpret_cast<Glib::ListHandle<const RackBox*>*>(p);
    }
    bool check_if_animate(const RackBox& rackbox);
    void show_entries();
    void hide_entries();
    void compress_all();
    void expand_all();
    void set_config_mode(bool mode);
    bool empty() const;
    void add(RackBox& r, int pos=-1);
};


/****************************************************************
 ** class PluginUI
 */

class PluginUI {
public:
    PluginType tp;
    std::string name;
    Glib::ustring fname;
    Glib::ustring tooltip;
    int index;
    Glib::RefPtr<Gdk::Pixbuf> icon;
    Gtk::ToolItemGroup *group;
    Gtk::ToolItem *toolitem;
    PluginUI(PluginType tp_, const std::string& name_, const Glib::ustring& fname_="", const Glib::ustring& tooltip_="")
	: tp(tp_), name(name_), fname(fname_), tooltip(tooltip_), index(-1), icon(), group(), toolitem() {}
};

/****************************************************************
 ** class MainWindow
 */

class Freezer {
private:
    Gtk::Window *window;
    sigc::connection tag;
    int size_x;
    int size_y;
public:
    Freezer();
    ~Freezer();
    void freeze(Gtk::Window *w, int width, int height);
    void freeze_until_width_update(Gtk::Window *w, int width) { freeze(w, width, -1); }
    void freeze_and_size_request(Gtk::Window *w, int width, int height);
    bool thaw_timeout();
    void thaw();
    bool check_thaw(int width, int height);
};

class MainWindow: public sigc::trackable {
private:
    int window_height;
    Freezer freezer;
    Glib::RefPtr<gx_gui::GxBuilder> bld;
    int oldpos;
    int scrl_size_x;
    int scrl_size_y;
    RackContainer monorackcontainer;
    RackContainer stereorackcontainer;
    int pre_act;
    bool is_visible;
    DragIcon *drag_icon;
    std::map<std::string, PluginUI*> plugin_dict;
    Glib::RefPtr<Gtk::ActionGroup> actiongroup;
    Glib::RefPtr<Gtk::UIManager> uimanager;
    gx_ui::GxUI ui;
    gx_system::CmdlineOptions& options;
    gx_engine::ParamMap&  pmap;

    // Widget pointers
    Gxw::PaintBox *tunerbox;
    Gtk::ScrolledWindow *vrack_scrolledbox;
    Gtk::HBox *stereorackcontainerH;
    Gtk::HBox *stereorackcontainerV;
    Gxw::PaintBox *rackcontainer;
    Gtk::ScrolledWindow *stereorackbox;
    Gtk::VBox *monocontainer;
    Gxw::PaintBox *monoampcontainer;
    Gtk::VPaned *main_vpaned;
    Gtk::HBox *amp_toplevel_box;
    Gtk::VBox *monobox;
    Gtk::VBox *upper_rackbox;
    Gtk::ScrolledWindow *preset_scrolledbox;
    Gxw::PaintBox *effects_frame_paintbox;
    Gtk::Image *status_image;
    Gtk::Image *jackd_image;
    Gtk::Image *logstate_image;
    Gtk::Window *window;
    Gtk::HBox *menubox;
    Gtk::ToggleButton *show_rack_button;
    Gtk::ToggleButton *liveplay_button;
    Gtk::ToggleButton *tuner_button;
    Gtk::ToggleButton *effects_button;
    Gtk::ToggleButton *presets_button;
    Gtk::Button *compress_button;
    Gtk::Button *expand_button;
    Gtk::ToolPalette *effects_toolpalette;
    Gxw::PaintBox *amp_background;
public:
    // ToggleActions
    Glib::RefPtr<Gtk::ToggleAction> show_plugin_bar_action;
    Glib::RefPtr<Gtk::ToggleAction> presets_action;
    Glib::RefPtr<Gtk::ToggleAction> show_rack_action;
    Glib::RefPtr<Gtk::ToggleAction> fullscreen_action;
    Glib::RefPtr<Gtk::ToggleAction> tuner_action;
    Glib::RefPtr<Gtk::Action> compress_action;
    Glib::RefPtr<Gtk::Action> expand_action;
    Glib::RefPtr<Gtk::ToggleAction> show_values_action;
    Glib::RefPtr<Gtk::ToggleAction> live_play_action;
    Gtk::RadioButtonGroup dir_group;
    Glib::RefPtr<Gtk::RadioAction> rackv_action;
    Glib::RefPtr<Gtk::RadioAction> rackh_action;
private:
    void load_widget_pointers();
    void maybe_shrink_horizontally();
    void on_show_tuner();
    bool is_variable_size();
    void maybe_change_resizable(void);
    void on_show_rack();
    void on_preset_action();
    void on_fullscreen();
    void on_compress_all();
    void on_expand_all();
    void on_show_plugin_bar();
    void move_widget(Gtk::Widget& w, Gtk::Box& b1, Gtk::Box& b2);
    int get_dir() const;
    static void change_expand(Gtk::Widget& w, bool value);
    void on_dir_changed(Glib::RefPtr<Gtk::RadioAction> act);
    void on_configure_event(GdkEventConfigure *ev);
    void clear_box(Gtk::Container& box);
    void add_rackbox_internal(const std::string& name, PluginType tp, Gtk::Widget *widget, bool mini=false, int pos=-1, bool animate=false, Gtk::Widget *bare=0);
    void on_show_values();
    Glib::RefPtr<Gtk::UIManager> create_menu(Glib::RefPtr<Gtk::ActionGroup>& actiongroup);
    void add_toolitem(PluginUI& pl, Gtk::ToolItemGroup *gw);
    bool on_visibility_notify(GdkEventVisibility *ev);
    void on_live_play();
    void on_ti_drag_begin(const Glib::RefPtr<Gdk::DragContext>& context, const std::string& effect_id, PluginType tp);
    void on_ti_drag_end(const Glib::RefPtr<Gdk::DragContext>& context);
    void on_ti_drag_data_get(const Glib::RefPtr<Gdk::DragContext>& context, Gtk::SelectionData& selection, int info, int timestamp, const std::string& effect_id);
    void hide_effect(const std::string& name);
    void on_ti_drag_data_delete(const Glib::RefPtr<Gdk::DragContext>& context, const std::string& effect_id);
    bool on_ti_button_press(GdkEventButton *ev, const std::string& effect_id);
    void on_tp_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, const Gtk::SelectionData& data, int info, int timestamp);
public:
    MainWindow(gx_system::CmdlineOptions& options, gx_engine::ParamMap& pmap);
    ~MainWindow();
    bool check_if_animate(RackContainer& rb) const;
    RackContainer& get_monorackcontainer() { return monorackcontainer; }
    void add_rackbox(const PluginUI& pl, bool mini=false, int pos=-1, bool animate=false);
    bool check_if_rack_container_size_animate(const RackContainer& rackcontainer) const;
    void add_icon(const std::string& name);
    PluginUI *get_plugin(const std::string& name) { return plugin_dict[name]; }
    void run() { Gtk::Main::run(*window); }
    gx_system::CmdlineOptions& get_options() { return options; }
};


/****************************************************************
 **
 ** Implementation
 **
 ****************************************************************/

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

/****************************************************************
 ** class DragIcon
 */

DragIcon::DragIcon(const Glib::ustring& text, PluginType tp, Glib::RefPtr<Gdk::DragContext> context, gx_system::CmdlineOptions& options, int xoff)
    : window(), drag_icon_pixbuf() {
    Glib::RefPtr<Gdk::Screen> screen = context->get_source_window()->get_screen();
    Glib::RefPtr<Gdk::Colormap> rgba = screen->get_rgba_colormap();
    if (screen->is_composited()) {
	window = new Gtk::Window(Gtk::WINDOW_POPUP);
	if (rgba) { // else will look ugly..
	    window->set_colormap(rgba);
	}
    }
    create_drag_icon_pixbuf(text, tp, rgba, options);
    int w = drag_icon_pixbuf->get_width();
    int h = drag_icon_pixbuf->get_height();
    int h2 = (h/2)-2;
    int w2 = std::min(w, xoff) - 4;
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

void DragIcon::destroy() {
    delete window;
    window = 0;
}

bool DragIcon::icon_expose_event(GdkEventExpose *ev) {
    Cairo::RefPtr<Cairo::Context> cr = Glib::wrap(ev->window, true)->create_cairo_context();
    Gdk::Cairo::add_region_to_path(cr, Glib::wrap(ev->region));
    cr->set_operator(Cairo::OPERATOR_SOURCE);
    cr->clip();
    Gdk::Cairo::set_source_pixbuf(cr, drag_icon_pixbuf, 0, 0);
    cr->paint();
    return true;
}

void DragIcon::create_drag_icon_pixbuf(const Glib::ustring& text, PluginType tp, Glib::RefPtr<Gdk::Colormap> rgba, gx_system::CmdlineOptions& options) {
    Gtk::OffscreenWindow w;
    w.signal_expose_event().connect(sigc::bind(sigc::mem_fun(*this, &DragIcon::window_expose_event), sigc::ref(w)));
    if (rgba) {
	w.set_colormap(rgba);
    }
    Gtk::Widget *r = RackBox::create_drag_widget(text, tp, options);
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
	const Gtk::Allocation a = child->get_allocation();
	Gdk::Cairo::set_source_pixmap(cr, child->get_window()->get_offscreen_pixmap(), a.get_x(), a.get_y());
	//cr->paint();
    }
    Cairo::RefPtr<Cairo::Surface> x_surf = cr->get_target();
    int w = gdk_window_get_width(event->window);
    int h = gdk_window_get_height(event->window);
    int dp = 10;
    Cairo::RefPtr<Cairo::LinearGradient> grad = Cairo::LinearGradient::create(w, 0, w-dp, 0);
    grad->add_color_stop_rgba(0, 1, 1, 1, 1);
    grad->add_color_stop_rgba(1, 1, 1, 1, 0);
    cr->rectangle(w-dp, 0, dp, h);
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
	b->add(*l);
	b->signal_clicked().connect(sigc::mem_fun(rb, &RackBox::on_kill));
	w = b;
    } else {
	w = new Gtk::Alignment();
    }
    w->set_size_request(20, 15);
    return w;
}

MiniRackBox::MiniRackBox(RackBox& rb, const Glib::RefPtr<Gtk::Action>& action, gx_system::CmdlineOptions& options)
    : Gtk::HBox(), evbox(), mconbox(false, 4), mb_expand_button(), mb_delete_button(), preset_button() {
    if (!szg_label) {
	szg_label = Gtk::SizeGroup::create(Gtk::SIZE_GROUP_HORIZONTAL);
    }
    evbox.set_visible_window(false);
    add(evbox);
    Gtk::HBox *box = new Gtk::HBox();
    evbox.add(*manage(box));
    Gxw::Switch *swtch = new Gxw::Switch("minitoggle");
    swtch->cp_set_var("eqs.on_off");
    //swtch->set_related_action(action);
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(swtch->gobj()), action->gobj());
    Gtk::Alignment *al = new Gtk::Alignment(0.5,0.5);
    al->add(*manage(swtch));
    RackBox::szg->add_widget(*al);
    box->pack_start(*al, Gtk::PACK_SHRINK);
    Gtk::Widget *effect_label = RackBox::make_label(rb.effect_id, rb.tp, options);
    szg_label->add_widget(*manage(effect_label));
    al = new Gtk::Alignment();
    al->add(*manage(RackBox::make_bar()));
    box->pack_start(*manage(al), Gtk::PACK_SHRINK);
    box->pack_start(*manage(effect_label), Gtk::PACK_SHRINK);
    Gxw::HSlider *sl = new Gxw::HSlider();
    sl->set_show_value(false);
    sl->set_adjustment(*manage(new Gtk::Adjustment(0,-1,1)));
    mconbox.pack_start(*sl, Gtk::PACK_SHRINK);
    Gtk::Label *l = new Gtk::Label("depth");
    l->set_name("rack_label");
    l->set_size_request(-1,18);
    l->set_alignment(0,1.0);
    mconbox.pack_start(*l, Gtk::PACK_SHRINK, 4);
    box->pack_start(mconbox, Gtk::PACK_EXPAND_WIDGET, 20);
    al = new Gtk::Alignment();
    Gtk::HBox *hb = new Gtk::HBox();
    al->add(*manage(hb));
    mb_expand_button = rb.make_expand_button(true);
    hb->pack_start(*mb_expand_button, Gtk::PACK_SHRINK);
    mb_delete_button = make_delete_button(rb);
    mb_delete_button->set_no_show_all(true);
    hb->pack_start(*mb_delete_button, Gtk::PACK_SHRINK);
    al->set_padding(1, 0, 4, 4);
    pack_end(*manage(al), Gtk::PACK_SHRINK);
    box->pack_end(*manage(RackBox::make_bar(8)), Gtk::PACK_SHRINK);
    preset_button = rb.make_preset_button();
    box->pack_end(*preset_button, Gtk::PACK_SHRINK);
    show_all();
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

Glib::RefPtr<Gtk::SizeGroup> RackBox::szg;

void RackBox::set_paintbox(Gxw::PaintBox& pb, PluginType tp) {
    pb.set_name("rackbox");
    pb.property_paint_func().set_value("rectangle_skin_color_expose");
    pb.set_border_width(4);
}

Gtk::Widget *RackBox::make_label(const Glib::ustring& name, PluginType tp, gx_system::CmdlineOptions& options) {
    Gtk::Label *effect_label = new Gtk::Label(name);
    effect_label->set_alignment(0, 0.5);
    effect_label->set_name("rack_effect_label");
    Pango::FontDescription font_desc = effect_label->get_style()->get_font();
    font_desc.set_size(int(7.5*Pango::SCALE));
    font_desc.set_weight(Pango::WEIGHT_BOLD);
    effect_label->modify_font(font_desc);
    if (tp == PLUGIN_TYPE_STEREO) {
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

Gtk::Widget *RackBox::create_icon_widget(const Glib::ustring& name, PluginType tp, gx_system::CmdlineOptions& options) {
    Gxw::PaintBox *pb = new Gxw::PaintBox(Gtk::ORIENTATION_HORIZONTAL);
    RackBox::set_paintbox(*pb, tp);
    Gtk::Widget *effect_label = RackBox::make_label(name, tp, options);
    Gtk::Alignment *al = new Gtk::Alignment();
    al->set_padding(0,2,2,0);
    al->add(*manage(effect_label));
    pb->pack_start(*manage(al), Gtk::PACK_SHRINK);
    pb->show_all();
    return pb;
}

Gtk::Widget *RackBox::create_drag_widget(const Glib::ustring& name, PluginType tp, gx_system::CmdlineOptions& options) {
    Gxw::PaintBox *pb = new Gxw::PaintBox(Gtk::ORIENTATION_HORIZONTAL);
    RackBox::set_paintbox(*pb, tp);
    if (name == "MainAmp") { // FIXME
	pb->property_paint_func().set_value("zac_expose");
    }
    Gxw::Switch *swtch = new Gxw::Switch("minitoggle");
    swtch->cp_set_var("eqs.on_off");
    RackBox::szg->add_widget(*swtch);
    pb->pack_start(*manage(swtch), Gtk::PACK_SHRINK);
    Gtk::Widget *effect_label = RackBox::make_label(name, tp, options);
    Gtk::Alignment *al = new Gtk::Alignment();
    al->set_padding(0,0,4,20);
    al->add(*manage(RackBox::make_bar(4, 4, true))); // FIXME: fix style and remove sens parameter
    pb->pack_start(*al, Gtk::PACK_SHRINK);
    pb->pack_start(*effect_label, Gtk::PACK_SHRINK);
    al = new Gtk::Alignment();
    al->set_size_request(50,-1);
    pb->pack_start(*manage(al), Gtk::PACK_SHRINK);
    pb->show_all();
    return pb;
}

RackBox::RackBox(const Glib::ustring& effect_id_, PluginType tp_, MainWindow& tl, Gtk::Widget* bare)
    : Gtk::VBox(), effect_id(effect_id_), tp(tp_), main(tl), vis(true), config_mode(false), anim_tag(),
      compress(true), delete_button(true), mbox(Gtk::ORIENTATION_HORIZONTAL), on_off_action(Gtk::ToggleAction::create()), minibox(0),
      fbox(0), target(), anim_height(0), drag_icon(), target_height(0), preset_index(-1), presets(),
      box(Gtk::ORIENTATION_HORIZONTAL, 2) {
    if (!szg) {
	szg = Gtk::SizeGroup::create(Gtk::SIZE_GROUP_HORIZONTAL);
    }
    //FIXME fill presets
    if (bare) {
	compress = false;
	delete_button = false;
    }
    set_paintbox(mbox, tp);
    minibox = new MiniRackBox(*this, on_off_action, tl.get_options());
    mbox.pack_start(*manage(minibox));
    pack_start(mbox, Gtk::PACK_SHRINK);
    if (bare) {
	add(*bare);
	fbox = bare;
	mbox.property_paint_func().set_value("zac_expose");
    } else {
	Gxw::PaintBox *pb = new Gxw::PaintBox(Gtk::ORIENTATION_HORIZONTAL);
	pb->show();
	set_paintbox(*pb, tp);
	pb->pack_start(*manage(make_full_box(tl.get_options())));
	pack_start(*manage(pb), Gtk::PACK_SHRINK);
	fbox = pb;
    }
    init_dnd();
    show();
}

void RackBox::init_dnd() {
    target = "application/x-guitarix-";
    if (tp == PLUGIN_TYPE_MONO) {
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
    mbox.signal_drag_data_delete().connect(sigc::mem_fun(*this, &RackBox::on_my_drag_data_delete));
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
    anim_height -= 7;
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

void RackBox::on_my_drag_begin(const Glib::RefPtr<Gdk::DragContext>& context) {
    int x, y;
    get_pointer(x, y);
    drag_icon = new DragIcon(effect_id, tp, context, main.get_options(), x);
    if (!dynamic_cast<RackContainer*>(get_parent())->check_if_animate(*this)) { //FIXME
	hide();
    } else {
	if (anim_tag.connected()) {
	    //Glib::source_remove(anim_tag);
	    anim_tag.disconnect();
	    set_size_request(-1,-1);
	    show();
	}
	anim_height = size_request().height;
	anim_tag = Glib::signal_timeout().connect(sigc::mem_fun(*this, &RackBox::animate_vanish), 20);
    }
}

bool RackBox::animate_create() {
    anim_height += 7;
    if (anim_height >= target_height) {
	set_size_request(-1,-1);
	//anim_tag.disconnect(); //FIXME
	return false;
    } else {
	set_size_request(-1, anim_height);
	return true;
    }
}

void RackBox::animate_insert() {
    if (!dynamic_cast<RackContainer*>(get_parent())->check_if_animate(*this)) { //FIXME
	show();
    } else {
	if (anim_tag.connected()) {
	    hide();
	    //glib.source_remove(self.anim_tag);
	    anim_tag.disconnect();
	    set_size_request(-1,-1);
	}
	target_height = size_request().height;
	set_size_request(-1,0);
	show();
	anim_height = 0;
	anim_tag = Glib::signal_timeout().connect(mem_fun(*this, &RackBox::animate_create), 20);
    }
}

void RackBox::on_my_drag_end(const Glib::RefPtr<Gdk::DragContext>& context) {
    if (drag_icon) {
	drag_icon->destroy();
	drag_icon = 0;
    }
    animate_insert();
}

void RackBox::on_my_drag_data_get(const Glib::RefPtr<Gdk::DragContext>& context, Gtk::SelectionData& selection, int info, int timestamp) {
    selection.set(target, effect_id);
}

void RackBox::on_my_drag_data_delete(const Glib::RefPtr<Gdk::DragContext>& context) {
    on_kill();
}

void RackBox::on_kill() {
    main.add_icon(effect_id);
    on_off_action->set_active(false);
    delete this;
}

void RackBox::vis_switch(Gtk::Widget& a, Gtk::Widget& b) {
    a.hide();
    b.show();
}

void RackBox::swtch(bool mini) {
    if (mini) {
	vis_switch(*fbox, mbox);
    } else {
	vis_switch(mbox, *fbox);
    }
}

void RackBox::on_expand(bool mini) {
    swtch(mini);
}

void RackBox::set_config_mode(bool mode) {
    config_mode = mode;
    minibox->set_config_mode(mode);
    if (mode) {
	vis = fbox->get_visible();
	if (vis) {
	    swtch(true);
	}
    } else {
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
    b->add(*l);
    b->set_size_request(20, 15);
    b->set_name("effect_reset");
    b->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &RackBox::on_expand), !expand));
    return b;
}

void RackBox::on_preset_popup_destroy(Gtk::Menu *w) {
    preset_index = w->property_active();
}

void RackBox::preset_popup() {
    Gtk::Menu *m = new Gtk::Menu();
    int i = 0;
    for (std::vector<Glib::ustring>::iterator s = presets.begin(); s != presets.end(); ++s) {
	Gtk::CheckMenuItem *c = new Gtk::CheckMenuItem(*s);
	if (i == preset_index) {
	    c->set_active(true);
	}
	m->append(*c);
	++i;
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
    //presets = ["setting %d" % (i+1) for i in range(3)]
    p->signal_clicked().connect(mem_fun(*this, &RackBox::preset_popup));
    return p;
}

void RackBox::pack(Gtk::Widget& child) {
    box.pack_start(child);
}

Gtk::HBox *RackBox::make_full_box(gx_system::CmdlineOptions& options) {
    Gtk::HBox *bx = new Gtk::HBox();
    bx->pack_start(*switcher_vbox(options), Gtk::PACK_SHRINK);
    box.set_name(effect_id);
    box.set_border_width(4);
    box.property_paint_func().set_value("RackBox_expose");
    bx->pack_start(box);
    Gtk::VBox *vbox = new Gtk::VBox();
    vbox->pack_start(*make_expand_button(false), Gtk::PACK_SHRINK);
    vbox->pack_start(*make_preset_button(), Gtk::PACK_EXPAND_PADDING);
    Gtk::Alignment *al = new Gtk::Alignment(0.5, 0.5, 1.0, 0.7);
    al->add(*vbox);
    al->set_padding(1, 0, 0, 4);
    bx->pack_end(*al, Gtk::PACK_SHRINK);
    bx->pack_end(*make_bar(4, 8), Gtk::PACK_SHRINK);
    bx->show_all();
    return bx;
}

Gtk::VBox *RackBox::switcher_vbox(gx_system::CmdlineOptions& options) {
    Gtk::VBox *vbox = new Gtk::VBox();
    Gtk::Widget *effect_label = make_label(effect_id, tp, options);
    vbox->pack_start(*effect_label, Gtk::PACK_SHRINK);
    Gtk::HBox *hbox = new Gtk::HBox();
    vbox->pack_start(*hbox);
    Gtk::HBox *hbox2 = new Gtk::HBox();
    hbox->pack_start(*hbox2, Gtk::PACK_SHRINK);
    Gtk::VBox *vbox2 = new Gtk::VBox();
    hbox2->pack_start(*vbox2);
    hbox2->pack_start(*make_bar(), Gtk::PACK_SHRINK);
    Gxw::Switch *swtch = new Gxw::Switch("switchit");
    szg->add_widget(*swtch);
    swtch->cp_set_var("eqs.on_off");
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(swtch->gobj()), GTK_ACTION(on_off_action->gobj()));
    Gtk::Alignment *al = new Gtk::Alignment(0.5,0.5);
    al->add(*swtch);
    vbox2->pack_start(*al);
    return vbox;
}


/****************************************************************
 ** class RackContainer
 */

RackContainer::RackContainer(PluginType tp_, MainWindow& main_)
    : Gtk::VBox(), tp(tp_), main(main_), config_mode(false), in_drag(-2), child_count(0), switch_level(1), targets(),
      hightlight_connection() {
    if (tp == PLUGIN_TYPE_MONO) {
	targets.push_back("application/x-guitarix-mono");
	targets.push_back("application/x-guitarix-mono-s");
	targets.push_back("application/x-gtk-tool-palette-item-mono");
    } else {
	targets.push_back("application/x-guitarix-stereo");
	targets.push_back("application/x-guitarix-stereo-s");
	targets.push_back("application/x-gtk-tool-palette-item-stereo");
    }
    std::vector<Gtk::TargetEntry> listTargets;
    listTargets.push_back(Gtk::TargetEntry("application/x-guitarix-mono", Gtk::TARGET_SAME_APP, 0));
    listTargets.push_back(Gtk::TargetEntry("application/x-guitarix-mono-s", Gtk::TARGET_SAME_APP, 1));
    listTargets.push_back(Gtk::TargetEntry("application/x-gtk-tool-palette-item-mono", Gtk::TARGET_SAME_APP, 2));
    listTargets.push_back(Gtk::TargetEntry("application/x-guitarix-stereo", Gtk::TARGET_SAME_APP, 3));
    listTargets.push_back(Gtk::TargetEntry("application/x-guitarix-stereo-s", Gtk::TARGET_SAME_APP, 4));
    listTargets.push_back(Gtk::TargetEntry("application/x-gtk-tool-palette-item-stereo", Gtk::TARGET_SAME_APP, 5));
    drag_dest_set(listTargets, Gtk::DEST_DEFAULT_DROP, Gdk::ACTION_MOVE);
    signal_remove().connect(sigc::mem_fun(*this, &RackContainer::on_my_remove));
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
	x = 0;
	y = 0;
	Glib::RefPtr<Gdk::Window> w = get_window();
	width = w->get_width();
	height = w->get_height();
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
    int y0, y1;
    Gtk::Widget *child;
    childpos(int y0_, int y1_, Gtk::Widget* ch): y0(y0_), y1(y1_), child(ch) {}
    bool operator<(const childpos& p) { return y0 < p.y0; }
};

void RackContainer::find_index(int x, int y, int* len, int *ypos) {
    std::list<childpos> l;
    std::vector<RackBox*> children = get_children();
    for (std::vector<RackBox*>::iterator ch = children.begin(); ch != children.end(); ++ch) {
	Gtk::Allocation a = (*ch)->get_allocation();
	int ht;
	if (!(*ch)->get_visible()) {
	    ht = 0;
	} else {
	    ht = a.get_height();
	}
	l.push_back(childpos(a.get_y(), a.get_y()+ht, (*ch)));
    }
    if (l.empty()) {
	*len = -1;
	*ypos = -1;
	return;
    }
    l.sort();
    Gtk::Allocation a0 = get_allocation();
    y += a0.get_y();
    int sy = l.begin()->y0;
    int i = 0;
    for (std::list<childpos>::iterator cp = l.begin(); cp != l.end(); ++cp) {
	if (y < (cp->y0 + cp->y1) / 2) {
	    *len = i;
	    *ypos = (cp->y0+sy)/2;
	    return;
	}
	sy = cp->y1;
    }
    *len = l.size();
    *ypos = sy;
}

void RackContainer::on_my_remove(Gtk::Widget *ch) {
    child_count -= 1;
    //assert self.child_count >= 0
    if (child_count == 0 && tp == PLUGIN_TYPE_MONO && main.show_plugin_bar_action->get_active()) {
	main.get_monorackcontainer().set_size_request(-1, 20);
    }
}

bool RackContainer::check_targets(const std::vector<std::string>& tgts) {
    for (std::vector<std::string>::iterator t = targets.begin(); t != targets.end(); ++t) {
	for (std::vector<std::string>::const_iterator t2 = tgts.begin(); t2 != tgts.end(); ++t2) {
	    if (*t == *t2) {
		return true;
	    }
	}
    }
    return false;
}

bool RackContainer::on_drag_motion(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, guint timestamp) {
    if (!check_targets(context->get_targets())) {
	return false;
    }
    context->drag_status(Gdk::ACTION_MOVE, timestamp);
    int i, ind;
    find_index(x, y, &i, &ind);
    if (in_drag == ind) {
	return true;
    }
    if (in_drag > -2) {
	hightlight_connection.disconnect();
    }
    hightlight_connection = signal_expose_event().connect(sigc::bind(sigc::mem_fun(*this, &RackContainer::drag_highlight_expose), ind), true);
    queue_draw();
    in_drag = ind;
    return true;
}

void RackContainer::on_drag_leave(const Glib::RefPtr<Gdk::DragContext>& context, guint timestamp) {
    if (in_drag > -2) {
	hightlight_connection.disconnect();
	queue_draw();
	in_drag = -2;
    }
}

void RackContainer::on_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, const Gtk::SelectionData& data, guint info, guint timestamp) {
    int i, ind;
    find_index(x, y, &i, &ind);
    std::string dtype = data.get_data_type();
    if (dtype == "application/x-gtk-tool-palette-item-mono" || dtype == "application/x-gtk-tool-palette-item-stereo") {
	main.add_rackbox(*main.get_plugin(data.get_data_as_string()), false, i, true);
    } else {
	reorder(data.get_data_as_string(), i);
	context->drag_status(Gdk::ACTION_COPY, timestamp);
    }
}

void RackContainer::show_entries() {
    Glib::ListHandle<RackBox*> l = get_children();
    for (Glib::ListHandle<RackBox*>::iterator ch = l.begin(); ch != l.end(); ++ch) {
	(*ch)->show();
    }
}

void RackContainer::hide_entries() {
    Glib::ListHandle<RackBox*> l = get_children();
    for (Glib::ListHandle<RackBox*>::iterator ch = l.begin(); ch != l.end(); ++ch) {
	if ((*ch)->can_compress()) {
	    (*ch)->hide();
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
	    if (i == pos) {
		return;
	    }
	    r = *v;
	    break;
	}
	++i;
    }
    if (!r) {
	//FIXME errormessage
	return;
    }
    reorder_child(*r, pos);
}

void RackContainer::on_add(Widget *ch) {
    add(*dynamic_cast<RackBox*>(ch));
}

void RackContainer::add(RackBox& r, int pos) {
    pack_start(r, Gtk::PACK_SHRINK);
    ++child_count;
    reorder_child(r, pos);
    if (config_mode) {
	r.set_config_mode(true);
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
    std::vector<RackBox*> l = get_children();
    for (std::vector<RackBox*>::iterator c = l.begin(); c != l.end(); ++c) {
	if ((*c)->can_compress()) {
	    (*c)->swtch(true);
	}
    }
}

void RackContainer::expand_all() {
    std::vector<RackBox*> l = get_children();
    for (std::vector<RackBox*>::iterator c = l.begin(); c != l.end(); ++c) {
	if ((*c)->can_compress()) {
	    (*c)->swtch(false);
	}
    }
}

bool RackContainer::empty() const {
    return get_children().empty();
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
    //self.tag = None
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
    //print "TM", self.size  // FIXME do logging
    //self.tag = None
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
    //glib.source_remove(self.tag)
    //self.tag = None
    //self.size = None
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
    //print self.size, (width, height), self.widget.window.get_state()
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

void update_scrolled_window(Gtk::ScrolledWindow& w) {
    Gtk::PolicyType hp, vp;
    w.get_policy(hp, vp);
    w.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    w.set_policy(hp, vp);
}

/*
** moving / hiding / showing parts of the UI
*/

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
    geom.min_width = -1;
    geom.max_width = -1;
    geom.min_height = -1;
    geom.max_height = -1;
    w->set_geometry_hints(geom, Gdk::HINT_MIN_SIZE|Gdk::HINT_MAX_SIZE);
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
    //self.live_play.display_tuner(v) FIXME
    update_scrolled_window(*vrack_scrolledbox);
}

void MainWindow::load_widget_pointers() {
    bld->get_toplevel("MainWindow", window);
    bld->find_widget("tunerbox", tunerbox);
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
    bld->find_widget("liveplay:barbutton", liveplay_button);
    bld->find_widget("tuner:barbutton", tuner_button);
    bld->find_widget("effects:barbutton", effects_button);
    bld->find_widget("presets:barbutton", presets_button);
    bld->find_widget("compress:barbutton", compress_button);
    bld->find_widget("expand:barbutton", expand_button);
    bld->find_widget("effects_toolpalette", effects_toolpalette);
    bld->find_widget("amp_background:ampbox", amp_background);
}

bool MainWindow::is_variable_size() {
    return presets_action->get_active() || show_rack_action->get_active();
}

void MainWindow::maybe_change_resizable() {
    if (window->get_window()->get_state() != 0) {
	return;
    }
    if (!is_variable_size() && window->get_resizable()) {
	window->set_resizable(false);
    } else if (!window->get_resizable()) {
	window->set_resizable(true);
    }
}

void child_set_property(Gtk::Container& container, Gtk::Widget& child, const char *property_name, bool value) {
    GValue v = {0};
    g_value_init(&v, G_TYPE_BOOLEAN);
    g_value_set_boolean(&v, value);
    gtk_container_child_set_property(container.gobj(), child.gobj(), property_name, &v);
}

void MainWindow::on_show_rack() {
    Gtk::Widget *w;
    if (get_dir() == 0) {
	// vertically
	w = stereorackcontainerV;
    } else {
	w = stereorackbox;
    }
    bool v = show_rack_action->get_active();
    fullscreen_action->set_sensitive(v);
    rackv_action->set_sensitive(v);
    rackh_action->set_sensitive(v);
    if (v) {
	//main_vpaned->child_set_property(amp_toplevel_box, "resize", true);
	child_set_property(*main_vpaned, *amp_toplevel_box, "resize", true);
	main_vpaned->set_position(oldpos);
	w->show();
	monoampcontainer->show();
	monorackcontainer.show_entries();
	vrack_scrolledbox->set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_AUTOMATIC);
	vrack_scrolledbox->set_size_request(scrl_size_x, scrl_size_y);
	if (window->get_window()->get_state() == 0) {
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
	//#print "##", self.window_height
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

void MainWindow::on_fullscreen() {
    bool v = fullscreen_action->get_active();
    show_rack_action->set_sensitive(!v);
    if (v) {
	window->fullscreen();
    } else {
	window->unfullscreen();
    }
}

void MainWindow::on_compress_all() {
    monorackcontainer.compress_all();
    stereorackcontainer.compress_all();
}

void MainWindow::on_expand_all() {
    monorackcontainer.expand_all();
    stereorackcontainer.expand_all();
}

void MainWindow::on_show_plugin_bar() {
    bool v = show_plugin_bar_action->get_active();
    show_rack_action->set_sensitive(!v);
    tuner_action->set_sensitive(!v);
    presets_action->set_sensitive(!v);
    compress_action->set_sensitive(!v);
    expand_action->set_sensitive(!v);
    Gtk::Requisition req;
    monobox->size_request(req);
    stereorackcontainer.set_config_mode(v);
    monorackcontainer.set_config_mode(v);
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
	if (get_dir() == 0) {
	    // vertically
	    monobox->set_size_request(req.width-req2.width,-1);
	    if (stereorackcontainer.empty()) {
		change_expand(*monobox, true);
	    } else if (monorackcontainer.empty()) {
		monorackcontainer.set_size_request(-1, 20);
	    }
	} else {
	    monobox->set_size_request(req.width-req2.width/2,-1);
	    change_expand(*monobox, true);
	}
    } else {
	if (pre_act) {
	    presets_action->set_active(true);
	}
	monobox->set_size_request(-1,-1);
	effects_frame_paintbox->hide();
	upper_rackbox->show();
	change_expand(*monobox, false);
	monorackcontainer.set_size_request(-1, -1);
    }
    update_scrolled_window(*vrack_scrolledbox);
    update_scrolled_window(*stereorackbox);
    maybe_shrink_horizontally();
    //show_size_request(self.window)
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

int MainWindow::get_dir() const {
    return rackv_action->get_current_value();
}

void MainWindow::change_expand(Gtk::Widget& w, bool value) {
    Gtk::Box *p = dynamic_cast<Gtk::Box*>(w.get_parent());
    int expand, fill;
    unsigned int padding;
    GtkPackType pack_type;
    gtk_box_query_child_packing(p->gobj(), w.gobj(), &expand, &fill, &padding, &pack_type);
    gtk_box_set_child_packing(p->gobj(), w.gobj(), value, fill, padding, pack_type);
}

void MainWindow::on_dir_changed(Glib::RefPtr<Gtk::RadioAction> act) {
    if (act->get_current_value()) {
	// horizontally
	move_widget(stereorackcontainer, *stereorackcontainerV, *stereorackcontainerH);
	change_expand(*monobox, true);
	stereorackbox->show();
    } else {
	move_widget(stereorackcontainer, *stereorackcontainerH, *stereorackcontainerV);
	stereorackbox->hide();
	if (show_plugin_bar_action->get_active()) {
	    change_expand(*monobox, stereorackcontainer.empty());
	    if (monorackcontainer.empty()) {
		monorackcontainer.set_size_request(-1, 20);
	    }
	} else {
	    if (!stereorackcontainer.empty()) {
		change_expand(*monobox, false);
	    }
	}
	maybe_shrink_horizontally();
    }
}

void MainWindow::on_configure_event(GdkEventConfigure *ev) {
    // print ev.x, ev.y, ev.width, ev.height
    if (freezer.check_thaw(ev->width, ev->height)) {
	if (is_variable_size()) {
	    window_height = ev->height;
	}
    }
}

void MainWindow::add_rackbox_internal(const std::string& name, PluginType tp, Gtk::Widget *widget, bool mini, int pos, bool animate, Gtk::Widget *bare) {
    RackBox *r = new RackBox(name, tp, *this, bare);
    if (mini) {
	r->swtch(true);
    }
    if (widget) {
	r->pack(*widget);
    }
    if (tp == PLUGIN_TYPE_MONO) {
	monorackcontainer.add(*r, pos);
	monorackcontainer.set_size_request(-1, -1);
    } else {
	stereorackcontainer.add(*r, pos);
    }
    if (animate) {
	r->animate_insert();
    }
}

void MainWindow::add_rackbox(const PluginUI& pl, bool mini, int pos, bool animate) {
    Gtk::Widget *widget = 0;
    if (!pl.fname.empty()) {
	//widget = load_rack_ui(pl.fname, self.pmap); FIXME
    }
    add_rackbox_internal(pl.name, pl.tp, widget, mini, pos, animate);
}

bool MainWindow::check_if_rack_container_size_animate(const RackContainer& rackcontainer) const {
    if (&rackcontainer == &monorackcontainer && get_dir() == 0 && !stereorackcontainer.empty()) {
	// non-empty stereo box below
	return true;
    }
    return false;
}

void MainWindow::add_icon(const std::string& name) {
    plugin_dict[name]->toolitem->show();
}

void MainWindow::on_show_values() {
    std::string s =
	"style \"ShowValue\n\" {\n"
	"  GxRegler::show-value = " + gx_system::to_string(show_values_action->get_active()) + "\n"
	"}\n"
	"class \"*GxRegler*\" style:highest \"ShowValue\"\n";
    gtk_rc_parse_string(s.c_str());
    gtk_rc_reset_styles(gtk_settings_get_default());
}

void MainWindow::on_preset_action() {
    maybe_change_resizable();
    //self.preset_window.on_preset_select(act) FIXME
    if (presets_action->get_active() && !show_rack_action->get_active()) {
	Gtk::Requisition req;
	window->size_request(req);
	int x, y;
	window->get_position(x, y);
	while (Gtk::Main::events_pending()) {
	    Gtk::Main::iteration();
	}
	window->get_window()->move_resize(x, y, req.width, max(req.height, window_height));
    }
}

/*
** UI initialization
*/

void MainWindow::add_toolitem(PluginUI& pl, Gtk::ToolItemGroup *gw) {
    Gtk::ToolItem *tb = new Gtk::ToolItem();
    tb->set_use_drag_window(true);
    tb->signal_drag_begin().connect(sigc::bind(sigc::mem_fun(*this, &MainWindow::on_ti_drag_begin), pl.name, pl.tp));
    tb->signal_drag_end().connect(sigc::mem_fun(*this, &MainWindow::on_ti_drag_end));
    tb->signal_drag_data_delete().connect(sigc::bind(sigc::mem_fun(*this, &MainWindow::on_ti_drag_data_delete), pl.name));
    tb->signal_button_press_event().connect(sigc::bind(sigc::mem_fun(*this, &MainWindow::on_ti_button_press), pl.name));
    std::vector<Gtk::TargetEntry> listTargets;
    if (pl.tp == PLUGIN_TYPE_MONO) {
	listTargets.push_back(Gtk::TargetEntry("application/x-gtk-tool-palette-item-mono", Gtk::TARGET_SAME_APP, 0));
    } else {
	listTargets.push_back(Gtk::TargetEntry("application/x-gtk-tool-palette-item-stereo", Gtk::TARGET_SAME_APP, 0));
    }
    tb->drag_source_set(listTargets, Gdk::BUTTON1_MASK, Gdk::ACTION_MOVE);
    tb->signal_drag_data_get().connect(sigc::bind(sigc::mem_fun(*this, &MainWindow::on_ti_drag_data_get), pl.name));
    Gtk::Image *img = new Gtk::Image(pl.icon);
    if (!pl.tooltip.empty()) {
	img->set_tooltip_text(pl.tooltip);
    }
    tb->add(*img);
    pl.toolitem = tb;
    gw->add(*tb);
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
    //live_play.on_live_play(live_play_action); FIXME
}

void MainWindow::on_ti_drag_begin(const Glib::RefPtr<Gdk::DragContext>& context, const std::string& effect_id, PluginType tp) {
    drag_icon = new DragIcon(effect_id, tp, context, options);
}

void MainWindow::on_ti_drag_end(const Glib::RefPtr<Gdk::DragContext>& context) {
    if (drag_icon) {
	drag_icon->destroy();
	drag_icon = 0;
    }
}

void MainWindow::on_ti_drag_data_get(const Glib::RefPtr<Gdk::DragContext>& context, Gtk::SelectionData& selection, int info, int timestamp, const std::string& effect_id) {
    selection.set(*context->get_targets().begin(), effect_id);
}

void MainWindow::hide_effect(const std::string& name) {
    plugin_dict[name]->toolitem->hide();
}

void MainWindow::on_ti_drag_data_delete(const Glib::RefPtr<Gdk::DragContext>& context, const std::string& effect_id) {
    hide_effect(effect_id);
}

bool MainWindow::on_ti_button_press(GdkEventButton *ev, const std::string& effect_id) {
    if (ev->type == GDK_2BUTTON_PRESS) {
	add_rackbox(*get_plugin(effect_id), false, -1, true);
	hide_effect(effect_id);
	return true;
    }
    return false;
}

void MainWindow::on_tp_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, const Gtk::SelectionData& data, int info, int timestamp) {
    add_icon(data.get_data_as_string());
    get_plugin(data.get_data_as_string())->group->set_collapsed(false);
}

const char *menudef =
    "<ui>\n"
    "  <menubar>\n"
    "    <menu name=\"engine\" action=\"EngineMenuAction\">\n"
    "      <menuitem name=\"quit\" action=\"QuitAction\" />\n"
    "    </menu>\n"
    "    <menu name=\"presets\" action=\"PresetsMenuAction\">\n"
    "      <menuitem name=\"select_preset\" action=\"PresetsAction\" />\n"
    "    </menu>\n"
    "    <menu name=\"plugins\" action=\"PluginsMenuAction\">\n"
    "      <menuitem name=\"show_plugin_bar\" action=\"ShowPluginBarAction\" />\n"
    "      <menuitem name=\"show_rack\" action=\"ShowRackAction\" />\n"
    "      <menuitem name=\"compress_all\" action=\"CompressAction\" />\n"
    "      <menuitem name=\"expand_all\" action=\"ExpandAction\" />\n"
    "      <menuitem name=\"order_rack_vertically\" action=\"RackVAction\" />\n"
    "      <menuitem name=\"order_rack_horizontally\" action=\"RackHAction\" />\n"
    "    </menu>\n"
    "    <menu name=\"tube\" action=\"TubeMenuAction\">\n"
    "    </menu>\n"
    "    <menu name=\"options\" action=\"OptionsMenuAction\">\n"
    "      <menuitem name=\"tuner\" action=\"TunerAction\" />\n"
    "      <menuitem name=\"values\" action=\"ShowValuesAction\" />\n"
    "      <menuitem name=\"live display\" action=\"LiveplayAction\" />\n"
    //"      <menuitem name=\"fullscreen\" action=\"FullscreenAction\" />\n"
    "    </menu>\n"
    "    <menu name=\"about\" action=\"AboutMenuAction\">\n"
    "    </menu>\n"
    "  </menubar>\n"
    "</ui>\n";

Glib::RefPtr<Gtk::UIManager> MainWindow::create_menu(Glib::RefPtr<Gtk::ActionGroup>& actiongroup) {
    Glib::RefPtr<Gtk::UIManager> uimanager = Gtk::UIManager::create();
    // Create actions
    actiongroup->add(Gtk::Action::create("EngineMenuAction","_Engine"));
    actiongroup->add(Gtk::Action::create("PresetsMenuAction","_Presets"));
    actiongroup->add(Gtk::Action::create("PluginsMenuAction","P_lugins"));
    actiongroup->add(Gtk::Action::create("TubeMenuAction","_Tube"));
    actiongroup->add(Gtk::Action::create("OptionsMenuAction","_Options"));
    actiongroup->add(Gtk::Action::create("AboutMenuAction","_About"));
    actiongroup->add(Gtk::Action::create("QuitAction","_Quit"),Gtk::AccelKey("<Control>q"),sigc::ptr_fun(Gtk::Main::quit));
    compress_action = Gtk::Action::create("CompressAction","_Compress all");
    actiongroup->add(compress_action,Gtk::AccelKey("<control>c"),sigc::mem_fun(*this, &MainWindow::on_compress_all));
    expand_action = Gtk::Action::create("ExpandAction","E_xpand all");
    actiongroup->add(expand_action, Gtk::AccelKey("<control>e"),sigc::mem_fun(*this, &MainWindow::on_expand_all));
    // Create a ToggleAction, etc.
    show_plugin_bar_action = Gtk::ToggleAction::create("ShowPluginBarAction","Show _Plugin Bar","",true);
    actiongroup->add(show_plugin_bar_action, Gtk::AccelKey("<Control>b"), sigc::mem_fun(*this, &MainWindow::on_show_plugin_bar));
    show_rack_action = Gtk::ToggleAction::create("ShowRackAction","Show _Rack","",true);
    actiongroup->add(show_rack_action, Gtk::AccelKey("<Control>r"),sigc::mem_fun(*this, &MainWindow::on_show_rack));
    live_play_action = Gtk::ToggleAction::create("LiveplayAction","_Live Display");
    actiongroup->add(live_play_action, Gtk::AccelKey("<Control>l"),sigc::mem_fun(*this, &MainWindow::on_live_play));
    tuner_action = Gtk::ToggleAction::create("TunerAction","_Tuner","",true);
    actiongroup->add(tuner_action,Gtk::AccelKey("<Control>t"),sigc::mem_fun(*this, &MainWindow::on_show_tuner));
    show_values_action = Gtk::ToggleAction::create("ShowValuesAction","_Show Values");
    actiongroup->add(show_values_action, Gtk::AccelKey("<Control>s"), sigc::mem_fun(*this, &MainWindow::on_show_values));
    //('FullscreenAction',None,"_Fullscreen","F11",None,self.on_fullscreen,False),
    presets_action = Gtk::ToggleAction::create("PresetsAction","_Preset Selection");
    actiongroup->add(presets_action, Gtk::AccelKey("<control>p"), sigc::mem_fun(*this, &MainWindow::on_preset_action));
    // Create some RadioActions
    rackv_action = Gtk::RadioAction::create(dir_group, "RackVAction", "Order Rack Vertically");
    rackv_action->property_value().set_value(0);
    actiongroup->add(rackv_action, Gtk::AccelKey("<Control>v"));
    rackh_action = Gtk::RadioAction::create(dir_group, "RackHAction", "Order Rack Horizontally");
    rackh_action->property_value().set_value(1);
    actiongroup->add(rackh_action, Gtk::AccelKey("<Control>h"));
    rackh_action->set_active(true);
    rackv_action->signal_changed().connect(sigc::mem_fun(*this, &MainWindow::on_dir_changed));
    // Add the actiongroup to the uimanager
    uimanager->insert_action_group(actiongroup);
    uimanager->add_ui_from_string(menudef);
    return uimanager;
}

/*
void get_current_workarea(int &x, int &y, int &width, int &height) {
    // Helper fetching the current workarea (i.e. usable space) size
    _NET_CURRENT_DESKTOP = Gdk::atom_intern("_NET_CURRENT_DESKTOP");
    _NET_WORKAREA = Gdk::atom_intern("_NET_WORKAREA");
    Glib::RefPtr<Gdk::Window> root = Gdk::screen_get_default().get_root_window();
    prop = root.property_get(_NET_CURRENT_DESKTOP);
    if (prop is None) {
        x, y, width, height, depth = root.get_geometry();
        return x, y, width, height;
    }
    propname, proptype, propvalue = prop;
    current = propvalue[0];
    prop = root.property_get(_NET_WORKAREA);
    if (prop is None) {
        x, y, width, height, depth = root.get_geometry();
        return x, y, width, height;
    }
    propname, proptype, propvalue = prop;
    x, y, width, height = propvalue[current * 4 : (current + 1) * 4];
    return x, y, width, height;
}
*/

void MainWindow::clear_box(Gtk::Container& box) {
    std::vector<Gtk::Widget*> l = box.get_children();
    for (std::vector<Gtk::Widget*>::iterator p = l.begin(); p != l.end(); ++p) {
	box.remove(**p);
    }
}

struct PluginDesc {
    Glib::ustring group;
    std::vector<PluginUI*> *plugins;
    PluginDesc(const Glib::ustring& g, std::vector<PluginUI*> *p)
	: group(g), plugins(p) {}
};

std::vector<PluginDesc*>& get_pluginlist(gx_system::CmdlineOptions& options) {
    static std::vector<PluginDesc*> l;
    std::vector<PluginUI*> *p;

    p = new std::vector<PluginUI*>;
    p->push_back(new PluginUI(PLUGIN_TYPE_MONO, "low high pass"));
    p->push_back(new PluginUI(PLUGIN_TYPE_MONO, "Scaleable EQ"));
    p->push_back(new PluginUI(PLUGIN_TYPE_MONO, "ImpulseResponse"));
    p->push_back(new PluginUI(PLUGIN_TYPE_MONO, "BiQuad Filter"));
    p->push_back(new PluginUI(PLUGIN_TYPE_MONO, "Feedback"));
    p->push_back(new PluginUI(PLUGIN_TYPE_MONO, "Tonestack", options.get_builder_filepath("tonestack_ui.glade")));
    p->push_back(new PluginUI(PLUGIN_TYPE_MONO, "Cabinet"));
    p->push_back(new PluginUI(PLUGIN_TYPE_STEREO, "Moog Filter"));
    p->push_back(new PluginUI(PLUGIN_TYPE_STEREO, "3 Band EQ"));
    l.push_back(new PluginDesc("Tone control", p));

    p = new std::vector<PluginUI*>;
    p->push_back(new PluginUI(PLUGIN_TYPE_MONO, "Multi Band Distortion"));
    p->push_back(new PluginUI(PLUGIN_TYPE_MONO, "Overdrive"));
    p->push_back(new PluginUI(PLUGIN_TYPE_STEREO, "Postamp"));
    l.push_back(new PluginDesc("Distortion", p));

    p = new std::vector<PluginUI*>;
    p->push_back(new PluginUI(PLUGIN_TYPE_MONO, "FreeVerb"));
    p->push_back(new PluginUI(PLUGIN_TYPE_STEREO, "Convolver"));
    p->push_back(new PluginUI(PLUGIN_TYPE_STEREO, "Stereo Verb"));
    p->push_back(new PluginUI(PLUGIN_TYPE_STEREO, "Zita Rev1", options.get_builder_filepath("zita_rev1_ui.glade"), "High Quality Reverb"));
    l.push_back(new PluginDesc("Reverb", p));

    p = new std::vector<PluginUI*>;
    p->push_back(new PluginUI(PLUGIN_TYPE_MONO, "Echo"));
    p->push_back(new PluginUI(PLUGIN_TYPE_MONO, "Delay"));
    p->push_back(new PluginUI(PLUGIN_TYPE_STEREO, "Stereo Delay"));
    p->push_back(new PluginUI(PLUGIN_TYPE_STEREO, "Stereo Echo"));
    l.push_back(new PluginDesc("Echo / Delay", p));

    p = new std::vector<PluginUI*>;
    p->push_back(new PluginUI(PLUGIN_TYPE_MONO, "Tremolo", options.get_builder_filepath("tremolo_ui.glade")));
    p->push_back(new PluginUI(PLUGIN_TYPE_MONO, "Phaser Mono"));
    p->push_back(new PluginUI(PLUGIN_TYPE_MONO, "Chorus Mono"));
    p->push_back(new PluginUI(PLUGIN_TYPE_MONO, "Flanger Mono"));
    p->push_back(new PluginUI(PLUGIN_TYPE_STEREO, "Chorus"));
    p->push_back(new PluginUI(PLUGIN_TYPE_STEREO, "Flanger"));
    p->push_back(new PluginUI(PLUGIN_TYPE_STEREO, "Phaser"));
    p->push_back(new PluginUI(PLUGIN_TYPE_STEREO, "UniVibe"));
    l.push_back(new PluginDesc("Modulation", p));

    p = new std::vector<PluginUI*>;
    p->push_back(new PluginUI(PLUGIN_TYPE_MONO, "Crybaby", options.get_builder_filepath("crybaby_ui.glade")));
    p->push_back(new PluginUI(PLUGIN_TYPE_MONO, "Crybaby 2"));
    p->push_back(new PluginUI(PLUGIN_TYPE_MONO, "Compressor"));
    l.push_back(new PluginDesc("Guitar Effects", p));

    p = new std::vector<PluginUI*>;
    p->push_back(new PluginUI(PLUGIN_TYPE_MONO, "Oscilloscope"));
    p->push_back(new PluginUI(PLUGIN_TYPE_MONO, "MIDI out"));
    l.push_back(new PluginDesc("Misc", p));

    return l;
}

void make_icons(std::map<std::string, PluginUI*>& plugin_dict, gx_system::CmdlineOptions& options) {
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
        Gtk::Widget *r = RackBox::create_icon_widget(i->second->name, i->second->tp, options);
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
        i->second->hide();
    }
    //w.destroy();
}

MainWindow::MainWindow(gx_system::CmdlineOptions& options_, gx_engine::ParamMap& pmap_) //std::string style_dir, std::string style_fname, std::string main_fname, std::string dirpath /*, rack_plugins, rackamp*/)
    : sigc::trackable(), window_height(0), freezer(), bld(), oldpos(0), scrl_size_x(-1), scrl_size_y(-1),
      monorackcontainer(PLUGIN_TYPE_MONO, *this), stereorackcontainer(PLUGIN_TYPE_STEREO, *this),
      pre_act(false), is_visible(false), drag_icon(0), plugin_dict(), actiongroup(), uimanager(),
      ui(), options(options_), pmap(pmap_) {
    /*
    ** max window size is work area reduce by arbitrary amount to
    ** make it visually more appealing and to account for the unknown
    ** frame size (difficult to find out, would have to query the
    ** window mananger)
    */
    //self.window_height = std::min(600, get_current_workarea()[3]-50);
    window_height = 600;

    //self.pmap = ParamMap(param_fname)
    //gtk_rc_parse(options.get_style_filepath(style_fname));
    //gtk.rc_parse_string(styledef % style_dir);

    // load builder def
    const char *id_list[] = {"MainWindow", "amp_background:ampbox", "bank_liststore", "target_liststore", "bank_combo_liststore", 0};
    bld = gx_gui::GxBuilder::create_from_file(options.get_builder_filepath("mainpanel.glade"), &ui, id_list);
    load_widget_pointers();
    rackcontainer->set_homogeneous(true); // setting it in glade is awkward to use with glade tool
    status_image->set(options.get_pixmap_filepath("gx_on.png"));
    jackd_image->set(options.get_pixmap_filepath("jackd_off.png"));
    logstate_image->set(options.get_pixmap_filepath("gx_off.png"));
    // remove child labels from boxes used for demo:
    clear_box(*monocontainer);
    clear_box(*stereorackcontainerH);
    clear_box(*stereorackcontainerV);

    //self.preset_window = PresetWindow(bld, actiongroup, self)

    // create menu
    actiongroup = Gtk::ActionGroup::create("Main");
    uimanager = create_menu(actiongroup);
    Gtk::Widget *menubar = uimanager->get_widget("/menubar");
    menubox->pack_start(*menubar);
    window->add_accel_group(uimanager->get_accel_group());

    // create rack
    stereorackcontainerH->pack_start(stereorackcontainer, Gtk::PACK_EXPAND_WIDGET);
    monocontainer->pack_start(monorackcontainer, Gtk::PACK_EXPAND_WIDGET);

    std::vector<PluginDesc*>& pluginlist = get_pluginlist(options);
    for (std::vector<PluginDesc*>::iterator l = pluginlist.begin(); l != pluginlist.end(); ++l) {
	for (std::vector<PluginUI*>::iterator v = (*l)->plugins->begin(); v != (*l)->plugins->end(); ++v) {
	    plugin_dict[(*v)->name] = (*v);
	}
    }
    make_icons(plugin_dict, options);

    // connect signal
    window->signal_configure_event().connect_notify(sigc::mem_fun(*this, &MainWindow::on_configure_event));
    //w.connect("destroy", gtk.main_quit);
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(show_rack_button->gobj()), GTK_ACTION(show_rack_action->gobj()));
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(liveplay_button->gobj()),GTK_ACTION(live_play_action->gobj()));
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(tuner_button->gobj()),GTK_ACTION(tuner_action->gobj()));
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(effects_button->gobj()), GTK_ACTION(show_plugin_bar_action->gobj()));
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(presets_button->gobj()), GTK_ACTION(presets_action->gobj()));
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(compress_button->gobj()), GTK_ACTION(compress_action->gobj()));
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(expand_button->gobj()), GTK_ACTION(expand_action->gobj()));

    //self.live_play = Liveplay(self.preset_window, main_fname, self.actiongroup)

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
    bool collapse = false;
    for (std::vector<PluginDesc*>::iterator l = pluginlist.begin(); l != pluginlist.end(); ++l) {
	Gtk::ToolItemGroup *gw = new Gtk::ToolItemGroup((*l)->group);
	gw->set_collapsed(collapse);
	collapse = true;
	for (std::vector<PluginUI*>::iterator v = (*l)->plugins->begin(); v != (*l)->plugins->end(); ++v) {
	    add_toolitem(**v, gw);
	}
	effects_toolpalette->add(*manage(gw));
	effects_toolpalette->set_exclusive(*gw, true);
	effects_toolpalette->set_expand(*gw, true);
    }
    effects_toolpalette->show_all();

    add_rackbox_internal("MainAmp", PLUGIN_TYPE_MONO, 0, false, -1, false, amp_background);
    /*
    for pl in rack_plugins:
	self.add_rackbox(pl)
	self.hide_effect(pl)
    */
    window->signal_visibility_notify_event().connect(sigc::mem_fun(*this, &MainWindow::on_visibility_notify));
    window->show();
}

MainWindow::~MainWindow() {
    delete window;
}

void start_main(gx_system::CmdlineOptions& options, gx_engine::ParamMap& pmap) {
    MainWindow w(options, pmap);
    w.run();
}
