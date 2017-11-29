declare id  	"dattorros_progenitor";
declare name "Plate Reverb";
declare category "Reverb";

//------------------------------------
//Based at:
//Effect Design Part 1: Reverberator and Other Filters
//JON DATTORRO, AES Member
//CCRMA, Stanford University, Stanford, CA, USA
//------------------------------------

import("stdfaust.lib");

import("guitarix.lib");

//Controls
max_predelay_ms = 200;
predelay = hslider("predelay ms[name:Predelay]", 0, 0, max_predelay_ms, 10);
excursion = hslider("excursion[name:Excursion]", 0, 0, 16, 0.5);
decay = hslider("decay[name:Decay]", 0.1, 0, 0.5, 0.01);
decay_diffusion1 = hslider("decay diff 1[name:Decay 1]", 0.1, 0, 0.7, 0.01);
decay_diffusion2 = hslider("decay diff 2[name:Decay 2]", 0.1, 0, 0.5, 0.01);
input_diffusion1 = hslider("input diff 1[name:Input 1]", 0.1, 0, 0.75, 0.01);
input_diffusion2 = hslider("input diff 2[name:Input 2]", 0.1, 0, 0.625, 0.01);
bandwidth = hslider("bandwidth[name:Bandwidth]", 0.9, 0.1, 0.95, 0.0005);
damping = hslider("damping[name:HF Damp]", 0.0005, 0.1, 0.95, 0.0005);
dry_wet = hslider("dry/wet[name:Dry/Wet]", 0.5, 0, 1, 0.05);

//Will be moved to .lib
X = (_,_)<:(!,_,_,!);
mixer(c,x0,y0,x1,y1) = sel(c,x0,y0), sel(c,x1,y1)
	with { 
			sel(c,x,y) = (1-c)*x + c*y; 
		  };

//Consts
orig_sr = 29761.0; //Original sample rate, described in paper

//Correct de.delay lines according sample rate
get_length(x) = x/orig_sr:_*ma.SR:int;
get_predelay_length(x) = x*ma.SR:_*0.001;

input_chain(predelay, bw, input_diffusion1, input_diffusion2) = 
	(_+_)*0.5: de.sdelay(int(2^18), 100*ma.SR/1000.0, get_predelay_length(predelay)):opf(bw):
	allpass_filter(get_length(142),input_diffusion1):allpass_filter(get_length(107),input_diffusion1):
	allpass_filter(get_length(379),input_diffusion2):allpass_filter(get_length(277),input_diffusion2);

left_branch(excursion,decay_diffusion1,damping,decay,decay_diffusion2) = 
	_*0.5+_*0.3:allpass_with_fdelay(get_length(656),decay_diffusion1,17,0.5*(os.osc(1)+1)*excursion)<:@(get_length(4453)),_:
	opf(damping),_:_*decay,_:allpass_filter(get_length(1800),decay_diffusion2),_:@(get_length(3720)),_:_*decay,_;

right_branch(excursion,decay_diffusion1,damping,decay,decay_diffusion2) =			  									  	   
	_*0.5+_*0.3:allpass_with_fdelay(get_length(892),decay_diffusion1,17,0.5*(os.osc(1)+1)*excursion)<:@(get_length(4217)),_:
	opf(damping),_:_*decay,_:allpass_filter(get_length(2656),decay_diffusion2),_:@(get_length(3163)),_:_*decay,_;

process = _,_<:
	(_,(input_chain(predelay,1 - bandwidth, input_diffusion1,input_diffusion2)<:_,_),_):>	   			    
	(_,(_,X,_:(left_branch(excursion,decay_diffusion1,damping,decay,decay_diffusion2),
	right_branch(excursion,decay_diffusion1,damping,decay,decay_diffusion2)):_,X,_)~X),_:_,_,X,_,_:
	_,(_,_:>_),(_,_:>_),_:X,_,_:mixer(1 - dry_wet);
