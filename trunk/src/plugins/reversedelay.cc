#include "gx_plugin.h"
#include <cmath>
#include <stdlib.h>	

namespace pluginlib {
namespace reversedelay {

#define N_(x) (x)

class ReverseDelay : public PluginDef {
private:
    float sample_rate;
    float *buffer;
    unsigned int counter;
   	unsigned int buf_size;
    
    unsigned int cur_buf_size; 
	float feedback_buf;

    //Params
    float time, feedback, window, drywet;
	//Params buffs
	float time_old, window_old;

    //Indicator
    float buf_indication;

	class overlap_window
	{
	private:
		float val;
		float step;
		float acc;
		unsigned int active_samples;
		unsigned int full_samples;
		unsigned int counter;

	public:
		overlap_window() {
		    val = 0;
		    step = 0;
		    acc = 0;
		    active_samples = 0;
		    full_samples = 0;
		    counter = 0;
		}
		void set_coef(float t /* 0..1 */, unsigned int full_samples) {
		    set_full(0, full_samples, t*full_samples);
		}
		bool set_full(float min_val, unsigned int full_samples, unsigned int active_samples) {
		    if(active_samples >= full_samples) return false;

		    acc = min_val;
		    val = min_val;
		    this->full_samples = full_samples;
		    this->active_samples = active_samples;
		    counter = 0;
		    step = (1 - min_val)/(active_samples/2);

		    return true;
		}
		float get() {
		    if(counter >= 0 && counter < active_samples/2) {
		        acc += step;
		        counter++;
		        return acc;
		    }
		    else if(counter >= active_samples/2 && counter <= full_samples - active_samples/2) {
		        counter++;
		        return 1;
		    }
		    else if(counter > full_samples - active_samples/2 && counter < full_samples) {
		        acc -= step;
		        counter++;
		        return acc;
		    }
		    else if(counter >= full_samples) {
		        float ret_val = acc;
		        acc = val;
		        counter = 0;
		        return ret_val;
		    }
		    return 1;
		}
	};	

	overlap_window ow;

	static float reverse_delay_line_impl(float in, float* buf, unsigned int* counter, unsigned int length)
	{
		float out = 0;

		//Read data
		if(*counter < length - 1)
		{
		    unsigned int read_counter = length - 1 - (*counter);
		    out = buf[read_counter];
		}

		//Write data
		*(buf + (*counter)) = in;
		(*counter)++;
		if ((*counter) > length-1)
		    (*counter) = 0;

		return (out);
	}

public:
    ReverseDelay();
    static void init(unsigned int samplingFreq, PluginDef *plugin);
    static void process(int count, float *input, float *output, PluginDef *plugin);
    static int registerparam(const ParamReg& reg);
    static int uiloader(const UiBuilder& builder, int form);
    static void del_instance(PluginDef *plugin);
};

ReverseDelay::ReverseDelay():
    PluginDef(),
    sample_rate(0) {
    version = PLUGINDEF_VERSION;
    id = "reversedelay";
    name = N_("ReverseDelay");
    category = N_("Echo / Delay");
    mono_audio = process;
    set_samplerate = init;
    register_params = registerparam;
    load_ui = uiloader;
    delete_instance = del_instance;

    buffer = NULL;
    counter = 0;
    buf_size    = 0;
    cur_buf_size = 0;
    feedback_buf = 0;
	time_old = 0; 
	window_old = 0;

    buf_indication = 0;
}

int ReverseDelay::registerparam(const ParamReg& reg) {
    ReverseDelay& self = *static_cast<ReverseDelay*>(reg.plugin);
    reg.registerVar("reversedelay.time", N_("Time (ms)"), "S", N_("Delay time in milliseconds"), &self.time, 500, 200, 2000, 1);
    reg.registerVar("reversedelay.feedback", N_("Feedback"), "S", N_("Feedback"), &self.feedback, 0, 0, 1, 0.05);
    reg.registerVar("reversedelay.window", N_("Window (%)"), "S", N_("Crossfade between delayed chunks in percents"), &self.window, 50, 0, 100, 1);
    reg.registerVar("reversedelay.drywet", N_("Dry/Wet"), "S", "Dey/Wet", &self.drywet, 0.5, 0, 1, 0.05);

    reg.registerNonMidiFloatVar("reversedelay.buf_indication",&self.buf_indication, false, true, 0.0, 0.0, 1.0, 0.01);

    return 0;
}

void ReverseDelay::init(unsigned int samplingFreq, PluginDef *plugin) {
	ReverseDelay& self = *static_cast<ReverseDelay*>(plugin);
    self.sample_rate = samplingFreq;

	float* old_buf = self.buffer;

	//Provide dual buf size, with 2 seconds length for every part
	unsigned int new_buf_size = (unsigned int)(samplingFreq * 2 * 2);

	float *new_buf = new float[new_buf_size];
	for (size_t i = 0; i < new_buf_size; i++)
		new_buf[i] = 0.0f;

	// Assign new pointer and size
	self.buffer         = new_buf;
	self.buf_size       = new_buf_size;

	// Delete old buffer
	if (old_buf != NULL)
		delete [] old_buf;
}

void ReverseDelay::process(int count, float *input, float *output, PluginDef *plugin) {
    ReverseDelay& self = *static_cast<ReverseDelay*>(plugin);

    //Update params
	if(self.time_old != self.time) {
		self.cur_buf_size = (self.time/1000.0)*self.sample_rate;
		self.counter = 0;
		self.ow.set_coef((self.window)/(100.0 + 1.0), self.cur_buf_size/2); //Avoid to pass 1

		self.time_old = self.time;
		self.window_old = self.window;
	}
	else if(self.window_old != self.window)
	{ 
    	self.ow.set_coef((self.window)/(100.0 + 1.0), self.cur_buf_size/2); 
		self.window_old = self.window;
	}

    for (int i = 0; i < count; ++i) {
        float in = input[i];
        float out = 0;

        //Update indicator
        self.buf_indication = ((float)self.counter)/self.cur_buf_size;

        //Process
        out = reverse_delay_line_impl(in + self.feedback_buf * self.feedback, self.buffer, &self.counter, self.cur_buf_size);
        self.feedback_buf = out;

        out*= self.ow.get();

        out = out* self.drywet + in* (1 - self.drywet);
        output[i] = out;
    }
}

int ReverseDelay::uiloader(const UiBuilder& b, int form) {
    if (!(form & UI_FORM_STACK)) {
    return -1;
    }
    b.openHorizontalhideBox("");
    {
        b.create_master_slider("reversedelay.drywet",0);
    }
    b.closeBox();
    b.openHorizontalBox("");
    {
		b.create_small_rackknob("reversedelay.time",0);

        b.openVerticalBox("");
        b.insertSpacer();
        b.create_port_display("reversedelay.buf_indication", "Buf state");
        b.insertSpacer();
        b.closeBox();

        b.create_small_rackknob("reversedelay.feedback",0);
		b.create_small_rackknob("reversedelay.window",0);
		b.create_small_rackknobr("reversedelay.drywet",0);

    }
    b.closeBox();
    return 0;
}

void ReverseDelay::del_instance(PluginDef *plugin)
{ 
	ReverseDelay& self = *static_cast<ReverseDelay*>(plugin);
	delete [] self.buffer;
    delete static_cast<ReverseDelay*>(plugin);
}


#if true

PluginDef *plugin() {
    return new ReverseDelay;
}

#else

extern "C" __attribute__ ((visibility ("default"))) int
get_gx_plugin(unsigned int idx, PluginDef **pplugin)
{
    const int count = 1;
    if (!pplugin) {
    return count;
    }
    switch (idx) {
    case 0: *pplugin = new ReverseDelay; return count;
    default: *pplugin = 0; return -1;
    }
}

#endif

} // end namespace reverse_delay
} // end namespace pluginlib
