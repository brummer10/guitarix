/*
  * Copyright (C) 2009 Hermann Meyer and James Warden
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

	jconv_settings.cpp

	part of guitarix, create a configfile for jconv and run it
	for guitarix by hermann meyer
*******************************************************************************
*******************************************************************************/

JCONV_SETTINGS::JCONV_SETTINGS()
{
}

JCONV_SETTINGS::~JCONV_SETTINGS()
{
}

string  jgain, frbuf, jmem, jmode, joffset, jlength;
float valo, vali ;
const char **port1, **port2;


// read the settings for jconv from file
void JCONV_SETTINGS::get_jconfset ()
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
            joffset = jgain;
            jlength = jgain;
        }
        jgain.erase(0, 24);
        jgain.erase(3);
        istringstream isn(jgain);
        isn >> valo;
        joffset.erase(0,33);
        joffset.erase(14);
        istringstream isno(joffset);
        isno >> offcut;
        jlength.erase(0,48);
        jlength.erase(9);
        istringstream isnl(jlength);
        isnl >> lenghtcut;
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
        gx_IntToString((frag), frbuf);
        offcut = 0;
        lenghtcut = 0;
    }
}


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
        gx_IntToString((vali), partioni);
        cim += "    ";
        cim += partioni;
        cim += "  \n";
        cim += "/impulse/read    1  1   ";
        int gainvalu = ((valo)*10);
        gx_IntToString((gainvalu), partion);
        if (gainvalu < 10)
        {
            cim += "0.";
            jgain = "0.";
            jgain +=  partion  ;
        }
        else
        {
            std::string bvalo(partion);
            bvalo.insert(1, ".");
            partion = bvalo;
            jgain =  partion  ;
        }
        cim +=  partion  ;
        cim += "     0       ";
        gx_IntToString((offcut), partion);
        cim += partion;
        cim += "       ";
        gx_IntToString((lenghtcut), partion);
        cim += partion;
        cim += "       1  ";
        cim += jconvwav;
        cim += "\n";
        if (jmode == "/impulse/copy")
        {
            cim += "/impulse/copy    2  2   1  1\n";
        }
        else
        {
            cim += "/impulse/read    2  2   ";
            gx_IntToString((gainvalu), partion);
            if (gainvalu < 10)
            {
                cim += "0.";
                jgain = "0.";
                jgain +=  partion  ;
            }
            else
            {
                std::string bvalo(partion);
                bvalo.insert(1, ".");
                partion = bvalo;
                jgain =  partion  ;
            }
            cim +=  partion  ;
            cim += "     0       ";
            gx_IntToString((offcut), partion);
            cim += partion;
            cim += "       ";
            gx_IntToString((lenghtcut), partion);
            cim += partion;
            cim += "       2  ";
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
    gx_IntToString((vali), partioni);
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
void JCONV_SETTINGS::fileselected( GtkWidget *widget, gpointer data )
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

    label = gtk_label_new ("           settings for              \n      jconv  by  Fons Adriaensen ");
    label1 = gtk_label_new (" \n");
    label2 = gtk_label_new (" partion size");
    label3 = gtk_label_new (" gain ");
    label4 = gtk_label_new (" max mem ");
    label5 = gtk_label_new (" mode ");
    button1  = gtk_button_new_with_label("Ok");
    int chans;
    float sr;
    int framecount;
    SNDFILE *sf = soundin_open1( jconvwav.c_str(), &chans, &sr, &framecount);
    soundin_close(sf);
    char lab[256] ;
    snprintf(lab, 256, "fileinfo \n(%i)channel (%i)Sample rate (%i)Samples ", chans, int(sr),framecount);
    gtk_label_set_text(GTK_LABEL(label1), lab);

    GtkObject* adjo = gtk_adjustment_new(valo, 0.0, 5.0, 0.1, 10*0.1, 0);
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
    gtk_file_chooser_get_local_only(GTK_FILE_CHOOSER (fbutton));
    gtk_file_chooser_set_filename(GTK_FILE_CHOOSER (fbutton), jconvwav.c_str());
    GtkFileFilter* filter =  gtk_file_filter_new ();
    gtk_file_filter_add_pattern (filter, "*.wav");
    gtk_file_chooser_set_filter (GTK_FILE_CHOOSER (fbutton), filter);
    GtkWaveView myGtkWaveView;
    GtkWidget * waveview = myGtkWaveView.gtk_wave_view(jconvwav.c_str());
    gtk_widget_set_size_request (GTK_WIDGET(waveview), 300.0, 200.0);
    GtkWidget * box = gtk_hbox_new (TRUE, 4);
    GtkWidget * box1 = gtk_hbox_new (TRUE, 4);
    GtkWidget * box2 = gtk_hbox_new (TRUE, 4);
    GtkWidget * box3 = gtk_hbox_new (TRUE, 4);
    GtkWidget * box4 = gtk_vbox_new (FALSE, 4);
    GtkWidget * viewbox = gtk_vbox_new (TRUE, 4);

    gtk_container_add (GTK_CONTAINER (box4), viewbox);
    gtk_container_add (GTK_CONTAINER (viewbox), waveview);
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
    g_signal_connect_swapped (fbutton, "file-set",  G_CALLBACK (flr), fbutton);
    g_signal_connect_swapped  (fbutton, "file-set",  G_CALLBACK (wv), fbutton);
    g_signal_connect_swapped (button1, "pressed",  G_CALLBACK (fileselect), fbutton);
    g_signal_connect_swapped (button1, "clicked",  G_CALLBACK (gtk_widget_destroy), fbutton);
    g_signal_connect_swapped (button1, "clicked",  G_CALLBACK (gtk_widget_destroy), about);
    g_signal_connect_swapped (GTK_OBJECT (adjo), "value-changed", G_CALLBACK (getvalue), adjo);
    g_signal_connect_swapped (GTK_OBJECT (adji), "value-changed", G_CALLBACK (getvalue2), adji);
    g_signal_connect_swapped (GTK_OBJECT (combo), "changed",  G_CALLBACK(getvalue1), (gpointer) combo);
    g_signal_connect_swapped (GTK_OBJECT (combo1), "changed",  G_CALLBACK(getvalue3), (gpointer) combo1);
    gtk_widget_show_all (about);
}

// run jconv
void JCONV_SETTINGS::runjconv( GtkWidget *widget, gpointer data )
{
    int unuseres = 0;
    if (checkbutton7 == 0)
    {
        checkbox7 = 1.0;
        if (system(" pidof jconv > /dev/null") == 0)
        {
            //  jack_disconnect(client, jack_port_name(output_ports[2]),"jconv:In-1");
            //  jack_disconnect(client, jack_port_name(output_ports[3]), "jconv:In-2");
            unuseres = system("command kill -2 `pidof  jconv` 2> /dev/null") ;
            sleep(1);
            runjc = 0;
            if (jack_port_is_mine (client,output_ports[3]))
            {
                jack_port_unregister(client, output_ports[3]);
                gNumOutChans -= 1;
            }
            if (jack_port_is_mine (client,output_ports[2]))
            {
                jack_port_unregister(client, output_ports[2]);
                gNumOutChans -= 1;
            }

            sleep(1);
            pclose(control_stream1);
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
//----- james, can we use here also the check install call we use for jack_capture ?
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
            control_stream1 = popen ("jconv ~/.guitarix/jconv_set.conf 2> /dev/null" , "r");
            sleep (2);
            if (system(" pidof jconv > /dev/null") == 0)
            {
                if(runjc == 0){
                char                buf [256];
                int i = 0;
                char*				pname;

                for (int i = 2; i < 4; i++)
                {
                    //char                buf [256];
                    snprintf(buf, 256, "out_%d", i);
                    output_ports[i] = jack_port_register(client, buf,JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
                    gNumOutChans += 1;
                }
                //gNumOutChans = 4;
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
                runjc = 1;
                }
            }
            else checkbutton7 = 0;
            checkbox7 = 0.0;
        }
    }
}

