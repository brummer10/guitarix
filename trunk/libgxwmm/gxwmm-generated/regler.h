// Generated by gmmproc 2.66.7 -- DO NOT MODIFY!
#ifndef _GXWMM_REGLER_H
#define _GXWMM_REGLER_H


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

#include <gtkmm/range.h>
#include <gtkmm/label.h>
#include <gdkmm/rectangle.h>
#include <gxwmm/controlparameter.h>


#ifndef DOXYGEN_SHOULD_SKIP_THIS
using GxRegler = struct _GxRegler;
using GxReglerClass = struct _GxReglerClass;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */


#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace Gxw
{ class  Regler_Class; } // namespace Gxw
#endif //DOXYGEN_SHOULD_SKIP_THIS

namespace Gxw {


class Regler: public Gtk::Range, public ControlParameter {
	public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  typedef Regler CppObjectType;
  typedef Regler_Class CppClassType;
  typedef GxRegler BaseObjectType;
  typedef GxReglerClass BaseClassType;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

  Regler(Regler&& src) noexcept;
  Regler& operator=(Regler&& src) noexcept;

  // noncopyable
  Regler(const Regler&) = delete;
  Regler& operator=(const Regler&) = delete;

  ~Regler() noexcept override;

#ifndef DOXYGEN_SHOULD_SKIP_THIS

private:
  friend class  Regler_Class;
  static CppClassType regler_class_;

protected:
  explicit Regler(const Glib::ConstructParams& construct_params);
  explicit Regler(GxRegler* castitem);

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

public:

  /** Get the GType for this class, for use with the underlying GObject type system.
   */
  static GType get_type()      G_GNUC_CONST;

#ifndef DOXYGEN_SHOULD_SKIP_THIS


  static GType get_base_type() G_GNUC_CONST;
#endif

  /// Provides access to the underlying C GObject.
  GxRegler*       gobj()       { return reinterpret_cast<GxRegler*>(gobject_); }

  /// Provides access to the underlying C GObject.
  const GxRegler* gobj() const { return reinterpret_cast<GxRegler*>(gobject_); }


public:
  //C++ methods used to invoke GTK+ virtual functions:

protected:
  //GTK+ Virtual Functions (override these to change behaviour):

  //Default Signal Handlers::
  /// This is a default handler for the signal signal_value_entry().
  virtual bool on_value_entry(const Gdk::Rectangle& p1, GdkEventButton* p2);
  /// This is a default handler for the signal signal_input_value().
  virtual int on_input_value(void * spin, void * new_val);
  /// This is a default handler for the signal signal_format_value().
  virtual Glib::ustring on_format_value(double value);


private:

	
	public:
	
  void set_label_ref(Gtk::Label* p1);
	
  Gtk::Label* get_label_ref();
	
  void set_show_value(bool p1);
	
  bool get_show_value();
	
  void set_value_position(Gtk::PositionType p1);
	
  Gtk::PositionType get_value_position();
 

  /**
   * @par Slot Prototype:
   * <tt>bool on_my_%value_entry(const Gdk::Rectangle& p1, GdkEventButton* p2)</tt>
   *
   * Flags: Run Last
   *
   */

  Glib::SignalProxy< bool,const Gdk::Rectangle&,GdkEventButton* > signal_value_entry();

	
  /**
   * @par Slot Prototype:
   * <tt>int on_my_%input_value(void * spin, void * new_val)</tt>
   *
   * Flags: Run Last
   *
   */

  Glib::SignalProxy< int,void *,void * > signal_input_value();

	/** GtkLabel for caption.
   *
   * @return A PropertyProxy that allows you to get or set the value of the property,
   * or receive notification when the value of the property changes.
   */
  Glib::PropertyProxy< Gtk::Label > property_label_ref() ;

/** GtkLabel for caption.
   *
   * @return A PropertyProxy_ReadOnly that allows you to get the value of the property,
   * or receive notification when the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly< Gtk::Label > property_label_ref() const;

	/** display the value.
   *
   * Default value: <tt>true</tt>
   *
   * @return A PropertyProxy that allows you to get or set the value of the property,
   * or receive notification when the value of the property changes.
   */
  Glib::PropertyProxy< bool > property_show_value() ;

/** display the value.
   *
   * Default value: <tt>true</tt>
   *
   * @return A PropertyProxy_ReadOnly that allows you to get the value of the property,
   * or receive notification when the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly< bool > property_show_value() const;

	/** The horizontal position of the value (0..1).
   *
   * Default value: 0.5
   *
   * @return A PropertyProxy that allows you to get or set the value of the property,
   * or receive notification when the value of the property changes.
   */
  Glib::PropertyProxy< double > property_value_xalign() ;

/** The horizontal position of the value (0..1).
   *
   * Default value: 0.5
   *
   * @return A PropertyProxy_ReadOnly that allows you to get the value of the property,
   * or receive notification when the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly< double > property_value_xalign() const;

	/** Number of digits for display.
   *
   * Default value: 1
   *
   * @return A PropertyProxy_ReadOnly that allows you to get the value of the property,
   * or receive notification when the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly< int > property_digits() const;


	/** The position of the value display.
   *
   * Default value: Gtk::POS_BOTTOM
   *
   * @return A PropertyProxy that allows you to get or set the value of the property,
   * or receive notification when the value of the property changes.
   */
  Glib::PropertyProxy< Gtk::PositionType > property_value_position() ;

/** The position of the value display.
   *
   * Default value: Gtk::POS_BOTTOM
   *
   * @return A PropertyProxy_ReadOnly that allows you to get the value of the property,
   * or receive notification when the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly< Gtk::PositionType > property_value_position() const;


  /**
   * @par Slot Prototype:
   * <tt>Glib::ustring on_my_%format_value(double value)</tt>
   *
   * Flags: Run Last
   *
   */

  Glib::SignalProxy< Glib::ustring,double > signal_format_value();


	protected:
	Regler();


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
   * @relates Gxw::Regler
   */
  
  Gxw::Regler* wrap(GxRegler* object, bool take_copy = false);
} //namespace Glib


#endif /* _GXWMM_REGLER_H */

