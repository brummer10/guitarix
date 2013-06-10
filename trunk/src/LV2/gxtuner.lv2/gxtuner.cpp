/*
 * Copyright (C) 2012 Hermann Meyer, Andreas Degert, Pete Shorthose, Steve Poskitt
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


////////////////////////////// LOCAL INCLUDES //////////////////////////
#include <glibmm.h>
#include "gx_common.h"      // faust support and denormal protection (SSE)

/****************************************************************
 ** "atomic" value access
 */

inline void atomic_set(volatile int32_t* p, int32_t v)
{
  g_atomic_int_set(p, v);
}

inline int32_t atomic_get(volatile int32_t& p)
{
  return g_atomic_int_get(&p);
}

inline bool atomic_compare_and_exchange(volatile int32_t *p, int32_t oldv, int32_t newv)
{
  return g_atomic_int_compare_and_exchange(p, oldv, newv);
}

template <class T>
inline void atomic_set(T **p, T *v)
{
  g_atomic_pointer_set(p, v);
}

template <class T>
inline void atomic_set_0(T **p)
{
  g_atomic_pointer_set(p, 0);
}

template <class T>
inline T *atomic_get(T*& p)
{
  return static_cast<T*>(g_atomic_pointer_get(&p));
}

template <class T>
inline bool atomic_compare_and_exchange(T **p, T *oldv, T *newv)
{
  return g_atomic_pointer_compare_and_exchange(reinterpret_cast<void* volatile*>(p), oldv, newv);
}



#include "gxtuner.h"        // define struct PortIndex
#include "gx_pluginlv2.h"   // define struct PluginLV2
#include "gx_resampler.h"
#include "tuner.cc"
#include "low_high_cut.cc"
#include "gx_pitch_tracker.cpp"
#include "gx_vumeter.cc"
#include "uniBar.cc"


////////////////////////////// PLUG-IN CLASS ///////////////////////////

class Gxtuner
{
protected:
  // MIDI stuff
  int                          midi_event;
  LV2_Event_Buffer             *MidiOut;
  LV2_Event_Iterator           out_iter;
  uint8_t                      note;
  float                        fnote;
  uint8_t                      lastnote;
  float                        level;
  float                        nolevel;
  float                        *nolevel_;
  float                        fallback;
  uint8_t                      midi_data[3];
  bool                         noteoff;
  float                        *channel_;
  uint8_t                      channel;
  uint8_t                      prevchannel;
  float                        *playmidi_;
  float                        playmidi;
  float                        fastnote;
  float*                       fastnote_;
  float*                       sendpich_;
  float                        sendpich;
  float*                       singlenote_;
  float*                       velocity_;
  float*                       verify_;
  float                        verify;
  float*                       gate_;
  float*                       gain_;
  float*                       synthfreq_;
  uint8_t                      velocity;
  float*                       ref_pitch;
  uint32_t                     w;
    // internal stuff
  float*                       output;
  float*                       input;
  float*                       freq;
  float                        threshold;
  float*                       threshold_;
  uint32_t                     frames_period;
  uint32_t                     sample_period;
  float*                       bpm_;
  float                        bpm;
  uint32_t                     count_frame;
  bool                         play;
  PluginLV2*                   tuner_adapter;
  PluginLV2*                   vu_adapter;
  PluginLV2*                   lhcut;
  PluginLV2*                   bow;
  float*                       allowed_notes[60];

private:
  inline void run_dsp_mono(uint32_t n_samples);
  inline void connect_mono(uint32_t port,void* data);
  inline void init_dsp_mono(uint32_t rate);
  inline void connect_all_mono_ports(uint32_t port, void* data);
  inline void activate_f();
  inline void deactivate_f();
  inline void clean_up();
  inline void play_midi(tuner& self);
  inline void send_midi_data(int count, uint8_t controller ,
                             uint8_t note, uint8_t velocity);

  void                         freq_changed_handler(); 
  inline bool                  verify_freq(float newf, float old);
  volatile int32_t             note_verified;
  float                        freq_old;
  float                        freq_new;
  uint32_t                     verifielevel;

public:
  // LV2 Descriptor
  static const LV2_Descriptor descriptor;
  // static wrapper to private functions
  static void deactivate(LV2_Handle instance);
  static void cleanup(LV2_Handle instance);
  static void run(LV2_Handle instance, uint32_t n_samples);
  static void activate(LV2_Handle instance);
  static void connect_port(LV2_Handle instance, uint32_t port, void* data);
  static LV2_Handle instantiate(const LV2_Descriptor* descriptor,
                                double rate, const char* bundle_path,
                                const LV2_Feature* const* features);
  Gxtuner();
  ~Gxtuner();
};

// constructor
Gxtuner::Gxtuner() :
  midi_event(0),
  MidiOut(NULL),
  note(0),
  lastnote(0),
  level(0),
  nolevel(0),
  nolevel_(NULL),
  fallback(0),
  noteoff(false),
  channel_(NULL),
  channel(0),
  prevchannel(0),
  playmidi_(NULL),
  fastnote(0),
  fastnote_(NULL),
  output(NULL),
  input(NULL),
  tuner_adapter(plugin()),
  vu_adapter(vu_plugin()),
  lhcut(low_high_cut::plugin()),
  bow(uniBar::plugin())
  {
    for(uint8_t i = 0; i<60;i++) allowed_notes[i]=NULL;
    atomic_set(&note_verified,0);
  };

// destructor
Gxtuner::~Gxtuner()
{
  // just to be sure the plug have given free the allocated mem
  // it didn't hurd if the mem is already given free by clean_up()
  if (tuner_adapter->activate_plugin !=0)
    tuner_adapter->activate_plugin(false, tuner_adapter);
  // delete DSP class
  tuner_adapter->delete_instance(tuner_adapter);
  vu_adapter->delete_instance(vu_adapter);
  lhcut->delete_instance(lhcut);
  bow->delete_instance(bow);
};

////////////////////////////// PRIVATE CLASS  FUNCTIONS ////////////////

inline bool Gxtuner::verify_freq(float newf, float old)
{
  bool back = false;
  float fvis = 12 * log2f(newf/(*(ref_pitch)));
  
  float scale = fabs(fvis-round(fvis)) ;
  //fprintf(stderr,"scale = %f , fvis = %f\n",scale,fvis);
  if (scale > 0.2) return back;
  if (fabs(newf - old) < 0.1) back = true;
  return back;
}

void Gxtuner::freq_changed_handler() 
{ 
  //freq_changed.signal();
  tuner& self = *static_cast<tuner*>(tuner_adapter);
  freq_new = self.get_freq(self);
  if (freq_new != 0 && verify_freq(freq_new, freq_old)) {
    verifielevel++;
    if(verifielevel>static_cast<uint32_t>(fastnote)+verify) {
      atomic_set(&note_verified,1);
      fnote = self.get_note(self);
     // *(synthfreq_) = self.get_freq(self);
      verifielevel =0;
      //fprintf(stderr,"NOTE VERIFIED \n");
    }
  } else {
    freq_old = freq_new;
    verifielevel =0;
    fnote = 1000;
    // fprintf(stderr,"NOTE NOT VERIFIED");
  }
  
}

void Gxtuner::send_midi_data(int count, uint8_t controller,
                             uint8_t note, uint8_t velocity)
{
  midi_data[0] = controller; // note on/off
  midi_data[1] = note; // note
  midi_data[2] = velocity; // velocity
  if(! MidiOut) return;
	if(!lv2_event_write(&out_iter, count, 0, midi_event, 3, midi_data)) {
		printf("Error! midi event fail!\n");
	} 
}

void Gxtuner::play_midi(tuner& self)
{
  MaxLevel& lev = *static_cast<MaxLevel*>(vu_adapter);
  lv2_event_begin(&out_iter,MidiOut);  
  //fnote = self.get_note(self);
  level = lev.get_midi_level(lev);
  nolevel = pow(10.,*(nolevel_)*0.05);
  count_frame++;
  if (count_frame >= frames_period) {
    count_frame = 0;
    play = true;
  } 
  //metronome
  if (play && bpm>0) {
    if (w<10) w++;  
    *(gain_) = 1;
    //if((*(gate_)<1))
    //  if((*(synthfreq_)<880) ? (*(synthfreq_)+=220) : (*(synthfreq_)=220));
    *(synthfreq_) = 220;
    if((*(gate_)>0) ? (*(gate_)=0) : (*(gate_)=1)) ;
    play = false;
  } 
  if ((fnote  < 999.) && (level > nolevel)  && atomic_get(note_verified)) {
    //play = false;
    atomic_set(&note_verified,0);
    note = static_cast<uint8_t>(round(fnote)+69);
    fallback = level;
    //fprintf(stderr,"note %i",note);
    if( note >= 24 && note <= 84 && note != lastnote &&
         *(allowed_notes[max(0,min(60,note-24))]) > 0) {
      channel = static_cast<uint8_t>(*(channel_));
      velocity = static_cast<uint8_t>(*(velocity_));
      sendpich = *(sendpich_);
      // clear pitchwheel
      if (sendpich > 0)
        send_midi_data(0, 0xE0| channel, 8192 & 127, (8192&16256) >> 7);
      // new note on
      send_midi_data(1, 0x90| channel, note, velocity);
      //*(gain_) = static_cast<float>(velocity)/127;
      //*(gate_) = 1;
      // send pitchwheel data
      if (sendpich > 0) {
        unsigned int pitch_wheel = 8192;
        float prepitch = fnote - (note - 57);
        if (prepitch>0){
		  pitch_wheel=8192+round(prepitch*8191);
	    } else {
		  pitch_wheel=8192+round(prepitch*8192);
	    }
        send_midi_data(2, 0xE0| channel, pitch_wheel & 127, (pitch_wheel&16256) >> 7);
      }
      // previus note off
      if (*(singlenote_)>0)
        send_midi_data(3, 0x80| channel,lastnote,velocity);
      lastnote = note;
      noteoff = true;
    } //else if(!play) *(gate_) = 0;
  } else if (((level+fallback) < (nolevel*0.1))&& noteoff) {
    // all note off
    send_midi_data(1, 0xB0| channel, 123, velocity);
    //if(!play) *(gate_) = 0;
    // clear pitch wheel
    if (sendpich > 0)
      send_midi_data(2, 0xE0| channel, 8192 & 127, (8192&16256) >> 7);
    lastnote = 0;
    noteoff = false;
  }
  if(noteoff) fallback *= 0.9;
  // when channel changed, send all note off to previus channel
  if (prevchannel !=channel) {
    send_midi_data(4, 0xB0| prevchannel, 123, velocity);
    // and clear pitch wheel
    if (sendpich > 0)
      send_midi_data(5, 0xE0| channel, 8192 & 127, (8192&16256) >> 7);
    prevchannel =channel;
  }
}

void Gxtuner::init_dsp_mono(uint32_t rate)
{
  AVOIDDENORMALS(); // init the SSE denormal protection
  sample_period = 60 * rate;
  tuner_adapter->set_samplerate(rate, tuner_adapter); // init the DSP class
  vu_adapter->set_samplerate(rate, vu_adapter);
  lhcut->set_samplerate(rate, lhcut);
  bow->set_samplerate(rate, bow);
  tuner& self = *static_cast<tuner*>(tuner_adapter);
  self.signal_freq_changed().connect(sigc::mem_fun(this, &Gxtuner::freq_changed_handler));
}

// connect the Ports used by the plug-in class
void Gxtuner::connect_mono(uint32_t port,void* data)
{
  if (port >=14 && port <=73) {
    allowed_notes[port-14] = static_cast<float*>(data);
    return;
  }
    
  switch ((PortIndex)port)
    {
    case FREQ: 
      freq = static_cast<float*>(data);
      break;
    case REFFREQ: 
      ref_pitch = static_cast<float*>(data);
      break;
    case THRESHOLD: 
      threshold_ = static_cast<float*>(data) ;
      break;
    case LEVEL: 
      nolevel_ = static_cast<float*>(data) ;
      break;
    case CHANNEL: 
      channel_ = static_cast<float*>(data) ;
      break;
    case ONMIDI:
      playmidi_ = static_cast<float*>(data) ;
      break;
    case FASTNOTE:
      fastnote_ = static_cast<float*>(data) ;
      break;
    case PITCHBEND:
      sendpich_ = static_cast<float*>(data) ;
      break;
    case SINGLENOTE:
      singlenote_ = static_cast<float*>(data) ;
      break;
    case BPM:
      bpm_ = static_cast<float*>(data) ;
      break;
    case VELOCITY:
      velocity_ = static_cast<float*>(data) ;
      break;
    case VERIFY:
      verify_ = static_cast<float*>(data) ;
      break;
    case GATE:
      gate_ = static_cast<float*>(data) ;
      break;
    case SYNTHFREQ:
      synthfreq_ = static_cast<float*>(data) ;
      break;
    case GAIN:
      gain_ = static_cast<float*>(data) ;
      break;
    case MIDIOUT: 
      MidiOut = static_cast<LV2_Event_Buffer*>(data) ;
      break;
    case EFFECTS_OUTPUT:
      output = static_cast<float*>(data);
      break;
    case EFFECTS_INPUT:
      input = static_cast<float*>(data);
      break;
    default:
      break;
    }
}

void Gxtuner::activate_f()
{
  // allocate the internal DSP mem
  if (tuner_adapter->activate_plugin !=0)
    tuner_adapter->activate_plugin(true, tuner_adapter);
}

void Gxtuner::clean_up()
{
  // delete the internal DSP mem
  if (tuner_adapter->activate_plugin !=0)
    tuner_adapter->activate_plugin(false, tuner_adapter);
}

void Gxtuner::deactivate_f()
{ 
  // delete the internal DSP mem
  if (tuner_adapter->activate_plugin !=0)
    tuner_adapter->activate_plugin(false, tuner_adapter);
}

void Gxtuner::run_dsp_mono(uint32_t n_samples)
{
  static uint32_t sample_set = sample_period/n_samples;
  if (fabs(bpm - *(bpm_))>0.1)
  {
    bpm = *(bpm_);
    if (bpm > 0) frames_period = sample_set/ bpm;
    else frames_period = 0;
  }
  vu_adapter->mono_audio(static_cast<int>(n_samples), input, input, vu_adapter);
  lhcut->mono_audio(static_cast<int>(n_samples), input, output, lhcut);
  tuner& self = *static_cast<tuner*>(tuner_adapter);
  if (fabs(threshold - *(threshold_))>0.1)
  {
    threshold = *(threshold_);
    self.set_threshold_level(self,threshold);
  }
  tuner_adapter->mono_audio(static_cast<int>(n_samples), output, output, tuner_adapter);
  *(freq) = self.get_freq(self);

  // MIDI
  if (fastnote != *(fastnote_)) {
    fastnote =  *(fastnote_);
    if (fastnote > 0) self.set_fast_note(self, true);
    else self.set_fast_note(self, false);
  }
  if (*(playmidi_) > 0) {
    verify = *(verify_);
    play_midi(self);
    bow->mono_audio(static_cast<int>(n_samples), input, output, bow);
    if (w<3) {
      memcpy(output, input, n_samples * sizeof(float));
    }
  } else memcpy(output, input, n_samples * sizeof(float));
}

void Gxtuner::connect_all_mono_ports(uint32_t port, void* data)
{
  // connect the Ports used by the plug-in class
  connect_mono(port,data); 
  // connect the Ports used by the DSP class
  vu_adapter->connect_ports(port, data, vu_adapter);
  bow->connect_ports(port, data, bow);
}

///////////////////////// STATIC CLASS  FUNCTIONS /////////////////////

LV2_Handle
Gxtuner::instantiate(const LV2_Descriptor*     descriptor,
            double                    rate,
            const char*               bundle_path,
            const LV2_Feature* const* features)
{
  // init the plug-in class
  Gxtuner *self = new Gxtuner();
  if (!self)
  {
    return NULL;
  }
  LV2_URI_Map_Feature *map_feature;
  for (int32_t i = 0; features[i]; ++i)
  {
    if (!strcmp(features[i]->URI, "http://lv2plug.in/ns/ext/uri-map")) 
    {
      map_feature = static_cast<LV2_URI_Map_Feature*>(features[i]->data);
      self->midi_event = map_feature->uri_to_id(map_feature->callback_data,
                                "http://lv2plug.in/ns/ext/event",
                                "http://lv2plug.in/ns/ext/midi#MidiEvent");
    }
  }
  if (self->midi_event == 0)
  {
    fprintf(stderr, "GxTuner: No MIDI Out support in host...\n");
  }

  self->init_dsp_mono((uint32_t)rate);
  return (LV2_Handle)self;
}

void Gxtuner::connect_port(LV2_Handle instance,
                                uint32_t   port,
                                void*      data)
{
  // connect all ports
  static_cast<Gxtuner*>(instance)->connect_all_mono_ports(port, data);
}

void Gxtuner::activate(LV2_Handle instance)
{
  // allocate needed mem
  static_cast<Gxtuner*>(instance)->activate_f();
}

void Gxtuner::run(LV2_Handle instance, uint32_t n_samples)
{
  // run dsp
  static_cast<Gxtuner*>(instance)->run_dsp_mono(n_samples);
}

void Gxtuner::deactivate(LV2_Handle instance)
{
  // free allocated mem
  static_cast<Gxtuner*>(instance)->deactivate_f();
}

void Gxtuner::cleanup(LV2_Handle instance)
{
  // well, clean up after us
  Gxtuner* self = static_cast<Gxtuner*>(instance);
  self->clean_up();
  delete self;
}

const LV2_Descriptor Gxtuner::descriptor =
{
  GXPLUGIN_URI "#tuner",
  instantiate,
  connect_port,
  activate,
  run,
  deactivate,
  cleanup,
  NULL
};

///////////////////////////// LV2 DESCRIPTOR ///////////////////////////

extern "C"
LV2_SYMBOL_EXPORT
const LV2_Descriptor*
lv2_descriptor(uint32_t index)
{
  switch (index)
    {
    case 0:
      return &Gxtuner::descriptor;
    default:
      return NULL;
    }
}

///////////////////////////// FIN //////////////////////////////////////
