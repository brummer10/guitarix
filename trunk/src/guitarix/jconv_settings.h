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

