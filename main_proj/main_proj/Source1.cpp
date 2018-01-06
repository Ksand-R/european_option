//#include "Header.h"
//#include <mkl.h>
//#include <math.h>
//#include <omp.h>
//
//
//
//void _V0(float *pT, float *pK, float *pS0, float *pC)
//{
//	int i;
//	float d1, d2, p1, p2;
//	for (i = 0; i < N; i++)
//	{
//		d1 = (log(pS0[i] / pK[i]) + (r + sig * sig * 0.5) *
//			pT[i]) / (sig * sqrt(pT[i]));
//		d2 = (log(pS0[i] / pK[i]) + (r - sig * sig * 0.5) *
//			pT[i]) / (sig * sqrt(pT[i]));
//		vsCdfNorm(1, &d1, &p1);
//		vsCdfNorm(1, &d2, &p2);
//		pC[i] = pS0[i] * p1 - pK[i] *
//			exp((-1.0) * r * pT[i]) * p2;
//	}
//}
//
//void _V1(float *pT, float *pK, float *pS0, float *pC)
//{
//	int i;
//	float d1, d2, p1, p2;
//	for (i = 0; i < N; i++)
//	{
//		d1 = (logf(pS0[i] / pK[i]) + (r + sig * sig * 0.5f) *
//			pT[i]) / (sig * sqrtf(pT[i]));
//		d2 = (logf(pS0[i] / pK[i]) + (r - sig * sig * 0.5f) *
//			pT[i]) / (sig * sqrtf(pT[i]));
//
//		vsCdfNorm(1, &d1, &p1);
//		vsCdfNorm(1, &d2, &p2);
//		pC[i] = pS0[i] * p1 - pK[i] *
//			expf((-1.0f) * r * pT[i]) * p2;
//	}
//}
//
//void _V2(float *pT, float *pK, float *pS0, float *pC)
//{
//	int		i;
//	float	d1, d2;
//	float	erf1, erf2;
//
//	for (i = 0; i < N; i++)
//	{
//		d1 = (logf(pS0[i] / pK[i]) + (r + sig * sig * 0.5f) *
//			pT[i]) / (sig * sqrtf(pT[i]));
//		d2 = (logf(pS0[i] / pK[i]) + (r - sig * sig * 0.5f) *
//			pT[i]) / (sig * sqrtf(pT[i]));
//
//		erf1 = 0.5f + 0.5f * erff(d1 / sqrtf(2.0f));
//		erf2 = 0.5f + 0.5f * erff(d2 / sqrtf(2.0f));
//		pC[i] = pS0[i] * erf1 - pK[i] * expf((-1.0f) * r *
//			pT[i]) * erf2;
//	}
//}
//
////void _V3(float* restrict pT, float* restrict pK, float* restrict pS0, float* restrict pC)
////{
////	int		i;
////	float	d1, d2;
////	float	erf1, erf2;
////
////	for (i = 0; i < N; i++)
////	{
////		d1 = (logf(pS0[i] / pK[i]) + (r + sig * sig * 0.5f) *
////			pT[i]) / (sig * sqrtf(pT[i]));
////		d2 = (logf(pS0[i] / pK[i]) + (r - sig * sig * 0.5f) *
////			pT[i]) / (sig * sqrtf(pT[i]));
////
////		erf1 = 0.5f + 0.5f * erff(d1 / sqrtf(2.0f));
////		erf2 = 0.5f + 0.5f * erff(d2 / sqrtf(2.0f));
////		pC[i] = pS0[i] * erf1 - pK[i] * expf((-1.0f) * r *
////			pT[i]) * erf2;
////	}
////}
//
//void _V4(float* pT, float* pK, float* pS0, float* pC)
//{
//	int		i;
//	float	d1, d2, erf1, erf2;
//
//#pragma simd
//#pragma vector always
//	for (i = 0; i < N; i++)
//	{
//		d1 = (logf(pS0[i] / pK[i]) + (r + sig * sig * 0.5f) *
//			pT[i]) / (sig * sqrtf(pT[i]));
//		d2 = (logf(pS0[i] / pK[i]) + (r - sig * sig * 0.5f) *
//			pT[i]) / (sig * sqrtf(pT[i]));
//		erf1 = 0.5f + 0.5f * erff(d1 / sqrtf(2.0f));
//		erf2 = 0.5f + 0.5f * erff(d2 / sqrtf(2.0f));
//		pC[i] = pS0[i] * erf1 - pK[i] * expf((-1.0f) * r *
//			pT[i]) * erf2;
//	}
//}
//
//void _V5(float* pT, float* pK, float* pS0, float* pC)
//{
//	int		i;
//	float	d1, d2, erf1, erf2;
//
//#pragma simd
//	for (i = 0; i < N; i++)
//	{
//		d1 = (logf(pS0[i] / pK[i]) + (r + sig * sig * 0.5f) * pT[i]) / (sig * sqrtf(pT[i]));
//		d2 = (logf(pS0[i] / pK[i]) + (r - sig * sig * 0.5f) * pT[i]) / (sig * sqrtf(pT[i]));
//		erf1 = 0.5f + 0.5f * erff(d1 * invsqrt2);
//		erf2 = 0.5f + 0.5f * erff(d2 * invsqrt2);
//		pC[i] = pS0[i] * erf1 - pK[i] * expf((-1.0f) * r * pT[i]) * erf2;
//	}
//}
//
//void _V6(float* pT, float* pK, float* pS0, float* pC)
//{
//	int		i;
//	float	d1, d2, erf1, erf2;
//	float	sig2 = sig * sig;
//	float	invf;
//
//#pragma simd
//	for (i = 0; i < N; i++)
//	{
//		float tmp = sig2 * pT[i];
//		vsInvSqrt(1, &tmp, &invf);
//		d1 = (logf(pS0[i] / pK[i]) + (r + sig * sig * 0.5f)
//			* pT[i]) / (sig * invf);
//		d2 = (logf(pS0[i] / pK[i]) + (r - sig * sig * 0.5f)
//			* pT[i]) / (sig * invf);
//		erf1 = 0.5f + 0.5f * erff(d1 * invsqrt2);
//		erf2 = 0.5f + 0.5f * erff(d2 * invsqrt2);
//		pC[i] = pS0[i] * erf1 - pK[i] * expf((-1.0f) * r * pT[i]) * erf2;
//	}
//}
//
//void _V7(float *pT, float *pK, float *pS0, float *pC)
//{
//	int		i;
//	float	d1, d2, erf1, erf2, invf;
//	float	sig2 = sig * sig;
//
//#pragma simd
//#pragma omp parallel for private(invf, d1, d2, erf1, erf2)
//	for (i = 0; i < N; i++)
//	{
//		d1 = (logf(pS0[i] / pK[i]) + (r + sig * sig * 0.5f) *
//			pT[i]) / (sig * sqrtf(pT[i]));
//		d2 = (logf(pS0[i] / pK[i]) + (r - sig * sig * 0.5f) *
//			pT[i]) / (sig * sqrtf(pT[i]));
//
//		erf1 = 0.5f + 0.5f * erff(d1 / sqrtf(2.0f));
//		erf2 = 0.5f + 0.5f * erff(d2 / sqrtf(2.0f));
//
//		pC[i] = pS0[i] * erf1 - pK[i] * expf((-1.0f) * r * pT[i]) * erf2;
//	}
//}
//
//void _V8(float *pT, float *pK, float *pS0, float *pC)
//{
//	int i;
//	float d1, d2, erf1, erf2;
//	float sig2 = sig * sig;
//
//#pragma simd 
//#pragma vector nontemporal
//#pragma omp parallel for private(d1, d2, erf1, erf2)
//	for (i = 0; i < N; i++)
//	{
//		d1 = (logf(pS0[i] / pK[i]) + (r + sig * sig * 0.5f) *
//			pT[i]) / (sig * sqrtf(pT[i]));
//		d2 = (logf(pS0[i] / pK[i]) + (r - sig * sig * 0.5f) *
//			pT[i]) / (sig * sqrtf(pT[i]));
//
//		erf1 = 0.5f + 0.5f * erff(d1 / sqrtf(2.0f));
//		erf2 = 0.5f + 0.5f * erff(d2 / sqrtf(2.0f));
//
//		pC[i] = pS0[i] * erf1 - pK[i] * expf((-1.0f) * r * pT[i]) * erf2;
//	}
//}
