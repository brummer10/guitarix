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
 * --------------------------------------------------------------------------
 */

#include "guitarix.h"                    // NOLINT

#include <gxw/GxControlParameter.h>      // NOLINT
#include <gxwmm/controlparameter.h>      // NOLINT
#include <gxwmm/radiobutton.h>           // NOLINT
#include <gxwmm/iredit.h>                // NOLINT
#include <gtkmm/window.h>                // NOLINT
#include <gtkmm/builder.h>               // NOLINT
#include <gtkmm/main.h>                  // NOLINT
#include <gtkmm/filechooserdialog.h>     // NOLINT

#include <gtkmm/combobox.h>              // NOLINT
#include <gtkmm/treeview.h>              // NOLINT
#include <gtkmm/treestore.h>             // NOLINT
#include <glibmm/ustring.h>              // NOLINT
#include <giomm/file.h>                  // NOLINT

#include <gtkmm/stock.h>                 // NOLINT
#include <gtkmm/recentmanager.h>         // NOLINT
#include <giomm.h>                       // NOLINT

#include <string>                        // NOLINT
#include <vector>                        // NOLINT

#define _(x) (x)

/****************************************************************
 ** fixup_controlparameters()
 ** helper function to initialize widgets which are linked to a
 ** variable name (via ControlParameter interface):
 ** set range, title and initial value from parameter table,
 ** connect uiItem and Midi learn
 */

namespace Glib { namespace Container_Helpers {
template <>
struct TypeTraits<GObject*> {
    typedef GObject *CppType;
    typedef GObject *CType;
    typedef GObject *CTypeNonConst;

    static CType to_c_type(CppType item) { return item; }
    static CppType to_cpp_type(CType item) { return item; }
    static void release_c_type(CType) {}
};
}} // end namespace Glib::Container_Helpers

namespace gx_jconv {

class uiToggle: gx_ui::GxUiItemFloat {
 protected:
    Glib::RefPtr<Gtk::ToggleButton> button;
    void on_button_toggled();
    virtual void reflectZone();
 public:
    uiToggle(gx_ui::GxUI& ui, Glib::RefPtr<Gtk::ToggleButton>& b, float *zone);
};

uiToggle::uiToggle(gx_ui::GxUI& ui, Glib::RefPtr<Gtk::ToggleButton>& b, float *zone)
    : gx_ui::GxUiItemFloat(&ui, zone), button(b) {
    button->signal_toggled().connect(sigc::mem_fun(*this, &uiToggle::on_button_toggled));
}

void uiToggle::on_button_toggled() {
    modifyZone(button->get_active());
}

void uiToggle::reflectZone() {
    float v = *fZone;
    fCache = v;
    button->set_active(v != 0.0);
}

static void fixup_controlparameters(Glib::RefPtr<Gtk::Builder> builder, gx_ui::GxUI& ui) {
    Glib::SListHandle<GObject*> objs = Glib::SListHandle<GObject*>(
        gtk_builder_get_objects(builder->gobj()), Glib::OWNERSHIP_DEEP);
    for (Glib::SListHandle<GObject*>::iterator i = objs.begin(); i != objs.end(); i++) {
        if (!g_type_is_a(G_OBJECT_TYPE(*i), GX_TYPE_CONTROL_PARAMETER)) {
            continue;
        }
        Glib::RefPtr<Gxw::ControlParameter> w = Glib::wrap(GX_CONTROL_PARAMETER(*i), true);
        Glib::ustring v = w->cp_get_var();
        if (v.empty()) {
            continue;
        }
        if (!gx_gui::parameter_map.hasId(v)) {
            gx_system::gx_print_warning("load dialog",
                (boost::format("Parameter variable %1% not found") % v).str());
            continue;
        }
        gx_gui::Parameter& p = gx_gui::parameter_map[v];
        if (!p.desc().empty()) {
            Glib::RefPtr<Gtk::Widget>::cast_dynamic(w)->set_tooltip_text(p.desc());
        }
        if (p.isFloat()) {
            gx_gui::FloatParameter &fp = p.getFloat();
            w->cp_configure(p.group(), p.name(), fp.lower, fp.upper, fp.step);
            w->cp_set_value(fp.value);
            Glib::RefPtr<Gtk::Range> r = Glib::RefPtr<Gtk::Range>::cast_dynamic(w);
            if (r) {
                Gtk::Adjustment *adj = r->get_adjustment();
                gx_gui::uiAdjustment* c = new gx_gui::uiAdjustment(&ui, &fp.value, adj->gobj());
                adj->signal_value_changed().connect(
                    sigc::bind<GtkAdjustment*>(
                        sigc::bind<gpointer>(
                            sigc::ptr_fun(gx_gui::uiAdjustment::changed),
                                         (gpointer)c), adj->gobj()));
            } else {
                Glib::RefPtr<Gtk::ToggleButton> t =
                    Glib::RefPtr<Gtk::ToggleButton>::cast_dynamic(w);
                if (t) {
                    new uiToggle(ui, t, &fp.value);
                }
            }
            if (fp.isControllable()) {
                gx_gui::connect_midi_controller(GTK_WIDGET(w->gobj()), &fp.value);
            }
        } else {
            gx_system::gx_print_warning("load dialog",
                      (boost::format("Parameter variable %1%: type not handled") % v).str());
        }
    }
}

// FIXME: needs to be moved somewhere else (at least be together with convolver_start)
void gx_convolver_restart() {
    if (!GxJConvSettings::checkbutton7) {
        return;
    }
    gx_engine::conv.stop();
    while (gx_engine::conv.is_runnable()) gx_engine::conv.checkstate();
    gx_jconv::GxJConvSettings* jcset = GxJConvSettings::instance();
    bool rc = gx_engine::conv.configure(
        gx_jack::gxjack.jack_bs, gx_jack::gxjack.jack_sr, jcset->getFullIRPath(),
        jcset->getGain(), jcset->getGain(), jcset->getDelay(), jcset->getDelay(),
        jcset->getOffset(), jcset->getLength(), 0, 0, jcset->getGainline());
    if (!rc || !gx_engine::conv.start()) {
        GxJConvSettings::checkbutton7 = 0;
    }
}

/****************************************************************
 ** Convolver Parameter Window
 */

class IRWindow: public Gtk::Window {
 private:
    Glib::RefPtr<Gtk::Builder> builder;
    Glib::ustring filename;
    double ms; // samples per millisecond
    float *audio_buffer;
    unsigned int audio_size;
    int audio_chan;
    static IRWindow *instance;

    // helper functions
    int set_val(Gxw::ControlParameter *sample_display, Gxw::ControlParameter *ms_display,
                double value, int fs);
    inline int get_ms(Gxw::ControlParameter *w) {
         return static_cast<int>(round(w->cp_get_value()*ms));
    }
    void file_changed(Glib::ustring filename, int rate, int length,
                      int channels, Glib::ustring format);
    void load_data(Glib::ustring filename);
    void load_state();
    bool save_state();
    void set_GainCor();
    double calc_normalized_gain(int offset, int length, const Gainline& points);
    void destroy_self();


    // signal functions and widget pointers
    void on_window_hide();

    Gxw::IREdit *wIredit;
    void on_delay_changed(int delay, int fs);
    void on_offset_changed(int offset, int fs);
    void on_length_changed(int length, int fs);
    void on_max_scale_reached(bool v);
    void on_min_scale_reached(bool v);

    Gxw::RadioButton *wLeft, *wRight, *wSum;
    void on_left();
    void on_right();
    void on_sum();

    Gxw::RadioButton *wLinear, *wLog;
    void on_linear();

    Gxw::ValueDisplay *wDelay, *wDelay_ms, *wOffset, *wOffset_ms, *wLength, *wLength_ms;
    void on_m_delay_changed();
    void on_ms_delay_changed();
    void on_m_offset_changed();
    void on_ms_offset_changed();
    void on_m_length_changed();
    void on_ms_length_changed();

    Gxw::Regler *wDelay_delta;
    Glib::ustring on_delay_delta_format_value(double v);

    Gtk::Button *wHome, *wJump_zoom_mark, *wIncr, *wDecr;
    void on_home();
    void on_jump_zoom_mark();
    void on_decr();
    void on_incr();

    Gtk::Button *wReset, *wOpen;
    void on_reset_clicked();
    void on_open();

    Gtk::Button *wOk, *wApply, *wCancel;
    void on_apply_button_clicked();
    void on_cancel_button_clicked();
    void on_ok_button_clicked();
    
    Gtk::Button *wadd, *wshow, *wremove, *wremoveall;
    Gtk::Label *wladd, *wlshow, *wlremove, *wlremoveall;
    void on_add_button_clicked();
    void on_show_button_clicked();
    void on_show_button_clicked_in();
    void on_remove_button_clicked();
    void on_remove_all_button_clicked();

    Gtk::ToggleButton *wGain_correction;
    void on_gain_button_toggled();

    Gtk::Label *wSamples, *wSampleRate, *wFormat, *wFilename;
    Gtk::Widget *wChannelbox;

    void on_help_clicked();
    Gtk::Window *wHelp;

 protected:
    void init_connect();
    IRWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
    ~IRWindow();
    friend class Gtk::Builder;
    friend void gx_show_jconv_dialog_gui(_GtkWidget*, void*);

    class ModelColumns : public Gtk::TreeModel::ColumnRecord {
     public:
        ModelColumns() { add(name);}
        Gtk::TreeModelColumn<Glib::ustring> name;
    };
    Gtk::ComboBox *wcombo;
    Gtk::HBox *wboxcombo;
    Gtk::TreeView *treeview;
    Glib::RefPtr<Gtk::TreeStore> model;
    ModelColumns columns;
    void on_remove_tree();
    void on_combo_changed();

 public:
    void on_enumerate();
    static void create(gx_ui::GxUI& ui);
    static void reload() { if (instance) instance->load_state(); }
    static void show_fav() { if (instance) instance->on_show_button_clicked(); }
    static void new_file(Glib::ustring filename) {if (instance) instance->load_data(filename);}
    static bool save() {
        if (instance) return instance->save_state();
        else
            return false;
    }
    static void show_window() { if (instance) instance->IRWindow::show(); }
    static IRWindow* get_window() {return instance;}
};

/*
** static class variables and functions
*/

IRWindow *IRWindow::instance = 0;

Glib::RefPtr<Gtk::Builder> load_builder(Glib::ustring name) {
    Glib::RefPtr<Gtk::Builder> bld = Gtk::Builder::create();
    try {
        bld->add_from_file(gx_system::sysvar.gx_builder_dir+name);
    } catch(const Glib::FileError& ex) {
        gx_system::gx_print_error("FileError", ex.what());
    } catch(const Gtk::BuilderError& ex) {
        gx_system::gx_print_error("Builder Error", ex.what());
    }
    return bld;
}

void IRWindow::create(gx_ui::GxUI& ui) {
    if (instance) {
        return;
    }
    Glib::RefPtr<Gtk::Builder> bld = load_builder("iredit.glade");
    fixup_controlparameters(bld, ui);
    bld->get_widget_derived("DisplayIR", instance);
}

/*
 ** Constructor
 */

void IRWindow::init_connect() {
    builder->get_widget("vbox11", wboxcombo);
    wboxcombo->add(*wcombo);
    wboxcombo->show_all();

    builder->get_widget("iredit", wIredit);
    wIredit->signal_delay_changed().connect(sigc::mem_fun(*this,
                                            &IRWindow::on_delay_changed));
    wIredit->signal_offset_changed().connect(sigc::mem_fun(*this,
                                            &IRWindow::on_offset_changed));
    wIredit->signal_length_changed().connect(sigc::mem_fun(*this,
                                             &IRWindow::on_length_changed));
    wIredit->signal_scale_max_reached().connect(sigc::mem_fun(*this,
                                                &IRWindow::on_max_scale_reached));
    wIredit->signal_scale_min_reached().connect(sigc::mem_fun(*this,
                                                &IRWindow::on_min_scale_reached));

    builder->get_widget("left", wLeft);
    wLeft->signal_toggled().connect(sigc::mem_fun(*this, &IRWindow::on_left));
    builder->get_widget("right", wRight);
    wRight->signal_toggled().connect(sigc::mem_fun(*this, &IRWindow::on_right));
    builder->get_widget("sum", wSum);
    wSum->set_active(true);
    wSum->signal_toggled().connect(sigc::mem_fun(*this, &IRWindow::on_sum));

    builder->get_widget("log", wLog);
    wLog->set_active(true);
    builder->get_widget("linear", wLinear);
    wLinear->signal_toggled().connect(sigc::mem_fun(*this, &IRWindow::on_linear));

    builder->get_widget("delay", wDelay);
    wDelay->signal_value_changed().connect(sigc::mem_fun(*this,
                                           &IRWindow::on_m_delay_changed));
    builder->get_widget("offset", wOffset);
    wOffset->signal_value_changed().connect(sigc::mem_fun(*this,
                                            &IRWindow::on_m_offset_changed));
    builder->get_widget("irlength", wLength);
    wLength->signal_value_changed().connect(sigc::mem_fun(*this,
                                            &IRWindow::on_m_length_changed));
    builder->get_widget("delay_ms", wDelay_ms);
    wDelay_ms->signal_value_changed().connect(sigc::mem_fun(*this,
                                              &IRWindow::on_ms_delay_changed));
    builder->get_widget("offset_ms", wOffset_ms);
    wOffset_ms->signal_value_changed().connect(sigc::mem_fun(*this,
                                               &IRWindow::on_ms_offset_changed));
    builder->get_widget("irlength_ms", wLength_ms);
    wLength_ms->signal_value_changed().connect(sigc::mem_fun(*this,
                                               &IRWindow::on_ms_length_changed));

    builder->get_widget("delay_delta", wDelay_delta);
    wDelay_delta->signal_format_value().connect(sigc::mem_fun(*this,
                                                &IRWindow::on_delay_delta_format_value));

    builder->get_widget("home", wHome);
    wHome->signal_clicked().connect(sigc::mem_fun(*this, &IRWindow::on_home));
    builder->get_widget("jump_zoom_mark", wJump_zoom_mark);
    wJump_zoom_mark->signal_clicked().connect(sigc::mem_fun(*this,
                                              &IRWindow::on_jump_zoom_mark));
    builder->get_widget("incr", wIncr);
    wIncr->signal_clicked().connect(sigc::mem_fun(*this, &IRWindow::on_incr));
    builder->get_widget("decr", wDecr);
    wDecr->signal_clicked().connect(sigc::mem_fun(*this, &IRWindow::on_decr));

    builder->get_widget("add_button", wadd);
    builder->get_widget("ablabel", wladd);
    wladd->set_name("beffekt_label");
    wadd->set_name("rack_button");
    wadd->signal_clicked().connect(sigc::mem_fun(*this, &IRWindow::on_add_button_clicked));

    builder->get_widget("list_button", wshow);
    builder->get_widget("sflabel", wlshow);
    wlshow->set_name("beffekt_label");
    wshow->set_name("rack_button");
    wshow->signal_clicked().connect(sigc::mem_fun(*this, &IRWindow::on_show_button_clicked_in));
    
    builder->get_widget("remove_button", wremove);
    builder->get_widget("relabel", wlremove);
    wlremove->set_name("beffekt_label");
    wremove->set_name("rack_button");
    wremove->signal_clicked().connect(sigc::mem_fun(*this, &IRWindow::on_remove_button_clicked));

    builder->get_widget("remove_list_button", wremoveall);
    builder->get_widget("rllabel", wlremoveall);
    wlremoveall->set_name("beffekt_label");
    wremoveall->set_name("rack_button");
    wremoveall->signal_clicked().connect(sigc::mem_fun(*this, &IRWindow::on_remove_all_button_clicked));

    builder->get_widget("reset_button", wReset);
    wReset->signal_clicked().connect(sigc::mem_fun(*this, &IRWindow::on_reset_clicked));
    builder->get_widget("open_button", wOpen);
    wOpen->signal_clicked().connect(sigc::mem_fun(*this, &IRWindow::on_open));

    builder->get_widget("apply_button", wApply);
    wApply->signal_clicked().connect(sigc::mem_fun(*this,
                                     &IRWindow::on_apply_button_clicked));

    builder->get_widget("cancel_button", wCancel);
    wCancel->signal_clicked().connect(sigc::mem_fun(*this,
                                      &IRWindow::on_cancel_button_clicked));
    builder->get_widget("ok_button", wOk);
    wOk->signal_clicked().connect(sigc::mem_fun(*this,
                                  &IRWindow::on_ok_button_clicked));

    builder->get_widget("gain_button", wGain_correction);
    wGain_correction->signal_toggled().connect(sigc::mem_fun(*this,
                                               &IRWindow::on_gain_button_toggled));

    builder->get_widget("length", wSamples);
    builder->get_widget("samplerate", wSampleRate);
    builder->get_widget("format", wFormat);
    builder->get_widget("filename", wFilename);

    builder->get_widget("channelbox", wChannelbox);

    Gtk::Button* button;
    builder->get_widget("help_button", button);
    button->signal_clicked().connect(sigc::mem_fun(*this, &IRWindow::on_help_clicked));
    builder->get_widget("HelpIR", wHelp);
    builder->get_widget("close_irhelp", button);
    button->signal_clicked().connect(sigc::mem_fun(wHelp, &Gtk::Widget::hide));
}

void IRWindow::set_GainCor() {
    GxJConvSettings& jcset = *GxJConvSettings::instance();
    unsigned int gain_cor      = jcset.getGainCor();
    if (gain_cor) {
        wGain_correction->set_active(true);
    } else {
        wGain_correction->set_active(false);
    }
}

IRWindow::IRWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& bld)
                  : Gtk::Window(cobject), builder(bld), ms(0.0), audio_buffer(0),
                audio_size(0), audio_chan(0) {

    // setup the TreeView
    treeview = new Gtk::TreeView;
    model = Gtk::TreeStore::create(columns);
    treeview->set_headers_visible(false);
    treeview->set_model(model);
    treeview->append_column("", columns.name);
    wcombo = new Gtk::ComboBox();
    wcombo->set_name("rack_button");

    init_connect();
    set_icon(Glib::wrap(gx_gui::gw.ib));
    set_GainCor();

    // reset display
    file_changed("", 0, 0, 0, "");
    on_delay_changed(0, 0);
    on_offset_changed(0, 0);
    on_length_changed(0, 0);

    // show();
}

IRWindow::~IRWindow() {
    delete audio_buffer;
    delete treeview;
    delete wcombo;
}

/*
** helper functions
*/

int IRWindow::set_val(Gxw::ControlParameter *sample_display,
                      Gxw::ControlParameter *ms_display,
                      double value, int fs) {
    double s1, s2;
    if (fs) {
        s1 = value;
        s2 = (value*1000.0)/fs;
    } else {
        s1 = 0;
        s2 = 0;
    }
    ms_display->cp_set_value(s2);
    sample_display->cp_set_value(s1);
    return sample_display->cp_get_int_value();
}

void IRWindow::file_changed(Glib::ustring filename, int rate, int length,
                            int channels, Glib::ustring format) {
    Glib::ustring s_rate, s_length, s_channels;
    if (filename.empty()) {
        filename = "no file selected";
        s_length = s_rate = format = s_channels = "--";
    } else {
        ms = rate/1000.0;
        wDelay->set_range(0, 5*rate);
        wDelay_ms->set_range(0, 5*1000);
        wOffset->set_range(0, length-1);
        wOffset_ms->set_range(0, (length-1)*1000.0/rate);
        wLength->set_range(0, length);
        wLength_ms->set_range(0, (length)*1000.0/rate);
        on_delay_changed(0, rate);
        on_offset_changed(0, rate);
        on_length_changed(length, rate);
        s_length = (boost::format("%1%") % length).str();
        s_rate = (boost::format("%1%") % rate).str();
    }
    wSamples->set_text(s_length);
    wSampleRate->set_text(s_rate);
    wFormat->set_text(format);
    wChannelbox->set_sensitive(channels >= 2);
    wFilename->set_text(Glib::path_get_dirname(filename));
    GxJConvSettings& jcset = *GxJConvSettings::instance();
    string amp = jcset.getIRFile();
    if (GTK_IS_LABEL(gx_gui::gw.set_label))
        gtk_label_set_text(GTK_LABEL(gx_gui::gw.set_label),amp.c_str());
}

// wrapper function to reload the cmbobox tree in a idle loop
gboolean enumerate(gpointer arg) {
    IRWindow::get_window()->on_enumerate();
    return false;
}

void IRWindow::load_state() {
    GxJConvSettings& jcset = *GxJConvSettings::instance();
    string path = jcset.getFullIRPath();
    if (path.empty()) {
        return;
    }
    load_data(path);
    wIredit->set_offset(jcset.getOffset());
    wIredit->set_delay(jcset.getDelay());
    wIredit->set_length(jcset.getLength());
    if (jcset.getGainline().size()) {
        wIredit->set_gain(jcset.getGainline());
    }
    g_idle_add(enumerate, NULL);
}

void IRWindow::load_data(Glib::ustring f) {
    filename = f;
    gx_engine::Audiofile audio;
    if (audio.open_read(filename)) {
        gx_system::gx_print_error("jconvolver", "Unable to open '" + filename + "'");
        return;
    }
    audio_size = audio.size();
    audio_chan = audio.chan();
    const unsigned int limit = 2000000; // arbitrary size limit
    if (audio_size > limit) {
        gx_system::gx_print_warning(
            "jconvolver", (boost::format(_("too many samples (%1%), truncated to %2%"))
                           % audio_size % limit).str());
        audio_size = limit;
    }
    if (audio_size * audio_chan == 0) {
        gx_system::gx_print_error("jconvolver", "No samples found");
        return;
    }
    float *buffer = new float[audio_size*audio_chan];
    if (audio.read(buffer, audio_size) != static_cast<int>(audio_size)) {
        gx_system::gx_print_error("jconvolver", "Error reading file");
        return;
    }
    Glib::ustring enc;
    switch (audio.type()) {
    case gx_engine::Audiofile::TYPE_OTHER: enc = "???"; break;
    case gx_engine::Audiofile::TYPE_CAF: enc = "CAF"; break;
    case gx_engine::Audiofile::TYPE_WAV: enc = "WAV"; break;
    case gx_engine::Audiofile::TYPE_AMB: enc = "AMB"; break;
    }
    enc += " ";
    switch (audio.form()) {
    case gx_engine::Audiofile::FORM_OTHER: enc += "?"; break;
    case gx_engine::Audiofile::FORM_16BIT: enc += "16 bit"; break;
    case gx_engine::Audiofile::FORM_24BIT: enc += "24 bit"; break;
    case gx_engine::Audiofile::FORM_32BIT: enc += "32 bit"; break;
    case gx_engine::Audiofile::FORM_FLOAT: enc += "float"; break;
    }
    delete audio_buffer;
    audio_buffer = buffer;
    wIredit->set_ir_data(audio_buffer, audio_chan, audio_size, audio.rate());
    file_changed(filename, audio.rate(), audio_size, audio_chan, enc);
    wSum->set_active(true);
    wLog->set_active(true);
}

// FIXME: gainline code just copied from GxConvolver::read_sndfile, move to 1 location
inline void compute_interpolation(
    double& fct, double& gp, unsigned int& idx,
    const Gainline& points, int offset) {
    fct = (points[idx+1].g-points[idx].g)/(20*(points[idx+1].i-points[idx].i));
    gp = points[idx].g/20 + fct * (offset-points[idx].i);
    idx++;
}

double IRWindow::calc_normalized_gain(int offset, int length, const Gainline& points) {
    double gain = 0.0;
    unsigned int idx = 0; // current index in gainline point array
    double gp = 0.0, fct = 0.0; // calculated parameter of interpolation line
    if (points.size()) {
        while (points[idx].i < offset) {
            idx++;
            assert(idx < points.size());
        }
        if (points[idx].i > offset) {
            idx--;
            compute_interpolation(fct, gp, idx, points, 0);
        }
    }
    for (int i = offset; i < offset+length; i++) {
        if (idx+1 < points.size() && points[idx].i == i) {
            compute_interpolation(fct, gp, idx, points, 0);
        }
        double g = pow(10, gp + i*fct);
        for (int j = 0; j < audio_chan; j++) {
            double v = audio_buffer[i*audio_chan+j] * g;
            gain += v*v;
        }
    }
    gain = sqrt(gain / audio_chan);
    if (gain != 0.0) {
        gain = 1 / gain;
    }
    return gain;
}

bool IRWindow::save_state() {
    GxJConvSettings& jcset = *GxJConvSettings::instance();
    unsigned int offset = wIredit->get_offset();
    unsigned int length = wIredit->get_length();
    unsigned int delay = wIredit->get_delay();
    unsigned int gain_cor      = jcset.getGainCor();
    Gainline gainline = wIredit->get_gain();
    if (offset == jcset.getOffset() &&
        delay == jcset.getDelay() &&
        length == jcset.getLength() &&
        filename == jcset.getFullIRPath() &&
        gainline ==  jcset.getGainline()) {
        // assume gain value is already calculated correctly
        return false;
    }
    jcset.setOffset(offset);
    jcset.setDelay(delay);
    jcset.setLength(length);
    jcset.setFullIRPath(filename);
    jcset.setGainline(gainline);
    double gain = calc_normalized_gain(offset, length, gainline);
    jcset.setGain(gain);
    jcset.setGainCor(gain_cor);
    return true;
}

/**
** signal functions
*/

// remove double entrys from the favourite menu list 
static void remove_double_entry() {
    vector<Glib::ustring>::iterator its;
    vector<Glib::ustring>::iterator it;
    GxJConvSettings& jcset = *GxJConvSettings::instance();
    it = jcset.faflist.begin();
    for (its = jcset.faflist.begin(); its != jcset.faflist.end(); its++) {
        string entry = *its;
        if (its != jcset.faflist.end()-1) {
            it = its+1;
            string next_entry = *it;
            if (entry.compare(next_entry) == 0) {
                jcset.faflist.erase(it);
                gx_system::gx_print_warning(
                    "jconvolver", " remove double entry '" + entry + "'");
            }
        }
    }
}

// add the active file to the favourite menu list
void IRWindow::on_add_button_clicked() {
    Gtk::TreeModel::iterator iter = wcombo->get_active();
    if (iter) {
        GxJConvSettings& jcset = *GxJConvSettings::instance();
        Gtk::TreeModel::Row row = *iter;
        if (row) {
            Glib::ustring name = row[columns.name];
            
            Glib::ustring path = jcset.getIRDir();
            path += "/";
            path += name;
            jcset.faflist.push_back(path);
        }
        std::sort(jcset.faflist.begin(), jcset.faflist.end());
        remove_double_entry();
    }
}

// remove selected file from from favorite menu list
static void remove_favorite_from_menu(GtkMenuItem *menuitem, gpointer data) {
    string  fname = gtk_menu_item_get_label(GTK_MENU_ITEM(menuitem));
    vector<Glib::ustring>::iterator its;
    GxJConvSettings& jcset = *GxJConvSettings::instance();
    for (its = jcset.faflist.begin(); its != jcset.faflist.end(); its++) {
        string entry = *its;
        if (entry.compare(fname) == 0) {
            jcset.faflist.erase(its);
        }
    }
}

// clear the favourite menu list
void IRWindow::on_remove_all_button_clicked() {
    GxJConvSettings& jcset = *GxJConvSettings::instance();
    jcset.faflist.clear();
}

// pop up the favorite menu liste to let select a file for remove
void IRWindow::on_remove_button_clicked() {
    vector<Glib::ustring>::iterator its;
    GxJConvSettings& jcset = *GxJConvSettings::instance();
    GtkWidget* menucont;  // menu container
    GtkWidget* menuitem;  // menu item
    menucont = gtk_menu_new();
    for (its = jcset.faflist.begin(); its != jcset.faflist.end(); its++) {
        string entry = *its;
        menuitem = gtk_menu_item_new_with_mnemonic(entry.c_str());
        gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuitem);
        g_signal_connect(GTK_OBJECT(menuitem), "activate",
                      G_CALLBACK(remove_favorite_from_menu), NULL);
        gtk_widget_show(menuitem);
    }
    guint32 tim = gtk_get_current_event_time();
    gtk_menu_popup(GTK_MENU(menucont), NULL, NULL, NULL,
                          (gpointer) menucont, 2, tim);
}

// load the selcted file into the convolver
// this is the callback for the button in the effect modul
// reloading the combobox isn't needed when only use the effect module
static void set_favorite_from_menu(GtkMenuItem *menuitem, gpointer data) {
    const gchar * fname = gtk_menu_item_get_label(GTK_MENU_ITEM(menuitem));
    GxJConvSettings& jcset = *GxJConvSettings::instance();
    jcset.setFullIRPath(fname);
    IRWindow::get_window()->new_file(fname);
    unsigned int gain_cor      = jcset.getGainCor();
    jcset.setGainCor(gain_cor);
    if (!GxJConvSettings::checkbutton7) {
        GxJConvSettings::checkbutton7 = 1;
        return;
    }
    if(IRWindow::get_window()->save()) {
        gx_convolver_restart();
    }
}

// this is the callback used by the jconv settings widget, 
// combobox will reload also when change a file
static void set_favorite_from_menu_in(GtkMenuItem *menuitem, gpointer data) {
    const gchar * fname = gtk_menu_item_get_label(GTK_MENU_ITEM(menuitem));
    GxJConvSettings& jcset = *GxJConvSettings::instance();
    jcset.setFullIRPath(fname);
    IRWindow::get_window()->new_file(fname);
    g_idle_add(enumerate, NULL);
    if (!GxJConvSettings::checkbutton7) {
        GxJConvSettings::checkbutton7 = 1;
        return;
    }
    if(IRWindow::get_window()->save()) {
        gx_convolver_restart();
    }
}

// create and present the favourite menu list 
// callback inside the jconv settings widget
void IRWindow::on_show_button_clicked_in() {
    vector<Glib::ustring>::iterator its;
    GxJConvSettings& jcset = *GxJConvSettings::instance();
    GtkWidget* menucont;  // menu container
    GtkWidget* menuitem;  // menu item
    menucont = gtk_menu_new();
    for (its = jcset.faflist.begin(); its != jcset.faflist.end(); its++) {
        string entry = *its;
        menuitem = gtk_menu_item_new_with_label(entry.c_str());
        gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuitem);
        g_signal_connect(GTK_OBJECT(menuitem), "activate",
                      G_CALLBACK(set_favorite_from_menu_in), NULL);
        gtk_widget_show(menuitem);
    }
    guint32 tim = gtk_get_current_event_time();
    gtk_menu_popup(GTK_MENU(menucont), NULL, NULL, NULL,
                          (gpointer) menucont, 2, tim);
}

// create and present the favourite menu
// callback from the effect module
void IRWindow::on_show_button_clicked() {
    vector<Glib::ustring>::iterator its;
    GxJConvSettings& jcset = *GxJConvSettings::instance();
    GtkWidget* menucont;  // menu container
    GtkWidget* menuitem;  // menu item
    menucont = gtk_menu_new();
    for (its = jcset.faflist.begin(); its != jcset.faflist.end(); its++) {
        string entry = *its;
        menuitem = gtk_menu_item_new_with_label(entry.c_str());
        gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuitem);
        g_signal_connect(GTK_OBJECT(menuitem), "activate",
                      G_CALLBACK(set_favorite_from_menu), NULL);
        gtk_widget_show(menuitem);
    }
    guint32 tim = gtk_get_current_event_time();
    gtk_menu_popup(GTK_MENU(menucont), NULL, NULL, NULL,
                          (gpointer) menucont, 2, tim);
}

void IRWindow::on_combo_changed() {
    Gtk::TreeModel::iterator iter = wcombo->get_active();
    if (iter) {
        Gtk::TreeModel::Row row = *iter;
        if (row) {
            Glib::ustring name = row[columns.name];
            static Glib::ustring old_name = name;
            GxJConvSettings& jcset = *GxJConvSettings::instance();
            Glib::ustring path = jcset.getIRDir();
            path += "/";
            path += name;
            if (name != old_name) {
                old_name = name;
                load_data(path);
            }
            if (GTK_IS_LABEL(gx_gui::gw.set_label))
                gtk_label_set_text(GTK_LABEL(gx_gui::gw.set_label),name.c_str());
        }
    }
}

void IRWindow::on_remove_tree() {
    delete wcombo;
    wcombo = new Gtk::ComboBox();
    wcombo->set_name("rack_button");
    wboxcombo->add(*wcombo);
    wboxcombo->show_all();
    wcombo->signal_changed().connect(sigc::mem_fun(*this,
              &IRWindow::on_combo_changed) );
}


// reload the treelist for the combobox
void IRWindow::on_enumerate() {
    on_remove_tree();
    wcombo->set_model(model);
    GxJConvSettings& jcset = *GxJConvSettings::instance();
    Glib::ustring path = jcset.getIRDir();
    Glib::RefPtr<Gio::File> file = Gio::File::create_for_path(path);
    if (file->query_exists()) {
        Glib::RefPtr<Gio::FileEnumerator> child_enumeration =
              file->enumerate_children(G_FILE_ATTRIBUTE_STANDARD_NAME);
        std::vector<Glib::ustring> file_names;
        Glib::RefPtr<Gio::FileInfo> file_info;

        while ((file_info = child_enumeration->next_file()) != 0) {
            if (file_info->get_name().size() > 3) { // filefilter
             if (file_info->get_name().compare(file_info->get_name().size()-3, 3, "wav") == 0 ||
                file_info->get_name().compare(file_info->get_name().size()-3, 3, "Wav") == 0 ||
                file_info->get_name().compare(file_info->get_name().size()-3, 3, "WAV") == 0)
                    file_names.push_back(file_info->get_name());
            }
        }
        // sort the vector
        std::sort(file_names.begin(), file_names.end());
        // clear the TreeView
        model->clear();
        // now populate the TreeView
        Gtk::TreeModel::Row row = *(model->append());
        string irfile = jcset.getIRFile();
        for (unsigned int i = 0; i < file_names.size(); i++) {
            row[columns.name] = file_names[i];
            if (file_names[i] == irfile ) wcombo->set_active(i);

            // avoid appending a last empty row
            if (i != file_names.size()-1) {
                row = *(model->append());
            }
        }
        wcombo->pack_start(columns.name, false);
    } else {
        gx_system::gx_print_error("jconvolver", "Error reading file path");
    }
}

void IRWindow::on_linear() {
    wIredit->set_log(not wLinear->get_active());
}

void IRWindow::on_left() {
    if (wLeft->get_active()) {
        wIredit->set_channel(0);
    }
}

void IRWindow::on_right() {
    if (wRight->get_active()) {
        wIredit->set_channel(1);
    }
}

void IRWindow::on_sum() {
    if (wSum->get_active()) {
        wIredit->set_channel(-1);
    }
}

void IRWindow::on_delay_changed(int delay, int fs) {
    int d = static_cast<int>(round(set_val(wDelay, wDelay_ms, delay, fs)));
    if (d != delay) {
        wIredit->set_delay(d);
    }
}

void IRWindow::on_offset_changed(int offset, int fs) {
    set_val(wOffset, wOffset_ms, offset, fs);
}

void IRWindow::on_length_changed(int length, int fs) {
    set_val(wLength, wLength_ms, length, fs);
}

void IRWindow::on_reset_clicked() {
    wIredit->set_offset(0);
    wIredit->set_delay(0);
    wIredit->set_length(audio_size);
    gx_gui::gx_reset_units("jconv");
}

Glib::ustring IRWindow::on_delay_delta_format_value(double v) {
    Glib::ustring s = "";
    if (v < 0.0) {
        v = -v;
        s = " R";
    } else if (v > 0.0) {
        s = " L";
    }
    // boost::format does not support "%*f"
    Glib::ustring fmt = (boost::format("%%.%df%%s") % wDelay_delta->property_digits()).str();
    return (boost::format(fmt) % v % s).str();
}

void IRWindow::on_max_scale_reached(bool v) {
    wIncr->set_sensitive(not v);
}

void IRWindow::on_min_scale_reached(bool v) {
    wDecr->set_sensitive(not v);
}

void IRWindow::on_open() {
    Gtk::FileChooserDialog d(*this, "Select Impulse Response");
    d.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
    d.add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);
    Gtk::FileFilter wav;
    wav.set_name("WAV Files");
    wav.add_pattern("*.wav");
    wav.add_pattern("*.WAV");
    wav.add_pattern("*.Wav");
    d.add_filter(wav);
    Gtk::FileFilter audio;
    audio.set_name("Audio Files");
    audio.add_mime_type("audio/*");
    d.add_filter(audio);
    Gtk::FileFilter all;
    all.add_pattern("*");
    all.set_name("All Files");
    d.add_filter(all);
    if (!filename.empty()) {
        d.set_filename(filename);
    } else {
        d.set_current_folder("/home/ad/Desktop/amp");
    }
    if (d.run() != Gtk::RESPONSE_OK) {
        return;
    }
    string fname = d.get_filename();
    Gtk::RecentManager::Data data;
    bool result_uncertain;
    data.mime_type = Gio::content_type_guess(fname, "", result_uncertain);
    data.app_name = "guitarix";
    data.groups.push_back("impulseresponse");
    Gtk::RecentManager::get_default()->add_item(d.get_uri(), data);
    load_data(fname);
    GxJConvSettings& jcset = *GxJConvSettings::instance();
    jcset.setFullIRPath(fname);
    save_state();
    g_idle_add(enumerate, NULL);
}

void IRWindow::on_home() {
    wIredit->home();
}

void IRWindow::on_jump_zoom_mark() {
    wIredit->jump_zoom_mark();
}

void IRWindow::on_decr() {
    wIredit->decr_scale(0.0);
}

void IRWindow::on_incr() {
    wIredit->incr_scale(0.0);
}

void IRWindow::on_m_delay_changed() {
    wIredit->set_delay(wDelay->cp_get_int_value());
}

void IRWindow::on_ms_delay_changed() {
    wIredit->set_delay(get_ms(wDelay_ms));
}

void IRWindow::on_m_offset_changed() {
    wIredit->set_offset(wOffset->cp_get_int_value());
}

void IRWindow::on_ms_offset_changed() {
    wIredit->set_offset(get_ms(wOffset_ms));
}

void IRWindow::on_m_length_changed() {
    wIredit->set_length(wLength->cp_get_int_value());
}

void IRWindow::on_ms_length_changed() {
    wIredit->set_length(get_ms(wLength_ms));
}

void IRWindow::on_apply_button_clicked() {
    if (!GxJConvSettings::checkbutton7) {
        GxJConvSettings::checkbutton7 = 1;
        return;
    }
    if (save_state()) {
        gx_convolver_restart();
    }
}

void IRWindow::destroy_self() {
    delete this;
    instance = 0;
}

void IRWindow::on_window_hide() {
    Glib::signal_idle().connect(
        sigc::bind_return(sigc::mem_fun(*this, &IRWindow::destroy_self), false));
}

void IRWindow::on_cancel_button_clicked() {
    GxJConvSettings& jcset = *GxJConvSettings::instance();
    string amp = jcset.getIRFile();
    if (GTK_IS_LABEL(gx_gui::gw.set_label))
        gtk_label_set_text(GTK_LABEL(gx_gui::gw.set_label),amp.c_str());
    hide();
}

void IRWindow::on_ok_button_clicked() {
    if (save_state()) {
        gx_convolver_restart();
    }
    GxJConvSettings& jcset = *GxJConvSettings::instance();
    string amp = jcset.getIRFile();
    if (GTK_IS_LABEL(gx_gui::gw.set_label))
        gtk_label_set_text(GTK_LABEL(gx_gui::gw.set_label),amp.c_str());
    hide();
}

void IRWindow::on_help_clicked() {
    wHelp->show();
}

void IRWindow::on_gain_button_toggled() {
    GxJConvSettings& jcset = *GxJConvSettings::instance();
    if (wGain_correction->get_active()) {
        jcset.setGainCor(1);
    } else {
        jcset.setGainCor(0);
    }
}

/****************************************************************
 ** Interface to rest of program
 */
void gx_load_jcgui() {
    IRWindow::create(*gx_gui::GxMainInterface::instance());
    //IRWindow::reload();
}

void gx_show_jconv_dialog_gui(_GtkWidget*, void*) {
    IRWindow::create(*gx_gui::GxMainInterface::instance());
    IRWindow::reload();
    IRWindow::show_window();
}

void gx_reload_jcgui() {
    IRWindow::reload();
}

void gx_save_jcgui() {
    IRWindow::save();
}

void gx_show_fav() {
    IRWindow::show_fav();
}

void gx_load_fav(GtkMenuItem *menuitem, gpointer data) {
    set_favorite_from_menu(menuitem, data);
}

// --------------- static vars
float GxJConvSettings::checkbutton7 = 0.;

// ---------------  constructor
GxJConvSettings::GxJConvSettings() {
    // default parameters
    fIRDir      = getenv("HOME");
    fIRFile     = "";
    fGain       = 0.2;
    fGainCor    = 1;
    fOffset     = 0;
    fLength     = 0;
    fDelay      = 0;
}

string GxJConvSettings::getFullIRPath() const {
    if (fIRFile.empty()) {
        return fIRFile;
    } else {
        return Glib::build_filename(fIRDir, fIRFile);
    }
}

void GxJConvSettings::setFullIRPath(string name) {
    fIRDir = Glib::path_get_dirname(name);
    fIRFile= Glib::path_get_basename(name);
}

void GxJConvSettings::writeJSON(gx_system::JsonWriter& w) {
    w.begin_object(true);
    w.write_key("jconv.IRFile");
    w.write(fIRFile, true);
    w.write_key("jconv.IRDir");
    w.write(fIRDir, true);
    w.write_key("jconv.Gain");
    w.write(fGain, true);
    w.write_key("jconv.GainCor");
    w.write(fGainCor, true);
    w.write_key("jconv.Offset");
    w.write(fOffset, true);
    w.write_key("jconv.Length");
    w.write(fLength, true);
    w.write_key("jconv.Delay");
    w.write(fDelay, true);
    w.write_key("jconv.gainline");
    w.begin_array();
    for (unsigned int i = 0; i < gainline.size(); i++) {
        w.begin_array();
        w.write(gainline[i].i);
        w.write(gainline[i].g);
        w.end_array();
    }
    w.end_array(true);
    
   // w.end_object(true);
    w.write_key("jconv.favorits");
    w.begin_array();
    vector<Glib::ustring>::iterator its;
    bool end = true;
    for (its = faflist.begin(); its != faflist.end(); its++) {
        w.begin_array();
        w.write(*its);
        if (its == faflist.end()-1) end = false;
        w.end_array(end);
    }
    w.end_array(true);
    w.end_object(true);
}

void GxJConvSettings::read_gainline(gx_system::JsonParser& jp) {
    gainline.clear();
    jp.next(gx_system::JsonParser::begin_array);
    while (jp.peek() == gx_system::JsonParser::begin_array) {
        jp.next();
        jp.next(gx_system::JsonParser::value_number);
        gain_points p;
        p.i = jp.current_value_int();
        jp.next(gx_system::JsonParser::value_number);
        p.g = jp.current_value_float();
        jp.next(gx_system::JsonParser::end_array);
        gainline.push_back(p);
    }
    jp.next(gx_system::JsonParser::end_array);
}

void GxJConvSettings::read_favorites(gx_system::JsonParser& jp) {
    jp.next(gx_system::JsonParser::begin_array);
    while (jp.peek() == gx_system::JsonParser::begin_array) {
        jp.next();
        jp.next(gx_system::JsonParser::value_string);
        jp.next(gx_system::JsonParser::end_array);
        faflist.push_back(jp.current_value());
    }
    jp.next(gx_system::JsonParser::end_array);
}

GxJConvSettings::GxJConvSettings(gx_system::JsonParser& jp) {
    jp.next(gx_system::JsonParser::begin_object);
    do {
        jp.next(gx_system::JsonParser::value_key);
        if (jp.current_value() == "jconv.IRFile") {
            jp.next(gx_system::JsonParser::value_string);
            fIRFile = jp.current_value();
        } else if (jp.current_value() == "jconv.IRDir") {
            jp.next(gx_system::JsonParser::value_string);
            fIRDir = jp.current_value();
        } else if (jp.current_value() == "jconv.Gain") {
            jp.next(gx_system::JsonParser::value_number);
            fGain = jp.current_value_float();
        } else if (jp.current_value() == "jconv.GainCor") {
            jp.next(gx_system::JsonParser::value_number);
            fGainCor = jp.current_value_int();
        } else if (jp.current_value() == "jconv.Offset") {
            jp.next(gx_system::JsonParser::value_number);
            fOffset = jp.current_value_int();
        } else if (jp.current_value() == "jconv.Length") {
            jp.next(gx_system::JsonParser::value_number);
            fLength = jp.current_value_int();
        } else if (jp.current_value() == "jconv.Delay") {
            jp.next(gx_system::JsonParser::value_number);
            fDelay = jp.current_value_int();
        } else if (jp.current_value() == "jconv.gainline") {
            read_gainline(jp);
        } else if (jp.current_value() == "jconv.favorits") {
            read_favorites(jp);
        } else {
            gx_system::gx_print_warning("jconv settings", "unknown key: " + jp.current_value());
            jp.skip_object();
        }
    } while (jp.peek() == gx_system::JsonParser::value_key);
    jp.next(gx_system::JsonParser::end_object);
}
} // namespace gx_jconv
