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

/*---------------------------------------------------------------------
-----------------------------------------------------------------------    
                define PortIndex and plugin uri
-----------------------------------------------------------------------
----------------------------------------------------------------------*/

#include "gx_graphiceq.h"

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
    Widget_t *meter_widget[CONTROLS];
    float db_zero;
} X11_UI_Private_t;

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

    cairo_pattern_t* pat;

    pat = cairo_pattern_create_linear (0, 30, 0, w->scale.init_height-60.0);
    cairo_pattern_add_color_stop_rgba (pat, 0,  0.25, 0.25, 0.25, 1.0);
    cairo_pattern_add_color_stop_rgba (pat, 0.25,  0.2, 0.2, 0.2, 1.0);
    cairo_pattern_add_color_stop_rgba (pat, 0.5,  0.15, 0.15, 0.15, 1.0);
    cairo_pattern_add_color_stop_rgba (pat, 0.75,  0.1, 0.1, 0.1, 1.0);
    cairo_pattern_add_color_stop_rgba (pat, 1,  0.05, 0.05, 0.05, 1.0);


    cairo_set_source (w->crb, pat);
    cairo_rectangle(w->crb, 50.0, 30.0,w->scale.init_width*0.3,w->scale.init_height-60.0);
    cairo_set_line_width(w->crb,2);
    cairo_stroke(w->crb);
    cairo_pattern_destroy (pat);
    pat = NULL;
    pat = cairo_pattern_create_linear (0, 38, 0, w->scale.init_height-76.0);
    cairo_pattern_add_color_stop_rgba (pat, 1,  0.25, 0.25, 0.25, 1.0);
    cairo_pattern_add_color_stop_rgba (pat, 0.75,  0.2, 0.2, 0.2, 1.0);
    cairo_pattern_add_color_stop_rgba (pat, 0.5,  0.15, 0.15, 0.15, 1.0);
    cairo_pattern_add_color_stop_rgba (pat, 0.25,  0.1, 0.1, 0.1, 1.0);
    cairo_pattern_add_color_stop_rgba (pat, 0,  0.05, 0.05, 0.05, 1.0);

    cairo_set_source (w->crb, pat);
    cairo_rectangle(w->crb, 59.0, 38.0,w->scale.init_width*0.28,w->scale.init_height-76.0);
    cairo_stroke(w->crb);
    cairo_pattern_destroy (pat);
    pat = NULL;

    widget_reset_scale(w);
}

void plugin_value_changed(X11_UI *ui, Widget_t *w, PortIndex index) {
    // do special stuff when needed
}

void plugin_set_window_size(int *w,int *h,const char * plugin_uri) {
    (*w) = 800; //initial widht of main window
    (*h) = 230; //initial heigth of main window
}

const char* plugin_set_name() {
    return "GxGraphicEQ"; //plugin name to display on UI
}

// shortcut to create knobs with portindex binding
Widget_t* add_my_slider(Widget_t *w, PortIndex index, const char * label,
                                X11_UI* ui, int x, int y, int width, int height) {
    w = add_vslider(ui->win, label, x, y, width, height);
    w->parent_struct = ui;
    w->data = index;
    w->func.value_changed_callback = value_changed;
    return w;
}

void plugin_create_controller_widgets(X11_UI *ui, const char * plugin_uri) {
    X11_UI_Private_t *ps =(X11_UI_Private_t*)malloc(sizeof(X11_UI_Private_t));;
    ui->private_ptr = (void*)ps;
    ps->db_zero = 20.*log10(0.0000003); // -130db
    ui->win->func.expose_callback = draw_my_window;

    int iw=0;
    int w_pos = 60;
    int port = (PortIndex) V1;
    for (;iw<CONTROLS;iw++) {
        ps->meter_widget[iw] = add_vmeter(ui->win, "Meter", false, w_pos, 40, 20, 150);
        ps->meter_widget[iw]->scale.gravity = CENTER;
        ps->meter_widget[iw]->parent_struct = ui;
        ps->meter_widget[iw]->data = port;
        port +=1;
        w_pos +=20;
    }


    iw=0;
    w_pos = 310;
    port = (PortIndex) G1;
    const char* frequencys[] = {">31", "62", "125", "250", "500", "1k", "2k", "4k", "8k", "16k", "<"};
    for (;iw<CONTROLS;iw++) {
        ui->widget[iw] = add_my_slider(ui->widget[iw], (PortIndex)port,frequencys[iw], ui,w_pos, 40, 40, 160);
        ui->widget[iw]->scale.gravity = CENTER;
        adj_set_log_scale(ui->widget[iw]->adj, 30.0);
        set_adjustment(ui->widget[iw]->adj,0.0, 0.0, -30.0, 20.0, 0.01, CL_LOGSCALE);
        port +=1;
        w_pos +=40;
    }

    iw = 0;
    for (;iw<CONTROLS;iw++) {
        cairo_select_font_face (ui->widget[iw]->crb, "Roboto", CAIRO_FONT_SLANT_NORMAL,
                               CAIRO_FONT_WEIGHT_BOLD);
    }
}

void plugin_cleanup(X11_UI *ui) {
    X11_UI_Private_t *ps = (X11_UI_Private_t*)ui->private_ptr;
    int iw=0;
    for (;iw<CONTROLS;iw++) {
        destroy_widget(ps->meter_widget[iw],&ui->main);
    }
    free(ps);
    ui->private_ptr = NULL;
}

// map power to db for meter widgets
static void set_meter_value(X11_UI* ui, Widget_t*w, float value) {
    X11_UI_Private_t *ps = (X11_UI_Private_t*)ui->private_ptr;
    float new_val = power2db(w,20.*log10(max(ps->db_zero,value)));
    check_value_changed(w->adj,&new_val);
}

void plugin_port_event(LV2UI_Handle handle, uint32_t port_index,
                        uint32_t buffer_size, uint32_t format,
                        const void * buffer) {
    if(port_index >= (uint32_t)V1 && port_index <= (uint32_t)V11) {
        X11_UI* ui = (X11_UI*)handle;
        X11_UI_Private_t *ps = (X11_UI_Private_t*)ui->private_ptr;
        float value = *(float*)buffer;
        set_meter_value(ui, ps->meter_widget[port_index-11], value);
    }
}
