#include <iostream>
#include "V0.h"

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
	V0(pT, pK, pS0, pC);
	finish = omp_get_wtime();
	time = finish - start;
	std::cout << time << std::endl;

	delete[] pT;
	system("pause");
	return 0;
}