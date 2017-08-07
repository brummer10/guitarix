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
    builder->find_widget("gxplayhead1", seq_pos);
    builder->find_widget("gxsmallknob6", seq_count);
    builder->find_widget("hbox12", preset_button);

    on_sec_length_changed(false);

    make_preset_button(preset_button);

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

    seq_pos->cp_set_value(0.0);
    std::string id;
    seq_pos->get_property("var_id",id);
    Glib::signal_timeout().connect(sigc::bind<Gxw::Regler*>(sigc::bind<const std::string>(
      sigc::mem_fun(*this, &SEQWindow::get_sequencer_pos),id), seq_pos), 60);

    seq_count->signal_value_changed().connect(sigc::bind(sigc::mem_fun(*this,
                                               &SEQWindow::on_sec_length_changed), true));

    gtk_window->signal_key_press_event().connect(
      sigc::mem_fun(this, &SEQWindow::on_key_press_event));
}

void SEQWindow::make_preset_button(Gtk::HBox * box) {
    Gtk::Button *p = new Gtk::Button();
    Gtk::Image *l = new Gtk::Image(Gdk::Pixbuf::create_from_file(machine.get_options().get_style_filepath("rack_preset.png")));
    p->add(*Gtk::manage(l));
    p->set_can_default(false);
    p->set_can_focus(false);
	p->set_tooltip_text(_("manage effect unit presets"));
	p->set_name("effect_on_off");
	box->pack_start(*Gtk::manage(p),Gtk::PACK_SHRINK);
    p->signal_clicked().connect(
	sigc::mem_fun(*this, &SEQWindow::on_preset_popup_clicked));
	p->show_all();
}

void SEQWindow::on_preset_popup_clicked() {
    new PluginPresetPopup(machine.pluginlist_lookup_plugin("seq")->get_pdef(), machine);
}

void SEQWindow::on_sec_length_changed(bool update) {
    static int r_save = 24;
    int r = int(seq_count->cp_get_value());
    if ( r_save > r) {
        remove_seq_block(tom_box, r);
        remove_seq_block(kick_box, r);
        remove_seq_block(snare_box, r);
        remove_seq_block(hat_box, r);
        r_save = r;
    } else if( r_save < r) {
        append_seq_block(tom_box,tomp, r,r_save);
        append_seq_block(kick_box,kickp, r,r_save);
        append_seq_block(snare_box,snarep, r,r_save);
        append_seq_block(hat_box,hatp, r,r_save);
        r_save = r;
    }
    if (update) {
        on_seq_button_clicked(tom_box,tomp);
        on_seq_button_clicked(kick_box,kickp);
        on_seq_button_clicked(snare_box,snarep);
        on_seq_button_clicked(hat_box,hatp);
    }
}


void SEQWindow::append_seq_block(Gtk::HBox * box, gx_engine::SeqParameter *p, int r, int r_save) {
    Gtk::ToggleButton * ab;
    for(int j = r_save; j<r; ++j) {
        ab = new Gtk::ToggleButton();
        box->pack_start(*Gtk::manage(ab),Gtk::PACK_EXPAND_WIDGET);
        ab->signal_clicked().connect(
          sigc::bind(sigc::bind(sigc::mem_fun(this, &SEQWindow::on_seq_button_clicked),p),box));
          ab->show();
    }
}

void SEQWindow::remove_seq_block(Gtk::HBox * box, int r) {
    Glib::ListHandle<Gtk::Widget*> boxList = box->get_children();
    int i = 0;
    for (Glib::ListHandle<Gtk::Widget*>::iterator itt = boxList.begin();itt != boxList.end(); ++itt) {
        if (i>=r) {
            box->remove(*(*itt));
            delete((*itt));
        }
        ++i;
    }
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
        if (itt == seqList.end()) break;
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
