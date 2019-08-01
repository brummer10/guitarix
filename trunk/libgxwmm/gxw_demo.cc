#ifdef GDK_DISABLE_DEPRECATED
// Some Gdkmm 2.4 header need this defined
struct GdkSpanFunc;
#endif
#include <glibmm.h>
#include <gtkmm/main.h>
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/treestore.h>
#include <gtkmm/listviewtext.h>
#include <gxwmm/init.h>
#include <gxwmm/switch.h>
#include <gxwmm/smallknob.h>
#include <gxwmm/smallknobr.h>
#include <gxwmm/bigknob.h>
#include <gxwmm/midknob.h>
#include <gxwmm/eqslider.h>
#include <gxwmm/selector.h>
#include <gxwmm/wheelvertical.h>
#include <gxwmm/wheel.h>
#include <gxwmm/hslider.h>
#include <gxwmm/vslider.h>
#include <gxwmm/minislider.h>
#include <gxwmm/playhead.h>

class TextColumns : public Gtk::TreeModelColumnRecord
{
public:

	TextColumns()
    {
		add(m_col_text);
	}

	Gtk::TreeModelColumn<Glib::ustring> m_col_text;
};

class Demo : public Gtk::Window
{

public:
	Demo();

protected:
	TextColumns m_selector_model;
	Gtk::VBox m_vbox;
	Gtk::HBox m_hbox1;
	Gxw::Switch m_switch1;
	Gxw::Switch m_switch2;
	Gxw::Switch m_switch3;
	Gxw::Switch m_switch4;
	Gxw::Switch m_switch5;
	Gtk::HBox m_hbox_knobs;
	Glib::RefPtr<Gtk::Adjustment> m_adj_knobs;
	Gxw::SmallKnob m_smallknob;
	Gxw::BigKnob m_bigknob;
	Gxw::MidKnob m_midknob;
	Gxw::SmallKnobR m_smallknob_r;

	Gtk::HBox m_hbox_sliders;
	Glib::RefPtr<Gtk::Adjustment> m_adj_sliders;
	Gxw::EqSlider m_eqslider;
	Gxw::HSlider m_h_slider;
	Gxw::VSlider m_v_slider;
	Gxw::MiniSlider m_mini_slider;

	Gtk::HBox m_hbox_wheels;
	Glib::RefPtr<Gtk::Adjustment> m_adj_wheels;
	Gxw::Wheel m_wheel;
	Gxw::WheelVertical m_v_wheel;
	Gxw::Selector m_selector;

	Gxw::PlayHead m_playhead;
};

Demo::Demo():
	m_vbox(),
	m_hbox1(),
	m_switch1("switchit"),
	m_switch2("switch"),
	m_switch3("minitoggle"),
	m_switch4("led"),
	m_switch5("button"),
	m_adj_knobs(Gtk::Adjustment::create(0, -1, 1, 0.01, 0.1)),
	m_smallknob(m_adj_knobs),
	m_bigknob(m_adj_knobs),
	m_midknob(m_adj_knobs),
	m_smallknob_r(m_adj_knobs),
	m_adj_sliders(Gtk::Adjustment::create(0, -1, 1, 0.01, 0.1)),
	m_eqslider(m_adj_sliders),
	m_h_slider(m_adj_sliders),
	m_v_slider(m_adj_sliders),
	m_mini_slider(m_adj_sliders),
	m_adj_wheels(Gtk::Adjustment::create(0, -1, 1, 0.01, 0.1)),
	m_wheel(m_adj_wheels),
	m_v_wheel(m_adj_wheels)
{
	m_hbox1.add(m_switch1);
	m_hbox1.add(m_switch2);
	m_hbox1.add(m_switch3);
	m_hbox1.add(m_switch4);
	m_hbox1.add(m_switch5);
	m_vbox.add(m_hbox1);
	m_vbox.add(*Gtk::manage(new Gtk::Label("Knobs")));
	m_hbox_knobs.add(m_smallknob);
	m_smallknob.set_show_value(true);
	m_hbox_knobs.add(m_bigknob);
	m_hbox_knobs.add(m_midknob);
	m_hbox_knobs.add(m_smallknob_r);
	m_vbox.add(m_hbox_knobs);
	m_vbox.add(*Gtk::manage(new Gtk::Label("Sliders")));
	m_eqslider.set_show_value(true);
	m_eqslider.set_value_position(Gtk::POS_RIGHT);
	m_hbox_sliders.add(m_eqslider);
	m_v_slider.set_value_position(Gtk::POS_RIGHT);
	m_hbox_sliders.add(m_v_slider);
	m_hbox_sliders.add(m_mini_slider);
	m_vbox.add(m_hbox_sliders);
	m_vbox.add(m_h_slider);
	m_vbox.add(*Gtk::manage(new Gtk::Label("Wheels")));
	m_v_wheel.set_value_position(Gtk::POS_RIGHT);
	m_hbox_wheels.add(m_v_wheel);
	m_vbox.add(m_hbox_wheels);
	m_vbox.add(m_wheel);
	m_vbox.add(*Gtk::manage(new Gtk::Label("Playhead")));
	m_vbox.add(m_playhead);

	m_vbox.add(*Gtk::manage(new Gtk::Label("Selector")));
	auto store = Gtk::TreeStore::create(m_selector_model);
	auto iter = store->append();
	iter->set_value(m_selector_model.m_col_text, Glib::ustring("Foo"));
	iter = store->append();
	iter->set_value(m_selector_model.m_col_text, Glib::ustring("Bar"));
	m_selector.set_model(store);
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
