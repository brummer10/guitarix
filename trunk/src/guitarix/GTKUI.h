
/******************************************************************************
*******************************************************************************

								GRAPHIC USER INTERFACE
								  gtk interface
	GTKUI.h
	header file for the virtuell discriptions from the GTK_WIDGETS used in guitarix
*******************************************************************************
*******************************************************************************/

#ifndef GTKUI_H
#define GTKUI_H


class GTKUI : public UI
{
private :
    static bool			fInitialized;
    static list<UI*>	fGuiList;

protected :
    //GtkWidget* 	fWindow;
    int			fTop;
    GtkWidget* 	fBox[stackSize];
    int 		fMode[stackSize];
    bool		fStopped;

    GtkWidget* addWidget(const char* label, GtkWidget* w);
    virtual void pushBox(int mode, GtkWidget* w);

public :

    static const gboolean expand = TRUE;
    static const gboolean fill = TRUE;
    static const gboolean homogene = FALSE;

    GTKUI(char * name, int* pargc, char*** pargv);

    // -- layout groups
    virtual void openFrameBox(const char* label);
    virtual void openHorizontalBox(const char* label = "");
    virtual void openVerticalBox(const char* label = "");
    virtual void openVerticalMidiBox(const char* label = "");
    virtual void openDialogBox(const char* label, float* zone);
    virtual void openEventBox(const char* label = "");
    virtual void openHandleBox(const char* label = "");
    virtual void openExpanderBox(const char* label, float* zone);
    virtual void openTabBox(const char* label = "");
    virtual void closeBox();

    // -- active widgets
    virtual void addMenu();
    virtual void addButton(const char* label, float* zone);
    virtual void addToggleButton(const char* label, float* zone);
    virtual void addPToggleButton(const char* label, float* zone);
    virtual void addJToggleButton(const char* label, float* zone);
    virtual void addCheckButton(const char* label, float* zone);
    virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step);
    virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step);
    virtual void addregler(const char* label, float* zone, float init, float min, float max, float step);
    virtual void addbigregler(const char* label, float* zone, float init, float min, float max, float step);
    virtual void addslider(const char* label, float* zone, float init, float min, float max, float step);
    virtual void addtoggle(const char* label, float* zone);
    virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step);
    virtual void addNumDisplay(const char* label, float* zone);
    virtual void addLiveWaveDisplay(const char* label, float* zone , float* zone1);
    virtual void addStatusDisplay(const char* label, float* zone );
    virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max);
    virtual void addVerticalBargraph(const char* label, float* zone, float min, float max);

    virtual void show();
    virtual void run();
    virtual void run_nogui();

};

#endif // GTKUI_H
