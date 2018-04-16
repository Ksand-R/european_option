//using_defined_invsqrt2
#include "Header.h"

void _V6(float* pT, float* pK, float* pS0, float* pC, float *pP)
{
	int		i;
	float	d1, d2, erf1, erf2;

#pragma simd
	for (i = 0; i < N; i++)
	{
		d1 = (logf(pS0[i] / pK[i]) + (r + sig * sig * 0.5f) * pT[i]) / (sig * sqrtf(pT[i]));
		d2 = (logf(pS0[i] / pK[i]) + (r - sig * sig * 0.5f) * pT[i]) / (sig * sqrtf(pT[i]));

		erf1 = 0.5f + 0.5f * erff(d1 * invsqrt2);
		erf2 = 0.5f + 0.5f * erff(d2 * invsqrt2);

		pC[i] = pS0[i] * erf1 - pK[i] * expf((-1.0f) * r * pT[i]) * erf2;
		pP[i] = pK[i] * expf((-1.0) * r * pT[i]) * (1 - erf2) - pS0[i] * (1 - erf1);
	}
}