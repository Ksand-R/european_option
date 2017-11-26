#pragma once
#include <mkl.h>
#include "Header.h"
using namespace EU_OP;

void _V1(float *pT, float *pK, float *pS0, float *pC)
{
	int i;
	float d1, d2, p1, p2;
	for (i = 0; i < N; i++)
	{
		d1 = (logf(pS0[i] / pK[i]) + (r + sig * sig * 0.5f) *
			pT[i]) / (sig * sqrtf(pT[i]));
		d2 = (logf(pS0[i] / pK[i]) + (r - sig * sig * 0.5f) *
			pT[i]) / (sig * sqrtf(pT[i]));

		vsCdfNorm(1, &d1, &p1);
		vsCdfNorm(1, &d2, &p2);
		pC[i] = pS0[i] * p1 - pK[i] *
			expf((-1.0f) * r * pT[i]) * p2;
	}
}
