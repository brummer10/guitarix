namespace barkgraphiceq {

#include "bark_freq_grid.h"

#include <iostream>

class Dsp: public PluginLV2 {
private:
	int fSamplingFreq;

	//First elements in both arrays are common gains
	float* fslider[BARK_NUMBER_OF_BANDS]; 
	float* fbargraph[BARK_NUMBER_OF_BANDS];
	//EQ's, first used for indication, second - for audio signal processing
	orfanidis_eq::eq1* p_eq1;
	orfanidis_eq::eq2* p_eq2;
	
	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(uint32_t samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(uint32_t samplingFreq, PluginLV2*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);

public:
	Dsp();
	~Dsp();
};

Dsp::Dsp()
	: PluginLV2() {
	
	version = PLUGINLV2_VERSION;
	id = "barkgraphiceq";
	name = N_("Bark Grid EQ");
	mono_audio = compute_static;
	stereo_audio = 0;
	set_samplerate = init_static;
	activate_plugin = 0;
	connect_ports = connect_static;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
	
	p_eq1 = NULL;
	p_eq2 = NULL;
	
	clear_state_f();

}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for(unsigned int i = 0; i < BARK_NUMBER_OF_BANDS; i++)
	{
		fslider[i] = 0; 
		fbargraph[i] = 0;
	}
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	
	orfanidis_eq::freq_grid fg;
	
	//Apply Bark frequency grid
	for (unsigned int i = 0; i < BARK_NUMBER_OF_BANDS; i++)
		fg.add_band(bark_center_freqs[i], bark_bands_widths[i]);
		
	//Create Butterworth EQ object's
	p_eq1 = new orfanidis_eq::eq1(fg, orfanidis_eq::butterworth);
	p_eq2 = new orfanidis_eq::eq2(fg, orfanidis_eq::butterworth);
	
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	//Set params
	for(unsigned int j = 0; j < BARK_NUMBER_OF_BANDS; j++) {
		p_eq1->change_band_gain_db(j, *fslider[j]);
		p_eq2->change_band_gain_db(j, *fslider[j]);
	}
	
	//Process audio
	double aver_out = 0;
	for (int i=0; i<count; i++) {
		double input = input0[i];	
		double out = 0;
		p_eq2->sbs_process(&input, &out);
		output0[i] = out;
		aver_out += out*out;
	}
	
	//Update bars
	for(unsigned int j = 0; j < BARK_NUMBER_OF_BANDS; j++) {
		double input = aver_out/count;
		double band_out = 0;
		p_eq1->sbs_process_band(j, &input, &band_out);
		*fbargraph[j] = BARK_NUMBER_OF_BANDS*band_out;				
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case G1: 
		fslider[0] = (float*)data;   
		break;
	case G2: 
		fslider[1] = (float*)data;   
		break;
	case G3: 
		fslider[2] = (float*)data; 
		break;
	case G4: 
		fslider[3] = (float*)data;   
		break;
	case G5: 
		fslider[4] = (float*)data;   
		break;
	case G6: 
		fslider[5] = (float*)data;   
		break;
	case G7: 
		fslider[6] = (float*)data;   
		break;
	case G8: 
		fslider[7] = (float*)data;   
		break;
	case G9: 
		fslider[8] = (float*)data;   
		break;
	case G10: 
		fslider[9] = (float*)data;   
		break;
	case G11: 
		fslider[10] = (float*)data;   
		break;
	case G12: 
		fslider[11] = (float*)data;   
		break;
	case G13: 
		fslider[12] = (float*)data;   
		break;
	case G14: 
		fslider[13] = (float*)data;   
		break;
	case G15: 
		fslider[14] = (float*)data;   
		break;
	case G16: 
		fslider[15] = (float*)data;   
		break;
	case G17: 
		fslider[16] = (float*)data;   
		break;
	case G18: 
		fslider[17] = (float*)data;   
		break;
	case G19: 
		fslider[18] = (float*)data;   
		break;
	case G20: 
		fslider[19] = (float*)data;   
		break;
	case G21: 
		fslider[20] = (float*)data;   
		break;
	case G22: 
		fslider[21] = (float*)data;   
		break;
	case G23: 
		fslider[22] = (float*)data;   
		break;
	case G24: 
		fslider[23] = (float*)data;   
		break;

	case V1: 
		fbargraph[0] = (float*)data;  
		break;
	case V2: 
		fbargraph[1] = (float*)data;  
		break;
	case V3: 
		fbargraph[2] = (float*)data;  
		break;
	case V4: 
		fbargraph[3] = (float*)data;  
		break;
	case V5: 
		fbargraph[4] = (float*)data;  
		break;
	case V6: 
		fbargraph[5] = (float*)data;  
		break;
	case V7: 
		fbargraph[6] = (float*)data;  
		break;
	case V8: 
		fbargraph[7] = (float*)data;  
		break;
	case V9: 
		fbargraph[8] = (float*)data;  
		break;
	case V10: 
		fbargraph[9] = (float*)data;  
		break;
	case V11: 
		fbargraph[10] = (float*)data;  
		break;
	case V12: 
		fbargraph[11] = (float*)data;  
		break;
	case V13: 
		fbargraph[12] = (float*)data;  
		break;
	case V14: 
		fbargraph[13] = (float*)data;  
		break;
	case V15: 
		fbargraph[14] = (float*)data;  
		break;
	case V16: 
		fbargraph[15] = (float*)data;  
		break;
	case V17: 
		fbargraph[16] = (float*)data;  
		break;
	case V18: 
		fbargraph[17] = (float*)data;  
		break;
	case V19: 
		fbargraph[18] = (float*)data;  
		break;
	case V20: 
		fbargraph[19] = (float*)data;  
		break;
	case V21: 
		fbargraph[20] = (float*)data;  
		break;
	case V22: 
		fbargraph[21] = (float*)data;  
		break;
	case V23: 
		fbargraph[22] = (float*)data;  
		break;
	case V24: 
		fbargraph[23] = (float*)data;  
		break;

	default:
		break;
	}
}

void Dsp::connect_static(uint32_t port,void* data, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->connect(port, data);
}

PluginLV2 *plugin() {
	return new Dsp();
}

void Dsp::del_instance(PluginLV2 *p)
{
	//Delete eq's
	delete static_cast<Dsp*>(p)->p_eq1;
	delete static_cast<Dsp*>(p)->p_eq2;
	delete static_cast<Dsp*>(p);
}

} // end namespace barkgraphiceq

