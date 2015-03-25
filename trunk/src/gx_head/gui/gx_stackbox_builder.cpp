#include "guitarix.h"        // NOLINT

#include <glibmm/i18n.h>     // NOLINT

// -------- the gx_head user interface build instruktions

namespace gx_gui {

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

void WidgetStack::container_add(Gtk::Widget *w) {
    dynamic_cast<Gtk::Container*>(top())->add(*w);
}

void WidgetStack::box_pack_start(Gtk::Widget *w, bool expand, bool fill, int padding) {
    dynamic_cast<Gtk::Box*>(top())->pack_start(*w, expand, fill, padding);
}

void WidgetStack::notebook_append_page(Gtk::Widget *w, Gtk::Widget *label) {
    dynamic_cast<Gtk::Notebook*>(top())->append_page(*w, *label);
}

Gtk::Widget *WidgetStack::add(Gtk::Widget *w, const Glib::ustring& label) {
    w->show();
    Gtk::Widget *t = top();
    Gtk::Notebook *n = dynamic_cast<Gtk::Notebook*>(t);
    if (n) {
	n->append_page(*w, *manage(new Gtk::Label(label)));
	return w;
    }
    Gtk::Box *b = dynamic_cast<Gtk::Box*>(t);
    if (b) {
	b->pack_start(*w, true, true, 0);
	return w;
    }
    Gtk::Container *c = dynamic_cast<Gtk::Container*>(t);
    if (c) {
	c->add(*w);
	return w;
    }
    assert(false);
    return w;
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
    fBox.push(manage(widget));
}

#ifndef NDEBUG
void wnotify(gpointer data, GObject *where_the_object_was) {
    printf("WN %p %p\n", where_the_object_was, data);
}

// check if object will be finalized
void trace_finalize(Glib::Object *o, int n) {
    g_object_weak_ref(o->gobj(), wnotify, GINT_TO_POINTER(n));
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
	{ "oscilloscope", &StackBoxBuilder::make_rackbox_oscilloscope },
	{ "jconv_mono", &StackBoxBuilder::make_rackbox_jconv_mono },
	{ "midi_out", &StackBoxBuilder::make_rackbox_midi_out },
	// stereo
	{ "jconv", &StackBoxBuilder::make_rackbox_jconv },
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

void StackBoxBuilder::loadRackFromBuilder(const Glib::RefPtr<GxBuilder>& bld) {
    if (!bld->has_object("rackbox")) {
        gx_print_error("load_ui Error", "can't find widget 'rackbox'");
	return;
    }
    Gtk::Widget* w;
    if (bld->has_object("minibox")) {
	bld->find_widget("minibox", w);
	fBox.add(w);
    }
    bld->find_widget("rackbox", w);
    fBox.add(w);
}

static const char *rackbox_ids[] = { "rackbox", "minibox", 0 };

void StackBoxBuilder::loadRackFromGladeFile(const char *fname) {
    loadRackFromBuilder(
	GxBuilder::create_from_file(
	    machine.get_options().get_builder_filepath(fname), &machine, rackbox_ids));
}

void StackBoxBuilder::loadRackFromGladeData(const char *xmldesc) {
    loadRackFromBuilder(GxBuilder::create_from_string(xmldesc, &machine, rackbox_ids));
}

void StackBoxBuilder::addwidget(Gtk::Widget *widget) {
    if (widget) {
	fBox.container_add(manage(widget));
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
    fBox.add(manage(button), label);
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
    //font.set_weight(Pango::WEIGHT_BOLD);
    convolver_filename_label.modify_font(font);
    box->pack_start(convolver_filename_label, false, false, 0);
    box->show_all();
    gx_engine::JConvParameter *jcp = dynamic_cast<gx_engine::JConvParameter*>(&machine.get_parameter("jconv.convolver"));
    assert(jcp);
    convolver_filename_label.set_label(jcp->get_value().getIRFile());
    jcp->signal_changed().connect(
	sigc::mem_fun(*this, &StackBoxBuilder::set_convolver_filename));
    fBox.box_pack_start(manage(box), false);
    fBox.push(box);
}

void StackBoxBuilder::openSetMonoLabelBox() {
    Gtk::VBox *box =  new Gtk::VBox();
    box->set_homogeneous(false);
    box->set_spacing(0);
    box->set_border_width(0);
    convolver_mono_filename_label.set_name("beffect_label");
    Pango::FontDescription font = convolver_mono_filename_label.get_style()->get_font();
    font.set_size(8*Pango::SCALE);
    //font.set_weight(Pango::WEIGHT_BOLD);
    convolver_mono_filename_label.modify_font(font);
    box->pack_start(convolver_mono_filename_label, true, false, 0);
    box->show_all();
    gx_engine::JConvParameter *jcp = dynamic_cast<gx_engine::JConvParameter*>(&machine.get_parameter("jconv_mono.convolver"));
    assert(jcp);
    convolver_mono_filename_label.set_label(jcp->get_value().getIRFile());
    jcp->signal_changed().connect(
	sigc::mem_fun(*this, &StackBoxBuilder::set_convolver_mono_filename));
    fBox.box_pack_start(manage(box));
    fBox.push(box);
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
    fBox.box_pack_start(manage(al), false);
    button->signal_clicked().connect(
	sigc::mem_fun(*irw, &gx_jconv::IRWindow::reload_and_show));
}

void StackBoxBuilder::set_next_flags(int flags) {
    next_flags = flags;
}

bool StackBoxBuilder::set_simple(Gxw::FastMeter *fastmeter,const std::string id) {
    if (machine.parameter_hasId(id)) {
    if (machine.get_parameter_value<bool>(id.substr(0,id.find_last_of(".")+1)+"on_off"))
    fastmeter->set_by_power(machine.get_parameter_value<float>(id));
    else
    fastmeter->set_by_power(0.0001);
    return true;
    } else {
    return false;
    }
}

void StackBoxBuilder::create_simple_meter(const std::string& id) {
    Gxw::FastMeter *fastmeter = new Gxw::FastMeter();
    fastmeter->set_hold_count(5);
    fastmeter->set_property("dimen",5);
    Glib::signal_timeout().connect(sigc::bind<Gxw::FastMeter*>(sigc::bind<const std::string>(
      sigc::mem_fun(*this, &StackBoxBuilder::set_simple),id), fastmeter), 60);
    fastmeter->set_by_power(0.0001);
    GxPaintBox *box =  new GxPaintBox(pb_amp_expose);
    box->set_border_width(2);
    box->pack_start(*Gtk::manage(static_cast<Gtk::Widget*>(fastmeter)),Gtk::PACK_SHRINK);
    box->show_all();
    fBox.box_pack_start(manage(box),false);
}

void StackBoxBuilder::create_simple_c_meter(const std::string& id, const std::string& idm, const char *label) {
    Gxw::FastMeter *fastmeter = new Gxw::FastMeter();
    fastmeter->set_hold_count(5);
    fastmeter->set_property("dimen",5);
    Glib::signal_timeout().connect(sigc::bind<Gxw::FastMeter*>(sigc::bind<const std::string>(
      sigc::mem_fun(*this, &StackBoxBuilder::set_simple),id), fastmeter), 60);
    fastmeter->set_by_power(0.0001);
    Gxw::LevelSlider *w = new UiRegler<Gxw::LevelSlider>(machine, idm);
    w->set_name("lmw");
    GxPaintBox *box =  new GxPaintBox("simple_level_meter_expose");
    box->set_border_width(2);
    box->pack_start(*Gtk::manage(static_cast<Gtk::Widget*>(fastmeter)),Gtk::PACK_SHRINK);
    box->add(*Gtk::manage(static_cast<Gtk::Widget*>(w)));
    if (label && label[0]) {
    GxPaintBox *boxv =  new GxPaintBox(pb_eq_expose);
    boxv->set_property("orientation",Gtk::ORIENTATION_VERTICAL);
    boxv->set_homogeneous(false);
    boxv->set_spacing(0);
    boxv->set_border_width(4);
    Gtk::Label *lab = new Gtk::Label(label);
    Pango::FontDescription font = lab->get_style()->get_font();
    font.set_size(6*Pango::SCALE);
    font.set_weight(Pango::WEIGHT_NORMAL);
    lab->modify_font(font);
    lab->set_name("beffekt_label");
    boxv->add(*manage(lab));
    Gtk::VBox *boxvv =  new Gtk::VBox();
    Gtk::HBox *boxl =  new Gtk::HBox();
    boxl->set_homogeneous(false);
    boxl->set_spacing(0);
    boxl->set_border_width(0);
    Gtk::HBox *boxr =  new Gtk::HBox();
    Gtk::HBox *boxs =  new Gtk::HBox();
    boxl->pack_start(*manage(boxr), Gtk::PACK_EXPAND_WIDGET);
    boxl->add(*manage(box));
    boxl->pack_end(*manage(boxs), Gtk::PACK_EXPAND_WIDGET);
    boxvv->add(*manage(boxv));    
    boxvv->add(*manage(boxl));    
    boxvv->show_all();
    fBox.box_pack_start(manage(boxvv),false);
    } else {
    box->show_all();
    fBox.box_pack_start(manage(box),false);
    }
}


bool StackBoxBuilder::set_engine_value(const std::string id) {
    if (machine.parameter_hasId(id)) {
    if (machine.get_parameter_value<bool>(id.substr(0,id.find_last_of(".")+1)+"on_off"))
      machine.signal_parameter_value<float>(id)(machine.get_parameter_value<float>(id));
    return true;
    } else {
    return false;
    }
}

void StackBoxBuilder::create_port_display(const std::string& id, const char *label) {
    CpBaseCaption *w = new UiReglerWithCaption<Gxw::PortDisplay>(machine, id);
    Glib::signal_timeout().connect(sigc::bind<const std::string>(
      sigc::mem_fun(*this, &StackBoxBuilder::set_engine_value),id), 60);
	w->set_rack_label(label);
	addwidget(w);
}

bool StackBoxBuilder::set_pd_value(Gxw::PortDisplay *w, const std::string id, const std::string& idl, const std::string& idh) {
    if (machine.parameter_hasId(id)) {
    if (machine.get_parameter_value<bool>(id.substr(0,id.find_last_of(".")+1)+"on_off")) {
      float low = machine.get_parameter_value<float>(idl);
      float high = 100-machine.get_parameter_value<float>(idh);
      w->set_state(int(low),int(high));
      float set = (low + high)*0.001;
      machine.signal_parameter_value<float>(id)(machine.get_parameter_value<float>(id)+set);
    }
    return true;
    } else {
    return false;
    }
}
    
void StackBoxBuilder::create_p_display(const std::string& id, const std::string& idl, const std::string& idh) {
    Gxw::PortDisplay *w = new UiRegler<Gxw::PortDisplay>(machine, id);
	w->set_name("playhead");
    Gtk::EventBox* e_box = new Gtk::EventBox();
    e_box->set_size_request(-1, -1);
    e_box->set_border_width(0);
    e_box->set_visible_window(true);
    e_box->set_above_child(true);
    e_box->add(*manage(static_cast<Gtk::Widget*>(w)));
    addwidget(e_box);
    e_box->show_all();
    Glib::signal_timeout().connect(sigc::bind<Gxw::PortDisplay*>(sigc::bind<const std::string>(
      sigc::bind<const std::string>(sigc::bind<const std::string>(
      sigc::mem_fun(*this, &StackBoxBuilder::set_pd_value),idh),idl),id),w ), 60);
}

void StackBoxBuilder::create_feedback_switch(const char *sw_type, const std::string& id) {
	addwidget(UiSwitch::create(machine, sw_type, id));
    Glib::signal_timeout().connect(sigc::bind<const std::string>(
      sigc::mem_fun(*this, &StackBoxBuilder::set_engine_value),id), 60);
}

void StackBoxBuilder::create_feedback_slider(const std::string& id, const char *label) {
	UiMasterReglerWithCaption<Gxw::HSlider> *w = new UiMasterReglerWithCaption<Gxw::HSlider>(machine, id);
    Glib::signal_timeout().connect(sigc::bind<const std::string>(
      sigc::mem_fun(*this, &StackBoxBuilder::set_engine_value),id), 60);
	w->set_label(label);
	addwidget(w);
    }

void StackBoxBuilder::create_selector(const std::string& id, const char *widget_name) {
    gx_engine::Parameter& p = machine.get_parameter(id);
    Gxw::Selector *s;
    if (p.isFloat()) {
        s = new UiSelector<float>(machine, id);
    } else {
        s = new UiSelector<int>(machine, id);
    }
    if (widget_name) {
	s->set_name(widget_name);
    }
    addwidget(s);
}

void StackBoxBuilder::create_selector_with_caption(const std::string& id, const char *label) {
    gx_engine::Parameter& p = machine.get_parameter(id);
    Gtk::VBox *s;
    if (p.isFloat()) {
        s = new UiSelectorWithCaption<float>(machine, id, label);
    } else {
        s = new UiSelectorWithCaption<int>(machine, id, label);
    }
    addwidget(s);
}

void StackBoxBuilder::openSpaceBox(const char* label) {
    GxVBox * box =  new GxVBox();
    box->set_homogeneous(true);
    box->set_spacing(2);
    box->set_border_width(4);
    box->show_all();
    if (!fBox.top_is_notebook() && label && label[0]) {
        fBox.box_pack_start(manage(box));
        fBox.push(box);
    } else {
        fBox.push(fBox.add(manage(box), label));
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

void StackBoxBuilder::create_small_rackknob(const std::string& id, const char *label) {
    UiReglerWithCaption<Gxw::SmallKnob> *w = new UiReglerWithCaption<Gxw::SmallKnob>(machine, id);
    w->set_rack_label(label);
    check_set_flags(w->get_regler());
    addwidget(w);
}

void StackBoxBuilder::create_small_rackknobr(const std::string& id, const char *label) {
    UiReglerWithCaption<Gxw::SmallKnobR> *w = new UiReglerWithCaption<Gxw::SmallKnobR>(machine, id);
    w->set_rack_label(label);
    check_set_flags(w->get_regler());
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
    box->pack_start(*manage(box1), true, true, 0);
    box->pack_start(*manage(e_box), false, false, 0);
    box->pack_start(*manage(box2), true, true, 0);
    fBox.add(manage(box), label);
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
        fBox.box_pack_start(manage(box));
        box->show();
        box->m_label.show();
        fBox.push(box);
    } else {
        fBox.push(fBox.add(manage(box), label));
    }
}

void StackBoxBuilder::openVerticalBox2(const char* label) {
    Gtk::VPaned * box =  new Gtk::VPaned();
    box->set_border_width(0);
    GxHBox * pbox =  new GxHBox();
    if (!fBox.top_is_notebook() && label && label[0]) {
        pbox->m_label.set_text(label);
        pbox->m_label.set_name("rack_label");
        pbox->pack_start(pbox->m_label, false, false, 0 );
    }
    pbox->set_border_width(0);
    box->pack1(*Gtk::manage(static_cast<Gtk::Widget*>(pbox)),true,true);
    GxHBox * hbox =  new GxHBox();
    hbox->set_homogeneous(false);
    hbox->set_spacing(0);
    hbox->set_border_width(0);
    box->pack2(*Gtk::manage(static_cast<Gtk::Widget*>(hbox)),true,true);
    box->set_position(200);
    fBox.box_pack_start(manage(box), false, false, 0);
    box->show_all();
    fBox.push(hbox);
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
        //font.set_weight(Pango::WEIGHT_BOLD);
        hbox->m_label.modify_font(font);

        hbox->add(hbox->m_label);
        hbox->add(*manage(vbox));
        box->add(*manage(hbox));
        fBox.box_pack_start(manage(box), false);
        box->show_all();
        fBox.push(vbox);
    } else {
        fBox.push(fBox.add(manage(box), label));
    }
}

class uiSpinner: public Gtk::SpinButton {
private:
    uiAdjustment adj;
public:
    uiSpinner(float step, gx_engine::GxMachineBase& machine, const std::string& id)
	: Gtk::SpinButton(step, precision(step)), adj(machine, id, get_adjustment()) {
	get_adjustment()->signal_value_changed().connect(
	    sigc::mem_fun(adj, &uiAdjustment::changed));
    }
};

void StackBoxBuilder::addNumEntry(const std::string& id, const char* label_) {
    Glib::ustring label(label_);
    if (!machine.parameter_hasId(id)) {
        return;
    }
    const gx_engine::FloatParameter &p = machine.get_parameter(id).getFloat();
    if (label.empty()) {
        label = p.l_name();
    }
    float step = p.getStepAsFloat();
    uiSpinner* spinner = new uiSpinner(step, machine, id);
    spinner->get_adjustment()->configure(
	machine.get_parameter_value<float>(id), p.getLowerAsFloat(), p.getUpperAsFloat(), step, 10*step, 0);
    connect_midi_controller(spinner, id, machine);
    Gtk::HBox *box = new Gtk::HBox(homogene, 0);
    Gtk::Label *lab = new Gtk::Label(label);
    box->add(*manage(lab));
    lab->set_name("rack_label");
    fBox.add(manage(box), label);
    fBox.add(manage(spinner), label);
}

class uiToggleButton: public Gtk::ToggleButton {
private:
    gx_engine::GxMachineBase& machine;
    const std::string id;
public:
    uiToggleButton(gx_engine::GxMachineBase& machine_, const std::string& id_);
    void toggled();
    void set_value(bool v);
};

uiToggleButton::uiToggleButton(gx_engine::GxMachineBase& machine_, const std::string& id_)
    : Gtk::ToggleButton(), machine(machine_), id(id_) {
    machine.signal_parameter_value<bool>(id).connect(
	sigc::mem_fun(this, &Gtk::ToggleButton::set_active));
    signal_toggled().connect(
	sigc::mem_fun(this, &uiToggleButton::toggled));
}

void uiToggleButton::toggled() {
    machine.set_parameter_value(id, get_active());
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
    uiToggleButton* button = new uiToggleButton(machine, id);
    Gtk::Label* lab = new Gtk::Label(label);
    Pango::FontDescription font = lab->get_style()->get_font();
    //font.set_weight(Pango::WEIGHT_BOLD);
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
    fBox.container_add(manage(box));
    button->modify_bg(Gtk::STATE_NORMAL, colorOwn);
    button->modify_bg(Gtk::STATE_ACTIVE, colorRed);
    lab->set_name("rack_label");
    connect_midi_controller(button, id, machine);
}

class uiCheckButton: public Gtk::CheckButton {
private:
    gx_engine::GxMachineBase& machine;
    const std::string& id;
public:
    uiCheckButton(gx_engine::GxMachineBase& machine_, const std::string& id_)
	: Gtk::CheckButton(), machine(machine_), id(id_) {
	set_active(machine.get_parameter_value<bool>(id));
	machine.signal_parameter_value<bool>(id).connect(sigc::mem_fun(this, &Gtk::CheckButton::set_active));
	signal_toggled().connect(
	    sigc::mem_fun(this, &uiCheckButton::toggled));
    }
    void toggled() {
	machine.set_parameter_value(id, get_active());
    }
};

void StackBoxBuilder::addCheckButton(const std::string& id, const char* label_) {
    if (!machine.parameter_hasId(id)) {
        return;
    }
    Glib::ustring label;
    if (label_ && label_[0]) {
	label = label_;
    } else {
        label = machine.get_parameter(id).getBool().l_name();
    }
    Gdk::Color colorRed("#000000");
    Gdk::Color colorOwn("#4c5159");
    Gdk::Color colorba("#c4c0c0");
    Gtk::Label *lab = new Gtk::Label(label);
    uiCheckButton *button = new uiCheckButton(machine, id);
    button->add(*manage(lab));
    fBox.add(manage(button), label);
    button->modify_bg(Gtk::STATE_PRELIGHT, colorOwn);
    button->modify_fg(Gtk::STATE_PRELIGHT, colorRed);
    button->modify_text(Gtk::STATE_NORMAL, colorRed);
    button->modify_base(Gtk::STATE_NORMAL, colorba);
    Glib::RefPtr<Gtk::Style> style = lab->get_style();
    style->get_font().set_size(8*Pango::SCALE);
    style->get_font().set_weight(Pango::WEIGHT_NORMAL);
    lab->modify_font(style->get_font());
    connect_midi_controller(button, id, machine);
    lab->show();
}

void StackBoxBuilder::openHorizontalhideBox(const char* label) {
    GxHBox * box =  new GxHBox();
    box->set_homogeneous(false);
    box->set_spacing(0);
    box->set_border_width(0);
    fBox.box_pack_start(manage(box) , false, false, 5);
    fBox.push(box);
    box->hide();
    if (label[0] != 0) {
	box->show();
    }
}

void StackBoxBuilder::openHorizontalTableBox(const char* label) {
    Gtk::HBox *box;
    if (!fBox.top_is_notebook() && label && label[0]) {
	GxHFrame *frame = new GxHFrame();
        frame->set_label(label);
        frame->set_shadow_type(Gtk::SHADOW_NONE);
        frame->add(frame->m_hbox);
	fBox.box_pack_start(manage(frame), false);
        frame->m_hbox.show();
        frame->show();
	box = &frame->m_hbox;
        fBox.push(box);
    } else {
	box = new Gtk::HBox();
        fBox.push(fBox.add(manage(box), label));
    }
    box->set_homogeneous(false);
    box->set_spacing(0);
    box->set_border_width(0);
}

void StackBoxBuilder::openPaintBox2(const char* label) {
    GxEventBox *box =  new GxEventBox();
    box->m_eventbox.set_name(label);
    box->set_homogeneous(false);
    box->set_spacing(0);
    box->set_border_width(0);
    fBox.box_pack_start(manage(box), false, false);
    box->show_all();
    fBox.push(&box->m_hbox);
}

void StackBoxBuilder::openTabBox(const char* label) {
    GxNotebookBox * box =  new GxNotebookBox();
    fBox.push(fBox.add(manage(box), label));
}

void StackBoxBuilder::openpaintampBox(const char* label) {
    GxPaintBox *box =  new GxPaintBox("box_uni_2_expose");
    box->m_hbox.set_border_width(4);
    box->set_name(label);
    box->set_tooltip_text(label);
    fBox.box_pack_start(manage(box));
    box->show_all();
    fBox.push(&box->m_hbox);
}

void StackBoxBuilder::closeBox() {
    assert(!fBox.empty());
    fBox.pop();
}

void StackBoxBuilder::openHorizontalBox(const char* label) {
    Gtk::HBox *box;
    if (!fBox.top_is_notebook() && label && label[0]) {
	GxHFrame *frame =  new GxHFrame();
        frame->set_label(label);
        frame->set_shadow_type(Gtk::SHADOW_NONE);
        frame->add(frame->m_hbox);
        fBox.box_pack_start(manage(frame), false);
        frame->m_hbox.show();
        frame->show();
	box = &frame->m_hbox;
        fBox.push(box);
    } else {
	box = new Gtk::HBox();
        fBox.push(fBox.add(manage(box), label));
    }
    box->set_homogeneous(false);
    box->set_spacing(0);
    box->set_border_width(0);
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
        //style->get_font().set_weight(Pango::WEIGHT_BOLD);
        box->m_label.modify_font(style->get_font());
        box->pack_start(box->m_label, false, false, 0 );
        fBox.box_pack_start(manage(box), false);
        box->show();
        box->m_label.show();
        fBox.push(box);
    } else {
        fBox.push(fBox.add(manage(box), label));
    }
}

void StackBoxBuilder::openFrameBox(const char* label) {
    Gtk::HBox *box;

    if (!fBox.top_is_notebook() && label && label[0]) {
	GxHFrame *frame = new GxHFrame();
        frame->set_label(label);
        frame->set_shadow_type(Gtk::SHADOW_NONE);
        frame->add(frame->m_hbox);
        fBox.box_pack_start(manage(frame), false);
        frame->m_hbox.show();
        frame->show();
	box = &frame->m_hbox;
        fBox.push(box);
    } else {
	box = new Gtk::HBox();
        fBox.push(fBox.add(manage(box), label));
    }
    box->set_homogeneous(false);
    box->set_spacing(2);
    box->set_border_width(2);
}

} // end namespace gx_gui
