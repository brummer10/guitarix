/*
  * Copyright (C) 2009 Hermann Meyer
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
  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

/******************************************************************************
*******************************************************************************

	jconv_settings.h
	
	part of guitarix, create a configfile for jconv and run it. These are the 
	virtual declarations for guitarix by hermann meyer
*******************************************************************************
*******************************************************************************/

#ifndef JCONV_SETTINGSH
#define JCONV_SETTINGSH

class JCONV_SETTINGS 
{
private:

public:

JCONV_SETTINGS();
~JCONV_SETTINGS();

virtual void get_jconfset ();
virtual void fileselected( GtkWidget *widget, gpointer data );
virtual void runjconv( GtkWidget *widget, gpointer data );

};

#endif

