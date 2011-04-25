// Generated by gtkmmproc -- DO NOT MODIFY!


#include <gxwmm/hslider.h>
#include <gxwmm/private/hslider_p.h>

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

#include <gxw/GxHSlider.h>

Gxw::HSlider::HSlider(Gtk::Adjustment& adjustment):
	// Mark this class as non-derived to allow C++ vfuncs to be skipped.
  Glib::ObjectBase(0),
  Gxw::Regler(Glib::ConstructParams(hslider_class_.init(), "adjustment",adjustment.gobj(), static_cast<char*>(0)))
{}

namespace
{
} // anonymous namespace


namespace Glib
{

Gxw::HSlider* wrap(GxHSlider* object, bool take_copy)
{
  return dynamic_cast<Gxw::HSlider *> (Glib::wrap_auto ((GObject*)(object), take_copy));
}

} /* namespace Glib */

namespace Gxw
{


/* The *_Class implementation: */

const Glib::Class& HSlider_Class::init()
{
  if(!gtype_) // create the GType if necessary
  {
    // Glib::Class has to know the class init function to clone custom types.
    class_init_func_ = &HSlider_Class::class_init_function;

    // This is actually just optimized away, apparently with no harm.
    // Make sure that the parent type has been created.
    //CppClassParent::CppObjectType::get_type();

    // Create the wrapper type, with the same class/instance size as the base type.
    register_derived_type(gx_hslider_get_type());

    // Add derived versions of interfaces, if the C type implements any interfaces:

  }

  return *this;
}


void HSlider_Class::class_init_function(void* g_class, void* class_data)
{
  BaseClassType *const klass = static_cast<BaseClassType*>(g_class);
  CppClassParent::class_init_function(klass, class_data);

#ifdef GLIBMM_VFUNCS_ENABLED
#endif //GLIBMM_VFUNCS_ENABLED

#ifdef GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED
#endif //GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED
}

#ifdef GLIBMM_VFUNCS_ENABLED
#endif //GLIBMM_VFUNCS_ENABLED

#ifdef GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED
#endif //GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED


Glib::ObjectBase* HSlider_Class::wrap_new(GObject* o)
{
  return manage(new HSlider((GxHSlider*)(o)));

}


/* The implementation: */

HSlider::HSlider(const Glib::ConstructParams& construct_params)
:
  Gxw::Regler(construct_params)
{
  }

HSlider::HSlider(GxHSlider* castitem)
:
  Gxw::Regler((GxRegler*)(castitem))
{
  }

HSlider::~HSlider()
{
  destroy_();
}

HSlider::CppClassType HSlider::hslider_class_; // initialize static member

GType HSlider::get_type()
{
  return hslider_class_.init().get_type();
}


GType HSlider::get_base_type()
{
  return gx_hslider_get_type();
}


HSlider::HSlider()
:
  // Mark this class as non-derived to allow C++ vfuncs to be skipped.
  Glib::ObjectBase(0),
  Gxw::Regler(Glib::ConstructParams(hslider_class_.init()))
{
  

}


#ifdef GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED
#endif //GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED

#ifdef GLIBMM_VFUNCS_ENABLED
#endif //GLIBMM_VFUNCS_ENABLED


} // namespace Gxw


