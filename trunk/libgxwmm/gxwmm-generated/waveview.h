// Generated by gmmproc 2.66.7 -- DO NOT MODIFY!
#ifndef _GXWMM_WAVEVIEW_H
#define _GXWMM_WAVEVIEW_H


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

#include <gtkmm/drawingarea.h>


#ifndef DOXYGEN_SHOULD_SKIP_THIS
using GxWaveView = struct _GxWaveView;
using GxWaveViewClass = struct _GxWaveViewClass;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */


#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace Gxw
{ class  WaveView_Class; } // namespace Gxw
#endif //DOXYGEN_SHOULD_SKIP_THIS

namespace Gxw {


class WaveView: public Gtk::DrawingArea {
	public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  typedef WaveView CppObjectType;
  typedef WaveView_Class CppClassType;
  typedef GxWaveView BaseObjectType;
  typedef GxWaveViewClass BaseClassType;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

  WaveView(WaveView&& src) noexcept;
  WaveView& operator=(WaveView&& src) noexcept;

  // noncopyable
  WaveView(const WaveView&) = delete;
  WaveView& operator=(const WaveView&) = delete;

  ~WaveView() noexcept override;

#ifndef DOXYGEN_SHOULD_SKIP_THIS

private:
  friend class  WaveView_Class;
  static CppClassType waveview_class_;

protected:
  explicit WaveView(const Glib::ConstructParams& construct_params);
  explicit WaveView(GxWaveView* castitem);

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

public:

  /** Get the GType for this class, for use with the underlying GObject type system.
   */
  static GType get_type()      G_GNUC_CONST;

#ifndef DOXYGEN_SHOULD_SKIP_THIS


  static GType get_base_type() G_GNUC_CONST;
#endif

  /// Provides access to the underlying C GObject.
  GxWaveView*       gobj()       { return reinterpret_cast<GxWaveView*>(gobject_); }

  /// Provides access to the underlying C GObject.
  const GxWaveView* gobj() const { return reinterpret_cast<GxWaveView*>(gobject_); }


public:
  //C++ methods used to invoke GTK+ virtual functions:

protected:
  //GTK+ Virtual Functions (override these to change behaviour):

  //Default Signal Handlers::


private:

	public:
	WaveView();
	
  void set_multiplicator(double p1, double p2);
	
  void set_frame(const float* p1, int p2);
	
  void set_text(const Glib::ustring& p1, Gtk::CornerType p2);
	/** Text to be displayed at the top left.
   *
   * Default value: ""
   *
   * @return A PropertyProxy that allows you to get or set the value of the property,
   * or receive notification when the value of the property changes.
   */
  Glib::PropertyProxy< Glib::ustring > property_text_top_left() ;

/** Text to be displayed at the top left.
   *
   * Default value: ""
   *
   * @return A PropertyProxy_ReadOnly that allows you to get the value of the property,
   * or receive notification when the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly< Glib::ustring > property_text_top_left() const;

	/** Text to be displayed at the top right.
   *
   * Default value: ""
   *
   * @return A PropertyProxy that allows you to get or set the value of the property,
   * or receive notification when the value of the property changes.
   */
  Glib::PropertyProxy< Glib::ustring > property_text_top_right() ;

/** Text to be displayed at the top right.
   *
   * Default value: ""
   *
   * @return A PropertyProxy_ReadOnly that allows you to get the value of the property,
   * or receive notification when the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly< Glib::ustring > property_text_top_right() const;

	/** Text to be displayed at the bottom left.
   *
   * Default value: ""
   *
   * @return A PropertyProxy that allows you to get or set the value of the property,
   * or receive notification when the value of the property changes.
   */
  Glib::PropertyProxy< Glib::ustring > property_text_bottom_left() ;

/** Text to be displayed at the bottom left.
   *
   * Default value: ""
   *
   * @return A PropertyProxy_ReadOnly that allows you to get the value of the property,
   * or receive notification when the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly< Glib::ustring > property_text_bottom_left() const;

	/** Text to be displayed at the bottom right.
   *
   * Default value: ""
   *
   * @return A PropertyProxy that allows you to get or set the value of the property,
   * or receive notification when the value of the property changes.
   */
  Glib::PropertyProxy< Glib::ustring > property_text_bottom_right() ;

/** Text to be displayed at the bottom right.
   *
   * Default value: ""
   *
   * @return A PropertyProxy_ReadOnly that allows you to get the value of the property,
   * or receive notification when the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly< Glib::ustring > property_text_bottom_right() const;

	/** Text to be displayed at the bottom right.
   *
   * Default value: 5
   *
   * @return A PropertyProxy that allows you to get or set the value of the property,
   * or receive notification when the value of the property changes.
   */
  Glib::PropertyProxy< double > property_text_pos_left() ;

/** Text to be displayed at the bottom right.
   *
   * Default value: 5
   *
   * @return A PropertyProxy_ReadOnly that allows you to get the value of the property,
   * or receive notification when the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly< double > property_text_pos_left() const;

	/** Text to be displayed at the bottom right.
   *
   * Default value: 70
   *
   * @return A PropertyProxy that allows you to get or set the value of the property,
   * or receive notification when the value of the property changes.
   */
  Glib::PropertyProxy< double > property_text_pos_right() ;

/** Text to be displayed at the bottom right.
   *
   * Default value: 70
   *
   * @return A PropertyProxy_ReadOnly that allows you to get the value of the property,
   * or receive notification when the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly< double > property_text_pos_right() const;


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
   * @relates Gxw::WaveView
   */
  
  Gxw::WaveView* wrap(GxWaveView* object, bool take_copy = false);
} //namespace Glib


#endif /* _GXWMM_WAVEVIEW_H */

