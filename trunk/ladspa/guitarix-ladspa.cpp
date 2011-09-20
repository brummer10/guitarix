//-----------------------------------------------------
// name : "guitarix"
// version : "0.02.7"
// author : "brummer" 
// contributors : "Julius O. Smith (jos at ccrma.stanford.edu)" 
// license : "BSD"
// copyright : "(c)brummer 2008"
// reference : "http://ccrma.stanford.edu/realsimple/faust_strings/"
//
// Code generated with Faust 0.9.9.4f (http://faust.grame.fr)
//-----------------------------------------------------
/* link with  */
#include <math.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <stack>
#include <string>
#include <iostream>
#include <map>

#include "ladspa.h"


using namespace std;

struct Meta : map<const char*, const char*>
{
    void declare (const char* key, const char* value) { (*this)[key]=value; }
};

	
#define max(x,y) (((x)>(y)) ? (x) : (y))
#define min(x,y) (((x)<(y)) ? (x) : (y))

#define sym(name) xsym(name)
#define xsym(name) #name


// abs is now predefined
//template<typename T> T abs (T a)			{ return (a<T(0)) ? -a : a; }


inline int		lsr (int x, int n)			{ return int(((unsigned int)x) >> n); }

inline int 		int2pow2 (int x)	{ int r=0; while ((1<<r)<x) r++; return r; }



/******************************************************************************
*******************************************************************************

							       VECTOR INTRINSICS

*******************************************************************************
*******************************************************************************/

//inline void *aligned_calloc(size_t nmemb, size_t size) { return (void*)((unsigned)(calloc((nmemb*size)+15,sizeof(char)))+15 & 0xfffffff0); }
inline void *aligned_calloc(size_t nmemb, size_t size)
{
    return (void*)(((size_t)(calloc((nmemb*size)+15,sizeof(char)))+15) & (~15));
}






//---------------------Abstract User Interface--------------------
//
// Abstract definition of a User Interface to be passed to the 
// buildUserInterface method of a Faust Signal Processor
// 
//----------------------------------------------------------------

class UI
{
	bool	fStopped;
public:
		
	UI() : fStopped(false) {}
	virtual ~UI() {}
	
	virtual void addButton(const char* label, float* zone) = 0;
	virtual void addToggleButton(const char* label, float* zone) = 0;
	virtual void addCheckButton(const char* label, float* zone) = 0;
	virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step) = 0;
	virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step) = 0;
	virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step) = 0;
		
	// -- passive widgets
	
	virtual void addNumDisplay(const char* label, float* zone, int precision) = 0;
	virtual void addTextDisplay(const char* label, float* zone, char* names[], float min, float max) = 0;
	virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max) = 0;
	virtual void addVerticalBargraph(const char* label, float* zone, float min, float max) = 0;

	// -- frames and labels
	
	virtual void openFrameBox(const char* label) = 0;
	virtual void openTabBox(const char* label) = 0;
	virtual void openHorizontalBox(const char* label) = 0;
	virtual void openVerticalBox(const char* label) = 0;
	virtual void closeBox() = 0;
	
	virtual void show() = 0;
	virtual void run() = 0;
	
	void stop()		{ fStopped = true; }
	bool stopped() 	{ return fStopped; }

    virtual void declare(float* zone, const char* key, const char* value) {}
};



//------------------Abstract Signal Processor---------------------
//
//  Abstract definition of a Faust Signal Processor
//
//----------------------------------------------------------------
			
class dsp {
 protected:
	int fSamplingFreq;
 public:
	dsp() {}
	virtual ~dsp() {}
	virtual int getNumInputs() 										= 0;
	virtual int getNumOutputs() 									= 0;
	virtual void buildUserInterface(UI* interface) 					= 0;
	virtual void init(int samplingRate) 							= 0;
 	virtual void compute(int len, float** inputs, float** outputs) 	= 0;
};
		

//----------------------------------------------------------------------------
// 	FAUST generated code
//----------------------------------------------------------------------------
		

class mydsp : public dsp {
  private:
	class SIG0 {
	  private:
		int 	fSamplingFreq;
	  public:
		int getNumInputs() 	{ return 0; }
		int getNumOutputs() 	{ return 1; }
		void init(int samplingFreq) {
			fSamplingFreq = samplingFreq;
		}
		void fill (int count, float output[]) {
			for (int i=0; i<count; i++) {
				output[i] = 0.000000f;
				// post processing
			}
		}
	};

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
	float 	fcheckbox0;
	float 	fcheckbox1;
	float 	fslider3;
	float 	fRec4[2];
	float 	fRec3[2];
	float 	fConst6;
	float 	fConst7;
	float 	fConst8;
	float 	fConst9;
	float 	fConst10;
	float 	fConst11;
	float 	fConst12;
	float 	fConst13;
	float 	fConst14;
	float 	fConst15;
	float 	fConst16;
	float 	fConst17;
	float 	fConst18;
	float 	fConst19;
	float 	fConst20;
	float 	fRec15[2];
	float 	fConst21;
	float 	fRec14[2];
	float 	fConst22;
	float 	fRec13[2];
	float 	fRec12[2];
	float 	fRec11[3];
	float 	fRec10[3];
	float 	fslider4;
	float 	fVec1[2];
	float 	fRec9[2];
	float 	fRec16[2];
	float 	fVec2[2];
	float 	fRec8[2];
	float 	fRec7[2];
	float 	fRec6[3];
	float 	fRec5[3];
	float 	fcheckbox2;
	float 	fVec3[3];
	float 	fRec2[3];
	float 	fRec1[3];
	float 	fslider5;
	float 	fRec18[2];
	float 	fConst23;
	float 	fConst24;
	float 	fRec19[2];
	float 	fRec20[2];
	float 	fRec17[3];
	float 	fcheckbox3;
	float 	fRec30[2];
	float 	fslider6;
	int 	IOTA;
	float 	fVec4[2048];
	float 	fRec29[2];
	float 	fRec32[2];
	float 	fVec5[2048];
	float 	fRec31[2];
	float 	fRec34[2];
	float 	fVec6[2048];
	float 	fRec33[2];
	float 	fRec36[2];
	float 	fVec7[2048];
	float 	fRec35[2];
	float 	fRec38[2];
	float 	fVec8[2048];
	float 	fRec37[2];
	float 	fRec40[2];
	float 	fVec9[2048];
	float 	fRec39[2];
	float 	fRec42[2];
	float 	fVec10[2048];
	float 	fRec41[2];
	float 	fRec44[2];
	float 	fVec11[2048];
	float 	fRec43[2];
	float 	fVec12[1024];
	float 	fRec27[2];
	float 	fVec13[512];
	float 	fRec25[2];
	float 	fVec14[512];
	float 	fRec23[2];
	float 	fVec15[256];
	float 	fRec21[2];
	float 	fcheckbox4;
	float 	fslider7;
	float 	fRec45[2];
	float 	fslider8;
	float 	fConst25;
	float 	fslider9;
	float 	fRec46[262144];
	float 	fcheckbox5;
	float 	fVec16[3];
	float 	fConst26;
	float 	fslider10;
	float 	fConst27;
	float 	fslider11;
	float 	fConst28;
	float 	fRec47[3];
	float 	fcheckbox6;
	float 	fVec17[4];
	float 	fslider12;
	float 	fRec0[6];
	float 	fslider13;
  public:
	static void metadata(Meta* m) 	{ 
		m->declare("name", "guitarix");
		m->declare("version", "0.01");
		m->declare("author", "brummer");
		m->declare("contributor", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("license", "BSD");
		m->declare("copyright", "(c)brummer 2008");
		m->declare("reference", "http://ccrma.stanford.edu/realsimple/faust_strings/");
	}

	virtual int getNumInputs() 	{ return 1; }
	virtual int getNumOutputs() 	{ return 2; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceInit(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fslider13 = 0.0f;
		fslider2 = 0.0f;
		fslider1 = 0.0f;
		fslider3 = 0.0f;
		fslider7 = 0.0f;
		fcheckbox1 = 0.0;
		fslider4 = 0.64f;
		fcheckbox2 = 0.0;
		fslider6 = 0.5f;
		fcheckbox4 = 0.0;
		fslider10 = 440.0f;
		fslider11 = 1.0f;
		fcheckbox6 = 0.0;
		fslider5 = 0.0f;
		fcheckbox3 = 0.0;
		fslider9 = 0.0f;
		fslider8 = 0.0f;
		fcheckbox5 = 0.0;
		fslider0 = 0.0f;
		fslider12 = 0.0f;
		fConst0 = (7539.822754f / fSamplingFreq);
		fConst1 = cosf(fConst0);
		fConst2 = (1.414214f * sinf(fConst0));
		fConst3 = (1884.955688f / fSamplingFreq);
		fConst4 = cosf(fConst3);
		fConst5 = (1.414214f * sinf(fConst3));
		for (int i=0; i<2; i++) fVec0[i] = 0;
		fcheckbox0 = 1.0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		for (int i=0; i<2; i++) fRec3[i] = 0;
		fConst6 = tanf((15707.963867f / fSamplingFreq));
		fConst7 = (2 * (1 - (1.0f / (fConst6 * fConst6))));
		fConst8 = (1.0f / fConst6);
		fConst9 = (1 + ((fConst8 - 0.765367f) / fConst6));
		fConst10 = (1.0f / (1 + ((0.765367f + fConst8) / fConst6)));
		fConst11 = (1 + ((fConst8 - 1.847759f) / fConst6));
		fConst12 = (1.0f / (1 + ((1.847759f + fConst8) / fConst6)));
		fConst13 = (408.407043f / fSamplingFreq);
		fConst14 = (1 - fConst13);
		fConst15 = (1.0f / tanf((0.5f * (((3.141593f * fSamplingFreq) - 4526.93457f) / fSamplingFreq))));
		fConst16 = (1 + fConst15);
		fConst17 = (0 - ((fConst15 - 1) / fConst16));
		fConst18 = (1.0f / tanf((2272.725586f / fSamplingFreq)));
		fConst19 = (fConst18 - 1);
		fConst20 = (1.0f / (1 + fConst18));
		for (int i=0; i<2; i++) fRec15[i] = 0;
		fConst21 = (1.0f / fConst16);
		for (int i=0; i<2; i++) fRec14[i] = 0;
		fConst22 = (1.0f / (1 + fConst13));
		for (int i=0; i<2; i++) fRec13[i] = 0;
		for (int i=0; i<2; i++) fRec12[i] = 0;
		for (int i=0; i<3; i++) fRec11[i] = 0;
		for (int i=0; i<3; i++) fRec10[i] = 0;
		for (int i=0; i<2; i++) fVec1[i] = 0;
		for (int i=0; i<2; i++) fRec9[i] = 0;
		for (int i=0; i<2; i++) fRec16[i] = 0;
		for (int i=0; i<2; i++) fVec2[i] = 0;
		for (int i=0; i<2; i++) fRec8[i] = 0;
		for (int i=0; i<2; i++) fRec7[i] = 0;
		for (int i=0; i<3; i++) fRec6[i] = 0;
		for (int i=0; i<3; i++) fRec5[i] = 0;
		for (int i=0; i<3; i++) fVec3[i] = 0;
		for (int i=0; i<3; i++) fRec2[i] = 0;
		for (int i=0; i<3; i++) fRec1[i] = 0;
		for (int i=0; i<2; i++) fRec18[i] = 0;
		fConst23 = (2827.43335f / fSamplingFreq);
		fConst24 = (1413.716675f / fSamplingFreq);
		for (int i=0; i<2; i++) fRec19[i] = 0;
		for (int i=0; i<2; i++) fRec20[i] = 0;
		for (int i=0; i<3; i++) fRec17[i] = 0;
		for (int i=0; i<2; i++) fRec30[i] = 0;
		IOTA = 0;
		for (int i=0; i<2048; i++) fVec4[i] = 0;
		for (int i=0; i<2; i++) fRec29[i] = 0;
		for (int i=0; i<2; i++) fRec32[i] = 0;
		for (int i=0; i<2048; i++) fVec5[i] = 0;
		for (int i=0; i<2; i++) fRec31[i] = 0;
		for (int i=0; i<2; i++) fRec34[i] = 0;
		for (int i=0; i<2048; i++) fVec6[i] = 0;
		for (int i=0; i<2; i++) fRec33[i] = 0;
		for (int i=0; i<2; i++) fRec36[i] = 0;
		for (int i=0; i<2048; i++) fVec7[i] = 0;
		for (int i=0; i<2; i++) fRec35[i] = 0;
		for (int i=0; i<2; i++) fRec38[i] = 0;
		for (int i=0; i<2048; i++) fVec8[i] = 0;
		for (int i=0; i<2; i++) fRec37[i] = 0;
		for (int i=0; i<2; i++) fRec40[i] = 0;
		for (int i=0; i<2048; i++) fVec9[i] = 0;
		for (int i=0; i<2; i++) fRec39[i] = 0;
		for (int i=0; i<2; i++) fRec42[i] = 0;
		for (int i=0; i<2048; i++) fVec10[i] = 0;
		for (int i=0; i<2; i++) fRec41[i] = 0;
		for (int i=0; i<2; i++) fRec44[i] = 0;
		for (int i=0; i<2048; i++) fVec11[i] = 0;
		for (int i=0; i<2; i++) fRec43[i] = 0;
		for (int i=0; i<1024; i++) fVec12[i] = 0;
		for (int i=0; i<2; i++) fRec27[i] = 0;
		for (int i=0; i<512; i++) fVec13[i] = 0;
		for (int i=0; i<2; i++) fRec25[i] = 0;
		for (int i=0; i<512; i++) fVec14[i] = 0;
		for (int i=0; i<2; i++) fRec23[i] = 0;
		for (int i=0; i<256; i++) fVec15[i] = 0;
		for (int i=0; i<2; i++) fRec21[i] = 0;
		for (int i=0; i<2; i++) fRec45[i] = 0;
		fConst25 = (1.000000e-03f * fSamplingFreq);
		for (int i=0; i<262144; i++) fRec46[i] = 0;
		for (int i=0; i<3; i++) fVec16[i] = 0;
		fConst26 = expf((0 - (314.159271f / fSamplingFreq)));
		fConst27 = (6.283185f / fSamplingFreq);
		fConst28 = (0.5f * (1 - (fConst26 * fConst26)));
		for (int i=0; i<3; i++) fRec47[i] = 0;
		for (int i=0; i<4; i++) fVec17[i] = 0;
		for (int i=0; i<6; i++) fRec0[i] = 0;

	}
	virtual void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
	virtual void buildUserInterface(UI* interface) {
		interface->openVerticalBox("guitarix");
		interface->addHorizontalSlider("balance", &fslider13, 0.0f, -1.0f, 1.0f, 1.000000e-03f);
		interface->openHorizontalBox("tone");
		interface->addVerticalSlider("bass", &fslider2, 0.0f, -20.0f, 20.0f, 0.1f);
		interface->addVerticalSlider("treble", &fslider1, 0.0f, -20.0f, 20.0f, 0.1f);
		interface->closeBox();
		interface->openVerticalBox("gain");
		interface->openHorizontalBox("");
		interface->addVerticalSlider("in", &fslider3, 0.0f, -40.0f, 40.0f, 0.1f);
		interface->addVerticalSlider("out", &fslider7, 0.0f, -40.0f, 40.0f, 0.1f);
		interface->closeBox();
		interface->addToggleButton("preamp", &fcheckbox1);
		interface->closeBox();
		interface->openVerticalBox("distortion");
		interface->addVerticalSlider("drive", &fslider4, 0.64f, 0.0f, 1.0f, 1.000000e-02f);
		interface->addToggleButton("on/off", &fcheckbox2);
		interface->closeBox();
		interface->openVerticalBox("freeverb");
		interface->addVerticalSlider("RoomSize", &fslider6, 0.5f, 0.0f, 1.0f, 2.500000e-02f);
		interface->addToggleButton("on/off", &fcheckbox4);
		interface->closeBox();
		interface->openVerticalBox("IR");
		interface->openHorizontalBox("");
		interface->addHorizontalSlider("frequency(Hz)", &fslider10, 440.0f, 20.0f, 2200.0f, 10.0f);
		interface->addHorizontalSlider("peakgain", &fslider11, 1.0f, 0.0f, 10.0f, 0.2f);
		interface->closeBox();
		interface->addToggleButton("on/off", &fcheckbox6);
		interface->closeBox();
		interface->openVerticalBox("crybaby");
		interface->addVerticalSlider("wah", &fslider5, 0.0f, 0.0f, 1.0f, 1.000000e-02f);
		interface->addToggleButton("on/off", &fcheckbox3);
		interface->closeBox();
		interface->openVerticalBox("echo");
		interface->openHorizontalBox("");
		interface->addVerticalSlider("release", &fslider9, 0.0f, 0.0f, 100.0f, 0.1f);
		interface->addVerticalSlider("time", &fslider8, 0.0f, 0.0f, 2000.0f, 1.0f);
		interface->closeBox();
		interface->addToggleButton("on/off", &fcheckbox5);
		interface->closeBox();
		interface->addHorizontalSlider("feedbackgain", &fslider0, 0.0f, -1.0f, 1.0f, 1.000000e-02f);
		interface->addHorizontalSlider("feedforwardgain", &fslider12, 0.0f, -1.0f, 1.0f, 1.000000e-02f);
		interface->closeBox();

	}
	virtual void compute (int count, float** input, float** output) {
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
			float 	fSlow15 = fcheckbox0;
			float 	fSlow16 = (7.118644f * fSlow15);
			int 	iSlow17 = int(fcheckbox1);
			float 	fSlow18 = (9.999871e-04f * powf(10, (5.000000e-02f * fslider3)));
			float 	fSlow19 = powf(10.0f, (2 * fslider4));
			int 	iSlow20 = int(fcheckbox2);
			float 	fSlow21 = (fSlow9 - (fSlow12 + fSlow13));
			float 	fSlow22 = (2 * (0 - ((1 + fSlow10) - fSlow8)));
			float 	fSlow23 = (fSlow8 + fSlow12);
			float 	fSlow24 = ((1 + fSlow23) - fSlow13);
			float 	fSlow25 = (1.0f / (1 + (fSlow13 + fSlow23)));
			float 	fSlow26 = (fSlow1 * ((1 + (fSlow1 + fSlow5)) - fSlow6));
			float 	fSlow27 = (fSlow1 + fSlow6);
			float 	fSlow28 = (fSlow1 * (1 + (fSlow5 + fSlow27)));
			float 	fSlow29 = (((fSlow1 + fSlow3) - 1) * (0 - (2 * fSlow1)));
			float 	fSlow30 = (1.0f / ((1 + fSlow27) - fSlow5));
			float 	fSlow31 = fslider5;
			float 	fSlow32 = (9.999872e-05f * powf(4.0f, fSlow31));
			float 	fSlow33 = powf(2.0f, (2.3f * fSlow31));
			float 	fSlow34 = (1 - (fConst24 * (fSlow33 / powf(2.0f, (1.0f + (2.0f * (1.0f - fSlow31)))))));
			float 	fSlow35 = (9.999871e-04f * (0 - (2.0f * (fSlow34 * cosf((fConst23 * fSlow33))))));
			float 	fSlow36 = (9.999871e-04f * (fSlow34 * fSlow34));
			int 	iSlow37 = int(fcheckbox3);
			float 	fSlow38 = (0.7f + (0.28f * fslider6));
			int 	iSlow39 = int(fcheckbox4);
			float 	fSlow40 = (9.999871e-04f * powf(10, (5.000000e-02f * fslider7)));
			int 	iSlow41 = int((1 + int((int((int((fConst25 * fslider8)) - 1)) & 131071))));
			float 	fSlow42 = (1.000000e-02f * fslider9);
			int 	iSlow43 = int(fcheckbox5);
			float 	fSlow44 = (2 * cosf((fConst27 * fslider10)));
			float 	fSlow45 = (fConst28 * fslider11);
			int 	iSlow46 = int(fcheckbox6);
			float 	fSlow47 = fslider12;
			float 	fSlow48 = fslider13;
			float 	fSlow49 = (1 - max(0, fSlow48));
			float 	fSlow50 = (1 - max(0, (0 - fSlow48)));
			float* input0 = input[0];
			float* output0 = output[0];
			float* output1 = output[1];
			for (int i=0; i<count; i++) {
				float 	S0[2];
				float 	S1[2];
				float 	S2[2];
				float 	S3[2];
				float 	S4[2];
				float 	S5[2];
				fVec0[0] = input0[i];
				S5[0] = (fSlow15 * fVec0[1]);
				S5[1] = (fSlow16 * fVec0[1]);
				fRec4[0] = (fSlow18 + (0.999f * fRec4[1]));
				fRec3[0] = (0.5f * ((2 * (fRec4[0] * S5[iSlow17])) + (1.76f * fRec3[1])));
				S4[0] = fRec3[0];
				fRec15[0] = (fConst20 * ((fRec3[0] + fRec3[1]) + (fConst19 * fRec15[1])));
				fRec14[0] = ((fConst21 * (fRec15[0] - fRec15[1])) + (fConst17 * fRec14[1]));
				fRec13[0] = (fConst22 * ((fRec14[0] - fRec14[1]) + (fConst14 * fRec13[1])));
				fRec12[0] = (fConst22 * ((fRec13[0] - fRec13[1]) + (fConst14 * fRec12[1])));
				fRec11[0] = (fRec12[0] - (fConst12 * ((fConst11 * fRec11[2]) + (fConst7 * fRec11[1]))));
				fRec10[0] = ((fConst12 * (fRec11[2] + (fRec11[0] + (2 * fRec11[1])))) - (fConst10 * ((fConst9 * fRec10[2]) + (fConst7 * fRec10[1]))));
				float fTemp0 = max(-1, min(1, (fSlow19 * (1.000000e-02f + (fConst10 * (fRec10[2] + (fRec10[0] + (2 * fRec10[1]))))))));
				float fTemp1 = (fTemp0 * (1 - (0.333333f * (fTemp0 * fTemp0))));
				fVec1[0] = fTemp1;
				fRec9[0] = ((fVec1[0] + (0.995f * fRec9[1])) - fVec1[1]);
				fRec16[0] = (3.981020e-04f + (0.999f * fRec16[1]));
				float fTemp2 = (fRec16[0] * fRec9[0]);
				fVec2[0] = fTemp2;
				fRec8[0] = (fConst22 * ((fVec2[0] - fVec2[1]) + (fConst14 * fRec8[1])));
				fRec7[0] = (fConst22 * ((fRec8[0] - fRec8[1]) + (fConst14 * fRec7[1])));
				fRec6[0] = (fRec7[0] - (fConst12 * ((fConst11 * fRec6[2]) + (fConst7 * fRec6[1]))));
				fRec5[0] = ((fConst12 * (fRec6[2] + (fRec6[0] + (2 * fRec6[1])))) - (fConst10 * ((fConst9 * fRec5[2]) + (fConst7 * fRec5[1]))));
				S4[1] = (fConst10 * (fRec5[2] + (fRec5[0] + (2 * fRec5[1]))));
				float fTemp3 = S4[iSlow20];
				fVec3[0] = fTemp3;
				fRec2[0] = (fSlow25 * ((fSlow8 * (((fSlow24 * fVec3[0]) + (fSlow22 * fVec3[1])) + (fSlow21 * fVec3[2]))) - ((fSlow14 * fRec2[2]) + (fSlow11 * fRec2[1]))));
				fRec1[0] = (fSlow30 * ((((fSlow29 * fRec2[1]) + (fSlow28 * fRec2[0])) + (fSlow26 * fRec2[2])) + (0 - ((fSlow7 * fRec1[2]) + (fSlow4 * fRec1[1])))));
				S3[0] = fRec1[0];
				fRec18[0] = (fSlow32 + (0.999f * fRec18[1]));
				fRec19[0] = (fSlow35 + (0.999f * fRec19[1]));
				fRec20[0] = (fSlow36 + (0.999f * fRec20[1]));
				fRec17[0] = (0 - (((fRec20[0] * fRec17[2]) + (fRec19[0] * fRec17[1])) - (fRec1[0] * fRec18[0])));
				S3[1] = (fRec17[0] - fRec17[1]);
				float fTemp4 = S3[iSlow37];
				S2[0] = fTemp4;
				fRec30[0] = (0.5f * (fRec29[1] + fRec30[1]));
				float fTemp5 = (1.500000e-02f * fTemp4);
				fVec4[IOTA&2047] = (fTemp5 + (fSlow38 * fRec30[0]));
				fRec29[0] = fVec4[(IOTA-1640)&2047];
				fRec32[0] = (0.5f * (fRec31[1] + fRec32[1]));
				fVec5[IOTA&2047] = (fTemp5 + (fSlow38 * fRec32[0]));
				fRec31[0] = fVec5[(IOTA-1580)&2047];
				fRec34[0] = (0.5f * (fRec33[1] + fRec34[1]));
				fVec6[IOTA&2047] = (fTemp5 + (fSlow38 * fRec34[0]));
				fRec33[0] = fVec6[(IOTA-1514)&2047];
				fRec36[0] = (0.5f * (fRec35[1] + fRec36[1]));
				fVec7[IOTA&2047] = (fTemp5 + (fSlow38 * fRec36[0]));
				fRec35[0] = fVec7[(IOTA-1445)&2047];
				fRec38[0] = (0.5f * (fRec37[1] + fRec38[1]));
				fVec8[IOTA&2047] = (fTemp5 + (fSlow38 * fRec38[0]));
				fRec37[0] = fVec8[(IOTA-1379)&2047];
				fRec40[0] = (0.5f * (fRec39[1] + fRec40[1]));
				fVec9[IOTA&2047] = (fTemp5 + (fSlow38 * fRec40[0]));
				fRec39[0] = fVec9[(IOTA-1300)&2047];
				fRec42[0] = (0.5f * (fRec41[1] + fRec42[1]));
				fVec10[IOTA&2047] = (fTemp5 + (fSlow38 * fRec42[0]));
				fRec41[0] = fVec10[(IOTA-1211)&2047];
				fRec44[0] = (0.5f * (fRec43[1] + fRec44[1]));
				fVec11[IOTA&2047] = (fTemp5 + (fSlow38 * fRec44[0]));
				fRec43[0] = fVec11[(IOTA-1139)&2047];
				float fTemp6 = (((((((fRec43[0] + fRec41[0]) + fRec39[0]) + fRec37[0]) + fRec35[0]) + fRec33[0]) + fRec31[0]) + fRec29[0]);
				fVec12[IOTA&1023] = (fTemp6 + (0.5f * fRec27[1]));
				fRec27[0] = fVec12[(IOTA-579)&1023];
				float 	fRec28 = (0 - (fTemp6 - fRec27[1]));
				fVec13[IOTA&511] = (fRec28 + (0.5f * fRec25[1]));
				fRec25[0] = fVec13[(IOTA-464)&511];
				float 	fRec26 = (fRec25[1] - fRec28);
				fVec14[IOTA&511] = (fRec26 + (0.5f * fRec23[1]));
				fRec23[0] = fVec14[(IOTA-364)&511];
				float 	fRec24 = (fRec23[1] - fRec26);
				fVec15[IOTA&255] = (fRec24 + (0.5f * fRec21[1]));
				fRec21[0] = fVec15[(IOTA-248)&255];
				float 	fRec22 = (fRec21[1] - fRec24);
				S2[1] = ((0.5f * fRec22) + (1.0075f * fTemp4));
				fRec45[0] = (fSlow40 + (0.999f * fRec45[1]));
				float fTemp7 = (fRec45[0] * S2[iSlow39]);
				S1[0] = fTemp7;
				fRec46[IOTA&262143] = (fTemp7 + (fSlow42 * fRec46[(IOTA-iSlow41)&262143]));
				S1[1] = fRec46[(IOTA-0)&262143];
				float fTemp8 = S1[iSlow43];
				fVec16[0] = fTemp8;
				S0[0] = fVec16[0];
				fRec47[0] = ((fSlow45 * (fVec16[0] - fVec16[2])) + (fConst26 * ((fSlow44 * fRec47[1]) - (fConst26 * fRec47[2]))));
				S0[1] = (fRec47[0] + fVec16[0]);
				float fTemp9 = S0[iSlow46];
				fVec17[0] = fTemp9;
				fRec0[0] = ((fVec17[0] + (fSlow47 * fVec17[3])) - (fSlow0 * fRec0[5]));
				output0[i] = (fSlow49 * fRec0[0]);
				output1[i] = (fSlow50 * fRec0[0]);
				// post processing
				for (int i=5; i>0; i--) fRec0[i] = fRec0[i-1];
				for (int i=3; i>0; i--) fVec17[i] = fVec17[i-1];
				fRec47[2] = fRec47[1]; fRec47[1] = fRec47[0];
				fVec16[2] = fVec16[1]; fVec16[1] = fVec16[0];
				fRec45[1] = fRec45[0];
				fRec21[1] = fRec21[0];
				fRec23[1] = fRec23[0];
				fRec25[1] = fRec25[0];
				fRec27[1] = fRec27[0];
				fRec43[1] = fRec43[0];
				fRec44[1] = fRec44[0];
				fRec41[1] = fRec41[0];
				fRec42[1] = fRec42[0];
				fRec39[1] = fRec39[0];
				fRec40[1] = fRec40[0];
				fRec37[1] = fRec37[0];
				fRec38[1] = fRec38[0];
				fRec35[1] = fRec35[0];
				fRec36[1] = fRec36[0];
				fRec33[1] = fRec33[0];
				fRec34[1] = fRec34[0];
				fRec31[1] = fRec31[0];
				fRec32[1] = fRec32[0];
				fRec29[1] = fRec29[0];
				IOTA = IOTA+1;
				fRec30[1] = fRec30[0];
				fRec17[2] = fRec17[1]; fRec17[1] = fRec17[0];
				fRec20[1] = fRec20[0];
				fRec19[1] = fRec19[0];
				fRec18[1] = fRec18[0];
				fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
				fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
				fVec3[2] = fVec3[1]; fVec3[1] = fVec3[0];
				fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
				fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
				fRec7[1] = fRec7[0];
				fRec8[1] = fRec8[0];
				fVec2[1] = fVec2[0];
				fRec16[1] = fRec16[0];
				fRec9[1] = fRec9[0];
				fVec1[1] = fVec1[0];
				fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
				fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
				fRec12[1] = fRec12[0];
				fRec13[1] = fRec13[0];
				fRec14[1] = fRec14[0];
				fRec15[1] = fRec15[0];
				fRec3[1] = fRec3[0];
				fRec4[1] = fRec4[0];
				fVec0[1] = fVec0[0];
		}
	}
};




		
	

//-----------------------------------portCollectorg--------------------------------------
//
// portCollectorg is passed to the buildUserInterface method of a dsp object
// in order to build a description of its inputs, outputs and control ports.
// This description is used to fill a LADSPA_Descriptor
//
//--------------------------------------------------------------------------------------



//--------------------------------useful constants--------------------------------------

#define MAXPORT 1024
static const int ICONTROLG 	= LADSPA_PORT_INPUT|LADSPA_PORT_CONTROL;
static const int OCONTROLG 	= LADSPA_PORT_OUTPUT|LADSPA_PORT_CONTROL;
static const int RANGEG 		= LADSPA_PORT_INPUT|LADSPA_PORT_CONTROL;

static const char* inames[] = {
					"input00", "input01", "input02", "input03", "input04",
					"input05", "input06", "input07", "input08", "input09",
					"input10", "input11", "input12", "input13", "input14",
					"input15", "input16", "input17", "input18", "input19",
					"input20", "input21", "input22", "input23", "input24",
					"input25", "input26", "input27", "input28", "input29",
					"input30", "input31", "input32", "input33", "input34",
					"input35", "input36", "input37", "input38", "input39"
};

static const char* onames[] = {
					"output00", "output01", "output02", "output03", "output04",
					"output05", "output06", "output07", "output08", "output09",
					"output10", "output11", "output12", "output13", "output14",
					"output15", "output16", "output17", "output18", "output19",
					"output20", "output21", "output22", "output23", "output24",
					"output25", "output26", "output27", "output28", "output29",
					"output30", "output31", "output32", "output33", "output34",
					"output35", "output36", "output37", "output38", "output39"
};



class portCollectorg : public UI
{		
 private:

	//--------------------------------------------------------------------------------------

	const int				fInsCount;					// number of audio input ports
	const int				fOutsCount;					// number of audio output ports
	int						fCtrlCount;					// number of control ports
	
	LADSPA_PortDescriptor 	fPortDescs[MAXPORT];		// table of port descriptors to be used in a LADSPA_Descriptor
	const char* 			fPortNames[MAXPORT];		// table of port names to be used in a LADSPA_Descriptor
	LADSPA_PortRangeHint 	fPortHints[MAXPORT];		// table of port hints to be used in a LADSPA_Descriptor
	
	string					fPluginName;				// toplevel prefix used as plugin name
	stack<string>			fPrefix;					// current prefix for controls name

	
	//--------------------------------------------------------------------------------------
	string simplify(const string& src)
	{
		int		i=0;
		int		level=2;
		string	dst;
		
		while (src[i] ) {
		
			switch (level) {
			
				case 0 : 	
				case 1 : 			
				case 2 : 	
					// Skip the begin of the label "--foo-"
					// until 3 '-' have been read
					if (src[i]=='-') { level++; }
					break;
							
				case 3 :	
					// copy the content, but skip non alphnum
					// and content in parenthesis
					switch (src[i]) {
						case '(' : 	
						case '[' : 	
							level++;
							break;
							
						case '-' : 	
							dst += '-';
							break;
									
						default :
							if (isalnum(src[i])) {
								dst+= tolower(src[i]); 
							}
							
					}
					break;
					
				default :	
					// here we are inside parenthesis and 
					// we skip the content until we are back to
					// level 3
					switch (src[i]) {
		
						case '(' : 	
						case '[' : 
							level++;
							break;
									
						case ')' : 	
						case ']' : 
							level--;
							break;
							
						default :
							break;
					}
						
			}
			i++;
		}
		return (dst.size() > 0) ? dst :src;
	}

	void addPortDescr(int type, const char* label, int hint, float min=0.0, float max=0.0) 
	{
		string fullname = simplify(fPrefix.top() + "-" + label);
		char * str = strdup(fullname.c_str());
		
		fPortDescs[fInsCount + fOutsCount + fCtrlCount] = type; 
		fPortNames[fInsCount + fOutsCount + fCtrlCount] = str; 
		fPortHints[fInsCount + fOutsCount + fCtrlCount].HintDescriptor = hint;
		fPortHints[fInsCount + fOutsCount + fCtrlCount].LowerBound = min;
		fPortHints[fInsCount + fOutsCount + fCtrlCount].UpperBound = max;
		fCtrlCount++; 
	}
	
	void openAnyBox(const char* label)
	{
		if (fPrefix.size() == 0) {
			// top level label is used as plugin name
			fPluginName = label;
			fPrefix.push(label);
			
		} else {
			string s;
			if (label && label[0]) {
				s = fPrefix.top() + "-" + label;
			} else {
				s = fPrefix.top();
			}
			fPrefix.push(s);
		}
		
	}
	

	
 public:
		
	
	//--------------------------------Collect the audio ports-------------------------------

	portCollectorg(int ins, int outs) : UI(), fInsCount(ins), fOutsCount(outs), fCtrlCount(0) 
	{
		for (int i = 0; i < ins; i++) { 
			fPortDescs[i] = LADSPA_PORT_INPUT | LADSPA_PORT_AUDIO; 
			fPortNames[i] = inames[i]; 
			fPortHints[i].HintDescriptor = 0;
		}
		for (int j = 0; j < outs; j++) {
			fPortDescs[ins + j] = LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO; 
			fPortNames[ins + j] = onames[j]; 
			fPortHints[ins + j].HintDescriptor = 0;
		}
	};

	virtual ~portCollectorg() {}
	
	
	
	//------------------------------Collect the control ports-------------------------------

	virtual void addButton(const char* label, float* zone) { 
		addPortDescr(ICONTROLG, label, LADSPA_HINT_TOGGLED); 
	}
	
	virtual void addToggleButton(const char* label, float* zone) { 
		addPortDescr(ICONTROLG, label, LADSPA_HINT_TOGGLED); 
	}
	
	virtual void addCheckButton(const char* label, float* zone) { 
		addPortDescr(ICONTROLG, label, LADSPA_HINT_TOGGLED); 
	}
		
	virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step) { 
		addPortDescr(ICONTROLG, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE, min, max); 
	}		
		
	virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step) { 
		addPortDescr(ICONTROLG, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE, min, max); 
	}

	virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step) { 
		addPortDescr(ICONTROLG, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE, min, max); 
	}
		
	// -- passive widgets
	
	virtual void addNumDisplay(const char* label, float* zone, int precision) {
		addPortDescr(OCONTROLG, label, 0, -10000, +10000); 
	}
	virtual void addTextDisplay(const char* label, float* zone, char* names[], float min, float max) {
		addPortDescr(OCONTROLG, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE, min, max); 
	}
	virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max) {
		addPortDescr(OCONTROLG, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE, min, max); 
	}
	virtual void addVerticalBargraph(const char* label, float* zone, float min, float max){
		addPortDescr(OCONTROLG, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE, min, max); 
	}

	virtual void openFrameBox(const char* label)		{ openAnyBox(label); }
	virtual void openTabBox(const char* label)		{ openAnyBox(label); }
	virtual void openHorizontalBox(const char* label)	{ openAnyBox(label); }
	virtual void openVerticalBox(const char* label)	{ openAnyBox(label); }
	
	virtual void closeBox() 					{ fPrefix.pop(); }
	
	virtual void show() {}
	virtual void run() 	{}
	
	
	
	//---------------------------------Fill the LADSPA descriptor---------------------------
	
	// generate an ID from a plugin name
	int makeID (const char* s) {
		int h = 0;
		for (int i = 0; s[i]; i++) {
			h = (h << 3) + (s[i] & 7);
		}
		return 1+h%1000;
	}

	// fill a ladspa descriptor with the information collected on ports
	void fillPortDescription (LADSPA_Descriptor * descriptor) {
		const char* name = sym(mydsp);
		descriptor->PortCount 			= fCtrlCount+fInsCount+fOutsCount;
		descriptor->PortDescriptors 	= fPortDescs;
		descriptor->PortNames 			= fPortNames;
		descriptor->PortRangeHints 		= fPortHints;
		
		descriptor->Label = "Simulators";
		descriptor->UniqueID = 4068;
//		descriptor->Label = strdup(fPluginName.c_str());
//		descriptor->UniqueID = makeID(fPluginName.c_str());
		descriptor->Properties = LADSPA_PROPERTY_HARD_RT_CAPABLE;
		descriptor->Name = name;
//		descriptor->Name = "monoamlifier";
		descriptor->Maker = "brummer";
		descriptor->Copyright = "GPL";
	}
};




//--------------------------------------portData----------------------------------------
//
// portData : a user interface used to associate the data buffers and the ports
//
//--------------------------------------------------------------------------------------


class portData : public UI
{	

	
 private:

	
	//--------------------------------------------------------------------------------------

	const int				fInsCount;					// number of audio input ports
	const int				fOutsCount;					// number of audio output ports
	int						fCtrlCount;					// number of control ports
	
	float* 					fPortZone[MAXPORT];			// 
	float* 					fPortData[MAXPORT];
	
	
	//--------------------------------------------------------------------------------------

	void addZone(float* zone) 
	{
		fPortZone[fInsCount + fOutsCount + fCtrlCount] = zone; 
		fCtrlCount++; 
	}
	
	
	
 public:
		
	
	//--------------------------------Collect the audio ports-------------------------------

	portData(int ins, int outs) : UI(), fInsCount(ins), fOutsCount(outs), fCtrlCount(0) {};
	virtual ~portData() {}
	
	
	//------------------------------Collect the control zones-------------------------------

	virtual void addButton(const char* label, float* zone) 			{ addZone(zone); }
	virtual void addToggleButton(const char* label, float* zone)  	{ addZone(zone); }
	virtual void addCheckButton(const char* label, float* zone)  		{ addZone(zone); }
		
	virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step) 		{ addZone(zone); }
	virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step) 	{ addZone(zone); }
	virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step)  			{ addZone(zone); }
		
	// -- passive widgets
	
	virtual void addNumDisplay(const char* label, float* zone, int precision) 						{ addZone(zone); }
	virtual void addTextDisplay(const char* label, float* zone, char* names[], float min, float max) 	{ addZone(zone); }
	virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max) 			{ addZone(zone); }
	virtual void addVerticalBargraph(const char* label, float* zone, float min, float max)			{ addZone(zone); }
	
	virtual void openFrameBox(const char* label)		{ }
	virtual void openTabBox(const char* label)		{ }
	virtual void openHorizontalBox(const char* label)	{ }
	virtual void openVerticalBox(const char* label)	{ }
	virtual void closeBox() 					{ }
	
	virtual void show() {}
	virtual void run() 	{}
	
	
	//---------------------------------interaction with LADSPA------------------------------
	
	void setPortData (unsigned long port, LADSPA_Data* data) {
		fPortData[port] = data;
	}
	
	void updateCtrlZones() {
		for (int i = fInsCount+fOutsCount; i < fInsCount+fOutsCount+fCtrlCount; i++)	*fPortZone[i] = *fPortData[i];
	}

	float** getInputs() {
		return &fPortData[0];
	}

	float** getOutputs() {
		return &fPortData[fInsCount];
	}	
};




//--------------------------------Faust-LADSPA plugin-----------------------------------
//
// Plugin structure, callbacks and LADSPA_descriptor(i) entry point
//
//--------------------------------------------------------------------------------------

LADSPA_Descriptor* 	gDescriptor = 0;

struct PLUGIN 
{
	unsigned long	fSampleRate;
	portData*		fPortData;
	dsp*			fDsp;
	
	PLUGIN(unsigned long r, portData* d, dsp* p) : fSampleRate(r), fPortData(d), fDsp(p) {}
};
	
LADSPA_Handle instantiate_method (const struct _LADSPA_Descriptor * Descriptor, unsigned long SampleRate) 
{
	dsp*		p = new mydsp();
	portData* 	d = new portData(p->getNumInputs(), p->getNumOutputs());
	
	p->buildUserInterface(d);	
	return new PLUGIN (SampleRate, d, p);
}

void connect_method (LADSPA_Handle Instance, unsigned long Port, LADSPA_Data * DataLocation) 
{
	PLUGIN* p = (PLUGIN*) Instance;
	p->fPortData->setPortData(Port, DataLocation);
}

void activate_method (LADSPA_Handle Instance)
{
	PLUGIN* p = (PLUGIN*) Instance;
	p->fDsp->init(p->fSampleRate);
}

void run_method (LADSPA_Handle Instance, unsigned long SampleCount)
{
	PLUGIN* p = (PLUGIN*) Instance;
	p->fPortData->updateCtrlZones();
	p->fDsp->compute(SampleCount, p->fPortData->getInputs(), p->fPortData->getOutputs());
}

void deactivate_method (LADSPA_Handle Instance)
{
}

void cleanup_method (LADSPA_Handle Instance)
{
	PLUGIN* p = (PLUGIN*) Instance;
	delete p->fPortData;
	delete p->fDsp;
	delete p;
}


//--------------------------------------------------------------------------------------

void init_descriptor(LADSPA_Descriptor* descriptor) 
{
	descriptor->UniqueID = 4068;
	descriptor->Label = "Simulators";
	descriptor->Properties = LADSPA_PROPERTY_HARD_RT_CAPABLE;
	descriptor->Name = "guitarix";
	descriptor->Maker = "brummer";
	descriptor->Copyright = "GPL";
	
	descriptor->ImplementationData = 0;
	
	// description des methods
	descriptor->instantiate = instantiate_method;
	descriptor->connect_port = connect_method;
	descriptor->activate = activate_method;
	descriptor->run = run_method;
	descriptor->run_adding = 0;
	descriptor->set_run_adding_gain = 0;
	descriptor->deactivate = deactivate_method;
	descriptor->cleanup = cleanup_method;
}



//--------------------------------------------------------------------------------------

const LADSPA_Descriptor * ladspa_descriptor(unsigned long Index) 
{
    if (Index == 0) {
		if (gDescriptor == 0) 
		{
			// allocate temporaries dsp and portCollectorg to build the plugin description
			mydsp* p = new mydsp();
			if (p) {
				portCollectorg*	c=new portCollectorg(p->getNumInputs(), p->getNumOutputs());
				p->buildUserInterface(c);
				gDescriptor = new LADSPA_Descriptor;
				init_descriptor(gDescriptor);
				c->fillPortDescription(gDescriptor);
				delete p;
			} else {
				printf("Memory Error : unable to allocate the dsp object\n");
			}
		}
		return gDescriptor;
	} else {
		return NULL;
	}
}

