//-----------------------------------------------------
// name: "freeverb"
// version: "0.1"
// author: "brummer"
// license: "GPL"
//
// Code generated with Faust 0.9.9.4k-par (http://faust.grame.fr)
//-----------------------------------------------------
/* link with  */
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
// Abstract definitfreeion of a User Interface to be passed to the 
// buildUserInterface methodfr of a Faust Signal Processor
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
	virtual void addVerticalSlider(const char* label, float* zone, float initfree, float min, float max, float step) = 0;
	virtual void addVerticalSlider1(const char* label, float* zone, float initdis, float min, float max, float step) = 0;
	virtual void addVerticalSlider0(const char* label, float* zone, float initdis, float min, float max, float step) = 0;
	virtual void addHorizontalSlider(const char* label, float* zone, float initfree, float min, float max, float step) = 0;
	virtual void addNumEntry(const char* label, float* zone, float initfree, float min, float max, float step) = 0;
		
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
//  Abstract definitfreeion of a Faust Signal Processor
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
	virtual void initfree(int samplingRate) 							= 0;
 	virtual void computfr(int len, float** inputs, float** outputs) 	= 0;
};
		

//----------------------------------------------------------------------------
// 	FAUST generated code
//----------------------------------------------------------------------------
		

class frdsp : public dsp {
  private:
	float 	fslider0;
	float 	fslider1;
	float 	fRec9[2];
	float 	fslider2;
	int 	IOTA;
	float 	fVec0[2048];
	float 	fRec8[2];
	float 	fRec11[2];
	float 	fVec1[2048];
	float 	fRec10[2];
	float 	fRec13[2];
	float 	fVec2[2048];
	float 	fRec12[2];
	float 	fRec15[2];
	float 	fVec3[2048];
	float 	fRec14[2];
	float 	fRec17[2];
	float 	fVec4[2048];
	float 	fRec16[2];
	float 	fRec19[2];
	float 	fVec5[2048];
	float 	fRec18[2];
	float 	fRec21[2];
	float 	fVec6[2048];
	float 	fRec20[2];
	float 	fRec23[2];
	float 	fVec7[2048];
	float 	fRec22[2];
	float 	fVec8[1024];
	float 	fRec6[2];
	float 	fVec9[512];
	float 	fRec4[2];
	float 	fVec10[512];
	float 	fRec2[2];
	float 	fVec11[256];
	float 	fRec0[2];
	float 	fcheckbox0;
  public:
	static void metadata(Meta* m) 	{ 
		m->declare("name", "freeverb");
		m->declare("version", "0.1");
		m->declare("author", "brummer");
		m->declare("license", "GPL");
	}

	virtual int getNumInputs() 	{ return 1; }
	virtual int getNumOutputs() 	{ return 1; }
	static void classinitfree(int samplingFreq) {
	}
	virtual void instanceinitfree(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fslider0 = 0.3333f;
		fslider1 = 0.5f;
		for (int i=0; i<2; i++) fRec9[i] = 0;
		fslider2 = 0.5f;
		IOTA = 0;
		for (int i=0; i<2048; i++) fVec0[i] = 0;
		for (int i=0; i<2; i++) fRec8[i] = 0;
		for (int i=0; i<2; i++) fRec11[i] = 0;
		for (int i=0; i<2048; i++) fVec1[i] = 0;
		for (int i=0; i<2; i++) fRec10[i] = 0;
		for (int i=0; i<2; i++) fRec13[i] = 0;
		for (int i=0; i<2048; i++) fVec2[i] = 0;
		for (int i=0; i<2; i++) fRec12[i] = 0;
		for (int i=0; i<2; i++) fRec15[i] = 0;
		for (int i=0; i<2048; i++) fVec3[i] = 0;
		for (int i=0; i<2; i++) fRec14[i] = 0;
		for (int i=0; i<2; i++) fRec17[i] = 0;
		for (int i=0; i<2048; i++) fVec4[i] = 0;
		for (int i=0; i<2; i++) fRec16[i] = 0;
		for (int i=0; i<2; i++) fRec19[i] = 0;
		for (int i=0; i<2048; i++) fVec5[i] = 0;
		for (int i=0; i<2; i++) fRec18[i] = 0;
		for (int i=0; i<2; i++) fRec21[i] = 0;
		for (int i=0; i<2048; i++) fVec6[i] = 0;
		for (int i=0; i<2; i++) fRec20[i] = 0;
		for (int i=0; i<2; i++) fRec23[i] = 0;
		for (int i=0; i<2048; i++) fVec7[i] = 0;
		for (int i=0; i<2; i++) fRec22[i] = 0;
		for (int i=0; i<1024; i++) fVec8[i] = 0;
		for (int i=0; i<2; i++) fRec6[i] = 0;
		for (int i=0; i<512; i++) fVec9[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		for (int i=0; i<512; i++) fVec10[i] = 0;
		for (int i=0; i<2; i++) fRec2[i] = 0;
		for (int i=0; i<256; i++) fVec11[i] = 0;
		for (int i=0; i<2; i++) fRec0[i] = 0;
		fcheckbox0 = 1.0;
	}
	virtual void initfree(int samplingFreq) {
		classinitfree(samplingFreq);
		instanceinitfree(samplingFreq);
	}
	virtual void buildUserInterface(UI* interface) {
		interface->openVerticalBox("freeverb");
		interface->addVerticalSlider("RoomSize", &fslider2, 0.5f, 0.0f, 1.0f, 2.500000e-02f);
		interface->addVerticalSlider("damp", &fslider1, 0.5f, 0.0f, 1.0f, 2.500000e-02f);
		interface->addHorizontalSlider("dry/wet/", &fslider0, 0.3333f, 0.0f, 1.0f, 2.500000e-02f);
		interface->closeBox();
	}
		virtual void computfr (int count, float** input, float** output) {
			float 	fSlow0 = fslider0;
			float 	fSlow1 = (2 * (1 - fSlow0));
			float 	fSlow2 = (0.4f * fslider1);
			float 	fSlow3 = (1 - fSlow2);
			float 	fSlow4 = (0.7f + (0.28f * fslider2));
			int 	iSlow5 = int(fcheckbox0);
			float* input0 = input[0];
			float* output0 = output[0];
			for (int i=0; i<count; i++) {
				float 	S0[2];
				float fTemp0 = input0[i];
				S0[0] = fTemp0;
				float fTemp1 = (1.500000e-02f * fTemp0);
				fRec9[0] = ((fSlow3 * fRec8[1]) + (fSlow2 * fRec9[1]));
				fVec0[IOTA&2047] = (fTemp1 + (fSlow4 * fRec9[0]));
				fRec8[0] = fVec0[(IOTA-1640)&2047];
				fRec11[0] = ((fSlow3 * fRec10[1]) + (fSlow2 * fRec11[1]));
				fVec1[IOTA&2047] = (fTemp1 + (fSlow4 * fRec11[0]));
				fRec10[0] = fVec1[(IOTA-1580)&2047];
				fRec13[0] = ((fSlow3 * fRec12[1]) + (fSlow2 * fRec13[1]));
				fVec2[IOTA&2047] = (fTemp1 + (fSlow4 * fRec13[0]));
				fRec12[0] = fVec2[(IOTA-1514)&2047];
				fRec15[0] = ((fSlow3 * fRec14[1]) + (fSlow2 * fRec15[1]));
				fVec3[IOTA&2047] = (fTemp1 + (fSlow4 * fRec15[0]));
				fRec14[0] = fVec3[(IOTA-1445)&2047];
				fRec17[0] = ((fSlow3 * fRec16[1]) + (fSlow2 * fRec17[1]));
				fVec4[IOTA&2047] = (fTemp1 + (fSlow4 * fRec17[0]));
				fRec16[0] = fVec4[(IOTA-1379)&2047];
				fRec19[0] = ((fSlow3 * fRec18[1]) + (fSlow2 * fRec19[1]));
				fVec5[IOTA&2047] = (fTemp1 + (fSlow4 * fRec19[0]));
				fRec18[0] = fVec5[(IOTA-1300)&2047];
				fRec21[0] = ((fSlow3 * fRec20[1]) + (fSlow2 * fRec21[1]));
				fVec6[IOTA&2047] = (fTemp1 + (fSlow4 * fRec21[0]));
				fRec20[0] = fVec6[(IOTA-1211)&2047];
				fRec23[0] = ((fSlow3 * fRec22[1]) + (fSlow2 * fRec23[1]));
				fVec7[IOTA&2047] = (fTemp1 + (fSlow4 * fRec23[0]));
				fRec22[0] = fVec7[(IOTA-1139)&2047];
				float fTemp2 = (((((((fRec22[0] + fRec20[0]) + fRec18[0]) + fRec16[0]) + fRec14[0]) + fRec12[0]) + fRec10[0]) + fRec8[0]);
				fVec8[IOTA&1023] = (fTemp2 + (0.5f * fRec6[1]));
				fRec6[0] = fVec8[(IOTA-579)&1023];
				float 	fRec7 = (0 - (fTemp2 - fRec6[1]));
				fVec9[IOTA&511] = (fRec7 + (0.5f * fRec4[1]));
				fRec4[0] = fVec9[(IOTA-464)&511];
				float 	fRec5 = (fRec4[1] - fRec7);
				fVec10[IOTA&511] = (fRec5 + (0.5f * fRec2[1]));
				fRec2[0] = fVec10[(IOTA-364)&511];
				float 	fRec3 = (fRec2[1] - fRec5);
				fVec11[IOTA&255] = (fRec3 + (0.5f * fRec0[1]));
				fRec0[0] = fVec11[(IOTA-248)&255];
				float 	fRec1 = (fRec0[1] - fRec3);
				S0[1] = ((fSlow0 * (fRec1 + fTemp1)) + (fSlow1 * fTemp0));
				output0[i] = S0[iSlow5];
				// post processing
				fRec0[1] = fRec0[0];
				fRec2[1] = fRec2[0];
				fRec4[1] = fRec4[0];
				fRec6[1] = fRec6[0];
				fRec22[1] = fRec22[0];
				fRec23[1] = fRec23[0];
				fRec20[1] = fRec20[0];
				fRec21[1] = fRec21[0];
				fRec18[1] = fRec18[0];
				fRec19[1] = fRec19[0];
				fRec16[1] = fRec16[0];
				fRec17[1] = fRec17[0];
				fRec14[1] = fRec14[0];
				fRec15[1] = fRec15[0];
				fRec12[1] = fRec12[0];
				fRec13[1] = fRec13[0];
				fRec10[1] = fRec10[0];
				fRec11[1] = fRec11[0];
				fRec8[1] = fRec8[0];
				IOTA = IOTA+1;
				fRec9[1] = fRec9[0];
			}
		}
};




		
	

//-----------------------------------portCollectorf--------------------------------------
//
// portCollectorf is passed to the buildUserInterface methodfr of a dsp object
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



class portCollectorf : public UI
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

	void addPortDescrfr(int type, const char* label, int hint, float min=0.0, float max=0.0) 
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

	portCollectorf(int ins, int outs) : UI(), fInsCount(ins), fOutsCount(outs), fCtrlCount(0) 
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

	virtual ~portCollectorf() {}
	
	
	
	//------------------------------Collect the control ports-------------------------------

	virtual void addButton(const char* label, float* zone) { 
		addPortDescrfr(ICONTROL, label, LADSPA_HINT_TOGGLED); 
	}
	
	virtual void addToggleButton(const char* label, float* zone) { 
		addPortDescrfr(ICONTROL, label, LADSPA_HINT_TOGGLED|  LADSPA_HINT_DEFAULT_0 ); 
	}
	
	virtual void addCheckButton(const char* label, float* zone) { 
		addPortDescrfr(ICONTROL, label, LADSPA_HINT_TOGGLED| LADSPA_HINT_DEFAULT_1 ); 
	}
		
	virtual void addVerticalSlider(const char* label, float* zone, float initdis, float min, float max, float step) { 
		addPortDescrfr(ICONTROL, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_MIDDLE , min, max); 
	}
 
	virtual void addVerticalSlider0(const char* label, float* zone, float initdis, float min, float max, float step) { 
		addPortDescrfr(ICONTROL, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_MINIMUM , min, max); 
	}
 
	virtual void addVerticalSlider1(const char* label, float* zone, float initdis, float min, float max, float step) { 
		addPortDescrfr(ICONTROL, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_MAXIMUM, min, max); 
	}		
		
	virtual void addHorizontalSlider(const char* label, float* zone, float initdis, float min, float max, float step) { 
		addPortDescrfr(ICONTROL, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE  | LADSPA_HINT_DEFAULT_LOW, min, max); 
	}

	virtual void addNumEntry(const char* label, float* zone, float initfree, float min, float max, float step) { 
		addPortDescrfr(ICONTROL, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE, min, max); 
	}
		
	// -- passive widgets
	
	virtual void addNumDisplay(const char* label, float* zone, int precision) {
		addPortDescrfr(OCONTROL, label, 0, -10000, +10000); 
	}
	virtual void addTextDisplay(const char* label, float* zone, char* names[], float min, float max) {
		addPortDescrfr(OCONTROL, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE, min, max); 
	}
	virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max) {
		addPortDescrfr(OCONTROL, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE, min, max); 
	}
	virtual void addVerticalBargraph(const char* label, float* zone, float min, float max){
		addPortDescrfr(OCONTROL, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE, min, max); 
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
		const char* name = sym(frdsp);
		descriptor->PortCount 			= fCtrlCount+fInsCount+fOutsCount;
		descriptor->PortDescriptors 	= fPortDescs;
		descriptor->PortNames 			= fPortNames;
		descriptor->PortRangeHints 		= fPortHints;
		
		descriptor->Label = strdup(name);
		descriptor->UniqueID = 4064;
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
		
	virtual void addVerticalSlider(const char* label, float* zone, float initfree, float min, float max, float step) 		{ addZone(zone); }
	virtual void addVerticalSlider1(const char* label, float* zone, float initdis, float min, float max, float step) 		{ addZone(zone); }
	virtual void addVerticalSlider0(const char* label, float* zone, float initdis, float min, float max, float step) 		{ addZone(zone); }
	virtual void addHorizontalSlider(const char* label, float* zone, float initfree, float min, float max, float step) 	{ addZone(zone); }
	virtual void addNumEntry(const char* label, float* zone, float initfree, float min, float max, float step)  			{ addZone(zone); }
		
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
	
	void setPortDatafr (unsigned long port, LADSPA_Data* data) {
		fPortData[port] = data;
	}
	
	void updateCtrlZonesfr() {
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

LADSPA_Descriptor* 	gDescriptorfe = 0;

struct PLUGIN 
{
	unsigned long	fSampleRate;
	portData*		fPortData;
	dsp*			fDsp;
	
	PLUGIN(unsigned long r, portData* d, dsp* p) : fSampleRate(r), fPortData(d), fDsp(p) {}
};
	
LADSPA_Handle instantiate_methodfr (const struct _LADSPA_Descriptor * Descriptor, unsigned long SampleRate) 
{
	dsp*		p = new frdsp();
	portData* 	d = new portData(p->getNumInputs(), p->getNumOutputs());
	
	p->buildUserInterface(d);	
	return new PLUGIN (SampleRate, d, p);
}

void connect_methodfr (LADSPA_Handle Instance, unsigned long Port, LADSPA_Data * DataLocation) 
{
	PLUGIN* p = (PLUGIN*) Instance;
	p->fPortData->setPortDatafr(Port, DataLocation);
}

void activate_methodfr (LADSPA_Handle Instance)
{
	PLUGIN* p = (PLUGIN*) Instance;
	p->fDsp->initfree(p->fSampleRate);
}

void run_methodfr (LADSPA_Handle Instance, unsigned long SampleCount)
{
	PLUGIN* p = (PLUGIN*) Instance;
	p->fPortData->updateCtrlZonesfr();
	p->fDsp->computfr(SampleCount, p->fPortData->getInputs(), p->fPortData->getOutputs());
}

void deactivate_methodfr (LADSPA_Handle Instance)
{
}

void cleanup_methodfr (LADSPA_Handle Instance)
{
	PLUGIN* p = (PLUGIN*) Instance;
	delete p->fPortData;
	delete p->fDsp;
	delete p;
}


//--------------------------------------------------------------------------------------

void initfree_descriptor(LADSPA_Descriptor* descriptor) 
{
	descriptor->UniqueID = 4064;
	descriptor->Label = "freeverb";
	descriptor->Properties = LADSPA_PROPERTY_HARD_RT_CAPABLE;
	descriptor->Name = "freeverb";
	descriptor->Maker = "brummer";
	descriptor->Copyright = "GPL";
	
	descriptor->ImplementationData = 0;
	
	// description des methodfrs
	descriptor->instantiate = instantiate_methodfr;
	descriptor->connect_port = connect_methodfr;
	descriptor->activate = activate_methodfr;
	descriptor->run = run_methodfr;
	descriptor->run_adding = 0;
	descriptor->set_run_adding_gain = 0;
	descriptor->deactivate = deactivate_methodfr;
	descriptor->cleanup = cleanup_methodfr;
}



//--------------------------------------------------------------------------------------

const LADSPA_Descriptor * ladspa_descriptor(unsigned long Index) 
{
    if (Index == 0) {
		if (gDescriptorfe == 0) 
		{
			// allocate temporaries dsp and portCollectorf to build the plugin description
			frdsp* p = new frdsp();
			if (p) {
				portCollectorf*	c=new portCollectorf(p->getNumInputs(), p->getNumOutputs());
				p->buildUserInterface(c);
				gDescriptorfe = new LADSPA_Descriptor;
				initfree_descriptor(gDescriptorfe);
				c->fillPortDescription(gDescriptorfe);
				delete p;
			} else {
				printf("Memory Error : unable to allocate the dsp object\n");
			}
		}
		return gDescriptorfe;
	} else {
		return NULL;
	}
}

