#pragma once
#include <cmath>
#include <omp.h>
#include <mkl.h>
#include "Header.h"
using namespace EU_OP;

void V0(float *pT, float *pK, float *pS0, float *pC)
{
	int i;
	float d1, d2, p1, p2;
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