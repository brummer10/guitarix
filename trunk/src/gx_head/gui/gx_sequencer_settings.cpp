/*
 * Copyright (C) 2017 Hermann Meyer, Andreas Degert
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

#define DRUMS 4

#define FOR_DRUMS(func) std::for_each(drums.begin(), drums.end(), [&](Drums d) { func });

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
    assert(kickp);
    assert(snarep);
    assert(hatp);
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
      tom(tomp_),
      kick(kickp_),
      snare(snarep_),
      hat(hatp_),
      gtk_window(0) {
    bld->get_toplevel("SequencerWindow", gtk_window);

    init_connect();

    // reset display
}

void SEQWindow::init_connect() {

    builder->find_widget("viewport1", vp);
    builder->find_widget("hbox1", tom.box);
    builder->find_widget("hbox2", kick.box);
    builder->find_widget("hbox3", snare.box);
    builder->find_widget("hbox4", hat.box);
    builder->find_widget("gxplayhead1", seq_pos);
    builder->find_widget("gxsmallknob6", seq_count);
    builder->find_widget("hbox12", preset_button);
    builder->find_widget("button1", add_button);

    make_preset_button(preset_button);

    drums.push_back(tom);
    drums.push_back(kick);
    drums.push_back(snare);
    drums.push_back(hat);

    on_sec_length_changed(false);

    FOR_DRUMS(
        d.p->signal_changed().connect(sigc::bind(
          sigc::mem_fun(this, &SEQWindow::seq_changed), d.box));
        init_sequences(d.p, d.box);
    );


    seq_pos->cp_set_value(0.0);
    std::string id;
    seq_pos->get_property("var_id",id);

    Glib::signal_timeout().connect(
      sigc::bind<Gxw::Regler*>(sigc::bind<const std::string>(
      sigc::mem_fun(*this, &SEQWindow::get_sequencer_pos),id), seq_pos), 60);

    seq_count->signal_value_changed().connect(
      sigc::bind(sigc::mem_fun(*this, &SEQWindow::on_sec_length_changed), true));

    add_button->signal_clicked().connect(
      sigc::mem_fun(*this, &SEQWindow::on_preset_add_clicked));
    add_button->set_tooltip_text(_("add effect unit preset to the sequence"));

    gtk_window->signal_key_press_event().connect(
      sigc::mem_fun(this, &SEQWindow::on_key_press_event));
}

void SEQWindow::init_sequences(gx_engine::SeqParameter *p, Gtk::HBox* _box) {
    Glib::ListHandle<Gtk::Widget*> List = _box->get_children();
    for (Glib::ListHandle<Gtk::Widget*>::iterator itt = List.begin();itt != List.end(); ++itt) {
        dynamic_cast<Gtk::ToggleButton*>((*itt))->signal_clicked().connect(
          sigc::bind(sigc::bind(sigc::mem_fun(this, &SEQWindow::on_seq_button_clicked),p),_box));
    }
}

void SEQWindow::on_preset_popup_clicked() {
    new PluginPresetPopup(machine.pluginlist_lookup_plugin("seq")->get_pdef(), machine);
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

void SEQWindow::reset_control(Glib::ustring id, float value) {
    machine.set_parameter_value(id,value);
    machine.signal_parameter_value<float>(id)(value);
}

int SEQWindow::append_sequence(const gx_engine::GxSeqSettings* seqc, gx_engine::SeqParameter *p, std::vector<int> *sequence) {
    int s = 0;
    std::vector<int> sequence_append = seqc->getseqline();
    for(std::vector<int>::const_iterator i = sequence_append.begin(); i != sequence_append.end(); ++i) {
        sequence->push_back(*i);
       ++s;
    }
    return s;
}

void SEQWindow::append_plugin_preset(Glib::ustring name) {
    // get current sequences
    std::vector<int> sequence[DRUMS];
    int i = 0;
    FOR_DRUMS(
        sequence[i] = static_cast<const gx_engine::GxSeqSettings*>(&d.p->get_value())->getseqline();
        ++i;
    );
    
    // get current control values
    float value = machine.get_parameter_value<float>("seq.asequences");
    float bpmv = machine.get_parameter_value<float>("seq.bpm");
    float tactv = machine.get_parameter_value<float>("seq.tact");
    float gainv = machine.get_parameter_value<float>("seq.gain");
    float tomg = machine.get_parameter_value<float>("seq.tom.dsp.Gain");
    float kickg = machine.get_parameter_value<float>("seq.kick.dsp.Gain");
    float snareg = machine.get_parameter_value<float>("seq.snare.dsp.Gain");
    float hatg = machine.get_parameter_value<float>("seq.hat_closed.dsp.Gain");

    // set preset values
    machine.plugin_preset_list_set(machine.pluginlist_lookup_plugin("seq")->get_pdef(), false, name);

    // append preset sequence to current and get new step size 
    int s = 0;
    i = 0;
    FOR_DRUMS(
        s = append_sequence(&d.p->get_value(), d.p, &sequence[i]);
        ++i;
    );

    // set new step size
    value += float(s);
    reset_control("seq.asequences",value);

    // set new sequences as parameter
    gx_engine::GxSeqSettings seqc;
    i = 0;
    FOR_DRUMS(
        seqc.setseqline(sequence[i]);
        d.p->set(seqc);
        ++i;
    );

    // reset controls to previus values
    reset_control("seq.bpm",bpmv);
    reset_control("seq.tact",tactv);
    reset_control("seq.gain",gainv);
    reset_control("seq.tom.dsp.Gain",tomg);
    reset_control("seq.kick.dsp.Gain",kickg);
    reset_control("seq.snare.dsp.Gain",snareg);
    reset_control("seq.hat_closed.dsp.Gain",hatg);
} 

void SEQWindow::on_preset_add_clicked() {
    Gtk::MenuItem* item;
    Gtk::Menu *presetMenu = Gtk::manage(new Gtk::Menu());
    gx_preset::UnitPresetList presetnames;
    machine.plugin_preset_list_load(machine.pluginlist_lookup_plugin("seq")->get_pdef(), presetnames);
    for (gx_preset::UnitPresetList::iterator i = presetnames.begin(); i != presetnames.end(); ++i) {
        if (!i->name.empty()) {
            item = Gtk::manage(new Gtk::MenuItem(i->name, true));
            presetMenu->append(*item);
             item->signal_activate().connect(sigc::bind(sigc::mem_fun(
              *this, &SEQWindow::append_plugin_preset),i->name));
        }
    }
    presetMenu->show_all();
    presetMenu->popup(1, gtk_get_current_event_time());
}

void SEQWindow::on_sec_length_changed(bool update) {
    static int r_save = 24;
    int r = int(seq_count->cp_get_value());
    if ( r_save > r) {
        std::for_each(drums.begin(), drums.end(), [&](Drums d) {
            remove_seq_block(d.box, r);
        });
        r_save = r;
    } else if( r_save < r) {
        std::for_each(drums.begin(), drums.end(), [&](Drums d) {
            append_seq_block(d.box,d.p, r,r_save);
        });
        r_save = r;
    }
    if (update) {
        std::for_each(drums.begin(), drums.end(), [&](Drums d) {
            on_seq_button_clicked(d.box,d.p);
        });
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

void SEQWindow::scroll_playhead(float value) {
    Gtk::Adjustment *a = vp->get_hadjustment();
    static float old_state = 0.0;
    float u = a->get_upper();
    float l = a->get_lower();
    float s = a->get_page_size();
    float set = (u-s) * ((value)/2300.0);
    if (u>s) {
        if (set>l && set<u) {
            if(std::abs(set-old_state) > 10) {
                a->set_value(set);
                old_state = set;
            }
        }
    }
    
}

bool SEQWindow::get_sequencer_pos(Gxw::Regler * regler, const std::string id) {
    if (machine.parameter_hasId(id)) {
        if (machine.get_parameter_value<bool>(id.substr(0,id.find_last_of(".")+1)+"on_off")) {
            float value = machine.get_parameter_value<float>(id);
            machine.signal_parameter_value<float>(id)(value);
           // scroll_playhead(value);
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
        FOR_DRUMS(
            seq_changed(&d.p->get_value(), d.box);
        );
        gtk_window->present();
    }
}

SEQWindow::~SEQWindow() {
    delete gtk_window;
}

} // end namespace 
