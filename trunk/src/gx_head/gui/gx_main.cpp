/*
 * Copyright (C) 2009, 2010 Hermann Meyer, James Warden, Andreas Degert
 * Copyright (C) 2011 Pete Shorthose
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
 * ---------------------------------------------------------------------------
 * ----------------------------------------------------------------------------
 *
 *    This is gx_head main.
 *
 * ----------------------------------------------------------------------------
 */

#include "guitarix.h"       // NOLINT

#ifndef GUITARIX_AS_PLUGIN
#include <gtkmm/main.h>     // NOLINT
#include <gxwmm/init.h>     // NOLINT
#include <condition_variable>
#endif
#include <string>           // NOLINT
#include <thread>

#include "jsonrpc.h"

#ifdef HAVE_AVAHI
#include "avahi_discover.h"
#endif

#ifdef GUITARIX_AS_PLUGIN
#include <glibmm/init.h>

volatile bool sInited = false;

void run_mainloop() {
	Glib::RefPtr<Glib::MainLoop> mainloop(Glib::MainLoop::create(/*Glib::MainContext::create()*/));
	while (!sInited);
	mainloop->run();
}

void gx_inited()
{
	sInited = true;
}

#else
/****************************************************************
 ** class NsmSignals
 **
 ** signal messages from GxNsmHandler to MainWindow
 */

NsmSignals::NsmSignals()
    : nsm_session_control(false) {
}


/****************************************************************
 ** class GxNsmHandler
 **
 ** watch for messages from NSM 
 */

#ifdef HAVE_LIBLO

class GxNsmHandler {
  private:
    gx_system::CmdlineOptions *options;
    NsmSignals *nsmsig;
    int _nsm_open (const char *name, const char *display_name,
            const char *client_id, char **out_msg);
    int _nsm_save ( char **out_msg);
    void _nsm_show ();
    void _nsm_hide ();
    void _on_nsm_is_shown();
    void _on_nsm_is_hidden();
    void _nsm_start_poll();
    bool _poll_nsm();
    nsm_client_t *nsm;
    bool wait_id;

  public:
    bool check_nsm(char *argv[]);
    static int gx_nsm_open (const char *name, const char *display_name,
            const char *client_id, char **out_msg,  void *userdata);
    static int gx_nsm_save ( char **out_msg, void *userdata );
    static void gx_nsm_show ( void *userdata );
    static void gx_nsm_hide ( void *userdata );
    GxNsmHandler(gx_system::CmdlineOptions *options,NsmSignals *nsmsig);
    ~GxNsmHandler();
};

GxNsmHandler::GxNsmHandler(gx_system::CmdlineOptions *options_,NsmSignals *nsmsig_)
    : options(options_),
      nsmsig(nsmsig_),
      nsm(0),
      wait_id(true) {
    nsmsig->signal_trigger_nsm_gui_is_shown().connect(
        sigc::mem_fun(this, &::GxNsmHandler::_on_nsm_is_shown));

    nsmsig->signal_trigger_nsm_gui_is_hidden().connect(
        sigc::mem_fun(this, &GxNsmHandler::_on_nsm_is_hidden));
}

GxNsmHandler::~GxNsmHandler() {
    if (nsm) {
        nsm_free( nsm );
        nsm = 0;
    }
}

bool GxNsmHandler::check_nsm(char *argv[]) {

    const char *nsm_url = getenv( "NSM_URL" );

    if (nsm_url) {
        nsm = nsm_new();
        nsm_set_open_callback( nsm, gx_nsm_open, static_cast<void*>(this));
        nsm_set_save_callback( nsm, gx_nsm_save, static_cast<void*>(this));
        nsm_set_show_callback( nsm, gx_nsm_show, static_cast<void*>(this));
        nsm_set_hide_callback( nsm, gx_nsm_hide, static_cast<void*>(this));
        if ( 0 == nsm_init( nsm, nsm_url)) {
            nsm_send_announce( nsm, "Guitarix", ":optional-gui:", argv[0]);
            int wait_count = 0;
            while(wait_id) {
                nsm_check_wait(nsm,500);
                wait_count +=1;
                if (wait_count > 200) {
                    gx_gui::gx_message_popup("NSM didn't response in time, \nGuitarix will exit now");
                    GxExit::get_instance().exit_program("NSM didn't response, exit now");
                }
            }
            return true;
        } else {
            nsm_free(nsm);
            nsm = 0;
        }
    }
    return false;
}

bool GxNsmHandler::_poll_nsm() {
    if (nsm) {
        nsm_check_nowait(nsm);
        return true;
    }
    return false;
}

void GxNsmHandler::_nsm_start_poll() {
    Glib::signal_timeout().connect(
        sigc::mem_fun(*this, &GxNsmHandler::_poll_nsm),
        200, Glib::PRIORITY_LOW);
}

int GxNsmHandler::_nsm_open (const char *name, const char *display_name,
                            const char *client_id, char **out_msg ) {

    std::string dirpath = name;
    if (dirpath[dirpath.size()-1] != '/') {
        dirpath += "/";
    }

    options->set_user_dir(dirpath);
    options->set_user_IR_dir( Glib::build_filename(dirpath, "IR/"));
    options->set_preset_dir( Glib::build_filename(dirpath, "banks/"));
    options->set_plugin_dir( Glib::build_filename(dirpath, "plugins/"));
    options->set_pluginpreset_dir( Glib::build_filename(dirpath, "pluginpresets/"));
    options->set_lv2_preset_dir( Glib::build_filename(dirpath, "pluginpresets/lv2/"));
    options->set_loop_dir( Glib::build_filename(dirpath, "loops/"));
    options->set_temp_dir( Glib::build_filename(dirpath, "temp/"));

    options->set_hideonquit(true);
    options->set_jack_instancename(client_id);
    options->set_jack_noconnect(true);
    options->set_jack_single(true);
    options->set_opt_autosave(false);
    options->read_ui_vars();
    if (!strstr(nsm_get_session_manager_features(nsm), ":optional-gui:")) {
        options->mainwin_visible = 1;
        gx_print_info(_("nsm startup"), _("optional-gui not supported by server"));
    }
    wait_id = false;
    gx_print_info(_("nsm startup"), name);
    _nsm_start_poll();

    return ERR_OK;
}
 
int GxNsmHandler::_nsm_save ( char **out_msg) {
    if (gx_preset::GxSettings::instance && nsm) {
        bool cur_state = gx_preset::GxSettings::instance->get_auto_save_state();
        gx_preset::GxSettings::instance->disable_autosave(false);
        gx_preset::GxSettings::instance->auto_save_state();
        gx_preset::GxSettings::instance->disable_autosave(cur_state);
        nsmsig->trigger_nsm_save_gui();
    }    
    return ERR_OK;
}
 
void GxNsmHandler::_nsm_show () {
    nsmsig->trigger_nsm_show_gui();
}

void GxNsmHandler::_nsm_hide () {
    nsmsig->trigger_nsm_hide_gui();
}
  
void GxNsmHandler::_on_nsm_is_shown () {
    nsm_send_is_shown(nsm);
}
  
void GxNsmHandler::_on_nsm_is_hidden () {
    nsm_send_is_hidden(nsm);
}
 
//static
int GxNsmHandler::gx_nsm_open (const char *name, const char *display_name,
            const char *client_id, char **out_msg, void *userdata ) {
    GxNsmHandler * nsmhandler = static_cast<GxNsmHandler*>(userdata);
    return nsmhandler->_nsm_open (name, display_name, client_id, out_msg);
}
            
//static            
int GxNsmHandler::gx_nsm_save ( char **out_msg, void *userdata ) {
    GxNsmHandler * nsmhandler = static_cast<GxNsmHandler*>(userdata);
    return nsmhandler->_nsm_save(out_msg);
}
            
//static            
void GxNsmHandler::gx_nsm_show (void *userdata ) {
    GxNsmHandler * nsmhandler = static_cast<GxNsmHandler*>(userdata);
    return nsmhandler->_nsm_show();
}
            
//static            
void GxNsmHandler::gx_nsm_hide (void *userdata ) {
    GxNsmHandler * nsmhandler = static_cast<GxNsmHandler*>(userdata);
    return nsmhandler->_nsm_hide();
}

#endif

/****************************************************************
 ** class GxTheme
 */

void GxTheme::init(gx_system::CmdlineOptions* options_) {
    options = options_;
    if (!options) {
        return; // program exit, no cleanup needed
    }
    std::string st_dir = options->get_style_dir();
    Gtk::IconTheme::get_default()->prepend_search_path(st_dir.substr(0, st_dir.size()-1));
    css_provider = Gtk::CssProvider::create();
    css_show_values = Gtk::CssProvider::create();
    style_context = Gtk::StyleContext::create();
    style_context->add_provider_for_screen(    Gdk::Screen::get_default(), css_show_values,
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    style_context->add_provider_for_screen(    Gdk::Screen::get_default(), css_provider,
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION+1);
}

bool GxTheme::set_new_skin(const Glib::ustring& skin_name) {
    if (!options) {
        return false;
    }
    if (skin_name.empty()) {
        options->skin.name = skin_name;
    } else {
        Glib::RefPtr<Gtk::IconTheme> deftheme = Gtk::IconTheme::get_default();
        std::vector<Glib::ustring> pathlist = deftheme->get_search_path();
        if (pathlist.empty() || pathlist.front() != options->get_style_filepath(options->skin.name)) {
            pathlist.insert(pathlist.cbegin(), "");
        }
        options->skin.name = skin_name;
        *pathlist.begin() = options->get_style_filepath(skin_name);
        deftheme->set_search_path(pathlist);
        deftheme->rescan_if_needed();
    }
    css_provider->load_from_path(options->get_current_style_cssfile());
    return true;
}

void GxTheme::update_show_values() {
    /* Gtk 3.24 uses information about which style modifications
     * change widget sizes this doesn't work with the (deprecated)
     * style setting show-value as work-around use a fake min-width
     * setting and remove it after the update
     *
     * DON'T USE "min-width: 1px" for GxRegler derived widgets in the
     * css style sheet, it will disable this update hack.
     */
    if (!options) {
        return;
    }
    boost::format fmt(
        "gx-regler, gx-big-knob, gx-mid-knob, gx-small-knob, gx-small-knob-r, gx-value-display, gx-vslider, gx-hslider {\n"
        "  -GxRegler-show-value: %1%;\n%2%"
        "}\n");
    fmt % gx_system::to_string(options->system_show_value);
    css_show_values->load_from_data((boost::format(fmt) % "  min-width: 1px\n").str());
    for (int i = 0; i < 50; i++) { // doesn't work reliable without this wait loop
        while (Gtk::Main::events_pending()) {
            Gtk::Main::iteration(false);
        }
        usleep(1000);
    }
    css_show_values->load_from_data((fmt % "").str());
}

#ifndef NDEBUG
void GxTheme::reload_css_post() {
    window->show();
    window->move(window_x, window_y);
    window->set_focus_on_map(true);
    try {
        css_provider->load_from_path(options->get_current_style_cssfile());
    } catch (Gtk::CssProviderError& e) {
        cerr << "CSS Style Error: " << e.what() << endl;
        gx_gui::show_error_msg(e.what());
    }
    style_context->add_provider_for_screen(    Gdk::Screen::get_default(), css_provider,
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION+1);
}

void GxTheme::reload_css() {
    if (!options) {
        return;
    }
    style_context->remove_provider_for_screen(Gdk::Screen::get_default(), css_provider);
    Glib::signal_idle().connect_once(sigc::mem_fun(this, &GxTheme::reload_css_post));
    window->get_position(window_x, window_y);
    window->set_focus_on_map(false);
    window->hide();
}
#endif


/****************************************************************
 ** class PosixSignals
 **
 ** Block unix signals and catch them in a special thread.
 ** Blocking is inherited by all threads created after an
 ** instance of PosixSignals
 */

class PosixSignals {
private:
    sigset_t waitset;
    std::thread *thread;
    bool gui;
    GxTheme *theme;
    volatile bool exit;
    void signal_helper_thread();
    void quit_slot();
    void gx_ladi_handler();
    void create_thread();
    bool gtk_level();
    static void relay_sigchld(int);
    
public:
    PosixSignals(bool gui, GxTheme *theme = nullptr);
    ~PosixSignals();
};


PosixSignals::PosixSignals(bool gui_, GxTheme *theme_)
    : waitset(),
      thread(nullptr),
      gui(gui_),
      theme(theme_),
      exit(false) {
    GxExit::get_instance().set_ui_thread();
    sigemptyset(&waitset);
    /* ----- block signal USR1 ---------
    ** inherited by all threads which are created later
    ** signals are processed synchronously by signal_helper_thread
    */
    sigaddset(&waitset, SIGUSR1);
    if (theme) {
        sigaddset(&waitset, SIGUSR2);
    }
    sigaddset(&waitset, SIGCHLD);
    sigaddset(&waitset, SIGINT);
    sigaddset(&waitset, SIGQUIT);
    sigaddset(&waitset, SIGTERM);
    sigaddset(&waitset, SIGHUP);
    sigaddset(&waitset, SIGKILL);

    // ----- leave alone these signals: generated by programming errors
    // SIGABRT
    // SIGSEGV

    sigprocmask(SIG_BLOCK, &waitset, NULL);
    create_thread();
    signal(SIGCHLD, relay_sigchld);
}

PosixSignals::~PosixSignals() {
    if (thread) {
        exit = true;
        pthread_kill(thread->native_handle(), SIGINT);
        thread->join();
        delete thread;
    }
    sigprocmask(SIG_UNBLOCK, &waitset, NULL);
}

void PosixSignals::create_thread() {
    try {
        thread = new std::thread(
            sigc::mem_fun(*this, &PosixSignals::signal_helper_thread));
    } catch (std::system_error& e) {
        throw GxFatalError(
            boost::format(_("Thread create failed (signal): %1%")) % e.what());
    }
}

void PosixSignals::quit_slot() {
    GxExit::get_instance().exit_program();
}

void PosixSignals::gx_ladi_handler() {
    gx_print_warning(
        _("signal_handler"), _("signal USR1 received, save settings"));
    if (gx_preset::GxSettings::instance) {
        bool cur_state = gx_preset::GxSettings::instance->get_auto_save_state();
        gx_preset::GxSettings::instance->disable_autosave(false);
        gx_preset::GxSettings::instance->auto_save_state();
        gx_preset::GxSettings::instance->disable_autosave(cur_state);
    }
}

void PosixSignals::relay_sigchld(int) {
    kill(getpid(), SIGCHLD);
}

bool PosixSignals::gtk_level() {
    if (! gui) {
        return 1;
    } else {
        return Gtk::Main::level();
    }
}

// --- wait for USR1 signal to arrive and invoke ladi handler via mainloop
void PosixSignals::signal_helper_thread() {
    const char *signame;
    guint source_id_usr1 = 0;
#ifndef NDEBUG
    guint source_id_usr2 = 0;
#endif
    pthread_sigmask(SIG_BLOCK, &waitset, NULL);
    bool seen = false;
    while (true) {
        int sig;
        int ret = sigwait(&waitset, &sig);
        if (exit) {
            break;
        }
        if (ret != 0) {
            assert(errno == EINTR);
            continue;
        }
        switch (sig) {
        case SIGUSR1:
            if (gtk_level() < 1) {
                gx_print_info(_("system startup"),
                        _("signal usr1 skipped"));
            break;
            }
            // do not add a new call if another one is already pending
            if (source_id_usr1 == 0 ||
                g_main_context_find_source_by_id(NULL, source_id_usr1) == NULL) {
                    const Glib::RefPtr<Glib::IdleSource> idle_source = Glib::IdleSource::create();
                    idle_source->connect( sigc::bind_return<bool>(
                        sigc::mem_fun(*this, &PosixSignals::gx_ladi_handler),false));
                    idle_source->attach();
                    source_id_usr1 = idle_source->get_id();
                }
            break;
#ifndef NDEBUG
        case SIGUSR2:
            if (gtk_level() < 1) {
                gx_print_info(_("system startup"),
                        _("signal usr2 skipped"));
                break;
            }
            // do not add a new call if another one is already pending
            if (source_id_usr2 == 0 ||
                g_main_context_find_source_by_id(NULL, source_id_usr2) == NULL) {
                    const Glib::RefPtr<Glib::IdleSource> idle_source = Glib::IdleSource::create();
                idle_source->connect(
                sigc::bind_return<bool>(
                sigc::mem_fun(*theme, &GxTheme::reload_css), false));
                idle_source->attach();
                source_id_usr2 = idle_source->get_id();
            }
            break;
#endif
        case SIGCHLD:
            Glib::signal_idle().connect_once(
                sigc::ptr_fun(gx_child_process::gx_sigchld_handler));
            break;
        case SIGINT:
        case SIGQUIT:
        case SIGTERM:
        case SIGHUP:
            switch (sig) {
            case SIGINT:
                signame = _("ctrl-c");
                break;
            case SIGQUIT:
                signame = "SIGQUIT";
                break;
            case SIGTERM:
                signame = "SIGTERM";
                break;
            case SIGHUP:
                signame = "SIGHUP";
                break;
            }
            if (!seen && gtk_level() == 1) {
                printf("\nquit (%s)\n", signame);
                Glib::signal_idle().connect_once(sigc::mem_fun(*this, &PosixSignals::quit_slot));
            } else {
                GxExit::get_instance().exit_program(
                    (boost::format("\nQUIT (%1%)\n") % signame).str());
            }
            seen = true;
            break;
        default:
            assert(false);
        }
    }
}


/****************************************************************
 ** class ErrorPopup
 ** show UI popup for kError messages
 */

class ErrorPopup {
private:
    Glib::ustring msg;
    bool active;
    Gtk::MessageDialog *dialog;
    void show_msg();
    void on_response(int);
public:
    ErrorPopup();
    ~ErrorPopup();
    void on_message(const Glib::ustring& msg, GxLogger::MsgType tp, bool plugged);
};

ErrorPopup::ErrorPopup()
    : msg(),
      active(false),
      dialog(0) {
}

ErrorPopup::~ErrorPopup() {
    delete dialog;
}

void ErrorPopup::on_message(const Glib::ustring& msg_, GxLogger::MsgType tp, bool plugged) {
    if (plugged) {
        return;
    }
    if (tp == GxLogger::kError) {
        if (active) {
            msg += "\n" + msg_;
            if (msg.size() > 1000) {
                msg.substr(msg.size()-1000);
            }
            if (dialog) {
                dialog->set_message(msg);
            }
        } else {
            msg = msg_;
            active = true;
            show_msg();
        }
    }
}

void ErrorPopup::on_response(int) {
    delete dialog;
    dialog = 0;
    active = false;
}

void ErrorPopup::show_msg() {
    dialog = new Gtk::MessageDialog(msg, false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_CLOSE);
    dialog->set_keep_above(true);
    dialog->set_title(_("GUITARIX ERROR"));
    dialog->signal_response().connect(
        sigc::mem_fun(*this, &ErrorPopup::on_response));
    dialog->show();
}


/****************************************************************
 ** class GxSplashBox
 ** show splash screen at start up
 */

class GxSplashBox: public Gtk::Window {
private:
    virtual void on_show();
    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
    Cairo::RefPtr<Cairo::ImageSurface> image;
public:
    explicit GxSplashBox(const string& imgpath);
    ~GxSplashBox() {}
    virtual void on_message(const Glib::ustring& msg_, GxLogger::MsgType tp, bool plugged);
};

GxSplashBox::GxSplashBox(const string& imgpath)
    : Gtk::Window(Gtk::WINDOW_POPUP),
      image(Cairo::ImageSurface::create_from_png(imgpath)) {
    set_app_paintable();
    set_position(Gtk::WIN_POS_CENTER);
    set_default_size(image->get_width(), image->get_height());
    realize();
#if GTK_MINOR_VERSION >= 24
    shape_combine_region(Gdk::Cairo::create_region_from_surface(image));
#endif
    show();
}

bool GxSplashBox::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
    cr->set_source(image, 0, 0);
    cr->paint();
    return false;
}

void GxSplashBox::on_message(const Glib::ustring& msg_, GxLogger::MsgType tp, bool plugged) {
    Gtk::Widget::hide();
}

void GxSplashBox::on_show() {
    Gtk::Widget::on_show();
    while(Gtk::Main::events_pending())
        Gtk::Main::iteration(false); 
}

/****************************************************************
 ** class GxRtCheck
 ** check if user have realtime priority
 */

class GxRtCheck {
private:
    std::thread _thd;
    std::mutex m;
    bool set_priority();
    void run();

public:
    bool run_check();
    GxRtCheck();
    ~GxRtCheck();
};
GxRtCheck::GxRtCheck() {run();}

GxRtCheck::~GxRtCheck() {}

bool GxRtCheck::run_check() {
#if defined(__linux__) || defined(_UNIX) || defined(__APPLE__)
    sched_param sch_params;
    sch_params.sched_priority = 50;
    if (pthread_setschedparam(_thd.native_handle(), SCHED_FIFO, &sch_params)) {
        return false;
    }
#elif defined(_WIN32)
    // HIGH_PRIORITY_CLASS, THREAD_PRIORITY_TIME_CRITICAL
    if (SetThreadPriority(_thd.native_handle(), 15)) {
        return false;
    }
#else
    //system does not supports thread priority!
#endif

    m.unlock();
    if (_thd.joinable()) {
        _thd.join();
    }
    return true;
}

void GxRtCheck::run() {
    m.lock();
    _thd = std::thread([this]() {
        /* Initially locked by the main thread, then released when this thread
         * should delete itself */
        std::scoped_lock<std::mutex> lk(m);
    });
}

/****************************************************************
 ** main()
 */
 
#if 0
#ifndef NDEBUG
int debug_display_glade(gx_engine::GxEngine& engine, gx_system::CmdlineOptions& options,
                        gx_engine::ParamMap& pmap, const string& fname) {
    pmap.set_init_values();
    if (!options.get_rcset().empty()) {
        std::string rcfile = options.get_style_filepath("gx_head_"+options.get_rcset()+".rc");
        gtk_rc_parse(rcfile.c_str());
        gtk_rc_reset_styles(gtk_settings_get_default());
    }
    Gtk::Window *w = 0;
    gx_ui::GxUI ui;
    Glib::RefPtr<gx_gui::GxBuilder> bld = gx_gui::GxBuilder::create_from_file(fname, &machine);
    w = bld->get_first_window();
    gx_ui::GxUI::updateAllGuis(true);
    if (w) {
    Gtk::Main::run(*w);
    delete w;
    }
    return 0;
}
#endif
#endif

#ifdef NDEBUG
// switch off GTK warnings in Release build
static void null_handler(const char *log_domain, GLogLevelFlags log_level,
                         const gchar *msg, gpointer user_data ) {
    return ;
}
#endif

static void mainHeadless(int argc, char *argv[]) {
    Glib::init();
    Gio::init();

    PosixSignals posixsig(false); // catch unix signals in special thread
    gx_system::CmdlineOptions options;
    options.parse(argc, argv);
    options.process(argc, argv);
    // ---------------- Check for working user directory  -------------
    bool need_new_preset;
    gx_preset::GxSettings::check_settings_dir(options, &need_new_preset);

    gx_engine::GxMachine machine(options);

    gx_jack::GxJack::rt_watchdog_set_limit(options.get_idle_thread_timeout());
    machine.loadstate();
    //if (!in_session) {
    //    gx_settings.disable_autosave(options.get_opt_auto_save());
    //}

    if (! machine.get_jack()->gx_jack_connection(true, true, 0, options)) {
        cerr << "can't connect to jack\n";
        return;
    }
    if (need_new_preset) {
        machine.create_default_scratch_preset();
    }
    // when midiout is requested we need to reload state in order to send midi feedback
    if (options.system_midiout) machine.loadstate();
    if (options.system_tuner_midiout) machine.set_parameter_value("system.midiout_tuner", true);
    if (!options.get_setbank().empty())
        machine.load_preset(machine.get_bank_file(options.get_cmdline_bank()), options.get_cmdline_preset()); 
    // ----------------------- Run Glib main loop ----------------------
    cout << "Ctrl-C to quit\n";
    Glib::RefPtr<Glib::MainLoop> loop = Glib::MainLoop::create();
    machine.get_jack()->shutdown.connect(sigc::mem_fun(loop.operator->(),&Glib::MainLoop::quit));
    int port = options.get_rpcport();
    if (port == RPCPORT_DEFAULT) {
        port = 7000;
    }
    if (port != RPCPORT_NONE) {
        machine.start_socket(sigc::mem_fun(loop.operator->(),&Glib::MainLoop::quit), options.get_rpcaddress(), port);
        loop->run();
    } else {
        loop->run();
    }
    gx_child_process::childprocs.killall();
}

static void exception_handler() {
    try {
        throw; // re-throw current exception
    } catch (const GxFatalError& error) {
        cerr << error.what() << endl;
        gx_print_fatal(_("Guitarix fatal error"), error.what());
    } catch (const Glib::OptionError &error) {
        cerr << error.what() << endl;
        cerr << _("use \"guitarix -h\" to get a help text") << endl;
        gx_print_fatal(_("Guitarix Commandline Option Error"),
                Glib::ustring::compose(
                "%1\n%2",
                error.what(),
                _("use \"guitarix -h\" to get a help text")));
    } catch (const Glib::Error& error) {
        const GError *perr = error.gobj();
        Glib::ustring msg = Glib::ustring::compose(
            "Glib::Error[%1/%2]: %3",
            g_quark_to_string(perr->domain),
            perr->code,
            (perr->message) ? perr->message : "(null)");
        cerr << msg << endl;
        gx_print_fatal(_("Guitarix fatal error"), msg);
    } catch (const std::exception& except) {
        Glib::ustring msg = Glib::ustring::compose(
            "std::exception: %1", except.what());
        cerr << msg << endl;
        gx_print_fatal(_("Guitarix fatal error"), msg);
    } catch(...) {
        cerr << _("unknown error") << endl;
        gx_print_fatal(_("Guitarix fatal error"),_("unknown error"));
    }
}

static bool is_headless(int argc, char *argv[]) {
    for (int i = 0; i < argc; ++i) {
        if (strcmp(argv[i], "-N") == 0 || strcmp(argv[i], "--nogui") == 0) {
            return true;
        }
    }
    return false;
}

static bool is_frontend(int argc, char *argv[]) {
    for (int i = 0; i < argc; ++i) {
        if (strcmp(argv[i], "-G") == 0 || strcmp(argv[i], "--onlygui") == 0) {
            return true;
        }
    }
    return false;
}

static void mainGtk(gx_system::CmdlineOptions& options, NsmSignals& nsmsig, GxTheme& theme, GxSplashBox *Splash, bool need_new_preset) {
/*
    GxRtCheck rtc;
    if (!rtc.run_check()) {
        delete Splash;
        gx_print_fatal(_("Guitarix"), "Can't access realtime priority, exit now");
    }
*/
    gx_engine::GxMachine machine(options);
#if 0
    while(Gtk::Main::events_pending()) {
        // prevents crash in show_error_msg!dialog.run() when its
        // called due to an early exception (like some icon file not
        // found when the style-dir is bad). This is probably not the
        // correct cure but it helps...
        Gtk::Main::iteration(false);
    }
#ifndef NDEBUG
    if (argc > 1) {
        delete Splash;
        debug_display_glade(engine, options, gx_engine::parameter_map, argv[1]);
        return;
    }
#endif
#endif
    // ----------------------- init GTK interface----------------------
    MainWindow gui(machine, options, nsmsig, theme, Splash, "");
    if (need_new_preset) {
        gui.create_default_scratch_preset();
    }
    // when midiout is requested we need to reload state in order to send midi feedback
    if (options.system_midiout) machine.loadstate();
    if (options.system_tuner_midiout) machine.set_parameter_value("system.midiout_tuner", true);
    if (!options.get_setbank().empty())
        machine.load_preset(machine.get_bank_file(options.get_cmdline_bank()), options.get_cmdline_preset()); 
    delete Splash;
    gui.run();
}

static void mainFront(gx_system::CmdlineOptions& options, NsmSignals& nsmsig, GxTheme& theme, GxSplashBox *Splash, bool need_new_preset) {
    Glib::ustring title;
#ifdef HAVE_AVAHI
    if (options.get_rpcaddress().empty() && options.get_rpcport() == RPCPORT_DEFAULT) {
        SelectInstance si(options, Splash);
        if (Splash) {
            Splash->show();
        }
        Glib::ustring a;
        int port;
        Glib::ustring name;
        Glib::ustring host;
        if (!si.get_address_port(a, port, name, host)) {
            cerr << "Failed to get address" << endl;
            return;
        }
        options.set_rpcaddress(a);
        options.set_rpcport(port);
        title = Glib::ustring::compose("%1 / %2:%3", name, host, port);
    }
#endif // HAVE_AVAHI
    if (options.get_rpcport() == RPCPORT_DEFAULT) {
        options.set_rpcport(7000);
    }
    if (options.get_rpcaddress().empty()) {
        options.set_rpcaddress("localhost");
    }
    if (title.empty()) {
        title = Glib::ustring::compose("%1:%2", options.get_rpcaddress(), options.get_rpcport());
    }
    gx_engine::GxMachineRemote machine(options);

    // ----------------------- init GTK interface----------------------
    MainWindow gui(machine, options, nsmsig,theme, Splash, title);
    if (need_new_preset) {
        gui.create_default_scratch_preset();
    }
    machine.set_init_values();
    delete Splash;
    gui.run();
}

static void mainProg(int argc, char *argv[]) {
    bool frontend = is_frontend(argc, argv);
    Glib::init();

    GxTheme theme;
#ifndef NDEBUG
    PosixSignals posixsig(true, &theme); // catch unix signals in special thread
#else
    PosixSignals posixsig(true, nullptr);
#endif
    Glib::add_exception_handler(sigc::ptr_fun(exception_handler));
    gx_system::CmdlineOptions options;

    NsmSignals nsmsig;

    Gtk::Main main(argc, argv, options);
    Gxw::init();
    options.process(argc, argv);

#ifdef HAVE_LIBLO
    GxNsmHandler nsmhandler(&options, &nsmsig);
    nsmsig.nsm_session_control = nsmhandler.check_nsm(argv);
#endif

    bool theme_ok = false;
    if (options.get_clear_rc()) {
        options.skin.name = "";
    } else if (options.skin.name.empty()) {
        options.skin.name = "Guitarix";
    }
    theme.init(&options);
    try { // early theme init
        theme.set_new_skin(options.skin.name);
        theme_ok = false;
    } catch (...) {
    // try again later to display message dialog
    }
    GxSplashBox * Splash = NULL;
#ifdef NDEBUG
    Splash =  new GxSplashBox(options.get_pixmap_filepath("gx_splash.png"));
    GxLogger::get_logger().signal_message().connect(
    sigc::mem_fun(Splash, &GxSplashBox::on_message));
    g_log_set_handler("Gtk",G_LOG_LEVEL_WARNING,null_handler,NULL);
#endif
    GxExit::get_instance().signal_msg().connect(
    sigc::ptr_fun(gx_gui::show_error_msg));  // show fatal errors in UI
    ErrorPopup popup;
    GxLogger::get_logger().signal_message().connect(
    sigc::mem_fun(popup, &ErrorPopup::on_message));
    if (!theme_ok) {
        theme.set_new_skin(options.skin.name); // try again, display error message
    }
    // ---------------- Check for working user directory  -------------
    bool need_new_preset;
    gx_preset::GxSettings::check_settings_dir(options, &need_new_preset);

    if (frontend) {
        mainFront(options, nsmsig, theme, Splash, need_new_preset);
    } else {
        mainGtk(options, nsmsig, theme, Splash, need_new_preset);
    }

    gx_child_process::childprocs.killall();
    theme.init(nullptr);
}

int main(int argc, char *argv[]) {
    // This is a hack. If we start qjackctl, we want to make sure it scale
    // automatically for HiDPI displays.
    // Note: we don't change then environment if it is already set to *any* value.
    if (!getenv("QT_AUTO_SCREEN_SCALE_FACTOR")) {
        setenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1", 0);
    }
#ifdef DISABLE_NLS
// break
#elif defined(IS_MACOSX)
// break
#elif ENABLE_NLS
    bindtextdomain(GETTEXT_PACKAGE, LOCALEDIR);
    bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
    textdomain(GETTEXT_PACKAGE);
#endif

    try {
    // ----------------------- init basic subsystems ----------------------
#if (GLIB_MAJOR_VERSION == 2 && GLIB_MINOR_VERSION < 32)
    if (!Glib::thread_supported()) {
        Glib::thread_init();
    }
#endif
    if (is_headless(argc, argv)) {
        mainHeadless(argc, argv);
    } else {
        mainProg(argc, argv);
    }
    } catch (...) {
        exception_handler();
    }
    return 0;
}
#endif
