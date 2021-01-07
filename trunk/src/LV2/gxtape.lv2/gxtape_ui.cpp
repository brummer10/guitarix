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

#include "gxtape.h"

/*---------------------------------------------------------------------
-----------------------------------------------------------------------    
                define controller numbers
-----------------------------------------------------------------------
----------------------------------------------------------------------*/

#define CONTROLS 10

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

// setup a color theme
static void set_my_theme(Xputty *main) {
    main->color_scheme->normal = (Colors) {
         /* cairo    / r  / g  / b  / a  /  */
        .fg =       { 0.85, 0.85, 0.85, 1.00},
        .bg =       { 0.1, 0.1, 0.1, 1.0},
        .base =     { 0.1, 0.1, 0.1, 1.0},
        .text =     { 0.1, 0.1, 0.1, 1.00},
        .shadow =   { 0.1, 0.1, 0.1, 0.2},
        .frame =    { 0.0, 0.0, 0.0, 1.0},
        .light =    { 0.1, 0.1, 0.1, 1.0}
    };

    main->color_scheme->prelight = (Colors) {
        .fg =       { 1.0, 1.0, 1.0, 1.0},
        .bg =       { 0.25, 0.25, 0.25, 1.0},
        .base =     { 0.2, 0.2, 0.2, 1.0},
        .text =     { 0.0, 0.0, 0.0, 1.0},
        .shadow =   { 0.1, 0.1, 0.1, 0.4},
        .frame =    { 0.3, 0.3, 0.3, 1.0},
        .light =    { 0.3, 0.3, 0.3, 1.0}
    };

    main->color_scheme->selected = (Colors) {
        .fg =       { 0.9, 0.9, 0.9, 1.0},
        .bg =       { 0.2, 0.2, 0.2, 1.0},
        .base =     { 0.1, 0.1, 0.1, 1.0},
        .text =     { 0.0, 0.0, 0.0, 1.0},
        .shadow =   { 0.18, 0.18, 0.18, 0.2},
        .frame =    { 0.18, 0.18, 0.18, 1.0},
        .light =    { 0.18, 0.18, 0.28, 1.0}
    };

    main->color_scheme->active = (Colors) {
        .fg =       { 0.9, 0.9, 0.9, 1.0},
        .bg =       { 0.2, 0.2, 0.2, 1.0},
        .base =     { 0.1, 0.1, 0.1, 1.0},
        .text =     { 0.0, 0.0, 0.0, 1.0},
        .shadow =   { 0.18, 0.18, 0.18, 0.2},
        .frame =    { 0.18, 0.18, 0.18, 1.0},
        .light =    { 0.18, 0.18, 0.28, 1.0}
    };
}

// draw the window
static void draw_my_window(void *w_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    widget_set_scale(w);
    cairo_set_source_surface (w->crb, w->image,0,0);
    cairo_paint (w->crb);

    cairo_select_font_face (w->crb, "Roboto", CAIRO_FONT_SLANT_NORMAL,
                               CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size (w->crb, 12);
    use_text_color_scheme(w, get_color_state(w));
    cairo_move_to (w->crb, w->scale.init_width*0.18, w->scale.init_height*0.65 );
    cairo_show_text(w->crb, "WOW");
    cairo_new_path (w->crb);
    cairo_move_to (w->crb, w->scale.init_width*0.45, w->scale.init_height*0.65 );
    cairo_show_text(w->crb, "FLUTTER");
    cairo_new_path (w->crb);
    cairo_move_to (w->crb, w->scale.init_width*0.75, w->scale.init_height*0.65 );
    cairo_show_text(w->crb, "TAPE");
    cairo_new_path (w->crb);

    widget_reset_scale(w);
}

void plugin_value_changed(X11_UI *ui, Widget_t *w, PortIndex index) {
    // do special stuff when needed
}

void plugin_set_window_size(int *w,int *h,const char * plugin_uri) {
    (*w) = 600; //initial width of main window
    (*h) = 300; //initial height of main window
}

const char* plugin_set_name() {
    return "GxTape"; //plugin name to display on UI
}

void plugin_create_controller_widgets(X11_UI *ui, const char * plugin_uri) {
    set_my_theme(&ui->main);
    widget_get_scaled_png(ui->win, LDVAR(tape_png));
    ui->win->func.expose_callback = draw_my_window;

    ui->widget[0] = add_my_switch_image(ui->widget[0], ON, "Off", ui,80, 43, 64, 74);
    widget_get_png(ui->widget[0], LDVAR(switch_png));
    strncpy(ui->widget[0]->input_label,"On",32);

    ui->widget[1] = add_my_image_knob(ui->widget[1], DRIVE,"Input", ui,200, 30, 80, 85);
    set_adjustment(ui->widget[1]->adj,0.5, 0.5, 0.0, 1.0, 0.01, CL_CONTINUOS);
    widget_get_png(ui->widget[1], LDVAR(tapeknob_png));

    ui->widget[2] = add_my_image_knob(ui->widget[2], GAIN,"Output", ui,320, 30, 80, 85);
    set_adjustment(ui->widget[2]->adj,0.5, 0.5, 0.0, 1.0, 0.01, CL_CONTINUOS);
    widget_get_surface_ptr(ui->widget[2], ui->widget[1]);

    ui->widget[3] = add_my_switch_image(ui->widget[3], TAPETYPE, "Machine 2", ui,440, 43, 64, 74);
    widget_get_surface_ptr(ui->widget[3], ui->widget[0]);
    strncpy(ui->widget[3]->input_label,"Machine 1",32);

    ui->widget[4] = add_my_image_knob(ui->widget[4], WOWDEPTH,"Depth", ui,50, 195, 70, 75);
    set_adjustment(ui->widget[4]->adj,0.0, 0.0, 0.0, 0.03, 0.001, CL_CONTINUOS);
    adj_set_scale(ui->widget[4]->adj, 0.5);
    widget_get_surface_ptr(ui->widget[4], ui->widget[1]);

    ui->widget[5] = add_my_image_knob(ui->widget[5], WOWFREQ,"Freq", ui,130, 195, 70, 75);
    set_adjustment(ui->widget[5]->adj,0.0, 0.0, 0.0, 4.0, 0.01, CL_CONTINUOS);
    adj_set_scale(ui->widget[5]->adj, 2.0);
    widget_get_surface_ptr(ui->widget[5], ui->widget[1]);

    ui->widget[6] = add_my_image_knob(ui->widget[6], FLUTTERDEPTH,"Depth", ui,220, 195, 70, 75);
    set_adjustment(ui->widget[6]->adj,0.0, 0.0, 0.0, 0.03, 0.001, CL_CONTINUOS);
    adj_set_scale(ui->widget[6]->adj, 0.5);
    widget_get_surface_ptr(ui->widget[6], ui->widget[1]);

    ui->widget[7] = add_my_image_knob(ui->widget[7], FLUTTERFREQ,"Freq", ui,300, 195, 70, 75);
    set_adjustment(ui->widget[7]->adj,4.0, 4.0, 4.0, 60.0, 0.1, CL_CONTINUOS);
    adj_set_scale(ui->widget[7]->adj, 3.0);
    widget_get_surface_ptr(ui->widget[7], ui->widget[1]);

    ui->widget[8] = add_my_image_knob(ui->widget[8], TAPEHISS,"Noise", ui,390, 195, 70, 75);
    set_adjustment(ui->widget[2]->adj,0.0, 0.0, 0.0, 1.0, 0.01, CL_CONTINUOS);
    widget_get_surface_ptr(ui->widget[8], ui->widget[1]);

    ui->widget[9] = add_my_switch_image(ui->widget[9], SPEED, "15 ips", ui,470, 200, 64, 74);
    widget_get_surface_ptr(ui->widget[9], ui->widget[0]);
    strncpy(ui->widget[9]->input_label,"7.5 ips",32);

    int i = 0;
    for (;i<CONTROLS;i++)
        cairo_select_font_face (ui->widget[i]->crb, "Roboto", CAIRO_FONT_SLANT_NORMAL,
                               CAIRO_FONT_WEIGHT_BOLD);

}

void plugin_cleanup(X11_UI *ui) {
}

void plugin_port_event(LV2UI_Handle handle, uint32_t port_index,
                        uint32_t buffer_size, uint32_t format,
                        const void * buffer) {
}
