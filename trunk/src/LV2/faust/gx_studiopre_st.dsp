// Yet another tube preamp experiment
// So far so good :
// Bright bypass must not do fi.zero division
// Look at actual gain of tube stages in real preamp
// and maybe adjust stage1 outpu to reflect as at present with gain at 0dB get very
// little distortion/overload
// Also look at relative loss in tonestack  
// stage1 gain is 30dB-35dB in reality
// tonestack takes around 12dB off in central position
// So stage1 effectively should boost by 18-23dB but in effect does only 3dB
// So to accuratley model the overload of next stage would need a boost of around
// 15-20dB at this point x 5.6 -> x10
// Would then need to attenuate final output to compensate ( actual preamp has 60dB gain! )

import("stdfaust.lib"); 
import("guitarix.lib");

//  Based on simple Alembic F-2B vstudio preamp
//  2 sectionos of 12AX7 together with tonestack and volume
// This is an identical circuit apart from coupling caps whcih could do with filters
// 1st cathode cap gives aroudn 2Hz !
// Coupling cap sat end gives cutoff 1.6Hz!
// So only reason to do is to eliminate low frequency rubbish

//studiopre = stage1:*(10):tone:volume:*(0.1) with{
studiopre( tone, gain ) = stage1:*(10):tone:gain:stage2:*(0.3334) with{
//studiopre = volume with{
	stage1 = tubestage(TB_12AX7_68k,2.1,1500.0,1.204541) ; // Gain 2.9   2nd -29.8 3rd -26.24
	stage2 = tubestage(TB_12AX7_250k,2.1,1500.0,1.204285) ; //  Gain 2.41 2nd -34.34 3rd -23.36

};

process =studiopre( tone_l,gain_l),studiopre(tone_r, gain_r) with{
//process =studiopre( tone_l,volume_l) with{
	volume_l =  vslider("Volume_L[alias][style:knob]",5,0,10,0.1)/10; 
	volume_r =  vslider("Volume_R[alias][style:knob]",5,0,10,0.1)/10; 
	// In actuall amp is Fender/marshall type B/M/T tone set
	// Look at adding tonestack in dsp.
	// Does not work for stereo as the slider are predefined
	// need to find a way of loadin 2
	tstack_l = component("tonestack.dsp");
	tone_l = tstack_l[tse=tstack_l.ts.fender_default;
t = vslider("Treble_L[alias]", 0.5, 0, 1, 0.01);
m = vslider("Middle_L[alias]", 0.5, 0, 1, 0.01);
l = vslider("Bass_L[alias]", 0.5, 0, 1, 0.01) : (_-1)*3.4 : exp;
] ;
	tstack_r = component("tonestack.dsp");
	tone_r = tstack_r[tse=tstack_r.ts.fender_default;
t = vslider("Treble_R[alias]", 0.5, 0, 1, 0.01);
m = vslider("Middle_R[alias]", 0.5, 0, 1, 0.01);
l = vslider("Bass_R[alias]", 0.5, 0, 1, 0.01) : (_-1)*3.4 : exp;
] ;
	// Attempt bright switch - bypass high frequencies around gain control
	// Important that this may only work up to 0dB
	// Note tried to emulate actual circuit so cutoff frequency varies with volume pot
	// In effect -3dB is when reactance of capacitor equals pot value
	// use equation freq = 160/( gain * 0.12 ) yo get -3dB cutoff
	// Assuming 1M pot and 120pF cap
	// Must avoid div by fi.zero
	// Seems to cause pros when gain less than 0.1
	freq_l = 160/(0.12 * ( volume_l+0.1) );
	bright_l = *(checkbox("bright_l")):fi.highpass( 1, freq_l  ) ;
	gain_l  = _<:bright_l,*(volume_l):>_ ;
	freq_r = 160/(0.12 * ( volume_r+0.1) );
	bright_r = *(checkbox("bright_r")):fi.highpass( 1, freq_r  ) ;
	gain_r  = _<:bright_r,*(volume_r):>_ ;
};
