#include <gxw/GxControlParameter.h>
#include "guitarix.h"        // NOLINT

#include <glibmm/i18n.h>     // NOLINT
#include <boost/algorithm/string.hpp>

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
    struct osc_info {
        int load, frames;
        jack_nframes_t bsize;
        bool rt;
        osc_info(): bsize(0) {}
    };
    static const char *osc_info_key = "osc_info";
    osc_info *oc = static_cast<osc_info*>(fWaveView.get_data(osc_info_key));
    if (!oc) {
        oc = new osc_info();
        fWaveView.set_data(osc_info_key, oc,
                           [](void *p){ delete static_cast<osc_info*>(p); });
    }
    if (!oc->bsize || oc->load != info.load) {
        oc->load = info.load;
        fWaveView.set_text(
            (boost::format(_("DSP Load  %1% %%")) % oc->load).str().c_str(),
            Gtk::CORNER_TOP_LEFT);
    }
    if (!oc->bsize || oc->frames != info.frames) {
        oc->frames = info.frames;
        fWaveView.set_text(
            (boost::format(_("HT Frames %1%")) % oc->frames).str().c_str(),
            Gtk::CORNER_BOTTOM_LEFT);
    }
    if (!oc->bsize || oc->rt != info.is_rt) {
        oc->rt = info.is_rt;
        fWaveView.set_text(
            oc->rt ? _("RT Mode  YES ") : _("RT mode  <span color=\"#cc1a1a\">NO</span>"),
            Gtk::CORNER_BOTTOM_RIGHT);
    }
    if (!oc->bsize || oc->bsize != info.bsize) {
        oc->bsize = info.bsize;
        fWaveView.set_text(
            (boost::format(_("Latency    %1%")) % oc->bsize).str().c_str(),
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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wuse-after-free"
    label->add_destroy_notify_callback(
        new sigc::connection(conn),
        [](void *p) {
            sigc::connection *conn = static_cast<sigc::connection*>(p);
            conn->disconnect();
            //delete conn;  //FIXME
            return p;
        });
#pragma GCC diagnostic pop
}


static void nam_filelabel(Glib::RefPtr<Glib::Object>& object, gx_engine::GxMachineBase& machine) {
    Gtk::Label *label = dynamic_cast<Gtk::Label*>(object.get());
    assert(label);
    gx_engine::StringParameter *p = dynamic_cast<gx_engine::StringParameter*>(
        &machine.get_parameter("nam.loadfile"));
    auto set_nam_filename = [=](Glib::ustring s) { label->set_label(s.substr(s.find_last_of("/\\") + 1)); };
    set_nam_filename(p->getString().get_value());
    sigc::connection conne = p->signal_changed().connect(set_nam_filename);
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wuse-after-free"
    label->add_destroy_notify_callback(
        new sigc::connection(conne),
        [](void *p) {
            sigc::connection *conne = static_cast<sigc::connection*>(p);
            conne->disconnect();
           // delete conne;
            return p;
        });
#pragma GCC diagnostic pop
}

static void rtneural_filelabel(Glib::RefPtr<Glib::Object>& object, gx_engine::GxMachineBase& machine) {
    Gtk::Label *label = dynamic_cast<Gtk::Label*>(object.get());
    assert(label);
    gx_engine::StringParameter *p = dynamic_cast<gx_engine::StringParameter*>(
        &machine.get_parameter("rtneural.loadfile"));
    auto set_rtneural_filename = [=](Glib::ustring s) { label->set_label(s.substr(s.find_last_of("/\\") + 1)); };
    set_rtneural_filename(p->getString().get_value());
    sigc::connection conne = p->signal_changed().connect(set_rtneural_filename);
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wuse-after-free"
    label->add_destroy_notify_callback(
        new sigc::connection(conne),
        [](void *p) {
            sigc::connection *conne = static_cast<sigc::connection*>(p);
            conne->disconnect();
            delete conne;
            return p;
        });
#pragma GCC diagnostic pop
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
                conn[i].disconnect();
            }
            delete[] conn;
            return p;
        });
}

/*
 * Livelooper
 */

static void on_file_chooser_response(int response_id, Gxw::Switch *button, Gtk::FileChooserDialog* d,
                                     gx_engine::GxMachineBase& machine, const std::string& id)
{
    if (response_id == Gtk::RESPONSE_OK) {
        Glib::ustring hostname = "localhost";
        Glib::ustring filename = Glib::filename_from_uri(d->get_uri(), hostname);
        Gtk::RecentManager::Data data;
        bool result_uncertain;
        data.mime_type = Gio::content_type_guess(filename, "", result_uncertain);
        data.app_name = "guitarix";
        data.groups.push_back("loopfiles");
        Gtk::RecentManager::get_default()->add_item(d->get_uri(), data);
        machine.set_parameter_value(id, filename);
    }
    button->set_active(false);
}

static Gtk::FileChooserDialog* create_looper_filedialog(Gxw::Switch* button,
                                                        gx_engine::GxMachineBase& machine,
                                                        const std::string& id) {
    auto d = new Gtk::FileChooserDialog("Select loop file");
    d->set_local_only(false);
    d->property_destroy_with_parent().set_value(true);
    d->add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
    d->add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);
    Glib::RefPtr<Gtk::FileFilter> wav = Gtk::FileFilter::create();
    wav->set_name("WAV Files");
    wav->add_mime_type("audio/x-vorbis+ogg");
    wav->add_mime_type("audio/x-wav");
    wav->add_pattern("*.ogg");
    wav->add_pattern("*.wav");
    wav->add_pattern("*.WAV");
    wav->add_pattern("*.Wav");
    d->add_filter(wav);
    Glib::RefPtr<Gtk::FileFilter> audio = Gtk::FileFilter::create();
    audio->set_name("Audio Files");
    audio->add_mime_type("audio/*");
    d->add_filter(audio);
    Glib::RefPtr<Gtk::FileFilter> all = Gtk::FileFilter::create();
    all->add_pattern("*");
    all->set_name("All Files");
    d->add_filter(all);
    d->signal_response().connect(
        [=,&machine](int response) {
            on_file_chooser_response(response, button, d, machine, id); });
    d->add_shortcut_folder_uri(
        Glib::filename_to_uri(machine.get_options().get_loop_dir(), "localhost"));
    return d;
}

static void select_looper_file(Gxw::Switch *w, gx_engine::GxMachineBase& machine, const string& id) {
    assert(w);
    if (!machine.get_jack()) {
        w->hide();
        return;
    }
    gx_engine::Parameter *p = check_get_parameter(machine, id, w);
    if (!p) {
        return;
    }
    if (!p->desc().empty()) {
        GxBuilder::set_tooltip_text_connect_handler(*w, p->l_desc());
    }
    static std::map<std::string, Gtk::FileChooserDialog*> sel_windows;
    Gtk::FileChooserDialog*& sel = sel_windows[id];
    if (!sel) {
        sel = create_looper_filedialog(w, machine, id);
        w->add_destroy_notify_callback(
            &sel,
            [](void *p) {
                Gtk::FileChooserDialog*& sel = *static_cast<Gtk::FileChooserDialog**>(p);
                delete sel;
                sel = 0;
                return p;
            });
    }
    auto on_toggled =
        [=,&machine]() {
            if (!w->get_active()) {
                sel->hide();
                return;
            }
            static Glib::ustring recent_filename = "";
            static Glib::ustring hostname = "localhost";
            Glib::ustring filename = machine.get_parameter_value<string>(id);
            Glib::ustring loop_dir = machine.get_options().get_loop_dir();
            if (!recent_filename.empty()) {
                sel->set_uri(Glib::filename_to_uri (recent_filename, hostname));
            } else if ((filename.find("tape") != Glib::ustring::npos) && (!filename.empty())) {
                sel->set_uri(Glib::filename_to_uri(loop_dir + filename + string(".wav"), hostname));
            } else {
                sel->set_current_folder_uri(Glib::filename_to_uri (loop_dir, hostname));
            }
            sel->show();
        };
    on_toggled();
    w->signal_toggled().connect(on_toggled);
}

/*
* Neural Amp Modeler
*/

static void on_nam_chooser_response(int response_id, Gxw::Switch *button, Gtk::FileChooserDialog* d,
                                     gx_engine::GxMachineBase& machine, const std::string& id)
{
    if (response_id == Gtk::RESPONSE_OK) {
        Glib::ustring hostname = "localhost";
        Glib::ustring filename = Glib::filename_from_uri(d->get_uri(), hostname);
        Gtk::RecentManager::Data data;
        bool result_uncertain;
        data.mime_type = Gio::content_type_guess(filename, "", result_uncertain);
        data.app_name = "guitarix";
        data.groups.push_back("namfiles");
        Gtk::RecentManager::get_default()->add_item(d->get_uri(), data);
        machine.set_parameter_value(id, filename);
    }
    button->set_active(false);
}

static Gtk::FileChooserDialog* create_nam_filedialog(Gxw::Switch* button,
                                                        gx_engine::GxMachineBase& machine,
                                                        const std::string& id) {
    auto d = new Gtk::FileChooserDialog("Select NAM file");
    d->set_local_only(false);
    d->property_destroy_with_parent().set_value(true);
    d->add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
    d->add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);
    Glib::RefPtr<Gtk::FileFilter> wav = Gtk::FileFilter::create();
    wav->set_name("NAM Files");
    wav->add_pattern("*.nam");
    wav->add_pattern("*.json");
    d->add_filter(wav);
    Glib::RefPtr<Gtk::FileFilter> audio = Gtk::FileFilter::create();
    audio->set_name("NAM Files");
    d->add_filter(audio);
    Glib::RefPtr<Gtk::FileFilter> all = Gtk::FileFilter::create();
    all->add_pattern("*");
    all->set_name("All Files");
    d->add_filter(all);
    d->signal_response().connect(
        [=,&machine](int response) {
            on_nam_chooser_response(response, button, d, machine, id); });
    d->add_shortcut_folder_uri(
        Glib::filename_to_uri(machine.get_options().get_loop_dir(), "localhost"));
    return d;
}

std::string getPathName(const std::string& s) {

   char sep = '/';

#ifdef _WIN32
   sep = '\\';
#endif

   size_t i = s.rfind(sep, s.length());
   if (i != std::string::npos) {
      return(s.substr(0, i));
   }

   return("");
}

static void select_nam_file(Gxw::Switch *w, gx_engine::GxMachineBase& machine, const string& id) {
    assert(w);
    if (!machine.get_jack()) {
        w->hide();
        return;
    }
    gx_engine::Parameter *p = check_get_parameter(machine, id, w);
    if (!p) {
        return;
    }
    if (!p->desc().empty()) {
        GxBuilder::set_tooltip_text_connect_handler(*w, p->l_desc());
    }
    static Glib::ustring hostname = "localhost";
    static std::map<std::string, Gtk::FileChooserDialog*> sel_windows;
    Gtk::FileChooserDialog*& sel = sel_windows[id];
    Glib::ustring filename = machine.get_parameter_value<string>(id);
    if (!sel) {
        sel = create_nam_filedialog(w, machine, id);
        w->add_destroy_notify_callback(
            &sel,
            [](void *p) {
                Gtk::FileChooserDialog*& sel = *static_cast<Gtk::FileChooserDialog**>(p);
                delete sel;
                sel = 0;
                return p;
            });
    }

    auto on_toggled =
        [=,&machine]() {
            if (!w->get_active()) {
                sel->hide();
                return;
            }
            static Glib::ustring recent_filename = "";
            static Glib::ustring hostname = "localhost";
            Glib::ustring filename = machine.get_parameter_value<string>(id);
            if (!recent_filename.empty()) {
                sel->set_uri(Glib::filename_to_uri (recent_filename, hostname));
            }
            sel->show();
            if (!filename.empty()) {
                Glib::ustring nam_dir = getPathName(filename);
                if (!nam_dir.empty())
                    sel->set_current_folder_uri(Glib::filename_to_uri (nam_dir, hostname));
            }
        };
    on_toggled();
    w->signal_toggled().connect(on_toggled);
}


/*
* RTNeural
*/

static void on_rtneural_chooser_response(int response_id, Gxw::Switch *button, Gtk::FileChooserDialog* d,
                                     gx_engine::GxMachineBase& machine, const std::string& id)
{
    if (response_id == Gtk::RESPONSE_OK) {
        Glib::ustring hostname = "localhost";
        Glib::ustring filename = Glib::filename_from_uri(d->get_uri(), hostname);
        Gtk::RecentManager::Data data;
        bool result_uncertain;
        data.mime_type = Gio::content_type_guess(filename, "", result_uncertain);
        data.app_name = "guitarix";
        data.groups.push_back("rtneuralfiles");
        Gtk::RecentManager::get_default()->add_item(d->get_uri(), data);
        machine.set_parameter_value(id, filename);
    }
    button->set_active(false);
}

static Gtk::FileChooserDialog* create_rtneural_filedialog(Gxw::Switch* button,
                                                        gx_engine::GxMachineBase& machine,
                                                        const std::string& id) {
    auto d = new Gtk::FileChooserDialog("Select RTNeural file");
    d->set_local_only(false);
    d->property_destroy_with_parent().set_value(true);
    d->add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
    d->add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);
    Glib::RefPtr<Gtk::FileFilter> wav = Gtk::FileFilter::create();
    wav->set_name("RTNeural Files");
    wav->add_pattern("*.aidax");
    wav->add_pattern("*.json");
    d->add_filter(wav);
    Glib::RefPtr<Gtk::FileFilter> all = Gtk::FileFilter::create();
    all->add_pattern("*");
    all->set_name("All Files");
    d->add_filter(all);
    d->signal_response().connect(
        [=,&machine](int response) {
            on_rtneural_chooser_response(response, button, d, machine, id); });
    d->add_shortcut_folder_uri(
        Glib::filename_to_uri(machine.get_options().get_loop_dir(), "localhost"));
    return d;
}

static void select_rtneural_file(Gxw::Switch *w, gx_engine::GxMachineBase& machine, const string& id) {
    assert(w);
    if (!machine.get_jack()) {
        w->hide();
        return;
    }
    gx_engine::Parameter *p = check_get_parameter(machine, id, w);
    if (!p) {
        return;
    }
    if (!p->desc().empty()) {
        GxBuilder::set_tooltip_text_connect_handler(*w, p->l_desc());
    }
    static Glib::ustring hostname = "localhost";
    static std::map<std::string, Gtk::FileChooserDialog*> sel_windows;
    Gtk::FileChooserDialog*& sel = sel_windows[id];
    Glib::ustring filename = machine.get_parameter_value<string>(id);
    if (!sel) {
        sel = create_rtneural_filedialog(w, machine, id);
        w->add_destroy_notify_callback(
            &sel,
            [](void *p) {
                Gtk::FileChooserDialog*& sel = *static_cast<Gtk::FileChooserDialog**>(p);
                delete sel;
                sel = 0;
                return p;
            });
    }

    auto on_toggled =
        [=,&machine]() {
            if (!w->get_active()) {
                sel->hide();
                return;
            }
            static Glib::ustring recent_filename = "";
            static Glib::ustring hostname = "localhost";
            Glib::ustring filename = machine.get_parameter_value<string>(id);
            if (!recent_filename.empty()) {
                sel->set_uri(Glib::filename_to_uri (recent_filename, hostname));
            }
            sel->show();
            if (!filename.empty()) {
                Glib::ustring rtneural_dir = getPathName(filename);
                if (!rtneural_dir.empty())
                    sel->set_current_folder_uri(Glib::filename_to_uri (rtneural_dir, hostname));
            }
        };
    on_toggled();
    w->signal_toggled().connect(on_toggled);
}

static void portdisplay_clip(Gxw::PortDisplay* w, gx_engine::GxMachineBase& machine,
                             const string& idl, const string& idh) {
    assert(w);
    const auto reversed_slider = [](int v){ return 100 - v; };
    w->set_cutoff_low(machine.get_parameter_value<float>(idl));
    w->set_cutoff_high(reversed_slider(machine.get_parameter_value<float>(idh)));
    machine.signal_parameter_value<float>(idl).connect(
        sigc::mem_fun(w, &Gxw::PortDisplay::set_cutoff_low));
    machine.signal_parameter_value<float>(idh).connect(
        sigc::compose(
            sigc::mem_fun(w, &Gxw::PortDisplay::set_cutoff_high),
            reversed_slider));
}

void StackBoxBuilder::connect_signals(Glib::RefPtr<GxBuilder> builder, Glib::RefPtr<Glib::Object> object,
                                      const char *signal_name, const char *handler_name) {
    /*
     * call function for handler_name
     */
    std::vector<string> token;
    boost::split(token, handler_name, [](char c){return c == ' ';}, boost::token_compress_on);
    if (token[0] == "ir_mono_window_reload_and_show") {
        jconv_button(object, machine, accels, window_icon, false);
    } else if (token[0] == "ir_stereo_window_reload_and_show") {
        jconv_button(object, machine, accels, window_icon, true);
    } else if (token[0] == "SEQWindow_reload_and_show") {
        seq_button(object, machine);
    } else if (token[0] == "connect_oscilloscope") {
        connect_waveview(object, machine, *current_plugin);
    } else if (token[0] == "jconv_mono.convolver:IRFile") {
        jconv_filelabel(object, machine, false);
    } else if (token[0] == "jconv.convolver:IRFile") {
        jconv_filelabel(object, machine, true);
    } else if (token[0] == "dubber:load_loop_file") {
        select_looper_file(dynamic_cast<Gxw::Switch*>(object.get()), machine, token[1]);
    } else if (token[0] == "portdisplay:clip") {
        portdisplay_clip(dynamic_cast<Gxw::PortDisplay*>(object.get()), machine, token[1], token[2]);
    } else if (token[0] == "nam:load_nam_file") {
        select_nam_file(dynamic_cast<Gxw::Switch*>(object.get()), machine, token[1]);
    } else if (token[0] == "nam.file") {
        nam_filelabel(object, machine);
    } else if (token[0] == "rtneural:load_json_file") {
        select_rtneural_file(dynamic_cast<Gxw::Switch*>(object.get()), machine, token[1]);
    } else if (token[0] == "rtneural.file") {
        rtneural_filelabel(object, machine);
    } else {
        gx_print_error(
            "StackBoxBuilder::connect_signals",
            boost::format("glade connect: handler not found: %1% [%2%]") % token[0] % signal_name);
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

bool StackBoxBuilder::ui_connect(Gtk::Widget *widget, const std::string& id) {
    return gx_gui::ui_connect(machine, widget, id, current_plugin->get_output_widget_state());
}

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
    ui_connect(fastmeter, id);
    Gtk::HBox *box =  new Gtk::HBox();
    box->set_border_width(2);
    box->pack_start(*Gtk::manage(fastmeter), Gtk::PACK_SHRINK);
    box->show_all();
    fBox.box_pack_start(manage(box),false);
}

void StackBoxBuilder::create_simple_c_meter(const std::string& id, const std::string& idm, const char *label) {
    Gxw::FastMeter *fastmeter = new Gxw::FastMeter();
    fastmeter->set_hold_count(5);
    fastmeter->property_dimen() = 2;
    fastmeter->property_power() = true;
    fastmeter->property_falloff() = true;
    fastmeter->property_orientation() = Gtk::ORIENTATION_VERTICAL;
    fastmeter->set_name("simplemeter");
    ui_connect(fastmeter, id);
    Gxw::LevelSlider *w = new Gxw::LevelSlider();
    w->get_style_context()->add_class("lmw");
    w->property_show_value() = false;
    ui_connect(w, idm);
    GxPaintBox *box =  new GxPaintBox("simple_level_meter_expose");
    box->set_border_width(2);
    box->pack_start(*Gtk::manage(fastmeter), Gtk::PACK_SHRINK);
    box->add(*Gtk::manage(w));
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

void StackBoxBuilder::create_port_display(const std::string& id, const char *label) {
    auto w = new UiReglerWithCaption<Gxw::PortDisplay>();
    if (next_flags & UI_LABEL_INVERSE) {
	w->set_rack_label_inverse(label);
    } else {
	w->set_rack_label(label);
    }
    ui_connect(w->get_regler(), id);
    addwidget(w);
}

void StackBoxBuilder::create_p_display(const std::string& id, const std::string& idl, const std::string& idh) {
    auto w = new UiRegler<Gxw::PortDisplay>();
    w->get_style_context()->add_class("playhead");
    w->show_all();
    ui_connect(w, id);
    portdisplay_clip(w, machine, idl, idh);
    addwidget(w);
}

void StackBoxBuilder::create_feedback_switch(const char *sw_type, const std::string& id) {
    auto sw = new Gxw::Switch(sw_type);
    sw->set_name("effect_on_off");
    sw->show();
    ui_connect(sw, id);
    addwidget(sw);
}

void StackBoxBuilder::create_fload_switch(const char *sw_type, const char *id, const std::string& idf) {
    if (!machine.get_jack()) {
        return;
    }
    auto sw = new Gxw::Switch(sw_type);
    sw->set_name("effect_on_off");
    sw->show();
    if (idf.find("dubber.") != std::string::npos) select_looper_file(sw, machine, idf);
    else if (idf.find("nam.") != std::string::npos) select_nam_file(sw, machine, idf);
    else if (idf.find("rtneural.") != std::string::npos) select_rtneural_file(sw, machine, idf);
    addwidget(sw);
}

void StackBoxBuilder::create_switch_no_caption(const char *sw_type, const std::string& id) {
    auto sw = new Gxw::Switch(sw_type);
    sw->show();
    ui_connect(sw, id);
    addwidget(sw);
}

void StackBoxBuilder::create_v_switch(const char *sw_type, const std::string& id, const char *label) {
    gx_engine::Parameter *p = check_get_parameter(machine, id, nullptr);
    if (!p) {
        return;
    }
    auto sw = new UiVSwitchWithCaption(sw_type, *p, label);
    sw->get_regler()->set_name("effect_on_off");
    if (next_flags & UI_LABEL_INVERSE) {
        sw->set_rack_label_inverse();
    }
    ui_connect(sw->get_regler(), id);
    addwidget(sw);
}

void StackBoxBuilder::create_master_slider(const std::string& id, const char *label) {
    auto w = new UiMasterReglerWithCaption<Gxw::HSlider>();
    w->set_label(label);
    ui_connect(w->get_regler(), id);
    addwidget(w);
}

void StackBoxBuilder::create_feedback_slider(const std::string& id, const char *label) {
    auto w = new UiMasterReglerWithCaption<Gxw::HSlider>();
    w->set_label(label);
    ui_connect(w->get_regler(), id);
    addwidget(w);
}

void StackBoxBuilder::create_selector(const std::string& id, const char *widget_name) {
    auto w = new Gxw::Selector();
    if (widget_name) {
	w->set_name(widget_name);
    }
    ui_connect(w, id);
    addwidget(w);
}

void StackBoxBuilder::create_selector_with_caption(const std::string& id, const char *label) {
    auto s = new UiSelectorWithCaption(label);
    if (next_flags & UI_LABEL_INVERSE) {
        s->set_rack_label_inverse();
    }
    ui_connect(s->get_selector(), id);
    addwidget(s);
}

void StackBoxBuilder::create_wheel(const std::string& id, const char *label) {
    auto w = new UiReglerWithCaption<Gxw::Wheel>();
    w->set_rack_label(label);
    ui_connect(w->get_regler(), id);
    addwidget(w);
}

void StackBoxBuilder::create_spin_value(const std::string& id, const char *label) {
    auto w = new UiDisplayWithCaption<Gxw::ValueDisplay>();
    if (next_flags & UI_LABEL_INVERSE) {
        w->set_rack_label_inverse(label);
    } else {
        w->set_rack_label(label);
    }
    w->get_regler()->set_name("show_always");
    ui_connect(w->get_regler(), id);
    addwidget(w);
}

void StackBoxBuilder::create_simple_spin_value(const std::string& id) {
    auto w = new UiRegler<Gxw::SimpleValueDisplay>();
    w->set_name("show_always");
    ui_connect(w, id);
    addwidget(w);
}

void StackBoxBuilder::create_eq_rackslider_no_caption(const std::string& id) {
    auto w = new UiRegler<Gxw::EqSlider>(true);
    ui_connect(w, id);
    addwidget(w);
}

void StackBoxBuilder::insertSpacer() {
    GxVBox * box =  new GxVBox();
    box->set_homogeneous(true);
    box->set_spacing(1);
    box->set_border_width(4);
    box->show_all();
    fBox.push(fBox.add(manage(box), ""));
    fBox.pop();
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

void StackBoxBuilder::add_regler(CpBaseCaption *w, Gxw::Regler *r, const std::string& id, const char *label) {
    if (next_flags & UI_LABEL_INVERSE) {
        w->set_rack_label_inverse(label);
    } else {
        w->set_rack_label(label);
    }
    check_set_flags(r);
    ui_connect(r, id);
    addwidget(w);
}

void StackBoxBuilder::create_mid_rackknob(const std::string& id, const char *label) {
    auto w = new UiReglerWithCaption<Gxw::MidKnob>();
    add_regler(w, w->get_regler(), id, label);
}

void StackBoxBuilder::create_small_rackknob(const std::string& id, const char *label) {
    auto w = new UiReglerWithCaption<Gxw::SmallKnob>();
    add_regler(w, w->get_regler(), id, label);
}

void StackBoxBuilder::create_small_rackknobr(const std::string& id, const char *label) {
    auto w = new UiReglerWithCaption<Gxw::SmallKnobR>();
    add_regler(w, w->get_regler(), id, label);
}

void StackBoxBuilder::create_big_rackknob(const std::string& id, const char *label) {
    auto w = new UiReglerWithCaption<Gxw::BigKnob>();
    add_regler(w, w->get_regler(), id, label);
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
