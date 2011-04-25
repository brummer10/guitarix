//-----------------------------------------------------
// name: "crybaby"
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
// Abstract definitcryion of a User Interface to be passed to the 
// buildUserInterface methodcry of a Faust Signal Processor
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
	virtual void addVerticalSlider(const char* label, float* zone, float initcry, float min, float max, float step) = 0;
	virtual void addVerticalSlider1(const char* label, float* zone, float initdis, float min, float max, float step) = 0;
	virtual void addVerticalSlider0(const char* label, float* zone, float initdis, float min, float max, float step) = 0;
	virtual void addHorizontalSlider(const char* label, float* zone, float initcry, float min, float max, float step) = 0;
	virtual void addNumEntry(const char* label, float* zone, float initcry, float min, float max, float step) = 0;
		
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
//  Abstract definitcryion of a Faust Signal Processor
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
	virtual void initcry(int samplingRate) 							= 0;
 	virtual void compute(int len, float** inputs, float** outputs) 	= 0;
};
		

//----------------------------------------------------------------------------
// 	FAUST generated code
//----------------------------------------------------------------------------
		

class crydsp : public dsp {
  private:
	float 	fslider0;
	float 	fRec1[2];
	float 	fslider1;
	float 	fslider2;
	float 	fConst0;
	float 	fConst1;
	float 	fRec2[2];
	float 	fRec3[2];
	float 	fRec0[3];
	float 	fcheckbox0;
  public:
	static void metadata(Meta* m) 	{ 
		m->declare("name", "emptty");
		m->declare("version", "0.01");
		m->declare("author", "brummer");
		m->declare("license", "GPL");
	}

	virtual int getNumInputs() 	{ return 1; }
	virtual int getNumOutputs() 	{ return 1; }
	static void classinitcry(int samplingFreq) {
	}
	virtual void instanceinitcry(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fslider0 = 0.0f;
		for (int i=0; i<2; i++) fRec1[i] = 0;
		fslider1 = 0.1f;
		fslider2 = 0.0f;
		fConst0 = (2827.43335f / fSamplingFreq);
		fConst1 = (1413.716675f / fSamplingFreq);
		for (int i=0; i<2; i++) fRec2[i] = 0;
		for (int i=0; i<2; i++) fRec3[i] = 0;
		for (int i=0; i<3; i++) fRec0[i] = 0;
		fcheckbox0 = 1.0;
	}
	virtual void initcry(int samplingFreq) {
		classinitcry(samplingFreq);
		instanceinitcry(samplingFreq);
	}
	virtual void buildUserInterface(UI* interface) {
		interface->openHorizontalBox("crybaby");
		interface->addHorizontalSlider("level", &fslider1, 0.1f, 0.0f, 1.0f, 1.000000e-02f);
		interface->addVerticalSlider0("wah", &fslider0, 0.0f, 0.0f, 1.0f, 1.000000e-02f);
		interface->addVerticalSlider("wet/dry", &fslider2, 0.0f, -1.0f, 1.0f, 1.000000e-03f);
		interface->closeBox();
	}
		virtual void compute (int count, float** input, float** output) {
			float 	fSlow0 = fslider0;
			float 	fSlow1 = (9.999872e-05f * powf(4.0f, fSlow0));
			float 	fSlow2 = fslider2;
			float 	fSlow3 = ((1 - max(0, (0 - fSlow2))) * fslider1);
			float 	fSlow4 = powf(2.0f, (2.3f * fSlow0));
			float 	fSlow5 = (1 - (fConst1 * (fSlow4 / powf(2.0f, (1.0f + (2.0f * (1.0f - fSlow0)))))));
			float 	fSlow6 = (9.999871e-04f * (0 - (2.0f * (fSlow5 * cosf((fConst0 * fSlow4))))));
			float 	fSlow7 = (9.999871e-04f * (fSlow5 * fSlow5));
			float 	fSlow8 = (1 - max(0, fSlow2));
			int 	iSlow9 = int(fcheckbox0);
			float* input0 = input[0];
			float* output0 = output[0];
			for (int i=0; i<count; i++) {
				float 	S0[2];
				float fTemp0 = input0[i];
				S0[0] = fTemp0;
				fRec1[0] = (fSlow1 + (0.999f * fRec1[1]));
				fRec2[0] = (fSlow6 + (0.999f * fRec2[1]));
				fRec3[0] = (fSlow7 + (0.999f * fRec3[1]));
				fRec0[0] = (0 - (((fRec3[0] * fRec0[2]) + (fRec2[0] * fRec0[1])) - (fSlow3 * (fTemp0 * fRec1[0]))));
				S0[1] = ((fRec0[0] + (fSlow8 * fTemp0)) - fRec0[1]);
				output0[i] = S0[iSlow9];
				// post processing
				fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
				fRec3[1] = fRec3[0];
				fRec2[1] = fRec2[0];
				fRec1[1] = fRec1[0];
			}
		}
};




		
	

//-----------------------------------portCollector--------------------------------------
//
// portCollector is passed to the buildUserInterface methodcry of a dsp object
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



class portCollector : public UI
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

	void addPortDescrcry(int type, const char* label, int hint, float min=0.0, float max=0.0) 
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

	portCollector(int ins, int outs) : UI(), fInsCount(ins), fOutsCount(outs), fCtrlCount(0) 
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

	virtual ~portCollector() {}
	
	
	
	//------------------------------Collect the control ports-------------------------------

	virtual void addButton(const char* label, float* zone) { 
		addPortDescrcry(ICONTROL, label, LADSPA_HINT_TOGGLED); 
	}
	
	virtual void addToggleButton(const char* label, float* zone) { 
		addPortDescrcry(ICONTROL, label, LADSPA_HINT_TOGGLED|  LADSPA_HINT_DEFAULT_0 ); 
	}
	
	virtual void addCheckButton(const char* label, float* zone) { 
		addPortDescrcry(ICONTROL, label, LADSPA_HINT_TOGGLED| LADSPA_HINT_DEFAULT_1 ); 
	}
		
	virtual void addVerticalSlider(const char* label, float* zone, float initdis, float min, float max, float step) { 
		addPortDescrcry(ICONTROL, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_MIDDLE , min, max); 
	}
 
	virtual void addVerticalSlider0(const char* label, float* zone, float initdis, float min, float max, float step) { 
		addPortDescrcry(ICONTROL, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_MINIMUM , min, max); 
	}
 
	virtual void addVerticalSlider1(const char* label, float* zone, float initdis, float min, float max, float step) { 
		addPortDescrcry(ICONTROL, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_MAXIMUM, min, max); 
	}		
		
	virtual void addHorizontalSlider(const char* label, float* zone, float initdis, float min, float max, float step) { 
		addPortDescrcry(ICONTROL, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE  | LADSPA_HINT_DEFAULT_LOW, min, max); 
	}

	virtual void addNumEntry(const char* label, float* zone, float initcry, float min, float max, float step) { 
		addPortDescrcry(ICONTROL, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE, min, max); 
	}
		
	// -- passive widgets
	
	virtual void addNumDisplay(const char* label, float* zone, int precision) {
		addPortDescrcry(OCONTROL, label, 0, -10000, +10000); 
	}
	virtual void addTextDisplay(const char* label, float* zone, char* names[], float min, float max) {
		addPortDescrcry(OCONTROL, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE, min, max); 
	}
	virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max) {
		addPortDescrcry(OCONTROL, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE, min, max); 
	}
	virtual void addVerticalBargraph(const char* label, float* zone, float min, float max){
		addPortDescrcry(OCONTROL, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE, min, max); 
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
		const char* name = sym(crydsp);
		descriptor->PortCount 			= fCtrlCount+fInsCount+fOutsCount;
		descriptor->PortDescriptors 	= fPortDescs;
		descriptor->PortNames 			= fPortNames;
		descriptor->PortRangeHints 		= fPortHints;
		
		descriptor->Label = strdup(name);
		descriptor->UniqueID = 4062;
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
		
	virtual void addVerticalSlider(const char* label, float* zone, float initcry, float min, float max, float step) 		{ addZone(zone); }
	virtual void addVerticalSlider1(const char* label, float* zone, float initdis, float min, float max, float step) 		{ addZone(zone); }
	virtual void addVerticalSlider0(const char* label, float* zone, float initdis, float min, float max, float step) 		{ addZone(zone); }
	virtual void addHorizontalSlider(const char* label, float* zone, float initcry, float min, float max, float step) 	{ addZone(zone); }
	virtual void addNumEntry(const char* label, float* zone, float initcry, float min, float max, float step)  			{ addZone(zone); }
		
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
	
	void setPortDatacry (unsigned long port, LADSPA_Data* data) {
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

LADSPA_Descriptor* 	gDescriptorc = 0;

struct PLUGIN 
{
	unsigned long	fSampleRate;
	portData*		fPortData;
	dsp*			fDsp;
	
	PLUGIN(unsigned long r, portData* d, dsp* p) : fSampleRate(r), fPortData(d), fDsp(p) {}
};
	
LADSPA_Handle instantiate_methodcry (const struct _LADSPA_Descriptor * Descriptor, unsigned long SampleRate) 
{
	dsp*		p = new crydsp();
	portData* 	d = new portData(p->getNumInputs(), p->getNumOutputs());
	
	p->buildUserInterface(d);	
	return new PLUGIN (SampleRate, d, p);
}

void connect_methodcry (LADSPA_Handle Instance, unsigned long Port, LADSPA_Data * DataLocation) 
{
	PLUGIN* p = (PLUGIN*) Instance;
	p->fPortData->setPortDatacry(Port, DataLocation);
}

void activate_methodcry (LADSPA_Handle Instance)
{
	PLUGIN* p = (PLUGIN*) Instance;
	p->fDsp->initcry(p->fSampleRate);
}

void run_methodcry (LADSPA_Handle Instance, unsigned long SampleCount)
{
	PLUGIN* p = (PLUGIN*) Instance;
	p->fPortData->updateCtrlZones();
	p->fDsp->compute(SampleCount, p->fPortData->getInputs(), p->fPortData->getOutputs());
}

void deactivate_methodcry (LADSPA_Handle Instance)
{
}

void cleanup_methodcry (LADSPA_Handle Instance)
{
	PLUGIN* p = (PLUGIN*) Instance;
	delete p->fPortData;
	delete p->fDsp;
	delete p;
}


//--------------------------------------------------------------------------------------

void initcry_descriptor(LADSPA_Descriptor* descriptor) 
{
	descriptor->UniqueID = 4062;
	descriptor->Label = "crybaby";
	descriptor->Properties = LADSPA_PROPERTY_HARD_RT_CAPABLE;
	descriptor->Name = "crybaby";
	descriptor->Maker = "brummer";
	descriptor->Copyright = "GPL";
	
	descriptor->ImplementationData = 0;
	
	// description des methodcrys
	descriptor->instantiate = instantiate_methodcry;
	descriptor->connect_port = connect_methodcry;
	descriptor->activate = activate_methodcry;
	descriptor->run = run_methodcry;
	descriptor->run_adding = 0;
	descriptor->set_run_adding_gain = 0;
	descriptor->deactivate = deactivate_methodcry;
	descriptor->cleanup = cleanup_methodcry;
}



//--------------------------------------------------------------------------------------

const LADSPA_Descriptor * ladspa_descriptor(unsigned long Index) 
{
    if (Index == 0) {
		if (gDescriptorc == 0) 
		{
			// allocate temporaries dsp and portCollector to build the plugin description
			crydsp* p = new crydsp();
			if (p) {
				portCollector*	c=new portCollector(p->getNumInputs(), p->getNumOutputs());
				p->buildUserInterface(c);
				gDescriptorc = new LADSPA_Descriptor;
				initcry_descriptor(gDescriptorc);
				c->fillPortDescription(gDescriptorc);
				delete p;
			} else {
				printf("Memory Error : unable to allocate the dsp object\n");
			}
		}
		return gDescriptorc;
	} else {
		return NULL;
	}
}

