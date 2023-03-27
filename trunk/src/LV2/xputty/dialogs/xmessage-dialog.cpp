/*
 *                           0BSD 
 * 
 *                    BSD Zero Clause License
 * 
 *  Copyright (c) 2019 Hermann Meyer
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted.

 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 *
 */

#include "xmessage-dialog.h"


static void draw_message_label(Widget_t *w, int width, int height) {
    MessageDialog *md = (MessageDialog *)w->parent_struct;
    cairo_text_extents_t extents;
    use_fg_color_scheme(w, NORMAL_);
    cairo_set_font_size (w->crb, 12.0);
    int i = 0;
    for(;i<(int)md->lin;i++) {
        cairo_text_extents(w->crb,md->message[i] , &extents);
        cairo_move_to (w->crb, 100, ((40)+(extents.height * (2*i))));
        cairo_show_text(w->crb, md->message[i]);
        cairo_new_path (w->crb);
    }    
}

static void draw_message_window(void *w_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    Metrics_t m;
    int width_t, height_t;
    os_get_window_metrics(w, &m);
    width_t = m.width;
    height_t = m.height;
    if (!m.visible) return;

    cairo_rectangle(w->crb,0,0,width_t,height_t);
    set_pattern(w,&w->app->color_scheme->selected,&w->app->color_scheme->normal,BACKGROUND_);
    cairo_fill (w->crb);

    widget_set_scale(w);
    int width, height;
    os_get_surface_size(w->image, &width, &height);
    double x = 64.0/(double)(width);
    double y = 64.0/(double)height;
    double x1 = (double)height/64.0;
    double y1 = (double)(width)/64.0;
    cairo_scale(w->crb, x,y);
    cairo_set_source_surface (w->crb, w->image, 50, 50);
    cairo_rectangle(w->crb,50, 50, width, height);
    cairo_fill(w->crb);
    cairo_scale(w->crb, x1,y1);

    draw_message_label(w,width_t,height_t);
    widget_reset_scale(w);
}

static void draw_entry(void *w_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    if (!w) return;
    Metrics_t m;
    int width, height;
    os_get_window_metrics(w, &m);
    width = m.width;
    height = m.height;
    if (!m.visible) return;

    use_base_color_scheme(w, NORMAL_);
    cairo_rectangle(w->cr,0,0,width,height);
    cairo_fill_preserve (w->cr);
    use_text_color_scheme(w, NORMAL_);
    cairo_set_line_width(w->cr, 2.0);
    cairo_stroke(w->cr);

    cairo_set_font_size (w->cr, 9.0);

    cairo_move_to (w->cr, 2, 9);
    cairo_show_text(w->cr, " ");
}

static void entry_add_text(void  *w_, void *label_) {
    Widget_t *w = (Widget_t*)w_;
    if (!w) return;
    char *label = (char*)label_;
    if (!label) {
        label = (char*)"";
    }
    draw_entry(w,NULL);
    cairo_text_extents_t extents;
    use_text_color_scheme(w, NORMAL_);
    cairo_set_font_size (w->cr, 11.0);
    if (strlen( w->input_label))
         w->input_label[strlen( w->input_label)-1] = 0;
    if (strlen( w->input_label)<30) {
        if (strlen(label))
        strcat( w->input_label, label);
    }
    w->label = w->input_label;
    strcat( w->input_label, "|");
    cairo_set_font_size (w->cr, 12.0);
    cairo_text_extents(w->cr, w->input_label , &extents);

    cairo_move_to (w->cr, 2, 12.0+extents.height);
    cairo_show_text(w->cr,  w->input_label);

}

static void entry_clip(Widget_t *w) {
    draw_entry(w,NULL);
    cairo_text_extents_t extents;
    use_text_color_scheme(w, NORMAL_);
    cairo_set_font_size (w->cr, 11.0);

    // check for UTF 8 char
    if (strlen( w->input_label)>=2) {
        int i = strlen( w->input_label)-1;
        int j = 0;
        int u = 0;
        for(;i>=0;i--) {
            if(IS_UTF8(w->input_label[i])) {
                 u++;
            }
            j++;
            if (u == 1) break;
            if (j>2) break;
        }
        if (!u) j =2;

        memset(&w->input_label[strlen( w->input_label)-(sizeof(char)*(j))],0,sizeof(char)*(j));
        strcat( w->input_label, "|");
    }
    cairo_set_font_size (w->cr, 12.0);
    cairo_text_extents(w->cr, w->input_label , &extents);

    cairo_move_to (w->cr, 2, 12.0+extents.height);
    cairo_show_text(w->cr,  w->input_label);

}

static void message_okay_callback(void *w_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    if (w->flags & HAS_POINTER && !*(int*)user_data){
        Widget_t *p = (Widget_t*)w->parent;
        MessageDialog *md = (MessageDialog *)p->parent_struct;
        if(md->message_type == QUESTION_BOX || md->message_type == SELECTION_BOX) {
            Widget_t *pa = (Widget_t*)p->parent;
            pa->func.dialog_callback(pa,&md->response);
        } else if(md->message_type == ENTRY_BOX) {
            Widget_t *pa = (Widget_t*)p->parent;
            if (strlen( md->text_entry->input_label))
                md->text_entry->input_label[strlen( md->text_entry->input_label)-1] = 0;
            md->text_entry->label = md->text_entry->input_label;
            pa->func.dialog_callback(pa,&md->text_entry->label);
        }
        destroy_widget(p, p->app);
    }
}

static void message_no_callback(void *w_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    if (w->flags & HAS_POINTER && !*(int*)user_data){
        Widget_t *p = (Widget_t*)w->parent;
        MessageDialog *md = (MessageDialog *)p->parent_struct;
        if(md->message_type == QUESTION_BOX) {
            Widget_t *pa = (Widget_t*)p->parent;
            md->response = -1;
            pa->func.dialog_callback(pa,&md->response);
        }
        destroy_widget(p, p->app);
    }
}

static void radio_box_set_active(Widget_t *w) {
    Widget_t * p = (Widget_t*)w->parent;
    MessageDialog *md = (MessageDialog *)p->parent_struct;
    int response = 0;
    int i = 0;
    for(;i<p->childlist->elem;i++) {
        Widget_t *wid = p->childlist->childs[i];
        if (wid->adj && wid->flags & IS_RADIO) {
            ++response;
            if (wid != w) adj_set_value(wid->adj_y, 0.0);
            else if (wid == w) md->response = response;
        }
    }
}

static void radio_box_button_pressed(void *w_, void* button_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    if (w->flags & HAS_FOCUS) {
        radio_box_set_active(w);
    }
}

static void create_checkboxes(Widget_t *w) {
    MessageDialog *md = (MessageDialog *)w->parent_struct;
    int y = (md->lin + 1) * 24 +12;
    int i = 0;
    for(;i<(int)md->sel;i++) {
        Widget_t *wid = add_check_box(w,md->choices[i] , 100, y + (24*i), 15, 15);
        wid->flags |= IS_RADIO;
        wid->func.button_press_callback = radio_box_button_pressed;
   }
}

static void entry_get_text(void *w_, void *key_, void *user_data) {
    Widget_t *w = (Widget_t*)w_;
    if (!w) return;
    XKeyEvent *key = (XKeyEvent*)key_;
    if (!key) return;
    int nk = key_mapping(w->app->dpy, key);
    if (nk) {
        switch (nk) {
            case 10: 
                {
                Widget_t *p = (Widget_t*)w->parent;
                MessageDialog *md = (MessageDialog *)p->parent_struct;
                Widget_t *pa = (Widget_t*)p->parent;
                if (strlen( md->text_entry->input_label))
                    md->text_entry->input_label[strlen( md->text_entry->input_label)-1] = 0;
                md->text_entry->label = md->text_entry->input_label;
                pa->func.dialog_callback(pa,&md->text_entry->label);

                destroy_widget(p, p->app);
                }
            break;
            case 11: entry_clip(w);
            break;
            default:
            break;
        }
    } else {
        Status status;
        KeySym keysym;
        char buf[32];
        Xutf8LookupString(w->xic, key, buf, sizeof(buf) - 1, &keysym, &status);
        if(status == XLookupChars || status == XLookupBoth){
            entry_add_text(w, buf);
        }
    }
}

static void create_entry_box(Widget_t *w) {
    MessageDialog *md = (MessageDialog *)w->parent_struct;

    md->text_entry = create_widget(w->app, w, 20, md->height-90, md->width-40, 40);
    memset(md->text_entry->input_label, 0, 32 * (sizeof md->text_entry->input_label[0]) );
    md->text_entry->func.expose_callback = entry_add_text;
    md->text_entry->func.key_press_callback = entry_get_text;
    md->text_entry->flags &= ~USE_TRANSPARENCY;
    md->text_entry->scale.gravity = CENTER;
}

static void check_for_message(MessageDialog *md, const char *message) {
    if(!message) return;
    if(!strlen(message)) return;
    int len = 0;
    char *ms =strdup(message);
    char * p = strtok (ms, "|");
    while (p) {
        md->message = (char**)realloc (md->message, sizeof (char*) * ++md->lin);
        md->message[md->lin-1] = strdup(p);
        len = max(len, (int)strlen(md->message[md->lin-1]));
        p = strtok (NULL, "|");
    }
    free(ms);
    md->width = len*12 ;
    md->height = md->lin*12+100;
}

static void check_for_choices(MessageDialog *md, const char *choices) {
    if(!choices) return;
    if(!strlen(choices)) return;
    int len = 0;
    char *ms =strdup(choices);
    char * p = strtok (ms, "|");
    while (p) {
        md->choices = (char**)realloc (md->choices, sizeof (char*) * ++md->sel);
        md->choices[md->sel-1] = strdup(p);
        len = max(len, (int)strlen(md->choices[md->sel-1]));
        p = strtok (NULL, "|");
    }
    free(ms);
    md->width = max(len*12,(int)md->width);
    md->height += md->sel*12+50;
}

static void check_for_style(MessageDialog *md, int style) {
    if(style == ENTRY_BOX) {
        md->width = max(330,md->width);
        md->height = max(140,md->height+60);
    }
}

static void mg_mem_free(void *w_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    MessageDialog *md = (MessageDialog *)w->parent_struct;
    if(md->icon) {
        os_free_pixmap(w, (*md->icon));
        md->icon = NULL;
    }
    int i = 0;
    for(;i<(int)md->lin;i++) {
        free(md->message[i]);
    }
    i = 0;
    for(;i<(int)md->sel;i++) {
        free(md->choices[i]);
    }
    free(md->choices);
    free(md);
}

Widget_t *open_message_dialog(Widget_t *w, int style, const char *title,
                              const char *message, const char *choices) {

    MessageDialog *md = (MessageDialog*)malloc(sizeof(MessageDialog));
    md->response = 0;
    md->message_type = 0;
    md->lin = 0;
    md->width = 330;
    md->height = 200;
    md->message = NULL;
    md->sel = 0;
    md->choices = NULL;
    md->icon = NULL;
    check_for_message(md, message);
    check_for_choices(md, choices);
    check_for_style(md, style);
    Widget_t *wid = create_window(w->app, DefaultRootWindow(w->app->dpy), 0, 0, md->width, md->height);
    wid->label = message;
    wid->flags |= HAS_MEM;
    wid->scale.gravity = CENTER;
    wid->parent_struct = md;
    wid->parent = w;
    wid->func.mem_free_callback = mg_mem_free;
    wid->func.expose_callback = draw_message_window;
    char *alternate_title = NULL;
    char *button_title = (char*)"OK";
    Widget_t *no;
    switch (style) {
        case INFO_BOX:
            widget_get_png(wid, LDVAR(info_png));
            alternate_title = (char*)"INFO";
            md->message_type = INFO_BOX;
            widget_set_icon_from_surface(wid,md->icon,wid->image);
        break;
        case WARNING_BOX:
            widget_get_png(wid, LDVAR(warning_png));
            alternate_title = (char*)"WARNING";
            md->message_type = WARNING_BOX;
            widget_set_icon_from_surface(wid,md->icon,wid->image);
        break;
        case ERROR_BOX:
            widget_get_png(wid, LDVAR(error_png));
            alternate_title = (char*)"ERROR";
            md->message_type = ERROR_BOX;
            widget_set_icon_from_surface(wid,md->icon,wid->image);
        break;
        case QUESTION_BOX:
            widget_get_png(wid, LDVAR(question_png));
            alternate_title = (char*)"QUESTION";
            no = add_button(wid, "NO", 10, md->height-40, 60, 30);
            no->scale.gravity = CENTER;
            no->func.value_changed_callback = message_no_callback;
            md->message_type = QUESTION_BOX;
            button_title = (char*)"YES";
            widget_set_icon_from_surface(wid,md->icon,wid->image);
        break;
        case SELECTION_BOX:
            widget_get_png(wid, LDVAR(choice_png));
            alternate_title = (char*)"SELECTION";
            md->message_type = SELECTION_BOX;
            create_checkboxes(wid);
            widget_set_icon_from_surface(wid,md->icon,wid->image);
        break;
        case ENTRY_BOX:
            widget_get_png(wid, LDVAR(message_png));
            alternate_title = (char*)"TEXT ENTRY";
            md->message_type = ENTRY_BOX;
            create_entry_box(wid);
            widget_set_icon_from_surface(wid,md->icon,wid->image);
        break;
    }
    widget_set_title(wid, (title)? title : alternate_title);

    Widget_t *okay = add_button(wid, button_title, md->width-70, md->height-40, 60, 30);
    okay->scale.gravity = CENTER;
    okay->func.value_changed_callback = message_okay_callback;

    widget_show_all(wid);
    return wid;
}
