declare name "feed";
import("music.lib"); 


fb_comb (maxdel,N,b0,aN) = (+ <:  delay(maxdel,N),_) ~ *(-aN) : !,*(b0);
rev1(maxdel,N,g) = fb_comb (maxdel,N,1,-g);

allpass_comb(maxdel,N,aN) = (+ <: 
   delay(maxdel,N-1),*(aN)) ~ *(-aN)
   : mem,_ : + ;
rev2(maxlen,len,g) = allpass_comb(maxlen,len,-g);

satrev = *(0.2) <: comb_bank :> allpass_chain <: _,*(-1) with {

  rev1N = rev1;

  rev11(len,g) = rev1N(1024,len,g);
  rev12(len,g) = rev1N(2048,len,g);

  comb_bank = 
    rev11( 778,.827),
    rev11( 901,.805),
    rev11(1011,.783),
    rev12(1123,.764);

  rev2N = rev2;

  allpass_chain = 
    rev2N(128,125,0.7) : 
    rev2N( 64, 42,0.7) : 
    rev2N( 16, 12,0.7);
};
   
//process =  _ : satrev : _,_

process = _ <: _,_;

