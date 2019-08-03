#ifdef GDK_DISABLE_DEPRECATED
// Some Gdkmm 2.4 header need this defined
struct GdkSpanFunc;
#endif
#include <glibmm.h>
#include <gtkmm/main.h>
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gxwmm/init.h>
#include <gxwmm/switch.h>
#include <gxwmm/smallknob.h>
#include <gxwmm/bigknob.h>
#include <gxwmm/eqslider.h>
#include <gxwmm/selector.h>
#include <gxwmm/wheelvertical.h>
#include <gxwmm/wheel.h>

class Demo : public Gtk::Window
{

public:
	Demo();

protected:
	Gtk::VBox m_vbox;
	Gtk::HBox m_hbox1;
	Gxw::Switch m_switch1;
	Gxw::Switch m_switch2;
	Gxw::Switch m_switch3;
	Gxw::Switch m_switch4;
	Gxw::Switch m_switch5;
	Gtk::HBox m_hbox2;
	Gtk::Adjustment m_adj;
	Gxw::SmallKnob m_smallknob;
	Gxw::BigKnob m_bigknob;
	Gxw::EqSlider m_eqslider;
	Gxw::Wheel m_wheel;
	Gxw::WheelVertical m_v_wheel;
	Gxw::Selector m_selector;
};

Demo::Demo():
	m_vbox(),
	m_hbox1(),
	m_switch1("switchit"),
	m_switch2("switch"),
	m_switch3("minitoggle"),
	m_switch4("led"),
	m_switch5("button"),
	m_adj(0, -1, 1, 0.01, 0.1),
	m_smallknob(m_adj),
	m_bigknob(m_adj),
	m_eqslider(m_adj),
	m_wheel(m_adj),
	m_v_wheel(m_adj)
{
	m_hbox1.add(m_switch1);
	m_hbox1.add(m_switch2);
	m_hbox1.add(m_switch3);
	m_hbox1.add(m_switch4);
	m_hbox1.add(m_switch5);
	m_vbox.add(m_hbox1);
	m_hbox2.add(m_smallknob);
	m_smallknob.set_show_value(true);
	m_hbox2.add(m_bigknob);
	m_eqslider.set_show_value(true);
	m_eqslider.set_value_position(Gtk::POS_RIGHT);
	m_hbox2.add(m_eqslider);
	m_hbox2.add(m_v_wheel);
	m_vbox.add(m_hbox2);
	m_vbox.add(m_wheel);
	m_vbox.add(m_selector);
	add(m_vbox);
	set_border_width(10);
	show_all();
}

int main (int argc, char *argv[])
{
	Gxw::init();
	Gtk::Main kit(argc, argv);

	Demo demo;
	Gtk::Main::run(demo);

	return 0;
}
