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
#include <assert.h>
#include <cstring>
#include <list>
#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <fstream>

#include <cmath>
#include <gtk/gtk.h>
#include <jack/midiport.h>
#include <sndfile.h>
using namespace std;

#include "guitarix.h"

namespace gx_engine
{

//----- jack process callback for the midi input
void GxEngine::compute_midi_in(void* midi_input_port_buf)
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

void GxEngine::compute_midi(int len)
{

	// retrieve engine state
	const GxEngineState estate = (GxEngineState)checky;

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
void GxEngine::process_midi(int len)
{

	float 	fConsta2 = 0;
	float fTemps45 = fslider45;
	float fTemps38 = fslider38;
	float rms = 0;
	float midi_db = 0;
	float sum = 0;
	float fnote = 0;
	float *audiodata = checkfreq;

	int preNote = 0;
	int iTemps31 = int(fslider31);
	int iTemps30 = int(fslider30);
	int iTemps27 = int(fslider27);
	int iTemps29 = int(fslider29)*12;
	int iTemps26 = int(fslider26);
	int iTemps36 = int(fslider36);
	int iTemps35 = int(fslider35);
	int iTemps33 = int(fslider33);
	int iTemps34 = int(fslider34)*12;
	int iTemps32 = int(fslider32);
	int iTemps43 = int(fslider43);
	int iTemps44 = int(fslider44);
	int iTemps41 = int(fslider41);
	int iTemps42 = int(fslider42)*12;
	int iTemps40 = int(fslider40);
	int step = fslider39;
	int iTemps37  = int(48000/fslider37);
	int iTemps37a  = iTemps37+20;
	int iTemps46 = int(fslider46);
	int iTemps47 = int(fslider47);
	int iTemps48 = int(fslider48);
	int piwe = 0;
	int cs = 0;

	double stepper = 1./step;

	//----- only run it when midi out or tuner is enabled
	if ((gx_gui::shownote == 1) || (dsp::isMidiOn() == true))
	{
		/**fConsta4 is the frequence value from the actuell frame, here we
		   calculate the Note from the freq by log2(freq/440)*12
		   the result is the Note (as float) related to the note "A"
		   To smoth the output we mix the last detected frequence (from the last frame)
		   in by 1/1.
		   preNote contains the next posible Note, related by round float to int.
		   piwe contain the pitchweel value witch show the diff beetween the detected Note and
		   the real Note by frequency.
		**/
		fnote = 12 * log2f(2.272727e-03f *  (cache_note + fConsta4)*0.5);
		cache_note = fConsta4;
		preNote = round(fnote)+57;
		fConsta2 = fnote - (preNote - 57);
		piwe = (fConsta2+1) * 8192; // pitch wheel value
		// preNote = round(fConsta1t)+57;
		// weg = 0;


		for (int i=0; i<len; i+=step)
		{
			float audio_db = *audiodata++;
			if(audio_db > 0.00001)
			{
				//----- convert the audio gain to midi gain value
				midi_db = (log(fabs(audio_db))*fConstlog2);
				beat0 = 254- floor(exp(fConstlog*midi_db)*127)+ midi_gain;
				rms = beat0 ;
			}
			//----- check gain value and run only when gain is higher then the selected value
			if (( beat0 >= fTemps45) && (gx_jack::jcpu_load < 65.0))
			{

				//----- rms the gain for a smother output
				if (cs == int(fConstun0*stepper))
				{
					cs = 0;
					sum = 0;
				}
				else
				{
					cs += 1;
					sum += sqrf(rms);
				}

				beat0 = sqrtf(sum/cs);
				//set the value for the tuner
				fConsta1 = fnote;
				//set timeout for tuner fallback
				weg = 0;




				//----- start the midi output
				if (dsp::isMidiOn() == true)
				{
					// channel0
					if (program != iTemps31)
					{
						program = iTemps31;
						midistat += 1.0f;
						midi_send = jack_midi_event_reserve(gx_jack::midi_port_buf, i, 2);

						if (midi_send)
						{
							midi_send[1] =  iTemps31;  // program value
							midi_send[0] = 0xC0 | iTemps30;  // controller+ channel
						}
					}

					if (send > iTemps27)     //20
					{
						if (int(fautogain) == 1)
						{
							iTemps46 = beat0;
							if ( iTemps46 < 0) iTemps46 = 0;
							else if ( iTemps46 > 127) iTemps46 = 127;
							fslider46 = iTemps46;
						}
						if (volume != iTemps46)
						{
							volume = iTemps46;
							midistat += 1.0f;
							midi_send = jack_midi_event_reserve(gx_jack::midi_port_buf, i, 3);

							if (midi_send)
							{
								midi_send[2] = iTemps46;	// volume value
								midi_send[1] =  0x07;     // set controler volume
								midi_send[0] = 0xB0 | iTemps30;  // controller + channel
							}
						}

						noten = preNote + iTemps29;
						send = 0;
						midistat += 1.0f;

						if (( noten>=0)&&(noten<=127))
						{
							// pitch wheel clear
							if (fpitch == 1.0)
							{
								midi_send = jack_midi_event_reserve(gx_jack::midi_port_buf, i, 3);
								if (midi_send)
								{
									midi_send[2] =  0x40;  // pitch value
									midi_send[1] = 0x00 ; // pitch value
									midi_send[0] = 0xE0 |  iTemps30; // controller + channel
								}
							}
							midi_send = jack_midi_event_reserve(gx_jack::midi_port_buf, i, 3);
							if (midi_send)
							{
								midi_send[2] = iTemps26; // velocity
								midi_send[1] = noten ; // note
								midi_send[0] = 0x90 |  iTemps30;	// controller + channel
							}

							// pitch wheel set auto
							if (fpitch == 1.0)
							{
								if (piwe < 0) piwe = 0;
								if (fConsta2 > 0x3fff) piwe = 0x3fff;
								midi_send = jack_midi_event_reserve(gx_jack::midi_port_buf, i, 3);

								if (midi_send)
								{
									midi_send[2] = (piwe >> 7) & 0x7f;  // pitch
									midi_send[1] = piwe & 0x7f ; // pitch
									midi_send[0] = 0xE0 |  iTemps30; // controller + channel
								}
							}
						}
					}

					// channel1
					if (fcheckbox10)
					{
						if (program1 != iTemps36)
						{
							program1 = iTemps36;
							midistat += 1.0f;
							midi_send1 = jack_midi_event_reserve(gx_jack::midi_port_buf, i, 2);

							if (midi_send1)
							{
								midi_send1[1] = iTemps36;  // program value
								midi_send1[0] = 0xC0 | iTemps35; // controller+ channel
							}
						}

						if (send1 > iTemps33)
						{
							if (int(fautogain1) == 1)
							{
								iTemps47 = beat0;
								if ( iTemps47 < 0) iTemps47 = 0;
								else if ( iTemps47 > 127) iTemps47 = 127;

								fslider47 = iTemps47;
							}

							if (volume1 != iTemps47)
							{
								volume1 = iTemps47;
								midistat += 1.0f;
								midi_send1 = jack_midi_event_reserve(gx_jack::midi_port_buf, i, 3);
								if (midi_send1)
								{
									midi_send1[2] = iTemps47;  // volume value
									midi_send1[1] =  0x07; // set controler channel volume
									midi_send1[0] = 0xB0 | iTemps35; // controller + channel
								}
							}

							noten1 = preNote + iTemps34;
							send1 = 0;
							midistat += 1.0f;
							if ((noten1>=0)&&(noten1<=127))
							{
								// pitch wheel clear
								if (fpitch1 == 1.0)
								{
									midi_send1 = jack_midi_event_reserve(gx_jack::midi_port_buf, i, 3);
									if (midi_send1)
									{
										midi_send1[2] =  0x40;  // pitch value
										midi_send1[1] = 0x00 ; // pitch value
										midi_send1[0] = 0xE0 |  iTemps35;  // controller + channel
									}
								}
								midi_send1 = jack_midi_event_reserve(gx_jack::midi_port_buf, i, 3);

								if (midi_send1)
								{
									midi_send1[2] = iTemps32; // velocity
									midi_send1[1] = noten1; // note
									midi_send1[0] = 0x90 | iTemps35; // note on + channel
								}

								// pitch wheel set auto
								if (fpitch1 == 1.0)
								{
									if (piwe < 0) piwe = 0;
									if (fConsta2 > 0x3fff) piwe = 0x3fff;
									midi_send1 = jack_midi_event_reserve(gx_jack::midi_port_buf, i, 3);

									if (midi_send1)
									{
										midi_send1[2] = (piwe >> 7) & 0x7f;  // pitch
										midi_send1[1] = piwe & 0x7f ; // pitch
										midi_send1[0] = 0xE0 |  iTemps35; // controller + channel
									}
								}
							}
						}
					}

					if (fcheckbox11)
					{
						if (program2 != iTemps43)
						{
							program2 = iTemps43;
							midistat += 1.0f;
							midi_send2 = jack_midi_event_reserve(gx_jack::midi_port_buf, i, 2);

							if (midi_send2)
							{
								midi_send2[1] =  iTemps43;  // program value
								midi_send2[0] = 0xC0 | iTemps44; // controller
							}
						}

						if (send2 > iTemps41)   //20
						{
							if (int(fautogain2) == 1)
							{
								iTemps48 = beat0;
								if ( iTemps48 < 0) iTemps48 = 0;
								else if ( iTemps48 > 127) iTemps48 = 127;
								fslider48 = iTemps48;
							}

							if (volume2 != iTemps48)
							{
								volume2 = iTemps48;
								midistat += 1.0f;
								midi_send2 = jack_midi_event_reserve(gx_jack::midi_port_buf, i, 3);
								if (midi_send2)
								{
									midi_send2[2] = iTemps48;  // volume value
									midi_send2[1] =  0x07; // set controler channel volume
									midi_send2[0] = 0xB0 | iTemps44; // controller + channel
								}
							}

							// pitch wheel clear
							if (fpitch2 == 1.0)
							{
								midi_send2 = jack_midi_event_reserve(gx_jack::midi_port_buf, i, 3);
								if (midi_send2)
								{
									midi_send2[2] =  0x40;  // pitch value
									midi_send2[1] = 0x00 ; // pitch value
									midi_send2[0] = 0xE0 |  iTemps44;	// controller + channel
								}
							}

							noten2 = preNote + iTemps42;
							send2 = 0;
							midistat += 1.0f;

							if ((noten2>=0)&&(noten2<=127))
							{
								midi_send2 = jack_midi_event_reserve(gx_jack::midi_port_buf, i, 3);

								if (midi_send2)
								{
									midi_send2[2] = iTemps40; // velocity
									midi_send2[1] = noten2; //  note
									midi_send2[0] = 0x90 | iTemps44;  // note on + channel
								}

								// pitch wheel set auto
								if (fpitch2 == 1.0)
								{
									if (piwe < 0) piwe = 0;
									if (fConsta2 > 0x3fff) piwe = 0x3fff;
									midi_send2 = jack_midi_event_reserve(gx_jack::midi_port_buf, i, 3);
									if (midi_send2)
									{
										midi_send2[2] = (piwe >> 7) & 0x7f;  // pitch
										midi_send2[1] = piwe & 0x7f ; // pitch
										midi_send2[0] = 0xE0 |  iTemps44; // controller + channel
									}
								}
							}
						}
					}

					if ( rms >= (Beat_is + fTemps38))
					{
						// if (Beat_is < rms)Beat_is += 2;
						//Beat_is = rms;
						send+=step;
						if (fcheckbox10 ) send1+=step;
						if (fcheckbox11 ) send2+=step;
					}
					// else weg +=step;
				}

				// end if playmidi = 1
			}
			else
			{
				if  (dsp::isMidiOn() == true)
				{
					if ((weg > iTemps37) || (gx_jack::jcpu_load > 64.0))
					{
						send = send1 = send2 = 0;
						Beat_is = fTemps45;
						if (weg <  iTemps37a)   // 5.0
						{
							midistat += 1.0f;
							midi_send = jack_midi_event_reserve(gx_jack::midi_port_buf, i, 3);

							if (midi_send)
							{
								midi_send[2] = iTemps26; // velocity
								midi_send[1] = 123;  // all notes off
								midi_send[0] = 0xB0 | iTemps30 ;	// controller
							}

							if (fcheckbox10)
							{
								midistat += 1.0f;
								midi_send1 = jack_midi_event_reserve(gx_jack::midi_port_buf, i, 3);

								if (midi_send1)
								{
									midi_send1[2] = iTemps32; // velocity
									midi_send1[1] = 123;  // all notes off
									midi_send1[0] = 0xB0 |  iTemps35;	// controller
								}
							}

							if (fcheckbox11)
							{
								midistat += 1.0f;
								midi_send2 = jack_midi_event_reserve(gx_jack::midi_port_buf, i, 3);

								if (midi_send2)
								{
									midi_send2[2] = iTemps40; // velocity
									midi_send2[1] = 123;  // all notes off
									midi_send2[0] = 0xB0 |  iTemps44;	// controller
								}
							}
							midistat = 0.0f;
						}
					}
					weg+=step;
				}

				if (gx_gui::shownote == 1)
				{
					if (weg > (fSamplingFreq)/2)
					{
						fConsta1 = 2000.0f;
					}
					weg+=step;
				}
			}

		}
	}
};

} /* end of gx_engine namespace */
