import("shimmizita.inc");


fsmax = 48000.0;
//For additional description, see .inc file
f1 = hslider("f1", 200, 50, 1000, 1);
t60dc = hslider("t60ds", 3, 1, 8, 0.1);
t60m = hslider("t60m",2, 1, 8, 0.1);
f2 = hslider("f2", 6000, 1500, 0.49*fsmax, 1);
mode = hslider("mode",0, -3, 3, 0.05);
shift = hslider("shift", 0, -6, +6, 0.1); 
envelope = hslider("envelope", 1, 0.1,3, 0.05);
control = hslider("control",0.5, 0, 1, 0.05);
speed = hslider("speed", 0.1, 0.1, 10, 0.05);
depth = hslider("depth", 0, 0, 1, 0.05);
ps_dry_wet = hslider("ps dry wet", 0.5, 0,1, 0.05);  
dry_wet = hslider("dry wet", 0.5, 0,1, 0.05);

process = _,_<:(_,_<:shimmizita_rev_fdn(f1,f2,t60dc,t60m, mode, shift,envelope,control,speed,depth,ps_dry_wet, fsmax):>_,_),_,_:_,X,_:mixer(1 - dry_wet)
with {
	X = (_,_)<:(!,_,_,!);
	mixer(c,x0,y0,x1,y1) = sel(c,x0,y0), sel(c,x1,y1)
	with { 
			sel(c,x,y) = (1-c)*x + c*y; 
		  };
};




