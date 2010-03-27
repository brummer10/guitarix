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
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <map>
#include <cstdlib>
#include <cstdio>
#include <cassert>

#include <array>
#include <zita-convolver.h>
#include <fftw3.h>
#include <zita-resampler.h>

#include <cassert>
#include <sigc++/sigc++.h>
#include <semaphore.h>

using namespace std;

#include "gx_ui.h"

namespace gx_ui
{
list<GxUI*> GxUI::fGuiList;

// constructor
GxUI::GxUI() : fStopped(false)
{
	fGuiList.push_back(this);
}

// -- registerZone(z,c) : zone management
void GxUI::registerZone(float* z, GxUiItem* c)
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
inline void GxUI::updateZone(float* z)
{
	float 	v = *z;
	clist* 	l = fZoneMap[z];
	for (clist::iterator c = l->begin(); c != l->end(); c++)
		if ((*c)->cache() != v) (*c)->reflectZone();
}

// Update all user items not up to date
inline void GxUI::updateAllZones()
{
	for (zmap::iterator m = fZoneMap.begin(); m != fZoneMap.end(); m++)
	{
		float* 	z = m->first;
		clist*	l = m->second;
		float	v = *z;
		for (clist::iterator c = l->begin(); c != l->end(); c++) {
			if ((*c)->cache() != v) (*c)->reflectZone();
		}
	}
}

// add a callback item
inline void GxUI::addCallback(float* zone, GxUiCallback foo, void* data)
{
	new GxUiCallbackItem(this, zone, foo, data);
};


/* ---------------- GxUiItem stuff --------------- */
GxUiItem::GxUiItem (GxUI* ui, float* zone)
	: fGUI(ui), fZone(zone), fCache(-123456.654321)
{
	ui->registerZone(zone, this);
}

// modify zone
void GxUiItem::modifyZone(float v)
{
	fCache = v;
	if (*fZone != v)
	{
		*fZone = v;
		fGUI->updateZone(fZone);
	}
}

// item cache
float	GxUiItem::cache()
{
	return fCache;
}

/* ----------------- GxUiCallbackItem stuff ---------------- */
GxUiCallbackItem::GxUiCallbackItem(GxUI* ui, float* zone, GxUiCallback foo, void* data)
	: GxUiItem(ui, zone), fCallback(foo), fData(data) {}

// reflect zone
void GxUiCallbackItem::reflectZone()
{
	float v = *fZone;
	fCache  = v;
	fCallback(v, fData);
}

} /* end of guitarix namespace */
