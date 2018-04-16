//fp
#include "Header.h"

void _V1(float *pT, float *pK, float *pS0, float *pC, float *pP)
{

	for (i = 0; i < N; i++)
	{
		d1 = (logf(pS0[i] / pK[i]) + (r + sig * sig * 0.5f) *
			pT[i]) / (sig * sqrtf(pT[i]));
		d2 = (logf(pS0[i] / pK[i]) + (r - sig * sig * 0.5f) *
			pT[i]) / (sig * sqrtf(pT[i]));

		vsCdfNorm(1, &d1, &p1);
		vsCdfNorm(1, &d2, &p2);

		pC[i] = pS0[i] * p1 - pK[i] * expf((-1.0) * r * pT[i]) * p2;
		pP[i] = pK[i] * expf((-1.0) * r * pT[i]) * (1 - p2) - pS0[i] * (1 - p1);	
	}
}
