/**********************************************************
	resample.cpp

	call it with     myResample.fileread(GtkWidget *widget, gpointer data )
	the GtkWidget must be a GTK_FILE_CHOOSER_BUTTON
	for guitarix by hermann meyer
***************************************************************/
//#include "./guitarix/resample.h"



Resample::Resample()
{
  // Nothing specific to do...
}

Resample::~Resample()
{
  // Nothing specific to do...
}

SNDFILE *soundout_open(const char* name, int chans, float sr)
{
    // initialise the SF_INFO structure
    SF_INFO info;
    info.samplerate = sr;
    info.channels = chans;
    info.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;
    return sf_open(name, SFM_WRITE, &info);
}

SNDFILE *soundin_open1(const char* name, int *chans, float *sr, int *length)
{
    SF_INFO info;
    SNDFILE *sf = sf_open(name, SFM_READ, &info);
    *sr     = (float) info.samplerate;
    *chans  =   info.channels;
    *length =   (int)   info.frames;
    return sf;
}

int soundout(SNDFILE *pOutput, float *buffer, int vecsize)
{
    return (int) sf_writef_float(pOutput, buffer, vecsize);
}

int soundin(SNDFILE *pInput, float *buffer, int vecsize)
{
    return (int) sf_readf_float(pInput, buffer, vecsize);
}

int resample(const char*  pInputi, const char* pOutputi, float jackframe)
{
    SNDFILE *pInput, *pOutput;
    int counter=0,chans,vecsize=64, length=0,length2=0, countfloat;
    float *sig,sr;
    if (!(pInput=soundin_open1(pInputi, &chans, &sr, &length2)))
    {
        GtkWidget *about, *label, *button;
        about = gtk_dialog_new();
        button  = gtk_button_new_with_label("Ok");
        label = gtk_label_new ("Error opening input file \n ");
        gtk_container_add (GTK_CONTAINER (GTK_DIALOG(about)->vbox), label);
        gtk_container_add (GTK_CONTAINER (GTK_DIALOG(about)->vbox), button);
        g_signal_connect_swapped (button, "clicked",  G_CALLBACK (gtk_widget_destroy), about);
        gtk_widget_show_all (about);
    }

    else if (!(pOutput=soundout_open(pOutputi, chans, jackframe)))
    {
        GtkWidget *about, *label, *button;
        about = gtk_dialog_new();
        button  = gtk_button_new_with_label("Ok");
        label = gtk_label_new ("Error opening output file \n ");
        gtk_container_add (GTK_CONTAINER (GTK_DIALOG(about)->vbox), label);
        gtk_container_add (GTK_CONTAINER (GTK_DIALOG(about)->vbox), button);
        g_signal_connect_swapped (button, "clicked",  G_CALLBACK (gtk_widget_destroy), about);
        gtk_widget_show_all (about);
    }
   else {
    sig      = new float[vecsize*2];
    while (counter<length+length2-1)
    {
        soundin(pInput, sig,vecsize);
        soundout(pOutput,sig,vecsize);
        counter=counter+64;
        countfloat = 0;
    }
    sf_close(pInput);
    sf_close(pOutput);
    delete[] sig;
        char lab[256] ;
    snprintf(lab, 256, "fileinfo \n (%i) channel (%i)Sample rate (%i) Frames ", chans, int(jackframe),length2);
        gtk_label_set_text(GTK_LABEL(label1), lab);  
    }
    return 0;
}

void resampleit(GtkWidget *widget, gpointer data)
{
    string jconvnew = jconvwav;
    std::string a(jconvnew);
    std::string b(".wav");
    std::string::size_type in = a.find(b);
    if (int(in) != -1) a.replace(in,1,"new.");
    jconvnew = a;
    resample(jconvwav.c_str(), jconvnew.c_str(), int(jackframe));
    string  jconvnew1 = jconvwav;
    std::string c(jconvnew1);
    std::string d(".wav");
    std::string::size_type is = c.find(d);
    if (int(is) != -1) c.replace(is,1,"orig.");
    jconvnew1 = c;
    rename(jconvwav.c_str(), jconvnew1.c_str());
    rename(jconvnew.c_str(), jconvwav.c_str());
}

SNDFILE *soundin_open(const char* name, int *chans, float *sr)
{
    SF_INFO info;
    SNDFILE *sf = sf_open(name, SFM_READ, &info);
    *sr = (float) info.samplerate;
    *chans = info.channels;
    return sf;
}

void soundin_close(SNDFILE *psf_in)
{
    sf_close(psf_in);
}

void Resample::fileread(GtkWidget *widget, gpointer data )
{
    gchar *fileis =  gtk_file_chooser_get_filename (GTK_FILE_CHOOSER(widget));
    if (fileis != NULL)
    {
        jconvwav = fileis;
        std::string e(jconvwav);
        std::string f(" ");
        std::string::size_type ifn = 0;
        while (int(ifn) != -1)
        {
            ifn = e.find(f);
            if (int(ifn) != -1) e.replace(ifn,1,"_");
        }
        rename(jconvwav.c_str(), e.c_str());
        jconvwav = e;
        gtk_file_chooser_set_filename(GTK_FILE_CHOOSER(widget), jconvwav.c_str());
        int chans;
        float sr;
        int framescount;
        SNDFILE *sf = soundin_open1( jconvwav.c_str(), &chans, &sr, &framescount);
        soundin_close(sf);
        char lab[256] ;
        snprintf(lab, 256, "fileinfo \n(%i)channel (%i)Sample rate (%i)Samples ", chans, int(sr),framescount);
        //snprintf(lab, 256, " (%i) channel (%i)Sample rate ", chans, int(sr));
    // GtkWaveView myGtkWaveView;
         wv(widget,data);
        gtk_label_set_text(GTK_LABEL(label1), lab);  
        if (sr != jackframe)
        {
            GtkWidget *about, *label, *button, *button1, *box, *box1;
            about = gtk_window_new (GTK_WINDOW_TOPLEVEL);
            gtk_window_set_decorated(GTK_WINDOW(about), TRUE);
            gtk_window_set_deletable(GTK_WINDOW(about), FALSE);
            gtk_window_set_resizable(GTK_WINDOW(about), FALSE);
            gtk_window_set_gravity(GTK_WINDOW(about), GDK_GRAVITY_SOUTH);
            gtk_window_set_transient_for (GTK_WINDOW(about), GTK_WINDOW(fWindow));
            gtk_window_set_position (GTK_WINDOW(about), GTK_WIN_POS_MOUSE);
            gtk_window_set_keep_below (GTK_WINDOW(about), FALSE);
            gtk_window_set_title (GTK_WINDOW (about), "resample");
            button  = gtk_button_new_with_label("Yes");
            button1  = gtk_button_new_with_label("Chancel");
            box = gtk_hbox_new (TRUE, 4);
            box1 = gtk_vbox_new (FALSE, 4);

            char lab[256] ;
            snprintf(lab, 256, "the (%i) channel Soundfile\n Sample rate (%i)\n did not match\n the jack Sample rate(%i)\ndo you wish to resample it ?\n", chans, int(sr), int(jackframe));
            const char *labe = lab;
            label = gtk_label_new (labe);
            GtkStyle *style = gtk_widget_get_style(label);
            pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
            gtk_widget_modify_font(label, style->font_desc);
            gtk_label_set_selectable(GTK_LABEL(label), TRUE);
            gtk_container_add (GTK_CONTAINER (box1), label);
            gtk_container_add (GTK_CONTAINER (box), button1);
            gtk_container_add (GTK_CONTAINER (box), button);
            gtk_container_add (GTK_CONTAINER (box1), box);
            gtk_container_add (GTK_CONTAINER (about), box1);
            g_signal_connect_swapped (button1, "clicked",  G_CALLBACK (gtk_widget_destroy), about);
            g_signal_connect_swapped (button, "clicked",  G_CALLBACK (resampleit), (gpointer) widget);
            g_signal_connect_swapped (button, "released",  G_CALLBACK (gtk_widget_destroy), about);
            gtk_widget_show_all (about);
        }
        g_free (fileis);
    }
}

