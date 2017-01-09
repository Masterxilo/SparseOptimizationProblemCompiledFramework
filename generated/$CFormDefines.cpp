#define sqrt sqrtf
#define pow powf

#define assertNonzero(x) assertNonzero_((x), #x)
#define rsqrt(x) (1. / sqrt(assertNonzero((x))))
#define inv(x) (1. / assertNonzero((x)))

#define neg(x) (-(x))
#define times(x,y) ((x)*(y))
#define plus(x,y) ((x)+(y))

#define greater(x,y) ((x)>(y))
#define less(x,y) ((x)<(y))
#define greaterEqual(x,y) ((x)>=(y))
#define lessEqual(x,y) ((x)>=(y))
#define equal(x,y) ((x)==(y))

#define and(x,y) ((x)&&(y))
#define or(x,y) ((x)||(y))

#define ifthenelse(test,a,b) ((test) ? (a) : (b))

template<typename T1, typename T2>
inline
#ifdef __CUDACC__
__host__ __device__
#endif
float max(T1 a, T2 b) { return a > b ? a : b; }


template<typename T1, typename T2>
inline
#ifdef __CUDACC__
__host__ __device__
#endif
float min(T1 a, T2 b) { return a < b ? a : b; }
