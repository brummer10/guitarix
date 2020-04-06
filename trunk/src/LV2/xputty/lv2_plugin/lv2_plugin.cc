/*
 * Copyright (C) 2020 Hermann Meyer, Andreas Degert
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
 * --------------------------------------------------------------------------
 */


#include "lv2_plugin.h"

/*---------------------------------------------------------------------
-----------------------------------------------------------------------    
                the main LV2 handle->XWindow
-----------------------------------------------------------------------
----------------------------------------------------------------------*/

// setup a color theme
static void set_default_theme(Xputty *main) {
    main->color_scheme->normal = (Colors) {
         /* cairo    / r  / g  / b  / a  /  */
        .fg =       { 0.68, 0.44, 0.00, 1.00},
        .bg =       { 0.1, 0.1, 0.1, 1.0},
        .base =     { 0.1, 0.1, 0.1, 1.0},
        .text =     { 0.85, 0.52, 0.00, 1.00},
        .shadow =   { 0.1, 0.1, 0.1, 0.2},
        .frame =    { 0.0, 0.0, 0.0, 1.0},
        .light =    { 0.1, 0.1, 0.2, 1.0}
    };

    main->color_scheme->prelight = (Colors) {
        .fg =       { 1.0, 1.0, 1.0, 1.0},
        .bg =       { 0.25, 0.25, 0.25, 1.0},
        .base =     { 0.2, 0.2, 0.2, 1.0},
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
}

static void set_default_knob_color(KnobColors* kp) {
    *kp = (KnobColors) {
         /* cairo    / r  / g  / b  / a  /  */
        .p1f =       { 0.349, 0.313, 0.243, 1.0},
        .p2f =       { 0.349, 0.235, 0.011, 1.0},
        .p3f =       { 0.15, 0.15, 0.15, 1.0},
        .p4f =       { 0.1, 0.1, 0.1, 1.00},
        .p5f =       { 0.05, 0.05, 0.05, 1.0},
        .p1k =       { 0.349, 0.313, 0.243, 1.0},
        .p2k =       { 0.349, 0.235, 0.011, 1.0},
        .p3k =       { 0.15, 0.15, 0.15, 1.0},
        .p4k =       { 0.1, 0.1, 0.1, 1.00},
        .p5k =       { 0.05, 0.05, 0.05, 1.0},
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
    cairo_move_to (w->crb, (w->scale.init_width*0.5)-tw, w->scale.init_height-10 );
    cairo_show_text(w->crb, w->label);
    cairo_new_path (w->crb);
    cairo_scale (w->crb, 0.95, 0.95);
    cairo_set_source_surface (w->crb, w->image,w->scale.init_width-110,15);
    cairo_paint (w->crb);
    cairo_scale (w->crb, 1.05, 1.05);
    widget_reset_scale(w);
}

// draw the knobs
static void draw_my_knob(void *w_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    X11_UI* ui = (X11_UI*)w->parent_struct;
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
    cairo_pattern_add_color_stop_rgba (pat, 1, ui->kp->p1f[0],ui->kp->p1f[1],ui->kp->p1f[2],ui->kp->p1f[3]);
    cairo_pattern_add_color_stop_rgba (pat, 0.75, ui->kp->p2f[0],ui->kp->p2f[1],ui->kp->p2f[2],ui->kp->p2f[3]);
    cairo_pattern_add_color_stop_rgba (pat, 0.5,  ui->kp->p3f[0],ui->kp->p3f[1],ui->kp->p3f[2],ui->kp->p3f[3]);
    cairo_pattern_add_color_stop_rgba (pat, 0.25,  ui->kp->p4f[0],ui->kp->p4f[1],ui->kp->p4f[2],ui->kp->p4f[3]);
    cairo_pattern_add_color_stop_rgba (pat, 0,  ui->kp->p5f[0],ui->kp->p5f[1],ui->kp->p5f[2],ui->kp->p5f[3]);

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
    cairo_pattern_add_color_stop_rgba (pat, 0, ui->kp->p1k[0],ui->kp->p1k[1],ui->kp->p1k[2],ui->kp->p1k[3]);
    cairo_pattern_add_color_stop_rgba (pat, 0.25, ui->kp->p2k[0],ui->kp->p2k[1],ui->kp->p2k[2],ui->kp->p2k[3]);
    cairo_pattern_add_color_stop_rgba (pat, 0.5, ui->kp->p3k[0],ui->kp->p3k[1],ui->kp->p3k[2],ui->kp->p3k[3]);
    cairo_pattern_add_color_stop_rgba (pat, 0.75, ui->kp->p4k[0],ui->kp->p4k[1],ui->kp->p4k[2],ui->kp->p4k[3]);
    cairo_pattern_add_color_stop_rgba (pat, 1, ui->kp->p5k[0],ui->kp->p5k[1],ui->kp->p5k[2],ui->kp->p5k[3]);

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
        float v = adj_get_value(w->adj);
        char s[64];
        const char* format[] = {"%.1f", "%.2f", "%.3f"};
        snprintf(s, 63, format[2-1], v);
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

    cairo_move_to (w->crb, knobx1-extents.width/2, height-2 );
    cairo_show_text(w->crb, w->label);
    cairo_new_path (w->crb);
}

// if controller value changed send notify to host
static void value_changed(void *w_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    X11_UI* ui = (X11_UI*)w->parent_struct;
    if (ui->block_event != w->data) {
        float v = adj_get_value(w->adj);
        ui->write_function(ui->controller,w->data,sizeof(float),0,&v);
        plugin_value_changed(ui, w, (PortIndex)w->data);
    }
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

// shortcut to create image knobs with portindex binding
Widget_t* add_my_image_knob(Widget_t *w, PortIndex index, const char * label,
                                X11_UI* ui, int x, int y, int width, int height) {
    w = add_image_knob(ui->win, label, x, y, width, height);
    w->parent_struct = ui;
    w->data = index;
    w->func.value_changed_callback = value_changed;
    return w;
}

// shortcut to create image knobs with portindex binding
Widget_t* add_my_value_knob(Widget_t *w, PortIndex index, const char * label,
                                X11_UI* ui, int x, int y, int width, int height) {
    w = add_knob(ui->win, label, x, y, width, height);
    w->parent_struct = ui;
    w->data = index;
    w->func.value_changed_callback = value_changed;
    return w;
}

// shortcut to create image knobs with portindex binding
Widget_t* add_my_switch_image(Widget_t *w, PortIndex index, const char * label,
                                X11_UI* ui, int x, int y, int width, int height) {
    w = add_switch_image_button(ui->win, label, x, y, width, height);
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
    for(; st < len; st++) {
        combobox_add_entry(w,items[st]);
    }
    w->parent_struct = ui;
    w->data = index;
    combobox_set_active_entry(w, active);
    w->func.value_changed_callback = value_changed;
    return w;
}

// init the xwindow and return the LV2UI handle
static LV2UI_Handle instantiate(const struct _LV2UI_Descriptor * descriptor,
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
    ui->private_ptr = NULL;

    int i = 0;
    for(;i<CONTROLS;i++)
        ui->widget[i] = NULL;

    i = 0;
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
    ui->kp = (KnobColors*)malloc(sizeof(KnobColors));
    set_default_knob_color(ui->kp);
    set_default_theme(&ui->main);
    int w = 1;
    int h = 1;
    plugin_set_window_size(&w,&h,plugin_uri);
    // create the toplevel Window on the parentXwindow provided by the host
    ui->win = create_window(&ui->main, (Window)ui->parentXwindow, 0, 0, w, h);
    ui->win->parent_struct = ui;
    ui->win->label = plugin_set_name();
    widget_get_png(ui->win, LDVAR(guitarix_orange_png));
    ui->screw = surface_get_png(ui->win, ui->screw, LDVAR(screw_png));
    // connect the expose func
    ui->win->func.expose_callback = draw_window;
    // create controller widgets
    plugin_create_controller_widgets(ui,plugin_uri);
    // map all widgets into the toplevel Widget_t
    widget_show_all(ui->win);
    // set the widget pointer to the X11 Window from the toplevel Widget_t
    *widget = (void*)ui->win->widget;
    // request to resize the parentXwindow to the size of the toplevel Widget_t
    if (resize){
        ui->resize = resize;
        resize->ui_resize(resize->handle, w, h);
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
    free(ui->kp);
    plugin_cleanup(ui);
    // Xputty free all memory used
    main_quit(&ui->main);
    free(ui->private_ptr);
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
        if (ui->widget[i] && port_index == (uint32_t)ui->widget[i]->data) {
            // prevent event loop between host and plugin
            ui->block_event = (int)port_index;
            // Xputty check if the new value differs from the old one
            // and set new one, when needed
            adj_set_value(ui->widget[i]->adj, value);
        }
   }
   plugin_port_event(handle, port_index, buffer_size, format, buffer);
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

static const LV2UI_Descriptor descriptors[] = {
    {GXPLUGIN_UI_URI,instantiate,cleanup,port_event,extension_data},
#ifdef GXPLUGIN_UI_URI2
    {GXPLUGIN_UI_URI2,instantiate,cleanup,port_event,extension_data},
#endif
};



#ifdef __cplusplus
extern "C" {
#endif
LV2_SYMBOL_EXPORT
const LV2UI_Descriptor* lv2ui_descriptor(uint32_t index) {
    if (index >= sizeof(descriptors) / sizeof(descriptors[0])) {
        return NULL;
    }
    return descriptors + index;
}
#ifdef __cplusplus
}
#endif

