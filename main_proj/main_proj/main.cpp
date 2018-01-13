#include <iostream>
#include "Header.h"

int main(int argc, char *argv[])
{
	version		= atoi(argv[1]);
	N			= atoi(argv[2]);
	num_Threads =  atoi(argv[3]);

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
	std::cout << _time << std::endl;
	std::cout << pC[1];

	delete[] pT;
	system("pause");
	return 0;
}
