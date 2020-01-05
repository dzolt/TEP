#include "CRandom.h"

CRandom::CRandom()
{
	random_engine = std::mt19937(random_device());
	vSetRange(DEFAULT_RANDOM_MIN_VALUE,DEFAULT_RANDOM_MAX_VALUE);
}

CRandom::CRandom(int iSeed)
{
	random_engine = std::mt19937(iSeed);
	vSetRange(DEFAULT_RANDOM_MIN_VALUE, DEFAULT_RANDOM_MAX_VALUE);
}

CRandom& CRandom::vSetRange(double dMinValue, double dMaxValue)
{
	random_distribution = std::uniform_real_distribution<double>(dMinValue, dMaxValue);
	return *this;
}

double CRandom::dGenerateNumber()
{
	return random_distribution(random_engine);
}