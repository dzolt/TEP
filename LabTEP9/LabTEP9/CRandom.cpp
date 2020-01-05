#include "CRandom.h"

CRandom::CRandom()
{
	random_engine = std::mt19937(random_device());
	vSetRange(1.0, 2.0);
}

CRandom::CRandom(int iSeed)
{
	random_engine = std::mt19937(iSeed);
	vSetRange(1.0, 2.0);
}

void CRandom::vSetRange(double dMinValue, double dMaxValue)
{
	random_distribution = std::uniform_real_distribution<double>(dMinValue, dMaxValue);
}

double CRandom::dGenerateNumber()
{
	return random_distribution(random_engine);
}