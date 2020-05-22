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

#include "gx_echo.h"

/*---------------------------------------------------------------------
-----------------------------------------------------------------------    
                define controller numbers
-----------------------------------------------------------------------
----------------------------------------------------------------------*/

#define CONTROLS 8 

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
    float mode;
} X11_UI_Private_t;

// setup a color theme
static void set_my_theme(Xputty *main) {
    main->color_scheme->normal = (Colors) {
         /* cairo    / r  / g  / b  / a  /  */
        /*fg */       { 0.45, 0.45, 0.45, 1.0},
        /*bg */       { 0.13, 0.11, 0.17, 1.00},
        /*base */     { 0.13, 0.11, 0.17, 1.00},
        /*text */     { 0.45, 0.45, 0.45, 1.0},
        /*shadow */   { 0.0, 0.0, 0.0, 0.2},
        /*frame */    { 0.0, 0.0, 0.0, 1.0},
        /*light */    { 0.1, 0.1, 0.1, 1.0}
    };

    main->color_scheme->prelight = (Colors) {
        /*fg */       { 1.0, 1.0, 1.0, 1.0},
        /*bg */       { 0.13, 0.11, 0.30, 1.00},
        /*base */     { 0.13, 0.11, 0.30, 1.00},
        /*text */     { 0.7, 0.7, 0.7, 1.0},
        /*shadow */   { 0.1, 0.1, 0.1, 0.4},
        /*frame */    { 0.3, 0.3, 0.3, 1.0},
        /*light */    { 0.3, 0.3, 0.3, 1.0}
    };

    main->color_scheme->selected = (Colors) {
        /*fg */       { 0.9, 0.9, 0.9, 1.0},
        /*bg */       { 0.13, 0.11, 0.30, 1.00},
        /*base */     { 0.13, 0.11, 0.30, 1.00},
        /*text */     { 1.0, 1.0, 1.0, 1.0},
        /*shadow */   { 0.18, 0.18, 0.18, 0.2},
        /*frame */    { 0.18, 0.18, 0.18, 1.0},
        /*light */    { 0.18, 0.18, 0.18, 1.0}
    };

    main->color_scheme->insensitive = (Colors) {
        /*fg */       { 0.15, 0.15, 0.15, 0.5},
        /*bg */       { 0.85, 0.85, 0.85, 0.5},
        /*base */     { 0.9, 0.9, 0.9, 0.5},
        /*text */     { 0.35, 0.35, 0.35, 0.5},
        /*shadow */   { 0.0, 0.0, 0.0, 0.1},
        /*frame */    { 0.2, 0.2, 0.2, 0.5},
        /*light */    { 0.9, 0.9, 0.9, 0.5}
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

// special function to link controllers of left and right channel
// when link is selected
static void check_for_link(X11_UI* ui, PortIndex port_name, float* value) {
    if (adj_get_value(ui->widget[6]->adj)) {
        switch (port_name) {
          case TIME_R:
            check_value_changed(ui->widget[1]->adj,value);
            break;
          case TIME_L:
            check_value_changed(ui->widget[0]->adj,value);
            break;
          case PERCENT_R:
            check_value_changed(ui->widget[4]->adj,value);
            break;
          case PERCENT_L:
            check_value_changed(ui->widget[3]->adj,value);
            break;
          default:
            break;
        }
    }
}

static void set_sensitive_state(X11_UI* ui, float state) {
    X11_UI_Private_t *ps = (X11_UI_Private_t*)ui->private_ptr;
    if (fabs(state - ps->mode)<0.1) {
        ps->mode = state;
        return;
    }
    if ( state < 0.1) {
        ui->widget[2]->state = INSENSITIVE_;
        expose_widget(ui->widget[2]);
    } else {
        ui->widget[2]->state = NORMAL_;
        expose_widget(ui->widget[2]);
    }
}

void plugin_value_changed(X11_UI *ui, Widget_t *w, PortIndex index) {
    if (w->data == INVERT) {
        set_sensitive_state(ui, w->adj->value);
    }
    check_for_link(ui, (PortIndex) w->data, &w->adj->value);
}

// shortcut to create knobs with portindex binding
Widget_t* add_my_toggle_button(Widget_t *w, PortIndex index, const char * label,
                                X11_UI* ui, int x, int y, int width, int height) {
    w = add_toggle_button(ui->win, label, x, y, width, height);
    w->parent_struct = ui;
    w->data = index;
    w->func.value_changed_callback = value_changed;
    return w;
}

void plugin_set_window_size(int *w,int *h,const char * plugin_uri) {
    (*w) = 810; //set initial widht of main window
    (*h) = 180; //set initial heigth of main window
}

const char* plugin_set_name() {
    return "GxEcho-Stereo"; //set plugin name to display on UI
}

void plugin_create_controller_widgets(X11_UI *ui, const char * plugin_uri) {
    X11_UI_Private_t *ps =(X11_UI_Private_t*)malloc(sizeof(X11_UI_Private_t));;
    ui->private_ptr = (void*)ps;
    ps->mode = 2.0;
    set_my_theme(&ui->main);
    set_my_knob_color(ui->kp);
    widget_get_png(ui->win, LDVAR(guitarix_png));
    // create all controllers needed
    ui->widget[0] = add_my_knob(ui->widget[0], TIME_R,"Time (R)", ui,480, 25, 100, 125);
    set_adjustment(ui->widget[0]->adj,100.0, 100.0, 1.0, 2000.0, 10.0, CL_CONTINUOS);

    ui->widget[1] = add_my_knob(ui->widget[1], TIME_L,"Time (L)", ui,240, 25, 100, 125);
    set_adjustment(ui->widget[1]->adj,100.0, 100.0, 1.0, 2000.0, 10.0, CL_CONTINUOS);

    ui->widget[2] = add_my_knob(ui->widget[2], LFOFREQ,"Lfo", ui,380, 25, 60, 85);
    set_adjustment(ui->widget[2]->adj,0.2, 0.2, 0.2, 5.0, 0.05, CL_CONTINUOS);

    ui->widget[3] = add_my_knob(ui->widget[3], PERCENT_R,"Level (R)", ui,600, 25, 100, 125);
    set_adjustment(ui->widget[3]->adj,30.0, 30.0, 0.0, 100.0, 1.0, CL_CONTINUOS);

    ui->widget[4] = add_my_knob(ui->widget[4], PERCENT_L,"Level (L)", ui,120, 25, 100, 125);
    set_adjustment(ui->widget[4]->adj,30.0, 30.0, 0.0, 100.0, 1.0, CL_CONTINUOS);

    const char* model[] = {"linear","ping pong"};
    size_t len = sizeof(model) / sizeof(model[0]);
    ui->widget[5] = add_my_combobox(ui->widget[5], INVERT, "Mode", model, len, 0, ui, 340, 110, 140, 30);

    ui->widget[6] = add_my_toggle_button(ui->widget[6], LINK,"Link(L+R)", ui,710, 70, 70, 40);

    ui->widget[7] = add_on_off_button(ui->win, "Power", 50, 50, 40, 80);
    ui->widget[7]->scale.gravity = ASPECT;
    ui->widget[7]->data = BYPASS;
    ui->widget[7]->parent_struct = ui;
    ui->widget[7]->func.value_changed_callback = value_changed;
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
    float value = *(float*)buffer;
    if (port_index == INVERT) {
        set_sensitive_state(ui, value);
    } else if (port_index == (uint32_t) BYPASS) {
        ui->block_event = -1;
    }
    check_for_link(ui, (PortIndex) port_index, &value);
}

