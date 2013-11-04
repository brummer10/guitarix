// generated from file '../src/plugins/dubber.dsp' by dsp2cc:
// Code generated with Faust 0.9.58 (http://faust.grame.fr)

#include "gx_plugin.h"
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cmath>
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>

#define fmax(x, y) (((x) > (y)) ? (x) : (y))
#define fmin(x, y) (((x) < (y)) ? (x) : (y))

#ifndef N_
#define N_(String) (String)
#endif
#ifndef NC_
#define NC_(Context, String) (String)
#endif

#define always_inline inline __attribute__((always_inline))

namespace pluginlib {
namespace dubbe {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	float 	gain;
	float 	fRec0[2];
	float 	gain_out;
	float 	fclip1;
	float 	fclip2;
	float 	fclip3;
	float 	fclip4;
	float 	fclips1;
	float 	fclips2;
	float 	fclips3;
	float 	fclips4;
	float 	rplay1;
	float 	rplay2;
	float 	rplay3;
	float 	rplay4;
	float 	record1;
	int 	iVec0[2];
	int 	IOTA1;
	int 	IOTA2;
	int 	IOTA3;
	int 	IOTA4;
	int 	IOTAR1;
	int 	IOTAR2;
	int 	IOTAR3;
	int 	IOTAR4;
	float *tape1;
	float 	fConst0;
	float 	fConst1;
	float 	fConst2;
	float 	reset1;
	int 	RecSize1[2];
	float 	rectime0;
	float 	fRec1[2];
	float 	fRec2[2];
	int 	iRec3[2];
	int 	iRec4[2];
	float 	play1;
	float 	playh1;
	float 	gain1;
	float 	record2;
	int 	iVec2[2];
	float *tape2;
	float 	reset2;
	int 	RecSize2[2];
	float 	rectime1;
	float 	fRec6[2];
	float 	fRec7[2];
	int 	iRec8[2];
	int 	iRec9[2];
	float 	play2;
	float 	playh2;
	float 	gain2;
	float 	record3;
	int 	iVec4[2];
	float *tape3;
	float 	reset3;
	int 	RecSize3[2];
	float 	rectime2;
	float 	fRec11[2];
	float 	fRec12[2];
	int 	iRec13[2];
	int 	iRec14[2];
	float 	play3;
	float 	playh3;
	float 	gain3;
	float 	record4;
	int 	iVec6[2];
	float *tape4;
	float 	reset4;
	int 	RecSize4[2];
	float 	rectime3;
	float 	fRec16[2];
	float 	fRec17[2];
	int 	iRec18[2];
	int 	iRec19[2];
	float 	play4;
	float 	playh4;
	float 	gain4;
	bool save1;
	bool save2;
	bool save3;
	bool save4;
	bool RP1;
	bool RP2;
	bool RP3;
	bool RP4;
	bool mem_allocated;
	void mem_alloc();
	void mem_free();
	void clear_state_f();
	int activate(bool start);
	int load_ui_f(const UiBuilder& b, int form);
	void init(unsigned int samplingFreq);
	void compute(int count, float *input0, float *output0);
	int register_par(const ParamReg& reg);
    void save_array();
    void load_array();

	static void clear_state_f_static(PluginDef*);
	static int activate_static(bool start, PluginDef*);
	static int load_ui_f_static(const UiBuilder& b, int form);
	static void init_static(unsigned int samplingFreq, PluginDef*);
	static void compute_static(int count, float *input0, float *output0, PluginDef*);
	static int register_params_static(const ParamReg& reg);
	static void del_instance(PluginDef *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginDef(),
	  tape1(0),
	  tape2(0),
	  tape3(0),
	  tape4(0),
	  save1(false),
	  save2(false),
	  save3(false),
	  save4(false),
	  RP1(false),
	  RP2(false),
	  RP3(false),
	  RP4(false),
	  mem_allocated(false) {
	version = PLUGINDEF_VERSION;
	flags = 0;
	id = "dubber";
	name = N_("Dubber");
	groups = 0;
	description = N_("Live Looper"); // description (tooltip)
	category = N_("Echo / Delay");       // category
	shortname = "";     // shortname
	mono_audio = compute_static;
	stereo_audio = 0;
	set_samplerate = init_static;
	activate_plugin = activate_static;
	register_params = register_params_static;
	load_ui = load_ui_f_static;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
    activate(false);
}

inline void Dsp::clear_state_f()
{
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) iVec0[i] = 0;
	for (int i=0; i<4194304; i++) tape1[i] = 0;
	for (int i=0; i<2; i++) RecSize1[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) iRec3[i] = 0;
	for (int i=0; i<2; i++) iRec4[i] = 0;
	for (int i=0; i<2; i++) iVec2[i] = 0;
	for (int i=0; i<4194304; i++) tape2[i] = 0;
	for (int i=0; i<2; i++) RecSize2[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) iRec8[i] = 0;
	for (int i=0; i<2; i++) iRec9[i] = 0;
	for (int i=0; i<2; i++) iVec4[i] = 0;
	for (int i=0; i<4194304; i++) tape3[i] = 0;
	for (int i=0; i<2; i++) RecSize3[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) iRec13[i] = 0;
	for (int i=0; i<2; i++) iRec14[i] = 0;
	for (int i=0; i<2; i++) iVec6[i] = 0;
	for (int i=0; i<4194304; i++) tape4[i] = 0;
	for (int i=0; i<2; i++) RecSize4[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) iRec18[i] = 0;
	for (int i=0; i<2; i++) iRec19[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	IOTA1 = 0;
	IOTA2 = 0;
	IOTA3 = 0;
	IOTA4 = 0;
	IOTAR1 = 0;
	IOTAR2 = 0;
	IOTAR3 = 0;
	IOTAR4 = 0;
	fConst0 = (1e+01f / float(fmin(192000, fmax(1, fSamplingFreq))));
	fConst1 = (0 - fConst0);
    fConst2 = (1.0 / float(fmin(192000, fmax(1, fSamplingFreq))));
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void Dsp::mem_alloc()
{
	if (!tape1) tape1 = new float[4194304];
	if (!tape2) tape2 = new float[4194304];
	if (!tape3) tape3 = new float[4194304];
	if (!tape4) tape4 = new float[4194304];
	mem_allocated = true;
}

void Dsp::mem_free()
{
	mem_allocated = false;
	if (tape1) { delete tape1; tape1 = 0; }
	if (tape2) { delete tape2; tape2 = 0; }
	if (tape3) { delete tape3; tape3 = 0; }
	if (tape4) { delete tape4; tape4 = 0; }
}

void Dsp::load_array()
{
    size_t lSize;
    std::string pPath = getenv("HOME");
    if (pPath.empty()) {
        struct passwd *pw = getpwuid(getuid());
        pPath = pw->pw_dir;
    }
    FILE *Tape1 = fopen((pPath+"/.config/guitarix/tape1.bin").c_str(), "rb");
    if (Tape1!=NULL) { 
        lSize = 4194304 - int(rectime0/fConst2);
        RecSize1[1] = fread(tape1,sizeof(tape1[0]),lSize,Tape1);
        fclose (Tape1);
        IOTAR1= RecSize1[1] - int(RecSize1[1]*(100-fclips1)*0.01);
        //fprintf (stderr,"Read tape(1) size: %i\n",RecSize1[1]);
    }

    FILE *Tape2 = fopen((pPath+"/.config/guitarix/tape2.bin").c_str(), "rb");
    if (Tape2!=NULL) { 
        lSize = 4194304 - int(rectime1/fConst2);
        RecSize2[1] = fread(tape2,sizeof(tape2[0]),lSize,Tape2);
        fclose (Tape2);
        IOTAR2= RecSize2[1] - int(RecSize2[1]*(100-fclips2)*0.01);
        //fprintf (stderr,"Read tape(2) size: %i\n",RecSize2[1]);
    }

    FILE *Tape3 = fopen((pPath+"/.config/guitarix/tape3.bin").c_str(), "rb");
    if (Tape3!=NULL) { 
        lSize = 4194304 - int(rectime2/fConst2);
        RecSize3[1] = fread(tape3,sizeof(tape3[0]),lSize,Tape3);
        fclose (Tape3);
        IOTAR3= RecSize3[1] - int(RecSize3[1]*(100-fclips3)*0.01);
        //fprintf (stderr,"Read tape(3) size: %i\n",RecSize3[1]);
    }

    FILE *Tape4 = fopen((pPath+"/.config/guitarix/tape4.bin").c_str(), "rb");
    if (Tape4!=NULL) {
        lSize = 4194304 - int(rectime3/fConst2);
        RecSize4[1] = fread(tape4,sizeof(tape4[0]),lSize,Tape4);
        fclose (Tape4);
        IOTAR4= RecSize4[1] - int(RecSize4[1]*(100-fclips4)*0.01);
        //fprintf (stderr,"Read tape(4) size: %i\n",RecSize4[1]);
    }
}

void Dsp::save_array()
{
    size_t lSize;
    size_t result;
    std::string pPath = getenv ("HOME");
    if (pPath.empty()) {
        struct passwd *pw = getpwuid(getuid());
        pPath = pw->pw_dir;
    }
    if (save1) {
        FILE *Tape1 = fopen((pPath+ "/.config/guitarix/tape1.bin").c_str(), "wb");
        if (Tape1!=NULL) { 
            lSize = 4194304 - int(rectime0/fConst2);
            if (lSize) {
                result = fwrite(tape1, sizeof(tape1[0]), lSize, Tape1);
                if (result != lSize) {fputs("Save tape(1) error\n",stderr);}
            }
            fclose (Tape1);
            save1 = false;
            //fprintf (stderr,"Save tape(1) size: %i\n",result);
        }
    }
    if (save2) {
        FILE *Tape2 = fopen((pPath+"/.config/guitarix/tape2.bin").c_str(), "wb");
        if (Tape2!=NULL) { 
            lSize = 4194304 - int(rectime1/fConst2);
            if (lSize) {
                result = fwrite (tape2, sizeof(tape2[0]), lSize, Tape2);
                if (result != lSize) {fputs("Save tape(2) error\n",stderr);}
            }
            fclose (Tape2);
            save2 = false;
            //fprintf (stderr,"Save tape(2) size: %i\n",result);
        }
    }
    if (save3) {
        FILE *Tape3 = fopen((pPath+"/.config/guitarix/tape3.bin").c_str(), "wb");
            if (Tape3!=NULL) { 
            lSize = 4194304 - int(rectime2/fConst2);
            if (lSize) {
                result = fwrite(tape3, sizeof(tape3[0]), lSize, Tape3);
                if (result != lSize) {fputs ("Save tape(3) error\n",stderr);}
            }
            fclose (Tape3);
            save3 = false;
            //fprintf (stderr,"Save tape(3) size: %i\n",result);
        }
    }
    if (save4) {
        FILE *Tape4 = fopen((pPath+"/.config/guitarix/tape4.bin").c_str(), "wb");
        if (Tape4!=NULL) {
            lSize = 4194304 - int(rectime3/fConst2);
            if (lSize) {
                result = fwrite(tape4, sizeof(tape4[0]), lSize, Tape4);
                if (result != lSize) {fputs("Save tape(4) error\n",stderr);}
            }
            fclose (Tape4);
            save4 = false;
            //fprintf (stderr,"Save tape(4) size: %i\n",result);
        }
    }
}

int Dsp::activate(bool start)
{
	if (start) {
		if (!mem_allocated) {
			mem_alloc();
			clear_state_f();
            load_array();
		}
	} else if (mem_allocated) {
        save_array();
		mem_free();
	}
	return 0;
}

int Dsp::activate_static(bool start, PluginDef *p)
{
	return static_cast<Dsp*>(p)->activate(start);
}

void always_inline Dsp::compute(int count, float *input0, float *output0)
{
    // trigger save array on exit
	if(record1 || reset1) save1 = true;
    if(record2 || reset2) save2 = true;
    if(record3 || reset3) save3 = true;
    if(record4 || reset4) save4 = true;
    // make play/ reverse play button act as radio button
    if (!RecSize1[0]) {play1 = 0.0;rplay1 = 0.0;}
    else if (rplay1 && !RP1) {play1 = 0.0;RP1=true;}
    else if (play1 && RP1) {rplay1 = 0.0;RP1=false;}
    if (!RecSize2[0]) {play2 = 0.0;rplay2 = 0.0;}
    else if (rplay2 && !RP2) {play2 = 0.0;RP2=true;}
    else if (play2 && RP2) {rplay2 = 0.0;RP2=false;}
    if (!RecSize3[0]) {play3 = 0.0;rplay3 = 0.0;}
    else if (rplay3 && !RP3) {play3 = 0.0;RP3=true;}
    else if (play3 && RP3) {rplay3 = 0.0;RP3=false;}
    if (!RecSize4[0]) {play4 = 0.0;rplay4 = 0.0;}
    else if (rplay4 && !RP4) {play4 = 0.0;RP4=true;}
    else if (play4 && RP4) {rplay4 = 0.0;RP4=false;}
    // switch off record when buffer is full
    record1     = rectime0? record1 : 0.0;
	record2     = rectime1? record2 : 0.0;
	record3     = rectime2? record3 : 0.0;
	record4     = rectime3? record4 : 0.0;
    // reset clip when reset is pressed
    fclip1 = reset1? 100.0:fclip1;
    fclip2 = reset2? 100.0:fclip2;
    fclip3 = reset3? 100.0:fclip3;
    fclip4 = reset4? 100.0:fclip4;
    fclips1 = reset1? 0.0:fclips1;
    fclips2 = reset2? 0.0:fclips2;
    fclips3 = reset3? 0.0:fclips3;
    fclips4 = reset1? 0.0:fclips4;
    // switch off reset button when buffer is empty 
    reset1     = (rectime0 < 4194304*fConst2)? reset1 : 0.0;
	reset2     = (rectime1 < 4194304*fConst2)? reset2 : 0.0;
	reset3     = (rectime2 < 4194304*fConst2)? reset3 : 0.0;
	reset4     = (rectime3 < 4194304*fConst2)? reset4 : 0.0;
    // set play head position
    float ph1      = 1.0/(RecSize1[0] * 0.001);
    playh1 = fmin(1000,fmax(0,float(IOTAR1*ph1)));
    float ph2      = 1.0/(RecSize2[0] * 0.001);
    playh2 = fmin(1000,fmax(0,float(IOTAR2*ph2)));
    float ph3      = 1.0/(RecSize3[0] * 0.001);
    playh3 = fmin(1000,fmax(0,float(IOTAR3*ph3)));
    float ph4      = 1.0/(RecSize4[0] * 0.001);
    playh4 = fmin(1000,fmax(0,float(IOTAR4*ph4)));
    // engine var settings
	float 	fSlow0 = (0.0010000000000000009f * powf(10,(0.05f * gain)));
	float 	fSlow1 = gain_out;
    int 	iSlow3 = int(record1);
	int 	iSlow4 = int((1 - reset1));
	float 	fSlow5 = (((1 - iSlow3) * gain1) * (play1+rplay1));
	int 	iSlow6 = int(record2);
	int 	iSlow7 = int((1 - reset2));
	float 	fSlow8 = (((1 - iSlow6) * gain2) * (play2+rplay2));
	int 	iSlow9 = int(record3);
	int 	iSlow10 = int((1 - reset3));
	float 	fSlow11 = (((1 - iSlow9) * gain3) * (play3+rplay3));
	int 	iSlow12 = int(record4);
	int 	iSlow13 = int((1 - reset4));
	float 	fSlow14 = (((1 - iSlow12) * gain4) * (play4+rplay4));
	float 	fSlow15 = (0.0001f * fSlow1);
    float   iClip1  = fclip1*0.01;
	float   iClip2  = fclip2*0.01;
	float   iClip3  = fclip3*0.01;
	float   iClip4  = fclip4*0.01;
	float   iClips1  = (100-fclips1)*0.01;
	float   iClips2  = (100-fclips2)*0.01;
	float   iClips3  = (100-fclips3)*0.01;
	float   iClips4  = (100-fclips4)*0.01;
    // run loop
	for (int i=0; i<count; i++) {
		fRec0[0] = (fSlow0 + (0.999f * fRec0[1]));
		float fTemp0 = ((float)input0[i] * fRec0[0]);
		iVec0[0] = iSlow3;
		float fTemp1 = (iSlow3 * fTemp0);
        RecSize1[0] = fmin(4194304, (int)(iSlow4 * (((iSlow3 - iVec0[1]) <= 0) * (iSlow3 + RecSize1[1]))));
		int iTemp2 = (4194304 - RecSize1[0]);
		rectime0 = iTemp2*fConst2;
        int iTemp3 = fmin(4194304-1, (int)(4194304 - iTemp2));
		if (iSlow3 == 1) {
        IOTA1 = IOTA1>int(iTemp3*iClip1)? iTemp3 - int(iTemp3*iClips1):IOTA1+1;
		tape1[IOTA1] = fTemp1;
        }
        if (rplay1) {
        IOTAR1 = IOTAR1< (iTemp3 - int(iTemp3*iClips1))? int(iTemp3*iClip1):IOTAR1-1;
        } else if (play1) {
        IOTAR1 = IOTAR1>int(iTemp3*iClip1)? iTemp3 - int(iTemp3*iClips1):IOTAR1+1;
        }
		
        float fTemp4 = ((int((fRec1[1] != 0.0f)))?((int(((fRec2[1] > 0.0f) & (fRec2[1] < 1.0f))))?fRec1[1]:0):((int(((fRec2[1] == 0.0f) & (iTemp3 != iRec3[1]))))?fConst0:((int(((fRec2[1] == 1.0f) & (iTemp3 != iRec4[1]))))?fConst1:0)));
		fRec1[0] = fTemp4;
		fRec2[0] = fmax(0.0f, fmin(1.0f, (fRec2[1] + fTemp4)));
		iRec3[0] = ((int(((fRec2[1] >= 1.0f) & (iRec4[1] != iTemp3))))?iTemp3:iRec3[1]);
		iRec4[0] = ((int(((fRec2[1] <= 0.0f) & (iRec3[1] != iTemp3))))?iTemp3:iRec4[1]);
		iVec2[0] = iSlow6;
		float fTemp5 = (iSlow6 * fTemp0);
		RecSize2[0] = fmin(4194304, (int)(iSlow7 * (((iSlow6 - iVec2[1]) <= 0) * (iSlow6 + RecSize2[1]))));
		int iTemp6 = (4194304 - RecSize2[0]);
		rectime1 = iTemp6*fConst2;
		int iTemp7 = fmin(4194304-1, (int)(4194304 - iTemp6));
		if (iSlow6 == 1) {
		IOTA2 = IOTA2>int(iTemp7*iClip2)? iTemp7 - int(iTemp7*iClips2):IOTA2+1;
		tape2[IOTA2] = fTemp5;
        }
		if (rplay2) {
        IOTAR2 = IOTAR2< (iTemp7 - int(iTemp7*iClips2))? int(iTemp7*iClip2):IOTAR2-1;
        } else if (play2) {
        IOTAR2 = IOTAR2>int(iTemp7*iClip2)? iTemp7 - int(iTemp7*iClips2):IOTAR2+1;
        }
		
        float fTemp8 = ((int((fRec6[1] != 0.0f)))?((int(((fRec7[1] > 0.0f) & (fRec7[1] < 1.0f))))?fRec6[1]:0):((int(((fRec7[1] == 0.0f) & (iTemp7 != iRec8[1]))))?fConst0:((int(((fRec7[1] == 1.0f) & (iTemp7 != iRec9[1]))))?fConst1:0)));
		fRec6[0] = fTemp8;
		fRec7[0] = fmax(0.0f, fmin(1.0f, (fRec7[1] + fTemp8)));
		iRec8[0] = ((int(((fRec7[1] >= 1.0f) & (iRec9[1] != iTemp7))))?iTemp7:iRec8[1]);
		iRec9[0] = ((int(((fRec7[1] <= 0.0f) & (iRec8[1] != iTemp7))))?iTemp7:iRec9[1]);
		iVec4[0] = iSlow9;
		float fTemp9 = (iSlow9 * fTemp0);
		RecSize3[0] = fmin(4194304, (int)(iSlow10 * (((iSlow9 - iVec4[1]) <= 0) * (iSlow9 + RecSize3[1]))));
		int iTemp10 = (4194304 - RecSize3[0]);
		rectime2 = iTemp10*fConst2;
		int iTemp11 = fmin(4194304-1, (int)(4194304 - iTemp10));
		if (iSlow9 == 1) {
		IOTA3 = IOTA3>int(iTemp11*iClip3)? iTemp11 - int(iTemp11*iClips3):IOTA3+1;
		tape3[IOTA3] = fTemp9;
        }
		if (rplay3) {
        IOTAR3 = IOTAR3< (iTemp11 - int(iTemp11*iClips3))? int(iTemp11*iClip3):IOTAR3-1;
        } else if (play3) {
        IOTAR3 = IOTAR3>int(iTemp11*iClip3)? iTemp11 - int(iTemp11*iClips3):IOTAR3+1;
        }
		
        float fTemp12 = ((int((fRec11[1] != 0.0f)))?((int(((fRec12[1] > 0.0f) & (fRec12[1] < 1.0f))))?fRec11[1]:0):((int(((fRec12[1] == 0.0f) & (iTemp11 != iRec13[1]))))?fConst0:((int(((fRec12[1] == 1.0f) & (iTemp11 != iRec14[1]))))?fConst1:0)));
		fRec11[0] = fTemp12;
		fRec12[0] = fmax(0.0f, fmin(1.0f, (fRec12[1] + fTemp12)));
		iRec13[0] = ((int(((fRec12[1] >= 1.0f) & (iRec14[1] != iTemp11))))?iTemp11:iRec13[1]);
		iRec14[0] = ((int(((fRec12[1] <= 0.0f) & (iRec13[1] != iTemp11))))?iTemp11:iRec14[1]);
		iVec6[0] = iSlow12;
		float fTemp13 = (iSlow12 * fTemp0);
		RecSize4[0] = fmin(4194304, (int)(iSlow13 * (((iSlow12 - iVec6[1]) <= 0) * (iSlow12 + RecSize4[1]))));
		int iTemp14 = (4194304 - RecSize4[0]);
		rectime3 = iTemp14*fConst2;
		int iTemp15 = fmin(4194304-1, (int)(4194304 - iTemp14));
		if (iSlow12 == 1) {
		IOTA4 = IOTA4>int(iTemp15*iClip4)? iTemp15 - int(iTemp15*iClips4):IOTA4+1;
		tape4[IOTA4] = fTemp13;
        }
		if (rplay4) {
        IOTAR4 = IOTAR4< (iTemp15 - int(iTemp15*iClips4))? int(iTemp15*iClip4):IOTAR4-1;
        } else if (play4) {
        IOTAR4 = IOTAR4>int(iTemp15*iClip4)? iTemp15 - int(iTemp15*iClips4):IOTAR4+1;
        }
		
        float fTemp16 = ((int((fRec16[1] != 0.0f)))?((int(((fRec17[1] > 0.0f) & (fRec17[1] < 1.0f))))?fRec16[1]:0):((int(((fRec17[1] == 0.0f) & (iTemp15 != iRec18[1]))))?fConst0:((int(((fRec17[1] == 1.0f) & (iTemp15 != iRec19[1]))))?fConst1:0)));
		fRec16[0] = fTemp16;
		fRec17[0] = fmax(0.0f, fmin(1.0f, (fRec17[1] + fTemp16)));
		iRec18[0] = ((int(((fRec17[1] >= 1.0f) & (iRec19[1] != iTemp15))))?iTemp15:iRec18[1]);
		iRec19[0] = ((int(((fRec17[1] <= 0.0f) & (iRec18[1] != iTemp15))))?iTemp15:iRec19[1]);
		output0[i] = (float)((fSlow15 * ((fSlow14 * ((fRec17[0] * tape4[IOTAR4]) + ((1.0f - fRec17[0]) * tape4[IOTAR4]))) + ((fSlow11 * ((fRec12[0] * tape3[IOTAR3]) + ((1.0f - fRec12[0]) * tape3[IOTAR3]))) + ((fSlow8 * ((fRec7[0] * tape2[IOTAR2]) + ((1.0f - fRec7[0]) * tape2[IOTAR2]))) + (fSlow5 * ((fRec2[0] * tape1[IOTAR1]) + ((1.0f - fRec2[0]) * tape1[IOTAR1]))))))) + (fTemp0));
		// post processing
		iRec19[1] = iRec19[0];
		iRec18[1] = iRec18[0];
		fRec17[1] = fRec17[0];
		fRec16[1] = fRec16[0];
		RecSize4[1] = RecSize4[0];
		iVec6[1] = iVec6[0];
		iRec14[1] = iRec14[0];
		iRec13[1] = iRec13[0];
		fRec12[1] = fRec12[0];
		fRec11[1] = fRec11[0];
		RecSize3[1] = RecSize3[0];
		iVec4[1] = iVec4[0];
		iRec9[1] = iRec9[0];
		iRec8[1] = iRec8[0];
		fRec7[1] = fRec7[0];
		fRec6[1] = fRec6[0];
		RecSize2[1] = RecSize2[0];
		iVec2[1] = iVec2[0];
		iRec4[1] = iRec4[0];
		iRec3[1] = iRec3[0];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
		RecSize1[1] = RecSize1[0];
		iVec0[1] = iVec0[0];
		fRec0[1] = fRec0[0];
	}
}

void __rt_func Dsp::compute_static(int count, float *input0, float *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("dubber.clip1","","S",N_("percentage clip at the delay length "),&fclip1, 1e+02f, 0.0f, 1e+02f, 1.0f);
	reg.registerVar("dubber.clip2","","S",N_("percentage clip at the delay length "),&fclip2, 1e+02f, 0.0f, 1e+02f, 1.0f);
	reg.registerVar("dubber.clip3","","S",N_("percentage clip at the delay length "),&fclip3, 1e+02f, 0.0f, 1e+02f, 1.0f);
	reg.registerVar("dubber.clip4","","S",N_("percentage clip at the delay length "),&fclip4, 1e+02f, 0.0f, 1e+02f, 1.0f);
	reg.registerVar("dubber.clips1","","S",N_("percentage cut on the delay start "),&fclips1, 0.0f, 0.0f, 1e+02f, 1.0f);
	reg.registerVar("dubber.clips2","","S",N_("percentage cut on the delay start "),&fclips2, 0.0f, 0.0f, 1e+02f, 1.0f);
	reg.registerVar("dubber.clips3","","S",N_("percentage cut on the delay start "),&fclips3, 0.0f, 0.0f, 1e+02f, 1.0f);
	reg.registerVar("dubber.clips4","","S",N_("percentage cut on the delay start "),&fclips4, 0.0f, 0.0f, 1e+02f, 1.0f);
	reg.registerVar("dubber.bar1","","S",N_("remaining recording time in sec"),&rectime0, 0.0, 0.0, 96.0, 1.0);
	reg.registerVar("dubber.bar2","","S",N_("remaining recording time in sec"),&rectime1, 0.0, 0.0, 96.0, 1.0);
	reg.registerVar("dubber.bar3","","S",N_("remaining recording time in sec"),&rectime2, 0.0, 0.0, 96.0, 1.0);
	reg.registerVar("dubber.bar4","","S",N_("remaining recording time in sec"),&rectime3, 0.0, 0.0, 96.0, 1.0);
	reg.registerVar("dubber.gain","","S",N_("overall gain of the input"),&gain, 0.0f, -2e+01f, 12.0f, 0.1f);
	reg.registerVar("dubber.level1","","S",N_("percentage of the delay gain level"),&gain1, 5e+01f, 0.0f, 1e+02f, 1.0f);
	reg.registerVar("dubber.level2","","S",N_("percentage of the delay gain level"),&gain2, 5e+01f, 0.0f, 1e+02f, 1.0f);
	reg.registerVar("dubber.level3","","S",N_("percentage of the delay gain level"),&gain3, 5e+01f, 0.0f, 1e+02f, 1.0f);
	reg.registerVar("dubber.level4","","S",N_("percentage of the delay gain level"),&gain4, 5e+01f, 0.0f, 1e+02f, 1.0f);
	reg.registerVar("dubber.mix","","S",N_("overall gain_out of the delay line in percent"),&gain_out, 1e+02f, 0.0f, 1.5e+02f, 1.0f);
	reg.registerVar("dubber.play1","","B",N_("play tape 1"),&play1, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("dubber.play2","","B",N_("play tape 2"),&play2, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("dubber.play3","","B",N_("play tape 3"),&play3, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("dubber.play4","","B",N_("play tape 4"),&play4, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("dubber.rplay1","","B",N_("play reverse"),&rplay1, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("dubber.rplay2","","B",N_("play reverse"),&rplay2, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("dubber.rplay3","","B",N_("play reverse"),&rplay3, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("dubber.rplay4","","B",N_("play reverse"),&rplay4, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("dubber.playh1","","S",N_("play position"),&playh1, 0.0, 0.0, 1000.0, 1.0);
	reg.registerVar("dubber.playh2","","S",N_("play position"),&playh2, 0.0, 0.0, 1000.0, 1.0);
	reg.registerVar("dubber.playh3","","S",N_("play position"),&playh3, 0.0, 0.0, 1000.0, 1.0);
	reg.registerVar("dubber.playh4","","S",N_("play position"),&playh4, 0.0, 0.0, 1000.0, 1.0);
	reg.registerVar("dubber.rec1","","B",N_("record"),&record1, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("dubber.rec2","","B",N_("record"),&record2, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("dubber.rec3","","B",N_("record"),&record3, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("dubber.rec4","","B",N_("record"),&record4, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("dubber.reset1","","B",N_("erase"),&reset1, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("dubber.reset2","","B",N_("erase"),&reset2, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("dubber.reset3","","B",N_("erase"),&reset3, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("dubber.reset4","","B",N_("erase"),&reset4, 0.0, 0.0, 1.0, 1.0);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("dubber" "." p)
b.openHorizontalhideBox("");
b.create_feedback_switch(sw_pbutton,PARAM("play1"));
b.create_feedback_switch(sw_pbutton,PARAM("play2"));
b.create_feedback_switch(sw_pbutton,PARAM("play3"));
b.create_feedback_switch(sw_pbutton,PARAM("play4"));
b.closeBox();

b.openHorizontalBox("");
b.create_small_rackknob(PARAM("gain"), 0);

b.openTabBox("");

b.openHorizontalBox(N_("Tape 1"));
b.openpaintampBox("");

b.openVerticalBox("");
b.openHorizontalBox("");
b.insertSpacer();
b.openVerticalBox("");
b.insertSpacer();
b.create_p_display(PARAM("playh1"));
b.insertSpacer();
b.openHorizontalBox("");
b.create_feedback_switch(sw_rbutton,PARAM("rec1"));
b.create_feedback_switch(sw_pbutton,PARAM("play1"));
b.create_feedback_switch(sw_prbutton,PARAM("rplay1"));
b.create_feedback_switch(sw_button,PARAM("reset1"));
b.closeBox();
b.closeBox();

b.insertSpacer();
b.create_port_display(PARAM("bar1"), "buffer");
b.insertSpacer();
b.closeBox();
b.create_feedback_slider(PARAM("clips1"), "cut");
b.create_feedback_slider(PARAM("clip1"), "clip");

b.closeBox();
b.create_small_rackknob(PARAM("level1"), "level");

b.closeBox();
b.closeBox();

b.openHorizontalBox(N_("Tape 2"));
b.openpaintampBox("");
b.openVerticalBox("");

b.openHorizontalBox("");
b.insertSpacer();
b.openVerticalBox("");
b.insertSpacer();
b.create_p_display(PARAM("playh2"));
b.insertSpacer();
b.openHorizontalBox("");
b.create_feedback_switch(sw_rbutton,PARAM("rec2"));
b.create_feedback_switch(sw_pbutton,PARAM("play2"));
b.create_feedback_switch(sw_prbutton,PARAM("rplay2"));
b.create_feedback_switch(sw_button,PARAM("reset2"));
b.closeBox();
b.closeBox();
b.insertSpacer();
b.create_port_display(PARAM("bar2"), "buffer");
b.insertSpacer();
b.closeBox();
b.create_feedback_slider(PARAM("clips2"), "cut");
b.create_feedback_slider(PARAM("clip2"), "clip");

b.closeBox();

b.create_small_rackknob(PARAM("level2"), "level");
b.closeBox();
b.closeBox();

b.openHorizontalBox(N_("Tape 3"));
b.openpaintampBox("");
b.openVerticalBox("");

b.openHorizontalBox("");
b.insertSpacer();
b.openVerticalBox("");
b.insertSpacer();
b.create_p_display(PARAM("playh3"));
b.insertSpacer();
b.openHorizontalBox("");
b.create_feedback_switch(sw_rbutton,PARAM("rec3"));
b.create_feedback_switch(sw_pbutton,PARAM("play3"));
b.create_feedback_switch(sw_prbutton,PARAM("rplay3"));
b.create_feedback_switch(sw_button,PARAM("reset3"));
b.closeBox();
b.closeBox();
b.insertSpacer();
b.create_port_display(PARAM("bar3"), "buffer");
b.insertSpacer();
b.closeBox();
b.create_feedback_slider(PARAM("clips3"), "cut");
b.create_feedback_slider(PARAM("clip3"), "clip");

b.closeBox();
b.create_small_rackknob(PARAM("level3"), "level");
b.closeBox();
b.closeBox();

b.openHorizontalBox(N_("Tape 4"));
b.openpaintampBox("");
b.openVerticalBox("");

b.openHorizontalBox("");
b.insertSpacer();
b.openVerticalBox("");
b.insertSpacer();
b.create_p_display(PARAM("playh4"));
b.insertSpacer();
b.openHorizontalBox("");
b.create_feedback_switch(sw_rbutton,PARAM("rec4"));
b.create_feedback_switch(sw_pbutton,PARAM("play4"));
b.create_feedback_switch(sw_prbutton,PARAM("rplay4"));
b.create_feedback_switch(sw_button,PARAM("reset4"));
b.closeBox();
b.closeBox();
b.insertSpacer();
b.create_port_display(PARAM("bar4"), "buffer");
b.insertSpacer();
b.closeBox();
b.create_feedback_slider(PARAM("clips4"), "cut");
b.create_feedback_slider(PARAM("clip4"), "clip");

b.closeBox();
b.create_small_rackknob(PARAM("level4"), "level");
b.closeBox();
b.closeBox();

b.closeBox();

b.create_small_rackknob(PARAM("mix"), 0);
b.closeBox();

#undef PARAM
        return 0;
    }
	return -1;
}

int Dsp::load_ui_f_static(const UiBuilder& b, int form)
{
	return static_cast<Dsp*>(b.plugin)->load_ui_f(b, form);
}

void Dsp::del_instance(PluginDef *p)
{
	delete static_cast<Dsp*>(p);
}

#if true

PluginDef *plugin() {
    return new Dsp;
}

#else

extern "C" __attribute__ ((visibility ("default"))) int
get_gx_plugin(unsigned int idx, PluginDef **pplugin)
{
    const int count = 1;
    if (!pplugin) {
	return count;
    }
    switch (idx) {
    case 0: *pplugin = new Dsp; return count;
    default: *pplugin = 0; return -1;
    }
}

#endif

} // end namespace dubber
} // end namespace pluginlib
