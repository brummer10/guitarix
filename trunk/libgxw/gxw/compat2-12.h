#ifndef GSEAL
#define GSEAL(x) x
#define gtk_widget_get_state(w) GtkStateType(GTK_WIDGET_STATE(w))
#define gtk_widget_has_default(w) GTK_WIDGET_HAS_DEFAULT(w)
#define gtk_widget_get_can_default(w) GTK_WIDGET_CAN_DEFAULT(w)
#define gtk_widget_has_focus(w) GTK_WIDGET_HAS_FOCUS(w)
#define gtk_widget_has_grab(w) GTK_WIDGET_HAS_GRAB(w)
#define gtk_widget_get_visible(w) GTK_WIDGET_VISIBLE(w)
#define gtk_widget_is_drawable(w) GTK_WIDGET_DRAWABLE(w)
#define gtk_widget_set_can_focus(w, s) GTK_WIDGET_SET_FLAGS(w, GTK_CAN_FOCUS)
#define gtk_widget_set_receives_default(w, s) GTK_WIDGET_SET_FLAGS(w, GTK_CAN_DEFAULT)
#define gtk_widget_set_has_window(w, s) {if(s)GTK_WIDGET_UNSET_FLAGS(w, GTK_NO_WINDOW); else GTK_WIDGET_SET_FLAGS(w, GTK_NO_WINDOW);}
#define gtk_widget_get_window(w) ((w)->window)
#define gtk_widget_get_requisition(w, r) (*r = (w)->requisition)
#define gtk_adjustment_get_lower(w) ((w)->lower)
#define gtk_adjustment_get_upper(w) ((w)->upper)
#define gtk_adjustment_configure(w, v, l, u, s, p, pp) {w->value=v;w->lower=l;w->upper=u;w->step_increment=s;w->page_increment=p;w->page_size=pp;}
#define gtk_menu_item_get_label(w) gtk_label_get_label(GTK_LABEL(gtk_bin_get_child(GTK_BIN(w))))
#endif
