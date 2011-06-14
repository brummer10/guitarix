/*
 * Copyright (C) 2009, 2010 Hermann Meyer, James Warden, Andreas Degert
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
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 * --------------------------------------------------------------------------
 *
 *
 *    This is the Guitarix MIDI Engine NOT using a ring buffer
 *
 *
 * --------------------------------------------------------------------------
 */

#include "guitarix.h"

namespace gx_engine
{

void MidiVariables::register_parameter()
{
	gx_gui::registerParam("midi_out.channel_1.velocity", "velocity", &fslider26, 64.f, 0.f, 127.f, 1.f);
	gx_gui::registerParam("midi_out.channel_1.volume", "volume", &fslider46, 64.f, 0.f, 127.f, 1.f);
	gx_gui::registerParam("midi_out.channel_1.autogain", "autogain", &fautogain);
	gx_gui::registerParam("midi_out.channel_1.channel", "channel 1", &fslider30, 0.f, 0.f, 16.f, 1.f);
	gx_gui::registerParam("midi_out.channel_1.program", "program", &fslider31, 0.f, 0.f, 248.f, 1.f);
	gx_gui::registerParam("midi_out.channel_1.oktave", "oktave", &fslider29, 0.f, -2.f, 2.f, 1.f);
	gx_gui::registerParam("midi_out.channel_1.sensity", "sensity", &fslider27, 20.f, 1.f, 500.f, 1.f);
	gx_gui::registerParam("midi_out.channel_1.auto_pitch", "auto pitch", &fpitch);

	gx_gui::registerParam("midi_out.channel_2.on_off", "on/off", &fcheckbox10, 0);
	gx_gui::registerParam("midi_out.channel_2.velocity", "velocity", &fslider32, 64.f, 0.f, 127.f, 1.f);
	gx_gui::registerParam("midi_out.channel_2.volume", "volume", &fslider47, 64.f, 0.f, 127.f, 1.f);
	gx_gui::registerParam("midi_out.channel_2.autogain", "autogain", &fautogain1);
	gx_gui::registerParam("midi_out.channel_2.channel", "channel 2", &fslider35, 0.f, 0.f, 16.f, 1.f);
	gx_gui::registerParam("midi_out.channel_2.program", "program", &fslider36, 0.f, 0.f, 248.f, 1.f);
	gx_gui::registerParam("midi_out.channel_2.oktave", "oktave", &fslider34, 0.f, -2.f, 2.f, 1.f);
	gx_gui::registerParam("midi_out.channel_2.sensity", "sensity", &fslider33, 20.f, 1.f, 500.f, 1.f);
	gx_gui::registerParam("midi_out.channel_2.auto_pitch", "auto pitch", &fpitch1);

	gx_gui::registerParam("midi_out.channel_3.on_off", "on/off", &fcheckbox11, 0);
	gx_gui::registerParam("midi_out.channel_3.velocity", "velocity", &fslider40, 64.f, 0.f, 127.f, 1.f);
	gx_gui::registerParam("midi_out.channel_3.volume", "volume", &fslider48, 64.f, 0.f, 127.f, 1.f);
	gx_gui::registerParam("midi_out.channel_3.autogain", "autogain", &fautogain2);
	gx_gui::registerParam("midi_out.channel_3.channel", "channel 3", &fslider44, 0.f, 0.f, 16.f, 1.f);
	gx_gui::registerParam("midi_out.channel_3.program", "program", &fslider43, 0.f, 0.f, 248.f, 1.f);
	gx_gui::registerParam("midi_out.channel_3.oktave", "oktave", &fslider42, 0.f, -2.f, 2.f, 1.f);
	gx_gui::registerParam("midi_out.channel_3.sensity", "sensity", &fslider41, 20.f, 1.f, 500.f, 1.f);
	gx_gui::registerParam("midi_out.channel_3.auto_pitch", "auto pitch", &fpitch2);

	gx_gui::registerParam("beat_detector.stepper", "stepper", &fslider39, 1.f, 1.f, 32.f, 1.f);
	gx_gui::registerParam("beat_detector.note_off", "note off", &fslider37, 2.f, 1.f, 127.f, 1.f);
	gx_gui::registerParam("beat_detector.atack_gain", "atack gain", &fslider45, 5.f, 1.f, 127.f, 1.f);
	gx_gui::registerParam("beat_detector.beat_gain", "beat gain", &fslider38, 1.f, 0.0f, 127.f, 1.f);
	gx_gui::registerParam("beat_detector.midi_gain", "midi gain", &midi_gain, 0.f, -40.f, 60.f, 1.f);
}

MidiVariables midi;

/*
float fslider45;
float fslider38;
float fslider31;
float fslider27;
float fslider29;
float fslider30;
float fslider26;
float fslider33;
float fslider34;
float fslider35;
float fslider36;
float fslider42;
float fslider43;
float fslider40;
float fslider41;
float fslider44;
float fslider37;
float fslider39;
float fslider46;
float fslider47;
float fslider48;
float fConsta4;
float fConstlog;
float fConstlog2;
float beat0;
float midi_gain;
float fConstun0;
int   weg;
int   program;
unsigned char* midi_send;
int   send;
float fautogain;
int   volume;
float fpitch;
int   noten;
float fslider32;
float cache_note;
int fcheckbox10;
int   program1;
int   send1;
int   noten1;
float fautogain1;
int   volume1;
unsigned char* midi_send1;
int   send2;
int   noten2;
float fpitch1;
float fpitch2;
int fcheckbox11;
int   program2;
int   volume2;
int Beat_is;
unsigned char* midi_send2;
float fautogain2;
*/

void MidiVariables::init(int samplingFreq)
{
	fConstlog = log(1.055)*0.5;;
	fConstlog2 = 6/log(2)*-1;
	midi_gain = 1.0;
	fConstun0  = (0.001*300*samplingFreq)*36;
	BeatFilterk =1.0/(gx_jack::gxjack.jack_sr*(1.0f/(2.0f*M_PI*1250.0f)));
	BeatFilter1 =0.0;
    BeatFilter2 =0.0;
}

//----- jack process callback for the midi input
void compute_midi_in(void* midi_input_port_buf)
{
	jack_midi_event_t in_event;
	jack_nframes_t event_count = jack_midi_get_event_count(midi_input_port_buf);
	unsigned int i;
	for (i=0; i<event_count; i++) {
		jack_midi_event_get(&in_event, midi_input_port_buf, i);
		if ((in_event.buffer[0] & 0xf0) == 0xc0) {  // program change on any midi channel
			g_atomic_int_set(&gx_gui::program_change, in_event.buffer[1]);
			sem_post(&gx_gui::program_change_sem);
		}
		else if ((in_event.buffer[0] & 0xf0) == 0xb0) {   // controller
			gx_gui::controller_map.set(in_event.buffer[1], in_event.buffer[2]);
		}
	}
}

void compute_midi(int len)
{

	// retrieve engine state
	const GxEngineState estate = checky;

	//------------ determine processing type
	unsigned short process_type = ZEROIZE_BUFFERS;

	if (gx_jack::NO_CONNECTION == 0) // ports connected
	{
		switch (estate)
		{
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

	//------------ main processing routine
	switch (process_type)
	{
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


//----- jack process callback for the midi output
void process_midi(int len)
{
	//----- only run it when midi out or tuner is enabled
	if (isMidiOn())
	{
		static float fnote = 1000.;
		float 	fConsta2 = 0.;
		float fTemps45 = midi.fslider45;
		float fTemps38 = midi.fslider38;
		float rms = 0.;
		float midi_db = 0.;
		float sum = 0.;
		float *audiodata = checkfreq;

		int preNote = 0;
		int iTemps31 = int(midi.fslider31);
		int iTemps30 = int(midi.fslider30);
		int iTemps27 = int(midi.fslider27);
		int iTemps29 = int(midi.fslider29)*12;
		int iTemps26 = int(midi.fslider26);
		int iTemps36 = int(midi.fslider36);
		int iTemps35 = int(midi.fslider35);
		int iTemps33 = int(midi.fslider33);
		int iTemps34 = int(midi.fslider34)*12;
		int iTemps32 = int(midi.fslider32);
		int iTemps43 = int(midi.fslider43);
		int iTemps44 = int(midi.fslider44);
		int iTemps41 = int(midi.fslider41);
		int iTemps42 = int(midi.fslider42)*12;
		int iTemps40 = int(midi.fslider40);
		int step = int(midi.fslider39);
		int iTemps37  = int(48000/midi.fslider37);
		int iTemps37a  = iTemps37+5;
		int iTemps46 = int(midi.fslider46);
		int iTemps47 = int(midi.fslider47);
		int iTemps48 = int(midi.fslider48);
		int piwe = 0;
		int cs = 0;

		double stepper = 1./step;

	
		/**fConsta4 is the frequence value from the actuell frame, here we
		   calculate the Note from the freq by log2(freq/440)*12
		   the result is the Note (as float) related to the note "A"

		   preNote contains the next posible Note, related by round float to int.
		   piwe contain the pitchweel value witch show the diff
		   beetween the detected Note and
		   the real Note by frequency.
		**/
		//fnote = 12 * log2f(2.272727e-03f * midi.fConsta4);
		if(audio.fConsta1t < 999.) fnote = audio.fConsta1t;
		preNote = int(round(fnote))+57;
		fConsta2 = fnote - (preNote - 57);
		piwe = ((int)fConsta2+1) * 8192; // pitch wheel value
		// preNote = round(fConsta1t)+57;
		// weg = 0;


		for (int i=0; i<len; i+=step)
		{
			float audio_db = *audiodata++;
			midi.BeatFilter1 = midi.BeatFilter1+(midi.BeatFilterk*(audio_db-midi.BeatFilter1));
            midi.BeatFilter2 = midi.BeatFilter2+(midi.BeatFilterk*(midi.BeatFilter1-midi.BeatFilter2));
            audio_db = midi.BeatFilter2*10;
			if(audio_db > 0.00001)
			{
				//----- convert the audio gain to midi gain value
				midi_db = (log(fabs(audio_db))*midi.fConstlog2);
				midi.beat0 = 254- floor(exp(midi.fConstlog*midi_db)*127)+ midi.midi_gain;
				rms = midi.beat0;
			}
			//----- check gain value and run only when gain is higher then the selected value
			if (( midi.beat0 >= fTemps45) && (gx_jack::gxjack.jcpu_load < 65.0))
			{

				//----- rms the gain for a smother output
				if (cs == int(midi.fConstun0*stepper))
				{
					cs = 0;
					sum = 0;
				}
				else
				{
					cs += 1;
					sum += sqrf(rms);
				}

				midi.beat0 = sqrtf(sum/cs);
				//set the value for the tuner
				//audio.fConsta1 = fnote;
				//set timeout for tuner fallback
				midi.weg = 0;
				
				if ( rms >= (midi.Beat_is + fTemps38))
				{
					//midi.Beat_is = rms;
					midi.Beat_is += (int)(rms*0.1);
					midi.send+=step;
					if (midi.fcheckbox10 ) midi.send1+=step;
					if (midi.fcheckbox11 ) midi.send2+=step;
					//midi.weg -= step; 
				}
				// else midi.weg +=step;

				//----- start the midi output
				
					// channel0
					if (midi.program != iTemps31)
					{
						midi.program = iTemps31;
						audio.midistat += 1.0f;
						midi.midi_send = jack_midi_event_reserve(gx_jack::midi_port_buf, i, 2);

						if (midi.midi_send)
						{
							midi.midi_send[1] =  (int)iTemps31;  // program value
							midi.midi_send[0] = 0xC0 | (int)iTemps30;  // controller+ channel
						}
					}

					if (midi.send > iTemps27)     //20
					{
						if (int(midi.fautogain) == 1)
						{
							iTemps46 = (int)midi.beat0;
							if ( iTemps46 < 0) iTemps46 = 0;
							else if ( iTemps46 > 127) iTemps46 = 127;
							midi.fslider46 = iTemps46;
						}
						if (midi.volume != iTemps46)
						{
							midi.volume = iTemps46;
							audio.midistat += 1.0f;
							midi.midi_send = jack_midi_event_reserve(gx_jack::midi_port_buf, i, 3);

							if (midi.midi_send)
							{
								midi.midi_send[2] = (int)iTemps46;	// volume value
								midi.midi_send[1] =  0x07;     // set controler volume
								midi.midi_send[0] = 0xB0 | (int)iTemps30;  // controller + channel
							}
						}

						midi.noten = preNote + iTemps29;
						midi.send = 0;
						audio.midistat += 1.0f;
						audio.midistat1 = true;

						if (( midi.noten>=0)&&(midi.noten<=127))
						{
							// pitch wheel clear
							if (midi.fpitch == 1.0)
							{
								midi.midi_send = jack_midi_event_reserve(gx_jack::midi_port_buf, i, 3);
								if (midi.midi_send)
								{
									midi.midi_send[2] =  0x40;  // pitch value
									midi.midi_send[1] = 0x00 ; // pitch value
									midi.midi_send[0] = 0xE0 |  (int)iTemps30; // controller + channel
								}
							}
							midi.midi_send = jack_midi_event_reserve(gx_jack::midi_port_buf, i, 3);
							if (midi.midi_send)
							{
								midi.midi_send[2] = (int)iTemps26; // velocity
								midi.midi_send[1] = midi.noten ; // note
								midi.midi_send[0] = 0x90 |  (int)iTemps30;	// controller + channel
							}

							// pitch wheel set auto
							if (midi.fpitch == 1.0)
							{
								if (piwe < 0) piwe = 0;
								if (fConsta2 > 0x3fff) piwe = 0x3fff;
								midi.midi_send = jack_midi_event_reserve(gx_jack::midi_port_buf, i, 3);

								if (midi.midi_send)
								{
									midi.midi_send[2] = (piwe >> 7) & 0x7f;  // pitch
									midi.midi_send[1] = piwe & 0x7f ; // pitch
									midi.midi_send[0] = 0xE0 |  (int)iTemps30; // controller + channel
								}
							}
						}
					}

					// channel1
					if (midi.fcheckbox10)
					{
						if (midi.program1 != iTemps36)
						{
							midi.program1 = iTemps36;
							audio.midistat += 1.0f;
							midi.midi_send1 = jack_midi_event_reserve(gx_jack::midi_port_buf, i, 2);

							if (midi.midi_send1)
							{
								midi.midi_send1[1] = (int)iTemps36;  // program value
								midi.midi_send1[0] = 0xC0 | (int)iTemps35; // controller+ channel
							}
						}

						if (midi.send1 > iTemps33)
						{
							if (int(midi.fautogain1) == 1)
							{
								iTemps47 = (int)midi.beat0;
								if ( iTemps47 < 0) iTemps47 = 0;
								else if ( iTemps47 > 127) iTemps47 = 127;

								midi.fslider47 = iTemps47;
							}

							if (midi.volume1 != iTemps47)
							{
								midi.volume1 = iTemps47;
								audio.midistat += 1.0f;
								midi.midi_send1 = jack_midi_event_reserve(gx_jack::midi_port_buf, i, 3);
								if (midi.midi_send1)
								{
									midi.midi_send1[2] = (int)iTemps47;  // volume value
									midi.midi_send1[1] =  0x07; // set controler channel volume
									midi.midi_send1[0] = 0xB0 | (int)iTemps35; // controller + channel
								}
							}

							midi.noten1 = preNote + iTemps34;
							midi.send1 = 0;
							audio.midistat += 1.0f;
							audio.midistat2 = true;
							if ((midi.noten1>=0)&&(midi.noten1<=127))
							{
								// pitch wheel clear
								if (midi.fpitch1 == 1.0)
								{
									midi.midi_send1 = jack_midi_event_reserve(gx_jack::midi_port_buf, i, 3);
									if (midi.midi_send1)
									{
										midi.midi_send1[2] =  0x40;  // pitch value
										midi.midi_send1[1] = 0x00 ; // pitch value
										midi.midi_send1[0] = 0xE0 |  (int)iTemps35;  // controller + channel
									}
								}
								midi.midi_send1 = jack_midi_event_reserve(gx_jack::midi_port_buf, i, 3);

								if (midi.midi_send1)
								{
									midi.midi_send1[2] = (int)iTemps32; // velocity
									midi.midi_send1[1] = midi.noten1; // note
									midi.midi_send1[0] = 0x90 | (int)iTemps35; // note on + channel
								}

								// pitch wheel set auto
								if (midi.fpitch1 == 1.0)
								{
									if (piwe < 0) piwe = 0;
									if (fConsta2 > 0x3fff) piwe = 0x3fff;
									midi.midi_send1 = jack_midi_event_reserve(gx_jack::midi_port_buf, i, 3);

									if (midi.midi_send1)
									{
										midi.midi_send1[2] = (piwe >> 7) & 0x7f;  // pitch
										midi.midi_send1[1] = piwe & 0x7f ; // pitch
										midi.midi_send1[0] = 0xE0 |  (int)iTemps35; // controller + channel
									}
								}
							}
						}
					}
					// channel2
					if (midi.fcheckbox11)
					{
						if (midi.program2 != iTemps43)
						{
							midi.program2 = iTemps43;
							audio.midistat += 1.0f;
							midi.midi_send2 = jack_midi_event_reserve(gx_jack::midi_port_buf, i, 2);

							if (midi.midi_send2)
							{
								midi.midi_send2[1] =  (int)iTemps43;  // program value
								midi.midi_send2[0] = 0xC0 | (int)iTemps44; // controller
							}
						}

						if (midi.send2 > iTemps41)   //20
						{
							if (int(midi.fautogain2) == 1)
							{
								iTemps48 = (int)midi.beat0;
								if ( iTemps48 < 0) iTemps48 = 0;
								else if ( iTemps48 > 127) iTemps48 = 127;
								midi.fslider48 = iTemps48;
							}

							if (midi.volume2 != iTemps48)
							{
								midi.volume2 = iTemps48;
								audio.midistat += 1.0f;
								midi.midi_send2 = jack_midi_event_reserve(gx_jack::midi_port_buf, i, 3);
								if (midi.midi_send2)
								{
									midi.midi_send2[2] = (int)iTemps48;  // volume value
									midi.midi_send2[1] =  0x07; // set controler channel volume
									midi.midi_send2[0] = 0xB0 | (int)iTemps44; // controller + channel
								}
							}

							// pitch wheel clear
							if (midi.fpitch2 == 1.0)
							{
								midi.midi_send2 = jack_midi_event_reserve(gx_jack::midi_port_buf, i, 3);
								if (midi.midi_send2)
								{
									midi.midi_send2[2] =  0x40;  // pitch value
									midi.midi_send2[1] = 0x00 ; // pitch value
									midi.midi_send2[0] = 0xE0 |  (int)iTemps44;	// controller + channel
								}
							}

							midi.noten2 = preNote + iTemps42;
							midi.send2 = 0;
							audio.midistat += 1.0f;
							audio.midistat3 = true;

							if ((midi.noten2>=0)&&(midi.noten2<=127))
							{
								midi.midi_send2 = jack_midi_event_reserve(gx_jack::midi_port_buf, i, 3);

								if (midi.midi_send2)
								{
									midi.midi_send2[2] = (int)iTemps40; // velocity
									midi.midi_send2[1] = midi.noten2; //  note
									midi.midi_send2[0] = 0x90 | (int)iTemps44;  // note on + channel
								}

								// pitch wheel set auto
								if (midi.fpitch2 == 1.0)
								{
									if (piwe < 0) piwe = 0;
									if (fConsta2 > 0x3fff) piwe = 0x3fff;
									midi.midi_send2 = jack_midi_event_reserve(gx_jack::midi_port_buf, i, 3);
									if (midi.midi_send2)
									{
										midi.midi_send2[2] = (piwe >> 7) & 0x7f;  // pitch
										midi.midi_send2[1] = piwe & 0x7f ; // pitch
										midi.midi_send2[0] = 0xE0 |  (int)iTemps44; // controller + channel
									}
								}
							}
						}
					}

					
				

				// end if playmidi = 1
			}
			else
			{
				
					if ((midi.weg > iTemps37) || (gx_jack::gxjack.jcpu_load > 64.0))
					{
						midi.send = midi.send1 = midi.send2 = 0;
						midi.Beat_is = (int)fTemps45;
						if (midi.weg <  iTemps37a)   // 5.0
						{
							audio.midistat += 1.0f;
							midi.midi_send = jack_midi_event_reserve(gx_jack::midi_port_buf, i, 3);

							if (midi.midi_send)
							{
								midi.midi_send[2] = (int)iTemps26; // velocity
								midi.midi_send[1] = 123;  // fix me all notes off
								midi.midi_send[0] = 0xB0 | (int)iTemps30 ;	// controller
							}

							if (midi.fcheckbox10)
							{
								audio.midistat += 1.0f;
								midi.midi_send1 = jack_midi_event_reserve(gx_jack::midi_port_buf, i, 3);

								if (midi.midi_send1)
								{
									midi.midi_send1[2] = (int)iTemps32; // velocity
									midi.midi_send1[1] = 123; // fix me all notes off
									midi.midi_send1[0] = 0xB0 |  (int)iTemps35;	// controller
									//fprintf(stderr, "Send %i , %i, %i.\n",iTemps32,123,0xB0 |  iTemps35);
								}
							}

							if (midi.fcheckbox11)
							{
								audio.midistat += 1.0f;
								midi.midi_send2 = jack_midi_event_reserve(gx_jack::midi_port_buf, i, 3);

								if (midi.midi_send2)
								{
									midi.midi_send2[2] = (int)iTemps40; // velocity
									midi.midi_send2[1] =  123;  // fix me all notes off
									midi.midi_send2[0] = 0xB0 |  (int)iTemps44;	// controller
								}
							}
							audio.midistat = 0.0f;
							audio.midistat1 = audio.midistat2 = audio.midistat3 = false;
						}
					}
					midi.weg+=step;
				
			}

		}
	}
}

} /* end of gx_engine namespace */
