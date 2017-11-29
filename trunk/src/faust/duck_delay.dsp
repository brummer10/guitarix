declare id   "duckDelay";
declare name "Duck Delay";
declare category "Echo / Delay";

//------------------------------------
//Inspired by:
//http://www.gvst.co.uk/gduckdly.htm
//Axe-FX II Owner's manual:5.6
//------------------------------------

//------------------------------------
//Description:
//The delayed signal added to output dependent of input signal amplitude. 
//If the input signal is high. The delayed signall turned off, and vise versa.
//The switching controlled by envelope follower 
//(parameters: "attack", "release", and main - "amount", what controls envelope follower influence).
//
//Parameters description:
//time - de.delay time in milliseconds 
//feedback - de.delay feedback
//attack, release - envelope follower time in seconds controls
//amount dB - envelope follower influence
//------------------------------------

import("stdfaust.lib");

//Constrols
p_time = hslider("time[name:Delay]", 500, 1, 2000, 1):si.smooth(ba.tau2pole(0.1));
p_feedback = hslider("feedback[name:Feedback]", 0, 0, 1, 0.05);
p_attack_time = hslider("attack[name:Attack]", 0.1, 0.05, 0.5, 0.05);
p_release_time = hslider("relese[name:Release]", 0.1, 0.05, 2, 0.05);
p_amount = hslider("amount[name:Amount]", 0.5, 0,56, 0.05):ba.db2linear;

//Consts
c_channels_sw_time = 0.1;
c_fdelay_max_len = 393216;

get_delay_length(x) = x*ma.SR:_*0.001;

process = _<:
	_,(_<:(_+_:de.fdelay(c_fdelay_max_len,get_delay_length(p_time)))~_*p_feedback,		
	(an.amp_follower_ud(p_attack_time,p_release_time):_*p_amount:_>1:(1 - _):
	si.smooth(ba.tau2pole(c_channels_sw_time)))):_,_*_
	:>_;
