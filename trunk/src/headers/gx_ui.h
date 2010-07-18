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

public:
	GxUI();
	virtual ~GxUI() {}

	// public methods
	void registerZone(float*, GxUiItem*);
	void updateAllZones();
	void updateZone(float* z);
	static void updateAllGuis();
};

} /* end of gx_ui namespace */
