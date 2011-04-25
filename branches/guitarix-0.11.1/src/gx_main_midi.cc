/*
 * Copyright (C) 2009, 2010 Hermann Meyer, James Warden, Andreas Degert
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
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 * ---------------------------------------------------------------------------
 *
 *    This file is part of the guitarix GUI main class
 *
 * ----------------------------------------------------------------------------
 */


/****************************************************************
 ** MidiControllerTable
 */

class MidiControllerTable: public sigc::trackable
{
private:
	enum {RESPONSE_DELETE_SELECTED};
	static GtkWidget *window; // there can only be 1 window
	GtkToggleButton *togglebutton;
	GtkTreeSelection *selection;
	GtkListStore *store;
	GtkCheckMenuItem *menuitem;
	static void response_cb(GtkWidget *widget, gint response_id, gpointer data);
	static void edited_cb(GtkCellRendererText *renderer, gchar *path, gchar *new_text, gpointer data);
	static void destroy_cb(GtkWidget*, gpointer data);
	static void toggleButtonSetSwitch(GtkWidget *w, gpointer data);
	void set(bool);
	void load();
	MidiControllerTable(GtkCheckMenuItem *item);
	~MidiControllerTable();
public:
	static void toggle(GtkWidget* widget, gpointer data);
};

GtkWidget *MidiControllerTable::window = 0;

void MidiControllerTable::response_cb(GtkWidget *widget, gint response_id, gpointer data)
{
	MidiControllerTable& m = *(MidiControllerTable*)data;
	if (response_id == RESPONSE_DELETE_SELECTED) {
		GtkTreeModel *model;
		GList *list = gtk_tree_selection_get_selected_rows(m.selection, &model);
		gtk_tree_selection_unselect_all(m.selection);
		for (GList *p = g_list_last(list); p; p = g_list_previous(p)) {
			GtkTreeIter iter;
			gtk_tree_model_get_iter(GTK_TREE_MODEL(model), &iter, (GtkTreePath*)p->data);
			const char* id;
			gtk_tree_model_get(GTK_TREE_MODEL(model), &iter, 7, &id, -1);
			controller_map.deleteParameter(parameter_map[id], true);
			gtk_tree_path_free((GtkTreePath*)p->data);
		}
		g_list_free (list);
		m.load();
		return;
	}
	gtk_check_menu_item_set_active(m.menuitem, FALSE);
}

void MidiControllerTable::destroy_cb(GtkWidget*, gpointer data)
{
	delete (MidiControllerTable*)data;
}

void  MidiControllerTable::edited_cb(
	GtkCellRendererText *renderer, gchar *path, gchar *new_text, gpointer data)
{
	GtkListStore *store = GTK_LIST_STORE(data);
	GtkTreeIter iter;
	gtk_tree_model_get_iter_from_string(GTK_TREE_MODEL(store), &iter, path);
	int ctrl;
	gtk_tree_model_get(GTK_TREE_MODEL(store), &iter, 0, &ctrl, -1);
	midi_std_ctr.replace(ctrl, new_text);
	bool valid = gtk_tree_model_get_iter_first(GTK_TREE_MODEL(store), &iter);
	const char *name = midi_std_ctr[ctrl].c_str();
	while (valid) {
		int n;
		gtk_tree_model_get(GTK_TREE_MODEL(store), &iter, 0, &n, -1);
		if (n == ctrl) {
			gtk_list_store_set(store, &iter, 1, name, -1);
		}
		valid = gtk_tree_model_iter_next (GTK_TREE_MODEL(store), &iter);
	}
}

void MidiControllerTable::toggleButtonSetSwitch(GtkWidget *w, gpointer data)
{
	SwitchParameter *p = (SwitchParameter*)data;
	p->set(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(w)));
}

void MidiControllerTable::set(bool v)
{
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(togglebutton), v);
}

void MidiControllerTable::load()
{
	GtkTreeIter iter;
	gtk_list_store_clear(store);
	for (int i = 0; i < controller_map.size(); i++) {
		midi_controller_list& cl = controller_map[i];
		for (midi_controller_list::iterator j = cl.begin(); j != cl.end(); j++) {
			Parameter& p = j->getParameter();
			string low, up;
			const char *tp;
			float step = p.getStepAsFloat();
			if (p.getControlType() == Parameter::Continuous) {
				tp = "Scale";
				low = fformat(j->lower(), step);
				up = fformat(j->upper(), step);
			} else if (p.getControlType() == Parameter::Enum) {
				tp = "Select";
				low = fformat(j->lower(), step);
				up = fformat(j->upper(), step);
			} else if (p.getControlType() == Parameter::Switch) {
				tp = "Switch";
				low = up = "";
			} else {
				tp = "??";
				assert(false);
			}
			gtk_list_store_append(store, &iter);
			gtk_list_store_set(store, &iter,
			                   0, i,
			                   1, midi_std_ctr[i].c_str(),
			                   2, p.group().c_str(),
			                   3, p.name().c_str(),
			                   4, tp,
			                   5, low.c_str(),
			                   6, up.c_str(),
			                   7, p.id().c_str(),
			                   -1);
		}
	}
}

void MidiControllerTable::toggle(GtkWidget* widget, gpointer data)
{
	if (!gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(data))) {
		if (window) {
			gtk_widget_destroy(window);
		}
	} else {
		if (!window) {
			new MidiControllerTable(GTK_CHECK_MENU_ITEM(data));
		}
	}
}

MidiControllerTable::~MidiControllerTable()
{
	window = NULL;
	gtk_widget_unref(GTK_WIDGET(menuitem));
}

MidiControllerTable::MidiControllerTable(GtkCheckMenuItem *item)
{
	menuitem = item;
	gtk_widget_ref(GTK_WIDGET(item));

	GtkBuilder * builder = gtk_builder_new();
	window = load_toplevel(builder, "midi.glade", "MidiControllerTable");
	store = GTK_LIST_STORE(gtk_builder_get_object(builder, "liststore1"));
	togglebutton = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "save_controller"));

	SwitchParameter& param = parameter_map["system.midi_in_preset"].getSwitch();
	gtk_toggle_button_set_active(togglebutton, param.get());
	param.changed.connect(sigc::mem_fun(*this, &MidiControllerTable::set));
	g_signal_connect(GTK_OBJECT(togglebutton), "toggled",
	                 G_CALLBACK(toggleButtonSetSwitch), (gpointer)&param);
	selection = gtk_tree_view_get_selection(
		GTK_TREE_VIEW(gtk_builder_get_object(builder, "treeview1")));
	gtk_tree_selection_set_mode(selection, GTK_SELECTION_MULTIPLE);

	load();

	g_signal_connect(window, "destroy", G_CALLBACK(destroy_cb), this);
	g_signal_connect(window, "response", G_CALLBACK(response_cb), this);
	g_signal_connect(G_OBJECT(gtk_builder_get_object(builder, "cellrenderertext2")),
	                 "edited", G_CALLBACK(edited_cb), store);

	gtk_window_add_accel_group(GTK_WINDOW(window),
	                           GxMainInterface::instance()->fAccelGroup);

	gtk_widget_show(window);
	g_object_unref(G_OBJECT(builder));
	controller_map.changed.connect(sigc::mem_fun(*this, &MidiControllerTable::load));
}


/*****************************************************************
 ** Midi Control
 */

class MidiConnect
{
private:
	enum { RESPONSE_DELETE = 1 };
	Parameter &param;
	GtkAdjustment* adj_lower;
	GtkAdjustment* adj_upper;
	GtkWidget* dialog;
	GtkWidget* entry_new;
	GtkWidget* label_desc;
	int current_control;
	static string ctr_desc(int ctr);
	static const char *ctl_to_str(int n);
public:
	MidiConnect(GdkEventButton *event, Parameter& param);
	static void midi_response_cb(GtkWidget *widget, gint response_id, gpointer data);
	static void midi_destroy_cb(GtkWidget *widget, gpointer data);
	static gboolean check_midi_cb(gpointer);
	static void changed_text_handler (GtkEditable *entry, gpointer data);
};

string MidiConnect::ctr_desc(int ctr)
{
	string p = midi_std_ctr[ctr];
	if (p.empty())
		return p;
	return "(" + p + ")";
}


void MidiConnect::midi_response_cb(GtkWidget *widget, gint response_id, gpointer data)
{
	MidiConnect* m = (MidiConnect*)data;
	switch (response_id) {
	case GTK_RESPONSE_OK:
		if (m->param.getControlType() == Parameter::Continuous ||
		    m->param.getControlType() == Parameter::Enum) {
			assert(m->adj_lower);
			assert(m->adj_upper);
			float lower = gtk_adjustment_get_value(m->adj_lower);
			float upper = gtk_adjustment_get_value(m->adj_upper);
			controller_map.modifyCurrent(m->param, lower, upper);
		} else {
			controller_map.modifyCurrent(m->param, 0, 0);
		}
		break;
	case RESPONSE_DELETE:
		controller_map.deleteParameter(m->param);
		break;
	}
	gtk_widget_destroy(m->dialog);
}

void MidiConnect::midi_destroy_cb(GtkWidget *widget, gpointer data)
{
	MidiConnect *m = (MidiConnect*)data;
	controller_map.set_config_mode(false);
	delete m;
}

const char* MidiConnect::ctl_to_str(int n)
{
	static char buf[12];
	if (n < 0)
		strcpy(buf, "---");
	else
		snprintf(buf, sizeof(buf), "%3d", n);
	return buf;
}

gboolean MidiConnect::check_midi_cb(gpointer data)
{
	MidiConnect *m = (MidiConnect*)data;
	if (!controller_map.get_config_mode())
		return FALSE;
	int ctl = controller_map.get_current_control();
	if (m->current_control == ctl)
		return TRUE;
	m->current_control = ctl;
	gtk_entry_set_text(GTK_ENTRY(m->entry_new), ctl_to_str(ctl));
	return TRUE;
}

void MidiConnect::changed_text_handler (GtkEditable *editable, gpointer data)
{
	MidiConnect *m = (MidiConnect*)data;
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
		if (n > 127) {
			n = 127;
		}
		ostringstream b;
		b << n;
		str = b.str().substr(0,3);
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
		controller_map.set_current_control(n);
		m->current_control = n;
		return;
	}
	gtk_editable_delete_text(editable, 0, -1);
	gint position = 0;
	gtk_editable_insert_text(editable, str.c_str(), str.size(), &position);
}


MidiConnect::MidiConnect(GdkEventButton *event, Parameter &param):
	param(param),
	current_control(-1)
{
	GtkBuilder * builder = gtk_builder_new();
	dialog = load_toplevel(builder, "midi.glade", "MidiConnect");
	GtkWidget *zn = GTK_WIDGET(gtk_builder_get_object(builder, "zone_name"));
	GtkStyle *style = gtk_widget_get_style(zn);
	pango_font_description_set_size(style->font_desc, 12*PANGO_SCALE);
	pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
	gtk_widget_modify_font(zn, style->font_desc);
	gtk_label_set_text(GTK_LABEL(zn), (param.group() + ": " + param.name()).c_str());
	const MidiController *pctrl;
	int nctl = controller_map.param2controller(param, &pctrl);
	if (param.getControlType() == Parameter::Continuous ||
		param.getControlType() == Parameter::Enum) {
		float lower = param.getLowerAsFloat();
		float upper = param.getUpperAsFloat();
		float step = param.getStepAsFloat();
		GtkSpinButton *spinner;
		adj_lower = GTK_ADJUSTMENT(gtk_adjustment_new(lower, lower, upper, step, 10*step, 0));
		spinner = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "lower"));
		float climb_rate = 0.0;
		gtk_spin_button_configure(spinner, adj_lower, climb_rate, precision(step));
		adj_upper = GTK_ADJUSTMENT(gtk_adjustment_new(upper, lower, upper, step, 10*step, 0));
		spinner = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "upper"));
		gtk_spin_button_configure(spinner, adj_upper, climb_rate, precision(step));
		if (nctl != -1) {
			gtk_adjustment_set_value(adj_lower, pctrl->lower());
			gtk_adjustment_set_value(adj_upper, pctrl->upper());
		}
	} else {
		adj_lower = adj_upper = 0;
		gtk_widget_hide(GTK_WIDGET(gtk_builder_get_object(builder, "range_label")));
		gtk_widget_hide(GTK_WIDGET(gtk_builder_get_object(builder, "range_box")));
	}
	entry_new = GTK_WIDGET(gtk_builder_get_object(builder, "new"));
	label_desc = GTK_WIDGET(gtk_builder_get_object(builder, "new_desc"));
	g_signal_connect(dialog, "response", G_CALLBACK(midi_response_cb), this);
	g_signal_connect(dialog, "destroy", G_CALLBACK(midi_destroy_cb), this);
	g_signal_connect(entry_new, "changed", G_CALLBACK(changed_text_handler), this);
	if (nctl == -1) {
		gtk_dialog_set_response_sensitive(GTK_DIALOG(dialog), RESPONSE_DELETE, FALSE);
		gtk_dialog_set_response_sensitive(GTK_DIALOG(dialog), GTK_RESPONSE_OK, FALSE);
		gtk_dialog_set_default_response(GTK_DIALOG(dialog), GTK_RESPONSE_CANCEL);
	}
	controller_map.set_config_mode(true, nctl);
	check_midi_cb(this);
	gtk_widget_show(dialog);
	g_timeout_add(40, check_midi_cb, this);
	g_object_unref(G_OBJECT(builder));
	return;
}

gboolean button_press_cb (GtkWidget *widget, GdkEventButton *event, gpointer data)
{
	if (event->button != 2)
		return FALSE;
	if (controller_map.get_config_mode())
		return TRUE;
	new MidiConnect(event, *(Parameter*)data);
	return TRUE;
}
