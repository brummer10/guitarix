/*
 * Copyright (C) 2009, 2010 Hermann Meyer, James Warden, Andreas Degert
 * Copyright (C) 2011 Pete Shorthose
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
 * --------------------------------------------------------------------------
 *
 *    This is the guitarix UI, it is part of the guitarix GUI main class
 *    Note: this header file is the base for gx_main_interface.h and
 *    gx_main_boxes.h
 * 
 * ----------------------------------------------------------------------------
 */


#pragma once

#ifndef GX_UI
#define GX_UI

#include <map>
#include <list>

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
public:
	virtual ~GxUiItem();
	GxUiItem(GxUI *ui): fGUI(ui) {}
	virtual void reflectZone() = 0;
	virtual bool hasChanged() = 0;
};

class GxUiItemFloat: GxUiItem
{
protected :
	float*	fZone;
	float	fCache;
	GxUiItemFloat(GxUI* ui, float* zone);
public :
	void  modifyZone(float v);
	virtual bool hasChanged();
};

class GxUiItemInt: GxUiItem
{
protected :
	int* fZone;
	int fCache;
	GxUiItemInt(GxUI* ui, int* zone);
public :
	void  modifyZone(int v);
	virtual bool hasChanged();
};

class GxUiItemBool: GxUiItem
{
protected :
	bool* fZone;
	bool fCache;
	GxUiItemBool(GxUI* ui, bool* zone);
public :
	void  modifyZone(bool v);
	virtual bool hasChanged();
};


/* --- Callback Item --- */
typedef void (*GxUiCallback)(float val, void* data);

struct GxUiCallbackItemFloat : public GxUiItemFloat
{
	GxUiCallback fCallback;
	void*	 fData;

	GxUiCallbackItemFloat(GxUI* ui, float* zone, GxUiCallback foo, void* data);
	virtual void reflectZone();
};

/* --- Main UI base class --- */
class GxUI
{
	typedef list< GxUiItem* > clist;
	typedef map < void*, clist* > zmap;

private:
	static list<GxUI*>	fGuiList;
	zmap		fZoneMap;

public:
	GxUI();
	virtual ~GxUI() {}

	// public methods
	void registerZone(void*, GxUiItem*);
	void updateAllZones();
	void updateZone(void* z);
	static void updateAllGuis();
};

} /* end of gx_ui namespace */

#endif

