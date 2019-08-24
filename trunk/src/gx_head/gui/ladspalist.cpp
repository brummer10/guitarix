/*
 * Copyright (C) 2012 Andreas Degert, Hermann Meyer
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
 */

#include <lrdf.h>
#include <ladspa.h>
#include <dlfcn.h>

#include "guitarix.h"

using Glib::ustring;
using gx_system::JsonParser;
using gx_system::JsonWriter;
using gx_system::JsonException;

namespace ladspa {

const char *step_type_names[] = { "coarse", "normal", "fine" };
const char *display_type_names[] = { "Scale", "Log. Scale", "Toggle", "Enum", "Display", "Led", "Hide", "Int", "Toggle" };


/****************************************************************
 ** class PluginDisplay
 */

static const char *menudef = "\
<ui>\n\
  <menubar name=\"ladspalist\">\n\
    <menu action=\"FileMenuAction\">\n\
      <menuitem action=\"SelectAllAction\" />\n\
      <menuitem action=\"SelectNoneAction\" />\n\
      <menuitem action=\"SaveAction\" />\n\
      <menuitem action=\"ApplyAction\" />\n\
      <menuitem action=\"QuitAction\" />\n\
    </menu>\n\
    <menu action=\"ViewMenuAction\">\n\
      <menuitem action= \"FindAction\" />\n\
    </menu>\n\
  </menubar>\n\
</ui>\n\
";

static void append_displaytype(Glib::RefPtr<Gtk::ListStore> ls, DisplayType tp) {
    Gtk::TreeIter it = ls->append();
    it->set_value(0, ustring(display_type_names[tp]));
    it->set_value(1, tp);
}

class CellRendererComboDerived : public Gtk::CellRendererCombo {
public:
    CellRendererComboDerived() : Glib::ObjectBase (0), Gtk::CellRendererCombo() { }
    CellRendererComboDerived(BaseObjectType* castitem) : Glib::ObjectBase (0), Gtk::CellRendererCombo((GtkCellRendererCombo*)(castitem)) { }
    virtual ~CellRendererComboDerived() { }
    static CellRendererComboDerived* create_from_builder(BaseObjectType* cobject) {
	return new CellRendererComboDerived(cobject);
    }
};

PluginDisplay::PluginDisplay(gx_engine::GxMachineBase& machine_, Glib::RefPtr<Gdk::Pixbuf> icon, sigc::slot<void, bool, bool> finished_callback_)
    : machine(machine_), pluginlist(), needs_reload(), current_plugin(0), old_state(0), bld(), change_count(0),
      actiongroup(Gtk::ActionGroup::create("ladspa_window")), uimanager(),
      enum_liststore(new EnumListStore), port_liststore(new PortListStore),
      plugin_liststore(new PluginListStore), masteridx_liststore(new MasterIdxListStore),
      on_reordered_conn(), display_type_list(), display_type_list_sr(), output_type_list(),
      finished_callback(finished_callback_), reload_plug(false)
{
    std::vector<std::string> old_not_found;
    machine.load_ladspalist(old_not_found, pluginlist);
    bld = gx_gui::GxBuilder::create_from_file(machine.get_options().get_builder_filepath("ladspaliste.glade"));
    bld->get_toplevel("window1", window);
    bld->find_widget("treeview1", treeview1);
    bld->find_widget("treeview2", treeview2);
    bld->find_widget("treeview3", treeview3);
    bld->find_widget("ladspa_category", ladspa_category);
    bld->find_widget("ladspa_maker", ladspa_maker);
    bld->find_widget("ladspa_uniqueid", ladspa_uniqueid);
    bld->find_widget("search_entry", search_entry);
    bld->find_widget("combobox_mono_stereo", combobox_mono_stereo);
    bld->find_widget("selected_only", selected_only);
    bld->find_widget("changed_only", changed_only);
    bld->find_widget("ladspa_only", ladspa_only);
    bld->find_widget("lv2_only", lv2_only);
    bld->find_widget("show_all", show_all);
    bld->find_widget("details_box", details_box);
    bld->find_widget("plugin_name", plugin_name);
    bld->find_widget("plugin_category", plugin_category);
    bld->find_widget("plugin_quirks", plugin_quirks);
    bld->find_widget("master_slider_idx", master_slider_idx);
    bld->find_widget("master_slider_name", master_slider_name);
    cellrenderer_master = Glib::RefPtr<Gtk::CellRendererText>::cast_dynamic(bld->get_object("cellrenderer_master"));
    cellrenderer_newrow = Glib::RefPtr<Gtk::CellRendererToggle>::cast_dynamic(bld->get_object("cellrenderer_newrow"));
    cellrenderer_caption = Glib::RefPtr<Gtk::CellRendererToggle>::cast_dynamic(bld->get_object("cellrenderer_caption"));
    cellrenderer_active = Glib::RefPtr<Gtk::CellRendererToggle>::cast_dynamic(bld->get_object("cellrenderer_active"));
    cellrenderer_category = Glib::RefPtr<Gtk::CellRendererText>::cast_dynamic(bld->get_object("cellrenderer_category"));
    cellrenderer_quirks = Glib::RefPtr<Gtk::CellRendererText>::cast_dynamic(bld->get_object("cellrenderer_quirks"));

    set_title();
    treeview1->set_name("PresetView");
    treeview2->set_name("PresetView");
    treeview3->set_name("PresetView");
    actiongroup->add(Gtk::Action::create("FileMenuAction",_("_File")));
    save_action = Gtk::Action::create("SaveAction", _("_Ok"));
    actiongroup->add(save_action, sigc::mem_fun(this, &PluginDisplay::on_save));
    apply_action = Gtk::Action::create("ApplyAction", _("_Apply"));
    actiongroup->add(apply_action, sigc::mem_fun(this, &PluginDisplay::on_apply));
    quit_action = Gtk::Action::create("QuitAction", _("_Quit"));
    actiongroup->add(quit_action, sigc::mem_fun(this, &PluginDisplay::on_quit));
    select_all_action = Gtk::Action::create("SelectAllAction", _("_Select All"));
    actiongroup->add(select_all_action, sigc::bind(sigc::mem_fun(this, &PluginDisplay::on_select_all), true));
    select_none_action = Gtk::Action::create("SelectNoneAction", _("Select _None"));
    actiongroup->add(select_none_action, sigc::bind(sigc::mem_fun(this, &PluginDisplay::on_select_all), false));
    actiongroup->add(Gtk::Action::create("ViewMenuAction", _("_View")));
    Glib::RefPtr<Gtk::Action> act = Gtk::Action::create("FindAction", _("_Find"));
    actiongroup->add(act, sigc::mem_fun(this, &PluginDisplay::on_find));

    uimanager = Gtk::UIManager::create();
    uimanager->insert_action_group(actiongroup, 0);
    uimanager->add_ui_from_string(menudef);
    //uimanager->get_widget("/ladspalist");
    //Gtk::HBox *ww; bld->find_widget("menubox", ww); ww->pack_start(*uimanager->get_widget("/ladspalist"));
    window->add_accel_group(uimanager->get_accel_group());

    window->signal_delete_event().connect(sigc::mem_fun(this, &PluginDisplay::on_delete_event));
    bld->find_widget("show_details", show_details);
    show_details->signal_clicked().connect(sigc::mem_fun(this, &PluginDisplay::on_show_details));
    treeview3->get_selection()->set_mode(Gtk::SELECTION_BROWSE);
    treeview3->set_model(enum_liststore);
    auto r = Glib::RefPtr<Gtk::CellRendererText>::cast_dynamic(bld->get_object("cellrenderer_label"));
    r->signal_edited().connect(sigc::mem_fun(this, &PluginDisplay::on_label_edited));
    auto c = Glib::RefPtr<Gtk::TreeViewColumn>::cast_dynamic(bld->get_object("treeviewcolumn_label"));
    c->set_cell_data_func(*r.get(), sigc::mem_fun(this, &PluginDisplay::display_label));
    
    bld->find_widget("dry_wet_button", dry_wet_button);
    dry_wet_button->signal_clicked().connect(sigc::mem_fun(this, &PluginDisplay::on_add_dry_wet_controller));
   // dry_wet_button->set_active(current_plugin->add_wet_dry);
    
    bld->find_widget("stereo_to_mono_button", stereo_to_mono_button);
    stereo_to_mono_button->signal_clicked().connect(sigc::mem_fun(this, &PluginDisplay::on_stereo_to_mono_controller));
   // stereo_to_mono_button->set_active(current_plugin->stereo_to_mono);

    Glib::RefPtr<Gtk::TreeSelection> sel = treeview2->get_selection();
    sel->set_mode(Gtk::SELECTION_BROWSE);
    sel->signal_changed().connect(sigc::mem_fun(this, &PluginDisplay::on_parameter_selection_changed));
    on_reordered_conn = port_liststore->signal_row_deleted().connect(sigc::mem_fun(this, &PluginDisplay::on_reordered));
    treeview2->set_model(port_liststore);

    CellRendererComboDerived *rd;
    bld->find_widget_derived("cellrenderer_type", rd, sigc::ptr_fun(CellRendererComboDerived::create_from_builder));
    rd->signal_edited().connect(sigc::mem_fun(this, &PluginDisplay::on_type_edited));
    c = Glib::RefPtr<Gtk::TreeViewColumn>::cast_dynamic(bld->get_object("treeviewcolumn_type"));
    c->set_cell_data_func(*rd, sigc::mem_fun(this, &PluginDisplay::display_type));

    bld->find_widget_derived("cellrenderer_step", rd, sigc::ptr_fun(CellRendererComboDerived::create_from_builder));
    rd->signal_edited().connect(sigc::mem_fun(this, &PluginDisplay::on_step_edited));
    c = Glib::RefPtr<Gtk::TreeViewColumn>::cast_dynamic(bld->get_object("treeviewcolumn_step"));
    c->set_cell_data_func(*rd, sigc::mem_fun(this, &PluginDisplay::display_step));

    cellrenderer_newrow->signal_toggled().connect(sigc::mem_fun(this, &PluginDisplay::on_newrow_toggled));
    Gtk::Label *label = new Gtk::Label("N");
    label->set_tooltip_text(_("start a new row of controls in the rackbox unit"));
    label->show();
    c = Glib::RefPtr<Gtk::TreeViewColumn>::cast_dynamic(bld->get_object("treeviewcolumn_newrow"));
    c->set_widget(*manage(label));
    c->set_cell_data_func(*cellrenderer_newrow.get(), sigc::mem_fun(this, &PluginDisplay::display_newrow));
    cellrenderer_caption->signal_toggled().connect(sigc::mem_fun(this, &PluginDisplay::on_caption_toggled));
    label = new Gtk::Label("C");
    label->set_tooltip_text(_("display the name as caption above the control"));
    label->show();
    c = Glib::RefPtr<Gtk::TreeViewColumn>::cast_dynamic(bld->get_object("treeviewcolumn_caption"));
    c->set_widget(*manage(label));
    c->set_cell_data_func(*cellrenderer_caption.get(), sigc::mem_fun(this, &PluginDisplay::display_caption));

    r = Glib::RefPtr<Gtk::CellRendererText>::cast_dynamic(bld->get_object("cellrenderer_name"));
    r->signal_edited().connect(sigc::mem_fun(this, &PluginDisplay::on_name_edited));
    c = Glib::RefPtr<Gtk::TreeViewColumn>::cast_dynamic(bld->get_object("treeviewcolumn_name"));
    c->set_cell_data_func(*r.get(), sigc::mem_fun(this, &PluginDisplay::display_name));
    r = Glib::RefPtr<Gtk::CellRendererText>::cast_dynamic(bld->get_object("cellrenderer_dflt"));
    r->signal_edited().connect(sigc::mem_fun(this, &PluginDisplay::on_dflt_edited));
    c = Glib::RefPtr<Gtk::TreeViewColumn>::cast_dynamic(bld->get_object("treeviewcolumn_dflt"));
    c->set_cell_data_func(*r.get(), sigc::mem_fun(this, &PluginDisplay::display_default));
    r = Glib::RefPtr<Gtk::CellRendererText>::cast_dynamic(bld->get_object("cellrenderer_low"));
    r->signal_edited().connect(sigc::mem_fun(this, &PluginDisplay::on_low_edited));
    c = Glib::RefPtr<Gtk::TreeViewColumn>::cast_dynamic(bld->get_object("treeviewcolumn_low"));
    c->set_cell_data_func(*r.get(), sigc::mem_fun(this, &PluginDisplay::display_lower));
    r = Glib::RefPtr<Gtk::CellRendererText>::cast_dynamic(bld->get_object("cellrenderer_up"));
    r->signal_edited().connect(sigc::mem_fun(this, &PluginDisplay::on_up_edited));
    c = Glib::RefPtr<Gtk::TreeViewColumn>::cast_dynamic(bld->get_object("treeviewcolumn_up"));
    c->set_cell_data_func(*r.get(), sigc::mem_fun(this, &PluginDisplay::display_upper));
    r = Glib::RefPtr<Gtk::CellRendererText>::cast_dynamic(bld->get_object("cellrenderer_idx"));
    c = Glib::RefPtr<Gtk::TreeViewColumn>::cast_dynamic(bld->get_object("treeviewcolumn_idx"));
    c->set_cell_data_func(*r.get(), sigc::mem_fun(this, &PluginDisplay::display_idx));

    c = Glib::RefPtr<Gtk::TreeViewColumn>::cast_dynamic(bld->get_object("treeviewcolumn_SR"));
    label = new Gtk::Label("SR");
    label->set_tooltip_text(_("marked rows: range depends on samplerate; using 44100 as fixed value"));
    label->show();
    c->set_widget(*manage(label));
    auto t = Glib::RefPtr<Gtk::CellRendererToggle>::cast_dynamic(bld->get_object("cellrenderer_SR"));
    c->set_cell_data_func(*t.get(), sigc::mem_fun(this, &PluginDisplay::display_SR));

    Gtk::TreeModelColumnRecord recdef;
    Gtk::TreeModelColumn<Glib::ustring> strcol;
    Gtk::TreeModelColumn<DisplayType> intcol;
    recdef.add(strcol);
    recdef.add(intcol);
    display_type_list = Gtk::ListStore::create(recdef);
    append_displaytype(display_type_list, tp_scale);
    append_displaytype(display_type_list, tp_scale_log);
    append_displaytype(display_type_list, tp_enabled);
    append_displaytype(display_type_list, tp_toggle);
    append_displaytype(display_type_list, tp_int);
    append_displaytype(display_type_list, tp_enum);
    append_displaytype(display_type_list, tp_none);
    display_type_list_sr = Gtk::ListStore::create(recdef);
    append_displaytype(display_type_list_sr, tp_scale);
    append_displaytype(display_type_list_sr, tp_scale_log);
    append_displaytype(display_type_list_sr, tp_none);
    output_type_list = Gtk::ListStore::create(recdef);
    append_displaytype(output_type_list, tp_display);
    append_displaytype(output_type_list, tp_display_toggle);
    append_displaytype(output_type_list, tp_none);

    treeview1->signal_row_activated().connect(sigc::mem_fun(this, &PluginDisplay::on_row_activated));
    treeview1->set_search_equal_func(sigc::mem_fun(this,&PluginDisplay::search_equal));
    Gtk::Entry *e;
    bld->find_widget("search_entry", e);
    e->signal_activate().connect(sigc::mem_fun(this, &PluginDisplay::on_search_entry_activate));
    treeview1->set_search_entry(*e);
    sel = treeview1->get_selection();
    sel->set_mode(Gtk::SELECTION_BROWSE);
    sel->signal_changed().connect(sigc::mem_fun(this, &PluginDisplay::selection_changed));
    treeview1->set_model(plugin_liststore);
    cellrenderer_active->signal_toggled().connect(sigc::mem_fun(this, &PluginDisplay::on_active_toggled));
    r = Glib::RefPtr<Gtk::CellRendererText>::cast_dynamic(bld->get_object("cellrenderer_ladspa"));
    c = Glib::RefPtr<Gtk::TreeViewColumn>::cast_dynamic(bld->get_object("treeviewcolumn_ladspa"));
    c->set_cell_data_func(*r.get(), sigc::mem_fun(this, &PluginDisplay::display_ladspa));

    Gtk::ComboBox *cb;
    bld->find_widget("plugin_category", cb);
    cb->set_cell_data_func(*cellrenderer_category.get(), sigc::mem_fun(this, &PluginDisplay::display_category));
    bld->find_widget("plugin_quirks", cb);
    cb->set_cell_data_func(*cellrenderer_quirks.get(), sigc::mem_fun(this, &PluginDisplay::display_quirks));

    master_slider_idx->set_cell_data_func(*cellrenderer_master.get(), sigc::mem_fun(this, &PluginDisplay::display_master_idx));
    master_slider_idx->signal_changed().connect(sigc::mem_fun(this, &PluginDisplay::set_master_text));

    selected_only->signal_toggled().connect(sigc::bind(sigc::mem_fun(this, &PluginDisplay::on_view_changed), selected_only));
    changed_only->signal_toggled().connect(sigc::bind(sigc::mem_fun(this, &PluginDisplay::on_view_changed), changed_only));
    ladspa_only->signal_toggled().connect(sigc::bind(sigc::mem_fun(this, &PluginDisplay::on_view_changed), ladspa_only));
    lv2_only->signal_toggled().connect(sigc::bind(sigc::mem_fun(this, &PluginDisplay::on_view_changed), lv2_only));
    show_all->signal_toggled().connect(sigc::bind(sigc::mem_fun(this, &PluginDisplay::on_view_changed), show_all));

    bld->find_widget("combobox_mono_stereo", cb);
    cb->signal_changed().connect(sigc::mem_fun(this, &PluginDisplay::on_mono_stereo_changed));
    cb->set_active(0);
    Gtk::Button *b;
    bld->find_widget("reset_changes", b);
    b->signal_clicked().connect(sigc::mem_fun(this, &PluginDisplay::on_delete_changes));

    bld->find_widget("master_slider_idx", cb);
    cb->set_model(masteridx_liststore);

    bld->find_widget("button_cancel", b);
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(b->gobj()), actiongroup->get_action("QuitAction")->gobj());
    bld->find_widget("button_apply", b);
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(b->gobj()), actiongroup->get_action("ApplyAction")->gobj());
    bld->find_widget("button_save", b);
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(b->gobj()), actiongroup->get_action("SaveAction")->gobj());
    bld->find_widget("select_all", b);
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(b->gobj()), actiongroup->get_action("SelectAllAction")->gobj());
    bld->find_widget("select_none", b);
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(b->gobj()), actiongroup->get_action("SelectNoneAction")->gobj());

    window->set_icon(icon);
    window->show();
}

PluginDisplay::~PluginDisplay() {
    delete window;
}

static void split(std::vector<ustring>& strvec, const ustring& str) {
    size_t start = 0, np = ustring::npos;
    while (true) {
        size_t end = str.find_first_of(' ', start);
	size_t len = (end == np) ? np : end - start;
	if (len > 0) {
	    strvec.push_back(str.substr(start, len).lowercase());
	}
	if (end == np) {
	    return;
	}
        start = end + 1;
    }
}

bool PluginDisplay::search_equal(const Glib::RefPtr<Gtk::TreeModel>& model, int column, const ustring& key, const Gtk::TreeIter& iter) {
    PluginDesc *p = iter->get_value(plugin_liststore->col.pdesc);
    ustring txt(gx_system::to_string(p->UniqueID));
    if (txt.compare(0, ustring::npos, key, 0, key.size()) == 0) {
        return false;
    }
    txt = iter->get_value(plugin_liststore->col.name).lowercase();
    std::vector<ustring> keyvec;
    split(keyvec, key);
    for (std::vector<ustring>::iterator i = keyvec.begin(); i != keyvec.end(); ++i) {
        if (txt.find(*i) == ustring::npos) {
            return true;
	}
    }
    return false;
}

void PluginDisplay::display_step(Gtk::CellRenderer *cell, const Gtk::TreeIter& it) {
    PortDesc *q = it->get_value(port_liststore->col.port);
    DisplayType tp = q->get_tp();
    cell->property_visible().set_value(tp == tp_scale || tp == tp_scale_log);
    if (q->step != stp_normal) {
        dynamic_cast<Gtk::CellRendererText*>(cell)->property_foreground().set_value("red");
    } else {
        dynamic_cast<Gtk::CellRendererText*>(cell)->property_foreground_set().set_value(false);
    }
}

void PluginDisplay::display_ladspa(Gtk::CellRenderer *cell, const Gtk::TreeIter& iter) {
    PluginDesc *p = iter->get_value(plugin_liststore->col.pdesc);
    if (p->has_settings) {
        dynamic_cast<Gtk::CellRendererText*>(cell)->property_foreground().set_value("red");
    } else {
        dynamic_cast<Gtk::CellRendererText*>(cell)->property_foreground_set().set_value(false);
    }
}

void PluginDisplay::display_label(Gtk::CellRenderer *cell, const Gtk::TreeIter& it) {
    PortDesc *q = it->get_value(enum_liststore->col.port);
    if (q->enumkey_changed(int(it->get_value(enum_liststore->col.value)))) {
	dynamic_cast<Gtk::CellRendererText*>(cell)->property_foreground().set_value("red");
    } else {
        dynamic_cast<Gtk::CellRendererText*>(cell)->property_foreground_set().set_value(false);
    }
}

void PluginDisplay::display_idx(Gtk::CellRenderer *cell, const Gtk::TreeIter& it) {
    PortDesc *q = it->get_value(port_liststore->col.port);
    if (int(port_liststore->get_path(it)[0]) != q->get_pos()) {
	dynamic_cast<Gtk::CellRendererText*>(cell)->property_foreground().set_value("red");
    } else {
        dynamic_cast<Gtk::CellRendererText*>(cell)->property_foreground_set().set_value(false);
    }
}

void PluginDisplay::display_name(Gtk::CellRenderer *cell, const Gtk::TreeIter& it) {
    PortDesc *q = it->get_value(port_liststore->col.port);
    if (q->is_set(ChangeableValues::name_set)) {
	dynamic_cast<Gtk::CellRendererText*>(cell)->property_foreground().set_value("red");
    } else {
        dynamic_cast<Gtk::CellRendererText*>(cell)->property_foreground_set().set_value(false);
    }
}

void PluginDisplay::display_default(Gtk::CellRenderer *cell, const Gtk::TreeIter& it) {
    PortDesc *q = it->get_value(port_liststore->col.port);
    Gtk::CellRendererText *tcell = dynamic_cast<Gtk::CellRendererText*>(cell);
    tcell->property_foreground_set().set_value(false);
    tcell->property_background_set().set_value(false);
    DisplayType tp = q->get_tp();
    if (tp == tp_display || tp == tp_display_toggle || tp == tp_none) {
        cell->property_visible().set_value(false);
        return;
    }
    cell->property_visible().set_value(true);
    if (q->is_set(ChangeableValues::dflt_set)) {
        tcell->property_foreground().set_value("red");
    } else if (q->fake_dflt) {
        tcell->property_background().set_value("grey");
    }
}

void PluginDisplay::display_lower(Gtk::CellRenderer *cell, const Gtk::TreeIter& it) {
    PortDesc *q = it->get_value(port_liststore->col.port);
    Gtk::CellRendererText *tcell = dynamic_cast<Gtk::CellRendererText*>(cell);
    tcell->property_foreground_set().set_value(false);
    tcell->property_background_set().set_value(false);
    DisplayType tp = q->get_tp();
    if (tp == tp_enabled || tp == tp_toggle || tp == tp_display_toggle || tp == tp_none) {
        cell->property_visible().set_value(false);
        return;
    }
    cell->property_visible().set_value(true);
    if (q->is_set(ChangeableValues::low_set)) {
        tcell->property_foreground().set_value("red");
    } else if (q->fake_low) {
        tcell->property_background().set_value("grey");
    }
}

void PluginDisplay::display_upper(Gtk::CellRenderer *cell, const Gtk::TreeIter& it) {
    PortDesc *q = it->get_value(port_liststore->col.port);
    Gtk::CellRendererText *tcell = dynamic_cast<Gtk::CellRendererText*>(cell);
    tcell->property_foreground_set().set_value(false);
    tcell->property_background_set().set_value(false);
    DisplayType tp = q->get_tp();
    if (tp == tp_enabled ||tp == tp_toggle ||  tp == tp_display_toggle || tp == tp_none) {
        cell->property_visible().set_value(false);
        return;
    }
    cell->property_visible().set_value(true);
    if (q->is_set(ChangeableValues::up_set)) {
        tcell->property_foreground().set_value("red");
    } else if (q->fake_up) {
        tcell->property_background().set_value("grey");
    }
}

void PluginDisplay::display_SR(Gtk::CellRenderer *cell, const Gtk::TreeIter& it) {
    cell->property_visible().set_value(it->get_value(port_liststore->col.port)->has_sr);
}

void PluginDisplay::display_type(Gtk::CellRenderer *cell, const Gtk::TreeIter& it) {
    PortDesc *q = it->get_value(port_liststore->col.port);
    Gtk::CellRendererText *tcell = dynamic_cast<Gtk::CellRendererText*>(cell);
    if (q->is_set(ChangeableValues::tp_set)) {
        tcell->property_foreground().set_value("red");
    } else {
        tcell->property_foreground_set().set_value(false);
    }
}

void PluginDisplay::display_newrow(Gtk::CellRenderer *cell, const Gtk::TreeIter& it) {
    PortDesc *q = it->get_value(port_liststore->col.port);
    if (q->is_set(ChangeableValues::newrow_set)) {
        cell->property_cell_background().set_value("red");
    } else {
        cell->property_cell_background_set().set_value(false);
    }
}

void PluginDisplay::display_caption(Gtk::CellRenderer *cell, const Gtk::TreeIter& it) {
    PortDesc *q = it->get_value(port_liststore->col.port);
    if (!q->has_caption) {
        cell->property_cell_background().set_value("red");
    } else {
        cell->property_cell_background_set().set_value(false);
    }
}

void PluginDisplay::on_delete_changes() {
    if (!current_plugin) {
	return;
    }
    current_plugin->reset();
    int changed = current_plugin->check_changed();
    int change_diff = changed - old_state;
    if (change_diff) {
	change_count += change_diff;
	set_title();
    }
    if (!changed) {
	current_plugin->clear_old();
    }
    current_plugin = 0;
    selection_changed();
}

void PluginDisplay::on_search_entry_activate() {
    Gtk::TreeIter it = treeview1->get_selection()->get_selected();
    if (it) {
	bool v = !it->get_value(plugin_liststore->col.active);
	it->set_value(plugin_liststore->col.active, v);
	change_count += it->get_value(plugin_liststore->col.pdesc)->set_active(v);
	set_title();
    }
}

bool PluginDisplay::check_for_changes() {
    PluginDesc *cur = current_plugin;
    save_current();
    bool ret = false;
    for (std::vector<PluginDesc*>::iterator p = pluginlist.begin(); p != pluginlist.end(); ++p) {
	if ((*p)->active != (*p)->active_set) {
	    ret = true;
	    break;
	}
	if ((*p)->old) {
	    ret = true;
	    break;
	}
    }
    if (cur) {
	set_old_state(cur);
    }
    return ret;
}

int PluginDisplay::ask_discard() {
    Gtk::MessageDialog d(*window, _("Discard changes to plugin definitions?"), false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_YES_NO, true);
    return d.run();
}

bool PluginDisplay::check_exit() {
    if (check_for_changes()) {
	int ret = ask_discard();
	if (ret != Gtk::RESPONSE_YES) {
	    return false;
	}
    }
    return true;
}

bool PluginDisplay::on_delete_event(GdkEventAny *) {
    return !check_exit();
}

void PluginDisplay::on_quit() {
    if (check_exit()) {
	finished_callback(false, true);
    }
}

void PluginDisplay::on_find() {
    search_entry->grab_focus();
}

void PluginDisplay::display_quirks(const Gtk::TreeIter& it) {
    if (!current_plugin) {
	cellrenderer_quirks->property_foreground_set().set_value(false);
    } else {
	int quirks;
	it->get_value(1, quirks);
	if (quirks == current_plugin->quirks_default) {
	    cellrenderer_quirks->property_foreground_set().set_value(false);
	} else {
	    cellrenderer_quirks->property_foreground().set_value("red");
	}
    }
}

void PluginDisplay::display_category(const Gtk::TreeIter& it) {
    if (!current_plugin) {
	cellrenderer_category->property_foreground_set().set_value(false);
    } else {
	ustring cat;
	it->get_value(0, cat);
	if (cat == current_plugin->deduced_category) {
	    cellrenderer_category->property_foreground_set().set_value(false);
	} else {
	    cellrenderer_category->property_foreground().set_value("red");
	}
    }
}

void PluginDisplay::load() {
    int a = combobox_mono_stereo->get_model()->get_path(combobox_mono_stereo->get_active())[0];
    bool s = selected_only->get_active();
    bool c = changed_only->get_active();
    bool d = ladspa_only->get_active();
    bool e = lv2_only->get_active();
    plugin_liststore->clear();
    for (std::vector<PluginDesc*>::iterator v = pluginlist.begin(); v != pluginlist.end(); ++v) {
	if (s && !(*v)->active) {
	    continue;
	}
	else if (c && !(*v)->has_settings) {
	    continue;
	}
	else if (d && (*v)->is_lv2) {
	    continue;
	}
 	else if (e && !(*v)->is_lv2) {
	    continue;
	}
	if ((a == 1 && (*v)->tp != 0) || (a == 2 && (*v)->tp != 1)) {
	    continue;
	}

	Gtk::TreeIter it = plugin_liststore->append();
	it->set_value(plugin_liststore->col.name, ustring((*v)->Name));
	it->set_value(plugin_liststore->col.active, (*v)->active);
	it->set_value(plugin_liststore->col.pdesc, *v);
    }
}

void PluginDisplay::on_save() {
    finished_callback(do_save(), true);
}

void PluginDisplay::on_apply() {
    if (do_save()) {
	finished_callback(true, false);
    }
    reload_plug = false;
    needs_reload.clear();
    selection_changed();
}

void PluginDisplay::on_stereo_to_mono() {
    for (std::vector<PluginDesc*>::iterator p = needs_reload.begin(); p != needs_reload.end(); ++p) {
        (*p)->active_set = (*p)->active = false;
    }
    machine.save_ladspalist(pluginlist);
    finished_callback(true, false);
    reload_plug = false;
    for (std::vector<PluginDesc*>::iterator p = needs_reload.begin(); p != needs_reload.end(); ++p) {
        (*p)->active_set = (*p)->active = true;
    }
    needs_reload.clear();
}

bool PluginDisplay::do_save() {
    bool changed = check_for_changes();
    if (changed && reload_plug) on_stereo_to_mono();
    machine.save_ladspalist(pluginlist);
    for (std::vector<PluginDesc*>::iterator p = pluginlist.begin(); p != pluginlist.end(); ++p) {
	(*p)->active_set = (*p)->active;
	(*p)->clear_old();
    }
    old_state = 0;
    change_count = 0;
    set_title();
    current_plugin = 0;
    return changed;
}

void PluginDisplay::on_select_all(bool v) {
    int d = 0;
    Gtk::TreeNodeChildren ch = plugin_liststore->children();
    for (Gtk::TreeIter it = ch.begin(); it != ch.end(); ++it) {
	it->set_value(plugin_liststore->col.active, v);
	d += it->get_value(plugin_liststore->col.pdesc)->set_active(v);
    }
    if (d) {
	change_count += d;
	set_title();
    }
}

void PluginDisplay::on_show_details() {
    details_box->set_visible(show_details->get_active());
    int w, h;
    window->get_size(w, h);
    window->resize(1, h);
}

void PluginDisplay::on_add_dry_wet_controller() {
    if (!current_plugin) {
	return;
    }
    current_plugin->set_add_wet_dry_controller(dry_wet_button->get_active()); 
}

void PluginDisplay::on_stereo_to_mono_controller() {
    if (!current_plugin) {
	return;
    }
    current_plugin->set_stereo_to_mono(stereo_to_mono_button->get_active());
    reload_plug = true;
    needs_reload.push_back(current_plugin);
}

void PluginDisplay::on_row_activated(const Gtk::TreePath& path, Gtk::TreeViewColumn* column) {
    show_details->clicked();
}

void PluginDisplay::on_mono_stereo_changed() {
    load();
}

void PluginDisplay::on_view_changed(const Gtk::ToggleButton *b) {
    if (b->get_active()) {
	load();
    }
}

void PluginDisplay::save_current() {
    if (!current_plugin) {
	return;
    }
    ustring s = plugin_name->get_text();
    gx_system::strip(s);
    if (s.empty()) {
	current_plugin->shortname = current_plugin->Name;
    } else {
	current_plugin->shortname = s;
    }
    plugin_category->get_active()->get_value(1, current_plugin->category);
    plugin_quirks->get_active()->get_value(1, current_plugin->quirks);
    Gtk::TreeIter it = master_slider_idx->get_active();
    if (it) {
	it->get_value(0, current_plugin->MasterIdx);
    } else {
	current_plugin->MasterIdx = -1;
    }
    if (current_plugin->MasterIdx < 0) {
	current_plugin->MasterLabel = "";
    } else {
	current_plugin->MasterLabel = master_slider_name->get_text();
    }
    current_plugin->check_has_settings();
    int changed = current_plugin->check_changed();
    int change_diff = changed - old_state;
    if (change_diff) {
	change_count += change_diff;
	set_title();
    }
    if (!changed) {
	current_plugin->clear_old();
    }
    current_plugin = 0;
}

void PluginDisplay::set_title() {
    ustring t = _("Select LADSPA/LV2 plugins for Guitarix");
    if (change_count) {
	window->set_title(t + _(" (*changed*)"));
    } else {
	window->set_title(t);
    }
}

void PluginDisplay::set_old_state(PluginDesc *p) {
    current_plugin = p;
    old_state = (p->old != 0);
    if (!p->old) {
	p->set_old();
    }
}

void PluginDisplay::selection_changed() {
    Gtk::TreeIter it = treeview1->get_selection()->get_selected();
    PluginDesc *p = 0;
    if (it) {
	p = it->get_value(plugin_liststore->col.pdesc);
	if (current_plugin == p) {
	    return;
	}
    }
    save_current();
    on_reordered_conn.block();
    port_liststore->clear();
    on_reordered_conn.unblock();
    ladspa_category->set_text("");
    ladspa_maker->set_text("");
    ladspa_uniqueid->set_text("");
    plugin_name->set_text("");
    plugin_category->set_active(-1);
    plugin_quirks->set_active(-1);
    if (!p) {
	return;
    }
    set_old_state(p);
    if (p->shortname != p->Name) {
	plugin_name->override_color(Gdk::RGBA("red"), Gtk::STATE_FLAG_NORMAL);
    } else {
	gtk_widget_override_color(GTK_WIDGET(plugin_name->gobj()), GTK_STATE_FLAG_NORMAL, nullptr);
    }
    plugin_name->set_text(p->shortname);
    Gtk::TreeNodeChildren ch = plugin_category->get_model()->children();
    int i = 0;
    for (it = ch.begin(); it != ch.end(); ++it, ++i) {
	ustring cat;
	it->get_value(1, cat);
	if (cat == p->category) {
	    plugin_category->set_active(i);
	    break;
	}
    }
    ch = plugin_quirks->get_model()->children();
    for (i = 0, it = ch.begin(); it != ch.end(); ++it, ++i) {
	int quirks;
	it->get_value(1, quirks);
	if (quirks == p->quirks) {
	    plugin_quirks->set_active(i);
	    break;
	}
    }
    Glib::RefPtr<Gtk::ListStore> ls_master = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(master_slider_idx->get_model());
    ls_master->clear();
    it = ls_master->append();
    i = -1;
    it->set_value(0, i);
    ustring ml("");
    for (unsigned int i = 0; i < p->ctrl_ports.size(); ++i) {
	it = ls_master->append();
	it->set_value(0, int(i));
	if (p->ctrl_ports[i]->pos == p->MasterIdx) {
	    ml = p->ctrl_ports[i]->factory.get_name();
	}
    }
    master_slider_idx->set_active(p->MasterIdx+1);
    gtk_widget_override_color(GTK_WIDGET(master_slider_name->gobj()), GTK_STATE_FLAG_NORMAL, nullptr);
    if (!p->MasterLabel.empty()) {
	master_slider_name->set_text(p->MasterLabel);
	if (p->MasterLabel != ml) {
	    master_slider_name->override_color(Gdk::RGBA("red"), Gtk::STATE_FLAG_NORMAL);
	}
    }
    dry_wet_button->set_active(current_plugin->add_wet_dry);
    stereo_to_mono_button->set_active(current_plugin->stereo_to_mono);
    stereo_to_mono_button->set_sensitive(p->tp);
    ladspa_category->set_text(p->ladspa_category);
    ladspa_maker->set_text(p->Maker);
    if (p->is_lv2) {
	ladspa_uniqueid->set_text(ustring::compose("LV2: %1", p->path));
    } else {
	ladspa_uniqueid->set_text(ustring::compose("%1: %2[%3]", p->UniqueID, p->path, p->index));
    }
    for (unsigned int i = 0; i < p->ctrl_ports.size(); ++i) {
	PortDesc *q = p->ctrl_ports[i];
	Glib::RefPtr<Gtk::ListStore> tls;
	if (q->is_output) {
	    tls = output_type_list;
	} else if (q->has_sr) {
	    tls = display_type_list_sr;
	} else {
	    tls = display_type_list;
	}
	float dflt = q->get_dflt();
	float low = q->get_low();
	float up = q->get_up();
	if (q->has_sr && !q->use_sr) {
	    if (q->factory.is_set(ChangeableValues::dflt_set)) {
		dflt *= q->SR;
	    }
	    if (q->factory.is_set(ChangeableValues::low_set)) {
		low *= q->SR;
	    }
	    if (q->factory.is_set(ChangeableValues::up_set)) {
		up *= q->SR;
	    }
	}
	it = port_liststore->append();
	it->set_value(port_liststore->col.pos, q->pos);
	it->set_value(port_liststore->col.name, q->get_name());
	it->set_value(port_liststore->col.dflt, ustring::format(dflt));
	it->set_value(port_liststore->col.low, ustring::format(low));
	it->set_value(port_liststore->col.up, ustring::format(up));
	it->set_value(port_liststore->col.step, ustring(step_type_names[q->step]));
	it->set_value(port_liststore->col.display, ustring(display_type_names[q->get_tp()]));
	it->set_value(port_liststore->col.display_types, tls);
	it->set_value(port_liststore->col.port, q);
	it->set_value(port_liststore->col.newrow, q->get_newrow());
	it->set_value(port_liststore->col.use_sr, q->has_sr && !q->use_sr);
	it->set_value(port_liststore->col.has_caption, q->has_caption);
    }
}

void PluginDisplay::display_master_idx(const Gtk::TreeIter& it) {
    int i;
    it->get_value(0, i);
    if (i < 0) {
	cellrenderer_master->property_text().set_value("--");
	cellrenderer_master->property_foreground_set().set_value(false);
    } else {
	cellrenderer_master->property_foreground().set_value("red");
    }
}

void PluginDisplay::set_master_text() {
    Gtk::TreeIter it = master_slider_idx->get_active();
    if (!it) {
	master_slider_name->set_text("");
	master_slider_name->set_editable(false);
	return;
    }
    int idx;
    it->get_value(0, idx);
    if (idx < 0) {
	master_slider_name->set_text("");
	master_slider_name->set_editable(false);
    } else {
	for (std::vector<PortDesc*>::iterator q = current_plugin->ctrl_ports.begin(); q != current_plugin->ctrl_ports.end(); ++q) {
	    if ((*q)->pos == idx) {
		master_slider_name->set_text((*q)->factory.get_name());
		break;
	    }
	}
	master_slider_name->set_editable(true);
    }
}

void PluginDisplay::on_parameter_selection_changed() {
    Gtk::TreeIter it = treeview2->get_selection()->get_selected();
    enum_liststore->clear();
    if (it) {
	PortDesc *q = it->get_value(port_liststore->col.port);
	if (q->get_tp() == tp_enum) {
	    int up = int(q->get_up());
	    for (int idx = int(q->get_low()); idx <= up; ++idx) {
		it = enum_liststore->append();
		it->set_value(enum_liststore->col.value, idx);
		it->set_value(enum_liststore->col.label, q->get_enum(idx));
		it->set_value(enum_liststore->col.port, q);
	    }
	}
    }
}

void PluginDisplay::on_reordered(const Gtk::TreePath& path) {
    assert(current_plugin);
    std::map<int,int> d;
    for (unsigned int i = 0; i < current_plugin->ctrl_ports.size(); ++i) {
	d[current_plugin->ctrl_ports[i]->pos] = i;
    }
    std::vector<PortDesc*> l;
    Gtk::TreeNodeChildren ch = port_liststore->children();
    for (Gtk::TreeIter it = ch.begin(); it != ch.end(); ++it) {
	l.push_back(current_plugin->ctrl_ports[d[it->get_value(port_liststore->col.pos)]]);
    }
    current_plugin->ctrl_ports = l;
}

void PluginDisplay::on_type_edited(const ustring& path, const ustring& newtext) {
    Gtk::TreeIter it = port_liststore->get_iter(path);
    PortDesc *q = it->get_value(port_liststore->col.port);
    DisplayType tp_old = q->user.get_tp();
    DisplayType tp = tp_scale;
    for (unsigned int i = 0; i < sizeof(display_type_names)/sizeof(display_type_names[0]); i++) {
	if (newtext == display_type_names[i]) {
	    tp = static_cast<DisplayType>(i);
	    break;
	}
    }
    q->set_tp(tp);
    if (tp != tp_old) {
	if (tp == tp_scale_log) {
	    if (q->get_low() <= 0) {
		q->set_low(1e-7);
	    }
	    if (q->get_up() <= q->get_low()) {
		q->set_up(q->get_low()*1000);
	    }
	    float dflt = q->get_dflt();
	    if (!(q->get_low() <= dflt && dflt <= q->get_up())) {
		q->set_dflt(q->get_low());
	    }
	} else if (tp == tp_enabled) {
	    q->set_dflt(int(q->get_dflt() != 0));
	    q->set_low(0);
	    q->set_up(1);
	} else if (tp == tp_toggle) {
	    q->set_dflt(int(q->get_dflt() != 0));
	    q->set_low(0);
	    q->set_up(1);
	} else if (tp == tp_enum || tp == tp_int) {
	    q->set_dflt(round(q->get_dflt()));
	    q->set_low(round(q->get_low()));
	    q->set_up(round(q->get_up()));
	}
	float dflt = q->get_dflt();
	float low = q->get_low();
	float up = q->get_up();
	if (q->has_sr && !q->use_sr) {
	    dflt *= q->SR;
	    low *= q->SR;
	    up *= q->SR;
	}
	it->set_value(port_liststore->col.dflt, ustring::format(dflt));
	it->set_value(port_liststore->col.low, ustring::format(low));
	it->set_value(port_liststore->col.up, ustring::format(up));
    }
    it->set_value(port_liststore->col.display, newtext);
    on_parameter_selection_changed();
}

void PluginDisplay::on_step_edited(const ustring& path, const ustring& newtext) {
    Gtk::TreeIter it = port_liststore->get_iter(path);
    step_mode m = stp_normal;
    for (unsigned int i = 0; i < sizeof(step_type_names)/sizeof(step_type_names[0]); ++i) {
	if (step_type_names[i] == newtext) {
	    m = static_cast<step_mode>(i);
	    break;
	}
    }
    it->get_value(port_liststore->col.port)->step = m;
    it->set_value(port_liststore->col.step, newtext);
}

void PluginDisplay::on_label_edited(const ustring& path, const ustring& newtext) {
    Gtk::TreeIter it = enum_liststore->get_iter(path);
    PortDesc *q = it->get_value(enum_liststore->col.port);
    ustring text(newtext);
    gx_system::strip(text);
    int idx = it->get_value(enum_liststore->col.value);
    std::map<int, ustring>::iterator i = q->factory.find_enum(idx);
    if (text.empty() || (i != q->factory.enum_end() && i->second == text)) {
	q->user.erase_enum(idx);
	text = "";
    }
    if (text.empty()) {
	std::map<int, ustring>::iterator i = q->factory.find_enum(idx);
	if (i == q->factory.enum_end()) {
	    text = ustring::format(idx);
	} else {
	    text = i->second;
	}
    } else {
	q->user.set_enumvalue(idx, text);
    }
    it->set_value(enum_liststore->col.label, text);
}

void PluginDisplay::on_name_edited(const ustring& path, const ustring& newtext) {
    Gtk::TreeIter it = port_liststore->get_iter(path);
    PortDesc *q = it->get_value(port_liststore->col.port);
    ustring text(newtext);
    gx_system::strip(text);
    if (text.empty() || q->factory.get_name() == text) {
	q->user.unset(ChangeableValues::name_set);
    } else {
	q->user.set_name(text);
    }
    it->set_value(port_liststore->col.name, q->get_name());
}

void PluginDisplay::on_dflt_edited(const ustring& path, const ustring& newtext) {
    Gtk::TreeIter it = port_liststore->get_iter(path);
    PortDesc *q = it->get_value(port_liststore->col.port);
    ustring text(newtext);
    gx_system::strip(text);
    float val;
    if (text.empty()) {
	q->user.unset(ChangeableValues::dflt_set);
	val = q->factory.get_dflt();
	if (val < q->get_low()) {
	    q->set_low(val);
	}
	if (val > q->get_up()) {
	    q->set_up(val);
	}
	if (q->has_sr && !q->use_sr) {
	    val *= q->SR;
	}
    } else {
	char *p;
	val = strtod(text.c_str(), &p);
	if (p != text.c_str() + text.size()) {
	    return;
	}
	float val2;
	if (q->has_sr && !q->use_sr) {
	    val2 = val / q->SR;
	} else {
	    val2 = val;
	}
	if (!(q->get_low() <= val2 && val2 <= q->get_up())) {
	    return;
	}
	q->set_dflt(val2);
    }
    it->set_value(port_liststore->col.dflt, ustring::format(val));
}

void PluginDisplay::on_low_edited(const ustring& path, const ustring& newtext) {
    Gtk::TreeIter it = port_liststore->get_iter(path);
    PortDesc *q = it->get_value(port_liststore->col.port);
    ustring text(newtext);
    gx_system::strip(text);
    float val;
    if (text.empty()) {
	q->user.unset(ChangeableValues::low_set);
	val = q->factory.get_low();
	if (q->get_dflt() < val) {
	    q->set_dflt(val);
	}
	if (q->get_up() < val) {
	    q->set_up(min(q->get_up(),val+1));
	}
	if (q->has_sr && !q->use_sr) {
	    val *= q->SR;
	}
    } else {
	char *p;
	val = strtod(text.c_str(), &p);
	if (p != text.c_str() + text.size()) {
	    return;
	}
	float val2;
	if (q->has_sr && !q->use_sr) {
	    val2 = val/q->SR;
	} else {
	    val2 = val;
	}
	if (!(val2 < q->get_up())) {
	    return;
	}
	if (q->get_dflt() < val2) {
	    q->user.set_dflt(val2);
	}
	it->set_value(port_liststore->col.dflt, ustring::format(q->get_dflt()));
	q->set_low(val2);
	if (q->get_tp() == tp_enum) {
	    on_parameter_selection_changed();
	}
    }
    it->set_value(port_liststore->col.low, ustring::format(val));
}

void PluginDisplay::on_up_edited(const ustring& path, const ustring& newtext) {
    Gtk::TreeIter it = port_liststore->get_iter(path);
    PortDesc *q = it->get_value(port_liststore->col.port);
    ustring text(newtext);
    gx_system::strip(text);
    float val;
    if (text.empty()) {
	q->user.unset(ChangeableValues::up_set);
	val = q->factory.get_up();
	if (q->get_dflt() > val) {
	    q->set_dflt(val);
	}
	if (q->get_low() > val) {
	    q->set_low(max(q->get_low(),val-1));
	}
	if (q->has_sr && !q->use_sr) {
	    val *= q->SR;
	}
    } else {
	char *p;
	val = strtod(text.c_str(), &p);
	if (p != text.c_str() + text.size()) {
	    return;
	}
	float val2;
	if (q->has_sr && !q->use_sr) {
	    val2 = val/q->SR;
	} else {
	    val2 = val;
	}
	if (!(val2 > q->get_low())) {
	    return;
	}
	if (q->get_dflt() > val2) {
	    q->user.set_dflt(val2);
	}
	it->set_value(port_liststore->col.dflt, ustring::format(q->get_dflt()));
	q->set_up(val2);
	if (q->get_tp() == tp_enum) {
	    on_parameter_selection_changed();
	}
    }
    it->set_value(port_liststore->col.up, ustring::format(val));
}

void PluginDisplay::on_newrow_toggled(const ustring& path) {
    Gtk::TreeIter it = port_liststore->get_iter(path);
    PortDesc *q = it->get_value(port_liststore->col.port);
    bool s = !cellrenderer_newrow->get_active();
    it->set_value(port_liststore->col.newrow, s);
    if (s == q->factory.get_newrow()) {
	q->user.unset(ChangeableValues::newrow_set);
    } else {
	q->user.set_newrow(s);
    }
}

void PluginDisplay::on_caption_toggled(const ustring& path) {
    Gtk::TreeIter it = port_liststore->get_iter(path);
    PortDesc *q = it->get_value(port_liststore->col.port);
    bool s = !cellrenderer_caption->get_active();
    it->set_value(port_liststore->col.has_caption, s);
    q->has_caption = s;
}

void PluginDisplay::on_active_toggled(const ustring& path) {
    Gtk::TreeIter it = plugin_liststore->get_iter(path);
    bool s = !cellrenderer_active->get_active();
    it->set_value(plugin_liststore->col.active, s);
    change_count += it->get_value(plugin_liststore->col.pdesc)->set_active(s);
    set_title();
}

} // namespace ladspa
