
#include "lv2/lv2plug.in/ns/lv2core/lv2.h"
#include "lv2/lv2plug.in/ns/extensions/ui/ui.h"

// xwidgets.h includes xputty.h and all defined widgets from Xputty
#include "xwidgets.h"

#include "gx_livelooper.h"

/*---------------------------------------------------------------------
-----------------------------------------------------------------------    
                define controller numbers
-----------------------------------------------------------------------
----------------------------------------------------------------------*/

#define CONTROLS 43

/*---------------------------------------------------------------------
-----------------------------------------------------------------------    
                the main LV2 handle->XWindow
-----------------------------------------------------------------------
----------------------------------------------------------------------*/


// main window struct
typedef struct {
    void *parentXwindow;
    Xputty main;
    Widget_t *win;
    Widget_t *tool;
    Widget_t *widget[CONTROLS];
    cairo_surface_t *screw;
    int block_event;

    void *controller;
    LV2UI_Write_Function write_function;
    LV2UI_Resize* resize;
} X11_UI;

// setup a color theme
static void set_my_theme(Xputty *main) {
    main->color_scheme->normal = (Colors) {
         /* cairo    / r  / g  / b  / a  /  */
        /*fg */       { 0.68, 0.44, 0.00, 1.00},
        /*bg */       { 0.1, 0.1, 0.1, 1.0},
        /*base */     { 0.1, 0.1, 0.1, 1.0},
        /*text */     { 0.85, 0.52, 0.00, 1.00},
        /*shadow */   { 0.85, 0.52, 0.00, 0.2},
        /*frame */    { 0.0, 0.0, 0.0, 1.0},
        /*light */    { 0.1, 0.1, 0.2, 1.0}
    };

    main->color_scheme->prelight = (Colors) {
        /*fg */       { 1.0, 1.0, 1.0, 1.0},
        /*bg */       { 0.25, 0.25, 0.25, 1.0},
        /*base */     { 0.2, 0.2, 0.3, 1.0},
        /*text */     { 0.7, 0.7, 0.7, 1.0},
        /*shadow */   { 0.1, 0.1, 0.1, 0.4},
        /*frame */    { 0.3, 0.3, 0.3, 1.0},
        /*light */    { 0.3, 0.3, 0.3, 1.0}
    };

    main->color_scheme->selected = (Colors) {
        /*fg */       { 0.9, 0.9, 0.9, 1.0},
        /*bg */       { 0.2, 0.2, 0.2, 1.0},
        /*base */     { 0.1, 0.1, 0.1, 1.0},
        /*text */     { 1.0, 1.0, 1.0, 1.0},
        /*shadow */   { 0.18, 0.18, 0.18, 0.2},
        /*frame */    { 0.18, 0.18, 0.18, 1.0},
        /*light */    { 0.18, 0.18, 0.28, 1.0}
    };

    main->color_scheme->active = (Colors) {
         /* cairo    / r  / g  / b  / a  /  */
        /*fg */       { 0.68, 0.44, 0.00, 1.00},
        /*bg */       { 0.1, 0.1, 0.1, 1.0},
        /*base */     { 0.1, 0.1, 0.1, 1.0},
        /*text */     { 0.85, 0.52, 0.00, 1.00},
        /*shadow */   { 0.85, 0.52, 0.00, 0.2},
        /*frame */    { 0.0, 0.0, 0.0, 1.0},
        /*light */    { 0.1, 0.1, 0.2, 1.0}
    };
}

// draw the window
static void draw_window(void *w_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    X11_UI* ui = (X11_UI*)w->parent_struct;
    set_pattern(w,&w->app->color_scheme->selected,&w->app->color_scheme->normal,BACKGROUND_);
    cairo_paint (w->crb);
    set_pattern(w,&w->app->color_scheme->normal,&w->app->color_scheme->selected,BACKGROUND_);
    cairo_rectangle (w->crb,4,4,w->width-8,w->height-8);
    cairo_set_line_width(w->crb,4);
    cairo_stroke(w->crb);

    cairo_set_source_surface (w->crb, ui->screw,5,5);
    cairo_paint (w->crb);
    cairo_set_source_surface (w->crb, ui->screw,5,w->height-37);
    cairo_paint (w->crb);
    cairo_set_source_surface (w->crb, ui->screw,w->width-37,w->height-37);
    cairo_paint (w->crb);
    cairo_set_source_surface (w->crb, ui->screw,w->width-37,5);
    cairo_paint (w->crb);
    cairo_new_path (w->crb);

    cairo_text_extents_t extents;
    use_text_color_scheme(w, get_color_state(w));
    //cairo_set_source_rgb (w->crb,0.45, 0.45, 0.45);
    float font_size = min(20.0,((w->height/2.2 < (w->width*0.5)/3) ? w->height/2.2 : (w->width*0.5)/3));
    cairo_set_font_size (w->crb, font_size);
    cairo_text_extents(w->crb,w->label , &extents);
    double tw = extents.width/2.0;

    widget_set_scale(w);
    cairo_move_to (w->crb, 462-tw, 170 );
    cairo_show_text(w->crb, w->label);
    cairo_new_path (w->crb);
    cairo_scale (w->crb, 0.95, 0.95);
    cairo_set_source_surface (w->crb, w->image,825,10);
    cairo_paint (w->crb);
    cairo_scale (w->crb, 1.05, 1.05);
    widget_reset_scale(w);
}

// draw the knobs
static void draw_my_knob(void *w_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    int width = w->width-2;
    int height = w->height-2;

    const double scale_zero = 20 * (M_PI/180); // defines "dead zone" for knobs
    int arc_offset = 2;
    int knob_x = 0;
    int knob_y = 0;

    int grow = (width > height) ? height:width;
    knob_x = grow-1;
    knob_y = grow-1;
    /** get values for the knob **/

    int knobx = (width - knob_x) * 0.5;
    int knobx1 = width* 0.5;

    int knoby = (height - knob_y) * 0.5;
    int knoby1 = height * 0.5;

    double knobstate = adj_get_state(w->adj_y);
    double angle = scale_zero + knobstate * 2 * (M_PI - scale_zero);

    double pointer_off =knob_x/3.5;
    double radius = min(knob_x-pointer_off, knob_y-pointer_off) / 2;
    double lengh_x = (knobx+radius+pointer_off/2) - radius * sin(angle);
    double lengh_y = (knoby+radius+pointer_off/2) + radius * cos(angle);
    double radius_x = (knobx+radius+pointer_off/2) - radius/ 1.18 * sin(angle);
    double radius_y = (knoby+radius+pointer_off/2) + radius/ 1.18 * cos(angle);
    cairo_pattern_t* pat;
    cairo_new_path (w->crb);

    pat = cairo_pattern_create_linear (0, 0, 0, knob_y);
    cairo_pattern_add_color_stop_rgba (pat, 1,  0.349, 0.313, 0.243, 1.0);
    cairo_pattern_add_color_stop_rgba (pat, 0.75,  0.349, 0.235, 0.011, 1.0);
    cairo_pattern_add_color_stop_rgba (pat, 0.5,  0.15, 0.15, 0.15, 1.0);
    cairo_pattern_add_color_stop_rgba (pat, 0.25,  0.1, 0.1, 0.1, 1.0);
    cairo_pattern_add_color_stop_rgba (pat, 0,  0.05, 0.05, 0.05, 1.0);

    cairo_scale (w->crb, 0.95, 1.05);
    cairo_arc(w->crb,knobx1+arc_offset/2, knoby1-arc_offset, knob_x/2.2, 0, 2 * M_PI );
    cairo_set_source (w->crb, pat);
    cairo_fill_preserve (w->crb);
    cairo_set_source_rgb (w->crb, 0.1, 0.1, 0.1); 
    cairo_set_line_width(w->crb,1);
    cairo_stroke(w->crb);
    cairo_scale (w->crb, 1.05, 0.95);
    cairo_new_path (w->crb);
    cairo_pattern_destroy (pat);
    pat = NULL;

    pat = cairo_pattern_create_linear (0, 0, 0, knob_y);
    cairo_pattern_add_color_stop_rgba (pat, 0,  0.349, 0.213, 0.143, 1.0);
    cairo_pattern_add_color_stop_rgba (pat, 0.25,  0.349, 0.235, 0.011, 1.0);
    cairo_pattern_add_color_stop_rgba (pat, 0.5,  0.15, 0.15, 0.15, 1.0);
    cairo_pattern_add_color_stop_rgba (pat, 0.75,  0.1, 0.1, 0.1, 1.0);
    cairo_pattern_add_color_stop_rgba (pat, 1,  0.05, 0.05, 0.05, 1.0);

    cairo_arc(w->crb,knobx1, knoby1, knob_x/2.6, 0, 2 * M_PI );
    cairo_set_source (w->crb, pat);
    cairo_fill_preserve (w->crb);
    cairo_set_source_rgb (w->crb, 0.1, 0.1, 0.1); 
    cairo_set_line_width(w->crb,1);
    cairo_stroke(w->crb);
    cairo_new_path (w->crb);
    cairo_pattern_destroy (pat);

    use_text_color_scheme(w, get_color_state(w));

    /** create a rotating pointer on the kob**/
    cairo_set_line_cap(w->crb, CAIRO_LINE_CAP_ROUND); 
    cairo_set_line_join(w->crb, CAIRO_LINE_JOIN_BEVEL);
    cairo_move_to(w->crb, radius_x, radius_y);
    cairo_line_to(w->crb,lengh_x,lengh_y);
    cairo_set_line_width(w->crb,3);
    cairo_stroke(w->crb);
    cairo_new_path (w->crb);

    cairo_text_extents_t extents;
    /** show value on the kob**/
    if (w->state>0.0 && w->state<4.0) {
        char s[64];
        const char* format[] = {"%.1f", "%.2f", "%.3f"};
        snprintf(s, 63, format[2-1], w->adj_y->value);
        cairo_set_font_size (w->crb, min(11.0,knobx1/3));
       cairo_text_extents(w->crb, s, &extents);
        cairo_move_to (w->crb, knobx1-extents.width/2, knoby1+extents.height/2);
        cairo_show_text(w->crb, s);
        cairo_new_path (w->crb);
    }

    /** show label below the knob**/
    float font_size = min(12.0,((height/2.2 < (width*0.6)/3) ? height/2.2 : (width*0.6)/3));
    cairo_set_font_size (w->crb, font_size);
    cairo_text_extents(w->crb,w->label , &extents);

    cairo_move_to (w->crb, knobx1-extents.width/2, height );
    cairo_show_text(w->crb, w->label);
    cairo_new_path (w->crb);
}

void draw_my_hslider(void *w_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;

    int width = w->width-2;
    int height = w->height-2;
    float center = (float)height/2;

    float sliderstate = adj_get_state(w->adj_x);

    use_text_color_scheme(w, get_color_state(w));
    cairo_move_to (w->crb, 0.0, center);
    cairo_line_to(w->crb,width,center);
    cairo_set_line_width(w->crb,center/10);
    cairo_stroke(w->crb);

    use_bg_color_scheme(w, NORMAL_);
    cairo_rectangle(w->crb, (width-height)*sliderstate,0,height, height);
    cairo_fill(w->crb);
    cairo_new_path (w->crb);

    use_text_color_scheme(w, NORMAL_);
    cairo_set_line_width(w->crb,3);
    cairo_move_to (w->crb,((width-height)*sliderstate)+center, 0.0);
    cairo_line_to(w->crb,((width-height)*sliderstate)+center,height);
    cairo_stroke(w->crb);

    /** show value on the kob**/
    if (w->state>0.0 && w->state<4.0) {
        use_fg_color_scheme(w, PRELIGHT_);
        cairo_text_extents_t extents;
        char s[64];
        char l[64];
        snprintf(l,63,"%s ", w->label);
        const char* format[] = {"%.1f", "%.2f", "%.3f"};
        snprintf(s, 63, format[2-1], w->adj->value);
        strcat(l,s);
        cairo_set_font_size (w->crb, min(11.0,height));
        cairo_text_extents(w->crb, l, &extents);
        cairo_move_to (w->crb, min(width-extents.width ,(width-height)*sliderstate), height);
        cairo_show_text(w->crb, l);
        cairo_new_path (w->crb);
    }
}

static void check_bar(X11_UI* ui, uint32_t port_index, float*value) {
    if((int)(*value)) return;
    float v = 0.0;
    switch ((PortIndex)port_index)
        {
        case bar1:
            check_value_changed(ui->widget[0]->adj, &v);
        break;
        case bar2:
            check_value_changed(ui->widget[1]->adj, &v);
        break;
        case bar3:
            check_value_changed(ui->widget[2]->adj, &v);
        break;
        case bar4:
            check_value_changed(ui->widget[3]->adj, &v);
        break;
        default:
        break;
    }
}

static void check_radio(X11_UI* ui, uint32_t port_index, float*value) {
    if(!(int)(*value)) return;
    float v = 0.0;
    switch ((PortIndex)port_index)
        {
        case play1:
            check_value_changed(ui->widget[8]->adj, &v);
        break;
        case play2:
            check_value_changed(ui->widget[9]->adj, &v);
        break;
        case play3:
            check_value_changed(ui->widget[10]->adj, &v);
        break;
        case play4:
            check_value_changed(ui->widget[11]->adj, &v);
        break;
        case rplay1:
            check_value_changed(ui->widget[4]->adj, &v);
        break;
        case rplay2:
            check_value_changed(ui->widget[5]->adj, &v);
        break;
        case rplay3:
            check_value_changed(ui->widget[6]->adj, &v);
        break;
        case rplay4:
            check_value_changed(ui->widget[7]->adj, &v);
        break;
        default:
        break;
    }
}

static void check_clip(X11_UI* ui, uint32_t port_index) {
    switch ((PortIndex)port_index)
        {
        case clip1:
        case clips1:
            expose_widget(ui->widget[16]);
        break;
        case clip2:
        case clips2:
            expose_widget(ui->widget[17]);
        break;
        case clip3:
        case clips3:
            expose_widget(ui->widget[18]);
        break;
        case clip4:
        case clips4:
            expose_widget(ui->widget[19]);
        break;
        default:
        break;
    }
}

static void check_reset(X11_UI* ui, uint32_t port_index, float*value) {
    if(!(int)(*value)) return;
    float v = 0.0;
    float vi = 100.0;
    switch ((PortIndex)port_index)
        {
        case reset1:
            check_value_changed(ui->widget[20]->adj, &v);
            check_value_changed(ui->widget[24]->adj, &vi);
        break;
        case reset2:
            check_value_changed(ui->widget[21]->adj, &v);
            check_value_changed(ui->widget[25]->adj, &vi);
        break;
        case reset3:
            check_value_changed(ui->widget[22]->adj, &v);
            check_value_changed(ui->widget[26]->adj, &vi);
        break;
        case reset4:
            check_value_changed(ui->widget[23]->adj, &v);
            check_value_changed(ui->widget[27]->adj, &vi);
        break;

        default:
        break;
    }
}

static void check_sync(X11_UI* ui, uint32_t port_index, float*value) {
    if (!adj_get_value(ui->widget[42]->adj)) return;
    switch ((PortIndex)port_index)
        {
        case play1:
        case play2:
        case play3:
        case play4:
            {
            float v = adj_get_value(ui->widget[4]->adj);
            check_value_changed(ui->widget[5]->adj, &v);
            check_value_changed(ui->widget[6]->adj, &v);
            check_value_changed(ui->widget[7]->adj, &v);
            }
        break;
        case rplay1:
        case rplay2:
        case rplay3:
        case rplay4:
            {
            float v = adj_get_value(ui->widget[8]->adj);
            check_value_changed(ui->widget[9]->adj, &v);
            check_value_changed(ui->widget[10]->adj, &v);
            check_value_changed(ui->widget[11]->adj, &v);
            }
        break;
        case rback1:
        case rback2:
        case rback3:
        case rback4:
            {
            float v = adj_get_value(ui->widget[38]->adj);
            check_value_changed(ui->widget[39]->adj, &v);
            check_value_changed(ui->widget[40]->adj, &v);
            check_value_changed(ui->widget[41]->adj, &v);
            }
        break;
        case clips1:
        case clips2:
        case clips3:
        case clips4:
            {
            float v = adj_get_value(ui->widget[20]->adj);
            check_value_changed(ui->widget[21]->adj, &v);
            check_value_changed(ui->widget[22]->adj, &v);
            check_value_changed(ui->widget[23]->adj, &v);
            }
        break;
        case clip1:
        case clip2:
        case clip3:
        case clip4:
            {
            float v = adj_get_value(ui->widget[24]->adj);
            check_value_changed(ui->widget[25]->adj, &v);
            check_value_changed(ui->widget[26]->adj, &v);
            check_value_changed(ui->widget[27]->adj, &v);
            }
        break;
        case speed1:
        case speed2:
        case speed3:
        case speed4:
            {
            float v = adj_get_value(ui->widget[28]->adj);
            check_value_changed(ui->widget[29]->adj, &v);
            check_value_changed(ui->widget[30]->adj, &v);
            check_value_changed(ui->widget[31]->adj, &v);
            }
        break;
        case reset1:
            check_value_changed(ui->widget[13]->adj, value);
            check_value_changed(ui->widget[14]->adj, value);
            check_value_changed(ui->widget[15]->adj, value);
        break;

        default:
        break;
    }
}

// if controller value changed send notify to host
static void value_changed(void *w_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    X11_UI* ui = (X11_UI*)w->parent_struct;
    if (ui->block_event != w->data) {
        ui->write_function(ui->controller,w->data,sizeof(float),0,&w->adj->value);
        check_radio(ui, (uint32_t)w->data, &w->adj->value);
        check_clip(ui, (uint32_t)w->data);
        check_reset(ui, (uint32_t)w->data, &w->adj->value);
        check_sync(ui, (uint32_t)w->data, &w->adj->value);
    }
    ui->block_event = -1;
}

static void tool_changed(void *w_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    X11_UI* ui = (X11_UI*)w->parent_struct;
    
    int i = 20;
    for(;i<36;i++) {
        if(w->adj->value) ui->widget[i]->flags |= HAS_TOOLTIP;
        else ui->widget[i]->flags &= ~HAS_TOOLTIP;
    }
    if(w->adj->value) ui->widget[42]->flags |= HAS_TOOLTIP;
    else ui->widget[42]->flags &= ~HAS_TOOLTIP;
}

// shortcut to create knobs with portindex binding
Widget_t* add_my_knob(Widget_t *w, PortIndex index, const char * label,
                                X11_UI* ui, int x, int y, int width, int height) {
    w = add_knob(ui->win, label, x, y, width, height);
    w->func.expose_callback = draw_my_knob;    
    w->parent_struct = ui;
    w->data = index;
    w->func.value_changed_callback = value_changed;
    return w;
}

// shortcut to create buttons with portindex binding
Widget_t* add_my_toggle_button(Widget_t *w, PortIndex index, const char * label,
                                X11_UI* ui, int x, int y, int width, int height) {
    w = add_image_toggle_button(ui->win, label, x, y, width, height);
    w->parent_struct = ui;
    w->data = index;
    w->func.value_changed_callback = value_changed;
    return w;
}

// shortcut to create buttons with portindex binding
Widget_t* add_my_button(Widget_t *w, PortIndex index, const char * label,
                                X11_UI* ui, int x, int y, int width, int height) {
    w = add_button(ui->win, label, x, y, width, height);
    w->parent_struct = ui;
    w->data = index;
    w->func.value_changed_callback = value_changed;
    return w;
}

// shortcut to create knobs with portindex binding
Widget_t* add_my_slider(Widget_t *w, PortIndex index, const char * label,
                                X11_UI* ui, int x, int y, int width, int height) {
    w = add_hslider(ui->win, label, x, y, width, height);
    set_adjustment(w->adj,0.0, 0.0, 0.0, 100.0, 0.1, CL_CONTINUOS);
    w->func.expose_callback = draw_my_hslider;    
    w->parent_struct = ui;
    w->data = index;
    w->func.value_changed_callback = value_changed;
    return w;
}

// shortcut to create comboboxes with portindex binding
Widget_t* add_my_combobox(Widget_t *w, PortIndex index, const char * label, const char** items,
                                size_t len, int active, X11_UI* ui, int x, int y, int width, int height) {
    w = add_combobox(ui->win, label, x, y, width, height);
    size_t st = 0;
    for(st = 0; st < len; st++) {
        combobox_add_entry(w,items[st]);
    }
    w->parent_struct = ui;
    w->data = index;
    combobox_set_active_entry(w, active);
    w->func.value_changed_callback = value_changed;
    return w;
}

// init the xwindow and return the LV2UI handle
static LV2UI_Handle instantiate(const LV2UI_Descriptor * descriptor,
            const char * plugin_uri, const char * bundle_path,
            LV2UI_Write_Function write_function,
            LV2UI_Controller controller, LV2UI_Widget * widget,
            const LV2_Feature * const * features) {

    X11_UI* ui = (X11_UI*)malloc(sizeof(X11_UI));

    if (!ui) {
        fprintf(stderr,"ERROR: failed to instantiate plugin with URI %s\n", plugin_uri);
        return NULL;
    }

    ui->parentXwindow = 0;
    LV2UI_Resize* resize = NULL;
    ui->block_event = -1;

    int i = 0;
    for (; features[i]; ++i) {
        if (!strcmp(features[i]->URI, LV2_UI__parent)) {
            ui->parentXwindow = features[i]->data;
        } else if (!strcmp(features[i]->URI, LV2_UI__resize)) {
            resize = (LV2UI_Resize*)features[i]->data;
        }
    }

    if (ui->parentXwindow == NULL)  {
        fprintf(stderr, "ERROR: Failed to open parentXwindow for %s\n", plugin_uri);
        free(ui);
        return NULL;
    }
    // init Xputty
    main_init(&ui->main);
    set_my_theme(&ui->main);
    // create the toplevel Window on the parentXwindow provided by the host
    ui->win = create_window(&ui->main, (Window)ui->parentXwindow, 0, 0, 925, 180);
    ui->win->parent_struct = ui;
    ui->win->label = "Gxlivelooper";
    widget_get_png(ui->win, LDVAR(guitarix_orange_png));
    ui->screw = surface_get_png(ui->win, ui->screw, LDVAR(screw_png));
    // connect the expose func
    ui->win->func.expose_callback = draw_window;

    // set min size equal to base size
    XSizeHints* win_size_hints;
    win_size_hints = XAllocSizeHints();
    win_size_hints->flags =  PMinSize|PBaseSize|PWinGravity;
    win_size_hints->min_width = 925;
    win_size_hints->min_height = 180;
    win_size_hints->base_width = 925;
    win_size_hints->base_height = 180;
    win_size_hints->win_gravity = CenterGravity;
    XSetWMNormalHints(ui->main.dpy, ui->win->widget, win_size_hints);
    XFree(win_size_hints);
    
    ui->tool = add_check_box(ui->win, "Show tooltips", 40, 10, 80, 15);
    ui->tool->parent_struct = ui;
    ui->tool->scale.gravity  = FIXEDSIZE;
    ui->tool->flags |= FAST_REDRAW;
    adj_set_value(ui->tool->adj,1.0);
    ui->tool->func.value_changed_callback = tool_changed;
    
    // create knob widgets
    ui->widget[0] = add_my_toggle_button(ui->widget[0], rec1,"", ui,140, 85, 30, 30);
    widget_get_png(ui->widget[0], LDVAR(record_png));

    ui->widget[1] = add_my_toggle_button(ui->widget[1], rec2,"", ui,305, 85, 30, 30);
    widget_get_surface_ptr(ui->widget[1], ui->widget[0]);

    ui->widget[2] = add_my_toggle_button(ui->widget[2], rec3,"", ui,470, 85, 30, 30);
    widget_get_surface_ptr(ui->widget[2], ui->widget[0]);

    ui->widget[3] = add_my_toggle_button(ui->widget[3], rec4,"", ui,635, 85, 30, 30);
    widget_get_surface_ptr(ui->widget[3], ui->widget[0]);


    ui->widget[4] = add_my_toggle_button(ui->widget[4], play1,"", ui,170, 85, 30, 30);
    widget_get_png(ui->widget[4], LDVAR(play_png));

    ui->widget[5] = add_my_toggle_button(ui->widget[5], play2,"", ui,335, 85, 30, 30);
    widget_get_surface_ptr(ui->widget[5], ui->widget[4]);

    ui->widget[6] = add_my_toggle_button(ui->widget[6], play3,"", ui,500, 85, 30, 30);
    widget_get_surface_ptr(ui->widget[6], ui->widget[4]);

    ui->widget[7] = add_my_toggle_button(ui->widget[7], play4,"", ui,665, 85, 30, 30);
    widget_get_surface_ptr(ui->widget[7], ui->widget[4]);


    ui->widget[8] = add_my_toggle_button(ui->widget[8], rplay1,"", ui,200, 85, 30, 30);
    widget_get_png(ui->widget[8], LDVAR(playreverse_png));

    ui->widget[9] = add_my_toggle_button(ui->widget[9], rplay2,"", ui,365, 85, 30, 30);
    widget_get_surface_ptr(ui->widget[9], ui->widget[8]);

    ui->widget[10] = add_my_toggle_button(ui->widget[10], rplay3,"", ui,530, 85, 30, 30);
    widget_get_surface_ptr(ui->widget[10], ui->widget[8]);

    ui->widget[11] = add_my_toggle_button(ui->widget[11], rplay4,"", ui,695, 85, 30, 30);
    widget_get_surface_ptr(ui->widget[11], ui->widget[8]);


    ui->widget[38] = add_my_button(ui->widget[38], rback1,"", ui,230, 85, 30, 30);
    widget_get_png(ui->widget[38], LDVAR(back_png));

    ui->widget[39] = add_my_button(ui->widget[39], rback2,"", ui,395, 85, 30, 30);
    widget_get_surface_ptr(ui->widget[39], ui->widget[38]);

    ui->widget[40] = add_my_button(ui->widget[40], rback3,"", ui,560, 85, 30, 30);
    widget_get_surface_ptr(ui->widget[40], ui->widget[38]);

    ui->widget[41] = add_my_button(ui->widget[41], rback4,"", ui,725, 85, 30, 30);
    widget_get_surface_ptr(ui->widget[41], ui->widget[38]);


    ui->widget[12] = add_my_button(ui->widget[12], reset1,"", ui,260, 85, 30, 30);
    widget_get_png(ui->widget[12], LDVAR(close_png));

    ui->widget[13] = add_my_button(ui->widget[13], reset2,"", ui,425, 85, 30, 30);
    widget_get_surface_ptr(ui->widget[13], ui->widget[12]);

    ui->widget[14] = add_my_button(ui->widget[14], reset3,"", ui,590, 85, 30, 30);
    widget_get_surface_ptr(ui->widget[14], ui->widget[12]);

    ui->widget[15] = add_my_button(ui->widget[15], reset4,"", ui,755, 85, 30, 30);
    widget_get_surface_ptr(ui->widget[15], ui->widget[12]);


    ui->widget[20] = add_my_slider(ui->widget[20], clips1,"clip", ui,140, 115, 150, 12);
    add_tooltip(ui->widget[20],"clip loop at start");
    ui->widget[21] = add_my_slider(ui->widget[21], clips2,"clip", ui,305, 115, 150, 12);
    add_tooltip(ui->widget[21],"clip loop at start");
    ui->widget[22] = add_my_slider(ui->widget[22], clips3,"clip", ui,470, 115, 150, 12);
    add_tooltip(ui->widget[22],"clip loop at start");
    ui->widget[23] = add_my_slider(ui->widget[23], clips4,"clip", ui,635, 115, 150, 12);
    add_tooltip(ui->widget[23],"clip loop at start");

    ui->widget[24] = add_my_slider(ui->widget[24], clip1,"cut", ui,140, 127, 150, 12);
    add_tooltip(ui->widget[24],"cut loop at end");
    ui->widget[25] = add_my_slider(ui->widget[25], clip2,"cut", ui,305, 127, 150, 12);
    add_tooltip(ui->widget[25],"cut loop at end");
    ui->widget[26] = add_my_slider(ui->widget[26], clip3,"cut", ui,470, 127, 150, 12);
    add_tooltip(ui->widget[26],"cut loop at end");
    ui->widget[27] = add_my_slider(ui->widget[27], clip4,"cut", ui,635, 127, 150, 12);
    add_tooltip(ui->widget[27],"cut loop at end");

    ui->widget[16] = add_playhead(ui->win,"", ui->widget[20]->adj, ui->widget[24]->adj, 140,75,150,10);
    ui->widget[16]->parent_struct = ui;
    ui->widget[16]->data = playh1;

    ui->widget[17] = add_playhead(ui->win,"", ui->widget[21]->adj, ui->widget[25]->adj, 305,75,150,10);
    ui->widget[17]->parent_struct = ui;
    ui->widget[17]->data = playh2;

    ui->widget[18] = add_playhead(ui->win,"", ui->widget[22]->adj, ui->widget[26]->adj, 470,75,150,10);
    ui->widget[18]->parent_struct = ui;
    ui->widget[18]->data = playh3;

    ui->widget[19] = add_playhead(ui->win,"", ui->widget[23]->adj, ui->widget[27]->adj, 635,75,150,10);
    ui->widget[19]->parent_struct = ui;
    ui->widget[19]->data = playh4;

    ui->widget[28] = add_my_slider(ui->widget[28], speed1,"speed", ui,140, 63, 150, 12);
    set_adjustment(ui->widget[28]->adj,0.0, 0.0, -0.9, 0.9, 0.01, CL_CONTINUOS);
    add_tooltip(ui->widget[28],"playback speed");

    ui->widget[29] = add_my_slider(ui->widget[29], speed2,"speed", ui,305, 63, 150, 12);
    set_adjustment(ui->widget[29]->adj,0.0, 0.0, -0.9, 0.9, 0.01, CL_CONTINUOS);
    add_tooltip(ui->widget[29],"playback speed");

    ui->widget[30] = add_my_slider(ui->widget[30], speed3,"speed", ui,470, 63, 150, 12);
    set_adjustment(ui->widget[30]->adj,0.0, 0.0, -0.9, 0.9, 0.01, CL_CONTINUOS);
    add_tooltip(ui->widget[30],"playback speed");

    ui->widget[31] = add_my_slider(ui->widget[31], speed4,"speed", ui,635, 63, 150, 12);
    set_adjustment(ui->widget[31]->adj,0.0, 0.0, -0.9, 0.9, 0.01, CL_CONTINUOS);
    add_tooltip(ui->widget[31],"playback speed");


    ui->widget[32] = add_my_slider(ui->widget[32], level1,"level", ui,140, 43, 150, 12);
    set_adjustment(ui->widget[32]->adj,50.0, 50.0, 0.0, 100., 1.0, CL_CONTINUOS);
    add_tooltip(ui->widget[32],"loop1 playback level");

    ui->widget[33] = add_my_slider(ui->widget[33], level2,"level", ui,305, 43, 150, 12);
    set_adjustment(ui->widget[33]->adj,50.0, 50.0, 0.0, 100., 1.0, CL_CONTINUOS);
    add_tooltip(ui->widget[33],"loop2 playback level");

    ui->widget[34] = add_my_slider(ui->widget[34], level3,"level", ui,470, 43, 150, 12);
    set_adjustment(ui->widget[34]->adj,50.0, 50.0, 0.0, 100., 1.0, CL_CONTINUOS);
    add_tooltip(ui->widget[34],"loop3 playback level");

    ui->widget[35] = add_my_slider(ui->widget[35], level4,"level", ui,635, 43, 150, 12);
    set_adjustment(ui->widget[35]->adj,50.0, 50.0, 0.0, 100., 1.0, CL_CONTINUOS);
    add_tooltip(ui->widget[35],"loop4 playback level");


    ui->widget[36] = add_my_knob(ui->widget[36], gain,"Gain", ui,40, 35, 80, 105);
    set_adjustment(ui->widget[36]->adj,0.0, 0.0, -20.0, 12.0, 0.1, CL_CONTINUOS);

    ui->widget[37] = add_my_knob(ui->widget[37], mix,"Mix", ui,805, 35, 80, 105);
    set_adjustment(ui->widget[37]->adj,100.0, 100.0, 0.0, 150.0, 1.0, CL_CONTINUOS);
    
    ui->widget[42] = add_check_box(ui->win, "sync tapes", 140, 150, 80, 15);
    ui->widget[42]->parent_struct = ui;
    ui->widget[42]->data = synct;
    ui->widget[42]->func.value_changed_callback = value_changed;
    add_tooltip(ui->widget[42],"loop1 becomes the master");

    // set all controllers to FIXEDSIZE and FAST_REDRAW to reduce flicker during resize
    i = 0;
    for (;i<CONTROLS;i++) {
        ui->widget[i]->scale.gravity  = FIXEDSIZE;
        ui->widget[i]->flags |= FAST_REDRAW;
    }

    adj_set_value(ui->tool->adj,0.0);
    // map all widgets into the toplevel Widget_t
    widget_show_all(ui->win);
    // set the widget pointer to the X11 Window from the toplevel Widget_t
    *widget = (void*)ui->win->widget;
    // request to resize the parentXwindow to the size of the toplevel Widget_t
    if (resize){
        ui->resize = resize;
        resize->ui_resize(resize->handle, 925, 180);
    }
    // store pointer to the host controller
    ui->controller = controller;
    // store pointer to the host write function
    ui->write_function = write_function;
    
    return (LV2UI_Handle)ui;
}

// cleanup after usage
static void cleanup(LV2UI_Handle handle) {
    X11_UI* ui = (X11_UI*)handle;
    cairo_surface_destroy(ui->screw);
    // Xputty free all memory used
    main_quit(&ui->main);
    free(ui);
}

/*---------------------------------------------------------------------
-----------------------------------------------------------------------    
                        LV2 interface
-----------------------------------------------------------------------
----------------------------------------------------------------------*/

// port value change message from host
static void port_event(LV2UI_Handle handle, uint32_t port_index,
                        uint32_t buffer_size, uint32_t format,
                        const void * buffer) {
    X11_UI* ui = (X11_UI*)handle;
    float value = *(float*)buffer;
    int i=0;
    for (;i<CONTROLS;i++) {
        if (port_index == (uint32_t)ui->widget[i]->data) {
            // prevent event loop between host and plugin
            ui->block_event = (int)port_index;
            // Xputty check if the new value differs from the old one
            // and set new one, when needed
            check_value_changed(ui->widget[i]->adj, &value);
        }
    }
    check_bar(ui, port_index, &value);
    check_radio(ui, port_index, &value);
    check_clip(ui, port_index);
    check_reset(ui, port_index, &value);
    check_sync(ui, port_index, &value);
}

// LV2 idle interface to host
static int ui_idle(LV2UI_Handle handle) {
    X11_UI* ui = (X11_UI*)handle;
    // Xputty event loop setup to run one cycle when called
    run_embedded(&ui->main);
    return 0;
}

// LV2 resize interface to host
static int ui_resize(LV2UI_Feature_Handle handle, int w, int h) {
    X11_UI* ui = (X11_UI*)handle;
    // Xputty sends configure event to the toplevel widget to resize itself
    if (ui) send_configure_event(ui->win,0, 0, w, h);
    return 0;
}

// connect idle and resize functions to host
static const void* extension_data(const char* uri) {
    static const LV2UI_Idle_Interface idle = { ui_idle };
    static const LV2UI_Resize resize = { 0 ,ui_resize };
    if (!strcmp(uri, LV2_UI__idleInterface)) {
        return &idle;
    }
    if (!strcmp(uri, LV2_UI__resize)) {
        return &resize;
    }
    return NULL;
}

static const LV2UI_Descriptor descriptor = {
    GXPLUGIN_UI_URI,
    instantiate,
    cleanup,
    port_event,
    extension_data
};



extern "C"
LV2_SYMBOL_EXPORT
const LV2UI_Descriptor* lv2ui_descriptor(uint32_t index) {
    switch (index) {
        case 0:
            return &descriptor;
        default:
        return NULL;
    }
}

