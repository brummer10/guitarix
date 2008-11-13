/******************************************************************************
*******************************************************************************

								GRAPHIC USER INTERFACE (v2)
								  abstract interfaces

*******************************************************************************
*******************************************************************************/

#include <map>
#include <list>

using namespace std;

struct Meta : map<const char*, const char*>
{
    void declare (const char* key, const char* value)
    {
        (*this)[key]=value;
    }
};

struct uiItem;
typedef void (*uiCallback)(float val, void* data);

/**
 * Graphic User Interface : abstract definition
 */

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
        {
            f << *(i->first) << ' ';
        }
        f << endl;
        f.close();
    }

    void savepreStatebyname(const char* filename, const char* tmpname, const gchar* presname)
    {
        string buffer = " ";
        extern int cm;
        int is;
        int lin = 2;
        ifstream fa(filename);
        ofstream f(tmpname);
        if (fa.good())
        {
            std::string b(presname);
            while (buffer != "")
            {
                getline(fa, buffer);
                std::string::size_type in = buffer.find(b);
                if ((buffer != "") & (in == -1))	 f <<  buffer <<endl;
                if (in != -1) cm = 1;
            }
        }
        f <<  presname << ' ';
        for (zmap::iterator i=fZoneMap.begin(); i!=fZoneMap.end(); i++)
        {
            f << *(i->first) << ' ';
        }
        f << endl;
        fa.close();
        f.close();
        remove(filename);
        rename(tmpname, filename);
    }

    void recallpreStatebyname(const char* filename, const char* tmpname, const gchar* text)
    {
        string buffer = " ";
        string  buf;
        ifstream fa(filename);
        ofstream fr(tmpname);
        if (fa.good())
        {
            std::string b(text);
            while (buffer != "")
            {
                getline(fa, buffer);
                std::string::size_type in = buffer.find(b);
                if ((buffer != "") & (in != -1))
                {
                    in = buffer.find(" ");
                    in += 1;
                    buffer.erase(0, in);
                    buf = buffer;
                }
            }
        }
        fr <<  buf <<endl;
        fr.close();
        fa.close();
        ifstream f(tmpname);
        if (f.good())
        {
            for (zmap::iterator i=fZoneMap.begin(); i!=fZoneMap.end(); i++)
            {
                f >> *(i->first);
            }
        }
        f.close();
    }

    // -- saveState(filename) : save the value of every zone to a file
    void savepreState(const char* filename, const char* tmpname, int lin)
    {
        string buffer;
        int is;
        ifstream fa(filename);
        ofstream f(tmpname);
        if (fa.good())
        {
            for (is=0; is<lin; is++)
            {
                getline(fa, buffer);
                f <<  buffer <<endl;
            }
            getline(fa, buffer);
        }
        for (zmap::iterator i=fZoneMap.begin(); i!=fZoneMap.end(); i++)
        {
            f << *(i->first) << ' ';
        }
        f << endl;
        lin = lin + 1;
        for (is=lin; is<6; is++)
        {
            getline(fa, buffer);
            f <<  buffer <<endl;
        }
        fa.close();
        f.close();
        remove(filename);
        rename(tmpname, filename);
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
              if ((is>a) & ( is<b))  f >> *(i->first);
              is++;
            }
        }
        f.close();
    }

    // -- recallpreState(filename) : load the value of every zone from a file
    void recallpreState(const char* filename, int lin)
    {
        string buffer;
        ifstream f(filename);
        if (f.good())
        {
            int is;
            int in;
            for (is=0; is<lin; is++)
            {
                getline(f, buffer);
            }
            int lage;
            lage = f.tellg();
            getline(f, buffer);
            in = buffer.find(" ");
            in += 1;
            in += lage;
            f.seekg(in, ios_base::beg);
            for (zmap::iterator i=fZoneMap.begin(); i!=fZoneMap.end(); i++)
            {
                f >> *(i->first);
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

    // -- active widgets
    virtual void addMenu() {};
    virtual void addButton(const char* label, float* zone) {};
    virtual void addToggleButton(const char* label, float* zone) {};
    virtual void addPToggleButton(const char* label, float* zone) {};
    virtual void addJToggleButton(const char* label, float* zone) {};
    virtual void addCheckButton(const char* label, float* zone) {};
    virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step) {};
    virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step) {};

    void addCallback(float* zone, uiCallback foo, void* data);

    // -- widget's layouts
    virtual void openFrameBox(const char* label) {};
    virtual void openHorizontalBox(const char* label) {};
    virtual void openVerticalBox(const char* label) {};
    virtual void openDialogBox(const char* label, float* zone) {};
    virtual void openEventBox(const char* label) {};
    virtual void openHandleBox(const char* label) {};
    virtual void openExpanderBox(const char* label, float* zone) {};
    virtual void closeBox() {};

 /*    virtual void setReset(float* zone1, float init1,  float* zone2, float init2, float* zone3, float init3, float* zone4, float init4, float* zone5, float init5, float* zone6, float init6, float* zone7, float init7, float* zone8, float init8, float* zone9, float init9, float* zone10, float init10, float* zone11, float init11) {};*/

    virtual void show() {};
    virtual void run() {};
    virtual void run_nogui() {};

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


/******************************************************************************
*******************************************************************************

								GRAPHIC USER INTERFACE
								  gtk interface

*******************************************************************************
*******************************************************************************/

#include <gtk/gtk.h>

#define stackSize 256

// Insertion modes
#define kSingleMode 0
#define kBoxMode 1
#define kTabMode 2

class GTKUI : public UI
{
private :
    static bool			fInitialized;
    static list<UI*>	fGuiList;

protected :
    //GtkWidget* 	fWindow;
    int			fTop;
    GtkWidget* 	fBox[stackSize];
    int 		fMode[stackSize];
    bool		fStopped;

    GtkWidget* addWidget(const char* label, GtkWidget* w);
     virtual void pushBox(int mode, GtkWidget* w);

public :

    static const gboolean expand = TRUE;
    static const gboolean fill = TRUE;
    static const gboolean homogene = FALSE;

    GTKUI(char * name, int* pargc, char*** pargv);

    // -- layout groups
    virtual void openFrameBox(const char* label);
    virtual void openHorizontalBox(const char* label = "");
    virtual void openVerticalBox(const char* label = "");
    virtual void openDialogBox(const char* label, float* zone);
    virtual void openEventBox(const char* label = "");
    virtual void openHandleBox(const char* label = "");
    virtual void openExpanderBox(const char* label, float* zone);
    virtual void closeBox();

    // -- active widgets
    virtual void addMenu();
    virtual void addButton(const char* label, float* zone);
    virtual void addToggleButton(const char* label, float* zone);
    virtual void addPToggleButton(const char* label, float* zone);
    virtual void addJToggleButton(const char* label, float* zone);
    virtual void addCheckButton(const char* label, float* zone);
    virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step);
    virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step);

/*     virtual void setReset(float* zone1, float init1,  float* zone2, float init2, float* zone3, float init3, float* zone4, float init4, float* zone5, float init5, float* zone6, float init6, float* zone7, float init7, float* zone8, float init8, float* zone9, float init9, float* zone10, float init10, float* zone11, float init11); */

    virtual void show();
    virtual void run();
    virtual void run_nogui();

};

