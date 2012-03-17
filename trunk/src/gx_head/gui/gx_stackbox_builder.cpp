#include "guitarix.h"        // NOLINT

#include <glibmm/i18n.h>     // NOLINT

// -------- the gx_head user interface build instruktions

namespace gx_gui {

GuiVariables guivar;
// Stock Items for Gxw::Switch

const char *sw_led =             "led";
const char *sw_switch =          "switch";
const char *sw_switchit =        "switchit";
const char *sw_minitoggle =      "minitoggle";
const char *sw_button =          "button";
const char *sw_pbutton =         "pbutton";
const char *sw_rbutton =         "rbutton";

// Paint Functions for Gxw::PaintBox

const char *pb_amp_expose =                  "amp_expose";
const char *pb_conv_widget_expose =          "conv_widget_expose";
const char *pb_upper_widget_expose =         "upper_widget_expose";
const char *pb_rectangle_expose =            "rectangle_expose";
const char *pb_rectangle_skin_color_expose = "rectangle_skin_color_expose";
const char *pb_convolver_icon_expose =       "convolver_icon_expose";
const char *pb_AmpBox_expose =               "AmpBox_expose";
const char *pb_tribal_box_expose =           "tribal_box_expose";
const char *pb_vbox_expose =                 "vbox_expose";
const char *pb_filter_box_expose =           "filter_box_expose";
const char *pb_plug_box_expose =             "plug_box_expose";
const char *pb_info_box_expose_on =          "info_box_expose_on";
const char *pb_info_box_expose_off =         "info_box_expose_off";
const char *pb_slooper_expose =              "slooper_expose";
const char *pb_zac_expose =                  "zac_expose";
const char *pb_gxhead_expose =               "gxhead_expose";
const char *pb_RackBox_expose =              "RackBox_expose";
const char *pb_gxrack_expose =               "gxrack_expose";
const char *pb_eq_expose =                   "eq_expose";
const char *pb_main_expose =                 "main_expose";
const char *pb_level_meter_expose =          "level_meter_expose";


int precision(double n) {
    if (n < 0.009999)
        return 3;
    else if (n < 0.099999)
        return 2;
    else if (n < 0.999999)
        return 1;
    else
        return 0;
}

string fformat(float value, float step) {
    ostringstream buf;
    buf << fixed << setprecision(precision(step)) << value;
    return buf.str();
}

void uiToggleButton::toggled() {
    modifyZone(fButton->get_active());
}

void uiToggleButton::reflectZone() {
    bool v = *fZone;
    fCache = v;
    fButton->set_active(v);
}

struct uiButton : public gx_ui::GxUiItemFloat {
    GtkButton*     fButton;
    uiButton(gx_ui::GxUI* ui, float* zone, GtkButton* b) : gx_ui::GxUiItemFloat(ui, zone),
             fButton(b) {}
    static void pressed(GtkWidget *widget, gpointer   data);
    static void released(GtkWidget *widget, gpointer   data);
    virtual void reflectZone();
};

void uiButton::pressed(GtkWidget *widget, gpointer   data) {
    gx_ui::GxUiItemFloat* c = (gx_ui::GxUiItemFloat*)data;
    c->modifyZone(1.0);
}

void uiButton::released(GtkWidget *widget, gpointer   data) {
    gx_ui::GxUiItemFloat* c = (gx_ui::GxUiItemFloat*) data;
    c->modifyZone(0.0);
}

void uiButton::reflectZone() {
    float v = *fZone;
    fCache = v;
    if (v > 0.0) {
	gtk_button_pressed(fButton);
    } else {
	gtk_button_released(fButton);
    }
}

gboolean button_press_cb(GtkWidget *widget, GdkEventButton *event, gpointer data) {
    if (event->button != 2)
        return FALSE;
    if (gx_engine::controller_map.get_config_mode())
        return TRUE;
    new gx_main_midi::MidiConnect(event, *reinterpret_cast<gx_engine::Parameter*>(data));
    return TRUE;
}

void GuiVariables::register_gui_parameter(gx_engine::ParamMap& pmap) {
    static value_pair starter[] = {
	{ "other", "other" },
	{ "qjackctl", "qjackctl" },
	{ "autostart", "autostart" },
	{0}
    };
    gx_engine::parameter_map.reg_non_midi_enum_par(
	"ui.jack_starter_idx", "", starter, static_cast<int*>(0), false, 1);
    gx_engine::parameter_map.reg_switch("ui.ask_for_jack_starter", false, true);
    gx_engine::parameter_map.reg_string("ui.jack_starter", "", 0, "");

    /* for level display */
    meter_falloff = 27; // in dB/sec.
    meter_display_timeout = 60; // in millisec
}

/****************************************************************
 ** class StackBoxBuilder
 */

StackBoxBuilder::StackBoxBuilder(
    int& fTop_, GtkWidget*(&fBox_)[stackSize], gx_engine::GxEngine& engine_,
    gx_engine::ParamMap& pmap_, int (&fMode_)[stackSize],
    Gxw::WaveView &fWaveView_, Gtk::Label &convolver_filename_label_, gx_ui::GxUI& ui_, Glib::RefPtr<Gdk::Pixbuf> window_icon_)
    : fTop(fTop_), fBox(fBox_), engine(engine_), pmap(pmap_),
      fMode(fMode_), fWaveView(fWaveView_),
      convolver_filename_label(convolver_filename_label_), ui(ui_),
      window_icon(window_icon_) {
}

StackBoxBuilder::~StackBoxBuilder() {
}

void StackBoxBuilder::loadRackFromGladeData(const char *xmldesc) {
    const char *ids[] = { "rackbox", "minibox", 0 };
    Glib::RefPtr<GxBuilder> bld = GxBuilder::create_from_string(xmldesc, &ui, ids);
    Gtk::Widget* w;
    bld->find_widget("minibox", w);
    if (w) {
	addWidget("", w->gobj());
    }
    bld->find_widget("rackbox", w);
    if (!w) {
        gx_system::gx_print_error("load_ui Error", "can't find widget 'rackbox'");
	return;
    }
    addWidget("", w->gobj());
}

void StackBoxBuilder::pushBox(int mode, GtkWidget* w) {
    ++fTop;
    assert(fTop < stackSize);
    fMode[fTop]     = mode;
    fBox[fTop]         = w;
}

GtkWidget* StackBoxBuilder::addWidget(const char* label, GtkWidget* w) {
    switch (fMode[fTop]) {
    case kSingleMode    :
        gtk_container_add(GTK_CONTAINER(fBox[fTop]), w);
        break;
    case kBoxMode         :
        gtk_box_pack_start(GTK_BOX(fBox[fTop]), w, expand, fill, 0);
        break;
    case kTabMode         :
        gtk_notebook_append_page(GTK_NOTEBOOK(fBox[fTop]), w, gtk_label_new(label));
        break;
    }
    gtk_widget_show(w);
    return w;
}

void StackBoxBuilder::addSmallJConvFavButton(const char* label, gx_jconv::IRWindow *irw) {
    Gtk::Button *button = new Gtk::Button();
    button->set_name("smallbutton");
    Gtk::Label *lab = new Gtk::Label(label);
    Pango::FontDescription font = lab->get_style()->get_font();
    font.set_size(7*Pango::SCALE);
    font.set_weight(Pango::WEIGHT_NORMAL);
    lab->modify_font(font);
    button->add(*manage(lab));
    lab->set_name("rack_label");
    addWidget(label, GTK_WIDGET(button->gobj()));
    lab->show();
    button->signal_clicked().connect(
	sigc::mem_fun(*irw, &gx_jconv::IRWindow::on_show_button_clicked));
}

void StackBoxBuilder::set_convolver_filename() {
    convolver_filename_label.set_label(engine.convolver.getIRFile());
}

void StackBoxBuilder::openSetLabelBox() {
    Gtk::VBox *box =  new Gtk::VBox();
    box->set_homogeneous(false);
    box->set_spacing(0);
    box->set_border_width(0);
    convolver_filename_label.set_name("beffect_label");
    Pango::FontDescription font = convolver_filename_label.get_style()->get_font();
    font.set_size(8*Pango::SCALE);
    font.set_weight(Pango::WEIGHT_BOLD);
    convolver_filename_label.modify_font(font);
    box->pack_start(convolver_filename_label, false, false, 0);
    box->show_all();
    convolver_filename_label.set_label(engine.convolver.getIRFile());
    engine.convolver.jcset.signal_file_changed().connect(
	sigc::mem_fun(*this, &StackBoxBuilder::set_convolver_filename));
    gtk_box_pack_start(GTK_BOX(fBox[fTop]), GTK_WIDGET(box->gobj()), false, fill, 0);
    pushBox(kBoxMode, GTK_WIDGET(box->gobj()));
}

void StackBoxBuilder::addJConvFavButton(const char* label, gx_jconv::IRWindow *irw) {
    Gtk::Button *button = new Gtk::Button();
    Gtk::Label *lab = new Gtk::Label(label);
    Pango::FontDescription font = lab->get_style()->get_font();
    font.set_size(10*Pango::SCALE);
    font.set_weight(Pango::WEIGHT_NORMAL);
    lab->modify_font(font);
    button->add(*manage(lab));
    lab->set_name("beffekt_label");
    addWidget(label, GTK_WIDGET(button->gobj()));
    lab->show();
    button->signal_clicked().connect(
	sigc::mem_fun(*irw, &gx_jconv::IRWindow::on_show_button_clicked));
}

void StackBoxBuilder::addJConvButton(const char* label, gx_jconv::IRWindow *irw) {
    Gtk::Button *button = new Gtk::Button();
    Gtk::Label *lab = new Gtk::Label(label);
    Pango::FontDescription font = lab->get_style()->get_font();
    font.set_size(10*Pango::SCALE);
    font.set_weight(Pango::WEIGHT_NORMAL);
    lab->modify_font(font);
    button->add(*manage(lab));
    lab->set_name("beffekt_label");
    addWidget(label, GTK_WIDGET(button->gobj()));
    lab->show();
    button->signal_clicked().connect(
	sigc::mem_fun(*irw, &gx_jconv::IRWindow::reload_and_show));
}

void StackBoxBuilder::addJToggleButton(const char* label, bool* zone) {
    Gdk::Color colorRed("#58b45e");
    Gdk::Color colorOwn("#7f7f7f");

    *zone = 0;
    Gtk::ToggleButton* button = new Gtk::ToggleButton();
    Gtk::Label* lab = new Gtk::Label(label);
    lab->set_name("beffekt_label");
    Pango::FontDescription font = lab->get_style()->get_font();
    font.set_size(10*Pango::SCALE);
    font.set_weight(Pango::WEIGHT_BOLD);
    lab->modify_font(font);
    button->add(*manage(lab));
    addWidget(label, GTK_WIDGET(button->gobj()));
    lab->show();

    uiToggleButton* c = new uiToggleButton(&ui, zone, button); // FIXME

    button->modify_bg(Gtk::STATE_NORMAL, colorOwn);
    button->modify_bg(Gtk::STATE_ACTIVE, colorRed);

    button->signal_toggled().connect(
	sigc::mem_fun(*c, &uiToggleButton::toggled));
    button->signal_toggled().connect(
	sigc::mem_fun(engine, &gx_engine::GxEngine::set_rack_changed));
    connect_midi_controller(GTK_WIDGET(button->gobj()), zone);
}

void StackBoxBuilder::create_selector(string id, const char *widget_name) {
    gx_engine::Parameter& p = pmap[id];
    UiSelectorBase *s;
    if (p.isFloat()) {
        s = new UiSelector<float>(ui, p.getFloat());
    } else if (p.isInt()) {
        s = new UiSelector<int>(ui, p.getInt());
    } else {
        s = new UiSelector<unsigned int>(ui, p.getUInt());
    }
    if (widget_name) {
	s->set_name(widget_name);
    }
    addwidget(s->get_widget());
}

void StackBoxBuilder::openSpaceBox(const char* label) {
    GxVBox * box =  new GxVBox(ui);
    box->m_box.set_homogeneous(true);
    box->m_box.set_spacing(2);
    box->m_box.set_border_width(4);
    box->m_box.show_all();
    if (fMode[fTop] != kTabMode && label[0] != 0) {
        gtk_box_pack_start(GTK_BOX(fBox[fTop]), GTK_WIDGET(box->m_box.gobj()), expand, fill, 0);
        pushBox(kBoxMode, GTK_WIDGET(box->m_box.gobj()));
    } else {
        pushBox(kBoxMode, addWidget(label, GTK_WIDGET(box->m_box.gobj())));
    }
}

void StackBoxBuilder::addLiveWaveDisplay(const char* label) {
    GtkWidget * box      = gtk_hbox_new(false, 4);
    GtkWidget * box1      = gtk_vbox_new(false, 0);
    GtkWidget * box2      = gtk_vbox_new(false, 0);
    GtkWidget * e_box =  gtk_event_box_new();
    g_signal_connect(box, "expose-event", G_CALLBACK(gx_cairo::conv_widget_expose), NULL);
    gtk_widget_set_size_request(box, 303, 82);
    gtk_widget_set_size_request(e_box, 284, 54);
    gtk_container_set_border_width(GTK_CONTAINER(box), 12);
    gtk_container_add(GTK_CONTAINER(e_box), GTK_WIDGET(fWaveView.gobj()));
    gtk_box_pack_start(GTK_BOX(box), box1, true, true, 0);
    gtk_box_pack_start(GTK_BOX(box), e_box, false, false, 0);
    gtk_box_pack_start(GTK_BOX(box), box2, true, true, 0);
    addWidget(label, box);
    fWaveView.hide(); // was show()'n by addWidget
    fWaveView.property_text_pos_left() = 1.5;
    fWaveView.property_text_pos_right() = 77;
    // multiplicator is already set by signal handler
    gtk_widget_show_all(box);
}

void StackBoxBuilder::openVerticalBox1(const char* label) {
    GxVBox * box =  new GxVBox(ui);
    box->m_box.set_homogeneous(false);
    box->m_box.set_spacing(0);
    box->m_box.set_border_width(0);

    if (fMode[fTop] != kTabMode && label[0] != 0) {
        box->m_label.set_text(label);
        box->m_label.set_name("effekt_label");
        box->m_box.pack_start(box->m_label, false, false, 0 );
        gtk_box_pack_start(GTK_BOX(fBox[fTop]), GTK_WIDGET(box->m_box.gobj()), expand, fill, 0);
        box->m_box.show();
        box->m_label.show();
        pushBox(kBoxMode, GTK_WIDGET(box->m_box.gobj()));
    } else {
        pushBox(kBoxMode, addWidget(label, GTK_WIDGET(box->m_box.gobj())));
    }
}

void StackBoxBuilder::openFlipLabelBox(const char* label) {
    GxVBox * box =  new GxVBox(ui);
    box->m_box.set_homogeneous(false);
    box->m_box.set_spacing(0);
    box->m_box.set_border_width(0);

    if (fMode[fTop] != kTabMode && label[0] != 0) {
        GxVBox * vbox =  new GxVBox(ui);
        vbox->m_box.set_homogeneous(false);
        vbox->m_box.set_spacing(0);
        vbox->m_box.set_border_width(0);

        GxHBox * hbox =  new GxHBox(ui);
        hbox->m_box.set_homogeneous(false);
        hbox->m_box.set_spacing(0);
        hbox->m_box.set_border_width(0);

        hbox->m_label.set_text(label);
        hbox->m_label.set_name("effekt_label");
        hbox->m_label.set_angle(90);
        hbox->m_label.set_size_request(15, -1);

        Pango::FontDescription font = hbox->m_label.get_style()->get_font();
        font.set_size(8*Pango::SCALE);
        font.set_weight(Pango::WEIGHT_BOLD);
        hbox->m_label.modify_font(font);

        hbox->m_box.add(hbox->m_label);
        hbox->m_box.add(vbox->m_box);
        box->m_box.add(hbox->m_box);
        gtk_box_pack_start(GTK_BOX(fBox[fTop]), GTK_WIDGET(box->m_box.gobj()), false, fill, 0);
        box->m_box.show_all();

        pushBox(kBoxMode, GTK_WIDGET(vbox->m_box.gobj()));
    } else {
        pushBox(kBoxMode, addWidget(label, GTK_WIDGET(box->m_box.gobj())));
    }
}

void StackBoxBuilder::addNumEntry(const char* label, float* zone, float init, float min,
                                  float max, float step) {
    *zone = init;
    GtkObject* adj = gtk_adjustment_new(init, min, max, step, 10*step, 0);
    uiAdjustment* c = new uiAdjustment(&ui, zone, GTK_ADJUSTMENT(adj));
    g_signal_connect(GTK_OBJECT(adj), "value-changed",
                      G_CALLBACK(uiAdjustment::changed), (gpointer) c);
    GtkWidget* spinner = gtk_spin_button_new(GTK_ADJUSTMENT(adj), step, precision(step));
    connect_midi_controller(spinner, zone);
    GtkWidget * box = gtk_hbox_new(homogene, 0);
    GtkWidget*     lab = gtk_label_new(label);
    gtk_container_add(GTK_CONTAINER(box), lab);
    gtk_widget_set_name(lab, "rack_label");
    addWidget(label, box);
    addWidget(label, spinner);
}

void StackBoxBuilder::addNumEntry(string id, const char* label_) {
    Glib::ustring label(label_);
    if (!pmap.hasId(id)) {
        return;
    }
    const gx_engine::FloatParameter &p = pmap[id].getFloat();
    if (label.empty()) {
        label = p.l_name();
    }
    addNumEntry(label.c_str(), &p.get_value(), p.std_value, p.lower, p.upper, p.step);
}

void StackBoxBuilder::addMToggleButton(const char* label, bool* zone) {
    Gdk::Color colorRed("#58b45e");
    Gdk::Color colorOwn("#7f7f7f");
    Gdk::Color colorwn("#000000");
    *zone = 0;
    Gtk::ToggleButton* button = new Gtk::ToggleButton();
    Gtk::Label* lab = new Gtk::Label(label);
    Pango::FontDescription font = lab->get_style()->get_font();
    font.set_weight(Pango::WEIGHT_BOLD);
    lab->modify_font(font);
    button->add(*manage(lab));
    button->set_size_request(70, 20);
    Gtk::Box* box = new Gtk::HBox(homogene, 4);
    Gtk::Box* box1 = new Gtk::VBox(homogene, 4);
    box->set_border_width(0);
    box1->set_border_width(0);
    box->add(*manage(box1));
    Gtk::Box* box2 = new Gtk::VBox(homogene, 4);
    box2->set_border_width(0);
    box2->set_size_request(6, 20);
    box->add(*manage(button));
    box->add(*manage(box2));
    box1->set_size_request(6, 20);
    button->show();
    box1->show();
    box2->show();
    lab->show();
    box->show();
    gtk_container_add(GTK_CONTAINER(fBox[fTop]), GTK_WIDGET(manage(box)->gobj()));
    uiToggleButton* c = new uiToggleButton(&ui, zone, button); // FIXME
    button->modify_bg(Gtk::STATE_NORMAL, colorOwn);
    button->modify_bg(Gtk::STATE_ACTIVE, colorRed);
    lab->set_name("rack_label");
    button->signal_toggled().connect(
	sigc::mem_fun(*c, &uiToggleButton::toggled));
    connect_midi_controller(GTK_WIDGET(button->gobj()), zone);
}

void StackBoxBuilder::addMToggleButton(string id, const char* label_) {
    Glib::ustring label(label_);
    if (!pmap.hasId(id)) {
        return;
    }
    const gx_engine::BoolParameter &p = pmap[id].getBool();
    if (label.empty()) {
        label = p.l_name();
    }
    addMToggleButton(label.c_str(), &p.get_value());
}

void StackBoxBuilder::addCheckButton(const char* label, bool* zone) {

    GdkColor   colorRed;
    GdkColor   colorOwn;
    GdkColor   colorba;
    gdk_color_parse("#000000", &colorRed);
    gdk_color_parse("#4c5159", &colorOwn);
    gdk_color_parse("#c4c0c0", &colorba);
    GtkWidget*     lab = gtk_label_new(label);
    GtkWidget*     button = gtk_check_button_new();
    gtk_container_add(GTK_CONTAINER(button), lab);
    addWidget(label, button);
    gtk_widget_modify_bg(button, GTK_STATE_PRELIGHT, &colorOwn);
    gtk_widget_modify_fg(button, GTK_STATE_PRELIGHT, &colorRed);
    gtk_widget_modify_text(button, GTK_STATE_NORMAL, &colorRed);
    gtk_widget_modify_base(button, GTK_STATE_NORMAL, &colorba);
    GtkStyle *style = gtk_widget_get_style(lab);
    pango_font_description_set_size(style->font_desc, 8*PANGO_SCALE);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_NORMAL);
    gtk_widget_modify_font(lab, style->font_desc);
    uiCheckButton* c = new uiCheckButton(&ui, zone, GTK_TOGGLE_BUTTON(button));
    g_signal_connect(GTK_OBJECT(button), "toggled",
                      G_CALLBACK(uiCheckButton::toggled), (gpointer) c);
    connect_midi_controller(button, zone);
    gtk_widget_show(lab);
}

void StackBoxBuilder::openHorizontalhideBox(const char* label) {
    GxHBox * box =  new GxHBox(ui);
    box->m_box.set_homogeneous(false);
    box->m_box.set_spacing(0);
    box->m_box.set_border_width(0);
    gtk_box_pack_start(GTK_BOX(fBox[fTop]), GTK_WIDGET(box->m_box.gobj()) , false, false, 5);
    manage(&box->m_box);
    pushBox(kBoxMode, GTK_WIDGET(box->m_box.gobj()));
    box->m_box.hide();
    if (label[0] != 0) box->m_box.show();
}

void StackBoxBuilder::openHorizontalTableBox(const char* label) {
    GxHBox * box =  new GxHBox(ui);
    box->m_box.set_homogeneous(false);
    box->m_box.set_spacing(0);
    box->m_box.set_border_width(0);

    if (fMode[fTop] != kTabMode && label[0] != 0) {
        box->m_frame.set_label(label);
        box->m_frame.set_shadow_type(Gtk::SHADOW_NONE);
        box->m_frame.add(box->m_box);
        gtk_box_pack_start(GTK_BOX(fBox[fTop]), GTK_WIDGET(box->m_frame.gobj()), false, fill, 0);
        box->m_box.show();
        box->m_frame.show();
        pushBox(kBoxMode, GTK_WIDGET(box->m_box.gobj()));
    } else {
        pushBox(kBoxMode, addWidget(label, GTK_WIDGET(box->m_box.gobj())));
    }
}

void StackBoxBuilder::openPaintBox2(const char* label) {
    GxEventBox * box =  new GxEventBox(ui);
    box->m_eventbox.set_name(label);
    box->m_box.set_homogeneous(false);
    box->m_box.set_spacing(0);
    box->m_box.set_border_width(0);
    gtk_box_pack_start(GTK_BOX(fBox[fTop]), GTK_WIDGET(box->m_hbox.gobj()), false, false, 0);
    box->m_hbox.show_all();
    pushBox(kBoxMode, GTK_WIDGET(box->m_box.gobj()));
}

void StackBoxBuilder::openTabBox(const char* label) {
    GxNotebookBox * box =  new GxNotebookBox(ui);
    pushBox(kTabMode, addWidget(label, GTK_WIDGET(box->m_box.gobj())));
}

void StackBoxBuilder::openpaintampBox(const char* label) {
    GxPaintBox * box =  new GxPaintBox(ui, pb_RackBox_expose);
    box->m_box.set_border_width(4);
    box->m_paintbox.set_name(label);
    box->m_paintbox.set_tooltip_text(label);
    gtk_box_pack_start(GTK_BOX(fBox[fTop]), GTK_WIDGET(box->m_paintbox.gobj()), expand, fill, 0);
    box->m_paintbox.show_all();
    pushBox(kBoxMode, GTK_WIDGET(box->m_box.gobj()));
}

void StackBoxBuilder::addCheckButton(string id, const char* label_) {
    Glib::ustring label(label_);
    if (!pmap.hasId(id)) {
        return;
    }
    const gx_engine::BoolParameter &p = pmap[id].getBool();
    if (label.empty()) {
        label = p.l_name();
    }
    addCheckButton(label.c_str(), &p.get_value());
}

void StackBoxBuilder::closeBox() {
    --fTop;
    assert(fTop >= 0);
}

void StackBoxBuilder::openHorizontalBox(const char* label) {
    GxHBox * box =  new GxHBox(ui);
    box->m_box.set_homogeneous(false);
    box->m_box.set_spacing(0);
    box->m_box.set_border_width(0);

    if (fMode[fTop] != kTabMode && label[0] != 0) {
        box->m_frame.set_label(label);
        box->m_frame.set_shadow_type(Gtk::SHADOW_NONE);
        box->m_frame.add(box->m_box);
        gtk_box_pack_start(GTK_BOX(fBox[fTop]), GTK_WIDGET(box->m_frame.gobj()), false, fill, 0);
        box->m_box.show();
        box->m_frame.show();
        pushBox(kBoxMode, GTK_WIDGET(box->m_box.gobj()));
    } else {
        pushBox(kBoxMode, addWidget(label, GTK_WIDGET(box->m_box.gobj())));
    }
}

void StackBoxBuilder::openVerticalBox(const char* label) {
    GxVBox * box =  new GxVBox(ui);
    box->m_box.set_homogeneous(false);
    box->m_box.set_spacing(0);
    box->m_box.set_border_width(0);

    if (fMode[fTop] != kTabMode && label[0] != 0) {
        box->m_label.set_text(label);
        box->m_label.set_name("rack_effect_label");
        GtkStyle *style = gtk_widget_get_style(GTK_WIDGET(box->m_label.gobj()));
        pango_font_description_set_size(style->font_desc, 8*PANGO_SCALE);
        pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
        gtk_widget_modify_font(GTK_WIDGET(box->m_label.gobj()), style->font_desc);
        box->m_box.pack_start(box->m_label, false, false, 0 );
        gtk_box_pack_start(GTK_BOX(fBox[fTop]), GTK_WIDGET(box->m_box.gobj()), false, fill, 0);
        box->m_box.show();
        box->m_label.show();
        pushBox(kBoxMode, GTK_WIDGET(box->m_box.gobj()));
    } else {
        pushBox(kBoxMode, addWidget(label, GTK_WIDGET(box->m_box.gobj())));
    }
}

void StackBoxBuilder::openFrameBox(const char* label) {
    GxHBox * box =  new GxHBox(ui);
    box->m_box.set_homogeneous(false);
    box->m_box.set_spacing(2);
    box->m_box.set_border_width(2);

    if (fMode[fTop] != kTabMode && label[0] != 0) {
        box->m_frame.set_label(label);
        box->m_frame.set_shadow_type(Gtk::SHADOW_NONE);
        box->m_frame.add(box->m_box);
        gtk_box_pack_start(GTK_BOX(fBox[fTop]), GTK_WIDGET(box->m_frame.gobj()), false, fill, 0);
        box->m_box.show();
        box->m_frame.show();
        pushBox(kBoxMode, GTK_WIDGET(box->m_box.gobj()));
    } else {
        pushBox(kBoxMode, addWidget(label, GTK_WIDGET(box->m_box.gobj())));
    }
}

} // end namespace gx_gui
