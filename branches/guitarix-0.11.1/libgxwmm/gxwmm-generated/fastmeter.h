// -*- c++ -*-
// Generated by gtkmmproc -- DO NOT MODIFY!
#ifndef _GXWMM_FASTMETER_H
#define _GXWMM_FASTMETER_H


#include <glibmm.h>

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
 */

#include <gtkmm/drawingarea.h>


#ifndef DOXYGEN_SHOULD_SKIP_THIS
typedef struct _GxFastMeter GxFastMeter;
typedef struct _GxFastMeterClass GxFastMeterClass;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */


namespace Gxw
{ class FastMeter_Class; } // namespace Gxw
namespace Gxw {


class FastMeter: public Gtk::DrawingArea {
	public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  typedef FastMeter CppObjectType;
  typedef FastMeter_Class CppClassType;
  typedef GxFastMeter BaseObjectType;
  typedef GxFastMeterClass BaseClassType;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

  virtual ~FastMeter();

#ifndef DOXYGEN_SHOULD_SKIP_THIS

private:
  friend class FastMeter_Class;
  static CppClassType fastmeter_class_;

  // noncopyable
  FastMeter(const FastMeter&);
  FastMeter& operator=(const FastMeter&);

protected:
  explicit FastMeter(const Glib::ConstructParams& construct_params);
  explicit FastMeter(GxFastMeter* castitem);

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  static GType get_type()      G_GNUC_CONST;


  static GType get_base_type() G_GNUC_CONST;
#endif

  ///Provides access to the underlying C GtkObject.
  GxFastMeter*       gobj()       { return reinterpret_cast<GxFastMeter*>(gobject_); }

  ///Provides access to the underlying C GtkObject.
  const GxFastMeter* gobj() const { return reinterpret_cast<GxFastMeter*>(gobject_); }


public:
  //C++ methods used to invoke GTK+ virtual functions:
#ifdef GLIBMM_VFUNCS_ENABLED
#endif //GLIBMM_VFUNCS_ENABLED

protected:
  //GTK+ Virtual Functions (override these to change behaviour):
#ifdef GLIBMM_VFUNCS_ENABLED
#endif //GLIBMM_VFUNCS_ENABLED

  //Default Signal Handlers::
#ifdef GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED
#endif //GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED


private:

	public:
	FastMeter();
	
  void set(double lvl);
	
  void clear();
	
  void set_hold_count(int val);
	#ifdef GLIBMM_PROPERTIES_ENABLED
/** Count of cycles for which the peak value is held on display.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy<int> property_hold() ;
#endif //#GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
/** Count of cycles for which the peak value is held on display.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly<int> property_hold() const;
#endif //#GLIBMM_PROPERTIES_ENABLED

	#ifdef GLIBMM_PROPERTIES_ENABLED
/** Horizontal size of meter.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy<int> property_dimen() ;
#endif //#GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
/** Horizontal size of meter.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly<int> property_dimen() const;
#endif //#GLIBMM_PROPERTIES_ENABLED


};

} // namespace Gxw


namespace Glib
{
  /** A Glib::wrap() method for this object.
   * 
   * @param object The C instance.
   * @param take_copy False if the result should take ownership of the C instance. True if it should take a new copy or ref.
   * @result A C++ instance that wraps this C instance.
   *
   * @relates Gxw::FastMeter
   */
  Gxw::FastMeter* wrap(GxFastMeter* object, bool take_copy = false);
} //namespace Glib


#endif /* _GXWMM_FASTMETER_H */

