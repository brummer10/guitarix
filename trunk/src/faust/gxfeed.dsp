import("stdfaust.lib");
import("guitarix.lib");

fb_combii (maxdel,N,b0,aN) = (+ <:  de.delay(maxdel,N),_) ~ *(-aN) : !,*(b0); 
rev1i(maxdel,N,g) = fb_combii (maxdel,N,1,-g); 
	 
	allpass_combi(maxdel,N,aN) = (+ <:  
	   de.delay(maxdel,N-1),*(aN)) ~ *(-aN) 
	   : mem,_ : + ; 
	rev2i(maxlen,len,g) = allpass_combi(maxlen,len,-g); 
	 
	sat_rev = *(0.2) <: comb_bank :> allpass_chain  with { 
	 
	  rev1N = rev1i; 
 	 
	  rev11(len,g) = rev1N(1024,len,g); 
	  rev12(len,g) = rev1N(2048,len,g); 
	 
	  comb_bank =  
	    rev11( 778,.827), 
	    rev11( 901,.805), 
	    rev11(1011,.783), 
	    rev12(1123,.764); 
	 
	  rev2N = rev2i; 
	 
	  allpass_chain =  
	    rev2N(128,125,0.7) :  
	    rev2N( 64, 42,0.7) :  
	    rev2N( 16, 12,0.7); 
	}; 

wet_dry =  vslider(".amp.wet_dry", 0, -1, 1, 0.01);
//wet_dry = vslider(".amp.wet_dry[name:wet/dry]",  100, 0, 100, 1) : /(100);
//dry = 1 - wet_dry;

switch   = checkbox(".amp.feed_on_off[name:reverb_on_of]");
//s_reverb  = _ <: select2(switch, _, ( _<:*(dry),(*(wet_dry):sat_rev):>_));
s_reverb = select2(switch, _, (wet_dry_mix(wet_dry,sat_rev)));

process =  (s_reverb) <: _,_;

//process = _ <: _,_;
