/******************************************************************************
*******************************************************************************

								FAUST DSP
	dsp_interface.cpp
	create the interface for guitarix
*******************************************************************************
*******************************************************************************/



    virtual void buildUserInterface(UI* interface)
    {

        interface->openVerticalBox("");
        interface->addMenu();
        interface->closeBox();
        interface->openVerticalBox("                                                ");
        interface->openEventBox(" ");
        interface->openHorizontalBox("");
        interface->openFrameBox("");
        interface->addNumDisplay("", &fConsta1);
        interface->closeBox();
        interface->openVerticalBox("");
        interface->addslider("balance", &fslider25, 0.f, -1.f, 1.f, 1.e-01f);
        interface->closeBox();
        interface->openFrameBox("");
        interface->openExpanderBox(" jconv ", &fexpand2);
        interface->openHandleBox("  ");
        interface->openVerticalBox("");
        interface->addslider("wet/dry", &fslider24,  0.f, -1.f, 1.f, 1.e-01f);
        interface->addButton("jconv settings", &filebutton);
        interface->addJToggleButton("run jconv", &checkbutton7);
        interface->closeBox();
        interface->closeBox();
        interface->closeBox();
        interface->closeBox();
        interface->closeBox();
        interface->closeBox();
        interface->openExpanderBox(" CONTROLS ", &fexpand);
        interface->openHandleBox("  ");
        interface->openHorizontalBox("");
        interface->openVerticalBox("volume");
        interface->openVerticalBox("");
        interface->addbigregler(" in ", &fslider3, 0.f, -40.f, 40.f, 0.1f);
        interface->addbigregler("out", &fslider17, 0.f, -40.f, 40.f, 0.1f);
        interface->closeBox();
        interface->addPToggleButton("preamp", &fcheckbox1);
        interface->closeBox();
        interface->openVerticalBox("");
        interface->openVerticalBox("tone");
        interface->addregler("bass", &fslider2, 0.f, -20.f, 20.f, 0.1f);
        interface->addregler("treble", &fslider1, 0.f, -20.f, 20.f, 0.1f);
        interface->openVerticalBox("  anti \naliase");
        interface->addtoggle("a.aliase", &antialis0);
        interface->addHorizontalSlider(" feedback ", &faas1, 0.3f, 0.3f, 0.9f, 0.01f);
        interface->closeBox();
        interface->closeBox();
        interface->closeBox();
        interface->openVerticalBox("valve");
        interface->openVerticalBox("tube");
        interface->addtoggle("", &ftube);
        interface->addHorizontalSlider("tube",&ffuzzytube, 0.f, 0.f, 10.f, 1.0f);
        interface->closeBox();
        interface->openVerticalBox("drive");
        interface->addtoggle("", &fprdr);
        interface->addHorizontalSlider("drive", &fpredrive, 0.f, 0.f, 10.f, 1.0f);
        interface->closeBox();
        interface->openVerticalBox("vibrato");
        interface->addtoggle("", &fresoon);
        interface->addHorizontalSlider("vibrato", &fvibrato, 0.f, 0.f, 2.f, 0.02f);
        interface->closeBox();
        interface->closeBox();
        interface->openVerticalBox("");
        interface->openHorizontalBox("");
        interface->openVerticalBox("compressor");
        interface->addregler("ratio", &fentrycom2, 2.000000f, 1.000000f, 20.000000f, 0.100000f);
        interface->openHorizontalBox("");
        interface->addtoggle("", &fcheckboxcom1);
        interface->openDialogBox("compressor", &fdialogbox8);
        interface->openHandleBox("  ");
        interface->openVerticalBox("compressor");
        interface->openHorizontalBox("");
        interface->addregler("knee", &fentrycom1, 3.000000f, 0.000000f, 20.000000f, 0.100000f);
        interface->addregler("ratio", &fentrycom2, 2.000000f, 1.000000f, 20.000000f, 0.100000f);
        interface->addregler("threshold", &fentrycom0, -20.000000f, -96.000000f, 10.000000f, 0.100000f);
        interface->closeBox();
        interface->openVerticalBox("envelop");
        interface->addslider("attack", &fslidercom0, 2.000000e-03f, 0.000000f, 1.000000f, 1.000000e-03f);
        interface->addslider("release", &fslidercom1, 0.500000f, 0.000000f, 10.000000f, 1.000000e-02f);
        interface->closeBox();
        interface->closeBox();
        interface->closeBox();
        interface->closeBox();
        interface->closeBox();
        interface->closeBox();
        interface->openVerticalBox("overdrive");
        interface->addregler("  drive ", &drive, 1.f, 1.f, 20.f, 0.1f);
        interface->addtoggle("", &foverdrive4);
        interface->closeBox();
        interface->openVerticalBox(" distortion");
        interface->addregler("  drive ", &fslider9, 0.64f, 0.f, 1.f, 1.e-02f);
        interface->openHorizontalBox("");
        interface->addtoggle("", &fcheckbox4);
        interface->openDialogBox("distortion", &fdialogbox1);
        interface->openHandleBox("  ");
        interface->addbigregler("  drive ", &fslider9, 0.64f, 0.f, 1.f, 1.e-02f);
        interface->addregler("level", &fslider8, 1.000000e-02f, 0.0f, 0.50f, 1.000000e-02f);
        interface->addregler("gain", &fslider10, 2.0f, -10.0f, 10.0f, 0.1f);
        interface->openVerticalBox("low/highpass");
        interface->openHorizontalBox("");
        interface->addregler("high-freq", &fentry1, 130.0f, 20.0f, 7040.0f, 10.0f);
        interface->addregler("low-freq", &fentry0, 5000.0f, 20.0f, 7040.0f, 10.0f);
        interface->closeBox();
        interface->addtoggle("", &fcheckbox2);
        interface->closeBox();
        interface->openVerticalBox("low/highcutoff");
        interface->openHorizontalBox("");
        interface->addregler("high-freq", &fslider6, 5000.0f, 1000.0f, 10000.0f, 10.0f);
        interface->addregler("low-freq", &fslider7, 130.0f, 20.0f, 1000.0f, 10.0f);
        interface->closeBox();
        interface->addtoggle("", &fcheckbox3);
        interface->closeBox();
        interface->openHorizontalBox("resonanz");
        interface->addregler("trigger", &fslider4, 0.12f, 0.0f, 1.0f, 1.000000e-02f);
        interface->addregler("vibrato", &fslider5, 1.0f, 0.0f, 1.0f, 1.000000e-02f);
        interface->closeBox();
        interface->closeBox();
        interface->closeBox();
        interface->closeBox();
        interface->closeBox();
        interface->openVerticalBox(" freeverb");
        interface->addregler("RoomSize", &fslider16, 0.500000f, 0.000000f, 1.000000f, 2.500000e-02f);
        interface->openHorizontalBox("");
        interface->addtoggle("", &fcheckbox6);
        interface->openDialogBox("freeverb", &fdialogbox2);
        interface->openHandleBox("  ");
        interface->addregler("RoomSize", &fslider16, 0.500000f, 0.000000f, 1.000000f, 2.500000e-02f);
        interface->addregler("damp", &fslider15, 0.5f, 0.0f, 1.0f, 2.500000e-02f);
        interface->addregler("wet/dry", &fslider14, 0.0f, -0.5f, 0.5f, 1.e-01f);
        interface->closeBox();
        interface->closeBox();
        interface->closeBox();
        interface->closeBox();
        interface->openVerticalBox("ImpulseResponse");
        interface->openHorizontalBox("");
        interface->addregler("   freq   ", &fslider21, 440.000000f, 20.000000f, 2200.000000f, 10.000000f);
        interface->addregler(" peak ", &fslider22, 1.000000f, 0.000000f, 10.000000f, 0.200000f);
        interface->closeBox();
        interface->openHorizontalBox("");
        interface->addtoggle("", &fcheckbox8);
        interface->openDialogBox("ImpulseResponse", &fdialogbox3);
        interface->openHandleBox("  ");
        interface->addregler("   freq   ", &fslider21, 440.000000f, 20.000000f, 2200.000000f, 10.000000f);
        interface->addregler(" peak ", &fslider22, 1.000000f, 0.000000f, 10.000000f, 0.200000f);
        interface->addregler("bandwidth", &fslider20, 100.0f, 20.0f, 20000.0f, 10.0f);
        interface->closeBox();
        interface->closeBox();
        interface->closeBox();
        interface->closeBox();
        interface->openVerticalBox("crybaby");
        interface->addregler(" wah ", &fslider11, 0.000000f, 0.000000f, 1.000000f, 1.000000e-02f);
        interface->openHorizontalBox("");
        interface->addtoggle("", &fcheckbox5);
        interface->openDialogBox("crybaby", &fdialogbox4);
        interface->openHandleBox("  ");
        interface->addregler(" wah ", &fslider11, 0.0f, 0.0f, 1.0f, 1.000000e-02f);
        interface->addregler("level", &fslider12, 0.1f, 0.0f, 1.0f, 1.000000e-02f);
        interface->addregler("wet/dry", &fslider13, 0.f, -1.f, 1.f, 1.e-01f);
        interface->closeBox();
        interface->closeBox();
        interface->closeBox();
        interface->closeBox();
        interface->closeBox();
        interface->openHorizontalBox("");
        interface->addLiveWaveDisplay(" ", &viv , &vivi);
        interface->closeBox();
        interface->closeBox();
        interface->openVerticalBox("");
        interface->openVerticalBox("echo");
        interface->addregler("    %    ", &fslider19, 0.000000f, 0.000000f, 100.000000f, 0.100000f);
        interface->addregler("  time  ", &fslider18, 1.000000f, 1.000000f, 2000.000000f, 1.000000f);
        interface->addtoggle("", &fcheckbox7);
        interface->closeBox();
        interface->closeBox();
        interface->closeBox();
        interface->closeBox();
        interface->closeBox();
        interface->openEventBox(" FEEDBACK ");
        interface->openHorizontalBox("");
        interface->openFrameBox("");
        interface->openVerticalMidiBox("");
        interface->openHorizontalBox("midi_out");
        interface->openDialogBox("midi out", &fdialogbox6);
        interface->openTabBox("");
        interface->openVerticalBox("channel1");
        interface->openEventBox(" ");
        interface->openHorizontalBox("");
        interface->addregler("velocity", &fslider26, 64.f, 0.f, 127.f, 1.f);
        interface->openVerticalBox("");
        interface->addregler("volume", &fslider46, 64.f, 0.f, 127.f, 1.f);
        interface->addCheckButton("autogain", &fautogain);
        interface->closeBox();
        interface->openVerticalBox("");
        interface->addNumEntry("channel 1", &fslider30, 0.f, 0.f, 16.f, 1.f);
        interface->addNumEntry("program", &fslider31, 0.f, 0.f, 248.f, 1.f);
        interface->closeBox();
        interface->addregler("oktave", &fslider29, 0.f, -2.f, 2.f, 1.f);
        interface->addregler("sensity", &fslider27, 20.f, 1.f, 500.f, 1.f);
        interface->closeBox();
        interface->closeBox();
        interface->openHorizontalBox("");
        interface->openHorizontalBox(" ");
        interface->closeBox();
        interface->openHorizontalBox(" ");
        interface->addPToggleButton("auto pitch", &fpitch);
        interface->closeBox();
        interface->closeBox();
        interface->closeBox();
        interface->openVerticalBox("channel2");
        interface->openEventBox(" ");
        interface->openHorizontalBox("");
        interface->addregler("velocity", &fslider32, 64.f, 0.f, 127.f, 1.f);
        interface->openVerticalBox("");
        interface->addregler("volume", &fslider47, 64.f, 0.f, 127.f, 1.f);
        interface->addCheckButton("autogain", &fautogain1);
        interface->closeBox();
        interface->openVerticalBox("");
        interface->addNumEntry("channel 2", &fslider35, 0.f, 0.f, 16.f, 1.f);
        interface->addNumEntry("program", &fslider36, 0.f, 0.f, 248.f, 1.f);
        interface->closeBox();
        interface->addregler("oktave", &fslider34, 0.f, -2.f, 2.f, 1.f);
        interface->addregler("sensity", &fslider33, 20.f, 1.f, 500.f, 1.f);
        interface->closeBox();
        interface->closeBox();
        interface->openHorizontalBox("");
        interface->addtoggle("", &fcheckbox10);
        interface->openHorizontalBox(" ");
        interface->addPToggleButton("auto pitch", &fpitch1);
        interface->closeBox();
        interface->closeBox();
        interface->closeBox();
        interface->openVerticalBox("channel3");
        interface->openEventBox(" ");
        interface->openHorizontalBox("");
        interface->addregler("velocity", &fslider40, 64.f, 0.f, 127.f, 1.f);
        interface->openVerticalBox("");
        interface->addregler("volume", &fslider48, 64.f, 0.f, 127.f, 1.f);
        interface->addCheckButton("autogain", &fautogain2);
        interface->closeBox();
        interface->openVerticalBox("");
        interface->addNumEntry("channel 3", &fslider44, 0.f, 0.f, 16.f, 1.f);
        interface->addNumEntry("program", &fslider43, 0.f, 0.f, 248.f, 1.f);
        interface->closeBox();
        interface->addregler("oktave", &fslider42, 0.f, -2.f, 2.f, 1.f);
        interface->addregler("sensity", &fslider41, 20.f, 1.f, 500.f, 1.f);
        interface->closeBox();
        interface->closeBox();
        interface->openHorizontalBox("");
        interface->addtoggle("", &fcheckbox11);
        interface->openHorizontalBox(" ");
        interface->addPToggleButton("auto pitch", &fpitch2);
        interface->closeBox();
        interface->closeBox();
        interface->closeBox();
        interface->openVerticalBox("beat_detector");
        interface->openEventBox(" ");
        interface->openHorizontalBox("");
        interface->addregler("note_on", &fslider39, 2.f, 1.f, 20.f, 1.f);
        interface->addregler("note_off", &fslider37, 2.f, 1.f, 2400.f, 1.f);
        interface->addregler("atack_note", &fslider45, 5.f, 1.f, 127.f, 1.f);
        interface->addregler("atack_beat", &fslider38, 1.f, 0.005f, 127.f, 1.f);
        interface->closeBox();
        interface->closeBox();
        interface->addStatusDisplay("", &midistat);
        interface->closeBox();
        interface->closeBox();
        interface->closeBox();
        interface->closeBox();
        interface->closeBox();
        interface->closeBox();
        interface->addslider(" feedback", &fslider0, 0.000000f, -1.000000f, 1.000000f, 1.000000e-02f);
        interface->addslider(" feedforward", &fslider23, 0.000000f, -1.000000f, 1.000000f, 1.000000e-02f);
        interface->openFrameBox("");
        interface->addToggleButton("record", &togglebutton1);
        interface->closeBox();
        interface->closeBox();
        interface->closeBox();
        interface->closeBox();
    }
