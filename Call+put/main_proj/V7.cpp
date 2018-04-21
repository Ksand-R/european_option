//self_counting_invsqrt
#include "Header.h"

void _V7(float* pT, float* pK, float* pS0, float* pC, float *pP)
{
	int		i;
	float	d1, d2, erf1, erf2;

#pragma simd
	for (i = 0; i < N; i++)
	{
		float tmp = sig2 * pT[i];
		vsInvSqrt(1, &tmp, &invf);
		d1 = (logf(pS0[i] / pK[i]) + (r + sig * sig * 0.5f)
			* pT[i]) * invf;
		d2 = (logf(pS0[i] / pK[i]) + (r - sig * sig * 0.5f)
			* pT[i]) * invf;

		erf1 = 0.5f + 0.5f * erff(d1 * invsqrt2);
		erf2 = 0.5f + 0.5f * erff(d2 * invsqrt2);

		pC[i] = pS0[i] * erf1 - pK[i] * expf((-1.0f) * r * pT[i]) * erf2;
		pP[i] = pC[i] - pS0[i] + pK[i] * expf((-1.0f) * r * pT[i]);
	}
}