//-----------------------------------------------------
// name: "echo"
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
// Abstract definitechion of a User Interface to be passed to the 
// buildUserInterfaceech methodech of a Faust Signal Processor
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
	virtual void addVerticalSlider(const char* label, float* zone, float initech, float min, float max, float step) = 0;
	virtual void addVerticalSlider1(const char* label, float* zone, float initdis, float min, float max, float step) = 0;
	virtual void addVerticalSlider0(const char* label, float* zone, float initdis, float min, float max, float step) = 0;
	virtual void addHorizontalSlider(const char* label, float* zone, float initech, float min, float max, float step) = 0;
	virtual void addNumEntry(const char* label, float* zone, float initech, float min, float max, float step) = 0;
		
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
//  Abstract definitechion of a Faust Signal Processor
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
	virtual void buildUserInterfaceech(UI* interface) 					= 0;
	virtual void initech(int samplingRate) 							= 0;
 	virtual void computeech(int len, float** inputs, float** outputs) 	= 0;
};
		

//----------------------------------------------------------------------------
// 	FAUST generated code
//----------------------------------------------------------------------------
		

class echodsp : public dsp {
  private:
	float 	fslider0;
	float 	fConst0;
	float 	fslider1;
	int 	IOTA;
	float 	fRec0[262144];
	float 	fcheckbox0;
  public:
	static void metadata(Meta* m) 	{ 
		m->declare("name", "echo");
		m->declare("version", "0.1");
		m->declare("author", "brummer");
		m->declare("license", "GPL");
	}

	virtual int getNumInputs() 	{ return 1; }
	virtual int getNumOutputs() 	{ return 1; }
	static void classinitech(int samplingFreq) {
	}
	virtual void instanceinitech(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fslider0 = 0.0f;
		fConst0 = (1.000000e-03f * fSamplingFreq);
		fslider1 = 0.0f;
		IOTA = 0;
		for (int i=0; i<262144; i++) fRec0[i] = 0;
		fcheckbox0 = 1.0;
	}
	virtual void initech(int samplingFreq) {
		classinitech(samplingFreq);
		instanceinitech(samplingFreq);
	}
	virtual void buildUserInterfaceech(UI* interface) {
		interface->openHorizontalBox("echo");
		interface->addVerticalSlider("release", &fslider1, 0.0f, 0.0f, 100.0f, 0.1f);
		interface->addVerticalSlider("time", &fslider0, 1.0f, 1.0f, 2000.0f, 1.0f);
		interface->closeBox();
	}
		virtual void computeech (int count, float** input, float** output) {
			int 	iSlow0 = int((1 + int((int((int((fConst0 * fslider0)) - 1)) & 131071))));
			float 	fSlow1 = (1.000000e-02f * fslider1);
			int 	iSlow2 = int(fcheckbox0);
			float* input0 = input[0];
			float* output0 = output[0];
			for (int i=0; i<count; i++) {
				float 	S0[2];
				float fTemp0 = input0[i];
				S0[0] = fTemp0;
				fRec0[IOTA&262143] = (fTemp0 + (fSlow1 * fRec0[(IOTA-iSlow0)&262143]));
				S0[1] = fRec0[(IOTA-0)&262143];
				output0[i] = S0[iSlow2];
				// post processing
				IOTA = IOTA+1;
			}
		}
};




		
	

//-----------------------------------portCollectorech--------------------------------------
//
// portCollectorech is passed to the buildUserInterfaceech methodech of a dsp object
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



class portCollectorech : public UI
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

	void addPortDescrechech(int type, const char* label, int hint, float min=0.0, float max=0.0) 
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
	
	void openAnyBoxech(const char* label)
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

	portCollectorech(int ins, int outs) : UI(), fInsCount(ins), fOutsCount(outs), fCtrlCount(0) 
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

	virtual ~portCollectorech() {}
	
	
	
	//------------------------------Collect the control ports-------------------------------

	virtual void addButton(const char* label, float* zone) { 
		addPortDescrechech(ICONTROL, label, LADSPA_HINT_TOGGLED); 
	}
	
	virtual void addToggleButton(const char* label, float* zone) { 
		addPortDescrechech(ICONTROL, label, LADSPA_HINT_TOGGLED|  LADSPA_HINT_DEFAULT_0 ); 
	}
	
	virtual void addCheckButton(const char* label, float* zone) { 
		addPortDescrechech(ICONTROL, label, LADSPA_HINT_TOGGLED| LADSPA_HINT_DEFAULT_1 ); 
	}
		
	virtual void addVerticalSlider(const char* label, float* zone, float initdis, float min, float max, float step) { 
		addPortDescrechech(ICONTROL, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_MIDDLE , min, max); 
	}
 
	virtual void addVerticalSlider0(const char* label, float* zone, float initdis, float min, float max, float step) { 
		addPortDescrechech(ICONTROL, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_MINIMUM , min, max); 
	}
 
	virtual void addVerticalSlider1(const char* label, float* zone, float initdis, float min, float max, float step) { 
		addPortDescrechech(ICONTROL, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_MAXIMUM, min, max); 
	}		
		
	virtual void addHorizontalSlider(const char* label, float* zone, float initdis, float min, float max, float step) { 
		addPortDescrechech(ICONTROL, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE  | LADSPA_HINT_DEFAULT_LOW, min, max); 
	}

	virtual void addNumEntry(const char* label, float* zone, float initech, float min, float max, float step) { 
		addPortDescrechech(ICONTROL, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE, min, max); 
	}
		
	// -- passive widgets
	
	virtual void addNumDisplay(const char* label, float* zone, int precision) {
		addPortDescrechech(OCONTROL, label, 0, -10000, +10000); 
	}
	virtual void addTextDisplay(const char* label, float* zone, char* names[], float min, float max) {
		addPortDescrechech(OCONTROL, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE, min, max); 
	}
	virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max) {
		addPortDescrechech(OCONTROL, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE, min, max); 
	}
	virtual void addVerticalBargraph(const char* label, float* zone, float min, float max){
		addPortDescrechech(OCONTROL, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE, min, max); 
	}

	virtual void openFrameBox(const char* label)		{ openAnyBoxech(label); }
	virtual void openTabBox(const char* label)		{ openAnyBoxech(label); }
	virtual void openHorizontalBox(const char* label)	{ openAnyBoxech(label); }
	virtual void openVerticalBox(const char* label)	{ openAnyBoxech(label); }
	
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
		const char* name = sym(echodsp);
		descriptor->PortCount 			= fCtrlCount+fInsCount+fOutsCount;
		descriptor->PortDescriptors 	= fPortDescs;
		descriptor->PortNames 			= fPortNames;
		descriptor->PortRangeHints 		= fPortHints;
		
		descriptor->Label = strdup(name);
		descriptor->UniqueID = 4063;
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
		
	virtual void addVerticalSlider(const char* label, float* zone, float initech, float min, float max, float step) 		{ addZone(zone); }
	virtual void addVerticalSlider1(const char* label, float* zone, float initdis, float min, float max, float step) 		{ addZone(zone); }
	virtual void addVerticalSlider0(const char* label, float* zone, float initdis, float min, float max, float step) 		{ addZone(zone); }
	virtual void addHorizontalSlider(const char* label, float* zone, float initech, float min, float max, float step) 	{ addZone(zone); }
	virtual void addNumEntry(const char* label, float* zone, float initech, float min, float max, float step)  			{ addZone(zone); }
		
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
	
	void setPortDataech (unsigned long port, LADSPA_Data* data) {
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

LADSPA_Descriptor* 	gDescriptore = 0;

struct PLUGIN 
{
	unsigned long	fSampleRate;
	portData*		fPortData;
	dsp*			fDsp;
	
	PLUGIN(unsigned long r, portData* d, dsp* p) : fSampleRate(r), fPortData(d), fDsp(p) {}
};
	
LADSPA_Handle instantiate_methodech (const struct _LADSPA_Descriptor * Descriptor, unsigned long SampleRate) 
{
	dsp*		p = new echodsp();
	portData* 	d = new portData(p->getNumInputs(), p->getNumOutputs());
	
	p->buildUserInterfaceech(d);	
	return new PLUGIN (SampleRate, d, p);
}

void connect_methodech (LADSPA_Handle Instance, unsigned long Port, LADSPA_Data * DataLocation) 
{
	PLUGIN* p = (PLUGIN*) Instance;
	p->fPortData->setPortDataech(Port, DataLocation);
}

void activate_methodech (LADSPA_Handle Instance)
{
	PLUGIN* p = (PLUGIN*) Instance;
	p->fDsp->initech(p->fSampleRate);
}

void run_methodech (LADSPA_Handle Instance, unsigned long SampleCount)
{
	PLUGIN* p = (PLUGIN*) Instance;
	p->fPortData->updateCtrlZones();
	p->fDsp->computeech(SampleCount, p->fPortData->getInputs(), p->fPortData->getOutputs());
}

void deactivate_methodech (LADSPA_Handle Instance)
{
}

void cleanup_methodech (LADSPA_Handle Instance)
{
	PLUGIN* p = (PLUGIN*) Instance;
	delete p->fPortData;
	delete p->fDsp;
	delete p;
}


//--------------------------------------------------------------------------------------

void initech_descriptor(LADSPA_Descriptor* descriptor) 
{
	descriptor->UniqueID = 4063;
	descriptor->Label = "echo";
	descriptor->Properties = LADSPA_PROPERTY_HARD_RT_CAPABLE;
	descriptor->Name = "echo";
	descriptor->Maker = "brummer";
	descriptor->Copyright = "GPL";
	
	descriptor->ImplementationData = 0;
	
	// description des methodechs
	descriptor->instantiate = instantiate_methodech;
	descriptor->connect_port = connect_methodech;
	descriptor->activate = activate_methodech;
	descriptor->run = run_methodech;
	descriptor->run_adding = 0;
	descriptor->set_run_adding_gain = 0;
	descriptor->deactivate = deactivate_methodech;
	descriptor->cleanup = cleanup_methodech;
}



//--------------------------------------------------------------------------------------

const LADSPA_Descriptor * ladspa_descriptor(unsigned long Index) 
{
    if (Index == 0) {
		if (gDescriptore == 0) 
		{
			// allocate temporaries dsp and portCollectorech to build the plugin description
			echodsp* p = new echodsp();
			if (p) {
				portCollectorech*	c=new portCollectorech(p->getNumInputs(), p->getNumOutputs());
				p->buildUserInterfaceech(c);
				gDescriptore = new LADSPA_Descriptor;
				initech_descriptor(gDescriptore);
				c->fillPortDescription(gDescriptore);
				delete p;
			} else {
				printf("Memory Error : unable to allocate the dsp object\n");
			}
		}
		return gDescriptore;
	} else {
		return NULL;
	}
}

