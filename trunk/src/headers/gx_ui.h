/*
 * Copyright (C) 2009, 2010 Hermann Meyer, James Warden, Andreas Degert
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
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 * --------------------------------------------------------------------------
 */

/* ----- This is the guitarix UI, it belongs to the guitarix namespace ------ */

#pragma once

// --- interface defines
#define stackSize 256
#define kSingleMode 0
#define kBoxMode 1
#define kTabMode 2

namespace gx_ui
{
/* ------------- UI Classes ------------- */
/* base interface classes interfacing with the GUI  */
class GxUI;

/* --- GxUiItem (virtual class) --- */
class GxUiItem
{
protected :
	GxUI*	fGUI;
	float*	fZone;
	float	fCache;

	GxUiItem (GxUI* ui, float* zone);

public :
	virtual ~GxUiItem() {}

	void  modifyZone(float v);
	float cache();
	virtual void reflectZone() = 0;
};


/* --- Callback Item --- */
typedef void (*GxUiCallback)(float val, void* data);

struct GxUiCallbackItem : public GxUiItem
{
	GxUiCallback fCallback;
	void*	 fData;

	GxUiCallbackItem(GxUI* ui, float* zone, GxUiCallback foo, void* data);
	virtual void reflectZone();
};

/* --- Main UI base class --- */
class GxUI
{
	typedef list< GxUiItem* > clist;
	typedef map < float*, clist* > zmap;

private:
	static list<GxUI*>	fGuiList;
	zmap		fZoneMap;
	bool		fStopped;

public:
	GxUI();
	virtual ~GxUI() {}

	// public methods
	void registerZone(float*, GxUiItem*);
	void updateAllZones();
	void updateZone(float* z);
	static void updateAllGuis();

	//    virtual GtkTextView* const getLoggingWindow() const { return NULL; }

	virtual void addMenu() {};
	virtual void addJConvButton(const char* label, float* zone) {};
	virtual void addToggleButton(const char* label, float* zone) {};
	virtual void addPToggleButton(const char* label, float* zone) {};
	virtual void addJToggleButton(const char* label, float* zone) {};
	virtual void addCheckButton(const char* label, float* zone) {};
	virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step) {};
	virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step) {};
	virtual void addHorizontalWheel(const char* label, float* zone, float init, float min, float max, float step){};
	virtual void addregler(const char* label, float* zone, float init, float min, float max, float step){};
	virtual void addbigregler(const char* label, float* zone, float init, float min, float max, float step) {};
	virtual void addslider(const char* label, float* zone, float init, float min, float max, float step){};
	virtual void addtoggle(const char* label, int* zone){};
	virtual void addtoggle(const char* label, float* zone){};
	virtual void addbtoggle(const char* label, int* zone){};
	virtual void addbtoggle(const char* label, float* zone){};
	virtual void addswitch(const char* label, int* zone){};
	virtual void addswitch(const char* label, float* zone){};
	virtual void addminiswitch(const char* label, int* zone){};
	virtual void addminiswitch(const char* label, float* zone){};
	virtual void addminieqswitch(const char* label, float* zone){};
	virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step) {};
	virtual void addNumDisplay(const char* label, float* zone) {};
	virtual void addLiveWaveDisplay(const char* label, float* zone , float* zone1) {};
	virtual void addStatusDisplay(const char* label, float* zone ) {};
	virtual void addselector(const char* label, float* zone, int maxv, const char* []){};


	void addCallback(float* zone, GxUiCallback foo, void* data);

	// -- widget's layouts
	virtual void openHorizontalOrderBox(const char* label, float* posit){};
	virtual void openHorizontalTableBox(const char* label){};
	virtual void openHorizontalRestetBox(const char* label, float* posit){};
	virtual void openFrameBox(const char* label) {};
	virtual void openHorizontalBox(const char* label) {};
	virtual void openHorizontalhideBox(const char* label) {};
	virtual void openVerticalBox(const char* label) {};
	virtual void openVerticalBox1(const char* label) {};
	virtual void openFlipLabelBox(const char* = ""){};
	virtual void openVerticalMidiBox(const char* label) {};
	virtual void openDialogBox(const char* label, float* zone) {};
	virtual void openPatchInfoBox(float* zone){};
	virtual void openWarningBox(const char* label, float* zone){};
	virtual void openEventBox(const char* label) {};
	virtual void openHandleBox(const char* label) {};
	virtual void openExpanderBox(const char* label, float* zone) {};
	virtual void openTabBox(const char* label) {};
	virtual void openSpaceBox(const char* label){};
	virtual void openAmpBox(const char* label){};
	virtual void openPlugBox(const char* label){};
	virtual void openpaintampBox(const char* label){};
	virtual void openPaintBox(const char* label){};
	virtual void openPaintBox1(const char* label){};
	virtual void openPaintBox2(const char* label){};
	virtual void openScrollBox(const char* label){};
	virtual void openTextLoggingBox(const char* label) {};
	virtual void openLevelMeterBox(const char* label)  {};
	virtual void openJackClientBox(const char* label) {};
	virtual void openToolBar(const char* label){};
	virtual void setSkinBox(const char* label, float* zone){};
	virtual void closeBox() {};

	virtual void setup() {};
	virtual void show() {};
	virtual void run() {};

	void stop()    { fStopped = true; }
	bool stopped() { return fStopped; }

	virtual void declare(float* zone, const char* key, const char* value) {}
};

} /* end of gx_ui namespace */
