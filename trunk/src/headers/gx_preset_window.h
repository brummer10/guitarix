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

/****************************************************************
 ** class PresetWindow
 */


class PresetStore: public Gtk::ListStore {
public:
    class PresetModelColumns : public Gtk::TreeModel::ColumnRecord {
    public:
	Gtk::TreeModelColumn<Glib::ustring> name;
	Gtk::TreeModelColumn< Glib::RefPtr<Gdk::Pixbuf> > edit_pb;
	Gtk::TreeModelColumn< Glib::RefPtr<Gdk::Pixbuf> > del_pb;

	PresetModelColumns() { add(name); add(edit_pb); add(del_pb); }
    } col;
public:
    PresetStore();
    virtual bool row_draggable_vfunc(const TreeModel::Path& path) const;
};

class TargetModelColumns : public Gtk::TreeModel::ColumnRecord {
public:
    Gtk::TreeModelColumn<Glib::ustring> name;
    TargetModelColumns() { add(name); }
};

class BankModelColumns : public Gtk::TreeModel::ColumnRecord {
public:
    Gtk::TreeModelColumn<Glib::ustring> name;
    Gtk::TreeModelColumn< Glib::RefPtr<Gdk::Pixbuf> > type_pb;
    Gtk::TreeModelColumn< Glib::RefPtr<Gdk::Pixbuf> > edit_pb;
    Gtk::TreeModelColumn< Glib::RefPtr<Gdk::Pixbuf> > del_pb;
    Gtk::TreeModelColumn<int> tp;
    BankModelColumns() { add(name); add(type_pb); add(edit_pb); add(del_pb); add(tp); }
};

class MyTreeView: public Gtk::TreeView {
private:
    MyTreeView(BaseObjectType* cobject): Gtk::TreeView(cobject) {}
public:
    static MyTreeView *create_from_builder(BaseObjectType* cobject) { return new MyTreeView(cobject); }
    //virtual bool on_drag_motion(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, guint timestamp);
    using Gtk::TreeView::on_drag_motion;
};

struct GxActions;

class PresetWindow: public sigc::trackable {
private:
    enum {
	TEXT_TARGETS = 0,
	MODELROW_TARGET = 1,
	URILIST_TARGET = 2,
    };
    gx_engine::GxMachineBase& machine;
    GxActions& actions;
    CURL *curl;
    bool in_edit;
    Gtk::TreeModel::iterator edit_iter;
    Glib::RefPtr<Gdk::Pixbuf> pb_edit;
    Glib::RefPtr<Gdk::Pixbuf> pb_del;
    Glib::RefPtr<Gdk::Pixbuf> pb_scratch;
    Glib::RefPtr<Gdk::Pixbuf> pb_versiondiff;
    Glib::RefPtr<Gdk::Pixbuf> pb_readonly;
    Glib::RefPtr<Gdk::Pixbuf> pb_factory;
    Glib::RefPtr<PresetStore> pstore;
    TargetModelColumns target_col;
    BankModelColumns bank_col;
    sigc::connection bank_row_del_conn;
    sigc::connection preset_row_del_conn;
    int vpaned_pos;
    int vpaned_step;
    int vpaned_target;
    const gx_system::CmdlineOptions& options;
    bool in_current_preset;
    sigc::connection on_map_conn;

    // widget pointers (keep last)
    Gtk::Button *close_preset;
    Gtk::Button *save_preset;
    Gtk::Button *new_preset_bank;
    Gtk::ToggleButton *organize_presets;
    Gtk::Button *online_preset;
    MyTreeView *bank_treeview;
    Glib::RefPtr<Gtk::CellRendererText> bank_cellrenderer;
    MyTreeView *preset_treeview;
    Glib::RefPtr<Gtk::CellRendererText> preset_cellrenderer;
    Gtk::ComboBox *banks_combobox;
    MyTreeView *presets_target_treeview;
    Gtk::Label *preset_title;
    Gtk::ScrolledWindow *presets_target_scrolledbox;
    Glib::RefPtr<Gtk::TreeViewColumn> bank_column_edit;
    Glib::RefPtr<Gtk::TreeViewColumn> bank_column_delete;
    Glib::RefPtr<Gtk::TreeViewColumn> preset_column_edit;
    Glib::RefPtr<Gtk::TreeViewColumn> preset_column_delete;
    Gtk::VPaned *main_vpaned;
    Gtk::ScrolledWindow *preset_scrolledbox;
    GtkSizeGroup *left_column;
private:
    void load_widget_pointers(Glib::RefPtr<gx_gui::GxBuilder> bld);
    void target_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, const Gtk::SelectionData& data, guint info, guint timestamp);
    bool on_target_drag_motion(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, guint timestamp);
    Glib::ustring get_combo_selection();
    void reload_combo();
    void on_preset_combo_changed();
    void reload_target();
    bool select_func(const Glib::RefPtr<Gtk::TreeModel>& model, const Gtk::TreePath& path, bool path_currently_selected);
    void highlight_current_bank(Gtk::CellRenderer *cell, const Gtk::TreeModel::iterator& iter);
    void text_func(Gtk::CellRenderer *cell, const Gtk::TreeModel::iterator& iter);
    void on_editing_started(const Gtk::CellEditable* edit, const Glib::ustring& path, Glib::RefPtr<Gtk::TreeModel>& model);
    bool edit_cell(Gtk::TreeModel::Path pt, Gtk::TreeViewColumn& col, Gtk::CellRenderer& cell);
    void reset_edit(Gtk::TreeViewColumn& col);
    void on_edit_canceled(Gtk::TreeViewColumn *col);
    void start_edit(const Gtk::TreeModel::Path& pt, Gtk::TreeViewColumn& col, Gtk::CellRenderer& cell);
    Gtk::TreeIter get_current_bank_iter() { return bank_treeview->get_selection()->get_selected(); }
    Glib::ustring get_current_bank();
    bool run_message_dialog(Gtk::Widget& w, const Glib::ustring& msg);
    bool on_bank_button_release(GdkEventButton *ev);
    void on_bank_edited(const Glib::ustring& path, const Glib::ustring& newtext, Gtk::TreeView* w);
    bool is_row_separator(const Glib::RefPtr<Gtk::TreeModel>& model, const Gtk::TreeModel::iterator& iter);
    void on_new_bank();
    void on_preset_save();
    const std::string pdir() { return options.get_preset_dir();}
    void on_online_preset();
    void replace_inline(std::string& l, const std::string& s, const std::string& r);
    void show_online_preset();
    void popup_pos( int& x, int& y, bool& push_in );
    void downloadPreset(Gtk::Menu *presetMenu,std::string uri);
    bool download_file(Glib::ustring from_uri, Glib::ustring to_path);
    Glib::ustring resolve_hostname();
    void create_preset_menu(bool is_new);
    void read_preset_menu();
    std::vector< std::tuple<std::string,std::string,std::string> > olp;
    bool on_bank_drag_motion(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, guint timestamp);
    void on_bank_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, const Gtk::SelectionData& data, guint info, guint timestamp);
    void on_bank_drag_data_get(const Glib::RefPtr<Gdk::DragContext>& context, Gtk::SelectionData& selection, int info, int timestamp);
    void on_bank_changed();
    bool on_bank_query_tooltip(int x, int y, bool kb_tooltip, Glib::RefPtr<Gtk::Tooltip> tooltip);
    void reload_banks(const Glib::ustring& sel_bank);
    void set_presets();
    void on_bank_reordered(const Gtk::TreeModel::Path& path);
    bool on_preset_button_release(GdkEventButton *ev);
    bool on_preset_button_press(GdkEventButton *ev);
    void on_preset_row_activated(const Gtk::TreePath& path, Gtk::TreeViewColumn* column);
    void on_preset_edited(const Glib::ustring& path, const Glib::ustring& newtext);
    void on_cursor_changed();
    void on_preset_changed();
    bool on_preset_drag_motion(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, guint timestamp);
    void on_preset_drag_data_get(const Glib::RefPtr<Gdk::DragContext>& context, Gtk::SelectionData& selection, int info, int timestamp);
    void on_preset_reordered(const Gtk::TreeModel::Path& path);
    void autosize();
    void on_organize();
    void on_presets_close();
    bool animate_preset_show();
    bool animate_preset_hide();
    void set_row_for_presetfile(Gtk::TreeIter i, gx_system::PresetFileGui *f);
    void display_paned(bool show_preset, int paned_child_height);
    void on_selection_changed();
public:
    PresetWindow(Glib::RefPtr<gx_gui::GxBuilder> bld, gx_engine::GxMachineBase& machine,
		 const gx_system::CmdlineOptions& options, GxActions& actions, GtkSizeGroup *lc);
    ~PresetWindow();
    void on_preset_select(bool v, bool animated, int preset_window_height);
};
