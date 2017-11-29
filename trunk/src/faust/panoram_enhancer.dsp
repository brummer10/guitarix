declare id   "panoram_enhancer";
declare name "Panoram Enhancer";
declare shortname "Panoram";
declare category "Misc";

//------------------------------------
//Based at:
//ECE542 T. Tran; Rice University; Spring 2005
//"Title: Stereo Enhancement Algorithm"
//------------------------------------

import("stdfaust.lib");

//Controls
delay_width = hslider("Delay width[name:Delay][tooltip:Delay Width]",0,0,1,0.01):si.smooth(0.999);
freq_width = hslider("Frequency width[name:Frequency][tooltip:Frequency Width]",0,0,1,0.01);

//Constants
dt_max_const = 65536; //Max length of all de.delay lines, to provide 200 ms at 192 kHz
dt_max = 0.2 * ma.SR; //Real max length, 200 ms 
filters_order = 6; //Filters order in filter-banks
fmain = 1800; //Main filter fhi
f1 = 3600; f2 = 6400; f3 = 20000; //Border freqs of filters in filter-banks
freq_shift = 1500; //Filters freq difference between filter-banks
fbank_coef_gap = 0.6; //Filters in filter-banks gain coefs min value

//Random changed values emulation
rv1 = _; rv2 = _*0.7; rv3 = _ + 0.3:sqrt(_);
rv4 = _*3.14:sin; rv5 = _*1.23:cos; rv6 = _+9:log10; 

pa_filter(dt,flo,fhi,coef) = de.fdelay(dt_max_const,dt):fi.highpass(filters_order,flo):fi.lowpass(filters_order,fhi):_*coef;   

gain_coef = _*(1 - fbank_coef_gap):_+fbank_coef_gap;

pa_filter_bank1(delay_width,filter_width) = _<: 			
	pa_filter(dt_max:rv1:_*delay_width,fmain,f1,freq_width:rv5:gain_coef),
	pa_filter(dt_max:rv3:_*delay_width,f1,f2, freq_width:rv2:gain_coef),
	pa_filter(dt_max:rv2:_*delay_width,f2,f3, freq_width:rv4:gain_coef)
	:>_;

pa_filter_bank2(delay_width,filter_width) = _<: 			
	pa_filter(dt_max:rv5:_*delay_width,fmain - freq_shift*freq_width,f1 - freq_shift*freq_width,freq_width:rv3:gain_coef),
	pa_filter(dt_max:rv1:_*delay_width,f1 - freq_shift*freq_width,f2 - freq_shift*freq_width,freq_width:rv4:gain_coef),
	pa_filter(dt_max:rv6:_*delay_width,f2 - freq_shift*freq_width,f3 - freq_shift*freq_width,freq_width:rv2:gain_coef)
	:>_;

process = _,_<:
	pa_filter_bank1(delay_width,freq_width),
	(_,_:(_*0.5,_*0.5:>fi.lowpass(4,fmain))<:_,_),
	pa_filter_bank2(delay_width,freq_width)
	:>_,_;
