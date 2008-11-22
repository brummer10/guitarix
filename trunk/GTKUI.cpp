#include "GTKUI.h"


// create main window
GTKUI::GTKUI(char * name, int* pargc, char*** pargv)
{
    if (!fInitialized)
    {
        gtk_init(pargc, pargv);
        fInitialized = true;
    }
    /*-- set rc file overwrite it with export--*/

    //setenv("GUITARIX_RC_PATH", "/usr/share/guitarix/guitarix.rc", 0);
    gtk_rc_parse(rcpath);
    /*-- Check for working directory to save and load presets --*/
    const char*	  home;
    const char*      pathname = ".guitarix";
    char                dirname[256];
    home = getenv ("HOME");
    if (home == 0) home = ".";
    snprintf(dirname, 256, "%s/%s", home, pathname);
    Exists( dirname);
    /*-- Declare the GTK Widgets --*/
    fWindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    /*---------------- set window defaults ----------------*/
    gtk_window_set_resizable(GTK_WINDOW (fWindow) , FALSE);
    gtk_window_set_title (GTK_WINDOW (fWindow), name);
    gtk_window_set_icon_from_file(GTK_WINDOW (fWindow),  "/usr/share/pixmaps/guitarix.png", NULL);
    /*---------------- singnals ----------------*/
    gtk_signal_connect (GTK_OBJECT (fWindow), "delete_event", GTK_SIGNAL_FUNC (delete_event), NULL);
    gtk_signal_connect (GTK_OBJECT (fWindow), "destroy", GTK_SIGNAL_FUNC (destroy_event), NULL);

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
    GdkColor   colorRed;
    gdk_color_parse ("red", &colorRed);
    GtkWidget * box = gtk_frame_new (label);
    //gtk_frame_set_label_align(GTK_FRAME(box),0.0,0.0);
    gtk_widget_modify_fg (box, GTK_STATE_NORMAL, &colorRed);
    pushBox(kSingleMode, addWidget(label, box));
}

void GTKUI::openHorizontalBox(const char* label)
{
    GtkWidget * box = gtk_hbox_new (homogene, 4);
    gtk_container_set_border_width (GTK_CONTAINER (box), 2);
    if (fMode[fTop] != kTabMode && label[0] != 0)
    {
        GtkWidget * frame = addWidget(label, gtk_frame_new (label));
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
    GtkWidget * box = gtk_hbox_new (homogene, 4);
    gtk_container_set_border_width (GTK_CONTAINER (box), 2);
    if (fMode[fTop] != kTabMode && label[0] != 0)
    {
        GtkWidget * frame = addWidget(label, gtk_expander_new (label));
        gtk_container_add (GTK_CONTAINER(frame), box);
        uiExpanderBox* c = new uiExpanderBox(this, zone, GTK_EXPANDER(frame));
        gtk_signal_connect (GTK_OBJECT (frame), "activate", GTK_SIGNAL_FUNC (uiExpanderBox::expanded), (gpointer)c);
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
    GtkWidget * box = gtk_vbox_new (homogene, 4);
    gtk_container_set_border_width (GTK_CONTAINER (box), 2);
    if (fMode[fTop] != kTabMode && label[0] != 0)
    {
        GtkWidget * frame = addWidget(label, gtk_frame_new (label));
        gtk_container_add (GTK_CONTAINER(frame), box);
        gtk_widget_show(box);
        pushBox(kBoxMode, box);
    }
    else
    {
        pushBox(kBoxMode, addWidget(label, box));
    }
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
    gtk_signal_connect (GTK_OBJECT (button), "pressed", GTK_SIGNAL_FUNC (uiButton::pressed), (gpointer) c);
    gtk_signal_connect (GTK_OBJECT (button), "released", GTK_SIGNAL_FUNC (uiButton::released), (gpointer) c);
    gtk_signal_connect (GTK_OBJECT (button), "clicked", GTK_SIGNAL_FUNC (fileselected), button);
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
    *zone = 0.0;
    GtkWidget* 	button = gtk_toggle_button_new_with_label (label);
    addWidget(label, button);
    uiToggleButton* c = new uiToggleButton(this, zone, GTK_TOGGLE_BUTTON(button));
    gtk_widget_modify_bg (button, GTK_STATE_NORMAL, &colorOwn);
    gtk_widget_modify_bg (button, GTK_STATE_ACTIVE, &colorRed);
    gtk_signal_connect (GTK_OBJECT (button), "toggled", GTK_SIGNAL_FUNC (uiToggleButton::toggled), (gpointer) c);
    gtk_signal_connect (GTK_OBJECT (button), "toggled", GTK_SIGNAL_FUNC (recordit), (gpointer) c);
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
    gtk_signal_connect (GTK_OBJECT (button), "toggled", GTK_SIGNAL_FUNC (uiToggleButton::toggled), (gpointer) c);
}

void GTKUI::addJToggleButton(const char* label, float* zone)
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
    addWidget(label, button);
    gtk_widget_show (lab);
    uiToggleButton* c = new uiToggleButton(this, zone, GTK_TOGGLE_BUTTON(button));
    gtk_widget_modify_bg (button, GTK_STATE_NORMAL, &colorOwn);
    gtk_widget_modify_bg (button, GTK_STATE_ACTIVE, &colorRed);
    gtk_widget_modify_fg (lab, GTK_STATE_ACTIVE, &colorwn);
    gtk_signal_connect (GTK_OBJECT (button), "toggled", GTK_SIGNAL_FUNC (uiToggleButton::toggled), (gpointer) c);
    gtk_signal_connect (GTK_OBJECT (button), "toggled", GTK_SIGNAL_FUNC (runjconv), (gpointer) c);
    get_jconfset ();
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
    // *zone = 0.0;
    GdkColor   colorRed;
    GdkColor   colorOwn;
    GdkColor   colorba;
    gdk_color_parse ("#000000", &colorRed);
    gdk_color_parse ("#4c5159", &colorOwn);
    gdk_color_parse ("#c4c0c0", &colorba);
    GtkWidget* 	button = gtk_check_button_new_with_label (label);
    addWidget(label, button);
    gtk_widget_modify_bg (button, GTK_STATE_PRELIGHT, &colorOwn);
    gtk_widget_modify_fg (button, GTK_STATE_PRELIGHT, &colorRed);
    gtk_widget_modify_text (button, GTK_STATE_NORMAL, &colorRed);
    gtk_widget_modify_base (button, GTK_STATE_NORMAL, &colorba);
    uiCheckButton* c = new uiCheckButton(this, zone, GTK_TOGGLE_BUTTON(button));
    gtk_signal_connect (GTK_OBJECT (button), "toggled", GTK_SIGNAL_FUNC(uiCheckButton::toggled), (gpointer) c);
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
    gtk_signal_connect (GTK_OBJECT (adj), "value-changed", GTK_SIGNAL_FUNC (uiAdjustment::changed), (gpointer) c);
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
    gtk_signal_connect (GTK_OBJECT (adj), "value-changed", GTK_SIGNAL_FUNC (uiAdjustment::changed), (gpointer) c);
    GdkColor colorGreen;
    GdkColor colorYellow;
    GdkColor colorRed;
    GtkWidget* slider = gtk_hscale_new (GTK_ADJUSTMENT(adj));
    gdk_color_parse("#52525c", &colorGreen);
    gdk_color_parse("#96a2a7", &colorYellow);
    gdk_color_parse("#7b8a90", &colorRed);
    gtk_scale_set_digits(GTK_SCALE(slider), precision(step));
    gtk_widget_set_usize(slider, 160, -1);
    gtk_widget_modify_bg (slider, GTK_STATE_NORMAL, &colorRed);
    gtk_widget_modify_bg (slider, GTK_STATE_PRELIGHT, &colorYellow);
    gtk_widget_modify_bg(slider, GTK_STATE_ACTIVE, &colorYellow);
    gtk_widget_modify_bg(slider, GTK_STATE_SELECTED, &colorGreen);
    openFrameBox(label);
    addWidget(label, slider);
    closeBox();
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

    GtkWidget * box = gtk_hbox_new (homogene, 4);
    GtkWidget * box4 = gtk_vbox_new (homogene, 4);
    GtkWidget * box5 = gtk_hbox_new (homogene, 4);
    gtk_container_set_border_width (GTK_CONTAINER (box), 2);
    GdkColor colorRed;
    GdkColor colorOwn;
    gdk_color_parse ("#000094", &colorRed);
    gdk_color_parse ("#7f7f7f", &colorOwn);
    *zone = 0.0;
    GtkWidget* 	button = gtk_toggle_button_new ();
    gtk_widget_set_size_request (GTK_WIDGET(button), 40.0, 10.0);
    GtkWidget * box3 = gtk_hbox_new (homogene, 4);
    GtkWidget * box1 = gtk_vbox_new (homogene, 4);
    gtk_container_set_border_width (GTK_CONTAINER (box3), 0);
    gtk_container_set_border_width (GTK_CONTAINER (box1), 0);
    gtk_container_add (GTK_CONTAINER(box3), box1);
    GtkWidget * box2 = gtk_vbox_new (homogene, 4);
    gtk_container_set_border_width (GTK_CONTAINER (box2), 0);
    gtk_widget_set_size_request (GTK_WIDGET(box2), 10.0, 10.0);
    gtk_container_add (GTK_CONTAINER(box3), button);
    gtk_container_add (GTK_CONTAINER(box3), box2);
    gtk_widget_set_size_request (GTK_WIDGET(box1), 10.0, 10.0);
    gtk_widget_show (button);
    gtk_widget_show (box1);
    gtk_widget_show (box2);
    gtk_widget_show (box3);
    gtk_container_add (GTK_CONTAINER(fBox[fTop]), box3);
    uiToggleButton* c = new uiToggleButton(this, zone, GTK_TOGGLE_BUTTON(button));
    gtk_widget_modify_bg (button, GTK_STATE_NORMAL, &colorOwn);
    gtk_widget_modify_bg (button, GTK_STATE_ACTIVE, &colorRed);
    gtk_signal_connect (GTK_OBJECT (button), "toggled", GTK_SIGNAL_FUNC (uiToggleButton::toggled), (gpointer) c);
    gtk_signal_connect (GTK_OBJECT (button), "toggled", GTK_SIGNAL_FUNC (show_dialog), (gpointer) dialog);

    GtkWidget * frame =  gtk_frame_new (label);
    GtkWidget* 	button1 = gtk_button_new_with_label ("reset");
    gtk_widget_set_size_request (GTK_WIDGET(button1), 60.0, 20.0);
    gtk_widget_set_size_request (GTK_WIDGET(frame), 260.0, 20.0);
    gtk_container_add (GTK_CONTAINER(box5), frame);
    gtk_container_add (GTK_CONTAINER(box5), button1);
    gtk_signal_connect (GTK_OBJECT (button1), "pressed", GTK_SIGNAL_FUNC (reset_dialog), (gpointer) dialog);
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


//----------------------------- menu ----------------------------
void GTKUI::addMenu()
{
    /*-- Declare the GTK Widgets used in the menu --*/
    GtkWidget *menucap;
    GSList *groupc = NULL;
    GtkWidget *menuFile;
    GtkWidget *menuEdit;
    GtkWidget *menuHelp;
    GtkWidget *menuLoad;
    GtkWidget *menuSave;
    GtkWidget *menubar;
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
    menu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuFile), menu);
    /* Some thing went wrong when compile without __SSE__ with that funktion. So I disable it in this case.*/
#if defined (__SSE__)
    /*-- Create New radio check menu item and set active under Engine submenu --*/
    menuitem = gtk_radio_menu_item_new_with_label (group, "  Play");
    group = gtk_radio_menu_item_get_group (GTK_RADIO_MENU_ITEM (menuitem));
    gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM (menuitem), TRUE);
    gtk_signal_connect (GTK_OBJECT (menuitem), "activate", GTK_SIGNAL_FUNC (play_function), NULL);
//checky = 1.0;
    gtk_menu_append(GTK_MENU(menu), menuitem);
    gtk_widget_show (menuitem);
    /*-- Create Open radio check menu item under Engine submenu --*/
    menuitem = gtk_radio_menu_item_new_with_label (group,  "  Stopp");
    gtk_signal_connect (GTK_OBJECT (menuitem), "activate", GTK_SIGNAL_FUNC (stop_function), NULL);
    gtk_menu_append(GTK_MENU(menu), menuitem);
    gtk_widget_show (menuitem);
#endif
//------------ create the Gui hide menuitem when start parameter nogui ------------------
    if (strcmp(param, "nogui") == 0)
    {
        /*-- Create Exit menu item under Engine submenu --*/
        menuitem = gtk_menu_item_new_with_label ("  Quit GUI  ");
        gtk_signal_connect(GTK_OBJECT (menuitem), "activate", GTK_SIGNAL_FUNC (hide_widget), fWindow);
        gtk_menu_append(GTK_MENU(menu), menuitem);
        gtk_widget_show (menuitem);
    }
    /*-- Create Exit menu item under Engine submenu --*/
    menuitem = gtk_menu_item_new_with_label ("  Exit  ");
    gtk_signal_connect (GTK_OBJECT (menuitem), "activate", GTK_SIGNAL_FUNC (delete_event), NULL);
    gtk_signal_connect(GTK_OBJECT (menuitem), "activate", GTK_SIGNAL_FUNC (destroy_event), NULL);
    gtk_menu_append(GTK_MENU(menu), menuitem);
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
    gtk_signal_connect (GTK_OBJECT (menuitem), "activate", GTK_SIGNAL_FUNC (save_function1), NULL);
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
            if (in != -1)
            {
                buffer.erase(in);
                menuitem = gtk_menu_item_new_with_label (buffer.c_str());
                gtk_signal_connect (GTK_OBJECT (menuitem), "activate", GTK_SIGNAL_FUNC (save_function2), NULL);
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
            if (in != -1)
            {
                buffer.erase(in);
                menuitem = gtk_menu_item_new_with_label (buffer.c_str());
                gtk_signal_connect (GTK_OBJECT (menuitem), "activate", GTK_SIGNAL_FUNC (load_function1), NULL);
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
    menuitem = gtk_check_menu_item_new_with_label ("  meterbridge");
    gtk_signal_connect (GTK_OBJECT (menuitem), "activate", GTK_SIGNAL_FUNC (meterbridge), NULL);
    gtk_menu_append(GTK_MENU(menu), menuitem);
    gtk_widget_show (menuitem);
    /*-- Create Open check menu item under Options submenu --*/
    menuitem = gtk_menu_item_new_with_label ("jack_capture settings");
    gtk_menu_append(GTK_MENU(menu), menuitem);
    gtk_signal_connect(GTK_OBJECT (menuitem), "activate", GTK_SIGNAL_FUNC (show_event1), NULL);
    gtk_widget_show (menuitem);

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
    gtk_signal_connect(GTK_OBJECT (menuitem), "activate", GTK_SIGNAL_FUNC (show_event), NULL);
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
    gtk_widget_show(menuEdit);
    gtk_widget_show(menuLoad);
    gtk_widget_show(menuSave);
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

void GTKUI::run_nogui()
{
    char c;
    printf("Type 'q' to quit\nor \ntype 'g' to load the GUI\n>");
    while (strcmp(stopit, "go") == 0)
    {
        sleep(1);
        if ((c = getchar()) == 'g')
        {
            printf("Ok,  please use the GUI for input now\n>");
            assert(fTop == 0);
            gtk_widget_show  (fBox[0]);
            gtk_widget_show  (fWindow);
            gtk_timeout_add(40, callUpdateAllGuis, 0);
            gtk_main ();
            assert(fTop == 0);
            printf("quit the GUI\nType 'q' to quit\nor \ntype 'g' to load the GUI\n>");
        }
        else if (c  == 'q')
        {
            stopit = "stop";
            checky = 0.0;
            printf("bye bye\n");
        }
        else if (c  == ' ')
        {
            printf("what did you think happen if you enter a empty space ?\n>");
        }
        else if ((int(c)  > 48) && (int(c)  < 55))
        {
            const char*	  home;
            const char*      prename = "guitarixpre";
            char                rcfilenamere[256];
            int lin;
            int lint;
            home = getenv ("HOME");
            if (home == 0) home = ".";
            snprintf(rcfilenamere, 256, "%s/.guitarix/%src", home, prename);
            lin = int(c) - 49;
            lint = lin + 1;
            interface->recallpreState(rcfilenamere, lin);
            printf("load preset %u \n>",  lint);
        }
        else if (c  == '0')
        {
            const char*	  home;
            const char*      prename = "guitarix";
            char                rcfilenamere[256];
            int lin;
            int lint;
            home = getenv ("HOME");
            if (home == 0) home = ".";
            snprintf(rcfilenamere, 256, "%s/.guitarix/%src", home, prename);
            lin = int(c) - 49;
            lint = lin + 1;
            interface->recallState(rcfilenamere);
            printf("load preset %u \n>",  lint);
        }
    }
    stop();
}


void GTKUI::run()
{
    if (strcmp(param, "nogui") == 0)
    {
        run_nogui();
    }
    else
    {
        assert(fTop == 0);
        gtk_widget_show  (fBox[0]);
        gtk_widget_show  (fWindow);
        gtk_timeout_add(40, callUpdateAllGuis, 0);
        gtk_main ();
        stop();
    }
}



