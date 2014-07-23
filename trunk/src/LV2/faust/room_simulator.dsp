//Description:
//Based at Gardner's room reverberator models:
//http://fc.mbs.net/~pfisher/fov2-0010016c/fov2-0010016e/fov2-001001a3/book/chapters/24mikelson/index.html
//The values with couple of nines are corrected and differ
//from original implementation
 
import("effect.lib");

//Controls
p_predelay = hslider("Predelay ms[style:knob]",20,1,200,1);
p_rsize = hslider("Room Size[style:knob]", 1, 0, 3, 0.05);
p_rt = hslider("RT[style:knob]", 0.3, 0, 1, 0.05);
p_drw = hslider("dry wet[style:knob]", 0.5, 0, 1,0.05);

//Convert time in ms to samples
ms2sps(x) = x*SR:_*0.001;

//One pole filter
opf(a) = (_+_*(1-a)~@(1)*a); 

//Allpasses
allpass(dt,fb,f_nest) = (+ <: 
   (delay(maxdel,dt-1):f_nest),*(fb)) ~ *(-fb)
   : mem,_ : + 
   with {
   	maxdel = 8192;
   };
   
sn_allpass(dt1,dt2,fb1,fb2) = allpass(dt1,fb1,allpass(dt2,fb2,_));
dn_allpass(dt1,dt2,dt3,fb1,fb2,fb3) = 
	allpass(dt1,fb1,allpass(dt2,fb2,allpass(dt3,fb3,_)));

//Gardners room emulation algorithms
small_room(rt,hf_damping) = lowpass(4,6000):
	((_,_:>@(ms2sps(24)):dn_allpass(ms2sps(35),ms2sps(22),
	ms2sps(8.3),0.15,0.25,0.3)<:	
	sn_allpass(ms2sps(66),ms2sps(30),0.08,0.3),_)~
	(_*1.199:highpass(2,800):lowpass(2,1600):_*rt:opf(hf_damping))):
	_*0.5,_*0.5:>_;

medium_room(rt,hf_damping,x) = x:lowpass(4,6000):
	((_,_:>dn_allpass(ms2sps(35),ms2sps(8.3),ms2sps(22),0.25,0.35,0.45)<:
	@(ms2sps(5)),_*0.5:allpass(ms2sps(30),0.45,_),_:(@(ms2sps(67))<:_,_*0.5),_:
	(@(ms2sps(15)):_*rt),_+_:
	(_*0.4:_+x:sn_allpass(ms2sps(39),ms2sps(9.8),0.25,0.35)),_)~
	(highpass(2,500):lowpass(2,1000):opf(hf_damping):_*rt:_*1.799)):
	_*0.5,_:_+_;

large_room(rt,hf_damping) = lowpass(4,4000):
	((_,_:>allpass(ms2sps(8),0.3,_):allpass(ms2sps(12),0.3,_):
	@(ms2sps(4))<:_,_*1.5:((@(ms2sps(17)):
	sn_allpass(ms2sps(87),ms2sps(62),0.5,0.25):@(ms2sps(31))<:_,_*0.8),_:_,_+_):
	((@(ms2sps(3)):
	dn_allpass(ms2sps(120),ms2sps(76),ms2sps(30),0.5,0.25,0.25)),_))~
	(_*0.5:_*rt:opf(hf_damping):highpass(2,500):lowpass(2,1000):_*1.799)):_+_*0.8;

mix2(c,x,y) = (1-c)*x + c*y; 
mix3(val) = _,_,_<:select3(val),select3(val+1):mix2(val-floor(val));



process = _<:_,(_<:(fdelay1s(ms2sps(p_predelay)):_<:
	small_room(p_rt, 0),medium_room(p_rt, 0),large_room(p_rt, 0):
	mix3(p_rsize):_),_:mix2(1 - p_drw)):select2(checkbox("Effect"));







