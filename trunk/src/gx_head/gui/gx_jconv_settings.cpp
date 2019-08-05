/*
 * Copyright (C) 2009, 2010, 2013 Hermann Meyer, James Warden, Andreas Degert
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

namespace gx_jconv {

/****************************************************************
 ** Convolver Parameter Window
 */

/*
** static class variables and functions
*/

IRWindow *IRWindow::create(const std::string& unit_id,
			   Glib::RefPtr<Gdk::Pixbuf> icon, gx_engine::GxMachineBase& machine,
			   Glib::RefPtr<Gtk::AccelGroup> accels, int nchan) {
    Glib::RefPtr<gx_gui::GxBuilder> bld = gx_gui::GxBuilder::create_from_file(
	machine.get_options().get_builder_filepath(nchan == 1 ? "iredit_mono.glade" : "iredit.glade"), &machine);
    Gtk::Widget *w;
    if (!machine.get_jack()) {
	bld->find_widget("file_selector_box", w);
	//w->hide();
	//bld->find_widget("dir_combo:rack_button", w);
	//w->show();
    }
    gx_engine::JConvParameter *jcp = dynamic_cast<gx_engine::JConvParameter*>(&machine.get_parameter(unit_id+".convolver"));
    assert(jcp);
    return new IRWindow(bld, jcp, icon, machine, accels, nchan);
}

/*
 ** Constructor
 */

void IRWindow::init_connect() {
    builder->find_widget("iredit", wIredit);
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

    builder->find_widget("file_combo:rack_button", wcombo);
    wcombo->signal_changed().connect(
	sigc::mem_fun(*this, &IRWindow::on_combo_changed));
    wcombo->set_model(model);

    builder->find_widget("dir_combo:rack_button", dircombo);
    if (dircombo->is_visible()) {
	Gtk::TreeModelColumnRecord rec;
	Gtk::TreeModelColumn<std::string> fname_col;
	rec.add(fname_col);
	Gtk::TreeModelColumn<Glib::ustring> dname_col;
	rec.add(dname_col);
	Glib::RefPtr<Gtk::ListStore> st = Gtk::ListStore::create(rec);
	std::vector<gx_system::FileName> dirs;
	machine.load_impresp_dirs(dirs);
	for (std::vector<gx_system::FileName>::iterator i = dirs.begin(); i != dirs.end(); ++i) {
	    Gtk::TreeIter j = st->append();
	    j->set_value(0, i->displayname);
	    j->set_value(1, i->filename);
	}
	dircombo->set_model(st);
	dircombo->signal_changed().connect(
	    sigc::mem_fun(*this, &IRWindow::on_dircombo_changed));
    }

    if (nchan != 1) {
	builder->find_widget("left", wLeft);
	wLeft->signal_toggled().connect(sigc::mem_fun(*this, &IRWindow::on_left));
	builder->find_widget("right", wRight);
	wRight->signal_toggled().connect(sigc::mem_fun(*this, &IRWindow::on_right));
	builder->find_widget("sum", wSum);
	wSum->set_active(true);
	wSum->signal_toggled().connect(sigc::mem_fun(*this, &IRWindow::on_sum));
    } else {
	wLeft = wRight = wSum = 0;
    }

    builder->find_widget("log", wLog);
    wLog->set_active(true);
    builder->find_widget("linear", wLinear);
    wLinear->signal_toggled().connect(sigc::mem_fun(*this, &IRWindow::on_linear));

    builder->find_widget("delay:show_always", wDelay);
    wDelay->signal_value_changed().connect(sigc::mem_fun(*this,
                                           &IRWindow::on_m_delay_changed));
    builder->find_widget("offset:show_always", wOffset);
    wOffset->signal_value_changed().connect(sigc::mem_fun(*this,
                                            &IRWindow::on_m_offset_changed));
    builder->find_widget("irlength:show_always", wLength);
    wLength->signal_value_changed().connect(sigc::mem_fun(*this,
                                            &IRWindow::on_m_length_changed));
    builder->find_widget("delay_ms:show_always", wDelay_ms);
    wDelay_ms->signal_value_changed().connect(sigc::mem_fun(*this,
                                              &IRWindow::on_ms_delay_changed));
    builder->find_widget("offset_ms:show_always", wOffset_ms);
    wOffset_ms->signal_value_changed().connect(sigc::mem_fun(*this,
                                               &IRWindow::on_ms_offset_changed));
    builder->find_widget("irlength_ms:show_always", wLength_ms);
    wLength_ms->signal_value_changed().connect(sigc::mem_fun(*this,
                                               &IRWindow::on_ms_length_changed));

    if (nchan != 1) {
	builder->find_widget("delay_delta", wDelay_delta);
	wDelay_delta->signal_format_value().connect(sigc::mem_fun(*this,
								  &IRWindow::on_delay_delta_format_value));
    }

    builder->find_widget("home", wHome);
    wHome->signal_clicked().connect(sigc::mem_fun(*this, &IRWindow::on_home));
    builder->find_widget("jump_zoom_mark", wJump_zoom_mark);
    wJump_zoom_mark->signal_clicked().connect(sigc::mem_fun(*this,
                                              &IRWindow::on_jump_zoom_mark));
    builder->find_widget("incr", wIncr);
    wIncr->signal_clicked().connect(sigc::mem_fun(*this, &IRWindow::on_incr));
    builder->find_widget("decr", wDecr);
    wDecr->signal_clicked().connect(sigc::mem_fun(*this, &IRWindow::on_decr));

    builder->find_widget("reset_button", wReset);
    wReset->signal_clicked().connect(sigc::mem_fun(*this, &IRWindow::on_reset_clicked));
    builder->find_widget("open_button", wOpen);
    if (!machine.get_jack()) wOpen->set_sensitive(false);
    wOpen->signal_clicked().connect(sigc::mem_fun(*this, &IRWindow::on_open));

    builder->find_widget("apply_button", wApply);
    wApply->signal_clicked().connect(sigc::mem_fun(*this,
                                     &IRWindow::on_apply_button_clicked));

    builder->find_widget("cancel_button", wCancel);
    wCancel->signal_clicked().connect(sigc::mem_fun(*this,
                                      &IRWindow::on_cancel_button_clicked));
    builder->find_widget("ok_button", wOk);
    wOk->signal_clicked().connect(sigc::mem_fun(*this,
                                  &IRWindow::on_ok_button_clicked));

    builder->find_widget("gain_button", wGain_correction);
    autogain_conn = wGain_correction->signal_toggled().connect(
	sigc::mem_fun(*this, &IRWindow::on_gain_button_toggled));

    builder->find_widget("length", wSamples);
    builder->find_widget("samplerate", wSampleRate);
    builder->find_widget("format", wFormat);
    builder->find_widget("channels", wChan);
    builder->find_widget("filename", wFilename);

    if (nchan == 1) {
	wChannelbox = 0;
    } else {
	builder->find_widget("channelbox", wChannelbox);
    }
    Gtk::Button* button;
    builder->find_widget("help_button", button);
    button->signal_clicked().connect(sigc::mem_fun(*this, &IRWindow::on_help_clicked));
    builder->find_widget("HelpIR", wHelp);
    builder->find_widget("close_irhelp", button);
    button->signal_clicked().connect(sigc::mem_fun(wHelp, &Gtk::Widget::hide));

    builder->find_widget("preset_button", button);
    button->signal_clicked().connect(
	sigc::mem_fun(this, &IRWindow::on_preset_popup_clicked));

    gtk_window->signal_key_press_event().connect(
	sigc::mem_fun(this, &IRWindow::on_key_press_event));
}

IRWindow::IRWindow(const Glib::RefPtr<gx_gui::GxBuilder>& bld, gx_engine::JConvParameter *jcp_,
		   Glib::RefPtr<Gdk::Pixbuf> icon, gx_engine::GxMachineBase& machine_,
		   Glib::RefPtr<Gtk::AccelGroup> accels, int nchan_)
    : machine(machine_),
      builder(bld),
      filename(),
      ms(0.0),
      audio_buffer(0),
      audio_size(0),
      audio_chan(0),
      jcp(jcp_),
      gtk_window(0),
      autogain_conn(),
      nchan(nchan_),
      //skipped all gtk widget pointers, will be set in init_connect()
      columns(),
      model(Gtk::TreeStore::create(columns)),
      current_combo_dir() {
    bld->get_toplevel("DisplayIR", gtk_window);

    init_connect();
    gtk_window->set_icon(icon);
    gtk_window->add_accel_group(accels);
    jcp->signal_changed().connect(
	sigc::mem_fun(this, &IRWindow::load_state));
    machine.signal_impresp_list().connect(
	sigc::mem_fun(this, &IRWindow::on_enumerate));

    // reset display
    file_changed("", 0, 0, 0, "");
    on_delay_changed(0, 0);
    on_offset_changed(0, 0);
    on_length_changed(0, 0);
}

IRWindow::~IRWindow() {
    delete gtk_window;
    delete audio_buffer;
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
        s_length = (boost::format("%1%") % length).str();
        s_rate = (boost::format("%1%") % rate).str();
	s_channels = (boost::format("%1%") % channels).str();
    }
    wSamples->set_text(s_length);
    wSampleRate->set_text(s_rate);
    wFormat->set_text(format);
    wChan->set_text(s_channels);
    if (nchan != 1) {
	wChannelbox->set_sensitive(channels >= 2);
    }
    wFilename->set_text(Glib::path_get_dirname(filename));
}

void IRWindow::load_state(const gx_engine::GxJConvSettings* jcs) {
    string path = jcs->getFullIRPath();
    if (path.empty()) {
	wIredit->set_ir_data(0, 0, 0, 0);
        return;
    }
    gx_engine::GxJConvSettings jc;
    make_state(jc);
    if (jc == *jcs) {
	return;
    }
    autogain_conn.block();
    wGain_correction->set_active(jcs->getGainCor());
    autogain_conn.unblock();
    load_data(path, jcs->getOffset(), jcs->getDelay(), jcs->getLength(), jcs->getGainline());
    reload_impresp_list();
}

Gainline IRWindow::gain0 = Gainline();

bool IRWindow::load_data(Glib::ustring f, int offset, int delay, int length, const Gainline& gain) {
    filename = f;
    int audio_type, audio_form, audio_rate;
    float *buffer;
    if (!machine.read_audio(filename, &audio_size, &audio_chan, &audio_type, &audio_form, &audio_rate, &buffer)) {
	return false;
    }
    Glib::ustring enc;
    switch (audio_type) {
    case gx_engine::Audiofile::TYPE_OTHER: enc = "???"; break;
    case gx_engine::Audiofile::TYPE_CAF: enc = "CAF"; break;
    case gx_engine::Audiofile::TYPE_WAV: enc = "WAV"; break;
    case gx_engine::Audiofile::TYPE_AIFF: enc = "AIFF"; break;
    case gx_engine::Audiofile::TYPE_AMB: enc = "AMB"; break;
    }
    enc += " ";
    switch (audio_form) {
    case gx_engine::Audiofile::FORM_OTHER: enc += "?"; break;
    case gx_engine::Audiofile::FORM_16BIT: enc += "16 bit"; break;
    case gx_engine::Audiofile::FORM_24BIT: enc += "24 bit"; break;
    case gx_engine::Audiofile::FORM_32BIT: enc += "32 bit"; break;
    case gx_engine::Audiofile::FORM_FLOAT: enc += "float"; break;
    }
    delete[] audio_buffer;
    audio_buffer = buffer;
    file_changed(filename, audio_rate, audio_size, audio_chan, enc);
    if (!length) {
	length = audio_size;
    }
    wIredit->set_state(audio_buffer, audio_chan, audio_size, audio_rate, offset, offset+length, delay-offset, gain);
    if (wSum) {
	wSum->set_active(true);
    }
    wLog->set_active(true);
    return true;
}

double IRWindow::calc_normalized_gain(int offset, int length, const Gainline& points) {
    if (audio_chan == 0) {
	return 1.0;
    }
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
	    gx_engine::GxConvolver::compute_interpolation(fct, gp, idx, points, 0);
        }
    }
    for (int i = offset; i < offset+length; i++) {
        if (idx+1 < points.size() && points[idx].i == i) {
            gx_engine::GxConvolver::compute_interpolation(fct, gp, idx, points, 0);
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

void IRWindow::make_state(gx_engine::GxJConvSettings& jc) {
    Gainline gainline = wIredit->get_gain();
    unsigned int offset = wIredit->get_offset();
    unsigned int length = wIredit->get_length();
    double gain = calc_normalized_gain(offset, length, gainline);
    jc.setDelay(wIredit->get_delay());
    jc.setOffset(offset);
    jc.setLength(length);
    jc.setFullIRPath(filename);
    jc.setGainline(gainline);
    jc.setGain(gain);
    jc.setGainCor(wGain_correction->get_active());
}

void IRWindow::save_state() {
    gx_engine::GxJConvSettings jc;
    make_state(jc);
    jcp->set(jc);
}

/**
** signal functions
*/

void IRWindow::on_combo_changed() {
    Gtk::TreeModel::iterator iter = wcombo->get_active();
    if (iter) {
        Gtk::TreeModel::Row row = *iter;
        if (row) {
            std::string fname = row[columns.filename];
	    if (fname != jcp->get_value().getIRFile()) {
		load_data(Glib::build_filename(current_combo_dir, fname));
		save_state();
            }
        }
    }
}

void IRWindow::on_dircombo_changed() {
    Gtk::TreeModel::iterator iter = dircombo->get_active();
    if (iter) {
	std::string dir;
	iter->get_value(1, dir);
	if (dir != current_combo_dir) {
	    machine.reload_impresp_list(dir);
        }
    }
}

void IRWindow::reload_impresp_list() {
    std::string path = jcp->get_value().getIRDir();
    if (path == "~/") {  // cruft in old files
	path = getenv("HOME");
    }
    string irfile = jcp->get_value().getIRFile();
    if (current_combo_dir == path) {
	Gtk::TreeNodeChildren ch = model->children();
	for (Gtk::TreeIter i = ch.begin(); i != ch.end(); ++i) {
	    if (i->get_value(columns.filename) == irfile) {
		wcombo->set_active(i);
	    }
	}
	return;
    }
    machine.reload_impresp_list(path);
}

// reload the treelist for the combobox
void IRWindow::on_enumerate(const std::string& path, const std::vector<gx_system::FileName>& l) {
    if (current_combo_dir == path) {
	return;
    }
    current_combo_dir = path;
    string irfile = jcp->get_value().getIRFile();
    model->clear();
    Gtk::TreeIter j;
    wcombo->unset_model();
    model->set_sort_column(Gtk::TreeSortable::DEFAULT_UNSORTED_COLUMN_ID, Gtk::SORT_ASCENDING);
    for (std::vector<gx_system::FileName>::const_iterator f = l.begin(); f != l.end(); ++f) {
	Gtk::TreeIter i = model->append();
	i->set_value(columns.displayname, f->displayname);
	i->set_value(columns.filename, f->filename);
	if (f->filename == irfile) {
	    j = i;
	}
    }
    model->set_sort_column(columns.displayname, Gtk::SORT_ASCENDING);
    wcombo->set_model(model);
    if (j) {
	wcombo->set_active(j);
    }
    if (dircombo->is_visible()) {
	Gtk::TreeNodeChildren ch = dircombo->get_model()->children();
	for (Gtk::TreeIter di = ch.begin(); di != ch.end(); ++di) {
	    std::string p;
	    di->get_value(1, p);
	    if (p == current_combo_dir) {
		dircombo->set_active(di);
		break;
	    }
	}
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
    gx_engine::GxJConvSettings jc;
    jc.setDelay(0);
    jc.setOffset(0);
    jc.setLength(audio_size);
    jc.setFullIRPath(filename);
    jc.setGainline(gain0);
    jc.setGain(calc_normalized_gain(0, audio_size, gain0));
    jc.setGainCor(true);
    jcp->set(jc);
    const char *params[] = {"jconv.balance", "jconv.diff_delay", "jconv.gain", "jconv.wet_dry", 0};
    for (const char **p = params; *p; ++p) {
	gx_engine::Parameter& pm = machine.get_parameter(*p);
	pm.stdJSON_value();
	pm.setJSON_value();
    }
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
    static Glib::ustring hostname = "localhost";
    if (! machine.get_jack()) {
        hostname = Gio::Resolver::get_default()->lookup_by_address
          (Gio::InetAddress::create( machine.get_options().get_rpcaddress()));
    }
    Glib::ustring title = hostname + ": Select Impulse Response";
    Gtk::FileChooserDialog d(*gtk_window, title);
    d.set_local_only(false);
    d.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
    d.add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);
    d.add_shortcut_folder_uri(Glib::filename_to_uri(GX_SOUND_BPA_DIR, hostname));
    d.add_shortcut_folder_uri(Glib::filename_to_uri(GX_SOUND_BPB_DIR, hostname));
    d.add_shortcut_folder_uri(Glib::filename_to_uri(string(getenv("HOME")) + string("/.config/guitarix/IR"), hostname));
    Glib::RefPtr<Gtk::FileFilter> wav;
    wav->set_name("WAV Files");
    wav->add_mime_type("audio/x-wav");
    wav->add_mime_type("audio/x-aiff");
    d.add_filter(wav);
    Glib::RefPtr<Gtk::FileFilter> audio;
    audio->set_name("Audio Files");
    audio->add_mime_type("audio/*");
    d.add_filter(audio);
    Glib::RefPtr<Gtk::FileFilter> all;
    all->add_pattern("*");
    all->set_name("All Files");
    d.add_filter(all);
    if (!filename.empty()) {
        d.set_uri(Glib::filename_to_uri (filename, hostname));
    } else {
        d.set_current_folder_uri(Glib::filename_to_uri (string(getenv("HOME")) + string("/"), hostname));
    }
    if (d.run() != Gtk::RESPONSE_OK) {
        return;
    }
    filename = Glib::filename_from_uri(d.get_uri(), hostname);
    Gtk::RecentManager::Data data;
    bool result_uncertain;
    data.mime_type = Gio::content_type_guess(filename, "", result_uncertain);
    data.app_name = "guitarix";
    data.groups.push_back("impulseresponse");
    Gtk::RecentManager::get_default()->add_item(d.get_uri(), data);
    load_data(filename);
    save_state();
    reload_impresp_list();
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
    machine.pluginlist_lookup_plugin(jcp->group_id())->set_on_off(true);
    save_state();
}

void IRWindow::destroy_self() {
    delete this;
}

void IRWindow::on_window_hide() {
    Glib::signal_idle().connect(
        sigc::bind_return(sigc::mem_fun(*this, &IRWindow::destroy_self), false));
}

void IRWindow::on_cancel_button_clicked() {
    gtk_window->hide();
}

void IRWindow::on_ok_button_clicked() {
    save_state();
    gtk_window->hide();
}

void IRWindow::on_preset_popup_clicked() {
    Glib::ustring name = Glib::path_get_basename(filename);
    Glib::ustring::size_type n = name.find_last_of('.');
    if (n != Glib::ustring::npos) {
	name.erase(n);
    }
    save_state();
    new PluginPresetPopup(machine.pluginlist_lookup_plugin(jcp->group_id())->get_pdef(), machine, name);
}

void IRWindow::on_help_clicked() {
    wHelp->show();
}

void IRWindow::on_gain_button_toggled() {
    save_state();
}

bool IRWindow::on_key_press_event(GdkEventKey *event) {
    if (event->keyval == GDK_KEY_Escape && (event->state & Gtk::AccelGroup::get_default_mod_mask()) == 0) {
	gtk_window->hide();
	return true;
    }
    return false;
}

void IRWindow::reload_and_show() {
    if (gtk_window->get_visible() && !(gtk_window->get_window()->get_state() & Gdk::WINDOW_STATE_ICONIFIED)) {
	gtk_window->hide();
    } else {
	load_state(&jcp->get_value());
	gtk_window->present();
    }
}

} // namespace gx_jconv
