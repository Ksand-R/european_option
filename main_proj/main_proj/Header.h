#pragma once
#include <cmath>
#include <omp.h>
#include <mkl.h>
namespace EU_OP {

	unsigned int	num_Threads;
	int				N; //amount of options 
	int 			version;
	double			time;
	double			start, finish;

	const float		invsqrt2 = 0.707106781f;

	const float		sig = 0.2f; // volatility; percent per year 0.2 -> 20%
	const float		r = 0.05f; // the interest rate; percent per year 0.05 -> 5%
	const float		T = 3.0f; // option execute time (years)
	const float		S0 = 100.0f; // option price at t == 0;
	const float		K = 100.0f; // strike price -- price fixed in option

}