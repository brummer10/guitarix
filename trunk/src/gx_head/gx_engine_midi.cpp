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
 *
 *
 *    This is the Guitarix MIDI Engine NOT using a ring buffer
 *
 *
 * --------------------------------------------------------------------------
 */

#include "guitarix.h"    //  NOLINT

namespace gx_engine {

void MidiVariables::register_parameter() {
    gx_gui::ParameterGroups& groups = gx_gui::get_group_table();
    groups.insert("midi_out", N_("Midi Out"));
    groups.insert("midi_out.channel_1", N_("Midi Out 1"));
    groups.insert("midi_out.channel_2", N_("Midi Out 2"));
    groups.insert("midi_out.channel_3", N_("Midi Out 3"));
    groups.insert("beat_detector", N_("Beat Detector"));

    static const char *on_off = N_("on/off");
    gx_gui::registerParam("midi_out.on_off",       on_off, &fmi, 0);
    gx_gui::registerNonMidiParam("midi_out.midistat",        &midistat, false);
    gx_gui::registerNonMidiParam("midi_out.midistat1",       &midistat1, false);
    gx_gui::registerNonMidiParam("midi_out.midistat2",       &midistat2, false);
    gx_gui::registerNonMidiParam("midi_out.midistat3",       &midistat3, false);

    gx_gui::registerParam("midi_out.channel_1.velocity", "velocity", &fslider26,
                           64.f, 0.f, 127.f, 1.f);
    gx_gui::registerParam("midi_out.channel_1.volume", "volume", &fslider46,
                           64.f, 0.f, 127.f, 1.f);
    gx_gui::registerParam("midi_out.channel_1.autogain", "autogain", &fautogain);
    gx_gui::registerParam("midi_out.channel_1.channel", "channel 1", &fslider30,
                           0.f, 0.f, 16.f, 1.f);
    gx_gui::registerParam("midi_out.channel_1.program", "program", &fslider31,
                           0.f, 0.f, 248.f, 1.f);
    gx_gui::registerParam("midi_out.channel_1.oktave", "oktave", &fslider29,
                           0.f, -2.f, 2.f, 1.f);
    gx_gui::registerParam("midi_out.channel_1.sensity", "sensity", &fslider27,
                           20.f, 1.f, 500.f, 1.f);
    gx_gui::registerParam("midi_out.channel_1.auto_pitch", "auto pitch", &fpitch);

    gx_gui::registerParam("midi_out.channel_2.on_off", "on/off", &fcheckbox10, 0);
    gx_gui::registerParam("midi_out.channel_2.velocity", "velocity", &fslider32,
                           64.f, 0.f, 127.f, 1.f);
    gx_gui::registerParam("midi_out.channel_2.volume", "volume", &fslider47,
                           64.f, 0.f, 127.f, 1.f);
    gx_gui::registerParam("midi_out.channel_2.autogain", "autogain", &fautogain1);
    gx_gui::registerParam("midi_out.channel_2.channel", "channel 2", &fslider35,
                           0.f, 0.f, 16.f, 1.f);
    gx_gui::registerParam("midi_out.channel_2.program", "program", &fslider36,
                           0.f, 0.f, 248.f, 1.f);
    gx_gui::registerParam("midi_out.channel_2.oktave", "oktave", &fslider34,
                           0.f, -2.f, 2.f, 1.f);
    gx_gui::registerParam("midi_out.channel_2.sensity", "sensity", &fslider33,
                           20.f, 1.f, 500.f, 1.f);
    gx_gui::registerParam("midi_out.channel_2.auto_pitch", "auto pitch", &fpitch1);

    gx_gui::registerParam("midi_out.channel_3.on_off", "on/off", &fcheckbox11, 0);
    gx_gui::registerParam("midi_out.channel_3.velocity", "velocity", &fslider40,
                           64.f, 0.f, 127.f, 1.f);
    gx_gui::registerParam("midi_out.channel_3.volume", "volume", &fslider48,
                           64.f, 0.f, 127.f, 1.f);
    gx_gui::registerParam("midi_out.channel_3.autogain", "autogain", &fautogain2);
    gx_gui::registerParam("midi_out.channel_3.channel", "channel 3", &fslider44,
                           0.f, 0.f, 16.f, 1.f);
    gx_gui::registerParam("midi_out.channel_3.program", "program", &fslider43,
                           0.f, 0.f, 248.f, 1.f);
    gx_gui::registerParam("midi_out.channel_3.oktave", "oktave", &fslider42,
                           0.f, -2.f, 2.f, 1.f);
    gx_gui::registerParam("midi_out.channel_3.sensity", "sensity", &fslider41,
                           20.f, 1.f, 500.f, 1.f);
    gx_gui::registerParam("midi_out.channel_3.auto_pitch", "auto pitch", &fpitch2);

    gx_gui::registerParam("beat_detector.stepper", "stepper", &fslider39,
                           1.f, 1.f, 32.f, 1.f);
    gx_gui::registerParam("beat_detector.note_off", "note off", &fslider37,
                           2.f, 1.f, 127.f, 1.f);
    gx_gui::registerParam("beat_detector.atack_gain", "atack gain", &fslider45,
                           5.f, 1.f, 127.f, 1.f);
    gx_gui::registerParam("beat_detector.beat_gain", "beat gain", &fslider38,
                           1.f, 0.0f, 127.f, 1.f);
    gx_gui::registerParam("beat_detector.midi_gain", "midi gain", &midi_gain,
                           0.f, -40.f, 60.f, 1.f);
}

MidiVariables midi;


void MidiVariables::init(int samplingFreq) {
    fConstlog = log(1.055) * 0.5;
    fConstlog2 = 6/log(2) * -1;
    midi_gain = 1.0;
    fConstun0  = (0.001 * 300 * samplingFreq) * 36;
    BeatFilterk =1.0/(gx_jack::gxjack.jack_sr * (1.0f/(2.0f * M_PI * 1250.0f)));
    BeatFilter1 =0.0;
    BeatFilter2 =0.0;
}

// ----- jack process callback for the midi input
void compute_midi_in(void* midi_input_port_buf) {
    jack_midi_event_t in_event;
    jack_nframes_t event_count = jack_midi_get_event_count(midi_input_port_buf);
    unsigned int i;
    for (i = 0; i < event_count; i++) {
        jack_midi_event_get(&in_event, midi_input_port_buf, i);
        if ((in_event.buffer[0] & 0xf0) == 0xc0) {  // program change on any midi channel
            g_atomic_int_set(&gx_gui::guivar.program_change, in_event.buffer[1]);
            sem_post(&gx_gui::guivar.program_change_sem);
        } else if ((in_event.buffer[0] & 0xf0) == 0xb0) {   // controller
            gx_gui::controller_map.set(in_event.buffer[1], in_event.buffer[2]);
        }
    }
}

void compute_midi(int len) {

    // retrieve engine state
    const GxEngineState estate = audio.checky;

    // ------------ determine processing type
    uint16_t process_type = ZEROIZE_BUFFERS;

    if (gx_jack::gxjack.NO_CONNECTION == 0) { // ports connected
        switch (estate) {
        case kEngineOn:
            process_type = PROCESS_BUFFERS;
            break;

        case kEngineBypass:
            process_type = JUSTCOPY_BUFFERS;
            break;

        default: // engine off or whatever: zeroize
            break;
        }
    }

    // ------------ main processing routine
    switch (process_type) {

    case PROCESS_BUFFERS:
        process_midi(len);
        break;
        // --------- just copy input to outputs
    case JUSTCOPY_BUFFERS:
        process_midi(len);
        break;
        // ------- zeroize buffers
    case ZEROIZE_BUFFERS:
    default:
        break;
    }
}


// ----- jack process callback for the midi output
void process_midi(int len) {

    // ----- only run it when midi out or tuner is enabled
    if (isMidiOn()) {
        static float fnote = 1000.;
        float     fConsta2 = 0.;
        float fTemps45 = midi.fslider45;
        float fTemps38 = midi.fslider38;
        float rms = 0.;
        float midi_db = 0.;
        float sum = 0.;
        float *audiodata = audio.checkfreq;

        int preNote = 0;
        int iTemps31 = static_cast<int>(midi.fslider31);
        int iTemps30 = static_cast<int>(midi.fslider30);
        int iTemps27 = static_cast<int>(midi.fslider27);
        int iTemps29 = static_cast<int>(midi.fslider29)*12;
        int iTemps26 = static_cast<int>(midi.fslider26);
        int iTemps36 = static_cast<int>(midi.fslider36);
        int iTemps35 = static_cast<int>(midi.fslider35);
        int iTemps33 = static_cast<int>(midi.fslider33);
        int iTemps34 = static_cast<int>(midi.fslider34)*12;
        int iTemps32 = static_cast<int>(midi.fslider32);
        int iTemps43 = static_cast<int>(midi.fslider43);
        int iTemps44 = static_cast<int>(midi.fslider44);
        int iTemps41 = static_cast<int>(midi.fslider41);
        int iTemps42 = static_cast<int>(midi.fslider42)*12;
        int iTemps40 = static_cast<int>(midi.fslider40);
        int step = static_cast<int>(midi.fslider39);
        int iTemps37  = static_cast<int>(48000/midi.fslider37);
        int iTemps37a  = iTemps37+5;
        int iTemps46 = static_cast<int>(midi.fslider46);
        int iTemps47 = static_cast<int>(midi.fslider47);
        int iTemps48 = static_cast<int>(midi.fslider48);
        int piwe = 0;
        int cs = 0;

        double stepper = 1./step;


        /**fConsta4 is the frequence value from the actuell frame, here we
           calculate the Note from the freq by log2(freq/440)*12
           the audio.result is the Note (as float) related to the note "A"

           preNote contains the next posible Note, related by round float to int.
           piwe contain the pitchweel value witch show the diff
           beetween the detected Note and
           the real Note by frequency.
        **/
        // fnote = 12 * log2f(2.272727e-03f * midi.fConsta4);
        if (audio.fConsta1t < 999.) fnote = audio.fConsta1t;
        preNote = static_cast<int>(round(fnote))+57;
        fConsta2 = fnote - (preNote - 57);
        piwe = (static_cast<int>(fConsta2+1)) * 8192; // pitch wheel value
        // preNote = round(fConsta1t)+57;
        // weg = 0;


        for (int i = 0; i < len; i += step) {

            float audio_db = *audiodata++;
            midi.BeatFilter1 = midi.BeatFilter1+(midi.BeatFilterk*(audio_db-midi.BeatFilter1));
            midi.BeatFilter2 = midi.BeatFilter2+(midi.BeatFilterk*(midi.BeatFilter1-
                                                 midi.BeatFilter2));
            audio_db = midi.BeatFilter2*10;
            if (audio_db > 0.00001) {
                // ----- convert the audio gain to midi gain value
                midi_db = (log(fabs(audio_db))*midi.fConstlog2);
                midi.beat0 = 254- floor(exp(midi.fConstlog*midi_db)*127)+ midi.midi_gain;
                rms = midi.beat0;
            }
            // ----- check gain value and run only when gain is higher then the selected value
            if (( midi.beat0 >= fTemps45) && (gx_jack::gxjack.jcpu_load < 65.0)) {

                // ----- rms the gain for a smother output
                if (cs == static_cast<int>(midi.fConstun0*stepper)) {
                    cs = 0;
                    sum = 0;
                } else {
                    cs += 1;
                    sum += sqrf(rms);
                }

                midi.beat0 = sqrtf(sum/cs);
                // set the value for the tuner
                // audio.fConsta1 = fnote;
                // set timeout for tuner fallback
                midi.weg = 0;

                if (rms >= (midi.Beat_is + fTemps38)) {
                    // midi.Beat_is = rms;
                    midi.Beat_is += static_cast<int>(rms*0.1);
                    midi.send+=step;
                    if (midi.fcheckbox10 ) midi.send1+=step;
                    if (midi.fcheckbox11 ) midi.send2+=step;
                    // midi.weg -= step;
                }
                // else midi.weg +=step;

                // ----- start the midi output

                // channel0
                if (midi.program != iTemps31) {
                    midi.program = iTemps31;
                    midi.midistat = true;
                    midi.midi_send = jack_midi_event_reserve(gx_jack::gxjack.midi_port_buf, i, 2);

                    if (midi.midi_send) {
                        // program value
                        midi.midi_send[1] =  static_cast<int>(iTemps31);
                        // controller+ channel
                        midi.midi_send[0] = 0xC0 | static_cast<int>(iTemps30);
                    }
                }

                if (midi.send > iTemps27) {     // 20
                    if (static_cast<int>(midi.fautogain) == 1) {
                        iTemps46 = static_cast<int>(midi.beat0);
                        if ( iTemps46 < 0) iTemps46 = 0;
                        else if ( iTemps46 > 127) iTemps46 = 127;
                        midi.fslider46 = iTemps46;
                    }
                    if (midi.volume != iTemps46) {
                        midi.volume = iTemps46;
                        midi.midistat = true;
                        midi.midi_send = jack_midi_event_reserve
                                                  (gx_jack::gxjack.midi_port_buf, i, 3);

                        if (midi.midi_send) {
                            // volume value
                            midi.midi_send[2] = static_cast<int>(iTemps46);
                            // set controler volume
                            midi.midi_send[1] =  0x07;
                            // controller + channel
                            midi.midi_send[0] = 0xB0 | static_cast<int>(iTemps30);
                        }
                    }

                    midi.noten = preNote + iTemps29;
                    midi.send = 0;
                    midi.midistat = true;
                    midi.midistat1 = true;

                    if (( midi.noten >= 0)&&(midi.noten <= 127)) {
                        // pitch wheel clear
                        if (midi.fpitch) {
                            midi.midi_send = jack_midi_event_reserve
                                                      (gx_jack::gxjack.midi_port_buf, i, 3);
                            if (midi.midi_send) {
                                // pitch value
                                midi.midi_send[2] = 0x40;
                                // pitch value
                                midi.midi_send[1] = 0x00;
                                // controller + channel
                                midi.midi_send[0] = 0xE0 | static_cast<int>(iTemps30);
                            }
                        }
                        midi.midi_send = jack_midi_event_reserve
                                                  (gx_jack::gxjack.midi_port_buf, i, 3);
                        if (midi.midi_send) {
                            // velocity
                            midi.midi_send[2] = static_cast<int>(iTemps26);
                            // note
                            midi.midi_send[1] = midi.noten;
                            // controller + channel
                            midi.midi_send[0] = 0x90 | static_cast<int>(iTemps30);
                        }

                        // pitch wheel set auto
                        if (midi.fpitch) {
                            if (piwe < 0) piwe = 0;
                            if (fConsta2 > 0x3fff) piwe = 0x3fff;
                            midi.midi_send = jack_midi_event_reserve
                                                      (gx_jack::gxjack.midi_port_buf, i, 3);

                            if (midi.midi_send) {
                                // pitch
                                midi.midi_send[2] = (piwe >> 7) & 0x7f;
                                // pitch
                                midi.midi_send[1] = piwe & 0x7f;
                                // controller + channel
                                midi.midi_send[0] = 0xE0 | static_cast<int>(iTemps30);
                            }
                        }
                    }
                }

                // channel1
                if (midi.fcheckbox10) {
                    if (midi.program1 != iTemps36) {
                        midi.program1 = iTemps36;
                        midi.midistat = true;
                        midi.midi_send1 = jack_midi_event_reserve
                                                   (gx_jack::gxjack.midi_port_buf, i, 2);

                        if (midi.midi_send1) {
                            // program value
                            midi.midi_send1[1] = static_cast<int>(iTemps36);
                            // controller+ channel
                            midi.midi_send1[0] = 0xC0 | static_cast<int>(iTemps35);
                        }
                    }

                    if (midi.send1 > iTemps33) {
                        if (static_cast<int>(midi.fautogain1) == 1) {
                            iTemps47 = static_cast<int>(midi.beat0);
                            if ( iTemps47 < 0) iTemps47 = 0;
                            else if ( iTemps47 > 127) iTemps47 = 127;

                            midi.fslider47 = iTemps47;
                        }

                        if (midi.volume1 != iTemps47) {
                            midi.volume1 = iTemps47;
                            midi.midistat = true;
                            midi.midi_send1 = jack_midi_event_reserve
                                                       (gx_jack::gxjack.midi_port_buf, i, 3);
                            if (midi.midi_send1) {
                                // volume value
                                midi.midi_send1[2] = static_cast<int>(iTemps47);
                                // set controler channel volume
                                midi.midi_send1[1] =  0x07;
                                // controller + channel
                                midi.midi_send1[0] = 0xB0 | static_cast<int>(iTemps35);
                            }
                        }

                        midi.noten1 = preNote + iTemps34;
                        midi.send1 = 0;
                        midi.midistat = true;
                        midi.midistat2 = true;
                        if ((midi.noten1 >= 0)&&(midi.noten1 <= 127)) {
                            // pitch wheel clear
                            if (midi.fpitch1) {
                                midi.midi_send1 = jack_midi_event_reserve
                                                           (gx_jack::gxjack.midi_port_buf, i, 3);
                                if (midi.midi_send1) {
                                    // pitch value
                                    midi.midi_send1[2] =  0x40;
                                    // pitch value
                                    midi.midi_send1[1] = 0x00;
                                    // controller + channel
                                    midi.midi_send1[0] = 0xE0 |  static_cast<int>(iTemps35);
                                }
                            }
                            midi.midi_send1 = jack_midi_event_reserve(gx_jack::gxjack.midi_port_buf, i, 3);

                            if (midi.midi_send1) {
                                // velocity
                                midi.midi_send1[2] = static_cast<int>(iTemps32);
                                // note
                                midi.midi_send1[1] = midi.noten1;
                                // note on + channel
                                midi.midi_send1[0] = 0x90 | static_cast<int>(iTemps35);
                            }

                            // pitch wheel set auto
                            if (midi.fpitch1) {
                                if (piwe < 0) piwe = 0;
                                if (fConsta2 > 0x3fff) piwe = 0x3fff;
                                midi.midi_send1 = jack_midi_event_reserve
                                                           (gx_jack::gxjack.midi_port_buf, i, 3);

                                if (midi.midi_send1) {
                                    // pitch
                                    midi.midi_send1[2] = (piwe >> 7) & 0x7f;
                                    // pitch
                                    midi.midi_send1[1] = piwe & 0x7f;
                                    // controller + channel
                                    midi.midi_send1[0] = 0xE0 | static_cast<int>(iTemps35);
                                }
                            }
                        }
                    }
                }
                // channel2
                if (midi.fcheckbox11) {
                    if (midi.program2 != iTemps43) {
                        midi.program2 = iTemps43;
                        midi.midistat = true;
                        midi.midi_send2 = jack_midi_event_reserve(gx_jack::gxjack.midi_port_buf, i, 2);

                        if (midi.midi_send2) {
                            // program value
                            midi.midi_send2[1] =  static_cast<int>(iTemps43);
                            // controller
                            midi.midi_send2[0] = 0xC0 | static_cast<int>(iTemps44);
                        }
                    }

                    if (midi.send2 > iTemps41) {   // 20
                        if (static_cast<int>(midi.fautogain2) == 1) {
                            iTemps48 = static_cast<int>(midi.beat0);
                            if ( iTemps48 < 0) iTemps48 = 0;
                            else if ( iTemps48 > 127) iTemps48 = 127;
                            midi.fslider48 = iTemps48;
                        }

                        if (midi.volume2 != iTemps48) {
                            midi.volume2 = iTemps48;
                            midi.midistat = true;
                            midi.midi_send2 = jack_midi_event_reserve
                                                       (gx_jack::gxjack.midi_port_buf, i, 3);
                            if (midi.midi_send2) {
                                // volume value
                                midi.midi_send2[2] = static_cast<int>(iTemps48);
                                // set controler channel volume
                                midi.midi_send2[1] =  0x07;
                                // controller + channel
                                midi.midi_send2[0] = 0xB0 | static_cast<int>(iTemps44);
                            }
                        }

                        // pitch wheel clear
                        if (midi.fpitch2) {
                            midi.midi_send2 = jack_midi_event_reserve
                                                       (gx_jack::gxjack.midi_port_buf, i, 3);
                            if (midi.midi_send2) {
                                // pitch value
                                midi.midi_send2[2] =  0x40;
                                // pitch value
                                midi.midi_send2[1] = 0x00;
                                // controller + channel
                                midi.midi_send2[0] = 0xE0 |  static_cast<int>(iTemps44);
                            }
                        }

                        midi.noten2 = preNote + iTemps42;
                        midi.send2 = 0;
                        midi.midistat = true;
                        midi.midistat3 = true;

                        if ((midi.noten2 >= 0)&&(midi.noten2 <= 127)) {
                            midi.midi_send2 = jack_midi_event_reserve
                                                        (gx_jack::gxjack.midi_port_buf, i, 3);

                            if (midi.midi_send2) {
                                // velocity
                                midi.midi_send2[2] = static_cast<int>(iTemps40);
                                //  note
                                midi.midi_send2[1] = midi.noten2;
                                // note on + channel
                                midi.midi_send2[0] = 0x90 | static_cast<int>(iTemps44);
                            }

                            // pitch wheel set auto
                            if (midi.fpitch2) {
                                if (piwe < 0) piwe = 0;
                                if (fConsta2 > 0x3fff) piwe = 0x3fff;
                                midi.midi_send2 = jack_midi_event_reserve
                                                           (gx_jack::gxjack.midi_port_buf, i, 3);
                                if (midi.midi_send2) {
                                    // pitch
                                    midi.midi_send2[2] = (piwe >> 7) & 0x7f;
                                    // pitch
                                    midi.midi_send2[1] = piwe & 0x7f;
                                    // controller + channel
                                    midi.midi_send2[0] = 0xE0 |  static_cast<int>(iTemps44);
                                }
                            }
                        }
                    }
                }

                // end if playmidi = 1
            } else {
                if ((midi.weg > iTemps37) || (gx_jack::gxjack.jcpu_load > 64.0)) {
                    midi.send = midi.send1 = midi.send2 = 0;
                    midi.Beat_is = static_cast<int>(fTemps45);
                    if (midi.weg <  iTemps37a) {   // 5.0
                        midi.midistat = true;
                        midi.midi_send = jack_midi_event_reserve(gx_jack::gxjack.midi_port_buf, i, 3);

                        if (midi.midi_send) {
                            // velocity
                            midi.midi_send[2] = static_cast<int>(iTemps26);
                            // fix me all notes off
                            midi.midi_send[1] = 123;
                            // controller
                            midi.midi_send[0] = 0xB0 | static_cast<int>(iTemps30);
                        }

                        if (midi.fcheckbox10) {
                            midi.midistat = true;
                            midi.midi_send1 = jack_midi_event_reserve(gx_jack::gxjack.midi_port_buf, i, 3);

                            if (midi.midi_send1) {
                                // velocity
                                midi.midi_send1[2] = static_cast<int>(iTemps32);
                                // fix me all notes off
                                midi.midi_send1[1] = 123;
                                // controller
                                midi.midi_send1[0] = 0xB0 |  static_cast<int>(iTemps35);
                            }
                        }

                        if (midi.fcheckbox11) {
                            midi.midistat = true;
                            midi.midi_send2 = jack_midi_event_reserve(gx_jack::gxjack.midi_port_buf, i, 3);

                            if (midi.midi_send2) {
                                // velocity
                                midi.midi_send2[2] = static_cast<int>(iTemps40);
                                // fix me all notes off
                                midi.midi_send2[1] =  123;
                                // controller
                                midi.midi_send2[0] = 0xB0 | static_cast<int>(iTemps44);
                            }
                        }
                        midi.midistat = midi.midistat1 = midi.midistat2 = midi.midistat3 = false;
                    }
                }
                midi.weg+=step;
            }
        }
    }
}
} /* end of gx_engine namespace */
