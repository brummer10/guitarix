#include "guitarix.h"        // NOLINT

#include <glibmm/i18n.h>     // NOLINT

// -------- the gx_head user interface build instruktions

namespace gx_gui {

// Stock Items for Gxw::Switch

const char *sw_led =             "led";
const char *sw_switch =          "switch";
const char *sw_switchit =        "switchit";
const char *sw_minitoggle =      "minitoggle";
const char *sw_button =          "button";
const char *sw_pbutton =         "pbutton";
const char *sw_rbutton =         "rbutton";

// Paint Functions for Gxw::PaintBox

const char *pb_amp_expose =                  "amp_expose";
const char *pb_conv_widget_expose =          "conv_widget_expose";
const char *pb_upper_widget_expose =         "upper_widget_expose";
const char *pb_rectangle_expose =            "rectangle_expose";
const char *pb_rectangle_skin_color_expose = "rectangle_skin_color_expose";
const char *pb_convolver_icon_expose =       "convolver_icon_expose";
const char *pb_AmpBox_expose =               "AmpBox_expose";
const char *pb_tribal_box_expose =           "tribal_box_expose";
const char *pb_vbox_expose =                 "vbox_expose";
const char *pb_filter_box_expose =           "filter_box_expose";
const char *pb_plug_box_expose =             "plug_box_expose";
const char *pb_info_box_expose_on =          "info_box_expose_on";
const char *pb_info_box_expose_off =         "info_box_expose_off";
const char *pb_slooper_expose =              "slooper_expose";
const char *pb_zac_expose =                  "zac_expose";
const char *pb_gxhead_expose =               "gxhead_expose";
const char *pb_RackBox_expose =              "RackBox_expose";
const char *pb_gxrack_expose =               "gxrack_expose";
const char *pb_eq_expose =                   "eq_expose";
const char *pb_main_expose =                 "main_expose";
const char *pb_level_meter_expose =          "level_meter_expose";


int precision(double n) {
    if (n < 0.009999)
        return 3;
    else if (n < 0.099999)
        return 2;
    else if (n < 0.999999)
        return 1;
    else
        return 0;
}

string fformat(float value, float step) {
    ostringstream buf;
    buf << fixed << setprecision(precision(step)) << value;
    return buf.str();
}

uiToggleButton::uiToggleButton(gx_engine::GxMachineBase& machine_, Gtk::ToggleButton* b, const std::string& id_)
    : machine(machine_), id(id_), fButton(b) {
    machine.signal_parameter_value<bool>(id).connect(
	sigc::mem_fun(this, &uiToggleButton::set_value));
}

void uiToggleButton::toggled() {
    machine.set_parameter_value(id, fButton->get_active());
}

void uiToggleButton::set_value(bool v) {
    fButton->set_active(v);
}

bool button_press_cb(GdkEventButton *event, gx_engine::GxMachineBase& machine, const std::string& id) {
    if (event->button == 2) {
	if (!machine.midi_get_config_mode()) {
	    new gx_main_midi::MidiConnect(event, machine.get_parameter(id), machine);
	}
	return true;
    }
    return false;
}


/****************************************************************
 ** class WidgetStack
 */

void WidgetStack::container_add(Gtk::Widget& w) {
    dynamic_cast<Gtk::Container*>(top())->add(w);
}

void WidgetStack::box_pack_start(Gtk::Widget& w, bool expand, bool fill, int padding) {
    dynamic_cast<Gtk::Box*>(top())->pack_start(w, expand, fill, padding);
}

void WidgetStack::notebook_append_page(Gtk::Widget& w, Gtk::Widget& label) {
    dynamic_cast<Gtk::Notebook*>(top())->append_page(w, label);
}

void WidgetStack::add(Gtk::Widget& w, const char *label) {
    Gtk::Widget *t = top();
    Gtk::Notebook *n = dynamic_cast<Gtk::Notebook*>(t);
    if (n) {
	if (!label) {
	    label = "";
	}
	n->append_page(w, *manage(new Gtk::Label(label)));
	return;
    }
    Gtk::Box *b = dynamic_cast<Gtk::Box*>(t);
    if (b) {
	b->pack_start(w, true, true, 0);
	return;
    }
    Gtk::Container *c = dynamic_cast<Gtk::Container*>(t);
    if (c) {
	c->add(w);
	return;
    }
    assert(false);
}

/****************************************************************
 ** class StackBoxBuilder
 */

StackBoxBuilder::StackBoxBuilder(
    gx_engine::GxMachineBase& machine_, Gxw::WaveView &fWaveView_, Gtk::Label &convolver_filename_label_,
    Gtk::Label &convolver_mono_filename_label_, Glib::RefPtr<Gdk::Pixbuf> window_icon_)
    : fBox(), machine(machine_),
      fWaveView(fWaveView_), convolver_filename_label(convolver_filename_label_),
      convolver_mono_filename_label(convolver_mono_filename_label_),
      widget(), accels(), window_icon(window_icon_), next_flags(0) {
}

StackBoxBuilder::~StackBoxBuilder() {
}

void StackBoxBuilder::openVerticalMidiBox(const char* label) {
    openVerticalBox(label);
}

void StackBoxBuilder::prepare() {
    widget = new Gtk::HBox();
    widget->show();
    fBox.push(*manage(widget));
}

#ifndef NDEBUG
void wnotify(gpointer data, GObject *where_the_object_was) {
    printf("WN %p %p\n", where_the_object_was, data);
}

// check if object will be finalized
void trace_finalize(Glib::Object *o, int n) {
    g_object_weak_ref(o->gobj(), wnotify, (gpointer)n);
}
#endif

void StackBoxBuilder::fetch(Gtk::Widget*& mainbox, Gtk::Widget*& minibox) {
    fBox.pop();
    assert(fBox.empty());
    mainbox = widget;
    Glib::ListHandle<Gtk::Widget*> l = widget->get_children();
    if (l.size() == 2) {
	Glib::ListHandle<Gtk::Widget*>::iterator i = l.begin();
	minibox = new Gtk::VBox();
	minibox->show();
	(*i)->show();
	(*i)->reference(); //FIXME can't unmanage widget, reparent unrefs
	(*i)->reparent(*minibox);
    } else {
	minibox = 0;
    }
}

void StackBoxBuilder::get_box(const std::string& name, Gtk::Widget*& mainbox, Gtk::Widget*& minibox) {
    struct {
	const char *name;
	void (StackBoxBuilder::*func)();
    } mapping[] = {
	// mono
	//{ "ampdetail", &StackBoxBuilder::make_rackbox_ampdetail },
	{ "overdrive", &StackBoxBuilder::make_rackbox_overdrive },
	{ "echo", &StackBoxBuilder::make_rackbox_echo },
	{ "delay", &StackBoxBuilder::make_rackbox_delay },
	{ "freeverb", &StackBoxBuilder::make_rackbox_freeverb },
	{ "oscilloscope", &StackBoxBuilder::make_rackbox_oscilloscope },
	{ "low_highpass", &StackBoxBuilder::make_rackbox_low_highpass },
	{ "eqs", &StackBoxBuilder::make_rackbox_eqs },
	{ "eq", &StackBoxBuilder::make_rackbox_peak_eq },
    { "dide", &StackBoxBuilder::make_rackbox_digital_delay },
	{ "didest", &StackBoxBuilder::make_rackbox_digital_delay_st },
	//{ "crybaby", &StackBoxBuilder::make_rackbox_crybaby },
	//{ "gx_distortion", &StackBoxBuilder::make_rackbox_gx_distortion },
	{ "IR", &StackBoxBuilder::make_rackbox_IR },
	{ "compressor", &StackBoxBuilder::make_rackbox_compressor },
    { "expander", &StackBoxBuilder::make_rackbox_expander },
	{ "biquad", &StackBoxBuilder::make_rackbox_biquad },
	//{ "tremolo", &StackBoxBuilder::make_rackbox_tremolo },
	{ "phaser_mono", &StackBoxBuilder::make_rackbox_phaser_mono },
	{ "chorus_mono", &StackBoxBuilder::make_rackbox_chorus_mono },
	{ "flanger_mono", &StackBoxBuilder::make_rackbox_flanger_mono },
	{ "feedback", &StackBoxBuilder::make_rackbox_feedback },
	//{ "amp.tonestack", &StackBoxBuilder::make_rackbox_amp_tonestack },
	{ "cab", &StackBoxBuilder::make_rackbox_cab },
    { "pre", &StackBoxBuilder::make_rackbox_pre },
    { "highbooster", &StackBoxBuilder::make_rackbox_highbooster },
	{ "jconv_mono", &StackBoxBuilder::make_rackbox_jconv_mono },
	{ "midi_out", &StackBoxBuilder::make_rackbox_midi_out },
	// stereo
	{ "chorus", &StackBoxBuilder::make_rackbox_chorus },
	{ "flanger", &StackBoxBuilder::make_rackbox_flanger },
	{ "phaser", &StackBoxBuilder::make_rackbox_phaser },
	{ "stereodelay", &StackBoxBuilder::make_rackbox_stereodelay },
	{ "stereoecho", &StackBoxBuilder::make_rackbox_stereoecho },
	{ "moog", &StackBoxBuilder::make_rackbox_moog },
	{ "ampmodul", &StackBoxBuilder::make_rackbox_ampmodul },
	{ "tonemodul", &StackBoxBuilder::make_rackbox_tonemodul },
	{ "jconv", &StackBoxBuilder::make_rackbox_jconv },
	{ "stereoverb", &StackBoxBuilder::make_rackbox_stereoverb }
    };
    mainbox = minibox = 0;
    for (unsigned int i = 0; i < sizeof(mapping) / sizeof(mapping[0]); ++i) {
	if (name == mapping[i].name) {
	    prepare();
	    (this->*mapping[i].func)();
	    fetch(mainbox, minibox);
	}
    }
}

void StackBoxBuilder::loadRackFromGladeData(const char *xmldesc) {
    const char *ids[] = { "rackbox", "minibox", 0 };
    Glib::RefPtr<GxBuilder> bld = GxBuilder::create_from_string(xmldesc, &machine, ids);
    Gtk::Widget* w;
    bld->find_widget("minibox", w);
    if (w) {
	addWidget("", w);
    }
    bld->find_widget("rackbox", w);
    if (!w) {
        gx_system::gx_print_error("load_ui Error", "can't find widget 'rackbox'");
	return;
    }
    addWidget("", w);
}

Gtk::Widget* StackBoxBuilder::addWidget(const char* label, Gtk::Widget* w) {
    fBox.add(*w, label);
    w->show();
    return w;
}

void StackBoxBuilder::addwidget(Gtk::Widget *widget) {
    if (widget) {
	fBox.container_add(*manage(widget));
    }
    next_flags = 0;
}

void StackBoxBuilder::addSmallJConvFavButton(const char* label, gx_jconv::IRWindow *irw) {
    Gtk::Button *button = new Gtk::Button();
    button->set_name("smallbutton");
    Gtk::Label *lab = new Gtk::Label(label);
    Pango::FontDescription font = lab->get_style()->get_font();
    font.set_size(7*Pango::SCALE);
    font.set_weight(Pango::WEIGHT_NORMAL);
    lab->modify_font(font);
    button->add(*manage(lab));
    lab->set_name("rack_label");
    lab->set_padding(5,0);
    addWidget(label, button);
    lab->show();
    button->signal_clicked().connect(
	sigc::mem_fun(*irw, &gx_jconv::IRWindow::reload_and_show));
}

void StackBoxBuilder::set_convolver_filename(const gx_engine::GxJConvSettings *jcs) {
    convolver_filename_label.set_label(jcs->getIRFile());
}

void StackBoxBuilder::set_convolver_mono_filename(const gx_engine::GxJConvSettings *jcs) {
    convolver_mono_filename_label.set_label(jcs->getIRFile());
}

void StackBoxBuilder::openSetLabelBox() {
    Gtk::VBox *box =  new Gtk::VBox();
    box->set_homogeneous(false);
    box->set_spacing(0);
    box->set_border_width(0);
    convolver_filename_label.set_name("beffect_label");
    Pango::FontDescription font = convolver_filename_label.get_style()->get_font();
    font.set_size(8*Pango::SCALE);
    font.set_weight(Pango::WEIGHT_BOLD);
    convolver_filename_label.modify_font(font);
    box->pack_start(convolver_filename_label, false, false, 0);
    box->show_all();
    gx_engine::JConvParameter *jcp = dynamic_cast<gx_engine::JConvParameter*>(&machine.get_parameter("jconv.convolver"));
    assert(jcp);
    convolver_filename_label.set_label(jcp->get_value().getIRFile());
    jcp->signal_changed().connect(
	sigc::mem_fun(*this, &StackBoxBuilder::set_convolver_filename));
    fBox.box_pack_start(*manage(box), false);
    fBox.push(*box);
}

void StackBoxBuilder::openSetMonoLabelBox() {
    Gtk::VBox *box =  new Gtk::VBox();
    box->set_homogeneous(false);
    box->set_spacing(0);
    box->set_border_width(0);
    convolver_mono_filename_label.set_name("beffect_label");
    Pango::FontDescription font = convolver_mono_filename_label.get_style()->get_font();
    font.set_size(8*Pango::SCALE);
    font.set_weight(Pango::WEIGHT_BOLD);
    convolver_mono_filename_label.modify_font(font);
    box->pack_start(convolver_mono_filename_label, true, false, 0);
    box->show_all();
    gx_engine::JConvParameter *jcp = dynamic_cast<gx_engine::JConvParameter*>(&machine.get_parameter("jconv_mono.convolver"));
    assert(jcp);
    convolver_mono_filename_label.set_label(jcp->get_value().getIRFile());
    jcp->signal_changed().connect(
	sigc::mem_fun(*this, &StackBoxBuilder::set_convolver_mono_filename));
    fBox.box_pack_start(*manage(box));
    fBox.push(*box);
}

void StackBoxBuilder::addJConvButton(const char* label, gx_jconv::IRWindow *irw) {
    Gtk::Button *button = new Gtk::Button();
    button->set_can_default(false);
    button->set_can_focus(false);
    Gtk::Label *lab = new Gtk::Label(label);
    Pango::FontDescription font = lab->get_style()->get_font();
    font.set_size(10*Pango::SCALE);
    font.set_weight(Pango::WEIGHT_NORMAL);
    lab->modify_font(font);
    button->add(*manage(lab));
    lab->set_name("beffekt_label");
    Gtk::Alignment *al = new Gtk::Alignment(0.0, 0.5, 0.0, 0.0);
    al->add(*manage(button));
    al->show_all();
    fBox.box_pack_start(*manage(al), false);
    button->signal_clicked().connect(
	sigc::mem_fun(*irw, &gx_jconv::IRWindow::reload_and_show));
}

void StackBoxBuilder::set_next_flags(int flags) {
    next_flags = flags;
}

void StackBoxBuilder::create_selector(string id, const char *widget_name) {
    gx_engine::Parameter& p = machine.get_parameter(id);
    UiSelectorBase *s;
    if (p.isFloat()) {
        s = new UiSelector<float>(machine, id);
    } else {
        s = new UiSelector<int>(machine, id);
    }
    if (widget_name) {
	s->set_name(widget_name);
    }
    addwidget(s->get_widget());
}

void StackBoxBuilder::create_selector_with_caption(string id, const char *label) {
    gx_engine::Parameter& p = machine.get_parameter(id);
    UiSelectorBase *s;
    if (p.isFloat()) {
        s = new UiSelectorWithCaption<float>(machine, id, label);
    } else {
        s = new UiSelectorWithCaption<int>(machine, id, label);
    }
    addwidget(s->get_widget());
}

void StackBoxBuilder::openSpaceBox(const char* label) {
    GxVBox * box =  new GxVBox();
    box->set_homogeneous(true);
    box->set_spacing(2);
    box->set_border_width(4);
    box->show_all();
    if (!fBox.top_is_notebook() && label && label[0]) {
        fBox.box_pack_start(*box);
        fBox.push(*box);
    } else {
        fBox.push(*addWidget(label, box));
    }
}

void StackBoxBuilder::check_set_flags(Gxw::Regler *r) {
    if (next_flags & UI_NUM_SHOW_ALWAYS) {
	r->set_name("show_always");
    }
    if ((next_flags & UI_NUM_POSITION_MASK)) {
	Gtk::PositionType pos = Gtk::POS_BOTTOM;
	switch (next_flags & UI_NUM_POSITION_MASK) {
	case UI_NUM_TOP: pos = Gtk::POS_TOP; break;
	case UI_NUM_LEFT: pos = Gtk::POS_LEFT; break;
	case UI_NUM_RIGHT: pos = Gtk::POS_RIGHT; break;
	}
	r->set_value_position(pos);
    }
}

void StackBoxBuilder::create_small_rackknob(string id) {
    Gxw::SmallKnob *r = new Gxw::SmallKnob();
    Gtk::Widget *w = UiRackReglerWithCaption::create(machine, r, id);
    check_set_flags(r);
    addwidget(w);
}

void StackBoxBuilder::create_small_rackknob(string id, Glib::ustring label) {
    Gxw::SmallKnob *r = new Gxw::SmallKnob();
    Gtk::Widget *w = UiRackReglerWithCaption::create(machine, r, id, label);
    check_set_flags(r);
    addwidget(w);
}

void StackBoxBuilder::create_small_rackknobr(string id) {
    Gxw::SmallKnobR *r = new Gxw::SmallKnobR();
    Gtk::Widget *w = UiRackReglerWithCaption::create(machine, r, id);
    check_set_flags(r);
    addwidget(w);
}

void StackBoxBuilder::create_small_rackknobr(string id, Glib::ustring label) {
    Gxw::SmallKnobR *r = new Gxw::SmallKnobR();
    Gtk::Widget *w = UiRackReglerWithCaption::create(machine, r, id, label);
    check_set_flags(r);
    addwidget(w);
}

void StackBoxBuilder::addLiveWaveDisplay(const char* label) {
    Gtk::HBox * box      = new Gtk::HBox(false, 4);
    Gtk::VBox * box1     = new Gtk::VBox(false, 0);
    Gtk::VBox * box2     = new Gtk::VBox(false, 0);
    Gtk::EventBox* e_box = new Gtk::EventBox();
    g_signal_connect(box->gobj(), "expose-event", G_CALLBACK(gx_cairo::conv_widget_expose), NULL);
    box->set_size_request(303, 82);
    e_box->set_size_request(284, 54);
    box->set_border_width(12);
    e_box->add(fWaveView);
    box->pack_start(*box1, true, true, 0);
    box->pack_start(*e_box, false, false, 0);
    box->pack_start(*box2, true, true, 0);
    addWidget(label, box);
    fWaveView.hide(); // was show()'n by addWidget
    fWaveView.property_text_pos_left() = 1.5;
    fWaveView.property_text_pos_right() = 77;
    // multiplicator is already set by signal handler
    box->show_all();
}

void StackBoxBuilder::openVerticalBox1(const char* label) {
    GxVBox * box =  new GxVBox();
    box->set_homogeneous(false);
    box->set_spacing(0);
    box->set_border_width(0);

    if (!fBox.top_is_notebook() && label && label[0]) {
        box->m_label.set_text(label);
        box->m_label.set_name("effekt_label");
        box->pack_start(box->m_label, false, false, 0 );
        fBox.box_pack_start(*manage(box));
        box->show();
        box->m_label.show();
        fBox.push(*box);
    } else {
        fBox.push(*addWidget(label, box));
    }
}

void StackBoxBuilder::openVerticalBox2(const char* label) {
    GxVBox * box =  new GxVBox();
    box->set_homogeneous(false);
    box->set_spacing(0);
    box->set_border_width(0);

    if (!fBox.top_is_notebook() && label && label[0]) {
        box->m_label.set_text(label);
        box->m_label.set_name("rack_label");
        box->pack_start(box->m_label, false, false, 0 );
        fBox.box_pack_start(*box);
        box->show();
        box->m_label.show();
        fBox.push(*box);
    } else {
        fBox.push(*addWidget(label, box));
    }
}

void StackBoxBuilder::openFlipLabelBox(const char* label) {
    GxVBox * box =  new GxVBox();
    box->set_homogeneous(false);
    box->set_spacing(0);
    box->set_border_width(0);

    if (!fBox.top_is_notebook() && label && label[0]) {
        GxVBox * vbox =  new GxVBox();
        vbox->set_homogeneous(false);
        vbox->set_spacing(0);
        vbox->set_border_width(0);

        GxHBox * hbox =  new GxHBox();
        hbox->set_homogeneous(false);
        hbox->set_spacing(0);
        hbox->set_border_width(0);

        hbox->m_label.set_text(label);
        hbox->m_label.set_name("effekt_label");
        hbox->m_label.set_angle(90);
        hbox->m_label.set_size_request(15, -1);

        Pango::FontDescription font = hbox->m_label.get_style()->get_font();
        font.set_size(8*Pango::SCALE);
        font.set_weight(Pango::WEIGHT_BOLD);
        hbox->m_label.modify_font(font);

        hbox->add(hbox->m_label);
        hbox->add(*vbox);
        box->add(*hbox);
        fBox.box_pack_start(*box, false);
        box->show_all();
        fBox.push(*vbox);
    } else {
        fBox.push(*addWidget(label, box));
    }
}

void StackBoxBuilder::addNumEntry(const char* label, const char *id, float init, float min,
                                  float max, float step) {
    Gtk::Adjustment* adj = new Gtk::Adjustment(init, min, max, step, 10*step, 0);
    uiAdjustment* c = new uiAdjustment(machine, id, adj);
    adj->signal_value_changed().connect(
	sigc::mem_fun(c, &uiAdjustment::changed));
    Gtk::SpinButton* spinner = new Gtk::SpinButton(*adj, step, precision(step));
    connect_midi_controller(spinner, id, machine);
    Gtk::HBox *box = new Gtk::HBox(homogene, 0);
    Gtk::Label *lab = new Gtk::Label(label);
    box->add(*lab);
    lab->set_name("rack_label");
    addWidget(label, box);
    addWidget(label, spinner);
}

void StackBoxBuilder::addNumEntry(string id, const char* label_) {
    Glib::ustring label(label_);
    if (!machine.parameter_hasId(id)) {
        return;
    }
    const gx_engine::FloatParameter &p = machine.get_parameter(id).getFloat();
    if (label.empty()) {
        label = p.l_name();
    }
    addNumEntry(label.c_str(), id.c_str(), machine.get_parameter_value<float>(id), p.getLowerAsFloat(), p.getUpperAsFloat(), p.getStepAsFloat());
}

void StackBoxBuilder::addMToggleButton(const std::string& id, const char* label_) {
    Glib::ustring label(label_);
    if (!machine.parameter_hasId(id)) {
        return;
    }
    const gx_engine::BoolParameter &p = machine.get_parameter(id).getBool();
    if (label.empty()) {
        label = p.l_name();
    }
    Gdk::Color colorRed("#58b45e");
    Gdk::Color colorOwn("#7f7f7f");
    Gdk::Color colorwn("#000000");
    Gtk::ToggleButton* button = new Gtk::ToggleButton();
    Gtk::Label* lab = new Gtk::Label(label);
    Pango::FontDescription font = lab->get_style()->get_font();
    font.set_weight(Pango::WEIGHT_BOLD);
    lab->modify_font(font);
    button->add(*manage(lab));
    button->set_size_request(70, 20);
    Gtk::Box* box = new Gtk::HBox(homogene, 4);
    Gtk::Box* box1 = new Gtk::VBox(homogene, 4);
    box->set_border_width(0);
    box1->set_border_width(0);
    box->add(*manage(box1));
    Gtk::Box* box2 = new Gtk::VBox(homogene, 4);
    box2->set_border_width(0);
    box2->set_size_request(6, 20);
    box->add(*manage(button));
    box->add(*manage(box2));
    box1->set_size_request(6, 20);
    button->show();
    box1->show();
    box2->show();
    lab->show();
    box->show();
    fBox.container_add(*manage(box));
    uiToggleButton* c = new uiToggleButton(machine, button, id); // FIXME
    button->modify_bg(Gtk::STATE_NORMAL, colorOwn);
    button->modify_bg(Gtk::STATE_ACTIVE, colorRed);
    lab->set_name("rack_label");
    button->signal_toggled().connect(
	sigc::mem_fun(*c, &uiToggleButton::toggled));
    connect_midi_controller(button, id, machine);
}

void StackBoxBuilder::addCheckButton(const char* label, const char *id) {
    Gdk::Color colorRed("#000000");
    Gdk::Color colorOwn("#4c5159");
    Gdk::Color colorba("#c4c0c0");
    Gtk::Label *lab = new Gtk::Label(label);
    Gtk::CheckButton *button = new Gtk::CheckButton();
    button->add(*lab);
    addWidget(label, button);
    button->modify_bg(Gtk::STATE_PRELIGHT, colorOwn);
    button->modify_fg(Gtk::STATE_PRELIGHT, colorRed);
    button->modify_text(Gtk::STATE_NORMAL, colorRed);
    button->modify_base(Gtk::STATE_NORMAL, colorba);
    Glib::RefPtr<Gtk::Style> style = lab->get_style();
    style->get_font().set_size(8*Pango::SCALE);
    style->get_font().set_weight(Pango::WEIGHT_NORMAL);
    lab->modify_font(style->get_font());
    uiCheckButton* c = new uiCheckButton(machine, id, button);
    button->signal_toggled().connect(
	sigc::mem_fun(c, &uiCheckButton::toggled));
    connect_midi_controller(button, id, machine);
    lab->show();
}

void StackBoxBuilder::openHorizontalhideBox(const char* label) {
    GxHBox * box =  new GxHBox();
    box->set_homogeneous(false);
    box->set_spacing(0);
    box->set_border_width(0);
    fBox.box_pack_start(*box , false, false, 5);
    fBox.push(*box);
    box->hide();
    if (label[0] != 0) {
	box->show();
    }
}

void StackBoxBuilder::openHorizontalTableBox(const char* label) {
    GxHBox * box =  new GxHBox();
    box->set_homogeneous(false);
    box->set_spacing(0);
    box->set_border_width(0);

    if (!fBox.top_is_notebook() && label && label[0]) {
        box->m_frame.set_label(label);
        box->m_frame.set_shadow_type(Gtk::SHADOW_NONE);
        box->m_frame.add(*box);
        fBox.box_pack_start(box->m_frame, false);
        box->show();
        box->m_frame.show();
        fBox.push(*box);
    } else {
        fBox.push(*addWidget(label, box));
    }
}

void StackBoxBuilder::openPaintBox2(const char* label) {
    GxEventBox * box =  new GxEventBox();
    box->m_eventbox.set_name(label);
    box->set_homogeneous(false);
    box->set_spacing(0);
    box->set_border_width(0);
    fBox.box_pack_start(box->m_hbox, false, false);
    box->m_hbox.show_all();
    fBox.push(*box);
}

void StackBoxBuilder::openTabBox(const char* label) {
    GxNotebookBox * box =  new GxNotebookBox();
    fBox.push(*addWidget(label, box));
}

void StackBoxBuilder::openpaintampBox(const char* label) {
    GxPaintBox * box =  new GxPaintBox(pb_RackBox_expose);
    box->set_border_width(4);
    box->m_paintbox.set_name(label);
    box->m_paintbox.set_tooltip_text(label);
    fBox.box_pack_start(box->m_paintbox);
    box->m_paintbox.show_all();
    fBox.push(*box);
}

void StackBoxBuilder::addCheckButton(string id, const char* label_) {
    Glib::ustring label(label_);
    if (!machine.parameter_hasId(id)) {
        return;
    }
    const gx_engine::BoolParameter &p = machine.get_parameter(id).getBool();
    if (label.empty()) {
        label = p.l_name();
    }
    addCheckButton(label.c_str(), id.c_str());
}

void StackBoxBuilder::closeBox() {
    assert(!fBox.empty());
    fBox.pop();
}

void StackBoxBuilder::openHorizontalBox(const char* label) {
    GxHBox * box =  new GxHBox();
    box->set_homogeneous(false);
    box->set_spacing(0);
    box->set_border_width(0);

    if (!fBox.top_is_notebook() && label && label[0]) {
        box->m_frame.set_label(label);
        box->m_frame.set_shadow_type(Gtk::SHADOW_NONE);
        box->m_frame.add(*box);
        fBox.box_pack_start(box->m_frame, false);
        box->show();
        box->m_frame.show();
        fBox.push(*box);
    } else {
        fBox.push(*addWidget(label, box));
    }
}

void StackBoxBuilder::openVerticalBox(const char* label) {
    GxVBox * box =  new GxVBox();
    box->set_homogeneous(false);
    box->set_spacing(0);
    box->set_border_width(0);

    if (!fBox.top_is_notebook() && label && label[0]) {
        box->m_label.set_text(label);
        box->m_label.set_name("rack_effect_label");
	Glib::RefPtr<Gtk::Style> style = box->m_label.get_style();
        style->get_font().set_size(8*Pango::SCALE);
        style->get_font().set_weight(Pango::WEIGHT_BOLD);
        box->m_label.modify_font(style->get_font());
        box->pack_start(box->m_label, false, false, 0 );
        fBox.box_pack_start(*box, false);
        box->show();
        box->m_label.show();
        fBox.push(*box);
    } else {
        fBox.push(*addWidget(label, box));
    }
}

void StackBoxBuilder::openFrameBox(const char* label) {
    GxHBox * box =  new GxHBox();
    box->set_homogeneous(false);
    box->set_spacing(2);
    box->set_border_width(2);

    if (!fBox.top_is_notebook() && label && label[0]) {
        box->m_frame.set_label(label);
        box->m_frame.set_shadow_type(Gtk::SHADOW_NONE);
        box->m_frame.add(*box);
        fBox.box_pack_start(box->m_frame, false);
        box->show();
        box->m_frame.show();
        fBox.push(*box);
    } else {
        fBox.push(*addWidget(label, box));
    }
}

} // end namespace gx_gui
