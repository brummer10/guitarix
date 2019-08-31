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

#define DRUMS 6

#define FOR_DRUMS(func) std::for_each(drums.begin(), drums.end(), [&](Drums d) { func });

/****************************************************************
 ** PluginPresetConnectWindow
 */

PluginPresetConnectWindow *PluginPresetConnectWindow::create_from_builder(
    BaseObjectType* cobject, Glib::RefPtr<gx_gui::GxBuilder> bld, gx_engine::GxMachineBase& _machine) {
    return new PluginPresetConnectWindow(cobject, bld, _machine);
}

PluginPresetConnectWindow::~PluginPresetConnectWindow() {
}

PluginPresetConnectWindow *PluginPresetConnectWindow::create(
                          gx_engine::GxMachineBase& machine) {
    Glib::RefPtr<gx_gui::GxBuilder> bld = gx_gui::GxBuilder::create_from_file(
      machine.get_options().get_builder_filepath("pluginpreset_connectwindow.glade"));
    PluginPresetConnectWindow *w;
    bld->get_toplevel_derived("PluginPresetConnectWindow", w,
      sigc::bind(sigc::ptr_fun(PluginPresetConnectWindow::create_from_builder), bld, sigc::ref(machine)));
    return w;
}

bool PluginPresetConnectWindow::on_key_press_event(GdkEventKey *event) {
    if (event->keyval == GDK_KEY_Escape && (event->state & Gtk::AccelGroup::get_default_mod_mask()) == 0) {
        hide();
        return true;
    }
    return Gtk::Window::on_key_press_event(event);
}

void PluginPresetConnectWindow::on_connect() {
    Gtk::TreeIter it = treeview->get_selection()->get_selected();
    if (it && !machine.midi_get_config_mode()) {
        Glib::ustring id = "seq." + it->get_value(upresetliststore->col.name);
        if (machine.parameter_hasId(id))
          new gx_main_midi::MidiConnect(0, machine.get_parameter(id), machine);
    }
}

PluginPresetConnectWindow::PluginPresetConnectWindow(
    BaseObjectType* cobject, Glib::RefPtr<gx_gui::GxBuilder> bld, gx_engine::GxMachineBase& _machine)
    : Gtk::Window(cobject),
      upresetliststore(UPresetListStore::create()),
      machine(_machine) {
    set_title("Connect Midi");
    Gtk::Button *b;
    bld->find_widget("closebutton", b);
    b->signal_clicked().connect(
      sigc::mem_fun(*this, &PluginPresetConnectWindow::hide));
    bld->find_widget("connectbutton", connectbutton);
    connectbutton->signal_clicked().connect(
      sigc::mem_fun0(*this, &PluginPresetConnectWindow::on_connect));
    bld->find_widget("treeview", treeview);
    gx_preset::UnitPresetList presetnames;
    machine.plugin_preset_list_load(machine.pluginlist_lookup_plugin("seq")->get_pdef(), presetnames);
    for (gx_preset::UnitPresetList::const_iterator i = presetnames.begin(); i != presetnames.end(); ++i) {
        if (i->name.empty()) {
            break;
        }
        upresetliststore->append()->set_value(upresetliststore->col.name, i->name);
    }
    treeview->set_model(upresetliststore);
    connectbutton->set_sensitive(false);
    Glib::RefPtr<Gtk::TreeSelection> sel = treeview->get_selection();
    sel->signal_changed().connect(
      sigc::mem_fun(*this, &PluginPresetConnectWindow::on_selection_changed));
}

void PluginPresetConnectWindow::on_selection_changed() {
    connectbutton->set_sensitive(treeview->get_selection()->get_selected());
}

void PluginPresetConnectWindow::run() {
    Gtk::Main::run(*this);
}

/****************************************************************
 ** Sequencer Parameter Window
 */

SEQWindow *SEQWindow::create(const std::string& unit_id, gx_engine::GxMachineBase& machine) {
    Glib::RefPtr<gx_gui::GxBuilder> bld = gx_gui::GxBuilder::create_from_file(
      machine.get_options().get_builder_filepath("Sequencer.glade"), &machine);
    gx_engine::SeqParameter *tomp = dynamic_cast<gx_engine::SeqParameter*>(&machine.get_parameter("seq.sequencer.tom"));
    gx_engine::SeqParameter *tomp1 = dynamic_cast<gx_engine::SeqParameter*>(&machine.get_parameter("seq.sequencer.tom1"));
    gx_engine::SeqParameter *tomp2 = dynamic_cast<gx_engine::SeqParameter*>(&machine.get_parameter("seq.sequencer.tom2"));
    gx_engine::SeqParameter *kickp = dynamic_cast<gx_engine::SeqParameter*>(&machine.get_parameter("seq.sequencer.kick"));
    gx_engine::SeqParameter *snarep = dynamic_cast<gx_engine::SeqParameter*>(&machine.get_parameter("seq.sequencer.snare"));
    gx_engine::SeqParameter *hatp = dynamic_cast<gx_engine::SeqParameter*>(&machine.get_parameter("seq.sequencer.hat"));
    assert(tomp);
    assert(tomp1);
    assert(tomp2);
    assert(kickp);
    assert(snarep);
    assert(hatp);
    return new SEQWindow(bld, tomp, tomp1, tomp2, kickp, snarep, hatp, machine);
}

/*
 ** Constructor
 */

SEQWindow::SEQWindow(const Glib::RefPtr<gx_gui::GxBuilder>& bld,gx_engine::SeqParameter *tomp_,
         gx_engine::SeqParameter *tomp1_,gx_engine::SeqParameter *tomp2_,
         gx_engine::SeqParameter *kickp_, gx_engine::SeqParameter *snarep_,
         gx_engine::SeqParameter *hatp_, gx_engine::GxMachineBase& machine_)
    : machine(machine_),
      builder(bld),
      tom(tomp_),
      tom1(tomp1_),
      tom2(tomp2_),
      kick(kickp_),
      snare(snarep_),
      hat(hatp_),
      is_active(false),
      gtk_window(0) {
    bld->get_toplevel("SequencerWindow", gtk_window);

    init_connect();

    // reset display
}

void SEQWindow::init_connect() {

    builder->find_widget("viewport1", vp);
    builder->find_widget("hbox1", tom.box);
    builder->find_widget("hbox1a", tom1.box);
    builder->find_widget("hbox1b", tom2.box);
    builder->find_widget("hbox2", kick.box);
    builder->find_widget("hbox3", snare.box);
    builder->find_widget("hbox4", hat.box);
    builder->find_widget("gxplayhead1", seq_pos);
    builder->find_widget("gxsmallknob6", seq_count);
    builder->find_widget("gxselector1", seq_tact);
    builder->find_widget("hbox12", preset_button);
    builder->find_widget("gxswitch6", add_button);
    builder->find_widget("gxswitch3", next_preset);
    builder->find_widget("gxswitch7", previus_preset);
    builder->find_widget("gxswitch4", set_step);
    builder->find_widget("gxswitch5", set_fstep);
    builder->find_widget("gxswitch8", set_sync);
    builder->find_widget("gxswitch9", reset_step);
    builder->find_widget("label9:rack_label_inverse", preset_label);
    builder->find_widget("gxvaluedisplay1", step_value);
    builder->find_widget("label8:rack_label_inverse", step_label);
    
    Pango::FontDescription font = preset_label->get_style_context()->get_font();
    font.set_size(10*Pango::SCALE);
    font.set_weight(Pango::WEIGHT_BOLD);
    preset_label->override_font(font);

    make_preset_button(preset_button);

    drums.push_back(tom);
    drums.push_back(tom1);
    drums.push_back(tom2);
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

    int ti_o = 60;
    if (!machine.get_jack()) ti_o = 250;
    Glib::signal_timeout().connect(
      sigc::bind<Gxw::Regler*>(sigc::bind<const std::string>(
      sigc::mem_fun(*this, &SEQWindow::get_sequencer_pos),id), seq_pos), ti_o);

    seq_count->signal_value_changed().connect(
      sigc::bind(sigc::mem_fun(*this, &SEQWindow::on_sec_length_changed), true));

    seq_tact->signal_value_changed().connect(
      sigc::mem_fun(*this, &SEQWindow::on_sec_tact_changed));

    next_preset->signal_toggled().connect(
      sigc::mem_fun(*this, &SEQWindow::on_next_preset));

    previus_preset->signal_toggled().connect(
      sigc::mem_fun(*this, &SEQWindow::on_previus_preset));

    set_step->signal_toggled().connect(
      sigc::mem_fun(*this, &SEQWindow::on_set_step));

    set_fstep->signal_toggled().connect(
      sigc::mem_fun(*this, &SEQWindow::on_set_fstep));

    set_sync->signal_toggled().connect(
      sigc::mem_fun(*this, &SEQWindow::on_sync_stepper));

    reset_step->signal_toggled().connect(
      sigc::mem_fun(*this, &SEQWindow::on_reset_stepper));

    add_button->signal_clicked().connect(
      sigc::mem_fun(*this, &SEQWindow::on_preset_add_clicked));
    add_button->set_tooltip_text(_("add effect unit preset to the sequence"));

    gtk_window->signal_key_press_event().connect(
      sigc::mem_fun(this, &SEQWindow::on_key_press_event));

    if (!machine.get_jack()) {
        step_value->hide();
        step_label->hide();
    }
}

void SEQWindow::init_sequences(gx_engine::SeqParameter *p, Gtk::Box* _box) {
    Glib::ListHandle<Gtk::Widget*> List = _box->get_children();
    for (Glib::ListHandle<Gtk::Widget*>::iterator itt = List.begin();itt != List.end(); ++itt) {
        dynamic_cast<Gtk::ToggleButton*>((*itt))->signal_clicked().connect(
          sigc::bind(sigc::bind(sigc::mem_fun(this, &SEQWindow::on_seq_button_clicked),p),_box));
    }
}

void SEQWindow::on_set_step() {
    if (!set_step->get_active()) return;
        float tactv = machine.get_parameter_value<float>("seq.tact");
        float value = std::max(0,int(machine.get_parameter_value<float>("seq.step")-tactv));
        reset_control("seq.step",value);
        set_step->set_active(false);
}

void SEQWindow::on_set_fstep() {
    if (!set_fstep->get_active()) return;
        float tactv = machine.get_parameter_value<float>("seq.tact");
        float valuea = machine.get_parameter_value<float>("seq.asequences");
        float value = std::min(int(valuea),int(machine.get_parameter_value<float>("seq.step")+tactv));
        reset_control("seq.step",value);
        set_fstep->set_active(false);
}

void SEQWindow::on_sync_stepper() {
    if (!set_sync->get_active()) return;
    reset_control("seq.step",machine.get_parameter_value<float>("seq.step_orig"));
    set_sync->set_active(false);
}

void SEQWindow::on_reset_stepper() {
    if (!reset_step->get_active()) return;
    reset_control("seq.step",0.0);
    reset_control("seq.step_orig",0.0);
    reset_control("seq.pos",0.0);
    reset_step->set_active(false);
}

void SEQWindow::on_next_preset() {
    if (!next_preset->get_active()) return;
    if (!is_active) {
        is_active = true;
        Glib::signal_idle().connect_once(sigc::mem_fun(this, &SEQWindow::on_next_preset_set));
    }
}

void SEQWindow::on_next_preset_set() {
    gx_preset::UnitPresetList presetnames;
    machine.plugin_preset_list_load(machine.pluginlist_lookup_plugin("seq")->get_pdef(), presetnames);
    for (gx_preset::UnitPresetList::iterator i = presetnames.begin(); i != presetnames.end(); ++i) {
        if (!i->name.empty()) {
            if (i->is_set) {
               ++i;
               if (i->name.empty()) i = presetnames.begin();
               machine.plugin_preset_list_sync_set(machine.pluginlist_lookup_plugin("seq")->get_pdef(), false, i->name);
                break; 
            } else {
                machine.plugin_preset_list_sync_set(machine.pluginlist_lookup_plugin("seq")->get_pdef(), false, presetnames.begin()->name);
            }
        }
    }
    is_active = false;
    reset_control("seq.npreset",0);
}

void SEQWindow::on_previus_preset() {
    if (!previus_preset->get_active()) return;
    if (!is_active) {
        is_active = true;
        Glib::signal_idle().connect_once(sigc::mem_fun(this, &SEQWindow::on_previus_preset_set));
    }
}

void SEQWindow::on_previus_preset_set() {
    gx_preset::UnitPresetList presetnames;
    machine.plugin_preset_list_load(machine.pluginlist_lookup_plugin("seq")->get_pdef(), presetnames);
    gx_preset::UnitPresetList::iterator i = presetnames.begin();
    for ( i = presetnames.begin(); i != presetnames.end(); ++i) {
        if (!i->name.empty()) {
            if (i->is_set) break; 
        }
    }
    if (i == presetnames.begin()) {
        i = presetnames.end();
        --i;
    } else if (i == presetnames.end()) {
        i -=2;
    } 
    --i;
    machine.plugin_preset_list_sync_set(machine.pluginlist_lookup_plugin("seq")->get_pdef(), false, i->name);
    is_active = false;
    reset_control("seq.ppreset",0);
}

void SEQWindow::on_preset_popup_clicked() {
    Gtk::Menu *presetMenu = static_cast<Gtk::Menu*>(new PluginPresetPopup(machine.pluginlist_lookup_plugin("seq")->get_pdef(), machine));
    Gtk::MenuItem* subitem = Gtk::manage(new Gtk::MenuItem("connect midi...", true));
    presetMenu->append(*subitem);
    subitem->signal_activate().connect(sigc::mem_fun(
              *this, &SEQWindow::connect_midi));
    presetMenu->show_all();
}

void SEQWindow::connect_midi() {
    PluginPresetConnectWindow *w = PluginPresetConnectWindow::create(machine);
    w->run();
    delete w;
}

void SEQWindow::make_preset_button(Gtk::Box * box) {
    Gtk::Button *p = new Gtk::Button();
    Gtk::Image *l = new Gtk::Image("rack_preset", Gtk::ICON_SIZE_BUTTON);
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
    if (!is_active) {
        is_active = true;
        Glib::signal_timeout().connect_once(sigc::bind(sigc::mem_fun(this, &SEQWindow::append_plugin_preset_set),name),5);
    }
}

void SEQWindow::append_plugin_preset_set(Glib::ustring name) {
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
    float tomg1 = machine.get_parameter_value<float>("seq.tom.dsp.Gain1");
    float tomg2 = machine.get_parameter_value<float>("seq.tom.dsp.Gain2");
    float kickg = machine.get_parameter_value<float>("seq.kick.dsp.Gain");
    float snareg = machine.get_parameter_value<float>("seq.snare.dsp.Gain");
    float hatg = machine.get_parameter_value<float>("seq.hat_closed.dsp.Gain");
    // set preset values
    machine.plugin_preset_list_set(machine.pluginlist_lookup_plugin("seq")->get_pdef(), false, name);

    // append preset sequence to current and get new step size 
    int s = 24;
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
    reset_control("seq.tom.dsp.Gain1",tomg1);
    reset_control("seq.tom.dsp.Gain2",tomg2);
    reset_control("seq.kick.dsp.Gain",kickg);
    reset_control("seq.snare.dsp.Gain",snareg);
    reset_control("seq.hat_closed.dsp.Gain",hatg);

    is_active = false;
 } 

static bool delete_plugin_preset_popup(Gtk::Menu *presetMenu) {
    delete presetMenu;
    return false;
}

void SEQWindow::on_selection_done(Gtk::Menu *presetMenu) {
    Glib::signal_idle().connect(sigc::bind(
      sigc::ptr_fun(delete_plugin_preset_popup), presetMenu));
}

void SEQWindow::on_preset_add_clicked() {
    if (!add_button->get_active()) return;
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
    presetMenu->signal_selection_done().connect(sigc::bind(sigc::mem_fun(
      *this, &SEQWindow::on_selection_done),presetMenu));
    presetMenu->show_all();
    presetMenu->popup(1, gtk_get_current_event_time());
    add_button->set_active(false);
}

void SEQWindow::on_sec_length_changed(bool update) {
    static int r_save = 24;
    int r = int(seq_count->cp_get_value());
    if ( r_save > r) {
        FOR_DRUMS(
            remove_seq_block(d.box, r);
        );
        r_save = r;
    } else if( r_save < r) {
        FOR_DRUMS(
            append_seq_block(d.box,d.p, r,r_save);
        );
        r_save = r;
    }
    if (update) {
        FOR_DRUMS(
            on_seq_button_clicked(d.box,d.p);
        );
    }
}

void SEQWindow::on_sec_tact_changed() {
    FOR_DRUMS(
        seq_changed(&d.p->get_value(), d.box);
    );
}

void SEQWindow::append_seq_block(Gtk::Box * box, gx_engine::SeqParameter *p, int r, int r_save) {
    Gtk::ToggleButton * ab;
    for(int j = r_save; j<r; ++j) {
        ab = new Gtk::ToggleButton();
        box->pack_start(*Gtk::manage(ab),Gtk::PACK_EXPAND_WIDGET);
        ab->signal_clicked().connect(
          sigc::bind(sigc::bind(sigc::mem_fun(this, &SEQWindow::on_seq_button_clicked),p),box));
          ab->show();
    }
}

void SEQWindow::remove_seq_block(Gtk::Box * box, int r) {
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
    Glib::RefPtr<Gtk::Adjustment> a = vp->get_hadjustment();
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
    float value = 0;
    if (machine.parameter_hasId(id)) {
        if (machine.get_parameter_value<bool>(id.substr(0,id.find_last_of(".")+1)+"on_off")) {
            value = machine.get_parameter_value<float>(id);
            if (!machine.get_jack()) {
                if (value<99.0) return true;
            }
            machine.signal_parameter_value<float>(id)(value);
            if (machine.get_jack()) machine.signal_parameter_value<float>("seq.step")(machine.get_parameter_value<float>("seq.step"));
            if (machine.get_parameter_value<float>("seq.follow"))
                scroll_playhead(value);
        }
        return true;
    } else {
        return false;
    }
}

bool SEQWindow::on_key_press_event(GdkEventKey *event) {
    return true;
}

void SEQWindow::on_seq_button_clicked(Gtk::Box *box, gx_engine::SeqParameter *p) {
    Glib::signal_timeout().connect_once(sigc::bind(sigc::bind(sigc::mem_fun(this, &SEQWindow::on_seq_button_clicked_set),p),box),2);
}

void SEQWindow::on_seq_button_clicked_set(Gtk::Box *box, gx_engine::SeqParameter *p) {
    std::vector<int> sequence;
    gx_engine::GxSeqSettings seqc;
    Glib::ListHandle<Gtk::Widget*> seqList = box->get_children();
    for (Glib::ListHandle<Gtk::Widget*>::iterator itt = seqList.begin();itt != seqList.end(); ++itt) {
        sequence.push_back(dynamic_cast<Gtk::ToggleButton*>((*itt))->get_active());
    }
    seqc.setseqline(sequence);
    p->set(seqc);
}

void SEQWindow::check_preset_label() {
    Glib::ustring pset = " ";
    gx_preset::UnitPresetList presetnames;
    machine.plugin_preset_list_load(machine.pluginlist_lookup_plugin("seq")->get_pdef(), presetnames);
    gx_preset::UnitPresetList::iterator i = presetnames.begin();
    for ( i = presetnames.begin(); i != presetnames.end(); ++i) {
        if (!i->name.empty()) {
            if (i->is_set) {
                pset = i->name;
                break;
            }
        }
    }
    preset_label->set_label(pset);
}

void SEQWindow::seq_changed(const gx_engine::GxSeqSettings* seqc, Gtk::Box *box) {

    Glib::ListHandle<Gtk::Widget*> seqList = box->get_children();
    Glib::ListHandle<Gtk::Widget*>::iterator itt = seqList.begin();
    std::vector<int> sequence = seqc->getseqline();
    int ic = int(machine.get_parameter_value<float>("seq.tact"))-1;
    int i0 = ic;
    for (std::vector<int>::const_iterator i = sequence.begin(); i != sequence.end(); ++i) {
        if (itt == seqList.end()) break;
        dynamic_cast<Gtk::ToggleButton*>((*itt))->set_active(*i);
        if (i0 == ic) {
            dynamic_cast<Gtk::ToggleButton*>((*itt))->set_name("seq_button");
            i0 = 0;
        } else {
            dynamic_cast<Gtk::ToggleButton*>((*itt))->set_name("button");
            ++i0;
        }
        ++itt;
    }
    Glib::signal_idle().connect_once(sigc::mem_fun(this, &SEQWindow::check_preset_label));
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
