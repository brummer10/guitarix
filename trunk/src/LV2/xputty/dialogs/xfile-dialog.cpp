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


/*
#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif
*/

#include <dirent.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <stdarg.h> 
#include <string.h>
#include <unistd.h>

#include <libgen.h>

#include "xfile-dialog.h"


static void draw_window(void *w_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    XWindowAttributes attrs;
    XGetWindowAttributes(w->app->dpy, (Window)w->widget, &attrs);
    int width = attrs.width;
    int height = attrs.height;
    if (attrs.map_state != IsViewable) return;

    cairo_rectangle(w->crb,0,0,width,height);
    set_pattern(w,&w->app->color_scheme->selected,&w->app->color_scheme->normal,BACKGROUND_);
    cairo_fill (w->crb);

    widget_set_scale(w);
    use_fg_color_scheme(w, NORMAL_);
    cairo_set_font_size (w->crb, 12.0);
    cairo_move_to (w->crb, 20, 35);
    cairo_show_text(w->crb, "Directory");
    cairo_move_to (w->crb, 20, 85);
    cairo_show_text(w->crb, "File");
    cairo_move_to (w->crb, 20, 340);
    cairo_show_text(w->crb, "Load: ");
    cairo_move_to (w->crb, 45, 380);
    cairo_show_text(w->crb, "Show hidden files"); 
    cairo_move_to (w->crb, 60, 340);
    cairo_show_text(w->crb, w->label);
    widget_reset_scale(w);
}

static void button_quit_callback(void *w_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    FileDialog *file_dialog = (FileDialog *)w->parent_struct;
   
    if (w->flags & HAS_POINTER && !adj_get_value(w->adj)){
        file_dialog->parent->func.dialog_callback(file_dialog->parent,NULL);
        file_dialog->send_clear_func = false;
        destroy_widget(file_dialog->w,file_dialog->w->app);
    }
}

static inline int clear(Widget_t *w) {
    destroy_widget(w,w->app);
    return 0;
}

static inline int set_files(FileDialog *file_dialog) {
    listview_set_list(file_dialog->ft,file_dialog->fp->file_names , (int)file_dialog->fp->file_counter);
    int ret = 0;
    int i = 0;
    for (; i<(int)file_dialog->fp->file_counter; i++) {
        if(file_dialog->fp->selected_file && strcmp(file_dialog->fp->file_names[i],
          basename(file_dialog->fp->selected_file))==0 )  ret = i;
    }
    return ret;
}

static void set_dirs(FileDialog *file_dialog) {
    int i = 0;
    for (; i<(int)file_dialog->fp->dir_counter; i++) {
        combobox_add_entry(file_dialog->ct,file_dialog->fp->dir_names[i]);
    }
}

static void center_widget(Widget_t *wid, Widget_t *w) {
    XMoveWindow(wid->app->dpy,w->widget,w->scale.init_x /
        wid->scale.cscale_x,w->scale.init_y / wid->scale.cscale_y);
    XResizeWindow (wid->app->dpy, w->widget, max(1,
        w->scale.init_width / (wid->scale.cscale_x)), 
        max(1,w->scale.init_height / (wid->scale.cscale_y)));
}

static void set_selected_file(FileDialog *file_dialog) {
    if(adj_get_value(file_dialog->ft->adj)<0 ||
        adj_get_value(file_dialog->ft->adj) > file_dialog->fp->file_counter) return;
    Widget_t* menu =  file_dialog->ct->childlist->childs[1];
    Widget_t* view_port =  menu->childlist->childs[0];
    if(!childlist_has_child(view_port->childlist)) return ;
    Widget_t *dir = view_port->childlist->childs[(int)adj_get_value(file_dialog->ct->adj)];
    free(file_dialog->fp->selected_file);
    file_dialog->fp->selected_file = NULL;
    asprintf(&file_dialog->fp->selected_file, "%s/%s",dir->label,
        file_dialog->fp->file_names[(int)adj_get_value(file_dialog->ft->adj)]);
    assert(file_dialog->fp->selected_file != NULL);
}

static void file_released_callback(void *w_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    FileDialog *file_dialog = (FileDialog *)w->parent_struct;
    set_selected_file(file_dialog);
    if(file_dialog->fp->selected_file) {
        file_dialog->w->label = file_dialog->fp->selected_file;
        expose_widget(file_dialog->w);
    }
}

static void reload_file_entrys(FileDialog *file_dialog) {
    clear(file_dialog->ft);
    fp_get_files(file_dialog->fp,file_dialog->fp->path, 0);
    file_dialog->ft = add_listview(file_dialog->w, "", 20, 90, 620, 225);
    file_dialog->ft->parent_struct = file_dialog;
    file_dialog->ft->func.value_changed_callback = file_released_callback;
    int set_f = set_files(file_dialog);
    center_widget(file_dialog->w,file_dialog->ft);
    listview_set_active_entry(file_dialog->ft, set_f);
    widget_show_all(file_dialog->w);
}

static void combo_response(void *w_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    FileDialog *file_dialog = (FileDialog *)w->parent_struct;
    Widget_t* menu =  w->childlist->childs[1];
    Widget_t* view_port =  menu->childlist->childs[0];
    if(!childlist_has_child(view_port->childlist)) return ;
    Widget_t *entry = view_port->childlist->childs[(int)adj_get_value(w->adj)];
    free(file_dialog->fp->path);
    file_dialog->fp->path = NULL;
    asprintf(&file_dialog->fp->path, "%s",entry->label);
    assert(file_dialog->fp->path != NULL);
    reload_file_entrys(file_dialog);
}

static void button_ok_callback(void *w_, void* user_data) {
   Widget_t *w = (Widget_t*)w_;
    FileDialog *file_dialog = (FileDialog *)w->parent_struct;
    if (w->flags & HAS_POINTER && !*(int*)user_data){
        if(!file_dialog->fp->selected_file) {
            set_selected_file(file_dialog);
        }
        if(file_dialog->fp->selected_file) {
            file_dialog->parent->func.dialog_callback(file_dialog->parent,&file_dialog->fp->selected_file);
            file_dialog->send_clear_func = false;
        }
        destroy_widget(file_dialog->w,file_dialog->w->app);
   }
}

static void reload_all(FileDialog *file_dialog) {
    Widget_t* menu =  file_dialog->ct->childlist->childs[1];
    Widget_t* view_port =  menu->childlist->childs[0];
    if(!childlist_has_child(view_port->childlist)) return ;
    Widget_t *entry = view_port->childlist->childs[(int)adj_get_value(file_dialog->ct->adj)];
    free(file_dialog->fp->path);
    file_dialog->fp->path = NULL;
    asprintf(&file_dialog->fp->path, "%s",entry->label);
    assert(file_dialog->fp->path != NULL);
    clear(file_dialog->ft);
    clear(file_dialog->ct);
    int ds = fp_get_files(file_dialog->fp,file_dialog->fp->path, 1);
    file_dialog->ct = add_combobox(file_dialog->w, "", 20, 40, 580, 30);
    center_widget(file_dialog->w,file_dialog->ct);
    file_dialog->ct->parent_struct = file_dialog;
    file_dialog->ct->func.value_changed_callback = combo_response;
    file_dialog->ft = add_listview(file_dialog->w, "", 20, 90, 620, 225);
    file_dialog->ft->parent_struct = file_dialog;
    file_dialog->ft->func.value_changed_callback = file_released_callback;
    int set_f = set_files(file_dialog);
    center_widget(file_dialog->w,file_dialog->ft);
    set_dirs(file_dialog);
    combobox_set_active_entry(file_dialog->ct, ds);
    listview_set_active_entry(file_dialog->ft, set_f);
    widget_show_all(file_dialog->w);
}

static void open_dir_callback(void *w_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    FileDialog *file_dialog = (FileDialog *)w->parent_struct;
    if (w->flags & HAS_POINTER && !*(int*)user_data){
        reload_all(file_dialog);
    }
}

static void button_hidden_callback(void *w_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    FileDialog *file_dialog = (FileDialog *)w->parent_struct;
    if (w->flags & HAS_POINTER) {
        file_dialog->fp->show_hidden = adj_get_value(w->adj) ? true : false;
        reload_all(file_dialog);
    }
}

static void set_filter_callback(void *w_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    FileDialog *file_dialog = (FileDialog *)w->parent_struct;
    if (file_dialog->fp->use_filter != (int)adj_get_value(w->adj)) {
        file_dialog->fp->use_filter = (int)adj_get_value(w->adj);
        Widget_t* menu =  w->childlist->childs[1];
        Widget_t* view_port =  menu->childlist->childs[0];
        if(!childlist_has_child(view_port->childlist)) return ;
        Widget_t *entry = view_port->childlist->childs[(int)adj_get_value(w->adj)];
        free(file_dialog->fp->filter);
        file_dialog->fp->filter = NULL;
        asprintf(&file_dialog->fp->filter, "%s",entry->label);
        assert(file_dialog->fp->filter != NULL);

        reload_file_entrys(file_dialog);
    }
}

static void fd_mem_free(void *w_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    FileDialog *file_dialog = (FileDialog *)w->parent_struct;
    if(file_dialog->icon) {
        XFreePixmap(w->app->dpy, (*file_dialog->icon));
        file_dialog->icon = NULL;
    }
    if(file_dialog->send_clear_func)
        file_dialog->parent->func.dialog_callback(file_dialog->parent,NULL);
    fp_free(file_dialog->fp);
    free(file_dialog->fp);
    free(file_dialog);
}

Widget_t *open_file_dialog(Widget_t *w, const char *path, const char *filter) {
    FileDialog *file_dialog = (FileDialog*)malloc(sizeof(FileDialog));
    
    file_dialog->fp = (FilePicker*)malloc(sizeof(FilePicker));
    fp_init(file_dialog->fp, (path) ? path : "/");
    file_dialog->parent = w;
    file_dialog->send_clear_func = true;
    file_dialog->icon = NULL;

    file_dialog->w = create_window(w->app, DefaultRootWindow(w->app->dpy), 0, 0, 660, 420);
    file_dialog->w->flags |= HAS_MEM;
    file_dialog->w->parent_struct = file_dialog;
    widget_set_title(file_dialog->w, "File Selector");
    file_dialog->w->func.expose_callback = draw_window;
    file_dialog->w->func.mem_free_callback = fd_mem_free;
    widget_set_icon_from_png(file_dialog->w,file_dialog->icon,LDVAR(directory_png));

    file_dialog->ct = add_combobox(file_dialog->w, "", 20, 40, 580, 30);
    file_dialog->ct->parent_struct = file_dialog;
    file_dialog->ct->func.value_changed_callback = combo_response;

    file_dialog->sel_dir = add_button(file_dialog->w, "\u23CE", 610, 40, 30, 30);
    file_dialog->sel_dir->parent_struct = file_dialog;
    file_dialog->sel_dir->scale.gravity = CENTER;
    add_tooltip(file_dialog->sel_dir,"Open sub-directory's");
    file_dialog->sel_dir->func.value_changed_callback = open_dir_callback;

    file_dialog->ft = add_listview(file_dialog->w, "", 20, 90, 620, 225);
    file_dialog->ft->parent_struct = file_dialog;
    file_dialog->ft->func.value_changed_callback = file_released_callback;

    int ds = fp_get_files(file_dialog->fp,file_dialog->fp->path, 1);   
    int set_f = set_files(file_dialog); 
    set_dirs(file_dialog);
    combobox_set_active_entry(file_dialog->ct, ds);
    listview_set_active_entry(file_dialog->ft, set_f);

    file_dialog->w_quit = add_button(file_dialog->w, "\u2620", 580, 350, 60, 60);
    file_dialog->w_quit->parent_struct = file_dialog;
    file_dialog->w_quit->scale.gravity = CENTER;
    add_tooltip(file_dialog->w_quit,"Exit file selector");
    file_dialog->w_quit->func.value_changed_callback = button_quit_callback;

    file_dialog->w_okay = add_button(file_dialog->w, "\u2713", 510, 350, 60, 60);
    file_dialog->w_okay->parent_struct = file_dialog;
    file_dialog->w_okay->scale.gravity = CENTER;
    add_tooltip(file_dialog->w_okay,"Load selected file");
    file_dialog->w_okay->func.value_changed_callback = button_ok_callback;

    file_dialog->set_filter = add_combobox(file_dialog->w, "", 360, 355, 120, 30);
    file_dialog->set_filter->parent_struct = file_dialog;
    combobox_add_entry(file_dialog->set_filter,"all");
    combobox_add_entry(file_dialog->set_filter,"application");
    combobox_add_entry(file_dialog->set_filter,"audio");
    combobox_add_entry(file_dialog->set_filter,"font");
    combobox_add_entry(file_dialog->set_filter,"image");
    combobox_add_entry(file_dialog->set_filter,"text");
    combobox_add_entry(file_dialog->set_filter,"video");
    combobox_add_entry(file_dialog->set_filter,"x-content");
    if(filter !=NULL && strlen(filter))
        combobox_add_entry(file_dialog->set_filter,filter);
    combobox_set_active_entry(file_dialog->set_filter, 0);
    file_dialog->set_filter->func.value_changed_callback = set_filter_callback;
    if(filter !=NULL && strlen(filter))
        combobox_set_active_entry(file_dialog->set_filter, 8);
    add_tooltip(file_dialog->set_filter->childlist->childs[0], "File filter type");

    file_dialog->w_hidden = add_check_button(file_dialog->w, "", 20, 365, 20, 20);
    file_dialog->w_hidden->parent_struct = file_dialog;
    file_dialog->w_hidden->scale.gravity = CENTER;
    add_tooltip(file_dialog->w_hidden,"Show hidden files and folders");
    file_dialog->w_hidden->func.value_changed_callback = button_hidden_callback;

    widget_show_all(file_dialog->w);
    return file_dialog->w;
}

/*---------------------------------------------------------------------
-----------------------------------------------------------------------	
				add_file_button
-----------------------------------------------------------------------
----------------------------------------------------------------------*/

static void fdialog_response(void *w_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    FileButton *filebutton = (FileButton *)w->parent_struct;
    if(user_data !=NULL) {
        char *tmp = strdup(*(const char**)user_data);
        free(filebutton->last_path);
        filebutton->last_path = NULL;
        filebutton->last_path = strdup(dirname(tmp));
        filebutton->path = filebutton->last_path;
        free(tmp);
    }
    w->func.user_callback(w,user_data);
    filebutton->is_active = false;
    adj_set_value(w->adj,0.0);
}

static void fbutton_callback(void *w_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    FileButton *filebutton = (FileButton *)w->parent_struct;
    if (w->flags & HAS_POINTER && adj_get_value(w->adj)){
        filebutton->w = open_file_dialog(w,filebutton->path,filebutton->filter);
        filebutton->is_active = true;
    } else if (w->flags & HAS_POINTER && !adj_get_value(w->adj)){
        if(filebutton->is_active)
            destroy_widget(filebutton->w,w->app);
    }
}

static void fbutton_mem_free(void *w_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    FileButton *filebutton = (FileButton *)w->parent_struct;
    free(filebutton->last_path);
    filebutton->last_path = NULL;
    free(filebutton);
    filebutton = NULL;
}

Widget_t *add_file_button(Widget_t *parent, int x, int y, int width, int height,
                           const char *path, const char *filter) {
    FileButton *filebutton = (FileButton*)malloc(sizeof(FileButton));
    filebutton->path = path;
    filebutton->filter = filter;
    filebutton->last_path = NULL;
    filebutton->w = NULL;
    filebutton->is_active = false;
    Widget_t *fbutton = add_image_toggle_button(parent, "", x, y, width, height);
    fbutton->parent_struct = filebutton;
    fbutton->flags |= HAS_MEM;
    widget_get_png(fbutton, LDVAR(directory_open_png));
    fbutton->scale.gravity = CENTER;
    fbutton->func.mem_free_callback = fbutton_mem_free;
    fbutton->func.value_changed_callback = fbutton_callback;
    fbutton->func.dialog_callback = fdialog_response;
    return fbutton;
}
