// Copyright 2018 Romanov Alexander

#include "include/call_put_versions.h"

//base_version

void _V0(float *pT, float *pK, float *pS0, float *pC, float *pP)
{

	for (i = 0; i < N; i++)
	{
		d1 = (log(pS0[i] / pK[i]) + (r + sig * sig * 0.5) *
			pT[i]) / (sig * sqrt(pT[i]));
		d2 = (log(pS0[i] / pK[i]) + (r - sig * sig * 0.5) *
			pT[i]) / (sig * sqrt(pT[i]));
		 vsCdfNorm(1, &d1, &p1);
		 vsCdfNorm(1, &d2, &p2);

		pC[i] = pS0[i] * p1 - pK[i] * exp((-1.0) * r * pT[i]) * p2;
		pP[i] = pC[i] - pS0[i] + pK[i] * exp((-1.0) * r * pT[i]);
	}
}

//fp

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

		pC[i] = pS0[i] * p1 - pK[i] * expf((-1.0f) * r * pT[i]) * p2;
		pP[i] = pC[i] - pS0[i] + pK[i] * expf((-1.0f) * r * pT[i]);
	}
}

//erf

void _V2(float *pT, float *pK, float *pS0, float *pC, float *pP)
{

	for (i = 0; i < N; i++)
	{
		d1 = (logf(pS0[i] / pK[i]) + (r + sig * sig * 0.5f) *
			pT[i]) / (sig * sqrtf(pT[i]));
		d2 = (logf(pS0[i] / pK[i]) + (r - sig * sig * 0.5f) *
			pT[i]) / (sig * sqrtf(pT[i]));

		erf1 = 0.5f + 0.5f * erff(d1 / sqrtf(2.0f));
		erf2 = 0.5f + 0.5f * erff(d2 / sqrtf(2.0f));

		pC[i] = pS0[i] * erf1 - pK[i] * expf((-1.0f) * r * pT[i]) * erf2;
		pP[i] = pC[i] - pS0[i] + pK[i] * expf((-1.0f) * r * pT[i]);	
	}
}

//restrict

void _V3(float* restrict pT, float* restrict pK, float* restrict pS0, float* restrict pC, float* restrict pP)
{

	for (i = 0; i < N; i++)
	{
		d1 = (logf(pS0[i] / pK[i]) + (r + sig * sig * 0.5f) *
			pT[i]) / (sig * sqrtf(pT[i]));
		d2 = (logf(pS0[i] / pK[i]) + (r - sig * sig * 0.5f) *
			pT[i]) / (sig * sqrtf(pT[i]));

		erf1 = 0.5f + 0.5f * erff(d1 / sqrtf(2.0f));
		erf2 = 0.5f + 0.5f * erff(d2 / sqrtf(2.0f));
		
		pC[i] = pS0[i] * erf1 - pK[i] * expf((-1.0f) * r * pT[i]) * erf2;
		pP[i] = pC[i] - S0[i] + pK[i] * expf((-1.0f) * r * pT[i]);
	}
}

//fp_simd_vector_always

void _V4(float *pT, float *pK, float *pS0, float *pC, float *pP)
{

	#pragma simd
	#pragma vector always	
	for (i = 0; i < N; i++)
	{
		d1 = (logf(pS0[i] / pK[i]) + (r + sig * sig * 0.5f) *
			pT[i]) / (sig * sqrtf(pT[i]));
		d2 = (logf(pS0[i] / pK[i]) + (r - sig * sig * 0.5f) *
			pT[i]) / (sig * sqrtf(pT[i]));

		vsCdfNorm(1, &d1, &p1);
		vsCdfNorm(1, &d2, &p2);
		pC[i] = pS0[i] * p1 - pK[i] * expf((-1.0f) * r * pT[i]) * p2;
		pP[i] = pC[i] - pS0[i] + pK[i] * expf((-1.0f) * r * pT[i]);
	}
}

//fp_erf_simd_vector_always

void _V5(float* pT, float* pK, float* pS0, float* pC, float *pP)
{

	#pragma simd
	#pragma vector always
	for (i = 0; i < N; i++)
	{
		d1 = (logf(pS0[i] / pK[i]) + (r + sig * sig * 0.5f) *
			pT[i]) / (sig * sqrtf(pT[i]));
		d2 = (logf(pS0[i] / pK[i]) + (r - sig * sig * 0.5f) *
			pT[i]) / (sig * sqrtf(pT[i]));
		erf1 = 0.5f + 0.5f * erff(d1 / sqrtf(2.0f));
		erf2 = 0.5f + 0.5f * erff(d2 / sqrtf(2.0f));
		
		pC[i] = pS0[i] * erf1 - pK[i] * expf((-1.0f) * r * pT[i]) * erf2;
		pP[i] = pC[i] - pS0[i] + pK[i] * expf((-1.0f) * r * pT[i]);
	}
}

//using_defined_invsqrt2

void _V6(float* pT, float* pK, float* pS0, float* pC, float *pP)
{

#pragma simd
	for (i = 0; i < N; i++)
	{
		d1 = (logf(pS0[i] / pK[i]) + (r + sig * sig * 0.5f) * pT[i]) / (sig * sqrtf(pT[i]));
		d2 = (logf(pS0[i] / pK[i]) + (r - sig * sig * 0.5f) * pT[i]) / (sig * sqrtf(pT[i]));

		erf1 = 0.5f + 0.5f * erff(d1 * invsqrt2);
		erf2 = 0.5f + 0.5f * erff(d2 * invsqrt2);

		pC[i] = pS0[i] * erf1 - pK[i] * expf((-1.0f) * r * pT[i]) * erf2;
		pP[i] = pC[i] - pS0[i] + pK[i] * expf((-1.0f) * r * pT[i]);
	}
}

//omp

void _V8(float *pT, float *pK, float *pS0, float *pC, float *pP)
{

#pragma simd
#pragma omp parallel for private(invf, d1, d2, erf1, erf2)
	for (i = 0; i < N; i++)
	{
		d1 = (logf(pS0[i] / pK[i]) + (r + sig * sig * 0.5f) *
			pT[i]) / (sig * sqrtf(pT[i]));
		d2 = (logf(pS0[i] / pK[i]) + (r - sig * sig * 0.5f) *
			pT[i]) / (sig * sqrtf(pT[i]));

		erf1 = 0.5f + 0.5f * erff(d1 / sqrtf(2.0f));
		erf2 = 0.5f + 0.5f * erff(d2 / sqrtf(2.0f));

		pC[i] = pS0[i] * erf1 - pK[i] * expf((-1.0f) * r * pT[i]) * erf2;
		pP[i] = pC[i] - pS0[i] + pK[i] * expf((-1.0f) * r * pT[i]);
	}
}

//omp_nontemporal

void _V9(float *pT, float *pK, float *pS0, float *pC, float *pP)
{

#pragma simd 
#pragma vector nontemporal
#pragma omp parallel for private(d1, d2, erf1, erf2)
	for (i = 0; i < N; i++)
	{
		d1 = (logf(pS0[i] / pK[i]) + (r + sig * sig * 0.5f) *
			pT[i]) / (sig * sqrtf(pT[i]));
		d2 = (logf(pS0[i] / pK[i]) + (r - sig * sig * 0.5f) *
			pT[i]) / (sig * sqrtf(pT[i]));

		erf1 = 0.5f + 0.5f * erff(d1 / sqrtf(2.0f));
		erf2 = 0.5f + 0.5f * erff(d2 / sqrtf(2.0f));

		pC[i] = pS0[i] * erf1 - pK[i] * expf((-1.0f) * r * pT[i]) * erf2;
		pP[i] = pC[i] - pS0[i] + pK[i] * expf((-1.0f) * r * pT[i]);
	}
}