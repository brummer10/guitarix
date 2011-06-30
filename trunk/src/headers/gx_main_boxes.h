/*
 * Copyright (C) 2009, 2010 Hermann Meyer, James Warden, Andreas Degert
 * Copyright (C) 2011 Pete Shorthose
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
 *
 *    This file is part of the guitarix GUI main class
 *    Note: this header file depends on gx_ui.h and
 *    gx_main_interface.h
 * 
 * ----------------------------------------------------------------------------
 */

/* ------- This is part of the GUI namespace ------- */


#pragma once

#ifndef GX_UI
#include "gx_ui.h"
#endif

#ifndef GX_MAIN_INTERFACE
#include "gx_main_interface.h"
#endif

#include <gtkmm/liststore.h>
#include <gtkmm/window.h>
#include <gtkmm/frame.h>
#include <gtkmm/accelgroup.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/fixed.h>
#include <gtkmm/eventbox.h>
#include <gtkmm/notebook.h>
#include <gxwmm/paintbox.h>
#include <gtkmm/radiomenuitem.h>
#include <gtkmm/paned.h>

namespace gx_gui
{

/****************************************************************/

class GxTBox
{
public:
	Gtk::VBox m_box;
	ToggleCheckButton m_tcb;
	GxTBox(gx_ui::GxUI& ui);
	virtual ~GxTBox();
};

/****************************************************************/

class GxVBox
{
public:
	Gtk::VBox m_box;
	Gtk::Label m_label;
	GxVBox(gx_ui::GxUI& ui);
	virtual ~GxVBox();
};

/****************************************************************/

class GxHBox
{
public:
	Gtk::HBox m_box;
	Gtk::Label m_label;
	Gtk::Frame m_frame;
	GxHBox(gx_ui::GxUI& ui);
	virtual ~GxHBox();
};

/****************************************************************/

class GxFixedBox
{
public:
	Gtk::Fixed m_fixed;
	Gtk::VBox m_box;
	GxFixedBox(gx_ui::GxUI& ui);
	virtual ~GxFixedBox();
};

/****************************************************************/

class GxPaintBox
{

public:
	
	Gtk::HBox m_box;
	Gxw::PaintBox m_paintbox;
	GxPaintBox(gx_ui::GxUI& ui, const char *expose_funk);
	~GxPaintBox();
};

/****************************************************************/

class GxEventBox
{
public:
	Gtk::HBox m_box;
	Gtk::HBox m_hbox;
	Gtk::HBox m_pbox;
	Gtk::HBox m_tbox;
	Gtk::EventBox m_eventbox;
	Gtk::HBox m_fbox;
	Gtk::HBox m_fixedbox;
	Gtk::Label m_label;
	GxEventBox(gx_ui::GxUI& ui);
	virtual ~GxEventBox();
};

/****************************************************************/

class GxMainBox
{
public:
	Gtk::HBox m_box;
	Gtk::HBox m_hbox;
	Gtk::HBox m_pbox;
	Gtk::HBox m_tbox;
	Gtk::HBox m_fbox;
	Gtk::EventBox m_eventbox;
	Gtk::Fixed m_fixedbox;
	Gtk::Label m_label;
	Gxw::PaintBox m_paintbox;
	GxMainBox(gx_ui::GxUI& ui,const char *expose_funk);
	virtual ~GxMainBox();
};

/****************************************************************/

class GxMidiBox
{
public:
	Gtk::HBox m_box;
	Gtk::EventBox m_eventbox;
	Gxw::PaintBox m_paintbox;
	ToggleCheckButton m_tcb;
	UiSwitch* unit_on_off;
	Gtk::HBox m_bbox;
	Gtk::Fixed m_fixedbox;
	GxMidiBox(gx_ui::GxUI& ui,const char *expose_funk);
	virtual ~GxMidiBox();
};

/****************************************************************/

class GxNotebookBox
{
public:
	Gtk::Notebook m_box;
	GxNotebookBox(gx_ui::GxUI& ui);
	virtual ~GxNotebookBox();
};

/****************************************************************/

class GxMoveBox
{
public:
	Gtk::Label m_label;
	Gtk::Label m_label1;
	Gtk::Fixed m_fixed;
	Gxw::PaintBox m_paintbox;
	Gtk::Button m_button;
	Gtk::Button m_button1;
	GxMoveBox(gx_ui::GxUI& ui);
	virtual ~GxMoveBox();
};

/****************************************************************/

class GxDialogButtonBox
{
public:
	Gtk::HBox box;
	UiSwitchBool show_dialog;
	GxDialogButtonBox(gx_ui::GxUI& ui, Parameter& param_dialog);
};

/****************************************************************/

class GxDialogWindowBox
{
private:
	void on_dialog_button_toggled();
	void on_reset_button_pressed();
	void on_dialog_menu_activate();
	bool on_window_delete_event(GdkEventAny* event);
	Glib::ustring group_id;
public:
	Gtk::HBox box;
	Gtk::HBox box1;
	Gxw::PaintBox paintbox;
	Gtk::HBox box4;
	Gtk::HBox box5;
	Gtk::HBox box6;
	UiSwitch* unit_on_off;
	MenuCheckItem menuitem;
	Gtk::Button reset_button;
	Gtk::Button reset_button1;
	ToggleCheckButton m_tcb;
	Gtk::ToggleButton& dialog_button;
	Gtk::Window m_regler_tooltip_window;
	GxDialogWindowBox(gx_ui::GxUI& ui, const char *expose_funk, Parameter& param_dialog, Parameter& param_switch, Gtk::ToggleButton& button,GtkWidget * Caller);
	~GxDialogWindowBox();
};

/****************************************************************/

class GxWindowBox
{
private:
	bool on_window_delete_event(GdkEventAny* event,gpointer d );
	bool on_button_pressed(GdkEventButton* event);

public:
	Gtk::HBox window;

	Gtk::HBox box;
	Gtk::HBox box1;

	Gtk::VBox rbox;
	Gtk::Window m_regler_tooltip_window;
	ToggleCheckButton m_tmono_rack;
	ToggleCheckButton m_tstereo_rack;
	GxWindowBox(gx_ui::GxUI& ui, 
		Glib::ustring titl,GtkWidget * d);
	~GxWindowBox();
};

/****************************************************************/

class GxScrollBox
{
private:
	
	bool on_window_delete_event(GdkEventAny* event,gpointer d );
	bool on_button_pressed(GdkEventButton* event);
	void on_rack_reorder_vertical();
	void on_rack_reorder_horizontal();
	
public:
	Gtk::HBox window;
	Gtk::ScrolledWindow m_scrolled_window; 
	Gtk::ScrolledWindow m_scrolled_window2; 
	Gtk::HBox box;
	Gtk::HBox box1;
	Gxw::PaintBox paintbox1;
	Gtk::VBox rbox;
	Gtk::VBox vbox;
	RadioCheckItem      fOrderhRack;
	RadioCheckItem      fOrdervRack;
	Gtk::RadioMenuItem::Group group;
	GxScrollBox(gx_ui::GxUI& ui, 
		const char *pb_2, Glib::ustring titl,GtkWidget * d);
	~GxScrollBox();
};

/****************************************************************/

class GxToolBox
{
private:
	bool on_window_delete_event(GdkEventAny* event,gpointer d );
	bool on_button_pressed(GdkEventButton* event);
public:
	Gtk::VBox window;
	Gtk::ScrolledWindow           m_scrolled_window; 
	Gtk::HBox box;
	Gtk::HBox box1;
	Gxw::PaintBox paintbox;
	Gxw::PaintBox paintbox1;
	Gtk::VBox rbox;
	Gtk::Window m_regler_tooltip_window;
	ToggleCheckButton m_tmono_rack;
	ToggleCheckButton m_tstereo_rack;
	GxToolBox(gx_ui::GxUI& ui, 
		const char *pb_2, Glib::ustring titl,GtkWidget * d);
	~GxToolBox();
};

/****************************************************************/

}/* end of gx_gui namespace */

