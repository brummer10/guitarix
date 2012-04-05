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

namespace gx_jconv {

/****************************************************************
 ** Convolver Parameter Window
 */

/*
** static class variables and functions
*/

IRWindow *IRWindow::instance = 0;

IRWindow *IRWindow::create(gx_ui::GxUI& ui, gx_engine::ConvolverAdapter& convolver_, Glib::RefPtr<Gdk::Pixbuf> icon) {
    if (!instance) {
	Glib::RefPtr<gx_gui::GxBuilder> bld = gx_gui::GxBuilder::create_from_file(
	    gx_system::get_options().get_builder_filepath("iredit.glade"), &ui);
	instance = new IRWindow(bld, convolver_, icon);
    }
    return instance;
}

/*
 ** Constructor
 */

void IRWindow::init_connect() {
    builder->find_widget("vbox11", wboxcombo);
    wboxcombo->add(*wcombo);
    wboxcombo->show_all();

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

    builder->find_widget("left", wLeft);
    wLeft->signal_toggled().connect(sigc::mem_fun(*this, &IRWindow::on_left));
    builder->find_widget("right", wRight);
    wRight->signal_toggled().connect(sigc::mem_fun(*this, &IRWindow::on_right));
    builder->find_widget("sum", wSum);
    wSum->set_active(true);
    wSum->signal_toggled().connect(sigc::mem_fun(*this, &IRWindow::on_sum));

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

    builder->find_widget("delay_delta", wDelay_delta);
    wDelay_delta->signal_format_value().connect(sigc::mem_fun(*this,
                                                &IRWindow::on_delay_delta_format_value));

    builder->find_widget("home", wHome);
    wHome->signal_clicked().connect(sigc::mem_fun(*this, &IRWindow::on_home));
    builder->find_widget("jump_zoom_mark", wJump_zoom_mark);
    wJump_zoom_mark->signal_clicked().connect(sigc::mem_fun(*this,
                                              &IRWindow::on_jump_zoom_mark));
    builder->find_widget("incr", wIncr);
    wIncr->signal_clicked().connect(sigc::mem_fun(*this, &IRWindow::on_incr));
    builder->find_widget("decr", wDecr);
    wDecr->signal_clicked().connect(sigc::mem_fun(*this, &IRWindow::on_decr));

    builder->find_widget("add_button", wadd);
    builder->find_widget("ablabel", wladd);
    wladd->set_name("beffekt_label");
    wadd->set_name("rack_button");
    wadd->signal_clicked().connect(sigc::mem_fun(*this, &IRWindow::on_add_button_clicked));

    builder->find_widget("list_button", wshow);
    builder->find_widget("sflabel", wlshow);
    wlshow->set_name("beffekt_label");
    wshow->set_name("rack_button");
    wshow->signal_clicked().connect(sigc::mem_fun(*this, &IRWindow::on_show_button_clicked_in));
    
    builder->find_widget("remove_button", wremove);
    builder->find_widget("relabel", wlremove);
    wlremove->set_name("beffekt_label");
    wremove->set_name("rack_button");
    wremove->signal_clicked().connect(sigc::mem_fun(*this, &IRWindow::on_remove_button_clicked));

    builder->find_widget("remove_list_button", wremoveall);
    builder->find_widget("rllabel", wlremoveall);
    wlremoveall->set_name("beffekt_label");
    wremoveall->set_name("rack_button");
    wremoveall->signal_clicked().connect(sigc::mem_fun(*this, &IRWindow::on_remove_all_button_clicked));

    builder->find_widget("reset_button", wReset);
    wReset->signal_clicked().connect(sigc::mem_fun(*this, &IRWindow::on_reset_clicked));
    builder->find_widget("open_button", wOpen);
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
    wGain_correction->signal_toggled().connect(sigc::mem_fun(*this,
                                               &IRWindow::on_gain_button_toggled));

    builder->find_widget("length", wSamples);
    builder->find_widget("samplerate", wSampleRate);
    builder->find_widget("format", wFormat);
    builder->find_widget("filename", wFilename);

    builder->find_widget("channelbox", wChannelbox);

    Gtk::Button* button;
    builder->find_widget("help_button", button);
    button->signal_clicked().connect(sigc::mem_fun(*this, &IRWindow::on_help_clicked));
    builder->find_widget("HelpIR", wHelp);
    builder->find_widget("close_irhelp", button);
    button->signal_clicked().connect(sigc::mem_fun(wHelp, &Gtk::Widget::hide));
}

void IRWindow::set_GainCor() {
    wGain_correction->set_active(convolver.jcset.getGainCor());
}

IRWindow::IRWindow(const Glib::RefPtr<gx_gui::GxBuilder>& bld, gx_engine::ConvolverAdapter& convolver_, Glib::RefPtr<Gdk::Pixbuf> icon)
    : builder(bld), filename(), ms(0.0), audio_buffer(0),
      audio_size(0), audio_chan(0), convolver(convolver_), gtk_window(0),
      //skipped all gtk widget pointers, will be set in init_connect()
      wcombo(), wboxcombo(), treeview(), model(), columns(), menucont(0) {
    bld->get_toplevel("DisplayIR", gtk_window);
    // setup the TreeView
    treeview = new Gtk::TreeView;
    model = Gtk::TreeStore::create(columns);
    treeview->set_headers_visible(false);
    treeview->set_model(model);
    treeview->append_column("", columns.name);
    wcombo = new Gtk::ComboBox();
    wcombo->set_name("rack_button");

    init_connect();
    gtk_window->set_icon(icon);
    set_GainCor();

    // reset display
    file_changed("", 0, 0, 0, "");
    on_delay_changed(0, 0);
    on_offset_changed(0, 0);
    on_length_changed(0, 0);
}

IRWindow::~IRWindow() {
    delete gtk_window;
    delete audio_buffer;
    delete treeview;
    delete wcombo;
    delete menucont;
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
        save_state();
    }
    wSamples->set_text(s_length);
    wSampleRate->set_text(s_rate);
    wFormat->set_text(format);
    wChannelbox->set_sensitive(channels >= 2);
    wFilename->set_text(Glib::path_get_dirname(filename));
}

// wrapper function to reload the cmbobox tree in a idle loop
gboolean enumerate(gpointer arg) {
    IRWindow::get_window()->on_enumerate();
    return false;
}

void IRWindow::load_state() {
    string path = convolver.jcset.getFullIRPath();
    if (path.empty()) {
        return;
    }
    wIredit->set_offset(convolver.jcset.getOffset());
    wIredit->set_delay(convolver.jcset.getDelay());
    wIredit->set_length(convolver.jcset.getLength());
    if (load_data(path) && convolver.jcset.getGainline().size()) {
        wIredit->set_gain(convolver.jcset.getGainline());
    }
    g_idle_add(enumerate, NULL);
}

bool IRWindow::load_data(Glib::ustring f) {
    filename = f;
    gx_engine::Audiofile audio;
    if (audio.open_read(filename)) {
        gx_system::gx_print_error("jconvolver", "Unable to open '" + filename + "'");
	audio_size = audio_chan = 0;
        return false;
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
        return false;
    }
    float *buffer = new float[audio_size*audio_chan];
    if (audio.read(buffer, audio_size) != static_cast<int>(audio_size)) {
	delete[] buffer;
        gx_system::gx_print_error("jconvolver", "Error reading file");
        return false;
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
    delete[] audio_buffer;
    audio_buffer = buffer;
    wIredit->set_ir_data(audio_buffer, audio_chan, audio_size, audio.rate());
    file_changed(filename, audio.rate(), audio_size, audio_chan, enc);
    wSum->set_active(true);
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

bool IRWindow::save_state() {
    unsigned int offset = wIredit->get_offset();
    unsigned int length = wIredit->get_length();
    unsigned int delay = wIredit->get_delay();
    bool gain_cor      = convolver.jcset.getGainCor();
    Gainline gainline = wIredit->get_gain();
    if (offset == convolver.jcset.getOffset() &&
        delay == convolver.jcset.getDelay() &&
        length == convolver.jcset.getLength() &&
        filename == convolver.jcset.getFullIRPath() &&
        gainline ==  convolver.jcset.getGainline()) {
        // assume gain value is already calculated correctly
        return false;
    }
    convolver.jcset.setOffset(offset);
    convolver.jcset.setDelay(delay);
    convolver.jcset.setLength(length);
    convolver.jcset.setFullIRPath(filename);
    convolver.jcset.setGainline(gainline);
    double gain = calc_normalized_gain(offset, length, gainline);
    convolver.jcset.setGain(gain);
    convolver.jcset.setGainCor(gain_cor);
    return true;
}

/**
** signal functions
*/

// add the active file to the favourite menu list
void IRWindow::on_add_button_clicked() {
    Gtk::TreeModel::iterator iter = wcombo->get_active();
    if (iter && *iter) {
	Glib::ustring path = convolver.jcset.getIRDir() + "/" + (*iter)[columns.name];
	convolver.jcset.faflist.remove(path);
	convolver.jcset.faflist.push_back(path);
	// (sorting is optional)
	convolver.jcset.faflist.sort();
    }
}

// remove selected file from from favorite menu list
void IRWindow::remove_favorite_from_menu(Glib::ustring fname) {
    convolver.jcset.faflist.remove(fname);
}

// clear the favourite menu list
void IRWindow::on_remove_all_button_clicked() {
    convolver.jcset.faflist.clear();
}

void IRWindow::make_popup_menu(void (IRWindow::*action)(Glib::ustring)) {
    delete menucont;
    menucont = new Gtk::Menu;
    Gtk::MenuItem* menuitem;
    for (gx_engine::GxJConvSettings::faf_iterator its = convolver.jcset.faflist.begin(); its != convolver.jcset.faflist.end(); its++) {
        string entry = *its;
        menuitem = manage(new Gtk::MenuItem(entry, true));
        menucont->add(*menuitem);
        menuitem->show();
	menuitem->signal_activate().connect(
	    sigc::bind<Glib::ustring>(mem_fun(*this, action),menuitem->get_label()));
    }
    guint32 tim = gtk_get_current_event_time();
    menucont->popup(2, tim);
}

// pop up the favorite menu liste to let select a file for remove
void IRWindow::on_remove_button_clicked() {
    make_popup_menu(&IRWindow::remove_favorite_from_menu);
}

// load the selcted file into the convolver
// this is the callback for the button in the effect modul
// reloading the combobox isn't needed when only use the effect module
void IRWindow::set_favorite_from_menu(Glib::ustring fname) {
    convolver.jcset.setFullIRPath(fname);
    new_file(fname);
    bool gain_cor = convolver.jcset.getGainCor();
    convolver.jcset.setGainCor(gain_cor);
    if (!convolver.plugin.on_off) {
        convolver.plugin.on_off = true;
        return;
    }
    save_state();
    convolver.restart();
}

// this is the callback used by the jconv settings widget, 
// combobox will reload also when change a file
void IRWindow::set_favorite_from_menu_in(Glib::ustring fname) {
    convolver.jcset.setFullIRPath(fname);
    new_file(fname);
    g_idle_add(enumerate, NULL);
    if (!convolver.plugin.on_off) {
        convolver.plugin.on_off = true;
        return;
    }
    save_state();
    convolver.restart();
}

// create and present the favourite menu list 
void IRWindow::on_show_button_clicked_in() {
    make_popup_menu(&IRWindow::set_favorite_from_menu_in);
}

// create and present the favourite menu
// callback from the effect module
void IRWindow::on_show_button_clicked() {
    make_popup_menu(&IRWindow::set_favorite_from_menu);
}

void IRWindow::on_combo_changed() {
    Gtk::TreeModel::iterator iter = wcombo->get_active();
    if (iter) {
        Gtk::TreeModel::Row row = *iter;
        if (row) {
            Glib::ustring name = row[columns.name];
            static Glib::ustring old_name = name;
            Glib::ustring path = convolver.jcset.getIRDir();
            path += "/";
            path += name;
            if (name != old_name) {
                old_name = name;
                load_data(path);
            }
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
    Glib::ustring path = convolver.jcset.getIRDir();
    if (path == "~/") {  // cruft in old files
	path = getenv("HOME");
    }
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
        string irfile = convolver.jcset.getIRFile();
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
        gx_system::gx_print_error(
	    "jconvolver",
	    boost::format(_("Error reading file path %1%")) % path);
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
    gx_engine::parameter_map.reset_unit("jconv");
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
    Gtk::FileChooserDialog d(*gtk_window, "Select Impulse Response");
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
        d.set_current_folder(string(getenv("HOME")) + string("/"));
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
    convolver.jcset.setFullIRPath(fname);
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
    if (!convolver.plugin.on_off) {
        convolver.plugin.on_off = true;
        return;
    }
    /* assuming users only press apply when they have change settings
     * we could remove the depence on settings change here
     * therefore we could save_state() as soon file_changed()
     * to avoid that the covolver get feed with wrong settings
     * and produce garbage output.
     * Otherwise the convolver simply restart also when no changes have 
     * happen, witch isn't a problem.  Comment ? --> remove this comment */
    //if (save_state()) {
        save_state();
        convolver.restart();
    //}
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
    gtk_window->hide();
}

void IRWindow::on_ok_button_clicked() {
    if (save_state()) {
        convolver.restart();
    }
    gtk_window->hide();
}

void IRWindow::on_help_clicked() {
    wHelp->show();
}

void IRWindow::on_gain_button_toggled() {
    convolver.jcset.setGainCor(wGain_correction->get_active());
}

void IRWindow::reload_and_show() {
    load_state();
    gtk_window->show();
}

} // namespace gx_jconv
