// generated from file './faust/digital_delay.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "beat.h"

namespace digital_delay {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT	*fcheckbox0_;
	FAUSTFLOAT 	fslider8;
	FAUSTFLOAT	*fslider8_;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	int 	iConst0;
	double 	fConst1;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fRec2[3];
	double 	fRec1[3];
	double 	fVec0[2];
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
	double 	fConst52;
	double 	fConst53;
	double 	fConst54;
	double 	fRec11[2];
	double 	fRec10[3];
	double 	fConst55;
	double 	fRec9[3];
	double 	fConst56;
	double 	fConst57;
	double 	fConst58;
	double 	fRec8[3];
	double 	fConst59;
	double 	fConst60;
	double 	fConst61;
	double 	fRec7[3];
	double 	fConst62;
	double 	fConst63;
	double 	fConst64;
	double 	fRec6[3];
	double 	fConst65;
	double 	fConst66;
	double 	fConst67;
	double 	fRec5[3];
	double 	fConst68;
	double 	fConst69;
	double 	fConst70;
	double 	fVec1[2];
	double 	fConst71;
	double 	fConst72;
	double 	fConst73;
	double 	fRec4[2];
	double 	fRec3[3];
	double 	fConst74;
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT	*fslider4_;
	double 	fRec18[2];
	double 	fRec16[2];
	double 	fRec14[2];
	double 	fRec12[2];
	double 	fRec26[2];
	double 	fRec24[2];
	double 	fRec22[2];
	double 	fRec20[2];
	int 	IOTA;
	double 	fVec2[524288];
	double 	fConst75;
	double 	fConst76;
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT	*fslider5_;
	FAUSTFLOAT 	fslider6;
	FAUSTFLOAT	*fslider6_;
	int 	iConst77;
	double 	fRec28[2];
	double 	fRec29[2];
	double 	fRec30[2];
	double 	fRec31[2];
	FAUSTFLOAT 	fslider7;
	FAUSTFLOAT	*fslider7_;
	double 	fRec0[2];
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
	id = "dide";
	name = N_("Digital Delay");
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
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<3; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<3; i++) fRec10[i] = 0;
	for (int i=0; i<3; i++) fRec9[i] = 0;
	for (int i=0; i<3; i++) fRec8[i] = 0;
	for (int i=0; i<3; i++) fRec7[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<3; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<524288; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec28[i] = 0;
	for (int i=0; i<2; i++) fRec29[i] = 0;
	for (int i=0; i<2; i++) fRec30[i] = 0;
	for (int i=0; i<2; i++) fRec31[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = std::min(192000, std::max(1, (int)fSamplingFreq));
	fConst1 = (3.141592653589793 / double(iConst0));
	fConst2 = tan((37699.11184307752 / double(iConst0)));
	fConst3 = (2 * (1 - (1.0 / faustpower<2>(fConst2))));
	fConst4 = (1.0 / fConst2);
	fConst5 = (1 + ((fConst4 - 1.0000000000000004) / fConst2));
	fConst6 = (1 + ((1.0000000000000004 + fConst4) / fConst2));
	fConst7 = (1.0 / fConst6);
	fConst8 = tan((25132.741228718343 / double(iConst0)));
	fConst9 = (2 * (1 - (1.0 / faustpower<2>(fConst8))));
	fConst10 = double((1.0 / double(iConst0)));
	fConst11 = (fConst10 / sin((50265.48245743669 * fConst10)));
	fConst12 = (3141.592653589793 * fConst11);
	fConst13 = (1.0 / fConst8);
	fConst14 = (1 + ((fConst13 - fConst12) / fConst8));
	fConst15 = (1 + ((fConst12 + fConst13) / fConst8));
	fConst16 = (1.0 / fConst15);
	fConst17 = tan((12566.370614359172 / double(iConst0)));
	fConst18 = (2 * (1 - (1.0 / faustpower<2>(fConst17))));
	fConst19 = (fConst10 / sin((25132.741228718343 * fConst10)));
	fConst20 = (6268.301430690795 * fConst19);
	fConst21 = (1.0 / fConst17);
	fConst22 = (1 + ((fConst21 - fConst20) / fConst17));
	fConst23 = (1.0 / (1 + ((fConst20 + fConst21) / fConst17)));
	fConst24 = tan((6283.185307179586 / double(iConst0)));
	fConst25 = (2 * (1 - (1.0 / faustpower<2>(fConst24))));
	fConst26 = (fConst10 / sin((12566.370614359172 * fConst10)));
	fConst27 = (1570.7963267948965 * fConst26);
	fConst28 = (1.0 / fConst24);
	fConst29 = (1 + ((fConst28 - fConst27) / fConst24));
	fConst30 = (1.0 / (1 + ((fConst27 + fConst28) / fConst24)));
	fConst31 = tan((1178.0972450961724 / double(iConst0)));
	fConst32 = (2 * (1 - (1.0 / faustpower<2>(fConst31))));
	fConst33 = (fConst10 / sin((2356.194490192345 * fConst10)));
	fConst34 = (392.6990816987241 * fConst33);
	fConst35 = (1.0 / fConst31);
	fConst36 = (1 + ((fConst35 - fConst34) / fConst31));
	fConst37 = (1.0 / (1 + ((fConst34 + fConst35) / fConst31)));
	fConst38 = tan((628.3185307179587 / double(iConst0)));
	fConst39 = (2 * (1 - (1.0 / faustpower<2>(fConst38))));
	fConst40 = (fConst10 / sin((1256.6370614359173 * fConst10)));
	fConst41 = (221.8808786553305 * fConst40);
	fConst42 = (1.0 / fConst38);
	fConst43 = (1 + ((fConst42 - fConst41) / fConst38));
	fConst44 = (1.0 / (1 + ((fConst41 + fConst42) / fConst38)));
	fConst45 = tan((251.32741228718345 / double(iConst0)));
	fConst46 = (1.0 / faustpower<2>(fConst45));
	fConst47 = (2 * (1 - fConst46));
	fConst48 = (1.0 / fConst45);
	fConst49 = (1 + ((fConst48 - 1.0000000000000004) / fConst45));
	fConst50 = (1.0 / (1 + ((1.0000000000000004 + fConst48) / fConst45)));
	fConst51 = (0 - fConst48);
	fConst52 = (1 + fConst48);
	fConst53 = (1.0 / fConst52);
	fConst54 = (0 - ((1 - fConst48) / fConst52));
	fConst55 = (2 * (0 - fConst46));
	fConst56 = (157.07963267948966 * fConst40);
	fConst57 = (1 + ((fConst42 - fConst56) / fConst38));
	fConst58 = (1 + ((fConst56 + fConst42) / fConst38));
	fConst59 = (466.72373331140534 * fConst33);
	fConst60 = (1 + ((fConst35 - fConst59) / fConst31));
	fConst61 = (1 + ((fConst59 + fConst35) / fConst31));
	fConst62 = (2218.808786553305 * fConst26);
	fConst63 = (1 + ((fConst28 - fConst62) / fConst24));
	fConst64 = (1 + ((fConst62 + fConst28) / fConst24));
	fConst65 = (3141.592653589793 * fConst19);
	fConst66 = (1 + ((fConst21 - fConst65) / fConst17));
	fConst67 = (1 + ((fConst65 + fConst21) / fConst17));
	fConst68 = (3955.030825110061 * fConst11);
	fConst69 = (1 + ((fConst13 - fConst68) / fConst8));
	fConst70 = (1 + ((fConst68 + fConst13) / fConst8));
	fConst71 = (1 + fConst4);
	fConst72 = (1.0 / (fConst71 * fConst15));
	fConst73 = (0 - ((1 - fConst4) / fConst71));
	fConst74 = (0.8 / fConst6);
	IOTA = 0;
	fConst75 = (1e+01 / double(iConst0));
	fConst76 = (0 - fConst75);
	iConst77 = (60 * iConst0);
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fcheckbox0 (*fcheckbox0_)
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
#define fslider2 (*fslider2_)
#define fslider3 (*fslider3_)
#define fslider4 (*fslider4_)
#define fslider5 (*fslider5_)
#define fslider6 (*fslider6_)
#define fslider7 (*fslider7_)
#define fslider8 (*fslider8_)
    if (int(fcheckbox0)) fslider6 = fslider8;
	double 	fSlow0 = (0.01 * double(fslider0));
	double 	fSlow1 = tan((fConst1 * double(fslider1)));
	double 	fSlow2 = (2 * (1 - (1.0 / faustpower<2>(fSlow1))));
	double 	fSlow3 = (1.0 / fSlow1);
	double 	fSlow4 = (1 + ((fSlow3 - 1.414213562373095) / fSlow1));
	double 	fSlow5 = (1 + ((1.414213562373095 + fSlow3) / fSlow1));
	double 	fSlow6 = (1.0 / fSlow5);
	double 	fSlow7 = tan((fConst1 * double(fslider2)));
	double 	fSlow8 = (1.0 / faustpower<2>(fSlow7));
	double 	fSlow9 = (2 * (1 - fSlow8));
	double 	fSlow10 = (1.0 / fSlow7);
	double 	fSlow11 = (1 + ((fSlow10 - 1.414213562373095) / fSlow7));
	double 	fSlow12 = (1.0 / (1 + ((1.414213562373095 + fSlow10) / fSlow7)));
	double 	fSlow13 = (0.01 * double(fslider3));
	double 	fSlow14 = (2 * (0 - fSlow8));
	double 	fSlow15 = (fConst48 / fSlow5);
	double 	fSlow16 = double(fslider4);
	int 	iSlow17 = int(std::min((double)2, std::max((double)0, fSlow16)));
	int 	iSlow18 = int(std::min((double)2, std::max((double)0, (fSlow16 - 1))));
	int 	iSlow19 = int(std::min((double)2, std::max((double)0, (fSlow16 - 2))));
	double 	fSlow20 = std::min(524288.0, B2N(double(fslider5), (double(iConst77) / double(fslider6))));
	double 	fSlow21 = (0.01 * double(fslider7));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fRec2[0] = ((fSlow13 * fRec0[1]) - (fSlow12 * ((fSlow11 * fRec2[2]) + (fSlow9 * fRec2[1]))));
		fRec1[0] = ((fSlow12 * (((fSlow8 * fRec2[0]) + (fSlow14 * fRec2[1])) + (fSlow8 * fRec2[2]))) - (fSlow6 * ((fSlow4 * fRec1[2]) + (fSlow2 * fRec1[1]))));
		double fTemp1 = (fRec1[2] + (fRec1[0] + (2 * fRec1[1])));
		double fTemp2 = (fSlow6 * fTemp1);
		fVec0[0] = fTemp2;
		double fTemp3 = (fConst9 * fRec5[1]);
		double fTemp4 = (fConst18 * fRec6[1]);
		double fTemp5 = (fConst25 * fRec7[1]);
		double fTemp6 = (fConst32 * fRec8[1]);
		double fTemp7 = (fConst39 * fRec9[1]);
		fRec11[0] = ((fConst54 * fRec11[1]) + (fConst53 * ((fSlow15 * fTemp1) + (fConst51 * fVec0[1]))));
		fRec10[0] = (fRec11[0] - (fConst50 * ((fConst49 * fRec10[2]) + (fConst47 * fRec10[1]))));
		fRec9[0] = ((fConst50 * (((fConst46 * fRec10[0]) + (fConst55 * fRec10[1])) + (fConst46 * fRec10[2]))) - (fConst44 * ((fConst43 * fRec9[2]) + fTemp7)));
		fRec8[0] = ((fConst44 * ((fTemp7 + (fConst58 * fRec9[0])) + (fConst57 * fRec9[2]))) - (fConst37 * ((fConst36 * fRec8[2]) + fTemp6)));
		fRec7[0] = ((fConst37 * ((fTemp6 + (fConst61 * fRec8[0])) + (fConst60 * fRec8[2]))) - (fConst30 * ((fConst29 * fRec7[2]) + fTemp5)));
		fRec6[0] = ((fConst30 * ((fTemp5 + (fConst64 * fRec7[0])) + (fConst63 * fRec7[2]))) - (fConst23 * ((fConst22 * fRec6[2]) + fTemp4)));
		fRec5[0] = ((fConst23 * ((fTemp4 + (fConst67 * fRec6[0])) + (fConst66 * fRec6[2]))) - (fConst16 * ((fConst14 * fRec5[2]) + fTemp3)));
		double fTemp8 = ((fTemp3 + (fConst70 * fRec5[0])) + (fConst69 * fRec5[2]));
		fVec1[0] = fTemp8;
		fRec4[0] = ((fConst73 * fRec4[1]) + (fConst72 * (fVec1[0] + fVec1[1])));
		fRec3[0] = (fRec4[0] - (fConst7 * ((fConst5 * fRec3[2]) + (fConst3 * fRec3[1]))));
		double fTemp9 = ((iSlow17==0)? fVec0[0] : ((iSlow17==1)?(fConst74 * (fRec3[2] + (fRec3[0] + (2 * fRec3[1])))):fVec0[0]) );
		double fTemp10 = (0.1 * fRec12[1]);
		double fTemp11 = ((0.4 * fRec16[1]) + fTemp10);
		double fTemp12 = (0.2 * fRec14[1]);
		double fTemp13 = ((fTemp12 + (fTemp9 + (0.6 * fRec18[1]))) - fTemp11);
		fRec18[0] = fTemp13;
		double 	fRec19 = (0 - (0.6 * fTemp13));
		fRec16[0] = (fRec19 + fRec18[1]);
		double fTemp14 = (fTemp9 + fTemp12);
		double 	fRec17 = (0.4 * (fTemp14 - fTemp11));
		fRec14[0] = (fRec17 + fRec16[1]);
		double 	fRec15 = (0 - (0.2 * (fTemp14 - fTemp10)));
		fRec12[0] = (fRec15 + fRec14[1]);
		double 	fRec13 = (0.1 * (fTemp9 - fTemp10));
		double fTemp15 = ((iSlow18==0)? fTemp9 : ((iSlow18==1)?(fRec13 + fRec12[1]):fTemp9) );
		double fTemp16 = (0.5 * fRec20[1]);
		double fTemp17 = ((0.4 * fRec22[1]) + fTemp16);
		double fTemp18 = (0.3 * fRec24[1]);
		double fTemp19 = ((fTemp18 + (fTemp15 + (0.2 * fRec26[1]))) - fTemp17);
		fRec26[0] = fTemp19;
		double 	fRec27 = (0 - (0.2 * fTemp19));
		fRec24[0] = (fRec27 + fRec26[1]);
		double 	fRec25 = (0 - (0.3 * ((fTemp15 + fTemp18) - fTemp17)));
		fRec22[0] = (fRec25 + fRec24[1]);
		double 	fRec23 = (0.4 * (fTemp15 - fTemp17));
		fRec20[0] = (fRec23 + fRec22[1]);
		double 	fRec21 = (0.5 * (fTemp15 - fTemp16));
		double fTemp20 = (((iSlow19==0)? fTemp15 : ((iSlow19==1)?(fRec21 + fRec20[1]):fTemp15) ) + (fSlow0 * fTemp0));
		fVec2[IOTA&524287] = fTemp20;
		double fTemp21 = ((int((fRec28[1] != 0.0)))?((int(((fRec29[1] > 0.0) & (fRec29[1] < 1.0))))?fRec28[1]:0):((int(((fRec29[1] == 0.0) & (fSlow20 != fRec30[1]))))?fConst75:((int(((fRec29[1] == 1.0) & (fSlow20 != fRec31[1]))))?fConst76:0)));
		fRec28[0] = fTemp21;
		fRec29[0] = std::max(0.0, std::min(1.0, (fRec29[1] + fTemp21)));
		fRec30[0] = ((int(((fRec29[1] >= 1.0) & (fRec31[1] != fSlow20))))?fSlow20:fRec30[1]);
		fRec31[0] = ((int(((fRec29[1] <= 0.0) & (fRec30[1] != fSlow20))))?fSlow20:fRec31[1]);
		fRec0[0] = (fSlow21 * (((1.0 - fRec29[0]) * fVec2[(IOTA-int((int(fRec30[0]) & 524287)))&524287]) + (fRec29[0] * fVec2[(IOTA-int((int(fRec31[0]) & 524287)))&524287])));
		output0[i] = (FAUSTFLOAT)(fTemp0 + fRec0[0]);
		// post processing
		fRec0[1] = fRec0[0];
		fRec31[1] = fRec31[0];
		fRec30[1] = fRec30[0];
		fRec29[1] = fRec29[0];
		fRec28[1] = fRec28[0];
		IOTA = IOTA+1;
		fRec20[1] = fRec20[0];
		fRec22[1] = fRec22[0];
		fRec24[1] = fRec24[0];
		fRec26[1] = fRec26[0];
		fRec12[1] = fRec12[0];
		fRec14[1] = fRec14[0];
		fRec16[1] = fRec16[0];
		fRec18[1] = fRec18[0];
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fVec1[1] = fVec1[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
		fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		fVec0[1] = fVec0[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
	}
#undef fcheckbox0
#undef fslider0
#undef fslider1
#undef fslider2
#undef fslider3
#undef fslider4
#undef fslider5
#undef fslider6
#undef fslider7
#undef fslider8
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case BPM: 
		fslider6_ = (float*)data; // , 1.2e+02, 24.0, 3.6e+02, 1.0 
		break;
	case FEEDBACK: 
		fslider3_ = (float*)data; // , 5e+01, 1.0, 1e+02, 1.0 
		break;
	case GAIN: 
		fslider0_ = (float*)data; // , 1e+02, 0.0, 1.2e+02, 1.0 
		break;
	case HIGHPASS: 
		fslider2_ = (float*)data; // , 1.2e+02, 2e+01, 2e+04, 1.0 
		break;
	case HOWPASS: 
		fslider1_ = (float*)data; // , 1.2e+04, 2e+01, 2e+04, 1.0 
		break;
	case LEVEL: 
		fslider7_ = (float*)data; // , 5e+01, 1.0, 1e+02, 1.0 
		break;
	// static const value_pair fslider4_values[] = {{"plain"},{"presence"},{"tape"},{"tape2"},{0}};
	case MODE: 
		fslider4_ = (float*)data; // , 0.0, 0.0, 3.0, 1.0 
		break;
	// static const value_pair fslider5_values[] = {{"Dotted 1/2 note"},{"1/2 note"},{"1/2 note triplets"},{" Dotted 1/4 note"},{"1/4 note"},{"1/4 note triplets"},{"Dotted 1/8 note"},{"1/8 note"},{"1/8 note triplets"},{" Dotted 1/16 note"},{"1/16 note"},{"1/16 note triplets"},{"Dotted 1/32 note"},{"1/32 note"},{"1/32 note triplets"},{" Dotted 1/64 note"},{"1/64 note"},{"1/64 note triplets"},{0}};
	case NOTES: 
		fslider5_ = (float*)data; // , 5.0, 1.0, 18.0, 1.0 
		break;
	case SYNC: 
		fcheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case HOSTBPM: 
		fslider8_ = (float*)data; // , 1.2e+02, 24.0, 3.6e+02, 1.0 
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
   BPM, 
   FEEDBACK, 
   GAIN, 
   HIGHPASS, 
   HOWPASS, 
   LEVEL, 
   MODE, 
   NOTES, 
} PortIndex;
*/

} // end namespace digital_delay
