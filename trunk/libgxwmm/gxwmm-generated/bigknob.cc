// Generated by gmmproc 2.66.7 -- DO NOT MODIFY!


#include <glibmm.h>

#include <gxwmm/bigknob.h>
#include <gxwmm/private/bigknob_p.h>


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

#include <gxw/GxBigKnob.h>

Gxw::BigKnob::BigKnob(const Glib::RefPtr<Gtk::Adjustment>& adjustment):
	// Mark this class as non-derived to allow C++ vfuncs to be skipped.
  Glib::ObjectBase(nullptr),
  Gxw::Knob(Glib::ConstructParams(bigknob_class_.init(), "adjustment",adjustment->gobj(), nullptr))
{}

namespace
{
} // anonymous namespace


namespace Glib
{

Gxw::BigKnob* wrap(GxBigKnob* object, bool take_copy)
{
  return dynamic_cast<Gxw::BigKnob *> (Glib::wrap_auto ((GObject*)(object), take_copy));
}

} /* namespace Glib */

namespace Gxw
{


/* The *_Class implementation: */

const Glib::Class& BigKnob_Class::init()
{
  if(!gtype_) // create the GType if necessary
  {
    // Glib::Class has to know the class init function to clone custom types.
    class_init_func_ = &BigKnob_Class::class_init_function;

    // This is actually just optimized away, apparently with no harm.
    // Make sure that the parent type has been created.
    //CppClassParent::CppObjectType::get_type();

    // Create the wrapper type, with the same class/instance size as the base type.
    register_derived_type(gx_big_knob_get_type());

    // Add derived versions of interfaces, if the C type implements any interfaces:

  }

  return *this;
}


void BigKnob_Class::class_init_function(void* g_class, void* class_data)
{
  const auto klass = static_cast<BaseClassType*>(g_class);
  CppClassParent::class_init_function(klass, class_data);


}


Glib::ObjectBase* BigKnob_Class::wrap_new(GObject* o)
{
  return manage(new BigKnob((GxBigKnob*)(o)));

}


/* The implementation: */

BigKnob::BigKnob(const Glib::ConstructParams& construct_params)
:
  Gxw::Knob(construct_params)
{
  }

BigKnob::BigKnob(GxBigKnob* castitem)
:
  Gxw::Knob((GxKnob*)(castitem))
{
  }


BigKnob::BigKnob(BigKnob&& src) noexcept
: Gxw::Knob(std::move(src))
{}

BigKnob& BigKnob::operator=(BigKnob&& src) noexcept
{
  Gxw::Knob::operator=(std::move(src));
  return *this;
}

BigKnob::~BigKnob() noexcept
{
  destroy_();
}

BigKnob::CppClassType BigKnob::bigknob_class_; // initialize static member

GType BigKnob::get_type()
{
  return bigknob_class_.init().get_type();
}


GType BigKnob::get_base_type()
{
  return gx_big_knob_get_type();
}


BigKnob::BigKnob()
:
  // Mark this class as non-derived to allow C++ vfuncs to be skipped.
  Glib::ObjectBase(nullptr),
  Gxw::Knob(Glib::ConstructParams(bigknob_class_.init()))
{
  

}


} // namespace Gxw


