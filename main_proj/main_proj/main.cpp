#include <iostream>
#include "Header.h"
using namespace EU_OP;

typedef void(*GetPrices)(float *pT, float *pK, float *pS0, float *pC);
GetPrices option_array[9] = 
	{ 
		_V0, //preference 1
		_V1, //preference 2
		_V2, //erf
		_V3, //restrict
		_V4, //#pragma simd #pragma vector always
		_V5, //#pragma simd invsqrt2_1
		_V6, //#pragma simd invsqrt2_2
		_V7, //#pragma simd #pragma omp parallel for private
		_V8  // _V7 + #pragma vector nontemporal
	};

int main(int argc, char *argv[])
{
	version		= atoi(argv[1]);
	N			= atoi(argv[2]);
	num_Threads = atoi(argv[3]);

	float* pT 	= new float[4 * N];
	float* pK 	= pT + N;
	float* pS0 	= pT + 2 * N;
	float* pC 	= pT + 3 * N;

	for (int i = 0; i < N; i++)
	{
		pT[i] 	= T;
		pS0[i] 	= S0;
		pK[i] 	= K;
	}

	start = omp_get_wtime();
	option_array[version](pT, pK, pS0, pC);
	finish 	= omp_get_wtime();
	_time 	= finish - start;
	std::cout << _time;

	///start = omp_get_wtime();
	///option_array[version](pT, pK, pS0, pC);
	///finish = omp_get_wtime();
	///_time = finish - start;
	///std::cout << _time;


	//std::cout << "Price == " << pC[0] << std::endl;
	//std::cout << "time == " << _time << std::endl;

	delete[] pT;
//	system("pause");
	return 0;
}
