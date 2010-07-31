namespace Exp {
// generated from file '../src/faust/Exp.dsp'

//-----------------------------------------------------
//
// Code generated with Faust 0.9.24 (http://faust.grame.fr)
//-----------------------------------------------------
/* link with  */
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
	g_signal_connect(box, "expose-event", G_CALLBACK(gx_cairo::tribal_box_expose), NULL);

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

class UiSwitch: uiItem, public Gxw::Switch
{
protected:
	virtual void on_toggled();
	virtual void reflectZone();
public:
	static GtkWidget *create(GTKUI& ui, const char* sw_type, float *zone)
		{
			return GTK_WIDGET((new UiSwitch(ui, sw_type, zone))->gobj());
		}
	UiSwitch(GTKUI& ui, const char *sw_type, float *zone);
};

void UiSwitch::on_toggled()
{
	modifyZone(get_active());
}

void UiSwitch::reflectZone()
{
	float v = *fZone;
	fCache = v;
	set_active(v != 0.0);
}

UiSwitch::UiSwitch(GTKUI& ui, const char *sw_type, float *zone):
	uiItem(&ui, zone),
	Gxw::Switch(sw_type)
{
	bool v = *zone != 0.0;
	set_active(v);
	show();
}

void GTKUI::addCheckButton(const char* label, float* zone)
{
	GtkWidget* slider = UiSwitch::create(*this, "minitoggle", zone);
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
	GtkWidget* slider = GTK_WIDGET((new Gxw::SmallKnob(*Glib::wrap(GTK_ADJUSTMENT(adj))))->gobj());
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
	int 	iVec0[2];
	double 	fConst0;
	FAUSTFLOAT 	fslider1;
	double 	fConst1;
	int 	iRec2[2];
	int 	iRec1[2];
	double 	fConst2;
	double 	fRec5[2];
	double 	fRec4[2];
	double 	fRec3[2];
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT 	fslider2;
	double 	fRec0[2];
	FAUSTFLOAT 	fcheckbox1;
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
		m->declare("osc.lib/name", "Faust Oscillator Library");
		m->declare("osc.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("osc.lib/copyright", "Julius O. Smith III");
		m->declare("osc.lib/version", "1.2");
		m->declare("osc.lib/license", "STK-4.3");
	}

	virtual int getNumInputs() 	{ return 1; }
	virtual int getNumOutputs() 	{ return 1; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceInit(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		for (int i=0; i<2; i++) iVec0[i] = 0;
		fConst0 = (1.0 / fSamplingFreq);
		fConst1 = (0.5 * fSamplingFreq);
		for (int i=0; i<2; i++) iRec2[i] = 0;
		for (int i=0; i<2; i++) iRec1[i] = 0;
		fConst2 = (6.283185307179586 / fSamplingFreq);
		for (int i=0; i<2; i++) fRec5[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		for (int i=0; i<2; i++) fRec3[i] = 0;
		for (int i=0; i<2; i++) fRec0[i] = 0;
	}
	virtual void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
	virtual void buildUserInterface(UI* interface) {
		interface->openHorizontalBox("test");
		interface->openHorizontalBox("tremolo");
		interface->addCheckButton("ON", &fcheckbox1);
		interface->addCheckButton("SINE", &fcheckbox0);
		interface->addVerticalSlider("depth", &fslider2, 0.5, 0.0, 1.0, 0.01);
		interface->addVerticalSlider("freq", &fslider1, 5.0, 0.1, 5e+01, 0.1);
		interface->declare(&fslider0, "name", "wet/dry");
		interface->addVerticalSlider("wet_dry", &fslider0, 0.0, -1.0, 1.0, 0.1);
		interface->closeBox();
		interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		double 	fSlow0 = fslider0;
		double 	fSlow1 = (1 - max(0, fSlow0));
		double 	fSlow2 = fslider1;
		int 	iSlow3 = int((fConst1 / double(fSlow2)));
		double 	fSlow4 = (1.0 / iSlow3);
		double 	fSlow5 = (fConst2 * fSlow2);
		int 	iSlow6 = int(fcheckbox0);
		double 	fSlow7 = fslider2;
		int 	iSlow8 = int(fcheckbox1);
		double 	fSlow9 = (1 - max(0, (0 - fSlow0)));
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* output0 = output[0];
		for (int i=0; i<count; i++) {
			double fTemp0 = (double)input0[i];
			iVec0[0] = 1;
			double fTemp1 = (fRec0[1] * (1 - (fConst0 / (fConst0 + (0.06 * exp((0 - (2.4849066497880004 * fRec0[1]))))))));
			iRec2[0] = ((int((iRec2[1] > 0)))?((2 * (iRec1[1] < iSlow3)) - 1):(1 - (2 * (iRec1[1] > 0))));
			iRec1[0] = (iRec2[0] + iRec1[1]);
			fRec5[0] = ((fSlow5 * (0 - fRec3[1])) + fRec5[1]);
			fRec4[0] = ((1 + ((fSlow5 * fRec5[0]) + fRec4[1])) - iVec0[1]);
			fRec3[0] = fRec4[0];
			fRec0[0] = (fTemp1 + (fConst0 * (pow((1 + (fSlow7 * (((iSlow6)?max(0, (0.5 * (1 + fRec3[0]))):(fSlow4 * iRec1[0])) - 1))),1.9) / (fConst0 + (0.06 * exp((0 - (2.4849066497880004 * fTemp1))))))));
			output0[i] = (FAUSTFLOAT)((fSlow9 * ((iSlow8)?(2700 * (fTemp0 / (2700 + exp((13.815510557964274 / log((2.718281828459045 + (8.551967507929417 * fRec0[0])))))))):fTemp0)) + (fSlow1 * fTemp0));
			// post processing
			fRec0[1] = fRec0[0];
			fRec3[1] = fRec3[0];
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			iRec1[1] = iRec1[0];
			iRec2[1] = iRec2[0];
			iVec0[1] = iVec0[0];
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
	registerVar("test.tremolo.ON","","B","",&fcheckbox1,0,0,1,1);
	registerVar("test.tremolo.SINE","","B","",&fcheckbox0,0,0,1,1);
	registerVar("test.tremolo.depth","","S","",&fslider2,0.5,0.0,1.0,0.01);
	registerVar("test.tremolo.freq","","S","",&fslider1,5.0,0.1,5e+01,0.1);
	registerVar("test.tremolo.wet_dry","wet/dry","S","",&fslider0,0.0,-1.0,1.0,0.1);
	registerInit("Experimental", Exp::init);
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
