
/******************************************************************************
*******************************************************************************

							JACK AUDIO INTERFACE

*******************************************************************************
*******************************************************************************/

//----------------------------------------------------------------------------
// 	number of input and output channels
//----------------------------------------------------------------------------

int		gNumInChans;
int		gNumOutChans;

//----------------------------------------------------------------------------
// Jack ports
//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
// tables of noninterleaved input and output channels for FAUST
//----------------------------------------------------------------------------

float* 	gInChannel[256];
float* 	gOutChannel[256];

//----------------------------------------------------------------------------
// Jack Callbacks
//----------------------------------------------------------------------------

int srate(jack_nframes_t nframes, void *arg)
{
    printf("the sample rate is now %u/sec\n", nframes);
    return 0;
}

void jack_shutdown(void *arg)
{
    exit(1);
}

int process (jack_nframes_t nframes, void *arg)
{
    AVOIDDENORMALS;
    for (int i = 0; i < gNumInChans; i++)
    {
        gInChannel[i] = (float *)jack_port_get_buffer(input_ports[i], nframes);
    }
    for (int i = 0; i < gNumOutChans; i++)
    {
        gOutChannel[i] = (float *)jack_port_get_buffer(output_ports[i], nframes);
    }
    DSP.compute(nframes, gInChannel, gOutChannel);
    return 0;
}

/******************************************************************************
*******************************************************************************

								MAIN PLAY THREAD

*******************************************************************************
*******************************************************************************/

//-------------------------------------------------------------------------
// 									MAIN
//-------------------------------------------------------------------------

int main(int argc, char *argv[] )
{

   {
        OPTARGS_BEGIN("\033[1;34m guitarix settings useage\033[0m\n all parameters are optional\n\n[\033[1;31m--pix -p\033[0m] [\033[1;31m--clear -c\033[0m] [\033[1;31m--rcset -r\033[0m]\n\n" 
                      "[\033[1;31m--pix\033[0m] or [\033[1;31m-p\033[0m]  ->use the gtk-pixmap engine with guitarix_pix.rc\n\n"
                      "[\033[1;31m--clear\033[0m] or [\033[1;31m-c\033[0m]  ->dont use a gtkrc style file\n\n"
                      "[\033[1;31m--rcset\033[0m] or [\033[1;31m-r\033[0m]  ->use the given path/name of gtk.rc file with guitarix.\n\n"
                      "                                                                                 -> leave it blank to use the gtk-clearlooks engine with guitarix.rc\n\n"
                     )
        {
            OPTARG("--pix","-p") rcpath = "/usr/share/guitarix/guitarix_pix.rc";
            OPTARG("--rcset","-r") rcpath=OPTARG_GETSTRING();
            OPTARG("--clear","-c") rcpath = "    ";
	    OPTARG("--nogui","-nogui") param = "nogui";
	   
        }
        OPTARGS_END;
    }
 if  (strcmp(rcpath, " ") == 0) rcpath =  "/usr/share/guitarix/guitarix.rc";
    char                buf [256];
    jack_status_t       jackstat;
    const char*			home;
    char*				pname;
    char*				jname;
    char                rcfilename[256];
    param = basename (argv [1]);
    jname = basename (argv [0]);

    AVOIDDENORMALS;

    if ((strcmp(param, "nogui") == 0) || (strcmp(param, "--nogui") == 0) || (strcmp(param, "-nogui") == 0))
    {
        fprintf (stderr, "no Gui version loaded\n");
        param = "nogui";
    }

    client = jack_client_open (jname, (jack_options_t) 0, &jackstat);
    if (client == 0)
    {
        fprintf (stderr, "Can't connect to JACK, is the server running ?\n");
        exit (1);
    }
    if (jackstat & JackNameNotUnique)
    {
        jname = jack_get_client_name (client);
    }

    jack_set_process_callback(client, process, 0);
    jack_set_sample_rate_callback(client, srate, 0);
    jack_on_shutdown(client, jack_shutdown, 0);
    gNumInChans = DSP.getNumInputs();
    gNumOutChans = DSP.getNumOutputs();
    frag = jack_get_buffer_size (client);
    printf("the buffer size is now %u/frames\n", frag);
    for (int i = 0; i < gNumInChans; i++)
    {
        snprintf(buf, 256, "in_%d", i);
        input_ports[i] = jack_port_register(client, buf, JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);
    }
    for (int i = 0; i < gNumOutChans; i++)
    {
        snprintf(buf, 256, "out_%d", i);
        output_ports[i] = jack_port_register(client, buf,JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
    }
    for (int i = 2; i < gNumOutChans; i++)
    {
        jack_port_unregister(client, output_ports[i]);
    }

    interface = new GTKUI (jname, &argc, &argv);
    DSP.init(jack_get_sample_rate(client));
    DSP.buildUserInterface(interface);

    home = getenv ("HOME");
    if (home == 0) home = ".";
    snprintf(rcfilename, 256, "%s/.guitarix/%src", home, jname);
    interface->recallState(rcfilename);

    if (jack_activate(client))
    {
        fprintf(stderr, "Can't activate JACK client\n");
        return 1;
    }

    // set autoconnect capture to capture_port_1
    setenv("GUITARIX2JACK_INPUTS", "system:capture_%d", 0);
    pname = getenv("GUITARIX2JACK_INPUTS");
    if (pname && *pname)
    {
        for (int i = 0; i < gNumInChans; i++)
        {
            snprintf(buf, 256, pname, i + 1);
            jack_connect(client, buf, jack_port_name(input_ports[i]));
        }
    }

    // set autoconnect to the first pysical playback ports
    //setenv("GUITARIX2JACK_OUTPUTS", "system:playback_%d", 0);
    setenv("GUITARIX2JACK_OUTPUTS1", "system:playback_1", 0);
    setenv("GUITARIX2JACK_OUTPUTS2", "system:playback_2", 0);
    pname = getenv("GUITARIX2JACK_OUTPUTS1");
    if (pname && *pname)
    {
        int i = 0;
        snprintf(buf, 256, pname, i + 1);
        jack_connect(client, jack_port_name(output_ports[i]), buf);
        i++;
        pname = getenv("GUITARIX2JACK_OUTPUTS2");
        snprintf(buf, 256, pname, i + 1);
        jack_connect(client, jack_port_name(output_ports[i]), buf);
    }

    interface->run();
	//sleep(2);
    jack_deactivate(client);

    for (int i = 0; i < gNumInChans; i++)
    {
        jack_port_unregister(client, input_ports[i]);
    }
    for (int i = 0; i < gNumOutChans; i++)
    {
        jack_port_unregister(client, output_ports[i]);
    }

    jack_client_close(client);
    interface->saveState(rcfilename);

    return 0;
}


