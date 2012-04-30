//-----------------------------------------------------
// name: "emptty"
// version: "0.01"
// author: "brummer"
// license: "BSD"
// copyright: "(c)brummer 2008"
//
// Code generated with Faust 0.9.9.4k-par (http://faust.grame.fr)
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
//inline void *aligned_calloc(size_t nmemb, size_t size) { return (void*)((size_t)(calloc((nmemb*size)+15,sizeof(char)))+15 & ~15); }







//---------------------Abstract User Interface--------------------
//
// Abstract definitdision of a User Interface to be passed to the 
// buildUserInterface methoddis of a Faust Signal Processor
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
	virtual void addVerticalSlider(const char* label, float* zone, float initdis, float min, float max, float step) = 0;
	virtual void addVerticalSlider1(const char* label, float* zone, float initdis, float min, float max, float step) = 0;
	virtual void addVerticalSlider0(const char* label, float* zone, float initdis, float min, float max, float step) = 0;
	virtual void addHorizontalSlider(const char* label, float* zone, float initdis, float min, float max, float step) = 0;
	virtual void addNumEntry(const char* label, float* zone, float initdis, float min, float max, float step) = 0;
		
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
//  Abstract definitdision of a Faust Signal Processor
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
	virtual void initdis(int samplingRate) 							= 0;
 	virtual void compute(int len, float** inputs, float** outputs) 	= 0;
};
		

//----------------------------------------------------------------------------
// 	FAUST generated code
//----------------------------------------------------------------------------
		

class distdsp : public dsp {
  private:
        float drive;
        float overdrive4;

	float 	fslider5;
	float 	fslider4;
	float 	fVec5[2];
	float 	fRec0[2];
	float 	fslider6;
	float 	fentry0;
	float 	fConst0;
	float 	fVec1[2];
	float 	fRec3[2];
	float 	fentry1;
	float 	fcheckbox0;
	float 	fslider0;
	int 	IOTA;
	float 	fVec0[4096];
	float 	fslider1;
	float 	fRec1[2];

	float 	fConst1;
	float 	fConst2;
	float 	fVec2[2];
	float 	fRec2[2];
	float 	fslider2;
	float 	fslider3;
	float 	fVec3[2];
	float 	fRec7[2];
	float 	fVec4[2];
	float 	fRec6[2];
	float 	fRec5[3];
	float 	fRec4[3];
	float 	fcheckbox1;
	float 	fRec8[2];
	float 	fVec6[2];
	float 	fRec12[2];
	float 	fVec7[2];
	float 	fRec11[2];
	float 	fRec10[3];
	float 	fRec9[3];
	float 	fRecover0[2];

  public:
	static void metadata(Meta* m) 	{ 
		m->declare("name", "distortion");
		m->declare("version", "0.1");
		m->declare("author", "brummer");
		m->declare("license", "GPL");
	}

	virtual int getNumInputs() 	{ return 1; }
	virtual int getNumOutputs() 	{ return 1; }
	static void classinitdis(int samplingFreq) {
	}
	virtual void instanceinitdis(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fslider0 = 0.12f;
		IOTA = 0;
		for (int i=0; i<4096; i++) fVec0[i] = 0;
		fslider1 = 0.5f;
		for (int i=0; i<2; i++) fRec1[i] = 0;
		fentry0 = 5000.0f;
		fConst0 = (3.141593f / fSamplingFreq);
		for (int i=0; i<2; i++) fVec1[i] = 0;
		for (int i=0; i<2; i++) fRec3[i] = 0;
		fentry1 = 130.0f;
		fConst1 = (3.141593f * fSamplingFreq);
		fConst2 = (0.5f / fSamplingFreq);
		for (int i=0; i<2; i++) fVec2[i] = 0;
		for (int i=0; i<2; i++) fRec2[i] = 0;
		fcheckbox0 = 1.0;
		fslider2 = 5000.0f;
		fslider3 = 130.0f;
		for (int i=0; i<2; i++) fVec3[i] = 0;
		for (int i=0; i<2; i++) fRec7[i] = 0;
		for (int i=0; i<2; i++) fVec4[i] = 0;
		for (int i=0; i<2; i++) fRec6[i] = 0;
		for (int i=0; i<3; i++) fRec5[i] = 0;
		for (int i=0; i<3; i++) fRec4[i] = 0;
		fcheckbox1 = 1.0;
		fslider4 = 0.0f;
		fslider5 = 0.64f;
		for (int i=0; i<2; i++) fVec5[i] = 0;
		for (int i=0; i<2; i++) fRec0[i] = 0;
		fslider6 = 0.0f;
		for (int i=0; i<2; i++) fRec8[i] = 0;
		for (int i=0; i<2; i++) fVec6[i] = 0;
		for (int i=0; i<2; i++) fRec12[i] = 0;
		for (int i=0; i<2; i++) fVec7[i] = 0;
		for (int i=0; i<2; i++) fRec11[i] = 0;
		for (int i=0; i<3; i++) fRec10[i] = 0;
		for (int i=0; i<3; i++) fRec9[i] = 0;
		drive = 0.0f;
		overdrive4 = 0.0;
		for (int i=0; i<2; i++) fRecover0[i] = 0;
	}
	virtual void initdis(int samplingFreq) {
		classinitdis(samplingFreq);
		instanceinitdis(samplingFreq);
	}
	virtual void buildUserInterface(UI* interface) {
		interface->openHorizontalBox("distortion");
               // interface->openVerticalBox("overdrive");
                interface->addVerticalSlider("overdrive ", &drive, 0.0f, 1.0f, 20.0f, 0.1f);
                interface->addToggleButton("driveover", &overdrive4);
               // interface->closeBox();
		interface->addVerticalSlider("drive", &fslider5, 0.64f, 0.0f, 1.0f, 0.01f);
		interface->addVerticalSlider0("drivelevel", &fslider4, 0.0f, 0.0f, 1.0f, 0.01f);
		interface->addVerticalSlider("drivegain", &fslider6, 0.0f, -20.0f, 20.0f, 0.1f);
		//interface->openHorizontalBox("low/highpass");
		//interface->openVerticalBox("");
		interface->addHorizontalSlider("highpass", &fentry1, 130.0f, 8.0f, 1000.0f, 1.0f);
		interface->addVerticalSlider("lowpass", &fentry0, 5000.0f, 1000.0f, 10000.0f, 1.0f);
		//interface->closeBox();
		interface->addCheckButton("low_highpass", &fcheckbox0);
		//interface->closeBox();
		//interface->openHorizontalBox("low/highcut");
		interface->addVerticalSlider("highcut", &fslider2, 5000.0f, 1000.0f, 10000.0f, 1.0f);
		interface->addHorizontalSlider("lowcut", &fslider3, 130.0f, 8.0f, 1000.0f, 1.0f);
		interface->addCheckButton("low_highcut", &fcheckbox1);
		//interface->closeBox();
		//interface->openVerticalBox("resonanz");
		interface->addVerticalSlider1("trigger", &fslider0, 1.0f, 0.0f, 1.0f,0.01f);
		interface->addVerticalSlider1("vibrato", &fslider1, 0.5f, 0.01f, 1.0f, 0.01f);
		//interface->closeBox();
		interface->closeBox();
	}
		virtual void compute (int count, float** input, float** output) {
			float 	fSlow0 = (1.0f - fslider0);
			float 	fSlow1 = fslider1;
			int 	iSlow2 = int((int((fSlow1 - 1)) & 4095));
			int 	iSlow3 = int((int(fSlow1) & 4095));
			float 	fSlow4 = (1.0f / tanf((fConst0 * fentry0)));
			float 	fSlow5 = (fSlow4 - 1);
			float 	fSlow6 = (1.0f / (1 + fSlow4));
			float 	fSlow7 = (1.0f / tanf((fConst2 * (fConst1 - (6.283185f * fentry1)))));
			float 	fSlow8 = (1 + fSlow7);
			float 	fSlow9 = (1.0f / fSlow8);
			float 	fSlow10 = (0 - ((fSlow7 - 1) / fSlow8));
			int 	iSlow11 = int(fcheckbox0);
			float 	fSlow12 = tanf((fConst0 * fslider2));
			float 	fSlow13 = (2 * (1 - (1.0f / (fSlow12 * fSlow12))));
			float 	fSlow14 = (1.0f / fSlow12);
			float 	fSlow15 = (1 + ((fSlow14 - 0.765367f) / fSlow12));
			float 	fSlow16 = (1.0f / (1 + ((0.765367f + fSlow14) / fSlow12)));
			float 	fSlow17 = (1 + ((fSlow14 - 1.847759f) / fSlow12));
			float 	fSlow18 = (1.0f / (1 + ((1.847759f + fSlow14) / fSlow12)));
			float 	fSlow19 = (fConst0 * fslider3);
			float 	fSlow20 = (1.0f / (1 + fSlow19));
			float 	fSlow21 = (1 - fSlow19);
			int 	iSlow22 = int(fcheckbox1);
			float 	fSlow23 = fslider4;
	                float drivem1 = drive - 1.0f;
			float 	fSlow24 = powf(10.0f, (2 * fslider5));
			float 	fSlow25 = (9.999871e-04f * powf(10, (5.000000e-02f * (fslider6 - 10))));
	   		float fSlowover0 = (9.999871e-04f * powf(10, (5.000000e-02f * (drive*-0.5))));
			float* input0 = input[0];
			float* output0 = output[0];
			for (int i=0; i<count; i++) {
				float 	S0[2];
				float 	S1[2];
				float 	S2[2];
				float fTempi0 = input0[i];
				if (overdrive4 == 1.0)     // overdrive
                		{
		    			float fTempdr0 = fTempi0 ; 
		    			float fTempdr1 = fabs(fTempdr0);
		    			fRecover0[0] = (fSlowover0 + (0.999000f * fRecover0[1]));
		    			fTempi0 = (fTempdr0*(fTempdr1 + drive)/(fTempdr0*fTempdr0 + drivem1*fTempdr1 + 1.0f))*fRecover0[0];
				} 
				float fTemp0 = (fTempi0 + (fSlow0 * fRec1[1]));
				fVec0[IOTA&4095] = fTemp0;
				fRec1[0] = (0.5f * (fVec0[(IOTA-iSlow3)&4095] + fVec0[(IOTA-iSlow2)&4095]));
				S2[0] = fRec1[0];
				fVec1[0] = (fSlow6 * fRec1[0]);
				fRec3[0] = (fVec1[1] + (fSlow6 * (fRec1[0] + (fSlow5 * fRec3[1]))));
				float fTemp1 = (fSlow9 * fRec3[0]);
				fVec2[0] = fTemp1;
				fRec2[0] = ((fVec2[0] + (fSlow10 * fRec2[1])) - fVec2[1]);
				S2[1] = fRec2[0];
				float fTemp2 = S2[iSlow11];
				S1[0] = fTemp2;
				fVec3[0] = (fSlow20 * fTemp2);
				fRec7[0] = ((fSlow20 * (fTemp2 + (fSlow21 * fRec7[1]))) - fVec3[1]);
				fVec4[0] = (fSlow20 * fRec7[0]);
				fRec6[0] = ((fSlow20 * (fRec7[0] + (fSlow21 * fRec6[1]))) - fVec4[1]);
				fRec5[0] = (fRec6[0] - (fSlow18 * ((fSlow17 * fRec5[2]) + (fSlow13 * fRec5[1]))));
				fRec4[0] = ((fSlow18 * (fRec5[2] + (fRec5[0] + (2 * fRec5[1])))) - (fSlow16 * ((fSlow15 * fRec4[2]) + (fSlow13 * fRec4[1]))));
				S1[1] = (fSlow16 * (fRec4[2] + (fRec4[0] + (2 * fRec4[1]))));
				float fTemp3 = max(-1, min(1, (fSlow24 * (fSlow23 + S1[iSlow22]))));
				float fTemp4 = (fTemp3 * (1 - (0.333333f * (fTemp3 * fTemp3))));
				fVec5[0] = fTemp4;
				fRec0[0] = ((fVec5[0] + (0.995f * fRec0[1])) - fVec5[1]);
				fRec8[0] = (fSlow25 + (0.999f * fRec8[1]));
				float fTemp5 = (fRec8[0] * fRec0[0]);
				S0[0] = fTemp5;
				fVec6[0] = (fSlow20 * fTemp5);
				fRec12[0] = ((fSlow20 * (fTemp5 + (fSlow21 * fRec12[1]))) - fVec6[1]);
				fVec7[0] = (fSlow20 * fRec12[0]);
				fRec11[0] = ((fSlow20 * (fRec12[0] + (fSlow21 * fRec11[1]))) - fVec7[1]);
				fRec10[0] = (fRec11[0] - (fSlow18 * ((fSlow17 * fRec10[2]) + (fSlow13 * fRec10[1]))));
				fRec9[0] = ((fSlow18 * (fRec10[2] + (fRec10[0] + (2 * fRec10[1])))) - (fSlow16 * ((fSlow15 * fRec9[2]) + (fSlow13 * fRec9[1]))));
				S0[1] = (fSlow16 * (fRec9[2] + (fRec9[0] + (2 * fRec9[1]))));
				output0[i] = S0[iSlow22];
				// post processing
				fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
				fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
				fRec11[1] = fRec11[0];
				fVec7[1] = fVec7[0];
				fRec12[1] = fRec12[0];
				fVec6[1] = fVec6[0];
				fRec8[1] = fRec8[0];
				fRec0[1] = fRec0[0];
				fVec5[1] = fVec5[0];
				fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
				fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
				fRec6[1] = fRec6[0];
				fVec4[1] = fVec4[0];
				fRec7[1] = fRec7[0];
				fVec3[1] = fVec3[0];
				fRec2[1] = fRec2[0];
				fVec2[1] = fVec2[0];
				fRec3[1] = fRec3[0];
				fVec1[1] = fVec1[0];
				fRec1[1] = fRec1[0];
				fRecover0[1] = fRecover0[0];
				IOTA = IOTA+1;
			}
		}
};




		
	

//-----------------------------------portCollectord--------------------------------------
//
// portCollectord is passed to the buildUserInterface methoddis of a dsp object
// in order to build a description of its inputs, outputs and control ports.
// This description is used to fill a LADSPA_Descriptor
//
//--------------------------------------------------------------------------------------



//--------------------------------useful constants--------------------------------------

#define MAXPORT 1024
static const int ICONTROL 	= LADSPA_PORT_INPUT|LADSPA_PORT_CONTROL;
static const int OCONTROL 	= LADSPA_PORT_OUTPUT|LADSPA_PORT_CONTROL;
static const int RANGE 		= LADSPA_PORT_INPUT|LADSPA_PORT_CONTROL;

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



class portCollectord : public UI
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

	void addPortDescrdis(int type, const char* label, int hint, float min=0.0, float max=0.0) 
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

	portCollectord(int ins, int outs) : UI(), fInsCount(ins), fOutsCount(outs), fCtrlCount(0) 
	{
		for (int i = 0; i < ins; i++) { 
			fPortDescs[i] = LADSPA_PORT_INPUT | LADSPA_PORT_AUDIO | LADSPA_HINT_DEFAULT_NONE; 
			fPortNames[i] = inames[i]; 
			fPortHints[i].HintDescriptor = 0;
		}
		for (int j = 0; j < outs; j++) {
			fPortDescs[ins + j] = LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO | LADSPA_HINT_DEFAULT_NONE; 
			fPortNames[ins + j] = onames[j]; 
			fPortHints[ins + j].HintDescriptor = 0;
		}
	};

	virtual ~portCollectord() {}
	
	
	
	//------------------------------Collect the control ports-------------------------------

	virtual void addButton(const char* label, float* zone) { 
		addPortDescrdis(ICONTROL, label, LADSPA_HINT_TOGGLED); 
	}
	
	virtual void addToggleButton(const char* label, float* zone) { 
		addPortDescrdis(ICONTROL, label, LADSPA_HINT_TOGGLED|  LADSPA_HINT_DEFAULT_0 ); 
	}
	
	virtual void addCheckButton(const char* label, float* zone) { 
		addPortDescrdis(ICONTROL, label, LADSPA_HINT_TOGGLED| LADSPA_HINT_DEFAULT_1 ); 
	}
		
	virtual void addVerticalSlider(const char* label, float* zone, float initdis, float min, float max, float step) { 
		addPortDescrdis(ICONTROL, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_MIDDLE , min, max); 
	}
 
	virtual void addVerticalSlider0(const char* label, float* zone, float initdis, float min, float max, float step) { 
		addPortDescrdis(ICONTROL, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_MINIMUM , min, max); 
	}
 
	virtual void addVerticalSlider1(const char* label, float* zone, float initdis, float min, float max, float step) { 
		addPortDescrdis(ICONTROL, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_MAXIMUM, min, max); 
	}		
		
	virtual void addHorizontalSlider(const char* label, float* zone, float initdis, float min, float max, float step) { 
		addPortDescrdis(ICONTROL, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE  | LADSPA_HINT_DEFAULT_LOW, min, max); 
	}

	virtual void addNumEntry(const char* label, float* zone, float initdis, float min, float max, float step) { 
		addPortDescrdis(ICONTROL, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE, min, max); 
	}
		
	// -- passive widgets
	
	virtual void addNumDisplay(const char* label, float* zone, int precision) {
		addPortDescrdis(OCONTROL, label, 0, -10000, +10000); 
	}
	virtual void addTextDisplay(const char* label, float* zone, char* names[], float min, float max) {
		addPortDescrdis(OCONTROL, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE, min, max); 
	}
	virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max) {
		addPortDescrdis(OCONTROL, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE, min, max); 
	}
	virtual void addVerticalBargraph(const char* label, float* zone, float min, float max){
		addPortDescrdis(OCONTROL, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE, min, max); 
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
		const char* name = sym(distdsp);
		descriptor->PortCount 			= fCtrlCount+fInsCount+fOutsCount;
		descriptor->PortDescriptors 	= fPortDescs;
		descriptor->PortNames 			= fPortNames;
		descriptor->PortRangeHints 		= fPortHints;
		
		descriptor->Label = "guitarix-distortion";
		descriptor->UniqueID = 4061;
//		descriptor->Label = strdup(fPluginName.c_str());
//		descriptor->UniqueID = makeID(fPluginName.c_str());
		descriptor->Properties = LADSPA_PROPERTY_HARD_RT_CAPABLE;
		descriptor->Name = name;
//		descriptor->Name = strdup(fPluginName.c_str());
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

		
	virtual void addVerticalSlider(const char* label, float* zone, float initdis, float min, float max, float step) 		{ addZone(zone); }
	virtual void addVerticalSlider1(const char* label, float* zone, float initdis, float min, float max, float step) 		{ addZone(zone); }
	virtual void addVerticalSlider0(const char* label, float* zone, float initdis, float min, float max, float step) 		{ addZone(zone); }
	virtual void addHorizontalSlider(const char* label, float* zone, float initdis, float min, float max, float step) 	{ addZone(zone); }
	virtual void addNumEntry(const char* label, float* zone, float initdis, float min, float max, float step)  			{ addZone(zone); }
		
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

LADSPA_Descriptor* 	gDescriptord = 0;

struct PLUGIN 
{
	unsigned long	fSampleRate;
	portData*		fPortData;
	dsp*			fDsp;
	
	PLUGIN(unsigned long r, portData* d, dsp* p) : fSampleRate(r), fPortData(d), fDsp(p) {}
};
	
LADSPA_Handle instantiate_methoddis (const struct _LADSPA_Descriptor * Descriptor, unsigned long SampleRate) 
{
	dsp*		p = new distdsp();
	portData* 	d = new portData(p->getNumInputs(), p->getNumOutputs());
	
	p->buildUserInterface(d);	
	return new PLUGIN (SampleRate, d, p);
}

void connect_methoddis (LADSPA_Handle Instance, unsigned long Port, LADSPA_Data * DataLocation) 
{
	PLUGIN* p = (PLUGIN*) Instance;
	p->fPortData->setPortData(Port, DataLocation);
}

void activate_methoddis (LADSPA_Handle Instance)
{
	PLUGIN* p = (PLUGIN*) Instance;
	p->fDsp->initdis(p->fSampleRate);
}

void run_methoddis (LADSPA_Handle Instance, unsigned long SampleCount)
{
	PLUGIN* p = (PLUGIN*) Instance;
	p->fPortData->updateCtrlZones();
	p->fDsp->compute(SampleCount, p->fPortData->getInputs(), p->fPortData->getOutputs());
}

void deactivate_methoddis (LADSPA_Handle Instance)
{
}

void cleanup_methoddis (LADSPA_Handle Instance)
{
	PLUGIN* p = (PLUGIN*) Instance;
	delete p->fPortData;
	delete p->fDsp;
	delete p;
}


//--------------------------------------------------------------------------------------

void initdis_descriptor(LADSPA_Descriptor* descriptor) 
{
	descriptor->UniqueID = 4061;
	descriptor->Label = "distortion";
	descriptor->Properties = LADSPA_PROPERTY_HARD_RT_CAPABLE;
	descriptor->Name = "distortion";
	descriptor->Maker = "brummer";
	descriptor->Copyright = "GPL";
	
	descriptor->ImplementationData = 0;
	
	// description des methoddiss
	descriptor->instantiate = instantiate_methoddis;
	descriptor->connect_port = connect_methoddis;
	descriptor->activate = activate_methoddis;
	descriptor->run = run_methoddis;
	descriptor->run_adding = 0;
	descriptor->set_run_adding_gain = 0;
	descriptor->deactivate = deactivate_methoddis;
	descriptor->cleanup = cleanup_methoddis;
}



//--------------------------------------------------------------------------------------

const LADSPA_Descriptor * ladspa_descriptor(unsigned long Index) 
{
    if (Index == 0) {
		if (gDescriptord == 0) 
		{
			// allocate temporaries dsp and portCollectord to build the plugin description
			distdsp* p = new distdsp();
			if (p) {
				portCollectord*	c=new portCollectord(p->getNumInputs(), p->getNumOutputs());
				p->buildUserInterface(c);
				gDescriptord = new LADSPA_Descriptor;
				initdis_descriptor(gDescriptord);
				c->fillPortDescription(gDescriptord);
				delete p;
			} else {
				printf("Memory Error : unable to allocate the dsp object\n");
			}
		}
		return gDescriptord;
	} else {
		return NULL;
	}
}

