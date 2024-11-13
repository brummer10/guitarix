/*
 * Copyright (C) 2011, 2012 Andreas Degert, Hermann Meyer
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

#include "guitarix.h"        // NOLINT

#include <glibmm/i18n.h>     // NOLINT

namespace gx_gui {

/****************************************************************/

class WidgetStack {
private:
    std::vector<Gtk::Widget*> stack;
    Gtk::Widget *top() { return stack.back(); }
public:
    WidgetStack(): stack() {}
    ~WidgetStack() {}
    bool empty() { return stack.empty(); }
    void push(Gtk::Widget *w) { stack.push_back(w); }
    void pop() { return stack.pop_back(); }
    void container_add(Gtk::Widget *w);
    void box_pack_start(Gtk::Widget *w, bool expand=true, bool fill=true, int padding=0);
    void notebook_append_page(Gtk::Widget *w, Gtk::Widget *label);
    bool top_is_notebook() { return dynamic_cast<Gtk::Notebook*>(top()) != 0; }
    Gtk::Widget *add(Gtk::Widget *w, const Glib::ustring& label = Glib::ustring());
};

class StackBoxBuilder {
private:
    WidgetStack          fBox;
    gx_engine::GxMachineBase& machine;
    Gtk::HBox           *widget;
    Glib::RefPtr<Gtk::AccelGroup> accels;
    Glib::RefPtr<Gdk::Pixbuf> window_icon;
    int next_flags;
    PluginUI *current_plugin;
    std::vector<Glib::ustring> nam_file_names;
    std::vector<Glib::ustring> snam_file_names;
    std::vector<Glib::ustring> mnam_afile_names;
    std::vector<Glib::ustring> mnam_bfile_names;
    std::vector<Glib::ustring> rtneural_file_names;
    std::vector<Glib::ustring> srtneural_file_names;
    std::vector<Glib::ustring> mrtneural_afile_names;
    std::vector<Glib::ustring> mrtneural_bfile_names;

private:
    void loadRackFromBuilder(const Glib::RefPtr<GxBuilder>& bld);
    // functions used in interfaces
    void create_master_slider(const std::string& id, const char *label);

    void closeBox();
    void insertSpacer();

    void check_set_flags(Gxw::Regler *r);
    void create_simple_meter(const std::string& id);
    void create_simple_c_meter(const std::string& id, const std::string& idl, const char *label);
    void create_mid_rackknob(const std::string& id, const char *label);
    void create_small_rackknob(const std::string& id, const char *label);
    void create_small_rackknobr(const std::string& id, const char *label);
    void create_big_rackknob(const std::string& id, const char *label);
    
    void openVerticalBox(const char* label = "");
    void openFrameBox(const char* label);
    void openHorizontalBox(const char* label = "");
    void openHorizontalhideBox(const char* label = "");
    void openHorizontalTableBox(const char* label);
    void create_switch_no_caption(const char *sw_type, const std::string& id);
    void create_v_switch(const char *sw_type, const std::string& id, const char *label);
    void openpaintampBox(const char* label = "");
    void create_wheel(const std::string& id, const char *label=0);
    void create_spin_value(const std::string& id, const char *label);
    void create_simple_spin_value(const std::string& id);
    void create_eq_rackslider_no_caption(const std::string& id);
    void create_port_display(const std::string& id, const char *label);
    void create_p_display(const std::string& id, const std::string& idl, const std::string& idh);
    void create_feedback_switch(const char *sw_type, const std::string& id);
    void create_feedback_slider(const std::string& id, const char *label);
    void create_fload_switch(const char *sw_type, const char *id, const std::string& idf);
    void create_selector(const std::string& id, const char *widget_name=0);
    void create_selector_with_caption(const std::string& id, const char *label);
    void openFlipLabelBox(const char* = 0);
    void openVerticalBox1(const char* label = 0);
    void openVerticalBox2(const char* label = 0);
    void openTabBox(const char* label = 0);
    void set_next_flags(int flags);
private:
    // functions used indirectly
    void addwidget(Gtk::Widget *widget);
    bool ui_connect(Gtk::Widget *widget, const std::string& id);
    void add_regler(CpBaseCaption *w, Gxw::Regler *r, const std::string& id, const char *label);
    void load_file(const std::string& id, const std::string& idf);
    void on_file_chooser_response(int response_id, Gtk::FileChooserDialog *d,
                                  const std::string& id, const std::string& idf);
    void load_file_f(const std::string& id, const std::string& idf);
    void loadRackFromGladeData(const char *xmldesc);
    void loadRackFromGladeFile(const char *fname);
    friend class UiBuilderImpl;

public:
    StackBoxBuilder(
	gx_engine::GxMachineBase& machine_, Glib::RefPtr<Gdk::Pixbuf> window_icon);
    ~StackBoxBuilder();
    void set_neural_filelist(Gxw::Selector *sel, std::string id, std::string fileid, std::string pathid);
    void set_neural_file(std::string id, std::string fileid, std::string pathid);
    void set_accelgroup(Glib::RefPtr<Gtk::AccelGroup> accels_) { accels = accels_; }
    void prepare();
    void fetch(Gtk::Widget*& mainbox, Gtk::Widget*& minibox);
    void set_current_plugin(PluginUI *p) { current_plugin = p; }
    void connect_signals(Glib::RefPtr<GxBuilder> builder, Glib::RefPtr<Glib::Object> object,
                         const char *signal_name, const char *handler_name);
};

} // end namespace gx_gui
