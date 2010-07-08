//tonestack selector

declare name 		"amp.tonestack";

import("music.lib");
import("filter.lib");
import("effect.lib"); 


/****************************************************************
 ** Guitar tone stacks
 ** values from CAPS plugin tonestack (based on work from D.T. Yeh
 */
 
ts = environment {
    k = *(1e3);
    M = *(1e6);
    nF = *(1e-9);
    pF = *(1e-12);

    /* Fender */

    bassman = environment { /* 59 Bassman 5F6-A */
	R1 = 250:k;
        R2 = 1:M;
        R3 = 25:k;
        R4 = 56:k;
        C1 = 250:pF;
        C2 = 20:nF;
        C3 = 20:nF;
        };

    twin = environment { /* 69 Twin Reverb AA270 */
	R1 = 250:k;
        R2 = 250:k;
        R3 = 10:k;
        R4 = 100:k;
        C1 = 120:pF;
        C2 = 100:nF;
        C3 = 47:nF;
        };

    princeton = environment { /* 64 Princeton AA1164 */
	R1 = 250:k;
        R2 = 250:k;
        R3 = 4.8:k;
        R4 = 100:k;
        C1 = 250:pF;
        C2 = 100:nF;
        C3 = 47:nF;
        };

    /* Marshall */

    jcm800 = environment { /* 59/81 JCM-800 Lead 100 2203 */
	R1 = 220:k;
        R2 = 1:M;
        R3 = 22:k;
        R4 = 33:k;
        C1 = 470:pF;
        C2 = 22:nF;
        C3 = 22:nF;
        };
    /* 90 JCM-900 Master 2100: same as JCM-800 */

    jcm2000 = environment { /* 81 2000 Lead */
	R1 = 250:k;
        R2 = 1:M;
        R3 = 25:k;
        R4 = 56:k; /* a 10 k fixed + 100 k pot in series actually */
        C1 = 500:pF;
        C2 = 22:nF;
        C3 = 22:nF;
        };

	/* parameter order is R1 - R4, C1 - C3 */
    mlead = environment { /* 67 Major Lead 200 */
	R1 = 250:k;
        R2 = 1:M;
        R3 = 25:k;
        R4 = 33:k;
        C1 = 500:pF;
        C2 = 22:nF;
        C3 = 22:nF;
        };

    m2199 = environment { /* undated M2199 30W solid state */
        R1 = 250:k;
        R2 = 250:k;
        R3 = 25:k;
        R4 = 56:k;
        C1 = 250:pF;
        C2 = 47:nF;
        C3 = 47:nF;
        };

    /* Vox */
    ac30 = environment { /* 59/86 AC-30 */
        /* R3 is fixed (circuit differs anyway) */
        R1 = 1:M;
        R2 = 1:M;
        R3 = 10:k;
        R4 = 100:k;
        C1 = 50:pF;
        C2 = 22:nF;
        C3 = 22:nF;
        };
};

   t = vslider("Treble", 0.5, 0, 1, 0.01);
   m = vslider("Middle", 0.5, 0, 1, 0.01);
   l = vslider("Bass", 0.5, 0, 1, 0.01) : (_-1)*3.4 : exp;

tonestack(tse) = 1/A0*tf3(B0,B1,B2,B3,A1/A0,A2/A0,A3/A0) with {
    C1 = tse.C1;
    C2 = tse.C2;
    C3 = tse.C3;
    R1 = tse.R1;
    R2 = tse.R2;
    R3 = tse.R3;
    R4 = tse.R4;

    b1 = t*C1*R1 + m*C3*R3 + l*(C1*R2 + C2*R2) + (C1*R3 + C2*R3);

    b2 = t*(C1*C2*R1*R4 + C1*C3*R1*R4) - m*m*(C1*C3*R3*R3 + C2*C3*R3*R3)
         + m*(C1*C3*R1*R3 + C1*C3*R3*R3 + C2*C3*R3*R3)
         + l*(C1*C2*R1*R2 + C1*C2*R2*R4 + C1*C3*R2*R4)
         + l*m*(C1*C3*R2*R3 + C2*C3*R2*R3)
         + (C1*C2*R1*R3 + C1*C2*R3*R4 + C1*C3*R3*R4);

    b3 = l*m*(C1*C2*C3*R1*R2*R3 + C1*C2*C3*R2*R3*R4)
         - m*m*(C1*C2*C3*R1*R3*R3 + C1*C2*C3*R3*R3*R4)
         + m*(C1*C2*C3*R1*R3*R3 + C1*C2*C3*R3*R3*R4)
         + t*C1*C2*C3*R1*R3*R4 - t*m*C1*C2*C3*R1*R3*R4
         + t*l*C1*C2*C3*R1*R2*R4;

    a0 = 1;

    a1 = (C1*R1 + C1*R3 + C2*R3 + C2*R4 + C3*R4)
         + m*C3*R3 + l*(C1*R2 + C2*R2);

    a2 = m*(C1*C3*R1*R3 - C2*C3*R3*R4 + C1*C3*R3*R3 + C2*C3*R3*R3)
         + l*m*(C1*C3*R2*R3 + C2*C3*R2*R3)
         - m*m*(C1*C3*R3*R3 + C2*C3*R3*R3)
         + l*(C1*C2*R2*R4 + C1*C2*R1*R2 + C1*C3*R2*R4 + C2*C3*R2*R4)
         + (C1*C2*R1*R4 + C1*C3*R1*R4 + C1*C2*R3*R4 + C1*C2*R1*R3 + C1*C3*R3*R4 + C2*C3*R3*R4);

    a3 = l*m*(C1*C2*C3*R1*R2*R3 + C1*C2*C3*R2*R3*R4)
         - m*m*(C1*C2*C3*R1*R3*R3 + C1*C2*C3*R3*R3*R4)
         + m*(C1*C2*C3*R3*R3*R4 + C1*C2*C3*R1*R3*R3 - C1*C2*C3*R1*R3*R4)
         + l*C1*C2*C3*R1*R2*R4
         + C1*C2*C3*R1*R3*R4;

    c = 2*float(SR);

    B0 = -b1*c - b2*pow(c,2) - b3*pow(c,3);
    B1 = -b1*c + b2*pow(c,2) + 3*b3*pow(c,3);
    B2 = b1*c + b2*pow(c,2) - 3*b3*pow(c,3);
    B3 = b1*c - b2*pow(c,2) + b3*pow(c,3);
    A0 = -a0 - a1*c - a2*pow(c,2) - a3*pow(c,3);
    A1 = -3*a0 - a1*c + a2*pow(c,2) + 3*a3*pow(c,3);
    A2 = -3*a0 + a1*c + a2*pow(c,2) - 3*a3*pow(c,3);
    A3 = -a0 + a1*c - a2*pow(c,2) + a3*pow(c,3);
};


aba = environment {
	 sl = hslider("select[enum:default|Bassman|Twin Reverb|Princeton|JCM-800|JCM-2000|M-Lead|M2199|AC-30|Off]",1,0,9,1);
	 a = min(2, max(0,sl)); 
	 b = min(2, max(0,sl-1)); 
	 c = min(2, max(0,sl-2));
	 d = min(2, max(0,sl-3));
	 e = min(2, max(0,sl-4));
	 f = min(2, max(0,sl-5));
	 g = min(2, max(0,sl-6));
	 h = min(2, max(0,sl-7));
	 x = min(2, max(0,sl-8));
};



process  = hgroup("tonestack",_<: a <: b <: c <: d <: e<: f <: g <:h :>_) with { 
	 a = select3(aba.a,N,A,_) ; 
	 b = select3(aba.b,_,B:*(1.5),_); //add a bit gain
	 c = select3(aba.c,_,C:*(1.5),_); //add a bit gain
	 d = select3(aba.d,_,D,_); 
	 e = select3(aba.e,_,E,_);
	 f = select3(aba.f,_,F,_);
	 g = select3(aba.g,_,G,_);
	 h = select3(aba.h,_,H,_);
	 x = select3(aba.x,_,X,_);
}

 with {
		N = component("tone.dsp").tone((l*20)-10,(m*10)-5,(t*20)-10);
		A = tonestack(ts.bassman);
		B = tonestack(ts.twin);
		C = tonestack(ts.princeton);
		D = tonestack(ts.jcm800);
		E = tonestack(ts.jcm2000);
		F = tonestack(ts.mlead);
		G = tonestack(ts.m2199);
		H = tonestack(ts.ac30);
		X = _;
};
