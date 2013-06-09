declare id "mbc";
declare name "Multi Band Compressor";
declare shortname "MB Compressor";
declare category "Guitar Effects";
declare description "Multi Band Compressor contributed by kokoko3k";

import("effect.lib");
import("filter.lib");
import("music.lib");

//Mono 
process =   _<: ( gcomp1s , gcomp2s , gcomp3s, gcomp4s, gcomp5s) :>_ with { 
gcomp1s = bandpass1:bypass1(bswitch1,compressor_mono(ratio1,-push1,attack1,release1)):*(Makeup1);
gcomp2s = bandpass2:bypass1(bswitch2,compressor_mono(ratio2,-push2,attack2,release2)):*(Makeup2);
gcomp3s = bandpass3:bypass1(bswitch3,compressor_mono(ratio3,-push3,attack3,release3)):*(Makeup3);
gcomp4s = bandpass4:bypass1(bswitch4,compressor_mono(ratio4,-push4,attack4,release4)):*(Makeup4);
gcomp5s = bandpass5:bypass1(bswitch5,compressor_mono(ratio5,-push5,attack5,release5)):*(Makeup5);
};


sel1         = hslider("Mode1[enum:Compress|Bypass|Mute][tooltip: Compress or Mute the selected band, or Bypass The Compressor]",1,1,3,1);
sel2         = hslider("Mode2[enum:Compress|Bypass|Mute][tooltip: Compress or Mute the selected band, or Bypass The Compressor]",1,1,3,1);
sel3         = hslider("Mode3[enum:Compress|Bypass|Mute][tooltip: Compress or Mute the selected band, or Bypass The Compressor]",1,1,3,1);
sel4         = hslider("Mode4[enum:Compress|Bypass|Mute][tooltip: Compress or Mute the selected band, or Bypass The Compressor]",1,1,3,1);
sel5         = hslider("Mode5[enum:Compress|Bypass|Mute][tooltip: Compress or Mute the selected band, or Bypass The Compressor]",1,1,3,1);

not(x) 	= abs(x-1);
mute1		= not(max(0,sel1-2));
mute2		= not(max(0,sel2-2));
mute3		= not(max(0,sel3-2));
mute4		= not(max(0,sel4-2));
mute5		= not(max(0,sel5-2));

bypass(switch, block) = _ <: select2(switch, _, block);

bswitch1	= max(0,sel1-1);
bswitch2	= max(0,sel2-1);
bswitch3	= max(0,sel3-1);
bswitch4	= max(0,sel4-1);
bswitch5	= max(0,sel5-1);

hifr1			=hslider("crossover_b1_b2 [log][name:Crossover B1-B2 (hz)][tooltip: Crossover bandpass frequency]" ,80 , 20, 20000, 1.08);
lowfr2			=hifr1;
hifr2			=hslider("crossover_b2_b3 [log][name:Crossover B2-B3 (hz)][tooltip: Crossover bandpass frequency]",210,20,20000,1.08);
lowfr3			=hifr2;
hifr3			=hslider("crossover_b3_b4 [log][name:Crossover B3-B4 (hz)][tooltip: Crossover bandpass frequency]",1700,20,20000,1.08);
lowfr4			=hifr3;
hifr4			=hslider("crossover_b4_b5 [log][name:Crossover B4-B5 (hz)][tooltip: Crossover bandpass frequency]",5000,20,20000,1.08);
lowfr5			=hifr4;

bandpass1 	= lowpass(3,hifr1) ;
bandpass2 	= lowpass(3,hifr2) : highpass(3,lowfr2);
bandpass3 	= lowpass(3,hifr3) : highpass(3,lowfr3);
bandpass4 	= lowpass(3,hifr4) : highpass(3,lowfr4);
bandpass5 	= highpass(3,lowfr5);

ratio1 		= hslider("[9] Ratio1 [tooltip: Compression ratio]",2,1,100,0.1);
attack1		= hslider("[A] Attack1 [tooltip: Time before the compressor starts to kick in]", 0.012, 0, 1, 0.001);
release1 	= hslider("[B] Release1 [tooltip: Time before the compressor releases the sound]", 1.25, 0, 10, 0.01);

ratio2 		= hslider("[9] Ratio2 [tooltip: Compression ratio]",2,1,100,0.1);
attack2		= hslider("[A] Attack2 [tooltip: Time before the compressor starts to kick in]", 0.012, 0, 1, 0.001);
release2 	= hslider("[B] Release2 [tooltip: Time before the compressor releases the sound]", 1.25, 0, 10, 0.01);

ratio3 		= hslider("[9] Ratio3 [tooltip: Compression ratio]",2,1,100,0.1);
attack3		= hslider("[A] Attack3 [tooltip: Time before the compressor starts to kick in]", 0.012, 0, 1, 0.001);
release3 	= hslider("[B] Release3 [tooltip: Time before the compressor releases the sound]", 1.25, 0, 10, 0.01);

ratio4 		= hslider("[9] Ratio4 [tooltip: Compression ratio]",2,1,100,0.1);
attack4		= hslider("[A] Attack4 [tooltip: Time before the compressor starts to kick in]", 0.012, 0, 1, 0.001);
release4 	= hslider("[B] Release4 [tooltip: Time before the compressor releases the sound]", 1.25, 0, 10, 0.01);

ratio5 		= hslider("[9] Ratio5 [tooltip: Compression ratio]",2,1,100,0.1);
attack5		= hslider("[A] Attack5 [tooltip: Time before the compressor starts to kick in]", 0.012, 0, 1, 0.001);
release5 	= hslider("[B] Release5 [tooltip: Time before the compressor releases the sound]", 1.25, 0, 10, 0.01);

push1 		= hslider("[5] Makeup1 [tooltip: Post amplification and threshold]"   , 13, -50, +50, 0.1) ; // threshold-=push ;  makeup+=push
push2 		= hslider("[5] Makeup2 [tooltip: Post amplification and threshold]"   , 10, -50, +50, 0.1) ; // threshold-=push ;  makeup+=push
push3 		= hslider("[5] Makeup3 [tooltip: Post amplification and threshold]"   , 4,  -50, +50, 0.1) ; // threshold-=push ;  makeup+=push
push4 		= hslider("[5] Makeup4 [tooltip: Post amplification and threshold]"   , 8,  -50, +50, 0.1) ; // threshold-=push ;  makeup+=push
push5 		= hslider("[5] Makeup5 [tooltip: Post amplification and threshold]"   , 11, -50, +50, 0.1) ; // threshold-=push ;  makeup+=push

safe1 	= hslider("[6] Makeup-Threshold1 [tooltip: Threshold correction, an anticlip measure]" , 2, 0, +10, 0.1) ; // makeup-=safe
safe2 	= hslider("[6] Makeup-Threshold2 [tooltip: Threshold correction, an anticlip measure]" , 2, 0, +10, 0.1) ; // makeup-=safe
safe3 	= hslider("[6] Makeup-Threshold3 [tooltip: Threshold correction, an anticlip measure]" , 2, 0, +10, 0.1) ; // makeup-=safe
safe4 	= hslider("[6] Makeup-Threshold4 [tooltip: Threshold correction, an anticlip measure]" , 2, 0, +10, 0.1) ; // makeup-=safe
safe5 	= hslider("[6] Makeup-Threshold5 [tooltip: Threshold correction, an anticlip measure]" , 2, 0, +10, 0.1) ; // makeup-=safe

Makeup1	=  mute1* (not(bswitch1)*(push1-safe1)  : db2linear : smooth(0.999));
Makeup2	=  mute2* (not(bswitch2)*(push2-safe2)  : db2linear : smooth(0.999));
Makeup3	=  mute3* (not(bswitch3)*(push3-safe3)  : db2linear : smooth(0.999));
Makeup4	=  mute4* (not(bswitch4)*(push4-safe4)  : db2linear : smooth(0.999));
Makeup5	=  mute5* (not(bswitch5)*(push5-safe5)  : db2linear : smooth(0.999));

//Low end headsets: 13,10,4,8,11 (split 80,210,1700,5000)
//Mid-high end headsets: 17,20.5,20,10.5,10 (split 44,180,800,5000)
