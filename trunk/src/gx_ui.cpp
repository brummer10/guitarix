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

/*
int GxUI::zone2index(float *zone)
{
	int n = 0;
	list<GxUI*>::iterator g;
	for (g = fGuiList.begin(); g != fGuiList.end(); g++)
	{
		zmap m = (*g)->fZoneMap;
		for (zmap::iterator i=m.begin(); i != m.end(); i++)
		{
			if (i->first == zone)
				return n;
			n++;
		}
	}
	assert(false);
	return -1;
}

float* GxUI::index2zone(int index)
{
	int n = 0;
	list<GxUI*>::iterator g;
	for (g = fGuiList.begin(); g != fGuiList.end(); g++)
	{
		zmap m = (*g)->fZoneMap;
		for (zmap::iterator i=m.begin(); i != m.end(); i++)
		{
			if (n == index)
				return i->first;
			n++;
		}
	}
	assert(false);
	return NULL;
}

// -- acquire current state, places it in string buffer
void GxUI::dumpStateToString(string& setting)
{
	// string containing preset data
	// will be flushed into preset file
	string space = " ";

	for (zmap::iterator i=fZoneMap.begin(); i!=fZoneMap.end(); i++)
	{
		// build buffer with ostringstream's
		ostringstream val; val << *(i->first);
		setting +=  space + val.str();
	}
}

// -- set a state by string
bool GxUI::applyStateFromString(const string& setting)
{
	if (setting.empty()) return false;

	// parse buffer
	istringstream values(setting);
	for (zmap::iterator i=fZoneMap.begin(); i!=fZoneMap.end(); i++)
		values >> *(i->first);

	return true;
}

// -- fetch state from file
void GxUI::fetchPresetStateFromFile(const char* filename,
                                    const char* presname,
                                    string& state)
{
	ifstream fa(filename);
	string buffer;

	if (fa.good())
	{
		do {
			getline(fa, buffer);
			if (!buffer.empty())
			{
				// do we have a match ?
				if ((int)buffer.find(presname) == -1) continue;

				buffer.erase(0, buffer.find(" ")+1);
				break;
			}
		}
		while (buffer != "");
		fa.close();
	}

	state = buffer;
}

// -- recall a preset setting by name
bool GxUI::recallPresetByname(const char* filename, const char* presname)
{
	string buffer;

	// lookup preset file until we find a match
	fetchPresetStateFromFile(filename, presname, buffer);

	// set the found state
	return applyStateFromString(buffer);
}

// -- recall a preset setting by name
bool GxUI::renamePreset(const char* filename, const char* oldname, const char* newname)
{
	string buffer, buf, space = " ";

	const string prefile = filename;
	const string tmpfile = prefile + "_tmp";

	// lookup preset file until we find a match
	fetchPresetStateFromFile(filename, oldname, buffer);

	// did we find anything ? weird if not ...
	if (buffer.empty()) return false;

	// let's use a tmp file that does not contain the preset
	ostringstream cat_tmpfile("cat");
	cat_tmpfile << "cat" << space << prefile << space
	            << "| grep -v" << space << oldname << space
	            << ">" << tmpfile;

	(void)system(cat_tmpfile.str().c_str());
	usleep(200);

	// add new name
	ostringstream presline;
	presline << "echo" << space << newname << space << buffer
	         << " >> " << tmpfile;

	// save preset in tmp file
	if (system(presline.str().c_str()) != 0)
	{
		string cmd = string("rm -f ") + tmpfile;
		system(cmd.c_str());
		return false;
	}

	// rename tmp file to filename
	string cmd = string("rm -f ") + prefile; system(cmd.c_str());
	rename(tmpfile.c_str(), prefile.c_str());

	return true;
}
*/

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
		for (clist::iterator c = l->begin(); c != l->end(); c++)
			if ((*c)->cache() != v) (*c)->reflectZone();
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
