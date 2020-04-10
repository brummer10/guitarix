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

#include "gx_mbcompressor.h"

/*---------------------------------------------------------------------
-----------------------------------------------------------------------    
                define controller numbers
-----------------------------------------------------------------------
----------------------------------------------------------------------*/

#define CONTROLS 26

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
    Widget_t *meter_widget[10];
    Widget_t *combo_widget[5];
    Adjustment_t *adj[3];
    float db_zero;
} X11_UI_Private_t;

// setup a color theme
static void set_my_theme(Xputty *main) {
    main->color_scheme->normal = (Colors) {
         /* cairo    / r  / g  / b  / a  /  */
        .fg =       { 0.45, 0.45, 0.45, 1.0},
        .bg =       { 0.07, 0.05, 0.14, 1.00},
        .base =     { 0.0, 0.0, 0.0, 1.00},
        .text =     { 0.45, 0.45, 0.45, 1.0},
        .shadow =   { 0.28, 0.34, 0.62, 0.43},
        .frame =    { 0.0, 0.0, 0.0, 1.0},
        .light =    { 0.1, 0.1, 0.1, 1.0}
    };

    main->color_scheme->prelight = (Colors) {
        .fg =       { 1.0, 1.0, 1.0, 1.0},
        .bg =       { 0.14, 0.14, 0.22, 1.00},
        .base =     { 0.0, 0.0, 0.0, 1.00},
        .text =     { 0.7, 0.7, 0.7, 1.0},
        .shadow =   { 0.28, 0.34, 0.62, 0.63},
        .frame =    { 0.3, 0.3, 0.3, 1.0},
        .light =    { 0.3, 0.3, 0.3, 1.0}
    };

    main->color_scheme->selected = (Colors) {
        .fg =       { 0.9, 0.9, 0.9, 1.0},
        .bg =       { 0.14, 0.14, 0.22, 1.00},
        .base =     { 0.0, 0.0, 0.18, 1.00},
        .text =     { 1.0, 1.0, 1.0, 1.0},
        .shadow =   { 0.28, 0.34, 0.62, 0.93},
        .frame =    { 0.18, 0.18, 0.18, 1.0},
        .light =    { 0.18, 0.18, 0.28, 1.0}
    };
}

// draw the slider handle
static void rounded_rectangle(cairo_t *cr,float x, float y, float w, float h) {
    float r = h*0.55;

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
    X11_UI_Private_t *ps = (X11_UI_Private_t*)ui->private_ptr;

    int width = w->width-2;
    int height = w->height-2;
    float center = (float)height/2;

    float sliderstate1 = adj_get_state(w->adj);
    float sliderstate2 = adj_get_state(ps->adj[0]);
    float sliderstate3 = adj_get_state(ps->adj[1]);
    float sliderstate4 = adj_get_state(ps->adj[2]);
    float sliderstate = 0.0;
    Color_state s1 = NORMAL_;
    Color_state s2 = NORMAL_;
    Color_state s3 = NORMAL_;
    Color_state s4 = NORMAL_;

    if (w->state>0.0 && w->state<4.0 && w->adj_x) {
        if (w->adj_x == w->adj) {
            sliderstate = sliderstate1;
            s1 = PRELIGHT_;
        } else if (w->adj_x == ps->adj[0]) {
            sliderstate = sliderstate2;
            s2 = PRELIGHT_;
        } else if (w->adj_x == ps->adj[1]) {
            sliderstate = sliderstate3;
            s3 = PRELIGHT_;
        } else if (w->adj_x == ps->adj[2]) {
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
    cairo_line_to(w->crb,((width-height)*sliderstate1)+center,height-4.0);
    cairo_stroke(w->crb);
    use_text_color_scheme(w, s2);
    cairo_move_to (w->crb,((width-height)*sliderstate2)+center, 2.0);
    cairo_line_to(w->crb,((width-height)*sliderstate2)+center,height-4.0);
    cairo_stroke(w->crb);
    use_text_color_scheme(w, s3);
    cairo_move_to (w->crb,((width-height)*sliderstate3)+center, 2.0);
    cairo_line_to(w->crb,((width-height)*sliderstate3)+center,height-4.0);
    cairo_stroke(w->crb);
    use_text_color_scheme(w, s4);
    cairo_move_to (w->crb,((width-height)*sliderstate4)+center, 2.0);
    cairo_line_to(w->crb,((width-height)*sliderstate4)+center,height-4.0);
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

void plugin_value_changed(X11_UI *ui, Widget_t *w, PortIndex index) {
    if (ui->block_event != w->data) {
        if (index >= MODE1 && index <= MODE5) {
            float value = adj_get_value(w->adj)+1.0;
            ui->write_function(ui->controller,w->data,sizeof(float),0,&value);
            ui->block_event = -1;
        }
    }
}

// check that bands didn't overlap
static void check_multi_controller(X11_UI* ui, uint32_t port_index, float value) {
    X11_UI_Private_t *ps = (X11_UI_Private_t*)ui->private_ptr;
    float v = log10f(value);
    switch ((PortIndex)port_index)
        {
        case CROSSOVER_B1_B2:
            check_value_changed(ui->widget[25]->adj, &v);
            adj_set_value(ps->adj[0], max(adj_get_value(ps->adj[0]), v+0.1));
        break;
        case CROSSOVER_B2_B3:
            adj_set_value(ui->widget[25]->adj, min(adj_get_value(ui->widget[25]->adj), v-0.1));
            check_value_changed(ps->adj[0], &v);
            adj_set_value(ps->adj[1], max(adj_get_value(ps->adj[1]), v+0.1));
        break;
        case CROSSOVER_B3_B4:
            adj_set_value(ps->adj[0], min(adj_get_value(ps->adj[0]), v-0.1));
            check_value_changed(ps->adj[1], &v);
            adj_set_value(ps->adj[2], max(adj_get_value(ps->adj[2]), v+0.1));
        break;
        case CROSSOVER_B4_B5:
            adj_set_value(ps->adj[1], min(adj_get_value(ps->adj[1]), v-0.1));
            check_value_changed(ps->adj[2], &v);
        break;
        default:
        break;
    }
}

// if adjustment value changed send notify to host
static void slider_value_changed(void *w_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    X11_UI* ui = (X11_UI*)w->parent_struct;
    X11_UI_Private_t *ps = (X11_UI_Private_t*)ui->private_ptr;
    uint32_t port_index = 0;
    float value = 0.0;
    if (w->adj_x == w->adj) {
        port_index = CROSSOVER_B1_B2;
        value = adj_get_value(w->adj);
    } else if (w->adj_x == ps->adj[0]) {
        port_index = CROSSOVER_B2_B3;
        value = adj_get_value(ps->adj[0]);
    } else if (w->adj_x == ps->adj[1]) {
        port_index = CROSSOVER_B3_B4;
        value = adj_get_value(ps->adj[1]);
    } else if (w->adj_x == ps->adj[2]) {
        port_index = CROSSOVER_B4_B5;
        value = adj_get_value(ps->adj[2]);
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
    X11_UI_Private_t *ps = (X11_UI_Private_t*)ui->private_ptr;
    float x = float(w->pos_x)/float(w->width-w->height);

    float sliderstate1 = adj_get_state(w->adj);
    float sliderstate2 = adj_get_state(ps->adj[0]);
    float sliderstate3 = adj_get_state(ps->adj[1]);
    float sliderstate4 = adj_get_state(ps->adj[2]);

    if (x < sliderstate1+0.04 && x >sliderstate1) {
        w->adj_x = w->adj;
        w->label = "Band 1<|>2 ";
    }
    else if (x < sliderstate2+0.04 && x >sliderstate2) {
        w->adj_x = ps->adj[0];
        w->label = "Band 2<|>3 ";
    }
    else if (x < sliderstate3+0.04 && x >sliderstate3) {
        w->adj_x = ps->adj[1];
        w->label = "Band 3<|>4 ";
    }
    else if (x < sliderstate4+0.04 && x >sliderstate4) {
        w->adj_x = ps->adj[2];
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
    X11_UI_Private_t *ps = (X11_UI_Private_t*)ui->private_ptr;
    w = create_widget(ui->win->app, ui->win, x, y, width, height);
    w->label = label;    
    w->adj = add_adjustment(w,1.3, 1.3, 1.3, 4.3, 0.001, CL_CONTINUOS);
    adj_set_scale(w->adj, 2.0);
    ps->adj[0] = add_adjustment(w,1.3, 1.3, 1.3, 4.3, 0.001, CL_CONTINUOS);
    adj_set_scale(ps->adj[0], 2.0);
    ps->adj[1] = add_adjustment(w,1.3, 1.3, 1.3, 4.3, 0.001, CL_CONTINUOS);
    adj_set_scale(ps->adj[1], 2.0);
    ps->adj[2] = add_adjustment(w,1.3, 1.3, 1.3, 4.3, 0.001, CL_CONTINUOS);
    adj_set_scale(ps->adj[2], 2.0);
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

void plugin_set_window_size(int *w,int *h,const char * plugin_uri) {
    (*w) = 780; //initial widht of main window
    (*h) = 520; //initial heigth of main window
}

const char* plugin_set_name() {
    return "GxMultiBandCompressor"; //plugin name to display on UI
}

void plugin_create_controller_widgets(X11_UI *ui, const char * plugin_uri) {
    X11_UI_Private_t *ps =(X11_UI_Private_t*)malloc(sizeof(X11_UI_Private_t));;
    ui->private_ptr = (void*)ps;
    ps->db_zero = 20.*log10(0.0000003); // -130db
    set_my_theme(&ui->main);

    int iw=0;
    int w_pos = 620;
    int port = (PortIndex) V1;
    for (;iw<10;iw++) {
        ps->meter_widget[iw] = add_vmeter(ui->win, "Meter", false, w_pos, 60, 20, 340);
        ps->meter_widget[iw]->parent_struct = ui;
        ps->meter_widget[iw]->scale.gravity = CENTER;
        ps->meter_widget[iw]->data = port;
        port +=1;
        w_pos +=20;
        if(iw == 4) w_pos = 60;
    }


    iw=0;
    w_pos = 200;
    port = (PortIndex) MAKEUP1;
    for (;iw<5;iw++) {
        ui->widget[iw] = add_my_knob(ui->widget[iw], (PortIndex)port,"Makeup", ui,w_pos, 0, 60, 85);
        set_adjustment(ui->widget[iw]->adj,13.0, 13.0, -50.0, 50.0, 0.1, CL_CONTINUOS);
        //adj_set_scale(ui->widget[iw]->adj, 2.0);
        port +=1;
        w_pos +=80;
    }

    w_pos = 200;
    port = (PortIndex) MAKEUPTHRESHOLD1;
    for (;iw<10;iw++) {
        ui->widget[iw] = add_my_knob(ui->widget[iw], (PortIndex)port,"Threshold", ui,w_pos, 85, 60, 85);
        set_adjustment(ui->widget[iw]->adj,2.0, 2.0, 0.0, 10.0, 0.01, CL_CONTINUOS);
        //adj_set_scale(ui->widget[iw]->adj, 2.0);
        port +=1;
        w_pos +=80;
    }

    w_pos = 200;
    port = (PortIndex) RATIO1;
    for (;iw<15;iw++) {
        ui->widget[iw] = add_my_knob(ui->widget[iw], (PortIndex)port,"Ratio", ui,w_pos, 170, 60, 85);
        set_adjustment(ui->widget[iw]->adj,4.0, 4.0, 1.0, 100.0, 0.1, CL_CONTINUOS);
        //adj_set_scale(ui->widget[iw]->adj, 2.0);
        port +=1;
        w_pos +=80;
    }

    w_pos = 200;
    port = (PortIndex) ATTACK1;
    for (;iw<20;iw++) {
        ui->widget[iw] = add_my_knob(ui->widget[iw], (PortIndex)port,"Attack", ui,w_pos, 255, 60, 85);
        set_adjustment(ui->widget[iw]->adj,0.012, 0.012, 0.001, 1.0, 0.001, CL_CONTINUOS);
        //adj_set_scale(ui->widget[iw]->adj, 2.0);
        port +=1;
        w_pos +=80;
    }

    w_pos = 200;
    port = (PortIndex) RELEASE1;
    for (;iw<25;iw++) {
        ui->widget[iw] = add_my_knob(ui->widget[iw], (PortIndex)port,"Release", ui,w_pos, 340, 60, 85);
        set_adjustment(ui->widget[iw]->adj,1.25, 1.25, 0.01, 10.0, 0.01, CL_CONTINUOS);
        //adj_set_scale(ui->widget[iw]->adj, 2.0);
        port +=1;
        w_pos +=80;
    }

    w_pos = 185;
    port = (PortIndex) MODE1;
    const char* model[] = {"Compress","Bypass","Mute"};
    size_t len = sizeof(model) / sizeof(model[0]);
    iw=0;
    for (;iw<5;iw++) {
        ps->combo_widget[iw] = add_my_combobox(ps->combo_widget[iw], (PortIndex)port,"Mode", model, len, 0, ui, w_pos, 425, 80, 25);
        //adj_set_scale(ui->widget[iw]->adj, 2.0);
        port +=1;
        w_pos +=80;
    }

    ui->widget[25] = add_my_slider(ui->widget[25], CROSSOVER_B1_B2,"Crossover ",ui, 160,460, 480, 20);
}

// map power to db for meter widgets
static void set_meter_value(X11_UI* ui, Widget_t*w, float value) {
    X11_UI_Private_t *ps = (X11_UI_Private_t*)ui->private_ptr;
    float new_val = power2db(w,20.*log10(max(ps->db_zero,value)));
    check_value_changed(w->adj,&new_val);
}

void plugin_cleanup(X11_UI *ui) {
    X11_UI_Private_t *ps = (X11_UI_Private_t*)ui->private_ptr;
    int i = 0;
    for(;i<10;i++)
        destroy_widget(ps->meter_widget[i],&ui->main);
    for(;i<5;i++)
        destroy_widget(ps->combo_widget[i],&ui->main);
    delete_adjustment(ps->adj[0]);
    delete_adjustment(ps->adj[1]);
    delete_adjustment(ps->adj[2]);
    ui->widget[25]->adj_x = NULL;
    free(ps);
    ui->private_ptr = NULL;
}

void plugin_port_event(LV2UI_Handle handle, uint32_t port_index,
                        uint32_t buffer_size, uint32_t format,
                        const void * buffer) {
    X11_UI* ui = (X11_UI*)handle;
    X11_UI_Private_t *ps = (X11_UI_Private_t*)ui->private_ptr;
    float value = *(float*)buffer;
    if (port_index == V1) set_meter_value(ui,ps->meter_widget[0],value);
    else if (port_index == V2) set_meter_value(ui,ps->meter_widget[1],value);
    else if (port_index == V3) set_meter_value(ui,ps->meter_widget[2],value);
    else if (port_index == V4) set_meter_value(ui,ps->meter_widget[3],value);
    else if (port_index == V5) set_meter_value(ui,ps->meter_widget[4],value);
    else if (port_index == V6) set_meter_value(ui,ps->meter_widget[5],value);
    else if (port_index == V7) set_meter_value(ui,ps->meter_widget[6],value);
    else if (port_index == V8) set_meter_value(ui,ps->meter_widget[7],value);
    else if (port_index == V9) set_meter_value(ui,ps->meter_widget[8],value);
    else if (port_index == V10) set_meter_value(ui,ps->meter_widget[9],value);
    if (port_index >= CROSSOVER_B1_B2 && port_index <= CROSSOVER_B4_B5) {
        check_multi_controller(ui, port_index, value);
        ui->block_event = (int)port_index;
    }
    if (port_index >= MODE1 && port_index <= MODE5) {
        value -=1.0;
        check_value_changed(ps->combo_widget[port_index]->adj, &value);
        ui->block_event = (int)port_index;
    }
}
