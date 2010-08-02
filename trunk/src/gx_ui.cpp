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
 *
 *
 *
 *    GRAPHIC USER INTERFACE (v2)
 *    This is the Guitarix Engine GUI builder
 *
 *
 * --------------------------------------------------------------------------
 */

using namespace std;
#include "gx_ui.h"
#include <limits.h>

namespace gx_ui
{
list<GxUI*> GxUI::fGuiList;

// constructor
GxUI::GxUI()
{
	fGuiList.push_back(this);
}

// -- registerZone(z,c) : zone management
void GxUI::registerZone(void* z, GxUiItem* c)
{
	if (fZoneMap.find(z) == fZoneMap.end()) fZoneMap[z] = new clist();
	fZoneMap[z]->push_back(c);
}

void GxUI::updateAllGuis()
{
	list<GxUI*>::iterator g;
	for (g = fGuiList.begin(); g != fGuiList.end(); g++)
	{
		(*g)->updateAllZones();
	}
}

// Update all user items reflecting zone z
inline void GxUI::updateZone(void* z)
{
	clist* 	l = fZoneMap[z];
	for (clist::iterator c = l->begin(); c != l->end(); c++)
		if ((*c)->hasChanged()) (*c)->reflectZone();
}

// Update all user items not up to date
inline void GxUI::updateAllZones()
{
	for (zmap::iterator m = fZoneMap.begin(); m != fZoneMap.end(); m++)
	{
		clist*	l = m->second;
		for (clist::iterator c = l->begin(); c != l->end(); c++) {
			if ((*c)->hasChanged()) (*c)->reflectZone();
		}
	}
}

/* ---------------- GxUiItem stuff --------------- */
GxUiItem::~GxUiItem()
{
}

GxUiItemFloat::GxUiItemFloat(GxUI* ui, float* zone)
	: GxUiItem(ui), fZone(zone), fCache(-123456.654321)
{
	ui->registerZone(zone, this);
}

GxUiItemInt::GxUiItemInt(GxUI* ui, int* zone)
	: GxUiItem(ui), fZone(zone), fCache(INT_MAX)
{
	ui->registerZone(zone, this);
}

bool GxUiItemInt::hasChanged()
{
	return *fZone != fCache;
}

void GxUiItemInt::modifyZone(int v)
{
	fCache = v;
	if (*fZone != v) {
		*fZone = v;
		fGUI->updateZone(fZone);
	}
}

GxUiItemBool::GxUiItemBool(GxUI* ui, bool* zone)
	: GxUiItem(ui), fZone(zone), fCache(INT_MAX)
{
	ui->registerZone(zone, this);
}

bool GxUiItemBool::hasChanged()
{
	return *fZone != fCache;
}

void GxUiItemBool::modifyZone(bool v)
{
	fCache = v;
	if (*fZone != v) {
		*fZone = v;
		fGUI->updateZone(fZone);
	}
}

bool GxUiItemFloat::hasChanged()
{
	return *fZone != fCache;
}

// modify zone
void GxUiItemFloat::modifyZone(float v)
{
	fCache = v;
	if (*fZone != v) {
		*fZone = v;
		fGUI->updateZone(fZone);
	}
}

/* ----------------- GxUiCallbackItem stuff ---------------- */
GxUiCallbackItemFloat::GxUiCallbackItemFloat(GxUI* ui, float* zone, GxUiCallback foo, void* data)
	: GxUiItemFloat(ui, zone), fCallback(foo), fData(data) {}

// reflect zone
void GxUiCallbackItemFloat::reflectZone()
{
	float v = *fZone;
	fCache  = v;
	fCallback(v, fData);
}

} /* end of guitarix namespace */
