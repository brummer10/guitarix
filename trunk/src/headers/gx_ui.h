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

#ifndef SRC_HEADERS_GX_UI_H_
#define SRC_HEADERS_GX_UI_H_

namespace gx_ui {
/* ------------- UI Classes ------------- */
/* base interface classes interfacing with the GUI  */
class GxUI;


/****************************************************************
 ** class GxUiItem (virtual class)
 */

class GxUiItem {
 public:
    virtual ~GxUiItem();
    virtual void reflectZone() = 0;
    virtual bool hasChanged() = 0;
};


/****************************************************************
 ** class GxUI
 ** Main UI base class
 */

class GxUI {
    typedef list< GxUiItem* > clist;
    typedef map < void*, clist* > zmap;

 private:
    static list<GxUI*>    fGuiList;
    static bool in_updateAll;
    bool        in_update;
    zmap        fZoneMap;
 public:
    GxUI();
    virtual ~GxUI();

    // public methods
    void registerZone(void*, GxUiItem*);
    void unregisterZone(void* z, GxUiItem* c);
    void updateAllZones(bool force = false);
    void updateZone(void* z, bool force = false);
    static void updateAllGuis(bool force = false);
};

// Update all user items reflecting zone z
inline void GxUI::updateZone(void* z, bool force) {
    clist* 	l = fZoneMap[z];
    for (clist::iterator c = l->begin(); c != l->end(); ++c) {
        if (force || (*c)->hasChanged()) {
	    (*c)->reflectZone();
	}
    }
}


/****************************************************************
 ** template class GxUiItemV<T>
 */

template<class T>
class GxUiItemV: public GxUiItem {
protected :
    GxUI*    fGUI;
public:
    T*    fZone;
    T     fCache;
public :
    GxUiItemV(GxUI* ui, T* zone);
    ~GxUiItemV();
    void  modifyZone(T v);
    virtual bool hasChanged();
};

typedef GxUiItemV<float> GxUiItemFloat;
typedef GxUiItemV<int> GxUiItemInt;
typedef GxUiItemV<unsigned int> GxUiItemUInt;
typedef GxUiItemV<bool> GxUiItemBool;

template<class T>
GxUiItemV<T>::GxUiItemV(GxUI* ui, T* zone)
    : fGUI(ui), fZone(zone), fCache(*zone) {
    ui->registerZone(zone, this);
}

template<class T>
GxUiItemV<T>::~GxUiItemV() {
    fGUI->unregisterZone(fZone, this);
}

template<class T>
bool GxUiItemV<T>::hasChanged() {
    return *fZone != fCache;
}

template<class T>
void GxUiItemV<T>::modifyZone(T v) {
    fCache = v;
    if (*fZone != v) {
        *fZone = v;
        fGUI->updateZone(fZone);
    }
}


/****************************************************************
 ** class GxUiCallbackItemFloat
 ** Callback Item
 */

typedef void (*GxUiCallback)(float val, void* data);

struct GxUiCallbackItemFloat : public GxUiItemFloat {
    GxUiCallback fCallback;
    void*     fData;

    GxUiCallbackItemFloat(GxUI* ui, float* zone, GxUiCallback foo, void* data);
    virtual void reflectZone();
};


/****************************************************************
 ** template class UiSignal<T>
 */

template <class T>
class UiSignal: public GxUiItemV<T> {
private:
    virtual void reflectZone();
public:
    UiSignal(GxUI* ui, T *v): GxUiItemV<T>(ui, v) {};
    static UiSignal* create(GxUI* ui, gx_engine::ParamMap& param, const char *id);
    ~UiSignal();
    sigc::signal<void, T> changed;
};

template<class T>
UiSignal<T>::~UiSignal() {
}

template<class T>
void UiSignal<T>::reflectZone() {
    T v = *GxUiItemV<T>::fZone;
    GxUiItemV<T>::fCache = v;
    changed(v);
}

template<class T>
UiSignal<T>* UiSignal<T>::create(GxUI* ui, gx_engine::ParamMap& param, const char *id) {
    if (!param.hasId(id)) {
	printf("%s not found!!!\n", id);
	return 0;
    }
    gx_engine::ParameterV<T>* p = dynamic_cast<gx_engine::ParameterV<T>*>(&param[id]);
    if (!p) {
	printf("%s has wrong type [%s/%s]!!\n", id, typeid(param[id]).name(), typeid(gx_engine::ParameterV<T>).name());
	return 0;
    }
    return new UiSignal(ui, &p->value);
}

typedef UiSignal<float> UiSignalFloat;
typedef UiSignal<int> UiSignalInt;
typedef UiSignal<unsigned int> UiSignalUInt;
typedef UiSignal<bool> UiSignalBool;

} /* end of gx_ui namespace */

#endif  // SRC_HEADERS_GX_UI_H_
