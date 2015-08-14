// generated from file '../src/LV2/faust/selwah.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)


namespace selwah {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	int 	iVec0[2];
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fConst4;
	double 	fRec2[2];
	double 	fRec1[2];
	double 	fRec0[2];
	double 	fConst5;
	double 	fConst6;
	double 	fRec5[2];
	double 	fConst7;
	double 	fConst8;
	double 	fRec4[2];
	double 	fRec3[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec6[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
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
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fRec7[7];
	double 	fConst44;
	double 	fConst45;
	double 	fConst46;
	double 	fConst47;
	double 	fConst48;
	double 	fConst49;
	double 	fConst50;
	double 	fConst51;
	double 	fConst52;
	double 	fConst53;
	double 	fConst54;
	double 	fConst55;
	double 	fConst56;
	double 	fConst57;
	double 	fConst58;
	double 	fConst59;
	double 	fConst60;
	double 	fConst61;
	double 	fConst62;
	double 	fConst63;
	double 	fConst64;
	double 	fConst65;
	double 	fConst66;
	double 	fConst67;
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
	id = "selwah";
	name = N_("Selmer Wah");
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
	for (int i=0; i<2; i++) iVec0[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<7; i++) fRec7[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = double(iConst0);
	fConst2 = (1.35882114465691e-28 * fConst1);
	fConst3 = (1.69793769618456e-16 + (fConst1 * (1.81545551158112e-17 + (fConst1 * (4.93391235123126e-19 + (fConst1 * (2.51442385828734e-22 + (fConst1 * (3.45921439164547e-25 + fConst2)))))))));
	fConst4 = (0.10471975511965977 / double(iConst0));
	fConst5 = exp((0 - (1e+01 / double(iConst0))));
	fConst6 = (1.0 - fConst5);
	fConst7 = exp((0 - (1e+02 / double(iConst0))));
	fConst8 = (1.0 - fConst7);
	fConst9 = (2.87536324325607e-29 * fConst1);
	fConst10 = (fConst1 * ((fConst1 * ((fConst1 * ((fConst1 * (0 - (7.24707538410401e-26 + fConst9))) - 4.43177812582699e-23)) - 8.54099892501484e-20)) - 4.10877633167215e-19));
	fConst11 = (1.0257776611342e-28 * fConst1);
	fConst12 = ((fConst1 * ((fConst1 * (8.8419802743762e-20 + (fConst1 * (2.63968556410486e-23 + (fConst1 * (0 - (2.48312712069526e-25 + fConst11))))))) - 1.52694083181368e-18)) - 9.33812802652761e-18);
	fConst13 = (1.57938882748672e-29 * fConst1);
	fConst14 = ((fConst1 * (2.5499891019935e-20 + (fConst1 * ((fConst1 * (3.50531492229223e-25 - fConst13)) - 5.3829047771671e-22)))) - 2.69849191037642e-19);
	fConst15 = (3.86402812614522e-30 * fConst1);
	fConst16 = (fConst1 * ((fConst1 * (1.1678747498279e-22 + (fConst1 * (fConst15 - 7.74007134746085e-26)))) - 3.74471317195193e-21));
	fConst17 = (3.86646538813055e-30 * fConst1);
	fConst18 = (8.26135324400454e-20 + (fConst1 * (1.16867440975778e-21 + (fConst1 * ((fConst1 * (7.73247041446566e-26 - fConst17)) - 1.15093885842761e-22)))));
	fConst19 = ((fConst1 * (1.81545551158112e-17 + (fConst1 * ((fConst1 * (2.51442385828734e-22 + (fConst1 * (fConst2 - 3.45921439164547e-25)))) - 4.93391235123126e-19)))) - 1.69793769618456e-16);
	fConst20 = (fConst1 * ((fConst1 * (8.54099892501484e-20 + (fConst1 * ((fConst1 * (7.24707538410401e-26 - fConst9)) - 4.43177812582699e-23)))) - 4.10877633167215e-19));
	fConst21 = (9.33812802652761e-18 + (fConst1 * ((fConst1 * ((fConst1 * (2.63968556410486e-23 + (fConst1 * (2.48312712069526e-25 - fConst11)))) - 8.8419802743762e-20)) - 1.52694083181368e-18)));
	fConst22 = (8.15292686794146e-28 * fConst1);
	fConst23 = faustpower<2>(fConst1);
	fConst24 = ((fConst1 * (3.63091102316224e-17 + (fConst23 * ((fConst1 * (1.38368575665819e-24 - fConst22)) - 5.02884771657468e-22)))) - 6.79175078473822e-16);
	fConst25 = (1.72521794595364e-28 * fConst1);
	fConst26 = (fConst1 * ((fConst23 * (8.86355625165398e-23 + (fConst1 * (fConst25 - 2.8988301536416e-25)))) - 8.2175526633443e-19));
	fConst27 = (6.15466596680521e-28 * fConst1);
	fConst28 = (3.73525121061104e-17 + (fConst1 * ((fConst23 * ((fConst1 * (fConst27 - 9.93250848278106e-25)) - 5.27937112820972e-23)) - 3.05388166362736e-18)));
	fConst29 = (2.03823171698537e-27 * fConst1);
	fConst30 = ((fConst1 * ((fConst1 * (1.48017370536938e-18 + (fConst1 * ((fConst1 * (fConst29 - 1.72960719582274e-24)) - 2.51442385828734e-22)))) - 1.81545551158112e-17)) - 8.48968848092278e-16);
	fConst31 = (4.31304486488411e-28 * fConst1);
	fConst32 = (fConst1 * (4.10877633167215e-19 + (fConst1 * ((fConst1 * (4.43177812582699e-23 + (fConst1 * (3.623537692052e-25 - fConst31)))) - 2.56229967750445e-19))));
	fConst33 = (1.5386664917013e-27 * fConst1);
	fConst34 = (4.66906401326381e-17 + (fConst1 * (1.52694083181368e-18 + (fConst1 * (2.65259408231286e-19 + (fConst1 * ((fConst1 * (1.24156356034763e-24 - fConst33)) - 2.63968556410486e-23)))))));
	fConst35 = ((fConst23 * (1.00576954331494e-21 - (2.71764228931382e-27 * fConst23))) - 7.26182204632447e-17);
	fConst36 = (1.64351053266886e-18 + (fConst23 * ((5.75072648651214e-28 * fConst23) - 1.7727112503308e-22)));
	fConst37 = (6.10776332725473e-18 + (fConst23 * (1.05587422564194e-22 + (2.0515553222684e-27 * fConst23))));
	fConst38 = (8.48968848092278e-16 + (fConst1 * ((fConst1 * ((fConst1 * ((fConst1 * (1.72960719582274e-24 + fConst29)) - 2.51442385828734e-22)) - 1.48017370536938e-18)) - 1.81545551158112e-17)));
	fConst39 = (fConst1 * (4.10877633167215e-19 + (fConst1 * (2.56229967750445e-19 + (fConst1 * (4.43177812582699e-23 + (fConst1 * (0 - (3.623537692052e-25 + fConst31)))))))));
	fConst40 = ((fConst1 * (1.52694083181368e-18 + (fConst1 * ((fConst1 * ((fConst1 * (0 - (1.24156356034763e-24 + fConst33))) - 2.63968556410486e-23)) - 2.65259408231286e-19)))) - 4.66906401326381e-17);
	fConst41 = (6.79175078473822e-16 + (fConst1 * (3.63091102316224e-17 + (fConst23 * ((fConst1 * (0 - (1.38368575665819e-24 + fConst22))) - 5.02884771657468e-22)))));
	fConst42 = (fConst1 * ((fConst23 * (8.86355625165398e-23 + (fConst1 * (2.8988301536416e-25 + fConst25)))) - 8.2175526633443e-19));
	fConst43 = ((fConst1 * ((fConst23 * ((fConst1 * (9.93250848278106e-25 + fConst27)) - 5.27937112820972e-23)) - 3.05388166362736e-18)) - 3.73525121061104e-17);
	fConst44 = (9.4763329649203e-29 * fConst1);
	fConst45 = ((fConst23 * (1.07658095543342e-21 + (fConst1 * (fConst44 - 1.40212596891689e-24)))) - 5.39698382075284e-19);
	fConst46 = (2.31841687568713e-29 * fConst1);
	fConst47 = (fConst23 * ((fConst1 * (3.09602853898434e-25 - fConst46)) - 2.3357494996558e-22));
	fConst48 = (2.31987923287833e-29 * fConst1);
	fConst49 = (1.65227064880091e-19 + (fConst23 * (2.30187771685523e-22 + (fConst1 * (fConst48 - 3.09298816578626e-25)))));
	fConst50 = (2.36908324123008e-28 * fConst1);
	fConst51 = (2.69849191037642e-19 + (fConst1 * ((fConst1 * (5.3829047771671e-22 + (fConst1 * (1.75265746114611e-24 - fConst50)))) - 7.6499673059805e-20)));
	fConst52 = (5.79604218921784e-29 * fConst1);
	fConst53 = (fConst1 * (1.12341395158558e-20 + (fConst1 * ((fConst1 * (fConst52 - 3.87003567373042e-25)) - 1.1678747498279e-22))));
	fConst54 = (5.79969808219582e-29 * fConst1);
	fConst55 = ((fConst1 * ((fConst1 * (1.15093885842761e-22 + (fConst1 * (3.86623520723283e-25 - fConst54)))) - 3.50602322927335e-21)) - 8.26135324400454e-20);
	fConst56 = (1.07939676415057e-18 + (fConst23 * ((3.15877765497343e-28 * fConst23) - 2.15316191086684e-21)));
	fConst57 = (fConst23 * (4.6714989993116e-22 - (7.72805625229045e-29 * fConst23)));
	fConst58 = ((fConst23 * ((7.7329307762611e-29 * fConst23) - 4.60375543371045e-22)) - 3.30454129760181e-19);
	fConst59 = (2.69849191037642e-19 + (fConst1 * (7.6499673059805e-20 + (fConst1 * (5.3829047771671e-22 + (fConst1 * (0 - (1.75265746114611e-24 + fConst50))))))));
	fConst60 = (fConst1 * ((fConst1 * ((fConst1 * (3.87003567373042e-25 + fConst52)) - 1.1678747498279e-22)) - 1.12341395158558e-20));
	fConst61 = ((fConst1 * (3.50602322927335e-21 + (fConst1 * (1.15093885842761e-22 + (fConst1 * (0 - (3.86623520723283e-25 + fConst54))))))) - 8.26135324400454e-20);
	fConst62 = ((fConst23 * (1.07658095543342e-21 + (fConst1 * (1.40212596891689e-24 + fConst44)))) - 5.39698382075284e-19);
	fConst63 = (fConst23 * ((fConst1 * (0 - (3.09602853898434e-25 + fConst46))) - 2.3357494996558e-22));
	fConst64 = (1.65227064880091e-19 + (fConst23 * (2.30187771685523e-22 + (fConst1 * (3.09298816578626e-25 + fConst48)))));
	fConst65 = ((fConst1 * ((fConst1 * ((fConst1 * (0 - (3.50531492229223e-25 + fConst13))) - 5.3829047771671e-22)) - 2.5499891019935e-20)) - 2.69849191037642e-19);
	fConst66 = (fConst1 * (3.74471317195193e-21 + (fConst1 * (1.1678747498279e-22 + (fConst1 * (7.74007134746085e-26 + fConst15))))));
	fConst67 = (8.26135324400454e-20 + (fConst1 * ((fConst1 * ((fConst1 * (0 - (7.73247041446566e-26 + fConst17))) - 1.15093885842761e-22)) - 1.16867440975778e-21)));
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
#define fslider2 (*fslider2_)
#define fslider3 (*fslider3_)
	double 	fSlow0 = (fConst4 * double(fslider0));
	double 	fSlow1 = (0.007000000000000006 * double(fslider1));
	int 	iSlow2 = int(double(fslider2));
	double 	fSlow3 = (0.01 * double(fslider3));
	double 	fSlow4 = (1 - fSlow3);
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		fRec2[0] = (fRec2[1] + (fSlow0 * (0 - fRec0[1])));
		fRec1[0] = ((1 + (fRec1[1] + (fSlow0 * fRec2[0]))) - iVec0[1]);
		fRec0[0] = fRec1[0];
		double fTemp0 = (double)input0[i];
		double fTemp1 = fabs(fTemp0);
		fRec5[0] = ((fConst5 * max(fTemp1, fRec5[1])) + (fConst6 * fTemp1));
		fRec4[0] = ((fConst7 * fRec4[1]) + (fConst8 * fRec5[0]));
		fRec3[0] = ((0.993 * fRec3[1]) + (0.007000000000000006 * (1 - max(0.1, min(0.99, fRec4[0])))));
		fRec6[0] = ((0.993 * fRec6[1]) + fSlow1);
		double fTemp2 = ((iSlow2==0)? fRec6[0] : ((iSlow2==1)?fRec3[0]:max(0.01, min(0.9, (0.5 * (1 + fRec0[0]))))) );
		double fTemp3 = (4.66906401326381e-16 + (fConst1 * ((fTemp2 * (fConst12 + (fConst10 * fTemp2))) + fConst3)));
		fRec7[0] = ((fSlow3 * fTemp0) - (((((((fRec7[1] * (2.80143840795828e-15 + (fConst1 * ((fTemp2 * (fConst43 + (fConst42 * fTemp2))) + fConst41)))) + (fRec7[2] * (7.00359601989571e-15 + (fConst1 * ((fTemp2 * (fConst40 + (fConst39 * fTemp2))) + fConst38))))) + (fRec7[3] * (9.33812802652761e-15 + (fConst23 * ((fTemp2 * (fConst37 + (fConst36 * fTemp2))) + fConst35))))) + (fRec7[4] * (7.00359601989571e-15 + (fConst1 * ((fTemp2 * (fConst34 + (fConst32 * fTemp2))) + fConst30))))) + (fRec7[5] * (2.80143840795828e-15 + (fConst1 * ((fTemp2 * (fConst28 + (fConst26 * fTemp2))) + fConst24))))) + (fRec7[6] * (4.66906401326381e-16 + (fConst1 * ((fTemp2 * (fConst21 + (fConst20 * fTemp2))) + fConst19))))) / fTemp3));
		output0[i] = (FAUSTFLOAT)((fSlow4 * fTemp0) + (fConst23 * ((((((((fRec7[0] * ((fTemp2 * (fConst67 + (fConst66 * fTemp2))) + fConst65)) + (fRec7[1] * ((fTemp2 * (fConst64 + (fConst63 * fTemp2))) + fConst62))) + (fRec7[2] * ((fTemp2 * (fConst61 + (fConst60 * fTemp2))) + fConst59))) + (fRec7[3] * ((fTemp2 * (fConst58 + (fConst57 * fTemp2))) + fConst56))) + (fRec7[4] * ((fTemp2 * (fConst55 + (fConst53 * fTemp2))) + fConst51))) + (fRec7[5] * ((fTemp2 * (fConst49 + (fConst47 * fTemp2))) + fConst45))) + (fRec7[6] * ((fTemp2 * (fConst18 + (fConst16 * fTemp2))) + fConst14))) / fTemp3)));
		// post processing
		for (int i=6; i>0; i--) fRec7[i] = fRec7[i-1];
		fRec6[1] = fRec6[0];
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		iVec0[1] = iVec0[0];
	}
#undef fslider0
#undef fslider1
#undef fslider2
#undef fslider3
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case WAH: 
		fslider1_ = (float*)data; // , 0.0, 0.0, 1.0, 0.01 
		break;
	case FREQ: 
		fslider0_ = (float*)data; // , 24.0, 24.0, 3.6e+02, 1.0 
		break;
	// static const value_pair fslider2_values[] = {{"manual"},{"auto"},{"alien"},{0}};
	case MODE: 
		fslider2_ = (float*)data; // , 0.0, 0.0, 2.0, 1.0 
		break;
	case WET_DRY: 
		fslider3_ = (float*)data; // , 1e+02, 0.0, 1e+02, 1.0 
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
   WAH, 
   FREQ, 
   MODE, 
   WET_DRY, 
} PortIndex;
*/

} // end namespace selwah
