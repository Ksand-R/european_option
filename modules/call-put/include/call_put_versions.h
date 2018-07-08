// Copyright 2018 Romanov Alexander

#ifndef ___EU_OP_CALL_PUT___
#define ___EU_OP_CALL_PUT___

#include  <omp.h>
#include <mkl.h>
#include <cmath>

extern int		num_Threads;
extern int		N; //amount of options 
extern int 		version;
extern double	_time;
extern double	start, finish;

extern const float		invsqrt2;
extern const float		sig; // volatility; percent per year 0.2 -> 20%
extern const float		r; // the interest rate; percent per year 0.05 -> 5%
extern const float		T; // option execute time (years)
extern const float		S0; // option price at t == 0;
extern const float		K; // strike price -- price fixed in option

extern int		i;
extern float	d1, d2, erf1, erf2, erf3, erf4;
extern float	sig2;
extern float	invf;
extern float	p1, p2;


void _V0(float *pT, float *pK, float *pS0, float *pC, float *pP);
void _V1(float *pT, float *pK, float *pS0, float *pC, float *pP);
void _V2(float *pT, float *pK, float *pS0, float *pC, float *pP);
void _V3(float* restrict pT, float* restrict pK, float* restrict pS0, float* restrict pC, float *pP);
void _V4(float *pT, float *pK, float *pS0, float *pC, float *pP);
void _V5(float *pT, float *pK, float *pS0, float *pC, float *pP);
void _V6(float *pT, float *pK, float *pS0, float *pC, float *pP);
void _V8(float *pT, float *pK, float *pS0, float *pC, float *pP);
void _V9(float *pT, float *pK, float *pS0, float *pC, float *pP);


typedef void(*GetPrices)(float *pT, float *pK, float *pS0, float *pC, float *pP);

extern GetPrices option_array[9];

#endif // !___EU_OP_CALL_PUT___