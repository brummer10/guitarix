/******************************************************************************
*******************************************************************************

								FAUST DSP
	dsp.cpp
	create the interface and compute the dsp processing for guitarix
*******************************************************************************
*******************************************************************************/


//----------------------------------------------------------------
//  définition du processeur de signal
//----------------------------------------------------------------

class dsp
{
protected:
    int fSamplingFreq;
public:
    dsp() {}
    virtual ~dsp() {}
    virtual int getNumInputs() 	= 0;
    virtual int getNumOutputs() 	= 0;
    virtual void buildUserInterface(UI* interface) 	= 0;
    virtual void init(int samplingRate) 	= 0;
    virtual void compute(int len, float** inputs, float** outputs) 	= 0;
    virtual void compute_midi( int len, float** input, void* midi_port_buf)  = 0;
};


//----------------------------------------------------------------------------
// 	FAUST generated code
//----------------------------------------------------------------------------

class mydsp : public dsp
{
private:
    float 	fslider0;
    float 	fslider1;
    float 	fConst0;
    float 	fConst1;
    float 	fConst2;
    float 	fslider2;
    float 	fConst3;
    float 	fConst4;
    float 	fConst5;
    float 	fVec0[2];
    //float 	fcheckbox0;
    float 	fcheckbox1;
    float 	fslider3;
    float 	fRec4[2];
    float 	fRec3[2];
    float 	fslider4;
    int 	IOTA;
    float 	fVec1[4096];
    float 	fslider5;
    float 	fRec6[2];
    float 	fentry0;
    float 	fConst6;
    float 	fVec2[2];
    float 	fRec8[2];
    float 	fentry1;
    float 	fConst7;
    float 	fConst8;
    float 	fVec3[2];
    float 	fRec7[2];
    float 	fcheckbox2;
    float 	fslider6;
    float 	fslider7;
    float 	fVec4[2];
    float 	fRec12[2];
    float 	fVec5[2];
    float 	fRec11[2];
    float 	fRec10[3];
    float 	fRec9[3];
    float 	fcheckbox3;
    float 	fslider8;
    float 	fslider9;
    float 	fVec6[2];
    float 	fRec5[2];
    float 	fslider10;
    float 	fRec13[2];
    float 	fVec7[2];
    float 	fRec17[2];
    float 	fVec8[2];
    float 	fRec16[2];
    float 	fRec15[3];
    float 	fRec14[3];
    float 	fcheckbox4;
    float 	fVec9[3];
    float 	fRec2[3];
    float 	fRec1[3];
    float 	fslider11;
    float 	fRec19[2];
    float 	fslider12;
    float 	fslider13;
    float 	fConst9;
    float 	fConst10;
    float 	fRec20[2];
    float 	fRec21[2];
    float 	fRec18[3];
    float 	fcheckbox5;
    float 	fslider14;
    float 	fslider15;
    float 	fRec31[2];
    float 	fslider16;
    float 	fVec10[2048];
    float 	fRec30[2];
    float 	fRec33[2];
    float 	fVec11[2048];
    float 	fRec32[2];
    float 	fRec35[2];
    float 	fVec12[2048];
    float 	fRec34[2];
    float 	fRec37[2];
    float 	fVec13[2048];
    float 	fRec36[2];
    float 	fRec39[2];
    float 	fVec14[2048];
    float 	fRec38[2];
    float 	fRec41[2];
    float 	fVec15[2048];
    float 	fRec40[2];
    float 	fRec43[2];
    float 	fVec16[2048];
    float 	fRec42[2];
    float 	fRec45[2];
    float 	fVec17[2048];
    float 	fRec44[2];
    float 	fVec18[1024];
    float 	fRec28[2];
    float 	fVec19[512];
    float 	fRec26[2];
    float 	fVec20[512];
    float 	fRec24[2];
    float 	fVec21[256];
    float 	fRec22[2];
    float 	fcheckbox6;
    float 	fslider17;
    float 	fRec46[2];
    float 	fslider18;
    float 	fConst11;
    float 	fslider19;
    float 	fRec47[262144];
    float 	fcheckbox7;
    float 	fVec22[3];
    float 	fslider20;
    float 	fslider21;
    float 	fConst12;
    float 	fslider22;
    float 	fRec48[3];
    float 	fcheckbox8;
    float 	fVec23[4];
    float 	fslider23;
    float 	fRec0[6];
    float 	fslider24;
    float 	fslider25;
    float 	fConstan0;
    float 	fConstan1;
    float 	fConstan2;
    float 	fVect0[2];
    float 	fConstan3;
    float 	fRect5[2];
    float 	fVect1[2];
    float 	fRect4[2];
    int 	iRect3[2];
    int 	iRect2[2];
    int 	iRect1[2];
    float 	fRect0[2];
    int weg;
    float 	fexpand;
    float 	fexpand2;
    float 	filebutton;
    float 	fdialogbox1;
    float 	fdialogbox2;
    float 	fdialogbox3;
    float 	fdialogbox4;
    float 	fdialogbox5;
    float 	fdialogbox6;
    float 	fConsta1;
    float 	fslider26;
    float 	fslider27;
    float 	fslider29;
    float 	fslider30;
    float 	fslider31;
    int program;
    unsigned char* midi_send;
    unsigned char* midi_send1;
    unsigned char* midi_send2;
    int send;
    int noten;
    float 	fslider32;
    float 	fslider33;
    float 	fslider34;
    float 	fslider35;
    float 	fslider36;
    float 	fcheckbox10;
    int program1;
    int send1;
    int noten1;
    float 	fslider37;
    float 	fslider38;
    float 	fslider39;
    int send2;
    int noten2;
    float 	fslider40;
    float 	fslider41;
    float 	fslider42;
    float 	fslider43;
    float 	fslider44;
    float 	fcheckbox11;
    int program2;
    float 	fslider45;
    float midistat;
    float 	fslider46;
    float 	fslider47;
    float 	fslider48;
    int volume;
    int volume1;
    int volume2;
    float 	fpitch;
    float 	fpitch1;
    float 	fpitch2;
    float 	fConsthp0;
    float 	fConsthp1;
    float 	fConsthp2;
    float 	fVechp0[2];
    float 	fConsthp3;
    float 	fRechp0[2];
    // compressor
    float 	fentrycom0;
    float 	fConstcom0;
    float 	fConstcom1;
    float 	fReccom1[2];
    float 	fReccom2[2];
    float 	fConstcom2;
    float 	fslidercom0;
    float 	fslidercom1;
    float 	fReccom0[2];
    float 	fentrycom1;
    float 	fentrycom2;
    float 	fdialogbox8;
    float  fcheckboxcom1;
    // compressor end

public:

    static void metadata(Meta* m)
    {
        m->declare("name", "guitarix");
        m->declare("version", "0.01");
        m->declare("author", "brummer");
        m->declare("contributor", "Julius O. Smith (jos at ccrma.stanford.edu)");
        m->declare("license", "BSD");
        m->declare("copyright", "(c)brummer 2008");
        m->declare("reference", "http://ccrma.stanford.edu/realsimple/faust_strings/");
    }

    virtual int getNumInputs()
    {
        return 1;
    }
    virtual int getNumOutputs()
    {
        return 4;
    }

    static void classInit(int samplingFreq)
    {
    }

    virtual void instanceInit(int samplingFreq)
    {
        fSamplingFreq = samplingFreq;
        // compressor
        fentrycom0 = -20.000000f;
        fConstcom0 = expf((0 - (10.000000f / fSamplingFreq)));
        fConstcom1 = (1 - fConstcom0);
        for (int i=0; i<2; i++) fReccom1[i] = 0;
        for (int i=0; i<2; i++) fReccom2[i] = 0;
        fConstcom2 = (1.000000f / fSamplingFreq);
        fslidercom0 = 2.000000e-03f;
        fslidercom1 = 0.500000f;
        for (int i=0; i<2; i++) fReccom0[i] = 0;
        fentrycom1 = 3.000000f;
        fentrycom2 = 2.000000f;
        // compressor end
        fConstan0 = (3.141593f / fSamplingFreq);
        fConstan1 = (251.327423f / fSamplingFreq);
        fConstan2 = (1 - fConstan1);
        for (int i=0; i<2; i++) fVect0[i] = 0;
        fConstan3 = (1.0f / (1 + fConstan1));
        for (int i=0; i<2; i++) fRect5[i] = 0;
        for (int i=0; i<2; i++) fVect1[i] = 0;
        for (int i=0; i<2; i++) fRect4[i] = 0;
        for (int i=0; i<2; i++) iRect3[i] = 0;
        for (int i=0; i<2; i++) iRect2[i] = 0;
        for (int i=0; i<2; i++) iRect1[i] = 0;
        for (int i=0; i<2; i++) fRect0[i] = 0;
        fConst0 = (7539.822754f / fSamplingFreq);
        fConst1 = cosf(fConst0);
        fConst2 = (1.414214f * sinf(fConst0));
        fslider0 = 0.0f;
        fslider1 = 0.0f;
      //  fConst0 = (7539.822754f / fSamplingFreq);
       // fConst1 = cosf(fConst0);
       // fConst2 = (1.414214f * sinf(fConst0));
        fslider2 = 0.0f;
        fConst3 = (1884.955688f / fSamplingFreq);
        fConst4 = cosf(fConst3);
        fConst5 = (1.414214f * sinf(fConst3));
        for (int i=0; i<2; i++) fVec0[i] = 0;
        checky = 1.0;
        fcheckbox1 = 0.0;
        fslider3 = 0.0f;
        for (int i=0; i<2; i++) fRec4[i] = 0;
        for (int i=0; i<2; i++) fRec3[i] = 0;
        fslider4 = 0.12f;
        IOTA = 0;
        for (int i=0; i<4096; i++) fVec1[i] = 0;
        fslider5 = 0.5f;
        for (int i=0; i<2; i++) fRec6[i] = 0;
        fentry0 = 723.0f;
        fConst6 = (3.141593f / fSamplingFreq);
        for (int i=0; i<2; i++) fVec2[i] = 0;
        for (int i=0; i<2; i++) fRec8[i] = 0;
        fentry1 = 720.0f;
        fConst7 = (3.141593f * fSamplingFreq);
        fConst8 = (0.5f / fSamplingFreq);
        for (int i=0; i<2; i++) fVec3[i] = 0;
        for (int i=0; i<2; i++) fRec7[i] = 0;
        fcheckbox2 = 1.0;
        fslider6 = 5000.0f;
        fslider7 = 130.0f;
        for (int i=0; i<2; i++) fVec4[i] = 0;
        for (int i=0; i<2; i++) fRec12[i] = 0;
        for (int i=0; i<2; i++) fVec5[i] = 0;
        for (int i=0; i<2; i++) fRec11[i] = 0;
        for (int i=0; i<3; i++) fRec10[i] = 0;
        for (int i=0; i<3; i++) fRec9[i] = 0;
        fcheckbox3 = 1.0;
        fslider8 = 1.000000e-02f;
        fslider9 = 0.64f;
        for (int i=0; i<2; i++) fVec6[i] = 0;
        for (int i=0; i<2; i++) fRec5[i] = 0;
        fslider10 = 2.0f;
        for (int i=0; i<2; i++) fRec13[i] = 0;
        for (int i=0; i<2; i++) fVec7[i] = 0;
        for (int i=0; i<2; i++) fRec17[i] = 0;
        for (int i=0; i<2; i++) fVec8[i] = 0;
        for (int i=0; i<2; i++) fRec16[i] = 0;
        for (int i=0; i<3; i++) fRec15[i] = 0;
        for (int i=0; i<3; i++) fRec14[i] = 0;
        fcheckbox4 = 1.0;
        for (int i=0; i<3; i++) fVec9[i] = 0;
        for (int i=0; i<3; i++) fRec2[i] = 0;
        for (int i=0; i<3; i++) fRec1[i] = 0;
        fslider11 = 0.0f;
        for (int i=0; i<2; i++) fRec19[i] = 0;
        fslider12 = 0.1f;
        fslider13 = 0.0f;
        fConst9 = (2827.43335f / fSamplingFreq);
        fConst10 = (1413.716675f / fSamplingFreq);
        for (int i=0; i<2; i++) fRec20[i] = 0;
        for (int i=0; i<2; i++) fRec21[i] = 0;
        for (int i=0; i<3; i++) fRec18[i] = 0;
        fcheckbox5 = 0.0;
        fslider14 = 0.3333f;
        fslider15 = 0.5f;
        for (int i=0; i<2; i++) fRec31[i] = 0;
        fslider16 = 0.5f;
        for (int i=0; i<2048; i++) fVec10[i] = 0;
        for (int i=0; i<2; i++) fRec30[i] = 0;
        for (int i=0; i<2; i++) fRec33[i] = 0;
        for (int i=0; i<2048; i++) fVec11[i] = 0;
        for (int i=0; i<2; i++) fRec32[i] = 0;
        for (int i=0; i<2; i++) fRec35[i] = 0;
        for (int i=0; i<2048; i++) fVec12[i] = 0;
        for (int i=0; i<2; i++) fRec34[i] = 0;
        for (int i=0; i<2; i++) fRec37[i] = 0;
        for (int i=0; i<2048; i++) fVec13[i] = 0;
        for (int i=0; i<2; i++) fRec36[i] = 0;
        for (int i=0; i<2; i++) fRec39[i] = 0;
        for (int i=0; i<2048; i++) fVec14[i] = 0;
        for (int i=0; i<2; i++) fRec38[i] = 0;
        for (int i=0; i<2; i++) fRec41[i] = 0;
        for (int i=0; i<2048; i++) fVec15[i] = 0;
        for (int i=0; i<2; i++) fRec40[i] = 0;
        for (int i=0; i<2; i++) fRec43[i] = 0;
        for (int i=0; i<2048; i++) fVec16[i] = 0;
        for (int i=0; i<2; i++) fRec42[i] = 0;
        for (int i=0; i<2; i++) fRec45[i] = 0;
        for (int i=0; i<2048; i++) fVec17[i] = 0;
        for (int i=0; i<2; i++) fRec44[i] = 0;
        for (int i=0; i<1024; i++) fVec18[i] = 0;
        for (int i=0; i<2; i++) fRec28[i] = 0;
        for (int i=0; i<512; i++) fVec19[i] = 0;
        for (int i=0; i<2; i++) fRec26[i] = 0;
        for (int i=0; i<512; i++) fVec20[i] = 0;
        for (int i=0; i<2; i++) fRec24[i] = 0;
        for (int i=0; i<256; i++) fVec21[i] = 0;
        for (int i=0; i<2; i++) fRec22[i] = 0;
        fcheckbox6 = 0.0;
        fslider17 = 0.0f;
        for (int i=0; i<2; i++) fRec46[i] = 0;
        fslider18 = 0.0f;
        fConst11 = (1.000000e-03f * fSamplingFreq);
        fslider19 = 0.0f;
        for (int i=0; i<262144; i++) fRec47[i] = 0;
        fcheckbox7 = 0.0;
        for (int i=0; i<3; i++) fVec22[i] = 0;
        fslider20 = 100.0f;
        fslider21 = 440.0f;
        fConst12 = (6.283185f / fSamplingFreq);
        fslider22 = 1.0f;
        for (int i=0; i<3; i++) fRec48[i] = 0;
        fcheckbox8 = 0.0;
        for (int i=0; i<4; i++) fVec23[i] = 0;
        fslider23 = 0.0f;
        for (int i=0; i<6; i++) fRec0[i] = 0;
        fslider24 = 0.0f;
        fslider25 = 0.0f;
        fslider26 = 64.0f;
        fslider27 = 20.0f;
        fslider29 = 0.0f;
        fslider30 = 0.0f;
        fslider31 = 0.0f;
        fslider32 = 64.0f;
        fslider33 = 20.0f;
        fslider34 = 0.0f;
        fslider35 = 0.0f;
        fslider36 = 0.0f;
        fslider37 = 2.0f;
        fslider38 = 1.0f;
        fslider39 = 20.0f;
        fslider40 = 64.0f;
        fslider41 = 20.0f;
        fslider42 = 0.0f;
        fslider43 = 0.0f;
        fslider44 = 0.0f;
        fslider45 = 5.0f;
        midistat = 0.0f;
        fslider46 = 64;
        fslider47 = 64;
        fslider48 = 64;
	fConsthp0 = (1.0f / tanf((0.5f * (((3.141593f * fSamplingFreq) - 2764.601562f) / fSamplingFreq))));
	fConsthp1 = (1 + fConsthp0);
	fConsthp2 = (0 - ((fConsthp0 - 1) / fConsthp1));
	for (int i=0; i<2; i++) fVechp0[i] = 0;
	fConsthp3 = (1.0f / fConsthp1);
	for (int i=0; i<2; i++) fRechp0[i] = 0;
	send = 0;
	send1 = 0;
	send2 = 0;
    }

    virtual void init(int samplingFreq)
    {
        classInit(samplingFreq);
        instanceInit(samplingFreq);
    }

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
        interface->addHorizontalSlider("balance", &fslider25, 0.f, -1.f, 1.f, 1.e-01f);
        interface->openFrameBox("");
        interface->openExpanderBox(" jconv ", &fexpand2);
        interface->openHandleBox("  ");
        interface->openVerticalBox("");
        interface->addHorizontalSlider("wet/dry", &fslider24,  0.f, -1.f, 1.f, 1.e-01f);
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
        interface->openVerticalBox(" volume");
        interface->openVerticalBox("");
        interface->addbigregler(" in ", &fslider3, 0.f, -40.f, 40.f, 0.1f);
        interface->addbigregler("out", &fslider17, 0.f, -40.f, 40.f, 0.1f);
        interface->closeBox();
        interface->addPToggleButton("preamp", &fcheckbox1);
        interface->closeBox();

        interface->openVerticalBox("");
        interface->openVerticalBox("  tone  ");
        interface->addregler("  bass  ", &fslider2, 0.f, -20.f, 20.f, 0.1f);
        interface->addregler(" treble ", &fslider1, 0.f, -20.f, 20.f, 0.1f);
        interface->openVerticalBox(" ");
        interface->closeBox();
        interface->closeBox();
        interface->closeBox();

        interface->openVerticalBox("");
        interface->openHorizontalBox("");
        interface->openVerticalBox("compressor");
        interface->addregler("ratio", &fentrycom2, 2.000000f, 1.000000f, 20.000000f, 0.100000f);
        interface->addtoggle("", &fcheckboxcom1);
        interface->openDialogBox("compressor", &fdialogbox8);
        interface->openHandleBox("  ");
        interface->openVerticalBox("compressor");
        interface->openHorizontalBox("");
        interface->addregler("knee", &fentrycom1, 3.000000f, 0.000000f, 20.000000f, 0.100000f);
        interface->addregler("ratio", &fentrycom2, 2.000000f, 1.000000f, 20.000000f, 0.100000f);
        interface->addregler("threshold", &fentrycom0, -20.000000f, -96.000000f, 10.000000f, 0.100000f);
        interface->closeBox();
        interface->openHorizontalBox("envelop");
        interface->addregler("attack", &fslidercom0, 2.000000e-03f, 0.000000f, 1.000000f, 1.000000e-03f);
        interface->addregler("release", &fslidercom1, 0.500000f, 0.000000f, 10.000000f, 1.000000e-02f);
        interface->closeBox();
        interface->closeBox();
        interface->closeBox();
        interface->closeBox();
        interface->closeBox();
        interface->openVerticalBox(" distortion");
        interface->addregler("  drive ", &fslider9, 0.64f, 0.f, 1.f, 1.e-02f);
        interface->addtoggle("", &fcheckbox4);
        interface->openDialogBox("distortion", &fdialogbox1);
        interface->openHandleBox("  ");
        interface->addbigregler("  drive ", &fslider9, 0.64f, 0.f, 1.f, 1.e-02f);
        interface->addregler("level", &fslider8, 1.000000e-02f, 0.0f, 0.50f, 1.000000e-02f);
        interface->addregler("gain", &fslider10, 2.0f, 0.0f, 10.0f, 0.1f);
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
        interface->addregler("trigger", &fslider4, 0.12f, 0.0f, 0.5f, 1.000000e-02f);
        interface->addregler("vibrato", &fslider5, 1.0f, 0.0f, 1.0f, 1.000000e-02f);
        interface->closeBox();
        interface->closeBox();
        interface->closeBox();
        interface->closeBox();
        interface->openVerticalBox(" freeverb");
        interface->addregler("RoomSize", &fslider16, 0.500000f, 0.000000f, 1.000000f, 2.500000e-02f);
        interface->addtoggle("", &fcheckbox6);
        interface->openDialogBox("freeverb", &fdialogbox2);
        interface->openHandleBox("  ");
        interface->addregler("RoomSize", &fslider16, 0.500000f, 0.000000f, 1.000000f, 2.500000e-02f);
        interface->addregler("damp", &fslider15, 0.5f, 0.0f, 1.0f, 2.500000e-02f);
        interface->addregler("wet/dry", &fslider14, 0.0f, -0.5f, 0.5f, 1.e-01f);
        interface->closeBox();
        interface->closeBox();
        interface->closeBox();
        interface->openVerticalBox("ImpulseResponse");
        interface->openHorizontalBox("");
        interface->addregler("   freq   ", &fslider21, 440.000000f, 20.000000f, 2200.000000f, 10.000000f);
        interface->addregler(" peak ", &fslider22, 1.000000f, 0.000000f, 10.000000f, 0.200000f);
        interface->closeBox();
        interface->addtoggle("", &fcheckbox8);
        interface->openDialogBox("ImpulseResponse", &fdialogbox3);
        interface->openHandleBox("  ");
        interface->addregler("   freq   ", &fslider21, 440.000000f, 20.000000f, 2200.000000f, 10.000000f);
        interface->addregler(" peak ", &fslider22, 1.000000f, 0.000000f, 10.000000f, 0.200000f);
        interface->addregler("bandwidth", &fslider20, 100.0f, 20.0f, 20000.0f, 10.0f);
        interface->closeBox();
        interface->closeBox();
        interface->closeBox();
        interface->openVerticalBox("crybaby");
        interface->addregler(" wah ", &fslider11, 0.000000f, 0.000000f, 1.000000f, 1.000000e-02f);
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
        interface->openVerticalBox(" ");
        //interface->addVerticalBargraph("", &cpu_load,0.0f, 100.0f);
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
        interface->addregler("volume", &fslider46, 64.f, 0.f, 127.f, 1.f);
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
        interface->addregler("volume", &fslider47, 64.f, 0.f, 127.f, 1.f);
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
        interface->addregler("volume", &fslider48, 64.f, 0.f, 127.f, 1.f);
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
        interface->addregler("note_on", &fslider39, 20.f, 1.f, 200.f, 1.f);
        interface->addregler("note_off", &fslider37, 2.f, 1.f, 2400.f, 1.f);
        interface->addregler("atack_note", &fslider45, 5.f, 1.f, 10.f, 1.f);
        interface->addregler("atack_beat", &fslider38, 1.f, 0.01f, 20.f, 0.01f);
        interface->closeBox();
        interface->closeBox();
      //  interface->openHorizontalBox(" ");
        interface->addStatusDisplay("", &midistat);
      //  interface->closeBox();
        interface->closeBox();
        interface->closeBox();
        interface->closeBox();
        interface->closeBox();
        interface->closeBox();
        interface->closeBox();

        interface->addHorizontalSlider(" feedback", &fslider0, 0.000000f, -1.000000f, 1.000000f, 1.000000e-02f);
        interface->addHorizontalSlider(" feedforward", &fslider23, 0.000000f, -1.000000f, 1.000000f, 1.000000e-02f);
        interface->openFrameBox("");
        interface->addToggleButton("record", &togglebutton1);
        interface->closeBox();
        interface->closeBox();
        interface->closeBox();
        interface->closeBox();
    }

    virtual void compute_midi( int len, float** inputi, void* midi_port_buf)
    {
        TBeatDetector myTBeatDetector;

        float 	beat0;
        float 	fConsta2;
        int preNote;
        float* inputi0 = inputi[0];
        float fTemps45 = fslider45*0.01;
        int iTemps31 = int(fslider31);
        int iTemps30 = int(fslider30);
        int iTemps27 = int(fslider27);
        int iTemps29 = int(fslider29)*12;
        int iTemps26 = int(fslider26);
        int iTemps36 = int(fslider36);
        int iTemps35 = int(fslider35);
        int iTemps33 = int(fslider33);
        int iTemps34 = int(fslider34)*12;
        int iTemps32 = int(fslider32);
        int iTemps43 = int(fslider43);
        int iTemps44 = int(fslider44);
        int iTemps41 = int(fslider41);
        int iTemps42 = int(fslider42)*12;
        int iTemps40 = int(fslider40);
        float fTemps37  = fSamplingFreq/fslider37;
        float fTemps37a  = (fSamplingFreq/fslider37) +5.0;
        float fTemps38 = fslider38;
        int iTemps39 = int(fslider39);
        int iTemps46 = int(fslider46);
        int iTemps47 = int(fslider47);
        int iTemps48 = int(fslider48);
        float fTemps39 = fslider39;
        int piwe;

        for (int i=0; i<len; i++)
        {
            if ((shownote == 1) | (playmidi == 1))
            {
	        float fTemphp0 = inputi0[i];
		float fTemphps0 = 1.5f * fTemphp0 - 0.5f * fTemphp0 *fTemphp0 * fTemphp0;
	        fVechp0[0] = fTemphps0;
		beat0 = fTemphps0;
	        fRechp0[0] = ((fConsthp3 * (fVechp0[0] - fVechp0[1])) + (fConsthp2 * fRechp0[1]));
	        float fTemphp1  = fRechp0[0];
                int iTempt0 = (1 + iRect2[1]);
                float fTempt1 = (1.0f / tanf((fConstan0 * max(100, fRect0[1]))));
                float fTempt2 = (1 + fTempt1);
                fVect0[0] = fTemphp1;
                fRect5[0] = (fConstan3 * ((fVect0[0] - fVect0[1]) + (fConstan2 * fRect5[1])));
                fVect1[0] = (fRect5[0] / fTempt2);
                fRect4[0] = (fVect1[1] + ((fRect5[0] + ((fTempt1 - 1) * fRect4[1])) / fTempt2));
                int iTempt4 = ((fRect4[1] < 0) & (fRect4[0] >= 0));
                iRect3[0] = (iTempt4 + (iRect3[1] % iTemps39));
                iRect2[0] = ((1 - (iTempt4 & (iRect3[0] ==  fTemps39))) * iTempt0);
                int iTempt5 = (iRect2[0] == 0);
                iRect1[0] = ((iTempt5 * iTempt0) + ((1 - iTempt5) * iRect1[1]));
                fRect0[0] = (fSamplingFreq * ((fTemps39 / max(iRect1[0], 1)) - (fTemps39 * (iRect1[0] == 0))));

                if (fTemphp0 >= fTemps45)
                {
                    fConsta1 = ( (12 * log2f((2.272727e-03f * fRect0[0]))));
                    preNote = int(fConsta1)+57;
                    fConsta2 = fConsta1 - (preNote - 57);
                    piwe = (fConsta2+1) * 8192; // pitch wheel value
                    weg = 0;
                    if (playmidi == 1)
                    {
                        // channel0
                        if (program != iTemps31)
                        {
                            program = iTemps31;
                            midistat += 1.0f;
                            midi_send = jack_midi_event_reserve(midi_port_buf, i, 2);
                            if (midi_send)
                            {
                                midi_send[1] =  iTemps31;  // program value
                                midi_send[0] = 0xC0 | iTemps30;  // controller+ channel
                            }
                        }
                        if (volume != iTemps46)
                        {
                            volume = iTemps46;
                            midistat += 1.0f;
                            midi_send = jack_midi_event_reserve(midi_port_buf, i, 3);
                            if (midi_send)
                            {
                                midi_send[2] = iTemps46;	// volume value
                                midi_send[1] =  0x07;     // set controler volume
                                midi_send[0] = 0xB0 | iTemps30;  // controller + channel
                            }
                        }
                        if (send > iTemps27)   //20
                        {
                            noten = preNote + iTemps29;
                            send = 0;
                            midistat += 1.0f;
                            if (( noten>=0)&(noten<=127))
                            {
                                // pitch wheel clear
                                if (fpitch == 1.0)
                                {
                                    midi_send = jack_midi_event_reserve(midi_port_buf, i, 3);
                                    if (midi_send)
                                    {
                                        midi_send[2] =  0x40;  // pitch value
                                        midi_send[1] = 0x00 ; // pitch value
                                        midi_send[0] = 0xE0 |  iTemps30; // controller + channel
                                    }
                                }
                                midi_send = jack_midi_event_reserve(midi_port_buf, i, 3);
                                if (midi_send)
                                {
                                    midi_send[2] = iTemps26; // velocity
                                    midi_send[1] = noten ; // note
                                    midi_send[0] = 0x90 |  iTemps30;	// controller + channel
                                }
                                // pitch wheel set auto
                                if (fpitch == 1.0)
                                {
                                    if (piwe < 0) piwe = 0;
                                    if (fConsta2 > 0x3fff) piwe = 0x3fff;
                                    midi_send = jack_midi_event_reserve(midi_port_buf, i, 3);
                                    if (midi_send)
                                    {
                                        midi_send[2] = (piwe >> 7) & 0x7f;  // pitch
                                        midi_send[1] = piwe & 0x7f ; // pitch
                                        midi_send[0] = 0xE0 |  iTemps30; // controller + channel
                                    }
                                }
                            }
                        }
                        // channel1
                        if (fcheckbox10 == 1.0)
                        {
                            if (program1 != iTemps36)
                            {
                                program1 = iTemps36;
                                midistat += 1.0f;
                                midi_send1 = jack_midi_event_reserve(midi_port_buf, i, 2);
                                if (midi_send1)
                                {
                                    midi_send1[1] = iTemps36;  // program value
                                    midi_send1[0] = 0xC0 | iTemps35; // controller+ channel
                                }
                            }
                            if (volume1 != iTemps47)
                            {
                                volume1 = iTemps47;
                                midistat += 1.0f;
                                midi_send1 = jack_midi_event_reserve(midi_port_buf, i, 3);
                                if (midi_send1)
                                {
                                    midi_send1[2] = iTemps47;  // volume value
                                    midi_send1[1] =  0x07; // set controler channel volume
                                    midi_send1[0] = 0xB0 | iTemps35; // controller + channel
                                }
                            }
                            if (send1 > iTemps33)
                            {
                                noten1 = preNote + iTemps34;
                                send1 = 0;
                                midistat += 1.0f;
                                if ((noten1>=0)&(noten1<=127))
                                {
                                    // pitch wheel clear
                                    if (fpitch1 == 1.0)
                                    {
                                        midi_send1 = jack_midi_event_reserve(midi_port_buf, i, 3);
                                        if (midi_send1)
                                        {
                                            midi_send1[2] =  0x40;  // pitch value
                                            midi_send1[1] = 0x00 ; // pitch value
                                            midi_send1[0] = 0xE0 |  iTemps35;  // controller + channel
                                        }
                                    }
                                    midi_send1 = jack_midi_event_reserve(midi_port_buf, i, 3);
                                    if (midi_send1)
                                    {
                                        midi_send1[2] = iTemps32; // velocity 
                                        midi_send1[1] = noten1; // note
                                        midi_send1[0] = 0x90 | iTemps35; // note on + channel
                                    }
                                    // pitch wheel set auto
                                    if (fpitch1 == 1.0)
                                    {
                                        if (piwe < 0) piwe = 0;
                                        if (fConsta2 > 0x3fff) piwe = 0x3fff;
                                        midi_send1 = jack_midi_event_reserve(midi_port_buf, i, 3);
                                        if (midi_send1)
                                        {
                                            midi_send1[2] = (piwe >> 7) & 0x7f;  // pitch
                                            midi_send1[1] = piwe & 0x7f ; // pitch
                                            midi_send1[0] = 0xE0 |  iTemps35; // controller + channel
                                        }
                                    }
                                }
                            }
                        }
                        if (fcheckbox11 == 1.0)
                        {
                            if (program2 != iTemps43)
                            {
                                program2 = iTemps43;
                                midistat += 1.0f;
                                midi_send2 = jack_midi_event_reserve(midi_port_buf, i, 2);
                                if (midi_send2)
                                {
                                    midi_send2[1] =  iTemps43;  // program value 
                                    midi_send2[0] = 0xC0 | iTemps44; // controller 
                                }
                            }
                            if (volume2 != iTemps48)
                            {
                                volume2 = iTemps48;
                                //  jack_midi_clear_buffer(midi_port_buf);
                                midistat += 1.0f;
                                midi_send2 = jack_midi_event_reserve(midi_port_buf, i, 3);
                                if (midi_send2)
                                {
                                    midi_send2[2] = iTemps48;  // volume value
                                    midi_send2[1] =  0x07; // set controler channel volume
                                    midi_send2[0] = 0xB0 | iTemps44; // controller + channel
                                }
                            }
                            if (send2 > iTemps41)   //20
                            {
                                // pitch wheel clear
                                if (fpitch2 == 1.0)
                                {
                                    midi_send2 = jack_midi_event_reserve(midi_port_buf, i, 3);
                                    if (midi_send2)
                                    {
                                        midi_send2[2] =  0x40;  // pitch value
                                        midi_send2[1] = 0x00 ; // pitch value
                                        midi_send2[0] = 0xE0 |  iTemps44;	// controller + channel
                                    }
                                }
                                noten2 = preNote + iTemps42;
                                send2 = 0;
                                midistat += 1.0f;
                                if ((noten2>=0)&(noten2<=127))
                                {
                                    midi_send2 = jack_midi_event_reserve(midi_port_buf, i, 3);
                                    if (midi_send2)
                                    {
                                        midi_send2[2] = iTemps40; // velocity 
                                        midi_send2[1] = noten2; //  note
                                        midi_send2[0] = 0x90 | iTemps44;  // note on + channel
                                    }
                                    // pitch wheel set auto
                                    if (fpitch2 == 1.0)
                                    {
                                        if (piwe < 0) piwe = 0;
                                        if (fConsta2 > 0x3fff) piwe = 0x3fff;
                                        midi_send2 = jack_midi_event_reserve(midi_port_buf, i, 3);
                                        if (midi_send2)
                                        {
                                            midi_send2[2] = (piwe >> 7) & 0x7f;  // pitch
                                            midi_send2[1] = piwe & 0x7f ; // pitch
                                            midi_send2[0] = 0xE0 |  iTemps44; // controller + channel
                                        }
                                    }
                                }
                            }
                        }
                       // myTBeatDetector.setSampleRate (fSamplingFreq);
                        myTBeatDetector.AudioProcess (beat0,  fTemps38);
                        if (myTBeatDetector.BeatPulse == TRUE)
                        {
                            send++;
                            if (fcheckbox10 == 1.0) send1++;
                            if (fcheckbox11 == 1.0) send2++;
                        }
                    }
                    // end if playmidi = 1
                }
                else // if input < 0.05
                {
                    if  (playmidi == 1)
                    {
                        if ((weg > fTemps37) | (cpu_load > 75.0))
                        {
                            fConsta1 = 2000.0f;
                            if ((weg <  fTemps37a) | (cpu_load > 75.0))  // 5.0
                            {
                                midistat += 1.0f;
                                midi_send = jack_midi_event_reserve(midi_port_buf, i, 3);
                                if (midi_send)
                                {
                                    midi_send[2] = iTemps26; // velocity 
                                    midi_send[1] = 123;  // all notes off 
                                    midi_send[0] = 0xB0 | iTemps30 ;	// controller 
                                }
                                if (fcheckbox10 == 1.0)
                                {
                                    midistat += 1.0f;
                                    midi_send1 = jack_midi_event_reserve(midi_port_buf, i, 3);
                                    if (midi_send1)
                                    {
                                        midi_send1[2] = iTemps32; // velocity 
                                        midi_send1[1] = 123;  // all notes off 
                                        midi_send1[0] = 0xB0 |  iTemps35;	// controller 
                                    }
                                }
                                if (fcheckbox11 == 1.0)
                                {
                                    midistat += 1.0f;
                                    midi_send2 = jack_midi_event_reserve(midi_port_buf, i, 3);
                                    if (midi_send2)
                                    {
                                        midi_send2[2] = iTemps40; // velocity 
                                        midi_send2[1] = 123;  // all notes off 
                                        midi_send2[0] = 0xB0 |  iTemps44;	// controller 
                                    }
                                }
                                midistat = 0.0f;
                            }
                        }
                        weg++;
                    }
                    else if ((shownote == 1) & (playmidi == 0))
                    {
                        if (weg > (fSamplingFreq)/2)
                        {
                            fConsta1 = 2000.0f;
                        }
                        weg++;
                    }
                }
            }
            else if (shownote == 0)
            {
                fConsta1 = 1000.0f;
            }
            fRect0[1] = fRect0[0];
            iRect1[1] = iRect1[0];
            iRect2[1] = iRect2[0];
            iRect3[1] = iRect3[0];
            fRect4[1] = fRect4[0];
            fVect1[1] = fVect1[0];
            fRect5[1] = fRect5[0];
            fVect0[1] = fVect0[0];
	    fRechp0[1] = fRechp0[0];
	    fVechp0[1] = fVechp0[0];
        }
    };


    virtual void compute (int count, float** input, float** output)
    {
        if (checky != 0)        // play
        {
            // compressor
            float fSlowcom0 = fentrycom0;
            float fSlowcom1 = expf((0 - (fConstcom2 / max(fConstcom2, fslidercom0))));
            float fSlowcom2 = expf((0 - (fConstcom2 / max(fConstcom2, fslidercom1))));
            float fSlowcom3 = fentrycom1;
            float fSlowcom4 = (1.000000f / (1.000000e-03f + fSlowcom3));
            float fSlowcom5 = fentrycom2;
            // compressor end
            float 	fSlow0 = fslider0;
            float 	fSlow1 = powf(10, (2.500000e-02f * fslider1));
            float 	fSlow2 = (1 + fSlow1);
            float 	fSlow3 = (fConst1 * fSlow2);
            float 	fSlow4 = (2 * (0 - ((1 + fSlow3) - fSlow1)));
            float 	fSlow5 = (fConst1 * (fSlow1 - 1));
            float 	fSlow6 = (fConst2 * sqrtf(fSlow1));
            float 	fSlow7 = (fSlow2 - (fSlow6 + fSlow5));
            float 	fSlow8 = powf(10, (2.500000e-02f * fslider2));
            float 	fSlow9 = (1 + fSlow8);
            float 	fSlow10 = (fConst4 * fSlow9);
            float 	fSlow11 = (0 - (2 * ((fSlow8 + fSlow10) - 1)));
            float 	fSlow12 = (fConst5 * sqrtf(fSlow8));
            float 	fSlow13 = (fConst4 * (fSlow8 - 1));
            float 	fSlow14 = ((1 + (fSlow8 + fSlow13)) - fSlow12);
            float 	fSlow15 = checky;
            float 	fSlow16 = (7.118644f * fSlow15);
            int 	iSlow17 = int(fcheckbox1);
            float 	fSlow18 = (9.999871e-04f * powf(10, (5.000000e-02f * fslider3)));
            float 	fSlow19 = (1.0f - fslider4);
            float 	fSlow20 = fslider5;
            int 	iSlow21 = int((int((fSlow20 - 1)) & 4095));
            int 	iSlow22 = int((int(fSlow20) & 4095));
            float 	fSlow23 = (1.0f / tanf((fConst6 * fentry0)));
            float 	fSlow24 = (fSlow23 - 1);
            float 	fSlow25 = (1.0f / (1 + fSlow23));
            float 	fSlow26 = (1.0f / tanf((fConst8 * (fConst7 - (6.283185f * fentry1)))));
            float 	fSlow27 = (1 + fSlow26);
            float 	fSlow28 = (1.0f / fSlow27);
            float 	fSlow29 = (0 - ((fSlow26 - 1) / fSlow27));
            int 	iSlow30 = int(fcheckbox2);
            float 	fSlow31 = tanf((fConst6 * fslider6));
            float 	fSlow32 = (2 * (1 - (1.0f / (fSlow31 * fSlow31))));
            float 	fSlow33 = (1.0f / fSlow31);
            float 	fSlow34 = (1 + ((fSlow33 - 0.765367f) / fSlow31));
            float 	fSlow35 = (1.0f / (1 + ((0.765367f + fSlow33) / fSlow31)));
            float 	fSlow36 = (1 + ((fSlow33 - 1.847759f) / fSlow31));
            float 	fSlow37 = (1.0f / (1 + ((1.847759f + fSlow33) / fSlow31)));
            float 	fSlow38 = (fConst6 * fslider7);
            float 	fSlow39 = (1.0f / (1 + fSlow38));
            float 	fSlow40 = (1 - fSlow38);
            int 	iSlow41 = int(fcheckbox3);
            float 	fSlow42 = fslider8;
            float 	fSlow43 = powf(10.0f, (2 * fslider9));
            float 	fSlow44 = (9.999871e-04f * powf(10, (5.000000e-02f * (fslider10 - 10))));
            int 	iSlow45 = int(fcheckbox4);
            float 	fSlow46 = (fSlow9 - (fSlow12 + fSlow13));
            float 	fSlow47 = (2 * (0 - ((1 + fSlow10) - fSlow8)));
            float 	fSlow48 = (fSlow8 + fSlow12);
            float 	fSlow49 = ((1 + fSlow48) - fSlow13);
            float 	fSlow50 = (1.0f / (1 + (fSlow13 + fSlow48)));
            float 	fSlow51 = (fSlow1 * ((1 + (fSlow1 + fSlow5)) - fSlow6));
            float 	fSlow52 = (fSlow1 + fSlow6);
            float 	fSlow53 = (fSlow1 * (1 + (fSlow5 + fSlow52)));
            float 	fSlow54 = (((fSlow1 + fSlow3) - 1) * (0 - (2 * fSlow1)));
            float 	fSlow55 = (1.0f / ((1 + fSlow52) - fSlow5));
            float 	fSlow56 = fslider11;
            float 	fSlow57 = (9.999872e-05f * powf(4.0f, fSlow56));
            float 	fSlow58 = fslider13;
            float 	fSlow59 = ((1 - max(0, (0 - fSlow58))) * fslider12);
            float 	fSlow60 = powf(2.0f, (2.3f * fSlow56));
            float 	fSlow61 = (1 - (fConst10 * (fSlow60 / powf(2.0f, (1.0f + (2.0f * (1.0f - fSlow56)))))));
            float 	fSlow62 = (9.999871e-04f * (0 - (2.0f * (fSlow61 * cosf((fConst9 * fSlow60))))));
            float 	fSlow63 = (9.999871e-04f * (fSlow61 * fSlow61));
            float 	fSlow64 = (1 - max(0, fSlow58));
            int 	iSlow65 = int(fcheckbox5);
            float 	fSlow66 = (0.5 + fslider14);
            float 	fSlow67 = (2 * (1 - fSlow66));
            float 	fSlow68 = fslider15;
            float 	fSlow69 = (1 - fSlow68);
            float 	fSlow70 = (0.7f + (0.28f * fslider16));
            int 	iSlow71 = int(fcheckbox6);
            float 	fSlow72 = (9.999871e-04f * powf(10, (5.000000e-02f * fslider17)));
            int 	iSlow73 = int((1 + int((int((int((fConst11 * fslider18)) - 1)) & 131071))));
            float 	fSlow74 = (1.000000e-02f * fslider19);
            int 	iSlow75 = int(fcheckbox7);
            float 	fSlow76 = expf((0 - (fConst6 * fslider20)));
            float 	fSlow77 = (2 * cosf((fConst12 * fslider21)));
            float 	fSlow78 = (0.5f * (fslider22 * (1 - (fSlow76 * fSlow76))));
            int 	iSlow79 = int(fcheckbox8);
            float 	fSlow80 = fslider23;
            float 	fSlow81 = fslider24;
            float 	fSlow82 = (1 - max(0, (0 - fSlow81)));
            float 	fSlow83 = fslider25;
            float 	fSlow84 = (1 - max(0, fSlow83));
            float 	fSlow85 = (fSlow84 * fSlow82);
            float 	fSlow86 = (1 - max(0, fSlow81));
            float 	fSlow87 = (fSlow84 * fSlow86);
            int 	iSlow88 = int(checkbox7);
            float 	fSlow89 = (1 - max(0, (0 - fSlow83)));
            float 	fSlow90 = (fSlow89 * fSlow82);
            float 	fSlow91 = (fSlow89 * fSlow86);
            float* input0 = input[0];
            float* output0 = output[2];
            float* output1 = output[0];
            float* output2 = output[3];
            float* output3 = output[1];
            for (int i=0; i<count; i++)
            {
                float 	S0[2];
                float 	S1[2];
                float 	S2[2];
                float 	S3[2];
                float 	S4[2];
                float 	S5[2];
                if (fcheckboxcom1 == 1.0)     // compressor
                {
                    float fTempcom0 = input0[i];
                    fReccom1[0] = ((fConstcom1 * fabsf(fTempcom0)) + (fConstcom0 * fReccom1[1]));
                    float fTempcom2 = max(fReccom1[0], fReccom1[0]);
                    float fTempcom3 = ((fSlowcom2 * (fReccom0[1] >= fTempcom2)) + (fSlowcom1 * (fReccom0[1] < fTempcom2)));
                    fReccom0[0] = ((fTempcom2 * (1 - fTempcom3)) + (fReccom0[1] * fTempcom3));
                    float fTempcom4 = max(0, ((fSlowcom3 + (20 * log10f(fReccom0[0]))) - fSlowcom0));
                    float fTempcom5 = min(1, max(0, (fSlowcom4 * fTempcom4)));
                    float fTempcom6 = (fSlowcom5 * fTempcom5);
                    float fTempcom7 = ((fTempcom4 / ((1 + fTempcom6) - fTempcom5)) * (fTempcom5 - fTempcom6));
                    float fTempcom8 = powf(10, (5.000000e-02f * fTempcom7));
                    fVec0[0]= (fTempcom0 * fTempcom8);
                }
                else fVec0[0] = input0[i]; // compressor end
                S5[0] = (fSlow15 * fVec0[1]);
                S5[1] = (fSlow16 * fVec0[1]);
                fRec4[0] = ((0.999f * fRec4[1]) + fSlow18);
                float fTemp0 = (fRec4[0] * S5[iSlow17]);
                fRec3[0] = (0.5f * ((2 * fTemp0) + (1.76f * fRec3[1])));
                S4[0] = fRec3[0];
                float 	S6[2];
                float 	S7[2];
                float 	S8[2];
                float fTemp1 = (fTemp0 + (fSlow19 * fRec6[1]));
                fVec1[IOTA&4095] = fTemp1;
                fRec6[0] = (0.5f * (fVec1[(IOTA-iSlow22)&4095] + fVec1[(IOTA-iSlow21)&4095]));
                S8[0] = fRec6[0];
                fVec2[0] = (fSlow25 * fRec6[0]);
                fRec8[0] = (fVec2[1] + (fSlow25 * (fRec6[0] + (fSlow24 * fRec8[1]))));
                float fTemp2 = (fSlow28 * fRec8[0]);
                fVec3[0] = fTemp2;
                fRec7[0] = ((fVec3[0] + (fSlow29 * fRec7[1])) - fVec3[1]);
                S8[1] = fRec7[0];
                float fTemp3 = S8[iSlow30];
                S7[0] = fTemp3;
                fVec4[0] = (fSlow39 * fTemp3);
                fRec12[0] = ((fSlow39 * (fTemp3 + (fSlow40 * fRec12[1]))) - fVec4[1]);
                fVec5[0] = (fSlow39 * fRec12[0]);
                fRec11[0] = ((fSlow39 * (fRec12[0] + (fSlow40 * fRec11[1]))) - fVec5[1]);
                fRec10[0] = (fRec11[0] - (fSlow37 * ((fSlow36 * fRec10[2]) + (fSlow32 * fRec10[1]))));
                fRec9[0] = ((fSlow37 * (fRec10[2] + (fRec10[0] + (2 * fRec10[1])))) - (fSlow35 * ((fSlow34 * fRec9[2]) + (fSlow32 * fRec9[1]))));
                S7[1] = (fSlow35 * (fRec9[2] + (fRec9[0] + (2 * fRec9[1]))));
                float fTemp4 = max(-1, min(1, (fSlow43 * (fSlow42 + S7[iSlow41]))));
                float fTemp5 = (fTemp4 * (1 - (0.333333f * (fTemp4 * fTemp4))));
                fVec6[0] = fTemp5;
                fRec5[0] = ((fVec6[0] + (0.995f * fRec5[1])) - fVec6[1]);
                fRec13[0] = (fSlow44 + (0.999f * fRec13[1]));
                float fTemp6 = (fRec13[0] * fRec5[0]);
                S6[0] = fTemp6;
                fVec7[0] = (fSlow39 * fTemp6);
                fRec17[0] = ((fSlow39 * (fTemp6 + (fSlow40 * fRec17[1]))) - fVec7[1]);
                fVec8[0] = (fSlow39 * fRec17[0]);
                fRec16[0] = ((fSlow39 * (fRec17[0] + (fSlow40 * fRec16[1]))) - fVec8[1]);
                fRec15[0] = (fRec16[0] - (fSlow37 * ((fSlow36 * fRec15[2]) + (fSlow32 * fRec15[1]))));
                fRec14[0] = ((fSlow37 * (fRec15[2] + (fRec15[0] + (2 * fRec15[1])))) - (fSlow35 * ((fSlow34 * fRec14[2]) + (fSlow32 * fRec14[1]))));
                S6[1] = (fSlow35 * (fRec14[2] + (fRec14[0] + (2 * fRec14[1]))));
                S4[1] = S6[iSlow41];
                float fTemp7 = S4[iSlow45];
                fVec9[0] = fTemp7;
                fRec2[0] = (fSlow50 * ((fSlow8 * (((fSlow49 * fVec9[0]) + (fSlow47 * fVec9[1])) + (fSlow46 * fVec9[2]))) - ((fSlow14 * fRec2[2]) + (fSlow11 * fRec2[1]))));
                fRec1[0] = (fSlow55 * ((((fSlow54 * fRec2[1]) + (fSlow53 * fRec2[0])) + (fSlow51 * fRec2[2])) + (0 - ((fSlow7 * fRec1[2]) + (fSlow4 * fRec1[1])))));
                S3[0] = fRec1[0];
                fRec19[0] = (fSlow57 + (0.999f * fRec19[1]));
                fRec20[0] = (fSlow62 + (0.999f * fRec20[1]));
                fRec21[0] = (fSlow63 + (0.999f * fRec21[1]));
                fRec18[0] = (0 - (((fRec21[0] * fRec18[2]) + (fRec20[0] * fRec18[1])) - (fSlow59 * (fRec1[0] * fRec19[0]))));
                S3[1] = ((fRec18[0] + (fSlow64 * fRec1[0])) - fRec18[1]);
                float fTemp8 = S3[iSlow65];
                S2[0] = fTemp8;
                float fTemp9 = (1.500000e-02f * fTemp8);
                fRec31[0] = ((fSlow69 * fRec30[1]) + (fSlow68 * fRec31[1]));
                fVec10[IOTA&2047] = (fTemp9 + (fSlow70 * fRec31[0]));
                fRec30[0] = fVec10[(IOTA-1640)&2047];
                fRec33[0] = ((fSlow69 * fRec32[1]) + (fSlow68 * fRec33[1]));
                fVec11[IOTA&2047] = (fTemp9 + (fSlow70 * fRec33[0]));
                fRec32[0] = fVec11[(IOTA-1580)&2047];
                fRec35[0] = ((fSlow69 * fRec34[1]) + (fSlow68 * fRec35[1]));
                fVec12[IOTA&2047] = (fTemp9 + (fSlow70 * fRec35[0]));
                fRec34[0] = fVec12[(IOTA-1514)&2047];
                fRec37[0] = ((fSlow69 * fRec36[1]) + (fSlow68 * fRec37[1]));
                fVec13[IOTA&2047] = (fTemp9 + (fSlow70 * fRec37[0]));
                fRec36[0] = fVec13[(IOTA-1445)&2047];
                fRec39[0] = ((fSlow69 * fRec38[1]) + (fSlow68 * fRec39[1]));
                fVec14[IOTA&2047] = (fTemp9 + (fSlow70 * fRec39[0]));
                fRec38[0] = fVec14[(IOTA-1379)&2047];
                fRec41[0] = ((fSlow69 * fRec40[1]) + (fSlow68 * fRec41[1]));
                fVec15[IOTA&2047] = (fTemp9 + (fSlow70 * fRec41[0]));
                fRec40[0] = fVec15[(IOTA-1300)&2047];
                fRec43[0] = ((fSlow69 * fRec42[1]) + (fSlow68 * fRec43[1]));
                fVec16[IOTA&2047] = (fTemp9 + (fSlow70 * fRec43[0]));
                fRec42[0] = fVec16[(IOTA-1211)&2047];
                fRec45[0] = ((fSlow69 * fRec44[1]) + (fSlow68 * fRec45[1]));
                fVec17[IOTA&2047] = (fTemp9 + (fSlow70 * fRec45[0]));
                fRec44[0] = fVec17[(IOTA-1139)&2047];
                float fTemp10 = (((((((fRec44[0] + fRec42[0]) + fRec40[0]) + fRec38[0]) + fRec36[0]) + fRec34[0]) + fRec32[0]) + fRec30[0]);
                fVec18[IOTA&1023] = (fTemp10 + (0.5f * fRec28[1]));
                fRec28[0] = fVec18[(IOTA-579)&1023];
                float 	fRec29 = (0 - (fTemp10 - fRec28[1]));
                fVec19[IOTA&511] = (fRec29 + (0.5f * fRec26[1]));
                fRec26[0] = fVec19[(IOTA-464)&511];
                float 	fRec27 = (fRec26[1] - fRec29);
                fVec20[IOTA&511] = (fRec27 + (0.5f * fRec24[1]));
                fRec24[0] = fVec20[(IOTA-364)&511];
                float 	fRec25 = (fRec24[1] - fRec27);
                fVec21[IOTA&255] = (fRec25 + (0.5f * fRec22[1]));
                fRec22[0] = fVec21[(IOTA-248)&255];
                float 	fRec23 = (fRec22[1] - fRec25);
                S2[1] = ((fSlow66 * (fRec23 + fTemp9)) + (fSlow67 * fTemp8));
                fRec46[0] = (fSlow72 + (0.999f * fRec46[1]));
                float fTemp11 = (fRec46[0] * S2[iSlow71]);
                S1[0] = fTemp11;
                fRec47[IOTA&262143] = (fTemp11 + (fSlow74 * fRec47[(IOTA-iSlow73)&262143]));
                S1[1] = fRec47[(IOTA-0)&262143];
                float fTemp12 = S1[iSlow75];
                fVec22[0] = fTemp12;
                S0[0] = fVec22[0];
                fRec48[0] = ((fSlow78 * (fVec22[0] - fVec22[2])) + (fSlow76 * ((fSlow77 * fRec48[1]) - (fSlow76 * fRec48[2]))));
                S0[1] = (fRec48[0] + fVec22[0]);
                float fTemp13 = S0[iSlow79];
                fVec23[0] = fTemp13;
                fRec0[0] = ((fVec23[0] + (fSlow80 * fVec23[3])) - (fSlow0 * fRec0[5]));
                output0[i] = (fSlow85 * fRec0[0]);
                float 	S9[2];
                S9[0] = (fSlow87 * fRec0[0]);
                S9[1] = (fSlow84 * fRec0[0]);
                output1[i] = S9[iSlow88];
                output2[i] = (fSlow90 * fRec0[0]);
                float 	S10[2];
                S10[0] = (fSlow91 * fRec0[0]);
                S10[1] = (fSlow89 * fRec0[0]);
                output3[i] = S10[iSlow88];
                // post processing
                for (int i=5; i>0; i--) fRec0[i] = fRec0[i-1];
                for (int i=3; i>0; i--) fVec23[i] = fVec23[i-1];
                fRec48[2] = fRec48[1];
                fRec48[1] = fRec48[0];
                fVec22[2] = fVec22[1];
                fVec22[1] = fVec22[0];
                fRec46[1] = fRec46[0];
                fRec22[1] = fRec22[0];
                fRec24[1] = fRec24[0];
                fRec26[1] = fRec26[0];
                fRec28[1] = fRec28[0];
                fRec44[1] = fRec44[0];
                fRec45[1] = fRec45[0];
                fRec42[1] = fRec42[0];
                fRec43[1] = fRec43[0];
                fRec40[1] = fRec40[0];
                fRec41[1] = fRec41[0];
                fRec38[1] = fRec38[0];
                fRec39[1] = fRec39[0];
                fRec36[1] = fRec36[0];
                fRec37[1] = fRec37[0];
                fRec34[1] = fRec34[0];
                fRec35[1] = fRec35[0];
                fRec32[1] = fRec32[0];
                fRec33[1] = fRec33[0];
                fRec30[1] = fRec30[0];
                fRec31[1] = fRec31[0];
                fRec18[2] = fRec18[1];
                fRec18[1] = fRec18[0];
                fRec21[1] = fRec21[0];
                fRec20[1] = fRec20[0];
                fRec19[1] = fRec19[0];
                fRec1[2] = fRec1[1];
                fRec1[1] = fRec1[0];
                fRec2[2] = fRec2[1];
                fRec2[1] = fRec2[0];
                fVec9[2] = fVec9[1];
                fVec9[1] = fVec9[0];
                fRec14[2] = fRec14[1];
                fRec14[1] = fRec14[0];
                fRec15[2] = fRec15[1];
                fRec15[1] = fRec15[0];
                fRec16[1] = fRec16[0];
                fVec8[1] = fVec8[0];
                fRec17[1] = fRec17[0];
                fVec7[1] = fVec7[0];
                fRec13[1] = fRec13[0];
                fRec5[1] = fRec5[0];
                fVec6[1] = fVec6[0];
                fRec9[2] = fRec9[1];
                fRec9[1] = fRec9[0];
                fRec10[2] = fRec10[1];
                fRec10[1] = fRec10[0];
                fRec11[1] = fRec11[0];
                fVec5[1] = fVec5[0];
                fRec12[1] = fRec12[0];
                fVec4[1] = fVec4[0];
                fRec7[1] = fRec7[0];
                fVec3[1] = fVec3[0];
                fRec8[1] = fRec8[0];
                fVec2[1] = fVec2[0];
                fRec6[1] = fRec6[0];
                IOTA = IOTA+1;
                fRec3[1] = fRec3[0];
                fRec4[1] = fRec4[0];
                fReccom0[1] = fReccom0[0];
                fReccom1[1] = fReccom1[0];
                fVec0[1] = fVec0[0];
                // post processing midi
                fRect0[1] = fRect0[0];
                iRect1[1] = iRect1[0];
                iRect2[1] = iRect2[0];
                iRect3[1] = iRect3[0];
                fRect4[1] = fRect4[0];
                fVect1[1] = fVect1[0];
                fRect5[1] = fRect5[0];
                fVect0[1] = fVect0[0];
		fRechp0[1] = fRechp0[0];
		fVechp0[1] = fVechp0[0]; 
            }
        }
        else
        {
            float* input0 = input[0];
            float* output0 = output[0];
            float* output1 = output[1];
            float* output2 = output[2];
            float* output3 = output[3];
            for (int i=0; i<count; i++)
            {
                float fTemp0 = 0.0f;
                output0[i] = fTemp0;
                output1[i] = fTemp0;
                output2[i] = fTemp0;
                output3[i] = fTemp0;
                // post processing midi
                fRect0[1] = fRect0[0];
                iRect1[1] = iRect1[0];
                iRect2[1] = iRect2[0];
                iRect3[1] = iRect3[0];
                fRect4[1] = fRect4[0];
                fVect1[1] = fVect1[0];
                fRect5[1] = fRect5[0];
                fVect0[1] = fVect0[0];
		fRechp0[1] = fRechp0[0];
		fVechp0[1] = fVechp0[0]; 
            }
        }
    }
};

mydsp	DSP;

