// generated from file '../src/LV2/faust/gx_w20.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)


namespace gx_w20 {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec0[2];
	double 	fConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	double 	fConst9;
	double 	fConst10;
	double 	fConst11;
	double 	fConst12;
	double 	fConst13;
	double 	fConst14;
	double 	fConst15;
	double 	fConst16;
	double 	fConst17;
	double 	fConst18;
	double 	fConst19;
	double 	fConst20;
	double 	fConst21;
	double 	fConst22;
	double 	fConst23;
	double 	fConst24;
	double 	fConst25;
	double 	fConst26;
	double 	fConst27;
	double 	fConst28;
	double 	fConst29;
	double 	fConst30;
	double 	fConst31;
	double 	fConst32;
	double 	fRec1[6];
	double 	fConst33;
	double 	fConst34;
	double 	fConst35;
	double 	fConst36;
	double 	fConst37;
	double 	fConst38;
	double 	fConst39;
	double 	fConst40;
	double 	fConst41;
	double 	fConst42;
	double 	fConst43;
	double 	fConst44;
	double 	fConst45;
	double 	fConst46;
	double 	fConst47;
	double 	fConst48;
	double 	fConst49;
	double 	fConst50;
	double 	fConst51;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec2[2];
	double 	fConst52;

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
	id = "w20";
	name = N_("Westbury W-20");
	mono_audio = compute_static;
	stereo_audio = 0;
	set_samplerate = init_static;
	activate_plugin = 0;
	connect_ports = connect_static;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<6; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = double(min(1.92e+05, max(1.0, (double)fSamplingFreq)));
	fConst1 = (1.0280271958907e-23 * fConst0);
	fConst2 = (1.35597773823241e-35 + (fConst0 * ((fConst0 * ((fConst0 * (0 - (8.36540868501136e-22 + fConst1))) - 1.56385834712324e-20)) - 5.19795592422045e-25)));
	fConst3 = (9.92905276020348e-24 * fConst0);
	fConst4 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst3 - 4.34163177403255e-21)) - 4.02016257201554e-19)) - 7.81929125002698e-18)) - 2.59898185626912e-22);
	fConst5 = (3.51219198703525e-25 * fConst0);
	fConst6 = (1.29949000095383e-18 + (fConst0 * (3.90964617079412e-14 + (fConst0 * (2.1817595880033e-15 + (fConst0 * (3.04912223958481e-17 + (fConst0 * (5.83356284305863e-20 + fConst5)))))))));
	fConst7 = (4.25008767113306e-21 * fConst0);
	fConst8 = (1.20590256422748e-34 + (fConst0 * (6.76918055130131e-24 + (fConst0 * (fConst7 - 6.43954751474457e-20)))));
	fConst9 = (8.4212352539407e-21 + (fConst0 * ((fConst0 * (2.1314833830679e-17 - fConst7)) - 3.21977374686867e-16)));
	fConst10 = (1.33767398764352e-28 * fConst0);
	fConst11 = ((fConst0 * (3.1080196209939e-20 + (fConst0 * (fConst10 - 8.4883795584658e-24)))) - 1.15566670466208e-17);
	fConst12 = ((fConst0 * ((fConst0 * (1.56385834712324e-20 + (fConst0 * (fConst1 - 8.36540868501136e-22)))) - 5.19795592422045e-25)) - 1.35597773823241e-35);
	fConst13 = (2.59898185626912e-22 + (fConst0 * ((fConst0 * (4.02016257201554e-19 + (fConst0 * (0 - (4.34163177403255e-21 + fConst3))))) - 7.81929125002698e-18)));
	fConst14 = (1.29949000095383e-18 + (fConst0 * ((fConst0 * (2.1817595880033e-15 + (fConst0 * ((fConst0 * (5.83356284305863e-20 - fConst5)) - 3.04912223958481e-17)))) - 3.90964617079412e-14)));
	fConst15 = (5.1401359794535e-23 * fConst0);
	fConst16 = ((fConst0 * ((fConst0 * ((fConst0 * (2.50962260550341e-21 - fConst15)) - 1.56385834712324e-20)) - 5.19795592422045e-25)) - 4.06793321469724e-35);
	fConst17 = (4.96452638010174e-23 * fConst0);
	fConst18 = (7.79694556880737e-22 + (fConst0 * ((fConst0 * ((fConst0 * (1.30248953220977e-20 + fConst17)) - 4.02016257201554e-19)) - 7.81929125002698e-18)));
	fConst19 = (1.75609599351763e-24 * fConst0);
	fConst20 = (6.49745000476917e-18 + (fConst0 * ((fConst0 * (2.1817595880033e-15 + (fConst0 * (3.04912223958481e-17 + (fConst0 * (fConst19 - 1.75006885291759e-19)))))) - 1.17289385123824e-13)));
	fConst21 = (1.0280271958907e-22 * fConst0);
	fConst22 = ((fConst0 * (1.03959118484409e-24 + (fConst0 * ((fConst0 * (fConst21 - 1.67308173700227e-21)) - 3.12771669424648e-20)))) - 2.71195547646483e-35);
	fConst23 = (9.92905276020348e-23 * fConst0);
	fConst24 = (5.19796371253824e-22 + (fConst0 * (1.5638582500054e-17 + (fConst0 * ((fConst0 * (0 - (8.6832635480651e-21 + fConst23))) - 8.04032514403108e-19)))));
	fConst25 = (3.51219198703525e-24 * fConst0);
	fConst26 = (1.29949000095383e-17 + (fConst0 * ((fConst0 * ((fConst0 * (6.09824447916961e-17 + (fConst0 * (1.16671256861173e-19 - fConst25)))) - 4.36351917600659e-15)) - 7.81929234158824e-14)));
	fConst27 = (2.71195547646483e-35 + (fConst0 * (1.03959118484409e-24 + (fConst0 * (3.12771669424648e-20 + (fConst0 * (0 - (1.67308173700227e-21 + fConst21))))))));
	fConst28 = ((fConst0 * (1.5638582500054e-17 + (fConst0 * (8.04032514403108e-19 + (fConst0 * (fConst23 - 8.6832635480651e-21)))))) - 5.19796371253824e-22);
	fConst29 = (1.29949000095383e-17 + (fConst0 * (7.81929234158824e-14 + (fConst0 * ((fConst0 * ((fConst0 * (1.16671256861173e-19 + fConst25)) - 6.09824447916961e-17)) - 4.36351917600659e-15)))));
	fConst30 = (4.06793321469724e-35 + (fConst0 * ((fConst0 * (1.56385834712324e-20 + (fConst0 * (2.50962260550341e-21 + fConst15)))) - 5.19795592422045e-25)));
	fConst31 = ((fConst0 * ((fConst0 * (4.02016257201554e-19 + (fConst0 * (1.30248953220977e-20 - fConst17)))) - 7.81929125002698e-18)) - 7.79694556880737e-22);
	fConst32 = (6.49745000476917e-18 + (fConst0 * (1.17289385123824e-13 + (fConst0 * (2.1817595880033e-15 + (fConst0 * ((fConst0 * (0 - (1.75006885291759e-19 + fConst19))) - 3.04912223958481e-17)))))));
	fConst33 = (2.12504383556653e-20 * fConst0);
	fConst34 = (1.20590256422748e-34 + (fConst0 * ((fConst0 * (1.93186425442337e-19 - fConst33)) - 6.76918055130131e-24)));
	fConst35 = (8.4212352539407e-21 + (fConst0 * (3.21977374686867e-16 + (fConst0 * (fConst33 - 6.39445014920369e-17)))));
	fConst36 = (4.01302196293057e-28 * fConst0);
	fConst37 = ((fConst0 * (3.1080196209939e-20 + (fConst0 * (8.4883795584658e-24 - fConst36)))) - 3.46700011398625e-17);
	fConst38 = (4.25008767113306e-20 * fConst0);
	fConst39 = ((fConst0 * ((fConst0 * (fConst38 - 1.28790950294891e-19)) - 1.35383611026026e-23)) - 2.41180512845497e-34);
	fConst40 = ((fConst0 * (6.43954749373733e-16 + (fConst0 * (4.26296676613579e-17 - fConst38)))) - 1.68424705078814e-20);
	fConst41 = (2.67534797528704e-28 * fConst0);
	fConst42 = ((fConst0 * ((fConst0 * (1.69767591169316e-23 + fConst41)) - 6.2160392419878e-20)) - 2.31133340932417e-17);
	fConst43 = ((fConst0 * (1.35383611026026e-23 + (fConst0 * (0 - (1.28790950294891e-19 + fConst38))))) - 2.41180512845497e-34);
	fConst44 = ((fConst0 * ((fConst0 * (4.26296676613579e-17 + fConst38)) - 6.43954749373733e-16)) - 1.68424705078814e-20);
	fConst45 = (2.31133340932417e-17 + (fConst0 * ((fConst0 * (fConst41 - 1.69767591169316e-23)) - 6.2160392419878e-20)));
	fConst46 = (1.20590256422748e-34 + (fConst0 * (6.76918055130131e-24 + (fConst0 * (1.93186425442337e-19 + fConst33)))));
	fConst47 = (8.4212352539407e-21 + (fConst0 * ((fConst0 * (0 - (6.39445014920369e-17 + fConst33))) - 3.21977374686867e-16)));
	fConst48 = (3.46700011398625e-17 + (fConst0 * (3.1080196209939e-20 + (fConst0 * (0 - (8.4883795584658e-24 + fConst36))))));
	fConst49 = (1.20590256422748e-34 + (fConst0 * ((fConst0 * (0 - (6.43954751474457e-20 + fConst7))) - 6.76918055130131e-24)));
	fConst50 = (8.4212352539407e-21 + (fConst0 * (3.21977374686867e-16 + (fConst0 * (2.1314833830679e-17 + fConst7)))));
	fConst51 = (1.15566670466208e-17 + (fConst0 * (3.1080196209939e-20 + (fConst0 * (8.4883795584658e-24 + fConst10)))));
	fConst52 = (0.1 * fConst0);
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
	double 	fSlow0 = (0.004073836948085289 * (exp(double(fslider0)) - 1));
	double 	fSlow1 = (0.004073836948085289 * (exp(double(fslider1)) - 1));
	for (int i=0; i<count; i++) {
		fRec0[0] = (fSlow0 + (0.993 * fRec0[1]));
		double fTemp0 = (fConst6 + (fRec0[0] * ((fConst0 * (fConst4 + (fConst2 * fRec0[0]))) - 6.1635351737837e-33)));
		fRec1[0] = ((double)input0[i] - ((((((fRec1[1] * (fConst32 + (fRec0[0] * ((fConst0 * (fConst31 + (fConst30 * fRec0[0]))) - 3.08176758689185e-32)))) + (fRec1[2] * (fConst29 + (fRec0[0] * ((fConst0 * (fConst28 + (fConst27 * fRec0[0]))) - 6.1635351737837e-32))))) + (fRec1[3] * (fConst26 + (fRec0[0] * ((fConst0 * (fConst24 + (fConst22 * fRec0[0]))) - 6.1635351737837e-32))))) + (fRec1[4] * (fConst20 + (fRec0[0] * ((fConst0 * (fConst18 + (fConst16 * fRec0[0]))) - 3.08176758689185e-32))))) + (fRec1[5] * (fConst14 + (fRec0[0] * ((fConst0 * (fConst13 + (fConst12 * fRec0[0]))) - 6.1635351737837e-33))))) / fTemp0));
		fRec2[0] = (fSlow1 + (0.993 * fRec2[1]));
		output0[i] = (FAUSTFLOAT)(fConst52 * ((fRec2[0] * ((((((fRec1[0] * (fConst51 + (fRec0[0] * ((fConst0 * (fConst50 + (fConst49 * fRec0[0]))) - 5.4813752919431e-32)))) + (fRec1[1] * (fConst48 + (fRec0[0] * ((fConst0 * (fConst47 + (fConst46 * fRec0[0]))) - 1.64441258758293e-31))))) + (fRec1[2] * (fConst45 + (fRec0[0] * ((fConst0 * (fConst44 + (fConst43 * fRec0[0]))) - 1.09627505838862e-31))))) + (fRec1[3] * (fConst42 + (fRec0[0] * (1.09627505838862e-31 + (fConst0 * (fConst40 + (fConst39 * fRec0[0])))))))) + (fRec1[4] * (fConst37 + (fRec0[0] * (1.64441258758293e-31 + (fConst0 * (fConst35 + (fConst34 * fRec0[0])))))))) + (fRec1[5] * (fConst11 + (fRec0[0] * (5.4813752919431e-32 + (fConst0 * (fConst9 + (fConst8 * fRec0[0]))))))))) / fTemp0));
		// post processing
		fRec2[1] = fRec2[0];
		for (int i=5; i>0; i--) fRec1[i] = fRec1[i-1];
		fRec0[1] = fRec0[0];
	}
#undef fslider0
#undef fslider1
}
		
void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case GAIN: 
		fslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case LEVEL: 
		fslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
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
	delete static_cast<Dsp*>(p);
}

/*
typedef enum
{
   GAIN, 
   LEVEL, 
} PortIndex;
*/

} // end namespace gx_w20
