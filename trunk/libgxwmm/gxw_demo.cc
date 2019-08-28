#include <glibmm.h>
#include <gtkmm/main.h>
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/treestore.h>
#include <gtkmm/stack.h>
#include <gtkmm/stacksidebar.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/switch.h>
#include <gtkmm/settings.h>
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
#include <gxwmm/portdisplay.h>
#include <gxwmm/minislider.h>
#include <gxwmm/playhead.h>
#include <gxwmm/fastmeter.h>
#include <gxwmm/tuner.h>
#include <gxwmm/racktuner.h>
#include <gxwmm/waveview.h>
#include <gxwmm/iredit.h>
#include <gxwmm/radiobutton.h>
#include <gxwmm/paintbox.h>


// The paint functions as found in GxPaintBox
static const char* s_paint_funcs[] = {
	"rectangle_skin_color_expose",
	"rack_unit_expose",
	"rack_unit_shrink_expose",
	"rack_amp_expose",
	"zac_expose",
	"gxhead_expose",
	"RackBox_expose",
	"gxrack_expose",
	"compressor_expose",
	"simple_level_meter_expose",
	"level_meter_expose",
	"amp_skin_expose",
	"gx_rack_unit_expose",
	"gx_rack_unit_shrink_expose",
	"gx_rack_amp_expose",
	"gx_lv2_unit_expose",
	"draw_skin",
	"rack_expose",
	"box_uni_1_expose",
	"box_uni_2_expose",
	"box_skin_expose",
	"live_box_expose",
	"logo_expose",
	nullptr
};

// Frequencies for the tuner.
static double s_freq[] = {
	82.41,   // E2 E
	110.00,  // A2 A
	146.83,  // D3 D
	196.00,  // G3 G
	246.94,  // B3 B
	329.63   // E4 e
};

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
	Gtk::HBox m_root_box;
	Gtk::StackSidebar m_stacksidebar;
	Gtk::Stack m_stack;

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
	Gxw::PortDisplay m_portdisplay;

	Gtk::HBox m_hbox_wheels;
	Glib::RefPtr<Gtk::Adjustment> m_adj_wheels;
	Gxw::Wheel m_wheel;
	Gxw::WheelVertical m_v_wheel;

	Gtk::VBox m_vbox2;
	Gxw::Selector m_selector;
	Gtk::RadioButtonGroup m_group;
	Gxw::RadioButton m_radiobutton1;
	Gxw::RadioButton m_radiobutton2;
	Gxw::PlayHead m_playhead;
	float m_playhead_value;

	Gtk::VBox m_vbox3;
	Gxw::FastMeter m_fastmeter;
	float m_meter_value;
	Gxw::Tuner m_tuner;
	Gxw::RackTuner m_racktuner;
	int m_freq_index;
	Gxw::WaveView m_waveviewer;

	Gtk::VBox m_vbox4;
	Gxw::IREdit m_iredit;

	Gtk::VBox m_rack;
	Gxw::PaintBox m_rack_unit;
	Gxw::PaintBox m_rack_amp;
	Gxw::PaintBox m_gxhead;

	Gtk::ComboBoxText m_unit_selector;
	Gxw::PaintBox m_custom_unit;
};

Demo::Demo():
	m_root_box(),
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
	m_portdisplay(m_adj_sliders),
	m_adj_wheels(Gtk::Adjustment::create(0, -1, 1, 0.01, 0.1)),
	m_wheel(m_adj_wheels),
	m_v_wheel(m_adj_wheels),
	m_playhead_value(0.0),
	m_meter_value(0.5),
	m_freq_index(0)
{
	// Stack setup
	Gtk::Box *vbox = new Gtk::Box(Gtk::ORIENTATION_VERTICAL);
	vbox->pack_start(m_stacksidebar, true, true);
	Gtk::Box *hbox = new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL);
	Gtk::Label *label = new Gtk::Label("Dark UI");
	label->set_xalign(0.0);
	hbox->pack_start(*manage(label), true, true);
	Gtk::Switch *dark = new Gtk::Switch();
	auto settings = Gtk::Settings::get_default();
	dark->set_state(settings->property_gtk_application_prefer_dark_theme().get_value());
	settings->property_gtk_application_prefer_dark_theme().signal_changed().connect(
		[dark, settings] () {
			dark->set_state(settings->property_gtk_application_prefer_dark_theme().get_value());
		});
	dark->property_active().signal_changed().connect(
		[dark, settings] () {
			settings->property_gtk_application_prefer_dark_theme() = dark->get_state();
		});
	hbox->pack_start(*manage(dark), false, true);
	vbox->pack_start(*manage(hbox), false, true, 4);
	m_root_box.add(*manage(vbox));
	m_stack.set_transition_type(Gtk::STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT);
	m_stacksidebar.set_stack(m_stack);
	m_root_box.add(m_stack);

	// Switches & Knobs
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
	m_hbox_sliders.add(m_portdisplay);
	m_vbox.add(m_hbox_sliders);
	m_vbox.add(m_h_slider);
	m_vbox.add(*Gtk::manage(new Gtk::Label("Wheels")));
	m_v_wheel.set_value_position(Gtk::POS_RIGHT);
	m_hbox_wheels.add(m_v_wheel);
	m_hbox_wheels.add(m_wheel);
	m_vbox.add(m_hbox_wheels);
	m_stack.add(m_vbox, "switches", "Switches");

	// Selector & playhead
	m_vbox2.set_valign(Gtk::ALIGN_START);
	m_vbox2.add(*Gtk::manage(new Gtk::Label("Playhead")));
	auto adj = m_playhead.get_adjustment();
	adj->set_upper(1.0);
	Glib::signal_timeout().connect(
		[this] () {
			float delta = 0.25 - ((float)random() / (2 * (float)RAND_MAX));
			this->m_playhead_value = std::max(0.0f, std::min(this->m_playhead_value + delta, 1.0f));
			this->m_playhead.cp_set_value(this->m_playhead_value);
			return true;
		}, 500);
	m_vbox2.add(m_playhead);

	m_vbox2.add(*Gtk::manage(new Gtk::Label("Radio Buttons")));
	m_radiobutton1.set_label("Test");
	m_radiobutton1.set_group(m_group);
	m_radiobutton1.property_base_name() = "led";
	m_radiobutton2.set_label("Test 2");
	m_radiobutton2.set_group(m_group);
	m_radiobutton2.property_base_name() = "minitoggle";
	m_vbox2.add(m_radiobutton1);
	m_vbox2.add(m_radiobutton2);
	m_vbox2.add(*Gtk::manage(new Gtk::Label("Selector")));
	auto store = Gtk::TreeStore::create(m_selector_model);
	auto iter = store->append();
	iter->set_value(m_selector_model.m_col_text, Glib::ustring("Foo"));
	iter = store->append();
	iter->set_value(m_selector_model.m_col_text, Glib::ustring("Bar"));
	m_selector.set_model(store);
	m_vbox2.add(m_selector);
	m_stack.add(m_vbox2, "selector", "Selector & Playhead");

	// Viewers
	m_vbox3.set_valign(Gtk::ALIGN_START);
	m_vbox3.add(*Gtk::manage(new Gtk::Label("Fast Meter")));
	m_fastmeter.property_horiz() = true;
	m_fastmeter.set_hold_count(3);
	m_fastmeter.set(m_meter_value);
	m_vbox3.add(m_fastmeter);
	Glib::signal_timeout().connect(
		[this] () {
			float delta = 0.25 - ((float)random() / (2 * (float)RAND_MAX));
			this->m_meter_value = std::max(0.0f, std::min(this->m_meter_value + delta, 1.0f));
			this->m_fastmeter.set(this->m_meter_value);
			return true;
		}, 500);
	m_vbox3.add(*Gtk::manage(new Gtk::Label("Tuner")));
	m_vbox3.add(m_tuner);
	m_vbox3.add(*Gtk::manage(new Gtk::Label("Rack Tuner")));
	m_vbox3.add(m_racktuner);
	Glib::signal_timeout().connect(
		[this] () {
			this->m_freq_index++;
			if (this->m_freq_index >= 6) {
				this->m_freq_index = 0;
			}
			double error = 1 + (0.25 - ((float)random() / (2 * (float)RAND_MAX))) / 100.;
			this->m_tuner.set_freq(s_freq[this->m_freq_index] * error);
			this->m_racktuner.set_freq(s_freq[this->m_freq_index] * error);
			return true;
		}, 500);

	m_vbox3.add(*Gtk::manage(new Gtk::Label("Wave Viewer")));
	m_waveviewer.set_text("Sample wave", Gtk::CORNER_TOP_LEFT);
	m_waveviewer.set_text("Hz", Gtk::CORNER_BOTTOM_RIGHT);
	m_waveviewer.property_text_pos_left() = 1.5;
	m_waveviewer.property_text_pos_right() = 77;
	m_waveviewer.set_multiplicator(20., 60.);
	static float frame[100];
	for (int i = 0; i < 100; i++) {
		frame[i] = sin((float)i);
	}
	m_waveviewer.set_frame(frame, 100);
	m_vbox3.add(m_waveviewer);
	m_stack.add(m_vbox3, "fastmeter", "Viewer");

	// IR Edit
	m_vbox4.set_valign(Gtk::ALIGN_START);
	m_vbox4.add(*Gtk::manage(new Gtk::Label("IR Edit")));
	m_iredit.set_ir_data(0, 0, 0, 0);
	m_iredit.property_no_data_text() = "No data";
	m_iredit.property_height_request() = 100;
	m_iredit.set_channel(1);
	m_vbox4.pack_start(m_iredit, true, true);
	Gtk::Button *btn = new Gtk::Button("Load");
	btn->signal_clicked().connect(
		[this] () {
			float buffer[100];
			for (int i = 0; i < 100; i++) {
				buffer[i] = - (float)i;
			}
			this->m_iredit.set_state(buffer, 1, 100, 10, 0, 100, 0, m_iredit.get_gain());
		});
	m_vbox4.add(*manage(btn));
	m_stack.add(m_vbox4, "irdedit", "IR Edit");

	// Rack
	m_rack_unit.property_paint_func() = "rack_unit_expose";
	m_rack.add(m_rack_unit);
	m_rack_amp.property_paint_func() = "rack_amp_expose";
	m_rack.add(m_rack_amp);
	m_gxhead.property_paint_func() = "gxhead_expose";
	m_rack.add(m_gxhead);
	const char** p = s_paint_funcs;
	while (*p) {
		m_unit_selector.append(Glib::ustring(*p));
		p++;
	}
	m_unit_selector.signal_changed().connect(
		[this]() {
			this->m_custom_unit.property_paint_func() = this->m_unit_selector.get_active_text();
		});
	m_rack.pack_start(m_unit_selector, false, true);
	m_rack.add(m_custom_unit);

	m_stack.add(m_rack, "rack", "Rack");

	add(m_root_box);
	set_border_width(10);
	show_all();
}

int main (int argc, char *argv[])
{
	Gtk::Main kit(argc, argv);
	Gxw::init();

	Demo demo;
	Gtk::Main::run(demo);

	return 0;
}
