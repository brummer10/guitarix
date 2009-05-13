
/******************************************************************************
*******************************************************************************

								funktions from guitarix
	guitarix.cpp
	here are the unsortet global funktions from guitarix 
*******************************************************************************
*******************************************************************************/


// global static fields
GtkWidget* fWindow, *menul, *menus, *pb, *midibox, *fbutton, *label1, *menuh;
GdkPixbuf*   ib, *ibm, *ibr;
GtkStatusIcon*  status_icon;
GtkWidget* livewa;

static float      togglebutton1;
static float      checkbutton7;

float      checkbox7 = 1.0;
float       	 checky = 1.0;
float               cap = 0;
float               capas = 0;
float jackframe; // jack sample freq
float cpu_load; // jack cpu_load
float  *get_frame;
float *checkfreq;

const char*     stopit = "go";
const char*     rcpath = " " ;
string  jconvwav ; 

int offcut;
int lenghtcut;
int cm = 0;
int shownote = 2;
int view_mode = 0;
int showwave = 0;
int playmidi = 0;
int showit = 0;
int		gNumOutChans;
int frag;   // jack frame size
int NO_CONNECTION = 0;

FILE*              control_stream;
FILE*              control_stream1;
UI*                 interface;

jack_client_t*      client ;
//jack_client_t*      midi_client;
jack_port_t *output_ports[256];
jack_port_t *input_ports[256];
jack_port_t *midi_output_ports;
jack_nframes_t time_is;
jack_ringbuffer_t *jack_ringbuffer;
jack_nframes_t  jackframes; 


// check version and if directory exists and create it if it not exist
bool Exists(const char* Path)
{
    struct stat my_stat;
    if  ( !stat(Path, &my_stat) != 0)
    {
        char          rcfilename[256];
        const char*	  home;
        home = getenv ("HOME");
        snprintf(rcfilename, 256, "%s/.%s-0.03.3", home, "guitarix/version");
        if  ( !stat(rcfilename, &my_stat) == 0)
        {
            snprintf(rcfilename, 256, "%s %s/.%s", "rm -f " , home, "guitarix/version-*");
            system (rcfilename);
            snprintf(rcfilename, 256, "%s/.%s-0.03.3", home, "guitarix/version");
            ofstream f(rcfilename);
            string cim = "guitarix-0.03.9";
            f <<  cim <<endl;
            f.close();
            snprintf(rcfilename, 256, "%s %s/.%s", "rm -f " , home, "guitarix/guitarixprerc");
            system (rcfilename);
            snprintf(rcfilename, 256, "%s %s/.%s", "rm -f " , home, "guitarix/guitarixrc");
            system (rcfilename);
            snprintf(rcfilename, 256, "%s %s/.%s", "rm -f " , home, "guitarix/*.conf");
            system (rcfilename);
            snprintf(rcfilename, 256, "%s/.%s", home, "guitarix/resettings");
            ofstream fa(rcfilename);
            cim = "0.12 1 5000 130 1 5000 130 1 0.01 0.64 2 \n0 0.3 0.7 \n20 440 2 \n0.62 0.12 0 \n84 0 -1 9 0 101 4 0 0 34 0 9 1 20 64 12 1 20 0 0 \n-64.0 0.52 10 1.5 1.5 0 \n";
            fa <<  cim <<endl;
            fa.close();
        }
    }
    else if  ( !stat(Path, &my_stat) == 0)
    {
        char                rcfilename[256];
        const char*	  home;
        home = getenv ("HOME");
        system("mkdir $HOME/.guitarix" );
        snprintf(rcfilename, 256, "%s/.%src", home, "guitarix/ja_ca_sset");
        ofstream f(rcfilename);
        string cim = "jack_capture -c 2 --silent --disable-meter --port guitarix:out* ";
        cim += home;
        cim += "/guitarix_session0.wav ";
        f <<  cim <<endl;
        f.close();
        snprintf(rcfilename, 256, "%s/.%s-0.03.3", home, "guitarix/version");
        ofstream fi(rcfilename);
        cim = "guitarix-0.03.9";
        fi <<  cim <<endl;
        fi.close();
        snprintf(rcfilename, 256, "%s/.%s", home, "guitarix/resettings");
        ofstream fa(rcfilename);
        cim = "0.12 1 5000 130 1 5000 130 1 0.01 0.64 2 \n0 0.3 0.7 \n20 440 2 \n0.62 0.12 0 \n84 0 -1 9 0 101 4 0 0 34 0 9 1 20 64 12 1 20 0 0 \n-64.0 0.52 10 1.5 1.5 0 \n";
        fa <<  cim <<endl;
        fa.close();
    }
return TRUE;
}

int Existspix()
{
    int ep = 1;
    struct stat my_stat;
    char          rcfilename[256];
    snprintf(rcfilename, 256, "%s", "/usr/share/pixmaps/guitarix.png");
    char          rcfilename1[256];
    snprintf(rcfilename1, 256, "%s", "/usr/share/pixmaps/guitarix-midi.png");
    char          rcfilename2[256];
    snprintf(rcfilename2, 256, "%s", "/usr/locale/share/pixmaps/guitarix.png");
    char          rcfilename3[256];   
    snprintf(rcfilename3, 256, "%s", "/usr/locale/share/pixmaps/guitarix-midi.png");
    char          rcfilename4[256];   
    snprintf(rcfilename4, 256, "%s", "./guitarix.png");
    char          rcfilename5[256];   
    snprintf(rcfilename5, 256, "%s", "./guitarix-midi.png");
    if (( stat(rcfilename, &my_stat) == 0) && ( stat(rcfilename1, &my_stat) == 0))
    {
      //  gtk_window_set_icon_from_file(GTK_WINDOW (fWindow),  "/usr/share/pixmaps/guitarix.png", NULL);
       // ib =       gtk_window_get_icon (GTK_WINDOW (fWindow));
        GtkWidget *ibf =  gtk_image_new_from_file ("/usr/share/pixmaps/guitarix.png");
        ib = gtk_image_get_pixbuf (GTK_IMAGE(ibf));
        GtkWidget *stim = gtk_image_new_from_file ("/usr/share/pixmaps/guitarix-midi.png");
        ibm = gtk_image_get_pixbuf (GTK_IMAGE(stim));
        GtkWidget *stir = gtk_image_new_from_file ("/usr/share/pixmaps/guitarix-warn.png");
        ibr = gtk_image_get_pixbuf (GTK_IMAGE(stir));
        ep = 0;
    }
    else if (( stat(rcfilename2, &my_stat) == 0) && ( stat(rcfilename3, &my_stat) == 0))
    {
       // gtk_window_set_icon_from_file(GTK_WINDOW (fWindow),  "/usr/locale/share/pixmaps/guitarix.png", NULL);
       // ib =       gtk_window_get_icon (GTK_WINDOW (fWindow));
        GtkWidget *ibf =  gtk_image_new_from_file ("/usr/locale/share/pixmaps/guitarix.png");
        ib = gtk_image_get_pixbuf (GTK_IMAGE(ibf));
        GtkWidget *stim = gtk_image_new_from_file ("/usr/locale/share/pixmaps/guitarix-midi.png");
        ibm = gtk_image_get_pixbuf (GTK_IMAGE(stim));
        GtkWidget *stir = gtk_image_new_from_file ("/usr/locale/share/pixmaps/guitarix-warn.png");
        ibr = gtk_image_get_pixbuf (GTK_IMAGE(stir));
        ep = 0;
    }
    else if (( stat(rcfilename4, &my_stat) == 0) && ( stat(rcfilename5, &my_stat) == 0))
    {
      //  gtk_window_set_icon_from_file(GTK_WINDOW (fWindow),  "guitarix.png", NULL);
      //  ib =       gtk_window_get_icon (GTK_WINDOW (fWindow));
        GtkWidget *ibf =  gtk_image_new_from_file ("./guitarix.png");
        ib = gtk_image_get_pixbuf (GTK_IMAGE(ibf));
        GtkWidget *stim = gtk_image_new_from_file ("./guitarix-midi.png");
        ibm = gtk_image_get_pixbuf (GTK_IMAGE(stim));
        GtkWidget *stir = gtk_image_new_from_file ("./guitarix-warn.png");
        ibr = gtk_image_get_pixbuf (GTK_IMAGE(stir));
        ep = 0;
    }
 return ep;
}

// convert int to string
void IntToString(int i, string & s)
{
    s = "";
    if (i == 0)
    {
        s = "0";
        return;
    }
    if (i < 0)
    {
        s += '-';
        i = -i;
    }
    int count = log10(i);
    while (count >= 0)
    {
        s += ('0' + i/pow(10.0, count));
        i -= static_cast<int>(i/pow(10.0,count)) * static_cast<int>(pow(10.0,count));
        count--;
    }
}

// use jack_capture for record the session, open a write stream for controll the stop funktion.
bool capture(const char* capturas)
{
    capas += 1;
    control_stream = popen (capturas, "w");
return TRUE;
}

bool		GTKUI::fInitialized = false;
list<UI*>	UI::fGuiList;

//----menu funktion play stop
void play_function (GtkCheckMenuItem *menuitem, gpointer checkplay)
{
    checky = 1.0;
}
void stop_function (GtkCheckMenuItem *menuitem, gpointer checkplay)
{
    checky = 0.0;
}

//----menu funktion meterbridge
void meterbridge (GtkCheckMenuItem *menuitem, gpointer checkplay)
{
    if (gtk_check_menu_item_get_active(menuitem) == TRUE)
    {
        system ("meterbridge -n meterbridge_guitarix_in_out -t sco guitarix:in_0  guitarix:out_0 > /dev/null &");
    }
    else
    {
        if (system(" pidof meterbridge > /dev/null") == 0)
        {
            system("kill -15 `pidof meterbridge ` > /dev/null");
        }
    }
}

void show_view (GtkCheckMenuItem *menuitem, gpointer checkplay)
{
    if (gtk_check_menu_item_get_active(menuitem) == TRUE)
    {
        showwave = 1;
     //   gtk_widget_hide( placehold);
        gtk_widget_show(livewa);
    }
    else
    {
       showwave = 0;
        gtk_widget_hide( livewa);
       // gtk_widget_show(placehold);
    }
}

//----menu funktion show note
void show_note (GtkCheckMenuItem *menuitem, gpointer checkplay)
{
    if (gtk_check_menu_item_get_active(menuitem) == TRUE)
    {
        shownote = 1;
        gtk_widget_show(pb);
    }
    else
    {
       shownote = 0;
        gtk_widget_hide(pb);
    }
}

void midi_note (GtkCheckMenuItem *menuitem, gpointer checkplay)
{
    if (gtk_check_menu_item_get_active(menuitem) == TRUE)
    {
        playmidi = 1;
        gtk_widget_show(midibox);
    }
    else
    {
        playmidi = 0;
        gtk_widget_hide(midibox);
    }
}

// start or stop record when toggle_button record is pressed
void recordit (GtkWidget *widget, gpointer data)
{
// stop record
    if ((togglebutton1 == 0) && (cap == 0))
    {
        if (system(" pidof jack_capture > /dev/null") == 0)
        {
            system("command kill -2 `pidof  jack_capture ` 2> /dev/null") ;
            pclose(control_stream);
        }
    }
// strat record
    else if (togglebutton1 == 1)
    {
        struct stat my_stat;
        char                path[256];
        char                path1[256];
        const char*      prename = "/usr/bin/jack_capture";
        const char*      name = "/usr/local/bin/jack_capture";
        snprintf(path, 256, "%s", prename);
        snprintf(path1, 256, "%s", name);
// check if jack_record is installed in /usr/bin or /usr/local/bin. If not found a messagebox will inform the user
        if (( !stat(path, &my_stat) == 0) && ( !stat(path1, &my_stat) == 0))
        {
            GtkWidget *about, *label, *button;
            about = gtk_dialog_new();
            button  = gtk_button_new_with_label("Ok");
            label = gtk_label_new ("  you need jack_capture <= 0.9.30 by Kjetil S. Matheussen  \n  please look here\n  http://old.notam02.no/arkiv/src/?M=D\n");
            GtkStyle *style = gtk_widget_get_style(label);
            pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
            gtk_widget_modify_font(label, style->font_desc);
            gtk_label_set_selectable(GTK_LABEL(label), TRUE);
            gtk_container_add (GTK_CONTAINER (GTK_DIALOG(about)->vbox), label);
            gtk_container_add (GTK_CONTAINER (GTK_DIALOG(about)->vbox), button);
            g_signal_connect_swapped (button, "clicked",  G_CALLBACK (gtk_widget_destroy), about);
            gtk_widget_show (button);
            gtk_widget_show (label);
            gtk_widget_show (about);
            cap = 1;
            togglebutton1 = 0;
        }
// when everything go's allright, start capture
        else
        {
            const char* capturas = "";
            string bufi;
            const char* home;
            char gfilename[256];
            home = getenv ("HOME");
            if (home == 0) home = ".";
            snprintf(gfilename, 256, "%s%src", home, "/.guitarix/ja_ca_sset");
            ifstream f(gfilename);
            if (f.good())
            {
                getline(f, bufi);
                string ma;
                IntToString(capas,ma);
                std::string a(bufi);
                std::string b(".");
                std::string::size_type in = a.find(b);
                in -= 1;
                if (int(in) != -1) a.replace(in,1,ma);
                bufi = a;
                capturas = bufi.c_str();
                f.close();
            }
            capture(capturas);
        }
    }
}

//----menu funktion load
void load_function1 (GtkMenuItem *menuitem, gpointer load_preset)
{
    JCONV_SETTINGS myJCONV_SETTINGS;
    checkbutton7 = 0;
    interface->updateAllGuis();
    const char*	  home;
    char                rcfilenamere[256];
    char                tmpfilename[256];
    const char*      tmpname = "guitarixtmp";
    const char*      prename = "guitarixpre";
    int lin;
    int zeile=0;
    int l=0;
    GtkWidget* title = gtk_bin_get_child(GTK_BIN(menuitem));
    const gchar* text = gtk_label_get_text (GTK_LABEL(title));
    home = getenv ("HOME");
    if (home == 0) home = ".";
    char                filename[256];
    snprintf(filename, 256, "cp %s/.%s%s%s %s/.%s", home, "guitarix/jconv_", text,".conf", home, "guitarix/jconv_set.conf");
    system(filename);
    snprintf(rcfilenamere, 256, "%s/.guitarix/%src", home, prename);
    snprintf(tmpfilename, 256, "%s/.guitarix/%src", home, tmpname);
    ifstream f(rcfilenamere);
    if (f.good())
    {
        string buffer;
        while (!f.eof())
        {
            getline(f, buffer);
            std::string b(" ");
            std::string::size_type in = buffer.find(b);
            if (int(in) != -1) buffer.erase(in);
            l++;
        }
        zeile = l-1;
    }
    f.close();
    lin = zeile;
    myJCONV_SETTINGS.get_jconfset ();
    interface->recallpreStatebyname(rcfilenamere, tmpfilename, text);
    string ttle = "guitarix ";
    ttle += text;
    const gchar* itle = ttle.c_str();
    gtk_window_set_title (GTK_WINDOW (fWindow), itle);
}

//---- funktion save
void save_functio (const gchar* presname)
{
    const char*	  home;
    const char*      prename = "guitarixpre";
    const char*      tmpname = "guitarixtmp";
    const char*      pathname = ".guitarix";
    char                rcfilenamere[256];
    char                tmpfilename[256];
    char                dirname[256];
    home = getenv ("HOME");
    if (home == 0) home = ".";
    snprintf(tmpfilename, 256, "%s/.guitarix/%src", home, tmpname);
    snprintf(rcfilenamere, 256, "%s/.guitarix/%src", home, prename);
    snprintf(dirname, 256, "%s/%s", home, pathname);
    interface->savepreStatebyname(rcfilenamere, tmpfilename, presname);
    if (cm == 0)
    {
        GtkWidget* menuitem = gtk_menu_item_new_with_label (presname);
        gtk_signal_connect (GTK_OBJECT (menuitem), "activate", GTK_SIGNAL_FUNC (load_function1), NULL);
        gtk_menu_append(GTK_MENU(menul), menuitem);
        gtk_widget_show (menuitem);
    }
    string ttle = "guitarix ";
    ttle += presname;
    const gchar* itle = ttle.c_str();
    gtk_window_set_title (GTK_WINDOW (fWindow), itle);
    char                filename[256];
    snprintf(filename, 256, "cp %s/.%s %s/.%s%s%s", home, "guitarix/jconv_set.conf", home, "guitarix/jconv_", presname,".conf");
    system(filename);
}

//----menu funktion save
void save_function2 (GtkMenuItem *menuitem, gpointer save_preset)
{
    GtkWidget* title = gtk_bin_get_child(GTK_BIN(menuitem));
    const gchar* text = gtk_label_get_text (GTK_LABEL(title));
    save_functio(text);
}

// read name for presset
void get_text(GtkWidget *box)
{
    const gchar* presname = gtk_entry_get_text (GTK_ENTRY(box));
    save_functio(presname);
    if (cm == 0)
    {
        GtkWidget*  menuitem = gtk_menu_item_new_with_label (presname);
        gtk_signal_connect (GTK_OBJECT (menuitem), "activate", GTK_SIGNAL_FUNC (save_function2), NULL);
        gtk_menu_append(GTK_MENU(menus), menuitem);
        gtk_widget_show (menuitem);
    }
    cm = 0;
}

//----menu funktion save
void save_function1 (GtkMenuItem *menuitem, gpointer save_preset)
{
    GtkWidget *about, *button;
    about = gtk_dialog_new();
    button  = gtk_button_new_with_label("Ok");
    GtkWidget * box = gtk_entry_new ();
    gtk_container_add (GTK_CONTAINER (GTK_DIALOG(about)->vbox), box);
    gtk_container_add (GTK_CONTAINER (GTK_DIALOG(about)->vbox), button);
    g_signal_connect_swapped (button, "clicked",  G_CALLBACK (get_text), box);
    g_signal_connect_swapped (button, "clicked",  G_CALLBACK (gtk_widget_destroy), about);
    gtk_widget_show (button);
    gtk_widget_show (box);
    gtk_widget_show (about);
}

//----menu funktion about
static void show_event( GtkWidget *widget, gpointer data )
{
    GtkWidget *about, *label, *button;
    about = gtk_dialog_new();
    button  = gtk_button_new_with_label("Ok");
    label = gtk_label_new ("\n This Aplication is to a large extent provided\n with the marvelous faust compiler.  Yann Orlary\n <http://faust.grame.fr/>\n A large part is based on the work of Julius Orion Smith\n <http://ccrma.stanford.edu/realsimple/faust/>\n and Albert Graef\n <http://www.musikwissenschaft.uni-mainz.de/~ag/ag.html> \n\n\n guitarix 0.02.5 use jack_capture >= 0.9.30 for record\n by Kjetil S. Matheussen \n http://old.notam02.no/arkiv/src/?M=D\n  it will allways record to ~/guitarix_sessionX.xxx \n for impulse response it use jconv \n by  Fons Adriaensen \n  http://www.kokkinizita.net/linuxaudio/index.html \n\n author: Hermann Meyer <brummer-@web.de>\n home: http://brummer.de.hm/guitarfx.html\n");
    GtkStyle *style = gtk_widget_get_style(label);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
    gtk_widget_modify_font(label, style->font_desc);
    gtk_label_set_selectable(GTK_LABEL(label), TRUE);
    gtk_container_add (GTK_CONTAINER (GTK_DIALOG(about)->vbox), label);
    gtk_container_add (GTK_CONTAINER (GTK_DIALOG(about)->vbox), button);
    g_signal_connect_swapped (button, "clicked",  G_CALLBACK (gtk_widget_destroy), about);
    gtk_widget_show (button);
    gtk_widget_show (label);
    gtk_widget_show (about);
}



//--------- class wrapper--------------------------
void flr( GtkWidget *widget, gpointer data )
{
    Resample myResample;
    myResample.fileread(widget, data);
}

void fls( GtkWidget *widget, gpointer data )
{
    JCONV_SETTINGS myJCONV_SETTINGS;
    myJCONV_SETTINGS.fileselected(widget, data);
}

void rjv( GtkWidget *widget, gpointer data )
{
    JCONV_SETTINGS myJCONV_SETTINGS;
    myJCONV_SETTINGS.runjconv(widget, data);
}

void wv( GtkWidget *widget, gpointer data )
{
    GtkWaveView myGtkWaveView;
    myGtkWaveView.gtk_waveview_set_value(widget, data);
}

//--------------------------- jack_capture settings ----------------------------------------
static void show_event1( GtkWidget *widget, gpointer data )
{
    system ("jack_capture_gui2 -o yes -f ~/guitarix_session -n guitarix -p /.guitarix/ja_ca_ssetrc &");
}

static gint delete_event( GtkWidget *widget, GdkEvent *event, gpointer data )
{
    if (system(" pidof meterbridge > /dev/null") == 0)
    {
        system("kill -15 `pidof meterbridge ` 2> /dev/null");
    }
    if (system(" pidof jack_capture > /dev/null") == 0)
    {
        system("command kill -2 `pidof  jack_capture ` 2> /dev/null") ;
        pclose(control_stream);
    }
    if (system(" pidof jconv > /dev/null") == 0)
    {
        system("command kill -2 `pidof  jconv ` 2> /dev/null") ;
        pclose(control_stream1);
    }
    return FALSE;
}

static void destroy_event( GtkWidget *widget, gpointer data )
{
    if (system(" pidof meterbridge > /dev/null") == 0)
    {
        system("kill -15 `pidof meterbridge ` 2> /dev/null");
    }
    if (system(" pidof jack_capture > /dev/null") == 0)
    {
        system("command kill -2 `pidof  jack_capture ` 2> /dev/null") ;
        pclose(control_stream);
    }
    if (system(" pidof jconv > /dev/null") == 0)
    {
        system("command kill -2 `pidof  jconv ` 2> /dev/null") ;
        pclose(control_stream1);
    }
    stopit = "stop";
    showwave = 0;
    playmidi = 0;
    // checky = 0.0;
   // jack_port_disconnect (client, output_ports[0]);
   // jack_port_disconnect (client, output_ports[1]);
  //  jack_port_disconnect (midi_client, input_ports[0]);
    GtkWaveView myGtkWaveView;
    myGtkWaveView.gtk_waveview_destroy (GTK_WIDGET(livewa), NULL );
    GtkRegler myGtkRegler;
    myGtkRegler.gtk_regler_destroy ( );
    if (G_IS_OBJECT(ib))  
    g_object_unref( ib);
    if (G_IS_OBJECT(ibm))  
    g_object_unref( ibm);
    if (G_IS_OBJECT(ibr))  
    g_object_unref(ibr);
    gtk_main_quit ();
}

/* disable xlib funktions----------------------------
void move_dialog(GtkWidget *widget, gpointer data)
{
Display *dsp = XOpenDisplay( NULL );
int screenNumber = DefaultScreen(dsp);
XEvent event;
//Cursor icon_cursor;
//icon_cursor = XCreateFontCursor(dsp, XC_hand1);
//XDefineCursor(dsp, (dsp, RootWindow(dsp, DefaultScreen(dsp))), icon_cursor);
//XSync(dsp, TRUE);
// get info about current pointer position
while ( event.xbutton.state != 0 ) {
XQueryPointer(dsp, RootWindow(dsp, DefaultScreen(dsp)),
&event.xbutton.root, &event.xbutton.window,
&event.xbutton.x_root, &event.xbutton.y_root,
&event.xbutton.x, &event.xbutton.y,
&event.xbutton.state);
//printf("Mouse Coordinates: %u %d\n", Button1MotionMask, event.xbutton.state);
gtk_window_move(GTK_WINDOW(data), event.xbutton.x, event.xbutton.y);
}
//XUndefineCursor(dsp, (dsp, RootWindow(dsp, DefaultScreen(dsp))));
XCloseDisplay( dsp );
}  -----------------------------------*/

// reset the extended sliders to default settings
static void reset_dialog( GtkWidget *widget, gpointer data )
{
    const char* witchres = gtk_window_get_title(GTK_WINDOW(data));
    const char*	  home;
    home = getenv ("HOME");
    if (home == 0) home = ".";
    char                filename[256];
    snprintf(filename, 256, "%s/.guitarix/resettings", home);
    if (strcmp(witchres, "distortion") == 0) interface->recalladState(filename,  4,  16, 0);
    else if (strcmp(witchres, "freeverb") == 0) interface->recalladState(filename,  20,  24, 1);
    else if (strcmp(witchres, "ImpulseResponse") == 0) interface->recalladState(filename,  28,  32, 2);
    else if (strcmp(witchres, "crybaby") == 0) interface->recalladState(filename,  16,  20, 3);
    else if (strcmp(witchres, "midi out") == 0) interface->recalladState(filename,  44,  50, 4);
    else if (strcmp(witchres, "compressor") == 0) interface->recalladState(filename,  72,  78, 5);
}

// show extendend settings slider
void show_dialog(GtkWidget *widget, gpointer data)
{
    if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(widget)) == TRUE)
    {
        gtk_widget_show(GTK_WIDGET(data));
        gint root_x, root_y;
        gtk_window_get_position (GTK_WINDOW(data), &root_x, &root_y);
        root_y -= 120;
        gtk_window_move(GTK_WINDOW(data), root_x, root_y);
    }
    else gtk_widget_hide(GTK_WIDGET(data));
}

static void hide_show( GtkWidget *widget, gpointer data )
{
    if (showit == 0){
    gtk_widget_hide(GTK_WIDGET(fWindow));
    showit = 1;
    }
    else {
    gtk_widget_show(GTK_WIDGET(fWindow));
    showit = 0;
    }
}

static void pop_menu( GtkWidget *widget, gpointer data )
{
guint32 tim = gtk_get_current_event_time ();
gtk_menu_popup (GTK_MENU(menuh),NULL,NULL,NULL,(gpointer) menuh,2,tim);
}

