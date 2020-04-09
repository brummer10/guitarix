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

#include "gxtuner.h"

/*---------------------------------------------------------------------
-----------------------------------------------------------------------    
                define controller numbers
-----------------------------------------------------------------------
----------------------------------------------------------------------*/

#define CONTROLS 3

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
    cairo_set_font_size (w->crb, w->app->big_font/w->scale.ascale);
    cairo_text_extents(w->crb,w->label , &extents);
    double tw = extents.width/2.0;

    widget_set_scale(w);
    cairo_move_to (w->crb, (w->scale.init_width*0.5)-tw, w->scale.init_height-10 );
    cairo_show_text(w->crb, w->label);
    cairo_new_path (w->crb);
    cairo_scale (w->crb, 0.95, 0.95);
    cairo_set_source_surface (w->crb, w->image,w->scale.init_width-120,25);
    cairo_paint (w->crb);
    cairo_scale (w->crb, 1.05, 1.05);


    cairo_pattern_t* pat;

    pat = cairo_pattern_create_linear (-1.0, 53, 0, w->scale.init_height-106.0);
    cairo_pattern_add_color_stop_rgba (pat, 0,  0.25, 0.25, 0.25, 1.0);
    cairo_pattern_add_color_stop_rgba (pat, 0.25,  0.2, 0.2, 0.2, 1.0);
    cairo_pattern_add_color_stop_rgba (pat, 0.5,  0.15, 0.15, 0.15, 1.0);
    cairo_pattern_add_color_stop_rgba (pat, 0.75,  0.1, 0.1, 0.1, 1.0);
    cairo_pattern_add_color_stop_rgba (pat, 1,  0.05, 0.05, 0.05, 1.0);

    cairo_set_source (w->crb, pat);
    cairo_rectangle(w->crb, 53.0, 53.0,w->scale.init_width*0.8,w->scale.init_height-106.0);
    cairo_set_line_width(w->crb,2);
    cairo_stroke(w->crb);
    cairo_pattern_destroy (pat);
    pat = NULL;
    pat = cairo_pattern_create_linear (-1.0, 58, 0, w->scale.init_height-116.0);
    cairo_pattern_add_color_stop_rgba (pat, 1,  0.25, 0.25, 0.25, 1.0);
    cairo_pattern_add_color_stop_rgba (pat, 0.75,  0.2, 0.2, 0.2, 1.0);
    cairo_pattern_add_color_stop_rgba (pat, 0.5,  0.15, 0.15, 0.15, 1.0);
    cairo_pattern_add_color_stop_rgba (pat, 0.25,  0.1, 0.1, 0.1, 1.0);
    cairo_pattern_add_color_stop_rgba (pat, 0,  0.05, 0.05, 0.05, 1.0);

    cairo_set_source (w->crb, pat);
    cairo_rectangle(w->crb, 58.0, 58.0,w->scale.init_width*0.78,w->scale.init_height-116.0);
    cairo_stroke(w->crb);
    cairo_pattern_destroy (pat);
    pat = NULL;

    widget_reset_scale(w);
}

void plugin_value_changed(X11_UI *ui, Widget_t *w, PortIndex index) {
    // do special stuff when needed
    switch (index) {
        case (REFFREQ):
            tuner_set_ref_freq(ui->widget[0],adj_get_value(ui->widget[2]->adj));
        break;
        case (TEMPERAMENT):
            tuner_set_temperament(ui->widget[0],adj_get_value(ui->widget[1]->adj));
        break;
        default:
        break;
    }
}

void plugin_set_window_size(int *w,int *h,const char * plugin_uri) {
    (*w) = 520; //initial widht of main window
    (*h) = 200; //initial heigth of main window
}

const char* plugin_set_name() {
    return "GxTuner"; //plugin name to display on UI
}

void plugin_create_controller_widgets(X11_UI *ui, const char * plugin_uri) {
    ui->win->func.expose_callback = draw_my_window;

    ui->widget[0] = add_tuner(ui->win, "Freq", 60, 60, 400, 80);
    //ui->widget[0]->parent_struct = ui;
    ui->widget[0]->data = FREQ;
    //ui->widget[0]->func.value_changed_callback = value_changed;

    const char* model[] = {"12-TET","19-TET","24-TET", "31-TET", "53-TET"};
    size_t len = sizeof(model) / sizeof(model[0]);
    ui->widget[1] = add_my_combobox(ui->widget[1], TEMPERAMENT, "Mode", model, len, 0, ui, 130, 20, 90, 25);
    ui->widget[1]->func.value_changed_callback = value_changed;
    tuner_set_temperament(ui->widget[0],adj_get_value(ui->widget[1]->adj));

    ui->widget[2] = add_valuedisplay(ui->win, "RefFreq", 60, 20, 50, 25);
    set_adjustment(ui->widget[2]->adj,440.0, 440.0, 427.0, 453.0, 0.1, CL_CONTINUOS);
    ui->widget[2]->parent_struct = ui;
    ui->widget[2]->data = REFFREQ;
    ui->widget[2]->func.value_changed_callback = value_changed;
    tuner_set_ref_freq(ui->widget[0],adj_get_value(ui->widget[2]->adj));
}

void plugin_cleanup(X11_UI *ui) {
}

void plugin_port_event(LV2UI_Handle handle, uint32_t port_index,
                        uint32_t buffer_size, uint32_t format,
                        const void * buffer) {
}
