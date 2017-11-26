#include <iostream>
#include "V0.h"
#include "V1.h"
#include "V2.h"

typedef void(*GetPrices)(float *pT, float *pK, float *pS0, float *pC);
GetPrices option_array[9] = { _V0, _V1, _V2 };

int main(int argc, char *argv[]){

	unsigned int version;
	std::cout << "Choose a version:" << std::endl;
	std::cin >> version;

	float* pT = new float[4 * N];
	float* pK = pT + N;
	float* pS0 = pT + 2 * N;
	float* pC = pT + 3 * N;

	for (int i = 0; i < N; i++)
	{
		pT[i] = T;
		pS0[i] = S0;
		pK[i] = K;
	}

	start = omp_get_wtime();
	option_array[version](pT, pK, pS0, pC);
	finish = omp_get_wtime();
	time = finish - start;
	std::cout << time;
	//std::cout << "Price == " << pC[0] << std::endl;
	//std::cout << "time == " << time << std::endl;

	delete[] pT;
	system("pause");
	return 0;
}
