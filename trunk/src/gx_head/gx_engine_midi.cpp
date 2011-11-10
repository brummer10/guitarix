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

#include "engine.h"

namespace gx_engine {

void MidiVariables::register_parameter(const ParamReg& reg) {
    reg.registerNonMidiVar("midi_out.midistat",  &midistat,  false);
    reg.registerNonMidiVar("midi_out.midistat1", &midistat1, false);
    reg.registerNonMidiVar("midi_out.midistat2", &midistat2, false);
    reg.registerNonMidiVar("midi_out.midistat3", &midistat3, false);

    reg.registerVar("midi_out.channel_1.velocity", "velocity", "S", "", &fslider26, 64, 0, 127, 1);
    reg.registerVar("midi_out.channel_1.volume", "volume", "S", "", &fslider46, 64, 0, 127, 1);
    reg.registerVar("midi_out.channel_1.autogain", "autogain", "B", "", &fautogain);
    reg.registerVar("midi_out.channel_1.channel", "channel 1", "S", "", &fslider30, 0, 0, 16, 1);
    reg.registerVar("midi_out.channel_1.program", "program", "S", "", &fslider31, 0, 0, 248, 1);
    reg.registerVar("midi_out.channel_1.oktave", "oktave", "S", "", &fslider29, 0, -2, 2, 1);
    reg.registerVar("midi_out.channel_1.sensity", "sensity", "S", "", &fslider27, 20, 1, 500, 1);
    reg.registerVar("midi_out.channel_1.auto_pitch", "auto pitch", "B", "", &fpitch);

    reg.registerVar("midi_out.channel_2.on_off", "on/off", "B", "", &fcheckbox10, 0);
    reg.registerVar("midi_out.channel_2.velocity", "velocity", "S", "", &fslider32, 64, 0, 127, 1);
    reg.registerVar("midi_out.channel_2.volume", "volume", "S", "", &fslider47, 64, 0, 127, 1);
    reg.registerVar("midi_out.channel_2.autogain", "autogain", "B", "", &fautogain1);
    reg.registerVar("midi_out.channel_2.channel", "channel 2", "S", "", &fslider35, 0, 0, 16, 1);
    reg.registerVar("midi_out.channel_2.program", "program", "S", "", &fslider36, 0, 0, 248, 1);
    reg.registerVar("midi_out.channel_2.oktave", "oktave", "S", "", &fslider34, 0, -2, 2, 1);
    reg.registerVar("midi_out.channel_2.sensity", "sensity", "S", "", &fslider33, 20, 1, 500, 1);
    reg.registerVar("midi_out.channel_2.auto_pitch", "auto pitch", "B", "", &fpitch1);

    reg.registerVar("midi_out.channel_3.on_off", "on/off", "B", "", &fcheckbox11, 0);
    reg.registerVar("midi_out.channel_3.velocity", "velocity", "S", "", &fslider40, 64, 0, 127, 1);
    reg.registerVar("midi_out.channel_3.volume", "volume", "S", "", &fslider48, 64, 0, 127, 1);
    reg.registerVar("midi_out.channel_3.autogain", "autogain", "B", "", &fautogain2);
    reg.registerVar("midi_out.channel_3.channel", "channel 3", "S", "", &fslider44, 0, 0, 16, 1);
    reg.registerVar("midi_out.channel_3.program", "program", "S", "", &fslider43, 0, 0, 248, 1);
    reg.registerVar("midi_out.channel_3.oktave", "oktave", "S", "", &fslider42, 0, -2, 2, 1);
    reg.registerVar("midi_out.channel_3.sensity", "sensity", "S", "", &fslider41, 20, 1, 500, 1);
    reg.registerVar("midi_out.channel_3.auto_pitch", "auto pitch", "B", "", &fpitch2);

    reg.registerVar("beat_detector.stepper", "stepper", "S", "", &fslider39, 1, 1, 32, 1);
    reg.registerVar("beat_detector.note_off", "note off", "S", "", &fslider37, 2, 1, 127, 1);
    reg.registerVar("beat_detector.atack_gain", "atack gain", "S", "", &fslider45, 5, 1, 127, 1);
    reg.registerVar("beat_detector.beat_gain", "beat gain", "S", "", &fslider38, 1, 0.0f, 127, 1);
    reg.registerVar("beat_detector.midi_gain", "midi gain", "S", "", &midi_gain, 0, -40, 60, 1);
}

void MidiVariables::init(int samplingFreq) {
    fConstlog = log(1.055) * 0.5;
    fConstlog2 = 6/log(2) * -1;
    midi_gain = 1.0;
    fConstun0  = (0.001 * 300 * samplingFreq) * 36;
    BeatFilterk =1.0/(samplingFreq * (1.0f/(2.0f * M_PI * 1250.0f)));
    BeatFilter1 =0.0;
    BeatFilter2 =0.0;
}

inline float sqrf(float x) {
    return x * x;
}

// ----- jack process callback for the midi output
void MidiVariables::process_midi(int len, float *audiodata, void *midi_port_buf, float jcpu_load,
				 float fConsta4, float fConsta1t) {
    static float fnote = 1000.;
    float fConsta2 = 0.;
    float fTemps45 = fslider45;
    float fTemps38 = fslider38;
    float rms = 0.;
    float midi_db = 0.;
    float sum = 0.;

    int preNote = 0;
    int iTemps31 = static_cast<int>(fslider31);
    int iTemps30 = static_cast<int>(fslider30);
    int iTemps27 = static_cast<int>(fslider27);
    int iTemps29 = static_cast<int>(fslider29)*12;
    int iTemps26 = static_cast<int>(fslider26);
    int iTemps36 = static_cast<int>(fslider36);
    int iTemps35 = static_cast<int>(fslider35);
    int iTemps33 = static_cast<int>(fslider33);
    int iTemps34 = static_cast<int>(fslider34)*12;
    int iTemps32 = static_cast<int>(fslider32);
    int iTemps43 = static_cast<int>(fslider43);
    int iTemps44 = static_cast<int>(fslider44);
    int iTemps41 = static_cast<int>(fslider41);
    int iTemps42 = static_cast<int>(fslider42)*12;
    int iTemps40 = static_cast<int>(fslider40);
    int step = static_cast<int>(fslider39);
    int iTemps37  = static_cast<int>(48000/fslider37);
    int iTemps37a  = iTemps37+5;
    int iTemps46 = static_cast<int>(fslider46);
    int iTemps47 = static_cast<int>(fslider47);
    int iTemps48 = static_cast<int>(fslider48);
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
    // fnote = 12 * log2f(2.272727e-03f * fConsta4);
    if (fConsta1t < 999.) fnote = fConsta1t;
    preNote = static_cast<int>(round(fnote))+57;
    fConsta2 = fnote - (preNote - 57);
    piwe = (static_cast<int>(fConsta2+1)) * 8192; // pitch wheel value
    // preNote = round(fConsta1t)+57;
    // weg = 0;


    for (int i = 0; i < len; i += step) {

	float audio_db = *audiodata++;
	BeatFilter1 = BeatFilter1+(BeatFilterk*(audio_db-BeatFilter1));
	BeatFilter2 = BeatFilter2+(BeatFilterk*(BeatFilter1-
							       BeatFilter2));
	audio_db = BeatFilter2*10;
	if (audio_db > 0.00001) {
	    // ----- convert the audio gain to midi gain value
	    midi_db = (log(fabs(audio_db))*fConstlog2);
	    beat0 = 254- floor(exp(fConstlog*midi_db)*127)+ midi_gain;
	    rms = beat0;
	}
	// ----- check gain value and run only when gain is higher then the selected value
	if (beat0 >= fTemps45 && jcpu_load < 65.0) {

	    // ----- rms the gain for a smother output
	    if (cs == static_cast<int>(fConstun0*stepper)) {
		cs = 0;
		sum = 0;
	    } else {
		cs += 1;
		sum += sqrf(rms);
	    }

	    beat0 = sqrtf(sum/cs);
	    // set the value for the tuner
	    // audio.fConsta1 = fnote;
	    // set timeout for tuner fallback
	    weg = 0;

	    if (rms >= (Beat_is + fTemps38)) {
		// Beat_is = rms;
		Beat_is += static_cast<int>(rms*0.1);
		send+=step;
		if (fcheckbox10 ) send1+=step;
		if (fcheckbox11 ) send2+=step;
		// weg -= step;
	    }
	    // else weg +=step;

	    // ----- start the midi output

	    // channel0
	    if (program != iTemps31) {
		program = iTemps31;
		midistat = true;
		midi_send = jack_midi_event_reserve(midi_port_buf, i, 2);

		if (midi_send) {
		    // program value
		    midi_send[1] =  static_cast<int>(iTemps31);
		    // controller+ channel
		    midi_send[0] = 0xC0 | static_cast<int>(iTemps30);
		}
	    }

	    if (send > iTemps27) {     // 20
		if (static_cast<int>(fautogain) == 1) {
		    iTemps46 = static_cast<int>(beat0);
		    if ( iTemps46 < 0) iTemps46 = 0;
		    else if ( iTemps46 > 127) iTemps46 = 127;
		    fslider46 = iTemps46;
		}
		if (volume != iTemps46) {
		    volume = iTemps46;
		    midistat = true;
		    midi_send = jack_midi_event_reserve(midi_port_buf, i, 3);

		    if (midi_send) {
			// volume value
			midi_send[2] = static_cast<int>(iTemps46);
			// set controler volume
			midi_send[1] =  0x07;
			// controller + channel
			midi_send[0] = 0xB0 | static_cast<int>(iTemps30);
		    }
		}

		noten = preNote + iTemps29;
		send = 0;
		midistat = true;
		midistat1 = true;

		if (( noten >= 0)&&(noten <= 127)) {
		    // pitch wheel clear
		    if (fpitch) {
			midi_send = jack_midi_event_reserve(midi_port_buf, i, 3);
			if (midi_send) {
			    // pitch value
			    midi_send[2] = 0x40;
			    // pitch value
			    midi_send[1] = 0x00;
			    // controller + channel
			    midi_send[0] = 0xE0 | static_cast<int>(iTemps30);
			}
		    }
		    midi_send = jack_midi_event_reserve(midi_port_buf, i, 3);
		    if (midi_send) {
			// velocity
			midi_send[2] = static_cast<int>(iTemps26);
			// note
			midi_send[1] = noten;
			// controller + channel
			midi_send[0] = 0x90 | static_cast<int>(iTemps30);
		    }

		    // pitch wheel set auto
		    if (fpitch) {
			if (piwe < 0) piwe = 0;
			if (fConsta2 > 0x3fff) piwe = 0x3fff;
			midi_send = jack_midi_event_reserve(midi_port_buf, i, 3);

			if (midi_send) {
			    // pitch
			    midi_send[2] = (piwe >> 7) & 0x7f;
			    // pitch
			    midi_send[1] = piwe & 0x7f;
			    // controller + channel
			    midi_send[0] = 0xE0 | static_cast<int>(iTemps30);
			}
		    }
		}
	    }

	    // channel1
	    if (fcheckbox10) {
		if (program1 != iTemps36) {
		    program1 = iTemps36;
		    midistat = true;
		    midi_send1 = jack_midi_event_reserve(midi_port_buf, i, 2);

		    if (midi_send1) {
			// program value
			midi_send1[1] = static_cast<int>(iTemps36);
			// controller+ channel
			midi_send1[0] = 0xC0 | static_cast<int>(iTemps35);
		    }
		}

		if (send1 > iTemps33) {
		    if (static_cast<int>(fautogain1) == 1) {
			iTemps47 = static_cast<int>(beat0);
			if ( iTemps47 < 0) iTemps47 = 0;
			else if ( iTemps47 > 127) iTemps47 = 127;

			fslider47 = iTemps47;
		    }

		    if (volume1 != iTemps47) {
			volume1 = iTemps47;
			midistat = true;
			midi_send1 = jack_midi_event_reserve(midi_port_buf, i, 3);
			if (midi_send1) {
			    // volume value
			    midi_send1[2] = static_cast<int>(iTemps47);
			    // set controler channel volume
			    midi_send1[1] =  0x07;
			    // controller + channel
			    midi_send1[0] = 0xB0 | static_cast<int>(iTemps35);
			}
		    }

		    noten1 = preNote + iTemps34;
		    send1 = 0;
		    midistat = true;
		    midistat2 = true;
		    if ((noten1 >= 0)&&(noten1 <= 127)) {
			// pitch wheel clear
			if (fpitch1) {
			    midi_send1 = jack_midi_event_reserve(midi_port_buf, i, 3);
			    if (midi_send1) {
				// pitch value
				midi_send1[2] =  0x40;
				// pitch value
				midi_send1[1] = 0x00;
				// controller + channel
				midi_send1[0] = 0xE0 |  static_cast<int>(iTemps35);
			    }
			}
			midi_send1 = jack_midi_event_reserve(midi_port_buf, i, 3);

			if (midi_send1) {
			    // velocity
			    midi_send1[2] = static_cast<int>(iTemps32);
			    // note
			    midi_send1[1] = noten1;
			    // note on + channel
			    midi_send1[0] = 0x90 | static_cast<int>(iTemps35);
			}

			// pitch wheel set auto
			if (fpitch1) {
			    if (piwe < 0) piwe = 0;
			    if (fConsta2 > 0x3fff) piwe = 0x3fff;
			    midi_send1 = jack_midi_event_reserve(midi_port_buf, i, 3);

			    if (midi_send1) {
				// pitch
				midi_send1[2] = (piwe >> 7) & 0x7f;
				// pitch
				midi_send1[1] = piwe & 0x7f;
				// controller + channel
				midi_send1[0] = 0xE0 | static_cast<int>(iTemps35);
			    }
			}
		    }
		}
	    }
	    // channel2
	    if (fcheckbox11) {
		if (program2 != iTemps43) {
		    program2 = iTemps43;
		    midistat = true;
		    midi_send2 = jack_midi_event_reserve(midi_port_buf, i, 2);

		    if (midi_send2) {
			// program value
			midi_send2[1] =  static_cast<int>(iTemps43);
			// controller
			midi_send2[0] = 0xC0 | static_cast<int>(iTemps44);
		    }
		}

		if (send2 > iTemps41) {   // 20
		    if (static_cast<int>(fautogain2) == 1) {
			iTemps48 = static_cast<int>(beat0);
			if ( iTemps48 < 0) iTemps48 = 0;
			else if ( iTemps48 > 127) iTemps48 = 127;
			fslider48 = iTemps48;
		    }

		    if (volume2 != iTemps48) {
			volume2 = iTemps48;
			midistat = true;
			midi_send2 = jack_midi_event_reserve(midi_port_buf, i, 3);
			if (midi_send2) {
			    // volume value
			    midi_send2[2] = static_cast<int>(iTemps48);
			    // set controler channel volume
			    midi_send2[1] =  0x07;
			    // controller + channel
			    midi_send2[0] = 0xB0 | static_cast<int>(iTemps44);
			}
		    }

		    // pitch wheel clear
		    if (fpitch2) {
			midi_send2 = jack_midi_event_reserve(midi_port_buf, i, 3);
			if (midi_send2) {
			    // pitch value
			    midi_send2[2] =  0x40;
			    // pitch value
			    midi_send2[1] = 0x00;
			    // controller + channel
			    midi_send2[0] = 0xE0 |  static_cast<int>(iTemps44);
			}
		    }

		    noten2 = preNote + iTemps42;
		    send2 = 0;
		    midistat = true;
		    midistat3 = true;

		    if ((noten2 >= 0)&&(noten2 <= 127)) {
			midi_send2 = jack_midi_event_reserve(midi_port_buf, i, 3);

			if (midi_send2) {
			    // velocity
			    midi_send2[2] = static_cast<int>(iTemps40);
			    //  note
			    midi_send2[1] = noten2;
			    // note on + channel
			    midi_send2[0] = 0x90 | static_cast<int>(iTemps44);
			}

			// pitch wheel set auto
			if (fpitch2) {
			    if (piwe < 0) piwe = 0;
			    if (fConsta2 > 0x3fff) piwe = 0x3fff;
			    midi_send2 = jack_midi_event_reserve(midi_port_buf, i, 3);
			    if (midi_send2) {
				// pitch
				midi_send2[2] = (piwe >> 7) & 0x7f;
				// pitch
				midi_send2[1] = piwe & 0x7f;
				// controller + channel
				midi_send2[0] = 0xE0 |  static_cast<int>(iTemps44);
			    }
			}
		    }
		}
	    }

	    // end if playmidi = 1
	} else {
	    if (weg > iTemps37 || jcpu_load > 64.0) {
		send = send1 = send2 = 0;
		Beat_is = static_cast<int>(fTemps45);
		if (weg <  iTemps37a) {   // 5.0
		    midistat = true;
		    midi_send = jack_midi_event_reserve(midi_port_buf, i, 3);

		    if (midi_send) {
			// velocity
			midi_send[2] = static_cast<int>(iTemps26);
			// fix me all notes off
			midi_send[1] = 123;
			// controller
			midi_send[0] = 0xB0 | static_cast<int>(iTemps30);
		    }

		    if (fcheckbox10) {
			midistat = true;
			midi_send1 = jack_midi_event_reserve(midi_port_buf, i, 3);

			if (midi_send1) {
			    // velocity
			    midi_send1[2] = static_cast<int>(iTemps32);
			    // fix me all notes off
			    midi_send1[1] = 123;
			    // controller
			    midi_send1[0] = 0xB0 |  static_cast<int>(iTemps35);
			}
		    }

		    if (fcheckbox11) {
			midistat = true;
			midi_send2 = jack_midi_event_reserve(midi_port_buf, i, 3);

			if (midi_send2) {
			    // velocity
			    midi_send2[2] = static_cast<int>(iTemps40);
			    // fix me all notes off
			    midi_send2[1] =  123;
			    // controller
			    midi_send2[0] = 0xB0 | static_cast<int>(iTemps44);
			}
		    }
		    midistat = midistat1 = midistat2 = midistat3 = false;
		}
	    }
	    weg+=step;
	}
    }
}
} /* end of gx_engine namespace */
