//-----------------------------------------------------
// name : "guitarix"
// version : "0.02.8"
// author : "brummer"
// contributors : "Julius O. Smith (jos at ccrma.stanford.edu)"
// license : "GPL"
// copyright : "(c)brummer 2008"
// reference : "http://ccrma.stanford.edu/realsimple/faust_strings/"
//
// Code prototype generated with Faust 0.9.9.4f (http://faust.grame.fr)
//-----------------------------------------------------

/* link with  */
#include <sys/ioctl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <cstring>
#include <cstdlib>
#include <dlfcn.h>

// #include <X11/Xlib.h>
// #include <X11/cursorfont.h>

#include <iostream>
#include <fstream>

#include <libgen.h>
#include <jack/jack.h>

using namespace std;

// On Intel set FZ (Flush to Zero) and DAZ (Denormals Are Zero)
// flags to avoid costly denormals
#ifdef __SSE__
#include <xmmintrin.h>
#ifdef __SSE2__
#define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8040)
#else
#define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8000)
#endif
#else
#define AVOIDDENORMALS
#endif

inline void *aligned_calloc(size_t nmemb, size_t size)
{
    return (void*)((size_t)(calloc((nmemb*size)+15,sizeof(char)))+15 & ~15);
}

// g++ -O3 -pipe  -march=native -mfpmath=sse -ffast-math -lm -ljack `gtk-config --cflags --libs` ex2.cpp

#define max(x,y) (((x)>(y)) ? (x) : (y))
#define min(x,y) (((x)<(y)) ? (x) : (y))

// ------------------define the parameter reading, take code from jack_capture -----------------------------------
#define OPTARGS_CHECK_GET(wrong,right) lokke==argc-1?(fprintf(stderr,"Must supply argument for '%s'\n",argv[lokke]),exit(-2),wrong):right
#define OPTARGS_BEGIN(das_usage) {int lokke;const char *usage=das_usage;for(lokke=1;lokke<argc;lokke++){char *a=argv[lokke];if(!strcmp("--help",a)||!strcmp("-h",a)){fprintf(stderr,usage);return 0;
#define OPTARG(name,name2) }}else if(!strcmp(name,a)||!strcmp(name2,a)){{
#define OPTARG_GETSTRING() OPTARGS_CHECK_GET("",argv[++lokke])
#define OPTARGS_END }else{fprintf(stderr,usage);return(-1);}}}


inline int		lsr (int x, int n)
{
    return int(((unsigned int)x) >> n);
}

inline int 		int2pow2 (int x)
{
    int r=0;
    while ((1<<r)<x) r++;
    return r;
}

#include "guitarixgui_v2.cpp"
#include "guitarixgtkfunk.cpp"


// create main window
GTKUI::GTKUI(char * name, int* pargc, char*** pargv)
{
    if (!fInitialized)
    {
        gtk_init(pargc, pargv);
        fInitialized = true;
    }
    /*-- set rc file overwrite it with export--*/

    //setenv("GUITARIX_RC_PATH", "/usr/share/guitarix/guitarix.rc", 0);
    gtk_rc_parse(rcpath);
    /*-- Check for working directory to save and load presets --*/
    const char*	  home;
    const char*      pathname = ".guitarix";
    char                dirname[256];
    home = getenv ("HOME");
    if (home == 0) home = ".";
    snprintf(dirname, 256, "%s/%s", home, pathname);
    Exists( dirname);
    /*-- Declare the GTK Widgets --*/
    fWindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    /*---------------- set window defaults ----------------*/
    gtk_window_set_resizable(GTK_WINDOW (fWindow) , FALSE);
    gtk_window_set_title (GTK_WINDOW (fWindow), name);
    gtk_window_set_icon_from_file(GTK_WINDOW (fWindow),  "/usr/share/pixmaps/guitarix.png", NULL);
    /*---------------- singnals ----------------*/
    gtk_signal_connect (GTK_OBJECT (fWindow), "delete_event", GTK_SIGNAL_FUNC (delete_event), NULL);
    gtk_signal_connect (GTK_OBJECT (fWindow), "destroy", GTK_SIGNAL_FUNC (destroy_event), NULL);

    /*---------------- create boxes ----------------*/
    fTop = 0;
    fBox[fTop] = gtk_vbox_new (homogene, 4);
    fMode[fTop] = kBoxMode;

    /*---------------- add mainbox to main window ---------------*/
    gtk_container_add (GTK_CONTAINER (fWindow), fBox[fTop]);

    fStopped = false;
}

#include "guitarixvirtui.cpp"

void GTKUI::show()
{
    assert(fTop == 0);
    gtk_widget_show  (fBox[0]);
    gtk_widget_show  (fWindow);
}

/**
 * Update all user items reflecting zone z
 */

static gboolean callUpdateAllGuis(gpointer)
{
    UI::updateAllGuis();
    return TRUE;
}

void GTKUI::run_nogui()
{
    char c;
    printf("Type 'q' to quit\nor \ntype 'g' to load the GUI\n>");
    while (strcmp(stopit, "go") == 0)
    {
        sleep(1);
        if ((c = getchar()) == 'g')
        {
            printf("Ok,  please use the GUI for input now\n>");
            assert(fTop == 0);
            gtk_widget_show  (fBox[0]);
            gtk_widget_show  (fWindow);
            gtk_timeout_add(40, callUpdateAllGuis, 0);
            gtk_main ();
            assert(fTop == 0);
            printf("quit the GUI\nType 'q' to quit\nor \ntype 'g' to load the GUI\n>");
        }
        else if (c  == 'q')
        {
            stopit = "stop";
            checky = 0.0;
            printf("bye bye\n");
        }
        else if (c  == ' ')
        {
            printf("what did you think happen if you enter a empty space ?\n>");
        }
        else if ((int(c)  > 48) && (int(c)  < 55))
        {
            const char*	  home;
            const char*      prename = "guitarixpre";
            char                rcfilenamere[256];
            int lin;
            int lint;
            home = getenv ("HOME");
            if (home == 0) home = ".";
            snprintf(rcfilenamere, 256, "%s/.guitarix/%src", home, prename);
            lin = int(c) - 49;
            lint = lin + 1;
            interface->recallpreState(rcfilenamere, lin);
            printf("load preset %u \n>",  lint);
        }
        else if (c  == '0')
        {
            const char*	  home;
            const char*      prename = "guitarix";
            char                rcfilenamere[256];
            int lin;
            int lint;
            home = getenv ("HOME");
            if (home == 0) home = ".";
            snprintf(rcfilenamere, 256, "%s/.guitarix/%src", home, prename);
            lin = int(c) - 49;
            lint = lin + 1;
            interface->recallState(rcfilenamere);
            printf("load preset %u \n>",  lint);
        }
    }
    stop();
}


void GTKUI::run()
{
    if (strcmp(param, "nogui") == 0)
    {
        run_nogui();
    }
    else
    {
        assert(fTop == 0);
        gtk_widget_show  (fBox[0]);
        gtk_widget_show  (fWindow);
        gtk_timeout_add(40, callUpdateAllGuis, 0);
        gtk_main ();
        stop();
    }
}

#include "guitarixcompute.cpp"
#include "guitarixjack.cpp"

