#pragma once
#include "Header.h"
using namespace EU_OP;

void _V6(float* pT, float* pK, float* pS0, float* pC)
{
	int		i;
	float	d1, d2, erf1, erf2;
	float	sig2 = sig * sig;
	float	invf;

#pragma simd
	for (i = 0; i < N; i++)
	{
		invf = 0.;// invsqrtf(sig2 * pT[i]);
		d1 = (logf(pS0[i] / pK[i]) + (r + sig * sig * 0.5f) 
			* pT[i]) / (sig * invf);
		d2 = (logf(pS0[i] / pK[i]) + (r - sig * sig * 0.5f) 
			* pT[i]) / (sig * invf);
		erf1 = 0.5f + 0.5f * erff(d1 * invsqrt2);
		erf2 = 0.5f + 0.5f * erff(d2 * invsqrt2);
		pC[i] = pS0[i] * erf1 - pK[i] * expf((-1.0f) * r * pT[i]) * erf2;
	}
}
