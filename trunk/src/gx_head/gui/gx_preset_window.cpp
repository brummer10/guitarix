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
 *
 * ----------------------------------------------------------------------------
 */

#include <guitarix.h>

void child_set_property(Gtk::Container& container, Gtk::Widget& child, const char *property_name, bool value) {
    GValue v = {0};
    g_value_init(&v, G_TYPE_BOOLEAN);
    g_value_set_boolean(&v, value);
    gtk_container_child_set_property(container.gobj(), child.gobj(), property_name, &v);
}

/****************************************************************
 ** class PresetWindow
 */

PresetStore::PresetStore(): Gtk::ListStore(PresetModelColumns())
{}

bool PresetStore::row_draggable_vfunc(const TreeModel::Path& path) const {
    Gtk::TreeModel::const_iterator i = const_cast<PresetStore*>(this)->get_iter(path); // Bug in Gtkmm: no get_iter() const
    Glib::ustring s(i->get_value(col.name));
    if (s.empty()) {
	return false;
    } else {
	return true;
    }
}


int PresetWindow::paned_child_height = 0;

PresetWindow::PresetWindow(gx_engine::ParamMap& pmap, Glib::RefPtr<gx_gui::GxBuilder> bld, gx_preset::GxSettings& gx_settings_,
			   const gx_system::CmdlineOptions& options_, Glib::RefPtr<Gtk::ActionGroup>& actiongroup_, Glib::RefPtr<Gtk::AccelGroup>& accel_group_)
    : sigc::trackable(),
      gx_settings(gx_settings_),
      actiongroup(actiongroup_),
      paned_child_height_param(pmap.reg_non_midi_par("system.preset_window_height", &paned_child_height, false, 200, 0, 99999)),
      in_edit(false),
      edit_iter(),
      pb_edit(),
      pb_del(),
      pb_scratch(),
      pb_versiondiff(),
      pb_readonly(),
      pb_factory(),
      pstore(new PresetStore),
      target_col(),
      bank_col(),
      bank_row_del_conn(),
      preset_row_del_conn(),
      vpaned_pos(),
      vpaned_step(),
      vpaned_target(),
      animate(true),
      options(options_),
      in_current_preset(false),
      on_map_conn(),
      accel_group(accel_group_)
      /* widget pointers not initialized */ {
    load_widget_pointers(bld);
    Glib::RefPtr<Gtk::Action> act = Gtk::Action::create("ClosePresetsAction");
    actiongroup->add(act, sigc::mem_fun(*this, &PresetWindow::on_presets_close));
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(close_preset->gobj()), act->gobj());
    act = Gtk::Action::create("NewBankAction");
    actiongroup->add(act, sigc::mem_fun(*this, &PresetWindow::on_new_bank));
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(new_preset_bank->gobj()), act->gobj());
    act = Gtk::Action::create("SaveAction");
    act->set_sensitive(false);
    actiongroup->add(act, sigc::mem_fun(*this, &PresetWindow::on_preset_save));
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(save_preset->gobj()), act->gobj());
    Glib::RefPtr<Gtk::ToggleAction> actt = Gtk::ToggleAction::create("OrganizeAction");
    actiongroup->add(actt, sigc::mem_fun(*this, &PresetWindow::on_organize));
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(organize_presets->gobj()), GTK_ACTION(actt->gobj()));

    bank_treeview->set_model(Gtk::ListStore::create(bank_col));
    bank_treeview->get_selection()->set_select_function(
	sigc::mem_fun(*this, &PresetWindow::select_func));
    bank_treeview->set_has_tooltip(true);
    bank_treeview->signal_query_tooltip().connect(
	sigc::mem_fun(*this, &PresetWindow::on_bank_query_tooltip));
    pb_edit = bank_treeview->render_icon(Gtk::Stock::EDIT, Gtk::ICON_SIZE_MENU);
    pb_del = bank_treeview->render_icon(Gtk::Stock::DELETE, Gtk::ICON_SIZE_MENU);
    pb_scratch = Gdk::Pixbuf::create_from_file(options.get_style_filepath("scratch.png"));
    pb_versiondiff = Gdk::Pixbuf::create_from_file(options.get_style_filepath("versiondiff.png"));
    pb_readonly = Gdk::Pixbuf::create_from_file(options.get_style_filepath("readonly.png"));
    pb_factory = Gdk::Pixbuf::create_from_file(options.get_style_filepath("factory.png"));
    bank_treeview->set_row_separator_func(sigc::mem_fun(*this, &PresetWindow::is_row_separator));
    bank_cellrenderer->signal_edited().connect(
	sigc::bind(sigc::mem_fun(*this, &PresetWindow::on_bank_edited), bank_treeview));
    bank_cellrenderer->signal_editing_canceled().connect(
	sigc::bind(sigc::mem_fun(*this, &PresetWindow::on_edit_canceled), bank_treeview->get_column(1)));
    bank_cellrenderer->signal_editing_started().connect(
	sigc::bind(sigc::mem_fun(*this, &PresetWindow::on_editing_started), bank_treeview->get_model()));
    Gtk::TreeViewColumn *col = bank_treeview->get_column(1);
    col->set_cell_data_func(**col->get_cell_renderers().begin(), sigc::mem_fun(*this, &PresetWindow::highlight_current_bank));

    std::vector<Gtk::TargetEntry> listTargets;
    listTargets.push_back(Gtk::TargetEntry("GTK_TREE_MODEL_ROW", Gtk::TARGET_SAME_WIDGET, 0));
    listTargets.push_back(Gtk::TargetEntry("text/uri-list", Gtk::TARGET_OTHER_APP, 1));
    bank_treeview->enable_model_drag_source(listTargets, Gdk::BUTTON1_MASK, Gdk::ACTION_COPY);
    bank_treeview->signal_drag_motion().connect(sigc::mem_fun(*this, &PresetWindow::on_bank_drag_motion), false);
    bank_treeview->enable_model_drag_dest(listTargets, Gdk::ACTION_COPY);
    bank_treeview->signal_drag_data_received().connect(
	sigc::mem_fun(*this, &PresetWindow::on_bank_drag_data_received));
    bank_treeview->signal_drag_data_get().connect(
	sigc::mem_fun(*this, &PresetWindow::on_bank_drag_data_get));
    Glib::RefPtr<Gtk::TreeSelection> sel = bank_treeview->get_selection();
    sel->set_mode(Gtk::SELECTION_BROWSE);
    sel->signal_changed().connect(sigc::mem_fun(*this, &PresetWindow::on_bank_changed));
    bank_treeview->signal_button_release_event().connect(sigc::mem_fun(*this, &PresetWindow::on_bank_button_release), true);
    Glib::RefPtr<Gtk::TreeModel> ls = bank_treeview->get_model();
    bank_row_del_conn = ls->signal_row_deleted().connect(sigc::mem_fun(*this, &PresetWindow::on_bank_reordered));

    preset_treeview->set_model(pstore);
    preset_treeview->signal_drag_motion().connect(sigc::mem_fun(*this, &PresetWindow::on_preset_drag_motion), false);
    preset_treeview->signal_drag_data_get().connect(sigc::mem_fun(*this, &PresetWindow::on_preset_drag_data_get));
    preset_treeview->signal_row_activated().connect(sigc::mem_fun(*this, &PresetWindow::on_preset_row_activated));
    preset_treeview->signal_button_press_event().connect(sigc::mem_fun(*this, &PresetWindow::on_preset_button_press));
    preset_treeview->signal_button_release_event().connect(sigc::mem_fun(*this, &PresetWindow::on_preset_button_release), true);
    preset_row_del_conn = pstore->signal_row_deleted().connect(sigc::mem_fun(*this, &PresetWindow::on_preset_reordered));
    preset_treeview->get_selection()->set_mode(Gtk::SELECTION_BROWSE);
    preset_treeview->get_selection()->set_select_function(
	sigc::mem_fun(*this, &PresetWindow::select_func));
    preset_treeview->get_selection()->signal_changed().connect(sigc::mem_fun(*this, &PresetWindow::on_preset_changed));
    preset_treeview->signal_cursor_changed().connect(sigc::mem_fun(*this, &PresetWindow::on_cursor_changed));
    preset_cellrenderer->signal_edited().connect(sigc::mem_fun(*this, &PresetWindow::on_preset_edited));
    preset_cellrenderer->signal_editing_canceled().connect(
	sigc::bind(sigc::mem_fun(*this, &PresetWindow::on_edit_canceled), preset_treeview->get_column(0)));
    preset_cellrenderer->signal_editing_started().connect(
	sigc::bind(
	    sigc::mem_fun(*this, &PresetWindow::on_editing_started),
	    Glib::RefPtr<Gtk::TreeModel>::cast_static(pstore)));
    preset_treeview->get_column(0)->set_cell_data_func(*preset_cellrenderer, sigc::mem_fun(*this, &PresetWindow::text_func));
    banks_combobox->signal_changed().connect(sigc::mem_fun(*this, &PresetWindow::on_preset_combo_changed));
    presets_target_treeview->get_selection()->set_mode(Gtk::SELECTION_NONE);
    std::vector<Gtk::TargetEntry> listTargets3;
    listTargets3.push_back(Gtk::TargetEntry("application/x-guitarix-preset", Gtk::TARGET_SAME_APP, 0));
    presets_target_treeview->enable_model_drag_dest(listTargets3, Gdk::ACTION_COPY);
    presets_target_treeview->signal_drag_motion().connect(sigc::mem_fun(*this, &PresetWindow::on_target_drag_motion), false);
    presets_target_treeview->signal_drag_data_received().connect_notify(sigc::mem_fun(*this, &PresetWindow::target_drag_data_received));
    gx_settings.signal_selection_changed().connect(
	sigc::mem_fun(*this, &PresetWindow::show_selected_preset));
    set_presets();
}

PresetWindow::~PresetWindow() {
    paned_child_height = main_vpaned->get_allocation().get_height() - main_vpaned->get_position();
}

void PresetWindow::load_widget_pointers(Glib::RefPtr<gx_gui::GxBuilder> bld) {
    bld->find_widget("close_preset", close_preset);
    bld->find_widget("save_preset", save_preset);
    bld->find_widget("new_preset_bank", new_preset_bank);
    bld->find_widget("organize_presets", organize_presets);
    bld->find_widget_derived("bank_treeview", bank_treeview, sigc::ptr_fun(MyTreeView::create_from_builder));
    bld->find_widget("bank_cellrenderer", bank_cellrenderer);
    bld->find_widget_derived("preset_treeview", preset_treeview, sigc::ptr_fun(MyTreeView::create_from_builder));
    bld->find_widget("preset_cellrenderer", preset_cellrenderer);
    bld->find_widget("banks_combobox", banks_combobox);
    bld->find_widget_derived("presets_target_treeview", presets_target_treeview, sigc::ptr_fun(MyTreeView::create_from_builder));
    bld->find_widget("preset_title", preset_title);
    bld->find_widget("presets_target_scrolledbox", presets_target_scrolledbox);
    bld->find_widget("bank_column_edit", bank_column_edit);
    bld->find_widget("bank_column_delete", bank_column_delete);
    bld->find_widget("preset_column_edit", preset_column_edit);
    bld->find_widget("preset_column_delete", preset_column_delete);
    bld->find_widget("main_vpaned", main_vpaned);
    bld->find_widget("preset_scrolledbox", preset_scrolledbox);
    bld->find_widget("preset_status", preset_status);
}

static bool preset_button_press_idle(Gtk::Widget& w) {
    w.grab_focus();
    return false;
}

bool PresetWindow::on_bank_query_tooltip(int x, int y, bool kb_tooltip, Glib::RefPtr<Gtk::Tooltip> tooltip) {
    Gtk::TreeIter it;
    if (!bank_treeview->get_tooltip_context_iter(x, y, kb_tooltip, it)) {
	return false;
    }
    int tp = it->get_value(bank_col.tp);
    if (tp == gx_system::PresetFile::PRESET_SEP) {
	return false;
    }
    Gtk::TreeModel::Path pt;
    Gtk::TreeViewColumn *col;
    int dx, dy;
    if (!bank_treeview->get_path_at_pos(x, y, pt, col, dx, dy)) {
	col = 0;
    }
    Glib::ustring nm = it->get_value(bank_col.name);
    if (nm.empty()) {
	return false;
    }
    gx_system::PresetFile *f = gx_settings.banks.get_file(nm);
    if (col == bank_treeview->get_column(0) || col == bank_treeview->get_column(1)) {
	if (tp == gx_system::PresetFile::PRESET_FILE) {
	    if (f->get_flags() & gx_system::PRESET_FLAG_INVALID) {
		tooltip->set_text(_("damaged bank file; click to delete"));
	    } else if (f->get_flags() & gx_system::PRESET_FLAG_VERSIONDIFF) {
		tooltip->set_text(
		    Glib::ustring::compose(_("wrong format version (is %1, need %2)\nclick to convert"),
					   f->get_header().version_string(),
					   f->get_header().current_version_string()));
	    } else if (f->get_flags() & gx_system::PRESET_FLAG_READONLY) {
		tooltip->set_text(_("readonly bank, click to change to read-write"));
	    } else if (col == bank_treeview->get_column(0)){
		tooltip->set_text(_("click to set to readonly"));
	    } else {
		return false;
	    }
	} else if (tp == gx_system::PresetFile::PRESET_FACTORY) {
	    tooltip->set_text(_("predefined factory preset bank"));
	} else if (tp == gx_system::PresetFile::PRESET_SCRATCH) {
	    tooltip->set_text(_("scratch preset bank: changes will be persistent (without explicit saving)"));
	} else {
	    return false;
	}
    } else if (col == bank_treeview->get_column(2)) {
	if (f->get_flags()) {
	    return false;
	}
	tooltip->set_text(_("click to edit the bank name"));
    } else if (col == bank_treeview->get_column(3)) {
	if (f->get_flags()) {
	    return false;
	}
	tooltip->set_text(_("click to delete the bank"));
    } else {
	return false;
    }
    bank_treeview->set_tooltip_cell(tooltip, &pt, col, 0);
    return true;
}

void PresetWindow::on_preset_row_activated(const Gtk::TreePath& path, Gtk::TreeViewColumn* column) {
    on_presets_close();
}

bool PresetWindow::on_preset_button_press(GdkEventButton *ev) {
    if (ev->type == GDK_BUTTON_PRESS) {
	Glib::signal_idle().connect(sigc::bind(sigc::ptr_fun(preset_button_press_idle), sigc::ref(*preset_treeview)));
    }
    return false;
}


void PresetWindow::on_preset_drag_data_get(const Glib::RefPtr<Gdk::DragContext>& context, Gtk::SelectionData& selection, int info, int timestamp) {
    if (selection.get_target() == "application/x-guitarix-preset") {
	Gtk::TreeModel::Path path;
	Gtk::TreeViewColumn *focus_column;
	preset_treeview->get_cursor(path, focus_column);
	Glib::ustring data = pstore->get_iter(path)->get_value(pstore->col.name);
	selection.set("application/x-guitarix-preset", data);
    }
}

void PresetWindow::on_bank_drag_data_get(const Glib::RefPtr<Gdk::DragContext>& context, Gtk::SelectionData& selection, int info, int timestamp) {
    if (selection.get_target() == "text/uri-list") {
	Gtk::TreeModel::Path path;
	Gtk::TreeViewColumn *focus_column;
	bank_treeview->get_cursor(path, focus_column);
	std::vector<std::string> uris;
	uris.push_back(
	    Gio::File::create_for_path(
		gx_settings.banks.get_file(
		    bank_treeview->get_model()->get_iter(path)->get_value(bank_col.name)
		    )->get_filename()
		)->get_uri());
	selection.set_uris(uris);
    }
}

void PresetWindow::on_bank_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, const Gtk::SelectionData& data, guint info, guint timestamp) {
    if (info != 1) {
	return;
    }
    bool is_move = context->get_selected_action() == Gdk::ACTION_MOVE;
    bool success = false;
    std::vector<Glib::ustring> uris = data.get_uris();
    Glib::RefPtr<Gtk::ListStore> ls = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(bank_treeview->get_model());
    for (std::vector<Glib::ustring>::iterator i = uris.begin(); i != uris.end(); ++i) {
	Glib::RefPtr<Gio::File> rem = Gio::File::create_for_uri(*i);
	std::string filename = rem->get_basename();
	gx_settings.banks.strip_preset_postfix(filename);
	Glib::ustring name = gx_settings.banks.decode_filename(filename);
	gx_settings.banks.make_valid_utf8(name);
	gx_settings.banks.make_bank_unique(name, &filename);
	Glib::RefPtr<Gio::File> dest = Gio::File::create_for_path(filename);
	try {
	    rem->copy(dest);
	} catch (Gio::Error& e) {
	    gx_system::gx_print_error(e.what().c_str(), _("can't copy to config dir"));
	    is_move = false;
	    continue;
	}
	gx_system::PresetFile *f = new gx_system::PresetFile();
	if (f->open_file(name, filename, gx_system::PresetFile::PRESET_FILE, 0)) {
	    gx_settings.banks.insert(f);
	    Gtk::TreeIter i = ls->prepend();
	    set_row_for_presetfile(i,f);
	    bank_treeview->set_cursor(ls->get_path(i));
	    bank_treeview->get_selection()->select(i);
	    success = true;
	} else {
	    delete f;
	    try {
		dest->remove();
	    } catch (Gio::Error& e) {
		gx_system::gx_print_error(e.what().c_str(), _("can't remove copied file!?"));
	    }
	    is_move = false;
	}
	if (is_move) {
	    try {
		rem->remove();
	    } catch (Gio::Error& e) {
		gx_system::gx_print_error(e.what().c_str(), _("can't move; file has been copied"));
	    }
	}
    }
    context->drag_finish(success, false, timestamp);
}

Glib::ustring PresetWindow::get_combo_selection() {
    Gtk::TreeIter idx = banks_combobox->get_active();
    if (!idx) {
	return "";
    }
    return idx->get_value(target_col.name);
}

/*
 ** dnd target
 */

void PresetWindow::target_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, const Gtk::SelectionData& data, guint info, guint timestamp) {
    Glib::ustring bank = get_combo_selection();
    if (bank.empty()) {
	presets_target_treeview->signal_drag_data_received().emission_stop();
	return;
    }
    gx_system::PresetFile& fl = *gx_settings.banks.get_file(bank);
    Glib::RefPtr<Gtk::ListStore> ls = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(presets_target_treeview->get_model());
    Glib::ustring srcnm = data.get_data_as_string();
    Glib::ustring dstnm = srcnm;
    int n = 1;
    while (fl.has_entry(dstnm)) {
	dstnm = srcnm + "-" + gx_system::to_string(n);
	n += 1;
    }
    Glib::ustring src_bank = get_current_bank();
    gx_system::PresetFile& pf = *gx_settings.banks.get_file(src_bank);
    Gtk::TreeModel::Path pt;
    Gtk::TreeViewDropPosition dst;
    if (!presets_target_treeview->get_dest_row_at_pos(x, y, pt, dst)) {
	ls->append()->set_value(target_col.name, dstnm);
	gx_settings.append(pf, srcnm, fl, dstnm);
    } else {
	Gtk::TreeIter it = ls->get_iter(pt);
	if (dst == Gtk::TREE_VIEW_DROP_BEFORE || dst == Gtk::TREE_VIEW_DROP_INTO_OR_BEFORE) {
	    ls->insert(it)->set_value(target_col.name, dstnm);
	    gx_settings.insert_before(pf, srcnm, fl, it->get_value(target_col.name), dstnm);
	} else { // gtk.TREE_VIEW_DROP_INTO_OR_AFTER, gtk.TREE_VIEW_DROP_AFTER
	    ls->insert_after(it)->set_value(target_col.name, dstnm);
	    gx_settings.insert_after(pf, srcnm, fl, it->get_value(target_col.name), dstnm);
	}
    }
    if (context->get_action() == Gdk::ACTION_MOVE) {
	Gtk::TreeModel::Path pt;
	Gtk::TreeViewColumn *col;
	preset_treeview->get_cursor(pt, col);
	preset_row_del_conn.block();
	pstore->erase(pstore->get_iter(pt));
	preset_row_del_conn.unblock();
	gx_settings.erase_preset(pf, srcnm);
    }
    if (src_bank == bank) {
	on_bank_changed();
    }
}

bool PresetWindow::on_target_drag_motion(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, guint timestamp) {
    Gtk::Widget *source_widget = Gtk::Widget::drag_get_source_widget(context);
    if (source_widget != preset_treeview || get_combo_selection().empty()) {
	context->drag_status((Gdk::DragAction)0, timestamp);
	return true;
    }
    presets_target_treeview->on_drag_motion(context, x, y, timestamp);
    Gtk::TreeIter it = bank_treeview->get_selection()->get_selected();
    int tp = it->get_value(bank_col.tp);
    Glib::ustring nm = it->get_value(bank_col.name);
    if ((tp != gx_system::PresetFile::PRESET_SCRATCH && tp != gx_system::PresetFile::PRESET_FILE) || gx_settings.banks.get_file(nm)->get_flags() ||
	get_combo_selection() == nm) {
	context->drag_status(Gdk::ACTION_COPY, timestamp);
    }
    return true;
}

void PresetWindow::reload_combo() {
    Glib::ustring old = get_combo_selection();
    Glib::RefPtr<Gtk::ListStore> ls = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(banks_combobox->get_model());
    ls->clear();
    int n = 0;
    int nn = -1;
    for (gx_system::PresetBanks::iterator i = gx_settings.banks.begin(); i != gx_settings.banks.end(); ++i) {
	int tp = i->get_type();
	if (tp != gx_system::PresetFile::PRESET_FILE && tp != gx_system::PresetFile::PRESET_SCRATCH) {
	    continue;
	}
	if (i->get_flags()) {
	    continue;
	}
	Glib::ustring s = i->get_name();
	ls->append()->set_value(bank_col.name, s);
	if (s == old) {
	    nn = n;
	}
	n += 1;
    }
    banks_combobox->set_active(nn);
}

void PresetWindow::on_preset_combo_changed() {
    Glib::RefPtr<Gtk::ListStore> ls = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(presets_target_treeview->get_model());
    ls->clear();
    Glib::ustring nm = get_combo_selection();
    if (nm.empty()) {
	return;
    }
    gx_system::PresetFile& f = *gx_settings.banks.get_file(nm);
    for (gx_system::PresetFile::iterator i = f.begin(); i != f.end(); ++i) {
	ls->append()->set_value(bank_col.name, i->name);
    }
}

void PresetWindow::reload_target() {
    on_preset_combo_changed();
}

/*
 ** name edit
 */

bool PresetWindow::select_func(const Glib::RefPtr<Gtk::TreeModel>& model, const Gtk::TreePath& path, bool path_currently_selected) {
    Glib::ustring s = model->get_iter(path)->get_value(bank_col.name);
    if (s.empty()) {
	return false;
    }
    return true;
}

void PresetWindow::on_editing_started(const Gtk::CellEditable* edit, const Glib::ustring& path, Glib::RefPtr<Gtk::TreeModel>& model) {
    Glib::ustring s = model->get_iter(path)->get_value(bank_col.name);
    if (s.empty()) {
	dynamic_cast<Gtk::Entry*>(const_cast<Gtk::CellEditable*>(edit))->set_text("");
    } else {
	dynamic_cast<Gtk::Entry*>(const_cast<Gtk::CellEditable*>(edit))->set_text(s);
    }
    dynamic_cast<Gtk::Window*>(main_vpaned->get_toplevel())->remove_accel_group(accel_group);
}

bool PresetWindow::edit_cell(const Gtk::TreeModel::Path pt, Gtk::TreeViewColumn& col, Gtk::CellRenderer& cell) {
    dynamic_cast<Gtk::CellRendererText*>(&cell)->property_editable().set_value(true);
    col.get_tree_view()->set_cursor(pt, col, true);
    return false;
}

void PresetWindow::reset_edit(Gtk::TreeViewColumn& col) {
    if (edit_iter) {
	Glib::RefPtr<Gtk::ListStore> ls = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(col.get_tree_view()->get_model());
	ls->erase(edit_iter);
	edit_iter = ls->children().end();
    }
    Gtk::CellRendererText& cell = *dynamic_cast<Gtk::CellRendererText*>(col.get_first_cell_renderer());
    cell.property_editable().set_value(false);
    col.set_min_width(0);
    col.queue_resize();
    in_edit = false;
    dynamic_cast<Gtk::Window*>(main_vpaned->get_toplevel())->add_accel_group(accel_group);
}

void PresetWindow::on_edit_canceled(Gtk::TreeViewColumn *col) {
    reset_edit(*col);
}

void PresetWindow::start_edit(const Gtk::TreeModel::Path& pt, Gtk::TreeViewColumn& col, Gtk::CellRenderer& cell) {
    col.set_min_width(100);
    Glib::signal_idle().connect(
	sigc::bind(sigc::mem_fun(*this, &PresetWindow::edit_cell),
		   pt, sigc::ref(col), sigc::ref(cell)));
}

/*
 ** list of banks
 */

void PresetWindow::highlight_current_bank(Gtk::CellRenderer *cell, const Gtk::TreeModel::iterator& iter) {
    Glib::ustring t = iter->get_value(bank_col.name);
    Gtk::CellRendererText *tc = dynamic_cast<Gtk::CellRendererText*>(cell);
    if (t == gx_settings.get_current_bank()) {
	tc->property_foreground().set_value("#f00");
    } else{
	tc->property_foreground_set().set_value(false);
    }
    int n = *bank_treeview->get_model()->get_path(iter).begin();
    if (n > 26) {
	t = "    " + t;
    } else {
	t = Glib::ustring::compose("%1:  %2", char('A'+n), t);
    }
    cell->set_property("text", t);
}

Glib::ustring PresetWindow::get_current_bank() {
    Gtk::TreeIter it = get_current_bank_iter();
    if (!it) {
	return "";
    }
    return it->get_value(bank_col.name);
}

bool PresetWindow::run_message_dialog(Gtk::Widget& w, const Glib::ustring& msg) {
    Gtk::MessageDialog d(*dynamic_cast<Gtk::Window*>(w.get_toplevel()), msg, false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_OK_CANCEL, true);
    d.set_position(Gtk::WIN_POS_MOUSE);
    return d.run() == Gtk::RESPONSE_OK;
}

bool PresetWindow::on_bank_button_release(GdkEventButton *ev) {
    // edit bank name / delete bank
    Gtk::TreeModel::Path pt;
    Gtk::TreeViewColumn *col;
    int dx, dy;
    if (!bank_treeview->get_path_at_pos(ev->x, ev->y, pt, col, dx, dy)) {
	return false;
    }
    Gtk::TreeModel::Path path;
    Gtk::TreeViewColumn *focus_column;
    bank_treeview->get_cursor(path, focus_column);
    if (col != focus_column || pt != path) {
	return false;
    }
    Glib::RefPtr<Gtk::ListStore> ls = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(bank_treeview->get_model());
    Gtk::TreeModel::iterator it = ls->get_iter(pt);
    Glib::ustring nm = it->get_value(bank_col.name);
    int tp = it->get_value(bank_col.tp);
    if (col == bank_treeview->get_column(0)) {
	if (tp == gx_system::PresetFile::PRESET_SCRATCH || tp == gx_system::PresetFile::PRESET_FILE) {
	    int flags = gx_settings.banks.get_file(nm)->get_flags();
	    gx_system::PresetFile *f = gx_settings.banks.get_file(nm);
	    if (flags == 0 && tp == gx_system::PresetFile::PRESET_FILE) {
		/*if (run_message_dialog(*bank_treeview, "set bank " + nm + " to readonly?")) {*/
		f->set_flag(gx_system::PRESET_FLAG_READONLY, true);
		gx_settings.banks.save();
		reload_banks(nm);
	    } else if (flags == gx_system::PRESET_FLAG_VERSIONDIFF) {
		if (run_message_dialog(*bank_treeview, "convert bank " + nm + " to new version?")) {
		    if (gx_settings.convert_preset(*f)) {
			reload_banks(nm);
		    }
		}
	    } else if (flags == gx_system::PRESET_FLAG_READONLY) {
		/*if (run_message_dialog(*bank_treeview, "set bank " + nm + " to read/write?")) {*/
		f->set_flag(gx_system::PRESET_FLAG_READONLY, false);
		gx_settings.banks.save();
		reload_banks(nm);
	    } else if (flags == (gx_system::PRESET_FLAG_READONLY | gx_system::PRESET_FLAG_VERSIONDIFF)) {
		if (run_message_dialog(*bank_treeview, "convert readonly bank " + nm + " to new version?")) {
		    if (gx_settings.convert_preset(*f)) {
			reload_banks(nm);
		    }
		}
	    } else if (flags & gx_system::PRESET_FLAG_INVALID) {
		if (run_message_dialog(
			*bank_treeview, "delete damaged bank " + nm + "?"
			" Export it before deleting and ask in the"
			" guitarix online forum if you want to try to repair it!")) {
		    gx_settings.banks.remove(nm);
		    reload_banks(nm);
		}
	    }
	}
	return false;
    }
    if (tp != gx_system::PresetFile::PRESET_FILE || gx_settings.banks.get_file(nm)->get_flags()) {
	return false;
    }
    if (col == bank_treeview->get_column(2)) {
	col = bank_treeview->get_column(1);
	start_edit(pt, *col, *col->get_first_cell_renderer());
    } else if (col == bank_treeview->get_column(3)) {
	Gtk::MessageDialog d(*dynamic_cast<Gtk::Window*>(bank_treeview->get_toplevel()), "delete bank " + nm + "?", false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_OK_CANCEL, true);
	d.set_position(Gtk::WIN_POS_MOUSE);
	if (d.run() == Gtk::RESPONSE_OK) {
	    bank_row_del_conn.block();
	    ls->erase(it);
	    bank_row_del_conn.unblock();
	    gx_settings.banks.remove(nm);
	    reload_combo();
	    if (nm == gx_settings.get_current_bank()) {
		gx_settings.set_source_to_state();
		save_preset->set_sensitive(false);
	    }
	}
    }
    return false;
}

static void strip(Glib::ustring& s) {
    size_t n = s.find_first_not_of(' ');
    if (n == Glib::ustring::npos) {
	s.erase();
	return;
    }
    if (n != 0) {
	s.erase(0, n);
    }
    s.erase(s.find_last_not_of(' ')+1);
}

void PresetWindow::on_bank_edited(const Glib::ustring& path, const Glib::ustring& newtext, Gtk::TreeView* w) {
    Gtk::TreeIter sel = w->get_model()->get_iter(path);
    Glib::ustring oldname = sel->get_value(bank_col.name);
    Glib::ustring newname = newtext;
    strip(newname);
    if (newname.empty() || newname == oldname) {
	Gtk::TreeViewColumn *p = w->get_column(1);
	reset_edit(*p);
	return;
    }
    Glib::RefPtr<Gtk::ListStore> ls = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(banks_combobox->get_model());
    std::string newfile;
    gx_settings.banks.make_bank_unique(newname, &newfile);
    if (edit_iter) {
	ls->prepend()->set_value(target_col.name, newname);
	edit_iter = ls->children().end();
	gx_system::PresetFile *f = new gx_system::PresetFile();
	if (f->create_file(newname, newfile, gx_system::PresetFile::PRESET_FILE, 0)) {
	    gx_settings.banks.insert(f);
	    set_row_for_presetfile(sel,f);
	} else {
	    delete f;
	}
    } else {
	Gtk::TreeNodeChildren ch = ls->children();
	for (Gtk::TreeIter it = ch.begin(); it != ch.end(); ++it) {
	    if (it->get_value(bank_col.name) == oldname) {
		it->set_value(bank_col.name, newname);
	    }
	}
	gx_settings.banks.rename(oldname, newname, newfile);
	if (oldname == gx_settings.get_current_bank()) {
	    //current_bank = newname; FIXME
	}
	sel->set_value(bank_col.name, newname);
    }
    w->get_selection()->select(sel);
    Gtk::TreeViewColumn *p = w->get_column(1);
    reset_edit(*p);
}

bool PresetWindow::is_row_separator(const Glib::RefPtr<Gtk::TreeModel>& model, const Gtk::TreeModel::iterator& iter) {
    return iter->get_value(bank_col.tp) == gx_system::PresetFile::PRESET_SEP;
}

void PresetWindow::on_new_bank() {
    Glib::RefPtr<Gtk::ListStore> m = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(bank_treeview->get_model());
    edit_iter = m->prepend();
    edit_iter->set_value(bank_col.tp, static_cast<int>(gx_system::PresetFile::PRESET_FILE));
    in_edit = true;
    start_edit(m->get_path(edit_iter), *bank_treeview->get_column(1), *bank_cellrenderer);
}

bool PresetWindow::on_bank_drag_motion(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, guint timestamp) {
    Gtk::Widget *source_widget = Gtk::Widget::drag_get_source_widget(context);
    if (!source_widget) {
	// URI from other application
	Gdk::DragAction a;
	if (context->get_suggested_action() == Gdk::ACTION_MOVE) {
	    a = context->get_suggested_action();
	} else {
	    a = Gdk::ACTION_COPY;
	}
	context->drag_status(a, timestamp);
    } else if (source_widget != bank_treeview) {
	// other window
	context->drag_status((Gdk::DragAction)0, timestamp);
    } else {
	// reorder
	Gtk::TreeIter it = bank_treeview->get_selection()->get_selected();
	if (!it) {
	    return true;
	}
	int tp = it->get_value(bank_col.tp);
	if (tp != gx_system::PresetFile::PRESET_SCRATCH && tp != gx_system::PresetFile::PRESET_FILE) {
	    context->drag_status((Gdk::DragAction)0, timestamp);
	    return true;
	}
	Gtk::TreeModel::Path pt;
	Gtk::TreeViewDropPosition dst;
	if (bank_treeview->get_dest_row_at_pos(x, y, pt, dst)) {
	    tp = bank_treeview->get_model()->get_iter(pt)->get_value(bank_col.tp);
	    if (tp != gx_system::PresetFile::PRESET_SCRATCH && tp != gx_system::PresetFile::PRESET_FILE) {
		context->drag_status((Gdk::DragAction)0, timestamp);
		return true;
	    }
	}
	bank_treeview->on_drag_motion(context, x, y, timestamp);
	context->drag_status(Gdk::ACTION_MOVE, timestamp);
    }
    return true;
}

void PresetWindow::on_bank_changed() {
    preset_row_del_conn.block();
    pstore->clear();
    preset_row_del_conn.unblock();
    Gtk::TreeIter it = bank_treeview->get_selection()->get_selected();
    if (!it) {
	in_current_preset = false;
	return;
    }
    Glib::ustring nm = it->get_value(bank_col.name);
    preset_title->set_text(nm);
    in_current_preset = (nm == gx_settings.get_current_bank());
    Gtk::TreeIter i;
    gx_system::PresetFile& ll = *gx_settings.banks.get_file(nm);
    if ((ll.get_flags() & gx_system::PRESET_FLAG_VERSIONDIFF) ||
	((ll.get_flags() & gx_system::PRESET_FLAG_READONLY) &&
	 !Glib::RefPtr<Gtk::ToggleAction>::cast_dynamic(actiongroup->get_action("OrganizeAction"))->get_active())) {
	preset_treeview->unset_rows_drag_source();
    } else {
	preset_treeview->unset_rows_drag_source(); //FIXME: needed?
	preset_treeview->set_reorderable(true);
	std::vector<Gtk::TargetEntry> listTargets2;
	listTargets2.push_back(Gtk::TargetEntry("GTK_TREE_MODEL_ROW", Gtk::TARGET_SAME_WIDGET, 0));
	listTargets2.push_back(Gtk::TargetEntry("application/x-guitarix-preset", Gtk::TARGET_SAME_APP, 1));
	preset_treeview->enable_model_drag_source(listTargets2, Gdk::BUTTON1_MASK, Gdk::ACTION_COPY|Gdk::ACTION_MOVE);
    }
    bool modifiable = ll.is_mutable();
    for (gx_system::PresetFile::iterator s = ll.begin(); s != ll.end(); ++s) {
	i = pstore->append();
	i->set_value(pstore->col.name, s->name);
	if (modifiable) {
	    i->set_value(pstore->col.edit_pb, pb_edit);
	    i->set_value(pstore->col.del_pb, pb_del);
	}
	if (in_current_preset && s->name == gx_settings.get_current_name()) {
	    if (preset_treeview->get_mapped()) {
		preset_treeview->scroll_to_row(pstore->get_path(i));
	    }
	}
    }
    if (modifiable) {
	i = pstore->append();
    }
}

void PresetWindow::set_row_for_presetfile(Gtk::TreeIter i, gx_system::PresetFile *f) {
    i->set_value(bank_col.name, f->get_name());
    if (f->get_flags() & gx_system::PRESET_FLAG_INVALID) {
	i->set_value(bank_col.type_pb, pb_del);
    } else if (f->get_flags() & gx_system::PRESET_FLAG_VERSIONDIFF) {
	i->set_value(bank_col.type_pb, pb_versiondiff);
    } else if (f->get_flags() & gx_system::PRESET_FLAG_READONLY) {
	i->set_value(bank_col.type_pb, pb_readonly);
    }
    int tp = f->get_type();
    i->set_value(bank_col.tp, tp);
    if (tp == gx_system::PresetFile::PRESET_SCRATCH) {
	i->set_value(bank_col.type_pb, pb_scratch);
    } else if (tp == gx_system::PresetFile::PRESET_FACTORY) {
	i->set_value(bank_col.type_pb, pb_factory);
    } else if (f->is_mutable() || f->get_flags() & gx_system::PRESET_FLAG_VERSIONDIFF) {
	i->set_value(bank_col.edit_pb, pb_edit);
	i->set_value(bank_col.del_pb, pb_del);
    }
}

void PresetWindow::reload_banks(const Glib::ustring& sel_bank) {
    preset_row_del_conn.block();
    pstore->clear();
    preset_row_del_conn.unblock();
    Glib::RefPtr<Gtk::ListStore> ls = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(bank_treeview->get_model());
    bank_row_del_conn.block();
    ls->clear();
    bank_row_del_conn.unblock();
    Gtk::TreeIter i;
    int in_factory = false;
    for (gx_system::PresetBanks::iterator v = gx_settings.banks.begin(); v != gx_settings.banks.end(); ++v) {
	if (!in_factory && v->get_type() == gx_system::PresetFile::PRESET_FACTORY) {
	    i = ls->append();
	    i->set_value(bank_col.tp, static_cast<int>(gx_system::PresetFile::PRESET_SEP));
	    in_factory = true;
	}
	i = ls->append();
	set_row_for_presetfile(i, *v);
	if (v->get_name() == sel_bank) {
	    bank_treeview->get_selection()->select(i);
	}
    }
    reload_combo();
}

void PresetWindow::set_presets() {
    reload_banks(gx_settings.get_current_bank());
}

void PresetWindow::on_bank_reordered(const Gtk::TreeModel::Path& path) {
    Glib::RefPtr<Gtk::TreeModel> ls = bank_treeview->get_model();
    Gtk::TreeModel::Children ch = ls->children();
    std::vector<Glib::ustring> l;
    for (Gtk::TreeIter i = ch.begin(); i != ch.end(); ++i) {
	int tp = i->get_value(bank_col.tp);
	Glib::ustring nm = i->get_value(bank_col.name);
	if (!nm.empty() && (tp == gx_system::PresetFile::PRESET_SCRATCH || tp == gx_system::PresetFile::PRESET_FILE)) {
	    l.push_back(nm);
	}
    }
    gx_settings.banks.reorder(l);
}

/*
 ** list of presets
 */

void PresetWindow::text_func(Gtk::CellRenderer *cell, const Gtk::TreeModel::iterator& iter) {
    Glib::ustring val = iter->get_value(pstore->col.name);
    Glib::ustring t = val;
    if (t.empty() && !cell->property_editing().get_value()) {
	t = "<new>";
    } else {
	int n = *pstore->get_path(iter).begin();
	if (n > 9) {
	    t = "    " + t;
	} else {
	    t = Glib::ustring::compose("%1:  %2", n+1, t);
	}
    }
    cell->set_property("text", t);
    Gtk::CellRendererText *tc = dynamic_cast<Gtk::CellRendererText*>(cell);
    if (in_current_preset && val == gx_settings.get_current_name()) {
	tc->property_foreground().set_value("#f00");
    } else{
	tc->property_foreground_set().set_value(false);
    }
}

bool PresetWindow::on_preset_button_release(GdkEventButton *ev) {
    Gtk::TreeModel::Path pt;
    Gtk::TreeViewColumn *col;
    int dx, dy;
    if (!preset_treeview->get_path_at_pos(ev->x, ev->y, pt, col, dx, dy)) {
	return false;
    }
    Gtk::TreeModel::Path path;
    Gtk::TreeViewColumn *focus_column;
    preset_treeview->get_cursor(path, focus_column);
    if (col != focus_column || pt != path) {
	return false;
    }
    Gtk::TreeIter bank_iter = get_current_bank_iter();
    int tp = bank_iter->get_value(bank_col.tp);
    if ((tp != gx_system::PresetFile::PRESET_SCRATCH && tp != gx_system::PresetFile::PRESET_FILE) || gx_settings.banks.get_file(bank_iter->get_value(bank_col.name))->get_flags()) {
	return false;
    }
    if (col == preset_treeview->get_column(1)) {
	col = preset_treeview->get_column(0);
	start_edit(pt, *col, *col->get_first_cell_renderer());
    } else if (col == preset_treeview->get_column(2)) {
	Glib::ustring nm = pstore->get_iter(pt)->get_value(pstore->col.name);
	Gtk::MessageDialog d(*dynamic_cast<Gtk::Window*>(preset_treeview->get_toplevel()), Glib::ustring::compose("delete preset %1?", nm), false,
			     Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_OK_CANCEL, true);
	d.set_position(Gtk::WIN_POS_MOUSE);
	if (d.run() == Gtk::RESPONSE_OK) {
	    preset_row_del_conn.block();
	    pstore->erase(pstore->get_iter(pt));
	    preset_row_del_conn.unblock();
	    gx_settings.erase_preset(*gx_settings.banks.get_file(bank_iter->get_value(bank_col.name)), nm);
	    reload_target();
	}
    }
    return false;
}

void PresetWindow::on_preset_edited(const Glib::ustring& path, const Glib::ustring& newtext) {
    Glib::ustring newname = newtext;
    strip(newname);
    if (newname.empty()) {
	reset_edit(*preset_treeview->get_column(0));
	return;
    }
    gx_system::PresetFile& fl = *gx_settings.banks.get_file(get_current_bank());
    Glib::ustring t = newname;
    int n = 1;
    while (fl.has_entry(newname)) {
	newname = Glib::ustring::compose("%1-%2", t, n);
	n += 1;
    }
    Gtk::TreeIter it = pstore->get_iter(path);
    t = it->get_value(pstore->col.name);
    if (t.empty()) {
	pstore->append();
	gx_settings.save(fl, newname);
    } else {
	fl.rename(t, newname);
	if (gx_settings.get_current_bank() == get_current_bank() && gx_settings.get_current_name() == it->get_value(pstore->col.name)) {
	    //current_preset = newname; FIXME
	}
    }
    it->set_value(pstore->col.name, newname);
    it->set_value(pstore->col.edit_pb, pb_edit);
    it->set_value(pstore->col.del_pb, pb_del);
    preset_treeview->get_selection()->select(pstore->get_iter(path));
    reload_target();
    reset_edit(*preset_treeview->get_column(0));
}

void PresetWindow::on_cursor_changed() {
    if (in_edit) {
	return;
    }
    Gtk::TreeModel::Path path;
    Gtk::TreeViewColumn *focus_column;
    preset_treeview->get_cursor(path, focus_column);
    if (!pstore->get_iter(path)->get_value(pstore->col.name).empty()) {
	return;
    }
    in_edit = true;
    start_edit(path, *preset_treeview->get_column(0), *preset_cellrenderer);
}

void PresetWindow::on_preset_changed() {
    if (!Glib::RefPtr<Gtk::ToggleAction>::cast_dynamic(actiongroup->get_action("OrganizeAction"))->get_active()) {
	preset_changed();
    }
}

bool PresetWindow::on_preset_drag_motion(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, guint timestamp) {
    if (Gtk::Widget::drag_get_source_widget(context) == preset_treeview) {
	Gtk::TreeIter it = bank_treeview->get_selection()->get_selected();
	bool ro = it && (gx_settings.banks.get_file(it->get_value(bank_col.name))->get_flags() & gx_system::PRESET_FLAG_READONLY);
	if (!ro) {
	    preset_treeview->on_drag_motion(context, x, y, timestamp);
	    Gtk::TreeModel::Path pt;
	    Gtk::TreeViewDropPosition dst;
	    if (preset_treeview->get_dest_row_at_pos(x, y, pt, dst)) {
		if (dst == Gtk::TREE_VIEW_DROP_BEFORE ||
		    (dst == Gtk::TREE_VIEW_DROP_AFTER &&
		     !pstore->get_iter(pt)->get_value(pstore->col.name).empty())) {
		    context->drag_status(Gdk::ACTION_MOVE, timestamp);
		    return true;
		}
	    }
	}
    }
    context->drag_status((Gdk::DragAction)0, timestamp);
    return true;
}

void PresetWindow::on_preset_reordered(const Gtk::TreeModel::Path& path) {
    // save changed order to file
    Gtk::TreeModel::Children ch = pstore->children();
    std::vector<Glib::ustring> l;
    for (Gtk::TreeIter i = ch.begin(); i != ch.end(); ++i) {
	Glib::ustring s = i->get_value(pstore->col.name);
	if (!s.empty()) {
	    l.push_back(s);
	}
    }
    gx_settings.reorder_preset(*gx_settings.banks.get_file(get_current_bank()), l);
    reload_target();
}

void PresetWindow::autosize() {
    bank_treeview->columns_autosize();
    preset_treeview->columns_autosize();
}

void PresetWindow::on_organize() {
    bool v = organize_presets->get_active();
    bank_column_edit->set_visible(v);
    bank_column_delete->set_visible(v);
    preset_column_edit->set_visible(v);
    preset_column_delete->set_visible(v);
    save_preset->set_sensitive(!v); // FIXME -> SaveAction
    Glib::RefPtr<Gtk::TreeSelection> sel = preset_treeview->get_selection();
    if (v) {
	sel->set_mode(Gtk::SELECTION_NONE);
	banks_combobox->set_active(-1);
	banks_combobox->show();
	presets_target_scrolledbox->show();
    } else {
	sel->set_mode(Gtk::SELECTION_BROWSE);
	banks_combobox->hide();
	presets_target_scrolledbox->hide();
    }
    on_bank_changed(); // reload for DnD adjustment of readonly banks
    autosize();
}

void PresetWindow::on_presets_close() {
    Glib::RefPtr<Gtk::ToggleAction>::cast_dynamic(actiongroup->get_action("PresetsAction"))->set_active(false); // FIXME
}

/*
 ** preset window
 */

bool PresetWindow::animate_preset_show() {
    vpaned_pos -= vpaned_step;
    if (vpaned_pos <= vpaned_target) {
	main_vpaned->set_position(vpaned_target);
	child_set_property(*main_vpaned, *preset_scrolledbox, "shrink", false);
	return false;
    }
    main_vpaned->set_position(vpaned_pos);
    return true;
}

bool PresetWindow::animate_preset_hide() {
    vpaned_pos += vpaned_step;
    if (vpaned_pos >= vpaned_target) {
	preset_scrolledbox->hide();
	return false;
    }
    main_vpaned->set_position(vpaned_pos);
    return true;
}

void PresetWindow::preset_changed() {
    Glib::ustring bank;
    Glib::ustring name;
    Gtk::TreeIter it = bank_treeview->get_selection()->get_selected();
    if (!it) {
	return;
    }
    bank = it->get_value(bank_col.name);
    it = preset_treeview->get_selection()->get_selected();
    if (!it) {
	return;
    }
    name = it->get_value(pstore->col.name);
    bool is_scratch = false;
    gx_system::PresetFile *cpf = 0;
    if (!gx_settings.get_current_bank().empty()) {
	cpf = gx_settings.banks.get_file(gx_settings.get_current_bank());
	if (cpf->has_entry(gx_settings.get_current_name())) {
	    is_scratch = (cpf->get_type() == gx_system::PresetFile::PRESET_SCRATCH);
	}
    }
    if (is_scratch) {
	gx_settings.save(*cpf, gx_settings.get_current_name());
	if (bank == gx_settings.get_current_bank() && name == gx_settings.get_current_name()) {
	    // no reload necessary
	    return;
	}
    }
    in_current_preset = true;
    cpf = gx_settings.banks.get_file(bank);
    gx_settings.load_preset(cpf, name);
    save_preset->set_sensitive(cpf && cpf->is_mutable());
}

void PresetWindow::show_selected_preset() {
    Glib::ustring t;
    if (gx_settings.get_current_source() != gx_system::GxSettingsBase::state) {
	t = gx_settings.get_current_bank() + " / " + gx_settings.get_current_name();
    }
    preset_status->set_text(t);
}

void PresetWindow::on_preset_save() {
    if (gx_settings.get_current_source() == gx_system::GxSettingsBase::state || gx_settings.get_current_bank().empty()) {
	return;
    }
    gx_system::PresetFile *pf = gx_settings.banks.get_file(gx_settings.get_current_bank());
    if (!pf->is_mutable()) {
	return;
    }
    gx_settings.save(*pf, gx_settings.get_current_name());
}

void PresetWindow::display_paned(bool show_preset) {
    vpaned_pos = main_vpaned->get_allocation().get_height();
    vpaned_target = vpaned_pos - paned_child_height;
    main_vpaned->set_position(vpaned_target);
    child_set_property(*main_vpaned, *preset_scrolledbox, "shrink", false);
    preset_scrolledbox->show();
    if (!show_preset || !in_current_preset) {
	return;
    }
    // make the current entry in the preset list window
    // visible (in case it's outside the displayed range).
    // apparently only works after the window is mapped
    // and some size calculations are done, so put it into
    // an idle handler.
    Gtk::TreeNodeChildren ch = pstore->children();
    for (Gtk::TreeIter it = ch.begin(); it != ch.end(); ++it) {
	if (it->get_value(pstore->col.name) == gx_settings.get_current_name()) {
	    Glib::signal_idle().connect_once(
		sigc::bind(
		    sigc::mem_fun1(*preset_treeview, &MyTreeView::scroll_to_row),
		    pstore->get_path(it)));
	    return;
	}
    }
    if (on_map_conn.connected()) {
	on_map_conn.disconnect();
    }
}

void PresetWindow::on_preset_select(bool v) {
    if (v) {
	if (gx_settings.banks.check_reparse()) {
	    set_presets();
	} else if (!get_current_bank_iter()) {
	    Glib::ustring bank = gx_settings.get_current_bank();
	    if (!bank.empty()) {
		reload_banks(bank);
	    }
	}
	autosize();
	if (!main_vpaned->get_mapped()) {
	    // don't have widget height to calculate paned separator
	    // position before window is mapped
	    on_map_conn = main_vpaned->get_toplevel()->signal_map().connect(
		sigc::bind(
		    sigc::mem_fun(*this, &PresetWindow::display_paned),
		    true));
	} else if (animate) {
	    vpaned_pos = main_vpaned->get_allocation().get_height();
	    vpaned_target = vpaned_pos - paned_child_height;
	    main_vpaned->set_position(vpaned_pos);
	    vpaned_step = paned_child_height / 5;
	    preset_scrolledbox->show();
	    animate_preset_show();
	    Glib::signal_timeout().connect(sigc::mem_fun(*this, &PresetWindow::animate_preset_show), 20);
	} else {
	    display_paned(false);
	}
    } else {
	vpaned_target = main_vpaned->get_allocation().get_height();
	if (animate && main_vpaned->get_mapped() && Glib::RefPtr<Gtk::ToggleAction>::cast_dynamic(actiongroup->get_action("ShowRack"))->get_active()) { //FIXME
	    vpaned_pos = main_vpaned->get_position();
	    paned_child_height = vpaned_target - vpaned_pos;
	    vpaned_step = paned_child_height / 5;
	    child_set_property(*main_vpaned, *preset_scrolledbox, "shrink", true);
	    Glib::signal_timeout().connect(sigc::mem_fun(*this, &PresetWindow::animate_preset_hide), 20);
	} else {
	    preset_scrolledbox->hide();
	}
	Glib::RefPtr<Gtk::ToggleAction>::cast_dynamic(actiongroup->get_action("OrganizeAction"))->set_active(false);
    }
}
