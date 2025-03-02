// Generated by gmmproc 2.66.7 -- DO NOT MODIFY!
#ifndef _GXWMM_TOGGLEIMAGE_H
#define _GXWMM_TOGGLEIMAGE_H


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

#include <gtkmm/misc.h>


#ifndef DOXYGEN_SHOULD_SKIP_THIS
using GxToggleImage = struct _GxToggleImage;
using GxToggleImageClass = struct _GxToggleImageClass;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */


#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace Gxw
{ class  ToggleImage_Class; } // namespace Gxw
#endif //DOXYGEN_SHOULD_SKIP_THIS

namespace Gxw {


class ToggleImage: public Gtk::Misc {
	public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  typedef ToggleImage CppObjectType;
  typedef ToggleImage_Class CppClassType;
  typedef GxToggleImage BaseObjectType;
  typedef GxToggleImageClass BaseClassType;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

  ToggleImage(ToggleImage&& src) noexcept;
  ToggleImage& operator=(ToggleImage&& src) noexcept;

  // noncopyable
  ToggleImage(const ToggleImage&) = delete;
  ToggleImage& operator=(const ToggleImage&) = delete;

  ~ToggleImage() noexcept override;

#ifndef DOXYGEN_SHOULD_SKIP_THIS

private:
  friend class  ToggleImage_Class;
  static CppClassType toggleimage_class_;

protected:
  explicit ToggleImage(const Glib::ConstructParams& construct_params);
  explicit ToggleImage(GxToggleImage* castitem);

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

public:

  /** Get the GType for this class, for use with the underlying GObject type system.
   */
  static GType get_type()      G_GNUC_CONST;

#ifndef DOXYGEN_SHOULD_SKIP_THIS


  static GType get_base_type() G_GNUC_CONST;
#endif

  /// Provides access to the underlying C GObject.
  GxToggleImage*       gobj()       { return reinterpret_cast<GxToggleImage*>(gobject_); }

  /// Provides access to the underlying C GObject.
  const GxToggleImage* gobj() const { return reinterpret_cast<GxToggleImage*>(gobject_); }


public:
  //C++ methods used to invoke GTK+ virtual functions:

protected:
  //GTK+ Virtual Functions (override these to change behaviour):

  //Default Signal Handlers::


private:

	public:
	ToggleImage();
	
  void set_base_name(const Glib::ustring& p1);
	
  Glib::ustring get_base_name();
	/** Base name of the image, append '_on' and '_off' for the stock names.
   *
   * Default value: "switch"
   *
   * @return A PropertyProxy that allows you to get or set the value of the property,
   * or receive notification when the value of the property changes.
   */
  Glib::PropertyProxy< Glib::ustring > property_base_name() ;

/** Base name of the image, append '_on' and '_off' for the stock names.
   *
   * Default value: "switch"
   *
   * @return A PropertyProxy_ReadOnly that allows you to get the value of the property,
   * or receive notification when the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly< Glib::ustring > property_base_name() const;

	/** The id of the linked variable.
   *
   * Default value: ""
   *
   * @return A PropertyProxy that allows you to get or set the value of the property,
   * or receive notification when the value of the property changes.
   */
  Glib::PropertyProxy< Glib::ustring > property_var_id() ;

/** The id of the linked variable.
   *
   * Default value: ""
   *
   * @return A PropertyProxy_ReadOnly that allows you to get the value of the property,
   * or receive notification when the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly< Glib::ustring > property_var_id() const;


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
   * @relates Gxw::ToggleImage
   */
  
  Gxw::ToggleImage* wrap(GxToggleImage* object, bool take_copy = false);
} //namespace Glib


#endif /* _GXWMM_TOGGLEIMAGE_H */

