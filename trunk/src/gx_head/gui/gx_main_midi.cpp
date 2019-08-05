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
 *    This file is part of the guitarix GUI main class
 *
 * ----------------------------------------------------------------------------
 */

#include "guitarix.h"     // NOLINT

/****************************************************************
 ** MidiControllerTable
 */
namespace gx_main_midi {

GtkWidget *MidiControllerTable::window = 0;

void MidiControllerTable::response_cb(GtkWidget *widget, gint response_id, gpointer data) {
    MidiControllerTable& m = *reinterpret_cast<MidiControllerTable*>(data);
    if (response_id == RESPONSE_DELETE_SELECTED) {
        GtkTreeModel *model;
        GList *list = gtk_tree_selection_get_selected_rows(m.selection, &model);
        gtk_tree_selection_unselect_all(m.selection);
        for (GList *p = g_list_last(list); p; p = g_list_previous(p)) {
            GtkTreeIter iter;
            gtk_tree_model_get_iter(GTK_TREE_MODEL(model), &iter,
                                    reinterpret_cast<GtkTreePath*>(p->data));
            const char* id;
            gtk_tree_model_get(GTK_TREE_MODEL(model), &iter, 7, &id, -1);
	    m.midi_conn.block();
            m.machine.midi_deleteParameter(m.machine.get_parameter(id));
	    m.midi_conn.unblock();
            gtk_tree_path_free(reinterpret_cast<GtkTreePath*>(p->data));
        }
        g_list_free(list);
	m.machine.signal_midi_changed()();
        return;
    }
    m.menuaction->set_active(false);
}

void MidiControllerTable::destroy_cb(GtkWidget*, gpointer data) {
    delete reinterpret_cast<MidiControllerTable*>(data);
}

void  MidiControllerTable::edited_cb(
    GtkCellRendererText *renderer, gchar *path, gchar *new_text, gpointer data) {
    GtkListStore *store = GTK_LIST_STORE(data);
    GtkTreeIter iter;
    gtk_tree_model_get_iter_from_string(GTK_TREE_MODEL(store), &iter, path);
    int ctrl;
    gtk_tree_model_get(GTK_TREE_MODEL(store), &iter, 0, &ctrl, -1);
    gx_engine::midi_std_ctr.replace(ctrl, new_text);
    bool valid = gtk_tree_model_get_iter_first(GTK_TREE_MODEL(store), &iter);
    const char *name = gx_engine::midi_std_ctr[ctrl].c_str();
    while (valid) {
        int n;
        gtk_tree_model_get(GTK_TREE_MODEL(store), &iter, 0, &n, -1);
        if (n == ctrl) {
            gtk_list_store_set(store, &iter, 1, name, -1);
        }
        valid = gtk_tree_model_iter_next(GTK_TREE_MODEL(store), &iter);
    }
}

void MidiControllerTable::toggleButtonSetSwitch(GtkWidget *w, gpointer data) {
    gx_engine::BoolParameter *p = (gx_engine::BoolParameter*)data;
    p->set(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(w)));
}

void MidiControllerTable::set(bool v) {
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(togglebutton), v);
}

void MidiControllerTable::load() {
    GtkTreeIter iter;
    gtk_list_store_clear(store);
    for (int i = 0; i < machine.midi_size(); i++) {
        gx_engine::midi_controller_list& cl = machine.midi_get(i);
        for (gx_engine::midi_controller_list::iterator j = cl.begin(); j != cl.end(); ++j) {
            gx_engine::Parameter& p = j->getParameter();
            string low, up;
            const char *tp;
            float step = p.getStepAsFloat();
            if (p.getControlType() == gx_engine::Parameter::Continuous) {
                tp = "Scale";
                low = gx_gui::fformat(j->lower(), step);
                up = gx_gui::fformat(j->upper(), step);
            } else if (p.getControlType() == gx_engine::Parameter::Enum) {
                tp = "Select";
                low = gx_gui::fformat(j->lower(), step);
                up = gx_gui::fformat(j->upper(), step);
            } else if (p.getControlType() == gx_engine::Parameter::Switch) {
		if (j->is_toggle()) {
		    tp = "Toggle";
		} else {
		    tp = "Switch";
		}
                low = up = "";
            } else {
                tp = "??";
                assert(false);
            }
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter,
                               0, i,
                               1, gx_engine::midi_std_ctr[i].c_str(),
                               2, p.l_group().c_str(),
                               3, p.l_name().c_str(),
                               4, tp,
                               5, low.c_str(),
                               6, up.c_str(),
                               7, p.id().c_str(),
                               -1);
        }
    }
}

void MidiControllerTable::toggle(gx_engine::GxMachineBase& machine, Glib::RefPtr<Gtk::ToggleAction> item) {
    if (!item->get_active()) {
        if (window) {
            gtk_widget_destroy(window);
        }
    } else {
        if (!window) {
            new MidiControllerTable(machine, item);
        }
    }
}

MidiControllerTable::~MidiControllerTable() {
    window = NULL;
}

MidiControllerTable::MidiControllerTable(gx_engine::GxMachineBase& machine_, Glib::RefPtr<Gtk::ToggleAction> item)
    : menuaction(item),
      machine(machine_),
      midi_conn() {

    GtkBuilder * builder = gtk_builder_new();
    window = gx_gui::load_toplevel(builder, "midi.glade", "MidiControllerTable");
    store = GTK_LIST_STORE(gtk_builder_get_object(builder, "liststore1"));
    togglebutton = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "save_controller"));

    gx_engine::BoolParameter& p = machine.get_parameter("system.midi_in_preset").getBool();
    gtk_toggle_button_set_active(togglebutton, p.get_value());
    machine.signal_parameter_value<bool>("system.midi_in_preset").connect(sigc::mem_fun(*this, &MidiControllerTable::set));
    g_signal_connect(G_OBJECT(togglebutton), "toggled",
                     G_CALLBACK(toggleButtonSetSwitch), (gpointer)&p);
    //g_signal_connect(gtk_builder_get_object(builder, "dialog-vbox1"),"expose-event",
                     //G_CALLBACK(gx_cairo::rectangle_skin_color_expose), NULL);
    //g_signal_connect(gtk_builder_get_object(builder, "dialog-vbox2"),"expose-event",
                     //G_CALLBACK(gx_cairo::rectangle_skin_color_expose), NULL);
    selection = gtk_tree_view_get_selection(
        GTK_TREE_VIEW(gtk_builder_get_object(builder, "treeview1")));
    gtk_tree_selection_set_mode(selection, GTK_SELECTION_MULTIPLE);
    gtk_widget_set_redraw_on_allocate(GTK_WIDGET(gtk_builder_get_object(builder, "dialog-vbox1")),true);
    gtk_widget_set_redraw_on_allocate(GTK_WIDGET(gtk_builder_get_object(builder, "dialog-vbox2")),true);
    load();

    g_signal_connect(window, "destroy", G_CALLBACK(destroy_cb), this);
    g_signal_connect(window, "response", G_CALLBACK(response_cb), this);
    g_signal_connect(G_OBJECT(gtk_builder_get_object(builder, "cellrenderertext2")),
                     "edited", G_CALLBACK(edited_cb), store);

    //gtk_window_add_accel_group(GTK_WINDOW(window),
    //                           gx_gui::GxMainInterface::get_instance().fAccelGroup->gobj());

    gtk_widget_show(window);
    g_object_unref(G_OBJECT(builder));
    midi_conn = machine.signal_midi_changed().connect(
	sigc::mem_fun(*this, &MidiControllerTable::load));
}


/*****************************************************************
 ** Midi Control
 */

string MidiConnect::ctr_desc(int ctr) {
    string p = gx_engine::midi_std_ctr[ctr];
    if (p.empty())
        return p;
    return "(" + p + ")";
}


void MidiConnect::midi_response_cb(GtkWidget *widget, gint response_id, gpointer data) {
    MidiConnect* m = reinterpret_cast<MidiConnect*>(data);
    switch (response_id) {
    case GTK_RESPONSE_OK:
        if (m->param.getControlType() == gx_engine::Parameter::Continuous ||
            m->param.getControlType() == gx_engine::Parameter::Enum) {
            assert(m->adj_lower);
            assert(m->adj_upper);
            float lower = gtk_adjustment_get_value(m->adj_lower);
            float upper = gtk_adjustment_get_value(m->adj_upper);
            m->machine.midi_modifyCurrent(m->param, lower, upper, false, gx_engine::Parameter::toggle_type::OnOff);
        } else {
            bool toggle = gtk_toggle_button_get_active(m->use_toggle);
            int toggle_behaviour = gtk_combo_box_get_active(GTK_COMBO_BOX(m->toggle_behaviours));
            m->machine.midi_modifyCurrent(m->param, 0, 0, toggle, toggle_behaviour);
        }
        break;
    case RESPONSE_DELETE:
        m->machine.midi_deleteParameter(m->param);
        break;
    case GTK_RESPONSE_HELP:
        static string midiconnecthelp;
    if (midiconnecthelp.empty()) {
        midiconnecthelp +=_("\n     Guitarix:Midi learn \n");
        midiconnecthelp +=
            _("    Just move your midi controller to connect it \n"
   "    with the selected guitarix Controller. \n"
   "    As soon the Midi Controller is detected,  \n"
   "    you will see the Controller Number in the   \n"
   "    Midi Controller Number field. Press 'OK' to connect it,   \n"
   "    or move a other Midi controller.  \n"
   "    A exception is the MIDI BEAT CLOCK, \n" 
   "    which isn't a Controller itself,\n"
   "    but could be used here to sync BPM controllers    \n"
   "    with external devices.  \n"
   "    To use it, you must insert '22' as Midi Controller Number   \n"
   "      \n"
   "    The same is true for the MIDI CLOCK start/stop function,    \n"
   "    which could be used to switch effects on/off.   \n"
   "    To use it, you must insert '23' as Midi Controller Number.   \n\n"
   "    Also Jack Transport is supported and can be used to control    \n"
   "    switch controllers (on/off) by connect then to    \n"
   "    Midi Controller Number '24'.    \n"

          "");

    }

    gx_gui::gx_message_popup(midiconnecthelp.c_str());
        return;
        break;
    }
    gtk_widget_destroy(m->dialog);
}

void MidiConnect::midi_destroy_cb(GtkWidget *widget, gpointer data) {
    MidiConnect *m = reinterpret_cast<MidiConnect*>(data);
    m->machine.midi_set_config_mode(false);
}

void MidiConnect::toggle_behaviours_visibility(GtkWidget *widget, gpointer data) {
    MidiConnect *m = reinterpret_cast<MidiConnect*>(data);
    int b = gtk_toggle_button_get_active(m->use_toggle);
    gtk_widget_set_sensitive(gtk_widget_get_parent(m->toggle_behaviours), b);
}

const char* MidiConnect::ctl_to_str(int n) {
    static char buf[12];
    if (n < 0)
        strcpy(buf, "---");     //  NOLINT
    else
        snprintf(buf, sizeof(buf), "%3d", n);
    return buf;
}

gboolean MidiConnect::check_midi_cb(gpointer data) {
    MidiConnect *m = reinterpret_cast<MidiConnect*>(data);
    int ctl;
    if (!m->machine.midi_get_config_mode(&ctl)) {
	delete m;
        return FALSE;
    }
    if (m->current_control == ctl)
        return TRUE;
    m->current_control = ctl;
    gtk_entry_set_text(GTK_ENTRY(m->entry_new), ctl_to_str(ctl));
    if ( ctl>200) {
        gtk_toggle_button_set_active(m->use_toggle, true);
        gtk_combo_box_set_active(GTK_COMBO_BOX(m->toggle_behaviours), gx_engine::Parameter::toggle_type::Constant);
    }
    return TRUE;
}

void MidiConnect::changed_text_handler(GtkEditable *editable, gpointer data) {
    MidiConnect *m = reinterpret_cast<MidiConnect*>(data);
    gchar *p = gtk_editable_get_chars(editable, 0, -1);
    ostringstream buf;
    for (const char *q = p; *q; q++) {
        if (isdigit(*q)) {
            buf << *q;
        }
    }
    string str = buf.str();
    int n = -1;
    if (!str.empty()) {
        istringstream i(buf.str());
        i >> n;
        if (n > 327) {
            n = 327;
        }
        ostringstream b;
        b << n;
        str = b.str().substr(0, 3);
    }
    // prevent infinite loop because after it has changed the text
    // the handler will be called again (and make sure the text
    // tranformation in this handler is idempotent!)
    if (str == p) {
        if (str.empty()) {
            gtk_dialog_set_response_sensitive(GTK_DIALOG(m->dialog), GTK_RESPONSE_OK, FALSE);
            gtk_dialog_set_default_response(GTK_DIALOG(m->dialog), GTK_RESPONSE_CANCEL);
        } else {
            gtk_dialog_set_response_sensitive(GTK_DIALOG(m->dialog), GTK_RESPONSE_OK, TRUE);
            gtk_dialog_set_default_response(GTK_DIALOG(m->dialog), GTK_RESPONSE_OK);
        }
        gtk_label_set_text(GTK_LABEL(m->label_desc), ctr_desc(n).c_str());
        m->machine.midi_set_current_control(n);
        m->current_control = n;
        return;
    }
    gtk_editable_delete_text(editable, 0, -1);
    gint position = 0;
    gtk_editable_insert_text(editable, str.c_str(), str.size(), &position);
}


MidiConnect::MidiConnect(GdkEventButton *event, gx_engine::Parameter &param_, gx_engine::GxMachineBase& machine_)
    : param(param_),
      machine(machine_),
      current_control(-1),
      adj_lower(),
      adj_upper() {
    GtkBuilder * builder = gtk_builder_new();
    dialog = gx_gui::load_toplevel(builder, "midi.glade", "MidiConnect");
    use_toggle = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "use_toggle"));
    toggle_behaviours = GTK_WIDGET(gtk_builder_get_object(builder, "toggle_behaviours"));
    GtkWidget *zn = GTK_WIDGET(gtk_builder_get_object(builder, "zone_name"));
    GtkStyle *style = gtk_widget_get_style(zn);
    pango_font_description_set_size(style->font_desc, 12*PANGO_SCALE);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
    gtk_widget_modify_font(zn, style->font_desc);
    gtk_label_set_text(GTK_LABEL(zn), (param.l_group() + ": " + param.l_name()).c_str());
    gtk_widget_set_tooltip_text(zn, (_("Parameter ID: ")+param.id()).c_str());
    zn = GTK_WIDGET(gtk_builder_get_object(builder, "desc_box"));
    if (param.desc().empty()) {
	gtk_widget_hide(zn);
    } else {
	GtkWidget *desc = GTK_WIDGET(gtk_builder_get_object(builder, "desc"));
	gtk_label_set_text(GTK_LABEL(desc), param.l_desc().c_str());
	gtk_widget_show(zn);
    }
    const gx_engine::MidiController *pctrl;
    int nctl = machine.midi_param2controller(param, &pctrl);
    if (param.getControlType() == gx_engine::Parameter::Continuous ||
        param.getControlType() == gx_engine::Parameter::Enum) {
        float lower = param.getLowerAsFloat();
        float upper = param.getUpperAsFloat();
        float step = param.getStepAsFloat();
        GtkSpinButton *spinner;
        adj_lower = GTK_ADJUSTMENT(gtk_adjustment_new(lower, lower, upper, step, 10*step, 0));
        spinner = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "lower"));
        float climb_rate = 0.0;
        gtk_spin_button_configure(spinner, adj_lower, climb_rate, gx_gui::precision(step));
        adj_upper = GTK_ADJUSTMENT(gtk_adjustment_new(upper, lower, upper, step, 10*step, 0));
        spinner = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "upper"));
        gtk_spin_button_configure(spinner, adj_upper, climb_rate, gx_gui::precision(step));
        if (nctl != -1) {
            gtk_adjustment_set_value(adj_lower, pctrl->lower());
            gtk_adjustment_set_value(adj_upper, pctrl->upper());
        }
        gtk_widget_hide(gtk_widget_get_parent(gtk_widget_get_parent(GTK_WIDGET(use_toggle))));
    } else {
        gtk_widget_hide(GTK_WIDGET(gtk_builder_get_object(builder, "range_label")));
        gtk_widget_hide(GTK_WIDGET(gtk_builder_get_object(builder, "range_box")));

        store = GTK_LIST_STORE(gtk_builder_get_object(builder, "liststore2"));
        GtkTreeIter iter;
        gtk_list_store_clear(store);
        for (std::map<gx_engine::Parameter::toggle_type, const char*>::iterator it = toggle_behaviour_descriptions.begin();
               it!=toggle_behaviour_descriptions.end(); ++it) {
                gtk_list_store_append(store, &iter);
                gtk_list_store_set(store, &iter, 0, it->first, 1, it->second, -1);
        }
        gtk_combo_box_set_model(GTK_COMBO_BOX(toggle_behaviours), GTK_TREE_MODEL(store));
        //g_object_unref(store); // this THROW A GLib-GObject-CRITICAL WARNING
        GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
        gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(toggle_behaviours), renderer, TRUE);
        gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(toggle_behaviours), renderer, "text", 1, NULL); // "cell-background", 0, -> throw Gtk-WARNING **: Don't know color `0'
        gtk_combo_box_set_active(GTK_COMBO_BOX(toggle_behaviours), gx_engine::Parameter::toggle_type::OnOff);
        if (nctl != -1) {
            gtk_toggle_button_set_active(use_toggle, pctrl->is_toggle());
            gtk_combo_box_set_active(GTK_COMBO_BOX(toggle_behaviours), pctrl->toggle_behaviour());
        }
        int b = gtk_toggle_button_get_active(use_toggle);
        gtk_widget_set_sensitive(gtk_widget_get_parent(toggle_behaviours), b);
    }
    entry_new = GTK_WIDGET(gtk_builder_get_object(builder, "new"));
    label_desc = GTK_WIDGET(gtk_builder_get_object(builder, "new_desc"));

    g_signal_connect(dialog, "response", G_CALLBACK(midi_response_cb), this);
    g_signal_connect(dialog, "destroy", G_CALLBACK(midi_destroy_cb), this);
    g_signal_connect(entry_new, "changed", G_CALLBACK(changed_text_handler), this);
    g_signal_connect(use_toggle, "toggled", G_CALLBACK(toggle_behaviours_visibility), this);
    if (nctl == -1) {
        gtk_dialog_set_response_sensitive(GTK_DIALOG(dialog), RESPONSE_DELETE, FALSE);
        gtk_dialog_set_response_sensitive(GTK_DIALOG(dialog), GTK_RESPONSE_OK, FALSE);
        gtk_dialog_set_response_sensitive(GTK_DIALOG(dialog), GTK_RESPONSE_HELP, TRUE);
        gtk_dialog_set_default_response(GTK_DIALOG(dialog), GTK_RESPONSE_CANCEL);
    }
    machine.midi_set_config_mode(true, nctl);
    check_midi_cb(this);
    gtk_widget_show(dialog);
    g_timeout_add(40, check_midi_cb, this);
    g_object_unref(G_OBJECT(builder));
}
} // end namespace
