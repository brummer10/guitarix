#include <gxw/GxControlParameter.h>
#include "guitarix.h"        // NOLINT

#include <glibmm/i18n.h>     // NOLINT

// -------- the gx_head user interface build instruktions

namespace gx_gui {

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
 ****************************************************************/

StackBoxBuilder::StackBoxBuilder(
    gx_engine::GxMachineBase& machine_, Glib::RefPtr<Gdk::Pixbuf> window_icon_)
    : fBox(), machine(machine_), widget(), accels(), window_icon(window_icon_),
      next_flags(0), current_plugin(nullptr) {
}

StackBoxBuilder::~StackBoxBuilder() {
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
	minibox->get_style_context()->add_class("minibox");
	minibox->show();
	(*i)->show();
	(*i)->reparent(*minibox);
    } else {
	minibox = 0;
    }
}

/****************************************************************
 * Support for loading from glade files
 *
 * The feature for defining signal connections in the glade file is
 * misused a bit; only the signal handler name is looked at, and its
 * taken as a symbol defining what sort of signal wiring and
 * additional processing is requestet.
 */

static void on_refresh_oscilloscope(Gxw::WaveView& fWaveView, const gx_engine::OscilloscopeInfo& info) {
    static struct  {
        int load, frames;
        jack_nframes_t bsize;
        bool rt;
    } oc;
    if (!oc.bsize || oc.load != info.load) {
        oc.load = info.load;
        fWaveView.set_text(
            (boost::format(_("DSP Load  %1% %%")) % oc.load).str().c_str(),
            Gtk::CORNER_TOP_LEFT);
    }
    if (!oc.bsize || oc.frames != info.frames) {
        oc.frames = info.frames;
        fWaveView.set_text(
            (boost::format(_("HT Frames %1%")) % oc.frames).str().c_str(),
            Gtk::CORNER_BOTTOM_LEFT);
    }
    if (!oc.bsize || oc.rt != info.is_rt) {
        oc.rt = info.is_rt;
        fWaveView.set_text(
            oc.rt ? _("RT Mode  YES ") : _("RT mode  <span color=\"#cc1a1a\">NO</span>"),
            Gtk::CORNER_BOTTOM_RIGHT);
    }
    if (!oc.bsize || oc.bsize != info.bsize) {
	oc.bsize = info.bsize;
        fWaveView.set_text(
            (boost::format(_("Latency    %1%")) % oc.bsize).str().c_str(),
            Gtk::CORNER_TOP_RIGHT);
    }
    fWaveView.queue_draw();
}

/*
 * JConvolver
 */
static void jconv_filelabel(Glib::RefPtr<Glib::Object>& object, gx_engine::GxMachineBase& machine, bool stereo) {
    gx_engine::JConvParameter *jcp = dynamic_cast<gx_engine::JConvParameter*>(
        &machine.get_parameter(stereo ? "jconv.convolver" : "jconv_mono.convolver"));
    assert(jcp);
    Gtk::Label *label = dynamic_cast<Gtk::Label*>(object.get());
    assert(label);
    auto set_convolver_filename = [=](const gx_engine::GxJConvSettings *jcs) { label->set_label(jcs->getIRFile()); };
    set_convolver_filename(&jcp->get_value());
    sigc::connection conn = jcp->signal_changed().connect(set_convolver_filename);
    label->add_destroy_notify_callback(
        new sigc::connection(conn),
        [](void *p) {
            sigc::connection *conn = static_cast<sigc::connection*>(p);
            conn->disconnect();
            delete conn;
            return p;
        });
}

static void jconv_button(Glib::RefPtr<Glib::Object>& object, gx_engine::GxMachineBase& machine,
                         Glib::RefPtr<Gtk::AccelGroup>& accels, Glib::RefPtr<Gdk::Pixbuf>& window_icon,
                         bool stereo) {
    auto *button = dynamic_cast<Gtk::Button*>(object.get());
    assert(button);
    static gx_jconv::IRWindow* ir_windows[2] = { nullptr, nullptr };
    gx_jconv::IRWindow*& irw = ir_windows[stereo ? 1 : 0];
    if (!irw) {
        irw = gx_jconv::IRWindow::create(
            (stereo ? "jconv" : "jconv_mono"), window_icon, machine, accels, (stereo ? 2 : 1));
        button->add_destroy_notify_callback(
            &irw,
            [](void *p) {
                gx_jconv::IRWindow*& irw = *static_cast<gx_jconv::IRWindow**>(p);
                delete irw;
                irw = 0;
                return p;
            });
    }
    button->signal_clicked().connect(
        sigc::mem_fun(*irw, &gx_jconv::IRWindow::reload_and_show));
}

/*
 * Drum Sequencer
 */
static void seq_button(Glib::RefPtr<Glib::Object>& object, gx_engine::GxMachineBase& machine) {
    auto *button = dynamic_cast<Gtk::Button*>(object.get());
    assert(button);
    static gx_seq::SEQWindow *seqw = nullptr;
    if (!seqw) {
        seqw = gx_seq::SEQWindow::create("seq", machine);
        button->add_destroy_notify_callback(
            &seqw,
            [](void *p) {
                gx_seq::SEQWindow*& seqw = *static_cast<gx_seq::SEQWindow**>(p);
                delete seqw;
                seqw = 0;
                return p;
            });
    }
    button->signal_clicked().connect(
        sigc::mem_fun(*seqw, &gx_seq::SEQWindow::reload_and_show));
}

/*
 * Oscilloscope
 */
static void connect_waveview(Glib::RefPtr<Glib::Object>& object, gx_engine::GxMachineBase& machine,
                             PluginUI& plugin) {
    auto w = dynamic_cast<Gxw::WaveView*>(object.get());
    assert(w);
    w->set_multiplicator(20, 60);
    const int conn_len = 3;
    const char *p_id = "oscilloscope.info";
    auto conn = new sigc::connection[conn_len];
    conn[0] = plugin.get_output_widget_state()->connect(
        [=,&machine](bool state) {
            machine.set_update_parameter(w, p_id, state);
            w->set_sensitive(state);
        });
    auto osc = dynamic_cast<gx_engine::OscParameter*>(&machine.get_parameter(p_id));
    conn[1] = osc->signal_changed().connect(
        [w](const gx_engine::OscilloscopeInfo& info) { on_refresh_oscilloscope(*w, info); });
    gx_engine::OscilloscopeInfo& info = osc->get_value();
    w->set_frame(info.get_buffer(), info.get_buffer_size());
    conn[2] = info.signal_size_change().connect(
        [=](unsigned int size, float *buffer){ w->set_frame(buffer, size); });
    w->add_destroy_notify_callback(
        conn,
        [](void*p) {
            sigc::connection *conn = static_cast<sigc::connection*>(p);
            for (int i = 0; i < conn_len; i++) {
                conn->disconnect();
            }
            delete[] conn;
            return p;
        });
}

void StackBoxBuilder::connect_signals(Glib::RefPtr<GxBuilder> builder, Glib::RefPtr<Glib::Object> object,
                                      const char *signal_name, const char *handler_name) {
    /*
     * call function for handler_name
     */
    if (!strcmp(handler_name, "ir_mono_window_reload_and_show")) {
        jconv_button(object, machine, accels, window_icon, false);
    } else if (!strcmp(handler_name, "ir_stereo_window_reload_and_show")) {
        jconv_button(object, machine, accels, window_icon, true);
    } else if (!strcmp(handler_name, "SEQWindow_reload_and_show")) {
        seq_button(object, machine);
    } else if (!strcmp(handler_name, "connect_oscilloscope")) {
        connect_waveview(object, machine, *current_plugin);
    } else if (!strcmp(handler_name, "jconv_mono.convolver:IRFile")) {
        jconv_filelabel(object, machine, false);
    } else if (!strcmp(handler_name, "jconv.convolver:IRFile")) {
        jconv_filelabel(object, machine, true);
    } else {
        gx_print_error(
            "StackBoxBuilder::connect_signals",
            boost::format("glade connect: signal / handler not found: %1% / %2%") % signal_name % handler_name);
    }
}

void StackBoxBuilder::loadRackFromBuilder(const Glib::RefPtr<GxBuilder>& bld) {
    if (!bld->has_object("rackbox")) {
        gx_print_error("load_ui Error", "can't find widget 'rackbox'");
	return;
    }
    gtk_builder_connect_signals_full(
        bld.get()->gobj(),
        [](GtkBuilder *builder, GObject *object, const gchar *signal_name, const gchar *handler_name,
           GObject *connect_object, GConnectFlags flags, gpointer user_data) {
            static_cast<StackBoxBuilder*>(user_data)->connect_signals(
                Glib::RefPtr<GxBuilder>::cast_dynamic(Glib::wrap(builder, true)),
                Glib::wrap(object, true), signal_name, handler_name);
        },
        this);
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
	    machine.get_options().get_builder_filepath(fname), &machine, rackbox_ids,
            current_plugin->get_output_widget_state()));
}

void StackBoxBuilder::loadRackFromGladeData(const char *xmldesc) {
    loadRackFromBuilder(GxBuilder::create_from_string(xmldesc, &machine, rackbox_ids,
                                                      current_plugin->get_output_widget_state()));
}

/****************************************************************
 * stack based building of Rackboxes
 */

void StackBoxBuilder::addwidget(Gtk::Widget *widget) {
    if (widget) {
	fBox.container_add(manage(widget));
    }
    next_flags = 0;
}

void StackBoxBuilder::set_next_flags(int flags) {
    next_flags = flags;
}

void StackBoxBuilder::create_simple_meter(const std::string& id) {
     //FIXME need ui connect, like eg. create_port_display
    Gxw::FastMeter *fastmeter = new Gxw::FastMeter();
    fastmeter->set_hold_count(5);
    fastmeter->property_dimen() = 2;
    fastmeter->property_falloff() = true;
    fastmeter->property_power() = true;
    fastmeter->set_sensitive(false);
    machine.set_update_parameter(fastmeter, id);
    Gtk::HBox *box =  new Gtk::HBox();
    box->set_border_width(2);
    box->pack_start(*Gtk::manage(static_cast<Gtk::Widget*>(fastmeter)),Gtk::PACK_SHRINK);
    box->show_all();
    fBox.box_pack_start(manage(box),false);
}

void StackBoxBuilder::create_simple_c_meter(const std::string& id, const std::string& idm, const char *label) {
    Gxw::FastMeter *fastmeter = new Gxw::FastMeter();
    fastmeter->set_hold_count(5);
    fastmeter->property_dimen() = 2;
    fastmeter->property_power() = true;
    fastmeter->property_falloff() = true;
    fastmeter->set_name("simplemeter");
    Gxw::LevelSlider *w = new UiRegler<Gxw::LevelSlider>(machine, idm);
    w->set_name("lmw");
    GxPaintBox *box =  new GxPaintBox("simple_level_meter_expose");
    box->set_border_width(2);
    box->pack_start(*Gtk::manage(static_cast<Gtk::Widget*>(fastmeter)),Gtk::PACK_SHRINK);
    box->add(*Gtk::manage(static_cast<Gtk::Widget*>(w)));
    if (label && label[0]) {
    Gtk::VBox *boxv =  new Gtk::VBox();
    //boxv->property_orientation() = Gtk::ORIENTATION_VERTICAL;
    boxv->set_homogeneous(false);
    boxv->set_spacing(0);
   // boxv->set_border_width(4);
    Gtk::Label *lab = new Gtk::Label(label);
    lab->get_style_context()->add_class("gx_simple_c_meter_label");
    lab->set_name("beffekt_label");
    boxv->add(*manage(lab));
    boxv->add(*manage(box));
    boxv->show_all();
    fBox.box_pack_start(manage(boxv),false);
    } else {
    box->show_all();
    fBox.box_pack_start(manage(box),false);
    }
}

class UiPortDisplayWithCaption: public UiReglerWithCaption<Gxw::PortDisplay> {
public:
    UiPortDisplayWithCaption(gx_engine::GxMachineBase& machine, const std::string& id)
	: UiReglerWithCaption(machine, id) {}
    void activate_output(bool state);
};

void UiPortDisplayWithCaption::activate_output(bool state) {
    base.machine.set_update_parameter(&regler, regler.cp_get_var(), state);
    regler.set_sensitive(state);
}

void StackBoxBuilder::create_port_display(const std::string& id, const char *label) {
    UiPortDisplayWithCaption *w = new UiPortDisplayWithCaption(machine, id);
    current_plugin->get_output_widget_state()->connect(
        sigc::mem_fun(w, &UiPortDisplayWithCaption::activate_output));
    if (next_flags & UI_LABEL_INVERSE) {
	w->set_rack_label_inverse(label);
    } else {
	w->set_rack_label(label);
    }
    addwidget(w);
}

class UiPDisplay: private CpBase, public Gxw::PortDisplay {
private:
    string idl;
    string idh;
    static int reversed_slider(int v) { return 100 - v; }
public:
    UiPDisplay(gx_engine::GxMachineBase& machine, const std::string& id,
	       const string& idl_, const string& idh_);
    void activate_output(bool state);
};

UiPDisplay::UiPDisplay(gx_engine::GxMachineBase& machine, const std::string& id,
		       const string& idl_, const string& idh_)
    : CpBase(machine, id),
      Gxw::PortDisplay(),
      idl(idl_), idh(idh_) {
    init(*this, false);
    set_cutoff_low(machine.get_parameter_value<float>(idl));
    set_cutoff_high(reversed_slider(machine.get_parameter_value<float>(idh)));
    machine.signal_parameter_value<float>(idl).connect(
	sigc::mem_fun(this, &Gxw::PortDisplay::set_cutoff_low));
    machine.signal_parameter_value<float>(idh).connect(
	sigc::compose(
	    sigc::mem_fun(this, &Gxw::PortDisplay::set_cutoff_high),
	    sigc::ptr_fun(reversed_slider)));
}

void UiPDisplay::activate_output(bool state) {
    machine.set_update_parameter(this, UiPDisplay::cp_get_var(), state);
    machine.set_update_parameter(this, idl, state);
    machine.set_update_parameter(this, idh, state);
    set_sensitive(state);
}

void StackBoxBuilder::create_p_display(const std::string& id, const std::string& idl, const std::string& idh) {
    UiPDisplay *w = new UiPDisplay(machine, id, idl, idh);
    w->get_style_context()->add_class("playhead");
    w->show_all();
    addwidget(w);
    current_plugin->get_output_widget_state()->connect(
        sigc::mem_fun(w, &UiPDisplay::activate_output));
}

class UiFeedbackSwitch: public UiSwitchFloat {
public:
    UiFeedbackSwitch(gx_engine::GxMachineBase& machine, const char *sw_type,
		     gx_engine::FloatParameter &param):
	UiSwitchFloat(machine, sw_type, param) {}
    void activate_output(bool state);
};

void UiFeedbackSwitch::activate_output(bool state) {
    machine.set_update_parameter(this, param.id(), state);
}

void StackBoxBuilder::create_feedback_switch(const char *sw_type, const std::string& id) {
    UiFeedbackSwitch *sw = new UiFeedbackSwitch(machine, sw_type, machine.get_parameter(id).getFloat());
	//sw->set_relief(Gtk::RELIEF_NONE);
	sw->set_name("effect_on_off");
	addwidget(sw);
	current_plugin->get_output_widget_state()->connect(
            sigc::mem_fun(sw, &UiFeedbackSwitch::activate_output));
}

void StackBoxBuilder::load_file(const std::string& id, const std::string& idf) {
	static Glib::ustring recent_filename = "";
	static Glib::ustring hostname = "localhost";
	if (! machine.get_jack()) {
		hostname = Gio::Resolver::get_default()->lookup_by_address
				(Gio::InetAddress::create( machine.get_options().get_rpcaddress()));
	}
    if (machine.parameter_hasId(id)) {
		if (machine.get_parameter_value<bool>(id.substr(0,id.find_last_of(".")+1)+"on_off")) {
			if (machine.get_parameter_value<float>(id)>0) {
				Glib::ustring filename = machine.get_parameter_value<string>(idf);
				Glib::ustring title = hostname + ": Select loop file";
				Gtk::FileChooserDialog d( title);
				d.set_local_only(false);
				d.property_destroy_with_parent().set_value(true);
				d.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
				d.add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);
				Glib::ustring loop_dir = machine.get_options().get_loop_dir();
				d.add_shortcut_folder_uri(Glib::filename_to_uri(loop_dir, hostname));
				Glib::RefPtr<Gtk::FileFilter> wav = Gtk::FileFilter::create();
				wav->set_name("WAV Files");
				wav->add_mime_type("audio/x-vorbis+ogg");
				wav->add_mime_type("audio/x-wav");
				wav->add_pattern("*.ogg");
				wav->add_pattern("*.wav");
				wav->add_pattern("*.WAV");
				wav->add_pattern("*.Wav");
				d.add_filter(wav);
				Glib::RefPtr<Gtk::FileFilter> audio = Gtk::FileFilter::create();
				audio->set_name("Audio Files");
				audio->add_mime_type("audio/*");
				d.add_filter(audio);
				Glib::RefPtr<Gtk::FileFilter> all = Gtk::FileFilter::create();
				all->add_pattern("*");
				all->set_name("All Files");
				d.add_filter(all);
				if (!recent_filename.empty()) {
					d.set_uri(Glib::filename_to_uri (recent_filename, hostname));
				} else if ((filename.find("tape") != Glib::ustring::npos) && (!filename.empty())) {
					d.set_uri(Glib::filename_to_uri (loop_dir + filename + string(".wav"), hostname));
				} else {
					d.set_current_folder_uri(Glib::filename_to_uri (loop_dir, hostname));
				}
				d.signal_response().connect(sigc::bind<Gtk::FileChooserDialog*>(sigc::bind<const std::string>(
					sigc::bind<const std::string>(sigc::mem_fun(*this, &StackBoxBuilder::on_file_chooser_response),idf),id), &d) );
				d.show();
				while(machine.get_parameter_value<float>(id)>0) {
				    //g_main_context_iteration (NULL, true);
					if (Gtk::Main::iteration(false)) {
						machine.set_parameter_value(id,0.0);
						machine.signal_parameter_value<float>(id)(0.0);	
					}
				}
				
			//	if (d.run() != Gtk::RESPONSE_OK) {
			//		machine.set_parameter_value(id,0.0);
			//		machine.signal_parameter_value<float>(id)(0.0);
			//		return;
			//	}
			//	filename = Glib::filename_from_uri(d.get_uri(), hostname);
			//	recent_filename = filename;
			//	Gtk::RecentManager::Data data;
			//	bool result_uncertain;
			//	data.mime_type = Gio::content_type_guess(filename, "", result_uncertain);
			//	data.app_name = "guitarix";
			//	data.groups.push_back("loopfiles");
			//	Gtk::RecentManager::get_default()->add_item(d.get_uri(), data);
			//	machine.set_parameter_value(idf,filename);
			//	machine.set_parameter_value(id,0.0);
			//	machine.signal_parameter_value<float>(id)(0.0);
			}
		}
	}
}

void StackBoxBuilder::on_file_chooser_response(int response_id, Gtk::FileChooserDialog *d, const std::string& id, const std::string& idf)
{
	if( response_id == Gtk::RESPONSE_OK) {
		static Glib::ustring hostname = "localhost";
		if (! machine.get_jack()) {
			hostname = Gio::Resolver::get_default()->lookup_by_address
					(Gio::InetAddress::create( machine.get_options().get_rpcaddress()));
		}
		Glib::ustring filename = Glib::filename_from_uri(d->get_uri(), hostname);
		Glib::ustring recent_filename = filename;
		Gtk::RecentManager::Data data;
		bool result_uncertain;
		data.mime_type = Gio::content_type_guess(filename, "", result_uncertain);
		data.app_name = "guitarix";
		data.groups.push_back("loopfiles");
		Gtk::RecentManager::get_default()->add_item(d->get_uri(), data);
		d->hide();
		machine.set_parameter_value(idf,filename);
		machine.set_parameter_value(id,0.0);
		machine.signal_parameter_value<float>(id)(0.0);	
	} else {
		d->hide();
		machine.set_parameter_value(id,0.0);
		machine.signal_parameter_value<float>(id)(0.0);
	}
 }

void StackBoxBuilder::load_file_f(const std::string& id, const std::string& idf) {
    Glib::signal_timeout().connect_once(
			sigc::bind<const std::string>(sigc::bind<const std::string>(sigc::mem_fun(this, &StackBoxBuilder::load_file), idf), id),100);
}

void StackBoxBuilder::create_fload_switch(const char *sw_type, const std::string& id, const std::string& idf) {
	if (machine.get_jack()) {
		Gtk::Widget *sw = UiSwitch::create(machine, sw_type, id);
		Gxw::Switch *regler = static_cast<Gxw::Switch*>(sw);
		//regler->set_relief(Gtk::RELIEF_NONE);
		regler->set_name("effect_on_off");
		addwidget(sw);
		gx_engine::Parameter& p = machine.get_parameter(id);
		p.signal_changed_float().connect(sigc::hide(
			sigc::bind<const std::string>(sigc::bind<const std::string>(sigc::mem_fun(this, &StackBoxBuilder::load_file_f), idf), id)));
	}
}

void StackBoxBuilder::create_v_switch(const char *sw_type, const std::string& id, const char *label) {
    Gtk::Widget* sw = UiVSwitchWithCaption::create(machine, sw_type, id, label);
    UiVSwitchWithCaption *w = static_cast<UiVSwitchWithCaption*>(sw);
	//w->get_regler()->set_relief(Gtk::RELIEF_NONE);
	w->get_regler()->set_name("effect_on_off");
    if (next_flags & UI_LABEL_INVERSE) {
        w->set_rack_label_inverse();
    }
    addwidget(sw);
}

class UiFeedbackSlider: public UiMasterReglerWithCaption<Gxw::HSlider> {
public:
    UiFeedbackSlider(gx_engine::GxMachineBase& machine, const std::string& id):
	UiMasterReglerWithCaption(machine, id) {}
    void activate_output(bool state);
};

void UiFeedbackSlider::activate_output(bool state) {
    base.machine.set_update_parameter(&regler, regler.cp_get_var(), state);
}

void StackBoxBuilder::create_feedback_slider(const std::string& id, const char *label) {
    UiFeedbackSlider *w = new UiFeedbackSlider(machine, id);
	w->set_label(label);
	addwidget(w);
	current_plugin->get_output_widget_state()->connect(
            sigc::mem_fun(w, &UiFeedbackSlider::activate_output));
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
        UiSelectorWithCaption<float> *sel;
        s = new UiSelectorWithCaption<float>(machine, id, label);
        sel = static_cast<UiSelectorWithCaption<float>*>(s);
        if (next_flags & UI_LABEL_INVERSE) {
            sel->set_rack_label_inverse();
        }
    } else {
        UiSelectorWithCaption<int> *sel;
        s = new UiSelectorWithCaption<int>(machine, id, label);
        sel = static_cast<UiSelectorWithCaption<int>*>(s);
        if (next_flags & UI_LABEL_INVERSE) {
            sel->set_rack_label_inverse();
        }
    }
    addwidget(s);
}

void StackBoxBuilder::openSpaceBox(const char* label) {
    GxVBox * box =  new GxVBox();
    box->set_homogeneous(true);
    box->set_spacing(1);
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

void StackBoxBuilder::create_mid_rackknob(const std::string& id, const char *label) {
    UiReglerWithCaption<Gxw::MidKnob> *w = new UiReglerWithCaption<Gxw::MidKnob>(machine, id);
    if (next_flags & UI_LABEL_INVERSE) {
        w->set_rack_label_inverse(label);
    } else {
        w->set_rack_label(label);
    }
    check_set_flags(w->get_regler());
    addwidget(w);
}

void StackBoxBuilder::create_small_rackknob(const std::string& id, const char *label) {
    UiReglerWithCaption<Gxw::SmallKnob> *w = new UiReglerWithCaption<Gxw::SmallKnob>(machine, id);
    if (next_flags & UI_LABEL_INVERSE) {
        w->set_rack_label_inverse(label);
    } else {
        w->set_rack_label(label);
    }
    check_set_flags(w->get_regler());
    addwidget(w);
}

void StackBoxBuilder::create_small_rackknobr(const std::string& id, const char *label) {
    UiReglerWithCaption<Gxw::SmallKnobR> *w = new UiReglerWithCaption<Gxw::SmallKnobR>(machine, id);
    if (next_flags & UI_LABEL_INVERSE) {
        w->set_rack_label_inverse(label);
    } else {
        w->set_rack_label(label);
    }
    check_set_flags(w->get_regler());
    addwidget(w);
}

void StackBoxBuilder::create_big_rackknob(const std::string& id, const char *label) {
    UiReglerWithCaption<Gxw::BigKnob> *w = new UiReglerWithCaption<Gxw::BigKnob>(machine, id);
    if (next_flags & UI_LABEL_INVERSE) {
        w->set_rack_label_inverse(label);
    } else {
        w->set_rack_label(label);
    }
    check_set_flags(w->get_regler());
    addwidget(w);
}

void StackBoxBuilder::openVerticalBox1(const char* label) {
    GxVBox * box =  new GxVBox();
    box->set_homogeneous(false);
    box->set_spacing(1);
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
    hbox->set_spacing(1);
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

        Pango::FontDescription font = hbox->m_label.get_style_context()->get_font();
        font.set_size(8*Pango::SCALE);
        font.set_weight(Pango::WEIGHT_BOLD);
        hbox->m_label.override_font(font);

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
    box->set_spacing(1);
    box->set_border_width(0);
}

void StackBoxBuilder::openTabBox(const char* label) {
    GxNotebookBox * box =  new GxNotebookBox();
    fBox.push(fBox.add(manage(box), label));
}

void StackBoxBuilder::openpaintampBox(const char* label) {
    GxPaintBox *box =  new GxPaintBox("rectangle_skin_color_expose");
    box->m_hbox.set_border_width(4);
    box->set_name(label);
    GxBuilder::set_tooltip_text_connect_handler(*box, label);
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
    box->set_spacing(1);
    box->set_border_width(0);
}

void StackBoxBuilder::openVerticalBox(const char* label) {
    GxVBox * box =  new GxVBox();
    box->set_homogeneous(false);
    box->set_spacing(1);
    box->set_border_width(0);

    if (!fBox.top_is_notebook() && label && label[0]) {
        box->m_label.set_text(label);
        box->m_label.set_name("rack_effect_label");
        Glib::RefPtr<Gtk::StyleContext> style = box->m_label.get_style_context();
        Pango::FontDescription font = style->get_font();
        font.set_size(8*Pango::SCALE);
        font.set_weight(Pango::WEIGHT_BOLD);
        box->m_label.override_font(font);
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
    box->set_spacing(1);
    box->set_border_width(2);
}

} // end namespace gx_gui
