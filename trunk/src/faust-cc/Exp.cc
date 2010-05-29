namespace Exp {
// generated from file '../src/faust/Exp.dsp'

//-----------------------------------------------------
//
// Code generated with Faust 0.9.24 (http://faust.grame.fr)
//-----------------------------------------------------
/* link with  */
template <int N> inline float faustpower(float x) 		{ return powf(x,N); } 
template <int N> inline double faustpower(double x) 	{ return pow(x,N); }
template <int N> inline int faustpower(int x) 			{ return faustpower<N/2>(x) * faustpower<N-N/2>(x); } 
template <> 	 inline int faustpower<0>(int x) 		{ return 1; }
template <> 	 inline int faustpower<1>(int x) 		{ return x; }
/*
** most of this file is a copy of faust architecture/jack-gtk.cpp
** which is licensed under GPL V2.
*/

struct Meta : map<const char*, const char*>
{
	void declare (const char* key, const char* value) { (*this)[key]=value; }
};



#define max(x,y) (((x)>(y)) ? (x) : (y))
#define min(x,y) (((x)<(y)) ? (x) : (y))


// abs is now predefined
//template<typename T> T abs (T a)			{ return (a<T(0)) ? -a : a; }


inline int		lsr (int x, int n)			{ return int(((unsigned int)x) >> n); }

inline int 		int2pow2 (int x)	        { int r=0; while ((1<<r)<x) r++; return r; }

/******************************************************************************
*******************************************************************************

							       VECTOR INTRINSICS

*******************************************************************************
*******************************************************************************/









/******************************************************************************
*******************************************************************************

								GRAPHIC USER INTERFACE (v2)
								  abstract interfaces

*******************************************************************************
*******************************************************************************/

struct uiItem;
typedef void (*uiCallback)(float val, void* data);

/**
 * Graphic User Interface : abstract definition
 */

class UI
{
	typedef list<uiItem*> clist;
	typedef map<float*, clist*> zmap;

protected:
	static list<UI*>	fGuiList;
	zmap				fZoneMap;

public:

	UI() {
		fGuiList.push_back(this);
	}

	virtual ~UI() {
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

			for (zmap::iterator i=fZoneMap.begin(); i!=fZoneMap.end(); i++) {
				f << *(i->first) << ' ';
			}

			f << endl;
			f.close();
		}

	// -- recallState(filename) : load the value of every zone from a file

	void recallState(const char* filename)
		{
			ifstream f(filename);
			if (f.good()) {
				for (zmap::iterator i=fZoneMap.begin(); i!=fZoneMap.end(); i++) {
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
			for (g = fGuiList.begin(); g != fGuiList.end(); g++) {
				(*g)->updateAllZones();
			}
		}

	// -- active widgets

	virtual void addButton(const char* label, float* zone) = 0;
	virtual void addToggleButton(const char* label, float* zone) = 0;
	virtual void addCheckButton(const char* label, float* zone) = 0;
	virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step) = 0;
	virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step) = 0;
	virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step) = 0;

	// -- passive widgets

	virtual void addNumDisplay(const char* label, float* zone, int precision) = 0;
	virtual void addTextDisplay(const char* label, float* zone, const char* names[], float min, float max) = 0;
	virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max) = 0;
	virtual void addVerticalBargraph(const char* label, float* zone, float min, float max) = 0;

	void addCallback(float* zone, uiCallback foo, void* data);

	// -- widget's layouts

	virtual void openFrameBox(const char* label) = 0;
	virtual void openTabBox(const char* label) = 0;
	virtual void openHorizontalBox(const char* label) = 0;
	virtual void openVerticalBox(const char* label) = 0;

	// -- extra widget's layouts

	virtual void openDialogBox(const char* label, float* zone) = 0;
	virtual void openEventBox(const char* label) = 0;
	virtual void openHandleBox(const char* label) = 0;
	virtual void openExpanderBox(const char* label, float* zone) = 0;

	virtual void closeBox() = 0;

	virtual void run() {};

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
			if (*fZone != v) {
				*fZone = v;
				fGUI->updateZone(fZone);
			}
		}

	float			cache()			{ return fCache; }
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

	virtual void 	reflectZone() {
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
	for (clist::iterator c = l->begin(); c != l->end(); c++) {
		if ((*c)->cache() != v) (*c)->reflectZone();
	}
}


/**
 * Update all user items not up to date
 */

inline void UI::updateAllZones()
{
	for (zmap::iterator m = fZoneMap.begin(); m != fZoneMap.end(); m++) {
		float* 	z = m->first;
		clist*	l = m->second;
		float	v = *z;
		for (clist::iterator c = l->begin(); c != l->end(); c++) {
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


#define stackSize 256

// Insertion modes

#define kSingleMode 0
#define kBoxMode 1
#define kTabMode 2

/**
 * rmWhiteSpaces(): Remove the leading and trailing white spaces of a string
 * (but not those in the middle of the string)
 */
static string rmWhiteSpaces(const string& s)
{
	size_t i = s.find_first_not_of(" \t");
	size_t j = s.find_last_not_of(" \t");

	if (i != string::npos && j != string::npos) {
		return s.substr(i, 1+j-i);
	} else {
		return "";
	}
}


/**
 * Extracts metdata from a label : 'vol [unit: dB]' -> 'vol' + metadata
 */
static void extractMetadata(const string& fulllabel, string& label, map<string, string>& metadata)
{
	enum {kLabel, kEscape1, kEscape2, kEscape3, kKey, kValue};
	int state = kLabel; int deep = 0;
	string key, value;

	for (unsigned int i=0; i < fulllabel.size(); i++) {
		char c = fulllabel[i];
		switch (state) {
		case kLabel :
			assert (deep == 0);
			switch (c) {
			case '\\' : state = kEscape1; break;
			case '[' : state = kKey; deep++; break;
			default : label += c;
			}
			break;

		case kEscape1 :
			label += c;
			state = kLabel;
			break;

		case kEscape2 :
			key += c;
			state = kKey;
			break;

		case kEscape3 :
			value += c;
			state = kValue;
			break;

		case kKey :
			assert (deep > 0);
			switch (c) {
			case '\\' :  state = kEscape2;
				break;

			case '[' :  deep++;
				key += c;
				break;

			case ':' :  if (deep == 1) {
					state = kValue;
				} else {
					key += c;
				}
				break;
			case ']' :  deep--;
				if (deep < 1) {
					metadata[rmWhiteSpaces(key)] = "";
					state = kLabel;
					key="";
					value="";
				} else {
					key += c;
				}
				break;
			default :   key += c;
			}
			break;

		case kValue :
			assert (deep > 0);
			switch (c) {
			case '\\' : state = kEscape3;
				break;

			case '[' :  deep++;
				value += c;
				break;

			case ']' :  deep--;
				if (deep < 1) {
					metadata[rmWhiteSpaces(key)]=rmWhiteSpaces(value);
					state = kLabel;
					key="";
					value="";
				} else {
					value += c;
				}
				break;
			default :   value += c;
			}
			break;

		default :
			cerr << "ERROR unrecognized state " << state << endl;
		}
	}
	label = rmWhiteSpaces(label);
}


class GTKUI : public UI
{
private :
	static list<UI*>                    fGuiList;
	static map<float*, float>           fGuiSize;       // map widget zone with widget size coef
	static map<float*, string>          fTooltip;       // map widget zone with tooltip strings

protected :
	int         fTop;
	GtkWidget*  fBox[stackSize];
	int         fMode[stackSize];

	GtkWidget* addWidget(const char* label, GtkWidget* w);
	virtual void pushBox(int mode, GtkWidget* w);


public :

	static const gboolean expand = TRUE;
	static const gboolean fill = TRUE;
	static const gboolean homogene = FALSE;

	GTKUI(GtkWidget *window);

	// -- Labels and metadata

	virtual void declare (float* zone, const char* key, const char* value);
	virtual int  checkLabelOptions (GtkWidget* widget, const string& fullLabel, string& simplifiedLabel);
	virtual void checkForTooltip (float* zone, GtkWidget* widget);

	// -- layout groups

	virtual void openFrameBox(const char* label);
	virtual void openTabBox(const char* label = "");
	virtual void openHorizontalBox(const char* label = "");
	virtual void openVerticalBox(const char* label = "");

	// -- extra widget's layouts

	virtual void openDialogBox(const char* label, float* zone);
	virtual void openEventBox(const char* label = "");
	virtual void openHandleBox(const char* label = "");
	virtual void openExpanderBox(const char* label, float* zone);

	virtual void closeBox();
	virtual void adjustStack(int n);

	// -- active widgets

	virtual void addButton(const char* label, float* zone);
	virtual void addToggleButton(const char* label, float* zone);
	virtual void addCheckButton(const char* label, float* zone);
	virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step);
	virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step);
	virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step);

	// -- passive display widgets

	virtual void addNumDisplay(const char* label, float* zone, int precision);
	virtual void addTextDisplay(const char* label, float* zone, const char* names[], float min, float max);
	virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max);
	virtual void addVerticalBargraph(const char* label, float* zone, float min, float max);

	virtual void run();

};



/******************************************************************************
*******************************************************************************

                                GRAPHIC USER INTERFACE (v2)
                                  gtk implementation

*******************************************************************************
*******************************************************************************/

// global static fields

list<UI*>                   UI::fGuiList;

map<float*, float>          GTKUI::fGuiSize;
map<float*, string>         GTKUI::fTooltip;

GTKUI::GTKUI(GtkWidget *window)
{
	fTop = 0;
	fBox[fTop] = gtk_vbox_new (homogene, 4);
	fMode[fTop] = kBoxMode;
	gtk_container_add (GTK_CONTAINER (window), fBox[fTop]);
}

// empilement des boites

void GTKUI::pushBox(int mode, GtkWidget* w)
{
	++fTop;
	assert(fTop < stackSize);
	fMode[fTop]     = mode;
	fBox[fTop]      = w;
}


/**
 * Remove n levels from the stack S before the top level
 * adjustStack(n): S -> S' with S' = S(0),S(n+1),S(n+2),...
 */
void GTKUI::adjustStack(int n)
{
	if (n > 0) {
		assert(fTop >= n);

		fTop -= n;
		fMode[fTop] = fMode[fTop+n];
		fBox[fTop]  = fBox[fTop+n];
	}
}

void GTKUI::closeBox()
{
	--fTop;
	assert(fTop >= 0);
}


/**
 * Analyses the widget zone metadata declarations and takes
 * appropriate actions
 */
void GTKUI::declare(float* zone, const char* key, const char* value)
{
	if (strcmp(key,"size")==0) {
		fGuiSize[zone]=atof(value);
	}
	else if (strcmp(key,"tooltip")==0) {
		fTooltip[zone] = value ;
	}
}



/**
 * Analyses a full label and activates the relevant options. returns a simplified
 * label (without options) and an amount of stack adjustement (in case additional
 * containers were pushed on the stack).
 */

int GTKUI::checkLabelOptions(GtkWidget* widget, const string& fullLabel, string& simplifiedLabel)
{
	map<string, string> metadata;
	extractMetadata(fullLabel, simplifiedLabel, metadata);

	if (metadata.count("tooltip")) {
		gtk_tooltips_set_tip (gtk_tooltips_new (), widget, metadata["tooltip"].c_str(), NULL);
	}
	if (metadata["option"] == "detachable") {
		openHandleBox(simplifiedLabel.c_str());
		return 1;
	}

	// no adjustement of the stack needed
	return 0;
}

/**
 * Check if a tooltip is associated to a zone and add it to the corresponding widget
 */
void GTKUI::checkForTooltip(float* zone, GtkWidget* widget)
{
	if (fTooltip.count(zone)) {
		gtk_tooltips_set_tip (gtk_tooltips_new (), widget, fTooltip[zone].c_str(), NULL);
	}
}


// les differentes boites

void GTKUI::openFrameBox(const char* label)
{
	GtkWidget * box = gtk_frame_new (label);
	//gtk_container_set_border_width (GTK_CONTAINER (box), 10);

	pushBox(kSingleMode, addWidget(label, box));
}


void GTKUI::openTabBox(const char* fullLabel)
{
	string  label;
	GtkWidget* widget = gtk_notebook_new();

	int     adjust = checkLabelOptions(widget, fullLabel, label);

	pushBox(kTabMode, addWidget(label.c_str(), widget));

	// adjust stack because otherwise Handlebox will remain open
	adjustStack(adjust);
}


void GTKUI::openHorizontalBox(const char* fullLabel)
{
	string   label;
	GtkWidget* box = gtk_hbox_new (homogene, 4);
	int     adjust = checkLabelOptions(box, fullLabel, label);

	gtk_container_set_border_width (GTK_CONTAINER (box), 10);

	if (fMode[fTop] != kTabMode && label[0] != 0) {
		GtkWidget * frame = addWidget(label.c_str(), gtk_frame_new (label.c_str()));
		gtk_container_add (GTK_CONTAINER(frame), box);
		gtk_widget_show(box);
		pushBox(kBoxMode, box);
	} else {
		pushBox(kBoxMode, addWidget(label.c_str(), box));
	}

	// adjust stack because otherwise Handlebox will remain open
	adjustStack(adjust);
}


void GTKUI::openVerticalBox(const char* fullLabel)
{
	string  label;
	GtkWidget * box = gtk_vbox_new (homogene, 4);
	int      adjust = checkLabelOptions(box, fullLabel, label);

	gtk_container_set_border_width (GTK_CONTAINER (box), 10);
	g_signal_connect(box, "expose-event", G_CALLBACK(gx_cairo::box9_expose), NULL);

	if (fMode[fTop] != kTabMode && label[0] != 0) {
		GtkWidget * frame = addWidget(label.c_str(), gtk_frame_new (label.c_str()));
		gtk_container_add (GTK_CONTAINER(frame), box);
		gtk_widget_show(box);
		pushBox(kBoxMode, box);
	} else {
		pushBox(kBoxMode, addWidget(label.c_str(), box));
	}

	// adjust stack because otherwise Handlebox will remain open
	adjustStack(adjust);
}


void GTKUI::openHandleBox(const char* label)
{
	GtkWidget * box = gtk_hbox_new (homogene, 4);
	gtk_container_set_border_width (GTK_CONTAINER (box), 2);
	if (fMode[fTop] != kTabMode && label[0] != 0)
	{
		GtkWidget * frame = addWidget(label, gtk_handle_box_new ());
		gtk_container_add (GTK_CONTAINER(frame), box);
		gtk_widget_show(box);
		pushBox(kBoxMode, box);
	}
	else
	{
		pushBox(kBoxMode, addWidget(label, box));
	}
}


void GTKUI::openEventBox(const char* label)
{
	GtkWidget * box = gtk_hbox_new (homogene, 4);
	gtk_container_set_border_width (GTK_CONTAINER (box), 2);
	if (fMode[fTop] != kTabMode && label[0] != 0)
	{
		GtkWidget * frame = addWidget(label, gtk_event_box_new ());
		gtk_container_add (GTK_CONTAINER(frame), box);
		gtk_widget_show(box);
		pushBox(kBoxMode, box);
	}
	else
	{
		pushBox(kBoxMode, addWidget(label, box));
	}
}


struct uiExpanderBox : public uiItem
{
	GtkExpander* fButton;
	uiExpanderBox(UI* ui, float* zone, GtkExpander* b) : uiItem(ui, zone), fButton(b) {}
	static void expanded (GtkWidget *widget, gpointer data)
		{
			float   v = gtk_expander_get_expanded  (GTK_EXPANDER(widget));
			if (v == 1.000000)
			{
				v = 0;
			}
			else v = 1;
			((uiItem*)data)->modifyZone(v);
		}

	virtual void reflectZone()
		{
			float   v = *fZone;
			fCache = v;
			gtk_expander_set_expanded(GTK_EXPANDER(fButton), v);
		}
};

void GTKUI::openExpanderBox(const char* label, float* zone)
{
	*zone = 0.0;
	GtkWidget * box = gtk_hbox_new (homogene, 4);
	gtk_container_set_border_width (GTK_CONTAINER (box), 2);
	if (fMode[fTop] != kTabMode && label[0] != 0)
	{
		GtkWidget * frame = addWidget(label, gtk_expander_new (label));
		gtk_container_add (GTK_CONTAINER(frame), box);
		uiExpanderBox* c = new uiExpanderBox(this, zone, GTK_EXPANDER(frame));
		gtk_signal_connect (GTK_OBJECT (frame), "activate", GTK_SIGNAL_FUNC (uiExpanderBox::expanded), (gpointer)c);
		gtk_widget_show(box);
		pushBox(kBoxMode, box);
	}
	else
	{
		pushBox(kBoxMode, addWidget(label, box));
	}
}



GtkWidget* GTKUI::addWidget(const char* label, GtkWidget* w)
{
	switch (fMode[fTop]) {
	case kSingleMode    : gtk_container_add (GTK_CONTAINER(fBox[fTop]), w);                             break;
	case kBoxMode       : gtk_box_pack_start (GTK_BOX(fBox[fTop]), w, expand, fill, 0);                 break;
	case kTabMode       : gtk_notebook_append_page (GTK_NOTEBOOK(fBox[fTop]), w, gtk_label_new(label)); break;
	}
	gtk_widget_show (w);
	return w;
}

// --------------------------- Press button ---------------------------

struct uiButton : public uiItem
{
	GtkButton*  fButton;

	uiButton (UI* ui, float* zone, GtkButton* b) : uiItem(ui, zone), fButton(b) {}

	static void pressed( GtkWidget *widget, gpointer   data )
		{
			uiItem* c = (uiItem*) data;
			c->modifyZone(1.0);
		}

	static void released( GtkWidget *widget, gpointer   data )
		{
			uiItem* c = (uiItem*) data;
			c->modifyZone(0.0);
		}

	virtual void reflectZone()
		{
			float   v = *fZone;
			fCache = v;
			if (v > 0.0) gtk_button_pressed(fButton); else gtk_button_released(fButton);
		}
};

void GTKUI::addButton(const char* label, float* zone)
{
	*zone = 0.0;
	GtkWidget*  button = gtk_button_new_with_label (label);
	addWidget(label, button);

	uiButton* c = new uiButton(this, zone, GTK_BUTTON(button));

	gtk_signal_connect (GTK_OBJECT (button), "pressed", GTK_SIGNAL_FUNC (uiButton::pressed), (gpointer) c);
	gtk_signal_connect (GTK_OBJECT (button), "released", GTK_SIGNAL_FUNC (uiButton::released), (gpointer) c);

	checkForTooltip(zone, button);
}

// ---------------------------  Toggle Buttons ---------------------------

struct uiToggleButton : public uiItem
{
	GtkToggleButton* fButton;

	uiToggleButton(UI* ui, float* zone, GtkToggleButton* b) : uiItem(ui, zone), fButton(b) {}

	static void toggled (GtkWidget *widget, gpointer data)
		{
			float   v = (GTK_TOGGLE_BUTTON (widget)->active) ? 1.0 : 0.0;
			((uiItem*)data)->modifyZone(v);
		}

	virtual void reflectZone()
		{
			float   v = *fZone;
			fCache = v;
			gtk_toggle_button_set_active(fButton, v > 0.0);
		}
};

void GTKUI::addToggleButton(const char* label, float* zone)
{
	*zone = 0.0;
	GtkWidget*  button = gtk_toggle_button_new_with_label (label);
	addWidget(label, button);

	uiToggleButton* c = new uiToggleButton(this, zone, GTK_TOGGLE_BUTTON(button));
	gtk_signal_connect (GTK_OBJECT (button), "toggled", GTK_SIGNAL_FUNC (uiToggleButton::toggled), (gpointer) c);

	checkForTooltip(zone, button);
}



void show_dialog(GtkWidget *widget, gpointer data)
{
	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(widget)) == TRUE)
	{
		gtk_widget_show(GTK_WIDGET(data));
		gint root_x, root_y;
		gtk_window_get_position (GTK_WINDOW(data), &root_x, &root_y);
		root_y -= 120;
		gtk_window_move(GTK_WINDOW(data), root_x, root_y);
	}
	else gtk_widget_hide(GTK_WIDGET(data));
}

static gboolean deleteevent( GtkWidget *widget, gpointer   data )
{
	return TRUE;
}

void GTKUI::openDialogBox(const char* label, float* zone)
{
	// create toplevel window and set properties
	GtkWidget * dialog = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_decorated(GTK_WINDOW(dialog), TRUE);
	gtk_window_set_deletable(GTK_WINDOW(dialog), FALSE);
	gtk_window_set_resizable(GTK_WINDOW(dialog), FALSE);
	gtk_window_set_gravity(GTK_WINDOW(dialog), GDK_GRAVITY_SOUTH);
	//##FIXME gtk_window_set_transient_for (GTK_WINDOW(dialog), GTK_WINDOW(fWindow));
	gtk_window_set_position (GTK_WINDOW(dialog), GTK_WIN_POS_MOUSE);
	gtk_window_set_keep_below (GTK_WINDOW(dialog), FALSE);
	gtk_window_set_title (GTK_WINDOW (dialog), label);
	g_signal_connect (G_OBJECT (dialog), "delete_event", G_CALLBACK (deleteevent), NULL);
	gtk_window_set_destroy_with_parent(GTK_WINDOW(dialog), TRUE);

	GtkWidget * box = gtk_hbox_new (homogene, 4);

	*zone = 0.0;
	GtkWidget*  button = gtk_toggle_button_new ();
	gtk_signal_connect (GTK_OBJECT (button), "toggled", GTK_SIGNAL_FUNC (show_dialog), (gpointer) dialog);

	gtk_container_add (GTK_CONTAINER(fBox[fTop]), button);
	gtk_container_add (GTK_CONTAINER(dialog), box);
	gtk_widget_show (button);
	gtk_widget_show(box);
	pushBox(kBoxMode, box);
}

// ---------------------------  Adjustmenty based widgets ---------------------------

struct uiAdjustment : public uiItem
{
	GtkAdjustment* fAdj;

	uiAdjustment(UI* ui, float* zone, GtkAdjustment* adj) : uiItem(ui, zone), fAdj(adj) {}

	static void changed (GtkWidget *widget, gpointer data)
		{
			float   v = GTK_ADJUSTMENT (widget)->value;
			((uiItem*)data)->modifyZone(v);
		}

	virtual void reflectZone()
		{
			float   v = *fZone;
			fCache = v;
			gtk_adjustment_set_value(fAdj, v);
		}
};

static int precision(double n)
{
	if (n < 0.009999) return 3;
	else if (n < 0.099999) return 2;
	else if (n < 0.999999) return 1;
	else return 0;
}

struct uiValueDisplay : public uiItem
{
	GtkLabel* fLabel;
	int	fPrecision ;

	uiValueDisplay(UI* ui, float* zone, GtkLabel* label, int precision)
		: uiItem(ui, zone), fLabel(label), fPrecision(precision) {}

	virtual void reflectZone()
		{
			float v = *fZone;
			fCache = v;
			char s[64];
			if (fPrecision <= 0)
				snprintf(s, 63, "%d", int(v));

			else if (fPrecision > 3)
				snprintf(s, 63, "%f", v);

			else if (fPrecision == 1)
			{
				const char* format[] = {"%.1f", "%.2f", "%.3f"};
				snprintf(s, 63, format[1-1], v);
			}
			else if (fPrecision == 2)
			{
				const char* format[] = {"%.1f", "%.2f", "%.3f"};
				snprintf(s, 63, format[2-1], v);
			}
			else
			{
				const char* format[] = {"%.1f", "%.2f", "%.3f"};
				snprintf(s, 63, format[3-1], v);
			}
			gtk_label_set_text(fLabel, s);
		}
};

// ---------------------------  Check Button ---------------------------

struct uiCheckButton : public uiItem
{
	GtkToggleButton* fButton;

	uiCheckButton(UI* ui, float* zone, GtkToggleButton* b) : uiItem(ui, zone), fButton(b) {}

	static void toggled (GtkWidget *widget, gpointer data)
		{
			float   v = (GTK_TOGGLE_BUTTON (widget)->active) ? 1.0 : 0.0;
			((uiItem*)data)->modifyZone(v);
		}

	virtual void reflectZone()
		{
			float   v = *fZone;
			fCache = v;
			gtk_toggle_button_set_active(fButton, v > 0.0);
		}
};

void GTKUI::addCheckButton(const char* label, float* zone)
{
	GtkObject* adj = gtk_adjustment_new(0, 0, 1, 1, 10*1, 0);
	uiAdjustment* c = new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));
	g_signal_connect (GTK_OBJECT (adj), "value-changed", G_CALLBACK (uiAdjustment::changed), (gpointer) c);
	GtkRegler myGtkRegler;
	GtkWidget* slider = myGtkRegler.gtk_mini_toggle_new_with_adjustment(GTK_ADJUSTMENT(adj));

	GtkWidget* lw = gtk_label_new(label);
	gtk_widget_set_name (lw,"effekt_label");

	GtkStyle *style = gtk_widget_get_style(lw);
	pango_font_description_set_size(style->font_desc, 8*PANGO_SCALE);
	pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_NORMAL);
	gtk_widget_modify_font(lw, style->font_desc);
	openHorizontalBox("");
	addWidget(label, slider);
	addWidget(label, lw);
	closeBox();
	checkForTooltip(zone, slider);
}


// -------------------------- Vertical Slider -----------------------------------

void GTKUI::addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step)
{
	*zone = init;
	GtkObject* adj = gtk_adjustment_new(init, min, max, step, 10*step, 0);
	uiAdjustment* c = new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));
	g_signal_connect (GTK_OBJECT (adj), "value-changed", G_CALLBACK (uiAdjustment::changed), (gpointer) c);
	GtkWidget* lw = gtk_label_new("");
	GtkWidget* lwl = gtk_label_new(label);
	gtk_widget_set_name (lw,"value_label");
	gtk_widget_set_name (lwl,"effekt_label");
	GtkStyle *style = gtk_widget_get_style(lw);
	pango_font_description_set_size(style->font_desc, 8*PANGO_SCALE);
	pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_NORMAL);
	gtk_widget_modify_font(lw, style->font_desc);
	gtk_widget_modify_font(lwl, style->font_desc);
	new uiValueDisplay(this, zone, GTK_LABEL(lw),precision(step));
	GtkRegler myGtkRegler;
	GtkWidget* slider = myGtkRegler.gtk_regler_new_with_adjustment(GTK_ADJUSTMENT(adj));

	gtk_range_set_inverted (GTK_RANGE(slider), TRUE);
	openVerticalBox("");
	addWidget(label, lwl);
	addWidget(label, slider);
	addWidget(label, lw);
	closeBox();
	checkForTooltip(zone, slider);
}

// -------------------------- Horizontal Slider -----------------------------------

void GTKUI::addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step)
{
	*zone = init;
	GtkObject* adj = gtk_adjustment_new(init, min, max, step, 10*step, 0);

	uiAdjustment* c = new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));

	gtk_signal_connect (GTK_OBJECT (adj), "value-changed", GTK_SIGNAL_FUNC (uiAdjustment::changed), (gpointer) c);

	GtkWidget* slider = gtk_hscale_new (GTK_ADJUSTMENT(adj));
	gtk_scale_set_digits(GTK_SCALE(slider), precision(step));
	float size = 160 * pow(2, fGuiSize[zone]);
	gtk_widget_set_usize(slider, size, -1);

	if (label && label[0]!=0) {
		openFrameBox(label);
		addWidget(label, slider);
		closeBox();
	} else {
		addWidget(label, slider);
	}

	checkForTooltip(zone, slider);
}


// ------------------------------ Num Entry -----------------------------------

void GTKUI::addNumEntry(const char* label, float* zone, float init, float min, float max, float step)
{
	*zone = init;
	GtkObject* adj = gtk_adjustment_new(init, min, max, step, 10*step, step);

	uiAdjustment* c = new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));

	gtk_signal_connect (GTK_OBJECT (adj), "value-changed", GTK_SIGNAL_FUNC (uiAdjustment::changed), (gpointer) c);

	GtkWidget* spinner = gtk_spin_button_new (GTK_ADJUSTMENT(adj), 0.005, precision(step));

	//gtk_widget_set_usize(slider, 160, -1);
	openFrameBox(label);
	addWidget(label, spinner);
	closeBox();

	checkForTooltip(zone, spinner);
}


// ==========================   passive widgets ===============================


// ------------------------------ Progress Bar -----------------------------------

struct uiBargraph : public uiItem
{
	GtkProgressBar*     fProgressBar;
	float               fMin;
	float               fMax;

	uiBargraph(UI* ui, float* zone, GtkProgressBar* pbar, float lo, float hi)
		: uiItem(ui, zone), fProgressBar(pbar), fMin(lo), fMax(hi) {}

	float scale(float v)        { return (v-fMin)/(fMax-fMin); }

	virtual void reflectZone()
		{
			float   v = *fZone;
			fCache = v;
			gtk_progress_bar_set_fraction(fProgressBar, scale(v));
		}
};



void GTKUI::addVerticalBargraph(const char* label, float* zone, float lo, float hi)
{
	GtkWidget* pb = gtk_progress_bar_new();
	gtk_progress_bar_set_orientation(GTK_PROGRESS_BAR(pb), GTK_PROGRESS_BOTTOM_TO_TOP);
	gtk_widget_set_size_request(pb, 8, -1);
	new uiBargraph(this, zone, GTK_PROGRESS_BAR(pb), lo, hi);
	openFrameBox(label);
	addWidget(label, pb);
	closeBox();

	checkForTooltip(zone, pb);
}


void GTKUI::addHorizontalBargraph(const char* label, float* zone, float lo, float hi)
{
	GtkWidget* pb = gtk_progress_bar_new();
	gtk_progress_bar_set_orientation(GTK_PROGRESS_BAR(pb), GTK_PROGRESS_LEFT_TO_RIGHT);
	gtk_widget_set_size_request(pb, -1, 8);
	new uiBargraph(this, zone, GTK_PROGRESS_BAR(pb), lo, hi);
	openFrameBox(label);
	addWidget(label, pb);
	closeBox();

	checkForTooltip(zone, pb);
}


// ------------------------------ Num Display -----------------------------------

struct uiNumDisplay : public uiItem
{
	GtkLabel* fLabel;
	int fPrecision;

	uiNumDisplay(UI* ui, float* zone, GtkLabel* label, int precision)
		: uiItem(ui, zone), fLabel(label), fPrecision(precision) {}

	virtual void reflectZone()
		{
			float   v = *fZone;
			fCache = v;
			char s[64];
			if (fPrecision <= 0) {
				snprintf(s, 63, "%d", int(v));
			} else if (fPrecision>3) {
				snprintf(s, 63, "%f", v);
			} else {
				const char* format[] = {"%.1f", "%.2f", "%.3f"};
				snprintf(s, 63, format[fPrecision-1], v);
			}
			gtk_label_set_text(fLabel, s);
		}
};


void GTKUI::addNumDisplay(const char* label, float* zone, int precision )
{
	GtkWidget* lw = gtk_label_new("");
	new uiNumDisplay(this, zone, GTK_LABEL(lw), precision);
	openFrameBox(label);
	addWidget(label, lw);
	closeBox();

	checkForTooltip(zone, lw);
}


// ------------------------------ Text Display -----------------------------------

struct uiTextDisplay : public uiItem
{
	GtkLabel*           fLabel;
	const char**    fNames;
	float               fMin;
	float               fMax;
	int                         fNum;


	uiTextDisplay (UI* ui, float* zone, GtkLabel* label, const char* names[], float lo, float hi)
		: uiItem(ui, zone), fLabel(label), fNames(names), fMin(lo), fMax(hi)
		{
			fNum = 0;
			while (fNames[fNum] != 0) fNum++;
		}

	virtual void reflectZone()
		{
			float   v = *fZone;
			fCache = v;

			int idx = int(fNum*(v-fMin)/(fMax-fMin));

			if      (idx < 0)       idx = 0;
			else if (idx >= fNum)   idx = fNum-1;

			gtk_label_set_text(fLabel, fNames[idx]);
		}
};


void GTKUI::addTextDisplay(const char* label, float* zone, const char* names[], float lo, float hi )
{
	GtkWidget* lw = gtk_label_new("");
	new uiTextDisplay (this, zone, GTK_LABEL(lw), names, lo, hi);
	openFrameBox(label);
	addWidget(label, lw);
	closeBox();

	checkForTooltip(zone, lw);
}



/**
 * Update all user items reflecting zone z
 */

static gboolean callUpdateAllGuis(gpointer)
{
	UI::updateAllGuis();
	return TRUE;
}


void GTKUI::run()
{
	assert(fTop == 0);
	gtk_widget_show  (fBox[0]);
	gtk_timeout_add(40, callUpdateAllGuis, 0);
}


/******************************************************************************
*******************************************************************************

								FAUST DSP

*******************************************************************************
*******************************************************************************/





//----------------------------------------------------------------
//  Definition of an abstract signal processor
//----------------------------------------------------------------

class dsp {
protected:
	float fSamplingFreq;
public:
	dsp() {}
	virtual ~dsp() {}

	virtual int getNumInputs() 										= 0;
	virtual int getNumOutputs() 									= 0;
	virtual void buildUserInterface(UI* interface) 					= 0;
	virtual void init(int samplingRate) 							= 0;
	virtual void compute(int len, float** inputs, float** outputs) 	= 0;
	void setup(GtkWidget *window);
};

void dsp::setup(GtkWidget *window)
{
	GTKUI *interface = new GTKUI (window);
	buildUserInterface(interface);
	interface->run();
}

#define DSP_HAS_SETUP


//----------------------------------------------------------------------------
// 	FAUST generated code
//----------------------------------------------------------------------------

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif  

typedef long double quad;

class mydsp : public dsp{
  protected:
	FAUSTFLOAT 	fslider0;
	double 	fVec0[2];
	FAUSTFLOAT 	fslider1;
	double 	fConst0;
	double 	fRec2[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT 	fcheckbox0;
	double 	fVec1[2];
	double 	fRec1[2];
	double 	fRec0[2];
	FAUSTFLOAT 	fslider5;
	double 	fConst1;
	double 	fConst2;
	double 	fVec2[2];
	double 	fRec3[2];
	FAUSTFLOAT 	fcheckbox1;
	FAUSTFLOAT 	fslider6;
	double 	fConst3;
	double 	fVec3[2];
	double 	fRec4[2];
	FAUSTFLOAT 	fcheckbox2;
	FAUSTFLOAT 	fcheckbox3;
  public:
	static void metadata(Meta* m) 	{ 
		m->declare("filter.lib/name", "Faust Filter Library");
		m->declare("filter.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("filter.lib/copyright", "Julius O. Smith III");
		m->declare("filter.lib/version", "1.5");
		m->declare("filter.lib/license", "STK-4.3");
		m->declare("filter.lib/reference", "http://ccrma.stanford.edu/~jos/filters/");
		m->declare("effect.lib/name", "Faust Effect Library");
		m->declare("effect.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("effect.lib/copyright", "Julius O. Smith III");
		m->declare("effect.lib/version", "1.1");
		m->declare("effect.lib/license", "STK-4.3");
		m->declare("effect.lib/reference", "http://ccrma.stanford.edu/realsimple/faust_strings/");
	}

	virtual int getNumInputs() 	{ return 1; }
	virtual int getNumOutputs() 	{ return 1; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceInit(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		for (int i=0; i<2; i++) fVec0[i] = 0;
		fConst0 = (19.7 / faustpower<2>(fSamplingFreq));
		for (int i=0; i<2; i++) fRec2[i] = 0;
		for (int i=0; i<2; i++) fVec1[i] = 0;
		for (int i=0; i<2; i++) fRec1[i] = 0;
		for (int i=0; i<2; i++) fRec0[i] = 0;
		fConst1 = (3.141592653589793 * fSamplingFreq);
		fConst2 = (0.5 / fSamplingFreq);
		for (int i=0; i<2; i++) fVec2[i] = 0;
		for (int i=0; i<2; i++) fRec3[i] = 0;
		fConst3 = (3.141592653589793 / fSamplingFreq);
		for (int i=0; i<2; i++) fVec3[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
	}
	virtual void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
	virtual void buildUserInterface(UI* interface) {
		interface->openHorizontalBox("Tube [option : detachable]");
		interface->openHorizontalBox("1 Amp");
		interface->addVerticalSlider("Dist", &fslider3, 0.5, 0.0, 1.0, 0.01);
		interface->addVerticalSlider("Duty", &fslider4, 0.0, -1.0, 1.0, 0.01);
		interface->addVerticalSlider("FB", &fslider0, 0.95, 0.6, 0.99, 0.001);
		interface->addVerticalSlider("FreqT", &fslider1, 1.25e+03, 2e+02, 3e+03, 1.0);
		interface->addCheckButton("ON", &fcheckbox0);
		interface->addVerticalSlider("Qual", &fslider2, 0.5, 0.0, 1.0, 0.01);
		interface->closeBox();
		interface->openVerticalBox("2 Highpass");
		interface->addCheckButton("ON", &fcheckbox1);
		interface->addVerticalSlider("freq", &fslider5, 1.3e+02, 5e+01, 2e+02, 1.0);
		interface->closeBox();
		interface->openVerticalBox("3 Lowpass");
		interface->addCheckButton("ON", &fcheckbox2);
		interface->addVerticalSlider("freq", &fslider6, 2e+02, 1.4e+03, 8e+03, 1e+01);
		interface->closeBox();
		interface->addCheckButton("ON", &fcheckbox3);
		interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		double 	fSlow0 = fslider0;
		double 	fSlow1 = (0.7 * sqrt((1 - fSlow0)));
		double 	fSlow2 = (1 - (fConst0 * faustpower<2>(fslider1)));
		double 	fSlow3 = faustpower<9>(((1.75 * fslider2) - 1.04));
		double 	fSlow4 = (0 - fSlow3);
		double 	fSlow5 = pow(10,(4 * fslider3));
		double 	fSlow6 = (fSlow5 * fSlow4);
		double 	fSlow7 = max(-600, fSlow6);
		double 	fSlow8 = (0 - fSlow7);
		double 	fSlow9 = exp(fSlow8);
		double 	fSlow10 = (1 - fSlow9);
		double 	fSlow11 = (exp(fSlow7) * fSlow8);
		int 	iSlow12 = int((fSlow7 < -50));
		int 	iSlow13 = int((fabs(fSlow6) > 0.0001));
		double 	fSlow14 = ((iSlow13)?((iSlow12)?fSlow11:((1.0 - ((fSlow7 * fSlow9) / fSlow10)) / fSlow10)):(0.5 + (fSlow6 * (0.16666666666666666 - (0.005555555555555556 * (faustpower<2>(fSlow5) * faustpower<2>(fSlow4)))))));
		double 	fSlow15 = ((iSlow13)?((iSlow12)?fSlow11:(fSlow7 / fSlow10)):(1 + (fSlow6 * (0.5 + (0.08333333333333333 * fSlow6)))));
		double 	fSlow16 = (0.08333333333333333 * fSlow5);
		double 	fSlow17 = (1.0 / fSlow5);
		double 	fSlow18 = (fSlow5 * fSlow3);
		double 	fSlow19 = exp(fSlow18);
		double 	fSlow20 = (1.0 / fSlow18);
		double 	fSlow21 = (0 - fSlow17);
		int 	iSlow22 = int((fSlow18 > 50));
		double 	fSlow23 = (1 + (0.3068528194400547 * fslider4));
		double 	fSlow24 = (fSlow5 * fSlow23);
		double 	fSlow25 = (1.0 / fSlow23);
		int 	iSlow26 = int(fcheckbox0);
		double 	fSlow27 = (0.2 - fSlow3);
		double 	fSlow28 = (fSlow5 * fSlow27);
		double 	fSlow29 = max(-600, fSlow28);
		double 	fSlow30 = (0 - fSlow29);
		double 	fSlow31 = (0.2 * fSlow5);
		double 	fSlow32 = (0 - ((iSlow22)?((int((fSlow31 > 50)))?1e+10:((int((fSlow31 < -50)))?fSlow21:((((fSlow19 * fSlow27) / (1 - exp((0 - fSlow28)))) - fSlow3) / fSlow18))):(fSlow17 * ((((int((fabs(fSlow28) > 0.0001)))?((int((fSlow29 < -50)))?(exp(fSlow29) * fSlow30):(fSlow29 / (1 - exp(fSlow30)))):(1 + (fSlow28 * (0.5 + (0.08333333333333333 * fSlow28))))) - fSlow15) / fSlow14))));
		double 	fSlow33 = ((fSlow23 * fSlow32) - fSlow3);
		double 	fSlow34 = (fSlow5 * fSlow33);
		double 	fSlow35 = max(-600, fSlow34);
		double 	fSlow36 = (0 - fSlow35);
		double 	fSlow37 = (fSlow24 * fSlow32);
		double 	fSlow38 = (0 - (0.2 + fSlow3));
		double 	fSlow39 = (fSlow5 * fSlow38);
		double 	fSlow40 = max(-600, fSlow39);
		double 	fSlow41 = (0 - fSlow40);
		double 	fSlow42 = (0 - fSlow31);
		double 	fSlow43 = (0 - ((iSlow22)?((int((fSlow42 > 50)))?1e+10:((int((fSlow42 < -50)))?fSlow21:((((fSlow19 * fSlow38) / (1 - exp((0 - fSlow39)))) - fSlow3) / fSlow18))):(fSlow17 * ((((int((fabs(fSlow39) > 0.0001)))?((int((fSlow40 < -50)))?(exp(fSlow40) * fSlow41):(fSlow40 / (1 - exp(fSlow41)))):(1 + (fSlow39 * (0.5 + (0.08333333333333333 * fSlow39))))) - fSlow15) / fSlow14))));
		double 	fSlow44 = ((fSlow23 * fSlow43) - fSlow3);
		double 	fSlow45 = (fSlow5 * fSlow44);
		double 	fSlow46 = max(-600, fSlow45);
		double 	fSlow47 = (0 - fSlow46);
		double 	fSlow48 = (fSlow24 * fSlow43);
		double 	fSlow49 = (((iSlow22)?((int((fSlow48 > 50)))?1e+10:((int((fSlow48 < -50)))?fSlow21:(fSlow20 * ((fSlow19 * (fSlow44 / (1 - exp((0 - fSlow45))))) - fSlow3)))):(fSlow17 * ((((int((fabs(fSlow45) > 0.0001)))?((int((fSlow46 < -50)))?(exp(fSlow46) * fSlow47):(fSlow46 / (1 - exp(fSlow47)))):(1 + (fSlow5 * (fSlow44 * (0.5 + (fSlow16 * fSlow44)))))) - fSlow15) / fSlow14))) - ((iSlow22)?((int((fSlow37 > 50)))?1e+10:((int((fSlow37 < -50)))?fSlow21:(fSlow20 * ((fSlow19 * (fSlow33 / (1 - exp((0 - fSlow34))))) - fSlow3)))):(fSlow17 * ((((int((fabs(fSlow34) > 0.0001)))?((int((fSlow35 < -50)))?(exp(fSlow35) * fSlow36):(fSlow35 / (1 - exp(fSlow36)))):(1 + (fSlow5 * (fSlow33 * (0.5 + (fSlow16 * fSlow33)))))) - fSlow15) / fSlow14))));
		double 	fSlow50 = (0.4 * fSlow23);
		double 	fSlow51 = (1.0 / tan((fConst2 * (fConst1 - (6.283185307179586 * fslider5)))));
		double 	fSlow52 = (1 + fSlow51);
		double 	fSlow53 = (1.0 / fSlow52);
		double 	fSlow54 = (0 - ((fSlow51 - 1) / fSlow52));
		int 	iSlow55 = int(fcheckbox1);
		double 	fSlow56 = (1.0 / tan((fConst3 * fslider6)));
		double 	fSlow57 = (fSlow56 - 1);
		double 	fSlow58 = (1.0 / (1 + fSlow56));
		int 	iSlow59 = int(fcheckbox2);
		int 	iSlow60 = int(fcheckbox3);
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* output0 = output[0];
		for (int i=0; i<count; i++) {
			double fTemp0 = (double)input0[i];
			double fTemp1 = ((fSlow1 * fTemp0) + (fSlow0 * fRec0[1]));
			fVec0[0] = fTemp1;
			fRec2[0] = ((fVec0[0] + (fSlow2 * fRec2[1])) - fVec0[1]);
			double fTemp2 = (fRec2[0] - fSlow3);
			double fTemp3 = (fSlow5 * fTemp2);
			double fTemp4 = max(-600, fTemp3);
			double fTemp5 = (0 - fTemp4);
			double fTemp6 = (fSlow5 * fRec2[0]);
			double fTemp7 = (0 - ((iSlow22)?((int((fTemp6 > 50)))?1e+10:((int((fTemp6 < -50)))?fSlow21:(fSlow20 * ((fSlow19 * (fTemp2 / (1 - exp((0 - fTemp3))))) - fSlow3)))):(fSlow17 * ((((int((fabs(fTemp3) > 0.0001)))?((int((fTemp4 < -50)))?(exp(fTemp4) * fTemp5):(fTemp4 / (1 - exp(fTemp5)))):(1 + (fSlow5 * (fTemp2 * (0.5 + (fSlow16 * fTemp2)))))) - fSlow15) / fSlow14))));
			double fTemp8 = ((fSlow23 * fTemp7) - fSlow3);
			double fTemp9 = (fSlow5 * fTemp8);
			double fTemp10 = max(-600, fTemp9);
			double fTemp11 = (0 - fTemp10);
			double fTemp12 = (fSlow24 * fTemp7);
			double fTemp13 = ((iSlow26)?(0 - (fSlow25 * ((iSlow22)?((int((fTemp12 > 50)))?1e+10:((int((fTemp12 < -50)))?fSlow21:(fSlow20 * ((fSlow19 * (fTemp8 / (1 - exp((0 - fTemp9))))) - fSlow3)))):(fSlow17 * ((((int((fabs(fTemp9) > 0.0001)))?((int((fTemp10 < -50)))?(exp(fTemp10) * fTemp11):(fTemp10 / (1 - exp(fTemp11)))):(1 + (fSlow5 * (fTemp8 * (0.5 + (fSlow16 * fTemp8)))))) - fSlow15) / fSlow14))))):fRec2[0]);
			fVec1[0] = fTemp13;
			fRec1[0] = ((fVec1[0] + (fSlow2 * fRec1[1])) - fVec1[1]);
			fRec0[0] = fRec1[0];
			double fTemp14 = ((iSlow26)?(fSlow50 * (fRec0[0] / fSlow49)):fRec0[0]);
			double fTemp15 = (fSlow53 * fTemp14);
			fVec2[0] = fTemp15;
			fRec3[0] = ((fVec2[0] + (fSlow54 * fRec3[1])) - fVec2[1]);
			double fTemp16 = ((iSlow55)?fRec3[0]:fTemp14);
			fVec3[0] = (fSlow58 * fTemp16);
			fRec4[0] = (fVec3[1] + (fSlow58 * (fTemp16 + (fSlow57 * fRec4[1]))));
			output0[i] = (FAUSTFLOAT)((iSlow60)?((iSlow59)?fRec4[0]:fTemp16):fTemp0);
			// post processing
			fRec4[1] = fRec4[0];
			fVec3[1] = fVec3[0];
			fRec3[1] = fRec3[0];
			fVec2[1] = fVec2[0];
			fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
			fVec1[1] = fVec1[0];
			fRec2[1] = fRec2[0];
			fVec0[1] = fVec0[0];
		}
	}
};



struct DspBlock: mydsp
{
	DspBlock();
        static void static_init(int);
};

DspBlock instance;

void init(int samplingRate)
{
	instance.init(samplingRate);
}

#ifdef DSP_HAS_SETUP
void setup(GtkWidget *w)
{
	instance.setup(w);
}
#endif

DspBlock::DspBlock()
{
	registerVar("Tube.1 Amp.Dist","","S","",&fslider3,0.5,0.0,1.0,0.01);
	registerVar("Tube.1 Amp.Duty","","S","",&fslider4,0.0,-1.0,1.0,0.01);
	registerVar("Tube.1 Amp.FB","","S","",&fslider0,0.95,0.6,0.99,0.001);
	registerVar("Tube.1 Amp.FreqT","","S","",&fslider1,1.25e+03,2e+02,3e+03,1.0);
	registerVar("Tube.1 Amp.ON","","B","",&fcheckbox0,0,0,1,1);
	registerVar("Tube.1 Amp.Qual","","S","",&fslider2,0.5,0.0,1.0,0.01);
	registerVar("Tube.2 Highpass.ON","","B","",&fcheckbox1,0,0,1,1);
	registerVar("Tube.2 Highpass.freq","","S","",&fslider5,1.3e+02,5e+01,2e+02,1.0);
	registerVar("Tube.3 Lowpass.ON","","B","",&fcheckbox2,0,0,1,1);
	registerVar("Tube.3 Lowpass.freq","","S","",&fslider6,2e+02,1.4e+03,8e+03,1e+01);
	registerVar("Tube.ON","","B","",&fcheckbox3,0,0,1,1);
	registerInit(Exp::init);
#ifdef DSP_HAS_SETUP
	registerSetup(Exp::setup);
#endif
}

void compute(int len, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	FAUSTFLOAT* inputs[1] = { input0 };
	FAUSTFLOAT* outputs[1] = { output0 };
	instance.compute(len, inputs, outputs);
}

} // end namespace Exp
