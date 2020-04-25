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
#include <boost/algorithm/string/replace.hpp>

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

PluginUI::PluginUI(PluginDict& plugin_dict_, const char *name,
		   const Glib::ustring& tooltip_)
    : action(),
      group(),
      toolitem(),
      rackbox(),
      hidden(false),
      active(false),
      output_widget_state(),
      output_widgets_active(false),
      tooltip(tooltip_),
      shortname(),
      plugin(plugin_dict_.get_machine().pluginlist_lookup_plugin(name)),
    plugin_dict(plugin_dict_) {
    if (plugin->get_pdef()->description && tooltip.empty()) {
	tooltip = plugin->get_pdef()->description;
    }
    plugin->get_pdef()->flags |= gx_engine::PGNI_UI_REG;
    active = !has_gui();
}

PluginUI::~PluginUI() {
    output_widget_state.clear();
    delete rackbox;
    if (toolitem) {
	if (group) {
	    group->remove(*toolitem);
	}
	delete toolitem;
    }
    plugin->get_pdef()->flags &= ~gx_engine::PGNI_UI_REG;
}

void PluginUI::on_plugin_preset_popup() {
    plugin_dict.plugin_preset_popup(plugin->get_pdef());
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

void PluginUI::set_action(Glib::RefPtr<ToggleAction>& act)
{
    action = act;
    action->signal_toggled().connect(sigc::mem_fun(*this, &PluginUI::on_action_toggled));
}

void PluginUI::on_action_toggled() {
    if (rackbox && action->get_active() == active) {
	return;
    }
    if (action->get_active()) {
	plugin_dict.activate(get_id(), "", true);
    } else {
	plugin_dict.deactivate(get_id(), true);
    }
}

void PluginUI::hide(bool animate) {
    rackbox->display(false, animate);
}

void PluginUI::show(bool animate) {
    hidden = plugin_dict.get_plugins_hidden();
    if (hidden) {
	rackbox->hide();
    } else {
	rackbox->display(true, animate);
    }
}

void PluginUI::activate(bool animate, const string& before) {
    if (!has_gui() || active) {
	return;
    }
    active = true;
    hidden = plugin_dict.get_plugins_hidden();
    toolitem->hide();
    bool plug = plugin->get_plug_visible();
    if (rackbox) {
	rackbox->swtch(plug);
    } else {
	rackbox = plugin_dict.add_rackbox(*this, plug, -1, animate);
    }
    plugin->set_box_visible(true);
    rackbox->set_config_mode(plugin_dict.get_config_mode());
    set_update_state(get_update_cond());
    if (hidden) {
	rackbox->display(false, false);
    } else {
	rackbox->display(true, animate);
    }
    set_active(true);
}

void PluginUI::deactivate(bool animate) {
    if (!has_gui() || !active) {
	return;
    }
    active = false;
    plugin->set_box_visible(false);
    toolitem->show();
    hide(animate);
    set_active(false);
}

void PluginUI::set_config_mode(bool state) {
    if (active) {
	on_state_change();
	rackbox->set_config_mode(state);
    }
}

void PluginUI::update_rackbox() {
    if (!rackbox) {
	return;
    }
    if (!plugin->get_box_visible()) {
	delete rackbox;
	rackbox = 0;
    }
    RackContainer *container = rackbox->get_parent();
    RackContainer::rackbox_list l = container->get_children();
    string before;
    for (RackContainer::rackbox_list::iterator i = l.begin(); i != l.end(); ++i) {
	if (*i == rackbox) {
	    if (++i != l.end()) {
		before = (*i)->get_id();
	    }
	    break;
	}
    }
    hide(false);
    delete rackbox;
    rackbox = plugin_dict.add_rackbox(*this, plugin->get_plug_visible(), -1, false);
    show(false);
    container->reorder(get_id(), before);
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

bool PluginUI::on_rack_handle_press(GdkEventButton* ev) {
    if (ev->type == GDK_2BUTTON_PRESS && ev->button == 1) {
        plugin_dict.deactivate(get_id(), true);
	group->set_collapsed(false);
	return true;
    }
    return false;
}

void PluginUI::on_ti_drag_begin(const Glib::RefPtr<Gdk::DragContext>& context) {
    plugin_dict.drag_icon = new DragIcon(*this, context, plugin_dict.get_options());
}

void PluginUI::on_ti_drag_data_get(const Glib::RefPtr<Gdk::DragContext>& context, Gtk::SelectionData& selection, int info, int timestamp) {
    selection.set(*context->list_targets().begin(), get_id());
}

void PluginUI::on_ti_drag_data_delete(const Glib::RefPtr<Gdk::DragContext>& context) {
    toolitem->hide();
}

bool PluginUI::on_ti_button_press(GdkEventButton *ev) {
    if (ev->type == GDK_2BUTTON_PRESS) {
	plugin_dict.activate(get_id(), "", true);
	return true;
    }
    return false;
}

void PluginUI::on_ti_drag_end(const Glib::RefPtr<Gdk::DragContext>& context) {
    if (plugin_dict.drag_icon) {
	delete plugin_dict.drag_icon;
	plugin_dict.drag_icon = nullptr;
    }
}

bool PluginUI::on_my_leave_out(GdkEventCrossing *focus) {
    Glib::RefPtr<Gdk::Window> wind = toolitem->get_window();
    wind->set_cursor();
    return true;
}

bool PluginUI::on_my_enter_in(GdkEventCrossing *focus) {
    Glib::RefPtr<Gdk::Window> wind = toolitem->get_window();
    Glib::RefPtr<Gdk::Display> disp = toolitem->get_display();
    Glib::RefPtr<Gdk::Cursor> cursor(Gdk::Cursor::create(disp, Gdk::HAND1));
    wind->set_cursor(cursor);
    return true;
}

Glib::ustring PluginUI::get_displayname(bool useshort) const {
    Glib::ustring name = useshort ? get_shortname() : get_name();
    if (get_type() == PLUGIN_TYPE_STEREO) {
	name = "◗◖ " + name; //♾⚮⦅◗◖⦆⚭ ⧓ Ꝏꝏ ⦅◉⦆● ▷◁ ▶◀
    }
    return name;
}

void PluginUI::add_toolitem(Gtk::ToolItemGroup *gw) {
    Gtk::ToolItem *tb = new Gtk::ToolItem();
    tb->set_use_drag_window(true);
    tb->signal_drag_begin().connect(sigc::mem_fun(*this, &PluginUI::on_ti_drag_begin));
    tb->signal_drag_end().connect(sigc::mem_fun(*this, &PluginUI::on_ti_drag_end));
    tb->signal_drag_data_delete().connect(sigc::mem_fun(*this, &PluginUI::on_ti_drag_data_delete));
    tb->signal_button_press_event().connect(sigc::mem_fun(*this, &PluginUI::on_ti_button_press));
    tb->add_events(Gdk::ENTER_NOTIFY_MASK|Gdk::LEAVE_NOTIFY_MASK);
    tb->signal_leave_notify_event().connect(sigc::mem_fun(*this, &PluginUI::on_my_leave_out));
    tb->signal_enter_notify_event().connect(sigc::mem_fun(*this, &PluginUI::on_my_enter_in));
    std::vector<Gtk::TargetEntry> listTargets;
    if (get_type() == PLUGIN_TYPE_MONO) {
	listTargets.push_back(Gtk::TargetEntry("application/x-gtk-tool-palette-item-mono", Gtk::TARGET_SAME_APP, 0));
    } else {
	listTargets.push_back(Gtk::TargetEntry("application/x-gtk-tool-palette-item-stereo", Gtk::TARGET_SAME_APP, 0));
    }
    tb->drag_source_set(listTargets, Gdk::BUTTON1_MASK, Gdk::ACTION_MOVE);
    tb->signal_drag_data_get().connect(sigc::mem_fun(*this, &PluginUI::on_ti_drag_data_get));
    Gtk::Label *img = new Gtk::Label(get_displayname(true));
    img->set_xalign(0);
    img->set_halign(Gtk::ALIGN_END);
    if (!tooltip.empty()) {
	gx_gui::GxBuilder::set_tooltip_text_connect_handler(*img, tooltip);
    }
    tb->add(*manage(img));
    tb->show_all();
    toolitem = tb;
    gw->add(*manage(tb));
    group = gw;
}

bool PluginUI::get_update_cond() {
    return active && !plugin_dict.get_config_mode() && plugin->get_on_off() /*&& !plugin->get_plug_visible()*/;
}

void PluginUI::set_update_state(bool state) {
    output_widgets_active = state;
    output_widget_state(state);
}

void PluginUI::on_state_change() {
    int i = get_update_cond();
    if (i != output_widgets_active) {
	set_update_state(i);
    }
}

// define if memory leaks in atk, pango, etc. are closed (valgrind --leak-check=full guitarix)
//#define LEAKS_OK

void PluginUI::dispose_rackbox() {
    if (plugin->get_box_visible()) {
        rackbox->hide(); // dnd operation, just hide
    } else {
#ifdef LEAKS_OK
        delete rackbox;
        rackbox = nullptr;
#else
        rackbox->hide();
#endif
    }
}

bool PluginUI::animate_vanish() {
    rackbox->anim_height -= rackbox->anim_step;
    if (rackbox->anim_height > 0) {
	rackbox->set_size_request(-1, rackbox->anim_height);
	return true;
    }
    rackbox->set_visibility(true);
    rackbox->set_size_request(-1,-1);
    dispose_rackbox();
    return false;
}

#define ANIMATE_STEPS 5
#define ANIMATE_TIME 20
#define AUTOSCROLL_TIMEOUT 50

void PluginUI::remove(bool animate) {
    if (!animate || !plugin_dict.use_animations()) {
        dispose_rackbox();
    } else {
	if (rackbox->anim_tag.connected()) {
	    rackbox->anim_tag.disconnect();
	    rackbox->set_size_request(-1,-1);
	    rackbox->show();
	}
	gint min_height, natural_height;
	rackbox->get_preferred_height(min_height, natural_height);
	rackbox->anim_height = min_height;
	rackbox->set_size_request(-1, rackbox->anim_height);
	rackbox->set_visibility(false);
	rackbox->anim_step = rackbox->anim_height / ANIMATE_STEPS;
	rackbox->anim_tag = Glib::signal_timeout().connect(
	    sigc::mem_fun(*this, &PluginUI::animate_vanish),
	    ANIMATE_TIME);
    }
}


/****************************************************************
 ** class PluginDict
 */

PluginDict::PluginDict(gx_engine::GxMachineBase& machine_, gx_system::CmdlineOptions& options_,
		       Gtk::ToolPalette& toolpalette_, gx_gui::StackBoxBuilder& boxbuilder_,
		       UIManager& uimanager_)
    : monorackcontainer(*this),
      stereorackcontainer(*this),
      groupmap(),
      monotargets(),
      stereotargets(),
      boxbuilder(boxbuilder_),
      machine(machine_),
      options(options_),
      toolpalette(toolpalette_),
      uimanager(uimanager_),
      config_mode(false),
      plugins_hidden(false),
      drag_icon(0) {
    std::vector<Gtk::TargetEntry> listTargets;
    // the tool palette accepts drags from the racks
    listTargets.push_back(Gtk::TargetEntry("application/x-guitarix-mono", Gtk::TARGET_SAME_APP, 0));
    listTargets.push_back(Gtk::TargetEntry("application/x-guitarix-stereo", Gtk::TARGET_SAME_APP, 1));
    toolpalette.drag_dest_set(listTargets, Gtk::DEST_DEFAULT_ALL, Gdk::ACTION_MOVE);
    toolpalette.signal_drag_data_received().connect(sigc::mem_fun(*this, &PluginDict::on_tp_drag_data_received));
    // the racks additionally accept drags from the tool palette
    listTargets.push_back(Gtk::TargetEntry("application/x-gtk-tool-palette-item-mono", Gtk::TARGET_SAME_APP, 2));
    listTargets.push_back(Gtk::TargetEntry("application/x-gtk-tool-palette-item-stereo", Gtk::TARGET_SAME_APP, 3));
    monotargets.push_back("application/x-guitarix-mono");
    monotargets.push_back("application/x-gtk-tool-palette-item-mono");
    stereotargets.push_back("application/x-guitarix-stereo");
    stereotargets.push_back("application/x-gtk-tool-palette-item-stereo");
    monorackcontainer.set_list_targets(listTargets, monotargets, stereotargets);
    stereorackcontainer.set_list_targets(listTargets, stereotargets, monotargets);
    machine.signal_selection_changed().connect(
	sigc::mem_fun0(this, &PluginDict::check_order));
    machine.signal_rack_unit_order_changed().connect(
	sigc::mem_fun(this, &PluginDict::unit_order_changed));
    machine.signal_plugin_changed().connect(
	sigc::mem_fun(this, &PluginDict::on_plugin_changed));
    fill_pluginlist();
}

PluginUI *PluginDict::activate(const string& id, const string& before, bool animate) {
    PluginUI *p = at(id);
    if (!p->has_gui() || p->active) {
	return p;
    }
    p->plugin->set_plug_visible(false);
    p->activate(animate, before);
    machine.insert_rack_unit(id, before, p->get_type());
    return p;
}

PluginUI *PluginDict::deactivate(const string& id, bool animate) {
    PluginUI *p = at(id);
    if (!p->has_gui() || !p->active) {
	return p;
    }
    p->plugin->set_on_off(false);
    p->deactivate(animate);
    machine.remove_rack_unit(id, p->get_type());
    return p;
}

double PluginDict::stop_at(RackContainer *container, double off, double step_size, double page_size) {
    if (container == &monorackcontainer) {
	return stereorackcontainer.stop_at_bottom(off, step_size, page_size);
    } else {
	assert(container == &stereorackcontainer);
	return monorackcontainer.stop_at_top(off, step_size);
    }
}

void PluginDict::check_order() {
    check_order(PLUGIN_TYPE_MONO, false);
    check_order(PLUGIN_TYPE_STEREO, false);
}

void PluginDict::check_order(PluginType tp, bool animate) {
    RackContainer& container = (tp == PLUGIN_TYPE_STEREO) ? stereorackcontainer : monorackcontainer;
    const std::vector<std::string> ol = machine.get_rack_unit_order(tp);
    bool in_order = true;
    int pos = 0;
    unsigned int post_pre = 1;
    bool need_renumber = false;
    std::set<std::string> unit_set(ol.begin(), ol.end());
    RackContainer::rackbox_list l = container.get_children();
    std::vector<std::string>::const_iterator oi = ol.begin();
    for (RackContainer::rackbox_list::iterator c = l.begin(); c != l.end(); ++c) {
	string id = (*c)->get_id();
	PluginUI *p = at(id);
	if (!p->active) {
	    continue;
	}
	if (unit_set.find(id) == unit_set.end()) {
	    deactivate(id, animate);
	    continue;
	}
	if (!in_order) {
	    continue;
	}
	if (oi == ol.end()) {
	    in_order = false;
	    continue;
	}
	if (*oi != id) {
	    in_order = false;
	    continue;
	}
	if (id == "ampstack") {
	    pos = 0;
	    post_pre = 0;
	    continue;
	}
	if (!need_renumber && !(*c)->compare_position(pos, post_pre)) {
	    need_renumber = true;
	}
	++oi;
    }
    if (oi != ol.end()) {
	in_order = false;
    }
    if (!in_order) {
	int n = 0;
	for (std::vector<std::string>::const_iterator oi = ol.begin(); oi != ol.end(); ++oi) {
	    PluginUI *p = at(*oi);
	    p->activate(animate, "");
	    if (p->rackbox) {
		container.reorder_child(*p->rackbox, n++);
	    }
	}
    }
    if (!in_order || need_renumber) {
	container.renumber();
    }
    container.set_child_count(ol.size());
}

void PluginDict::unit_order_changed(bool stereo) {
    check_order(stereo ? PLUGIN_TYPE_STEREO : PLUGIN_TYPE_MONO, true);
}

void PluginDict::reorder(RackContainer *container, const std::string& name, const std::string& before) {
    PluginType tp = (container == &monorackcontainer ? PLUGIN_TYPE_MONO : PLUGIN_TYPE_STEREO);
    machine.insert_rack_unit(name, before, tp);
}

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
    for (std::map<Glib::ustring, Gtk::ToolItemGroup*>::iterator i = groupmap.begin(); i != groupmap.end(); ++i) {
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

void PluginDict::set_config_mode(bool state) {
    config_mode = state;
    for (std::map<std::string, PluginUI*>::iterator i = begin(); i != end(); ++i) {
	i->second->set_config_mode(state);
    }
}

void PluginDict::show_entries() {
    plugins_hidden = false;
    for (std::map<std::string, PluginUI*>::iterator i = begin(); i != end(); ++i) {
	i->second->hidden = false;
	if (i->second->active) {
	    RackBox *r = i->second->rackbox;
	    if (r) {
		r->show();
	    }
	}
    }
}

void PluginDict::hide_entries() {
    plugins_hidden = true;
    for (std::map<std::string, PluginUI*>::iterator i = begin(); i != end(); ++i) {
	i->second->hidden = true;
	RackBox *r = i->second->rackbox;
	if (r) {
	    if (r->can_compress()) {
		r->hide();
	    }
	}
    }
}

void PluginDict::on_tp_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, const Gtk::SelectionData& data, int info, int timestamp) {
    Glib::ustring id = data.get_data_as_string();
    PluginUI *p = deactivate(id, false);
    p->group->set_collapsed(false);
}

void PluginDict::add_plugin(std::vector<PluginUI*>& p, const char *id, const Glib::ustring& tooltip) {
    if (PluginUI::is_registered(machine, id)) {
	return;
    }
    p.push_back(new PluginUI(*this, id, tooltip));
}

void PluginDict::add_bare(const char * id, Gtk::Container *box) {
    PluginUI *plugin = new PluginUI(*this, id);
    add(plugin);
    plugin->rackbox = add_rackbox_internal(*plugin, 0, 0, false, -1, false, box);
}

RackBox *PluginDict::add_rackbox_internal(PluginUI& plugin, Gtk::Widget *mainwidget, Gtk::Widget *miniwidget,
					  bool mini, int pos, bool animate, Gtk::Widget *bare) {
    RackBox *r = new RackBox(plugin, *this, bare);
    r->swtch(mini);
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

RackBox *PluginDict::add_rackbox(PluginUI& pl, bool mini, int pos, bool animate) {
    gx_gui::UiBuilderImpl builder(this, &boxbuilder, nullptr, &pl);
    Gtk::Widget *mainwidget = 0;
    Gtk::Widget *miniwidget = 0;
    if (machine.load_unit(builder, pl.plugin->get_pdef())) {
        boxbuilder.fetch(mainwidget, miniwidget);
    }
    return add_rackbox_internal(pl, mainwidget, miniwidget, mini, pos, animate);
}

void PluginDict::plugin_preset_popup(const PluginDef *pdef) {
    new PluginPresetPopup(pdef, machine);
}

void PluginDict::plugin_preset_popup(const PluginDef *pdef, const Glib::ustring& name) {
    new PluginPresetPopup(pdef, machine, name);
}

void PluginDict::pluginlist_append(std::vector<PluginUI*>& p) {
    gx_gui::UiBuilderImpl builder(this, &boxbuilder, &p, nullptr);
    machine.pluginlist_append_rack(builder);
}

void PluginDict::on_plugin_changed(gx_engine::Plugin *pl, gx_engine::PluginChange::pc c) {
    if (!pl) { // end of update sequence
        return;
    }
    if (c == gx_engine::PluginChange::add) {
        register_plugin(new PluginUI(*this, pl->get_pdef()->id, ""));
        return;
    }
    PluginUI *pui = at(pl->get_pdef()->id);
    if (c == gx_engine::PluginChange::remove) {
        Glib::ustring actname = pui->get_action()->get_name();
        remove_plugin_menu_entry(pui);
        uimanager.get_action_group()->remove(actname);
        machine.remove_rack_unit(pui->get_id(), pui->get_type());
        std::string group_id = pui->get_category();
        remove(pui);
        delete pui;
        Gtk::ToolItemGroup * group = groupmap[group_id];
        if (group->get_n_items() == 0) {
            // removal is optional since empty toolitem groups and
            // menus are already hidden.
            uimanager.remove_item(category_id(pui->get_category(), false));
            uimanager.remove_item(category_id(pui->get_category(), true));
            groupmap.erase(group_id);
            delete group;
        }
    } else {
        assert(c == gx_engine::PluginChange::update ||
               c == gx_engine::PluginChange::update_category);
        bool state =  pui->plugin->get_on_off();
        pui->update_rackbox();
        pui->plugin->set_on_off(state);
        if (c == gx_engine::PluginChange::update_category) {
            pui->group = add_plugin_category(pui->get_category());
            // if the toolitem group becomes empty, it will be hidden automatically
            pui->toolitem->reparent(*pui->group);
            remove_plugin_menu_entry(pui);
            add_plugin_menu_entry(pui);
        }
    }
}

Glib::ustring PluginDict::category_id(const std::string& group, bool stereo) {
    const char *tp = stereo ? "Stereo" : "Mono";
    std::string group_id = group;
    boost::replace_all(group_id, " ", ""); // FIXME: replace all invalid chars
    return Glib::ustring::compose("Plugin%1Category_%2", tp, group_id);
}

Gtk::ToolItemGroup *PluginDict::add_plugin_category(const char *group, bool collapse) {
    std::map<Glib::ustring, Gtk::ToolItemGroup*>::iterator it = groupmap.find(group);
    if (it != groupmap.end()) {
        return it->second;
    }
    // add category menus (mono and stereo)
    Glib::ustring display = gettext(group);
    Glib::RefPtr<Gio::MenuItem> item;
    Glib::ustring action;
    action = category_id(group, false);
    item = Gio::MenuItem::create(display, action);
    item->set_submenu(Gio::Menu::create());
    uimanager.get_linked_menu("MonoPlugins")->append_item(item);
    uimanager.find_item(action)->hide();
    action = category_id(group, true);
    item = Gio::MenuItem::create(display, action);
    item->set_submenu(Gio::Menu::create());
    uimanager.get_linked_menu("StereoPlugins")->append_item(item);
    uimanager.find_item(action)->hide();
    // toolitem group
    Gtk::ToolItemGroup *gw = new Gtk::ToolItemGroup(gettext(group));
    groupmap[group] = gw;
    gw->set_collapsed(collapse);
    toolpalette.add(*manage(gw));
    toolpalette.set_exclusive(*gw, true);
    toolpalette.set_expand(*gw, true);
    // make groups label left aligned (not settable in CSS)
    gw->get_label_widget()->set_halign(Gtk::ALIGN_START);
    return gw;
}

Glib::ustring PluginDict::add_plugin_menu_entry(PluginUI *pui) {
    Glib::ustring cat_id = category_id(
        pui->get_category(), pui->get_type() == PLUGIN_TYPE_STEREO);
    Glib::RefPtr<Gio::Menu> menu = uimanager.get_linked_menu(cat_id);
    uimanager.find_item(cat_id)->show();
    Glib::ustring actname = Glib::ustring::compose("Plugin_%1", pui->get_id());
    auto a = Gio::MenuItem::create(pui->get_name(), actname);
    menu->append_item(a);
    return actname;
}

void PluginDict::remove_plugin_menu_entry(PluginUI *pui) {
    Glib::ustring action = pui->get_action()->get_name();
    auto *menu = dynamic_cast<Gtk::Menu*>(uimanager.find_item(action)->get_parent());
    uimanager.remove_item(action);
    if (menu->get_children().size() == 0) {
        menu->get_attach_widget()->hide();
    }
}

void PluginDict::register_plugin(PluginUI *pui) {
    add(pui);
    Gtk::ToolItemGroup *gw = add_plugin_category(pui->get_category());
    Glib::ustring actionname = add_plugin_menu_entry(pui);
    pui->add_toolitem(gw);
    Glib::RefPtr<ToggleAction> act = uimanager.add_toggle_action(
        actionname, pui->plugin->get_box_visible());
    pui->set_action(act);
    if (pui->plugin->get_box_visible()) {
        act->set_active(true);
    }
}

class JConvPluginUI: public PluginUI {
private:
    virtual void on_plugin_preset_popup();
public:
    JConvPluginUI(PluginDict& plugin_dict, const char* id,
		  const Glib::ustring& tooltip="")
	: PluginUI(plugin_dict, id, tooltip) {
    }
};

void JConvPluginUI::on_plugin_preset_popup() {
    gx_engine::JConvParameter *jcp = dynamic_cast<gx_engine::JConvParameter*>(
	&plugin_dict.get_machine().get_parameter(std::string(get_id())+".convolver"));
    assert(jcp);
    Glib::ustring name = jcp->get_value().getIRFile();
    Glib::ustring::size_type n = name.find_last_of('.');
    if (n != Glib::ustring::npos) {
	name.erase(n);
    }
    plugin_dict.plugin_preset_popup(plugin->get_pdef(), name);
}

void PluginDict::fill_pluginlist() {
    // define order of categories by registering
    // them first
    add_plugin_category(N_("Tone Control"), false);
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
    pluginlist_append(p);
    std::sort(p.begin(), p.end(), plugins_by_name_less);
    for (std::vector<PluginUI*>::iterator v = p.begin(); v != p.end(); ++v) {
	register_plugin(*v);
    }
}


/****************************************************************
 ** class DragIcon
 */

DragIcon::DragIcon(PluginUI& plugin, Glib::RefPtr<Gdk::DragContext> context, gx_system::CmdlineOptions& options, int xoff)
    : window(), drag_icon_pixbuf() {
    Glib::RefPtr<Gdk::Screen> screen = context->get_source_window()->get_screen();
    Glib::RefPtr<Gdk::Visual> rgba;
    if (screen->is_composited()) {
	rgba = screen->get_rgba_visual();
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
    while (Gtk::Main::events_pending()) { // needed for style updates
	Gtk::Main::iteration(false);
    }
    w.get_window()->process_updates(true);
    drag_icon_pixbuf = w.get_pixbuf();
}

bool DragIcon::window_draw(const Cairo::RefPtr<Cairo::Context> &cr, Gtk::OffscreenWindow& widget) {
    Gtk::Widget *child = widget.get_child();
    if (child) {
	widget.propagate_draw(*child, cr);
    }
    if (!window) {
	return true;
    }
    int w = widget.get_window()->get_width();
    int h = widget.get_window()->get_height();
    Cairo::RefPtr<Cairo::LinearGradient> grad = Cairo::LinearGradient::create(w, 0, w-gradient_length, 0);
    grad->add_color_stop_rgba(0, 1, 1, 1, 1);
    grad->add_color_stop_rgba(1, 1, 1, 1, 0);
    cr->rectangle(w-gradient_length, 0, gradient_length, h);
    cr->mask(grad);
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
	b->signal_clicked().connect(
	    sigc::hide_return(
		sigc::bind(
		    sigc::mem_fun(rb.plugin.plugin_dict, &PluginDict::deactivate),
		    rb.get_id(), true)));
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
      on_off_switch("switchit") {
    gx_gui::ui_connect_switch(rb.plugin_dict.get_machine(), &on_off_switch,
                              rb.plugin.plugin->id_on_off(), nullptr, false);
    if (strcmp(rb.plugin.get_id(), "ampstack") != 0) { // FIXME
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
	al->get_style_context()->add_class("minibox-title");
    
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
    }
    show_all();
}

void MiniRackBox::pack(Gtk::Widget *w) {
    if (w) {
	mconbox.pack_start(*manage(w), Gtk::PACK_SHRINK, 4);
    }
}

void MiniRackBox::set_config_mode(bool mode, PluginUI& plugin) {
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
	    // force event handling of the button to be above the evbox
	    mb_delete_button->hide();
	    Glib::signal_idle().connect_once(
		sigc::mem_fun(mb_delete_button,&Gtk::Widget::show),
		Glib::PRIORITY_HIGH_IDLE);
	    evbox_button = evbox.signal_button_press_event().connect(
		sigc::mem_fun(plugin, &PluginUI::on_rack_handle_press));
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
	    evbox_button.disconnect();
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

void RackBox::set_paintbox_unit_shrink(Gxw::PaintBox& pb, PluginType tp) {
    pb.get_style_context()->add_class("rackmini");
    pb.set_border_width(0);
}

void RackBox::set_paintbox_unit(Gxw::PaintBox& pb, const PluginUI& plugin) {
    pb.set_border_width(0);
}

void RackBox::set_paintbox(Gxw::PaintBox& pb, PluginType tp) {
    pb.set_name("rackbox");
   // pb.property_paint_func().set_value("rectangle_skin_color_expose");
    pb.set_border_width(0);
}

Gtk::Widget *RackBox::make_label(const PluginUI& plugin, gx_system::CmdlineOptions& options, bool useshort) {
    Gtk::Label *effect_label = new Gtk::Label(plugin.get_displayname(useshort));
    effect_label->set_alignment(0.0, 0.5);
    effect_label->get_style_context()->add_class("effect_title");
    return effect_label;
}

Gtk::Widget *RackBox::make_bar(int left, int right, bool sens) {
    Gtk::Alignment *al = new Gtk::Alignment(0, 0, 1.0, 1.0);
    //al->set_padding(4, 4, left, right);
    Gtk::Button *button = new Gtk::Button();
    button->set_size_request(32,-1);
    //button->set_name("effect_reset");
    gx_gui::GxBuilder::set_tooltip_text_connect_handler(*button, _("Drag'n' Drop Handle"));
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

Gtk::Widget *RackBox::wrap_bar(int left, int right, bool sens) {
    Gtk::EventBox *ev = new Gtk::EventBox;
    ev->set_visible_window(false);
    ev->set_above_child(true);
    ev->add(*manage(make_bar(left, right, sens)));
    ev->signal_leave_notify_event().connect(sigc::mem_fun(*this, &RackBox::on_my_leave_out));
    ev->signal_enter_notify_event().connect(sigc::mem_fun(*this, &RackBox::on_my_enter_in));
    ev->signal_button_press_event().connect(sigc::mem_fun(plugin, &PluginUI::on_rack_handle_press));
    ev->signal_drag_begin().connect(sigc::mem_fun(*this, &RackBox::on_my_drag_begin));
    ev->signal_drag_end().connect(sigc::mem_fun(*this, &RackBox::on_my_drag_end));
    ev->signal_drag_failed().connect(sigc::mem_fun(*this, &RackBox::on_my_drag_failed));
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
    if (v) {
	if (animate) {
	    animate_insert();
	} else {
	    show();
	}
    } else {
	plugin.remove(animate);
    }
}

RackBox::RackBox(PluginUI& plugin_, PluginDict& tl, Gtk::Widget* bare)
    : Gtk::VBox(),
      plugin(plugin_),
      plugin_dict(tl),
      anim_tag(),
      compress(true),
      delete_button(true),
      mbox(Gtk::ORIENTATION_HORIZONTAL),
      minibox(0),
      fbox(0),
      target(),
      anim_height(0),
      anim_step(),
      drag_icon(),
      target_height(0),
      box(Gtk::ORIENTATION_HORIZONTAL, 2),
      on_off_switch("switchit") {
    gx_gui::ui_connect_switch(tl.get_machine(), &on_off_switch,
                              plugin.plugin->id_on_off(), nullptr, false);
    if (bare) {
	compress = false;
	delete_button = false;
    }
    set_paintbox_unit_shrink(mbox, plugin.get_type());
    init_dnd();
    minibox = new MiniRackBox(*this, tl.get_options());
    mbox.pack_start(*manage(minibox));
    pack_start(mbox, Gtk::PACK_EXPAND_WIDGET);
    if (bare) {
	add(*manage(bare));
	fbox = bare;
    } else {
	Gxw::PaintBox *pb = new Gxw::PaintBox(Gtk::ORIENTATION_HORIZONTAL);
	pb->show();
	set_paintbox_unit(*pb, plugin);
	pb->pack_start(*manage(make_full_box(tl.get_options())));
	pack_start(*manage(pb), Gtk::PACK_SHRINK);
	fbox = pb;
    }
    fbox->get_style_context()->add_class("rackmain");

    string css_id = plugin.plugin->get_pdef()->id;
    boost::replace_all(css_id, ".", "-");
    set_name("PLUI-" + css_id);
    Glib::RefPtr<Gtk::StyleContext> context = get_style_context();
    context->add_class("rackbox");
    if (plugin.plugin->get_pdef()->flags & gx_engine::PGNI_IS_LV2) {
	context->add_class("PL-LV2");
    } else if (plugin.plugin->get_pdef()->flags & gx_engine::PGNI_IS_LADSPA) {
	context->add_class("PL-LADSPA");
    }
    on_off_switch.signal_toggled().connect(
	sigc::mem_fun(plugin, &PluginUI::on_state_change));
    show();
}

void RackBox::init_dnd() {
    target = "application/x-guitarix-";
    if (plugin.get_type() == PLUGIN_TYPE_MONO) {
	target += "mono";
    } else {
	target += "stereo";
    }
    mbox.signal_drag_begin().connect(sigc::mem_fun(*this, &RackBox::on_my_drag_begin));
    mbox.signal_drag_end().connect(sigc::mem_fun(*this, &RackBox::on_my_drag_end));
    mbox.signal_drag_failed().connect(sigc::mem_fun(*this, &RackBox::on_my_drag_failed));
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

RackContainer *RackBox::get_parent() {
    return dynamic_cast<RackContainer*>(Gtk::VBox::get_parent());
}

void RackBox::on_my_drag_begin(const Glib::RefPtr<Gdk::DragContext>& context) {
    int x, y;
    get_pointer(x, y);
    drag_icon = new DragIcon(plugin, context, plugin_dict.get_options(), x);
    plugin.remove(true);
    get_parent()->change_child_count(-1);
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
    if (!plugin_dict.use_animations()) {
	show();
	get_parent()->ensure_visible(*this);
    } else {
	if (anim_tag.connected()) {
	    hide();
	    anim_tag.disconnect();
	    set_size_request(-1,-1);
	}
	show();
	gint min_height, natural_height;
	get_preferred_height(min_height, natural_height); // needs show and visibility true
	target_height = min_height;
	set_size_request(-1,0);
	set_visibility(false);
	anim_height = 0;
	anim_step = target_height / ANIMATE_STEPS;
	anim_tag = Glib::signal_timeout().connect(mem_fun(*this, &RackBox::animate_create), ANIMATE_TIME);
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

bool RackBox::on_my_drag_failed(const Glib::RefPtr<Gdk::DragContext>& context, Gtk::DragResult result) {
    get_parent()->change_child_count(1);
    return false;
}

void RackBox::on_my_drag_data_get(const Glib::RefPtr<Gdk::DragContext>& context, Gtk::SelectionData& selection, int info, int timestamp) {
    selection.set(target, plugin.get_id());
}

void RackBox::vis_switch(Gtk::Widget& a, Gtk::Widget& b) {
    a.hide();
    b.show();
}

void RackBox::set_visibility(bool v) {
    bool config_mode = plugin_dict.get_config_mode();
    if (config_mode || get_plug_visible()) {
	mbox.set_visible(v);
	set_config_mode(plugin_dict.get_config_mode());
    } else {
	fbox->set_visible(v);
    }
}

void RackBox::swtch(bool mini) {
    plugin.plugin->set_plug_visible(mini);
    plugin.on_state_change();
    if (mini || plugin_dict.get_config_mode()) {
	vis_switch(*fbox, mbox);
    } else {
	vis_switch(mbox, *fbox);
    }
}

void RackBox::set_config_mode(bool mode) {
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
    minibox->set_config_mode(mode, plugin);
    enable_drag(mode);
}

void RackBox::set_position(int pos, int post_pre) {
    plugin.plugin->set_position(pos);
    if (plugin.get_type() == PLUGIN_TYPE_MONO) {
	plugin.plugin->set_effect_post_pre(post_pre);
    }
}

bool RackBox::compare_position(int pos, int post_pre) {
    if (plugin.plugin->get_position() != pos) {
	return false;
    }
    if (plugin.get_type() == PLUGIN_TYPE_MONO && plugin.plugin->get_effect_post_pre() != post_pre) {
	return false;
    }
    return true;
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
	gx_gui::GxBuilder::set_tooltip_text_connect_handler(*b, _("expand effect unit"));
    } else {
	t = "rack_shrink";
	gx_gui::GxBuilder::set_tooltip_text_connect_handler(*b, _("shrink effect unit"));
    }
    Gtk::Image *l = new Gtk::Image(Gtk::StockID(t), Gtk::ICON_SIZE_BUTTON);
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
    gx_gui::GxBuilder::set_tooltip_text_connect_handler(*p, _("manage effect unit presets"));
	p->set_name("effect_on_off");
    p->signal_clicked().connect(
	sigc::mem_fun(plugin, &PluginUI::on_plugin_preset_popup));
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


/****************************************************************
 ** class RackContainer
 */

static const int min_containersize = 40;

RackContainer::RackContainer(PluginDict& plugin_dict_)
    : Gtk::VBox(),
      plugin_dict(plugin_dict_),
      in_drag(-2),
      count(0),
      targets(),
      othertargets(),
      highlight_connection(),
      autoscroll_connection() {
    set_size_request(-1, min_containersize);
    show_all();
}

void RackContainer::set_list_targets(const std::vector<Gtk::TargetEntry>& listTargets,
				     const std::vector<std::string>& targets_,
				     const std::vector<std::string>& othertargets_) {
    targets = targets_;
    othertargets = othertargets_;
    drag_dest_set(listTargets, Gtk::DEST_DEFAULT_DROP, Gdk::ACTION_MOVE);
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
    Glib::RefPtr<Gdk::Pixbuf> pb_ = Gtk::IconTheme::get_default()->load_icon("insert", -1, Gtk::ICON_LOOKUP_GENERIC_FALLBACK);
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

void RackContainer::find_index(int x, int y, string *before, int *ypos) {
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
	if (before) {
	    *before = "";
	}
	*ypos = -1;
	return;
    }
    Gtk::Allocation a0 = get_allocation();
    y += a0.get_y();
    int sy = l.begin()->y0;
    for (std::list<childpos>::iterator cp = l.begin(); cp != l.end(); ++cp) {
	if (y < (cp->y0 + cp->y1) / 2) {
	    if (before) {
		*before = children[cp->pos]->get_id();
	    }
	    *ypos = (cp->y0+sy)/2 - a0.get_y();
	    return;
	}
	sy = cp->y1;
    }
    if (before) {
	*before = "";
    }
    *ypos = sy - a0.get_y();
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
		    sigc::mem_fun(*this, &RackContainer::scrollother_timeout), AUTOSCROLL_TIMEOUT);
	    }
	    context->drag_status(Gdk::DragAction(0), timestamp);
	    return true;
	}
	return false;
    }
    context->drag_status(Gdk::ACTION_MOVE, timestamp);
    int ind;
    find_index(x, y, nullptr, &ind);
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
	autoscroll_connection = Glib::signal_timeout().connect(
	    sigc::mem_fun(*this, &RackContainer::scroll_timeout), AUTOSCROLL_TIMEOUT);
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
    off = plugin_dict.stop_at(this, off, step_size, a->get_page_size());
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

double RackContainer::stop_at_bottom(double off, double step_size, double pagesize) {
    Gtk::Allocation alloc = get_allocation();
    double lim = alloc.get_y() + alloc.get_height() - pagesize;
    if (off >= lim) {
	return off;
    }
    return min(off+step_size, lim);
}

double RackContainer::stop_at_top(double off, double step_size) {
    Gtk::Allocation alloc = get_allocation();
    if (off < alloc.get_y()) {
	return off;
    }
    return max(off-step_size, double(alloc.get_y()));
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
    int ind;
    string before;
    find_index(x, y, &before, &ind);
    string id = data.get_data_as_string();
    std::string dtype = data.get_data_type();
    if (dtype == "application/x-gtk-tool-palette-item-mono" || dtype == "application/x-gtk-tool-palette-item-stereo") {
	plugin_dict.activate(id, before, true);
    } else {
	reorder(id, before);
	plugin_dict[id]->show(true);
    }
}

void RackContainer::on_add(Widget *ch) {
    assert(false);
}

void RackContainer::add(RackBox& r, int pos) {
    pack_start(r, false, true);
    if (pos != -1) {
	reorder_child(r, pos);
    }
}

void RackContainer::set_child_count(int n) {
    if (n == count) {
	return;
    }
    count = n;
    if (!count) {
	set_size_request(-1, min_containersize);
    } else {
	set_size_request(-1, -1);
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
	(*c)->set_position(pos, post_pre);
    }
}
