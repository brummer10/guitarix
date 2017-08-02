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
    tomp->signal_changed().connect(
	sigc::mem_fun(this, &SEQWindow::tom_changed));
    kickp->signal_changed().connect(
	sigc::mem_fun(this, &SEQWindow::kick_changed));
    snarep->signal_changed().connect(
	sigc::mem_fun(this, &SEQWindow::snare_changed));
     hatp->signal_changed().connect(
 	sigc::mem_fun(this, &SEQWindow::hat_changed));

    // reset display
}

void SEQWindow::init_connect() {
    builder->find_widget("label1:rack_label_inverse", tom);
    builder->find_widget("label2:rack_label_inverse", kick);
    builder->find_widget("label3:rack_label_inverse", snare);
    builder->find_widget("label4:rack_label_inverse", hat);
    builder->find_widget("label5:rack_label_inverse", bpm);
    builder->find_widget("label6:rack_label_inverse", gain);

    builder->find_widget("gxsmallknob1", tom_gain);
    builder->find_widget("gxsmallknob2", kick_gain);
    builder->find_widget("gxsmallknob3", snare_gain);
    builder->find_widget("gxsmallknob4", hat_gain);
    builder->find_widget("gxsmallknob5", bpm_seq);
    builder->find_widget("gxselector1", tact_seq);
    builder->find_widget("gxhslider1", seq_gain);

    int b = 1;
    for (int i = 0; i<24; ++i) {
        Glib::ustring button = "togglebutton"+Glib::ustring::format(b);
        builder->find_widget(button, tom_seq[i]);
        tom_seq[i]->signal_clicked().connect(
          sigc::bind(sigc::mem_fun(this, &SEQWindow::on_seq_button_clicked),0));
        ++b;
    }
    b = 25;
    for (int i = 0; i<24; ++i) {
        Glib::ustring button = "togglebutton"+Glib::ustring::format(b);
        builder->find_widget(button, kick_seq[i]);
        kick_seq[i]->signal_clicked().connect(
          sigc::bind(sigc::mem_fun(this, &SEQWindow::on_seq_button_clicked),1));
        ++b;
    }
    b = 49;
    for (int i = 0; i<24; ++i) {
        Glib::ustring button = "togglebutton"+Glib::ustring::format(b);
        builder->find_widget(button, snare_seq[i]);
        snare_seq[i]->signal_clicked().connect(
          sigc::bind(sigc::mem_fun(this, &SEQWindow::on_seq_button_clicked),2));
        ++b;
    }
    b = 73;
    for (int i = 0; i<24; ++i) {
        Glib::ustring button = "togglebutton"+Glib::ustring::format(b);
        builder->find_widget(button, hat_seq[i]);
        hat_seq[i]->signal_clicked().connect(
          sigc::bind(sigc::mem_fun(this, &SEQWindow::on_seq_button_clicked),3));
        ++b;
    }
    gtk_window->signal_key_press_event().connect(
      sigc::mem_fun(this, &SEQWindow::on_key_press_event));
}

bool SEQWindow::on_key_press_event(GdkEventKey *event) {
	return true;
}
void SEQWindow::tom_changed(const gx_engine::GxSeqSettings* tomp) {

    std::vector<int> tomsequence = tomp->getseqline();
    int j = 0;
    for (std::vector<int>::const_iterator i = tomsequence.begin(); i != tomsequence.end(); ++i) {
        tom_seq[j]->set_active(*i);
        ++j;
    }
}
void SEQWindow::kick_changed(const gx_engine::GxSeqSettings* kickp) {

    std::vector<int> kicksequence = kickp->getseqline();
    int j = 0;
    for (std::vector<int>::const_iterator i = kicksequence.begin(); i != kicksequence.end(); ++i) {
        kick_seq[j]->set_active(*i);
        ++j;
    }
}
void SEQWindow::snare_changed(const gx_engine::GxSeqSettings* snarep) {

    std::vector<int> snaresequence = snarep->getseqline();
    int j = 0;
    for (std::vector<int>::const_iterator i = snaresequence.begin(); i != snaresequence.end(); ++i) {
        snare_seq[j]->set_active(*i);
        ++j;
    }
}
void SEQWindow::hat_changed(const gx_engine::GxSeqSettings* hatp) {

    std::vector<int> hatsequence = hatp->getseqline();
    int j = 0;
    for (std::vector<int>::const_iterator i = hatsequence.begin(); i != hatsequence.end(); ++i) {
        hat_seq[j]->set_active(*i);
        ++j;
    }
}

void SEQWindow::make_state(gx_engine::GxSeqSettings& seqc, std::vector<int> seq) {
    seqc.setseqline(seq);
}

void SEQWindow::on_seq_button_clicked(int p) {
    std::vector<int> sequence;
    gx_engine::GxSeqSettings seqc;
    if (p == 0) {
        for (int i = 0; i<24; ++i) {
            sequence.push_back(tom_seq[i]->get_active());
        }
        make_state(seqc, sequence);
        tomp->set(seqc);
    } else if (p == 1) {
        for (int i = 0; i<24; ++i) {
            sequence.push_back(kick_seq[i]->get_active());
        }
        make_state(seqc, sequence);
        kickp->set(seqc);
    } else if (p == 2) {
        for (int i = 0; i<24; ++i) {
            sequence.push_back(snare_seq[i]->get_active());
        }
        make_state(seqc, sequence);
        snarep->set(seqc);
    } else if (p == 3) {
        for (int i = 0; i<24; ++i) {
            sequence.push_back(hat_seq[i]->get_active());
        }
        make_state(seqc, sequence);
        hatp->set(seqc);
    }
}


SEQWindow::~SEQWindow() {
    delete gtk_window;
}

void SEQWindow::reload_and_show() {
    if (gtk_window->get_visible() && !(gtk_window->get_window()->get_state() & Gdk::WINDOW_STATE_ICONIFIED)) {
        gtk_window->hide();
    } else {
        tom_changed(&tomp->get_value());
        kick_changed(&kickp->get_value());
        snare_changed(&snarep->get_value());
        hat_changed(&hatp->get_value());
        gtk_window->present();
    }
}

} // end namespace 
