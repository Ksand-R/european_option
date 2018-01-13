#include "Header.h"
void _V0(float *pT, float *pK, float *pS0, float *pC)
{

	for (i = 0; i < N; i++)
	{
		d1 = (log(pS0[i] / pK[i]) + (r + sig * sig * 0.5) *
			pT[i]) / (sig * sqrt(pT[i]));
		d2 = (log(pS0[i] / pK[i]) + (r - sig * sig * 0.5) *
			pT[i]) / (sig * sqrt(pT[i]));
		vsCdfNorm(1, &d1, &p1);
		vsCdfNorm(1, &d2, &p2);
		pC[i] = pS0[i] * p1 - pK[i] *
			exp((-1.0) * r * pT[i]) * p2;
	}
}

