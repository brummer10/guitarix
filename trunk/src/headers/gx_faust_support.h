#include <cmath>

#define max(x, y) (((x) > (y)) ? (x) : (y))
#define min(x, y) (((x) < (y)) ? (x) : (y))

// FIXME (temporary)hack to support older compiler versions
inline float  pow(float b, float e)   {return ::powf(b, e);}
inline double pow(double b, double e) {return ::pow(b, e);}
inline double pow(double b, int e)    {return ::pow(b, static_cast<double>(e));}
inline double pow(int b, double e)    {return ::pow(static_cast<double>(b), e);}
inline double pow(double b, float e)  {return ::pow(b, static_cast<double>(e));}
inline double pow(float b, double e)  {return ::pow(static_cast<double>(b), e);}
inline float  pow(float b, int e)     {return ::powf(b, static_cast<float>(e));}
inline float  pow(int b, float e)     {return ::powf(static_cast<float>(b),  e);}

template <int N> inline float faustpower(float x)       {return powf(x, N);}
template <int N> inline double faustpower(double x)     {return pow(x, N);}
template <int N> inline int faustpower(int x) {return faustpower<N/2>(x) * faustpower<N-N/2>(x);}
template <>      inline int faustpower<0>(int x)        {return 1;}
template <>      inline int faustpower<1>(int x)        {return x;}

#define FAUSTFLOAT float
