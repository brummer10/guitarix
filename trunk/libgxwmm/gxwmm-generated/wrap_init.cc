
#include <glib.h>

// Disable the 'const' function attribute of the get_type() functions.
// GCC would optimize them out because we don't use the return value.
#undef  G_GNUC_CONST
#define G_GNUC_CONST /* empty */

#include <gxwmm/wrap_init.h>
#include <glibmm/error.h>
#include <glibmm/object.h>

// #include the widget headers so that we can call the get_type() static methods:

#include "controlparameter.h"
#include "switch.h"
#include "regler.h"
#include "knob.h"
#include "bigknob.h"
#include "smallknob.h"
#include "smallknobr.h"
#include "tuner.h"
#include "fastmeter.h"
#include "waveview.h"
#include "selector.h"
#include "toggleimage.h"
#include "iredit.h"
#include "radiobutton.h"
#include "wheel.h"
#include "wheelvertical.h"
#include "hslider.h"
#include "minislider.h"
#include "vslider.h"
#include "eqslider.h"
#include "levelslider.h"
#include "paintbox.h"
#include "meterscale.h"
#include "valuedisplay.h"
#include "simplevaluedisplay.h"

extern "C"
{

//Declarations of the *_get_type() functions:

GType gx_big_knob_get_type(void);
GType gx_eq_slider_get_type(void);
GType gx_fast_meter_get_type(void);
GType gx_hslider_get_type(void);
GType gx_ir_edit_get_type(void);
GType gx_knob_get_type(void);
GType gx_level_slider_get_type(void);
GType gx_meter_scale_get_type(void);
GType gx_mini_slider_get_type(void);
GType gx_paint_box_get_type(void);
GType gx_radio_button_get_type(void);
GType gx_regler_get_type(void);
GType gx_selector_get_type(void);
GType gx_simple_value_display_get_type(void);
GType gx_small_knob_get_type(void);
GType gx_small_knob_r_get_type(void);
GType gx_switch_get_type(void);
GType gx_toggle_image_get_type(void);
GType gx_tuner_get_type(void);
GType gx_vslider_get_type(void);
GType gx_value_display_get_type(void);
GType gx_wave_view_get_type(void);
GType gx_wheel_get_type(void);
GType gx_wheel_vertical_get_type(void);

//Declarations of the *_error_quark() functions:

} // extern "C"


//Declarations of the *_Class::wrap_new() methods, instead of including all the private headers:

namespace Gxw {  class BigKnob_Class { public: static Glib::ObjectBase* wrap_new(GObject*); };  }
namespace Gxw {  class EqSlider_Class { public: static Glib::ObjectBase* wrap_new(GObject*); };  }
namespace Gxw {  class FastMeter_Class { public: static Glib::ObjectBase* wrap_new(GObject*); };  }
namespace Gxw {  class HSlider_Class { public: static Glib::ObjectBase* wrap_new(GObject*); };  }
namespace Gxw {  class IREdit_Class { public: static Glib::ObjectBase* wrap_new(GObject*); };  }
namespace Gxw {  class Knob_Class { public: static Glib::ObjectBase* wrap_new(GObject*); };  }
namespace Gxw {  class LevelSlider_Class { public: static Glib::ObjectBase* wrap_new(GObject*); };  }
namespace Gxw {  class MeterScale_Class { public: static Glib::ObjectBase* wrap_new(GObject*); };  }
namespace Gxw {  class MiniSlider_Class { public: static Glib::ObjectBase* wrap_new(GObject*); };  }
namespace Gxw {  class PaintBox_Class { public: static Glib::ObjectBase* wrap_new(GObject*); };  }
namespace Gxw {  class RadioButton_Class { public: static Glib::ObjectBase* wrap_new(GObject*); };  }
namespace Gxw {  class Regler_Class { public: static Glib::ObjectBase* wrap_new(GObject*); };  }
namespace Gxw {  class Selector_Class { public: static Glib::ObjectBase* wrap_new(GObject*); };  }
namespace Gxw {  class SimpleValueDisplay_Class { public: static Glib::ObjectBase* wrap_new(GObject*); };  }
namespace Gxw {  class SmallKnob_Class { public: static Glib::ObjectBase* wrap_new(GObject*); };  }
namespace Gxw {  class SmallKnobR_Class { public: static Glib::ObjectBase* wrap_new(GObject*); };  }
namespace Gxw {  class Switch_Class { public: static Glib::ObjectBase* wrap_new(GObject*); };  }
namespace Gxw {  class ToggleImage_Class { public: static Glib::ObjectBase* wrap_new(GObject*); };  }
namespace Gxw {  class Tuner_Class { public: static Glib::ObjectBase* wrap_new(GObject*); };  }
namespace Gxw {  class VSlider_Class { public: static Glib::ObjectBase* wrap_new(GObject*); };  }
namespace Gxw {  class ValueDisplay_Class { public: static Glib::ObjectBase* wrap_new(GObject*); };  }
namespace Gxw {  class WaveView_Class { public: static Glib::ObjectBase* wrap_new(GObject*); };  }
namespace Gxw {  class Wheel_Class { public: static Glib::ObjectBase* wrap_new(GObject*); };  }
namespace Gxw {  class WheelVertical_Class { public: static Glib::ObjectBase* wrap_new(GObject*); };  }

namespace Gxw { 

void wrap_init()
{
  // Register Error domains:

// Map gtypes to gtkmm wrapper-creation functions:
  Glib::wrap_register(gx_big_knob_get_type(), &Gxw::BigKnob_Class::wrap_new);
  Glib::wrap_register(gx_eq_slider_get_type(), &Gxw::EqSlider_Class::wrap_new);
  Glib::wrap_register(gx_fast_meter_get_type(), &Gxw::FastMeter_Class::wrap_new);
  Glib::wrap_register(gx_hslider_get_type(), &Gxw::HSlider_Class::wrap_new);
  Glib::wrap_register(gx_ir_edit_get_type(), &Gxw::IREdit_Class::wrap_new);
  Glib::wrap_register(gx_knob_get_type(), &Gxw::Knob_Class::wrap_new);
  Glib::wrap_register(gx_level_slider_get_type(), &Gxw::LevelSlider_Class::wrap_new);
  Glib::wrap_register(gx_meter_scale_get_type(), &Gxw::MeterScale_Class::wrap_new);
  Glib::wrap_register(gx_mini_slider_get_type(), &Gxw::MiniSlider_Class::wrap_new);
  Glib::wrap_register(gx_paint_box_get_type(), &Gxw::PaintBox_Class::wrap_new);
  Glib::wrap_register(gx_radio_button_get_type(), &Gxw::RadioButton_Class::wrap_new);
  Glib::wrap_register(gx_regler_get_type(), &Gxw::Regler_Class::wrap_new);
  Glib::wrap_register(gx_selector_get_type(), &Gxw::Selector_Class::wrap_new);
  Glib::wrap_register(gx_simple_value_display_get_type(), &Gxw::SimpleValueDisplay_Class::wrap_new);
  Glib::wrap_register(gx_small_knob_get_type(), &Gxw::SmallKnob_Class::wrap_new);
  Glib::wrap_register(gx_small_knob_r_get_type(), &Gxw::SmallKnobR_Class::wrap_new);
  Glib::wrap_register(gx_switch_get_type(), &Gxw::Switch_Class::wrap_new);
  Glib::wrap_register(gx_toggle_image_get_type(), &Gxw::ToggleImage_Class::wrap_new);
  Glib::wrap_register(gx_tuner_get_type(), &Gxw::Tuner_Class::wrap_new);
  Glib::wrap_register(gx_vslider_get_type(), &Gxw::VSlider_Class::wrap_new);
  Glib::wrap_register(gx_value_display_get_type(), &Gxw::ValueDisplay_Class::wrap_new);
  Glib::wrap_register(gx_wave_view_get_type(), &Gxw::WaveView_Class::wrap_new);
  Glib::wrap_register(gx_wheel_get_type(), &Gxw::Wheel_Class::wrap_new);
  Glib::wrap_register(gx_wheel_vertical_get_type(), &Gxw::WheelVertical_Class::wrap_new);

  // Register the gtkmm gtypes:
  Gxw::BigKnob::get_type();
  Gxw::EqSlider::get_type();
  Gxw::FastMeter::get_type();
  Gxw::HSlider::get_type();
  Gxw::IREdit::get_type();
  Gxw::Knob::get_type();
  Gxw::LevelSlider::get_type();
  Gxw::MeterScale::get_type();
  Gxw::MiniSlider::get_type();
  Gxw::PaintBox::get_type();
  Gxw::RadioButton::get_type();
  Gxw::Regler::get_type();
  Gxw::Selector::get_type();
  Gxw::SimpleValueDisplay::get_type();
  Gxw::SmallKnob::get_type();
  Gxw::SmallKnobR::get_type();
  Gxw::Switch::get_type();
  Gxw::ToggleImage::get_type();
  Gxw::Tuner::get_type();
  Gxw::VSlider::get_type();
  Gxw::ValueDisplay::get_type();
  Gxw::WaveView::get_type();
  Gxw::Wheel::get_type();
  Gxw::WheelVertical::get_type();

} // wrap_init()

} //Gxw


