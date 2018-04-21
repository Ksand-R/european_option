#include <iostream>
#include "Header.h"

int main(int argc, char *argv[])
{
	version		= atoi(argv[1]);
	N 			= atoi(argv[2]);
	num_Threads = atoi(argv[3]);
	omp_set_num_threads(num_Threads);
	float* pT 	= new float[5 * N];
	float* pK 	= pT + N;
	float* pS0 	= pT + 2 * N;
	float* pC 	= pT + 3 * N;
	float* pP 	= pT + 4 * N;

	for (int i = 0; i < N; i++)
	{
		pT[i] 	= T;
		pS0[i] 	= S0;
		pK[i] 	= K;
	}
	
//	int sum = 0;
	if (version == 8 || version == 9)
	{
//		int a[1024] = { 0 };
//		#pragma omp parallel shared(a) reduction (+: sum) 
//		{
//			# pragma omp for
//			for (int i = 0; i < 4096; ++i)
//				sum += a[i];
//		}
		option_array[version](pT, pK, pS0, pC, pP);
		option_array[version](pT, pK, pS0, pC, pP);
		start = omp_get_wtime();
		option_array[version](pT, pK, pS0, pC, pP);
		finish 	= omp_get_wtime();
		_time 	= finish - start;
	}
	else
	{
		start = omp_get_wtime();
		option_array[version](pT, pK, pS0, pC, pP);
		finish 	= omp_get_wtime();
		_time 	= finish - start;
	}

	std::cout << _time  << std::endl;
//	std::cout << sum << std::endl;
	//std::cout << pC[1];
	//std::cout << pP[1];
	delete[] pT;
//	system("pause");
	return 0;
}
