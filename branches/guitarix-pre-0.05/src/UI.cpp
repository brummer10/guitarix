/*
  * Copyright (C) 2009 Hermann Meyer and James Warden
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
*/

/******************************************************************************
*******************************************************************************

								GRAPHIC USER INTERFACE (v2)
								  abstract interfaces
	UI.cpp
	interface actions for guitarix
*******************************************************************************
*******************************************************************************/

struct uiItem;
typedef void (*uiCallback)(float val, void* data);

class UI
{
    typedef list<uiItem*> clist;
    typedef map<float*, clist*> zmap;

private:
    static list<UI*>	fGuiList;
    zmap				fZoneMap;
    bool				fStopped;

public:

    UI() : fStopped(false)
    {
        fGuiList.push_back(this);
    }

    virtual ~UI()
    {
        // suppression de this dans fGuiList
    }

    // -- registerZone(z,c) : zone management
    void registerZone(float* z, uiItem* c)
    {
        if (fZoneMap.find(z) == fZoneMap.end()) fZoneMap[z] = new clist();
        fZoneMap[z]->push_back(c);
    }

    // -- saveState(filename) : save the value of every zone to a file
    void saveState(const char* filename)
    {
      ofstream f(filename);
      for (zmap::iterator i=fZoneMap.begin(); i!=fZoneMap.end(); i++) 
	f << *(i->first) << ' ';

      f << endl;
      f.close();
    }

    // -- acquire current state, places it in string buffer
    void getState(string& setting)
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
    bool setState(const string& setting)
    {
      if (setting.empty()) return false;

      // parse buffer
      istringstream values(setting);
      for (zmap::iterator i=fZoneMap.begin(); i!=fZoneMap.end(); i++)
	values >> *(i->first);

      return true;
    }

    // -- fetch state from file
    void fetchStateFromFile(const char* filename, const char* presname, string& state)
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
    bool recallPresetByname(const char* filename, const char* presname)
    {
      string buffer;
      
      // lookup preset file until we find a match
      fetchStateFromFile(filename, presname, buffer);

      // set the found state
      return setState(buffer);
    }

    // -- recall a preset setting by name 
    bool renamePreset(const char* filename, const char* oldname, const char* newname)
    {
      string buffer, buf, space = " ";
      
      const string prefile = filename;
      const string tmpfile = prefile + "_tmp";

      // lookup preset file until we find a match
      fetchStateFromFile(filename, oldname, buffer);

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

    // -- recallState(filename) : load the value of every zone from a file
    void recallState(const char* filename)
    {
        ifstream f(filename);
        if (f.good())
        {
            for (zmap::iterator i=fZoneMap.begin(); i!=fZoneMap.end(); i++)
            {
                f >> *(i->first);
            }
        }
        f.close();
    }

    // -- recalladState(filename) : load the value of every zone for extra sets from a file
    void recalladState(const char* filename, int a, int b, int lin)
    {
        ifstream f(filename);
        int is = 0;
        string buffer;
        if (f.good())
            for (is=0; is<lin; is++)
            {
                getline(f, buffer);
            }
        is = 0;
        {
            for (zmap::iterator i=fZoneMap.begin(); i!=fZoneMap.end(); i++)
            {
                if ((is>a) && ( is<b))  f >> *(i->first);
                is++;
            }
        }
        f.close();
    }

    void updateAllZones();

    void updateZone(float* z);

    static void updateAllGuis()
    {
        list<UI*>::iterator g;
        for (g = fGuiList.begin(); g != fGuiList.end(); g++)
        {
            (*g)->updateAllZones();
        }
    }

    // -- retrieve loggin window
    virtual GtkTextView* const getLoggingWindow() const { return NULL; }

    // -- active widgets
    virtual void addMenu() {};
    virtual void addButton(const char* label, float* zone) {};
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
    virtual void addtoggle(const char* label, float* zone){};
    virtual void addswitch(const char* label, float* zone){};
    virtual void addminiswitch(const char* label, float* zone){};
    virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step) {};
    virtual void addNumDisplay(const char* label, float* zone) {};
    virtual void addLiveWaveDisplay(const char* label, float* zone , float* zone1) {};
    virtual void addStatusDisplay(const char* label, float* zone ) {};
    virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max){};
    virtual void addVerticalBargraph(const char* label, float* zone, float min, float max){};

    void addCallback(float* zone, uiCallback foo, void* data);

    // -- widget's layouts
    virtual void openFrameBox(const char* label) {};
    virtual void openHorizontalBox(const char* label) {};
    virtual void openVerticalBox(const char* label) {};
    virtual void openVerticalBox1(const char* label) {};
    virtual void openVerticalMidiBox(const char* label) {};
    virtual void openDialogBox(const char* label, float* zone) {};
    virtual void openWarningBox(const char* label, float* zone){};
    virtual void openEventBox(const char* label) {};
    virtual void openHandleBox(const char* label) {};
    virtual void openExpanderBox(const char* label, float* zone) {};
    virtual void openTabBox(const char* label) {};
    virtual void openTextLoggingBox(const char* label) {};
    virtual void closeBox() {};

    virtual void show() {};
    virtual void run() {};

    void stop()
    {
        fStopped = true;
    }
    bool stopped()
    {
        return fStopped;
    }

    virtual void declare(float* zone, const char* key, const char* value) {}
};

/**
 * User Interface Item: abstract definition
 */


class uiItem
{
protected :

    UI*		fGUI;
    float*		fZone;
    float		fCache;

    uiItem (UI* ui, float* zone) : fGUI(ui), fZone(zone), fCache(-123456.654321)
    {
        ui->registerZone(zone, this);
    }

public :
    virtual ~uiItem() {}

    void modifyZone(float v)
    {
        fCache = v;
        if (*fZone != v)
        {
            *fZone = v;
            fGUI->updateZone(fZone);
        }
    }

    float			cache()
    {
        return fCache;
    }
    virtual void 	reflectZone() 	= 0;
};


/**
 * Callback Item
 */

struct uiCallbackItem : public uiItem
{
    uiCallback	fCallback;
    void*		fData;

    uiCallbackItem(UI* ui, float* zone, uiCallback foo, void* data)
            : uiItem(ui, zone), fCallback(foo), fData(data) {}

    virtual void 	reflectZone()
    {
        float 	v = *fZone;
        fCache = v;
        fCallback(v, fData);
    }
};

// en cours d'installation de call back. a finir!!!!!
/**
 * Update all user items reflecting zone z
 */

inline void UI::updateZone(float* z)
{
    float 	v = *z;
    clist* 	l = fZoneMap[z];
    for (clist::iterator c = l->begin(); c != l->end(); c++)
    {
        if ((*c)->cache() != v) (*c)->reflectZone();
    }
}

/**
 * Update all user items not up to date
 */

inline void UI::updateAllZones()
{
    for (zmap::iterator m = fZoneMap.begin(); m != fZoneMap.end(); m++)
    {
        float* 	z = m->first;
        clist*	l = m->second;
        float	v = *z;
        for (clist::iterator c = l->begin(); c != l->end(); c++)
        {
            if ((*c)->cache() != v) (*c)->reflectZone();
        }
    }
}

inline void UI::addCallback(float* zone, uiCallback foo, void* data)
{
    new uiCallbackItem(this, zone, foo, data);
};



