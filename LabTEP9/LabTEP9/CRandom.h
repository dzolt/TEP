#pragma once
#include <random>

class CRandom
{
public:
	CRandom();
	CRandom(int seed);
	
	void vSetRange(double dMinValue, double dMaxValue);

	double dGenerateNumber();
	
private:
	std::random_device random_device; //will be used to obtain a seed for random number engine
	std::mt19937 random_engine; //mersenne_twister_engine will be seeded with random_device
	std::uniform_real_distribution<double> random_distribution; //distributes random double from certain range
};//class CRandom