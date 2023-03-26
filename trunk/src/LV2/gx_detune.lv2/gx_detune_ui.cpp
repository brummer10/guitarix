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

#include "xslider_private.h"

/*---------------------------------------------------------------------
-----------------------------------------------------------------------    
                define PortIndex and plugin uri
-----------------------------------------------------------------------
----------------------------------------------------------------------*/

#include "gx_detune.h"

/*---------------------------------------------------------------------
-----------------------------------------------------------------------    
                define controller numbers
-----------------------------------------------------------------------
----------------------------------------------------------------------*/

#define CONTROLS 11

/*---------------------------------------------------------------------
-----------------------------------------------------------------------    
                include the LV2 interface
-----------------------------------------------------------------------
----------------------------------------------------------------------*/

#include "lv2_plugin.cc"

/*---------------------------------------------------------------------
-----------------------------------------------------------------------    
                define the plugin settings
-----------------------------------------------------------------------
----------------------------------------------------------------------*/

typedef struct {
    float latency;
} X11_UI_Private_t;

// setup a color theme
static void set_my_theme(Xputty *main) {
    main->color_scheme->normal = (Colors) {
         /* cairo    / r  / g  / b  / a  /  */
        /*fg */       { 0.45, 0.45, 0.45, 1.0},
        /*bg */       { 0.10, 0.19, 0.33, 1.00},
        /*base */     { 0.10, 0.19, 0.33, 1.00},
        /*text */     { 0.45, 0.45, 0.45, 1.0},
        /*shadow */   { 0.0, 0.0, 0.0, 0.2},
        /*frame */    { 0.0, 0.0, 0.0, 1.0},
        /*light */    { 0.1, 0.1, 0.1, 1.0}
    };

    main->color_scheme->prelight = (Colors) {
        /*fg */       { 1.0, 1.0, 1.0, 1.0},
        /*bg */       { 0.16, 0.19, 0.27, 1.00},
        /*base */     { 0.16, 0.19, 0.27, 1.00},
        /*text */     { 0.7, 0.7, 0.7, 1.0},
        /*shadow */   { 0.1, 0.1, 0.1, 0.4},
        /*frame */    { 0.3, 0.3, 0.3, 1.0},
        /*light */    { 0.3, 0.3, 0.3, 1.0}
    };

    main->color_scheme->selected = (Colors) {
        /*fg */       { 0.9, 0.9, 0.9, 1.0},
        /*bg */       { 0.16, 0.19, 0.27, 1.00},
        /*base */     { 0.16, 0.19, 0.27, 1.00},
        /*text */     { 1.0, 1.0, 1.0, 1.0},
        /*shadow */   { 0.18, 0.18, 0.18, 0.2},
        /*frame */    { 0.18, 0.18, 0.18, 1.0},
        /*light */    { 0.18, 0.18, 0.18, 1.0}
    };
}

static void set_my_knob_color(KnobColors* kp) {
    *kp = (KnobColors) {
         /* cairo    / r  / g  / b  / a  /  */
        /*p1f */       { 0.349, 0.313, 0.243, 1.0},
        /*p2f */       { 0.349, 0.235, 0.011, 1.0},
        /*p3f */       { 0.15, 0.15, 0.15, 1.0},
        /*p4f */       { 0.1, 0.1, 0.1, 1.00},
        /*p5f */       { 0.05, 0.05, 0.05, 1.0},
        /*p1k */       { 0.349, 0.213, 0.143, 1.0},
        /*p2k */       { 0.349, 0.235, 0.011, 1.0},
        /*p3k */       { 0.15, 0.15, 0.15, 1.0},
        /*p4k */       { 0.1, 0.1, 0.1, 1.00},
        /*p5k */       { 0.05, 0.05, 0.05, 1.0},
    };
}

// draw the window
static void draw_my_window(void *w_, void* user_data) {
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
    cairo_set_source_rgb (w->crb,0.45, 0.45, 0.45);
    float font_size = min(20.0,((w->height/2.2 < (w->width*0.5)/3) ? w->height/2.2 : (w->width*0.5)/3));
    cairo_set_font_size (w->crb, font_size);
    cairo_text_extents(w->crb,w->label , &extents);
    double tw = extents.width/2.0;

    widget_set_scale(w);
    cairo_move_to (w->crb, 390-tw, 170 );
    cairo_show_text(w->crb, w->label);
    cairo_new_path (w->crb);
    if (strlen(w->input_label)) {
    cairo_set_font_size (w->crb, 11);
        cairo_move_to (w->crb, 140, 160 );
        cairo_show_text(w->crb, w->input_label);
        cairo_new_path (w->crb);
    }
    
    cairo_scale (w->crb, 0.95, 0.95);
    cairo_set_source_surface (w->crb, w->image,680,10);
    cairo_paint (w->crb);
    cairo_scale (w->crb, 1.05, 1.05);
    widget_reset_scale(w);
}

static void draw_my_vslider(void *w_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    Metrics_t m;
    int width, height;
    os_get_window_metrics(w, &m);
    width = m.width-2;
    height = m.height-2;
    float center = (float)width/2;
    float upcenter = (float)width;
    
    if (!m.visible) return;

    float sliderstate = adj_get_state(w->adj_y);

    _pattern_vslider(w, get_color_state(w), width);
    cairo_move_to (w->crb, center, center);
    cairo_line_to(w->crb,center,height-center-10);
    cairo_set_line_cap (w->crb,CAIRO_LINE_CAP_ROUND);
    cairo_set_line_width(w->crb,center);
    cairo_stroke(w->crb);

    use_shadow_color_scheme(w, get_color_state(w));
    cairo_move_to (w->crb, center, center);
    cairo_line_to(w->crb,center,height-center-10);
    cairo_set_line_width(w->crb,center/10);
    cairo_stroke(w->crb);

    use_shadow_color_scheme(w, get_color_state(w));
    cairo_arc(w->crb,center, (height-center-10) -
        ((height-10-upcenter) * sliderstate), center/2, 0, 2 * M_PI );
    cairo_fill_preserve(w->crb);
    cairo_set_line_width(w->crb,1);
    cairo_stroke(w->crb);


    //use_bg_color_scheme(w, get_color_state(w));

    cairo_set_source_rgb (w->crb, 0.1, 0.1, 0.1); 
    cairo_arc(w->crb,center, (height-center-10) -
        ((height-10-upcenter) * sliderstate), center/3, 0, 2 * M_PI );
    cairo_fill_preserve(w->crb);
    cairo_set_source_rgb (w->crb, 0.349, 0.235, 0.011);
    cairo_set_line_width(w->crb,center/15);
    cairo_stroke(w->crb);
    cairo_new_path (w->crb);

    cairo_text_extents_t extents;


    use_text_color_scheme(w, get_color_state(w));
    cairo_set_font_size (w->crb, center/2.1);
    cairo_text_extents(w->crb,w->label , &extents);

    cairo_move_to (w->crb, center-extents.width/2, height-center/2.1);
    cairo_show_text(w->crb, w->label);
    cairo_new_path (w->crb);

    char s[64];
    const char* format[] = {"%.1f", "%.2f", "%.3f"};
    if (fabs(w->adj_y->value)>9.99) {
        snprintf(s, 63,"%d",  (int) w->adj->value);
    } else if (fabs(w->adj_y->value)>0.99) {
        snprintf(s, 63, format[1-1], w->adj->value);
    } else {
        snprintf(s, 63, format[2-1], w->adj->value);
    }
    cairo_text_extents(w->crb,s , &extents);
    cairo_move_to (w->crb, center-extents.width/2, extents.height );
    cairo_show_text(w->crb, s);
    cairo_new_path (w->crb);
}

void plugin_value_changed(X11_UI *ui, Widget_t *w, PortIndex index) {
    // do special stuff when needed
}

// shortcut to create knobs with portindex binding
Widget_t* add_my_slider(Widget_t *w, PortIndex index, const char * label,
                                X11_UI* ui, int x, int y, int width, int height) {
    w = add_vslider(ui->win, label, x, y, width, height);
    w->func.expose_callback = draw_my_vslider;    
    w->parent_struct = ui;
    w->data = index;
    w->func.value_changed_callback = value_changed;
    return w;
}

void plugin_set_window_size(int *w,int *h,const char * plugin_uri) {
    (*w) = 840; //set initial width of main window
    (*h) = 180; //set initial height of main window
}

const char* plugin_set_name() {
    return "GxDetune"; //set plugin name to display on UI
}

void plugin_create_controller_widgets(X11_UI *ui, const char * plugin_uri) {
    X11_UI_Private_t *ps =(X11_UI_Private_t*)malloc(sizeof(X11_UI_Private_t));;
    ui->private_ptr = (void*)ps;
    ps->latency = 0.0;
    set_my_theme(&ui->main);
    set_my_knob_color(ui->kp);
    widget_get_png(ui->win, LDVAR(guitarix_png));
    ui->win->func.expose_callback = draw_my_window;
    // create all controllers needed
    ui->widget[0] = add_my_knob(ui->widget[0], DETUNE,"Detune", ui,310, 25, 100, 125);
    set_adjustment(ui->widget[0]->adj,0.0, 0.0, -12.0, 12.0, 0.1, CL_CONTINUOS);

    ui->widget[1] = add_my_knob(ui->widget[1], WET,"Wet", ui,420, 35, 80, 105);
    set_adjustment(ui->widget[1]->adj,50.0, 50.0, 0.0, 100.0, 1.0, CL_CONTINUOS);

    ui->widget[2] = add_my_knob(ui->widget[2], DRY,"Dry", ui,510, 35, 80, 105);
    set_adjustment(ui->widget[2]->adj,50.0, 50.0, 0.0, 100.0, 1.0, CL_CONTINUOS);

    ui->widget[3] = add_my_slider(ui->widget[3], LOW,"Low", ui,610, 35, 40, 130);
    set_adjustment(ui->widget[3]->adj,1.0, 1.0, 0.0, 2.0, 0.01, CL_CONTINUOS);

    ui->widget[4] = add_my_slider(ui->widget[4], MIDDLELOW,"Lo Mid", ui,650, 35, 40, 130);
    set_adjustment(ui->widget[4]->adj,1.0, 1.0, 0.0, 2.0, 0.01, CL_CONTINUOS);

    ui->widget[5] = add_my_slider(ui->widget[5], MIDDLETREBLE,"Hi MID", ui,690, 35, 40, 130);
    set_adjustment(ui->widget[5]->adj,1.0, 1.0, 0.0, 2.0, 0.01, CL_CONTINUOS);

    ui->widget[6] = add_my_slider(ui->widget[6], TREBLE,"High", ui,730, 35, 40, 130);
    set_adjustment(ui->widget[6]->adj,1.0, 1.0, 0.0, 2.0, 0.01, CL_CONTINUOS);

    const char* model[] = {"no shift","octave up","octave down"};
    size_t len = sizeof(model) / sizeof(model[0]);
    ui->widget[7] = add_my_combobox(ui->widget[7], OCTAVE, "Octave", model, len, 0, ui, 140, 30, 140, 30);


    const char* comp[] = {"delay ","compensate"};
    len = sizeof(comp) / sizeof(comp[0]);
    ui->widget[8] = add_my_combobox(ui->widget[8], COMPENSATE, "Compensate", comp, len, 0, ui, 140, 70, 140, 30);

    const char* lat[] = {"high quality","low quality","realtime"};
    len = sizeof(lat) / sizeof(lat[0]);
    ui->widget[9] = add_my_combobox(ui->widget[9], LATENCY, "Latency", lat, len, 0, ui, 140, 110, 140, 30);

    ui->widget[10] = add_on_off_button(ui->win, "Power", 50, 50, 40, 80);
    ui->widget[10]->scale.gravity = ASPECT;
    ui->widget[10]->data = BYPASS;
    ui->widget[10]->parent_struct = ui;
    ui->widget[10]->func.value_changed_callback = value_changed;
}

void plugin_cleanup(X11_UI *ui) {
    X11_UI_Private_t *ps = (X11_UI_Private_t*)ui->private_ptr;
    free(ps);
    ui->private_ptr = NULL;
}

void plugin_port_event(LV2UI_Handle handle, uint32_t port_index,
                        uint32_t buffer_size, uint32_t format,
                        const void * buffer) {
    X11_UI* ui = (X11_UI*)handle;
    if (port_index == LATENCYREPORT) {
        X11_UI_Private_t *ps = (X11_UI_Private_t*)ui->private_ptr;
        float value = *(float*)buffer;
        if (fabs(ps->latency-value)>0.9) {
            memset(ui->win->input_label, 0, 32 * (sizeof ui->win->input_label[0]));
            snprintf(ui->win->input_label, 32, "Latency: %.0f", value);
            expose_widget(ui->win);
            ps->latency = value;
        }
    } else if (port_index == (uint32_t) BYPASS) {
        ui->block_event = -1;
    }
}

