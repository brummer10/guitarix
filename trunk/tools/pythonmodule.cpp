/*
 * most of the code copied from plot.cpp of faust project
 * Changes and additions Copyright (C) 2011 Andreas Degert
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *----------------------------------------------------------------
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <errno.h>
#include <time.h>
#include <ctype.h>

#include <vector>
#include <stack>
#include <string>
#include <map>
#include <iostream> 

using namespace std;

struct Meta : map<const char*, const char*>
{
    void declare (const char* key, const char* value) { (*this)[key]=value; }
};

//-------------------------------------------------------------------
// Generic min and max using c++ inline
//-------------------------------------------------------------------

inline int	max (unsigned int a, unsigned int b) { return (a>b) ? a : b; }
inline int	max (int a, int b) 		{ return (a>b) ? a : b; }

inline long 	max (long a, long b) 		{ return (a>b) ? a : b; }
inline long 	max (int a, long b) 		{ return (a>b) ? a : b; }
inline long 	max (long a, int b) 		{ return (a>b) ? a : b; }

inline float 	max (float a, float b) 		{ return (a>b) ? a : b; }
inline float 	max (int a, float b) 		{ return (a>b) ? a : b; }
inline float 	max (float a, int b) 		{ return (a>b) ? a : b; }
inline float 	max (long a, float b) 		{ return (a>b) ? a : b; }
inline float 	max (float a, long b) 		{ return (a>b) ? a : b; }

inline double 	max (double a, double b) 	{ return (a>b) ? a : b; }
inline double 	max (int a, double b) 		{ return (a>b) ? a : b; }
inline double 	max (double a, int b) 		{ return (a>b) ? a : b; }
inline double 	max (long a, double b) 		{ return (a>b) ? a : b; }
inline double 	max (double a, long b) 		{ return (a>b) ? a : b; }
inline double 	max (float a, double b) 	{ return (a>b) ? a : b; }
inline double 	max (double a, float b) 	{ return (a>b) ? a : b; }


inline int 		min (int a, int b) 			{ return (a<b) ? a : b; }

inline long 	min (long a, long b) 		{ return (a<b) ? a : b; }
inline long 	min (int a, long b) 		{ return (a<b) ? a : b; }
inline long 	min (long a, int b) 		{ return (a<b) ? a : b; }

inline float 	min (float a, float b) 		{ return (a<b) ? a : b; }
inline float 	min (int a, float b) 		{ return (a<b) ? a : b; }
inline float 	min (float a, int b) 		{ return (a<b) ? a : b; }
inline float 	min (long a, float b) 		{ return (a<b) ? a : b; }
inline float 	min (float a, long b) 		{ return (a<b) ? a : b; }

inline double 	min (double a, double b) 	{ return (a<b) ? a : b; }
inline double 	min (int a, double b) 		{ return (a<b) ? a : b; }
inline double 	min (double a, int b) 		{ return (a<b) ? a : b; }
inline double 	min (long a, double b) 		{ return (a<b) ? a : b; }
inline double 	min (double a, long b) 		{ return (a<b) ? a : b; }
inline double 	min (float a, double b) 	{ return (a<b) ? a : b; }
inline double 	min (double a, float b) 	{ return (a<b) ? a : b; }
		


inline int lsr (int x, int n) { return int(((unsigned int)x) >> n); }
		
template<typename T> T abs (T a) { return (a<T(0)) ? -a : a; }


/******************************************************************************
*******************************************************************************

			       VECTOR INTRINSICS

*******************************************************************************
*******************************************************************************/

//inline void *aligned_calloc(size_t nmemb, size_t size) { return (void*)((unsigned)(calloc((nmemb*size)+15,sizeof(char)))+15 & 0xfffffff0); }
//inline void *aligned_calloc(size_t nmemb, size_t size) { return (void*)((size_t)(calloc((nmemb*size)+15,sizeof(char)))+15 & ~15); }

<<includeIntrinsic>>




/******************************************************************************
*******************************************************************************

				USER INTERFACE

*******************************************************************************
*******************************************************************************/

class UI {
    bool	fStopped;
public:
    UI() : fStopped(false) {}
    virtual ~UI() {}
	
    // -- active widgets
	
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
	
    void stop() { fStopped = true; }
    bool stopped() { return fStopped; }

    virtual void declare(float* zone, const char* key, const char* value) {}
};

struct param {
    float* fZone; float fMin; float fMax;
    param(float* z, float init, float a, float b) : fZone(z), fMin(a), fMax(b) { *z = init; }
};

typedef map<string, param> fKeyType;
typedef fKeyType::iterator fKeyIter;

class CMDUI : public UI
{
public:
    stack<string>	fPrefix;
    map<string, param>	fKeyParam;

private:	
    void openAnyBox(const char* label) {
	string prefix;

	if (label && label[0]) {
	    prefix = fPrefix.top() + "." + label;
	} else {
	    prefix = fPrefix.top();
	}
	fPrefix.push(prefix);
    }

    string simplify(const string& src) {
	int i=0;
	int level=0;
	string dst;

	while (src[i] ) {
	    switch (level) {
	    case 0: 	
	    case 1: 			
		// Skip the begin of the label "--foo-"
		// until 2 '.' have been read
		if (src[i]=='.') { level++; }
		break;
	    case 2:	
		// copy the content, but skip non alphnum
		// and content in parenthesis
		switch (src[i]) {
		case '(' : 	
		case '[' : 	
		    level++;
		    break;
		default :
		    dst+= src[i]; 
		}
		break;
	    default:	
		// here we are inside parenthesis and 
		// we skip the content until we are back to
		// level 2
		switch (src[i]) {
		case '(': 	
		case '[': 
		    level++;
		    break;
		case ')': 	
		case ']': 
		    level--;
		    break;
		default :
		    break;
		}
	    }
	    i++;
	}
	return dst;
    }
public:
    CMDUI() : UI() { fPrefix.push(""); }
    virtual ~CMDUI() {}

    void addOption(const char* label, float* zone, float init, float min, float max) {
	string fullname = simplify(fPrefix.top() + "." + label);
	fKeyParam.insert(make_pair(fullname, param(zone, init, min, max)));
    }

    virtual void addButton(const char* label, float* zone) {
	addOption(label,zone,0,0,1);
    }
	
    virtual void addToggleButton(const char* label, float* zone) {
	addOption(label,zone,0,0,1);
    }
	
    virtual void addCheckButton(const char* label, float* zone) {
	addOption(label,zone,0,0,1);
    }
		
    virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step) {
	addOption(label,zone,init,min,max);
    }
		
    virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step) {
	addOption(label,zone,init,min,max);
    }

    virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step) {
	addOption(label,zone,init,min,max);
    }
		
    // -- passive widgets
	
    virtual void addNumDisplay(const char* label, float* zone, int precision) {}
    virtual void addTextDisplay(const char* label, float* zone, char* names[], float min, float max) {}
    virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max) {}
    virtual void addVerticalBargraph(const char* label, float* zone, float min, float max) {}
	
    virtual void openFrameBox(const char* label) { openAnyBox(label); }
    virtual void openTabBox(const char* label) { openAnyBox(label); }
    virtual void openHorizontalBox(const char* label) { openAnyBox(label); }
    virtual void openVerticalBox(const char* label) { openAnyBox(label); }
	
    virtual void closeBox() { fPrefix.pop(); }
	
    virtual void show() {}
    virtual void run() {}
};

//----------------------------------------------------------------
//  definition du processeur de signal
//----------------------------------------------------------------
			
class dsp {
protected:
    int fSamplingFreq;
public:
    dsp() {}
    virtual ~dsp() {}
	
    virtual int getNumInputs() = 0;
    virtual int getNumOutputs() = 0;
    virtual void buildUserInterface(UI* interface) = 0;
    virtual void init(int samplingRate) = 0;
    virtual void compute(int len, float** inputs, float** outputs) = 0;
    virtual void conclude() {}
};
		

//----------------------------------------------------------------------------
// 	FAUST generated code
//----------------------------------------------------------------------------
		
<<includeclass>>
