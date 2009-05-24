/******************************************************************************
*******************************************************************************

								FAUST DSP
	dsp_midi.cpp
	the dsp_midi processing for guitarix
*******************************************************************************
*******************************************************************************/

virtual void compute_midi( int len)
{
    TBeatDetector myTBeatDetector;


    float 	fConsta2 = 0;
    int preNote = 0;
    float fTemps45 = fslider45;
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
    double stepper = 1./step;
    int iTemps37  = int(fSamplingFreq/fslider37);
    int iTemps37a  = iTemps37+20;
    float fTemps38 = fslider38;
    float rms = 0;
    float midi_db = 0;
    int iTemps46 = int(fslider46);
    int iTemps47 = int(fslider47);
    int iTemps48 = int(fslider48);
    int piwe = 0;
    int cs = 0;
    int sum = 0;
    float *audiodata = checkfreq;

    if ((shownote == 1) || (playmidi == 1))
    {
        for (int i=0; i<len; i+=step)
        {

            midi_db = (log(fabs(audiodata[i]))*fConstlog2);
            beat0 = 254- floor(exp(fConstlog*midi_db)*127);
            rms = beat0;

            if (( beat0 >= fTemps45) && (cpu_load < 65.0))
            {

                if (cs == int(fConstun0*stepper))
                {
                    cs = 0;
                    sum = 0;
                }
                else
                {
                    cs += 1;
                    sum += sqr(rms);
                }
                beat0 = sqrt(sum/cs);

                fConsta1 = 12 * log2f(2.272727e-03f *  fConsta4);
                preNote = round(fConsta1)+57;
                fConsta2 = fConsta1 - (preNote - 57);
                piwe = (fConsta2+1) * 8192; // pitch wheel value
                weg = 0;

                if (playmidi == 1)
                {
                    // channel0
                    if (program != iTemps31)
                    {
                        program = iTemps31;
                        midistat += 1.0f;
                        midi_send = jack_midi_event_reserve(midi_port_buf, i, 2);
                        if (midi_send)
                        {
                            midi_send[1] =  iTemps31;  // program value
                            midi_send[0] = 0xC0 | iTemps30;  // controller+ channel
                        }
                    }
                    if (send > iTemps27)   //20
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
                            midi_send = jack_midi_event_reserve(midi_port_buf, i, 3);
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
                                midi_send = jack_midi_event_reserve(midi_port_buf, i, 3);
                                if (midi_send)
                                {
                                    midi_send[2] =  0x40;  // pitch value
                                    midi_send[1] = 0x00 ; // pitch value
                                    midi_send[0] = 0xE0 |  iTemps30; // controller + channel
                                }
                            }
                            midi_send = jack_midi_event_reserve(midi_port_buf, i, 3);
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
                                midi_send = jack_midi_event_reserve(midi_port_buf, i, 3);
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
                    if (fcheckbox10 == 1.0)
                    {
                        if (program1 != iTemps36)
                        {
                            program1 = iTemps36;
                            midistat += 1.0f;
                            midi_send1 = jack_midi_event_reserve(midi_port_buf, i, 2);
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
                                midi_send1 = jack_midi_event_reserve(midi_port_buf, i, 3);
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
                                    midi_send1 = jack_midi_event_reserve(midi_port_buf, i, 3);
                                    if (midi_send1)
                                    {
                                        midi_send1[2] =  0x40;  // pitch value
                                        midi_send1[1] = 0x00 ; // pitch value
                                        midi_send1[0] = 0xE0 |  iTemps35;  // controller + channel
                                    }
                                }
                                midi_send1 = jack_midi_event_reserve(midi_port_buf, i, 3);
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
                                    midi_send1 = jack_midi_event_reserve(midi_port_buf, i, 3);
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
                    if (fcheckbox11 == 1.0)
                    {
                        if (program2 != iTemps43)
                        {
                            program2 = iTemps43;
                            midistat += 1.0f;
                            midi_send2 = jack_midi_event_reserve(midi_port_buf, i, 2);
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
                                midi_send2 = jack_midi_event_reserve(midi_port_buf, i, 3);
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
                                midi_send2 = jack_midi_event_reserve(midi_port_buf, i, 3);
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
                                midi_send2 = jack_midi_event_reserve(midi_port_buf, i, 3);
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
                                    midi_send2 = jack_midi_event_reserve(midi_port_buf, i, 3);
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
                    myTBeatDetector.setSampleRate (fSamplingFreq);
                    myTBeatDetector.AudioProcess (beat0,  fTemps38);
                    if (myTBeatDetector.BeatPulse == TRUE)
                    {
                        send+=step;
                        if (fcheckbox10 == 1.0) send1+=step;
                        if (fcheckbox11 == 1.0) send2+=step;
                    }
                }
                // end if playmidi = 1
            }
            else
            {
                if  (playmidi == 1)
                {
                    if ((weg > iTemps37) || (cpu_load > 64.0))
                    {
                        if (weg <  iTemps37a)  // 5.0
                        {
                            midistat += 1.0f;
                            midi_send = jack_midi_event_reserve(midi_port_buf, i, 3);
                            if (midi_send)
                            {
                                midi_send[2] = iTemps26; // velocity
                                midi_send[1] = 123;  // all notes off
                                midi_send[0] = 0xB0 | iTemps30 ;	// controller
                            }
                            if (fcheckbox10 == 1.0)
                            {
                                midistat += 1.0f;
                                midi_send1 = jack_midi_event_reserve(midi_port_buf, i, 3);
                                if (midi_send1)
                                {
                                    midi_send1[2] = iTemps32; // velocity
                                    midi_send1[1] = 123;  // all notes off
                                    midi_send1[0] = 0xB0 |  iTemps35;	// controller
                                }
                            }
                            if (fcheckbox11 == 1.0)
                            {
                                midistat += 1.0f;
                                midi_send2 = jack_midi_event_reserve(midi_port_buf, i, 3);
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
                if (shownote == 1)
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
