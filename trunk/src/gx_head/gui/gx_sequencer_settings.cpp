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

namespace gx_seq {

/****************************************************************
 ** Sequencer Parameter Window
 */

/*
** static class variables and functions
*/

SEQWindow *SEQWindow::create(const std::string& unit_id, gx_engine::GxMachineBase& machine) {
    Glib::RefPtr<gx_gui::GxBuilder> bld = gx_gui::GxBuilder::create_from_file(
	machine.get_options().get_builder_filepath("Sequencer.glade"), &machine);
    gx_engine::SeqParameter *tomp = dynamic_cast<gx_engine::SeqParameter*>(&machine.get_parameter("seq.sequencer.tom"));
    gx_engine::SeqParameter *kickp = dynamic_cast<gx_engine::SeqParameter*>(&machine.get_parameter("seq.sequencer.kick"));
    gx_engine::SeqParameter *snarep = dynamic_cast<gx_engine::SeqParameter*>(&machine.get_parameter("seq.sequencer.snare"));
    gx_engine::SeqParameter *hatp = dynamic_cast<gx_engine::SeqParameter*>(&machine.get_parameter("seq.sequencer.hat"));
    assert(tomp);
    return new SEQWindow(bld, tomp, kickp, snarep, hatp, machine);
}

/*
 ** Constructor
 */

SEQWindow::SEQWindow(const Glib::RefPtr<gx_gui::GxBuilder>& bld,gx_engine::SeqParameter *tomp_,
         gx_engine::SeqParameter *kickp_, gx_engine::SeqParameter *snarep_,
         gx_engine::SeqParameter *hatp_, gx_engine::GxMachineBase& machine_)
    : machine(machine_),
      builder(bld),
      tomp(tomp_),
      kickp(kickp_),
      snarep(snarep_),
      hatp(hatp_),
      gtk_window(0) {
    bld->get_toplevel("SequencerWindow", gtk_window);

    init_connect();

    // reset display
}

void SEQWindow::init_connect() {


    builder->find_widget("hbox1", tom_box);
    builder->find_widget("hbox2", kick_box);
    builder->find_widget("hbox3", snare_box);
    builder->find_widget("hbox4", hat_box);
    builder->find_widget("gxportdisplay1", seq_pos);

    tomp->signal_changed().connect(sigc::bind(
      sigc::mem_fun(this, &SEQWindow::seq_changed), tom_box));
    kickp->signal_changed().connect(sigc::bind(
      sigc::mem_fun(this, &SEQWindow::seq_changed), kick_box));
    snarep->signal_changed().connect(sigc::bind(
      sigc::mem_fun(this, &SEQWindow::seq_changed), snare_box));
    hatp->signal_changed().connect(sigc::bind(
      sigc::mem_fun(this, &SEQWindow::seq_changed), hat_box));

    Glib::ListHandle<Gtk::Widget*> tomList = tom_box->get_children();
    for (Glib::ListHandle<Gtk::Widget*>::iterator itt = tomList.begin();itt != tomList.end(); ++itt) {
        dynamic_cast<Gtk::ToggleButton*>((*itt))->signal_clicked().connect(
          sigc::bind(sigc::bind(sigc::mem_fun(this, &SEQWindow::on_seq_button_clicked),tomp),tom_box));
    }
    
    Glib::ListHandle<Gtk::Widget*> kickList = kick_box->get_children();
    for (Glib::ListHandle<Gtk::Widget*>::iterator itt = kickList.begin();itt != kickList.end(); ++itt) {
        dynamic_cast<Gtk::ToggleButton*>((*itt))->signal_clicked().connect(
          sigc::bind(sigc::bind(sigc::mem_fun(this, &SEQWindow::on_seq_button_clicked),kickp),kick_box));
    }

    Glib::ListHandle<Gtk::Widget*> snareList = snare_box->get_children();
    for (Glib::ListHandle<Gtk::Widget*>::iterator itt = snareList.begin();itt != snareList.end(); ++itt) {
        dynamic_cast<Gtk::ToggleButton*>((*itt))->signal_clicked().connect(
          sigc::bind(sigc::bind(sigc::mem_fun(this, &SEQWindow::on_seq_button_clicked),snarep),snare_box));
    }

    Glib::ListHandle<Gtk::Widget*> hatList = hat_box->get_children();
    for (Glib::ListHandle<Gtk::Widget*>::iterator itt = hatList.begin();itt != hatList.end(); ++itt) {
        dynamic_cast<Gtk::ToggleButton*>((*itt))->signal_clicked().connect(
          sigc::bind(sigc::bind(sigc::mem_fun(this, &SEQWindow::on_seq_button_clicked),hatp),hat_box));
    }

    seq_pos->set_name("playhead2");
    seq_pos->cp_set_value(0.0);
    std::string id;
    seq_pos->get_property("var_id",id);
    Glib::signal_timeout().connect(sigc::bind<Gxw::Regler*>(sigc::bind<const std::string>(
      sigc::mem_fun(*this, &SEQWindow::get_sequencer_pos),id), seq_pos), 60);

    gtk_window->signal_key_press_event().connect(
      sigc::mem_fun(this, &SEQWindow::on_key_press_event));
}

bool SEQWindow::get_sequencer_pos(Gxw::Regler * regler, const std::string id) {
    if (machine.parameter_hasId(id)) {
        if (machine.get_parameter_value<bool>(id.substr(0,id.find_last_of(".")+1)+"on_off")) {
            machine.signal_parameter_value<float>(id)(machine.get_parameter_value<float>(id));
        }
        return true;
    } else {
        return false;
    }
}

bool SEQWindow::on_key_press_event(GdkEventKey *event) {
    return true;
}

void SEQWindow::on_seq_button_clicked(Gtk::HBox *box, gx_engine::SeqParameter *p) {
    std::vector<int> sequence;
    gx_engine::GxSeqSettings seqc;
    Glib::ListHandle<Gtk::Widget*> seqList = box->get_children();
    for (Glib::ListHandle<Gtk::Widget*>::iterator itt = seqList.begin();itt != seqList.end(); ++itt) {
        sequence.push_back(dynamic_cast<Gtk::ToggleButton*>((*itt))->get_active());
    }
    seqc.setseqline(sequence);
    p->set(seqc);
}

void SEQWindow::seq_changed(const gx_engine::GxSeqSettings* seqc, Gtk::HBox *box) {

    Glib::ListHandle<Gtk::Widget*> seqList = box->get_children();
    Glib::ListHandle<Gtk::Widget*>::iterator itt = seqList.begin();
    std::vector<int> sequence = seqc->getseqline();
    for (std::vector<int>::const_iterator i = sequence.begin(); i != sequence.end(); ++i) {
        dynamic_cast<Gtk::ToggleButton*>((*itt))->set_active(*i);
        ++itt;
    }
}

void SEQWindow::reload_and_show() {
    if (gtk_window->get_visible() && !(gtk_window->get_window()->get_state() & Gdk::WINDOW_STATE_ICONIFIED)) {
        gtk_window->hide();
    } else {
        seq_changed(&tomp->get_value(), tom_box);
        seq_changed(&kickp->get_value(), kick_box);
        seq_changed(&snarep->get_value(), snare_box);
        seq_changed(&hatp->get_value(), hat_box);
        gtk_window->present();
    }
}

SEQWindow::~SEQWindow() {
    delete gtk_window;
}

} // end namespace 
