
/******************************************************************************
*******************************************************************************

								funktions from guitarix
	guitarix.cpp
	here are the unsortet global funktions from guitarix 
*******************************************************************************
*******************************************************************************/


// global static fields
GtkWidget* fWindow;
GtkWidget *menul;
GtkWidget *menus;
GtkWidget* pb;
GtkWidget* midibox;

float       	 checky = 1.0;
static float      togglebutton1;
static float      checkbutton7;
static float      checkbox7 = 1.0;
float               cap = 0;
float               capas = 0;
int cm = 0;
int shownote = 0;
int playmidi = 0;
const char*     param;
const char*     stopit = "go";
const char*     rcpath = " " ;
string  jconvwav, jgain, frbuf, jmem, jmode;
GtkWidget*     fbutton, *label1;
FILE*              control_stream;
FILE*              control_stream1;
UI*                 interface;
float valo, vali ;
jack_client_t*      client;
jack_port_t *output_ports[256];
jack_port_t *input_ports[256];
jack_port_t *midi_output_ports;
unsigned char* midi_send;
int send;
int note;
const char **port1, **port2;
int frag;   // jack frame size
float jackframe;

// check version and if directory exists and create it if it not exist
bool Exists(const char* Path)
{
    struct stat my_stat;
    if  ( !stat(Path, &my_stat) != 0)
    {
        char          rcfilename[256];
        const char*	  home;
        home = getenv ("HOME");
        snprintf(rcfilename, 256, "%s/.%s-0.03.1", home, "guitarix/version");
        if  ( !stat(rcfilename, &my_stat) == 0)
        {
            snprintf(rcfilename, 256, "%s %s/.%s", "rm -f " , home, "guitarix/version-*");
            system (rcfilename);
            snprintf(rcfilename, 256, "%s/.%s-0.03.1", home, "guitarix/version");
            ofstream f(rcfilename);
            string cim = "guitarix-0.03.0";
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
            cim = "0.12 1 5000 130 1 5000 130 1 0.01 0.64 2 \n0 0.3 0.7 \n20 440 2 \n0.62 0.12 0 \n64 4 0 0 0 \n";
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
        snprintf(rcfilename, 256, "%s/.%s-0.03.1", home, "guitarix/version");
        ofstream fi(rcfilename);
        cim = "guitarix-0.03.1";
        fi <<  cim <<endl;
        fi.close();
        snprintf(rcfilename, 256, "%s/.%s", home, "guitarix/resettings");
        ofstream fa(rcfilename);
        cim = "0.12 1 5000 130 1 5000 130 1 0.01 0.64 2 \n0 0.3 0.7 \n20 440 2 \n0.62 0.12 0 \n64 4 0 0 0 \n";
        fa <<  cim <<endl;
        fa.close();
    }
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
            const char* capturas ;
            string buf;
            const char* home;
            char gfilename[256];
            home = getenv ("HOME");
            if (home == 0) home = ".";
            snprintf(gfilename, 256, "%s%src", home, "/.guitarix/ja_ca_sset");
            ifstream f(gfilename);
            if (f.good())
            {
                getline(f, buf);
                string ma;
                IntToString(capas,ma);
                std::string a(buf);
                std::string b(".");
                std::string::size_type in = a.find(b);
                in -= 1;
                if (in != -1) a.replace(in,1,ma);
                buf = a;
                capturas = buf.c_str();
                f.close();
            }
            capture(capturas);
        }
    }
}

// read the settings for jconv from file
void get_jconfset ()
{
    char                filename[256];
    const char*	  home;
    home = getenv ("HOME");
    snprintf(filename, 256, "%s/.%s", home, "guitarix/jconv_set.conf");
    ifstream f(filename);
    if (f.good())
    {
        jconvwav = " ";
        int is;
        for (is=0; is<2; is++)
        {
            getline(f,  jmem);
            frbuf = jmem;
        }
        jmem.erase(0, 33);
        frbuf.erase(0, 27);
        frbuf.erase(4);
        for (is=0; is<1; is++)
        {
            getline(f,  jgain);
        }
        jgain.erase(0, 24);
        jgain.erase(3);
        istringstream isn(jgain);
        isn >> valo;
        for (is=0; is<2; is++)
        {
            getline(f,  jconvwav);
        }
        jconvwav.erase(0, 2);
        getline(f,  jmode);
        jmode.erase(0, 2);
        f.close();
    }
    else
    {
        jconvwav = home;
        jgain = "0.2";
        jmem = "8000";
        jmode = "/impulse/copy";
        IntToString((frag), frbuf);
    }
}

//----menu funktion load
void load_function1 (GtkMenuItem *menuitem, gpointer load_preset)
{
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
            if (in != -1) buffer.erase(in);
            l++;
        }
        zeile = l-1;
    }
    f.close();
    lin = zeile;
    get_jconfset ();
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

#include"resample.cpp"

// read name from selected ir.wav file and save *.conf file for jconv
static void fileselect( GtkWidget *widget, gpointer data )
{
    gchar *fileis =  gtk_file_chooser_get_filename (GTK_FILE_CHOOSER(widget));
    if (fileis != NULL)
    {
        jconvwav = fileis;
        char                filename[256];
        const char*	  home;
        home = getenv ("HOME");
        string partioni;
        snprintf(filename, 256, "%s/.%s", home, "guitarix/jconv_set.conf");
        ofstream f(filename);
        string cim = "/cd ";
        cim += jconvwav ;
        std::string b("/");
        std::string::size_type in = cim.find_last_of(b);
        cim.erase(in++);
        in = in - 4;
        jconvwav.erase(0, in);
        cim += "\n";
        cim += "/convolver/new    2    2   ";
        string partion = frbuf;
        cim +=  partion  ;
        IntToString((vali), partioni);
        cim += "    ";
        cim += partioni;
        cim += "  \n";
        cim += "/impulse/read    1  1   ";
        int gainvalu = valo*10;
        IntToString((gainvalu), partion);
        cim += "0.";
        cim +=  partion  ;
        jgain = "0.";
        jgain +=  partion  ;
        cim += "     0       0       0     1  ";
        cim += jconvwav;
        cim += "\n";
        if (jmode == "/impulse/copy")
        {
            cim += "/impulse/copy    2  2   1  1\n";
        }
        else
        {
            cim += "/impulse/read    2  2   ";
            IntToString((gainvalu), partion);
            cim += "0.";
            cim +=  partion  ;
            jgain = "0.";
            jgain +=  partion  ;
            cim += "     0       0       0     2  ";
            cim += jconvwav;
            cim += "\n";
        }
        cim += "# ";
        jconvwav = fileis;
        cim +=  jconvwav;
        cim += "\n";
        cim += "# ";
        cim += jmode;
        cim += "\n";
        f <<  cim <<endl;
        f.close();
        g_free (fileis);
    }
}

// get the value from adjustment and set new label text
static void getvalue( GtkObject *widget, gpointer data )
{
    valo = gtk_adjustment_get_value (GTK_ADJUSTMENT(widget));
}

// get the value from adjustment and set new label text
static void getvalue2( GtkObject *widget, gpointer data )
{
    vali = gtk_adjustment_get_value (GTK_ADJUSTMENT(widget));
    string  partioni ;
    IntToString((vali), partioni);
    jmem = partioni;
}

// get selected entry from combobox and set new label text
static void getvalue1( GtkObject *widget, gpointer data )
{
    frbuf = gtk_combo_box_get_active_text(GTK_COMBO_BOX(widget));
}

// get selected entry from combobox and set new label text
static void getvalue3( GtkObject *widget, gpointer data )
{
    jmode = gtk_combo_box_get_active_text(GTK_COMBO_BOX(widget));
}

// widget to create the jconv settings
static void fileselected( GtkWidget *widget, gpointer data )
{
    GtkWidget *about, *label, *button1, *label2, *label3, *label4, *label5;

    about = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_decorated(GTK_WINDOW(about), TRUE);
    gtk_window_set_deletable(GTK_WINDOW(about), FALSE);
    gtk_window_set_resizable(GTK_WINDOW(about), FALSE);
    gtk_window_set_gravity(GTK_WINDOW(about), GDK_GRAVITY_SOUTH);
    gtk_window_set_transient_for (GTK_WINDOW(about), GTK_WINDOW(fWindow));
    gtk_window_set_position (GTK_WINDOW(about), GTK_WIN_POS_MOUSE);
    gtk_window_set_keep_below (GTK_WINDOW(about), FALSE);
    gtk_window_set_title (GTK_WINDOW (about), "jconv settings");
    gtk_window_set_destroy_with_parent(GTK_WINDOW(about), TRUE);

    label = gtk_label_new ("           settings for jconv             \n        by  Fons Adriaensen ");
    label1 = gtk_label_new ("  \n");
    label2 = gtk_label_new (" partion size");
    label3 = gtk_label_new (" gain ");
    label4 = gtk_label_new (" max mem ");
    label5 = gtk_label_new (" mode ");
    button1  = gtk_button_new_with_label("Ok");
#if defined (__SND_FILE__)
    int chans;
    float sr;
    SNDFILE *sf = soundin_open( jconvwav.c_str(), &chans, &sr);
    soundin_close(sf);
    char lab[256] ;
    snprintf(lab, 256, " (%i) channel (%i)Sample rate ", chans, int(sr));
    gtk_label_set_text(GTK_LABEL(label1), lab);  
#endif
 
    GtkObject* adjo = gtk_adjustment_new(valo, 0.0, 1.0, 0.1, 10*0.1, 0);
    GtkWidget* slider = gtk_spin_button_new (GTK_ADJUSTMENT(adjo), 1.0, 1);
    valo = gtk_adjustment_get_value (GTK_ADJUSTMENT(adjo));
    float jgi;
    jgi = atof(jmem.c_str());
    GtkObject* adji = gtk_adjustment_new( jgi, 1000.0, 200000.0, 1000.0, 10*100.0, 0);
    vali = gtk_adjustment_get_value (GTK_ADJUSTMENT(adji));
    GtkWidget* slider1 = gtk_spin_button_new (GTK_ADJUSTMENT(adji), 1.0, 1);
    GtkWidget*      combo1 = gtk_combo_box_new_text();
    string bufer1 = "/impulse/copy";
    gtk_combo_box_append_text(GTK_COMBO_BOX(combo1), bufer1.c_str());
    bufer1 = "/impulse/read";
    gtk_combo_box_append_text(GTK_COMBO_BOX(combo1), bufer1.c_str());
    if ((jmode == "/impulse/copy") || (frbuf == "/impulse/copy  "))
    {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo1), 0);
    }
    else if ((jmode == "/impulse/read") || (frbuf == "/impulse/read  "))
    {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo1), 1);
    }

    GtkWidget*      combo = gtk_combo_box_new_text();
    bufer1 = "64";
    gtk_combo_box_append_text(GTK_COMBO_BOX(combo), bufer1.c_str());
    bufer1 = "128";
    gtk_combo_box_append_text(GTK_COMBO_BOX(combo), bufer1.c_str());
    bufer1 = "256";
    gtk_combo_box_append_text(GTK_COMBO_BOX(combo), bufer1.c_str());
    bufer1 = "512";
    gtk_combo_box_append_text(GTK_COMBO_BOX(combo), bufer1.c_str());
    bufer1 = "1024";
    gtk_combo_box_append_text(GTK_COMBO_BOX(combo), bufer1.c_str());
    bufer1 = "2048";
    gtk_combo_box_append_text(GTK_COMBO_BOX(combo), bufer1.c_str());
    bufer1 = "4096";
    gtk_combo_box_append_text(GTK_COMBO_BOX(combo), bufer1.c_str());

    if ((frbuf == "64") || (frbuf == "64  "))
    {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo), 0);
    }
    else if ((frbuf == "128") || (frbuf == "128 "))
    {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo), 1);
    }
    else if ((frbuf == "256") || (frbuf == "256 "))
    {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo), 2);
    }
    else if ((frbuf == "512") || (frbuf == "512 "))
    {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo), 3);
    }
    else if (frbuf == "1024")
    {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo), 4);
    }
    else if (frbuf == "2048")
    {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo), 5);
    }
    else if (frbuf == "4096")
    {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo), 6);
    }
    fbutton = gtk_file_chooser_button_new ("Select a *.wav file", GTK_FILE_CHOOSER_ACTION_OPEN);
    // GTK_DIALOG_DESTROY_WITH_PARENT;
    gtk_file_chooser_get_local_only(GTK_FILE_CHOOSER (fbutton));
    gtk_file_chooser_set_filename(GTK_FILE_CHOOSER (fbutton), jconvwav.c_str());
    GtkFileFilter* filter =  gtk_file_filter_new ();
    gtk_file_filter_add_pattern (filter, "*.wav");
    gtk_file_chooser_set_filter (GTK_FILE_CHOOSER (fbutton), filter);
    GtkWidget * box = gtk_hbox_new (TRUE, 4);
    GtkWidget * box1 = gtk_hbox_new (TRUE, 4);
    GtkWidget * box2 = gtk_hbox_new (TRUE, 4);
    GtkWidget * box3 = gtk_hbox_new (TRUE, 4);
    GtkWidget * box4 = gtk_vbox_new (TRUE, 4);
    gtk_container_add (GTK_CONTAINER (box4), label);
    gtk_container_add (GTK_CONTAINER (about), box4);
    gtk_container_add (GTK_CONTAINER (box4), fbutton);
    gtk_container_add (GTK_CONTAINER (box4), label1);
    gtk_container_add (GTK_CONTAINER (box4), box3);
    gtk_container_add (GTK_CONTAINER (box3), combo1);
    gtk_container_add (GTK_CONTAINER (box3), label5);
    gtk_container_add (GTK_CONTAINER (box4), box);
    gtk_container_add (GTK_CONTAINER (box), combo);
    gtk_container_add (GTK_CONTAINER (box), label2);
    gtk_container_add (GTK_CONTAINER (box4), box2);
    gtk_container_add (GTK_CONTAINER (box2), slider1);
    gtk_container_add (GTK_CONTAINER (box2), label4);
    gtk_container_add (GTK_CONTAINER (box4), box1);
    gtk_container_add (GTK_CONTAINER (box1), slider);
    gtk_container_add (GTK_CONTAINER (box1), label3);
    gtk_container_add (GTK_CONTAINER (box4), button1);
    g_signal_connect_swapped (fbutton, "file-set",  G_CALLBACK (fileread), fbutton);
    g_signal_connect_swapped (button1, "pressed",  G_CALLBACK (fileselect), fbutton);
    g_signal_connect_swapped (button1, "clicked",  G_CALLBACK (gtk_widget_destroy), fbutton);
    g_signal_connect_swapped (button1, "clicked",  G_CALLBACK (gtk_widget_destroy), about);
    g_signal_connect_swapped (GTK_OBJECT (adjo), "value-changed", G_CALLBACK (getvalue), adjo);
    g_signal_connect_swapped (GTK_OBJECT (adji), "value-changed", G_CALLBACK (getvalue2), adji);
    g_signal_connect_swapped (GTK_OBJECT (combo), "changed",  G_CALLBACK(getvalue1), (gpointer) combo);
    g_signal_connect_swapped (GTK_OBJECT (combo1), "changed",  G_CALLBACK(getvalue3), (gpointer) combo1);
    gtk_widget_show_all (about);
    //GTK_DIALOG_DESTROY_WITH_PARENT;
}

// run jconv
static void runjconv( GtkWidget *widget, gpointer data )
{
    if (checkbutton7 == 0)
    {
        checkbox7 = 1.0;
        if (system(" pidof jconv > /dev/null") == 0)
        {
            jack_disconnect(client, jack_port_name(output_ports[2]),"jconv:In-1");
            jack_disconnect(client, jack_port_name(output_ports[3]), "jconv:In-2");
            system("command kill -2 `pidof  jconv` 2> /dev/null") ;
            sleep(1);
            pclose(control_stream1);

            for (int i = 2; i < 4; i++)
            {
                jack_port_unregister(client, output_ports[i]);
            }
        }
    }
    else
    {
        struct stat my_stat;
        char                path[256];
        char                path1[256];
        const char*      prename = "/usr/bin/jconv";
        const char*      name = "/usr/local/bin/jconv";
        snprintf(path, 256, "%s", prename);
        snprintf(path1, 256, "%s", name);
// check if jconv is installed in /usr/bin or /usr/local/bin. If not found a messagebox will inform the user
        if (( !stat(path, &my_stat) == 0) && ( !stat(path1, &my_stat) == 0))
        {
            GtkWidget *about, *label, *button;
            about = gtk_dialog_new();
            button  = gtk_button_new_with_label("Ok");
            label = gtk_label_new ("  you need jconv by  Fons Adriaensen \n  please look here\n  http://www.kokkinizita.net/linuxaudio/index.html");
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
            checkbutton7 = 0;
        }
        else
        {

            checkbox7 = 0.0;
            control_stream1 = popen ("jconv ~/.guitarix/jconv_set.conf 2> /dev/null" , "r");
            sleep (2);
            if (system(" pidof jconv > /dev/null") == 0)
            {
                char                buf [256];
                int i = 0;
                char*				pname;
                for (int i = 2; i < 4; i++)
                {
                    //char                buf [256];
                    snprintf(buf, 256, "out_%d", i);
                    output_ports[i] = jack_port_register(client, buf,JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
                }
                pname = getenv("GUITARIX2JACK_OUTPUTS1");
                snprintf(buf, 256, pname, i + 1);
                port1 = jack_port_get_connections (output_ports[i]);
                if (port1 != NULL && port1[0] != NULL)
                {
                    jack_connect(client, jack_port_name(output_ports[2]), "jconv:In-1");
                    jack_connect(client, "jconv:Out-1", port1[0]);
                }
                else
                {
                    jack_connect(client, jack_port_name(output_ports[2]), "jconv:In-1");
                    jack_connect(client, "jconv:Out-1", buf);
                }
                i++;
                pname = getenv("GUITARIX2JACK_OUTPUTS2");
                snprintf(buf, 256, pname, i + 1);
                port2 = jack_port_get_connections (output_ports[i]);
                if (port2 != NULL && port2[0] != NULL)
                {
                    jack_connect(client, jack_port_name(output_ports[3]), "jconv:In-2");
                    jack_connect(client, "jconv:Out-2", port2[0]);
                }
                else
                {
                    jack_connect(client, jack_port_name(output_ports[3]), "jconv:In-2");
                    jack_connect(client, "jconv:Out-2", buf);
                }
            }
            else checkbutton7 = 0;
        }
    }
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
    // checky = 0.0;
    jack_port_disconnect (client, output_ports[0]);
    jack_port_disconnect (client, output_ports[1]);
    jack_port_disconnect (client, input_ports[0]);
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

//------------------ quit GUI------------------
static void hide_widget( GtkWidget *widget, gpointer fWindow )
{
    gtk_widget_hide(GTK_WIDGET(fWindow));
    gtk_main_quit ();
}

