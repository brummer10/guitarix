declare id   "duckDelaySt";
declare name "Duck Delay St";
declare category "Echo / Delay";

//------------------------------------
//Description:
//The delayed signal added to output dependent of input signal amplitude. 
//If the input signal is high. The delayed signall turned off, and vise versa.
//The switching controlled by envelope follower 
//(parameters: "attack", "release", and main - "amount", what is controls envelope follower influence).
//
//Parameters description:
//time - de.delay time in milliseconds 
//feedback - de.delay feedback
//pingpong - changes feedback character
//coloration - LP/HP coloration filter
//attack, release - envelope follower time in seconds controls
//amount dB - envelope follower influence
//effect - amplitude of effect signal in mix
//------------------------------------

import("stdfaust.lib");

//Constrols
p_time = hslider("time[name:Delay]", 500, 1, 2000, 1):si.smooth(ba.tau2pole(0.1));
p_feedback = hslider("feedback[name:Feedback]", 0, 0, 1, 0.05);
p_pingpong = hslider("pingpong[name:Ping Pong]", 0, 0, 1, 0.05);
coloration = hslider("coloration[name:Coloration]", 0, -1, 1, 0.05);

p_attack_time = hslider("attack[name:Attack]", 0.1, 0.05, 0.5, 0.05);
p_release_time = hslider("release[name:Release]", 0.1, 0.05, 2, 0.05);
p_amount = hslider("amount[name:Amount]", 0.5, 0,56, 0.05):ba.db2linear;

p_effect = hslider("effect[name:Effect]", 0, -16, +4, 0.1) : ba.db2linear : si.smooth(0.999);

//Consts
c_fdelay_max_len = 393216;
c_channels_sw_time = 0.1;

//Funcs
X = (_,_)<:(!,_,_,!);
get_delay_length(x) = x*ma.SR:_*0.001;
coloration_filter(coloration) = _<:(fi.lowshelf(5,(1 - coloration)*12,440),
	fi.highshelf(5,coloration*12,880)):>_*ba.db2linear(-15);

pp_delay(time,fb_coef,pp_fb_coef) = _,_*(1 - pp_fb_coef):
	(_,X,_:(X:(pp_fb_delay(time, fb_coef,pp_fb_coef))),
	(X:(pp_fb_delay(time, fb_coef,pp_fb_coef))):_,_)~X
	:>_,_
with {
	pp_fb_delay(time,fb_coef,pp_fb_coef) = _+_*pp_fb_coef:
	(_+_:de.fdelay(c_fdelay_max_len,get_delay_length(p_time)))~_*fb_coef;
};

switcher(att, rel, amount) = an.amp_follower_ud(att,rel):
	_*amount:_>1:(1 - _):
	si.smooth(ba.tau2pole(c_channels_sw_time));

process = (_<:_,_,_),(_<:_,_,_):
	_,
	switcher(p_attack_time, p_release_time, p_amount),
	(pp_delay(p_time,p_feedback*(1 - p_pingpong),p_pingpong*p_feedback):
	coloration_filter(coloration),coloration_filter(coloration)),
	switcher(p_attack_time, p_release_time, p_amount),
	_:
	_,_*_,_*_,_:(_,_*p_effect:>_),(_*p_effect,_:>_);
