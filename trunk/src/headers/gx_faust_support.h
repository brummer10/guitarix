#include <cmath>

#define max(x, y) (((x) > (y)) ? (x) : (y))
#define min(x, y) (((x) < (y)) ? (x) : (y))

template <int N> inline float faustpower(float x)       {return powf(x, N);}
template <int N> inline double faustpower(double x)     {return pow(x, N);}
template <int N> inline int faustpower(int x) {return faustpower<N/2>(x) * faustpower<N-N/2>(x);}
template <>      inline int faustpower<0>(int x)        {return 1;}
template <>      inline int faustpower<1>(int x)        {return x;}

#define FAUSTFLOAT float
#ifndef N_
#define N_(String) (String)
#endif
#ifndef NC_
#define NC_(Context, String) (String)
#endif

#define always_inline inline __attribute__((__always_inline__))
