// Generated by gmmproc 2.66.7 -- DO NOT MODIFY!
#ifndef _GXWMM_VSLIDER_P_H
#define _GXWMM_VSLIDER_P_H


#include <gxwmm/private/regler_p.h>

#include <glibmm/class.h>

namespace Gxw
{

class  VSlider_Class : public Glib::Class
{
public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  using CppObjectType = VSlider;
  using BaseObjectType = GxVSlider;
  using BaseClassType = GxVSliderClass;
  using CppClassParent = Gxw::Regler_Class;
  using BaseClassParent = GxReglerClass;

  friend class VSlider;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

  const Glib::Class& init();


  static void class_init_function(void* g_class, void* class_data);

  static Glib::ObjectBase* wrap_new(GObject*);

protected:

  //Callbacks (default signal handlers):
  //These will call the *_impl member methods, which will then call the existing default signal callbacks, if any.
  //You could prevent the original default signal handlers being called by overriding the *_impl method.

  //Callbacks (virtual functions):
};


} // namespace Gxw


#endif /* _GXWMM_VSLIDER_P_H */

