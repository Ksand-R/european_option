#include "Header.h"
int		num_Threads;
int		N; //amount of options 
int 		version;
double	_time;
double	start, finish;

const float		invsqrt2 = 0.707106781f;
const float		sig = 0.2f; // volatility; percent per year 0.2 -> 20%
const float		r = 0.05f; // the interest rate; percent per year 0.05 -> 5%
const float		T = 3.0f; // option execute time (years)
const float		S0 = 100.0f; // option price at t == 0;
const float		K = 100.0f; // strike price -- price fixed in option

int		i;
float	d1, d2, erf1, erf2;
float	sig2 = sig * sig;
float	invf;
float	p1, p2;

GetPrices option_array[9] =
{
	_V0, //preference 1
	_V1, //preference 2
	_V2, //erf
	//_V3, //restrict
	_V4, //#pragma simd #pragma vector always
	_V5, //#pragma simd invsqrt2_1
	_V6, //#pragma simd invsqrt2_2
	_V7, //#pragma simd #pragma omp parallel for private
	_V8  // _V7 + #pragma vector nontemporal
};

