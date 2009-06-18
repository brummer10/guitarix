//-----------------------------------------------------
// name: "monoamp"
// version: "0.1"
// author: "brummer"
// license: "GPL"
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
// Abstract definitampion of a User Interface to be passed to the 
// buildUserInterface1 method of a Faust Signal Processor
// 
//----------------------------------------------------------------

class UI
{
	bool	fStopped;
public:
		
	UI() : fStopped(false) {}
	virtual ~UI() {}
	
	virtual void addButton(const char* label, float* zone1) = 0;
	virtual void addToggleButton(const char* label, float* zone1) = 0;
	virtual void addCheckButton(const char* label, float* zone1) = 0;
	virtual void addVerticalSlider(const char* label, float* zone1, float initamp, float min, float max, float step) = 0;
	virtual void addVerticalSlider1(const char* label, float* zone, float initdis, float min, float max, float step) = 0;
	virtual void addVerticalSlider0(const char* label, float* zone, float initdis, float min, float max, float step) = 0;
	virtual void addHorizontalSlider(const char* label, float* zone1, float initamp, float min, float max, float step) = 0;
	virtual void addNumEntry1(const char* label, float* zone1, float initamp, float min, float max, float step) = 0;
		
	// -- passive widgets
	
	virtual void addNumDisplay1(const char* label, float* zone1, int precision) = 0;
	virtual void addTextDisplay1(const char* label, float* zone1, char* names[], float min, float max) = 0;
	virtual void addHorizontalBargraph1(const char* label, float* zone1, float min, float max) = 0;
	virtual void addVerticalBargraph1(const char* label, float* zone1, float min, float max) = 0;

	// -- frames and labels
	
	virtual void openFrameBox1(const char* label) = 0;
	virtual void openTabBox1(const char* label) = 0;
	virtual void openHorizontalBox1(const char* label) = 0;
	virtual void openVerticalBox1(const char* label) = 0;
	virtual void closeBox1() = 0;
	
	virtual void show() = 0;
	virtual void run() = 0;
	
	void stop()		{ fStopped = true; }
	bool stopped() 	{ return fStopped; }

    virtual void declare(float* zone1, const char* key, const char* value) {}
};



//------------------Abstract Signal Processor---------------------
//
//  Abstract definitampion of a Faust Signal Processor
//
//----------------------------------------------------------------
			
class dspamp {
 protected:
	int fSamplingFreq;
 public:
	dspamp() {}
	virtual ~dspamp() {}
	virtual int getNumInputs() 										= 0;
	virtual int getNumOutputs() 									= 0;
	virtual void buildUserInterface1(UI* interface1) 					= 0;
	virtual void initamp(int samplingRate) 							= 0;
 	virtual void computeamp(int len, float** inputs, float** outputs) 	= 0;
};
		

//----------------------------------------------------------------------------
// 	FAUST generated code
//----------------------------------------------------------------------------
		

class ampdsp : public dspamp {
  private:
	float 	fcheckbox0;
	float 	fslideramp3;
	float 	fslideramp2;
	float 	fslideramp1;
	float 	fslideramp0;
	float 	fslideramp4;

	float 	fConstamp0;
	float 	fConstamp1;
	float 	fConstamp2;
	float 	fConstamp3;
	float 	fConstamp4;
	float 	fConstamp5;

	float 	fVecamp0[3];
	float 	fRecamp3[2];
	float 	fRecamp2[3];
	float 	fRecamp1[4];
	float 	fRecamp0[6];
  public:
	static void metadata(Meta* m) 	{ 
		m->declare("name", "monoamp");
		m->declare("version", "0.1");
		m->declare("author", "brummer");
		m->declare("license", "GPL");
	}

	virtual int getNumInputs() 	{ return 1; }
	virtual int getNumOutputs() 	{ return 1; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceInit1(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fslideramp0 = 0.0f;
		fslideramp1 = 0.0f;
		fConstamp0 = (7539.822754f / fSamplingFreq);
		fConstamp1 = cosf(fConstamp0);
		fConstamp2 = (1.414214f * sinf(fConstamp0));
		fslideramp2 = 0.0f;
		fConstamp3 = (1884.955688f / fSamplingFreq);
		fConstamp4 = cosf(fConstamp3);
		fConstamp5 = (1.414214f * sinf(fConstamp3));
		fcheckbox0 = 0.0;
		fslideramp3 = 0.0f;
		for (int i=0; i<2; i++) fRecamp3[i] = 0;
		for (int i=0; i<3; i++) fVecamp0[i] = 0;
		for (int i=0; i<3; i++) fRecamp2[i] = 0;
		for (int i=0; i<4; i++) fRecamp1[i] = 0;
		fslideramp4 = 0.0f;
		for (int i=0; i<6; i++) fRecamp0[i] = 0;
	}
	virtual void initamp(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit1(samplingFreq);
	}
	virtual void buildUserInterface1(UI* interface1) {
		interface1->openHorizontalBox1("monoamp");
		//interface1->openVerticalBox1("preamp");
		interface1->addToggleButton("preamp", &fcheckbox0);
		//interface1->closeBox1();
		interface1->addVerticalSlider("gain", &fslideramp3, 0.0f, -40.0f, 40.0f, 0.1f);
		interface1->addVerticalSlider("bass", &fslideramp2, 0.0f, -20.0f, 20.0f, 0.1f);
		interface1->addVerticalSlider("treble", &fslideramp1, 0.0f, -20.0f, 20.0f, 0.1f);
		interface1->addVerticalSlider0("feedbackgain", &fslideramp0, 0.0f, 0.0f, 1.0f, 0.01f);
		interface1->addVerticalSlider0("feedforwardgain", &fslideramp4, 0.0f, 0.0f, 1.0f, 0.01f);
		interface1->closeBox1();
	}
		virtual void computeamp (int count, float** input, float** output) {
			float 	fSlowamp0 = fslideramp0;
			float 	fSlowamp1 = powf(10, (2.500000e-02f * fslideramp1));
			float 	fSlowamp2 = (1 + fSlowamp1);
			float 	fSlowamp3 = (fConstamp1 * fSlowamp2);
			float 	fSlowamp4 = (2 * (0 - ((1 + fSlowamp3) - fSlowamp1)));
			float 	fSlowamp5 = (fConstamp1 * (fSlowamp1 - 1));
			float 	fSlowamp6 = (fConstamp2 * sqrtf(fSlowamp1));
			float 	fSlowamp7 = (fSlowamp2 - (fSlowamp6 + fSlowamp5));
			float 	fSlowamp8 = powf(10, (2.500000e-02f * fslideramp2));
			float 	fSlowamp9 = (1 + fSlowamp8);
			float 	fSlowamp10 = (fConstamp4 * fSlowamp9);
			float 	fSlowamp11 = (0 - (2 * ((fSlowamp8 + fSlowamp10) - 1)));
			float 	fSlowamp12 = (fConstamp5 * sqrtf(fSlowamp8));
			float 	fSlowamp13 = (fConstamp4 * (fSlowamp8 - 1));
			float 	fSlowamp14 = ((1 + (fSlowamp8 + fSlowamp13)) - fSlowamp12);
			int 	iSlowamp15 = int(fcheckbox0);
			float 	fSlowamp16 = (9.999871e-04f * powf(10, (5.000000e-02f * fslideramp3)));
			float 	fSlowamp17 = (fSlowamp9 - (fSlowamp12 + fSlowamp13));
			float 	fSlowamp18 = (2 * (0 - ((1 + fSlowamp10) - fSlowamp8)));
			float 	fSlowamp19 = (fSlowamp8 + fSlowamp12);
			float 	fSlowamp20 = ((1 + fSlowamp19) - fSlowamp13);
			float 	fSlowamp21 = (1.0f / (1 + (fSlowamp13 + fSlowamp19)));
			float 	fSlowamp22 = (fSlowamp1 * ((1 + (fSlowamp1 + fSlowamp5)) - fSlowamp6));
			float 	fSlowamp23 = (fSlowamp1 + fSlowamp6);
			float 	fSlowamp24 = (fSlowamp1 * (1 + (fSlowamp5 + fSlowamp23)));
			float 	fSlowamp25 = (((fSlowamp1 + fSlowamp3) - 1) * (0 - (2 * fSlowamp1)));
			float 	fSlowamp26 = (1.0f / ((1 + fSlowamp23) - fSlowamp5));
			float 	fSlowamp27 = fslideramp4;
			float* input0 = input[0];
			float* output0 = output[0];
			for (int i=0; i<count; i++) {
				float 	Samp0[2];
				float fTempamp0 = input0[i];
				Samp0[0] = fTempamp0;
				//Samp0[1] = (7.118644f * fTempamp0);
				fRecamp3[0] = (fSlowamp16 + (0.999f * fRecamp3[1]));
				//float fTempamp1 = (fRecamp3[0] * Samp0[iSlowamp15]);
                                if (iSlowamp15 == 1)     // preamp
                		{
		    			float  in = fTempamp0 * 3;
		    			if(in>=1.0)
		     			in = 2/3.0;
		    			else if (in<-1.0)
		      			in = -2/3.0;
		    			else in = (in - in*in*in/3.0);
		      			Samp0[1] = in;
					}  //preamp ende
 				float fTempamp1 = (fRecamp3[0] * Samp0[iSlowamp15]);
				fVecamp0[0] = fTempamp1;
				fRecamp2[0] = (fSlowamp21 * ((fSlowamp8 * (((fSlowamp20 * fVecamp0[0]) + (fSlowamp18 * fVecamp0[1])) + (fSlowamp17 * fVecamp0[2]))) - ((fSlowamp14 * fRecamp2[2]) + (fSlowamp11 * fRecamp2[1]))));
				fRecamp1[0] = (fSlowamp26 * ((((fSlowamp25 * fRecamp2[1]) + (fSlowamp24 * fRecamp2[0])) + (fSlowamp22 * fRecamp2[2])) + (0 - ((fSlowamp7 * fRecamp1[2]) + (fSlowamp4 * fRecamp1[1])))));
				fRecamp0[0] = ((fRecamp1[0] + (fSlowamp27 * fRecamp1[3])) - (fSlowamp0 * fRecamp0[5]));
				output0[i] = fRecamp0[0];
				// post processing
				for (int i=5; i>0; i--) fRecamp0[i] = fRecamp0[i-1];
				for (int i=3; i>0; i--) fRecamp1[i] = fRecamp1[i-1];
				fRecamp2[2] = fRecamp2[1]; fRecamp2[1] = fRecamp2[0];
				fVecamp0[2] = fVecamp0[1]; fVecamp0[1] = fVecamp0[0];
				fRecamp3[1] = fRecamp3[0];
			}
		}
};




		
	

//-----------------------------------portCollector1--------------------------------------
//
// portCollector1 is passed to the buildUserInterface1 method of a dsp object
// in order to build a description of its inputs, outputs and control ports.
// This description is used to fill a LADSPA_Descriptor
//
//--------------------------------------------------------------------------------------



//--------------------------------useful constants--------------------------------------

#define MAXPORT 1024
static const int ICONTROL1 	= LADSPA_PORT_INPUT|LADSPA_PORT_CONTROL;
static const int OCONTROL1 	= LADSPA_PORT_OUTPUT|LADSPA_PORT_CONTROL;
static const int RANGE1 		= LADSPA_PORT_INPUT|LADSPA_PORT_CONTROL;

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



class portCollector1 : public UI
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

	void addPortDescr1(int type, const char* label, int hint, float min=0.0, float max=0.0) 
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
	
	void openAnyBox1(const char* label)
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

	portCollector1(int ins, int outs) : UI(), fInsCount(ins), fOutsCount(outs), fCtrlCount(0) 
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

	virtual ~portCollector1() {}
	
	
	
	//------------------------------Collect the control ports-------------------------------

	virtual void addButton(const char* label, float* zone1) { 
		addPortDescr1(ICONTROL1, label, LADSPA_HINT_TOGGLED); 
	}
	
	virtual void addToggleButton(const char* label, float* zone) { 
		addPortDescr1(ICONTROL1, label, LADSPA_HINT_TOGGLED|  LADSPA_HINT_DEFAULT_0 ); 
	}
	
	virtual void addCheckButton(const char* label, float* zone) { 
		addPortDescr1(ICONTROL1, label, LADSPA_HINT_TOGGLED| LADSPA_HINT_DEFAULT_1 ); 
	}
		
	virtual void addVerticalSlider(const char* label, float* zone, float initdis, float min, float max, float step) { 
		addPortDescr1(ICONTROL1, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_MIDDLE , min, max); 
	}
 
	virtual void addVerticalSlider0(const char* label, float* zone, float initdis, float min, float max, float step) { 
		addPortDescr1(ICONTROL1, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_MINIMUM , min, max); 
	}
 
	virtual void addVerticalSlider1(const char* label, float* zone, float initdis, float min, float max, float step) { 
		addPortDescr1(ICONTROL1, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_MAXIMUM, min, max); 
	}		
		
	virtual void addHorizontalSlider(const char* label, float* zone, float initdis, float min, float max, float step) { 
		addPortDescr1(ICONTROL1, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE  | LADSPA_HINT_DEFAULT_LOW, min, max); 
	}

	virtual void addNumEntry1(const char* label, float* zone1, float initamp, float min, float max, float step) { 
		addPortDescr1(ICONTROL1, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE| LADSPA_HINT_DEFAULT_0, min, max); 
	}
		
	// -- passive widgets
	
	virtual void addNumDisplay1(const char* label, float* zone1, int precision) {
		addPortDescr1(OCONTROL1, label, 0, -10000, +10000); 
	}
	virtual void addTextDisplay1(const char* label, float* zone1, char* names[], float min, float max) {
		addPortDescr1(OCONTROL1, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE, min, max); 
	}
	virtual void addHorizontalBargraph1(const char* label, float* zone1, float min, float max) {
		addPortDescr1(OCONTROL1, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE, min, max); 
	}
	virtual void addVerticalBargraph1(const char* label, float* zone1, float min, float max){
		addPortDescr1(OCONTROL1, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE, min, max); 
	}

	virtual void openFrameBox1(const char* label)		{ openAnyBox1(label); }
	virtual void openTabBox1(const char* label)		{ openAnyBox1(label); }
	virtual void openHorizontalBox1(const char* label)	{ openAnyBox1(label); }
	virtual void openVerticalBox1(const char* label)	{ openAnyBox1(label); }
	
	virtual void closeBox1() 					{ fPrefix.pop(); }
	
	virtual void show() {}
	virtual void run() 	{}
	
	
	
	//---------------------------------Fill the LADSPA descriptor---------------------------
	
	// generate an ID from a plugin name
	int makeID1 (const char* s) {
		int h = 0;
		for (int i = 0; s[i]; i++) {
			h = (h << 3) + (s[i] & 7);
		}
		return 1+h%1000;
	}

	// fill a ladspa descriptor with the information collected on ports
	void fillPortDescription (LADSPA_Descriptor * descriptor1) {
		const char* name = sym(ampdsp);
		descriptor1->PortCount 			= fCtrlCount+fInsCount+fOutsCount;
		descriptor1->PortDescriptors 	= fPortDescs;
		descriptor1->PortNames 			= fPortNames;
		descriptor1->PortRangeHints 		= fPortHints;
		
		descriptor1->Label = strdup(name);
		descriptor1->UniqueID = 4066;
//		descriptor1->Label = strdup(fPluginName.c_str());
//		descriptor1->UniqueID = makeID1(fPluginName.c_str());
		descriptor1->Properties = LADSPA_PROPERTY_HARD_RT_CAPABLE;
		descriptor1->Name = name;
//		descriptor1->Name = strdup(fPluginName.c_str());
		descriptor1->Maker = "brummer";
		descriptor1->Copyright = "GPL";
	}
};




//--------------------------------------portData1----------------------------------------
//
// portData1 : a user interface used to associate the data buffers and the ports
//
//--------------------------------------------------------------------------------------


class portData1 : public UI
{	

	
 private:

	
	//--------------------------------------------------------------------------------------

	const int				fInsCount;					// number of audio input ports
	const int				fOutsCount;					// number of audio output ports
	int						fCtrlCount;					// number of control ports
	
	float* 					fPortZone1[MAXPORT];			// 
	float* 					fPortData1[MAXPORT];
	
	
	//--------------------------------------------------------------------------------------

	void addZone1(float* zone1) 
	{
		fPortZone1[fInsCount + fOutsCount + fCtrlCount] = zone1; 
		fCtrlCount++; 
	}
	
	
	
 public:
		
	
	//--------------------------------Collect the audio ports-------------------------------

	portData1(int ins, int outs) : UI(), fInsCount(ins), fOutsCount(outs), fCtrlCount(0) {};
	virtual ~portData1() {}
	
	
	//------------------------------Collect the control zone1s-------------------------------

	virtual void addButton(const char* label, float* zone1) 			{ addZone1(zone1); }
	virtual void addToggleButton(const char* label, float* zone1)  	{ addZone1(zone1); }
	virtual void addCheckButton(const char* label, float* zone1)  		{ addZone1(zone1); }
		
	virtual void addVerticalSlider(const char* label, float* zone1, float initamp, float min, float max, float step) 		{ addZone1(zone1); }
	virtual void addVerticalSlider1(const char* label, float* zone, float initdis, float min, float max, float step) 		{ addZone1(zone); }
	virtual void addVerticalSlider0(const char* label, float* zone, float initdis, float min, float max, float step) 		{ addZone1(zone); }
	virtual void addHorizontalSlider(const char* label, float* zone1, float initamp, float min, float max, float step) 	{ addZone1(zone1); }
	virtual void addNumEntry1(const char* label, float* zone1, float initamp, float min, float max, float step)  			{ addZone1(zone1); }
		
	// -- passive widgets
	
	virtual void addNumDisplay1(const char* label, float* zone1, int precision) 						{ addZone1(zone1); }
	virtual void addTextDisplay1(const char* label, float* zone1, char* names[], float min, float max) 	{ addZone1(zone1); }
	virtual void addHorizontalBargraph1(const char* label, float* zone1, float min, float max) 			{ addZone1(zone1); }
	virtual void addVerticalBargraph1(const char* label, float* zone1, float min, float max)			{ addZone1(zone1); }
	
	virtual void openFrameBox1(const char* label)		{ }
	virtual void openTabBox1(const char* label)		{ }
	virtual void openHorizontalBox1(const char* label)	{ }
	virtual void openVerticalBox1(const char* label)	{ }
	virtual void closeBox1() 					{ }
	
	virtual void show() {}
	virtual void run() 	{}
	
	
	//---------------------------------interaction with LADSPA------------------------------
	
	void setPortData1 (unsigned long port, LADSPA_Data* data) {
		fPortData1[port] = data;
	}
	
	void updateCtrlZones1() {
		for (int i = fInsCount+fOutsCount; i < fInsCount+fOutsCount+fCtrlCount; i++)	*fPortZone1[i] = *fPortData1[i];
	}

	float** getInputs() {
		return &fPortData1[0];
	}

	float** getOutputs() {
		return &fPortData1[fInsCount];
	}	
};




//--------------------------------Faust-LADSPA plugin-----------------------------------
//
// Plugin structure, callbacks and LADSPA_descriptor(i) entry point
//
//--------------------------------------------------------------------------------------

LADSPA_Descriptor* 	gDescriptor1 = 0;

struct PLUGIN1 
{
	unsigned long	fSampleRate;
	portData1*		fPortData1;
	dspamp*			fDspamp;
	
	PLUGIN1(unsigned long r, portData1* d, dspamp* p) : fSampleRate(r), fPortData1(d), fDspamp(p) {}
};
	
LADSPA_Handle instantiate_method1 (const struct _LADSPA_Descriptor * Descriptor, unsigned long SampleRate) 
{
	dspamp*		p1 = new ampdsp();
	portData1* 	damp = new portData1(p1->getNumInputs(), p1->getNumOutputs());
	
	p1->buildUserInterface1(damp);	
	return new PLUGIN1 (SampleRate, damp, p1);
}

void connect_method1 (LADSPA_Handle Instance1, unsigned long Port, LADSPA_Data * DataLocation1) 
{
	PLUGIN1* p1 = (PLUGIN1*) Instance1;
	p1->fPortData1->setPortData1(Port, DataLocation1);
}

void activate_method1 (LADSPA_Handle Instance1)
{
	PLUGIN1* p1 = (PLUGIN1*) Instance1;
	p1->fDspamp->initamp(p1->fSampleRate);
}

void run_method1 (LADSPA_Handle Instance1, unsigned long SampleCount)
{
	PLUGIN1* p1 = (PLUGIN1*) Instance1;
	p1->fPortData1->updateCtrlZones1();
	p1->fDspamp->computeamp(SampleCount, p1->fPortData1->getInputs(), p1->fPortData1->getOutputs());
}

void deactivate_method1 (LADSPA_Handle Instance1)
{
}

void cleanup_method (LADSPA_Handle Instance1)
{
	PLUGIN1* p1 = (PLUGIN1*) Instance1;
	delete p1->fPortData1;
	delete p1->fDspamp;
	delete p1;
}


//--------------------------------------------------------------------------------------

void initamp_descriptor(LADSPA_Descriptor* descriptor1) 
{
	descriptor1->UniqueID = 4066;
	descriptor1->Label = "monoamp";
	descriptor1->Properties = LADSPA_PROPERTY_HARD_RT_CAPABLE;
	descriptor1->Name = "monoamp";
	descriptor1->Maker = "brummer";
	descriptor1->Copyright = "GPL";
	
	descriptor1->ImplementationData = 0;
	
	// description des methods
	descriptor1->instantiate = instantiate_method1;
	descriptor1->connect_port = connect_method1;
	descriptor1->activate = activate_method1;
	descriptor1->run = run_method1;
	descriptor1->run_adding = 0;
	descriptor1->set_run_adding_gain = 0;
	descriptor1->deactivate = deactivate_method1;
	descriptor1->cleanup = cleanup_method;
}



//--------------------------------------------------------------------------------------

const LADSPA_Descriptor * ladspa_descriptor(unsigned long Index) 
{
    if (Index == 0) {
		if (gDescriptor1 == 0) 
		{
			// allocate temporaries dsp and portCollector1 to build the plugin description
			ampdsp* p1 = new ampdsp();
			if (p1) {
				portCollector1*	c=new portCollector1(p1->getNumInputs(), p1->getNumOutputs());
				p1->buildUserInterface1(c);
				gDescriptor1 = new LADSPA_Descriptor;
				initamp_descriptor(gDescriptor1);
				c->fillPortDescription(gDescriptor1);
				delete p1;
			} else {
				printf("Memory Error : unable to allocate the dsp object\n");
			}
		}
		return gDescriptor1;
	} else {
		return NULL;
	}
}

