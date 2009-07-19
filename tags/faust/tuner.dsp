  import("math.lib") ;



  SH(trig,x) = (*(1 - trig) + x * trig) ~ _;
  a = 4.0 ;

  Pitch(a,x) = a * SR / max(M,1) - a * SR * (M == 0)

   with {
   U = (x' < 0) & (x >= 0) ;
   V = +(U) ~ %(int(a)) ;
   W = U & (V == a) ;
   N = (+(1) : *(1 - W)) ~ _ ;
   M = SH(N == 0, N' + 1) ;
         };

result = (12*log(Pitch(a)/440))+57;
process = result;
