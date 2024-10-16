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

/****************************************************************
 * class PresetWindow
 *
 * model / view scheme
 *
 * There might be several views (clients), and the model (represented
 * by a GxMachineBase/GxSettingsBase instance) might be located in a
 * remote headless Guitarix instance.
 *
 * The model state consists of
 *  - list of banks
 *  - current bank
 *  - list of presets (for current bank)
 *  - current preset
 *
 * Model state changes trigger one of two signals:
 *  - presetlist_changed: need full state reload
 *  - selection_changed: current bank / preset changed
 *
 * Modifications of the model state will be reflected by a
 * signal. Changes loaded in response of a signal must not be set
 * (again) in the model.
 */

PresetStore::PresetStore(): Gtk::ListStore(), col() {
    set_column_types(col);
}

bool PresetStore::row_draggable_vfunc(const TreeModel::Path& path) const {
    Gtk::TreeModel::const_iterator i = const_cast<PresetStore*>(this)->get_iter(path); // Bug in Gtkmm: no get_iter() const
    Glib::ustring s(i->get_value(col.name));
    if (s.empty()) {
	return false;
    } else {
	return true;
    }
}

PresetWindow::PresetWindow(Glib::RefPtr<gx_gui::GxBuilder> bld, gx_engine::GxMachineBase& machine_,
                           const gx_system::CmdlineOptions& options_, GxActions& actions_,
                           UIManager& uimanager)
    : sigc::trackable(),
      machine(machine_),
      actions(actions_),
      accelgroup(uimanager.get_accel_group()),
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
      vpaned_pos(),
      vpaned_step(),
      vpaned_target(),
      options(options_),
      in_current_preset(false),
      load_in_progress(false),
      on_map_conn()
      /* widget pointers not initialized */ {
    load_widget_pointers(bld);
    gx_gui::GxBuilder::connect_gx_tooltip_handler(GTK_WIDGET(bank_treeview->gobj()));

    // create actions
    actions.new_bank = uimanager.add_action(
        "NewBank", sigc::mem_fun(*this, &PresetWindow::on_new_bank));
    UIManager::set_widget_action(new_preset_bank, actions.new_bank);
    actions.save_changes = uimanager.add_action(
        "Save", sigc::mem_fun(*this, &PresetWindow::on_preset_save));
    UIManager::set_widget_action(save_preset, actions.save_changes);
    actions.organize = uimanager.add_toggle_action("Organize");
    actions.organize->signal_toggled().connect(
        sigc::mem_fun(*this, &PresetWindow::on_organize));
    UIManager::set_widget_action(organize_presets, actions.organize);
    actions.online_preset_bank = uimanager.add_action(
        "OnlineBank", sigc::mem_fun(*this, &PresetWindow::on_online_preset));
    UIManager::set_widget_action(online_preset, actions.online_preset_bank);

    // bank treeview
    bank_treeview->set_model(Gtk::ListStore::create(bank_col));
    bank_treeview->get_selection()->set_select_function(
	sigc::mem_fun(*this, &PresetWindow::select_func));
    bank_treeview->set_has_tooltip(true);
    bank_treeview->signal_query_tooltip().connect(
	sigc::mem_fun(*this, &PresetWindow::on_bank_query_tooltip));
    pb_edit = bank_treeview->render_icon_pixbuf(Gtk::Stock::EDIT, Gtk::ICON_SIZE_MENU);
    pb_del = bank_treeview->render_icon_pixbuf(Gtk::Stock::DELETE, Gtk::ICON_SIZE_MENU);
    pb_scratch = Gdk::Pixbuf::create_from_file(options.get_style_filepath("scratch.png"));
    pb_versiondiff = Gdk::Pixbuf::create_from_file(options.get_style_filepath("versiondiff.png"));
    pb_readonly = Gdk::Pixbuf::create_from_file(options.get_style_filepath("readonly.png"));
    pb_factory = Gdk::Pixbuf::create_from_file(options.get_style_filepath("factory.png"));
    bank_treeview->set_row_separator_func(sigc::mem_fun(*this, &PresetWindow::is_row_separator));
    bank_cellrenderer->signal_edited().connect(
	sigc::bind(sigc::mem_fun(*this, &PresetWindow::on_bank_edited), bank_treeview));
    bank_cellrenderer->signal_editing_canceled().connect(
	sigc::bind(sigc::mem_fun(*this, &PresetWindow::on_edit_canceled), bank_column_bank));
    bank_cellrenderer->signal_editing_started().connect(
	sigc::bind(sigc::mem_fun(*this, &PresetWindow::on_editing_started), bank_treeview->get_model()));
    bank_column_bank->set_cell_data_func(*bank_cellrenderer, sigc::mem_fun(*this, &PresetWindow::highlight_current_bank));

    std::vector<Gtk::TargetEntry> listTargets;
    listTargets.push_back(Gtk::TargetEntry("GTK_TREE_MODEL_ROW", Gtk::TARGET_SAME_WIDGET, MODELROW_TARGET));
    listTargets.push_back(Gtk::TargetEntry("text/uri-list", Gtk::TARGET_OTHER_APP, URILIST_TARGET));
    bank_treeview->enable_model_drag_source(listTargets, Gdk::BUTTON1_MASK, Gdk::ACTION_COPY);
    bank_treeview->drag_source_add_text_targets(); // sets info == 0 (TEXT_TARGETS)
    bank_treeview->signal_drag_motion().connect(sigc::mem_fun(*this, &PresetWindow::on_bank_drag_motion), false);
    bank_treeview->enable_model_drag_dest(listTargets, Gdk::ACTION_COPY);
    bank_treeview->signal_drag_data_received().connect(
	sigc::mem_fun(*this, &PresetWindow::on_bank_drag_data_received));
    bank_treeview->signal_drag_data_get().connect(
	sigc::mem_fun(*this, &PresetWindow::on_bank_drag_data_get));
    bank_treeview->signal_drag_begin().connect(
	sigc::hide(sigc::mem_fun(machine, &gx_engine::GxMachineBase::bank_drag_begin)));
    Glib::RefPtr<Gtk::TreeSelection> sel = bank_treeview->get_selection();
    sel->signal_changed().connect(sigc::mem_fun(*this, &PresetWindow::on_bank_changed));
    bank_treeview->signal_button_release_event().connect(sigc::mem_fun(*this, &PresetWindow::on_bank_button_release), true);
    Glib::RefPtr<Gtk::TreeModel> ls = bank_treeview->get_model();
    ls->signal_row_deleted().connect(sigc::mem_fun(*this, &PresetWindow::on_bank_reordered));

    // preset treeview
    preset_treeview->set_model(pstore);
    preset_treeview->signal_drag_motion().connect(sigc::mem_fun(*this, &PresetWindow::on_preset_drag_motion), false);
    preset_treeview->signal_drag_data_get().connect(sigc::mem_fun(*this, &PresetWindow::on_preset_drag_data_get));
    preset_treeview->signal_row_activated().connect(sigc::mem_fun(*this, &PresetWindow::on_preset_row_activated));
    preset_treeview->signal_button_release_event().connect(sigc::mem_fun(*this, &PresetWindow::on_preset_button_release), true);
    pstore->signal_row_deleted().connect(sigc::mem_fun(*this, &PresetWindow::on_preset_reordered));
    preset_treeview->get_selection()->set_select_function(
	sigc::mem_fun(*this, &PresetWindow::select_func));
    preset_treeview->signal_cursor_changed 	().connect(sigc::mem_fun(*this, &PresetWindow::on_preset_changed));
    preset_cellrenderer->signal_edited().connect(sigc::mem_fun(*this, &PresetWindow::on_preset_edited));
    preset_cellrenderer->signal_editing_canceled().connect(
	sigc::bind(sigc::mem_fun(*this, &PresetWindow::on_edit_canceled), preset_column_preset));
    preset_cellrenderer->signal_editing_started().connect(
	sigc::bind(
	    sigc::mem_fun(*this, &PresetWindow::on_editing_started),
	    Glib::RefPtr<Gtk::TreeModel>::cast_static(pstore)));
    preset_column_preset->set_cell_data_func(
	*preset_cellrenderer, sigc::mem_fun(*this, &PresetWindow::text_func));

    // third column
    banks_combobox->signal_changed().connect(
	sigc::mem_fun(*this, &PresetWindow::on_preset_combo_changed));
    std::vector<Gtk::TargetEntry> listTargets3;
    listTargets3.push_back(
	Gtk::TargetEntry("application/x-guitarix-preset", Gtk::TARGET_SAME_APP, 0));
    presets_target_treeview->enable_model_drag_dest(listTargets3, Gdk::ACTION_COPY);
    presets_target_treeview->signal_drag_motion().connect(
	sigc::mem_fun(*this, &PresetWindow::on_target_drag_motion), false);
    presets_target_treeview->signal_drag_data_received().connect_notify(
	sigc::mem_fun(*this, &PresetWindow::target_drag_data_received));
    machine.signal_selection_changed().connect(
	sigc::mem_fun(*this, &PresetWindow::on_selection_changed));
    machine.signal_presetlist_changed().connect(
	sigc::mem_fun(*this, &PresetWindow::on_presetlist_changed));

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
}

PresetWindow::~PresetWindow() {
    curl_easy_cleanup(curl);
    curl_global_cleanup();
}

/*
 * bank / preset in model has changed
 *
 * redraw the banklist and presetlist to make sure the current
 * selection is displayed.
 * The save button state depends on the current bank.
 */
void PresetWindow::on_selection_changed() {
    Glib::ustring bank = get_current_bank();
    in_current_preset = (!bank.empty() && bank == machine.get_current_bank());
    Glib::RefPtr<Gtk::TreeModel> ls = bank_treeview->get_model();
    // show active bank
    Gtk::TreeNodeChildren ch = ls->children();
    Glib::ustring active_bank = machine.get_current_bank();
    for (Gtk::TreeIter it = ch.begin(); it != ch.end(); ++it) {
        if (it->get_value(bank_col.name) == active_bank) {
            if (!in_current_preset) {
                bank_treeview->get_selection()->select(it);
                // now in_current_preset == 1
            }
            // first time after program start sometimes does not work
            // when using direct call (Gtk 3.24)
            Glib::signal_idle().connect_once(
                sigc::bind(
                    sigc::mem_fun1(bank_treeview, &MyTreeView::scroll_to_row),
                    ls->get_path(it)));
            break;
        }
    }
    if (in_current_preset) {
        Glib::ustring active_preset = machine.get_current_name();
        ch = pstore->children();
        for (Gtk::TreeIter it = ch.begin(); it != ch.end(); ++it) {
            if (it->get_value(pstore->col.name) == active_preset) {
                preset_treeview->scroll_to_row(pstore->get_path(it));
                break;
            }
        }
    }
    bank_treeview->queue_draw();
    preset_treeview->queue_draw();
    bool savable = false;
    if (!organize_presets->get_active() && machine.setting_is_preset()) {
        gx_system::PresetFileGui *pf = machine.get_current_bank_file();
        if (pf && pf->is_mutable()) {
            savable = true;
        }
    }
    actions.save_changes->set_enabled(savable);
}

/**
 * state of model has changed
 *
 * reload the bank list and try to preserve the state of the displayed
 * lists
 */
void PresetWindow::on_presetlist_changed() {
    load_in_progress = true;
    Glib::ustring current_bank = get_current_bank();
    Glib::RefPtr<Gtk::ListStore> ls = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(bank_treeview->get_model());
    ls->clear();
    Gtk::TreeIter it, ifound, mfound;
    Glib::ustring mbank = machine.get_current_bank();
    int in_factory = false;
    for (gx_engine::bank_iterator v = machine.bank_begin(); v != machine.bank_end(); ++v) {
	if (!in_factory && v->get_type() == gx_system::PresetFile::PRESET_FACTORY) {
	    it = ls->append();
	    it->set_value(bank_col.tp, static_cast<int>(gx_system::PresetFile::PRESET_SEP));
	    in_factory = true;
	}
	it = ls->append();
	set_row_for_presetfile(it, *v);
	if (v->get_name() == current_bank) {
	    ifound = it;
	}
	if (!ifound && v->get_name() == mbank) {
	    mfound = it;
	}
    }
    if (!ifound) {
	ifound = mfound;
    }
    if (!ifound) {
	pstore->clear();
	preset_title->set_text("");
    }
    load_in_progress = false;
    if (ifound) {
	bank_treeview->get_selection()->select(ifound);
    }
    if (organize_presets->get_active()) {
	reload_combo();
    }
}

bool MyTreeView::on_button_press_event(GdkEventButton* button_event) {
    bool r = Gtk::TreeView::on_button_press_event(button_event);
    m_signal_row_clicked();
    return r;
}

void PresetWindow::load_widget_pointers(Glib::RefPtr<gx_gui::GxBuilder> bld) {
    bld->find_widget("save_preset", save_preset);
    bld->find_widget("new_preset_bank", new_preset_bank);
    bld->find_widget("organize_presets", organize_presets);
    bld->find_widget("online_preset", online_preset);
    bld->find_widget_derived("bank_treeview", bank_treeview, sigc::ptr_fun(MyTreeView::create_from_builder));
    bld->find_object("bank_cellrenderer", bank_cellrenderer);
    bld->find_widget_derived("preset_treeview", preset_treeview, sigc::ptr_fun(MyTreeView::create_from_builder));
    bld->find_object("preset_cellrenderer", preset_cellrenderer);
    bld->find_widget("banks_combobox", banks_combobox);
    bld->find_widget_derived("presets_target_treeview", presets_target_treeview, sigc::ptr_fun(MyTreeView::create_from_builder));
    bld->find_widget("preset_title", preset_title);
    bld->find_widget("presets_target_scrolledbox", presets_target_scrolledbox);
    bld->find_object("bank_column_flags", bank_column_flags);
    bld->find_object("bank_column_bank", bank_column_bank);
    bld->find_object("bank_column_edit", bank_column_edit);
    bld->find_object("bank_column_delete", bank_column_delete);
    bld->find_object("bank_column_spacer", bank_column_spacer);
    bld->find_object("preset_column_preset", preset_column_preset);
    bld->find_object("preset_column_edit", preset_column_edit);
    bld->find_object("preset_column_delete", preset_column_delete);
    bld->find_object("preset_column_spacer", preset_column_spacer);
    bld->find_widget("main_vpaned", main_vpaned);
    bld->find_widget("preset_scrolledbox", preset_scrolledbox);
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
    gx_system::PresetFileGui *f = machine.get_bank_file(nm);
    if (col == bank_column_flags || col == bank_column_bank) {
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
	    } else if (col == bank_column_flags){
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
    } else if (col == bank_column_edit) {
	if (f->get_flags()) {
	    return false;
	}
	tooltip->set_text(_("click to edit the bank name"));
    } else if (col == bank_column_delete) {
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
    bool in_organize = actions.organize->get_active();
    actions.presets->set_active(false);
    if (in_organize) {
	preset_treeview->get_selection()->select(path);
    }
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
    if (info != URILIST_TARGET && info != TEXT_TARGETS) {
	return;
    }
    Gtk::TreeModel::Path path;
    Gtk::TreeViewColumn *focus_column;
    bank_treeview->get_cursor(path, focus_column);
    Glib::RefPtr<Gio::File> f =
	Gio::File::create_for_path(
	    machine.bank_get_filename(
		bank_treeview->get_model()->get_iter(path)->get_value(bank_col.name)));
    if (info == TEXT_TARGETS) {
	selection.set_text(f->get_path());
    } else {
	std::vector<Glib::ustring> uris;
	uris.push_back(f->get_uri());
	selection.set_uris(uris);
    }
}

void PresetWindow::on_bank_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, const Gtk::SelectionData& data, guint info, guint timestamp) {
    if (info != URILIST_TARGET) {
	return;
    }
    bool is_move = context->get_selected_action() == Gdk::ACTION_MOVE;
    bool success = false;
    std::vector<Glib::ustring> uris = data.get_uris();
    Gtk::TreePath pt;
    Gtk::TreeViewDropPosition dst;
    int position = 0;
    if (PresetWindow::bank_find_drop_position(x, y, pt, dst)) {
	position = pt[0];
	if (dst == Gtk::TREE_VIEW_DROP_AFTER) {
	    position += 1;
	}
    }
    for (std::vector<Glib::ustring>::iterator i = uris.begin(); i != uris.end(); ++i) {
	machine.bank_insert_uri(*i, is_move, position);
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
    gx_system::PresetFileGui& fl = *machine.get_bank_file(bank);
    Glib::ustring srcnm = data.get_data_as_string();
    Glib::ustring dstnm = srcnm;
    int n = 1;
    while (fl.has_entry(dstnm)) {
	dstnm = srcnm + "-" + gx_system::to_string(n);
	n += 1;
    }
    Glib::ustring src_bank = get_current_bank();
    gx_system::PresetFileGui& pf = *machine.bank_get_file(src_bank);
    if (src_bank == bank) {
        gx_print_error("preset", "can't copy inside the same bank");
        return;
    }
    Gtk::TreeModel::Path pt;
    Gtk::TreeViewDropPosition dst;
    if (!presets_target_treeview->get_dest_row_at_pos(x, y, pt, dst)) {
	machine.pf_append(pf, srcnm, fl, dstnm);
    } else {
	Gtk::TreeIter it = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(presets_target_treeview->get_model())->get_iter(pt);
	if (dst == Gtk::TREE_VIEW_DROP_BEFORE || dst == Gtk::TREE_VIEW_DROP_INTO_OR_BEFORE) {
	    machine.pf_insert_before(pf, srcnm, fl, it->get_value(target_col.name), dstnm);
	} else { // gtk.TREE_VIEW_DROP_INTO_OR_AFTER, gtk.TREE_VIEW_DROP_AFTER
	    machine.pf_insert_after(pf, srcnm, fl, it->get_value(target_col.name), dstnm);
	}
    }
    if (context->get_actions() == Gdk::ACTION_MOVE) {
	machine.erase_preset(pf, srcnm);
    }
    if (src_bank == bank) {
	on_bank_changed();
    }
}

inline void change_drag_dst_before_or_after(Gtk::TreeViewDropPosition& dst) {
    if (dst == Gtk::TREE_VIEW_DROP_INTO_OR_BEFORE) {
	dst = Gtk::TREE_VIEW_DROP_BEFORE;
    } else if (dst == Gtk::TREE_VIEW_DROP_INTO_OR_AFTER) {
	dst = Gtk::TREE_VIEW_DROP_AFTER;
    }
}

bool PresetWindow::on_target_drag_motion(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, guint timestamp) {
    Gtk::Widget *source_widget = Gtk::Widget::drag_get_source_widget(context);
    if (source_widget != preset_treeview || get_combo_selection().empty()) {
	context->drag_status((Gdk::DragAction)0, timestamp);
	return true;
    }
    presets_target_treeview->on_drag_motion(context, x, y, timestamp);
    Gtk::TreeIter it = get_current_bank_iter();
    int tp = it->get_value(bank_col.tp);
    Glib::ustring nm = it->get_value(bank_col.name);
    if ((tp != gx_system::PresetFile::PRESET_SCRATCH && tp != gx_system::PresetFile::PRESET_FILE) || machine.get_bank_file(nm)->get_flags() ||
	get_combo_selection() == nm) {
	context->drag_status(Gdk::ACTION_COPY, timestamp);
    }
    Gtk::TreeModel::Path pt;
    Gtk::TreeViewDropPosition dst;
    if (presets_target_treeview->get_dest_row_at_pos(x, y, pt, dst)) {
	change_drag_dst_before_or_after(dst);
    } else {
	Gtk::TreeModel::Path start;
	presets_target_treeview->get_visible_range(start, pt);
	dst = Gtk::TREE_VIEW_DROP_AFTER;
    }
    presets_target_treeview->set_drag_dest_row(pt, dst);
    return true;
}

void PresetWindow::reload_combo() {
    Glib::ustring old = get_combo_selection();
    Glib::RefPtr<Gtk::ListStore> ls = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(banks_combobox->get_model());
    ls->clear();
    int n = 0;
    int nn = -1;
    for (gx_engine::bank_iterator i = machine.bank_begin(); i != machine.bank_end(); ++i) {
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
    gx_system::PresetFileGui& f = *machine.get_bank_file(nm);
    for (gx_system::PresetFile::iterator i = f.begin(); i != f.end(); ++i) {
	ls->append()->set_value(bank_col.name, i->name);
    }
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
    dynamic_cast<Gtk::Window*>(main_vpaned->get_toplevel())->remove_accel_group(accelgroup);
}

void PresetWindow::reset_edit(Gtk::TreeViewColumn& col) {
    if (edit_iter) {
	Glib::RefPtr<Gtk::ListStore> ls = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(col.get_tree_view()->get_model());
	ls->erase(edit_iter);
	edit_iter = ls->children().end();
    }
    Gtk::CellRendererText& cell = *dynamic_cast<Gtk::CellRendererText*>(col.get_first_cell());
    cell.property_editable().set_value(false);
    col.set_min_width(0);
    col.queue_resize();
    in_edit = false;
    if (!organize_presets->get_active()) {
        actions.save_changes->set_enabled(true);
    }
    dynamic_cast<Gtk::Window*>(main_vpaned->get_toplevel())->add_accel_group(accelgroup);
}

void PresetWindow::on_edit_canceled(Gtk::TreeViewColumn *col) {
    reset_edit(*col);
}

void PresetWindow::start_edit(const Gtk::TreeModel::Path& pt, Gtk::TreeViewColumn& col, Gtk::CellRenderer& cell) {
    col.set_min_width(100);
    dynamic_cast<Gtk::CellRendererText*>(&cell)->property_editable().set_value(true);
    col.get_tree_view()->set_cursor(pt, col, cell, true);
}

/*
 ** list of banks
 */

void PresetWindow::set_cell_text(Gtk::Widget *widget, Gtk::CellRenderer *cell, const Glib::ustring& text, bool selected) {
    cell->set_property("text", text);
    Gtk::CellRendererText *tc = dynamic_cast<Gtk::CellRendererText*>(cell);
    Glib::RefPtr<Gtk::StyleContext> context = widget->get_style_context();
    Gtk::StateFlags state_flag = selected ? Gtk::STATE_FLAG_CHECKED : Gtk::STATE_FLAG_NORMAL;
	
    tc->property_foreground_rgba().set_value(
        context->get_color(state_flag));

    Pango::FontDescription font = context->get_font(state_flag);
    tc->property_weight().set_value(font.get_weight());
}

void PresetWindow::highlight_current_bank(Gtk::CellRenderer *cell, const Gtk::TreeModel::iterator& iter) {
    Glib::ustring t = iter->get_value(bank_col.name);
    if (t.empty()) {
        return;
    }
    bool selected = (machine.setting_is_preset() && t == machine.get_current_bank());
    if (!organize_presets->get_active()) {
        int idx = *bank_treeview->get_model()->get_path(iter).begin();
        if (machine.get_bank_file(t)->get_type() & gx_system::PresetFile::PRESET_FACTORY) {
            // correction for separator before factory rows
            idx -= 1;
        }
        char c = KeySwitcher::bank_idx_to_char(idx, machine.bank_size());
        if (c) {
            t = Glib::ustring::compose("%1:  %2", c, t);
        } else {
            t = "    " + t;
        }
    }
    set_cell_text(bank_treeview, cell, t, selected);
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
    if (nm.empty()) return false;
    int tp = it->get_value(bank_col.tp);
    if (col == bank_column_flags) {
	if (tp == gx_system::PresetFile::PRESET_SCRATCH || tp == gx_system::PresetFile::PRESET_FILE) {
	    int flags = machine.get_bank_file(nm)->get_flags();
	    gx_system::PresetFileGui *f = machine.get_bank_file(nm);
	    if (flags == 0 && tp == gx_system::PresetFile::PRESET_FILE) {
		/*if (run_message_dialog(*bank_treeview, "set bank " + nm + " to readonly?")) {*/
		machine.bank_set_flag(f, gx_system::PRESET_FLAG_READONLY, true);
	    } else if (flags == gx_system::PRESET_FLAG_VERSIONDIFF) {
		if (run_message_dialog(*bank_treeview, "convert bank " + nm + " to new version?")) {
		    machine.convert_preset(*f);
		}
	    } else if (flags == gx_system::PRESET_FLAG_READONLY) {
		/*if (run_message_dialog(*bank_treeview, "set bank " + nm + " to read/write?")) {*/
		machine.bank_set_flag(f, gx_system::PRESET_FLAG_READONLY, false);
	    } else if (flags == (gx_system::PRESET_FLAG_READONLY | gx_system::PRESET_FLAG_VERSIONDIFF)) {
		if (run_message_dialog(*bank_treeview, "convert readonly bank " + nm + " to new version?")) {
		    machine.convert_preset(*f);
		}
	    } else if (flags & gx_system::PRESET_FLAG_INVALID) {
		if (run_message_dialog(
			*bank_treeview, "delete damaged bank " + nm + "?"
			" Export it before deleting and ask in the"
			" guitarix online forum if you want to try to repair it!")) {
		    machine.bank_remove(nm);
		}
	    }
	}
	return false;
    }
    if (tp != gx_system::PresetFile::PRESET_FILE || machine.get_bank_file(nm)->get_flags()) {
	return false;
    }
    if (col == bank_column_edit) {
	start_edit(pt, *bank_column_bank, *bank_cellrenderer);
    } else if (col == bank_column_delete) {
	Gtk::MessageDialog d(*dynamic_cast<Gtk::Window*>(bank_treeview->get_toplevel()), "delete bank " + nm + "?", false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_OK_CANCEL, true);
	d.set_position(Gtk::WIN_POS_MOUSE);
	if (d.run() == Gtk::RESPONSE_OK) {
	    machine.bank_remove(nm);
	}
    }
    return false;
}

void PresetWindow::on_bank_edited(const Glib::ustring& path, const Glib::ustring& newtext, Gtk::TreeView* w) {
    Gtk::TreeIter sel = w->get_model()->get_iter(path);
    Glib::ustring oldname = sel->get_value(bank_col.name);
    Glib::ustring newname = newtext;
    gx_system::strip(newname);
    if (newname.empty() || newname == oldname) {
        reset_edit(*bank_column_bank);
        return;
    }
    Glib::RefPtr<Gtk::ListStore> ls = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(banks_combobox->get_model());
    if (edit_iter) {
        edit_iter = Gtk::TreeIter();
        machine.bank_insert_new(newname);
    } else {
        machine.rename_bank(oldname, newname);
    }
    reset_edit(*bank_column_bank);
}

bool PresetWindow::is_row_separator(const Glib::RefPtr<Gtk::TreeModel>& model, const Gtk::TreeModel::iterator& iter) {
    return iter->get_value(bank_col.tp) == gx_system::PresetFile::PRESET_SEP;
}

void PresetWindow::on_new_bank() {
    Glib::RefPtr<Gtk::ListStore> m = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(bank_treeview->get_model());
    edit_iter = m->prepend();
    edit_iter->set_value(bank_col.tp, static_cast<int>(gx_system::PresetFile::PRESET_FILE));
    in_edit = true;
    start_edit(m->get_path(edit_iter), *bank_column_bank, *bank_cellrenderer);
}

// Online Preset Downloader

Glib::ustring PresetWindow::resolve_hostname() {
    static Glib::ustring hostname = "localhost";
    if (! machine.get_jack()) {
        hostname = Gio::Resolver::get_default()->lookup_by_address
        (Gio::InetAddress::create( machine.get_options().get_rpcaddress()));
    }
    return hostname;
}

bool PresetWindow::download_file(Glib::ustring from_uri, Glib::ustring to_path) {

    CURLcode res;
    FILE *out;
    out = fopen(to_path.c_str(), "wb");
  
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, out);
    curl_easy_setopt(curl, CURLOPT_URL, from_uri.c_str());
    res = curl_easy_perform(curl);
    if(CURLE_OK == res) {
        char *ct = NULL;
        res = curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &ct);
        if (strstr(ct, "application/json")!= NULL ) {
            gx_print_info( "download_file", from_uri);
        } else if (strstr(ct, "application/octet-stream")!= NULL) {
             gx_print_info( "download_preset", from_uri);
        } else {
           res = CURLE_CONV_FAILED;
        }
    }
    curl_easy_reset(curl);
    fclose(out);
    if(res != CURLE_OK) {
        remove(to_path.c_str());
        gx_print_error( "download_file", Glib::ustring::compose("curl_easy_perform() failed: %1", curl_easy_strerror(res)));
        return false;
    }
    return true;
}

void PresetWindow::downloadPreset(Gtk::Menu *presetMenu,std::string uri) {

    std::string::size_type n = uri.find_last_of('/');
    if (n != std::string::npos) {
        std::string fn = uri.substr(n);
        std::string ff = "/tmp"+fn;

        if (download_file(uri, ff)) {
            Glib::RefPtr<Gtk::ListStore> ls = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(bank_treeview->get_model());
            machine.bank_insert_uri(Glib::filename_to_uri(ff, resolve_hostname()), false, 0);
        }
    } else {
        gx_print_error("downloadPreset", _("can't download preset from https://musical-artifacts.com/"));
    }
}

void PresetWindow::read_preset_menu() {
    ifstream is(options.get_online_config_filename());
    gx_system::JsonParser jp(&is);
    try {
	jp.next(gx_system::JsonParser::begin_array);
	do {
	    std::string NAME_;
	    std::string FILE_;
	    std::string INFO_;
	    std::string AUTHOR_;
	    jp.next(gx_system::JsonParser::begin_object);
	    do {
		jp.next(gx_system::JsonParser::value_key);
		if (jp.current_value() == "name") {
		    jp.read_kv("name", NAME_);
		} else if (jp.current_value() == "description") {
		    jp.read_kv("description", INFO_);
		} else if (jp.current_value() == "author") {
		    jp.read_kv("author", AUTHOR_);
		} else if (jp.current_value() == "file") {
		    jp.read_kv("file", FILE_);
		} else {
		    jp.skip_object();
		}
	    } while (jp.peek() == gx_system::JsonParser::value_key);
	    jp.next(gx_system::JsonParser::end_object);
	    INFO_ += "Author : " + AUTHOR_;
	    olp.push_back(std::tuple<std::string,std::string,std::string>(NAME_,FILE_,INFO_));
	} while (jp.peek() == gx_system::JsonParser::begin_object);
    } catch (gx_system::JsonException& e) {
	cerr << "JsonException: " << e.what() << ": '" << jp.current_value() << "'" << endl;
	assert(false);
    }
}

void PresetWindow::popup_pos( int& x, int& y, bool& push_in ){
    online_preset->get_window()->get_origin( x, y );
    x +=150;
    y -= 450;
    push_in = false;
}
 
void PresetWindow::create_preset_menu() {

    static bool read_new = true;
    if (read_new) {
        read_preset_menu();
        read_new = false;
    }

    Gtk::MenuItem* item;
    Gtk::Menu *presetMenu = Gtk::manage(new Gtk::Menu());
    presetMenu->set_size_request (-1, 600);
    for(std::vector<std::tuple<std::string,std::string,std::string> >::iterator it = olp.begin(); it != olp.end(); it++) {
        item = Gtk::manage(new Gtk::MenuItem(get<0>(*it), true));
        item->set_tooltip_text(get<2>(*it));
        std::string f = get<1>(*it);
        item->signal_activate().connect(
            sigc::bind(sigc::mem_fun(*this, &PresetWindow::downloadPreset),
		       presetMenu, f));
        presetMenu->append(*item);
    }
    presetMenu->show_all();
    presetMenu->popup(Gtk::Menu::SlotPositionCalc(sigc::mem_fun(
       *this, &PresetWindow::popup_pos ) ),0,gtk_get_current_event_time());
}

void PresetWindow::show_online_preset() {
    static bool load_new = true;
    Glib::RefPtr<Gio::File> dest = Gio::File::create_for_path(options.get_online_config_filename());
    bool exists = dest->query_exists();
    if (load_new || !exists) {
	load_new = false;
	bool reload = false;
	gx_gui::WaitCursor(dynamic_cast<Gtk::Window*>(main_vpaned->get_toplevel()));
        if (exists) {
            Gtk::MessageDialog d(*dynamic_cast<Gtk::Window*>(online_preset->get_toplevel()),
				 "Do you want to check for new presets from\n https://musical-artifacts.com ?\n"
				 "Note, that may take a while",
				 false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_YES_NO, true);
            d.set_position(Gtk::WIN_POS_MOUSE);
            if (d.run() == Gtk::RESPONSE_YES) {
		reload = true;
	    }
        }
	if (!exists || reload) {
	    if (!download_file("https://musical-artifacts.com/artifacts.json?apps=guitarix&formats=gx", options.get_online_config_filename())) {
		return;
	    }
	}
    }
    create_preset_menu();
}

void PresetWindow::on_online_preset() {
    Glib::signal_idle().connect_once(sigc::mem_fun(*this, &PresetWindow::show_online_preset));
}

bool PresetWindow::bank_drag_moveable(Gtk::TreePath pt) {
    if (!pt) {
	return false;
    }
    Gtk::TreeIter it = bank_treeview->get_model()->get_iter(pt);
    if (!it) {
	return false;
    }
    string nm = it->get_value(bank_col.name);
    if (nm.empty()) {
	return false;
    }
    return machine.get_bank_file(nm)->is_moveable();
}

bool PresetWindow::bank_find_drop_position(int x, int y, Gtk::TreeModel::Path& pt, Gtk::TreeViewDropPosition& dst) {
    if (bank_treeview->get_dest_row_at_pos(x, y, pt, dst)) {
	change_drag_dst_before_or_after(dst);
    } else {
	Gtk::TreeModel::Path start;
	preset_treeview->get_visible_range(start, pt);
	dst = Gtk::TREE_VIEW_DROP_AFTER;
    }
    if (!bank_drag_moveable(pt)) {
	if (dst == Gtk::TREE_VIEW_DROP_AFTER) {
	    pt.next();
	    if (bank_drag_moveable(pt)) {
		dst = Gtk::TREE_VIEW_DROP_BEFORE;
	    } else {
		return false;
	    }
	} else {
	    if (pt.prev()) {
		if (bank_drag_moveable(pt)) {
		    dst = Gtk::TREE_VIEW_DROP_AFTER;
		} else {
		    return false;
		}
	    }
	}
    }
    return true;
}

bool PresetWindow::on_bank_drag_motion(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, guint timestamp) {
    Gtk::Widget *source_widget = Gtk::Widget::drag_get_source_widget(context);
    if (source_widget && source_widget != bank_treeview) {
	// other window
	context->drag_status((Gdk::DragAction)0, timestamp);
	return true;
    }
    Gdk::DragAction action;
    if (!source_widget) {
	// URI from other application
	if (context->get_suggested_action() & Gdk::ACTION_MOVE) {
	    action = Gdk::ACTION_MOVE;
	} else {
	    action = Gdk::ACTION_COPY;
	}
    } else {
	// reorder
	Gtk::TreeIter it = get_current_bank_iter();
	if (!it) {
	    // unknown source drag bank
	    context->drag_status((Gdk::DragAction)0, timestamp);
	    return true;
	}
	if (!machine.get_bank_file(it->get_value(bank_col.name))->is_moveable()) {
	    context->drag_status((Gdk::DragAction)0, timestamp);
	    return true;
	}
	action = Gdk::ACTION_MOVE;
    }
    Gtk::TreeModel::Path pt;
    Gtk::TreeViewDropPosition dst;
    if (PresetWindow::bank_find_drop_position(x, y, pt, dst)) {
	bank_treeview->set_drag_dest_row(pt, dst);
    } else {
	action = (Gdk::DragAction)0;
	bank_treeview->unset_drag_dest_row();
    }
    context->drag_status(action, timestamp);
    return true;
}

void PresetWindow::on_bank_changed() {
    if (load_in_progress) {
	return;
    }
    load_in_progress = true;
    pstore->clear();
    Gtk::TreeIter it = get_current_bank_iter();
    if (!it) {
	preset_title->set_text("");
	in_current_preset = false;
	load_in_progress = false;
	return;
    }
    Glib::ustring nm = it->get_value(bank_col.name);
    preset_title->set_text(nm);
    in_current_preset = (nm == machine.get_current_bank());
    Gtk::TreeIter i;
    gx_system::PresetFileGui& ll = *machine.get_bank_file(nm);
    if ((ll.get_flags() & gx_system::PRESET_FLAG_VERSIONDIFF) ||
	((ll.get_flags() & gx_system::PRESET_FLAG_READONLY) && !actions.organize->get_active())) {
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
    Gtk::TreeIter first_row;
    Gtk::TreePath sel_path;
    for (gx_system::PresetFile::iterator s = ll.begin(); s != ll.end(); ++s) {
	i = pstore->append();
	if (!first_row) {
	    first_row = i;
	}
	i->set_value(pstore->col.name, s->name);
	if (modifiable) {
	    i->set_value(pstore->col.edit_pb, pb_edit);
	    i->set_value(pstore->col.del_pb, pb_del);
	}
	if (in_current_preset && s->name == machine.get_current_name()) {
	    if (preset_treeview->get_mapped()) {
		sel_path = pstore->get_path(i);
	    }
	}
    }
    if (modifiable) {
	i = pstore->append();
	if (!first_row) {
	    first_row = i;
	}
    }
    if (first_row) {
	// when the treeview widget gets the focus with no cursor set,
	// it will automatically be set on the first row and trigger a
	// selection of the first list entry. So the side effect will
	// be that unexpectedly the first preset will be set if one
	// clicks on some inactive part of the widget. So make sure
	// the cursor is set:
	preset_treeview->set_cursor(pstore->get_path(first_row));
	preset_treeview->get_selection()->unselect(first_row);
    }
    if (sel_path) {
	preset_treeview->scroll_to_row(sel_path);
    }
    load_in_progress = false;
}

void PresetWindow::set_row_for_presetfile(Gtk::TreeIter i, gx_system::PresetFileGui *f) {
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

// row deleted in model of bank_treeview
void PresetWindow::on_bank_reordered(const Gtk::TreeModel::Path& path) {
    if (load_in_progress) {
	return;
    }
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
    machine.bank_reorder(l);
}

/*
 ** list of presets
 */

void PresetWindow::text_func(Gtk::CellRenderer *cell, const Gtk::TreeModel::iterator& iter) {
    Glib::ustring val = iter->get_value(pstore->col.name);
    Glib::ustring t = val;
    if (t.empty() && !cell->property_editing().get_value()) {
        t = "<new>";
    } else if (in_current_preset && !organize_presets->get_active()) {
        char c = KeySwitcher::idx_to_char(*pstore->get_path(iter).begin());
        if (c) {
            t = Glib::ustring::compose("%1:  %2", c, t);
        } else {
            t = "    " + t;
        }
    }
    bool selected = (in_current_preset && machine.setting_is_preset() && val == machine.get_current_name());
    set_cell_text(preset_treeview, cell, t, selected);
}

/*
 * button-release event handler for preset_treeview
 * edit and delete actions
 * maybe better done by setting the CellRenderer mode property
 */
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
    if (col != focus_column || !path || pt != path) {
	return false;
    }
    Gtk::TreeIter bank_iter = get_current_bank_iter();
    int tp = bank_iter->get_value(bank_col.tp);
    if ((tp != gx_system::PresetFile::PRESET_SCRATCH && tp != gx_system::PresetFile::PRESET_FILE)
	|| machine.get_bank_file(bank_iter->get_value(bank_col.name))->get_flags()) {
	return false;
    }
    Glib::ustring nm = pstore->get_iter(pt)->get_value(pstore->col.name);
    if (nm.empty()) {  // "<new>"
	if (col == preset_column_preset) {
        if (!organize_presets->get_active()) {
            Glib::RefPtr<Gtk::TreeSelection> sel = preset_treeview->get_selection();
            sel->set_mode(Gtk::SELECTION_SINGLE);
            actions.save_changes->set_enabled(false);
        }
	    start_edit(pt, *preset_column_preset, *preset_cellrenderer);
	}
	return false;
    }
    if (col == preset_column_edit) {
	start_edit(pt, *preset_column_preset, *preset_cellrenderer);
    } else if (col == preset_column_delete) {
	Gtk::MessageDialog d(*dynamic_cast<Gtk::Window*>(preset_treeview->get_toplevel()),
			     Glib::ustring::compose("delete preset %1?", nm), false,
			     Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_OK_CANCEL, true);
	d.set_position(Gtk::WIN_POS_MOUSE);
	if (d.run() == Gtk::RESPONSE_OK) {
	    machine.erase_preset(*machine.get_bank_file(bank_iter->get_value(bank_col.name)), nm);
	}
    }
    return false;
}

void PresetWindow::on_preset_edited(const Glib::ustring& path, const Glib::ustring& newtext) {
    Gtk::TreeIter it = pstore->get_iter(path);
    Glib::ustring oldname = it->get_value(pstore->col.name);
    Glib::ustring newname = newtext;
    gx_system::strip(newname);
    if (newname.empty() || newname == oldname) {
	reset_edit(*preset_column_preset);
	return;
    }
    gx_system::PresetFileGui& fl = *machine.get_bank_file(get_current_bank());
    Glib::ustring t = newname;
    int n = 1;
    while (fl.has_entry(newname)) {
	newname = Glib::ustring::compose("%1-%2", t, n);
	n += 1;
    }
    it->set_value(pstore->col.name, newname);
    it->set_value(pstore->col.edit_pb, pb_edit);
    it->set_value(pstore->col.del_pb, pb_del);
    if (oldname.empty()) {
        // check if current preset is scratch and needs to be saved
        if (!machine.get_current_bank().empty()) {
	    gx_system::PresetFileGui *cpf = machine.get_bank_file(machine.get_current_bank());
	    if (cpf && cpf->has_entry(machine.get_current_name())) {
	        if (cpf->get_type() == gx_system::PresetFile::PRESET_SCRATCH && cpf->is_mutable()) {
		    machine.pf_save(*cpf, machine.get_current_name());
		}
	    }
	}
	pstore->append();
	machine.pf_save(fl, newname);
    } else {
	machine.rename_preset(fl, oldname, newname);
    }
    reset_edit(*preset_column_preset);
}

bool PresetWindow::on_preset_drag_motion(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, guint timestamp) {
    if (Gtk::Widget::drag_get_source_widget(context) == preset_treeview) {
	Gtk::TreeIter it = get_current_bank_iter();
	if (it && (machine.get_bank_file(it->get_value(bank_col.name))->is_mutable())) {
	    preset_treeview->on_drag_motion(context, x, y, timestamp);
	    Gtk::TreeModel::Path pt;
	    Gtk::TreeViewDropPosition dst;
	    if (preset_treeview->get_dest_row_at_pos(x, y, pt, dst)) {
		if (pstore->get_iter(pt)->get_value(pstore->col.name).empty()) {
		    dst = Gtk::TREE_VIEW_DROP_BEFORE;
		}
		change_drag_dst_before_or_after(dst);
	    } else {
		Gtk::TreeModel::Path start;
		preset_treeview->get_visible_range(start, pt);
		dst = Gtk::TREE_VIEW_DROP_BEFORE;
	    }
	    preset_treeview->set_drag_dest_row(pt, dst);
	    context->drag_status(Gdk::ACTION_MOVE, timestamp);
	    return true;
	}
    }
    context->drag_status((Gdk::DragAction)0, timestamp);
    return true;
}

void PresetWindow::on_preset_reordered(const Gtk::TreeModel::Path& path) {
    // save changed order to file
    if (load_in_progress) {
	return;
    }
    Gtk::TreeModel::Children ch = pstore->children();
    std::vector<Glib::ustring> l;
    for (Gtk::TreeIter i = ch.begin(); i != ch.end(); ++i) {
	Glib::ustring s = i->get_value(pstore->col.name);
	if (!s.empty()) {
	    l.push_back(s);
	}
    }
    machine.reorder_preset(*machine.get_bank_file(get_current_bank()), l);
}

void PresetWindow::autosize() {
    if (bank_treeview->get_mapped()) {
	bank_treeview->columns_autosize();
	preset_treeview->columns_autosize();
    }
}

void PresetWindow::on_organize() {
    bool v = organize_presets->get_active();
    bank_column_edit->set_visible(v);
    bank_column_delete->set_visible(v);
    bank_column_spacer->set_visible(v);
    preset_column_edit->set_visible(v);
    preset_column_delete->set_visible(v);
    preset_column_spacer->set_visible(v);
    Glib::RefPtr<Gtk::TreeSelection> sel = preset_treeview->get_selection();
    if (v) {
	actions.presets->set_active(true);
	reload_combo();
	sel->set_mode(Gtk::SELECTION_NONE);
	banks_combobox->set_active(-1);
	banks_combobox->show();
	presets_target_scrolledbox->show();
	actions.save_changes->set_enabled(false);
    } else {
	sel->set_mode(Gtk::SELECTION_SINGLE);
	banks_combobox->hide();
	presets_target_scrolledbox->hide();
	if (machine.setting_is_preset()) {
	    if (machine.get_bank_file(machine.get_current_bank())->is_mutable()) {
		actions.save_changes->set_enabled(true);
	    }
	}
    }
    on_bank_changed(); // reload for DnD adjustment of readonly banks
    autosize();
    // strange bug in Gtk (V3.24): preset treeview with apparently
    // wrong internal sizes on first switch after program start
    // a delayed resize operation seems to fix it
    Gtk::Widget *toplevel = main_vpaned->get_toplevel();
    Glib::signal_idle().connect_once(
        sigc::mem_fun(toplevel, &Gtk::Widget::queue_resize),
        Glib::PRIORITY_LOW);
}

/*
 ** preset window
 */

bool PresetWindow::animate_preset_show() {
    vpaned_pos -= vpaned_step;
    if (vpaned_pos <= vpaned_target) {
	main_vpaned->set_position(vpaned_target);
	gx_gui::child_set_property(*main_vpaned, *preset_scrolledbox, "shrink", false);
	Gtk::TreeIter it = get_current_bank_iter();
	if (it) {
	    bank_treeview->scroll_to_row(bank_treeview->get_model()->get_path(it));
	}
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

void PresetWindow::on_preset_changed() {
    if (load_in_progress) {
	return;
    }
    if (actions.organize->get_active()) {
	return;
    }
    Glib::ustring bank = get_current_bank();
    if (bank.empty()) {
	return;
    }
    Gtk::TreeIter it = preset_treeview->get_selection()->get_selected();
    if (!it) {
	return;
    }
    Glib::ustring name = it->get_value(pstore->col.name);
    bool is_scratch = false;
    gx_system::PresetFileGui *cpf = 0;
    if (!machine.get_current_bank().empty()) {
	cpf = machine.get_bank_file(machine.get_current_bank());
	if (cpf && cpf->has_entry(machine.get_current_name())) {
	    is_scratch = (cpf->get_type() == gx_system::PresetFile::PRESET_SCRATCH);
	}
    }
    if (is_scratch) {
	if (bank == machine.get_current_bank() && name == machine.get_current_name()) {
	    machine.pf_save(*cpf, machine.get_current_name());
	    // no reload necessary
	    return;
	}
    }
    in_current_preset = true;
    cpf = machine.get_bank_file(bank);
    machine.load_preset(cpf, name);
}

void PresetWindow::on_preset_save() {
    if (!machine.setting_is_preset()) {
	return;
    }
    gx_system::PresetFileGui *pf = machine.get_bank_file(machine.get_current_bank());
    if (!pf->is_mutable()) {
	return;
    }
    machine.pf_save(*pf, machine.get_current_name());
}

void PresetWindow::display_paned(bool show_preset, int paned_child_height) {
    on_map_conn.disconnect();
    if (preset_scrolledbox->get_parent() == main_vpaned) {
	vpaned_pos = main_vpaned->get_allocation().get_height();
	int h;
	h = main_vpaned->get_handle_window()->get_height();
	vpaned_target = vpaned_pos - paned_child_height - h;
	main_vpaned->set_position(vpaned_target);
	gx_gui::child_set_property(*main_vpaned, *preset_scrolledbox, "shrink", false);
    }
    preset_scrolledbox->show();
    if (!show_preset || !in_current_preset) {
	return;
    }
    // make the current entry in the preset list window
    // visible (in case it's outside the displayed range).
    // apparently only works after the window is mapped
    // and some size calculations are done, so put it into
    // an idle handler.
    Gtk::TreeIter it = get_current_bank_iter();
    if (it) {
	Glib::signal_idle().connect_once(
	    sigc::bind(
		sigc::mem_fun1(bank_treeview, &MyTreeView::scroll_to_row),
		bank_treeview->get_model()->get_path(it)));
    }
    Gtk::TreeNodeChildren ch = pstore->children();
    for (it = ch.begin(); it != ch.end(); ++it) {
	if (it->get_value(pstore->col.name) == machine.get_current_name()) {
	    Glib::signal_idle().connect_once(
		sigc::bind(
		    sigc::mem_fun1(*preset_treeview, &MyTreeView::scroll_to_row),
		    pstore->get_path(it)));
	    break;
	}
    }
}

// open the preset selection pane
void PresetWindow::on_preset_select(bool v, bool animated, int paned_child_height) {
    static bool first_time = true;
    if (first_time) {
        //FIXME needed to fix first time display height, not clear why
        paned_child_height += 4;
        first_time = false;
    }
    // (margin.top + margin.bottom) of the GtkPaned css node "separator"
    // there doesn't seem to be a way to get this value with Gtk3
    // see also the guitarix scss style file
    const int paned_sep_margin_top_bottom = -8;
    paned_child_height += paned_sep_margin_top_bottom;

    on_map_conn.disconnect();
    bool is_mapped = main_vpaned->get_toplevel()->get_mapped();
    bool rack_visible = actions.show_rack->get_active();
    if (v) {
	if (machine.bank_check_reparse()) {
	    on_presetlist_changed();
	} else if (!get_current_bank_iter()) {
	    on_presetlist_changed();
	}
	autosize();
	Gtk::TreeIter it = get_current_bank_iter();
	if (it && animated && is_mapped) {
	    bank_treeview->scroll_to_row(bank_treeview->get_model()->get_path(it));
	}
	if (!is_mapped) {
	    // don't have widget height to calculate paned separator
	    // position before window is mapped
	    on_map_conn = main_vpaned->get_toplevel()->signal_map().connect(
		sigc::bind(sigc::mem_fun(*this, &PresetWindow::display_paned), true, paned_child_height));
	} else if (animated && rack_visible) {
	    gx_gui::child_set_property(*main_vpaned, *preset_scrolledbox, "shrink", true);
	    vpaned_pos = main_vpaned->get_allocation().get_height();
	    int h;
	    h = main_vpaned->get_handle_window()->get_height();
	    vpaned_target = vpaned_pos - paned_child_height - h;
	    main_vpaned->set_position(vpaned_pos);
	    vpaned_step = paned_child_height / 5;
	    preset_scrolledbox->show();
	    animate_preset_show();
	    Glib::signal_timeout().connect(sigc::mem_fun(*this, &PresetWindow::animate_preset_show), 20);
	} else {
	    display_paned(false, paned_child_height);
	}
    } else {
	vpaned_target = main_vpaned->get_allocation().get_height();
	vpaned_pos = main_vpaned->get_position();
	if (animated && is_mapped && rack_visible) {
	    vpaned_step = paned_child_height / 5;
	    gx_gui::child_set_property(*main_vpaned, *preset_scrolledbox, "shrink", true);
	    Glib::signal_timeout().connect(sigc::mem_fun(*this, &PresetWindow::animate_preset_hide), 20);
	} else {
	    preset_scrolledbox->hide();
	}
	actions.organize->set_active(false);
    }
}
