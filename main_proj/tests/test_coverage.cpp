#include "gtest.h"
#include <iostream>
#include "Header.h"

float *pT, *pK, *pS0;
float *pC;

void _init()
{
	*pT = 3.0f;
	*pS0 = 100.0f;
	*pK = 100.0f;
}

TEST(EU_OP, test_V0)
{
	_init();
	//_V0(pT, pK, pS0, pC);
	ASSERT_EQ(*pC, float(20.9244));
}
