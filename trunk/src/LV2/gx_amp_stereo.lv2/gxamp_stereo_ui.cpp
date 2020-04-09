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

#include "gxamp_stereo.h"

/*---------------------------------------------------------------------
-----------------------------------------------------------------------    
                define controller numbers
-----------------------------------------------------------------------
----------------------------------------------------------------------*/

#define CONTROLS 12

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
    float schedule;
} X11_UI_Private_t;

// setup a color theme
static void set_my_theme(Xputty *main) {
    main->color_scheme->normal = (Colors) {
         /* cairo    / r  / g  / b  / a  /  */
        .fg =       { 0.85, 0.85, 0.85, 1.0},
        .bg =       { 0.1, 0.1, 0.2, 1.0},
        .base =     { 0.1, 0.1, 0.2, 1.0},
        .text =     { 0.9, 0.9, 0.9, 1.0},
        .shadow =   { 0.0, 0.0, 0.0, 0.2},
        .frame =    { 0.0, 0.0, 0.0, 1.0},
        .light =    { 0.1, 0.1, 0.2, 1.0}
    };

    main->color_scheme->prelight = (Colors) {
        .fg =       { 1.0, 0.0, 1.0, 1.0},
        .bg =       { 0.25, 0.25, 0.35, 1.0},
        .base =     { 0.2, 0.2, 0.3, 1.0},
        .text =     { 1.0, 1.0, 1.0, 1.0},
        .shadow =   { 0.1, 0.1, 0.1, 0.4},
        .frame =    { 0.3, 0.3, 0.3, 1.0},
        .light =    { 0.3, 0.3, 0.3, 1.0}
    };

    main->color_scheme->selected = (Colors) {
        .fg =       { 0.9, 0.9, 0.9, 1.0},
        .bg =       { 0.2, 0.2, 0.3, 1.0},
        .base =     { 0.18, 0.18, 0.28, 1.0},
        .text =     { 1.0, 1.0, 1.0, 1.0},
        .shadow =   { 0.18, 0.18, 0.18, 0.2},
        .frame =    { 0.18, 0.18, 0.18, 1.0},
        .light =    { 0.18, 0.18, 0.28, 1.0}
    };
}

void plugin_value_changed(X11_UI *ui, Widget_t *w, PortIndex index) {
    // do special stuff when needed
}

void plugin_set_window_size(int *w,int *h,const char * plugin_uri) {
    (*w) = 810; //set initial widht of main window
    (*h) = 196; //set initial heigth of main window
}

const char* plugin_set_name() {
    return "GxAmplifier-Stereo-X"; //set plugin name to display on UI
}

void plugin_create_controller_widgets(X11_UI *ui, const char * plugin_uri) {
    X11_UI_Private_t *ps =(X11_UI_Private_t*)malloc(sizeof(X11_UI_Private_t));;
    ui->private_ptr = (void*)ps;
    ps->schedule = 2.0;
    set_my_theme(&ui->main);
    widget_get_png(ui->win, LDVAR(guitarix_png));

    // create knob widgets
    ui->widget[0] = add_my_knob(ui->widget[0], GAIN1,"Mastergain", ui,685, 60, 90, 115);
    set_adjustment(ui->widget[0]->adj,0.0, 0.0, -20.0, 20.0, 0.1, CL_CONTINUOS);

    ui->widget[1] = add_my_knob(ui->widget[1], PREGAIN,"Pregain", ui,40, 60, 90, 115);
    set_adjustment(ui->widget[1]->adj,0.0, 0.0, -20.0, 20.0, 0.1, CL_CONTINUOS);

    ui->widget[2] = add_my_knob(ui->widget[2], WET_DRY,"Distortion", ui,142, 67, 75, 100);
    set_adjustment(ui->widget[2]->adj,1.0, 1.0, 1.0, 100.0, 1.0, CL_CONTINUOS);

    ui->widget[3] = add_my_knob(ui->widget[3], DRIVE,"Drive", ui,225, 70, 70, 95);
    set_adjustment(ui->widget[3]->adj,0.01, 0.01, 0.01, 1.0, 0.01, CL_CONTINUOS);

    ui->widget[4] = add_my_knob(ui->widget[4], TREBLE,"Treble", ui,305, 72, 65, 90);
    set_adjustment(ui->widget[4]->adj,0.5, 0.5, 0.0, 1.0, 0.01, CL_CONTINUOS);

    ui->widget[5] = add_my_knob(ui->widget[5], MIDDLE,"Mid", ui,375, 72, 65, 90);
    set_adjustment(ui->widget[5]->adj,0.5, 0.5, 0.0, 1.0, 0.01, CL_CONTINUOS);

    ui->widget[6] = add_my_knob(ui->widget[6], BASS,"Bass", ui,445, 72, 65, 90);
    set_adjustment(ui->widget[6]->adj,0.5, 0.5, 0.0, 1.0, 0.01, CL_CONTINUOS);

    ui->widget[7] = add_my_knob(ui->widget[7], ALevel,"Presence", ui,520, 70, 70, 95);
    set_adjustment(ui->widget[7]->adj,1.0, 1.0, 1.0, 10.0, 0.1, CL_CONTINUOS);

    ui->widget[8] = add_my_knob(ui->widget[8], CLevel,"Cabinet", ui,600, 67, 75, 100);
    set_adjustment(ui->widget[8]->adj,1.0, 1.0, 1.0, 20.0, 0.1, CL_CONTINUOS);

    // create combobox widgets
    const char* tonestacks[] = {"default","Bassman Style","Twin Reverb Style","Princeton Style","JCM-800 Style",
    "JCM-2000 Style","M-Lead Style","M2199 Style","AC-30 Style","Mesa Boogie Style","SOL 100 Style","JTM-45 Style","AC-15 Style",
    "Peavey Style","Ibanez Style","Roland Style","Ampeg Style","Rev.Rocket Style","MIG 100 H Style","Triple Giant Style",
    "Trio Preamp Style","Hughes&Kettner Style","Fender Junior Style","Fender Style","Fender Deville Style",
    "Gibsen Style", "Off" };
    size_t len = sizeof(tonestacks) / sizeof(tonestacks[0]);
    ui->widget[9] = add_my_combobox(ui->widget[9], T_MODEL, "Tonestack", tonestacks, len, 1, ui, 300, 30, 210, 30);

    const char* cab[] = {"4x12","2x12","1x12","4x10","2x10","HighGain Style","Twin Style",
    "Bassman Style","Marshall Style","AC30 Style","Princeton Style","A2 Style","1x15","Mesa Style","Briliant","Vitalize",
    "Charisma","1x8", "Off" };
    len = sizeof(cab) / sizeof(cab[0]);
    ui->widget[10] = add_my_combobox(ui->widget[10], C_MODEL, "Cabinet", cab, len, 0, ui, 540, 30, 210, 30);

    const char* tubes[] = {"12ax7","12AU7","12AT7","6DJ8","6C16","6V6","12ax7 feedback",
    "12AU7 feedback","12AT7 feedback","6DJ8 feedback","pre 12ax7/ master 6V6","pre 12AU7/ master 6V6",
    "pre 12AT7/ master 6V6","pre 6DJ8/ master 6V6","pre 12ax7/ push-pull 6V6","pre 12AU7/ push-pull 6V6",
    "pre 12AT7/ push pull 6V6","pre 6DJ8/ push-pull 6V6" };
    len = sizeof(tubes) / sizeof(tubes[0]);
    ui->widget[11] = add_my_combobox(ui->widget[11], MODEL, "Tubes", tubes, len, 0, ui, 60, 30, 210, 30);
}

void plugin_cleanup(X11_UI *ui) {
    X11_UI_Private_t *ps = (X11_UI_Private_t*)ui->private_ptr;
    free(ps);
    ui->private_ptr = NULL;
}

// disable presence and cabinet controlls when worker threads not been supported
static void set_sensitive_state(X11_UI* ui, float state) {
    X11_UI_Private_t *ps = (X11_UI_Private_t*)ui->private_ptr;
    if (fabs(state - ps->schedule)<0.1) {
        return;
    }
    ps->schedule = state;
    if ( state > 0) {
        ui->widget[10]->state = INSENSITIVE_;
        ui->widget[10]->childlist->childs[0]->state = INSENSITIVE_;
        ui->widget[7]->state = INSENSITIVE_;
        ui->widget[8]->state = INSENSITIVE_;
    } else {
        ui->widget[10]->state = NORMAL_;
        ui->widget[10]->childlist->childs[0]->state = NORMAL_;
        ui->widget[7]->state = NORMAL_;
        ui->widget[8]->state = NORMAL_;
    }
}

void plugin_port_event(LV2UI_Handle handle, uint32_t port_index,
                        uint32_t buffer_size, uint32_t format,
                        const void * buffer) {
    if (port_index == SCHEDULE) {
        X11_UI* ui = (X11_UI*)handle;
        float value = *(float*)buffer;
        set_sensitive_state(ui, value);
    }
}

