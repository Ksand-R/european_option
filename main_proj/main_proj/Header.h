#ifndef ___EU_OP___
#define ___EU_OP___
#include <math.h>
#include <omp.h>
#include <mkl.h>

namespace EU_OP {
	int		num_Threads;
	int		N; //amount of options 
	int 	version;
	double	_time;
	double	start, finish;

	const float		invsqrt2 = 0.707106781f;
	const float		sig = 0.2f; // volatility; percent per year 0.2 -> 20%
	const float		r = 0.05f; // the interest rate; percent per year 0.05 -> 5%
	const float		T = 3.0f; // option execute time (years)
	const float		S0 = 100.0f; // option price at t == 0;
	const float		K = 100.0f; // strike price -- price fixed in option

	void _V0(float *pT, float *pK, float *pS0, float *pC);
	void _V1(float *pT, float *pK, float *pS0, float *pC);
	void _V2(float *pT, float *pK, float *pS0, float *pC);
	void _V3(float* restrict pT, float* restrict pK, float* restrict pS0, float* restrict pC);
	void _V4(float *pT, float *pK, float *pS0, float *pC);
	void _V5(float *pT, float *pK, float *pS0, float *pC);
	void _V6(float *pT, float *pK, float *pS0, float *pC);
	void _V7(float *pT, float *pK, float *pS0, float *pC);
	void _V8(float *pT, float *pK, float *pS0, float *pC);

}

#endif // !___EU_OP___