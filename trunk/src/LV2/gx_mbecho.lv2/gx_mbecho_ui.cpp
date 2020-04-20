
#include "lv2/lv2plug.in/ns/lv2core/lv2.h"
#include "lv2/lv2plug.in/ns/extensions/ui/ui.h"

// xwidgets.h includes xputty.h and all defined widgets from Xputty
#include "xwidgets.h"

#include "gx_mbecho.h"

/*---------------------------------------------------------------------
-----------------------------------------------------------------------    
                define controller numbers
-----------------------------------------------------------------------
----------------------------------------------------------------------*/

#define CONTROLS 10

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
    Widget_t *widget[CONTROLS+1];
    Widget_t *meter_widget[5];
    Adjustment_t *adj[3];
    cairo_surface_t *screw;
    int block_event;
    float db_zero;

    void *controller;
    LV2UI_Write_Function write_function;
    LV2UI_Resize* resize;
} X11_UI;

// setup a color theme
static void set_my_theme(Xputty *main) {
    main->color_scheme->normal = (Colors) {
         /* cairo    / r  / g  / b  / a  /  */
        .fg =       { 0.68, 0.44, 0.00, 1.00},
        .bg =       { 0.1, 0.1, 0.1, 1.0},
        .base =     { 0.1, 0.1, 0.1, 1.0},
        .text =     { 0.85, 0.52, 0.00, 1.00},
        .shadow =   { 0.85, 0.52, 0.00, 0.2},
        .frame =    { 0.0, 0.0, 0.0, 1.0},
        .light =    { 0.1, 0.1, 0.2, 1.0}
    };

    main->color_scheme->prelight = (Colors) {
        .fg =       { 1.0, 1.0, 1.0, 1.0},
        .bg =       { 0.25, 0.25, 0.25, 1.0},
        .base =     { 0.2, 0.2, 0.3, 1.0},
        .text =     { 0.7, 0.7, 0.7, 1.0},
        .shadow =   { 0.1, 0.1, 0.1, 0.4},
        .frame =    { 0.3, 0.3, 0.3, 1.0},
        .light =    { 0.3, 0.3, 0.3, 1.0}
    };

    main->color_scheme->selected = (Colors) {
        .fg =       { 0.9, 0.9, 0.9, 1.0},
        .bg =       { 0.2, 0.2, 0.2, 1.0},
        .base =     { 0.1, 0.1, 0.1, 1.0},
        .text =     { 1.0, 1.0, 1.0, 1.0},
        .shadow =   { 0.18, 0.18, 0.18, 0.2},
        .frame =    { 0.18, 0.18, 0.18, 1.0},
        .light =    { 0.18, 0.18, 0.28, 1.0}
    };

    main->color_scheme->active = (Colors) {
         /* cairo    / r  / g  / b  / a  /  */
        .fg =       { 0.68, 0.44, 0.00, 1.00},
        .bg =       { 0.1, 0.1, 0.1, 1.0},
        .base =     { 0.1, 0.1, 0.1, 1.0},
        .text =     { 0.85, 0.52, 0.00, 1.00},
        .shadow =   { 0.85, 0.52, 0.00, 0.2},
        .frame =    { 0.0, 0.0, 0.0, 1.0},
        .light =    { 0.1, 0.1, 0.2, 1.0}
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
    float font_size = min(20.0,((w->height/2.2 < (w->width*0.5)/3) ? w->height/2.2 : (w->width*0.5)/3));
    cairo_set_font_size (w->crb, font_size);
    cairo_text_extents(w->crb,w->label , &extents);
    double tw = extents.width/2.0;

    widget_set_scale(w);
    cairo_move_to (w->crb, 355-tw, 250 );
    cairo_show_text(w->crb, w->label);
    cairo_new_path (w->crb);
    cairo_scale (w->crb, 0.95, 0.95);
    cairo_set_source_surface (w->crb, w->image,610,10);
    cairo_paint (w->crb);
    cairo_scale (w->crb, 1.05, 1.05);
    widget_reset_scale(w);
}

// draw the slider handle
static void rounded_rectangle(cairo_t *cr,float x, float y, float w, float h) {
    float r = h*0.75;

    cairo_move_to(cr,x+r,y);
    cairo_line_to(cr,x+w-r,y);
    cairo_curve_to(cr,x+w,y,x+w,y,x+w,y+r);
    cairo_line_to(cr,x+w,y+h-r);
    cairo_curve_to(cr,x+w,y+h,x+w,y+h,x+w-r,y+h);
    cairo_line_to(cr,x+r,y+h);
    cairo_curve_to(cr,x,y+h,x,y+h,x,y+h-r);
    cairo_line_to(cr,x,y+r);
    cairo_curve_to(cr,x,y,x,y,x+r,y);
}

// draw the slider
static void draw_my_hslider(void *w_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    X11_UI* ui = (X11_UI*)w->parent_struct;

    int width = w->width-2;
    int height = w->height-2;
    float center = (float)height/2;

    float sliderstate1 = adj_get_state(w->adj);
    float sliderstate2 = adj_get_state(ui->adj[0]);
    float sliderstate3 = adj_get_state(ui->adj[1]);
    float sliderstate4 = adj_get_state(ui->adj[2]);
    float sliderstate = 0.0;
    Color_state s1 = NORMAL_;
    Color_state s2 = NORMAL_;
    Color_state s3 = NORMAL_;
    Color_state s4 = NORMAL_;

    if (w->state>0.0 && w->state<4.0 && w->adj_x) {
        if (w->adj_x == w->adj) {
            sliderstate = sliderstate1;
            s1 = PRELIGHT_;
        } else if (w->adj_x == ui->adj[0]) {
            sliderstate = sliderstate2;
            s2 = PRELIGHT_;
        } else if (w->adj_x == ui->adj[1]) {
            sliderstate = sliderstate3;
            s3 = PRELIGHT_;
        } else if (w->adj_x == ui->adj[2]) {
            sliderstate = sliderstate4;
            s4 = PRELIGHT_;
        }
    }
    cairo_pattern_t* pat;

    pat = cairo_pattern_create_linear (0, 0, 0, height);
    cairo_pattern_add_color_stop_rgba (pat, 1,  0.25, 0.25, 0.25, 1.0);
    cairo_pattern_add_color_stop_rgba (pat, 0.75,  0.2, 0.2, 0.2, 1.0);
    cairo_pattern_add_color_stop_rgba (pat, 0.5,  0.15, 0.15, 0.15, 1.0);
    cairo_pattern_add_color_stop_rgba (pat, 0.25,  0.1, 0.1, 0.1, 1.0);
    cairo_pattern_add_color_stop_rgba (pat, 0,  0.05, 0.05, 0.05, 1.0);


    cairo_set_source (w->crb, pat);
    rounded_rectangle(w->crb, 0.0, 0.0,width,height);
    cairo_set_line_width(w->crb,2);
    cairo_stroke(w->crb);
    cairo_pattern_destroy (pat);
    pat = NULL;

    use_text_color_scheme(w, get_color_state(w));
    cairo_move_to (w->crb, center, center);
    cairo_line_to(w->crb,width-center,center);
    cairo_set_line_width(w->crb,center/10);
    cairo_stroke(w->crb);

    pat = cairo_pattern_create_linear (0, 0, 0, height);
    cairo_pattern_add_color_stop_rgba (pat, 0,  0.25, 0.25, 0.25, 1.0);
    cairo_pattern_add_color_stop_rgba (pat, 0.25,  0.2, 0.2, 0.2, 1.0);
    cairo_pattern_add_color_stop_rgba (pat, 0.5,  0.15, 0.15, 0.15, 1.0);
    cairo_pattern_add_color_stop_rgba (pat, 0.75,  0.1, 0.1, 0.1, 1.0);
    cairo_pattern_add_color_stop_rgba (pat, 1,  0.05, 0.05, 0.05, 1.0);

    cairo_set_source (w->crb, pat);
    rounded_rectangle(w->crb, (width-height)*sliderstate1,0,height, height);
    cairo_fill_preserve (w->crb);
    cairo_set_source_rgb (w->crb, 0.1, 0.1, 0.1); 
    cairo_set_line_width(w->crb,2);
    cairo_stroke(w->crb);
    cairo_new_path (w->crb);
    cairo_set_source (w->crb, pat);
    rounded_rectangle(w->crb, (width-height)*sliderstate2,0,height, height);
    cairo_fill_preserve (w->crb);
    cairo_set_source_rgb (w->crb, 0.1, 0.1, 0.1); 
    cairo_stroke(w->crb);
    cairo_new_path (w->crb);
    cairo_set_source (w->crb, pat);
    rounded_rectangle(w->crb, (width-height)*sliderstate3,0,height, height);
    cairo_fill_preserve (w->crb);
    cairo_set_source_rgb (w->crb, 0.1, 0.1, 0.1); 
    cairo_stroke(w->crb);
    cairo_new_path (w->crb);
    cairo_set_source (w->crb, pat);
    rounded_rectangle(w->crb, (width-height)*sliderstate4,0,height, height);
    cairo_fill_preserve (w->crb);
    cairo_set_source_rgb (w->crb, 0.1, 0.1, 0.1); 
    cairo_stroke(w->crb);
    cairo_new_path (w->crb);
    cairo_pattern_destroy (pat);
    pat = NULL;

    use_text_color_scheme(w, s1);
    cairo_set_line_width(w->crb,2);
    cairo_move_to (w->crb,((width-height)*sliderstate1)+center, 2.0);
    cairo_line_to(w->crb,((width-height)*sliderstate1)+center,height-2.0);
    cairo_stroke(w->crb);
    use_text_color_scheme(w, s2);
    cairo_move_to (w->crb,((width-height)*sliderstate2)+center, 2.0);
    cairo_line_to(w->crb,((width-height)*sliderstate2)+center,height-2.0);
    cairo_stroke(w->crb);
    use_text_color_scheme(w, s3);
    cairo_move_to (w->crb,((width-height)*sliderstate3)+center, 2.0);
    cairo_line_to(w->crb,((width-height)*sliderstate3)+center,height-2.0);
    cairo_stroke(w->crb);
    use_text_color_scheme(w, s4);
    cairo_move_to (w->crb,((width-height)*sliderstate4)+center, 2.0);
    cairo_line_to(w->crb,((width-height)*sliderstate4)+center,height-2.0);
    cairo_stroke(w->crb);

    /** show value on the slider**/
    if (w->state>0.0 && w->state<4.0 && w->adj_x) {
        use_fg_color_scheme(w, PRELIGHT_);
        cairo_text_extents_t extents;
        char s[64];
        char l[64];
        snprintf(l,63,"%s ", w->label);
        const char* format[] = {"%.1f", "%.2f", "%.3f"};
        snprintf(s, 63, format[2-1], pow(10.0,w->adj_x->value));
        strcat(l,s);
        cairo_set_font_size (w->crb, min(11.0,height));
        cairo_text_extents(w->crb, l, &extents);
        cairo_move_to (w->crb, min(width-extents.width ,(width-height)*sliderstate), height);
        cairo_show_text(w->crb, l);
        cairo_new_path (w->crb);
    }
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

    int knobx = (grow - knob_x) * 0.5;
    int knobx1 = grow* 0.5;

    int knoby = (grow - knob_y) * 0.5;
    int knoby1 = grow * 0.5;

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
    cairo_pattern_add_color_stop_rgba (pat, 1,  0.25, 0.25, 0.25, 1.0);
    cairo_pattern_add_color_stop_rgba (pat, 0.75,  0.2, 0.2, 0.2, 1.0);
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
    cairo_pattern_add_color_stop_rgba (pat, 0,  0.25, 0.25, 0.25, 1.0);
    cairo_pattern_add_color_stop_rgba (pat, 0.25,  0.2, 0.2, 0.2, 1.0);
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

// if controller value changed send notify to host
static void value_changed(void *w_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    X11_UI* ui = (X11_UI*)w->parent_struct;
    if (ui->block_event != w->data) 
        ui->write_function(ui->controller,w->data,sizeof(float),0,&w->adj->value);
    ui->block_event = -1;
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

// check that bands didn't overlap
static void check_multi_controller(X11_UI* ui, uint32_t port_index, float value) {
    float v = log10f(value);
    switch ((PortIndex)port_index)
        {
        case CROSSOVER_B1_B2:
            check_value_changed(ui->widget[10]->adj, &v);
            adj_set_value(ui->adj[0], max(adj_get_value(ui->adj[0]), v+0.1));
        break;
        case CROSSOVER_B2_B3:
            adj_set_value(ui->widget[10]->adj, min(adj_get_value(ui->widget[10]->adj), v-0.1));
            check_value_changed(ui->adj[0], &v);
            adj_set_value(ui->adj[1], max(adj_get_value(ui->adj[1]), v+0.1));
        break;
        case CROSSOVER_B3_B4:
            adj_set_value(ui->adj[0], min(adj_get_value(ui->adj[0]), v-0.1));
            check_value_changed(ui->adj[1], &v);
            adj_set_value(ui->adj[2], max(adj_get_value(ui->adj[2]), v+0.1));
        break;
        case CROSSOVER_B4_B5:
            adj_set_value(ui->adj[1], min(adj_get_value(ui->adj[1]), v-0.1));
            check_value_changed(ui->adj[2], &v);
        break;
        default:
        break;
    }
}

// if adjustment value changed send notify to host
static void slider_value_changed(void *w_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    X11_UI* ui = (X11_UI*)w->parent_struct;
    uint32_t port_index = 0;
    float value = 0.0;
    if (w->adj_x == w->adj) {
        port_index = CROSSOVER_B1_B2;
        value = adj_get_value(w->adj);
    } else if (w->adj_x == ui->adj[0]) {
        port_index = CROSSOVER_B2_B3;
        value = adj_get_value(ui->adj[0]);
    } else if (w->adj_x == ui->adj[1]) {
        port_index = CROSSOVER_B3_B4;
        value = adj_get_value(ui->adj[1]);
    } else if (w->adj_x == ui->adj[2]) {
        port_index = CROSSOVER_B4_B5;
        value = adj_get_value(ui->adj[2]);
    }
    if (port_index) {
        float v = pow(10,value);
        check_multi_controller(ui,port_index, v);
        if (ui->block_event != (int)port_index) 
            ui->write_function(ui->controller,port_index,sizeof(float),0,&v);
        ui->block_event = -1;
    }
}

// redraw slider when mouse button released
static void my_slider_released(void *w_, void* button_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    expose_widget(w);
}

// set active adjustment based on mouse position
static void my_slider_pressed(void *w_, void* button_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    X11_UI* ui = (X11_UI*)w->parent_struct;
    float x = float(w->pos_x)/float(w->width-w->height);

    float sliderstate1 = adj_get_state(w->adj);
    float sliderstate2 = adj_get_state(ui->adj[0]);
    float sliderstate3 = adj_get_state(ui->adj[1]);
    float sliderstate4 = adj_get_state(ui->adj[2]);

    if (x < sliderstate1+0.04 && x >sliderstate1) {
        w->adj_x = w->adj;
        w->label = "Band 1<|>2 ";
    }
    else if (x < sliderstate2+0.04 && x >sliderstate2) {
        w->adj_x = ui->adj[0];
        w->label = "Band 2<|>3 ";
    }
    else if (x < sliderstate3+0.04 && x >sliderstate3) {
        w->adj_x = ui->adj[1];
        w->label = "Band 3<|>4 ";
    }
    else if (x < sliderstate4+0.04 && x >sliderstate4) {
        w->adj_x = ui->adj[2];
        w->label = "Band 4<|>5 ";
    } else {
        w->adj_x = NULL;
        w->label = " ";
    }
    adj_set_start_value(w);

    expose_widget(w);
}

// shortcut to create multi adjustment slider with portindex binding
Widget_t* add_my_slider(Widget_t *w, PortIndex index, const char * label,
                                X11_UI* ui, int x, int y, int width, int height) {
    w = create_widget(ui->win->app, ui->win, x, y, width, height);
    w->label = label;    
    w->adj = add_adjustment(w,1.3, 1.3, 1.3, 4.3, 0.001, CL_CONTINUOS);
    adj_set_scale(w->adj, 2.0);
    ui->adj[0] = add_adjustment(w,1.3, 1.3, 1.3, 4.3, 0.001, CL_CONTINUOS);
    adj_set_scale(ui->adj[0], 2.0);
    ui->adj[1] = add_adjustment(w,1.3, 1.3, 1.3, 4.3, 0.001, CL_CONTINUOS);
    adj_set_scale(ui->adj[1], 2.0);
    ui->adj[2] = add_adjustment(w,1.3, 1.3, 1.3, 4.3, 0.001, CL_CONTINUOS);
    adj_set_scale(ui->adj[2], 2.0);
    w->scale.gravity = ASPECT;
    w->func.expose_callback = draw_my_hslider;
    w->func.enter_callback = transparent_draw;
    w->func.leave_callback = transparent_draw;
    w->func.button_press_callback = my_slider_pressed;
    w->func.button_release_callback = my_slider_released;
    w->parent_struct = ui;
    w->data = index;
    w->func.value_changed_callback = slider_value_changed;
    return w;
}

// init the xwindow and return the LV2UI handle
static LV2UI_Handle instantiate(const struct LV2UI_Descriptor * descriptor,
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
    ui->db_zero = 20.*log10(0.0000003); // -130db

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
    ui->win = create_window(&ui->main, (Window)ui->parentXwindow, 0, 0, 710, 260);
    ui->win->parent_struct = ui;
    ui->win->label = "GxMultiBandEcho";
    widget_get_png(ui->win, LDVAR(guitarix_orange_png));
    ui->screw = surface_get_png(ui->win, ui->screw, LDVAR(screw_png));
    // connect the expose func
    ui->win->func.expose_callback = draw_window;

    int iw=0;
    int w_pos = 60;
    int port = (PortIndex) V1;
    for (;iw<5;iw++) {
        ui->meter_widget[iw] = add_vmeter(ui->win, "Meter", false, w_pos, 40, 20, 145);
        ui->meter_widget[iw]->parent_struct = ui;
        ui->meter_widget[iw]->data = port;
        port +=1;
        w_pos +=100;
    }

    iw=0;
    w_pos = 85;
    port = (PortIndex) PERCENT1;
    for (;iw<5;iw++) {
        ui->widget[iw] = add_my_knob(ui->widget[iw], (PortIndex)port,"Amount", ui,w_pos, 40, 60, 70);
        set_adjustment(ui->widget[iw]->adj,0.0, 0.0, 0.0, 100.0, 1.0, CL_CONTINUOS);
        //adj_set_scale(ui->widget[iw]->adj, 2.0);
        port +=1;
        w_pos +=100;
    }

    w_pos = 85;
    port = (PortIndex) TIME1;
    for (;iw<10;iw++) {
        ui->widget[iw] = add_my_knob(ui->widget[iw], (PortIndex)port,"BPM", ui,w_pos, 115, 60, 70);
        set_adjustment(ui->widget[iw]->adj,120.0, 120.0, 24.0, 360.5, 1.0, CL_CONTINUOS);
        adj_set_scale(ui->widget[iw]->adj, 2.0);
        port +=1;
        w_pos +=100;
    }

    ui->widget[10] = add_my_slider(ui->widget[10], CROSSOVER_B1_B2,"Crossover ",ui, 60,205, 480, 20);

    // map all widgets into the toplevel Widget_t
    widget_show_all(ui->win);
    // set the widget pointer to the X11 Window from the toplevel Widget_t
    *widget = (void*)ui->win->widget;
    // request to resize the parentXwindow to the size of the toplevel Widget_t
    if (resize){
        ui->resize = resize;
        resize->ui_resize(resize->handle, 710, 260);
    }
    // store pointer to the host controller
    ui->controller = controller;
    // store pointer to the host write function
    ui->write_function = write_function;
    
    return (LV2UI_Handle)ui;
}

// map power to db for meter widgets
static void set_meter_value(X11_UI* ui, Widget_t*w, float value) {
    float new_val = power2db(w,20.*log10(max(ui->db_zero,value)));
    check_value_changed(w->adj,&new_val);
}

// cleanup after usage
static void cleanup(LV2UI_Handle handle) {
    X11_UI* ui = (X11_UI*)handle;
    cairo_surface_destroy(ui->screw);
    delete_adjustment(ui->adj[0]);
    delete_adjustment(ui->adj[1]);
    delete_adjustment(ui->adj[2]);
    ui->widget[10]->adj_x = NULL;
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
    if (port_index == V1) set_meter_value(ui,ui->meter_widget[0],value);
    else if (port_index == V2) set_meter_value(ui,ui->meter_widget[1],value);
    else if (port_index == V3) set_meter_value(ui,ui->meter_widget[2],value);
    else if (port_index == V4) set_meter_value(ui,ui->meter_widget[3],value);
    else if (port_index == V5) set_meter_value(ui,ui->meter_widget[4],value);
    if (port_index >= CROSSOVER_B1_B2 && port_index <= CROSSOVER_B4_B5) {
        check_multi_controller(ui, port_index, value);
        ui->block_event = (int)port_index;
    }
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

