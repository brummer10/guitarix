// generated from file '../src/plugins/drumseq.dsp' by dsp2cc:
// Code generated with Faust 0.9.73 (http://faust.grame.fr)




DrumSequencer::DrumSequencer(ParamMap& param_)
	: PluginDef(), 
      Vectom(0),
      Veckick(0),
      Vecsnare(0),
      Vechat(0),
      param(param_),
      tomset(),
      tomp(0),
      snareset(),
      snarep(0),
      hatset(),
      hatp(0),
      kickset(),
      kickp(0),
      plugin() {
	version = PLUGINDEF_VERSION;
	flags = 0;
	id = "seq";
	name = N_("DrumSequencer");
	groups = 0;
	description = N_("Simple Drum Step Sequencer"); // description (tooltip)
	category = N_("Misc");       // category
	shortname = N_("Drum");     // shortname
	mono_audio = compute_static;
	stereo_audio = 0;
	set_samplerate = init_static;
	activate_plugin = 0;
	register_params = register_params_static;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
	plugin = this;
}

DrumSequencer::~DrumSequencer() {
}

inline void DrumSequencer::clear_state_f()
{
	for (int i=0; i<2; i++) iVec0[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) iRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) iRec6[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) iRec12[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<3; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) iRec13[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<3; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) iRec17[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec25[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<64; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<2; i++) fRec27[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fRec30[i] = 0;
	for (int i=0; i<2; i++) fRec31[i] = 0;
	for (int i=0; i<2; i++) fRec28[i] = 0;
	for (int i=0; i<2; i++) fRec29[i] = 0;
	for (int i=0; i<2; i++) fRec34[i] = 0;
	for (int i=0; i<2; i++) fRec35[i] = 0;
	for (int i=0; i<2; i++) fRec32[i] = 0;
	for (int i=0; i<2; i++) fRec33[i] = 0;
	for (int i=0; i<2; i++) fRec38[i] = 0;
	for (int i=0; i<2; i++) fRec39[i] = 0;
	for (int i=0; i<2; i++) fRec36[i] = 0;
	for (int i=0; i<2; i++) fRec37[i] = 0;
	for (int i=0; i<2; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<3; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fRec42[i] = 0;
	for (int i=0; i<2; i++) iRec40[i] = 0;
	for (int i=0; i<2; i++) fRec41[i] = 0;
	for (int i=0; i<3; i++) fRec43[i] = 0;
	for (int i=0; i<2; i++) fRec44[i] = 0;
	for (int i=0; i<2; i++) fVec7[i] = 0;
	for (int i=0; i<2; i++) fRec45[i] = 0;
	for (int i=0; i<2; i++) fRec49[i] = 0;
	for (int i=0; i<3; i++) fRec48[i] = 0;
	for (int i=0; i<2; i++) fVec8[i] = 0;
	for (int i=0; i<2; i++) fRec47[i] = 0;
	for (int i=0; i<3; i++) fRec46[i] = 0;
	for (int i=0; i<2; i++) fRec52[i] = 0;
	for (int i=0; i<2; i++) iRec50[i] = 0;
	for (int i=0; i<2; i++) fRec51[i] = 0;
	for (int i=0; i<2; i++) fRec57[i] = 0;
	for (int i=0; i<2; i++) fRec58[i] = 0;
	for (int i=0; i<2; i++) fRec59[i] = 0;
	for (int i=0; i<2; i++) fRec55[i] = 0;
	for (int i=0; i<2; i++) fRec56[i] = 0;
	for (int i=0; i<2; i++) fRec54[i] = 0;
	for (int i=0; i<3; i++) fRec53[i] = 0;
	for (int i=0; i<2; i++) fRec62[i] = 0;
	for (int i=0; i<2; i++) iRec60[i] = 0;
	for (int i=0; i<2; i++) fRec61[i] = 0;
	for (int i=0; i<2; i++) fRec63[i] = 0;
	for (int i=0; i<2; i++) fVec9[i] = 0;
	for (int i=0; i<2; i++) fRec66[i] = 0;
	for (int i=0; i<2; i++) iRec64[i] = 0;
	for (int i=0; i<2; i++) fRec65[i] = 0;
	for (int i=0; i<2; i++) fRec67[i] = 0;
	for (int i=0; i<2; i++) fRec68[i] = 0;
	for (int i=0; i<2; i++) fRec69[i] = 0;
	for (int i=0; i<2; i++) fRec70[i] = 0;
	for (int i=0; i<2; i++) fRec73[i] = 0;
	for (int i=0; i<2; i++) fRec74[i] = 0;
	for (int i=0; i<2; i++) fRec75[i] = 0;
	for (int i=0; i<2; i++) fVec10[i] = 0;
	for (int i=0; i<2; i++) fRec71[i] = 0;
	for (int i=0; i<2; i++) fRec72[i] = 0;
	for (int i=0; i<2; i++) iRec76[i] = 0;
	for (int i=0; i<2; i++) fRec77[i] = 0;
	for (int i=0; i<2; i++) fRecout[i] = 0;
	seq_size = min_seq_size();
}

void DrumSequencer::clear_state_f_static(PluginDef *p)
{
	static_cast<DrumSequencer*>(p)->clear_state_f();
}

int DrumSequencer::min_seq_size(){
    int i = min(min(Vectom.size(),Veckick.size()),min(Vechat.size(),Vecsnare.size()));
    return i-1;
}

void DrumSequencer::reset_tom() {
	Vectom = tomset.getseqline() ;
	seq_size = min_seq_size();
}

void DrumSequencer::reset_kick() {
	Veckick = kickset.getseqline() ;
	seq_size = min_seq_size();
}

void DrumSequencer::reset_hat() {
	Vechat = hatset.getseqline() ;
	seq_size = min_seq_size();
}

void DrumSequencer::reset_snare() {
	Vecsnare = snareset.getseqline() ;
	seq_size = min_seq_size();
}

inline void DrumSequencer::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = double(iConst0);
	fConst2 = (1.0 / double(int((0.0005 * fConst1))));
	fConst3 = (1 - (1.0 / pow(1e+03,(13.333333333333334 / double(iConst0)))));
	fConst4 = (2e+03 / double(iConst0));
	fConst5 = (1162.3892818282234 / double(iConst0));
	fConst6 = cos(fConst5);
	fConst7 = sin(fConst5);
	fConst8 = (0 - fConst7);
	fConst9 = (1 - (1.0 / pow(1e+03,(18.181818181818183 / double(iConst0)))));
	fConst10 = (2073.4511513692632 / double(iConst0));
	fConst11 = cos(fConst10);
	fConst12 = sin(fConst10);
	fConst13 = (0 - fConst12);
	fConst14 = tan((22116.812281272145 / double(iConst0)));
	fConst15 = (2 * (1 - (1.0 / faustpower<2>(fConst14))));
	fConst16 = (1.0 / fConst14);
	fConst17 = (1 + ((fConst16 - 1.0000000000000004) / fConst14));
	fConst18 = (1.0 / (1 + ((1.0000000000000004 + fConst16) / fConst14)));
	fConst19 = (1 + fConst16);
	fConst20 = (4.656612875245797e-10 / fConst19);
	fConst21 = (0 - ((1 - fConst16) / fConst19));
	fConst22 = (1 - (1.0 / pow(1e+03,(5.0 / double(iConst0)))));
	fConst23 = tan((1643.0529578274618 / double(iConst0)));
	fConst24 = (1.0 / faustpower<2>(fConst23));
	fConst25 = (2 * (1 - fConst24));
	fConst26 = (1.0 / fConst23);
	fConst27 = (1 + ((fConst26 - 1.0000000000000004) / fConst23));
	fConst28 = (1.0 / (1 + ((1.0000000000000004 + fConst26) / fConst23)));
	fConst29 = (0 - fConst26);
	fConst30 = (1 + fConst26);
	fConst31 = (4.656612875245797e-10 / fConst30);
	fConst32 = (0 - ((1 - fConst26) / fConst30));
	fConst33 = (2 * (0 - fConst24));
	fConst34 = (1 - (1.0 / pow(1e+03,(5.46448087431694 / double(iConst0)))));
	fConst35 = (1.0 / double(int((0.1 * fConst1))));
	fConst36 = (3.141592653589793 / double(iConst0));
	fConst37 = (1.6e+03 / fConst1);
	IOTA = 0;
	fConst38 = max((double)0, min((double)2047, (0.0003125 * fConst1)));
	iConst39 = int(fConst38);
	iConst40 = (1 + iConst39);
	iConst41 = int(iConst40);
	fConst42 = (0.00015625 * (fConst38 - iConst39));
	fConst43 = (0.00015625 * (iConst40 - fConst38));
	fConst44 = (4.572399611740729 / double(iConst0));
	fConst45 = cos(fConst44);
	fConst46 = sin(fConst44);
	fConst47 = (0 - fConst46);
	fConst48 = (0.72772 * fConst1);
	fConst49 = (6.283185307179586 / double(iConst0));
	fConst50 = (20.327952464404543 / double(iConst0));
	fConst51 = cos(fConst50);
	fConst52 = sin(fConst50);
	fConst53 = (0 - fConst52);
	fConst54 = (3.235294117647059 * fConst1);
	fConst55 = (326.7256359733385 / double(iConst0));
	fConst56 = cos(fConst55);
	fConst57 = sin(fConst55);
	fConst58 = (0 - fConst57);
	fConst59 = (52.0 * fConst1);
	fConst60 = (1498.2980347889782 / double(iConst0));
	fConst61 = cos(fConst60);
	fConst62 = sin(fConst60);
	fConst63 = (0 - fConst62);
	fConst64 = (238.46153846153845 * fConst1);
	fConst65 = (1.0 / double(int((0.005 * fConst1))));
	fConst66 = (1 - (1.0 / pow(1e+03,(1e+01 / double(iConst0)))));
	fConst67 = (2e+02 / double(iConst0));
	fConst68 = (1.0 / double(iConst0));
	fConst69 = (2.0 / double(iConst0));
	fConst70 = (1.0 / double(int((0.03 * fConst1))));
	fConst71 = tan((1570.7963267948965 / double(iConst0)));
	fConst72 = (1.0 / faustpower<2>(fConst71));
	fConst73 = (2 * (1 - fConst72));
	fConst74 = (1.0 / fConst71);
	fConst75 = (1 + ((fConst74 - 1.0000000000000004) / fConst71));
	fConst76 = (1.0 / (1 + ((1.0000000000000004 + fConst74) / fConst71)));
	fConst77 = (0 - fConst74);
	fConst78 = (1 + fConst74);
	fConst79 = (1.396983862573739e-11 / fConst78);
	fConst80 = (0 - ((1 - fConst74) / fConst78));
	fConst81 = (2 * (0 - fConst72));
	fConst82 = (1.0 / double(int((0.01 * fConst1))));
	fConst83 = (1 - (1.0 / pow(1e+03,fConst68)));
	fConst84 = (1e+02 / double(iConst0));
	fConst85 = tan((3141.592653589793 / double(iConst0)));
	fConst86 = (2 * (1 - (1.0 / faustpower<2>(fConst85))));
	fConst87 = (1.0 / fConst85);
	fConst88 = (1 + ((fConst87 - 1.0000000000000004) / fConst85));
	fConst89 = (1.0 / (1 + ((1.0000000000000004 + fConst87) / fConst85)));
	fConst90 = (31.41592653589793 / double(iConst0));
	fConst91 = cos(fConst90);
	fConst92 = sin(fConst90);
	fConst93 = (0 - fConst92);
	fConst94 = (1.0 / double(int((0.02 * fConst1))));
	fConst95 = (1 + fConst87);
	fConst96 = (1.0 / fConst95);
	fConst97 = (0 - ((1 - fConst87) / fConst95));
	fConst98 = (1 - (1.0 / pow(1e+03,(2.5 / double(iConst0)))));
	fConst99 = (1 - (1.0 / pow(1e+03,fConst84)));
	fConst100 = (565.4866776461628 / double(iConst0));
	fConst101 = cos(fConst100);
	fConst102 = sin(fConst100);
	fConst103 = (0 - fConst102);
	fConst104 = (452.3893421169302 / double(iConst0));
	fConst105 = cos(fConst104);
	fConst106 = sin(fConst104);
	fConst107 = (0 - fConst106);
	fConst108 = (480.66367599923836 / double(iConst0));
	fConst109 = cos(fConst108);
	fConst110 = sin(fConst108);
	fConst111 = (0 - fConst110);
	fConst112 = (0.012345679012345678 * fConst1);
	fConst113 = (162.0 / fConst1);
	fConst114 = (0.012345679012345678 * iConst0);
	counter = 0;
	step = 0;
	fSlow1 = 0.0;
	fSlow3 = 0.0;
	fSlow5 = 0.0;
	fSlow7 = 0.0;
	position = 0.0;
	clear_state_f();
}

void DrumSequencer::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<DrumSequencer*>(p)->init(samplingFreq);
}

void always_inline DrumSequencer::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlow15 = (60/double(fsliderbpm*ftact))*fSamplingFreq;
	double 	fSlow0 = (0.0010000000000000009 * pow(10,(0.05 * double(fslidersnare))));
	double 	fSlow2 = (0.0010000000000000009 * pow(10,(0.05 * double(fsliderhat))));
	double 	fSlow4 = (0.0010000000000000009 * pow(10,(0.05 * double(fsliderkick))));
	double 	fSlow6 = (0.0010000000000000009 * pow(10,(0.05 * double(fslidertom))));
	double 	fSlowgain = (0.0010000000000000009 * pow(10,(0.05 * double(fslidergain))));
		counter = counter+count;
		if (counter >= (int)fSlow15) {
			fSlow1 = double(Vecsnare[step]);
			if ((int)fSlow15 > 4800) {
				fSlow3 = double(Vechat[step]);
			}
			fSlow5 = double(Veckick[step]);
			fSlow7 = double(Vectom[step]);
			counter = 0;
			if (step<seq_size) step = step+1;
			else step = 0;
			double ph1 = 2300.0/seq_size;
			position = fmin(2300,fmax(0,double(step*ph1)));
			//position = double(step);
		} else {
			fSlow1 = 0.0;
			fSlow3 = 0.0;
			fSlow5 = 0.0;
			fSlow7 = 0.0;
		}
	for (int i=0; i<count; i++) {
		fRecout[0] = ((0.999 * fRecout[1]) + fSlowgain);
		iVec0[0] = 1;
		fRec0[0] = ((0.999 * fRec0[1]) + fSlow0);
		fVec1[0] = fSlow1;
		fRec3[0] = ((fRec3[1] + (fSlow1 > fVec1[1])) - (fConst2 * (fRec3[1] > 0.0)));
		int iTemp0 = (fRec3[0] > 0.0);
		int iTemp1 = (iTemp0 > 0);
		iRec1[0] = (iTemp1 & (iRec1[1] | (fRec2[1] >= 1)));
		int iTemp2 = (iTemp0 <= 0);
		int iTemp3 = (iTemp2 & (fRec2[1] > 0));
		fRec2[0] = (((fConst4 * (((iRec1[1] == 0) & iTemp1) & (fRec2[1] < 1))) + (fRec2[1] * (1 - (fConst3 * iTemp3)))) * ((iTemp3 == 0) | (fRec2[1] >= 1e-06)));
		fRec4[0] = ((fConst7 * fRec5[1]) + (fConst6 * fRec4[1]));
		fRec5[0] = ((1 + ((fConst6 * fRec5[1]) + (fConst8 * fRec4[1]))) - iVec0[1]);
		fVec2[0] = 0.25;
		iRec6[0] = (iTemp1 & (iRec6[1] | (fRec7[1] >= 1)));
		int iTemp4 = (iTemp2 & (fRec7[1] > 0));
		fRec7[0] = (((fConst4 * (((iRec6[1] == 0) & iTemp1) & (fRec7[1] < 1))) + (fRec7[1] * (1 - (fConst9 * iTemp4)))) * ((iTemp4 == 0) | (fRec7[1] >= 1e-06)));
		fRec8[0] = ((fConst12 * fRec9[1]) + (fConst11 * fRec8[1]));
		fRec9[0] = ((1 + ((fConst11 * fRec9[1]) + (fConst13 * fRec8[1]))) - iVec0[1]);
		iRec12[0] = (12345 + (1103515245 * iRec12[1]));
		fRec11[0] = ((fConst21 * fRec11[1]) + (fConst20 * (iRec12[0] + iRec12[1])));
		fRec10[0] = (fRec11[0] - (fConst18 * ((fConst17 * fRec10[2]) + (fConst15 * fRec10[1]))));
		iRec13[0] = (iTemp1 & (iRec13[1] | (fRec14[1] >= 1)));
		int iTemp5 = (iTemp2 & (fRec14[1] > 0));
		fRec14[0] = (((fConst4 * (((iRec13[1] == 0) & iTemp1) & (fRec14[1] < 1))) + (fRec14[1] * (1 - (fConst22 * iTemp5)))) * ((iTemp5 == 0) | (fRec14[1] >= 1e-06)));
		fRec16[0] = ((fConst32 * fRec16[1]) + (fConst31 * ((fConst26 * iRec12[0]) + (fConst29 * iRec12[1]))));
		fRec15[0] = (fRec16[0] - (fConst28 * ((fConst27 * fRec15[2]) + (fConst25 * fRec15[1]))));
		iRec17[0] = (iTemp1 & (iRec17[1] | (fRec18[1] >= 1)));
		int iTemp6 = (iTemp2 & (fRec18[1] > 0));
		fRec18[0] = (((fConst4 * (((iRec17[1] == 0) & iTemp1) & (fRec18[1] < 1))) + (fRec18[1] * (1 - (fConst34 * iTemp6)))) * ((iTemp6 == 0) | (fRec18[1] >= 1e-06)));
		fRec19[0] = ((0.999 * fRec19[1]) + fSlow2);
		fVec3[0] = fSlow3;
		int iTemp7 = (fSlow3 > fVec3[1]);
		fRec20[0] = ((fRec20[1] + iTemp7) - (fConst35 * (fRec20[1] > 0.0)));
		double fTemp8 = tan((fConst36 * (12000 - (3000 * fRec20[0]))));
		double fTemp9 = (1.0 / fTemp8);
		double fTemp10 = (1 + ((1.0000000000000004 + fTemp9) / fTemp8));
		double fTemp11 = faustpower<2>(fTemp8);
		double fTemp12 = (1.0 / fTemp11);
		double fTemp13 = (1 + fTemp9);
		fRec25[0] = fmod((fConst37 + fRec25[1]),1);
		double fTemp14 = faustpower<2>(((2 * fRec25[0]) - 1));
		fVec4[0] = fTemp14;
		double fTemp15 = (iVec0[1] * (fVec4[0] - fVec4[1]));
		fVec5[IOTA&63] = fTemp15;
		double fTemp16 = (((0.00015625 * fVec5[IOTA&63]) - (fConst43 * fVec5[(IOTA-iConst39)&63])) - (fConst42 * fVec5[(IOTA-iConst41)&63]));
		fRec26[0] = ((fConst46 * fRec27[1]) + (fConst45 * fRec26[1]));
		fRec27[0] = ((1 + ((fConst45 * fRec27[1]) + (fConst47 * fRec26[1]))) - iVec0[1]);
		double fTemp17 = (fConst49 * (2094.4 + (fConst48 * (fRec26[0] * fTemp16))));
		double fTemp18 = cos(fTemp17);
		double fTemp19 = sin(fTemp17);
		fRec23[0] = ((fRec24[1] * fTemp19) + (fRec23[1] * fTemp18));
		fRec24[0] = ((1 + ((fRec24[1] * fTemp18) + (fRec23[1] * (0 - fTemp19)))) - iVec0[1]);
		fRec30[0] = ((fConst52 * fRec31[1]) + (fConst51 * fRec30[1]));
		fRec31[0] = ((1 + ((fConst51 * fRec31[1]) + (fConst53 * fRec30[1]))) - iVec0[1]);
		double fTemp20 = (fConst49 * (4944.0 + (fConst54 * (fRec30[0] * fTemp16))));
		double fTemp21 = cos(fTemp20);
		double fTemp22 = sin(fTemp20);
		fRec28[0] = ((fRec29[1] * fTemp22) + (fRec28[1] * fTemp21));
		fRec29[0] = ((1 + ((fRec29[1] * fTemp21) + (fRec28[1] * (0 - fTemp22)))) - iVec0[1]);
		fRec34[0] = ((fConst57 * fRec35[1]) + (fConst56 * fRec34[1]));
		fRec35[0] = ((1 + ((fConst56 * fRec35[1]) + (fConst58 * fRec34[1]))) - iVec0[1]);
		double fTemp23 = (fConst49 * (3847.9999999999995 + (fConst59 * (fRec34[0] * fTemp16))));
		double fTemp24 = cos(fTemp23);
		double fTemp25 = sin(fTemp23);
		fRec32[0] = ((fRec33[1] * fTemp25) + (fRec32[1] * fTemp24));
		fRec33[0] = ((1 + ((fRec33[1] * fTemp24) + (fRec32[1] * (0 - fTemp25)))) - iVec0[1]);
		fRec38[0] = ((fConst62 * fRec39[1]) + (fConst61 * fRec38[1]));
		fRec39[0] = ((1 + ((fConst61 * fRec39[1]) + (fConst63 * fRec38[1]))) - iVec0[1]);
		double fTemp26 = (fConst49 * (2144.0 + (fConst64 * (fRec38[0] * fTemp16))));
		double fTemp27 = cos(fTemp26);
		double fTemp28 = sin(fTemp26);
		fRec36[0] = ((fRec37[1] * fTemp28) + (fRec36[1] * fTemp27));
		fRec37[0] = ((1 + ((fRec37[1] * fTemp27) + (fRec36[1] * (0 - fTemp28)))) - iVec0[1]);
		double fTemp29 = (((fRec36[0] + fRec32[0]) + fRec28[0]) + fRec23[0]);
		fVec6[0] = fTemp29;
		fRec22[0] = ((fRec22[1] * (0 - ((1 - fTemp9) / fTemp13))) + (((fVec6[1] * (0 - fTemp9)) + (fVec6[0] / fTemp8)) / fTemp13));
		fRec21[0] = (fRec22[0] - (((fRec21[2] * (1 + ((fTemp9 - 1.0000000000000004) / fTemp8))) + (2 * (fRec21[1] * (1 - fTemp12)))) / fTemp10));
		fRec42[0] = ((iTemp7 + fRec42[1]) - (fConst65 * (fRec42[1] > 0.0)));
		int iTemp30 = (fRec42[0] > 0.0);
		int iTemp31 = (iTemp30 > 0);
		iRec40[0] = (iTemp31 & (iRec40[1] | (fRec41[1] >= 1)));
		int iTemp32 = ((iTemp30 <= 0) & (fRec41[1] > 0));
		fRec41[0] = (((fConst67 * (((iRec40[1] == 0) & iTemp31) & (fRec41[1] < 1))) + (fRec41[1] * (1 - (fConst66 * iTemp32)))) * ((iTemp32 == 0) | (fRec41[1] >= 1e-06)));
		double fTemp33 = (9000 + (6000 * fRec20[0]));
		double fTemp34 = (0 - (3.141592653589793 * fTemp33));
		fRec43[0] = (0 - ((((fRec43[1] * (0 - (fConst69 * fTemp34))) * cos((fConst49 * fTemp33))) + (faustpower<2>((fConst68 * fTemp34)) * fRec43[2])) - fVec6[0]));
		fRec44[0] = ((0.999 * fRec44[1]) + fSlow4);
		fVec7[0] = fSlow5;
		int iTemp35 = (fSlow5 > fVec7[1]);
		fRec45[0] = ((iTemp35 + fRec45[1]) - (fConst70 * (fRec45[1] > 0.0)));
		double fTemp36 = tan((fConst36 * (500 + (5500 * fRec45[0]))));
		double fTemp37 = (1.0 / fTemp36);
		double fTemp38 = (1 + ((1.0000000000000004 + fTemp37) / fTemp36));
		double fTemp39 = (1 + fTemp37);
		fRec49[0] = ((fConst80 * fRec49[1]) + (fConst79 * ((fConst74 * iRec12[0]) + (fConst77 * iRec12[1]))));
		fRec48[0] = (fRec49[0] - (fConst76 * ((fConst75 * fRec48[2]) + (fConst73 * fRec48[1]))));
		double fTemp40 = (((fConst72 * fRec48[0]) + (fConst81 * fRec48[1])) + (fConst72 * fRec48[2]));
		fVec8[0] = fTemp40;
		fRec47[0] = ((fRec47[1] * (0 - ((1 - fTemp37) / fTemp39))) + (fConst76 * ((fVec8[0] + fVec8[1]) / fTemp39)));
		fRec46[0] = (fRec47[0] - (((fRec46[2] * (1 + ((fTemp37 - 1.0000000000000004) / fTemp36))) + (2 * (fRec46[1] * (1 - (1.0 / faustpower<2>(fTemp36)))))) / fTemp38));
		fRec52[0] = ((iTemp35 + fRec52[1]) - (fConst82 * (fRec52[1] > 0.0)));
		int iTemp41 = (fRec52[0] > 0.0);
		int iTemp42 = (iTemp41 > 0);
		iRec50[0] = (iTemp42 & (iRec50[1] | (fRec51[1] >= 1)));
		int iTemp43 = ((iTemp41 <= 0) & (fRec51[1] > 0));
		fRec51[0] = (((fConst84 * (((iRec50[1] == 0) & iTemp42) & (fRec51[1] < 1))) + (fRec51[1] * (1 - (fConst83 * iTemp43)))) * ((iTemp43 == 0) | (fRec51[1] >= 1e-06)));
		fRec57[0] = ((fConst92 * fRec58[1]) + (fConst91 * fRec57[1]));
		fRec58[0] = ((1 + ((fConst91 * fRec58[1]) + (fConst93 * fRec57[1]))) - iVec0[1]);
		fRec59[0] = ((fRec59[1] + iTemp35) - (fConst94 * (fRec59[1] > 0.0)));
		double fTemp44 = (fConst49 * ((50 * (1 + fRec59[0])) + (19.23076923076923 * fRec57[0])));
		double fTemp45 = cos(fTemp44);
		double fTemp46 = sin(fTemp44);
		fRec55[0] = ((fRec56[1] * fTemp46) + (fRec55[1] * fTemp45));
		fRec56[0] = ((1 + ((fRec56[1] * fTemp45) + (fRec55[1] * (0 - fTemp46)))) - iVec0[1]);
		fRec54[0] = ((fConst97 * fRec54[1]) + (fConst96 * (fRec55[0] + fRec55[1])));
		fRec53[0] = (fRec54[0] - (fConst89 * ((fConst88 * fRec53[2]) + (fConst86 * fRec53[1]))));
		fRec62[0] = ((iTemp35 + fRec62[1]) - (fConst65 * (fRec62[1] > 0.0)));
		int iTemp47 = (fRec62[0] > 0.0);
		int iTemp48 = (iTemp47 > 0);
		iRec60[0] = (iTemp48 & (iRec60[1] | (fRec61[1] >= 1)));
		int iTemp49 = ((iTemp47 <= 0) & (fRec61[1] > 0));
		fRec61[0] = (((fConst67 * (((iRec60[1] == 0) & iTemp48) & (fRec61[1] < 1))) + (fRec61[1] * (1 - (fConst98 * iTemp49)))) * ((iTemp49 == 0) | (fRec61[1] >= 1e-06)));
		fRec63[0] = ((0.999 * fRec63[1]) + fSlow6);
		fVec9[0] = fSlow7;
		fRec66[0] = ((fRec66[1] + (fSlow7 > fVec9[1])) - (fConst65 * (fRec66[1] > 0.0)));
		int iTemp50 = (fRec66[0] > 0.0);
		int iTemp51 = (iTemp50 > 0);
		iRec64[0] = (iTemp51 & (iRec64[1] | (fRec65[1] >= 1)));
		int iTemp52 = (iTemp50 <= 0);
		int iTemp53 = (iTemp52 & (fRec65[1] > 0));
		fRec65[0] = (((fConst67 * (((iRec64[1] == 0) & iTemp51) & (fRec65[1] < 1))) + (fRec65[1] * (1 - (fConst99 * iTemp53)))) * ((iTemp53 == 0) | (fRec65[1] >= 1e-06)));
		fRec67[0] = ((fConst102 * fRec68[1]) + (fConst101 * fRec67[1]));
		fRec68[0] = ((1 + ((fConst101 * fRec68[1]) + (fConst103 * fRec67[1]))) - iVec0[1]);
		fRec69[0] = ((fConst106 * fRec70[1]) + (fConst105 * fRec69[1]));
		fRec70[0] = ((1 + ((fConst105 * fRec70[1]) + (fConst107 * fRec69[1]))) - iVec0[1]);
		fRec73[0] = ((fConst110 * fRec74[1]) + (fConst109 * fRec73[1]));
		fRec74[0] = ((1 + ((fConst109 * fRec74[1]) + (fConst111 * fRec73[1]))) - iVec0[1]);
		fRec75[0] = fmod((1.0 + fRec75[1]),fConst112);
		double fTemp54 = faustpower<2>(((fConst113 * fRec75[0]) - 1.0));
		fVec10[0] = fTemp54;
		double fTemp55 = (fConst49 * ((fConst114 * (fVec2[1] * (fVec10[0] - fVec10[1]))) + (58.84615384615384 * fRec73[0])));
		double fTemp56 = cos(fTemp55);
		double fTemp57 = sin(fTemp55);
		fRec71[0] = ((fRec72[1] * fTemp57) + (fRec71[1] * fTemp56));
		fRec72[0] = ((1 + ((fRec72[1] * fTemp56) + (fRec71[1] * (0 - fTemp57)))) - iVec0[1]);
		iRec76[0] = (iTemp51 & (iRec76[1] | (fRec77[1] >= 1)));
		int iTemp58 = (iTemp52 & (fRec77[1] > 0));
		fRec77[0] = (((fConst67 * (((iRec76[1] == 0) & iTemp51) & (fRec77[1] < 1))) + (fRec77[1] * (1 - (fConst98 * iTemp58)))) * ((iTemp58 == 0) | (fRec77[1] >= 1e-06)));
		output0[i] = (FAUSTFLOAT)((double)input0[i] + ((2 * ((((0.25 * (fRec77[0] * ((5 * fRec71[0]) + (0.5 * (fRec69[0] + fRec67[0]))))) + (3 * fRec65[0])) * fRec63[0]) + (((((fConst89 * (fRec61[0] * (fRec53[2] + (fRec53[0] + (2 * fRec53[1]))))) + ((fRec51[0] * (fRec46[2] + (fRec46[0] + (2 * fRec46[1])))) / fTemp38)) * fRec44[0]) + (0.5 * (((fRec41[0] * (fRec43[0] - fRec43[2])) + ((sqrt(fRec41[0]) * (((fRec21[0] / fTemp11) + (2 * (fRec21[1] * (0 - fTemp12)))) + (fRec21[2] / fTemp11))) / fTemp10)) * fRec19[0]))) + (0.1 * (((fConst28 * (fRec18[0] * (((fConst24 * fRec15[0]) + (fConst33 * fRec15[1])) + (fConst24 * fRec15[2])))) + ((fConst18 * (fRec14[0] * (fRec10[2] + (fRec10[0] + (2 * fRec10[1]))))) + ((5.0 * ((0.25 + fRec8[0]) * fRec7[0])) + (5.0 * ((0.25 + fRec4[0]) * fRec2[0]))))) * fRec0[0]))))) * fRecout[0]));
		// post processing
		fRec77[1] = fRec77[0];
		iRec76[1] = iRec76[0];
		fRec72[1] = fRec72[0];
		fRec71[1] = fRec71[0];
		fVec10[1] = fVec10[0];
		fRec75[1] = fRec75[0];
		fRec74[1] = fRec74[0];
		fRec73[1] = fRec73[0];
		fRec70[1] = fRec70[0];
		fRec69[1] = fRec69[0];
		fRec68[1] = fRec68[0];
		fRec67[1] = fRec67[0];
		fRec65[1] = fRec65[0];
		iRec64[1] = iRec64[0];
		fRec66[1] = fRec66[0];
		fVec9[1] = fVec9[0];
		fRec63[1] = fRec63[0];
		fRec61[1] = fRec61[0];
		iRec60[1] = iRec60[0];
		fRec62[1] = fRec62[0];
		fRec53[2] = fRec53[1]; fRec53[1] = fRec53[0];
		fRec54[1] = fRec54[0];
		fRec56[1] = fRec56[0];
		fRec55[1] = fRec55[0];
		fRec59[1] = fRec59[0];
		fRec58[1] = fRec58[0];
		fRec57[1] = fRec57[0];
		fRec51[1] = fRec51[0];
		iRec50[1] = iRec50[0];
		fRec52[1] = fRec52[0];
		fRec46[2] = fRec46[1]; fRec46[1] = fRec46[0];
		fRec47[1] = fRec47[0];
		fVec8[1] = fVec8[0];
		fRec48[2] = fRec48[1]; fRec48[1] = fRec48[0];
		fRec49[1] = fRec49[0];
		fRec45[1] = fRec45[0];
		fVec7[1] = fVec7[0];
		fRec44[1] = fRec44[0];
		fRec43[2] = fRec43[1]; fRec43[1] = fRec43[0];
		fRec41[1] = fRec41[0];
		iRec40[1] = iRec40[0];
		fRec42[1] = fRec42[0];
		fRec21[2] = fRec21[1]; fRec21[1] = fRec21[0];
		fRec22[1] = fRec22[0];
		fVec6[1] = fVec6[0];
		fRec37[1] = fRec37[0];
		fRec36[1] = fRec36[0];
		fRec39[1] = fRec39[0];
		fRec38[1] = fRec38[0];
		fRec33[1] = fRec33[0];
		fRec32[1] = fRec32[0];
		fRec35[1] = fRec35[0];
		fRec34[1] = fRec34[0];
		fRec29[1] = fRec29[0];
		fRec28[1] = fRec28[0];
		fRec31[1] = fRec31[0];
		fRec30[1] = fRec30[0];
		fRec24[1] = fRec24[0];
		fRec23[1] = fRec23[0];
		fRec27[1] = fRec27[0];
		fRec26[1] = fRec26[0];
		IOTA = IOTA+1;
		fVec4[1] = fVec4[0];
		fRec25[1] = fRec25[0];
		fRec20[1] = fRec20[0];
		fVec3[1] = fVec3[0];
		fRec19[1] = fRec19[0];
		fRec18[1] = fRec18[0];
		iRec17[1] = iRec17[0];
		fRec15[2] = fRec15[1]; fRec15[1] = fRec15[0];
		fRec16[1] = fRec16[0];
		fRec14[1] = fRec14[0];
		iRec13[1] = iRec13[0];
		fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		iRec12[1] = iRec12[0];
		fRec9[1] = fRec9[0];
		fRec8[1] = fRec8[0];
		fRec7[1] = fRec7[0];
		iRec6[1] = iRec6[0];
		fVec2[1] = fVec2[0];
		fRec5[1] = fRec5[0];
		fRec4[1] = fRec4[0];
		fRec2[1] = fRec2[0];
		iRec1[1] = iRec1[0];
		fRec3[1] = fRec3[0];
		fVec1[1] = fVec1[0];
		fRec0[1] = fRec0[0];
		fRecout[1] = fRecout[0];
		iVec0[1] = iVec0[0];
	}
}
		
void __rt_func DrumSequencer::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<DrumSequencer*>(p)->compute(count, input0, output0);
}

int DrumSequencer::register_par(const ParamReg& reg)
{
	reg.registerVar("seq.bpm","","S",N_("Beats per Minute"),&fsliderbpm, 120, 24, 360, 1);
	reg.registerVar("seq.hat_closed.dsp.Gain","","S",N_("Volume level in decibels"),&fsliderhat, -2e+01, -6e+01, 4e+01, 0.1);
	reg.registerVar("seq.kick.dsp.Gain","","S",N_("Volume level in decibels"),&fsliderkick, -2e+01, -6e+01, 4e+01, 0.1);
	reg.registerVar("seq.snare.dsp.Gain","","S",N_("Volume level in decibels"),&fslidersnare, -2e+01, -6e+01, 4e+01, 0.1);
	reg.registerVar("seq.tom.dsp.Gain","","S",N_("Volume level in decibels"),&fslidertom, -2e+01, -6e+01, 4e+01, 0.1);
    static const value_pair ftact_values[] = {{"1/4"},{"2/4"},{"3/4"},{"4/4"},{0}};
    reg.registerEnumVar("seq.tact","","S",N_("select tact"),ftact_values,&ftact, 4.0, 1.0, 4.0, 1.0);
    reg.registerVar("seq.asequences","","S",N_("Number of Sequences"),&fsec, 24.0, 24.0, 240.0, 4.0);
	reg.registerVar("seq.gain","","S",N_("Volume level in decibels"),&fslidergain, 0.0, -6e+01, 4e+01, 0.1);
    reg.registerNonMidiFloatVar("seq.pos",&position, false, true, 0.0, 0.0, 2300.0, 1.0);
	for (int i=0; i<24; i++) Vectom.push_back(0);
	for (int i=0; i<24; i++) Veckick.push_back(0);
	for (int i=0; i<24; i++) Vechat.push_back(0);
	for (int i=0; i<24; i++) Vecsnare.push_back(0);
    tomp = SeqParameter::insert_param(param, "seq.sequencer.tom", &tomset);
    snarep = SeqParameter::insert_param(param, "seq.sequencer.snare", &snareset);
    hatp = SeqParameter::insert_param(param, "seq.sequencer.hat", &hatset);
    kickp = SeqParameter::insert_param(param, "seq.sequencer.kick", &kickset);
    tomp->signal_changed().connect(
	sigc::hide(
	    sigc::mem_fun(this, &DrumSequencer::reset_tom)));
    snarep->signal_changed().connect(
	sigc::hide(
	    sigc::mem_fun(this, &DrumSequencer::reset_snare)));
    hatp->signal_changed().connect(
	sigc::hide(
	    sigc::mem_fun(this, &DrumSequencer::reset_hat)));
    kickp->signal_changed().connect(
	sigc::hide(
	    sigc::mem_fun(this, &DrumSequencer::reset_kick)));
	
	return 0;
}

int DrumSequencer::register_params_static(const ParamReg& reg)
{
	return static_cast<DrumSequencer*>(reg.plugin)->register_par(reg);
}

void DrumSequencer::del_instance(PluginDef *p)
{
	delete static_cast<DrumSequencer*>(p);
}

