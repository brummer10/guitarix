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

#include "gxredeye.h"

/*---------------------------------------------------------------------
-----------------------------------------------------------------------    
                define controller numbers
-----------------------------------------------------------------------
----------------------------------------------------------------------*/

#define CONTROLS 7

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
    cairo_surface_t *logo;
} X11_UI_Private_t;

// setup a color theme
static void set_chump_theme(Xputty *main) {
    main->color_scheme->normal = (Colors) {
         /* cairo    / r  / g  / b  / a  /  */
        .fg =       { 0.85, 0.85, 0.85, 1.00},
        .bg =       { 0.1, 0.1, 0.1, 1.0},
        .base =     { 0.1, 0.1, 0.1, 1.0},
        .text =     { 0.05, 0.05, 0.05, 1.00},
        .shadow =   { 0.1, 0.1, 0.1, 0.2},
        .frame =    { 0.0, 0.0, 0.0, 1.0},
        .light =    { 0.1, 0.1, 0.1, 1.0}
    };

    main->color_scheme->prelight = (Colors) {
        .fg =       { 1.0, 1.0, 1.0, 1.0},
        .bg =       { 0.25, 0.25, 0.25, 1.0},
        .base =     { 0.2, 0.2, 0.2, 1.0},
        .text =     { 0.07, 0.07, 0.07, 1.0},
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

// setup a color theme
static void set_champ_theme(Xputty *main) {
    main->color_scheme->normal = (Colors) {
         /* cairo    / r  / g  / b  / a  /  */
        .text =     { 0.75, 0.75, 0.75, 1.00}
    };

    main->color_scheme->prelight = (Colors) {
        .text =     { 0.9, 0.9, 0.9, 1.0}
    };

    main->color_scheme->selected = (Colors) {
        .text =     { 0.9, 0.9, 0.9, 1.0}
    };

    main->color_scheme->active = (Colors) {
        .text =     { 0.75, 0.75, 0.75, 1.0}
    };
}

// draw the window
static void draw_my_window(void *w_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    X11_UI* ui = (X11_UI*)w->parent_struct;
    X11_UI_Private_t *ps = (X11_UI_Private_t*)ui->private_ptr;
    widget_set_scale(w);
    cairo_set_source_surface (w->crb, w->image,0,0);
    cairo_paint (w->crb);

    cairo_set_source_surface (w->crb, ps->logo,60,40);
    cairo_paint (w->crb);

    widget_reset_scale(w);
}

void plugin_value_changed(X11_UI *ui, Widget_t *w, PortIndex index) {
    // do special stuff when needed
}

void plugin_set_window_size(int *w,int *h,const char * plugin_uri) {
    if(strcmp(GXPLUGIN_URI "#chump", plugin_uri) == 0 ||
      strcmp(GXPLUGIN_URI "#bigchump", plugin_uri) == 0) {
        (*w) = 664; //initial widht of main window
        (*h) = 301; //initial heigth of main window
    } else if(strcmp(GXPLUGIN_URI "#vibrochump", plugin_uri) == 0){
        (*w) = 750; //initial widht of main window
        (*h) = 280; //initial heigth of main window
    }
}

const char* plugin_set_name() {
    return "GxRedeye Chump"; //plugin name to display on UI
}

void plugin_create_controller_widgets(X11_UI *ui, const char * plugin_uri) {
    if(strcmp(GXPLUGIN_URI "#chump", plugin_uri) == 0 ||
      strcmp(GXPLUGIN_URI "#bigchump", plugin_uri) == 0) {
        widget_get_scaled_png(ui->win, LDVAR(chump_png));
    } else if(strcmp(GXPLUGIN_URI "#vibrochump", plugin_uri) == 0){
        widget_get_scaled_png(ui->win, LDVAR(champ_png));
    }
    X11_UI_Private_t *ps =(X11_UI_Private_t*)malloc(sizeof(X11_UI_Private_t));;
    ps->logo = surface_get_png(ui->win,ps->logo,LDVAR(redeyelogo_png));
    ui->private_ptr = (void*)ps;
    ui->win->func.expose_callback = draw_my_window;


    if(strcmp(GXPLUGIN_URI "#chump", plugin_uri) == 0 ||
      strcmp(GXPLUGIN_URI "#bigchump", plugin_uri) == 0) {

        set_chump_theme(&ui->main);
        ui->widget[0] = add_my_image_knob(ui->widget[0], GAIN,"Gain", ui,180, 210, 60, 70);
        set_adjustment(ui->widget[0]->adj,0.5, 0.5, 0.0, 1.0, 0.01, CL_CONTINUOS);
        widget_get_png(ui->widget[0], LDVAR(chumpknob_png));

        ui->widget[1] = add_my_image_knob(ui->widget[1], TONE,"Tone", ui,260, 210, 60, 70);
        set_adjustment(ui->widget[1]->adj,0.5, 0.5, 0.0, 1.0, 0.01, CL_CONTINUOS);
        widget_get_surface_ptr(ui->widget[1], ui->widget[0]);

        ui->widget[2] = add_my_image_knob(ui->widget[2], VOLUME,"Volume", ui,340, 210, 60, 70);
        set_adjustment(ui->widget[2]->adj,0.5, 0.5, 0.0, 1.0, 0.01, CL_CONTINUOS);
        widget_get_surface_ptr(ui->widget[2], ui->widget[0]);

        ui->widget[3] = add_my_switch_image(ui->widget[3], FEEDBACK, "Feedback", ui,420, 212, 60, 70);
        widget_get_png(ui->widget[3], LDVAR(switch_png));
    } else if(strcmp(GXPLUGIN_URI "#vibrochump", plugin_uri) == 0){

        set_champ_theme(&ui->main);
        ui->widget[0] = add_my_image_knob(ui->widget[0], GAIN,"Gain", ui,80, 180, 60, 70);
        set_adjustment(ui->widget[0]->adj,0.5, 0.5, 0.0, 1.0, 0.01, CL_CONTINUOS);
        widget_get_png(ui->widget[0], LDVAR(chumpknob_png));

        ui->widget[1] = add_my_image_knob(ui->widget[1], TONE,"Tone", ui,170, 180, 60, 70);
        set_adjustment(ui->widget[1]->adj,0.5, 0.5, 0.0, 1.0, 0.01, CL_CONTINUOS);
        widget_get_surface_ptr(ui->widget[1], ui->widget[0]);

        ui->widget[2] = add_my_image_knob(ui->widget[2], VOLUME,"Volume", ui,260, 180, 60, 70);
        set_adjustment(ui->widget[2]->adj,0.5, 0.5, 0.0, 1.0, 0.01, CL_CONTINUOS);
        widget_get_surface_ptr(ui->widget[2], ui->widget[0]);

        ui->widget[3] = add_my_switch_image(ui->widget[3], VIBE, "Vibe", ui,350, 182, 60, 70);
        widget_get_png(ui->widget[3], LDVAR(switch_png));

        ui->widget[4] = add_my_image_knob(ui->widget[4], SPEED,"Speed", ui,440, 180, 60, 70);
        set_adjustment(ui->widget[4]->adj,5.0, 5.0, 0.1, 10.0, 0.1, CL_CONTINUOS);
        widget_get_surface_ptr(ui->widget[4], ui->widget[0]);

        ui->widget[5] = add_my_image_knob(ui->widget[5], INTENSITY,"Intensity", ui,530, 180, 60, 70);
        set_adjustment(ui->widget[5]->adj,0.0, 0.0, 0.0, 10.0, 0.1, CL_CONTINUOS);
        widget_get_surface_ptr(ui->widget[5], ui->widget[0]);

        ui->widget[6] = add_my_switch_image(ui->widget[6], SINEWAVE, "Sine", ui,620, 182, 60, 70);
        widget_get_surface_ptr(ui->widget[6], ui->widget[3]);

    }
    int i = 0;
    for (;i<CONTROLS;i++) {
        if(ui->widget[i]) cairo_select_font_face (ui->widget[i]->crb, "Roboto", CAIRO_FONT_SLANT_NORMAL,
                               CAIRO_FONT_WEIGHT_BOLD);
    }
}

void plugin_cleanup(X11_UI *ui) {
    X11_UI_Private_t *ps = (X11_UI_Private_t*)ui->private_ptr;
    cairo_surface_destroy(ps->logo);
    free(ps);
    ui->private_ptr = NULL;
}

void plugin_port_event(LV2UI_Handle handle, uint32_t port_index,
                        uint32_t buffer_size, uint32_t format,
                        const void * buffer) {
}
