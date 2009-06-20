/******************************************************************************
*******************************************************************************

								GRAPHIC USER INTERFACE
								  gtk interface
            #include "GTKUI.h"
	GTKUI.cpp
	here are the virtuell discriptions from the included GTK_WIDGET for guitarix
*******************************************************************************
*******************************************************************************/

// create main window
GTKUI::GTKUI(char * name, int* pargc, char*** pargv)
{
    if (!fInitialized)
    {
        gtk_init(pargc, pargv);
        fInitialized = true;
    }
    /*-- set rc file overwrite it with export--*/

    gtk_rc_parse(rcpath);
    /*-- Check for working directory to save and load presets --*/
    const char*	  home;
    const char*      pathname = ".guitarix";
    char                dirname[256];
    home = getenv ("HOME");
    if (home == 0) home = ".";
    snprintf(dirname, 256, "%s/%s", home, pathname);
    gx_version_check( dirname);
    /*-- Declare the GTK Widgets --*/
    fWindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    /*---------------- set window defaults ----------------*/
    gtk_window_set_resizable(GTK_WINDOW (fWindow) , FALSE);
    gtk_window_set_title (GTK_WINDOW (fWindow), name);

    /*---------------- singnals ----------------*/
    g_signal_connect (GTK_OBJECT (fWindow), "delete_event", G_CALLBACK (gx_delete_event), NULL);
    g_signal_connect (GTK_OBJECT (fWindow), "destroy", G_CALLBACK (gx_destroy_event), NULL);
    /*---------------- status icon ----------------*/
    if (gx_pixmap_check() == 0)
    {
        status_icon =    gtk_status_icon_new_from_pixbuf (GDK_PIXBUF(ib));
        gtk_window_set_icon(GTK_WINDOW (fWindow), GDK_PIXBUF(ib));
        g_signal_connect (G_OBJECT (status_icon), "activate", G_CALLBACK (gx_hide_extendet_settings), NULL);
        g_signal_connect (G_OBJECT (status_icon), "popup-menu", G_CALLBACK (gx_sytray_menu), NULL);
    }
    /*---------------- create boxes ----------------*/
    fTop = 0;
    fBox[fTop] = gtk_vbox_new (homogene, 4);
    fMode[fTop] = kBoxMode;

    /*---------------- add mainbox to main window ---------------*/
    gtk_container_add (GTK_CONTAINER (fWindow), fBox[fTop]);

    fStopped = false;
}

// empilement des boites

void GTKUI::pushBox(int mode, GtkWidget* w)
{
    assert(++fTop < stackSize);
    fMode[fTop] 	= mode;
    fBox[fTop] 		= w;
}

void GTKUI::closeBox()
{
    assert(--fTop >= 0);
}

// les differentes boites

void GTKUI::openFrameBox(const char* label)
{
    GtkWidget * box = gtk_hbox_new (homogene, 2);
    gtk_container_set_border_width (GTK_CONTAINER (box), 2);

    if (fMode[fTop] != kTabMode && label[0] != 0)
    {
        GtkWidget * frame = addWidget(label, gtk_frame_new (label));
        gtk_frame_set_shadow_type(GTK_FRAME(frame),GTK_SHADOW_NONE);
        gtk_container_add (GTK_CONTAINER(frame), box);
        gtk_widget_show(box);
        pushBox(kBoxMode, box);
    }
    else
    {
        pushBox(kBoxMode, addWidget(label, box));
    }


    /* GtkWidget * box = gtk_frame_new (label);
     gtk_frame_set_shadow_type(GTK_FRAME(box),GTK_SHADOW_ETCHED_OUT);
     pushBox(kSingleMode, addWidget(label, box));*/
}

void GTKUI::openTabBox(const char* label)
{
    pushBox(kTabMode, addWidget(label, gtk_notebook_new ()));
}

void GTKUI::openHorizontalBox(const char* label)
{
    GtkWidget * box = gtk_hbox_new (homogene, 0);
    gtk_container_set_border_width (GTK_CONTAINER (box), 0);

    if (fMode[fTop] != kTabMode && label[0] != 0)
    {
        GtkWidget * frame = addWidget(label, gtk_frame_new (label));
        gtk_frame_set_shadow_type(GTK_FRAME(frame),GTK_SHADOW_NONE);
        gtk_container_add (GTK_CONTAINER(frame), box);
        gtk_widget_show(box);
        pushBox(kBoxMode, box);
    }
    else
    {
        pushBox(kBoxMode, addWidget(label, box));
    }
}

void GTKUI::openHandleBox(const char* label)
{
    GtkWidget * box = gtk_hbox_new (homogene, 4);
    gtk_container_set_border_width (GTK_CONTAINER (box), 2);
    if (fMode[fTop] != kTabMode && label[0] != 0)
    {
        GtkWidget * frame = addWidget(label, gtk_handle_box_new ());
        gtk_container_add (GTK_CONTAINER(frame), box);
        gtk_widget_show(box);
        pushBox(kBoxMode, box);
    }
    else
    {
        pushBox(kBoxMode, addWidget(label, box));
    }
}

void GTKUI::openEventBox(const char* label)
{
    GtkWidget * box = gtk_hbox_new (homogene, 4);
    gtk_container_set_border_width (GTK_CONTAINER (box), 2);
    if (fMode[fTop] != kTabMode && label[0] != 0)
    {
        GtkWidget * frame = addWidget(label, gtk_event_box_new ());
        gtk_container_add (GTK_CONTAINER(frame), box);
        gtk_widget_show(box);
        pushBox(kBoxMode, box);
    }
    else
    {
        pushBox(kBoxMode, addWidget(label, box));
    }
}

struct uiExpanderBox : public uiItem
{
    GtkExpander* fButton;
    uiExpanderBox(UI* ui, float* zone, GtkExpander* b) : uiItem(ui, zone), fButton(b) {}
    static void expanded (GtkWidget *widget, gpointer data)
    {
        float	v = gtk_expander_get_expanded  (GTK_EXPANDER(widget));
        if (v == 1.000000)
        {
            v = 0;
        }
        else v = 1;
        ((uiItem*)data)->modifyZone(v);
    }

    virtual void reflectZone()
    {
        float 	v = *fZone;
        fCache = v;
        gtk_expander_set_expanded(GTK_EXPANDER(fButton), v);
    }
};

void GTKUI::openExpanderBox(const char* label, float* zone)
{
    *zone = 0.0;
    GtkWidget * box = gtk_hbox_new (homogene, 0);
    gtk_container_set_border_width (GTK_CONTAINER (box), 0);
    if (fMode[fTop] != kTabMode && label[0] != 0)
    {
        GtkWidget * frame = addWidget(label, gtk_expander_new (label));
        gtk_container_add (GTK_CONTAINER(frame), box);
        uiExpanderBox* c = new uiExpanderBox(this, zone, GTK_EXPANDER(frame));
        g_signal_connect (GTK_OBJECT (frame), "activate", G_CALLBACK (uiExpanderBox::expanded), (gpointer)c);
        gtk_widget_show(box);
        pushBox(kBoxMode, box);
    }
    else
    {
        pushBox(kBoxMode, addWidget(label, box));
    }
}

void GTKUI::openVerticalBox(const char* label)
{
    GtkWidget * box = gtk_vbox_new (homogene, 0);
    gtk_container_set_border_width (GTK_CONTAINER (box), 0);
    if (fMode[fTop] != kTabMode && label[0] != 0)
    {
        // GtkWidget * frame = addWidget(label, gtk_frame_new (label));
        // gtk_frame_set_shadow_type(GTK_FRAME(frame),GTK_SHADOW_NONE);
        GtkWidget* lw = gtk_label_new(label);
        GdkColor colorGreen;
        gdk_color_parse("#a6a9aa", &colorGreen);
        gtk_widget_modify_fg (lw, GTK_STATE_NORMAL, &colorGreen);
        GtkStyle *style = gtk_widget_get_style(lw);
        pango_font_description_set_size(style->font_desc, 8*PANGO_SCALE);
        pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
        gtk_widget_modify_font(lw, style->font_desc);
        gtk_container_add (GTK_CONTAINER(box), lw);
        gtk_box_pack_start (GTK_BOX(fBox[fTop]), box, expand, fill, 0);
        gtk_widget_show(lw);
        gtk_widget_show(box);
        pushBox(kBoxMode, box);
    }
    else
    {
        pushBox(kBoxMode, addWidget(label, box));
    }
}

void GTKUI::openVerticalBox1(const char* label)
{
    GtkWidget * box = gtk_vbox_new (homogene, 0);
    gtk_container_set_border_width (GTK_CONTAINER (box), 0);
    if (fMode[fTop] != kTabMode && label[0] != 0)
    {
        // GtkWidget * frame = addWidget(label, gtk_frame_new (label));
        // gtk_frame_set_shadow_type(GTK_FRAME(frame),GTK_SHADOW_NONE);
        GtkWidget* lw = gtk_label_new(label);
        GdkColor colorGreen;
        gdk_color_parse("#a6a9aa", &colorGreen);
        gtk_widget_modify_fg (lw, GTK_STATE_NORMAL, &colorGreen);
        GtkStyle *style = gtk_widget_get_style(lw);
        pango_font_description_set_size(style->font_desc, 6*PANGO_SCALE);
        pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_LIGHT);
        gtk_widget_modify_font(lw, style->font_desc);
        gtk_container_add (GTK_CONTAINER(box), lw);
        gtk_box_pack_start (GTK_BOX(fBox[fTop]), box, expand, fill, 0);
        gtk_widget_show(lw);
        gtk_widget_show(box);
        pushBox(kBoxMode, box);
    }
    else
    {
        pushBox(kBoxMode, addWidget(label, box));
    }
}

void GTKUI::openVerticalMidiBox(const char* label)
{
    midibox = gtk_vbox_new (homogene, 4);
    gtk_container_set_border_width (GTK_CONTAINER (midibox), 2);
    if (fMode[fTop] != kTabMode && label[0] != 0)
    {
        GtkWidget * frame = addWidget(label, gtk_frame_new (label));
        gtk_container_add (GTK_CONTAINER(frame), midibox);
        gtk_widget_show(midibox);
        pushBox(kBoxMode, midibox);
    }
    else
    {
        pushBox(kBoxMode, addWidget(label, midibox));
    }
    gtk_widget_hide(midibox);
}

GtkWidget* GTKUI::addWidget(const char* label, GtkWidget* w)
{
    switch (fMode[fTop])
    {
    case kSingleMode	:
        gtk_container_add (GTK_CONTAINER(fBox[fTop]), w);
        break;
    case kBoxMode 		:
        gtk_box_pack_start (GTK_BOX(fBox[fTop]), w, expand, fill, 0);
        break;
    case kTabMode 		:
        gtk_notebook_append_page (GTK_NOTEBOOK(fBox[fTop]), w, gtk_label_new(label));
        break;
    }
    gtk_widget_show (w);
    return w;
}

// --------------------------- Press button ---------------------------

struct uiButton : public uiItem
{
    GtkButton* 	fButton;
    uiButton (UI* ui, float* zone, GtkButton* b) : uiItem(ui, zone), fButton(b) {}
    static void pressed( GtkWidget *widget, gpointer   data )
    {
        uiItem* c = (uiItem*) data;
        c->modifyZone(1.0);
    }

    static void released( GtkWidget *widget, gpointer   data )
    {
        uiItem* c = (uiItem*) data;
        c->modifyZone(0.0);
    }

    virtual void reflectZone()
    {
        float 	v = *fZone;
        fCache = v;
        if (v > 0.0) gtk_button_pressed(fButton);
        else gtk_button_released(fButton);
    }
};

void GTKUI::addButton(const char* label, float* zone)
{
    *zone = 0.0;
    GtkWidget* 	button = gtk_button_new_with_label (label);
    addWidget(label, button);
    uiButton* c = new uiButton(this, zone, GTK_BUTTON(button));
    g_signal_connect (GTK_OBJECT (button), "pressed", G_CALLBACK (uiButton::pressed), (gpointer) c);
    g_signal_connect (GTK_OBJECT (button), "released", G_CALLBACK (uiButton::released), (gpointer) c);
    g_signal_connect (GTK_OBJECT (button), "clicked", G_CALLBACK (fls), button);
}

// ---------------------------	Toggle Buttons ---------------------------

struct uiToggleButton : public uiItem
{
    GtkToggleButton* fButton;
    uiToggleButton(UI* ui, float* zone, GtkToggleButton* b) : uiItem(ui, zone), fButton(b) {}
    static void toggled (GtkWidget *widget, gpointer data)
    {
        float	v = (GTK_TOGGLE_BUTTON (widget)->active) ? 1.0 : 0.0;
        ((uiItem*)data)->modifyZone(v);
    }

    virtual void reflectZone()
    {
        float 	v = *fZone;
        fCache = v;
        gtk_toggle_button_set_active(fButton, v > 0.0);
    }
};

void GTKUI::addToggleButton(const char* label, float* zone)
{
    GdkColor colorRed;
    GdkColor colorOwn;
    gdk_color_parse ("#d56161", &colorRed);
    gdk_color_parse ("#7f7f7f", &colorOwn);
    float local_zone = 0.0;
    if (zone) local_zone = *zone;
    GtkWidget* 	button = gtk_toggle_button_new_with_label (label);
    addWidget(label, button);
    uiToggleButton* c = new uiToggleButton(this, &local_zone, GTK_TOGGLE_BUTTON(button));
    gtk_widget_modify_bg (button, GTK_STATE_NORMAL, &colorOwn);
    gtk_widget_modify_bg (button, GTK_STATE_ACTIVE, &colorRed);
    g_signal_connect (GTK_OBJECT (button), "toggled", G_CALLBACK (uiToggleButton::toggled), (gpointer) c);
    g_signal_connect (GTK_OBJECT (button), "toggled", G_CALLBACK (gx_run_jack_capture), (gpointer) c);
}

void GTKUI::addPToggleButton(const char* label, float* zone)
{
    GdkColor colorRed;
    GdkColor colorOwn;
    GdkColor colorwn;
    gdk_color_parse ("#58b45e", &colorRed);
    gdk_color_parse ("#000000", &colorwn);
    gdk_color_parse ("#7f7f7f", &colorOwn);
    *zone = 0.0;
    GtkWidget* 	button = gtk_toggle_button_new();
    GtkWidget* 	lab = gtk_label_new(label);
    GtkStyle *style = gtk_widget_get_style(lab);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
    gtk_widget_modify_font(lab, style->font_desc);
    gtk_container_add (GTK_CONTAINER(button), lab);
    gtk_widget_set_size_request (GTK_WIDGET(button), 60.0, 20.0);
    GtkWidget * box = gtk_hbox_new (homogene, 4);
    GtkWidget * box1 = gtk_vbox_new (homogene, 4);
    gtk_container_set_border_width (GTK_CONTAINER (box), 0);
    gtk_container_set_border_width (GTK_CONTAINER (box1), 0);
    gtk_container_add (GTK_CONTAINER(box), box1);
    GtkWidget * box2 = gtk_vbox_new (homogene, 4);
    gtk_container_set_border_width (GTK_CONTAINER (box2), 0);
    gtk_widget_set_size_request (GTK_WIDGET(box2), 6.0, 20.0);
    gtk_container_add (GTK_CONTAINER(box), button);
    gtk_container_add (GTK_CONTAINER(box), box2);
    gtk_widget_set_size_request (GTK_WIDGET(box1), 6.0, 20.0);
    gtk_widget_show (button);
    gtk_widget_show (box1);
    gtk_widget_show (box2);
    gtk_widget_show (lab);
    gtk_widget_show (box);
    gtk_container_add (GTK_CONTAINER(fBox[fTop]), box);
    uiToggleButton* c = new uiToggleButton(this, zone, GTK_TOGGLE_BUTTON(button));
    gtk_widget_modify_bg (button, GTK_STATE_NORMAL, &colorOwn);
    gtk_widget_modify_bg (button, GTK_STATE_ACTIVE, &colorRed);
    gtk_widget_modify_fg (lab, GTK_STATE_ACTIVE, &colorwn);
    g_signal_connect (GTK_OBJECT (button), "toggled", G_CALLBACK (uiToggleButton::toggled), (gpointer) c);
}

void GTKUI::addJToggleButton(const char* label, float* zone)
{
    JCONV_SETTINGS myJCONV_SETTINGS;
    GdkColor colorRed;
    GdkColor colorOwn;
    GdkColor colorwn;
    gdk_color_parse ("#58b45e", &colorRed);
    gdk_color_parse ("#000000", &colorwn);
    gdk_color_parse ("#7f7f7f", &colorOwn);
    *zone = 0.0;
    GtkWidget* 	button = gtk_toggle_button_new();
    GtkWidget* 	lab = gtk_label_new(label);
    GtkStyle *style = gtk_widget_get_style(lab);
    pango_font_description_set_size(style->font_desc, 10*PANGO_SCALE);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
    gtk_widget_modify_font(lab, style->font_desc);
    gtk_container_add (GTK_CONTAINER(button), lab);
    addWidget(label, button);
    gtk_widget_show (lab);
    uiToggleButton* c = new uiToggleButton(this, zone, GTK_TOGGLE_BUTTON(button));
    gtk_widget_modify_bg (button, GTK_STATE_NORMAL, &colorOwn);
    gtk_widget_modify_bg (button, GTK_STATE_ACTIVE, &colorRed);
    gtk_widget_modify_fg (lab, GTK_STATE_ACTIVE, &colorwn);
    g_signal_connect (GTK_OBJECT (button), "toggled", G_CALLBACK (uiToggleButton::toggled), (gpointer) c);
    g_signal_connect (GTK_OBJECT (button), "toggled", G_CALLBACK (rjv), (gpointer) c);
    myJCONV_SETTINGS.get_jconfset ();
}

// ---------------------------	Check Button ---------------------------

struct uiCheckButton : public uiItem
{
    GtkToggleButton* fButton;
    uiCheckButton(UI* ui, float* zone, GtkToggleButton* b) : uiItem(ui, zone), fButton(b) {}
    static void toggled (GtkWidget *widget, gpointer data)
    {
        float	v = (GTK_TOGGLE_BUTTON (widget)->active) ? 1.0 : 0.0;
        ((uiItem*)data)->modifyZone(v);
    }

    virtual void reflectZone()
    {
        float 	v = *fZone;
        fCache = v;
        gtk_toggle_button_set_active(fButton, v > 0.0);
    }
};

void GTKUI::addCheckButton(const char* label, float* zone)
{
    GdkColor   colorRed;
    GdkColor   colorOwn;
    GdkColor   colorba;
    gdk_color_parse ("#000000", &colorRed);
    gdk_color_parse ("#4c5159", &colorOwn);
    gdk_color_parse ("#c4c0c0", &colorba);
    GtkWidget* 	lab = gtk_label_new(label);
    GtkWidget* 	button = gtk_check_button_new ();
    gtk_container_add (GTK_CONTAINER(button), lab);
    addWidget(label, button);
    gtk_widget_modify_bg (button, GTK_STATE_PRELIGHT, &colorOwn);
    gtk_widget_modify_fg (button, GTK_STATE_PRELIGHT, &colorRed);
    gtk_widget_modify_text (button, GTK_STATE_NORMAL, &colorRed);
    gtk_widget_modify_base (button, GTK_STATE_NORMAL, &colorba);
    GtkStyle *style = gtk_widget_get_style(lab);
    pango_font_description_set_size(style->font_desc, 8*PANGO_SCALE);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_LIGHT);
    gtk_widget_modify_font(lab, style->font_desc);
    uiCheckButton* c = new uiCheckButton(this, zone, GTK_TOGGLE_BUTTON(button));
    g_signal_connect (GTK_OBJECT (button), "toggled", G_CALLBACK(uiCheckButton::toggled), (gpointer) c);
    gtk_widget_show (lab);
}

// ---------------------------	Adjustmenty based widgets ---------------------------

struct uiAdjustment : public uiItem
{
    GtkAdjustment* fAdj;
    uiAdjustment(UI* ui, float* zone, GtkAdjustment* adj) : uiItem(ui, zone), fAdj(adj) {}
    static void changed (GtkWidget *widget, gpointer data)
    {
        float	v = GTK_ADJUSTMENT (widget)->value;
        ((uiItem*)data)->modifyZone(v);
    }

    virtual void reflectZone()
    {
        float 	v = *fZone;
        fCache = v;
        gtk_adjustment_set_value(fAdj, v);
    }
};

static int precision(double n)
{
    if (n < 0.009999) return 3;
    else if (n < 0.099999) return 2;
    else if (n < 0.999999) return 1;
    else return 0;
}

// -------------------------- Vertical Slider -----------------------------------

void GTKUI::addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step)
{
    *zone = init;
    GtkObject* adj = gtk_adjustment_new(init, min, max, step, 10*step, 0);
    uiAdjustment* c = new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));
    g_signal_connect (GTK_OBJECT (adj), "value-changed", G_CALLBACK (uiAdjustment::changed), (gpointer) c);
    GdkColor colorRed;
    GdkColor colorGreen;
    GdkColor colorYellow;
    GtkWidget* slider = gtk_vscale_new (GTK_ADJUSTMENT(adj));
    gdk_color_parse("#c4c0c0", &colorGreen);
    gdk_color_parse("#96a2a7", &colorYellow);
    gdk_color_parse("#7b8a90", &colorRed);
    gtk_range_set_inverted (GTK_RANGE(slider), TRUE);
    gtk_scale_set_digits(GTK_SCALE(slider), precision(step));
    gtk_widget_set_usize(slider, -1, 120);
    gtk_widget_modify_bg (slider, GTK_STATE_NORMAL, &colorRed);
    gtk_widget_modify_bg (slider, GTK_STATE_PRELIGHT, &colorYellow);
    gtk_widget_modify_bg(slider, GTK_STATE_ACTIVE, &colorYellow);
    gtk_widget_modify_bg(slider, GTK_STATE_SELECTED, &colorGreen);
    openFrameBox(label);
    addWidget(label, slider);
    closeBox();
}

// -------------------------- Horizontal Slider -----------------------------------

void GTKUI::addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step)
{
    *zone = init;
    GtkObject* adj = gtk_adjustment_new(init, min, max, step, 10*step, 0);
    uiAdjustment* c = new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));
    g_signal_connect (GTK_OBJECT (adj), "value-changed", G_CALLBACK (uiAdjustment::changed), (gpointer) c);
    GtkRegler myGtkRegler;
    GtkWidget* slider = myGtkRegler.gtk_mini_slider_new_with_adjustment (GTK_ADJUSTMENT(adj));
    gtk_range_set_inverted (GTK_RANGE(slider), TRUE);
    addWidget(label, slider);
}

void GTKUI::addHorizontalWheel(const char* label, float* zone, float init, float min, float max, float step)
{
    *zone = init;
    GtkObject* adj = gtk_adjustment_new(init, min, max, step, 10*step, 0);
    uiAdjustment* c = new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));
    g_signal_connect (GTK_OBJECT (adj), "value-changed", G_CALLBACK (uiAdjustment::changed), (gpointer) c);
    GtkRegler myGtkRegler;
    GtkWidget* slider = myGtkRegler.gtk_wheel_new_with_adjustment (GTK_ADJUSTMENT(adj));
    gtk_range_set_inverted (GTK_RANGE(slider), TRUE);
    addWidget(label, slider);
}

struct uiValueDisplay : public uiItem
{
    GtkLabel* fLabel;
    int	fPrecision ;

    uiValueDisplay(UI* ui, float* zone, GtkLabel* label, int precision)
            : uiItem(ui, zone), fLabel(label), fPrecision(precision) {}

    virtual void reflectZone()
    {
        float 	v = *fZone;
        fCache = v;
        char s[64];
        if ( fPrecision <= 0)
        {
            snprintf(s, 63, "%d", int(v));
        }
        else if (fPrecision > 3)
        {
            snprintf(s, 63, "%f", v);
        }
        else if (fPrecision == 1)
        {
            const char* format[] = {"%.1f", "%.2f", "%.3f"};
            snprintf(s, 63, format[1-1], v);
        }
        else if (fPrecision == 2)
        {
            const char* format[] = {"%.1f", "%.2f", "%.3f"};
            snprintf(s, 63, format[2-1], v);
        }
        else
        {
            const char* format[] = {"%.1f", "%.2f", "%.3f"};
            snprintf(s, 63, format[3-1], v);
        }
        gtk_label_set_text(fLabel, s);
    }
};


void GTKUI::addregler(const char* label, float* zone, float init, float min, float max, float step)
{
    *zone = init;
    GtkObject* adj = gtk_adjustment_new(init, min, max, step, 10*step, 0);
    uiAdjustment* c = new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));
    g_signal_connect (GTK_OBJECT (adj), "value-changed", G_CALLBACK (uiAdjustment::changed), (gpointer) c);
    GtkWidget* lw = gtk_label_new("");
    GtkWidget* lwl = gtk_label_new(label);
    GdkColor colorGreen;
    gdk_color_parse("#a6a9aa", &colorGreen);
    gtk_widget_modify_fg (lw, GTK_STATE_NORMAL, &colorGreen);
    GtkStyle *style = gtk_widget_get_style(lw);
    pango_font_description_set_size(style->font_desc, 8*PANGO_SCALE);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_LIGHT);
    gtk_widget_modify_font(lw, style->font_desc);
    gtk_widget_modify_font(lwl, style->font_desc);
    new uiValueDisplay(this, zone, GTK_LABEL(lw),precision(step));
    GtkRegler myGtkRegler;
    GtkWidget* slider = myGtkRegler.gtk_regler_new_with_adjustment(GTK_ADJUSTMENT(adj));
    gtk_range_set_inverted (GTK_RANGE(slider), TRUE);
    openVerticalBox("");
    addWidget(label, lwl);
    addWidget(label, slider);
    addWidget(label, lw);
    closeBox();
}

void GTKUI::addbigregler(const char* label, float* zone, float init, float min, float max, float step)
{
    *zone = init;
    GtkObject* adj = gtk_adjustment_new(init, min, max, step, 10*step, 0);
    uiAdjustment* c = new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));
    g_signal_connect (GTK_OBJECT (adj), "value-changed", G_CALLBACK (uiAdjustment::changed), (gpointer) c);
    GtkWidget* lw = gtk_label_new("");
    GtkWidget* lwl = gtk_label_new(label);
    GdkColor colorGreen;
    gdk_color_parse("#a6a9aa", &colorGreen);
    gtk_widget_modify_fg (lw, GTK_STATE_NORMAL, &colorGreen);
    GtkStyle *style = gtk_widget_get_style(lw);
    pango_font_description_set_size(style->font_desc, 8*PANGO_SCALE);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_LIGHT);
    gtk_widget_modify_font(lw, style->font_desc);
    gtk_widget_modify_font(lwl, style->font_desc);
    new uiValueDisplay(this, zone, GTK_LABEL(lw),precision(step));
    GtkRegler myGtkRegler;
    GtkWidget* slider = myGtkRegler.gtk_big_regler_new_with_adjustment(GTK_ADJUSTMENT(adj));
    gtk_range_set_inverted (GTK_RANGE(slider), TRUE);
    openVerticalBox("");
    addWidget(label, lwl);
    addWidget(label, slider);
    addWidget(label, lw);
    closeBox();
}

void GTKUI::addslider(const char* label, float* zone, float init, float min, float max, float step)
{
    *zone = init;
    GtkObject* adj = gtk_adjustment_new(init, min, max, step, 10*step, 0);
    uiAdjustment* c = new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));
    g_signal_connect (GTK_OBJECT (adj), "value-changed", G_CALLBACK (uiAdjustment::changed), (gpointer) c);
    GtkWidget* lw = gtk_label_new("");
    GdkColor colorGreen;
    gdk_color_parse("#a6a9aa", &colorGreen);
    gtk_widget_modify_fg (lw, GTK_STATE_NORMAL, &colorGreen);
    GtkStyle *style = gtk_widget_get_style(lw);
    pango_font_description_set_size(style->font_desc, 8*PANGO_SCALE);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_LIGHT);
    gtk_widget_modify_font(lw, style->font_desc);
    new uiValueDisplay(this, zone, GTK_LABEL(lw),precision(step));
    GtkRegler myGtkRegler;
    GtkWidget* slider = myGtkRegler.gtk_hslider_new_with_adjustment(GTK_ADJUSTMENT(adj));
    gtk_range_set_inverted (GTK_RANGE(slider), TRUE);
    openVerticalBox(label);
    addWidget(label, lw);
    addWidget(label, slider);
    closeBox();
}

void GTKUI::addtoggle(const char* label, float* zone)
{
    GtkObject* adj = gtk_adjustment_new(0, 0, 1, 1, 10*1, 0);
    uiAdjustment* c = new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));
    g_signal_connect (GTK_OBJECT (adj), "value-changed", G_CALLBACK (uiAdjustment::changed), (gpointer) c);
    GtkRegler myGtkRegler;
    GtkWidget* slider = myGtkRegler.gtk_toggle_new_with_adjustment(GTK_ADJUSTMENT(adj));
    addWidget(label, slider);
}

void GTKUI::addswitch(const char* label, float* zone)
{
    GtkObject* adj = gtk_adjustment_new(0, 0, 1, 1, 10*1, 0);
    uiAdjustment* c = new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));
    g_signal_connect (GTK_OBJECT (adj), "value-changed", G_CALLBACK (uiAdjustment::changed), (gpointer) c);
    GtkRegler myGtkRegler;
    GtkWidget* slider = myGtkRegler.gtk_switch_new_with_adjustment(GTK_ADJUSTMENT(adj));
    GtkWidget* lw = gtk_label_new(label);
    GdkColor colorGreen;
    gdk_color_parse("#a6a9aa", &colorGreen);
    gtk_widget_modify_fg (lw, GTK_STATE_NORMAL, &colorGreen);
    GtkStyle *style = gtk_widget_get_style(lw);
    pango_font_description_set_size(style->font_desc, 8*PANGO_SCALE);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_LIGHT);
    gtk_widget_modify_font(lw, style->font_desc);
    openVerticalBox("");
    addWidget(label, lw);
    addWidget(label, slider);
    closeBox();
}

void GTKUI::addminiswitch(const char* label, float* zone)
{
    GtkObject* adj = gtk_adjustment_new(0, 0, 1, 1, 10*1, 0);
    uiAdjustment* c = new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));
    g_signal_connect (GTK_OBJECT (adj), "value-changed", G_CALLBACK (uiAdjustment::changed), (gpointer) c);
    GtkRegler myGtkRegler;
    GtkWidget* slider = myGtkRegler.gtk_mini_toggle_new_with_adjustment(GTK_ADJUSTMENT(adj));
    GtkWidget* lw = gtk_label_new(label);
    GdkColor colorGreen;
    gdk_color_parse("#a6a9aa", &colorGreen);
    gtk_widget_modify_fg (lw, GTK_STATE_NORMAL, &colorGreen);
    GtkStyle *style = gtk_widget_get_style(lw);
    pango_font_description_set_size(style->font_desc, 8*PANGO_SCALE);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_LIGHT);
    gtk_widget_modify_font(lw, style->font_desc);
    openHorizontalBox("");
    addWidget(label, slider);
    addWidget(label, lw);
    closeBox();
}

void GTKUI::addNumEntry(const char* label, float* zone, float init, float min, float max, float step)
{
    *zone = init;
    GtkObject* adj = gtk_adjustment_new(init, min, max, step, 10*step, 0);
    uiAdjustment* c = new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));
    g_signal_connect (GTK_OBJECT (adj), "value-changed", G_CALLBACK (uiAdjustment::changed), (gpointer) c);
    GtkWidget* spinner = gtk_spin_button_new (GTK_ADJUSTMENT(adj), step, precision(step));
    openFrameBox(label);
    addWidget(label, spinner);
    closeBox();
}

static gboolean deleteevent( GtkWidget *widget, gpointer   data )
{
    return TRUE;
}

void GTKUI::openWarningBox(const char* label, float* zone)
{
    GtkWidget* 	button = gtk_check_button_new ();
    uiCheckButton* c = new uiCheckButton(this, zone, GTK_TOGGLE_BUTTON(button));
    g_signal_connect (GTK_OBJECT (button), "toggled", G_CALLBACK(uiCheckButton::toggled), (gpointer) c);
}

void GTKUI::openDialogBox(const char* label, float* zone)
{
    GtkWidget * dialog = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_decorated(GTK_WINDOW(dialog), TRUE);
    gtk_window_set_deletable(GTK_WINDOW(dialog), FALSE);
    gtk_window_set_resizable(GTK_WINDOW(dialog), FALSE);
    gtk_window_set_gravity(GTK_WINDOW(dialog), GDK_GRAVITY_SOUTH);
    gtk_window_set_transient_for (GTK_WINDOW(dialog), GTK_WINDOW(fWindow));
    gtk_window_set_position (GTK_WINDOW(dialog), GTK_WIN_POS_MOUSE);
    gtk_window_set_keep_below (GTK_WINDOW(dialog), FALSE);
    gtk_window_set_title (GTK_WINDOW (dialog), label);
    g_signal_connect (G_OBJECT (dialog), "delete_event", G_CALLBACK (deleteevent), NULL);
    gtk_window_set_destroy_with_parent(GTK_WINDOW(dialog), TRUE);
    GtkWidget * box = gtk_hbox_new (homogene, 4);
    GtkWidget * box4 = gtk_vbox_new (homogene, 4);
    GtkWidget * box5 = gtk_hbox_new (homogene, 4);
    GtkWidget * box6 = gtk_hbox_new (homogene, 4);
    GtkWidget * box7 = gtk_vbox_new (homogene, 4);
    gtk_container_set_border_width (GTK_CONTAINER (box), 2);
    GdkColor colorRed;
    GdkColor colorOwn;
    gdk_color_parse ("#000094", &colorRed);
    gdk_color_parse ("#7f7f7f", &colorOwn);
    *zone = 0.0;
    GtkWidget* 	button = gtk_toggle_button_new ();
    gtk_widget_set_size_request (GTK_WIDGET(button), 20.0, 5.0);
    gtk_widget_set_size_request (GTK_WIDGET(box6), 20.0, 5.0);
    GtkWidget * box3 = gtk_hbox_new (homogene, 4);
    GtkWidget * box1 = gtk_vbox_new (homogene, 4);
    gtk_container_set_border_width (GTK_CONTAINER (box3), 0);
    gtk_container_set_border_width (GTK_CONTAINER (box1), 0);
    gtk_container_add (GTK_CONTAINER(box3), box1);
    GtkWidget * box2 = gtk_vbox_new (homogene, 4);
    gtk_container_set_border_width (GTK_CONTAINER (box2), 0);
    gtk_widget_set_size_request (GTK_WIDGET(box2), 5.0, 5.0);
    gtk_container_add (GTK_CONTAINER(box3), box7);
    gtk_container_add (GTK_CONTAINER(box7), box6);
    gtk_container_add (GTK_CONTAINER(box7), button);
    gtk_container_add (GTK_CONTAINER(box3), box2);
    gtk_widget_set_size_request (GTK_WIDGET(box1), 5.0, 5.0);
    gtk_widget_show (button);
    gtk_widget_show (box1);
    gtk_widget_show (box2);
    gtk_widget_show (box3);
    gtk_widget_show (box6);
    gtk_widget_show (box7);
    gtk_container_add (GTK_CONTAINER(fBox[fTop]), box3);
    uiToggleButton* c = new uiToggleButton(this, zone, GTK_TOGGLE_BUTTON(button));
    gtk_widget_modify_bg (button, GTK_STATE_NORMAL, &colorOwn);
    gtk_widget_modify_bg (button, GTK_STATE_ACTIVE, &colorRed);
    g_signal_connect (GTK_OBJECT (button), "toggled", G_CALLBACK (uiToggleButton::toggled), (gpointer) c);
    g_signal_connect (GTK_OBJECT (button), "toggled", G_CALLBACK (gx_show_extendet_settings), (gpointer) dialog);

    GtkWidget * frame =  gtk_frame_new (label);
    GtkWidget* 	button1 = gtk_button_new_with_label ("reset");
    gtk_widget_set_size_request (GTK_WIDGET(button1), 60.0, 20.0);
    gtk_widget_set_size_request (GTK_WIDGET(frame), 100.0, 20.0);
    gtk_container_add (GTK_CONTAINER(box5), frame);
    gtk_container_add (GTK_CONTAINER(box5), button1);
    g_signal_connect (GTK_OBJECT (button1), "pressed", G_CALLBACK (gx_reset_units), (gpointer) dialog);
    gtk_container_add (GTK_CONTAINER(box4), box5);
    gtk_container_add (GTK_CONTAINER(box4), box);
    gtk_container_add (GTK_CONTAINER(dialog), box4);
    // gtk_widget_show(dialog);
    gtk_widget_show(frame);
    gtk_widget_show(button1);
    gtk_widget_show(box);
    gtk_widget_show(box4);
    gtk_widget_show(box5);
    pushBox(kBoxMode, box);
}

// ------------------------------ Num Display -----------------------------------

struct uiNumDisplay : public uiItem
{
    GtkWidget* fLabel;

    uiNumDisplay(UI* ui, float* zone, GtkWidget* label)
            : uiItem(ui, zone), fLabel(label) {}

    virtual void reflectZone()
    {
        float 	v = *fZone;
        fCache = v;
        char s[64];
        int vis = round(v);
        float scale = ((v-vis)-(-1.0))/(1.0-(-1.0));
        if ((scale <= 0.0) || (scale > 1.0)) scale = 0.0;
        vis += 9;
        const char* note[] = {"C ","C#","D ","D#","E ","F ","F#","G ","G#","A ","A#","B "};
        if (shownote == 1)
        {
            if ((vis>=0)&&(vis<=11)) snprintf(s, 63, "%s",  note[vis]);
            else if ((vis>=-24)&&(vis<=-13)) snprintf(s, 63, "%s", note[vis+24]);
            else if ((vis>=-12)&&(vis<=-1)) snprintf(s, 63, "%s", note[vis+12]);
            else if ((vis>=12)&&(vis<=23)) snprintf(s, 63, "%s", note[vis-12]);
            else if ((vis>=24)&&(vis<=35)) snprintf(s, 63,"%s", note[vis-24]);
            else if ((vis>=36)&&(vis<=47)) snprintf(s, 63,"%s", note[vis-36]);
            else
            {
                snprintf(s, 63, "%s", "");
                scale = 0.0;
            }
            if ((scale >= 0.0) && (scale < 1.0)) gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(pb), scale);
            gtk_progress_bar_set_text(GTK_PROGRESS_BAR(pb), s);
        }
        else if (shownote == 0)
        {
            gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(pb), scale);
            snprintf(s, 63, "%s", "");
            gtk_progress_bar_set_text(GTK_PROGRESS_BAR(pb), s);
            shownote = 2;
        }
    }
};


void GTKUI::addNumDisplay(const char* label, float* zone )
{
    openVerticalBox(label);
    pb = gtk_progress_bar_new();
    gtk_progress_bar_set_orientation(GTK_PROGRESS_BAR(pb), GTK_PROGRESS_LEFT_TO_RIGHT);
    new uiNumDisplay(this, zone, GTK_WIDGET(pb));
    gtk_progress_bar_set_text(GTK_PROGRESS_BAR(pb), label);
    gtk_widget_set_size_request(pb, 40.0, 20.0);
    GtkStyle *style = gtk_widget_get_style(pb);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
    gtk_widget_modify_font(pb, style->font_desc);
    addWidget(label, pb);
    gtk_widget_hide(pb);
    closeBox();
}

struct uiStatusDisplay : public uiItem
{
    GtkLabel* fLabel;
    int	fPrecision;

    uiStatusDisplay(UI* ui, float* zone, GtkLabel* label)
            : uiItem(ui, zone), fLabel(label) {}

    virtual void reflectZone()
    {
        float 	v = *fZone;
        fCache = v;
        if ((playmidi == 1) && (cpu_load < 65.0))
        {
            if (v > 0.0f) gtk_status_icon_set_from_pixbuf ( GTK_STATUS_ICON(status_icon), GDK_PIXBUF(ibm));
            else  gtk_status_icon_set_from_pixbuf ( GTK_STATUS_ICON(status_icon), GDK_PIXBUF(ib));
        }
        else if (playmidi == 0)
        {
            gtk_status_icon_set_from_pixbuf ( GTK_STATUS_ICON(status_icon), GDK_PIXBUF(ib));
        }
        else gtk_status_icon_set_from_pixbuf ( GTK_STATUS_ICON(status_icon), GDK_PIXBUF(ibr));
    }
};

void GTKUI::addStatusDisplay(const char* label, float* zone )
{
    GtkWidget* lw = gtk_label_new("");
    new uiStatusDisplay(this, zone, GTK_LABEL(lw));
    openFrameBox(label);
    addWidget(label, lw);
    closeBox();
    gtk_widget_hide(lw);
};

void GTKUI::addLiveWaveDisplay(const char* label, float* zone , float* zone1)
{
    GtkObject* adj = gtk_adjustment_new(0.0, -1.0, 1.0, 0.0009, 10*0.0009, 0);
    new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));
    GtkWaveView myGtkWaveView;
    livewa = myGtkWaveView.gtk_wave_live_view(zone,zone1,GTK_ADJUSTMENT(adj));
    GtkWidget * nolivewa =  gtk_event_box_new ();
    GtkWidget * box = gtk_vbox_new (homogene, 4);
    gtk_widget_set_size_request (nolivewa, 550, 80);
    gtk_container_add (GTK_CONTAINER(nolivewa),box );
    gtk_container_add (GTK_CONTAINER(box),livewa );
    addWidget(label, nolivewa);
    gtk_widget_show(box);
    gtk_widget_hide(livewa);
};


// ------------------------------ Progress Bar -----------------------------------

struct uiBargraph : public uiItem
{
    GtkProgressBar*		fProgressBar;
    float				fMin;
    float				fMax;

    uiBargraph(UI* ui, float* zone, GtkProgressBar* pbar, float lo, float hi)
            : uiItem(ui, zone), fProgressBar(pbar), fMin(lo), fMax(hi) {}

    float scale(float v)
    {
        return (v-fMin)/(fMax-fMin);
    }

    virtual void reflectZone()
    {
        float 	v = *fZone;
        fCache = v;
        if (v >= 1.0) v = 1.0f;
        gtk_progress_bar_set_fraction(fProgressBar, scale(v));
    }
};

void GTKUI::addVerticalBargraph(const char* label, float* zone, float lo, float hi)
{
    GtkWidget* pb = gtk_progress_bar_new();
    gtk_progress_bar_set_orientation(GTK_PROGRESS_BAR(pb), GTK_PROGRESS_RIGHT_TO_LEFT);
    gtk_widget_set_size_request(pb,  -1,8);
    new uiBargraph(this, zone, GTK_PROGRESS_BAR(pb), lo, hi);
    openFrameBox(label);
    addWidget(label, pb);
    closeBox();
}

void GTKUI::addHorizontalBargraph(const char* label, float* zone, float lo, float hi)
{
    GtkWidget* pb = gtk_progress_bar_new();
    gtk_progress_bar_set_orientation(GTK_PROGRESS_BAR(pb), GTK_PROGRESS_LEFT_TO_RIGHT);
    gtk_widget_set_size_request(pb, -1, 8);
    new uiBargraph(this, zone, GTK_PROGRESS_BAR(pb), lo, hi);
    openFrameBox(label);
    addWidget(label, pb);
    closeBox();
}

//----------------------------- menu ----------------------------
void GTKUI::addMenu()
{
    /*-- Declare the GTK Widgets used in the menu --*/
    GtkWidget *menucap;
    GtkWidget *menuFile;
    GtkWidget *menuEdit;
    GtkWidget *menuHelp;
    GtkWidget *menuLoad;
    GtkWidget *menuSave;
    GtkWidget *menubar;
    GtkWidget *menuLatency;
    GtkWidget *menulat;
    GtkWidget *menuSkinChooser;
    GtkWidget *menuskin;
    GtkWidget *menu;
    GtkWidget *menu1;
    GtkWidget *menuitem;
// GtkWidget *vbox;
    GSList *group = NULL;
    GtkWidget *handlebox;  // remove handlebox here
    /*-- Create the vbox --*/
// vbox = gtk_vbox_new(FALSE, 0);
    /*-- Create the menu bar --*/
    menubar = gtk_menu_bar_new();
    handlebox = gtk_handle_box_new();   // remove handlebox here
    /*-- Add the menubar to the vbox  enable to remove the handlebox--*/
// gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, TRUE, 0);
    gtk_widget_show(menubar);
    /*---------------- Create Engine menu items ------------------*/
    menuFile = gtk_menu_item_new_with_label ("Engine");
    gtk_menu_bar_append (GTK_MENU_BAR(menubar), menuFile);
    gtk_widget_show(menuFile);
    /*-- Create Engine submenu  --*/
    menuh = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuFile), menuh);
    /* Some thing went wrong when compile without __SSE__ with that funktion. So I disable it in this case.*/

    /*-- Create New radio check menu item and set active under Engine submenu --*/
    menuitem = gtk_radio_menu_item_new_with_label (group, "  Play");
    group = gtk_radio_menu_item_get_group (GTK_RADIO_MENU_ITEM (menuitem));
    gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM (menuitem), TRUE);
    g_signal_connect (GTK_OBJECT (menuitem), "activate", G_CALLBACK (gx_play_function), NULL);
    gtk_menu_append(GTK_MENU(menuh), menuitem);
    gtk_widget_show (menuitem);
    /*-- Create Open radio check menu item under Engine submenu --*/
    menuitem = gtk_radio_menu_item_new_with_label (group,  "  Stopp");
    g_signal_connect (GTK_OBJECT (menuitem), "activate", G_CALLBACK (gx_stop_function), NULL);
    gtk_menu_append(GTK_MENU(menuh), menuitem);
    gtk_widget_show (menuitem);

    /*-- Create Open check menu item under Engine submenu --*/
    menuitem = gtk_check_menu_item_new_with_label ("  midi_out ");
    g_signal_connect (GTK_OBJECT (menuitem), "activate", G_CALLBACK (gx_midi_out), NULL);
    gtk_menu_append(GTK_MENU(menuh), menuitem);
    gtk_widget_show (menuitem);

    /*---------------- Create Latency menu items --------------------*/
    /*-- Create  Latency submenu under Engine submenu --*/
    menuLatency = gtk_menu_item_new_with_label ("Latency");
    gtk_menu_append (GTK_MENU(menuh), menuLatency);
    menulat = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuLatency), menulat);

    /*-- Create  menu item under Latency submenu --*/
    gchar buf_size[8];
    const int min_pow = 5;  // 2**5  = 32
    const int max_pow = 13; // 2**13 = 8192
    group = NULL;

    for (int i = min_pow; i <= max_pow; i++)
    {
        int jack_buffer_size = (int)pow(2.,i);
        (void)snprintf(buf_size, 5, "%d", jack_buffer_size);
        menuitem = gtk_radio_menu_item_new_with_label (group, buf_size);
        group = gtk_radio_menu_item_get_group (GTK_RADIO_MENU_ITEM (menuitem));
        gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM (menuitem), FALSE);

        g_signal_connect (GTK_OBJECT (menuitem), "activate",
                          G_CALLBACK (gx_set_jack_buffer_size),
                          GINT_TO_POINTER(jack_buffer_size));

        // display actual buffer size as default
        if (client)
            if (jack_buffer_size == (int)jack_get_buffer_size(client))
                gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM (menuitem), TRUE);

        gtk_menu_append(GTK_MENU(menulat), menuitem);
        gtk_widget_show (menuitem);
    }
    /*---------------- End Latency menu declarations ----------------*/

    /*-- Create Exit menu item under Engine submenu --*/
    menuitem = gtk_menu_item_new_with_label ("  Exit  ");
    g_signal_connect (GTK_OBJECT (menuitem), "activate", G_CALLBACK (gx_delete_event), NULL);
    g_signal_connect(GTK_OBJECT (menuitem), "activate", G_CALLBACK (gx_destroy_event), NULL);
    gtk_menu_append(GTK_MENU(menuh), menuitem);
    gtk_widget_show (menuitem);
    /*---------------- End Engine menu declarations ----------------*/



    /*---------------- Create Settings menu items --------------------*/
    menuEdit = gtk_menu_item_new_with_label ("Presets");
    gtk_menu_bar_append (GTK_MENU_BAR(menubar), menuEdit);
    gtk_widget_show(menuEdit);
    /*-- Create Settings submenu --*/
    menu1 = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuEdit), menu1);
    /*-- Create  menu item under Settings submenu --*/
    menuSave = gtk_menu_item_new_with_label ("save as");
    gtk_menu_append(GTK_MENU(menu1), menuSave);
    menus = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuSave), menus);

    /*-- Create  menu item under Save submenu --*/
    menuitem = gtk_menu_item_new_with_label ("new");
    g_signal_connect (GTK_OBJECT (menuitem), "activate", G_CALLBACK (gx_save_presetn1), NULL);
    gtk_menu_append(GTK_MENU(menus), menuitem);
    gtk_widget_show (menuitem);
    const char*	  home;
    char                rcfilenamere[256];
    const char*      prename = "guitarixpre";
    home = getenv ("HOME");
    if (home == 0) home = ".";
    snprintf(rcfilenamere, 256, "%s/.guitarix/%src", home, prename);

    ifstream f(rcfilenamere);
    if (f.good())
    {
        string buffer;
        while (!f.eof())
        {
            getline(f, buffer);
            std::string b(" ");
            std::string::size_type in = buffer.find(b);
            if (int(in) != -1)
            {
                buffer.erase(in);
                menuitem = gtk_menu_item_new_with_label (buffer.c_str());
                g_signal_connect (GTK_OBJECT (menuitem), "activate", G_CALLBACK (gx_save_presetn2), NULL);
                gtk_menu_append(GTK_MENU(menus), menuitem);
                gtk_widget_show (menuitem);
            }
        }
    }
    f.close();
    free(f);

    /*-- Create  menu load under Settings submenu --*/
    menuLoad = gtk_menu_item_new_with_label ("load");
    gtk_menu_append (GTK_MENU(menu1), menuLoad);
    menul = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuLoad), menul);
    ifstream fa(rcfilenamere);
    if (fa.good())
    {
        string buffer;
        while (!fa.eof())
        {
            getline(fa, buffer);
            std::string b(" ");
            std::string::size_type in = buffer.find(b);
            if (int(in) != -1)
            {
                buffer.erase(in);
                menuitem = gtk_menu_item_new_with_label (buffer.c_str());
                g_signal_connect (GTK_OBJECT (menuitem), "activate", G_CALLBACK (gx_load_preset), NULL);
                gtk_menu_append(GTK_MENU(menul), menuitem);
                gtk_widget_show (menuitem);
            }
        }
    }
    fa.close();
    free(fa);
    /*---------------- End Settingsmenu declarations ----------------*/
    /*---------------- Create Options menu items ------------------*/
    menucap = gtk_menu_item_new_with_label ("Options");
    gtk_menu_bar_append (GTK_MENU_BAR(menubar), menucap);
    gtk_widget_show(menucap);
    /*-- Create Options submenu  --*/
    menu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menucap), menu);

    /*-- Create Open check menu item under Options submenu --*/
    menuitem = gtk_check_menu_item_new_with_label ("  Oscilloscope");
    //  gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM (menuitem), TRUE);
    g_signal_connect (GTK_OBJECT (menuitem), "activate", G_CALLBACK (gx_show_oscilloscope), NULL);
    gtk_menu_append(GTK_MENU(menu), menuitem);
    gtk_widget_show (menuitem);
    /*-- Create Open check menu item under Options submenu --*/
    menuitem = gtk_check_menu_item_new_with_label ("  tuner ");
    g_signal_connect (GTK_OBJECT (menuitem), "activate", G_CALLBACK (gx_tuner), NULL);
    gtk_menu_append(GTK_MENU(menu), menuitem);
    gtk_widget_show (menuitem);
    /*-- Create Open check menu item under Options submenu --*/
    menuitem = gtk_check_menu_item_new_with_label ("  meterbridge");
    g_signal_connect (GTK_OBJECT (menuitem), "activate", G_CALLBACK (gx_meterbridge), NULL);
    gtk_menu_append(GTK_MENU(menu), menuitem);
    gtk_widget_show (menuitem);
    /*-- Create Open check menu item under Options submenu --*/
    menuitem = gtk_menu_item_new_with_label ("jack_capture settings");
    gtk_menu_append(GTK_MENU(menu), menuitem);
    g_signal_connect(GTK_OBJECT (menuitem), "activate", G_CALLBACK (gx_show_j_c_gui), NULL);
    gtk_widget_show (menuitem);

    /*-- Create skin menu under Options submenu--*/
    menuSkinChooser = gtk_menu_item_new_with_label ("Skin");
    gtk_menu_append (GTK_MENU(menu), menuSkinChooser);
    menuskin = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuSkinChooser), menuskin);
 
    /* Create black skin item under skin submenu --*/
    int idx = GX_BLACK_SKIN;
    while (idx < GX_NUM_OF_SKINS) {
      menuitem = gtk_radio_menu_item_new_with_label (group, skins[idx]);
      group = gtk_radio_menu_item_get_group (GTK_RADIO_MENU_ITEM (menuitem));
      gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM (menuitem), FALSE);
      g_signal_connect (GTK_OBJECT (menuitem), "activate", G_CALLBACK (gx_change_skin), GINT_TO_POINTER(idx));
      gtk_menu_append(GTK_MENU(menuskin), menuitem);
      gtk_widget_show (menuitem);
      idx++;
    }

    /*-- End skin menu declarations --*/

    /*---------------- Start About menu declarations ----------------*/
    menuHelp = gtk_menu_item_new_with_label ("About");
    gtk_menu_bar_append (GTK_MENU_BAR(menubar), menuHelp);
    gtk_widget_show(menuHelp);
    /*-- Create About submenu --*/
    menu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuHelp), menu);
    /*-- Create About menu item under About submenu --*/
    menuitem = gtk_menu_item_new_with_label ("About");
    gtk_menu_append(GTK_MENU(menu), menuitem);
    g_signal_connect(GTK_OBJECT (menuitem), "activate", G_CALLBACK (gx_show_about), NULL);
    gtk_widget_show (menuitem);
    /*---------------- End About menu declarations ----------------*/

    /*-- Add the menubar to the handlebox  remove hamdlebox here--*/
    gtk_container_add(GTK_CONTAINER(handlebox), menubar);
//gtk_box_pack_start(GTK_BOX(vbox), handlebox, FALSE, TRUE, 0);
    /*---------------- add menu to main window box----------------*/
    gtk_box_pack_start (GTK_BOX (fBox[fTop]), handlebox , FALSE, FALSE, 0);
    /*---------------- show menu ----------------*/
    gtk_widget_show(handlebox);   // remove handelbox here
    gtk_widget_show(menuitem);
    gtk_widget_show(menuFile);
    gtk_widget_show(menuLatency);
    gtk_widget_show(menuEdit);
    gtk_widget_show(menuLoad);
    gtk_widget_show(menuSave);
    gtk_widget_show(menuSkinChooser);
    gtk_widget_show(menuHelp);
//  gtk_widget_show(vbox);
    /*---------------- end show menu ----------------*/
}

void GTKUI::show()
{
    assert(fTop == 0);
    gtk_widget_show  (fBox[0]);
    gtk_widget_show  (fWindow);
}

/**
 * Update all user items reflecting zone z
 */

static gboolean callUpdateAllGuis(gpointer)
{
    UI::updateAllGuis();
    return TRUE;
}

void GTKUI::run()
{
    assert(fTop == 0);
    gtk_widget_show  (fBox[0]);
    gtk_widget_show  (fWindow);
    gtk_timeout_add(40, callUpdateAllGuis, 0);
    gtk_main ();
    stop();
}



