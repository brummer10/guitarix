#include <cmath>
#include <algorithm>
#include "gx_resampler.h"

using std::signbit;

#define max(x, y) (((x) > (y)) ? (x) : (y))
#define min(x, y) (((x) < (y)) ? (x) : (y))

template <int N> inline float faustpower(float x)       {return powf(x, N);}
template <int N> inline double faustpower(double x)     {return pow(x, N);}
template <int N> inline int faustpower(int x) {return faustpower<N/2>(x) * faustpower<N-N/2>(x);}
template <>      inline int faustpower<0>(int x)        {return 1;}
template <>      inline int faustpower<1>(int x)        {return x;}


template<class T> inline T mydsp_faustpower2_f(T x) {return (x * x);}
template<class T> inline T mydsp_faustpower3_f(T x) {return ((x * x) * x);}
template<class T> inline T mydsp_faustpower4_f(T x) {return (((x * x) * x) * x);}
template<class T> inline T mydsp_faustpower5_f(T x) {return ((((x * x) * x) * x) * x);}
template<class T> inline T mydsp_faustpower6_f(T x) {return (((((x * x) * x) * x) * x) * x);}

#define FAUSTFLOAT float
#ifndef N_
#define N_(String) (String)
#endif
#ifndef NC_
#define NC_(Context, String) (String)
#endif

#ifndef GUITARIX_AS_PLUGIN
#define always_inline inline __attribute__((__always_inline__))
#else
#define always_inline inline
#endif

#define FAUSTFLOAT_BUF(buf, len) FAUSTFLOAT *buf=(FAUSTFLOAT*)alloca(sizeof(FAUSTFLOAT)*len)
#define FLOAT_BUF(b,s) float *b=(float*)alloca(sizeof(float)*s)
