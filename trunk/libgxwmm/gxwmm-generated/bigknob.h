// -*- c++ -*-
// Generated by gtkmmproc -- DO NOT MODIFY!
#ifndef _GXWMM_BIGKNOB_H
#define _GXWMM_BIGKNOB_H


#include <glibmm/ustring.h>
#include <sigc++/sigc++.h>

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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <gxwmm/knob.h>
#include <gtkmm/adjustment.h>


#ifndef DOXYGEN_SHOULD_SKIP_THIS
typedef struct _GxBigKnob GxBigKnob;
typedef struct _GxBigKnobClass GxBigKnobClass;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */


namespace Gxw
{ class BigKnob_Class; } // namespace Gxw
namespace Gxw {


class BigKnob: public Gxw::Knob {
	public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  typedef BigKnob CppObjectType;
  typedef BigKnob_Class CppClassType;
  typedef GxBigKnob BaseObjectType;
  typedef GxBigKnobClass BaseClassType;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

  virtual ~BigKnob();

#ifndef DOXYGEN_SHOULD_SKIP_THIS

private:
  friend class BigKnob_Class;
  static CppClassType bigknob_class_;

  // noncopyable
  BigKnob(const BigKnob&);
  BigKnob& operator=(const BigKnob&);

protected:
  explicit BigKnob(const Glib::ConstructParams& construct_params);
  explicit BigKnob(GxBigKnob* castitem);

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  static GType get_type()      G_GNUC_CONST;


  static GType get_base_type() G_GNUC_CONST;
#endif

  ///Provides access to the underlying C GtkObject.
  GxBigKnob*       gobj()       { return reinterpret_cast<GxBigKnob*>(gobject_); }

  ///Provides access to the underlying C GtkObject.
  const GxBigKnob* gobj() const { return reinterpret_cast<GxBigKnob*>(gobject_); }


public:
  //C++ methods used to invoke GTK+ virtual functions:

protected:
  //GTK+ Virtual Functions (override these to change behaviour):

  //Default Signal Handlers::


private:

	public:
	BigKnob();
	explicit BigKnob(Gtk::Adjustment& adjustment);


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
   * @relates Gxw::BigKnob
   */
  Gxw::BigKnob* wrap(GxBigKnob* object, bool take_copy = false);
} //namespace Glib


#endif /* _GXWMM_BIGKNOB_H */

