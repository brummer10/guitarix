// generated from file '../src/plugins/zita_rev1.dsp' by dsp2cc:
// Code generated with Faust 0.9.30 (http://faust.grame.fr)


#include "gx_faust_support.h"
#include "gx_plugin.h"
#define N_(x) (x)
namespace zita_rev1 {
static double 	fConst0;
static double 	fConst1;
static FAUSTFLOAT 	fslider0;
static int 	iConst2;
static double 	fConst3;
static double 	fConst4;
static FAUSTFLOAT 	fslider1;
static double 	fConst5;
static FAUSTFLOAT 	fslider2;
static double 	fConst6;
static double 	fRec13[2];
static FAUSTFLOAT 	fslider3;
static double 	fRec12[2];
static int 	IOTA;
static double 	fVec0[8192];
static double 	fConst7;
static int 	iConst8;
static double 	fVec1[8192];
static FAUSTFLOAT 	fslider4;
static double 	fConst9;
static double 	fVec2[2048];
static int 	iConst10;
static double 	fRec10[2];
static double 	fConst11;
static double 	fConst12;
static double 	fRec17[2];
static double 	fRec16[2];
static double 	fVec3[8192];
static double 	fConst13;
static int 	iConst14;
static double 	fVec4[1024];
static int 	iConst15;
static double 	fRec14[2];
static double 	fConst16;
static double 	fConst17;
static double 	fRec21[2];
static double 	fRec20[2];
static double 	fVec5[8192];
static double 	fConst18;
static int 	iConst19;
static double 	fVec6[2048];
static int 	iConst20;
static double 	fRec18[2];
static double 	fConst21;
static double 	fConst22;
static double 	fRec25[2];
static double 	fRec24[2];
static double 	fVec7[8192];
static double 	fConst23;
static int 	iConst24;
static double 	fVec8[1024];
static int 	iConst25;
static double 	fRec22[2];
static double 	fConst26;
static double 	fConst27;
static double 	fConst28;
static double 	fConst29;
static double 	fRec29[2];
static double 	fRec28[2];
static double 	fVec9[16384];
static double 	fConst30;
static int 	iConst31;
static double 	fVec10[8192];
static double 	fVec11[2048];
static int 	iConst32;
static double 	fRec26[2];
static double 	fConst33;
static double 	fConst34;
static double 	fRec33[2];
static double 	fRec32[2];
static double 	fVec12[8192];
static double 	fConst35;
static int 	iConst36;
static double 	fVec13[2048];
static int 	iConst37;
static double 	fRec30[2];
static double 	fConst38;
static double 	fConst39;
static double 	fRec37[2];
static double 	fRec36[2];
static double 	fVec14[16384];
static double 	fConst40;
static int 	iConst41;
static double 	fVec15[2048];
static int 	iConst42;
static double 	fRec34[2];
static double 	fConst43;
static double 	fConst44;
static double 	fRec41[2];
static double 	fRec40[2];
static double 	fVec16[16384];
static double 	fConst45;
static int 	iConst46;
static double 	fVec17[1024];
static int 	iConst47;
static double 	fRec38[2];
static double 	fRec2[3];
static double 	fRec3[3];
static double 	fRec4[3];
static double 	fRec5[3];
static double 	fRec6[3];
static double 	fRec7[3];
static double 	fRec8[3];
static double 	fRec9[3];
static FAUSTFLOAT 	fslider5;
static double 	fConst48;
static FAUSTFLOAT 	fslider6;
static double 	fRec1[3];
static FAUSTFLOAT 	fslider7;
static FAUSTFLOAT 	fslider8;
static double 	fRec0[3];
static FAUSTFLOAT 	fslider9;
static double 	fRec42[2];
static FAUSTFLOAT 	fslider10;
static double 	fRec43[2];
static double 	fRec45[3];
static double 	fRec44[3];
static int	fSamplingFreq;

static void clear_state(PluginDef* = 0)
{
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<8192; i++) fVec0[i] = 0;
	for (int i=0; i<8192; i++) fVec1[i] = 0;
	for (int i=0; i<2048; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<8192; i++) fVec3[i] = 0;
	for (int i=0; i<1024; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<8192; i++) fVec5[i] = 0;
	for (int i=0; i<2048; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fRec25[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<8192; i++) fVec7[i] = 0;
	for (int i=0; i<1024; i++) fVec8[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fRec29[i] = 0;
	for (int i=0; i<2; i++) fRec28[i] = 0;
	for (int i=0; i<16384; i++) fVec9[i] = 0;
	for (int i=0; i<8192; i++) fVec10[i] = 0;
	for (int i=0; i<2048; i++) fVec11[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<2; i++) fRec33[i] = 0;
	for (int i=0; i<2; i++) fRec32[i] = 0;
	for (int i=0; i<8192; i++) fVec12[i] = 0;
	for (int i=0; i<2048; i++) fVec13[i] = 0;
	for (int i=0; i<2; i++) fRec30[i] = 0;
	for (int i=0; i<2; i++) fRec37[i] = 0;
	for (int i=0; i<2; i++) fRec36[i] = 0;
	for (int i=0; i<16384; i++) fVec14[i] = 0;
	for (int i=0; i<2048; i++) fVec15[i] = 0;
	for (int i=0; i<2; i++) fRec34[i] = 0;
	for (int i=0; i<2; i++) fRec41[i] = 0;
	for (int i=0; i<2; i++) fRec40[i] = 0;
	for (int i=0; i<16384; i++) fVec16[i] = 0;
	for (int i=0; i<1024; i++) fVec17[i] = 0;
	for (int i=0; i<2; i++) fRec38[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<3; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec4[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<3; i++) fRec7[i] = 0;
	for (int i=0; i<3; i++) fRec8[i] = 0;
	for (int i=0; i<3; i++) fRec9[i] = 0;
	for (int i=0; i<3; i++) fRec1[i] = 0;
	for (int i=0; i<3; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec42[i] = 0;
	for (int i=0; i<2; i++) fRec43[i] = 0;
	for (int i=0; i<3; i++) fRec45[i] = 0;
	for (int i=0; i<3; i++) fRec44[i] = 0;
}

static void init(int samplingFreq, PluginDef* = 0)
{
	fSamplingFreq = samplingFreq;
	fConst0 = ((0)?-0.6:0.6);
	fConst1 = (0 - fConst0);
	iConst2 = min(192000, max(1, fSamplingFreq));
	fConst3 = floor((0.5 + (0.174713 * iConst2)));
	fConst4 = ((0 - (6.907755278982138 * fConst3)) / iConst2);
	fConst5 = (6.283185307179586 / double(iConst2));
	fConst6 = (3.141592653589793 / iConst2);
	IOTA = 0;
	fConst7 = floor((0.5 + (0.022904 * iConst2)));
	iConst8 = int((int((fConst3 - fConst7)) & 8191));
	fConst9 = (0.001 * iConst2);
	iConst10 = int((int((fConst7 - 1)) & 2047));
	fConst11 = floor((0.5 + (0.153129 * iConst2)));
	fConst12 = ((0 - (6.907755278982138 * fConst11)) / iConst2);
	fConst13 = floor((0.5 + (0.020346 * iConst2)));
	iConst14 = int((int((fConst11 - fConst13)) & 8191));
	iConst15 = int((int((fConst13 - 1)) & 1023));
	fConst16 = floor((0.5 + (0.127837 * iConst2)));
	fConst17 = ((0 - (6.907755278982138 * fConst16)) / iConst2);
	fConst18 = floor((0.5 + (0.031604 * iConst2)));
	iConst19 = int((int((fConst16 - fConst18)) & 8191));
	iConst20 = int((int((fConst18 - 1)) & 2047));
	fConst21 = floor((0.5 + (0.125 * iConst2)));
	fConst22 = ((0 - (6.907755278982138 * fConst21)) / iConst2);
	fConst23 = floor((0.5 + (0.013458 * iConst2)));
	iConst24 = int((int((fConst21 - fConst23)) & 8191));
	iConst25 = int((int((fConst23 - 1)) & 1023));
	fConst26 = ((1)?-0.6:0.6);
	fConst27 = (0 - fConst26);
	fConst28 = floor((0.5 + (0.210389 * iConst2)));
	fConst29 = ((0 - (6.907755278982138 * fConst28)) / iConst2);
	fConst30 = floor((0.5 + (0.024421 * iConst2)));
	iConst31 = int((int((fConst28 - fConst30)) & 16383));
	iConst32 = int((int((fConst30 - 1)) & 2047));
	fConst33 = floor((0.5 + (0.192303 * iConst2)));
	fConst34 = ((0 - (6.907755278982138 * fConst33)) / iConst2);
	fConst35 = floor((0.5 + (0.029291 * iConst2)));
	iConst36 = int((int((fConst33 - fConst35)) & 8191));
	iConst37 = int((int((fConst35 - 1)) & 2047));
	fConst38 = floor((0.5 + (0.256891 * iConst2)));
	fConst39 = ((0 - (6.907755278982138 * fConst38)) / iConst2);
	fConst40 = floor((0.5 + (0.027333 * iConst2)));
	iConst41 = int((int((fConst38 - fConst40)) & 16383));
	iConst42 = int((int((fConst40 - 1)) & 2047));
	fConst43 = floor((0.5 + (0.219991 * iConst2)));
	fConst44 = ((0 - (6.907755278982138 * fConst43)) / iConst2);
	fConst45 = floor((0.5 + (0.019123 * iConst2)));
	iConst46 = int((int((fConst43 - fConst45)) & 16383));
	iConst47 = int((int((fConst45 - 1)) & 1023));
	fConst48 = (6.283185307179586 / iConst2);
	clear_state();
}

static void compute(int count, float *input0, float *input1, float *output0, float *output1)
{
	double 	fSlow0 = fslider0;
	double 	fSlow1 = exp((fConst4 / fSlow0));
	double 	fSlow2 = faustpower<2>(fSlow1);
	double 	fSlow3 = (1.0 - fSlow2);
	double 	fSlow4 = cos((fConst5 * fslider1));
	double 	fSlow5 = (1.0 - (fSlow4 * fSlow2));
	double 	fSlow6 = sqrt(((faustpower<2>(fSlow5) / faustpower<2>(fSlow3)) - 1.0));
	double 	fSlow7 = (fSlow5 / fSlow3);
	double 	fSlow8 = (fSlow7 - fSlow6);
	double 	fSlow9 = (1.0 / tan((fConst6 * fslider2)));
	double 	fSlow10 = (1 + fSlow9);
	double 	fSlow11 = (0 - ((1 - fSlow9) / fSlow10));
	double 	fSlow12 = (1.0 / fSlow10);
	double 	fSlow13 = fslider3;
	double 	fSlow14 = ((exp((fConst4 / fSlow13)) / fSlow1) - 1);
	double 	fSlow15 = (fSlow1 * ((1.0 + fSlow6) - fSlow7));
	int 	iSlow16 = int((int((fConst9 * fslider4)) & 8191));
	double 	fSlow17 = exp((fConst12 / fSlow0));
	double 	fSlow18 = faustpower<2>(fSlow17);
	double 	fSlow19 = (1.0 - fSlow18);
	double 	fSlow20 = (1.0 - (fSlow4 * fSlow18));
	double 	fSlow21 = sqrt(((faustpower<2>(fSlow20) / faustpower<2>(fSlow19)) - 1.0));
	double 	fSlow22 = (fSlow20 / fSlow19);
	double 	fSlow23 = (fSlow22 - fSlow21);
	double 	fSlow24 = ((exp((fConst12 / fSlow13)) / fSlow17) - 1);
	double 	fSlow25 = (fSlow17 * ((1.0 + fSlow21) - fSlow22));
	double 	fSlow26 = exp((fConst17 / fSlow0));
	double 	fSlow27 = faustpower<2>(fSlow26);
	double 	fSlow28 = (1.0 - fSlow27);
	double 	fSlow29 = (1.0 - (fSlow4 * fSlow27));
	double 	fSlow30 = sqrt(((faustpower<2>(fSlow29) / faustpower<2>(fSlow28)) - 1.0));
	double 	fSlow31 = (fSlow29 / fSlow28);
	double 	fSlow32 = (fSlow31 - fSlow30);
	double 	fSlow33 = ((exp((fConst17 / fSlow13)) / fSlow26) - 1);
	double 	fSlow34 = (fSlow26 * ((1.0 + fSlow30) - fSlow31));
	double 	fSlow35 = exp((fConst22 / fSlow0));
	double 	fSlow36 = faustpower<2>(fSlow35);
	double 	fSlow37 = (1.0 - fSlow36);
	double 	fSlow38 = (1.0 - (fSlow4 * fSlow36));
	double 	fSlow39 = sqrt(((faustpower<2>(fSlow38) / faustpower<2>(fSlow37)) - 1.0));
	double 	fSlow40 = (fSlow38 / fSlow37);
	double 	fSlow41 = (fSlow40 - fSlow39);
	double 	fSlow42 = ((exp((fConst22 / fSlow13)) / fSlow35) - 1);
	double 	fSlow43 = (fSlow35 * ((1.0 + fSlow39) - fSlow40));
	double 	fSlow44 = exp((fConst29 / fSlow0));
	double 	fSlow45 = faustpower<2>(fSlow44);
	double 	fSlow46 = (1.0 - fSlow45);
	double 	fSlow47 = (1.0 - (fSlow4 * fSlow45));
	double 	fSlow48 = sqrt(((faustpower<2>(fSlow47) / faustpower<2>(fSlow46)) - 1.0));
	double 	fSlow49 = (fSlow47 / fSlow46);
	double 	fSlow50 = (fSlow49 - fSlow48);
	double 	fSlow51 = ((exp((fConst29 / fSlow13)) / fSlow44) - 1);
	double 	fSlow52 = (fSlow44 * ((1.0 + fSlow48) - fSlow49));
	double 	fSlow53 = exp((fConst34 / fSlow0));
	double 	fSlow54 = faustpower<2>(fSlow53);
	double 	fSlow55 = (1.0 - fSlow54);
	double 	fSlow56 = (1.0 - (fSlow4 * fSlow54));
	double 	fSlow57 = sqrt(((faustpower<2>(fSlow56) / faustpower<2>(fSlow55)) - 1.0));
	double 	fSlow58 = (fSlow56 / fSlow55);
	double 	fSlow59 = (fSlow58 - fSlow57);
	double 	fSlow60 = ((exp((fConst34 / fSlow13)) / fSlow53) - 1);
	double 	fSlow61 = (fSlow53 * ((1.0 + fSlow57) - fSlow58));
	double 	fSlow62 = exp((fConst39 / fSlow0));
	double 	fSlow63 = faustpower<2>(fSlow62);
	double 	fSlow64 = (1.0 - fSlow63);
	double 	fSlow65 = (1.0 - (fSlow4 * fSlow63));
	double 	fSlow66 = sqrt(((faustpower<2>(fSlow65) / faustpower<2>(fSlow64)) - 1.0));
	double 	fSlow67 = (fSlow65 / fSlow64);
	double 	fSlow68 = (fSlow67 - fSlow66);
	double 	fSlow69 = ((exp((fConst39 / fSlow13)) / fSlow62) - 1);
	double 	fSlow70 = (fSlow62 * ((1.0 + fSlow66) - fSlow67));
	double 	fSlow71 = exp((fConst44 / fSlow0));
	double 	fSlow72 = faustpower<2>(fSlow71);
	double 	fSlow73 = (1.0 - fSlow72);
	double 	fSlow74 = (1.0 - (fSlow72 * fSlow4));
	double 	fSlow75 = sqrt(((faustpower<2>(fSlow74) / faustpower<2>(fSlow73)) - 1.0));
	double 	fSlow76 = (fSlow74 / fSlow73);
	double 	fSlow77 = (fSlow76 - fSlow75);
	double 	fSlow78 = ((exp((fConst44 / fSlow13)) / fSlow71) - 1);
	double 	fSlow79 = (fSlow71 * ((1.0 + fSlow75) - fSlow76));
	double 	fSlow80 = fslider5;
	double 	fSlow81 = pow(10,(0.05 * fslider6));
	double 	fSlow82 = (fConst48 * (fSlow80 / sqrt(fSlow81)));
	double 	fSlow83 = ((1.0 - fSlow82) / (1.0 + fSlow82));
	double 	fSlow84 = ((1 + fSlow83) * (0 - cos((fConst48 * fSlow80))));
	double 	fSlow85 = fslider7;
	double 	fSlow86 = pow(10,(0.05 * fslider8));
	double 	fSlow87 = (fConst48 * (fSlow85 / sqrt(fSlow86)));
	double 	fSlow88 = ((1.0 - fSlow87) / (1.0 + fSlow87));
	double 	fSlow89 = ((1 + fSlow88) * (0 - cos((fConst48 * fSlow85))));
	double 	fSlow90 = (0.0010000000000000009 * fslider9);
	double 	fSlow91 = (0.0010000000000000009 * fslider10);
	for (int i=0; i<count; i++) {
		fRec13[0] = ((fSlow12 * (fRec6[1] + fRec6[2])) + (fSlow11 * fRec13[1]));
		fRec12[0] = ((fSlow15 * (fRec6[1] + (fSlow14 * fRec13[0]))) + (fSlow8 * fRec12[1]));
		fVec0[IOTA&8191] = (1e-20 + (0.35355339059327373 * fRec12[0]));
		double fTemp0 = (double)input0[i];
		fVec1[IOTA&8191] = fTemp0;
		double fTemp1 = (0.3 * fVec1[(IOTA-iSlow16)&8191]);
		double fTemp2 = ((fTemp1 + fVec0[(IOTA-iConst8)&8191]) + (fConst1 * fRec10[1]));
		fVec2[IOTA&2047] = fTemp2;
		fRec10[0] = fVec2[(IOTA-iConst10)&2047];
		double 	fRec11 = (fConst0 * fVec2[IOTA&2047]);
		fRec17[0] = ((fSlow12 * (fRec2[1] + fRec2[2])) + (fSlow11 * fRec17[1]));
		fRec16[0] = ((fSlow25 * (fRec2[1] + (fSlow24 * fRec17[0]))) + (fSlow23 * fRec16[1]));
		fVec3[IOTA&8191] = (1e-20 + (0.35355339059327373 * fRec16[0]));
		double fTemp3 = ((fTemp1 + fVec3[(IOTA-iConst14)&8191]) + (fConst1 * fRec14[1]));
		fVec4[IOTA&1023] = fTemp3;
		fRec14[0] = fVec4[(IOTA-iConst15)&1023];
		double 	fRec15 = (fConst0 * fVec4[IOTA&1023]);
		double fTemp4 = (fRec15 + fRec11);
		fRec21[0] = ((fSlow12 * (fRec4[1] + fRec4[2])) + (fSlow11 * fRec21[1]));
		fRec20[0] = ((fSlow34 * (fRec4[1] + (fSlow33 * fRec21[0]))) + (fSlow32 * fRec20[1]));
		fVec5[IOTA&8191] = (1e-20 + (0.35355339059327373 * fRec20[0]));
		double fTemp5 = ((fVec5[(IOTA-iConst19)&8191] + (fConst1 * fRec18[1])) - fTemp1);
		fVec6[IOTA&2047] = fTemp5;
		fRec18[0] = fVec6[(IOTA-iConst20)&2047];
		double 	fRec19 = (fConst0 * fVec6[IOTA&2047]);
		fRec25[0] = ((fSlow12 * (fRec8[1] + fRec8[2])) + (fSlow11 * fRec25[1]));
		fRec24[0] = ((fSlow43 * (fRec8[1] + (fSlow42 * fRec25[0]))) + (fSlow41 * fRec24[1]));
		fVec7[IOTA&8191] = (1e-20 + (0.35355339059327373 * fRec24[0]));
		double fTemp6 = ((fVec7[(IOTA-iConst24)&8191] + (fConst1 * fRec22[1])) - fTemp1);
		fVec8[IOTA&1023] = fTemp6;
		fRec22[0] = fVec8[(IOTA-iConst25)&1023];
		double 	fRec23 = (fConst0 * fVec8[IOTA&1023]);
		double fTemp7 = (fRec23 + (fRec19 + fTemp4));
		fRec29[0] = ((fSlow12 * (fRec3[1] + fRec3[2])) + (fSlow11 * fRec29[1]));
		fRec28[0] = ((fSlow52 * (fRec3[1] + (fSlow51 * fRec29[0]))) + (fSlow50 * fRec28[1]));
		fVec9[IOTA&16383] = (1e-20 + (0.35355339059327373 * fRec28[0]));
		double fTemp8 = (double)input1[i];
		fVec10[IOTA&8191] = fTemp8;
		double fTemp9 = (0.3 * fVec10[(IOTA-iSlow16)&8191]);
		double fTemp10 = ((fTemp9 + fVec9[(IOTA-iConst31)&16383]) + (fConst27 * fRec26[1]));
		fVec11[IOTA&2047] = fTemp10;
		fRec26[0] = fVec11[(IOTA-iConst32)&2047];
		double 	fRec27 = (fConst26 * fVec11[IOTA&2047]);
		fRec33[0] = ((fSlow12 * (fRec7[1] + fRec7[2])) + (fSlow11 * fRec33[1]));
		fRec32[0] = ((fSlow61 * (fRec7[1] + (fSlow60 * fRec33[0]))) + (fSlow59 * fRec32[1]));
		fVec12[IOTA&8191] = (1e-20 + (0.35355339059327373 * fRec32[0]));
		double fTemp11 = ((fTemp9 + fVec12[(IOTA-iConst36)&8191]) + (fConst27 * fRec30[1]));
		fVec13[IOTA&2047] = fTemp11;
		fRec30[0] = fVec13[(IOTA-iConst37)&2047];
		double 	fRec31 = (fConst26 * fVec13[IOTA&2047]);
		fRec37[0] = ((fSlow12 * (fRec5[1] + fRec5[2])) + (fSlow11 * fRec37[1]));
		fRec36[0] = ((fSlow70 * (fRec5[1] + (fSlow69 * fRec37[0]))) + (fSlow68 * fRec36[1]));
		fVec14[IOTA&16383] = (1e-20 + (0.35355339059327373 * fRec36[0]));
		double fTemp12 = ((fVec14[(IOTA-iConst41)&16383] + (fConst27 * fRec34[1])) - fTemp9);
		fVec15[IOTA&2047] = fTemp12;
		fRec34[0] = fVec15[(IOTA-iConst42)&2047];
		double 	fRec35 = (fConst26 * fVec15[IOTA&2047]);
		fRec41[0] = ((fSlow12 * (fRec9[1] + fRec9[2])) + (fSlow11 * fRec41[1]));
		fRec40[0] = ((fSlow79 * (fRec9[1] + (fSlow78 * fRec41[0]))) + (fSlow77 * fRec40[1]));
		fVec16[IOTA&16383] = (1e-20 + (0.35355339059327373 * fRec40[0]));
		double fTemp13 = ((fVec16[(IOTA-iConst46)&16383] + (fConst27 * fRec38[1])) - fTemp9);
		fVec17[IOTA&1023] = fTemp13;
		fRec38[0] = fVec17[(IOTA-iConst47)&1023];
		double 	fRec39 = (fConst26 * fVec17[IOTA&1023]);
		fRec2[0] = (fRec14[1] + (fRec10[1] + (fRec18[1] + (fRec22[1] + (fRec26[1] + (fRec30[1] + (fRec34[1] + (fRec38[1] + (fRec39 + (fRec35 + (fRec31 + (fRec27 + fTemp7))))))))))));
		fRec3[0] = (0 - ((fRec26[1] + (fRec30[1] + (fRec34[1] + (fRec38[1] + (fRec39 + (fRec35 + (fRec27 + fRec31))))))) - (fRec14[1] + (fRec10[1] + (fRec18[1] + (fRec22[1] + fTemp7))))));
		double fTemp14 = (fRec19 + fRec23);
		fRec4[0] = (0 - ((fRec18[1] + (fRec22[1] + (fRec34[1] + (fRec38[1] + (fRec39 + (fRec35 + fTemp14)))))) - (fRec14[1] + (fRec10[1] + (fRec26[1] + (fRec30[1] + (fRec31 + (fRec27 + fTemp4))))))));
		fRec5[0] = (0 - ((fRec18[1] + (fRec22[1] + (fRec26[1] + (fRec30[1] + (fRec31 + (fRec27 + fTemp14)))))) - (fRec14[1] + (fRec10[1] + (fRec34[1] + (fRec38[1] + (fRec39 + (fRec35 + fTemp4))))))));
		double fTemp15 = (fRec15 + fRec19);
		double fTemp16 = (fRec11 + fRec23);
		fRec6[0] = (0 - ((fRec10[1] + (fRec22[1] + (fRec30[1] + (fRec38[1] + (fRec39 + (fRec31 + fTemp16)))))) - (fRec14[1] + (fRec18[1] + (fRec26[1] + (fRec34[1] + (fRec35 + (fRec27 + fTemp15))))))));
		fRec7[0] = (0 - ((fRec10[1] + (fRec22[1] + (fRec26[1] + (fRec34[1] + (fRec35 + (fRec27 + fTemp16)))))) - (fRec14[1] + (fRec18[1] + (fRec30[1] + (fRec38[1] + (fRec39 + (fRec31 + fTemp15))))))));
		double fTemp17 = (fRec15 + fRec23);
		double fTemp18 = (fRec11 + fRec19);
		fRec8[0] = (0 - ((fRec10[1] + (fRec18[1] + (fRec30[1] + (fRec34[1] + (fRec35 + (fRec31 + fTemp18)))))) - (fRec14[1] + (fRec22[1] + (fRec26[1] + (fRec38[1] + (fRec39 + (fRec27 + fTemp17))))))));
		fRec9[0] = (0 - ((fRec10[1] + (fRec18[1] + (fRec26[1] + (fRec38[1] + (fRec39 + (fRec27 + fTemp18)))))) - (fRec14[1] + (fRec22[1] + (fRec30[1] + (fRec34[1] + (fRec35 + (fRec31 + fTemp17))))))));
		double fTemp19 = (0.37 * (fRec3[0] + fRec4[0]));
		double fTemp20 = (fSlow84 * fRec1[1]);
		fRec1[0] = (0 - (((fSlow83 * fRec1[2]) + fTemp20) - fTemp19));
		double fTemp21 = (fSlow83 * fRec1[0]);
		double fTemp22 = (0.5 * ((fSlow81 * ((fTemp21 + (fRec1[2] + fTemp20)) - fTemp19)) + (fTemp21 + (fTemp20 + (fTemp19 + fRec1[2])))));
		double fTemp23 = (fSlow89 * fRec0[1]);
		fRec0[0] = (0 - (((fSlow88 * fRec0[2]) + fTemp23) - fTemp22));
		double fTemp24 = (fSlow88 * fRec0[0]);
		fRec42[0] = (fSlow90 + (0.999 * fRec42[1]));
		double fTemp25 = (1.0 + fRec42[0]);
		double fTemp26 = (1.0 - (0.5 * fTemp25));
		fRec43[0] = (fSlow91 + (0.999 * fRec43[1]));
		double fTemp27 = pow(10,(0.05 * fRec43[0]));
		output0[i] = (FAUSTFLOAT)(fTemp27 * ((fVec1[IOTA&8191] * fTemp26) + (0.25 * (fTemp25 * ((fSlow86 * ((fTemp24 + (fRec0[2] + fTemp23)) - fTemp22)) + (fTemp24 + (fTemp23 + (fTemp22 + fRec0[2]))))))));
		double fTemp28 = (0.37 * (fRec3[0] - fRec4[0]));
		double fTemp29 = (fSlow84 * fRec45[1]);
		fRec45[0] = (0 - (((fSlow83 * fRec45[2]) + fTemp29) - fTemp28));
		double fTemp30 = (fSlow83 * fRec45[0]);
		double fTemp31 = (0.5 * ((fSlow81 * ((fTemp30 + (fRec45[2] + fTemp29)) - fTemp28)) + (fTemp30 + (fTemp29 + (fTemp28 + fRec45[2])))));
		double fTemp32 = (fSlow89 * fRec44[1]);
		fRec44[0] = (0 - (((fSlow88 * fRec44[2]) + fTemp32) - fTemp31));
		double fTemp33 = (fSlow88 * fRec44[0]);
		output1[i] = (FAUSTFLOAT)(fTemp27 * ((fVec10[IOTA&8191] * fTemp26) + (0.25 * (fTemp25 * ((fSlow86 * ((fTemp33 + (fRec44[2] + fTemp32)) - fTemp31)) + (fTemp33 + (fTemp32 + (fTemp31 + fRec44[2]))))))));
		// post processing
		fRec44[2] = fRec44[1]; fRec44[1] = fRec44[0];
		fRec45[2] = fRec45[1]; fRec45[1] = fRec45[0];
		fRec43[1] = fRec43[0];
		fRec42[1] = fRec42[0];
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
		fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec38[1] = fRec38[0];
		fRec40[1] = fRec40[0];
		fRec41[1] = fRec41[0];
		fRec34[1] = fRec34[0];
		fRec36[1] = fRec36[0];
		fRec37[1] = fRec37[0];
		fRec30[1] = fRec30[0];
		fRec32[1] = fRec32[0];
		fRec33[1] = fRec33[0];
		fRec26[1] = fRec26[0];
		fRec28[1] = fRec28[0];
		fRec29[1] = fRec29[0];
		fRec22[1] = fRec22[0];
		fRec24[1] = fRec24[0];
		fRec25[1] = fRec25[0];
		fRec18[1] = fRec18[0];
		fRec20[1] = fRec20[0];
		fRec21[1] = fRec21[0];
		fRec14[1] = fRec14[0];
		fRec16[1] = fRec16[0];
		fRec17[1] = fRec17[0];
		fRec10[1] = fRec10[0];
		IOTA = IOTA+1;
		fRec12[1] = fRec12[0];
		fRec13[1] = fRec13[0];
	}
}

static int register_params(const ParamReg& reg)
{
	reg.registerVar("zita_rev1.g5.level","Level","S","Output scale factor",&fslider10, -4e+01, -7e+01, 4e+01, 0.1);
	reg.registerVar("zita_rev1.g4.eq2_freq","Eq2 Freq","S","Center-frequency of second-order Regalia-Mitra peaking equalizer section 2",&fslider7, 315.0, 4e+01, 2.5e+03, 1.0);
	reg.registerVar("zita_rev1.g3.eq1_level","Eq1 Level","S","Peak level in dB of second-order Regalia-Mitra peaking equalizer section 1",&fslider6, 0.0, -15.0, 15.0, 0.1);
	reg.registerVar("zita_rev1.g3.eq1_freq","Eq1 Freq","S","Center-frequency of second-order Regalia-Mitra peaking equalizer section 1",&fslider5, 315.0, 4e+01, 2.5e+03, 1.0);
	reg.registerVar("zita_rev1.g1.in_delay","In Delay","S","Delay in ms before reverberation begins",&fslider4, 6e+01, 2e+01, 1e+02, 1.0);
	reg.registerVar("zita_rev1.g2.low_rt60","Low RT60","S","T60 = time (in seconds) to decay 60dB in low-frequency band",&fslider3, 3.0, 1.0, 8.0, 0.1);
	reg.registerVar("zita_rev1.g2.lf_x","LF X","S","Crossover frequency (Hz) separating low and middle frequencies",&fslider2, 2e+02, 5e+01, 1e+03, 1.0);
	reg.registerVar("zita_rev1.g2.hf_damping","HF Damping","S","Frequency (Hz) at which the high-frequency T60 is half the middle-band's T60",&fslider1, 6e+03, 1.5e+03, 2.352e+04, 1.0);
	reg.registerVar("zita_rev1.g2.mid_rt60","Mid RT60","S","T60 = time (in seconds) to decay 60dB in middle band",&fslider0, 2.0, 1.0, 8.0, 0.1);
	reg.registerVar("zita_rev1.g5.dry_wet_mix","Dry/Wet Mix","S","-1 = dry, 1 = wet",&fslider9, 0.0, -1.0, 1.0, 0.01);
	reg.registerVar("zita_rev1.g4.eq2_level","Eq2 Level","S","Peak level in dB of second-order Regalia-Mitra peaking equalizer section 2",&fslider8, 0.0, -15.0, 15.0, 0.1);
	return 0;
}

int load_ui(const UiBuilder& b) {
    b.openVerticalBox("");
    {
	b.openHorizontalBox("");
	{
	    b.create_small_rackknob("zita_rev1.g1.in_delay");
	    b.create_small_rackknob("zita_rev1.g2.lf_x");
	    b.create_small_rackknob("zita_rev1.g2.low_rt60");
	    b.create_small_rackknob("zita_rev1.g2.mid_rt60");
	    b.create_small_rackknob("zita_rev1.g2.hf_damping");
	}
	b.closeBox();
	b.openHorizontalBox("");
	{
	    b.create_small_rackknob("zita_rev1.g3.eq1_freq");
	    b.create_small_rackknob("zita_rev1.g3.eq1_level");
	    b.create_small_rackknob("zita_rev1.g4.eq2_freq");
	    b.create_small_rackknob("zita_rev1.g4.eq2_level");
	    b.create_small_rackknob("zita_rev1.g5.dry_wet_mix");
	    b.create_small_rackknob("zita_rev1.g5.level");
	}
	b.closeBox();
    }
    b.closeBox();
    return 0;
}

static const char* groups[] = {
	"g5", N_("Output"),
	"g4", N_("RM Peaking Equalizer 2"),
	"g3", N_("RM Peaking Equalizer 1"),
	"g2", N_("Decay Times in Bands (see tooltips)"),
	"g1", N_("Input"),
	0
	};

PluginDef plugin = {
    PLUGINDEF_VERSION,
    0,   // flags
    "zita_rev1",  // id
    N_("Zita Rev1"),  // name
    groups,  // groups
    0,  // mono_audio
    compute,  // stereo_audio
    init,  // set_samplerate
    0,  // activate plugin
    register_params,
    load_ui,   // load_ui
    clear_state,  // clear_state
};

extern "C" __attribute__ ((visibility ("default"))) int
get_gx_plugins(int *count, PluginDef **pplugin)
{
    *count = 1;
    *pplugin = &plugin;
    return 0;
}

} // end namespace zita_rev1
