#include "guitarix.h"        // NOLINT

#include <glibmm/i18n.h>     // NOLINT

// -------- the gx_head user interface build instruktions

namespace gx_gui {

/****************************************************************
 ** class StackBoxBuilder
 */

StackBoxBuilder::StackBoxBuilder(
    int& fTop_, GtkWidget*(&fBox_)[stackSize], gx_engine::GxEngine& engine_,
    gx_engine::ParamMap& pmap_, int (&fMode_)[stackSize], MainMenu &mainmenu_,
    Gxw::WaveView &fWaveView_, Gtk::Label &convolver_filename_label_)
    : gx_ui::GxUI(), fTop(fTop_), fBox(fBox_), engine(engine_), pmap(pmap_),
      fMode(fMode_), mainmenu(mainmenu_), fWaveView(fWaveView_),
      convolver_filename_label(convolver_filename_label_) {
}

StackBoxBuilder::~StackBoxBuilder() {
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

void StackBoxBuilder::addSmallJConvFavButton(const char* label) {
    
    GtkWidget*     button = gtk_button_new();
    gtk_widget_set_name(button, "smallbutton");
    GtkWidget*     lab = gtk_label_new(label);
    GtkStyle *style = gtk_widget_get_style(lab);
    pango_font_description_set_size(style->font_desc, 7*PANGO_SCALE);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_NORMAL);
    gtk_widget_modify_font(lab, style->font_desc);
    gtk_container_add(GTK_CONTAINER(button), lab);
    //gtk_widget_set_size_request(GTK_WIDGET(button),-1,14);
    gtk_widget_set_name(lab, "rack_label");
    addWidget(label, button);
    gtk_widget_show(lab);

    g_signal_connect(GTK_OBJECT(button), "clicked",
                      G_CALLBACK(gx_jconv::gx_show_fav),
                      (gpointer) NULL);
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
    gtk_box_pack_start(GTK_BOX(fBox[fTop]), GTK_WIDGET(box->gobj()), false, fill, 0);
    pushBox(kBoxMode, GTK_WIDGET(box->gobj()));
}

void StackBoxBuilder::addJConvFavButton(const char* label) {
    
    GtkWidget*     button = gtk_button_new();

    GtkWidget*     lab = gtk_label_new(label);
    GtkStyle *style = gtk_widget_get_style(lab);
    pango_font_description_set_size(style->font_desc, 10*PANGO_SCALE);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_NORMAL);
    gtk_widget_modify_font(lab, style->font_desc);
    gtk_container_add(GTK_CONTAINER(button), lab);

    gtk_widget_set_name(lab, "beffekt_label");
    addWidget(label, button);
    gtk_widget_show(lab);

    
    g_signal_connect(GTK_OBJECT(button), "clicked",
                      G_CALLBACK(gx_jconv::gx_show_fav),
                      (gpointer) NULL);
}

void StackBoxBuilder::addJConvButton(const char* label, float* zone) {
    *zone = 0.0;
    GtkWidget*     button = gtk_button_new();

    GtkWidget*     lab = gtk_label_new(label);
    GtkStyle *style = gtk_widget_get_style(lab);
    pango_font_description_set_size(style->font_desc, 10*PANGO_SCALE);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_NORMAL);
    gtk_widget_modify_font(lab, style->font_desc);
    gtk_container_add(GTK_CONTAINER(button), lab);

    gtk_widget_set_name(lab, "beffekt_label");
    addWidget(label, button);
    gtk_widget_show(lab);

    uiButton* c = new uiButton(this, zone, GTK_BUTTON(button));
    g_signal_connect(GTK_OBJECT(button), "clicked",
                      G_CALLBACK(gx_jconv::gx_show_jconv_dialog_gui),
                      (gpointer) c);
}

void StackBoxBuilder::addJToggleButton(const char* label, bool* zone) {
    GdkColor colorRed;
    GdkColor colorOwn;
    gdk_color_parse("#58b45e", &colorRed);
    gdk_color_parse("#7f7f7f", &colorOwn);

    *zone = 0;

    GtkWidget*     button = gtk_toggle_button_new();
    GtkWidget*     lab = gtk_label_new(label);
    gtk_widget_set_name(lab, "beffekt_label");
    GtkStyle *style = gtk_widget_get_style(lab);

    pango_font_description_set_size(style->font_desc, 10*PANGO_SCALE);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
    gtk_widget_modify_font(lab, style->font_desc);
    gtk_container_add(GTK_CONTAINER(button), lab);
    addWidget(label, button);
    gtk_widget_show(lab);

    uiToggleButton* c =
        new uiToggleButton(this, zone, GTK_TOGGLE_BUTTON(button));

    gtk_widget_modify_bg(button, GTK_STATE_NORMAL, &colorOwn);
    gtk_widget_modify_bg(button, GTK_STATE_ACTIVE, &colorRed);

    g_signal_connect(GTK_OBJECT(button), "toggled",
                     G_CALLBACK(uiToggleButton::toggled), (gpointer) c);

    g_signal_connect(GTK_OBJECT(button), "toggled",
                     G_CALLBACK(gx_start_stop_jconv), (gpointer)c); //FIXME
    connect_midi_controller(button, zone);
}

void StackBoxBuilder::create_selector(string id, const char *widget_name) {
    gx_engine::Parameter& p = pmap[id];
    UiSelectorBase *s;
    if (p.isFloat()) {
        s = new UiSelector<float>(*this, p.getFloat());
    } else if (p.isInt()) {
        s = new UiSelector<int>(*this, p.getInt());
    } else {
        s = new UiSelector<unsigned int>(*this, p.getUInt());
    }
    if (widget_name) {
	s->set_name(widget_name);
    }
    addwidget(s->get_widget());
}

void StackBoxBuilder::openSpaceBox(const char* label) {
    GxVBox * box =  new GxVBox(*this);
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
    // gtk_container_set_border_width (GTK_CONTAINER(e_box),2);
    g_signal_connect(box, "expose-event", G_CALLBACK(gx_cairo::conv_widget_expose), NULL);
    gtk_widget_set_size_request(box, 303, 82);
    gtk_widget_set_size_request(e_box, 284, 54);
    gtk_container_set_border_width(GTK_CONTAINER(box), 12);
    gtk_container_add(GTK_CONTAINER(e_box), GTK_WIDGET(fWaveView.gobj()));
    // gtk_container_add(GTK_CONTAINER(box),e_box );
    gtk_box_pack_start(GTK_BOX(box), box1, true, true, 0);
    gtk_box_pack_start(GTK_BOX(box), e_box, false, false, 0);
    gtk_box_pack_start(GTK_BOX(box), box2, true, true, 0);
    addWidget(label, box);
    fWaveView.hide(); // was show()'n by addWidget
    fWaveView.property_text_pos_left() = 1.5;
    fWaveView.property_text_pos_right() = 77;
    fWaveView.set_multiplicator(150., 250.);
    gtk_widget_show_all(box);
    //gtk_widget_hide(e_box);
}

void StackBoxBuilder::openVerticalBox1(const char* label) {
    GxVBox * box =  new GxVBox(*this);
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
    GxVBox * box =  new GxVBox(*this);
    box->m_box.set_homogeneous(false);
    box->m_box.set_spacing(0);
    box->m_box.set_border_width(0);

    if (fMode[fTop] != kTabMode && label[0] != 0) {
        GxVBox * vbox =  new GxVBox(*this);
        vbox->m_box.set_homogeneous(false);
        vbox->m_box.set_spacing(0);
        vbox->m_box.set_border_width(0);

        GxHBox * hbox =  new GxHBox(*this);
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
    uiAdjustment* c = new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));
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
    GdkColor colorRed;
    GdkColor colorOwn;
    GdkColor colorwn;
    gdk_color_parse("#58b45e", &colorRed);
    gdk_color_parse("#000000", &colorwn);
    gdk_color_parse("#7f7f7f", &colorOwn);
    *zone = 0;
    GtkWidget*     button = gtk_toggle_button_new();
    GtkWidget*     lab = gtk_label_new(label);
    GtkStyle *style = gtk_widget_get_style(lab);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
    gtk_widget_modify_font(lab, style->font_desc);
    gtk_container_add(GTK_CONTAINER(button), lab);
    gtk_widget_set_size_request(GTK_WIDGET(button), 70, 20);
    GtkWidget * box = gtk_hbox_new(homogene, 4);
    GtkWidget * box1 = gtk_vbox_new(homogene, 4);
    gtk_container_set_border_width(GTK_CONTAINER(box), 0);
    gtk_container_set_border_width(GTK_CONTAINER(box1), 0);
    gtk_container_add(GTK_CONTAINER(box), box1);
    GtkWidget * box2 = gtk_vbox_new(homogene, 4);
    gtk_container_set_border_width(GTK_CONTAINER(box2), 0);
    gtk_widget_set_size_request(GTK_WIDGET(box2), 6, 20);
    gtk_container_add(GTK_CONTAINER(box), button);
    gtk_container_add(GTK_CONTAINER(box), box2);
    gtk_widget_set_size_request(GTK_WIDGET(box1), 6, 20);
    gtk_widget_show(button);
    gtk_widget_show(box1);
    gtk_widget_show(box2);
    gtk_widget_show(lab);
    gtk_widget_show(box);
    gtk_container_add(GTK_CONTAINER(fBox[fTop]), box);
    uiToggleButton* c = new uiToggleButton(this, zone, GTK_TOGGLE_BUTTON(button));
    gtk_widget_modify_bg(button, GTK_STATE_NORMAL, &colorOwn);
    gtk_widget_modify_bg(button, GTK_STATE_ACTIVE, &colorRed);
    gtk_widget_set_name(lab, "rack_label");
    g_signal_connect(GTK_OBJECT(button), "toggled",
                     G_CALLBACK(uiToggleButton::toggled), (gpointer) c);
    connect_midi_controller(button, zone);
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
    uiCheckButton* c = new uiCheckButton(this, zone, GTK_TOGGLE_BUTTON(button));
    g_signal_connect(GTK_OBJECT(button), "toggled",
                      G_CALLBACK(uiCheckButton::toggled), (gpointer) c);
    connect_midi_controller(button, zone);
    gtk_widget_show(lab);
}

void StackBoxBuilder::openHorizontalhideBox(const char* label) {
    GxHBox * box =  new GxHBox(*this);
    box->m_box.set_homogeneous(false);
    box->m_box.set_spacing(0);
    box->m_box.set_border_width(0);
    gtk_box_pack_start(GTK_BOX(fBox[fTop]), GTK_WIDGET(box->m_box.gobj()) , false, false, 5);
    manage(&box->m_box);
    pushBox(kBoxMode, GTK_WIDGET(box->m_box.gobj()));
    box->m_box.hide();
    if (label[0] != 0) box->m_box.show();
}

void StackBoxBuilder::openVerticalHideBox(const char* label) {
    string s = label;
    
    static bool hs = true;
    gx_engine::get_group_table().insert(s, s);
    s +=".s_h";
    pmap.reg_non_midi_par(s, &hs, false);
    gx_engine::Parameter& param_switch = pmap[s];
    GxVHideBox * box =  new GxVHideBox(*this, param_switch);
    box->m_box.set_homogeneous(false);
    box->m_box.set_spacing(0);
    box->m_box.set_border_width(4);
    //gtk_box_pack_start(GTK_BOX(fBox[fTop]), GTK_WIDGET(box->m_box.gobj()), false, fill, 0);
    box->m_box.show_all();
    pushBox(kBoxMode, addWidget(label, GTK_WIDGET(box->m_box.gobj())));
    
}

void StackBoxBuilder::openHorizontalTableBox(const char* label) {
    GxHBox * box =  new GxHBox(*this);
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
    GxEventBox * box =  new GxEventBox(*this);
    box->m_eventbox.set_name(label);
    box->m_box.set_homogeneous(false);
    box->m_box.set_spacing(0);
    box->m_box.set_border_width(0);
    gtk_box_pack_start(GTK_BOX(fBox[fTop]), GTK_WIDGET(box->m_hbox.gobj()), false, false, 0);
    box->m_hbox.show_all();
    pushBox(kBoxMode, GTK_WIDGET(box->m_box.gobj()));
}

void StackBoxBuilder::openTabBox(const char* label) {
    GxNotebookBox * box =  new GxNotebookBox(*this);
    pushBox(kTabMode, addWidget(label, GTK_WIDGET(box->m_box.gobj())));
}

void StackBoxBuilder::openpaintampBox(const char* label) {
    GxPaintBox * box =  new GxPaintBox(*this, pb_RackBox_expose);
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
    GxHBox * box =  new GxHBox(*this);
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
    GxVBox * box =  new GxVBox(*this);
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
    GxHBox * box =  new GxHBox(*this);
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

/****************************************************************
 ** class StackBoxBuilderOld
 */

StackBoxBuilderOld::StackBoxBuilderOld(
    int& fTop_, GtkWidget*(&fBox_)[stackSize], gx_engine::GxEngine& engine_,
    gx_engine::ParamMap& pmap_, GtkWidget* fMonoRackContainer_, GtkWidget* fStereoRackContainer_,
    GtkWidget*& rBox_, GtkWidget*& sBox_, GtkWidget*& tBox_, int (&fMode_)[stackSize],
    MainMenu &mainmenu_, Gxw::WaveView &fWaveView_, Glib::RefPtr<Gtk::AccelGroup> fAccelGroup_,
    Gtk::Label &convolver_filename_label_)
    : StackBoxBuilder(fTop_, fBox_, engine_, pmap_, fMode_, mainmenu_, fWaveView_, convolver_filename_label_),
      rBox(rBox_), sBox(sBox_), tBox(tBox_), fAccelGroup(fAccelGroup_),
      fMonoRackContainer(fMonoRackContainer_), fStereoRackContainer(fStereoRackContainer_) {
}

/****************************************************************
 ** class StackBoxBuilderOld
 */

void StackBoxBuilderOld::openMonoRackBox(const char* label, int* posit, const char *id_on_off,
				      const char *id_pre_post, const char *id_dialog) {
    fBox[++fTop] = fMonoRackContainer;
    fMode[fTop] = kBoxMode;
    string group = id_on_off;
    string group_id = group.substr(0, group.find_last_of("."));
    GtkWidget* box = openHorizontalOrderBox(group_id.c_str(), posit);
    openHorizontalhideBox("");
    create_switch_no_caption(sw_minitoggle, id_on_off);
    closeBox();
    openVerticalBox(label);
    openHorizontalBox("");
    openPaintBox1("");
    create_switch_no_caption(sw_switchit, id_on_off);
    if (id_pre_post) {
	create_selector(id_pre_post);
    }
    closeBox();
    
    openDialogBox(id_dialog, id_on_off, "RackBox_expose", box);
}

void StackBoxBuilderOld::closeMonoRackBox() {
    closeBox();
    closeBox();
    closeBox();
    closeBox();
    --fTop;
}

void StackBoxBuilderOld::openStereoRackBox(const char* label, int* posit, const char *id_on_off,
				      const char *id_dialog) {
    fBox[++fTop] = fStereoRackContainer;
    fMode[fTop] = kBoxMode;
    string group = id_on_off;
    string group_id = group.substr(0, group.find_last_of("."));
    GtkWidget* box = openHorizontalRestetBox(group_id.c_str(), posit);
    openHorizontalhideBox("");
    create_switch_no_caption(sw_minitoggle, id_on_off);
    closeBox();
    openVerticalBox(label);
    openHorizontalTableBox("");
    openPaintBox1("");
    openHorizontalBox("");
    create_switch_no_caption(sw_switchit, id_on_off);
    closeBox();
    closeBox();
    opensDialogBox(id_dialog, id_on_off, "RackBox_expose", box);
}

void StackBoxBuilderOld::closeStereoRackBox() {
    closeBox();
    closeBox();
    closeBox();
    closeBox();
    --fTop;
}

GtkWidget* StackBoxBuilderOld::openHorizontalRestetBox(const char* label, int* posit) {
    string p = label;
    p +=".s_h";
    gx_engine::Parameter& param_switch = pmap[p];
    //gx_engine::SwitchParameter* param_switch = new gx_engine::SwitchParameter(p, true, false);
    GxMoveBox * box =  new GxMoveBox(*this, param_switch);
    uiOrderButton* c = new uiOrderButton(this, posit, GTK_BUTTON(box->m_button.gobj()));

    g_signal_connect(GTK_OBJECT(box->m_button.gobj()), "pressed",
                      G_CALLBACK(uiOrderButton::pressed_right), (gpointer) c);
    g_signal_connect(GTK_OBJECT(box->m_button1.gobj()), "pressed",
                      G_CALLBACK(uiOrderButton::pressed_left), (gpointer) c);
    g_signal_connect(GTK_OBJECT(box->m_button.gobj()), "clicked",
                      G_CALLBACK(uiOrderButton::clicked), (gpointer) c);
    g_signal_connect(GTK_OBJECT(box->m_button1.gobj()), "clicked",
                      G_CALLBACK(uiOrderButton::clicked), (gpointer) c);
    gtk_box_pack_start(GTK_BOX(sBox), GTK_WIDGET(box->m_paintbox.gobj()), expand, false, 0);
    GValue  pos = {0};
    g_value_init(&pos, G_TYPE_INT);
    g_value_set_int(&pos, *posit);
    string tooltip = _("Move ");
    tooltip += label;
    tooltip += _(" up");
    box->m_button1.set_tooltip_text(tooltip);
    box->m_button1.get_accessible()->set_description(tooltip);
    box->m_button1.get_accessible()->set_name(label);
    tooltip = _("Move ");
    tooltip += label;
    tooltip += _(" down");
    box->m_button.set_tooltip_text(tooltip);
    box->m_button.get_accessible()->set_description(tooltip);
    box->m_button.get_accessible()->set_name(label);
    gtk_container_child_set_property(GTK_CONTAINER(sBox),
                                     GTK_WIDGET(box->m_paintbox.gobj()), "position", &pos);
    GtkWidget* mainbox = GTK_WIDGET(box->m_paintbox.gobj());
    pushBox(kBoxMode, mainbox);
    return mainbox;
}

void StackBoxBuilderOld::opensDialogBox(const char *id_dialog, const char *id_switch,
                                     const char *expose_funk, GtkWidget* box) {
    gx_engine::Parameter& param_dialog = pmap[id_dialog];
    gx_engine::Parameter& param_switch = pmap[id_switch];
    GxDialogButtonBox *bbox = new GxDialogButtonBox(*this, param_dialog);

    guivar.stereo_plugs++;
    gtk_box_pack_end(GTK_BOX(box), GTK_WIDGET(bbox->box.gobj()), false, false, 0);
    GxDialogWindowBox *bdialog = new GxDialogWindowBox(*this, expose_funk, param_dialog,
                                 param_switch, bbox->show_dialog, gw.srack_widget);
    gtk_box_pack_start(GTK_BOX(box), GTK_WIDGET(bdialog->paintbox.gobj()) , true, fill, 0);
    pushBox(kBoxMode, GTK_WIDGET(bdialog->box.gobj()));

    const gchar * title = gtk_widget_get_name(GTK_WIDGET(bdialog->paintbox.gobj()));
    bdialog->menuitem.set_label(title);
    string p = "ui.";
    p +=title;
    string s;

    guint accel_key = GDK_t  + guivar.stereo_plugs;
    if (accel_key <= GDK_z) {
	bdialog->menuitem.add_accelerator(
	    "activate", fAccelGroup, accel_key,
	    Gdk::LOCK_MASK, Gtk::ACCEL_VISIBLE);
    }
    mainmenu.plugin_stereo_menu.append(bdialog->menuitem);
    bdialog->menuitem.show();
    //bdialog->menuitem.set_parameter(new SwitchParameter(p, true, false));

    //bdialog->m_tcb.set_parameter(&param_dialog);
    gtk_box_pack_start(GTK_BOX(tBox), GTK_WIDGET(bdialog->box1.gobj()) , false, false, 0);
    bdialog->box1.pack_start(bdialog->m_tcb, true, true);
    string tooltip = "Show ";
    tooltip +=title;
    bdialog->m_tcb.set_tooltip_text(tooltip.c_str());
    bdialog->box1.show_all();
    bdialog->paintbox.show_all();
    // gtk_box_pack_start (GTK_BOX(tBox),GTK_WIDGET(bdialog->m_tcb.gobj()) , false, false, 0);
}

void StackBoxBuilderOld::openDialogBox(const char *id_dialog, const char *id_switch,
                                    const char *expose_funk, GtkWidget* box) {
    gx_engine::Parameter& param_dialog = pmap[id_dialog];
    gx_engine::Parameter& param_switch = pmap[id_switch];
    GxDialogButtonBox *bbox = new GxDialogButtonBox(*this, param_dialog);
    guivar.mono_plugs++;
    gtk_box_pack_end(GTK_BOX(box), GTK_WIDGET(bbox->box.gobj()), false, false, 0);
    GxDialogWindowBox *dialog = new GxDialogWindowBox(*this, expose_funk, param_dialog,
                                param_switch, bbox->show_dialog, gw.rack_widget);
    gtk_box_pack_start(GTK_BOX(box), GTK_WIDGET(dialog->paintbox.gobj()) , true, fill, 0);
    pushBox(kBoxMode, GTK_WIDGET(dialog->box.gobj()));

    const gchar * title = gtk_widget_get_name(GTK_WIDGET(dialog->paintbox.gobj()));
    string p = "ui.";
    p +=title;
    dialog->menuitem.set_label(title);
    guint accel_key = GDK_a + guivar.mono_plugs;
    dialog->menuitem.add_accelerator(
	"activate", fAccelGroup, accel_key,
	Gdk::LOCK_MASK, Gtk::ACCEL_VISIBLE);  // FIXME MOD1_MASK
    mainmenu.plugin_mono_menu.append(dialog->menuitem);
    dialog->menuitem.show();
    //dialog->menuitem.set_parameter(new SwitchParameter(p, true, false));

    //dialog->m_tcb.set_parameter(&param_dialog);
    gtk_box_pack_start(GTK_BOX(tBox), GTK_WIDGET(dialog->box1.gobj()) , false, false, 0);
    dialog->box1.pack_start(dialog->m_tcb, true, true);
    string tooltip = "Show ";
    tooltip +=title;
    dialog->m_tcb.set_tooltip_text(tooltip.c_str());
    dialog->box1.show_all();
    dialog->paintbox.show_all();
}

GtkWidget *StackBoxBuilderOld::openHorizontalOrderBox(const char* label, int* posit) {
    string p = label;
    p +=".s_h";
    gx_engine::Parameter& param_switch = pmap[p];
    //gx_engine::SwitchParameter* param_switch = new gx_engine::SwitchParameter(p, true, false);
    GxMoveBox * box =  new GxMoveBox(*this, param_switch);
    uiOrderButton* c = new uiOrderButton(this, posit, GTK_BUTTON(box->m_button.gobj()));

    g_signal_connect(GTK_OBJECT(box->m_button.gobj()), "pressed",
                     G_CALLBACK(uiOrderButton::pressed_right), (gpointer) c);
    g_signal_connect(GTK_OBJECT(box->m_button1.gobj()), "pressed",
                     G_CALLBACK(uiOrderButton::pressed_left), (gpointer) c);
    g_signal_connect(GTK_OBJECT(box->m_button.gobj()), "clicked",
                     G_CALLBACK(uiOrderButton::clicked), (gpointer) c);
    g_signal_connect(GTK_OBJECT(box->m_button1.gobj()), "clicked",
                     G_CALLBACK(uiOrderButton::clicked), (gpointer) c);
    gtk_box_pack_start(GTK_BOX(rBox), GTK_WIDGET(box->m_paintbox.gobj()), expand, false, 0);
    GValue  pos = {0};
    g_value_init(&pos, G_TYPE_INT);
    g_value_set_int(&pos, *posit);
    gtk_container_child_set_property(GTK_CONTAINER(rBox),
				     GTK_WIDGET(box->m_paintbox.gobj()), "position", &pos);
    string tooltip = _("Move ");
    tooltip += label;
    tooltip += _(" up");
    box->m_button1.set_tooltip_text(tooltip);
    box->m_button1.get_accessible()->set_description(tooltip);
    box->m_button1.get_accessible()->set_name(label);
    tooltip = _("Move ");
    tooltip += label;
    tooltip += _(" down");
    box->m_button.set_tooltip_text(tooltip);
    box->m_button.get_accessible()->set_description(tooltip);
    box->m_button.get_accessible()->set_name(label);
    tooltip = _("show/hide ");
    tooltip += label;
    tooltip += _(" controller");
    box->m_button2.set_tooltip_text(tooltip);
    box->m_button2.get_accessible()->set_description(tooltip);
    box->m_button2.get_accessible()->set_name(label);
    
    GtkWidget* mainbox = GTK_WIDGET(box->m_paintbox.gobj());
    pushBox(kBoxMode, mainbox);
    return mainbox;
}

void StackBoxBuilderOld::openPaintBox1(const char* label) {
    GxVBox * box =  new GxVBox(*this);
    box->m_box.set_homogeneous(false);
    box->m_box.set_spacing(0);
    box->m_box.set_border_width(0);
    box->m_box.set_size_request(60, -1);
    box->m_box.show_all();
    gtk_box_pack_start(GTK_BOX(fBox[fTop]), GTK_WIDGET(box->m_box.gobj()), expand, fill, 0);
    pushBox(kBoxMode, GTK_WIDGET(box->m_box.gobj()));
}

void StackBoxBuilderOld::openVerticalMidiBox(const char* label) {
    GxMidiBox * box =  new GxMidiBox(*this, pb_eq_expose);
    gw.midibox = GTK_WIDGET(box->m_eventbox.gobj());
    // gtk_container_add (GTK_CONTAINER(rBox), gw.midibox);
    gtk_box_pack_end(GTK_BOX(rBox), GTK_WIDGET(gw.midibox) , false, false, 0);
    gtk_widget_show_all(gw.midibox);
    pushBox(kBoxMode, GTK_WIDGET(box->m_box.gobj()));
    gtk_widget_hide(gw.midibox);

    GList*   child_list =  gtk_container_get_children(GTK_CONTAINER(gw.rack_tool_bar));
    GtkWidget *box1 = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 0));
    child_list =  gtk_container_get_children(GTK_CONTAINER(box1));
    box1 = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 0));
    child_list =  gtk_container_get_children(GTK_CONTAINER(box1));
    box1 = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 0));
    child_list =  gtk_container_get_children(GTK_CONTAINER(box1));
    box1 = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 0));
    child_list =  gtk_container_get_children(GTK_CONTAINER(box1));
    box1 = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 0));
    child_list =  gtk_container_get_children(GTK_CONTAINER(box1));
    box1 = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 0));
    g_list_free(child_list);
    box->m_tcb.set_parameter(mainmenu.fShowMidiOut.get_parameter());
    box->m_tcb.m_label.set_text(_("MIDI out"));
    gtk_container_add(GTK_CONTAINER(box1), GTK_WIDGET(box->m_bbox.gobj()));
}

} // end namespace gx_gui
