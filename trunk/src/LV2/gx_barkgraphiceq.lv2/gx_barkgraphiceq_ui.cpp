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

#include "gx_barkgraphiceq.h"
#include "bark_freq_grid.h"
#include "xasprintf.h"

/*---------------------------------------------------------------------
-----------------------------------------------------------------------    
                define controller numbers
-----------------------------------------------------------------------
----------------------------------------------------------------------*/

#define CONTROLS BARK_NUMBER_OF_BANDS

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
    char **frequencys;
} X11_UI_Private_t;

void plugin_value_changed(X11_UI *ui, Widget_t *w, PortIndex index) {
    // do special stuff when needed
}

void plugin_set_window_size(int *w,int *h,const char * plugin_uri) {
    (*w) = 800; //initial width of main window
    (*h) = 340; //initial height of main window
}

const char* plugin_set_name() {
    return "GxBarkGraphicEQ"; //plugin name to display on UI
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
    ps->frequencys = NULL;

    int iw=0;
    int w_pos = 40;
    int port = (PortIndex) V1;
    for (;iw<CONTROLS;iw++) {
        ps->meter_widget[iw] = add_vmeter(ui->win, "Meter", false, w_pos, 40, 30, 120);
        ps->meter_widget[iw]->parent_struct = ui;
        ps->meter_widget[iw]->data = port;
        port +=1;
        w_pos +=30;
    }

    iw=0;
    w_pos = 40;
    port = (PortIndex) G1;
    ps->frequencys = (char **)malloc((CONTROLS) * sizeof(char *));

    for (;iw<CONTROLS;iw++) {
        asprintf (&ps->frequencys[iw], "%d", bark_center_freqs[iw]);
        ui->widget[iw] = add_my_slider(ui->widget[iw], (PortIndex)port,ps->frequencys[iw], ui,w_pos, 180, 30, 100);
        set_adjustment(ui->widget[iw]->adj,0.0, 0.0, -40.0, 4.0, 0.1, CL_CONTINUOS);
        //adj_set_scale(ui->widget[iw]->adj, 2.0);
        port +=1;
        w_pos +=30;
    }
}

void plugin_cleanup(X11_UI *ui) {
    X11_UI_Private_t *ps = (X11_UI_Private_t*)ui->private_ptr;
    int iw=0;
    for (;iw<CONTROLS;iw++) {
        destroy_widget(ps->meter_widget[iw],&ui->main);
        free(ps->frequencys[iw]);
        ps->frequencys[iw] = NULL;
    }
    
    free(ps->frequencys);
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
    if(port_index >= (uint32_t)V1 && port_index <= (uint32_t)V24) {
        X11_UI* ui = (X11_UI*)handle;
        X11_UI_Private_t *ps = (X11_UI_Private_t*)ui->private_ptr;
        float value = *(float*)buffer;
        set_meter_value(ui, ps->meter_widget[port_index-24], value);
    }
}
